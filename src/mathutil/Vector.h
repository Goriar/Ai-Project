#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED

class CVector
{
protected:
	double value_[2];
	
public:
	// standard constructor
	CVector(
		);

	// copy constructor
	CVector(
		const CVector& vector_in
		);

	// Konstruktor mit Initialisierung
	CVector(
		const double& a_in,
		const double& b_in
		);

	// Zuweisungsoperator
	CVector&
	operator=(
		const CVector& vector_in
		);

	// [] Operator f�r direkten Zugriff auf die Komponenten
	// Mit diesem Operator kann ich auf die einzelnen Vektorkomponenten lesend und schreibend zugreifen!
	double&
	operator[](
		const unsigned short index_in
		);

	// [] Operator f�r direkten Zugriff auf die Komponenten (const Version)
	// (Mit diesem Operator kann ich bei konstanten Vektoren auf die Vektorkomponenten lesend zugreifen!)
	double
	operator[](
		const unsigned short index_in
		) const;

	// Setze alle Vektorkomponenten 
	void
	set(
		const double& x_in, 
		const double& y_in
		);
	
	// Lese alle Vektorkomponenten
	void
	get(
		double& x_out, 
		double& y_out
		) const;

	// Vergleichs-Operator
	bool
	operator==(
		const CVector& vector_in
		) const;

	// negativer Vergleichs-Operator
	bool
	operator!=(
		const CVector& vector_in
		) const;

	// negativer Vektor (un�rer Minus-Operator)
	CVector
	operator-(
		) const;

	// Subtraktions-Operator f�r die Vektor-Differenz (bin�rer Minus-Operator)
	friend CVector
	operator-(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	// Additions-Operator f�r die Vektor-Summe (bin�rer Plus-Operator)
	friend CVector
	operator+(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	// Skalarprodukt (bin�rer *-Operator)
	friend  double
	operator*(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	// Skalarprodukt (�quivalent zu vorheriger Funktion, nur als un�re Funktion definiert)
	double
	getInnerProduct(
		const CVector& vector_in
		) const;
   
	// Skalares Vielfaches
	friend CVector
	operator*(
		const double& scalar_in,
		const CVector& vector_in
		);

	// Skalares Vielfaches (kommutativ)
	friend  CVector
	operator*(
		const CVector& vector_in,
		const double& scalar_in
		);
	
	// Skalare Division 
	friend  CVector
	operator/(
		const CVector& vector_in,
		const double& scalar_in
		);

	// Vektor-Inkrement Operator
	CVector&
	operator+=(
		const CVector& vector_in
		);

	// Vektor-Dekrement Operator
	CVector&
	operator-=(
		const CVector& vector_in
		);

	// Vektor-Skalierungs-Operator *=
	CVector&
	operator*=(
		const double& scalar_in
		);

	// Vektor-Divisions-Operator /=
	CVector&
	operator/=(
		const double& scalar_in
		);

	// Vektorl�nge
	double
	getLength(
		) const;

	// Normalisierungs-Funktion
	void
	normalize(
		);

	// Abfrage, ob es ein Einheitsvektor ist
	bool
	isNormalized(
		) const;

	// Abfrage, ob es der Nullvektor ist
	bool
	isNil(
		) const;
};


#endif // CVECTOR_H_INCLUDED
