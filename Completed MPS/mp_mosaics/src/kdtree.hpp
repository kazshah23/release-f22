/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

// ----------------- DONE --------------------
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    else if (first[curDim] > second[curDim]) return false;
    else return (first < second);
}

// ----------------- DONE --------------------
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double potentialD = 0;
     double currD = 0;
     for (unsigned i = 0; i < Dim; i++) {
      potentialD += ((target[i] - potential[i])*(target[i] - potential[i]));
      currD += ((target[i] - currentBest[i])*(target[i] - currentBest[i]));
     }
     if (currD > potentialD) return true;
     if (currD < potentialD) return false;

     return (potential < currentBest);
}


// --------------- CONSTRUCTOR ----------------
template <int Dim> 
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dim)
{
  Point<Dim> pivotValue = kPoints[pivotIndex];
  std::swap(kPoints[pivotIndex], kPoints[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    if (smallerDimVal(kPoints[i], pivotValue, dim)) {
      std::swap(kPoints[storeIndex], kPoints[i]);
      storeIndex++;
    } 
  }
  std::swap(kPoints[right], kPoints[storeIndex]);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::select(int left, int right, int k, int dim) 
{
 while (true) {
  int pivotIndex = partition(left,right,k,dim);
  if (pivotIndex == k) return;
  if (k < pivotIndex) right = pivotIndex - 1;
  else left = pivotIndex + 1;
 }

}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int left, int right, int dim) {
  if (left <= right) {
    int median = ((left +right)/2);
    select(left, right, median, dim);
    KDTreeNode* node = new KDTreeNode(kPoints[median]);
    node -> left = buildTree(left, median - 1, (dim+1)%Dim);
    node -> right = buildTree(median + 1, right, (dim+1)%Dim);
    return node;
    size++;
  } 
  return nullptr;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    
    kPoints = newPoints;
    if (kPoints.size() == 0) return;
    root = buildTree(0, newPoints.size() - 1, 0);
    size = 1;

}

// --------------- FIND NEIGHBOR ----------------

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return find_neighbor(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::find_neighbor(const Point<Dim>& currPoint, int dim, KDTreeNode* currRoot) const
{
    /**
     * @todo Implement this function!
     */
    // ------ Declarations --&-- Base case -------
    Point<Dim> currentBest;
    Point<Dim> competition;
    bool checked_left = false;
    if (currRoot -> left == nullptr && currRoot -> right == nullptr) return currRoot -> point;


    // ------ Part 1: find smallest rectangle that contains target element ------
    if (smallerDimVal(currPoint, currRoot -> point, dim)) {
      if (currRoot -> left) {
        currentBest = find_neighbor(currPoint, (dim + 1) % Dim, currRoot -> left);
        checked_left = true;
      } else {
        currentBest = currRoot -> point;
      }
    } else {
      if (currRoot -> right) {
        currentBest = find_neighbor(currPoint, (dim + 1) % Dim, currRoot -> right);
      } else {
        currentBest = currRoot -> point;
      }
    }
     // ------ Part 2: back traversal to see if any other rectangle could contain a closer point ------

    // Check if theres another point worthy of checking
    if (shouldReplace(currPoint, currentBest, currRoot -> point)) currentBest = currRoot -> point;

    double radius = 0;
    double splitDist = 0;

    for (int i = 0; i < Dim; i++) {
      radius += (currentBest[i] - currPoint[i]) * (currentBest[i] - currPoint[i]);
    }
    splitDist = (currRoot -> point[dim] - currPoint[dim]) * (currRoot -> point[dim] - currPoint[dim]);
    
    // Another point potentially closer
    if (radius >= splitDist) {
      //smallerDimVal(currPoint, currRoot -> point, dim)
      if (checked_left) {
        if (currRoot -> right) {
          competition = find_neighbor(currPoint, (dim + 1) & Dim, currRoot -> right);
        } else {
         return currentBest;
        }
      } else {
        if (currRoot -> left) {
          competition = find_neighbor(currPoint, (dim + 1) % Dim, currRoot -> left);
        } else {
          return currentBest;
        }
      }
      // If it is then replace 
      if (shouldReplace(currPoint, currentBest, competition)) { 
        currentBest = competition;
      } 
    }
    return currentBest;
    
}



// ------ Rule of Zero --------

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  MakeCopy(root, other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this == nullptr) {
    return;
  }
  Clear(root);
  MakeCopy(this->root, rhs.root);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  Clear(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* other) {

}



template <int Dim>
void KDTree<Dim>::MakeCopy(KDTreeNode* Node, KDTreeNode* NodeToCopy) {
  Node = new KDTreeNode();
	Node->point = Node->point;
	copy(Node->left, NodeToCopy->left);
	copy(Node->right, NodeToCopy->right);
}


template <int Dim>
void KDTree<Dim>::Clear(KDTreeNode* Node) {
  if (Node == nullptr) {
    return;
  }
  if (Node->left != nullptr) {
    Clear(Node->left);
  }
  if (Node->right != nullptr) {
    Clear(Node->right);
  }
    delete Node;
    Node = nullptr;
}