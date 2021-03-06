/*
 * Copyright 2008-2012 Sergio Pascual
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

#include "FlrwTestDataMixin.h"

   /* These tests are removed
     * {50.,0.,-1.} : recollapse
     * {50., 0.,1.5} : recollapse
     * {50., 1.5, 0.} : no Big Bang
     * A2_1 A2_2 recollapse
     * O_m + O_v != 1 and (b > 2 or b < 0) case A1
     * O_m + O_v != 1 and 0 < b < 2        case A2_2
     */

const double FlrwTestDataMixin::lum_model[][2] = {
    {0.0, 0.0}, // OM_OV_0
    {0.3, 0.7}, // OM_OV_1
    {0.0, 0.5}, // OM
    {0.0, 1.0}, // OM_DS
    {0.5, 0.}, // OV_1
    {1.5, 0.}, // OV_2 makes the Universe recollapse
    {1.0, 0.}, // OV_EDS
    {0.3, 0.2}, // A1
    {1.5, 0.008665856}, // A2_1 recollapse
    {1.5, 0.007},    // A2_2
};

// {0.3, 1.713460403} breaks
// {0.7, 2.254425343} exception
// {0.7, 3} exception
// {0.3, 2.} exception

const double FlrwTestDataMixin::lum_table[][5][3] =
{
    {{0.0010005, 0.001, 1e-8}, // OM_OV_0
     {0.01005, 0.01, 1e-7},
     {0.105, 0.1, 1e-6},
     {1.5, 1, 1e-5},
     {60, 10, 1e-4}},
    {{0.00100077472630146, 0.001, 1e-8}, // OM_OV_1
     {0.0100772263424244, 0.01, 1e-7},
     {0.107477672260662, 0.1, 1e-6},
     {1.54285413285213, 1, 1e-5},
     {24.2467481030569, 10, 1e-4}},
    {{0.00100074987507797, 0.001, 1e-8}, // OM
     {0.0100748757773573, 0.01, 1e-7},
     {0.10738243542085, 0.1, 1e-6},
     {1.67544467966324, 1, 1e-5},
     {70.1745071300536, 10, 1e-4}},
    {{0.001001, 0.001, 1e-8}, // OM_DS
     {0.0101, 0.01, 1e-7},
     {0.11, 0.1, 1e-6},
     {2, 1, 1e-5},
     {110, 10, 1e-3}},
    {{0.00100037, 0.001, 1e-08}, // OV_1
     {0.0100374, 0.01, 1e-07},
     {0.103659, 0.1, 1e-06},
     {1.30306, 1, 1e-05},
     {22.6061, 10, 0.0001}},
    {{0.00100012, 0.001, 1e-08},  // OV_2
     {0.0100124, 0.01, 1e-07},
     {0.101164, 0.1, 1e-06},
     {1.07505, 1, 1e-05},
     {12, 10, 0.0001}},
    {{0.00100025, 0.001, 1e-05},  // OV_EDS
     {0.0100249, 0.01, 0.0001},
     {0.102382, 0.1, 0.001},
     {1.17157, 1, 0.01},
     {15.3668, 10, 0.1}},
    {{0.00100052, 0.001, 1e-05},  // A1
     {0.0100523, 0.01, 0.0001},
     {0.105086, 0.1, 0.001},
     {1.41268, 1, 0.01},
     {28.0628, 10, 0.1}},
   {{7.8857087429991, 0.001, 1e-5}, // A2_1
     {78.8935170063695, 0.01, 1e-4},
     {792.123728711388, 0.1, 1e-3},
     {8062.13711960825, 1, 1e-2},
     {82400.7313510225, 10, 1}},
    {{7.9083906462936, 0.001, 1e-5}, // A2_2
     {79.1172155869955, 0.01, 1e-4},
     {794.101243918663, 0.1, 1e-3},
     {8074.20017301852, 1, 1e-2},
     {82510.3087399524, 10, 1e-1}},
};

const double FlrwTestDataMixin::ang_model[][2] = {
    {1.0, 0.},
    };

const double FlrwTestDataMixin::ang_table[][5][3] =
  {{{0.000998252372081318, 0.001, 1e-5},
    {0.00982734611883356, 0.01, 1e-4},
    {0.0846134740989231, 0.1, 1e-3},
    {0.292893218813452, 1, 1e-2},
    {0.126997937349498, 10, 1e-3}}};

const double FlrwTestDataMixin::cotran_model[][2] = {
    {1.0, 0.},
    };

const double FlrwTestDataMixin::cotran_table[][5][3] =
  {{{0.000999250624453399, 0.001, 1e-5},
    {0.0099256195800219, 0.01, 1e-4},
    {0.0930748215088154, 0.1, 1e-3},
    {0.585786437626905, 1, 1e-2},
    {1.39697731084447, 10, 1e-1}}};

const double FlrwTestDataMixin::com_model[][2] = {
    {1.0, 0.},
    {0.5, 0.6},
    {0.5, 0.4},
    };

