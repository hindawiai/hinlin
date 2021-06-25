<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _SNOC_H_
#घोषणा _SNOC_H_

#समावेश "hw.h"
#समावेश "ce.h"
#समावेश "qmi.h"

काष्ठा ath10k_snoc_drv_priv अणु
	क्रमागत ath10k_hw_rev hw_rev;
	u64 dma_mask;
	u32 msa_size;
पूर्ण;

काष्ठा snoc_state अणु
	u32 pipe_cfg_addr;
	u32 svc_to_pipe_map;
पूर्ण;

काष्ठा ath10k_snoc_pipe अणु
	काष्ठा ath10k_ce_pipe *ce_hdl;
	u8 pipe_num;
	काष्ठा ath10k *hअगर_ce_state;
	माप_प्रकार buf_sz;
	/* protect ce info */
	spinlock_t pipe_lock;
	काष्ठा ath10k_snoc *ar_snoc;
पूर्ण;

काष्ठा ath10k_snoc_target_info अणु
	u32 target_version;
	u32 target_type;
	u32 target_revision;
	u32 soc_version;
पूर्ण;

काष्ठा ath10k_snoc_ce_irq अणु
	u32 irq_line;
पूर्ण;

क्रमागत ath10k_snoc_flags अणु
	ATH10K_SNOC_FLAG_REGISTERED,
	ATH10K_SNOC_FLAG_UNREGISTERING,
	ATH10K_SNOC_FLAG_RECOVERY,
	ATH10K_SNOC_FLAG_8BIT_HOST_CAP_QUIRK,
पूर्ण;

काष्ठा clk_bulk_data;
काष्ठा regulator_bulk_data;

काष्ठा ath10k_snoc अणु
	काष्ठा platक्रमm_device *dev;
	काष्ठा ath10k *ar;
	अचिन्हित पूर्णांक use_tz;
	काष्ठा ath10k_firmware अणु
		काष्ठा device *dev;
		dma_addr_t fw_start_addr;
		काष्ठा iommu_करोमुख्य *iommu_करोमुख्य;
		माप_प्रकार mapped_mem_size;
	पूर्ण fw;
	व्योम __iomem *mem;
	dma_addr_t mem_pa;
	काष्ठा ath10k_snoc_target_info target_info;
	माप_प्रकार mem_len;
	काष्ठा ath10k_snoc_pipe pipe_info[CE_COUNT_MAX];
	काष्ठा ath10k_snoc_ce_irq ce_irqs[CE_COUNT_MAX];
	काष्ठा ath10k_ce ce;
	काष्ठा समयr_list rx_post_retry;
	काष्ठा regulator_bulk_data *vregs;
	माप_प्रकार num_vregs;
	काष्ठा clk_bulk_data *clks;
	माप_प्रकार num_clks;
	काष्ठा ath10k_qmi *qmi;
	अचिन्हित दीर्घ flags;
	bool xo_cal_supported;
	u32 xo_cal_data;
	DECLARE_BITMAP(pending_ce_irqs, CE_COUNT_MAX);
पूर्ण;

अटल अंतरभूत काष्ठा ath10k_snoc *ath10k_snoc_priv(काष्ठा ath10k *ar)
अणु
	वापस (काष्ठा ath10k_snoc *)ar->drv_priv;
पूर्ण

पूर्णांक ath10k_snoc_fw_indication(काष्ठा ath10k *ar, u64 type);
व्योम ath10k_snoc_fw_crashed_dump(काष्ठा ath10k *ar);

#पूर्ण_अगर /* _SNOC_H_ */
