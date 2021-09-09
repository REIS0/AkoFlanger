declare filename "akoflanger.dsp"; 
declare name "AkoFlanger"; 
declare author "REIS0";
declare license "GNU GPLv3";
declare version "0.1";

import("stdfaust.lib");
import("delays.lib");

max_delay = ma.SR * 0.005;
min_delay = ma.SR * 0.002;

freq = hslider("[0]Frequency", 1, 0.1, 2, 0.01) : si.smooth(0.999);
lfo = os.osc(freq) * 0.5 + 0.5;
ldelay = lfo * (max_delay - min_delay + min_delay);

flanger(depth, regen) = (+ <: de.fdelay(max_delay, ldelay) * depth, _) ~ *(regen) : + : *(0.6);

akoflanger = _ <: flanger(depth, regen), _ : *(dry_wet), *(1-dry_wet) : +
with{
    depth = hslider("[1]Depth", 0.5, 0.1, 0.9, 0.01);
    regen = hslider("[2]Regen", 0.25, 0.0, 0.5, 0.01); 
    dry_wet = hslider("[3]Dry/Wet", 0.5, 0, 1, 0.01);
};

level = hslider("[4]Level", 1.0, 0.0, 1.0, 0.01);

process = akoflanger, akoflanger : *(level), *(level);