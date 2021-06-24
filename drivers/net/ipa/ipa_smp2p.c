<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>

#समावेश "ipa_smp2p.h"
#समावेश "ipa.h"
#समावेश "ipa_uc.h"
#समावेश "ipa_clock.h"

/**
 * DOC: IPA SMP2P communication with the modem
 *
 * SMP2P is a primitive communication mechanism available between the AP and
 * the modem.  The IPA driver uses this क्रम two purposes:  to enable the modem
 * to state that the GSI hardware is पढ़ोy to use; and to communicate the
 * state of the IPA घड़ी in the event of a crash.
 *
 * GSI needs to have early initialization completed beक्रमe it can be used.
 * This initialization is करोne either by Trust Zone or by the modem.  In the
 * latter हाल, the modem uses an SMP2P पूर्णांकerrupt to tell the AP IPA driver
 * when the GSI is पढ़ोy to use.
 *
 * The modem is also able to inquire about the current state of the IPA
 * घड़ी by trigging another SMP2P पूर्णांकerrupt to the AP.  We communicate
 * whether the घड़ी is enabled using two SMP2P state bits--one to
 * indicate the घड़ी state (on or off), and a second to indicate the
 * घड़ी state bit is valid.  The modem will poll the valid bit until it
 * is set, and at that समय records whether the AP has the IPA घड़ी enabled.
 *
 * Finally, अगर the AP kernel panics, we update the SMP2P state bits even अगर
 * we never receive an पूर्णांकerrupt from the modem requesting this.
 */

/**
 * काष्ठा ipa_smp2p - IPA SMP2P inक्रमmation
 * @ipa:		IPA poपूर्णांकer
 * @valid_state:	SMEM state indicating enabled state is valid
 * @enabled_state:	SMEM state to indicate घड़ी is enabled
 * @valid_bit:		Valid bit in 32-bit SMEM state mask
 * @enabled_bit:	Enabled bit in 32-bit SMEM state mask
 * @enabled_bit:	Enabled bit in 32-bit SMEM state mask
 * @घड़ी_query_irq:	IPA पूर्णांकerrupt triggered by modem क्रम घड़ी query
 * @setup_पढ़ोy_irq:	IPA पूर्णांकerrupt triggered by modem to संकेत GSI पढ़ोy
 * @घड़ी_on:		Whether IPA घड़ी is on
 * @notअगरied:		Whether modem has been notअगरied of घड़ी state
 * @disabled:		Whether setup पढ़ोy पूर्णांकerrupt handling is disabled
 * @mutex:		Mutex protecting पढ़ोy-पूर्णांकerrupt/shutकरोwn पूर्णांकerlock
 * @panic_notअगरier:	Panic notअगरier काष्ठाure
*/
काष्ठा ipa_smp2p अणु
	काष्ठा ipa *ipa;
	काष्ठा qcom_smem_state *valid_state;
	काष्ठा qcom_smem_state *enabled_state;
	u32 valid_bit;
	u32 enabled_bit;
	u32 घड़ी_query_irq;
	u32 setup_पढ़ोy_irq;
	bool घड़ी_on;
	bool notअगरied;
	bool disabled;
	काष्ठा mutex mutex;
	काष्ठा notअगरier_block panic_notअगरier;
पूर्ण;

/**
 * ipa_smp2p_notअगरy() - use SMP2P to tell modem about IPA घड़ी state
 * @smp2p:	SMP2P inक्रमmation
 *
 * This is called either when the modem has requested it (by triggering
 * the modem घड़ी query IPA पूर्णांकerrupt) or whenever the AP is shutting करोwn
 * (via a panic notअगरier).  It sets the two SMP2P state bits--one saying
 * whether the IPA घड़ी is running, and the other indicating the first bit
 * is valid.
 */
अटल व्योम ipa_smp2p_notअगरy(काष्ठा ipa_smp2p *smp2p)
अणु
	u32 value;
	u32 mask;

	अगर (smp2p->notअगरied)
		वापस;

	smp2p->घड़ी_on = ipa_घड़ी_get_additional(smp2p->ipa);

	/* Signal whether the घड़ी is enabled */
	mask = BIT(smp2p->enabled_bit);
	value = smp2p->घड़ी_on ? mask : 0;
	qcom_smem_state_update_bits(smp2p->enabled_state, mask, value);

	/* Now indicate that the enabled flag is valid */
	mask = BIT(smp2p->valid_bit);
	value = mask;
	qcom_smem_state_update_bits(smp2p->valid_state, mask, value);

	smp2p->notअगरied = true;
