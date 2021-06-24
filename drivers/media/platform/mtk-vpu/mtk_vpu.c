<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: Andrew-CT Chen <andrew-ct.chen@mediatek.com>
*/
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/dma-mapping.h>

#समावेश "mtk_vpu.h"

/*
 * VPU (video processor unit) is a tiny processor controlling video hardware
 * related to video codec, scaling and color क्रमmat converting.
 * VPU पूर्णांकerfaces with other blocks by share memory and पूर्णांकerrupt.
 */

#घोषणा INIT_TIMEOUT_MS		2000U
#घोषणा IPI_TIMEOUT_MS		2000U
#घोषणा VPU_IDLE_TIMEOUT_MS	1000U
#घोषणा VPU_FW_VER_LEN		16

/* maximum program/data TCM (Tightly-Coupled Memory) size */
#घोषणा VPU_PTCM_SIZE		(96 * SZ_1K)
#घोषणा VPU_DTCM_SIZE		(32 * SZ_1K)
/* the offset to get data tcm address */
#घोषणा VPU_DTCM_OFFSET		0x18000UL
/* daynamic allocated maximum extended memory size */
#घोषणा VPU_EXT_P_SIZE		SZ_1M
#घोषणा VPU_EXT_D_SIZE		SZ_4M
/* maximum binary firmware size */
#घोषणा VPU_P_FW_SIZE		(VPU_PTCM_SIZE + VPU_EXT_P_SIZE)
#घोषणा VPU_D_FW_SIZE		(VPU_DTCM_SIZE + VPU_EXT_D_SIZE)
/* the size of share buffer between Host and  VPU */
#घोषणा SHARE_BUF_SIZE		48

/* binary firmware name */
#घोषणा VPU_P_FW		"vpu_p.bin"
#घोषणा VPU_D_FW		"vpu_d.bin"
#घोषणा VPU_P_FW_NEW		"mediatek/mt8173/vpu_p.bin"
#घोषणा VPU_D_FW_NEW		"mediatek/mt8173/vpu_d.bin"

#घोषणा VPU_RESET		0x0
#घोषणा VPU_TCM_CFG		0x0008
#घोषणा VPU_PMEM_EXT0_ADDR	0x000C
#घोषणा VPU_PMEM_EXT1_ADDR	0x0010
#घोषणा VPU_TO_HOST		0x001C
#घोषणा VPU_DMEM_EXT0_ADDR	0x0014
#घोषणा VPU_DMEM_EXT1_ADDR	0x0018
#घोषणा HOST_TO_VPU		0x0024
#घोषणा VPU_IDLE_REG		0x002C
#घोषणा VPU_INT_STATUS		0x0034
#घोषणा VPU_PC_REG		0x0060
#घोषणा VPU_SP_REG		0x0064
#घोषणा VPU_RA_REG		0x0068
#घोषणा VPU_WDT_REG		0x0084

/* vpu पूर्णांकer-processor communication पूर्णांकerrupt */
#घोषणा VPU_IPC_INT		BIT(8)
/* vpu idle state */
#घोषणा VPU_IDLE_STATE		BIT(23)

/**
 * क्रमागत vpu_fw_type - VPU firmware type
 *
 * @P_FW: program firmware
 * @D_FW: data firmware
 *
 */
क्रमागत vpu_fw_type अणु
	P_FW,
	D_FW,
पूर्ण;

/**
 * काष्ठा vpu_mem - VPU extended program/data memory inक्रमmation
 *
 * @va:		the kernel भव memory address of VPU extended memory
 * @pa:		the physical memory address of VPU extended memory
 *
 */
काष्ठा vpu_mem अणु
	व्योम *va;
	dma_addr_t pa;
पूर्ण;

/**
 * काष्ठा vpu_regs - VPU TCM and configuration रेजिस्टरs
 *
 * @tcm:	the रेजिस्टर क्रम VPU Tightly-Coupled Memory
 * @cfg:	the रेजिस्टर क्रम VPU configuration
 * @irq:	the irq number क्रम VPU पूर्णांकerrupt
 */
काष्ठा vpu_regs अणु
	व्योम __iomem *tcm;
	व्योम __iomem *cfg;
	पूर्णांक irq;
पूर्ण;

/**
 * काष्ठा vpu_wdt_handler - VPU watchकरोg reset handler
 *
 * @reset_func:	reset handler
 * @priv:	निजी data
 */
काष्ठा vpu_wdt_handler अणु
	व्योम (*reset_func)(व्योम *);
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा vpu_wdt - VPU watchकरोg workqueue
 *
 * @handler:	VPU watchकरोg reset handler
 * @ws:		workकाष्ठा क्रम VPU watchकरोg
 * @wq:		workqueue क्रम VPU watchकरोg
 */
काष्ठा vpu_wdt अणु
	काष्ठा vpu_wdt_handler handler[VPU_RST_MAX];
	काष्ठा work_काष्ठा ws;
	काष्ठा workqueue_काष्ठा *wq;
