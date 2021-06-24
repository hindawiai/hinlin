<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Pengutronix, Jan Luebbe <kernel@pengutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/edac.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/hardware/cache-aurora-l2.h>

#समावेश "edac_mc.h"
#समावेश "edac_device.h"
#समावेश "edac_module.h"

/************************ EDAC MC (DDR RAM) ********************************/

#घोषणा SDRAM_NUM_CS 4

#घोषणा SDRAM_CONFIG_REG        0x0
#घोषणा SDRAM_CONFIG_ECC_MASK         BIT(18)
#घोषणा SDRAM_CONFIG_REGISTERED_MASK  BIT(17)
#घोषणा SDRAM_CONFIG_BUS_WIDTH_MASK   BIT(15)

#घोषणा SDRAM_ADDR_CTRL_REG     0x10
#घोषणा SDRAM_ADDR_CTRL_SIZE_HIGH_OFFSET(cs) (20+cs)
#घोषणा SDRAM_ADDR_CTRL_SIZE_HIGH_MASK(cs)   (0x1 << SDRAM_ADDR_CTRL_SIZE_HIGH_OFFSET(cs))
#घोषणा SDRAM_ADDR_CTRL_ADDR_SEL_MASK(cs)    BIT(16+cs)
#घोषणा SDRAM_ADDR_CTRL_SIZE_LOW_OFFSET(cs)  (cs*4+2)
#घोषणा SDRAM_ADDR_CTRL_SIZE_LOW_MASK(cs)    (0x3 << SDRAM_ADDR_CTRL_SIZE_LOW_OFFSET(cs))
#घोषणा SDRAM_ADDR_CTRL_STRUCT_OFFSET(cs)    (cs*4)
#घोषणा SDRAM_ADDR_CTRL_STRUCT_MASK(cs)      (0x3 << SDRAM_ADDR_CTRL_STRUCT_OFFSET(cs))

#घोषणा SDRAM_ERR_DATA_H_REG    0x40
#घोषणा SDRAM_ERR_DATA_L_REG    0x44

#घोषणा SDRAM_ERR_RECV_ECC_REG  0x48
#घोषणा SDRAM_ERR_RECV_ECC_VALUE_MASK 0xff

#घोषणा SDRAM_ERR_CALC_ECC_REG  0x4c
#घोषणा SDRAM_ERR_CALC_ECC_ROW_OFFSET 8
#घोषणा SDRAM_ERR_CALC_ECC_ROW_MASK   (0xffff << SDRAM_ERR_CALC_ECC_ROW_OFFSET)
#घोषणा SDRAM_ERR_CALC_ECC_VALUE_MASK 0xff

#घोषणा SDRAM_ERR_ADDR_REG      0x50
#घोषणा SDRAM_ERR_ADDR_BANK_OFFSET    23
#घोषणा SDRAM_ERR_ADDR_BANK_MASK      (0x7 << SDRAM_ERR_ADDR_BANK_OFFSET)
#घोषणा SDRAM_ERR_ADDR_COL_OFFSET     8
#घोषणा SDRAM_ERR_ADDR_COL_MASK       (0x7fff << SDRAM_ERR_ADDR_COL_OFFSET)
#घोषणा SDRAM_ERR_ADDR_CS_OFFSET      1
#घोषणा SDRAM_ERR_ADDR_CS_MASK        (0x3 << SDRAM_ERR_ADDR_CS_OFFSET)
#घोषणा SDRAM_ERR_ADDR_TYPE_MASK      BIT(0)

#घोषणा SDRAM_ERR_CTRL_REG      0x54
#घोषणा SDRAM_ERR_CTRL_THR_OFFSET     16
#घोषणा SDRAM_ERR_CTRL_THR_MASK       (0xff << SDRAM_ERR_CTRL_THR_OFFSET)
#घोषणा SDRAM_ERR_CTRL_PROP_MASK      BIT(9)

#घोषणा SDRAM_ERR_SBE_COUNT_REG 0x58
#घोषणा SDRAM_ERR_DBE_COUNT_REG 0x5c

