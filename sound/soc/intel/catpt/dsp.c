<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/devcoredump.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/pxa2xx_ssp.h>
#समावेश "core.h"
#समावेश "messages.h"
#समावेश "registers.h"

अटल bool catpt_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस param == chan->device->dev;
पूर्ण

/*
 * Either engine 0 or 1 can be used क्रम image loading.
 * Align with Winकरोws driver equivalent and stick to engine 1.
 */
#घोषणा CATPT_DMA_DEVID		1
#घोषणा CATPT_DMA_DSP_ADDR_MASK	GENMASK(31, 20)

काष्ठा dma_chan *catpt_dma_request_config_chan(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा dma_slave_config config;
	काष्ठा dma_chan *chan;
	dma_cap_mask_t mask;
	पूर्णांक ret;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	chan = dma_request_channel(mask, catpt_dma_filter, cdev->dev);
	अगर (!chan) अणु
		dev_err(cdev->dev, "request channel failed\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.direction = DMA_MEM_TO_DEV;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.src_maxburst = 16;
	config.dst_maxburst = 16;

	ret = dmaengine_slave_config(chan, &config);
	अगर (ret) अणु
		dev_err(cdev->dev, "slave config failed: %d\n", ret);
		dma_release_channel(chan);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस chan;
पूर्ण

अटल पूर्णांक catpt_dma_स_नकल(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			    dma_addr_t dst_addr, dma_addr_t src_addr,
			    माप_प्रकार size)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	क्रमागत dma_status status;

	desc = dmaengine_prep_dma_स_नकल(chan, dst_addr, src_addr, size,
					 DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(cdev->dev, "prep dma memcpy failed\n");
		वापस -EIO;
	पूर्ण

	/* enable demand mode क्रम dma channel */
	catpt_updatel_shim(cdev, HMDC,
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id),
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id));
	dmaengine_submit(desc);
	status = dma_रुको_क्रम_async_tx(desc);
	/* regardless of status, disable access to HOST memory in demand mode */
	catpt_updatel_shim(cdev, HMDC,
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id), 0);

	वापस (status == DMA_COMPLETE) ? 0 : -EPROTO;
पूर्ण

पूर्णांक catpt_dma_स_नकल_todsp(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			   dma_addr_t dst_addr, dma_addr_t src_addr,
			   माप_प्रकार size)
अणु
	वापस catpt_dma_स_नकल(cdev, chan, dst_addr | CATPT_DMA_DSP_ADDR_MASK,
				src_addr, size);
पूर्ण

पूर्णांक catpt_dma_स_नकल_fromdsp(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			     dma_addr_t dst_addr, dma_addr_t src_addr,
			     माप_प्रकार size)
अणु
	वापस catpt_dma_स_नकल(cdev, chan, dst_addr,
				src_addr | CATPT_DMA_DSP_ADDR_MASK, size);
पूर्ण

