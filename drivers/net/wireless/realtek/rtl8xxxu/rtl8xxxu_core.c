<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTL8XXXU mac80211 USB driver
 *
 * Copyright (c) 2014 - 2017 Jes Sorensen <Jes.Sorensen@gmail.com>
 *
 * Portions, notably calibration code:
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This driver was written as a replacement क्रम the venकरोr provided
 * rtl8723au driver. As the Realtek 8xxx chips are very similar in
 * their programming पूर्णांकerface, I have started adding support क्रम
 * additional 8xxx chips like the 8192cu, 8188cus, etc.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/wireless.h>
#समावेश <linux/firmware.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/mac80211.h>
#समावेश "rtl8xxxu.h"
#समावेश "rtl8xxxu_regs.h"

#घोषणा DRIVER_NAME "rtl8xxxu"

पूर्णांक rtl8xxxu_debug = RTL8XXXU_DEBUG_EFUSE;
अटल bool rtl8xxxu_ht40_2g;
अटल bool rtl8xxxu_dma_aggregation;
अटल पूर्णांक rtl8xxxu_dma_agg_समयout = -1;
अटल पूर्णांक rtl8xxxu_dma_agg_pages = -1;

MODULE_AUTHOR("Jes Sorensen <Jes.Sorensen@gmail.com>");
MODULE_DESCRIPTION("RTL8XXXu USB mac80211 Wireless LAN Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("rtlwifi/rtl8723aufw_A.bin");
MODULE_FIRMWARE("rtlwifi/rtl8723aufw_B.bin");
MODULE_FIRMWARE("rtlwifi/rtl8723aufw_B_NoBT.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_A.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_B.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_TMSC.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192eu_nic.bin");
MODULE_FIRMWARE("rtlwifi/rtl8723bu_nic.bin");
MODULE_FIRMWARE("rtlwifi/rtl8723bu_bt.bin");

module_param_named(debug, rtl8xxxu_debug, पूर्णांक, 0600);
MODULE_PARM_DESC(debug, "Set debug mask");
module_param_named(ht40_2g, rtl8xxxu_ht40_2g, bool, 0600);
MODULE_PARM_DESC(ht40_2g, "Enable HT40 support on the 2.4GHz band");
module_param_named(dma_aggregation, rtl8xxxu_dma_aggregation, bool, 0600);
MODULE_PARM_DESC(dma_aggregation, "Enable DMA packet aggregation");
module_param_named(dma_agg_समयout, rtl8xxxu_dma_agg_समयout, पूर्णांक, 0600);
MODULE_PARM_DESC(dma_agg_समयout, "Set DMA aggregation timeout (range 1-127)");
module_param_named(dma_agg_pages, rtl8xxxu_dma_agg_pages, पूर्णांक, 0600);
MODULE_PARM_DESC(dma_agg_pages, "Set DMA aggregation pages (range 1-127, 0 to disable)");

#घोषणा USB_VENDOR_ID_REALTEK		0x0bda
#घोषणा RTL8XXXU_RX_URBS		32
#घोषणा RTL8XXXU_RX_URB_PENDING_WATER	8
#घोषणा RTL8XXXU_TX_URBS		64
#घोषणा RTL8XXXU_TX_URB_LOW_WATER	25
#घोषणा RTL8XXXU_TX_URB_HIGH_WATER	32

अटल पूर्णांक rtl8xxxu_submit_rx_urb(काष्ठा rtl8xxxu_priv *priv,
				  काष्ठा rtl8xxxu_rx_urb *rx_urb);

अटल काष्ठा ieee80211_rate rtl8xxxu_rates[] = अणु
	अणु .bitrate = 10, .hw_value = DESC_RATE_1M, .flags = 0 पूर्ण,
	अणु .bitrate = 20, .hw_value = DESC_RATE_2M, .flags = 0 पूर्ण,
	अणु .bitrate = 55, .hw_value = DESC_RATE_5_5M, .flags = 0 पूर्ण,
	अणु .bitrate = 110, .hw_value = DESC_RATE_11M, .flags = 0 पूर्ण,
	अणु .bitrate = 60, .hw_value = DESC_RATE_6M, .flags = 0 पूर्ण,
	अणु .bitrate = 90, .hw_value = DESC_RATE_9M, .flags = 0 पूर्ण,
	अणु .bitrate = 120, .hw_value = DESC_RATE_12M, .flags = 0 पूर्ण,
	अणु .bitrate = 180, .hw_value = DESC_RATE_18M, .flags = 0 पूर्ण,
	अणु .bitrate = 240, .hw_value = DESC_RATE_24M, .flags = 0 पूर्ण,
	अणु .bitrate = 360, .hw_value = DESC_RATE_36M, .flags = 0 पूर्ण,
	अणु .bitrate = 480, .hw_value = DESC_RATE_48M, .flags = 0 पूर्ण,
	अणु .bitrate = 540, .hw_value = DESC_RATE_54M, .flags = 0 पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel rtl8xxxu_channels_2g[] = अणु
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2412,
	  .hw_value = 1, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2417,
	  .hw_value = 2, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2422,
	  .hw_value = 3, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2427,
	  .hw_value = 4, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2432,
	  .hw_value = 5, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2437,
	  .hw_value = 6, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2442,
	  .hw_value = 7, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2447,
	  .hw_value = 8, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2452,
	  .hw_value = 9, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2457,
	  .hw_value = 10, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2462,
	  .hw_value = 11, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2467,
	  .hw_value = 12, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2472,
	  .hw_value = 13, .max_घातer = 30 पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2484,
	  .hw_value = 14, .max_घातer = 30 पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_supported_band rtl8xxxu_supported_band = अणु
	.channels = rtl8xxxu_channels_2g,
	.n_channels = ARRAY_SIZE(rtl8xxxu_channels_2g),
	.bitrates = rtl8xxxu_rates,
	.n_bitrates = ARRAY_SIZE(rtl8xxxu_rates),
पूर्ण;

काष्ठा rtl8xxxu_reg8val rtl8xxxu_gen1_mac_init_table[] = अणु
	अणु0x420, 0x80पूर्ण, अणु0x423, 0x00पूर्ण, अणु0x430, 0x00पूर्ण, अणु0x431, 0x00पूर्ण,
	अणु0x432, 0x00पूर्ण, अणु0x433, 0x01पूर्ण, अणु0x434, 0x04पूर्ण, अणु0x435, 0x05पूर्ण,
	अणु0x436, 0x06पूर्ण, अणु0x437, 0x07पूर्ण, अणु0x438, 0x00पूर्ण, अणु0x439, 0x00पूर्ण,
	अणु0x43a, 0x00पूर्ण, अणु0x43b, 0x01पूर्ण, अणु0x43c, 0x04पूर्ण, अणु0x43d, 0x05पूर्ण,
	अणु0x43e, 0x06पूर्ण, अणु0x43f, 0x07पूर्ण, अणु0x440, 0x5dपूर्ण, अणु0x441, 0x01पूर्ण,
	अणु0x442, 0x00पूर्ण, अणु0x444, 0x15पूर्ण, अणु0x445, 0xf0पूर्ण, अणु0x446, 0x0fपूर्ण,
	अणु0x447, 0x00पूर्ण, अणु0x458, 0x41पूर्ण, अणु0x459, 0xa8पूर्ण, अणु0x45a, 0x72पूर्ण,
	अणु0x45b, 0xb9पूर्ण, अणु0x460, 0x66पूर्ण, अणु0x461, 0x66पूर्ण, अणु0x462, 0x08पूर्ण,
	अणु0x463, 0x03पूर्ण, अणु0x4c8, 0xffपूर्ण, अणु0x4c9, 0x08पूर्ण, अणु0x4cc, 0xffपूर्ण,
	अणु0x4cd, 0xffपूर्ण, अणु0x4ce, 0x01पूर्ण, अणु0x500, 0x26पूर्ण, अणु0x501, 0xa2पूर्ण,
	अणु0x502, 0x2fपूर्ण, अणु0x503, 0x00पूर्ण, अणु0x504, 0x28पूर्ण, अणु0x505, 0xa3पूर्ण,
	अणु0x506, 0x5eपूर्ण, अणु0x507, 0x00पूर्ण, अणु0x508, 0x2bपूर्ण, अणु0x509, 0xa4पूर्ण,
	अणु0x50a, 0x5eपूर्ण, अणु0x50b, 0x00पूर्ण, अणु0x50c, 0x4fपूर्ण, अणु0x50d, 0xa4पूर्ण,
	अणु0x50e, 0x00पूर्ण, अणु0x50f, 0x00पूर्ण, अणु0x512, 0x1cपूर्ण, अणु0x514, 0x0aपूर्ण,
	अणु0x515, 0x10पूर्ण, अणु0x516, 0x0aपूर्ण, अणु0x517, 0x10पूर्ण, अणु0x51a, 0x16पूर्ण,
	अणु0x524, 0x0fपूर्ण, अणु0x525, 0x4fपूर्ण, अणु0x546, 0x40पूर्ण, अणु0x547, 0x00पूर्ण,
	अणु0x550, 0x10पूर्ण, अणु0x551, 0x10पूर्ण, अणु0x559, 0x02पूर्ण, अणु0x55a, 0x02पूर्ण,
	अणु0x55d, 0xffपूर्ण, अणु0x605, 0x30पूर्ण, अणु0x608, 0x0eपूर्ण, अणु0x609, 0x2aपूर्ण,
	अणु0x652, 0x20पूर्ण, अणु0x63c, 0x0aपूर्ण, अणु0x63d, 0x0aपूर्ण, अणु0x63e, 0x0eपूर्ण,
	अणु0x63f, 0x0eपूर्ण, अणु0x66e, 0x05पूर्ण, अणु0x700, 0x21पूर्ण, अणु0x701, 0x43पूर्ण,
	अणु0x702, 0x65पूर्ण, अणु0x703, 0x87पूर्ण, अणु0x708, 0x21पूर्ण, अणु0x709, 0x43पूर्ण,
	अणु0x70a, 0x65पूर्ण, अणु0x70b, 0x87पूर्ण, अणु0xffff, 0xffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8723a_phy_1t_init_table[] = अणु
	अणु0x800, 0x80040000पूर्ण, अणु0x804, 0x00000003पूर्ण,
	अणु0x808, 0x0000fc00पूर्ण, अणु0x80c, 0x0000000aपूर्ण,
	अणु0x810, 0x10001331पूर्ण, अणु0x814, 0x020c3d10पूर्ण,
	अणु0x818, 0x02200385पूर्ण, अणु0x81c, 0x00000000पूर्ण,
	अणु0x820, 0x01000100पूर्ण, अणु0x824, 0x00390004पूर्ण,
	अणु0x828, 0x00000000पूर्ण, अणु0x82c, 0x00000000पूर्ण,
	अणु0x830, 0x00000000पूर्ण, अणु0x834, 0x00000000पूर्ण,
	अणु0x838, 0x00000000पूर्ण, अणु0x83c, 0x00000000पूर्ण,
	अणु0x840, 0x00010000पूर्ण, अणु0x844, 0x00000000पूर्ण,
	अणु0x848, 0x00000000पूर्ण, अणु0x84c, 0x00000000पूर्ण,
	अणु0x850, 0x00000000पूर्ण, अणु0x854, 0x00000000पूर्ण,
	अणु0x858, 0x569a569aपूर्ण, अणु0x85c, 0x001b25a4पूर्ण,
	अणु0x860, 0x66f60110पूर्ण, अणु0x864, 0x061f0130पूर्ण,
	अणु0x868, 0x00000000पूर्ण, अणु0x86c, 0x32323200पूर्ण,
	अणु0x870, 0x07000760पूर्ण, अणु0x874, 0x22004000पूर्ण,
	अणु0x878, 0x00000808पूर्ण, अणु0x87c, 0x00000000पूर्ण,
	अणु0x880, 0xc0083070पूर्ण, अणु0x884, 0x000004d5पूर्ण,
	अणु0x888, 0x00000000पूर्ण, अणु0x88c, 0xccc000c0पूर्ण,
	अणु0x890, 0x00000800पूर्ण, अणु0x894, 0xfffffffeपूर्ण,
	अणु0x898, 0x40302010पूर्ण, अणु0x89c, 0x00706050पूर्ण,
	अणु0x900, 0x00000000पूर्ण, अणु0x904, 0x00000023पूर्ण,
	अणु0x908, 0x00000000पूर्ण, अणु0x90c, 0x81121111पूर्ण,
	अणु0xa00, 0x00d047c8पूर्ण, अणु0xa04, 0x80ff000cपूर्ण,
	अणु0xa08, 0x8c838300पूर्ण, अणु0xa0c, 0x2e68120fपूर्ण,
	अणु0xa10, 0x9500bb78पूर्ण, अणु0xa14, 0x11144028पूर्ण,
	अणु0xa18, 0x00881117पूर्ण, अणु0xa1c, 0x89140f00पूर्ण,
	अणु0xa20, 0x1a1b0000पूर्ण, अणु0xa24, 0x090e1317पूर्ण,
	अणु0xa28, 0x00000204पूर्ण, अणु0xa2c, 0x00d30000पूर्ण,
	अणु0xa70, 0x101fbf00पूर्ण, अणु0xa74, 0x00000007पूर्ण,
	अणु0xa78, 0x00000900पूर्ण,
	अणु0xc00, 0x48071d40पूर्ण, अणु0xc04, 0x03a05611पूर्ण,
	अणु0xc08, 0x000000e4पूर्ण, अणु0xc0c, 0x6c6c6c6cपूर्ण,
	अणु0xc10, 0x08800000पूर्ण, अणु0xc14, 0x40000100पूर्ण,
	अणु0xc18, 0x08800000पूर्ण, अणु0xc1c, 0x40000100पूर्ण,
	अणु0xc20, 0x00000000पूर्ण, अणु0xc24, 0x00000000पूर्ण,
	अणु0xc28, 0x00000000पूर्ण, अणु0xc2c, 0x00000000पूर्ण,
	अणु0xc30, 0x69e9ac44पूर्ण, अणु0xc34, 0x469652afपूर्ण,
	अणु0xc38, 0x49795994पूर्ण, अणु0xc3c, 0x0a97971cपूर्ण,
	अणु0xc40, 0x1f7c403fपूर्ण, अणु0xc44, 0x000100b7पूर्ण,
	अणु0xc48, 0xec020107पूर्ण, अणु0xc4c, 0x007f037fपूर्ण,
	अणु0xc50, 0x69543420पूर्ण, अणु0xc54, 0x43bc0094पूर्ण,
	अणु0xc58, 0x69543420पूर्ण, अणु0xc5c, 0x433c0094पूर्ण,
	अणु0xc60, 0x00000000पूर्ण, अणु0xc64, 0x7112848bपूर्ण,
	अणु0xc68, 0x47c00bffपूर्ण, अणु0xc6c, 0x00000036पूर्ण,
	अणु0xc70, 0x2c7f000dपूर्ण, अणु0xc74, 0x018610dbपूर्ण,
	अणु0xc78, 0x0000001fपूर्ण, अणु0xc7c, 0x00b91612पूर्ण,
	अणु0xc80, 0x40000100पूर्ण, अणु0xc84, 0x20f60000पूर्ण,
	अणु0xc88, 0x40000100पूर्ण, अणु0xc8c, 0x20200000पूर्ण,
	अणु0xc90, 0x00121820पूर्ण, अणु0xc94, 0x00000000पूर्ण,
	अणु0xc98, 0x00121820पूर्ण, अणु0xc9c, 0x00007f7fपूर्ण,
	अणु0xca0, 0x00000000पूर्ण, अणु0xca4, 0x00000080पूर्ण,
	अणु0xca8, 0x00000000पूर्ण, अणु0xcac, 0x00000000पूर्ण,
	अणु0xcb0, 0x00000000पूर्ण, अणु0xcb4, 0x00000000पूर्ण,
	अणु0xcb8, 0x00000000पूर्ण, अणु0xcbc, 0x28000000पूर्ण,
	अणु0xcc0, 0x00000000पूर्ण, अणु0xcc4, 0x00000000पूर्ण,
	अणु0xcc8, 0x00000000पूर्ण, अणु0xccc, 0x00000000पूर्ण,
	अणु0xcd0, 0x00000000पूर्ण, अणु0xcd4, 0x00000000पूर्ण,
	अणु0xcd8, 0x64b22427पूर्ण, अणु0xcdc, 0x00766932पूर्ण,
	अणु0xce0, 0x00222222पूर्ण, अणु0xce4, 0x00000000पूर्ण,
	अणु0xce8, 0x37644302पूर्ण, अणु0xcec, 0x2f97d40cपूर्ण,
	अणु0xd00, 0x00080740पूर्ण, अणु0xd04, 0x00020401पूर्ण,
	अणु0xd08, 0x0000907fपूर्ण, अणु0xd0c, 0x20010201पूर्ण,
	अणु0xd10, 0xa0633333पूर्ण, अणु0xd14, 0x3333bc43पूर्ण,
	अणु0xd18, 0x7a8f5b6bपूर्ण, अणु0xd2c, 0xcc979975पूर्ण,
	अणु0xd30, 0x00000000पूर्ण, अणु0xd34, 0x80608000पूर्ण,
	अणु0xd38, 0x00000000पूर्ण, अणु0xd3c, 0x00027293पूर्ण,
	अणु0xd40, 0x00000000पूर्ण, अणु0xd44, 0x00000000पूर्ण,
	अणु0xd48, 0x00000000पूर्ण, अणु0xd4c, 0x00000000पूर्ण,
	अणु0xd50, 0x6437140aपूर्ण, अणु0xd54, 0x00000000पूर्ण,
	अणु0xd58, 0x00000000पूर्ण, अणु0xd5c, 0x30032064पूर्ण,
	अणु0xd60, 0x4653de68पूर्ण, अणु0xd64, 0x04518a3cपूर्ण,
	अणु0xd68, 0x00002101पूर्ण, अणु0xd6c, 0x2a201c16पूर्ण,
	अणु0xd70, 0x1812362eपूर्ण, अणु0xd74, 0x322c2220पूर्ण,
	अणु0xd78, 0x000e3c24पूर्ण, अणु0xe00, 0x2a2a2a2aपूर्ण,
	अणु0xe04, 0x2a2a2a2aपूर्ण, अणु0xe08, 0x03902a2aपूर्ण,
	अणु0xe10, 0x2a2a2a2aपूर्ण, अणु0xe14, 0x2a2a2a2aपूर्ण,
	अणु0xe18, 0x2a2a2a2aपूर्ण, अणु0xe1c, 0x2a2a2a2aपूर्ण,
	अणु0xe28, 0x00000000पूर्ण, अणु0xe30, 0x1000dc1fपूर्ण,
	अणु0xe34, 0x10008c1fपूर्ण, अणु0xe38, 0x02140102पूर्ण,
	अणु0xe3c, 0x681604c2पूर्ण, अणु0xe40, 0x01007c00पूर्ण,
	अणु0xe44, 0x01004800पूर्ण, अणु0xe48, 0xfb000000पूर्ण,
	अणु0xe4c, 0x000028d1पूर्ण, अणु0xe50, 0x1000dc1fपूर्ण,
	अणु0xe54, 0x10008c1fपूर्ण, अणु0xe58, 0x02140102पूर्ण,
	अणु0xe5c, 0x28160d05पूर्ण, अणु0xe60, 0x00000008पूर्ण,
	अणु0xe68, 0x001b25a4पूर्ण, अणु0xe6c, 0x631b25a0पूर्ण,
	अणु0xe70, 0x631b25a0पूर्ण, अणु0xe74, 0x081b25a0पूर्ण,
	अणु0xe78, 0x081b25a0पूर्ण, अणु0xe7c, 0x081b25a0पूर्ण,
	अणु0xe80, 0x081b25a0पूर्ण, अणु0xe84, 0x631b25a0पूर्ण,
	अणु0xe88, 0x081b25a0पूर्ण, अणु0xe8c, 0x631b25a0पूर्ण,
	अणु0xed0, 0x631b25a0पूर्ण, अणु0xed4, 0x631b25a0पूर्ण,
	अणु0xed8, 0x631b25a0पूर्ण, अणु0xedc, 0x001b25a0पूर्ण,
	अणु0xee0, 0x001b25a0पूर्ण, अणु0xeec, 0x6b1b25a0पूर्ण,
	अणु0xf14, 0x00000003पूर्ण, अणु0xf4c, 0x00000000पूर्ण,
	अणु0xf00, 0x00000300पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8192cu_phy_2t_init_table[] = अणु
	अणु0x024, 0x0011800fपूर्ण, अणु0x028, 0x00ffdb83पूर्ण,
	अणु0x800, 0x80040002पूर्ण, अणु0x804, 0x00000003पूर्ण,
	अणु0x808, 0x0000fc00पूर्ण, अणु0x80c, 0x0000000aपूर्ण,
	अणु0x810, 0x10000330पूर्ण, अणु0x814, 0x020c3d10पूर्ण,
	अणु0x818, 0x02200385पूर्ण, अणु0x81c, 0x00000000पूर्ण,
	अणु0x820, 0x01000100पूर्ण, अणु0x824, 0x00390004पूर्ण,
	अणु0x828, 0x01000100पूर्ण, अणु0x82c, 0x00390004पूर्ण,
	अणु0x830, 0x27272727पूर्ण, अणु0x834, 0x27272727पूर्ण,
	अणु0x838, 0x27272727पूर्ण, अणु0x83c, 0x27272727पूर्ण,
	अणु0x840, 0x00010000पूर्ण, अणु0x844, 0x00010000पूर्ण,
	अणु0x848, 0x27272727पूर्ण, अणु0x84c, 0x27272727पूर्ण,
	अणु0x850, 0x00000000पूर्ण, अणु0x854, 0x00000000पूर्ण,
	अणु0x858, 0x569a569aपूर्ण, अणु0x85c, 0x0c1b25a4पूर्ण,
	अणु0x860, 0x66e60230पूर्ण, अणु0x864, 0x061f0130पूर्ण,
	अणु0x868, 0x27272727पूर्ण, अणु0x86c, 0x2b2b2b27पूर्ण,
	अणु0x870, 0x07000700पूर्ण, अणु0x874, 0x22184000पूर्ण,
	अणु0x878, 0x08080808पूर्ण, अणु0x87c, 0x00000000पूर्ण,
	अणु0x880, 0xc0083070पूर्ण, अणु0x884, 0x000004d5पूर्ण,
	अणु0x888, 0x00000000पूर्ण, अणु0x88c, 0xcc0000c0पूर्ण,
	अणु0x890, 0x00000800पूर्ण, अणु0x894, 0xfffffffeपूर्ण,
	अणु0x898, 0x40302010पूर्ण, अणु0x89c, 0x00706050पूर्ण,
	अणु0x900, 0x00000000पूर्ण, अणु0x904, 0x00000023पूर्ण,
	अणु0x908, 0x00000000पूर्ण, अणु0x90c, 0x81121313पूर्ण,
	अणु0xa00, 0x00d047c8पूर्ण, अणु0xa04, 0x80ff000cपूर्ण,
	अणु0xa08, 0x8c838300पूर्ण, अणु0xa0c, 0x2e68120fपूर्ण,
	अणु0xa10, 0x9500bb78पूर्ण, अणु0xa14, 0x11144028पूर्ण,
	अणु0xa18, 0x00881117पूर्ण, अणु0xa1c, 0x89140f00पूर्ण,
	अणु0xa20, 0x1a1b0000पूर्ण, अणु0xa24, 0x090e1317पूर्ण,
	अणु0xa28, 0x00000204पूर्ण, अणु0xa2c, 0x00d30000पूर्ण,
	अणु0xa70, 0x101fbf00पूर्ण, अणु0xa74, 0x00000007पूर्ण,
	अणु0xc00, 0x48071d40पूर्ण, अणु0xc04, 0x03a05633पूर्ण,
	अणु0xc08, 0x000000e4पूर्ण, अणु0xc0c, 0x6c6c6c6cपूर्ण,
	अणु0xc10, 0x08800000पूर्ण, अणु0xc14, 0x40000100पूर्ण,
	अणु0xc18, 0x08800000पूर्ण, अणु0xc1c, 0x40000100पूर्ण,
	अणु0xc20, 0x00000000पूर्ण, अणु0xc24, 0x00000000पूर्ण,
	अणु0xc28, 0x00000000पूर्ण, अणु0xc2c, 0x00000000पूर्ण,
	अणु0xc30, 0x69e9ac44पूर्ण, अणु0xc34, 0x469652cfपूर्ण,
	अणु0xc38, 0x49795994पूर्ण, अणु0xc3c, 0x0a97971cपूर्ण,
	अणु0xc40, 0x1f7c403fपूर्ण, अणु0xc44, 0x000100b7पूर्ण,
	अणु0xc48, 0xec020107पूर्ण, अणु0xc4c, 0x007f037fपूर्ण,
	अणु0xc50, 0x69543420पूर्ण, अणु0xc54, 0x43bc0094पूर्ण,
	अणु0xc58, 0x69543420पूर्ण, अणु0xc5c, 0x433c0094पूर्ण,
	अणु0xc60, 0x00000000पूर्ण, अणु0xc64, 0x5116848bपूर्ण,
	अणु0xc68, 0x47c00bffपूर्ण, अणु0xc6c, 0x00000036पूर्ण,
	अणु0xc70, 0x2c7f000dपूर्ण, अणु0xc74, 0x2186115bपूर्ण,
	अणु0xc78, 0x0000001fपूर्ण, अणु0xc7c, 0x00b99612पूर्ण,
	अणु0xc80, 0x40000100पूर्ण, अणु0xc84, 0x20f60000पूर्ण,
	अणु0xc88, 0x40000100पूर्ण, अणु0xc8c, 0xa0e40000पूर्ण,
	अणु0xc90, 0x00121820पूर्ण, अणु0xc94, 0x00000000पूर्ण,
	अणु0xc98, 0x00121820पूर्ण, अणु0xc9c, 0x00007f7fपूर्ण,
	अणु0xca0, 0x00000000पूर्ण, अणु0xca4, 0x00000080पूर्ण,
	अणु0xca8, 0x00000000पूर्ण, अणु0xcac, 0x00000000पूर्ण,
	अणु0xcb0, 0x00000000पूर्ण, अणु0xcb4, 0x00000000पूर्ण,
	अणु0xcb8, 0x00000000पूर्ण, अणु0xcbc, 0x28000000पूर्ण,
	अणु0xcc0, 0x00000000पूर्ण, अणु0xcc4, 0x00000000पूर्ण,
	अणु0xcc8, 0x00000000पूर्ण, अणु0xccc, 0x00000000पूर्ण,
	अणु0xcd0, 0x00000000पूर्ण, अणु0xcd4, 0x00000000पूर्ण,
	अणु0xcd8, 0x64b22427पूर्ण, अणु0xcdc, 0x00766932पूर्ण,
	अणु0xce0, 0x00222222पूर्ण, अणु0xce4, 0x00000000पूर्ण,
	अणु0xce8, 0x37644302पूर्ण, अणु0xcec, 0x2f97d40cपूर्ण,
	अणु0xd00, 0x00080740पूर्ण, अणु0xd04, 0x00020403पूर्ण,
	अणु0xd08, 0x0000907fपूर्ण, अणु0xd0c, 0x20010201पूर्ण,
	अणु0xd10, 0xa0633333पूर्ण, अणु0xd14, 0x3333bc43पूर्ण,
	अणु0xd18, 0x7a8f5b6bपूर्ण, अणु0xd2c, 0xcc979975पूर्ण,
	अणु0xd30, 0x00000000पूर्ण, अणु0xd34, 0x80608000पूर्ण,
	अणु0xd38, 0x00000000पूर्ण, अणु0xd3c, 0x00027293पूर्ण,
	अणु0xd40, 0x00000000पूर्ण, अणु0xd44, 0x00000000पूर्ण,
	अणु0xd48, 0x00000000पूर्ण, अणु0xd4c, 0x00000000पूर्ण,
	अणु0xd50, 0x6437140aपूर्ण, अणु0xd54, 0x00000000पूर्ण,
	अणु0xd58, 0x00000000पूर्ण, अणु0xd5c, 0x30032064पूर्ण,
	अणु0xd60, 0x4653de68पूर्ण, अणु0xd64, 0x04518a3cपूर्ण,
	अणु0xd68, 0x00002101पूर्ण, अणु0xd6c, 0x2a201c16पूर्ण,
	अणु0xd70, 0x1812362eपूर्ण, अणु0xd74, 0x322c2220पूर्ण,
	अणु0xd78, 0x000e3c24पूर्ण, अणु0xe00, 0x2a2a2a2aपूर्ण,
	अणु0xe04, 0x2a2a2a2aपूर्ण, अणु0xe08, 0x03902a2aपूर्ण,
	अणु0xe10, 0x2a2a2a2aपूर्ण, अणु0xe14, 0x2a2a2a2aपूर्ण,
	अणु0xe18, 0x2a2a2a2aपूर्ण, अणु0xe1c, 0x2a2a2a2aपूर्ण,
	अणु0xe28, 0x00000000पूर्ण, अणु0xe30, 0x1000dc1fपूर्ण,
	अणु0xe34, 0x10008c1fपूर्ण, अणु0xe38, 0x02140102पूर्ण,
	अणु0xe3c, 0x681604c2पूर्ण, अणु0xe40, 0x01007c00पूर्ण,
	अणु0xe44, 0x01004800पूर्ण, अणु0xe48, 0xfb000000पूर्ण,
	अणु0xe4c, 0x000028d1पूर्ण, अणु0xe50, 0x1000dc1fपूर्ण,
	अणु0xe54, 0x10008c1fपूर्ण, अणु0xe58, 0x02140102पूर्ण,
	अणु0xe5c, 0x28160d05पूर्ण, अणु0xe60, 0x00000010पूर्ण,
	अणु0xe68, 0x001b25a4पूर्ण, अणु0xe6c, 0x63db25a4पूर्ण,
	अणु0xe70, 0x63db25a4पूर्ण, अणु0xe74, 0x0c1b25a4पूर्ण,
	अणु0xe78, 0x0c1b25a4पूर्ण, अणु0xe7c, 0x0c1b25a4पूर्ण,
	अणु0xe80, 0x0c1b25a4पूर्ण, अणु0xe84, 0x63db25a4पूर्ण,
	अणु0xe88, 0x0c1b25a4पूर्ण, अणु0xe8c, 0x63db25a4पूर्ण,
	अणु0xed0, 0x63db25a4पूर्ण, अणु0xed4, 0x63db25a4पूर्ण,
	अणु0xed8, 0x63db25a4पूर्ण, अणु0xedc, 0x001b25a4पूर्ण,
	अणु0xee0, 0x001b25a4पूर्ण, अणु0xeec, 0x6fdb25a4पूर्ण,
	अणु0xf14, 0x00000003पूर्ण, अणु0xf4c, 0x00000000पूर्ण,
	अणु0xf00, 0x00000300पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8188ru_phy_1t_highpa_table[] = अणु
	अणु0x024, 0x0011800fपूर्ण, अणु0x028, 0x00ffdb83पूर्ण,
	अणु0x040, 0x000c0004पूर्ण, अणु0x800, 0x80040000पूर्ण,
	अणु0x804, 0x00000001पूर्ण, अणु0x808, 0x0000fc00पूर्ण,
	अणु0x80c, 0x0000000aपूर्ण, अणु0x810, 0x10005388पूर्ण,
	अणु0x814, 0x020c3d10पूर्ण, अणु0x818, 0x02200385पूर्ण,
	अणु0x81c, 0x00000000पूर्ण, अणु0x820, 0x01000100पूर्ण,
	अणु0x824, 0x00390204पूर्ण, अणु0x828, 0x00000000पूर्ण,
	अणु0x82c, 0x00000000पूर्ण, अणु0x830, 0x00000000पूर्ण,
	अणु0x834, 0x00000000पूर्ण, अणु0x838, 0x00000000पूर्ण,
	अणु0x83c, 0x00000000पूर्ण, अणु0x840, 0x00010000पूर्ण,
	अणु0x844, 0x00000000पूर्ण, अणु0x848, 0x00000000पूर्ण,
	अणु0x84c, 0x00000000पूर्ण, अणु0x850, 0x00000000पूर्ण,
	अणु0x854, 0x00000000पूर्ण, अणु0x858, 0x569a569aपूर्ण,
	अणु0x85c, 0x001b25a4पूर्ण, अणु0x860, 0x66e60230पूर्ण,
	अणु0x864, 0x061f0130पूर्ण, अणु0x868, 0x00000000पूर्ण,
	अणु0x86c, 0x20202000पूर्ण, अणु0x870, 0x03000300पूर्ण,
	अणु0x874, 0x22004000पूर्ण, अणु0x878, 0x00000808पूर्ण,
	अणु0x87c, 0x00ffc3f1पूर्ण, अणु0x880, 0xc0083070पूर्ण,
	अणु0x884, 0x000004d5पूर्ण, अणु0x888, 0x00000000पूर्ण,
	अणु0x88c, 0xccc000c0पूर्ण, अणु0x890, 0x00000800पूर्ण,
	अणु0x894, 0xfffffffeपूर्ण, अणु0x898, 0x40302010पूर्ण,
	अणु0x89c, 0x00706050पूर्ण, अणु0x900, 0x00000000पूर्ण,
	अणु0x904, 0x00000023पूर्ण, अणु0x908, 0x00000000पूर्ण,
	अणु0x90c, 0x81121111पूर्ण, अणु0xa00, 0x00d047c8पूर्ण,
	अणु0xa04, 0x80ff000cपूर्ण, अणु0xa08, 0x8c838300पूर्ण,
	अणु0xa0c, 0x2e68120fपूर्ण, अणु0xa10, 0x9500bb78पूर्ण,
	अणु0xa14, 0x11144028पूर्ण, अणु0xa18, 0x00881117पूर्ण,
	अणु0xa1c, 0x89140f00पूर्ण, अणु0xa20, 0x15160000पूर्ण,
	अणु0xa24, 0x070b0f12पूर्ण, अणु0xa28, 0x00000104पूर्ण,
	अणु0xa2c, 0x00d30000पूर्ण, अणु0xa70, 0x101fbf00पूर्ण,
	अणु0xa74, 0x00000007पूर्ण, अणु0xc00, 0x48071d40पूर्ण,
	अणु0xc04, 0x03a05611पूर्ण, अणु0xc08, 0x000000e4पूर्ण,
	अणु0xc0c, 0x6c6c6c6cपूर्ण, अणु0xc10, 0x08800000पूर्ण,
	अणु0xc14, 0x40000100पूर्ण, अणु0xc18, 0x08800000पूर्ण,
	अणु0xc1c, 0x40000100पूर्ण, अणु0xc20, 0x00000000पूर्ण,
	अणु0xc24, 0x00000000पूर्ण, अणु0xc28, 0x00000000पूर्ण,
	अणु0xc2c, 0x00000000पूर्ण, अणु0xc30, 0x69e9ac44पूर्ण,
	अणु0xc34, 0x469652cfपूर्ण, अणु0xc38, 0x49795994पूर्ण,
	अणु0xc3c, 0x0a97971cपूर्ण, अणु0xc40, 0x1f7c403fपूर्ण,
	अणु0xc44, 0x000100b7पूर्ण, अणु0xc48, 0xec020107पूर्ण,
	अणु0xc4c, 0x007f037fपूर्ण, अणु0xc50, 0x6954342eपूर्ण,
	अणु0xc54, 0x43bc0094पूर्ण, अणु0xc58, 0x6954342fपूर्ण,
	अणु0xc5c, 0x433c0094पूर्ण, अणु0xc60, 0x00000000पूर्ण,
	अणु0xc64, 0x5116848bपूर्ण, अणु0xc68, 0x47c00bffपूर्ण,
	अणु0xc6c, 0x00000036पूर्ण, अणु0xc70, 0x2c46000dपूर्ण,
	अणु0xc74, 0x018610dbपूर्ण, अणु0xc78, 0x0000001fपूर्ण,
	अणु0xc7c, 0x00b91612पूर्ण, अणु0xc80, 0x24000090पूर्ण,
	अणु0xc84, 0x20f60000पूर्ण, अणु0xc88, 0x24000090पूर्ण,
	अणु0xc8c, 0x20200000पूर्ण, अणु0xc90, 0x00121820पूर्ण,
	अणु0xc94, 0x00000000पूर्ण, अणु0xc98, 0x00121820पूर्ण,
	अणु0xc9c, 0x00007f7fपूर्ण, अणु0xca0, 0x00000000पूर्ण,
	अणु0xca4, 0x00000080पूर्ण, अणु0xca8, 0x00000000पूर्ण,
	अणु0xcac, 0x00000000पूर्ण, अणु0xcb0, 0x00000000पूर्ण,
	अणु0xcb4, 0x00000000पूर्ण, अणु0xcb8, 0x00000000पूर्ण,
	अणु0xcbc, 0x28000000पूर्ण, अणु0xcc0, 0x00000000पूर्ण,
	अणु0xcc4, 0x00000000पूर्ण, अणु0xcc8, 0x00000000पूर्ण,
	अणु0xccc, 0x00000000पूर्ण, अणु0xcd0, 0x00000000पूर्ण,
	अणु0xcd4, 0x00000000पूर्ण, अणु0xcd8, 0x64b22427पूर्ण,
	अणु0xcdc, 0x00766932पूर्ण, अणु0xce0, 0x00222222पूर्ण,
	अणु0xce4, 0x00000000पूर्ण, अणु0xce8, 0x37644302पूर्ण,
	अणु0xcec, 0x2f97d40cपूर्ण, अणु0xd00, 0x00080740पूर्ण,
	अणु0xd04, 0x00020401पूर्ण, अणु0xd08, 0x0000907fपूर्ण,
	अणु0xd0c, 0x20010201पूर्ण, अणु0xd10, 0xa0633333पूर्ण,
	अणु0xd14, 0x3333bc43पूर्ण, अणु0xd18, 0x7a8f5b6bपूर्ण,
	अणु0xd2c, 0xcc979975पूर्ण, अणु0xd30, 0x00000000पूर्ण,
	अणु0xd34, 0x80608000पूर्ण, अणु0xd38, 0x00000000पूर्ण,
	अणु0xd3c, 0x00027293पूर्ण, अणु0xd40, 0x00000000पूर्ण,
	अणु0xd44, 0x00000000पूर्ण, अणु0xd48, 0x00000000पूर्ण,
	अणु0xd4c, 0x00000000पूर्ण, अणु0xd50, 0x6437140aपूर्ण,
	अणु0xd54, 0x00000000पूर्ण, अणु0xd58, 0x00000000पूर्ण,
	अणु0xd5c, 0x30032064पूर्ण, अणु0xd60, 0x4653de68पूर्ण,
	अणु0xd64, 0x04518a3cपूर्ण, अणु0xd68, 0x00002101पूर्ण,
	अणु0xd6c, 0x2a201c16पूर्ण, अणु0xd70, 0x1812362eपूर्ण,
	अणु0xd74, 0x322c2220पूर्ण, अणु0xd78, 0x000e3c24पूर्ण,
	अणु0xe00, 0x24242424पूर्ण, अणु0xe04, 0x24242424पूर्ण,
	अणु0xe08, 0x03902024पूर्ण, अणु0xe10, 0x24242424पूर्ण,
	अणु0xe14, 0x24242424पूर्ण, अणु0xe18, 0x24242424पूर्ण,
	अणु0xe1c, 0x24242424पूर्ण, अणु0xe28, 0x00000000पूर्ण,
	अणु0xe30, 0x1000dc1fपूर्ण, अणु0xe34, 0x10008c1fपूर्ण,
	अणु0xe38, 0x02140102पूर्ण, अणु0xe3c, 0x681604c2पूर्ण,
	अणु0xe40, 0x01007c00पूर्ण, अणु0xe44, 0x01004800पूर्ण,
	अणु0xe48, 0xfb000000पूर्ण, अणु0xe4c, 0x000028d1पूर्ण,
	अणु0xe50, 0x1000dc1fपूर्ण, अणु0xe54, 0x10008c1fपूर्ण,
	अणु0xe58, 0x02140102पूर्ण, अणु0xe5c, 0x28160d05पूर्ण,
	अणु0xe60, 0x00000008पूर्ण, अणु0xe68, 0x001b25a4पूर्ण,
	अणु0xe6c, 0x631b25a0पूर्ण, अणु0xe70, 0x631b25a0पूर्ण,
	अणु0xe74, 0x081b25a0पूर्ण, अणु0xe78, 0x081b25a0पूर्ण,
	अणु0xe7c, 0x081b25a0पूर्ण, अणु0xe80, 0x081b25a0पूर्ण,
	अणु0xe84, 0x631b25a0पूर्ण, अणु0xe88, 0x081b25a0पूर्ण,
	अणु0xe8c, 0x631b25a0पूर्ण, अणु0xed0, 0x631b25a0पूर्ण,
	अणु0xed4, 0x631b25a0पूर्ण, अणु0xed8, 0x631b25a0पूर्ण,
	अणु0xedc, 0x001b25a0पूर्ण, अणु0xee0, 0x001b25a0पूर्ण,
	अणु0xeec, 0x6b1b25a0पूर्ण, अणु0xee8, 0x31555448पूर्ण,
	अणु0xf14, 0x00000003पूर्ण, अणु0xf4c, 0x00000000पूर्ण,
	अणु0xf00, 0x00000300पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8xxx_agc_standard_table[] = अणु
	अणु0xc78, 0x7b000001पूर्ण, अणु0xc78, 0x7b010001पूर्ण,
	अणु0xc78, 0x7b020001पूर्ण, अणु0xc78, 0x7b030001पूर्ण,
	अणु0xc78, 0x7b040001पूर्ण, अणु0xc78, 0x7b050001पूर्ण,
	अणु0xc78, 0x7a060001पूर्ण, अणु0xc78, 0x79070001पूर्ण,
	अणु0xc78, 0x78080001पूर्ण, अणु0xc78, 0x77090001पूर्ण,
	अणु0xc78, 0x760a0001पूर्ण, अणु0xc78, 0x750b0001पूर्ण,
	अणु0xc78, 0x740c0001पूर्ण, अणु0xc78, 0x730d0001पूर्ण,
	अणु0xc78, 0x720e0001पूर्ण, अणु0xc78, 0x710f0001पूर्ण,
	अणु0xc78, 0x70100001पूर्ण, अणु0xc78, 0x6f110001पूर्ण,
	अणु0xc78, 0x6e120001पूर्ण, अणु0xc78, 0x6d130001पूर्ण,
	अणु0xc78, 0x6c140001पूर्ण, अणु0xc78, 0x6b150001पूर्ण,
	अणु0xc78, 0x6a160001पूर्ण, अणु0xc78, 0x69170001पूर्ण,
	अणु0xc78, 0x68180001पूर्ण, अणु0xc78, 0x67190001पूर्ण,
	अणु0xc78, 0x661a0001पूर्ण, अणु0xc78, 0x651b0001पूर्ण,
	अणु0xc78, 0x641c0001पूर्ण, अणु0xc78, 0x631d0001पूर्ण,
	अणु0xc78, 0x621e0001पूर्ण, अणु0xc78, 0x611f0001पूर्ण,
	अणु0xc78, 0x60200001पूर्ण, अणु0xc78, 0x49210001पूर्ण,
	अणु0xc78, 0x48220001पूर्ण, अणु0xc78, 0x47230001पूर्ण,
	अणु0xc78, 0x46240001पूर्ण, अणु0xc78, 0x45250001पूर्ण,
	अणु0xc78, 0x44260001पूर्ण, अणु0xc78, 0x43270001पूर्ण,
	अणु0xc78, 0x42280001पूर्ण, अणु0xc78, 0x41290001पूर्ण,
	अणु0xc78, 0x402a0001पूर्ण, अणु0xc78, 0x262b0001पूर्ण,
	अणु0xc78, 0x252c0001पूर्ण, अणु0xc78, 0x242d0001पूर्ण,
	अणु0xc78, 0x232e0001पूर्ण, अणु0xc78, 0x222f0001पूर्ण,
	अणु0xc78, 0x21300001पूर्ण, अणु0xc78, 0x20310001पूर्ण,
	अणु0xc78, 0x06320001पूर्ण, अणु0xc78, 0x05330001पूर्ण,
	अणु0xc78, 0x04340001पूर्ण, अणु0xc78, 0x03350001पूर्ण,
	अणु0xc78, 0x02360001पूर्ण, अणु0xc78, 0x01370001पूर्ण,
	अणु0xc78, 0x00380001पूर्ण, अणु0xc78, 0x00390001पूर्ण,
	अणु0xc78, 0x003a0001पूर्ण, अणु0xc78, 0x003b0001पूर्ण,
	अणु0xc78, 0x003c0001पूर्ण, अणु0xc78, 0x003d0001पूर्ण,
	अणु0xc78, 0x003e0001पूर्ण, अणु0xc78, 0x003f0001पूर्ण,
	अणु0xc78, 0x7b400001पूर्ण, अणु0xc78, 0x7b410001पूर्ण,
	अणु0xc78, 0x7b420001पूर्ण, अणु0xc78, 0x7b430001पूर्ण,
	अणु0xc78, 0x7b440001पूर्ण, अणु0xc78, 0x7b450001पूर्ण,
	अणु0xc78, 0x7a460001पूर्ण, अणु0xc78, 0x79470001पूर्ण,
	अणु0xc78, 0x78480001पूर्ण, अणु0xc78, 0x77490001पूर्ण,
	अणु0xc78, 0x764a0001पूर्ण, अणु0xc78, 0x754b0001पूर्ण,
	अणु0xc78, 0x744c0001पूर्ण, अणु0xc78, 0x734d0001पूर्ण,
	अणु0xc78, 0x724e0001पूर्ण, अणु0xc78, 0x714f0001पूर्ण,
	अणु0xc78, 0x70500001पूर्ण, अणु0xc78, 0x6f510001पूर्ण,
	अणु0xc78, 0x6e520001पूर्ण, अणु0xc78, 0x6d530001पूर्ण,
	अणु0xc78, 0x6c540001पूर्ण, अणु0xc78, 0x6b550001पूर्ण,
	अणु0xc78, 0x6a560001पूर्ण, अणु0xc78, 0x69570001पूर्ण,
	अणु0xc78, 0x68580001पूर्ण, अणु0xc78, 0x67590001पूर्ण,
	अणु0xc78, 0x665a0001पूर्ण, अणु0xc78, 0x655b0001पूर्ण,
	अणु0xc78, 0x645c0001पूर्ण, अणु0xc78, 0x635d0001पूर्ण,
	अणु0xc78, 0x625e0001पूर्ण, अणु0xc78, 0x615f0001पूर्ण,
	अणु0xc78, 0x60600001पूर्ण, अणु0xc78, 0x49610001पूर्ण,
	अणु0xc78, 0x48620001पूर्ण, अणु0xc78, 0x47630001पूर्ण,
	अणु0xc78, 0x46640001पूर्ण, अणु0xc78, 0x45650001पूर्ण,
	अणु0xc78, 0x44660001पूर्ण, अणु0xc78, 0x43670001पूर्ण,
	अणु0xc78, 0x42680001पूर्ण, अणु0xc78, 0x41690001पूर्ण,
	अणु0xc78, 0x406a0001पूर्ण, अणु0xc78, 0x266b0001पूर्ण,
	अणु0xc78, 0x256c0001पूर्ण, अणु0xc78, 0x246d0001पूर्ण,
	अणु0xc78, 0x236e0001पूर्ण, अणु0xc78, 0x226f0001पूर्ण,
	अणु0xc78, 0x21700001पूर्ण, अणु0xc78, 0x20710001पूर्ण,
	अणु0xc78, 0x06720001पूर्ण, अणु0xc78, 0x05730001पूर्ण,
	अणु0xc78, 0x04740001पूर्ण, अणु0xc78, 0x03750001पूर्ण,
	अणु0xc78, 0x02760001पूर्ण, अणु0xc78, 0x01770001पूर्ण,
	अणु0xc78, 0x00780001पूर्ण, अणु0xc78, 0x00790001पूर्ण,
	अणु0xc78, 0x007a0001पूर्ण, अणु0xc78, 0x007b0001पूर्ण,
	अणु0xc78, 0x007c0001पूर्ण, अणु0xc78, 0x007d0001पूर्ण,
	अणु0xc78, 0x007e0001पूर्ण, अणु0xc78, 0x007f0001पूर्ण,
	अणु0xc78, 0x3800001eपूर्ण, अणु0xc78, 0x3801001eपूर्ण,
	अणु0xc78, 0x3802001eपूर्ण, अणु0xc78, 0x3803001eपूर्ण,
	अणु0xc78, 0x3804001eपूर्ण, अणु0xc78, 0x3805001eपूर्ण,
	अणु0xc78, 0x3806001eपूर्ण, अणु0xc78, 0x3807001eपूर्ण,
	अणु0xc78, 0x3808001eपूर्ण, अणु0xc78, 0x3c09001eपूर्ण,
	अणु0xc78, 0x3e0a001eपूर्ण, अणु0xc78, 0x400b001eपूर्ण,
	अणु0xc78, 0x440c001eपूर्ण, अणु0xc78, 0x480d001eपूर्ण,
	अणु0xc78, 0x4c0e001eपूर्ण, अणु0xc78, 0x500f001eपूर्ण,
	अणु0xc78, 0x5210001eपूर्ण, अणु0xc78, 0x5611001eपूर्ण,
	अणु0xc78, 0x5a12001eपूर्ण, अणु0xc78, 0x5e13001eपूर्ण,
	अणु0xc78, 0x6014001eपूर्ण, अणु0xc78, 0x6015001eपूर्ण,
	अणु0xc78, 0x6016001eपूर्ण, अणु0xc78, 0x6217001eपूर्ण,
	अणु0xc78, 0x6218001eपूर्ण, अणु0xc78, 0x6219001eपूर्ण,
	अणु0xc78, 0x621a001eपूर्ण, अणु0xc78, 0x621b001eपूर्ण,
	अणु0xc78, 0x621c001eपूर्ण, अणु0xc78, 0x621d001eपूर्ण,
	अणु0xc78, 0x621e001eपूर्ण, अणु0xc78, 0x621f001eपूर्ण,
	अणु0xffff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8xxx_agc_highpa_table[] = अणु
	अणु0xc78, 0x7b000001पूर्ण, अणु0xc78, 0x7b010001पूर्ण,
	अणु0xc78, 0x7b020001पूर्ण, अणु0xc78, 0x7b030001पूर्ण,
	अणु0xc78, 0x7b040001पूर्ण, अणु0xc78, 0x7b050001पूर्ण,
	अणु0xc78, 0x7b060001पूर्ण, अणु0xc78, 0x7b070001पूर्ण,
	अणु0xc78, 0x7b080001पूर्ण, अणु0xc78, 0x7a090001पूर्ण,
	अणु0xc78, 0x790a0001पूर्ण, अणु0xc78, 0x780b0001पूर्ण,
	अणु0xc78, 0x770c0001पूर्ण, अणु0xc78, 0x760d0001पूर्ण,
	अणु0xc78, 0x750e0001पूर्ण, अणु0xc78, 0x740f0001पूर्ण,
	अणु0xc78, 0x73100001पूर्ण, अणु0xc78, 0x72110001पूर्ण,
	अणु0xc78, 0x71120001पूर्ण, अणु0xc78, 0x70130001पूर्ण,
	अणु0xc78, 0x6f140001पूर्ण, अणु0xc78, 0x6e150001पूर्ण,
	अणु0xc78, 0x6d160001पूर्ण, अणु0xc78, 0x6c170001पूर्ण,
	अणु0xc78, 0x6b180001पूर्ण, अणु0xc78, 0x6a190001पूर्ण,
	अणु0xc78, 0x691a0001पूर्ण, अणु0xc78, 0x681b0001पूर्ण,
	अणु0xc78, 0x671c0001पूर्ण, अणु0xc78, 0x661d0001पूर्ण,
	अणु0xc78, 0x651e0001पूर्ण, अणु0xc78, 0x641f0001पूर्ण,
	अणु0xc78, 0x63200001पूर्ण, अणु0xc78, 0x62210001पूर्ण,
	अणु0xc78, 0x61220001पूर्ण, अणु0xc78, 0x60230001पूर्ण,
	अणु0xc78, 0x46240001पूर्ण, अणु0xc78, 0x45250001पूर्ण,
	अणु0xc78, 0x44260001पूर्ण, अणु0xc78, 0x43270001पूर्ण,
	अणु0xc78, 0x42280001पूर्ण, अणु0xc78, 0x41290001पूर्ण,
	अणु0xc78, 0x402a0001पूर्ण, अणु0xc78, 0x262b0001पूर्ण,
	अणु0xc78, 0x252c0001पूर्ण, अणु0xc78, 0x242d0001पूर्ण,
	अणु0xc78, 0x232e0001पूर्ण, अणु0xc78, 0x222f0001पूर्ण,
	अणु0xc78, 0x21300001पूर्ण, अणु0xc78, 0x20310001पूर्ण,
	अणु0xc78, 0x06320001पूर्ण, अणु0xc78, 0x05330001पूर्ण,
	अणु0xc78, 0x04340001पूर्ण, अणु0xc78, 0x03350001पूर्ण,
	अणु0xc78, 0x02360001पूर्ण, अणु0xc78, 0x01370001पूर्ण,
	अणु0xc78, 0x00380001पूर्ण, अणु0xc78, 0x00390001पूर्ण,
	अणु0xc78, 0x003a0001पूर्ण, अणु0xc78, 0x003b0001पूर्ण,
	अणु0xc78, 0x003c0001पूर्ण, अणु0xc78, 0x003d0001पूर्ण,
	अणु0xc78, 0x003e0001पूर्ण, अणु0xc78, 0x003f0001पूर्ण,
	अणु0xc78, 0x7b400001पूर्ण, अणु0xc78, 0x7b410001पूर्ण,
	अणु0xc78, 0x7b420001पूर्ण, अणु0xc78, 0x7b430001पूर्ण,
	अणु0xc78, 0x7b440001पूर्ण, अणु0xc78, 0x7b450001पूर्ण,
	अणु0xc78, 0x7b460001पूर्ण, अणु0xc78, 0x7b470001पूर्ण,
	अणु0xc78, 0x7b480001पूर्ण, अणु0xc78, 0x7a490001पूर्ण,
	अणु0xc78, 0x794a0001पूर्ण, अणु0xc78, 0x784b0001पूर्ण,
	अणु0xc78, 0x774c0001पूर्ण, अणु0xc78, 0x764d0001पूर्ण,
	अणु0xc78, 0x754e0001पूर्ण, अणु0xc78, 0x744f0001पूर्ण,
	अणु0xc78, 0x73500001पूर्ण, अणु0xc78, 0x72510001पूर्ण,
	अणु0xc78, 0x71520001पूर्ण, अणु0xc78, 0x70530001पूर्ण,
	अणु0xc78, 0x6f540001पूर्ण, अणु0xc78, 0x6e550001पूर्ण,
	अणु0xc78, 0x6d560001पूर्ण, अणु0xc78, 0x6c570001पूर्ण,
	अणु0xc78, 0x6b580001पूर्ण, अणु0xc78, 0x6a590001पूर्ण,
	अणु0xc78, 0x695a0001पूर्ण, अणु0xc78, 0x685b0001पूर्ण,
	अणु0xc78, 0x675c0001पूर्ण, अणु0xc78, 0x665d0001पूर्ण,
	अणु0xc78, 0x655e0001पूर्ण, अणु0xc78, 0x645f0001पूर्ण,
	अणु0xc78, 0x63600001पूर्ण, अणु0xc78, 0x62610001पूर्ण,
	अणु0xc78, 0x61620001पूर्ण, अणु0xc78, 0x60630001पूर्ण,
	अणु0xc78, 0x46640001पूर्ण, अणु0xc78, 0x45650001पूर्ण,
	अणु0xc78, 0x44660001पूर्ण, अणु0xc78, 0x43670001पूर्ण,
	अणु0xc78, 0x42680001पूर्ण, अणु0xc78, 0x41690001पूर्ण,
	अणु0xc78, 0x406a0001पूर्ण, अणु0xc78, 0x266b0001पूर्ण,
	अणु0xc78, 0x256c0001पूर्ण, अणु0xc78, 0x246d0001पूर्ण,
	अणु0xc78, 0x236e0001पूर्ण, अणु0xc78, 0x226f0001पूर्ण,
	अणु0xc78, 0x21700001पूर्ण, अणु0xc78, 0x20710001पूर्ण,
	अणु0xc78, 0x06720001पूर्ण, अणु0xc78, 0x05730001पूर्ण,
	अणु0xc78, 0x04740001पूर्ण, अणु0xc78, 0x03750001पूर्ण,
	अणु0xc78, 0x02760001पूर्ण, अणु0xc78, 0x01770001पूर्ण,
	अणु0xc78, 0x00780001पूर्ण, अणु0xc78, 0x00790001पूर्ण,
	अणु0xc78, 0x007a0001पूर्ण, अणु0xc78, 0x007b0001पूर्ण,
	अणु0xc78, 0x007c0001पूर्ण, अणु0xc78, 0x007d0001पूर्ण,
	अणु0xc78, 0x007e0001पूर्ण, अणु0xc78, 0x007f0001पूर्ण,
	अणु0xc78, 0x3800001eपूर्ण, अणु0xc78, 0x3801001eपूर्ण,
	अणु0xc78, 0x3802001eपूर्ण, अणु0xc78, 0x3803001eपूर्ण,
	अणु0xc78, 0x3804001eपूर्ण, अणु0xc78, 0x3805001eपूर्ण,
	अणु0xc78, 0x3806001eपूर्ण, अणु0xc78, 0x3807001eपूर्ण,
	अणु0xc78, 0x3808001eपूर्ण, अणु0xc78, 0x3c09001eपूर्ण,
	अणु0xc78, 0x3e0a001eपूर्ण, अणु0xc78, 0x400b001eपूर्ण,
	अणु0xc78, 0x440c001eपूर्ण, अणु0xc78, 0x480d001eपूर्ण,
	अणु0xc78, 0x4c0e001eपूर्ण, अणु0xc78, 0x500f001eपूर्ण,
	अणु0xc78, 0x5210001eपूर्ण, अणु0xc78, 0x5611001eपूर्ण,
	अणु0xc78, 0x5a12001eपूर्ण, अणु0xc78, 0x5e13001eपूर्ण,
	अणु0xc78, 0x6014001eपूर्ण, अणु0xc78, 0x6015001eपूर्ण,
	अणु0xc78, 0x6016001eपूर्ण, अणु0xc78, 0x6217001eपूर्ण,
	अणु0xc78, 0x6218001eपूर्ण, अणु0xc78, 0x6219001eपूर्ण,
	अणु0xc78, 0x621a001eपूर्ण, अणु0xc78, 0x621b001eपूर्ण,
	अणु0xc78, 0x621c001eपूर्ण, अणु0xc78, 0x621d001eपूर्ण,
	अणु0xc78, 0x621e001eपूर्ण, अणु0xc78, 0x621f001eपूर्ण,
	अणु0xffff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregs rtl8xxxu_rfregs[] = अणु
	अणु	/* RF_A */
		.hssiparm1 = REG_FPGA0_XA_HSSI_PARM1,
		.hssiparm2 = REG_FPGA0_XA_HSSI_PARM2,
		.lssiparm = REG_FPGA0_XA_LSSI_PARM,
		.hspiपढ़ो = REG_HSPI_XA_READBACK,
		.lssiपढ़ो = REG_FPGA0_XA_LSSI_READBACK,
		.rf_sw_ctrl = REG_FPGA0_XA_RF_SW_CTRL,
	पूर्ण,
	अणु	/* RF_B */
		.hssiparm1 = REG_FPGA0_XB_HSSI_PARM1,
		.hssiparm2 = REG_FPGA0_XB_HSSI_PARM2,
		.lssiparm = REG_FPGA0_XB_LSSI_PARM,
		.hspiपढ़ो = REG_HSPI_XB_READBACK,
		.lssiपढ़ो = REG_FPGA0_XB_LSSI_READBACK,
		.rf_sw_ctrl = REG_FPGA0_XB_RF_SW_CTRL,
	पूर्ण,
पूर्ण;

स्थिर u32 rtl8xxxu_iqk_phy_iq_bb_reg[RTL8XXXU_BB_REGS] = अणु
	REG_OFDM0_XA_RX_IQ_IMBALANCE,
	REG_OFDM0_XB_RX_IQ_IMBALANCE,
	REG_OFDM0_ENERGY_CCA_THRES,
	REG_OFDM0_AGCR_SSI_TABLE,
	REG_OFDM0_XA_TX_IQ_IMBALANCE,
	REG_OFDM0_XB_TX_IQ_IMBALANCE,
	REG_OFDM0_XC_TX_AFE,
	REG_OFDM0_XD_TX_AFE,
	REG_OFDM0_RX_IQ_EXT_ANTA
पूर्ण;

u8 rtl8xxxu_पढ़ो8(काष्ठा rtl8xxxu_priv *priv, u16 addr)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक len;
	u8 data;

	mutex_lock(&priv->usb_buf_mutex);
	len = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_READ,
			      addr, 0, &priv->usb_buf.val8, माप(u8),
			      RTW_USB_CONTROL_MSG_TIMEOUT);
	data = priv->usb_buf.val8;
	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_READ)
		dev_info(&udev->dev, "%s(%04x)   = 0x%02x, len %i\n",
			 __func__, addr, data, len);
	वापस data;
