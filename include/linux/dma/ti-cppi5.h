<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CPPI5 descriptors पूर्णांकerface
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 */

#अगर_अघोषित __TI_CPPI5_H__
#घोषणा __TI_CPPI5_H__

#समावेश <linux/bitops.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bug.h>

/**
 * काष्ठा cppi5_desc_hdr_t - Descriptor header, present in all types of
 *			     descriptors
 * @pkt_info0:		Packet info word 0 (n/a in Buffer desc)
 * @pkt_info0:		Packet info word 1 (n/a in Buffer desc)
 * @pkt_info0:		Packet info word 2 (n/a in Buffer desc)
 * @src_dst_tag:	Packet info word 3 (n/a in Buffer desc)
 */
काष्ठा cppi5_desc_hdr_t अणु
	u32 pkt_info0;
	u32 pkt_info1;
	u32 pkt_info2;
	u32 src_dst_tag;
पूर्ण __packed;

/**
 * काष्ठा cppi5_host_desc_t - Host-mode packet and buffer descriptor definition
 * @hdr:		Descriptor header
 * @next_desc:		word 4/5: Linking word
 * @buf_ptr:		word 6/7: Buffer poपूर्णांकer
 * @buf_info1:		word 8: Buffer valid data length
 * @org_buf_len:	word 9: Original buffer length
 * @org_buf_ptr:	word 10/11: Original buffer poपूर्णांकer
 * @epib[0]:		Extended Packet Info Data (optional, 4 words), and/or
 *			Protocol Specअगरic Data (optional, 0-128 bytes in
 *			multiples of 4), and/or
 *			Other Software Data (0-N bytes, optional)
 */
काष्ठा cppi5_host_desc_t अणु
	काष्ठा cppi5_desc_hdr_t hdr;
	u64 next_desc;
	u64 buf_ptr;
	u32 buf_info1;
	u32 org_buf_len;
	u64 org_buf_ptr;
	u32 epib[];
पूर्ण __packed;

#घोषणा CPPI5_DESC_MIN_ALIGN			(16U)

#घोषणा CPPI5_INFO0_HDESC_EPIB_SIZE		(16U)
#घोषणा CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE	(128U)

#घोषणा CPPI5_INFO0_HDESC_TYPE_SHIFT		(30U)
#घोषणा CPPI5_INFO0_HDESC_TYPE_MASK		GENMASK(31, 30)
#घोषणा   CPPI5_INFO0_DESC_TYPE_VAL_HOST	(1U)
#घोषणा   CPPI5_INFO0_DESC_TYPE_VAL_MONO	(2U)
#घोषणा   CPPI5_INFO0_DESC_TYPE_VAL_TR		(3U)
#घोषणा CPPI5_INFO0_HDESC_EPIB_PRESENT		BIT(29)
/*
 * Protocol Specअगरic Words location:
 * 0 - located in the descriptor,
 * 1 = located in the SOP Buffer immediately prior to the data.
 */
#घोषणा CPPI5_INFO0_HDESC_PSINFO_LOCATION	BIT(28)
#घोषणा CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT	(22U)
#घोषणा CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK	GENMASK(27, 22)
#घोषणा CPPI5_INFO0_HDESC_PKTLEN_SHIFT		(0)
#घोषणा CPPI5_INFO0_HDESC_PKTLEN_MASK		GENMASK(21, 0)

#घोषणा CPPI5_INFO1_DESC_PKTERROR_SHIFT		(28U)
#घोषणा CPPI5_INFO1_DESC_PKTERROR_MASK		GENMASK(31, 28)
#घोषणा CPPI5_INFO1_HDESC_PSFLGS_SHIFT		(24U)
#घोषणा CPPI5_INFO1_HDESC_PSFLGS_MASK		GENMASK(27, 24)
#घोषणा CPPI5_INFO1_DESC_PKTID_SHIFT		(14U)
#घोषणा CPPI5_INFO1_DESC_PKTID_MASK		GENMASK(23, 14)
#घोषणा CPPI5_INFO1_DESC_FLOWID_SHIFT		(0)
#घोषणा CPPI5_INFO1_DESC_FLOWID_MASK		GENMASK(13, 0)
#घोषणा CPPI5_INFO1_DESC_FLOWID_DEFAULT		CPPI5_INFO1_DESC_FLOWID_MASK

#घोषणा CPPI5_INFO2_HDESC_PKTTYPE_SHIFT		(27U)
#घोषणा CPPI5_INFO2_HDESC_PKTTYPE_MASK		GENMASK(31, 27)
/* Return Policy: 0 - Entire packet 1 - Each buffer */
#घोषणा CPPI5_INFO2_HDESC_RETPOLICY		BIT(18)
/*
 * Early Return:
 * 0 = desc poपूर्णांकers should be वापसed after all पढ़ोs have been completed
 * 1 = desc poपूर्णांकers should be वापसed immediately upon fetching
 * the descriptor and beginning to transfer data.
 */
#घोषणा CPPI5_INFO2_HDESC_EARLYRET		BIT(17)
/*
 * Return Push Policy:
 * 0 = Descriptor must be वापसed to tail of queue
 * 1 = Descriptor must be वापसed to head of queue
 */
#घोषणा CPPI5_INFO2_DESC_RETPUSHPOLICY		BIT(16)
#घोषणा CPPI5_INFO2_DESC_RETP_MASK		GENMASK(18, 16)

#घोषणा CPPI5_INFO2_DESC_RETQ_SHIFT		(0)
#घोषणा CPPI5_INFO2_DESC_RETQ_MASK		GENMASK(15, 0)

#घोषणा CPPI5_INFO3_DESC_SRCTAG_SHIFT		(16U)
#घोषणा CPPI5_INFO3_DESC_SRCTAG_MASK		GENMASK(31, 16)
#घोषणा CPPI5_INFO3_DESC_DSTTAG_SHIFT		(0)
#घोषणा CPPI5_INFO3_DESC_DSTTAG_MASK		GENMASK(15, 0)

#घोषणा CPPI5_BUFINFO1_HDESC_DATA_LEN_SHIFT	(0)
#घोषणा CPPI5_BUFINFO1_HDESC_DATA_LEN_MASK	GENMASK(27, 0)

#घोषणा CPPI5_OBUFINFO0_HDESC_BUF_LEN_SHIFT	(0)
#घोषणा CPPI5_OBUFINFO0_HDESC_BUF_LEN_MASK	GENMASK(27, 0)

/**
 * काष्ठा cppi5_desc_epib_t - Host Packet Descriptor Extended Packet Info Block
 * @बारtamp:		word 0: application specअगरic बारtamp
 * @sw_info0:		word 1: Software Info 0
 * @sw_info1:		word 1: Software Info 1
 * @sw_info2:		word 1: Software Info 2
 */
