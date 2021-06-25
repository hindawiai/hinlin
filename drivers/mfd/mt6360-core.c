<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 *
 * Author: Gene Chen <gene_chen@richtek.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/mfd/mt6360.h>

/* reg 0 -> 0 ~ 7 */
#घोषणा MT6360_CHG_TREG_EVT		(4)
#घोषणा MT6360_CHG_AICR_EVT		(5)
#घोषणा MT6360_CHG_MIVR_EVT		(6)
#घोषणा MT6360_PWR_RDY_EVT		(7)
/* REG 1 -> 8 ~ 15 */
#घोषणा MT6360_CHG_BATSYSUV_EVT		(9)
#घोषणा MT6360_FLED_CHG_VINOVP_EVT	(11)
#घोषणा MT6360_CHG_VSYSUV_EVT		(12)
#घोषणा MT6360_CHG_VSYSOV_EVT		(13)
#घोषणा MT6360_CHG_VBATOV_EVT		(14)
#घोषणा MT6360_CHG_VBUSOV_EVT		(15)
/* REG 2 -> 16 ~ 23 */
/* REG 3 -> 24 ~ 31 */
#घोषणा MT6360_WD_PMU_DET		(25)
#घोषणा MT6360_WD_PMU_DONE		(26)
#घोषणा MT6360_CHG_TMRI			(27)
#घोषणा MT6360_CHG_ADPBADI		(29)
#घोषणा MT6360_CHG_RVPI			(30)
#घोषणा MT6360_OTPI			(31)
/* REG 4 -> 32 ~ 39 */
#घोषणा MT6360_CHG_AICCMEASL		(32)
#घोषणा MT6360_CHGDET_DONEI		(34)
#घोषणा MT6360_WDTMRI			(35)
#घोषणा MT6360_SSFINISHI		(36)
#घोषणा MT6360_CHG_RECHGI		(37)
#घोषणा MT6360_CHG_TERMI		(38)
#घोषणा MT6360_CHG_IEOCI		(39)
/* REG 5 -> 40 ~ 47 */
#घोषणा MT6360_PUMPX_DONEI		(40)
#घोषणा MT6360_BAT_OVP_ADC_EVT		(41)
#घोषणा MT6360_TYPEC_OTP_EVT		(42)
#घोषणा MT6360_ADC_WAKEUP_EVT		(43)
#घोषणा MT6360_ADC_DONEI		(44)
#घोषणा MT6360_BST_BATUVI		(45)
#घोषणा MT6360_BST_VBUSOVI		(46)
#घोषणा MT6360_BST_OLPI			(47)
/* REG 6 -> 48 ~ 55 */
#घोषणा MT6360_ATTACH_I			(48)
#घोषणा MT6360_DETACH_I			(49)
#घोषणा MT6360_QC30_STPDONE		(51)
#घोषणा MT6360_QC_VBUSDET_DONE		(52)
#घोषणा MT6360_HVDCP_DET		(53)
#घोषणा MT6360_CHGDETI			(54)
#घोषणा MT6360_DCDTI			(55)
/* REG 7 -> 56 ~ 63 */
#घोषणा MT6360_FOD_DONE_EVT		(56)
#घोषणा MT6360_FOD_OV_EVT		(57)
#घोषणा MT6360_CHRDET_UVP_EVT		(58)
#घोषणा MT6360_CHRDET_OVP_EVT		(59)
#घोषणा MT6360_CHRDET_EXT_EVT		(60)
#घोषणा MT6360_FOD_LR_EVT		(61)
#घोषणा MT6360_FOD_HR_EVT		(62)
#घोषणा MT6360_FOD_DISCHG_FAIL_EVT	(63)
/* REG 8 -> 64 ~ 71 */
#घोषणा MT6360_USBID_EVT		(64)
#घोषणा MT6360_APWDTRST_EVT		(65)
#घोषणा MT6360_EN_EVT			(66)
#घोषणा MT6360_QONB_RST_EVT		(67)
#घोषणा MT6360_MRSTB_EVT		(68)
#घोषणा MT6360_OTP_EVT			(69)
#घोषणा MT6360_VDDAOV_EVT		(70)
#घोषणा MT6360_SYSUV_EVT		(71)
/* REG 9 -> 72 ~ 79 */
#घोषणा MT6360_FLED_STRBPIN_EVT		(72)
#घोषणा MT6360_FLED_TORPIN_EVT		(73)
#घोषणा MT6360_FLED_TX_EVT		(74)
#घोषणा MT6360_FLED_LVF_EVT		(75)
#घोषणा MT6360_FLED2_SHORT_EVT		(78)
#घोषणा MT6360_FLED1_SHORT_EVT		(79)
/* REG 10 -> 80 ~ 87 */
#घोषणा MT6360_FLED2_STRB_EVT		(80)
#घोषणा MT6360_FLED1_STRB_EVT		(81)
#घोषणा MT6360_FLED2_STRB_TO_EVT	(82)
#घोषणा MT6360_FLED1_STRB_TO_EVT	(83)
#घोषणा MT6360_FLED2_TOR_EVT		(84)
#घोषणा MT6360_FLED1_TOR_EVT		(85)
/* REG 11 -> 88 ~ 95 */
/* REG 12 -> 96 ~ 103 */
#घोषणा MT6360_BUCK1_PGB_EVT		(96)
#घोषणा MT6360_BUCK1_OC_EVT		(100)
#घोषणा MT6360_BUCK1_OV_EVT		(101)
#घोषणा MT6360_BUCK1_UV_EVT		(102)
/* REG 13 -> 104 ~ 111 */
#घोषणा MT6360_BUCK2_PGB_EVT		(104)
#घोषणा MT6360_BUCK2_OC_EVT		(108)
#घोषणा MT6360_BUCK2_OV_EVT		(109)
#घोषणा MT6360_BUCK2_UV_EVT		(110)
/* REG 14 -> 112 ~ 119 */
#घोषणा MT6360_LDO1_OC_EVT		(113)
#घोषणा MT6360_LDO2_OC_EVT		(114)
#घोषणा MT6360_LDO3_OC_EVT		(115)
#घोषणा MT6360_LDO5_OC_EVT		(117)
#घोषणा MT6360_LDO6_OC_EVT		(118)
#घोषणा MT6360_LDO7_OC_EVT		(119)
/* REG 15 -> 120 ~ 127 */
#घोषणा MT6360_LDO1_PGB_EVT		(121)
#घोषणा MT6360_LDO2_PGB_EVT		(122)
#घोषणा MT6360_LDO3_PGB_EVT		(123)
#घोषणा MT6360_LDO5_PGB_EVT		(125)
#घोषणा MT6360_LDO6_PGB_EVT		(126)
#घोषणा MT6360_LDO7_PGB_EVT		(127)

