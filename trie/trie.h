#include <iostream>
#include <vector>
//#include <template>

using namespace std;
template <class KeyType, class ValueType>
class TrieNode {
  public:
	TrieNode() : is_str_(false) {}
	TrieNode(const KeyType &k, const ValueType &v)
	{
      char_ = k;
	  value_ = v;
	  is_str_ = false;
	}

	TrieNode(const KeyType &k)
	{
	  char_ = k;
	  is_str_ = false;
	}

	~TrieNode()
	{
	  for (auto &node : children_) {
        delete node;
      }
	}

	// return node of k, create if not present
	inline TrieNode<KeyType, ValueType> *AddChild(const KeyType &k)
	{
	  auto *node = FindChild(k);
	  if (node) {
		return node;
      }
	  node = new TrieNode<KeyType, ValueType>(k);
	  auto it = children_.begin();
	  for (; it != children_.end(); it++) {
		if ((*it)->char_ > k)
			break;
	  }
      children_.insert(it, node);
      return node;
	}

	// binary search of children
	inline const TrieNode<KeyType, ValueType> *FindChild(const KeyType &k) const
	{
	  if (children_.size() == 0) {
        return nullptr;
      }
 	  int l = 0; 
	  int r = children_.size() - 1;
	  do {
		int m = (l + r) / 2;
		if (children_[m]->char_ == k) {
			return children_[m];
		} else if (children_[m]->char_ < k) {
			l = m + 1;
		} else {
			r = m - 1;
		}
      } while(l <= r);
	  return nullptr;
	}

	inline TrieNode<KeyType, ValueType> *FindChild(const KeyType &k)
	{
	  if (children_.size() == 0) {
		return nullptr;
	  }
	  int l = 0; 
	  int r = children_.size() - 1;
	  do {
		int m = (l + r) / 2;
		if (children_[m]->char_ == k) {
			return children_[m];
		} else if (children_[m]->char_ < k) {
			l = m + 1;
		} else {
			r = m - 1;
		}
	  } while(l <= r);
      return nullptr;
	}

	inline void SetIsStr()
	{
	  is_str_ = true;
	}

	inline void SetValue(const ValueType &v)
	{
	  is_str_ = true;
	  value_ = v;
	}

	inline bool IsStr() const
	{
	  return is_str_;
	}
	KeyType char_;
	ValueType value_;
	bool is_str_;
	std::vector<TrieNode *> children_;
	void Dump()
	{
	  int i = 0;
	  vector<TrieNode<KeyType, ValueType> *>  queue;
	  for (auto node : children_) {
		queue.push_back(node);
	  }
	  while (i != queue.size()) {
		auto node = queue[i++];
		cout << node->char_ << " ";
		for (auto n: node->children_) {
          queue.push_back(n);
	}
};

template <class KeyType, class ValueType>
class TrieTree {
  public :
	TrieTree()
	{
 	  root_ = new TrieNode<KeyType, ValueType>();
	}

	~TrieTree()
	{
	  delete root_;
	}

	void Insert(const KeyType *str, size_t length, const ValueType &v)
	{
	  auto node = root_;
	  for (size_t i = 0; i != length; i++) {
		node = node->AddChild(str[i]);
	  }
	  node->SetValue(v);
	}

	bool Find(const KeyType *str, size_t length, ValueType &v) const
	{
	  const auto *node = root_;
	  for (size_t i = 0; i != length; i++) {
		node = node->FindChild(str[i]);
		if (!node) {
			return false;
		}
	  }
      v = node->value_;
	  return node->IsStr();
	}

	bool Find(std::vector<KeyType> &vec) const
	{
	  return false;
	}

	void Dump() {
		root_->Dump();
	}

  private :
	TrieNode<KeyType, ValueType> *root_;
};
