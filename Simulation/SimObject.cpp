#include "SimObject.h"

SimObject::SimObject() {
  Xz_.fill(0.0);
  Xu_.fill(0.0);

  for (int i = 0; i < 5; ++i)
    UInput_.push(0.0);

  for (int i = 0; i < 3; ++i)
    ZInput_.push(0.0);
}

double SimObject::CalculateY(double u, double z) {
  UInput_.push(u);
  ZInput_.push(z);

  double uk_5 = UInput_.front();
  UInput_.pop();

  double zk_3 = ZInput_.front();
  ZInput_.pop();

  double Xuk = Bu4 * UInput_.front() + Bu5 * uk_5 - Au1 * Xu_[0] - Au2 * Xu_[1];
  double Xzk = Bz2 * ZInput_.front() + Bz3 * zk_3 - Az1 * Xz_[0] - Az2 * Xz_[1];

  Xu_[1] = Xu_[0];
  Xu_[0] = Xuk;

  Xz_[1] = Xz_[0];
  Xz_[0] = Xzk;

  return Xuk + Xzk;
}