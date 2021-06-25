<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_UC_H_
#घोषणा _IPA_UC_H_

काष्ठा ipa;

/**
 * ipa_uc_setup() - set up the IPA microcontroller subप्रणाली
 * @ipa:	IPA poपूर्णांकer
 */
व्योम ipa_uc_setup(काष्ठा ipa *ipa);

/**
 * ipa_uc_tearकरोwn() - inverse of ipa_uc_setup()
 * @ipa:	IPA poपूर्णांकer
 */
व्योम ipa_uc_tearकरोwn(काष्ठा ipa *ipa);

/**
 * ipa_uc_panic_notअगरier()
 * @ipa:	IPA poपूर्णांकer
 *
 * Notअगरier function called when the प्रणाली crashes, to inक्रमm the
 * microcontroller of the event.
 */
व्योम ipa_uc_panic_notअगरier(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_UC_H_ */
