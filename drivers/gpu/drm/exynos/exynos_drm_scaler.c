<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Samsung Electronics Co.Ltd
 * Author:
 *	Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_ipp.h"
#समावेश "regs-scaler.h"

#घोषणा scaler_पढ़ो(offset)		पढ़ोl(scaler->regs + (offset))
#घोषणा scaler_ग_लिखो(cfg, offset)	ग_लिखोl(cfg, scaler->regs + (offset))
#घोषणा SCALER_MAX_CLK			4
#घोषणा SCALER_AUTOSUSPEND_DELAY	2000
#घोषणा SCALER_RESET_WAIT_RETRIES	100

काष्ठा scaler_data अणु
	स्थिर अक्षर	*clk_name[SCALER_MAX_CLK];
	अचिन्हित पूर्णांक	num_clk;
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	अचिन्हित पूर्णांक	num_क्रमmats;
पूर्ण;

काष्ठा scaler_context अणु
	काष्ठा exynos_drm_ipp		ipp;
	काष्ठा drm_device		*drm_dev;
	व्योम				*dma_priv;
	काष्ठा device			*dev;
	व्योम __iomem			*regs;
	काष्ठा clk			*घड़ी[SCALER_MAX_CLK];
	काष्ठा exynos_drm_ipp_task	*task;
	स्थिर काष्ठा scaler_data	*scaler_data;
पूर्ण;

काष्ठा scaler_क्रमmat अणु
	u32	drm_fmt;
	u32	पूर्णांकernal_fmt;
	u32	chroma_tile_w;
	u32	chroma_tile_h;
पूर्ण;

अटल स्थिर काष्ठा scaler_क्रमmat scaler_क्रमmats[] = अणु
	अणु DRM_FORMAT_NV12, SCALER_YUV420_2P_UV, 8, 8 पूर्ण,
	अणु DRM_FORMAT_NV21, SCALER_YUV420_2P_VU, 8, 8 पूर्ण,
	अणु DRM_FORMAT_YUV420, SCALER_YUV420_3P, 8, 8 पूर्ण,
	अणु DRM_FORMAT_YUYV, SCALER_YUV422_1P_YUYV, 16, 16 पूर्ण,
	अणु DRM_FORMAT_UYVY, SCALER_YUV422_1P_UYVY, 16, 16 पूर्ण,
	अणु DRM_FORMAT_YVYU, SCALER_YUV422_1P_YVYU, 16, 16 पूर्ण,
	अणु DRM_FORMAT_NV16, SCALER_YUV422_2P_UV, 8, 16 पूर्ण,
	अणु DRM_FORMAT_NV61, SCALER_YUV422_2P_VU, 8, 16 पूर्ण,
	अणु DRM_FORMAT_YUV422, SCALER_YUV422_3P, 8, 16 पूर्ण,
	अणु DRM_FORMAT_NV24, SCALER_YUV444_2P_UV, 16, 16 पूर्ण,
	अणु DRM_FORMAT_NV42, SCALER_YUV444_2P_VU, 16, 16 पूर्ण,
	अणु DRM_FORMAT_YUV444, SCALER_YUV444_3P, 16, 16 पूर्ण,
	अणु DRM_FORMAT_RGB565, SCALER_RGB_565, 0, 0 पूर्ण,
	अणु DRM_FORMAT_XRGB1555, SCALER_ARGB1555, 0, 0 पूर्ण,
	अणु DRM_FORMAT_ARGB1555, SCALER_ARGB1555, 0, 0 पूर्ण,
	अणु DRM_FORMAT_XRGB4444, SCALER_ARGB4444, 0, 0 पूर्ण,
	अणु DRM_FORMAT_ARGB4444, SCALER_ARGB4444, 0, 0 पूर्ण,
	अणु DRM_FORMAT_XRGB8888, SCALER_ARGB8888, 0, 0 पूर्ण,
	अणु DRM_FORMAT_ARGB8888, SCALER_ARGB8888, 0, 0 पूर्ण,
	अणु DRM_FORMAT_RGBX8888, SCALER_RGBA8888, 0, 0 पूर्ण,
	अणु DRM_FORMAT_RGBA8888, SCALER_RGBA8888, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scaler_क्रमmat *scaler_get_क्रमmat(u32 drm_fmt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(scaler_क्रमmats); i++)
		अगर (scaler_क्रमmats[i].drm_fmt == drm_fmt)
			वापस &scaler_क्रमmats[i];

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक scaler_reset(काष्ठा scaler_context *scaler)
अणु
	पूर्णांक retry = SCALER_RESET_WAIT_RETRIES;

	scaler_ग_लिखो(SCALER_CFG_SOFT_RESET, SCALER_CFG);
	करो अणु
		cpu_relax();
	पूर्ण जबतक (--retry > 1 &&
		 scaler_पढ़ो(SCALER_CFG) & SCALER_CFG_SOFT_RESET);
	करो अणु
		cpu_relax();
		scaler_ग_लिखो(1, SCALER_INT_EN);
	पूर्ण जबतक (--retry > 0 && scaler_पढ़ो(SCALER_INT_EN) != 1);

	वापस retry ? 0 : -EIO;