पूर्ण

u16 rtl8xxxu_पढ़ो16(काष्ठा rtl8xxxu_priv *priv, u16 addr)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक len;
	u16 data;

	mutex_lock(&priv->usb_buf_mutex);
	len = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_READ,
			      addr, 0, &priv->usb_buf.val16, माप(u16),
			      RTW_USB_CONTROL_MSG_TIMEOUT);
	data = le16_to_cpu(priv->usb_buf.val16);
	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_READ)
		dev_info(&udev->dev, "%s(%04x)  = 0x%04x, len %i\n",
			 __func__, addr, data, len);
	वापस data;
पूर्ण

u32 rtl8xxxu_पढ़ो32(काष्ठा rtl8xxxu_priv *priv, u16 addr)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक len;
	u32 data;

	mutex_lock(&priv->usb_buf_mutex);
	len = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_READ,
			      addr, 0, &priv->usb_buf.val32, माप(u32),
			      RTW_USB_CONTROL_MSG_TIMEOUT);
	data = le32_to_cpu(priv->usb_buf.val32);
	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_READ)
		dev_info(&udev->dev, "%s(%04x)  = 0x%08x, len %i\n",
			 __func__, addr, data, len);
	वापस data;
पूर्ण

पूर्णांक rtl8xxxu_ग_लिखो8(काष्ठा rtl8xxxu_priv *priv, u16 addr, u8 val)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक ret;

	mutex_lock(&priv->usb_buf_mutex);
	priv->usb_buf.val8 = val;
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_WRITE,
			      addr, 0, &priv->usb_buf.val8, माप(u8),
			      RTW_USB_CONTROL_MSG_TIMEOUT);

	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_WRITE)
		dev_info(&udev->dev, "%s(%04x) = 0x%02x\n",
			 __func__, addr, val);
	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_ग_लिखो16(काष्ठा rtl8xxxu_priv *priv, u16 addr, u16 val)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक ret;

	mutex_lock(&priv->usb_buf_mutex);
	priv->usb_buf.val16 = cpu_to_le16(val);
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_WRITE,
			      addr, 0, &priv->usb_buf.val16, माप(u16),
			      RTW_USB_CONTROL_MSG_TIMEOUT);
	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_WRITE)
		dev_info(&udev->dev, "%s(%04x) = 0x%04x\n",
			 __func__, addr, val);
	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_ग_लिखो32(काष्ठा rtl8xxxu_priv *priv, u16 addr, u32 val)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक ret;

	mutex_lock(&priv->usb_buf_mutex);
	priv->usb_buf.val32 = cpu_to_le32(val);
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      REALTEK_USB_CMD_REQ, REALTEK_USB_WRITE,
			      addr, 0, &priv->usb_buf.val32, माप(u32),
			      RTW_USB_CONTROL_MSG_TIMEOUT);
	mutex_unlock(&priv->usb_buf_mutex);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_REG_WRITE)
		dev_info(&udev->dev, "%s(%04x) = 0x%08x\n",
			 __func__, addr, val);
	वापस ret;
पूर्ण

अटल पूर्णांक
rtl8xxxu_ग_लिखोN(काष्ठा rtl8xxxu_priv *priv, u16 addr, u8 *buf, u16 len)
अणु
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक blocksize = priv->fops->ग_लिखोN_block_size;
	पूर्णांक ret, i, count, reमुख्यder;

	count = len / blocksize;
	reमुख्यder = len % blocksize;

	क्रम (i = 0; i < count; i++) अणु
		ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      REALTEK_USB_CMD_REQ, REALTEK_USB_WRITE,
				      addr, 0, buf, blocksize,
				      RTW_USB_CONTROL_MSG_TIMEOUT);
		अगर (ret != blocksize)
			जाओ ग_लिखो_error;

		addr += blocksize;
		buf += blocksize;
	पूर्ण

	अगर (reमुख्यder) अणु
		ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      REALTEK_USB_CMD_REQ, REALTEK_USB_WRITE,
				      addr, 0, buf, reमुख्यder,
				      RTW_USB_CONTROL_MSG_TIMEOUT);
		अगर (ret != reमुख्यder)
			जाओ ग_लिखो_error;
	पूर्ण

	वापस len;

ग_लिखो_error:
	dev_info(&udev->dev,
		 "%s: Failed to write block at addr: %04x size: %04x\n",
		 __func__, addr, blocksize);
	वापस -EAGAIN;
पूर्ण

u32 rtl8xxxu_पढ़ो_rfreg(काष्ठा rtl8xxxu_priv *priv,
			क्रमागत rtl8xxxu_rfpath path, u8 reg)
अणु
	u32 hssia, val32, retval;

	hssia = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XA_HSSI_PARM2);
	अगर (path != RF_A)
		val32 = rtl8xxxu_पढ़ो32(priv, rtl8xxxu_rfregs[path].hssiparm2);
	अन्यथा
		val32 = hssia;

	val32 &= ~FPGA0_HSSI_PARM2_ADDR_MASK;
	val32 |= (reg << FPGA0_HSSI_PARM2_ADDR_SHIFT);
	val32 |= FPGA0_HSSI_PARM2_EDGE_READ;
	hssia &= ~FPGA0_HSSI_PARM2_EDGE_READ;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_HSSI_PARM2, hssia);

	udelay(10);

	rtl8xxxu_ग_लिखो32(priv, rtl8xxxu_rfregs[path].hssiparm2, val32);
	udelay(100);

	hssia |= FPGA0_HSSI_PARM2_EDGE_READ;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_HSSI_PARM2, hssia);
	udelay(10);

	val32 = rtl8xxxu_पढ़ो32(priv, rtl8xxxu_rfregs[path].hssiparm1);
	अगर (val32 & FPGA0_HSSI_PARM1_PI)
		retval = rtl8xxxu_पढ़ो32(priv, rtl8xxxu_rfregs[path].hspiपढ़ो);
	अन्यथा
		retval = rtl8xxxu_पढ़ो32(priv, rtl8xxxu_rfregs[path].lssiपढ़ो);

	retval &= 0xfffff;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_RFREG_READ)
		dev_info(&priv->udev->dev, "%s(%02x) = 0x%06x\n",
			 __func__, reg, retval);
	वापस retval;
पूर्ण

/*
 * The RTL8723BU driver indicates that रेजिस्टरs 0xb2 and 0xb6 can
 * have ग_लिखो issues in high temperature conditions. We may have to
 * retry writing them.
 */
पूर्णांक rtl8xxxu_ग_लिखो_rfreg(काष्ठा rtl8xxxu_priv *priv,
			 क्रमागत rtl8xxxu_rfpath path, u8 reg, u32 data)
अणु
	पूर्णांक ret, retval;
	u32 dataaddr, val32;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_RFREG_WRITE)
		dev_info(&priv->udev->dev, "%s(%02x) = 0x%06x\n",
			 __func__, reg, data);

	data &= FPGA0_LSSI_PARM_DATA_MASK;
	dataaddr = (reg << FPGA0_LSSI_PARM_ADDR_SHIFT) | data;

	अगर (priv->rtl_chip == RTL8192E) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_POWER_SAVE);
		val32 &= ~0x20000;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_POWER_SAVE, val32);
	पूर्ण

	/* Use XB क्रम path B */
	ret = rtl8xxxu_ग_लिखो32(priv, rtl8xxxu_rfregs[path].lssiparm, dataaddr);
	अगर (ret != माप(dataaddr))
		retval = -EIO;
	अन्यथा
		retval = 0;

	udelay(1);

	अगर (priv->rtl_chip == RTL8192E) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_POWER_SAVE);
		val32 |= 0x20000;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_POWER_SAVE, val32);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक
rtl8xxxu_gen1_h2c_cmd(काष्ठा rtl8xxxu_priv *priv, काष्ठा h2c_cmd *h2c, पूर्णांक len)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक mbox_nr, retry, retval = 0;
	पूर्णांक mbox_reg, mbox_ext_reg;
	u8 val8;

	mutex_lock(&priv->h2c_mutex);

	mbox_nr = priv->next_mbox;
	mbox_reg = REG_HMBOX_0 + (mbox_nr * 4);
	mbox_ext_reg = REG_HMBOX_EXT_0 + (mbox_nr * 2);

	/*
	 * MBOX पढ़ोy?
	 */
	retry = 100;
	करो अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_HMTFR);
		अगर (!(val8 & BIT(mbox_nr)))
			अवरोध;
	पूर्ण जबतक (retry--);

	अगर (!retry) अणु
		dev_info(dev, "%s: Mailbox busy\n", __func__);
		retval = -EBUSY;
		जाओ error;
	पूर्ण

	/*
	 * Need to swap as it's being swapped again by rtl8xxxu_ग_लिखो16/32()
	 */
	अगर (len > माप(u32)) अणु
		rtl8xxxu_ग_लिखो16(priv, mbox_ext_reg, le16_to_cpu(h2c->raw.ext));
		अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_H2C)
			dev_info(dev, "H2C_EXT %04x\n",
				 le16_to_cpu(h2c->raw.ext));
	पूर्ण
	rtl8xxxu_ग_लिखो32(priv, mbox_reg, le32_to_cpu(h2c->raw.data));
	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_H2C)
		dev_info(dev, "H2C %08x\n", le32_to_cpu(h2c->raw.data));

	priv->next_mbox = (mbox_nr + 1) % H2C_MAX_MBOX;

error:
	mutex_unlock(&priv->h2c_mutex);
	वापस retval;
पूर्ण

पूर्णांक
rtl8xxxu_gen2_h2c_cmd(काष्ठा rtl8xxxu_priv *priv, काष्ठा h2c_cmd *h2c, पूर्णांक len)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक mbox_nr, retry, retval = 0;
	पूर्णांक mbox_reg, mbox_ext_reg;
	u8 val8;

	mutex_lock(&priv->h2c_mutex);

	mbox_nr = priv->next_mbox;
	mbox_reg = REG_HMBOX_0 + (mbox_nr * 4);
	mbox_ext_reg = REG_HMBOX_EXT0_8723B + (mbox_nr * 4);

	/*
	 * MBOX पढ़ोy?
	 */
	retry = 100;
	करो अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_HMTFR);
		अगर (!(val8 & BIT(mbox_nr)))
			अवरोध;
	पूर्ण जबतक (retry--);

	अगर (!retry) अणु
		dev_info(dev, "%s: Mailbox busy\n", __func__);
		retval = -EBUSY;
		जाओ error;
	पूर्ण

	/*
	 * Need to swap as it's being swapped again by rtl8xxxu_ग_लिखो16/32()
	 */
	अगर (len > माप(u32)) अणु
		rtl8xxxu_ग_लिखो32(priv, mbox_ext_reg,
				 le32_to_cpu(h2c->raw_wide.ext));
		अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_H2C)
			dev_info(dev, "H2C_EXT %08x\n",
				 le32_to_cpu(h2c->raw_wide.ext));
	पूर्ण
	rtl8xxxu_ग_लिखो32(priv, mbox_reg, le32_to_cpu(h2c->raw.data));
	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_H2C)
		dev_info(dev, "H2C %08x\n", le32_to_cpu(h2c->raw.data));

	priv->next_mbox = (mbox_nr + 1) % H2C_MAX_MBOX;

error:
	mutex_unlock(&priv->h2c_mutex);
	वापस retval;
पूर्ण

व्योम rtl8xxxu_gen1_enable_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_SPS0_CTRL);
	val8 |= BIT(0) | BIT(3);
	rtl8xxxu_ग_लिखो8(priv, REG_SPS0_CTRL, val8);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XAB_RF_PARM);
	val32 &= ~(BIT(4) | BIT(5));
	val32 |= BIT(3);
	अगर (priv->rf_paths == 2) अणु
		val32 &= ~(BIT(20) | BIT(21));
		val32 |= BIT(19);
	पूर्ण
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XAB_RF_PARM, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_TRX_PATH_ENABLE);
	val32 &= ~OFDM_RF_PATH_TX_MASK;
	अगर (priv->tx_paths == 2)
		val32 |= OFDM_RF_PATH_TX_A | OFDM_RF_PATH_TX_B;
	अन्यथा अगर (priv->rtl_chip == RTL8192C || priv->rtl_chip == RTL8191C)
		val32 |= OFDM_RF_PATH_TX_B;
	अन्यथा
		val32 |= OFDM_RF_PATH_TX_A;
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
	val32 &= ~FPGA_RF_MODE_JAPAN;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

	अगर (priv->rf_paths == 2)
		rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, 0x63db25a0);
	अन्यथा
		rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, 0x631b25a0);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC, 0x32d95);
	अगर (priv->rf_paths == 2)
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_AC, 0x32d95);

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0x00);
पूर्ण

व्योम rtl8xxxu_gen1_disable_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 sps0;
	u32 val32;

	sps0 = rtl8xxxu_पढ़ो8(priv, REG_SPS0_CTRL);

	/* RF RX code क्रम preamble घातer saving */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XAB_RF_PARM);
	val32 &= ~(BIT(3) | BIT(4) | BIT(5));
	अगर (priv->rf_paths == 2)
		val32 &= ~(BIT(19) | BIT(20) | BIT(21));
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XAB_RF_PARM, val32);

	/* Disable TX क्रम four paths */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_TRX_PATH_ENABLE);
	val32 &= ~OFDM_RF_PATH_TX_MASK;
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

	/* Enable घातer saving */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
	val32 |= FPGA_RF_MODE_JAPAN;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

	/* AFE control रेजिस्टर to घातer करोwn bits [30:22] */
	अगर (priv->rf_paths == 2)
		rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, 0x00db25a0);
	अन्यथा
		rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, 0x001b25a0);

	/* Power करोwn RF module */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC, 0);
	अगर (priv->rf_paths == 2)
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_AC, 0);

	sps0 &= ~(BIT(0) | BIT(3));
	rtl8xxxu_ग_लिखो8(priv, REG_SPS0_CTRL, sps0);
पूर्ण

अटल व्योम rtl8xxxu_stop_tx_beacon(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_FWHW_TXQ_CTRL + 2);
	val8 &= ~BIT(6);
	rtl8xxxu_ग_लिखो8(priv, REG_FWHW_TXQ_CTRL + 2, val8);

	rtl8xxxu_ग_लिखो8(priv, REG_TBTT_PROHIBIT + 1, 0x64);
	val8 = rtl8xxxu_पढ़ो8(priv, REG_TBTT_PROHIBIT + 2);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_TBTT_PROHIBIT + 2, val8);
पूर्ण


/*
 * The rtl8723a has 3 channel groups क्रम it's efuse settings. It only
 * supports the 2.4GHz band, so channels 1 - 14:
 *  group 0: channels 1 - 3
 *  group 1: channels 4 - 9
 *  group 2: channels 10 - 14
 *
 * Note: We index from 0 in the code
 */
अटल पूर्णांक rtl8xxxu_gen1_channel_to_group(पूर्णांक channel)
अणु
	पूर्णांक group;

	अगर (channel < 4)
		group = 0;
	अन्यथा अगर (channel < 10)
		group = 1;
	अन्यथा
		group = 2;

	वापस group;
पूर्ण

/*
 * Valid क्रम rtl8723bu and rtl8192eu
 */
पूर्णांक rtl8xxxu_gen2_channel_to_group(पूर्णांक channel)
अणु
	पूर्णांक group;

	अगर (channel < 3)
		group = 0;
	अन्यथा अगर (channel < 6)
		group = 1;
	अन्यथा अगर (channel < 9)
		group = 2;
	अन्यथा अगर (channel < 12)
		group = 3;
	अन्यथा
		group = 4;

	वापस group;
पूर्ण

व्योम rtl8xxxu_gen1_config_channel(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	u32 val32, rsr;
	u8 val8, opmode;
	bool ht = true;
	पूर्णांक sec_ch_above, channel;
	पूर्णांक i;

	opmode = rtl8xxxu_पढ़ो8(priv, REG_BW_OPMODE);
	rsr = rtl8xxxu_पढ़ो32(priv, REG_RESPONSE_RATE_SET);
	channel = hw->conf.chandef.chan->hw_value;

	चयन (hw->conf.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		ht = false;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20:
		opmode |= BW_OPMODE_20MHZ;
		rtl8xxxu_ग_लिखो8(priv, REG_BW_OPMODE, opmode);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
		val32 &= ~FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA1_RF_MODE);
		val32 &= ~FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA1_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_ANALOG2);
		val32 |= FPGA0_ANALOG2_20MHZ;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_ANALOG2, val32);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		अगर (hw->conf.chandef.center_freq1 >
		    hw->conf.chandef.chan->center_freq) अणु
			sec_ch_above = 1;
			channel += 2;
		पूर्ण अन्यथा अणु
			sec_ch_above = 0;
			channel -= 2;
		पूर्ण

		opmode &= ~BW_OPMODE_20MHZ;
		rtl8xxxu_ग_लिखो8(priv, REG_BW_OPMODE, opmode);
		rsr &= ~RSR_RSC_BANDWIDTH_40M;
		अगर (sec_ch_above)
			rsr |= RSR_RSC_UPPER_SUB_CHANNEL;
		अन्यथा
			rsr |= RSR_RSC_LOWER_SUB_CHANNEL;
		rtl8xxxu_ग_लिखो32(priv, REG_RESPONSE_RATE_SET, rsr);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
		val32 |= FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA1_RF_MODE);
		val32 |= FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA1_RF_MODE, val32);

		/*
		 * Set Control channel to upper or lower. These settings
		 * are required only क्रम 40MHz
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_CCK0_SYSTEM);
		val32 &= ~CCK0_SIDEBAND;
		अगर (!sec_ch_above)
			val32 |= CCK0_SIDEBAND;
		rtl8xxxu_ग_लिखो32(priv, REG_CCK0_SYSTEM, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM1_LSTF);
		val32 &= ~OFDM_LSTF_PRIME_CH_MASK; /* 0xc00 */
		अगर (sec_ch_above)
			val32 |= OFDM_LSTF_PRIME_CH_LOW;
		अन्यथा
			val32 |= OFDM_LSTF_PRIME_CH_HIGH;
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM1_LSTF, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_ANALOG2);
		val32 &= ~FPGA0_ANALOG2_20MHZ;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_ANALOG2, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_POWER_SAVE);
		val32 &= ~(FPGA0_PS_LOWER_CHANNEL | FPGA0_PS_UPPER_CHANNEL);
		अगर (sec_ch_above)
			val32 |= FPGA0_PS_UPPER_CHANNEL;
		अन्यथा
			val32 |= FPGA0_PS_LOWER_CHANNEL;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_POWER_SAVE, val32);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = RF_A; i < priv->rf_paths; i++) अणु
		val32 = rtl8xxxu_पढ़ो_rfreg(priv, i, RF6052_REG_MODE_AG);
		val32 &= ~MODE_AG_CHANNEL_MASK;
		val32 |= channel;
		rtl8xxxu_ग_लिखो_rfreg(priv, i, RF6052_REG_MODE_AG, val32);
	पूर्ण

	अगर (ht)
		val8 = 0x0e;
	अन्यथा
		val8 = 0x0a;

	rtl8xxxu_ग_लिखो8(priv, REG_SIFS_CCK + 1, val8);
	rtl8xxxu_ग_लिखो8(priv, REG_SIFS_OFDM + 1, val8);

	rtl8xxxu_ग_लिखो16(priv, REG_R2T_SIFS, 0x0808);
	rtl8xxxu_ग_लिखो16(priv, REG_T2T_SIFS, 0x0a0a);

	क्रम (i = RF_A; i < priv->rf_paths; i++) अणु
		val32 = rtl8xxxu_पढ़ो_rfreg(priv, i, RF6052_REG_MODE_AG);
		अगर (hw->conf.chandef.width == NL80211_CHAN_WIDTH_40)
			val32 &= ~MODE_AG_CHANNEL_20MHZ;
		अन्यथा
			val32 |= MODE_AG_CHANNEL_20MHZ;
		rtl8xxxu_ग_लिखो_rfreg(priv, i, RF6052_REG_MODE_AG, val32);
	पूर्ण
पूर्ण

व्योम rtl8xxxu_gen2_config_channel(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	u32 val32;
	u8 val8, subchannel;
	u16 rf_mode_bw;
	bool ht = true;
	पूर्णांक sec_ch_above, channel;
	पूर्णांक i;

	rf_mode_bw = rtl8xxxu_पढ़ो16(priv, REG_WMAC_TRXPTCL_CTL);
	rf_mode_bw &= ~WMAC_TRXPTCL_CTL_BW_MASK;
	channel = hw->conf.chandef.chan->hw_value;

/* Hack */
	subchannel = 0;

	चयन (hw->conf.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		ht = false;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20:
		rf_mode_bw |= WMAC_TRXPTCL_CTL_BW_20;
		subchannel = 0;

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
		val32 &= ~FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA1_RF_MODE);
		val32 &= ~FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA1_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_TX_PSDO_NOISE_WEIGHT);
		val32 &= ~(BIT(30) | BIT(31));
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TX_PSDO_NOISE_WEIGHT, val32);

		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		rf_mode_bw |= WMAC_TRXPTCL_CTL_BW_40;

		अगर (hw->conf.chandef.center_freq1 >
		    hw->conf.chandef.chan->center_freq) अणु
			sec_ch_above = 1;
			channel += 2;
		पूर्ण अन्यथा अणु
			sec_ch_above = 0;
			channel -= 2;
		पूर्ण

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
		val32 |= FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA1_RF_MODE);
		val32 |= FPGA_RF_MODE;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA1_RF_MODE, val32);

		/*
		 * Set Control channel to upper or lower. These settings
		 * are required only क्रम 40MHz
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_CCK0_SYSTEM);
		val32 &= ~CCK0_SIDEBAND;
		अगर (!sec_ch_above)
			val32 |= CCK0_SIDEBAND;
		rtl8xxxu_ग_लिखो32(priv, REG_CCK0_SYSTEM, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM1_LSTF);
		val32 &= ~OFDM_LSTF_PRIME_CH_MASK; /* 0xc00 */
		अगर (sec_ch_above)
			val32 |= OFDM_LSTF_PRIME_CH_LOW;
		अन्यथा
			val32 |= OFDM_LSTF_PRIME_CH_HIGH;
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM1_LSTF, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_POWER_SAVE);
		val32 &= ~(FPGA0_PS_LOWER_CHANNEL | FPGA0_PS_UPPER_CHANNEL);
		अगर (sec_ch_above)
			val32 |= FPGA0_PS_UPPER_CHANNEL;
		अन्यथा
			val32 |= FPGA0_PS_LOWER_CHANNEL;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_POWER_SAVE, val32);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		rf_mode_bw |= WMAC_TRXPTCL_CTL_BW_80;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = RF_A; i < priv->rf_paths; i++) अणु
		val32 = rtl8xxxu_पढ़ो_rfreg(priv, i, RF6052_REG_MODE_AG);
		val32 &= ~MODE_AG_CHANNEL_MASK;
		val32 |= channel;
		rtl8xxxu_ग_लिखो_rfreg(priv, i, RF6052_REG_MODE_AG, val32);
	पूर्ण

	rtl8xxxu_ग_लिखो16(priv, REG_WMAC_TRXPTCL_CTL, rf_mode_bw);
	rtl8xxxu_ग_लिखो8(priv, REG_DATA_SUBCHANNEL, subchannel);

	अगर (ht)
		val8 = 0x0e;
	अन्यथा
		val8 = 0x0a;

	rtl8xxxu_ग_लिखो8(priv, REG_SIFS_CCK + 1, val8);
	rtl8xxxu_ग_लिखो8(priv, REG_SIFS_OFDM + 1, val8);

	rtl8xxxu_ग_लिखो16(priv, REG_R2T_SIFS, 0x0808);
	rtl8xxxu_ग_लिखो16(priv, REG_T2T_SIFS, 0x0a0a);

	क्रम (i = RF_A; i < priv->rf_paths; i++) अणु
		val32 = rtl8xxxu_पढ़ो_rfreg(priv, i, RF6052_REG_MODE_AG);
		val32 &= ~MODE_AG_BW_MASK;
		चयन(hw->conf.chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_80:
			val32 |= MODE_AG_BW_80MHZ_8723B;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_40:
			val32 |= MODE_AG_BW_40MHZ_8723B;
			अवरोध;
		शेष:
			val32 |= MODE_AG_BW_20MHZ_8723B;
			अवरोध;
		पूर्ण
		rtl8xxxu_ग_लिखो_rfreg(priv, i, RF6052_REG_MODE_AG, val32);
	पूर्ण
पूर्ण

व्योम
rtl8xxxu_gen1_set_tx_घातer(काष्ठा rtl8xxxu_priv *priv, पूर्णांक channel, bool ht40)
अणु
	काष्ठा rtl8xxxu_घातer_base *घातer_base = priv->घातer_base;
	u8 cck[RTL8723A_MAX_RF_PATHS], ofdm[RTL8723A_MAX_RF_PATHS];
	u8 ofdmbase[RTL8723A_MAX_RF_PATHS], mcsbase[RTL8723A_MAX_RF_PATHS];
	u32 val32, ofdm_a, ofdm_b, mcs_a, mcs_b;
	u8 val8;
	पूर्णांक group, i;

	group = rtl8xxxu_gen1_channel_to_group(channel);

	cck[0] = priv->cck_tx_घातer_index_A[group] - 1;
	cck[1] = priv->cck_tx_घातer_index_B[group] - 1;

	अगर (priv->hi_pa) अणु
		अगर (cck[0] > 0x20)
			cck[0] = 0x20;
		अगर (cck[1] > 0x20)
			cck[1] = 0x20;
	पूर्ण

	ofdm[0] = priv->ht40_1s_tx_घातer_index_A[group];
	ofdm[1] = priv->ht40_1s_tx_घातer_index_B[group];
	अगर (ofdm[0])
		ofdm[0] -= 1;
	अगर (ofdm[1])
		ofdm[1] -= 1;

	ofdmbase[0] = ofdm[0] +	priv->ofdm_tx_घातer_index_dअगरf[group].a;
	ofdmbase[1] = ofdm[1] +	priv->ofdm_tx_घातer_index_dअगरf[group].b;

	mcsbase[0] = ofdm[0];
	mcsbase[1] = ofdm[1];
	अगर (!ht40) अणु
		mcsbase[0] += priv->ht20_tx_घातer_index_dअगरf[group].a;
		mcsbase[1] += priv->ht20_tx_घातer_index_dअगरf[group].b;
	पूर्ण

	अगर (priv->tx_paths > 1) अणु
		अगर (ofdm[0] > priv->ht40_2s_tx_घातer_index_dअगरf[group].a)
			ofdm[0] -=  priv->ht40_2s_tx_घातer_index_dअगरf[group].a;
		अगर (ofdm[1] > priv->ht40_2s_tx_घातer_index_dअगरf[group].b)
			ofdm[1] -=  priv->ht40_2s_tx_घातer_index_dअगरf[group].b;
	पूर्ण

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_CHANNEL)
		dev_info(&priv->udev->dev,
			 "%s: Setting TX power CCK A: %02x, "
			 "CCK B: %02x, OFDM A: %02x, OFDM B: %02x\n",
			 __func__, cck[0], cck[1], ofdm[0], ofdm[1]);

	क्रम (i = 0; i < RTL8723A_MAX_RF_PATHS; i++) अणु
		अगर (cck[i] > RF6052_MAX_TX_PWR)
			cck[i] = RF6052_MAX_TX_PWR;
		अगर (ofdm[i] > RF6052_MAX_TX_PWR)
			ofdm[i] = RF6052_MAX_TX_PWR;
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_A_CCK1_MCS32);
	val32 &= 0xffff00ff;
	val32 |= (cck[0] << 8);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_CCK1_MCS32, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
	val32 &= 0xff;
	val32 |= ((cck[0] << 8) | (cck[0] << 16) | (cck[0] << 24));
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
	val32 &= 0xffffff00;
	val32 |= cck[1];
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK1_55_MCS32);
	val32 &= 0xff;
	val32 |= ((cck[1] << 8) | (cck[1] << 16) | (cck[1] << 24));
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK1_55_MCS32, val32);

	ofdm_a = ofdmbase[0] | ofdmbase[0] << 8 |
		ofdmbase[0] << 16 | ofdmbase[0] << 24;
	ofdm_b = ofdmbase[1] | ofdmbase[1] << 8 |
		ofdmbase[1] << 16 | ofdmbase[1] << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE18_06,
			 ofdm_a + घातer_base->reg_0e00);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_RATE18_06,
			 ofdm_b + घातer_base->reg_0830);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE54_24,
			 ofdm_a + घातer_base->reg_0e04);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_RATE54_24,
			 ofdm_b + घातer_base->reg_0834);

	mcs_a = mcsbase[0] | mcsbase[0] << 8 |
		mcsbase[0] << 16 | mcsbase[0] << 24;
	mcs_b = mcsbase[1] | mcsbase[1] << 8 |
		mcsbase[1] << 16 | mcsbase[1] << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS03_MCS00,
			 mcs_a + घातer_base->reg_0e10);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS03_MCS00,
			 mcs_b + घातer_base->reg_083c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS07_MCS04,
			 mcs_a + घातer_base->reg_0e14);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS07_MCS04,
			 mcs_b + घातer_base->reg_0848);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS11_MCS08,
			 mcs_a + घातer_base->reg_0e18);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS11_MCS08,
			 mcs_b + घातer_base->reg_084c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS15_MCS12,
			 mcs_a + घातer_base->reg_0e1c);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i != 2)
			val8 = (mcsbase[0] > 8) ? (mcsbase[0] - 8) : 0;
		अन्यथा
			val8 = (mcsbase[0] > 6) ? (mcsbase[0] - 6) : 0;
		rtl8xxxu_ग_लिखो8(priv, REG_OFDM0_XC_TX_IQ_IMBALANCE + i, val8);
	पूर्ण
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS15_MCS12,
			 mcs_b + घातer_base->reg_0868);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i != 2)
			val8 = (mcsbase[1] > 8) ? (mcsbase[1] - 8) : 0;
		अन्यथा
			val8 = (mcsbase[1] > 6) ? (mcsbase[1] - 6) : 0;
		rtl8xxxu_ग_लिखो8(priv, REG_OFDM0_XD_TX_IQ_IMBALANCE + i, val8);
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_set_linktype(काष्ठा rtl8xxxu_priv *priv,
				  क्रमागत nl80211_अगरtype linktype)
अणु
	u8 val8;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_MSR);
	val8 &= ~MSR_LINKTYPE_MASK;

	चयन (linktype) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		val8 |= MSR_LINKTYPE_NONE;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		val8 |= MSR_LINKTYPE_ADHOC;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		val8 |= MSR_LINKTYPE_STATION;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		val8 |= MSR_LINKTYPE_AP;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	rtl8xxxu_ग_लिखो8(priv, REG_MSR, val8);
out:
	वापस;
पूर्ण

अटल व्योम
rtl8xxxu_set_retry(काष्ठा rtl8xxxu_priv *priv, u16 लघु_retry, u16 दीर्घ_retry)
अणु
	u16 val16;

	val16 = ((लघु_retry << RETRY_LIMIT_SHORT_SHIFT) &
		 RETRY_LIMIT_SHORT_MASK) |
		((दीर्घ_retry << RETRY_LIMIT_LONG_SHIFT) &
		 RETRY_LIMIT_LONG_MASK);

	rtl8xxxu_ग_लिखो16(priv, REG_RETRY_LIMIT, val16);
पूर्ण

अटल व्योम
rtl8xxxu_set_spec_sअगरs(काष्ठा rtl8xxxu_priv *priv, u16 cck, u16 ofdm)
अणु
	u16 val16;

	val16 = ((cck << SPEC_SIFS_CCK_SHIFT) & SPEC_SIFS_CCK_MASK) |
		((ofdm << SPEC_SIFS_OFDM_SHIFT) & SPEC_SIFS_OFDM_MASK);

	rtl8xxxu_ग_लिखो16(priv, REG_SPEC_SIFS, val16);
पूर्ण

अटल व्योम rtl8xxxu_prपूर्णांक_chipinfo(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	अक्षर *cut;

	चयन (priv->chip_cut) अणु
	हाल 0:
		cut = "A";
		अवरोध;
	हाल 1:
		cut = "B";
		अवरोध;
	हाल 2:
		cut = "C";
		अवरोध;
	हाल 3:
		cut = "D";
		अवरोध;
	हाल 4:
		cut = "E";
		अवरोध;
	शेष:
		cut = "unknown";
	पूर्ण

	dev_info(dev,
		 "RTL%s rev %s (%s) %iT%iR, TX queues %i, WiFi=%i, BT=%i, GPS=%i, HI PA=%i\n",
		 priv->chip_name, cut, priv->chip_venकरोr, priv->tx_paths,
		 priv->rx_paths, priv->ep_tx_count, priv->has_wअगरi,
		 priv->has_bluetooth, priv->has_gps, priv->hi_pa);

	dev_info(dev, "RTL%s MAC: %pM\n", priv->chip_name, priv->mac_addr);
पूर्ण

अटल पूर्णांक rtl8xxxu_identअगरy_chip(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	u32 val32, bonding;
	u16 val16;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_SYS_CFG);
	priv->chip_cut = (val32 & SYS_CFG_CHIP_VERSION_MASK) >>
		SYS_CFG_CHIP_VERSION_SHIFT;
	अगर (val32 & SYS_CFG_TRP_VAUX_EN) अणु
		dev_info(dev, "Unsupported test chip\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (val32 & SYS_CFG_BT_FUNC) अणु
		अगर (priv->chip_cut >= 3) अणु
			प्र_लिखो(priv->chip_name, "8723BU");
			priv->rtl_chip = RTL8723B;
		पूर्ण अन्यथा अणु
			प्र_लिखो(priv->chip_name, "8723AU");
			priv->usb_पूर्णांकerrupts = 1;
			priv->rtl_chip = RTL8723A;
		पूर्ण

		priv->rf_paths = 1;
		priv->rx_paths = 1;
		priv->tx_paths = 1;

		val32 = rtl8xxxu_पढ़ो32(priv, REG_MULTI_FUNC_CTRL);
		अगर (val32 & MULTI_WIFI_FUNC_EN)
			priv->has_wअगरi = 1;
		अगर (val32 & MULTI_BT_FUNC_EN)
			priv->has_bluetooth = 1;
		अगर (val32 & MULTI_GPS_FUNC_EN)
			priv->has_gps = 1;
		priv->is_multi_func = 1;
	पूर्ण अन्यथा अगर (val32 & SYS_CFG_TYPE_ID) अणु
		bonding = rtl8xxxu_पढ़ो32(priv, REG_HPON_FSM);
		bonding &= HPON_FSM_BONDING_MASK;
		अगर (priv->fops->tx_desc_size ==
		    माप(काष्ठा rtl8xxxu_txdesc40)) अणु
			अगर (bonding == HPON_FSM_BONDING_1T2R) अणु
				प्र_लिखो(priv->chip_name, "8191EU");
				priv->rf_paths = 2;
				priv->rx_paths = 2;
				priv->tx_paths = 1;
				priv->rtl_chip = RTL8191E;
			पूर्ण अन्यथा अणु
				प्र_लिखो(priv->chip_name, "8192EU");
				priv->rf_paths = 2;
				priv->rx_paths = 2;
				priv->tx_paths = 2;
				priv->rtl_chip = RTL8192E;
			पूर्ण
		पूर्ण अन्यथा अगर (bonding == HPON_FSM_BONDING_1T2R) अणु
			प्र_लिखो(priv->chip_name, "8191CU");
			priv->rf_paths = 2;
			priv->rx_paths = 2;
			priv->tx_paths = 1;
			priv->usb_पूर्णांकerrupts = 1;
			priv->rtl_chip = RTL8191C;
		पूर्ण अन्यथा अणु
			प्र_लिखो(priv->chip_name, "8192CU");
			priv->rf_paths = 2;
			priv->rx_paths = 2;
			priv->tx_paths = 2;
			priv->usb_पूर्णांकerrupts = 1;
			priv->rtl_chip = RTL8192C;
		पूर्ण
		priv->has_wअगरi = 1;
	पूर्ण अन्यथा अणु
		प्र_लिखो(priv->chip_name, "8188CU");
		priv->rf_paths = 1;
		priv->rx_paths = 1;
		priv->tx_paths = 1;
		priv->rtl_chip = RTL8188C;
		priv->usb_पूर्णांकerrupts = 1;
		priv->has_wअगरi = 1;
	पूर्ण

	चयन (priv->rtl_chip) अणु
	हाल RTL8188E:
	हाल RTL8192E:
	हाल RTL8723B:
		चयन (val32 & SYS_CFG_VENDOR_EXT_MASK) अणु
		हाल SYS_CFG_VENDOR_ID_TSMC:
			प्र_लिखो(priv->chip_venकरोr, "TSMC");
			अवरोध;
		हाल SYS_CFG_VENDOR_ID_SMIC:
			प्र_लिखो(priv->chip_venकरोr, "SMIC");
			priv->venकरोr_smic = 1;
			अवरोध;
		हाल SYS_CFG_VENDOR_ID_UMC:
			प्र_लिखो(priv->chip_venकरोr, "UMC");
			priv->venकरोr_umc = 1;
			अवरोध;
		शेष:
			प्र_लिखो(priv->chip_venकरोr, "unknown");
		पूर्ण
		अवरोध;
	शेष:
		अगर (val32 & SYS_CFG_VENDOR_ID) अणु
			प्र_लिखो(priv->chip_venकरोr, "UMC");
			priv->venकरोr_umc = 1;
		पूर्ण अन्यथा अणु
			प्र_लिखो(priv->chip_venकरोr, "TSMC");
		पूर्ण
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_GPIO_OUTSTS);
	priv->rom_rev = (val32 & GPIO_RF_RL_ID) >> 28;

	val16 = rtl8xxxu_पढ़ो16(priv, REG_NORMAL_SIE_EP_TX);
	अगर (val16 & NORMAL_SIE_EP_TX_HIGH_MASK) अणु
		priv->ep_tx_high_queue = 1;
		priv->ep_tx_count++;
	पूर्ण

	अगर (val16 & NORMAL_SIE_EP_TX_NORMAL_MASK) अणु
		priv->ep_tx_normal_queue = 1;
		priv->ep_tx_count++;
	पूर्ण

	अगर (val16 & NORMAL_SIE_EP_TX_LOW_MASK) अणु
		priv->ep_tx_low_queue = 1;
		priv->ep_tx_count++;
	पूर्ण

	/*
	 * Fallback क्रम devices that करो not provide REG_NORMAL_SIE_EP_TX
	 */
	अगर (!priv->ep_tx_count) अणु
		चयन (priv->nr_out_eps) अणु
		हाल 4:
		हाल 3:
			priv->ep_tx_low_queue = 1;
			priv->ep_tx_count++;
			fallthrough;
		हाल 2:
			priv->ep_tx_normal_queue = 1;
			priv->ep_tx_count++;
			fallthrough;
		हाल 1:
			priv->ep_tx_high_queue = 1;
			priv->ep_tx_count++;
			अवरोध;
		शेष:
			dev_info(dev, "Unsupported USB TX end-points\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
rtl8xxxu_पढ़ो_efuse8(काष्ठा rtl8xxxu_priv *priv, u16 offset, u8 *data)
अणु
	पूर्णांक i;
	u8 val8;
	u32 val32;

	/* Write Address */
	rtl8xxxu_ग_लिखो8(priv, REG_EFUSE_CTRL + 1, offset & 0xff);
	val8 = rtl8xxxu_पढ़ो8(priv, REG_EFUSE_CTRL + 2);
	val8 &= 0xfc;
	val8 |= (offset >> 8) & 0x03;
	rtl8xxxu_ग_लिखो8(priv, REG_EFUSE_CTRL + 2, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_EFUSE_CTRL + 3);
	rtl8xxxu_ग_लिखो8(priv, REG_EFUSE_CTRL + 3, val8 & 0x7f);

	/* Poll क्रम data पढ़ो */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_EFUSE_CTRL);
	क्रम (i = 0; i < RTL8XXXU_MAX_REG_POLL; i++) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_EFUSE_CTRL);
		अगर (val32 & BIT(31))
			अवरोध;
	पूर्ण

	अगर (i == RTL8XXXU_MAX_REG_POLL)
		वापस -EIO;

	udelay(50);
	val32 = rtl8xxxu_पढ़ो32(priv, REG_EFUSE_CTRL);

	*data = val32 & 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8xxxu_पढ़ो_efuse(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक i, ret = 0;
	u8 val8, word_mask, header, extheader;
	u16 val16, efuse_addr, offset;
	u32 val32;

	val16 = rtl8xxxu_पढ़ो16(priv, REG_9346CR);
	अगर (val16 & EEPROM_ENABLE)
		priv->has_eeprom = 1;
	अगर (val16 & EEPROM_BOOT)
		priv->boot_eeprom = 1;

	अगर (priv->is_multi_func) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_EFUSE_TEST);
		val32 = (val32 & ~EFUSE_SELECT_MASK) | EFUSE_WIFI_SELECT;
		rtl8xxxu_ग_लिखो32(priv, REG_EFUSE_TEST, val32);
	पूर्ण

	dev_dbg(dev, "Booting from %s\n",
		priv->boot_eeprom ? "EEPROM" : "EFUSE");

	rtl8xxxu_ग_लिखो8(priv, REG_EFUSE_ACCESS, EFUSE_ACCESS_ENABLE);

	/*  1.2V Power: From VDDON with Power Cut(0x0000[15]), शेष valid */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_ISO_CTRL);
	अगर (!(val16 & SYS_ISO_PWC_EV12V)) अणु
		val16 |= SYS_ISO_PWC_EV12V;
		rtl8xxxu_ग_लिखो16(priv, REG_SYS_ISO_CTRL, val16);
	पूर्ण
	/*  Reset: 0x0000[28], शेष valid */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	अगर (!(val16 & SYS_FUNC_ELDR)) अणु
		val16 |= SYS_FUNC_ELDR;
		rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);
	पूर्ण

	/*
	 * Clock: Gated(0x0008[5]) 8M(0x0008[1]) घड़ी from ANA, शेष valid
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_CLKR);
	अगर (!(val16 & SYS_CLK_LOADER_ENABLE) || !(val16 & SYS_CLK_ANA8M)) अणु
		val16 |= (SYS_CLK_LOADER_ENABLE | SYS_CLK_ANA8M);
		rtl8xxxu_ग_लिखो16(priv, REG_SYS_CLKR, val16);
	पूर्ण

	/* Default value is 0xff */
	स_रखो(priv->efuse_wअगरi.raw, 0xff, EFUSE_MAP_LEN);

	efuse_addr = 0;
	जबतक (efuse_addr < EFUSE_REAL_CONTENT_LEN_8723A) अणु
		u16 map_addr;

		ret = rtl8xxxu_पढ़ो_efuse8(priv, efuse_addr++, &header);
		अगर (ret || header == 0xff)
			जाओ निकास;

		अगर ((header & 0x1f) == 0x0f) अणु	/* extended header */
			offset = (header & 0xe0) >> 5;

			ret = rtl8xxxu_पढ़ो_efuse8(priv, efuse_addr++,
						   &extheader);
			अगर (ret)
				जाओ निकास;
			/* All words disabled */
			अगर ((extheader & 0x0f) == 0x0f)
				जारी;

			offset |= ((extheader & 0xf0) >> 1);
			word_mask = extheader & 0x0f;
		पूर्ण अन्यथा अणु
			offset = (header >> 4) & 0x0f;
			word_mask = header & 0x0f;
		पूर्ण

		/* Get word enable value from PG header */

		/* We have 8 bits to indicate validity */
		map_addr = offset * 8;
		अगर (map_addr >= EFUSE_MAP_LEN) अणु
			dev_warn(dev, "%s: Illegal map_addr (%04x), "
				 "efuse corrupt!\n",
				 __func__, map_addr);
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
		क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
			/* Check word enable condition in the section */
			अगर (word_mask & BIT(i)) अणु
				map_addr += 2;
				जारी;
			पूर्ण

			ret = rtl8xxxu_पढ़ो_efuse8(priv, efuse_addr++, &val8);
			अगर (ret)
				जाओ निकास;
			priv->efuse_wअगरi.raw[map_addr++] = val8;

			ret = rtl8xxxu_पढ़ो_efuse8(priv, efuse_addr++, &val8);
			अगर (ret)
				जाओ निकास;
			priv->efuse_wअगरi.raw[map_addr++] = val8;
		पूर्ण
	पूर्ण

