<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_CE_H
#घोषणा ATH11K_CE_H

#घोषणा CE_COUNT_MAX 12

/* Byte swap data words */
#घोषणा CE_ATTR_BYTE_SWAP_DATA 2

/* no पूर्णांकerrupt on copy completion */
#घोषणा CE_ATTR_DIS_INTR		8

/* Host software's Copy Engine configuration. */
#अगर_घोषित __BIG_ENDIAN
#घोषणा CE_ATTR_FLAGS CE_ATTR_BYTE_SWAP_DATA
#अन्यथा
#घोषणा CE_ATTR_FLAGS 0
#पूर्ण_अगर

/* Threshold to poll क्रम tx completion in हाल of Interrupt disabled CE's */
#घोषणा ATH11K_CE_USAGE_THRESHOLD 32

व्योम ath11k_ce_byte_swap(व्योम *mem, u32 len);

/*
 * Directions क्रम पूर्णांकerconnect pipe configuration.
 * These definitions may be used during configuration and are shared
 * between Host and Target.
 *
 * Pipe Directions are relative to the Host, so PIPEसूची_IN means
 * "coming IN over air through Target to Host" as with a WiFi Rx operation.
 * Conversely, PIPEसूची_OUT means "going OUT from Host through Target over air"
 * as with a WiFi Tx operation. This is somewhat awkward क्रम the "middle-man"
 * Target since things that are "PIPEDIR_OUT" are coming IN to the Target
 * over the पूर्णांकerconnect.
 */
#घोषणा PIPEसूची_NONE		0
#घोषणा PIPEसूची_IN		1 /* Target-->Host, WiFi Rx direction */
#घोषणा PIPEसूची_OUT		2 /* Host->Target, WiFi Tx direction */
#घोषणा PIPEसूची_INOUT		3 /* bidirectional */
#घोषणा PIPEसूची_INOUT_H2H	4 /* bidirectional, host to host */

/* CE address/mask */
#घोषणा CE_HOST_IE_ADDRESS	0x00A1803C
#घोषणा CE_HOST_IE_2_ADDRESS	0x00A18040
#घोषणा CE_HOST_IE_3_ADDRESS	CE_HOST_IE_ADDRESS

#घोषणा CE_HOST_IE_3_SHIFT	0xC

#घोषणा CE_RING_IDX_INCR(nentries_mask, idx) (((idx) + 1) & (nentries_mask))

#घोषणा ATH11K_CE_RX_POST_RETRY_JIFFIES 50

काष्ठा ath11k_base;

/*
 * Establish a mapping between a service/direction and a pipe.
 * Configuration inक्रमmation क्रम a Copy Engine pipe and services.
 * Passed from Host to Target through QMI message and must be in
 * little endian क्रमmat.
 */
काष्ठा service_to_pipe अणु
	__le32 service_id;
	__le32 pipedir;
	__le32 pipक्रमागत;
पूर्ण;

/*
 * Configuration inक्रमmation क्रम a Copy Engine pipe.
 * Passed from Host to Target through QMI message during startup (one per CE).
 *
 * NOTE: Structure is shared between Host software and Target firmware!
 */
काष्ठा ce_pipe_config अणु
	__le32 pipक्रमागत;
	__le32 pipedir;
	__le32 nentries;
	__le32 nbytes_max;
	__le32 flags;
	__le32 reserved;
पूर्ण;

काष्ठा ce_attr अणु
	/* CE_ATTR_* values */
	अचिन्हित पूर्णांक flags;

	/* #entries in source ring - Must be a घातer of 2 */
	अचिन्हित पूर्णांक src_nentries;

	/*
	 * Max source send size क्रम this CE.
	 * This is also the minimum size of a destination buffer.
	 */
	अचिन्हित पूर्णांक src_sz_max;

	/* #entries in destination ring - Must be a घातer of 2 */
	अचिन्हित पूर्णांक dest_nentries;

	व्योम (*recv_cb)(काष्ठा ath11k_base *, काष्ठा sk_buff *);
पूर्ण;

#घोषणा CE_DESC_RING_ALIGN 8

