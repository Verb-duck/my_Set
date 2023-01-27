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
	void print();
	bool insert(const T& date);
	bool erase(const T& date);
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
	this->clear();
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
bool my_set<T>::erase(const T& date)
{
	if (lenght == 1)
	{
		delete cell_head;
		cell_head = nullptr;
		lenght--;
		return true;
	}
	if (lenght == 0)
		return false;

	Cell<T>* previos_cell = nullptr;
	Cell<T>* now_cell = cell_head;
	bool flag_turn_right;
	while (now_cell->date != date)						 //ищем нужную ячейку
	{	
		previos_cell = now_cell;
		if (date > now_cell->date)						 //идём вправо
		{
			now_cell = now_cell->cell_right;
			flag_turn_right = true;						 //запоминаем куда повернули последний раз
		}
		else											 //идём влево 
		{
			now_cell = now_cell->cell_left;
			flag_turn_right = false;					 //запоминаем куда повернули последний раз
		}
	}
	if (flag_turn_right)								 //если повернули направо
	{
		previos_cell->cell_right = now_cell->cell_right; //вписываем правый хвост в праввый адрес предыдешей ячейки
		if (now_cell-> cell_left != NULL)				 //если есть левое ветвление от удаляемой ячейки
		{
			Cell<T>* cell_temp = now_cell->cell_right;
			while (cell_temp->cell_left != NULL)		 //ищем свободный левый адрес в правом хвосте
			{											 //тк левый хвост по умолчанию самый малый, всегда  
				cell_temp = cell_temp->cell_left;		 //поворачиваем налево
			}
			cell_temp->cell_left = now_cell->cell_left;
		}
		delete now_cell;
		lenght--;
		return true;
	}
	else												 //если повернули налево
	{
		previos_cell->cell_left = now_cell->cell_right; //вписываем правый хвост в левый адрес предыдешей ячейки
		if (now_cell->cell_left != NULL)				 //если есть левое ветвление от удаляемой ячейки
		{
			Cell<T>* cell_temp = now_cell->cell_right;
			while (cell_temp->cell_left != NULL)		 //ищем свободный левый адрес в правом хвосте
			{											 //тк левый хвост по умолчанию самый малый, всегда  
				cell_temp = cell_temp->cell_left;		 //поворачиваем налево
			}
			cell_temp->cell_left = now_cell->cell_left;
		}
		delete now_cell;
		lenght--;
		return true;
	}
	
}


template<class T>
size_t my_set<T>::size() const
{
	return lenght;
}

template<class T>
void my_set<T>::clear()
{
	Cell<T>* go_right = cell_head->cell_right;
	Cell<T>* go_left = cell_head->cell_left;
	if (cell_head != NULL)
	{
		delete cell_head;
		cell_head = nullptr;
		lenght--;
	}
	if (go_left != NULL)			//смещаемся влево до упора
	{
		cell_head = go_left;
		this->clear();
	}
	if (go_right != NULL)			//смещаемся вправо,
	{
		cell_head = go_right;
		this->clear();
	}
}

template<class T>
void my_set<T>::print()
{
	Cell<T>* go_right = cell_head->cell_right;
	Cell<T>* go_left = cell_head->cell_left;
	if (cell_head != NULL)
	{
		std::cout << cell_head->date << std::endl;
	}
	if (go_left != NULL)			//смещаемся влево до упора
	{
		cell_head = go_left;
		this->print();
	}
	if (go_right != NULL)			//смещаемся вправо,
	{
		cell_head = go_right;
		this->print();
	}
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
	set.erase(2);
	set.print();
}

