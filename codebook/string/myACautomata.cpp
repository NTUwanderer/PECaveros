int counts[105]; // added strings
int indexCounter;
struct Node{
  int cnt,dp;
  vector<int> indices;
  Node *go[26], *fail;
  Node (){
    cnt = 0; dp = -1; fail = 0;
    memset(go,0,sizeof(go));
  }
};
Node pool[1048576];

struct ACautomata{ // O(N)
  Node *root;
  int nMem;
  Node* new_Node(){
    pool[nMem] = Node();
    return &pool[nMem++];
  }
  void init()
  { nMem = 0; root = new_Node(); }
  void add(const string &str)
  { insert(root,str,0); }
  void insert(Node *cur, const string &str, int pos){
    if (pos >= (int)str.size()) {
      cur->cnt++;
      cur->indices.push_back(indexCounter++);
      return;
    }
    int c = str[pos]-'a';
    if (cur->go[c] == 0)
      cur->go[c] = new_Node();
    insert(cur->go[c],str,pos+1);
  }
  void make_fail(){
    queue<Node*> que;
    que.push(root);
    while (!que.empty()){
      Node* fr=que.front();
      que.pop();
      for (int i=0; i<26; i++){
        if (fr->go[i]){
          Node *ptr = fr->fail;
          while (ptr && !ptr->go[i]) ptr = ptr->fail;
          if (!ptr) fr->go[i]->fail = root;
          else fr->go[i]->fail = ptr->go[i];
          que.push(fr->go[i]);
        }
      }
    }
  }
  void query(const string& str) {
    int ans=0,k,len=str.size();
    Node *p=root;
    for(int i=0; i<len; i++){
      k=str[i]-'a';
      while(!p->go[k]&&p!=root)
        p=p->fail;
      p=p->go[k];
      if(!p)p=root;
      Node *temp=p;
      while(temp!=root){
        ans+=temp->cnt;
        for (int k=0; k<temp->indices.size(); ++k)
          counts[temp->indices[k]]++;
        temp=temp->fail;
      }
    }
  }
};

