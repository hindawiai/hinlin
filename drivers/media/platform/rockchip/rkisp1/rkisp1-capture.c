<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - V4l capture device
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on Rockchip ISP1 driver by Rockchip Electronics Co., Ltd.
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "rkisp1-common.h"

/*
 * NOTE: There are two capture video devices in rkisp1, selfpath and मुख्यpath.
 *
 * dअगरferences between selfpath and मुख्यpath
 * available mp sink input: isp
 * available sp sink input : isp, dma(TODO)
 * available mp sink pad fmts: yuv422, raw
 * available sp sink pad fmts: yuv422, yuv420......
 * available mp source fmts: yuv, raw, jpeg(TODO)
 * available sp source fmts: yuv, rgb
 */

#घोषणा RKISP1_SP_DEV_NAME	RKISP1_DRIVER_NAME "_selfpath"
#घोषणा RKISP1_MP_DEV_NAME	RKISP1_DRIVER_NAME "_mainpath"

#घोषणा RKISP1_MIN_BUFFERS_NEEDED 3

क्रमागत rkisp1_plane अणु
	RKISP1_PLANE_Y	= 0,
	RKISP1_PLANE_CB	= 1,
	RKISP1_PLANE_CR	= 2
पूर्ण;

/*
 * @fourcc: pixel क्रमmat
 * @fmt_type: helper filed क्रम pixel क्रमmat
 * @uv_swap: अगर cb cr swapped, क्रम yuv
 * @ग_लिखो_क्रमmat: defines how YCbCr self picture data is written to memory
 * @output_क्रमmat: defines sp output क्रमmat
 * @mbus: the mbus code on the src resizer pad that matches the pixel क्रमmat
 */
काष्ठा rkisp1_capture_fmt_cfg अणु
	u32 fourcc;
	u8 uv_swap;
	u32 ग_लिखो_क्रमmat;
	u32 output_क्रमmat;
	u32 mbus;
पूर्ण;

काष्ठा rkisp1_capture_ops अणु
	व्योम (*config)(काष्ठा rkisp1_capture *cap);
	व्योम (*stop)(काष्ठा rkisp1_capture *cap);
	व्योम (*enable)(काष्ठा rkisp1_capture *cap);
	व्योम (*disable)(काष्ठा rkisp1_capture *cap);
	व्योम (*set_data_path)(काष्ठा rkisp1_capture *cap);
	bool (*is_stopped)(काष्ठा rkisp1_capture *cap);
पूर्ण;

काष्ठा rkisp1_capture_config अणु
	स्थिर काष्ठा rkisp1_capture_fmt_cfg *fmts;
	पूर्णांक fmt_size;
	काष्ठा अणु
		u32 y_size_init;
		u32 cb_size_init;
		u32 cr_size_init;
		u32 y_base_ad_init;
		u32 cb_base_ad_init;
		u32 cr_base_ad_init;
		u32 y_offs_cnt_init;
		u32 cb_offs_cnt_init;
		u32 cr_offs_cnt_init;
	पूर्ण mi;
पूर्ण;

/*
 * The supported pixel क्रमmats क्रम मुख्यpath. NOTE, pixel क्रमmats with identical 'mbus'
 * are grouped together. This is assumed and used by the function rkisp1_cap_क्रमागत_mbus_codes
 */
अटल स्थिर काष्ठा rkisp1_capture_fmt_cfg rkisp1_mp_fmts[] = अणु
	/* yuv422 */
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUVINT,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU422M,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	/* yuv400 */
	अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	/* yuv420 */
	अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV21M,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12M,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_SPLA,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV420,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU420,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण,
	/* raw */
	अणु
		.fourcc = V4L2_PIX_FMT_SRGGB8,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_SRGGB8_1X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG8,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_SGRBG8_1X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG8,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_SGBRG8_1X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SBGGR8,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_YUV_PLA_OR_RAW8,
		.mbus = MEDIA_BUS_FMT_SBGGR8_1X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SRGGB10,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SRGGB10_1X10,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG10,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SGRBG10_1X10,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG10,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SGBRG10_1X10,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SBGGR10,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SBGGR10_1X10,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SRGGB12,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SRGGB12_1X12,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG12,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SGRBG12_1X12,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG12,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SGBRG12_1X12,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SBGGR12,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_MP_WRITE_RAW12,
		.mbus = MEDIA_BUS_FMT_SBGGR12_1X12,
	पूर्ण,
पूर्ण;

/*
 * The supported pixel क्रमmats क्रम selfpath. NOTE, pixel क्रमmats with identical 'mbus'
 * are grouped together. This is assumed and used by the function rkisp1_cap_क्रमागत_mbus_codes
 */
