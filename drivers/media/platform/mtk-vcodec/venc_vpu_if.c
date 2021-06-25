<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PoChun Lin <pochun.lin@mediatek.com>
 */

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_fw.h"
#समावेश "venc_ipi_msg.h"
#समावेश "venc_vpu_if.h"

अटल व्योम handle_enc_init_msg(काष्ठा venc_vpu_inst *vpu, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा venc_vpu_ipi_msg_init *msg = data;

	vpu->inst_addr = msg->vpu_inst_addr;
	vpu->vsi = mtk_vcodec_fw_map_dm_addr(vpu->ctx->dev->fw_handler,
					     msg->vpu_inst_addr);

	/* Firmware version field value is unspecअगरied on MT8173. */
	अगर (vpu->ctx->dev->venc_pdata->chip == MTK_MT8173)
		वापस;

	/* Check firmware version. */
	mtk_vcodec_debug(vpu, "firmware version: 0x%x\n",
			 msg->venc_abi_version);
	चयन (msg->venc_abi_version) अणु
	हाल 1:
		अवरोध;
	शेष:
		mtk_vcodec_err(vpu, "unhandled firmware version 0x%x\n",
			       msg->venc_abi_version);
		vpu->failure = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_enc_encode_msg(काष्ठा venc_vpu_inst *vpu, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा venc_vpu_ipi_msg_enc *msg = data;

	vpu->state = msg->state;
	vpu->bs_size = msg->bs_size;
	vpu->is_key_frm = msg->is_key_frm;
पूर्ण

अटल व्योम vpu_enc_ipi_handler(व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv)
अणु
	स्थिर काष्ठा venc_vpu_ipi_msg_common *msg = data;
	काष्ठा venc_vpu_inst *vpu =
		(काष्ठा venc_vpu_inst *)(अचिन्हित दीर्घ)msg->venc_inst;

	mtk_vcodec_debug(vpu, "msg_id %x inst %p status %d",
			 msg->msg_id, vpu, msg->status);

	vpu->संकेतed = 1;
	vpu->failure = (msg->status != VENC_IPI_MSG_STATUS_OK);
	अगर (vpu->failure)
		जाओ failure;

	चयन (msg->msg_id) अणु
	हाल VPU_IPIMSG_ENC_INIT_DONE:
		handle_enc_init_msg(vpu, data);
		अवरोध;
	हाल VPU_IPIMSG_ENC_SET_PARAM_DONE:
		अवरोध;
	हाल VPU_IPIMSG_ENC_ENCODE_DONE:
		handle_enc_encode_msg(vpu, data);
		अवरोध;
	हाल VPU_IPIMSG_ENC_DEINIT_DONE:
		अवरोध;
	शेष:
		mtk_vcodec_err(vpu, "unknown msg id %x", msg->msg_id);
		अवरोध;
	पूर्ण

failure:
	mtk_vcodec_debug_leave(vpu);
पूर्ण

अटल पूर्णांक vpu_enc_send_msg(काष्ठा venc_vpu_inst *vpu, व्योम *msg,
			    पूर्णांक len)
अणु
	पूर्णांक status;

	mtk_vcodec_debug_enter(vpu);

	अगर (!vpu->ctx->dev->fw_handler) अणु
		mtk_vcodec_err(vpu, "inst dev is NULL");
		वापस -EINVAL;
	पूर्ण

	status = mtk_vcodec_fw_ipi_send(vpu->ctx->dev->fw_handler, vpu->id, msg,
					len, 2000);
	अगर (status) अणु
		mtk_vcodec_err(vpu, "vpu_ipi_send msg_id %x len %d fail %d",
			       *(uपूर्णांक32_t *)msg, len, status);
		वापस -EINVAL;
	पूर्ण
	अगर (vpu->failure)
		वापस -EINVAL;

	mtk_vcodec_debug_leave(vpu);

	वापस 0;
पूर्ण

पूर्णांक vpu_enc_init(काष्ठा venc_vpu_inst *vpu)
अणु
	पूर्णांक status;
	काष्ठा venc_ap_ipi_msg_init out;

	mtk_vcodec_debug_enter(vpu);

	init_रुकोqueue_head(&vpu->wq_hd);
	vpu->संकेतed = 0;
	vpu->failure = 0;

	status = mtk_vcodec_fw_ipi_रेजिस्टर(vpu->ctx->dev->fw_handler, vpu->id,
					    vpu_enc_ipi_handler, "venc", शून्य);

	अगर (status) अणु
		mtk_vcodec_err(vpu, "vpu_ipi_register fail %d", status);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&out, 0, माप(out));
	out.msg_id = AP_IPIMSG_ENC_INIT;
	out.venc_inst = (अचिन्हित दीर्घ)vpu;
	अगर (vpu_enc_send_msg(vpu, &out, माप(out))) अणु
		mtk_vcodec_err(vpu, "AP_IPIMSG_ENC_INIT fail");
		वापस -EINVAL;
	पूर्ण

	mtk_vcodec_debug_leave(vpu);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक venc_enc_param_crop_right(काष्ठा venc_vpu_inst *vpu,
					      काष्ठा venc_enc_param *enc_prm)
अणु
	अचिन्हित पूर्णांक img_crop_right = enc_prm->buf_width - enc_prm->width;

	वापस img_crop_right % 16;
पूर्ण

अटल अचिन्हित पूर्णांक venc_enc_param_crop_bottom(काष्ठा venc_enc_param *enc_prm)
अणु
	वापस round_up(enc_prm->height, 16) - enc_prm->height;
पूर्ण

अटल अचिन्हित पूर्णांक venc_enc_param_num_mb(काष्ठा venc_enc_param *enc_prm)
अणु
	वापस DIV_ROUND_UP(enc_prm->width, 16) *
	       DIV_ROUND_UP(enc_prm->height, 16);
पूर्ण

पूर्णांक vpu_enc_set_param(काष्ठा venc_vpu_inst *vpu,
		      क्रमागत venc_set_param_type id,
		      काष्ठा venc_enc_param *enc_param)
अणु
	स्थिर bool is_ext = MTK_ENC_CTX_IS_EXT(vpu->ctx);
	माप_प्रकार msg_size = is_ext ?
		माप(काष्ठा venc_ap_ipi_msg_set_param_ext) :
		माप(काष्ठा venc_ap_ipi_msg_set_param);
	काष्ठा venc_ap_ipi_msg_set_param_ext out;

	mtk_vcodec_debug(vpu, "id %d ->", id);

	स_रखो(&out, 0, माप(out));
	out.base.msg_id = AP_IPIMSG_ENC_SET_PARAM;
	out.base.vpu_inst_addr = vpu->inst_addr;
	out.base.param_id = id;
	चयन (id) अणु
	हाल VENC_SET_PARAM_ENC:
		अगर (is_ext) अणु
			out.base.data_item = 3;
			out.base.data[0] =
				venc_enc_param_crop_right(vpu, enc_param);
			out.base.data[1] =
				venc_enc_param_crop_bottom(enc_param);
			out.base.data[2] = venc_enc_param_num_mb(enc_param);
		पूर्ण अन्यथा अणु
			out.base.data_item = 0;
		पूर्ण
		अवरोध;
	हाल VENC_SET_PARAM_FORCE_INTRA:
		out.base.data_item = 0;
		अवरोध;
	हाल VENC_SET_PARAM_ADJUST_BITRATE:
		out.base.data_item = 1;
		out.base.data[0] = enc_param->bitrate;
		अवरोध;
	हाल VENC_SET_PARAM_ADJUST_FRAMERATE:
		out.base.data_item = 1;
		out.base.data[0] = enc_param->frm_rate;
		अवरोध;
	हाल VENC_SET_PARAM_GOP_SIZE:
		out.base.data_item = 1;
		out.base.data[0] = enc_param->gop_size;
		अवरोध;
	हाल VENC_SET_PARAM_INTRA_PERIOD:
		out.base.data_item = 1;
		out.base.data[0] = enc_param->पूर्णांकra_period;
		अवरोध;
	हाल VENC_SET_PARAM_SKIP_FRAME:
		out.base.data_item = 0;
		अवरोध;
	शेष:
		mtk_vcodec_err(vpu, "id %d not supported", id);
		वापस -EINVAL;
	पूर्ण
	अगर (vpu_enc_send_msg(vpu, &out, msg_size)) अणु
		mtk_vcodec_err(vpu,
			       "AP_IPIMSG_ENC_SET_PARAM %d fail", id);
		वापस -EINVAL;
	पूर्ण

	mtk_vcodec_debug(vpu, "id %d <-", id);

	वापस 0;
पूर्ण

पूर्णांक vpu_enc_encode(काष्ठा venc_vpu_inst *vpu, अचिन्हित पूर्णांक bs_mode,
		   काष्ठा venc_frm_buf *frm_buf,
		   काष्ठा mtk_vcodec_mem *bs_buf,
		   अचिन्हित पूर्णांक *bs_size,
		   काष्ठा venc_frame_info *frame_info)
अणु
	स्थिर bool is_ext = MTK_ENC_CTX_IS_EXT(vpu->ctx);
	माप_प्रकार msg_size = is_ext ?
		माप(काष्ठा venc_ap_ipi_msg_enc_ext) :
		माप(काष्ठा venc_ap_ipi_msg_enc);
	काष्ठा venc_ap_ipi_msg_enc_ext out;

	mtk_vcodec_debug(vpu, "bs_mode %d ->", bs_mode);

	स_रखो(&out, 0, माप(out));
	out.base.msg_id = AP_IPIMSG_ENC_ENCODE;
	out.base.vpu_inst_addr = vpu->inst_addr;
	out.base.bs_mode = bs_mode;
	अगर (frm_buf) अणु
		अगर ((frm_buf->fb_addr[0].dma_addr % 16 == 0) &&
		    (frm_buf->fb_addr[1].dma_addr % 16 == 0) &&
		    (frm_buf->fb_addr[2].dma_addr % 16 == 0)) अणु
			out.base.input_addr[0] = frm_buf->fb_addr[0].dma_addr;
			out.base.input_addr[1] = frm_buf->fb_addr[1].dma_addr;
			out.base.input_addr[2] = frm_buf->fb_addr[2].dma_addr;
		पूर्ण अन्यथा अणु
			mtk_vcodec_err(vpu, "dma_addr not align to 16");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (bs_buf) अणु
		out.base.bs_addr = bs_buf->dma_addr;
		out.base.bs_size = bs_buf->size;
	पूर्ण
	अगर (is_ext && frame_info) अणु
		out.data_item = 3;
		out.data[0] = frame_info->frm_count;
		out.data[1] = frame_info->skip_frm_count;
		out.data[2] = frame_info->frm_type;
	पूर्ण
	अगर (vpu_enc_send_msg(vpu, &out, msg_size)) अणु
		mtk_vcodec_err(vpu, "AP_IPIMSG_ENC_ENCODE %d fail",
			       bs_mode);
		वापस -EINVAL;
	पूर्ण

	mtk_vcodec_debug(vpu, "bs_mode %d state %d size %d key_frm %d <-",
			 bs_mode, vpu->state, vpu->bs_size, vpu->is_key_frm);

	वापस 0;
पूर्ण

पूर्णांक vpu_enc_deinit(काष्ठा venc_vpu_inst *vpu)
अणु
	काष्ठा venc_ap_ipi_msg_deinit out;

	mtk_vcodec_debug_enter(vpu);

	स_रखो(&out, 0, माप(out));
	out.msg_id = AP_IPIMSG_ENC_DEINIT;
	out.vpu_inst_addr = vpu->inst_addr;
	अगर (vpu_enc_send_msg(vpu, &out, माप(out))) अणु
		mtk_vcodec_err(vpu, "AP_IPIMSG_ENC_DEINIT fail");
		वापस -EINVAL;
	पूर्ण

	mtk_vcodec_debug_leave(vpu);

	वापस 0;
पूर्ण
