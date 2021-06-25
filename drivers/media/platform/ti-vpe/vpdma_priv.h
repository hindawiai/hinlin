<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */

#अगर_अघोषित _TI_VPDMA_PRIV_H_
#घोषणा _TI_VPDMA_PRIV_H_

/*
 * VPDMA Register offsets
 */

/* Top level */
#घोषणा VPDMA_PID		0x00
#घोषणा VPDMA_LIST_ADDR		0x04
#घोषणा VPDMA_LIST_ATTR		0x08
#घोषणा VPDMA_LIST_STAT_SYNC	0x0c
#घोषणा VPDMA_BG_RGB		0x18
#घोषणा VPDMA_BG_YUV		0x1c
#घोषणा VPDMA_SETUP		0x30
#घोषणा VPDMA_MAX_SIZE1		0x34
#घोषणा VPDMA_MAX_SIZE2		0x38
#घोषणा VPDMA_MAX_SIZE3		0x3c
#घोषणा VPDMA_MAX_SIZE_WIDTH_MASK	0xffff
#घोषणा VPDMA_MAX_SIZE_WIDTH_SHFT	16
#घोषणा VPDMA_MAX_SIZE_HEIGHT_MASK	0xffff
#घोषणा VPDMA_MAX_SIZE_HEIGHT_SHFT	0

/* Interrupts */
#घोषणा VPDMA_INT_CHAN_STAT(grp)	(0x40 + grp * 8)
#घोषणा VPDMA_INT_CHAN_MASK(grp)	(VPDMA_INT_CHAN_STAT(grp) + 4)
#घोषणा VPDMA_INT_CLIENT0_STAT		0x78
#घोषणा VPDMA_INT_CLIENT0_MASK		0x7c
#घोषणा VPDMA_INT_CLIENT1_STAT		0x80
#घोषणा VPDMA_INT_CLIENT1_MASK		0x84
#घोषणा VPDMA_INT_LIST0_STAT		0x88
#घोषणा VPDMA_INT_LIST0_MASK		0x8c

#घोषणा VPDMA_INTX_OFFSET		0x50

#घोषणा VPDMA_PERFMON(i)		(0x200 + i * 4)

/* VIP/VPE client रेजिस्टरs */
#घोषणा VPDMA_DEI_CHROMA1_CSTAT		0x0300
#घोषणा VPDMA_DEI_LUMA1_CSTAT		0x0304
#घोषणा VPDMA_DEI_LUMA2_CSTAT		0x0308
#घोषणा VPDMA_DEI_CHROMA2_CSTAT		0x030c
#घोषणा VPDMA_DEI_LUMA3_CSTAT		0x0310
#घोषणा VPDMA_DEI_CHROMA3_CSTAT		0x0314
#घोषणा VPDMA_DEI_MV_IN_CSTAT		0x0330
#घोषणा VPDMA_DEI_MV_OUT_CSTAT		0x033c
#घोषणा VPDMA_VIP_LO_Y_CSTAT		0x0388
#घोषणा VPDMA_VIP_LO_UV_CSTAT		0x038c
#घोषणा VPDMA_VIP_UP_Y_CSTAT		0x0390
#घोषणा VPDMA_VIP_UP_UV_CSTAT		0x0394
#घोषणा VPDMA_VPI_CTL_CSTAT		0x03d0

/* Reg field info क्रम VPDMA_CLIENT_CSTAT रेजिस्टरs */
#घोषणा VPDMA_CSTAT_LINE_MODE_MASK	0x03
#घोषणा VPDMA_CSTAT_LINE_MODE_SHIFT	8
#घोषणा VPDMA_CSTAT_FRAME_START_MASK	0xf
#घोषणा VPDMA_CSTAT_FRAME_START_SHIFT	10

#घोषणा VPDMA_LIST_NUM_MASK		0x07
#घोषणा VPDMA_LIST_NUM_SHFT		24
#घोषणा VPDMA_LIST_STOP_SHFT		20
#घोषणा VPDMA_LIST_RDY_MASK		0x01
#घोषणा VPDMA_LIST_RDY_SHFT		19
#घोषणा VPDMA_LIST_TYPE_MASK		0x03
#घोषणा VPDMA_LIST_TYPE_SHFT		16
#घोषणा VPDMA_LIST_SIZE_MASK		0xffff

