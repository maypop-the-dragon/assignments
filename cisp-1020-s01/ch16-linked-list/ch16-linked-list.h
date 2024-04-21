#include <iostream>

// This is a namespace for my "Bad Linked List,"
// so called because you probably shouldn't use it for any serious project.
namespace bll {
	template<class T> class List;
	template<class T> class Node {
		friend class List<T>;

		private:
			Node<T>* prev;
			Node<T>* next;

			inline Node(Node<T>* prev, T value, Node<T>* next) {
				this->prev = prev;
				this->value = value;
				this->next = next;
			}

			// This is here so the node can't be copied except by list methods.
			inline Node(const Node<T>& node) {
				this->prev = node.prev;
				this->value = node.value;
				this->next = node.next;
			}

		public:
			// The value attached to this node.
			// You can access or change it at any time.* (see List)
			T value;
	};

	// A doubly linked list containing values of type `T`.
	//
	// Do not call the list's methods with nodes that aren't actually in it,
	// as that will cause issues. Also, do not try to access nodes in lists that
	// have already been dropped, since their memory will have been freed.
	template<class T> class List {
		private:
			Node<T>* first_node;
			Node<T>* last_node;

		public:
			// Create a new empty list.
			inline List() {
				this->first_node = NULL;
				this->last_node = NULL;
			}
			inline ~List() {
				Node<T> *current_node = this->first_node;

				while (current_node != NULL) {
					Node<T> *next_node = current_node->next;
					delete current_node;
					current_node = next_node;
				}
			}

			// Check if the list is empty.
			inline bool isEmpty() {
				// If the first node is null, the list is empty.
				return this->first_node == NULL;
			}

			// Attempt to get the first node in the list.
			// If the list is empty, this returns a null pointer.
			inline Node<T>* getFirstNode() {
				return this->first_node;
			}
			// Attempt to get the last node in the list.
			// If the list is empty, this returns a null pointer.
			inline Node<T>* getLastNode() {
				return this->last_node;
			}

			// Get the node immediately after the given one.
			// If there is no next node, this returns a null pointer.
			// If the given node pointer is null, it CRASHES.
			inline Node<T>* getNodeAfter(const Node<T>* previous) {
				return previous->next;
			}
			// Get the node immediately before the given one.
			// If there is no previous node, this returns a null pointer.
			// If the given node pointer is null, it CRASHES.
			inline Node<T>* getNodeBefore(const Node<T>* next) {
				return next->prev;
			}

			// Remove the given node from the list.
			// If the given node pointer is null, this CRASHES.
			inline void remove(Node<T>* node) {
				if (node->prev != NULL)
					node->prev->next = node->next;
				else
					this->first_node = node->next;

				if (node->next != NULL)
					node->next->prev = node->prev;
				else
					this->last_node = node->prev;

				// Delete the newly orphaned node.
				delete node;
			}

			// Add a new node with the given value before the given node.
			// If the given node pointer is null, this CRASHES.
			inline Node<T>* insertValueAfter(Node<T>* previous, T value) {
				// Create a new node with the correct connections.
				Node<T> *new_node = new Node<T>(previous, value, previous->next);

				if (previous->next == NULL)
					// Update the "last node" if this is the new last node.
					this->last_node = new_node;
				else
					// Otherwise update the next node's "previous node."
					previous->next->prev = new_node;

				// Update the previous node's "next node."
				previous->next = new_node;

				return new_node;
			}
			// Add a new node with the given value after the given node.
			// If the given node pointer is null, this CRASHES.
			inline Node<T>* insertValueBefore(T value, Node<T>* next) {
				// Create a new node with the correct connections.
				Node<T> *new_node = new Node<T>(next->prev, value, next);

				if (next->prev == NULL)
					// Update the "first node" if this is the new first node.
					this->first_node = new_node;
				else
					// Otherwise update the previous node's "next node."
					next->prev->next = new_node;

				// Update the next node's "previous node."
				next->prev = new_node;

				return new_node;
			}

			// Add a new node with the given value at the end of the list.
			inline Node<T>* append(T value) {
				if (this->isEmpty())
					return this->last_node = this->first_node = new Node<T>(NULL, value, NULL);
				else
					return this->insertValueAfter(this->last_node, value);
			}
			// Add a new node with the given value at the beginning of the list.
			inline Node<T>* prepend(T value) {
				if (this->isEmpty())
					return this->last_node = this->first_node = new Node<T>(NULL, value, NULL);
				else
					return this->insertValueBefore(value, this->first_node);
			}

			// Print the list to the given stream.
			//
			// This function's source code also serves as a decent example of
			// how one might iterate over one of these linked lists!
            void print(
				std::ostream& destination,
				const char* prefix = "- ",
				const char* postfix = "\n"
			) {
				// If the list is empty, print the fact that it is empty
				// rather than printing nothing.
				if (this->isEmpty()) {
					destination << "[EMPTY]" << postfix;
					return;
				}

				// Otherwise, print the value of each node in order.
				Node<T> *node = this->first_node;
				while (node != NULL) {
					destination << prefix << node->value << postfix;
					node = this->getNodeAfter(node);
				}
			}
	};
}
