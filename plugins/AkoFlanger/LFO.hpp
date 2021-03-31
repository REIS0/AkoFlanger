class LFO {
public:
  LFO(int freq, int samplerate);

  float get_value();

private:
  int freq;
  float t_samples;    // one unity of time using the samples as parameter
  float time;
  bool wave_type; // 0 for sine, 1 for triangle
};