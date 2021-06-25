<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018, 2019 Cisco Systems
 */

#समावेश <linux/edac.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश "edac_module.h"


#घोषणा DRV_NAME "aspeed-edac"


#घोषणा ASPEED_MCR_PROT        0x00 /* protection key रेजिस्टर */
#घोषणा ASPEED_MCR_CONF        0x04 /* configuration रेजिस्टर */
#घोषणा ASPEED_MCR_INTR_CTRL   0x50 /* पूर्णांकerrupt control/status रेजिस्टर */
#घोषणा ASPEED_MCR_ADDR_UNREC  0x58 /* address of first un-recoverable error */
#घोषणा ASPEED_MCR_ADDR_REC    0x5c /* address of last recoverable error */
#घोषणा ASPEED_MCR_LAST        ASPEED_MCR_ADDR_REC


#घोषणा ASPEED_MCR_PROT_PASSWD	            0xfc600309
#घोषणा ASPEED_MCR_CONF_DRAM_TYPE               BIT(4)
#घोषणा ASPEED_MCR_CONF_ECC                     BIT(7)
#घोषणा ASPEED_MCR_INTR_CTRL_CLEAR             BIT(31)
#घोषणा ASPEED_MCR_INTR_CTRL_CNT_REC   GENMASK(23, 16)
#घोषणा ASPEED_MCR_INTR_CTRL_CNT_UNREC GENMASK(15, 12)
#घोषणा ASPEED_MCR_INTR_CTRL_ENABLE  (BIT(0) | BIT(1))


अटल काष्ठा regmap *aspeed_regmap;


अटल पूर्णांक regmap_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	व्योम __iomem *regs = (व्योम __iomem *)context;

	/* enable ग_लिखो to MCR रेजिस्टर set */
	ग_लिखोl(ASPEED_MCR_PROT_PASSWD, regs + ASPEED_MCR_PROT);

	ग_लिखोl(val, regs + reg);

	/* disable ग_लिखो to MCR रेजिस्टर set */
	ग_लिखोl(~ASPEED_MCR_PROT_PASSWD, regs + ASPEED_MCR_PROT);

	वापस 0;
पूर्ण


अटल पूर्णांक regmap_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	व्योम __iomem *regs = (व्योम __iomem *)context;

	*val = पढ़ोl(regs + reg);

	वापस 0;
पूर्ण

अटल bool regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ASPEED_MCR_PROT:
	हाल ASPEED_MCR_INTR_CTRL:
	हाल ASPEED_MCR_ADDR_UNREC:
	हाल ASPEED_MCR_ADDR_REC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा regmap_config aspeed_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = ASPEED_MCR_LAST,
	.reg_ग_लिखो = regmap_reg_ग_लिखो,
	.reg_पढ़ो = regmap_reg_पढ़ो,
	.अस्थिर_reg = regmap_is_अस्थिर,
	.fast_io = true,
पूर्ण;


अटल व्योम count_rec(काष्ठा mem_ctl_info *mci, u8 rec_cnt, u32 rec_addr)
अणु
	काष्ठा csrow_info *csrow = mci->csrows[0];
	u32 page, offset, syndrome;

	अगर (!rec_cnt)
		वापस;

	/* report first few errors (अगर there are) */
	/* note: no addresses are recorded */
	अगर (rec_cnt > 1) अणु
		/* page, offset and syndrome are not available */
		page = 0;
		offset = 0;
		syndrome = 0;
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, rec_cnt-1,
				     page, offset, syndrome, 0, 0, -1,
				     "address(es) not available", "");
	पूर्ण

	/* report last error */
	/* note: rec_addr is the last recoverable error addr */
	page = rec_addr >> PAGE_SHIFT;
	offset = rec_addr & ~PAGE_MASK;
	/* syndrome is not available */
	syndrome = 0;
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     csrow->first_page + page, offset, syndrome,
			     0, 0, -1, "", "");
पूर्ण


अटल व्योम count_un_rec(काष्ठा mem_ctl_info *mci, u8 un_rec_cnt,
			 u32 un_rec_addr)
