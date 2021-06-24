<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc
 *
 * Freescale Integrated Flash Controller
 *
 * Author: Dipen Dudhat <Dipen.Dudhat@मुक्तscale.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fsl_अगरc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

काष्ठा fsl_अगरc_ctrl *fsl_अगरc_ctrl_dev;
EXPORT_SYMBOL(fsl_अगरc_ctrl_dev);

/*
 * convert_अगरc_address - convert the base address
 * @addr_base:	base address of the memory bank
 */
अचिन्हित पूर्णांक convert_अगरc_address(phys_addr_t addr_base)
अणु
	वापस addr_base & CSPR_BA;
पूर्ण
EXPORT_SYMBOL(convert_अगरc_address);

/*
 * fsl_अगरc_find - find IFC bank
 * @addr_base:	base address of the memory bank
 *
 * This function walks IFC banks comparing "Base address" field of the CSPR
 * रेजिस्टरs with the supplied addr_base argument. When bases match this
 * function वापसs bank number (starting with 0), otherwise it वापसs
 * appropriate त्रुटि_सं value.
 */
पूर्णांक fsl_अगरc_find(phys_addr_t addr_base)
अणु
	पूर्णांक i = 0;

	अगर (!fsl_अगरc_ctrl_dev || !fsl_अगरc_ctrl_dev->gregs)
		वापस -ENODEV;

	क्रम (i = 0; i < fsl_अगरc_ctrl_dev->banks; i++) अणु
		u32 cspr = अगरc_in32(&fsl_अगरc_ctrl_dev->gregs->cspr_cs[i].cspr);

		अगर (cspr & CSPR_V && (cspr & CSPR_BA) ==
				convert_अगरc_address(addr_base))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(fsl_अगरc_find);

अटल पूर्णांक fsl_अगरc_ctrl_init(काष्ठा fsl_अगरc_ctrl *ctrl)
अणु
	काष्ठा fsl_अगरc_global __iomem *अगरc = ctrl->gregs;

	/*
	 * Clear all the common status and event रेजिस्टरs
	 */
	अगर (अगरc_in32(&अगरc->cm_evter_stat) & IFC_CM_EVTER_STAT_CSER)
		अगरc_out32(IFC_CM_EVTER_STAT_CSER, &अगरc->cm_evter_stat);

	/* enable all error and events */
	अगरc_out32(IFC_CM_EVTER_EN_CSEREN, &अगरc->cm_evter_en);

	/* enable all error and event पूर्णांकerrupts */
	अगरc_out32(IFC_CM_EVTER_INTR_EN_CSERIREN, &अगरc->cm_evter_पूर्णांकr_en);
	अगरc_out32(0x0, &अगरc->cm_erattr0);
	अगरc_out32(0x0, &अगरc->cm_erattr1);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_अगरc_ctrl_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fsl_अगरc_ctrl *ctrl = dev_get_drvdata(&dev->dev);

	मुक्त_irq(ctrl->nand_irq, ctrl);
	मुक्त_irq(ctrl->irq, ctrl);

	irq_dispose_mapping(ctrl->nand_irq);
	irq_dispose_mapping(ctrl->irq);

	iounmap(ctrl->gregs);

	dev_set_drvdata(&dev->dev, शून्य);
	kमुक्त(ctrl);

	वापस 0;
पूर्ण

/*
 * न_अंकD events are split between an operational पूर्णांकerrupt which only
 * receives OPC, and an error पूर्णांकerrupt that receives everything अन्यथा,
 * including non-न_अंकD errors.  Whichever पूर्णांकerrupt माला_लो to it first
 * records the status and wakes the रुको queue.
 */
अटल DEFINE_SPINLOCK(nand_irq_lock);

अटल u32 check_nand_stat(काष्ठा fsl_अगरc_ctrl *ctrl)
अणु
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;
	अचिन्हित दीर्घ flags;
	u32 stat;

	spin_lock_irqsave(&nand_irq_lock, flags);

	stat = अगरc_in32(&अगरc->अगरc_nand.nand_evter_stat);
	अगर (stat) अणु
		अगरc_out32(stat, &अगरc->अगरc_nand.nand_evter_stat);
		ctrl->nand_stat = stat;
		wake_up(&ctrl->nand_रुको);
	पूर्ण

	spin_unlock_irqrestore(&nand_irq_lock, flags);

	वापस stat;
