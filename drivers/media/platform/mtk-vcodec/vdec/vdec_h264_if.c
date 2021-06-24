<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "../vdec_drv_if.h"
#समावेश "../mtk_vcodec_util.h"
#समावेश "../mtk_vcodec_dec.h"
#समावेश "../mtk_vcodec_intr.h"
#समावेश "../vdec_vpu_if.h"
#समावेश "../vdec_drv_base.h"

#घोषणा NAL_NON_IDR_SLICE			0x01
#घोषणा NAL_IDR_SLICE				0x05
#घोषणा NAL_H264_PPS				0x08
#घोषणा NAL_TYPE(value)				((value) & 0x1F)

#घोषणा BUF_PREDICTION_SZ			(32 * 1024)

#घोषणा MB_UNIT_LEN				16

/* motion vector size (bytes) क्रम every macro block */
#घोषणा HW_MB_STORE_SZ				64

#घोषणा H264_MAX_FB_NUM				17
#घोषणा HDR_PARSING_BUF_SZ			1024

#घोषणा DEC_ERR_RET(ret)			((ret) >> 16)
#घोषणा H264_ERR_NOT_VALID			3

/**
 * काष्ठा h264_fb - h264 decode frame buffer inक्रमmation
 * @vdec_fb_va  : भव address of काष्ठा vdec_fb
 * @y_fb_dma    : dma address of Y frame buffer (luma)
 * @c_fb_dma    : dma address of C frame buffer (chroma)
 * @poc         : picture order count of frame buffer
 * @reserved    : क्रम 8 bytes alignment
 */
काष्ठा h264_fb अणु
	uपूर्णांक64_t vdec_fb_va;
	uपूर्णांक64_t y_fb_dma;
	uपूर्णांक64_t c_fb_dma;
	पूर्णांक32_t poc;
	uपूर्णांक32_t reserved;
पूर्ण;

/**
 * काष्ठा h264_ring_fb_list - ring frame buffer list
 * @fb_list   : frame buffer array
 * @पढ़ो_idx  : पढ़ो index
 * @ग_लिखो_idx : ग_लिखो index
 * @count     : buffer count in list
 * @reserved  : क्रम 8 bytes alignment
 */
काष्ठा h264_ring_fb_list अणु
	काष्ठा h264_fb fb_list[H264_MAX_FB_NUM];
	अचिन्हित पूर्णांक पढ़ो_idx;
	अचिन्हित पूर्णांक ग_लिखो_idx;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

/**
 * काष्ठा vdec_h264_dec_info - decode inक्रमmation
 * @dpb_sz		: decoding picture buffer size
 * @resolution_changed  : resolution change happen
 * @पुनः_स्मृति_mv_buf	: flag to notअगरy driver to re-allocate mv buffer
 * @reserved		: क्रम 8 bytes alignment
 * @bs_dma		: Input bit-stream buffer dma address
 * @y_fb_dma		: Y frame buffer dma address
 * @c_fb_dma		: C frame buffer dma address
 * @vdec_fb_va		: VDEC frame buffer काष्ठा भव address
 */
काष्ठा vdec_h264_dec_info अणु
	uपूर्णांक32_t dpb_sz;
	uपूर्णांक32_t resolution_changed;
	uपूर्णांक32_t पुनः_स्मृति_mv_buf;
	uपूर्णांक32_t reserved;
	uपूर्णांक64_t bs_dma;
	uपूर्णांक64_t y_fb_dma;
	uपूर्णांक64_t c_fb_dma;
	uपूर्णांक64_t vdec_fb_va;
पूर्ण;

/**
 * काष्ठा vdec_h264_vsi - shared memory क्रम decode inक्रमmation exchange
 *                        between VPU and Host.
 *                        The memory is allocated by VPU then mapping to Host
 *                        in vpu_dec_init() and मुक्तd in vpu_dec_deinit()
 *                        by VPU.
 *                        AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *                        VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @hdr_buf      : Header parsing buffer (AP-W, VPU-R)
 * @pred_buf_dma : HW working predication buffer dma address (AP-W, VPU-R)
 * @mv_buf_dma   : HW working motion vector buffer dma address (AP-W, VPU-R)
 * @list_मुक्त    : मुक्त frame buffer ring list (AP-W/R, VPU-W)
 * @list_disp    : display frame buffer ring list (AP-R, VPU-W)
 * @dec          : decode inक्रमmation (AP-R, VPU-W)
 * @pic          : picture inक्रमmation (AP-R, VPU-W)
 * @crop         : crop inक्रमmation (AP-R, VPU-W)
 */
