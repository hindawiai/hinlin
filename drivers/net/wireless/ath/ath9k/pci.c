<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/nl80211.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "ath9k.h"

बाह्य पूर्णांक ath9k_use_msi;

अटल स्थिर काष्ठा pci_device_id ath_pci_id_table[] = अणु
	अणु PCI_VDEVICE(ATHEROS, 0x0023) पूर्ण, /* PCI   */
	अणु PCI_VDEVICE(ATHEROS, 0x0024) पूर्ण, /* PCI-E */
	अणु PCI_VDEVICE(ATHEROS, 0x0027) पूर्ण, /* PCI   */

#अगर_घोषित CONFIG_ATH9K_PCOEM
	/* Mini PCI AR9220 MB92 cards: Compex WLM200NX, Wistron DNMA-92 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0029,
			 PCI_VENDOR_ID_ATHEROS,
			 0x2096),
	  .driver_data = ATH9K_PCI_LED_ACT_HI पूर्ण,
#पूर्ण_अगर

	अणु PCI_VDEVICE(ATHEROS, 0x0029) पूर्ण, /* PCI   */

#अगर_घोषित CONFIG_ATH9K_PCOEM
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1C71),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE01F),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x11AD, /* LITEON */
			 0x6632),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x11AD, /* LITEON */
			 0x6642),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 PCI_VENDOR_ID_QMI,
			 0x0306),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x185F, /* WNC */
			 0x309D),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x147C),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x147D),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x1536),
	  .driver_data = ATH9K_PCI_D3_L1_WAR पूर्ण,
#पूर्ण_अगर

	अणु PCI_VDEVICE(ATHEROS, 0x002A) पूर्ण, /* PCI-E */

#अगर_घोषित CONFIG_ATH9K_PCOEM
	/* AR9285 card क्रम Asus */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x002B,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2C37),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
#पूर्ण_अगर

	अणु PCI_VDEVICE(ATHEROS, 0x002B) पूर्ण, /* PCI-E */
	अणु PCI_VDEVICE(ATHEROS, 0x002C) पूर्ण, /* PCI-E 802.11n bonded out */
	अणु PCI_VDEVICE(ATHEROS, 0x002D) पूर्ण, /* PCI   */
	अणु PCI_VDEVICE(ATHEROS, 0x002E) पूर्ण, /* PCI-E */

	/* Killer Wireless (3x3) */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0030,
			 0x1A56,
			 0x2000),
	  .driver_data = ATH9K_PCI_KILLER पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0030,
			 0x1A56,
			 0x2001),
	  .driver_data = ATH9K_PCI_KILLER पूर्ण,

	अणु PCI_VDEVICE(ATHEROS, 0x0030) पूर्ण, /* PCI-E  AR9300 */

#अगर_घोषित CONFIG_ATH9K_PCOEM
	/* PCI-E CUS198 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2086),
	  .driver_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1237),
	  .driver_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2126),
	  .driver_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x126A),
	  .driver_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV पूर्ण,

	/* PCI-E CUS230 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2152),
	  .driver_data = ATH9K_PCI_CUS230 | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE075),
	  .driver_data = ATH9K_PCI_CUS230 | ATH9K_PCI_BT_ANT_DIV पूर्ण,

	/* WB225 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3119),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3122),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x185F, /* WNC */
			 0x3119),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x185F, /* WNC */
			 0x3027),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x4105),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x4106),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x410D),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x410E),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x410F),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0xC706),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0xC680),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_SAMSUNG,
			 0xC708),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_LENOVO,
			 0x3218),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_LENOVO,
			 0x3219),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,

	/* AR9485 cards with PLL घातer-save disabled by शेष. */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2C97),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2100),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x1C56, /* ASKEY */
			 0x4001),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x11AD, /* LITEON */
			 0x6627),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x11AD, /* LITEON */
			 0x6628),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE04E),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE04F),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x144F, /* ASKEY */
			 0x7197),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x2000),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x2001),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1186),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1F86),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1195),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_AZWAVE,
			 0x1F95),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x1C00),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x1C01),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0032,
			 PCI_VENDOR_ID_ASUSTEK,
			 0x850D),
	  .driver_data = ATH9K_PCI_NO_PLL_PWRSAVE पूर्ण,
#पूर्ण_अगर

	अणु PCI_VDEVICE(ATHEROS, 0x0032) पूर्ण, /* PCI-E  AR9485 */
	अणु PCI_VDEVICE(ATHEROS, 0x0033) पूर्ण, /* PCI-E  AR9580 */

