from random import randint, choice


def load_data(filename, array):
    with open(filename, "r") as f:
        for line in f:
            array.append(line.strip())


musicals = list()
plays = list()
composers = list()
countries = list()
names = list()
surnames = list()
theaters = list()


load_data("musicals.txt", musicals)
load_data("theaters.txt", theaters)
load_data("composers.txt", composers)
load_data("names.txt", names)
load_data("surnames.txt", surnames)
load_data("plays.txt", plays)
load_data("countries.txt", countries)


possible_types = ["child", "adult", "musical"]
possible_genres_c = ["play", "fairy tale"]
possible_genres_g = ["play", "drama", "comedy"]


total_els = [50, 100, 250, 500, 1000]
for j in total_els:

# j = 90
    with open(f"test_data_{j}.txt", "w") as f:
        for i in range(j):
            producer = choice(names) + " " + choice(surnames)
            if len(producer) > 20:
                producer = producer[:20]

            perf_type = choice(possible_types)
            performance = choice(musicals) if perf_type == "musical" else choice(plays)

            f.write("Theater:{}\n".format(choice(theaters)))
            f.write("Performance:{}\n".format(performance))
            f.write("Producer:{}\n".format(producer))
            f.write("Minimum price:{}\n".format(randint(1, 10000)))
            f.write("Maximum price:{}\n".format(randint(10001, 50000)))
            f.write("Type:{}\n".format(perf_type))

            if perf_type == "child":
                f.write("Minimum age:{}\n".format(randint(0, 3)))
                f.write("Maximum age:{}\n".format(randint(4, 7)))
                f.write("Genre:{}".format(choice(possible_genres_c)))
            elif perf_type == "adult":
                f.write("Genre:{}".format(choice(possible_genres_g)))
            else:
                f.write("Composer:{}\n".format(choice(composers)))
                f.write("Country:{}\n".format(choice(countries)))
                f.write("Minimum age:{}\n".format(randint(0, 5)))
                f.write("Duration:{}".format(randint(100, 200)))

            if i != j - 1:
                f.write("\n")
