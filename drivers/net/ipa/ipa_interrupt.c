<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2014-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */

/* DOC: IPA Interrupts
 *
 * The IPA has an पूर्णांकerrupt line distinct from the पूर्णांकerrupt used by the GSI
 * code.  Whereas GSI पूर्णांकerrupts are generally related to channel events (like
 * transfer completions), IPA पूर्णांकerrupts are related to other events related
 * to the IPA.  Some of the IPA पूर्णांकerrupts come from a microcontroller
 * embedded in the IPA.  Each IPA पूर्णांकerrupt type can be both masked and
 * acknowledged independent of the others.
 *
 * Two of the IPA पूर्णांकerrupts are initiated by the microcontroller.  A third
 * can be generated to संकेत the need क्रम a wakeup/resume when an IPA
 * endpoपूर्णांक has been suspended.  There are other IPA events, but at this
 * समय only these three are supported.
 */

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "ipa.h"
#समावेश "ipa_clock.h"
#समावेश "ipa_reg.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_interrupt.h"

/**
 * काष्ठा ipa_पूर्णांकerrupt - IPA पूर्णांकerrupt inक्रमmation
 * @ipa:		IPA poपूर्णांकer
 * @irq:		Linux IRQ number used क्रम IPA पूर्णांकerrupts
 * @enabled:		Mask indicating which पूर्णांकerrupts are enabled
 * @handler:		Array of handlers indexed by IPA पूर्णांकerrupt ID
 */
काष्ठा ipa_पूर्णांकerrupt अणु
	काष्ठा ipa *ipa;
	u32 irq;
	u32 enabled;
	ipa_irq_handler_t handler[IPA_IRQ_COUNT];
पूर्ण;

/* Returns true अगर the पूर्णांकerrupt type is associated with the microcontroller */
अटल bool ipa_पूर्णांकerrupt_uc(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, u32 irq_id)
अणु
	वापस irq_id == IPA_IRQ_UC_0 || irq_id == IPA_IRQ_UC_1;
पूर्ण

/* Process a particular पूर्णांकerrupt type that has been received */
अटल व्योम ipa_पूर्णांकerrupt_process(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, u32 irq_id)
अणु
	bool uc_irq = ipa_पूर्णांकerrupt_uc(पूर्णांकerrupt, irq_id);
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 mask = BIT(irq_id);
	u32 offset;

	/* For microcontroller पूर्णांकerrupts, clear the पूर्णांकerrupt right away,
	 * "to avoid clearing unhandled interrupts."
	 */
	offset = ipa_reg_irq_clr_offset(ipa->version);
	अगर (uc_irq)
		ioग_लिखो32(mask, ipa->reg_virt + offset);

	अगर (irq_id < IPA_IRQ_COUNT && पूर्णांकerrupt->handler[irq_id])
		पूर्णांकerrupt->handler[irq_id](पूर्णांकerrupt->ipa, irq_id);

	/* Clearing the SUSPEND_TX पूर्णांकerrupt also clears the रेजिस्टर
	 * that tells us which suspended endpoपूर्णांक(s) caused the पूर्णांकerrupt,
	 * so defer clearing until after the handler has been called.
	 */
	अगर (!uc_irq)
		ioग_लिखो32(mask, ipa->reg_virt + offset);
पूर्ण

/* Process all IPA पूर्णांकerrupt types that have been संकेतed */
अटल व्योम ipa_पूर्णांकerrupt_process_all(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt)
अणु
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 enabled = पूर्णांकerrupt->enabled;
	u32 offset;
	u32 mask;

	/* The status रेजिस्टर indicates which conditions are present,
	 * including conditions whose पूर्णांकerrupt is not enabled.  Handle
	 * only the enabled ones.
	 */
	offset = ipa_reg_irq_stts_offset(ipa->version);
	mask = ioपढ़ो32(ipa->reg_virt + offset);
	जबतक ((mask &= enabled)) अणु
		करो अणु
			u32 irq_id = __ffs(mask);

			mask ^= BIT(irq_id);

			ipa_पूर्णांकerrupt_process(पूर्णांकerrupt, irq_id);
		पूर्ण जबतक (mask);
		mask = ioपढ़ो32(ipa->reg_virt + offset);
	पूर्ण
