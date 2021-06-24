<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//      Ben Dooks <ben@simtec.co.uk>
//      http://armlinux.simtec.co.uk/
//
// S3C64XX - Interrupt handling Power Management

/*
 * NOTE: Code in this file is not used when booting with Device Tree support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश "map.h"

#समावेश "regs-gpio.h"
#समावेश "cpu.h"
#समावेश "pm.h"

/* We handled all the IRQ types in this code, to save having to make several
 * small files to handle each dअगरferent type separately. Having the EINT_GRP
 * code here shouldn't be as much bloat as the IRQ table space needed when
 * they are enabled. The added benefit is we ensure that these रेजिस्टरs are
 * in the same state as we suspended.
 */

अटल काष्ठा sleep_save irq_save[] = अणु
	SAVE_ITEM(S3C64XX_PRIORITY),
	SAVE_ITEM(S3C64XX_EINT0CON0),
	SAVE_ITEM(S3C64XX_EINT0CON1),
	SAVE_ITEM(S3C64XX_EINT0FLTCON0),
	SAVE_ITEM(S3C64XX_EINT0FLTCON1),
	SAVE_ITEM(S3C64XX_EINT0FLTCON2),
	SAVE_ITEM(S3C64XX_EINT0FLTCON3),
	SAVE_ITEM(S3C64XX_EINT0MASK),
पूर्ण;

अटल काष्ठा irq_grp_save अणु
	u32	fltcon;
	u32	con;
	u32	mask;
पूर्ण eपूर्णांक_grp_save[5];

#अगर_अघोषित CONFIG_SERIAL_SAMSUNG_UARTS
#घोषणा SERIAL_SAMSUNG_UARTS 0
#अन्यथा
#घोषणा	SERIAL_SAMSUNG_UARTS CONFIG_SERIAL_SAMSUNG_UARTS
#पूर्ण_अगर

अटल u32 irq_uart_mask[SERIAL_SAMSUNG_UARTS];

अटल पूर्णांक s3c64xx_irq_pm_suspend(व्योम)
अणु
	काष्ठा irq_grp_save *grp = eपूर्णांक_grp_save;
	पूर्णांक i;

	S3C_PMDBG("%s: suspending IRQs\n", __func__);

	s3c_pm_करो_save(irq_save, ARRAY_SIZE(irq_save));

	क्रम (i = 0; i < SERIAL_SAMSUNG_UARTS; i++)
		irq_uart_mask[i] = __raw_पढ़ोl(S3C_VA_UARTx(i) + S3C64XX_UINTM);

	क्रम (i = 0; i < ARRAY_SIZE(eपूर्णांक_grp_save); i++, grp++) अणु
		grp->con = __raw_पढ़ोl(S3C64XX_EINT12CON + (i * 4));
		grp->mask = __raw_पढ़ोl(S3C64XX_EINT12MASK + (i * 4));
		grp->fltcon = __raw_पढ़ोl(S3C64XX_EINT12FLTCON + (i * 4));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s3c64xx_irq_pm_resume(व्योम)
अणु
	काष्ठा irq_grp_save *grp = eपूर्णांक_grp_save;
	पूर्णांक i;

	S3C_PMDBG("%s: resuming IRQs\n", __func__);

	s3c_pm_करो_restore(irq_save, ARRAY_SIZE(irq_save));

	क्रम (i = 0; i < SERIAL_SAMSUNG_UARTS; i++)
		__raw_ग_लिखोl(irq_uart_mask[i], S3C_VA_UARTx(i) + S3C64XX_UINTM);

	क्रम (i = 0; i < ARRAY_SIZE(eपूर्णांक_grp_save); i++, grp++) अणु
		__raw_ग_लिखोl(grp->con, S3C64XX_EINT12CON + (i * 4));
		__raw_ग_लिखोl(grp->mask, S3C64XX_EINT12MASK + (i * 4));
		__raw_ग_लिखोl(grp->fltcon, S3C64XX_EINT12FLTCON + (i * 4));
	पूर्ण

	S3C_PMDBG("%s: IRQ configuration restored\n", __func__);
पूर्ण

अटल काष्ठा syscore_ops s3c64xx_irq_syscore_ops = अणु
	.suspend = s3c64xx_irq_pm_suspend,
	.resume	 = s3c64xx_irq_pm_resume,
पूर्ण;

अटल __init पूर्णांक s3c64xx_syscore_init(व्योम)
अणु
	/* Appropriate drivers (pinctrl, uart) handle this when using DT. */
	अगर (of_have_populated_dt() || !soc_is_s3c64xx())
		वापस 0;

	रेजिस्टर_syscore_ops(&s3c64xx_irq_syscore_ops);

	वापस 0;
पूर्ण

core_initcall(s3c64xx_syscore_init);
