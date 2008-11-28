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

#ifndef MILIA_SCHECHTER_H
#define MILIA_SCHECHTER_H

#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

namespace milia
{
  namespace luminosity_functions
  {
    /**
     * A Schechter luminosity function
     */
    class schechter
    {
      public:

        /**
         * Constructor with evolution
         */
        template<typename EvolP, typename EvolL, typename EvolA> schechter(
            const EvolP& phi_star, const EvolL& lum_star, const EvolA& alpha,
            double z) :
          m_phi_star(phi_star), m_lum_star(lum_star), m_alpha(alpha),
              m_current_z(z)
        {
        }

        /**
         * Constructor without evolution
         */
        schechter(double phi_star, double lum_star, double alpha, double z);

        /**
         * Constructor with evolution
         */
        schechter(const boost::function<double(double)>& phi_star, const boost::function<double(double)>& lum_star, const boost::function<double(double)>& alpha, double z);

        double function(double lum) const;
        double object_density(double lum1, double lum2) const;
        double luminosity_density(double lum1, double lum2) const;
        void evolve(double z);
        boost::tuple<double, double, double> parameters() const;
      private:
        boost::function<double(double)> m_phi_star;
        boost::function<double(double)> m_lum_star;
        boost::function<double(double)> m_alpha;
        double m_current_z;
        double function_normalized(double x) const;
    };

  } // namespace luminosity_functions

} // namespace milia


#endif /* MILIA_SCHECHTER_H */
