<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2016-2017 Qualcomm Atheros, Inc. All rights reserved.
 * Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "pci.h"
#समावेश "ahb.h"

अटल स्थिर काष्ठा of_device_id ath10k_ahb_of_match[] = अणु
	अणु .compatible = "qcom,ipq4019-wifi",
	  .data = (व्योम *)ATH10K_HW_QCA4019
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ath10k_ahb_of_match);

#घोषणा QCA4019_SRAM_ADDR      0x000C0000
#घोषणा QCA4019_SRAM_LEN       0x00040000 /* 256 kb */

अटल अंतरभूत काष्ठा ath10k_ahb *ath10k_ahb_priv(काष्ठा ath10k *ar)
अणु
	वापस &((काष्ठा ath10k_pci *)ar->drv_priv)->ahb[0];
पूर्ण

अटल व्योम ath10k_ahb_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ioग_लिखो32(value, ar_ahb->mem + offset);
पूर्ण

अटल u32 ath10k_ahb_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	वापस ioपढ़ो32(ar_ahb->mem + offset);
पूर्ण

अटल u32 ath10k_ahb_gcc_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	वापस ioपढ़ो32(ar_ahb->gcc_mem + offset);
पूर्ण

अटल व्योम ath10k_ahb_tcsr_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ioग_लिखो32(value, ar_ahb->tcsr_mem + offset);
पूर्ण

अटल u32 ath10k_ahb_tcsr_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	वापस ioपढ़ो32(ar_ahb->tcsr_mem + offset);
पूर्ण

अटल u32 ath10k_ahb_soc_पढ़ो32(काष्ठा ath10k *ar, u32 addr)
अणु
	वापस ath10k_ahb_पढ़ो32(ar, RTC_SOC_BASE_ADDRESS + addr);
पूर्ण

अटल पूर्णांक ath10k_ahb_get_num_banks(काष्ठा ath10k *ar)
अणु
	अगर (ar->hw_rev == ATH10K_HW_QCA4019)
		वापस 1;

	ath10k_warn(ar, "unknown number of banks, assuming 1\n");
	वापस 1;
पूर्ण

