<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Purna Chandra Mandal, purna.mandal@microchip.com
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach-pic32/pic32.h>

#समावेश "pic32mzda.h"

#घोषणा PIC32_CFGCON	0x0000
#घोषणा PIC32_DEVID	0x0020
#घोषणा PIC32_SYSKEY	0x0030
#घोषणा PIC32_CFGEBIA	0x00c0
#घोषणा PIC32_CFGEBIC	0x00d0
#घोषणा PIC32_CFGCON2	0x00f0
#घोषणा PIC32_RCON	0x1240

अटल व्योम __iomem *pic32_conf_base;
अटल DEFINE_SPINLOCK(config_lock);
अटल u32 pic32_reset_status;

अटल u32 pic32_conf_get_reg_field(u32 offset, u32 rshअगरt, u32 mask)
अणु
	u32 v;

	v = पढ़ोl(pic32_conf_base + offset);
	v >>= rshअगरt;
	v &= mask;

	वापस v;
पूर्ण

अटल u32 pic32_conf_modअगरy_atomic(u32 offset, u32 mask, u32 set)
अणु
	u32 v;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&config_lock, flags);
	v = पढ़ोl(pic32_conf_base + offset);
	v &= ~mask;
	v |= (set & mask);
	ग_लिखोl(v, pic32_conf_base + offset);
	spin_unlock_irqrestore(&config_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक pic32_enable_lcd(व्योम)
अणु
	वापस pic32_conf_modअगरy_atomic(PIC32_CFGCON2, BIT(31), BIT(31));
पूर्ण

पूर्णांक pic32_disable_lcd(व्योम)
अणु
	वापस pic32_conf_modअगरy_atomic(PIC32_CFGCON2, BIT(31), 0);
पूर्ण

पूर्णांक pic32_set_lcd_mode(पूर्णांक mode)
अणु
	u32 mask = mode ? BIT(30) : 0;

	वापस pic32_conf_modअगरy_atomic(PIC32_CFGCON2, BIT(30), mask);
पूर्ण

पूर्णांक pic32_set_sdhci_adma_fअगरo_threshold(u32 rthrsh, u32 wthrsh)
अणु
	u32 clr, set;

	clr = (0x3ff << 4) | (0x3ff << 16);
	set = (rthrsh << 4) | (wthrsh << 16);
	वापस pic32_conf_modअगरy_atomic(PIC32_CFGCON2, clr, set);
पूर्ण

व्योम pic32_syskey_unlock_debug(स्थिर अक्षर *func, स्थिर uदीर्घ line)
अणु
	व्योम __iomem *syskey = pic32_conf_base + PIC32_SYSKEY;

	pr_debug("%s: called from %s:%lu\n", __func__, func, line);
	ग_लिखोl(0x00000000, syskey);
	ग_लिखोl(0xAA996655, syskey);
	ग_लिखोl(0x556699AA, syskey);
पूर्ण

अटल u32 pic32_get_device_id(व्योम)
अणु
	वापस pic32_conf_get_reg_field(PIC32_DEVID, 0, 0x0fffffff);
पूर्ण

अटल u32 pic32_get_device_version(व्योम)
अणु
	वापस pic32_conf_get_reg_field(PIC32_DEVID, 28, 0xf);
पूर्ण

u32 pic32_get_boot_status(व्योम)
अणु
	वापस pic32_reset_status;
पूर्ण
EXPORT_SYMBOL(pic32_get_boot_status);

व्योम __init pic32_config_init(व्योम)
अणु
	pic32_conf_base = ioremap(PIC32_BASE_CONFIG, 0x110);
	अगर (!pic32_conf_base)
		panic("pic32: config base not mapped");

	/* Boot Status */
	pic32_reset_status = पढ़ोl(pic32_conf_base + PIC32_RCON);
	ग_लिखोl(-1, PIC32_CLR(pic32_conf_base + PIC32_RCON));

	/* Device Inक्रमation */
	pr_info("Device Id: 0x%08x, Device Ver: 0x%04x\n",
		pic32_get_device_id(),
		pic32_get_device_version());
पूर्ण