पूर्ण

अटल अंतरभूत व्योम scaler_enable_पूर्णांक(काष्ठा scaler_context *scaler)
अणु
	u32 val;

	val = SCALER_INT_EN_TIMEOUT |
		SCALER_INT_EN_ILLEGAL_BLEND |
		SCALER_INT_EN_ILLEGAL_RATIO |
		SCALER_INT_EN_ILLEGAL_DST_HEIGHT |
		SCALER_INT_EN_ILLEGAL_DST_WIDTH |
		SCALER_INT_EN_ILLEGAL_DST_V_POS |
		SCALER_INT_EN_ILLEGAL_DST_H_POS |
		SCALER_INT_EN_ILLEGAL_DST_C_SPAN |
		SCALER_INT_EN_ILLEGAL_DST_Y_SPAN |
		SCALER_INT_EN_ILLEGAL_DST_CR_BASE |
		SCALER_INT_EN_ILLEGAL_DST_CB_BASE |
		SCALER_INT_EN_ILLEGAL_DST_Y_BASE |
		SCALER_INT_EN_ILLEGAL_DST_COLOR |
		SCALER_INT_EN_ILLEGAL_SRC_HEIGHT |
		SCALER_INT_EN_ILLEGAL_SRC_WIDTH |
		SCALER_INT_EN_ILLEGAL_SRC_CV_POS |
		SCALER_INT_EN_ILLEGAL_SRC_CH_POS |
		SCALER_INT_EN_ILLEGAL_SRC_YV_POS |
		SCALER_INT_EN_ILLEGAL_SRC_YH_POS |
		SCALER_INT_EN_ILLEGAL_DST_SPAN |
		SCALER_INT_EN_ILLEGAL_SRC_Y_SPAN |
		SCALER_INT_EN_ILLEGAL_SRC_CR_BASE |
		SCALER_INT_EN_ILLEGAL_SRC_CB_BASE |
		SCALER_INT_EN_ILLEGAL_SRC_Y_BASE |
		SCALER_INT_EN_ILLEGAL_SRC_COLOR |
		SCALER_INT_EN_FRAME_END;
	scaler_ग_लिखो(val, SCALER_INT_EN);
पूर्ण

अटल अंतरभूत व्योम scaler_set_src_fmt(काष्ठा scaler_context *scaler,
	u32 src_fmt, u32 tile)
अणु
	u32 val;

	val = SCALER_SRC_CFG_SET_COLOR_FORMAT(src_fmt) | (tile << 10);
	scaler_ग_लिखो(val, SCALER_SRC_CFG);
पूर्ण

अटल अंतरभूत व्योम scaler_set_src_base(काष्ठा scaler_context *scaler,
	काष्ठा exynos_drm_ipp_buffer *src_buf)
अणु
	अटल अचिन्हित पूर्णांक bases[] = अणु
		SCALER_SRC_Y_BASE,
		SCALER_SRC_CB_BASE,
		SCALER_SRC_CR_BASE,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < src_buf->क्रमmat->num_planes; ++i)
		scaler_ग_लिखो(src_buf->dma_addr[i], bases[i]);
पूर्ण

अटल अंतरभूत व्योम scaler_set_src_span(काष्ठा scaler_context *scaler,
	काष्ठा exynos_drm_ipp_buffer *src_buf)
