/*
 * Copyright 2008 Sergio Pascual
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

#include "flrw.h"
#include "flrw_prec.h"
#include "exception.h"

#include <cmath>
#include <cstdlib>

// Provides M_SQRT3
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_ellint.h>

namespace
{
    static const double M_4THRT3 = sqrt(M_SQRT3);
}

namespace milia
{

    namespace metrics
    {

        double flrw::distance_luminosity(double z) const
        {
            switch (m_case) {
            case OM_OV_0:
                return m_r_h * 0.5 * z * (z + 2.);
                break;
            case OV_1:
            case OV_2:
            case OV_3:
                return m_r_h * 2. * ((2. - m_om * (1. - z) - (2. - m_om) * sqrt(1
                                      + m_om * z))) / gsl_pow_2(m_om);
                break;
            case OM:
                // m_ov == 0 corresponds to  OM_OV_0
                if(m_ov == 1) {
                    return m_r_h * z;
                } else {
                    const double par = abs(m_ok / m_ov);

                    if(m_ov > 1) {
                        return m_r_h / m_ov * ((1. + z) * sqrt(1 - par) - sqrt(1 - par * gsl_pow_2(1. + z )));
                    } else if (m_ov < 0) {
                        return m_r_h / m_ov * (sqrt(par * gsl_pow_2(1. + z ) - 1.) - (1. + z) * sqrt(par - 1.));
                    } else  // 0 < m_ov < 1
                        return m_r_h / m_ov * ((1. + z) * sqrt(1 + par) - sqrt(1 + par * gsl_pow_2(1. + z )));
                }
                break;
            case A1: {
                    //om+ol != 1 and (b<0 || b>2) {
                    const double v = cbrt(m_kap * (m_b - 1.) + sqrt(m_b * (m_b - 2.)));
                    const double y=(-1.+m_kap*(v+1./v))/3.;
                    const double A=sqrt(y*(3.*y+2.));
                    const double g=1./sqrt(A);
                    const double k = sqrt(0.5+0.25*g*g*(v+1./v));
                    const double sup = m_om / abs(m_ok);
                    const double phi = acos(((1.+z)*sup+m_kap*y-A)/((1.+z)*sup+m_kap*y+A));
                    const double phi0 = acos((sup+m_kap*y-A)/(sup+m_kap*y+A));
                    if (m_b > 0)
                        return m_r_h*(1+z)/sqrt(abs(m_ok))*sin(g*(gsl_sf_ellint_F(phi0, k,
                                                               PREC)-gsl_sf_ellint_F(phi, k, PREC)));
                    else
                        return m_r_h*(1+z)/sqrt(abs(m_ok))*sinh(g*(gsl_sf_ellint_F(phi0, k,
                                                                PREC)-gsl_sf_ellint_F(phi, k, PREC)));
                }
            case A2_1:
                // b=2
            case A2_2:
                // 0 < b < 2
                {
                    const double arg0=acos(1.-m_b)/3.;
                    const double arg1=m_om/abs(m_ok);
                    const double y1=(-1.+cos(arg0)+M_SQRT3*sin(arg0))/3.;
                    const double y2=(-1.-2.*cos(arg0))/3.;
                    const double y3=(-1.+cos(arg0)-M_SQRT3*sin(arg0))/3.;
                    const double g=2./sqrt(y1-y2);
                    const double k=sqrt((y1-y3)/(y1-y2));
                    const double phi=asin(sqrt((y1-y2)/((1+z)*arg1+y1)));
                    const double phi0=asin(sqrt((y1-y2)/(arg1+y1)));
                    return m_r_h*(1.+z)/sqrt(abs(m_ok))*sin(g*(gsl_sf_ellint_F(phi0, k,
                                                            PREC)-gsl_sf_ellint_F(phi, k, PREC)));
                }
            case OM_OV_1: {
                    // om + ol == 1
                    const double k=0.9659258263; // sqrt(1/2 + sqrt(3) / 4)
                    const double arg0 = cbrt(1. / m_om - 1.);
                    const double down = 1 + (1 + M_SQRT3) * arg0;
                    const double up = 1 + (1 - M_SQRT3) * arg0;
                    const double phi=acos((z+up)/(z+down));
                    const double phi0=acos(up/down);
                    return m_r_h * (1 + z) / (M_4THRT3 * sqrt(m_om) * sqrt(arg0)) *
                           (gsl_sf_ellint_F(phi0, k, PREC) - gsl_sf_ellint_F(phi, k, PREC));
                }
                break;
            }
            return -1;
        }

    } // namespace metrics

}
// namespace milia