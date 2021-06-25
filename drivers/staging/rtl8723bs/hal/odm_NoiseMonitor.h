<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 *****************************************************************************/
#अगर_अघोषित	__ODMNOISEMONITOR_H__
#घोषणा __ODMNOISEMONITOR_H__

#घोषणा	ODM_MAX_CHANNEL_NUM					38/* 14+24 */
काष्ठा noise_level अणु
	/* u8 value_a, value_b; */
	u8 value[MAX_RF_PATH];
	/* s8 sval_a, sval_b; */
	s8 sval[MAX_RF_PATH];

	/* s32 noise_a = 0, noise_b = 0, sum_a = 0, sum_b = 0; */
	/* s32 noise[ODM_RF_PATH_MAX]; */
	s32 sum[MAX_RF_PATH];
	/* u8 valid_cnt_a = 0, valid_cnt_b = 0, */
	u8 valid[MAX_RF_PATH];
	u8 valid_cnt[MAX_RF_PATH];

पूर्ण;


काष्ठा odm_noise_monitor अणु
	s8 noise[MAX_RF_PATH];
	s16 noise_all;
पूर्ण;

s16 ODM_InbandNoise_Monitor(
	व्योम *pDM_VOID,
	u8 bPauseDIG,
	u8 IGIValue,
	u32 max_समय
);

#पूर्ण_अगर
