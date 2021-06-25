<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/qcom/llcc-qcom.h>

#समावेश "edac_mc.h"
#समावेश "edac_device.h"

#घोषणा EDAC_LLCC                       "qcom_llcc"

#घोषणा LLCC_ERP_PANIC_ON_UE            1

#घोषणा TRP_SYN_REG_CNT                 6
#घोषणा DRP_SYN_REG_CNT                 8

#घोषणा LLCC_COMMON_STATUS0             0x0003000c
#घोषणा LLCC_LB_CNT_MASK                GENMASK(31, 28)
#घोषणा LLCC_LB_CNT_SHIFT               28

/* Single & द्विगुन bit syndrome रेजिस्टर offsets */
#घोषणा TRP_ECC_SB_ERR_SYN0             0x0002304c
#घोषणा TRP_ECC_DB_ERR_SYN0             0x00020370
#घोषणा DRP_ECC_SB_ERR_SYN0             0x0004204c
#घोषणा DRP_ECC_DB_ERR_SYN0             0x00042070

/* Error रेजिस्टर offsets */
#घोषणा TRP_ECC_ERROR_STATUS1           0x00020348
#घोषणा TRP_ECC_ERROR_STATUS0           0x00020344
#घोषणा DRP_ECC_ERROR_STATUS1           0x00042048
#घोषणा DRP_ECC_ERROR_STATUS0           0x00042044

/* TRP, DRP पूर्णांकerrupt रेजिस्टर offsets */
#घोषणा DRP_INTERRUPT_STATUS            0x00041000
#घोषणा TRP_INTERRUPT_0_STATUS          0x00020480
#घोषणा DRP_INTERRUPT_CLEAR             0x00041008
#घोषणा DRP_ECC_ERROR_CNTR_CLEAR        0x00040004
#घोषणा TRP_INTERRUPT_0_CLEAR           0x00020484
#घोषणा TRP_ECC_ERROR_CNTR_CLEAR        0x00020440

/* Mask and shअगरt macros */
#घोषणा ECC_DB_ERR_COUNT_MASK           GENMASK(4, 0)
#घोषणा ECC_DB_ERR_WAYS_MASK            GENMASK(31, 16)
#घोषणा ECC_DB_ERR_WAYS_SHIFT           BIT(4)

#घोषणा ECC_SB_ERR_COUNT_MASK           GENMASK(23, 16)
#घोषणा ECC_SB_ERR_COUNT_SHIFT          BIT(4)
#घोषणा ECC_SB_ERR_WAYS_MASK            GENMASK(15, 0)

#घोषणा SB_ECC_ERROR                    BIT(0)
#घोषणा DB_ECC_ERROR                    BIT(1)

#घोषणा DRP_TRP_INT_CLEAR               GENMASK(1, 0)
#घोषणा DRP_TRP_CNT_CLEAR               GENMASK(1, 0)

/* Config रेजिस्टरs offsets*/
#घोषणा DRP_ECC_ERROR_CFG               0x00040000

/* Tag RAM, Data RAM पूर्णांकerrupt रेजिस्टर offsets */
#घोषणा CMN_INTERRUPT_0_ENABLE          0x0003001c
#घोषणा CMN_INTERRUPT_2_ENABLE          0x0003003c
#घोषणा TRP_INTERRUPT_0_ENABLE          0x00020488
#घोषणा DRP_INTERRUPT_ENABLE            0x0004100c

#घोषणा SB_ERROR_THRESHOLD              0x1
#घोषणा SB_ERROR_THRESHOLD_SHIFT        24
#घोषणा SB_DB_TRP_INTERRUPT_ENABLE      0x3
#घोषणा TRP0_INTERRUPT_ENABLE           0x1
#घोषणा DRP0_INTERRUPT_ENABLE           BIT(6)
#घोषणा SB_DB_DRP_INTERRUPT_ENABLE      0x3

क्रमागत अणु
	LLCC_DRAM_CE = 0,
	LLCC_DRAM_UE,
	LLCC_TRAM_CE,
	LLCC_TRAM_UE,
पूर्ण;

