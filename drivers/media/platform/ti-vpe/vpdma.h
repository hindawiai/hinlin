<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */

#अगर_अघोषित __TI_VPDMA_H_
#घोषणा __TI_VPDMA_H_

#घोषणा VPDMA_MAX_NUM_LIST		8
/*
 * A vpdma_buf tracks the size, DMA address and mapping status of each
 * driver DMA area.
 */
काष्ठा vpdma_buf अणु
	व्योम			*addr;
	dma_addr_t		dma_addr;
	माप_प्रकार			size;
	bool			mapped;
पूर्ण;

काष्ठा vpdma_desc_list अणु
	काष्ठा vpdma_buf buf;
	व्योम *next;
	पूर्णांक type;
पूर्ण;

काष्ठा vpdma_data अणु
	व्योम __iomem		*base;

	काष्ठा platक्रमm_device	*pdev;

	spinlock_t		lock;
	bool			hwlist_used[VPDMA_MAX_NUM_LIST];
	व्योम			*hwlist_priv[VPDMA_MAX_NUM_LIST];
	/* callback to VPE driver when the firmware is loaded */
	व्योम (*cb)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

क्रमागत vpdma_data_क्रमmat_type अणु
	VPDMA_DATA_FMT_TYPE_YUV,
	VPDMA_DATA_FMT_TYPE_RGB,
	VPDMA_DATA_FMT_TYPE_MISC,
पूर्ण;

काष्ठा vpdma_data_क्रमmat अणु
	क्रमागत vpdma_data_क्रमmat_type type;
	पूर्णांक data_type;
	u8 depth;
पूर्ण;

#घोषणा VPDMA_DESC_ALIGN		16	/* 16-byte descriptor alignment */
#घोषणा VPDMA_STRIDE_ALIGN		16	/*
						 * line stride of source and dest
						 * buffers should be 16 byte aligned
						 */
#घोषणा VPDMA_MAX_STRIDE		65520	/* Max line stride 16 byte aligned */
#घोषणा VPDMA_DTD_DESC_SIZE		32	/* 8 words */
#घोषणा VPDMA_CFD_CTD_DESC_SIZE		16	/* 4 words */

#घोषणा VPDMA_LIST_TYPE_NORMAL		0
#घोषणा VPDMA_LIST_TYPE_SELF_MODIFYING	1
#घोषणा VPDMA_LIST_TYPE_DOORBELL	2

क्रमागत vpdma_yuv_क्रमmats अणु
	VPDMA_DATA_FMT_Y444 = 0,
	VPDMA_DATA_FMT_Y422,
	VPDMA_DATA_FMT_Y420,
	VPDMA_DATA_FMT_C444,
	VPDMA_DATA_FMT_C422,
	VPDMA_DATA_FMT_C420,
	VPDMA_DATA_FMT_CB420,
	VPDMA_DATA_FMT_YCR422,
	VPDMA_DATA_FMT_YC444,
	VPDMA_DATA_FMT_CRY422,
	VPDMA_DATA_FMT_CBY422,
	VPDMA_DATA_FMT_YCB422,
पूर्ण;

क्रमागत vpdma_rgb_क्रमmats अणु
	VPDMA_DATA_FMT_RGB565 = 0,
	VPDMA_DATA_FMT_ARGB16_1555,
	VPDMA_DATA_FMT_ARGB16,
	VPDMA_DATA_FMT_RGBA16_5551,
	VPDMA_DATA_FMT_RGBA16,
	VPDMA_DATA_FMT_ARGB24,
	VPDMA_DATA_FMT_RGB24,
	VPDMA_DATA_FMT_ARGB32,
	VPDMA_DATA_FMT_RGBA24,
	VPDMA_DATA_FMT_RGBA32,
	VPDMA_DATA_FMT_BGR565,
	VPDMA_DATA_FMT_ABGR16_1555,
	VPDMA_DATA_FMT_ABGR16,
	VPDMA_DATA_FMT_BGRA16_5551,
	VPDMA_DATA_FMT_BGRA16,
	VPDMA_DATA_FMT_ABGR24,
	VPDMA_DATA_FMT_BGR24,
	VPDMA_DATA_FMT_ABGR32,
	VPDMA_DATA_FMT_BGRA24,
	VPDMA_DATA_FMT_BGRA32,
पूर्ण;

क्रमागत vpdma_raw_क्रमmats अणु
	VPDMA_DATA_FMT_RAW8 = 0,
	VPDMA_DATA_FMT_RAW16,
पूर्ण;

क्रमागत vpdma_misc_क्रमmats अणु
	VPDMA_DATA_FMT_MV = 0,
पूर्ण;

