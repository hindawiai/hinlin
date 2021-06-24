<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2012 QLogic Corporation
 */

/*
 * Driver debug definitions.
 */
/* #घोषणा QL_DEBUG  */			/* DEBUG messages */
/* #घोषणा QL_DEBUG_LEVEL_3  */		/* Output function tracing */
/* #घोषणा QL_DEBUG_LEVEL_4  */
/* #घोषणा QL_DEBUG_LEVEL_5  */
/* #घोषणा QL_DEBUG_LEVEL_7  */
/* #घोषणा QL_DEBUG_LEVEL_9  */

#घोषणा QL_DEBUG_LEVEL_2	/* ALways enable error messagess */
#अगर defined(QL_DEBUG)
#घोषणा DEBUG(x)   करो अणुx;पूर्ण जबतक (0);
#अन्यथा
#घोषणा DEBUG(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर

#अगर defined(QL_DEBUG_LEVEL_2)
#घोषणा DEBUG2(x)      करो अणुअगर(ql4xextended_error_logging == 2) x;पूर्ण जबतक (0);
#घोषणा DEBUG2_3(x)   करो अणुx;पूर्ण जबतक (0);
#अन्यथा				/*  */
#घोषणा DEBUG2(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर				/*  */

#अगर defined(QL_DEBUG_LEVEL_3)
#घोषणा DEBUG3(x)      करो अणुअगर(ql4xextended_error_logging == 3) x;पूर्ण जबतक (0);
#अन्यथा				/*  */
#घोषणा DEBUG3(x)	करो अणुपूर्ण जबतक (0);
#अगर !defined(QL_DEBUG_LEVEL_2)
#घोषणा DEBUG2_3(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर				/*  */
#पूर्ण_अगर				/*  */
#अगर defined(QL_DEBUG_LEVEL_4)
#घोषणा DEBUG4(x)	करो अणुx;पूर्ण जबतक (0);
#अन्यथा				/*  */
#घोषणा DEBUG4(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर				/*  */

#अगर defined(QL_DEBUG_LEVEL_5)
#घोषणा DEBUG5(x)	करो अणुx;पूर्ण जबतक (0);
#अन्यथा				/*  */
#घोषणा DEBUG5(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर				/*  */

#अगर defined(QL_DEBUG_LEVEL_7)
#घोषणा DEBUG7(x)	करो अणुx; पूर्ण जबतक (0)
#अन्यथा				/*  */
#घोषणा DEBUG7(x)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/*  */

#अगर defined(QL_DEBUG_LEVEL_9)
#घोषणा DEBUG9(x)	करो अणुx;पूर्ण जबतक (0);
#अन्यथा				/*  */
#घोषणा DEBUG9(x)	करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर				/*  */
