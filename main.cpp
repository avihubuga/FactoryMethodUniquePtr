// Copied from StackOverflow anwer: https://stackoverflow.com/a/27302125

#include <iostream>
#include <memory>
#include <map>

using namespace std;

class A;

class A_Factory {
	public:
		A_Factory() {}
		virtual unique_ptr<A> create_unique() = 0;
};

class A {
	public:
		A() {}
		
		static void registerType(int n, A_Factory *factory) {
			get_factory_instance()[n] = factory;
		}

		static unique_ptr<A> create_unique(int n) {
			unique_ptr<A> A_instance = move(get_factory_instance()[n]->create_unique());
			return A_instance;
		}

		virtual void setMyID(int n) {}
		virtual void I_am() { cout << "I am A" << endl; }
		virtual ~A() {}

	protected:
		int MyID;
		static map<int, A_Factory *> &get_factory_instance() {
			static map<int, A_Factory *> map_instance;
			return map_instance;
		}
};

class B: public A {
	public:
		B() {}
		void Foo() {}
		void I_am() { cout << "I am B " << MyID << endl; }
		void setMyID(int n) { MyID = n; }
		~B() {}
};

class B_Factory: public A_Factory {
	public:
		B_Factory() { A::registerType(1, this); }
		unique_ptr<A> create_unique() {
			unique_ptr<A> ptr_to_B(new B);
			return ptr_to_B;
		}
};

static B_Factory b0_factory;

void caller() {}

int main() {
	unique_ptr<A> b1 = move(A::create_unique(1));
	unique_ptr<A> b2 = move(A::create_unique(1));
	b1->setMyID(10);
	b2->setMyID(20);
	b1->I_am();
	b2->I_am();

	return 0;
}