अणु
	u32 val;

	val = SCALER_SRC_SPAN_SET_Y_SPAN(src_buf->buf.pitch[0] /
		src_buf->क्रमmat->cpp[0]);

	अगर (src_buf->क्रमmat->num_planes > 1)
		val |= SCALER_SRC_SPAN_SET_C_SPAN(src_buf->buf.pitch[1]);

	scaler_ग_लिखो(val, SCALER_SRC_SPAN);
पूर्ण

अटल अंतरभूत व्योम scaler_set_src_luma_chroma_pos(काष्ठा scaler_context *scaler,
			काष्ठा drm_exynos_ipp_task_rect *src_pos,
			स्थिर काष्ठा scaler_क्रमmat *fmt)
अणु
	u32 val;

	val = SCALER_SRC_Y_POS_SET_YH_POS(src_pos->x << 2);
	val |=  SCALER_SRC_Y_POS_SET_YV_POS(src_pos->y << 2);
	scaler_ग_लिखो(val, SCALER_SRC_Y_POS);
	val = SCALER_SRC_C_POS_SET_CH_POS(
		(src_pos->x * fmt->chroma_tile_w / 16) << 2);
	val |=  SCALER_SRC_C_POS_SET_CV_POS(
		(src_pos->y * fmt->chroma_tile_h / 16) << 2);
	scaler_ग_लिखो(val, SCALER_SRC_C_POS);
पूर्ण

अटल अंतरभूत व्योम scaler_set_src_wh(काष्ठा scaler_context *scaler,
	काष्ठा drm_exynos_ipp_task_rect *src_pos)
अणु
	u32 val;

	val = SCALER_SRC_WH_SET_WIDTH(src_pos->w);
	val |= SCALER_SRC_WH_SET_HEIGHT(src_pos->h);
	scaler_ग_लिखो(val, SCALER_SRC_WH);
पूर्ण

अटल अंतरभूत व्योम scaler_set_dst_fmt(काष्ठा scaler_context *scaler,
	u32 dst_fmt)
अणु
	u32 val;

	val = SCALER_DST_CFG_SET_COLOR_FORMAT(dst_fmt);
	scaler_ग_लिखो(val, SCALER_DST_CFG);
पूर्ण

अटल अंतरभूत व्योम scaler_set_dst_base(काष्ठा scaler_context *scaler,
	काष्ठा exynos_drm_ipp_buffer *dst_buf)
अणु
	अटल अचिन्हित पूर्णांक bases[] = अणु
		SCALER_DST_Y_BASE,
		SCALER_DST_CB_BASE,
		SCALER_DST_CR_BASE,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < dst_buf->क्रमmat->num_planes; ++i)
		scaler_ग_लिखो(dst_buf->dma_addr[i], bases[i]);
पूर्ण

अटल अंतरभूत व्योम scaler_set_dst_span(काष्ठा scaler_context *scaler,
	काष्ठा exynos_drm_ipp_buffer *dst_buf)
अणु
	u32 val;

	val = SCALER_DST_SPAN_SET_Y_SPAN(dst_buf->buf.pitch[0] /
		dst_buf->क्रमmat->cpp[0]);

	अगर (dst_buf->क्रमmat->num_planes > 1)
		val |= SCALER_DST_SPAN_SET_C_SPAN(dst_buf->buf.pitch[1]);

	scaler_ग_लिखो(val, SCALER_DST_SPAN);
पूर्ण

अटल अंतरभूत व्योम scaler_set_dst_luma_pos(काष्ठा scaler_context *scaler,
	काष्ठा drm_exynos_ipp_task_rect *dst_pos)
अणु
	u32 val;

	val = SCALER_DST_WH_SET_WIDTH(dst_pos->w);
	val |= SCALER_DST_WH_SET_HEIGHT(dst_pos->h);
	scaler_ग_लिखो(val, SCALER_DST_WH);
पूर्ण

अटल अंतरभूत व्योम scaler_set_dst_wh(काष्ठा scaler_context *scaler,
	काष्ठा drm_exynos_ipp_task_rect *dst_pos)
अणु
	u32 val;

	val = SCALER_DST_POS_SET_H_POS(dst_pos->x);
	val |= SCALER_DST_POS_SET_V_POS(dst_pos->y);
	scaler_ग_लिखो(val, SCALER_DST_POS);
