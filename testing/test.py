import random

computer = random.randint(1, 10)
user = -1
while user != computer :
	user = int(input("Enter a number: "))
	if user < computer :
		print("Too low")
	else :
		print("Too high")

