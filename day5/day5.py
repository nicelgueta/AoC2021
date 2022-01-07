import numpy as np
import pandas as pd

INC_PART_2 = True

with open('input.txt', 'r') as f:
    data = [l.strip() for l in f.readlines()]

processed = [ l.split(" -> ") for l in data ]
coords = []
maxX, maxY = 0,0
for o in processed:
    a,b = o
    coords.append([
        tuple([ int(i) for i in  a.split(",") ]), 
        tuple([ int(i) for i in  b.split(",") ])
    ])
for coord in coords:
    x1 = coord[0][0]
    if x1 > maxX:
        maxX = x1
    y1 = coord[0][1]
    if y1 > maxY:
        maxY = y1
    x2 = coord[1][0]
    if x2 > maxX:
        maxX = x2
    y2 = coord[1][1]
    if y2 > maxY:
        maxY = y2

df = pd.DataFrame(np.zeros((maxX + 2,maxY + 2)))
# print(df)

# work out liens
for coord in coords:
    x1 = coord[0][0]
    x2 = coord[1][0]

    y1 = coord[0][1]
    y2 = coord[1][1]

    yD = (y2 - y1)
    xD = (x2 - x1)
    
    # non diags
    if not xD or not yD:
        if xD:
            y = y1
            for x in [x for x in range(x1, x2+np.sign(xD), np.sign(xD))]:
                df[x][y]+=1
        if yD:
            x = x1
            for y in [y for y in range(y1, y2+np.sign(yD), np.sign(yD))]:
                df[x][y]+=1
    else:
        if INC_PART_2:
            xs = [x for x in range(x1, x2+np.sign(xD), np.sign(xD))]
            ys = [y for y in range(y1, y2+np.sign(yD), np.sign(yD))]
            for x,y in zip(xs, ys):
                df[x][y]+=1

# print(df)
total = 0
for idx in df.index:
    for col in df.columns:
        if df[col][idx] >= 2:
            total+=1
print(f"{total=}")


    