बाह्य स्थिर काष्ठा vpdma_data_क्रमmat vpdma_yuv_fmts[];
बाह्य स्थिर काष्ठा vpdma_data_क्रमmat vpdma_rgb_fmts[];
बाह्य स्थिर काष्ठा vpdma_data_क्रमmat vpdma_raw_fmts[];
बाह्य स्थिर काष्ठा vpdma_data_क्रमmat vpdma_misc_fmts[];

क्रमागत vpdma_frame_start_event अणु
	VPDMA_FSEVENT_HDMI_FID = 0,
	VPDMA_FSEVENT_DVO2_FID,
	VPDMA_FSEVENT_HDCOMP_FID,
	VPDMA_FSEVENT_SD_FID,
	VPDMA_FSEVENT_LM_FID0,
	VPDMA_FSEVENT_LM_FID1,
	VPDMA_FSEVENT_LM_FID2,
	VPDMA_FSEVENT_CHANNEL_ACTIVE,
पूर्ण;

/* max width configurations */
क्रमागत vpdma_max_width अणु
	MAX_OUT_WIDTH_UNLIMITED = 0,
	MAX_OUT_WIDTH_REG1,
	MAX_OUT_WIDTH_REG2,
	MAX_OUT_WIDTH_REG3,
	MAX_OUT_WIDTH_352,
	MAX_OUT_WIDTH_768,
	MAX_OUT_WIDTH_1280,
	MAX_OUT_WIDTH_1920,
पूर्ण;

/* max height configurations */
क्रमागत vpdma_max_height अणु
	MAX_OUT_HEIGHT_UNLIMITED = 0,
	MAX_OUT_HEIGHT_REG1,
	MAX_OUT_HEIGHT_REG2,
	MAX_OUT_HEIGHT_REG3,
	MAX_OUT_HEIGHT_288,
	MAX_OUT_HEIGHT_576,
	MAX_OUT_HEIGHT_720,
	MAX_OUT_HEIGHT_1080,
पूर्ण;

/*
 * VPDMA channel numbers
 */
क्रमागत vpdma_channel अणु
	VPE_CHAN_LUMA1_IN,
	VPE_CHAN_CHROMA1_IN,
	VPE_CHAN_LUMA2_IN,
	VPE_CHAN_CHROMA2_IN,
	VPE_CHAN_LUMA3_IN,
	VPE_CHAN_CHROMA3_IN,
	VPE_CHAN_MV_IN,
	VPE_CHAN_MV_OUT,
	VPE_CHAN_LUMA_OUT,
	VPE_CHAN_CHROMA_OUT,
	VPE_CHAN_RGB_OUT,
पूर्ण;

#घोषणा VIP_CHAN_VIP2_OFFSET		70
#घोषणा VIP_CHAN_MULT_PORTB_OFFSET	16
#घोषणा VIP_CHAN_YUV_PORTB_OFFSET	2
#घोषणा VIP_CHAN_RGB_PORTB_OFFSET	1

#घोषणा VPDMA_MAX_CHANNELS		256

/* flags क्रम VPDMA data descriptors */
#घोषणा VPDMA_DATA_ODD_LINE_SKIP	(1 << 0)
#घोषणा VPDMA_DATA_EVEN_LINE_SKIP	(1 << 1)
#घोषणा VPDMA_DATA_FRAME_1D		(1 << 2)
#घोषणा VPDMA_DATA_MODE_TILED		(1 << 3)

/*
 * client identअगरiers used क्रम configuration descriptors
 */
#घोषणा CFD_MMR_CLIENT		0
#घोषणा CFD_SC_CLIENT		4

/* Address data block header क्रमmat */
काष्ठा vpdma_adb_hdr अणु
	u32			offset;
	u32			nwords;
	u32			reserved0;
	u32			reserved1;
पूर्ण;

/* helpers क्रम creating ADB headers क्रम config descriptors MMRs as client */
#घोषणा ADB_ADDR(dma_buf, str, fld)	((dma_buf)->addr + दुरत्व(str, fld))
#घोषणा MMR_ADB_ADDR(buf, str, fld)	ADB_ADDR(&(buf), काष्ठा str, fld)

#घोषणा VPDMA_SET_MMR_ADB_HDR(buf, str, hdr, regs, offset_a)	\
	करो अणु							\
		काष्ठा vpdma_adb_hdr *h;			\
		काष्ठा str *adb = शून्य;				\
		h = MMR_ADB_ADDR(buf, str, hdr);		\
		h->offset = (offset_a);				\
		h->nwords = माप(adb->regs) >> 2;		\
	पूर्ण जबतक (0)

/* vpdma descriptor buffer allocation and management */
पूर्णांक vpdma_alloc_desc_buf(काष्ठा vpdma_buf *buf, माप_प्रकार size);
व्योम vpdma_मुक्त_desc_buf(काष्ठा vpdma_buf *buf);
पूर्णांक vpdma_map_desc_buf(काष्ठा vpdma_data *vpdma, काष्ठा vpdma_buf *buf);
व्योम vpdma_unmap_desc_buf(काष्ठा vpdma_data *vpdma, काष्ठा vpdma_buf *buf);

