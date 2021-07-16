#include <bits/stdc++.h>
using namespace std;

struct Node
{
	char data;
	Node *left;
	Node *right;
	Node(char data)
	{
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

Node *create_tree(string);
Node *convert_string_to_tree(string, Node *, int, int);
string convert_tree_to_string(Node *);
void reverse_alternate_levels(Node *);
string level_order_trav(Node *);

void input(string &);

int main()
{
	int T = 10;
	while (T--)
	{
		cout << "\nEnter 1 to get encrypted key\n"
				 << "Enter 2 to get decrypted key\n"
				 << "Enter 3 to exit\n";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			string key, encrypted_key;

			input(key);
			encrypted_key = encryption_algo(key);

			cout << "Encrypted_key : " << encrypted_key << endl;
		}
		else if (choice == 2)
		{
			string key, decrypted_text;

			input(key);
			decrypted_text = decryption_algo(key);

			cout << "Decrypted_key : " << decrypted_text << endl;
		}
		else if (choice == 3)
		{
			return 0;
		}
		else
		{
			cout << "Enter Valid option\n";
		}
	}
}
// Takes input from console
void input(string &key)
{
	cin.clear();
	cin.sync();
	cout << "Enter Text " << endl;
	getline(cin, key);
}

// Performs encryption
string encryption_algo(string key)
{
	key = level_one_encryption(key);
	key = level_two_encryption(key);
	return key;
}

// performs decryption
string decryption_algo(string text)
{
	text = decrypt_level_one(text);
	text = decrypt_level_two(text);
	return text;
}

// level one encryption
// returns Intermediate Cipher text
string level_one_encryption(string s)
{
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (i & 1)
			s[i] = (char)(int(s[i]) + i);
		else
			s[i] = (char)(int(s[i]) + i + 2);
	}
	return s;
}

// level two encryption
// returns cipher text
string level_two_encryption(string s)
{
	Node *root = create_tree(s);
	reverse_alternate_levels(root);
	string ciphertext;
	ciphertext = level_order_trav(root);
	return ciphertext;
}

// level one decryption
// returns intermediate cipher text
string decrypt_level_one(string s)
{
	Node *root = create_tree(s);
	reverse_alternate_levels(root);
	string intermediate_text = convert_tree_to_string(root);
	return intermediate_text;
}

// final level decryption
// returns original text
string decrypt_level_two(string s)
{
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		if (i & 1)
			s[i] = char(int(s[i]) - i);
		else
			s[i] = char(int(s[i]) - i - 2);
	}
	return s;
}

// creates tree from the intermediate cipher text
Node *create_tree(string s)
{
	int len = s.length();
	Node *root = convert_string_to_tree(s, root, 0, len);
	return root;
}

// converts string to tree and returns root of tree
Node *convert_string_to_tree(string s, Node *root, int i, int n)
{
	if (i < n)
	{
		Node *temp = new Node(s[i]);
		root = temp;
		root->left = convert_string_to_tree(s, root->left, 2 * i + 1, n);
		root->right = convert_string_to_tree(s, root->right, 2 * i + 2, n);
	}
	return root;
}

// reverse alternate levels (2nd level encryption)
void reverse_alternate_levels(Node *root)
{
	queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		Node *node = q.front();
		q.pop();
		//  actually swapping nodes not just the data
		swap(node->left, node->right);
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
}

// performs level order traversal on final tree
string level_order_trav(Node *root)
{
	string s = "";
	queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		Node *node = q.front();
		q.pop();
		s.push_back(node->data);
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
	return s;
}

// converts tree to string(level 2 decryption)
string convert_tree_to_string(Node *root)
{
	return level_order_trav(root);
}
