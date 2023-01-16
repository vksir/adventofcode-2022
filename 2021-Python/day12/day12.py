import copy
import queue
from typing import List

from pydantic import BaseModel


EXAMPLE_DATA = """start-A
start-b
A-c
A-b
b-d
A-end
b-end"""
EXAMPLE_DATA2 = """dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc"""
EXAMPLE_DATA3 = """fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW"""


class Node(BaseModel):
    value: str
    father: 'Node' = None
    visited_small_holes = set()
    is_visited_twice = False


Node.update_forward_refs()


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = EXAMPLE_DATA
    # data = EXAMPLE_DATA2
    # data = EXAMPLE_DATA3

    mapping = {}
    for line in data.splitlines():
        a, b = line.split('-')
        mapping.setdefault(a, set())
        mapping[a].add(b)
        mapping.setdefault(b, set())
        mapping[b].add(a)

    que = queue.Queue()
    que.put(Node(value='start'))
    ways = []
    while not que.empty():
        node = que.get()
        next_node_values = mapping[node.value]
        for next_node_value in next_node_values:
            if next_node_value == 'start':
                continue
            next_node = Node(value=next_node_value, father=node,
                             visited_small_holes=copy.copy(node.visited_small_holes),
                             is_visited_twice=node.is_visited_twice)
            if next_node_value == 'end':
                ways.append(next_node)
                continue
            if next_node_value.islower():
                if next_node_value not in next_node.visited_small_holes:
                    next_node.visited_small_holes.add(next_node_value)
                else:
                    if not next_node.is_visited_twice:
                        next_node.is_visited_twice = True
                    else:
                        continue
            que.put(next_node)
    for way in ways:
        path = [way]
        while way.father:
            way = way.father
            path.append(way)
        path = '-'.join(node.value for node in reversed(path))
        print(path)
    print(len(ways))


if __name__ == '__main__':
    main()