अटल स्थिर काष्ठा rkisp1_capture_fmt_cfg rkisp1_sp_fmts[] = अणु
	/* yuv422 */
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_INT,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV422,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV422,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV422,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV61,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV422,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU422M,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV422,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	/* yuv400 */
	अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV400,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	/* rgb */
	अणु
		.fourcc = V4L2_PIX_FMT_XBGR32,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_RGB888,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_RGB565,
		.mbus = MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	/* yuv420 */
	अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV21M,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12M,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_SPLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV420,
		.uv_swap = 0,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU420,
		.uv_swap = 1,
		.ग_लिखो_क्रमmat = RKISP1_MI_CTRL_SP_WRITE_PLA,
		.output_क्रमmat = RKISP1_MI_CTRL_SP_OUTPUT_YUV420,
		.mbus = MEDIA_BUS_FMT_YUYV8_1_5X8,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rkisp1_capture_config rkisp1_capture_config_mp = अणु
	.fmts = rkisp1_mp_fmts,
	.fmt_size = ARRAY_SIZE(rkisp1_mp_fmts),
	.mi = अणु
		.y_size_init =		RKISP1_CIF_MI_MP_Y_SIZE_INIT,
		.cb_size_init =		RKISP1_CIF_MI_MP_CB_SIZE_INIT,
		.cr_size_init =		RKISP1_CIF_MI_MP_CR_SIZE_INIT,
		.y_base_ad_init =	RKISP1_CIF_MI_MP_Y_BASE_AD_INIT,
		.cb_base_ad_init =	RKISP1_CIF_MI_MP_CB_BASE_AD_INIT,
		.cr_base_ad_init =	RKISP1_CIF_MI_MP_CR_BASE_AD_INIT,
		.y_offs_cnt_init =	RKISP1_CIF_MI_MP_Y_OFFS_CNT_INIT,
		.cb_offs_cnt_init =	RKISP1_CIF_MI_MP_CB_OFFS_CNT_INIT,
		.cr_offs_cnt_init =	RKISP1_CIF_MI_MP_CR_OFFS_CNT_INIT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rkisp1_capture_config rkisp1_capture_config_sp = अणु
	.fmts = rkisp1_sp_fmts,
	.fmt_size = ARRAY_SIZE(rkisp1_sp_fmts),
	.mi = अणु
		.y_size_init =		RKISP1_CIF_MI_SP_Y_SIZE_INIT,
		.cb_size_init =		RKISP1_CIF_MI_SP_CB_SIZE_INIT,
		.cr_size_init =		RKISP1_CIF_MI_SP_CR_SIZE_INIT,
		.y_base_ad_init =	RKISP1_CIF_MI_SP_Y_BASE_AD_INIT,
		.cb_base_ad_init =	RKISP1_CIF_MI_SP_CB_BASE_AD_INIT,
		.cr_base_ad_init =	RKISP1_CIF_MI_SP_CR_BASE_AD_INIT,
		.y_offs_cnt_init =	RKISP1_CIF_MI_SP_Y_OFFS_CNT_INIT,
		.cb_offs_cnt_init =	RKISP1_CIF_MI_SP_CB_OFFS_CNT_INIT,
		.cr_offs_cnt_init =	RKISP1_CIF_MI_SP_CR_OFFS_CNT_INIT,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा rkisp1_vdev_node *
rkisp1_vdev_to_node(काष्ठा video_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा rkisp1_vdev_node, vdev);
पूर्ण

