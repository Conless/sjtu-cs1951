from cyaron import *
from numpy import *

test_data = IO("1895.in")

n = int(10)
m = int(20)
s = randint(int(n / 2), n)
test_data.input_writeln(n, s, m)

a = [x for x in range(1, n + 1)]
random.shuffle(a)
test_data.input_writeln(a[0:s])

graph = Graph.graph(n, m, directed=False, weight_limit=(
    5, 20), self_loop=False, repeated_edges=False)
test_data.input_writeln(graph)

q = 20
test_data.input_writeln(q)
for i in range(0, q):
    test_data.input_writeln(a[randint(0, s - 1)], a[randint(0, s - 1)], randint(10, 20))