const double FlrwTestDataMixin::com_table[][5][3] =
  {
      {{0.000999250624453399, 0.001, 1e-8},
       {0.0099256195800219, 0.01, 1e-7},
       {0.0930748215088154, 0.1, 1e-6},
       {0.585786437626905, 1, 1e-5},
       {1.39697731084447, 10, 1e-4}},
      {{0.00099967497802137, 0.001, 1e-8},
       {0.0099674789833964, 0.01, 1e-7},
       {0.0967381686976204, 0.1, 1e-6},
       {0.713117467943536, 1, 1e-5},
       {1.86997191796328, 10, 1e-4}},
     {{0.000999575094644594, 0.001, 1e-8},
       {0.0099575952110075, 0.01, 1e-7},
       {0.0958500887970284, 0.1, 1e-6},
       {0.681391296690221, 1, 1e-5},
       {1.78694247364436, 10, 1e-4}}
  };

const double FlrwTestDataMixin::age_model[][2] = {
    {0.0, 0.0}, // OM_OV_0
    {0.3, 0.7}, // OM_OV_1
    {0.0, 0.5}, // OM
    {0.5, 0.}, // OV_1
    {1.0, 0.}, // OV_EDS
    {0.3, 0.2}, // A1
    {0.23, 0.73}, // A1, direct integration
    {1.5, 0.}, // OV_2 
    {1.5, 0.008665856}, // A2_1
    {1.5, 0.007},    // A2_2
};

const double FlrwTestDataMixin::age_table[][5][3] =
{
 {{1.00, 0,1e-5}, // OM_OV_0
  {0.909090909090909, 0.1, 1e-6},
  {0.5, 1, 1e-6},
  {0.0909090909090909, 10, 1e-7},
  {0.009900990099009, 100, 1e-8}},
 {{0.964099381639469, 0, 1e-6}, // OM_OV_1
  {0.870939682668294, 0.1, 1e-6},
  {0.411759550867871, 1, 1e-6},
  {0.0333527982200001, 10, 1e-7},
  {0.00119912895252357, 100, 1e-8}},
 {{1.24645048028046, 0, 1e-5}, // OM
  {1.15344516859466, 0.1, 1e-5},
  {0.6805362893736, 1, 1e-6},
  {0.128388438074633, 10, 1e-6},
  {0.014001885718741, 100, 1e-7}},
 {{0.753549519719539, 0, 1e-6},  // OV_1
  {0.663714442215256, 0.1, 1e-6},
  {0.293515011938877, 1, 1e-6},
  {0.0251701404285369, 10, 1e-7},
  {0.000926097248061558, 100, 1e-9}},
 {{0.666667, 0, 0.01},   // OV_3
  {0.577856, 0.1, 0.0001},
  {0.235702, 1, 1e-05},
  {0.0182734, 10, 1e-06},
  {0.00065679, 100, 1e-07}},
 {{0.844023, 0, 0.0001},  // A1
  {0.752972, 0.1, 0.0001},
  {0.351653, 1, 1e-05},
  {0.0319559, 10, 1e-06},
  {0.00119324, 100, 1e-07}},
 {{1.02148, 0, 0.0001}, // A1, direct integration
  {0.928015, 0.1, 0.0001},
  {0.453876, 1, 1e-05},
  {0.0379087, 10, 1e-06},
  {0.00136879, 100, 1e-07}},
 {{0.611259, 0, 0.0001}, // OV_2
  {0.523428, 0.1, 0.0001},
  {0.203037, 1, 1e-05},
  {0.0150581, 10, 1e-06},
  {0.000536799, 100, 1e-07}}, 
 {{11.9652153000123, 0, 1e-4}, // A2_1
  {10.2470057537261, 0.1, 1e-4},
  {3.9739607157997, 1, 1e-5},
  {0.294520478816483, 10, 1e-6},
  {0.0104977358097757, 100, 1e-7}},
 {{11.9629969132962, 0, 1e-4}, // A2_2
  {10.2449013226402, 0.1, 1e-4},
  {3.97330714539515, 1, 1e-5},
  {0.294511383174483, 10, 1e-6},
  {0.0104977010927877, 100, 1e-7}},
};

const double FlrwTestDataMixin::vol_model[][2] = {
    {0.5, 0.},
    {0.31, 0.70},
    {1.0, 0.},
    {0.27, 0.73},
};

// {0.3, 1.713460403} breaks
// {0.7, 2.254425343} exception
// {0.7, 3} exception
// {0.3, 2.} exception

const double FlrwTestDataMixin::vol_table[][5][3] =
{
  {
    {3.32709204371034e-10, 1e-3, 1e-14},
    {3.27169442482234e-07, 1e-2, 1e-11},
    {0.000278576986986676, 1e-1, 1e-8},
    {0.0869075037164473, 1 , 1e-6},
    {1.97269773430209, 10, 1e-4},
  },
  {
    {3.33105841087561e-10, 1e-3, 1e-14},
    {3.31058538742545e-07, 1e-2, 1e-11},
    {0.000310671938196644, 1e-1, 1e-8},
    {0.151512864390907, 1, 1e-5},
    {3.44711884730253, 10, 1e-4}
  },
  {
	  {3.32584519210168e-10, 1e-3, 1e-14},
	  {3.2595047863571e-07, 1e-2, 1e-11},
	  {0.000268766652007378, 1e-1, 1e-8},
	  {0.0670033755922231, 1, 1e-6},
	  {0.908754978025706, 10, 1e-5},
  },
  {
	  {3.33130821458192e-10, 1e-3, 1e-14},
	  {3.31307201519457e-07, 1e-2,1e-11},
	  {0.000313028445573882, 1e-1, 1e-8},
	  {0.161654583682334, 1, 1e-5},
	  {3.99680922122125, 10, 1e-4},
  },

};
