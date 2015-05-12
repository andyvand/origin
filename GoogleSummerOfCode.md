# Introduction #
We plan to apply as a mentoring organization for [Google Summer of Code](http://www.google-melange.com/) this year. The goal of our participation in this project is to encourage students to implement generic libraries using the C++0x programming language. The focus of GSoC projects will be on the investigation of a computational domain (set theory, graph theory, linear algebra, computational geometry, etc.), and the initial design, specification, and implementation of its basic abstractions. Note that Origin projects are not specifically limited to scientific computation; operating system and data/text processing concepts are also of interest.

Prospective students must have a strong background in C++ programming, be especially comfortable reading and writing templates, and have a basic understanding of [concepts](CxxConcepts.md).

# Submission Requirements #
A GSoC submission for Origin requires the following information.

## Personal & Academic Information ##
  * Name:
  * College/University?:
  * Course/Major?:
  * Degree Program (B.Sc., M, Sc., PhD, etc.)
  * Email:
  * Homepage:
  * Availability:
    * How much time do you plan to spend on your GSoC?
    * What are your intended start and end dates?
    * What other factors affect your availability (exams, courses, moving, work, etc.)?

## Background Information ##
Please summarize your educational background (degrees earned, courses taken, etc.). Please do not include information about programming contests; they have no bearing on the quality of the application. Please do not include references to faculty members at your university; they have no bearing on the quality of the application.

Please summarize your programming background (OSS projects, internships, jobs, etc.). Please do not include references to managers at your previous positions. they have no bearing on the quality of the application.

Please tell us a little about your programming interests.

Please tell us why you are interested in contributing to Origin.

What is your interest in the project you are proposing?

Have you done any previous work in this area before or on similar projects?

What are your plans beyond this Google Summer of Code time frame for your proposed work?.

What software development environments are you most familiar with (Visual Studio, Eclipse, KDevelop, etc.)?

What software documentation tool are you most familiar with (Doxygen, DocBook, Quickbook, etc.)?

## Project Proposal ##
Please provide a description of your proposed work. Please note that we are looking for substantially more than a single statement of purpose. A good proposal will include the following:

  1. An introduction that clearly states your proposed goal
  1. A short survey of related work and implementations
  1. A description of how your proposal varies from or incorporates the surveyed material. Describing interfaces or usage patterns works well here.

## Proposed Milestones and Schedule ##
Please provide estimated milestones and schedule for completing the proposed work.

# Project Ideas #
The following topics are areas in which project submissions can be made. It is unlikely that any topic could be fully implemented over the course of a single summer. However, small subsets of each topic (a handful of data structures and algorithms) make idea GSoC projects.

## Advanced Data Structures ##
Prefix trees (tries), suffix trees, mutable heaps, binomial and fibonacci heaps, etc. These make great summer-long projects. Understanding tradeoffs, strategies, memory management and exception safety issues require serious thought and experimentation.

## Arbitrary Precision Arithmetic Types ##
The C++ standard (and Boost) continue to lack comprehensive support for arbitrary precision integer and floating point types.

## Extended Numeric Types ##
There are a variety of interesting numeric types that can be implemented. These include arbitrary-width integers, fixed-point decimal types, polynomial functions, and rational numbers and functions.

## Linear Algebra ##
A great number of useful computing applications require matrix computation. While there are a number of libraries providing these facilities, it would be nice to have some native to Origin.

## Sets ##
Sets are fundamental abstractions in mathematics and computer science. Beyond the standard associative containers, `std::bitset`, and `boost::dynamic_bitset`, and their related algorithms, there does not seem to be a clear conceptual definition of _sets_ in the abstract.

## Graphs ##
Origin already has a nascent graph library, but it's far from complete. There are a number of projects that could be proposed to extend the existing work. New graph data structures, algorithms, adatpors, and I/O facilities make ideal candidates.