#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXLINE 6
vector<vector<string>> state;
vector<string> item(MAXLINE);
vector<string> attribute_row;
map<string, vector<string>> map_attribute_values;
string yes("yes");
string no("no");
string blank("");
struct Node
{
	string attribute;
	string attribute_value;
	vector<Node*> childs;
	Node()
	{
		attribute=blank;
		attribute_value = blank;
	}
};

Node* root;


void Input()
{
	string s;
	ifstream f;
	f.open("data.txt", ios::in);
	if (!f)
	{
		cout << "can't find the file!" << endl;
		f.close();
		return;
	}
	while (f >> s, s.compare("end")!=0)
	{
		item[0] = s;
		for (int i = 1; i < MAXLINE; i++)
			f >> item[i];
		state.push_back(item);
	}
	for (int i = 0; i < MAXLINE; i++)
		attribute_row.push_back(state[0][i]);
	f.close();
}

void ComputeMapFrom2DVector()
{
	bool exited = false;
	vector<string> values;
	for (int i = 1; i < MAXLINE - 1; i++)
	{
		for (int j = 1; j < state.size(); j++)
		{
			for (int k = 0; k < values.size(); k++)
			{
				if (values[k].compare(state[j][i]) == 0)
					exited = true;
			}
			if (!exited)
				values.push_back(state[j][i]);
			exited = false;
		}
		map_attribute_values[state[0][i]] = values;
		values.erase(values.begin(), values.end());
	}
}

bool AllTheSameLabel(vector<vector<string>> remain_state, string label)
{
	int count = 0;
	for (int i = 0; i < remain_state.size(); i++)
	{
		if (remain_state[i][MAXLINE - 1].compare(label))
			count++;
	}
	if (count == remain_state.size() - 1)
		return true;
	else
		return false;
}

string MostCommonLabel(vector<vector<string>> remain_state)
{
	int p = 0, n = 0;
	for (int i = 0; i < remain_state.size(); i++)
	{
		if (remain_state[i][MAXLINE - 1].compare(yes))
			p++;
		else
			n++;
	}
	if (p >= n)
		return yes;
	else
		return no;
}

double ComputeEntropy(vector<vector<string>> remain_state, string attribute, string value, bool ifparent)
{
	vector<int> count(2, 0);
	bool done_flag = false;
	for (int j = 1; j < MAXLINE; j++)
	{
		if (done_flag)
			break;
		if (attribute_row[j].compare(attribute) == 0)
		{
			for (int i = 1; i < remain_state.size(); i++)
			{
				if ((!ifparent&&!remain_state[i][j].compare(value)) || ifparent)
				{
					if (remain_state[i][MAXLINE-1].compare(yes)==0)
						count[0]++;
					else
						count[1]++;
				}
			}
			done_flag = true;
		}
	}
	if (count[0] == 0 || count[1] == 0)
		return 0;
	double sum = count[0] + count[1];
	double entropy = -count[0] / sum*log(-count[0] / sum) / log(2.0) - count[1] / sum*log(count[1] / sum) / log(2.0);
	return entropy;
}

double ComputeGain(vector<vector<string>> remain_state, string attribute)
{
	double parent_entropy = ComputeEntropy(remain_state, attribute, blank, true);
	double children_entropy = 0;
	vector<string> values = map_attribute_values[attribute];
	vector<double> ratio;
	vector<int> count_values;
	for (int m = 0; m < values.size(); m++)
	{
		int temp = 0;
		for (int k = 1; k < MAXLINE; k++)
		{
			if (attribute_row[k].compare(attribute) == 0)
			{
				for (int j = 1; j < remain_state.size(); j++)
				{
					if (remain_state[j][k].compare(values[m])==0)
					{
						temp++;
					}
				}
			}
		}
		count_values.push_back(temp);
	}
	for (int j = 0; j < values.size(); j++)
	{
		ratio.push_back((double)count_values[j] / (double)(remain_state.size() - 1));
	}
	double temp_entropy;
	for (int j = 0; j < values.size(); j++)
	{
		temp_entropy = ComputeEntropy(remain_state, attribute, values[j], false);
		children_entropy += ratio[j]*temp_entropy;
	}
	return parent_entropy - children_entropy;
}

