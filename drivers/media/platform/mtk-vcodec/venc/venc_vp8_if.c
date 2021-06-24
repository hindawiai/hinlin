<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Daniel Hsiao <daniel.hsiao@mediatek.com>
 *         PoChun Lin <pochun.lin@mediatek.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "../mtk_vcodec_drv.h"
#समावेश "../mtk_vcodec_util.h"
#समावेश "../mtk_vcodec_intr.h"
#समावेश "../mtk_vcodec_enc.h"
#समावेश "../mtk_vcodec_enc_pm.h"
#समावेश "../venc_drv_base.h"
#समावेश "../venc_ipi_msg.h"
#समावेश "../venc_vpu_if.h"

#घोषणा VENC_BITSTREAM_FRAME_SIZE 0x0098
#घोषणा VENC_BITSTREAM_HEADER_LEN 0x00e8

/* This ac_tag is vp8 frame tag. */
#घोषणा MAX_AC_TAG_SIZE 10

/*
 * क्रमागत venc_vp8_vpu_work_buf - vp8 encoder buffer index
 */
क्रमागत venc_vp8_vpu_work_buf अणु
	VENC_VP8_VPU_WORK_BUF_LUMA,
	VENC_VP8_VPU_WORK_BUF_LUMA2,
	VENC_VP8_VPU_WORK_BUF_LUMA3,
	VENC_VP8_VPU_WORK_BUF_CHROMA,
	VENC_VP8_VPU_WORK_BUF_CHROMA2,
	VENC_VP8_VPU_WORK_BUF_CHROMA3,
	VENC_VP8_VPU_WORK_BUF_MV_INFO,
	VENC_VP8_VPU_WORK_BUF_BS_HEADER,
	VENC_VP8_VPU_WORK_BUF_PROB_BUF,
	VENC_VP8_VPU_WORK_BUF_RC_INFO,
	VENC_VP8_VPU_WORK_BUF_RC_CODE,
	VENC_VP8_VPU_WORK_BUF_RC_CODE2,
	VENC_VP8_VPU_WORK_BUF_RC_CODE3,
	VENC_VP8_VPU_WORK_BUF_MAX,
पूर्ण;

/*
 * काष्ठा venc_vp8_vpu_config - Structure क्रम vp8 encoder configuration
 *                              AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                              VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @input_fourcc: input fourcc
 * @bitrate: target bitrate (in bps)
 * @pic_w: picture width. Picture size is visible stream resolution, in pixels,
 *         to be used क्रम display purposes; must be smaller or equal to buffer
 *         size.
 * @pic_h: picture height
 * @buf_w: buffer width (with 16 alignment). Buffer size is stream resolution
 *         in pixels aligned to hardware requirements.
 * @buf_h: buffer height (with 16 alignment)
 * @gop_size: group of picture size (key frame)
 * @framerate: frame rate in fps
 * @ts_mode: temporal scalability mode (0: disable, 1: enable)
 *	     support three temporal layers - 0: 7.5fps 1: 7.5fps 2: 15fps.
 */
काष्ठा venc_vp8_vpu_config अणु
	u32 input_fourcc;
	u32 bitrate;
	u32 pic_w;
	u32 pic_h;
	u32 buf_w;
	u32 buf_h;
	u32 gop_size;
	u32 framerate;
	u32 ts_mode;
पूर्ण;

/*
 * काष्ठा venc_vp8_vpu_buf - Structure क्रम buffer inक्रमmation
 *                           AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                           VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @iova: IO भव address
 * @vpua: VPU side memory addr which is used by RC_CODE
 * @size: buffer size (in bytes)
 */
काष्ठा venc_vp8_vpu_buf अणु
	u32 iova;
	u32 vpua;
	u32 size;
पूर्ण;

/*
 * काष्ठा venc_vp8_vsi - Structure क्रम VPU driver control and info share
 *                       AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                       VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * This काष्ठाure is allocated in VPU side and shared to AP side.
 * @config: vp8 encoder configuration
 * @work_bufs: working buffer inक्रमmation in VPU side
 * The work_bufs here is क्रम storing the 'size' info shared to AP side.
 * The similar item in काष्ठा venc_vp8_inst is क्रम memory allocation
 * in AP side. The AP driver will copy the 'size' from here to the one in
 * काष्ठा mtk_vcodec_mem, then invoke mtk_vcodec_mem_alloc to allocate
 * the buffer. After that, bypass the 'dma_addr' to the 'iova' field here क्रम
 * रेजिस्टर setting in VPU side.
 */
काष्ठा venc_vp8_vsi अणु
	काष्ठा venc_vp8_vpu_config config;
	काष्ठा venc_vp8_vpu_buf work_bufs[VENC_VP8_VPU_WORK_BUF_MAX];
पूर्ण;

