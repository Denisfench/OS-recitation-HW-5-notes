# This is a sample Python script.

# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.

import bcrypt
import time

password = b'mySecretPassword'

salt = bcrypt.gensalt()
hashed = bcrypt.hashpw(password, salt)

print("original password:", password)
print("salt ", salt)
print("hashed password ", hashed)

if bcrypt.checkpw(password, hashed):
    print("match")
else:
    print("does not match")


# introducing the work factor

start = time.time()
# we have a customizable parameter 'rounds' denoting the number of iterations
# performed by the hash function, thus raising the cost
salt = bcrypt.gensalt(rounds=16)
hashed = bcrypt.hashpw(password, salt)
end = time.time()

print("the hashing with 16 rounds took took ", end - start)

print(hashed)
