#include <optional>

template<class T> class Stack;

template<class T> class StackEntry {
	friend class Stack<T>;

	private:
		StackEntry<T>* below;
		T value;

		inline StackEntry(StackEntry<T>* below, T value) {
			this->below = below;
			this->value = value;
		}
};

// A dynamic stack containing values of type T.
template<class T> class Stack {
	private:
		StackEntry<T>* top;

	public:
		// Create a new, empty stack.
		inline Stack() {
			this->top = NULL;
		}

		inline ~Stack() {
			while (this->top != NULL)
				this->pop();
		}

		// Pop one item from the stack, if there are any.
		// If there are no items, this function returns nothing.
		inline std::optional<T> pop() {
			if (this->top == NULL)
				return std::nullopt;

			T value = this->top->value;
			StackEntry<T> *new_top = this->top->below;

			delete this->top;
			this->top = new_top;

			return std::optional<T>{value};
		}

		// Push one item onto the stack.
		inline void push(T value) {
			this->top = new StackEntry<T>(this->top, value);
		}

		// Execute a function for each item on the stack,
		// starting at the top, going downwards, and ending at the bottom.
		//
		// The function can read the items, but not write them.
		inline void forEach(void(*function)(const T&)) {
			StackEntry<T> *entry = this->top;

			while (entry != NULL) {
				function(entry->value);
				entry = entry->below;
			}
		}
};
