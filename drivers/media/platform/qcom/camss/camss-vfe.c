<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-vfe.c
 *
 * Qualcomm MSM Camera Subप्रणाली - VFE (Video Front End) Module
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/spinlock.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "camss-vfe.h"
#समावेश "camss.h"

#घोषणा MSM_VFE_NAME "msm_vfe"

/* VFE reset समयout */
#घोषणा VFE_RESET_TIMEOUT_MS 50

#घोषणा SCALER_RATIO_MAX 16

काष्ठा vfe_क्रमmat अणु
	u32 code;
	u8 bpp;
पूर्ण;

अटल स्थिर काष्ठा vfe_क्रमmat क्रमmats_rdi_8x16[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vfe_क्रमmat क्रमmats_pix_8x16[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vfe_क्रमmat क्रमmats_rdi_8x96[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, 16 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_2X8_PADHI_LE, 16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vfe_क्रमmat क्रमmats_pix_8x96[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vfe_क्रमmat क्रमmats_rdi_845[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, 16 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_2X8_PADHI_LE, 16 पूर्ण,
पूर्ण;

/*
 * vfe_get_bpp - map media bus क्रमmat to bits per pixel
 * @क्रमmats: supported media bus क्रमmats array
 * @nक्रमmats: size of @क्रमmats array
 * @code: media bus क्रमmat code
 *
 * Return number of bits per pixel
 */
अटल u8 vfe_get_bpp(स्थिर काष्ठा vfe_क्रमmat *क्रमmats,
		      अचिन्हित पूर्णांक nक्रमmats, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nक्रमmats; i++)
		अगर (code == क्रमmats[i].code)
			वापस क्रमmats[i].bpp;

	WARN(1, "Unknown format\n");

	वापस क्रमmats[0].bpp;
पूर्ण

अटल u32 vfe_find_code(u32 *code, अचिन्हित पूर्णांक n_code,
			 अचिन्हित पूर्णांक index, u32 req_code)
अणु
	पूर्णांक i;

	अगर (!req_code && (index >= n_code))
		वापस 0;

	क्रम (i = 0; i < n_code; i++)
		अगर (req_code) अणु
			अगर (req_code == code[i])
				वापस req_code;
		पूर्ण अन्यथा अणु
			अगर (i == index)
				वापस code[i];
		पूर्ण

	वापस code[0];
पूर्ण

अटल u32 vfe_src_pad_code(काष्ठा vfe_line *line, u32 sink_code,
			    अचिन्हित पूर्णांक index, u32 src_req_code)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);

	अगर (vfe->camss->version == CAMSS_8x16)
		चयन (sink_code) अणु
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_YUYV8_2X8,
				MEDIA_BUS_FMT_YUYV8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_YVYU8_2X8,
				MEDIA_BUS_FMT_YVYU8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_UYVY8_2X8,
				MEDIA_BUS_FMT_UYVY8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_VYUY8_2X8,
				MEDIA_BUS_FMT_VYUY8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		शेष:
			अगर (index > 0)
				वापस 0;

			वापस sink_code;
		पूर्ण
	अन्यथा अगर (vfe->camss->version == CAMSS_8x96 ||
		 vfe->camss->version == CAMSS_660 ||
		 vfe->camss->version == CAMSS_845)
		चयन (sink_code) अणु
		हाल MEDIA_BUS_FMT_YUYV8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_YUYV8_2X8,
				MEDIA_BUS_FMT_YVYU8_2X8,
				MEDIA_BUS_FMT_UYVY8_2X8,
				MEDIA_BUS_FMT_VYUY8_2X8,
				MEDIA_BUS_FMT_YUYV8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_YVYU8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_YVYU8_2X8,
				MEDIA_BUS_FMT_YUYV8_2X8,
				MEDIA_BUS_FMT_UYVY8_2X8,
				MEDIA_BUS_FMT_VYUY8_2X8,
				MEDIA_BUS_FMT_YVYU8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_UYVY8_2X8,
				MEDIA_BUS_FMT_YUYV8_2X8,
				MEDIA_BUS_FMT_YVYU8_2X8,
				MEDIA_BUS_FMT_VYUY8_2X8,
				MEDIA_BUS_FMT_UYVY8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		हाल MEDIA_BUS_FMT_VYUY8_2X8:
		अणु
			u32 src_code[] = अणु
				MEDIA_BUS_FMT_VYUY8_2X8,
				MEDIA_BUS_FMT_YUYV8_2X8,
				MEDIA_BUS_FMT_YVYU8_2X8,
				MEDIA_BUS_FMT_UYVY8_2X8,
				MEDIA_BUS_FMT_VYUY8_1_5X8,
			पूर्ण;

			वापस vfe_find_code(src_code, ARRAY_SIZE(src_code),
					     index, src_req_code);
		पूर्ण
		शेष:
			अगर (index > 0)
				वापस 0;

			वापस sink_code;
		पूर्ण
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक vfe_reset(काष्ठा vfe_device *vfe)
अणु
	अचिन्हित दीर्घ समय;

	reinit_completion(&vfe->reset_complete);

	vfe->ops->global_reset(vfe);

	समय = रुको_क्रम_completion_समयout(&vfe->reset_complete,
		msecs_to_jअगरfies(VFE_RESET_TIMEOUT_MS));
	अगर (!समय) अणु
		dev_err(vfe->camss->dev, "VFE reset timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vfe_init_outमाला_दो(काष्ठा vfe_device *vfe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vfe->line_num; i++) अणु
		काष्ठा vfe_output *output = &vfe->line[i].output;

		output->state = VFE_OUTPUT_OFF;
		output->buf[0] = शून्य;
		output->buf[1] = शून्य;
		INIT_LIST_HEAD(&output->pending_bufs);
	पूर्ण
पूर्ण

अटल व्योम vfe_reset_output_maps(काष्ठा vfe_device *vfe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vfe->wm_output_map); i++)
		vfe->wm_output_map[i] = VFE_LINE_NONE;
पूर्ण

पूर्णांक vfe_reserve_wm(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id)
अणु
	पूर्णांक ret = -EBUSY;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vfe->wm_output_map); i++) अणु
		अगर (vfe->wm_output_map[i] == VFE_LINE_NONE) अणु
			vfe->wm_output_map[i] = line_id;
			ret = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vfe_release_wm(काष्ठा vfe_device *vfe, u8 wm)
अणु
	अगर (wm >= ARRAY_SIZE(vfe->wm_output_map))
		वापस -EINVAL;

	vfe->wm_output_map[wm] = VFE_LINE_NONE;

	वापस 0;
पूर्ण

काष्ठा camss_buffer *vfe_buf_get_pending(काष्ठा vfe_output *output)
अणु
	काष्ठा camss_buffer *buffer = शून्य;

	अगर (!list_empty(&output->pending_bufs)) अणु
		buffer = list_first_entry(&output->pending_bufs,
					  काष्ठा camss_buffer,
					  queue);
		list_del(&buffer->queue);
	पूर्ण

	वापस buffer;
पूर्ण

व्योम vfe_buf_add_pending(काष्ठा vfe_output *output,
			 काष्ठा camss_buffer *buffer)
अणु
	INIT_LIST_HEAD(&buffer->queue);
	list_add_tail(&buffer->queue, &output->pending_bufs);
पूर्ण

/*
 * vfe_buf_flush_pending - Flush all pending buffers.
 * @output: VFE output
 * @state: vb2 buffer state
 */
अटल व्योम vfe_buf_flush_pending(काष्ठा vfe_output *output,
				  क्रमागत vb2_buffer_state state)
अणु
	काष्ठा camss_buffer *buf;
	काष्ठा camss_buffer *t;

	list_क्रम_each_entry_safe(buf, t, &output->pending_bufs, queue) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->queue);
	पूर्ण
पूर्ण

पूर्णांक vfe_put_output(काष्ठा vfe_line *line)
अणु
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output = &line->output;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&vfe->output_lock, flags);

	क्रम (i = 0; i < output->wm_num; i++)
		vfe_release_wm(vfe, output->wm_idx[i]);

	output->state = VFE_OUTPUT_OFF;

	spin_unlock_irqrestore(&vfe->output_lock, flags);
	वापस 0;
