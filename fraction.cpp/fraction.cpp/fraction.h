#ifndef FRACTION_H
#define FRACTION_H
class fraction
{
private:
	int num;
	int denom;
public:
	fraction();
	fraction(int);
	fraction(int, int);

	void setNum(int);
	void setDenom(int);

	fraction& multiply(const fraction& f1);
	fraction& devide(const fraction& f1);
	fraction& add(const fraction& f1);
	fraction& sub(const fraction& f1);

	void readFrac();
	void displayFrac()const;
	int getNum();
	int getDenom();
};

#endif