#अगर_घोषित CONFIG_ATH9K_PCOEM
	/* PCI-E CUS217 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2116),
	  .driver_data = ATH9K_PCI_CUS217 पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x11AD, /* LITEON */
			 0x6661),
	  .driver_data = ATH9K_PCI_CUS217 पूर्ण,

	/* AR9462 with WoW support */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3117),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_LENOVO,
			 0x3214),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_ATTANSIC,
			 0x0091),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2110),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_ASUSTEK,
			 0x850E),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x11AD, /* LITEON */
			 0x6631),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x11AD, /* LITEON */
			 0x6641),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_HP,
			 0x1864),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x14CD, /* USI */
			 0x0063),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x14CD, /* USI */
			 0x0064),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 0x10CF, /* Fujitsu */
			 0x1783),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_DELL,
			 0x020B),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0034,
			 PCI_VENDOR_ID_DELL,
			 0x0300),
	  .driver_data = ATH9K_PCI_WOW पूर्ण,

	/* Killer Wireless (2x2) */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0030,
			 0x1A56,
			 0x2003),
	  .driver_data = ATH9K_PCI_KILLER पूर्ण,

	अणु PCI_VDEVICE(ATHEROS, 0x0034) पूर्ण, /* PCI-E  AR9462 */
	अणु PCI_VDEVICE(ATHEROS, 0x0037) पूर्ण, /* PCI-E  AR1111/AR9485 */

	/* CUS252 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3028),
	  .driver_data = ATH9K_PCI_CUS252 |
			 ATH9K_PCI_AR9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2176),
	  .driver_data = ATH9K_PCI_CUS252 |
			 ATH9K_PCI_AR9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV पूर्ण,

	/* WB335 1-ANT */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE068),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x185F, /* WNC */
			 0xA119),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0632),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x06B2),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0842),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x1842),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x6671),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2811),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2812),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A1),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A3),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x218A),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2F8A),
	  .driver_data = ATH9K_PCI_AR9565_1ANT पूर्ण,

	/* WB335 1-ANT / Antenna Diversity */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3025),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3026),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x302B),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE069),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x185F, /* WNC */
			 0x3028),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0622),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0672),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0662),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x06A2),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0682),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x213A),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x213C),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_HP,
			 0x18E3),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_HP,
			 0x217F),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_HP,
			 0x2005),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_DELL,
			 0x020C),
	  .driver_data = ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,

	/* WB335 2-ANT / Antenna-Diversity */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x411A),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x411B),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x411C),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x411D),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x411E),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x4129),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_SAMSUNG,
			 0x412A),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x3027),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ATHEROS,
			 0x302C),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0642),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0652),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0612),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0832),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x1832),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0692),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0803),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x11AD, /* LITEON */
			 0x0813),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2130),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x213B),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2182),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x218B),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x218C),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_AZWAVE,
			 0x2F82),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x144F, /* ASKEY */
			 0x7202),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2810),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2813),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A2),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A4),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x185F, /* WNC */
			 0x3027),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 0x185F, /* WNC */
			 0xA120),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE07F),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE08F),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE081),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE091),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_FOXCONN,
			 0xE099),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_LENOVO,
			 0x3026),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_LENOVO,
			 0x4026),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_ASUSTEK,
			 0x85F2),
	  .driver_data = ATH9K_PCI_AR9565_2ANT | ATH9K_PCI_BT_ANT_DIV पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_ATHEROS,
			 0x0036,
			 PCI_VENDOR_ID_DELL,
			 0x020E),
	  .driver_data = ATH9K_PCI_AR9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV |
			 ATH9K_PCI_LED_ACT_HIपूर्ण,

	/* PCI-E AR9565 (WB335) */
	अणु PCI_VDEVICE(ATHEROS, 0x0036),
	  .driver_data = ATH9K_PCI_BT_ANT_DIV पूर्ण,
#पूर्ण_अगर

	अणु 0 पूर्ण
पूर्ण;


/* वापस bus cachesize in 4B word units */
अटल व्योम ath_pci_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;
	u8 u8पंचांगp;

	pci_पढ़ो_config_byte(to_pci_dev(sc->dev), PCI_CACHE_LINE_SIZE, &u8पंचांगp);
	*csz = (पूर्णांक)u8पंचांगp;

	/*
	 * This check was put in to aव्योम "unpleasant" consequences अगर
	 * the bootrom has not fully initialized all PCI devices.
	 * Someबार the cache line size रेजिस्टर is not set
	 */

	अगर (*csz == 0)
		*csz = DEFAULT_CACHELINE >> 2;   /* Use the शेष size */
