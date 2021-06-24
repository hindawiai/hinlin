<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Secure Processor driver
 *
 * Copyright (C) 2017-2018 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"
#समावेश "sp-dev.h"

MODULE_AUTHOR("Tom Lendacky <thomas.lendacky@amd.com>");
MODULE_AUTHOR("Gary R Hook <gary.hook@amd.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1.0");
MODULE_DESCRIPTION("AMD Secure Processor driver");

/* List of SPs, SP count, पढ़ो-ग_लिखो access lock, and access functions
 *
 * Lock काष्ठाure: get sp_unit_lock क्रम पढ़ोing whenever we need to
 * examine the SP list.
 */
अटल DEFINE_RWLOCK(sp_unit_lock);
अटल LIST_HEAD(sp_units);

/* Ever-increasing value to produce unique unit numbers */
अटल atomic_t sp_ordinal;

अटल व्योम sp_add_device(काष्ठा sp_device *sp)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&sp_unit_lock, flags);

	list_add_tail(&sp->entry, &sp_units);

	ग_लिखो_unlock_irqrestore(&sp_unit_lock, flags);
पूर्ण

अटल व्योम sp_del_device(काष्ठा sp_device *sp)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&sp_unit_lock, flags);

	list_del(&sp->entry);

	ग_लिखो_unlock_irqrestore(&sp_unit_lock, flags);
पूर्ण

अटल irqवापस_t sp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sp_device *sp = data;

	अगर (sp->ccp_irq_handler)
		sp->ccp_irq_handler(irq, sp->ccp_irq_data);

	अगर (sp->psp_irq_handler)
		sp->psp_irq_handler(irq, sp->psp_irq_data);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक sp_request_ccp_irq(काष्ठा sp_device *sp, irq_handler_t handler,
		       स्थिर अक्षर *name, व्योम *data)
