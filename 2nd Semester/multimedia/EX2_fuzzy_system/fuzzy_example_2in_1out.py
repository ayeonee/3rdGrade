from fuzzy_system.fuzzy_variable_output import FuzzyOutputVariable
from fuzzy_system.fuzzy_variable_input import FuzzyInputVariable
from fuzzy_system.fuzzy_systemp import FuzzySystem

x = FuzzyInputVariable('x', 0, 100, 100)
x.add_trapezoidal('A1', 0, 0, 30, 40)
x.add_triangular('A2', 32, 47, 62)
x.add_trapezoidal('A3', 55, 65, 100, 100)

y = FuzzyInputVariable('y', 0, 100, 100)
y.add_trapezoidal('B1', 0, 0, 42, 62)
y.add_trapezoidal('B2', 46, 66, 100, 100)

z = FuzzyOutputVariable('z', 0, 100, 100)
z.add_triangular('C1', 0, 0, 50)
z.add_triangular('C2', 10, 50, 90)
z.add_triangular('C3', 50, 100, 100)

system = FuzzySystem()
system.add_input_variable(x)
system.add_input_variable(y)
system.add_output_variable(z)

system.add_rule(
		{ 'x':'A3',
			'y':'B1' },
		{ 'z':'C1'})

system.add_rule(
		{ 'x':'A2',
			'y':'B2' },
		{ 'z':'C2'})

system.add_rule(
		{ 'x':'A1' },
		{ 'z':'C3'})


output = system.evaluate_output({
				'x':35,
				'y':60
		})

print(output)
#print('fuzzification\n-------------\n', info['fuzzification'])
# print('rules\n-----\n', info['rules'])

system.plot_system()