अटल पूर्णांक ath10k_ahb_घड़ी_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	काष्ठा device *dev;

	dev = &ar_ahb->pdev->dev;

	ar_ahb->cmd_clk = devm_clk_get(dev, "wifi_wcss_cmd");
	अगर (IS_ERR_OR_शून्य(ar_ahb->cmd_clk)) अणु
		ath10k_err(ar, "failed to get cmd clk: %ld\n",
			   PTR_ERR(ar_ahb->cmd_clk));
		वापस ar_ahb->cmd_clk ? PTR_ERR(ar_ahb->cmd_clk) : -ENODEV;
	पूर्ण

	ar_ahb->ref_clk = devm_clk_get(dev, "wifi_wcss_ref");
	अगर (IS_ERR_OR_शून्य(ar_ahb->ref_clk)) अणु
		ath10k_err(ar, "failed to get ref clk: %ld\n",
			   PTR_ERR(ar_ahb->ref_clk));
		वापस ar_ahb->ref_clk ? PTR_ERR(ar_ahb->ref_clk) : -ENODEV;
	पूर्ण

	ar_ahb->rtc_clk = devm_clk_get(dev, "wifi_wcss_rtc");
	अगर (IS_ERR_OR_शून्य(ar_ahb->rtc_clk)) अणु
		ath10k_err(ar, "failed to get rtc clk: %ld\n",
			   PTR_ERR(ar_ahb->rtc_clk));
		वापस ar_ahb->rtc_clk ? PTR_ERR(ar_ahb->rtc_clk) : -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_ahb_घड़ी_deinit(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ar_ahb->cmd_clk = शून्य;
	ar_ahb->ref_clk = शून्य;
	ar_ahb->rtc_clk = शून्य;
पूर्ण

अटल पूर्णांक ath10k_ahb_घड़ी_enable(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(ar_ahb->cmd_clk) ||
	    IS_ERR_OR_शून्य(ar_ahb->ref_clk) ||
	    IS_ERR_OR_शून्य(ar_ahb->rtc_clk)) अणु
		ath10k_err(ar, "clock(s) is/are not initialized\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(ar_ahb->cmd_clk);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable cmd clk: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(ar_ahb->ref_clk);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable ref clk: %d\n", ret);
		जाओ err_cmd_clk_disable;
	पूर्ण

	ret = clk_prepare_enable(ar_ahb->rtc_clk);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable rtc clk: %d\n", ret);
		जाओ err_ref_clk_disable;
	पूर्ण

	वापस 0;

err_ref_clk_disable:
	clk_disable_unprepare(ar_ahb->ref_clk);

err_cmd_clk_disable:
	clk_disable_unprepare(ar_ahb->cmd_clk);

out:
	वापस ret;
पूर्ण

अटल व्योम ath10k_ahb_घड़ी_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	clk_disable_unprepare(ar_ahb->cmd_clk);

	clk_disable_unprepare(ar_ahb->ref_clk);

	clk_disable_unprepare(ar_ahb->rtc_clk);
पूर्ण

अटल पूर्णांक ath10k_ahb_rst_ctrl_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	काष्ठा device *dev;

	dev = &ar_ahb->pdev->dev;

	ar_ahb->core_cold_rst = devm_reset_control_get_exclusive(dev,
								 "wifi_core_cold");
	अगर (IS_ERR(ar_ahb->core_cold_rst)) अणु
		ath10k_err(ar, "failed to get core cold rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->core_cold_rst));
		वापस PTR_ERR(ar_ahb->core_cold_rst);
	पूर्ण

	ar_ahb->radio_cold_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_cold");
	अगर (IS_ERR(ar_ahb->radio_cold_rst)) अणु
		ath10k_err(ar, "failed to get radio cold rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_cold_rst));
		वापस PTR_ERR(ar_ahb->radio_cold_rst);
	पूर्ण

	ar_ahb->radio_warm_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_warm");
	अगर (IS_ERR(ar_ahb->radio_warm_rst)) अणु
		ath10k_err(ar, "failed to get radio warm rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_warm_rst));
		वापस PTR_ERR(ar_ahb->radio_warm_rst);
	पूर्ण

	ar_ahb->radio_srअगर_rst = devm_reset_control_get_exclusive(dev,
								  "wifi_radio_srif");
	अगर (IS_ERR(ar_ahb->radio_srअगर_rst)) अणु
		ath10k_err(ar, "failed to get radio srif rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->radio_srअगर_rst));
		वापस PTR_ERR(ar_ahb->radio_srअगर_rst);
	पूर्ण

	ar_ahb->cpu_init_rst = devm_reset_control_get_exclusive(dev,
								"wifi_cpu_init");
	अगर (IS_ERR(ar_ahb->cpu_init_rst)) अणु
		ath10k_err(ar, "failed to get cpu init rst ctrl: %ld\n",
			   PTR_ERR(ar_ahb->cpu_init_rst));
		वापस PTR_ERR(ar_ahb->cpu_init_rst);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_ahb_rst_ctrl_deinit(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ar_ahb->core_cold_rst = शून्य;
	ar_ahb->radio_cold_rst = शून्य;
	ar_ahb->radio_warm_rst = शून्य;
	ar_ahb->radio_srअगर_rst = शून्य;
	ar_ahb->cpu_init_rst = शून्य;
पूर्ण

अटल पूर्णांक ath10k_ahb_release_reset(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(ar_ahb->radio_cold_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->radio_warm_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->radio_srअगर_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->cpu_init_rst)) अणु
		ath10k_err(ar, "rst ctrl(s) is/are not initialized\n");
		वापस -EINVAL;
	पूर्ण

	ret = reset_control_deनिश्चित(ar_ahb->radio_cold_rst);
	अगर (ret) अणु
		ath10k_err(ar, "failed to deassert radio cold rst: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(ar_ahb->radio_warm_rst);
	अगर (ret) अणु
		ath10k_err(ar, "failed to deassert radio warm rst: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(ar_ahb->radio_srअगर_rst);
	अगर (ret) अणु
		ath10k_err(ar, "failed to deassert radio srif rst: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(ar_ahb->cpu_init_rst);
	अगर (ret) अणु
		ath10k_err(ar, "failed to deassert cpu init rst: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_ahb_halt_axi_bus(काष्ठा ath10k *ar, u32 haltreq_reg,
				    u32 haltack_reg)
अणु
	अचिन्हित दीर्घ समयout;
	u32 val;

	/* Issue halt axi bus request */
	val = ath10k_ahb_tcsr_पढ़ो32(ar, haltreq_reg);
	val |= AHB_AXI_BUS_HALT_REQ;
	ath10k_ahb_tcsr_ग_लिखो32(ar, haltreq_reg, val);

	/* Wait क्रम axi bus halted ack */
	समयout = jअगरfies + msecs_to_jअगरfies(ATH10K_AHB_AXI_BUS_HALT_TIMEOUT);
	करो अणु
		val = ath10k_ahb_tcsr_पढ़ो32(ar, haltack_reg);
		अगर (val & AHB_AXI_BUS_HALT_ACK)
			अवरोध;

		mdelay(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (!(val & AHB_AXI_BUS_HALT_ACK)) अणु
		ath10k_err(ar, "failed to halt axi bus: %d\n", val);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_AHB, "axi bus halted\n");
पूर्ण

अटल व्योम ath10k_ahb_halt_chip(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	u32 core_id, glb_cfg_reg, haltreq_reg, haltack_reg;
	u32 val;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(ar_ahb->core_cold_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->radio_cold_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->radio_warm_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->radio_srअगर_rst) ||
	    IS_ERR_OR_शून्य(ar_ahb->cpu_init_rst)) अणु
		ath10k_err(ar, "rst ctrl(s) is/are not initialized\n");
		वापस;
	पूर्ण

	core_id = ath10k_ahb_पढ़ो32(ar, ATH10K_AHB_WLAN_CORE_ID_REG);

	चयन (core_id) अणु
	हाल 0:
		glb_cfg_reg = ATH10K_AHB_TCSR_WIFI0_GLB_CFG;
		haltreq_reg = ATH10K_AHB_TCSR_WCSS0_HALTREQ;
		haltack_reg = ATH10K_AHB_TCSR_WCSS0_HALTACK;
		अवरोध;
	हाल 1:
		glb_cfg_reg = ATH10K_AHB_TCSR_WIFI1_GLB_CFG;
		haltreq_reg = ATH10K_AHB_TCSR_WCSS1_HALTREQ;
		haltack_reg = ATH10K_AHB_TCSR_WCSS1_HALTACK;
		अवरोध;
	शेष:
		ath10k_err(ar, "invalid core id %d found, skipping reset sequence\n",
			   core_id);
		वापस;
	पूर्ण

	ath10k_ahb_halt_axi_bus(ar, haltreq_reg, haltack_reg);

	val = ath10k_ahb_tcsr_पढ़ो32(ar, glb_cfg_reg);
	val |= TCSR_WIFIX_GLB_CFG_DISABLE_CORE_CLK;
	ath10k_ahb_tcsr_ग_लिखो32(ar, glb_cfg_reg, val);

	ret = reset_control_निश्चित(ar_ahb->core_cold_rst);
	अगर (ret)
		ath10k_err(ar, "failed to assert core cold rst: %d\n", ret);
	msleep(1);

	ret = reset_control_निश्चित(ar_ahb->radio_cold_rst);
	अगर (ret)
		ath10k_err(ar, "failed to assert radio cold rst: %d\n", ret);
	msleep(1);

	ret = reset_control_निश्चित(ar_ahb->radio_warm_rst);
	अगर (ret)
		ath10k_err(ar, "failed to assert radio warm rst: %d\n", ret);
	msleep(1);

	ret = reset_control_निश्चित(ar_ahb->radio_srअगर_rst);
	अगर (ret)
		ath10k_err(ar, "failed to assert radio srif rst: %d\n", ret);
	msleep(1);

	ret = reset_control_निश्चित(ar_ahb->cpu_init_rst);
	अगर (ret)
		ath10k_err(ar, "failed to assert cpu init rst: %d\n", ret);
	msleep(10);

	/* Clear halt req and core घड़ी disable req beक्रमe
	 * deनिश्चितing wअगरi core reset.
	 */
	val = ath10k_ahb_tcsr_पढ़ो32(ar, haltreq_reg);
	val &= ~AHB_AXI_BUS_HALT_REQ;
	ath10k_ahb_tcsr_ग_लिखो32(ar, haltreq_reg, val);

	val = ath10k_ahb_tcsr_पढ़ो32(ar, glb_cfg_reg);
	val &= ~TCSR_WIFIX_GLB_CFG_DISABLE_CORE_CLK;
	ath10k_ahb_tcsr_ग_लिखो32(ar, glb_cfg_reg, val);

	ret = reset_control_deनिश्चित(ar_ahb->core_cold_rst);
	अगर (ret)
		ath10k_err(ar, "failed to deassert core cold rst: %d\n", ret);

	ath10k_dbg(ar, ATH10K_DBG_AHB, "core %d reset done\n", core_id);
पूर्ण

अटल irqवापस_t ath10k_ahb_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath10k *ar = arg;

	अगर (!ath10k_pci_irq_pending(ar))
		वापस IRQ_NONE;

	ath10k_pci_disable_and_clear_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_mask(ar);
	napi_schedule(&ar->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath10k_ahb_request_irq_legacy(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	पूर्णांक ret;

	ret = request_irq(ar_ahb->irq,
			  ath10k_ahb_पूर्णांकerrupt_handler,
			  IRQF_SHARED, "ath10k_ahb", ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request legacy irq %d: %d\n",
			    ar_ahb->irq, ret);
		वापस ret;
	पूर्ण
	ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_LEGACY;

	वापस 0;
पूर्ण

अटल व्योम ath10k_ahb_release_irq_legacy(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	मुक्त_irq(ar_ahb->irq, ar);
पूर्ण

अटल व्योम ath10k_ahb_irq_disable(काष्ठा ath10k *ar)
अणु
	ath10k_ce_disable_पूर्णांकerrupts(ar);
	ath10k_pci_disable_and_clear_legacy_irq(ar);
पूर्ण

अटल पूर्णांक ath10k_ahb_resource_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;
	पूर्णांक ret;

	pdev = ar_ahb->pdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ath10k_err(ar, "failed to get memory resource\n");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	ar_ahb->mem = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ar_ahb->mem)) अणु
		ath10k_err(ar, "mem ioremap error\n");
		ret = PTR_ERR(ar_ahb->mem);
		जाओ out;
	पूर्ण

	ar_ahb->mem_len = resource_size(res);

	ar_ahb->gcc_mem = ioremap(ATH10K_GCC_REG_BASE,
				  ATH10K_GCC_REG_SIZE);
	अगर (!ar_ahb->gcc_mem) अणु
		ath10k_err(ar, "gcc mem ioremap error\n");
		ret = -ENOMEM;
		जाओ err_mem_unmap;
	पूर्ण

	ar_ahb->tcsr_mem = ioremap(ATH10K_TCSR_REG_BASE,
				   ATH10K_TCSR_REG_SIZE);
	अगर (!ar_ahb->tcsr_mem) अणु
		ath10k_err(ar, "tcsr mem ioremap error\n");
		ret = -ENOMEM;
		जाओ err_gcc_mem_unmap;
	पूर्ण

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		ath10k_err(ar, "failed to set 32-bit dma mask: %d\n", ret);
		जाओ err_tcsr_mem_unmap;
	पूर्ण

	ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		ath10k_err(ar, "failed to set 32-bit consistent dma: %d\n",
			   ret);
		जाओ err_tcsr_mem_unmap;
	पूर्ण

	ret = ath10k_ahb_घड़ी_init(ar);
	अगर (ret)
		जाओ err_tcsr_mem_unmap;

	ret = ath10k_ahb_rst_ctrl_init(ar);
	अगर (ret)
		जाओ err_घड़ी_deinit;

	ar_ahb->irq = platक्रमm_get_irq_byname(pdev, "legacy");
	अगर (ar_ahb->irq < 0) अणु
		ath10k_err(ar, "failed to get irq number: %d\n", ar_ahb->irq);
		ret = ar_ahb->irq;
		जाओ err_घड़ी_deinit;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "irq: %d\n", ar_ahb->irq);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "mem: 0x%pK mem_len: %lu gcc mem: 0x%pK tcsr_mem: 0x%pK\n",
		   ar_ahb->mem, ar_ahb->mem_len,
		   ar_ahb->gcc_mem, ar_ahb->tcsr_mem);
	वापस 0;

err_घड़ी_deinit:
	ath10k_ahb_घड़ी_deinit(ar);

err_tcsr_mem_unmap:
	iounmap(ar_ahb->tcsr_mem);

err_gcc_mem_unmap:
	ar_ahb->tcsr_mem = शून्य;
	iounmap(ar_ahb->gcc_mem);

err_mem_unmap:
	ar_ahb->gcc_mem = शून्य;
	devm_iounmap(&pdev->dev, ar_ahb->mem);

out:
	ar_ahb->mem = शून्य;
	वापस ret;
पूर्ण

अटल व्योम ath10k_ahb_resource_deinit(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);
	काष्ठा device *dev;

	dev = &ar_ahb->pdev->dev;

	अगर (ar_ahb->mem)
		devm_iounmap(dev, ar_ahb->mem);

	अगर (ar_ahb->gcc_mem)
		iounmap(ar_ahb->gcc_mem);

	अगर (ar_ahb->tcsr_mem)
		iounmap(ar_ahb->tcsr_mem);

	ar_ahb->mem = शून्य;
	ar_ahb->gcc_mem = शून्य;
	ar_ahb->tcsr_mem = शून्य;

	ath10k_ahb_घड़ी_deinit(ar);
	ath10k_ahb_rst_ctrl_deinit(ar);
पूर्ण

अटल पूर्णांक ath10k_ahb_prepare_device(काष्ठा ath10k *ar)
अणु
	u32 val;
	पूर्णांक ret;

	ret = ath10k_ahb_घड़ी_enable(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable clocks\n");
		वापस ret;
	पूर्ण

	/* Clock क्रम the target is supplied from outside of target (ie,
	 * बाह्यal घड़ी module controlled by the host). Target needs
	 * to know what frequency target cpu is configured which is needed
	 * क्रम target पूर्णांकernal use. Read target cpu frequency info from
	 * gcc रेजिस्टर and ग_लिखो पूर्णांकo target's scratch रेजिस्टर where
	 * target expects this inक्रमmation.
	 */
	val = ath10k_ahb_gcc_पढ़ो32(ar, ATH10K_AHB_GCC_FEPLL_PLL_DIV);
	ath10k_ahb_ग_लिखो32(ar, ATH10K_AHB_WIFI_SCRATCH_5_REG, val);

	ret = ath10k_ahb_release_reset(ar);
	अगर (ret)
		जाओ err_clk_disable;

	ath10k_ahb_irq_disable(ar);

	ath10k_ahb_ग_लिखो32(ar, FW_INDICATOR_ADDRESS, FW_IND_HOST_READY);

	ret = ath10k_pci_रुको_क्रम_target_init(ar);
	अगर (ret)
		जाओ err_halt_chip;

	वापस 0;

err_halt_chip:
	ath10k_ahb_halt_chip(ar);

err_clk_disable:
	ath10k_ahb_घड़ी_disable(ar);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_ahb_chip_reset(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ath10k_ahb_halt_chip(ar);
	ath10k_ahb_घड़ी_disable(ar);

	ret = ath10k_ahb_prepare_device(ar);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_ahb_wake_target_cpu(काष्ठा ath10k *ar)
अणु
	u32 addr, val;

	addr = SOC_CORE_BASE_ADDRESS | CORE_CTRL_ADDRESS;
	val = ath10k_ahb_पढ़ो32(ar, addr);
	val |= ATH10K_AHB_CORE_CTRL_CPU_INTR_MASK;
	ath10k_ahb_ग_लिखो32(ar, addr, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_ahb_hअगर_start(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot ahb hif start\n");

	ath10k_core_napi_enable(ar);
	ath10k_ce_enable_पूर्णांकerrupts(ar);
	ath10k_pci_enable_legacy_irq(ar);

	ath10k_pci_rx_post(ar);

	वापस 0;
पूर्ण

अटल व्योम ath10k_ahb_hअगर_stop(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ahb *ar_ahb = ath10k_ahb_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot ahb hif stop\n");

	ath10k_ahb_irq_disable(ar);
	synchronize_irq(ar_ahb->irq);

	ath10k_core_napi_sync_disable(ar);

	ath10k_pci_flush(ar);
पूर्ण

अटल पूर्णांक ath10k_ahb_hअगर_घातer_up(काष्ठा ath10k *ar,
				   क्रमागत ath10k_firmware_mode fw_mode)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot ahb hif power up\n");

	ret = ath10k_ahb_chip_reset(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to reset chip: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = ath10k_pci_init_pipes(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to initialize CE: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = ath10k_pci_init_config(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to setup init config: %d\n", ret);
		जाओ err_ce_deinit;
	पूर्ण

	ret = ath10k_ahb_wake_target_cpu(ar);
	अगर (ret) अणु
		ath10k_err(ar, "could not wake up target CPU: %d\n", ret);
		जाओ err_ce_deinit;
	पूर्ण

	वापस 0;

err_ce_deinit:
	ath10k_pci_ce_deinit(ar);
out:
	वापस ret;
पूर्ण

अटल u32 ath10k_ahb_qca4019_targ_cpu_to_ce_addr(काष्ठा ath10k *ar, u32 addr)
अणु
	u32 val = 0, region = addr & 0xfffff;

	val = ath10k_pci_पढ़ो32(ar, PCIE_BAR_REG_ADDRESS);

	अगर (region >= QCA4019_SRAM_ADDR && region <=
	    (QCA4019_SRAM_ADDR + QCA4019_SRAM_LEN)) अणु
		/* SRAM contents क्रम QCA4019 can be directly accessed and
		 * no conversions are required
		 */
		val |= region;
	पूर्ण अन्यथा अणु
		val |= 0x100000 | region;
	पूर्ण

	वापस val;
पूर्ण

अटल स्थिर काष्ठा ath10k_hअगर_ops ath10k_ahb_hअगर_ops = अणु
	.tx_sg                  = ath10k_pci_hअगर_tx_sg,
	.diag_पढ़ो              = ath10k_pci_hअगर_diag_पढ़ो,
	.diag_ग_लिखो             = ath10k_pci_diag_ग_लिखो_mem,
	.exchange_bmi_msg       = ath10k_pci_hअगर_exchange_bmi_msg,
	.start                  = ath10k_ahb_hअगर_start,
	.stop                   = ath10k_ahb_hअगर_stop,
	.map_service_to_pipe    = ath10k_pci_hअगर_map_service_to_pipe,
	.get_शेष_pipe       = ath10k_pci_hअगर_get_शेष_pipe,
	.send_complete_check    = ath10k_pci_hअगर_send_complete_check,
	.get_मुक्त_queue_number  = ath10k_pci_hअगर_get_मुक्त_queue_number,
	.घातer_up               = ath10k_ahb_hअगर_घातer_up,
	.घातer_करोwn             = ath10k_pci_hअगर_घातer_करोwn,
	.पढ़ो32                 = ath10k_ahb_पढ़ो32,
	.ग_लिखो32                = ath10k_ahb_ग_लिखो32,
पूर्ण;

अटल स्थिर काष्ठा ath10k_bus_ops ath10k_ahb_bus_ops = अणु
	.पढ़ो32		= ath10k_ahb_पढ़ो32,
	.ग_लिखो32	= ath10k_ahb_ग_लिखो32,
	.get_num_banks	= ath10k_ahb_get_num_banks,
पूर्ण;

अटल पूर्णांक ath10k_ahb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ahb *ar_ahb;
	काष्ठा ath10k_pci *ar_pci;
	स्थिर काष्ठा of_device_id *of_id;
	क्रमागत ath10k_hw_rev hw_rev;
	माप_प्रकार size;
	पूर्णांक ret;
	काष्ठा ath10k_bus_params bus_params = अणुपूर्ण;

	of_id = of_match_device(ath10k_ahb_of_match, &pdev->dev);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "failed to find matching device tree id\n");
		वापस -EINVAL;
	पूर्ण

	hw_rev = (क्रमागत ath10k_hw_rev)of_id->data;

	size = माप(*ar_pci) + माप(*ar_ahb);
	ar = ath10k_core_create(size, &pdev->dev, ATH10K_BUS_AHB,
				hw_rev, &ath10k_ahb_hअगर_ops);
	अगर (!ar) अणु
		dev_err(&pdev->dev, "failed to allocate core\n");
		वापस -ENOMEM;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "ahb probe\n");

	ar_pci = ath10k_pci_priv(ar);
	ar_ahb = ath10k_ahb_priv(ar);

	ar_ahb->pdev = pdev;
	platक्रमm_set_drvdata(pdev, ar);

	ret = ath10k_ahb_resource_init(ar);
	अगर (ret)
		जाओ err_core_destroy;

	ar->dev_id = 0;
	ar_pci->mem = ar_ahb->mem;
	ar_pci->mem_len = ar_ahb->mem_len;
	ar_pci->ar = ar;
	ar_pci->ce.bus_ops = &ath10k_ahb_bus_ops;
	ar_pci->targ_cpu_to_ce_addr = ath10k_ahb_qca4019_targ_cpu_to_ce_addr;
	ar->ce_priv = &ar_pci->ce;

	ret = ath10k_pci_setup_resource(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to setup resource: %d\n", ret);
		जाओ err_resource_deinit;
	पूर्ण

	ath10k_pci_init_napi(ar);

	ret = ath10k_ahb_request_irq_legacy(ar);
	अगर (ret)
		जाओ err_मुक्त_pipes;

	ret = ath10k_ahb_prepare_device(ar);
	अगर (ret)
		जाओ err_मुक्त_irq;

	ath10k_pci_ce_deinit(ar);

	bus_params.dev_type = ATH10K_DEV_TYPE_LL;
	bus_params.chip_id = ath10k_ahb_soc_पढ़ो32(ar, SOC_CHIP_ID_ADDRESS);
	अगर (bus_params.chip_id == 0xffffffff) अणु
		ath10k_err(ar, "failed to get chip id\n");
		ret = -ENODEV;
		जाओ err_halt_device;
	पूर्ण

	ret = ath10k_core_रेजिस्टर(ar, &bus_params);
	अगर (ret) अणु
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		जाओ err_halt_device;
	पूर्ण

	वापस 0;

err_halt_device:
	ath10k_ahb_halt_chip(ar);
	ath10k_ahb_घड़ी_disable(ar);

err_मुक्त_irq:
	ath10k_ahb_release_irq_legacy(ar);

err_मुक्त_pipes:
	ath10k_pci_release_resource(ar);

err_resource_deinit:
	ath10k_ahb_resource_deinit(ar);

err_core_destroy:
	ath10k_core_destroy(ar);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_ahb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath10k *ar = platक्रमm_get_drvdata(pdev);
	काष्ठा ath10k_ahb *ar_ahb;

	अगर (!ar)
		वापस -EINVAL;

	ar_ahb = ath10k_ahb_priv(ar);

	अगर (!ar_ahb)
		वापस -EINVAL;

	ath10k_dbg(ar, ATH10K_DBG_AHB, "ahb remove\n");

	ath10k_core_unरेजिस्टर(ar);
	ath10k_ahb_irq_disable(ar);
	ath10k_ahb_release_irq_legacy(ar);
	ath10k_pci_release_resource(ar);
	ath10k_ahb_halt_chip(ar);
	ath10k_ahb_घड़ी_disable(ar);
	ath10k_ahb_resource_deinit(ar);
	ath10k_core_destroy(ar);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ath10k_ahb_driver = अणु
	.driver         = अणु
		.name   = "ath10k_ahb",
		.of_match_table = ath10k_ahb_of_match,
	पूर्ण,
	.probe  = ath10k_ahb_probe,
	.हटाओ = ath10k_ahb_हटाओ,
पूर्ण;

पूर्णांक ath10k_ahb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&ath10k_ahb_driver);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "failed to register ath10k ahb driver: %d\n",
		       ret);
	वापस ret;
पूर्ण

व्योम ath10k_ahb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ath10k_ahb_driver);
पूर्ण