काष्ठा vdec_h264_vsi अणु
	अचिन्हित अक्षर hdr_buf[HDR_PARSING_BUF_SZ];
	uपूर्णांक64_t pred_buf_dma;
	uपूर्णांक64_t mv_buf_dma[H264_MAX_FB_NUM];
	काष्ठा h264_ring_fb_list list_मुक्त;
	काष्ठा h264_ring_fb_list list_disp;
	काष्ठा vdec_h264_dec_info dec;
	काष्ठा vdec_pic_info pic;
	काष्ठा v4l2_rect crop;
पूर्ण;

/**
 * काष्ठा vdec_h264_inst - h264 decoder instance
 * @num_nalu : how many nalus be decoded
 * @ctx      : poपूर्णांक to mtk_vcodec_ctx
 * @pred_buf : HW working predication buffer
 * @mv_buf   : HW working motion vector buffer
 * @vpu      : VPU instance
 * @vsi      : VPU shared inक्रमmation
 */
काष्ठा vdec_h264_inst अणु
	अचिन्हित पूर्णांक num_nalu;
	काष्ठा mtk_vcodec_ctx *ctx;
	काष्ठा mtk_vcodec_mem pred_buf;
	काष्ठा mtk_vcodec_mem mv_buf[H264_MAX_FB_NUM];
	काष्ठा vdec_vpu_inst vpu;
	काष्ठा vdec_h264_vsi *vsi;
पूर्ण;

अटल अचिन्हित पूर्णांक get_mv_buf_size(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	वापस HW_MB_STORE_SZ * (width/MB_UNIT_LEN) * (height/MB_UNIT_LEN);
पूर्ण

अटल पूर्णांक allocate_predication_buf(काष्ठा vdec_h264_inst *inst)
अणु
	पूर्णांक err = 0;

	inst->pred_buf.size = BUF_PREDICTION_SZ;
	err = mtk_vcodec_mem_alloc(inst->ctx, &inst->pred_buf);
	अगर (err) अणु
		mtk_vcodec_err(inst, "failed to allocate ppl buf");
		वापस err;
	पूर्ण

	inst->vsi->pred_buf_dma = inst->pred_buf.dma_addr;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_predication_buf(काष्ठा vdec_h264_inst *inst)
अणु
	काष्ठा mtk_vcodec_mem *mem = शून्य;

	mtk_vcodec_debug_enter(inst);

	inst->vsi->pred_buf_dma = 0;
	mem = &inst->pred_buf;
	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);
पूर्ण

अटल पूर्णांक alloc_mv_buf(काष्ठा vdec_h264_inst *inst, काष्ठा vdec_pic_info *pic)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा mtk_vcodec_mem *mem = शून्य;
	अचिन्हित पूर्णांक buf_sz = get_mv_buf_size(pic->buf_w, pic->buf_h);

	क्रम (i = 0; i < H264_MAX_FB_NUM; i++) अणु
		mem = &inst->mv_buf[i];
		अगर (mem->va)
			mtk_vcodec_mem_मुक्त(inst->ctx, mem);
		mem->size = buf_sz;
		err = mtk_vcodec_mem_alloc(inst->ctx, mem);
		अगर (err) अणु
			mtk_vcodec_err(inst, "failed to allocate mv buf");
			वापस err;
		पूर्ण
		inst->vsi->mv_buf_dma[i] = mem->dma_addr;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mv_buf(काष्ठा vdec_h264_inst *inst)
