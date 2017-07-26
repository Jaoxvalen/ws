#include "miniwin.h"
#include "CGraph.h"
#include "Local.h"

using namespace miniwin;
using namespace DS;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<CGraph<Local, int>::Node*, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;
typedef K::Point_2 PointCGAL;
class CanvasHandler
{
private:
    void drawTrinagulation(Delaunay dt)
    {
        color(ROJO);
        for(Delaunay::Finite_edges_iterator it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it) {
            PointCGAL i1 = it->first->vertex((it->second + 1) % 3)->point();
            PointCGAL i2 = it->first->vertex((it->second + 2) % 3)->point();
            linea(i1.x(), i1.y(), i2.x(), i2.y());
        }
        refresca();
    }

public:
    int nodeSize = 5;

    int width, height;
    void initWindow(int _width, int _height)
    {
        width = _width;
        height = _height;
        vredimensiona(width, height);
    }
    void drawGraph(const CGraph<Local, int> _graph, Delaunay dt)
    {
        color(VERDE);
        for(int i = 0; i < _graph.nodes.size(); i++) {
            circulo(_graph.nodes[i]->data.xPos, _graph.nodes[i]->data.yPos, nodeSize);
        }
        drawTrinagulation(dt);
        refresca();
    }
};