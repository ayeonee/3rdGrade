from fuzzy_system.fuzzy_set import FuzzySet
import matplotlib.pyplot as plt

class FuzzyVariable():
	def __init__(self, name, min_val, max_val, res):
		self._sets={}
		self._max_val = max_val
		self._min_val = min_val
		self._res = res
		self._name = name

	def __str__(self):
		return ', '.join(self._sets.keys())

	@property
	def name(self):
		return self._name

	def _add_set(self, name, f_set):
		self._sets[name] = f_set

	def get_set(self, name):
		return self._sets[name]

	def add_triangular(self, name, low, mid, high):
		new_set = FuzzySet.create_triangular(name, self._min_val, self._max_val, self._res, low, mid, high)
		self._add_set(name, new_set)
		return new_set

	def add_trapezoidal(self, name, a, b, c, d):
		new_set = FuzzySet. create_trapezoidal(name, self._min_val, self._max_val, self._res, a, b, c, d)
		self._add_set(name, new_set)
		return new_set

	def plot_variable(self, ax=None, show=True):
		if ax == None:
			ax = plt.subplot(111)

		for n ,s in self._sets.items():
			ax.plot(s.domain_elements(), s.dom_elements(), label=n)

		# Shrink current axis by 20%
		pos = ax.get_position()
		ax.set_position([pos.x0, pos.y0, pos.width * 0.8, pos.height])
		ax.grid(True, which='both', alpha=0.4)
		ax.set_title(self._name)
		ax.set(xlabel='x', ylabel='$\mu (x)$')

		# Put a legend to the right of the current axis
		ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))

		if show:
			plt.show()