पूर्णांक rkisp1_cap_क्रमागत_mbus_codes(काष्ठा rkisp1_capture *cap,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	स्थिर काष्ठा rkisp1_capture_fmt_cfg *fmts = cap->config->fmts;
	/*
	 * initialize curr_mbus to non existing mbus code 0 to ensure it is
	 * dअगरferent from fmts[0].mbus
	 */
	u32 curr_mbus = 0;
	पूर्णांक i, n = 0;

	क्रम (i = 0; i < cap->config->fmt_size; i++) अणु
		अगर (fmts[i].mbus == curr_mbus)
			जारी;

		curr_mbus = fmts[i].mbus;
		अगर (n++ == code->index) अणु
			code->code = curr_mbus;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ----------------------------------------------------------------------------
 * Stream operations क्रम self-picture path (sp) and मुख्य-picture path (mp)
 */

अटल व्योम rkisp1_mi_config_ctrl(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_ctrl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL);

	mi_ctrl &= ~GENMASK(17, 16);
	mi_ctrl |= RKISP1_CIF_MI_CTRL_BURST_LEN_LUM_64;

	mi_ctrl &= ~GENMASK(19, 18);
	mi_ctrl |= RKISP1_CIF_MI_CTRL_BURST_LEN_CHROM_64;

	mi_ctrl |= RKISP1_CIF_MI_CTRL_INIT_BASE_EN |
		   RKISP1_CIF_MI_CTRL_INIT_OFFSET_EN;

	rkisp1_ग_लिखो(cap->rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल u32 rkisp1_pixfmt_comp_size(स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm,
				   अचिन्हित पूर्णांक component)
अणु
	/*
	 * If packed क्रमmat, then plane_fmt[0].sizeimage is the sum of all
	 * components, so we need to calculate just the size of Y component.
	 * See rkisp1_fill_pixfmt().
	 */
	अगर (!component && pixm->num_planes == 1)
		वापस pixm->plane_fmt[0].bytesperline * pixm->height;
	वापस pixm->plane_fmt[component].sizeimage;
पूर्ण

अटल व्योम rkisp1_irq_frame_end_enable(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_imsc = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_IMSC);

	mi_imsc |= RKISP1_CIF_MI_FRAME(cap);
	rkisp1_ग_लिखो(cap->rkisp1, mi_imsc, RKISP1_CIF_MI_IMSC);
पूर्ण

अटल व्योम rkisp1_mp_config(काष्ठा rkisp1_capture *cap)
अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &cap->pix.fmt;
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;
	u32 reg;

	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_Y),
		     cap->config->mi.y_size_init);
	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CB),
		     cap->config->mi.cb_size_init);
	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CR),
		     cap->config->mi.cr_size_init);

	rkisp1_irq_frame_end_enable(cap);

	/* set uv swapping क्रम semiplanar क्रमmats */
	अगर (cap->pix.info->comp_planes == 2) अणु
		reg = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_XTD_FORMAT_CTRL);
		अगर (cap->pix.cfg->uv_swap)
			reg |= RKISP1_CIF_MI_XTD_FMT_CTRL_MP_CB_CR_SWAP;
		अन्यथा
			reg &= ~RKISP1_CIF_MI_XTD_FMT_CTRL_MP_CB_CR_SWAP;
		rkisp1_ग_लिखो(rkisp1, reg, RKISP1_CIF_MI_XTD_FORMAT_CTRL);
	पूर्ण

	rkisp1_mi_config_ctrl(cap);

	reg = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_CTRL);
	reg &= ~RKISP1_MI_CTRL_MP_FMT_MASK;
	reg |= cap->pix.cfg->ग_लिखो_क्रमmat;
	rkisp1_ग_लिखो(rkisp1, reg, RKISP1_CIF_MI_CTRL);

	reg = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_CTRL);
	reg |= RKISP1_CIF_MI_MP_AUTOUPDATE_ENABLE;
	rkisp1_ग_लिखो(rkisp1, reg, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_sp_config(काष्ठा rkisp1_capture *cap)
अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &cap->pix.fmt;
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;
	u32 mi_ctrl, reg;

	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_Y),
		     cap->config->mi.y_size_init);
	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CB),
		     cap->config->mi.cb_size_init);
	rkisp1_ग_लिखो(rkisp1, rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CR),
		     cap->config->mi.cr_size_init);

	rkisp1_ग_लिखो(rkisp1, pixm->width, RKISP1_CIF_MI_SP_Y_PIC_WIDTH);
	rkisp1_ग_लिखो(rkisp1, pixm->height, RKISP1_CIF_MI_SP_Y_PIC_HEIGHT);
	rkisp1_ग_लिखो(rkisp1, cap->sp_y_stride, RKISP1_CIF_MI_SP_Y_LLENGTH);

	rkisp1_irq_frame_end_enable(cap);

	/* set uv swapping क्रम semiplanar क्रमmats */
	अगर (cap->pix.info->comp_planes == 2) अणु
		reg = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_XTD_FORMAT_CTRL);
		अगर (cap->pix.cfg->uv_swap)
			reg |= RKISP1_CIF_MI_XTD_FMT_CTRL_SP_CB_CR_SWAP;
		अन्यथा
			reg &= ~RKISP1_CIF_MI_XTD_FMT_CTRL_SP_CB_CR_SWAP;
		rkisp1_ग_लिखो(rkisp1, reg, RKISP1_CIF_MI_XTD_FORMAT_CTRL);
	पूर्ण

	rkisp1_mi_config_ctrl(cap);

	mi_ctrl = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_CTRL);
	mi_ctrl &= ~RKISP1_MI_CTRL_SP_FMT_MASK;
	mi_ctrl |= cap->pix.cfg->ग_लिखो_क्रमmat |
		   RKISP1_MI_CTRL_SP_INPUT_YUV422 |
		   cap->pix.cfg->output_क्रमmat |
		   RKISP1_CIF_MI_SP_AUTOUPDATE_ENABLE;
	rkisp1_ग_लिखो(rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_mp_disable(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_ctrl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL);

	mi_ctrl &= ~(RKISP1_CIF_MI_CTRL_MP_ENABLE |
		     RKISP1_CIF_MI_CTRL_RAW_ENABLE);
	rkisp1_ग_लिखो(cap->rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_sp_disable(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_ctrl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL);

	mi_ctrl &= ~RKISP1_CIF_MI_CTRL_SP_ENABLE;
	rkisp1_ग_लिखो(cap->rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_mp_enable(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_ctrl;

	rkisp1_mp_disable(cap);

	mi_ctrl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL);
	अगर (v4l2_is_क्रमmat_bayer(cap->pix.info))
		mi_ctrl |= RKISP1_CIF_MI_CTRL_RAW_ENABLE;
	/* YUV */
	अन्यथा
		mi_ctrl |= RKISP1_CIF_MI_CTRL_MP_ENABLE;

	rkisp1_ग_लिखो(cap->rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_sp_enable(काष्ठा rkisp1_capture *cap)
अणु
	u32 mi_ctrl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL);

	mi_ctrl |= RKISP1_CIF_MI_CTRL_SP_ENABLE;
	rkisp1_ग_लिखो(cap->rkisp1, mi_ctrl, RKISP1_CIF_MI_CTRL);
पूर्ण

अटल व्योम rkisp1_mp_sp_stop(काष्ठा rkisp1_capture *cap)
अणु
	अगर (!cap->is_streaming)
		वापस;
	rkisp1_ग_लिखो(cap->rkisp1,
		     RKISP1_CIF_MI_FRAME(cap), RKISP1_CIF_MI_ICR);
	cap->ops->disable(cap);
पूर्ण

अटल bool rkisp1_mp_is_stopped(काष्ठा rkisp1_capture *cap)
अणु
	u32 en = RKISP1_CIF_MI_CTRL_SHD_MP_IN_ENABLED |
		 RKISP1_CIF_MI_CTRL_SHD_RAW_OUT_ENABLED;

	वापस !(rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL_SHD) & en);
पूर्ण

अटल bool rkisp1_sp_is_stopped(काष्ठा rkisp1_capture *cap)
अणु
	वापस !(rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_MI_CTRL_SHD) &
		 RKISP1_CIF_MI_CTRL_SHD_SP_IN_ENABLED);
पूर्ण

अटल व्योम rkisp1_mp_set_data_path(काष्ठा rkisp1_capture *cap)
अणु
	u32 dpcl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_VI_DPCL);

	dpcl = dpcl | RKISP1_CIF_VI_DPCL_CHAN_MODE_MP |
	       RKISP1_CIF_VI_DPCL_MP_MUX_MRSZ_MI;
	rkisp1_ग_लिखो(cap->rkisp1, dpcl, RKISP1_CIF_VI_DPCL);
पूर्ण

अटल व्योम rkisp1_sp_set_data_path(काष्ठा rkisp1_capture *cap)
अणु
	u32 dpcl = rkisp1_पढ़ो(cap->rkisp1, RKISP1_CIF_VI_DPCL);

	dpcl |= RKISP1_CIF_VI_DPCL_CHAN_MODE_SP;
	rkisp1_ग_लिखो(cap->rkisp1, dpcl, RKISP1_CIF_VI_DPCL);
पूर्ण

अटल स्थिर काष्ठा rkisp1_capture_ops rkisp1_capture_ops_mp = अणु
	.config = rkisp1_mp_config,
	.enable = rkisp1_mp_enable,
	.disable = rkisp1_mp_disable,
	.stop = rkisp1_mp_sp_stop,
	.set_data_path = rkisp1_mp_set_data_path,
	.is_stopped = rkisp1_mp_is_stopped,
पूर्ण;

अटल स्थिर काष्ठा rkisp1_capture_ops rkisp1_capture_ops_sp = अणु
	.config = rkisp1_sp_config,
	.enable = rkisp1_sp_enable,
	.disable = rkisp1_sp_disable,
	.stop = rkisp1_mp_sp_stop,
	.set_data_path = rkisp1_sp_set_data_path,
	.is_stopped = rkisp1_sp_is_stopped,
पूर्ण;

/* ----------------------------------------------------------------------------
 * Frame buffer operations
 */

