<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Jungchang Tsao <jungchang.tsao@mediatek.com>
 *         Daniel Hsiao <daniel.hsiao@mediatek.com>
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

अटल स्थिर अक्षर h264_filler_marker[] = अणु0x0, 0x0, 0x0, 0x1, 0xcपूर्ण;

#घोषणा H264_FILLER_MARKER_SIZE ARRAY_SIZE(h264_filler_marker)
#घोषणा VENC_PIC_BITSTREAM_BYTE_CNT 0x0098

/*
 * क्रमागत venc_h264_frame_type - h264 encoder output bitstream frame type
 */
क्रमागत venc_h264_frame_type अणु
	VENC_H264_IDR_FRM,
	VENC_H264_I_FRM,
	VENC_H264_P_FRM,
	VENC_H264_B_FRM,
पूर्ण;

/*
 * क्रमागत venc_h264_vpu_work_buf - h264 encoder buffer index
 */
क्रमागत venc_h264_vpu_work_buf अणु
	VENC_H264_VPU_WORK_BUF_RC_INFO,
	VENC_H264_VPU_WORK_BUF_RC_CODE,
	VENC_H264_VPU_WORK_BUF_REC_LUMA,
	VENC_H264_VPU_WORK_BUF_REC_CHROMA,
	VENC_H264_VPU_WORK_BUF_REF_LUMA,
	VENC_H264_VPU_WORK_BUF_REF_CHROMA,
	VENC_H264_VPU_WORK_BUF_MV_INFO_1,
	VENC_H264_VPU_WORK_BUF_MV_INFO_2,
	VENC_H264_VPU_WORK_BUF_SKIP_FRAME,
	VENC_H264_VPU_WORK_BUF_MAX,
पूर्ण;

/*
 * क्रमागत venc_h264_bs_mode - क्रम bs_mode argument in h264_enc_vpu_encode
 */
क्रमागत venc_h264_bs_mode अणु
	H264_BS_MODE_SPS,
	H264_BS_MODE_PPS,
	H264_BS_MODE_FRAME,
पूर्ण;

/*
 * काष्ठा venc_h264_vpu_config - Structure क्रम h264 encoder configuration
 *                               AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                               VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @input_fourcc: input fourcc
 * @bitrate: target bitrate (in bps)
 * @pic_w: picture width. Picture size is visible stream resolution, in pixels,
 *         to be used क्रम display purposes; must be smaller or equal to buffer
 *         size.
 * @pic_h: picture height
 * @buf_w: buffer width. Buffer size is stream resolution in pixels aligned to
 *         hardware requirements.
 * @buf_h: buffer height
 * @gop_size: group of picture size (idr frame)
 * @पूर्णांकra_period: पूर्णांकra frame period
 * @framerate: frame rate in fps
 * @profile: as specअगरied in standard
 * @level: as specअगरied in standard
 * @wfd: WFD mode 1:on, 0:off
 */
काष्ठा venc_h264_vpu_config अणु
	u32 input_fourcc;
	u32 bitrate;
	u32 pic_w;
	u32 pic_h;
	u32 buf_w;
	u32 buf_h;
	u32 gop_size;
	u32 पूर्णांकra_period;
	u32 framerate;
	u32 profile;
	u32 level;
	u32 wfd;
पूर्ण;

/*
 * काष्ठा venc_h264_vpu_buf - Structure क्रम buffer inक्रमmation
 *                            AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                            VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @iova: IO भव address
 * @vpua: VPU side memory addr which is used by RC_CODE
 * @size: buffer size (in bytes)
 */
काष्ठा venc_h264_vpu_buf अणु
	u32 iova;
	u32 vpua;
	u32 size;
पूर्ण;

/*
 * काष्ठा venc_h264_vsi - Structure क्रम VPU driver control and info share
 *                        AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                        VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * This काष्ठाure is allocated in VPU side and shared to AP side.
 * @config: h264 encoder configuration
 * @work_bufs: working buffer inक्रमmation in VPU side
 * The work_bufs here is क्रम storing the 'size' info shared to AP side.
 * The similar item in काष्ठा venc_h264_inst is क्रम memory allocation
 * in AP side. The AP driver will copy the 'size' from here to the one in
 * काष्ठा mtk_vcodec_mem, then invoke mtk_vcodec_mem_alloc to allocate
 * the buffer. After that, bypass the 'dma_addr' to the 'iova' field here क्रम
 * रेजिस्टर setting in VPU side.
 */
