<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTL8XXXU mac80211 USB driver - 8192e specअगरic subdriver
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

अटल काष्ठा rtl8xxxu_reg8val rtl8192e_mac_init_table[] = अणु
	अणु0x011, 0xebपूर्ण, अणु0x012, 0x07पूर्ण, अणु0x014, 0x75पूर्ण, अणु0x303, 0xa7पूर्ण,
	अणु0x428, 0x0aपूर्ण, अणु0x429, 0x10पूर्ण, अणु0x430, 0x00पूर्ण, अणु0x431, 0x00पूर्ण,
	अणु0x432, 0x00पूर्ण, अणु0x433, 0x01पूर्ण, अणु0x434, 0x04पूर्ण, अणु0x435, 0x05पूर्ण,
	अणु0x436, 0x07पूर्ण, अणु0x437, 0x08पूर्ण, अणु0x43c, 0x04पूर्ण, अणु0x43d, 0x05पूर्ण,
	अणु0x43e, 0x07पूर्ण, अणु0x43f, 0x08पूर्ण, अणु0x440, 0x5dपूर्ण, अणु0x441, 0x01पूर्ण,
	अणु0x442, 0x00पूर्ण, अणु0x444, 0x10पूर्ण, अणु0x445, 0x00पूर्ण, अणु0x446, 0x00पूर्ण,
	अणु0x447, 0x00पूर्ण, अणु0x448, 0x00पूर्ण, अणु0x449, 0xf0पूर्ण, अणु0x44a, 0x0fपूर्ण,
	अणु0x44b, 0x3eपूर्ण, अणु0x44c, 0x10पूर्ण, अणु0x44d, 0x00पूर्ण, अणु0x44e, 0x00पूर्ण,
	अणु0x44f, 0x00पूर्ण, अणु0x450, 0x00पूर्ण, अणु0x451, 0xf0पूर्ण, अणु0x452, 0x0fपूर्ण,
	अणु0x453, 0x00पूर्ण, अणु0x456, 0x5eपूर्ण, अणु0x460, 0x66पूर्ण, अणु0x461, 0x66पूर्ण,
	अणु0x4c8, 0xffपूर्ण, अणु0x4c9, 0x08पूर्ण, अणु0x4cc, 0xffपूर्ण, अणु0x4cd, 0xffपूर्ण,
	अणु0x4ce, 0x01पूर्ण, अणु0x500, 0x26पूर्ण, अणु0x501, 0xa2पूर्ण, अणु0x502, 0x2fपूर्ण,
	अणु0x503, 0x00पूर्ण, अणु0x504, 0x28पूर्ण, अणु0x505, 0xa3पूर्ण, अणु0x506, 0x5eपूर्ण,
	अणु0x507, 0x00पूर्ण, अणु0x508, 0x2bपूर्ण, अणु0x509, 0xa4पूर्ण, अणु0x50a, 0x5eपूर्ण,
	अणु0x50b, 0x00पूर्ण, अणु0x50c, 0x4fपूर्ण, अणु0x50d, 0xa4पूर्ण, अणु0x50e, 0x00पूर्ण,
	अणु0x50f, 0x00पूर्ण, अणु0x512, 0x1cपूर्ण, अणु0x514, 0x0aपूर्ण, अणु0x516, 0x0aपूर्ण,
	अणु0x525, 0x4fपूर्ण, अणु0x540, 0x12पूर्ण, अणु0x541, 0x64पूर्ण, अणु0x550, 0x10पूर्ण,
	अणु0x551, 0x10पूर्ण, अणु0x559, 0x02पूर्ण, अणु0x55c, 0x50पूर्ण, अणु0x55d, 0xffपूर्ण,
	अणु0x605, 0x30पूर्ण, अणु0x608, 0x0eपूर्ण, अणु0x609, 0x2aपूर्ण, अणु0x620, 0xffपूर्ण,
	अणु0x621, 0xffपूर्ण, अणु0x622, 0xffपूर्ण, अणु0x623, 0xffपूर्ण, अणु0x624, 0xffपूर्ण,
	अणु0x625, 0xffपूर्ण, अणु0x626, 0xffपूर्ण, अणु0x627, 0xffपूर्ण, अणु0x638, 0x50पूर्ण,
	अणु0x63c, 0x0aपूर्ण, अणु0x63d, 0x0aपूर्ण, अणु0x63e, 0x0eपूर्ण, अणु0x63f, 0x0eपूर्ण,
	अणु0x640, 0x40पूर्ण, अणु0x642, 0x40पूर्ण, अणु0x643, 0x00पूर्ण, अणु0x652, 0xc8पूर्ण,
	अणु0x66e, 0x05पूर्ण, अणु0x700, 0x21पूर्ण, अणु0x701, 0x43पूर्ण, अणु0x702, 0x65पूर्ण,
	अणु0x703, 0x87पूर्ण, अणु0x708, 0x21पूर्ण, अणु0x709, 0x43पूर्ण, अणु0x70a, 0x65पूर्ण,
	अणु0x70b, 0x87पूर्ण,
	अणु0xffff, 0xffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8192eu_phy_init_table[] = अणु
	अणु0x800, 0x80040000पूर्ण, अणु0x804, 0x00000003पूर्ण,
	अणु0x808, 0x0000fc00पूर्ण, अणु0x80c, 0x0000000aपूर्ण,
	अणु0x810, 0x10001331पूर्ण, अणु0x814, 0x020c3d10पूर्ण,
	अणु0x818, 0x02220385पूर्ण, अणु0x81c, 0x00000000पूर्ण,
	अणु0x820, 0x01000100पूर्ण, अणु0x824, 0x00390204पूर्ण,
	अणु0x828, 0x01000100पूर्ण, अणु0x82c, 0x00390204पूर्ण,
	अणु0x830, 0x32323232पूर्ण, अणु0x834, 0x30303030पूर्ण,
	अणु0x838, 0x30303030पूर्ण, अणु0x83c, 0x30303030पूर्ण,
	अणु0x840, 0x00010000पूर्ण, अणु0x844, 0x00010000पूर्ण,
	अणु0x848, 0x28282828पूर्ण, अणु0x84c, 0x28282828पूर्ण,
	अणु0x850, 0x00000000पूर्ण, अणु0x854, 0x00000000पूर्ण,
	अणु0x858, 0x009a009aपूर्ण, अणु0x85c, 0x01000014पूर्ण,
	अणु0x860, 0x66f60000पूर्ण, अणु0x864, 0x061f0000पूर्ण,
	अणु0x868, 0x30303030पूर्ण, अणु0x86c, 0x30303030पूर्ण,
	अणु0x870, 0x00000000पूर्ण, अणु0x874, 0x55004200पूर्ण,
	अणु0x878, 0x08080808पूर्ण, अणु0x87c, 0x00000000पूर्ण,
	अणु0x880, 0xb0000c1cपूर्ण, अणु0x884, 0x00000001पूर्ण,
	अणु0x888, 0x00000000पूर्ण, अणु0x88c, 0xcc0000c0पूर्ण,
	अणु0x890, 0x00000800पूर्ण, अणु0x894, 0xfffffffeपूर्ण,
	अणु0x898, 0x40302010पूर्ण, अणु0x900, 0x00000000पूर्ण,
	अणु0x904, 0x00000023पूर्ण, अणु0x908, 0x00000000पूर्ण,
	अणु0x90c, 0x81121313पूर्ण, अणु0x910, 0x806c0001पूर्ण,
	अणु0x914, 0x00000001पूर्ण, अणु0x918, 0x00000000पूर्ण,
	अणु0x91c, 0x00010000पूर्ण, अणु0x924, 0x00000001पूर्ण,
	अणु0x928, 0x00000000पूर्ण, अणु0x92c, 0x00000000पूर्ण,
	अणु0x930, 0x00000000पूर्ण, अणु0x934, 0x00000000पूर्ण,
	अणु0x938, 0x00000000पूर्ण, अणु0x93c, 0x00000000पूर्ण,
	अणु0x940, 0x00000000पूर्ण, अणु0x944, 0x00000000पूर्ण,
	अणु0x94c, 0x00000008पूर्ण, अणु0xa00, 0x00d0c7c8पूर्ण,
	अणु0xa04, 0x81ff000cपूर्ण, अणु0xa08, 0x8c838300पूर्ण,
	अणु0xa0c, 0x2e68120fपूर्ण, अणु0xa10, 0x95009b78पूर्ण,
	अणु0xa14, 0x1114d028पूर्ण, अणु0xa18, 0x00881117पूर्ण,
	अणु0xa1c, 0x89140f00पूर्ण, अणु0xa20, 0x1a1b0000पूर्ण,
	अणु0xa24, 0x090e1317पूर्ण, अणु0xa28, 0x00000204पूर्ण,
	अणु0xa2c, 0x00d30000पूर्ण, अणु0xa70, 0x101fff00पूर्ण,
	अणु0xa74, 0x00000007पूर्ण, अणु0xa78, 0x00000900पूर्ण,
	अणु0xa7c, 0x225b0606पूर्ण, अणु0xa80, 0x218075b1पूर्ण,
	अणु0xb38, 0x00000000पूर्ण, अणु0xc00, 0x48071d40पूर्ण,
	अणु0xc04, 0x03a05633पूर्ण, अणु0xc08, 0x000000e4पूर्ण,
	अणु0xc0c, 0x6c6c6c6cपूर्ण, अणु0xc10, 0x08800000पूर्ण,
	अणु0xc14, 0x40000100पूर्ण, अणु0xc18, 0x08800000पूर्ण,
	अणु0xc1c, 0x40000100पूर्ण, अणु0xc20, 0x00000000पूर्ण,
	अणु0xc24, 0x00000000पूर्ण, अणु0xc28, 0x00000000पूर्ण,
	अणु0xc2c, 0x00000000पूर्ण, अणु0xc30, 0x69e9ac47पूर्ण,
	अणु0xc34, 0x469652afपूर्ण, अणु0xc38, 0x49795994पूर्ण,
	अणु0xc3c, 0x0a97971cपूर्ण, अणु0xc40, 0x1f7c403fपूर्ण,
	अणु0xc44, 0x000100b7पूर्ण, अणु0xc48, 0xec020107पूर्ण,
	अणु0xc4c, 0x007f037fपूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0xc50, 0x00340220पूर्ण,
