<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/edac.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश "edac_module.h"

/* Registers Offset */
#घोषणा AL_MC_ECC_CFG		0x70
#घोषणा AL_MC_ECC_CLEAR		0x7c
#घोषणा AL_MC_ECC_ERR_COUNT	0x80
#घोषणा AL_MC_ECC_CE_ADDR0	0x84
#घोषणा AL_MC_ECC_CE_ADDR1	0x88
#घोषणा AL_MC_ECC_UE_ADDR0	0xa4
#घोषणा AL_MC_ECC_UE_ADDR1	0xa8
#घोषणा AL_MC_ECC_CE_SYND0	0x8c
#घोषणा AL_MC_ECC_CE_SYND1	0x90
#घोषणा AL_MC_ECC_CE_SYND2	0x94
#घोषणा AL_MC_ECC_UE_SYND0	0xac
#घोषणा AL_MC_ECC_UE_SYND1	0xb0
#घोषणा AL_MC_ECC_UE_SYND2	0xb4

/* Registers Fields */
#घोषणा AL_MC_ECC_CFG_SCRUB_DISABLED	BIT(4)

#घोषणा AL_MC_ECC_CLEAR_UE_COUNT	BIT(3)
#घोषणा AL_MC_ECC_CLEAR_CE_COUNT	BIT(2)
#घोषणा AL_MC_ECC_CLEAR_UE_ERR		BIT(1)
#घोषणा AL_MC_ECC_CLEAR_CE_ERR		BIT(0)

#घोषणा AL_MC_ECC_ERR_COUNT_UE		GENMASK(31, 16)
#घोषणा AL_MC_ECC_ERR_COUNT_CE		GENMASK(15, 0)

#घोषणा AL_MC_ECC_CE_ADDR0_RANK		GENMASK(25, 24)
#घोषणा AL_MC_ECC_CE_ADDR0_ROW		GENMASK(17, 0)

#घोषणा AL_MC_ECC_CE_ADDR1_BG		GENMASK(25, 24)
#घोषणा AL_MC_ECC_CE_ADDR1_BANK		GENMASK(18, 16)
#घोषणा AL_MC_ECC_CE_ADDR1_COLUMN	GENMASK(11, 0)

#घोषणा AL_MC_ECC_UE_ADDR0_RANK		GENMASK(25, 24)
#घोषणा AL_MC_ECC_UE_ADDR0_ROW		GENMASK(17, 0)

#घोषणा AL_MC_ECC_UE_ADDR1_BG		GENMASK(25, 24)
#घोषणा AL_MC_ECC_UE_ADDR1_BANK		GENMASK(18, 16)
#घोषणा AL_MC_ECC_UE_ADDR1_COLUMN	GENMASK(11, 0)

#घोषणा DRV_NAME "al_mc_edac"
#घोषणा AL_MC_EDAC_MSG_MAX 256

काष्ठा al_mc_edac अणु
	व्योम __iomem *mmio_base;
	spinlock_t lock;
	पूर्णांक irq_ce;
	पूर्णांक irq_ue;
पूर्ण;

अटल व्योम prepare_msg(अक्षर *message, माप_प्रकार buffer_size,
			क्रमागत hw_event_mc_err_type type,
			u8 rank, u32 row, u8 bg, u8 bank, u16 column,
			u32 syn0, u32 syn1, u32 syn2)
अणु
	snम_लिखो(message, buffer_size,
		 "%s rank=0x%x row=0x%x bg=0x%x bank=0x%x col=0x%x syn0: 0x%x syn1: 0x%x syn2: 0x%x",
		 type == HW_EVENT_ERR_UNCORRECTED ? "UE" : "CE",
		 rank, row, bg, bank, column, syn0, syn1, syn2);
पूर्ण

