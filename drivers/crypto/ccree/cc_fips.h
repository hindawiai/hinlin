<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#अगर_अघोषित __CC_FIPS_H__
#घोषणा __CC_FIPS_H__

#अगर_घोषित CONFIG_CRYPTO_FIPS

क्रमागत cc_fips_status अणु
	CC_FIPS_SYNC_MODULE_OK = 0x0,
	CC_FIPS_SYNC_MODULE_ERROR = 0x1,
	CC_FIPS_SYNC_REE_STATUS = 0x4,
	CC_FIPS_SYNC_TEE_STATUS = 0x8,
	CC_FIPS_SYNC_STATUS_RESERVE32B = S32_MAX
पूर्ण;

पूर्णांक cc_fips_init(काष्ठा cc_drvdata *p_drvdata);
व्योम cc_fips_fini(काष्ठा cc_drvdata *drvdata);
व्योम fips_handler(काष्ठा cc_drvdata *drvdata);
व्योम cc_set_ree_fips_status(काष्ठा cc_drvdata *drvdata, bool ok);
व्योम cc_tee_handle_fips_error(काष्ठा cc_drvdata *p_drvdata);

#अन्यथा  /* CONFIG_CRYPTO_FIPS */

अटल अंतरभूत पूर्णांक cc_fips_init(काष्ठा cc_drvdata *p_drvdata)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cc_fips_fini(काष्ठा cc_drvdata *drvdata) अणुपूर्ण
अटल अंतरभूत व्योम cc_set_ree_fips_status(काष्ठा cc_drvdata *drvdata,
					  bool ok) अणुपूर्ण
अटल अंतरभूत व्योम fips_handler(काष्ठा cc_drvdata *drvdata) अणुपूर्ण
अटल अंतरभूत व्योम cc_tee_handle_fips_error(काष्ठा cc_drvdata *p_drvdata) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_FIPS */

#पूर्ण_अगर  /*__CC_FIPS_H__*/