अटल स्थिर काष्ठा llcc_edac_reg_data edac_reg_data[] = अणु
	[LLCC_DRAM_CE] = अणु
		.name = "DRAM Single-bit",
		.synd_reg = DRP_ECC_SB_ERR_SYN0,
		.count_status_reg = DRP_ECC_ERROR_STATUS1,
		.ways_status_reg = DRP_ECC_ERROR_STATUS0,
		.reg_cnt = DRP_SYN_REG_CNT,
		.count_mask = ECC_SB_ERR_COUNT_MASK,
		.ways_mask = ECC_SB_ERR_WAYS_MASK,
		.count_shअगरt = ECC_SB_ERR_COUNT_SHIFT,
	पूर्ण,
	[LLCC_DRAM_UE] = अणु
		.name = "DRAM Double-bit",
		.synd_reg = DRP_ECC_DB_ERR_SYN0,
		.count_status_reg = DRP_ECC_ERROR_STATUS1,
		.ways_status_reg = DRP_ECC_ERROR_STATUS0,
		.reg_cnt = DRP_SYN_REG_CNT,
		.count_mask = ECC_DB_ERR_COUNT_MASK,
		.ways_mask = ECC_DB_ERR_WAYS_MASK,
		.ways_shअगरt = ECC_DB_ERR_WAYS_SHIFT,
	पूर्ण,
	[LLCC_TRAM_CE] = अणु
		.name = "TRAM Single-bit",
		.synd_reg = TRP_ECC_SB_ERR_SYN0,
		.count_status_reg = TRP_ECC_ERROR_STATUS1,
		.ways_status_reg = TRP_ECC_ERROR_STATUS0,
		.reg_cnt = TRP_SYN_REG_CNT,
		.count_mask = ECC_SB_ERR_COUNT_MASK,
		.ways_mask = ECC_SB_ERR_WAYS_MASK,
		.count_shअगरt = ECC_SB_ERR_COUNT_SHIFT,
	पूर्ण,
	[LLCC_TRAM_UE] = अणु
		.name = "TRAM Double-bit",
		.synd_reg = TRP_ECC_DB_ERR_SYN0,
		.count_status_reg = TRP_ECC_ERROR_STATUS1,
		.ways_status_reg = TRP_ECC_ERROR_STATUS0,
		.reg_cnt = TRP_SYN_REG_CNT,
		.count_mask = ECC_DB_ERR_COUNT_MASK,
		.ways_mask = ECC_DB_ERR_WAYS_MASK,
		.ways_shअगरt = ECC_DB_ERR_WAYS_SHIFT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक qcom_llcc_core_setup(काष्ठा regmap *llcc_bcast_regmap)
अणु
	u32 sb_err_threshold;
	पूर्णांक ret;

	/*
	 * Configure पूर्णांकerrupt enable रेजिस्टरs such that Tag, Data RAM related
	 * पूर्णांकerrupts are propagated to पूर्णांकerrupt controller क्रम servicing
	 */
	ret = regmap_update_bits(llcc_bcast_regmap, CMN_INTERRUPT_2_ENABLE,
				 TRP0_INTERRUPT_ENABLE,
				 TRP0_INTERRUPT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(llcc_bcast_regmap, TRP_INTERRUPT_0_ENABLE,
				 SB_DB_TRP_INTERRUPT_ENABLE,
				 SB_DB_TRP_INTERRUPT_ENABLE);
	अगर (ret)
		वापस ret;

	sb_err_threshold = (SB_ERROR_THRESHOLD << SB_ERROR_THRESHOLD_SHIFT);
	ret = regmap_ग_लिखो(llcc_bcast_regmap, DRP_ECC_ERROR_CFG,
			   sb_err_threshold);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(llcc_bcast_regmap, CMN_INTERRUPT_2_ENABLE,
				 DRP0_INTERRUPT_ENABLE,
				 DRP0_INTERRUPT_ENABLE);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(llcc_bcast_regmap, DRP_INTERRUPT_ENABLE,
			   SB_DB_DRP_INTERRUPT_ENABLE);
	वापस ret;
पूर्ण

/* Clear the error पूर्णांकerrupt and counter रेजिस्टरs */
अटल पूर्णांक
qcom_llcc_clear_error_status(पूर्णांक err_type, काष्ठा llcc_drv_data *drv)
अणु
	पूर्णांक ret = 0;

	चयन (err_type) अणु
	हाल LLCC_DRAM_CE:
	हाल LLCC_DRAM_UE:
		ret = regmap_ग_लिखो(drv->bcast_regmap, DRP_INTERRUPT_CLEAR,
				   DRP_TRP_INT_CLEAR);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(drv->bcast_regmap, DRP_ECC_ERROR_CNTR_CLEAR,
				   DRP_TRP_CNT_CLEAR);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल LLCC_TRAM_CE:
	हाल LLCC_TRAM_UE:
		ret = regmap_ग_लिखो(drv->bcast_regmap, TRP_INTERRUPT_0_CLEAR,
				   DRP_TRP_INT_CLEAR);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(drv->bcast_regmap, TRP_ECC_ERROR_CNTR_CLEAR,
				   DRP_TRP_CNT_CLEAR);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		ret = -EINVAL;
		edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC, "Unexpected error type: %d\n",
			    err_type);
	पूर्ण
	वापस ret;
