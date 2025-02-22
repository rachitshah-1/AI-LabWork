import numpy as np

class Neuron:
    def __init__(self, num_weights):
        np.random.seed(4)
        self.weights = np.random.randn(num_weights) * 0.01  # Small random values

    def getOutput(self, inputs):
        newInputs = np.array([1] + inputs)  # Add bias term
        return 1 if np.dot(self.weights, newInputs) > 0 else 0

    def train(self, inputs, outputs, alpha=0.1, max_iterations=1000):
        for _ in range(max_iterations):
            solved = True
            for ipt, opt in zip(inputs, outputs):
                result = self.getOutput(ipt)
                if result != opt:
                    res = opt - result
                    self.weights += alpha * res * np.array([1] + ipt)
                    solved = False
            if solved:
                break  # Stop if converged

# Example: AND gate (works)
and_inputs = [[1, 0], [0, 1], [1, 1], [0, 0]]
and_outputs = [0, 0, 1, 0]
neuron = Neuron(3)
neuron.train(and_inputs, and_outputs)

print("AND Gate Results:")
for ipt in and_inputs:
    print(f"Input: {ipt}, Output: {neuron.getOutput(ipt)}")

# Example: XOR gate (fails with perceptron)
xor_inputs = [[1, 0], [0, 1], [1, 1], [0, 0]]
xor_outputs = [1, 1, 0, 0]
neuron = Neuron(3)
neuron.train(xor_inputs, xor_outputs)

print("\nXOR Gate Results (Expected to Fail):")
for ipt in xor_inputs:
    print(f"Input: {ipt}, Output: {neuron.getOutput(ipt)}")  # Incorrect results expected