पूर्ण

/* Thपढ़ोed part of the IPA IRQ handler */
अटल irqवापस_t ipa_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt = dev_id;

	ipa_घड़ी_get(पूर्णांकerrupt->ipa);

	ipa_पूर्णांकerrupt_process_all(पूर्णांकerrupt);

	ipa_घड़ी_put(पूर्णांकerrupt->ipa);

	वापस IRQ_HANDLED;
पूर्ण

/* Hard part (i.e., "real" IRQ handler) of the IRQ handler */
अटल irqवापस_t ipa_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt = dev_id;
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 offset;
	u32 mask;

	offset = ipa_reg_irq_stts_offset(ipa->version);
	mask = ioपढ़ो32(ipa->reg_virt + offset);
	अगर (mask & पूर्णांकerrupt->enabled)
		वापस IRQ_WAKE_THREAD;

	/* Nothing in the mask was supposed to cause an पूर्णांकerrupt */
	offset = ipa_reg_irq_clr_offset(ipa->version);
	ioग_लिखो32(mask, ipa->reg_virt + offset);

	dev_err(&ipa->pdev->dev, "%s: unexpected interrupt, mask 0x%08x\n",
		__func__, mask);

	वापस IRQ_HANDLED;
पूर्ण

/* Common function used to enable/disable TX_SUSPEND क्रम an endpoपूर्णांक */
अटल व्योम ipa_पूर्णांकerrupt_suspend_control(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt,
					  u32 endpoपूर्णांक_id, bool enable)
अणु
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 mask = BIT(endpoपूर्णांक_id);
	u32 offset;
	u32 val;

	/* निश्चित(mask & ipa->available); */

	/* IPA version 3.0 करोes not support TX_SUSPEND पूर्णांकerrupt control */
	अगर (ipa->version == IPA_VERSION_3_0)
		वापस;

	offset = ipa_reg_irq_suspend_en_offset(ipa->version);
	val = ioपढ़ो32(ipa->reg_virt + offset);
	अगर (enable)
		val |= mask;
	अन्यथा
		val &= ~mask;
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

/* Enable TX_SUSPEND क्रम an endpoपूर्णांक */
व्योम
ipa_पूर्णांकerrupt_suspend_enable(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, u32 endpoपूर्णांक_id)
अणु
	ipa_पूर्णांकerrupt_suspend_control(पूर्णांकerrupt, endpoपूर्णांक_id, true);
पूर्ण

/* Disable TX_SUSPEND क्रम an endpoपूर्णांक */
व्योम
ipa_पूर्णांकerrupt_suspend_disable(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, u32 endpoपूर्णांक_id)
अणु
	ipa_पूर्णांकerrupt_suspend_control(पूर्णांकerrupt, endpoपूर्णांक_id, false);
पूर्ण

/* Clear the suspend पूर्णांकerrupt क्रम all endpoपूर्णांकs that संकेतed it */
व्योम ipa_पूर्णांकerrupt_suspend_clear_all(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt)
अणु
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 offset;
	u32 val;

	offset = ipa_reg_irq_suspend_info_offset(ipa->version);
	val = ioपढ़ो32(ipa->reg_virt + offset);

	/* SUSPEND पूर्णांकerrupt status isn't cleared on IPA version 3.0 */
	अगर (ipa->version == IPA_VERSION_3_0)
		वापस;

	offset = ipa_reg_irq_suspend_clr_offset(ipa->version);
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

/* Simulate arrival of an IPA TX_SUSPEND पूर्णांकerrupt */
व्योम ipa_पूर्णांकerrupt_simulate_suspend(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt)
अणु
	ipa_पूर्णांकerrupt_process(पूर्णांकerrupt, IPA_IRQ_TX_SUSPEND);
पूर्ण