काष्ठा venc_h264_vsi अणु
	काष्ठा venc_h264_vpu_config config;
	काष्ठा venc_h264_vpu_buf work_bufs[VENC_H264_VPU_WORK_BUF_MAX];
पूर्ण;

/*
 * काष्ठा venc_h264_inst - h264 encoder AP driver instance
 * @hw_base: h264 encoder hardware रेजिस्टर base
 * @work_bufs: working buffer
 * @pps_buf: buffer to store the pps bitstream
 * @work_buf_allocated: working buffer allocated flag
 * @frm_cnt: encoded frame count
 * @prepend_hdr: when the v4l2 layer send VENC_SET_PARAM_PREPEND_HEADER cmd
 *  through h264_enc_set_param पूर्णांकerface, it will set this flag and prepend the
 *  sps/pps in h264_enc_encode function.
 * @vpu_inst: VPU instance to exchange inक्रमmation between AP and VPU
 * @vsi: driver काष्ठाure allocated by VPU side and shared to AP side क्रम
 *	 control and info share
 * @ctx: context क्रम v4l2 layer पूर्णांकegration
 */
काष्ठा venc_h264_inst अणु
	व्योम __iomem *hw_base;
	काष्ठा mtk_vcodec_mem work_bufs[VENC_H264_VPU_WORK_BUF_MAX];
	काष्ठा mtk_vcodec_mem pps_buf;
	bool work_buf_allocated;
	अचिन्हित पूर्णांक frm_cnt;
	अचिन्हित पूर्णांक skip_frm_cnt;
	अचिन्हित पूर्णांक prepend_hdr;
	काष्ठा venc_vpu_inst vpu_inst;
	काष्ठा venc_h264_vsi *vsi;
	काष्ठा mtk_vcodec_ctx *ctx;
पूर्ण;

अटल अंतरभूत u32 h264_पढ़ो_reg(काष्ठा venc_h264_inst *inst, u32 addr)
अणु
	वापस पढ़ोl(inst->hw_base + addr);
पूर्ण

अटल अचिन्हित पूर्णांक h264_get_profile(काष्ठा venc_h264_inst *inst,
				     अचिन्हित पूर्णांक profile)
