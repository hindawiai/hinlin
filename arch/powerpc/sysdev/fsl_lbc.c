<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale LBC and UPM routines.
 *
 * Copyright तऊ 2007-2008  MontaVista Software, Inc.
 * Copyright तऊ 2010 Freescale Semiconductor
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 * Author: Jack Lan <Jack.Lan@मुक्तscale.com>
 * Author: Roy Zang <tie-fei.zang@मुक्तscale.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/fsl_lbc.h>

अटल DEFINE_SPINLOCK(fsl_lbc_lock);
काष्ठा fsl_lbc_ctrl *fsl_lbc_ctrl_dev;
EXPORT_SYMBOL(fsl_lbc_ctrl_dev);

/**
 * fsl_lbc_addr - convert the base address
 * @addr_base:	base address of the memory bank
 *
 * This function converts a base address of lbc पूर्णांकo the right क्रमmat क्रम the
 * BR रेजिस्टर. If the SOC has eLBC then it वापसs 32bit physical address
 * अन्यथा it convers a 34bit local bus physical address to correct क्रमmat of
 * 32bit address क्रम BR रेजिस्टर (Example: MPC8641).
 */
u32 fsl_lbc_addr(phys_addr_t addr_base)
अणु
	काष्ठा device_node *np = fsl_lbc_ctrl_dev->dev->of_node;
	u32 addr = addr_base & 0xffff8000;

	अगर (of_device_is_compatible(np, "fsl,elbc"))
		वापस addr;

	वापस addr | ((addr_base & 0x300000000ull) >> 19);
पूर्ण
EXPORT_SYMBOL(fsl_lbc_addr);

/**
 * fsl_lbc_find - find Localbus bank
 * @addr_base:	base address of the memory bank
 *
 * This function walks LBC banks comparing "Base address" field of the BR
 * रेजिस्टरs with the supplied addr_base argument. When bases match this
 * function वापसs bank number (starting with 0), otherwise it वापसs
 * appropriate त्रुटि_सं value.
 */
पूर्णांक fsl_lbc_find(phys_addr_t addr_base)
अणु
	पूर्णांक i;
	काष्ठा fsl_lbc_regs __iomem *lbc;

	अगर (!fsl_lbc_ctrl_dev || !fsl_lbc_ctrl_dev->regs)
		वापस -ENODEV;

	lbc = fsl_lbc_ctrl_dev->regs;
	क्रम (i = 0; i < ARRAY_SIZE(lbc->bank); i++) अणु
		u32 br = in_be32(&lbc->bank[i].br);
		u32 or = in_be32(&lbc->bank[i].or);

		अगर (br & BR_V && (br & or & BR_BA) == fsl_lbc_addr(addr_base))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(fsl_lbc_find);

/**
 * fsl_upm_find - find pre-programmed UPM via base address
 * @addr_base:	base address of the memory bank controlled by the UPM
 * @upm:	poपूर्णांकer to the allocated fsl_upm काष्ठाure
 *
 * This function fills fsl_upm काष्ठाure so you can use it with the rest of
 * UPM API. On success this function वापसs 0, otherwise it वापसs
 * appropriate त्रुटि_सं value.
 */
पूर्णांक fsl_upm_find(phys_addr_t addr_base, काष्ठा fsl_upm *upm)
अणु
	पूर्णांक bank;
	u32 br;
	काष्ठा fsl_lbc_regs __iomem *lbc;

	bank = fsl_lbc_find(addr_base);
	अगर (bank < 0)
		वापस bank;

	अगर (!fsl_lbc_ctrl_dev || !fsl_lbc_ctrl_dev->regs)
		वापस -ENODEV;

	lbc = fsl_lbc_ctrl_dev->regs;
	br = in_be32(&lbc->bank[bank].br);

	चयन (br & BR_MSEL) अणु
	हाल BR_MS_UPMA:
		upm->mxmr = &lbc->mamr;
		अवरोध;
	हाल BR_MS_UPMB:
		upm->mxmr = &lbc->mbmr;
		अवरोध;
	हाल BR_MS_UPMC:
		upm->mxmr = &lbc->mcmr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (br & BR_PS) अणु
	हाल BR_PS_8:
		upm->width = 8;
		अवरोध;
	हाल BR_PS_16:
		upm->width = 16;
		अवरोध;
	हाल BR_PS_32:
		upm->width = 32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fsl_upm_find);

/**
 * fsl_upm_run_pattern - actually run an UPM pattern
 * @upm:	poपूर्णांकer to the fsl_upm काष्ठाure obtained via fsl_upm_find
 * @io_base:	remapped poपूर्णांकer to where memory access should happen
 * @mar:	MAR रेजिस्टर content during pattern execution
 *
 * This function triggers dummy ग_लिखो to the memory specअगरied by the io_base,
 * thus UPM pattern actually executed. Note that mar usage depends on the
 * pre-programmed AMX bits in the UPM RAM.
 */
