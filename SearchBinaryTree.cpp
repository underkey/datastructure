#include<iostream>
#include<cassert>
using namespace std;

template<class T>
struct SearchBinaryTreeNode
{
public:
	SearchBinaryTreeNode(const T& key)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
	{}
	SearchBinaryTreeNode<T>* _left;
	SearchBinaryTreeNode<T>* _right;
	T _key;
};
template<class T>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<T> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}
	SearchBinaryTree(T* a,size_t size,const T& value)
	{
		assert(a);
		size_t index=0;
	 _root=_CreateTree(a,size,index,value);
	}

	SearchBinaryTree(const SearchBinaryTree<T>& t)
	{
	_root=_Copy(t._root);
	}

	~SearchBinaryTree()
	{
		_Destroy(_root);
	}
	bool InsertR(const T& key)//递归
	{
	  return _InsertR(_root,key);
	}
	bool FindR(const T& key)
	{	
		return _FindR(_root,key);
	}
	bool RemoveR(const T& key)
	{
	return _RemoveR(_root,key);
	}
	//bool Insert(const T& key)//非递归
	//{
	//	if(_root==NULL)//为空
	//	{
	//	 Node* root=new Node(key);
	//	 return true;
	//	}
	//	Node* cur = _root;
	//	Node* parent=NULL;
	//	while(cur)
	//	  {
	//			if(cur->_key>key)
	//			{
	//				parent=cur; 
	//				cur=cur->_left ;
	//			}
	//			if(cur->_key<key)
	//			{
	//				parent=cur;
	//				cur=cur->_right ;
	//			}
	//			else if(cur->_key==key)
	//			{
	//				return false;
	//			}
	//	  }
	//	//不存在
	//		 if(parent->_key>key)
	//			{
	//				parent->_left =new Node(key);
	//				return true;
	//			}
	//			if(parent->_key<key)
	//			{
	//				parent->_right =new Node(key);
	//				return true;
	//			}
	//}
	//bool Remove(const T& key)
	//{
	//	if(_root==NULL)
	//		return false;
	//	Node* cur =_root;
	//	Node* parent=NULL;
	//	while(cur)
	//	{
	//		if(key>cur->_key)
	//		{
	//			parent=cur;
	//			cur=cur->_right ;
	//		}
	//		else if(key<cur->_key)
	//		{
	//			parent=cur;
	//			cur=cur->_left ;
	//		}
	//		else
	//		{
	//			if(cur->_left ==NULL||cur->_right ==NULL)
	//			{//左为空或右为空
	//				   if(cur->_left ==NULL)
	//				   {
	//					parent->_right =cur->_right ;
	//					delete cur;
	//					return true;
	//				   }
	//				  if(cur->_right ==NULL)
	//				  {
	//				   parent->_left =cur->_left ;
	//				   delete cur;
	//				   return true;
	//				  }
	//			}
	//			else
	//			{
	//				parent=cur;
	//				while(cur->_left)
	//				{
	//					cur=cur->_left ;
	//				}//寻找最左节点
	//				swap(parent->_key ,cur->_key );
	//				delete cur;
	//				return true;
	//			}
	//	   }
	//	}
	//	return false;
	//}
	
	/*bool Find(const T& key)
	{
		if(_root==NULL)
		return false;
		Node* cur =_root;
		while(cur)
			{
				if(cur->_key<key)
					{
					  cur=cur->_right ;
					}
				else if(cur->_key >key)
					{
					cur=cur->_left;
					}
				else if(cur->_key ==key)
				{
					return true;
				}
			}
		return false;
	}*/

	void InOrder()
	{
	_InOrder(_root);
	cout<<endl;
	}
