import random
numbers = [random.randint(1, 50) for _ in range(40)]
def lambda_func_1(x):
	return x * x
	
numbers = list(map(lambda_func_1, numbers))
print(True)
def lambda_func_2(x):
	ns = [random.randint(1, 50) for _ in range(40)]
	def lambda_func_3(x):
		return x - 1
		
	ns = list(map(lambda_func_3, ns ))
	x += 1
	x *= x
	return x
	
numbers = list(map(lambda_func_2, numbers))
print(True)

