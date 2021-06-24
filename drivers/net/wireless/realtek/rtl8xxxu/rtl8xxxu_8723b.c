<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTL8XXXU mac80211 USB driver - 8723b specअगरic subdriver
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

अटल काष्ठा rtl8xxxu_reg8val rtl8723b_mac_init_table[] = अणु
	अणु0x02f, 0x30पूर्ण, अणु0x035, 0x00पूर्ण, अणु0x039, 0x08पूर्ण, अणु0x04e, 0xe0पूर्ण,
	अणु0x064, 0x00पूर्ण, अणु0x067, 0x20पूर्ण, अणु0x428, 0x0aपूर्ण, अणु0x429, 0x10पूर्ण,
	अणु0x430, 0x00पूर्ण, अणु0x431, 0x00पूर्ण,
	अणु0x432, 0x00पूर्ण, अणु0x433, 0x01पूर्ण, अणु0x434, 0x04पूर्ण, अणु0x435, 0x05पूर्ण,
	अणु0x436, 0x07पूर्ण, अणु0x437, 0x08पूर्ण, अणु0x43c, 0x04पूर्ण, अणु0x43d, 0x05पूर्ण,
	अणु0x43e, 0x07पूर्ण, अणु0x43f, 0x08पूर्ण, अणु0x440, 0x5dपूर्ण, अणु0x441, 0x01पूर्ण,
	अणु0x442, 0x00पूर्ण, अणु0x444, 0x10पूर्ण, अणु0x445, 0x00पूर्ण, अणु0x446, 0x00पूर्ण,
	अणु0x447, 0x00पूर्ण, अणु0x448, 0x00पूर्ण, अणु0x449, 0xf0पूर्ण, अणु0x44a, 0x0fपूर्ण,
	अणु0x44b, 0x3eपूर्ण, अणु0x44c, 0x10पूर्ण, अणु0x44d, 0x00पूर्ण, अणु0x44e, 0x00पूर्ण,
	अणु0x44f, 0x00पूर्ण, अणु0x450, 0x00पूर्ण, अणु0x451, 0xf0पूर्ण, अणु0x452, 0x0fपूर्ण,
	अणु0x453, 0x00पूर्ण, अणु0x456, 0x5eपूर्ण, अणु0x460, 0x66पूर्ण, अणु0x461, 0x66पूर्ण,
	अणु0x4c8, 0xffपूर्ण, अणु0x4c9, 0x08पूर्ण, अणु0x4cc, 0xffपूर्ण,
	अणु0x4cd, 0xffपूर्ण, अणु0x4ce, 0x01पूर्ण, अणु0x500, 0x26पूर्ण, अणु0x501, 0xa2पूर्ण,
	अणु0x502, 0x2fपूर्ण, अणु0x503, 0x00पूर्ण, अणु0x504, 0x28पूर्ण, अणु0x505, 0xa3पूर्ण,
	अणु0x506, 0x5eपूर्ण, अणु0x507, 0x00पूर्ण, अणु0x508, 0x2bपूर्ण, अणु0x509, 0xa4पूर्ण,
	अणु0x50a, 0x5eपूर्ण, अणु0x50b, 0x00पूर्ण, अणु0x50c, 0x4fपूर्ण, अणु0x50d, 0xa4पूर्ण,
	अणु0x50e, 0x00पूर्ण, अणु0x50f, 0x00पूर्ण, अणु0x512, 0x1cपूर्ण, अणु0x514, 0x0aपूर्ण,
	अणु0x516, 0x0aपूर्ण, अणु0x525, 0x4fपूर्ण,
	अणु0x550, 0x10पूर्ण, अणु0x551, 0x10पूर्ण, अणु0x559, 0x02पूर्ण, अणु0x55c, 0x50पूर्ण,
	अणु0x55d, 0xffपूर्ण, अणु0x605, 0x30पूर्ण, अणु0x608, 0x0eपूर्ण, अणु0x609, 0x2aपूर्ण,
	अणु0x620, 0xffपूर्ण, अणु0x621, 0xffपूर्ण, अणु0x622, 0xffपूर्ण, अणु0x623, 0xffपूर्ण,
	अणु0x624, 0xffपूर्ण, अणु0x625, 0xffपूर्ण, अणु0x626, 0xffपूर्ण, अणु0x627, 0xffपूर्ण,
	अणु0x638, 0x50पूर्ण, अणु0x63c, 0x0aपूर्ण, अणु0x63d, 0x0aपूर्ण, अणु0x63e, 0x0eपूर्ण,
	अणु0x63f, 0x0eपूर्ण, अणु0x640, 0x40पूर्ण, अणु0x642, 0x40पूर्ण, अणु0x643, 0x00पूर्ण,
	अणु0x652, 0xc8पूर्ण, अणु0x66e, 0x05पूर्ण, अणु0x700, 0x21पूर्ण, अणु0x701, 0x43पूर्ण,
	अणु0x702, 0x65पूर्ण, अणु0x703, 0x87पूर्ण, अणु0x708, 0x21पूर्ण, अणु0x709, 0x43पूर्ण,
	अणु0x70a, 0x65पूर्ण, अणु0x70b, 0x87पूर्ण, अणु0x765, 0x18पूर्ण, अणु0x76e, 0x04पूर्ण,
	अणु0xffff, 0xffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8723b_phy_1t_init_table[] = अणु
	अणु0x800, 0x80040000पूर्ण, अणु0x804, 0x00000003पूर्ण,
	अणु0x808, 0x0000fc00पूर्ण, अणु0x80c, 0x0000000aपूर्ण,
	अणु0x810, 0x10001331पूर्ण, अणु0x814, 0x020c3d10पूर्ण,
	अणु0x818, 0x02200385पूर्ण, अणु0x81c, 0x00000000पूर्ण,
	अणु0x820, 0x01000100पूर्ण, अणु0x824, 0x00190204पूर्ण,
	अणु0x828, 0x00000000पूर्ण, अणु0x82c, 0x00000000पूर्ण,
	अणु0x830, 0x00000000पूर्ण, अणु0x834, 0x00000000पूर्ण,
	अणु0x838, 0x00000000पूर्ण, अणु0x83c, 0x00000000पूर्ण,
	अणु0x840, 0x00010000पूर्ण, अणु0x844, 0x00000000पूर्ण,
	अणु0x848, 0x00000000पूर्ण, अणु0x84c, 0x00000000पूर्ण,
	अणु0x850, 0x00000000पूर्ण, अणु0x854, 0x00000000पूर्ण,
	अणु0x858, 0x569a11a9पूर्ण, अणु0x85c, 0x01000014पूर्ण,
	अणु0x860, 0x66f60110पूर्ण, अणु0x864, 0x061f0649पूर्ण,
	अणु0x868, 0x00000000पूर्ण, अणु0x86c, 0x27272700पूर्ण,
	अणु0x870, 0x07000760पूर्ण, अणु0x874, 0x25004000पूर्ण,
	अणु0x878, 0x00000808पूर्ण, अणु0x87c, 0x00000000पूर्ण,
	अणु0x880, 0xb0000c1cपूर्ण, अणु0x884, 0x00000001पूर्ण,
	अणु0x888, 0x00000000पूर्ण, अणु0x88c, 0xccc000c0पूर्ण,
	अणु0x890, 0x00000800पूर्ण, अणु0x894, 0xfffffffeपूर्ण,
	अणु0x898, 0x40302010पूर्ण, अणु0x89c, 0x00706050पूर्ण,
	अणु0x900, 0x00000000पूर्ण, अणु0x904, 0x00000023पूर्ण,
	अणु0x908, 0x00000000पूर्ण, अणु0x90c, 0x81121111पूर्ण,
	अणु0x910, 0x00000002पूर्ण, अणु0x914, 0x00000201पूर्ण,
	अणु0xa00, 0x00d047c8पूर्ण, अणु0xa04, 0x80ff800cपूर्ण,
	अणु0xa08, 0x8c838300पूर्ण, अणु0xa0c, 0x2e7f120fपूर्ण,
	अणु0xa10, 0x9500bb78पूर्ण, अणु0xa14, 0x1114d028पूर्ण,
	अणु0xa18, 0x00881117पूर्ण, अणु0xa1c, 0x89140f00पूर्ण,
	अणु0xa20, 0x1a1b0000पूर्ण, अणु0xa24, 0x090e1317पूर्ण,
	अणु0xa28, 0x00000204पूर्ण, अणु0xa2c, 0x00d30000पूर्ण,
	अणु0xa70, 0x101fbf00पूर्ण, अणु0xa74, 0x00000007पूर्ण,
	अणु0xa78, 0x00000900पूर्ण, अणु0xa7c, 0x225b0606पूर्ण,
	अणु0xa80, 0x21806490पूर्ण, अणु0xb2c, 0x00000000पूर्ण,
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
	अणु0xc50, 0x69553420पूर्ण, अणु0xc54, 0x43bc0094पूर्ण,
	अणु0xc58, 0x00013149पूर्ण, अणु0xc5c, 0x00250492पूर्ण,
	अणु0xc60, 0x00000000पूर्ण, अणु0xc64, 0x7112848bपूर्ण,
	अणु0xc68, 0x47c00bffपूर्ण, अणु0xc6c, 0x00000036पूर्ण,
	अणु0xc70, 0x2c7f000dपूर्ण, अणु0xc74, 0x020610dbपूर्ण,
	अणु0xc78, 0x0000001fपूर्ण, अणु0xc7c, 0x00b91612पूर्ण,
	अणु0xc80, 0x390000e4पूर्ण, अणु0xc84, 0x20f60000पूर्ण,
	अणु0xc88, 0x40000100पूर्ण, अणु0xc8c, 0x20200000पूर्ण,
	अणु0xc90, 0x00020e1aपूर्ण, अणु0xc94, 0x00000000पूर्ण,
	अणु0xc98, 0x00020e1aपूर्ण, अणु0xc9c, 0x00007f7fपूर्ण,
	अणु0xca0, 0x00000000पूर्ण, अणु0xca4, 0x000300a0पूर्ण,
	अणु0xca8, 0x00000000पूर्ण, अणु0xcac, 0x00000000पूर्ण,
	अणु0xcb0, 0x00000000पूर्ण, अणु0xcb4, 0x00000000पूर्ण,
	अणु0xcb8, 0x00000000पूर्ण, अणु0xcbc, 0x28000000पूर्ण,
	अणु0xcc0, 0x00000000पूर्ण, अणु0xcc4, 0x00000000पूर्ण,
	अणु0xcc8, 0x00000000पूर्ण, अणु0xccc, 0x00000000पूर्ण,
	अणु0xcd0, 0x00000000पूर्ण, अणु0xcd4, 0x00000000पूर्ण,
	अणु0xcd8, 0x64b22427पूर्ण, अणु0xcdc, 0x00766932पूर्ण,
	अणु0xce0, 0x00222222पूर्ण, अणु0xce4, 0x00000000पूर्ण,
	अणु0xce8, 0x37644302पूर्ण, अणु0xcec, 0x2f97d40cपूर्ण,
	अणु0xd00, 0x00000740पूर्ण, अणु0xd04, 0x40020401पूर्ण,
	अणु0xd08, 0x0000907fपूर्ण, अणु0xd0c, 0x20010201पूर्ण,
	अणु0xd10, 0xa0633333पूर्ण, अणु0xd14, 0x3333bc53पूर्ण,
	अणु0xd18, 0x7a8f5b6fपूर्ण, अणु0xd2c, 0xcc979975पूर्ण,
	अणु0xd30, 0x00000000पूर्ण, अणु0xd34, 0x80608000पूर्ण,
	अणु0xd38, 0x00000000पूर्ण, अणु0xd3c, 0x00127353पूर्ण,
	अणु0xd40, 0x00000000पूर्ण, अणु0xd44, 0x00000000पूर्ण,
	अणु0xd48, 0x00000000पूर्ण, अणु0xd4c, 0x00000000पूर्ण,
	अणु0xd50, 0x6437140aपूर्ण, अणु0xd54, 0x00000000पूर्ण,
	अणु0xd58, 0x00000282पूर्ण, अणु0xd5c, 0x30032064पूर्ण,
	अणु0xd60, 0x4653de68पूर्ण, अणु0xd64, 0x04518a3cपूर्ण,
	अणु0xd68, 0x00002101पूर्ण, अणु0xd6c, 0x2a201c16पूर्ण,
	अणु0xd70, 0x1812362eपूर्ण, अणु0xd74, 0x322c2220पूर्ण,
	अणु0xd78, 0x000e3c24पूर्ण, अणु0xe00, 0x2d2d2d2dपूर्ण,
	अणु0xe04, 0x2d2d2d2dपूर्ण, अणु0xe08, 0x0390272dपूर्ण,
	अणु0xe10, 0x2d2d2d2dपूर्ण, अणु0xe14, 0x2d2d2d2dपूर्ण,
	अणु0xe18, 0x2d2d2d2dपूर्ण, अणु0xe1c, 0x2d2d2d2dपूर्ण,
	अणु0xe28, 0x00000000पूर्ण, अणु0xe30, 0x1000dc1fपूर्ण,
	अणु0xe34, 0x10008c1fपूर्ण, अणु0xe38, 0x02140102पूर्ण,
	अणु0xe3c, 0x681604c2पूर्ण, अणु0xe40, 0x01007c00पूर्ण,
	अणु0xe44, 0x01004800पूर्ण, अणु0xe48, 0xfb000000पूर्ण,
	अणु0xe4c, 0x000028d1पूर्ण, अणु0xe50, 0x1000dc1fपूर्ण,
	अणु0xe54, 0x10008c1fपूर्ण, अणु0xe58, 0x02140102पूर्ण,
	अणु0xe5c, 0x28160d05पूर्ण, अणु0xe60, 0x00000008पूर्ण,
	अणु0xe68, 0x001b2556पूर्ण, अणु0xe6c, 0x00c00096पूर्ण,
	अणु0xe70, 0x00c00096पूर्ण, अणु0xe74, 0x01000056पूर्ण,
	अणु0xe78, 0x01000014पूर्ण, अणु0xe7c, 0x01000056पूर्ण,
	अणु0xe80, 0x01000014पूर्ण, अणु0xe84, 0x00c00096पूर्ण,
	अणु0xe88, 0x01000056पूर्ण, अणु0xe8c, 0x00c00096पूर्ण,
	अणु0xed0, 0x00c00096पूर्ण, अणु0xed4, 0x00c00096पूर्ण,
	अणु0xed8, 0x00c00096पूर्ण, अणु0xedc, 0x000000d6पूर्ण,
	अणु0xee0, 0x000000d6पूर्ण, अणु0xeec, 0x01c00016पूर्ण,
	अणु0xf14, 0x00000003पूर्ण, अणु0xf4c, 0x00000000पूर्ण,
	अणु0xf00, 0x00000300पूर्ण,
	अणु0x820, 0x01000100पूर्ण, अणु0x800, 0x83040000पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8xxx_agc_8723bu_table[] = अणु
	अणु0xc78, 0xfd000001पूर्ण, अणु0xc78, 0xfc010001पूर्ण,
	अणु0xc78, 0xfb020001पूर्ण, अणु0xc78, 0xfa030001पूर्ण,
	अणु0xc78, 0xf9040001पूर्ण, अणु0xc78, 0xf8050001पूर्ण,
	अणु0xc78, 0xf7060001पूर्ण, अणु0xc78, 0xf6070001पूर्ण,
	अणु0xc78, 0xf5080001पूर्ण, अणु0xc78, 0xf4090001पूर्ण,
	अणु0xc78, 0xf30a0001पूर्ण, अणु0xc78, 0xf20b0001पूर्ण,
	अणु0xc78, 0xf10c0001पूर्ण, अणु0xc78, 0xf00d0001पूर्ण,
	अणु0xc78, 0xef0e0001पूर्ण, अणु0xc78, 0xee0f0001पूर्ण,
	अणु0xc78, 0xed100001पूर्ण, अणु0xc78, 0xec110001पूर्ण,
	अणु0xc78, 0xeb120001पूर्ण, अणु0xc78, 0xea130001पूर्ण,
	अणु0xc78, 0xe9140001पूर्ण, अणु0xc78, 0xe8150001पूर्ण,
	अणु0xc78, 0xe7160001पूर्ण, अणु0xc78, 0xe6170001पूर्ण,
	अणु0xc78, 0xe5180001पूर्ण, अणु0xc78, 0xe4190001पूर्ण,
	अणु0xc78, 0xe31a0001पूर्ण, अणु0xc78, 0xa51b0001पूर्ण,
	अणु0xc78, 0xa41c0001पूर्ण, अणु0xc78, 0xa31d0001पूर्ण,
	अणु0xc78, 0x671e0001पूर्ण, अणु0xc78, 0x661f0001पूर्ण,
	अणु0xc78, 0x65200001पूर्ण, अणु0xc78, 0x64210001पूर्ण,
	अणु0xc78, 0x63220001पूर्ण, अणु0xc78, 0x4a230001पूर्ण,
	अणु0xc78, 0x49240001पूर्ण, अणु0xc78, 0x48250001पूर्ण,
	अणु0xc78, 0x47260001पूर्ण, अणु0xc78, 0x46270001पूर्ण,
	अणु0xc78, 0x45280001पूर्ण, अणु0xc78, 0x44290001पूर्ण,
	अणु0xc78, 0x432a0001पूर्ण, अणु0xc78, 0x422b0001पूर्ण,
	अणु0xc78, 0x292c0001पूर्ण, अणु0xc78, 0x282d0001पूर्ण,
	अणु0xc78, 0x272e0001पूर्ण, अणु0xc78, 0x262f0001पूर्ण,
	अणु0xc78, 0x0a300001पूर्ण, अणु0xc78, 0x09310001पूर्ण,
	अणु0xc78, 0x08320001पूर्ण, अणु0xc78, 0x07330001पूर्ण,
	अणु0xc78, 0x06340001पूर्ण, अणु0xc78, 0x05350001पूर्ण,
	अणु0xc78, 0x04360001पूर्ण, अणु0xc78, 0x03370001पूर्ण,
	अणु0xc78, 0x02380001पूर्ण, अणु0xc78, 0x01390001पूर्ण,
	अणु0xc78, 0x013a0001पूर्ण, अणु0xc78, 0x013b0001पूर्ण,
	अणु0xc78, 0x013c0001पूर्ण, अणु0xc78, 0x013d0001पूर्ण,
	अणु0xc78, 0x013e0001पूर्ण, अणु0xc78, 0x013f0001पूर्ण,
	अणु0xc78, 0xfc400001पूर्ण, अणु0xc78, 0xfb410001पूर्ण,
	अणु0xc78, 0xfa420001पूर्ण, अणु0xc78, 0xf9430001पूर्ण,
	अणु0xc78, 0xf8440001पूर्ण, अणु0xc78, 0xf7450001पूर्ण,
	अणु0xc78, 0xf6460001पूर्ण, अणु0xc78, 0xf5470001पूर्ण,
	अणु0xc78, 0xf4480001पूर्ण, अणु0xc78, 0xf3490001पूर्ण,
	अणु0xc78, 0xf24a0001पूर्ण, अणु0xc78, 0xf14b0001पूर्ण,
	अणु0xc78, 0xf04c0001पूर्ण, अणु0xc78, 0xef4d0001पूर्ण,
	अणु0xc78, 0xee4e0001पूर्ण, अणु0xc78, 0xed4f0001पूर्ण,
	अणु0xc78, 0xec500001पूर्ण, अणु0xc78, 0xeb510001पूर्ण,
	अणु0xc78, 0xea520001पूर्ण, अणु0xc78, 0xe9530001पूर्ण,
	अणु0xc78, 0xe8540001पूर्ण, अणु0xc78, 0xe7550001पूर्ण,
	अणु0xc78, 0xe6560001पूर्ण, अणु0xc78, 0xe5570001पूर्ण,
	अणु0xc78, 0xe4580001पूर्ण, अणु0xc78, 0xe3590001पूर्ण,
	अणु0xc78, 0xa65a0001पूर्ण, अणु0xc78, 0xa55b0001पूर्ण,
	अणु0xc78, 0xa45c0001पूर्ण, अणु0xc78, 0xa35d0001पूर्ण,
	अणु0xc78, 0x675e0001पूर्ण, अणु0xc78, 0x665f0001पूर्ण,
	अणु0xc78, 0x65600001पूर्ण, अणु0xc78, 0x64610001पूर्ण,
	अणु0xc78, 0x63620001पूर्ण, अणु0xc78, 0x62630001पूर्ण,
	अणु0xc78, 0x61640001पूर्ण, अणु0xc78, 0x48650001पूर्ण,
	अणु0xc78, 0x47660001पूर्ण, अणु0xc78, 0x46670001पूर्ण,
	अणु0xc78, 0x45680001पूर्ण, अणु0xc78, 0x44690001पूर्ण,
	अणु0xc78, 0x436a0001पूर्ण, अणु0xc78, 0x426b0001पूर्ण,
	अणु0xc78, 0x286c0001पूर्ण, अणु0xc78, 0x276d0001पूर्ण,
	अणु0xc78, 0x266e0001पूर्ण, अणु0xc78, 0x256f0001पूर्ण,
	अणु0xc78, 0x24700001पूर्ण, अणु0xc78, 0x09710001पूर्ण,
	अणु0xc78, 0x08720001पूर्ण, अणु0xc78, 0x07730001पूर्ण,
	अणु0xc78, 0x06740001पूर्ण, अणु0xc78, 0x05750001पूर्ण,
	अणु0xc78, 0x04760001पूर्ण, अणु0xc78, 0x03770001पूर्ण,
	अणु0xc78, 0x02780001पूर्ण, अणु0xc78, 0x01790001पूर्ण,
	अणु0xc78, 0x017a0001पूर्ण, अणु0xc78, 0x017b0001पूर्ण,
	अणु0xc78, 0x017c0001पूर्ण, अणु0xc78, 0x017d0001पूर्ण,
	अणु0xc78, 0x017e0001पूर्ण, अणु0xc78, 0x017f0001पूर्ण,
	अणु0xc50, 0x69553422पूर्ण,
	अणु0xc50, 0x69553420पूर्ण,
	अणु0x824, 0x00390204पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8723bu_radioa_1t_init_table[] = अणु
	अणु0x00, 0x00010000पूर्ण, अणु0xb0, 0x000dffe0पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xb1, 0x00000018पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xb2, 0x00084c00पूर्ण,
	अणु0xb5, 0x0000d2ccपूर्ण, अणु0xb6, 0x000925aaपूर्ण,
	अणु0xb7, 0x00000010पूर्ण, अणु0xb8, 0x0000907fपूर्ण,
	अणु0x5c, 0x00000002पूर्ण, अणु0x7c, 0x00000002पूर्ण,
	अणु0x7e, 0x00000005पूर्ण, अणु0x8b, 0x0006fc00पूर्ण,
	अणु0xb0, 0x000ff9f0पूर्ण, अणु0x1c, 0x000739d2पूर्ण,
	अणु0x1e, 0x00000000पूर्ण, अणु0xdf, 0x00000780पूर्ण,
	अणु0x50, 0x00067435पूर्ण,
	/*
	 * The 8723bu venकरोr driver indicates that bit 8 should be set in
	 * 0x51 क्रम package types TFBGA90, TFBGA80, and TFBGA79. However
	 * they never actually check the package type - and just शेष
	 * to not setting it.
	 */
	अणु0x51, 0x0006b04eपूर्ण,
	अणु0x52, 0x000007d2पूर्ण, अणु0x53, 0x00000000पूर्ण,
	अणु0x54, 0x00050400पूर्ण, अणु0x55, 0x0004026eपूर्ण,
	अणु0xdd, 0x0000004cपूर्ण, अणु0x70, 0x00067435पूर्ण,
	/*
	 * 0x71 has same package type condition as क्रम रेजिस्टर 0x51
	 */
	अणु0x71, 0x0006b04eपूर्ण,
	अणु0x72, 0x000007d2पूर्ण, अणु0x73, 0x00000000पूर्ण,
	अणु0x74, 0x00050400पूर्ण, अणु0x75, 0x0004026eपूर्ण,
	अणु0xef, 0x00000100पूर्ण, अणु0x34, 0x0000add7पूर्ण,
	अणु0x35, 0x00005c00पूर्ण, अणु0x34, 0x00009dd4पूर्ण,
	अणु0x35, 0x00005000पूर्ण, अणु0x34, 0x00008dd1पूर्ण,
	अणु0x35, 0x00004400पूर्ण, अणु0x34, 0x00007dceपूर्ण,
	अणु0x35, 0x00003800पूर्ण, अणु0x34, 0x00006cd1पूर्ण,
	अणु0x35, 0x00004400पूर्ण, अणु0x34, 0x00005cceपूर्ण,
	अणु0x35, 0x00003800पूर्ण, अणु0x34, 0x000048ceपूर्ण,
	अणु0x35, 0x00004400पूर्ण, अणु0x34, 0x000034ceपूर्ण,
	अणु0x35, 0x00003800पूर्ण, अणु0x34, 0x00002451पूर्ण,
	अणु0x35, 0x00004400पूर्ण, अणु0x34, 0x0000144eपूर्ण,
	अणु0x35, 0x00003800पूर्ण, अणु0x34, 0x00000051पूर्ण,
	अणु0x35, 0x00004400पूर्ण, अणु0xef, 0x00000000पूर्ण,
	अणु0xef, 0x00000100पूर्ण, अणु0xed, 0x00000010पूर्ण,
	अणु0x44, 0x0000add7पूर्ण, अणु0x44, 0x00009dd4पूर्ण,
	अणु0x44, 0x00008dd1पूर्ण, अणु0x44, 0x00007dceपूर्ण,
	अणु0x44, 0x00006cc1पूर्ण, अणु0x44, 0x00005cceपूर्ण,
	अणु0x44, 0x000044d1पूर्ण, अणु0x44, 0x000034ceपूर्ण,
	अणु0x44, 0x00002451पूर्ण, अणु0x44, 0x0000144eपूर्ण,
	अणु0x44, 0x00000051पूर्ण, अणु0xef, 0x00000000पूर्ण,
	अणु0xed, 0x00000000पूर्ण, अणु0x7f, 0x00020080पूर्ण,
	अणु0xef, 0x00002000पूर्ण, अणु0x3b, 0x000380efपूर्ण,
	अणु0x3b, 0x000302feपूर्ण, अणु0x3b, 0x00028ce6पूर्ण,
	अणु0x3b, 0x000200bcपूर्ण, अणु0x3b, 0x000188a5पूर्ण,
	अणु0x3b, 0x00010fbcपूर्ण, अणु0x3b, 0x00008f71पूर्ण,
	अणु0x3b, 0x00000900पूर्ण, अणु0xef, 0x00000000पूर्ण,
	अणु0xed, 0x00000001पूर्ण, अणु0x40, 0x000380efपूर्ण,
	अणु0x40, 0x000302feपूर्ण, अणु0x40, 0x00028ce6पूर्ण,
	अणु0x40, 0x000200bcपूर्ण, अणु0x40, 0x000188a5पूर्ण,
	अणु0x40, 0x00010fbcपूर्ण, अणु0x40, 0x00008f71पूर्ण,
	अणु0x40, 0x00000900पूर्ण, अणु0xed, 0x00000000पूर्ण,
	अणु0x82, 0x00080000पूर्ण, अणु0x83, 0x00008000पूर्ण,
	अणु0x84, 0x00048d80पूर्ण, अणु0x85, 0x00068000पूर्ण,
	अणु0xa2, 0x00080000पूर्ण, अणु0xa3, 0x00008000पूर्ण,
	अणु0xa4, 0x00048d80पूर्ण, अणु0xa5, 0x00068000पूर्ण,
	अणु0xed, 0x00000002पूर्ण, अणु0xef, 0x00000002पूर्ण,
	अणु0x56, 0x00000032पूर्ण, अणु0x76, 0x00000032पूर्ण,
	अणु0x01, 0x00000780पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल व्योम rtl8723bu_ग_लिखो_btreg(काष्ठा rtl8xxxu_priv *priv, u8 reg, u8 data)
