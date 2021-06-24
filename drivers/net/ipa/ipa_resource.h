<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */
#अगर_अघोषित _IPA_RESOURCE_H_
#घोषणा _IPA_RESOURCE_H_

काष्ठा ipa;
काष्ठा ipa_resource_data;

/**
 * ipa_resource_config() - Configure resources
 * @ipa:	IPA poपूर्णांकer
 * @data:	IPA resource configuration data
 *
 * There is no need क्रम a matching ipa_resource_deconfig() function.
 *
 * Return:	true अगर all regions are valid, false otherwise
 */
पूर्णांक ipa_resource_config(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_resource_data *data);

#पूर्ण_अगर /* _IPA_RESOURCE_H_ */