पूर्ण

/**
 * vfe_isr_comp_करोne() - Process composite image करोne पूर्णांकerrupt
 * @vfe: VFE Device
 * @comp: Composite image id
 */
व्योम vfe_isr_comp_करोne(काष्ठा vfe_device *vfe, u8 comp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vfe->wm_output_map); i++)
		अगर (vfe->wm_output_map[i] == VFE_LINE_PIX) अणु
			vfe->isr_ops.wm_करोne(vfe, i);
			अवरोध;
		पूर्ण
पूर्ण

व्योम vfe_isr_reset_ack(काष्ठा vfe_device *vfe)
अणु
	complete(&vfe->reset_complete);
पूर्ण

/*
 * vfe_set_घड़ी_rates - Calculate and set घड़ी rates on VFE module
 * @vfe: VFE device
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_set_घड़ी_rates(काष्ठा vfe_device *vfe)
अणु
	काष्ठा device *dev = vfe->camss->dev;
	u64 pixel_घड़ी[VFE_LINE_NUM_MAX];
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = VFE_LINE_RDI0; i < vfe->line_num; i++) अणु
		ret = camss_get_pixel_घड़ी(&vfe->line[i].subdev.entity,
					    &pixel_घड़ी[i]);
		अगर (ret)
			pixel_घड़ी[i] = 0;
	पूर्ण

	क्रम (i = 0; i < vfe->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &vfe->घड़ी[i];

		अगर (!म_भेद(घड़ी->name, "vfe0") ||
		    !म_भेद(घड़ी->name, "vfe1") ||
		    !म_भेद(घड़ी->name, "vfe_lite")) अणु
			u64 min_rate = 0;
			दीर्घ rate;

			क्रम (j = VFE_LINE_RDI0; j < vfe->line_num; j++) अणु
				u32 पंचांगp;
				u8 bpp;

				अगर (j == VFE_LINE_PIX) अणु
					पंचांगp = pixel_घड़ी[j];
				पूर्ण अन्यथा अणु
					काष्ठा vfe_line *l = &vfe->line[j];

					bpp = vfe_get_bpp(l->क्रमmats,
						l->nक्रमmats,
						l->fmt[MSM_VFE_PAD_SINK].code);
					पंचांगp = pixel_घड़ी[j] * bpp / 64;
				पूर्ण

				अगर (min_rate < पंचांगp)
					min_rate = पंचांगp;
			पूर्ण

			camss_add_घड़ी_margin(&min_rate);

			क्रम (j = 0; j < घड़ी->nfreqs; j++)
				अगर (min_rate < घड़ी->freq[j])
					अवरोध;

			अगर (j == घड़ी->nfreqs) अणु
				dev_err(dev,
					"Pixel clock is too high for VFE");
				वापस -EINVAL;
			पूर्ण

			/* अगर sensor pixel घड़ी is not available */
			/* set highest possible VFE घड़ी rate */
			अगर (min_rate == 0)
				j = घड़ी->nfreqs - 1;

			rate = clk_round_rate(घड़ी->clk, घड़ी->freq[j]);
			अगर (rate < 0) अणु
				dev_err(dev, "clk round rate failed: %ld\n",
					rate);
				वापस -EINVAL;
			पूर्ण

			ret = clk_set_rate(घड़ी->clk, rate);
			अगर (ret < 0) अणु
				dev_err(dev, "clk set rate failed: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_check_घड़ी_rates - Check current घड़ी rates on VFE module
 * @vfe: VFE device
 *
 * Return 0 अगर current घड़ी rates are suitable क्रम a new pipeline
 * or a negative error code otherwise
 */
अटल पूर्णांक vfe_check_घड़ी_rates(काष्ठा vfe_device *vfe)
अणु
	u64 pixel_घड़ी[VFE_LINE_NUM_MAX];
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = VFE_LINE_RDI0; i < vfe->line_num; i++) अणु
		ret = camss_get_pixel_घड़ी(&vfe->line[i].subdev.entity,
					    &pixel_घड़ी[i]);
		अगर (ret)
			pixel_घड़ी[i] = 0;
	पूर्ण

	क्रम (i = 0; i < vfe->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &vfe->घड़ी[i];

		अगर (!म_भेद(घड़ी->name, "vfe0") ||
		    !म_भेद(घड़ी->name, "vfe1")) अणु
			u64 min_rate = 0;
			अचिन्हित दीर्घ rate;

			क्रम (j = VFE_LINE_RDI0; j < vfe->line_num; j++) अणु
				u32 पंचांगp;
				u8 bpp;

				अगर (j == VFE_LINE_PIX) अणु
					पंचांगp = pixel_घड़ी[j];
				पूर्ण अन्यथा अणु
					काष्ठा vfe_line *l = &vfe->line[j];

					bpp = vfe_get_bpp(l->क्रमmats,
						l->nक्रमmats,
						l->fmt[MSM_VFE_PAD_SINK].code);
					पंचांगp = pixel_घड़ी[j] * bpp / 64;
				पूर्ण

				अगर (min_rate < पंचांगp)
					min_rate = पंचांगp;
			पूर्ण

			camss_add_घड़ी_margin(&min_rate);

			rate = clk_get_rate(घड़ी->clk);
			अगर (rate < min_rate)
				वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_get - Power up and reset VFE module
 * @vfe: VFE Device
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_get(काष्ठा vfe_device *vfe)
अणु
	पूर्णांक ret;

	mutex_lock(&vfe->घातer_lock);

	अगर (vfe->घातer_count == 0) अणु
		ret = vfe->ops->pm_करोमुख्य_on(vfe);
		अगर (ret < 0)
			जाओ error_pm_करोमुख्य;

		ret = pm_runसमय_get_sync(vfe->camss->dev);
		अगर (ret < 0)
			जाओ error_pm_runसमय_get;

		ret = vfe_set_घड़ी_rates(vfe);
		अगर (ret < 0)
			जाओ error_pm_runसमय_get;

		ret = camss_enable_घड़ीs(vfe->nघड़ीs, vfe->घड़ी,
					  vfe->camss->dev);
		अगर (ret < 0)
			जाओ error_pm_runसमय_get;

		ret = vfe_reset(vfe);
		अगर (ret < 0)
			जाओ error_reset;

		vfe_reset_output_maps(vfe);

		vfe_init_outमाला_दो(vfe);
	पूर्ण अन्यथा अणु
		ret = vfe_check_घड़ी_rates(vfe);
		अगर (ret < 0)
			जाओ error_pm_runसमय_get;
	पूर्ण
	vfe->घातer_count++;

	mutex_unlock(&vfe->घातer_lock);

	वापस 0;

error_reset:
	camss_disable_घड़ीs(vfe->nघड़ीs, vfe->घड़ी);

error_pm_runसमय_get:
	pm_runसमय_put_sync(vfe->camss->dev);
	vfe->ops->pm_करोमुख्य_off(vfe);

error_pm_करोमुख्य:
	mutex_unlock(&vfe->घातer_lock);

	वापस ret;
पूर्ण

/*
 * vfe_put - Power करोwn VFE module
 * @vfe: VFE Device
 */
अटल व्योम vfe_put(काष्ठा vfe_device *vfe)
अणु
	mutex_lock(&vfe->घातer_lock);

	अगर (vfe->घातer_count == 0) अणु
		dev_err(vfe->camss->dev, "vfe power off on power_count == 0\n");
		जाओ निकास;
	पूर्ण अन्यथा अगर (vfe->घातer_count == 1) अणु
		अगर (vfe->was_streaming) अणु
			vfe->was_streaming = 0;
			vfe->ops->vfe_halt(vfe);
		पूर्ण
		camss_disable_घड़ीs(vfe->nघड़ीs, vfe->घड़ी);
		pm_runसमय_put_sync(vfe->camss->dev);
		vfe->ops->pm_करोमुख्य_off(vfe);
	पूर्ण

	vfe->घातer_count--;

निकास:
	mutex_unlock(&vfe->घातer_lock);
पूर्ण

/*
 * vfe_flush_buffers - Return all vb2 buffers
 * @vid: Video device काष्ठाure
 * @state: vb2 buffer state of the वापसed buffers
 *
 * Return all buffers to vb2. This includes queued pending buffers (still
 * unused) and any buffers given to the hardware but again still not used.
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक vfe_flush_buffers(काष्ठा camss_video *vid,
		      क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vfe_line *line = container_of(vid, काष्ठा vfe_line, video_out);
	काष्ठा vfe_device *vfe = to_vfe(line);
	काष्ठा vfe_output *output;
	अचिन्हित दीर्घ flags;

	output = &line->output;

	spin_lock_irqsave(&vfe->output_lock, flags);

	vfe_buf_flush_pending(output, state);

	अगर (output->buf[0])
		vb2_buffer_करोne(&output->buf[0]->vb.vb2_buf, state);

	अगर (output->buf[1])
		vb2_buffer_करोne(&output->buf[1]->vb.vb2_buf, state);

	अगर (output->last_buffer) अणु
		vb2_buffer_करोne(&output->last_buffer->vb.vb2_buf, state);
		output->last_buffer = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&vfe->output_lock, flags);

	वापस 0;
पूर्ण

/*
 * vfe_set_घातer - Power on/off VFE module
 * @sd: VFE V4L2 subdevice
 * @on: Requested घातer state
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा vfe_device *vfe = to_vfe(line);
	पूर्णांक ret;

	अगर (on) अणु
		ret = vfe_get(vfe);
		अगर (ret < 0)
			वापस ret;

		vfe->ops->hw_version_पढ़ो(vfe, vfe->camss->dev);
	पूर्ण अन्यथा अणु
		vfe_put(vfe);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_set_stream - Enable/disable streaming on VFE module
 * @sd: VFE V4L2 subdevice
 * @enable: Requested streaming state
 *
 * Main configuration of VFE module is triggered here.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा vfe_device *vfe = to_vfe(line);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = vfe->ops->vfe_enable(line);
		अगर (ret < 0)
			dev_err(vfe->camss->dev,
				"Failed to enable vfe outputs\n");
	पूर्ण अन्यथा अणु
		ret = vfe->ops->vfe_disable(line);
		अगर (ret < 0)
			dev_err(vfe->camss->dev,
				"Failed to disable vfe outputs\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * __vfe_get_क्रमmat - Get poपूर्णांकer to क्रमmat काष्ठाure
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad from which क्रमmat is requested
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE क्रमmat काष्ठाure
 */
अटल काष्ठा v4l2_mbus_framefmt *
__vfe_get_क्रमmat(काष्ठा vfe_line *line,
		 काष्ठा v4l2_subdev_pad_config *cfg,
		 अचिन्हित पूर्णांक pad,
		 क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&line->subdev, cfg, pad);

	वापस &line->fmt[pad];
पूर्ण

/*
 * __vfe_get_compose - Get poपूर्णांकer to compose selection काष्ठाure
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE compose rectangle काष्ठाure
 */
अटल काष्ठा v4l2_rect *
__vfe_get_compose(काष्ठा vfe_line *line,
		  काष्ठा v4l2_subdev_pad_config *cfg,
		  क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_compose(&line->subdev, cfg,
						   MSM_VFE_PAD_SINK);

	वापस &line->compose;
पूर्ण

/*
 * __vfe_get_crop - Get poपूर्णांकer to crop selection काष्ठाure
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE crop rectangle काष्ठाure
 */
अटल काष्ठा v4l2_rect *
__vfe_get_crop(काष्ठा vfe_line *line,
	       काष्ठा v4l2_subdev_pad_config *cfg,
	       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&line->subdev, cfg,
						MSM_VFE_PAD_SRC);

	वापस &line->crop;
पूर्ण

/*
 * vfe_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad on which क्रमmat is requested
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम vfe_try_क्रमmat(काष्ठा vfe_line *line,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad,
			   काष्ठा v4l2_mbus_framefmt *fmt,
			   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अचिन्हित पूर्णांक i;
	u32 code;

	चयन (pad) अणु
	हाल MSM_VFE_PAD_SINK:
		/* Set क्रमmat on sink pad */

		क्रम (i = 0; i < line->nक्रमmats; i++)
			अगर (fmt->code == line->क्रमmats[i].code)
				अवरोध;

		/* If not found, use UYVY as शेष */
		अगर (i >= line->nक्रमmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		अवरोध;

	हाल MSM_VFE_PAD_SRC:
		/* Set and वापस a क्रमmat same as sink pad */
		code = fmt->code;

		*fmt = *__vfe_get_क्रमmat(line, cfg, MSM_VFE_PAD_SINK, which);

		fmt->code = vfe_src_pad_code(line, fmt->code, 0, code);

		अगर (line->id == VFE_LINE_PIX) अणु
			काष्ठा v4l2_rect *rect;

			rect = __vfe_get_crop(line, cfg, which);

			fmt->width = rect->width;
			fmt->height = rect->height;
		पूर्ण

		अवरोध;
	पूर्ण

	fmt->colorspace = V4L2_COLORSPACE_SRGB;
पूर्ण

/*
 * vfe_try_compose - Handle try compose selection by pad subdev method
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @rect: poपूर्णांकer to v4l2 rect काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम vfe_try_compose(काष्ठा vfe_line *line,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_rect *rect,
			    क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt;

	fmt = __vfe_get_क्रमmat(line, cfg, MSM_VFE_PAD_SINK, which);

	अगर (rect->width > fmt->width)
		rect->width = fmt->width;

	अगर (rect->height > fmt->height)
		rect->height = fmt->height;

	अगर (fmt->width > rect->width * SCALER_RATIO_MAX)
		rect->width = (fmt->width + SCALER_RATIO_MAX - 1) /
							SCALER_RATIO_MAX;

	rect->width &= ~0x1;

	अगर (fmt->height > rect->height * SCALER_RATIO_MAX)
		rect->height = (fmt->height + SCALER_RATIO_MAX - 1) /
							SCALER_RATIO_MAX;

	अगर (rect->width < 16)
		rect->width = 16;

	अगर (rect->height < 4)
		rect->height = 4;
पूर्ण

/*
 * vfe_try_crop - Handle try crop selection by pad subdev method
 * @line: VFE line
 * @cfg: V4L2 subdev pad configuration
 * @rect: poपूर्णांकer to v4l2 rect काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम vfe_try_crop(काष्ठा vfe_line *line,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_rect *rect,
			 क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_rect *compose;

	compose = __vfe_get_compose(line, cfg, which);

	अगर (rect->width > compose->width)
		rect->width = compose->width;

	अगर (rect->width + rect->left > compose->width)
		rect->left = compose->width - rect->width;

	अगर (rect->height > compose->height)
		rect->height = compose->height;

	अगर (rect->height + rect->top > compose->height)
		rect->top = compose->height - rect->height;

	/* wm in line based mode ग_लिखोs multiple of 16 horizontally */
	rect->left += (rect->width & 0xf) >> 1;
	rect->width &= ~0xf;

	अगर (rect->width < 16) अणु
		rect->left = 0;
		rect->width = 16;
	पूर्ण

	अगर (rect->height < 4) अणु
		rect->top = 0;
		rect->height = 4;
	पूर्ण
पूर्ण

/*
 * vfe_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 *
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक vfe_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);

	अगर (code->pad == MSM_VFE_PAD_SINK) अणु
		अगर (code->index >= line->nक्रमmats)
			वापस -EINVAL;

		code->code = line->क्रमmats[code->index].code;
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_mbus_framefmt *sink_fmt;

		sink_fmt = __vfe_get_क्रमmat(line, cfg, MSM_VFE_PAD_SINK,
					    code->which);

		code->code = vfe_src_pad_code(line, sink_fmt->code,
					      code->index, 0);
		अगर (!code->code)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_क्रमागत_frame_size - Handle frame size क्रमागतeration
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: poपूर्णांकer to v4l2_subdev_frame_size_क्रमागत काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक vfe_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	vfe_try_क्रमmat(line, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	vfe_try_क्रमmat(line, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * vfe_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक vfe_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __vfe_get_क्रमmat(line, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक vfe_set_selection(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel);

/*
 * vfe_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक vfe_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __vfe_get_क्रमmat(line, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	vfe_try_क्रमmat(line, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	अगर (fmt->pad == MSM_VFE_PAD_SINK) अणु
		काष्ठा v4l2_subdev_selection sel = अणु 0 पूर्ण;
		पूर्णांक ret;

		/* Propagate the क्रमmat from sink to source */
		क्रमmat = __vfe_get_क्रमmat(line, cfg, MSM_VFE_PAD_SRC,
					  fmt->which);

		*क्रमmat = fmt->क्रमmat;
		vfe_try_क्रमmat(line, cfg, MSM_VFE_PAD_SRC, क्रमmat,
			       fmt->which);

		अगर (line->id != VFE_LINE_PIX)
			वापस 0;

		/* Reset sink pad compose selection */
		sel.which = fmt->which;
		sel.pad = MSM_VFE_PAD_SINK;
		sel.target = V4L2_SEL_TGT_COMPOSE;
		sel.r.width = fmt->क्रमmat.width;
		sel.r.height = fmt->क्रमmat.height;
		ret = vfe_set_selection(sd, cfg, &sel);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_get_selection - Handle get selection by pads subdev method
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: poपूर्णांकer to v4l2 subdev selection काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक vfe_get_selection(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु 0 पूर्ण;
	काष्ठा v4l2_rect *rect;
	पूर्णांक ret;

	अगर (line->id != VFE_LINE_PIX)
		वापस -EINVAL;

	अगर (sel->pad == MSM_VFE_PAD_SINK)
		चयन (sel->target) अणु
		हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
			fmt.pad = sel->pad;
			fmt.which = sel->which;
			ret = vfe_get_क्रमmat(sd, cfg, &fmt);
			अगर (ret < 0)
				वापस ret;

			sel->r.left = 0;
			sel->r.top = 0;
			sel->r.width = fmt.क्रमmat.width;
			sel->r.height = fmt.क्रमmat.height;
			अवरोध;
		हाल V4L2_SEL_TGT_COMPOSE:
			rect = __vfe_get_compose(line, cfg, sel->which);
			अगर (rect == शून्य)
				वापस -EINVAL;

			sel->r = *rect;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	अन्यथा अगर (sel->pad == MSM_VFE_PAD_SRC)
		चयन (sel->target) अणु
		हाल V4L2_SEL_TGT_CROP_BOUNDS:
			rect = __vfe_get_compose(line, cfg, sel->which);
			अगर (rect == शून्य)
				वापस -EINVAL;

			sel->r.left = rect->left;
			sel->r.top = rect->top;
			sel->r.width = rect->width;
			sel->r.height = rect->height;
			अवरोध;
		हाल V4L2_SEL_TGT_CROP:
			rect = __vfe_get_crop(line, cfg, sel->which);
			अगर (rect == शून्य)
				वापस -EINVAL;

			sel->r = *rect;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

	वापस 0;
पूर्ण

/*
 * vfe_set_selection - Handle set selection by pads subdev method
 * @sd: VFE V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: poपूर्णांकer to v4l2 subdev selection काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक vfe_set_selection(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा vfe_line *line = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_rect *rect;
	पूर्णांक ret;

	अगर (line->id != VFE_LINE_PIX)
		वापस -EINVAL;

	अगर (sel->target == V4L2_SEL_TGT_COMPOSE &&
		sel->pad == MSM_VFE_PAD_SINK) अणु
		काष्ठा v4l2_subdev_selection crop = अणु 0 पूर्ण;

		rect = __vfe_get_compose(line, cfg, sel->which);
		अगर (rect == शून्य)
			वापस -EINVAL;

		vfe_try_compose(line, cfg, &sel->r, sel->which);
		*rect = sel->r;

		/* Reset source crop selection */
		crop.which = sel->which;
		crop.pad = MSM_VFE_PAD_SRC;
		crop.target = V4L2_SEL_TGT_CROP;
		crop.r = *rect;
		ret = vfe_set_selection(sd, cfg, &crop);
	पूर्ण अन्यथा अगर (sel->target == V4L2_SEL_TGT_CROP &&
		sel->pad == MSM_VFE_PAD_SRC) अणु
		काष्ठा v4l2_subdev_क्रमmat fmt = अणु 0 पूर्ण;

		rect = __vfe_get_crop(line, cfg, sel->which);
		अगर (rect == शून्य)
			वापस -EINVAL;

		vfe_try_crop(line, cfg, &sel->r, sel->which);
		*rect = sel->r;

		/* Reset source pad क्रमmat width and height */
		fmt.which = sel->which;
		fmt.pad = MSM_VFE_PAD_SRC;
		ret = vfe_get_क्रमmat(sd, cfg, &fmt);
		अगर (ret < 0)
			वापस ret;

		fmt.क्रमmat.width = rect->width;
		fmt.क्रमmat.height = rect->height;
		ret = vfe_set_क्रमmat(sd, cfg, &fmt);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * vfe_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: VFE V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक vfe_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.pad = MSM_VFE_PAD_SINK,
		.which = fh ? V4L2_SUBDEV_FORMAT_TRY :
			      V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.code = MEDIA_BUS_FMT_UYVY8_2X8,
			.width = 1920,
			.height = 1080
		पूर्ण
	पूर्ण;

	वापस vfe_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);
पूर्ण

/*
 * msm_vfe_subdev_init - Initialize VFE device काष्ठाure and resources
 * @vfe: VFE device
 * @res: VFE module resources table
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_vfe_subdev_init(काष्ठा camss *camss, काष्ठा vfe_device *vfe,
			स्थिर काष्ठा resources *res, u8 id)
अणु
	काष्ठा device *dev = camss->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *r;
	पूर्णांक i, j;
	पूर्णांक ret;

	चयन (camss->version) अणु
	हाल CAMSS_8x16:
		vfe->ops = &vfe_ops_4_1;
		अवरोध;
	हाल CAMSS_8x96:
		vfe->ops = &vfe_ops_4_7;
		अवरोध;
	हाल CAMSS_660:
		vfe->ops = &vfe_ops_4_8;
		अवरोध;

	हाल CAMSS_845:
		vfe->ops = &vfe_ops_170;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	vfe->ops->subdev_init(dev, vfe);

	/* Memory */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	vfe->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(vfe->base)) अणु
		dev_err(dev, "could not map memory\n");
		वापस PTR_ERR(vfe->base);
	पूर्ण

	/* Interrupt */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ,
					 res->पूर्णांकerrupt[0]);
	अगर (!r) अणु
		dev_err(dev, "missing IRQ\n");
		वापस -EINVAL;
	पूर्ण

	vfe->irq = r->start;
	snम_लिखो(vfe->irq_name, माप(vfe->irq_name), "%s_%s%d",
		 dev_name(dev), MSM_VFE_NAME, vfe->id);
	ret = devm_request_irq(dev, vfe->irq, vfe->ops->isr,
			       IRQF_TRIGGER_RISING, vfe->irq_name, vfe);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Clocks */

	vfe->nघड़ीs = 0;
	जबतक (res->घड़ी[vfe->nघड़ीs])
		vfe->nघड़ीs++;

	vfe->घड़ी = devm_kसुस्मृति(dev, vfe->nघड़ीs, माप(*vfe->घड़ी),
				  GFP_KERNEL);
	अगर (!vfe->घड़ी)
		वापस -ENOMEM;

	क्रम (i = 0; i < vfe->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &vfe->घड़ी[i];

		घड़ी->clk = devm_clk_get(dev, res->घड़ी[i]);
		अगर (IS_ERR(घड़ी->clk))
			वापस PTR_ERR(घड़ी->clk);

		घड़ी->name = res->घड़ी[i];

		घड़ी->nfreqs = 0;
		जबतक (res->घड़ी_rate[i][घड़ी->nfreqs])
			घड़ी->nfreqs++;

		अगर (!घड़ी->nfreqs) अणु
			घड़ी->freq = शून्य;
			जारी;
		पूर्ण

		घड़ी->freq = devm_kसुस्मृति(dev,
					   घड़ी->nfreqs,
					   माप(*घड़ी->freq),
					   GFP_KERNEL);
		अगर (!घड़ी->freq)
			वापस -ENOMEM;

		क्रम (j = 0; j < घड़ी->nfreqs; j++)
			घड़ी->freq[j] = res->घड़ी_rate[i][j];
	पूर्ण

	mutex_init(&vfe->घातer_lock);
	vfe->घातer_count = 0;

	mutex_init(&vfe->stream_lock);
	vfe->stream_count = 0;

	spin_lock_init(&vfe->output_lock);

	vfe->camss = camss;
	vfe->id = id;
	vfe->reg_update = 0;

	क्रम (i = VFE_LINE_RDI0; i < vfe->line_num; i++) अणु
		काष्ठा vfe_line *l = &vfe->line[i];

		l->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		l->video_out.camss = camss;
		l->id = i;
		init_completion(&l->output.sof);
		init_completion(&l->output.reg_update);

		अगर (camss->version == CAMSS_8x16) अणु
			अगर (i == VFE_LINE_PIX) अणु
				l->क्रमmats = क्रमmats_pix_8x16;
				l->nक्रमmats = ARRAY_SIZE(क्रमmats_pix_8x16);
			पूर्ण अन्यथा अणु
				l->क्रमmats = क्रमmats_rdi_8x16;
				l->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_8x16);
			पूर्ण
		पूर्ण अन्यथा अगर (camss->version == CAMSS_8x96 ||
			   camss->version == CAMSS_660) अणु
			अगर (i == VFE_LINE_PIX) अणु
				l->क्रमmats = क्रमmats_pix_8x96;
				l->nक्रमmats = ARRAY_SIZE(क्रमmats_pix_8x96);
			पूर्ण अन्यथा अणु
				l->क्रमmats = क्रमmats_rdi_8x96;
				l->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_8x96);
			पूर्ण
		पूर्ण अन्यथा अगर (camss->version == CAMSS_845) अणु
			l->क्रमmats = क्रमmats_rdi_845;
			l->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_845);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	init_completion(&vfe->reset_complete);
	init_completion(&vfe->halt_complete);

	वापस 0;