#घोषणा SDRAM_ERR_CAUSE_ERR_REG 0xd0
#घोषणा SDRAM_ERR_CAUSE_MSG_REG 0xd8
#घोषणा SDRAM_ERR_CAUSE_DBE_MASK      BIT(1)
#घोषणा SDRAM_ERR_CAUSE_SBE_MASK      BIT(0)

#घोषणा SDRAM_RANK_CTRL_REG 0x1e0
#घोषणा SDRAM_RANK_CTRL_EXIST_MASK(cs) BIT(cs)

काष्ठा axp_mc_drvdata अणु
	व्योम __iomem *base;
	/* width in bytes */
	अचिन्हित पूर्णांक width;
	/* bank पूर्णांकerleaving */
	bool cs_addr_sel[SDRAM_NUM_CS];

	अक्षर msg[128];
पूर्ण;

/* derived from "DRAM Address Multiplexing" in the ARMADA XP Functional Spec */
अटल uपूर्णांक32_t axp_mc_calc_address(काष्ठा axp_mc_drvdata *drvdata,
				    uपूर्णांक8_t cs, uपूर्णांक8_t bank, uपूर्णांक16_t row,
				    uपूर्णांक16_t col)
अणु
	अगर (drvdata->width == 8) अणु
		/* 64 bit */
		अगर (drvdata->cs_addr_sel[cs])
			/* bank पूर्णांकerleaved */
			वापस (((row & 0xfff8) << 16) |
				((bank & 0x7) << 16) |
				((row & 0x7) << 13) |
				((col & 0x3ff) << 3));
		अन्यथा
			वापस (((row & 0xffff << 16) |
				 ((bank & 0x7) << 13) |
				 ((col & 0x3ff)) << 3));
	पूर्ण अन्यथा अगर (drvdata->width == 4) अणु
		/* 32 bit */
		अगर (drvdata->cs_addr_sel[cs])
			/* bank पूर्णांकerleaved */
			वापस (((row & 0xfff0) << 15) |
				((bank & 0x7) << 16) |
				((row & 0xf) << 12) |
				((col & 0x3ff) << 2));
		अन्यथा
			वापस (((row & 0xffff << 15) |
				 ((bank & 0x7) << 12) |
				 ((col & 0x3ff)) << 2));
	पूर्ण अन्यथा अणु
		/* 16 bit */
		अगर (drvdata->cs_addr_sel[cs])
			/* bank पूर्णांकerleaved */
			वापस (((row & 0xffe0) << 14) |
				((bank & 0x7) << 16) |
				((row & 0x1f) << 11) |
				((col & 0x3ff) << 1));
		अन्यथा
			वापस (((row & 0xffff << 14) |
				 ((bank & 0x7) << 11) |
				 ((col & 0x3ff)) << 1));
	पूर्ण
पूर्ण

