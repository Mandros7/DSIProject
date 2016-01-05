class Conversor {

private:
	VComp registroDatos;
	VComp registroControl;

public:
	VComp getRegistroDatos();

	VComp getRegistroControl();

	void convert(short sensValor);
};