अटल पूर्णांक rkisp1_dummy_buf_create(काष्ठा rkisp1_capture *cap)
अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &cap->pix.fmt;
	काष्ठा rkisp1_dummy_buffer *dummy_buf = &cap->buf.dummy;

	dummy_buf->size = max3(rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_Y),
			       rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CB),
			       rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CR));

	/* The driver never access vaddr, no mapping is required */
	dummy_buf->vaddr = dma_alloc_attrs(cap->rkisp1->dev,
					   dummy_buf->size,
					   &dummy_buf->dma_addr,
					   GFP_KERNEL,
					   DMA_ATTR_NO_KERNEL_MAPPING);
	अगर (!dummy_buf->vaddr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम rkisp1_dummy_buf_destroy(काष्ठा rkisp1_capture *cap)
अणु
	dma_मुक्त_attrs(cap->rkisp1->dev,
		       cap->buf.dummy.size, cap->buf.dummy.vaddr,
		       cap->buf.dummy.dma_addr, DMA_ATTR_NO_KERNEL_MAPPING);
पूर्ण

अटल व्योम rkisp1_set_next_buf(काष्ठा rkisp1_capture *cap)
अणु
	cap->buf.curr = cap->buf.next;
	cap->buf.next = शून्य;

	अगर (!list_empty(&cap->buf.queue)) अणु
		u32 *buff_addr;

		cap->buf.next = list_first_entry(&cap->buf.queue, काष्ठा rkisp1_buffer, queue);
		list_del(&cap->buf.next->queue);

		buff_addr = cap->buf.next->buff_addr;

		rkisp1_ग_लिखो(cap->rkisp1,
			     buff_addr[RKISP1_PLANE_Y],
			     cap->config->mi.y_base_ad_init);
		rkisp1_ग_लिखो(cap->rkisp1,
			     buff_addr[RKISP1_PLANE_CB],
			     cap->config->mi.cb_base_ad_init);
		rkisp1_ग_लिखो(cap->rkisp1,
			     buff_addr[RKISP1_PLANE_CR],
			     cap->config->mi.cr_base_ad_init);
	पूर्ण अन्यथा अणु
		/*
		 * Use the dummy space allocated by dma_alloc_coherent to
		 * throw data अगर there is no available buffer.
		 */
		rkisp1_ग_लिखो(cap->rkisp1,
			     cap->buf.dummy.dma_addr,
			     cap->config->mi.y_base_ad_init);
		rkisp1_ग_लिखो(cap->rkisp1,
			     cap->buf.dummy.dma_addr,
			     cap->config->mi.cb_base_ad_init);
		rkisp1_ग_लिखो(cap->rkisp1,
			     cap->buf.dummy.dma_addr,
			     cap->config->mi.cr_base_ad_init);
	पूर्ण

	/* Set plane offsets */
	rkisp1_ग_लिखो(cap->rkisp1, 0, cap->config->mi.y_offs_cnt_init);
	rkisp1_ग_लिखो(cap->rkisp1, 0, cap->config->mi.cb_offs_cnt_init);
	rkisp1_ग_लिखो(cap->rkisp1, 0, cap->config->mi.cr_offs_cnt_init);
पूर्ण

/*
 * This function is called when a frame end comes. The next frame
 * is processing and we should set up buffer क्रम next-next frame,
 * otherwise it will overflow.
 */
अटल व्योम rkisp1_handle_buffer(काष्ठा rkisp1_capture *cap)
अणु
	काष्ठा rkisp1_isp *isp = &cap->rkisp1->isp;
	काष्ठा rkisp1_buffer *curr_buf;

	spin_lock(&cap->buf.lock);
	curr_buf = cap->buf.curr;

	अगर (curr_buf) अणु
		curr_buf->vb.sequence = isp->frame_sequence;
		curr_buf->vb.vb2_buf.बारtamp = kसमय_get_bootसमय_ns();
		curr_buf->vb.field = V4L2_FIELD_NONE;
		vb2_buffer_करोne(&curr_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण अन्यथा अणु
		cap->rkisp1->debug.frame_drop[cap->id]++;
	पूर्ण

	rkisp1_set_next_buf(cap);
	spin_unlock(&cap->buf.lock);
पूर्ण

व्योम rkisp1_capture_isr(काष्ठा rkisp1_device *rkisp1)
अणु
	अचिन्हित पूर्णांक i;
	u32 status;

	status = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MI_MIS);
	rkisp1_ग_लिखो(rkisp1, status, RKISP1_CIF_MI_ICR);

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1->capture_devs); ++i) अणु
		काष्ठा rkisp1_capture *cap = &rkisp1->capture_devs[i];

		अगर (!(status & RKISP1_CIF_MI_FRAME(cap)))
			जारी;
		अगर (!cap->is_stopping) अणु
			rkisp1_handle_buffer(cap);
			जारी;
		पूर्ण
		/*
		 * Make sure stream is actually stopped, whose state
		 * can be पढ़ो from the shaकरोw रेजिस्टर, beक्रमe
		 * wake_up() thपढ़ो which would immediately मुक्त all
		 * frame buffers. stop() takes effect at the next
		 * frame end that sync the configurations to shaकरोw
		 * regs.
		 */
		अगर (!cap->ops->is_stopped(cap)) अणु
			cap->ops->stop(cap);
			जारी;
		पूर्ण
		cap->is_stopping = false;
		cap->is_streaming = false;
		wake_up(&cap->करोne);
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------------
 * Vb2 operations
 */

अटल पूर्णांक rkisp1_vb2_queue_setup(काष्ठा vb2_queue *queue,
				  अचिन्हित पूर्णांक *num_buffers,
				  अचिन्हित पूर्णांक *num_planes,
				  अचिन्हित पूर्णांक sizes[],
				  काष्ठा device *alloc_devs[])
