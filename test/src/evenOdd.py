
#name_var = raw_input ("what is your name: ")
#print ("Your name is " + name_var)

while 1:
    age_var = int(raw_input("Press a number to check for EVEN/ODD: "))
    
    if (age_var % 2) == 0:
        if (age_var % 4) == 0:
            print ("Number entered is Even and devisible by 4")
        else:
            print ("Number entered is Even")
    else:
        print ("Number id Odd")   
    
