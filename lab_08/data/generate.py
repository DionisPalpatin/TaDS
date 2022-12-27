from random import randint, choice


size = 5
elems = [randint(1, 15)] * size + [10000] * size
matrix = [[10000 for _ in range(size)] for _ in range(size)]
for i in range(size):
   for j in range(i + 1, size):
       matrix[i][j] = choice(elems)
       if 0 < matrix[i][j] < 10000:
           matrix[j][i] = randint(1, 15)
for i in range(size):
   matrix[i][i] = 0


filename = "data/example.txt"
with open(filename, "w") as f:
   f.write(f"{size}\n")
   for row in matrix:
       f.write(" ".join(list(map(str, row))))
       f.write("\n")


# for i in range(5, 55, 5):
# 	filename = f"test/test_{i}.txt"
#
#
# 	size = i
# 	elems = [randint(1, 15)] * size + [10000] * size
# 	matrix = [[10000 for _ in range(size)] for _ in range(size)]
# 	for i in range(size):
# 		for j in range(i + 1, size):
# 		    matrix[i][j] = choice(elems)
# 		    if 0 < matrix[i][j] < 10000:
# 		        matrix[j][i] = randint(1, 15)
# 	for i in range(size):
# 		matrix[i][i] = 0
#
#
# 	with open(filename, "w") as f:
# 	    f.write(f"{size}\n")
# 	    for row in matrix:
# 	        f.write(" ".join(list(map(str, row))))
# 	        f.write("\n")

