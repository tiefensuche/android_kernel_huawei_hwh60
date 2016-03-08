/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0
*                                REL-4 Version 4.1.0
*
********************************************************************************
*
*      File             : sqrt_l.tab
*      Purpose          : Table for routine sqrt_l_exp()
*      $Id $
*
********************************************************************************
*/
#include "codec_op_etsi.h"
#include "cnst.h"

/* table[i] = sqrt((i+16)*2^-6) * 2^15, i.e. sqrt(x) scaled Q15 */

static const Word16 table[49] =
{
 16384,
 16888,
 17378,
 17854,
 18318,
 18770,
 19212,
 19644,
 20066,
 20480,
 20886,
 21283,
 21674,
 22058,
 22435,
 22806,
 23170,
 23530,
 23884,
 24232,
 24576,
 24915,
 25249,
 25580,
 25905,
 26227,
 26545,
 26859,
 27170,
 27477,
 27780,
 28081,
 28378,
 28672,
 28963,
 29251,
 29537,
 29819,
 30099,
 30377,
 30652,
 30924,
 31194,
 31462,
 31727,
 31991,
 32252,
 32511,
 32767
};