पूर्ण

अटल अंतरभूत व्योम scaler_set_hv_ratio(काष्ठा scaler_context *scaler,
	अचिन्हित पूर्णांक rotation,
	काष्ठा drm_exynos_ipp_task_rect *src_pos,
	काष्ठा drm_exynos_ipp_task_rect *dst_pos)
अणु
	u32 val, h_ratio, v_ratio;

	अगर (drm_rotation_90_or_270(rotation)) अणु
		h_ratio = (src_pos->h << 16) / dst_pos->w;
		v_ratio = (src_pos->w << 16) / dst_pos->h;
	पूर्ण अन्यथा अणु
		h_ratio = (src_pos->w << 16) / dst_pos->w;
		v_ratio = (src_pos->h << 16) / dst_pos->h;
	पूर्ण

	val = SCALER_H_RATIO_SET(h_ratio);
	scaler_ग_लिखो(val, SCALER_H_RATIO);

	val = SCALER_V_RATIO_SET(v_ratio);
	scaler_ग_लिखो(val, SCALER_V_RATIO);
पूर्ण

अटल अंतरभूत व्योम scaler_set_rotation(काष्ठा scaler_context *scaler,
	अचिन्हित पूर्णांक rotation)
अणु
	u32 val = 0;

	अगर (rotation & DRM_MODE_ROTATE_90)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_90);
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_180)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_180);
	अन्यथा अगर (rotation & DRM_MODE_ROTATE_270)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_270);
	अगर (rotation & DRM_MODE_REFLECT_X)
		val |= SCALER_ROT_CFG_FLIP_X_EN;
	अगर (rotation & DRM_MODE_REFLECT_Y)
		val |= SCALER_ROT_CFG_FLIP_Y_EN;
	scaler_ग_लिखो(val, SCALER_ROT_CFG);
पूर्ण

अटल अंतरभूत व्योम scaler_set_csc(काष्ठा scaler_context *scaler,
	स्थिर काष्ठा drm_क्रमmat_info *fmt)
