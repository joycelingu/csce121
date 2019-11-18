class Matrix
{
	friend class Point2D;
	friend class Rot2D;
	public:
	Matrix(int p, int q);
	Matrix(const Matrix &obj);
	float get(int row, int col);
	void set(int row, int col, float val);
	void print();
	void center();
	float** transpose();
	float** prod(float** x, float** y, int r1, int c2, int c1);
	float** covariance();
	float** correlation();
	
	private:
	float** a;
	int r, c; 
	
};

class Point2D : public Matrix
{
	friend class Rot2D;
	public:
	Point2D();
};

class Rot2D : public Matrix
{
	friend class Point2D;
	public:
	Rot2D();
	void set2(float one, float two);
	void rotation(float degree);
	void hour(float d);
	
	private:
	float** P;
};