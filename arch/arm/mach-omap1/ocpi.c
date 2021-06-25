<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/arch/arm/plat-omap/ocpi.c
 *
 * Minimal OCP bus support क्रम omap16xx
 *
 * Copyright (C) 2003 - 2005 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Written by Tony Lindgren <tony@atomide.com>
 *
 * Modअगरied क्रम घड़ी framework by Paul Mundt <paul.mundt@nokia.com>.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>

#समावेश "common.h"

#घोषणा OCPI_BASE		0xfffec320
#घोषणा OCPI_FAULT		(OCPI_BASE + 0x00)
#घोषणा OCPI_CMD_FAULT		(OCPI_BASE + 0x04)
#घोषणा OCPI_SINT0		(OCPI_BASE + 0x08)
#घोषणा OCPI_TABORT		(OCPI_BASE + 0x0c)
#घोषणा OCPI_SINT1		(OCPI_BASE + 0x10)
#घोषणा OCPI_PROT		(OCPI_BASE + 0x14)
#घोषणा OCPI_SEC		(OCPI_BASE + 0x18)

/* USB OHCI OCPI access error रेजिस्टरs */
#घोषणा HOSTUEADDR	0xfffba0e0
#घोषणा HOSTUESTATUS	0xfffba0e4

अटल काष्ठा clk *ocpi_ck;

/*
 * Enables device access to OMAP buses via the OCPI bridge
 */
पूर्णांक ocpi_enable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!cpu_is_omap16xx())
		वापस -ENODEV;

	/* Enable access क्रम OHCI in OCPI */
	val = omap_पढ़ोl(OCPI_PROT);
	val &= ~0xff;
	/* val &= (1 << 0);	 Allow access only to EMIFS */
	omap_ग_लिखोl(val, OCPI_PROT);

	val = omap_पढ़ोl(OCPI_SEC);
	val &= ~0xff;
	omap_ग_लिखोl(val, OCPI_SEC);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocpi_enable);

अटल पूर्णांक __init omap_ocpi_init(व्योम)
अणु
	अगर (!cpu_is_omap16xx())
		वापस -ENODEV;

	ocpi_ck = clk_get(शून्य, "l3_ocpi_ck");
	अगर (IS_ERR(ocpi_ck))
		वापस PTR_ERR(ocpi_ck);

	clk_enable(ocpi_ck);
	ocpi_enable();
	pr_info("OMAP OCPI interconnect driver loaded\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास omap_ocpi_निकास(व्योम)
अणु
	/* REVISIT: Disable OCPI */

	अगर (!cpu_is_omap16xx())
		वापस;

	clk_disable(ocpi_ck);
	clk_put(ocpi_ck);
पूर्ण

MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("OMAP OCPI bus controller module");
MODULE_LICENSE("GPL");
module_init(omap_ocpi_init);
module_निकास(omap_ocpi_निकास);