पूर्ण

अटल irqवापस_t fsl_अगरc_nand_irq(पूर्णांक irqno, व्योम *data)
अणु
	काष्ठा fsl_अगरc_ctrl *ctrl = data;

	अगर (check_nand_stat(ctrl))
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

/*
 * NOTE: This पूर्णांकerrupt is used to report अगरc events of various kinds,
 * such as transaction errors on the chipselects.
 */
अटल irqवापस_t fsl_अगरc_ctrl_irq(पूर्णांक irqno, व्योम *data)
अणु
	काष्ठा fsl_अगरc_ctrl *ctrl = data;
	काष्ठा fsl_अगरc_global __iomem *अगरc = ctrl->gregs;
	u32 err_axiid, err_srcid, status, cs_err, err_addr;
	irqवापस_t ret = IRQ_NONE;

	/* पढ़ो क्रम chip select error */
	cs_err = अगरc_in32(&अगरc->cm_evter_stat);
	अगर (cs_err) अणु
		dev_err(ctrl->dev, "transaction sent to IFC is not mapped to any memory bank 0x%08X\n",
			cs_err);
		/* clear the chip select error */
		अगरc_out32(IFC_CM_EVTER_STAT_CSER, &अगरc->cm_evter_stat);

		/* पढ़ो error attribute रेजिस्टरs prपूर्णांक the error inक्रमmation */
		status = अगरc_in32(&अगरc->cm_erattr0);
		err_addr = अगरc_in32(&अगरc->cm_erattr1);

		अगर (status & IFC_CM_ERATTR0_ERTYP_READ)
			dev_err(ctrl->dev, "Read transaction error CM_ERATTR0 0x%08X\n",
				status);
		अन्यथा
			dev_err(ctrl->dev, "Write transaction error CM_ERATTR0 0x%08X\n",
				status);

		err_axiid = (status & IFC_CM_ERATTR0_ERAID) >>
					IFC_CM_ERATTR0_ERAID_SHIFT;
		dev_err(ctrl->dev, "AXI ID of the error transaction 0x%08X\n",
			err_axiid);

		err_srcid = (status & IFC_CM_ERATTR0_ESRCID) >>
					IFC_CM_ERATTR0_ESRCID_SHIFT;
		dev_err(ctrl->dev, "SRC ID of the error transaction 0x%08X\n",
			err_srcid);

		dev_err(ctrl->dev, "Transaction Address corresponding to error ERADDR 0x%08X\n",
			err_addr);

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (check_nand_stat(ctrl))
		ret = IRQ_HANDLED;

	वापस ret;
पूर्ण

/*
 * fsl_अगरc_ctrl_probe
 *
 * called by device layer when it finds a device matching
 * one our driver can handled. This code allocates all of
 * the resources needed क्रम the controller only.  The
 * resources क्रम the न_अंकD banks themselves are allocated
 * in the chip probe function.
 */
