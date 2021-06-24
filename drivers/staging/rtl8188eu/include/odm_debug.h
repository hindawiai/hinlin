<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__ODM_DBG_H__
#घोषणा __ODM_DBG_H__

/*  */
/*	Define the debug levels */
/*  */
/*	1. DBG_TRACE and DBG_LOUD are used क्रम normal हालs. */
/*	They can help SW engineer to develop or trace states changed */
/*	and also help HW enginner to trace every operation to and from HW, */
/*	e.g IO, Tx, Rx. */
/*  */
/*	2. DBG_WARNNING and DBG_SERIOUS are used क्रम unusual or error हालs, */
/*	which help us to debug SW or HW. */

/*	Never used in a call to ODM_RT_TRACE()! */
#घोषणा ODM_DBG_OFF				1

/*	Fatal bug. */
/*	For example, Tx/Rx/IO locked up, OS hangs, memory access violation, */
/*	resource allocation failed, unexpected HW behavior, HW BUG and so on. */
#घोषणा ODM_DBG_SERIOUS				2

/*	Abnormal, rare, or unexpected हालs. */
/*	For example, IRP/Packet/OID canceled, device suprisely unहटाओd and so on. */
#घोषणा ODM_DBG_WARNING				3

/*	Normal हाल with useful inक्रमmation about current SW or HW state. */
/*	For example, Tx/Rx descriptor to fill, Tx/Rx descr. completed status, */
/*	SW protocol state change, dynamic mechanism state change and so on. */
/*  */
#घोषणा ODM_DBG_LOUD					4

/*	Normal हाल with detail execution flow or inक्रमmation. */
#घोषणा ODM_DBG_TRACE					5

/*  Define the tracing components */
/* BB Functions */
#घोषणा ODM_COMP_DIG					BIT(0)
#घोषणा ODM_COMP_RA_MASK				BIT(1)
#घोषणा ODM_COMP_DYNAMIC_TXPWR				BIT(2)
#घोषणा ODM_COMP_FA_CNT					BIT(3)
#घोषणा ODM_COMP_RSSI_MONITOR				BIT(4)
#घोषणा ODM_COMP_CCK_PD					BIT(5)
#घोषणा ODM_COMP_ANT_DIV				BIT(6)
#घोषणा ODM_COMP_PWR_SAVE				BIT(7)
#घोषणा ODM_COMP_PWR_TRA				BIT(8)
#घोषणा ODM_COMP_RATE_ADAPTIVE				BIT(9)
#घोषणा ODM_COMP_PATH_DIV				BIT(10)
#घोषणा ODM_COMP_PSD					BIT(11)
#घोषणा ODM_COMP_DYNAMIC_PRICCA				BIT(12)
#घोषणा ODM_COMP_RXHP					BIT(13)
/* MAC Functions */
#घोषणा ODM_COMP_EDCA_TURBO				BIT(16)
#घोषणा ODM_COMP_EARLY_MODE				BIT(17)
/* RF Functions */
#घोषणा ODM_COMP_TX_PWR_TRACK				BIT(24)
#घोषणा ODM_COMP_RX_GAIN_TRACK				BIT(25)
#घोषणा ODM_COMP_CALIBRATION				BIT(26)
/* Common Functions */
#घोषणा ODM_COMP_COMMON					BIT(30)
#घोषणा ODM_COMP_INIT					BIT(31)

/*------------------------Export Marco Definition---------------------------*/
#घोषणा RT_PRINTK(fmt, args...)				\
	pr_info("%s(): " fmt, __func__, ## args);

#अगर_अघोषित ASSERT
	#घोषणा ASSERT(expr)
#पूर्ण_अगर

#घोषणा ODM_RT_TRACE(pDM_Odm, comp, level, fmt)				\
	अगर (((comp) & pDM_Odm->DebugComponents) &&			\
	    (level <= pDM_Odm->DebugLevel)) अणु				\
		pr_info("[ODM-8188E] ");				\
		RT_PRINTK fmt;						\
	पूर्ण

#घोषणा ODM_RT_ASSERT(pDM_Odm, expr, fmt)				\
	अगर (!(expr)) अणु							\
		pr_info("Assertion failed! %s at ......\n", #expr);	\
		pr_info("      ......%s,%s,line=%d\n", __खाता__,	\
			__func__, __LINE__);				\
		RT_PRINTK fmt;						\
		ASSERT(false);						\
	पूर्ण

व्योम ODM_InitDebugSetting(काष्ठा odm_dm_काष्ठा *pDM_Odm);

#पूर्ण_अगर	/*  __ODM_DBG_H__ */
