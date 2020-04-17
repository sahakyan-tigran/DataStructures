#pragma once

class Polynom {
	friend std::ostream& operator<<(std::ostream&, const Polynom&);
public:
	Polynom();
	Polynom(double*,int*, int);
	Polynom(const Polynom&);
	Polynom& operator=(const Polynom&);
	~Polynom();

	Polynom& operator+=(const Polynom&);
	Polynom& operator*=(const Polynom&);
	Polynom& operator*=(const double);

	Polynom& derivative();
	double count_value(double);

private:
	void deallocate();
	bool find_exponent(int);

private:
	struct Node {
		double m_coefficient;
		int m_exponent;
		Node* m_next;

		Node(double coefficient = 0,int exponent = 0)
			: m_coefficient(coefficient), m_exponent(exponent), m_next(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Polynom&) = delete;
	};
private:
	Node* m_head;
};

Polynom operator+(Polynom, const Polynom&);
Polynom operator*(Polynom, const Polynom&);
Polynom operator*(Polynom, const double);
