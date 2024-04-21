#include "./ch16-linked-list.h"
#include <iostream>

int main() {
	// {}
	bll::List<int> list;

	// { 0 }
	list.append(0);
	// { 1000, 0 }
	list.prepend(1000);
	// { 0 }
	list.remove(
		// 1000
		list.getFirstNode()
	);

	// { 0, 3 }
	list.insertValueAfter(
		// 0
		list.getLastNode(),
		3
	);
	// { -3, 0, 3 }
	list.insertValueBefore(
		-3,
		// 0
		list.getFirstNode()
	);

	// { -3, 0, 2, 3 }
	list.insertValueBefore(
		2,
		// 3
		list.getLastNode()
	);
	// { -3, -2, 0, 2, 3 }
	bll::Node<int> *negative_two = list.insertValueAfter(
		// -3
		list.getFirstNode(),
		-2
	);

	// { -3, -2, 0, 1, 2, 3 }
	list.insertValueBefore(
		1,
		// 2
		list.getNodeBefore(
			// 3
			list.getLastNode()
		)
	);
	// { -3, -2, -1, 0, 1, 2, 3 }
	list.insertValueAfter(
		// -2
		negative_two,
		-1
	);

	list.print(std::cout);

	return 0;
}
