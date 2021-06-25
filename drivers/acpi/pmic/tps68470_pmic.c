<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI TPS68470 PMIC operation region driver
 *
 * Copyright (C) 2017 Intel Corporation. All rights reserved.
 *
 * Author: Rajmohan Mani <rajmohan.mani@पूर्णांकel.com>
 *
 * Based on drivers/acpi/pmic/पूर्णांकel_pmic* drivers
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/tps68470.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

काष्ठा tps68470_pmic_table अणु
	u32 address;		/* operation region address */
	u32 reg;		/* corresponding रेजिस्टर */
	u32 biपंचांगask;		/* bit mask क्रम घातer, घड़ी */
पूर्ण;

#घोषणा TI_PMIC_POWER_OPREGION_ID		0xB0
#घोषणा TI_PMIC_VR_VAL_OPREGION_ID		0xB1
#घोषणा TI_PMIC_CLOCK_OPREGION_ID		0xB2
#घोषणा TI_PMIC_CLKFREQ_OPREGION_ID		0xB3

काष्ठा tps68470_pmic_opregion अणु
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा S_IO_I2C_EN	(BIT(0) | BIT(1))

अटल स्थिर काष्ठा tps68470_pmic_table घातer_table[] = अणु
	अणु
		.address = 0x00,
		.reg = TPS68470_REG_S_I2C_CTL,
		.biपंचांगask = S_IO_I2C_EN,
		/* S_I2C_CTL */
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = TPS68470_REG_VCMCTL,
		.biपंचांगask = BIT(0),
		/* VCMCTL */
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = TPS68470_REG_VAUX1CTL,
		.biपंचांगask = BIT(0),
		/* VAUX1_CTL */
	पूर्ण,
	अणु
		.address = 0x0C,
		.reg = TPS68470_REG_VAUX2CTL,
		.biपंचांगask = BIT(0),
		/* VAUX2CTL */
	पूर्ण,
	अणु
		.address = 0x10,
		.reg = TPS68470_REG_VACTL,
		.biपंचांगask = BIT(0),
		/* VACTL */
	पूर्ण,
	अणु
		.address = 0x14,
		.reg = TPS68470_REG_VDCTL,
		.biपंचांगask = BIT(0),
		/* VDCTL */
	पूर्ण,
पूर्ण;

/* Table to set voltage regulator value */
अटल स्थिर काष्ठा tps68470_pmic_table vr_val_table[] = अणु
	अणु
		.address = 0x00,
		.reg = TPS68470_REG_VSIOVAL,
		.biपंचांगask = TPS68470_VSIOVAL_IOVOLT_MASK,
		/* TPS68470_REG_VSIOVAL */
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = TPS68470_REG_VIOVAL,
		.biपंचांगask = TPS68470_VIOVAL_IOVOLT_MASK,
		/* TPS68470_REG_VIOVAL */
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = TPS68470_REG_VCMVAL,
		.biपंचांगask = TPS68470_VCMVAL_VCVOLT_MASK,
		/* TPS68470_REG_VCMVAL */
	पूर्ण,
	अणु
		.address = 0x0C,
		.reg = TPS68470_REG_VAUX1VAL,
		.biपंचांगask = TPS68470_VAUX1VAL_AUX1VOLT_MASK,
		/* TPS68470_REG_VAUX1VAL */
	पूर्ण,
	अणु
		.address = 0x10,
		.reg = TPS68470_REG_VAUX2VAL,
		.biपंचांगask = TPS68470_VAUX2VAL_AUX2VOLT_MASK,
		/* TPS68470_REG_VAUX2VAL */
	पूर्ण,
	अणु
		.address = 0x14,
		.reg = TPS68470_REG_VAVAL,
		.biपंचांगask = TPS68470_VAVAL_AVOLT_MASK,
		/* TPS68470_REG_VAVAL */
	पूर्ण,
	अणु
		.address = 0x18,
		.reg = TPS68470_REG_VDVAL,
		.biपंचांगask = TPS68470_VDVAL_DVOLT_MASK,
		/* TPS68470_REG_VDVAL */
	पूर्ण,
पूर्ण;

