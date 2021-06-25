<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * i.MX8QXP/i.MX8QM JPEG encoder/decoder v4l2 driver
 *
 * Copyright 2018-2019 NXP
 */

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>

#अगर_अघोषित _MXC_JPEG_CORE_H
#घोषणा _MXC_JPEG_CORE_H

#घोषणा MXC_JPEG_NAME			"mxc-jpeg"
#घोषणा MXC_JPEG_FMT_TYPE_ENC		0
#घोषणा MXC_JPEG_FMT_TYPE_RAW		1
#घोषणा MXC_JPEG_DEFAULT_WIDTH		1280
#घोषणा MXC_JPEG_DEFAULT_HEIGHT		720
#घोषणा MXC_JPEG_DEFAULT_PFMT		V4L2_PIX_FMT_RGB24
#घोषणा MXC_JPEG_MIN_WIDTH		64
#घोषणा MXC_JPEG_MIN_HEIGHT		64
#घोषणा MXC_JPEG_MAX_WIDTH		0x2000
#घोषणा MXC_JPEG_MAX_HEIGHT		0x2000
#घोषणा MXC_JPEG_MAX_CFG_STREAM		0x1000
#घोषणा MXC_JPEG_H_ALIGN		3
#घोषणा MXC_JPEG_W_ALIGN		3
#घोषणा MXC_JPEG_MAX_SIZEIMAGE		0xFFFFFC00
#घोषणा MXC_JPEG_MAX_PLANES		2

क्रमागत mxc_jpeg_enc_state अणु
	MXC_JPEG_ENCODING	= 0, /* jpeg encode phase */
	MXC_JPEG_ENC_CONF	= 1, /* jpeg encoder config phase */
पूर्ण;

क्रमागत mxc_jpeg_mode अणु
	MXC_JPEG_DECODE	= 0, /* jpeg decode mode */
	MXC_JPEG_ENCODE	= 1, /* jpeg encode mode */
पूर्ण;

/**
 * काष्ठा mxc_jpeg_fmt - driver's पूर्णांकernal color क्रमmat data
 * @name:	क्रमmat description
 * @fourcc:	fourcc code, 0 अगर not applicable
 * @subsampling: subsampling of jpeg components
 * @nc:		number of color components
 * @depth:	number of bits per pixel
 * @colplanes:	number of color planes (1 क्रम packed क्रमmats)
 * @h_align:	horizontal alignment order (align to 2^h_align)
 * @v_align:	vertical alignment order (align to 2^v_align)
 * @flags:	flags describing क्रमmat applicability
 */
काष्ठा mxc_jpeg_fmt अणु
	अक्षर					*name;
	u32					fourcc;
	क्रमागत v4l2_jpeg_chroma_subsampling	subsampling;
	पूर्णांक					nc;
	पूर्णांक					depth;
	पूर्णांक					colplanes;
	पूर्णांक					h_align;
	पूर्णांक					v_align;
	u32					flags;
पूर्ण;

काष्ठा mxc_jpeg_desc अणु
	u32 next_descpt_ptr;
	u32 buf_base0;
	u32 buf_base1;
	u32 line_pitch;
	u32 sपंचांग_bufbase;
	u32 sपंचांग_bufsize;
	u32 imgsize;
	u32 sपंचांग_ctrl;
पूर्ण __packed;

काष्ठा mxc_jpeg_q_data अणु
	काष्ठा mxc_jpeg_fmt	*fmt;
	u32			sizeimage[MXC_JPEG_MAX_PLANES];
	u32			bytesperline[MXC_JPEG_MAX_PLANES];
	पूर्णांक			w;
	पूर्णांक			w_adjusted;
	पूर्णांक			h;
	पूर्णांक			h_adjusted;
	अचिन्हित पूर्णांक		sequence;
पूर्ण;

काष्ठा mxc_jpeg_ctx अणु
	काष्ठा mxc_jpeg_dev		*mxc_jpeg;
	काष्ठा mxc_jpeg_q_data		out_q;
	काष्ठा mxc_jpeg_q_data		cap_q;
	काष्ठा v4l2_fh			fh;
	क्रमागत mxc_jpeg_enc_state		enc_state;
	अचिन्हित पूर्णांक			stopping;
	अचिन्हित पूर्णांक			slot;
पूर्ण;

काष्ठा mxc_jpeg_slot_data अणु
	bool used;
	काष्ठा mxc_jpeg_desc *desc; // enc/dec descriptor
	काष्ठा mxc_jpeg_desc *cfg_desc; // configuration descriptor
	व्योम *cfg_stream_vaddr; // configuration bitstream भव address
	अचिन्हित पूर्णांक cfg_stream_size;
	dma_addr_t desc_handle;
	dma_addr_t cfg_desc_handle; // configuration descriptor dma address
	dma_addr_t cfg_stream_handle; // configuration bitstream dma address
पूर्ण;

काष्ठा mxc_jpeg_dev अणु
	spinlock_t			hw_lock; /* hardware access lock */
	अचिन्हित पूर्णांक			mode;
	काष्ठा mutex			lock; /* v4l2 ioctls serialization */
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा device			*dev;
	व्योम __iomem			*base_reg;
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा v4l2_m2m_dev		*m2m_dev;
	काष्ठा video_device		*dec_vdev;
	काष्ठा mxc_jpeg_slot_data	slot_data[MXC_MAX_SLOTS];
	पूर्णांक				num_करोमुख्यs;
	काष्ठा device			**pd_dev;
	काष्ठा device_link		**pd_link;
पूर्ण;

/**
 * काष्ठा mxc_jpeg_sof_comp - JPEG Start Of Frame component fields
 * @id:				component id
 * @v:				vertical sampling
 * @h:				horizontal sampling
 * @quantization_table_no:	id of quantization table
 */
काष्ठा mxc_jpeg_sof_comp अणु
	u8 id;
	u8 v :4;
	u8 h :4;
	u8 quantization_table_no;
पूर्ण __packed;

#घोषणा MXC_JPEG_MAX_COMPONENTS 4
/**
 * काष्ठा mxc_jpeg_sof - JPEG Start Of Frame marker fields
 * @length:		Start of Frame length
 * @precision:		precision (bits per pixel per color component)
 * @height:		image height
 * @width:		image width
 * @components_no:	number of color components
 * @comp:		component fields क्रम each color component
 */
काष्ठा mxc_jpeg_sof अणु
	u16 length;
	u8 precision;
	u16 height, width;
	u8 components_no;
	काष्ठा mxc_jpeg_sof_comp comp[MXC_JPEG_MAX_COMPONENTS];
पूर्ण __packed;

/**
 * काष्ठा mxc_jpeg_sos_comp - JPEG Start Of Scan component fields
 * @id:			component id
 * @huffman_table_no:	id of the Huffman table
 */
काष्ठा mxc_jpeg_sos_comp अणु
	u8 id; /*component id*/
	u8 huffman_table_no;
पूर्ण __packed;

/**
 * काष्ठा mxc_jpeg_sos - JPEG Start Of Scan marker fields
 * @length:		Start of Frame length
 * @components_no:	number of color components
 * @comp:		SOS component fields क्रम each color component
 * @ignorable_bytes:	ignorable bytes
 */
काष्ठा mxc_jpeg_sos अणु
	u16 length;
	u8 components_no;
	काष्ठा mxc_jpeg_sos_comp comp[MXC_JPEG_MAX_COMPONENTS];
	u8 ignorable_bytes[3];
पूर्ण __packed;

#पूर्ण_अगर