अणु
	काष्ठा h2c_cmd h2c;
	पूर्णांक reqnum = 0;

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.bt_mp_oper.cmd = H2C_8723B_BT_MP_OPER;
	h2c.bt_mp_oper.operreq = 0 | (reqnum << 4);
	h2c.bt_mp_oper.opcode = BT_MP_OP_WRITE_REG_VALUE;
	h2c.bt_mp_oper.data = data;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.bt_mp_oper));

	reqnum++;
	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.bt_mp_oper.cmd = H2C_8723B_BT_MP_OPER;
	h2c.bt_mp_oper.operreq = 0 | (reqnum << 4);
	h2c.bt_mp_oper.opcode = BT_MP_OP_WRITE_REG_VALUE;
	h2c.bt_mp_oper.addr = reg;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.bt_mp_oper));
पूर्ण

अटल व्योम rtl8723bu_reset_8051(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 sys_func;

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL);
	val8 &= ~BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	sys_func = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	sys_func &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, sys_func);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL);
	val8 &= ~BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_RSV_CTRL + 1);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL + 1, val8);

	sys_func |= SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, sys_func);
पूर्ण

अटल व्योम
rtl8723b_set_tx_घातer(काष्ठा rtl8xxxu_priv *priv, पूर्णांक channel, bool ht40)
अणु
	u32 val32, ofdm, mcs;
	u8 cck, ofdmbase, mcsbase;
	पूर्णांक group, tx_idx;

	tx_idx = 0;
	group = rtl8xxxu_gen2_channel_to_group(channel);

	cck = priv->cck_tx_घातer_index_B[group];
	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_A_CCK1_MCS32);
	val32 &= 0xffff00ff;
	val32 |= (cck << 8);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_CCK1_MCS32, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
	val32 &= 0xff;
	val32 |= ((cck << 8) | (cck << 16) | (cck << 24));
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

	ofdmbase = priv->ht40_1s_tx_घातer_index_B[group];
	ofdmbase += priv->ofdm_tx_घातer_dअगरf[tx_idx].b;
	ofdm = ofdmbase | ofdmbase << 8 | ofdmbase << 16 | ofdmbase << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE18_06, ofdm);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE54_24, ofdm);

	mcsbase = priv->ht40_1s_tx_घातer_index_B[group];
	अगर (ht40)
		mcsbase += priv->ht40_tx_घातer_dअगरf[tx_idx++].b;
	अन्यथा
		mcsbase += priv->ht20_tx_घातer_dअगरf[tx_idx++].b;
	mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS03_MCS00, mcs);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS07_MCS04, mcs);
