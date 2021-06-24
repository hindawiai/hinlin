<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश "global.h"

काष्ठा GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3324[] = अणु
/*  ClkRange, DVP0, DVP0DataDriving,  DVP0ClockDriving, DVP1,
					DVP1Driving, DFPHigh, DFPLow */
/*  CR96, SR2A[5], SR1B[1], SR2A[4], SR1E[2], CR9B,
					SR65,        CR97,    CR99   */
	/* LCK/VCK < 30000000 will use this value */
	अणुDPA_CLK_RANGE_30M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	 0x00पूर्ण,
	/* 30000000 < LCK/VCK < 50000000 will use this value */
	अणुDPA_CLK_RANGE_30_50M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	 0x00पूर्ण,
	/* 50000000 < LCK/VCK < 70000000 will use this value */
	अणुDPA_CLK_RANGE_50_70M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00पूर्ण,
	/* 70000000 < LCK/VCK < 100000000 will use this value */
	अणुDPA_CLK_RANGE_70_100M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00पूर्ण,
	/* 100000000 < LCK/VCK < 15000000 will use this value */
	अणुDPA_CLK_RANGE_100_150M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
	 0x00पूर्ण,
	/* 15000000 < LCK/VCK will use this value */
	अणुDPA_CLK_RANGE_150M, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0E, 0x00,
	 0x00पूर्ण,
पूर्ण;

काष्ठा GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3327[] = अणु
/*  ClkRange,DVP0, DVP0DataDriving,  DVP0ClockDriving, DVP1,
					DVP1Driving, DFPHigh,   DFPLow */
/*   CR96, SR2A[5], SR1B[1], SR2A[4], SR1E[2], CR9B,
					SR65,        CR97,      CR99   */
/* LCK/VCK < 30000000 will use this value */
अणुDPA_CLK_RANGE_30M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01पूर्ण,
/* 30000000 < LCK/VCK < 50000000 will use this value */
अणुDPA_CLK_RANGE_30_50M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01पूर्ण,
/* 50000000 < LCK/VCK < 70000000 will use this value */
अणुDPA_CLK_RANGE_50_70M, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x01पूर्ण,
/* 70000000 < LCK/VCK < 100000000 will use this value */
अणुDPA_CLK_RANGE_70_100M, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x03पूर्ण,
/* 100000000 < LCK/VCK < 15000000 will use this value */
अणुDPA_CLK_RANGE_100_150M, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x02पूर्ण,
/* 15000000 < LCK/VCK will use this value */
अणुDPA_CLK_RANGE_150M, 0x00, 0x20, 0x00, 0x10, 0x00, 0x03, 0x00, 0x0D, 0x03पूर्ण,
पूर्ण;

/* For VT3364: */
काष्ठा GFX_DPA_SETTING GFX_DPA_SETTING_TBL_VT3364[] = अणु
/*  ClkRange,DVP0, DVP0DataDriving,  DVP0ClockDriving, DVP1,
					DVP1Driving, DFPHigh,   DFPLow */
/*   CR96, SR2A[5], SR1B[1], SR2A[4], SR1E[2], CR9B,
					SR65,        CR97,      CR99   */
/* LCK/VCK < 30000000 will use this value */
अणुDPA_CLK_RANGE_30M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
/* 30000000 < LCK/VCK < 50000000 will use this value */
अणुDPA_CLK_RANGE_30_50M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
/* 50000000 < LCK/VCK < 70000000 will use this value */
अणुDPA_CLK_RANGE_50_70M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
/* 70000000 < LCK/VCK < 100000000 will use this value */
अणुDPA_CLK_RANGE_70_100M, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
/* 100000000 < LCK/VCK < 15000000 will use this value */
अणुDPA_CLK_RANGE_100_150M, 0x03, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
/* 15000000 < LCK/VCK will use this value */
अणुDPA_CLK_RANGE_150M, 0x01, 0x00, 0x02, 0x10, 0x00, 0x03, 0x00, 0x00, 0x08पूर्ण,
पूर्ण;