#अन्यथा
	अणु0xc50, 0x00340020पूर्ण,
#पूर्ण_अगर
	अणु0xc54, 0x0080801fपूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0xc58, 0x00000220पूर्ण,
#अन्यथा
	अणु0xc58, 0x00000020पूर्ण,
#पूर्ण_अगर
	अणु0xc5c, 0x00248492पूर्ण, अणु0xc60, 0x00000000पूर्ण,
	अणु0xc64, 0x7112848bपूर्ण, अणु0xc68, 0x47c00bffपूर्ण,
	अणु0xc6c, 0x00000036पूर्ण, अणु0xc70, 0x00000600पूर्ण,
	अणु0xc74, 0x02013169पूर्ण, अणु0xc78, 0x0000001fपूर्ण,
	अणु0xc7c, 0x00b91612पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0xc80, 0x2d4000b5पूर्ण,
#अन्यथा
	अणु0xc80, 0x40000100पूर्ण,
#पूर्ण_अगर
	अणु0xc84, 0x21f60000पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0xc88, 0x2d4000b5पूर्ण,
#अन्यथा
	अणु0xc88, 0x40000100पूर्ण,
#पूर्ण_अगर
	अणु0xc8c, 0xa0e40000पूर्ण, अणु0xc90, 0x00121820पूर्ण,
	अणु0xc94, 0x00000000पूर्ण, अणु0xc98, 0x00121820पूर्ण,
	अणु0xc9c, 0x00007f7fपूर्ण, अणु0xca0, 0x00000000पूर्ण,
	अणु0xca4, 0x000300a0पूर्ण, अणु0xca8, 0x00000000पूर्ण,
	अणु0xcac, 0x00000000पूर्ण, अणु0xcb0, 0x00000000पूर्ण,
	अणु0xcb4, 0x00000000पूर्ण, अणु0xcb8, 0x00000000पूर्ण,
	अणु0xcbc, 0x28000000पूर्ण, अणु0xcc0, 0x00000000पूर्ण,
	अणु0xcc4, 0x00000000पूर्ण, अणु0xcc8, 0x00000000पूर्ण,
	अणु0xccc, 0x00000000पूर्ण, अणु0xcd0, 0x00000000पूर्ण,
	अणु0xcd4, 0x00000000पूर्ण, अणु0xcd8, 0x64b22427पूर्ण,
	अणु0xcdc, 0x00766932पूर्ण, अणु0xce0, 0x00222222पूर्ण,
	अणु0xce4, 0x00040000पूर्ण, अणु0xce8, 0x77644302पूर्ण,
	अणु0xcec, 0x2f97d40cपूर्ण, अणु0xd00, 0x00080740पूर्ण,
	अणु0xd04, 0x00020403पूर्ण, अणु0xd08, 0x0000907fपूर्ण,
	अणु0xd0c, 0x20010201पूर्ण, अणु0xd10, 0xa0633333पूर्ण,
	अणु0xd14, 0x3333bc43पूर्ण, अणु0xd18, 0x7a8f5b6bपूर्ण,
	अणु0xd1c, 0x0000007fपूर्ण, अणु0xd2c, 0xcc979975पूर्ण,
	अणु0xd30, 0x00000000पूर्ण, अणु0xd34, 0x80608000पूर्ण,
	अणु0xd38, 0x00000000पूर्ण, अणु0xd3c, 0x00127353पूर्ण,
	अणु0xd40, 0x00000000पूर्ण, अणु0xd44, 0x00000000पूर्ण,
	अणु0xd48, 0x00000000पूर्ण, अणु0xd4c, 0x00000000पूर्ण,
	अणु0xd50, 0x6437140aपूर्ण, अणु0xd54, 0x00000000पूर्ण,
	अणु0xd58, 0x00000282पूर्ण, अणु0xd5c, 0x30032064पूर्ण,
	अणु0xd60, 0x4653de68पूर्ण, अणु0xd64, 0x04518a3cपूर्ण,
	अणु0xd68, 0x00002101पूर्ण, अणु0xd6c, 0x2a201c16पूर्ण,
	अणु0xd70, 0x1812362eपूर्ण, अणु0xd74, 0x322c2220पूर्ण,
	अणु0xd78, 0x000e3c24पूर्ण, अणु0xd80, 0x01081008पूर्ण,
	अणु0xd84, 0x00000800पूर्ण, अणु0xd88, 0xf0b50000पूर्ण,
	अणु0xe00, 0x30303030पूर्ण, अणु0xe04, 0x30303030पूर्ण,
	अणु0xe08, 0x03903030पूर्ण, अणु0xe10, 0x30303030पूर्ण,
	अणु0xe14, 0x30303030पूर्ण, अणु0xe18, 0x30303030पूर्ण,
	अणु0xe1c, 0x30303030पूर्ण, अणु0xe28, 0x00000000पूर्ण,
	अणु0xe30, 0x1000dc1fपूर्ण, अणु0xe34, 0x10008c1fपूर्ण,
	अणु0xe38, 0x02140102पूर्ण, अणु0xe3c, 0x681604c2पूर्ण,
	अणु0xe40, 0x01007c00पूर्ण, अणु0xe44, 0x01004800पूर्ण,
	अणु0xe48, 0xfb000000पूर्ण, अणु0xe4c, 0x000028d1पूर्ण,
	अणु0xe50, 0x1000dc1fपूर्ण, अणु0xe54, 0x10008c1fपूर्ण,
	अणु0xe58, 0x02140102पूर्ण, अणु0xe5c, 0x28160d05पूर्ण,
	अणु0xe60, 0x00000008पूर्ण, अणु0xe68, 0x0fc05656पूर्ण,
	अणु0xe6c, 0x03c09696पूर्ण, अणु0xe70, 0x03c09696पूर्ण,
	अणु0xe74, 0x0c005656पूर्ण, अणु0xe78, 0x0c005656पूर्ण,
	अणु0xe7c, 0x0c005656पूर्ण, अणु0xe80, 0x0c005656पूर्ण,
	अणु0xe84, 0x03c09696पूर्ण, अणु0xe88, 0x0c005656पूर्ण,
	अणु0xe8c, 0x03c09696पूर्ण, अणु0xed0, 0x03c09696पूर्ण,
	अणु0xed4, 0x03c09696पूर्ण, अणु0xed8, 0x03c09696पूर्ण,
	अणु0xedc, 0x0000d6d6पूर्ण, अणु0xee0, 0x0000d6d6पूर्ण,
	अणु0xeec, 0x0fc01616पूर्ण, अणु0xee4, 0xb0000c1cपूर्ण,
	अणु0xee8, 0x00000001पूर्ण, अणु0xf14, 0x00000003पूर्ण,
	अणु0xf4c, 0x00000000पूर्ण, अणु0xf00, 0x00000300पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण,
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8xxx_agc_8192eu_std_table[] = अणु
	अणु0xc78, 0xfb000001पूर्ण, अणु0xc78, 0xfb010001पूर्ण,
	अणु0xc78, 0xfb020001पूर्ण, अणु0xc78, 0xfb030001पूर्ण,
	अणु0xc78, 0xfb040001पूर्ण, अणु0xc78, 0xfb050001पूर्ण,
	अणु0xc78, 0xfa060001पूर्ण, अणु0xc78, 0xf9070001पूर्ण,
	अणु0xc78, 0xf8080001पूर्ण, अणु0xc78, 0xf7090001पूर्ण,
	अणु0xc78, 0xf60a0001पूर्ण, अणु0xc78, 0xf50b0001पूर्ण,
	अणु0xc78, 0xf40c0001पूर्ण, अणु0xc78, 0xf30d0001पूर्ण,
	अणु0xc78, 0xf20e0001पूर्ण, अणु0xc78, 0xf10f0001पूर्ण,
	अणु0xc78, 0xf0100001पूर्ण, अणु0xc78, 0xef110001पूर्ण,
	अणु0xc78, 0xee120001पूर्ण, अणु0xc78, 0xed130001पूर्ण,
	अणु0xc78, 0xec140001पूर्ण, अणु0xc78, 0xeb150001पूर्ण,
	अणु0xc78, 0xea160001पूर्ण, अणु0xc78, 0xe9170001पूर्ण,
	अणु0xc78, 0xe8180001पूर्ण, अणु0xc78, 0xe7190001पूर्ण,
	अणु0xc78, 0xc81a0001पूर्ण, अणु0xc78, 0xc71b0001पूर्ण,
	अणु0xc78, 0xc61c0001पूर्ण, अणु0xc78, 0x071d0001पूर्ण,
	अणु0xc78, 0x061e0001पूर्ण, अणु0xc78, 0x051f0001पूर्ण,
	अणु0xc78, 0x04200001पूर्ण, अणु0xc78, 0x03210001पूर्ण,
	अणु0xc78, 0xaa220001पूर्ण, अणु0xc78, 0xa9230001पूर्ण,
	अणु0xc78, 0xa8240001पूर्ण, अणु0xc78, 0xa7250001पूर्ण,
	अणु0xc78, 0xa6260001पूर्ण, अणु0xc78, 0x85270001पूर्ण,
	अणु0xc78, 0x84280001पूर्ण, अणु0xc78, 0x83290001पूर्ण,
	अणु0xc78, 0x252a0001पूर्ण, अणु0xc78, 0x242b0001पूर्ण,
	अणु0xc78, 0x232c0001पूर्ण, अणु0xc78, 0x222d0001पूर्ण,
	अणु0xc78, 0x672e0001पूर्ण, अणु0xc78, 0x662f0001पूर्ण,
	अणु0xc78, 0x65300001पूर्ण, अणु0xc78, 0x64310001पूर्ण,
	अणु0xc78, 0x63320001पूर्ण, अणु0xc78, 0x62330001पूर्ण,
	अणु0xc78, 0x61340001पूर्ण, अणु0xc78, 0x45350001पूर्ण,
	अणु0xc78, 0x44360001पूर्ण, अणु0xc78, 0x43370001पूर्ण,
	अणु0xc78, 0x42380001पूर्ण, अणु0xc78, 0x41390001पूर्ण,
	अणु0xc78, 0x403a0001पूर्ण, अणु0xc78, 0x403b0001पूर्ण,
	अणु0xc78, 0x403c0001पूर्ण, अणु0xc78, 0x403d0001पूर्ण,
	अणु0xc78, 0x403e0001पूर्ण, अणु0xc78, 0x403f0001पूर्ण,
	अणु0xc78, 0xfb400001पूर्ण, अणु0xc78, 0xfb410001पूर्ण,
	अणु0xc78, 0xfb420001पूर्ण, अणु0xc78, 0xfb430001पूर्ण,
	अणु0xc78, 0xfb440001पूर्ण, अणु0xc78, 0xfb450001पूर्ण,
	अणु0xc78, 0xfa460001पूर्ण, अणु0xc78, 0xf9470001पूर्ण,
	अणु0xc78, 0xf8480001पूर्ण, अणु0xc78, 0xf7490001पूर्ण,
	अणु0xc78, 0xf64a0001पूर्ण, अणु0xc78, 0xf54b0001पूर्ण,
	अणु0xc78, 0xf44c0001पूर्ण, अणु0xc78, 0xf34d0001पूर्ण,
	अणु0xc78, 0xf24e0001पूर्ण, अणु0xc78, 0xf14f0001पूर्ण,
	अणु0xc78, 0xf0500001पूर्ण, अणु0xc78, 0xef510001पूर्ण,
	अणु0xc78, 0xee520001पूर्ण, अणु0xc78, 0xed530001पूर्ण,
	अणु0xc78, 0xec540001पूर्ण, अणु0xc78, 0xeb550001पूर्ण,
	अणु0xc78, 0xea560001पूर्ण, अणु0xc78, 0xe9570001पूर्ण,
	अणु0xc78, 0xe8580001पूर्ण, अणु0xc78, 0xe7590001पूर्ण,
	अणु0xc78, 0xe65a0001पूर्ण, अणु0xc78, 0xe55b0001पूर्ण,
	अणु0xc78, 0xe45c0001पूर्ण, अणु0xc78, 0xe35d0001पूर्ण,
	अणु0xc78, 0xe25e0001पूर्ण, अणु0xc78, 0xe15f0001पूर्ण,
	अणु0xc78, 0x8a600001पूर्ण, अणु0xc78, 0x89610001पूर्ण,
	अणु0xc78, 0x88620001पूर्ण, अणु0xc78, 0x87630001पूर्ण,
	अणु0xc78, 0x86640001पूर्ण, अणु0xc78, 0x85650001पूर्ण,
	अणु0xc78, 0x84660001पूर्ण, अणु0xc78, 0x83670001पूर्ण,
	अणु0xc78, 0x82680001पूर्ण, अणु0xc78, 0x6b690001पूर्ण,
	अणु0xc78, 0x6a6a0001पूर्ण, अणु0xc78, 0x696b0001पूर्ण,
	अणु0xc78, 0x686c0001पूर्ण, अणु0xc78, 0x676d0001पूर्ण,
	अणु0xc78, 0x666e0001पूर्ण, अणु0xc78, 0x656f0001पूर्ण,
	अणु0xc78, 0x64700001पूर्ण, अणु0xc78, 0x63710001पूर्ण,
	अणु0xc78, 0x62720001पूर्ण, अणु0xc78, 0x61730001पूर्ण,
	अणु0xc78, 0x49740001पूर्ण, अणु0xc78, 0x48750001पूर्ण,
	अणु0xc78, 0x47760001पूर्ण, अणु0xc78, 0x46770001पूर्ण,
	अणु0xc78, 0x45780001पूर्ण, अणु0xc78, 0x44790001पूर्ण,
	अणु0xc78, 0x437a0001पूर्ण, अणु0xc78, 0x427b0001पूर्ण,
	अणु0xc78, 0x417c0001पूर्ण, अणु0xc78, 0x407d0001पूर्ण,
	अणु0xc78, 0x407e0001पूर्ण, अणु0xc78, 0x407f0001पूर्ण,
	अणु0xc50, 0x00040022पूर्ण, अणु0xc50, 0x00040020पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_reg32val rtl8xxx_agc_8192eu_highpa_table[] = अणु
	अणु0xc78, 0xfa000001पूर्ण, अणु0xc78, 0xf9010001पूर्ण,
	अणु0xc78, 0xf8020001पूर्ण, अणु0xc78, 0xf7030001पूर्ण,
	अणु0xc78, 0xf6040001पूर्ण, अणु0xc78, 0xf5050001पूर्ण,
	अणु0xc78, 0xf4060001पूर्ण, अणु0xc78, 0xf3070001पूर्ण,
	अणु0xc78, 0xf2080001पूर्ण, अणु0xc78, 0xf1090001पूर्ण,
	अणु0xc78, 0xf00a0001पूर्ण, अणु0xc78, 0xef0b0001पूर्ण,
	अणु0xc78, 0xee0c0001पूर्ण, अणु0xc78, 0xed0d0001पूर्ण,
	अणु0xc78, 0xec0e0001पूर्ण, अणु0xc78, 0xeb0f0001पूर्ण,
	अणु0xc78, 0xea100001पूर्ण, अणु0xc78, 0xe9110001पूर्ण,
	अणु0xc78, 0xe8120001पूर्ण, अणु0xc78, 0xe7130001पूर्ण,
	अणु0xc78, 0xe6140001पूर्ण, अणु0xc78, 0xe5150001पूर्ण,
	अणु0xc78, 0xe4160001पूर्ण, अणु0xc78, 0xe3170001पूर्ण,
	अणु0xc78, 0xe2180001पूर्ण, अणु0xc78, 0xe1190001पूर्ण,
	अणु0xc78, 0x8a1a0001पूर्ण, अणु0xc78, 0x891b0001पूर्ण,
	अणु0xc78, 0x881c0001पूर्ण, अणु0xc78, 0x871d0001पूर्ण,
	अणु0xc78, 0x861e0001पूर्ण, अणु0xc78, 0x851f0001पूर्ण,
	अणु0xc78, 0x84200001पूर्ण, अणु0xc78, 0x83210001पूर्ण,
	अणु0xc78, 0x82220001पूर्ण, अणु0xc78, 0x6a230001पूर्ण,
	अणु0xc78, 0x69240001पूर्ण, अणु0xc78, 0x68250001पूर्ण,
	अणु0xc78, 0x67260001पूर्ण, अणु0xc78, 0x66270001पूर्ण,
	अणु0xc78, 0x65280001पूर्ण, अणु0xc78, 0x64290001पूर्ण,
	अणु0xc78, 0x632a0001पूर्ण, अणु0xc78, 0x622b0001पूर्ण,
	अणु0xc78, 0x612c0001पूर्ण, अणु0xc78, 0x602d0001पूर्ण,
	अणु0xc78, 0x472e0001पूर्ण, अणु0xc78, 0x462f0001पूर्ण,
	अणु0xc78, 0x45300001पूर्ण, अणु0xc78, 0x44310001पूर्ण,
	अणु0xc78, 0x43320001पूर्ण, अणु0xc78, 0x42330001पूर्ण,
	अणु0xc78, 0x41340001पूर्ण, अणु0xc78, 0x40350001पूर्ण,
	अणु0xc78, 0x40360001पूर्ण, अणु0xc78, 0x40370001पूर्ण,
	अणु0xc78, 0x40380001पूर्ण, अणु0xc78, 0x40390001पूर्ण,
	अणु0xc78, 0x403a0001पूर्ण, अणु0xc78, 0x403b0001पूर्ण,
	अणु0xc78, 0x403c0001पूर्ण, अणु0xc78, 0x403d0001पूर्ण,
	अणु0xc78, 0x403e0001पूर्ण, अणु0xc78, 0x403f0001पूर्ण,
	अणु0xc78, 0xfa400001पूर्ण, अणु0xc78, 0xf9410001पूर्ण,
	अणु0xc78, 0xf8420001पूर्ण, अणु0xc78, 0xf7430001पूर्ण,
	अणु0xc78, 0xf6440001पूर्ण, अणु0xc78, 0xf5450001पूर्ण,
	अणु0xc78, 0xf4460001पूर्ण, अणु0xc78, 0xf3470001पूर्ण,
	अणु0xc78, 0xf2480001पूर्ण, अणु0xc78, 0xf1490001पूर्ण,
	अणु0xc78, 0xf04a0001पूर्ण, अणु0xc78, 0xef4b0001पूर्ण,
	अणु0xc78, 0xee4c0001पूर्ण, अणु0xc78, 0xed4d0001पूर्ण,
	अणु0xc78, 0xec4e0001पूर्ण, अणु0xc78, 0xeb4f0001पूर्ण,
	अणु0xc78, 0xea500001पूर्ण, अणु0xc78, 0xe9510001पूर्ण,
	अणु0xc78, 0xe8520001पूर्ण, अणु0xc78, 0xe7530001पूर्ण,
	अणु0xc78, 0xe6540001पूर्ण, अणु0xc78, 0xe5550001पूर्ण,
	अणु0xc78, 0xe4560001पूर्ण, अणु0xc78, 0xe3570001पूर्ण,
	अणु0xc78, 0xe2580001पूर्ण, अणु0xc78, 0xe1590001पूर्ण,
	अणु0xc78, 0x8a5a0001पूर्ण, अणु0xc78, 0x895b0001पूर्ण,
	अणु0xc78, 0x885c0001पूर्ण, अणु0xc78, 0x875d0001पूर्ण,
	अणु0xc78, 0x865e0001पूर्ण, अणु0xc78, 0x855f0001पूर्ण,
	अणु0xc78, 0x84600001पूर्ण, अणु0xc78, 0x83610001पूर्ण,
	अणु0xc78, 0x82620001पूर्ण, अणु0xc78, 0x6a630001पूर्ण,
	अणु0xc78, 0x69640001पूर्ण, अणु0xc78, 0x68650001पूर्ण,
	अणु0xc78, 0x67660001पूर्ण, अणु0xc78, 0x66670001पूर्ण,
	अणु0xc78, 0x65680001पूर्ण, अणु0xc78, 0x64690001पूर्ण,
	अणु0xc78, 0x636a0001पूर्ण, अणु0xc78, 0x626b0001पूर्ण,
	अणु0xc78, 0x616c0001पूर्ण, अणु0xc78, 0x606d0001पूर्ण,
	अणु0xc78, 0x476e0001पूर्ण, अणु0xc78, 0x466f0001पूर्ण,
	अणु0xc78, 0x45700001पूर्ण, अणु0xc78, 0x44710001पूर्ण,
	अणु0xc78, 0x43720001पूर्ण, अणु0xc78, 0x42730001पूर्ण,
	अणु0xc78, 0x41740001पूर्ण, अणु0xc78, 0x40750001पूर्ण,
	अणु0xc78, 0x40760001पूर्ण, अणु0xc78, 0x40770001पूर्ण,
	अणु0xc78, 0x40780001पूर्ण, अणु0xc78, 0x40790001पूर्ण,
	अणु0xc78, 0x407a0001पूर्ण, अणु0xc78, 0x407b0001पूर्ण,
	अणु0xc78, 0x407c0001पूर्ण, अणु0xc78, 0x407d0001पूर्ण,
	अणु0xc78, 0x407e0001पूर्ण, अणु0xc78, 0x407f0001पूर्ण,
	अणु0xc50, 0x00040222पूर्ण, अणु0xc50, 0x00040220पूर्ण,
	अणु0xffff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8192eu_radioa_init_table[] = अणु
	अणु0x7f, 0x00000082पूर्ण, अणु0x81, 0x0003fc00पूर्ण,
	अणु0x00, 0x00030000पूर्ण, अणु0x08, 0x00008400पूर्ण,
	अणु0x18, 0x00000407पूर्ण, अणु0x19, 0x00000012पूर्ण,
	अणु0x1b, 0x00000064पूर्ण, अणु0x1e, 0x00080009पूर्ण,
	अणु0x1f, 0x00000880पूर्ण, अणु0x2f, 0x0001a060पूर्ण,
	अणु0x3f, 0x00000000पूर्ण, अणु0x42, 0x000060c0पूर्ण,
	अणु0x57, 0x000d0000पूर्ण, अणु0x58, 0x000be180पूर्ण,
	अणु0x67, 0x00001552पूर्ण, अणु0x83, 0x00000000पूर्ण,
	अणु0xb0, 0x000ff9f1पूर्ण, अणु0xb1, 0x00055418पूर्ण,
	अणु0xb2, 0x0008cc00पूर्ण, अणु0xb4, 0x00043083पूर्ण,
	अणु0xb5, 0x00008166पूर्ण, अणु0xb6, 0x0000803eपूर्ण,
	अणु0xb7, 0x0001c69fपूर्ण, अणु0xb8, 0x0000407fपूर्ण,
	अणु0xb9, 0x00080001पूर्ण, अणु0xba, 0x00040001पूर्ण,
	अणु0xbb, 0x00000400पूर्ण, अणु0xbf, 0x000c0000पूर्ण,
	अणु0xc2, 0x00002400पूर्ण, अणु0xc3, 0x00000009पूर्ण,
	अणु0xc4, 0x00040c91पूर्ण, अणु0xc5, 0x00099999पूर्ण,
	अणु0xc6, 0x000000a3पूर्ण, अणु0xc7, 0x00088820पूर्ण,
	अणु0xc8, 0x00076c06पूर्ण, अणु0xc9, 0x00000000पूर्ण,
	अणु0xca, 0x00080000पूर्ण, अणु0xdf, 0x00000180पूर्ण,
	अणु0xef, 0x000001a0पूर्ण, अणु0x51, 0x00069545पूर्ण,
	अणु0x52, 0x0007e45eपूर्ण, अणु0x53, 0x00000071पूर्ण,
	अणु0x56, 0x00051ff3पूर्ण, अणु0x35, 0x000000a8पूर्ण,
	अणु0x35, 0x000001e2पूर्ण, अणु0x35, 0x000002a8पूर्ण,
	अणु0x36, 0x00001c24पूर्ण, अणु0x36, 0x00009c24पूर्ण,
	अणु0x36, 0x00011c24पूर्ण, अणु0x36, 0x00019c24पूर्ण,
	अणु0x18, 0x00000c07पूर्ण, अणु0x5a, 0x00048000पूर्ण,
	अणु0x19, 0x000739d0पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x34, 0x0000a093पूर्ण, अणु0x34, 0x0000908fपूर्ण,
	अणु0x34, 0x0000808cपूर्ण, अणु0x34, 0x0000704dपूर्ण,
	अणु0x34, 0x0000604aपूर्ण, अणु0x34, 0x00005047पूर्ण,
	अणु0x34, 0x0000400aपूर्ण, अणु0x34, 0x00003007पूर्ण,
	अणु0x34, 0x00002004पूर्ण, अणु0x34, 0x00001001पूर्ण,
	अणु0x34, 0x00000000पूर्ण,
