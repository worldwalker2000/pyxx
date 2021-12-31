import random
numbers = [random.randint(1, 50) for _ in range(40)]
def lambda_func_1(x):
	return x * x
	
numbers = list(map(lambda_func_1, numbers))
print(True)
def lambda_func_2(x):
	x += 1
	x *= x
	return x
	
numbers = list(map(lambda_func_2, numbers))
print(True)

