// See LICENSE for license details.

#include "decode.h"
#include "disasm.h"
#include "sim.h"
#include "mmu.h"
#include <sys/mman.h>
#include <termios.h>
#include <map>
#include <iostream>
#include <climits>
#include <cinttypes>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <pthread.h>

void sim_t::single_step()
{
    while (!done())
    {
        pthread_mutex_lock(&mutex);
        set_procs_debug(true);
        step(1);
        store_gpr_buffer();
        pthread_mutex_lock(&mutex);
        continue;
    }
    ctrlc_pressed = false;
}

void sim_t::store_gpr_buffer()
{
    processor_t *p = get_core(0);
    for (int i = 0 ; i < 32 ; i++ ) {
        gpr[i] = p->get_state()->XPR[i];
    }
}
