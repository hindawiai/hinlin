<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 NextThing Co
 * Copyright (C) 2016-2019 Bootlin
 *
 * Author: Maxime Ripard <maxime.ripard@bootlin.com>
 */

#अगर_अघोषित _SUN4I_CSI_H_
#घोषणा _SUN4I_CSI_H_

#समावेश <media/media-device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/videobuf2-core.h>

#घोषणा CSI_EN_REG			0x00

#घोषणा CSI_CFG_REG			0x04
#घोषणा CSI_CFG_INPUT_FMT(fmt)			((fmt) << 20)
#घोषणा CSI_CFG_OUTPUT_FMT(fmt)			((fmt) << 16)
#घोषणा CSI_CFG_YUV_DATA_SEQ(seq)		((seq) << 8)
#घोषणा CSI_CFG_VREF_POL(pol)			((pol) << 2)
#घोषणा CSI_CFG_HREF_POL(pol)			((pol) << 1)
#घोषणा CSI_CFG_PCLK_POL(pol)			((pol) << 0)

#घोषणा CSI_CPT_CTRL_REG		0x08
#घोषणा CSI_CPT_CTRL_VIDEO_START		BIT(1)
#घोषणा CSI_CPT_CTRL_IMAGE_START		BIT(0)

#घोषणा CSI_BUF_ADDR_REG(fअगरo, buf)	(0x10 + (0x8 * (fअगरo)) + (0x4 * (buf)))

#घोषणा CSI_BUF_CTRL_REG		0x28
#घोषणा CSI_BUF_CTRL_DBN			BIT(2)
#घोषणा CSI_BUF_CTRL_DBS			BIT(1)
#घोषणा CSI_BUF_CTRL_DBE			BIT(0)

#घोषणा CSI_INT_EN_REG			0x30
#घोषणा CSI_INT_FRM_DONE			BIT(1)
#घोषणा CSI_INT_CPT_DONE			BIT(0)

#घोषणा CSI_INT_STA_REG			0x34

#घोषणा CSI_WIN_CTRL_W_REG		0x40
#घोषणा CSI_WIN_CTRL_W_ACTIVE(w)		((w) << 16)

#घोषणा CSI_WIN_CTRL_H_REG		0x44
#घोषणा CSI_WIN_CTRL_H_ACTIVE(h)		((h) << 16)

#घोषणा CSI_BUF_LEN_REG			0x48

#घोषणा CSI_MAX_BUFFER		2
#घोषणा CSI_MAX_HEIGHT		8192U
#घोषणा CSI_MAX_WIDTH		8192U

क्रमागत csi_input अणु
	CSI_INPUT_RAW	= 0,
	CSI_INPUT_BT656	= 2,
	CSI_INPUT_YUV	= 3,
पूर्ण;

क्रमागत csi_output_raw अणु
	CSI_OUTPUT_RAW_PASSTHROUGH = 0,
पूर्ण;

क्रमागत csi_output_yuv अणु
	CSI_OUTPUT_YUV_422_PLANAR	= 0,
	CSI_OUTPUT_YUV_420_PLANAR	= 1,
	CSI_OUTPUT_YUV_422_UV		= 4,
	CSI_OUTPUT_YUV_420_UV		= 5,
	CSI_OUTPUT_YUV_422_MACRO	= 8,
	CSI_OUTPUT_YUV_420_MACRO	= 9,
पूर्ण;

क्रमागत csi_yuv_data_seq अणु
	CSI_YUV_DATA_SEQ_YUYV	= 0,
	CSI_YUV_DATA_SEQ_YVYU	= 1,
	CSI_YUV_DATA_SEQ_UYVY	= 2,
	CSI_YUV_DATA_SEQ_VYUY	= 3,
पूर्ण;

क्रमागत csi_subdev_pads अणु
	CSI_SUBDEV_SINK,
	CSI_SUBDEV_SOURCE,

	CSI_SUBDEV_PADS,
पूर्ण;

बाह्य स्थिर काष्ठा v4l2_subdev_ops sun4i_csi_subdev_ops;

काष्ठा sun4i_csi_क्रमmat अणु
	u32			mbus;
	u32			fourcc;
	क्रमागत csi_input		input;
	u32			output;
	अचिन्हित पूर्णांक		num_planes;
	u8			bpp[3];
	अचिन्हित पूर्णांक		hsub;
	अचिन्हित पूर्णांक		vsub;
पूर्ण;

स्थिर काष्ठा sun4i_csi_क्रमmat *sun4i_csi_find_क्रमmat(स्थिर u32 *fourcc,
						     स्थिर u32 *mbus);

काष्ठा sun4i_csi अणु
	/* Device resources */
	काष्ठा device			*dev;

	स्थिर काष्ठा sun4i_csi_traits	*traits;

	व्योम __iomem			*regs;
	काष्ठा clk			*bus_clk;
	काष्ठा clk			*isp_clk;
	काष्ठा clk			*ram_clk;
	काष्ठा reset_control		*rst;

	काष्ठा vb2_v4l2_buffer		*current_buf[CSI_MAX_BUFFER];

	काष्ठा अणु
		माप_प्रकार			size;
		व्योम			*vaddr;
		dma_addr_t		paddr;
	पूर्ण scratch;

	काष्ठा v4l2_fwnode_bus_parallel	bus;

	/* Main Device */
	काष्ठा v4l2_device		v4l;
	काष्ठा media_device		mdev;
	काष्ठा video_device		vdev;
	काष्ठा media_pad		vdev_pad;
	काष्ठा v4l2_pix_क्रमmat_mplane	fmt;

	/* Local subdev */
	काष्ठा v4l2_subdev		subdev;
	काष्ठा media_pad		subdev_pads[CSI_SUBDEV_PADS];
	काष्ठा v4l2_mbus_framefmt	subdev_fmt;

	/* V4L2 Async variables */
	काष्ठा v4l2_async_notअगरier	notअगरier;
	काष्ठा v4l2_subdev		*src_subdev;
	पूर्णांक				src_pad;

	/* V4L2 variables */
	काष्ठा mutex			lock;

	/* Videobuf2 */
	काष्ठा vb2_queue		queue;
	काष्ठा list_head		buf_list;
	spinlock_t			qlock;
	अचिन्हित पूर्णांक			sequence;
पूर्ण;

पूर्णांक sun4i_csi_dma_रेजिस्टर(काष्ठा sun4i_csi *csi, पूर्णांक irq);
व्योम sun4i_csi_dma_unरेजिस्टर(काष्ठा sun4i_csi *csi);

पूर्णांक sun4i_csi_v4l2_रेजिस्टर(काष्ठा sun4i_csi *csi);

#पूर्ण_अगर /* _SUN4I_CSI_H_ */