अणु
	पूर्णांक i;
	काष्ठा mtk_vcodec_mem *mem = शून्य;

	क्रम (i = 0; i < H264_MAX_FB_NUM; i++) अणु
		inst->vsi->mv_buf_dma[i] = 0;
		mem = &inst->mv_buf[i];
		अगर (mem->va)
			mtk_vcodec_mem_मुक्त(inst->ctx, mem);
	पूर्ण
पूर्ण

अटल पूर्णांक check_list_validity(काष्ठा vdec_h264_inst *inst, bool disp_list)
अणु
	काष्ठा h264_ring_fb_list *list;

	list = disp_list ? &inst->vsi->list_disp : &inst->vsi->list_मुक्त;

	अगर (list->count > H264_MAX_FB_NUM ||
	    list->पढ़ो_idx >= H264_MAX_FB_NUM ||
	    list->ग_लिखो_idx >= H264_MAX_FB_NUM) अणु
		mtk_vcodec_err(inst, "%s list err: cnt=%d r_idx=%d w_idx=%d",
			       disp_list ? "disp" : "free", list->count,
			       list->पढ़ो_idx, list->ग_लिखो_idx);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम put_fb_to_मुक्त(काष्ठा vdec_h264_inst *inst, काष्ठा vdec_fb *fb)
अणु
	काष्ठा h264_ring_fb_list *list;

	अगर (fb) अणु
		अगर (check_list_validity(inst, false))
			वापस;

		list = &inst->vsi->list_मुक्त;
		अगर (list->count == H264_MAX_FB_NUM) अणु
			mtk_vcodec_err(inst, "[FB] put fb free_list full");
			वापस;
		पूर्ण

		mtk_vcodec_debug(inst, "[FB] put fb into free_list @(%p, %llx)",
				 fb->base_y.va, (u64)fb->base_y.dma_addr);

		list->fb_list[list->ग_लिखो_idx].vdec_fb_va = (u64)(uपूर्णांकptr_t)fb;
		list->ग_लिखो_idx = (list->ग_लिखो_idx == H264_MAX_FB_NUM - 1) ?
				  0 : list->ग_लिखो_idx + 1;
		list->count++;
	पूर्ण
पूर्ण

अटल व्योम get_pic_info(काष्ठा vdec_h264_inst *inst,
			 काष्ठा vdec_pic_info *pic)