अणु
	अटल स्थिर u32 csc_mtx[2][3][3] = अणु
		अणु /* YCbCr to RGB */
			अणु0x254, 0x000, 0x331पूर्ण,
			अणु0x254, 0xf38, 0xe60पूर्ण,
			अणु0x254, 0x409, 0x000पूर्ण,
		पूर्ण,
		अणु /* RGB to YCbCr */
			अणु0x084, 0x102, 0x032पूर्ण,
			अणु0xfb4, 0xf6b, 0x0e1पूर्ण,
			अणु0x0e1, 0xf44, 0xfdcपूर्ण,
		पूर्ण,
	पूर्ण;
	पूर्णांक i, j, dir;

	चयन (fmt->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_RGBA8888:
		dir = 1;
		अवरोध;
	शेष:
		dir = 0;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		क्रम (j = 0; j < 3; j++)
			scaler_ग_लिखो(csc_mtx[dir][i][j], SCALER_CSC_COEF(j, i));
पूर्ण

अटल अंतरभूत व्योम scaler_set_समयr(काष्ठा scaler_context *scaler,
	अचिन्हित पूर्णांक समयr, अचिन्हित पूर्णांक भागider)
अणु
	u32 val;

	val = SCALER_TIMEOUT_CTRL_TIMER_ENABLE;
	val |= SCALER_TIMEOUT_CTRL_SET_TIMER_VALUE(समयr);
	val |= SCALER_TIMEOUT_CTRL_SET_TIMER_DIV(भागider);
	scaler_ग_लिखो(val, SCALER_TIMEOUT_CTRL);
पूर्ण

अटल अंतरभूत व्योम scaler_start_hw(काष्ठा scaler_context *scaler)
अणु
	scaler_ग_लिखो(SCALER_CFG_START_CMD, SCALER_CFG);
पूर्ण

अटल पूर्णांक scaler_commit(काष्ठा exynos_drm_ipp *ipp,
			  काष्ठा exynos_drm_ipp_task *task)
अणु
	काष्ठा scaler_context *scaler =
			container_of(ipp, काष्ठा scaler_context, ipp);

	काष्ठा drm_exynos_ipp_task_rect *src_pos = &task->src.rect;
	काष्ठा drm_exynos_ipp_task_rect *dst_pos = &task->dst.rect;
	स्थिर काष्ठा scaler_क्रमmat *src_fmt, *dst_fmt;

	src_fmt = scaler_get_क्रमmat(task->src.buf.fourcc);
	dst_fmt = scaler_get_क्रमmat(task->dst.buf.fourcc);

	pm_runसमय_get_sync(scaler->dev);
	अगर (scaler_reset(scaler)) अणु
		pm_runसमय_put(scaler->dev);
		वापस -EIO;
	पूर्ण

	scaler->task = task;

	scaler_set_src_fmt(
		scaler, src_fmt->पूर्णांकernal_fmt, task->src.buf.modअगरier != 0);
	scaler_set_src_base(scaler, &task->src);
	scaler_set_src_span(scaler, &task->src);
	scaler_set_src_luma_chroma_pos(scaler, src_pos, src_fmt);
	scaler_set_src_wh(scaler, src_pos);

	scaler_set_dst_fmt(scaler, dst_fmt->पूर्णांकernal_fmt);
	scaler_set_dst_base(scaler, &task->dst);
	scaler_set_dst_span(scaler, &task->dst);
	scaler_set_dst_luma_pos(scaler, dst_pos);
	scaler_set_dst_wh(scaler, dst_pos);

	scaler_set_hv_ratio(scaler, task->transक्रमm.rotation, src_pos, dst_pos);
	scaler_set_rotation(scaler, task->transक्रमm.rotation);

	scaler_set_csc(scaler, task->src.क्रमmat);

	scaler_set_समयr(scaler, 0xffff, 0xf);

	scaler_enable_पूर्णांक(scaler);
	scaler_start_hw(scaler);

	वापस 0;
पूर्ण

अटल काष्ठा exynos_drm_ipp_funcs ipp_funcs = अणु
	.commit = scaler_commit,
पूर्ण;

अटल अंतरभूत व्योम scaler_disable_पूर्णांक(काष्ठा scaler_context *scaler)
अणु
	scaler_ग_लिखो(0, SCALER_INT_EN);
पूर्ण

अटल अंतरभूत u32 scaler_get_पूर्णांक_status(काष्ठा scaler_context *scaler)
अणु
	u32 val = scaler_पढ़ो(SCALER_INT_STATUS);

	scaler_ग_लिखो(val, SCALER_INT_STATUS);

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक scaler_task_करोne(u32 val)
अणु
	वापस val & SCALER_INT_STATUS_FRAME_END ? 0 : -EINVAL;
पूर्ण

अटल irqवापस_t scaler_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा scaler_context *scaler = arg;

	u32 val = scaler_get_पूर्णांक_status(scaler);

	scaler_disable_पूर्णांक(scaler);

	अगर (scaler->task) अणु
		काष्ठा exynos_drm_ipp_task *task = scaler->task;

		scaler->task = शून्य;
		pm_runसमय_mark_last_busy(scaler->dev);
		pm_runसमय_put_स्वतःsuspend(scaler->dev);
		exynos_drm_ipp_task_करोne(task, scaler_task_करोne(val));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक scaler_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा scaler_context *scaler = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_ipp *ipp = &scaler->ipp;

	scaler->drm_dev = drm_dev;
	ipp->drm_dev = drm_dev;
	exynos_drm_रेजिस्टर_dma(drm_dev, dev, &scaler->dma_priv);

	exynos_drm_ipp_रेजिस्टर(dev, ipp, &ipp_funcs,
			DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE |
			DRM_EXYNOS_IPP_CAP_SCALE | DRM_EXYNOS_IPP_CAP_CONVERT,
			scaler->scaler_data->क्रमmats,
			scaler->scaler_data->num_क्रमmats, "scaler");

	dev_info(dev, "The exynos scaler has been probed successfully\n");

	वापस 0;
पूर्ण

अटल व्योम scaler_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा scaler_context *scaler = dev_get_drvdata(dev);
	काष्ठा exynos_drm_ipp *ipp = &scaler->ipp;

	exynos_drm_ipp_unरेजिस्टर(dev, ipp);
	exynos_drm_unरेजिस्टर_dma(scaler->drm_dev, scaler->dev,
				  &scaler->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops scaler_component_ops = अणु
	.bind	= scaler_bind,
	.unbind = scaler_unbind,
पूर्ण;

अटल पूर्णांक scaler_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*regs_res;
	काष्ठा scaler_context *scaler;
	पूर्णांक irq;
	पूर्णांक ret, i;

	scaler = devm_kzalloc(dev, माप(*scaler), GFP_KERNEL);
	अगर (!scaler)
		वापस -ENOMEM;

	scaler->scaler_data =
		(काष्ठा scaler_data *)of_device_get_match_data(dev);

	scaler->dev = dev;
	regs_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	scaler->regs = devm_ioremap_resource(dev, regs_res);
	अगर (IS_ERR(scaler->regs))
		वापस PTR_ERR(scaler->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,	scaler_irq_handler,
					IRQF_ONESHOT, "drm_scaler", scaler);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < scaler->scaler_data->num_clk; ++i) अणु
		scaler->घड़ी[i] = devm_clk_get(dev,
					      scaler->scaler_data->clk_name[i]);
		अगर (IS_ERR(scaler->घड़ी[i])) अणु
			dev_err(dev, "failed to get clock\n");
			वापस PTR_ERR(scaler->घड़ी[i]);
		पूर्ण
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, SCALER_AUTOSUSPEND_DELAY);
	pm_runसमय_enable(dev);
	platक्रमm_set_drvdata(pdev, scaler);

	ret = component_add(dev, &scaler_component_ops);
	अगर (ret)
		जाओ err_ippdrv_रेजिस्टर;

	वापस 0;