पूर्ण

अटल पूर्णांक rtl8723bu_parse_efuse(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8723bu_efuse *efuse = &priv->efuse_wअगरi.efuse8723bu;
	पूर्णांक i;

	अगर (efuse->rtl_id != cpu_to_le16(0x8129))
		वापस -EINVAL;

	ether_addr_copy(priv->mac_addr, efuse->mac_addr);

	स_नकल(priv->cck_tx_घातer_index_A, efuse->tx_घातer_index_A.cck_base,
	       माप(efuse->tx_घातer_index_A.cck_base));
	स_नकल(priv->cck_tx_घातer_index_B, efuse->tx_घातer_index_B.cck_base,
	       माप(efuse->tx_घातer_index_B.cck_base));

	स_नकल(priv->ht40_1s_tx_घातer_index_A,
	       efuse->tx_घातer_index_A.ht40_base,
	       माप(efuse->tx_घातer_index_A.ht40_base));
	स_नकल(priv->ht40_1s_tx_घातer_index_B,
	       efuse->tx_घातer_index_B.ht40_base,
	       माप(efuse->tx_घातer_index_B.ht40_base));

	priv->ofdm_tx_घातer_dअगरf[0].a =
		efuse->tx_घातer_index_A.ht20_ofdm_1s_dअगरf.a;
	priv->ofdm_tx_घातer_dअगरf[0].b =
		efuse->tx_घातer_index_B.ht20_ofdm_1s_dअगरf.a;

	priv->ht20_tx_घातer_dअगरf[0].a =
		efuse->tx_घातer_index_A.ht20_ofdm_1s_dअगरf.b;
	priv->ht20_tx_घातer_dअगरf[0].b =
		efuse->tx_घातer_index_B.ht20_ofdm_1s_dअगरf.b;

	priv->ht40_tx_घातer_dअगरf[0].a = 0;
	priv->ht40_tx_घातer_dअगरf[0].b = 0;

	क्रम (i = 1; i < RTL8723B_TX_COUNT; i++) अणु
		priv->ofdm_tx_घातer_dअगरf[i].a =
			efuse->tx_घातer_index_A.pwr_dअगरf[i - 1].ofdm;
		priv->ofdm_tx_घातer_dअगरf[i].b =
			efuse->tx_घातer_index_B.pwr_dअगरf[i - 1].ofdm;

		priv->ht20_tx_घातer_dअगरf[i].a =
			efuse->tx_घातer_index_A.pwr_dअगरf[i - 1].ht20;
		priv->ht20_tx_घातer_dअगरf[i].b =
			efuse->tx_घातer_index_B.pwr_dअगरf[i - 1].ht20;

		priv->ht40_tx_घातer_dअगरf[i].a =
			efuse->tx_घातer_index_A.pwr_dअगरf[i - 1].ht40;
		priv->ht40_tx_घातer_dअगरf[i].b =
			efuse->tx_घातer_index_B.pwr_dअगरf[i - 1].ht40;
	पूर्ण

	priv->has_xtalk = 1;
	priv->xtalk = priv->efuse_wअगरi.efuse8723bu.xtal_k & 0x3f;

	dev_info(&priv->udev->dev, "Vendor: %.7s\n", efuse->venकरोr_name);
	dev_info(&priv->udev->dev, "Product: %.41s\n", efuse->device_name);

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_EFUSE) अणु
		पूर्णांक i;
		अचिन्हित अक्षर *raw = priv->efuse_wअगरi.raw;

		dev_info(&priv->udev->dev,
			 "%s: dumping efuse (0x%02zx bytes):\n",
			 __func__, माप(काष्ठा rtl8723bu_efuse));
		क्रम (i = 0; i < माप(काष्ठा rtl8723bu_efuse); i += 8)
			dev_info(&priv->udev->dev, "%02x: %8ph\n", i, &raw[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8723bu_load_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	अक्षर *fw_name;
	पूर्णांक ret;

	अगर (priv->enable_bluetooth)
		fw_name = "rtlwifi/rtl8723bu_bt.bin";
	अन्यथा
		fw_name = "rtlwifi/rtl8723bu_nic.bin";

	ret = rtl8xxxu_load_firmware(priv, fw_name);
	वापस ret;
पूर्ण

अटल व्योम rtl8723bu_init_phy_bb(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;

	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB | SYS_FUNC_DIO_RF;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00);

	/* 6. 0x1f[7:0] = 0x07 */
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, val8);

	/* Why? */
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC, 0xe3);
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_XTAL_CTRL + 1, 0x80);
	rtl8xxxu_init_phy_regs(priv, rtl8723b_phy_1t_init_table);

	rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8723bu_table);
