#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<utility>
#include<unordered_map>
using namespace std;



struct node
{
	char ch;
	int count;
	node* left;
	node* right;
};
node* getnode(char c,int cnt,node* l,node* r)
{
	node* n = new node();
	n->ch = c ;
	n->count = cnt ;
	n->left = l;
	n->right = r;
	return n;
}

struct comp
{
	bool operator()(node* l, node* r)
	{
		// highest priority item has lowest frequency
		return l->count > r->count;
	}
};

node* build(vector<pair<char,int>> vec)
{
	priority_queue<node*, vector<node*>, comp> pq;

	for (auto pair: vec) {
		pq.push(getnode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		
		node *left = pq.top(); pq.pop();
		node *right = pq.top();	pq.pop();

		int sum = left->count + right->count;
		pq.push(getnode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	node* root = pq.top();
	return root;
}


void print_tree(node* root)
{
	queue<node*> q;
	q.push(root);
	while(q.front()!=nullptr)
	{
		node* cur = q.front();
		cout<<cur->ch<<":"<<cur->count<<endl;
		q.pop();
		if(cur->left!=nullptr) 
		{
			q.push(cur->left);
			q.push(cur->right);
		}
	}
}


void traverse_tree(node* root,string str,unordered_map<char,string>&um)
{
      if(root)
      {
          traverse_tree(root->left,str+"0",um);
	  um[root->ch]=str;
	  //cout<<root->ch<<":"<<str<<endl;
          traverse_tree(root->right,str+'1',um);
          um[root->ch]=str;
	  //cout<<root->ch<<":"<<str<<endl;
      }
      
      
}

int main()
{	
	
	string line;
	vector<char> vec;
	unordered_map<char,int> us;	




	/*fstream fout;
	fout.open("sam", ios::trunc | ios::out);
	while(fout)
	{
		getline(cin,line);
		if(line=="-1") break;
		fout<<line;
	}
	fout.close();
	*/




	fstream fin;
	fin.open("sam",ios::in);
	while(getline(fin,line))
	{
		for(char c : line)
		{
			vec.push_back(c);
			us[c]+=1;
		}
	}
	unordered_map<char, int>::iterator itr;
	
	/*for(itr = us.begin() ; itr!=us.end() ; ++itr)
	{
		cout<<itr->first<<" : "<<itr->second<<" ";
	}*/
	
	vector<pair<char,int>> v(us.begin(),us.end());
	sort(v.begin(),v.end(),
		[](const auto& a, const auto& b) 
			{return a.second < b.second;});
	for(const auto& x : v)
	{
		cout<<"'"<<x.first<<"'"<<":"<<x.second<<" ";
	}

	node* r = new node();
	r = build(v);
	//cout<<r->left->ch<<":"<<r->left->count;
	print_tree(r);
	unordered_map<char,string> um;
	traverse_tree(r,"",um);
	for(auto x:um) cout<<x.first<<":"<<x.second<<endl;

	fstream fout; 
	//cout<<fin.tellg();
	fin.clear(fin.eofbit);
	fin.seekg(0,ios::beg);
	//cout<<fin.tellg();
	fout.open("zip.txt",ios::out);
	while(getline(fin,line))
	{
		for(char c : line)
		{
			fout<<um[c];
			cout<<c<<":"<<um[c]<<" ";
		}
		fout<<endl;
		cout<<endl;
	}
	delete r;
	fin.close();
	fout.close();
	return 0;
}