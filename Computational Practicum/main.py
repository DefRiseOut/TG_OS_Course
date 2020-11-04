from PyQt5 import QtWidgets
from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg
import sys
from design import UiMainWindow
import os

# Equation: y'= 3y^(2/3)
# Solution: y = (x + C)^3


# -------------------------------------------------

class Equation:
    C = 0
    step = 1

    def __init__(self, x0, y0, step):
        if y0 > 0:
            self.C = y0 ** (1./3.) - x0
        elif y0 == 0:
            self.C = - x0

    @staticmethod
    def y_derivative(x, y):
        return 3 * y ** (2 / 3)

    def y(self, x):
        return (x + self.C) ** 3


def round_to_3(x):
    return round(x * 1000) / 1000


class Method:
    x0 = 0
    y0 = 0
    X = 1
    N = 1
    step = 1

    def __init__(self, x0, y0, X, N):
        self.x0 = x0
        self.y0 = y0
        self.X = X
        self.N = N
        self.step = (X - x0) / N
        self.function = Equation(x0, y0, self.step)

    def next_yi(self, xi, yi):
        return yi

    def range_n(self, n):
        return [(self.X - self.x0)*i/n+self.x0 for i in range(n)]

    def exact(self):
        x_values = self.range_n(100) + [self.X]
        yi = self.y0
        exact_values = [yi]
        for xi in self.range_n(100):
            exact_values += [self.function.y(xi + (self.X-self.x0)/100)]
        x_values2 = [self.x0 + j * self.step for j in range(self.N)] + [self.X]
        return x_values, exact_values, x_values2

    def local_error(self, xi):
        yi = self.function.y(xi)
        return self.function.y(xi+self.step) - self.next_yi(xi, yi)

    def approximate_error(self):
        approx = []
        local_errors = []
        yi = self.y0
        approx += [yi]

        for xi in self.range_n(self.N):
            yi = self.next_yi(xi, yi)
            approx += [yi]

            local_errors += [self.local_error(xi)]

        total_error = self.function.y(self.X) - approx[-1]

        return approx, local_errors, total_error


class EulerMethod(Method):

    def __init__(self, x0, y0, X, N):
        super().__init__(x0, y0, X, N)
        self.x0 = x0
        self.y0 = y0
        self.X = X
        self.N = N
        self.step = (X - x0) / N
        self.funct = Equation(x0, y0, self.step)

    def next_yi(self, xi, yi):
        return yi + self.step * self.funct.y_derivative(xi, yi)


class ImprovedEulerMethod(Method):
    def __init__(self, x0, y0, X, N):
        super().__init__(x0, y0, X, N)
        self.x0 = x0
        self.y0 = y0
        self.X = X
        self.N = N
        self.step = (X - x0) / N
        self.funct = Equation(x0, y0, self.step)

    def next_yi(self, xi, yi):
        yi_1 = yi + self.step * self.funct.y_derivative(xi, yi)
        return yi + (self.step / 2) * (self.funct.y_derivative(xi, yi) + self.funct.y_derivative(xi + self.step, yi_1))


class RungeKuttaMethod(Method):
    def __init__(self, x0, y0, X, N):
        super().__init__(x0, y0, X, N)
        self.x0 = x0
        self.y0 = y0
        self.X = X
        self.N = N
        self.step = (X - x0) / N
        self.function = Equation(x0, y0, self.step)

    def next_yi(self, xi, yi):
        k1_i = self.function.y_derivative(xi, yi)
        k2_i = self.function.y_derivative(xi + self.step / 2, yi + self.step / 2 * k1_i)
        k3_i = self.function.y_derivative(xi + self.step / 2, yi + self.step / 2 * k2_i)
        k4_i = self.function.y_derivative(xi + self.step, yi + self.step * k3_i)
        return yi + self.step / 6 * (k1_i + 2 * k2_i + 2 * k3_i + k4_i)


def methods_n_range(x0, y0, X, n_start, n_end):
    errors_1 = []
    errors_2 = []
    errors_3 = []
    for N in range(n_start, n_end+1):
        euler = EulerMethod(x0, y0, X, N)
        improved_euler = ImprovedEulerMethod(x0, y0, X, N)
        runge_kutta = RungeKuttaMethod(x0, y0, X, N)
        temp1, temp2, error1 = euler.approximate_error()
        temp1, temp2, error2 = improved_euler.approximate_error()
        temp1, temp2, error3 = runge_kutta.approximate_error()
        errors_1 += [error1]
        errors_2 += [error2]
        errors_3 += [error3]
    n_range = range(n_start, n_end+1)
    return n_range, errors_1, errors_2, errors_3