अटल स्थिर काष्ठा regmap_irq mt6360_pmu_irqs[] =  अणु
	REGMAP_IRQ_REG_LINE(MT6360_CHG_TREG_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_AICR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_MIVR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_PWR_RDY_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_BATSYSUV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED_CHG_VINOVP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_VSYSUV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_VSYSOV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_VBATOV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_VBUSOV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_WD_PMU_DET, 8),
	REGMAP_IRQ_REG_LINE(MT6360_WD_PMU_DONE, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_TMRI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_ADPBADI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_RVPI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_OTPI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_AICCMEASL, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHGDET_DONEI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_WDTMRI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_SSFINISHI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_RECHGI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_TERMI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHG_IEOCI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_PUMPX_DONEI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BAT_OVP_ADC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_TYPEC_OTP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_ADC_WAKEUP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_ADC_DONEI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BST_BATUVI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BST_VBUSOVI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BST_OLPI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_ATTACH_I, 8),
	REGMAP_IRQ_REG_LINE(MT6360_DETACH_I, 8),
	REGMAP_IRQ_REG_LINE(MT6360_QC30_STPDONE, 8),
	REGMAP_IRQ_REG_LINE(MT6360_QC_VBUSDET_DONE, 8),
	REGMAP_IRQ_REG_LINE(MT6360_HVDCP_DET, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHGDETI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_DCDTI, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FOD_DONE_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FOD_OV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHRDET_UVP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHRDET_OVP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_CHRDET_EXT_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FOD_LR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FOD_HR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FOD_DISCHG_FAIL_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_USBID_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_APWDTRST_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_EN_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_QONB_RST_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_MRSTB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_OTP_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_VDDAOV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_SYSUV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED_STRBPIN_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED_TORPIN_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED_TX_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED_LVF_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED2_SHORT_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED1_SHORT_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED2_STRB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED1_STRB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED2_STRB_TO_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED1_STRB_TO_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED2_TOR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_FLED1_TOR_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK1_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK1_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK1_OV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK1_UV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK2_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK2_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK2_OV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_BUCK2_UV_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO1_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO2_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO3_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO5_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO6_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO7_OC_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO1_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO2_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO3_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO5_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO6_PGB_EVT, 8),
	REGMAP_IRQ_REG_LINE(MT6360_LDO7_PGB_EVT, 8),