अटल व्योम axp_mc_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा axp_mc_drvdata *drvdata = mci->pvt_info;
	uपूर्णांक32_t data_h, data_l, recv_ecc, calc_ecc, addr;
	uपूर्णांक32_t cnt_sbe, cnt_dbe, cause_err, cause_msg;
	uपूर्णांक32_t row_val, col_val, bank_val, addr_val;
	uपूर्णांक8_t syndrome_val, cs_val;
	अक्षर *msg = drvdata->msg;

	data_h    = पढ़ोl(drvdata->base + SDRAM_ERR_DATA_H_REG);
	data_l    = पढ़ोl(drvdata->base + SDRAM_ERR_DATA_L_REG);
	recv_ecc  = पढ़ोl(drvdata->base + SDRAM_ERR_RECV_ECC_REG);
	calc_ecc  = पढ़ोl(drvdata->base + SDRAM_ERR_CALC_ECC_REG);
	addr      = पढ़ोl(drvdata->base + SDRAM_ERR_ADDR_REG);
	cnt_sbe   = पढ़ोl(drvdata->base + SDRAM_ERR_SBE_COUNT_REG);
	cnt_dbe   = पढ़ोl(drvdata->base + SDRAM_ERR_DBE_COUNT_REG);
	cause_err = पढ़ोl(drvdata->base + SDRAM_ERR_CAUSE_ERR_REG);
	cause_msg = पढ़ोl(drvdata->base + SDRAM_ERR_CAUSE_MSG_REG);

	/* clear cause रेजिस्टरs */
	ग_लिखोl(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK),
	       drvdata->base + SDRAM_ERR_CAUSE_ERR_REG);
	ग_लिखोl(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK),
	       drvdata->base + SDRAM_ERR_CAUSE_MSG_REG);

	/* clear error counter रेजिस्टरs */
	अगर (cnt_sbe)
		ग_लिखोl(0, drvdata->base + SDRAM_ERR_SBE_COUNT_REG);
	अगर (cnt_dbe)
		ग_लिखोl(0, drvdata->base + SDRAM_ERR_DBE_COUNT_REG);

	अगर (!cnt_sbe && !cnt_dbe)
		वापस;

	अगर (!(addr & SDRAM_ERR_ADDR_TYPE_MASK)) अणु
		अगर (cnt_sbe)
			cnt_sbe--;
		अन्यथा
			dev_warn(mci->pdev, "inconsistent SBE count detected\n");
	पूर्ण अन्यथा अणु
		अगर (cnt_dbe)
			cnt_dbe--;
		अन्यथा
			dev_warn(mci->pdev, "inconsistent DBE count detected\n");
	पूर्ण

	/* report earlier errors */
	अगर (cnt_sbe)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     cnt_sbe, /* error count */
				     0, 0, 0, /* pfn, offset, syndrome */
				     -1, -1, -1, /* top, mid, low layer */
				     mci->ctl_name,
				     "details unavailable (multiple errors)");
	अगर (cnt_dbe)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     cnt_sbe, /* error count */
				     0, 0, 0, /* pfn, offset, syndrome */
				     -1, -1, -1, /* top, mid, low layer */
				     mci->ctl_name,
				     "details unavailable (multiple errors)");

	/* report details क्रम most recent error */
	cs_val   = (addr & SDRAM_ERR_ADDR_CS_MASK) >> SDRAM_ERR_ADDR_CS_OFFSET;
	bank_val = (addr & SDRAM_ERR_ADDR_BANK_MASK) >> SDRAM_ERR_ADDR_BANK_OFFSET;
	row_val  = (calc_ecc & SDRAM_ERR_CALC_ECC_ROW_MASK) >> SDRAM_ERR_CALC_ECC_ROW_OFFSET;
	col_val  = (addr & SDRAM_ERR_ADDR_COL_MASK) >> SDRAM_ERR_ADDR_COL_OFFSET;
	syndrome_val = (recv_ecc ^ calc_ecc) & 0xff;
	addr_val = axp_mc_calc_address(drvdata, cs_val, bank_val, row_val,
				       col_val);
	msg += प्र_लिखो(msg, "row=0x%04x ", row_val); /* 11 अक्षरs */
	msg += प्र_लिखो(msg, "bank=0x%x ", bank_val); /*  9 अक्षरs */
	msg += प्र_लिखो(msg, "col=0x%04x ", col_val); /* 11 अक्षरs */
	msg += प्र_लिखो(msg, "cs=%d", cs_val);	     /*  4 अक्षरs */

	अगर (!(addr & SDRAM_ERR_ADDR_TYPE_MASK)) अणु
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     1,	/* error count */
				     addr_val >> PAGE_SHIFT,
				     addr_val & ~PAGE_MASK,
				     syndrome_val,
				     cs_val, -1, -1, /* top, mid, low layer */
				     mci->ctl_name, drvdata->msg);
	पूर्ण अन्यथा अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     1,	/* error count */
				     addr_val >> PAGE_SHIFT,
				     addr_val & ~PAGE_MASK,
				     syndrome_val,
				     cs_val, -1, -1, /* top, mid, low layer */
				     mci->ctl_name, drvdata->msg);
	पूर्ण
पूर्ण

