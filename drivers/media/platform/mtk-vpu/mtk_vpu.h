<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: Andrew-CT Chen <andrew-ct.chen@mediatek.com>
*/

#अगर_अघोषित _MTK_VPU_H
#घोषणा _MTK_VPU_H

#समावेश <linux/platक्रमm_device.h>

/**
 * DOC: VPU
 *
 * VPU (video processor unit) is a tiny processor controlling video hardware
 * related to video codec, scaling and color क्रमmat converting.
 * VPU पूर्णांकerfaces with other blocks by share memory and पूर्णांकerrupt.
 */

प्रकार व्योम (*ipi_handler_t) (स्थिर व्योम *data,
			       अचिन्हित पूर्णांक len,
			       व्योम *priv);

/**
 * क्रमागत ipi_id - the id of पूर्णांकer-processor पूर्णांकerrupt
 *
 * @IPI_VPU_INIT:	 The पूर्णांकerrupt from vpu is to notfiy kernel
 *			 VPU initialization completed.
 *			 IPI_VPU_INIT is sent from VPU when firmware is
 *			 loaded. AP करोesn't need to send IPI_VPU_INIT
 *			 command to VPU.
 *			 For other IPI below, AP should send the request
 *			 to VPU to trigger the पूर्णांकerrupt.
 * @IPI_VDEC_H264:	 The पूर्णांकerrupt from vpu is to notअगरy kernel to
 *			 handle H264 viकरोe decoder job, and vice versa.
 *			 Decode output क्रमmat is always MT21 no matter what
 *			 the input क्रमmat is.
 * @IPI_VDEC_VP8:	 The पूर्णांकerrupt from is to notअगरy kernel to
 *			 handle VP8 video decoder job, and vice versa.
 *			 Decode output क्रमmat is always MT21 no matter what
 *			 the input क्रमmat is.
 * @IPI_VDEC_VP9:	 The पूर्णांकerrupt from vpu is to notअगरy kernel to
 *			 handle VP9 video decoder job, and vice versa.
 *			 Decode output क्रमmat is always MT21 no matter what
 *			 the input क्रमmat is.
 * @IPI_VENC_H264:	 The पूर्णांकerrupt from vpu is to notअगरy kernel to
 *			 handle H264 video encoder job, and vice versa.
 * @IPI_VENC_VP8:	 The पूर्णांकerrupt fro vpu is to notअगरy kernel to
 *			 handle VP8 video encoder job,, and vice versa.
 * @IPI_MDP:		 The पूर्णांकerrupt from vpu is to notअगरy kernel to
 *			 handle MDP (Media Data Path) job, and vice versa.
 * @IPI_MAX:		 The maximum IPI number
 */

क्रमागत ipi_id अणु
	IPI_VPU_INIT = 0,
	IPI_VDEC_H264,
	IPI_VDEC_VP8,
	IPI_VDEC_VP9,
	IPI_VENC_H264,
	IPI_VENC_VP8,
	IPI_MDP,
	IPI_MAX,
पूर्ण;

/**
 * क्रमागत rst_id - reset id to रेजिस्टर reset function क्रम VPU watchकरोg समयout
 *
 * @VPU_RST_ENC: encoder reset id
 * @VPU_RST_DEC: decoder reset id
 * @VPU_RST_MDP: MDP (Media Data Path) reset id
 * @VPU_RST_MAX: maximum reset id
 */
क्रमागत rst_id अणु
	VPU_RST_ENC,
	VPU_RST_DEC,
	VPU_RST_MDP,
	VPU_RST_MAX,
पूर्ण;

/**
 * vpu_ipi_रेजिस्टर - रेजिस्टर an ipi function
 *
 * @pdev:	VPU platक्रमm device
 * @id:		IPI ID
 * @handler:	IPI handler
 * @name:	IPI name
 * @priv:	निजी data क्रम IPI handler
 *
 * Register an ipi function to receive ipi पूर्णांकerrupt from VPU.
 *
 * Return: Return 0 अगर ipi रेजिस्टरs successfully, otherwise it is failed.
 */
