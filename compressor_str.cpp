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
	string str;
	int count;
	node* left;
	node* right;
};
node* getnode(string s,int cnt,node* l,node* r)
{
	node* n = new node();
	n->str = s ;
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

node* build(vector<pair<string,int>> vec)
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
		pq.push(getnode("\0", sum, left, right));
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
		cout<<cur->str<<":"<<cur->count<<endl;
		q.pop();
		if(cur->left!=nullptr) 
		{
			q.push(cur->left);
			q.push(cur->right);
		}
	}
}


void traverse_tree(node* root,string s,unordered_map<string,string>&um)
{
      if(root)
      {
          traverse_tree(root->left,s+"0",um);
	  um[root->str]=s;
	  //cout<<root->str<<":"<<s<<endl;
          traverse_tree(root->right,s+'1',um);
          um[root->str]=s;
	  //cout<<root->str<<":"<<s<<endl;
      }
      
      
}

int main()
{	
	
	string line;
	vector<string> vec;
	unordered_map<string,int> us;	




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
		string str="";
		for(char c : line)
		{
			if(c==' ') 
			{
				vec.push_back(str);
				us[str]+=1;
				str=c;
				vec.push_back(str);
				us[str]+=1;
				str="";
			}
			else str+=c;
		}
	}
	unordered_map<string, int>::iterator itr;
	
	/*for(itr = us.begin() ; itr!=us.end() ; ++itr)
	{
		cout<<itr->first<<" : "<<itr->second<<" ";
	}*/
	
	vector<pair<string,int>> v(us.begin(),us.end());
	sort(v.begin(),v.end(),
		[](const auto& a, const auto& b) 
			{return a.second < b.second;});
	for(const auto& x : v)
	{
		cout<<"'"<<x.first<<"'"<<":"<<x.second<<" ";
	}

	node* r = new node();
	r = build(v);
	//cout<<r->left->str<<":"<<r->left->count;
	print_tree(r);
	unordered_map<string,string> um;
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
		string str="";
		for(char c : line)
		{
			if(c==' ') 
			{
				fout<<um[str];
				cout<<str<<":"<<um[str]<<" ";
				str=c;
				fout<<um[str];
				cout<<str<<":"<<um[str]<<" ";
				str="";
			}
			else str+=c;
		}
		fout<<endl;
		cout<<endl;
	}
	delete r;
	fin.close();
	fout.close();
	return 0;
}