पूर्ण;

/**
 * काष्ठा vpu_run - VPU initialization status
 *
 * @संकेतed:		the संकेत of vpu initialization completed
 * @fw_ver:		VPU firmware version
 * @dec_capability:	decoder capability which is not used क्रम now and
 *			the value is reserved क्रम future use
 * @enc_capability:	encoder capability which is not used क्रम now and
 *			the value is reserved क्रम future use
 * @wq:			रुको queue क्रम VPU initialization status
 */
काष्ठा vpu_run अणु
	u32 संकेतed;
	अक्षर fw_ver[VPU_FW_VER_LEN];
	अचिन्हित पूर्णांक	dec_capability;
	अचिन्हित पूर्णांक	enc_capability;
	रुको_queue_head_t wq;
पूर्ण;

/**
 * काष्ठा vpu_ipi_desc - VPU IPI descriptor
 *
 * @handler:	IPI handler
 * @name:	the name of IPI handler
 * @priv:	the निजी data of IPI handler
 */
काष्ठा vpu_ipi_desc अणु
	ipi_handler_t handler;
	स्थिर अक्षर *name;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा share_obj - DTCM (Data Tightly-Coupled Memory) buffer shared with
 *		      AP and VPU
 *
 * @id:		IPI id
 * @len:	share buffer length
 * @share_buf:	share buffer data
 */
काष्ठा share_obj अणु
	s32 id;
	u32 len;
	अचिन्हित अक्षर share_buf[SHARE_BUF_SIZE];
पूर्ण;

/**
 * काष्ठा mtk_vpu - vpu driver data
 * @exपंचांगem:		VPU extended memory inक्रमmation
 * @reg:		VPU TCM and configuration रेजिस्टरs
 * @run:		VPU initialization status
 * @wdt:		VPU watchकरोg workqueue
 * @ipi_desc:		VPU IPI descriptor
 * @recv_buf:		VPU DTCM share buffer क्रम receiving. The
 *			receive buffer is only accessed in पूर्णांकerrupt context.
 * @send_buf:		VPU DTCM share buffer क्रम sending
 * @dev:		VPU काष्ठा device
 * @clk:		VPU घड़ी on/off
 * @fw_loaded:		indicate VPU firmware loaded
 * @enable_4GB:		VPU 4GB mode on/off
 * @vpu_mutex:		protect mtk_vpu (except recv_buf) and ensure only
 *			one client to use VPU service at a समय. For example,
 *			suppose a client is using VPU to decode VP8.
 *			If the other client wants to encode VP8,
 *			it has to रुको until VP8 decode completes.
 * @wdt_refcnt:		WDT reference count to make sure the watchकरोg can be
 *			disabled अगर no other client is using VPU service
 * @ack_wq:		The रुको queue क्रम each codec and mdp. When sleeping
 *			processes wake up, they will check the condition
 *			"ipi_id_ack" to run the corresponding action or
 *			go back to sleep.
 * @ipi_id_ack:		The ACKs क्रम रेजिस्टरed IPI function sending
 *			पूर्णांकerrupt to VPU
 *
 */
काष्ठा mtk_vpu अणु
	काष्ठा vpu_mem exपंचांगem[2];
	काष्ठा vpu_regs reg;
	काष्ठा vpu_run run;
	काष्ठा vpu_wdt wdt;
	काष्ठा vpu_ipi_desc ipi_desc[IPI_MAX];
	काष्ठा share_obj __iomem *recv_buf;
	काष्ठा share_obj __iomem *send_buf;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	bool fw_loaded;
	bool enable_4GB;
	काष्ठा mutex vpu_mutex; /* क्रम protecting vpu data data काष्ठाure */
	u32 wdt_refcnt;
	रुको_queue_head_t ack_wq;
	bool ipi_id_ack[IPI_MAX];
पूर्ण;

अटल अंतरभूत व्योम vpu_cfg_ग_लिखोl(काष्ठा mtk_vpu *vpu, u32 val, u32 offset)
अणु
	ग_लिखोl(val, vpu->reg.cfg + offset);
पूर्ण

अटल अंतरभूत u32 vpu_cfg_पढ़ोl(काष्ठा mtk_vpu *vpu, u32 offset)
अणु
	वापस पढ़ोl(vpu->reg.cfg + offset);
पूर्ण

अटल अंतरभूत bool vpu_running(काष्ठा mtk_vpu *vpu)
अणु
	वापस vpu_cfg_पढ़ोl(vpu, VPU_RESET) & BIT(0);
पूर्ण

अटल व्योम vpu_घड़ी_disable(काष्ठा mtk_vpu *vpu)
अणु
	/* Disable VPU watchकरोg */
	mutex_lock(&vpu->vpu_mutex);
	अगर (!--vpu->wdt_refcnt)
		vpu_cfg_ग_लिखोl(vpu,
			       vpu_cfg_पढ़ोl(vpu, VPU_WDT_REG) & ~(1L << 31),
			       VPU_WDT_REG);
	mutex_unlock(&vpu->vpu_mutex);

	clk_disable(vpu->clk);