पूर्ण

अटल bool ath_pci_eeprom_पढ़ो(काष्ठा ath_common *common, u32 off, u16 *data)
अणु
	काष्ठा ath_hw *ah = (काष्ठा ath_hw *) common->ah;

	common->ops->पढ़ो(ah, AR5416_EEPROM_OFFSET + (off << AR5416_EEPROM_S));

	अगर (!ath9k_hw_रुको(ah,
				AR_EEPROM_STATUS_DATA,
				AR_EEPROM_STATUS_DATA_BUSY |
				AR_EEPROM_STATUS_DATA_PROT_ACCESS, 0,
				AH_WAIT_TIMEOUT)) अणु
		वापस false;
	पूर्ण

	*data = MS(common->ops->पढ़ो(ah, AR_EEPROM_STATUS_DATA),
			AR_EEPROM_STATUS_DATA_VAL);

	वापस true;
पूर्ण

/* Need to be called after we discover btcoex capabilities */
अटल व्योम ath_pci_aspm_init(काष्ठा ath_common *common)
अणु
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा pci_dev *pdev = to_pci_dev(sc->dev);
	काष्ठा pci_dev *parent;
	u16 aspm;
	पूर्णांक ret;

	अगर (!ah->is_pciexpress)
		वापस;

	parent = pdev->bus->self;
	अगर (!parent)
		वापस;

	अगर ((ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_NONE) &&
	    (AR_SREV_9285(ah))) अणु
		/* Bluetooth coexistence requires disabling ASPM. */
		pcie_capability_clear_word(pdev, PCI_EXP_LNKCTL,
			PCI_EXP_LNKCTL_ASPM_L0S | PCI_EXP_LNKCTL_ASPM_L1);

		/*
		 * Both upstream and करोwnstream PCIe components should
		 * have the same ASPM settings.
		 */
		pcie_capability_clear_word(parent, PCI_EXP_LNKCTL,
			PCI_EXP_LNKCTL_ASPM_L0S | PCI_EXP_LNKCTL_ASPM_L1);

		ath_info(common, "Disabling ASPM since BTCOEX is enabled\n");
		वापस;
	पूर्ण

	/*
	 * 0x70c - Ack Frequency Register.
	 *
	 * Bits 27:29 - DEFAULT_L1_ENTRANCE_LATENCY.
	 *
	 * 000 : 1 us
	 * 001 : 2 us
	 * 010 : 4 us
	 * 011 : 8 us
	 * 100 : 16 us
	 * 101 : 32 us
	 * 110/111 : 64 us
	 */
	अगर (AR_SREV_9462(ah))
		pci_पढ़ो_config_dword(pdev, 0x70c, &ah->config.aspm_l1_fix);

	ret = pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL, &aspm);
	अगर (!ret && (aspm & (PCI_EXP_LNKCTL_ASPM_L0S | PCI_EXP_LNKCTL_ASPM_L1))) अणु
		ah->aspm_enabled = true;
		/* Initialize PCIe PM and SERDES रेजिस्टरs. */
		ath9k_hw_configpciघातersave(ah, false);
		ath_info(common, "ASPM enabled: 0x%x\n", aspm);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ath_bus_ops ath_pci_bus_ops = अणु
	.ath_bus_type = ATH_PCI,
	.पढ़ो_cachesize = ath_pci_पढ़ो_cachesize,
	.eeprom_पढ़ो = ath_pci_eeprom_पढ़ो,
	.aspm_init = ath_pci_aspm_init,
पूर्ण;

