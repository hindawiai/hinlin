<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _RTL_DEBUG_H
#घोषणा _RTL_DEBUG_H

/* Allow files to override DRV_NAME */
#अगर_अघोषित DRV_NAME
#घोषणा DRV_NAME "rtllib_92e"
#पूर्ण_अगर

बाह्य u32 rt_global_debug_component;

/* These are the defines क्रम rt_global_debug_component */
क्रमागत RTL_DEBUG अणु
	COMP_TRACE		= (1 << 0),
	COMP_DBG		= (1 << 1),
	COMP_INIT		= (1 << 2),
	COMP_RECV		= (1 << 3),
	COMP_POWER		= (1 << 6),
	COMP_SWBW		= (1 << 8),
	COMP_SEC		= (1 << 9),
	COMP_LPS		= (1 << 10),
	COMP_QOS		= (1 << 11),
	COMP_RATE		= (1 << 12),
	COMP_RXDESC		= (1 << 13),
	COMP_PHY		= (1 << 14),
	COMP_DIG		= (1 << 15),
	COMP_TXAGC		= (1 << 16),
	COMP_HALDM		= (1 << 17),
	COMP_POWER_TRACKING	= (1 << 18),
	COMP_CH			= (1 << 19),
	COMP_RF			= (1 << 20),
	COMP_FIRMWARE		= (1 << 21),
	COMP_RESET		= (1 << 23),
	COMP_CMDPKT		= (1 << 24),
	COMP_SCAN		= (1 << 25),
	COMP_PS			= (1 << 26),
	COMP_DOWN		= (1 << 27),
	COMP_INTR		= (1 << 28),
	COMP_ERR		= (1 << 31)
पूर्ण;

#घोषणा RT_TRACE(component, x, args...)		\
करो अणु			\
	अगर (rt_global_debug_component & component) \
		prपूर्णांकk(KERN_DEBUG DRV_NAME ":" x "\n", ##args);\
पूर्ण जबतक (0)

#पूर्ण_अगर