पूर्ण

अटल पूर्णांक rtl8723bu_init_phy_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8723bu_radioa_1t_init_table, RF_A);
	/*
	 * PHY LCK
	 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, 0xb0, 0xdfbe0);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_MODE_AG, 0x8c01);
	msleep(200);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, 0xb0, 0xdffe0);

	वापस ret;
पूर्ण

अटल व्योम rtl8723bu_phy_init_antenna_selection(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_PAD_CTRL1);
	val32 &= ~(BIT(20) | BIT(24));
	rtl8xxxu_ग_लिखो32(priv, REG_PAD_CTRL1, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_GPIO_MUXCFG);
	val32 &= ~BIT(4);
	rtl8xxxu_ग_लिखो32(priv, REG_GPIO_MUXCFG, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_GPIO_MUXCFG);
	val32 |= BIT(3);
	rtl8xxxu_ग_लिखो32(priv, REG_GPIO_MUXCFG, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_LEDCFG0);
	val32 |= BIT(24);
	rtl8xxxu_ग_लिखो32(priv, REG_LEDCFG0, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_LEDCFG0);
	val32 &= ~BIT(23);
	rtl8xxxu_ग_लिखो32(priv, REG_LEDCFG0, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RFE_BUFFER);
	val32 |= (BIT(0) | BIT(1));
	rtl8xxxu_ग_लिखो32(priv, REG_RFE_BUFFER, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RFE_CTRL_ANTA_SRC);
	val32 &= 0xffffff00;
	val32 |= 0x77;
	rtl8xxxu_ग_लिखो32(priv, REG_RFE_CTRL_ANTA_SRC, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_PWR_DATA);
	val32 |= PWR_DATA_EEPRPAD_RFE_CTRL_EN;
	rtl8xxxu_ग_लिखो32(priv, REG_PWR_DATA, val32);
पूर्ण

अटल पूर्णांक rtl8723bu_iqk_path_a(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_e94, reg_e9c, path_sel, val32;
	पूर्णांक result = 0;

	path_sel = rtl8xxxu_पढ़ो32(priv, REG_S0S1_PATH_SWITCH);

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/*
	 * Enable path A PA in TX IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x20000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0003f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xc7f87);

	/*
	 * Tx IQK setting
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x821403ea);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x28110000);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x82110000);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x28110000);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x00462911);

	/*
	 * Enter IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	val32 |= 0x80800000;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/*
	 * The venकरोr driver indicates the USB module is always using
	 * S0S1 path 1 क्रम the 8723bu. This may be dअगरferent क्रम 8192eu
	 */
	अगर (priv->rf_paths > 1)
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000000);
	अन्यथा
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Bit 12 seems to be BT_GRANT, and is only found in the 8723bu.
	 * No trace of this in the 8192eu or 8188eu venकरोr drivers.
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00000800);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Restore Ant Path */
	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, path_sel);
