/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0
*                                REL-4 Version 4.1.0
*
********************************************************************************
*
*      File             : lsp_az.h
*      Purpose          : Converts from the line spectral pairs (LSP) to
*                       : LP coefficients, for a 10th order filter.
*
********************************************************************************
*/
#ifndef lsp_az_h
#define lsp_az_h "$Id $"

/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
#include "codec_op_etsi.h"

/*
********************************************************************************
*                         DEFINITION OF DATA TYPES
********************************************************************************
*/

/*
********************************************************************************
*                         DECLARATION OF PROTOTYPES
********************************************************************************
*/
void Lsp_Az (
    Word16 lsp[],      /* (i)    : line spectral frequencies                */
    Word16 a[]         /* (o)    : predictor coefficients (order = 10)      */
);

#endif
