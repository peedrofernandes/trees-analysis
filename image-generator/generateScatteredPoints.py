import matplotlib.pyplot as plt


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


def extractDataFromFile(files: dict):
  # Read first line
  for file in files.values():
    file.readline()

  # Worst-case set of data for each tree
  worstCaseLines = [[file.readline() for _ in range(0, 1000)] for file in files.values()]

  # Discard another line ("AVG CASE")
  for file in files.values():
    file.readline()

  # Average case set of data for each tree
  avgCaseLines = [[file.readline() for _ in range(0, 1000)] for file in files.values()]

  data = [[[int(worst.split()[1]), float(avg.split()[1])] for worst, avg in zip(worstLines, avgLines)] for worstLines, avgLines in zip(worstCaseLines, avgCaseLines)]

  return data


avlFile = open("files/avl.txt", "r")
b1File = open("files/b1.txt", "r")
b5File = open("files/b5.txt", "r")
b10File = open("files/b10.txt", "r")
rbFile = open("files/rubroNegra.txt", "r")

files = {
  "avl": avlFile,
  "b1": b1File,
  "b5": b5File,
  "b10": b10File,
  "rb": rbFile
}

data = extractDataFromFile(files)
yWorst = [[y[0] for y in di] for di in data]
yAvg = [[y[1] for y in di] for di in data]
colorSet = ["blue", "magenta", "green", "black", "red"]
labelSet = ["Avl Tree", "B-tree dg.1", "B-tree dg.5", "B-tree dg.10", "Red-black tree"]

x = [i for i in range(1, 1001)]

# Pior caso
generate_scatter(x, yWorst, colorSet, labelSet, "files/worstCaseScattered.png")

# Caso médio
generate_scatter(x, yAvg, colorSet, labelSet, "files/avgCaseScattered.png")