/*
 * The YUV data type definition below are taken from
 * both the TRM and i839 Errata inक्रमmation.
 * Use the correct data type considering byte
 * reordering of components.
 *
 * Also since the single use of "C" in the 422 हाल
 * to mean "Cr" (i.e. V component). It was decided
 * to explicitly label them CR to हटाओ any confusion.
 * Bear in mind that the type label refer to the memory
 * packed order (LSB - MSB).
 */
#घोषणा DATA_TYPE_Y444				0x0
#घोषणा DATA_TYPE_Y422				0x1
#घोषणा DATA_TYPE_Y420				0x2
#घोषणा DATA_TYPE_C444				0x4
#घोषणा DATA_TYPE_C422				0x5
#घोषणा DATA_TYPE_C420				0x6
#घोषणा DATA_TYPE_CB420				0x16
#घोषणा DATA_TYPE_YC444				0x8
#घोषणा DATA_TYPE_YCB422			0x7
#घोषणा DATA_TYPE_YCR422			0x17
#घोषणा DATA_TYPE_CBY422			0x27
#घोषणा DATA_TYPE_CRY422			0x37

/*
 * The RGB data type definition below are defined
 * to follow Errata i819.
 * The initial values were taken from:
 * VPDMA_data_type_mapping_v0.2vayu_c.pdf
 * But some of the ARGB definition appeared to be wrong
 * in the करोcument also. As they would yield RGBA instead.
 * They have been corrected based on experimentation.
 */
#घोषणा DATA_TYPE_RGB16_565			0x10
#घोषणा DATA_TYPE_ARGB_1555			0x13
#घोषणा DATA_TYPE_ARGB_4444			0x14
#घोषणा DATA_TYPE_RGBA_5551			0x11
#घोषणा DATA_TYPE_RGBA_4444			0x12
#घोषणा DATA_TYPE_ARGB24_6666			0x18
#घोषणा DATA_TYPE_RGB24_888			0x16
#घोषणा DATA_TYPE_ARGB32_8888			0x17
#घोषणा DATA_TYPE_RGBA24_6666			0x15
#घोषणा DATA_TYPE_RGBA32_8888			0x19
#घोषणा DATA_TYPE_BGR16_565			0x0
#घोषणा DATA_TYPE_ABGR_1555			0x3
#घोषणा DATA_TYPE_ABGR_4444			0x4
#घोषणा DATA_TYPE_BGRA_5551			0x1
#घोषणा DATA_TYPE_BGRA_4444			0x2
#घोषणा DATA_TYPE_ABGR24_6666			0x8
#घोषणा DATA_TYPE_BGR24_888			0x6
#घोषणा DATA_TYPE_ABGR32_8888			0x7
#घोषणा DATA_TYPE_BGRA24_6666			0x5
#घोषणा DATA_TYPE_BGRA32_8888			0x9

#घोषणा DATA_TYPE_MV				0x3

/* VPDMA channel numbers, some are common between VIP/VPE and appear twice */
#घोषणा	VPE_CHAN_NUM_LUMA1_IN		0
#घोषणा	VPE_CHAN_NUM_CHROMA1_IN		1
#घोषणा	VPE_CHAN_NUM_LUMA2_IN		2
#घोषणा	VPE_CHAN_NUM_CHROMA2_IN		3
#घोषणा	VPE_CHAN_NUM_LUMA3_IN		4
#घोषणा	VPE_CHAN_NUM_CHROMA3_IN		5
#घोषणा	VPE_CHAN_NUM_MV_IN		12
#घोषणा	VPE_CHAN_NUM_MV_OUT		15
#घोषणा VIP1_CHAN_NUM_MULT_PORT_A_SRC0	38
#घोषणा VIP1_CHAN_NUM_MULT_ANC_A_SRC0	70
#घोषणा	VPE_CHAN_NUM_LUMA_OUT		102
#घोषणा	VPE_CHAN_NUM_CHROMA_OUT		103
#घोषणा VIP1_CHAN_NUM_PORT_A_LUMA	102
#घोषणा VIP1_CHAN_NUM_PORT_A_CHROMA	103
#घोषणा	VPE_CHAN_NUM_RGB_OUT		106
#घोषणा VIP1_CHAN_NUM_PORT_A_RGB	106
#घोषणा VIP1_CHAN_NUM_PORT_B_RGB	107
/*
 * a VPDMA address data block payload क्रम a configuration descriptor needs to
 * have each sub block length as a multiple of 16 bytes. Thereक्रमe, the overall
 * size of the payload also needs to be a multiple of 16 bytes. The sub block
 * lengths should be ensured to be aligned by the VPDMA user.
 */
