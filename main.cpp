#include <iostream>
#include <vector>
#include <string>
using namespace std; 

void ksa(const string& key, vector<int>& s)
{
	s.resize(256); // S array
	vector<int> k(256); // K array

	for (int i = 0; i < 256; i++)
	{
		s[i] = i; 
	}
	
	for (int i = 0; i < 256; i++)
	{
		k[i] = key[i % key.size()];  //repeat key to fill K array
	}

	int j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + s[i] + k[i]) % 256; 
		swap(s[i], s[j]);
	}
}

string rc4_process(const string& message, vector<int>& s)
{
	int i{ 0 }, j{ 0 };
	string output = ""; 

	// loop over message bytes
	for (int n = 0; n < message.size(); n++) {
		
		// PRGA
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		swap(s[i], s[j]); 
		int t = (s[i] + s[j]) % 256;
		int keystream_byte = s[t];
		
		char cipher_byte = message[n] ^ keystream_byte; // XOR
		output += cipher_byte;
	}

	return output;
}

int main()
{
	vector<int> s;
	string key = "cryptographyyughfg is fun!";
	ksa(key, s);
	
	//encrypt
	string plaintext = "Hello, World!"; 
	string ciphertext = rc4_process(plaintext, s); 
	cout << "Plaintext: " << plaintext << endl;
	cout << "Ciphertext: " << ciphertext << endl;

	//decrypt
	vector<int> s2;
	ksa(key, s2); // reinitialize S array with the same key, without this step decryption will fail

	string decryptedtext = rc4_process(ciphertext, s2); 
	cout << "Decrypted text: " << decryptedtext << endl;


	system("PAUSE"); 
	return 0; 
}