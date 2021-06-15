#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include <array>
#include <queue>

class SimObject {
private:
  std::queue<double> UInput_;
  std::queue<double> ZInput_;
  std::array<double, 2> Xu_;
  std::array<double, 2> Xz_;

  const double Au1 = -1.746;
  const double Au2 = 0.7533;
  const double Bu4 = 0.003797;
  const double Bu5 = 0.003455;

  const double Az1 = -1.574;
  const double Az2 = 0.5886;
  const double Bz2 = 0.0007021;
  const double Bz3 = 0.0005879;

public:
  SimObject();
  double CalculateY(double u, double z);
};

// SIMOBJECT_H
#endif