निकास:
	rtl8xxxu_ग_लिखो8(priv, REG_EFUSE_ACCESS, EFUSE_ACCESS_DISABLE);

	वापस ret;
पूर्ण

व्योम rtl8xxxu_reset_8051(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 sys_func;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	sys_func = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	sys_func &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, sys_func);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	sys_func |= SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, sys_func);
पूर्ण

अटल पूर्णांक rtl8xxxu_start_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक ret = 0, i;
	u32 val32;

	/* Poll checksum report */
	क्रम (i = 0; i < RTL8XXXU_FIRMWARE_POLL_MAX; i++) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_MCU_FW_DL);
		अगर (val32 & MCU_FW_DL_CSUM_REPORT)
			अवरोध;
	पूर्ण

	अगर (i == RTL8XXXU_FIRMWARE_POLL_MAX) अणु
		dev_warn(dev, "Firmware checksum poll timed out\n");
		ret = -EAGAIN;
		जाओ निकास;
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_MCU_FW_DL);
	val32 |= MCU_FW_DL_READY;
	val32 &= ~MCU_WINT_INIT_READY;
	rtl8xxxu_ग_लिखो32(priv, REG_MCU_FW_DL, val32);

	/*
	 * Reset the 8051 in order क्रम the firmware to start running,
	 * otherwise it won't come up on the 8192eu
	 */
	priv->fops->reset_8051(priv);

	/* Wait क्रम firmware to become पढ़ोy */
	क्रम (i = 0; i < RTL8XXXU_FIRMWARE_POLL_MAX; i++) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_MCU_FW_DL);
		अगर (val32 & MCU_WINT_INIT_READY)
			अवरोध;

		udelay(100);
	पूर्ण

	अगर (i == RTL8XXXU_FIRMWARE_POLL_MAX) अणु
		dev_warn(dev, "Firmware failed to start\n");
		ret = -EAGAIN;
		जाओ निकास;
	पूर्ण

	/*
	 * Init H2C command
	 */
	अगर (priv->rtl_chip == RTL8723B)
		rtl8xxxu_ग_लिखो8(priv, REG_HMTFR, 0x0f);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8xxxu_करोwnload_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक pages, reमुख्यder, i, ret;
	u8 val8;
	u16 val16;
	u32 val32;
	u8 *fwptr;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_FUNC + 1);
	val8 |= 4;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC + 1, val8);

	/* 8051 enable */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL);
	अगर (val8 & MCU_FW_RAM_SEL) अणु
		pr_info("do the RAM reset\n");
		rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, 0x00);
		priv->fops->reset_8051(priv);
	पूर्ण

	/* MCU firmware करोwnload enable */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL);
	val8 |= MCU_FW_DL_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, val8);

	/* 8051 reset */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_MCU_FW_DL);
	val32 &= ~BIT(19);
	rtl8xxxu_ग_लिखो32(priv, REG_MCU_FW_DL, val32);

	/* Reset firmware करोwnload checksum */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL);
	val8 |= MCU_FW_DL_CSUM_REPORT;
	rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, val8);

	pages = priv->fw_size / RTL_FW_PAGE_SIZE;
	reमुख्यder = priv->fw_size % RTL_FW_PAGE_SIZE;

	fwptr = priv->fw_data->data;

	क्रम (i = 0; i < pages; i++) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL + 2) & 0xF8;
		val8 |= i;
		rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL + 2, val8);

		ret = rtl8xxxu_ग_लिखोN(priv, REG_FW_START_ADDRESS,
				      fwptr, RTL_FW_PAGE_SIZE);
		अगर (ret != RTL_FW_PAGE_SIZE) अणु
			ret = -EAGAIN;
			जाओ fw_पात;
		पूर्ण

		fwptr += RTL_FW_PAGE_SIZE;
	पूर्ण

	अगर (reमुख्यder) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL + 2) & 0xF8;
		val8 |= i;
		rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL + 2, val8);
		ret = rtl8xxxu_ग_लिखोN(priv, REG_FW_START_ADDRESS,
				      fwptr, reमुख्यder);
		अगर (ret != reमुख्यder) अणु
			ret = -EAGAIN;
			जाओ fw_पात;
		पूर्ण
	पूर्ण

	ret = 0;
fw_पात:
	/* MCU firmware करोwnload disable */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_MCU_FW_DL);
	val16 &= ~MCU_FW_DL_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_MCU_FW_DL, val16);

	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_load_firmware(काष्ठा rtl8xxxu_priv *priv, अक्षर *fw_name)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0;
	u16 signature;

	dev_info(dev, "%s: Loading firmware %s\n", DRIVER_NAME, fw_name);
	अगर (request_firmware(&fw, fw_name, &priv->udev->dev)) अणु
		dev_warn(dev, "request_firmware(%s) failed\n", fw_name);
		ret = -EAGAIN;
		जाओ निकास;
	पूर्ण
	अगर (!fw) अणु
		dev_warn(dev, "Firmware data not available\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	priv->fw_data = kmemdup(fw->data, fw->size, GFP_KERNEL);
	अगर (!priv->fw_data) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	priv->fw_size = fw->size - माप(काष्ठा rtl8xxxu_firmware_header);

	signature = le16_to_cpu(priv->fw_data->signature);
	चयन (signature & 0xfff0) अणु
	हाल 0x92e0:
	हाल 0x92c0:
	हाल 0x88c0:
	हाल 0x5300:
	हाल 0x2300:
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_warn(dev, "%s: Invalid firmware signature: 0x%04x\n",
			 __func__, signature);
	पूर्ण

	dev_info(dev, "Firmware revision %i.%i (signature 0x%04x)\n",
		 le16_to_cpu(priv->fw_data->major_version),
		 priv->fw_data->minor_version, signature);

निकास:
	release_firmware(fw);
	वापस ret;
पूर्ण

व्योम rtl8xxxu_firmware_self_reset(काष्ठा rtl8xxxu_priv *priv)
अणु
	u16 val16;
	पूर्णांक i = 100;

	/* Inक्रमm 8051 to perक्रमm reset */
	rtl8xxxu_ग_लिखो8(priv, REG_HMTFR + 3, 0x20);

	क्रम (i = 100; i > 0; i--) अणु
		val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);

		अगर (!(val16 & SYS_FUNC_CPU_ENABLE)) अणु
			dev_dbg(&priv->udev->dev,
				"%s: Firmware self reset success!\n", __func__);
			अवरोध;
		पूर्ण
		udelay(50);
	पूर्ण

	अगर (!i) अणु
		/* Force firmware reset */
		val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
		val16 &= ~SYS_FUNC_CPU_ENABLE;
		rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);
	पूर्ण
पूर्ण

अटल पूर्णांक
rtl8xxxu_init_mac(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_reg8val *array = priv->fops->mactable;
	पूर्णांक i, ret;
	u16 reg;
	u8 val;

	क्रम (i = 0; ; i++) अणु
		reg = array[i].reg;
		val = array[i].val;

		अगर (reg == 0xffff && val == 0xff)
			अवरोध;

		ret = rtl8xxxu_ग_लिखो8(priv, reg, val);
		अगर (ret != 1) अणु
			dev_warn(&priv->udev->dev,
				 "Failed to initialize MAC "
				 "(reg: %04x, val %02x)\n", reg, val);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (priv->rtl_chip != RTL8723B && priv->rtl_chip != RTL8192E)
		rtl8xxxu_ग_लिखो8(priv, REG_MAX_AGGR_NUM, 0x0a);

	वापस 0;
पूर्ण

पूर्णांक rtl8xxxu_init_phy_regs(काष्ठा rtl8xxxu_priv *priv,
			   काष्ठा rtl8xxxu_reg32val *array)
अणु
	पूर्णांक i, ret;
	u16 reg;
	u32 val;

	क्रम (i = 0; ; i++) अणु
		reg = array[i].reg;
		val = array[i].val;

		अगर (reg == 0xffff && val == 0xffffffff)
			अवरोध;

		ret = rtl8xxxu_ग_लिखो32(priv, reg, val);
		अगर (ret != माप(val)) अणु
			dev_warn(&priv->udev->dev,
				 "Failed to initialize PHY\n");
			वापस -EAGAIN;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rtl8xxxu_gen1_init_phy_bb(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8, lकरोa15, lकरोv12d, lplकरो, lकरोhci12;
	u16 val16;
	u32 val32;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_AFE_PLL_CTRL);
	udelay(2);
	val8 |= AFE_PLL_320_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_PLL_CTRL, val8);
	udelay(2);

	rtl8xxxu_ग_लिखो8(priv, REG_AFE_PLL_CTRL + 1, 0xff);
	udelay(2);

	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_AFE_XTAL_CTRL);
	val32 &= ~AFE_XTAL_RF_GATE;
	अगर (priv->has_bluetooth)
		val32 &= ~AFE_XTAL_BT_GATE;
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_XTAL_CTRL, val32);

	/* 6. 0x1f[7:0] = 0x07 */
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, val8);

	अगर (priv->hi_pa)
		rtl8xxxu_init_phy_regs(priv, rtl8188ru_phy_1t_highpa_table);
	अन्यथा अगर (priv->tx_paths == 2)
		rtl8xxxu_init_phy_regs(priv, rtl8192cu_phy_2t_init_table);
	अन्यथा
		rtl8xxxu_init_phy_regs(priv, rtl8723a_phy_1t_init_table);

	अगर (priv->rtl_chip == RTL8188R && priv->hi_pa &&
	    priv->venकरोr_umc && priv->chip_cut == 1)
		rtl8xxxu_ग_लिखो8(priv, REG_OFDM0_AGC_PARM1 + 2, 0x50);

	अगर (priv->hi_pa)
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_highpa_table);
	अन्यथा
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_standard_table);

	lकरोa15 = LDOA15_ENABLE | LDOA15_OBUF;
	lकरोv12d = LDOV12D_ENABLE | BIT(2) | (2 << LDOV12D_VADJ_SHIFT);
	lकरोhci12 = 0x57;
	lplकरो = 1;
	val32 = (lplकरो << 24) | (lकरोhci12 << 16) | (lकरोv12d << 8) | lकरोa15;
	rtl8xxxu_ग_लिखो32(priv, REG_LDOA15_CTRL, val32);
पूर्ण

/*
 * Most of this is black magic retrieved from the old rtl8723au driver
 */
अटल पूर्णांक rtl8xxxu_init_phy_bb(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;

	priv->fops->init_phy_bb(priv);

	अगर (priv->tx_paths == 1 && priv->rx_paths == 2) अणु
		/*
		 * For 1T2R boards, patch the रेजिस्टरs.
		 *
		 * It looks like 8191/2 1T2R boards use path B क्रम TX
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_TX_INFO);
		val32 &= ~(BIT(0) | BIT(1));
		val32 |= BIT(1);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_TX_INFO, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA1_TX_INFO);
		val32 &= ~0x300033;
		val32 |= 0x200022;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA1_TX_INFO, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_CCK0_AFE_SETTING);
		val32 &= ~CCK0_AFE_RX_MASK;
		val32 &= 0x00ffffff;
		val32 |= 0x40000000;
		val32 |= CCK0_AFE_RX_ANT_B;
		rtl8xxxu_ग_लिखो32(priv, REG_CCK0_AFE_SETTING, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_TRX_PATH_ENABLE);
		val32 &= ~(OFDM_RF_PATH_RX_MASK | OFDM_RF_PATH_TX_MASK);
		val32 |= (OFDM_RF_PATH_RX_A | OFDM_RF_PATH_RX_B |
			  OFDM_RF_PATH_TX_B);
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_AGC_PARM1);
		val32 &= ~(BIT(4) | BIT(5));
		val32 |= BIT(4);
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_AGC_PARM1, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_CCK_RFON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_CCK_RFON, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_CCK_BBON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_CCK_BBON, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_OFDM_RFON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_OFDM_RFON, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_OFDM_BBON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_OFDM_BBON, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_TO_TX);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_TO_TX, val32);
	पूर्ण

	अगर (priv->has_xtalk) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_MAC_PHY_CTRL);

		val8 = priv->xtalk;
		val32 &= 0xff000fff;
		val32 |= ((val8 | (val8 << 6)) << 12);

		rtl8xxxu_ग_लिखो32(priv, REG_MAC_PHY_CTRL, val32);
	पूर्ण

	अगर (priv->rtl_chip == RTL8192E)
		rtl8xxxu_ग_लिखो32(priv, REG_AFE_XTAL_CTRL, 0x000f81fb);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8xxxu_init_rf_regs(काष्ठा rtl8xxxu_priv *priv,
				 काष्ठा rtl8xxxu_rfregval *array,
				 क्रमागत rtl8xxxu_rfpath path)
अणु
	पूर्णांक i, ret;
	u8 reg;
	u32 val;

	क्रम (i = 0; ; i++) अणु
		reg = array[i].reg;
		val = array[i].val;

		अगर (reg == 0xff && val == 0xffffffff)
			अवरोध;

		चयन (reg) अणु
		हाल 0xfe:
			msleep(50);
			जारी;
		हाल 0xfd:
			mdelay(5);
			जारी;
		हाल 0xfc:
			mdelay(1);
			जारी;
		हाल 0xfb:
			udelay(50);
			जारी;
		हाल 0xfa:
			udelay(5);
			जारी;
		हाल 0xf9:
			udelay(1);
			जारी;
		पूर्ण

		ret = rtl8xxxu_ग_लिखो_rfreg(priv, path, reg, val);
		अगर (ret) अणु
			dev_warn(&priv->udev->dev,
				 "Failed to initialize RF\n");
			वापस -EAGAIN;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rtl8xxxu_init_phy_rf(काष्ठा rtl8xxxu_priv *priv,
			 काष्ठा rtl8xxxu_rfregval *table,
			 क्रमागत rtl8xxxu_rfpath path)
अणु
	u32 val32;
	u16 val16, rfsi_rfenv;
	u16 reg_sw_ctrl, reg_पूर्णांक_oe, reg_hssi_parm2;

	चयन (path) अणु
	हाल RF_A:
		reg_sw_ctrl = REG_FPGA0_XA_RF_SW_CTRL;
		reg_पूर्णांक_oe = REG_FPGA0_XA_RF_INT_OE;
		reg_hssi_parm2 = REG_FPGA0_XA_HSSI_PARM2;
		अवरोध;
	हाल RF_B:
		reg_sw_ctrl = REG_FPGA0_XB_RF_SW_CTRL;
		reg_पूर्णांक_oe = REG_FPGA0_XB_RF_INT_OE;
		reg_hssi_parm2 = REG_FPGA0_XB_HSSI_PARM2;
		अवरोध;
	शेष:
		dev_err(&priv->udev->dev, "%s:Unsupported RF path %c\n",
			__func__, path + 'A');
		वापस -EINVAL;
	पूर्ण
	/* For path B, use XB */
	rfsi_rfenv = rtl8xxxu_पढ़ो16(priv, reg_sw_ctrl);
	rfsi_rfenv &= FPGA0_RF_RFENV;

	/*
	 * These two we might be able to optimize पूर्णांकo one
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, reg_पूर्णांक_oe);
	val32 |= BIT(20);	/* 0x10 << 16 */
	rtl8xxxu_ग_लिखो32(priv, reg_पूर्णांक_oe, val32);
	udelay(1);

	val32 = rtl8xxxu_पढ़ो32(priv, reg_पूर्णांक_oe);
	val32 |= BIT(4);
	rtl8xxxu_ग_लिखो32(priv, reg_पूर्णांक_oe, val32);
	udelay(1);

	/*
	 * These two we might be able to optimize पूर्णांकo one
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, reg_hssi_parm2);
	val32 &= ~FPGA0_HSSI_3WIRE_ADDR_LEN;
	rtl8xxxu_ग_लिखो32(priv, reg_hssi_parm2, val32);
	udelay(1);

	val32 = rtl8xxxu_पढ़ो32(priv, reg_hssi_parm2);
	val32 &= ~FPGA0_HSSI_3WIRE_DATA_LEN;
	rtl8xxxu_ग_लिखो32(priv, reg_hssi_parm2, val32);
	udelay(1);

	rtl8xxxu_init_rf_regs(priv, table, path);

	/* For path B, use XB */
	val16 = rtl8xxxu_पढ़ो16(priv, reg_sw_ctrl);
	val16 &= ~FPGA0_RF_RFENV;
	val16 |= rfsi_rfenv;
	rtl8xxxu_ग_लिखो16(priv, reg_sw_ctrl, val16);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8xxxu_llt_ग_लिखो(काष्ठा rtl8xxxu_priv *priv, u8 address, u8 data)
अणु
	पूर्णांक ret = -EBUSY;
	पूर्णांक count = 0;
	u32 value;

	value = LLT_OP_WRITE | address << 8 | data;

	rtl8xxxu_ग_लिखो32(priv, REG_LLT_INIT, value);

	करो अणु
		value = rtl8xxxu_पढ़ो32(priv, REG_LLT_INIT);
		अगर ((value & LLT_OP_MASK) == LLT_OP_INACTIVE) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (count++ < 20);

	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_init_llt_table(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u8 last_tx_page;

	last_tx_page = priv->fops->total_page_num;

	क्रम (i = 0; i < last_tx_page; i++) अणु
		ret = rtl8xxxu_llt_ग_लिखो(priv, i, i + 1);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	ret = rtl8xxxu_llt_ग_लिखो(priv, last_tx_page, 0xff);
	अगर (ret)
		जाओ निकास;

	/* Mark reमुख्यing pages as a ring buffer */
	क्रम (i = last_tx_page + 1; i < 0xff; i++) अणु
		ret = rtl8xxxu_llt_ग_लिखो(priv, i, (i + 1));
		अगर (ret)
			जाओ निकास;
	पूर्ण

	/*  Let last entry poपूर्णांक to the start entry of ring buffer */
	ret = rtl8xxxu_llt_ग_लिखो(priv, 0xff, last_tx_page + 1);
	अगर (ret)
		जाओ निकास;

निकास:
	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_स्वतः_llt_table(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;
	पूर्णांक ret = 0;
	पूर्णांक i;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_AUTO_LLT);
	val32 |= AUTO_LLT_INIT_LLT;
	rtl8xxxu_ग_लिखो32(priv, REG_AUTO_LLT, val32);

	क्रम (i = 500; i; i--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_AUTO_LLT);
		अगर (!(val32 & AUTO_LLT_INIT_LLT))
			अवरोध;
		usleep_range(2, 4);
	पूर्ण

	अगर (!i) अणु
		ret = -EBUSY;
		dev_warn(&priv->udev->dev, "LLT table init failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8xxxu_init_queue_priority(काष्ठा rtl8xxxu_priv *priv)
अणु
	u16 val16, hi, lo;
	u16 hiq, mgq, bkq, beq, viq, voq;
	पूर्णांक hip, mgp, bkp, bep, vip, vop;
	पूर्णांक ret = 0;

	चयन (priv->ep_tx_count) अणु
	हाल 1:
		अगर (priv->ep_tx_high_queue) अणु
			hi = TRXDMA_QUEUE_HIGH;
		पूर्ण अन्यथा अगर (priv->ep_tx_low_queue) अणु
			hi = TRXDMA_QUEUE_LOW;
		पूर्ण अन्यथा अगर (priv->ep_tx_normal_queue) अणु
			hi = TRXDMA_QUEUE_NORMAL;
		पूर्ण अन्यथा अणु
			hi = 0;
			ret = -EINVAL;
		पूर्ण

		hiq = hi;
		mgq = hi;
		bkq = hi;
		beq = hi;
		viq = hi;
		voq = hi;

		hip = 0;
		mgp = 0;
		bkp = 0;
		bep = 0;
		vip = 0;
		vop = 0;
		अवरोध;
	हाल 2:
		अगर (priv->ep_tx_high_queue && priv->ep_tx_low_queue) अणु
			hi = TRXDMA_QUEUE_HIGH;
			lo = TRXDMA_QUEUE_LOW;
		पूर्ण अन्यथा अगर (priv->ep_tx_normal_queue && priv->ep_tx_low_queue) अणु
			hi = TRXDMA_QUEUE_NORMAL;
			lo = TRXDMA_QUEUE_LOW;
		पूर्ण अन्यथा अगर (priv->ep_tx_high_queue && priv->ep_tx_normal_queue) अणु
			hi = TRXDMA_QUEUE_HIGH;
			lo = TRXDMA_QUEUE_NORMAL;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			hi = 0;
			lo = 0;
		पूर्ण

		hiq = hi;
		mgq = hi;
		bkq = lo;
		beq = lo;
		viq = hi;
		voq = hi;

		hip = 0;
		mgp = 0;
		bkp = 1;
		bep = 1;
		vip = 0;
		vop = 0;
		अवरोध;
	हाल 3:
		beq = TRXDMA_QUEUE_LOW;
		bkq = TRXDMA_QUEUE_LOW;
		viq = TRXDMA_QUEUE_NORMAL;
		voq = TRXDMA_QUEUE_HIGH;
		mgq = TRXDMA_QUEUE_HIGH;
		hiq = TRXDMA_QUEUE_HIGH;

		hip = hiq ^ 3;
		mgp = mgq ^ 3;
		bkp = bkq ^ 3;
		bep = beq ^ 3;
		vip = viq ^ 3;
		vop = viq ^ 3;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	/*
	 * None of the venकरोr drivers are configuring the beacon
	 * queue here .... why?
	 */
	अगर (!ret) अणु
		val16 = rtl8xxxu_पढ़ो16(priv, REG_TRXDMA_CTRL);
		val16 &= 0x7;
		val16 |= (voq << TRXDMA_CTRL_VOQ_SHIFT) |
			(viq << TRXDMA_CTRL_VIQ_SHIFT) |
			(beq << TRXDMA_CTRL_BEQ_SHIFT) |
			(bkq << TRXDMA_CTRL_BKQ_SHIFT) |
			(mgq << TRXDMA_CTRL_MGQ_SHIFT) |
			(hiq << TRXDMA_CTRL_HIQ_SHIFT);
		rtl8xxxu_ग_लिखो16(priv, REG_TRXDMA_CTRL, val16);

		priv->pipe_out[TXDESC_QUEUE_VO] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[vop]);
		priv->pipe_out[TXDESC_QUEUE_VI] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[vip]);
		priv->pipe_out[TXDESC_QUEUE_BE] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[bep]);
		priv->pipe_out[TXDESC_QUEUE_BK] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[bkp]);
		priv->pipe_out[TXDESC_QUEUE_BEACON] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[0]);
		priv->pipe_out[TXDESC_QUEUE_MGNT] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[mgp]);
		priv->pipe_out[TXDESC_QUEUE_HIGH] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[hip]);
		priv->pipe_out[TXDESC_QUEUE_CMD] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[0]);
	पूर्ण

	वापस ret;
पूर्ण

व्योम rtl8xxxu_fill_iqk_matrix_a(काष्ठा rtl8xxxu_priv *priv, bool iqk_ok,
				पूर्णांक result[][8], पूर्णांक candidate, bool tx_only)
अणु
	u32 oldval, x, tx0_a, reg;
	पूर्णांक y, tx0_c;
	u32 val32;

	अगर (!iqk_ok)
		वापस;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_TX_IQ_IMBALANCE);
	oldval = val32 >> 22;

	x = result[candidate][0];
	अगर ((x & 0x00000200) != 0)
		x = x | 0xfffffc00;
	tx0_a = (x * oldval) >> 8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_TX_IQ_IMBALANCE);
	val32 &= ~0x3ff;
	val32 |= tx0_a;
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_TX_IQ_IMBALANCE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_ENERGY_CCA_THRES);
	val32 &= ~BIT(31);
	अगर ((x * oldval >> 7) & 0x1)
		val32 |= BIT(31);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_ENERGY_CCA_THRES, val32);

	y = result[candidate][1];
	अगर ((y & 0x00000200) != 0)
		y = y | 0xfffffc00;
	tx0_c = (y * oldval) >> 8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XC_TX_AFE);
	val32 &= ~0xf0000000;
	val32 |= (((tx0_c & 0x3c0) >> 6) << 28);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XC_TX_AFE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_TX_IQ_IMBALANCE);
	val32 &= ~0x003f0000;
	val32 |= ((tx0_c & 0x3f) << 16);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_TX_IQ_IMBALANCE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_ENERGY_CCA_THRES);
	val32 &= ~BIT(29);
	अगर ((y * oldval >> 7) & 0x1)
		val32 |= BIT(29);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_ENERGY_CCA_THRES, val32);

	अगर (tx_only) अणु
		dev_dbg(&priv->udev->dev, "%s: only TX\n", __func__);
		वापस;
	पूर्ण

	reg = result[candidate][2];

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_RX_IQ_IMBALANCE);
	val32 &= ~0x3ff;
	val32 |= (reg & 0x3ff);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_RX_IQ_IMBALANCE, val32);

	reg = result[candidate][3] & 0x3F;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_RX_IQ_IMBALANCE);
	val32 &= ~0xfc00;
	val32 |= ((reg << 10) & 0xfc00);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_RX_IQ_IMBALANCE, val32);

	reg = (result[candidate][3] >> 6) & 0xF;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_RX_IQ_EXT_ANTA);
	val32 &= ~0xf0000000;
	val32 |= (reg << 28);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_RX_IQ_EXT_ANTA, val32);
पूर्ण

व्योम rtl8xxxu_fill_iqk_matrix_b(काष्ठा rtl8xxxu_priv *priv, bool iqk_ok,
				पूर्णांक result[][8], पूर्णांक candidate, bool tx_only)
अणु
	u32 oldval, x, tx1_a, reg;
	पूर्णांक y, tx1_c;
	u32 val32;

	अगर (!iqk_ok)
		वापस;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_TX_IQ_IMBALANCE);
	oldval = val32 >> 22;

	x = result[candidate][4];
	अगर ((x & 0x00000200) != 0)
		x = x | 0xfffffc00;
	tx1_a = (x * oldval) >> 8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_TX_IQ_IMBALANCE);
	val32 &= ~0x3ff;
	val32 |= tx1_a;
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_TX_IQ_IMBALANCE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_ENERGY_CCA_THRES);
	val32 &= ~BIT(27);
	अगर ((x * oldval >> 7) & 0x1)
		val32 |= BIT(27);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_ENERGY_CCA_THRES, val32);

	y = result[candidate][5];
	अगर ((y & 0x00000200) != 0)
		y = y | 0xfffffc00;
	tx1_c = (y * oldval) >> 8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XD_TX_AFE);
	val32 &= ~0xf0000000;
	val32 |= (((tx1_c & 0x3c0) >> 6) << 28);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XD_TX_AFE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_TX_IQ_IMBALANCE);
	val32 &= ~0x003f0000;
	val32 |= ((tx1_c & 0x3f) << 16);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_TX_IQ_IMBALANCE, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_ENERGY_CCA_THRES);
	val32 &= ~BIT(25);
	अगर ((y * oldval >> 7) & 0x1)
		val32 |= BIT(25);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_ENERGY_CCA_THRES, val32);

	अगर (tx_only) अणु
		dev_dbg(&priv->udev->dev, "%s: only TX\n", __func__);
		वापस;
	पूर्ण

	reg = result[candidate][6];

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_RX_IQ_IMBALANCE);
	val32 &= ~0x3ff;
	val32 |= (reg & 0x3ff);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_RX_IQ_IMBALANCE, val32);

	reg = result[candidate][7] & 0x3f;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_RX_IQ_IMBALANCE);
	val32 &= ~0xfc00;
	val32 |= ((reg << 10) & 0xfc00);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_RX_IQ_IMBALANCE, val32);

	reg = (result[candidate][7] >> 6) & 0xf;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_AGCR_SSI_TABLE);
	val32 &= ~0x0000f000;
	val32 |= (reg << 12);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_AGCR_SSI_TABLE, val32);
पूर्ण

#घोषणा MAX_TOLERANCE		5

अटल bool rtl8xxxu_simularity_compare(काष्ठा rtl8xxxu_priv *priv,
					पूर्णांक result[][8], पूर्णांक c1, पूर्णांक c2)
अणु
	u32 i, j, dअगरf, simubiपंचांगap, bound = 0;
	पूर्णांक candidate[2] = अणु-1, -1पूर्ण;	/* क्रम path A and path B */
	bool retval = true;

	अगर (priv->tx_paths > 1)
		bound = 8;
	अन्यथा
		bound = 4;

	simubiपंचांगap = 0;

	क्रम (i = 0; i < bound; i++) अणु
		dअगरf = (result[c1][i] > result[c2][i]) ?
			(result[c1][i] - result[c2][i]) :
			(result[c2][i] - result[c1][i]);
		अगर (dअगरf > MAX_TOLERANCE) अणु
			अगर ((i == 2 || i == 6) && !simubiपंचांगap) अणु
				अगर (result[c1][i] + result[c1][i + 1] == 0)
					candidate[(i / 4)] = c2;
				अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
					candidate[(i / 4)] = c1;
				अन्यथा
					simubiपंचांगap = simubiपंचांगap | (1 << i);
			पूर्ण अन्यथा अणु
				simubiपंचांगap = simubiपंचांगap | (1 << i);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (simubiपंचांगap == 0) अणु
		क्रम (i = 0; i < (bound / 4); i++) अणु
			अगर (candidate[i] >= 0) अणु
				क्रम (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] = result[candidate[i]][j];
				retval = false;
			पूर्ण
		पूर्ण
		वापस retval;
	पूर्ण अन्यथा अगर (!(simubiपंचांगap & 0x0f)) अणु
		/* path A OK */
		क्रम (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
	पूर्ण अन्यथा अगर (!(simubiपंचांगap & 0xf0) && priv->tx_paths > 1) अणु
		/* path B OK */
		क्रम (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
	पूर्ण

	वापस false;
पूर्ण

bool rtl8xxxu_gen2_simularity_compare(काष्ठा rtl8xxxu_priv *priv,
				      पूर्णांक result[][8], पूर्णांक c1, पूर्णांक c2)
अणु
	u32 i, j, dअगरf, simubiपंचांगap, bound = 0;
	पूर्णांक candidate[2] = अणु-1, -1पूर्ण;	/* क्रम path A and path B */
	पूर्णांक पंचांगp1, पंचांगp2;
	bool retval = true;

	अगर (priv->tx_paths > 1)
		bound = 8;
	अन्यथा
		bound = 4;

	simubiपंचांगap = 0;

	क्रम (i = 0; i < bound; i++) अणु
		अगर (i & 1) अणु
			अगर ((result[c1][i] & 0x00000200))
				पंचांगp1 = result[c1][i] | 0xfffffc00;
			अन्यथा
				पंचांगp1 = result[c1][i];

			अगर ((result[c2][i]& 0x00000200))
				पंचांगp2 = result[c2][i] | 0xfffffc00;
			अन्यथा
				पंचांगp2 = result[c2][i];
		पूर्ण अन्यथा अणु
			पंचांगp1 = result[c1][i];
			पंचांगp2 = result[c2][i];
		पूर्ण

		dअगरf = (पंचांगp1 > पंचांगp2) ? (पंचांगp1 - पंचांगp2) : (पंचांगp2 - पंचांगp1);

		अगर (dअगरf > MAX_TOLERANCE) अणु
			अगर ((i == 2 || i == 6) && !simubiपंचांगap) अणु
				अगर (result[c1][i] + result[c1][i + 1] == 0)
					candidate[(i / 4)] = c2;
				अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
					candidate[(i / 4)] = c1;
				अन्यथा
					simubiपंचांगap = simubiपंचांगap | (1 << i);
			पूर्ण अन्यथा अणु
				simubiपंचांगap = simubiपंचांगap | (1 << i);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (simubiपंचांगap == 0) अणु
		क्रम (i = 0; i < (bound / 4); i++) अणु
			अगर (candidate[i] >= 0) अणु
				क्रम (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] = result[candidate[i]][j];
				retval = false;
			पूर्ण
		पूर्ण
		वापस retval;
	पूर्ण अन्यथा अणु
		अगर (!(simubiपंचांगap & 0x03)) अणु
			/* path A TX OK */
			क्रम (i = 0; i < 2; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(simubiपंचांगap & 0x0c)) अणु
			/* path A RX OK */
			क्रम (i = 2; i < 4; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(simubiपंचांगap & 0x30) && priv->tx_paths > 1) अणु
			/* path B RX OK */
			क्रम (i = 4; i < 6; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(simubiपंचांगap & 0x30) && priv->tx_paths > 1) अणु
			/* path B RX OK */
			क्रम (i = 6; i < 8; i++)
				result[3][i] = result[c1][i];
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

व्योम
rtl8xxxu_save_mac_regs(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *reg, u32 *backup)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (RTL8XXXU_MAC_REGS - 1); i++)
		backup[i] = rtl8xxxu_पढ़ो8(priv, reg[i]);

	backup[i] = rtl8xxxu_पढ़ो32(priv, reg[i]);
पूर्ण

व्योम rtl8xxxu_restore_mac_regs(काष्ठा rtl8xxxu_priv *priv,
			       स्थिर u32 *reg, u32 *backup)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (RTL8XXXU_MAC_REGS - 1); i++)
		rtl8xxxu_ग_लिखो8(priv, reg[i], backup[i]);

	rtl8xxxu_ग_लिखो32(priv, reg[i], backup[i]);
पूर्ण