पूर्णांक fsl_upm_run_pattern(काष्ठा fsl_upm *upm, व्योम __iomem *io_base, u32 mar)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (!fsl_lbc_ctrl_dev || !fsl_lbc_ctrl_dev->regs)
		वापस -ENODEV;

	spin_lock_irqsave(&fsl_lbc_lock, flags);

	out_be32(&fsl_lbc_ctrl_dev->regs->mar, mar);

	चयन (upm->width) अणु
	हाल 8:
		out_8(io_base, 0x0);
		अवरोध;
	हाल 16:
		out_be16(io_base, 0x0);
		अवरोध;
	हाल 32:
		out_be32(io_base, 0x0);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&fsl_lbc_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fsl_upm_run_pattern);

अटल पूर्णांक fsl_lbc_ctrl_init(काष्ठा fsl_lbc_ctrl *ctrl,
			     काष्ठा device_node *node)
अणु
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;

	/* clear event रेजिस्टरs */
	setbits32(&lbc->ltesr, LTESR_CLEAR);
	out_be32(&lbc->lteatr, 0);
	out_be32(&lbc->ltear, 0);
	out_be32(&lbc->lteccr, LTECCR_CLEAR);
	out_be32(&lbc->ltedr, LTEDR_ENABLE);

	/* Set the monitor समयout value to the maximum क्रम erratum A001 */
	अगर (of_device_is_compatible(node, "fsl,elbc"))
		clrsetbits_be32(&lbc->lbcr, LBCR_BMT, LBCR_BMTPS);

	वापस 0;
पूर्ण

/*
 * NOTE: This पूर्णांकerrupt is used to report localbus events of various kinds,
 * such as transaction errors on the chipselects.
 */

