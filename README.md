# MatchingWildcards

<br /><b>Matching Wildcards: An Improved Algorithm for Big Data</b><br />
This is a new algorithm for matching wildcards.  It has been tested for reliability and performance.  In many commonly occurring situations it outperforms all prior algorithms that have been compared, to my knowledge.  Graphical comparative performance findings appear at this link, along with a description of the algorithmic design strategy:<br />
http://www.developforperformance.com/MatchingWildcards_AnImprovedAlgorithmForBigData.html<br />
<br />
<b>Code listings</b><br />
Listing1.cpp - a pointer-based implementation, named FastWildCompare();<br />
Listing2.cpp - a more portable version that relies on index variables rather than pointers, named FastWildComparePortable();<br />
Listing3.cpp - a test routine covering the handling of strings that contain wildcards, named TestWild();<br />
Listing4.cpp - a test routine covering the handling of strings that don't contain wildcards, named TestTame();<br />
Listing5.cpp - a test routine covering empty string handling, named TestEmpty().<br />
<br />
<b>Brief discussion</b><br />
(Excerpted from the <i>Develop for Performance</i> article at the above URL, which goes on to describe details of the design strategy, along with performance findings.)<br />
<br />
Over the past ten years, concepts for how to improve on the existing algorithms for matching wildcards have come to me now and then.  Meanwhile, there have been requests for permission to include the two routines that I’ve published in <i>Dr. Dobb's Journal</i> in various projects, occasional suggestions for improved correctness or completeness, and various thoughts that have arrived out of the blue.  One thought was this: though the approach I took in 2014 – tuning my first non-recursive routine of 2008[1] using a performance profiler – turned out to be successful[2], tuning code is no substitute for designing it as well as can be from the start for the use case at hand.<br />
<br />
A profiler has nothing to say about the ways in and out of string matching that might be handled more efficiently than how previous routines have gone about it.  Something I’ve observed from profiling these routines is that the more special cases can be handled in special logic, off the paths more commonly taken through the code, the faster those commonly taken paths can work.  An empty input string represents an increasingly popular case of a commonly taken path.  Another thing I’ve realized is that while handling the entire string matching job in a single while loop may seem elegant, it pushes the logic for matching text subsequent to a * wildcard to be at, or near the top of, another commonly taken path.<br />
<br />
Some important use cases for any general purpose routine for matching wildcards come up in the course of processing sparse data.  Since big data use cases are often just as well described as sparse data use cases that scale, the routine can be handed lots of empty strings just when it needs to be at its most efficient.  That is, either the “tame” or “wild” input strings may be empty, over and over, across a large data set.  The routine also may be called for long strings that don’t contain any wildcards, given the off-chance that a wildcard may be in there now and then.  In cases like these, the routine ideally should act as much as possible like one of its non-wildcard peers, except for the additional checks for the wildcard characters.<br />
<br />
The evolution of the algorithmic design strategy can be traced via the <i>Dr. Dobb's Journal</i> articles cited above:<br />
[1] http://www.drdobbs.com/architecture-and-design/matching-wildcards-an-algorithm/210200888<br />
[2] http://www.drdobbs.com/architecture-and-design/matching-wildcards-an-empirical-way-to-t/240169123