व्योम rtl8xxxu_save_regs(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			u32 *backup, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		backup[i] = rtl8xxxu_पढ़ो32(priv, regs[i]);
पूर्ण

व्योम rtl8xxxu_restore_regs(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			   u32 *backup, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		rtl8xxxu_ग_लिखो32(priv, regs[i], backup[i]);
पूर्ण


व्योम rtl8xxxu_path_adda_on(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			   bool path_a_on)
अणु
	u32 path_on;
	पूर्णांक i;

	अगर (priv->tx_paths == 1) अणु
		path_on = priv->fops->adda_1t_path_on;
		rtl8xxxu_ग_लिखो32(priv, regs[0], priv->fops->adda_1t_init);
	पूर्ण अन्यथा अणु
		path_on = path_a_on ? priv->fops->adda_2t_path_on_a :
			priv->fops->adda_2t_path_on_b;

		rtl8xxxu_ग_लिखो32(priv, regs[0], path_on);
	पूर्ण

	क्रम (i = 1 ; i < RTL8XXXU_ADDA_REGS ; i++)
		rtl8xxxu_ग_लिखो32(priv, regs[i], path_on);
पूर्ण

व्योम rtl8xxxu_mac_calibration(काष्ठा rtl8xxxu_priv *priv,
			      स्थिर u32 *regs, u32 *backup)
अणु
	पूर्णांक i = 0;

	rtl8xxxu_ग_लिखो8(priv, regs[i], 0x3f);

	क्रम (i = 1 ; i < (RTL8XXXU_MAC_REGS - 1); i++)
		rtl8xxxu_ग_लिखो8(priv, regs[i], (u8)(backup[i] & ~BIT(3)));

	rtl8xxxu_ग_लिखो8(priv, regs[i], (u8)(backup[i] & ~BIT(5)));
पूर्ण

अटल पूर्णांक rtl8xxxu_iqk_path_a(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4, val32;
	पूर्णांक result = 0;

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x10008c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x10008c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82140102);

	val32 = (priv->rf_paths > 1) ? 0x28160202 :
		/*IS_81xxC_VENDOR_UMC_B_CUT(pHalData->VersionID)?0x28160202: */
		0x28160502;
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, val32);

	/* path-B IQK setting */
	अगर (priv->rf_paths > 1) अणु
		rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x10008c22);
		rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x10008c22);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x82140102);
		rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x28160202);
	पूर्ण

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x001028d1);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_A);
	reg_ea4 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_A_2);

	अगर (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000))
		result |= 0x01;
	अन्यथा	/* If TX not OK, ignore RX */
		जाओ out;

	/* If TX is OK, check whether RX is OK */
	अगर (!(reg_eac & BIT(27)) &&
	    ((reg_ea4 & 0x03ff0000) != 0x01320000) &&
	    ((reg_eac & 0x03ff0000) != 0x00360000))
		result |= 0x02;
	अन्यथा
		dev_warn(&priv->udev->dev, "%s: Path A RX IQK failed!\n",
			 __func__);
out:
	वापस result;
पूर्ण

अटल पूर्णांक rtl8xxxu_iqk_path_b(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_eb4, reg_ebc, reg_ec4, reg_ecc;
	पूर्णांक result = 0;

	/* One shot, path B LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_CONT, 0x00000002);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_CONT, 0x00000000);

	mdelay(1);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_eb4 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
	reg_ebc = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);
	reg_ec4 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_B_2);
	reg_ecc = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_B_2);

	अगर (!(reg_eac & BIT(31)) &&
	    ((reg_eb4 & 0x03ff0000) != 0x01420000) &&
	    ((reg_ebc & 0x03ff0000) != 0x00420000))
		result |= 0x01;
	अन्यथा
		जाओ out;

	अगर (!(reg_eac & BIT(30)) &&
	    (((reg_ec4 & 0x03ff0000) >> 16) != 0x132) &&
	    (((reg_ecc & 0x03ff0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		dev_warn(&priv->udev->dev, "%s: Path B RX IQK failed!\n",
			 __func__);
out:
	वापस result;
पूर्ण

अटल व्योम rtl8xxxu_phy_iqcalibrate(काष्ठा rtl8xxxu_priv *priv,
				     पूर्णांक result[][8], पूर्णांक t)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	u32 i, val32;
	पूर्णांक path_a_ok, path_b_ok;
	पूर्णांक retry = 2;
	अटल स्थिर u32 adda_regs[RTL8XXXU_ADDA_REGS] = अणु
		REG_FPGA0_XCD_SWITCH_CTRL, REG_BLUETOOTH,
		REG_RX_WAIT_CCA, REG_TX_CCK_RFON,
		REG_TX_CCK_BBON, REG_TX_OFDM_RFON,
		REG_TX_OFDM_BBON, REG_TX_TO_RX,
		REG_TX_TO_TX, REG_RX_CCK,
		REG_RX_OFDM, REG_RX_WAIT_RIFS,
		REG_RX_TO_RX, REG_STANDBY,
		REG_SLEEP, REG_PMPD_ANAEN
	पूर्ण;
	अटल स्थिर u32 iqk_mac_regs[RTL8XXXU_MAC_REGS] = अणु
		REG_TXPAUSE, REG_BEACON_CTRL,
		REG_BEACON_CTRL_1, REG_GPIO_MUXCFG
	पूर्ण;
	अटल स्थिर u32 iqk_bb_regs[RTL8XXXU_BB_REGS] = अणु
		REG_OFDM0_TRX_PATH_ENABLE, REG_OFDM0_TR_MUX_PAR,
		REG_FPGA0_XCD_RF_SW_CTRL, REG_CONFIG_ANT_A, REG_CONFIG_ANT_B,
		REG_FPGA0_XAB_RF_SW_CTRL, REG_FPGA0_XA_RF_INT_OE,
		REG_FPGA0_XB_RF_INT_OE, REG_FPGA0_RF_MODE
	पूर्ण;

	/*
	 * Note: IQ calibration must be perक्रमmed after loading
	 *       PHY_REG.txt , and radio_a, radio_b.txt
	 */

	अगर (t == 0) अणु
		/* Save ADDA parameters, turn Path A ADDA on */
		rtl8xxxu_save_regs(priv, adda_regs, priv->adda_backup,
				   RTL8XXXU_ADDA_REGS);
		rtl8xxxu_save_mac_regs(priv, iqk_mac_regs, priv->mac_backup);
		rtl8xxxu_save_regs(priv, iqk_bb_regs,
				   priv->bb_backup, RTL8XXXU_BB_REGS);
	पूर्ण

	rtl8xxxu_path_adda_on(priv, adda_regs, true);

	अगर (t == 0) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XA_HSSI_PARM1);
		अगर (val32 & FPGA0_HSSI_PARM1_PI)
			priv->pi_enabled = 1;
	पूर्ण

	अगर (!priv->pi_enabled) अणु
		/* Switch BB to PI mode to करो IQ Calibration. */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_HSSI_PARM1, 0x01000100);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_HSSI_PARM1, 0x01000100);
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
	val32 &= ~FPGA_RF_MODE_CCK;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TRX_PATH_ENABLE, 0x03a05600);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TR_MUX_PAR, 0x000800e4);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XCD_RF_SW_CTRL, 0x22204000);

	अगर (!priv->no_pape) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XAB_RF_SW_CTRL);
		val32 |= (FPGA0_RF_PAPE |
			  (FPGA0_RF_PAPE << FPGA0_RF_BD_CTRL_SHIFT));
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XAB_RF_SW_CTRL, val32);
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XA_RF_INT_OE);
	val32 &= ~BIT(10);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_RF_INT_OE, val32);
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XB_RF_INT_OE);
	val32 &= ~BIT(10);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_RF_INT_OE, val32);

	अगर (priv->tx_paths > 1) अणु
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_LSSI_PARM, 0x00010000);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_LSSI_PARM, 0x00010000);
	पूर्ण

	/* MAC settings */
	rtl8xxxu_mac_calibration(priv, iqk_mac_regs, priv->mac_backup);

	/* Page B init */
	rtl8xxxu_ग_लिखो32(priv, REG_CONFIG_ANT_A, 0x00080000);

	अगर (priv->tx_paths > 1)
		rtl8xxxu_ग_लिखो32(priv, REG_CONFIG_ANT_B, 0x00080000);

	/* IQ calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	क्रम (i = 0; i < retry; i++) अणु
		path_a_ok = rtl8xxxu_iqk_path_a(priv);
		अगर (path_a_ok == 0x03) अणु
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_BEFORE_IQK_A);
			result[t][0] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_AFTER_IQK_A);
			result[t][1] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_RX_POWER_BEFORE_IQK_A_2);
			result[t][2] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_RX_POWER_AFTER_IQK_A_2);
			result[t][3] = (val32 >> 16) & 0x3ff;
			अवरोध;
		पूर्ण अन्यथा अगर (i == (retry - 1) && path_a_ok == 0x01) अणु
			/* TX IQK OK */
			dev_dbg(dev, "%s: Path A IQK Only Tx Success!!\n",
				__func__);

			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_BEFORE_IQK_A);
			result[t][0] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_AFTER_IQK_A);
			result[t][1] = (val32 >> 16) & 0x3ff;
		पूर्ण
	पूर्ण

	अगर (!path_a_ok)
		dev_dbg(dev, "%s: Path A IQK failed!\n", __func__);

	अगर (priv->tx_paths > 1) अणु
		/*
		 * Path A पूर्णांकo standby
		 */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x0);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_LSSI_PARM, 0x00010000);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

		/* Turn Path B ADDA on */
		rtl8xxxu_path_adda_on(priv, adda_regs, false);

		क्रम (i = 0; i < retry; i++) अणु
			path_b_ok = rtl8xxxu_iqk_path_b(priv);
			अगर (path_b_ok == 0x03) अणु
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
				result[t][4] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);
				result[t][5] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_B_2);
				result[t][6] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_B_2);
				result[t][7] = (val32 >> 16) & 0x3ff;
				अवरोध;
			पूर्ण अन्यथा अगर (i == (retry - 1) && path_b_ok == 0x01) अणु
				/* TX IQK OK */
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
				result[t][4] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);
				result[t][5] = (val32 >> 16) & 0x3ff;
			पूर्ण
		पूर्ण

		अगर (!path_b_ok)
			dev_dbg(dev, "%s: Path B IQK failed!\n", __func__);
	पूर्ण

	/* Back to BB mode, load original value */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0);

	अगर (t) अणु
		अगर (!priv->pi_enabled) अणु
			/*
			 * Switch back BB to SI mode after finishing
			 * IQ Calibration
			 */
			val32 = 0x01000000;
			rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_HSSI_PARM1, val32);
			rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_HSSI_PARM1, val32);
		पूर्ण

		/* Reload ADDA घातer saving parameters */
		rtl8xxxu_restore_regs(priv, adda_regs, priv->adda_backup,
				      RTL8XXXU_ADDA_REGS);

		/* Reload MAC parameters */
		rtl8xxxu_restore_mac_regs(priv, iqk_mac_regs, priv->mac_backup);

		/* Reload BB parameters */
		rtl8xxxu_restore_regs(priv, iqk_bb_regs,
				      priv->bb_backup, RTL8XXXU_BB_REGS);

		/* Restore RX initial gain */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_LSSI_PARM, 0x00032ed3);

		अगर (priv->tx_paths > 1) अणु
			rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_LSSI_PARM,
					 0x00032ed3);
		पूर्ण

		/* Load 0xe30 IQC शेष value */
		rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x01008c00);
		rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x01008c00);
	पूर्ण
पूर्ण

व्योम rtl8xxxu_gen2_prepare_calibrate(काष्ठा rtl8xxxu_priv *priv, u8 start)
अणु
	काष्ठा h2c_cmd h2c;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.bt_wlan_calibration.cmd = H2C_8723B_BT_WLAN_CALIBRATION;
	h2c.bt_wlan_calibration.data = start;

	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.bt_wlan_calibration));
पूर्ण

व्योम rtl8xxxu_gen1_phy_iq_calibrate(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक result[4][8];	/* last is final result */
	पूर्णांक i, candidate;
	bool path_a_ok, path_b_ok;
	u32 reg_e94, reg_e9c, reg_ea4, reg_eac;
	u32 reg_eb4, reg_ebc, reg_ec4, reg_ecc;
	s32 reg_पंचांगp = 0;
	bool simu;

	स_रखो(result, 0, माप(result));
	candidate = -1;

	path_a_ok = false;
	path_b_ok = false;

	rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);

	क्रम (i = 0; i < 3; i++) अणु
		rtl8xxxu_phy_iqcalibrate(priv, result, i);

		अगर (i == 1) अणु
			simu = rtl8xxxu_simularity_compare(priv, result, 0, 1);
			अगर (simu) अणु
				candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 2) अणु
			simu = rtl8xxxu_simularity_compare(priv, result, 0, 2);
			अगर (simu) अणु
				candidate = 0;
				अवरोध;
			पूर्ण

			simu = rtl8xxxu_simularity_compare(priv, result, 1, 2);
			अगर (simu) अणु
				candidate = 1;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < 8; i++)
					reg_पंचांगp += result[3][i];

				अगर (reg_पंचांगp)
					candidate = 3;
				अन्यथा
					candidate = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		reg_e94 = result[i][0];
		reg_e9c = result[i][1];
		reg_ea4 = result[i][2];
		reg_eac = result[i][3];
		reg_eb4 = result[i][4];
		reg_ebc = result[i][5];
		reg_ec4 = result[i][6];
		reg_ecc = result[i][7];
	पूर्ण

	अगर (candidate >= 0) अणु
		reg_e94 = result[candidate][0];
		priv->rege94 =  reg_e94;
		reg_e9c = result[candidate][1];
		priv->rege9c = reg_e9c;
		reg_ea4 = result[candidate][2];
		reg_eac = result[candidate][3];
		reg_eb4 = result[candidate][4];
		priv->regeb4 = reg_eb4;
		reg_ebc = result[candidate][5];
		priv->regebc = reg_ebc;
		reg_ec4 = result[candidate][6];
		reg_ecc = result[candidate][7];
		dev_dbg(dev, "%s: candidate is %x\n", __func__, candidate);
		dev_dbg(dev,
			"%s: e94 =%x e9c=%x ea4=%x eac=%x eb4=%x ebc=%x ec4=%x ecc=%x\n",
			__func__, reg_e94, reg_e9c,
			reg_ea4, reg_eac, reg_eb4, reg_ebc, reg_ec4, reg_ecc);
		path_a_ok = true;
		path_b_ok = true;
	पूर्ण अन्यथा अणु
		reg_e94 = reg_eb4 = priv->rege94 = priv->regeb4 = 0x100;
		reg_e9c = reg_ebc = priv->rege9c = priv->regebc = 0x0;
	पूर्ण

	अगर (reg_e94 && candidate >= 0)
		rtl8xxxu_fill_iqk_matrix_a(priv, path_a_ok, result,
					   candidate, (reg_ea4 == 0));

	अगर (priv->tx_paths > 1 && reg_eb4)
		rtl8xxxu_fill_iqk_matrix_b(priv, path_b_ok, result,
					   candidate, (reg_ec4 == 0));

	rtl8xxxu_save_regs(priv, rtl8xxxu_iqk_phy_iq_bb_reg,
			   priv->bb_recovery_backup, RTL8XXXU_BB_REGS);
पूर्ण

अटल व्योम rtl8723a_phy_lc_calibrate(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;
	u32 rf_amode, rf_bmode = 0, lstf;

	/* Check continuous TX and Packet TX */
	lstf = rtl8xxxu_पढ़ो32(priv, REG_OFDM1_LSTF);

	अगर (lstf & OFDM_LSTF_MASK) अणु
		/* Disable all continuous TX */
		val32 = lstf & ~OFDM_LSTF_MASK;
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM1_LSTF, val32);

		/* Read original RF mode Path A */
		rf_amode = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_AC);

		/* Set RF mode to standby Path A */
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC,
				     (rf_amode & 0x8ffff) | 0x10000);

		/* Path-B */
		अगर (priv->tx_paths > 1) अणु
			rf_bmode = rtl8xxxu_पढ़ो_rfreg(priv, RF_B,
						       RF6052_REG_AC);

			rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_AC,
					     (rf_bmode & 0x8ffff) | 0x10000);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  Deal with Packet TX हाल */
		/*  block all queues */
		rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);
	पूर्ण

	/* Start LC calibration */
	अगर (priv->fops->has_s0s1)
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_S0S1, 0xdfbe0);
	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_MODE_AG);
	val32 |= 0x08000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_MODE_AG, val32);

	msleep(100);

	अगर (priv->fops->has_s0s1)
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_S0S1, 0xdffe0);

	/* Restore original parameters */
	अगर (lstf & OFDM_LSTF_MASK) अणु
		/* Path-A */
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM1_LSTF, lstf);
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC, rf_amode);

		/* Path-B */
		अगर (priv->tx_paths > 1)
			rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_AC,
					     rf_bmode);
	पूर्ण अन्यथा /*  Deal with Packet TX हाल */
		rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0x00);
पूर्ण

अटल पूर्णांक rtl8xxxu_set_mac(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक i;
	u16 reg;

	reg = REG_MACID;

	क्रम (i = 0; i < ETH_ALEN; i++)
		rtl8xxxu_ग_लिखो8(priv, reg + i, priv->mac_addr[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8xxxu_set_bssid(काष्ठा rtl8xxxu_priv *priv, स्थिर u8 *bssid)
अणु
	पूर्णांक i;
	u16 reg;

	dev_dbg(&priv->udev->dev, "%s: (%pM)\n", __func__, bssid);

	reg = REG_BSSID;

	क्रम (i = 0; i < ETH_ALEN; i++)
		rtl8xxxu_ग_लिखो8(priv, reg + i, bssid[i]);

	वापस 0;
पूर्ण

अटल व्योम
rtl8xxxu_set_ampdu_factor(काष्ठा rtl8xxxu_priv *priv, u8 ampdu_factor)
अणु
	u8 vals[4] = अणु 0x41, 0xa8, 0x72, 0xb9 पूर्ण;
	u8 max_agg = 0xf;
	पूर्णांक i;

	ampdu_factor = 1 << (ampdu_factor + 2);
	अगर (ampdu_factor > max_agg)
		ampdu_factor = max_agg;

	क्रम (i = 0; i < 4; i++) अणु
		अगर ((vals[i] & 0xf0) > (ampdu_factor << 4))
			vals[i] = (vals[i] & 0x0f) | (ampdu_factor << 4);

		अगर ((vals[i] & 0x0f) > ampdu_factor)
			vals[i] = (vals[i] & 0xf0) | ampdu_factor;

		rtl8xxxu_ग_लिखो8(priv, REG_AGGLEN_LMT + i, vals[i]);
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_set_ampdu_min_space(काष्ठा rtl8xxxu_priv *priv, u8 density)
अणु
	u8 val8;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_AMPDU_MIN_SPACE);
	val8 &= 0xf8;
	val8 |= density;
	rtl8xxxu_ग_लिखो8(priv, REG_AMPDU_MIN_SPACE, val8);
पूर्ण

अटल पूर्णांक rtl8xxxu_active_to_emu(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	पूर्णांक count, ret = 0;

	/* Start of rtl8723AU_card_enable_flow */
	/* Act to Cardemu sequence*/
	/* Turn off RF */
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, 0);

	/* 0x004E[7] = 0, चयन DPDT_SEL_P output from रेजिस्टर 0x0065[2] */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_LEDCFG2);
	val8 &= ~LEDCFG2_DPDT_SELECT;
	rtl8xxxu_ग_लिखो8(priv, REG_LEDCFG2, val8);

	/* 0x0005[1] = 1 turn off MAC by HW state machine*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 |= BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
		अगर ((val8 & BIT(1)) == 0)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (!count) अणु
		dev_warn(&priv->udev->dev, "%s: Disabling MAC timed out\n",
			 __func__);
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* 0x0000[5] = 1 analog Ips to digital, 1:isolation */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_ISO_CTRL);
	val8 |= SYS_ISO_ANALOG_IPS;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_ISO_CTRL, val8);

	/* 0x0020[0] = 0 disable LDOA12 MACRO block*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_LDOA15_CTRL);
	val8 &= ~LDOA15_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_LDOA15_CTRL, val8);

निकास:
	वापस ret;
पूर्ण

पूर्णांक rtl8xxxu_active_to_lps(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u8 val32;
	पूर्णांक count, ret = 0;

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);

	/*
	 * Poll - रुको क्रम RX packet to complete
	 */
	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, 0x5f8);
		अगर (!val32)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (!count) अणु
		dev_warn(&priv->udev->dev,
			 "%s: RX poll timed out (0x05f8)\n", __func__);
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* Disable CCK and OFDM, घड़ी gated */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_FUNC);
	val8 &= ~SYS_FUNC_BBRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC, val8);

	udelay(2);

	/* Reset baseband */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_FUNC);
	val8 &= ~SYS_FUNC_BB_GLB_RSTN;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC, val8);

	/* Reset MAC TRX */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_CR);
	val8 = CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_CR, val8);

	/* Reset MAC TRX */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_CR + 1);
	val8 &= ~BIT(1); /* CR_SECURITY_ENABLE */
	rtl8xxxu_ग_लिखो8(priv, REG_CR + 1, val8);

	/* Respond TX OK to scheduler */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_DUAL_TSF_RST);
	val8 |= DUAL_TSF_TX_OK;
	rtl8xxxu_ग_लिखो8(priv, REG_DUAL_TSF_RST, val8);

निकास:
	वापस ret;
पूर्ण

व्योम rtl8xxxu_disabled_to_emu(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;

	/* Clear suspend enable and घातer करोwn enable*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(7));
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* 0x48[16] = 0 to disable GPIO9 as EXT WAKEUP*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_INTM + 2);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_INTM + 2, val8);

	/* 0x04[12:11] = 11 enable WL suspend*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);
पूर्ण

अटल पूर्णांक rtl8xxxu_emu_to_disabled(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;

	/* 0x0007[7:0] = 0x20 SOP option to disable BG/MB */
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 3, 0x20);

	/* 0x04[12:11] = 01 enable WL suspend */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~BIT(4);
	val8 |= BIT(3);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 |= BIT(7);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* 0x48[16] = 1 to enable GPIO9 as EXT wakeup */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_INTM + 2);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_INTM + 2, val8);

	वापस 0;
पूर्ण

पूर्णांक rtl8xxxu_flush_fअगरo(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	u32 val32;
	पूर्णांक retry, retval;

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RXPKT_NUM);
	val32 |= RXPKT_NUM_RW_RELEASE_EN;
	rtl8xxxu_ग_लिखो32(priv, REG_RXPKT_NUM, val32);

	retry = 100;
	retval = -EBUSY;

	करो अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_RXPKT_NUM);
		अगर (val32 & RXPKT_NUM_RXDMA_IDLE) अणु
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retry--);

	rtl8xxxu_ग_लिखो16(priv, REG_RQPN_NPQ, 0);
	rtl8xxxu_ग_लिखो32(priv, REG_RQPN, 0x80000000);
	mdelay(2);

	अगर (!retry)
		dev_warn(dev, "Failed to flush FIFO\n");

	वापस retval;
पूर्ण

व्योम rtl8xxxu_gen1_usb_quirks(काष्ठा rtl8xxxu_priv *priv)
अणु
	/* Fix USB पूर्णांकerface पूर्णांकerference issue */
	rtl8xxxu_ग_लिखो8(priv, 0xfe40, 0xe0);
	rtl8xxxu_ग_लिखो8(priv, 0xfe41, 0x8d);
	rtl8xxxu_ग_लिखो8(priv, 0xfe42, 0x80);
	/*
	 * This sets TXDMA_OFFSET_DROP_DATA_EN (bit 9) as well as bits
	 * 8 and 5, क्रम which I have found no करोcumentation.
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_TXDMA_OFFSET_CHK, 0xfd0320);

	/*
	 * Solve too many protocol error on USB bus.
	 * Can't करो this क्रम 8188/8192 UMC A cut parts
	 */
	अगर (!(!priv->chip_cut && priv->venकरोr_umc)) अणु
		rtl8xxxu_ग_लिखो8(priv, 0xfe40, 0xe6);
		rtl8xxxu_ग_लिखो8(priv, 0xfe41, 0x94);
		rtl8xxxu_ग_लिखो8(priv, 0xfe42, 0x80);

		rtl8xxxu_ग_लिखो8(priv, 0xfe40, 0xe0);
		rtl8xxxu_ग_लिखो8(priv, 0xfe41, 0x19);
		rtl8xxxu_ग_लिखो8(priv, 0xfe42, 0x80);

		rtl8xxxu_ग_लिखो8(priv, 0xfe40, 0xe5);
		rtl8xxxu_ग_लिखो8(priv, 0xfe41, 0x91);
		rtl8xxxu_ग_लिखो8(priv, 0xfe42, 0x80);

		rtl8xxxu_ग_लिखो8(priv, 0xfe40, 0xe2);
		rtl8xxxu_ग_लिखो8(priv, 0xfe41, 0x81);
		rtl8xxxu_ग_लिखो8(priv, 0xfe42, 0x80);
	पूर्ण
पूर्ण

व्योम rtl8xxxu_gen2_usb_quirks(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TXDMA_OFFSET_CHK);
	val32 |= TXDMA_OFFSET_DROP_DATA_EN;
	rtl8xxxu_ग_लिखो32(priv, REG_TXDMA_OFFSET_CHK, val32);
पूर्ण

व्योम rtl8xxxu_घातer_off(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;
	u32 val32;

	/*
	 * Workaround क्रम 8188RU LNA घातer leakage problem.
	 */
	अगर (priv->rtl_chip == RTL8188R) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XCD_RF_PARM);
		val32 |= BIT(1);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XCD_RF_PARM, val32);
	पूर्ण

	rtl8xxxu_flush_fअगरo(priv);

	rtl8xxxu_active_to_lps(priv);

	/* Turn off RF */
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, 0x00);

	/* Reset Firmware अगर running in RAM */
	अगर (rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);

	/* Reset MCU */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	/* Reset MCU पढ़ोy status */
	rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, 0x00);

	rtl8xxxu_active_to_emu(priv);
	rtl8xxxu_emu_to_disabled(priv);

	/* Reset MCU IO Wrapper */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	/* RSV_CTRL 0x1C[7:0] = 0x0e  lock ISO/CLK/Power control रेजिस्टर */
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, 0x0e);
पूर्ण

व्योम rtl8723bu_set_ps_tdma(काष्ठा rtl8xxxu_priv *priv,
			   u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
अणु
	काष्ठा h2c_cmd h2c;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.b_type_dma.cmd = H2C_8723B_B_TYPE_TDMA;
	h2c.b_type_dma.data1 = arg1;
	h2c.b_type_dma.data2 = arg2;
	h2c.b_type_dma.data3 = arg3;
	h2c.b_type_dma.data4 = arg4;
	h2c.b_type_dma.data5 = arg5;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.b_type_dma));
पूर्ण

व्योम rtl8xxxu_gen2_disable_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RX_WAIT_CCA);
	val32 &= ~(BIT(22) | BIT(23));
	rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, val32);
पूर्ण