#अन्यथा
	/* Regular */
	अणु0x34, 0x0000add7पूर्ण, अणु0x34, 0x00009dd4पूर्ण,
	अणु0x34, 0x00008dd1पूर्ण, अणु0x34, 0x00007dceपूर्ण,
	अणु0x34, 0x00006dcbपूर्ण, अणु0x34, 0x00005dc8पूर्ण,
	अणु0x34, 0x00004dc5पूर्ण, अणु0x34, 0x000034ccपूर्ण,
	अणु0x34, 0x0000244fपूर्ण, अणु0x34, 0x0000144cपूर्ण,
	अणु0x34, 0x00000014पूर्ण,
#पूर्ण_अगर
	अणु0x00, 0x00030159पूर्ण,
	अणु0x84, 0x00068180पूर्ण,
	अणु0x86, 0x0000014eपूर्ण,
	अणु0x87, 0x00048e00पूर्ण,
	अणु0x8e, 0x00065540पूर्ण,
	अणु0x8f, 0x00088000पूर्ण,
	अणु0xef, 0x000020a0पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x3b, 0x000f07b0पूर्ण,
#अन्यथा
	अणु0x3b, 0x000f02b0पूर्ण,
#पूर्ण_अगर
	अणु0x3b, 0x000ef7b0पूर्ण, अणु0x3b, 0x000d4fb0पूर्ण,
	अणु0x3b, 0x000cf060पूर्ण, अणु0x3b, 0x000b0090पूर्ण,
	अणु0x3b, 0x000a0080पूर्ण, अणु0x3b, 0x00090080पूर्ण,
	अणु0x3b, 0x0008f780पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x3b, 0x000787b0पूर्ण,
