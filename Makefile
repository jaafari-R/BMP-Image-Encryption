compile:
	g++ main.cpp bmp_crypto.cpp -lcrypto++ -o a.out

encryption_test:
	./a.out e test.bmp outtest.bmp