पूर्ण

अटल पूर्णांक vpu_घड़ी_enable(काष्ठा mtk_vpu *vpu)
अणु
	पूर्णांक ret;

	ret = clk_enable(vpu->clk);
	अगर (ret)
		वापस ret;
	/* Enable VPU watchकरोg */
	mutex_lock(&vpu->vpu_mutex);
	अगर (!vpu->wdt_refcnt++)
		vpu_cfg_ग_लिखोl(vpu,
			       vpu_cfg_पढ़ोl(vpu, VPU_WDT_REG) | (1L << 31),
			       VPU_WDT_REG);
	mutex_unlock(&vpu->vpu_mutex);

	वापस ret;
पूर्ण

अटल व्योम vpu_dump_status(काष्ठा mtk_vpu *vpu)
अणु
	dev_info(vpu->dev,
		 "vpu: run %x, pc = 0x%x, ra = 0x%x, sp = 0x%x, idle = 0x%x\n"
		 "vpu: int %x, hv = 0x%x, vh = 0x%x, wdt = 0x%x\n",
		 vpu_running(vpu), vpu_cfg_पढ़ोl(vpu, VPU_PC_REG),
		 vpu_cfg_पढ़ोl(vpu, VPU_RA_REG), vpu_cfg_पढ़ोl(vpu, VPU_SP_REG),
		 vpu_cfg_पढ़ोl(vpu, VPU_IDLE_REG),
		 vpu_cfg_पढ़ोl(vpu, VPU_INT_STATUS),
		 vpu_cfg_पढ़ोl(vpu, HOST_TO_VPU),
		 vpu_cfg_पढ़ोl(vpu, VPU_TO_HOST),
		 vpu_cfg_पढ़ोl(vpu, VPU_WDT_REG));
पूर्ण

पूर्णांक vpu_ipi_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
		     क्रमागत ipi_id id, ipi_handler_t handler,
		     स्थिर अक्षर *name, व्योम *priv)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);
	काष्ठा vpu_ipi_desc *ipi_desc;

	अगर (!vpu) अणु
		dev_err(&pdev->dev, "vpu device in not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	अगर (id < IPI_MAX && handler) अणु
		ipi_desc = vpu->ipi_desc;
		ipi_desc[id].name = name;
		ipi_desc[id].handler = handler;
		ipi_desc[id].priv = priv;
		वापस 0;
	पूर्ण

	dev_err(&pdev->dev, "register vpu ipi id %d with invalid arguments\n",
		id);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_ipi_रेजिस्टर);

पूर्णांक vpu_ipi_send(काष्ठा platक्रमm_device *pdev,
		 क्रमागत ipi_id id, व्योम *buf,
		 अचिन्हित पूर्णांक len)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);
	काष्ठा share_obj __iomem *send_obj = vpu->send_buf;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;

	अगर (id <= IPI_VPU_INIT || id >= IPI_MAX ||
	    len > माप(send_obj->share_buf) || !buf) अणु
		dev_err(vpu->dev, "failed to send ipi message\n");
		वापस -EINVAL;
	पूर्ण

	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(vpu->dev, "failed to enable vpu clock\n");
		वापस ret;
	पूर्ण
	अगर (!vpu_running(vpu)) अणु
		dev_err(vpu->dev, "vpu_ipi_send: VPU is not running\n");
		ret = -EINVAL;
		जाओ घड़ी_disable;
	पूर्ण

	mutex_lock(&vpu->vpu_mutex);

	 /* Wait until VPU receives the last command */
	समयout = jअगरfies + msecs_to_jअगरfies(IPI_TIMEOUT_MS);
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(vpu->dev, "vpu_ipi_send: IPI timeout!\n");
			ret = -EIO;
			vpu_dump_status(vpu);
			जाओ mut_unlock;
		पूर्ण
	पूर्ण जबतक (vpu_cfg_पढ़ोl(vpu, HOST_TO_VPU));

	स_नकल_toio(send_obj->share_buf, buf, len);
	ग_लिखोl(len, &send_obj->len);
	ग_लिखोl(id, &send_obj->id);

	vpu->ipi_id_ack[id] = false;
	/* send the command to VPU */
	vpu_cfg_ग_लिखोl(vpu, 0x1, HOST_TO_VPU);

	mutex_unlock(&vpu->vpu_mutex);

	/* रुको क्रम VPU's ACK */
	समयout = msecs_to_jअगरfies(IPI_TIMEOUT_MS);
	ret = रुको_event_समयout(vpu->ack_wq, vpu->ipi_id_ack[id], समयout);
	vpu->ipi_id_ack[id] = false;
	अगर (ret == 0) अणु
		dev_err(vpu->dev, "vpu ipi %d ack time out !\n", id);
		ret = -EIO;
		vpu_dump_status(vpu);
		जाओ घड़ी_disable;
	पूर्ण
	vpu_घड़ी_disable(vpu);

	वापस 0;

