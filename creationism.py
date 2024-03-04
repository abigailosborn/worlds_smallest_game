def sum_string(string):
    return sum([ord(c) for c in string])

while True:
    password = input('Please enter your password: ')
    if sum_string(password) >= 3000:
        print('Estamos en')
        break
    else:
        print('Intentar nueva')
