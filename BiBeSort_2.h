struct TestSystem
{
	struct Result
	{
		double erst, zweiten, ratio;

		template<class Ostream>
		Ostream& print(Ostream& os) const
		{
			os << erst << '/' << zweiten << " = " << ratio;
			return os;
		}
	};
	std::vector<Result> results;
	void print_results() {
		int size = results.size();
		for (int i = 0; i < size; i++) {
			results[i].print<std::ostream>(std::cout);
			std::cout << std::endl;
		}
	}
	template<typename Functor>
	double vremya(Functor f, int n) const
	{
		umnas::chasici<std::chrono::system_clock> watch;
		watch.start();
		for (int i = 0; i < n; ++i) {
			f();
			f.reset();
		}
		watch.stop();
		std::chrono::duration<double, std::ratio<1, 1000>> dur = watch.duration();
		return dur.count();
	}

	template<
		typename Functorerst,
		typename Functorzweiten
	>
		Result operator()(
			Functorerst erst,
			Functorzweiten zweiten,
			int n = 100000, int nn = 1
			)
	{
		Result res;
		results.clear();
		results.reserve(nn);
		for (int i = 0; i < nn; ++i)
		{
			res.erst = vremya(erst, n);
			res.zweiten = vremya(zweiten, n);
			res.ratio = res.erst / res.zweiten;
			results.push_back(res);
		}
		return res;
	}
};
using namespace std;
template <class T> class my_array {
	T* veca; //массив типа Т
	T* veca_for_reset; //копия массива veca для сброса
	int gr; //количество элементов в массиве
	atomic_int* adt2; //массив целых чисел, которые можно безопасно использовать в нескольких потоках
	int adt; //максимальное число потоков, которое целесообразно использовать для сортировки Шелла
public:
	int get_adt() { return adt; }
	my_array(T* veca1, int size) {
		veca = new T[size];
		veca_for_reset = new T[size];
		for (int i = 0; i < size; i++) {
			veca[i] = veca1[i];
			veca_for_reset[i] = veca1[i];
		}
		gr = size;
	};
	void reset() {
		for (int i = 0; i < gr; i++)
			veca[i] = veca_for_reset[i];
	}
	T operator[] (int n) {
		return veca[n];
	}
	my_array(const my_array & ob) {
		gr = ob.gr;
		veca = new T[gr];
		veca_for_reset = new T[gr];
		for (int i = 0; i < gr; i++) {
			veca[i] = ob.veca[i];
			veca_for_reset[i] = ob.veca_for_reset[i];
		}
	}
	void vn(int b)
	{
		int j, i; //переменные i и j используются в качестве индексов элементов массива
		T t; //буферная переменная для элементов массива
		int k = gr / 2; //расстояние между сортируемыми элементами на данном этапе сортировки 
		int er = 0; //номер текущего элемента массива adt2
		for (; k > adt; k /= 2, er++) {
			for (i = k + b; i < gr; i += adt)
			{
				t = veca[i];
				for (j = i; j >= k; j -= k)
				{
					if (t < veca[j - k]) {
						veca[j] = veca[j - k];
					}
					else {
						break;
					}
				}
				veca[j] = t;
			}
			adt2[er]++;
			while (1)
				if (adt2[er] == adt)
					break;
		}
		if (b == 0) {
			for (; k > b + 1; er++, k /= 2) {
				for (i = k + b; i < gr; i += k)
				{
					t = veca[i];
					for (j = i; j >= k; j -= k)
					{
						if (t < veca[j - k]) {
							veca[j] = veca[j - k];
						}
						else {
							break;
						}
					}
					veca[j] = t;
				}
				adt2[er]++;
				while (1)
					if (adt2[er] == k)
						break;
			}
			for (i = 1 + b; i < gr; i++)
			{
				t = veca[i];
				for (j = i; j >= 1; j--)
				{
					if (t < veca[j - 1]) {
						veca[j] = veca[j - 1];
					}
					else {
						break;
					}
				}
				veca[j] = t;
			}
		}
		else {
			for (; k > b; er++, k /= 2) {
				for (i = k + b; i < gr; i += k)
				{
					t = veca[i];
					for (j = i; j >= k; j -= k)
					{
						if (t < veca[j - k]) {
							veca[j] = veca[j - k];
						}
						else {
							break;
						}
					}
					veca[j] = t;
				}
				adt2[er]++;
				while (1)
					if (adt2[er] == k)
						break;
			}
		}
	}
	void operator()(void) {
		int maxx = thread::hardware_concurrency(); //максимальное возможное количество одновременно работающих потоков, которое можно запустить в системе
		adt = gr / 2; 
		(maxx < adt) ? (adt = maxx) : 1;
		int hyt = log2(gr) - 1; //количество элементов в массиве adt2
		adt2 = new atomic_int[hyt]; 
		for (int i = 0; i < hyt; i++)
			adt2[i] = 0;
		thread * te = new thread[adt - 1]; //массив потоков
		for (int b = 0; b < adt - 1; b++) {
			te[b] = thread(&my_array::vn, this, b);
		}
		vn(adt - 1);
		for (int b = 0; b < adt - 1; b++)
			te[b].join();
		delete[] te;
		delete[] adt2;
	}
	void print() {
		for (int i = 0; i < gr; i++)
			cout << veca[i] << ' ';
		cout << endl;
	}
	~my_array() {
		delete[] veca;
	}
};
template <class T> class my_array1 {
        T* veca; //массив типа Т
	T* veca_for_reset; //копия массива veca для сброса
	int gr; //количество элементов в массиве
public:
	my_array1(T* veca1, int size) {
		veca = new T[size];
		veca_for_reset = new T[size];
		for (int i = 0; i < size; i++) {
			veca[i] = veca1[i];
			veca_for_reset[i] = veca1[i];
		}
		gr = size;
	};
	my_array1(const my_array1& ob) {
		gr = ob.gr;
		veca = new T[gr];
		veca_for_reset = new T[gr];
		for (int i = 0; i < gr; i++) {
			veca[i] = ob.veca[i];
			veca_for_reset[i] = ob.veca_for_reset[i];
		}
	}
	void reset() {
		for (int i = 0; i < gr; i++)
			veca_for_reset[i] = veca[i];
	}
	T operator[] (int n) {
		return veca[n];
	}
	void print() {
		for (int i = 0; i < gr; i++)
			cout << veca[i] << ' ';
		cout << endl;
	}
	void operator()(void) {
		int i, j, k; //переменные i и j используются в качестве индексов элементов массива, которые обрабатываются в данный момент.\
Переменная k - расстояние между сортируемыми элементами на данном этапе сортировки 
		T t; //буферная переменная для элементов массива
		for (k = gr / 2; k > 0; k /= 2) {
			for (i = k; i < gr; i++)
			{
				t = veca[i];
				for (j = i; j >= k; j -= k)
				{
					if (t < veca[j - k])
						veca[j] = veca[j -  k];
					else
						break;
				}
				veca[j] = t;
			}
		}
	};
	~my_array1() {
		delete[] veca;
	};
};