पूर्ण

/* Dump Syndrome रेजिस्टरs data क्रम Tag RAM, Data RAM bit errors*/
अटल पूर्णांक
dump_syn_reg_values(काष्ठा llcc_drv_data *drv, u32 bank, पूर्णांक err_type)
अणु
	काष्ठा llcc_edac_reg_data reg_data = edac_reg_data[err_type];
	पूर्णांक err_cnt, err_ways, ret, i;
	u32 synd_reg, synd_val;

	क्रम (i = 0; i < reg_data.reg_cnt; i++) अणु
		synd_reg = reg_data.synd_reg + (i * 4);
		ret = regmap_पढ़ो(drv->regmap, drv->offsets[bank] + synd_reg,
				  &synd_val);
		अगर (ret)
			जाओ clear;

		edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC, "%s: ECC_SYN%d: 0x%8x\n",
			    reg_data.name, i, synd_val);
	पूर्ण

	ret = regmap_पढ़ो(drv->regmap,
			  drv->offsets[bank] + reg_data.count_status_reg,
			  &err_cnt);
	अगर (ret)
		जाओ clear;

	err_cnt &= reg_data.count_mask;
	err_cnt >>= reg_data.count_shअगरt;
	edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC, "%s: Error count: 0x%4x\n",
		    reg_data.name, err_cnt);

	ret = regmap_पढ़ो(drv->regmap,
			  drv->offsets[bank] + reg_data.ways_status_reg,
			  &err_ways);
	अगर (ret)
		जाओ clear;

	err_ways &= reg_data.ways_mask;
	err_ways >>= reg_data.ways_shअगरt;

	edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC, "%s: Error ways: 0x%4x\n",
		    reg_data.name, err_ways);

clear:
	वापस qcom_llcc_clear_error_status(err_type, drv);
पूर्ण

अटल पूर्णांक
dump_syn_reg(काष्ठा edac_device_ctl_info *edev_ctl, पूर्णांक err_type, u32 bank)
अणु
	काष्ठा llcc_drv_data *drv = edev_ctl->pvt_info;
	पूर्णांक ret;

	ret = dump_syn_reg_values(drv, bank, err_type);
	अगर (ret)
		वापस ret;

	चयन (err_type) अणु
	हाल LLCC_DRAM_CE:
		edac_device_handle_ce(edev_ctl, 0, bank,
				      "LLCC Data RAM correctable Error");
		अवरोध;
	हाल LLCC_DRAM_UE:
		edac_device_handle_ue(edev_ctl, 0, bank,
				      "LLCC Data RAM uncorrectable Error");
		अवरोध;
	हाल LLCC_TRAM_CE:
		edac_device_handle_ce(edev_ctl, 0, bank,
				      "LLCC Tag RAM correctable Error");
		अवरोध;
	हाल LLCC_TRAM_UE:
		edac_device_handle_ue(edev_ctl, 0, bank,
				      "LLCC Tag RAM uncorrectable Error");
		अवरोध;
	शेष:
		ret = -EINVAL;
		edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC, "Unexpected error type: %d\n",
			    err_type);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t