#घोषणा VPDMA_ADB_SIZE_ALIGN		0x0f

/*
 * data transfer descriptor
 */
काष्ठा vpdma_dtd अणु
	u32			type_ctl_stride;
	जोड़ अणु
		u32		xfer_length_height;
		u32		w1;
	पूर्ण;
	u32			start_addr;
	u32			pkt_ctl;
	जोड़ अणु
		u32		frame_width_height;	/* inbound */
		u32		desc_ग_लिखो_addr;	/* outbound */
	पूर्ण;
	जोड़ अणु
		u32		start_h_v;		/* inbound */
		u32		max_width_height;	/* outbound */
	पूर्ण;
	u32			client_attr0;
	u32			client_attr1;
पूर्ण;

/* Data Transfer Descriptor specअगरics */
#घोषणा DTD_NO_NOTIFY		0
#घोषणा DTD_NOTIFY		1

#घोषणा DTD_PKT_TYPE		0xa
#घोषणा DTD_सूची_IN		0
#घोषणा DTD_सूची_OUT		1

/* type_ctl_stride */
#घोषणा DTD_DATA_TYPE_MASK	0x3f
#घोषणा DTD_DATA_TYPE_SHFT	26
#घोषणा DTD_NOTIFY_MASK		0x01
#घोषणा DTD_NOTIFY_SHFT		25
#घोषणा DTD_FIELD_MASK		0x01
#घोषणा DTD_FIELD_SHFT		24
#घोषणा DTD_1D_MASK		0x01
#घोषणा DTD_1D_SHFT		23
#घोषणा DTD_EVEN_LINE_SKIP_MASK	0x01
#घोषणा DTD_EVEN_LINE_SKIP_SHFT	20
#घोषणा DTD_ODD_LINE_SKIP_MASK	0x01
#घोषणा DTD_ODD_LINE_SKIP_SHFT	16
#घोषणा DTD_LINE_STRIDE_MASK	0xffff
#घोषणा DTD_LINE_STRIDE_SHFT	0

/* xfer_length_height */
#घोषणा DTD_LINE_LENGTH_MASK	0xffff
#घोषणा DTD_LINE_LENGTH_SHFT	16
#घोषणा DTD_XFER_HEIGHT_MASK	0xffff
#घोषणा DTD_XFER_HEIGHT_SHFT	0

/* pkt_ctl */
#घोषणा DTD_PKT_TYPE_MASK	0x1f
#घोषणा DTD_PKT_TYPE_SHFT	27
#घोषणा DTD_MODE_MASK		0x01
#घोषणा DTD_MODE_SHFT		26
#घोषणा DTD_सूची_MASK		0x01
#घोषणा DTD_सूची_SHFT		25
#घोषणा DTD_CHAN_MASK		0x01ff
#घोषणा DTD_CHAN_SHFT		16
#घोषणा DTD_PRI_MASK		0x0f
#घोषणा DTD_PRI_SHFT		9
#घोषणा DTD_NEXT_CHAN_MASK	0x01ff
#घोषणा DTD_NEXT_CHAN_SHFT	0

/* frame_width_height */
#घोषणा DTD_FRAME_WIDTH_MASK	0xffff
#घोषणा DTD_FRAME_WIDTH_SHFT	16
#घोषणा DTD_FRAME_HEIGHT_MASK	0xffff
#घोषणा DTD_FRAME_HEIGHT_SHFT	0

/* start_h_v */
#घोषणा DTD_H_START_MASK	0xffff
#घोषणा DTD_H_START_SHFT	16
#घोषणा DTD_V_START_MASK	0xffff
#घोषणा DTD_V_START_SHFT	0

#घोषणा DTD_DESC_START_MASK	0xffffffe0
#घोषणा DTD_DESC_START_SHIFT	5
#घोषणा DTD_WRITE_DESC_MASK	0x01
#घोषणा DTD_WRITE_DESC_SHIFT	2
#घोषणा DTD_DROP_DATA_MASK	0x01
#घोषणा DTD_DROP_DATA_SHIFT	1
#घोषणा DTD_USE_DESC_MASK	0x01
#घोषणा DTD_USE_DESC_SHIFT	0

/* max_width_height */
#घोषणा DTD_MAX_WIDTH_MASK	0x07
#घोषणा DTD_MAX_WIDTH_SHFT	4
#घोषणा DTD_MAX_HEIGHT_MASK	0x07
#घोषणा DTD_MAX_HEIGHT_SHFT	0

