<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nl802154.h
 *
 * Copyright (C) 2007, 2008 Siemens AG
 */

#समावेश <linux/kernel.h>
#समावेश <net/netlink.h>
#समावेश <linux/nl802154.h>

#घोषणा NLA_HW_ADDR NLA_U64

स्थिर काष्ठा nla_policy ieee802154_policy[IEEE802154_ATTR_MAX + 1] = अणु
	[IEEE802154_ATTR_DEV_NAME] = अणु .type = NLA_STRING, पूर्ण,
	[IEEE802154_ATTR_DEV_INDEX] = अणु .type = NLA_U32, पूर्ण,
	[IEEE802154_ATTR_PHY_NAME] = अणु .type = NLA_STRING, पूर्ण,

	[IEEE802154_ATTR_STATUS] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_SHORT_ADDR] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_HW_ADDR] = अणु .type = NLA_HW_ADDR, पूर्ण,
	[IEEE802154_ATTR_PAN_ID] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_CHANNEL] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_BCN_ORD] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_SF_ORD] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_PAN_COORD] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_BAT_EXT] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_COORD_REALIGN] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_PAGE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_DEV_TYPE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_COORD_SHORT_ADDR] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_COORD_HW_ADDR] = अणु .type = NLA_HW_ADDR, पूर्ण,
	[IEEE802154_ATTR_COORD_PAN_ID] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_SRC_SHORT_ADDR] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_SRC_HW_ADDR] = अणु .type = NLA_HW_ADDR, पूर्ण,
	[IEEE802154_ATTR_SRC_PAN_ID] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_DEST_SHORT_ADDR] = अणु .type = NLA_U16, पूर्ण,
	[IEEE802154_ATTR_DEST_HW_ADDR] = अणु .type = NLA_HW_ADDR, पूर्ण,
	[IEEE802154_ATTR_DEST_PAN_ID] = अणु .type = NLA_U16, पूर्ण,

	[IEEE802154_ATTR_CAPABILITY] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_REASON] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_SCAN_TYPE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_CHANNELS] = अणु .type = NLA_U32, पूर्ण,
	[IEEE802154_ATTR_DURATION] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_ED_LIST] = अणु .len = 27 पूर्ण,
	[IEEE802154_ATTR_CHANNEL_PAGE_LIST] = अणु .len = 32 * 4, पूर्ण,

	[IEEE802154_ATTR_TXPOWER] = अणु .type = NLA_S8, पूर्ण,
	[IEEE802154_ATTR_LBT_ENABLED] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_CCA_MODE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_CCA_ED_LEVEL] = अणु .type = NLA_S32, पूर्ण,
	[IEEE802154_ATTR_CSMA_RETRIES] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_CSMA_MIN_BE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_CSMA_MAX_BE] = अणु .type = NLA_U8, पूर्ण,

	[IEEE802154_ATTR_FRAME_RETRIES] = अणु .type = NLA_S8, पूर्ण,

	[IEEE802154_ATTR_LLSEC_ENABLED] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_SECLEVEL] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_MODE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT] = अणु .type = NLA_U32, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED] = अणु .type = NLA_HW_ADDR, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_ID] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_FRAME_COUNTER] = अणु .type = NLA_U32 पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_BYTES] = अणु .len = 16, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_USAGE_FRAME_TYPES] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_KEY_USAGE_COMMANDS] = अणु .len = 258 / 8 पूर्ण,
	[IEEE802154_ATTR_LLSEC_FRAME_TYPE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_CMD_FRAME_ID] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_SECLEVELS] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE] = अणु .type = NLA_U8, पूर्ण,
	[IEEE802154_ATTR_LLSEC_DEV_KEY_MODE] = अणु .type = NLA_U8, पूर्ण,
पूर्ण;
