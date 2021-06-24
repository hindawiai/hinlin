<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CE_H_
#घोषणा _CE_H_

#समावेश "hif.h"

#घोषणा CE_HTT_H2T_MSG_SRC_NENTRIES 8192

/* Descriptor rings must be aligned to this boundary */
#घोषणा CE_DESC_RING_ALIGN	8
#घोषणा CE_SEND_FLAG_GATHER	0x00010000

/*
 * Copy Engine support: low-level Target-side Copy Engine API.
 * This is a hardware access layer used by code that understands
 * how to use copy engines.
 */

काष्ठा ath10k_ce_pipe;

#घोषणा CE_DESC_FLAGS_GATHER         (1 << 0)
#घोषणा CE_DESC_FLAGS_BYTE_SWAP      (1 << 1)
#घोषणा CE_WCN3990_DESC_FLAGS_GATHER BIT(31)

#घोषणा CE_DESC_ADDR_MASK		GENMASK_ULL(34, 0)
#घोषणा CE_DESC_ADDR_HI_MASK		GENMASK(4, 0)

/* Following desc flags are used in QCA99X0 */
#घोषणा CE_DESC_FLAGS_HOST_INT_DIS	(1 << 2)
#घोषणा CE_DESC_FLAGS_TGT_INT_DIS	(1 << 3)

#घोषणा CE_DESC_FLAGS_META_DATA_MASK ar->hw_values->ce_desc_meta_data_mask
#घोषणा CE_DESC_FLAGS_META_DATA_LSB  ar->hw_values->ce_desc_meta_data_lsb

#घोषणा CE_DDR_RRI_MASK			GENMASK(15, 0)
#घोषणा CE_DDR_DRRI_SHIFT		16

काष्ठा ce_desc अणु
	__le32 addr;
	__le16 nbytes;
	__le16 flags; /* %CE_DESC_FLAGS_ */
पूर्ण;

काष्ठा ce_desc_64 अणु
	__le64 addr;
	__le16 nbytes; /* length in रेजिस्टर map */
	__le16 flags; /* fw_metadata_high */
	__le32 toeplitz_hash_result;
पूर्ण;

#घोषणा CE_DESC_SIZE माप(काष्ठा ce_desc)
#घोषणा CE_DESC_SIZE_64 माप(काष्ठा ce_desc_64)

काष्ठा ath10k_ce_ring अणु
	/* Number of entries in this ring; must be घातer of 2 */
	अचिन्हित पूर्णांक nentries;
	अचिन्हित पूर्णांक nentries_mask;

	/*
	 * For dest ring, this is the next index to be processed
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
	/*
	 * For src ring, this is the next index not yet processed by HW.
	 * This is a cached copy of the real HW index (पढ़ो index), used
	 * क्रम aव्योमing पढ़ोing the HW index रेजिस्टर more often than
	 * necessary.
	 * This extends the invariant:
	 *     ग_लिखो index >= पढ़ो index >= hw_index >= sw_index
	 *
	 * For dest ring, this is currently unused.
	 */
	/* cached copy */
	अचिन्हित पूर्णांक hw_index;

	/* Start of DMA-coherent area reserved क्रम descriptors */
	/* Host address space */
	व्योम *base_addr_owner_space_unaligned;
	/* CE address space */
	dma_addr_t base_addr_ce_space_unaligned;

	/*
	 * Actual start of descriptors.
	 * Aligned to descriptor-size boundary.
	 * Poपूर्णांकs पूर्णांकo reserved DMA-coherent area, above.
	 */
	/* Host address space */
	व्योम *base_addr_owner_space;

	/* CE address space */
	dma_addr_t base_addr_ce_space;

	अक्षर *shaकरोw_base_unaligned;
	काष्ठा ce_desc_64 *shaकरोw_base;

	/* keep last */
	व्योम *per_transfer_context[];
पूर्ण;

काष्ठा ath10k_ce_pipe अणु
	काष्ठा ath10k *ar;
	अचिन्हित पूर्णांक id;

	अचिन्हित पूर्णांक attr_flags;

	u32 ctrl_addr;

	व्योम (*send_cb)(काष्ठा ath10k_ce_pipe *);
	व्योम (*recv_cb)(काष्ठा ath10k_ce_pipe *);

	अचिन्हित पूर्णांक src_sz_max;
	काष्ठा ath10k_ce_ring *src_ring;
	काष्ठा ath10k_ce_ring *dest_ring;
	स्थिर काष्ठा ath10k_ce_ops *ops;
