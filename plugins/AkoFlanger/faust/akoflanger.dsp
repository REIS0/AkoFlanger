declare filename "akoflanger.dsp"; declare name "akoflanger"; import("stdfaust.lib");
import("delays.lib");

max_delay = ma.SR * 0.005;
min_delay = ma.SR * 0.002;

freq = hslider("Frequency", 1, 0.1, 2, 0.01) : si.smooth(0.999);
lfo = os.osc(freq);
ldelay = min_delay + lfo * (max_delay - min_delay);

flanger(x, depth) = x <: _, depth * de.fdelay(max_delay, ldelay) : +;

akoflanger(x) = x <: flanger(_, invert), _ : +~(fdelay(max_delay, ldelay)*regen), _ : *(dry_wet), *(1-dry_wet) : +
with{
    flange = flanger(x, depth, lfo);
    depth = hslider("Depth", 0.5, 0.1, 0.9, 0.01);
    regen = hslider("Regen", 0.5, 0.1, 0.9, 0.01);
    dry_wet = hslider("Dry/Wet", 0.5, 0, 1, 0.01);
    invert = depth,1-depth: select2(checkbox("invert depth"));
};

process = akoflanger(_), akoflanger(_);