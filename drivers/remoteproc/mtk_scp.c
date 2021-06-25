<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 MediaTek Inc.

#समावेश <यंत्र/barrier.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/remoteproc/mtk_scp.h>
#समावेश <linux/rpmsg/mtk_rpmsg.h>

#समावेश "mtk_common.h"
#समावेश "remoteproc_internal.h"

#घोषणा MAX_CODE_SIZE 0x500000
#घोषणा SECTION_NAME_IPI_BUFFER ".ipi_buffer"

/**
 * scp_get() - get a reference to SCP.
 *
 * @pdev:	the platक्रमm device of the module requesting SCP platक्रमm
 *		device क्रम using SCP API.
 *
 * Return: Return शून्य अगर failed.  otherwise reference to SCP.
 **/
काष्ठा mtk_scp *scp_get(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *scp_node;
	काष्ठा platक्रमm_device *scp_pdev;

	scp_node = of_parse_phandle(dev->of_node, "mediatek,scp", 0);
	अगर (!scp_node) अणु
		dev_err(dev, "can't get SCP node\n");
		वापस शून्य;
	पूर्ण

	scp_pdev = of_find_device_by_node(scp_node);
	of_node_put(scp_node);

	अगर (WARN_ON(!scp_pdev)) अणु
		dev_err(dev, "SCP pdev failed\n");
		वापस शून्य;
	पूर्ण

	वापस platक्रमm_get_drvdata(scp_pdev);
पूर्ण
EXPORT_SYMBOL_GPL(scp_get);

/**
 * scp_put() - "free" the SCP
 *
 * @scp:	mtk_scp काष्ठाure from scp_get().
 **/
व्योम scp_put(काष्ठा mtk_scp *scp)
अणु
	put_device(scp->dev);
पूर्ण
EXPORT_SYMBOL_GPL(scp_put);

अटल व्योम scp_wdt_handler(काष्ठा mtk_scp *scp, u32 scp_to_host)
अणु
	dev_err(scp->dev, "SCP watchdog timeout! 0x%x", scp_to_host);
	rproc_report_crash(scp->rproc, RPROC_WATCHDOG);
पूर्ण

अटल व्योम scp_init_ipi_handler(व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv)
अणु
	काष्ठा mtk_scp *scp = (काष्ठा mtk_scp *)priv;
	काष्ठा scp_run *run = (काष्ठा scp_run *)data;

	scp->run.संकेतed = run->संकेतed;
	strscpy(scp->run.fw_ver, run->fw_ver, SCP_FW_VER_LEN);
	scp->run.dec_capability = run->dec_capability;
	scp->run.enc_capability = run->enc_capability;
	wake_up_पूर्णांकerruptible(&scp->run.wq);
पूर्ण

अटल व्योम scp_ipi_handler(काष्ठा mtk_scp *scp)
अणु
	काष्ठा mtk_share_obj __iomem *rcv_obj = scp->recv_buf;
	काष्ठा scp_ipi_desc *ipi_desc = scp->ipi_desc;
	u8 पंचांगp_data[SCP_SHARE_BUFFER_SIZE];
	scp_ipi_handler_t handler;
	u32 id = पढ़ोl(&rcv_obj->id);
	u32 len = पढ़ोl(&rcv_obj->len);

	अगर (len > SCP_SHARE_BUFFER_SIZE) अणु
		dev_err(scp->dev, "ipi message too long (len %d, max %d)", len,
			SCP_SHARE_BUFFER_SIZE);
		वापस;
	पूर्ण
	अगर (id >= SCP_IPI_MAX) अणु
		dev_err(scp->dev, "No such ipi id = %d\n", id);
		वापस;
	पूर्ण

	scp_ipi_lock(scp, id);
	handler = ipi_desc[id].handler;
	अगर (!handler) अणु
		dev_err(scp->dev, "No such ipi id = %d\n", id);
		scp_ipi_unlock(scp, id);
		वापस;
	पूर्ण

	स_नकल_fromio(पंचांगp_data, &rcv_obj->share_buf, len);
	handler(पंचांगp_data, len, ipi_desc[id].priv);
	scp_ipi_unlock(scp, id);

	scp->ipi_id_ack[id] = true;
	wake_up(&scp->ack_wq);
पूर्ण

अटल पूर्णांक scp_elf_पढ़ो_ipi_buf_addr(काष्ठा mtk_scp *scp,
				     स्थिर काष्ठा firmware *fw,
				     माप_प्रकार *offset);

अटल पूर्णांक scp_ipi_init(काष्ठा mtk_scp *scp, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret;
	माप_प्रकार offset;

	/* पढ़ो the ipi buf addr from FW itself first */
	ret = scp_elf_पढ़ो_ipi_buf_addr(scp, fw, &offset);
	अगर (ret) अणु
		/* use शेष ipi buf addr अगर the FW करोesn't have it */
		offset = scp->data->ipi_buf_offset;
		अगर (!offset)
			वापस ret;
	पूर्ण
	dev_info(scp->dev, "IPI buf addr %#010zx\n", offset);

	scp->recv_buf = (काष्ठा mtk_share_obj __iomem *)
			(scp->sram_base + offset);
	scp->send_buf = (काष्ठा mtk_share_obj __iomem *)
			(scp->sram_base + offset + माप(*scp->recv_buf));
	स_रखो_io(scp->recv_buf, 0, माप(*scp->recv_buf));
	स_रखो_io(scp->send_buf, 0, माप(*scp->send_buf));

	वापस 0;
पूर्ण

अटल व्योम mt8183_scp_reset_निश्चित(काष्ठा mtk_scp *scp)
अणु
	u32 val;

	val = पढ़ोl(scp->reg_base + MT8183_SW_RSTN);
	val &= ~MT8183_SW_RSTN_BIT;
	ग_लिखोl(val, scp->reg_base + MT8183_SW_RSTN);
पूर्ण

अटल व्योम mt8183_scp_reset_deनिश्चित(काष्ठा mtk_scp *scp)
अणु
	u32 val;

	val = पढ़ोl(scp->reg_base + MT8183_SW_RSTN);
	val |= MT8183_SW_RSTN_BIT;
	ग_लिखोl(val, scp->reg_base + MT8183_SW_RSTN);
पूर्ण

अटल व्योम mt8192_scp_reset_निश्चित(काष्ठा mtk_scp *scp)
अणु
	ग_लिखोl(1, scp->reg_base + MT8192_CORE0_SW_RSTN_SET);
पूर्ण

अटल व्योम mt8192_scp_reset_deनिश्चित(काष्ठा mtk_scp *scp)
अणु
	ग_लिखोl(1, scp->reg_base + MT8192_CORE0_SW_RSTN_CLR);
पूर्ण

अटल व्योम mt8183_scp_irq_handler(काष्ठा mtk_scp *scp)
अणु
	u32 scp_to_host;

	scp_to_host = पढ़ोl(scp->reg_base + MT8183_SCP_TO_HOST);
	अगर (scp_to_host & MT8183_SCP_IPC_INT_BIT)
		scp_ipi_handler(scp);
	अन्यथा
		scp_wdt_handler(scp, scp_to_host);

	/* SCP won't send another पूर्णांकerrupt until we set SCP_TO_HOST to 0. */
	ग_लिखोl(MT8183_SCP_IPC_INT_BIT | MT8183_SCP_WDT_INT_BIT,
	       scp->reg_base + MT8183_SCP_TO_HOST);
पूर्ण

अटल व्योम mt8192_scp_irq_handler(काष्ठा mtk_scp *scp)
अणु
	u32 scp_to_host;

	scp_to_host = पढ़ोl(scp->reg_base + MT8192_SCP2APMCU_IPC_SET);

	अगर (scp_to_host & MT8192_SCP_IPC_INT_BIT) अणु
		scp_ipi_handler(scp);

		/*
		 * SCP won't send another पूर्णांकerrupt until we clear
		 * MT8192_SCP2APMCU_IPC.
		 */
		ग_लिखोl(MT8192_SCP_IPC_INT_BIT,
		       scp->reg_base + MT8192_SCP2APMCU_IPC_CLR);
	पूर्ण अन्यथा अणु
		scp_wdt_handler(scp, scp_to_host);
		ग_लिखोl(1, scp->reg_base + MT8192_CORE0_WDT_IRQ);
	पूर्ण
पूर्ण

अटल irqवापस_t scp_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_scp *scp = priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(scp->dev, "failed to enable clocks\n");
		वापस IRQ_NONE;
	पूर्ण

	scp->data->scp_irq_handler(scp);

	clk_disable_unprepare(scp->clk);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक scp_elf_load_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &rproc->dev;
	काष्ठा elf32_hdr *ehdr;
	काष्ठा elf32_phdr *phdr;
	पूर्णांक i, ret = 0;
	स्थिर u8 *elf_data = fw->data;

	ehdr = (काष्ठा elf32_hdr *)elf_data;
	phdr = (काष्ठा elf32_phdr *)(elf_data + ehdr->e_phoff);

	/* go through the available ELF segments */
	क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
		u32 da = phdr->p_paddr;
		u32 memsz = phdr->p_memsz;
		u32 filesz = phdr->p_filesz;
		u32 offset = phdr->p_offset;
		व्योम __iomem *ptr;

		dev_dbg(dev, "phdr: type %d da 0x%x memsz 0x%x filesz 0x%x\n",
			phdr->p_type, da, memsz, filesz);

		अगर (phdr->p_type != PT_LOAD)
			जारी;
		अगर (!filesz)
			जारी;

		अगर (filesz > memsz) अणु
			dev_err(dev, "bad phdr filesz 0x%x memsz 0x%x\n",
				filesz, memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (offset + filesz > fw->size) अणु
			dev_err(dev, "truncated fw: need 0x%x avail 0x%zx\n",
				offset + filesz, fw->size);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* grab the kernel address क्रम this device address */
		ptr = (व्योम __iomem *)rproc_da_to_va(rproc, da, memsz, शून्य);
		अगर (!ptr) अणु
			dev_err(dev, "bad phdr da 0x%x mem 0x%x\n", da, memsz);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* put the segment where the remote processor expects it */
		scp_स_नकल_aligned(ptr, elf_data + phdr->p_offset, filesz);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scp_elf_पढ़ो_ipi_buf_addr(काष्ठा mtk_scp *scp,
				     स्थिर काष्ठा firmware *fw,
				     माप_प्रकार *offset)
अणु
	काष्ठा elf32_hdr *ehdr;
	काष्ठा elf32_shdr *shdr, *shdr_strtab;
	पूर्णांक i;
	स्थिर u8 *elf_data = fw->data;
	स्थिर अक्षर *strtab;

	ehdr = (काष्ठा elf32_hdr *)elf_data;
	shdr = (काष्ठा elf32_shdr *)(elf_data + ehdr->e_shoff);
	shdr_strtab = shdr + ehdr->e_shstrndx;
	strtab = (स्थिर अक्षर *)(elf_data + shdr_strtab->sh_offset);

	क्रम (i = 0; i < ehdr->e_shnum; i++, shdr++) अणु
		अगर (म_भेद(strtab + shdr->sh_name,
			   SECTION_NAME_IPI_BUFFER) == 0) अणु
			*offset = shdr->sh_addr;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक mt8183_scp_beक्रमe_load(काष्ठा mtk_scp *scp)
अणु
	/* Clear SCP to host पूर्णांकerrupt */
	ग_लिखोl(MT8183_SCP_IPC_INT_BIT, scp->reg_base + MT8183_SCP_TO_HOST);

	/* Reset घड़ीs beक्रमe loading FW */
	ग_लिखोl(0x0, scp->reg_base + MT8183_SCP_CLK_SW_SEL);
	ग_लिखोl(0x0, scp->reg_base + MT8183_SCP_CLK_DIV_SEL);

	/* Initialize TCM beक्रमe loading FW. */
	ग_लिखोl(0x0, scp->reg_base + MT8183_SCP_L1_SRAM_PD);
	ग_लिखोl(0x0, scp->reg_base + MT8183_SCP_TCM_TAIL_SRAM_PD);

	/* Turn on the घातer of SCP's SRAM beक्रमe using it. */
	ग_लिखोl(0x0, scp->reg_base + MT8183_SCP_SRAM_PDN);

	/*
	 * Set I-cache and D-cache size beक्रमe loading SCP FW.
	 * SCP SRAM logical address may change when cache size setting dअगरfers.
	 */
	ग_लिखोl(MT8183_SCP_CACHE_CON_WAYEN | MT8183_SCP_CACHESIZE_8KB,
	       scp->reg_base + MT8183_SCP_CACHE_CON);
	ग_लिखोl(MT8183_SCP_CACHESIZE_8KB, scp->reg_base + MT8183_SCP_DCACHE_CON);

	वापस 0;
पूर्ण

अटल व्योम mt8192_घातer_on_sram(व्योम __iomem *addr)
अणु
	पूर्णांक i;

	क्रम (i = 31; i >= 0; i--)
		ग_लिखोl(GENMASK(i, 0), addr);
	ग_लिखोl(0, addr);
पूर्ण

अटल व्योम mt8192_घातer_off_sram(व्योम __iomem *addr)
अणु
	पूर्णांक i;

	ग_लिखोl(0, addr);
	क्रम (i = 0; i < 32; i++)
		ग_लिखोl(GENMASK(i, 0), addr);
पूर्ण

अटल पूर्णांक mt8192_scp_beक्रमe_load(काष्ठा mtk_scp *scp)
अणु
	/* clear SPM पूर्णांकerrupt, SCP2SPM_IPC_CLR */
	ग_लिखोl(0xff, scp->reg_base + MT8192_SCP2SPM_IPC_CLR);

	ग_लिखोl(1, scp->reg_base + MT8192_CORE0_SW_RSTN_SET);

	/* enable SRAM घड़ी */
	mt8192_घातer_on_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_0);
	mt8192_घातer_on_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_1);
	mt8192_घातer_on_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_2);
	mt8192_घातer_on_sram(scp->reg_base + MT8192_L1TCM_SRAM_PDN);
	mt8192_घातer_on_sram(scp->reg_base + MT8192_CPU0_SRAM_PD);

	/* enable MPU क्रम all memory regions */
	ग_लिखोl(0xff, scp->reg_base + MT8192_CORE0_MEM_ATT_PREDEF);

	वापस 0;