/* Add a handler क्रम an IPA पूर्णांकerrupt */
व्योम ipa_पूर्णांकerrupt_add(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt,
		       क्रमागत ipa_irq_id ipa_irq, ipa_irq_handler_t handler)
अणु
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 offset;

	/* निश्चित(ipa_irq < IPA_IRQ_COUNT); */
	पूर्णांकerrupt->handler[ipa_irq] = handler;

	/* Update the IPA पूर्णांकerrupt mask to enable it */
	पूर्णांकerrupt->enabled |= BIT(ipa_irq);
	offset = ipa_reg_irq_en_offset(ipa->version);
	ioग_लिखो32(पूर्णांकerrupt->enabled, ipa->reg_virt + offset);
पूर्ण

/* Remove the handler क्रम an IPA पूर्णांकerrupt type */
व्योम
ipa_पूर्णांकerrupt_हटाओ(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, क्रमागत ipa_irq_id ipa_irq)
अणु
	काष्ठा ipa *ipa = पूर्णांकerrupt->ipa;
	u32 offset;

	/* निश्चित(ipa_irq < IPA_IRQ_COUNT); */
	/* Update the IPA पूर्णांकerrupt mask to disable it */
	पूर्णांकerrupt->enabled &= ~BIT(ipa_irq);
	offset = ipa_reg_irq_en_offset(ipa->version);
	ioग_लिखो32(पूर्णांकerrupt->enabled, ipa->reg_virt + offset);

	पूर्णांकerrupt->handler[ipa_irq] = शून्य;
पूर्ण

/* Set up the IPA पूर्णांकerrupt framework */
काष्ठा ipa_पूर्णांकerrupt *ipa_पूर्णांकerrupt_setup(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt;
	अचिन्हित पूर्णांक irq;
	u32 offset;
	पूर्णांक ret;

	ret = platक्रमm_get_irq_byname(ipa->pdev, "ipa");
	अगर (ret <= 0) अणु
		dev_err(dev, "DT error %d getting \"ipa\" IRQ property\n",
			ret);
		वापस ERR_PTR(ret ? : -EINVAL);
	पूर्ण
	irq = ret;

	पूर्णांकerrupt = kzalloc(माप(*पूर्णांकerrupt), GFP_KERNEL);
	अगर (!पूर्णांकerrupt)
		वापस ERR_PTR(-ENOMEM);
	पूर्णांकerrupt->ipa = ipa;
	पूर्णांकerrupt->irq = irq;

	/* Start with all IPA पूर्णांकerrupts disabled */
	offset = ipa_reg_irq_en_offset(ipa->version);
	ioग_लिखो32(0, ipa->reg_virt + offset);

	ret = request_thपढ़ोed_irq(irq, ipa_isr, ipa_isr_thपढ़ो, IRQF_ONESHOT,
				   "ipa", पूर्णांकerrupt);
	अगर (ret) अणु
		dev_err(dev, "error %d requesting \"ipa\" IRQ\n", ret);
		जाओ err_kमुक्त;
	पूर्ण

	ret = enable_irq_wake(irq);
	अगर (ret) अणु
		dev_err(dev, "error %d enabling wakeup for \"ipa\" IRQ\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	वापस पूर्णांकerrupt;

err_मुक्त_irq:
	मुक्त_irq(पूर्णांकerrupt->irq, पूर्णांकerrupt);
err_kमुक्त:
	kमुक्त(पूर्णांकerrupt);

	वापस ERR_PTR(ret);
पूर्ण

/* Tear करोwn the IPA पूर्णांकerrupt framework */
व्योम ipa_पूर्णांकerrupt_tearकरोwn(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt)
अणु
	काष्ठा device *dev = &पूर्णांकerrupt->ipa->pdev->dev;
	पूर्णांक ret;

	ret = disable_irq_wake(पूर्णांकerrupt->irq);
	अगर (ret)
		dev_err(dev, "error %d disabling \"ipa\" IRQ wakeup\n", ret);
	मुक्त_irq(पूर्णांकerrupt->irq, पूर्णांकerrupt);
	kमुक्त(पूर्णांकerrupt);
पूर्ण