अटल अंतरभूत u32 dtd_type_ctl_stride(पूर्णांक type, bool notअगरy, पूर्णांक field,
			bool one_d, bool even_line_skip, bool odd_line_skip,
			पूर्णांक line_stride)
अणु
	वापस (type << DTD_DATA_TYPE_SHFT) | (notअगरy << DTD_NOTIFY_SHFT) |
		(field << DTD_FIELD_SHFT) | (one_d << DTD_1D_SHFT) |
		(even_line_skip << DTD_EVEN_LINE_SKIP_SHFT) |
		(odd_line_skip << DTD_ODD_LINE_SKIP_SHFT) |
		line_stride;
पूर्ण

अटल अंतरभूत u32 dtd_xfer_length_height(पूर्णांक line_length, पूर्णांक xfer_height)
अणु
	वापस (line_length << DTD_LINE_LENGTH_SHFT) | xfer_height;
पूर्ण

अटल अंतरभूत u32 dtd_pkt_ctl(bool mode, bool dir, पूर्णांक chan, पूर्णांक pri,
			पूर्णांक next_chan)
अणु
	वापस (DTD_PKT_TYPE << DTD_PKT_TYPE_SHFT) | (mode << DTD_MODE_SHFT) |
		(dir << DTD_सूची_SHFT) | (chan << DTD_CHAN_SHFT) |
		(pri << DTD_PRI_SHFT) | next_chan;
पूर्ण

अटल अंतरभूत u32 dtd_frame_width_height(पूर्णांक width, पूर्णांक height)
अणु
	वापस (width << DTD_FRAME_WIDTH_SHFT) | height;
पूर्ण

अटल अंतरभूत u32 dtd_desc_ग_लिखो_addr(अचिन्हित पूर्णांक addr, bool ग_लिखो_desc,
			bool drop_data, bool use_desc)
अणु
	वापस (addr & DTD_DESC_START_MASK) |
		(ग_लिखो_desc << DTD_WRITE_DESC_SHIFT) |
		(drop_data << DTD_DROP_DATA_SHIFT) |
		use_desc;
पूर्ण

अटल अंतरभूत u32 dtd_start_h_v(पूर्णांक h_start, पूर्णांक v_start)
अणु
	वापस (h_start << DTD_H_START_SHFT) | v_start;
पूर्ण

