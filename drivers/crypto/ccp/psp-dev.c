<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Platक्रमm Security Processor (PSP) पूर्णांकerface
 *
 * Copyright (C) 2016,2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irqवापस.h>

#समावेश "sp-dev.h"
#समावेश "psp-dev.h"
#समावेश "sev-dev.h"
#समावेश "tee-dev.h"

काष्ठा psp_device *psp_master;

अटल काष्ठा psp_device *psp_alloc_काष्ठा(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा psp_device *psp;

	psp = devm_kzalloc(dev, माप(*psp), GFP_KERNEL);
	अगर (!psp)
		वापस शून्य;

	psp->dev = dev;
	psp->sp = sp;

	snम_लिखो(psp->name, माप(psp->name), "psp-%u", sp->ord);

	वापस psp;
पूर्ण

अटल irqवापस_t psp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा psp_device *psp = data;
	अचिन्हित पूर्णांक status;

	/* Read the पूर्णांकerrupt status: */
	status = ioपढ़ो32(psp->io_regs + psp->vdata->पूर्णांकsts_reg);

	/* invoke subdevice पूर्णांकerrupt handlers */
	अगर (status) अणु
		अगर (psp->sev_irq_handler)
			psp->sev_irq_handler(irq, psp->sev_irq_data, status);

		अगर (psp->tee_irq_handler)
			psp->tee_irq_handler(irq, psp->tee_irq_data, status);
	पूर्ण

	/* Clear the पूर्णांकerrupt status by writing the same value we पढ़ो. */
	ioग_लिखो32(status, psp->io_regs + psp->vdata->पूर्णांकsts_reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक psp_get_capability(काष्ठा psp_device *psp)
अणु
	अचिन्हित पूर्णांक val = ioपढ़ो32(psp->io_regs + psp->vdata->feature_reg);

	/*
	 * Check क्रम a access to the रेजिस्टरs.  If this पढ़ो वापसs
	 * 0xffffffff, it's likely that the प्रणाली is running a broken
	 * BIOS which disallows access to the device. Stop here and
	 * fail the PSP initialization (but not the load, as the CCP
	 * could get properly initialized).
	 */
	अगर (val == 0xffffffff) अणु
		dev_notice(psp->dev, "psp: unable to access the device: you might be running a broken BIOS.\n");
		वापस 0;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक psp_check_sev_support(काष्ठा psp_device *psp,
				 अचिन्हित पूर्णांक capability)
अणु
	/* Check अगर device supports SEV feature */
	अगर (!(capability & 1)) अणु
		dev_dbg(psp->dev, "psp does not support SEV\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_check_tee_support(काष्ठा psp_device *psp,
				 अचिन्हित पूर्णांक capability)
अणु
	/* Check अगर device supports TEE feature */
	अगर (!(capability & 2)) अणु
		dev_dbg(psp->dev, "psp does not support TEE\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_check_support(काष्ठा psp_device *psp,
			     अचिन्हित पूर्णांक capability)
अणु
	पूर्णांक sev_support = psp_check_sev_support(psp, capability);
	पूर्णांक tee_support = psp_check_tee_support(psp, capability);

	/* Return error अगर device neither supports SEV nor TEE */
	अगर (sev_support && tee_support)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक psp_init(काष्ठा psp_device *psp, अचिन्हित पूर्णांक capability)
अणु
	पूर्णांक ret;

	अगर (!psp_check_sev_support(psp, capability)) अणु
		ret = sev_dev_init(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!psp_check_tee_support(psp, capability)) अणु
		ret = tee_dev_init(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक psp_dev_init(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा psp_device *psp;
	अचिन्हित पूर्णांक capability;
	पूर्णांक ret;

	ret = -ENOMEM;
	psp = psp_alloc_काष्ठा(sp);
	अगर (!psp)
		जाओ e_err;

	sp->psp_data = psp;

	psp->vdata = (काष्ठा psp_vdata *)sp->dev_vdata->psp_vdata;
	अगर (!psp->vdata) अणु
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		जाओ e_err;
	पूर्ण

	psp->io_regs = sp->io_map;

	capability = psp_get_capability(psp);
	अगर (!capability)
		जाओ e_disable;

	ret = psp_check_support(psp, capability);
	अगर (ret)
		जाओ e_disable;

	/* Disable and clear पूर्णांकerrupts until पढ़ोy */
	ioग_लिखो32(0, psp->io_regs + psp->vdata->पूर्णांकen_reg);
	ioग_लिखो32(-1, psp->io_regs + psp->vdata->पूर्णांकsts_reg);

	/* Request an irq */
	ret = sp_request_psp_irq(psp->sp, psp_irq_handler, psp->name, psp);
	अगर (ret) अणु
		dev_err(dev, "psp: unable to allocate an IRQ\n");
		जाओ e_err;
	पूर्ण

	ret = psp_init(psp, capability);
	अगर (ret)
		जाओ e_irq;

	अगर (sp->set_psp_master_device)
		sp->set_psp_master_device(sp);

	/* Enable पूर्णांकerrupt */
	ioग_लिखो32(-1, psp->io_regs + psp->vdata->पूर्णांकen_reg);

	dev_notice(dev, "psp enabled\n");

	वापस 0;

e_irq:
	sp_मुक्त_psp_irq(psp->sp, psp);
e_err:
	sp->psp_data = शून्य;

	dev_notice(dev, "psp initialization failed\n");

	वापस ret;

e_disable:
	sp->psp_data = शून्य;

	वापस ret;
पूर्ण

व्योम psp_dev_destroy(काष्ठा sp_device *sp)
अणु
	काष्ठा psp_device *psp = sp->psp_data;

	अगर (!psp)
		वापस;

	sev_dev_destroy(psp);

	tee_dev_destroy(psp);

	sp_मुक्त_psp_irq(sp, psp);

	अगर (sp->clear_psp_master_device)
		sp->clear_psp_master_device(sp);
पूर्ण

व्योम psp_set_sev_irq_handler(काष्ठा psp_device *psp, psp_irq_handler_t handler,
			     व्योम *data)
अणु
	psp->sev_irq_data = data;
	psp->sev_irq_handler = handler;
पूर्ण

व्योम psp_clear_sev_irq_handler(काष्ठा psp_device *psp)
अणु
	psp_set_sev_irq_handler(psp, शून्य, शून्य);
पूर्ण

व्योम psp_set_tee_irq_handler(काष्ठा psp_device *psp, psp_irq_handler_t handler,
			     व्योम *data)
अणु
	psp->tee_irq_data = data;
	psp->tee_irq_handler = handler;
पूर्ण

व्योम psp_clear_tee_irq_handler(काष्ठा psp_device *psp)
अणु
	psp_set_tee_irq_handler(psp, शून्य, शून्य);
पूर्ण

काष्ठा psp_device *psp_get_master_device(व्योम)
अणु
	काष्ठा sp_device *sp = sp_get_psp_master_device();

	वापस sp ? sp->psp_data : शून्य;
पूर्ण

व्योम psp_pci_init(व्योम)
अणु
	psp_master = psp_get_master_device();

	अगर (!psp_master)
		वापस;

	sev_pci_init();
पूर्ण

व्योम psp_pci_निकास(व्योम)
अणु
	अगर (!psp_master)
		वापस;

	sev_pci_निकास();
पूर्ण
