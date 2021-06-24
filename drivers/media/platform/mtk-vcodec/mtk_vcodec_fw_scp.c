<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "mtk_vcodec_fw_priv.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "mtk_vcodec_drv.h"

अटल पूर्णांक mtk_vcodec_scp_load_firmware(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस rproc_boot(scp_get_rproc(fw->scp));
पूर्ण

अटल अचिन्हित पूर्णांक mtk_vcodec_scp_get_vdec_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस scp_get_vdec_hw_capa(fw->scp);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_vcodec_scp_get_venc_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस scp_get_venc_hw_capa(fw->scp);
पूर्ण

अटल व्योम *mtk_vcodec_vpu_scp_dm_addr(काष्ठा mtk_vcodec_fw *fw,
					u32 dtcm_dmem_addr)
अणु
	वापस scp_mapping_dm_addr(fw->scp, dtcm_dmem_addr);
पूर्ण

अटल पूर्णांक mtk_vcodec_scp_set_ipi_रेजिस्टर(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
					   mtk_vcodec_ipi_handler handler,
					   स्थिर अक्षर *name, व्योम *priv)
अणु
	वापस scp_ipi_रेजिस्टर(fw->scp, id, handler, priv);
पूर्ण

अटल पूर्णांक mtk_vcodec_scp_ipi_send(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id, व्योम *buf,
				   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको)
अणु
	वापस scp_ipi_send(fw->scp, id, buf, len, रुको);
पूर्ण

अटल व्योम mtk_vcodec_scp_release(काष्ठा mtk_vcodec_fw *fw)
अणु
	scp_put(fw->scp);
पूर्ण

अटल स्थिर काष्ठा mtk_vcodec_fw_ops mtk_vcodec_rproc_msg = अणु
	.load_firmware = mtk_vcodec_scp_load_firmware,
	.get_vdec_capa = mtk_vcodec_scp_get_vdec_capa,
	.get_venc_capa = mtk_vcodec_scp_get_venc_capa,
	.map_dm_addr = mtk_vcodec_vpu_scp_dm_addr,
	.ipi_रेजिस्टर = mtk_vcodec_scp_set_ipi_रेजिस्टर,
	.ipi_send = mtk_vcodec_scp_ipi_send,
	.release = mtk_vcodec_scp_release,
पूर्ण;

काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_scp_init(काष्ठा mtk_vcodec_dev *dev)
अणु
	काष्ठा mtk_vcodec_fw *fw;
	काष्ठा mtk_scp *scp;

	scp = scp_get(dev->plat_dev);
	अगर (!scp) अणु
		mtk_v4l2_err("could not get vdec scp handle");
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	fw = devm_kzalloc(&dev->plat_dev->dev, माप(*fw), GFP_KERNEL);
	fw->type = SCP;
	fw->ops = &mtk_vcodec_rproc_msg;
	fw->scp = scp;

	वापस fw;
पूर्ण