पूर्णांक catpt_dmac_probe(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा dw_dma_chip *dmac;
	पूर्णांक ret;

	dmac = devm_kzalloc(cdev->dev, माप(*dmac), GFP_KERNEL);
	अगर (!dmac)
		वापस -ENOMEM;

	dmac->regs = cdev->lpe_ba + cdev->spec->host_dma_offset[CATPT_DMA_DEVID];
	dmac->dev = cdev->dev;
	dmac->irq = cdev->irq;

	ret = dma_coerce_mask_and_coherent(cdev->dev, DMA_BIT_MASK(31));
	अगर (ret)
		वापस ret;
	/*
	 * Caller is responsible क्रम putting device in D0 to allow
	 * क्रम I/O and memory access beक्रमe probing DW.
	 */
	ret = dw_dma_probe(dmac);
	अगर (ret)
		वापस ret;

	cdev->dmac = dmac;
	वापस 0;
पूर्ण

व्योम catpt_dmac_हटाओ(काष्ठा catpt_dev *cdev)
अणु
	/*
	 * As करो_dma_हटाओ() juggles with pm_runसमय_get_xxx() and
	 * pm_runसमय_put_xxx() जबतक both ADSP and DW 'devices' are part of
	 * the same module, caller makes sure pm_runसमय_disable() is invoked
	 * beक्रमe removing DW to prevent posपंचांगortem resume and suspend.
	 */
	dw_dma_हटाओ(cdev->dmac);
पूर्ण

अटल व्योम catpt_dsp_set_srampge(काष्ठा catpt_dev *cdev, काष्ठा resource *sram,
				  अचिन्हित दीर्घ mask, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ old;
	u32 off = sram->start;
	u32 b = __ffs(mask);

	old = catpt_पढ़ोl_pci(cdev, VDRTCTL0) & mask;
	dev_dbg(cdev->dev, "SRAMPGE [0x%08lx] 0x%08lx -> 0x%08lx",
		mask, old, new);

	अगर (old == new)
		वापस;

	catpt_updatel_pci(cdev, VDRTCTL0, mask, new);
	/* रुको क्रम SRAM घातer gating to propagate */
	udelay(60);

	/*
	 * Dummy पढ़ो as the very first access after block enable
	 * to prevent byte loss in future operations.
	 */
	क्रम_each_clear_bit_from(b, &new, fls_दीर्घ(mask)) अणु
		u8 buf[4];

		/* newly enabled: new bit=0 जबतक old bit=1 */
		अगर (test_bit(b, &old)) अणु
			dev_dbg(cdev->dev, "sanitize block %ld: off 0x%08x\n",
				b - __ffs(mask), off);
			स_नकल_fromio(buf, cdev->lpe_ba + off, माप(buf));
		पूर्ण
		off += CATPT_MEMBLOCK_SIZE;
	पूर्ण
पूर्ण

व्योम catpt_dsp_update_srampge(काष्ठा catpt_dev *cdev, काष्ठा resource *sram,
			      अचिन्हित दीर्घ mask)
अणु
	काष्ठा resource *res;
	अचिन्हित दीर्घ new = 0;

	/* flag all busy blocks */
	क्रम (res = sram->child; res; res = res->sibling) अणु
		u32 h, l;

		h = (res->end - sram->start) / CATPT_MEMBLOCK_SIZE;
		l = (res->start - sram->start) / CATPT_MEMBLOCK_SIZE;
		new |= GENMASK(h, l);
	पूर्ण

	/* offset value given mask's start and invert it as ON=b0 */
	new = ~(new << __ffs(mask)) & mask;

	/* disable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE, 0);

	catpt_dsp_set_srampge(cdev, sram, mask, new);

	/* enable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE,
			  CATPT_VDRTCTL2_DCLCGE);
पूर्ण

पूर्णांक catpt_dsp_stall(काष्ठा catpt_dev *cdev, bool stall)
अणु
	u32 reg, val;

	val = stall ? CATPT_CS_STALL : 0;
	catpt_updatel_shim(cdev, CS1, CATPT_CS_STALL, val);

	वापस catpt_पढ़ोl_poll_shim(cdev, CS1,
				     reg, (reg & CATPT_CS_STALL) == val,
				     500, 10000);
पूर्ण

अटल पूर्णांक catpt_dsp_reset(काष्ठा catpt_dev *cdev, bool reset)
अणु
	u32 reg, val;

	val = reset ? CATPT_CS_RST : 0;
	catpt_updatel_shim(cdev, CS1, CATPT_CS_RST, val);

	वापस catpt_पढ़ोl_poll_shim(cdev, CS1,
				     reg, (reg & CATPT_CS_RST) == val,
				     500, 10000);
पूर्ण

व्योम lpt_dsp_pll_shutकरोwn(काष्ठा catpt_dev *cdev, bool enable)
अणु
	u32 val;

	val = enable ? LPT_VDRTCTL0_APLLSE : 0;
	catpt_updatel_pci(cdev, VDRTCTL0, LPT_VDRTCTL0_APLLSE, val);
पूर्ण

व्योम wpt_dsp_pll_shutकरोwn(काष्ठा catpt_dev *cdev, bool enable)
अणु
	u32 val;

	val = enable ? WPT_VDRTCTL2_APLLSE : 0;
	catpt_updatel_pci(cdev, VDRTCTL2, WPT_VDRTCTL2_APLLSE, val);
पूर्ण

अटल पूर्णांक catpt_dsp_select_lpघड़ी(काष्ठा catpt_dev *cdev, bool lp, bool रुकोi)
अणु
	u32 mask, reg, val;
	पूर्णांक ret;

	mutex_lock(&cdev->clk_mutex);

	val = lp ? CATPT_CS_LPCS : 0;
	reg = catpt_पढ़ोl_shim(cdev, CS1) & CATPT_CS_LPCS;
	dev_dbg(cdev->dev, "LPCS [0x%08lx] 0x%08x -> 0x%08x",
		CATPT_CS_LPCS, reg, val);

	अगर (reg == val) अणु
		mutex_unlock(&cdev->clk_mutex);
		वापस 0;
	पूर्ण

	अगर (रुकोi) अणु
		/* रुको क्रम DSP to संकेत WAIT state */
		ret = catpt_पढ़ोl_poll_shim(cdev, ISD,
					    reg, (reg & CATPT_ISD_DCPWM),
					    500, 10000);
		अगर (ret) अणु
			dev_warn(cdev->dev, "await WAITI timeout\n");
			/* no संकेत - only high घड़ी selection allowed */
			अगर (lp) अणु
				mutex_unlock(&cdev->clk_mutex);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = catpt_पढ़ोl_poll_shim(cdev, CLKCTL,
				    reg, !(reg & CATPT_CLKCTL_CFCIP),
				    500, 10000);
	अगर (ret)
		dev_warn(cdev->dev, "clock change still in progress\n");

	/* शेष to DSP core & audio fabric high घड़ी */
	val |= CATPT_CS_DCS_HIGH;
	mask = CATPT_CS_LPCS | CATPT_CS_DCS;
	catpt_updatel_shim(cdev, CS1, mask, val);

	ret = catpt_पढ़ोl_poll_shim(cdev, CLKCTL,
				    reg, !(reg & CATPT_CLKCTL_CFCIP),
				    500, 10000);
	अगर (ret)
		dev_warn(cdev->dev, "clock change still in progress\n");

	/* update PLL accordingly */
	cdev->spec->pll_shutकरोwn(cdev, lp);

	mutex_unlock(&cdev->clk_mutex);
	वापस 0;
पूर्ण

पूर्णांक catpt_dsp_update_lpघड़ी(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा catpt_stream_runसमय *stream;

	list_क्रम_each_entry(stream, &cdev->stream_list, node)
		अगर (stream->prepared)
			वापस catpt_dsp_select_lpघड़ी(cdev, false, true);

	वापस catpt_dsp_select_lpघड़ी(cdev, true, true);
पूर्ण

/* bring रेजिस्टरs to their शेषs as HW won't reset itself */
अटल व्योम catpt_dsp_set_regs_शेषs(काष्ठा catpt_dev *cdev)
अणु
	पूर्णांक i;

	catpt_ग_लिखोl_shim(cdev, CS1, CATPT_CS_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, ISC, CATPT_ISC_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, ISD, CATPT_ISD_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, IMC, CATPT_IMC_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, IMD, CATPT_IMD_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, IPCC, CATPT_IPCC_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, IPCD, CATPT_IPCD_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, CLKCTL, CATPT_CLKCTL_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, CS2, CATPT_CS2_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, LTRC, CATPT_LTRC_DEFAULT);
	catpt_ग_लिखोl_shim(cdev, HMDC, CATPT_HMDC_DEFAULT);

	क्रम (i = 0; i < CATPT_SSP_COUNT; i++) अणु
		catpt_ग_लिखोl_ssp(cdev, i, SSCR0, CATPT_SSC0_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSCR1, CATPT_SSC1_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSSR, CATPT_SSS_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSITR, CATPT_SSIT_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSDR, CATPT_SSD_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSTO, CATPT_SSTO_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSPSP, CATPT_SSPSP_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSTSA, CATPT_SSTSA_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSRSA, CATPT_SSRSA_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSTSS, CATPT_SSTSS_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSCR2, CATPT_SSCR2_DEFAULT);
		catpt_ग_लिखोl_ssp(cdev, i, SSPSP2, CATPT_SSPSP2_DEFAULT);
	पूर्ण
पूर्ण

पूर्णांक catpt_dsp_घातer_करोwn(काष्ठा catpt_dev *cdev)
अणु
	u32 mask, val;

	/* disable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE, 0);

	catpt_dsp_reset(cdev, true);
	/* set 24Mhz घड़ी क्रम both SSPs */
	catpt_updatel_shim(cdev, CS1, CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1),
			   CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1));
	catpt_dsp_select_lpघड़ी(cdev, true, false);
	/* disable MCLK */
	catpt_updatel_shim(cdev, CLKCTL, CATPT_CLKCTL_SMOS, 0);

	catpt_dsp_set_regs_शेषs(cdev);

	/* चयन घड़ी gating */
	mask = CATPT_VDRTCTL2_CGEALL & (~CATPT_VDRTCTL2_DCLCGE);
	val = mask & (~CATPT_VDRTCTL2_DTCGE);
	catpt_updatel_pci(cdev, VDRTCTL2, mask, val);
	/* enable DTCGE separatelly */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DTCGE,
			  CATPT_VDRTCTL2_DTCGE);

	/* SRAM घातer gating all */
	catpt_dsp_set_srampge(cdev, &cdev->dram, cdev->spec->dram_mask,
			      cdev->spec->dram_mask);
	catpt_dsp_set_srampge(cdev, &cdev->iram, cdev->spec->iram_mask,
			      cdev->spec->iram_mask);
	mask = cdev->spec->d3srampgd_bit | cdev->spec->d3pgd_bit;
	catpt_updatel_pci(cdev, VDRTCTL0, mask, cdev->spec->d3pgd_bit);

	catpt_updatel_pci(cdev, PMCS, PCI_PM_CTRL_STATE_MASK, PCI_D3hot);
	/* give hw समय to drop off */
	udelay(50);

	/* enable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE,
			  CATPT_VDRTCTL2_DCLCGE);
	udelay(50);

	वापस 0;
पूर्ण

पूर्णांक catpt_dsp_घातer_up(काष्ठा catpt_dev *cdev)
अणु
	u32 mask, val;

	/* disable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE, 0);

	/* चयन घड़ी gating */
	mask = CATPT_VDRTCTL2_CGEALL & (~CATPT_VDRTCTL2_DCLCGE);
	val = mask & (~CATPT_VDRTCTL2_DTCGE);
	catpt_updatel_pci(cdev, VDRTCTL2, mask, val);

	catpt_updatel_pci(cdev, PMCS, PCI_PM_CTRL_STATE_MASK, PCI_D0);

	/* SRAM घातer gating none */
	mask = cdev->spec->d3srampgd_bit | cdev->spec->d3pgd_bit;
	catpt_updatel_pci(cdev, VDRTCTL0, mask, mask);
	catpt_dsp_set_srampge(cdev, &cdev->dram, cdev->spec->dram_mask, 0);
	catpt_dsp_set_srampge(cdev, &cdev->iram, cdev->spec->iram_mask, 0);

	catpt_dsp_set_regs_शेषs(cdev);

	/* restore MCLK */
	catpt_updatel_shim(cdev, CLKCTL, CATPT_CLKCTL_SMOS, CATPT_CLKCTL_SMOS);
	catpt_dsp_select_lpघड़ी(cdev, false, false);
	/* set 24Mhz घड़ी क्रम both SSPs */
	catpt_updatel_shim(cdev, CS1, CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1),
			   CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1));
	catpt_dsp_reset(cdev, false);

	/* enable core घड़ी gating */
	catpt_updatel_pci(cdev, VDRTCTL2, CATPT_VDRTCTL2_DCLCGE,
			  CATPT_VDRTCTL2_DCLCGE);

	/* generate पूर्णांक deनिश्चित msg to fix inversed पूर्णांक logic */
	catpt_updatel_shim(cdev, IMC, CATPT_IMC_IPCDB | CATPT_IMC_IPCCD, 0);

	वापस 0;
