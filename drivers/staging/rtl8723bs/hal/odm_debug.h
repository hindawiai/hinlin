<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __ODM_DBG_H__
#घोषणा __ODM_DBG_H__


/*  */
/* Define the debug levels */
/*  */
/* 1.	DBG_TRACE and DBG_LOUD are used क्रम normal हालs. */
/* So that, they can help SW engineer to developed or trace states changed */
/* and also help HW enginner to trace every operation to and from HW, */
/* e.g IO, Tx, Rx. */
/*  */
/* 2.	DBG_WARNNING and DBG_SERIOUS are used क्रम unusual or error हालs, */
/* which help us to debug SW or HW. */
/*  */
/*  */
/*  */
/* Never used in a call to ODM_RT_TRACE()! */
/*  */
#घोषणा ODM_DBG_OFF					1

/*  */
/* Fatal bug. */
/* For example, Tx/Rx/IO locked up, OS hangs, memory access violation, */
/* resource allocation failed, unexpected HW behavior, HW BUG and so on. */
/*  */
#घोषणा ODM_DBG_SERIOUS				2

/*  */
/* Abnormal, rare, or unexpected हालs. */
/* For example, */
/* IRP/Packet/OID canceled, */
/* device suprisely unहटाओd and so on. */
/*  */
#घोषणा ODM_DBG_WARNING				3

/*  */
/* Normal हाल with useful inक्रमmation about current SW or HW state. */
/* For example, Tx/Rx descriptor to fill, Tx/Rx descriptor completed status, */
/* SW protocol state change, dynamic mechanism state change and so on. */
/*  */
#घोषणा ODM_DBG_LOUD				4

/*  */
/* Normal हाल with detail execution flow or inक्रमmation. */
/*  */
#घोषणा ODM_DBG_TRACE				5

/*  */
/*  Define the tracing components */
/*  */
/*  */
/* BB Functions */
#घोषणा ODM_COMP_DIG				BIT0
#घोषणा ODM_COMP_RA_MASK			BIT1
#घोषणा ODM_COMP_DYNAMIC_TXPWR		BIT2
#घोषणा ODM_COMP_FA_CNT				BIT3
#घोषणा ODM_COMP_RSSI_MONITOR		BIT4
#घोषणा ODM_COMP_CCK_PD				BIT5
#घोषणा ODM_COMP_ANT_DIV			BIT6
#घोषणा ODM_COMP_PWR_SAVE			BIT7
#घोषणा ODM_COMP_PWR_TRAIN			BIT8
#घोषणा ODM_COMP_RATE_ADAPTIVE		BIT9
#घोषणा ODM_COMP_PATH_DIV			BIT10
#घोषणा ODM_COMP_PSD				BIT11
#घोषणा ODM_COMP_DYNAMIC_PRICCA		BIT12
#घोषणा ODM_COMP_RXHP				BIT13
#घोषणा ODM_COMP_MP					BIT14
#घोषणा ODM_COMP_CFO_TRACKING		BIT15
/* MAC Functions */
#घोषणा ODM_COMP_EDCA_TURBO			BIT16
#घोषणा ODM_COMP_EARLY_MODE			BIT17
/* RF Functions */
#घोषणा ODM_COMP_TX_PWR_TRACK		BIT24
#घोषणा ODM_COMP_RX_GAIN_TRACK		BIT25
#घोषणा ODM_COMP_CALIBRATION		BIT26
/* Common Functions */
#घोषणा ODM_COMP_COMMON				BIT30
#घोषणा ODM_COMP_INIT				BIT31

/*------------------------Export Marco Definition---------------------------*/
	#घोषणा DbgPrपूर्णांक prपूर्णांकk
	#घोषणा RT_PRINTK(fmt, args...)\
		DbgPrपूर्णांक("%s(): " fmt, __func__, ## args)
	#घोषणा RT_DISP(dbgtype, dbgflag, prपूर्णांकstr)

#अगर_अघोषित ASSERT
	#घोषणा ASSERT(expr)
#पूर्ण_अगर

#अगर DBG
#घोषणा ODM_RT_TRACE(pDM_Odm, comp, level, fmt)\
	करो अणु\
		अगर (\
			(comp & pDM_Odm->DebugComponents) &&\
			(level <= pDM_Odm->DebugLevel ||\
			 level == ODM_DBG_SERIOUS)\
		) अणु\
			RT_PRINTK fmt;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा ODM_RT_TRACE_F(pDM_Odm, comp, level, fmt)\
	करो अणु\
		अगर (\
			(comp & pDM_Odm->DebugComponents) &&\
			(level <= pDM_Odm->DebugLevel)\
		) अणु\
			RT_PRINTK fmt;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा ODM_RT_ASSERT(pDM_Odm, expr, fmt)\
	करो अणु\
		अगर (!expr) अणु\
			DbgPrपूर्णांक("Assertion failed! %s at ......\n", #expr);\
			DbgPrपूर्णांक(\
				"      ......%s,%s, line =%d\n",\
				__खाता__,\
				__func__,\
				__LINE__\
			);\
			RT_PRINTK fmt;\
			ASSERT(false);\
		पूर्ण \
	पूर्ण जबतक (0)
#घोषणा ODM_dbg_trace(str) अणु DbgPrपूर्णांक("%s:%s\n", __func__, str); पूर्ण

#घोषणा ODM_PRINT_ADDR(pDM_Odm, comp, level, title_str, ptr)\
	करो अणु\
		अगर (\
			(comp & pDM_Odm->DebugComponents) &&\
			(level <= pDM_Odm->DebugLevel)\
		) अणु\
			पूर्णांक __i;\
			u8 *__ptr = (u8 *)ptr;\
			DbgPrपूर्णांक("[ODM] ");\
			DbgPrपूर्णांक(title_str);\
			DbgPrपूर्णांक(" ");\
			क्रम (__i = 0; __i < 6; __i++)\
				DbgPrपूर्णांक("%02X%s", __ptr[__i], (__i == 5) ? "" : "-");\
			DbgPrपूर्णांक("\n");\
		पूर्ण \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा ODM_RT_TRACE(pDM_Odm, comp, level, fmt)		no_prपूर्णांकk fmt
#घोषणा ODM_RT_TRACE_F(pDM_Odm, comp, level, fmt)	no_prपूर्णांकk fmt
#घोषणा ODM_RT_ASSERT(pDM_Odm, expr, fmt)		no_prपूर्णांकk fmt
#घोषणा ODM_dbg_enter()					करो अणुपूर्ण जबतक (0)
#घोषणा ODM_dbg_निकास()					करो अणुपूर्ण जबतक (0)
#घोषणा ODM_dbg_trace(str)				no_prपूर्णांकk("%s", str)
#घोषणा ODM_PRINT_ADDR(pDM_Odm, comp, level, title_str, ptr) \
	no_prपूर्णांकk("%s %p", title_str, ptr)
#पूर्ण_अगर

व्योम ODM_InitDebugSetting(काष्ठा dm_odm_t *pDM_Odm);

#पूर्ण_अगर	/*  __ODM_DBG_H__ */
