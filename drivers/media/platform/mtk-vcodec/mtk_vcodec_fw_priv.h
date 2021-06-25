<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _MTK_VCODEC_FW_PRIV_H_
#घोषणा _MTK_VCODEC_FW_PRIV_H_

#समावेश "mtk_vcodec_fw.h"

काष्ठा mtk_vcodec_dev;

काष्ठा mtk_vcodec_fw अणु
	क्रमागत mtk_vcodec_fw_type type;
	स्थिर काष्ठा mtk_vcodec_fw_ops *ops;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mtk_scp *scp;
पूर्ण;

काष्ठा mtk_vcodec_fw_ops अणु
	पूर्णांक (*load_firmware)(काष्ठा mtk_vcodec_fw *fw);
	अचिन्हित पूर्णांक (*get_vdec_capa)(काष्ठा mtk_vcodec_fw *fw);
	अचिन्हित पूर्णांक (*get_venc_capa)(काष्ठा mtk_vcodec_fw *fw);
	व्योम *(*map_dm_addr)(काष्ठा mtk_vcodec_fw *fw, u32 dtcm_dmem_addr);
	पूर्णांक (*ipi_रेजिस्टर)(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id,
			    mtk_vcodec_ipi_handler handler, स्थिर अक्षर *name,
			    व्योम *priv);
	पूर्णांक (*ipi_send)(काष्ठा mtk_vcodec_fw *fw, पूर्णांक id, व्योम *buf,
			अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको);
	व्योम (*release)(काष्ठा mtk_vcodec_fw *fw);
पूर्ण;

#अगर IS_ENABLED(CONFIG_VIDEO_MEDIATEK_VCODEC_VPU)
काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_vpu_init(काष्ठा mtk_vcodec_dev *dev,
					     क्रमागत mtk_vcodec_fw_use fw_use);
#अन्यथा
अटल अंतरभूत काष्ठा mtk_vcodec_fw *
mtk_vcodec_fw_vpu_init(काष्ठा mtk_vcodec_dev *dev,
		       क्रमागत mtk_vcodec_fw_use fw_use)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर /* CONFIG_VIDEO_MEDIATEK_VCODEC_VPU */

#अगर IS_ENABLED(CONFIG_VIDEO_MEDIATEK_VCODEC_SCP)
काष्ठा mtk_vcodec_fw *mtk_vcodec_fw_scp_init(काष्ठा mtk_vcodec_dev *dev);
#अन्यथा
अटल अंतरभूत काष्ठा mtk_vcodec_fw *
mtk_vcodec_fw_scp_init(काष्ठा mtk_vcodec_dev *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर /* CONFIG_VIDEO_MEDIATEK_VCODEC_SCP */

#पूर्ण_अगर /* _MTK_VCODEC_FW_PRIV_H_ */