पूर्ण

/*
 * msm_vfe_get_vfe_id - Get VFE HW module id
 * @entity: Poपूर्णांकer to VFE media entity काष्ठाure
 * @id: Return CSID HW module id here
 */
व्योम msm_vfe_get_vfe_id(काष्ठा media_entity *entity, u8 *id)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा vfe_line *line;
	काष्ठा vfe_device *vfe;

	sd = media_entity_to_v4l2_subdev(entity);
	line = v4l2_get_subdevdata(sd);
	vfe = to_vfe(line);

	*id = vfe->id;
पूर्ण

/*
 * msm_vfe_get_vfe_line_id - Get VFE line id by media entity
 * @entity: Poपूर्णांकer to VFE media entity काष्ठाure
 * @id: Return VFE line id here
 */
व्योम msm_vfe_get_vfe_line_id(काष्ठा media_entity *entity, क्रमागत vfe_line_id *id)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा vfe_line *line;

	sd = media_entity_to_v4l2_subdev(entity);
	line = v4l2_get_subdevdata(sd);

	*id = line->id;
पूर्ण

/*
 * vfe_link_setup - Setup VFE connections
 * @entity: Poपूर्णांकer to media entity काष्ठाure
 * @local: Poपूर्णांकer to local pad
 * @remote: Poपूर्णांकer to remote pad
 * @flags: Link flags
 *
 * Return 0 on success
 */