पूर्ण;

/* Copy Engine settable attributes */
काष्ठा ce_attr;

काष्ठा ath10k_bus_ops अणु
	u32 (*पढ़ो32)(काष्ठा ath10k *ar, u32 offset);
	व्योम (*ग_लिखो32)(काष्ठा ath10k *ar, u32 offset, u32 value);
	पूर्णांक (*get_num_banks)(काष्ठा ath10k *ar);
पूर्ण;

अटल अंतरभूत काष्ठा ath10k_ce *ath10k_ce_priv(काष्ठा ath10k *ar)
अणु
	वापस (काष्ठा ath10k_ce *)ar->ce_priv;
पूर्ण

काष्ठा ath10k_ce अणु
	/* protects CE info */
	spinlock_t ce_lock;
	स्थिर काष्ठा ath10k_bus_ops *bus_ops;
	काष्ठा ath10k_ce_pipe ce_states[CE_COUNT_MAX];
	u32 *vaddr_rri;
	dma_addr_t paddr_rri;
पूर्ण;

/*==================Send====================*/

/* ath10k_ce_send flags */
#घोषणा CE_SEND_FLAG_BYTE_SWAP 1

/*
 * Queue a source buffer to be sent to an anonymous destination buffer.
 *   ce         - which copy engine to use
 *   buffer          - address of buffer
 *   nbytes          - number of bytes to send
 *   transfer_id     - arbitrary ID; reflected to destination
 *   flags           - CE_SEND_FLAG_* values
 * Returns 0 on success; otherwise an error status.
 *
 * Note: If no flags are specअगरied, use CE's शेष data swap mode.
 *
 * Implementation note: pushes 1 buffer to Source ring
 */
पूर्णांक ath10k_ce_send(काष्ठा ath10k_ce_pipe *ce_state,
		   व्योम *per_transfer_send_context,
		   dma_addr_t buffer,
		   अचिन्हित पूर्णांक nbytes,
		   /* 14 bits */
		   अचिन्हित पूर्णांक transfer_id,
		   अचिन्हित पूर्णांक flags);

पूर्णांक ath10k_ce_send_nolock(काष्ठा ath10k_ce_pipe *ce_state,
			  व्योम *per_transfer_context,
			  dma_addr_t buffer,
			  अचिन्हित पूर्णांक nbytes,
			  अचिन्हित पूर्णांक transfer_id,
			  अचिन्हित पूर्णांक flags);

व्योम __ath10k_ce_send_revert(काष्ठा ath10k_ce_pipe *pipe);

पूर्णांक ath10k_ce_num_मुक्त_src_entries(काष्ठा ath10k_ce_pipe *pipe);

/*==================Recv=======================*/

पूर्णांक __ath10k_ce_rx_num_मुक्त_bufs(काष्ठा ath10k_ce_pipe *pipe);
पूर्णांक ath10k_ce_rx_post_buf(काष्ठा ath10k_ce_pipe *pipe, व्योम *ctx,
			  dma_addr_t paddr);
व्योम ath10k_ce_rx_update_ग_लिखो_idx(काष्ठा ath10k_ce_pipe *pipe, u32 nentries);

/* recv flags */
/* Data is byte-swapped */
#घोषणा CE_RECV_FLAG_SWAPPED	1

/*
 * Supply data क्रम the next completed unprocessed receive descriptor.
 * Pops buffer from Dest ring.
 */
पूर्णांक ath10k_ce_completed_recv_next(काष्ठा ath10k_ce_pipe *ce_state,
				  व्योम **per_transfer_contextp,
				  अचिन्हित पूर्णांक *nbytesp);
/*
 * Supply data क्रम the next completed unprocessed send descriptor.
 * Pops 1 completed send buffer from Source ring.
 */
पूर्णांक ath10k_ce_completed_send_next(काष्ठा ath10k_ce_pipe *ce_state,
				  व्योम **per_transfer_contextp);

पूर्णांक ath10k_ce_completed_send_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम **per_transfer_contextp);

/*==================CE Engine Initialization=======================*/

पूर्णांक ath10k_ce_init_pipe(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			स्थिर काष्ठा ce_attr *attr);
व्योम ath10k_ce_deinit_pipe(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id);
पूर्णांक ath10k_ce_alloc_pipe(काष्ठा ath10k *ar, पूर्णांक ce_id,
			 स्थिर काष्ठा ce_attr *attr);