अणु
	काष्ठा csrow_info *csrow = mci->csrows[0];
	u32 page, offset, syndrome;

	अगर (!un_rec_cnt)
		वापस;

	/* report 1. error */
	/* note: un_rec_addr is the first unrecoverable error addr */
	page = un_rec_addr >> PAGE_SHIFT;
	offset = un_rec_addr & ~PAGE_MASK;
	/* syndrome is not available */
	syndrome = 0;
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
			     csrow->first_page + page, offset, syndrome,
			     0, 0, -1, "", "");

	/* report further errors (अगर there are) */
	/* note: no addresses are recorded */
	अगर (un_rec_cnt > 1) अणु
		/* page, offset and syndrome are not available */
		page = 0;
		offset = 0;
		syndrome = 0;
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, un_rec_cnt-1,
				     page, offset, syndrome, 0, 0, -1,
				     "address(es) not available", "");
	पूर्ण
पूर्ण


अटल irqवापस_t mcr_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा mem_ctl_info *mci = arg;
	u32 rec_addr, un_rec_addr;
	u32 reg50, reg5c, reg58;
	u8  rec_cnt, un_rec_cnt;

	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_INTR_CTRL, &reg50);
	dev_dbg(mci->pdev, "received edac interrupt w/ mcr register 50: 0x%x\n",
		reg50);

	/* collect data about recoverable and unrecoverable errors */
	rec_cnt = (reg50 & ASPEED_MCR_INTR_CTRL_CNT_REC) >> 16;
	un_rec_cnt = (reg50 & ASPEED_MCR_INTR_CTRL_CNT_UNREC) >> 12;

	dev_dbg(mci->pdev, "%d recoverable interrupts and %d unrecoverable interrupts\n",
		rec_cnt, un_rec_cnt);

	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_ADDR_UNREC, &reg58);
	un_rec_addr = reg58;

	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_ADDR_REC, &reg5c);
	rec_addr = reg5c;

	/* clear पूर्णांकerrupt flags and error counters: */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_CLEAR,
			   ASPEED_MCR_INTR_CTRL_CLEAR);

	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_CLEAR, 0);

	/* process recoverable and unrecoverable errors */
	count_rec(mci, rec_cnt, rec_addr);
	count_un_rec(mci, un_rec_cnt, un_rec_addr);

	अगर (!rec_cnt && !un_rec_cnt)
		dev_dbg(mci->pdev, "received edac interrupt, but did not find any ECC counters\n");

	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_INTR_CTRL, &reg50);
	dev_dbg(mci->pdev, "edac interrupt handled. mcr reg 50 is now: 0x%x\n",
		reg50);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक config_irq(व्योम *ctx, काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq;
	पूर्णांक rc;

	/* रेजिस्टर पूर्णांकerrupt handler */
	irq = platक्रमm_get_irq(pdev, 0);
	dev_dbg(&pdev->dev, "got irq %d\n", irq);
	अगर (irq < 0)
		वापस irq;

	rc = devm_request_irq(&pdev->dev, irq, mcr_isr, IRQF_TRIGGER_HIGH,
			      DRV_NAME, ctx);
	अगर (rc) अणु
		dev_err(&pdev->dev, "unable to request irq %d\n", irq);
		वापस rc;
	पूर्ण

	/* enable पूर्णांकerrupts */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_ENABLE,
			   ASPEED_MCR_INTR_CTRL_ENABLE);

	वापस 0;
पूर्ण


