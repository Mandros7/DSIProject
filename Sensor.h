class Sensor {

private:
	VComp entrada;

public:
	Sensor(VComp* entrada);

	short getValue();
};