अटल व्योम axp_mc_पढ़ो_config(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा axp_mc_drvdata *drvdata = mci->pvt_info;
	uपूर्णांक32_t config, addr_ctrl, rank_ctrl;
	अचिन्हित पूर्णांक i, cs_काष्ठा, cs_size;
	काष्ठा dimm_info *dimm;

	config = पढ़ोl(drvdata->base + SDRAM_CONFIG_REG);
	अगर (config & SDRAM_CONFIG_BUS_WIDTH_MASK)
		/* 64 bit */
		drvdata->width = 8;
	अन्यथा
		/* 32 bit */
		drvdata->width = 4;

	addr_ctrl = पढ़ोl(drvdata->base + SDRAM_ADDR_CTRL_REG);
	rank_ctrl = पढ़ोl(drvdata->base + SDRAM_RANK_CTRL_REG);
	क्रम (i = 0; i < SDRAM_NUM_CS; i++) अणु
		dimm = mci->dimms[i];

		अगर (!(rank_ctrl & SDRAM_RANK_CTRL_EXIST_MASK(i)))
			जारी;

		drvdata->cs_addr_sel[i] =
			!!(addr_ctrl & SDRAM_ADDR_CTRL_ADDR_SEL_MASK(i));

		cs_काष्ठा = (addr_ctrl & SDRAM_ADDR_CTRL_STRUCT_MASK(i)) >> SDRAM_ADDR_CTRL_STRUCT_OFFSET(i);
		cs_size   = ((addr_ctrl & SDRAM_ADDR_CTRL_SIZE_HIGH_MASK(i)) >> (SDRAM_ADDR_CTRL_SIZE_HIGH_OFFSET(i) - 2) |
			    ((addr_ctrl & SDRAM_ADDR_CTRL_SIZE_LOW_MASK(i)) >> SDRAM_ADDR_CTRL_SIZE_LOW_OFFSET(i)));

		चयन (cs_size) अणु
		हाल 0: /* 2GBit */
			dimm->nr_pages = 524288;
			अवरोध;
		हाल 1: /* 256MBit */
			dimm->nr_pages = 65536;
			अवरोध;
		हाल 2: /* 512MBit */
			dimm->nr_pages = 131072;
			अवरोध;
		हाल 3: /* 1GBit */
			dimm->nr_pages = 262144;
			अवरोध;
		हाल 4: /* 4GBit */
			dimm->nr_pages = 1048576;
			अवरोध;
		हाल 5: /* 8GBit */
			dimm->nr_pages = 2097152;
			अवरोध;
		पूर्ण
		dimm->grain = 8;
		dimm->dtype = cs_काष्ठा ? DEV_X16 : DEV_X8;
		dimm->mtype = (config & SDRAM_CONFIG_REGISTERED_MASK) ?
			MEM_RDDR3 : MEM_DDR3;
		dimm->edac_mode = EDAC_SECDED;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id axp_mc_of_match[] = अणु
	अणु.compatible = "marvell,armada-xp-sdram-controller",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axp_mc_of_match);

