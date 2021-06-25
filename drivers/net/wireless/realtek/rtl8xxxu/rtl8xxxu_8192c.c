<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTL8XXXU mac80211 USB driver - 8188c/8188r/8192c specअगरic subdriver
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

#अगर_घोषित CONFIG_RTL8XXXU_UNTESTED
अटल काष्ठा rtl8xxxu_घातer_base rtl8192c_घातer_base = अणु
	.reg_0e00 = 0x07090c0c,
	.reg_0e04 = 0x01020405,
	.reg_0e08 = 0x00000000,
	.reg_086c = 0x00000000,

	.reg_0e10 = 0x0b0c0c0e,
	.reg_0e14 = 0x01030506,
	.reg_0e18 = 0x0b0c0d0e,
	.reg_0e1c = 0x01030509,

	.reg_0830 = 0x07090c0c,
	.reg_0834 = 0x01020405,
	.reg_0838 = 0x00000000,
	.reg_086c_2 = 0x00000000,

	.reg_083c = 0x0b0c0d0e,
	.reg_0848 = 0x01030509,
	.reg_084c = 0x0b0c0d0e,
	.reg_0868 = 0x01030509,
पूर्ण;

अटल काष्ठा rtl8xxxu_घातer_base rtl8188r_घातer_base = अणु
	.reg_0e00 = 0x06080808,
	.reg_0e04 = 0x00040406,
	.reg_0e08 = 0x00000000,
	.reg_086c = 0x00000000,

	.reg_0e10 = 0x04060608,
	.reg_0e14 = 0x00020204,
	.reg_0e18 = 0x04060608,
	.reg_0e1c = 0x00020204,

	.reg_0830 = 0x06080808,
	.reg_0834 = 0x00040406,
	.reg_0838 = 0x00000000,
	.reg_086c_2 = 0x00000000,

	.reg_083c = 0x04060608,
	.reg_0848 = 0x00020204,
	.reg_084c = 0x04060608,
	.reg_0868 = 0x00020204,
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8192cu_radioa_2t_init_table[] = अणु
	अणु0x00, 0x00030159पूर्ण, अणु0x01, 0x00031284पूर्ण,
	अणु0x02, 0x00098000पूर्ण, अणु0x03, 0x00018c63पूर्ण,
	अणु0x04, 0x000210e7पूर्ण, अणु0x09, 0x0002044fपूर्ण,
	अणु0x0a, 0x0001adb1पूर्ण, अणु0x0b, 0x00054867पूर्ण,
	अणु0x0c, 0x0008992eपूर्ण, अणु0x0d, 0x0000e52cपूर्ण,
	अणु0x0e, 0x00039ce7पूर्ण, अणु0x0f, 0x00000451पूर्ण,
	अणु0x19, 0x00000000पूर्ण, अणु0x1a, 0x00010255पूर्ण,
	अणु0x1b, 0x00060a00पूर्ण, अणु0x1c, 0x000fc378पूर्ण,
	अणु0x1d, 0x000a1250पूर्ण, अणु0x1e, 0x0004445fपूर्ण,
	अणु0x1f, 0x00080001पूर्ण, अणु0x20, 0x0000b614पूर्ण,
	अणु0x21, 0x0006c000पूर्ण, अणु0x22, 0x00000000पूर्ण,
	अणु0x23, 0x00001558पूर्ण, अणु0x24, 0x00000060पूर्ण,
	अणु0x25, 0x00000483पूर्ण, अणु0x26, 0x0004f000पूर्ण,
	अणु0x27, 0x000ec7d9पूर्ण, अणु0x28, 0x000577c0पूर्ण,
	अणु0x29, 0x00004783पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00021334पूर्ण, अणु0x2a, 0x00000000पूर्ण,
	अणु0x2b, 0x00000054पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000cपूर्ण, अणु0x2a, 0x00000002पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000003पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000004पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000005पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000006पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000007पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000008पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0004b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000009पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000aपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000bपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000cपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000dपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000eपूर्ण,
	अणु0x2b, 0x0000050bपूर्ण, अणु0x2b, 0x00066666पूर्ण,
	अणु0x2c, 0x0000001aपूर्ण, अणु0x2a, 0x000e0000पूर्ण,
	अणु0x10, 0x0004000fपूर्ण, अणु0x11, 0x000e31fcपूर्ण,
	अणु0x10, 0x0006000fपूर्ण, अणु0x11, 0x000ff9f8पूर्ण,
	अणु0x10, 0x0002000fपूर्ण, अणु0x11, 0x000203f9पूर्ण,
	अणु0x10, 0x0003000fपूर्ण, अणु0x11, 0x000ff500पूर्ण,
	अणु0x10, 0x00000000पूर्ण, अणु0x11, 0x00000000पूर्ण,
	अणु0x10, 0x0008000fपूर्ण, अणु0x11, 0x0003f100पूर्ण,
	अणु0x10, 0x0009000fपूर्ण, अणु0x11, 0x00023100पूर्ण,
	अणु0x12, 0x00032000पूर्ण, अणु0x12, 0x00071000पूर्ण,
	अणु0x12, 0x000b0000पूर्ण, अणु0x12, 0x000fc000पूर्ण,
	अणु0x13, 0x000287b3पूर्ण, अणु0x13, 0x000244b7पूर्ण,
	अणु0x13, 0x000204abपूर्ण, अणु0x13, 0x0001c49fपूर्ण,
	अणु0x13, 0x00018493पूर्ण, अणु0x13, 0x0001429bपूर्ण,
	अणु0x13, 0x00010299पूर्ण, अणु0x13, 0x0000c29cपूर्ण,
	अणु0x13, 0x000081a0पूर्ण, अणु0x13, 0x000040acपूर्ण,
	अणु0x13, 0x00000020पूर्ण, अणु0x14, 0x0001944cपूर्ण,
	अणु0x14, 0x00059444पूर्ण, अणु0x14, 0x0009944cपूर्ण,
	अणु0x14, 0x000d9444पूर्ण, अणु0x15, 0x0000f424पूर्ण,
	अणु0x15, 0x0004f424पूर्ण, अणु0x15, 0x0008f424पूर्ण,
	अणु0x15, 0x000cf424पूर्ण, अणु0x16, 0x000e0330पूर्ण,
	अणु0x16, 0x000a0330पूर्ण, अणु0x16, 0x00060330पूर्ण,
	अणु0x16, 0x00020330पूर्ण, अणु0x00, 0x00010159पूर्ण,
	अणु0x18, 0x0000f401पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x1f, 0x00080003पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0x1e, 0x00044457पूर्ण, अणु0x1f, 0x00080000पूर्ण,
	अणु0x00, 0x00030159पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8192cu_radiob_2t_init_table[] = अणु
	अणु0x00, 0x00030159पूर्ण, अणु0x01, 0x00031284पूर्ण,
	अणु0x02, 0x00098000पूर्ण, अणु0x03, 0x00018c63पूर्ण,
	अणु0x04, 0x000210e7पूर्ण, अणु0x09, 0x0002044fपूर्ण,
	अणु0x0a, 0x0001adb1पूर्ण, अणु0x0b, 0x00054867पूर्ण,
	अणु0x0c, 0x0008992eपूर्ण, अणु0x0d, 0x0000e52cपूर्ण,
	अणु0x0e, 0x00039ce7पूर्ण, अणु0x0f, 0x00000451पूर्ण,
	अणु0x12, 0x00032000पूर्ण, अणु0x12, 0x00071000पूर्ण,
	अणु0x12, 0x000b0000पूर्ण, अणु0x12, 0x000fc000पूर्ण,
	अणु0x13, 0x000287afपूर्ण, अणु0x13, 0x000244b7पूर्ण,
	अणु0x13, 0x000204abपूर्ण, अणु0x13, 0x0001c49fपूर्ण,
	अणु0x13, 0x00018493पूर्ण, अणु0x13, 0x00014297पूर्ण,
	अणु0x13, 0x00010295पूर्ण, अणु0x13, 0x0000c298पूर्ण,
	अणु0x13, 0x0000819cपूर्ण, अणु0x13, 0x000040a8पूर्ण,
	अणु0x13, 0x0000001cपूर्ण, अणु0x14, 0x0001944cपूर्ण,
	अणु0x14, 0x00059444पूर्ण, अणु0x14, 0x0009944cपूर्ण,
	अणु0x14, 0x000d9444पूर्ण, अणु0x15, 0x0000f424पूर्ण,
	अणु0x15, 0x0004f424पूर्ण, अणु0x15, 0x0008f424पूर्ण,
	अणु0x15, 0x000cf424पूर्ण, अणु0x16, 0x000e0330पूर्ण,
	अणु0x16, 0x000a0330पूर्ण, अणु0x16, 0x00060330पूर्ण,
	अणु0x16, 0x00020330पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8192cu_radioa_1t_init_table[] = अणु
	अणु0x00, 0x00030159पूर्ण, अणु0x01, 0x00031284पूर्ण,
	अणु0x02, 0x00098000पूर्ण, अणु0x03, 0x00018c63पूर्ण,
	अणु0x04, 0x000210e7पूर्ण, अणु0x09, 0x0002044fपूर्ण,
	अणु0x0a, 0x0001adb1पूर्ण, अणु0x0b, 0x00054867पूर्ण,
	अणु0x0c, 0x0008992eपूर्ण, अणु0x0d, 0x0000e52cपूर्ण,
	अणु0x0e, 0x00039ce7पूर्ण, अणु0x0f, 0x00000451पूर्ण,
	अणु0x19, 0x00000000पूर्ण, अणु0x1a, 0x00010255पूर्ण,
	अणु0x1b, 0x00060a00पूर्ण, अणु0x1c, 0x000fc378पूर्ण,
	अणु0x1d, 0x000a1250पूर्ण, अणु0x1e, 0x0004445fपूर्ण,
	अणु0x1f, 0x00080001पूर्ण, अणु0x20, 0x0000b614पूर्ण,
	अणु0x21, 0x0006c000पूर्ण, अणु0x22, 0x00000000पूर्ण,
	अणु0x23, 0x00001558पूर्ण, अणु0x24, 0x00000060पूर्ण,
	अणु0x25, 0x00000483पूर्ण, अणु0x26, 0x0004f000पूर्ण,
	अणु0x27, 0x000ec7d9पूर्ण, अणु0x28, 0x000577c0पूर्ण,
	अणु0x29, 0x00004783पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00021334पूर्ण, अणु0x2a, 0x00000000पूर्ण,
	अणु0x2b, 0x00000054पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000cपूर्ण, अणु0x2a, 0x00000002पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000003पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000004पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000005पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000006पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000007पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000008पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0004b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000009पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000aपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000bपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000cपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000dपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000eपूर्ण,
	अणु0x2b, 0x0000050bपूर्ण, अणु0x2b, 0x00066666पूर्ण,
	अणु0x2c, 0x0000001aपूर्ण, अणु0x2a, 0x000e0000पूर्ण,
	अणु0x10, 0x0004000fपूर्ण, अणु0x11, 0x000e31fcपूर्ण,
	अणु0x10, 0x0006000fपूर्ण, अणु0x11, 0x000ff9f8पूर्ण,
	अणु0x10, 0x0002000fपूर्ण, अणु0x11, 0x000203f9पूर्ण,
	अणु0x10, 0x0003000fपूर्ण, अणु0x11, 0x000ff500पूर्ण,
	अणु0x10, 0x00000000पूर्ण, अणु0x11, 0x00000000पूर्ण,
	अणु0x10, 0x0008000fपूर्ण, अणु0x11, 0x0003f100पूर्ण,
	अणु0x10, 0x0009000fपूर्ण, अणु0x11, 0x00023100पूर्ण,
	अणु0x12, 0x00032000पूर्ण, अणु0x12, 0x00071000पूर्ण,
	अणु0x12, 0x000b0000पूर्ण, अणु0x12, 0x000fc000पूर्ण,
	अणु0x13, 0x000287b3पूर्ण, अणु0x13, 0x000244b7पूर्ण,
	अणु0x13, 0x000204abपूर्ण, अणु0x13, 0x0001c49fपूर्ण,
	अणु0x13, 0x00018493पूर्ण, अणु0x13, 0x0001429bपूर्ण,
	अणु0x13, 0x00010299पूर्ण, अणु0x13, 0x0000c29cपूर्ण,
	अणु0x13, 0x000081a0पूर्ण, अणु0x13, 0x000040acपूर्ण,
	अणु0x13, 0x00000020पूर्ण, अणु0x14, 0x0001944cपूर्ण,
	अणु0x14, 0x00059444पूर्ण, अणु0x14, 0x0009944cपूर्ण,
	अणु0x14, 0x000d9444पूर्ण, अणु0x15, 0x0000f405पूर्ण,
	अणु0x15, 0x0004f405पूर्ण, अणु0x15, 0x0008f405पूर्ण,
	अणु0x15, 0x000cf405पूर्ण, अणु0x16, 0x000e0330पूर्ण,
	अणु0x16, 0x000a0330पूर्ण, अणु0x16, 0x00060330पूर्ण,
	अणु0x16, 0x00020330पूर्ण, अणु0x00, 0x00010159पूर्ण,
	अणु0x18, 0x0000f401पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x1f, 0x00080003पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0x1e, 0x00044457पूर्ण, अणु0x1f, 0x00080000पूर्ण,
	अणु0x00, 0x00030159पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8188ru_radioa_1t_highpa_table[] = अणु
	अणु0x00, 0x00030159पूर्ण, अणु0x01, 0x00031284पूर्ण,
	अणु0x02, 0x00098000पूर्ण, अणु0x03, 0x00018c63पूर्ण,
	अणु0x04, 0x000210e7पूर्ण, अणु0x09, 0x0002044fपूर्ण,
	अणु0x0a, 0x0001adb0पूर्ण, अणु0x0b, 0x00054867पूर्ण,
	अणु0x0c, 0x0008992eपूर्ण, अणु0x0d, 0x0000e529पूर्ण,
	अणु0x0e, 0x00039ce7पूर्ण, अणु0x0f, 0x00000451पूर्ण,
	अणु0x19, 0x00000000पूर्ण, अणु0x1a, 0x00000255पूर्ण,
	अणु0x1b, 0x00060a00पूर्ण, अणु0x1c, 0x000fc378पूर्ण,
	अणु0x1d, 0x000a1250पूर्ण, अणु0x1e, 0x0004445fपूर्ण,
	अणु0x1f, 0x00080001पूर्ण, अणु0x20, 0x0000b614पूर्ण,
	अणु0x21, 0x0006c000पूर्ण, अणु0x22, 0x0000083cपूर्ण,
	अणु0x23, 0x00001558पूर्ण, अणु0x24, 0x00000060पूर्ण,
	अणु0x25, 0x00000483पूर्ण, अणु0x26, 0x0004f000पूर्ण,
	अणु0x27, 0x000ec7d9पूर्ण, अणु0x28, 0x000977c0पूर्ण,
	अणु0x29, 0x00004783पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00021334पूर्ण, अणु0x2a, 0x00000000पूर्ण,
	अणु0x2b, 0x00000054पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000cपूर्ण, अणु0x2a, 0x00000002पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000003पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000004पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000005पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000006पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000007पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000008पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0004b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000009पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000aपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000bपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000cपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000dपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000eपूर्ण,
	अणु0x2b, 0x0000050bपूर्ण, अणु0x2b, 0x00066666पूर्ण,
	अणु0x2c, 0x0000001aपूर्ण, अणु0x2a, 0x000e0000पूर्ण,
	अणु0x10, 0x0004000fपूर्ण, अणु0x11, 0x000e31fcपूर्ण,
	अणु0x10, 0x0006000fपूर्ण, अणु0x11, 0x000ff9f8पूर्ण,
	अणु0x10, 0x0002000fपूर्ण, अणु0x11, 0x000203f9पूर्ण,
	अणु0x10, 0x0003000fपूर्ण, अणु0x11, 0x000ff500पूर्ण,
	अणु0x10, 0x00000000पूर्ण, अणु0x11, 0x00000000पूर्ण,
	अणु0x10, 0x0008000fपूर्ण, अणु0x11, 0x0003f100पूर्ण,
	अणु0x10, 0x0009000fपूर्ण, अणु0x11, 0x00023100पूर्ण,
	अणु0x12, 0x000d8000पूर्ण, अणु0x12, 0x00090000पूर्ण,
	अणु0x12, 0x00051000पूर्ण, अणु0x12, 0x00012000पूर्ण,
	अणु0x13, 0x00028fb4पूर्ण, अणु0x13, 0x00024fa8पूर्ण,
	अणु0x13, 0x000207a4पूर्ण, अणु0x13, 0x0001c3b0पूर्ण,
	अणु0x13, 0x000183a4पूर्ण, अणु0x13, 0x00014398पूर्ण,
	अणु0x13, 0x000101a4पूर्ण, अणु0x13, 0x0000c198पूर्ण,
	अणु0x13, 0x000080a4पूर्ण, अणु0x13, 0x00004098पूर्ण,
	अणु0x13, 0x00000000पूर्ण, अणु0x14, 0x0001944cपूर्ण,
	अणु0x14, 0x00059444पूर्ण, अणु0x14, 0x0009944cपूर्ण,
	अणु0x14, 0x000d9444पूर्ण, अणु0x15, 0x0000f405पूर्ण,
	अणु0x15, 0x0004f405पूर्ण, अणु0x15, 0x0008f405पूर्ण,
	अणु0x15, 0x000cf405पूर्ण, अणु0x16, 0x000e0330पूर्ण,
	अणु0x16, 0x000a0330पूर्ण, अणु0x16, 0x00060330पूर्ण,
	अणु0x16, 0x00020330पूर्ण, अणु0x00, 0x00010159पूर्ण,
	अणु0x18, 0x0000f401पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x1f, 0x00080003पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0x1e, 0x00044457पूर्ण, अणु0x1f, 0x00080000पूर्ण,
	अणु0x00, 0x00030159पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल पूर्णांक rtl8192cu_load_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	अक्षर *fw_name;
	पूर्णांक ret;

	अगर (!priv->venकरोr_umc)
		fw_name = "rtlwifi/rtl8192cufw_TMSC.bin";
	अन्यथा अगर (priv->chip_cut || priv->rtl_chip == RTL8192C)
		fw_name = "rtlwifi/rtl8192cufw_B.bin";
	अन्यथा
		fw_name = "rtlwifi/rtl8192cufw_A.bin";

	ret = rtl8xxxu_load_firmware(priv, fw_name);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8192cu_parse_efuse(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8192cu_efuse *efuse = &priv->efuse_wअगरi.efuse8192;
	पूर्णांक i;

	अगर (efuse->rtl_id != cpu_to_le16(0x8129))
		वापस -EINVAL;

	ether_addr_copy(priv->mac_addr, efuse->mac_addr);

	स_नकल(priv->cck_tx_घातer_index_A,
	       efuse->cck_tx_घातer_index_A,
	       माप(efuse->cck_tx_घातer_index_A));
	स_नकल(priv->cck_tx_घातer_index_B,
	       efuse->cck_tx_घातer_index_B,
	       माप(efuse->cck_tx_घातer_index_B));

	स_नकल(priv->ht40_1s_tx_घातer_index_A,
	       efuse->ht40_1s_tx_घातer_index_A,
	       माप(efuse->ht40_1s_tx_घातer_index_A));
	स_नकल(priv->ht40_1s_tx_घातer_index_B,
	       efuse->ht40_1s_tx_घातer_index_B,
	       माप(efuse->ht40_1s_tx_घातer_index_B));
	स_नकल(priv->ht40_2s_tx_घातer_index_dअगरf,
	       efuse->ht40_2s_tx_घातer_index_dअगरf,
	       माप(efuse->ht40_2s_tx_घातer_index_dअगरf));

	स_नकल(priv->ht20_tx_घातer_index_dअगरf,
	       efuse->ht20_tx_घातer_index_dअगरf,
	       माप(efuse->ht20_tx_घातer_index_dअगरf));
	स_नकल(priv->ofdm_tx_घातer_index_dअगरf,
	       efuse->ofdm_tx_घातer_index_dअगरf,
	       माप(efuse->ofdm_tx_घातer_index_dअगरf));

	स_नकल(priv->ht40_max_घातer_offset,
	       efuse->ht40_max_घातer_offset,
	       माप(efuse->ht40_max_घातer_offset));
	स_नकल(priv->ht20_max_घातer_offset,
	       efuse->ht20_max_घातer_offset,
	       माप(efuse->ht20_max_घातer_offset));

	dev_info(&priv->udev->dev, "Vendor: %.7s\n",
		 efuse->venकरोr_name);
	dev_info(&priv->udev->dev, "Product: %.20s\n",
		 efuse->device_name);

	priv->घातer_base = &rtl8192c_घातer_base;

	अगर (efuse->rf_regulatory & 0x20) अणु
		प्र_लिखो(priv->chip_name, "8188RU");
		priv->rtl_chip = RTL8188R;
		priv->hi_pa = 1;
		priv->no_pape = 1;
		priv->घातer_base = &rtl8188r_घातer_base;
	पूर्ण

	अगर (rtl8xxxu_debug & RTL8XXXU_DEBUG_EFUSE) अणु
		अचिन्हित अक्षर *raw = priv->efuse_wअगरi.raw;

		dev_info(&priv->udev->dev,
			 "%s: dumping efuse (0x%02zx bytes):\n",
			 __func__, माप(काष्ठा rtl8192cu_efuse));
		क्रम (i = 0; i < माप(काष्ठा rtl8192cu_efuse); i += 8)
			dev_info(&priv->udev->dev, "%02x: %8ph\n", i, &raw[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8192cu_init_phy_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8xxxu_rfregval *rftable;
	पूर्णांक ret;

	अगर (priv->rtl_chip == RTL8188R) अणु
		rftable = rtl8188ru_radioa_1t_highpa_table;
		ret = rtl8xxxu_init_phy_rf(priv, rftable, RF_A);
	पूर्ण अन्यथा अगर (priv->rf_paths == 1) अणु
		rftable = rtl8192cu_radioa_1t_init_table;
		ret = rtl8xxxu_init_phy_rf(priv, rftable, RF_A);
	पूर्ण अन्यथा अणु
		rftable = rtl8192cu_radioa_2t_init_table;
		ret = rtl8xxxu_init_phy_rf(priv, rftable, RF_A);
		अगर (ret)
			जाओ निकास;
		rftable = rtl8192cu_radiob_2t_init_table;
		ret = rtl8xxxu_init_phy_rf(priv, rftable, RF_B);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8192cu_घातer_on(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक i;

	क्रम (i = 100; i; i--) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO);
		अगर (val8 & APS_FSMCO_PFM_ALDN)
			अवरोध;
	पूर्ण

	अगर (!i) अणु
		pr_info("%s: Poll failed\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/*
	 * RSV_CTRL 0x001C[7:0] = 0x00, unlock ISO/CLK/Power control रेजिस्टर
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, 0x0);
	rtl8xxxu_ग_लिखो8(priv, REG_SPS0_CTRL, 0x2b);
	udelay(100);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_LDOV12D_CTRL);
	अगर (!(val8 & LDOV12D_ENABLE)) अणु
		pr_info("%s: Enabling LDOV12D (%02x)\n", __func__, val8);
		val8 |= LDOV12D_ENABLE;
		rtl8xxxu_ग_लिखो8(priv, REG_LDOV12D_CTRL, val8);

		udelay(100);

		val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_ISO_CTRL);
		val8 &= ~SYS_ISO_MD2PP;
		rtl8xxxu_ग_लिखो8(priv, REG_SYS_ISO_CTRL, val8);
	पूर्ण

	/*
	 * Auto enable WLAN
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_APS_FSMCO);
	val16 |= APS_FSMCO_MAC_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_APS_FSMCO, val16);

	क्रम (i = 1000; i; i--) अणु
		val16 = rtl8xxxu_पढ़ो16(priv, REG_APS_FSMCO);
		अगर (!(val16 & APS_FSMCO_MAC_ENABLE))
			अवरोध;
	पूर्ण
	अगर (!i) अणु
		pr_info("%s: FSMCO_MAC_ENABLE poll failed\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Enable radio, GPIO, LED
	 */
	val16 = APS_FSMCO_HW_SUSPEND | APS_FSMCO_ENABLE_POWERDOWN |
		APS_FSMCO_PFM_ALDN;
	rtl8xxxu_ग_लिखो16(priv, REG_APS_FSMCO, val16);

	/*
	 * Release RF digital isolation
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_SYS_ISO_CTRL);
	val16 &= ~SYS_ISO_DIOR;
	rtl8xxxu_ग_लिखो16(priv, REG_SYS_ISO_CTRL, val16);

	val8 = rtl8xxxu_पढ़ो8(priv, REG_APSD_CTRL);
	val8 &= ~APSD_CTRL_OFF;
	rtl8xxxu_ग_लिखो8(priv, REG_APSD_CTRL, val8);
	क्रम (i = 200; i; i--) अणु
		val8 = rtl8xxxu_पढ़ो8(priv, REG_APSD_CTRL);
		अगर (!(val8 & APSD_CTRL_OFF_STATUS))
			अवरोध;
	पूर्ण

	अगर (!i) अणु
		pr_info("%s: APSD_CTRL poll failed\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Enable MAC DMA/WMAC/SCHEDULE/SEC block
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 |= CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE |
		CR_TXDMA_ENABLE | CR_RXDMA_ENABLE | CR_PROTOCOL_ENABLE |
		CR_SCHEDULE_ENABLE | CR_MAC_TX_ENABLE | CR_MAC_RX_ENABLE;
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	rtl8xxxu_ग_लिखो8(priv, 0xfe10, 0x19);

	/*
	 * Workaround क्रम 8188RU LNA घातer leakage problem.
	 */
	अगर (priv->rtl_chip == RTL8188R) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_FPGA0_XCD_RF_PARM);
		val32 &= ~BIT(1);
		rtl8xxxu_ग_लिखो32(priv, REG_FPGA0_XCD_RF_PARM, val32);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा rtl8xxxu_fileops rtl8192cu_fops = अणु
	.parse_efuse = rtl8192cu_parse_efuse,
	.load_firmware = rtl8192cu_load_firmware,
	.घातer_on = rtl8192cu_घातer_on,
	.घातer_off = rtl8xxxu_घातer_off,
	.reset_8051 = rtl8xxxu_reset_8051,
	.llt_init = rtl8xxxu_init_llt_table,
	.init_phy_bb = rtl8xxxu_gen1_init_phy_bb,
	.init_phy_rf = rtl8192cu_init_phy_rf,
	.phy_iq_calibrate = rtl8xxxu_gen1_phy_iq_calibrate,
	.config_channel = rtl8xxxu_gen1_config_channel,
	.parse_rx_desc = rtl8xxxu_parse_rxdesc16,
	.init_aggregation = rtl8xxxu_gen1_init_aggregation,
	.enable_rf = rtl8xxxu_gen1_enable_rf,
	.disable_rf = rtl8xxxu_gen1_disable_rf,
	.usb_quirks = rtl8xxxu_gen1_usb_quirks,
	.set_tx_घातer = rtl8xxxu_gen1_set_tx_घातer,
	.update_rate_mask = rtl8xxxu_update_rate_mask,
	.report_connect = rtl8xxxu_gen1_report_connect,
	.fill_txdesc = rtl8xxxu_fill_txdesc_v1,
	.ग_लिखोN_block_size = 128,
	.rx_agg_buf_size = 16000,
	.tx_desc_size = माप(काष्ठा rtl8xxxu_txdesc32),
	.rx_desc_size = माप(काष्ठा rtl8xxxu_rxdesc16),
	.adda_1t_init = 0x0b1b25a0,
	.adda_1t_path_on = 0x0bdb25a0,
	.adda_2t_path_on_a = 0x04db25a4,
	.adda_2t_path_on_b = 0x0b1b25a4,
	.trxff_boundary = 0x27ff,
	.pbp_rx = PBP_PAGE_SIZE_128,
	.pbp_tx = PBP_PAGE_SIZE_128,
	.mactable = rtl8xxxu_gen1_mac_init_table,
	.total_page_num = TX_TOTAL_PAGE_NUM,
	.page_num_hi = TX_PAGE_NUM_HI_PQ,
	.page_num_lo = TX_PAGE_NUM_LO_PQ,
	.page_num_norm = TX_PAGE_NUM_NORM_PQ,
पूर्ण;
#पूर्ण_अगर
