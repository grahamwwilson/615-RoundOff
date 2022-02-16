x = 1.0
dx = 1.0
y = x + dx
i = 0
while y > 1.0:
    i += 1
    dx = dx/2.0
    y = x + dx
    print(i,dx,y)
