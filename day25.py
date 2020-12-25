def secret(pub1, pub2):
    loop, key = 0, 1
    while key != pub1 and key != pub2:
        key = (key * 7) % 20201227
        loop += 1
    key, subj = 1, pub2 if key == pub1 else pub1
    for _ in range(loop):
        key = (key * subj) % 20201227
    print(key)

secret(15113849, 4206373)
