<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_DBRING_H
#घोषणा ATH11K_DBRING_H

#समावेश <linux/types.h>
#समावेश <linux/idr.h>
#समावेश <linux/spinlock.h>
#समावेश "dp.h"

काष्ठा ath11k_dbring_element अणु
	dma_addr_t paddr;
	u8 payload[0];
पूर्ण;

काष्ठा ath11k_dbring_data अणु
	व्योम *data;
	u32 data_sz;
	काष्ठा wmi_dma_buf_release_meta_data meta;
पूर्ण;

काष्ठा ath11k_dbring_buf_release_event अणु
	काष्ठा ath11k_wmi_dma_buf_release_fixed_param fixed;
	काष्ठा wmi_dma_buf_release_entry *buf_entry;
	काष्ठा wmi_dma_buf_release_meta_data *meta_data;
	u32 num_buf_entry;
	u32 num_meta;
पूर्ण;

काष्ठा ath11k_dbring_cap अणु
	u32 pdev_id;
	क्रमागत wmi_direct_buffer_module id;
	u32 min_elem;
	u32 min_buf_sz;
	u32 min_buf_align;
पूर्ण;

काष्ठा ath11k_dbring अणु
	काष्ठा dp_srng refill_srng;
	काष्ठा idr bufs_idr;
	/* Protects bufs_idr */
	spinlock_t idr_lock;
	dma_addr_t tp_addr;
	dma_addr_t hp_addr;
	पूर्णांक bufs_max;
	u32 pdev_id;
	u32 buf_sz;
	u32 buf_align;
	u32 num_resp_per_event;
	u32 event_समयout_ms;
	पूर्णांक (*handler)(काष्ठा ath11k *, काष्ठा ath11k_dbring_data *);
पूर्ण;

पूर्णांक ath11k_dbring_set_cfg(काष्ठा ath11k *ar,
			  काष्ठा ath11k_dbring *ring,
			  u32 num_resp_per_event,
			  u32 event_समयout_ms,
			  पूर्णांक (*handler)(काष्ठा ath11k *,
					 काष्ठा ath11k_dbring_data *));
पूर्णांक ath11k_dbring_wmi_cfg_setup(काष्ठा ath11k *ar,
				काष्ठा ath11k_dbring *ring,
				क्रमागत wmi_direct_buffer_module id);
पूर्णांक ath11k_dbring_buf_setup(काष्ठा ath11k *ar,
			    काष्ठा ath11k_dbring *ring,
			    काष्ठा ath11k_dbring_cap *db_cap);
पूर्णांक ath11k_dbring_srng_setup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring,
			     पूर्णांक ring_num, पूर्णांक num_entries);
पूर्णांक ath11k_dbring_buffer_release_event(काष्ठा ath11k_base *ab,
				       काष्ठा ath11k_dbring_buf_release_event *ev);
पूर्णांक ath11k_dbring_get_cap(काष्ठा ath11k_base *ab,
			  u8 pdev_idx,
			  क्रमागत wmi_direct_buffer_module id,
			  काष्ठा ath11k_dbring_cap *db_cap);
व्योम ath11k_dbring_srng_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring);
व्योम ath11k_dbring_buf_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring);
#पूर्ण_अगर /* ATH11K_DBRING_H */
