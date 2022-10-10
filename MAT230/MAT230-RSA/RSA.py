## Dante Trisciuzzi
# 4.18.2022
# SNHU MAT-230-J4332

class rsa_keyset:
    p: int
    q: int
    e: int
    pub: int
    pvt: int
    def __init__(self, p, q, e):
        self.p = p
        self.q = q
        self.e = e
        self.pub = get_pub_key(p, q)
        self.pvt = create_private_key(p, q, e)


def get_pub_key(p, q):
    return (p*q)


def create_private_key(p, q, e):
    phi = (p-1) * (q-1)
    for i in range(e):
        j = 1 + i * (phi //e)
        if(j * e) % phi == 1:
            return i
        
        
def reverse_private_key( e, pub):
    factors = get_prime_factorization(pub)
    phi = (factors[0]-1) * (factors[1]-1)
    for i in range(e):
        j = 1 + i * (phi //e)
        if(j * e) % phi == 1:
            return i


def get_prime_factorization(num : int):
    x = 2
    factors = []
    while x * x <= num:
        if num % x:
            x += 1
        else:
            num //= x
            factors.append(x)
    if num > 1:
        factors.append(num)
    return factors


def make_ciphertext( plainvalue, keys : rsa_keyset) -> int:
    return pow(plainvalue, keys.e) % keys.pub


def make_plaintext( ciphertext, keys : rsa_keyset) -> int:
    return pow( ciphertext, keys.pvt) % keys.pub


def encrypt_string(keys : rsa_keyset, input : str , lookup : dict) -> str:
    out = ""
    for c in input.upper():
        out += "{:02} ".format(make_ciphertext(int(lookup[c]), keys))
    return out.removesuffix(" ")


def decrypt_string(keys : rsa_keyset, input : str , lookup : dict) -> str:
    out = ""
    for i in input.split(' '):
        out += lookup["{:02}".format(make_plaintext(int(i), keys))]
    return out


def generate_cipher_lookup() -> dict:
    chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ .,!?'
    d = {}

    for i  in range(1, 32):
        d[chars[i-1]] = "{:02}".format(i)
        d["{:02}".format(i)] = chars[i-1]
    return d
        

if __name__ == "__main__":
    lookup = generate_cipher_lookup()
    keys = rsa_keyset(3, 11, 3)
    encrypted = encrypt_string(keys, "Hello World!", lookup)
    print(encrypted)
    print(decrypt_string(keys, encrypted, lookup))
