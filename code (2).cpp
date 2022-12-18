#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
using std::string;
using std::ifstream; 
using std::endl;
using std::vector;
static const vector<string> hexat ={"20","30","31","32","33","34","35","36","37","38","39","41",
"42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F","50","51","52","53","54",
"55","56","57","58","59","5A","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D",
"6E","6F","70","71","72","73","74","75","76","77","78","79","7A"};
static const vector<char> ASCII={' ','0','1','2','3','4','5','6','7','8','9','A','B','C','D',
'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a',
'b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
'y','z'};
class Facteur{
    string nomf;
    int zonef;
    public:
        Facteur(string nf, int nz){
            nomf=nf;
            zonef=nz;
        }
         Facteur(){}
        void setNomf(string nf){
            nomf=nf;
        }
        string getNomf(){
            return(nomf);
        }
         void setZonef(int nz){
            zonef=nz;
        }
        int getZonef(){
            return(zonef);
        }
};
class Habitant{
    string nomh;
    int zoneh;
    public:
      Habitant(string n, int nz){
        nomh=n;
        zoneh=nz;
      }
      Habitant(){}
      void setNomh(string n){
            nomh=n;
        }
        string getNomh(){
            return(nomh);
        }
        void setZoneh(int nz){
            zoneh=nz;
        }
        int getZoneh(){
            return(zoneh);
        }

};
class Recommande{
    int numf;
    int numh;
	string type;
    /*Facteur facteur;
    Habitant destinataire;*/
    public:
        /*Recommande(string nf, int ntf, string nh, int nth, string nz){
            facteur=Facteur(nf,ntf,nz);
            destinataire=Habitant(nh,nth,nz);
        }*/
        Recommande(int nf,int nh,string t){
            numf=nf;
            numh=nh;
			type=t;
        }
        Recommande(){}
       void setNumf(int nf){
        numf=nf;
       }
       int getNumf(){
        return(numf);
       }
       void setNumh(int nh){
        numh=nh;
       }
       int getNumh(){
        return(numh);
       }
	    void setType(string t){
        type=t;
       }
       string getType(){
        return(type);
       }
};
//
void keygeneration(string key, vector<string> &rkb,vector<string> &rk);
string tohexa(string s);
string toASCII(string s);
int nbrline(string file);
bool existe(string file, string mot);
void addF(string nf, string nz);
void addH(string nh, string nz);
void addR(string nf,string nh,string t);
bool data_existe();
void create_data(string k);
string hex2bin(string s);
string bin2hex(string s);
string permute(string k, int* arr, int n);
string shift_left(string k, int shifts);
string xor_(string a, string b);
string encrypt(string pt, vector<string> rkb,vector<string> rk);
string decrypt(string cipher,vector<string> rkb,vector<string> rk);
string DES(string key,string s);
string base64bits(string s);
int ifaddR(int nf,int nh);
void readH(vector<Habitant>&h,vector<string> rkb,vector<string> rk);
void readR(vector<Recommande>&r,vector<string> rkb,vector<string> rk);
void readF(vector<Facteur>&f,vector<string> rkb,vector<string> rk);
//main
int main(){
    vector<string> rkb; // rkb for RoundKeys in binary
	vector<string> rk; // rk for RoundKeys in hexadecimal
    bool ex_data=data_existe();
    string key;
    if (ex_data==false){
        cout<<"create a key for the new data"<<endl;
        cin>>key;
		string k=tohexa(key);
		key=base64bits(k);
        keygeneration(key,rkb,rk);
		string enc_key=encrypt(key,rkb,rk);
		cout<<"enc_key"<<enc_key;
		create_data(enc_key);
    }
	else
	{ string vkey,k;	
		ifstream f("Recommande.txt");
		getline(f,vkey);
		//autentifycation
			cout<<"enter the key:"<<endl;
			cin>>key;
			k=tohexa(key);
			key=base64bits(k);
            keygeneration(key,rkb,rk);
		    string enc_key=encrypt(key,rkb,rk);
		while (enc_key!=vkey)
		{
			cout<<"enter the key:"<<endl;
			cin>>key;
			k=tohexa(key);
			key=base64bits(k);
            keygeneration(key,rkb,rk);
		    string enc_key=encrypt(key,rkb,rk);
			
		}
		
		
	}
	
    
    cout<<"chose the action that you wanna do:\n"
    <<"delete data (d)\n"
    <<"add data (a)\n"
    <<"read data (r)\n";
    char choix;
    cin>>choix;
    while((choix!='a')&&(choix!='d')&&(choix!='r')){
        cout<<"entre a valide choice: delete data (d) add data (a) read data (r)\n";
        cin>>choix;
    }
    if (choix=='a')
    {    char ac;
        cout<<"to add:\n facteur(f) habitant(h) recommande(r)\n";
        cin>>ac;
        while((ac!='f')&&(ac!='h')&&(ac!='r')){
            cout<<"entre a valide choice to add: facteur(f) habitant(h) recommande(r)\n";
            cin>>ac;
         }
        if(ac=='f'){
            string nf;
            int nz;
            cout<<"entre the name of the facteur\n";
            cin>>nf;
            cout<<"entre the zone num of the facteur\n";
            cin>>nz;
            nf=encrypt(nf,rkb,rk);
            string nzs=to_string(nz);
            nzs=encrypt(nzs,rkb,rk);
            addF(nf,nzs);
        }
        else{
        if(ac=='h'){
            string nh;
            int nz;
            cout<<"entre the name of habitant\n";
            cin>>nh;
            cout<<"entre the zone num of habitant\n";
            cin>>nz;
            nh=encrypt(nh,rkb,rk);
            string nzs=to_string(nz);
            nzs=encrypt(nzs,rkb,rk);
            addH(nh,nzs);
        }
        else{
            int nh;
            int nf;
            cout<<"entre facteur num of Habitant\n";
            cin>>nh;
            cout<<"entre habitant num of Facteur\n";
            cin>>nf;
            int e= ifaddR(nf,nh);
            if(e==0){
                string type;
                cout<<"type of recommande:(l)lettre (c)coli \n";
                cin>>type;
                while ((type!="l")&&(type!="c"))
                {
                    cout<<"entre a valide type: (l)lettre (c)coli\n";
                    cin>>type;
                }
                string nhs=to_string(nh);
                string nfs=to_string(nf);
                nhs=encrypt(nhs,rkb,rk);
                nfs=encrypt(nfs,rkb,rk);
                type=encrypt(type,rkb,rk);
                addR(nfs,nhs,type);

            }
            else{
                if (e==1)
                {
                    cout<<"facteur doesn't exist\n";
                }else{
                    if (e==2)
                    {
                        cout<<"habitant doesn't exist\n";
                    }
                    else
                    {
                        cout<<"facteur and habitant aren't in the same zone\n";
                    }
                    
                    
                }
            }
            
        }
        }
    }
    if(choix=='r'){
        char c;
        cout<<"to read: facteur table(f) habirant table(h) recommande table(r)"<<endl;
        cin>>c;
        while((c!='f')&&(c!='h')&&(c!='r')){
            cout<<"to read: facteur table(f) habirant table(h) recommande table(r)"<<endl;
            cin>>c;
         }
        if (c=='f')
        { vector <Facteur>facteurs;
            readF(facteurs,rkb,rk);
            for (int i = 0; i < facteurs.size(); i++)
            {
                cout<<"facteur: "<<facteurs[i].getNomf()<<" zone: "<<facteurs[i].getZonef()<<endl;
                
            }
            
        }
        if (c=='h')
        {   vector <Habitant>habitants;
            readH(habitants,rkb,rk);
            for (int i = 0; i < habitants.size(); i++)
            {
                cout<<" habitant: "<<habitants[i].getNomh()<<"  zone: "<<habitants[i].getZoneh()<<endl;
                
            }
        }
        if (c=='r')
        {  vector <Recommande>recommandes;
            readR(recommandes,rkb,rk);
            for (int i = 0; i < recommandes.size(); i++)
            {   if (recommandes[i].getType()=="l")
            {
                cout<<"lettre by: ";
            }
            else{
                cout<<"coli by: ";
            }
              cout<<recommandes[i].getNumf()<<" to: "<<recommandes[i].getNumh()<<endl;  
            }
        }
        

    }
    
    return(0);
}
//convert from ASCII to hexadecimal
string tohexa(string s){
    string h="";
    for ( char c:s)
    {
       for (int i = 0; i<ASCII.size(); i++)
       {
         if (ASCII[i]==c)
         {
            h+=hexat[i];
         }
         
       }
       
    }
    
  return(h);  
}
//convert from hexadecimal to ASCII
string toASCII(string s){
    string sa="";
    for (int i = 0; i < s.size(); i=i+2)
    {
        string sh="";
        sh+=s[i];
        sh+=s[i+1];
        for (int i = 0; i<hexat.size(); i++)
       {
         if (hexat[i]==sh)
         {
            sa+=ASCII[i];
         }
         
       }

        
    }
    return(sa);
}
//verify if the string is in base 64
string base64bits(string s){
	int cpt=0;
    for (char c:s)
    {
        cpt++;
    }
    if(cpt<16){
        int n=16-cpt;
        for (int i = 0; i <int(n/2); i++)
        {
            s+="58";
        }
        
    }
	return (s);
}
//verify if the data is created already or not
bool data_existe(){
    ifstream file("Recommande.txt");
    if(!file.is_open()){
        return(false);
    }else{
        return(true);
    }
}
//create a new data 
void create_data(string k){
	ofstream R;
	R.open("Recommande.txt",ios_base::app | ios_base::in);
	R<<k<< endl;
	R.close();
	ofstream F;
	F.open("Recommande.txt",ios_base::app);
	F.close();
	ofstream H;
	H.open("Recommande.txt",ios_base::app);
	H.close();

}
int nbrline(string file){
    int nbr=0;
    string str;
    ifstream f(file);
    if(f){
       while(getline(f,str)){
           nbr++;
       }
    }
    return(nbr);
}
bool existe(string file, string mot){
    string str;
    bool ex=false;
    ifstream f(file);
    if(f){
       while((getline(f,str))&&(ex==false)){
            if (str==mot)
            {
              ex=true;
            }
            
       }
    
    }
    return(ex); 
}
string hex2bin(string s)
{
	// hexadecimal to binary conversion
	unordered_map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	string bin = "";
	for (int i = 0; i < s.size(); i++) {
		bin += mp[s[i]];
	}
	return bin;
}
string bin2hex(string s)
{
	// binary to hexadecimal conversion
	unordered_map<string, string> mp;
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
	string hex = "";
	for (int i = 0; i < s.length(); i += 4) {
		string ch = "";
		ch += s[i];
		ch += s[i + 1];
		ch += s[i + 2];
		ch += s[i + 3];
		hex += mp[ch];
	}
	return hex;
}

