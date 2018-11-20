# The CPU Cache and You

-   [The CPU Cache and You](#the-cpu-cache-and-you)

## Introduction

You've likely heard about CPU caches. The idea of "caching" is simple: introduce a layer that sits between the consumer of some operation and the producer, store the result of the operation after the first time it's performed, and then return that stored result rather than performing the potentially costly operation again. This pattern is ubiquitous in computing, implemented in both software (e.g. cached database queries) and at the hardware (CPU Caches).

All caches exhibit some key features, however. They solve for a performance issue, where the cached data is too expensive to be computed with every access. They involve a hierarchy of data access, in which the cache is checked first for the result, and if not present, the _cache miss_ is "graceful". The additional computation is now performed and stored in the cache so that future requests result in a _cache hit_. A cache will also almost always only contain a small subset of possible data, since storage has a memory cost associated with it, and the cache will only ever contain the results that have been computed so far.

CPU caches have all of these features. They sit between your CPU and your Memory, storing data that has been recently accessed from the Memory in the hopes that if your CPU accesses the same data, or data this is "close by", it will be able to return faster than the entire round trip to memory.

In case you are curious as to why this is neccessary, one important thing to note is that modern CPUs are capable of consuming and processing data much, MUCH faster than modern RAM is able to return it. The reasons for this come down to two things:

1. General memory access speeds has not kept pace with CPU speeds due to cost and physical limitations
2. The CPU's access to memory is limited due to the Von Neumann architecture.

## Experiments

### Looping through an array

## Results

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
