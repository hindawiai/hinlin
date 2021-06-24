<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित	__RTL_92S_DM_H__
#घोषणा __RTL_92S_DM_H__

क्रमागत dm_dig_alg अणु
	DIG_ALGO_BY_FALSE_ALARM = 0,
	DIG_ALGO_BY_RSSI	= 1,
	DIG_ALGO_BEFORE_CONNECT_BY_RSSI_AND_ALARM = 2,
	DIG_ALGO_BY_TOW_PORT = 3,
	DIG_ALGO_MAX
पूर्ण;

क्रमागत dm_dig_two_port_alg अणु
	DIG_TWO_PORT_ALGO_RSSI = 0,
	DIG_TWO_PORT_ALGO_FALSE_ALARM = 1,
पूर्ण;

क्रमागत dm_dig_dbg अणु
	DM_DBG_OFF = 0,
	DM_DBG_ON = 1,
	DM_DBG_MAX
पूर्ण;

क्रमागत dm_dig_sta अणु
	DM_STA_DIG_OFF = 0,
	DM_STA_DIG_ON,
	DM_STA_DIG_MAX
पूर्ण;

क्रमागत dm_ratr_sta अणु
	DM_RATR_STA_HIGH = 0,
	DM_RATR_STA_MIDDLEHIGH = 1,
	DM_RATR_STA_MIDDLE = 2,
	DM_RATR_STA_MIDDLELOW = 3,
	DM_RATR_STA_LOW = 4,
	DM_RATR_STA_ULTRALOW = 5,
	DM_RATR_STA_MAX
पूर्ण;

#घोषणा DM_TYPE_BYFW			0
#घोषणा DM_TYPE_BYDRIVER		1

#घोषणा	TX_HIGH_PWR_LEVEL_NORMAL	0
#घोषणा	TX_HIGH_PWR_LEVEL_LEVEL1	1
#घोषणा	TX_HIGH_PWR_LEVEL_LEVEL2	2

#घोषणा	HAL_DM_DIG_DISABLE		BIT(0)	/* Disable Dig */
#घोषणा	HAL_DM_HIPWR_DISABLE		BIT(1)	/* Disable High Power */

#घोषणा	TX_HIGHPWR_LEVEL_NORMAL		0
#घोषणा	TX_HIGHPWR_LEVEL_NORMAL1	1
#घोषणा	TX_HIGHPWR_LEVEL_NORMAL2	2

#घोषणा	TX_POWER_NEAR_FIELD_THRESH_LVL2	74
#घोषणा	TX_POWER_NEAR_FIELD_THRESH_LVL1	67

#घोषणा	DM_DIG_HIGH_PWR_THRESH_HIGH	75
#घोषणा	DM_DIG_HIGH_PWR_THRESH_LOW	70
#घोषणा	DM_DIG_MIN_NETCORE		0x12

व्योम rtl92s_dm_watchकरोg(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_dm_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
