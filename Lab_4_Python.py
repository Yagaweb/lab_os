import time


def app():
    a = 0
    b = 3
    c = 3
    for i in range(0, 100000000):
        a += b * 2 + c - i


if __name__ == "__main__":
    start = time.perf_counter()
    app()
    print(f"command took {time.perf_counter() - start : .5f} s")