#अन्यथा
	अणु0x3b, 0x00078730पूर्ण,
#पूर्ण_अगर
	अणु0x3b, 0x00060fb0पूर्ण, अणु0x3b, 0x0005ffa0पूर्ण,
	अणु0x3b, 0x00040620पूर्ण, अणु0x3b, 0x00037090पूर्ण,
	अणु0x3b, 0x00020080पूर्ण, अणु0x3b, 0x0001f060पूर्ण,
	अणु0x3b, 0x0000ffb0पूर्ण, अणु0xef, 0x000000a0पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x18, 0x0000fc07पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0x1e, 0x00000001पूर्ण, अणु0x1f, 0x00080000पूर्ण,
	अणु0x00, 0x00033e70पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8192eu_radiob_init_table[] = अणु
	अणु0x7f, 0x00000082पूर्ण, अणु0x81, 0x0003fc00पूर्ण,
	अणु0x00, 0x00030000पूर्ण, अणु0x08, 0x00008400पूर्ण,
	अणु0x18, 0x00000407पूर्ण, अणु0x19, 0x00000012पूर्ण,
	अणु0x1b, 0x00000064पूर्ण, अणु0x1e, 0x00080009पूर्ण,
	अणु0x1f, 0x00000880पूर्ण, अणु0x2f, 0x0001a060पूर्ण,
	अणु0x3f, 0x00000000पूर्ण, अणु0x42, 0x000060c0पूर्ण,
	अणु0x57, 0x000d0000पूर्ण, अणु0x58, 0x000be180पूर्ण,
	अणु0x67, 0x00001552पूर्ण, अणु0x7f, 0x00000082पूर्ण,
	अणु0x81, 0x0003f000पूर्ण, अणु0x83, 0x00000000पूर्ण,
	अणु0xdf, 0x00000180पूर्ण, अणु0xef, 0x000001a0पूर्ण,
	अणु0x51, 0x00069545पूर्ण, अणु0x52, 0x0007e42eपूर्ण,
	अणु0x53, 0x00000071पूर्ण, अणु0x56, 0x00051ff3पूर्ण,
	अणु0x35, 0x000000a8पूर्ण, अणु0x35, 0x000001e0पूर्ण,
	अणु0x35, 0x000002a8पूर्ण, अणु0x36, 0x00001ca8पूर्ण,
	अणु0x36, 0x00009c24पूर्ण, अणु0x36, 0x00011c24पूर्ण,
	अणु0x36, 0x00019c24पूर्ण, अणु0x18, 0x00000c07पूर्ण,
	अणु0x5a, 0x00048000पूर्ण, अणु0x19, 0x000739d0पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x34, 0x0000a093पूर्ण, अणु0x34, 0x0000908fपूर्ण,
	अणु0x34, 0x0000808cपूर्ण, अणु0x34, 0x0000704dपूर्ण,
	अणु0x34, 0x0000604aपूर्ण, अणु0x34, 0x00005047पूर्ण,
	अणु0x34, 0x0000400aपूर्ण, अणु0x34, 0x00003007पूर्ण,
	अणु0x34, 0x00002004पूर्ण, अणु0x34, 0x00001001पूर्ण,
	अणु0x34, 0x00000000पूर्ण,
