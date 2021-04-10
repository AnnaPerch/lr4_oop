//Створити базовий клас ТАРИФНИЙ ПАКЕТ (задаються оператор та назва).
//Створити похідний клас ПАКЕТ З АБОНПЛАТОЮ БЕЗ ВКЛЮЧЕНИХ ХВИЛИН
//(задаються розмір абонплати, вартість дзвінків за 1 хвилину).
//Для введених даних про різні тарифні пакети і очікувану кількість хвилин щомісячних
//розмов обчислити сумарну вартість цих розмов для кожного пакету і визначити ті,
//вартість яких не перевищує задане значення.

#include <iostream>
#include <string>
int y;
using namespace std;

class tariff {					//клас ТАРИФНИЙ ПАКЕТ (задаються оператор та назва).
protected:
	string provider;
	string tar_name;
public:
	tariff() {
		provider = "";
		tar_name = "";
	}

	tariff(string str1, string str2) : provider(str1), tar_name(str2) {}
	~tariff() {}
	string get_provider() { return provider; }
	string get_tar_name() { return tar_name; }
	virtual double total() { return 0; }
	bool operator<(tariff& p) {
		return this->total() < p.total();
	}
	bool operator>(tariff& p) {
		return this->total() > p.total();
	}
};

class tariff_plan : public tariff {				//похідний клас ПАКЕТ З АБОНПЛАТОЮ БЕЗ ВКЛЮЧЕНИХ ХВИЛИН
private:
	int subscriber_fee;
	int minute_price;	
public:
	tariff_plan() : tariff(), subscriber_fee(0), minute_price(0) {}
	tariff_plan(string str1, string str2, int s_fee, int m_price) : tariff(str1, str2), subscriber_fee(s_fee), minute_price(m_price) {}
	~tariff_plan() {}
	int get_subscriber_fee() { return subscriber_fee; }
	int get_minute_price() { return minute_price; }
	void set_fee_p(double p) { subscriber_fee = p; }
	void set_price_p(double p) { minute_price = p; }
	double total() { return (minute_price * y + subscriber_fee); }
};

ostream& operator<<(ostream& o, tariff p) {
	o << "Provider: " << p.get_provider() << "\t\tName of tariff: " << p.get_tar_name() << endl;
	return o;
}

ostream& operator<<(ostream& o, tariff_plan v) {
	o << "Provider: " << v.get_provider() << "\t\tName of tariff: " << v.get_tar_name() << "\n\t Subscriber's fee: " << v.get_subscriber_fee() << "\tPrice per minute: " << v.get_minute_price() << endl;
	return o;
}

void input(tariff** p, int n) {
	cout << "\n\tEnter pass:\n";
	for (int i = 0; i < n; i++) {
		string s;
		string l;
		int s_fee, m_price;
		cout << "Provider: "; cin >> s;
		cout << "Name of tariff: "; cin >> l;
		cout << "Subscriber's fee: "; cin >> s_fee;
		cout << "Price per minute: "; cin >> m_price;
		
		cout << "\n\n";
		
		p[i] = new tariff_plan(s, l, s_fee, m_price);
	}
}

void sort(tariff** p, int n, int x) {	
	cout << "\n\tTariffs for you:\n";
	for (int i = 0; i < n; i++) {
		if (p[i]->total() <= x)
			cout << p[i]->get_provider() << ": " << p[i]->get_tar_name() << " - " << p[i]->total() << " grivnas" << endl;
	}
}

int main() {
	tariff*(*p);
	int x,n;
	cout << "Enter number of tariff's: ";
	cin >> n;
	p = new tariff * [n];
	input(p, n);	
	cout << "Enter amount of money you can pay: ";
	cin >> x;		
	cout << "Enter number of minutes you want to use: ";
	cin >> y;
	sort(p, n, x);
	return 0;
}