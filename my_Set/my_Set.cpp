#include <iostream>

template <class T> 
class my_set {
private:
	template <class T>
	class Cell;
public:
	my_set();
	~my_set();
	void clear();
	bool insert(const T& date);
	size_t size() const;
	
private:

	template <class T>
	class Cell {
	public:
		Cell* cell_left;
		Cell* cell_right;
		T date;
		Cell (const T& date = T(), Cell* cell_left = nullptr, Cell* cell_right = nullptr) {
			this->date = date;
			this->cell_left = cell_left;
			this->cell_right = cell_right;
		}
	};
	Cell<T>* cell_head = nullptr;
	size_t lenght = 0;
};

template<class T>
my_set<T>::my_set()
{
}

template<class T>
my_set<T>::~my_set()
{
}

template<class T>
void my_set<T>::clear()
{	
	//if(cell_head->cell_right != NULL)
		Cell<T>* go_right = cell_head ->cell_right;
	//if(cell_head->cell_left != NULL)
		Cell<T>* go_left = cell_head->cell_left;
	if (cell_head != NULL)
	{
		delete cell_head;
		lenght--;
	}
	if (go_left != NULL)
	{
		cell_head = go_left;
		this->clear();
	}
	if (go_right != NULL)
	{
		cell_head = go_right;
		this->clear();
	}

}

template<class T>
bool my_set<T>::insert(const T& date)
{
	if (cell_head == NULL)
	{
		cell_head = new Cell<T>(date);
		lenght++;
		return true;
	}
	else
	{
		Cell<T>* cell_now = cell_head;
		while (1)
		{
			if (date == cell_now->date)
			{
				return false;
			}
			else if (date < cell_now->date)			//идём влево
			{
				if (cell_now->cell_left != NULL)
				{
					cell_now = cell_now->cell_left;
					continue;
				}
				else
				{
					cell_now->cell_left = new Cell<T>(date);
					lenght++;
					return true;
				}
			}
			else									//идём вправо
			{
				if (cell_now->cell_right != NULL)
				{
					cell_now = cell_now->cell_right;
					continue;
				}
				else
				{
					cell_now->cell_right = new Cell<T>(date);
					lenght++;
					return true;
				}
			}
		}
	}
}


template<class T>
size_t my_set<T>::size() const
{
	return lenght;
}


int main()
{
	my_set <int> set;
	set.insert(5);
	set.insert(6);
	set.insert(2);
	set.insert(1);
	set.insert(3);
	set.insert(8);
}

