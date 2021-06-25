<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित _LINUX_ASYM_TPM_SUBTYPE_H
#घोषणा _LINUX_ASYM_TPM_SUBTYPE_H

#समावेश <linux/keyctl.h>

काष्ठा tpm_key अणु
	व्योम *blob;
	u32 blob_len;
	uपूर्णांक16_t key_len; /* Size in bits of the key */
	स्थिर व्योम *pub_key; /* poपूर्णांकer inside blob to the खुला key bytes */
	uपूर्णांक16_t pub_key_len; /* length of the खुला key */
पूर्ण;

काष्ठा tpm_key *tpm_key_create(स्थिर व्योम *blob, uपूर्णांक32_t blob_len);

बाह्य काष्ठा asymmetric_key_subtype asym_tpm_subtype;

#पूर्ण_अगर /* _LINUX_ASYM_TPM_SUBTYPE_H */