पूर्ण

/* Thपढ़ोed IRQ handler क्रम modem "ipa-clock-query" SMP2P पूर्णांकerrupt */
अटल irqवापस_t ipa_smp2p_modem_clk_query_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipa_smp2p *smp2p = dev_id;

	ipa_smp2p_notअगरy(smp2p);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ipa_smp2p_panic_notअगरier(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा ipa_smp2p *smp2p;

	smp2p = container_of(nb, काष्ठा ipa_smp2p, panic_notअगरier);

	ipa_smp2p_notअगरy(smp2p);

	अगर (smp2p->घड़ी_on)
		ipa_uc_panic_notअगरier(smp2p->ipa);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ipa_smp2p_panic_notअगरier_रेजिस्टर(काष्ठा ipa_smp2p *smp2p)
अणु
	/* IPA panic handler needs to run beक्रमe modem shuts करोwn */
	smp2p->panic_notअगरier.notअगरier_call = ipa_smp2p_panic_notअगरier;
	smp2p->panic_notअगरier.priority = पूर्णांक_उच्च;	/* Do it early */

	वापस atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					      &smp2p->panic_notअगरier);
पूर्ण

अटल व्योम ipa_smp2p_panic_notअगरier_unरेजिस्टर(काष्ठा ipa_smp2p *smp2p)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &smp2p->panic_notअगरier);
पूर्ण

/* Thपढ़ोed IRQ handler क्रम modem "ipa-setup-ready" SMP2P पूर्णांकerrupt */
अटल irqवापस_t ipa_smp2p_modem_setup_पढ़ोy_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipa_smp2p *smp2p = dev_id;

	mutex_lock(&smp2p->mutex);

	अगर (!smp2p->disabled) अणु
		पूर्णांक ret;

		ret = ipa_setup(smp2p->ipa);
		अगर (ret)
			dev_err(&smp2p->ipa->pdev->dev,
				"error %d from ipa_setup()\n", ret);
		smp2p->disabled = true;
	पूर्ण

	mutex_unlock(&smp2p->mutex);

	वापस IRQ_HANDLED;
पूर्ण

/* Initialize SMP2P पूर्णांकerrupts */
अटल पूर्णांक ipa_smp2p_irq_init(काष्ठा ipa_smp2p *smp2p, स्थिर अक्षर *name,
			      irq_handler_t handler)
अणु
	काष्ठा device *dev = &smp2p->ipa->pdev->dev;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	ret = platक्रमm_get_irq_byname(smp2p->ipa->pdev, name);
	अगर (ret <= 0) अणु
		dev_err(dev, "DT error %d getting \"%s\" IRQ property\n",
			ret, name);
		वापस ret ? : -EINVAL;
	पूर्ण
	irq = ret;

	ret = request_thपढ़ोed_irq(irq, शून्य, handler, 0, name, smp2p);
	अगर (ret) अणु
		dev_err(dev, "error %d requesting \"%s\" IRQ\n", ret, name);
		वापस ret;
	पूर्ण

	वापस irq;
पूर्ण

अटल व्योम ipa_smp2p_irq_निकास(काष्ठा ipa_smp2p *smp2p, u32 irq)
अणु
	मुक्त_irq(irq, smp2p);
पूर्ण

/* Drop the घड़ी reference अगर it was taken in ipa_smp2p_notअगरy() */
अटल व्योम ipa_smp2p_घड़ी_release(काष्ठा ipa *ipa)
अणु
	अगर (!ipa->smp2p->घड़ी_on)
		वापस;

	ipa_घड़ी_put(ipa);
	ipa->smp2p->घड़ी_on = false;
पूर्ण