अटल अंतरभूत u32 dtd_max_width_height(पूर्णांक max_width, पूर्णांक max_height)
अणु
	वापस (max_width << DTD_MAX_WIDTH_SHFT) | max_height;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_data_type(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->type_ctl_stride >> DTD_DATA_TYPE_SHFT;
पूर्ण

अटल अंतरभूत bool dtd_get_notअगरy(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->type_ctl_stride >> DTD_NOTIFY_SHFT) & DTD_NOTIFY_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_field(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->type_ctl_stride >> DTD_FIELD_SHFT) & DTD_FIELD_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_1d(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->type_ctl_stride >> DTD_1D_SHFT) & DTD_1D_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_even_line_skip(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->type_ctl_stride >> DTD_EVEN_LINE_SKIP_SHFT)
		& DTD_EVEN_LINE_SKIP_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_odd_line_skip(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->type_ctl_stride >> DTD_ODD_LINE_SKIP_SHFT)
		& DTD_ODD_LINE_SKIP_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_line_stride(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->type_ctl_stride & DTD_LINE_STRIDE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_line_length(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->xfer_length_height >> DTD_LINE_LENGTH_SHFT;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_xfer_height(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->xfer_length_height & DTD_XFER_HEIGHT_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_pkt_type(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->pkt_ctl >> DTD_PKT_TYPE_SHFT;
पूर्ण

अटल अंतरभूत bool dtd_get_mode(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->pkt_ctl >> DTD_MODE_SHFT) & DTD_MODE_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_dir(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->pkt_ctl >> DTD_सूची_SHFT) & DTD_सूची_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_chan(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->pkt_ctl >> DTD_CHAN_SHFT) & DTD_CHAN_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_priority(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->pkt_ctl >> DTD_PRI_SHFT) & DTD_PRI_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_next_chan(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->pkt_ctl >> DTD_NEXT_CHAN_SHFT) & DTD_NEXT_CHAN_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_frame_width(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->frame_width_height >> DTD_FRAME_WIDTH_SHFT;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_frame_height(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->frame_width_height & DTD_FRAME_HEIGHT_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_desc_ग_लिखो_addr(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->desc_ग_लिखो_addr & DTD_DESC_START_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_ग_लिखो_desc(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->desc_ग_लिखो_addr >> DTD_WRITE_DESC_SHIFT) &
							DTD_WRITE_DESC_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_drop_data(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->desc_ग_लिखो_addr >> DTD_DROP_DATA_SHIFT) &
							DTD_DROP_DATA_MASK;
पूर्ण

अटल अंतरभूत bool dtd_get_use_desc(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->desc_ग_लिखो_addr & DTD_USE_DESC_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_h_start(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->start_h_v >> DTD_H_START_SHFT;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_v_start(काष्ठा vpdma_dtd *dtd)
अणु
	वापस dtd->start_h_v & DTD_V_START_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_max_width(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->max_width_height >> DTD_MAX_WIDTH_SHFT) &
							DTD_MAX_WIDTH_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक dtd_get_max_height(काष्ठा vpdma_dtd *dtd)
अणु
	वापस (dtd->max_width_height >> DTD_MAX_HEIGHT_SHFT) &
							DTD_MAX_HEIGHT_MASK;
पूर्ण

/*
 * configuration descriptor
 */
काष्ठा vpdma_cfd अणु
	जोड़ अणु
		u32	dest_addr_offset;
		u32	w0;
	पूर्ण;
	जोड़ अणु
		u32	block_len;		/* in words */
		u32	w1;
	पूर्ण;
	u32		payload_addr;
	u32		ctl_payload_len;	/* in words */
पूर्ण;

/* Configuration descriptor specअगरics */

#घोषणा CFD_PKT_TYPE		0xb

#घोषणा CFD_सूचीECT		1
#घोषणा CFD_INसूचीECT		0
#घोषणा CFD_CLS_ADB		0
#घोषणा CFD_CLS_BLOCK		1

/* block_len */
#घोषणा CFD__BLOCK_LEN_MASK	0xffff
#घोषणा CFD__BLOCK_LEN_SHFT	0

/* ctl_payload_len */
#घोषणा CFD_PKT_TYPE_MASK	0x1f
#घोषणा CFD_PKT_TYPE_SHFT	27
#घोषणा CFD_सूचीECT_MASK		0x01
#घोषणा CFD_सूचीECT_SHFT		26
#घोषणा CFD_CLASS_MASK		0x03
#घोषणा CFD_CLASS_SHFT		24
#घोषणा CFD_DEST_MASK		0xff
#घोषणा CFD_DEST_SHFT		16
#घोषणा CFD_PAYLOAD_LEN_MASK	0xffff
#घोषणा CFD_PAYLOAD_LEN_SHFT	0

अटल अंतरभूत u32 cfd_pkt_payload_len(bool direct, पूर्णांक cls, पूर्णांक dest,
		पूर्णांक payload_len)
अणु
	वापस (CFD_PKT_TYPE << CFD_PKT_TYPE_SHFT) |
		(direct << CFD_सूचीECT_SHFT) |
		(cls << CFD_CLASS_SHFT) |
		(dest << CFD_DEST_SHFT) |
		payload_len;
पूर्ण

अटल अंतरभूत पूर्णांक cfd_get_pkt_type(काष्ठा vpdma_cfd *cfd)
अणु
	वापस cfd->ctl_payload_len >> CFD_PKT_TYPE_SHFT;
पूर्ण

अटल अंतरभूत bool cfd_get_direct(काष्ठा vpdma_cfd *cfd)
अणु
	वापस (cfd->ctl_payload_len >> CFD_सूचीECT_SHFT) & CFD_सूचीECT_MASK;
पूर्ण

अटल अंतरभूत bool cfd_get_class(काष्ठा vpdma_cfd *cfd)
अणु
	वापस (cfd->ctl_payload_len >> CFD_CLASS_SHFT) & CFD_CLASS_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक cfd_get_dest(काष्ठा vpdma_cfd *cfd)
अणु
	वापस (cfd->ctl_payload_len >> CFD_DEST_SHFT) & CFD_DEST_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक cfd_get_payload_len(काष्ठा vpdma_cfd *cfd)
अणु
	वापस cfd->ctl_payload_len & CFD_PAYLOAD_LEN_MASK;
पूर्ण

/*
 * control descriptor
 */
काष्ठा vpdma_ctd अणु
	जोड़ अणु
		u32	समयr_value;
		u32	list_addr;
		u32	w0;
	पूर्ण;
	जोड़ अणु
		u32	pixel_line_count;
		u32	list_size;
		u32	w1;
	पूर्ण;
	जोड़ अणु
		u32	event;
		u32	fid_ctl;
		u32	w2;
	पूर्ण;
	u32		type_source_ctl;
पूर्ण;

/* control descriptor types */
#घोषणा CTD_TYPE_SYNC_ON_CLIENT		0
#घोषणा CTD_TYPE_SYNC_ON_LIST		1
#घोषणा CTD_TYPE_SYNC_ON_EXT		2
#घोषणा CTD_TYPE_SYNC_ON_LM_TIMER	3
#घोषणा CTD_TYPE_SYNC_ON_CHANNEL	4
#घोषणा CTD_TYPE_CHNG_CLIENT_IRQ	5
#घोषणा CTD_TYPE_SEND_IRQ		6
#घोषणा CTD_TYPE_RELOAD_LIST		7
#घोषणा CTD_TYPE_ABORT_CHANNEL		8

#घोषणा CTD_PKT_TYPE		0xc

/* समयr_value */
#घोषणा CTD_TIMER_VALUE_MASK	0xffff
#घोषणा CTD_TIMER_VALUE_SHFT	0

/* pixel_line_count */
#घोषणा CTD_PIXEL_COUNT_MASK	0xffff
#घोषणा CTD_PIXEL_COUNT_SHFT	16
#घोषणा CTD_LINE_COUNT_MASK	0xffff
#घोषणा CTD_LINE_COUNT_SHFT	0

/* list_size */
#घोषणा CTD_LIST_SIZE_MASK	0xffff
#घोषणा CTD_LIST_SIZE_SHFT	0

/* event */
#घोषणा CTD_EVENT_MASK		0x0f
#घोषणा CTD_EVENT_SHFT		0

/* fid_ctl */
#घोषणा CTD_FID2_MASK		0x03
#घोषणा CTD_FID2_SHFT		4
#घोषणा CTD_FID1_MASK		0x03
#घोषणा CTD_FID1_SHFT		2
#घोषणा CTD_FID0_MASK		0x03
#घोषणा CTD_FID0_SHFT		0

/* type_source_ctl */
#घोषणा CTD_PKT_TYPE_MASK	0x1f
#घोषणा CTD_PKT_TYPE_SHFT	27
#घोषणा CTD_SOURCE_MASK		0xff
#घोषणा CTD_SOURCE_SHFT		16
#घोषणा CTD_CONTROL_MASK	0x0f
#घोषणा CTD_CONTROL_SHFT	0

अटल अंतरभूत u32 ctd_pixel_line_count(पूर्णांक pixel_count, पूर्णांक line_count)
अणु
	वापस (pixel_count << CTD_PIXEL_COUNT_SHFT) | line_count;
पूर्ण

अटल अंतरभूत u32 ctd_set_fid_ctl(पूर्णांक fid0, पूर्णांक fid1, पूर्णांक fid2)
अणु
	वापस (fid2 << CTD_FID2_SHFT) | (fid1 << CTD_FID1_SHFT) | fid0;
पूर्ण

अटल अंतरभूत u32 ctd_type_source_ctl(पूर्णांक source, पूर्णांक control)
अणु
	वापस (CTD_PKT_TYPE << CTD_PKT_TYPE_SHFT) |
		(source << CTD_SOURCE_SHFT) | control;
पूर्ण

अटल अंतरभूत u32 ctd_get_pixel_count(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->pixel_line_count >> CTD_PIXEL_COUNT_SHFT;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_line_count(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->pixel_line_count & CTD_LINE_COUNT_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_event(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->event & CTD_EVENT_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_fid2_ctl(काष्ठा vpdma_ctd *ctd)
अणु
	वापस (ctd->fid_ctl >> CTD_FID2_SHFT) & CTD_FID2_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_fid1_ctl(काष्ठा vpdma_ctd *ctd)
अणु
	वापस (ctd->fid_ctl >> CTD_FID1_SHFT) & CTD_FID1_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_fid0_ctl(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->fid_ctl & CTD_FID2_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_pkt_type(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->type_source_ctl >> CTD_PKT_TYPE_SHFT;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_source(काष्ठा vpdma_ctd *ctd)
अणु
	वापस (ctd->type_source_ctl >> CTD_SOURCE_SHFT) & CTD_SOURCE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ctd_get_ctl(काष्ठा vpdma_ctd *ctd)
अणु
	वापस ctd->type_source_ctl & CTD_CONTROL_MASK;
पूर्ण

#पूर्ण_अगर
