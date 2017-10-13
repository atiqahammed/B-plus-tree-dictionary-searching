#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define linkSize 3
#define keySize 2
#define test cout << "testing" << endl;

using namespace std; 

int totalDataSize;
string testWord = "elephant";
bool found = false;

struct Word
{
    string english;
    string bangla;
};

struct Node
{
    bool isLeaf;
    vector<Word> key;    
    Node *child1;
    Node *child2;
    Node *child3;
    Node *tempChild;
    Node *parent;
    Node *sibling;
    int numberOfKey;
};

Node *root = NULL;
void insertIntoTree(Word word, Node *currentNode);

Node* createNewNode(void)
{
    Node *newNode;
    
    newNode = new Node[1];
    newNode[0].isLeaf = true;
    newNode[0].child1 = NULL;
    newNode[0].child2 = NULL;
    newNode[0].child3 = NULL;
    newNode[0].tempChild = NULL;
    newNode[0].parent = NULL;
    newNode[0].sibling = NULL;
    newNode[0].numberOfKey = 0;
    
    return newNode;
}

bool compare(Word x, Word y)
{
    return x.english < y.english; 
}

void split(Node *currentNode)
{
    if(currentNode[0].tempChild != NULL && currentNode[0].parent != NULL)
    {
        //test
        Word mid = currentNode[0].key[1];
    
    
        Node *c2 = createNewNode();
        c2[0].key.push_back(currentNode[0].key[2]);
        c2[0].isLeaf = false;
        
        c2[0].child1 = currentNode[0].child3;
        currentNode[0].child3[0].parent = c2;
        c2[0].child2 = currentNode[0].tempChild;
        currentNode[0].tempChild[0].parent = c2;
        
        vector<Word> newKey;
        newKey.push_back(currentNode[0].key[0]);
        currentNode[0].key = newKey;
        
        currentNode[0].child3 = NULL;
        currentNode[0].tempChild = NULL;
        
        if(currentNode[0].parent[0].key.size() == 1)
        {
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].child3 = c2;
            c2[0].parent = currentNode[0].parent;
        
        }
        
        else
        {
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].tempChild = c2;
            c2[0].parent = currentNode[0].parent;;
            split(currentNode[0].parent);
        }
    }
    
    
    else if(currentNode[0].tempChild != NULL && currentNode[0].parent == NULL)
    {
        //test
        Word mid = currentNode[0].key[1];
        Node *par = createNewNode();
        par[0].key.push_back(mid);
        
        Node *c2 = createNewNode();
        c2[0].key.push_back(currentNode[0].key[2]);
        c2[0].isLeaf = false;
        c2[0].child1 = currentNode[0].child3;
        currentNode[0].child3[0].parent = c2;
        
        c2[0].child2 = currentNode[0].tempChild;
        currentNode[0].tempChild[0].parent = c2;
        
        
        vector<Word> newKey;
        newKey.push_back(currentNode[0].key[0]);
        currentNode[0].key = newKey;
        
        currentNode[0].child3 = NULL;
        currentNode[0].tempChild = NULL;
        
        par[0].child1 = currentNode;
        currentNode[0].parent = par;
        par[0].child2 = c2;
        c2[0].parent = par;
        par[0].isLeaf = false;
        root = par; 
    }
   
    else if(currentNode[0].parent == NULL && currentNode[0].isLeaf)
    {
        Word mid = currentNode[0].key[1];
        
        Node *c1 = createNewNode();
        insertIntoTree(currentNode[0].key[0], c1);
        c1[0].parent = currentNode;
        currentNode[0].child1 = c1;
        
        Node *c2 = createNewNode();
        insertIntoTree(currentNode[0].key[1], c2);
        insertIntoTree(currentNode[0].key[2], c2);
        c2[0].parent = currentNode;
        currentNode[0].child2 = c2;
        
        c1[0].sibling = c2;
        
        vector<Word> newKey;
        currentNode[0].key = newKey;
        currentNode[0].key.push_back(mid);
        currentNode[0].isLeaf = false;
    }
    
    else if(currentNode[0].parent != NULL && currentNode[0].isLeaf)
    {
        Word mid = currentNode[0].key[1];
        vector<Word> newKey;
        
        newKey.push_back(currentNode[0].key[0]);
        
        Node *c3 = createNewNode();
        c3[0].key.push_back(currentNode[0].key[1]);
        c3[0].key.push_back(currentNode[0].key[2]);
    
        currentNode[0].key = newKey;
        currentNode[0].sibling = c3;
        
        if(currentNode[0].parent[0].key.size() == 1)
        {
            //test
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].child3 = c3;
            c3[0].parent = currentNode[0].parent;
        }
        
        else if(currentNode[0].parent[0].key.size() == 2)
        {
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].tempChild = c3;
            c3[0].parent = currentNode[0].parent;
            split(currentNode[0].parent);
        }        
    }
}

void insertIntoTree(Word word, Node *currentNode)
{
    if(currentNode[0].isLeaf)
    {
        currentNode[0].key.push_back(word);
       
        sort(currentNode[0].key.begin(), currentNode[0].key.end(), compare);
       
       
        if(currentNode[0].key.size() == linkSize)
            split(currentNode);   
    }
    else
    {
        if(word.english < currentNode[0].key[0].english)
            insertIntoTree(word, currentNode[0].child1);
       // test
        else {
            if(currentNode[0].key.size() == 1)
            {
                //test
           
                insertIntoTree(word, currentNode[0].child2);
            }
            
            else{
                //test
                if(word.english < currentNode[0].key[1].english)
                {
                    insertIntoTree(word, currentNode[0].child2);
                }
                else
                {
                    insertIntoTree(word, currentNode[0].child3);
                }
            }
        }    
    }
}




void input(void)
{
    cin >> totalDataSize;
    for(int i = 0; i < totalDataSize; i++)
    {
        string s1, s2;
        cin >> s1;
        getline(cin, s2);
        getline(cin, s2);   
        Word temp;
        temp.english = s1;
        temp.bangla = s2;
        insertIntoTree(temp, root);
    
    
    }


}

void traverse(Node *node)
{
    cout << endl;
    if(node[0].isLeaf) cout << "Leaf" << endl;
    
    for(int i = 0; i < node[0].key.size(); i++)
        cout << node[0].key[i].english << " ..> " << node[0].key[i].bangla << "   ";
    cout << endl;
    if(node[0].child1 != NULL)
    {
        traverse(node[0].child1);
    }
    
    if(node[0].child2 != NULL)
    {
        traverse(node[0].child2);
    }
    
    if(node[0].child3 != NULL)
    {
        traverse(node[0].child3);
    }
}

void search(Node *node)
{
    int index = 0;
    for(int i = 0; i < node[0].key.size(); i++)
    {   
        if(node[0].key[i].english == testWord && node[0].isLeaf)
        {
            cout << "Word found" << endl;
            cout << testWord << "  means,  " << node[0].key[i].bangla << endl;
            found = true;
        }
    }
    if(node[0].child1 != NULL)
    {
        search(node[0].child1);
    }
    
    if(node[0].child2 != NULL)
    {
        search(node[0].child2);
    }
    
    if(node[0].child3 != NULL)
    {
        search(node[0].child3);
    }
}



int main(void)
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    root = createNewNode();
    input();
    //traverse(root);
    search(root);
    if(!found) cout << "Sorry" << endl << "Not Found" << endl;
    //if(root[0].isLeaf) test


}
