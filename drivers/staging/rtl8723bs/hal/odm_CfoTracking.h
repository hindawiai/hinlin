<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__ODMCFOTRACK_H__
#घोषणा    __ODMCFOTRACK_H__

#घोषणा		CFO_TH_XTAL_HIGH		20		/*  kHz */
#घोषणा		CFO_TH_XTAL_LOW			10		/*  kHz */
#घोषणा		CFO_TH_ATC			80		/*  kHz */

काष्ठा cfo_tracking अणु
	bool bATCStatus;
	bool largeCFOHit;
	bool bAdjust;
	u8 CrystalCap;
	u8 DefXCap;
	पूर्णांक CFO_tail[2];
	पूर्णांक CFO_ave_pre;
	u32 packetCount;
	u32 packetCount_pre;

	bool bForceXtalCap;
	bool bReset;
पूर्ण;

व्योम ODM_CfoTrackingReset(व्योम *pDM_VOID
);

व्योम ODM_CfoTrackingInit(व्योम *pDM_VOID);

व्योम ODM_CfoTracking(व्योम *pDM_VOID);

व्योम ODM_ParsingCFO(व्योम *pDM_VOID, व्योम *pPktinfo_VOID, s8 *pcfotail);

#पूर्ण_अगर
