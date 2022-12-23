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

def generate_scatter(x, y, colorSet, labelSet, path):
  plt.clf()
  for i, yi in enumerate(y):
    plt.scatter(x, yi, 2, colorSet[i], label=labelSet[i])
  plt.legend(loc='upper right', scatterpoints=1, markerscale=8)
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

# # Pior caso
# generate_png(x, [y[0] for y in avlData], "green", "files/worstCaseScattered.png")
# generate_png(x, [y[0] for y in b1Data], "black", "files/worstCaseScattered.png")
# generate_png(x, [y[0] for y in b5Data], "blue", "files/worstCaseScattered.png")
# generate_png(x, [y[0] for y in b10Data], "orange", "files/worstCaseScattered.png")
# generate_png(x, [y[0] for y in rnData], "red", "files/worstCaseScattered.png")


# # Caso médio
# generate_png(x, [y[1] for y in avlData], "green", "files/avgCaseScattered.png")
# generate_png(x, [y[1] for y in b1Data], "black", "files/avgCaseScattered.png")
# generate_png(x, [y[1] for y in b5Data], "blue", "files/avgCaseScattered.png")
# generate_png(x, [y[1] for y in b10Data], "orange", "files/avgCaseScattered.png")
# generate_png(x, [y[1] for y in rnData], "red", "files/avgCaseScattered.png")

# --------------------------------------------
data = [avlData, b1Data, b5Data, b10Data, rnData]
yWorst = [[y[0] for y in di] for di in data]
yAvg = [[y[1] for y in di] for di in data]
colorSet = ["blue", "magenta", "green", "black", "red"]
labelSet = ["Avl Tree", "B-tree dg.1", "B-tree dg.5", "B-tree dg.10", "Red-black tree"]

# Pior caso

generate_scatter(x, yWorst, colorSet, labelSet, "files/worstCaseScattered.png")

# Caso médio

generate_scatter(x, yAvg, colorSet, labelSet, "files/avgCaseScattered.png")
