#include "Utils.h"
#include "CGraph.h"
#include "Local.h"
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>


using namespace std;
using namespace DS;
class MapHandler
{
public:
    
    
    /*typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
    typedef K::Point_2 PointCGAL;*/
    
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef CGAL::Triangulation_vertex_base_with_info_2<CGraph<Local, int>::Node*, K>    Vb;
    typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
    typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;
    typedef K::Point_2 PointCGAL;
    
    
    CGraph<Local, int> oGraph;
    Delaunay dt;
    int padding=10;
    
    void buildMap(int _numberOfNodes,int _widthMap, int _heigthMap)
    {
        Utils::initialize_randomness(-1);
        int x,y;
        
        //vector<PointCGAL> pointsToTriangule;
        vector< pair<PointCGAL,CGraph<Local, int>::Node*> > pointsToTriangule;
        
        
        for(int i=0; i<_numberOfNodes; i++)
        {
            Local data;
            data.xPos=Utils::randint(padding,_widthMap-padding);
            data.yPos=Utils::randint(padding,_heigthMap-padding);
            CGraph<Local, int>::Node *oNode;
            oNode=oGraph.insertNode(data);
            pointsToTriangule.push_back(make_pair(PointCGAL(data.xPos,data.yPos),oNode));
            
        }
        //delaunay triangulation
        dt.insert(pointsToTriangule.begin(), pointsToTriangule.end());
        
        //insertamos los vertices
        for(Delaunay::Finite_edges_iterator it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it) {
            CGraph<Local, int>::Node* nodo1= it->first->vertex( (it->second+1)%3 )->info();
            CGraph<Local, int>::Node* nodo2= it->first->vertex( (it->second+2)%3 )->info();
            oGraph.insertEdge(nodo1,nodo2,1,false);
        }
    }
};