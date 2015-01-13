using namespace std;
#include <fstream>
#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <deque>
//create node class
//node(state number, start/accept) [0-1000]
	//has amount of transitions
	//bool start
	//bool accept
	//store transition nodes in a vector
//addtransition(number node[0-1000], char x, number node[0-1000] )
	//increment transition amount  
	
class Transition{
	public:
		Transition(int num1, char spec, int num2)
		{
			p = num1;
			x = spec;
			q = num2;
		}
		int getFirst()
		{
			return p;
		}
		char getSecond()
		{
			return x;
		}
		int getThird()
		{
			return q;
		}
		~Transition()
		{}
	private:
		int p, q;
		char x;
};

class Node{
	public:
	Node()
	{
		state = 0;
		trans;
		accept = false;
		explored = false;
	}
	Node(int sn, bool acc)
	{
		state = sn;
		trans;
		accept = acc;
		explored = false;
	}
	int getState()
	{
		return state;
	}
	void addTransition(int num1, char spec, int num2)
	{
		trans.push_back(Transition(num1, spec, num2));
	}
	vector<Transition> getTrans()
	{
		return trans;
	}
	bool getAccept()
	{
		return accept;
	}
	bool getExplored()
	{
		return explored;
	}
	void changeExplored()
	{
		explored = true;
	}
	~Node()
	{
	}
	private:
		int state;
		bool accept;
		vector<Transition> trans;
		bool explored;
};


