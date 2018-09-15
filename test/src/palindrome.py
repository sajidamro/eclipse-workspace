
s = raw_input("Type in a palindrome word")
print s

#for x in range (len(s)):
print "reversing the string"

s_rev = s[::-1]

print s_rev

if s == s_rev:
    print "We have a palindrome "
else: 
    print "Eneterd string does not belong to palindrome category"
    