protected:
	bool _FindR(Node* root,const T& key)
	{
		if(_root==NULL)//为空
		{
		 return false;
	    }
		if(root->_key<key)
		return	_FindR(root->_right ,key);
		if(root->_key>key)
		return	_FindR(root->_left,key);
		else 
		return true;
	}
	 bool _InsertR(Node* &root,const T& key)
	 {
		 if(root==NULL)
		 {
		 root=new Node(key);
		 return true;
		 }
		 if(root->_key <key)
			 return _InsertR(root->_right ,key);
		 if(root->_key >key)
			 return _InsertR(root->_left  ,key);
		 else 
			 return false;
	 }
	bool _RemoveR(Node* &root,const T& key)
	{
		if(root==NULL)
			return false;
		if(root->_key <key)
			 return _RemoveR(root->_right ,key);
		if(root->_key >key)
			 return _RemoveR(root->_left  ,key);
		else
		{
		Node* del=root;
		if(root->_left ==NULL)
			root=root->_right ;
		if(root->_right ==NULL)
			root=root->_left ;
		else
		{
			Node* parent=root;
			Node* minRight=root->_right ;
			while(minRight->_left)//寻找右子树的最左节点
			{
				parent=minRight;
				minRight=minRight->_left ;
			}
			del=minRight;
			root->_key =minRight->_key ;
			if(parent->_left ==minRight)
				parent->_left ==minRight->_right ;
			else
				parent->_right = minRight->_right ;
		}
		return true;
		}

	}
	void _InOrder(Node* root)
	{
		if(root==NULL)
			return;
        _InOrder(root->_left);
		cout<<root->_key <<"，";
		_InOrder(root->_right );
	}

	Node* _Copy(Node* root)
	{
		if(root == NULL)
			return NULL;
		
		Node* newRoot = new Node(root->_key);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);
		return newRoot;
	}
	Node* _CreateTree(T* a, size_t size,
		size_t& index,const T& invalid)
	{
		Node* root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, size, ++index, invalid);
			root->_right = _CreateTree(a, size, ++index, invalid);
		}

		return root; 
	}
	void _Destroy(Node* root)
	{
		if(root==NULL)
			return;
		else
		{
			_Destroy(root->_left );
			_Destroy(root->_right );
			delete root;
		}
	}

protected:
	Node* _root;
};

//void TestSearchTree1()
//{
//	int arr[]={5,3,2,'#','#',4,'#','#',6};
//	SearchBinaryTree<int> t1(arr,9,'#');
//    t1.InOrder ();
//	cout<<"t1.Find (2):"<<t1.Find (2)<<endl;
//	cout<<"t1.Find (9):"<<t1.Find (9)<<endl;
//	cout<<"t1.Insert (7):"<<t1.Insert (7)<<endl;
//	t1.InOrder();
//	cout<<"t1.Insert (2):"<<t1.Insert (2)<<endl;
//	t1.InOrder();
    /*cout<<"t1.RemoveR(7):"<<t1.RemoveR(7)<<endl;
	t1.InOrder();
	cout<<"t1.RemoveR(10):"<<t1.RemoveR(10)<<endl;
	t1.InOrder();
	cout<<"t1.RemoveR(2):"<<t1.RemoveR(2)<<endl;
	cout<<"t1.RemoveR(3):"<<t1.RemoveR(3)<<endl;
	cout<<"t1.RemoveR(4):"<<t1.RemoveR(4)<<endl;
	cout<<"t1.RemoveR(5):"<<t1.RemoveR(5)<<endl;
	cout<<"t1.RemoveR(6):"<<t1.RemoveR(6)<<endl;
	cout<<"t1.RemoveR(7):"<<t1.RemoveR(7)<<endl;
	t1.InOrder();*/
//
//	SearchBinaryTree<int> t2(t1);
//	t2.InOrder();
//}
void TestSearchTree2()
{
	int arr[]={5,3,2,'#','#',4,'#','#',6};
	SearchBinaryTree<int> t1(arr,9,'#');
    t1.InOrder ();
	/*cout<<"t1.FindR(2):"<<t1.FindR(2)<<endl;
	cout<<"t1.FindR(9):"<<t1.FindR(9)<<endl;*/
	cout<<"t1.InsertR(7):"<<t1.InsertR (7)<<endl;
	t1.InOrder();
	cout<<"t1.InsertR(2):"<<t1.InsertR(2)<<endl;
	t1.InOrder();
	cout<<"t1.RemoveR(7):"<<t1.RemoveR(7)<<endl;
	t1.InOrder();
	cout<<"t1.RemoveR(10):"<<t1.RemoveR(10)<<endl;
	t1.InOrder();
	cout<<"t1.RemoveR(2):"<<t1.RemoveR(2)<<endl;
	cout<<"t1.RemoveR(3):"<<t1.RemoveR(3)<<endl;
	cout<<"t1.RemoveR(4):"<<t1.RemoveR(4)<<endl;
	cout<<"t1.RemoveR(5):"<<t1.RemoveR(5)<<endl;
	cout<<"t1.RemoveR(6):"<<t1.RemoveR(6)<<endl;
	cout<<"t1.RemoveR(7):"<<t1.RemoveR(7)<<endl;
	t1.InOrder();

}
int main()
{
  TestSearchTree2();
	system("pause");
return 0;
}