mut_unlock:
	mutex_unlock(&vpu->vpu_mutex);
घड़ी_disable:
	vpu_घड़ी_disable(vpu);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_ipi_send);

अटल व्योम vpu_wdt_reset_func(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा vpu_wdt *wdt = container_of(ws, काष्ठा vpu_wdt, ws);
	काष्ठा mtk_vpu *vpu = container_of(wdt, काष्ठा mtk_vpu, wdt);
	काष्ठा vpu_wdt_handler *handler = wdt->handler;
	पूर्णांक index, ret;

	dev_info(vpu->dev, "vpu reset\n");
	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(vpu->dev, "[VPU] wdt enables clock failed %d\n", ret);
		वापस;
	पूर्ण
	mutex_lock(&vpu->vpu_mutex);
	vpu_cfg_ग_लिखोl(vpu, 0x0, VPU_RESET);
	vpu->fw_loaded = false;
	mutex_unlock(&vpu->vpu_mutex);
	vpu_घड़ी_disable(vpu);

	क्रम (index = 0; index < VPU_RST_MAX; index++) अणु
		अगर (handler[index].reset_func) अणु
			handler[index].reset_func(handler[index].priv);
			dev_dbg(vpu->dev, "wdt handler func %d\n", index);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक vpu_wdt_reg_handler(काष्ठा platक्रमm_device *pdev,
			व्योम wdt_reset(व्योम *),
			व्योम *priv, क्रमागत rst_id id)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);
	काष्ठा vpu_wdt_handler *handler;

	अगर (!vpu) अणु
		dev_err(&pdev->dev, "vpu device in not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	handler = vpu->wdt.handler;

	अगर (id < VPU_RST_MAX && wdt_reset) अणु
		dev_dbg(vpu->dev, "wdt register id %d\n", id);
		mutex_lock(&vpu->vpu_mutex);
		handler[id].reset_func = wdt_reset;
		handler[id].priv = priv;
		mutex_unlock(&vpu->vpu_mutex);
		वापस 0;
	पूर्ण

	dev_err(vpu->dev, "register vpu wdt handler failed\n");
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_wdt_reg_handler);

अचिन्हित पूर्णांक vpu_get_vdec_hw_capa(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);

	वापस vpu->run.dec_capability;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_get_vdec_hw_capa);

अचिन्हित पूर्णांक vpu_get_venc_hw_capa(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);

	वापस vpu->run.enc_capability;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_get_venc_hw_capa);