अणु
	काष्ठा rkisp1_capture *cap = queue->drv_priv;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &cap->pix.fmt;
	अचिन्हित पूर्णांक i;

	अगर (*num_planes) अणु
		अगर (*num_planes != pixm->num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < pixm->num_planes; i++)
			अगर (sizes[i] < pixm->plane_fmt[i].sizeimage)
				वापस -EINVAL;
	पूर्ण अन्यथा अणु
		*num_planes = pixm->num_planes;
		क्रम (i = 0; i < pixm->num_planes; i++)
			sizes[i] = pixm->plane_fmt[i].sizeimage;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rkisp1_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rkisp1_buffer *ispbuf =
		container_of(vbuf, काष्ठा rkisp1_buffer, vb);
	काष्ठा rkisp1_capture *cap = vb->vb2_queue->drv_priv;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &cap->pix.fmt;
	अचिन्हित पूर्णांक i;

	स_रखो(ispbuf->buff_addr, 0, माप(ispbuf->buff_addr));
	क्रम (i = 0; i < pixm->num_planes; i++)
		ispbuf->buff_addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);

	/* Convert to non-MPLANE */
	अगर (pixm->num_planes == 1) अणु
		ispbuf->buff_addr[RKISP1_PLANE_CB] =
			ispbuf->buff_addr[RKISP1_PLANE_Y] +
			rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_Y);
		ispbuf->buff_addr[RKISP1_PLANE_CR] =
			ispbuf->buff_addr[RKISP1_PLANE_CB] +
			rkisp1_pixfmt_comp_size(pixm, RKISP1_PLANE_CB);
	पूर्ण

	/*
	 * uv swap can be supported क्रम planar क्रमmats by चयनing
	 * the address of cb and cr
	 */
	अगर (cap->pix.info->comp_planes == 3 && cap->pix.cfg->uv_swap)
		swap(ispbuf->buff_addr[RKISP1_PLANE_CR],
		     ispbuf->buff_addr[RKISP1_PLANE_CB]);

	spin_lock_irq(&cap->buf.lock);
	list_add_tail(&ispbuf->queue, &cap->buf.queue);
	spin_unlock_irq(&cap->buf.lock);
पूर्ण