class MainWindow(UiMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setupUi(self)

        self.eulerMethod = EulerMethod(2, 1, 10, 100)
        self.improvedEulerMethod = ImprovedEulerMethod(2, 1, 10, 100)
        self.rungeKuttaMethod = RungeKuttaMethod(2, 1, 10, 100)

        self.setup()

    def setup(self):
        self.x0Input.textChanged.connect(lambda: self.update_plots())
        self.y0Input.textChanged.connect(lambda: self.update_plots())
        self.Xinput.textChanged.connect(lambda: self.update_plots())
        self.NInput.textChanged.connect(lambda: self.update_plots())
        self.NstartInput.textChanged.connect(lambda: self.update_plots())
        self.NendInput.textChanged.connect(lambda: self.update_plots())
        self.checkBox.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_2.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_3.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_4.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_5.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_6.stateChanged.connect(lambda: self.update_plots())
        self.checkBox_7.stateChanged.connect(lambda: self.update_plots())
        self.update_plots()

    def update_plots(self):
        self.graphwidget.clear()
        self.graphwidget_2.clear()
        self.graphwidget_3.clear()

        x0 = float(self.x0Input.text())
        y0 = float(self.y0Input.text())
        X = float(self.Xinput.text())
        N = round(int(self.NInput.text()))
        N_start = round(int(self.NstartInput.text()))
        N_end = round(int(self.NendInput.text()))

        if x0 == X:
            return None
        if N == 0:
            return None
        if N_start > N_end:
            return None
        if N_start <= 0:
            return None
        if y0 < 0:
            return None

        self.eulerMethod = EulerMethod(x0, y0, X, N)
        self.improvedEulerMethod = ImprovedEulerMethod(x0, y0, X, N)
        self.rungeKuttaMethod = RungeKuttaMethod(x0, y0, X, N)

        x_values, exact_values, x_values2 = self.eulerMethod.exact()
        for i in x_values: print(i)
        print(len(x_values))
        if self.checkBox.checkState():
            pen = pg.mkPen(color=(255, 255, 255))
            self.graphwidget.plot(x_values, exact_values, pen=pen, name="Exact Solution")

        if self.checkBox_2.checkState():
            approx_2, local_2, total_2 = self.eulerMethod.approximate_error()
            pen = pg.mkPen(color=(0, 0, 255))
            self.graphwidget.plot(x_values2, approx_2, pen=pen, name="Euler's method")
            self.graphwidget_2.plot(x_values2[:N], local_2, pen=pen, name="Euler's method")

        if self.checkBox_3.checkState():
            approx_3, local_3, total_3 = self.improvedEulerMethod.approximate_error()
            pen = pg.mkPen(color=(255, 0, 0))
            self.graphwidget.plot(x_values2, approx_3, pen=pen, name="Improved Euler's method")
            self.graphwidget_2.plot(x_values2[:N], local_3, pen=pen, name="Improved Euler's method")

        if self.checkBox_4.checkState():
            approx_4, local_4, total_4 = self.rungeKuttaMethod.approximate_error()
            pen = pg.mkPen(color=(0, 255, 0))
            self.graphwidget.plot(x_values2, approx_4, pen=pen, name="Runge-Kutta method")
            self.graphwidget_2.plot(x_values2[:N], local_4, pen=pen, name="Runge-Kutta method")

        n_range, errors1, errors2, errors3 = methods_n_range(x0, y0, X, N_start, N_end)

        if self.checkBox_5.checkState():
            pen = pg.mkPen(color=(0, 0, 255))
            self.graphwidget_3.plot(n_range, errors1, pen=pen, name="Euler's method")

        if self.checkBox_7.checkState():
            pen = pg.mkPen(color=(255, 0, 0))
            self.graphwidget_3.plot(n_range, errors2, pen=pen, name="Improved Euler's method")

        if self.checkBox_6.checkState():
            pen = pg.mkPen(color=(0, 255, 0))
            self.graphwidget_3.plot(n_range, errors3, pen=pen, name="Runge-Kutta method")


def main():
    app = QtWidgets.QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
