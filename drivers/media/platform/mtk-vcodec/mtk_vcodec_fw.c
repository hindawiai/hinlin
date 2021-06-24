<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "mtk_vcodec_fw.h"
#समावेश "mtk_vcodec_fw_priv.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "mtk_vcodec_drv.h"

काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_select(काष्ठा mtk_vcodec_dev *dev,
					   क्रमागत mtk_vcodec_fw_type type,
					   क्रमागत mtk_vcodec_fw_use fw_use)
अणु
	चयन (type) अणु
	हाल VPU:
		वापस mtk_vcodec_fw_vpu_init(dev, fw_use);
	हाल SCP:
		वापस mtk_vcodec_fw_scp_init(dev);
	शेष:
		mtk_v4l2_err("invalid vcodec fw type");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_select);

व्योम mtk_vcodec_fw_release(काष्ठा mtk_vcodec_fw *fw)
अणु
	fw->ops->release(fw);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_release);

पूर्णांक mtk_vcodec_fw_load_firmware(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस fw->ops->load_firmware(fw);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_load_firmware);

अचिन्हित पूर्णांक mtk_vcodec_fw_get_vdec_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस fw->ops->get_vdec_capa(fw);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_get_vdec_capa);

अचिन्हित पूर्णांक mtk_vcodec_fw_get_venc_capa(काष्ठा mtk_vcodec_fw *fw)
अणु
	वापस fw->ops->get_venc_capa(fw);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_get_venc_capa);

व्योम *mtk_vcodec_fw_map_dm_addr(काष्ठा mtk_vcodec_fw *fw, u32 mem_addr)
अणु
	वापस fw->ops->map_dm_addr(fw, mem_addr);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_map_dm_addr);

पूर्णांक mtk_vcodec_fw_ipi_रेजिस्टर(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
			       mtk_vcodec_ipi_handler handler,
			       स्थिर अक्षर *name, व्योम *priv)
अणु
	वापस fw->ops->ipi_रेजिस्टर(fw, id, handler, name, priv);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_ipi_रेजिस्टर);

पूर्णांक mtk_vcodec_fw_ipi_send(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id, व्योम *buf,
			   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको)
अणु
	वापस fw->ops->ipi_send(fw, id, buf, len, रुको);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_vcodec_fw_ipi_send);
