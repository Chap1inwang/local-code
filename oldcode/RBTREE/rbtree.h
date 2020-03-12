#ifndef _RBTREE_H_
#define _RBTREE_H

#include<iostream>
#include<iomanip>

using namespace std;

enum RBTColor{RED, BLACK};

template <class T>
class RBTNode{
    public:
        RBTColor color;    // 颜色
        T key;            // 关键字(键值)
        RBTNode *left;    // 左孩子
        RBTNode *right;    // 右孩子
        RBTNode *parent; // 父结点

        RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value),color(c),parent(),left(l),right(r) {}
};

template <class T>
class RBTree {
    private:
        RBTNode<T> *mRoot;    // 根结点

    public:
        RBTree();
        ~RBTree();

        // 前序遍历"红黑树"
        void preOrder() const;
        // 中序遍历"红黑树"
        void inOrder() const;
        // 后序遍历"红黑树"
        void postOrder() const;

        // (递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* search(T key);
        // (非递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* iterativeSearch(T key);

        // 查找最小结点：返回最小结点的键值。
        T minimum();
        // 查找最大结点：返回最大结点的键值。
        T maximum();

        // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
        RBTNode<T>* successor(RBTNode<T> *x);
        // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
        RBTNode<T>* predecessor(RBTNode<T> *x);

        // 将结点(key为节点键值)插入到红黑树中
        void insert(T key);

        // 删除结点(key为节点键值)
        void remove(T key);

        // 销毁红黑树
        void destroy();

        // 打印红黑树
        void print();
    private:
		RBTNode<T>* tree_minimum(RBTNode<T>* root);
		void RB_Transplant(RBTNode<T>* &root,RBTNode<T>* u,RBTNode<T>* v);
        // 前序遍历"红黑树"
        void preOrder(RBTNode<T>* tree) const;
        // 中序遍历"红黑树"
        void inOrder(RBTNode<T>* tree) const;
        // 后序遍历"红黑树"
        void postOrder(RBTNode<T>* tree) const;

        // (递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* search(RBTNode<T>* x, T key) const;
        // (非递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

        // 查找最小结点：返回tree为根结点的红黑树的最小结点。
        RBTNode<T>* minimum(RBTNode<T>* tree);
        // 查找最大结点：返回tree为根结点的红黑树的最大结点。
        RBTNode<T>* maximum(RBTNode<T>* tree);

        // 左旋
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
        // 右旋
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
        // 插入函数
        void insert(RBTNode<T>* &root, RBTNode<T>* node);
        // 插入修正函数
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
        // 删除函数
        void remove(RBTNode<T>* &root, RBTNode<T> *node);
        // 删除修正函数
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node,RBTNode<T>* parent);

        // 销毁红黑树
        void destroy(RBTNode<T>* &tree);

        // 打印红黑树
        void print(RBTNode<T>* tree, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};



template<class T>
RBTree<T>::RBTree():mRoot(NULL){}

template<class T>
RBTree<T>::~RBTree(){
	destroy();
}

template<class T>
void RBTree<T>::postOrder(RBTNode<T>* node) const{
	if(node!=NULL){
		postOrder(node->left);
		postOrder(node->right);
		cout<<node->key<<" ";
	}
	return;
}

template<class T>
void RBTree<T>::inOrder(RBTNode<T>* node) const{
	if(node!=NULL){
		inOrder(node->left);
		cout<<node->key<<" ";
		inOrder(node->right);
	}
	return;
}

template<class T>
void RBTree<T>::preOrder(RBTNode<T>* node) const{
	if(node!=NULL){
		cout<<node->key<<" ";
		preOrder(node->left);
		preOrder(node->right);
	}
	return;
}


template<class T>
void RBTree<T>::preOrder() const{
	preOrder(this->mRoot);
}

template<class T>
void RBTree<T>::inOrder() const{
	inOrder(this->mRoot);
	return;
}

template<class T>
void RBTree<T>::postOrder() const{
	postOrder(this->mRoot);
	return;
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key){
	return search(this->mRoot,key);
}

template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* mRoot, T key) const{
	if(mRoot==NULL) return NULL;
	if(mRoot->key==key) return mRoot;
	else if(mRoot->key<key){
		return search(mRoot->right,key);
	}
	return search(mRoot->left,key);
}

template<class T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key){
	return iterativeSearch(this->mRoot,key);
}


template<class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* mRoot,T key) const{
	if(mRoot==NULL) return NULL;
	if(mRoot->key==key){
		return mRoot;
	}
	else if(mRoot->key>key){
		return iterativeSearch(mRoot->left,key);
	}
	return iterativeSearch(mRoot->right,key);
}

template<class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* node)  {
	if(node==NULL) return NULL;
	while(node->left!=NULL){
		node=node->left;
	}
	return node;
}

template<class T>
T RBTree<T>::minimum(){
	RBTNode<T>* p=minimum(this->mRoot);
	if(p!=NULL){
		return p->key;
	}
	return (T)NULL;
}

template<class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* node)  {
	if(node==NULL) return NULL;
	while(node->right!=NULL){
		node=node->right;
	}
	return node;
}

