import random

a = []
b = []

for i in range(100):
    a.append(random.randrange(1,101,1))
    b.append(random.randrange(1,50,1))
print a
print "length of a is: "+str(len(a))
print b
print "Length of b is: "+str(len(b))

Overlap_List = []

for x in range(len(b)):
    for y in range(len(a)):
        if a[y] == b [x]:
            if b[x] not in Overlap_List:
                Overlap_List.append(b[x])

print Overlap_List