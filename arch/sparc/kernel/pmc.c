<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pmc - Driver implementation क्रम घातer management functions
 * of Power Management Controller (PMC) on SPARCstation-Voyager.
 *
 * Copyright (c) 2002 Eric Brower (ebrower@usa.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/processor.h>

/* Debug
 *
 * #घोषणा PMC_DEBUG_LED
 * #घोषणा PMC_NO_IDLE
 */

#घोषणा PMC_OBPNAME	"SUNW,pmc"
#घोषणा PMC_DEVNAME	"pmc"

#घोषणा PMC_IDLE_REG	0x00
#घोषणा PMC_IDLE_ON	0x01

अटल u8 __iomem *regs;

#घोषणा pmc_पढ़ोb(offs)		(sbus_पढ़ोb(regs+offs))
#घोषणा pmc_ग_लिखोb(val, offs)	(sbus_ग_लिखोb(val, regs+offs))

/*
 * CPU idle callback function
 * See .../arch/sparc/kernel/process.c
 */
अटल व्योम pmc_swअगरt_idle(व्योम)
अणु
#अगर_घोषित PMC_DEBUG_LED
	set_auxio(0x00, AUXIO_LED);
#पूर्ण_अगर

	pmc_ग_लिखोb(pmc_पढ़ोb(PMC_IDLE_REG) | PMC_IDLE_ON, PMC_IDLE_REG);

#अगर_घोषित PMC_DEBUG_LED
	set_auxio(AUXIO_LED, 0x00);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक pmc_probe(काष्ठा platक्रमm_device *op)
अणु
	regs = of_ioremap(&op->resource[0], 0,
			  resource_size(&op->resource[0]), PMC_OBPNAME);
	अगर (!regs) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to map registers\n", PMC_DEVNAME);
		वापस -ENODEV;
	पूर्ण

#अगर_अघोषित PMC_NO_IDLE
	/* Assign घातer management IDLE handler */
	sparc_idle = pmc_swअगरt_idle;
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "%s: power management initialized\n", PMC_DEVNAME);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pmc_match[] = अणु
	अणु
		.name = PMC_OBPNAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pmc_match);

अटल काष्ठा platक्रमm_driver pmc_driver = अणु
	.driver = अणु
		.name = "pmc",
		.of_match_table = pmc_match,
	पूर्ण,
	.probe		= pmc_probe,
पूर्ण;

अटल पूर्णांक __init pmc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pmc_driver);
पूर्ण

/* This driver is not critical to the boot process
 * and is easiest to ioremap when SBus is alपढ़ोy
 * initialized, so we install ourselves thusly:
 */
__initcall(pmc_init);