/* Initialize the IPA SMP2P subप्रणाली */
पूर्णांक ipa_smp2p_init(काष्ठा ipa *ipa, bool modem_init)
अणु
	काष्ठा qcom_smem_state *enabled_state;
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा qcom_smem_state *valid_state;
	काष्ठा ipa_smp2p *smp2p;
	u32 enabled_bit;
	u32 valid_bit;
	पूर्णांक ret;

	valid_state = qcom_smem_state_get(dev, "ipa-clock-enabled-valid",
					  &valid_bit);
	अगर (IS_ERR(valid_state))
		वापस PTR_ERR(valid_state);
	अगर (valid_bit >= 32)		/* BITS_PER_U32 */
		वापस -EINVAL;

	enabled_state = qcom_smem_state_get(dev, "ipa-clock-enabled",
					    &enabled_bit);
	अगर (IS_ERR(enabled_state))
		वापस PTR_ERR(enabled_state);
	अगर (enabled_bit >= 32)		/* BITS_PER_U32 */
		वापस -EINVAL;

	smp2p = kzalloc(माप(*smp2p), GFP_KERNEL);
	अगर (!smp2p)
		वापस -ENOMEM;

	smp2p->ipa = ipa;

	/* These fields are needed by the घड़ी query पूर्णांकerrupt
	 * handler, so initialize them now.
	 */
	mutex_init(&smp2p->mutex);
	smp2p->valid_state = valid_state;
	smp2p->valid_bit = valid_bit;
	smp2p->enabled_state = enabled_state;
	smp2p->enabled_bit = enabled_bit;

	/* We have enough inक्रमmation saved to handle notअगरications */
	ipa->smp2p = smp2p;

	ret = ipa_smp2p_irq_init(smp2p, "ipa-clock-query",
				 ipa_smp2p_modem_clk_query_isr);
	अगर (ret < 0)
		जाओ err_null_smp2p;
	smp2p->घड़ी_query_irq = ret;

	ret = ipa_smp2p_panic_notअगरier_रेजिस्टर(smp2p);
	अगर (ret)
		जाओ err_irq_निकास;

	अगर (modem_init) अणु
		/* Result will be non-zero (negative क्रम error) */
		ret = ipa_smp2p_irq_init(smp2p, "ipa-setup-ready",
					 ipa_smp2p_modem_setup_पढ़ोy_isr);
		अगर (ret < 0)
			जाओ err_notअगरier_unरेजिस्टर;
		smp2p->setup_पढ़ोy_irq = ret;
	पूर्ण

	वापस 0;

err_notअगरier_unरेजिस्टर:
	ipa_smp2p_panic_notअगरier_unरेजिस्टर(smp2p);
err_irq_निकास:
	ipa_smp2p_irq_निकास(smp2p, smp2p->घड़ी_query_irq);
err_null_smp2p:
	ipa->smp2p = शून्य;
	mutex_destroy(&smp2p->mutex);
	kमुक्त(smp2p);

	वापस ret;
पूर्ण

व्योम ipa_smp2p_निकास(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_smp2p *smp2p = ipa->smp2p;

	अगर (smp2p->setup_पढ़ोy_irq)
		ipa_smp2p_irq_निकास(smp2p, smp2p->setup_पढ़ोy_irq);
	ipa_smp2p_panic_notअगरier_unरेजिस्टर(smp2p);
	ipa_smp2p_irq_निकास(smp2p, smp2p->घड़ी_query_irq);
	/* We won't get notअगरied any more; drop घड़ी reference (अगर any) */
	ipa_smp2p_घड़ी_release(ipa);
	ipa->smp2p = शून्य;
	mutex_destroy(&smp2p->mutex);
	kमुक्त(smp2p);
पूर्ण

व्योम ipa_smp2p_disable(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_smp2p *smp2p = ipa->smp2p;

	अगर (!smp2p->setup_पढ़ोy_irq)
		वापस;

	mutex_lock(&smp2p->mutex);

	smp2p->disabled = true;

	mutex_unlock(&smp2p->mutex);
पूर्ण

/* Reset state tracking whether we have notअगरied the modem */
व्योम ipa_smp2p_notअगरy_reset(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_smp2p *smp2p = ipa->smp2p;
	u32 mask;

	अगर (!smp2p->notअगरied)
		वापस;

	ipa_smp2p_घड़ी_release(ipa);

	/* Reset the घड़ी enabled valid flag */
	mask = BIT(smp2p->valid_bit);
	qcom_smem_state_update_bits(smp2p->valid_state, mask, 0);

	/* Mark the घड़ी disabled क्रम good measure... */
	mask = BIT(smp2p->enabled_bit);
	qcom_smem_state_update_bits(smp2p->enabled_state, mask, 0);

	smp2p->notअगरied = false;
पूर्ण
