//Zeynep Tandogan
struct coordinate_node{
	int row,col;
	coordinate_node *next;
};

class fill_empty
{
	private:
		coordinate_node *top;

	public:	
		fill_empty();//constructor
		~fill_empty();//destructor
		bool isEmpty() const;
		void push(int,int);//for adding the coordinate values there are two parameters
		void pop(int&,int&);//for taking back the coordinate values there are two parameters
};