काष्ठा cppi5_desc_epib_t अणु
	u32 बारtamp;	/* w0: application specअगरic बारtamp */
	u32 sw_info0;	/* w1: Software Info 0 */
	u32 sw_info1;	/* w2: Software Info 1 */
	u32 sw_info2;	/* w3: Software Info 2 */
पूर्ण;

/**
 * काष्ठा cppi5_monolithic_desc_t - Monolithic-mode packet descriptor
 * @hdr:		Descriptor header
 * @epib[0]:		Extended Packet Info Data (optional, 4 words), and/or
 *			Protocol Specअगरic Data (optional, 0-128 bytes in
 *			multiples of 4), and/or
 *			Other Software Data (0-N bytes, optional)
 */
काष्ठा cppi5_monolithic_desc_t अणु
	काष्ठा cppi5_desc_hdr_t hdr;
	u32 epib[];
पूर्ण;

#घोषणा CPPI5_INFO2_MDESC_DATA_OFFSET_SHIFT	(18U)
#घोषणा CPPI5_INFO2_MDESC_DATA_OFFSET_MASK	GENMASK(26, 18)

/*
 * Reload Count:
 * 0 = Finish the packet and place the descriptor back on the वापस queue
 * 1-0x1ff = Vector to the Reload Index and resume processing
 * 0x1ff indicates perpetual loop, infinite reload until the channel is stopped
 */
#घोषणा CPPI5_INFO0_TRDESC_RLDCNT_SHIFT		(20U)
#घोषणा CPPI5_INFO0_TRDESC_RLDCNT_MASK		GENMASK(28, 20)
#घोषणा CPPI5_INFO0_TRDESC_RLDCNT_MAX		(0x1ff)
#घोषणा CPPI5_INFO0_TRDESC_RLDCNT_INFINITE	CPPI5_INFO0_TRDESC_RLDCNT_MAX
#घोषणा CPPI5_INFO0_TRDESC_RLDIDX_SHIFT		(14U)
#घोषणा CPPI5_INFO0_TRDESC_RLDIDX_MASK		GENMASK(19, 14)
#घोषणा CPPI5_INFO0_TRDESC_RLDIDX_MAX		(0x3f)
#घोषणा CPPI5_INFO0_TRDESC_LASTIDX_SHIFT	(0)
#घोषणा CPPI5_INFO0_TRDESC_LASTIDX_MASK		GENMASK(13, 0)

#घोषणा CPPI5_INFO1_TRDESC_RECSIZE_SHIFT	(24U)
#घोषणा CPPI5_INFO1_TRDESC_RECSIZE_MASK		GENMASK(26, 24)
#घोषणा   CPPI5_INFO1_TRDESC_RECSIZE_VAL_16B	(0)
#घोषणा   CPPI5_INFO1_TRDESC_RECSIZE_VAL_32B	(1U)
#घोषणा   CPPI5_INFO1_TRDESC_RECSIZE_VAL_64B	(2U)
#घोषणा   CPPI5_INFO1_TRDESC_RECSIZE_VAL_128B	(3U)

अटल अंतरभूत व्योम cppi5_desc_dump(व्योम *desc, u32 size)
अणु
	prपूर्णांक_hex_dump(KERN_ERR, "dump udmap_desc: ", DUMP_PREFIX_NONE,
		       32, 4, desc, size, false);
पूर्ण

#घोषणा CPPI5_TDCM_MARKER			(0x1)
/**
 * cppi5_desc_is_tdcm - check अगर the paddr indicates Tearकरोwn Complete Message
 * @paddr: Physical address of the packet popped from the ring
 *
 * Returns true अगर the address indicates TDCM
 */
अटल अंतरभूत bool cppi5_desc_is_tdcm(dma_addr_t paddr)
अणु
	वापस (paddr & CPPI5_TDCM_MARKER) ? true : false;
पूर्ण

/**
 * cppi5_desc_get_type - get descriptor type
 * @desc_hdr: packet descriptor/TR header
 *
 * Returns descriptor type:
 * CPPI5_INFO0_DESC_TYPE_VAL_HOST
 * CPPI5_INFO0_DESC_TYPE_VAL_MONO
 * CPPI5_INFO0_DESC_TYPE_VAL_TR
 */
अटल अंतरभूत u32 cppi5_desc_get_type(काष्ठा cppi5_desc_hdr_t *desc_hdr)
अणु
	वापस (desc_hdr->pkt_info0 & CPPI5_INFO0_HDESC_TYPE_MASK) >>
		CPPI5_INFO0_HDESC_TYPE_SHIFT;
पूर्ण

/**
 * cppi5_desc_get_errflags - get Error Flags from Desc
 * @desc_hdr: packet/TR descriptor header
 *
 * Returns Error Flags from Packet/TR Descriptor
 */
अटल अंतरभूत u32 cppi5_desc_get_errflags(काष्ठा cppi5_desc_hdr_t *desc_hdr)
अणु
	वापस (desc_hdr->pkt_info1 & CPPI5_INFO1_DESC_PKTERROR_MASK) >>
		CPPI5_INFO1_DESC_PKTERROR_SHIFT;
पूर्ण

/**
 * cppi5_desc_get_pktids - get Packet and Flow ids from Desc
 * @desc_hdr: packet/TR descriptor header
 * @pkt_id: Packet ID
 * @flow_id: Flow ID
 *
 * Returns Packet and Flow ids from packet/TR descriptor
 */
अटल अंतरभूत व्योम cppi5_desc_get_pktids(काष्ठा cppi5_desc_hdr_t *desc_hdr,
					 u32 *pkt_id, u32 *flow_id)
अणु
	*pkt_id = (desc_hdr->pkt_info1 & CPPI5_INFO1_DESC_PKTID_MASK) >>
		   CPPI5_INFO1_DESC_PKTID_SHIFT;
	*flow_id = (desc_hdr->pkt_info1 & CPPI5_INFO1_DESC_FLOWID_MASK) >>
		    CPPI5_INFO1_DESC_FLOWID_SHIFT;
पूर्ण

/**
 * cppi5_desc_set_pktids - set Packet and Flow ids in Desc
 * @desc_hdr: packet/TR descriptor header
 * @pkt_id: Packet ID
 * @flow_id: Flow ID
 */
अटल अंतरभूत व्योम cppi5_desc_set_pktids(काष्ठा cppi5_desc_hdr_t *desc_hdr,
					 u32 pkt_id, u32 flow_id)
