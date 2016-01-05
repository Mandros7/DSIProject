class VComp {

private:
	Mutex mutex;
	double* valor;

public:
	VComp(int double_valor_inicial);

	double* getValor();

	void setValor(double* n_Valor);
};
