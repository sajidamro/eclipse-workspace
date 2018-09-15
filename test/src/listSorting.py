a = [1,1,2,3,5,8,13,21,34,55,89]

final = []

age_var = int(raw_input("Press a numer to sort the list untill "))
b = age_var#5 
for x in range (len(a)):
    if b > a[x]:
        final.insert(x,a[x])
print final  

    