पूर्ण;

अटल पूर्णांक mt6360_pmu_handle_post_irq(व्योम *irq_drv_data)
अणु
	काष्ठा mt6360_pmu_data *mpd = irq_drv_data;

	वापस regmap_update_bits(mpd->regmap,
		MT6360_PMU_IRQ_SET, MT6360_IRQ_RETRIG, MT6360_IRQ_RETRIG);
पूर्ण

अटल काष्ठा regmap_irq_chip mt6360_pmu_irq_chip = अणु
	.irqs = mt6360_pmu_irqs,
	.num_irqs = ARRAY_SIZE(mt6360_pmu_irqs),
	.num_regs = MT6360_PMU_IRQ_REGNUM,
	.mask_base = MT6360_PMU_CHG_MASK1,
	.status_base = MT6360_PMU_CHG_IRQ1,
	.ack_base = MT6360_PMU_CHG_IRQ1,
	.init_ack_masked = true,
	.use_ack = true,
	.handle_post_irq = mt6360_pmu_handle_post_irq,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mt6360_pmu_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MT6360_PMU_MAXREG,
पूर्ण;

अटल स्थिर काष्ठा resource mt6360_adc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MT6360_ADC_DONEI, "adc_donei"),
पूर्ण;

अटल स्थिर काष्ठा resource mt6360_chg_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_TREG_EVT, "chg_treg_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_PWR_RDY_EVT, "pwr_rdy_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_BATSYSUV_EVT, "chg_batsysuv_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_VSYSUV_EVT, "chg_vsysuv_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_VSYSOV_EVT, "chg_vsysov_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_VBATOV_EVT, "chg_vbatov_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_VBUSOV_EVT, "chg_vbusov_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_AICCMEASL, "chg_aiccmeasl"),
	DEFINE_RES_IRQ_NAMED(MT6360_WDTMRI, "wdtmri"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_RECHGI, "chg_rechgi"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_TERMI, "chg_termi"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHG_IEOCI, "chg_ieoci"),
	DEFINE_RES_IRQ_NAMED(MT6360_PUMPX_DONEI, "pumpx_donei"),
	DEFINE_RES_IRQ_NAMED(MT6360_ATTACH_I, "attach_i"),
	DEFINE_RES_IRQ_NAMED(MT6360_CHRDET_EXT_EVT, "chrdet_ext_evt"),
पूर्ण;

अटल स्थिर काष्ठा resource mt6360_led_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MT6360_FLED_CHG_VINOVP_EVT, "fled_chg_vinovp_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_FLED_LVF_EVT, "fled_lvf_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_FLED2_SHORT_EVT, "fled2_short_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_FLED1_SHORT_EVT, "fled1_short_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_FLED2_STRB_TO_EVT, "fled2_strb_to_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_FLED1_STRB_TO_EVT, "fled1_strb_to_evt"),
पूर्ण;

अटल स्थिर काष्ठा resource mt6360_pmic_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK1_PGB_EVT, "buck1_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK1_OC_EVT, "buck1_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK1_OV_EVT, "buck1_ov_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK1_UV_EVT, "buck1_uv_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK2_PGB_EVT, "buck2_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK2_OC_EVT, "buck2_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK2_OV_EVT, "buck2_ov_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_BUCK2_UV_EVT, "buck2_uv_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO6_OC_EVT, "ldo6_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO7_OC_EVT, "ldo7_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO6_PGB_EVT, "ldo6_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO7_PGB_EVT, "ldo7_pgb_evt"),
पूर्ण;

अटल स्थिर काष्ठा resource mt6360_lकरो_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MT6360_LDO1_OC_EVT, "ldo1_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO2_OC_EVT, "ldo2_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO3_OC_EVT, "ldo3_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO5_OC_EVT, "ldo5_oc_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO1_PGB_EVT, "ldo1_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO2_PGB_EVT, "ldo2_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO3_PGB_EVT, "ldo3_pgb_evt"),
	DEFINE_RES_IRQ_NAMED(MT6360_LDO5_PGB_EVT, "ldo5_pgb_evt"),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell mt6360_devs[] = अणु
	MFD_CELL_OF("mt6360_adc", mt6360_adc_resources,
		    शून्य, 0, 0, "mediatek,mt6360_adc"),
	MFD_CELL_OF("mt6360_chg", mt6360_chg_resources,
		    शून्य, 0, 0, "mediatek,mt6360_chg"),
	MFD_CELL_OF("mt6360_led", mt6360_led_resources,
		    शून्य, 0, 0, "mediatek,mt6360_led"),
	MFD_CELL_OF("mt6360_pmic", mt6360_pmic_resources,
		    शून्य, 0, 0, "mediatek,mt6360_pmic"),
	MFD_CELL_OF("mt6360_ldo", mt6360_lकरो_resources,
		    शून्य, 0, 0, "mediatek,mt6360_ldo"),
	MFD_CELL_OF("mt6360_tcpc", शून्य,
		    शून्य, 0, 0, "mediatek,mt6360_tcpc"),
