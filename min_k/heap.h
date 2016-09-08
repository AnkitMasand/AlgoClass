#ifndef HEAP_H
#define HEAP_H
#define MAXLEN 100000
class Heap{
	private:
		int A[MAXLEN];
		int last;
		void top_down_heapify(int pos);
		void bottom_up_heapify(int pos);
	public:
		Heap(){
                        for(int i=0;i<MAXLEN;i++)
                                A[i]=0;
                        last=0;
                }
		void add_elem(int i);
		int delete_max();
		int get_max();
		void display();
		void decrease_key(int pos,int val);
};

#endif