व्योम ath10k_ce_मुक्त_pipe(काष्ठा ath10k *ar, पूर्णांक ce_id);

/*==================CE Engine Shutकरोwn=======================*/
/*
 * Support clean shutकरोwn by allowing the caller to revoke
 * receive buffers.  Target DMA must be stopped beक्रमe using
 * this API.
 */
पूर्णांक ath10k_ce_revoke_recv_next(काष्ठा ath10k_ce_pipe *ce_state,
			       व्योम **per_transfer_contextp,
			       dma_addr_t *bufferp);

पूर्णांक ath10k_ce_completed_recv_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम **per_transfer_contextp,
					 अचिन्हित पूर्णांक *nbytesp);

/*
 * Support clean shutकरोwn by allowing the caller to cancel
 * pending sends.  Target DMA must be stopped beक्रमe using
 * this API.
 */
पूर्णांक ath10k_ce_cancel_send_next(काष्ठा ath10k_ce_pipe *ce_state,
			       व्योम **per_transfer_contextp,
			       dma_addr_t *bufferp,
			       अचिन्हित पूर्णांक *nbytesp,
			       अचिन्हित पूर्णांक *transfer_idp);

/*==================CE Interrupt Handlers====================*/
व्योम ath10k_ce_per_engine_service_any(काष्ठा ath10k *ar);
व्योम ath10k_ce_per_engine_service(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id);
व्योम ath10k_ce_disable_पूर्णांकerrupt(काष्ठा ath10k *ar, पूर्णांक ce_id);
व्योम ath10k_ce_disable_पूर्णांकerrupts(काष्ठा ath10k *ar);
व्योम ath10k_ce_enable_पूर्णांकerrupt(काष्ठा ath10k *ar, पूर्णांक ce_id);
व्योम ath10k_ce_enable_पूर्णांकerrupts(काष्ठा ath10k *ar);
व्योम ath10k_ce_dump_रेजिस्टरs(काष्ठा ath10k *ar,
			      काष्ठा ath10k_fw_crash_data *crash_data);

व्योम ath10k_ce_alloc_rri(काष्ठा ath10k *ar);
व्योम ath10k_ce_मुक्त_rri(काष्ठा ath10k *ar);

/* ce_attr.flags values */
/* Use NonSnooping PCIe accesses? */
#घोषणा CE_ATTR_NO_SNOOP		BIT(0)

/* Byte swap data words */
#घोषणा CE_ATTR_BYTE_SWAP_DATA		BIT(1)

/* Swizzle descriptors? */
#घोषणा CE_ATTR_SWIZZLE_DESCRIPTORS	BIT(2)

/* no पूर्णांकerrupt on copy completion */
#घोषणा CE_ATTR_DIS_INTR		BIT(3)

/* no पूर्णांकerrupt, only polling */
#घोषणा CE_ATTR_POLL			BIT(4)

/* Attributes of an instance of a Copy Engine */
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

	व्योम (*send_cb)(काष्ठा ath10k_ce_pipe *);
	व्योम (*recv_cb)(काष्ठा ath10k_ce_pipe *);
पूर्ण;

काष्ठा ath10k_ce_ops अणु
	काष्ठा ath10k_ce_ring *(*ce_alloc_src_ring)(काष्ठा ath10k *ar,
						    u32 ce_id,
						    स्थिर काष्ठा ce_attr *attr);
	काष्ठा ath10k_ce_ring *(*ce_alloc_dst_ring)(काष्ठा ath10k *ar,
						    u32 ce_id,
						    स्थिर काष्ठा ce_attr *attr);
	पूर्णांक (*ce_rx_post_buf)(काष्ठा ath10k_ce_pipe *pipe, व्योम *ctx,
			      dma_addr_t paddr);
	पूर्णांक (*ce_completed_recv_next_nolock)(काष्ठा ath10k_ce_pipe *ce_state,
					     व्योम **per_transfer_contextp,
					     u32 *nbytesp);
	पूर्णांक (*ce_revoke_recv_next)(काष्ठा ath10k_ce_pipe *ce_state,
				   व्योम **per_transfer_contextp,
				   dma_addr_t *nbytesp);
	व्योम (*ce_extract_desc_data)(काष्ठा ath10k *ar,
				     काष्ठा ath10k_ce_ring *src_ring,
				     u32 sw_index, dma_addr_t *bufferp,
				     u32 *nbytesp, u32 *transfer_idp);
	व्योम (*ce_मुक्त_pipe)(काष्ठा ath10k *ar, पूर्णांक ce_id);
	पूर्णांक (*ce_send_nolock)(काष्ठा ath10k_ce_pipe *pipe,
			      व्योम *per_transfer_context,
			      dma_addr_t buffer, u32 nbytes,
			      u32 transfer_id, u32 flags);
	व्योम (*ce_set_src_ring_base_addr_hi)(काष्ठा ath10k *ar,
					     u32 ce_ctrl_addr,
					     u64 addr);
	व्योम (*ce_set_dest_ring_base_addr_hi)(काष्ठा ath10k *ar,
					      u32 ce_ctrl_addr,
					      u64 addr);
	पूर्णांक (*ce_completed_send_next_nolock)(काष्ठा ath10k_ce_pipe *ce_state,
					     व्योम **per_transfer_contextp);
