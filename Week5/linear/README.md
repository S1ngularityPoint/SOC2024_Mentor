# Linear Regression
- Given a dataset $D = \{X,Y\}$, where $X \in \mathbb{R}^{n\times d}$ and $Y \in \mathbb{R}^{n}$ with $(X_{i},Y_{i})$ representing the $i^{th}$ datapoint in the dataset, linear regression aims to find a _linear_ relation between the elements of the pair $(X_{i},Y_{i})$ $\forall i \in [0,n - 1]$
- Each datapoint consists of an input vector or feature vector $X_{i}$ which is a $d-$dimensional vector ie, $X_{i} \in \mathbb{R}^{d}$ and a scalar value or label $Y_{i}$.
- The goal of linear regression is to find a linear function $f$ and a constant term $b$ that for every pair $(\vec{x_{i}},y_{i}) \in (X,Y)$, best approximates $y_{i} \text{ as } f(\vec{x_i}) + b$.
- The function $f$ can also be denoted as a $d-$dimensional vector $\vec{w}$ so the goal is to "learn" the values of $w_{1},w_{2},\dots w_{d}$ and $b$ that give the best possible results.

# How do we define Results?

- As seen in the previous section, our goal is get the best possible results/approximations for the dataset that is given. A natur
# Geometric Representation
- The equation of a  hyperplane with unit normal vector $\vec{w}$ and distance from origin $b$ is given by 
$$ \vec{w}\cdot\vec{x} = b $$
- Now the goal of regression is to find the equation