int FindAttributeNumByName(string attri)
{
	for (int i = 0; i < MAXLINE; i++)
	{
		if (state[0][i].compare(attri) == 0)
			return i;
	}
	cerr << "can't find the numth of attribute" << endl;
	return 0;
}

Node *BuildDecisionTreeDFS(Node* p, vector<vector<string>> remain_state, vector<string> remain_attribute)
{
	if (p == NULL)
		p = new Node();
	if (AllTheSameLabel(remain_state, yes))
	{
		p->attribute = yes;
		return p;
	}
	if (AllTheSameLabel(remain_state, no))
	{
		p->attribute = no;
		return p;
	}
	if (remain_attribute.size() == 0)
	{
		string label = MostCommonLabel(remain_state);
		p->attribute = label;
		return p;
	}
	double max_gain = -1;
	double temp_gain;
	vector<string>::iterator max_it = remain_attribute.begin();
	for (vector<string>::iterator it1 = remain_attribute.begin(); it1 < remain_attribute.end(); it1++)
	{
		temp_gain = ComputeGain(remain_state, *it1);
		if (temp_gain > max_gain)
		{
			max_gain = temp_gain;
			max_it = it1;
		}
	}
	vector<string> new_attribute;
	vector<vector<string>> new_state;
	for (vector<string>::iterator it2 = remain_attribute.begin(); it2 < remain_attribute.end(); it2++)
	{
		if ((*it2).compare(*max_it) != 0)
			new_attribute.push_back(*it2);
	}
	p->attribute = *max_it;
	vector<string> values = map_attribute_values[*max_it];
	int attribute_num = FindAttributeNumByName(*max_it);
	new_state.push_back(attribute_row);
	for (vector<string>::iterator it3 = values.begin(); it3 < values.end(); it3++)
	{
		for (int i = 0; i < remain_state.size(); i++)
		{
			if (remain_state[i][attribute_num].compare(*it3) == 0)
			{
				new_state.push_back(remain_state[i]);
			}
		}
		Node *new_node = new Node();
		new_node->attribute_value = *it3;
		if (new_state.size() == 0)
			new_node->attribute = MostCommonLabel(remain_state);
		else
			new_node=BuildDecisionTreeDFS(new_node, new_state, new_attribute);
		p->childs.push_back(new_node);
		new_state.erase(new_state.begin(), new_state.end());
	}
	return p;
}

void PrintTree(Node *p, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "\t";
	if (!p->attribute_value.empty())
	{
		cout << p->attribute_value << endl;
		for (int i = 0; i < depth + 1; i++)
			cout << "\t";
	}
	cout << p->attribute << endl;
	for (vector<Node*>::iterator it = p->childs.begin(); it != p->childs.end(); it++)
		PrintTree(*it, depth + 1);
}

int main()
{
	Input();
	/*
	for (int i = 0; i <state.size(); i++)
	{
		for (int j = 0; j < state[0].size(); j++)
			cout << state[i][j] << " ";
		cout << endl;
	}
	*/
	ComputeMapFrom2DVector();
	/*
	for (map<string, vector<string>>::iterator i = map_attribute_values.begin(); i != map_attribute_values.end(); i++)
	{
		cout << i->first << ":";
		for (int j = 0; j < i->second.size(); j++)
			cout << i->second[j] << " ";
		cout << endl;
	}
	*/
	vector<string> remain_attribute(state[0].begin() + 1, state[0].end() - 1);
	/*
	for (int i = 0; i < remain_attribute.size(); i++)
		cout << remain_attribute[i] << " ";
	*/
	vector<vector<string>> remain_state;
	for (int i = 0; i < state.size(); i++)
		remain_state.push_back(state[i]);
	root=BuildDecisionTreeDFS(root, remain_state, remain_attribute);
	PrintTree(root, 0);
}