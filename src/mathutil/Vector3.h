#ifndef CVECTOR3_H_INCLUDED
#define CVECTOR3_H_INCLUDED

class CVector3
{
protected:
	double value_[3];
	
public:
	// standard constructor
	CVector3(
		);

	// copy constructor
	CVector3(
		const CVector3& vector_in
		);

	// Konstruktor mit Initialisierung
	CVector3(
		const double& a_in,
		const double& b_in,
		const double& c_in
		);

	// Zuweisungsoperator
	CVector3&
	operator=(
		const CVector3& vector_in
		);

	// [] Operator für direkten Zugriff auf die Komponenten
	// Mit diesem Operator kann ich auf die einzelnen Vektorkomponenten lesend und schreibend zugreifen!
	double&
	operator[](
		const unsigned short index_in
		);

	// [] Operator für direkten Zugriff auf die Komponenten (const Version)
	// (Mit diesem Operator kann ich bei konstanten Vektoren auf die Vektorkomponenten lesend zugreifen!)
	double
	operator[](
		const unsigned short index_in
		) const;

	// Setze alle Vektorkomponenten 
	void
	set(
		const double& x_in, 
		const double& y_in,
		const double& z_in
		);
	
	// Lese alle Vektorkomponenten
	void
	get(
		double& x_out, 
		double& y_out,
		double& z_out
		) const;

	// Vergleichs-Operator
	bool
	operator==(
		const CVector3& vector_in
		) const;

	// negativer Vergleichs-Operator
	bool
	operator!=(
		const CVector3& vector_in
		) const;

	// negativer Vektor (unärer Minus-Operator)
	CVector3
	operator-(
		) const;

	// Subtraktions-Operator für die Vektor-Differenz (binärer Minus-Operator)
	friend CVector3
	operator-(
		const CVector3& vector0_in,
		const CVector3& vector1_in
		);

	// Additions-Operator für die Vektor-Summe (binärer Plus-Operator)
	friend CVector3
	operator+(
		const CVector3& vector0_in,
		const CVector3& vector1_in
		);

	// Skalarprodukt (binärer *-Operator)
	friend  double
	operator*(
		const CVector3& vector0_in,
		const CVector3& vector1_in
		);

	// Skalarprodukt (äquivalent zu vorheriger Funktion, nur als unäre Funktion definiert)
	double
	getInnerProduct(
		const CVector3& vector_in
		) const;
   
	// Skalares Vielfaches
	friend CVector3
	operator*(
		const double& scalar_in,
		const CVector3& vector_in
		);

	// Skalares Vielfaches (kommutativ)
	friend  CVector3
	operator*(
		const CVector3& vector_in,
		const double& scalar_in
		);
	
	// Skalare Division 
	friend  CVector3
	operator/(
		const CVector3& vector_in,
		const double& scalar_in
		);

	// Vektor-Inkrement Operator
	CVector3&
	operator+=(
		const CVector3& vector_in
		);

	// Vektor-Dekrement Operator
	CVector3&
	operator-=(
		const CVector3& vector_in
		);

	// Vektor-Skalierungs-Operator *=
	CVector3&
	operator*=(
		const double& scalar_in
		);

	// Vektor-Divisions-Operator /=
	CVector3&
	operator/=(
		const double& scalar_in
		);

	// Vektorlänge
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

	CVector3 crossProduct(CVector3 v1, CVector3 v2);
};


#endif // CVECTOR3_H_INCLUDED