/*
 * काष्ठा venc_vp8_inst - vp8 encoder AP driver instance
 * @hw_base: vp8 encoder hardware रेजिस्टर base
 * @work_bufs: working buffer
 * @work_buf_allocated: working buffer allocated flag
 * @frm_cnt: encoded frame count, it's used क्रम I-frame judgement and
 *	     reset when क्रमce पूर्णांकra cmd received.
 * @ts_mode: temporal scalability mode (0: disable, 1: enable)
 *	     support three temporal layers - 0: 7.5fps 1: 7.5fps 2: 15fps.
 * @vpu_inst: VPU instance to exchange inक्रमmation between AP and VPU
 * @vsi: driver काष्ठाure allocated by VPU side and shared to AP side क्रम
 *	 control and info share
 * @ctx: context क्रम v4l2 layer पूर्णांकegration
 */
काष्ठा venc_vp8_inst अणु
	व्योम __iomem *hw_base;
	काष्ठा mtk_vcodec_mem work_bufs[VENC_VP8_VPU_WORK_BUF_MAX];
	bool work_buf_allocated;
	अचिन्हित पूर्णांक frm_cnt;
	अचिन्हित पूर्णांक ts_mode;
	काष्ठा venc_vpu_inst vpu_inst;
	काष्ठा venc_vp8_vsi *vsi;
	काष्ठा mtk_vcodec_ctx *ctx;
पूर्ण;

अटल अंतरभूत u32 vp8_enc_पढ़ो_reg(काष्ठा venc_vp8_inst *inst, u32 addr)
अणु
	वापस पढ़ोl(inst->hw_base + addr);
पूर्ण

अटल व्योम vp8_enc_मुक्त_work_buf(काष्ठा venc_vp8_inst *inst)
अणु
	पूर्णांक i;

	mtk_vcodec_debug_enter(inst);

	/* Buffers need to be मुक्तd by AP. */
	क्रम (i = 0; i < VENC_VP8_VPU_WORK_BUF_MAX; i++) अणु
		अगर (inst->work_bufs[i].size == 0)
			जारी;
		mtk_vcodec_mem_मुक्त(inst->ctx, &inst->work_bufs[i]);
	पूर्ण

	mtk_vcodec_debug_leave(inst);
पूर्ण

अटल पूर्णांक vp8_enc_alloc_work_buf(काष्ठा venc_vp8_inst *inst)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा venc_vp8_vpu_buf *wb = inst->vsi->work_bufs;

	mtk_vcodec_debug_enter(inst);

	क्रम (i = 0; i < VENC_VP8_VPU_WORK_BUF_MAX; i++) अणु
		अगर (wb[i].size == 0)
			जारी;
		/*
		 * This 'wb' काष्ठाure is set by VPU side and shared to AP क्रम
		 * buffer allocation and IO भव addr mapping. For most of
		 * the buffers, AP will allocate the buffer according to 'size'
		 * field and store the IO भव addr in 'iova' field. For the
		 * RC_CODEx buffers, they are pre-allocated in the VPU side
		 * because they are inside VPU SRAM, and save the VPU addr in
		 * the 'vpua' field. The AP will translate the VPU addr to the
		 * corresponding IO भव addr and store in 'iova' field.
		 */
		inst->work_bufs[i].size = wb[i].size;
		ret = mtk_vcodec_mem_alloc(inst->ctx, &inst->work_bufs[i]);
		अगर (ret) अणु
			mtk_vcodec_err(inst,
				       "cannot alloc work_bufs[%d]", i);
			जाओ err_alloc;
		पूर्ण
		/*
		 * This RC_CODEx is pre-allocated by VPU and saved in VPU addr.
		 * So we need use स_नकल to copy RC_CODEx from VPU addr पूर्णांकo IO
		 * भव addr in 'iova' field क्रम reg setting in VPU side.
		 */
		अगर (i == VENC_VP8_VPU_WORK_BUF_RC_CODE ||
		    i == VENC_VP8_VPU_WORK_BUF_RC_CODE2 ||
		    i == VENC_VP8_VPU_WORK_BUF_RC_CODE3) अणु
			काष्ठा mtk_vcodec_fw *handler;
			व्योम *पंचांगp_va;

			handler = inst->vpu_inst.ctx->dev->fw_handler;
			पंचांगp_va = mtk_vcodec_fw_map_dm_addr(handler,
							   wb[i].vpua);
			स_नकल(inst->work_bufs[i].va, पंचांगp_va, wb[i].size);
		पूर्ण
		wb[i].iova = inst->work_bufs[i].dma_addr;

		mtk_vcodec_debug(inst,
				 "work_bufs[%d] va=0x%p,iova=%pad,size=%zu",
				 i, inst->work_bufs[i].va,
				 &inst->work_bufs[i].dma_addr,
				 inst->work_bufs[i].size);
	पूर्ण

	mtk_vcodec_debug_leave(inst);

	वापस ret;