#अगर_घोषित RTL8723BU_BT
	/* GNT_BT = 1 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00001800);
#पूर्ण_अगर

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_A);

	val32 = (reg_e9c >> 16) & 0x3ff;
	अगर (val32 & 0x200)
		val32 = 0x400 - val32;

	अगर (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000) &&
	    ((reg_e94 & 0x03ff0000)  < 0x01100000) &&
	    ((reg_e94 & 0x03ff0000)  > 0x00f00000) &&
	    val32 < 0xf)
		result |= 0x01;
	अन्यथा	/* If TX not OK, ignore RX */
		जाओ out;

out:
	वापस result;
पूर्ण

अटल पूर्णांक rtl8723bu_rx_iqk_path_a(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_ea4, reg_eac, reg_e94, reg_e9c, path_sel, val32;
	पूर्णांक result = 0;

	path_sel = rtl8xxxu_पढ़ो32(priv, REG_S0S1_PATH_SWITCH);

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/*
	 * Enable path A PA in TX IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0001f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xf7fb7);

	/*
	 * Tx IQK setting
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82160ff0);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x28110000);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x82110000);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x28110000);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a911);

	/*
	 * Enter IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	val32 |= 0x80800000;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/*
	 * The venकरोr driver indicates the USB module is always using
	 * S0S1 path 1 क्रम the 8723bu. This may be dअगरferent क्रम 8192eu
	 */
	अगर (priv->rf_paths > 1)
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000000);
	अन्यथा
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Bit 12 seems to be BT_GRANT, and is only found in the 8723bu.
	 * No trace of this in the 8192eu or 8188eu venकरोr drivers.
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00000800);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Restore Ant Path */
	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, path_sel);
