from random import randint, choice


# Cоздание случайной матрицы	
def gen_random_matrix(matrix, rows, cols, non_zeros):
    for _ in range(rows):
        matrix.append([0] * cols)

    all_cells = list()
    for i in range(rows):
        for j in range(cols):
            all_cells.append((i, j))

    poss_elems = [i for i in range(-100, 0)] + [i for i in range(1, 101)]
    elems = [choice(poss_elems) for _ in range(non_zeros)]

    for i in range(non_zeros):
        cell = all_cells.pop(randint(0, len(all_cells) - 1))
        matrix[cell[0]][cell[1]] = elems[i]


# Cоздание случайного вектора	
def gen_random_vector(vector, rows, non_zeros):
    for _ in range(rows):
        vector.append([0])

    all_cells = list()
    for i in range(rows):
        all_cells.append(i)

    poss_elems = [i for i in range(-100, 0)] + [i for i in range(1, 101)]
    elems = [choice(poss_elems) for _ in range(non_zeros)]

    for i in range(non_zeros):
        i_ind = all_cells.pop(randint(0, len(all_cells) - 1))
        vector[i_ind][0] = elems[i]


# Запись матрицы в файл
def write_matrix_to_file(file_name, matrix):
    size_i = len(matrix)
    size_j = len(matrix[0])

    entries = list()
    for i in range(size_i):
        for j in range(size_j):
            if matrix[i][j] != 0:
                entries.append(f"{i} {j} {matrix[i][j]}")

    for i in range(len(entries) - 1):
        entries[i] += "\n"

    with open(file_name, "w") as f:
        for string in entries:
            f.write(string)


def main():
    for size in [10, 50, 100, 150]:
        for pers in range(0, 101):
            non_zeros = int(pers / 100 * size * size)
            file_name = f"mtr_{size}_{pers}.txt"
            matrix = list()
            gen_random_matrix(matrix, size, size, non_zeros)
            write_matrix_to_file(file_name, matrix)

            non_zeros = int(pers / 100 * size)
            file_name = f"vec_{size}_{pers}.txt"
            vector = list()
            gen_random_vector(vector, size, non_zeros)
            write_matrix_to_file(file_name, vector)


if __name__ == "__main__":
    main()
