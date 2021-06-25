<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_SMP2P_H_
#घोषणा _IPA_SMP2P_H_

#समावेश <linux/types.h>

काष्ठा ipa;

/**
 * ipa_smp2p_init() - Initialize the IPA SMP2P subप्रणाली
 * @ipa:	IPA poपूर्णांकer
 * @modem_init:	Whether the modem is responsible क्रम GSI initialization
 *
 * Return:	0 अगर successful, or a negative error code
 *
 */
पूर्णांक ipa_smp2p_init(काष्ठा ipa *ipa, bool modem_init);

/**
 * ipa_smp2p_निकास() - Inverse of ipa_smp2p_init()
 * @ipa:	IPA poपूर्णांकer
 */
व्योम ipa_smp2p_निकास(काष्ठा ipa *ipa);

/**
 * ipa_smp2p_disable() - Prevent "ipa-setup-ready" पूर्णांकerrupt handling
 * @ipa:	IPA poपूर्णांकer
 *
 * Prevent handling of the "setup ready" पूर्णांकerrupt from the modem.
 * This is used beक्रमe initiating shutकरोwn of the driver.
 */
व्योम ipa_smp2p_disable(काष्ठा ipa *ipa);

/**
 * ipa_smp2p_notअगरy_reset() - Reset modem notअगरication state
 * @ipa:	IPA poपूर्णांकer
 *
 * If the modem crashes it queries the IPA घड़ी state.  In cleaning
 * up after such a crash this is used to reset some state मुख्यtained
 * क्रम managing this notअगरication.
 */
व्योम ipa_smp2p_notअगरy_reset(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_SMP2P_H_ */
