#pragma once
#include <vector>


template <class KeyData, class Data>
class AVL_Tree  {
  struct TreeNode {
    Data value;
    KeyData key;

    TreeNode* left;
    TreeNode* right;
    TreeNode* top;

    int Height;
    TreeNode() : key(KeyData(0)), left(nullptr), right(nullptr), top(nullptr), Height(0){};

    TreeNode(KeyData key, Data value)
        : value(value), key(key), left(nullptr), right(nullptr), top(nullptr), Height(0){};
  };

  using it = TreeNode*;
  it start_root;


  std::vector<Data> vec_;


  it node_look_at;
  it minValueNode(it node) {
    it current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  int getHeight(it node) {
    if (node == nullptr) {
      return 0;
    }
    return node->Height;
  }

  it insertNode(it& node, KeyData key, Data value) {
    if (node == nullptr) {
      node = new TreeNode(key, value);
      return node;
    }

    if (key < node->key) {
      node->left = insertNode(node->left, key, value);
      node->left->top = node;
    } else if (key > node->key) {
      node->right = insertNode(node->right, key, value);
      node->right->top = node;
    }

    node->Height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
      return (node == start_root) ? (start_root = rightRotate(node)) : rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
      return (node == start_root) ? (start_root = leftRotate(node)) : leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return (node == start_root) ? (start_root = rightRotate(node)) : rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return (node == start_root) ? (start_root = leftRotate(node)) : leftRotate(node);
    }
    return node;
  }

  it removeNode(it& root, KeyData key) {
    if (root == nullptr) return root;

    if (key < root->key) {
      root->left = removeNode(root->left, key);
    } else if (key > root->key) {
      root->right = removeNode(root->right, key);
    } else {
      if (root->left == nullptr || root->right == nullptr) {
        it temp = (root->left) ? root->left : root->right;

        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        } else {
          *root = *temp;
        }
        temp = nullptr;

      } else {
        it temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = removeNode(root->right, temp->key);
      }
    }

    if (root == nullptr) return root;

    root->Height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }

    return root;
  }

  
  it search(KeyData key) {
    TreeNode* temp = start_root;
    if (temp != nullptr) {
      while (1) {
        if (temp->key == key) {
          return temp;
        }

        if (temp->key > key)
          if (temp->left != nullptr)
            temp = temp->left;
          else
            return nullptr;

        if (temp->key < key)
          if (temp->right != nullptr)
            temp = temp->right;
          else
            return nullptr;
      }
    }
  }


  it rightRotate(it p) {
    auto q = p->left;
    p->left = q->right;
    if (p->left != nullptr) p->left->top = p;
    q->right = p;
    q->top = p->top;
    p->top = q;
    p->Height = 1 + std::max(getHeight(p->left), getHeight(p->right));
    q->Height = 1 + std::max(getHeight(q->left), getHeight(q->right));
    return q;
  }
  int getBalance(it node) {
    if (node == nullptr) {
      return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
  }
  it leftRotate(it q) {
    auto p = q->right;
    q->right = p->left;
    if (q->right != nullptr) q->right->top = q;
    p->left = q;
    p->top = q->top;
    q->top = p;
    q->Height = 1 + std::max(getHeight(q->left), getHeight(q->right));
    p->Height = 1 + std::max(getHeight(p->left), getHeight(p->right));

    return p;
  }
  it bigRightRotate(it node) {
    it x = node;
    node = rightRotate(x);
    return leftRotate(node);
  }
  it bigLeftRotate(it node) {
    it y = node;
    node = leftRotate(y);
    return rightRotate(node);
  }

  void destroyTree(it node) {
    if (node == nullptr) {
      return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
    node = nullptr;
  }
  double calculate_single_seg(double x1, double y1, double x2, double y2, double x) {
    if (x1 == x2) {
      std::cout << x1 << "  " << y1 << std::endl << x2 << "  " << y2;
      throw std::invalid_argument("The points have the same x-coordinate; the slope is undefined.");
    }
    return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
  }

  void re_calculate_tree_nodes_at_point(double x) {
    std::vector<TreeNode*> nodes;
    collect_nodes_inorder(start_root, nodes);
    start_root = nullptr;                      


    for (auto node : nodes) {
      double x1 = node->value.start.x;
      double y1 = node->value.start.y;
      double x2 = node->value.stop.x;
      double y2 = node->value.stop.y;

      if (x1 != x2) {
        node->key = calculate_single_seg(x1, y1, x2, y2, x);
      } else {
        node->key = y1; 
      }
    }


    std::sort(nodes.begin(), nodes.end(), [](TreeNode* a, TreeNode* b) { return a->key < b->key; });

    start_root = build_balanced_tree(nodes, 0, nodes.size() - 1);
  }


  void collect_nodes_inorder(it node, std::vector<it>& nodes) {
    if (node == nullptr) return;
    collect_nodes_inorder(node->left, nodes);
    nodes.push_back(node);
    collect_nodes_inorder(node->right, nodes);
  }

  it build_balanced_tree(std::vector<it>& nodes, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    it node = nodes[mid];

    node->left = build_balanced_tree(nodes, start, mid - 1);
    if (node->left) node->left->top = node;

    node->right = build_balanced_tree(nodes, mid + 1, end);
    if (node->right) node->right->top = node;

    node->Height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    return node;
  }


  it find_t(it root) {
    if (root->right != nullptr) {
      root = root->right;
      while (root->left != nullptr) {
        root = root->left;
      }
      return root;
    } else {
      while (root->top != nullptr && root == root->top->right) {
        root = root->top;
      }
      return root->top;  
    }
  }

  it find_d(it root) {
    if (root->left != nullptr) {
      root = root->left;
      while (root->right != nullptr) {
        root = root->right;
      }
      return root;
    } else {
      while (root->top != nullptr && root == root->top->left) {
        root = root->top;
      }
      return root->top;
    }
  }

 public:
  AVL_Tree() {
    start_root = nullptr;
    vec_.reserve(15);
  }
  AVL_Tree(KeyData key, Data val) {
    start_root = new TreeNode(key, val);
    flag_not_null = true;
  }
  void insert(KeyData key, Data& val) {
    insertNode(start_root, key, val);
    vec_.push_back(val);

  }
  void remove(KeyData key) {
      removeNode(start_root, key); 
      for (auto &&lhs = vec_.begin(), rhs = vec_.end(); lhs != rhs; ++lhs) {
        if (lhs->stop.y ==key ){
          vec_.erase(lhs);
          break;
        }
      }
  }

  void find_segs_for_checking(double x, double key, std::vector<Data*>& vec) {
    re_calculate_tree_nodes_at_point(x);
    using it = TreeNode*;
    it look_at_loc = search(key);//O(log(n))
    if (look_at_loc != nullptr) {
      vec[0] = &look_at_loc->value;

      it upper = find_t(look_at_loc);//O(log(n))
      it lower = find_d(look_at_loc);//O(log(n))
      vec[1] = (upper) ? &upper->value : nullptr;
      vec[2] = (lower) ? &lower->value : nullptr;
    } 
  }
  ~AVL_Tree() { 
      destroyTree(start_root);
  }
};