अटल व्योम rtl8xxxu_init_queue_reserved_page(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_fileops *fops = priv->fops;
	u32 hq, lq, nq, eq, pubq;
	u32 val32;

	hq = 0;
	lq = 0;
	nq = 0;
	eq = 0;
	pubq = 0;

	अगर (priv->ep_tx_high_queue)
		hq = fops->page_num_hi;
	अगर (priv->ep_tx_low_queue)
		lq = fops->page_num_lo;
	अगर (priv->ep_tx_normal_queue)
		nq = fops->page_num_norm;

	val32 = (nq << RQPN_NPQ_SHIFT) | (eq << RQPN_EPQ_SHIFT);
	rtl8xxxu_ग_लिखो32(priv, REG_RQPN_NPQ, val32);

	pubq = fops->total_page_num - hq - lq - nq - 1;

	val32 = RQPN_LOAD;
	val32 |= (hq << RQPN_HI_PQ_SHIFT);
	val32 |= (lq << RQPN_LO_PQ_SHIFT);
	val32 |= (pubq << RQPN_PUB_PQ_SHIFT);

	rtl8xxxu_ग_लिखो32(priv, REG_RQPN, val32);
पूर्ण

अटल पूर्णांक rtl8xxxu_init_device(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	काष्ठा rtl8xxxu_fileops *fops = priv->fops;
	bool macघातer;
	पूर्णांक ret;
	u8 val8;
	u16 val16;
	u32 val32;

	/* Check अगर MAC is alपढ़ोy घातered on */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_CR);
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_CLKR);

	/*
	 * Fix 92DU-VC S3 hang with the reason is that secondary mac is not
	 * initialized. First MAC वापसs 0xea, second MAC वापसs 0x00
	 */
	अगर (val8 == 0xea || !(val16 & SYS_CLK_MAC_CLK_ENABLE))
		macघातer = false;
	अन्यथा
		macघातer = true;

	अगर (fops->needs_full_init)
		macघातer = false;

	ret = fops->घातer_on(priv);
	अगर (ret < 0) अणु
		dev_warn(dev, "%s: Failed power on\n", __func__);
		जाओ निकास;
	पूर्ण

	अगर (!macघातer)
		rtl8xxxu_init_queue_reserved_page(priv);

	ret = rtl8xxxu_init_queue_priority(priv);
	dev_dbg(dev, "%s: init_queue_priority %i\n", __func__, ret);
	अगर (ret)
		जाओ निकास;

	/*
	 * Set RX page boundary
	 */
	rtl8xxxu_ग_लिखो16(priv, REG_TRXFF_BNDY + 2, fops->trxff_boundary);

	ret = rtl8xxxu_करोwnload_firmware(priv);
	dev_dbg(dev, "%s: download_firmware %i\n", __func__, ret);
	अगर (ret)
		जाओ निकास;
	ret = rtl8xxxu_start_firmware(priv);
	dev_dbg(dev, "%s: start_firmware %i\n", __func__, ret);
	अगर (ret)
		जाओ निकास;

	अगर (fops->phy_init_antenna_selection)
		fops->phy_init_antenna_selection(priv);

	ret = rtl8xxxu_init_mac(priv);

	dev_dbg(dev, "%s: init_mac %i\n", __func__, ret);
	अगर (ret)
		जाओ निकास;

	ret = rtl8xxxu_init_phy_bb(priv);
	dev_dbg(dev, "%s: init_phy_bb %i\n", __func__, ret);
	अगर (ret)
		जाओ निकास;

	ret = fops->init_phy_rf(priv);
	अगर (ret)
		जाओ निकास;

	/* RFSW Control - clear bit 14 ?? */
	अगर (priv->rtl_chip != RTL8723B && priv->rtl_chip != RTL8192E)
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_TX_INFO, 0x00000003);

	val32 = FPGA0_RF_TRSW | FPGA0_RF_TRSWB | FPGA0_RF_ANTSW |
		FPGA0_RF_ANTSWB |
		((FPGA0_RF_ANTSW | FPGA0_RF_ANTSWB) << FPGA0_RF_BD_CTRL_SHIFT);
	अगर (!priv->no_pape) अणु
		val32 |= (FPGA0_RF_PAPE |
			  (FPGA0_RF_PAPE << FPGA0_RF_BD_CTRL_SHIFT));
	पूर्ण
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XAB_RF_SW_CTRL, val32);

	/* 0x860[6:5]= 00 - why? - this sets antenna B */
	अगर (priv->rtl_chip != RTL8192E)
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_RF_INT_OE, 0x66f60210);

	अगर (!macघातer) अणु
		/*
		 * Set TX buffer boundary
		 */
		val8 = fops->total_page_num + 1;

		rtl8xxxu_ग_लिखो8(priv, REG_TXPKTBUF_BCNQ_BDNY, val8);
		rtl8xxxu_ग_लिखो8(priv, REG_TXPKTBUF_MGQ_BDNY, val8);
		rtl8xxxu_ग_लिखो8(priv, REG_TXPKTBUF_WMAC_LBK_BF_HD, val8);
		rtl8xxxu_ग_लिखो8(priv, REG_TRXFF_BNDY, val8);
		rtl8xxxu_ग_लिखो8(priv, REG_TDECTRL + 1, val8);
	पूर्ण

	/*
	 * The venकरोr drivers set PBP क्रम all devices, except 8192e.
	 * There is no explanation क्रम this in any of the sources.
	 */
	val8 = (fops->pbp_rx << PBP_PAGE_SIZE_RX_SHIFT) |
		(fops->pbp_tx << PBP_PAGE_SIZE_TX_SHIFT);
	अगर (priv->rtl_chip != RTL8192E)
		rtl8xxxu_ग_लिखो8(priv, REG_PBP, val8);

	dev_dbg(dev, "%s: macpower %i\n", __func__, macघातer);
	अगर (!macघातer) अणु
		ret = fops->llt_init(priv);
		अगर (ret) अणु
			dev_warn(dev, "%s: LLT table init failed\n", __func__);
			जाओ निकास;
		पूर्ण

		/*
		 * Chip specअगरic quirks
		 */
		fops->usb_quirks(priv);

		/*
		 * Enable TX report and TX report समयr क्रम 8723bu/8188eu/...
		 */
		अगर (fops->has_tx_report) अणु
			val8 = rtl8xxxu_पढ़ो8(priv, REG_TX_REPORT_CTRL);
			val8 |= TX_REPORT_CTRL_TIMER_ENABLE;
			rtl8xxxu_ग_लिखो8(priv, REG_TX_REPORT_CTRL, val8);
			/* Set MAX RPT MACID */
			rtl8xxxu_ग_लिखो8(priv, REG_TX_REPORT_CTRL + 1, 0x02);
			/* TX report Timer. Unit: 32us */
			rtl8xxxu_ग_लिखो16(priv, REG_TX_REPORT_TIME, 0xcdf0);

			/* पंचांगp ps ? */
			val8 = rtl8xxxu_पढ़ो8(priv, 0xa3);
			val8 &= 0xf8;
			rtl8xxxu_ग_लिखो8(priv, 0xa3, val8);
		पूर्ण
	पूर्ण

	/*
	 * Unit in 8 bytes, not obvious what it is used क्रम
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_RX_DRVINFO_SZ, 4);

	अगर (priv->rtl_chip == RTL8192E) अणु
		rtl8xxxu_ग_लिखो32(priv, REG_HIMR0, 0x00);
		rtl8xxxu_ग_लिखो32(priv, REG_HIMR1, 0x00);
	पूर्ण अन्यथा अणु
		/*
		 * Enable all पूर्णांकerrupts - not obvious USB needs to करो this
		 */
		rtl8xxxu_ग_लिखो32(priv, REG_HISR, 0xffffffff);
		rtl8xxxu_ग_लिखो32(priv, REG_HIMR, 0xffffffff);
	पूर्ण

	rtl8xxxu_set_mac(priv);
	rtl8xxxu_set_linktype(priv, NL80211_IFTYPE_STATION);

	/*
	 * Configure initial WMAC settings
	 */
	val32 = RCR_ACCEPT_PHYS_MATCH | RCR_ACCEPT_MCAST | RCR_ACCEPT_BCAST |
		RCR_ACCEPT_MGMT_FRAME | RCR_HTC_LOC_CTRL |
		RCR_APPEND_PHYSTAT | RCR_APPEND_ICV | RCR_APPEND_MIC;
	rtl8xxxu_ग_लिखो32(priv, REG_RCR, val32);

	/*
	 * Accept all multicast
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_MAR, 0xffffffff);
	rtl8xxxu_ग_लिखो32(priv, REG_MAR + 4, 0xffffffff);

	/*
	 * Init adaptive controls
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_RESPONSE_RATE_SET);
	val32 &= ~RESPONSE_RATE_BITMAP_ALL;
	val32 |= RESPONSE_RATE_RRSR_CCK_ONLY_1M;
	rtl8xxxu_ग_लिखो32(priv, REG_RESPONSE_RATE_SET, val32);

	/* CCK = 0x0a, OFDM = 0x10 */
	rtl8xxxu_set_spec_sअगरs(priv, 0x10, 0x10);
	rtl8xxxu_set_retry(priv, 0x30, 0x30);
	rtl8xxxu_set_spec_sअगरs(priv, 0x0a, 0x10);

	/*
	 * Init EDCA
	 */
	rtl8xxxu_ग_लिखो16(priv, REG_MAC_SPEC_SIFS, 0x100a);

	/* Set CCK SIFS */
	rtl8xxxu_ग_लिखो16(priv, REG_SIFS_CCK, 0x100a);

	/* Set OFDM SIFS */
	rtl8xxxu_ग_लिखो16(priv, REG_SIFS_OFDM, 0x100a);

	/* TXOP */
	rtl8xxxu_ग_लिखो32(priv, REG_EDCA_BE_PARAM, 0x005ea42b);
	rtl8xxxu_ग_लिखो32(priv, REG_EDCA_BK_PARAM, 0x0000a44f);
	rtl8xxxu_ग_लिखो32(priv, REG_EDCA_VI_PARAM, 0x005ea324);
	rtl8xxxu_ग_लिखो32(priv, REG_EDCA_VO_PARAM, 0x002fa226);

	/* Set data स्वतः rate fallback retry count */
	rtl8xxxu_ग_लिखो32(priv, REG_DARFRC, 0x00000000);
	rtl8xxxu_ग_लिखो32(priv, REG_DARFRC + 4, 0x10080404);
	rtl8xxxu_ग_लिखो32(priv, REG_RARFRC, 0x04030201);
	rtl8xxxu_ग_लिखो32(priv, REG_RARFRC + 4, 0x08070605);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_FWHW_TXQ_CTRL);
	val8 |= FWHW_TXQ_CTRL_AMPDU_RETRY;
	rtl8xxxu_ग_लिखो8(priv, REG_FWHW_TXQ_CTRL, val8);

	/*  Set ACK समयout */
	rtl8xxxu_ग_लिखो8(priv, REG_ACKTO, 0x40);

	/*
	 * Initialize beacon parameters
	 */
	val16 = BEACON_DISABLE_TSF_UPDATE | (BEACON_DISABLE_TSF_UPDATE << 8);
	rtl8xxxu_ग_लिखो16(priv, REG_BEACON_CTRL, val16);
	rtl8xxxu_ग_लिखो16(priv, REG_TBTT_PROHIBIT, 0x6404);
	rtl8xxxu_ग_लिखो8(priv, REG_DRIVER_EARLY_INT, DRIVER_EARLY_INT_TIME);
	rtl8xxxu_ग_लिखो8(priv, REG_BEACON_DMA_TIME, BEACON_DMA_ATIME_INT_TIME);
	rtl8xxxu_ग_लिखो16(priv, REG_BEACON_TCFG, 0x660F);

	/*
	 * Initialize burst parameters
	 */
	अगर (priv->rtl_chip == RTL8723B) अणु
		/*
		 * For USB high speed set 512B packets
		 */
		val8 = rtl8xxxu_पढ़ो8(priv, REG_RXDMA_PRO_8723B);
		val8 &= ~(BIT(4) | BIT(5));
		val8 |= BIT(4);
		val8 |= BIT(1) | BIT(2) | BIT(3);
		rtl8xxxu_ग_लिखो8(priv, REG_RXDMA_PRO_8723B, val8);

		/*
		 * For USB high speed set 512B packets
		 */
		val8 = rtl8xxxu_पढ़ो8(priv, REG_HT_SINGLE_AMPDU_8723B);
		val8 |= BIT(7);
		rtl8xxxu_ग_लिखो8(priv, REG_HT_SINGLE_AMPDU_8723B, val8);

		rtl8xxxu_ग_लिखो16(priv, REG_MAX_AGGR_NUM, 0x0c14);
		rtl8xxxu_ग_लिखो8(priv, REG_AMPDU_MAX_TIME_8723B, 0x5e);
		rtl8xxxu_ग_लिखो32(priv, REG_AGGLEN_LMT, 0xffffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_RX_PKT_LIMIT, 0x18);
		rtl8xxxu_ग_लिखो8(priv, REG_PIFS, 0x00);
		rtl8xxxu_ग_लिखो8(priv, REG_USTIME_TSF_8723B, 0x50);
		rtl8xxxu_ग_लिखो8(priv, REG_USTIME_EDCA, 0x50);

		val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL);
		val8 |= BIT(5) | BIT(6);
		rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, val8);
	पूर्ण

	अगर (fops->init_aggregation)
		fops->init_aggregation(priv);

	/*
	 * Enable CCK and OFDM block
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
	val32 |= (FPGA_RF_MODE_CCK | FPGA_RF_MODE_OFDM);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);

	/*
	 * Invalidate all CAM entries - bit 30 is unकरोcumented
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_CAM_CMD, CAM_CMD_POLLING | BIT(30));

	/*
	 * Start out with शेष घातer levels क्रम channel 6, 20MHz
	 */
	fops->set_tx_घातer(priv, 1, false);

	/* Let the 8051 take control of antenna setting */
	अगर (priv->rtl_chip != RTL8192E) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_LEDCFG2);
		val8 |= LEDCFG2_DPDT_SELECT;
		rtl8xxxu_ग_लिखो8(priv, REG_LEDCFG2, val8);
	पूर्ण

	rtl8xxxu_ग_लिखो8(priv, REG_HWSEQ_CTRL, 0xff);

	/* Disable BAR - not sure अगर this has any effect on USB */
	rtl8xxxu_ग_लिखो32(priv, REG_BAR_MODE_CTRL, 0x0201ffff);

	rtl8xxxu_ग_लिखो16(priv, REG_FAST_EDCA_CTRL, 0);

	अगर (fops->init_statistics)
		fops->init_statistics(priv);

	अगर (priv->rtl_chip == RTL8192E) अणु
		/*
		 * 0x4c6[3] 1: RTS BW = Data BW
		 * 0: RTS BW depends on CCA / secondary CCA result.
		 */
		val8 = rtl8xxxu_पढ़ो8(priv, REG_QUEUE_CTRL);
		val8 &= ~BIT(3);
		rtl8xxxu_ग_लिखो8(priv, REG_QUEUE_CTRL, val8);
		/*
		 * Reset USB mode चयन setting
		 */
		rtl8xxxu_ग_लिखो8(priv, REG_ACLK_MON, 0x00);
	पूर्ण

	rtl8723a_phy_lc_calibrate(priv);

	fops->phy_iq_calibrate(priv);

	/*
	 * This should enable thermal meter
	 */
	अगर (fops->gen2_thermal_meter)
		rtl8xxxu_ग_लिखो_rfreg(priv,
				     RF_A, RF6052_REG_T_METER_8723B, 0x37cf8);
	अन्यथा
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_T_METER, 0x60);

	/* Set NAV_UPPER to 30000us */
	val8 = ((30000 + NAV_UPPER_UNIT - 1) / NAV_UPPER_UNIT);
	rtl8xxxu_ग_लिखो8(priv, REG_NAV_UPPER, val8);

	अगर (priv->rtl_chip == RTL8723A) अणु
		/*
		 * 2011/03/09 MH debug only, UMC-B cut pass 2500 S5 test,
		 * but we need to find root cause.
		 * This is 8723au only.
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_RF_MODE);
		अगर ((val32 & 0xff000000) != 0x83000000) अणु
			val32 |= FPGA_RF_MODE_CCK;
			rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_RF_MODE, val32);
		पूर्ण
	पूर्ण अन्यथा अगर (priv->rtl_chip == RTL8192E) अणु
		rtl8xxxu_ग_लिखो8(priv, REG_USB_HRPWM, 0x00);
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FWHW_TXQ_CTRL);
	val32 |= FWHW_TXQ_CTRL_XMIT_MGMT_ACK;
	/* ack क्रम xmit mgmt frames. */
	rtl8xxxu_ग_लिखो32(priv, REG_FWHW_TXQ_CTRL, val32);

	अगर (priv->rtl_chip == RTL8192E) अणु
		/*
		 * Fix LDPC rx hang issue.
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_AFE_MISC);
		rtl8xxxu_ग_लिखो8(priv, REG_8192E_LDOV12_CTRL, 0x75);
		val32 &= 0xfff00fff;
		val32 |= 0x0007e000;
		rtl8xxxu_ग_लिखो32(priv, REG_AFE_MISC, val32);
	पूर्ण
निकास:
	वापस ret;
पूर्ण

अटल व्योम rtl8xxxu_cam_ग_लिखो(काष्ठा rtl8xxxu_priv *priv,
			       काष्ठा ieee80211_key_conf *key, स्थिर u8 *mac)
अणु
	u32 cmd, val32, addr, ctrl;
	पूर्णांक j, i, पंचांगp_debug;

	पंचांगp_debug = rtl8xxxu_debug;
	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_KEY)
		rtl8xxxu_debug |= RTL8XXXU_DEBUG_REG_WRITE;

	/*
	 * This is a bit of a hack - the lower bits of the cipher
	 * suite selector happens to match the cipher index in the CAM
	 */
	addr = key->keyidx << CAM_CMD_KEY_SHIFT;
	ctrl = (key->cipher & 0x0f) << 2 | key->keyidx | CAM_WRITE_VALID;

	क्रम (j = 5; j >= 0; j--) अणु
		चयन (j) अणु
		हाल 0:
			val32 = ctrl | (mac[0] << 16) | (mac[1] << 24);
			अवरोध;
		हाल 1:
			val32 = mac[2] | (mac[3] << 8) |
				(mac[4] << 16) | (mac[5] << 24);
			अवरोध;
		शेष:
			i = (j - 2) << 2;
			val32 = key->key[i] | (key->key[i + 1] << 8) |
				key->key[i + 2] << 16 | key->key[i + 3] << 24;
			अवरोध;
		पूर्ण

		rtl8xxxu_ग_लिखो32(priv, REG_CAM_WRITE, val32);
		cmd = CAM_CMD_POLLING | CAM_CMD_WRITE | (addr + j);
		rtl8xxxu_ग_लिखो32(priv, REG_CAM_CMD, cmd);
		udelay(100);
	पूर्ण

	rtl8xxxu_debug = पंचांगp_debug;
पूर्ण

अटल व्योम rtl8xxxu_sw_scan_start(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *mac)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	u8 val8;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_BEACON_CTRL);
	val8 |= BEACON_DISABLE_TSF_UPDATE;
	rtl8xxxu_ग_लिखो8(priv, REG_BEACON_CTRL, val8);
पूर्ण

अटल व्योम rtl8xxxu_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	u8 val8;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_BEACON_CTRL);
	val8 &= ~BEACON_DISABLE_TSF_UPDATE;
	rtl8xxxu_ग_लिखो8(priv, REG_BEACON_CTRL, val8);
पूर्ण

व्योम rtl8xxxu_update_rate_mask(काष्ठा rtl8xxxu_priv *priv,
			       u32 ramask, u8 rateid, पूर्णांक sgi)
अणु
	काष्ठा h2c_cmd h2c;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));

	h2c.ramask.cmd = H2C_SET_RATE_MASK;
	h2c.ramask.mask_lo = cpu_to_le16(ramask & 0xffff);
	h2c.ramask.mask_hi = cpu_to_le16(ramask >> 16);

	h2c.ramask.arg = 0x80;
	अगर (sgi)
		h2c.ramask.arg |= 0x20;

	dev_dbg(&priv->udev->dev, "%s: rate mask %08x, arg %02x, size %zi\n",
		__func__, ramask, h2c.ramask.arg, माप(h2c.ramask));
	rtl8xxxu_gen1_h2c_cmd(priv, &h2c, माप(h2c.ramask));
पूर्ण

व्योम rtl8xxxu_gen2_update_rate_mask(काष्ठा rtl8xxxu_priv *priv,
				    u32 ramask, u8 rateid, पूर्णांक sgi)
अणु
	काष्ठा h2c_cmd h2c;
	u8 bw = RTL8XXXU_CHANNEL_WIDTH_20;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));

	h2c.b_macid_cfg.cmd = H2C_8723B_MACID_CFG_RAID;
	h2c.b_macid_cfg.ramask0 = ramask & 0xff;
	h2c.b_macid_cfg.ramask1 = (ramask >> 8) & 0xff;
	h2c.b_macid_cfg.ramask2 = (ramask >> 16) & 0xff;
	h2c.b_macid_cfg.ramask3 = (ramask >> 24) & 0xff;

	h2c.ramask.arg = 0x80;
	h2c.b_macid_cfg.data1 = rateid;
	अगर (sgi)
		h2c.b_macid_cfg.data1 |= BIT(7);

	h2c.b_macid_cfg.data2 = bw;

	dev_dbg(&priv->udev->dev, "%s: rate mask %08x, arg %02x, size %zi\n",
		__func__, ramask, h2c.ramask.arg, माप(h2c.b_macid_cfg));
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.b_macid_cfg));
पूर्ण

व्योम rtl8xxxu_gen1_report_connect(काष्ठा rtl8xxxu_priv *priv,
				  u8 macid, bool connect)
अणु
	काष्ठा h2c_cmd h2c;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));

	h2c.joinbss.cmd = H2C_JOIN_BSS_REPORT;

	अगर (connect)
		h2c.joinbss.data = H2C_JOIN_BSS_CONNECT;
	अन्यथा
		h2c.joinbss.data = H2C_JOIN_BSS_DISCONNECT;

	rtl8xxxu_gen1_h2c_cmd(priv, &h2c, माप(h2c.joinbss));
पूर्ण

व्योम rtl8xxxu_gen2_report_connect(काष्ठा rtl8xxxu_priv *priv,
				  u8 macid, bool connect)
अणु
#अगर_घोषित RTL8XXXU_GEN2_REPORT_CONNECT
	/*
	 * Barry Day reports this causes issues with 8192eu and 8723bu
	 * devices reconnecting. The reason क्रम this is unclear, but
	 * until it is better understood, leave the code in place but
	 * disabled, so it is not lost.
	 */
	काष्ठा h2c_cmd h2c;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));

	h2c.media_status_rpt.cmd = H2C_8723B_MEDIA_STATUS_RPT;
	अगर (connect)
		h2c.media_status_rpt.parm |= BIT(0);
	अन्यथा
		h2c.media_status_rpt.parm &= ~BIT(0);

	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.media_status_rpt));
#पूर्ण_अगर
पूर्ण

व्योम rtl8xxxu_gen1_init_aggregation(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 agg_ctrl, usb_spec, page_thresh, समयout;

	usb_spec = rtl8xxxu_पढ़ो8(priv, REG_USB_SPECIAL_OPTION);
	usb_spec &= ~USB_SPEC_USB_AGG_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_USB_SPECIAL_OPTION, usb_spec);

	agg_ctrl = rtl8xxxu_पढ़ो8(priv, REG_TRXDMA_CTRL);
	agg_ctrl &= ~TRXDMA_CTRL_RXDMA_AGG_EN;

	अगर (!rtl8xxxu_dma_aggregation) अणु
		rtl8xxxu_ग_लिखो8(priv, REG_TRXDMA_CTRL, agg_ctrl);
		वापस;
	पूर्ण

	agg_ctrl |= TRXDMA_CTRL_RXDMA_AGG_EN;
	rtl8xxxu_ग_लिखो8(priv, REG_TRXDMA_CTRL, agg_ctrl);

	/*
	 * The number of packets we can take looks to be buffer size / 512
	 * which matches the 512 byte rounding we have to करो when de-muxing
	 * the packets.
	 *
	 * Sample numbers from the venकरोr driver:
	 * USB High-Speed mode values:
	 *   RxAggBlockCount = 8 : 512 byte unit
	 *   RxAggBlockTimeout = 6
	 *   RxAggPageCount = 48 : 128 byte unit
	 *   RxAggPageTimeout = 4 or 6 (असलolute समय 34ms/(2^6))
	 */

	page_thresh = (priv->fops->rx_agg_buf_size / 512);
	अगर (rtl8xxxu_dma_agg_pages >= 0) अणु
		अगर (rtl8xxxu_dma_agg_pages <= page_thresh)
			समयout = page_thresh;
		अन्यथा अगर (rtl8xxxu_dma_agg_pages <= 6)
			dev_err(&priv->udev->dev,
				"%s: dma_agg_pages=%i too small, minimum is 6\n",
				__func__, rtl8xxxu_dma_agg_pages);
		अन्यथा
			dev_err(&priv->udev->dev,
				"%s: dma_agg_pages=%i larger than limit %i\n",
				__func__, rtl8xxxu_dma_agg_pages, page_thresh);
	पूर्ण
	rtl8xxxu_ग_लिखो8(priv, REG_RXDMA_AGG_PG_TH, page_thresh);
	/*
	 * REG_RXDMA_AGG_PG_TH + 1 seems to be the समयout रेजिस्टर on
	 * gen2 chips and rtl8188eu. The rtl8723au seems unhappy अगर we
	 * करोn't set it, so better set both.
	 */
	समयout = 4;

	अगर (rtl8xxxu_dma_agg_समयout >= 0) अणु
		अगर (rtl8xxxu_dma_agg_समयout <= 127)
			समयout = rtl8xxxu_dma_agg_समयout;
		अन्यथा
			dev_err(&priv->udev->dev,
				"%s: Invalid dma_agg_timeout: %i\n",
				__func__, rtl8xxxu_dma_agg_समयout);
	पूर्ण

	rtl8xxxu_ग_लिखो8(priv, REG_RXDMA_AGG_PG_TH + 1, समयout);
	rtl8xxxu_ग_लिखो8(priv, REG_USB_DMA_AGG_TO, समयout);
	priv->rx_buf_aggregation = 1;
पूर्ण

अटल व्योम rtl8xxxu_set_basic_rates(काष्ठा rtl8xxxu_priv *priv, u32 rate_cfg)
अणु
	u32 val32;
	u8 rate_idx = 0;

	rate_cfg &= RESPONSE_RATE_BITMAP_ALL;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RESPONSE_RATE_SET);
	val32 &= ~RESPONSE_RATE_BITMAP_ALL;
	val32 |= rate_cfg;
	rtl8xxxu_ग_लिखो32(priv, REG_RESPONSE_RATE_SET, val32);

	dev_dbg(&priv->udev->dev, "%s: rates %08x\n", __func__,	rate_cfg);

	जबतक (rate_cfg) अणु
		rate_cfg = (rate_cfg >> 1);
		rate_idx++;
	पूर्ण
	rtl8xxxu_ग_लिखो8(priv, REG_INIRTS_RATE_SEL, rate_idx);
पूर्ण

अटल u16
rtl8xxxu_wireless_mode(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta)
अणु
	u16 network_type = WIRELESS_MODE_UNKNOWN;

	अगर (hw->conf.chandef.chan->band == NL80211_BAND_5GHZ) अणु
		अगर (sta->vht_cap.vht_supported)
			network_type = WIRELESS_MODE_AC;
		अन्यथा अगर (sta->ht_cap.ht_supported)
			network_type = WIRELESS_MODE_N_5G;

		network_type |= WIRELESS_MODE_A;
	पूर्ण अन्यथा अणु
		अगर (sta->vht_cap.vht_supported)
			network_type = WIRELESS_MODE_AC;
		अन्यथा अगर (sta->ht_cap.ht_supported)
			network_type = WIRELESS_MODE_N_24G;

		अगर (sta->supp_rates[0] <= 0xf)
			network_type |= WIRELESS_MODE_B;
		अन्यथा अगर (sta->supp_rates[0] & 0xf)
			network_type |= (WIRELESS_MODE_B | WIRELESS_MODE_G);
		अन्यथा
			network_type |= WIRELESS_MODE_G;
	पूर्ण

	वापस network_type;
पूर्ण

अटल व्योम
rtl8xxxu_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *bss_conf, u32 changed)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	काष्ठा ieee80211_sta *sta;
	u32 val32;
	u8 val8;

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		dev_dbg(dev, "Changed ASSOC: %i!\n", bss_conf->assoc);

		rtl8xxxu_set_linktype(priv, vअगर->type);

		अगर (bss_conf->assoc) अणु
			u32 ramask;
			पूर्णांक sgi = 0;

			rcu_पढ़ो_lock();
			sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
			अगर (!sta) अणु
				dev_info(dev, "%s: ASSOC no sta found\n",
					 __func__);
				rcu_पढ़ो_unlock();
				जाओ error;
			पूर्ण

			अगर (sta->ht_cap.ht_supported)
				dev_info(dev, "%s: HT supported\n", __func__);
			अगर (sta->vht_cap.vht_supported)
				dev_info(dev, "%s: VHT supported\n", __func__);

			/* TODO: Set bits 28-31 क्रम rate adaptive id */
			ramask = (sta->supp_rates[0] & 0xfff) |
				sta->ht_cap.mcs.rx_mask[0] << 12 |
				sta->ht_cap.mcs.rx_mask[1] << 20;
			अगर (sta->ht_cap.cap &
			    (IEEE80211_HT_CAP_SGI_40 | IEEE80211_HT_CAP_SGI_20))
				sgi = 1;
			rcu_पढ़ो_unlock();

			priv->vअगर = vअगर;
			priv->rssi_level = RTL8XXXU_RATR_STA_INIT;

			priv->fops->update_rate_mask(priv, ramask, 0, sgi);

			rtl8xxxu_ग_लिखो8(priv, REG_BCN_MAX_ERR, 0xff);

			rtl8xxxu_stop_tx_beacon(priv);

			/* joinbss sequence */
			rtl8xxxu_ग_लिखो16(priv, REG_BCN_PSR_RPT,
					 0xc000 | bss_conf->aid);

			priv->fops->report_connect(priv, 0, true);
		पूर्ण अन्यथा अणु
			val8 = rtl8xxxu_पढ़ो8(priv, REG_BEACON_CTRL);
			val8 |= BEACON_DISABLE_TSF_UPDATE;
			rtl8xxxu_ग_लिखो8(priv, REG_BEACON_CTRL, val8);

			priv->fops->report_connect(priv, 0, false);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		dev_dbg(dev, "Changed ERP_PREAMBLE: Use short preamble %i\n",
			bss_conf->use_लघु_preamble);
		val32 = rtl8xxxu_पढ़ो32(priv, REG_RESPONSE_RATE_SET);
		अगर (bss_conf->use_लघु_preamble)
			val32 |= RSR_ACK_SHORT_PREAMBLE;
		अन्यथा
			val32 &= ~RSR_ACK_SHORT_PREAMBLE;
		rtl8xxxu_ग_लिखो32(priv, REG_RESPONSE_RATE_SET, val32);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		dev_dbg(dev, "Changed ERP_SLOT: short_slot_time %i\n",
			bss_conf->use_लघु_slot);

		अगर (bss_conf->use_लघु_slot)
			val8 = 9;
		अन्यथा
			val8 = 20;
		rtl8xxxu_ग_लिखो8(priv, REG_SLOT, val8);
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		dev_dbg(dev, "Changed BSSID!\n");
		rtl8xxxu_set_bssid(priv, bss_conf->bssid);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		dev_dbg(dev, "Changed BASIC_RATES!\n");
		rtl8xxxu_set_basic_rates(priv, bss_conf->basic_rates);
	पूर्ण
error:
	वापस;
पूर्ण

अटल u32 rtl8xxxu_80211_to_rtl_queue(u32 queue)
अणु
	u32 rtlqueue;

	चयन (queue) अणु
	हाल IEEE80211_AC_VO:
		rtlqueue = TXDESC_QUEUE_VO;
		अवरोध;
	हाल IEEE80211_AC_VI:
		rtlqueue = TXDESC_QUEUE_VI;
		अवरोध;
	हाल IEEE80211_AC_BE:
		rtlqueue = TXDESC_QUEUE_BE;
		अवरोध;
	हाल IEEE80211_AC_BK:
		rtlqueue = TXDESC_QUEUE_BK;
		अवरोध;
	शेष:
		rtlqueue = TXDESC_QUEUE_BE;
	पूर्ण

	वापस rtlqueue;
पूर्ण

अटल u32 rtl8xxxu_queue_select(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	u32 queue;

	अगर (ieee80211_is_mgmt(hdr->frame_control))
		queue = TXDESC_QUEUE_MGNT;
	अन्यथा
		queue = rtl8xxxu_80211_to_rtl_queue(skb_get_queue_mapping(skb));

	वापस queue;
पूर्ण

/*
 * Despite newer chips 8723b/8812/8821 having a larger TX descriptor
 * क्रमmat. The descriptor checksum is still only calculated over the
 * initial 32 bytes of the descriptor!
 */
अटल व्योम rtl8xxxu_calc_tx_desc_csum(काष्ठा rtl8xxxu_txdesc32 *tx_desc)
अणु
	__le16 *ptr = (__le16 *)tx_desc;
	u16 csum = 0;
	पूर्णांक i;

	/*
	 * Clear csum field beक्रमe calculation, as the csum field is
	 * in the middle of the काष्ठा.
	 */
	tx_desc->csum = cpu_to_le16(0);

	क्रम (i = 0; i < (माप(काष्ठा rtl8xxxu_txdesc32) / माप(u16)); i++)
		csum = csum ^ le16_to_cpu(ptr[i]);

	tx_desc->csum |= cpu_to_le16(csum);
पूर्ण

अटल व्योम rtl8xxxu_मुक्त_tx_resources(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_tx_urb *tx_urb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->tx_urb_lock, flags);
	list_क्रम_each_entry_safe(tx_urb, पंचांगp, &priv->tx_urb_मुक्त_list, list) अणु
		list_del(&tx_urb->list);
		priv->tx_urb_मुक्त_count--;
		usb_मुक्त_urb(&tx_urb->urb);
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_urb_lock, flags);
पूर्ण

अटल काष्ठा rtl8xxxu_tx_urb *
rtl8xxxu_alloc_tx_urb(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_tx_urb *tx_urb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->tx_urb_lock, flags);
	tx_urb = list_first_entry_or_null(&priv->tx_urb_मुक्त_list,
					  काष्ठा rtl8xxxu_tx_urb, list);
	अगर (tx_urb) अणु
		list_del(&tx_urb->list);
		priv->tx_urb_मुक्त_count--;
		अगर (priv->tx_urb_मुक्त_count < RTL8XXXU_TX_URB_LOW_WATER &&
		    !priv->tx_stopped) अणु
			priv->tx_stopped = true;
			ieee80211_stop_queues(priv->hw);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_urb_lock, flags);

	वापस tx_urb;
पूर्ण

अटल व्योम rtl8xxxu_मुक्त_tx_urb(काष्ठा rtl8xxxu_priv *priv,
				 काष्ठा rtl8xxxu_tx_urb *tx_urb)
अणु
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&tx_urb->list);

	spin_lock_irqsave(&priv->tx_urb_lock, flags);

	list_add(&tx_urb->list, &priv->tx_urb_मुक्त_list);
	priv->tx_urb_मुक्त_count++;
	अगर (priv->tx_urb_मुक्त_count > RTL8XXXU_TX_URB_HIGH_WATER &&
	    priv->tx_stopped) अणु
		priv->tx_stopped = false;
		ieee80211_wake_queues(priv->hw);
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_urb_lock, flags);
पूर्ण

अटल व्योम rtl8xxxu_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_hw *hw;
	काष्ठा rtl8xxxu_priv *priv;
	काष्ठा rtl8xxxu_tx_urb *tx_urb =
		container_of(urb, काष्ठा rtl8xxxu_tx_urb, urb);

	tx_info = IEEE80211_SKB_CB(skb);
	hw = tx_info->rate_driver_data[0];
	priv = hw->priv;

	skb_pull(skb, priv->fops->tx_desc_size);

	ieee80211_tx_info_clear_status(tx_info);
	tx_info->status.rates[0].idx = -1;
	tx_info->status.rates[0].count = 0;

	अगर (!urb->status)
		tx_info->flags |= IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_irqsafe(hw, skb);

	rtl8xxxu_मुक्त_tx_urb(priv, tx_urb);
पूर्ण

अटल व्योम rtl8xxxu_dump_action(काष्ठा device *dev,
				 काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)hdr;
	u16 cap, समयout;

	अगर (!(rtl8xxxu_debug & RTL8XXXU_DEBUG_ACTION))
		वापस;

	चयन (mgmt->u.action.u.addba_resp.action_code) अणु
	हाल WLAN_ACTION_ADDBA_RESP:
		cap = le16_to_cpu(mgmt->u.action.u.addba_resp.capab);
		समयout = le16_to_cpu(mgmt->u.action.u.addba_resp.समयout);
		dev_info(dev, "WLAN_ACTION_ADDBA_RESP: "
			 "timeout %i, tid %02x, buf_size %02x, policy %02x, "
			 "status %02x\n",
			 समयout,
			 (cap & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2,
			 (cap & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6,
			 (cap >> 1) & 0x1,
			 le16_to_cpu(mgmt->u.action.u.addba_resp.status));
		अवरोध;
	हाल WLAN_ACTION_ADDBA_REQ:
		cap = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
		समयout = le16_to_cpu(mgmt->u.action.u.addba_req.समयout);
		dev_info(dev, "WLAN_ACTION_ADDBA_REQ: "
			 "timeout %i, tid %02x, buf_size %02x, policy %02x\n",
			 समयout,
			 (cap & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2,
			 (cap & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6,
			 (cap >> 1) & 0x1);
		अवरोध;
	शेष:
		dev_info(dev, "action frame %02x\n",
			 mgmt->u.action.u.addba_resp.action_code);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Fill in v1 (gen1) specअगरic TX descriptor bits.
 * This क्रमmat is used on 8188cu/8192cu/8723au
 */
व्योम
rtl8xxxu_fill_txdesc_v1(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *hdr,
			काष्ठा ieee80211_tx_info *tx_info,
			काष्ठा rtl8xxxu_txdesc32 *tx_desc, bool sgi,
			bool लघु_preamble, bool ampdu_enable, u32 rts_rate)
अणु
	काष्ठा ieee80211_rate *tx_rate = ieee80211_get_tx_rate(hw, tx_info);
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	u32 rate;
	u16 rate_flags = tx_info->control.rates[0].flags;
	u16 seq_number;

	अगर (rate_flags & IEEE80211_TX_RC_MCS &&
	    !ieee80211_is_mgmt(hdr->frame_control))
		rate = tx_info->control.rates[0].idx + DESC_RATE_MCS0;
	अन्यथा
		rate = tx_rate->hw_value;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_TX)
		dev_info(dev, "%s: TX rate: %d, pkt size %u\n",
			 __func__, rate, le16_to_cpu(tx_desc->pkt_size));

	seq_number = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));

	tx_desc->txdw5 = cpu_to_le32(rate);

	अगर (ieee80211_is_data(hdr->frame_control))
		tx_desc->txdw5 |= cpu_to_le32(0x0001ff00);

	tx_desc->txdw3 = cpu_to_le32((u32)seq_number << TXDESC32_SEQ_SHIFT);

	अगर (ampdu_enable)
		tx_desc->txdw1 |= cpu_to_le32(TXDESC32_AGG_ENABLE);
	अन्यथा
		tx_desc->txdw1 |= cpu_to_le32(TXDESC32_AGG_BREAK);

	अगर (ieee80211_is_mgmt(hdr->frame_control)) अणु
		tx_desc->txdw5 = cpu_to_le32(rate);
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_USE_DRIVER_RATE);
		tx_desc->txdw5 |= cpu_to_le32(6 << TXDESC32_RETRY_LIMIT_SHIFT);
		tx_desc->txdw5 |= cpu_to_le32(TXDESC32_RETRY_LIMIT_ENABLE);
	पूर्ण

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_QOS);

	अगर (लघु_preamble)
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_SHORT_PREAMBLE);

	अगर (sgi)
		tx_desc->txdw5 |= cpu_to_le32(TXDESC32_SHORT_GI);

	/*
	 * rts_rate is zero अगर RTS/CTS or CTS to SELF are not enabled
	 */
	tx_desc->txdw4 |= cpu_to_le32(rts_rate << TXDESC32_RTS_RATE_SHIFT);
	अगर (rate_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_RTS_CTS_ENABLE);
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_HW_RTS_ENABLE);
	पूर्ण अन्यथा अगर (rate_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_CTS_SELF_ENABLE);
		tx_desc->txdw4 |= cpu_to_le32(TXDESC32_HW_RTS_ENABLE);
	पूर्ण
पूर्ण

/*
 * Fill in v2 (gen2) specअगरic TX descriptor bits.
 * This क्रमmat is used on 8192eu/8723bu
 */
व्योम
rtl8xxxu_fill_txdesc_v2(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *hdr,
			काष्ठा ieee80211_tx_info *tx_info,
			काष्ठा rtl8xxxu_txdesc32 *tx_desc32, bool sgi,
			bool लघु_preamble, bool ampdu_enable, u32 rts_rate)
