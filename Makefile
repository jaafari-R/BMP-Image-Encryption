compile:
	g++ main.cpp bmp_crypto.cpp -lcrypto++ -o a.out -W

encryption_test:
	./a.out e test.bmp outtest.bmp

decryption_test:
	./a.out d outtest.bmp decouttest.bmp 