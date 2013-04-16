/*
 * Copyright 2008-2013 Sergio Pascual
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <memory>

#include "flrw_nat.h"

#include "flrw_prec.h"
#include "metric.h"
#include "util.h"

#include "flrw_nat_impl.h"
#include "flatmodel.h"

using std::abs;

namespace milia
{

 namespace impl {

    flrw_nat_impl* flrw_nat_impl::construct(double matter, double vacuum)
    {
      return new flrw_nat_OV_EDS();
    }

 } //namespace impl
} //namespace milia