अटल पूर्णांक vfe_link_setup(काष्ठा media_entity *entity,
			  स्थिर काष्ठा media_pad *local,
			  स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	अगर (flags & MEDIA_LNK_FL_ENABLED)
		अगर (media_entity_remote_pad(local))
			वापस -EBUSY;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops vfe_core_ops = अणु
	.s_घातer = vfe_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vfe_video_ops = अणु
	.s_stream = vfe_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops vfe_pad_ops = अणु
	.क्रमागत_mbus_code = vfe_क्रमागत_mbus_code,
	.क्रमागत_frame_size = vfe_क्रमागत_frame_size,
	.get_fmt = vfe_get_क्रमmat,
	.set_fmt = vfe_set_क्रमmat,
	.get_selection = vfe_get_selection,
	.set_selection = vfe_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vfe_v4l2_ops = अणु
	.core = &vfe_core_ops,
	.video = &vfe_video_ops,
	.pad = &vfe_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops vfe_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = vfe_init_क्रमmats,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations vfe_media_ops = अणु
	.link_setup = vfe_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * msm_vfe_रेजिस्टर_entities - Register subdev node क्रम VFE module
 * @vfe: VFE device
 * @v4l2_dev: V4L2 device
 *
 * Initialize and रेजिस्टर a subdev node क्रम the VFE module. Then
 * call msm_video_रेजिस्टर() to रेजिस्टर the video device node which
 * will be connected to this subdev node. Then actually create the
 * media link between them.
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_vfe_रेजिस्टर_entities(काष्ठा vfe_device *vfe,
			      काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा device *dev = vfe->camss->dev;
	काष्ठा v4l2_subdev *sd;
	काष्ठा media_pad *pads;
	काष्ठा camss_video *video_out;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < vfe->line_num; i++) अणु
		अक्षर name[32];

		sd = &vfe->line[i].subdev;
		pads = vfe->line[i].pads;
		video_out = &vfe->line[i].video_out;

		v4l2_subdev_init(sd, &vfe_v4l2_ops);
		sd->पूर्णांकernal_ops = &vfe_v4l2_पूर्णांकernal_ops;
		sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
		अगर (i == VFE_LINE_PIX)
			snम_लिखो(sd->name, ARRAY_SIZE(sd->name), "%s%d_%s",
				 MSM_VFE_NAME, vfe->id, "pix");
		अन्यथा
			snम_लिखो(sd->name, ARRAY_SIZE(sd->name), "%s%d_%s%d",
				 MSM_VFE_NAME, vfe->id, "rdi", i);

		v4l2_set_subdevdata(sd, &vfe->line[i]);

		ret = vfe_init_क्रमmats(sd, शून्य);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to init format: %d\n", ret);
			जाओ error_init;
		पूर्ण

		pads[MSM_VFE_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
		pads[MSM_VFE_PAD_SRC].flags = MEDIA_PAD_FL_SOURCE;

		sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
		sd->entity.ops = &vfe_media_ops;
		ret = media_entity_pads_init(&sd->entity, MSM_VFE_PADS_NUM,
					     pads);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to init media entity: %d\n", ret);
			जाओ error_init;
		पूर्ण

		ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register subdev: %d\n", ret);
			जाओ error_reg_subdev;
		पूर्ण

		video_out->ops = &vfe->video_ops;
		video_out->bpl_alignment = 8;
		video_out->line_based = 0;
		अगर (i == VFE_LINE_PIX) अणु
			video_out->bpl_alignment = 16;
			video_out->line_based = 1;
		पूर्ण
		snम_लिखो(name, ARRAY_SIZE(name), "%s%d_%s%d",
			 MSM_VFE_NAME, vfe->id, "video", i);
		ret = msm_video_रेजिस्टर(video_out, v4l2_dev, name,
					 i == VFE_LINE_PIX ? 1 : 0);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register video node: %d\n",
				ret);
			जाओ error_reg_video;
		पूर्ण

		ret = media_create_pad_link(
				&sd->entity, MSM_VFE_PAD_SRC,
				&video_out->vdev.entity, 0,
				MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to link %s->%s entities: %d\n",
				sd->entity.name, video_out->vdev.entity.name,
				ret);
			जाओ error_link;
		पूर्ण
	पूर्ण

	वापस 0;

error_link:
	msm_video_unरेजिस्टर(video_out);

error_reg_video:
	v4l2_device_unरेजिस्टर_subdev(sd);

error_reg_subdev:
	media_entity_cleanup(&sd->entity);

error_init:
	क्रम (i--; i >= 0; i--) अणु
		sd = &vfe->line[i].subdev;
		video_out = &vfe->line[i].video_out;

		msm_video_unरेजिस्टर(video_out);
		v4l2_device_unरेजिस्टर_subdev(sd);
		media_entity_cleanup(&sd->entity);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * msm_vfe_unरेजिस्टर_entities - Unरेजिस्टर VFE module subdev node
 * @vfe: VFE device
 */
व्योम msm_vfe_unरेजिस्टर_entities(काष्ठा vfe_device *vfe)
अणु
	पूर्णांक i;

	mutex_destroy(&vfe->घातer_lock);
	mutex_destroy(&vfe->stream_lock);

	क्रम (i = 0; i < vfe->line_num; i++) अणु
		काष्ठा v4l2_subdev *sd = &vfe->line[i].subdev;
		काष्ठा camss_video *video_out = &vfe->line[i].video_out;

		msm_video_unरेजिस्टर(video_out);
		v4l2_device_unरेजिस्टर_subdev(sd);
		media_entity_cleanup(&sd->entity);
	पूर्ण
पूर्ण