अणु
	चयन (profile) अणु
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE:
		वापस 66;
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_MAIN:
		वापस 77;
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_HIGH:
		वापस 100;
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE:
		mtk_vcodec_err(inst, "unsupported CONSTRAINED_BASELINE");
		वापस 0;
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_EXTENDED:
		mtk_vcodec_err(inst, "unsupported EXTENDED");
		वापस 0;
	शेष:
		mtk_vcodec_debug(inst, "unsupported profile %d", profile);
		वापस 100;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक h264_get_level(काष्ठा venc_h264_inst *inst,
				   अचिन्हित पूर्णांक level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		mtk_vcodec_err(inst, "unsupported 1B");
		वापस 0;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		वापस 10;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		वापस 11;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		वापस 12;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		वापस 13;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		वापस 20;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		वापस 21;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		वापस 22;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		वापस 30;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		वापस 31;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		वापस 32;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		वापस 40;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		वापस 41;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		वापस 42;
	शेष:
		mtk_vcodec_debug(inst, "unsupported level %d", level);
		वापस 31;
	पूर्ण
पूर्ण

अटल व्योम h264_enc_मुक्त_work_buf(काष्ठा venc_h264_inst *inst)
अणु
	पूर्णांक i;

	mtk_vcodec_debug_enter(inst);

	/* Except the SKIP_FRAME buffers,
	 * other buffers need to be मुक्तd by AP.
	 */
	क्रम (i = 0; i < VENC_H264_VPU_WORK_BUF_MAX; i++) अणु
		अगर (i != VENC_H264_VPU_WORK_BUF_SKIP_FRAME)
			mtk_vcodec_mem_मुक्त(inst->ctx, &inst->work_bufs[i]);
	पूर्ण

	mtk_vcodec_mem_मुक्त(inst->ctx, &inst->pps_buf);

	mtk_vcodec_debug_leave(inst);
पूर्ण

अटल पूर्णांक h264_enc_alloc_work_buf(काष्ठा venc_h264_inst *inst)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा venc_h264_vpu_buf *wb = inst->vsi->work_bufs;

	mtk_vcodec_debug_enter(inst);

	क्रम (i = 0; i < VENC_H264_VPU_WORK_BUF_MAX; i++) अणु
		/*
		 * This 'wb' काष्ठाure is set by VPU side and shared to AP क्रम
		 * buffer allocation and IO भव addr mapping. For most of
		 * the buffers, AP will allocate the buffer according to 'size'
		 * field and store the IO भव addr in 'iova' field. There
		 * are two exceptions:
		 * (1) RC_CODE buffer, it's pre-allocated in the VPU side, and
		 * save the VPU addr in the 'vpua' field. The AP will translate
		 * the VPU addr to the corresponding IO भव addr and store
		 * in 'iova' field क्रम reg setting in VPU side.
		 * (2) SKIP_FRAME buffer, it's pre-allocated in the VPU side,
		 * and save the VPU addr in the 'vpua' field. The AP will
		 * translate the VPU addr to the corresponding AP side भव
		 * address and करो some स_नकल access to move to bitstream buffer
		 * asचिन्हित by v4l2 layer.
		 */
		inst->work_bufs[i].size = wb[i].size;
		अगर (i == VENC_H264_VPU_WORK_BUF_SKIP_FRAME) अणु
			काष्ठा mtk_vcodec_fw *handler;

			handler = inst->vpu_inst.ctx->dev->fw_handler;
			inst->work_bufs[i].va =
				mtk_vcodec_fw_map_dm_addr(handler, wb[i].vpua);
			inst->work_bufs[i].dma_addr = 0;
		पूर्ण अन्यथा अणु
			ret = mtk_vcodec_mem_alloc(inst->ctx,
						   &inst->work_bufs[i]);
			अगर (ret) अणु
				mtk_vcodec_err(inst,
					       "cannot allocate buf %d", i);
				जाओ err_alloc;
			पूर्ण
			/*
			 * This RC_CODE is pre-allocated by VPU and saved in VPU
			 * addr. So we need use स_नकल to copy RC_CODE from VPU
			 * addr पूर्णांकo IO भव addr in 'iova' field क्रम reg
			 * setting in VPU side.
			 */
			अगर (i == VENC_H264_VPU_WORK_BUF_RC_CODE) अणु
				काष्ठा mtk_vcodec_fw *handler;
				व्योम *पंचांगp_va;

				handler = inst->vpu_inst.ctx->dev->fw_handler;
				पंचांगp_va = mtk_vcodec_fw_map_dm_addr(handler,
								   wb[i].vpua);
				स_नकल(inst->work_bufs[i].va, पंचांगp_va,
				       wb[i].size);
			पूर्ण
		पूर्ण
		wb[i].iova = inst->work_bufs[i].dma_addr;

		mtk_vcodec_debug(inst,
				 "work_buf[%d] va=0x%p iova=%pad size=%zu",
				 i, inst->work_bufs[i].va,
				 &inst->work_bufs[i].dma_addr,
				 inst->work_bufs[i].size);
	पूर्ण

	/* the pps_buf is used by AP side only */
	inst->pps_buf.size = 128;
	ret = mtk_vcodec_mem_alloc(inst->ctx, &inst->pps_buf);
	अगर (ret) अणु
		mtk_vcodec_err(inst, "cannot allocate pps_buf");
		जाओ err_alloc;
	पूर्ण

	mtk_vcodec_debug_leave(inst);

	वापस ret;

err_alloc:
	h264_enc_मुक्त_work_buf(inst);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक h264_enc_रुको_venc_करोne(काष्ठा venc_h264_inst *inst)
अणु
	अचिन्हित पूर्णांक irq_status = 0;
	काष्ठा mtk_vcodec_ctx *ctx = (काष्ठा mtk_vcodec_ctx *)inst->ctx;

	अगर (!mtk_vcodec_रुको_क्रम_करोne_ctx(ctx, MTK_INST_IRQ_RECEIVED,
					  WAIT_INTR_TIMEOUT_MS)) अणु
		irq_status = ctx->irq_status;
		mtk_vcodec_debug(inst, "irq_status %x <-", irq_status);
	पूर्ण
	वापस irq_status;
पूर्ण

अटल पूर्णांक h264_frame_type(काष्ठा venc_h264_inst *inst)
अणु
	अगर ((inst->vsi->config.gop_size != 0 &&
	     (inst->frm_cnt % inst->vsi->config.gop_size) == 0) ||
	    (inst->frm_cnt == 0 && inst->vsi->config.gop_size == 0)) अणु
		/* IDR frame */
		वापस VENC_H264_IDR_FRM;
	पूर्ण अन्यथा अगर ((inst->vsi->config.पूर्णांकra_period != 0 &&
		    (inst->frm_cnt % inst->vsi->config.पूर्णांकra_period) == 0) ||
		   (inst->frm_cnt == 0 && inst->vsi->config.पूर्णांकra_period == 0)) अणु
		/* I frame */
		वापस VENC_H264_I_FRM;
	पूर्ण अन्यथा अणु
		वापस VENC_H264_P_FRM;  /* Note: B frames are not supported */
	पूर्ण
पूर्ण
अटल पूर्णांक h264_encode_sps(काष्ठा venc_h264_inst *inst,
			   काष्ठा mtk_vcodec_mem *bs_buf,
			   अचिन्हित पूर्णांक *bs_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक irq_status;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_encode(&inst->vpu_inst, H264_BS_MODE_SPS, शून्य,
			     bs_buf, bs_size, शून्य);
	अगर (ret)
		वापस ret;

	irq_status = h264_enc_रुको_venc_करोne(inst);
	अगर (irq_status != MTK_VENC_IRQ_STATUS_SPS) अणु
		mtk_vcodec_err(inst, "expect irq status %d",
			       MTK_VENC_IRQ_STATUS_SPS);
		वापस -EINVAL;
	पूर्ण

	*bs_size = h264_पढ़ो_reg(inst, VENC_PIC_BITSTREAM_BYTE_CNT);
	mtk_vcodec_debug(inst, "bs size %d <-", *bs_size);

	वापस ret;
पूर्ण

अटल पूर्णांक h264_encode_pps(काष्ठा venc_h264_inst *inst,
			   काष्ठा mtk_vcodec_mem *bs_buf,
			   अचिन्हित पूर्णांक *bs_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक irq_status;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_encode(&inst->vpu_inst, H264_BS_MODE_PPS, शून्य,
			     bs_buf, bs_size, शून्य);
	अगर (ret)
		वापस ret;

	irq_status = h264_enc_रुको_venc_करोne(inst);
	अगर (irq_status != MTK_VENC_IRQ_STATUS_PPS) अणु
		mtk_vcodec_err(inst, "expect irq status %d",
			       MTK_VENC_IRQ_STATUS_PPS);
		वापस -EINVAL;
	पूर्ण

	*bs_size = h264_पढ़ो_reg(inst, VENC_PIC_BITSTREAM_BYTE_CNT);
	mtk_vcodec_debug(inst, "bs size %d <-", *bs_size);

	वापस ret;
पूर्ण

अटल पूर्णांक h264_encode_header(काष्ठा venc_h264_inst *inst,
			      काष्ठा mtk_vcodec_mem *bs_buf,
			      अचिन्हित पूर्णांक *bs_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक bs_size_sps;
	अचिन्हित पूर्णांक bs_size_pps;

	ret = h264_encode_sps(inst, bs_buf, &bs_size_sps);
	अगर (ret)
		वापस ret;

	ret = h264_encode_pps(inst, &inst->pps_buf, &bs_size_pps);
	अगर (ret)
		वापस ret;

	स_नकल(bs_buf->va + bs_size_sps, inst->pps_buf.va, bs_size_pps);
	*bs_size = bs_size_sps + bs_size_pps;

	वापस ret;
पूर्ण

अटल पूर्णांक h264_encode_frame(काष्ठा venc_h264_inst *inst,
			     काष्ठा venc_frm_buf *frm_buf,
			     काष्ठा mtk_vcodec_mem *bs_buf,
			     अचिन्हित पूर्णांक *bs_size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक irq_status;
	काष्ठा venc_frame_info frame_info;

	mtk_vcodec_debug_enter(inst);
	mtk_vcodec_debug(inst, "frm_cnt = %d\n ", inst->frm_cnt);
	frame_info.frm_count = inst->frm_cnt;
	frame_info.skip_frm_count = inst->skip_frm_cnt;
	frame_info.frm_type = h264_frame_type(inst);
	mtk_vcodec_debug(inst, "frm_count = %d,skip_frm_count =%d,frm_type=%d.\n",
			 frame_info.frm_count, frame_info.skip_frm_count,
			 frame_info.frm_type);
	ret = vpu_enc_encode(&inst->vpu_inst, H264_BS_MODE_FRAME, frm_buf,
			     bs_buf, bs_size, &frame_info);
	अगर (ret)
		वापस ret;

	/*
	 * skip frame हाल: The skip frame buffer is composed by vpu side only,
	 * it करोes not trigger the hw, so skip the रुको पूर्णांकerrupt operation.
	 */
	अगर (inst->vpu_inst.state == VEN_IPI_MSG_ENC_STATE_SKIP) अणु
		*bs_size = inst->vpu_inst.bs_size;
		स_नकल(bs_buf->va,
		       inst->work_bufs[VENC_H264_VPU_WORK_BUF_SKIP_FRAME].va,
		       *bs_size);
		++inst->frm_cnt;
		++inst->skip_frm_cnt;
		वापस ret;
	पूर्ण

	irq_status = h264_enc_रुको_venc_करोne(inst);
	अगर (irq_status != MTK_VENC_IRQ_STATUS_FRM) अणु
		mtk_vcodec_err(inst, "irq_status=%d failed", irq_status);
		वापस -EIO;
	पूर्ण

	*bs_size = h264_पढ़ो_reg(inst, VENC_PIC_BITSTREAM_BYTE_CNT);

	++inst->frm_cnt;
	mtk_vcodec_debug(inst, "frm %d bs_size %d key_frm %d <-",
			 inst->frm_cnt, *bs_size, inst->vpu_inst.is_key_frm);

	वापस ret;
पूर्ण

अटल व्योम h264_encode_filler(काष्ठा venc_h264_inst *inst, व्योम *buf,
			       पूर्णांक size)
अणु
	अचिन्हित अक्षर *p = buf;

	अगर (size < H264_FILLER_MARKER_SIZE) अणु
		mtk_vcodec_err(inst, "filler size too small %d", size);
		वापस;
	पूर्ण

	स_नकल(p, h264_filler_marker, ARRAY_SIZE(h264_filler_marker));
	size -= H264_FILLER_MARKER_SIZE;
	p += H264_FILLER_MARKER_SIZE;
	स_रखो(p, 0xff, size);
पूर्ण

अटल पूर्णांक h264_enc_init(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	स्थिर bool is_ext = MTK_ENC_CTX_IS_EXT(ctx);
	पूर्णांक ret = 0;
	काष्ठा venc_h264_inst *inst;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	inst->ctx = ctx;
	inst->vpu_inst.ctx = ctx;
	inst->vpu_inst.id = is_ext ? SCP_IPI_VENC_H264 : IPI_VENC_H264;
	inst->hw_base = mtk_vcodec_get_reg_addr(inst->ctx, VENC_SYS);

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_init(&inst->vpu_inst);

	inst->vsi = (काष्ठा venc_h264_vsi *)inst->vpu_inst.vsi;

	mtk_vcodec_debug_leave(inst);

	अगर (ret)
		kमुक्त(inst);
	अन्यथा
		ctx->drv_handle = inst;

	वापस ret;
पूर्ण

अटल पूर्णांक h264_enc_encode(व्योम *handle,
			   क्रमागत venc_start_opt opt,
			   काष्ठा venc_frm_buf *frm_buf,
			   काष्ठा mtk_vcodec_mem *bs_buf,
			   काष्ठा venc_करोne_result *result)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_h264_inst *inst = (काष्ठा venc_h264_inst *)handle;
	काष्ठा mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_debug(inst, "opt %d ->", opt);

	enable_irq(ctx->dev->enc_irq);

	चयन (opt) अणु
	हाल VENC_START_OPT_ENCODE_SEQUENCE_HEADER: अणु
		अचिन्हित पूर्णांक bs_size_hdr;

		ret = h264_encode_header(inst, bs_buf, &bs_size_hdr);
		अगर (ret)
			जाओ encode_err;

		result->bs_size = bs_size_hdr;
		result->is_key_frm = false;
		अवरोध;
	पूर्ण

	हाल VENC_START_OPT_ENCODE_FRAME: अणु
		पूर्णांक hdr_sz;
		पूर्णांक hdr_sz_ext;
		पूर्णांक filler_sz = 0;
		स्थिर पूर्णांक bs_alignment = 128;
		काष्ठा mtk_vcodec_mem पंचांगp_bs_buf;
		अचिन्हित पूर्णांक bs_size_hdr;
		अचिन्हित पूर्णांक bs_size_frm;

		अगर (!inst->prepend_hdr) अणु
			ret = h264_encode_frame(inst, frm_buf, bs_buf,
						&result->bs_size);
			अगर (ret)
				जाओ encode_err;
			result->is_key_frm = inst->vpu_inst.is_key_frm;
			अवरोध;
		पूर्ण

		mtk_vcodec_debug(inst, "h264_encode_frame prepend SPS/PPS");

		ret = h264_encode_header(inst, bs_buf, &bs_size_hdr);
		अगर (ret)
			जाओ encode_err;

		hdr_sz = bs_size_hdr;
		hdr_sz_ext = (hdr_sz & (bs_alignment - 1));
		अगर (hdr_sz_ext) अणु
			filler_sz = bs_alignment - hdr_sz_ext;
			अगर (hdr_sz_ext + H264_FILLER_MARKER_SIZE > bs_alignment)
				filler_sz += bs_alignment;
			h264_encode_filler(inst, bs_buf->va + hdr_sz,
					   filler_sz);
		पूर्ण

		पंचांगp_bs_buf.va = bs_buf->va + hdr_sz + filler_sz;
		पंचांगp_bs_buf.dma_addr = bs_buf->dma_addr + hdr_sz + filler_sz;
		पंचांगp_bs_buf.size = bs_buf->size - (hdr_sz + filler_sz);

		ret = h264_encode_frame(inst, frm_buf, &पंचांगp_bs_buf,
					&bs_size_frm);
		अगर (ret)
			जाओ encode_err;

		result->bs_size = hdr_sz + filler_sz + bs_size_frm;

		mtk_vcodec_debug(inst, "hdr %d filler %d frame %d bs %d",
				 hdr_sz, filler_sz, bs_size_frm,
				 result->bs_size);

		inst->prepend_hdr = 0;
		result->is_key_frm = inst->vpu_inst.is_key_frm;
		अवरोध;
	पूर्ण

	शेष:
		mtk_vcodec_err(inst, "venc_start_opt %d not supported", opt);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

encode_err:

	disable_irq(ctx->dev->enc_irq);
	mtk_vcodec_debug(inst, "opt %d <-", opt);

	वापस ret;
पूर्ण

अटल पूर्णांक h264_enc_set_param(व्योम *handle,
			      क्रमागत venc_set_param_type type,
			      काष्ठा venc_enc_param *enc_prm)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_h264_inst *inst = (काष्ठा venc_h264_inst *)handle;

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
		inst->vsi->config.पूर्णांकra_period = enc_prm->पूर्णांकra_period;
		inst->vsi->config.profile =
			h264_get_profile(inst, enc_prm->h264_profile);
		inst->vsi->config.level =
			h264_get_level(inst, enc_prm->h264_level);
		inst->vsi->config.wfd = 0;
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		अगर (ret)
			अवरोध;
		अगर (inst->work_buf_allocated) अणु
			h264_enc_मुक्त_work_buf(inst);
			inst->work_buf_allocated = false;
		पूर्ण
		ret = h264_enc_alloc_work_buf(inst);
		अगर (ret)
			अवरोध;
		inst->work_buf_allocated = true;
		अवरोध;

	हाल VENC_SET_PARAM_PREPEND_HEADER:
		inst->prepend_hdr = 1;
		mtk_vcodec_debug(inst, "set prepend header mode");
		अवरोध;
	हाल VENC_SET_PARAM_FORCE_INTRA:
	हाल VENC_SET_PARAM_GOP_SIZE:
	हाल VENC_SET_PARAM_INTRA_PERIOD:
		inst->frm_cnt = 0;
		inst->skip_frm_cnt = 0;
		fallthrough;
	शेष:
		ret = vpu_enc_set_param(&inst->vpu_inst, type, enc_prm);
		अवरोध;
	पूर्ण

	mtk_vcodec_debug_leave(inst);

	वापस ret;
पूर्ण

अटल पूर्णांक h264_enc_deinit(व्योम *handle)
अणु
	पूर्णांक ret = 0;
	काष्ठा venc_h264_inst *inst = (काष्ठा venc_h264_inst *)handle;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_deinit(&inst->vpu_inst);

	अगर (inst->work_buf_allocated)
		h264_enc_मुक्त_work_buf(inst);

	mtk_vcodec_debug_leave(inst);
	kमुक्त(inst);

	वापस ret;
पूर्ण

स्थिर काष्ठा venc_common_अगर venc_h264_अगर = अणु
	.init = h264_enc_init,
	.encode = h264_enc_encode,
	.set_param = h264_enc_set_param,
	.deinit = h264_enc_deinit,
पूर्ण;
