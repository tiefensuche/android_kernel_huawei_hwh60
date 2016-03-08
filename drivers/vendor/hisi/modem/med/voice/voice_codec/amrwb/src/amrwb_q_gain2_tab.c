/*------------------------------------------------------*
 * Tables for function q_gain2()                        *
 *                                                      *
 *  g_pitch(Q14),  g_code(Q11)                          *
 *                                                      *
 * pitch gain are ordered in table to reduce complexity *
 * during quantization of gains.                        *
 *------------------------------------------------------*/
#include "amrwb_q_gain2_tab.h"

Word16 t_qua_gain6b[64*2] = {
   1566,  1332,
   1577,  3557,
   3071,  6490,
   4193, 10163,
   4496,  2534,
   5019,  4488,
   5586, 15614,
   5725,  1422,
   6453,   580,
   6724,  6831,
   7657,  3527,
   8072,  2099,
   8232,  5319,
   8827,  8775,
   9740,  2868,
   9856,  1465,
  10087, 12488,
  10241,  4453,
  10859,  6618,
  11321,  3587,
  11417,  1800,
  11643,  2428,
  11718,   988,
  12312,  5093,
  12523,  8413,
  12574, 26214,
  12601,  3396,
  13172,  1623,
  13285,  2423,
  13418,  6087,
  13459, 12810,
  13656,  3607,
  14111,  4521,
  14144,  1229,
  14425,  1871,
  14431,  7234,
  14445,  2834,
  14628, 10036,
  14860, 17496,
  15161,  3629,
  15209,  5819,
  15299,  2256,
  15518,  4722,
  15663,  1060,
  15759,  7972,
  15939, 11964,
  16020,  2996,
  16086,  1707,
  16521,  4254,
  16576,  6224,
  16894,  2380,
  16906,   681,
  17213,  8406,
  17610,  3418,
  17895,  5269,
  18168, 11748,
  18230,  1575,
  18607, 32767,
  18728, 21684,
  19137,  2543,
  19422,  6577,
  19446,  4097,
  19450,  9056,
  20371, 14885};

Word16 t_qua_gain7b[128*2] = {
    204,   441,
    464,  1977,
    869,  1077,
   1072,  3062,
   1281,  4759,
   1647,  1539,
   1845,  7020,
   1853,   634,
   1995,  2336,
   2351, 15400,
   2661,  1165,
   2702,  3900,
   2710, 10133,
   3195,  1752,
   3498,  2624,
   3663,   849,
   3984,  5697,
   4214,  3399,
   4415,  1304,
   4695,  2056,
   5376,  4558,
   5386,   676,
   5518, 23554,
   5567,  7794,
   5644,  3061,
   5672,  1513,
   5957,  2338,
   6533,  1060,
   6804,  5998,
   6820,  1767,
   6937,  3837,
   7277,   414,
   7305,  2665,
   7466, 11304,
   7942,   794,
   8007,  1982,
   8007,  1366,
   8326,  3105,
   8336,  4810,
   8708,  7954,
   8989,  2279,
   9031,  1055,
   9247,  3568,
   9283,  1631,
   9654,  6311,
   9811,  2605,
  10120,   683,
  10143,  4179,
  10245,  1946,
  10335,  1218,
  10468,  9960,
  10651,  3000,
  10951,  1530,
  10969,  5290,
  11203,  2305,
  11325,  3562,
  11771,  6754,
  11839,  1849,
  11941,  4495,
  11954,  1298,
  11975, 15223,
  11977,   883,
  11986,  2842,
  12438,  2141,
  12593,  3665,
  12636,  8367,
  12658,  1594,
  12886,  2628,
  12984,  4942,
  13146,  1115,
  13224,   524,
  13341,  3163,
  13399,  1923,
  13549,  5961,
  13606,  1401,
  13655,  2399,
  13782,  3909,
  13868, 10923,
  14226,  1723,
  14232,  2939,
  14278,  7528,
  14439,  4598,
  14451,   984,
  14458,  2265,
  14792,  1403,
  14818,  3445,
  14899,  5709,
  15017, 15362,
  15048,  1946,
  15069,  2655,
  15405,  9591,
  15405,  4079,
  15570,  7183,
  15687,  2286,
  15691,  1624,
  15699,  3068,
  15772,  5149,
  15868,  1205,
  15970,   696,
  16249,  3584,
  16338,  1917,
  16424,  2560,
  16483,  4438,
  16529,  6410,
  16620, 11966,
  16839,  8780,
  17030,  3050,
  17033, 18325,
  17092,  1568,
  17123,  5197,
  17351,  2113,
  17374,   980,
  17566, 26214,
  17609,  3912,
  17639, 32767,
  18151,  7871,
  18197,  2516,
  18202,  5649,
  18679,  3283,
  18930,  1370,
  19271, 13757,
  19317,  4120,
  19460,  1973,
  19654, 10018,
  19764,  6792,
  19912,  5135,
  20040,  2841,
  21234, 19833};



