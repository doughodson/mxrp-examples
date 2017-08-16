
#include <iostream>

#include "Lognormal.hpp"

#include "mixr/base/numbers/Number.hpp"

using mixr::base::Number;

IMPLEMENT_SUBCLASS(Lognormal, "Lognormal")
EMPTY_DELETEDATA(Lognormal)
EMPTY_SERIALIZER(Lognormal)

// slot table for this class type
BEGIN_SLOTTABLE(Lognormal)
  "sigma",              // 1
  "mu",                 // 2
  "gamma",              // 3
END_SLOTTABLE(Lognormal)
//  map slot table to handles
BEGIN_SLOT_MAP(Lognormal)
  ON_SLOT(1, setSlotSigma, Number)
  ON_SLOT(2, setSlotMu, Number)
  ON_SLOT(3, setSlotGamma, Number)
END_SLOT_MAP()

Lognormal::Lognormal()
{
  STANDARD_CONSTRUCTOR()
}

void Lognormal::copyData(const Lognormal& org, const bool)
{
  BaseClass::copyData(org);
  sigma = org.sigma;
  mu = org.mu;
  gamma = org.gamma;
}

unsigned Lognormal::num()
{
   std::lognormal_distribution<double> dist(0.0, 1.0);
   const unsigned val = static_cast<unsigned>(dist(engine) * 1000);
   return val;
}

/*
double Lognormal::draw()
{
  double u(0.0), r2(0.0);
  do {
      // choose x,y in uniform square (-1,-1) to (+1,+1)
      u = -1 + 2 * drawHalfOpen();
      const double v = -1 + 2 * drawHalfOpen();
      // see if it is in the unit circle
      r2 = u * u + v * v;
  } while (r2 > 1.0 || r2 == 0);
  const double normal = u * std::sqrt(-2.0 * std::log(r2) / r2);
  double z =  std::exp(sigma * normal + mu);
  // shift for location
  z += gamma;
  return z;
}
*/

bool Lognormal::setSlotSigma(const Number* const x)
{
  bool ok = false;
  if(x != nullptr)
    ok = setSigma(x->getDouble());
  return ok;
}

bool Lognormal::setSlotMu(const Number* const x)
{
  bool ok = false;
  if(x != nullptr)
    ok = setMu(x->getDouble());
  return ok;
}

bool Lognormal::setSlotGamma(const Number* const x)
{
  bool ok = false;
  if(x != nullptr)
    ok = setGamma(x->getDouble());
  return ok;
}