template<class T>
T RBTree<T>::maximum(){

	RBTNode<T>* p=maximum(this->mRoot);
	if(p!=NULL){
		return p->key;
	}
	return (T)NULL;
}

template<class T>
RBTNode<T>* successor(RBTNode<T>* node){
	if(node->right!=NULL){
		return minimum(node->right);
	}
	//如果node没有右孩子
	//一、node是一个左孩子，其后继节点为其父节点
	//二、node是一个右孩子，其后集结点为第一个使node在其左子树的祖宗节点
	RBTNode<T>* p=node->parent;
	while((p!=NULL)&&(node==p->right)){
		node=p;
		p=p->parent;
	}
	return p;
}

template<class T>
RBTNode<T>* predecessor(RBTNode<T>* node){
	if(node->left){
		return maximum(node->left);
	}
	RBTNode<T>* p=node->parent;
	while((p!=NULL)&&(node==p->left)){
		node=p;
		p=p->parent;
	}
	return p;
}


/* 
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
    // 设置x的右孩子为y
    RBTNode<T> *y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }
    
    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
}

/* 
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
    // 设置x是当前节点的左孩子。
    RBTNode<T> *x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
		RBTNode<T> *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
		// Case 2条件：叔叔是黑色，且当前节点是右孩子
		if(!uncle||rb_is_black(uncle)){
			if (parent->right == node)
            		{
                		RBTNode<T> *tmp;
                		leftRotate(root, parent);
                		tmp = parent;
                		parent = node;
                		node = tmp;
            		}
			// Case 3条件：叔叔是黑色，且当前节点是左孩子。
            		rb_set_black(parent);
            		rb_set_red(gparent);
            		rightRotate(root, gparent);
		}
          } 
          else{
                RBTNode<T> *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
		if(!uncle||rb_is_black(uncle)){
			if (parent->left == node)
            		{
                		RBTNode<T> *tmp;
                		rightRotate(root, parent);
                		tmp = parent;
                		parent = node;
                		node = tmp;
            		}
            		rb_set_black(parent);
            		rb_set_red(gparent);
            		leftRotate(root, gparent);
		}
          }
    }
    rb_set_black(root);
}


/* 
 * 将结点插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 插入的结点        // 对应《算法导论》中的node
 */
template <class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y!=NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    // 2. 设置节点的颜色为红色
    node->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    insertFixUp(root, node);
}

/* 
 * 将结点(key为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 插入结点的键值
 */
template <class T>
void RBTree<T>::insert(T key)
{
    RBTNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new RBTNode<T>(key,RED,NULL,NULL,NULL)) == NULL)
        return ;

    insert(mRoot, z);
}


template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}


//删除函数（内部接口）
template<class T>
void RBTree<T>::remove(RBTNode<T>* &root,RBTNode<T>* node){
	RBTNode<T>* pnode=rb_parent(node);
	RBTNode<T>*  n=node;//记录实际删除节点的子树，实际删除节点的子树最多只有一个
	RBTColor col=rb_color(node);
	if(node->left==NULL){  //直接拿右子树放在node原来的位置上
		n=node->right;
		RB_Transplant(root,node,node->right);
	}
	else if(node->right==NULL){ //直接拿左子树放在node原来的位置上
		n=node->left;
		RB_Transplant(root,node,node->left);
	}
	else{  //node有两个子树的时候
		RBTNode<T>* y=tree_minimum(node->right);
		n=y->right;
		pnode=rb_parent(y);
		col=y->color;
		//把node的右子树与y连接
		if(y->parent==node){
			n->parent=y;
		}
		else{
			RB_Transplant(root,y,y->right);
			y->right=node->right;
			y->right->parent=y;
		}
		//把node父节点与y连接
		RB_Transplant(root,node,y);
		//连接node左子树与y节点
		y->left=node->left;
		y->left->parent=y;
		//y占据node位置以后着上node的颜色
		y->color=node->color;
	}
	//需要delete node节点？
	//如果删除y的是黑色节点，需要补充调用修正函数
	if(col==BLACK){
		removeFixUp(root,n,pnode);
	}
	if(node){
		delete node;
	}
	return;
}

template<class T>
RBTNode<T>* RBTree<T>::tree_minimum(RBTNode<T>* root){
	if(root==NULL){
		return NULL;
	}
	while(root->left){
		root=root->left;
	}
	return root;
}


template<class T>
void RBTree<T>::RB_Transplant(RBTNode<T>* &root,RBTNode<T>* u,RBTNode<T>* v){
	if(u->parent==NULL){
		root=v;
	}
	else if(u==u->parent->left){
		u->parent->left=v;
	}
	else{
		u->parent->right=v;
	}
	if(v){
		v->parent=u->parent;
	}
	return;
}


/* 
 * 删除红黑树中键值为key的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 */
template <class T>
void RBTree<T>::remove(T key)
{
    RBTNode<T> *node; 

    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = search(mRoot, key)) != NULL)
        remove(mRoot, node);
}

/*
 * 销毁红黑树
 */
template <class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree=NULL;
}

template <class T>
void RBTree<T>::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << setw(2) << tree->key << "(B) is root" << endl;
        else                // tree是分支节点
            cout << setw(2) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void RBTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}



#endif