पूर्ण

अटल पूर्णांक scp_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा mtk_scp *scp = rproc->priv;
	काष्ठा device *dev = scp->dev;
	पूर्णांक ret;

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clocks\n");
		वापस ret;
	पूर्ण

	/* Hold SCP in reset जबतक loading FW. */
	scp->data->scp_reset_निश्चित(scp);

	ret = scp->data->scp_beक्रमe_load(scp);
	अगर (ret < 0)
		जाओ leave;

	ret = scp_elf_load_segments(rproc, fw);
leave:
	clk_disable_unprepare(scp->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक scp_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा mtk_scp *scp = rproc->priv;
	काष्ठा device *dev = scp->dev;
	पूर्णांक ret;

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clocks\n");
		वापस ret;
	पूर्ण

	ret = scp_ipi_init(scp, fw);
	clk_disable_unprepare(scp->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक scp_start(काष्ठा rproc *rproc)
अणु
	काष्ठा mtk_scp *scp = (काष्ठा mtk_scp *)rproc->priv;
	काष्ठा device *dev = scp->dev;
	काष्ठा scp_run *run = &scp->run;
	पूर्णांक ret;

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clocks\n");
		वापस ret;
	पूर्ण

	run->संकेतed = false;

	scp->data->scp_reset_deनिश्चित(scp);

	ret = रुको_event_पूर्णांकerruptible_समयout(
					run->wq,
					run->संकेतed,
					msecs_to_jअगरfies(2000));

	अगर (ret == 0) अणु
		dev_err(dev, "wait SCP initialization timeout!\n");
		ret = -ETIME;
		जाओ stop;
	पूर्ण
	अगर (ret == -ERESTARTSYS) अणु
		dev_err(dev, "wait SCP interrupted by a signal!\n");
		जाओ stop;
	पूर्ण

	clk_disable_unprepare(scp->clk);
	dev_info(dev, "SCP is ready. FW version %s\n", run->fw_ver);

	वापस 0;

stop:
	scp->data->scp_reset_निश्चित(scp);
	clk_disable_unprepare(scp->clk);
	वापस ret;
पूर्ण

अटल व्योम *mt8183_scp_da_to_va(काष्ठा mtk_scp *scp, u64 da, माप_प्रकार len)
अणु
	पूर्णांक offset;

	अगर (da < scp->sram_size) अणु
		offset = da;
		अगर (offset >= 0 && (offset + len) <= scp->sram_size)
			वापस (व्योम __क्रमce *)scp->sram_base + offset;
	पूर्ण अन्यथा अगर (scp->dram_size) अणु
		offset = da - scp->dma_addr;
		अगर (offset >= 0 && (offset + len) <= scp->dram_size)
			वापस scp->cpu_addr + offset;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *mt8192_scp_da_to_va(काष्ठा mtk_scp *scp, u64 da, माप_प्रकार len)
अणु
	पूर्णांक offset;

	अगर (da >= scp->sram_phys &&
	    (da + len) <= scp->sram_phys + scp->sram_size) अणु
		offset = da - scp->sram_phys;
		वापस (व्योम __क्रमce *)scp->sram_base + offset;
	पूर्ण

	/* optional memory region */
	अगर (scp->l1tcm_size &&
	    da >= scp->l1tcm_phys &&
	    (da + len) <= scp->l1tcm_phys + scp->l1tcm_size) अणु
		offset = da - scp->l1tcm_phys;
		वापस (व्योम __क्रमce *)scp->l1tcm_base + offset;
	पूर्ण

	/* optional memory region */
	अगर (scp->dram_size &&
	    da >= scp->dma_addr &&
	    (da + len) <= scp->dma_addr + scp->dram_size) अणु
		offset = da - scp->dma_addr;
		वापस scp->cpu_addr + offset;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *scp_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा mtk_scp *scp = (काष्ठा mtk_scp *)rproc->priv;

	वापस scp->data->scp_da_to_va(scp, da, len);
पूर्ण

अटल व्योम mt8183_scp_stop(काष्ठा mtk_scp *scp)
अणु
	/* Disable SCP watchकरोg */
	ग_लिखोl(0, scp->reg_base + MT8183_WDT_CFG);
पूर्ण

अटल व्योम mt8192_scp_stop(काष्ठा mtk_scp *scp)
अणु
	/* Disable SRAM घड़ी */
	mt8192_घातer_off_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_0);
	mt8192_घातer_off_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_1);
	mt8192_घातer_off_sram(scp->reg_base + MT8192_L2TCM_SRAM_PD_2);
	mt8192_घातer_off_sram(scp->reg_base + MT8192_L1TCM_SRAM_PDN);
	mt8192_घातer_off_sram(scp->reg_base + MT8192_CPU0_SRAM_PD);

	/* Disable SCP watchकरोg */
	ग_लिखोl(0, scp->reg_base + MT8192_CORE0_WDT_CFG);
