<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */
#अगर_अघोषित _IPA_TABLE_H_
#घोषणा _IPA_TABLE_H_

#समावेश <linux/types.h>

काष्ठा ipa;

/* The maximum number of filter table entries (IPv4, IPv6; hashed or not) */
#घोषणा IPA_FILTER_COUNT_MAX	14

/* The maximum number of route table entries (IPv4, IPv6; hashed or not) */
#घोषणा IPA_ROUTE_COUNT_MAX	15

#अगर_घोषित IPA_VALIDATE

/**
 * ipa_table_valid() - Validate route and filter table memory regions
 * @ipa:	IPA poपूर्णांकer
 *
 * Return:	true अगर all regions are valid, false otherwise
 */
bool ipa_table_valid(काष्ठा ipa *ipa);

/**
 * ipa_filter_map_valid() - Validate a filter table endpoपूर्णांक biपंचांगap
 * @ipa:	IPA poपूर्णांकer
 * @filter_mask: Filter table endpoपूर्णांक biपंचांगap to check
 *
 * Return:	true अगर all regions are valid, false otherwise
 */
bool ipa_filter_map_valid(काष्ठा ipa *ipa, u32 filter_mask);

#अन्यथा /* !IPA_VALIDATE */

अटल अंतरभूत bool ipa_table_valid(काष्ठा ipa *ipa)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool ipa_filter_map_valid(काष्ठा ipa *ipa, u32 filter_mask)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* !IPA_VALIDATE */

/**
 * ipa_table_hash_support() - Return true अगर hashed tables are supported
 * @ipa:	IPA poपूर्णांकer
 */
अटल अंतरभूत bool ipa_table_hash_support(काष्ठा ipa *ipa)
अणु
	वापस ipa->version != IPA_VERSION_4_2;
पूर्ण

/**
 * ipa_table_reset() - Reset filter and route tables entries to "none"
 * @ipa:	IPA poपूर्णांकer
 * @modem:	Whether to reset modem or AP entries
 */
व्योम ipa_table_reset(काष्ठा ipa *ipa, bool modem);

/**
 * ipa_table_hash_flush() - Synchronize hashed filter and route updates
 * @ipa:	IPA poपूर्णांकer
 */
पूर्णांक ipa_table_hash_flush(काष्ठा ipa *ipa);

/**
 * ipa_table_setup() - Set up filter and route tables
 * @ipa:	IPA poपूर्णांकer
 *
 * There is no need क्रम a matching ipa_table_tearकरोwn() function.
 */
पूर्णांक ipa_table_setup(काष्ठा ipa *ipa);

/**
 * ipa_table_config() - Configure filter and route tables
 * @ipa:	IPA poपूर्णांकer
 *
 * There is no need क्रम a matching ipa_table_deconfig() function.
 */
व्योम ipa_table_config(काष्ठा ipa *ipa);

/**
 * ipa_table_init() - Do early initialization of filter and route tables
 * @ipa:	IPA poपूर्णांकer
 */
पूर्णांक ipa_table_init(काष्ठा ipa *ipa);

/**
 * ipa_table_निकास() - Inverse of ipa_table_init()
 * @ipa:	IPA poपूर्णांकer
 */
व्योम ipa_table_निकास(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_TABLE_H_ */
