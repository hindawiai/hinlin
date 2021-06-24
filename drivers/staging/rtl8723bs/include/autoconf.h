<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

/*
 * Automatically generated C config: करोn't edit
 */

/*
 * Functions Config
 */

#अगर_अघोषित CONFIG_WIRELESS_EXT
#त्रुटि CONFIG_WIRELESS_EXT needs to be enabled क्रम this driver to work
#पूर्ण_अगर

/*
 * Auto Config Section
 */
#घोषणा LPS_RPWM_WAIT_MS 300
#अगर_अघोषित DISABLE_BB_RF
#घोषणा DISABLE_BB_RF	0
#पूर्ण_अगर

#अगर DISABLE_BB_RF
	#घोषणा HAL_MAC_ENABLE	0
	#घोषणा HAL_BB_ENABLE		0
	#घोषणा HAL_RF_ENABLE		0
#अन्यथा
	#घोषणा HAL_MAC_ENABLE	1
	#घोषणा HAL_BB_ENABLE		1
	#घोषणा HAL_RF_ENABLE		1
#पूर्ण_अगर

/*
 * Platक्रमm dependent
 */
#घोषणा WAKEUP_GPIO_IDX	12	/* WIFI Chip Side */

/*
 * Debug Related Config
 */

#घोषणा DBG	0	/*  क्रम ODM & BTCOEX debug */

/* define DBG_XMIT_BUF */
/* define DBG_XMIT_BUF_EXT */