पूर्ण

अटल पूर्णांक scp_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा mtk_scp *scp = (काष्ठा mtk_scp *)rproc->priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(scp->dev, "failed to enable clocks\n");
		वापस ret;
	पूर्ण

	scp->data->scp_reset_निश्चित(scp);
	scp->data->scp_stop(scp);
	clk_disable_unprepare(scp->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rproc_ops scp_ops = अणु
	.start		= scp_start,
	.stop		= scp_stop,
	.load		= scp_load,
	.da_to_va	= scp_da_to_va,
	.parse_fw	= scp_parse_fw,
पूर्ण;

/**
 * scp_get_device() - get device काष्ठा of SCP
 *
 * @scp:	mtk_scp काष्ठाure
 **/
काष्ठा device *scp_get_device(काष्ठा mtk_scp *scp)
अणु
	वापस scp->dev;
पूर्ण
EXPORT_SYMBOL_GPL(scp_get_device);

/**
 * scp_get_rproc() - get rproc काष्ठा of SCP
 *
 * @scp:	mtk_scp काष्ठाure
 **/
काष्ठा rproc *scp_get_rproc(काष्ठा mtk_scp *scp)
अणु
	वापस scp->rproc;
पूर्ण
EXPORT_SYMBOL_GPL(scp_get_rproc);

/**
 * scp_get_vdec_hw_capa() - get video decoder hardware capability
 *
 * @scp:	mtk_scp काष्ठाure
 *
 * Return: video decoder hardware capability
 **/
अचिन्हित पूर्णांक scp_get_vdec_hw_capa(काष्ठा mtk_scp *scp)
अणु
	वापस scp->run.dec_capability;
पूर्ण
EXPORT_SYMBOL_GPL(scp_get_vdec_hw_capa);

/**
 * scp_get_venc_hw_capa() - get video encoder hardware capability
 *
 * @scp:	mtk_scp काष्ठाure
 *
 * Return: video encoder hardware capability
 **/
अचिन्हित पूर्णांक scp_get_venc_hw_capa(काष्ठा mtk_scp *scp)
अणु
	वापस scp->run.enc_capability;
पूर्ण
EXPORT_SYMBOL_GPL(scp_get_venc_hw_capa);

/**
 * scp_mapping_dm_addr() - Mapping SRAM/DRAM to kernel भव address
 *
 * @scp:	mtk_scp काष्ठाure
 * @mem_addr:	SCP views memory address
 *
 * Mapping the SCP's SRAM address /
 * DMEM (Data Extended Memory) memory address /
 * Working buffer memory address to
 * kernel भव address.
 *
 * Return: Return ERR_PTR(-EINVAL) अगर mapping failed,
 * otherwise the mapped kernel भव address
 **/
व्योम *scp_mapping_dm_addr(काष्ठा mtk_scp *scp, u32 mem_addr)
अणु
	व्योम *ptr;

	ptr = scp_da_to_va(scp->rproc, mem_addr, 0, शून्य);
	अगर (!ptr)
		वापस ERR_PTR(-EINVAL);

	वापस ptr;
पूर्ण
EXPORT_SYMBOL_GPL(scp_mapping_dm_addr);

अटल पूर्णांक scp_map_memory_region(काष्ठा mtk_scp *scp)
अणु
	पूर्णांक ret;

	ret = of_reserved_mem_device_init(scp->dev);

	/* reserved memory is optional. */
	अगर (ret == -ENODEV) अणु
		dev_info(scp->dev, "skipping reserved memory initialization.");
		वापस 0;
	पूर्ण

	अगर (ret) अणु
		dev_err(scp->dev, "failed to assign memory-region: %d\n", ret);
		वापस -ENOMEM;
	पूर्ण

	/* Reserved SCP code size */
	scp->dram_size = MAX_CODE_SIZE;
	scp->cpu_addr = dma_alloc_coherent(scp->dev, scp->dram_size,
					   &scp->dma_addr, GFP_KERNEL);
	अगर (!scp->cpu_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम scp_unmap_memory_region(काष्ठा mtk_scp *scp)
अणु
	अगर (scp->dram_size == 0)
		वापस;

	dma_मुक्त_coherent(scp->dev, scp->dram_size, scp->cpu_addr,
			  scp->dma_addr);
	of_reserved_mem_device_release(scp->dev);
पूर्ण

अटल पूर्णांक scp_रेजिस्टर_ipi(काष्ठा platक्रमm_device *pdev, u32 id,
			    ipi_handler_t handler, व्योम *priv)
अणु
	काष्ठा mtk_scp *scp = platक्रमm_get_drvdata(pdev);

	वापस scp_ipi_रेजिस्टर(scp, id, handler, priv);
पूर्ण

अटल व्योम scp_unरेजिस्टर_ipi(काष्ठा platक्रमm_device *pdev, u32 id)
अणु
	काष्ठा mtk_scp *scp = platक्रमm_get_drvdata(pdev);

	scp_ipi_unरेजिस्टर(scp, id);
पूर्ण

अटल पूर्णांक scp_send_ipi(काष्ठा platक्रमm_device *pdev, u32 id, व्योम *buf,
			अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको)
अणु
	काष्ठा mtk_scp *scp = platक्रमm_get_drvdata(pdev);

	वापस scp_ipi_send(scp, id, buf, len, रुको);
पूर्ण

अटल काष्ठा mtk_rpmsg_info mtk_scp_rpmsg_info = अणु
	.send_ipi = scp_send_ipi,
	.रेजिस्टर_ipi = scp_रेजिस्टर_ipi,
	.unरेजिस्टर_ipi = scp_unरेजिस्टर_ipi,
	.ns_ipi_id = SCP_IPI_NS_SERVICE,
पूर्ण;

अटल व्योम scp_add_rpmsg_subdev(काष्ठा mtk_scp *scp)
अणु
	scp->rpmsg_subdev =
		mtk_rpmsg_create_rproc_subdev(to_platक्रमm_device(scp->dev),
					      &mtk_scp_rpmsg_info);
	अगर (scp->rpmsg_subdev)
		rproc_add_subdev(scp->rproc, scp->rpmsg_subdev);
पूर्ण

अटल व्योम scp_हटाओ_rpmsg_subdev(काष्ठा mtk_scp *scp)
अणु
	अगर (scp->rpmsg_subdev) अणु
		rproc_हटाओ_subdev(scp->rproc, scp->rpmsg_subdev);
		mtk_rpmsg_destroy_rproc_subdev(scp->rpmsg_subdev);
		scp->rpmsg_subdev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक scp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा mtk_scp *scp;
	काष्ठा rproc *rproc;
	काष्ठा resource *res;
	अक्षर *fw_name = "scp.img";
	पूर्णांक ret, i;

	rproc = rproc_alloc(dev,
			    np->name,
			    &scp_ops,
			    fw_name,
			    माप(*scp));
	अगर (!rproc) अणु
		dev_err(dev, "unable to allocate remoteproc\n");
		वापस -ENOMEM;
	पूर्ण

	scp = (काष्ठा mtk_scp *)rproc->priv;
	scp->rproc = rproc;
	scp->dev = dev;
	scp->data = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, scp);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "sram");
	scp->sram_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR((__क्रमce व्योम *)scp->sram_base)) अणु
		dev_err(dev, "Failed to parse and map sram memory\n");
		ret = PTR_ERR((__क्रमce व्योम *)scp->sram_base);
		जाओ मुक्त_rproc;
	पूर्ण
	scp->sram_size = resource_size(res);
	scp->sram_phys = res->start;

	/* l1tcm is an optional memory region */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "l1tcm");
	scp->l1tcm_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR((__क्रमce व्योम *)scp->l1tcm_base)) अणु
		ret = PTR_ERR((__क्रमce व्योम *)scp->l1tcm_base);
		अगर (ret != -EINVAL) अणु
			dev_err(dev, "Failed to map l1tcm memory\n");
			जाओ मुक्त_rproc;
		पूर्ण
	पूर्ण अन्यथा अणु
		scp->l1tcm_size = resource_size(res);
		scp->l1tcm_phys = res->start;
	पूर्ण

	mutex_init(&scp->send_lock);
	क्रम (i = 0; i < SCP_IPI_MAX; i++)
		mutex_init(&scp->ipi_desc[i].lock);

	scp->reg_base = devm_platक्रमm_ioremap_resource_byname(pdev, "cfg");
	अगर (IS_ERR((__क्रमce व्योम *)scp->reg_base)) अणु
		dev_err(dev, "Failed to parse and map cfg memory\n");
		ret = PTR_ERR((__क्रमce व्योम *)scp->reg_base);
		जाओ destroy_mutex;
	पूर्ण

	ret = scp_map_memory_region(scp);
	अगर (ret)
		जाओ destroy_mutex;

	scp->clk = devm_clk_get(dev, "main");
	अगर (IS_ERR(scp->clk)) अणु
		dev_err(dev, "Failed to get clock\n");
		ret = PTR_ERR(scp->clk);
		जाओ release_dev_mem;
	पूर्ण

	/* रेजिस्टर SCP initialization IPI */
	ret = scp_ipi_रेजिस्टर(scp, SCP_IPI_INIT, scp_init_ipi_handler, scp);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IPI_SCP_INIT\n");
		जाओ release_dev_mem;
	पूर्ण

	init_रुकोqueue_head(&scp->run.wq);
	init_रुकोqueue_head(&scp->ack_wq);

	scp_add_rpmsg_subdev(scp);

	ret = devm_request_thपढ़ोed_irq(dev, platक्रमm_get_irq(pdev, 0), शून्य,
					scp_irq_handler, IRQF_ONESHOT,
					pdev->name, scp);

	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ हटाओ_subdev;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ हटाओ_subdev;

	वापस 0;