/* Table to configure घड़ी frequency */
अटल स्थिर काष्ठा tps68470_pmic_table clk_freq_table[] = अणु
	अणु
		.address = 0x00,
		.reg = TPS68470_REG_POSTDIV2,
		.biपंचांगask = BIT(0) | BIT(1),
		/* TPS68470_REG_POSTDIV2 */
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = TPS68470_REG_BOOSTDIV,
		.biपंचांगask = 0x1F,
		/* TPS68470_REG_BOOSTDIV */
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = TPS68470_REG_BUCKDIV,
		.biपंचांगask = 0x0F,
		/* TPS68470_REG_BUCKDIV */
	पूर्ण,
	अणु
		.address = 0x0C,
		.reg = TPS68470_REG_PLLSWR,
		.biपंचांगask = 0x13,
		/* TPS68470_REG_PLLSWR */
	पूर्ण,
	अणु
		.address = 0x10,
		.reg = TPS68470_REG_XTALDIV,
		.biपंचांगask = 0xFF,
		/* TPS68470_REG_XTALDIV */
	पूर्ण,
	अणु
		.address = 0x14,
		.reg = TPS68470_REG_PLLDIV,
		.biपंचांगask = 0xFF,
		/* TPS68470_REG_PLLDIV */
	पूर्ण,
	अणु
		.address = 0x18,
		.reg = TPS68470_REG_POSTDIV,
		.biपंचांगask = 0x83,
		/* TPS68470_REG_POSTDIV */
	पूर्ण,
पूर्ण;

/* Table to configure and enable घड़ीs */
अटल स्थिर काष्ठा tps68470_pmic_table clk_table[] = अणु
	अणु
		.address = 0x00,
		.reg = TPS68470_REG_PLLCTL,
		.biपंचांगask = 0xF5,
		/* TPS68470_REG_PLLCTL */
	पूर्ण,
	अणु
		.address = 0x04,
		.reg = TPS68470_REG_PLLCTL2,
		.biपंचांगask = BIT(0),
		/* TPS68470_REG_PLLCTL2 */
	पूर्ण,
	अणु
		.address = 0x08,
		.reg = TPS68470_REG_CLKCFG1,
		.biपंचांगask = TPS68470_CLKCFG1_MODE_A_MASK |
			TPS68470_CLKCFG1_MODE_B_MASK,
		/* TPS68470_REG_CLKCFG1 */
	पूर्ण,
	अणु
		.address = 0x0C,
		.reg = TPS68470_REG_CLKCFG2,
		.biपंचांगask = TPS68470_CLKCFG1_MODE_A_MASK |
			TPS68470_CLKCFG1_MODE_B_MASK,
		/* TPS68470_REG_CLKCFG2 */
	पूर्ण,
पूर्ण;

अटल पूर्णांक pmic_get_reg_bit(u64 address,
			    स्थिर काष्ठा tps68470_pmic_table *table,
			    स्थिर अचिन्हित पूर्णांक table_size, पूर्णांक *reg,
			    पूर्णांक *biपंचांगask)
अणु
	u64 i;

	i = address / 4;
	अगर (i >= table_size)
		वापस -ENOENT;

	अगर (!reg || !biपंचांगask)
		वापस -EINVAL;

	*reg = table[i].reg;
	*biपंचांगask = table[i].biपंचांगask;

	वापस 0;
पूर्ण

अटल पूर्णांक tps68470_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक biपंचांगask, u64 *value)
अणु
	अचिन्हित पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = (data & biपंचांगask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tps68470_pmic_get_vr_val(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक biपंचांगask, u64 *value)
अणु
	अचिन्हित पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = data & biपंचांगask;
	वापस 0;
पूर्ण

अटल पूर्णांक tps68470_pmic_get_clk(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक biपंचांगask, u64 *value)
अणु
	अचिन्हित पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = (data & biपंचांगask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tps68470_pmic_get_clk_freq(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक biपंचांगask, u64 *value)
अणु
	अचिन्हित पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	*value = data & biपंचांगask;
	वापस 0;
पूर्ण

अटल पूर्णांक ti_tps68470_regmap_update_bits(काष्ठा regmap *regmap, पूर्णांक reg,
					पूर्णांक biपंचांगask, u64 value)
अणु
	वापस regmap_update_bits(regmap, reg, biपंचांगask, value);
पूर्ण

अटल acpi_status tps68470_pmic_common_handler(u32 function,
					  acpi_physical_address address,
					  u32 bits, u64 *value,
					  व्योम *region_context,
					  पूर्णांक (*get)(काष्ठा regmap *,
						     पूर्णांक, पूर्णांक, u64 *),
					  पूर्णांक (*update)(काष्ठा regmap *,
							पूर्णांक, पूर्णांक, u64),
					  स्थिर काष्ठा tps68470_pmic_table *tbl,
					  अचिन्हित पूर्णांक tbl_size)
अणु
	काष्ठा tps68470_pmic_opregion *opregion = region_context;
	काष्ठा regmap *regmap = opregion->regmap;
	पूर्णांक reg, ret, biपंचांगask;

	अगर (bits != 32)
		वापस AE_BAD_PARAMETER;

	ret = pmic_get_reg_bit(address, tbl, tbl_size, &reg, &biपंचांगask);
	अगर (ret < 0)
		वापस AE_BAD_PARAMETER;

	अगर (function == ACPI_WRITE && *value > biपंचांगask)
		वापस AE_BAD_PARAMETER;

	mutex_lock(&opregion->lock);

	ret = (function == ACPI_READ) ?
		get(regmap, reg, biपंचांगask, value) :
		update(regmap, reg, biपंचांगask, *value);

	mutex_unlock(&opregion->lock);

	वापस ret ? AE_ERROR : AE_OK;
पूर्ण

अटल acpi_status tps68470_pmic_cfreq_handler(u32 function,
					    acpi_physical_address address,
					    u32 bits, u64 *value,
					    व्योम *handler_context,
					    व्योम *region_context)
अणु
	वापस tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_clk_freq,
				ti_tps68470_regmap_update_bits,
				clk_freq_table,
				ARRAY_SIZE(clk_freq_table));
पूर्ण

अटल acpi_status tps68470_pmic_clk_handler(u32 function,
				       acpi_physical_address address, u32 bits,
				       u64 *value, व्योम *handler_context,
				       व्योम *region_context)
अणु
	वापस tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_clk,
				ti_tps68470_regmap_update_bits,
				clk_table,
				ARRAY_SIZE(clk_table));
