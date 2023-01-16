import time
import contextlib


def read_input(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        return f.read()


@contextlib.contextmanager
def time_it():
    t = time.perf_counter()
    yield
    print(f'Cost: {(time.perf_counter() - t) * 1000:.4f}ms')
