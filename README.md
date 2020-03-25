
# GeneticAlgorithm Reloaded(v2.0.3A)
This algorithm is fully rewrited on c++.:)
Algorithm is based on vector of struct instances.

- Genetical Algorithm? What is this?
-There is a certain number of bool vectors with the same number of elements (genes), 
in the future I will call these vectors individuals.

There is a vector of individuals in it all individuals of the current population are stored.

The first stage: the number of individuals indicated at the beginning of the 
algorithm is generated with the specified number of random genes, 
the generated individuals are written to the vector of individuals.

Second stage (Selection and crossing over): Two random individuals are selected, 
they are compared by the number of positive genes (units), the one in which more units are stored in the buffer, 
then one more is selected from the other two random individuals and written to the first buffer. 
Then a random number r is generated from 0 to a number equal to the length of the individual, 
then an individual is written in the vector of the next population in which genes from the first 
individual are written in the buffer from the first to the r-gene, and from the r-gene to the last of the second, 
respectively, which individual is the buffer is the first and which is the second, determined randomly. 
(this operation is repeated until the entire vector of individuals is completely filled)

The third stage (Mutation):
Each individual in a new population goes through a mutation. 
A mutation is similar to a biological mutation, or rather, 
a change in some genes to the opposite (in our case, a change of one to zero, and vice versa).

Fourth step: Record a new population in place of the old and repeat the algorithm.


Last Update:
version 2.0.3A
