<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _MTK_VCODEC_FW_H_
#घोषणा _MTK_VCODEC_FW_H_

#समावेश <linux/remoteproc.h>
#समावेश <linux/remoteproc/mtk_scp.h>

#समावेश "../mtk-vpu/mtk_vpu.h"

काष्ठा mtk_vcodec_dev;

क्रमागत mtk_vcodec_fw_type अणु
	VPU,
	SCP,
पूर्ण;

क्रमागत mtk_vcodec_fw_use अणु
	DECODER,
	ENCODER,
पूर्ण;

काष्ठा mtk_vcodec_fw;

प्रकार व्योम (*mtk_vcodec_ipi_handler) (व्योम *data,
	अचिन्हित पूर्णांक len, व्योम *priv);

काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_select(काष्ठा mtk_vcodec_dev *dev,
					   क्रमागत mtk_vcodec_fw_type type,
					   क्रमागत mtk_vcodec_fw_use fw_use);
व्योम mtk_vcodec_fw_release(काष्ठा mtk_vcodec_fw *fw);

पूर्णांक mtk_vcodec_fw_load_firmware(काष्ठा mtk_vcodec_fw *fw);
अचिन्हित पूर्णांक mtk_vcodec_fw_get_vdec_capa(काष्ठा mtk_vcodec_fw *fw);
अचिन्हित पूर्णांक mtk_vcodec_fw_get_venc_capa(काष्ठा mtk_vcodec_fw *fw);
व्योम *mtk_vcodec_fw_map_dm_addr(काष्ठा mtk_vcodec_fw *fw, u32 mem_addr);
पूर्णांक mtk_vcodec_fw_ipi_रेजिस्टर(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
			       mtk_vcodec_ipi_handler handler,
			       स्थिर अक्षर *name, व्योम *priv);
पूर्णांक mtk_vcodec_fw_ipi_send(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
			   व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको);

#पूर्ण_अगर /* _MTK_VCODEC_FW_H_ */
