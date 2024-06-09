import random
import os

# Function to generate a single test case file
def generate_testcase(file_number, n):
    # Randomly choose the size of the array between 1 and 10^9    
    # Open a new file to write the test case
    with open(f'{file_number}.in', 'w') as f:
        # Write the size of the array
        f.write(f"{n}\n")
        
        # Generate the array with random integers between 1 and 10^9
        array = [str(random.randint(1, 10**9)) for _ in range(n)]
        
        # Write the array to the file
        f.write(' '.join(array))

# Create a directory to store test case files
os.makedirs('tests_subsets', exist_ok=True)

# Change the working directory to 'testcases'
os.chdir('tests_subsets')

# Generate 10 test case files
for i in range(1,9):
    generate_testcase(i,10**(i//2))

print("Test cases generated successfully.")
