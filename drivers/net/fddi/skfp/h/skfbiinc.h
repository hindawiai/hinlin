<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

#अगर_अघोषित	_SKFBIINC_
#घोषणा _SKFBIINC_

#समावेश "supern_2.h"

/*
 * special defines क्रम use पूर्णांकo .यंत्र files
 */
#घोषणा ERR_FLAGS (FS_MSRABT | FS_SEAC2 | FS_SFRMERR | FS_SFRMTY1)

#अगर_घोषित PCI
#घोषणा	IMASK_FAST	(IS_PLINT1 | IS_PLINT2 | IS_TIMINT | IS_TOKEN | \
			 IS_MINTR2 | IS_MINTR3 | IS_R1_P | \
			 IS_R1_C | IS_XA_C | IS_XS_C)
#पूर्ण_अगर

#अगर_घोषित	PCI
#घोषणा	ISR_MASK	(IS_MINTR1 | IS_R1_F | IS_XS_F| IS_XA_F | IMASK_FAST)
#अन्यथा
#घोषणा	ISR_MASK	(IS_MINTR1 | IS_MINTR2 | IMASK_FAST)
#पूर्ण_अगर

#घोषणा	FMA_FM_CMDREG1	FMA(FM_CMDREG1)
#घोषणा	FMA_FM_CMDREG2	FMA(FM_CMDREG2)
#घोषणा	FMA_FM_STMCHN	FMA(FM_STMCHN)
#घोषणा	FMA_FM_RPR	FMA(FM_RPR)
#घोषणा	FMA_FM_WPXA0	FMA(FM_WPXA0)
#घोषणा	FMA_FM_WPXA2	FMA(FM_WPXA2)
#घोषणा	FMA_FM_MARR	FMA(FM_MARR)
#घोषणा	FMA_FM_MARW	FMA(FM_MARW)
#घोषणा	FMA_FM_MDRU	FMA(FM_MDRU)
#घोषणा	FMA_FM_MDRL	FMA(FM_MDRL)
#घोषणा	FMA_ST1L	FMA(FM_ST1L)
#घोषणा	FMA_ST1U	FMA(FM_ST1U)
#घोषणा	FMA_ST2L	FMA(FM_ST2L)
#घोषणा	FMA_ST2U	FMA(FM_ST2U)
#अगर_घोषित	SUPERNET_3
#घोषणा FMA_ST3L	FMA(FM_ST3L)
#घोषणा FMA_ST3U	FMA(FM_ST3U)
#पूर्ण_अगर

#घोषणा TMODE_RRQ	RQ_RRQ
#घोषणा TMODE_WAQ2	RQ_WA2
#घोषणा	HSRA		HSR(0)


#घोषणा FMA_FM_ST1L	FMA_ST1L
#घोषणा FMA_FM_ST1U	FMA_ST1U
#घोषणा FMA_FM_ST2L	FMA_ST2L
#घोषणा FMA_FM_ST2U	FMA_ST2U
#अगर_घोषित	SUPERNET_3
#घोषणा FMA_FM_ST3L	FMA_ST3L
#घोषणा FMA_FM_ST3U	FMA_ST3U
#पूर्ण_अगर

#घोषणा FMA_FM_SWPR	FMA(FM_SWPR)

#घोषणा FMA_FM_RPXA0	FMA(FM_RPXA0)

#घोषणा	FMA_FM_RPXS	FMA(FM_RPXS)
#घोषणा	FMA_FM_WPXS	FMA(FM_WPXS)

#घोषणा	FMA_FM_IMSK1U	FMA(FM_IMSK1U)
#घोषणा	FMA_FM_IMSK1L	FMA(FM_IMSK1L)

#घोषणा	FMA_FM_EAS	FMA(FM_EAS)
#घोषणा	FMA_FM_EAA0	FMA(FM_EAA0)

#घोषणा	TMODE_WAQ0	RQ_WA0
#घोषणा TMODE_WSQ	RQ_WSQ

/* Define शेष क्रम DRV_PCM_STATE_CHANGE */
#अगर_अघोषित	DRV_PCM_STATE_CHANGE
#घोषणा	DRV_PCM_STATE_CHANGE(smc,plc,p_state)	/* nothing */
#पूर्ण_अगर

/* Define शेष क्रम DRV_RMT_INDICATION */
#अगर_अघोषित	DRV_RMT_INDICATION
#घोषणा	DRV_RMT_INDICATION(smc,i)	/* nothing */
#पूर्ण_अगर

#पूर्ण_अगर	/* n_SKFBIINC_ */