अटल पूर्णांक handle_ce(काष्ठा mem_ctl_info *mci)
अणु
	u32 eccerrcnt, ecccaddr0, ecccaddr1, ecccsyn0, ecccsyn1, ecccsyn2, row;
	काष्ठा al_mc_edac *al_mc = mci->pvt_info;
	अक्षर msg[AL_MC_EDAC_MSG_MAX];
	u16 ce_count, column;
	अचिन्हित दीर्घ flags;
	u8 rank, bg, bank;

	eccerrcnt = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_ERR_COUNT);
	ce_count = FIELD_GET(AL_MC_ECC_ERR_COUNT_CE, eccerrcnt);
	अगर (!ce_count)
		वापस 0;

	ecccaddr0 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_CE_ADDR0);
	ecccaddr1 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_CE_ADDR1);
	ecccsyn0 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_CE_SYND0);
	ecccsyn1 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_CE_SYND1);
	ecccsyn2 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_CE_SYND2);

	ग_लिखोl_relaxed(AL_MC_ECC_CLEAR_CE_COUNT | AL_MC_ECC_CLEAR_CE_ERR,
		       al_mc->mmio_base + AL_MC_ECC_CLEAR);

	dev_dbg(mci->pdev, "eccuaddr0=0x%08x eccuaddr1=0x%08x\n",
		ecccaddr0, ecccaddr1);

	rank = FIELD_GET(AL_MC_ECC_CE_ADDR0_RANK, ecccaddr0);
	row = FIELD_GET(AL_MC_ECC_CE_ADDR0_ROW, ecccaddr0);

	bg = FIELD_GET(AL_MC_ECC_CE_ADDR1_BG, ecccaddr1);
	bank = FIELD_GET(AL_MC_ECC_CE_ADDR1_BANK, ecccaddr1);
	column = FIELD_GET(AL_MC_ECC_CE_ADDR1_COLUMN, ecccaddr1);

	prepare_msg(msg, माप(msg), HW_EVENT_ERR_CORRECTED,
		    rank, row, bg, bank, column,
		    ecccsyn0, ecccsyn1, ecccsyn2);

	spin_lock_irqsave(&al_mc->lock, flags);
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
			     ce_count, 0, 0, 0, 0, 0, -1, mci->ctl_name, msg);
	spin_unlock_irqrestore(&al_mc->lock, flags);

	वापस ce_count;
पूर्ण

अटल पूर्णांक handle_ue(काष्ठा mem_ctl_info *mci)
अणु
	u32 eccerrcnt, eccuaddr0, eccuaddr1, eccusyn0, eccusyn1, eccusyn2, row;
	काष्ठा al_mc_edac *al_mc = mci->pvt_info;
	अक्षर msg[AL_MC_EDAC_MSG_MAX];
	u16 ue_count, column;
	अचिन्हित दीर्घ flags;
	u8 rank, bg, bank;

	eccerrcnt = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_ERR_COUNT);
	ue_count = FIELD_GET(AL_MC_ECC_ERR_COUNT_UE, eccerrcnt);
	अगर (!ue_count)
		वापस 0;

	eccuaddr0 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_UE_ADDR0);
	eccuaddr1 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_UE_ADDR1);
	eccusyn0 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_UE_SYND0);
	eccusyn1 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_UE_SYND1);
	eccusyn2 = पढ़ोl_relaxed(al_mc->mmio_base + AL_MC_ECC_UE_SYND2);

	ग_लिखोl_relaxed(AL_MC_ECC_CLEAR_UE_COUNT | AL_MC_ECC_CLEAR_UE_ERR,
		       al_mc->mmio_base + AL_MC_ECC_CLEAR);

	dev_dbg(mci->pdev, "eccuaddr0=0x%08x eccuaddr1=0x%08x\n",
		eccuaddr0, eccuaddr1);

	rank = FIELD_GET(AL_MC_ECC_UE_ADDR0_RANK, eccuaddr0);
	row = FIELD_GET(AL_MC_ECC_UE_ADDR0_ROW, eccuaddr0);

	bg = FIELD_GET(AL_MC_ECC_UE_ADDR1_BG, eccuaddr1);
	bank = FIELD_GET(AL_MC_ECC_UE_ADDR1_BANK, eccuaddr1);
	column = FIELD_GET(AL_MC_ECC_UE_ADDR1_COLUMN, eccuaddr1);

	prepare_msg(msg, माप(msg), HW_EVENT_ERR_UNCORRECTED,
		    rank, row, bg, bank, column,
		    eccusyn0, eccusyn1, eccusyn2);

	spin_lock_irqsave(&al_mc->lock, flags);
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
			     ue_count, 0, 0, 0, 0, 0, -1, mci->ctl_name, msg);
	spin_unlock_irqrestore(&al_mc->lock, flags);

	वापस ue_count;
पूर्ण

अटल व्योम al_mc_edac_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा al_mc_edac *al_mc = mci->pvt_info;

	अगर (al_mc->irq_ue <= 0)
		handle_ue(mci);

	अगर (al_mc->irq_ce <= 0)
		handle_ce(mci);
पूर्ण

अटल irqवापस_t al_mc_edac_irq_handler_ue(पूर्णांक irq, व्योम *info)
अणु
	काष्ठा platक्रमm_device *pdev = info;
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	अगर (handle_ue(mci))
		वापस IRQ_HANDLED;
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t al_mc_edac_irq_handler_ce(पूर्णांक irq, व्योम *info)
अणु
	काष्ठा platक्रमm_device *pdev = info;
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	अगर (handle_ce(mci))
		वापस IRQ_HANDLED;
	वापस IRQ_NONE;