अटल पूर्णांक axp_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp_mc_drvdata *drvdata;
	काष्ठा edac_mc_layer layers[1];
	स्थिर काष्ठा of_device_id *id;
	काष्ठा mem_ctl_info *mci;
	काष्ठा resource *r;
	व्योम __iomem *base;
	uपूर्णांक32_t config;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "Unable to get mem resource\n");
		वापस -ENODEV;
	पूर्ण

	base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(base)) अणु
		dev_err(&pdev->dev, "Unable to map regs\n");
		वापस PTR_ERR(base);
	पूर्ण

	config = पढ़ोl(base + SDRAM_CONFIG_REG);
	अगर (!(config & SDRAM_CONFIG_ECC_MASK)) अणु
		dev_warn(&pdev->dev, "SDRAM ECC is not enabled\n");
		वापस -EINVAL;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = SDRAM_NUM_CS;
	layers[0].is_virt_csrow = true;

	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*drvdata));
	अगर (!mci)
		वापस -ENOMEM;

	drvdata = mci->pvt_info;
	drvdata->base = base;
	mci->pdev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, mci);

	id = of_match_device(axp_mc_of_match, &pdev->dev);
	mci->edac_check = axp_mc_check;
	mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = pdev->dev.driver->name;
	mci->ctl_name = id ? id->compatible : "unknown";
	mci->dev_name = dev_name(&pdev->dev);
	mci->scrub_mode = SCRUB_NONE;

	axp_mc_पढ़ो_config(mci);

	/* These SoCs have a reduced width bus */
	अगर (of_machine_is_compatible("marvell,armada380") ||
	    of_machine_is_compatible("marvell,armadaxp-98dx3236"))
		drvdata->width /= 2;

	/* configure SBE threshold */
	/* it seems that SBEs are not captured otherwise */
	ग_लिखोl(1 << SDRAM_ERR_CTRL_THR_OFFSET, drvdata->base + SDRAM_ERR_CTRL_REG);

	/* clear cause रेजिस्टरs */
	ग_लिखोl(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK), drvdata->base + SDRAM_ERR_CAUSE_ERR_REG);
	ग_लिखोl(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK), drvdata->base + SDRAM_ERR_CAUSE_MSG_REG);

	/* clear counter रेजिस्टरs */
	ग_लिखोl(0, drvdata->base + SDRAM_ERR_SBE_COUNT_REG);
	ग_लिखोl(0, drvdata->base + SDRAM_ERR_DBE_COUNT_REG);

	अगर (edac_mc_add_mc(mci)) अणु
		edac_mc_मुक्त(mci);
		वापस -EINVAL;
	पूर्ण
	edac_op_state = EDAC_OPSTATE_POLL;

	वापस 0;
पूर्ण

अटल पूर्णांक axp_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axp_mc_driver = अणु
	.probe = axp_mc_probe,
	.हटाओ = axp_mc_हटाओ,
	.driver = अणु
		.name = "armada_xp_mc_edac",
		.of_match_table = of_match_ptr(axp_mc_of_match),
	पूर्ण,
पूर्ण;

/************************ EDAC Device (L2 Cache) ***************************/

काष्ठा aurora_l2_drvdata अणु
	व्योम __iomem *base;

	अक्षर msg[128];

	/* error injection via debugfs */
	uपूर्णांक32_t inject_addr;
	uपूर्णांक32_t inject_mask;
	uपूर्णांक8_t inject_ctl;

	काष्ठा dentry *debugfs;
पूर्ण;

#अगर_घोषित CONFIG_EDAC_DEBUG
अटल व्योम aurora_l2_inject(काष्ठा aurora_l2_drvdata *drvdata)
अणु
	drvdata->inject_addr &= AURORA_ERR_INJECT_CTL_ADDR_MASK;
	drvdata->inject_ctl &= AURORA_ERR_INJECT_CTL_EN_MASK;
	ग_लिखोl(0, drvdata->base + AURORA_ERR_INJECT_CTL_REG);
	ग_लिखोl(drvdata->inject_mask, drvdata->base + AURORA_ERR_INJECT_MASK_REG);
	ग_लिखोl(drvdata->inject_addr | drvdata->inject_ctl, drvdata->base + AURORA_ERR_INJECT_CTL_REG);
पूर्ण
#पूर्ण_अगर