err_alloc:
	vp8_enc_मुक्त_work_buf(inst);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक vp8_enc_रुको_venc_करोne(काष्ठा venc_vp8_inst *inst)
अणु
	अचिन्हित पूर्णांक irq_status = 0;
	काष्ठा mtk_vcodec_ctx *ctx = (काष्ठा mtk_vcodec_ctx *)inst->ctx;

	अगर (!mtk_vcodec_रुको_क्रम_करोne_ctx(ctx, MTK_INST_IRQ_RECEIVED,
					  WAIT_INTR_TIMEOUT_MS)) अणु
		irq_status = ctx->irq_status;
		mtk_vcodec_debug(inst, "isr return %x", irq_status);
	पूर्ण
	वापस irq_status;
पूर्ण

/*
 * Compose ac_tag, bitstream header and bitstream payload पूर्णांकo
 * one bitstream buffer.
 */
अटल पूर्णांक vp8_enc_compose_one_frame(काष्ठा venc_vp8_inst *inst,
				     काष्ठा mtk_vcodec_mem *bs_buf,
				     अचिन्हित पूर्णांक *bs_size)
अणु
	अचिन्हित पूर्णांक not_key;
	u32 bs_frm_size;
	u32 bs_hdr_len;
	अचिन्हित पूर्णांक ac_tag_size;
	u8 ac_tag[MAX_AC_TAG_SIZE];
	u32 tag;

	bs_frm_size = vp8_enc_पढ़ो_reg(inst, VENC_BITSTREAM_FRAME_SIZE);
	bs_hdr_len = vp8_enc_पढ़ो_reg(inst, VENC_BITSTREAM_HEADER_LEN);

	/* अगर a frame is key frame, not_key is 0 */
	not_key = !inst->vpu_inst.is_key_frm;
	tag = (bs_hdr_len << 5) | 0x10 | not_key;
	ac_tag[0] = tag & 0xff;
	ac_tag[1] = (tag >> 8) & 0xff;
	ac_tag[2] = (tag >> 16) & 0xff;

	/* key frame */
	अगर (not_key == 0) अणु
		ac_tag_size = MAX_AC_TAG_SIZE;
		ac_tag[3] = 0x9d;
		ac_tag[4] = 0x01;
		ac_tag[5] = 0x2a;
		ac_tag[6] = inst->vsi->config.pic_w;
		ac_tag[7] = inst->vsi->config.pic_w >> 8;
		ac_tag[8] = inst->vsi->config.pic_h;
		ac_tag[9] = inst->vsi->config.pic_h >> 8;
	पूर्ण अन्यथा अणु
		ac_tag_size = 3;
	पूर्ण

	अगर (bs_buf->size < bs_hdr_len + bs_frm_size + ac_tag_size) अणु
		mtk_vcodec_err(inst, "bitstream buf size is too small(%zu)",
			       bs_buf->size);
		वापस -EINVAL;
	पूर्ण

	/*
	* (1) The vp8 bitstream header and body are generated by the HW vp8
	* encoder separately at the same समय. We cannot know the bitstream
	* header length in advance.
	* (2) From the vp8 spec, there is no stuffing byte allowed between the
	* ac tag, bitstream header and bitstream body.
	*/
	स_हटाओ(bs_buf->va + bs_hdr_len + ac_tag_size,
		bs_buf->va, bs_frm_size);
	स_नकल(bs_buf->va + ac_tag_size,
	       inst->work_bufs[VENC_VP8_VPU_WORK_BUF_BS_HEADER].va,
	       bs_hdr_len);
	स_नकल(bs_buf->va, ac_tag, ac_tag_size);
	*bs_size = bs_frm_size + bs_hdr_len + ac_tag_size;

	वापस 0;
पूर्ण

