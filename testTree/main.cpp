/****************************************************************************
**				TEST - heterogeneous tree
** this application provides a wrapper for working with binary trees.
** 
** how to run:
**		<appname> [command1] [command2]
**	commands:		
**		-i [filename] - input from file
**		-o [filename] - output to file
**		
** Date: 8.8.2021
** Creator: Konstantin Prigoda 
****************************************************************************/


#include <iostream>
#include <GeterTree.h>
#include <GeterSerialize.h>
#include "ArgsHandlers.h"

using namespace std;

#pragma comment (lib, "HeterTreeLib.lib")

void fill(const std::string& prefix, GeterTreeNode* node, bool isChild)
{
	if (!node)
		return;

	std::cout << prefix << (node->next() ? "├──" : "└──");

	switch (node->type())
	{
		case GeterTreeNode::GTN_DataType::GTN_int64:
			std::cout << node->toInt64();
			break;
		case GeterTreeNode::GTN_DataType::GTN_int:
			std::cout << node->toInt();
		break;

		case GeterTreeNode::GTN_DataType::GTN_float:
			std::cout << node->toFloat();
			break;

		case GeterTreeNode::GTN_DataType::GTN_double:
			std::cout << node->toDouble();
			break;

		case GeterTreeNode::GTN_DataType::GTN_string:
			std::cout << '\"' << node->toString() << '\"';
			break;

		case GeterTreeNode::GTN_DataType::GTN_byte_array:
			std::cout << '\"' << static_cast<const char*>(node->data()) << '\"';
			break;
	}
	std::cout << std::endl;
	
	fill(prefix + (isChild ? "│   " : "    "), node->child(), true);
	fill(prefix, node->next(),  false);
	
}

int main(int argc, char* argv[])
{

	ArgsHandlers a(argc, argv);
	GeterTree tree;

	a.insert(
		"-i",
		"to load from file. (-i [filename])",
		[&tree](const std::string& arg)
		{
			GeterSerializeBinary sb(&tree);
			sb.load(arg);
		}
	);

	a.insert(
		"-o",
		"to save to file. (-o [filename])",
		[&tree](const std::string& arg)
		{
			GeterSerializeBinary sb(&tree);
			sb.save(arg);
		}
	);



	

	/* Example initialize tree 

	//append 8
	tree.append(nullptr, GeterTreeVariant(8));

	//append "bar"
	{
		GeterTreeNode* node_bar = tree.append(tree.node(), GeterTreeVariant(std::string("bar")));

			tree.append(
				tree.append(node_bar, GeterTreeVariant(float(2.015))),
														GeterTreeVariant(9));

			tree.append(node_bar, GeterTreeVariant(2015));
			tree.append(node_bar, GeterTreeVariant(std::string("2015")));
	}

	//append "baz"
	{
		GeterTreeNode* node_baz = tree.append(tree.node(), GeterTreeVariant(std::string("baz")));

			
			tree.append(node_baz, GeterTreeVariant(std::string("foo")));
			tree.append(
				tree.append(node_baz, GeterTreeVariant(double(6.28318))),
				GeterTreeVariant(std::string("hello")));
					

	}
	*/

	a.exec();


	fill("", tree.node(), false);
	return 0;
}