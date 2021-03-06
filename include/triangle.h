#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "Vertex.h"
#include "edge.h"
#include "numeric.h"
#include <cmath>

template <class T>
class Triangle
{
public:
    using EdgeType = Edge<T>;
    using VertexType = Vertex<T>;

public:
    Triangle(const VertexType &_p1, const VertexType &_p2, const VertexType &_p3)
            :	p1(_p1), p2(_p2), p3(_p3),
                 e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), isBad(false)
    {}

    //判断一点是否在三角形内部
    inline bool ContainsVertex(const VertexType &v) const
    {
        // return p1 == v || p2 == v || p3 == v;
        return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v);
    }

    bool CircumCircleContains(const VertexType &v) ;   //判断一点是否在外接圆内（包括在外接圆上）
    bool ComputeAngle();    // 计算角度  计算相似度


//    friend class Edge<T>;

    VertexType p1;
    VertexType p2;
    VertexType p3;
    VertexType circum;
    VertexType mainpoint;
    EdgeType e1;
    EdgeType e2;
    EdgeType e3;
    double angle[3]{};
    bool isBad;
};

template<class T>
bool Triangle<T>::CircumCircleContains(const Triangle::VertexType &v)  {
    const T ab = p1.norm2();
    const T cd = p2.norm2();
    const T ef = p3.norm2();

    circum.x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) / (p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y));
    circum.y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) / (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x));
    circum.x = half(circum.x);
    circum.y = half(circum.y);

    mainpoint.x = (p1.x - circum.x) + (p2.x - circum.x) + (p3.x - circum.x) +circum.x;
    mainpoint.y = (p1.y - circum.y) + (p2.y - circum.y) + (p3.y - circum.y) +circum.y;

    const T circum_radius = p1.dist2(circum);   // 得到当前三角形外接圆的半径
    const T dist = v.dist2(circum);
    return dist <= circum_radius;
}

template<class T>
bool Triangle<T>::ComputeAngle() {
    e1.ComputeSideLength();
    e2.ComputeSideLength();
    e3.ComputeSideLength();
    double cosA = (e2.sideLength*e2.sideLength + e3.sideLength*e3.sideLength - e1.sideLength*e1.sideLength)/(2*e2.sideLength*e3.sideLength);
    double cosB = (e1.sideLength*e1.sideLength + e3.sideLength*e3.sideLength - e2.sideLength*e2.sideLength)/(2*e1.sideLength*e3.sideLength);
    double cosC = (e1.sideLength*e1.sideLength + e2.sideLength*e2.sideLength - e3.sideLength*e3.sideLength)/(2*e1.sideLength*e2.sideLength);
    angle[0] = acos(cosA);
    angle[1] = acos(cosB);
    angle[2] = acos(cosC);
    return true;
}

template <class T>
inline std::ostream &operator << (std::ostream &str, const Triangle<T> & t)
{
    return str << "Triangle:" << std::endl << "\t" << t.p1 << std::endl << "\t" << t.p2 << std::endl << "\t" << t.p3 << std::endl << "\t" << t.e1 << std::endl << "\t" << t.e2 << std::endl << "\t" << t.e3 << std::endl;
}

template <class T>
inline bool operator == (const Triangle<T> &t1, const Triangle<T> &t2)
{
    return	(t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) &&
              (t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) &&
              (t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3);
}

//注意这里的 almost 函数，该函数在 numeric.h 中定义
template <class T>
inline bool almost_equal(const Triangle<T> &t1, const Triangle<T> &t2)
{
    return	(almost_equal(t1.p1 , t2.p1) || almost_equal(t1.p1 , t2.p2) || almost_equal(t1.p1 , t2.p3)) &&
              (almost_equal(t1.p2 , t2.p1) || almost_equal(t1.p2 , t2.p2) || almost_equal(t1.p2 , t2.p3)) &&
              (almost_equal(t1.p3 , t2.p1) || almost_equal(t1.p3 , t2.p2) || almost_equal(t1.p3 , t2.p3));
}

#endif
