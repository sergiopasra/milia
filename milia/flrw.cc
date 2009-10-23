/*
 * Copyright 2008-2009 Sergio Pascual
 *
 * This file is part of Milia
 *
 * Milia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milia is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Milia.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// $Id$

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cmath>
#include <sstream>

#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <boost/math/special_functions/pow.hpp>

#include "flrw.h"
#include "flrw_prec.h"
#include "exception.h"

using std::abs;
using boost::math::asinh;
using boost::math::atanh;
using boost::math::pow;

namespace milia
{
  namespace metrics
  {

    flrw::flrw(double h, double m, double v) :
      m_hu(h), m_om(m), m_ov(v), m_ok(1 - m_om - m_ov), m_sqok(sqrt(abs(m_ok)))
    {

      if (m_hu <= 0)
        throw milia::exception("Hubble constant <= 0 not allowed");

      //om < 0 not allowed
      if (m_om < 0)
        throw milia::exception("Matter density < 0 not allowed");

      //ov < 0 makes the universe recollapse
      if (m_ov < -FLRW_EQ_TOL)
        throw milia::recollapse("The Universe recollapses"); // Recollapse

      m_b = -13.5 * pow<2> (m_om) * m_ov / (pow<3> (m_ok));

      m_kap = m_ok > 0 ? -1 : 1;
      m_case = check();

      m_r_h = ms_hubble_radius / m_hu;
      m_t_h = ms_hubble_time / m_hu;

      if (m_case == A2_1 or m_case == A2_2)
      {
        if (m_om >= 1 && m_b <= 2)
        {
          throw milia::recollapse("The Universe recollapses"); // Recollapse
        }

        if (m_ov >= 1 && m_b <= 2)
          throw milia::no_big_bang("No Big Bang"); // No Big bang with this parameters

      }

      m_universe_age = m_case != OM_DS ? age() : 0;
    }

    std::string flrw::to_string() const
    {
      std::stringstream out;
      out << "flrw(hubble=" << m_hu << ", matter=" << m_om << ", vacuum="
          << m_ov << ")";
      return out.str();
    }

    double flrw::sinc(double k, double a, double x)
    {
      if (k > 0)
        return sin(a * x) / a;
      if (k < 0)
        return sinh(a * x) / a;
      return -1;
    }

    double flrw::asinc(double k, double a, double x)
    {
      if (k > 0)
        return asin(a * x) / a;
      if (k < 0)
        return asinh(a * x) / a;
      return -1;
    }

    bool flrw::does_recollapse(double matter, double vacuum)
    {
      if (vacuum < 0)
        return true;
      if (matter < 1)
        return false;
      const double critical = 4 * matter * pow<3> (cos(1. / 3. * acos(1.
          / matter - 1.) + 4 * M_PI / 3.));
      if (vacuum > critical)
        return false;
      return true;
    }

    bool flrw::set_hubble(double hubble)
    {
      if (hubble > 0)
      {
        m_hu = hubble;
        m_r_h = ms_hubble_radius / m_hu;
        m_t_h = ms_hubble_time / m_hu;
        m_universe_age = age();
        return true;
      }
      else
        throw milia::exception("Hubble constant <= 0 not allowed");
    }

    bool flrw::set_matter(double matter)
    {
      if (matter < 0)
      {
        throw milia::exception("Matter density < 0 not allowed");
      }

      const double OK = 1 - m_ov - matter;
      double B = -13.5 * pow<2> (matter) * m_ov / pow<3> (OK);

      if (matter >= 1 && B <= 2)
        throw milia::recollapse("The Universe recollapses"); // Recollapse

      if (m_ov >= 1 && B <= 2)
        throw milia::no_big_bang("No Big Bang"); // No Big bang with this parameters

      // Time and space scale
      m_om = matter;
      m_ok = OK;
      m_sqok = sqrt(abs(OK));
      m_b = B;
      m_kap = (m_ok > 0 ? -1 : 1);
      m_case = check();
      m_universe_age = m_case != OM_DS ? age() : 0;
      return true;
    }

    bool flrw::set_vacuum(double vacuum)
    {
      if (vacuum < 0)
        throw milia::recollapse("The Universe recollapses"); // Recollapse

      const double OK = 1 - m_om - vacuum;
      double B = -13.5 * pow<2> (m_om) * vacuum / pow<3> (OK);

      if (m_om >= 1 && B <= 2)
        throw milia::recollapse("The Universe recollapses"); // Recollapse

      if (vacuum >= 1 && B <= 2)
        throw milia::no_big_bang("No Big Bang"); // No Big bang with this parameters

      m_ov = vacuum;
      m_ok = OK;
      m_sqok = sqrt(abs(OK));
      m_b = B;
      m_kap = (m_ok > 0 ? -1 : 1);
      m_case = check();
      m_universe_age = m_case != OM_DS ? age() : 0;
      return true;
    }

    flrw::ComputationCases flrw::check() const
    {
      const bool l3 = (abs(m_om) < FLRW_EQ_TOL);
      const bool l4 = (abs(m_ov) < FLRW_EQ_TOL);
      // om = ov = 0
      if (l3 && l4)
        return OM_OV_0;
      // ov = 0 om == 1. Einstein-de Sitter Universe
      if (l4 && abs(m_om - 1) < FLRW_EQ_TOL)
        return OV_EDS;
      // ov=0 0<om<1
      if (l4 && m_om < 1)
        return OV_1;
      // ov=0 om>1
      if (l4 && m_om > 1)
        return OV_2;

      // om = 0 ov = 1 de Sitter Universe
      if (l3 and (abs(m_ov - 1) < FLRW_EQ_TOL))
        return OM_DS;
      // om=0 0 < ov < 1
      if (l3 and (m_ov > 0) and (m_ov < 1))
        return OM;
      // om+ov==1
      if (abs(m_ok) < FLRW_EQ_TOL)
        return OM_OV_1;
      // a2 b=2
      if (abs(m_b - 2) < FLRW_EQ_TOL)
        return A2_1;
      // om+ov!=1
      // a1 b<0 || b>2
      if ((m_b < 0) || (m_b > 2))
        return A1;

      // a2 0<b<2
      if ((m_b > 0) && (m_b < 2))
        return A2_2;
      //
      return NO_CASE;
    }

    double flrw::hubble(double z) const
    {
      return m_hu * sqrt(m_om * pow<3> (1 + z) + m_ok * pow<2> (1 + z) + m_ov);
    }

    double flrw::lt(double z) const
    {
      // de Sitter's Universe age is infinity
      // but look-back time is valid
      if (m_case == OM_DS)
        return m_t_h * log(1 + z);
      return m_universe_age - age(z);
    }

    double flrw::dc(double z) const
    {
      return dc(z, dm(z));
    }

    double flrw::dc(double z, double dm) const
    {
      switch (m_case)
      {
        // Flat cases
        case OV_EDS: // EdS
        case OM_DS: // dS
        case OM_OV_1: // Flat
          return dm;
        default:
        {
          const double r = dm / m_r_h;
          return m_r_h * asinc(m_kap, m_sqok, r);
        }
      }
    }

    double flrw::dm(double z) const
    {
      return dm(z, dl(z));
    }

    double flrw::dm(double z, double dl) const
    {
      return dl / (1. + z);
    }

    double flrw::da(double z) const
    {
      return da(z, dl(z));
    }

    double flrw::da(double z, double dl) const
    {
      return dl / pow<2> (1 + z);
    }

    double flrw::DM(double z) const
    {
      return 5 * log10(dl(z)) + 25;
    }

    double flrw::vol(double z) const
    {
      return vol(z, dm(z, dl(z)));
    }

    double flrw::vol(double z, double dm) const
    {
      switch (m_case)
      {
        // Flat cases
        case OV_EDS: // EdS
        case OM_DS: // dS
        case OM_OV_1: // Flat
          return pow<3> (dm) / 3.0;
        default:
        {
          const double r = dm / m_r_h;
          const double scale = pow<3> (m_r_h);
          return scale * (r * sqrt(1 + m_ok * pow<2> (r)) - asinc(m_kap,
              m_sqok, r)) / (2 * m_ok);
        }
      }
    }

    flrw_cache::flrw_cache(double hubble, double matter, double vacuum) :
      metrics::flrw(hubble, matter, vacuum)
    {
    }

    bool flrw_cache::set_hubble(double hubble_parameter)
    {
      metrics::flrw::set_hubble(hubble_parameter);
      m_cache.recompute();
      return true;
    }

    bool flrw_cache::set_matter(double matter_density)
    {
      metrics::flrw::set_matter(matter_density);
      m_cache.recompute();
      return true;
    }

    bool flrw_cache::set_vacuum(double vacuum_energy_density)
    {
      metrics::flrw::set_vacuum(vacuum_energy_density);
      m_cache.recompute();
      return true;
    }

    double flrw_cache::hubble(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.hubble;
    }

    double flrw_cache::dc(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.dc;
    }

    double flrw_cache::da(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.da;
    }

    double flrw_cache::dm(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.dm;
    }

    double flrw_cache::dl(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.dl;
    }

    double flrw_cache::DM(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.DM;
    }

    double flrw_cache::vol(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.vol;
    }

    double flrw_cache::age() const
    {
      return m_cache.age_0;
    }

    double flrw_cache::age(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.age;
    }

    double flrw_cache::lt(double z) const
    {
      if (!m_cache.can_use(z))
      {
        m_cache.initialize(*this, z);
      }
      return m_cache.lt;
    }

    void flrw_cache::Cache::initialize(const metrics::flrw& metric, double zz)
    {
      // redshift
      z = zz;
      // hubble
      hubble = metric.hubble(z);
      // dl
      dl = metric.dl(z);
      // dm
      dm = metric.dm(z, dl);
      // da
      da = metric.da(z, dl);
      // dc
      dc = metric.dc(z, dm);
      // DM (check z > 0)
      if (z > 0)
        DM = 5. * log10(dl) + 25.;
      else
        DM = -1.;
      // Vol
      vol = metric.vol(z, dm);
      // Age
      age_0 = metric.age();
      age = metric.age(z);
      // Look-back time
      lt = age_0 - age;
    }

    bool flrw_cache::Cache::can_use(double zz) const
    {
      if (z == zz)
        return true;
      return false;
    }

    void flrw_cache::Cache::scale(double rh, double th)
    {
      dl /= rh;
      dm /= rh;
      da /= rh;
      dc /= rh;
      if (z > 0)
        DM = 5. * log10(dl) + 25.;
      else
        DM = -1.;
      vol /= pow<3> (rh);
      age /= th;
      lt /= th;
    }

    void flrw_cache::Cache::recompute()
    {
      z = -1;
    }

  } //namespace metrics

} //namespace milia

std::ostream& operator<<(std::ostream& os, milia::metrics::flrw& iflrw)
{
  os << iflrw.to_string();
  return os;
}
