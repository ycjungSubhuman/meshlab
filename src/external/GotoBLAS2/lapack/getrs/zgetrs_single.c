/*********************************************************************/
/*                                                                   */
/*             Optimized BLAS libraries                              */
/*                     By Kazushige Goto <kgoto@tacc.utexas.edu>     */
/*                                                                   */
/* Copyright (c) The University of Texas, 2009. All rights reserved. */
/* UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING  */
/* THIS SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF      */
/* MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE,              */
/* NON-INFRINGEMENT AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY  */
/* THAT MIGHT OTHERWISE ARISE FROM COURSE OF DEALING OR USAGE OF     */
/* TRADE. NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH RESPECT TO   */
/* THE USE OF THE SOFTWARE OR DOCUMENTATION.                         */
/* Under no circumstances shall University be liable for incidental, */
/* special, indirect, direct or consequential damages or loss of     */
/* profits, interruption of business, or related expenses which may  */
/* arise from use of Software or Documentation, including but not    */
/* limited to those resulting from defects in Software and/or        */
/* Documentation, or loss or inaccuracy of data of any kind.         */
/*********************************************************************/

#include <stdio.h>
#include "common.h"

blasint CNAME(blas_arg_t *args, BLASLONG *range_m, BLASLONG *range_n, FLOAT *sa, FLOAT *sb, BLASLONG mypos) {

#if TRANS == 1
    LASWP_PLUS (args -> n, 1, args -> m, ZERO, ZERO, args -> b, args -> ldb, NULL, 0, args -> c, 1);

    TRSM_LNLU(args, range_m, range_n, sa, sb, 0);
    TRSM_LNUN(args, range_m, range_n, sa, sb, 0); 
#elif TRANS == 2
    TRSM_LTUN(args, range_m, range_n, sa, sb, 0);
    TRSM_LTLU(args, range_m, range_n, sa, sb, 0);
    
    LASWP_MINUS(args -> n, 1, args -> m, ZERO, ZERO, args -> b, args -> ldb, NULL, 0, args -> c, -1);
#elif TRANS == 3
    LASWP_PLUS (args -> n, 1, args -> m, ZERO, ZERO, args -> b, args -> ldb, NULL, 0, args -> c, 1);

    TRSM_LRLU(args, range_m, range_n, sa, sb, 0);
    TRSM_LRUN(args, range_m, range_n, sa, sb, 0);
#else
    TRSM_LCUN(args, range_m, range_n, sa, sb, 0);
    TRSM_LCLU(args, range_m, range_n, sa, sb, 0);

    LASWP_MINUS(args -> n, 1,    args -> m, ZERO, ZERO, args -> b, args -> ldb, NULL, 0, args -> c, -1);
#endif
   return 0;
  }
