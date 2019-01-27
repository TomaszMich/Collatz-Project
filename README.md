# Collatz function


The Collatz function is a function f:ℕ⟶ℕ such that f(n)=3n+1 if n is odd and f(n)=n/2 if n is even. Use the function on the smallest/largest number of a given sequence.
If there are two or more smallest/largest numbers we choose the first one in the sequence.
If the smallest numbers are 1s then we pick the second smallest number.
If after applying the Collatz function the result does not fit in unsigned int (32-bit) then the result is omitted. The omitted numbers from the sequence are not taking into account when the smallest/largest numbers are searched.
# Input
In the first line there is a number n - the number of elements in the sequence (n<60000).
In the second line there are n numbers - the sequence. All the number are positive integers that fit into unsigned int. 
In the third line there is a number of commands (q).
The next q lines consist the commands.
A command consists of a number k and a charter c. The charter decides the searched number, 's' stands for the smallest numbers, 'l' stands for the largest numbers. The number k describes number of times which searching and applying the Collatz function should occur.
# Output
Write the sequence after performing the commands. Instead the omitted numbers write charter 'm'.