अटल पूर्णांक ath_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ath_softc *sc;
	काष्ठा ieee80211_hw *hw;
	u8 csz;
	u32 val;
	पूर्णांक ret = 0;
	अक्षर hw_name[64];
	पूर्णांक msi_enabled = 0;

	अगर (pcim_enable_device(pdev))
		वापस -EIO;

	ret =  pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		pr_err("32-bit DMA not available\n");
		वापस ret;
	पूर्ण

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		pr_err("32-bit DMA consistent DMA enable failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Cache line size is used to size and align various
	 * काष्ठाures used to communicate with the hardware.
	 */
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &csz);
	अगर (csz == 0) अणु
		/*
		 * Linux 2.4.18 (at least) ग_लिखोs the cache line size
		 * रेजिस्टर as a 16-bit wide रेजिस्टर which is wrong.
		 * We must have this setup properly क्रम rx buffer
		 * DMA to work so क्रमce a reasonable value here अगर it
		 * comes up zero.
		 */
		csz = L1_CACHE_BYTES / माप(u32);
		pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE, csz);
	पूर्ण
	/*
	 * The शेष setting of latency समयr yields poor results,
	 * set it to the value used by other प्रणालीs. It may be worth
	 * tweaking this setting more.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0xa8);

	pci_set_master(pdev);

	/*
	 * Disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state.
	 */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	ret = pcim_iomap_regions(pdev, BIT(0), "ath9k");
	अगर (ret) अणु
		dev_err(&pdev->dev, "PCI memory region reserve error\n");
		वापस -ENODEV;
	पूर्ण

	ath9k_fill_chanctx_ops();
	hw = ieee80211_alloc_hw(माप(काष्ठा ath_softc), &ath9k_ops);
	अगर (!hw) अणु
		dev_err(&pdev->dev, "No memory for ieee80211_hw\n");
		वापस -ENOMEM;
	पूर्ण

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_drvdata(pdev, hw);

	sc = hw->priv;
	sc->hw = hw;
	sc->dev = &pdev->dev;
	sc->mem = pcim_iomap_table(pdev)[0];
	sc->driver_data = id->driver_data;

	अगर (ath9k_use_msi) अणु
		अगर (pci_enable_msi(pdev) == 0) अणु
			msi_enabled = 1;
			dev_err(&pdev->dev, "Using MSI\n");
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Using INTx\n");
		पूर्ण
	पूर्ण

	अगर (!msi_enabled)
		ret = request_irq(pdev->irq, ath_isr, IRQF_SHARED, "ath9k", sc);
	अन्यथा
		ret = request_irq(pdev->irq, ath_isr, 0, "ath9k", sc);

	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ err_irq;
	पूर्ण

	sc->irq = pdev->irq;

	ret = ath9k_init_device(id->device, sc, &ath_pci_bus_ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize device\n");
		जाओ err_init;
	पूर्ण

	sc->sc_ah->msi_enabled = msi_enabled;
	sc->sc_ah->msi_reg = 0;

	ath9k_hw_name(sc->sc_ah, hw_name, माप(hw_name));
	wiphy_info(hw->wiphy, "%s mem=0x%lx, irq=%d\n",
		   hw_name, (अचिन्हित दीर्घ)sc->mem, pdev->irq);

	वापस 0;

err_init:
	मुक्त_irq(sc->irq, sc);
err_irq:
	ieee80211_मुक्त_hw(hw);
	वापस ret;
पूर्ण

अटल व्योम ath_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा ath_softc *sc = hw->priv;

	अगर (!is_ath9k_unloaded)
		sc->sc_ah->ah_flags |= AH_UNPLUGGED;
	ath9k_deinit_device(sc);
	मुक्त_irq(sc->irq, sc);
	ieee80211_मुक्त_hw(sc->hw);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ath_pci_suspend(काष्ठा device *device)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(device);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (test_bit(ATH_OP_WOW_ENABLED, &common->op_flags)) अणु
		dev_info(device, "WOW is enabled, bypassing PCI suspend\n");
		वापस 0;
	पूर्ण

	/* The device has to be moved to FULLSLEEP क्रमcibly.
	 * Otherwise the chip never moved to full sleep,
	 * when no पूर्णांकerface is up.
	 */
	ath9k_stop_btcoex(sc);
	ath9k_hw_disable(sc->sc_ah);
	del_समयr_sync(&sc->sleep_समयr);
	ath9k_hw_setघातer(sc->sc_ah, ATH9K_PM_FULL_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक ath_pci_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 val;

	/*
	 * Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state
	 */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	ath_pci_aspm_init(common);
	ah->reset_घातer_on = false;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath9k_pm_ops, ath_pci_suspend, ath_pci_resume);

#घोषणा ATH9K_PM_OPS	(&ath9k_pm_ops)

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा ATH9K_PM_OPS	शून्य

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */


MODULE_DEVICE_TABLE(pci, ath_pci_id_table);

अटल काष्ठा pci_driver ath_pci_driver = अणु
	.name       = "ath9k",
	.id_table   = ath_pci_id_table,
	.probe      = ath_pci_probe,
	.हटाओ     = ath_pci_हटाओ,
	.driver.pm  = ATH9K_PM_OPS,
पूर्ण;

पूर्णांक ath_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&ath_pci_driver);
पूर्ण

व्योम ath_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ath_pci_driver);
पूर्ण
