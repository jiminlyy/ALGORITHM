#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

typedef struct node {
    struct node* l;
    int key;
    struct node* r;
}Node;

Node* TreeInit() {
    Node* head;
    head = (Node*)malloc(sizeof * head);
    head->l = NULL;
    head->r = NULL;
    head->key = 0;  
    return head;
}

Node* TreeSearch(Node* head, int xkey) {
    Node* t;
    t = head->r; 
    while (t != NULL) {
        if (xkey == t->key)return t;
        else if (xkey < t->key)t = t->l; 
        else t = t->r;                  
    }
  
    return NULL;
}

void TreeDelete(Node* head, int xkey) {
    Node* p, * t;
    Node* s, * ps;

    p = head;
    t = head->r; 
    while (t != NULL&& t->key != xkey) {
        p = t;
        if (xkey < t->key) {
            t = t->l;
        }
        else {
            t = t->r;
        }
    }

    if (t == NULL) {
        cout << xkey << " 값 없음" << endl;
        return;
    }

    if (t->l == NULL) {
        if (t == p->r) p->r = t->r; 
        else p->l = t->r;           
        free(t);
    }
   
    else if (t->r == NULL) {
        if (t == p->r) p->r = t->l;
        else p->l = t->l;
        free(t);
    }
    
    else {
        ps = t;      
        s = t->r;    
        while (s->l != NULL) { 
            ps = s;
            s = s->l;
        }
        t->key = s->key;

        if (s == ps->r) ps->r = s->r; 
        else ps->l = s->r;         

        free(s);
    }
}

void printTree(Node* head) {
    if (head == NULL || head->r == NULL) {
        cout << "트리가 비어 있음" << endl;
        return;
    }

    stack<Node*> node_s;
    stack<int> space_s;    

    Node* current_node = head->r; 
    int current_space = 0;
    const int STEP = 6; 

    while (current_node != NULL || !node_s.empty()) {
        while (current_node != NULL) {
            node_s.push(current_node);
            space_s.push(current_space);

            current_space += STEP;
            current_node = current_node->r;
        }

       
        current_node = node_s.top();
        node_s.pop();

        current_space = space_s.top();
        space_s.pop();

        
        for (int i = 0; i < current_space; i++) {
            cout << " ";
        }

        cout << current_node->key << "\n"; 
        
        current_node = current_node->l;
        current_space += STEP;
    }
    cout << endl;
}
int main() {
    int keys[] = { 26,12,8,10,22,16,14,18,20,15 };
    int n = sizeof(keys) / sizeof(keys[0]);
    Node* k = TreeInit();

    cout << "삽입할 키: ";
    for (int i = 0; i < n; ++i) {
        cout << keys[i] << " ";
        Node* p = k, * t = k->r;
        while (t != NULL) {
            p = t;
            if (keys[i] == t->key) break;
            else if (keys[i] < t->key) t = t->l;
            else t = t->r;
        }
        if (t == NULL) {
            t = (Node*)malloc(sizeof(Node));
            t->key = keys[i]; 
            t->l = NULL; 
            t->r = NULL;
            if (p == k) p->r = t;
            else if (keys[i] < p->key) p->l = t;
            else p->r = t;
        }
    }
    cout << "\n\n";
    printTree(k);

    cout << "\n16의 키 값 구하기" << endl;
    Node *mm = TreeSearch(k, 16);
    cout << "오른쪽 "<< mm->r->key << " 왼쪽 " << mm->l->key << endl;
    
    cout << "\n12를 삭제 한 트리\n";
    TreeDelete(k, 12);
    printTree(k);

    cout << "\n16의 키 값 구하기" << endl;
    Node* mk = TreeSearch(k, 16);
    cout << "오른쪽 " << mk->r->key << " 왼쪽 " << mk->l->key << endl;
    cout << "\n최악의 시간 복잡도를 가지는 예시" << endl;

    int keys_worst[] = { 10,20,30,40,50,60,70,80 };
    int nw = sizeof(keys_worst) / sizeof(keys_worst[0]);
    Node* kw = TreeInit();

    cout << "삽입할 키: ";
    for (int i = 0; i < nw; ++i) {
        cout << keys_worst[i] << " ";
        Node* pw = kw, * tw = kw->r;
        while (tw != NULL) {
            pw = tw;
            if (keys_worst[i] == tw->key) break;
            else if (keys_worst[i] < tw->key) tw = tw->l;
            else tw = tw->r;
        }

        if (tw == NULL) {
            tw = (Node*)malloc(sizeof(Node));
            tw->key = keys_worst[i]; 
            tw->l = NULL; 
            tw->r = NULL;
            if (pw == kw) pw->r = tw;
            else if (keys_worst[i] < pw->key) pw->l = tw;
            else pw->r = tw;
        }
    }
    cout << "\n\n";
    printTree(kw);

    return 0;
}