#include <iostream>
#include "GeterTree.h"
#include "GeterSerialize.h"

using namespace std;

int main(int argc, char* argv[])
{
	GeterTree tree;
	GeterTreeNode* tnode1,*tnode2;
	
	tnode1 = tree.append(nullptr, GeterTreeVariant(8));

	tnode2 = tree.append(tnode1, GeterTreeVariant(std::string("bar")));
	tnode1 = tree.append(tnode1, GeterTreeVariant(std::string("baz")));

	tnode2 = tree.append(tnode2, GeterTreeVariant(float(2.015)));
	tree.append(tnode2, GeterTreeVariant(2015));
	tree.append(tnode2, GeterTreeVariant(std::string("2015")));
	tree.append(tnode2, GeterTreeVariant(9));
	
	tree.append(tnode1, GeterTreeVariant(std::string("foo")));
	tnode1 = tree.append(tnode1, GeterTreeVariant(double(6.28318)));
	tree.append(tnode1, GeterTreeVariant(std::string("hello")));

	
	tree.clear();
	return 0;
}