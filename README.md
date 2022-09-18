# Bloom filter

C++ header-only [**Bloom filter**](https://en.wikipedia.org/wiki/Bloom_filter) data structure

### Context

This probabilistic data structure was introduced in my algorithms course ([Algoritmos com C++](https://www.agit.com.br/cursoalgoritmos.php "Algoritmos com C++")), then I'm sharing here as free code.

The first time I had to deal with a problem using Bloom filter was using the [Guava library](https://github.com/google/guava/wiki/HashingExplained#bloomfilter) from Google. 
So I felt like I needed to port and adapt to my favorite programming language: [C++](https://isocpp.org/ "C++")
After that, I've ported and adapted to [C#](https://learn.microsoft.com/en-us/dotnet/csharp/ "C#") in a commercial release, exploring its capabilities to solve the problem of [Idempotent Consumer](https://microservices.io/patterns/communication-style/idempotent-consumer.html "Idempotent Consumer").
Here is the result of my experience. Enjoy it!

### C++ example 

```cpp
auto bf = bloom_filter::make_bloom_filter<std::string>(100, 0.01);
bf.add("hello");
bf.add("world");
bf.add("hello");
bf.exists("hello"); //true
bf.exists("C++");   //false
```

### Bloom filter in action

![Bloom filter in action](/images/bloom_filter.PNG "Bloom filter in action")

## License

MIT

**Free Software, Hell Yeah!**