अणु
	desc_hdr->pkt_info1 &= ~(CPPI5_INFO1_DESC_PKTID_MASK |
				 CPPI5_INFO1_DESC_FLOWID_MASK);
	desc_hdr->pkt_info1 |= (pkt_id << CPPI5_INFO1_DESC_PKTID_SHIFT) &
				CPPI5_INFO1_DESC_PKTID_MASK;
	desc_hdr->pkt_info1 |= (flow_id << CPPI5_INFO1_DESC_FLOWID_SHIFT) &
				CPPI5_INFO1_DESC_FLOWID_MASK;
पूर्ण

/**
 * cppi5_desc_set_retpolicy - set Packet Return Policy in Desc
 * @desc_hdr: packet/TR descriptor header
 * @flags: fags, supported values
 *  CPPI5_INFO2_HDESC_RETPOLICY
 *  CPPI5_INFO2_HDESC_EARLYRET
 *  CPPI5_INFO2_DESC_RETPUSHPOLICY
 * @वापस_ring_id: Packet Return Queue/Ring id, value 0xFFFF reserved
 */
अटल अंतरभूत व्योम cppi5_desc_set_retpolicy(काष्ठा cppi5_desc_hdr_t *desc_hdr,
					    u32 flags, u32 वापस_ring_id)
अणु
	desc_hdr->pkt_info2 &= ~(CPPI5_INFO2_DESC_RETP_MASK |
				 CPPI5_INFO2_DESC_RETQ_MASK);
	desc_hdr->pkt_info2 |= flags & CPPI5_INFO2_DESC_RETP_MASK;
	desc_hdr->pkt_info2 |= वापस_ring_id & CPPI5_INFO2_DESC_RETQ_MASK;
पूर्ण

/**
 * cppi5_desc_get_tags_ids - get Packet Src/Dst Tags from Desc
 * @desc_hdr: packet/TR descriptor header
 * @src_tag_id: Source Tag
 * @dst_tag_id: Dest Tag
 *
 * Returns Packet Src/Dst Tags from packet/TR descriptor
 */
अटल अंतरभूत व्योम cppi5_desc_get_tags_ids(काष्ठा cppi5_desc_hdr_t *desc_hdr,
					   u32 *src_tag_id, u32 *dst_tag_id)
अणु
	अगर (src_tag_id)
		*src_tag_id = (desc_hdr->src_dst_tag &
			      CPPI5_INFO3_DESC_SRCTAG_MASK) >>
			      CPPI5_INFO3_DESC_SRCTAG_SHIFT;
	अगर (dst_tag_id)
		*dst_tag_id = desc_hdr->src_dst_tag &
			      CPPI5_INFO3_DESC_DSTTAG_MASK;
पूर्ण

/**
 * cppi5_desc_set_tags_ids - set Packet Src/Dst Tags in HDesc
 * @desc_hdr: packet/TR descriptor header
 * @src_tag_id: Source Tag
 * @dst_tag_id: Dest Tag
 *
 * Returns Packet Src/Dst Tags from packet/TR descriptor
 */
अटल अंतरभूत व्योम cppi5_desc_set_tags_ids(काष्ठा cppi5_desc_hdr_t *desc_hdr,
					   u32 src_tag_id, u32 dst_tag_id)
अणु
	desc_hdr->src_dst_tag = (src_tag_id << CPPI5_INFO3_DESC_SRCTAG_SHIFT) &
				CPPI5_INFO3_DESC_SRCTAG_MASK;
	desc_hdr->src_dst_tag |= dst_tag_id & CPPI5_INFO3_DESC_DSTTAG_MASK;
पूर्ण

/**
 * cppi5_hdesc_calc_size - Calculate Host Packet Descriptor size
 * @epib: is EPIB present
 * @psdata_size: PSDATA size
 * @sw_data_size: SWDATA size
 *
 * Returns required Host Packet Descriptor size
 * 0 - अगर PSDATA > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE
 */
अटल अंतरभूत u32 cppi5_hdesc_calc_size(bool epib, u32 psdata_size,
					u32 sw_data_size)
अणु
	u32 desc_size;

	अगर (psdata_size > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE)
		वापस 0;

	desc_size = माप(काष्ठा cppi5_host_desc_t) + psdata_size +
		    sw_data_size;

	अगर (epib)
		desc_size += CPPI5_INFO0_HDESC_EPIB_SIZE;

	वापस ALIGN(desc_size, CPPI5_DESC_MIN_ALIGN);
पूर्ण

/**
 * cppi5_hdesc_init - Init Host Packet Descriptor size
 * @desc: Host packet descriptor
 * @flags: supported values
 *	CPPI5_INFO0_HDESC_EPIB_PRESENT
 *	CPPI5_INFO0_HDESC_PSINFO_LOCATION
 * @psdata_size: PSDATA size
 *
 * Returns required Host Packet Descriptor size
 * 0 - अगर PSDATA > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE
 */
अटल अंतरभूत व्योम cppi5_hdesc_init(काष्ठा cppi5_host_desc_t *desc, u32 flags,
				    u32 psdata_size)
अणु
	desc->hdr.pkt_info0 = (CPPI5_INFO0_DESC_TYPE_VAL_HOST <<
			       CPPI5_INFO0_HDESC_TYPE_SHIFT) | (flags);
	desc->hdr.pkt_info0 |= ((psdata_size >> 2) <<
				CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT) &
				CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
	desc->next_desc = 0;
पूर्ण

/**
 * cppi5_hdesc_update_flags - Replace descriptor flags
 * @desc: Host packet descriptor
 * @flags: supported values
 *	CPPI5_INFO0_HDESC_EPIB_PRESENT
 *	CPPI5_INFO0_HDESC_PSINFO_LOCATION
 */
अटल अंतरभूत व्योम cppi5_hdesc_update_flags(काष्ठा cppi5_host_desc_t *desc,
					    u32 flags)
अणु
	desc->hdr.pkt_info0 &= ~(CPPI5_INFO0_HDESC_EPIB_PRESENT |
				 CPPI5_INFO0_HDESC_PSINFO_LOCATION);
	desc->hdr.pkt_info0 |= flags;
पूर्ण

/**
 * cppi5_hdesc_update_psdata_size - Replace PSdata size
 * @desc: Host packet descriptor
 * @psdata_size: PSDATA size
 */
अटल अंतरभूत व्योम
cppi5_hdesc_update_psdata_size(काष्ठा cppi5_host_desc_t *desc, u32 psdata_size)
अणु
	desc->hdr.pkt_info0 &= ~CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
	desc->hdr.pkt_info0 |= ((psdata_size >> 2) <<
				CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT) &
				CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
पूर्ण