अटल irqवापस_t fsl_lbc_ctrl_irq(पूर्णांक irqno, व्योम *data)
अणु
	काष्ठा fsl_lbc_ctrl *ctrl = data;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;
	u32 status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fsl_lbc_lock, flags);
	status = in_be32(&lbc->ltesr);
	अगर (!status) अणु
		spin_unlock_irqrestore(&fsl_lbc_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	out_be32(&lbc->ltesr, LTESR_CLEAR);
	out_be32(&lbc->lteatr, 0);
	out_be32(&lbc->ltear, 0);
	ctrl->irq_status = status;

	अगर (status & LTESR_BM)
		dev_err(ctrl->dev, "Local bus monitor time-out: "
			"LTESR 0x%08X\n", status);
	अगर (status & LTESR_WP)
		dev_err(ctrl->dev, "Write protect error: "
			"LTESR 0x%08X\n", status);
	अगर (status & LTESR_ATMW)
		dev_err(ctrl->dev, "Atomic write error: "
			"LTESR 0x%08X\n", status);
	अगर (status & LTESR_ATMR)
		dev_err(ctrl->dev, "Atomic read error: "
			"LTESR 0x%08X\n", status);
	अगर (status & LTESR_CS)
		dev_err(ctrl->dev, "Chip select error: "
			"LTESR 0x%08X\n", status);
	अगर (status & LTESR_FCT) अणु
		dev_err(ctrl->dev, "FCM command time-out: "
			"LTESR 0x%08X\n", status);
		smp_wmb();
		wake_up(&ctrl->irq_रुको);
	पूर्ण
	अगर (status & LTESR_PAR) अणु
		dev_err(ctrl->dev, "Parity or Uncorrectable ECC error: "
			"LTESR 0x%08X\n", status);
		smp_wmb();
		wake_up(&ctrl->irq_रुको);
	पूर्ण
	अगर (status & LTESR_CC) अणु
		smp_wmb();
		wake_up(&ctrl->irq_रुको);
	पूर्ण
	अगर (status & ~LTESR_MASK)
		dev_err(ctrl->dev, "Unknown error: "
			"LTESR 0x%08X\n", status);
	spin_unlock_irqrestore(&fsl_lbc_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * fsl_lbc_ctrl_probe
 *
 * called by device layer when it finds a device matching
 * one our driver can handled. This code allocates all of
 * the resources needed क्रम the controller only.  The
 * resources क्रम the न_अंकD banks themselves are allocated
 * in the chip probe function.
*/

अटल पूर्णांक fsl_lbc_ctrl_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->dev.of_node) अणु
		dev_err(&dev->dev, "Device OF-Node is NULL");
		वापस -EFAULT;
	पूर्ण

	fsl_lbc_ctrl_dev = kzalloc(माप(*fsl_lbc_ctrl_dev), GFP_KERNEL);
	अगर (!fsl_lbc_ctrl_dev)
		वापस -ENOMEM;

	dev_set_drvdata(&dev->dev, fsl_lbc_ctrl_dev);

	spin_lock_init(&fsl_lbc_ctrl_dev->lock);
	init_रुकोqueue_head(&fsl_lbc_ctrl_dev->irq_रुको);

	fsl_lbc_ctrl_dev->regs = of_iomap(dev->dev.of_node, 0);
	अगर (!fsl_lbc_ctrl_dev->regs) अणु
		dev_err(&dev->dev, "failed to get memory region\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	fsl_lbc_ctrl_dev->irq[0] = irq_of_parse_and_map(dev->dev.of_node, 0);
	अगर (!fsl_lbc_ctrl_dev->irq[0]) अणु
		dev_err(&dev->dev, "failed to get irq resource\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	fsl_lbc_ctrl_dev->dev = &dev->dev;

	ret = fsl_lbc_ctrl_init(fsl_lbc_ctrl_dev, dev->dev.of_node);
	अगर (ret < 0)
		जाओ err;

	ret = request_irq(fsl_lbc_ctrl_dev->irq[0], fsl_lbc_ctrl_irq, 0,
				"fsl-lbc", fsl_lbc_ctrl_dev);
	अगर (ret != 0) अणु
		dev_err(&dev->dev, "failed to install irq (%d)\n",
			fsl_lbc_ctrl_dev->irq[0]);
		ret = fsl_lbc_ctrl_dev->irq[0];
		जाओ err;
	पूर्ण

	fsl_lbc_ctrl_dev->irq[1] = irq_of_parse_and_map(dev->dev.of_node, 1);
	अगर (fsl_lbc_ctrl_dev->irq[1]) अणु
		ret = request_irq(fsl_lbc_ctrl_dev->irq[1], fsl_lbc_ctrl_irq,
				IRQF_SHARED, "fsl-lbc-err", fsl_lbc_ctrl_dev);
		अगर (ret) अणु
			dev_err(&dev->dev, "failed to install irq (%d)\n",
					fsl_lbc_ctrl_dev->irq[1]);
			ret = fsl_lbc_ctrl_dev->irq[1];
			जाओ err1;
		पूर्ण
	पूर्ण

	/* Enable पूर्णांकerrupts क्रम any detected events */
	out_be32(&fsl_lbc_ctrl_dev->regs->lteir, LTEIR_ENABLE);

	वापस 0;

err1:
	मुक्त_irq(fsl_lbc_ctrl_dev->irq[0], fsl_lbc_ctrl_dev);
err:
	iounmap(fsl_lbc_ctrl_dev->regs);
	kमुक्त(fsl_lbc_ctrl_dev);
	fsl_lbc_ctrl_dev = शून्य;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SUSPEND

/* save lbc रेजिस्टरs */
अटल पूर्णांक fsl_lbc_syscore_suspend(व्योम)
अणु
	काष्ठा fsl_lbc_ctrl *ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc;

	ctrl = fsl_lbc_ctrl_dev;
	अगर (!ctrl)
		जाओ out;

	lbc = ctrl->regs;
	अगर (!lbc)
		जाओ out;

	ctrl->saved_regs = kदो_स्मृति(माप(काष्ठा fsl_lbc_regs), GFP_KERNEL);
	अगर (!ctrl->saved_regs)
		वापस -ENOMEM;

	_स_नकल_fromio(ctrl->saved_regs, lbc, माप(काष्ठा fsl_lbc_regs));

out:
	वापस 0;
पूर्ण

/* restore lbc रेजिस्टरs */
अटल व्योम fsl_lbc_syscore_resume(व्योम)
अणु
	काष्ठा fsl_lbc_ctrl *ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc;

	ctrl = fsl_lbc_ctrl_dev;
	अगर (!ctrl)
		जाओ out;

	lbc = ctrl->regs;
	अगर (!lbc)
		जाओ out;

	अगर (ctrl->saved_regs) अणु
		_स_नकल_toio(lbc, ctrl->saved_regs,
				माप(काष्ठा fsl_lbc_regs));
		kमुक्त(ctrl->saved_regs);
		ctrl->saved_regs = शून्य;
	पूर्ण

out:
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल स्थिर काष्ठा of_device_id fsl_lbc_match[] = अणु
	अणु .compatible = "fsl,elbc", पूर्ण,
	अणु .compatible = "fsl,pq3-localbus", पूर्ण,
	अणु .compatible = "fsl,pq2-localbus", पूर्ण,
	अणु .compatible = "fsl,pq2pro-localbus", पूर्ण,
	अणुपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SUSPEND
अटल काष्ठा syscore_ops lbc_syscore_pm_ops = अणु
	.suspend = fsl_lbc_syscore_suspend,
	.resume = fsl_lbc_syscore_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver fsl_lbc_ctrl_driver = अणु
	.driver = अणु
		.name = "fsl-lbc",
		.of_match_table = fsl_lbc_match,
	पूर्ण,
	.probe = fsl_lbc_ctrl_probe,
पूर्ण;

अटल पूर्णांक __init fsl_lbc_init(व्योम)
अणु
#अगर_घोषित CONFIG_SUSPEND
	रेजिस्टर_syscore_ops(&lbc_syscore_pm_ops);
#पूर्ण_अगर
	वापस platक्रमm_driver_रेजिस्टर(&fsl_lbc_ctrl_driver);
पूर्ण
subsys_initcall(fsl_lbc_init);
