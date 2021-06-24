<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Jacob Chen <jacob-chen@iotwrt.com>
 */
#अगर_अघोषित __RGA_H__
#घोषणा __RGA_H__

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#घोषणा RGA_NAME "rockchip-rga"

काष्ठा rga_fmt अणु
	u32 fourcc;
	पूर्णांक depth;
	u8 uv_factor;
	u8 y_भाग;
	u8 x_भाग;
	u8 color_swap;
	u8 hw_क्रमmat;
पूर्ण;

काष्ठा rga_frame अणु
	/* Original dimensions */
	u32 width;
	u32 height;
	u32 colorspace;

	/* Crop */
	काष्ठा v4l2_rect crop;

	/* Image क्रमmat */
	काष्ठा rga_fmt *fmt;

	/* Variables that can calculated once and reused */
	u32 stride;
	u32 size;
पूर्ण;

काष्ठा rockchip_rga_version अणु
	u32 major;
	u32 minor;
पूर्ण;

काष्ठा rga_ctx अणु
	काष्ठा v4l2_fh fh;
	काष्ठा rockchip_rga *rga;
	काष्ठा rga_frame in;
	काष्ठा rga_frame out;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	/* Control values */
	u32 op;
	u32 hflip;
	u32 vflip;
	u32 rotate;
	u32 fill_color;
पूर्ण;

काष्ठा rockchip_rga अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा video_device *vfd;

	काष्ठा device *dev;
	काष्ठा regmap *grf;
	व्योम __iomem *regs;
	काष्ठा clk *sclk;
	काष्ठा clk *aclk;
	काष्ठा clk *hclk;
	काष्ठा rockchip_rga_version version;

	/* vfd lock */
	काष्ठा mutex mutex;
	/* ctrl parm lock */
	spinlock_t ctrl_lock;

	काष्ठा rga_ctx *curr;
	dma_addr_t cmdbuf_phy;
	व्योम *cmdbuf_virt;
	अचिन्हित पूर्णांक *src_mmu_pages;
	अचिन्हित पूर्णांक *dst_mmu_pages;
पूर्ण;

काष्ठा rga_frame *rga_get_frame(काष्ठा rga_ctx *ctx, क्रमागत v4l2_buf_type type);

/* RGA Buffers Manage */
बाह्य स्थिर काष्ठा vb2_ops rga_qops;
व्योम rga_buf_map(काष्ठा vb2_buffer *vb);

/* RGA Hardware */
अटल अंतरभूत व्योम rga_ग_लिखो(काष्ठा rockchip_rga *rga, u32 reg, u32 value)
अणु
	ग_लिखोl(value, rga->regs + reg);
पूर्ण;

अटल अंतरभूत u32 rga_पढ़ो(काष्ठा rockchip_rga *rga, u32 reg)
अणु
	वापस पढ़ोl(rga->regs + reg);
पूर्ण;

अटल अंतरभूत व्योम rga_mod(काष्ठा rockchip_rga *rga, u32 reg, u32 val, u32 mask)
अणु
	u32 temp = rga_पढ़ो(rga, reg) & ~(mask);

	temp |= val & mask;
	rga_ग_लिखो(rga, reg, temp);
पूर्ण;

व्योम rga_hw_start(काष्ठा rockchip_rga *rga);

#पूर्ण_अगर