पूर्ण;

अटल स्थिर अचिन्हित लघु mt6360_slave_addr[MT6360_SLAVE_MAX] = अणु
	MT6360_PMU_SLAVEID,
	MT6360_PMIC_SLAVEID,
	MT6360_LDO_SLAVEID,
	MT6360_TCPC_SLAVEID,
पूर्ण;

अटल पूर्णांक mt6360_pmu_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt6360_pmu_data *mpd;
	अचिन्हित पूर्णांक reg_data;
	पूर्णांक i, ret;

	mpd = devm_kzalloc(&client->dev, माप(*mpd), GFP_KERNEL);
	अगर (!mpd)
		वापस -ENOMEM;

	mpd->dev = &client->dev;
	i2c_set_clientdata(client, mpd);

	mpd->regmap = devm_regmap_init_i2c(client, &mt6360_pmu_regmap_config);
	अगर (IS_ERR(mpd->regmap)) अणु
		dev_err(&client->dev, "Failed to register regmap\n");
		वापस PTR_ERR(mpd->regmap);
	पूर्ण

	ret = regmap_पढ़ो(mpd->regmap, MT6360_PMU_DEV_INFO, &reg_data);
	अगर (ret) अणु
		dev_err(&client->dev, "Device not found\n");
		वापस ret;
	पूर्ण

	mpd->chip_rev = reg_data & CHIP_REV_MASK;
	अगर (mpd->chip_rev != CHIP_VEN_MT6360) अणु
		dev_err(&client->dev, "Device not supported\n");
		वापस -ENODEV;
	पूर्ण

	mt6360_pmu_irq_chip.irq_drv_data = mpd;
	ret = devm_regmap_add_irq_chip(&client->dev, mpd->regmap, client->irq,
				       IRQF_TRIGGER_FALLING, 0,
				       &mt6360_pmu_irq_chip, &mpd->irq_data);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to add Regmap IRQ Chip\n");
		वापस ret;
	पूर्ण

	mpd->i2c[0] = client;
	क्रम (i = 1; i < MT6360_SLAVE_MAX; i++) अणु
		mpd->i2c[i] = devm_i2c_new_dummy_device(&client->dev,
							client->adapter,
							mt6360_slave_addr[i]);
		अगर (IS_ERR(mpd->i2c[i])) अणु
			dev_err(&client->dev,
				"Failed to get new dummy I2C device for address 0x%x",
				mt6360_slave_addr[i]);
			वापस PTR_ERR(mpd->i2c[i]);
		पूर्ण
		i2c_set_clientdata(mpd->i2c[i], mpd);
	पूर्ण

	ret = devm_mfd_add_devices(&client->dev, PLATFORM_DEVID_AUTO,
				   mt6360_devs, ARRAY_SIZE(mt6360_devs), शून्य,
				   0, regmap_irq_get_करोमुख्य(mpd->irq_data));
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to register subordinate devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6360_pmu_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(i2c->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6360_pmu_resume(काष्ठा device *dev)
अणु

	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(i2c->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mt6360_pmu_pm_ops,
			 mt6360_pmu_suspend, mt6360_pmu_resume);

अटल स्थिर काष्ठा of_device_id __maybe_unused mt6360_pmu_of_id[] = अणु
	अणु .compatible = "mediatek,mt6360_pmu", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6360_pmu_of_id);

अटल काष्ठा i2c_driver mt6360_pmu_driver = अणु
	.driver = अणु
		.name = "mt6360_pmu",
		.pm = &mt6360_pmu_pm_ops,
		.of_match_table = of_match_ptr(mt6360_pmu_of_id),
	पूर्ण,
	.probe_new = mt6360_pmu_probe,
पूर्ण;
module_i2c_driver(mt6360_pmu_driver);

MODULE_AUTHOR("Gene Chen <gene_chen@richtek.com>");
MODULE_DESCRIPTION("MT6360 PMU I2C Driver");
MODULE_LICENSE("GPL v2");