हटाओ_subdev:
	scp_हटाओ_rpmsg_subdev(scp);
	scp_ipi_unरेजिस्टर(scp, SCP_IPI_INIT);
release_dev_mem:
	scp_unmap_memory_region(scp);
destroy_mutex:
	क्रम (i = 0; i < SCP_IPI_MAX; i++)
		mutex_destroy(&scp->ipi_desc[i].lock);
	mutex_destroy(&scp->send_lock);
मुक्त_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक scp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_scp *scp = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	rproc_del(scp->rproc);
	scp_हटाओ_rpmsg_subdev(scp);
	scp_ipi_unरेजिस्टर(scp, SCP_IPI_INIT);
	scp_unmap_memory_region(scp);
	क्रम (i = 0; i < SCP_IPI_MAX; i++)
		mutex_destroy(&scp->ipi_desc[i].lock);
	mutex_destroy(&scp->send_lock);
	rproc_मुक्त(scp->rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_scp_of_data mt8183_of_data = अणु
	.scp_beक्रमe_load = mt8183_scp_beक्रमe_load,
	.scp_irq_handler = mt8183_scp_irq_handler,
	.scp_reset_निश्चित = mt8183_scp_reset_निश्चित,
	.scp_reset_deनिश्चित = mt8183_scp_reset_deनिश्चित,
	.scp_stop = mt8183_scp_stop,
	.scp_da_to_va = mt8183_scp_da_to_va,
	.host_to_scp_reg = MT8183_HOST_TO_SCP,
	.host_to_scp_पूर्णांक_bit = MT8183_HOST_IPC_INT_BIT,
	.ipi_buf_offset = 0x7bdb0,
पूर्ण;

अटल स्थिर काष्ठा mtk_scp_of_data mt8192_of_data = अणु
	.scp_beक्रमe_load = mt8192_scp_beक्रमe_load,
	.scp_irq_handler = mt8192_scp_irq_handler,
	.scp_reset_निश्चित = mt8192_scp_reset_निश्चित,
	.scp_reset_deनिश्चित = mt8192_scp_reset_deनिश्चित,
	.scp_stop = mt8192_scp_stop,
	.scp_da_to_va = mt8192_scp_da_to_va,
	.host_to_scp_reg = MT8192_GIPC_IN_SET,
	.host_to_scp_पूर्णांक_bit = MT8192_HOST_IPC_INT_BIT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_scp_of_match[] = अणु
	अणु .compatible = "mediatek,mt8183-scp", .data = &mt8183_of_data पूर्ण,
	अणु .compatible = "mediatek,mt8192-scp", .data = &mt8192_of_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_scp_of_match);

अटल काष्ठा platक्रमm_driver mtk_scp_driver = अणु
	.probe = scp_probe,
	.हटाओ = scp_हटाओ,
	.driver = अणु
		.name = "mtk-scp",
		.of_match_table = mtk_scp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_scp_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek SCP control driver");