#अगर_घोषित RTL8723BU_BT
	/* GNT_BT = 1 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00001800);
#पूर्ण_अगर

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_A);

	val32 = (reg_e9c >> 16) & 0x3ff;
	अगर (val32 & 0x200)
		val32 = 0x400 - val32;

	अगर (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000) &&
	    ((reg_e94 & 0x03ff0000)  < 0x01100000) &&
	    ((reg_e94 & 0x03ff0000)  > 0x00f00000) &&
	    val32 < 0xf)
		result |= 0x01;
	अन्यथा	/* If TX not OK, ignore RX */
		जाओ out;

	val32 = 0x80007c00 | (reg_e94 &0x3ff0000) |
		((reg_e9c & 0x3ff0000) >> 16);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, val32);

	/*
	 * Modअगरy RX IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);
	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0001f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xf7d77);

	/*
	 * PA, PAD setting
	 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0xf80);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_55, 0x4021f);

	/*
	 * RX IQK setting
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82110000);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x2816001f);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x82110000);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x28110000);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a8d1);

	/*
	 * Enter IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	val32 |= 0x80800000;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	अगर (priv->rf_paths > 1)
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000000);
	अन्यथा
		rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Disable BT
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00000800);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Restore Ant Path */
	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, path_sel);
#अगर_घोषित RTL8723BU_BT
	/* GNT_BT = 1 */
	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, 0x00001800);
#पूर्ण_अगर

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_ea4 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_A_2);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x780);

	val32 = (reg_eac >> 16) & 0x3ff;
	अगर (val32 & 0x200)
		val32 = 0x400 - val32;

	अगर (!(reg_eac & BIT(27)) &&
	    ((reg_ea4 & 0x03ff0000) != 0x01320000) &&
	    ((reg_eac & 0x03ff0000) != 0x00360000) &&
	    ((reg_ea4 & 0x03ff0000)  < 0x01100000) &&
	    ((reg_ea4 & 0x03ff0000)  > 0x00f00000) &&
	    val32 < 0xf)
		result |= 0x02;
	अन्यथा	/* If TX not OK, ignore RX */
		जाओ out;
out:
	वापस result;
पूर्ण

अटल व्योम rtl8723bu_phy_iqcalibrate(काष्ठा rtl8xxxu_priv *priv,
				      पूर्णांक result[][8], पूर्णांक t)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	u32 i, val32;
	पूर्णांक path_a_ok /*, path_b_ok */;
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
	u8 xa_agc = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_AGC_CORE1) & 0xff;
	u8 xb_agc = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_AGC_CORE1) & 0xff;

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

	/* MAC settings */
	rtl8xxxu_mac_calibration(priv, iqk_mac_regs, priv->mac_backup);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_CCK0_AFE_SETTING);
	val32 |= 0x0f000000;
	rtl8xxxu_ग_लिखो32(priv, REG_CCK0_AFE_SETTING, val32);

	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TRX_PATH_ENABLE, 0x03a05600);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_TR_MUX_PAR, 0x000800e4);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XCD_RF_SW_CTRL, 0x22204000);

	/*
	 * RX IQ calibration setting क्रम 8723B D cut large current issue
	 * when leaving IPS
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0001f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xf7fb7);

	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_ED);
	val32 |= 0x20;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_ED, val32);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_43, 0x60fbd);

	क्रम (i = 0; i < retry; i++) अणु
		path_a_ok = rtl8723bu_iqk_path_a(priv);
		अगर (path_a_ok == 0x01) अणु
			val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
			val32 &= 0x000000ff;
			rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_BEFORE_IQK_A);
			result[t][0] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_TX_POWER_AFTER_IQK_A);
			result[t][1] = (val32 >> 16) & 0x3ff;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!path_a_ok)
		dev_dbg(dev, "%s: Path A TX IQK failed!\n", __func__);

	क्रम (i = 0; i < retry; i++) अणु
		path_a_ok = rtl8723bu_rx_iqk_path_a(priv);
		अगर (path_a_ok == 0x03) अणु
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_RX_POWER_BEFORE_IQK_A_2);
			result[t][2] = (val32 >> 16) & 0x3ff;
			val32 = rtl8xxxu_पढ़ो32(priv,
						REG_RX_POWER_AFTER_IQK_A_2);
			result[t][3] = (val32 >> 16) & 0x3ff;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!path_a_ok)
		dev_dbg(dev, "%s: Path A RX IQK failed!\n", __func__);

	अगर (priv->tx_paths > 1) अणु
#अगर 1
		dev_warn(dev, "%s: Path B not supported\n", __func__);
#अन्यथा

		/*
		 * Path A पूर्णांकo standby
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
		val32 &= 0x000000ff;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC, 0x10000);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
		val32 &= 0x000000ff;
		val32 |= 0x80800000;
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

		/* Turn Path B ADDA on */
		rtl8xxxu_path_adda_on(priv, adda_regs, false);

		क्रम (i = 0; i < retry; i++) अणु
			path_b_ok = rtl8xxxu_iqk_path_b(priv);
			अगर (path_b_ok == 0x03) अणु
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
				result[t][4] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);
				result[t][5] = (val32 >> 16) & 0x3ff;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!path_b_ok)
			dev_dbg(dev, "%s: Path B IQK failed!\n", __func__);

		क्रम (i = 0; i < retry; i++) अणु
			path_b_ok = rtl8723bu_rx_iqk_path_b(priv);
			अगर (path_a_ok == 0x03) अणु
				val32 = rtl8xxxu_पढ़ो32(priv,
							REG_RX_POWER_BEFORE_IQK_B_2);
				result[t][6] = (val32 >> 16) & 0x3ff;
				val32 = rtl8xxxu_पढ़ो32(priv,
							REG_RX_POWER_AFTER_IQK_B_2);
				result[t][7] = (val32 >> 16) & 0x3ff;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!path_b_ok)
			dev_dbg(dev, "%s: Path B RX IQK failed!\n", __func__);
#पूर्ण_अगर
	पूर्ण

	/* Back to BB mode, load original value */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);

	अगर (t) अणु
		/* Reload ADDA घातer saving parameters */
		rtl8xxxu_restore_regs(priv, adda_regs, priv->adda_backup,
				      RTL8XXXU_ADDA_REGS);

		/* Reload MAC parameters */
		rtl8xxxu_restore_mac_regs(priv, iqk_mac_regs, priv->mac_backup);

		/* Reload BB parameters */
		rtl8xxxu_restore_regs(priv, iqk_bb_regs,
				      priv->bb_backup, RTL8XXXU_BB_REGS);

		/* Restore RX initial gain */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XA_AGC_CORE1);
		val32 &= 0xffffff00;
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_AGC_CORE1, val32 | 0x50);
		rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XA_AGC_CORE1, val32 | xa_agc);

		अगर (priv->tx_paths > 1) अणु
			val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_XB_AGC_CORE1);
			val32 &= 0xffffff00;
			rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_AGC_CORE1,
					 val32 | 0x50);
			rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_XB_AGC_CORE1,
					 val32 | xb_agc);
		पूर्ण

		/* Load 0xe30 IQC शेष value */
		rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x01008c00);
		rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x01008c00);
	पूर्ण
पूर्ण

अटल व्योम rtl8723bu_phy_iq_calibrate(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक result[4][8];	/* last is final result */
	पूर्णांक i, candidate;
	bool path_a_ok, path_b_ok;
	u32 reg_e94, reg_e9c, reg_ea4, reg_eac;
	u32 reg_eb4, reg_ebc, reg_ec4, reg_ecc;
	u32 val32, bt_control;
	s32 reg_पंचांगp = 0;
	bool simu;

	rtl8xxxu_gen2_prepare_calibrate(priv, 1);

	स_रखो(result, 0, माप(result));
	candidate = -1;

	path_a_ok = false;
	path_b_ok = false;

	bt_control = rtl8xxxu_पढ़ो32(priv, REG_BT_CONTROL_8723BU);

	क्रम (i = 0; i < 3; i++) अणु
		rtl8723bu_phy_iqcalibrate(priv, result, i);

		अगर (i == 1) अणु
			simu = rtl8xxxu_gen2_simularity_compare(priv,
								result, 0, 1);
			अगर (simu) अणु
				candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 2) अणु
			simu = rtl8xxxu_gen2_simularity_compare(priv,
								result, 0, 2);
			अगर (simu) अणु
				candidate = 0;
				अवरोध;
			पूर्ण

			simu = rtl8xxxu_gen2_simularity_compare(priv,
								result, 1, 2);
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

	rtl8xxxu_ग_लिखो32(priv, REG_BT_CONTROL_8723BU, bt_control);

	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x18000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0001f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xe6177);
	val32 = rtl8xxxu_पढ़ो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_ED);
	val32 |= 0x20;
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_ED, val32);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, 0x43, 0x300bd);

	अगर (priv->rf_paths > 1)
		dev_dbg(dev, "%s: 8723BU 2T not supported\n", __func__);

	rtl8xxxu_gen2_prepare_calibrate(priv, 0);
