<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2016-2017 Socionext Inc.
//   Author: Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pinctrl-uniphier.h"

अटल स्थिर काष्ठा pinctrl_pin_desc uniphier_ld11_pins[] = अणु
	UNIPHIER_PINCTRL_PIN(0, "XECS1", UNIPHIER_PIN_IECTRL_EXIST,
			     0, UNIPHIER_PIN_DRV_1BIT,
			     0, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(1, "ERXW", UNIPHIER_PIN_IECTRL_NONE,
			     1, UNIPHIER_PIN_DRV_1BIT,
			     1, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(2, "XERWE1", UNIPHIER_PIN_IECTRL_NONE,
			     2, UNIPHIER_PIN_DRV_1BIT,
			     2, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(3, "XNFWP", UNIPHIER_PIN_IECTRL_EXIST,
			     3, UNIPHIER_PIN_DRV_1BIT,
			     3, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(4, "XNFCE0", UNIPHIER_PIN_IECTRL_EXIST,
			     4, UNIPHIER_PIN_DRV_1BIT,
			     4, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(5, "NFRYBY0", UNIPHIER_PIN_IECTRL_EXIST,
			     5, UNIPHIER_PIN_DRV_1BIT,
			     5, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(6, "XNFRE", UNIPHIER_PIN_IECTRL_NONE,
			     6, UNIPHIER_PIN_DRV_1BIT,
			     6, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(7, "XNFWE", UNIPHIER_PIN_IECTRL_NONE,
			     7, UNIPHIER_PIN_DRV_1BIT,
			     7, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(8, "NFALE", UNIPHIER_PIN_IECTRL_NONE,
			     8, UNIPHIER_PIN_DRV_1BIT,
			     8, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(9, "NFCLE", UNIPHIER_PIN_IECTRL_NONE,
			     9, UNIPHIER_PIN_DRV_1BIT,
			     9, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(10, "NFD0", UNIPHIER_PIN_IECTRL_EXIST,
			     10, UNIPHIER_PIN_DRV_1BIT,
			     10, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(11, "NFD1", UNIPHIER_PIN_IECTRL_EXIST,
			     11, UNIPHIER_PIN_DRV_1BIT,
			     11, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(12, "NFD2", UNIPHIER_PIN_IECTRL_EXIST,
			     12, UNIPHIER_PIN_DRV_1BIT,
			     12, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(13, "NFD3", UNIPHIER_PIN_IECTRL_EXIST,
			     13, UNIPHIER_PIN_DRV_1BIT,
			     13, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(14, "NFD4", UNIPHIER_PIN_IECTRL_EXIST,
			     14, UNIPHIER_PIN_DRV_1BIT,
			     14, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(15, "NFD5", UNIPHIER_PIN_IECTRL_EXIST,
			     15, UNIPHIER_PIN_DRV_1BIT,
			     15, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(16, "NFD6", UNIPHIER_PIN_IECTRL_EXIST,
			     16, UNIPHIER_PIN_DRV_1BIT,
			     16, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(17, "NFD7", UNIPHIER_PIN_IECTRL_EXIST,
			     17, UNIPHIER_PIN_DRV_1BIT,
			     17, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(18, "XERST", UNIPHIER_PIN_IECTRL_EXIST,
			     0, UNIPHIER_PIN_DRV_2BIT,
			     18, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(19, "MMCCLK", UNIPHIER_PIN_IECTRL_EXIST,
			     1, UNIPHIER_PIN_DRV_2BIT,
			     19, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(20, "MMCCMD", UNIPHIER_PIN_IECTRL_EXIST,
			     2, UNIPHIER_PIN_DRV_2BIT,
			     20, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(21, "MMCDS", UNIPHIER_PIN_IECTRL_EXIST,
			     3, UNIPHIER_PIN_DRV_2BIT,
			     21, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(22, "MMCDAT0", UNIPHIER_PIN_IECTRL_EXIST,
			     4, UNIPHIER_PIN_DRV_2BIT,
			     22, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(23, "MMCDAT1", UNIPHIER_PIN_IECTRL_EXIST,
			     5, UNIPHIER_PIN_DRV_2BIT,
			     23, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(24, "MMCDAT2", UNIPHIER_PIN_IECTRL_EXIST,
			     6, UNIPHIER_PIN_DRV_2BIT,
			     24, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(25, "MMCDAT3", UNIPHIER_PIN_IECTRL_EXIST,
			     7, UNIPHIER_PIN_DRV_2BIT,
			     25, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(26, "MMCDAT4", UNIPHIER_PIN_IECTRL_EXIST,
			     8, UNIPHIER_PIN_DRV_2BIT,
			     26, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(27, "MMCDAT5", UNIPHIER_PIN_IECTRL_EXIST,
			     9, UNIPHIER_PIN_DRV_2BIT,
			     27, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(28, "MMCDAT6", UNIPHIER_PIN_IECTRL_EXIST,
			     10, UNIPHIER_PIN_DRV_2BIT,
			     28, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(29, "MMCDAT7", UNIPHIER_PIN_IECTRL_EXIST,
			     11, UNIPHIER_PIN_DRV_2BIT,
			     29, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(46, "USB0VBUS", UNIPHIER_PIN_IECTRL_EXIST,
			     46, UNIPHIER_PIN_DRV_1BIT,
			     46, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(47, "USB0OD", UNIPHIER_PIN_IECTRL_NONE,
			     47, UNIPHIER_PIN_DRV_1BIT,
			     47, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(48, "USB1VBUS", UNIPHIER_PIN_IECTRL_EXIST,
			     48, UNIPHIER_PIN_DRV_1BIT,
			     48, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(49, "USB1OD", UNIPHIER_PIN_IECTRL_EXIST,
			     49, UNIPHIER_PIN_DRV_1BIT,
			     49, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(50, "USB2VBUS", UNIPHIER_PIN_IECTRL_EXIST,
			     50, UNIPHIER_PIN_DRV_1BIT,
			     50, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(51, "USB2OD", UNIPHIER_PIN_IECTRL_EXIST,
			     51, UNIPHIER_PIN_DRV_1BIT,
			     51, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(54, "TXD0", UNIPHIER_PIN_IECTRL_EXIST,
			     54, UNIPHIER_PIN_DRV_1BIT,
			     54, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(55, "RXD0", UNIPHIER_PIN_IECTRL_EXIST,
			     55, UNIPHIER_PIN_DRV_1BIT,
			     55, UNIPHIER_PIN_PULL_UP),
	UNIPHIER_PINCTRL_PIN(56, "SPISYNC0", UNIPHIER_PIN_IECTRL_EXIST,
			     56, UNIPHIER_PIN_DRV_1BIT,
			     56, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(57, "SPISCLK0", UNIPHIER_PIN_IECTRL_EXIST,
			     57, UNIPHIER_PIN_DRV_1BIT,
			     57, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(58, "SPITXD0", UNIPHIER_PIN_IECTRL_EXIST,
			     58, UNIPHIER_PIN_DRV_1BIT,
			     58, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(59, "SPIRXD0", UNIPHIER_PIN_IECTRL_EXIST,
			     59, UNIPHIER_PIN_DRV_1BIT,
			     59, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(60, "AGCI", UNIPHIER_PIN_IECTRL_EXIST,
			     60, UNIPHIER_PIN_DRV_1BIT,
			     60, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(61, "DMDSDA0", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(62, "DMDSCL0", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(63, "SDA0", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(64, "SCL0", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(65, "SDA1", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(66, "SCL1", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED4,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(67, "HIN", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED5,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(68, "VIN", UNIPHIER_PIN_IECTRL_EXIST,
			     -1, UNIPHIER_PIN_DRV_FIXED5,
			     -1, UNIPHIER_PIN_PULL_NONE),
	UNIPHIER_PINCTRL_PIN(69, "PCA00", UNIPHIER_PIN_IECTRL_EXIST,
			     69, UNIPHIER_PIN_DRV_1BIT,
			     69, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(70, "PCA01", UNIPHIER_PIN_IECTRL_EXIST,
			     70, UNIPHIER_PIN_DRV_1BIT,
			     70, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(71, "PCA02", UNIPHIER_PIN_IECTRL_EXIST,
			     71, UNIPHIER_PIN_DRV_1BIT,
			     71, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(72, "PCA03", UNIPHIER_PIN_IECTRL_EXIST,
			     72, UNIPHIER_PIN_DRV_1BIT,
			     72, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(73, "PCA04", UNIPHIER_PIN_IECTRL_EXIST,
			     73, UNIPHIER_PIN_DRV_1BIT,
			     73, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(74, "PCA05", UNIPHIER_PIN_IECTRL_EXIST,
			     74, UNIPHIER_PIN_DRV_1BIT,
			     74, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(75, "PCA06", UNIPHIER_PIN_IECTRL_EXIST,
			     75, UNIPHIER_PIN_DRV_1BIT,
			     75, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(76, "PCA07", UNIPHIER_PIN_IECTRL_EXIST,
			     76, UNIPHIER_PIN_DRV_1BIT,
			     76, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(77, "PCA08", UNIPHIER_PIN_IECTRL_EXIST,
			     77, UNIPHIER_PIN_DRV_1BIT,
			     77, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(78, "PCA09", UNIPHIER_PIN_IECTRL_EXIST,
			     78, UNIPHIER_PIN_DRV_1BIT,
			     78, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(79, "PCA10", UNIPHIER_PIN_IECTRL_EXIST,
			     79, UNIPHIER_PIN_DRV_1BIT,
			     79, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(80, "PCA11", UNIPHIER_PIN_IECTRL_EXIST,
			     80, UNIPHIER_PIN_DRV_1BIT,
			     80, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(81, "PCA12", UNIPHIER_PIN_IECTRL_EXIST,
			     81, UNIPHIER_PIN_DRV_1BIT,
			     81, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(82, "PCA13", UNIPHIER_PIN_IECTRL_EXIST,
			     82, UNIPHIER_PIN_DRV_1BIT,
			     82, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(83, "PCA14", UNIPHIER_PIN_IECTRL_EXIST,
			     83, UNIPHIER_PIN_DRV_1BIT,
			     83, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(84, "PC0READY", UNIPHIER_PIN_IECTRL_EXIST,
			     84, UNIPHIER_PIN_DRV_1BIT,
			     84, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(85, "PC0CD1", UNIPHIER_PIN_IECTRL_EXIST,
			     85, UNIPHIER_PIN_DRV_1BIT,
			     85, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(86, "PC0CD2", UNIPHIER_PIN_IECTRL_EXIST,
			     86, UNIPHIER_PIN_DRV_1BIT,
			     86, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(87, "PC0WAIT", UNIPHIER_PIN_IECTRL_EXIST,
			     87, UNIPHIER_PIN_DRV_1BIT,
			     87, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(88, "PC0RESET", UNIPHIER_PIN_IECTRL_EXIST,
			     88, UNIPHIER_PIN_DRV_1BIT,
			     88, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(89, "PC0CE1", UNIPHIER_PIN_IECTRL_EXIST,
			     89, UNIPHIER_PIN_DRV_1BIT,
			     89, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(90, "PC0WE", UNIPHIER_PIN_IECTRL_EXIST,
			     90, UNIPHIER_PIN_DRV_1BIT,
			     90, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(91, "PC0OE", UNIPHIER_PIN_IECTRL_EXIST,
			     91, UNIPHIER_PIN_DRV_1BIT,
			     91, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(92, "PC0IOWR", UNIPHIER_PIN_IECTRL_EXIST,
			     92, UNIPHIER_PIN_DRV_1BIT,
			     92, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(93, "PC0IORD", UNIPHIER_PIN_IECTRL_EXIST,
			     93, UNIPHIER_PIN_DRV_1BIT,
			     93, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(94, "PCD00", UNIPHIER_PIN_IECTRL_EXIST,
			     94, UNIPHIER_PIN_DRV_1BIT,
			     94, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(95, "PCD01", UNIPHIER_PIN_IECTRL_EXIST,
			     95, UNIPHIER_PIN_DRV_1BIT,
			     95, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(96, "PCD02", UNIPHIER_PIN_IECTRL_EXIST,
			     96, UNIPHIER_PIN_DRV_1BIT,
			     96, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(97, "PCD03", UNIPHIER_PIN_IECTRL_EXIST,
			     97, UNIPHIER_PIN_DRV_1BIT,
			     97, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(98, "PCD04", UNIPHIER_PIN_IECTRL_EXIST,
			     98, UNIPHIER_PIN_DRV_1BIT,
			     98, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(99, "PCD05", UNIPHIER_PIN_IECTRL_EXIST,
			     99, UNIPHIER_PIN_DRV_1BIT,
			     99, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(100, "PCD06", UNIPHIER_PIN_IECTRL_EXIST,
			     100, UNIPHIER_PIN_DRV_1BIT,
			     100, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(101, "PCD07", UNIPHIER_PIN_IECTRL_EXIST,
			     101, UNIPHIER_PIN_DRV_1BIT,
			     101, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(102, "HS0BCLKIN", UNIPHIER_PIN_IECTRL_EXIST,
			     102, UNIPHIER_PIN_DRV_1BIT,
			     102, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(103, "HS0SYNCIN", UNIPHIER_PIN_IECTRL_EXIST,
			     103, UNIPHIER_PIN_DRV_1BIT,
			     103, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(104, "HS0VALIN", UNIPHIER_PIN_IECTRL_EXIST,
			     104, UNIPHIER_PIN_DRV_1BIT,
			     104, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(105, "HS0DIN0", UNIPHIER_PIN_IECTRL_EXIST,
			     105, UNIPHIER_PIN_DRV_1BIT,
			     105, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(106, "HS0DIN1", UNIPHIER_PIN_IECTRL_EXIST,
			     106, UNIPHIER_PIN_DRV_1BIT,
			     106, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(107, "HS0DIN2", UNIPHIER_PIN_IECTRL_EXIST,
			     107, UNIPHIER_PIN_DRV_1BIT,
			     107, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(108, "HS0DIN3", UNIPHIER_PIN_IECTRL_EXIST,
			     108, UNIPHIER_PIN_DRV_1BIT,
			     108, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(109, "HS0DIN4", UNIPHIER_PIN_IECTRL_EXIST,
			     109, UNIPHIER_PIN_DRV_1BIT,
			     109, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(110, "HS0DIN5", UNIPHIER_PIN_IECTRL_EXIST,
			     110, UNIPHIER_PIN_DRV_1BIT,
			     110, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(111, "HS0DIN6", UNIPHIER_PIN_IECTRL_EXIST,
			     111, UNIPHIER_PIN_DRV_1BIT,
			     111, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(112, "HS0DIN7", UNIPHIER_PIN_IECTRL_EXIST,
			     112, UNIPHIER_PIN_DRV_1BIT,
			     112, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(113, "HS0BCLKOUT", UNIPHIER_PIN_IECTRL_EXIST,
			     113, UNIPHIER_PIN_DRV_1BIT,
			     113, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(114, "HS0SYNCOUT", UNIPHIER_PIN_IECTRL_EXIST,
			     114, UNIPHIER_PIN_DRV_1BIT,
			     114, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(115, "HS0VALOUT", UNIPHIER_PIN_IECTRL_EXIST,
			     115, UNIPHIER_PIN_DRV_1BIT,
			     115, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(116, "HS0DOUT0", UNIPHIER_PIN_IECTRL_EXIST,
			     116, UNIPHIER_PIN_DRV_1BIT,
			     116, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(117, "HS0DOUT1", UNIPHIER_PIN_IECTRL_EXIST,
			     117, UNIPHIER_PIN_DRV_1BIT,
			     117, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(118, "HS0DOUT2", UNIPHIER_PIN_IECTRL_EXIST,
			     118, UNIPHIER_PIN_DRV_1BIT,
			     118, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(119, "HS0DOUT3", UNIPHIER_PIN_IECTRL_EXIST,
			     119, UNIPHIER_PIN_DRV_1BIT,
			     119, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(120, "HS0DOUT4", UNIPHIER_PIN_IECTRL_EXIST,
			     120, UNIPHIER_PIN_DRV_1BIT,
			     120, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(121, "HS0DOUT5", UNIPHIER_PIN_IECTRL_EXIST,
			     121, UNIPHIER_PIN_DRV_1BIT,
			     121, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(122, "HS0DOUT6", UNIPHIER_PIN_IECTRL_EXIST,
			     122, UNIPHIER_PIN_DRV_1BIT,
			     122, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(123, "HS0DOUT7", UNIPHIER_PIN_IECTRL_EXIST,
			     123, UNIPHIER_PIN_DRV_1BIT,
			     123, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(124, "HS1BCLKIN", UNIPHIER_PIN_IECTRL_EXIST,
			     124, UNIPHIER_PIN_DRV_1BIT,
			     124, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(125, "HS1SYNCIN", UNIPHIER_PIN_IECTRL_EXIST,
			     125, UNIPHIER_PIN_DRV_1BIT,
			     125, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(126, "HS1VALIN", UNIPHIER_PIN_IECTRL_EXIST,
			     126, UNIPHIER_PIN_DRV_1BIT,
			     126, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(127, "HS1DIN0", UNIPHIER_PIN_IECTRL_EXIST,
			     127, UNIPHIER_PIN_DRV_1BIT,
			     127, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(128, "HS1DIN1", UNIPHIER_PIN_IECTRL_EXIST,
			     128, UNIPHIER_PIN_DRV_1BIT,
			     128, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(129, "HS1DIN2", UNIPHIER_PIN_IECTRL_EXIST,
			     129, UNIPHIER_PIN_DRV_1BIT,
			     129, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(130, "HS1DIN3", UNIPHIER_PIN_IECTRL_EXIST,
			     130, UNIPHIER_PIN_DRV_1BIT,
			     130, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(131, "HS1DIN4", UNIPHIER_PIN_IECTRL_EXIST,
			     131, UNIPHIER_PIN_DRV_1BIT,
			     131, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(132, "HS1DIN5", UNIPHIER_PIN_IECTRL_EXIST,
			     132, UNIPHIER_PIN_DRV_1BIT,
			     132, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(133, "HS1DIN6", UNIPHIER_PIN_IECTRL_EXIST,
			     133, UNIPHIER_PIN_DRV_1BIT,
			     133, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(134, "HS1DIN7", UNIPHIER_PIN_IECTRL_EXIST,
			     134, UNIPHIER_PIN_DRV_1BIT,
			     134, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(135, "AO1IEC", UNIPHIER_PIN_IECTRL_EXIST,
			     135, UNIPHIER_PIN_DRV_1BIT,
			     135, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(136, "AO1ARC", UNIPHIER_PIN_IECTRL_EXIST,
			     136, UNIPHIER_PIN_DRV_1BIT,
			     136, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(137, "AO1DACCK", UNIPHIER_PIN_IECTRL_EXIST,
			     137, UNIPHIER_PIN_DRV_1BIT,
			     137, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(138, "AO1BCK", UNIPHIER_PIN_IECTRL_EXIST,
			     138, UNIPHIER_PIN_DRV_1BIT,
			     138, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(139, "AO1LRCK", UNIPHIER_PIN_IECTRL_EXIST,
			     139, UNIPHIER_PIN_DRV_1BIT,
			     139, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(140, "AO1D0", UNIPHIER_PIN_IECTRL_EXIST,
			     140, UNIPHIER_PIN_DRV_1BIT,
			     140, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(141, "AO1D1", UNIPHIER_PIN_IECTRL_EXIST,
			     141, UNIPHIER_PIN_DRV_1BIT,
			     141, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(142, "AO1D2", UNIPHIER_PIN_IECTRL_EXIST,
			     142, UNIPHIER_PIN_DRV_1BIT,
			     142, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(143, "XIRQ9", UNIPHIER_PIN_IECTRL_EXIST,
			     143, UNIPHIER_PIN_DRV_1BIT,
			     143, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(144, "XIRQ10", UNIPHIER_PIN_IECTRL_EXIST,
			     144, UNIPHIER_PIN_DRV_1BIT,
			     144, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(145, "XIRQ11", UNIPHIER_PIN_IECTRL_EXIST,
			     145, UNIPHIER_PIN_DRV_1BIT,
			     145, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(146, "XIRQ13", UNIPHIER_PIN_IECTRL_EXIST,
			     146, UNIPHIER_PIN_DRV_1BIT,
			     146, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(147, "PWMA", UNIPHIER_PIN_IECTRL_EXIST,
			     147, UNIPHIER_PIN_DRV_1BIT,
			     147, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(148, "LR_GOUT", UNIPHIER_PIN_IECTRL_EXIST,
			     148, UNIPHIER_PIN_DRV_1BIT,
			     148, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(149, "XIRQ0", UNIPHIER_PIN_IECTRL_EXIST,
			     149, UNIPHIER_PIN_DRV_1BIT,
			     149, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(150, "XIRQ1", UNIPHIER_PIN_IECTRL_EXIST,
			     150, UNIPHIER_PIN_DRV_1BIT,
			     150, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(151, "XIRQ2", UNIPHIER_PIN_IECTRL_EXIST,
			     151, UNIPHIER_PIN_DRV_1BIT,
			     151, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(152, "XIRQ3", UNIPHIER_PIN_IECTRL_EXIST,
			     152, UNIPHIER_PIN_DRV_1BIT,
			     152, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(153, "XIRQ4", UNIPHIER_PIN_IECTRL_EXIST,
			     153, UNIPHIER_PIN_DRV_1BIT,
			     153, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(154, "XIRQ5", UNIPHIER_PIN_IECTRL_EXIST,
			     154, UNIPHIER_PIN_DRV_1BIT,
			     154, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(155, "XIRQ6", UNIPHIER_PIN_IECTRL_EXIST,
			     155, UNIPHIER_PIN_DRV_1BIT,
			     155, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(156, "XIRQ7", UNIPHIER_PIN_IECTRL_EXIST,
			     156, UNIPHIER_PIN_DRV_1BIT,
			     156, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(157, "XIRQ8", UNIPHIER_PIN_IECTRL_EXIST,
			     157, UNIPHIER_PIN_DRV_1BIT,
			     157, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(158, "AGCBS", UNIPHIER_PIN_IECTRL_EXIST,
			     158, UNIPHIER_PIN_DRV_1BIT,
			     158, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(159, "XIRQ21", UNIPHIER_PIN_IECTRL_EXIST,
			     159, UNIPHIER_PIN_DRV_1BIT,
			     159, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(160, "XIRQ22", UNIPHIER_PIN_IECTRL_EXIST,
			     160, UNIPHIER_PIN_DRV_1BIT,
			     160, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(161, "XIRQ23", UNIPHIER_PIN_IECTRL_EXIST,
			     161, UNIPHIER_PIN_DRV_1BIT,
			     161, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(162, "CH2CLK", UNIPHIER_PIN_IECTRL_EXIST,
			     162, UNIPHIER_PIN_DRV_1BIT,
			     162, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(163, "CH2PSYNC", UNIPHIER_PIN_IECTRL_EXIST,
			     163, UNIPHIER_PIN_DRV_1BIT,
			     163, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(164, "CH2VAL", UNIPHIER_PIN_IECTRL_EXIST,
			     164, UNIPHIER_PIN_DRV_1BIT,
			     164, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(165, "CH2DATA", UNIPHIER_PIN_IECTRL_EXIST,
			     165, UNIPHIER_PIN_DRV_1BIT,
			     165, UNIPHIER_PIN_PULL_DOWN),
	UNIPHIER_PINCTRL_PIN(166, "CK25O", UNIPHIER_PIN_IECTRL_EXIST,
			     166, UNIPHIER_PIN_DRV_1BIT,
			     166, UNIPHIER_PIN_PULL_DOWN),
पूर्ण;

अटल स्थिर अचिन्हित aout1_pins[] = अणु137, 138, 139, 140, 141, 142पूर्ण;
अटल स्थिर पूर्णांक aout1_muxvals[] = अणु0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित aoutiec1_pins[] = अणु135, 136पूर्ण;
अटल स्थिर पूर्णांक aoutiec1_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_pins[] = अणु19, 20, 21, 22, 23, 24, 25पूर्ण;
अटल स्थिर पूर्णांक emmc_muxvals[] = अणु0, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित emmc_dat8_pins[] = अणु26, 27, 28, 29पूर्ण;
अटल स्थिर पूर्णांक emmc_dat8_muxvals[] = अणु0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित ether_rmii_pins[] = अणु6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
					   16, 17पूर्ण;
अटल स्थिर पूर्णांक ether_rmii_muxvals[] = अणु4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4पूर्ण;
अटल स्थिर अचिन्हित hscin0_ci_pins[] = अणु102, 103, 104, 105, 106, 107, 108,
					  109, 110, 111, 112पूर्ण;
अटल स्थिर पूर्णांक hscin0_ci_muxvals[] = अणु1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1पूर्ण;
अटल स्थिर अचिन्हित hscin0_p_pins[] = अणु102, 103, 104, 105, 106, 107, 108, 109,
					 110, 111, 112पूर्ण;
अटल स्थिर पूर्णांक hscin0_p_muxvals[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित hscin0_s_pins[] = अणु116, 117, 118, 119पूर्ण;
अटल स्थिर पूर्णांक hscin0_s_muxvals[] = अणु3, 3, 3, 3पूर्ण;
अटल स्थिर अचिन्हित hscin1_p_pins[] = अणु124, 125, 126, 127, 128, 129, 130, 131,
					 132, 133, 134पूर्ण;
अटल स्थिर पूर्णांक hscin1_p_muxvals[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित hscin1_s_pins[] = अणु120, 121, 122, 123पूर्ण;
अटल स्थिर पूर्णांक hscin1_s_muxvals[] = अणु3, 3, 3, 3पूर्ण;
अटल स्थिर अचिन्हित hscin2_s_pins[] = अणु124, 125, 126, 127पूर्ण;
अटल स्थिर पूर्णांक hscin2_s_muxvals[] = अणु3, 3, 3, 3पूर्ण;
अटल स्थिर अचिन्हित hscout0_ci_pins[] = अणु113, 114, 115, 116, 117, 118, 119,
					   120, 121, 122, 123पूर्ण;
अटल स्थिर पूर्णांक hscout0_ci_muxvals[] = अणु1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1पूर्ण;
अटल स्थिर अचिन्हित hscout0_p_pins[] = अणु113, 114, 115, 116, 117, 118, 119,
					  120, 121, 122, 123पूर्ण;
अटल स्थिर पूर्णांक hscout0_p_muxvals[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित hscout0_s_pins[] = अणु116, 117, 118, 119पूर्ण;
अटल स्थिर पूर्णांक hscout0_s_muxvals[] = अणु4, 4, 4, 4पूर्ण;
अटल स्थिर अचिन्हित hscout1_s_pins[] = अणु120, 121, 122, 123पूर्ण;
अटल स्थिर पूर्णांक hscout1_s_muxvals[] = अणु4, 4, 4, 4पूर्ण;
अटल स्थिर अचिन्हित i2c0_pins[] = अणु63, 64पूर्ण;
अटल स्थिर पूर्णांक i2c0_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित i2c1_pins[] = अणु65, 66पूर्ण;
अटल स्थिर पूर्णांक i2c1_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित i2c3_pins[] = अणु67, 68पूर्ण;
अटल स्थिर पूर्णांक i2c3_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित i2c4_pins[] = अणु61, 62पूर्ण;
अटल स्थिर पूर्णांक i2c4_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित nand_pins[] = अणु3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
				     15, 16, 17पूर्ण;
अटल स्थिर पूर्णांक nand_muxvals[] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित spi0_pins[] = अणु56, 57, 58, 59पूर्ण;
अटल स्थिर पूर्णांक spi0_muxvals[] = अणु0, 0, 0, 0पूर्ण;
अटल स्थिर अचिन्हित spi1_pins[] = अणु169, 170, 171, 172पूर्ण;
अटल स्थिर पूर्णांक spi1_muxvals[] = अणु1, 1, 1, 1पूर्ण;
अटल स्थिर अचिन्हित प्रणाली_bus_pins[] = अणु1, 2, 6, 7, 8, 9, 10, 11, 12, 13,
					   14, 15, 16, 17पूर्ण;
अटल स्थिर पूर्णांक प्रणाली_bus_muxvals[] = अणु0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
					 2पूर्ण;
अटल स्थिर अचिन्हित प्रणाली_bus_cs1_pins[] = अणु0पूर्ण;
अटल स्थिर पूर्णांक प्रणाली_bus_cs1_muxvals[] = अणु0पूर्ण;
अटल स्थिर अचिन्हित uart0_pins[] = अणु54, 55पूर्ण;
अटल स्थिर पूर्णांक uart0_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित uart1_pins[] = अणु58, 59पूर्ण;
अटल स्थिर पूर्णांक uart1_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित uart2_pins[] = अणु90, 91पूर्ण;
अटल स्थिर पूर्णांक uart2_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित uart3_pins[] = अणु94, 95पूर्ण;
अटल स्थिर पूर्णांक uart3_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित uart3_ctsrts_pins[] = अणु96, 98पूर्ण;
अटल स्थिर पूर्णांक uart3_ctsrts_muxvals[] = अणु1, 1पूर्ण;
अटल स्थिर अचिन्हित uart3_modem_pins[] = अणु97, 99, 100, 101पूर्ण;
अटल स्थिर पूर्णांक uart3_modem_muxvals[] = अणु1, 1, 1, 1पूर्ण;
अटल स्थिर अचिन्हित usb0_pins[] = अणु46, 47पूर्ण;
अटल स्थिर पूर्णांक usb0_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित usb1_pins[] = अणु48, 49पूर्ण;
अटल स्थिर पूर्णांक usb1_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित usb2_pins[] = अणु50, 51पूर्ण;
अटल स्थिर पूर्णांक usb2_muxvals[] = अणु0, 0पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range0_pins[] = अणु
	159, 160, 161, 162, 163, 164, 165, 166,		/* PORT0x */
	0, 1, 2, 3, 4, 5, 6, 7,				/* PORT1x */
	8, 9, 10, 11, 12, 13, 14, 15,			/* PORT2x */
	16, 17, 18,					/* PORT30-32 */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range1_pins[] = अणु
	46, 47, 48, 49, 50,				/* PORT53-57 */
	51,						/* PORT60 */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range2_pins[] = अणु
	54, 55, 56, 57, 58,				/* PORT63-67 */
	59, 60, 69, 70, 71, 72, 73, 74,			/* PORT7x */
	75, 76, 77, 78, 79, 80, 81, 82,			/* PORT8x */
	83, 84, 85, 86, 87, 88, 89, 90,			/* PORT9x */
	91, 92, 93, 94, 95, 96, 97, 98,			/* PORT10x */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range3_pins[] = अणु
	99, 100, 101, 102, 103, 104, 105, 106,		/* PORT12x */
	107, 108, 109, 110, 111, 112, 113, 114,		/* PORT13x */
	115, 116, 117, 118, 119, 120, 121, 122,		/* PORT14x */
	149, 150, 151, 152, 153, 154, 155, 156,		/* XIRQ0-7 */
	157, 143, 144, 145, 85, 146, 158, 84,		/* XIRQ8-15 */
	141, 142, 148, 50, 51, 159, 160, 161,		/* XIRQ16-23 */
	61, 62, 63, 64, 65, 66, 67, 68,			/* PORT18x */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range4_pins[] = अणु
	123, 124, 125, 126, 127, 128, 129, 130,		/* PORT20x */
	131, 132, 133, 134, 135, 136, 137, 138,		/* PORT21x */
	139, 140, 141, 142,				/* PORT220-223 */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_range5_pins[] = अणु
	147, 148, 149, 150, 151, 152, 153, 154,		/* PORT23x */
	155, 156, 157, 143, 144, 145, 146, 158,		/* PORT24x */
पूर्ण;

अटल स्थिर काष्ठा uniphier_pinctrl_group uniphier_ld11_groups[] = अणु
	UNIPHIER_PINCTRL_GROUP(aout1),
	UNIPHIER_PINCTRL_GROUP(aoutiec1),
	UNIPHIER_PINCTRL_GROUP(emmc),
	UNIPHIER_PINCTRL_GROUP(emmc_dat8),
	UNIPHIER_PINCTRL_GROUP(ether_rmii),
	UNIPHIER_PINCTRL_GROUP(hscin0_ci),
	UNIPHIER_PINCTRL_GROUP(hscin0_p),
	UNIPHIER_PINCTRL_GROUP(hscin0_s),
	UNIPHIER_PINCTRL_GROUP(hscin1_p),
	UNIPHIER_PINCTRL_GROUP(hscin1_s),
	UNIPHIER_PINCTRL_GROUP(hscin2_s),
	UNIPHIER_PINCTRL_GROUP(hscout0_ci),
	UNIPHIER_PINCTRL_GROUP(hscout0_p),
	UNIPHIER_PINCTRL_GROUP(hscout0_s),
	UNIPHIER_PINCTRL_GROUP(hscout1_s),
	UNIPHIER_PINCTRL_GROUP(i2c0),
	UNIPHIER_PINCTRL_GROUP(i2c1),
	UNIPHIER_PINCTRL_GROUP(i2c3),
	UNIPHIER_PINCTRL_GROUP(i2c4),
	UNIPHIER_PINCTRL_GROUP(nand),
	UNIPHIER_PINCTRL_GROUP(spi0),
	UNIPHIER_PINCTRL_GROUP(spi1),
	UNIPHIER_PINCTRL_GROUP(प्रणाली_bus),
	UNIPHIER_PINCTRL_GROUP(प्रणाली_bus_cs1),
	UNIPHIER_PINCTRL_GROUP(uart0),
	UNIPHIER_PINCTRL_GROUP(uart1),
	UNIPHIER_PINCTRL_GROUP(uart2),
	UNIPHIER_PINCTRL_GROUP(uart3),
	UNIPHIER_PINCTRL_GROUP(uart3_ctsrts),
	UNIPHIER_PINCTRL_GROUP(uart3_modem),
	UNIPHIER_PINCTRL_GROUP(usb0),
	UNIPHIER_PINCTRL_GROUP(usb1),
	UNIPHIER_PINCTRL_GROUP(usb2),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range0),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range1),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range2),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range3),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range4),
	UNIPHIER_PINCTRL_GROUP_GPIO(gpio_range5),
पूर्ण;

अटल स्थिर अक्षर * स्थिर aout1_groups[] = अणु"aout1"पूर्ण;
अटल स्थिर अक्षर * स्थिर aoutiec1_groups[] = अणु"aoutiec1"पूर्ण;
अटल स्थिर अक्षर * स्थिर emmc_groups[] = अणु"emmc", "emmc_dat8"पूर्ण;
अटल स्थिर अक्षर * स्थिर ether_rmii_groups[] = अणु"ether_rmii"पूर्ण;
अटल स्थिर अक्षर * स्थिर hscin0_groups[] = अणु"hscin0_ci",
					     "hscin0_p",
					     "hscin0_s"पूर्ण;
अटल स्थिर अक्षर * स्थिर hscin1_groups[] = अणु"hscin1_p", "hscin1_s"पूर्ण;
अटल स्थिर अक्षर * स्थिर hscin2_groups[] = अणु"hscin2_s"पूर्ण;
अटल स्थिर अक्षर * स्थिर hscout0_groups[] = अणु"hscout0_ci",
					      "hscout0_p",
					      "hscout0_s"पूर्ण;
अटल स्थिर अक्षर * स्थिर hscout1_groups[] = अणु"hscout1_s"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु"i2c0"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c1_groups[] = अणु"i2c1"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c3_groups[] = अणु"i2c3"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c4_groups[] = अणु"i2c4"पूर्ण;
अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु"nand"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0_groups[] = अणु"spi0"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi1_groups[] = अणु"spi1"पूर्ण;
अटल स्थिर अक्षर * स्थिर प्रणाली_bus_groups[] = अणु"system_bus",
						 "system_bus_cs1"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart0_groups[] = अणु"uart0"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु"uart1"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2_groups[] = अणु"uart2"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart3_groups[] = अणु"uart3", "uart3_ctsrts",
					    "uart3_modem"पूर्ण;
अटल स्थिर अक्षर * स्थिर usb0_groups[] = अणु"usb0"पूर्ण;
अटल स्थिर अक्षर * स्थिर usb1_groups[] = अणु"usb1"पूर्ण;
अटल स्थिर अक्षर * स्थिर usb2_groups[] = अणु"usb2"पूर्ण;

अटल स्थिर काष्ठा uniphier_pinmux_function uniphier_ld11_functions[] = अणु
	UNIPHIER_PINMUX_FUNCTION(aout1),
	UNIPHIER_PINMUX_FUNCTION(aoutiec1),
	UNIPHIER_PINMUX_FUNCTION(emmc),
	UNIPHIER_PINMUX_FUNCTION(ether_rmii),
	UNIPHIER_PINMUX_FUNCTION(hscin0),
	UNIPHIER_PINMUX_FUNCTION(hscin1),
	UNIPHIER_PINMUX_FUNCTION(hscin2),
	UNIPHIER_PINMUX_FUNCTION(hscout0),
	UNIPHIER_PINMUX_FUNCTION(hscout1),
	UNIPHIER_PINMUX_FUNCTION(i2c0),
	UNIPHIER_PINMUX_FUNCTION(i2c1),
	UNIPHIER_PINMUX_FUNCTION(i2c3),
	UNIPHIER_PINMUX_FUNCTION(i2c4),
	UNIPHIER_PINMUX_FUNCTION(nand),
	UNIPHIER_PINMUX_FUNCTION(spi0),
	UNIPHIER_PINMUX_FUNCTION(spi1),
	UNIPHIER_PINMUX_FUNCTION(प्रणाली_bus),
	UNIPHIER_PINMUX_FUNCTION(uart0),
	UNIPHIER_PINMUX_FUNCTION(uart1),
	UNIPHIER_PINMUX_FUNCTION(uart2),
	UNIPHIER_PINMUX_FUNCTION(uart3),
	UNIPHIER_PINMUX_FUNCTION(usb0),
	UNIPHIER_PINMUX_FUNCTION(usb1),
	UNIPHIER_PINMUX_FUNCTION(usb2),
पूर्ण;

अटल पूर्णांक uniphier_ld11_get_gpio_muxval(अचिन्हित पूर्णांक pin,
					 अचिन्हित पूर्णांक gpio_offset)
अणु
	अगर (gpio_offset == 132 || gpio_offset == 135)	/* XIRQ12, 15 */
		वापस 13;

	अगर (gpio_offset >= 120 && gpio_offset <= 143)	/* XIRQx */
		वापस 14;

	वापस 15;
पूर्ण

अटल स्थिर काष्ठा uniphier_pinctrl_socdata uniphier_ld11_pindata = अणु
	.pins = uniphier_ld11_pins,
	.npins = ARRAY_SIZE(uniphier_ld11_pins),
	.groups = uniphier_ld11_groups,
	.groups_count = ARRAY_SIZE(uniphier_ld11_groups),
	.functions = uniphier_ld11_functions,
	.functions_count = ARRAY_SIZE(uniphier_ld11_functions),
	.get_gpio_muxval = uniphier_ld11_get_gpio_muxval,
	.caps = UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL,
पूर्ण;

अटल पूर्णांक uniphier_ld11_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस uniphier_pinctrl_probe(pdev, &uniphier_ld11_pindata);
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_ld11_pinctrl_match[] = अणु
	अणु .compatible = "socionext,uniphier-ld11-pinctrl" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_ld11_pinctrl_driver = अणु
	.probe = uniphier_ld11_pinctrl_probe,
	.driver = अणु
		.name = "uniphier-ld11-pinctrl",
		.of_match_table = uniphier_ld11_pinctrl_match,
		.pm = &uniphier_pinctrl_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(uniphier_ld11_pinctrl_driver);