err_ippdrv_रेजिस्टर:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक scaler_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	component_del(dev, &scaler_component_ops);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक clk_disable_unprepare_wrapper(काष्ठा clk *clk)
अणु
	clk_disable_unprepare(clk);

	वापस 0;
पूर्ण

अटल पूर्णांक scaler_clk_ctrl(काष्ठा scaler_context *scaler, bool enable)
अणु
	पूर्णांक (*clk_fun)(काष्ठा clk *clk), i;

	clk_fun = enable ? clk_prepare_enable : clk_disable_unprepare_wrapper;

	क्रम (i = 0; i < scaler->scaler_data->num_clk; ++i)
		clk_fun(scaler->घड़ी[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक scaler_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा scaler_context *scaler = dev_get_drvdata(dev);

	वापस  scaler_clk_ctrl(scaler, false);
पूर्ण

अटल पूर्णांक scaler_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा scaler_context *scaler = dev_get_drvdata(dev);

	वापस  scaler_clk_ctrl(scaler, true);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops scaler_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(scaler_runसमय_suspend, scaler_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit scaler_5420_two_pixel_hv_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, SZ_8K पूर्ण, .v = अणु 16, SZ_8K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 2, .v.align = 2) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण,
			  .v = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit scaler_5420_two_pixel_h_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, SZ_8K पूर्ण, .v = अणु 16, SZ_8K पूर्ण) पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 2, .v.align = 1) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण,
			  .v = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit scaler_5420_one_pixel_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, SZ_8K पूर्ण, .v = अणु 16, SZ_8K पूर्ण) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण,
			  .v = अणु 65536 * 1 / 4, 65536 * 16 पूर्ण) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_exynos_ipp_limit scaler_5420_tile_limits[] = अणु
	अणु IPP_SIZE_LIMIT(BUFFER, .h = अणु 16, SZ_8K पूर्ण, .v = अणु 16, SZ_8K पूर्ण)पूर्ण,
	अणु IPP_SIZE_LIMIT(AREA, .h.align = 16, .v.align = 16) पूर्ण,
	अणु IPP_SCALE_LIMIT(.h = अणु1, 1पूर्ण, .v = अणु1, 1पूर्ण)पूर्ण,
	अणु पूर्ण
पूर्ण;

#घोषणा IPP_SRCDST_TILE_FORMAT(f, l)	\
	IPP_SRCDST_MFORMAT(f, DRM_FORMAT_MOD_SAMSUNG_16_16_TILE, (l))