पूर्ण

अटल पूर्णांक rtl8723bu_active_to_emu(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक count, ret = 0;

	/* Turn off RF */
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, 0);

	/* Enable rising edge triggering पूर्णांकerrupt */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_GPIO_INTM);
	val16 &= ~GPIO_INTM_EDGE_TRIG_IRQ;
	rtl8xxxu_ग_लिखो16(priv, REG_GPIO_INTM, val16);

	/* Release WLON reset 0x04[16]= 1*/
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 |= APS_FSMCO_WLON_RESET;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

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

	/* Enable BT control XTAL setting */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_AFE_MISC);
	val8 &= ~AFE_MISC_WL_XTAL_CTRL;
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_MISC, val8);

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

अटल पूर्णांक rtl8723b_emu_to_active(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;
	पूर्णांक count, ret = 0;

	/* 0x20[0] = 1 enable LDOA12 MACRO block क्रम all पूर्णांकerface */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_LDOA15_CTRL);
	val8 |= LDOA15_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_LDOA15_CTRL, val8);

	/* 0x67[0] = 0 to disable BT_GPS_SEL pins*/
	val8 = rtl8xxxu_पढ़ो8(priv, 0x0067);
	val8 &= ~BIT(4);
	rtl8xxxu_ग_लिखो8(priv, 0x0067, val8);

	mdelay(1);

	/* 0x00[5] = 0 release analog Ips to digital, 1:isolation */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_ISO_CTRL);
	val8 &= ~SYS_ISO_ANALOG_IPS;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_ISO_CTRL, val8);

	/* Disable SW LPS 0x04[10]= 0 */
	val32 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO);
	val32 &= ~APS_FSMCO_SW_LPS;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	/* Wait until 0x04[17] = 1 घातer पढ़ोy */
	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
		अगर (val32 & BIT(17))
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (!count) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* We should be able to optimize the following three entries पूर्णांकo one */

	/* Release WLON reset 0x04[16]= 1*/
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 |= APS_FSMCO_WLON_RESET;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	/* Disable HWPDN 0x04[15]= 0*/
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 &= ~APS_FSMCO_HW_POWERDOWN;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	/* Disable WL suspend*/
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 &= ~(APS_FSMCO_HW_SUSPEND | APS_FSMCO_PCIE);
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	/* Set, then poll until 0 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 |= APS_FSMCO_MAC_ENABLE;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
		अगर ((val32 & APS_FSMCO_MAC_ENABLE) == 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण

	अगर (!count) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* Enable WL control XTAL setting */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_AFE_MISC);
	val8 |= AFE_MISC_WL_XTAL_CTRL;
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_MISC, val8);

	/* Enable falling edge triggering पूर्णांकerrupt */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_INTM + 1);
	val8 |= BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_INTM + 1, val8);

	/* Enable GPIO9 पूर्णांकerrupt mode */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_IO_SEL_2 + 1);
	val8 |= BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_IO_SEL_2 + 1, val8);

	/* Enable GPIO9 input mode */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_IO_SEL_2);
	val8 &= ~BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_IO_SEL_2, val8);

	/* Enable HSISR GPIO[C:0] पूर्णांकerrupt */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_HSIMR);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_HSIMR, val8);

	/* Enable HSISR GPIO9 पूर्णांकerrupt */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_HSIMR + 2);
	val8 |= BIT(1);
	rtl8xxxu_ग_लिखो8(priv, REG_HSIMR + 2, val8);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_MULTI_FUNC_CTRL);
	val8 |= MULTI_WIFI_HW_ROF_EN;
	rtl8xxxu_ग_लिखो8(priv, REG_MULTI_FUNC_CTRL, val8);

	/* For GPIO9 पूर्णांकernal pull high setting BIT(14) */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_MULTI_FUNC_CTRL + 1);
	val8 |= BIT(6);
	rtl8xxxu_ग_लिखो8(priv, REG_MULTI_FUNC_CTRL + 1, val8);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8723bu_घातer_on(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक ret;

	rtl8xxxu_disabled_to_emu(priv);

	ret = rtl8723b_emu_to_active(priv);
	अगर (ret)
		जाओ निकास;

	/*
	 * Enable MAC DMA/WMAC/SCHEDULE/SEC block
	 * Set CR bit10 to enable 32k calibration.
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 |= (CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE |
		  CR_TXDMA_ENABLE | CR_RXDMA_ENABLE |
		  CR_PROTOCOL_ENABLE | CR_SCHEDULE_ENABLE |
		  CR_MAC_TX_ENABLE | CR_MAC_RX_ENABLE |
		  CR_SECURITY_ENABLE | CR_CALTIMER_ENABLE);
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	/*
	 * BT coexist घातer on settings. This is identical क्रम 1 and 2
	 * antenna parts.
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_PAD_CTRL1 + 3, 0x20);

	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BBRSTB | SYS_FUNC_BB_GLB_RSTN;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	rtl8xxxu_ग_लिखो8(priv, REG_BT_CONTROL_8723BU + 1, 0x18);
	rtl8xxxu_ग_लिखो8(priv, REG_WLAN_ACT_CONTROL_8723B, 0x04);
	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x00);
	/* Antenna inverse */
	rtl8xxxu_ग_लिखो8(priv, 0xfe08, 0x01);

	val16 = rtl8xxxu_पढ़ो16(priv, REG_PWR_DATA);
	val16 |= PWR_DATA_EEPRPAD_RFE_CTRL_EN;
	rtl8xxxu_ग_लिखो16(priv, REG_PWR_DATA, val16);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_LEDCFG0);
	val32 |= LEDCFG0_DPDT_SELECT;
	rtl8xxxu_ग_लिखो32(priv, REG_LEDCFG0, val32);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_PAD_CTRL1);
	val8 &= ~PAD_CTRL1_SW_DPDT_SEL_DATA;
	rtl8xxxu_ग_लिखो8(priv, REG_PAD_CTRL1, val8);
निकास:
	वापस ret;
पूर्ण

अटल व्योम rtl8723bu_घातer_off(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;

	rtl8xxxu_flush_fअगरo(priv);

	/*
	 * Disable TX report समयr
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_TX_REPORT_CTRL);
	val8 &= ~TX_REPORT_CTRL_TIMER_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_TX_REPORT_CTRL, val8);

	rtl8xxxu_ग_लिखो8(priv, REG_CR, 0x0000);

	rtl8xxxu_active_to_lps(priv);

	/* Reset Firmware अगर running in RAM */
	अगर (rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);

	/* Reset MCU */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	/* Reset MCU पढ़ोy status */
	rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, 0x00);

	rtl8723bu_active_to_emu(priv);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 |= BIT(3); /* APS_FSMCO_HW_SUSPEND */
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* 0x48[16] = 1 to enable GPIO9 as EXT wakeup */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_INTM + 2);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_INTM + 2, val8);
पूर्ण