अटल पूर्णांक vp8_enc_encode_frame(काष्ठा venc_vp8_inst *inst,
				काष्ठा venc_frm_buf *frm_buf,
				काष्ठा mtk_vcodec_mem *bs_buf,
				अचिन्हित पूर्णांक *bs_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक irq_status;

	mtk_vcodec_debug(inst, "->frm_cnt=%d", inst->frm_cnt);

	ret = vpu_enc_encode(&inst->vpu_inst, 0, frm_buf, bs_buf, bs_size,
			     शून्य);
	अगर (ret)
		वापस ret;

	irq_status = vp8_enc_रुको_venc_करोne(inst);
	अगर (irq_status != MTK_VENC_IRQ_STATUS_FRM) अणु
		mtk_vcodec_err(inst, "irq_status=%d failed", irq_status);
		वापस -EIO;
	पूर्ण

	अगर (vp8_enc_compose_one_frame(inst, bs_buf, bs_size)) अणु
		mtk_vcodec_err(inst, "vp8_enc_compose_one_frame failed");
		वापस -EINVAL;
	पूर्ण

	inst->frm_cnt++;
	mtk_vcodec_debug(inst, "<-size=%d key_frm=%d", *bs_size,
			 inst->vpu_inst.is_key_frm);

	वापस ret;
पूर्ण

अटल पूर्णांक vp8_enc_init(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_vp8_inst *inst;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	inst->ctx = ctx;
	inst->vpu_inst.ctx = ctx;
	inst->vpu_inst.id = IPI_VENC_VP8;
	inst->hw_base = mtk_vcodec_get_reg_addr(inst->ctx, VENC_LT_SYS);

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_init(&inst->vpu_inst);

	inst->vsi = (काष्ठा venc_vp8_vsi *)inst->vpu_inst.vsi;

	mtk_vcodec_debug_leave(inst);

	अगर (ret)
		kमुक्त(inst);
	अन्यथा
		ctx->drv_handle = inst;

	वापस ret;
पूर्ण

अटल पूर्णांक vp8_enc_encode(व्योम *handle,
			  क्रमागत venc_start_opt opt,
			  काष्ठा venc_frm_buf *frm_buf,
			  काष्ठा mtk_vcodec_mem *bs_buf,
			  काष्ठा venc_करोne_result *result)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_vp8_inst *inst = (काष्ठा venc_vp8_inst *)handle;
	काष्ठा mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_debug_enter(inst);

	enable_irq(ctx->dev->enc_irq);

	चयन (opt) अणु
	हाल VENC_START_OPT_ENCODE_FRAME:
		ret = vp8_enc_encode_frame(inst, frm_buf, bs_buf,
					   &result->bs_size);
		अगर (ret)
			जाओ encode_err;
		result->is_key_frm = inst->vpu_inst.is_key_frm;
		अवरोध;

	शेष:
		mtk_vcodec_err(inst, "opt not support:%d", opt);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

encode_err:

	disable_irq(ctx->dev->enc_irq);
	mtk_vcodec_debug_leave(inst);

	वापस ret;
पूर्ण

अटल पूर्णांक vp8_enc_set_param(व्योम *handle,
			     क्रमागत venc_set_param_type type,
			     काष्ठा venc_enc_param *enc_prm)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_vp8_inst *inst = (काष्ठा venc_vp8_inst *)handle;

	mtk_vcodec_debug(inst, "->type=%d", type);

	चयन (type) अणु
	हाल VENC_SET_PARAM_ENC:
		inst->vsi->config.input_fourcc = enc_prm->input_yuv_fmt;
		inst->vsi->config.bitrate = enc_prm->bitrate;
		inst->vsi->config.pic_w = enc_prm->width;
		inst->vsi->config.pic_h = enc_prm->height;
		inst->vsi->config.buf_w = enc_prm->buf_width;
		inst->vsi->config.buf_h = enc_prm->buf_height;
		inst->vsi->config.gop_size = enc_prm->gop_size;
		inst->vsi->config.framerate = enc_prm->frm_rate;
		inst->vsi->config.ts_mode = inst->ts_mode;
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		अगर (ret)
			अवरोध;
		अगर (inst->work_buf_allocated) अणु
			vp8_enc_मुक्त_work_buf(inst);
			inst->work_buf_allocated = false;
		पूर्ण
		ret = vp8_enc_alloc_work_buf(inst);
		अगर (ret)
			अवरोध;
		inst->work_buf_allocated = true;
		अवरोध;

	/*
	 * VENC_SET_PARAM_TS_MODE must be called beक्रमe VENC_SET_PARAM_ENC
	 */
	हाल VENC_SET_PARAM_TS_MODE:
		inst->ts_mode = 1;
		mtk_vcodec_debug(inst, "set ts_mode");
		अवरोध;

	शेष:
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		अवरोध;
	पूर्ण

	mtk_vcodec_debug_leave(inst);

	वापस ret;
पूर्ण

अटल पूर्णांक vp8_enc_deinit(व्योम *handle)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_vp8_inst *inst = (काष्ठा venc_vp8_inst *)handle;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_deinit(&inst->vpu_inst);

	अगर (inst->work_buf_allocated)
		vp8_enc_मुक्त_work_buf(inst);

	mtk_vcodec_debug_leave(inst);
	kमुक्त(inst);

	वापस ret;
पूर्ण

स्थिर काष्ठा venc_common_अगर venc_vp8_अगर = अणु
	.init = vp8_enc_init,
	.encode = vp8_enc_encode,
	.set_param = vp8_enc_set_param,
	.deinit = vp8_enc_deinit,
पूर्ण;