अटल व्योम aurora_l2_check(काष्ठा edac_device_ctl_info *dci)
अणु
	काष्ठा aurora_l2_drvdata *drvdata = dci->pvt_info;
	uपूर्णांक32_t cnt, src, txn, err, attr_cap, addr_cap, way_cap;
	अचिन्हित पूर्णांक cnt_ce, cnt_ue;
	अक्षर *msg = drvdata->msg;
	माप_प्रकार size = माप(drvdata->msg);
	माप_प्रकार len = 0;

	cnt = पढ़ोl(drvdata->base + AURORA_ERR_CNT_REG);
	attr_cap = पढ़ोl(drvdata->base + AURORA_ERR_ATTR_CAP_REG);
	addr_cap = पढ़ोl(drvdata->base + AURORA_ERR_ADDR_CAP_REG);
	way_cap = पढ़ोl(drvdata->base + AURORA_ERR_WAY_CAP_REG);

	cnt_ce = (cnt & AURORA_ERR_CNT_CE_MASK) >> AURORA_ERR_CNT_CE_OFFSET;
	cnt_ue = (cnt & AURORA_ERR_CNT_UE_MASK) >> AURORA_ERR_CNT_UE_OFFSET;
	/* clear error counter रेजिस्टरs */
	अगर (cnt_ce || cnt_ue)
		ग_लिखोl(AURORA_ERR_CNT_CLR, drvdata->base + AURORA_ERR_CNT_REG);

	अगर (!(attr_cap & AURORA_ERR_ATTR_CAP_VALID))
		जाओ clear_reमुख्यing;

	src = (attr_cap & AURORA_ERR_ATTR_SRC_MSK) >> AURORA_ERR_ATTR_SRC_OFF;
	अगर (src <= 3)
		len += scnम_लिखो(msg+len, size-len, "src=CPU%d ", src);
	अन्यथा
		len += scnम_लिखो(msg+len, size-len, "src=IO ");

	txn =  (attr_cap & AURORA_ERR_ATTR_TXN_MSK) >> AURORA_ERR_ATTR_TXN_OFF;
	चयन (txn) अणु
	हाल 0:
		len += scnम_लिखो(msg+len, size-len, "txn=Data-Read ");
		अवरोध;
	हाल 1:
		len += scnम_लिखो(msg+len, size-len, "txn=Isn-Read ");
		अवरोध;
	हाल 2:
		len += scnम_लिखो(msg+len, size-len, "txn=Clean-Flush ");
		अवरोध;
	हाल 3:
		len += scnम_लिखो(msg+len, size-len, "txn=Eviction ");
		अवरोध;
	हाल 4:
		len += scnम_लिखो(msg+len, size-len,
				"txn=Read-Modify-Write ");
		अवरोध;
	पूर्ण

	err = (attr_cap & AURORA_ERR_ATTR_ERR_MSK) >> AURORA_ERR_ATTR_ERR_OFF;
	चयन (err) अणु
	हाल 0:
		len += scnम_लिखो(msg+len, size-len, "err=CorrECC ");
		अवरोध;
	हाल 1:
		len += scnम_लिखो(msg+len, size-len, "err=UnCorrECC ");
		अवरोध;
	हाल 2:
		len += scnम_लिखो(msg+len, size-len, "err=TagParity ");
		अवरोध;
	पूर्ण

	len += scnम_लिखो(msg+len, size-len, "addr=0x%x ", addr_cap & AURORA_ERR_ADDR_CAP_ADDR_MASK);
	len += scnम_लिखो(msg+len, size-len, "index=0x%x ", (way_cap & AURORA_ERR_WAY_IDX_MSK) >> AURORA_ERR_WAY_IDX_OFF);
	len += scnम_लिखो(msg+len, size-len, "way=0x%x", (way_cap & AURORA_ERR_WAY_CAP_WAY_MASK) >> AURORA_ERR_WAY_CAP_WAY_OFFSET);

	/* clear error capture रेजिस्टरs */
	ग_लिखोl(AURORA_ERR_ATTR_CAP_VALID, drvdata->base + AURORA_ERR_ATTR_CAP_REG);
	अगर (err) अणु
		/* UnCorrECC or TagParity */
		अगर (cnt_ue)
			cnt_ue--;
		edac_device_handle_ue(dci, 0, 0, drvdata->msg);
	पूर्ण अन्यथा अणु
		अगर (cnt_ce)
			cnt_ce--;
		edac_device_handle_ce(dci, 0, 0, drvdata->msg);
	पूर्ण

clear_reमुख्यing:
	/* report reमुख्यing errors */
	जबतक (cnt_ue--)
		edac_device_handle_ue(dci, 0, 0, "details unavailable (multiple errors)");
	जबतक (cnt_ce--)
		edac_device_handle_ue(dci, 0, 0, "details unavailable (multiple errors)");
पूर्ण

अटल व्योम aurora_l2_poll(काष्ठा edac_device_ctl_info *dci)
अणु
#अगर_घोषित CONFIG_EDAC_DEBUG
	काष्ठा aurora_l2_drvdata *drvdata = dci->pvt_info;
#पूर्ण_अगर

	aurora_l2_check(dci);