अणु
	काष्ठा ieee80211_rate *tx_rate = ieee80211_get_tx_rate(hw, tx_info);
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	काष्ठा rtl8xxxu_txdesc40 *tx_desc40;
	u32 rate;
	u16 rate_flags = tx_info->control.rates[0].flags;
	u16 seq_number;

	tx_desc40 = (काष्ठा rtl8xxxu_txdesc40 *)tx_desc32;

	अगर (rate_flags & IEEE80211_TX_RC_MCS &&
	    !ieee80211_is_mgmt(hdr->frame_control))
		rate = tx_info->control.rates[0].idx + DESC_RATE_MCS0;
	अन्यथा
		rate = tx_rate->hw_value;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_TX)
		dev_info(dev, "%s: TX rate: %d, pkt size %u\n",
			 __func__, rate, le16_to_cpu(tx_desc40->pkt_size));

	seq_number = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));

	tx_desc40->txdw4 = cpu_to_le32(rate);
	अगर (ieee80211_is_data(hdr->frame_control)) अणु
		tx_desc40->txdw4 |= cpu_to_le32(0x1f <<
						TXDESC40_DATA_RATE_FB_SHIFT);
	पूर्ण

	tx_desc40->txdw9 = cpu_to_le32((u32)seq_number << TXDESC40_SEQ_SHIFT);

	अगर (ampdu_enable)
		tx_desc40->txdw2 |= cpu_to_le32(TXDESC40_AGG_ENABLE);
	अन्यथा
		tx_desc40->txdw2 |= cpu_to_le32(TXDESC40_AGG_BREAK);

	अगर (ieee80211_is_mgmt(hdr->frame_control)) अणु
		tx_desc40->txdw4 = cpu_to_le32(rate);
		tx_desc40->txdw3 |= cpu_to_le32(TXDESC40_USE_DRIVER_RATE);
		tx_desc40->txdw4 |=
			cpu_to_le32(6 << TXDESC40_RETRY_LIMIT_SHIFT);
		tx_desc40->txdw4 |= cpu_to_le32(TXDESC40_RETRY_LIMIT_ENABLE);
	पूर्ण

	अगर (लघु_preamble)
		tx_desc40->txdw5 |= cpu_to_le32(TXDESC40_SHORT_PREAMBLE);

	tx_desc40->txdw4 |= cpu_to_le32(rts_rate << TXDESC40_RTS_RATE_SHIFT);
	/*
	 * rts_rate is zero अगर RTS/CTS or CTS to SELF are not enabled
	 */
	अगर (rate_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		tx_desc40->txdw3 |= cpu_to_le32(TXDESC40_RTS_CTS_ENABLE);
		tx_desc40->txdw3 |= cpu_to_le32(TXDESC40_HW_RTS_ENABLE);
	पूर्ण अन्यथा अगर (rate_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		/*
		 * For some reason the venकरोr driver करोesn't set
		 * TXDESC40_HW_RTS_ENABLE क्रम CTS to SELF
		 */
		tx_desc40->txdw3 |= cpu_to_le32(TXDESC40_CTS_SELF_ENABLE);
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_tx(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_tx_control *control,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा rtl8xxxu_txdesc32 *tx_desc;
	काष्ठा rtl8xxxu_tx_urb *tx_urb;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा ieee80211_vअगर *vअगर = tx_info->control.vअगर;
	काष्ठा device *dev = &priv->udev->dev;
	u32 queue, rts_rate;
	u16 pktlen = skb->len;
	u16 rate_flag = tx_info->control.rates[0].flags;
	पूर्णांक tx_desc_size = priv->fops->tx_desc_size;
	पूर्णांक ret;
	bool ampdu_enable, sgi = false, लघु_preamble = false;

	अगर (skb_headroom(skb) < tx_desc_size) अणु
		dev_warn(dev,
			 "%s: Not enough headroom (%i) for tx descriptor\n",
			 __func__, skb_headroom(skb));
		जाओ error;
	पूर्ण

	अगर (unlikely(skb->len > (65535 - tx_desc_size))) अणु
		dev_warn(dev, "%s: Trying to send over-sized skb (%i)\n",
			 __func__, skb->len);
		जाओ error;
	पूर्ण

	tx_urb = rtl8xxxu_alloc_tx_urb(priv);
	अगर (!tx_urb) अणु
		dev_warn(dev, "%s: Unable to allocate tx urb\n", __func__);
		जाओ error;
	पूर्ण

	अगर (ieee80211_is_action(hdr->frame_control))
		rtl8xxxu_dump_action(dev, hdr);

	tx_info->rate_driver_data[0] = hw;

	अगर (control && control->sta)
		sta = control->sta;

	tx_desc = skb_push(skb, tx_desc_size);

	स_रखो(tx_desc, 0, tx_desc_size);
	tx_desc->pkt_size = cpu_to_le16(pktlen);
	tx_desc->pkt_offset = tx_desc_size;

	tx_desc->txdw0 =
		TXDESC_OWN | TXDESC_FIRST_SEGMENT | TXDESC_LAST_SEGMENT;
	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr)))
		tx_desc->txdw0 |= TXDESC_BROADMULTICAST;

	queue = rtl8xxxu_queue_select(hw, skb);
	tx_desc->txdw1 = cpu_to_le32(queue << TXDESC_QUEUE_SHIFT);

	अगर (tx_info->control.hw_key) अणु
		चयन (tx_info->control.hw_key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			tx_desc->txdw1 |= cpu_to_le32(TXDESC_SEC_RC4);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			tx_desc->txdw1 |= cpu_to_le32(TXDESC_SEC_AES);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* (tx_info->flags & IEEE80211_TX_CTL_AMPDU) && */
	ampdu_enable = false;
	अगर (ieee80211_is_data_qos(hdr->frame_control) && sta) अणु
		अगर (sta->ht_cap.ht_supported) अणु
			u32 ampdu, val32;

			ampdu = (u32)sta->ht_cap.ampdu_density;
			val32 = ampdu << TXDESC_AMPDU_DENSITY_SHIFT;
			tx_desc->txdw2 |= cpu_to_le32(val32);

			ampdu_enable = true;
		पूर्ण
	पूर्ण

	अगर (rate_flag & IEEE80211_TX_RC_SHORT_GI ||
	    (ieee80211_is_data_qos(hdr->frame_control) &&
	     sta && sta->ht_cap.cap &
	     (IEEE80211_HT_CAP_SGI_40 | IEEE80211_HT_CAP_SGI_20)))
		sgi = true;

	अगर (rate_flag & IEEE80211_TX_RC_USE_SHORT_PREAMBLE ||
	    (sta && vअगर && vअगर->bss_conf.use_लघु_preamble))
		लघु_preamble = true;

	अगर (rate_flag & IEEE80211_TX_RC_USE_RTS_CTS)
		rts_rate = ieee80211_get_rts_cts_rate(hw, tx_info)->hw_value;
	अन्यथा अगर (rate_flag & IEEE80211_TX_RC_USE_CTS_PROTECT)
		rts_rate = ieee80211_get_rts_cts_rate(hw, tx_info)->hw_value;
	अन्यथा
		rts_rate = 0;


	priv->fops->fill_txdesc(hw, hdr, tx_info, tx_desc, sgi, लघु_preamble,
				ampdu_enable, rts_rate);

	rtl8xxxu_calc_tx_desc_csum(tx_desc);

	usb_fill_bulk_urb(&tx_urb->urb, priv->udev, priv->pipe_out[queue],
			  skb->data, skb->len, rtl8xxxu_tx_complete, skb);

	usb_anchor_urb(&tx_urb->urb, &priv->tx_anchor);
	ret = usb_submit_urb(&tx_urb->urb, GFP_ATOMIC);
	अगर (ret) अणु
		usb_unanchor_urb(&tx_urb->urb);
		rtl8xxxu_मुक्त_tx_urb(priv, tx_urb);
		जाओ error;
	पूर्ण
	वापस;
error:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम rtl8xxxu_rx_parse_phystats(काष्ठा rtl8xxxu_priv *priv,
				       काष्ठा ieee80211_rx_status *rx_status,
				       काष्ठा rtl8723au_phy_stats *phy_stats,
				       u32 rxmcs)
अणु
	अगर (phy_stats->sgi_en)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (rxmcs < DESC_RATE_6M) अणु
		/*
		 * Handle PHY stats क्रम CCK rates
		 */
		u8 cck_agc_rpt = phy_stats->cck_agc_rpt_ofdm_cfosho_a;

		चयन (cck_agc_rpt & 0xc0) अणु
		हाल 0xc0:
			rx_status->संकेत = -46 - (cck_agc_rpt & 0x3e);
			अवरोध;
		हाल 0x80:
			rx_status->संकेत = -26 - (cck_agc_rpt & 0x3e);
			अवरोध;
		हाल 0x40:
			rx_status->संकेत = -12 - (cck_agc_rpt & 0x3e);
			अवरोध;
		हाल 0x00:
			rx_status->संकेत = 16 - (cck_agc_rpt & 0x3e);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rx_status->संकेत =
			(phy_stats->cck_sig_qual_ofdm_pwdb_all >> 1) - 110;
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_मुक्त_rx_resources(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_rx_urb *rx_urb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->rx_urb_lock, flags);

	list_क्रम_each_entry_safe(rx_urb, पंचांगp,
				 &priv->rx_urb_pending_list, list) अणु
		list_del(&rx_urb->list);
		priv->rx_urb_pending_count--;
		usb_मुक्त_urb(&rx_urb->urb);
	पूर्ण

	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);
पूर्ण

अटल व्योम rtl8xxxu_queue_rx_urb(काष्ठा rtl8xxxu_priv *priv,
				  काष्ठा rtl8xxxu_rx_urb *rx_urb)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक pending = 0;

	spin_lock_irqsave(&priv->rx_urb_lock, flags);

	अगर (!priv->shutकरोwn) अणु
		list_add_tail(&rx_urb->list, &priv->rx_urb_pending_list);
		priv->rx_urb_pending_count++;
		pending = priv->rx_urb_pending_count;
	पूर्ण अन्यथा अणु
		skb = (काष्ठा sk_buff *)rx_urb->urb.context;
		dev_kमुक्त_skb(skb);
		usb_मुक्त_urb(&rx_urb->urb);
	पूर्ण

	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	अगर (pending > RTL8XXXU_RX_URB_PENDING_WATER)
		schedule_work(&priv->rx_urb_wq);
पूर्ण

अटल व्योम rtl8xxxu_rx_urb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8xxxu_priv *priv;
	काष्ठा rtl8xxxu_rx_urb *rx_urb, *पंचांगp;
	काष्ठा list_head local;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	priv = container_of(work, काष्ठा rtl8xxxu_priv, rx_urb_wq);
	INIT_LIST_HEAD(&local);

	spin_lock_irqsave(&priv->rx_urb_lock, flags);

	list_splice_init(&priv->rx_urb_pending_list, &local);
	priv->rx_urb_pending_count = 0;

	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	list_क्रम_each_entry_safe(rx_urb, पंचांगp, &local, list) अणु
		list_del_init(&rx_urb->list);
		ret = rtl8xxxu_submit_rx_urb(priv, rx_urb);
		/*
		 * If out of memory or temporary error, put it back on the
		 * queue and try again. Otherwise the device is dead/gone
		 * and we should drop it.
		 */
		चयन (ret) अणु
		हाल 0:
			अवरोध;
		हाल -ENOMEM:
		हाल -EAGAIN:
			rtl8xxxu_queue_rx_urb(priv, rx_urb);
			अवरोध;
		शेष:
			pr_info("failed to requeue urb %i\n", ret);
			skb = (काष्ठा sk_buff *)rx_urb->urb.context;
			dev_kमुक्त_skb(skb);
			usb_मुक्त_urb(&rx_urb->urb);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The RTL8723BU/RTL8192EU venकरोr driver use coexistence table type
 * 0-7 to represent writing dअगरferent combinations of रेजिस्टर values
 * to REG_BT_COEX_TABLEs. It's क्रम dअगरferent kinds of coexistence use
 * हालs which Realtek करोesn't provide detail क्रम these settings. Keep
 * this aligned with venकरोr driver क्रम easier मुख्यtenance.
 */
अटल
व्योम rtl8723bu_set_coex_with_type(काष्ठा rtl8xxxu_priv *priv, u8 type)
अणु
	चयन (type) अणु
	हाल 0:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x55555555);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0x55555555);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 1:
	हाल 3:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x55555555);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0x5a5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 2:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x5a5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0x5a5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 4:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x5a5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0xaaaa5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 5:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x5a5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0xaa5a5a5a);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 6:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x55555555);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0xaaaaaaaa);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	हाल 7:
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0xaaaaaaaa);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0xaaaaaaaa);
		rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
		rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम rtl8723bu_update_bt_link_info(काष्ठा rtl8xxxu_priv *priv, u8 bt_info)
अणु
	काष्ठा rtl8xxxu_btcoex *btcoex = &priv->bt_coex;

	अगर (bt_info & BT_INFO_8723B_1ANT_B_INQ_PAGE)
		btcoex->c2h_bt_inquiry = true;
	अन्यथा
		btcoex->c2h_bt_inquiry = false;

	अगर (!(bt_info & BT_INFO_8723B_1ANT_B_CONNECTION)) अणु
		btcoex->bt_status = BT_8723B_1ANT_STATUS_NON_CONNECTED_IDLE;
		btcoex->has_sco = false;
		btcoex->has_hid = false;
		btcoex->has_pan = false;
		btcoex->has_a2dp = false;
	पूर्ण अन्यथा अणु
		अगर ((bt_info & 0x1f) == BT_INFO_8723B_1ANT_B_CONNECTION)
			btcoex->bt_status = BT_8723B_1ANT_STATUS_CONNECTED_IDLE;
		अन्यथा अगर ((bt_info & BT_INFO_8723B_1ANT_B_SCO_ESCO) ||
			 (bt_info & BT_INFO_8723B_1ANT_B_SCO_BUSY))
			btcoex->bt_status = BT_8723B_1ANT_STATUS_SCO_BUSY;
		अन्यथा अगर (bt_info & BT_INFO_8723B_1ANT_B_ACL_BUSY)
			btcoex->bt_status = BT_8723B_1ANT_STATUS_ACL_BUSY;
		अन्यथा
			btcoex->bt_status = BT_8723B_1ANT_STATUS_MAX;

		अगर (bt_info & BT_INFO_8723B_1ANT_B_FTP)
			btcoex->has_pan = true;
		अन्यथा
			btcoex->has_pan = false;

		अगर (bt_info & BT_INFO_8723B_1ANT_B_A2DP)
			btcoex->has_a2dp = true;
		अन्यथा
			btcoex->has_a2dp = false;

		अगर (bt_info & BT_INFO_8723B_1ANT_B_HID)
			btcoex->has_hid = true;
		अन्यथा
			btcoex->has_hid = false;

		अगर (bt_info & BT_INFO_8723B_1ANT_B_SCO_ESCO)
			btcoex->has_sco = true;
		अन्यथा
			btcoex->has_sco = false;
	पूर्ण

	अगर (!btcoex->has_a2dp && !btcoex->has_sco &&
	    !btcoex->has_pan && btcoex->has_hid)
		btcoex->hid_only = true;
	अन्यथा
		btcoex->hid_only = false;

	अगर (!btcoex->has_sco && !btcoex->has_pan &&
	    !btcoex->has_hid && btcoex->has_a2dp)
		btcoex->has_a2dp = true;
	अन्यथा
		btcoex->has_a2dp = false;

	अगर (btcoex->bt_status == BT_8723B_1ANT_STATUS_SCO_BUSY ||
	    btcoex->bt_status == BT_8723B_1ANT_STATUS_ACL_BUSY)
		btcoex->bt_busy = true;
	अन्यथा
		btcoex->bt_busy = false;
पूर्ण

अटल
व्योम rtl8723bu_handle_bt_inquiry(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा rtl8xxxu_btcoex *btcoex;
	bool wअगरi_connected;

	vअगर = priv->vअगर;
	btcoex = &priv->bt_coex;
	wअगरi_connected = (vअगर && vअगर->bss_conf.assoc);

	अगर (!wअगरi_connected) अणु
		rtl8723bu_set_ps_tdma(priv, 0x8, 0x0, 0x0, 0x0, 0x0);
		rtl8723bu_set_coex_with_type(priv, 0);
	पूर्ण अन्यथा अगर (btcoex->has_sco || btcoex->has_hid || btcoex->has_a2dp) अणु
		rtl8723bu_set_ps_tdma(priv, 0x61, 0x35, 0x3, 0x11, 0x11);
		rtl8723bu_set_coex_with_type(priv, 4);
	पूर्ण अन्यथा अगर (btcoex->has_pan) अणु
		rtl8723bu_set_ps_tdma(priv, 0x61, 0x3f, 0x3, 0x11, 0x11);
		rtl8723bu_set_coex_with_type(priv, 4);
	पूर्ण अन्यथा अणु
		rtl8723bu_set_ps_tdma(priv, 0x8, 0x0, 0x0, 0x0, 0x0);
		rtl8723bu_set_coex_with_type(priv, 7);
	पूर्ण
पूर्ण

अटल
व्योम rtl8723bu_handle_bt_info(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा rtl8xxxu_btcoex *btcoex;
	bool wअगरi_connected;

	vअगर = priv->vअगर;
	btcoex = &priv->bt_coex;
	wअगरi_connected = (vअगर && vअगर->bss_conf.assoc);

	अगर (wअगरi_connected) अणु
		u32 val32 = 0;
		u32 high_prio_tx = 0, high_prio_rx = 0;

		val32 = rtl8xxxu_पढ़ो32(priv, 0x770);
		high_prio_tx = val32 & 0x0000ffff;
		high_prio_rx = (val32  & 0xffff0000) >> 16;

		अगर (btcoex->bt_busy) अणु
			अगर (btcoex->hid_only) अणु
				rtl8723bu_set_ps_tdma(priv, 0x61, 0x20,
						      0x3, 0x11, 0x11);
				rtl8723bu_set_coex_with_type(priv, 5);
			पूर्ण अन्यथा अगर (btcoex->a2dp_only) अणु
				rtl8723bu_set_ps_tdma(priv, 0x61, 0x35,
						      0x3, 0x11, 0x11);
				rtl8723bu_set_coex_with_type(priv, 4);
			पूर्ण अन्यथा अगर ((btcoex->has_a2dp && btcoex->has_pan) ||
				   (btcoex->has_hid && btcoex->has_a2dp &&
				    btcoex->has_pan)) अणु
				rtl8723bu_set_ps_tdma(priv, 0x51, 0x21,
						      0x3, 0x10, 0x10);
				rtl8723bu_set_coex_with_type(priv, 4);
			पूर्ण अन्यथा अगर (btcoex->has_hid && btcoex->has_a2dp) अणु
				rtl8723bu_set_ps_tdma(priv, 0x51, 0x21,
						      0x3, 0x10, 0x10);
				rtl8723bu_set_coex_with_type(priv, 3);
			पूर्ण अन्यथा अणु
				rtl8723bu_set_ps_tdma(priv, 0x61, 0x35,
						      0x3, 0x11, 0x11);
				rtl8723bu_set_coex_with_type(priv, 4);
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl8723bu_set_ps_tdma(priv, 0x8, 0x0, 0x0, 0x0, 0x0);
			अगर (high_prio_tx + high_prio_rx <= 60)
				rtl8723bu_set_coex_with_type(priv, 2);
			अन्यथा
				rtl8723bu_set_coex_with_type(priv, 7);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl8723bu_set_ps_tdma(priv, 0x8, 0x0, 0x0, 0x0, 0x0);
		rtl8723bu_set_coex_with_type(priv, 0);
	पूर्ण
पूर्ण

अटल काष्ठा ieee80211_rate rtl8xxxu_legacy_ratetable[] = अणु
	अणु.bitrate = 10, .hw_value = 0x00,पूर्ण,
	अणु.bitrate = 20, .hw_value = 0x01,पूर्ण,
	अणु.bitrate = 55, .hw_value = 0x02,पूर्ण,
	अणु.bitrate = 110, .hw_value = 0x03,पूर्ण,
	अणु.bitrate = 60, .hw_value = 0x04,पूर्ण,
	अणु.bitrate = 90, .hw_value = 0x05,पूर्ण,
	अणु.bitrate = 120, .hw_value = 0x06,पूर्ण,
	अणु.bitrate = 180, .hw_value = 0x07,पूर्ण,
	अणु.bitrate = 240, .hw_value = 0x08,पूर्ण,
	अणु.bitrate = 360, .hw_value = 0x09,पूर्ण,
	अणु.bitrate = 480, .hw_value = 0x0a,पूर्ण,
	अणु.bitrate = 540, .hw_value = 0x0b,पूर्ण,
पूर्ण;

अटल व्योम rtl8xxxu_desc_to_mcsrate(u16 rate, u8 *mcs, u8 *nss)
अणु
	अगर (rate <= DESC_RATE_54M)
		वापस;

	अगर (rate >= DESC_RATE_MCS0 && rate <= DESC_RATE_MCS15) अणु
		अगर (rate < DESC_RATE_MCS8)
			*nss = 1;
		अन्यथा
			*nss = 2;
		*mcs = rate - DESC_RATE_MCS0;
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_c2hcmd_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl8xxxu_priv *priv;
	काष्ठा rtl8723bu_c2h *c2h;
	काष्ठा sk_buff *skb = शून्य;
	u8 bt_info = 0;
	काष्ठा rtl8xxxu_btcoex *btcoex;
	काष्ठा rtl8xxxu_ra_report *rarpt;
	u8 rate, sgi, bw;
	u32 bit_rate;
	u8 mcs = 0, nss = 0;

	priv = container_of(work, काष्ठा rtl8xxxu_priv, c2hcmd_work);
	btcoex = &priv->bt_coex;
	rarpt = &priv->ra_report;

	अगर (priv->rf_paths > 1)
		जाओ out;

	जबतक (!skb_queue_empty(&priv->c2hcmd_queue)) अणु
		skb = skb_dequeue(&priv->c2hcmd_queue);

		c2h = (काष्ठा rtl8723bu_c2h *)skb->data;

		चयन (c2h->id) अणु
		हाल C2H_8723B_BT_INFO:
			bt_info = c2h->bt_info.bt_info;

			rtl8723bu_update_bt_link_info(priv, bt_info);
			अगर (btcoex->c2h_bt_inquiry) अणु
				rtl8723bu_handle_bt_inquiry(priv);
				अवरोध;
			पूर्ण
			rtl8723bu_handle_bt_info(priv);
			अवरोध;
		हाल C2H_8723B_RA_REPORT:
			rarpt->txrate.flags = 0;
			rate = c2h->ra_report.rate;
			sgi = c2h->ra_report.sgi;
			bw = c2h->ra_report.bw;

			अगर (rate < DESC_RATE_MCS0) अणु
				rarpt->txrate.legacy =
					rtl8xxxu_legacy_ratetable[rate].bitrate;
			पूर्ण अन्यथा अणु
				rtl8xxxu_desc_to_mcsrate(rate, &mcs, &nss);
				rarpt->txrate.flags |= RATE_INFO_FLAGS_MCS;

				rarpt->txrate.mcs = mcs;
				rarpt->txrate.nss = nss;

				अगर (sgi) अणु
					rarpt->txrate.flags |=
						RATE_INFO_FLAGS_SHORT_GI;
				पूर्ण

				अगर (bw == RATE_INFO_BW_20)
					rarpt->txrate.bw |= RATE_INFO_BW_20;
			पूर्ण
			bit_rate = cfg80211_calculate_bitrate(&rarpt->txrate);
			rarpt->bit_rate = bit_rate;
			rarpt->desc_rate = rate;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम rtl8723bu_handle_c2h(काष्ठा rtl8xxxu_priv *priv,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl8723bu_c2h *c2h = (काष्ठा rtl8723bu_c2h *)skb->data;
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक len;

	len = skb->len - 2;

	dev_dbg(dev, "C2H ID %02x seq %02x, len %02x source %02x\n",
		c2h->id, c2h->seq, len, c2h->bt_info.response_source);

	चयन(c2h->id) अणु
	हाल C2H_8723B_BT_INFO:
		अगर (c2h->bt_info.response_source >
		    BT_INFO_SRC_8723B_BT_ACTIVE_SEND)
			dev_dbg(dev, "C2H_BT_INFO WiFi only firmware\n");
		अन्यथा
			dev_dbg(dev, "C2H_BT_INFO BT/WiFi coexist firmware\n");

		अगर (c2h->bt_info.bt_has_reset)
			dev_dbg(dev, "BT has been reset\n");
		अगर (c2h->bt_info.tx_rx_mask)
			dev_dbg(dev, "BT TRx mask\n");

		अवरोध;
	हाल C2H_8723B_BT_MP_INFO:
		dev_dbg(dev, "C2H_MP_INFO ext ID %02x, status %02x\n",
			c2h->bt_mp_info.ext_id, c2h->bt_mp_info.status);
		अवरोध;
	हाल C2H_8723B_RA_REPORT:
		dev_dbg(dev,
			"C2H RA RPT: rate %02x, unk %i, macid %02x, noise %i\n",
			c2h->ra_report.rate, c2h->ra_report.sgi,
			c2h->ra_report.macid, c2h->ra_report.noisy_state);
		अवरोध;
	शेष:
		dev_info(dev, "Unhandled C2H event %02x seq %02x\n",
			 c2h->id, c2h->seq);
		prपूर्णांक_hex_dump(KERN_INFO, "C2H content: ", DUMP_PREFIX_NONE,
			       16, 1, c2h->raw.payload, len, false);
		अवरोध;
	पूर्ण

	skb_queue_tail(&priv->c2hcmd_queue, skb);

	schedule_work(&priv->c2hcmd_work);
पूर्ण

पूर्णांक rtl8xxxu_parse_rxdesc16(काष्ठा rtl8xxxu_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा rtl8xxxu_rxdesc16 *rx_desc;
	काष्ठा rtl8723au_phy_stats *phy_stats;
	काष्ठा sk_buff *next_skb = शून्य;
	__le32 *_rx_desc_le;
	u32 *_rx_desc;
	पूर्णांक drvinfo_sz, desc_shअगरt;
	पूर्णांक i, pkt_cnt, pkt_len, urb_len, pkt_offset;

	urb_len = skb->len;
	pkt_cnt = 0;

	करो अणु
		rx_desc = (काष्ठा rtl8xxxu_rxdesc16 *)skb->data;
		_rx_desc_le = (__le32 *)skb->data;
		_rx_desc = (u32 *)skb->data;

		क्रम (i = 0;
		     i < (माप(काष्ठा rtl8xxxu_rxdesc16) / माप(u32)); i++)
			_rx_desc[i] = le32_to_cpu(_rx_desc_le[i]);

		/*
		 * Only पढ़ो pkt_cnt from the header अगर we're parsing the
		 * first packet
		 */
		अगर (!pkt_cnt)
			pkt_cnt = rx_desc->pkt_cnt;
		pkt_len = rx_desc->pktlen;

		drvinfo_sz = rx_desc->drvinfo_sz * 8;
		desc_shअगरt = rx_desc->shअगरt;
		pkt_offset = roundup(pkt_len + drvinfo_sz + desc_shअगरt +
				     माप(काष्ठा rtl8xxxu_rxdesc16), 128);

		/*
		 * Only clone the skb अगर there's enough data at the end to
		 * at least cover the rx descriptor
		 */
		अगर (pkt_cnt > 1 &&
		    urb_len > (pkt_offset + माप(काष्ठा rtl8xxxu_rxdesc16)))
			next_skb = skb_clone(skb, GFP_ATOMIC);

		rx_status = IEEE80211_SKB_RXCB(skb);
		स_रखो(rx_status, 0, माप(काष्ठा ieee80211_rx_status));

		skb_pull(skb, माप(काष्ठा rtl8xxxu_rxdesc16));

		phy_stats = (काष्ठा rtl8723au_phy_stats *)skb->data;

		skb_pull(skb, drvinfo_sz + desc_shअगरt);

		skb_trim(skb, pkt_len);

		अगर (rx_desc->phy_stats)
			rtl8xxxu_rx_parse_phystats(priv, rx_status, phy_stats,
						   rx_desc->rxmcs);

		rx_status->maस_समय = rx_desc->tsfl;
		rx_status->flag |= RX_FLAG_MACTIME_START;

		अगर (!rx_desc->swdec)
			rx_status->flag |= RX_FLAG_DECRYPTED;
		अगर (rx_desc->crc32)
			rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
		अगर (rx_desc->bw)
			rx_status->bw = RATE_INFO_BW_40;

		अगर (rx_desc->rxht) अणु
			rx_status->encoding = RX_ENC_HT;
			rx_status->rate_idx = rx_desc->rxmcs - DESC_RATE_MCS0;
		पूर्ण अन्यथा अणु
			rx_status->rate_idx = rx_desc->rxmcs;
		पूर्ण

		rx_status->freq = hw->conf.chandef.chan->center_freq;
		rx_status->band = hw->conf.chandef.chan->band;

		ieee80211_rx_irqsafe(hw, skb);

		skb = next_skb;
		अगर (skb)
			skb_pull(next_skb, pkt_offset);

		pkt_cnt--;
		urb_len -= pkt_offset;
	पूर्ण जबतक (skb && urb_len > 0 && pkt_cnt > 0);

	वापस RX_TYPE_DATA_PKT;
पूर्ण

पूर्णांक rtl8xxxu_parse_rxdesc24(काष्ठा rtl8xxxu_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा rtl8xxxu_rxdesc24 *rx_desc =
		(काष्ठा rtl8xxxu_rxdesc24 *)skb->data;
	काष्ठा rtl8723au_phy_stats *phy_stats;
	__le32 *_rx_desc_le = (__le32 *)skb->data;
	u32 *_rx_desc = (u32 *)skb->data;
	पूर्णांक drvinfo_sz, desc_shअगरt;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(काष्ठा rtl8xxxu_rxdesc24) / माप(u32)); i++)
		_rx_desc[i] = le32_to_cpu(_rx_desc_le[i]);

	स_रखो(rx_status, 0, माप(काष्ठा ieee80211_rx_status));

	skb_pull(skb, माप(काष्ठा rtl8xxxu_rxdesc24));

	phy_stats = (काष्ठा rtl8723au_phy_stats *)skb->data;

	drvinfo_sz = rx_desc->drvinfo_sz * 8;
	desc_shअगरt = rx_desc->shअगरt;
	skb_pull(skb, drvinfo_sz + desc_shअगरt);

	अगर (rx_desc->rpt_sel) अणु
		काष्ठा device *dev = &priv->udev->dev;
		dev_dbg(dev, "%s: C2H packet\n", __func__);
		rtl8723bu_handle_c2h(priv, skb);
		वापस RX_TYPE_C2H;
	पूर्ण

	अगर (rx_desc->phy_stats)
		rtl8xxxu_rx_parse_phystats(priv, rx_status, phy_stats,
					   rx_desc->rxmcs);

	rx_status->maस_समय = rx_desc->tsfl;
	rx_status->flag |= RX_FLAG_MACTIME_START;

	अगर (!rx_desc->swdec)
		rx_status->flag |= RX_FLAG_DECRYPTED;
	अगर (rx_desc->crc32)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (rx_desc->bw)
		rx_status->bw = RATE_INFO_BW_40;

	अगर (rx_desc->rxmcs >= DESC_RATE_MCS0) अणु
		rx_status->encoding = RX_ENC_HT;
		rx_status->rate_idx = rx_desc->rxmcs - DESC_RATE_MCS0;
	पूर्ण अन्यथा अणु
		rx_status->rate_idx = rx_desc->rxmcs;
	पूर्ण

	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;

	ieee80211_rx_irqsafe(hw, skb);
	वापस RX_TYPE_DATA_PKT;
पूर्ण

अटल व्योम rtl8xxxu_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा rtl8xxxu_rx_urb *rx_urb =
		container_of(urb, काष्ठा rtl8xxxu_rx_urb, urb);
	काष्ठा ieee80211_hw *hw = rx_urb->hw;
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा device *dev = &priv->udev->dev;

	skb_put(skb, urb->actual_length);

	अगर (urb->status == 0) अणु
		priv->fops->parse_rx_desc(priv, skb);

		skb = शून्य;
		rx_urb->urb.context = शून्य;
		rtl8xxxu_queue_rx_urb(priv, rx_urb);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: status %i\n",	__func__, urb->status);
		जाओ cleanup;
	पूर्ण
	वापस;

cleanup:
	usb_मुक्त_urb(urb);
	dev_kमुक्त_skb(skb);
	वापस;
पूर्ण

अटल पूर्णांक rtl8xxxu_submit_rx_urb(काष्ठा rtl8xxxu_priv *priv,
				  काष्ठा rtl8xxxu_rx_urb *rx_urb)
अणु
	काष्ठा rtl8xxxu_fileops *fops = priv->fops;
	काष्ठा sk_buff *skb;
	पूर्णांक skb_size;
	पूर्णांक ret, rx_desc_sz;

	rx_desc_sz = fops->rx_desc_size;

	अगर (priv->rx_buf_aggregation && fops->rx_agg_buf_size) अणु
		skb_size = fops->rx_agg_buf_size;
		skb_size += (rx_desc_sz + माप(काष्ठा rtl8723au_phy_stats));
	पूर्ण अन्यथा अणु
		skb_size = IEEE80211_MAX_FRAME_LEN;
	पूर्ण

	skb = __netdev_alloc_skb(शून्य, skb_size, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	स_रखो(skb->data, 0, rx_desc_sz);
	usb_fill_bulk_urb(&rx_urb->urb, priv->udev, priv->pipe_in, skb->data,
			  skb_size, rtl8xxxu_rx_complete, skb);
	usb_anchor_urb(&rx_urb->urb, &priv->rx_anchor);
	ret = usb_submit_urb(&rx_urb->urb, GFP_ATOMIC);
	अगर (ret)
		usb_unanchor_urb(&rx_urb->urb);
	वापस ret;
पूर्ण

अटल व्योम rtl8xxxu_पूर्णांक_complete(काष्ठा urb *urb)
अणु
	काष्ठा rtl8xxxu_priv *priv = (काष्ठा rtl8xxxu_priv *)urb->context;
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक ret;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_INTERRUPT)
		dev_dbg(dev, "%s: status %i\n", __func__, urb->status);
	अगर (urb->status == 0) अणु
		usb_anchor_urb(urb, &priv->पूर्णांक_anchor);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (ret)
			usb_unanchor_urb(urb);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: Error %i\n", __func__, urb->status);
	पूर्ण
पूर्ण


अटल पूर्णांक rtl8xxxu_submit_पूर्णांक_urb(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा urb *urb;
	u32 val32;
	पूर्णांक ret;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	usb_fill_पूर्णांक_urb(urb, priv->udev, priv->pipe_पूर्णांकerrupt,
			 priv->पूर्णांक_buf, USB_INTR_CONTENT_LENGTH,
			 rtl8xxxu_पूर्णांक_complete, priv, 1);
	usb_anchor_urb(urb, &priv->पूर्णांक_anchor);
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		जाओ error;
	पूर्ण

	val32 = rtl8xxxu_पढ़ो32(priv, REG_USB_HIMR);
	val32 |= USB_HIMR_CPWM;
	rtl8xxxu_ग_लिखो32(priv, REG_USB_HIMR, val32);

error:
	usb_मुक्त_urb(urb);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8xxxu_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	पूर्णांक ret;
	u8 val8;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (!priv->vअगर)
			priv->vअगर = vअगर;
		अन्यथा
			वापस -EOPNOTSUPP;
		rtl8xxxu_stop_tx_beacon(priv);

		val8 = rtl8xxxu_पढ़ो8(priv, REG_BEACON_CTRL);
		val8 |= BEACON_ATIM | BEACON_FUNCTION_ENABLE |
			BEACON_DISABLE_TSF_UPDATE;
		rtl8xxxu_ग_लिखो8(priv, REG_BEACON_CTRL, val8);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	rtl8xxxu_set_linktype(priv, vअगर->type);

	वापस ret;
पूर्ण

अटल व्योम rtl8xxxu_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;

	dev_dbg(&priv->udev->dev, "%s\n", __func__);

	अगर (priv->vअगर)
		priv->vअगर = शून्य;
पूर्ण

अटल पूर्णांक rtl8xxxu_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	u16 val16;
	पूर्णांक ret = 0, channel;
	bool ht40;

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_CHANNEL)
		dev_info(dev,
			 "%s: channel: %i (changed %08x chandef.width %02x)\n",
			 __func__, hw->conf.chandef.chan->hw_value,
			 changed, hw->conf.chandef.width);

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) अणु
		val16 = ((hw->conf.दीर्घ_frame_max_tx_count <<
			  RETRY_LIMIT_LONG_SHIFT) & RETRY_LIMIT_LONG_MASK) |
			((hw->conf.लघु_frame_max_tx_count <<
			  RETRY_LIMIT_SHORT_SHIFT) & RETRY_LIMIT_SHORT_MASK);
		rtl8xxxu_ग_लिखो16(priv, REG_RETRY_LIMIT, val16);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		चयन (hw->conf.chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_20_NOHT:
		हाल NL80211_CHAN_WIDTH_20:
			ht40 = false;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_40:
			ht40 = true;
			अवरोध;
		शेष:
			ret = -ENOTSUPP;
			जाओ निकास;
		पूर्ण

		channel = hw->conf.chandef.chan->hw_value;

		priv->fops->set_tx_घातer(priv, channel, ht40);

		priv->fops->config_channel(hw);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8xxxu_conf_tx(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			    स्थिर काष्ठा ieee80211_tx_queue_params *param)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	u32 val32;
	u8 aअगरs, acm_ctrl, acm_bit;

	aअगरs = param->aअगरs;

	val32 = aअगरs |
		fls(param->cw_min) << EDCA_PARAM_ECW_MIN_SHIFT |
		fls(param->cw_max) << EDCA_PARAM_ECW_MAX_SHIFT |
		(u32)param->txop << EDCA_PARAM_TXOP_SHIFT;

	acm_ctrl = rtl8xxxu_पढ़ो8(priv, REG_ACM_HW_CTRL);
	dev_dbg(dev,
		"%s: IEEE80211 queue %02x val %08x, acm %i, acm_ctrl %02x\n",
		__func__, queue, val32, param->acm, acm_ctrl);

	चयन (queue) अणु
	हाल IEEE80211_AC_VO:
		acm_bit = ACM_HW_CTRL_VO;
		rtl8xxxu_ग_लिखो32(priv, REG_EDCA_VO_PARAM, val32);
		अवरोध;
	हाल IEEE80211_AC_VI:
		acm_bit = ACM_HW_CTRL_VI;
		rtl8xxxu_ग_लिखो32(priv, REG_EDCA_VI_PARAM, val32);
		अवरोध;
	हाल IEEE80211_AC_BE:
		acm_bit = ACM_HW_CTRL_BE;
		rtl8xxxu_ग_लिखो32(priv, REG_EDCA_BE_PARAM, val32);
		अवरोध;
	हाल IEEE80211_AC_BK:
		acm_bit = ACM_HW_CTRL_BK;
		rtl8xxxu_ग_लिखो32(priv, REG_EDCA_BK_PARAM, val32);
		अवरोध;
	शेष:
		acm_bit = 0;
		अवरोध;
	पूर्ण

	अगर (param->acm)
		acm_ctrl |= acm_bit;
	अन्यथा
		acm_ctrl &= ~acm_bit;
	rtl8xxxu_ग_लिखो8(priv, REG_ACM_HW_CTRL, acm_ctrl);

	वापस 0;
पूर्ण

अटल व्योम rtl8xxxu_configure_filter(काष्ठा ieee80211_hw *hw,
				      अचिन्हित पूर्णांक changed_flags,
				      अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	u32 rcr = rtl8xxxu_पढ़ो32(priv, REG_RCR);

	dev_dbg(&priv->udev->dev, "%s: changed_flags %08x, total_flags %08x\n",
		__func__, changed_flags, *total_flags);

	/*
	 * FIF_ALLMULTI ignored as all multicast frames are accepted (REG_MAR)
	 */

	अगर (*total_flags & FIF_FCSFAIL)
		rcr |= RCR_ACCEPT_CRC32;
	अन्यथा
		rcr &= ~RCR_ACCEPT_CRC32;

	/*
	 * FIF_PLCPFAIL not supported?
	 */

	अगर (*total_flags & FIF_BCN_PRBRESP_PROMISC)
		rcr &= ~RCR_CHECK_BSSID_BEACON;
	अन्यथा
		rcr |= RCR_CHECK_BSSID_BEACON;

	अगर (*total_flags & FIF_CONTROL)
		rcr |= RCR_ACCEPT_CTRL_FRAME;
	अन्यथा
		rcr &= ~RCR_ACCEPT_CTRL_FRAME;

	अगर (*total_flags & FIF_OTHER_BSS) अणु
		rcr |= RCR_ACCEPT_AP;
		rcr &= ~RCR_CHECK_BSSID_MATCH;
	पूर्ण अन्यथा अणु
		rcr &= ~RCR_ACCEPT_AP;
		rcr |= RCR_CHECK_BSSID_MATCH;
	पूर्ण

	अगर (*total_flags & FIF_PSPOLL)
		rcr |= RCR_ACCEPT_PM;
	अन्यथा
		rcr &= ~RCR_ACCEPT_PM;

	/*
	 * FIF_PROBE_REQ ignored as probe requests always seem to be accepted
	 */

	rtl8xxxu_ग_लिखो32(priv, REG_RCR, rcr);

	*total_flags &= (FIF_ALLMULTI | FIF_FCSFAIL | FIF_BCN_PRBRESP_PROMISC |
			 FIF_CONTROL | FIF_OTHER_BSS | FIF_PSPOLL |
			 FIF_PROBE_REQ);
पूर्ण

अटल पूर्णांक rtl8xxxu_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 rts)
अणु
	अगर (rts > 2347)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8xxxu_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	u8 mac_addr[ETH_ALEN];
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक retval = -EOPNOTSUPP;

	dev_dbg(dev, "%s: cmd %02x, cipher %08x, index %i\n",
		__func__, cmd, key->cipher, key->keyidx);

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (key->keyidx > 3)
		वापस -EOPNOTSUPP;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:

		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		dev_dbg(dev, "%s: pairwise key\n", __func__);
		ether_addr_copy(mac_addr, sta->addr);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: group key\n", __func__);
		eth_broadcast_addr(mac_addr);
	पूर्ण

	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 |= CR_SECURITY_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	val8 = SEC_CFG_TX_SEC_ENABLE | SEC_CFG_TXBC_USE_DEFKEY |
		SEC_CFG_RX_SEC_ENABLE | SEC_CFG_RXBC_USE_DEFKEY;
	val8 |= SEC_CFG_TX_USE_DEFKEY | SEC_CFG_RX_USE_DEFKEY;
	rtl8xxxu_ग_लिखो8(priv, REG_SECURITY_CFG, val8);

	चयन (cmd) अणु
	हाल SET_KEY:
		key->hw_key_idx = key->keyidx;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		rtl8xxxu_cam_ग_लिखो(priv, key, mac_addr);
		retval = 0;
		अवरोध;
	हाल DISABLE_KEY:
		rtl8xxxu_ग_लिखो32(priv, REG_CAM_WRITE, 0x00000000);
		val32 = CAM_CMD_POLLING | CAM_CMD_WRITE |
			key->keyidx << CAM_CMD_KEY_SHIFT;
		rtl8xxxu_ग_लिखो32(priv, REG_CAM_CMD, val32);
		retval = 0;
		अवरोध;
	शेष:
		dev_warn(dev, "%s: Unsupported command %02x\n", __func__, cmd);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक
rtl8xxxu_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा device *dev = &priv->udev->dev;
	u8 ampdu_factor, ampdu_density;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_TX_START:
		dev_dbg(dev, "%s: IEEE80211_AMPDU_TX_START\n", __func__);
		ampdu_factor = sta->ht_cap.ampdu_factor;
		ampdu_density = sta->ht_cap.ampdu_density;
		rtl8xxxu_set_ampdu_factor(priv, ampdu_factor);
		rtl8xxxu_set_ampdu_min_space(priv, ampdu_density);
		dev_dbg(dev,
			"Changed HT: ampdu_factor %02x, ampdu_density %02x\n",
			ampdu_factor, ampdu_density);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
		dev_dbg(dev, "%s: IEEE80211_AMPDU_TX_STOP_FLUSH\n", __func__);
		rtl8xxxu_set_ampdu_factor(priv, 0);
		rtl8xxxu_set_ampdu_min_space(priv, 0);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		dev_dbg(dev, "%s: IEEE80211_AMPDU_TX_STOP_FLUSH_CONT\n",
			 __func__);
		rtl8xxxu_set_ampdu_factor(priv, 0);
		rtl8xxxu_set_ampdu_min_space(priv, 0);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_START:
		dev_dbg(dev, "%s: IEEE80211_AMPDU_RX_START\n", __func__);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		dev_dbg(dev, "%s: IEEE80211_AMPDU_RX_STOP\n", __func__);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
rtl8xxxu_sta_statistics(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, काष्ठा station_info *sinfo)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;

	sinfo->txrate = priv->ra_report.txrate;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
पूर्ण

अटल u8 rtl8xxxu_संकेत_to_snr(पूर्णांक संकेत)
अणु
	अगर (संकेत < RTL8XXXU_NOISE_FLOOR_MIN)
		संकेत = RTL8XXXU_NOISE_FLOOR_MIN;
	अन्यथा अगर (संकेत > 0)
		संकेत = 0;
	वापस (u8)(संकेत - RTL8XXXU_NOISE_FLOOR_MIN);
पूर्ण

अटल व्योम rtl8xxxu_refresh_rate_mask(काष्ठा rtl8xxxu_priv *priv,
				       पूर्णांक संकेत, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	u16 wireless_mode;
	u8 rssi_level, ratr_idx;
	u8 txbw_40mhz;
	u8 snr, snr_thresh_high, snr_thresh_low;
	u8 go_up_gap = 5;

	rssi_level = priv->rssi_level;
	snr = rtl8xxxu_संकेत_to_snr(संकेत);
	snr_thresh_high = RTL8XXXU_SNR_THRESH_HIGH;
	snr_thresh_low = RTL8XXXU_SNR_THRESH_LOW;
	txbw_40mhz = (hw->conf.chandef.width == NL80211_CHAN_WIDTH_40) ? 1 : 0;

	चयन (rssi_level) अणु
	हाल RTL8XXXU_RATR_STA_MID:
		snr_thresh_high += go_up_gap;
		अवरोध;
	हाल RTL8XXXU_RATR_STA_LOW:
		snr_thresh_high += go_up_gap;
		snr_thresh_low += go_up_gap;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (snr > snr_thresh_high)
		rssi_level = RTL8XXXU_RATR_STA_HIGH;
	अन्यथा अगर (snr > snr_thresh_low)
		rssi_level = RTL8XXXU_RATR_STA_MID;
	अन्यथा
		rssi_level = RTL8XXXU_RATR_STA_LOW;

	अगर (rssi_level != priv->rssi_level) अणु
		पूर्णांक sgi = 0;
		u32 rate_biपंचांगap = 0;

		rcu_पढ़ो_lock();
		rate_biपंचांगap = (sta->supp_rates[0] & 0xfff) |
				(sta->ht_cap.mcs.rx_mask[0] << 12) |
				(sta->ht_cap.mcs.rx_mask[1] << 20);
		अगर (sta->ht_cap.cap &
		    (IEEE80211_HT_CAP_SGI_40 | IEEE80211_HT_CAP_SGI_20))
			sgi = 1;
		rcu_पढ़ो_unlock();

		wireless_mode = rtl8xxxu_wireless_mode(hw, sta);
		चयन (wireless_mode) अणु
		हाल WIRELESS_MODE_B:
			ratr_idx = RATEID_IDX_B;
			अगर (rate_biपंचांगap & 0x0000000c)
				rate_biपंचांगap &= 0x0000000d;
			अन्यथा
				rate_biपंचांगap &= 0x0000000f;
			अवरोध;
		हाल WIRELESS_MODE_A:
		हाल WIRELESS_MODE_G:
			ratr_idx = RATEID_IDX_G;
			अगर (rssi_level == RTL8XXXU_RATR_STA_HIGH)
				rate_biपंचांगap &= 0x00000f00;
			अन्यथा
				rate_biपंचांगap &= 0x00000ff0;
			अवरोध;
		हाल (WIRELESS_MODE_B | WIRELESS_MODE_G):
			ratr_idx = RATEID_IDX_BG;
			अगर (rssi_level == RTL8XXXU_RATR_STA_HIGH)
				rate_biपंचांगap &= 0x00000f00;
			अन्यथा अगर (rssi_level == RTL8XXXU_RATR_STA_MID)
				rate_biपंचांगap &= 0x00000ff0;
			अन्यथा
				rate_biपंचांगap &= 0x00000ff5;
			अवरोध;
		हाल WIRELESS_MODE_N_24G:
		हाल WIRELESS_MODE_N_5G:
		हाल (WIRELESS_MODE_G | WIRELESS_MODE_N_24G):
		हाल (WIRELESS_MODE_A | WIRELESS_MODE_N_5G):
			अगर (priv->tx_paths == 2 && priv->rx_paths == 2)
				ratr_idx = RATEID_IDX_GN_N2SS;
			अन्यथा
				ratr_idx = RATEID_IDX_GN_N1SS;
			अवरोध;
		हाल (WIRELESS_MODE_B | WIRELESS_MODE_G | WIRELESS_MODE_N_24G):
		हाल (WIRELESS_MODE_B | WIRELESS_MODE_N_24G):
			अगर (txbw_40mhz) अणु
				अगर (priv->tx_paths == 2 && priv->rx_paths == 2)
					ratr_idx = RATEID_IDX_BGN_40M_2SS;
				अन्यथा
					ratr_idx = RATEID_IDX_BGN_40M_1SS;
			पूर्ण अन्यथा अणु
				अगर (priv->tx_paths == 2 && priv->rx_paths == 2)
					ratr_idx = RATEID_IDX_BGN_20M_2SS_BN;
				अन्यथा
					ratr_idx = RATEID_IDX_BGN_20M_1SS_BN;
			पूर्ण

			अगर (priv->tx_paths == 2 && priv->rx_paths == 2) अणु
				अगर (rssi_level == RTL8XXXU_RATR_STA_HIGH) अणु
					rate_biपंचांगap &= 0x0f8f0000;
				पूर्ण अन्यथा अगर (rssi_level == RTL8XXXU_RATR_STA_MID) अणु
					rate_biपंचांगap &= 0x0f8ff000;
				पूर्ण अन्यथा अणु
					अगर (txbw_40mhz)
						rate_biपंचांगap &= 0x0f8ff015;
					अन्यथा
						rate_biपंचांगap &= 0x0f8ff005;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (rssi_level == RTL8XXXU_RATR_STA_HIGH) अणु
					rate_biपंचांगap &= 0x000f0000;
				पूर्ण अन्यथा अगर (rssi_level == RTL8XXXU_RATR_STA_MID) अणु
					rate_biपंचांगap &= 0x000ff000;
				पूर्ण अन्यथा अणु
					अगर (txbw_40mhz)
						rate_biपंचांगap &= 0x000ff015;
					अन्यथा
						rate_biपंचांगap &= 0x000ff005;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			ratr_idx = RATEID_IDX_BGN_40M_2SS;
			rate_biपंचांगap &= 0x0fffffff;
			अवरोध;
		पूर्ण

		priv->rssi_level = rssi_level;
		priv->fops->update_rate_mask(priv, rate_biपंचांगap, ratr_idx, sgi);
	पूर्ण
पूर्ण

अटल व्योम rtl8xxxu_watchकरोg_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा rtl8xxxu_priv *priv;

	priv = container_of(work, काष्ठा rtl8xxxu_priv, ra_watchकरोg.work);
	vअगर = priv->vअगर;

	अगर (vअगर && vअगर->type == NL80211_IFTYPE_STATION) अणु
		पूर्णांक संकेत;
		काष्ठा ieee80211_sta *sta;

		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, vअगर->bss_conf.bssid);
		अगर (!sta) अणु
			काष्ठा device *dev = &priv->udev->dev;

			dev_dbg(dev, "%s: no sta found\n", __func__);
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण
		rcu_पढ़ो_unlock();

		संकेत = ieee80211_ave_rssi(vअगर);
		rtl8xxxu_refresh_rate_mask(priv, संकेत, sta);
	पूर्ण

out:
	schedule_delayed_work(&priv->ra_watchकरोg, 2 * HZ);
पूर्ण

अटल पूर्णांक rtl8xxxu_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	काष्ठा rtl8xxxu_rx_urb *rx_urb;
	काष्ठा rtl8xxxu_tx_urb *tx_urb;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i;

	ret = 0;

	init_usb_anchor(&priv->rx_anchor);
	init_usb_anchor(&priv->tx_anchor);
	init_usb_anchor(&priv->पूर्णांक_anchor);

	priv->fops->enable_rf(priv);
	अगर (priv->usb_पूर्णांकerrupts) अणु
		ret = rtl8xxxu_submit_पूर्णांक_urb(hw);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < RTL8XXXU_TX_URBS; i++) अणु
		tx_urb = kदो_स्मृति(माप(काष्ठा rtl8xxxu_tx_urb), GFP_KERNEL);
		अगर (!tx_urb) अणु
			अगर (!i)
				ret = -ENOMEM;

			जाओ error_out;
		पूर्ण
		usb_init_urb(&tx_urb->urb);
		INIT_LIST_HEAD(&tx_urb->list);
		tx_urb->hw = hw;
		list_add(&tx_urb->list, &priv->tx_urb_मुक्त_list);
		priv->tx_urb_मुक्त_count++;
	पूर्ण

	priv->tx_stopped = false;

	spin_lock_irqsave(&priv->rx_urb_lock, flags);
	priv->shutकरोwn = false;
	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	क्रम (i = 0; i < RTL8XXXU_RX_URBS; i++) अणु
		rx_urb = kदो_स्मृति(माप(काष्ठा rtl8xxxu_rx_urb), GFP_KERNEL);
		अगर (!rx_urb) अणु
			अगर (!i)
				ret = -ENOMEM;

			जाओ error_out;
		पूर्ण
		usb_init_urb(&rx_urb->urb);
		INIT_LIST_HEAD(&rx_urb->list);
		rx_urb->hw = hw;

		ret = rtl8xxxu_submit_rx_urb(priv, rx_urb);
		अगर (ret) अणु
			अगर (ret != -ENOMEM) अणु
				skb = (काष्ठा sk_buff *)rx_urb->urb.context;
				dev_kमुक्त_skb(skb);
			पूर्ण
			rtl8xxxu_queue_rx_urb(priv, rx_urb);
		पूर्ण
	पूर्ण

	schedule_delayed_work(&priv->ra_watchकरोg, 2 * HZ);
निकास:
	/*
	 * Accept all data and mgmt frames
	 */
	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP2, 0xffff);
	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP0, 0xffff);

	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_AGC_CORE1, 0x6954341e);

	वापस ret;

