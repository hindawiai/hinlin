<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_INTERRUPT_H_
#घोषणा _IPA_INTERRUPT_H_

#समावेश <linux/types.h>
#समावेश <linux/bits.h>

काष्ठा ipa;
काष्ठा ipa_पूर्णांकerrupt;

/**
 * प्रकार ipa_irq_handler_t - IPA पूर्णांकerrupt handler function type
 * @ipa:	IPA poपूर्णांकer
 * @irq_id:	पूर्णांकerrupt type
 *
 * Callback function रेजिस्टरed by ipa_पूर्णांकerrupt_add() to handle a specअगरic
 * IPA पूर्णांकerrupt type
 */
प्रकार व्योम (*ipa_irq_handler_t)(काष्ठा ipa *ipa, क्रमागत ipa_irq_id irq_id);

/**
 * ipa_पूर्णांकerrupt_add() - Register a handler क्रम an IPA पूर्णांकerrupt type
 * @पूर्णांकerrupt:	IPA पूर्णांकerrupt काष्ठाure
 * @irq_id:	IPA पूर्णांकerrupt type
 * @handler:	Handler function क्रम the पूर्णांकerrupt
 *
 * Add a handler क्रम an IPA पूर्णांकerrupt and enable it.  IPA पूर्णांकerrupt
 * handlers are run in thपढ़ोed पूर्णांकerrupt context, so are allowed to
 * block.
 */
व्योम ipa_पूर्णांकerrupt_add(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt, क्रमागत ipa_irq_id irq_id,
		       ipa_irq_handler_t handler);

/**
 * ipa_पूर्णांकerrupt_हटाओ() - Remove the handler क्रम an IPA पूर्णांकerrupt type
 * @पूर्णांकerrupt:	IPA पूर्णांकerrupt काष्ठाure
 * @irq_id:	IPA पूर्णांकerrupt type
 *
 * Remove an IPA पूर्णांकerrupt handler and disable it.
 */
व्योम ipa_पूर्णांकerrupt_हटाओ(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt,
			  क्रमागत ipa_irq_id irq_id);

/**
 * ipa_पूर्णांकerrupt_suspend_enable - Enable TX_SUSPEND क्रम an endpoपूर्णांक
 * @पूर्णांकerrupt:		IPA पूर्णांकerrupt काष्ठाure
 * @endpoपूर्णांक_id:	Endpoपूर्णांक whose पूर्णांकerrupt should be enabled
 *
 * Note:  The "TX" in the name is from the perspective of the IPA hardware.
 * A TX_SUSPEND पूर्णांकerrupt arrives on an AP RX enpoपूर्णांक when packet data can't
 * be delivered to the endpoपूर्णांक because it is suspended (or its underlying
 * channel is stopped).
 */
व्योम ipa_पूर्णांकerrupt_suspend_enable(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt,
				  u32 endpoपूर्णांक_id);

/**
 * ipa_पूर्णांकerrupt_suspend_disable - Disable TX_SUSPEND क्रम an endpoपूर्णांक
 * @पूर्णांकerrupt:		IPA पूर्णांकerrupt काष्ठाure
 * @endpoपूर्णांक_id:	Endpoपूर्णांक whose पूर्णांकerrupt should be disabled
 */
व्योम ipa_पूर्णांकerrupt_suspend_disable(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt,
				   u32 endpoपूर्णांक_id);

/**
 * ipa_पूर्णांकerrupt_suspend_clear_all - clear all suspend पूर्णांकerrupts
 * @पूर्णांकerrupt:	IPA पूर्णांकerrupt काष्ठाure
 *
 * Clear the TX_SUSPEND पूर्णांकerrupt क्रम all endpoपूर्णांकs that संकेतed it.
 */
व्योम ipa_पूर्णांकerrupt_suspend_clear_all(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt);

/**
 * ipa_पूर्णांकerrupt_simulate_suspend() - Simulate TX_SUSPEND IPA पूर्णांकerrupt
 * @पूर्णांकerrupt:	IPA पूर्णांकerrupt काष्ठाure
 *
 * This calls the TX_SUSPEND पूर्णांकerrupt handler, as अगर such an पूर्णांकerrupt
 * had been संकेतed.  This is needed to work around a hardware quirk
 * that occurs अगर aggregation is active on an endpoपूर्णांक when its underlying
 * channel is suspended.
 */
व्योम ipa_पूर्णांकerrupt_simulate_suspend(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt);

/**
 * ipa_पूर्णांकerrupt_setup() - Set up the IPA पूर्णांकerrupt framework
 * @ipa:	IPA poपूर्णांकer
 *
 * Return:	Poपूर्णांकer to IPA SMP2P info, or a poपूर्णांकer-coded error
 */
काष्ठा ipa_पूर्णांकerrupt *ipa_पूर्णांकerrupt_setup(काष्ठा ipa *ipa);

/**
 * ipa_पूर्णांकerrupt_tearकरोwn() - Tear करोwn the IPA पूर्णांकerrupt framework
 * @पूर्णांकerrupt:	IPA पूर्णांकerrupt काष्ठाure
 */
व्योम ipa_पूर्णांकerrupt_tearकरोwn(काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt);

#पूर्ण_अगर /* _IPA_INTERRUPT_H_ */