पूर्ण

अटल क्रमागत scrub_type get_scrub_mode(व्योम __iomem *mmio_base)
अणु
	u32 ecccfg0;

	ecccfg0 = पढ़ोl(mmio_base + AL_MC_ECC_CFG);

	अगर (FIELD_GET(AL_MC_ECC_CFG_SCRUB_DISABLED, ecccfg0))
		वापस SCRUB_NONE;
	अन्यथा
		वापस SCRUB_HW_SRC;
पूर्ण

अटल व्योम devm_al_mc_edac_मुक्त(व्योम *data)
अणु
	edac_mc_मुक्त(data);
पूर्ण

अटल व्योम devm_al_mc_edac_del(व्योम *data)
अणु
	edac_mc_del_mc(data);
पूर्ण

अटल पूर्णांक al_mc_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_mc_layer layers[1];
	काष्ठा mem_ctl_info *mci;
	काष्ठा al_mc_edac *al_mc;
	व्योम __iomem *mmio_base;
	काष्ठा dimm_info *dimm;
	पूर्णांक ret;

	mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mmio_base)) अणु
		dev_err(&pdev->dev, "failed to ioremap memory (%ld)\n",
			PTR_ERR(mmio_base));
		वापस PTR_ERR(mmio_base);
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 1;
	layers[0].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा al_mc_edac));
	अगर (!mci)
		वापस -ENOMEM;

	ret = devm_add_action(&pdev->dev, devm_al_mc_edac_मुक्त, mci);
	अगर (ret) अणु
		edac_mc_मुक्त(mci);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mci);
	al_mc = mci->pvt_info;

	al_mc->mmio_base = mmio_base;

	al_mc->irq_ue = of_irq_get_byname(pdev->dev.of_node, "ue");
	अगर (al_mc->irq_ue <= 0)
		dev_dbg(&pdev->dev,
			"no IRQ defined for UE - falling back to polling\n");

	al_mc->irq_ce = of_irq_get_byname(pdev->dev.of_node, "ce");
	अगर (al_mc->irq_ce <= 0)
		dev_dbg(&pdev->dev,
			"no IRQ defined for CE - falling back to polling\n");

	/*
	 * In हाल both पूर्णांकerrupts (ue/ce) are to be found, use पूर्णांकerrupt mode.
	 * In हाल none of the पूर्णांकerrupt are foud, use polling mode.
	 * In हाल only one पूर्णांकerrupt is found, use पूर्णांकerrupt mode क्रम it but
	 * keep polling mode enable क्रम the other.
	 */
	अगर (al_mc->irq_ue <= 0 || al_mc->irq_ce <= 0) अणु
		edac_op_state = EDAC_OPSTATE_POLL;
		mci->edac_check = al_mc_edac_check;
	पूर्ण अन्यथा अणु
		edac_op_state = EDAC_OPSTATE_INT;
	पूर्ण

	spin_lock_init(&al_mc->lock);

	mci->mtype_cap = MEM_FLAG_DDR3 | MEM_FLAG_DDR4;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = DRV_NAME;
	mci->ctl_name = "al_mc";
	mci->pdev = &pdev->dev;
	mci->scrub_mode = get_scrub_mode(mmio_base);

	dimm = *mci->dimms;
	dimm->grain = 1;

	ret = edac_mc_add_mc(mci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"fail to add memory controller device (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action(&pdev->dev, devm_al_mc_edac_del, &pdev->dev);
	अगर (ret) अणु
		edac_mc_del_mc(&pdev->dev);
		वापस ret;
	पूर्ण

	अगर (al_mc->irq_ue > 0) अणु
		ret = devm_request_irq(&pdev->dev,
				       al_mc->irq_ue,
				       al_mc_edac_irq_handler_ue,
				       IRQF_SHARED,
				       pdev->name,
				       pdev);
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"failed to request UE IRQ %d (%d)\n",
				al_mc->irq_ue, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (al_mc->irq_ce > 0) अणु
		ret = devm_request_irq(&pdev->dev,
				       al_mc->irq_ce,
				       al_mc_edac_irq_handler_ce,
				       IRQF_SHARED,
				       pdev->name,
				       pdev);
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"failed to request CE IRQ %d (%d)\n",
				al_mc->irq_ce, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id al_mc_edac_of_match[] = अणु
	अणु .compatible = "amazon,al-mc-edac", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, al_mc_edac_of_match);

अटल काष्ठा platक्रमm_driver al_mc_edac_driver = अणु
	.probe = al_mc_edac_probe,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = al_mc_edac_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(al_mc_edac_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Talel Shenhar");
MODULE_DESCRIPTION("Amazon's Annapurna Lab's Memory Controller EDAC Driver");