काष्ठा ath11k_ce_ring अणु
	/* Number of entries in this ring; must be घातer of 2 */
	अचिन्हित पूर्णांक nentries;
	अचिन्हित पूर्णांक nentries_mask;

	/* For dest ring, this is the next index to be processed
	 * by software after it was/is received पूर्णांकo.
	 *
	 * For src ring, this is the last descriptor that was sent
	 * and completion processed by software.
	 *
	 * Regardless of src or dest ring, this is an invariant
	 * (modulo ring size):
	 *     ग_लिखो index >= पढ़ो index >= sw_index
	 */
	अचिन्हित पूर्णांक sw_index;
	/* cached copy */
	अचिन्हित पूर्णांक ग_लिखो_index;

	/* Start of DMA-coherent area reserved क्रम descriptors */
	/* Host address space */
	व्योम *base_addr_owner_space_unaligned;
	/* CE address space */
	u32 base_addr_ce_space_unaligned;

	/* Actual start of descriptors.
	 * Aligned to descriptor-size boundary.
	 * Poपूर्णांकs पूर्णांकo reserved DMA-coherent area, above.
	 */
	/* Host address space */
	व्योम *base_addr_owner_space;

	/* CE address space */
	u32 base_addr_ce_space;

	/* HAL ring id */
	u32 hal_ring_id;

	/* keep last */
	काष्ठा sk_buff *skb[0];
पूर्ण;

काष्ठा ath11k_ce_pipe अणु
	काष्ठा ath11k_base *ab;
	u16 pipe_num;
	अचिन्हित पूर्णांक attr_flags;
	अचिन्हित पूर्णांक buf_sz;
	अचिन्हित पूर्णांक rx_buf_needed;

	व्योम (*send_cb)(काष्ठा ath11k_ce_pipe *);
	व्योम (*recv_cb)(काष्ठा ath11k_base *, काष्ठा sk_buff *);

	काष्ठा tasklet_काष्ठा पूर्णांकr_tq;
	काष्ठा ath11k_ce_ring *src_ring;
	काष्ठा ath11k_ce_ring *dest_ring;
	काष्ठा ath11k_ce_ring *status_ring;
	u64 बारtamp;
पूर्ण;

काष्ठा ath11k_ce अणु
	काष्ठा ath11k_ce_pipe ce_pipe[CE_COUNT_MAX];
	/* Protects rings of all ce pipes */
	spinlock_t ce_lock;
	काष्ठा ath11k_hp_update_समयr hp_समयr[CE_COUNT_MAX];
पूर्ण;

बाह्य स्थिर काष्ठा ce_attr ath11k_host_ce_config_ipq8074[];
बाह्य स्थिर काष्ठा ce_attr ath11k_host_ce_config_qca6390[];
बाह्य स्थिर काष्ठा ce_attr ath11k_host_ce_config_qcn9074[];

व्योम ath11k_ce_cleanup_pipes(काष्ठा ath11k_base *ab);
व्योम ath11k_ce_rx_replenish_retry(काष्ठा समयr_list *t);
व्योम ath11k_ce_per_engine_service(काष्ठा ath11k_base *ab, u16 ce_id);
पूर्णांक ath11k_ce_send(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb, u8 pipe_id,
		   u16 transfer_id);
व्योम ath11k_ce_rx_post_buf(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_ce_init_pipes(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_ce_alloc_pipes(काष्ठा ath11k_base *ab);
व्योम ath11k_ce_मुक्त_pipes(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_ce_get_attr_flags(काष्ठा ath11k_base *ab, पूर्णांक ce_id);
व्योम ath11k_ce_poll_send_completed(काष्ठा ath11k_base *ab, u8 pipe_id);
पूर्णांक ath11k_ce_map_service_to_pipe(काष्ठा ath11k_base *ab, u16 service_id,
				  u8 *ul_pipe, u8 *dl_pipe);
पूर्णांक ath11k_ce_attr_attach(काष्ठा ath11k_base *ab);
व्योम ath11k_ce_get_shaकरोw_config(काष्ठा ath11k_base *ab,
				 u32 **shaकरोw_cfg, u32 *shaकरोw_cfg_len);
व्योम ath11k_ce_stop_shaकरोw_समयrs(काष्ठा ath11k_base *ab);

#पूर्ण_अगर
