<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_ULP_H
#घोषणा BNXT_ULP_H

#घोषणा BNXT_ROCE_ULP	0
#घोषणा BNXT_OTHER_ULP	1
#घोषणा BNXT_MAX_ULP	2

#घोषणा BNXT_MIN_ROCE_CP_RINGS	2
#घोषणा BNXT_MIN_ROCE_STAT_CTXS	1

काष्ठा hwrm_async_event_cmpl;
काष्ठा bnxt;

काष्ठा bnxt_msix_entry अणु
	u32	vector;
	u32	ring_idx;
	u32	db_offset;
पूर्ण;

काष्ठा bnxt_ulp_ops अणु
	/* async_notअगरier() cannot sleep (in BH context) */
	व्योम (*ulp_async_notअगरier)(व्योम *, काष्ठा hwrm_async_event_cmpl *);
	व्योम (*ulp_stop)(व्योम *);
	व्योम (*ulp_start)(व्योम *);
	व्योम (*ulp_sriov_config)(व्योम *, पूर्णांक);
	व्योम (*ulp_shutकरोwn)(व्योम *);
	व्योम (*ulp_irq_stop)(व्योम *);
	व्योम (*ulp_irq_restart)(व्योम *, काष्ठा bnxt_msix_entry *);
पूर्ण;

काष्ठा bnxt_fw_msg अणु
	व्योम	*msg;
	पूर्णांक	msg_len;
	व्योम	*resp;
	पूर्णांक	resp_max_len;
	पूर्णांक	समयout;
पूर्ण;

काष्ठा bnxt_ulp अणु
	व्योम		*handle;
	काष्ठा bnxt_ulp_ops __rcu *ulp_ops;
	अचिन्हित दीर्घ	*async_events_bmap;
	u16		max_async_event_id;
	u16		msix_requested;
	u16		msix_base;
	atomic_t	ref_count;
पूर्ण;

काष्ठा bnxt_en_dev अणु
	काष्ठा net_device *net;
	काष्ठा pci_dev *pdev;
	u32 flags;
	#घोषणा BNXT_EN_FLAG_ROCEV1_CAP		0x1
	#घोषणा BNXT_EN_FLAG_ROCEV2_CAP		0x2
	#घोषणा BNXT_EN_FLAG_ROCE_CAP		(BNXT_EN_FLAG_ROCEV1_CAP | \
						 BNXT_EN_FLAG_ROCEV2_CAP)
	#घोषणा BNXT_EN_FLAG_MSIX_REQUESTED	0x4
	#घोषणा BNXT_EN_FLAG_ULP_STOPPED	0x8
	स्थिर काष्ठा bnxt_en_ops	*en_ops;
	काष्ठा bnxt_ulp			ulp_tbl[BNXT_MAX_ULP];
	पूर्णांक				l2_db_size;	/* Doorbell BAR size in
							 * bytes mapped by L2
							 * driver.
							 */
	पूर्णांक				l2_db_size_nc;	/* Doorbell BAR size in
							 * bytes mapped as non-
							 * cacheable.
							 */
पूर्ण;

काष्ठा bnxt_en_ops अणु
	पूर्णांक (*bnxt_रेजिस्टर_device)(काष्ठा bnxt_en_dev *, पूर्णांक,
				    काष्ठा bnxt_ulp_ops *, व्योम *);
	पूर्णांक (*bnxt_unरेजिस्टर_device)(काष्ठा bnxt_en_dev *, पूर्णांक);
	पूर्णांक (*bnxt_request_msix)(काष्ठा bnxt_en_dev *, पूर्णांक,
				 काष्ठा bnxt_msix_entry *, पूर्णांक);
	पूर्णांक (*bnxt_मुक्त_msix)(काष्ठा bnxt_en_dev *, पूर्णांक);
	पूर्णांक (*bnxt_send_fw_msg)(काष्ठा bnxt_en_dev *, पूर्णांक,
				काष्ठा bnxt_fw_msg *);
	पूर्णांक (*bnxt_रेजिस्टर_fw_async_events)(काष्ठा bnxt_en_dev *, पूर्णांक,
					     अचिन्हित दीर्घ *, u16);
पूर्ण;

अटल अंतरभूत bool bnxt_ulp_रेजिस्टरed(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id)
अणु
	अगर (edev && rcu_access_poपूर्णांकer(edev->ulp_tbl[ulp_id].ulp_ops))
		वापस true;
	वापस false;
पूर्ण

पूर्णांक bnxt_get_ulp_msix_num(काष्ठा bnxt *bp);
पूर्णांक bnxt_get_ulp_msix_base(काष्ठा bnxt *bp);
पूर्णांक bnxt_get_ulp_stat_ctxs(काष्ठा bnxt *bp);
व्योम bnxt_ulp_stop(काष्ठा bnxt *bp);
व्योम bnxt_ulp_start(काष्ठा bnxt *bp, पूर्णांक err);
व्योम bnxt_ulp_sriov_cfg(काष्ठा bnxt *bp, पूर्णांक num_vfs);
व्योम bnxt_ulp_shutकरोwn(काष्ठा bnxt *bp);
व्योम bnxt_ulp_irq_stop(काष्ठा bnxt *bp);
व्योम bnxt_ulp_irq_restart(काष्ठा bnxt *bp, पूर्णांक err);
व्योम bnxt_ulp_async_events(काष्ठा bnxt *bp, काष्ठा hwrm_async_event_cmpl *cmpl);
काष्ठा bnxt_en_dev *bnxt_ulp_probe(काष्ठा net_device *dev);

#पूर्ण_अगर
