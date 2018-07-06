/*
git cmds    log     status//what files youve modified
git cheat sheet     try.github.com - good website
*/
//for group project
void reserve(int newalloc)
{
    if (newalloc <= space) return;//never decrease allocarion
    T* p = new T[newalloc];                   //allocate new space
    for (int i=0; i<size_v; ++i)p[i] = elem[i];      //copy old elements
    delete[] elem;                       //deallocate old space
    elem = p;
    space = newalloc;
}





class Shape{
    public:
        enum class ShapeType { NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Text};

        Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape);
        virtual ~shape() {}

        ShapeType get_shape() const;
        const QPen& get_pen() const;
        const QBrush& get_brush() const;

        void set_shape(ShapeType shape);
        void set_pen(QT::GlobalColor, int width,.........)
        .........







    
}
