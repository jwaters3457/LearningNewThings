import matplotlib.pyplot as plt
import numpy as np

defaultRange = int(100)

def drawParametric(xEquation, yEquation):
    return

def drawPolynomial(CoefficientList, PolyList):
    if len(CoefficientList) != len(PolyList):
        warnings.warn("drawPolynomial Failed. Coefficient list length must match Polynomial list")
        return
    x = np.array(range(defaultRange))
    y = 0

    for i, Coefficient in enumerate(CoefficientList):
        y += Coefficient * x ** PolyList[i]
        
    plt.plot(x,y)
    plt.show()
    return




       
if __name__ == "__main__":
    drawPolynomial([2,2,2],[2,1,0])