#अन्यथा
	अणु0x34, 0x0000add7पूर्ण, अणु0x34, 0x00009dd4पूर्ण,
	अणु0x34, 0x00008dd1पूर्ण, अणु0x34, 0x00007dceपूर्ण,
	अणु0x34, 0x00006dcbपूर्ण, अणु0x34, 0x00005dc8पूर्ण,
	अणु0x34, 0x00004dc5पूर्ण, अणु0x34, 0x000034ccपूर्ण,
	अणु0x34, 0x0000244fपूर्ण, अणु0x34, 0x0000144cपूर्ण,
	अणु0x34, 0x00000014पूर्ण,
#पूर्ण_अगर
	अणु0x00, 0x00030159पूर्ण, अणु0x84, 0x00068180पूर्ण,
	अणु0x86, 0x000000ceपूर्ण, अणु0x87, 0x00048a00पूर्ण,
	अणु0x8e, 0x00065540पूर्ण, अणु0x8f, 0x00088000पूर्ण,
	अणु0xef, 0x000020a0पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x3b, 0x000f07b0पूर्ण,
#अन्यथा
	अणु0x3b, 0x000f02b0पूर्ण,
#पूर्ण_अगर

	अणु0x3b, 0x000ef7b0पूर्ण, अणु0x3b, 0x000d4fb0पूर्ण,
	अणु0x3b, 0x000cf060पूर्ण, अणु0x3b, 0x000b0090पूर्ण,
	अणु0x3b, 0x000a0080पूर्ण, अणु0x3b, 0x00090080पूर्ण,
	अणु0x3b, 0x0008f780पूर्ण,