#अगर_घोषित CONFIG_EDAC_DEBUG
	aurora_l2_inject(drvdata);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा of_device_id aurora_l2_of_match[] = अणु
	अणु.compatible = "marvell,aurora-system-cache",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aurora_l2_of_match);

अटल पूर्णांक aurora_l2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aurora_l2_drvdata *drvdata;
	काष्ठा edac_device_ctl_info *dci;
	स्थिर काष्ठा of_device_id *id;
	uपूर्णांक32_t l2x0_aux_ctrl;
	व्योम __iomem *base;
	काष्ठा resource *r;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "Unable to get mem resource\n");
		वापस -ENODEV;
	पूर्ण

	base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(base)) अणु
		dev_err(&pdev->dev, "Unable to map regs\n");
		वापस PTR_ERR(base);
	पूर्ण

	l2x0_aux_ctrl = पढ़ोl(base + L2X0_AUX_CTRL);
	अगर (!(l2x0_aux_ctrl & AURORA_ACR_PARITY_EN))
		dev_warn(&pdev->dev, "tag parity is not enabled\n");
	अगर (!(l2x0_aux_ctrl & AURORA_ACR_ECC_EN))
		dev_warn(&pdev->dev, "data ECC is not enabled\n");

	dci = edac_device_alloc_ctl_info(माप(*drvdata),
					 "cpu", 1, "L", 1, 2, शून्य, 0, 0);
	अगर (!dci)
		वापस -ENOMEM;

	drvdata = dci->pvt_info;
	drvdata->base = base;
	dci->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dci);

	id = of_match_device(aurora_l2_of_match, &pdev->dev);
	dci->edac_check = aurora_l2_poll;
	dci->mod_name = pdev->dev.driver->name;
	dci->ctl_name = id ? id->compatible : "unknown";
	dci->dev_name = dev_name(&pdev->dev);

	/* clear रेजिस्टरs */
	ग_लिखोl(AURORA_ERR_CNT_CLR, drvdata->base + AURORA_ERR_CNT_REG);
	ग_लिखोl(AURORA_ERR_ATTR_CAP_VALID, drvdata->base + AURORA_ERR_ATTR_CAP_REG);

	अगर (edac_device_add_device(dci)) अणु
		edac_device_मुक्त_ctl_info(dci);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG
	drvdata->debugfs = edac_debugfs_create_dir(dev_name(&pdev->dev));
	अगर (drvdata->debugfs) अणु
		edac_debugfs_create_x32("inject_addr", 0644,
					drvdata->debugfs,
					&drvdata->inject_addr);
		edac_debugfs_create_x32("inject_mask", 0644,
					drvdata->debugfs,
					&drvdata->inject_mask);
		edac_debugfs_create_x8("inject_ctl", 0644,
				       drvdata->debugfs, &drvdata->inject_ctl);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक aurora_l2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *dci = platक्रमm_get_drvdata(pdev);
#अगर_घोषित CONFIG_EDAC_DEBUG
	काष्ठा aurora_l2_drvdata *drvdata = dci->pvt_info;

	edac_debugfs_हटाओ_recursive(drvdata->debugfs);
#पूर्ण_अगर
	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(dci);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aurora_l2_driver = अणु
	.probe = aurora_l2_probe,
	.हटाओ = aurora_l2_हटाओ,
	.driver = अणु
		.name = "aurora_l2_edac",
		.of_match_table = of_match_ptr(aurora_l2_of_match),
	पूर्ण,
पूर्ण;

/************************ Driver registration ******************************/

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&axp_mc_driver,
	&aurora_l2_driver,
पूर्ण;

अटल पूर्णांक __init armada_xp_edac_init(व्योम)
अणु
	पूर्णांक res;

	/* only polling is supported */
	edac_op_state = EDAC_OPSTATE_POLL;

	res = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (res)
		pr_warn("Armada XP EDAC drivers fail to register\n");

	वापस 0;
पूर्ण
module_init(armada_xp_edac_init);

अटल व्योम __निकास armada_xp_edac_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(armada_xp_edac_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Pengutronix");
MODULE_DESCRIPTION("EDAC Drivers for Marvell Armada XP SDRAM and L2 Cache Controller");
