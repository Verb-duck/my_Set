#include <iostream>

template <class T> 
class my_set {
public:
	my_set();
	bool emplase(const T& date);
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
	size_t size = 0;
};

template<class T>
my_set<T>::my_set()
{
}

template<class T>
bool my_set<T>::emplase(const T& date)
{
	if (cell_head == NULL) 
	{
		cell_head = new Cell<T>( date);
		size++;
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
					size++;
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
					size++;
					return true;
				}
			}
		}
	}
}

int main()
{
	my_set <int> set;
}