अटल व्योम rtl8723b_enable_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा h2c_cmd h2c;
	u32 val32;
	u8 val8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RX_WAIT_CCA);
	val32 |= (BIT(22) | BIT(23));
	rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, val32);

	/*
	 * No indication anywhere as to what 0x0790 करोes. The 2 antenna
	 * venकरोr code preserves bits 6-7 here.
	 */
	rtl8xxxu_ग_लिखो8(priv, 0x0790, 0x05);
	/*
	 * 0x0778 seems to be related to enabling the number of antennas
	 * In the venकरोr driver halbtc8723b2ant_InitHwConfig() sets it
	 * to 0x03, जबतक halbtc8723b1ant_InitHwConfig() sets it to 0x01
	 */
	rtl8xxxu_ग_लिखो8(priv, 0x0778, 0x01);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_MUXCFG);
	val8 |= BIT(5);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_MUXCFG, val8);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_IQADJ_G1, 0x780);

	rtl8723bu_ग_लिखो_btreg(priv, 0x3c, 0x15); /* BT TRx Mask on */

	/*
	 * Set BT grant to low
	 */
	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.bt_grant.cmd = H2C_8723B_BT_GRANT;
	h2c.bt_grant.data = 0;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.bt_grant));

	/*
	 * WLAN action by PTA
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_WLAN_ACT_CONTROL_8723B, 0x0c);

	/*
	 * BT select S0/S1 controlled by WiFi
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, 0x0067);
	val8 |= BIT(5);
	rtl8xxxu_ग_लिखो8(priv, 0x0067, val8);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_PWR_DATA);
	val32 |= PWR_DATA_EEPRPAD_RFE_CTRL_EN;
	rtl8xxxu_ग_लिखो32(priv, REG_PWR_DATA, val32);

	/*
	 * Bits 6/7 are marked in/out ... but क्रम what?
	 */
	rtl8xxxu_ग_लिखो8(priv, 0x0974, 0xff);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RFE_BUFFER);
	val32 |= (BIT(0) | BIT(1));
	rtl8xxxu_ग_लिखो32(priv, REG_RFE_BUFFER, val32);

	rtl8xxxu_ग_लिखो8(priv, REG_RFE_CTRL_ANTA_SRC, 0x77);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_LEDCFG0);
	val32 &= ~BIT(24);
	val32 |= BIT(23);
	rtl8xxxu_ग_लिखो32(priv, REG_LEDCFG0, val32);

	/*
	 * Fix बाह्यal चयन Main->S1, Aux->S0
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_PAD_CTRL1);
	val8 &= ~BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_PAD_CTRL1, val8);

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.ant_sel_rsv.cmd = H2C_8723B_ANT_SEL_RSV;
	h2c.ant_sel_rsv.ant_inverse = 1;
	h2c.ant_sel_rsv.पूर्णांक_चयन_type = 0;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.ant_sel_rsv));

	/*
	 * Dअगरferent settings per dअगरferent antenna position.
	 *      Antenna Position:   | Normal   Inverse
	 * --------------------------------------------------
	 * Antenna चयन to BT:    |  0x280,   0x00
	 * Antenna चयन to WiFi:  |  0x0,     0x280
	 * Antenna चयन to PTA:   |  0x200,   0x80
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_S0S1_PATH_SWITCH, 0x80);

	/*
	 * Software control, antenna at WiFi side
	 */
	rtl8723bu_set_ps_tdma(priv, 0x08, 0x00, 0x00, 0x00, 0x00);

	rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE1, 0x55555555);
	rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE2, 0x55555555);
	rtl8xxxu_ग_लिखो32(priv, REG_BT_COEX_TABLE3, 0x00ffffff);
	rtl8xxxu_ग_लिखो8(priv, REG_BT_COEX_TABLE4, 0x03);

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.bt_info.cmd = H2C_8723B_BT_INFO;
	h2c.bt_info.data = BIT(0);
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.bt_info));

	स_रखो(&h2c, 0, माप(काष्ठा h2c_cmd));
	h2c.ignore_wlan.cmd = H2C_8723B_BT_IGNORE_WLANACT;
	h2c.ignore_wlan.data = 0;
	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, माप(h2c.ignore_wlan));
पूर्ण

अटल व्योम rtl8723bu_init_aggregation(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 agg_rx;
	u8 agg_ctrl;

	/*
	 * For now simply disable RX aggregation
	 */
	agg_ctrl = rtl8xxxu_पढ़ो8(priv, REG_TRXDMA_CTRL);
	agg_ctrl &= ~TRXDMA_CTRL_RXDMA_AGG_EN;

	agg_rx = rtl8xxxu_पढ़ो32(priv, REG_RXDMA_AGG_PG_TH);
	agg_rx &= ~RXDMA_USB_AGG_ENABLE;
	agg_rx &= ~0xff0f;

	rtl8xxxu_ग_लिखो8(priv, REG_TRXDMA_CTRL, agg_ctrl);
	rtl8xxxu_ग_लिखो32(priv, REG_RXDMA_AGG_PG_TH, agg_rx);
पूर्ण

अटल व्योम rtl8723bu_init_statistics(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;

	/* Time duration क्रम NHM unit: 4us, 0x2710=40ms */
	rtl8xxxu_ग_लिखो16(priv, REG_NHM_TIMER_8723B + 2, 0x2710);
	rtl8xxxu_ग_लिखो16(priv, REG_NHM_TH9_TH10_8723B + 2, 0xffff);
	rtl8xxxu_ग_लिखो32(priv, REG_NHM_TH3_TO_TH0_8723B, 0xffffff52);
	rtl8xxxu_ग_लिखो32(priv, REG_NHM_TH7_TO_TH4_8723B, 0xffffffff);
	/* TH8 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_IQK);
	val32 |= 0xff;
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, val32);
	/* Enable CCK */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_NHM_TH9_TH10_8723B);
	val32 |= BIT(8) | BIT(9) | BIT(10);
	rtl8xxxu_ग_लिखो32(priv, REG_NHM_TH9_TH10_8723B, val32);
	/* Max घातer amongst all RX antennas */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_OFDM0_FA_RSTC);
	val32 |= BIT(7);
	rtl8xxxu_ग_लिखो32(priv, REG_OFDM0_FA_RSTC, val32);
पूर्ण

काष्ठा rtl8xxxu_fileops rtl8723bu_fops = अणु
	.parse_efuse = rtl8723bu_parse_efuse,
	.load_firmware = rtl8723bu_load_firmware,
	.घातer_on = rtl8723bu_घातer_on,
	.घातer_off = rtl8723bu_घातer_off,
	.reset_8051 = rtl8723bu_reset_8051,
	.llt_init = rtl8xxxu_स्वतः_llt_table,
	.init_phy_bb = rtl8723bu_init_phy_bb,
	.init_phy_rf = rtl8723bu_init_phy_rf,
	.phy_init_antenna_selection = rtl8723bu_phy_init_antenna_selection,
	.phy_iq_calibrate = rtl8723bu_phy_iq_calibrate,
	.config_channel = rtl8xxxu_gen2_config_channel,
	.parse_rx_desc = rtl8xxxu_parse_rxdesc24,
	.init_aggregation = rtl8723bu_init_aggregation,
	.init_statistics = rtl8723bu_init_statistics,
	.enable_rf = rtl8723b_enable_rf,
	.disable_rf = rtl8xxxu_gen2_disable_rf,
	.usb_quirks = rtl8xxxu_gen2_usb_quirks,
	.set_tx_घातer = rtl8723b_set_tx_घातer,
	.update_rate_mask = rtl8xxxu_gen2_update_rate_mask,
	.report_connect = rtl8xxxu_gen2_report_connect,
	.fill_txdesc = rtl8xxxu_fill_txdesc_v2,
	.ग_लिखोN_block_size = 1024,
	.tx_desc_size = माप(काष्ठा rtl8xxxu_txdesc40),
	.rx_desc_size = माप(काष्ठा rtl8xxxu_rxdesc24),
	.has_s0s1 = 1,
	.has_tx_report = 1,
	.gen2_thermal_meter = 1,
	.needs_full_init = 1,
	.adda_1t_init = 0x01c00014,
	.adda_1t_path_on = 0x01c00014,
	.adda_2t_path_on_a = 0x01c00014,
	.adda_2t_path_on_b = 0x01c00014,
	.trxff_boundary = 0x3f7f,
	.pbp_rx = PBP_PAGE_SIZE_256,
	.pbp_tx = PBP_PAGE_SIZE_256,
	.mactable = rtl8723b_mac_init_table,
	.total_page_num = TX_TOTAL_PAGE_NUM_8723B,
	.page_num_hi = TX_PAGE_NUM_HI_PQ_8723B,
	.page_num_lo = TX_PAGE_NUM_LO_PQ_8723B,
	.page_num_norm = TX_PAGE_NUM_NORM_PQ_8723B,
पूर्ण;
