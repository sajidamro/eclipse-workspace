
divisors = []

div_var = int(raw_input("Press a number to check a list of its divisor "))
 
for x in range (1,div_var):
    if  (div_var % x) ==0 :
        divisors.append(x)
print divisors  
print len(divisors)

    
