# for i in range(1, 8):
#     with open("neg_0{}_args.txt".format(i), "w") as f:
#         f.write("./func_tests/data/neg_0{}_in.txt out.txt".format(i))

#     with open("neg_0{}_in.txt".format(i), "w") as f:
#         f.write("1\n2\n3\n4\n5")


# for i in range(1, 6):
#     with open("pos_0{}_args.txt".format(i), "w") as f:
#         f.write("./func_tests/data/pos_0{}_in.txt ./out/real_output_data.txt".format(i))
    # with open("pos_0{}_in.txt".format(i), "w") as f:
    #     pass
    # with open("pos_0{}_out.txt".format(i), "w") as f:
    #     pass


# from random import randint
#
#
# arr = [randint(0, 100)] + [randint(-100, 100) for i in range(90)] + [randint(0, 100) for i in range(9)]
#
# with open("pos_05_in.txt", "w") as src, open("pos_05_out.txt", "w") as out:
#     for i in range(len(arr) - 1):
#         src.write(str(arr[i]))
#         src.write('\n')
#     src.write(str(arr[-1]))
#
#     index = len(arr) - 1
#     while arr[index] >= 0:
#         index -= 1
#
#     arr = arr[:index]
#     arr.sort()
#
#     for i in range(len(arr) - 1):
#         out.write(str(arr[i]))
#         out.write(' ')
#     out.write(str(arr[-1]))


with open("../data/pos_05_out.txt", "r") as src, open("../../out/real_output_data.txt", "r") as real:
    src_lines = [int(line) for line in src.readlines()[0].split(' ')]
    real_lines = [int(line) for line in real.readlines()[0].split(' ')]

    print("Len src: {}; len real: {}".format(len(src_lines), len(real_lines)))
