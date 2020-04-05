#include <iostream>
#include <string>

const int MAX_SIZE=100;

class Student {
public:
	Student() : m_name("") , m_group(0) , m_avg(0.0) {}
	Student(const std::string& name,int group) : m_name(name) , m_group(group) , m_avg(0) {}
	
	const std::string& get_name() const { return m_name; }
	int get_group() const { return m_group; }
	const double& get_avg() const { return m_avg; }
	void set_avg(const double& avg) { m_avg = avg; }

private:
	std::string m_name;
	int m_group;
	double m_avg;
};

class Journal {
public:
	static Journal& get_instance() {
		static Journal object;
		return object;
	}
	const Student& operator[] (int) const;

	void add_student(const Student&);
	void remove_student(int);
	void avg(double);

private:
	Journal();
	Journal(const Journal&) = delete;
	Journal& operator=(const Journal&) = delete;
	~Journal();

	int m_max_size;
	int m_size;
	Student* m_students;
};
Journal::Journal() : m_max_size(MAX_SIZE), m_size(0), m_students(nullptr) { m_students = new Student[m_max_size]; }
Journal::~Journal() { delete[] m_students; }

const Student& Journal::operator[](int index) const {
	if (index <= 0 || index > m_size) {
		throw std::exception("Index is out of journal.");
	}
	return m_students[index];
}

void Journal::add_student(const Student& obj) {
	if (m_size + 1 == m_max_size) {
		m_max_size *= 2;
		Student* tmp = new Student[m_max_size];
		for (int i = 1;i <= m_size;++i) {
			tmp[i] = m_students[i];
		}
		delete[] m_students;
		m_students = tmp;
	}
	m_students[++m_size] = obj;
}

void Journal::remove_student(int index) {
	if (index <= 0 || index > m_size) {
		throw std::exception("Index is out of journal.");
	}
	if (m_size == 0) {
		return;
	}
	if (index != m_size ) {
		for (int i = index;i < m_size;++i) {
			m_students[i] = m_students[i + 1];
		}
	}
	--m_size;
}

void Journal::avg(double number) {
	for (int i = 1;i <= m_size;++i) {
		if (m_students[i].get_avg() >= number) {
			std::cout << m_students[i].get_name()<<std::endl;
		}
	}
}


int main() {
	Student a("a", 910), b("b", 911), c("c", 912), d("d", 913), e("e", 914);
	a.set_avg(16.5);
	b.set_avg(17.8);
	c.set_avg(18.3);
	d.set_avg(18.9);
	e.set_avg(19.8);
	Journal &j = Journal::get_instance();
	j.add_student(a);
	j.add_student(b);
	j.add_student(c);
	j.add_student(d);		
	j.add_student(e);
	j.avg(18.0);
	return 0;
}

