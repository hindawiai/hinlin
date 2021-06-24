<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * i.MX8QXP/i.MX8QM JPEG encoder/decoder v4l2 driver
 *
 * Copyright 2018-2019 NXP
 */

#अगर_अघोषित _MXC_JPEG_HW_H
#घोषणा _MXC_JPEG_HW_H

/* JPEG Decoder/Encoder Wrapper Register Map */
#घोषणा GLB_CTRL			0x0
#घोषणा COM_STATUS			0x4
#घोषणा BUF_BASE0			0x14
#घोषणा BUF_BASE1			0x18
#घोषणा LINE_PITCH			0x1C
#घोषणा STM_BUFBASE			0x20
#घोषणा STM_बफ_मानE			0x24
#घोषणा IMGSIZE				0x28
#घोषणा STM_CTRL			0x2C

/* CAST JPEG-Decoder/Encoder Status Register Map (पढ़ो-only)*/
#घोषणा CAST_STATUS0			0x100
#घोषणा CAST_STATUS1			0x104
#घोषणा CAST_STATUS2			0x108
#घोषणा CAST_STATUS3			0x10c
#घोषणा CAST_STATUS4			0x110
#घोषणा CAST_STATUS5			0x114
#घोषणा CAST_STATUS6			0x118
#घोषणा CAST_STATUS7			0x11c
#घोषणा CAST_STATUS8			0x120
#घोषणा CAST_STATUS9			0x124
#घोषणा CAST_STATUS10			0x128
#घोषणा CAST_STATUS11			0x12c
#घोषणा CAST_STATUS12			0x130
#घोषणा CAST_STATUS13			0x134
/* the following are क्रम encoder only */
#घोषणा CAST_STATUS14		0x138
#घोषणा CAST_STATUS15		0x13c
#घोषणा CAST_STATUS16		0x140
#घोषणा CAST_STATUS17		0x144
#घोषणा CAST_STATUS18		0x148
#घोषणा CAST_STATUS19		0x14c

/* CAST JPEG-Decoder Control Register Map (ग_लिखो-only) */
#घोषणा CAST_CTRL			CAST_STATUS13

/* CAST JPEG-Encoder Control Register Map (ग_लिखो-only) */
#घोषणा CAST_MODE			CAST_STATUS0
#घोषणा CAST_CFG_MODE			CAST_STATUS1
#घोषणा CAST_QUALITY			CAST_STATUS2
#घोषणा CAST_RSVD			CAST_STATUS3
#घोषणा CAST_REC_REGS_SEL		CAST_STATUS4
#घोषणा CAST_LUMTH			CAST_STATUS5
#घोषणा CAST_CHRTH			CAST_STATUS6
#घोषणा CAST_NOMFRSIZE_LO		CAST_STATUS7
#घोषणा CAST_NOMFRSIZE_HI		CAST_STATUS8
#घोषणा CAST_OFBSIZE_LO			CAST_STATUS9
#घोषणा CAST_OFBSIZE_HI			CAST_STATUS10

#घोषणा MXC_MAX_SLOTS	1 /* TODO use all 4 slots*/
/* JPEG-Decoder Wrapper Slot Registers 0..3 */
#घोषणा SLOT_BASE			0x10000
#घोषणा SLOT_STATUS			0x0
#घोषणा SLOT_IRQ_EN			0x4
#घोषणा SLOT_BUF_PTR			0x8
#घोषणा SLOT_CUR_DESCPT_PTR		0xC
#घोषणा SLOT_NXT_DESCPT_PTR		0x10
#घोषणा MXC_SLOT_OFFSET(slot, offset)	((SLOT_BASE * ((slot) + 1)) + (offset))

/* GLB_CTRL fields */
#घोषणा GLB_CTRL_JPG_EN					0x1
#घोषणा GLB_CTRL_SFT_RST				(0x1 << 1)
#घोषणा GLB_CTRL_DEC_GO					(0x1 << 2)
#घोषणा GLB_CTRL_L_ENDIAN(le)				((le) << 3)
#घोषणा GLB_CTRL_SLOT_EN(slot)				(0x1 << ((slot) + 4))

/* COM_STAUS fields */
#घोषणा COM_STATUS_DEC_ONGOING(r)		(((r) & (1 << 31)) >> 31)
#घोषणा COM_STATUS_CUR_SLOT(r)			(((r) & (0x3 << 29)) >> 29)

