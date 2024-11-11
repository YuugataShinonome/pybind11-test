import test_module

a = test_module.add(1,2)
print(a)
b = test_module.accmulate_integers(list(range(10000)), 8)
print(f'The answer of my lib is {b}, and the result from std lib is {sum(range(1000))}')