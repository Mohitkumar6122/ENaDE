#include<bits/stdc++.h>
using namespace std;

struct Node{
	char data;
	Node *left;
	Node *right;
	Node(char data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

string encryption_algo(string);
string level_one_encryption(string);
string level_two_encryption(string);

string decryption_algo(string);
string decrypt_level_one(string);
string decrypt_level_two(string);

Node* create_tree(string);
Node* convert_string_to_tree(string, Node*, int , int);
string convert_tree_to_string (Node*);
void reverse_alternate_levels(Node*);
string level_order_trav(Node*);

void input(string&);


int main(){
	int T = 10;
	while(T--){
		cout << endl << "Enter 1 to get encrypted key "<<endl << "Enter 2 to get decrypted key"<<endl <<"Enter 3 to exit\n" ;
		int choice; cin >> choice;
		if(choice == 1){
			string key, encrypted_key;

			input(key);
			encrypted_key = encryption_algo(key);

			cout<< "Encrypted_key : " << encrypted_key << endl;
		}
		else if (choice == 2){
			string key, decrypted_text;

			input(key);
			decrypted_text = decryption_algo(key);

			cout <<"Decrypted_key : " << decrypted_text << endl;
		}
		else if (choice == 3) { return 0 ;
		}
		else {cout << "Enter Valid option\n" ;
		}
	}

}


void input(string &key){
	cout << "Enter Text " << endl;
	cin >> key;
}
string encryption_algo(string key){
	key = level_one_encryption(key);
	key = level_two_encryption(key);
	return key;
}
string decryption_algo(string text){
	text = decrypt_level_one(text);
	text = decrypt_level_two(text);
	return text;
}

string level_one_encryption(string s){
	int len = s.length();
	for(int i = 0 ; i<len ; i++){
		if(i&1)
			s[i] = char(int(s[i]) + i); 
		else
			s[i] = char(int(s[i]) + i + 2);
	}
	return s;
}
string level_two_encryption(string s){
	Node *root = create_tree(s);
	reverse_alternate_levels(root);
	string ciphertext;
	ciphertext = level_order_trav(root);
	return ciphertext;
}
string decrypt_level_one(string s){
	Node *root = create_tree(s);
	reverse_alternate_levels(root);
	string intermediate_text = convert_tree_to_string(root);
	return intermediate_text;
}
string decrypt_level_two(string s){
	int n = s.length();
	for(int i = 0 ; i<n ; i++){
		if(i&1)
			s[i] = char(int(s[i]) - i);
		else
			s[i] = char(int(s[i]) - i -2);
	}
	return s;
}
Node* create_tree(string s){
	int len = s.length();
	Node *root = convert_string_to_tree(s, root, 0,len);
	return root;
}
Node* convert_string_to_tree(string s, Node* root, int i, int n){
	if(i < n){
		Node *temp = new Node(s[i]);
		root = temp;
		root->left = convert_string_to_tree(s, root->left, 2*i+1,n);
		root->right = convert_string_to_tree(s, root->right, 2*i + 2, n);
	}
	return root;
}
void reverse_alternate_levels(Node *root){
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		Node *node = q.front();
		q.pop();
		if(node->left && node->right)
		swap(node->left->data, node->right->data);
		if(node->left)q.push(node->left);
		if(node->right)q.push(node->right);
	}
}
string level_order_trav(Node *root){
	string s = "";
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		Node *node = q.front();
		q.pop();
		s.push_back(node->data);
		if(node->left)q.push(node->left);
		if(node->right)q.push(node->right);
	}
	return s;
}
string convert_tree_to_string (Node *root){
	return level_order_trav(root);
}
