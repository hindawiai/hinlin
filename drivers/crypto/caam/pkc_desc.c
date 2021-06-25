<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * caam - Freescale FSL CAAM support क्रम Public Key Cryptography descriptors
 *
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * There is no Shared Descriptor क्रम PKC so that the Job Descriptor must carry
 * all the desired key parameters, input and output poपूर्णांकers.
 */
#समावेश "caampkc.h"
#समावेश "desc_constr.h"

/* Descriptor क्रम RSA Public operation */
व्योम init_rsa_pub_desc(u32 *desc, काष्ठा rsa_pub_pdb *pdb)
अणु
	init_job_desc_pdb(desc, 0, SIZखातापूर्ण_RSA_PUB_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->n_dma);
	append_ptr(desc, pdb->e_dma);
	append_cmd(desc, pdb->f_len);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSAENC_PUBKEY);
पूर्ण

/* Descriptor क्रम RSA Private operation - Private Key Form #1 */
व्योम init_rsa_priv_f1_desc(u32 *desc, काष्ठा rsa_priv_f1_pdb *pdb)
अणु
	init_job_desc_pdb(desc, 0, SIZखातापूर्ण_RSA_PRIV_F1_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->n_dma);
	append_ptr(desc, pdb->d_dma);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSADEC_PRVKEY |
			 RSA_PRIV_KEY_FRM_1);
पूर्ण

/* Descriptor क्रम RSA Private operation - Private Key Form #2 */
व्योम init_rsa_priv_f2_desc(u32 *desc, काष्ठा rsa_priv_f2_pdb *pdb)
अणु
	init_job_desc_pdb(desc, 0, SIZखातापूर्ण_RSA_PRIV_F2_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->d_dma);
	append_ptr(desc, pdb->p_dma);
	append_ptr(desc, pdb->q_dma);
	append_ptr(desc, pdb->पंचांगp1_dma);
	append_ptr(desc, pdb->पंचांगp2_dma);
	append_cmd(desc, pdb->p_q_len);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSADEC_PRVKEY |
			 RSA_PRIV_KEY_FRM_2);
पूर्ण

/* Descriptor क्रम RSA Private operation - Private Key Form #3 */
व्योम init_rsa_priv_f3_desc(u32 *desc, काष्ठा rsa_priv_f3_pdb *pdb)
अणु
	init_job_desc_pdb(desc, 0, SIZखातापूर्ण_RSA_PRIV_F3_PDB);
	append_cmd(desc, pdb->sgf);
	append_ptr(desc, pdb->g_dma);
	append_ptr(desc, pdb->f_dma);
	append_ptr(desc, pdb->c_dma);
	append_ptr(desc, pdb->p_dma);
	append_ptr(desc, pdb->q_dma);
	append_ptr(desc, pdb->dp_dma);
	append_ptr(desc, pdb->dq_dma);
	append_ptr(desc, pdb->पंचांगp1_dma);
	append_ptr(desc, pdb->पंचांगp2_dma);
	append_cmd(desc, pdb->p_q_len);
	append_operation(desc, OP_TYPE_UNI_PROTOCOL | OP_PCLID_RSADEC_PRVKEY |
			 RSA_PRIV_KEY_FRM_3);
पूर्ण