अटल स्थिर काष्ठा exynos_drm_ipp_क्रमmats exynos5420_क्रमmats[] = अणु
	/* SCALER_YUV420_2P_UV */
	अणु IPP_SRCDST_FORMAT(NV21, scaler_5420_two_pixel_hv_limits) पूर्ण,

	/* SCALER_YUV420_2P_VU */
	अणु IPP_SRCDST_FORMAT(NV12, scaler_5420_two_pixel_hv_limits) पूर्ण,

	/* SCALER_YUV420_3P */
	अणु IPP_SRCDST_FORMAT(YUV420, scaler_5420_two_pixel_hv_limits) पूर्ण,

	/* SCALER_YUV422_1P_YUYV */
	अणु IPP_SRCDST_FORMAT(YUYV, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV422_1P_UYVY */
	अणु IPP_SRCDST_FORMAT(UYVY, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV422_1P_YVYU */
	अणु IPP_SRCDST_FORMAT(YVYU, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV422_2P_UV */
	अणु IPP_SRCDST_FORMAT(NV61, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV422_2P_VU */
	अणु IPP_SRCDST_FORMAT(NV16, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV422_3P */
	अणु IPP_SRCDST_FORMAT(YUV422, scaler_5420_two_pixel_h_limits) पूर्ण,

	/* SCALER_YUV444_2P_UV */
	अणु IPP_SRCDST_FORMAT(NV42, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_YUV444_2P_VU */
	अणु IPP_SRCDST_FORMAT(NV24, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_YUV444_3P */
	अणु IPP_SRCDST_FORMAT(YUV444, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_RGB_565 */
	अणु IPP_SRCDST_FORMAT(RGB565, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB1555 */
	अणु IPP_SRCDST_FORMAT(XRGB1555, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB1555 */
	अणु IPP_SRCDST_FORMAT(ARGB1555, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB4444 */
	अणु IPP_SRCDST_FORMAT(XRGB4444, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB4444 */
	अणु IPP_SRCDST_FORMAT(ARGB4444, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB8888 */
	अणु IPP_SRCDST_FORMAT(XRGB8888, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_ARGB8888 */
	अणु IPP_SRCDST_FORMAT(ARGB8888, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_RGBA8888 */
	अणु IPP_SRCDST_FORMAT(RGBX8888, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_RGBA8888 */
	अणु IPP_SRCDST_FORMAT(RGBA8888, scaler_5420_one_pixel_limits) पूर्ण,

	/* SCALER_YUV420_2P_UV TILE */
	अणु IPP_SRCDST_TILE_FORMAT(NV21, scaler_5420_tile_limits) पूर्ण,

	/* SCALER_YUV420_2P_VU TILE */
	अणु IPP_SRCDST_TILE_FORMAT(NV12, scaler_5420_tile_limits) पूर्ण,

	/* SCALER_YUV420_3P TILE */
	अणु IPP_SRCDST_TILE_FORMAT(YUV420, scaler_5420_tile_limits) पूर्ण,

	/* SCALER_YUV422_1P_YUYV TILE */
	अणु IPP_SRCDST_TILE_FORMAT(YUYV, scaler_5420_tile_limits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scaler_data exynos5420_data = अणु
	.clk_name	= अणु"mscl"पूर्ण,
	.num_clk	= 1,
	.क्रमmats	= exynos5420_क्रमmats,
	.num_क्रमmats	= ARRAY_SIZE(exynos5420_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा scaler_data exynos5433_data = अणु
	.clk_name	= अणु"pclk", "aclk", "aclk_xiu"पूर्ण,
	.num_clk	= 3,
	.क्रमmats	= exynos5420_क्रमmats, /* पूर्णांकentional */
	.num_क्रमmats	= ARRAY_SIZE(exynos5420_क्रमmats),
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_scaler_match[] = अणु
	अणु
		.compatible = "samsung,exynos5420-scaler",
		.data = &exynos5420_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-scaler",
		.data = &exynos5433_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_scaler_match);

काष्ठा platक्रमm_driver scaler_driver = अणु
	.probe		= scaler_probe,
	.हटाओ		= scaler_हटाओ,
	.driver		= अणु
		.name	= "exynos-scaler",
		.owner	= THIS_MODULE,
		.pm	= &scaler_pm_ops,
		.of_match_table = exynos_scaler_match,
	पूर्ण,
पूर्ण;
