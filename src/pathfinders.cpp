#include "pathfinders.h"
#include "dgraph.h"
#include "heaps/heap.h"

#include <algorithm> // std::fill

#include <Rcpp.h> // TODO: Delete that

/* Dijkstra's Algorithm
 * ----------------------------------------------------------------------------
 * Author: Mark Padgham, modified from code by Shane Saunders
 */

/*--- Dijkstra -----------------------------------------------------------*/

/* - Constructor -
 * Allocate the algorithm for use on graphs of n vertices.  The parameter heapD
 * (points to a heap descriptor object) specifies the heap to be used by
 * Dijkstra's algorithm.
 */
Dijkstra::Dijkstra(unsigned int n, const HeapDesc& heapD, std::shared_ptr<const DGraph> g) 
{
    m_heap = heapD.newInstance(n);
    m_s = new bool[n];
    m_f = new bool[n];
    init(g);
}

/* - Destructor - */
Dijkstra::~Dijkstra() {
    delete [] m_s;
    delete [] m_f;
    delete m_heap;
}

/* - init() -
 * Initialise the algorithm for use with the graph pointed to by g.
 */
void Dijkstra::init(std::shared_ptr<const DGraph> g) {
    m_graph = g;
}

/* - run() -
 * Run the algorithm, computing single-source from the starting vertex v0.
 * This assumes that the array d has been initialised with d[v] = INFINITE_DIST
 * for all vertices v != v0.
 */

void Dijkstra::run (std::vector<double>& d,
        std::vector<double>& w,
        std::vector<int>& prev,
        unsigned int v0,
        const double d_threshold)
{
    /* indexes, counters, pointers */
    const DGraphEdge *edge;

    /*** initialisation ***/

    /* optimise access to the data structures allocated for the algorithm */
    const unsigned int n = m_graph->nVertices();
    const std::vector<DGraphVertex>& vertices = m_graph->vertices();

    /* initialise all vertices as unexplored */
    std::fill (m_s, m_s + n, false);
    std::fill (m_f, m_f + n, false);

    /* place v0 into the frontier set with a distance of zero */
    w [v0] = 0.0;
    d [v0] = 0.0;
    prev [v0] = -1;
    m_heap->insert(v0, 0.0);
    m_f [v0] = true;

    /* Implement a speed-up by only tracing out to some distance range. This
     * itself requires expanding the threshold to ensure shortest paths are
     * traced. This expansion must go beyond the threshold because it includes
     * initial (non-settled) distance estimates, which may be greater yet end up
     * being less. Values of 2 generate discrepancies, whereas the value of 5
     * generates only rounding-error discrepancies for a trial network of
     * 370,000 edges. On this network, the `if (w+..)<=dt2` clause speeds up
     * calculations by 4-5 times
     */
    double dt2 = d_threshold * 5.0;

    /* repeatedly update distances from the minimum remaining trigger vertex */
    while (m_heap->nItems() > 0) {
        /* delete the vertex in frontier that has minimum distance */
        unsigned int v = m_heap->deleteMin();

        /* the selected vertex moves from the frontier to the solution set */
        m_s [v] = true;
        m_f [v] = false;

        // explore the OUT set of v only if distances are < threshold
        bool explore = false;
        edge = vertices [v].outHead;
        while (edge) {
            if ((w [v] + edge->wt) <= dt2)
            {
                explore = true;
                break;
            }
            edge = edge->nextOut;
        }

        if (explore)
        {
            edge = vertices [v].outHead;
            while (edge) {
                unsigned int et = edge->target;

                if (!m_s [et]) {
                    double wt = w [v] + edge->wt;
                    if (wt < w [et]) {
                        d [et] = d [v] + edge->dist;
                        w [et] = wt;
                        prev [et] = static_cast <int> (v);
                        if (m_f [et]) {
                            m_heap->decreaseKey(et, wt);
                        }
                        else {
                            m_heap->insert (et, wt);
                            m_f [et] = true;
                        }
                    }
                }
            edge = edge->nextOut;
            } // end while
        } // end if explore
    } // end while
}
