import numpy as np
import matplotlib.pyplot as plt
from generateScatteredPoints import yWorst, yAvg, x, labelSet, colorSet
from math import log, exp
from decimal import Decimal

def poly_regression(x, y, k = 1):
  n = len(x)

  A = [[0 for _ in range(k+1)] for _ in range(k+1)]
  B = []

  for i in range(k + 1):
    for j in range(k + 1):
      A[i][j] = (sum(xi ** (i + j) for xi in x)) if (i + j > 0) else (n)

    B.append((sum(yi * xi ** i for xi, yi in zip(x, y))) if (i > 0) else (sum(y)))

  return np.linalg.solve(A, B)


def build_poly(coeffs):
  def p(x):
    return sum((ci*x**i if (i > 0) else (ci)) for i, ci in enumerate(coeffs))
  return p


# def generate_regression(x, y, p, colorSet, labelSet, path):
#   plt.clf()
#   t = np.linspace(min(x), max(x), 200)
#   pt = [p(ti) for ti in t]

#   plt.scatter(x, y)
#   plt.plot(t, pt, color)
#   plt.savefig(path)

def generate_regressions(functions, colorSet, labelSet, path):
  plt.clf()
  d = np.linspace(1, 1000, 200)
  
  for i, fi in enumerate(functions):
    fd = [fi(di) for di in d]
    plt.plot(d, fd, colorSet[i], label=labelSet[i])
  
  plt.legend(loc='upper right', scatterpoints=1, markerscale=8)
  plt.savefig(path)


def build_f(a, b):
  def f(x):
    return a * log(x) + b
  return f

X = [log(xi) for xi in x]
worstCaseCoeffs = [poly_regression(X, yi) for yi in yWorst]
avgCaseCoeffs = [poly_regression(X, yi) for yi in yAvg]
worstCaseFunctions = [build_f(a, b) for a, b in worstCaseCoeffs]
avgCaseFunctions = [build_f(a, b) for a, b in avgCaseCoeffs]

generate_regressions(worstCaseFunctions, colorSet, labelSet, "files/worstCaseFunctions.png")
generate_regressions(avgCaseFunctions, colorSet, labelSet, "files/avgCaseFunctions.png")