पूर्ण;

अटल अंतरभूत u32 ath10k_ce_base_address(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id)
अणु
	वापस CE0_BASE_ADDRESS + (CE1_BASE_ADDRESS - CE0_BASE_ADDRESS) * ce_id;
पूर्ण

#घोषणा COPY_ENGINE_ID(COPY_ENGINE_BASE_ADDRESS) (((COPY_ENGINE_BASE_ADDRESS) \
		- CE0_BASE_ADDRESS) / (CE1_BASE_ADDRESS - CE0_BASE_ADDRESS))

#घोषणा CE_SRC_RING_TO_DESC(baddr, idx) \
	(&(((काष्ठा ce_desc *)baddr)[idx]))

#घोषणा CE_DEST_RING_TO_DESC(baddr, idx) \
	(&(((काष्ठा ce_desc *)baddr)[idx]))

#घोषणा CE_SRC_RING_TO_DESC_64(baddr, idx) \
	(&(((काष्ठा ce_desc_64 *)baddr)[idx]))

#घोषणा CE_DEST_RING_TO_DESC_64(baddr, idx) \
	(&(((काष्ठा ce_desc_64 *)baddr)[idx]))

/* Ring arithmetic (modulus number of entries in ring, which is a pwr of 2). */
#घोषणा CE_RING_DELTA(nentries_mask, fromidx, toidx) \
	(((पूर्णांक)(toidx) - (पूर्णांक)(fromidx)) & (nentries_mask))

#घोषणा CE_RING_IDX_INCR(nentries_mask, idx) (((idx) + 1) & (nentries_mask))
#घोषणा CE_RING_IDX_ADD(nentries_mask, idx, num) \
		(((idx) + (num)) & (nentries_mask))

#घोषणा CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_LSB \
				ar->regs->ce_wrap_पूर्णांकr_sum_host_msi_lsb
#घोषणा CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_MASK \
				ar->regs->ce_wrap_पूर्णांकr_sum_host_msi_mask
#घोषणा CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_GET(x) \
	(((x) & CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_MASK) >> \
		CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_LSB)
#घोषणा CE_WRAPPER_INTERRUPT_SUMMARY_ADDRESS			0x0000

अटल अंतरभूत u32 ath10k_ce_पूर्णांकerrupt_summary(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस CE_WRAPPER_INTERRUPT_SUMMARY_HOST_MSI_GET(
		ce->bus_ops->पढ़ो32((ar), CE_WRAPPER_BASE_ADDRESS +
		CE_WRAPPER_INTERRUPT_SUMMARY_ADDRESS));
पूर्ण

/* Host software's Copy Engine configuration. */
#घोषणा CE_ATTR_FLAGS 0

/*
 * Configuration inक्रमmation क्रम a Copy Engine pipe.
 * Passed from Host to Target during startup (one per CE).
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
#घोषणा PIPEसूची_NONE    0
#घोषणा PIPEसूची_IN      1  /* Target-->Host, WiFi Rx direction */
#घोषणा PIPEसूची_OUT     2  /* Host->Target, WiFi Tx direction */
#घोषणा PIPEसूची_INOUT   3  /* bidirectional */

/* Establish a mapping between a service/direction and a pipe. */
काष्ठा ce_service_to_pipe अणु
	__le32 service_id;
	__le32 pipedir;
	__le32 pipक्रमागत;
पूर्ण;

#पूर्ण_अगर /* _CE_H_ */