#अगर_घोषित EXT_PA_8192EU
	/* External PA or बाह्यal LNA */
	अणु0x3b, 0x000787b0पूर्ण,
#अन्यथा
	अणु0x3b, 0x00078730पूर्ण,
#पूर्ण_अगर
	अणु0x3b, 0x00060fb0पूर्ण, अणु0x3b, 0x0005ffa0पूर्ण,
	अणु0x3b, 0x00040620पूर्ण, अणु0x3b, 0x00037090पूर्ण,
	अणु0x3b, 0x00020080पूर्ण, अणु0x3b, 0x0001f060पूर्ण,
	अणु0x3b, 0x0000ffb0पूर्ण, अणु0xef, 0x000000a0पूर्ण,
	अणु0x00, 0x00010159पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x1e, 0x00000001पूर्ण,
	अणु0x1f, 0x00080000पूर्ण, अणु0x00, 0x00033e70पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल व्योम
rtl8192e_set_tx_घातer(काष्ठा rtl8xxxu_priv *priv, पूर्णांक channel, bool ht40)
अणु
	u32 val32, ofdm, mcs;
	u8 cck, ofdmbase, mcsbase;
	पूर्णांक group, tx_idx;

	tx_idx = 0;
	group = rtl8xxxu_gen2_channel_to_group(channel);

	cck = priv->cck_tx_घातer_index_A[group];

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_A_CCK1_MCS32);
	val32 &= 0xffff00ff;
	val32 |= (cck << 8);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_CCK1_MCS32, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
	val32 &= 0xff;
	val32 |= ((cck << 8) | (cck << 16) | (cck << 24));
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

	ofdmbase = priv->ht40_1s_tx_घातer_index_A[group];
	ofdmbase += priv->ofdm_tx_घातer_dअगरf[tx_idx].a;
	ofdm = ofdmbase | ofdmbase << 8 | ofdmbase << 16 | ofdmbase << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE18_06, ofdm);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_RATE54_24, ofdm);

	mcsbase = priv->ht40_1s_tx_घातer_index_A[group];
	अगर (ht40)
		mcsbase += priv->ht40_tx_घातer_dअगरf[tx_idx++].a;
	अन्यथा
		mcsbase += priv->ht20_tx_घातer_dअगरf[tx_idx++].a;
	mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS03_MCS00, mcs);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS07_MCS04, mcs);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS11_MCS08, mcs);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_A_MCS15_MCS12, mcs);

	अगर (priv->tx_paths > 1) अणु
		cck = priv->cck_tx_घातer_index_B[group];

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK1_55_MCS32);
		val32 &= 0xff;
		val32 |= ((cck << 8) | (cck << 16) | (cck << 24));
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK1_55_MCS32, val32);

		val32 = rtl8xxxu_पढ़ो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
		val32 &= 0xffffff00;
		val32 |= cck;
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

		ofdmbase = priv->ht40_1s_tx_घातer_index_B[group];
		ofdmbase += priv->ofdm_tx_घातer_dअगरf[tx_idx].b;
		ofdm = ofdmbase | ofdmbase << 8 |
			ofdmbase << 16 | ofdmbase << 24;

		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_RATE18_06, ofdm);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_RATE54_24, ofdm);

		mcsbase = priv->ht40_1s_tx_घातer_index_B[group];
		अगर (ht40)
			mcsbase += priv->ht40_tx_घातer_dअगरf[tx_idx++].b;
		अन्यथा
			mcsbase += priv->ht20_tx_घातer_dअगरf[tx_idx++].b;
		mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS03_MCS00, mcs);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS07_MCS04, mcs);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS11_MCS08, mcs);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_AGC_B_MCS15_MCS12, mcs);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8192eu_parse_efuse(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8192eu_efuse *efuse = &priv->efuse_wअगरi.efuse8192eu;
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
	priv->xtalk = priv->efuse_wअगरi.efuse8192eu.xtal_k & 0x3f;

	dev_info(&priv->udev->dev, "Vendor: %.7s\n", efuse->venकरोr_name);
	dev_info(&priv->udev->dev, "Product: %.11s\n", efuse->device_name);
	अगर (स_प्रथम_inv(efuse->serial, 0xff, 11))
		dev_info(&priv->udev->dev, "Serial: %.11s\n", efuse->serial);
	अन्यथा
		dev_info(&priv->udev->dev, "Serial not available.\n");

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_EFUSE) अणु
		अचिन्हित अक्षर *raw = priv->efuse_wअगरi.raw;

		dev_info(&priv->udev->dev,
			 "%s: dumping efuse (0x%02zx bytes):\n",
			 __func__, माप(काष्ठा rtl8192eu_efuse));
		क्रम (i = 0; i < माप(काष्ठा rtl8192eu_efuse); i += 8)
			dev_info(&priv->udev->dev, "%02x: %8ph\n", i, &raw[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8192eu_load_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	अक्षर *fw_name;
	पूर्णांक ret;

	fw_name = "rtlwifi/rtl8192eu_nic.bin";

	ret = rtl8xxxu_load_firmware(priv, fw_name);

	वापस ret;
पूर्ण

अटल व्योम rtl8192eu_init_phy_bb(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;

	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB | SYS_FUNC_DIO_RF;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	/* 6. 0x1f[7:0] = 0x07 */
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, val8);

	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 |= (SYS_FUNC_USBA | SYS_FUNC_USBD | SYS_FUNC_DIO_RF |
		  SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB);
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, val8);
	rtl8xxxu_init_phy_regs(priv, rtl8192eu_phy_init_table);

	अगर (priv->hi_pa)
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8192eu_highpa_table);
	अन्यथा
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8192eu_std_table);
पूर्ण

अटल पूर्णांक rtl8192eu_init_phy_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8192eu_radioa_init_table, RF_A);
	अगर (ret)
		जाओ निकास;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8192eu_radiob_init_table, RF_B);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8192eu_iqk_path_a(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_e94, reg_e9c;
	पूर्णांक result = 0;

	/*
	 * TX IQK
	 * PA/PAD controlled by 0x0
	 */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x00180);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* Path A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82140303);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x68160000);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x00462911);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(10);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_A);

	अगर (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000))
		result |= 0x01;

	वापस result;
पूर्ण