पूर्ण

अटल acpi_status tps68470_pmic_vrval_handler(u32 function,
					  acpi_physical_address address,
					  u32 bits, u64 *value,
					  व्योम *handler_context,
					  व्योम *region_context)
अणु
	वापस tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_vr_val,
				ti_tps68470_regmap_update_bits,
				vr_val_table,
				ARRAY_SIZE(vr_val_table));
पूर्ण

अटल acpi_status tps68470_pmic_pwr_handler(u32 function,
					 acpi_physical_address address,
					 u32 bits, u64 *value,
					 व्योम *handler_context,
					 व्योम *region_context)
अणु
	अगर (bits != 32)
		वापस AE_BAD_PARAMETER;

	/* set/clear क्रम bit 0, bits 0 and 1 together */
	अगर (function == ACPI_WRITE &&
	    !(*value == 0 || *value == 1 || *value == 3)) अणु
		वापस AE_BAD_PARAMETER;
	पूर्ण

	वापस tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_घातer,
				ti_tps68470_regmap_update_bits,
				घातer_table,
				ARRAY_SIZE(घातer_table));
पूर्ण

अटल पूर्णांक tps68470_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *tps68470_regmap = dev_get_drvdata(pdev->dev.parent);
	acpi_handle handle = ACPI_HANDLE(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tps68470_pmic_opregion *opregion;
	acpi_status status;

	अगर (!dev || !tps68470_regmap) अणु
		dev_warn(dev, "dev or regmap is NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!handle) अणु
		dev_warn(dev, "acpi handle is NULL\n");
		वापस -ENODEV;
	पूर्ण

	opregion = devm_kzalloc(dev, माप(*opregion), GFP_KERNEL);
	अगर (!opregion)
		वापस -ENOMEM;

	mutex_init(&opregion->lock);
	opregion->regmap = tps68470_regmap;

	status = acpi_install_address_space_handler(handle,
						    TI_PMIC_POWER_OPREGION_ID,
						    tps68470_pmic_pwr_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status))
		जाओ out_mutex_destroy;

	status = acpi_install_address_space_handler(handle,
						    TI_PMIC_VR_VAL_OPREGION_ID,
						    tps68470_pmic_vrval_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status))
		जाओ out_हटाओ_घातer_handler;

	status = acpi_install_address_space_handler(handle,
						    TI_PMIC_CLOCK_OPREGION_ID,
						    tps68470_pmic_clk_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status))
		जाओ out_हटाओ_vr_val_handler;

	status = acpi_install_address_space_handler(handle,
						    TI_PMIC_CLKFREQ_OPREGION_ID,
						    tps68470_pmic_cfreq_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status))
		जाओ out_हटाओ_clk_handler;

	वापस 0;

out_हटाओ_clk_handler:
	acpi_हटाओ_address_space_handler(handle, TI_PMIC_CLOCK_OPREGION_ID,
					  tps68470_pmic_clk_handler);
out_हटाओ_vr_val_handler:
	acpi_हटाओ_address_space_handler(handle, TI_PMIC_VR_VAL_OPREGION_ID,
					  tps68470_pmic_vrval_handler);
out_हटाओ_घातer_handler:
	acpi_हटाओ_address_space_handler(handle, TI_PMIC_POWER_OPREGION_ID,
					  tps68470_pmic_pwr_handler);
out_mutex_destroy:
	mutex_destroy(&opregion->lock);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा platक्रमm_driver tps68470_pmic_opregion_driver = अणु
	.probe = tps68470_pmic_opregion_probe,
	.driver = अणु
		.name = "tps68470_pmic_opregion",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(tps68470_pmic_opregion_driver)
