class FDT {

private:
	double* xk;
	double* yk;
	int tam;
	VComp entrada;
	VComp salida;
	VComp salidasTabla;
	double* coefNum;
	double* coefDen;

public:
	virtual double read() = 0;

	FDT(VComp* entrada, VComp* salida, VComp* salidasTabla, double* coefNum, double* coefDen);

	double simular(double n_entrada);

private:
	double productoEscalar(double* vector1, double* vector2);

	void desplazarTabla(double* tabla, double n_valor);
};