व्योम *vpu_mapping_dm_addr(काष्ठा platक्रमm_device *pdev,
			  u32 dtcm_dmem_addr)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);

	अगर (!dtcm_dmem_addr ||
	    (dtcm_dmem_addr > (VPU_DTCM_SIZE + VPU_EXT_D_SIZE))) अणु
		dev_err(vpu->dev, "invalid virtual data memory address\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (dtcm_dmem_addr < VPU_DTCM_SIZE)
		वापस (__क्रमce व्योम *)(dtcm_dmem_addr + vpu->reg.tcm +
					VPU_DTCM_OFFSET);

	वापस vpu->exपंचांगem[D_FW].va + (dtcm_dmem_addr - VPU_DTCM_SIZE);
पूर्ण
EXPORT_SYMBOL_GPL(vpu_mapping_dm_addr);

काष्ठा platक्रमm_device *vpu_get_plat_device(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *vpu_node;
	काष्ठा platक्रमm_device *vpu_pdev;

	vpu_node = of_parse_phandle(dev->of_node, "mediatek,vpu", 0);
	अगर (!vpu_node) अणु
		dev_err(dev, "can't get vpu node\n");
		वापस शून्य;
	पूर्ण

	vpu_pdev = of_find_device_by_node(vpu_node);
	of_node_put(vpu_node);
	अगर (WARN_ON(!vpu_pdev)) अणु
		dev_err(dev, "vpu pdev failed\n");
		वापस शून्य;
	पूर्ण

	वापस vpu_pdev;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_get_plat_device);

/* load vpu program/data memory */
अटल पूर्णांक load_requested_vpu(काष्ठा mtk_vpu *vpu,
			      u8 fw_type)
अणु
	माप_प्रकार tcm_size = fw_type ? VPU_DTCM_SIZE : VPU_PTCM_SIZE;
	माप_प्रकार fw_size = fw_type ? VPU_D_FW_SIZE : VPU_P_FW_SIZE;
	अक्षर *fw_name = fw_type ? VPU_D_FW : VPU_P_FW;
	अक्षर *fw_new_name = fw_type ? VPU_D_FW_NEW : VPU_P_FW_NEW;
	स्थिर काष्ठा firmware *vpu_fw;
	माप_प्रकार dl_size = 0;
	माप_प्रकार extra_fw_size = 0;
	व्योम *dest;
	पूर्णांक ret;

	ret = request_firmware(&vpu_fw, fw_new_name, vpu->dev);
	अगर (ret < 0) अणु
		dev_info(vpu->dev, "Failed to load %s, %d, retry\n",
			 fw_new_name, ret);

		ret = request_firmware(&vpu_fw, fw_name, vpu->dev);
		अगर (ret < 0) अणु
			dev_err(vpu->dev, "Failed to load %s, %d\n", fw_name,
				ret);
			वापस ret;
		पूर्ण
	पूर्ण
	dl_size = vpu_fw->size;
	अगर (dl_size > fw_size) अणु
		dev_err(vpu->dev, "fw %s size %zu is abnormal\n", fw_name,
			dl_size);
		release_firmware(vpu_fw);
		वापस  -EFBIG;
	पूर्ण
	dev_dbg(vpu->dev, "Downloaded fw %s size: %zu.\n",
		fw_name,
		dl_size);
	/* reset VPU */
	vpu_cfg_ग_लिखोl(vpu, 0x0, VPU_RESET);

	/* handle extended firmware size */
	अगर (dl_size > tcm_size) अणु
		dev_dbg(vpu->dev, "fw size %zu > limited fw size %zu\n",
			dl_size, tcm_size);
		extra_fw_size = dl_size - tcm_size;
		dev_dbg(vpu->dev, "extra_fw_size %zu\n", extra_fw_size);
		dl_size = tcm_size;
	पूर्ण
	dest = (__क्रमce व्योम *)vpu->reg.tcm;
	अगर (fw_type == D_FW)
		dest += VPU_DTCM_OFFSET;
	स_नकल(dest, vpu_fw->data, dl_size);
	/* करोwnload to extended memory अगर need */
	अगर (extra_fw_size > 0) अणु
		dest = vpu->exपंचांगem[fw_type].va;
		dev_dbg(vpu->dev, "download extended memory type %x\n",
			fw_type);
		स_नकल(dest, vpu_fw->data + tcm_size, extra_fw_size);
	पूर्ण

	release_firmware(vpu_fw);

	वापस 0;
पूर्ण

पूर्णांक vpu_load_firmware(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vpu *vpu;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vpu_run *run;
	पूर्णांक ret;

	अगर (!pdev) अणु
		dev_err(dev, "VPU platform device is invalid\n");
		वापस -EINVAL;
	पूर्ण

	vpu = platक्रमm_get_drvdata(pdev);
	run = &vpu->run;

	mutex_lock(&vpu->vpu_mutex);
	अगर (vpu->fw_loaded) अणु
		mutex_unlock(&vpu->vpu_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&vpu->vpu_mutex);

	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(dev, "enable clock failed %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_lock(&vpu->vpu_mutex);

	run->संकेतed = false;
	dev_dbg(vpu->dev, "firmware request\n");
	/* Downloading program firmware to device*/
	ret = load_requested_vpu(vpu, P_FW);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request %s, %d\n", VPU_P_FW, ret);
		जाओ OUT_LOAD_FW;
	पूर्ण

	/* Downloading data firmware to device */
	ret = load_requested_vpu(vpu, D_FW);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request %s, %d\n", VPU_D_FW, ret);
		जाओ OUT_LOAD_FW;
	पूर्ण

	vpu->fw_loaded = true;
	/* boot up vpu */
	vpu_cfg_ग_लिखोl(vpu, 0x1, VPU_RESET);

	ret = रुको_event_पूर्णांकerruptible_समयout(run->wq,
					       run->संकेतed,
					       msecs_to_jअगरfies(INIT_TIMEOUT_MS)
					       );
	अगर (ret == 0) अणु
		ret = -ETIME;
		dev_err(dev, "wait vpu initialization timeout!\n");
		जाओ OUT_LOAD_FW;
	पूर्ण अन्यथा अगर (-ERESTARTSYS == ret) अणु
		dev_err(dev, "wait vpu interrupted by a signal!\n");
		जाओ OUT_LOAD_FW;
	पूर्ण

	ret = 0;
	dev_info(dev, "vpu is ready. Fw version %s\n", run->fw_ver);

OUT_LOAD_FW:
	mutex_unlock(&vpu->vpu_mutex);
	vpu_घड़ी_disable(vpu);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vpu_load_firmware);

अटल व्योम vpu_init_ipi_handler(स्थिर व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv)
अणु
	काष्ठा mtk_vpu *vpu = priv;
	स्थिर काष्ठा vpu_run *run = data;

	vpu->run.संकेतed = run->संकेतed;
	strscpy(vpu->run.fw_ver, run->fw_ver, माप(vpu->run.fw_ver));
	vpu->run.dec_capability = run->dec_capability;
	vpu->run.enc_capability = run->enc_capability;
	wake_up_पूर्णांकerruptible(&vpu->run.wq);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार vpu_debug_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[256];
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक running, pc, vpu_to_host, host_to_vpu, wdt, idle, ra, sp;
	पूर्णांक ret;
	काष्ठा device *dev = file->निजी_data;
	काष्ठा mtk_vpu *vpu = dev_get_drvdata(dev);

	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(vpu->dev, "[VPU] enable clock failed %d\n", ret);
		वापस 0;
	पूर्ण

	/* vpu रेजिस्टर status */
	running = vpu_running(vpu);
	pc = vpu_cfg_पढ़ोl(vpu, VPU_PC_REG);
	wdt = vpu_cfg_पढ़ोl(vpu, VPU_WDT_REG);
	host_to_vpu = vpu_cfg_पढ़ोl(vpu, HOST_TO_VPU);
	vpu_to_host = vpu_cfg_पढ़ोl(vpu, VPU_TO_HOST);
	ra = vpu_cfg_पढ़ोl(vpu, VPU_RA_REG);
	sp = vpu_cfg_पढ़ोl(vpu, VPU_SP_REG);
	idle = vpu_cfg_पढ़ोl(vpu, VPU_IDLE_REG);

	vpu_घड़ी_disable(vpu);

	अगर (running) अणु
		len = snम_लिखो(buf, माप(buf), "VPU is running\n\n"
		"FW Version: %s\n"
		"PC: 0x%x\n"
		"WDT: 0x%x\n"
		"Host to VPU: 0x%x\n"
		"VPU to Host: 0x%x\n"
		"SP: 0x%x\n"
		"RA: 0x%x\n"
		"idle: 0x%x\n",
		vpu->run.fw_ver, pc, wdt,
		host_to_vpu, vpu_to_host, sp, ra, idle);
	पूर्ण अन्यथा अणु
		len = snम_लिखो(buf, माप(buf), "VPU not running\n");
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations vpu_debug_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = vpu_debug_पढ़ो,
पूर्ण;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल व्योम vpu_मुक्त_ext_mem(काष्ठा mtk_vpu *vpu, u8 fw_type)
अणु
	काष्ठा device *dev = vpu->dev;
	माप_प्रकार fw_ext_size = fw_type ? VPU_EXT_D_SIZE : VPU_EXT_P_SIZE;

	dma_मुक्त_coherent(dev, fw_ext_size, vpu->exपंचांगem[fw_type].va,
			  vpu->exपंचांगem[fw_type].pa);
पूर्ण

अटल पूर्णांक vpu_alloc_ext_mem(काष्ठा mtk_vpu *vpu, u32 fw_type)
अणु
	काष्ठा device *dev = vpu->dev;
	माप_प्रकार fw_ext_size = fw_type ? VPU_EXT_D_SIZE : VPU_EXT_P_SIZE;
	u32 vpu_ext_mem0 = fw_type ? VPU_DMEM_EXT0_ADDR : VPU_PMEM_EXT0_ADDR;
	u32 vpu_ext_mem1 = fw_type ? VPU_DMEM_EXT1_ADDR : VPU_PMEM_EXT1_ADDR;
	u32 offset_4gb = vpu->enable_4GB ? 0x40000000 : 0;

	vpu->exपंचांगem[fw_type].va = dma_alloc_coherent(dev,
					       fw_ext_size,
					       &vpu->exपंचांगem[fw_type].pa,
					       GFP_KERNEL);
	अगर (!vpu->exपंचांगem[fw_type].va) अणु
		dev_err(dev, "Failed to allocate the extended program memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* Disable extend0. Enable extend1 */
	vpu_cfg_ग_लिखोl(vpu, 0x1, vpu_ext_mem0);
	vpu_cfg_ग_लिखोl(vpu, (vpu->exपंचांगem[fw_type].pa & 0xFFFFF000) + offset_4gb,
		       vpu_ext_mem1);

	dev_info(dev, "%s extend memory phy=0x%llx virt=0x%p\n",
		 fw_type ? "Data" : "Program",
		 (अचिन्हित दीर्घ दीर्घ)vpu->exपंचांगem[fw_type].pa,
		 vpu->exपंचांगem[fw_type].va);

	वापस 0;
पूर्ण

अटल व्योम vpu_ipi_handler(काष्ठा mtk_vpu *vpu)
अणु
	काष्ठा share_obj __iomem *rcv_obj = vpu->recv_buf;
	काष्ठा vpu_ipi_desc *ipi_desc = vpu->ipi_desc;
	अचिन्हित अक्षर data[SHARE_BUF_SIZE];
	s32 id = पढ़ोl(&rcv_obj->id);

	स_नकल_fromio(data, rcv_obj->share_buf, माप(data));
	अगर (id < IPI_MAX && ipi_desc[id].handler) अणु
		ipi_desc[id].handler(data, पढ़ोl(&rcv_obj->len),
				     ipi_desc[id].priv);
		अगर (id > IPI_VPU_INIT) अणु
			vpu->ipi_id_ack[id] = true;
			wake_up(&vpu->ack_wq);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(vpu->dev, "No such ipi id = %d\n", id);
	पूर्ण
पूर्ण

अटल पूर्णांक vpu_ipi_init(काष्ठा mtk_vpu *vpu)
अणु
	/* Disable VPU to host पूर्णांकerrupt */
	vpu_cfg_ग_लिखोl(vpu, 0x0, VPU_TO_HOST);

	/* shared buffer initialization */
	vpu->recv_buf = vpu->reg.tcm + VPU_DTCM_OFFSET;
	vpu->send_buf = vpu->recv_buf + 1;
	स_रखो_io(vpu->recv_buf, 0, माप(काष्ठा share_obj));
	स_रखो_io(vpu->send_buf, 0, माप(काष्ठा share_obj));

	वापस 0;
पूर्ण

अटल irqवापस_t vpu_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_vpu *vpu = priv;
	u32 vpu_to_host;
	पूर्णांक ret;

	/*
	 * Clock should have been enabled alपढ़ोy.
	 * Enable again in हाल vpu_ipi_send बार out
	 * and has disabled the घड़ी.
	 */
	ret = clk_enable(vpu->clk);
	अगर (ret) अणु
		dev_err(vpu->dev, "[VPU] enable clock failed %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण
	vpu_to_host = vpu_cfg_पढ़ोl(vpu, VPU_TO_HOST);
	अगर (vpu_to_host & VPU_IPC_INT) अणु
		vpu_ipi_handler(vpu);
	पूर्ण अन्यथा अणु
		dev_err(vpu->dev, "vpu watchdog timeout! 0x%x", vpu_to_host);
		queue_work(vpu->wdt.wq, &vpu->wdt.ws);
	पूर्ण

	/* VPU won't send another पूर्णांकerrupt until we set VPU_TO_HOST to 0. */
	vpu_cfg_ग_लिखोl(vpu, 0x0, VPU_TO_HOST);
	clk_disable(vpu->clk);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *vpu_debugfs;
#पूर्ण_अगर
अटल पूर्णांक mtk_vpu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vpu *vpu;
	काष्ठा device *dev;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	dev_dbg(&pdev->dev, "initialization\n");

	dev = &pdev->dev;
	vpu = devm_kzalloc(dev, माप(*vpu), GFP_KERNEL);
	अगर (!vpu)
		वापस -ENOMEM;

	vpu->dev = &pdev->dev;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "tcm");
	vpu->reg.tcm = devm_ioremap_resource(dev, res);
	अगर (IS_ERR((__क्रमce व्योम *)vpu->reg.tcm))
		वापस PTR_ERR((__क्रमce व्योम *)vpu->reg.tcm);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cfg_reg");
	vpu->reg.cfg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR((__क्रमce व्योम *)vpu->reg.cfg))
		वापस PTR_ERR((__क्रमce व्योम *)vpu->reg.cfg);

	/* Get VPU घड़ी */
	vpu->clk = devm_clk_get(dev, "main");
	अगर (IS_ERR(vpu->clk)) अणु
		dev_err(dev, "get vpu clock failed\n");
		वापस PTR_ERR(vpu->clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, vpu);

	ret = clk_prepare(vpu->clk);
	अगर (ret) अणु
		dev_err(dev, "prepare vpu clock failed\n");
		वापस ret;
	पूर्ण

	/* VPU watchकरोg */
	vpu->wdt.wq = create_singlethपढ़ो_workqueue("vpu_wdt");
	अगर (!vpu->wdt.wq) अणु
		dev_err(dev, "initialize wdt workqueue failed\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_WORK(&vpu->wdt.ws, vpu_wdt_reset_func);
	mutex_init(&vpu->vpu_mutex);

	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(dev, "enable vpu clock failed\n");
		जाओ workqueue_destroy;
	पूर्ण

	dev_dbg(dev, "vpu ipi init\n");
	ret = vpu_ipi_init(vpu);
	अगर (ret) अणु
		dev_err(dev, "Failed to init ipi\n");
		जाओ disable_vpu_clk;
	पूर्ण

	/* रेजिस्टर vpu initialization IPI */
	ret = vpu_ipi_रेजिस्टर(pdev, IPI_VPU_INIT, vpu_init_ipi_handler,
			       "vpu_init", vpu);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IPI_VPU_INIT\n");
		जाओ vpu_mutex_destroy;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	vpu_debugfs = debugfs_create_file("mtk_vpu", S_IRUGO, शून्य, (व्योम *)dev,
					  &vpu_debug_fops);
#पूर्ण_अगर

	/* Set PTCM to 96K and DTCM to 32K */
	vpu_cfg_ग_लिखोl(vpu, 0x2, VPU_TCM_CFG);

	vpu->enable_4GB = !!(totalram_pages() > (SZ_2G >> PAGE_SHIFT));
	dev_info(dev, "4GB mode %u\n", vpu->enable_4GB);

	अगर (vpu->enable_4GB) अणु
		ret = of_reserved_mem_device_init(dev);
		अगर (ret)
			dev_info(dev, "init reserved memory failed\n");
			/* जारी to use dynamic allocation अगर failed */
	पूर्ण

	ret = vpu_alloc_ext_mem(vpu, D_FW);
	अगर (ret) अणु
		dev_err(dev, "Allocate DM failed\n");
		जाओ हटाओ_debugfs;
	पूर्ण

	ret = vpu_alloc_ext_mem(vpu, P_FW);
	अगर (ret) अणु
		dev_err(dev, "Allocate PM failed\n");
		जाओ मुक्त_d_mem;
	पूर्ण

	init_रुकोqueue_head(&vpu->run.wq);
	init_रुकोqueue_head(&vpu->ack_wq);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "get IRQ resource failed.\n");
		ret = -ENXIO;
		जाओ मुक्त_p_mem;
	पूर्ण
	vpu->reg.irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(dev, vpu->reg.irq, vpu_irq_handler, 0,
			       pdev->name, vpu);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ मुक्त_p_mem;
	पूर्ण

	vpu_घड़ी_disable(vpu);
	dev_dbg(dev, "initialization completed\n");

	वापस 0;

मुक्त_p_mem:
	vpu_मुक्त_ext_mem(vpu, P_FW);
मुक्त_d_mem:
	vpu_मुक्त_ext_mem(vpu, D_FW);
हटाओ_debugfs:
	of_reserved_mem_device_release(dev);
#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_हटाओ(vpu_debugfs);
#पूर्ण_अगर
	स_रखो(vpu->ipi_desc, 0, माप(काष्ठा vpu_ipi_desc) * IPI_MAX);
vpu_mutex_destroy:
	mutex_destroy(&vpu->vpu_mutex);
disable_vpu_clk:
	vpu_घड़ी_disable(vpu);
workqueue_destroy:
	destroy_workqueue(vpu->wdt.wq);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_vpu_match[] = अणु
	अणु
		.compatible = "mediatek,mt8173-vpu",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_vpu_match);

अटल पूर्णांक mtk_vpu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vpu *vpu = platक्रमm_get_drvdata(pdev);

#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_हटाओ(vpu_debugfs);
#पूर्ण_अगर
	अगर (vpu->wdt.wq) अणु
		flush_workqueue(vpu->wdt.wq);
		destroy_workqueue(vpu->wdt.wq);
	पूर्ण
	vpu_मुक्त_ext_mem(vpu, P_FW);
	vpu_मुक्त_ext_mem(vpu, D_FW);
	mutex_destroy(&vpu->vpu_mutex);
	clk_unprepare(vpu->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_vpu_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_vpu *vpu = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(dev, "failed to enable vpu clock\n");
		वापस ret;
	पूर्ण

	mutex_lock(&vpu->vpu_mutex);
	/* disable vpu समयr पूर्णांकerrupt */
	vpu_cfg_ग_लिखोl(vpu, vpu_cfg_पढ़ोl(vpu, VPU_INT_STATUS) | VPU_IDLE_STATE,
		       VPU_INT_STATUS);
	/* check अगर vpu is idle क्रम प्रणाली suspend */
	समयout = jअगरfies + msecs_to_jअगरfies(VPU_IDLE_TIMEOUT_MS);
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(dev, "vpu idle timeout\n");
			mutex_unlock(&vpu->vpu_mutex);
			vpu_घड़ी_disable(vpu);
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक (!vpu_cfg_पढ़ोl(vpu, VPU_IDLE_REG));

	mutex_unlock(&vpu->vpu_mutex);
	vpu_घड़ी_disable(vpu);
	clk_unprepare(vpu->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_vpu_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_vpu *vpu = dev_get_drvdata(dev);
	पूर्णांक ret;

	clk_prepare(vpu->clk);
	ret = vpu_घड़ी_enable(vpu);
	अगर (ret) अणु
		dev_err(dev, "failed to enable vpu clock\n");
		वापस ret;
	पूर्ण

	mutex_lock(&vpu->vpu_mutex);
	/* enable vpu समयr पूर्णांकerrupt */
	vpu_cfg_ग_लिखोl(vpu,
		       vpu_cfg_पढ़ोl(vpu, VPU_INT_STATUS) & ~(VPU_IDLE_STATE),
		       VPU_INT_STATUS);
	mutex_unlock(&vpu->vpu_mutex);
	vpu_घड़ी_disable(vpu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_vpu_pm = अणु
	.suspend = mtk_vpu_suspend,
	.resume = mtk_vpu_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_vpu_driver = अणु
	.probe	= mtk_vpu_probe,
	.हटाओ	= mtk_vpu_हटाओ,
	.driver	= अणु
		.name	= "mtk_vpu",
		.pm = &mtk_vpu_pm,
		.of_match_table = mtk_vpu_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_vpu_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Mediatek Video Processor Unit driver");
