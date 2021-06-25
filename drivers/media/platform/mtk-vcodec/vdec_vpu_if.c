<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 */

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "vdec_ipi_msg.h"
#समावेश "vdec_vpu_if.h"
#समावेश "mtk_vcodec_fw.h"

अटल व्योम handle_init_ack_msg(स्थिर काष्ठा vdec_vpu_ipi_init_ack *msg)
अणु
	काष्ठा vdec_vpu_inst *vpu = (काष्ठा vdec_vpu_inst *)
					(अचिन्हित दीर्घ)msg->ap_inst_addr;

	mtk_vcodec_debug(vpu, "+ ap_inst_addr = 0x%llx", msg->ap_inst_addr);

	/* mapping VPU address to kernel भव address */
	/* the content in vsi is initialized to 0 in VPU */
	vpu->vsi = mtk_vcodec_fw_map_dm_addr(vpu->ctx->dev->fw_handler,
					     msg->vpu_inst_addr);
	vpu->inst_addr = msg->vpu_inst_addr;

	mtk_vcodec_debug(vpu, "- vpu_inst_addr = 0x%x", vpu->inst_addr);
पूर्ण

/*
 * vpu_dec_ipi_handler - Handler क्रम VPU ipi message.
 *
 * @data: ipi message
 * @len : length of ipi message
 * @priv: callback निजी data which is passed by decoder when रेजिस्टर.
 *
 * This function runs in पूर्णांकerrupt context and it means there's an IPI MSG
 * from VPU.
 */
अटल व्योम vpu_dec_ipi_handler(व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv)
अणु
	स्थिर काष्ठा vdec_vpu_ipi_ack *msg = data;
	काष्ठा vdec_vpu_inst *vpu = (काष्ठा vdec_vpu_inst *)
					(अचिन्हित दीर्घ)msg->ap_inst_addr;

	mtk_vcodec_debug(vpu, "+ id=%X", msg->msg_id);

	अगर (msg->status == 0) अणु
		चयन (msg->msg_id) अणु
		हाल VPU_IPIMSG_DEC_INIT_ACK:
			handle_init_ack_msg(data);
			अवरोध;

		हाल VPU_IPIMSG_DEC_START_ACK:
		हाल VPU_IPIMSG_DEC_END_ACK:
		हाल VPU_IPIMSG_DEC_DEINIT_ACK:
		हाल VPU_IPIMSG_DEC_RESET_ACK:
			अवरोध;

		शेष:
			mtk_vcodec_err(vpu, "invalid msg=%X", msg->msg_id);
			अवरोध;
		पूर्ण
	पूर्ण

	mtk_vcodec_debug(vpu, "- id=%X", msg->msg_id);
	vpu->failure = msg->status;
	vpu->संकेतed = 1;
पूर्ण

अटल पूर्णांक vcodec_vpu_send_msg(काष्ठा vdec_vpu_inst *vpu, व्योम *msg, पूर्णांक len)
अणु
	पूर्णांक err;

	mtk_vcodec_debug(vpu, "id=%X", *(uपूर्णांक32_t *)msg);

	vpu->failure = 0;
	vpu->संकेतed = 0;

	err = mtk_vcodec_fw_ipi_send(vpu->ctx->dev->fw_handler, vpu->id, msg,
				     len, 2000);
	अगर (err) अणु
		mtk_vcodec_err(vpu, "send fail vpu_id=%d msg_id=%X status=%d",
			       vpu->id, *(uपूर्णांक32_t *)msg, err);
		वापस err;
	पूर्ण

	वापस vpu->failure;
पूर्ण

अटल पूर्णांक vcodec_send_ap_ipi(काष्ठा vdec_vpu_inst *vpu, अचिन्हित पूर्णांक msg_id)
अणु
	काष्ठा vdec_ap_ipi_cmd msg;
	पूर्णांक err = 0;

	mtk_vcodec_debug(vpu, "+ id=%X", msg_id);

	स_रखो(&msg, 0, माप(msg));
	msg.msg_id = msg_id;
	msg.vpu_inst_addr = vpu->inst_addr;

	err = vcodec_vpu_send_msg(vpu, &msg, माप(msg));
	mtk_vcodec_debug(vpu, "- id=%X ret=%d", msg_id, err);
	वापस err;
पूर्ण

पूर्णांक vpu_dec_init(काष्ठा vdec_vpu_inst *vpu)
अणु
	काष्ठा vdec_ap_ipi_init msg;
	पूर्णांक err;

	mtk_vcodec_debug_enter(vpu);

	init_रुकोqueue_head(&vpu->wq);
	vpu->handler = vpu_dec_ipi_handler;

	err = mtk_vcodec_fw_ipi_रेजिस्टर(vpu->ctx->dev->fw_handler, vpu->id,
					 vpu->handler, "vdec", शून्य);
	अगर (err != 0) अणु
		mtk_vcodec_err(vpu, "vpu_ipi_register fail status=%d", err);
		वापस err;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.msg_id = AP_IPIMSG_DEC_INIT;
	msg.ap_inst_addr = (अचिन्हित दीर्घ)vpu;

	mtk_vcodec_debug(vpu, "vdec_inst=%p", vpu);

	err = vcodec_vpu_send_msg(vpu, (व्योम *)&msg, माप(msg));
	mtk_vcodec_debug(vpu, "- ret=%d", err);
	वापस err;
पूर्ण

पूर्णांक vpu_dec_start(काष्ठा vdec_vpu_inst *vpu, uपूर्णांक32_t *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vdec_ap_ipi_dec_start msg;
	पूर्णांक i;
	पूर्णांक err = 0;

	mtk_vcodec_debug_enter(vpu);

	अगर (len > ARRAY_SIZE(msg.data)) अणु
		mtk_vcodec_err(vpu, "invalid len = %d\n", len);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.msg_id = AP_IPIMSG_DEC_START;
	msg.vpu_inst_addr = vpu->inst_addr;

	क्रम (i = 0; i < len; i++)
		msg.data[i] = data[i];

	err = vcodec_vpu_send_msg(vpu, (व्योम *)&msg, माप(msg));
	mtk_vcodec_debug(vpu, "- ret=%d", err);
	वापस err;
पूर्ण

पूर्णांक vpu_dec_end(काष्ठा vdec_vpu_inst *vpu)
अणु
	वापस vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_END);
पूर्ण

पूर्णांक vpu_dec_deinit(काष्ठा vdec_vpu_inst *vpu)
अणु
	वापस vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_DEINIT);
पूर्ण

पूर्णांक vpu_dec_reset(काष्ठा vdec_vpu_inst *vpu)
अणु
	वापस vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_RESET);
पूर्ण