llcc_ecc_irq_handler(पूर्णांक irq, व्योम *edev_ctl)
अणु
	काष्ठा edac_device_ctl_info *edac_dev_ctl = edev_ctl;
	काष्ठा llcc_drv_data *drv = edac_dev_ctl->pvt_info;
	irqवापस_t irq_rc = IRQ_NONE;
	u32 drp_error, trp_error, i;
	पूर्णांक ret;

	/* Iterate over the banks and look क्रम Tag RAM or Data RAM errors */
	क्रम (i = 0; i < drv->num_banks; i++) अणु
		ret = regmap_पढ़ो(drv->regmap,
				  drv->offsets[i] + DRP_INTERRUPT_STATUS,
				  &drp_error);

		अगर (!ret && (drp_error & SB_ECC_ERROR)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC,
				    "Single Bit Error detected in Data RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_DRAM_CE, i);
		पूर्ण अन्यथा अगर (!ret && (drp_error & DB_ECC_ERROR)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC,
				    "Double Bit Error detected in Data RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_DRAM_UE, i);
		पूर्ण
		अगर (!ret)
			irq_rc = IRQ_HANDLED;

		ret = regmap_पढ़ो(drv->regmap,
				  drv->offsets[i] + TRP_INTERRUPT_0_STATUS,
				  &trp_error);

		अगर (!ret && (trp_error & SB_ECC_ERROR)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC,
				    "Single Bit Error detected in Tag RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_TRAM_CE, i);
		पूर्ण अन्यथा अगर (!ret && (trp_error & DB_ECC_ERROR)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_LLCC,
				    "Double Bit Error detected in Tag RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_TRAM_UE, i);
		पूर्ण
		अगर (!ret)
			irq_rc = IRQ_HANDLED;
	पूर्ण

	वापस irq_rc;
पूर्ण

अटल पूर्णांक qcom_llcc_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा llcc_drv_data *llcc_driv_data = pdev->dev.platक्रमm_data;
	काष्ठा edac_device_ctl_info *edev_ctl;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ecc_irq;
	पूर्णांक rc;

	rc = qcom_llcc_core_setup(llcc_driv_data->bcast_regmap);
	अगर (rc)
		वापस rc;

	/* Allocate edac control info */
	edev_ctl = edac_device_alloc_ctl_info(0, "qcom-llcc", 1, "bank",
					      llcc_driv_data->num_banks, 1,
					      शून्य, 0,
					      edac_device_alloc_index());

	अगर (!edev_ctl)
		वापस -ENOMEM;

	edev_ctl->dev = dev;
	edev_ctl->mod_name = dev_name(dev);
	edev_ctl->dev_name = dev_name(dev);
	edev_ctl->ctl_name = "llcc";
	edev_ctl->panic_on_ue = LLCC_ERP_PANIC_ON_UE;
	edev_ctl->pvt_info = llcc_driv_data;

	rc = edac_device_add_device(edev_ctl);
	अगर (rc)
		जाओ out_mem;

	platक्रमm_set_drvdata(pdev, edev_ctl);

	/* Request क्रम ecc irq */
	ecc_irq = llcc_driv_data->ecc_irq;
	अगर (ecc_irq < 0) अणु
		rc = -ENODEV;
		जाओ out_dev;
	पूर्ण
	rc = devm_request_irq(dev, ecc_irq, llcc_ecc_irq_handler,
			      IRQF_TRIGGER_HIGH, "llcc_ecc", edev_ctl);
	अगर (rc)
		जाओ out_dev;

	वापस rc;

out_dev:
	edac_device_del_device(edev_ctl->dev);
out_mem:
	edac_device_मुक्त_ctl_info(edev_ctl);

	वापस rc;
पूर्ण

अटल पूर्णांक qcom_llcc_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *edev_ctl = dev_get_drvdata(&pdev->dev);

	edac_device_del_device(edev_ctl->dev);
	edac_device_मुक्त_ctl_info(edev_ctl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_llcc_edac_driver = अणु
	.probe = qcom_llcc_edac_probe,
	.हटाओ = qcom_llcc_edac_हटाओ,
	.driver = अणु
		.name = "qcom_llcc_edac",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_llcc_edac_driver);

MODULE_DESCRIPTION("QCOM EDAC driver");
MODULE_LICENSE("GPL v2");
