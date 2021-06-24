<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2011 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <coelho@ti.com>
 */

#अगर_अघोषित __DEBUG_H__
#घोषणा __DEBUG_H__

#समावेश <linux/bitops.h>
#समावेश <linux/prपूर्णांकk.h>

#घोषणा DRIVER_NAME "wlcore"
#घोषणा DRIVER_PREFIX DRIVER_NAME ": "

क्रमागत अणु
	DEBUG_NONE	= 0,
	DEBUG_IRQ	= BIT(0),
	DEBUG_SPI	= BIT(1),
	DEBUG_BOOT	= BIT(2),
	DEBUG_MAILBOX	= BIT(3),
	DEBUG_TESTMODE	= BIT(4),
	DEBUG_EVENT	= BIT(5),
	DEBUG_TX	= BIT(6),
	DEBUG_RX	= BIT(7),
	DEBUG_SCAN	= BIT(8),
	DEBUG_CRYPT	= BIT(9),
	DEBUG_PSM	= BIT(10),
	DEBUG_MAC80211	= BIT(11),
	DEBUG_CMD	= BIT(12),
	DEBUG_ACX	= BIT(13),
	DEBUG_SDIO	= BIT(14),
	DEBUG_FILTERS   = BIT(15),
	DEBUG_ADHOC     = BIT(16),
	DEBUG_AP	= BIT(17),
	DEBUG_PROBE	= BIT(18),
	DEBUG_IO	= BIT(19),
	DEBUG_MASTER	= (DEBUG_ADHOC | DEBUG_AP),
	DEBUG_ALL	= ~0,
पूर्ण;

बाह्य u32 wl12xx_debug_level;

#घोषणा DEBUG_DUMP_LIMIT 1024

#घोषणा wl1271_error(fmt, arg...) \
	pr_err(DRIVER_PREFIX "ERROR " fmt "\n", ##arg)

#घोषणा wl1271_warning(fmt, arg...) \
	pr_warn(DRIVER_PREFIX "WARNING " fmt "\n", ##arg)

#घोषणा wl1271_notice(fmt, arg...) \
	pr_info(DRIVER_PREFIX fmt "\n", ##arg)

#घोषणा wl1271_info(fmt, arg...) \
	pr_info(DRIVER_PREFIX fmt "\n", ##arg)

/* define the debug macro dअगरferently अगर dynamic debug is supported */
#अगर defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा wl1271_debug(level, fmt, arg...) \
	करो अणु \
		अगर (unlikely(level & wl12xx_debug_level)) \
			dynamic_pr_debug(DRIVER_PREFIX fmt "\n", ##arg); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा wl1271_debug(level, fmt, arg...) \
	करो अणु \
		अगर (unlikely(level & wl12xx_debug_level)) \
			prपूर्णांकk(KERN_DEBUG pr_fmt(DRIVER_PREFIX fmt "\n"), \
			       ##arg); \
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा wl1271_dump(level, prefix, buf, len)				      \
	करो अणु								      \
		अगर (level & wl12xx_debug_level)				      \
			prपूर्णांक_hex_dump_debug(DRIVER_PREFIX prefix,	      \
					DUMP_PREFIX_OFFSET, 16, 1,	      \
					buf,				      \
					min_t(माप_प्रकार, len, DEBUG_DUMP_LIMIT), \
					0);				      \
	पूर्ण जबतक (0)

#घोषणा wl1271_dump_ascii(level, prefix, buf, len)			      \
	करो अणु								      \
		अगर (level & wl12xx_debug_level)				      \
			prपूर्णांक_hex_dump_debug(DRIVER_PREFIX prefix,	      \
					DUMP_PREFIX_OFFSET, 16, 1,	      \
					buf,				      \
					min_t(माप_प्रकार, len, DEBUG_DUMP_LIMIT), \
					true);				      \
	पूर्ण जबतक (0)

#पूर्ण_अगर /* __DEBUG_H__ */