अटल पूर्णांक rtl8192eu_rx_iqk_path_a(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_ea4, reg_eac, reg_e94, reg_e9c, val32;
	पूर्णांक result = 0;

	/* Leave IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00);

	/* Enable path A PA in TX IQK mode */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, 0x800a0);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0000f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xf117b);

	/* PA/PAD control by 0x56, and set = 0x0 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x00980);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_56, 0x51000);

	/* Enter IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* TX IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82160c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x68160c1f);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a911);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xfa000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(10);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_A);

	अगर (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000)) अणु
		result |= 0x01;
	पूर्ण अन्यथा अणु
		/* PA/PAD controlled by 0x0 */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x180);
		जाओ out;
	पूर्ण

	val32 = 0x80007c00 |
		(reg_e94 & 0x03ff0000) | ((reg_e9c >> 16) & 0x03ff);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, val32);

	/* Modअगरy RX IQK mode table */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_WE_LUT, 0x800a0);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0000f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xf7ffa);

	/* PA/PAD control by 0x56, and set = 0x0 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x00980);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_56, 0x51000);

	/* Enter IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* Path A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82160c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x28160c1f);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a891);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xfa000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(10);

	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_ea4 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_A_2);

	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_UNKNOWN_DF, 0x180);

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

अटल पूर्णांक rtl8192eu_iqk_path_b(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_eb4, reg_ebc;
	पूर्णांक result = 0;

	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_DF, 0x00180);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* Path B IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x821403e2);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x68160000);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x00492911);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xfa000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_eb4 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
	reg_ebc = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);

	अगर (!(reg_eac & BIT(31)) &&
	    ((reg_eb4 & 0x03ff0000) != 0x01420000) &&
	    ((reg_ebc & 0x03ff0000) != 0x00420000))
		result |= 0x01;
	अन्यथा
		dev_warn(&priv->udev->dev, "%s: Path B IQK failed!\n",
			 __func__);

	वापस result;
पूर्ण

अटल पूर्णांक rtl8192eu_rx_iqk_path_b(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 reg_eac, reg_eb4, reg_ebc, reg_ec4, reg_ecc, val32;
	पूर्णांक result = 0;

	/* Leave IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);

	/* Enable path A PA in TX IQK mode */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_WE_LUT, 0x800a0);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_TXPA_G1, 0x0000f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_TXPA_G2, 0xf117b);

	/* PA/PAD control by 0x56, and set = 0x0 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_DF, 0x00980);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_56, 0x51000);

	/* Enter IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* TX IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x18008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_B, 0x82160c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_B, 0x68160c1f);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a911);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xfa000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(10);

	/* Check failed */
	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_eb4 = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_BEFORE_IQK_B);
	reg_ebc = rtl8xxxu_पढ़ो32(priv, REG_TX_POWER_AFTER_IQK_B);

	अगर (!(reg_eac & BIT(31)) &&
	    ((reg_eb4 & 0x03ff0000) != 0x01420000) &&
	    ((reg_ebc & 0x03ff0000) != 0x00420000)) अणु
		result |= 0x01;
	पूर्ण अन्यथा अणु
		/*
		 * PA/PAD controlled by 0x0
		 * Venकरोr driver restores RF_A here which I believe is a bug
		 */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_DF, 0x180);
		जाओ out;
	पूर्ण

	val32 = 0x80007c00 |
		(reg_eb4 & 0x03ff0000) | ((reg_ebc >> 16) & 0x03ff);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, val32);

	/* Modअगरy RX IQK mode table */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);

	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_WE_LUT, 0x800a0);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_RCK_OS, 0x30000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_TXPA_G1, 0x0000f);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_TXPA_G2, 0xf7ffa);

	/* PA/PAD control by 0x56, and set = 0x0 */
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_DF, 0x00980);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_56, 0x51000);

	/* Enter IQK mode */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

	/* IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	/* Path A IQK setting */
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_TONE_B, 0x18008c1c);

	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK_PI_A, 0x82160c1f);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK_PI_A, 0x28160c1f);

	/* LO calibration setting */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_RSP, 0x0046a891);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xfa000000);
	rtl8xxxu_ग_लिखो32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(10);

	reg_eac = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_ec4 = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_BEFORE_IQK_B_2);
	reg_ecc = rtl8xxxu_पढ़ो32(priv, REG_RX_POWER_AFTER_IQK_B_2);

	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
	rtl8xxxu_ग_लिखो_rfreg(priv, RF_B, RF6052_REG_UNKNOWN_DF, 0x180);

	अगर (!(reg_eac & BIT(30)) &&
	    ((reg_ec4 & 0x03ff0000) != 0x01320000) &&
	    ((reg_ecc & 0x03ff0000) != 0x00360000))
		result |= 0x02;
	अन्यथा
		dev_warn(&priv->udev->dev, "%s: Path B RX IQK failed!\n",
			 __func__);

out:
	वापस result;
पूर्ण

अटल व्योम rtl8192eu_phy_iqcalibrate(काष्ठा rtl8xxxu_priv *priv,
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
		REG_FPGA0_XB_RF_INT_OE, REG_CCK0_AFE_SETTING
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
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XCD_RF_SW_CTRL, 0x22208200);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XAB_RF_SW_CTRL);
	val32 |= (FPGA0_RF_PAPE | (FPGA0_RF_PAPE << FPGA0_RF_BD_CTRL_SHIFT));
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XAB_RF_SW_CTRL, val32);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XA_RF_INT_OE);
	val32 |= BIT(10);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XA_RF_INT_OE, val32);
	val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XB_RF_INT_OE);
	val32 |= BIT(10);
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XB_RF_INT_OE, val32);

	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);
	rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

	क्रम (i = 0; i < retry; i++) अणु
		path_a_ok = rtl8192eu_iqk_path_a(priv);
		अगर (path_a_ok == 0x01) अणु
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
		path_a_ok = rtl8192eu_rx_iqk_path_a(priv);
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

	अगर (priv->rf_paths > 1) अणु
		/* Path A पूर्णांकo standby */
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);
		rtl8xxxu_ग_लिखो_rfreg(priv, RF_A, RF6052_REG_AC, 0x10000);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);

		/* Turn Path B ADDA on */
		rtl8xxxu_path_adda_on(priv, adda_regs, false);

		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x80800000);
		rtl8xxxu_ग_लिखो32(priv, REG_TX_IQK, 0x01007c00);
		rtl8xxxu_ग_लिखो32(priv, REG_RX_IQK, 0x01004800);

		क्रम (i = 0; i < retry; i++) अणु
			path_b_ok = rtl8192eu_iqk_path_b(priv);
			अगर (path_b_ok == 0x01) अणु
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
			path_b_ok = rtl8192eu_rx_iqk_path_b(priv);
			अगर (path_b_ok == 0x03) अणु
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
	पूर्ण

	/* Back to BB mode, load original value */
	rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_IQK, 0x00000000);

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

		अगर (priv->rf_paths > 1) अणु
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