पूर्ण

#घोषणा CATPT_DUMP_MAGIC		0xcd42
#घोषणा CATPT_DUMP_SECTION_ID_खाता	0x00
#घोषणा CATPT_DUMP_SECTION_ID_IRAM	0x01
#घोषणा CATPT_DUMP_SECTION_ID_DRAM	0x02
#घोषणा CATPT_DUMP_SECTION_ID_REGS	0x03
#घोषणा CATPT_DUMP_HASH_SIZE		20

काष्ठा catpt_dump_section_hdr अणु
	u16 magic;
	u8 core_id;
	u8 section_id;
	u32 size;
पूर्ण;

पूर्णांक catpt_coredump(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा catpt_dump_section_hdr *hdr;
	माप_प्रकार dump_size, regs_size;
	u8 *dump, *pos;
	स्थिर अक्षर *eof;
	अक्षर *info;
	पूर्णांक i;

	regs_size = CATPT_SHIM_REGS_SIZE;
	regs_size += CATPT_DMA_COUNT * CATPT_DMA_REGS_SIZE;
	regs_size += CATPT_SSP_COUNT * CATPT_SSP_REGS_SIZE;
	dump_size = resource_size(&cdev->dram);
	dump_size += resource_size(&cdev->iram);
	dump_size += regs_size;
	/* account क्रम header of each section and hash chunk */
	dump_size += 4 * माप(*hdr) + CATPT_DUMP_HASH_SIZE;

	dump = vzalloc(dump_size);
	अगर (!dump)
		वापस -ENOMEM;

	pos = dump;

	hdr = (काष्ठा catpt_dump_section_hdr *)pos;
	hdr->magic = CATPT_DUMP_MAGIC;
	hdr->core_id = cdev->spec->core_id;
	hdr->section_id = CATPT_DUMP_SECTION_ID_खाता;
	hdr->size = dump_size - माप(*hdr);
	pos += माप(*hdr);

	info = cdev->ipc.config.fw_info;
	eof = info + FW_INFO_SIZE_MAX;
	/* navigate to fअगरth info segment (fw hash) */
	क्रम (i = 0; i < 4 && info < eof; i++, info++) अणु
		/* info segments are separated by space each */
		info = strnchr(info, eof - info, ' ');
		अगर (!info)
			अवरोध;
	पूर्ण

	अगर (i == 4 && info)
		स_नकल(pos, info, min_t(u32, eof - info, CATPT_DUMP_HASH_SIZE));
	pos += CATPT_DUMP_HASH_SIZE;

	hdr = (काष्ठा catpt_dump_section_hdr *)pos;
	hdr->magic = CATPT_DUMP_MAGIC;
	hdr->core_id = cdev->spec->core_id;
	hdr->section_id = CATPT_DUMP_SECTION_ID_IRAM;
	hdr->size = resource_size(&cdev->iram);
	pos += माप(*hdr);

	स_नकल_fromio(pos, cdev->lpe_ba + cdev->iram.start, hdr->size);
	pos += hdr->size;

	hdr = (काष्ठा catpt_dump_section_hdr *)pos;
	hdr->magic = CATPT_DUMP_MAGIC;
	hdr->core_id = cdev->spec->core_id;
	hdr->section_id = CATPT_DUMP_SECTION_ID_DRAM;
	hdr->size = resource_size(&cdev->dram);
	pos += माप(*hdr);

	स_नकल_fromio(pos, cdev->lpe_ba + cdev->dram.start, hdr->size);
	pos += hdr->size;

	hdr = (काष्ठा catpt_dump_section_hdr *)pos;
	hdr->magic = CATPT_DUMP_MAGIC;
	hdr->core_id = cdev->spec->core_id;
	hdr->section_id = CATPT_DUMP_SECTION_ID_REGS;
	hdr->size = regs_size;
	pos += माप(*hdr);

	स_नकल_fromio(pos, catpt_shim_addr(cdev), CATPT_SHIM_REGS_SIZE);
	pos += CATPT_SHIM_REGS_SIZE;

	क्रम (i = 0; i < CATPT_SSP_COUNT; i++) अणु
		स_नकल_fromio(pos, catpt_ssp_addr(cdev, i),
			      CATPT_SSP_REGS_SIZE);
		pos += CATPT_SSP_REGS_SIZE;
	पूर्ण
	क्रम (i = 0; i < CATPT_DMA_COUNT; i++) अणु
		स_नकल_fromio(pos, catpt_dma_addr(cdev, i),
			      CATPT_DMA_REGS_SIZE);
		pos += CATPT_DMA_REGS_SIZE;
	पूर्ण

	dev_coredumpv(cdev->dev, dump, dump_size, GFP_KERNEL);

	वापस 0;
पूर्ण
