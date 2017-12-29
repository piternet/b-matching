#include "blimit.hpp"

unsigned int bvalue(unsigned int method, unsigned long node_id) {
    switch (method) {
    default: return node_id % 42;
    case 0: return 4;
    case 1: return 7;
    }        
}
