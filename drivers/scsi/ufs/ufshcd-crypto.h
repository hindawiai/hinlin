<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित _UFSHCD_CRYPTO_H
#घोषणा _UFSHCD_CRYPTO_H

#अगर_घोषित CONFIG_SCSI_UFS_CRYPTO
#समावेश "ufshcd.h"
#समावेश "ufshci.h"

अटल अंतरभूत व्योम ufshcd_prepare_lrbp_crypto(काष्ठा request *rq,
					      काष्ठा ufshcd_lrb *lrbp)
अणु
	अगर (!rq || !rq->crypt_keyslot) अणु
		lrbp->crypto_key_slot = -1;
		वापस;
	पूर्ण

	lrbp->crypto_key_slot = blk_ksm_get_slot_idx(rq->crypt_keyslot);
	lrbp->data_unit_num = rq->crypt_ctx->bc_dun[0];
पूर्ण

अटल अंतरभूत व्योम
ufshcd_prepare_req_desc_hdr_crypto(काष्ठा ufshcd_lrb *lrbp, u32 *dword_0,
				   u32 *dword_1, u32 *dword_3)
अणु
	अगर (lrbp->crypto_key_slot >= 0) अणु
		*dword_0 |= UTP_REQ_DESC_CRYPTO_ENABLE_CMD;
		*dword_0 |= lrbp->crypto_key_slot;
		*dword_1 = lower_32_bits(lrbp->data_unit_num);
		*dword_3 = upper_32_bits(lrbp->data_unit_num);
	पूर्ण
पूर्ण

bool ufshcd_crypto_enable(काष्ठा ufs_hba *hba);

पूर्णांक ufshcd_hba_init_crypto_capabilities(काष्ठा ufs_hba *hba);

व्योम ufshcd_init_crypto(काष्ठा ufs_hba *hba);

व्योम ufshcd_crypto_setup_rq_keyslot_manager(काष्ठा ufs_hba *hba,
					    काष्ठा request_queue *q);

#अन्यथा /* CONFIG_SCSI_UFS_CRYPTO */

अटल अंतरभूत व्योम ufshcd_prepare_lrbp_crypto(काष्ठा request *rq,
					      काष्ठा ufshcd_lrb *lrbp) अणु पूर्ण

अटल अंतरभूत व्योम
ufshcd_prepare_req_desc_hdr_crypto(काष्ठा ufshcd_lrb *lrbp, u32 *dword_0,
				   u32 *dword_1, u32 *dword_3) अणु पूर्ण

अटल अंतरभूत bool ufshcd_crypto_enable(काष्ठा ufs_hba *hba)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ufshcd_hba_init_crypto_capabilities(काष्ठा ufs_hba *hba)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ufshcd_init_crypto(काष्ठा ufs_hba *hba) अणु पूर्ण

अटल अंतरभूत व्योम ufshcd_crypto_setup_rq_keyslot_manager(काष्ठा ufs_hba *hba,
						काष्ठा request_queue *q) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SCSI_UFS_CRYPTO */

#पूर्ण_अगर /* _UFSHCD_CRYPTO_H */
