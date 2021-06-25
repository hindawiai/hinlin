<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "mtk_vcodec_fw_priv.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "mtk_vcodec_drv.h"

अटल पूर्णांक mtk_vcodec_vpu_load_firmware(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस vpu_load_firmware(fw->pdev);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_vcodec_vpu_get_vdec_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस vpu_get_vdec_hw_capa(fw->pdev);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_vcodec_vpu_get_venc_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस vpu_get_venc_hw_capa(fw->pdev);
पूर्ण

अटल व्योम *mtk_vcodec_vpu_map_dm_addr(काष्ठा mtk_vcodec_fw *fw,
					u32 dtcm_dmem_addr)
अणु
	वापस vpu_mapping_dm_addr(fw->pdev, dtcm_dmem_addr);
पूर्ण

अटल पूर्णांक mtk_vcodec_vpu_set_ipi_रेजिस्टर(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
					   mtk_vcodec_ipi_handler handler,
					   स्थिर अक्षर *name, व्योम *priv)
अणु
	/*
	 * The handler we receive takes a व्योम * as its first argument. We
	 * cannot change this because it needs to be passed करोwn to the rproc
	 * subप्रणाली when SCP is used. VPU takes a स्थिर argument, which is
	 * more स्थिरrained, so the conversion below is safe.
	 */
	ipi_handler_t handler_स्थिर = (ipi_handler_t)handler;

	वापस vpu_ipi_रेजिस्टर(fw->pdev, id, handler_स्थिर, name, priv);
पूर्ण

अटल पूर्णांक mtk_vcodec_vpu_ipi_send(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id, व्योम *buf,
				   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको)
अणु
	वापस vpu_ipi_send(fw->pdev, id, buf, len);
पूर्ण

अटल व्योम mtk_vcodec_vpu_release(काष्ठा mtk_vcodec_fw *fw)
अणु
	put_device(&fw->pdev->dev);
पूर्ण

अटल व्योम mtk_vcodec_vpu_reset_handler(व्योम *priv)
अणु
	काष्ठा mtk_vcodec_dev *dev = priv;
	काष्ठा mtk_vcodec_ctx *ctx;

	mtk_v4l2_err("Watchdog timeout!!");

	mutex_lock(&dev->dev_mutex);
	list_क्रम_each_entry(ctx, &dev->ctx_list, list) अणु
		ctx->state = MTK_STATE_ABORT;
		mtk_v4l2_debug(0, "[%d] Change to state MTK_STATE_ABORT",
			       ctx->id);
	पूर्ण
	mutex_unlock(&dev->dev_mutex);
पूर्ण

अटल स्थिर काष्ठा mtk_vcodec_fw_ops mtk_vcodec_vpu_msg = अणु
	.load_firmware = mtk_vcodec_vpu_load_firmware,
	.get_vdec_capa = mtk_vcodec_vpu_get_vdec_capa,
	.get_venc_capa = mtk_vcodec_vpu_get_venc_capa,
	.map_dm_addr = mtk_vcodec_vpu_map_dm_addr,
	.ipi_रेजिस्टर = mtk_vcodec_vpu_set_ipi_रेजिस्टर,
	.ipi_send = mtk_vcodec_vpu_ipi_send,
	.release = mtk_vcodec_vpu_release,
पूर्ण;

काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_vpu_init(काष्ठा mtk_vcodec_dev *dev,
					     क्रमागत mtk_vcodec_fw_use fw_use)
अणु
	काष्ठा platक्रमm_device *fw_pdev;
	काष्ठा mtk_vcodec_fw *fw;
	क्रमागत rst_id rst_id;

	चयन (fw_use) अणु
	हाल ENCODER:
		rst_id = VPU_RST_ENC;
		अवरोध;
	हाल DECODER:
	शेष:
		rst_id = VPU_RST_DEC;
		अवरोध;
	पूर्ण

	fw_pdev = vpu_get_plat_device(dev->plat_dev);
	अगर (!fw_pdev) अणु
		mtk_v4l2_err("firmware device is not ready");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	vpu_wdt_reg_handler(fw_pdev, mtk_vcodec_vpu_reset_handler, dev, rst_id);

	fw = devm_kzalloc(&dev->plat_dev->dev, माप(*fw), GFP_KERNEL);
	fw->type = VPU;
	fw->ops = &mtk_vcodec_vpu_msg;
	fw->pdev = fw_pdev;

	वापस fw;
पूर्ण
