#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VTile.h"

using namespace std;

VTile *top;
VerilatedVcdC *tfp;

vluint64_t main_time = 0;
const vluint64_t sim_time = 1024;

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    top = new VTile;
    tfp = new VerilatedVcdC;

    top->trace(tfp, 99);
    tfp->open("./vcd/Tile.vcd");

    while(!Verilated::gotFinish() && main_time < sim_time)
    {
        // Clock
        if (main_time % 2)
            top->clock = 1;
        else
            top->clock = 0;

        top->eval();
        tfp->dump(main_time);
        main_time++;
    }

    tfp->close();
    delete top;
    delete tfp;
    exit(0);
    return 0;
}