/* STM_CTRL fields */
#घोषणा STM_CTRL_PIXEL_PRECISION		(0x1 << 2)
#घोषणा STM_CTRL_IMAGE_FORMAT(img_fmt)		((img_fmt) << 3)
#घोषणा STM_CTRL_IMAGE_FORMAT_MASK		(0xF << 3)
#घोषणा STM_CTRL_BITBUF_PTR_CLR(clr)		((clr) << 7)
#घोषणा STM_CTRL_AUTO_START(go)			((go) << 8)
#घोषणा STM_CTRL_CONFIG_MOD(mod)		((mod) << 9)

/* SLOT_STATUS fields क्रम slots 0..3 */
#घोषणा SLOT_STATUS_FRMDONE			(0x1 << 3)
#घोषणा SLOT_STATUS_ENC_CONFIG_ERR		(0x1 << 8)

/* SLOT_IRQ_EN fields TBD */

#घोषणा MXC_NXT_DESCPT_EN			0x1
#घोषणा MXC_DEC_EXIT_IDLE_MODE			0x4

/* JPEG-Decoder Wrapper - STM_CTRL Register Fields */
#घोषणा MXC_PIXEL_PRECISION(precision) ((precision) / 8 << 2)
क्रमागत mxc_jpeg_image_क्रमmat अणु
	MXC_JPEG_INVALID = -1,
	MXC_JPEG_YUV420 = 0x0, /* 2 Plannar, Y=1st plane UV=2nd plane */
	MXC_JPEG_YUV422 = 0x1, /* 1 Plannar, YUYV sequence */
	MXC_JPEG_RGB	= 0x2, /* RGBRGB packed क्रमmat */
	MXC_JPEG_YUV444	= 0x3, /* 1 Plannar, YUVYUV sequence */
	MXC_JPEG_GRAY = 0x4, /* Y8 or Y12 or Single Component */
	MXC_JPEG_RESERVED = 0x5,
	MXC_JPEG_ARGB	= 0x6,
पूर्ण;

#समावेश "mxc-jpeg.h"
व्योम prपूर्णांक_descriptor_info(काष्ठा device *dev, काष्ठा mxc_jpeg_desc *desc);
व्योम prपूर्णांक_cast_status(काष्ठा device *dev, व्योम __iomem *reg,
		       अचिन्हित पूर्णांक mode);
व्योम prपूर्णांक_wrapper_info(काष्ठा device *dev, व्योम __iomem *reg);
व्योम mxc_jpeg_sw_reset(व्योम __iomem *reg);
पूर्णांक mxc_jpeg_enable(व्योम __iomem *reg);
व्योम रुको_frmकरोne(काष्ठा device *dev, व्योम __iomem *reg);
व्योम mxc_jpeg_enc_mode_conf(काष्ठा device *dev, व्योम __iomem *reg);
व्योम mxc_jpeg_enc_mode_go(काष्ठा device *dev, व्योम __iomem *reg);
व्योम mxc_jpeg_dec_mode_go(काष्ठा device *dev, व्योम __iomem *reg);
पूर्णांक mxc_jpeg_get_slot(व्योम __iomem *reg);
u32 mxc_jpeg_get_offset(व्योम __iomem *reg, पूर्णांक slot);
व्योम mxc_jpeg_enable_slot(व्योम __iomem *reg, पूर्णांक slot);
व्योम mxc_jpeg_set_l_endian(व्योम __iomem *reg, पूर्णांक le);
व्योम mxc_jpeg_enable_irq(व्योम __iomem *reg, पूर्णांक slot);
पूर्णांक mxc_jpeg_set_input(व्योम __iomem *reg, u32 in_buf, u32 bufsize);
पूर्णांक mxc_jpeg_set_output(व्योम __iomem *reg, u16 out_pitch, u32 out_buf,
			u16 w, u16 h);
व्योम mxc_jpeg_set_config_mode(व्योम __iomem *reg, पूर्णांक config_mode);
पूर्णांक mxc_jpeg_set_params(काष्ठा mxc_jpeg_desc *desc,  u32 bufsize, u16
			out_pitch, u32 क्रमmat);
व्योम mxc_jpeg_set_bufsize(काष्ठा mxc_jpeg_desc *desc,  u32 bufsize);
व्योम mxc_jpeg_set_res(काष्ठा mxc_jpeg_desc *desc, u16 w, u16 h);
व्योम mxc_jpeg_set_line_pitch(काष्ठा mxc_jpeg_desc *desc, u32 line_pitch);
व्योम mxc_jpeg_set_desc(u32 desc, व्योम __iomem *reg, पूर्णांक slot);
व्योम mxc_jpeg_set_regs_from_desc(काष्ठा mxc_jpeg_desc *desc,
				 व्योम __iomem *reg);
#पूर्ण_अगर