अटल पूर्णांक rkisp1_vb2_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rkisp1_capture *cap = vb->vb2_queue->drv_priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cap->pix.fmt.num_planes; i++) अणु
		अचिन्हित दीर्घ size = cap->pix.fmt.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < size) अणु
			dev_err(cap->rkisp1->dev,
				"User buffer too small (%ld < %ld)\n",
				vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण
		vb2_set_plane_payload(vb, i, size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rkisp1_वापस_all_buffers(काष्ठा rkisp1_capture *cap,
				      क्रमागत vb2_buffer_state state)
अणु
	काष्ठा rkisp1_buffer *buf;

	spin_lock_irq(&cap->buf.lock);
	अगर (cap->buf.curr) अणु
		vb2_buffer_करोne(&cap->buf.curr->vb.vb2_buf, state);
		cap->buf.curr = शून्य;
	पूर्ण
	अगर (cap->buf.next) अणु
		vb2_buffer_करोne(&cap->buf.next->vb.vb2_buf, state);
		cap->buf.next = शून्य;
	पूर्ण
	जबतक (!list_empty(&cap->buf.queue)) अणु
		buf = list_first_entry(&cap->buf.queue,
				       काष्ठा rkisp1_buffer, queue);
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण
	spin_unlock_irq(&cap->buf.lock);
पूर्ण

/*
 * Most of रेजिस्टरs inside rockchip ISP1 have shaकरोw रेजिस्टर since
 * they must be not be changed during processing a frame.
 * Usually, each sub-module updates its shaकरोw रेजिस्टर after
 * processing the last pixel of a frame.
 */
अटल व्योम rkisp1_cap_stream_enable(काष्ठा rkisp1_capture *cap)
अणु
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;
	काष्ठा rkisp1_capture *other = &rkisp1->capture_devs[cap->id ^ 1];

	cap->ops->set_data_path(cap);
	cap->ops->config(cap);

	/* Setup a buffer क्रम the next frame */
	spin_lock_irq(&cap->buf.lock);
	rkisp1_set_next_buf(cap);
	cap->ops->enable(cap);
	/* It's safe to config ACTIVE and SHADOW regs क्रम the
	 * first stream. While when the second is starting, करो NOT
	 * क्रमce update because it also update the first one.
	 *
	 * The latter हाल would drop one more buf(that is 2) since
	 * there's not buf in shadow when the second FE received. This's
	 * also required because the second FE maybe corrupt especially
	 * when run at 120fps.
	 */
	अगर (!other->is_streaming) अणु
		/* क्रमce cfg update */
		rkisp1_ग_लिखो(rkisp1,
			     RKISP1_CIF_MI_INIT_SOFT_UPD, RKISP1_CIF_MI_INIT);
		rkisp1_set_next_buf(cap);
	पूर्ण
	spin_unlock_irq(&cap->buf.lock);
	cap->is_streaming = true;
पूर्ण

अटल व्योम rkisp1_cap_stream_disable(काष्ठा rkisp1_capture *cap)
अणु
	पूर्णांक ret;

	/* Stream should stop in पूर्णांकerrupt. If it करोesn't, stop it by क्रमce. */
	cap->is_stopping = true;
	ret = रुको_event_समयout(cap->करोne,
				 !cap->is_streaming,
				 msecs_to_jअगरfies(1000));
	अगर (!ret) अणु
		cap->rkisp1->debug.stop_समयout[cap->id]++;
		cap->ops->stop(cap);
		cap->is_stopping = false;
		cap->is_streaming = false;
	पूर्ण
पूर्ण

/*
 * rkisp1_pipeline_stream_disable - disable nodes in the pipeline
 *
 * Call s_stream(false) in the reverse order from
 * rkisp1_pipeline_stream_enable() and disable the DMA engine.
 * Should be called beक्रमe media_pipeline_stop()
 */
अटल व्योम rkisp1_pipeline_stream_disable(काष्ठा rkisp1_capture *cap)
	__must_hold(&cap->rkisp1->stream_lock)
अणु
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;

	rkisp1_cap_stream_disable(cap);

	/*
	 * If the other capture is streaming, isp and sensor nodes shouldn't
	 * be disabled, skip them.
	 */
	अगर (rkisp1->pipe.streaming_count < 2) अणु
		v4l2_subdev_call(rkisp1->active_sensor->sd, video, s_stream,
				 false);
		v4l2_subdev_call(&rkisp1->isp.sd, video, s_stream, false);
	पूर्ण

	v4l2_subdev_call(&rkisp1->resizer_devs[cap->id].sd, video, s_stream,
			 false);
पूर्ण

/*
 * rkisp1_pipeline_stream_enable - enable nodes in the pipeline
 *
 * Enable the DMA Engine and call s_stream(true) through the pipeline.
 * Should be called after media_pipeline_start()
 */
अटल पूर्णांक rkisp1_pipeline_stream_enable(काष्ठा rkisp1_capture *cap)
	__must_hold(&cap->rkisp1->stream_lock)
अणु
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;
	पूर्णांक ret;

	rkisp1_cap_stream_enable(cap);

	ret = v4l2_subdev_call(&rkisp1->resizer_devs[cap->id].sd, video,
			       s_stream, true);
	अगर (ret)
		जाओ err_disable_cap;

	/*
	 * If the other capture is streaming, isp and sensor nodes are alपढ़ोy
	 * enabled, skip them.
	 */
	अगर (rkisp1->pipe.streaming_count > 1)
		वापस 0;

	ret = v4l2_subdev_call(&rkisp1->isp.sd, video, s_stream, true);
	अगर (ret)
		जाओ err_disable_rsz;

	ret = v4l2_subdev_call(rkisp1->active_sensor->sd, video, s_stream,
			       true);
	अगर (ret)
		जाओ err_disable_isp;

	वापस 0;

err_disable_isp:
	v4l2_subdev_call(&rkisp1->isp.sd, video, s_stream, false);
err_disable_rsz:
	v4l2_subdev_call(&rkisp1->resizer_devs[cap->id].sd, video, s_stream,
			 false);
err_disable_cap:
	rkisp1_cap_stream_disable(cap);

	वापस ret;
पूर्ण

अटल व्योम rkisp1_vb2_stop_streaming(काष्ठा vb2_queue *queue)
अणु
	काष्ठा rkisp1_capture *cap = queue->drv_priv;
	काष्ठा rkisp1_vdev_node *node = &cap->vnode;
	काष्ठा rkisp1_device *rkisp1 = cap->rkisp1;
	पूर्णांक ret;

	mutex_lock(&cap->rkisp1->stream_lock);

	rkisp1_pipeline_stream_disable(cap);

	rkisp1_वापस_all_buffers(cap, VB2_BUF_STATE_ERROR);

	v4l2_pipeline_pm_put(&node->vdev.entity);
	ret = pm_runसमय_put(rkisp1->dev);
	अगर (ret < 0)
		dev_err(rkisp1->dev, "power down failed error:%d\n", ret);

	rkisp1_dummy_buf_destroy(cap);

	media_pipeline_stop(&node->vdev.entity);

	mutex_unlock(&cap->rkisp1->stream_lock);
पूर्ण

अटल पूर्णांक
rkisp1_vb2_start_streaming(काष्ठा vb2_queue *queue, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rkisp1_capture *cap = queue->drv_priv;
	काष्ठा media_entity *entity = &cap->vnode.vdev.entity;
	पूर्णांक ret;

	mutex_lock(&cap->rkisp1->stream_lock);

	ret = media_pipeline_start(entity, &cap->rkisp1->pipe);
	अगर (ret) अणु
		dev_err(cap->rkisp1->dev, "start pipeline failed %d\n", ret);
		जाओ err_ret_buffers;
	पूर्ण

	ret = rkisp1_dummy_buf_create(cap);
	अगर (ret)
		जाओ err_pipeline_stop;

	ret = pm_runसमय_get_sync(cap->rkisp1->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cap->rkisp1->dev);
		dev_err(cap->rkisp1->dev, "power up failed %d\n", ret);
		जाओ err_destroy_dummy;
	पूर्ण
	ret = v4l2_pipeline_pm_get(entity);
	अगर (ret) अणु
		dev_err(cap->rkisp1->dev, "open cif pipeline failed %d\n", ret);
		जाओ err_pipe_pm_put;
	पूर्ण

	ret = rkisp1_pipeline_stream_enable(cap);
	अगर (ret)
		जाओ err_v4l2_pm_put;

	mutex_unlock(&cap->rkisp1->stream_lock);

	वापस 0;

err_v4l2_pm_put:
	v4l2_pipeline_pm_put(entity);
err_pipe_pm_put:
	pm_runसमय_put(cap->rkisp1->dev);
err_destroy_dummy:
	rkisp1_dummy_buf_destroy(cap);
err_pipeline_stop:
	media_pipeline_stop(entity);
err_ret_buffers:
	rkisp1_वापस_all_buffers(cap, VB2_BUF_STATE_QUEUED);
	mutex_unlock(&cap->rkisp1->stream_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vb2_ops rkisp1_vb2_ops = अणु
	.queue_setup = rkisp1_vb2_queue_setup,
	.buf_queue = rkisp1_vb2_buf_queue,
	.buf_prepare = rkisp1_vb2_buf_prepare,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.stop_streaming = rkisp1_vb2_stop_streaming,
	.start_streaming = rkisp1_vb2_start_streaming,
पूर्ण;

/* ----------------------------------------------------------------------------
 * IOCTLs operations
 */

अटल स्थिर काष्ठा v4l2_क्रमmat_info *
rkisp1_fill_pixfmt(काष्ठा v4l2_pix_क्रमmat_mplane *pixm,
		   क्रमागत rkisp1_stream_id id)
अणु
	काष्ठा v4l2_plane_pix_क्रमmat *plane_y = &pixm->plane_fmt[0];
	स्थिर काष्ठा v4l2_क्रमmat_info *info;
	अचिन्हित पूर्णांक i;
	u32 stride;

	स_रखो(pixm->plane_fmt, 0, माप(pixm->plane_fmt));
	info = v4l2_क्रमmat_info(pixm->pixelक्रमmat);
	pixm->num_planes = info->mem_planes;
	stride = info->bpp[0] * pixm->width;
	/* Self path supports custom stride but Main path करोesn't */
	अगर (id == RKISP1_MAINPATH || plane_y->bytesperline < stride)
		plane_y->bytesperline = stride;
	plane_y->sizeimage = plane_y->bytesperline * pixm->height;

	/* normalize stride to pixels per line */
	stride = DIV_ROUND_UP(plane_y->bytesperline, info->bpp[0]);

	क्रम (i = 1; i < info->comp_planes; i++) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *plane = &pixm->plane_fmt[i];

		/* bytesperline क्रम other components derive from Y component */
		plane->bytesperline = DIV_ROUND_UP(stride, info->hभाग) *
				      info->bpp[i];
		plane->sizeimage = plane->bytesperline *
				   DIV_ROUND_UP(pixm->height, info->vभाग);
	पूर्ण

	/*
	 * If pixfmt is packed, then plane_fmt[0] should contain the total size
	 * considering all components. plane_fmt[i] क्रम i > 0 should be ignored
	 * by userspace as mem_planes == 1, but we are keeping inक्रमmation there
	 * क्रम convenience.
	 */
	अगर (info->mem_planes == 1)
		क्रम (i = 1; i < info->comp_planes; i++)
			plane_y->sizeimage += pixm->plane_fmt[i].sizeimage;

	वापस info;
पूर्ण

अटल स्थिर काष्ठा rkisp1_capture_fmt_cfg *
rkisp1_find_fmt_cfg(स्थिर काष्ठा rkisp1_capture *cap, स्थिर u32 pixelfmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cap->config->fmt_size; i++) अणु
		अगर (cap->config->fmts[i].fourcc == pixelfmt)
			वापस &cap->config->fmts[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम rkisp1_try_fmt(स्थिर काष्ठा rkisp1_capture *cap,
			   काष्ठा v4l2_pix_क्रमmat_mplane *pixm,
			   स्थिर काष्ठा rkisp1_capture_fmt_cfg **fmt_cfg,
			   स्थिर काष्ठा v4l2_क्रमmat_info **fmt_info)
अणु
	स्थिर काष्ठा rkisp1_capture_config *config = cap->config;
	स्थिर काष्ठा rkisp1_capture_fmt_cfg *fmt;
	स्थिर काष्ठा v4l2_क्रमmat_info *info;
	स्थिर अचिन्हित पूर्णांक max_widths[] = अणु RKISP1_RSZ_MP_SRC_MAX_WIDTH,
					    RKISP1_RSZ_SP_SRC_MAX_WIDTH पूर्ण;
	स्थिर अचिन्हित पूर्णांक max_heights[] = अणु RKISP1_RSZ_MP_SRC_MAX_HEIGHT,
					     RKISP1_RSZ_SP_SRC_MAX_HEIGHTपूर्ण;

	fmt = rkisp1_find_fmt_cfg(cap, pixm->pixelक्रमmat);
	अगर (!fmt) अणु
		fmt = config->fmts;
		pixm->pixelक्रमmat = fmt->fourcc;
	पूर्ण

	pixm->width = clamp_t(u32, pixm->width,
			      RKISP1_RSZ_SRC_MIN_WIDTH, max_widths[cap->id]);
	pixm->height = clamp_t(u32, pixm->height,
			       RKISP1_RSZ_SRC_MIN_HEIGHT, max_heights[cap->id]);

	pixm->field = V4L2_FIELD_NONE;
	pixm->colorspace = V4L2_COLORSPACE_DEFAULT;
	pixm->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	pixm->quantization = V4L2_QUANTIZATION_DEFAULT;

	info = rkisp1_fill_pixfmt(pixm, cap->id);

	अगर (fmt_cfg)
		*fmt_cfg = fmt;
	अगर (fmt_info)
		*fmt_info = info;
पूर्ण

अटल व्योम rkisp1_set_fmt(काष्ठा rkisp1_capture *cap,
			   काष्ठा v4l2_pix_क्रमmat_mplane *pixm)
अणु
	rkisp1_try_fmt(cap, pixm, &cap->pix.cfg, &cap->pix.info);
	cap->pix.fmt = *pixm;

	/* SP supports custom stride in number of pixels of the Y plane */
	अगर (cap->id == RKISP1_SELFPATH)
		cap->sp_y_stride = pixm->plane_fmt[0].bytesperline /
				   cap->pix.info->bpp[0];
पूर्ण

अटल पूर्णांक rkisp1_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkisp1_capture *cap = video_drvdata(file);

	rkisp1_try_fmt(cap, &f->fmt.pix_mp, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_क्रमागत_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
					  काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा rkisp1_capture *cap = video_drvdata(file);
	स्थिर काष्ठा rkisp1_capture_fmt_cfg *fmt = शून्य;
	अचिन्हित पूर्णांक i, n = 0;

	अगर (!f->mbus_code) अणु
		अगर (f->index >= cap->config->fmt_size)
			वापस -EINVAL;

		fmt = &cap->config->fmts[f->index];
		f->pixelक्रमmat = fmt->fourcc;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < cap->config->fmt_size; i++) अणु
		अगर (cap->config->fmts[i].mbus != f->mbus_code)
			जारी;

		अगर (n++ == f->index) अणु
			f->pixelक्रमmat = cap->config->fmts[i].fourcc;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rkisp1_s_fmt_vid_cap_mplane(काष्ठा file *file,
				       व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkisp1_capture *cap = video_drvdata(file);
	काष्ठा rkisp1_vdev_node *node =
				rkisp1_vdev_to_node(&cap->vnode.vdev);

	अगर (vb2_is_busy(&node->buf_queue))
		वापस -EBUSY;

	rkisp1_set_fmt(cap, &f->fmt.pix_mp);

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_g_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rkisp1_capture *cap = video_drvdata(file);

	f->fmt.pix_mp = cap->pix.fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक
rkisp1_querycap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा rkisp1_capture *cap_dev = video_drvdata(file);
	काष्ठा rkisp1_device *rkisp1 = cap_dev->rkisp1;

	strscpy(cap->driver, rkisp1->dev->driver->name, माप(cap->driver));
	strscpy(cap->card, rkisp1->dev->driver->name, माप(cap->card));
	strscpy(cap->bus_info, RKISP1_BUS_INFO, माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rkisp1_v4l2_ioctl_ops = अणु
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_try_fmt_vid_cap_mplane = rkisp1_try_fmt_vid_cap_mplane,
	.vidioc_s_fmt_vid_cap_mplane = rkisp1_s_fmt_vid_cap_mplane,
	.vidioc_g_fmt_vid_cap_mplane = rkisp1_g_fmt_vid_cap_mplane,
	.vidioc_क्रमागत_fmt_vid_cap = rkisp1_क्रमागत_fmt_vid_cap_mplane,
	.vidioc_querycap = rkisp1_querycap,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक rkisp1_capture_link_validate(काष्ठा media_link *link)
अणु
	काष्ठा video_device *vdev =
		media_entity_to_video_device(link->sink->entity);
	काष्ठा v4l2_subdev *sd =
		media_entity_to_v4l2_subdev(link->source->entity);
	काष्ठा rkisp1_capture *cap = video_get_drvdata(vdev);
	स्थिर काष्ठा rkisp1_capture_fmt_cfg *fmt =
		rkisp1_find_fmt_cfg(cap, cap->pix.fmt.pixelक्रमmat);
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;
	पूर्णांक ret;

	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	sd_fmt.pad = link->source->index;
	ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &sd_fmt);
	अगर (ret)
		वापस ret;

	अगर (sd_fmt.क्रमmat.height != cap->pix.fmt.height ||
	    sd_fmt.क्रमmat.width != cap->pix.fmt.width ||
	    sd_fmt.क्रमmat.code != fmt->mbus)
		वापस -EPIPE;

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------------
 * core functions
 */

अटल स्थिर काष्ठा media_entity_operations rkisp1_media_ops = अणु
	.link_validate = rkisp1_capture_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations rkisp1_fops = अणु
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

अटल व्योम rkisp1_unरेजिस्टर_capture(काष्ठा rkisp1_capture *cap)
अणु
	media_entity_cleanup(&cap->vnode.vdev.entity);
	vb2_video_unरेजिस्टर_device(&cap->vnode.vdev);
पूर्ण

व्योम rkisp1_capture_devs_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_capture *mp = &rkisp1->capture_devs[RKISP1_MAINPATH];
	काष्ठा rkisp1_capture *sp = &rkisp1->capture_devs[RKISP1_SELFPATH];

	rkisp1_unरेजिस्टर_capture(mp);
	rkisp1_unरेजिस्टर_capture(sp);
पूर्ण

अटल पूर्णांक rkisp1_रेजिस्टर_capture(काष्ठा rkisp1_capture *cap)
अणु
	स्थिर अक्षर * स्थिर dev_names[] = अणुRKISP1_MP_DEV_NAME,
					  RKISP1_SP_DEV_NAMEपूर्ण;
	काष्ठा v4l2_device *v4l2_dev = &cap->rkisp1->v4l2_dev;
	काष्ठा video_device *vdev = &cap->vnode.vdev;
	काष्ठा rkisp1_vdev_node *node;
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	strscpy(vdev->name, dev_names[cap->id], माप(vdev->name));
	node = rkisp1_vdev_to_node(vdev);
	mutex_init(&node->vlock);

	vdev->ioctl_ops = &rkisp1_v4l2_ioctl_ops;
	vdev->release = video_device_release_empty;
	vdev->fops = &rkisp1_fops;
	vdev->minor = -1;
	vdev->v4l2_dev = v4l2_dev;
	vdev->lock = &node->vlock;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			    V4L2_CAP_STREAMING | V4L2_CAP_IO_MC;
	vdev->entity.ops = &rkisp1_media_ops;
	video_set_drvdata(vdev, cap);
	vdev->vfl_dir = VFL_सूची_RX;
	node->pad.flags = MEDIA_PAD_FL_SINK;

	q = &node->buf_queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->drv_priv = cap;
	q->ops = &rkisp1_vb2_ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा rkisp1_buffer);
	q->min_buffers_needed = RKISP1_MIN_BUFFERS_NEEDED;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &node->vlock;
	q->dev = cap->rkisp1->dev;
	ret = vb2_queue_init(q);
	अगर (ret) अणु
		dev_err(cap->rkisp1->dev,
			"vb2 queue init failed (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	vdev->queue = q;

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(cap->rkisp1->dev,
			"failed to register %s, ret=%d\n", vdev->name, ret);
		वापस ret;
	पूर्ण
	v4l2_info(v4l2_dev, "registered %s as /dev/video%d\n", vdev->name,
		  vdev->num);

	ret = media_entity_pads_init(&vdev->entity, 1, &node->pad);
	अगर (ret) अणु
		video_unरेजिस्टर_device(vdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
rkisp1_capture_init(काष्ठा rkisp1_device *rkisp1, क्रमागत rkisp1_stream_id id)
अणु
	काष्ठा rkisp1_capture *cap = &rkisp1->capture_devs[id];
	काष्ठा v4l2_pix_क्रमmat_mplane pixm;

	स_रखो(cap, 0, माप(*cap));
	cap->id = id;
	cap->rkisp1 = rkisp1;

	INIT_LIST_HEAD(&cap->buf.queue);
	init_रुकोqueue_head(&cap->करोne);
	spin_lock_init(&cap->buf.lock);
	अगर (cap->id == RKISP1_SELFPATH) अणु
		cap->ops = &rkisp1_capture_ops_sp;
		cap->config = &rkisp1_capture_config_sp;
	पूर्ण अन्यथा अणु
		cap->ops = &rkisp1_capture_ops_mp;
		cap->config = &rkisp1_capture_config_mp;
	पूर्ण

	cap->is_streaming = false;

	स_रखो(&pixm, 0, माप(pixm));
	pixm.pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	pixm.width = RKISP1_DEFAULT_WIDTH;
	pixm.height = RKISP1_DEFAULT_HEIGHT;
	rkisp1_set_fmt(cap, &pixm);
पूर्ण

पूर्णांक rkisp1_capture_devs_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_capture *cap;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1->capture_devs); i++) अणु
		rkisp1_capture_init(rkisp1, i);
		cap = &rkisp1->capture_devs[i];
		cap->rkisp1 = rkisp1;
		ret = rkisp1_रेजिस्टर_capture(cap);
		अगर (ret)
			जाओ err_unreg_capture_devs;
	पूर्ण

	वापस 0;

err_unreg_capture_devs:
	क्रम (j = 0; j < i; j++) अणु
		cap = &rkisp1->capture_devs[j];
		rkisp1_unरेजिस्टर_capture(cap);
	पूर्ण

	वापस ret;
पूर्ण
