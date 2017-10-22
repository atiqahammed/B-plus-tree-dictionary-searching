#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define linkSize 3
#define keySize 2
#define test cout << "testing" << endl;

using namespace std; 

int totalDataSize;
string testWord = "cat";
string meaning;
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
};

Node *root = NULL;
void insertIntoTree(Word word, Node *currentNode);

void splitNonLeaf(Node *node, Node *newSib)
{
    vector<Word> newKey;
    newSib[0].key.push_back(node[0].key[2]);
    newSib[0].isLeaf = false;
        
    newSib[0].child1 = node[0].child3;
    node[0].child3[0].parent = newSib;
    node[0].child3 = NULL;
        
    newSib[0].child2 = node[0].tempChild;
    node[0].tempChild[0].parent = newSib;
    node[0].tempChild = NULL;
        
    newKey.push_back(node[0].key[0]);
    node[0].key = newKey;    
}



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
    
    return newNode;
}

bool compare(Word x, Word y)
{
    return x.english < y.english; 
}

void split(Node *currentNode)
{
    vector<Word> newKey;
    Word mid = currentNode[0].key[1];
    Node *c1 = createNewNode();
    Node *c2 = createNewNode();
    
    
    if(currentNode[0].tempChild != NULL && currentNode[0].parent != NULL)
    {
        splitNonLeaf(currentNode, c2);
        
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
        Node *par = createNewNode();
        par[0].key.push_back(mid);
        
        splitNonLeaf(currentNode, c2);
        
        par[0].child1 = currentNode;
        currentNode[0].parent = par;
        par[0].child2 = c2;
        c2[0].parent = par;
        par[0].isLeaf = false;
        root = par; 
    }
   
    else if(currentNode[0].parent == NULL && currentNode[0].isLeaf)
    {
        insertIntoTree(currentNode[0].key[0], c1);
        c1[0].parent = currentNode;
        currentNode[0].child1 = c1;
        insertIntoTree(currentNode[0].key[1], c2);
        insertIntoTree(currentNode[0].key[2], c2);
        c2[0].parent = currentNode;
        currentNode[0].child2 = c2;
        c1[0].sibling = c2;
        currentNode[0].key = newKey;
        currentNode[0].key.push_back(mid);
        currentNode[0].isLeaf = false;
    }
    
    else if(currentNode[0].parent != NULL && currentNode[0].isLeaf)
    {
        newKey.push_back(currentNode[0].key[0]);
        c1[0].key.push_back(currentNode[0].key[1]);
        c1[0].key.push_back(currentNode[0].key[2]);
        currentNode[0].key = newKey;
        currentNode[0].sibling = c1;
        
        if(currentNode[0].parent[0].key.size() == 1)
        {
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].child3 = c1;
            c1[0].parent = currentNode[0].parent;
        }
        
        else if(currentNode[0].parent[0].key.size() == 2)
        {
            currentNode[0].parent[0].key.push_back(mid);
            currentNode[0].parent[0].tempChild = c1;
            c1[0].parent = currentNode[0].parent;
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
        if(currentNode[0].key.size() == linkSize) split(currentNode);   
    }
    else
    {
        if(word.english < currentNode[0].key[0].english) insertIntoTree(word, currentNode[0].child1);
        else {
            if(currentNode[0].key.size() == 1) insertIntoTree(word, currentNode[0].child2);
            else
            {
                if(word.english < currentNode[0].key[1].english) insertIntoTree(word, currentNode[0].child2);
                else insertIntoTree(word, currentNode[0].child3);
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
        Word word;
        word.english = s1;
        word.bangla = s2;
        insertIntoTree(word, root);
    }
}

void traverse(Node *node)
{
    cout << endl;
    if(node[0].isLeaf) cout << "Leaf" << endl;
    for(int i = 0; i < node[0].key.size(); i++)
        cout << node[0].key[i].english << " ..> " << node[0].key[i].bangla << "   ";
    cout << endl;
    
    if(node[0].child1 != NULL) traverse(node[0].child1);
    if(node[0].child2 != NULL) traverse(node[0].child2);
    if(node[0].child3 != NULL) traverse(node[0].child3);
}

void search2(Node *node)
{
    int index = -1;
    for(int i = 0; i < node[0].key.size(); i++)
    {
        if(!found && node[0].key[i].english == testWord)
        {
            meaning = node[0].key[i].bangla;
            found = true;
            return;
        }
        
        else if(node[0].key[i].english > testWord)
        {
            index = i;
            break;
        }  
    }
    
    if(!found)
    {
        if(index == 0 && node[0].child1 != NULL) search2(node[0].child1);
        else if(index = 1 && node[0].child2 != NULL) search2(node[0].child2);
        else if(node[0].child3 != NULL) search2(node[0].child3);
    }
}

void search(Node *node)
{
    for(int i = 0; i < node[0].key.size(); i++)
        if(node[0].key[i].english == testWord && node[0].isLeaf)
        {
            cout << testWord << "  means,  " << node[0].key[i].bangla << endl;
            found = true;
        }
        
    if(node[0].child1 != NULL) search(node[0].child1);
    if(node[0].child2 != NULL) search(node[0].child2);
    if(node[0].child3 != NULL) search(node[0].child3);
}

int main(void)
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    root = createNewNode();
    input();
    traverse(root);
    search(root);
    if(!found) cout << "Sorry" << endl << "Not Found" << endl;
    //else cout << testWord << ".. means, -  " << meaning << endl;
    return 0;
}
