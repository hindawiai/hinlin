<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Rockchip Video Decoder driver
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on rkvdec driver by Google LLC. (Tomasz Figa <tfiga@chromium.org>)
 * Based on s5p-mfc driver by Samsung Electronics Co., Ltd.
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 */
#अगर_अघोषित RKVDEC_H_
#घोषणा RKVDEC_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>
#समावेश <linux/clk.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

काष्ठा rkvdec_ctx;

काष्ठा rkvdec_ctrl_desc अणु
	काष्ठा v4l2_ctrl_config cfg;
पूर्ण;

काष्ठा rkvdec_ctrls अणु
	स्थिर काष्ठा rkvdec_ctrl_desc *ctrls;
	अचिन्हित पूर्णांक num_ctrls;
पूर्ण;

काष्ठा rkvdec_run अणु
	काष्ठा अणु
		काष्ठा vb2_v4l2_buffer *src;
		काष्ठा vb2_v4l2_buffer *dst;
	पूर्ण bufs;
पूर्ण;

काष्ठा rkvdec_vp9_decoded_buffer_info अणु
	/* Info needed when the decoded frame serves as a reference frame. */
	u16 width;
	u16 height;
	u32 bit_depth : 4;
पूर्ण;

काष्ठा rkvdec_decoded_buffer अणु
	/* Must be the first field in this काष्ठा. */
	काष्ठा v4l2_m2m_buffer base;
पूर्ण;

अटल अंतरभूत काष्ठा rkvdec_decoded_buffer *
vb2_to_rkvdec_decoded_buf(काष्ठा vb2_buffer *buf)
अणु
	वापस container_of(buf, काष्ठा rkvdec_decoded_buffer,
			    base.vb.vb2_buf);
पूर्ण

काष्ठा rkvdec_coded_fmt_ops अणु
	पूर्णांक (*adjust_fmt)(काष्ठा rkvdec_ctx *ctx,
			  काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*start)(काष्ठा rkvdec_ctx *ctx);
	व्योम (*stop)(काष्ठा rkvdec_ctx *ctx);
	पूर्णांक (*run)(काष्ठा rkvdec_ctx *ctx);
	व्योम (*करोne)(काष्ठा rkvdec_ctx *ctx, काष्ठा vb2_v4l2_buffer *src_buf,
		     काष्ठा vb2_v4l2_buffer *dst_buf,
		     क्रमागत vb2_buffer_state result);
पूर्ण;

काष्ठा rkvdec_coded_fmt_desc अणु
	u32 fourcc;
	काष्ठा v4l2_frmsize_stepwise frmsize;
	स्थिर काष्ठा rkvdec_ctrls *ctrls;
	स्थिर काष्ठा rkvdec_coded_fmt_ops *ops;
	अचिन्हित पूर्णांक num_decoded_fmts;
	स्थिर u32 *decoded_fmts;
पूर्ण;

काष्ठा rkvdec_dev अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device mdev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा device *dev;
	काष्ठा clk_bulk_data *घड़ीs;
	व्योम __iomem *regs;
	काष्ठा mutex vdev_lock; /* serializes ioctls */
	काष्ठा delayed_work watchकरोg_work;
पूर्ण;

काष्ठा rkvdec_ctx अणु
	काष्ठा v4l2_fh fh;
	काष्ठा v4l2_क्रमmat coded_fmt;
	काष्ठा v4l2_क्रमmat decoded_fmt;
	स्थिर काष्ठा rkvdec_coded_fmt_desc *coded_fmt_desc;
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा rkvdec_dev *dev;
	व्योम *priv;
पूर्ण;

अटल अंतरभूत काष्ठा rkvdec_ctx *fh_to_rkvdec_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा rkvdec_ctx, fh);
पूर्ण

काष्ठा rkvdec_aux_buf अणु
	व्योम *cpu;
	dma_addr_t dma;
	माप_प्रकार size;
पूर्ण;

व्योम rkvdec_run_preamble(काष्ठा rkvdec_ctx *ctx, काष्ठा rkvdec_run *run);
व्योम rkvdec_run_postamble(काष्ठा rkvdec_ctx *ctx, काष्ठा rkvdec_run *run);

बाह्य स्थिर काष्ठा rkvdec_coded_fmt_ops rkvdec_h264_fmt_ops;
#पूर्ण_अगर /* RKVDEC_H_ */
