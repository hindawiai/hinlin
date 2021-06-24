<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2014 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WLCORE_VENDOR_H__
#घोषणा __WLCORE_VENDOR_H__

#अगर_घोषित __KERNEL__
व्योम wlcore_set_venकरोr_commands(काष्ठा wiphy *wiphy);
#पूर्ण_अगर

#घोषणा TI_OUI	0x080028

क्रमागत wlcore_venकरोr_commands अणु
	WLCORE_VENDOR_CMD_SMART_CONFIG_START,
	WLCORE_VENDOR_CMD_SMART_CONFIG_STOP,
	WLCORE_VENDOR_CMD_SMART_CONFIG_SET_GROUP_KEY,

	NUM_WLCORE_VENDOR_CMD,
	MAX_WLCORE_VENDOR_CMD = NUM_WLCORE_VENDOR_CMD - 1
पूर्ण;

क्रमागत wlcore_venकरोr_attributes अणु
	WLCORE_VENDOR_ATTR_FREQ,
	WLCORE_VENDOR_ATTR_PSK,
	WLCORE_VENDOR_ATTR_SSID,
	WLCORE_VENDOR_ATTR_GROUP_ID,
	WLCORE_VENDOR_ATTR_GROUP_KEY,

	NUM_WLCORE_VENDOR_ATTR,
	MAX_WLCORE_VENDOR_ATTR = NUM_WLCORE_VENDOR_ATTR - 1
पूर्ण;

क्रमागत wlcore_venकरोr_events अणु
	WLCORE_VENDOR_EVENT_SC_SYNC,
	WLCORE_VENDOR_EVENT_SC_DECODE,
पूर्ण;

#पूर्ण_अगर /* __WLCORE_VENDOR_H__ */
