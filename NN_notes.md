# Neural network notes

- Chapter 1 handwritten numeral recognition

Large number of training examples -> inference of rules

- types of artificial neuron
  - perceptron (weighted sum)
  - sigmoid neuron (squish formula)

- main learning algorithm = stochastic decent

## Perceptron

- takes in several binary inputs and outputs their weighted sum
- ∑wx should be greater or equal than a threshold
  - If it is greater than or equal to the threshold, it outputs one, otherwise it outputs zero
- Many layers of perceptrons together can form more complicated decision-making machines.
- Simple definition
  - 0 if ```w * x + b <= 0```
  - 1 if ```w * x + b > 0```
  - B = bias, or -threshold
  - bias is how easy it is to get the perceptron to fire
    - perceptron can simuloate any logical gate using different weights and biases

## Sigmoid neurons

- we want a small change in weights to lead to a small change in output
- sigmoid neuron compresses the output of a perceptron so it is between 0-1 (sort of a normalization thing)
- Nowadays ReLU or CReLU is used in Stockfish and similar engines but sigmoid was the first "squisher" to be invented
