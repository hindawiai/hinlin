<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Samsung S5P G2D - 2D Graphics Accelerator Driver
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Kamil Debski, <k.debski@samsung.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा G2D_NAME "s5p-g2d"
#घोषणा TYPE_G2D_3X 3
#घोषणा TYPE_G2D_4X 4

काष्ठा g2d_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा video_device	*vfd;
	काष्ठा mutex		mutex;
	spinlock_t		ctrl_lock;
	atomic_t		num_inst;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	काष्ठा clk		*gate;
	काष्ठा g2d_ctx		*curr;
	काष्ठा g2d_variant	*variant;
	पूर्णांक irq;
पूर्ण;

काष्ठा g2d_frame अणु
	/* Original dimensions */
	u32	width;
	u32	height;
	/* Crop size */
	u32	c_width;
	u32	c_height;
	/* Offset */
	u32	o_width;
	u32	o_height;
	/* Image क्रमmat */
	काष्ठा g2d_fmt *fmt;
	/* Variables that can calculated once and reused */
	u32	stride;
	u32	bottom;
	u32	right;
	u32	size;
पूर्ण;

काष्ठा g2d_ctx अणु
	काष्ठा v4l2_fh fh;
	काष्ठा g2d_dev		*dev;
	काष्ठा g2d_frame	in;
	काष्ठा g2d_frame	out;
	काष्ठा v4l2_ctrl	*ctrl_hflip;
	काष्ठा v4l2_ctrl	*ctrl_vflip;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	u32 rop;
	u32 flip;
पूर्ण;

काष्ठा g2d_fmt अणु
	u32	fourcc;
	पूर्णांक	depth;
	u32	hw;
पूर्ण;

काष्ठा g2d_variant अणु
	अचिन्हित लघु hw_rev;
पूर्ण;

व्योम g2d_reset(काष्ठा g2d_dev *d);
व्योम g2d_set_src_size(काष्ठा g2d_dev *d, काष्ठा g2d_frame *f);
व्योम g2d_set_src_addr(काष्ठा g2d_dev *d, dma_addr_t a);
व्योम g2d_set_dst_size(काष्ठा g2d_dev *d, काष्ठा g2d_frame *f);
व्योम g2d_set_dst_addr(काष्ठा g2d_dev *d, dma_addr_t a);
व्योम g2d_start(काष्ठा g2d_dev *d);
व्योम g2d_clear_पूर्णांक(काष्ठा g2d_dev *d);
व्योम g2d_set_rop4(काष्ठा g2d_dev *d, u32 r);
व्योम g2d_set_flip(काष्ठा g2d_dev *d, u32 r);
व्योम g2d_set_v41_stretch(काष्ठा g2d_dev *d,
			काष्ठा g2d_frame *src, काष्ठा g2d_frame *dst);
व्योम g2d_set_cmd(काष्ठा g2d_dev *d, u32 c);
