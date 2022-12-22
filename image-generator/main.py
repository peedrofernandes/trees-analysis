import matplotlib.pyplot as plt

avlFile = open("files/avl.txt", "r")
b1File = open("files/b1.txt", "r")
b5File = open("files/b5.txt", "r")
b10File = open("files/b10.txt", "r")
rnFile = open("files/rubroNegra.txt", "r")

def generate_png(x, y, color, path):
  # plt.scatter(x, y, color)
  plt.scatter(x, y, 1, color)
  plt.savefig(path)

avlFile.readline()
b1File.readline()
b5File.readline()
b10File.readline()
rnFile.readline()

avlWorstLines = [avlFile.readline() for _ in range(0, 1000)]
b1WorstLines = [b1File.readline() for _ in range(0, 1000)]
b5WorstLines = [b5File.readline() for _ in range(0, 1000)]
b10WorstLines = [b10File.readline() for _ in range(0, 1000)]
rnWorstLines = [rnFile.readline() for _ in range(0, 1000)]

avlFile.readline()
b1File.readline()
b5File.readline()
b10File.readline()
rnFile.readline()

avlMediumLines = [avlFile.readline() for _ in range(0, 1000)]
b1MediumLines = [b1File.readline() for _ in range(0, 1000)]
b5MediumLines = [b5File.readline() for _ in range(0, 1000)]
b10MediumLines = [b10File.readline() for _ in range(0, 1000)]
rnMediumLines = [rnFile.readline() for _ in range(0, 1000)]

avlData = [[int(avlWorst.split()[1]), float(avlMid.split()[1])] for (avlWorst, avlMid) in zip(avlWorstLines, avlMediumLines)]

b1Data = [[int(b1Worst.split()[1]), float(b1Mid.split()[1])] for (b1Worst, b1Mid) in zip(b1WorstLines, b1MediumLines)]

b5Data = [[int(b5Worst.split()[1]), float(b5Mid.split()[1])] for (b5Worst, b5Mid) in zip(b5WorstLines, b5MediumLines)]

b10Data = [[int(b10Worst.split()[1]), float(b10Mid.split()[1])] for (b10Worst, b10Mid) in zip(b10WorstLines, b10MediumLines)]

rnData = [[int(rnWorst.split()[1]), float(rnMid.split()[1])] for (rnWorst, rnMid) in zip(rnWorstLines, rnMediumLines)]

x = [i for i in range(1, 1001)]

# Pior caso
generate_png(x, [y[0] for y in avlData], "green", "files/worst.png")
generate_png(x, [y[0] for y in b1Data], "black", "files/worst.png")
generate_png(x, [y[0] for y in b5Data], "blue", "files/worst.png")
generate_png(x, [y[0] for y in b10Data], "orange", "files/worst.png")
generate_png(x, [y[0] for y in rnData], "red", "files/worst.png")


# Caso médio
generate_png(x, [y[1] for y in avlData], "green", "files/medium.png")
generate_png(x, [y[1] for y in b1Data], "black", "files/medium.png")
generate_png(x, [y[1] for y in b5Data], "blue", "files/medium.png")
generate_png(x, [y[1] for y in b10Data], "orange", "files/medium.png")
generate_png(x, [y[1] for y in rnData], "red", "files/medium.png")

# generate_png(x, [y[0] for y in avlData], "red", "../files/avl.png")
# generate_png(x, [y[1] for y in avlData], "blue", "../files/avl.png")
# print(len(x))
# print(len([y[0] for y in avlData]))

# for i in range(0, 1000):
#   print(float(avlMedium[i].split()[1]))
