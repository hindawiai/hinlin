<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#समावेश "mtk_mdp_core.h"
#समावेश "mtk_mdp_vpu.h"
#समावेश "mtk_vpu.h"


अटल अंतरभूत काष्ठा mtk_mdp_ctx *vpu_to_ctx(काष्ठा mtk_mdp_vpu *vpu)
अणु
	वापस container_of(vpu, काष्ठा mtk_mdp_ctx, vpu);
पूर्ण

अटल व्योम mtk_mdp_vpu_handle_init_ack(स्थिर काष्ठा mdp_ipi_comm_ack *msg)
अणु
	काष्ठा mtk_mdp_vpu *vpu = (काष्ठा mtk_mdp_vpu *)
					(अचिन्हित दीर्घ)msg->ap_inst;

	/* mapping VPU address to kernel भव address */
	vpu->vsi = (काष्ठा mdp_process_vsi *)
			vpu_mapping_dm_addr(vpu->pdev, msg->vpu_inst_addr);
	vpu->inst_addr = msg->vpu_inst_addr;
पूर्ण

अटल व्योम mtk_mdp_vpu_ipi_handler(स्थिर व्योम *data, अचिन्हित पूर्णांक len,
				    व्योम *priv)
अणु
	स्थिर काष्ठा mdp_ipi_comm_ack *msg = data;
	अचिन्हित पूर्णांक msg_id = msg->msg_id;
	काष्ठा mtk_mdp_vpu *vpu = (काष्ठा mtk_mdp_vpu *)
					(अचिन्हित दीर्घ)msg->ap_inst;
	काष्ठा mtk_mdp_ctx *ctx;

	vpu->failure = msg->status;
	अगर (!vpu->failure) अणु
		चयन (msg_id) अणु
		हाल VPU_MDP_INIT_ACK:
			mtk_mdp_vpu_handle_init_ack(data);
			अवरोध;
		हाल VPU_MDP_DEINIT_ACK:
		हाल VPU_MDP_PROCESS_ACK:
			अवरोध;
		शेष:
			ctx = vpu_to_ctx(vpu);
			dev_err(&ctx->mdp_dev->pdev->dev,
				"handle unknown ipi msg:0x%x\n",
				msg_id);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx = vpu_to_ctx(vpu);
		mtk_mdp_dbg(0, "[%d]:msg 0x%x, failure:%d", ctx->id,
			    msg_id, vpu->failure);
	पूर्ण
पूर्ण

पूर्णांक mtk_mdp_vpu_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_mdp_dev *mdp = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = vpu_ipi_रेजिस्टर(mdp->vpu_dev, IPI_MDP,
			       mtk_mdp_vpu_ipi_handler, "mdp_vpu", शून्य);
	अगर (err)
		dev_err(&mdp->pdev->dev,
			"vpu_ipi_registration fail status=%d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_mdp_vpu_send_msg(व्योम *msg, पूर्णांक len, काष्ठा mtk_mdp_vpu *vpu,
				पूर्णांक id)
अणु
	काष्ठा mtk_mdp_ctx *ctx = vpu_to_ctx(vpu);
	पूर्णांक err;

	अगर (!vpu->pdev) अणु
		mtk_mdp_dbg(1, "[%d]:vpu pdev is NULL", ctx->id);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&ctx->mdp_dev->vpulock);
	err = vpu_ipi_send(vpu->pdev, (क्रमागत ipi_id)id, msg, len);
	अगर (err)
		dev_err(&ctx->mdp_dev->pdev->dev,
			"vpu_ipi_send fail status %d\n", err);
	mutex_unlock(&ctx->mdp_dev->vpulock);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_mdp_vpu_send_ap_ipi(काष्ठा mtk_mdp_vpu *vpu, uपूर्णांक32_t msg_id)
अणु
	पूर्णांक err;
	काष्ठा mdp_ipi_comm msg;

	msg.msg_id = msg_id;
	msg.ipi_id = IPI_MDP;
	msg.vpu_inst_addr = vpu->inst_addr;
	msg.ap_inst = (अचिन्हित दीर्घ)vpu;
	err = mtk_mdp_vpu_send_msg((व्योम *)&msg, माप(msg), vpu, IPI_MDP);
	अगर (!err && vpu->failure)
		err = -EINVAL;

	वापस err;
पूर्ण

पूर्णांक mtk_mdp_vpu_init(काष्ठा mtk_mdp_vpu *vpu)
अणु
	पूर्णांक err;
	काष्ठा mdp_ipi_init msg;
	काष्ठा mtk_mdp_ctx *ctx = vpu_to_ctx(vpu);

	vpu->pdev = ctx->mdp_dev->vpu_dev;

	msg.msg_id = AP_MDP_INIT;
	msg.ipi_id = IPI_MDP;
	msg.ap_inst = (अचिन्हित दीर्घ)vpu;
	err = mtk_mdp_vpu_send_msg((व्योम *)&msg, माप(msg), vpu, IPI_MDP);
	अगर (!err && vpu->failure)
		err = -EINVAL;

	वापस err;
पूर्ण

पूर्णांक mtk_mdp_vpu_deinit(काष्ठा mtk_mdp_vpu *vpu)
अणु
	वापस mtk_mdp_vpu_send_ap_ipi(vpu, AP_MDP_DEINIT);
पूर्ण

पूर्णांक mtk_mdp_vpu_process(काष्ठा mtk_mdp_vpu *vpu)
अणु
	वापस mtk_mdp_vpu_send_ap_ipi(vpu, AP_MDP_PROCESS);
पूर्ण
