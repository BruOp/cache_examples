# Experiments in CPU Caching

-   [The CPU Cache and You](#the-cpu-cache-and-you)

## Introduction

You've likely heard about CPU caches. The idea of "caching" is simple: introduce a layer that sits between the consumer of some operation and the producer, store the result of the operation after the first time it's performed, and then return that stored result rather than performing the potentially costly operation again. This pattern is ubiquitous in computing, implemented in both software (e.g. cached database queries) and at the hardware (CPU Caches).

All caches exhibit some key features, however. They solve for a performance issue, where the cached data is too expensive to be computed with every access. They involve a hierarchy of data access, in which the cache is checked first for the result, and if not present, the _cache miss_ is "graceful". The additional computation is now performed and stored in the cache so that future requests result in a _cache hit_. A cache will also almost always only contain a small subset of possible data, since storage has a memory cost associated with it, and the cache will only ever contain the results that have been computed so far.

CPU caches are no different. They sit between your CPU and your Memory, storing data that has been recently accessed from the Memory in the hopes that if your CPU accesses the same data, or data this is "close by", it will be able to return faster than the entire round trip to memory.

In case you are curious as to why this is necessary, one important thing to note is that modern CPUs are capable of consuming and processing data much, MUCH faster than modern RAM is able to return it. The reasons for this come down to two things:

1. General memory access speeds have not kept pace with CPU speeds due to cost and physical limitations
2. The CPU's access to memory is limited due to the Von Neumann architecture.

In terms of implementation, there are a few important features to note:

-   The CPU cache is actually a hierarchy of caches. The number of caches and their arrangement is hardware specific, but most modern CPUs (circa 2018) will have three levels.
-   Each level in the CPU Cache is slower than the one above it, but also larger. This means that each tier will replace its data less frequently that the tier above it.
-   When the CPU attempts to access the data, each tier of cache is checked to see if it contains the data. If no cache contains the data, it's time to make a trip to system memory.
-   Data is fed into the cache in chunks called **Cache Lines**. The size of a cache line seems to have stabilized around 64 Bytes.

There's quite a bit more to CPU caches than this: replacement policies, write policies, multi-core systems and their caches, etc. but I'm going to stick to these basic facts for now. You can read more on the [wikipedia page](https://en.wikipedia.org/wiki/CPU_cache), which is quite excellent, or the paper by [Ulrich Drepper](https://akkadia.org/drepper/cpumemory.pdf).

## Cache Hierarchy

In my current XPS 15 laptop, there is a i7 6700HQ with the following Cache Hierarchy:

You can see that each core has it's own L1 and L2 caches, as well as a core-agnostic L3 cache. The sizes are:

-   L1 Cache: 256kb
    -   L1d (Data): 128 kB
    -   L1i (Instruction): 128 kB
-   L2 Cache: 1 MB
-   L3 Cache: 6 MB

You'll notice that the L1 Cache is split into Data and Instruction caches. This is due to the fact that the instructions your sending to your CPU are also store in memory and sent through the caching layers. Only the L1 cache has this explicit divide between instruction and data. The experiments I'm going to present below are going to focus on the data caches, but really the principles are the same. Cache misses are expensive regardless of whether it's data or instructions, so laying out instructions such that they can be easily cached and predictably accessed is important.

The timings aren't officially available to me, but generally L1 cache reads are on the order of ~5 cycles,

## Experiments

I tried to model my experiments off [this excellent blog post](http://igoro.com/archive/gallery-of-processor-cache-effects/) by Igor Ostrovsky. Interestingly, I wasn't able to reproduce his results, which I'll go into further detail about in the next section. The two experiments I tried to reproduce were:

1. Stepping through an array of fixed size (larger than the largest cache available to me) with step sizes increasing past 64 bytes
2. Stepping 64 bytes at a time through variably sized arrays, from 2kB to 10MB.

## Results

I tried to model my experiments off [this excellent blog post](http://igoro.com/archive/gallery-of-processor-cache-effects/) by Igor Ostrovsky. Interestingly, I wasn't able to reproduce his results around stepping through an array of fixed size with step sizes increasing > 64 bytes, nor for his experiment around stepping 64 bytes/iteration through variably sized arrays. In both cases I saw basically constant time, with exception to one or two extreme outliers. In fact, every time I ran either experiment, I encountered the issue where my first loop would always take a very long time, even though it was always designed to be well within the cache limits. Running each step in the experiment multiple times revealed that the very first loop ALWAYS took several times as long as subsequent loops. I'm not super sure what the deal is with this! I'm worried it my be due to my caches being filled with

In both cases I saw basically constant time, with exception to one or two extreme outliers. In fact, every time I ran either experiment, I encountered the issue where my first loop would always take a very long time, even though it was always designed to be well within the cache limits. Running each step in the experiment multiple times revealed that the very first loop ALWAYS took several times as long as subsequent loops. I'm not super sure what the deal is with this! I'm worried it my be due to my caches being filled with

```txt
I   refs:      104,222,306,602
I1  misses:              1,738
LLi misses:              1,687
I1  miss rate:            0.00%
LLi miss rate:            0.00%

D   refs:       72,202,246,044  (72,121,484,770 rd   + 80,761,274 wr)
D1  misses:        510,311,726  (   508,301,307 rd   +  2,010,419 wr)
LLd misses:        508,723,640  (   506,714,496 rd   +  2,009,144 wr)
D1  miss rate:             0.7% (           0.7%     +        2.5%  )
LLd miss rate:             0.7% (           0.7%     +        2.5%  )

LL refs:           510,313,464  (   508,303,045 rd   +  2,010,419 wr)
LL misses:         508,725,327  (   506,716,183 rd   +  2,009,144 wr)
LL miss rate:              0.3% (           0.3%     +        2.5%  )
```

## Analysis

## Further Exploration