error_out:
	rtl8xxxu_मुक्त_tx_resources(priv);
	/*
	 * Disable all data and mgmt frames
	 */
	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP2, 0x0000);
	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP0, 0x0000);

	वापस ret;
पूर्ण

अटल व्योम rtl8xxxu_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8xxxu_priv *priv = hw->priv;
	अचिन्हित दीर्घ flags;

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);

	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP0, 0x0000);
	rtl8xxxu_ग_लिखो16(priv, REG_RXFLTMAP2, 0x0000);

	spin_lock_irqsave(&priv->rx_urb_lock, flags);
	priv->shutकरोwn = true;
	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	usb_समाप्त_anchored_urbs(&priv->rx_anchor);
	usb_समाप्त_anchored_urbs(&priv->tx_anchor);
	अगर (priv->usb_पूर्णांकerrupts)
		usb_समाप्त_anchored_urbs(&priv->पूर्णांक_anchor);

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);

	priv->fops->disable_rf(priv);

	/*
	 * Disable पूर्णांकerrupts
	 */
	अगर (priv->usb_पूर्णांकerrupts)
		rtl8xxxu_ग_लिखो32(priv, REG_USB_HIMR, 0);

	cancel_delayed_work_sync(&priv->ra_watchकरोg);

	rtl8xxxu_मुक्त_rx_resources(priv);
	rtl8xxxu_मुक्त_tx_resources(priv);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rtl8xxxu_ops = अणु
	.tx = rtl8xxxu_tx,
	.add_पूर्णांकerface = rtl8xxxu_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = rtl8xxxu_हटाओ_पूर्णांकerface,
	.config = rtl8xxxu_config,
	.conf_tx = rtl8xxxu_conf_tx,
	.bss_info_changed = rtl8xxxu_bss_info_changed,
	.configure_filter = rtl8xxxu_configure_filter,
	.set_rts_threshold = rtl8xxxu_set_rts_threshold,
	.start = rtl8xxxu_start,
	.stop = rtl8xxxu_stop,
	.sw_scan_start = rtl8xxxu_sw_scan_start,
	.sw_scan_complete = rtl8xxxu_sw_scan_complete,
	.set_key = rtl8xxxu_set_key,
	.ampdu_action = rtl8xxxu_ampdu_action,
	.sta_statistics = rtl8xxxu_sta_statistics,
पूर्ण;

अटल पूर्णांक rtl8xxxu_parse_usb(काष्ठा rtl8xxxu_priv *priv,
			      काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकerface_desc;
	काष्ठा usb_host_पूर्णांकerface *host_पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक i, j = 0, endpoपूर्णांकs;
	u8 dir, xtype, num;
	पूर्णांक ret = 0;

	host_पूर्णांकerface = पूर्णांकerface->cur_altsetting;
	पूर्णांकerface_desc = &host_पूर्णांकerface->desc;
	endpoपूर्णांकs = पूर्णांकerface_desc->bNumEndpoपूर्णांकs;

	क्रम (i = 0; i < endpoपूर्णांकs; i++) अणु
		endpoपूर्णांक = &host_पूर्णांकerface->endpoपूर्णांक[i].desc;

		dir = endpoपूर्णांक->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK;
		num = usb_endpoपूर्णांक_num(endpoपूर्णांक);
		xtype = usb_endpoपूर्णांक_type(endpoपूर्णांक);
		अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_USB)
			dev_dbg(dev,
				"%s: endpoint: dir %02x, # %02x, type %02x\n",
				__func__, dir, num, xtype);
		अगर (usb_endpoपूर्णांक_dir_in(endpoपूर्णांक) &&
		    usb_endpoपूर्णांक_xfer_bulk(endpoपूर्णांक)) अणु
			अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_USB)
				dev_dbg(dev, "%s: in endpoint num %i\n",
					__func__, num);

			अगर (priv->pipe_in) अणु
				dev_warn(dev,
					 "%s: Too many IN pipes\n", __func__);
				ret = -EINVAL;
				जाओ निकास;
			पूर्ण

			priv->pipe_in =	usb_rcvbulkpipe(priv->udev, num);
		पूर्ण

		अगर (usb_endpoपूर्णांक_dir_in(endpoपूर्णांक) &&
		    usb_endpoपूर्णांक_xfer_पूर्णांक(endpoपूर्णांक)) अणु
			अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_USB)
				dev_dbg(dev, "%s: interrupt endpoint num %i\n",
					__func__, num);

			अगर (priv->pipe_पूर्णांकerrupt) अणु
				dev_warn(dev, "%s: Too many INTERRUPT pipes\n",
					 __func__);
				ret = -EINVAL;
				जाओ निकास;
			पूर्ण

			priv->pipe_पूर्णांकerrupt = usb_rcvपूर्णांकpipe(priv->udev, num);
		पूर्ण

		अगर (usb_endpoपूर्णांक_dir_out(endpoपूर्णांक) &&
		    usb_endpoपूर्णांक_xfer_bulk(endpoपूर्णांक)) अणु
			अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_USB)
				dev_dbg(dev, "%s: out endpoint num %i\n",
					__func__, num);
			अगर (j >= RTL8XXXU_OUT_ENDPOINTS) अणु
				dev_warn(dev,
					 "%s: Too many OUT pipes\n", __func__);
				ret = -EINVAL;
				जाओ निकास;
			पूर्ण
			priv->out_ep[j++] = num;
		पूर्ण
	पूर्ण
निकास:
	priv->nr_out_eps = j;
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8xxxu_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा rtl8xxxu_priv *priv;
	काष्ठा ieee80211_hw *hw;
	काष्ठा usb_device *udev;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक ret;
	पूर्णांक untested = 1;

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	चयन (id->idVenकरोr) अणु
	हाल USB_VENDOR_ID_REALTEK:
		चयन(id->idProduct) अणु
		हाल 0x1724:
		हाल 0x8176:
		हाल 0x8178:
		हाल 0x817f:
		हाल 0x818b:
			untested = 0;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x7392:
		अगर (id->idProduct == 0x7811 || id->idProduct == 0xa611)
			untested = 0;
		अवरोध;
	हाल 0x050d:
		अगर (id->idProduct == 0x1004)
			untested = 0;
		अवरोध;
	हाल 0x20f4:
		अगर (id->idProduct == 0x648b)
			untested = 0;
		अवरोध;
	हाल 0x2001:
		अगर (id->idProduct == 0x3308)
			untested = 0;
		अवरोध;
	हाल 0x2357:
		अगर (id->idProduct == 0x0109)
			untested = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (untested) अणु
		rtl8xxxu_debug |= RTL8XXXU_DEBUG_EFUSE;
		dev_info(&udev->dev,
			 "This Realtek USB WiFi dongle (0x%04x:0x%04x) is untested!\n",
			 id->idVenकरोr, id->idProduct);
		dev_info(&udev->dev,
			 "Please report results to Jes.Sorensen@gmail.com\n");
	पूर्ण

	hw = ieee80211_alloc_hw(माप(काष्ठा rtl8xxxu_priv), &rtl8xxxu_ops);
	अगर (!hw) अणु
		ret = -ENOMEM;
		priv = शून्य;
		जाओ निकास;
	पूर्ण

	priv = hw->priv;
	priv->hw = hw;
	priv->udev = udev;
	priv->fops = (काष्ठा rtl8xxxu_fileops *)id->driver_info;
	mutex_init(&priv->usb_buf_mutex);
	mutex_init(&priv->h2c_mutex);
	INIT_LIST_HEAD(&priv->tx_urb_मुक्त_list);
	spin_lock_init(&priv->tx_urb_lock);
	INIT_LIST_HEAD(&priv->rx_urb_pending_list);
	spin_lock_init(&priv->rx_urb_lock);
	INIT_WORK(&priv->rx_urb_wq, rtl8xxxu_rx_urb_work);
	INIT_DELAYED_WORK(&priv->ra_watchकरोg, rtl8xxxu_watchकरोg_callback);
	INIT_WORK(&priv->c2hcmd_work, rtl8xxxu_c2hcmd_callback);
	skb_queue_head_init(&priv->c2hcmd_queue);

	usb_set_पूर्णांकfdata(पूर्णांकerface, hw);

	ret = rtl8xxxu_parse_usb(priv, पूर्णांकerface);
	अगर (ret)
		जाओ निकास;

	ret = rtl8xxxu_identअगरy_chip(priv);
	अगर (ret) अणु
		dev_err(&udev->dev, "Fatal - failed to identify chip\n");
		जाओ निकास;
	पूर्ण

	ret = rtl8xxxu_पढ़ो_efuse(priv);
	अगर (ret) अणु
		dev_err(&udev->dev, "Fatal - failed to read EFuse\n");
		जाओ निकास;
	पूर्ण

	ret = priv->fops->parse_efuse(priv);
	अगर (ret) अणु
		dev_err(&udev->dev, "Fatal - failed to parse EFuse\n");
		जाओ निकास;
	पूर्ण

	rtl8xxxu_prपूर्णांक_chipinfo(priv);

	ret = priv->fops->load_firmware(priv);
	अगर (ret) अणु
		dev_err(&udev->dev, "Fatal - failed to load firmware\n");
		जाओ निकास;
	पूर्ण

	ret = rtl8xxxu_init_device(hw);
	अगर (ret)
		जाओ निकास;

	hw->wiphy->max_scan_ssids = 1;
	hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);
	hw->queues = 4;

	sband = &rtl8xxxu_supported_band;
	sband->ht_cap.ht_supported = true;
	sband->ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	sband->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	sband->ht_cap.cap = IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40;
	स_रखो(&sband->ht_cap.mcs, 0, माप(sband->ht_cap.mcs));
	sband->ht_cap.mcs.rx_mask[0] = 0xff;
	sband->ht_cap.mcs.rx_mask[4] = 0x01;
	अगर (priv->rf_paths > 1) अणु
		sband->ht_cap.mcs.rx_mask[1] = 0xff;
		sband->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
	पूर्ण
	sband->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	/*
	 * Some APs will negotiate HT20_40 in a noisy environment leading
	 * to miserable perक्रमmance. Rather than शेषing to this, only
	 * enable it अगर explicitly requested at module load समय.
	 */
	अगर (rtl8xxxu_ht40_2g) अणु
		dev_info(&udev->dev, "Enabling HT_20_40 on the 2.4GHz band\n");
		sband->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	पूर्ण
	hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;

	hw->wiphy->rts_threshold = 2347;

	SET_IEEE80211_DEV(priv->hw, &पूर्णांकerface->dev);
	SET_IEEE80211_PERM_ADDR(hw, priv->mac_addr);

	hw->extra_tx_headroom = priv->fops->tx_desc_size;
	ieee80211_hw_set(hw, SIGNAL_DBM);
	/*
	 * The firmware handles rate control
	 */
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = ieee80211_रेजिस्टर_hw(priv->hw);
	अगर (ret) अणु
		dev_err(&udev->dev, "%s: Failed to register: %i\n",
			__func__, ret);
		जाओ निकास;
	पूर्ण

	वापस 0;

निकास:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	अगर (priv) अणु
		kमुक्त(priv->fw_data);
		mutex_destroy(&priv->usb_buf_mutex);
		mutex_destroy(&priv->h2c_mutex);
	पूर्ण
	usb_put_dev(udev);

	ieee80211_मुक्त_hw(hw);

	वापस ret;
पूर्ण

अटल व्योम rtl8xxxu_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा rtl8xxxu_priv *priv;
	काष्ठा ieee80211_hw *hw;

	hw = usb_get_पूर्णांकfdata(पूर्णांकerface);
	priv = hw->priv;

	ieee80211_unरेजिस्टर_hw(hw);

	priv->fops->घातer_off(priv);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	dev_info(&priv->udev->dev, "disconnecting\n");

	kमुक्त(priv->fw_data);
	mutex_destroy(&priv->usb_buf_mutex);
	mutex_destroy(&priv->h2c_mutex);

	अगर (priv->udev->state != USB_STATE_NOTATTACHED) अणु
		dev_info(&priv->udev->dev,
			 "Device still attached, trying to reset\n");
		usb_reset_device(priv->udev);
	पूर्ण
	usb_put_dev(priv->udev);
	ieee80211_मुक्त_hw(hw);
पूर्ण

अटल स्थिर काष्ठा usb_device_id dev_table[] = अणु
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8724, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8723au_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x1724, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8723au_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x0724, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8723au_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x818b, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
/* TP-Link TL-WN822N v4 */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2357, 0x0108, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
/* D-Link DWA-131 rev E1, tested by David Patiथऔo */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x3319, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
/* Tested by Myckel Habets */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2357, 0x0109, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0xb720, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8723bu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x7392, 0xa611, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8723bu_fopsपूर्ण,
#अगर_घोषित CONFIG_RTL8XXXU_UNTESTED
/* Still supported by rtlwअगरi */
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8176, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8178, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x817f, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Tested by Larry Finger */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x7392, 0x7811, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Tested by Andrea Merello */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x050d, 0x1004, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Tested by Jocelyn Mayer */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x20f4, 0x648b, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Tested by Stefano Bravi */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x3308, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Currently untested 8188 series devices */
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x018a, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8191, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8170, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x8177, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x817a, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x817b, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x817d, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x817e, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x818a, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x317f, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x1058, 0x0631, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04bb, 0x094c, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x050d, 0x1102, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x06f8, 0xe033, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x07b8, 0x8189, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0846, 0x9041, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0b05, 0x17ba, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x1e1e, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x5088, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0df6, 0x0052, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0df6, 0x005c, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0eb0, 0x9071, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x103c, 0x1629, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x13d3, 0x3357, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x330b, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0x4902, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0xab2a, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0xab2e, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0xed17, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x4855, 0x0090, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x4856, 0x0091, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0xcdab, 0x8010, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaff7, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaff9, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaffa, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaff8, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaffb, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04f2, 0xaffc, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0x1201, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* Currently untested 8192 series devices */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x04bb, 0x0950, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x050d, 0x2102, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x050d, 0x2103, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0586, 0x341f, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x06f8, 0xe035, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0b05, 0x17ab, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0df6, 0x0061, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0df6, 0x0070, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0789, 0x016d, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x07aa, 0x0056, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x07b8, 0x8178, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0846, 0x9021, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0846, 0xf001, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x2e2e, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0e66, 0x0019, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x0e66, 0x0020, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x3307, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x3309, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2001, 0x330a, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0xab2b, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x20f4, 0x624d, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2357, 0x0100, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x4855, 0x0091, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x7392, 0x7822, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192cu_fopsपूर्ण,
/* found in rtl8192eu venकरोr driver */
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2357, 0x0107, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(0x2019, 0xab33, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_VENDOR_ID_REALTEK, 0x818c, 0xff, 0xff, 0xff),
	.driver_info = (अचिन्हित दीर्घ)&rtl8192eu_fopsपूर्ण,
#पूर्ण_अगर
अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver rtl8xxxu_driver = अणु
	.name = DRIVER_NAME,
	.probe = rtl8xxxu_probe,
	.disconnect = rtl8xxxu_disconnect,
	.id_table = dev_table,
	.no_dynamic_id = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

अटल पूर्णांक __init rtl8xxxu_module_init(व्योम)
अणु
	पूर्णांक res;

	res = usb_रेजिस्टर(&rtl8xxxu_driver);
	अगर (res < 0)
		pr_err(DRIVER_NAME ": usb_register() failed (%i)\n", res);

	वापस res;
पूर्ण

अटल व्योम __निकास rtl8xxxu_module_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&rtl8xxxu_driver);
पूर्ण


MODULE_DEVICE_TABLE(usb, dev_table);

module_init(rtl8xxxu_module_init);
module_निकास(rtl8xxxu_module_निकास);