अटल पूर्णांक init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा csrow_info *csrow = mci->csrows[0];
	u32 nr_pages, dram_type;
	काष्ठा dimm_info *dimm;
	काष्ठा device_node *np;
	काष्ठा resource r;
	u32 reg04;
	पूर्णांक rc;

	/* retrieve info about physical memory from device tree */
	np = of_find_node_by_name(शून्य, "memory");
	अगर (!np) अणु
		dev_err(mci->pdev, "dt: missing /memory node\n");
		वापस -ENODEV;
	पूर्ण

	rc = of_address_to_resource(np, 0, &r);

	of_node_put(np);

	अगर (rc) अणु
		dev_err(mci->pdev, "dt: failed requesting resource for /memory node\n");
		वापस rc;
	पूर्ण

	dev_dbg(mci->pdev, "dt: /memory node resources: first page r.start=0x%x, resource_size=0x%x, PAGE_SHIFT macro=0x%x\n",
		r.start, resource_size(&r), PAGE_SHIFT);

	csrow->first_page = r.start >> PAGE_SHIFT;
	nr_pages = resource_size(&r) >> PAGE_SHIFT;
	csrow->last_page = csrow->first_page + nr_pages - 1;

	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_CONF, &reg04);
	dram_type = (reg04 & ASPEED_MCR_CONF_DRAM_TYPE) ? MEM_DDR4 : MEM_DDR3;

	dimm = csrow->channels[0]->dimm;
	dimm->mtype = dram_type;
	dimm->edac_mode = EDAC_SECDED;
	dimm->nr_pages = nr_pages / csrow->nr_channels;

	dev_dbg(mci->pdev, "initialized dimm with first_page=0x%lx and nr_pages=0x%x\n",
		csrow->first_page, nr_pages);

	वापस 0;
पूर्ण


अटल पूर्णांक aspeed_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा mem_ctl_info *mci;
	व्योम __iomem *regs;
	u32 reg04;
	पूर्णांक rc;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	aspeed_regmap = devm_regmap_init(dev, शून्य, (__क्रमce व्योम *)regs,
					 &aspeed_regmap_config);
	अगर (IS_ERR(aspeed_regmap))
		वापस PTR_ERR(aspeed_regmap);

	/* bail out अगर ECC mode is not configured */
	regmap_पढ़ो(aspeed_regmap, ASPEED_MCR_CONF, &reg04);
	अगर (!(reg04 & ASPEED_MCR_CONF_ECC)) अणु
		dev_err(&pdev->dev, "ECC mode is not configured in u-boot\n");
		वापस -EPERM;
	पूर्ण

	edac_op_state = EDAC_OPSTATE_INT;

	/* allocate & init EDAC MC data काष्ठाure */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 1;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 1;
	layers[1].is_virt_csrow = false;

	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);
	अगर (!mci)
		वापस -ENOMEM;

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR3 | MEM_FLAG_DDR4;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->scrub_cap = SCRUB_FLAG_HW_SRC;
	mci->scrub_mode = SCRUB_HW_SRC;
	mci->mod_name = DRV_NAME;
	mci->ctl_name = "MIC";
	mci->dev_name = dev_name(&pdev->dev);

	rc = init_csrows(mci);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to init csrows\n");
		जाओ probe_निकास02;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mci);

	/* रेजिस्टर with edac core */
	rc = edac_mc_add_mc(mci);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to register with EDAC core\n");
		जाओ probe_निकास02;
	पूर्ण

	/* रेजिस्टर पूर्णांकerrupt handler and enable पूर्णांकerrupts */
	rc = config_irq(mci, pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed setting up irq\n");
		जाओ probe_निकास01;
	पूर्ण

	वापस 0;

probe_निकास01:
	edac_mc_del_mc(&pdev->dev);
probe_निकास02:
	edac_mc_मुक्त(mci);
	वापस rc;
पूर्ण


अटल पूर्णांक aspeed_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	/* disable पूर्णांकerrupts */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_ENABLE, 0);

	/* मुक्त resources */
	mci = edac_mc_del_mc(&pdev->dev);
	अगर (mci)
		edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id aspeed_of_match[] = अणु
	अणु .compatible = "aspeed,ast2400-sdram-edac" पूर्ण,
	अणु .compatible = "aspeed,ast2500-sdram-edac" पूर्ण,
	अणु .compatible = "aspeed,ast2600-sdram-edac" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, aspeed_of_match);

अटल काष्ठा platक्रमm_driver aspeed_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = aspeed_of_match
	पूर्ण,
	.probe		= aspeed_probe,
	.हटाओ		= aspeed_हटाओ
पूर्ण;
module_platक्रमm_driver(aspeed_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefan Schaeckeler <sschaeck@cisco.com>");
MODULE_DESCRIPTION("Aspeed BMC SoC EDAC driver");
MODULE_VERSION("1.0");
