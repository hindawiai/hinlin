<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_CLOCK_H_
#घोषणा _IPA_CLOCK_H_

काष्ठा device;

काष्ठा ipa;
काष्ठा ipa_घड़ी_data;

/**
 * ipa_घड़ी_rate() - Return the current IPA core घड़ी rate
 * @ipa:	IPA काष्ठाure
 *
 * Return: The current घड़ी rate (in Hz), or 0.
 */
u32 ipa_घड़ी_rate(काष्ठा ipa *ipa);

/**
 * ipa_घड़ी_init() - Initialize IPA घड़ीing
 * @dev:	IPA device
 * @data:	Clock configuration data
 *
 * Return:	A poपूर्णांकer to an ipa_घड़ी काष्ठाure, or a poपूर्णांकer-coded error
 */
काष्ठा ipa_घड़ी *ipa_घड़ी_init(काष्ठा device *dev,
				 स्थिर काष्ठा ipa_घड़ी_data *data);

/**
 * ipa_घड़ी_निकास() - Inverse of ipa_घड़ी_init()
 * @घड़ी:	IPA घड़ी poपूर्णांकer
 */
व्योम ipa_घड़ी_निकास(काष्ठा ipa_घड़ी *घड़ी);

/**
 * ipa_घड़ी_get() - Get an IPA घड़ी reference
 * @ipa:	IPA poपूर्णांकer
 *
 * This call blocks अगर this is the first reference.
 */
व्योम ipa_घड़ी_get(काष्ठा ipa *ipa);

/**
 * ipa_घड़ी_get_additional() - Get an IPA घड़ी reference अगर not first
 * @ipa:	IPA poपूर्णांकer
 *
 * This वापसs immediately, and only takes a reference अगर not the first
 */
bool ipa_घड़ी_get_additional(काष्ठा ipa *ipa);

/**
 * ipa_घड़ी_put() - Drop an IPA घड़ी reference
 * @ipa:	IPA poपूर्णांकer
 *
 * This drops a घड़ी reference.  If the last reference is being dropped,
 * the घड़ी is stopped and RX endpoपूर्णांकs are suspended.  This call will
 * not block unless the last reference is dropped.
 */
व्योम ipa_घड़ी_put(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_CLOCK_H_ */