/* vpdma descriptor list funcs */
पूर्णांक vpdma_create_desc_list(काष्ठा vpdma_desc_list *list, माप_प्रकार size, पूर्णांक type);
व्योम vpdma_reset_desc_list(काष्ठा vpdma_desc_list *list);
व्योम vpdma_मुक्त_desc_list(काष्ठा vpdma_desc_list *list);
पूर्णांक vpdma_submit_descs(काष्ठा vpdma_data *vpdma, काष्ठा vpdma_desc_list *list,
		       पूर्णांक list_num);
bool vpdma_list_busy(काष्ठा vpdma_data *vpdma, पूर्णांक list_num);
व्योम vpdma_update_dma_addr(काष्ठा vpdma_data *vpdma,
	काष्ठा vpdma_desc_list *list, dma_addr_t dma_addr,
	व्योम *ग_लिखो_dtd, पूर्णांक drop, पूर्णांक idx);

/* VPDMA hardware list funcs */
पूर्णांक vpdma_hwlist_alloc(काष्ठा vpdma_data *vpdma, व्योम *priv);
व्योम *vpdma_hwlist_get_priv(काष्ठा vpdma_data *vpdma, पूर्णांक list_num);
व्योम *vpdma_hwlist_release(काष्ठा vpdma_data *vpdma, पूर्णांक list_num);

/* helpers क्रम creating vpdma descriptors */
व्योम vpdma_add_cfd_block(काष्ठा vpdma_desc_list *list, पूर्णांक client,
		काष्ठा vpdma_buf *blk, u32 dest_offset);
व्योम vpdma_add_cfd_adb(काष्ठा vpdma_desc_list *list, पूर्णांक client,
		काष्ठा vpdma_buf *adb);
व्योम vpdma_add_sync_on_channel_ctd(काष्ठा vpdma_desc_list *list,
		क्रमागत vpdma_channel chan);
व्योम vpdma_add_पात_channel_ctd(काष्ठा vpdma_desc_list *list,
		पूर्णांक chan_num);
व्योम vpdma_add_out_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		पूर्णांक max_w, पूर्णांक max_h, क्रमागत vpdma_channel chan, u32 flags);
व्योम vpdma_rawchan_add_out_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		पूर्णांक max_w, पूर्णांक max_h, पूर्णांक raw_vpdma_chan, u32 flags);

व्योम vpdma_add_in_dtd(काष्ठा vpdma_desc_list *list, पूर्णांक width,
		पूर्णांक stride, स्थिर काष्ठा v4l2_rect *c_rect,
		स्थिर काष्ठा vpdma_data_क्रमmat *fmt, dma_addr_t dma_addr,
		क्रमागत vpdma_channel chan, पूर्णांक field, u32 flags, पूर्णांक frame_width,
		पूर्णांक frame_height, पूर्णांक start_h, पूर्णांक start_v);
पूर्णांक vpdma_list_cleanup(काष्ठा vpdma_data *vpdma, पूर्णांक list_num,
		पूर्णांक *channels, पूर्णांक size);

/* vpdma list पूर्णांकerrupt management */
व्योम vpdma_enable_list_complete_irq(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num,
		पूर्णांक list_num, bool enable);
व्योम vpdma_clear_list_stat(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num,
			   पूर्णांक list_num);
अचिन्हित पूर्णांक vpdma_get_list_stat(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num);
अचिन्हित पूर्णांक vpdma_get_list_mask(काष्ठा vpdma_data *vpdma, पूर्णांक irq_num);

/* vpdma client configuration */
व्योम vpdma_set_line_mode(काष्ठा vpdma_data *vpdma, पूर्णांक line_mode,
		क्रमागत vpdma_channel chan);
व्योम vpdma_set_frame_start_event(काष्ठा vpdma_data *vpdma,
		क्रमागत vpdma_frame_start_event fs_event, क्रमागत vpdma_channel chan);
व्योम vpdma_set_max_size(काष्ठा vpdma_data *vpdma, पूर्णांक reg_addr,
			u32 width, u32 height);

व्योम vpdma_set_bg_color(काष्ठा vpdma_data *vpdma,
			काष्ठा vpdma_data_क्रमmat *fmt, u32 color);
व्योम vpdma_dump_regs(काष्ठा vpdma_data *vpdma);

/* initialize vpdma, passed with VPE's platक्रमm device poपूर्णांकer */
पूर्णांक vpdma_create(काष्ठा platक्रमm_device *pdev, काष्ठा vpdma_data *vpdma,
		व्योम (*cb)(काष्ठा platक्रमm_device *pdev));

#पूर्ण_अगर
