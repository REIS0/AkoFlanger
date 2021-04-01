class LFO {
public:
  LFO(float freq, int samplerate);

  float get_value();

  void set_freq(int freq);
  float get_freq() const;

private:
  float freq;
  float t_samples; // one unity of time using the samples as parameter
  float time;
  bool wave_type; // 0 for sine, 1 for triangle
};