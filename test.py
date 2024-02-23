from PySpice.Spice.Parser import SpiceParser
from PySpice.Spice.NgSpice.Shared import NgSpiceShared
from PySpice.Unit import *

import math

class MyNgSpiceShared(NgSpiceShared):


    def __init__(self, amplitude, frequency, **kwargs):

        super().__init__(**kwargs)

        self._amplitude = amplitude
        self._pulsation = float(frequency.pulsation)


    def get_vsrc_data(self, voltage, time, node, ngspice_id):
        self._logger.debug('ngspice_id-{} get_vsrc_data @{} node {}'.format(ngspice_id, time, node))
        voltage[0] = self._amplitude * math.sin(self._pulsation * time)
        return 0


    def get_isrc_data(self, current, time, node, ngspice_id):
        self._logger.debug('ngspice_id-{} get_isrc_data @{} node {}'.format(ngspice_id, time, node))
        current[0] = 1.
        return 0


source = SpiceParser("test.spice")
circuit = source.build_circuit()

ngspice_shared = MyNgSpiceShared(10@u_V,440 @ u_Hz, send_data=False)
simulator = circuit.simulator(tempature=25,
    nominal_temperature=25,
    simulator='ngspice-shared',
    ngspice_shared=ngspice_shared)
analysis = simulator.transient(step_time=1/440,end_time=2)