पूर्णांक vpu_ipi_रेजिस्टर(काष्ठा platक्रमm_device *pdev, क्रमागत ipi_id id,
		     ipi_handler_t handler, स्थिर अक्षर *name, व्योम *priv);

/**
 * vpu_ipi_send - send data from AP to vpu.
 *
 * @pdev:	VPU platक्रमm device
 * @id:		IPI ID
 * @buf:	the data buffer
 * @len:	the data buffer length
 *
 * This function is thपढ़ो-safe. When this function वापसs,
 * VPU has received the data and starts the processing.
 * When the processing completes, IPI handler रेजिस्टरed
 * by vpu_ipi_रेजिस्टर will be called in पूर्णांकerrupt context.
 *
 * Return: Return 0 अगर sending data successfully, otherwise it is failed.
 **/
पूर्णांक vpu_ipi_send(काष्ठा platक्रमm_device *pdev,
		 क्रमागत ipi_id id, व्योम *buf,
		 अचिन्हित पूर्णांक len);

/**
 * vpu_get_plat_device - get VPU's platक्रमm device
 *
 * @pdev:	the platक्रमm device of the module requesting VPU platक्रमm
 *		device क्रम using VPU API.
 *
 * Return: Return शून्य अगर it is failed.
 * otherwise it is VPU's platक्रमm device
 **/
काष्ठा platक्रमm_device *vpu_get_plat_device(काष्ठा platक्रमm_device *pdev);

/**
 * vpu_wdt_reg_handler - रेजिस्टर a VPU watchकरोg handler
 *
 * @pdev:               VPU platक्रमm device
 * @vpu_wdt_reset_func():	the callback reset function
 *	@priv: the निजी data क्रम reset function
 * @priv:		the निजी data क्रम reset function
 * @id:			reset id
 *
 * Register a handler perक्रमming own tasks when vpu reset by watchकरोg
 *
 * Return: Return 0 अगर the handler is added successfully,
 * otherwise it is failed.
 **/
पूर्णांक vpu_wdt_reg_handler(काष्ठा platक्रमm_device *pdev,
			व्योम vpu_wdt_reset_func(व्योम *priv),
			व्योम *priv, क्रमागत rst_id id);

/**
 * vpu_get_vdec_hw_capa - get video decoder hardware capability
 *
 * @pdev:	VPU platक्रमm device
 *
 * Return: video decoder hardware capability
 **/
अचिन्हित पूर्णांक vpu_get_vdec_hw_capa(काष्ठा platक्रमm_device *pdev);

/**
 * vpu_get_venc_hw_capa - get video encoder hardware capability
 *
 * @pdev:	VPU platक्रमm device
 *
 * Return: video encoder hardware capability
 **/
अचिन्हित पूर्णांक vpu_get_venc_hw_capa(काष्ठा platक्रमm_device *pdev);

/**
 * vpu_load_firmware - करोwnload VPU firmware and boot it
 *
 * @pdev:	VPU platक्रमm device
 *
 * Return: Return 0 अगर करोwnloading firmware successfully,
 * otherwise it is failed
 **/
पूर्णांक vpu_load_firmware(काष्ठा platक्रमm_device *pdev);

/**
 * vpu_mapping_dm_addr - Mapping DTCM/DMEM to kernel भव address
 *
 * @pdev:		VPU platक्रमm device
 * @dtcm_dmem_addr:	VPU's data memory address
 *
 * Mapping the VPU's DTCM (Data Tightly-Coupled Memory) /
 * DMEM (Data Extended Memory) memory address to
 * kernel भव address.
 *
 * Return: Return ERR_PTR(-EINVAL) अगर mapping failed,
 * otherwise the mapped kernel भव address
 **/
व्योम *vpu_mapping_dm_addr(काष्ठा platक्रमm_device *pdev,
			  u32 dtcm_dmem_addr);
#पूर्ण_अगर /* _MTK_VPU_H */