/**
 * cppi5_hdesc_get_psdata_size - get PSdata size in bytes
 * @desc: Host packet descriptor
 */
अटल अंतरभूत u32 cppi5_hdesc_get_psdata_size(काष्ठा cppi5_host_desc_t *desc)
अणु
	u32 psdata_size = 0;

	अगर (!(desc->hdr.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_LOCATION))
		psdata_size = (desc->hdr.pkt_info0 &
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	वापस (psdata_size << 2);
पूर्ण

/**
 * cppi5_hdesc_get_pktlen - get Packet Length from HDesc
 * @desc: Host packet descriptor
 *
 * Returns Packet Length from Host Packet Descriptor
 */
अटल अंतरभूत u32 cppi5_hdesc_get_pktlen(काष्ठा cppi5_host_desc_t *desc)
अणु
	वापस (desc->hdr.pkt_info0 & CPPI5_INFO0_HDESC_PKTLEN_MASK);
पूर्ण

/**
 * cppi5_hdesc_set_pktlen - set Packet Length in HDesc
 * @desc: Host packet descriptor
 */
अटल अंतरभूत व्योम cppi5_hdesc_set_pktlen(काष्ठा cppi5_host_desc_t *desc,
					  u32 pkt_len)
अणु
	desc->hdr.pkt_info0 &= ~CPPI5_INFO0_HDESC_PKTLEN_MASK;
	desc->hdr.pkt_info0 |= (pkt_len & CPPI5_INFO0_HDESC_PKTLEN_MASK);
पूर्ण

/**
 * cppi5_hdesc_get_psflags - get Protocol Specअगरic Flags from HDesc
 * @desc: Host packet descriptor
 *
 * Returns Protocol Specअगरic Flags from Host Packet Descriptor
 */
अटल अंतरभूत u32 cppi5_hdesc_get_psflags(काष्ठा cppi5_host_desc_t *desc)
अणु
	वापस (desc->hdr.pkt_info1 & CPPI5_INFO1_HDESC_PSFLGS_MASK) >>
		CPPI5_INFO1_HDESC_PSFLGS_SHIFT;
पूर्ण

/**
 * cppi5_hdesc_set_psflags - set Protocol Specअगरic Flags in HDesc
 * @desc: Host packet descriptor
 */
अटल अंतरभूत व्योम cppi5_hdesc_set_psflags(काष्ठा cppi5_host_desc_t *desc,
					   u32 ps_flags)
अणु
	desc->hdr.pkt_info1 &= ~CPPI5_INFO1_HDESC_PSFLGS_MASK;
	desc->hdr.pkt_info1 |= (ps_flags <<
				CPPI5_INFO1_HDESC_PSFLGS_SHIFT) &
				CPPI5_INFO1_HDESC_PSFLGS_MASK;
पूर्ण

/**
 * cppi5_hdesc_get_errflags - get Packet Type from HDesc
 * @desc: Host packet descriptor
 */
अटल अंतरभूत u32 cppi5_hdesc_get_pkttype(काष्ठा cppi5_host_desc_t *desc)
अणु
	वापस (desc->hdr.pkt_info2 & CPPI5_INFO2_HDESC_PKTTYPE_MASK) >>
		CPPI5_INFO2_HDESC_PKTTYPE_SHIFT;
पूर्ण

/**
 * cppi5_hdesc_get_errflags - set Packet Type in HDesc
 * @desc: Host packet descriptor
 * @pkt_type: Packet Type
 */
अटल अंतरभूत व्योम cppi5_hdesc_set_pkttype(काष्ठा cppi5_host_desc_t *desc,
					   u32 pkt_type)
अणु
	desc->hdr.pkt_info2 &= ~CPPI5_INFO2_HDESC_PKTTYPE_MASK;
	desc->hdr.pkt_info2 |=
			(pkt_type << CPPI5_INFO2_HDESC_PKTTYPE_SHIFT) &
			 CPPI5_INFO2_HDESC_PKTTYPE_MASK;
पूर्ण

/**
 * cppi5_hdesc_attach_buf - attach buffer to HDesc
 * @desc: Host packet descriptor
 * @buf: Buffer physical address
 * @buf_data_len: Buffer length
 * @obuf: Original Buffer physical address
 * @obuf_len: Original Buffer length
 *
 * Attaches buffer to Host Packet Descriptor
 */
अटल अंतरभूत व्योम cppi5_hdesc_attach_buf(काष्ठा cppi5_host_desc_t *desc,
					  dma_addr_t buf, u32 buf_data_len,
					  dma_addr_t obuf, u32 obuf_len)
अणु
	desc->buf_ptr = buf;
	desc->buf_info1 = buf_data_len & CPPI5_BUFINFO1_HDESC_DATA_LEN_MASK;
	desc->org_buf_ptr = obuf;
	desc->org_buf_len = obuf_len & CPPI5_OBUFINFO0_HDESC_BUF_LEN_MASK;
पूर्ण

अटल अंतरभूत व्योम cppi5_hdesc_get_obuf(काष्ठा cppi5_host_desc_t *desc,
					dma_addr_t *obuf, u32 *obuf_len)
अणु
	*obuf = desc->org_buf_ptr;
	*obuf_len = desc->org_buf_len & CPPI5_OBUFINFO0_HDESC_BUF_LEN_MASK;
पूर्ण

अटल अंतरभूत व्योम cppi5_hdesc_reset_to_original(काष्ठा cppi5_host_desc_t *desc)
अणु
	desc->buf_ptr = desc->org_buf_ptr;
	desc->buf_info1 = desc->org_buf_len;
पूर्ण

/**
 * cppi5_hdesc_link_hbdesc - link Host Buffer Descriptor to HDesc
 * @desc: Host Packet Descriptor
 * @buf_desc: Host Buffer Descriptor physical address
 *
 * add and link Host Buffer Descriptor to HDesc
 */
अटल अंतरभूत व्योम cppi5_hdesc_link_hbdesc(काष्ठा cppi5_host_desc_t *desc,
					   dma_addr_t hbuf_desc)
अणु
	desc->next_desc = hbuf_desc;
पूर्ण

अटल अंतरभूत dma_addr_t
cppi5_hdesc_get_next_hbdesc(काष्ठा cppi5_host_desc_t *desc)
अणु
	वापस (dma_addr_t)desc->next_desc;
पूर्ण

अटल अंतरभूत व्योम cppi5_hdesc_reset_hbdesc(काष्ठा cppi5_host_desc_t *desc)
अणु
	desc->hdr = (काष्ठा cppi5_desc_hdr_t) अणु 0 पूर्ण;
	desc->next_desc = 0;
पूर्ण

/**
 * cppi5_hdesc_epib_present -  check अगर EPIB present
 * @desc_hdr: packet descriptor/TR header
 *
 * Returns true अगर EPIB present in the packet
 */
अटल अंतरभूत bool cppi5_hdesc_epib_present(काष्ठा cppi5_desc_hdr_t *desc_hdr)
अणु
	वापस !!(desc_hdr->pkt_info0 & CPPI5_INFO0_HDESC_EPIB_PRESENT);
पूर्ण

/**
 * cppi5_hdesc_get_psdata -  Get poपूर्णांकer on PSDATA
 * @desc: Host packet descriptor
 *
 * Returns poपूर्णांकer on PSDATA in HDesc.
 * शून्य - अगर ps_data placed at the start of data buffer.
 */
अटल अंतरभूत व्योम *cppi5_hdesc_get_psdata(काष्ठा cppi5_host_desc_t *desc)
अणु
	u32 psdata_size;
	व्योम *psdata;

	अगर (desc->hdr.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_LOCATION)
		वापस शून्य;

	psdata_size = (desc->hdr.pkt_info0 &
		       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
		       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	अगर (!psdata_size)
		वापस शून्य;

	psdata = &desc->epib;

	अगर (cppi5_hdesc_epib_present(&desc->hdr))
		psdata += CPPI5_INFO0_HDESC_EPIB_SIZE;

	वापस psdata;
पूर्ण

/**
 * cppi5_hdesc_get_swdata -  Get poपूर्णांकer on swdata
 * @desc: Host packet descriptor
 *
 * Returns poपूर्णांकer on SWDATA in HDesc.
 * NOTE. It's caller responsibility to be sure hdesc actually has swdata.
 */
अटल अंतरभूत व्योम *cppi5_hdesc_get_swdata(काष्ठा cppi5_host_desc_t *desc)
अणु
	u32 psdata_size = 0;
	व्योम *swdata;

	अगर (!(desc->hdr.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_LOCATION))
		psdata_size = (desc->hdr.pkt_info0 &
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	swdata = &desc->epib;

	अगर (cppi5_hdesc_epib_present(&desc->hdr))
		swdata += CPPI5_INFO0_HDESC_EPIB_SIZE;

	swdata += (psdata_size << 2);

	वापस swdata;
पूर्ण

/* ================================== TR ================================== */

#घोषणा CPPI5_TR_TYPE_SHIFT			(0U)
#घोषणा CPPI5_TR_TYPE_MASK			GENMASK(3, 0)
#घोषणा CPPI5_TR_STATIC				BIT(4)
#घोषणा CPPI5_TR_WAIT				BIT(5)
#घोषणा CPPI5_TR_EVENT_SIZE_SHIFT		(6U)
#घोषणा CPPI5_TR_EVENT_SIZE_MASK		GENMASK(7, 6)
#घोषणा CPPI5_TR_TRIGGER0_SHIFT			(8U)
#घोषणा CPPI5_TR_TRIGGER0_MASK			GENMASK(9, 8)
#घोषणा CPPI5_TR_TRIGGER0_TYPE_SHIFT		(10U)
#घोषणा CPPI5_TR_TRIGGER0_TYPE_MASK		GENMASK(11, 10)
#घोषणा CPPI5_TR_TRIGGER1_SHIFT			(12U)
#घोषणा CPPI5_TR_TRIGGER1_MASK			GENMASK(13, 12)
#घोषणा CPPI5_TR_TRIGGER1_TYPE_SHIFT		(14U)
#घोषणा CPPI5_TR_TRIGGER1_TYPE_MASK		GENMASK(15, 14)
#घोषणा CPPI5_TR_CMD_ID_SHIFT			(16U)
#घोषणा CPPI5_TR_CMD_ID_MASK			GENMASK(23, 16)
#घोषणा CPPI5_TR_CSF_FLAGS_SHIFT		(24U)
#घोषणा CPPI5_TR_CSF_FLAGS_MASK			GENMASK(31, 24)
#घोषणा   CPPI5_TR_CSF_SA_INसूचीECT		BIT(0)
#घोषणा   CPPI5_TR_CSF_DA_INसूचीECT		BIT(1)
#घोषणा   CPPI5_TR_CSF_SUPR_EVT			BIT(2)
#घोषणा   CPPI5_TR_CSF_EOL_ADV_SHIFT		(4U)
#घोषणा   CPPI5_TR_CSF_EOL_ADV_MASK		GENMASK(6, 4)
#घोषणा   CPPI5_TR_CSF_EOP			BIT(7)

/**
 * क्रमागत cppi5_tr_types - TR types
 * @CPPI5_TR_TYPE0:	One dimensional data move
 * @CPPI5_TR_TYPE1:	Two dimensional data move
 * @CPPI5_TR_TYPE2:	Three dimensional data move
 * @CPPI5_TR_TYPE3:	Four dimensional data move
 * @CPPI5_TR_TYPE4:	Four dimensional data move with data क्रमmatting
 * @CPPI5_TR_TYPE5:	Four dimensional Cache Warm
 * @CPPI5_TR_TYPE8:	Four Dimensional Block Move
 * @CPPI5_TR_TYPE9:	Four Dimensional Block Move with Repacking
 * @CPPI5_TR_TYPE10:	Two Dimensional Block Move
 * @CPPI5_TR_TYPE11:	Two Dimensional Block Move with Repacking
 * @CPPI5_TR_TYPE15:	Four Dimensional Block Move with Repacking and
 *			Indirection
 */
क्रमागत cppi5_tr_types अणु
	CPPI5_TR_TYPE0 = 0,
	CPPI5_TR_TYPE1,
	CPPI5_TR_TYPE2,
	CPPI5_TR_TYPE3,
	CPPI5_TR_TYPE4,
	CPPI5_TR_TYPE5,
	/* type6-7: Reserved */
	CPPI5_TR_TYPE8 = 8,
	CPPI5_TR_TYPE9,
	CPPI5_TR_TYPE10,
	CPPI5_TR_TYPE11,
	/* type12-14: Reserved */
	CPPI5_TR_TYPE15 = 15,
	CPPI5_TR_TYPE_MAX
पूर्ण;

/**
 * क्रमागत cppi5_tr_event_size - TR Flags EVENT_SIZE field specअगरies when an event
 *			      is generated क्रम each TR.
 * @CPPI5_TR_EVENT_SIZE_COMPLETION:	When TR is complete and all status क्रम
 * 					the TR has been received
 * @CPPI5_TR_EVENT_SIZE_ICNT1_DEC:	Type 0: when the last data transaction
 *					is sent क्रम the TR
 *					Type 1-11: when ICNT1 is decremented
 * @CPPI5_TR_EVENT_SIZE_ICNT2_DEC:	Type 0-1,10-11: when the last data
 *					transaction is sent क्रम the TR
 *					All other types: when ICNT2 is
 *					decremented
 * @CPPI5_TR_EVENT_SIZE_ICNT3_DEC:	Type 0-2,10-11: when the last data
 *					transaction is sent क्रम the TR
 *					All other types: when ICNT3 is
 *					decremented
 */
क्रमागत cppi5_tr_event_size अणु
	CPPI5_TR_EVENT_SIZE_COMPLETION,
	CPPI5_TR_EVENT_SIZE_ICNT1_DEC,
	CPPI5_TR_EVENT_SIZE_ICNT2_DEC,
	CPPI5_TR_EVENT_SIZE_ICNT3_DEC,
	CPPI5_TR_EVENT_SIZE_MAX
पूर्ण;

/**
 * क्रमागत cppi5_tr_trigger - TR Flags TRIGGERx field specअगरies the type of trigger
 *			   used to enable the TR to transfer data as specअगरied
 *			   by TRIGGERx_TYPE field.
 * @CPPI5_TR_TRIGGER_NONE:		No trigger
 * @CPPI5_TR_TRIGGER_GLOBAL0:		Global trigger 0
 * @CPPI5_TR_TRIGGER_GLOBAL1:		Global trigger 1
 * @CPPI5_TR_TRIGGER_LOCAL_EVENT:	Local Event
 */
क्रमागत cppi5_tr_trigger अणु
	CPPI5_TR_TRIGGER_NONE,
	CPPI5_TR_TRIGGER_GLOBAL0,
	CPPI5_TR_TRIGGER_GLOBAL1,
	CPPI5_TR_TRIGGER_LOCAL_EVENT,
	CPPI5_TR_TRIGGER_MAX
पूर्ण;

/**
 * क्रमागत cppi5_tr_trigger_type - TR Flags TRIGGERx_TYPE field specअगरies the type
 *				of data transfer that will be enabled by
 *				receiving a trigger as specअगरied by TRIGGERx.
 * @CPPI5_TR_TRIGGER_TYPE_ICNT1_DEC:	The second inner most loop (ICNT1) will
 *					be decremented by 1
 * @CPPI5_TR_TRIGGER_TYPE_ICNT2_DEC:	The third inner most loop (ICNT2) will
 *					be decremented by 1
 * @CPPI5_TR_TRIGGER_TYPE_ICNT3_DEC:	The outer most loop (ICNT3) will be
 *					decremented by 1
 * @CPPI5_TR_TRIGGER_TYPE_ALL:		The entire TR will be allowed to
 *					complete
 */
क्रमागत cppi5_tr_trigger_type अणु
	CPPI5_TR_TRIGGER_TYPE_ICNT1_DEC,
	CPPI5_TR_TRIGGER_TYPE_ICNT2_DEC,
	CPPI5_TR_TRIGGER_TYPE_ICNT3_DEC,
	CPPI5_TR_TRIGGER_TYPE_ALL,
	CPPI5_TR_TRIGGER_TYPE_MAX
पूर्ण;

प्रकार u32 cppi5_tr_flags_t;

/**
 * काष्ठा cppi5_tr_type0_t - Type 0 (One dimensional data move) TR (16 byte)
 * @flags:		TR flags (type, triggers, event, configuration)
 * @icnt0:		Total loop iteration count क्रम level 0 (innermost)
 * @_reserved:		Not used
 * @addr:		Starting address क्रम the source data or destination data
 */
काष्ठा cppi5_tr_type0_t अणु
	cppi5_tr_flags_t flags;
	u16 icnt0;
	u16 _reserved;
	u64 addr;
पूर्ण __aligned(16) __packed;

/**
 * काष्ठा cppi5_tr_type1_t - Type 1 (Two dimensional data move) TR (32 byte)
 * @flags:		TR flags (type, triggers, event, configuration)
 * @icnt0:		Total loop iteration count क्रम level 0 (innermost)
 * @icnt1:		Total loop iteration count क्रम level 1
 * @addr:		Starting address क्रम the source data or destination data
 * @dim1:		Signed dimension क्रम loop level 1
 */
काष्ठा cppi5_tr_type1_t अणु
	cppi5_tr_flags_t flags;
	u16 icnt0;
	u16 icnt1;
	u64 addr;
	s32 dim1;
पूर्ण __aligned(32) __packed;

/**
 * काष्ठा cppi5_tr_type2_t - Type 2 (Three dimensional data move) TR (32 byte)
 * @flags:		TR flags (type, triggers, event, configuration)
 * @icnt0:		Total loop iteration count क्रम level 0 (innermost)
 * @icnt1:		Total loop iteration count क्रम level 1
 * @addr:		Starting address क्रम the source data or destination data
 * @dim1:		Signed dimension क्रम loop level 1
 * @icnt2:		Total loop iteration count क्रम level 2
 * @_reserved:		Not used
 * @dim2:		Signed dimension क्रम loop level 2
 */
काष्ठा cppi5_tr_type2_t अणु
	cppi5_tr_flags_t flags;
	u16 icnt0;
	u16 icnt1;
	u64 addr;
	s32 dim1;
	u16 icnt2;
	u16 _reserved;
	s32 dim2;
पूर्ण __aligned(32) __packed;

/**
 * काष्ठा cppi5_tr_type3_t - Type 3 (Four dimensional data move) TR (32 byte)
 * @flags:		TR flags (type, triggers, event, configuration)
 * @icnt0:		Total loop iteration count क्रम level 0 (innermost)
 * @icnt1:		Total loop iteration count क्रम level 1
 * @addr:		Starting address क्रम the source data or destination data
 * @dim1:		Signed dimension क्रम loop level 1
 * @icnt2:		Total loop iteration count क्रम level 2
 * @icnt3:		Total loop iteration count क्रम level 3 (outermost)
 * @dim2:		Signed dimension क्रम loop level 2
 * @dim3:		Signed dimension क्रम loop level 3
 */
काष्ठा cppi5_tr_type3_t अणु
	cppi5_tr_flags_t flags;
	u16 icnt0;
	u16 icnt1;
	u64 addr;
	s32 dim1;
	u16 icnt2;
	u16 icnt3;
	s32 dim2;
	s32 dim3;
पूर्ण __aligned(32) __packed;

/**
 * काष्ठा cppi5_tr_type15_t - Type 15 (Four Dimensional Block Copy with
 *			      Repacking and Indirection Support) TR (64 byte)
 * @flags:		TR flags (type, triggers, event, configuration)
 * @icnt0:		Total loop iteration count क्रम level 0 (innermost) क्रम
 *			source
 * @icnt1:		Total loop iteration count क्रम level 1 क्रम source
 * @addr:		Starting address क्रम the source data
 * @dim1:		Signed dimension क्रम loop level 1 क्रम source
 * @icnt2:		Total loop iteration count क्रम level 2 क्रम source
 * @icnt3:		Total loop iteration count क्रम level 3 (outermost) क्रम
 *			source
 * @dim2:		Signed dimension क्रम loop level 2 क्रम source
 * @dim3:		Signed dimension क्रम loop level 3 क्रम source
 * @_reserved:		Not used
 * @ddim1:		Signed dimension क्रम loop level 1 क्रम destination
 * @daddr:		Starting address क्रम the destination data
 * @ddim2:		Signed dimension क्रम loop level 2 क्रम destination
 * @ddim3:		Signed dimension क्रम loop level 3 क्रम destination
 * @dicnt0:		Total loop iteration count क्रम level 0 (innermost) क्रम
 *			destination
 * @dicnt1:		Total loop iteration count क्रम level 1 क्रम destination
 * @dicnt2:		Total loop iteration count क्रम level 2 क्रम destination
 * @sicnt3:		Total loop iteration count क्रम level 3 (outermost) क्रम
 *			destination
 */
काष्ठा cppi5_tr_type15_t अणु
	cppi5_tr_flags_t flags;
	u16 icnt0;
	u16 icnt1;
	u64 addr;
	s32 dim1;
	u16 icnt2;
	u16 icnt3;
	s32 dim2;
	s32 dim3;
	u32 _reserved;
	s32 ddim1;
	u64 daddr;
	s32 ddim2;
	s32 ddim3;
	u16 dicnt0;
	u16 dicnt1;
	u16 dicnt2;
	u16 dicnt3;
पूर्ण __aligned(64) __packed;

/**
 * काष्ठा cppi5_tr_resp_t - TR response record
 * @status:		Status type and info
 * @_reserved:		Not used
 * @cmd_id:		Command ID क्रम the TR क्रम TR identअगरication
 * @flags:		Configuration Specअगरic Flags
 */
काष्ठा cppi5_tr_resp_t अणु
	u8 status;
	u8 _reserved;
	u8 cmd_id;
	u8 flags;
पूर्ण __packed;

#घोषणा CPPI5_TR_RESPONSE_STATUS_TYPE_SHIFT	(0U)
#घोषणा CPPI5_TR_RESPONSE_STATUS_TYPE_MASK	GENMASK(3, 0)
#घोषणा CPPI5_TR_RESPONSE_STATUS_INFO_SHIFT	(4U)
#घोषणा CPPI5_TR_RESPONSE_STATUS_INFO_MASK	GENMASK(7, 4)
#घोषणा CPPI5_TR_RESPONSE_CMDID_SHIFT		(16U)
#घोषणा CPPI5_TR_RESPONSE_CMDID_MASK		GENMASK(23, 16)
#घोषणा CPPI5_TR_RESPONSE_CFG_SPECIFIC_SHIFT	(24U)
#घोषणा CPPI5_TR_RESPONSE_CFG_SPECIFIC_MASK	GENMASK(31, 24)

/**
 * क्रमागत cppi5_tr_resp_status_type - TR Response Status Type field is used to
 *				    determine what type of status is being
 *				    वापसed.
 * @CPPI5_TR_RESPONSE_STATUS_NONE:		No error, completion: completed
 * @CPPI5_TR_RESPONSE_STATUS_TRANSFER_ERR:	Transfer Error, completion: none
 *						or partially completed
 * @CPPI5_TR_RESPONSE_STATUS_ABORTED_ERR:	Aborted Error, completion: none
 *						or partially completed
 * @CPPI5_TR_RESPONSE_STATUS_SUBMISSION_ERR:	Submission Error, completion:
 *						none
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_ERR:	Unsupported Error, completion:
 *						none
 * @CPPI5_TR_RESPONSE_STATUS_TRANSFER_EXCEPTION: Transfer Exception, completion:
 *						partially completed
 * @CPPI5_TR_RESPONSE_STATUS__TEARDOWN_FLUSH:	Tearकरोwn Flush, completion: none
 */
क्रमागत cppi5_tr_resp_status_type अणु
	CPPI5_TR_RESPONSE_STATUS_NONE,
	CPPI5_TR_RESPONSE_STATUS_TRANSFER_ERR,
	CPPI5_TR_RESPONSE_STATUS_ABORTED_ERR,
	CPPI5_TR_RESPONSE_STATUS_SUBMISSION_ERR,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_ERR,
	CPPI5_TR_RESPONSE_STATUS_TRANSFER_EXCEPTION,
	CPPI5_TR_RESPONSE_STATUS__TEARDOWN_FLUSH,
	CPPI5_TR_RESPONSE_STATUS_MAX
पूर्ण;

/**
 * क्रमागत cppi5_tr_resp_status_submission - TR Response Status field values which
 *					  corresponds Submission Error
 * @CPPI5_TR_RESPONSE_STATUS_SUBMISSION_ICNT0:	ICNT0 was 0
 * @CPPI5_TR_RESPONSE_STATUS_SUBMISSION_FIFO_FULL: Channel FIFO was full when TR
 *						received
 * @CPPI5_TR_RESPONSE_STATUS_SUBMISSION_OWN:	Channel is not owned by the
 *						submitter
 */
क्रमागत cppi5_tr_resp_status_submission अणु
	CPPI5_TR_RESPONSE_STATUS_SUBMISSION_ICNT0,
	CPPI5_TR_RESPONSE_STATUS_SUBMISSION_FIFO_FULL,
	CPPI5_TR_RESPONSE_STATUS_SUBMISSION_OWN,
	CPPI5_TR_RESPONSE_STATUS_SUBMISSION_MAX
पूर्ण;

/**
 * क्रमागत cppi5_tr_resp_status_unsupported - TR Response Status field values which
 *					   corresponds Unsupported Error
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_TR_TYPE:	TR Type not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_STATIC:	STATIC not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_EOL:		EOL not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_CFG_SPECIFIC:	CONFIGURATION SPECIFIC
 *							not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_AMODE:		AMODE not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_ELTYPE:	ELTYPE not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_DFMT:		DFMT not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_SECTR:		SECTR not supported
 * @CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_AMODE_SPECIFIC: AMODE SPECIFIC field
 *							not supported
 */
क्रमागत cppi5_tr_resp_status_unsupported अणु
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_TR_TYPE,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_STATIC,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_EOL,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_CFG_SPECIFIC,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_AMODE,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_ELTYPE,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_DFMT,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_SECTR,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_AMODE_SPECIFIC,
	CPPI5_TR_RESPONSE_STATUS_UNSUPPORTED_MAX
पूर्ण;

/**
 * cppi5_trdesc_calc_size - Calculate TR Descriptor size
 * @tr_count: number of TR records
 * @tr_size: Nominal size of TR record (max) [16, 32, 64, 128]
 *
 * Returns required TR Descriptor size
 */
अटल अंतरभूत माप_प्रकार cppi5_trdesc_calc_size(u32 tr_count, u32 tr_size)
अणु
	/*
	 * The Size of a TR descriptor is:
	 * 1 x tr_size : the first 16 bytes is used by the packet info block +
	 * tr_count x tr_size : Transfer Request Records +
	 * tr_count x माप(काष्ठा cppi5_tr_resp_t) : Transfer Response Records
	 */
	वापस tr_size * (tr_count + 1) +
		माप(काष्ठा cppi5_tr_resp_t) * tr_count;
पूर्ण

/**
 * cppi5_trdesc_init - Init TR Descriptor
 * @desc: TR Descriptor
 * @tr_count: number of TR records
 * @tr_size: Nominal size of TR record (max) [16, 32, 64, 128]
 * @reload_idx: Absolute index to jump to on the 2nd and following passes
 *		through the TR packet.
 * @reload_count: Number of बार to jump from last entry to reload_idx. 0x1ff
 *		  indicates infinite looping.
 *
 * Init TR Descriptor
 */
अटल अंतरभूत व्योम cppi5_trdesc_init(काष्ठा cppi5_desc_hdr_t *desc_hdr,
				     u32 tr_count, u32 tr_size, u32 reload_idx,
				     u32 reload_count)
अणु
	desc_hdr->pkt_info0 = CPPI5_INFO0_DESC_TYPE_VAL_TR <<
			      CPPI5_INFO0_HDESC_TYPE_SHIFT;
	desc_hdr->pkt_info0 |=
			(reload_count << CPPI5_INFO0_TRDESC_RLDCNT_SHIFT) &
			CPPI5_INFO0_TRDESC_RLDCNT_MASK;
	desc_hdr->pkt_info0 |=
			(reload_idx << CPPI5_INFO0_TRDESC_RLDIDX_SHIFT) &
			CPPI5_INFO0_TRDESC_RLDIDX_MASK;
	desc_hdr->pkt_info0 |= (tr_count - 1) & CPPI5_INFO0_TRDESC_LASTIDX_MASK;

	desc_hdr->pkt_info1 |= ((ffs(tr_size >> 4) - 1) <<
				CPPI5_INFO1_TRDESC_RECSIZE_SHIFT) &
				CPPI5_INFO1_TRDESC_RECSIZE_MASK;
पूर्ण

/**
 * cppi5_tr_init - Init TR record
 * @flags: Poपूर्णांकer to the TR's flags
 * @type: TR type
 * @अटल_tr: TR is अटल
 * @रुको: Wait क्रम TR completion beक्रमe allow the next TR to start
 * @event_size: output event generation cfg
 * @cmd_id: TR identअगरier (application specअगरics)
 *
 * Init TR record
 */
अटल अंतरभूत व्योम cppi5_tr_init(cppi5_tr_flags_t *flags,
				 क्रमागत cppi5_tr_types type, bool अटल_tr,
				 bool रुको, क्रमागत cppi5_tr_event_size event_size,
				 u32 cmd_id)
अणु
	*flags = type;
	*flags |= (event_size << CPPI5_TR_EVENT_SIZE_SHIFT) &
		  CPPI5_TR_EVENT_SIZE_MASK;

	*flags |= (cmd_id << CPPI5_TR_CMD_ID_SHIFT) &
		  CPPI5_TR_CMD_ID_MASK;

	अगर (अटल_tr && (type == CPPI5_TR_TYPE8 || type == CPPI5_TR_TYPE9))
		*flags |= CPPI5_TR_STATIC;

	अगर (रुको)
		*flags |= CPPI5_TR_WAIT;
पूर्ण

/**
 * cppi5_tr_set_trigger - Configure trigger0/1 and trigger0/1_type
 * @flags: Poपूर्णांकer to the TR's flags
 * @trigger0: trigger0 selection
 * @trigger0_type: type of data transfer that will be enabled by trigger0
 * @trigger1: trigger1 selection
 * @trigger1_type: type of data transfer that will be enabled by trigger1
 *
 * Configure the triggers क्रम the TR
 */
अटल अंतरभूत व्योम cppi5_tr_set_trigger(cppi5_tr_flags_t *flags,
		क्रमागत cppi5_tr_trigger trigger0,
		क्रमागत cppi5_tr_trigger_type trigger0_type,
		क्रमागत cppi5_tr_trigger trigger1,
		क्रमागत cppi5_tr_trigger_type trigger1_type)
अणु
	*flags &= ~(CPPI5_TR_TRIGGER0_MASK | CPPI5_TR_TRIGGER0_TYPE_MASK |
		    CPPI5_TR_TRIGGER1_MASK | CPPI5_TR_TRIGGER1_TYPE_MASK);
	*flags |= (trigger0 << CPPI5_TR_TRIGGER0_SHIFT) &
		  CPPI5_TR_TRIGGER0_MASK;
	*flags |= (trigger0_type << CPPI5_TR_TRIGGER0_TYPE_SHIFT) &
		  CPPI5_TR_TRIGGER0_TYPE_MASK;

	*flags |= (trigger1 << CPPI5_TR_TRIGGER1_SHIFT) &
		  CPPI5_TR_TRIGGER1_MASK;
	*flags |= (trigger1_type << CPPI5_TR_TRIGGER1_TYPE_SHIFT) &
		  CPPI5_TR_TRIGGER1_TYPE_MASK;
पूर्ण

/**
 * cppi5_tr_cflag_set - Update the Configuration specअगरic flags
 * @flags: Poपूर्णांकer to the TR's flags
 * @csf: Configuration specअगरic flags
 *
 * Set a bit in Configuration Specअगरic Flags section of the TR flags.
 */
अटल अंतरभूत व्योम cppi5_tr_csf_set(cppi5_tr_flags_t *flags, u32 csf)
अणु
	*flags &= ~CPPI5_TR_CSF_FLAGS_MASK;
	*flags |= (csf << CPPI5_TR_CSF_FLAGS_SHIFT) &
		  CPPI5_TR_CSF_FLAGS_MASK;
पूर्ण

#पूर्ण_अगर /* __TI_CPPI5_H__ */
