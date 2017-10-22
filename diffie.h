// 			DIFFIE-HELLMEN IS A PROCEDURE FOR KEY EXCHANGE IN THE CRPTYOGRAPHY

	
//						ALICE						BOB
//			Public Keys Avail = P & G					Public Keys Avail = P & G
// 			Private keys for Alice = a					Private keys avail for bob = b
//			keygen = x = G^a mod P						keygen = y = G^b mod P

// 						EXCHANGE WILL TAKE PLACE
//			Key received = y						Key received = x
// 			Generated secret key = ka = y^a mod P				Generated secret key = kb = x^b mod P
// 			In the process G is the primitive root of P

// 			Now BOB and ALICE can use the key exchanged for the encryption and decryption process


/*
Step 1: Alice and Bob get public numbers P = 23, G = 9

Step 2: Alice selected a private key a = 4 and
        Bob selected a private key b = 3

Step 3: Alice and Bob compute public values
Alice	:    x = (9^4 mod 23) = (6561 mod 23) = 6
Bob	:    y = (9^3 mod 23) = (729 mod 23)  = 16

Step 4: Alice and Bob exchange public numbers

Step 5: Alice receives public key y =16 and
        Bob receives public key x = 6

Step 6: Alice and Bob compute symmetric keys
        Alice:  ka = y^a mod p = 65536 mod 23 = 9
        Bob:    kb = x^b mod p = 216 mod 23 = 9

Step 7: 9 is the shared secret.
*/

#include<math.h>
#include<stdio.h>

typedef long long int ll;

ll power(ll a, ll b, ll p ) {

	if (b == 1)
		return a;
	else
		return (((ll)pow(a,b))%p);
}