अणु
	*pic = inst->vsi->pic;
	mtk_vcodec_debug(inst, "pic(%d, %d), buf(%d, %d)",
			 pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vcodec_debug(inst, "fb size: Y(%d), C(%d)",
			 pic->fb_sz[0], pic->fb_sz[1]);
पूर्ण

अटल व्योम get_crop_info(काष्ठा vdec_h264_inst *inst, काष्ठा v4l2_rect *cr)
अणु
	cr->left = inst->vsi->crop.left;
	cr->top = inst->vsi->crop.top;
	cr->width = inst->vsi->crop.width;
	cr->height = inst->vsi->crop.height;

	mtk_vcodec_debug(inst, "l=%d, t=%d, w=%d, h=%d",
			 cr->left, cr->top, cr->width, cr->height);
पूर्ण

अटल व्योम get_dpb_size(काष्ठा vdec_h264_inst *inst, अचिन्हित पूर्णांक *dpb_sz)
अणु
	*dpb_sz = inst->vsi->dec.dpb_sz;
	mtk_vcodec_debug(inst, "sz=%d", *dpb_sz);
पूर्ण

अटल पूर्णांक vdec_h264_init(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vdec_h264_inst *inst = शून्य;
	पूर्णांक err;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_H264;
	inst->vpu.ctx = ctx;

	err = vpu_dec_init(&inst->vpu);
	अगर (err) अणु
		mtk_vcodec_err(inst, "vdec_h264 init err=%d", err);
		जाओ error_मुक्त_inst;
	पूर्ण

	inst->vsi = (काष्ठा vdec_h264_vsi *)inst->vpu.vsi;
	err = allocate_predication_buf(inst);
	अगर (err)
		जाओ error_deinit;

	mtk_vcodec_debug(inst, "H264 Instance >> %p", inst);

	ctx->drv_handle = inst;
	वापस 0;

error_deinit:
	vpu_dec_deinit(&inst->vpu);

error_मुक्त_inst:
	kमुक्त(inst);
	वापस err;
पूर्ण

अटल व्योम vdec_h264_deinit(व्योम *h_vdec)
अणु
	काष्ठा vdec_h264_inst *inst = (काष्ठा vdec_h264_inst *)h_vdec;

	mtk_vcodec_debug_enter(inst);

	vpu_dec_deinit(&inst->vpu);
	मुक्त_predication_buf(inst);
	मुक्त_mv_buf(inst);

	kमुक्त(inst);
पूर्ण

अटल पूर्णांक find_start_code(अचिन्हित अक्षर *data, अचिन्हित पूर्णांक data_sz)
अणु
	अगर (data_sz > 3 && data[0] == 0 && data[1] == 0 && data[2] == 1)
		वापस 3;

	अगर (data_sz > 4 && data[0] == 0 && data[1] == 0 && data[2] == 0 &&
	    data[3] == 1)
		वापस 4;

	वापस -1;
पूर्ण

अटल पूर्णांक vdec_h264_decode(व्योम *h_vdec, काष्ठा mtk_vcodec_mem *bs,
			    काष्ठा vdec_fb *fb, bool *res_chg)
अणु
	काष्ठा vdec_h264_inst *inst = (काष्ठा vdec_h264_inst *)h_vdec;
	काष्ठा vdec_vpu_inst *vpu = &inst->vpu;
	पूर्णांक nal_start_idx = 0;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक nal_start;
	अचिन्हित पूर्णांक nal_type;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक buf_sz;
	अचिन्हित पूर्णांक data[2];
	uपूर्णांक64_t vdec_fb_va = (u64)(uपूर्णांकptr_t)fb;
	uपूर्णांक64_t y_fb_dma = fb ? (u64)fb->base_y.dma_addr : 0;
	uपूर्णांक64_t c_fb_dma = fb ? (u64)fb->base_c.dma_addr : 0;

	mtk_vcodec_debug(inst, "+ [%d] FB y_dma=%llx c_dma=%llx va=%p",
			 ++inst->num_nalu, y_fb_dma, c_fb_dma, fb);

	/* bs शून्य means flush decoder */
	अगर (bs == शून्य)
		वापस vpu_dec_reset(vpu);

	buf = (अचिन्हित अक्षर *)bs->va;
	buf_sz = bs->size;
	nal_start_idx = find_start_code(buf, buf_sz);
	अगर (nal_start_idx < 0) अणु
		mtk_vcodec_err(inst, "invalid nal start code");
		err = -EIO;
		जाओ err_मुक्त_fb_out;
	पूर्ण

	nal_start = buf[nal_start_idx];
	nal_type = NAL_TYPE(buf[nal_start_idx]);
	mtk_vcodec_debug(inst, "\n + NALU[%d] type %d +\n", inst->num_nalu,
			 nal_type);

	अगर (nal_type == NAL_H264_PPS) अणु
		buf_sz -= nal_start_idx;
		अगर (buf_sz > HDR_PARSING_BUF_SZ) अणु
			err = -EILSEQ;
			जाओ err_मुक्त_fb_out;
		पूर्ण
		स_नकल(inst->vsi->hdr_buf, buf + nal_start_idx, buf_sz);
	पूर्ण

	inst->vsi->dec.bs_dma = (uपूर्णांक64_t)bs->dma_addr;
	inst->vsi->dec.y_fb_dma = y_fb_dma;
	inst->vsi->dec.c_fb_dma = c_fb_dma;
	inst->vsi->dec.vdec_fb_va = vdec_fb_va;

	data[0] = buf_sz;
	data[1] = nal_start;
	err = vpu_dec_start(vpu, data, 2);
	अगर (err) अणु
		अगर (err > 0 && (DEC_ERR_RET(err) == H264_ERR_NOT_VALID)) अणु
			mtk_vcodec_err(inst, "- error bitstream - err = %d -",
				       err);
			err = -EIO;
		पूर्ण
		जाओ err_मुक्त_fb_out;
	पूर्ण

	*res_chg = inst->vsi->dec.resolution_changed;
	अगर (*res_chg) अणु
		काष्ठा vdec_pic_info pic;

		mtk_vcodec_debug(inst, "- resolution changed -");
		get_pic_info(inst, &pic);

		अगर (inst->vsi->dec.पुनः_स्मृति_mv_buf) अणु
			err = alloc_mv_buf(inst, &pic);
			अगर (err)
				जाओ err_मुक्त_fb_out;
		पूर्ण
	पूर्ण

	अगर (nal_type == NAL_NON_IDR_SLICE || nal_type == NAL_IDR_SLICE) अणु
		/* रुको decoder करोne पूर्णांकerrupt */
		err = mtk_vcodec_रुको_क्रम_करोne_ctx(inst->ctx,
						   MTK_INST_IRQ_RECEIVED,
						   WAIT_INTR_TIMEOUT_MS);
		अगर (err)
			जाओ err_मुक्त_fb_out;

		vpu_dec_end(vpu);
	पूर्ण

	mtk_vcodec_debug(inst, "\n - NALU[%d] type=%d -\n", inst->num_nalu,
			 nal_type);
	वापस 0;

err_मुक्त_fb_out:
	put_fb_to_मुक्त(inst, fb);
	mtk_vcodec_err(inst, "\n - NALU[%d] err=%d -\n", inst->num_nalu, err);
	वापस err;
पूर्ण

अटल व्योम vdec_h264_get_fb(काष्ठा vdec_h264_inst *inst,
			     काष्ठा h264_ring_fb_list *list,
			     bool disp_list, काष्ठा vdec_fb **out_fb)
अणु
	काष्ठा vdec_fb *fb;

	अगर (check_list_validity(inst, disp_list))
		वापस;

	अगर (list->count == 0) अणु
		mtk_vcodec_debug(inst, "[FB] there is no %s fb",
				 disp_list ? "disp" : "free");
		*out_fb = शून्य;
		वापस;
	पूर्ण

	fb = (काष्ठा vdec_fb *)
		(uपूर्णांकptr_t)list->fb_list[list->पढ़ो_idx].vdec_fb_va;
	fb->status |= (disp_list ? FB_ST_DISPLAY : FB_ST_FREE);

	*out_fb = fb;
	mtk_vcodec_debug(inst, "[FB] get %s fb st=%d poc=%d %llx",
			 disp_list ? "disp" : "free",
			 fb->status, list->fb_list[list->पढ़ो_idx].poc,
			 list->fb_list[list->पढ़ो_idx].vdec_fb_va);

	list->पढ़ो_idx = (list->पढ़ो_idx == H264_MAX_FB_NUM - 1) ?
			 0 : list->पढ़ो_idx + 1;
	list->count--;
पूर्ण

अटल पूर्णांक vdec_h264_get_param(व्योम *h_vdec, क्रमागत vdec_get_param_type type,
			       व्योम *out)
अणु
	काष्ठा vdec_h264_inst *inst = (काष्ठा vdec_h264_inst *)h_vdec;

	चयन (type) अणु
	हाल GET_PARAM_DISP_FRAME_BUFFER:
		vdec_h264_get_fb(inst, &inst->vsi->list_disp, true, out);
		अवरोध;

	हाल GET_PARAM_FREE_FRAME_BUFFER:
		vdec_h264_get_fb(inst, &inst->vsi->list_मुक्त, false, out);
		अवरोध;

	हाल GET_PARAM_PIC_INFO:
		get_pic_info(inst, out);
		अवरोध;

	हाल GET_PARAM_DPB_SIZE:
		get_dpb_size(inst, out);
		अवरोध;

	हाल GET_PARAM_CROP_INFO:
		get_crop_info(inst, out);
		अवरोध;

	शेष:
		mtk_vcodec_err(inst, "invalid get parameter type=%d", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा vdec_common_अगर vdec_h264_अगर = अणु
	.init		= vdec_h264_init,
	.decode		= vdec_h264_decode,
	.get_param	= vdec_h264_get_param,
	.deinit		= vdec_h264_deinit,
पूर्ण;