अणु
	पूर्णांक ret;

	अगर ((sp->psp_irq == sp->ccp_irq) && sp->dev_vdata->psp_vdata) अणु
		/* Need a common routine to manage all पूर्णांकerrupts */
		sp->ccp_irq_data = data;
		sp->ccp_irq_handler = handler;

		अगर (!sp->irq_रेजिस्टरed) अणु
			ret = request_irq(sp->ccp_irq, sp_irq_handler, 0,
					  sp->name, sp);
			अगर (ret)
				वापस ret;

			sp->irq_रेजिस्टरed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Each sub-device can manage it's own पूर्णांकerrupt */
		ret = request_irq(sp->ccp_irq, handler, 0, name, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sp_request_psp_irq(काष्ठा sp_device *sp, irq_handler_t handler,
		       स्थिर अक्षर *name, व्योम *data)
अणु
	पूर्णांक ret;

	अगर ((sp->psp_irq == sp->ccp_irq) && sp->dev_vdata->ccp_vdata) अणु
		/* Need a common routine to manage all पूर्णांकerrupts */
		sp->psp_irq_data = data;
		sp->psp_irq_handler = handler;

		अगर (!sp->irq_रेजिस्टरed) अणु
			ret = request_irq(sp->psp_irq, sp_irq_handler, 0,
					  sp->name, sp);
			अगर (ret)
				वापस ret;

			sp->irq_रेजिस्टरed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Each sub-device can manage it's own पूर्णांकerrupt */
		ret = request_irq(sp->psp_irq, handler, 0, name, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sp_मुक्त_ccp_irq(काष्ठा sp_device *sp, व्योम *data)
अणु
	अगर ((sp->psp_irq == sp->ccp_irq) && sp->dev_vdata->psp_vdata) अणु
		/* Using common routine to manage all पूर्णांकerrupts */
		अगर (!sp->psp_irq_handler) अणु
			/* Nothing अन्यथा using it, so मुक्त it */
			मुक्त_irq(sp->ccp_irq, sp);

			sp->irq_रेजिस्टरed = false;
		पूर्ण

		sp->ccp_irq_handler = शून्य;
		sp->ccp_irq_data = शून्य;
	पूर्ण अन्यथा अणु
		/* Each sub-device can manage it's own पूर्णांकerrupt */
		मुक्त_irq(sp->ccp_irq, data);
	पूर्ण
पूर्ण

व्योम sp_मुक्त_psp_irq(काष्ठा sp_device *sp, व्योम *data)
अणु
	अगर ((sp->psp_irq == sp->ccp_irq) && sp->dev_vdata->ccp_vdata) अणु
		/* Using common routine to manage all पूर्णांकerrupts */
		अगर (!sp->ccp_irq_handler) अणु
			/* Nothing अन्यथा using it, so मुक्त it */
			मुक्त_irq(sp->psp_irq, sp);

			sp->irq_रेजिस्टरed = false;
		पूर्ण

		sp->psp_irq_handler = शून्य;
		sp->psp_irq_data = शून्य;
	पूर्ण अन्यथा अणु
		/* Each sub-device can manage it's own पूर्णांकerrupt */
		मुक्त_irq(sp->psp_irq, data);
	पूर्ण
पूर्ण

/**
 * sp_alloc_काष्ठा - allocate and initialize the sp_device काष्ठा
 *
 * @dev: device काष्ठा of the SP
 */
काष्ठा sp_device *sp_alloc_काष्ठा(काष्ठा device *dev)
अणु
	काष्ठा sp_device *sp;

	sp = devm_kzalloc(dev, माप(*sp), GFP_KERNEL);
	अगर (!sp)
		वापस शून्य;

	sp->dev = dev;
	sp->ord = atomic_inc_वापस(&sp_ordinal);
	snम_लिखो(sp->name, SP_MAX_NAME_LEN, "sp-%u", sp->ord);

	वापस sp;
पूर्ण

पूर्णांक sp_init(काष्ठा sp_device *sp)
अणु
	sp_add_device(sp);

	अगर (sp->dev_vdata->ccp_vdata)
		ccp_dev_init(sp);

	अगर (sp->dev_vdata->psp_vdata)
		psp_dev_init(sp);
	वापस 0;
पूर्ण

व्योम sp_destroy(काष्ठा sp_device *sp)
अणु
	अगर (sp->dev_vdata->ccp_vdata)
		ccp_dev_destroy(sp);

	अगर (sp->dev_vdata->psp_vdata)
		psp_dev_destroy(sp);

	sp_del_device(sp);
पूर्ण

पूर्णांक sp_suspend(काष्ठा sp_device *sp)
अणु
	अगर (sp->dev_vdata->ccp_vdata) अणु
		ccp_dev_suspend(sp);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sp_resume(काष्ठा sp_device *sp)
अणु
	अगर (sp->dev_vdata->ccp_vdata) अणु
		ccp_dev_resume(sp);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sp_device *sp_get_psp_master_device(व्योम)
अणु
	काष्ठा sp_device *i, *ret = शून्य;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&sp_unit_lock, flags);
	अगर (list_empty(&sp_units))
		जाओ unlock;

	list_क्रम_each_entry(i, &sp_units, entry) अणु
		अगर (i->psp_data && i->get_psp_master_device) अणु
			ret = i->get_psp_master_device();
			अवरोध;
		पूर्ण
	पूर्ण

unlock:
	ग_लिखो_unlock_irqrestore(&sp_unit_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक __init sp_mod_init(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	पूर्णांक ret;

	ret = sp_pci_init();
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
	psp_pci_init();
#पूर्ण_अगर

	वापस 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64
	पूर्णांक ret;

	ret = sp_platक्रमm_init();
	अगर (ret)
		वापस ret;

	वापस 0;
#पूर्ण_अगर

	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sp_mod_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_X86

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
	psp_pci_निकास();
#पूर्ण_अगर

	sp_pci_निकास();
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64
	sp_platक्रमm_निकास();
#पूर्ण_अगर
पूर्ण

module_init(sp_mod_init);
module_निकास(sp_mod_निकास);