अटल व्योम rtl8192eu_phy_iq_calibrate(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	पूर्णांक result[4][8];	/* last is final result */
	पूर्णांक i, candidate;
	bool path_a_ok, path_b_ok;
	u32 reg_e94, reg_e9c, reg_ea4, reg_eac;
	u32 reg_eb4, reg_ebc, reg_ec4, reg_ecc;
	bool simu;

	स_रखो(result, 0, माप(result));
	candidate = -1;

	path_a_ok = false;
	path_b_ok = false;

	क्रम (i = 0; i < 3; i++) अणु
		rtl8192eu_phy_iqcalibrate(priv, result, i);

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
			अगर (simu)
				candidate = 1;
			अन्यथा
				candidate = 3;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		reg_e94 = result[i][0];
		reg_e9c = result[i][1];
		reg_ea4 = result[i][2];
		reg_eb4 = result[i][4];
		reg_ebc = result[i][5];
		reg_ec4 = result[i][6];
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

	अगर (priv->rf_paths > 1)
		rtl8xxxu_fill_iqk_matrix_b(priv, path_b_ok, result,
					   candidate, (reg_ec4 == 0));

	rtl8xxxu_save_regs(priv, rtl8xxxu_iqk_phy_iq_bb_reg,
			   priv->bb_recovery_backup, RTL8XXXU_BB_REGS);
पूर्ण

/*
 * This is needed क्रम 8723bu as well, presumable
 */
अटल व्योम rtl8192e_crystal_afe_adjust(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;

	/*
	 * 40Mhz crystal source, MAC 0x28[2]=0
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_AFE_PLL_CTRL);
	val8 &= 0xfb;
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_PLL_CTRL, val8);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_AFE_CTRL4);
	val32 &= 0xfffffc7f;
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_CTRL4, val32);

	/*
	 * 92e AFE parameter
	 * AFE PLL KVCO selection, MAC 0x28[6]=1
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_AFE_PLL_CTRL);
	val8 &= 0xbf;
	rtl8xxxu_ग_लिखो8(priv, REG_AFE_PLL_CTRL, val8);

	/*
	 * AFE PLL KVCO selection, MAC 0x78[21]=0
	 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_AFE_CTRL4);
	val32 &= 0xffdfffff;
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_CTRL4, val32);
पूर्ण

अटल व्योम rtl8192e_disabled_to_emu(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;

	/* Clear suspend enable and घातer करोwn enable*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);
पूर्ण

अटल पूर्णांक rtl8192e_emu_to_active(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;
	पूर्णांक count, ret = 0;

	/* disable HWPDN 0x04[15]=0*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~BIT(7);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* disable SW LPS 0x04[10]= 0 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~BIT(2);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* disable WL suspend*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* रुको till 0x04[17] = 1 घातer पढ़ोy*/
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

	/* release WLON reset 0x04[16]= 1*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 2);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 2, val8);

	/* set, then poll until 0 */
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

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8192eu_active_to_lps(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा device *dev = &priv->udev->dev;
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक retry, retval;

	rtl8xxxu_ग_लिखो8(priv, REG_TXPAUSE, 0xff);

	retry = 100;
	retval = -EBUSY;
	/*
	 * Poll 32 bit wide 0x05f8 क्रम 0x00000000 to ensure no TX is pending.
	 */
	करो अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_SCH_TX_CMD);
		अगर (!val32) अणु
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retry--);

	अगर (!retry) अणु
		dev_warn(dev, "Failed to flush TX queue\n");
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	/* Disable CCK and OFDM, घड़ी gated */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_FUNC);
	val8 &= ~SYS_FUNC_BBRSTB;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC, val8);

	udelay(2);

	/* Reset whole BB */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_FUNC);
	val8 &= ~SYS_FUNC_BB_GLB_RSTN;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_FUNC, val8);

	/* Reset MAC TRX */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 &= 0xff00;
	val16 |= (CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE);
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 &= ~CR_SECURITY_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_DUAL_TSF_RST);
	val8 |= DUAL_TSF_TX_OK;
	rtl8xxxu_ग_लिखो8(priv, REG_DUAL_TSF_RST, val8);

out:
	वापस retval;
पूर्ण

अटल पूर्णांक rtl8192eu_active_to_emu(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	पूर्णांक count, ret = 0;

	/* Turn off RF */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_RF_CTRL);
	val8 &= ~RF_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, val8);

	/* Switch DPDT_SEL_P output from रेजिस्टर 0x65[2] */
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

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8192eu_emu_to_disabled(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;

	/* 0x04[12:11] = 01 enable WL suspend */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	val8 |= BIT(3);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8192eu_घातer_on(काष्ठा rtl8xxxu_priv *priv)
अणु
	u16 val16;
	u32 val32;
	पूर्णांक ret;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_SYS_CFG);
	अगर (val32 & SYS_CFG_SPS_LDO_SEL) अणु
		rtl8xxxu_ग_लिखो8(priv, REG_LDO_SW_CTRL, 0xc3);
	पूर्ण अन्यथा अणु
		/*
		 * Raise 1.2V voltage
		 */
		val32 = rtl8xxxu_पढ़ो32(priv, REG_8192E_LDOV12_CTRL);
		val32 &= 0xff0fffff;
		val32 |= 0x00500000;
		rtl8xxxu_ग_लिखो32(priv, REG_8192E_LDOV12_CTRL, val32);
		rtl8xxxu_ग_लिखो8(priv, REG_LDO_SW_CTRL, 0x83);
	पूर्ण

	/*
	 * Adjust AFE beक्रमe enabling PLL
	 */
	rtl8192e_crystal_afe_adjust(priv);
	rtl8192e_disabled_to_emu(priv);

	ret = rtl8192e_emu_to_active(priv);
	अगर (ret)
		जाओ निकास;

	rtl8xxxu_ग_लिखो16(priv, REG_CR, 0x0000);

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

निकास:
	वापस ret;
पूर्ण

अटल व्योम rtl8192eu_घातer_off(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;

	rtl8xxxu_flush_fअगरo(priv);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_TX_REPORT_CTRL);
	val8 &= ~TX_REPORT_CTRL_TIMER_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_TX_REPORT_CTRL, val8);

	/* Turn off RF */
	rtl8xxxu_ग_लिखो8(priv, REG_RF_CTRL, 0x00);

	rtl8192eu_active_to_lps(priv);

	/* Reset Firmware अगर running in RAM */
	अगर (rtl8xxxu_पढ़ो8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);

	/* Reset MCU */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_FUNC, val16);

	/* Reset MCU पढ़ोy status */
	rtl8xxxu_ग_लिखो8(priv, REG_MCU_FW_DL, 0x00);

	rtl8xxxu_reset_8051(priv);

	rtl8192eu_active_to_emu(priv);
	rtl8192eu_emu_to_disabled(priv);
पूर्ण

अटल व्योम rtl8192e_enable_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	u32 val32;
	u8 val8;

	val32 = rtl8xxxu_पढ़ो32(priv, REG_RX_WAIT_CCA);
	val32 |= (BIT(22) | BIT(23));
	rtl8xxxu_ग_लिखो32(priv, REG_RX_WAIT_CCA, val32);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_GPIO_MUXCFG);
	val8 |= BIT(5);
	rtl8xxxu_ग_लिखो8(priv, REG_GPIO_MUXCFG, val8);

	/*
	 * WLAN action by PTA
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_WLAN_ACT_CONTROL_8723B, 0x04);

	val32 = rtl8xxxu_पढ़ो32(priv, REG_PWR_DATA);
	val32 |= PWR_DATA_EEPRPAD_RFE_CTRL_EN;
	rtl8xxxu_ग_लिखो32(priv, REG_PWR_DATA, val32);

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
पूर्ण

काष्ठा rtl8xxxu_fileops rtl8192eu_fops = अणु
	.parse_efuse = rtl8192eu_parse_efuse,
	.load_firmware = rtl8192eu_load_firmware,
	.घातer_on = rtl8192eu_घातer_on,
	.घातer_off = rtl8192eu_घातer_off,
	.reset_8051 = rtl8xxxu_reset_8051,
	.llt_init = rtl8xxxu_स्वतः_llt_table,
	.init_phy_bb = rtl8192eu_init_phy_bb,
	.init_phy_rf = rtl8192eu_init_phy_rf,
	.phy_iq_calibrate = rtl8192eu_phy_iq_calibrate,
	.config_channel = rtl8xxxu_gen2_config_channel,
	.parse_rx_desc = rtl8xxxu_parse_rxdesc24,
	.enable_rf = rtl8192e_enable_rf,
	.disable_rf = rtl8xxxu_gen2_disable_rf,
	.usb_quirks = rtl8xxxu_gen2_usb_quirks,
	.set_tx_घातer = rtl8192e_set_tx_घातer,
	.update_rate_mask = rtl8xxxu_gen2_update_rate_mask,
	.report_connect = rtl8xxxu_gen2_report_connect,
	.fill_txdesc = rtl8xxxu_fill_txdesc_v2,
	.ग_लिखोN_block_size = 128,
	.tx_desc_size = माप(काष्ठा rtl8xxxu_txdesc40),
	.rx_desc_size = माप(काष्ठा rtl8xxxu_rxdesc24),
	.has_s0s1 = 0,
	.gen2_thermal_meter = 1,
	.adda_1t_init = 0x0fc01616,
	.adda_1t_path_on = 0x0fc01616,
	.adda_2t_path_on_a = 0x0fc01616,
	.adda_2t_path_on_b = 0x0fc01616,
	.trxff_boundary = 0x3cff,
	.mactable = rtl8192e_mac_init_table,
	.total_page_num = TX_TOTAL_PAGE_NUM_8192E,
	.page_num_hi = TX_PAGE_NUM_HI_PQ_8192E,
	.page_num_lo = TX_PAGE_NUM_LO_PQ_8192E,
	.page_num_norm = TX_PAGE_NUM_NORM_PQ_8192E,
पूर्ण;