int main (int argc, char *argv[] )
{
	string line;
	if (argc != 3){
		cout << "Incorrect number of arguments!" << endl;
	}
	else{
		Node* currentNode;
		Node* startingNode;
		vector<Node*>* store = new vector<Node*>;
		vector<int>* acceptnodes = new vector<int>;
		vector<int>* startnodes = new vector<int>;
		vector<int>* finalaccept = new vector<int>;
		vector<int>* finalreject = new vector<int>;
		vector<int>* endingstates = new vector<int>;
		deque<Node*>* nextnodes = new deque<Node*>;
		deque<int>* nextnodesint = new deque<int>;
		deque<int>::iterator uni;
		ifstream am (argv[1]);
		ifstream dummy(argv[1]);
		if (!am.is_open() && !dummy.is_open()){
			cout << "Could not open file." << endl;
		}
		else{
			while(getline(am, line)){
				//cout << line << endl;
				if (line.find("state") != string::npos)
				{//found the state line
					if (line.find("start") != string::npos && line.find("accept") != string::npos)
					{//first check if line can have both
						string sn;
						dummy >> sn; dummy >> sn; //second word of line (state number)
						//cout << "START SN: " << sn << endl;
						int change = atoi(sn.c_str());
						Node* add = new Node(change, 1);
						store->push_back(add);
						startnodes->push_back(change);
						acceptnodes->push_back(change);
					}
					else if (line.find("start") != string::npos)
					{//find the starting node
						string sn;
						dummy >> sn; dummy >> sn; //second word of line (state number)
						//cout << "START SN: " << sn << endl;
						int change = atoi(sn.c_str());
						Node* add = new Node(change, 0);
						store->push_back(add);
						startnodes->push_back(change);
					}
					else if (line.find("accept") != string::npos)
					{//find the accepting nodes
						string sn;
						dummy >> sn; dummy >> sn; //second word of line (state number)
						//cout << "ACCEPT SN: " << sn << endl;
						int change = atoi(sn.c_str());
					 	Node* add = new Node(change,1);
						store->push_back(add);
						acceptnodes->push_back(change);
					}
					else if(line.find("start") == string::npos && line.find("accept") == string::npos)
					{//find the nodes with neither accepting nor starting qualities
						string sn;
						dummy >> sn; dummy >> sn; //second word of line (state number)
						//cout << "NEITHER SN: " << sn << endl;
						int change = atoi(sn.c_str());
						Node* add = new Node(change,0);
						store->push_back(add);	
					}
				getline(dummy, line); //move the second file along to keep track with first file
				}
				else if (line.find("transition") !=string::npos)
				{
					string sn, a, b, c;
					dummy >> sn;
					dummy >> a;
					dummy >> b;
					dummy >> c;
					//cout << "sn: " << sn << " " << "a: " << a << " " << "b: " << b << " "<< "c: " << c << " "<< endl;
					int changeP = atoi(a.c_str());
					char changeX = b[0];
					int changeQ = atoi(c.c_str());
					for (int i = 0; i < store->size(); i++){
						if ((*store)[i]->getState() == changeP){
							(*store)[i]->addTransition(changeP, changeX, changeQ);
						}
					}
				}
			}
			/*cout << "store size: " << store->size() << endl;
			for (int i = 0; i < (*store).size(); i++){
				cout << "NODE STATES: " << (*store)[i]->getState() << endl;
				cout << "trans size: " << (*store)[i]->getTrans().size() << endl;
				for (int j = 0; j < (*store)[i]->getTrans().size(); j++)
				{
				cout << "TRANSITIONS: " << (*store)[i]->getTrans()[j].getFirst() << (*store)[i]->getTrans()[j].getSecond() << (*store)[i]->getTrans()[j].getThird() << endl;
				}
			}
			for (int i =0; i < acceptnodes->size(); i++)
			{
				cout << "Accept nodes: " << (*acceptnodes)[i] << endl;
			}
			for (int i =0; i < startnodes->size(); i++)
			{
				cout << "Start nodes: " << (*startnodes)[i] << endl;
			}
			*/
		}
		//cout << "argv[2]: " << argv[2] << endl;	
		string argu = argv[2];
		deque<char> dequearg;
		for (int i = 0; i < argu.size(); i++)
		{
			dequearg.push_back(argu[i]);
			//cout << "argu[i]: " << argu[i] << endl;
		}
		for(int i=0; i < store->size(); i++)
		{
			if((*store)[i]->getState() == (*startnodes)[0])
			{
				currentNode = (*store)[i];
				startingNode = (*store)[i];
			}
		}
	int a = 0;
	if (dequearg.size() == 1){
		for (int i=0; i < currentNode -> getTrans().size(); i++)
		{
			if (currentNode -> getTrans()[i].getSecond() == dequearg[0])
			{
				finalreject -> push_back(currentNode -> getTrans()[i].getThird());
			}
		}
	}
	else
	{
		for (int i = 0; i < dequearg.size(); i++)
		{
			for (int j = 0; j < currentNode -> getTrans().size(); j++)
			{
				if (dequearg[i] == currentNode->getTrans()[j].getSecond())
				{
					//cout << dequearg[i] << " transitions to: " << currentNode->getTrans()[j].getThird() << endl;
					finalreject-> push_back(currentNode->getTrans()[j].getThird());
					if (currentNode->getTrans()[j].getFirst() == currentNode->getTrans()[j].getThird())
					{
						//cout << currentNode->getTrans()[j].getThird() << " can reject" << endl;
						finalreject -> push_back(currentNode->getTrans()[j].getThird());
					}
					if (currentNode ->getState() != currentNode->getTrans()[j].getThird() && currentNode -> getExplored() == false )
					{
						//cout << "Explore next node: " << currentNode->getTrans()[j].getThird() << endl;
						for (int k = 0; k < (*store).size(); k++)
						{
							if ((*store)[k]->getState() == currentNode->getTrans()[j].getThird())
							{
							//	cout << "pushed: " << (*store)[k]->getState() << endl;
								nextnodes -> push_back((*store)[k]);
							//	cout << "Size of nextnodes: " << (*nextnodes).size() << endl;
							}
						}
					}
				}
			}
			if (!(*nextnodes).empty())
			{
				currentNode -> changeExplored(); 
				currentNode = (*nextnodes)[0];
				(*nextnodes).pop_back();
				//cout << "CurrentNode changed" << endl;
			}
		}
	}
	for (int i = 0; i < (*finalreject).size(); i++)
	{
		for (int j = 0; j < (*acceptnodes).size(); j++)
		{
			if ((*finalreject)[i] == (*acceptnodes)[j])
			{
				finalaccept -> push_back((*finalreject)[i]);
			}	
		}
	}
	if (finalreject -> empty())
	{
		finalreject -> push_back(startingNode -> getState());
	}
	//for (int i=0; i < nextnodes -> size(); i++){
	//	cout << "Nextnodes: " << (*nextnodes)[i] -> getState() << endl;
	//}
	for (int i=0; i < endingstates->size();i++)
	{
		finalreject -> push_back((*endingstates)[i]);
	}
	sort(finalaccept->begin(), finalaccept->end());
	sort(finalreject->begin(), finalreject->end());
	vector<int>::iterator it1;
	it1 = unique (finalaccept->begin(), finalaccept->end());
	finalaccept -> resize(distance(finalaccept->begin(), it1));
	if (!finalaccept->empty())
	{
		cout << "accept ";
		for (int i=0; i< finalaccept->size(); i++)
		{
			cout << (*finalaccept)[i] << " ";
		}
		cout << endl;
	}
	vector<int>::iterator it2;
	it2 = unique (finalreject->begin(), finalreject->end());
	finalreject -> resize(distance(finalreject->begin(), it2));
	if (finalaccept->empty())
	{
		cout << "reject ";
		for (int i=0; i < finalreject->size(); i++)
		{
			cout << (*finalreject)[i] << " ";
		}
		cout << endl;
	}
		am.close();
		dummy.close();
		for (int i =0; i<(*store).size();i++){
			delete (*store)[i];
		}
		delete store;
		delete startnodes;
		delete acceptnodes;
		delete finalreject;
		delete finalaccept;
		delete nextnodes;
		delete nextnodesint;
		delete endingstates;
	}
}