अटल पूर्णांक fsl_अगरc_ctrl_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक version, banks;
	व्योम __iomem *addr;

	dev_info(&dev->dev, "Freescale Integrated Flash Controller\n");

	fsl_अगरc_ctrl_dev = kzalloc(माप(*fsl_अगरc_ctrl_dev), GFP_KERNEL);
	अगर (!fsl_अगरc_ctrl_dev)
		वापस -ENOMEM;

	dev_set_drvdata(&dev->dev, fsl_अगरc_ctrl_dev);

	/* IOMAP the entire IFC region */
	fsl_अगरc_ctrl_dev->gregs = of_iomap(dev->dev.of_node, 0);
	अगर (!fsl_अगरc_ctrl_dev->gregs) अणु
		dev_err(&dev->dev, "failed to get memory region\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dev->dev.of_node, "little-endian")) अणु
		fsl_अगरc_ctrl_dev->little_endian = true;
		dev_dbg(&dev->dev, "IFC REGISTERS are LITTLE endian\n");
	पूर्ण अन्यथा अणु
		fsl_अगरc_ctrl_dev->little_endian = false;
		dev_dbg(&dev->dev, "IFC REGISTERS are BIG endian\n");
	पूर्ण

	version = अगरc_in32(&fsl_अगरc_ctrl_dev->gregs->अगरc_rev) &
			FSL_IFC_VERSION_MASK;

	banks = (version == FSL_IFC_VERSION_1_0_0) ? 4 : 8;
	dev_info(&dev->dev, "IFC version %d.%d, %d banks\n",
		version >> 24, (version >> 16) & 0xf, banks);

	fsl_अगरc_ctrl_dev->version = version;
	fsl_अगरc_ctrl_dev->banks = banks;

	addr = fsl_अगरc_ctrl_dev->gregs;
	अगर (version >= FSL_IFC_VERSION_2_0_0)
		addr += PGOFFSET_64K;
	अन्यथा
		addr += PGOFFSET_4K;
	fsl_अगरc_ctrl_dev->rregs = addr;

	/* get the Controller level irq */
	fsl_अगरc_ctrl_dev->irq = irq_of_parse_and_map(dev->dev.of_node, 0);
	अगर (fsl_अगरc_ctrl_dev->irq == 0) अणु
		dev_err(&dev->dev, "failed to get irq resource for IFC\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* get the nand machine irq */
	fsl_अगरc_ctrl_dev->nand_irq =
			irq_of_parse_and_map(dev->dev.of_node, 1);

	fsl_अगरc_ctrl_dev->dev = &dev->dev;

	ret = fsl_अगरc_ctrl_init(fsl_अगरc_ctrl_dev);
	अगर (ret < 0)
		जाओ err;

	init_रुकोqueue_head(&fsl_अगरc_ctrl_dev->nand_रुको);

	ret = request_irq(fsl_अगरc_ctrl_dev->irq, fsl_अगरc_ctrl_irq, IRQF_SHARED,
			  "fsl-ifc", fsl_अगरc_ctrl_dev);
	अगर (ret != 0) अणु
		dev_err(&dev->dev, "failed to install irq (%d)\n",
			fsl_अगरc_ctrl_dev->irq);
		जाओ err_irq;
	पूर्ण

	अगर (fsl_अगरc_ctrl_dev->nand_irq) अणु
		ret = request_irq(fsl_अगरc_ctrl_dev->nand_irq, fsl_अगरc_nand_irq,
				0, "fsl-ifc-nand", fsl_अगरc_ctrl_dev);
		अगर (ret != 0) अणु
			dev_err(&dev->dev, "failed to install irq (%d)\n",
				fsl_अगरc_ctrl_dev->nand_irq);
			जाओ err_nandirq;
		पूर्ण
	पूर्ण

	वापस 0;

err_nandirq:
	मुक्त_irq(fsl_अगरc_ctrl_dev->nand_irq, fsl_अगरc_ctrl_dev);
	irq_dispose_mapping(fsl_अगरc_ctrl_dev->nand_irq);
err_irq:
	मुक्त_irq(fsl_अगरc_ctrl_dev->irq, fsl_अगरc_ctrl_dev);
	irq_dispose_mapping(fsl_अगरc_ctrl_dev->irq);
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_अगरc_match[] = अणु
	अणु
		.compatible = "fsl,ifc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_अगरc_ctrl_driver = अणु
	.driver = अणु
		.name	= "fsl-ifc",
		.of_match_table = fsl_अगरc_match,
	पूर्ण,
	.probe       = fsl_अगरc_ctrl_probe,
	.हटाओ      = fsl_अगरc_ctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init fsl_अगरc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fsl_अगरc_ctrl_driver);
पूर्ण
subsys_initcall(fsl_अगरc_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Freescale Semiconductor");
MODULE_DESCRIPTION("Freescale Integrated Flash Controller driver");
