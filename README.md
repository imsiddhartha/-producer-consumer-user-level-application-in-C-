Implemented a producer consumer user­level application using shared­memory. 

Producer writes a fibonacci number in shared memory and waits for the consumer to read it and 
reply back with the next fibonacci number. Then this goes in cycle between both of them. 
 
The starting two numbers of the fibonacci series will be given as input to both producer & 
consumer.



Example :  
Producer process:      ./a.out 3 10 
Consumer process:     ./a.out 5 10 

This means the fibonacci series starts from 3 and goes upto next 10 numbers ­  
3   5     8     13     21     34     55     89     144     233 