string permute(string k, int* arr, int n)
{
	string per = "";
	for (int i = 0; i < n; i++) {
		per += k[arr[i] - 1];
	}
	return per;
}

string shift_left(string k, int shifts)
{
	string s = "";
	for (int i = 0; i < shifts; i++) {
		for (int j = 1; j < 28; j++) {
			s += k[j];
		}
		s += k[0];
		k = s;
		s = "";
	}
	return k;
}

string xor_(string a, string b)
{
	string ans = "";
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			ans += "0";
		}
		else {
			ans += "1";
		}
	}
	return ans;
}
string encrypt(string pt, vector<string> rkb,vector<string> rk)
{
	// Hexadecimal to binary
	pt = hex2bin(pt);

	// Initial Permutation Table
	int initial_perm[64]
		= { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44,
			36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22,
			14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57,
			49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35,
			27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13,
			5, 63, 55, 47, 39, 31, 23, 15, 7 };
	// Initial Permutation
	pt = permute(pt, initial_perm, 64);

	// Splitting
	string left = pt.substr(0, 32);
	string right = pt.substr(32, 32);
	// Expansion D-box Table
	int exp_d[48]
		= { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

	// S-box Table
	int s[8][4][16] = {
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5,
		9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6,
		12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2,
		11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2,
		4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12,
		0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0,
		1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13,
		1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1,
		3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12,
		7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4,
		6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 13,
		6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,
		5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8,
		7, 4, 15, 14, 3, 11, 5, 2, 12 },
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11,
		12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7,
		2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7,
		13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6,
		10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13,
		0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0,
		15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7,
		8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7,
		1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14,
		7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1,
		13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12,
		3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12,
		9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5,
		10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3,
		5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7,
		14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8,
		1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5,
		0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5,
		6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14,
		2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7,
		4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	};

	// Straight Permutation Table
	int per[32]
		= { 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23,
			26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27,
			3, 9, 19, 13, 30, 6, 22, 11, 4, 25 };

	for (int i = 0; i < 16; i++) {
		// Expansion D-box
		string right_expanded = permute(right, exp_d, 48);

		// XOR RoundKey[i] and right_expanded
		string x = xor_(rkb[i], right_expanded);

		// S-boxes
		string op = "";
		for (int i = 0; i < 8; i++) {
			int row = 2 * int(x[i * 6] - '0')
					+ int(x[i * 6 + 5] - '0');
			int col = 8 * int(x[i * 6 + 1] - '0')
					+ 4 * int(x[i * 6 + 2] - '0')
					+ 2 * int(x[i * 6 + 3] - '0')
					+ int(x[i * 6 + 4] - '0');
			int val = s[i][row][col];
			op += char(val / 8 + '0');
			val = val % 8;
			op += char(val / 4 + '0');
			val = val % 4;
			op += char(val / 2 + '0');
			val = val % 2;
			op += char(val + '0');
		}
		// Straight D-box
		op = permute(op, per, 32);

		// XOR left and op
		x = xor_(op, left);

		left = x;

		// Swapper
		if (i != 15) {
			swap(left, right);
		}
	}

	// Combination
	string combine = left + right;

	// Final Permutation Table
	int final_perm[64]
		= { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47,
			15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22,
			62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36,
			4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11,
			51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58,
			26, 33, 1, 41, 9, 49, 17, 57, 25 };

	// Final Permutation
	string cipher
		= bin2hex(permute(combine, final_perm, 64));
	return cipher;
}
string decrypt(string cipher,vector<string> rkb,vector<string> rk){
    	reverse(rkb.begin(), rkb.end());
	    reverse(rk.begin(), rk.end());
        string text = encrypt(cipher, rkb, rk);
        return(text);
}
//key generation
void keygeneration(string key, vector<string> &rkb,vector<string> &rk){
	key = hex2bin(key);

	// Parity bit drop table
	int keyp[56]
		= { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34,
			26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3,
			60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,
			62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37,
			29, 21, 13, 5, 28, 20, 12, 4 };

	// getting 56 bit key from 64 bit using the parity bits
	key = permute(key, keyp, 56); // key without parity

	// Number of bit shifts
	int shift_table[16] = { 1, 1, 2, 2, 2, 2, 2, 2,
							1, 2, 2, 2, 2, 2, 2, 1 };

	// Key- Compression Table
	int key_comp[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
						15, 6, 21, 10, 23, 19, 12, 4,
						26, 8, 16, 7, 27, 20, 13, 2,
						41, 52, 31, 37, 47, 55, 30, 40,
						51, 45, 33, 48, 44, 49, 39, 56,
						34, 53, 46, 42, 50, 36, 29, 32 };

	// Splitting
	string left = key.substr(0, 28);
	string right = key.substr(28, 28);
	for (int i = 0; i < 16; i++) {
		// Shifting 16
		left = shift_left(left, shift_table[i]);
		right = shift_left(right, shift_table[i]);

		// Combining
		string combine = left + right;

		// Key Compression
		string RoundKey = permute(combine, key_comp, 48);
		rkb.push_back(RoundKey);
		rk.push_back(bin2hex(RoundKey));
	}
}
//
void addF(string nf, string nz){
    string nomfile="Facteur.txt";
    fstream dataf;
    dataf.open(nomfile, std::ios_base::app | std::ios_base::in);
    if (dataf.is_open()){
        dataf<<nf<<" "<<nz<< endl;
        dataf.close();
    }
}
void addH(string nh, string nz){
    string nomfile="Habitant.txt";
    fstream dataf;
    dataf.open(nomfile, std::ios_base::app | std::ios_base::in);
    if (dataf.is_open()){
        dataf<<nh<<" "<<nz<< endl;
        dataf.close();
    }
}
void addR(string nf,string nh,string t){
    fstream datar;
    datar.open("Recommande.txt", std::ios_base::app | std::ios_base::in);
    if (datar.is_open()){
        datar<<nf<<" "<<nh<<" "<<t<< endl;
        datar.close();
    }
}
//function if we can add recommande return 0 if yes 1 if facteur don't existe,2 if habitant don't existe,3 if diffrent zone
int ifaddR(int nf,int nh){
    int e=0;
    string s;
    int i=0;
    fstream dataf;
    dataf.open("Facteur.txt", std::ios_base::app | std::ios_base::in);
    while((getline( dataf, s ))&&(i<=nf)) {
        i++;
    }
    if(i<nf){
        e=1;
    }else{
         string sh;
        int j=0;
        fstream datah;
        datah.open("Facteur.txt", std::ios_base::app | std::ios_base::in);
        while((getline( datah, sh ))&&(i<=nh)) {
            j++;
        }
        if(j<nh){
            e=2;
        }else{
            //find zone facteur
            int k=0;
            string nzf="";
            while ((k<s.size())&&(s[k]!=' '))
            {
                k++;
            }
            for (int k =k+1; k <s.size(); k++)
            {
                nzf+=s[k];
            }
            //find zone habitant
            int h=0;
            string nzh="";
            while ((h<s.size())&&(s[h]!=' '))
            {
                h++;
            }
            for (int h =h+1; h<s.size(); h++)
            {
                nzh+=s[h];
            }
            if(nzf!=nzh){
                e=3;
            }
        }
        return(e);
    }


}
//read table facteur
void readF(vector<Facteur>&f,vector<string> rkb,vector<string> rk){
     fstream dataf; 
     dataf.open("Facteur.txt", std::ios_base::app | std::ios_base::in);
     string s,name,numz;
     int j=0;
      while(getline( dataf, s )) {
            name="";
            numz="";
            int i=0;
            string nzf="";
            while ((i<s.size())&&(s[i]!=' '))
            {   
                
                name+=s[i];
                i++;
            }
            for (int k =i+1; k <s.size(); k++)
            {
                nzf+=s[k];
            }
            name=decrypt(name,rkb,rk);
            nzf=decrypt(nzf,rkb,rk);
            f[i].setNomf(name);
            f[i].setZonef(stoi(nzf));//stoi function convert from string to int
            j++;
        }
    dataf.close();    
}
//read table habitant
void readH(vector<Habitant>&h,vector<string> rkb,vector<string> rk){
     fstream datah; 
     datah.open("Habitant.txt", std::ios_base::app | std::ios_base::in);
     string s,name,numz;
     int j=0;
      while(getline( datah, s )) {
            name="";
            numz="";
            int i=0;
            string nzh="";
            while ((i<s.size())&&(s[i]!=' '))
            {   
                name+=s[i];
                i++;
            }
            for (int k =i+1; k <s.size(); k++)
            {
                nzh+=s[k];
            }
            name=decrypt(name,rkb,rk);
            nzh=decrypt(nzh,rkb,rk);
            h[i].setNomh(name);
            h[i].setZoneh(stoi(nzh));//stoi function convert from string to int
            j++;
        }
    datah.close();
}
void readR(vector<Recommande>&r,vector<string> rkb,vector<string> rk){
     fstream datah; 
     datah.open("Recommande.txt", std::ios_base::app | std::ios_base::in);
     string s,numf,numh,type;
     int j=0;
      while(getline( datah, s )) {
            numf="";
            numh="";
            type="";
            int i=0;
            while ((i<s.size())&&(s[i]!=' '))
            {   
                numf+=s[i];
                 i++;
            }
            int k =i+1;
            while ((k<s.size())&&(s[k]!=' '))
            {
                numh+=s[k];
                k++;
            }
            for (int t = 0; t < s.size(); t++)
            {
                type+=s[i];
            }
            //decrytpt line
            numf=decrypt(numf,rkb,rk);
            numh=decrypt(numh,rkb,rk);
            type=decrypt(type,rkb,rk);
            //covert line from hexa to ASCII
            numf=toASCII(numf);
            numh=toASCII(numh);
            type=toASCII(numh); 
            r[i].setNumf(stoi(numf));//stoi function convert from string to int
            r[i].setNumh(stoi(numh));
            r[i].setType(type);
            j++;
        }
    datah.close();
}