class Regulador : FDT {

private:
	Sensor sens;
	Conversor conv;

public:
	Regulador(int parameters, Conversor* s);

	double read();
};
