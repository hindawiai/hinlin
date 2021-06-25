<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pmic.c - Intel PMIC operation region driver
 *
 * Copyright (C) 2014 Intel Corporation. All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/regmap.h>
#समावेश <acpi/acpi_lpat.h>
#समावेश "intel_pmic.h"

#घोषणा PMIC_POWER_OPREGION_ID		0x8d
#घोषणा PMIC_THERMAL_OPREGION_ID	0x8c
#घोषणा PMIC_REGS_OPREGION_ID		0x8f

काष्ठा पूर्णांकel_pmic_regs_handler_ctx अणु
	अचिन्हित पूर्णांक val;
	u16 addr;
पूर्ण;

काष्ठा पूर्णांकel_pmic_opregion अणु
	काष्ठा mutex lock;
	काष्ठा acpi_lpat_conversion_table *lpat_table;
	काष्ठा regmap *regmap;
	काष्ठा पूर्णांकel_pmic_opregion_data *data;
	काष्ठा पूर्णांकel_pmic_regs_handler_ctx ctx;
पूर्ण;

अटल काष्ठा पूर्णांकel_pmic_opregion *पूर्णांकel_pmic_opregion;

अटल पूर्णांक pmic_get_reg_bit(पूर्णांक address, काष्ठा pmic_table *table,
			    पूर्णांक count, पूर्णांक *reg, पूर्णांक *bit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (table[i].address == address) अणु
			*reg = table[i].reg;
			अगर (bit)
				*bit = table[i].bit;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल acpi_status पूर्णांकel_pmic_घातer_handler(u32 function,
		acpi_physical_address address, u32 bits, u64 *value64,
		व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा पूर्णांकel_pmic_opregion *opregion = region_context;
	काष्ठा regmap *regmap = opregion->regmap;
	काष्ठा पूर्णांकel_pmic_opregion_data *d = opregion->data;
	पूर्णांक reg, bit, result;

	अगर (bits != 32 || !value64)
		वापस AE_BAD_PARAMETER;

	अगर (function == ACPI_WRITE && !(*value64 == 0 || *value64 == 1))
		वापस AE_BAD_PARAMETER;

	result = pmic_get_reg_bit(address, d->घातer_table,
				  d->घातer_table_count, &reg, &bit);
	अगर (result == -ENOENT)
		वापस AE_BAD_PARAMETER;

	mutex_lock(&opregion->lock);

	result = function == ACPI_READ ?
		d->get_घातer(regmap, reg, bit, value64) :
		d->update_घातer(regmap, reg, bit, *value64 == 1);

	mutex_unlock(&opregion->lock);

	वापस result ? AE_ERROR : AE_OK;
पूर्ण

अटल पूर्णांक pmic_पढ़ो_temp(काष्ठा पूर्णांकel_pmic_opregion *opregion,
			  पूर्णांक reg, u64 *value)
अणु
	पूर्णांक raw_temp, temp;

	अगर (!opregion->data->get_raw_temp)
		वापस -ENXIO;

	raw_temp = opregion->data->get_raw_temp(opregion->regmap, reg);
	अगर (raw_temp < 0)
		वापस raw_temp;

	अगर (!opregion->lpat_table) अणु
		*value = raw_temp;
		वापस 0;
	पूर्ण

	temp = acpi_lpat_raw_to_temp(opregion->lpat_table, raw_temp);
	अगर (temp < 0)
		वापस temp;

	*value = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_thermal_temp(काष्ठा पूर्णांकel_pmic_opregion *opregion, पूर्णांक reg,
			     u32 function, u64 *value)
अणु
	वापस function == ACPI_READ ?
		pmic_पढ़ो_temp(opregion, reg, value) : -EINVAL;
पूर्ण

अटल पूर्णांक pmic_thermal_aux(काष्ठा पूर्णांकel_pmic_opregion *opregion, पूर्णांक reg,
			    u32 function, u64 *value)
अणु
	पूर्णांक raw_temp;

	अगर (function == ACPI_READ)
		वापस pmic_पढ़ो_temp(opregion, reg, value);

	अगर (!opregion->data->update_aux)
		वापस -ENXIO;

	अगर (opregion->lpat_table) अणु
		raw_temp = acpi_lpat_temp_to_raw(opregion->lpat_table, *value);
		अगर (raw_temp < 0)
			वापस raw_temp;
	पूर्ण अन्यथा अणु
		raw_temp = *value;
	पूर्ण

	वापस opregion->data->update_aux(opregion->regmap, reg, raw_temp);
पूर्ण

अटल पूर्णांक pmic_thermal_pen(काष्ठा पूर्णांकel_pmic_opregion *opregion, पूर्णांक reg,
			    पूर्णांक bit, u32 function, u64 *value)
अणु
	काष्ठा पूर्णांकel_pmic_opregion_data *d = opregion->data;
	काष्ठा regmap *regmap = opregion->regmap;

	अगर (!d->get_policy || !d->update_policy)
		वापस -ENXIO;

	अगर (function == ACPI_READ)
		वापस d->get_policy(regmap, reg, bit, value);

	अगर (*value != 0 && *value != 1)
		वापस -EINVAL;

	वापस d->update_policy(regmap, reg, bit, *value);
पूर्ण

अटल bool pmic_thermal_is_temp(पूर्णांक address)
अणु
	वापस (address <= 0x3c) && !(address % 12);
पूर्ण

अटल bool pmic_thermal_is_aux(पूर्णांक address)
अणु
	वापस (address >= 4 && address <= 0x40 && !((address - 4) % 12)) ||
	       (address >= 8 && address <= 0x44 && !((address - 8) % 12));
पूर्ण

अटल bool pmic_thermal_is_pen(पूर्णांक address)
अणु
	वापस address >= 0x48 && address <= 0x5c;
पूर्ण

अटल acpi_status पूर्णांकel_pmic_thermal_handler(u32 function,
		acpi_physical_address address, u32 bits, u64 *value64,
		व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा पूर्णांकel_pmic_opregion *opregion = region_context;
	काष्ठा पूर्णांकel_pmic_opregion_data *d = opregion->data;
	पूर्णांक reg, bit, result;

	अगर (bits != 32 || !value64)
		वापस AE_BAD_PARAMETER;

	result = pmic_get_reg_bit(address, d->thermal_table,
				  d->thermal_table_count, &reg, &bit);
	अगर (result == -ENOENT)
		वापस AE_BAD_PARAMETER;

	mutex_lock(&opregion->lock);

	अगर (pmic_thermal_is_temp(address))
		result = pmic_thermal_temp(opregion, reg, function, value64);
	अन्यथा अगर (pmic_thermal_is_aux(address))
		result = pmic_thermal_aux(opregion, reg, function, value64);
	अन्यथा अगर (pmic_thermal_is_pen(address))
		result = pmic_thermal_pen(opregion, reg, bit,
						function, value64);
	अन्यथा
		result = -EINVAL;

	mutex_unlock(&opregion->lock);

	अगर (result < 0) अणु
		अगर (result == -EINVAL)
			वापस AE_BAD_PARAMETER;
		अन्यथा
			वापस AE_ERROR;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल acpi_status पूर्णांकel_pmic_regs_handler(u32 function,
		acpi_physical_address address, u32 bits, u64 *value64,
		व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा पूर्णांकel_pmic_opregion *opregion = region_context;
	पूर्णांक result = 0;

	चयन (address) अणु
	हाल 0:
		वापस AE_OK;
	हाल 1:
		opregion->ctx.addr |= (*value64 & 0xff) << 8;
		वापस AE_OK;
	हाल 2:
		opregion->ctx.addr |= *value64 & 0xff;
		वापस AE_OK;
	हाल 3:
		opregion->ctx.val = *value64 & 0xff;
		वापस AE_OK;
	हाल 4:
		अगर (*value64) अणु
			result = regmap_ग_लिखो(opregion->regmap, opregion->ctx.addr,
					      opregion->ctx.val);
		पूर्ण अन्यथा अणु
			result = regmap_पढ़ो(opregion->regmap, opregion->ctx.addr,
					     &opregion->ctx.val);
			अगर (result == 0)
				*value64 = opregion->ctx.val;
		पूर्ण
		स_रखो(&opregion->ctx, 0x00, माप(opregion->ctx));
	पूर्ण

	अगर (result < 0) अणु
		अगर (result == -EINVAL)
			वापस AE_BAD_PARAMETER;
		अन्यथा
			वापस AE_ERROR;
	पूर्ण

	वापस AE_OK;
पूर्ण

पूर्णांक पूर्णांकel_pmic_install_opregion_handler(काष्ठा device *dev, acpi_handle handle,
					काष्ठा regmap *regmap,
					काष्ठा पूर्णांकel_pmic_opregion_data *d)
अणु
	acpi_status status = AE_OK;
	काष्ठा पूर्णांकel_pmic_opregion *opregion;
	पूर्णांक ret;

	अगर (!dev || !regmap || !d)
		वापस -EINVAL;

	अगर (!handle)
		वापस -ENODEV;

	opregion = devm_kzalloc(dev, माप(*opregion), GFP_KERNEL);
	अगर (!opregion)
		वापस -ENOMEM;

	mutex_init(&opregion->lock);
	opregion->regmap = regmap;
	opregion->lpat_table = acpi_lpat_get_conversion_table(handle);

	अगर (d->घातer_table_count)
		status = acpi_install_address_space_handler(handle,
						    PMIC_POWER_OPREGION_ID,
						    पूर्णांकel_pmic_घातer_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status)) अणु
		ret = -ENODEV;
		जाओ out_error;
	पूर्ण

	अगर (d->thermal_table_count)
		status = acpi_install_address_space_handler(handle,
						    PMIC_THERMAL_OPREGION_ID,
						    पूर्णांकel_pmic_thermal_handler,
						    शून्य, opregion);
	अगर (ACPI_FAILURE(status)) अणु
		ret = -ENODEV;
		जाओ out_हटाओ_घातer_handler;
	पूर्ण

	status = acpi_install_address_space_handler(handle,
			PMIC_REGS_OPREGION_ID, पूर्णांकel_pmic_regs_handler, शून्य,
			opregion);
	अगर (ACPI_FAILURE(status)) अणु
		ret = -ENODEV;
		जाओ out_हटाओ_thermal_handler;
	पूर्ण

	opregion->data = d;
	पूर्णांकel_pmic_opregion = opregion;
	वापस 0;

out_हटाओ_thermal_handler:
	अगर (d->thermal_table_count)
		acpi_हटाओ_address_space_handler(handle,
						  PMIC_THERMAL_OPREGION_ID,
						  पूर्णांकel_pmic_thermal_handler);

out_हटाओ_घातer_handler:
	अगर (d->घातer_table_count)
		acpi_हटाओ_address_space_handler(handle,
						  PMIC_POWER_OPREGION_ID,
						  पूर्णांकel_pmic_घातer_handler);

out_error:
	acpi_lpat_मुक्त_conversion_table(opregion->lpat_table);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmic_install_opregion_handler);

/**
 * पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element - Execute PMIC MIPI sequence
 * @i2c_address:  I2C client address क्रम the PMIC
 * @reg_address:  PMIC रेजिस्टर address
 * @value:        New value क्रम the रेजिस्टर bits to change
 * @mask:         Mask indicating which रेजिस्टर bits to change
 *
 * DSI LCD panels describe an initialization sequence in the i915 VBT (Video
 * BIOS Tables) using so called MIPI sequences. One possible element in these
 * sequences is a PMIC specअगरic element of 15 bytes.
 *
 * This function executes these PMIC specअगरic elements sending the embedded
 * commands to the PMIC.
 *
 * Return 0 on success, < 0 on failure.
 */
पूर्णांक पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element(u16 i2c_address, u32 reg_address,
					      u32 value, u32 mask)
अणु
	काष्ठा पूर्णांकel_pmic_opregion_data *d;
	पूर्णांक ret;

	अगर (!पूर्णांकel_pmic_opregion) अणु
		pr_warn("%s: No PMIC registered\n", __func__);
		वापस -ENXIO;
	पूर्ण

	d = पूर्णांकel_pmic_opregion->data;

	mutex_lock(&पूर्णांकel_pmic_opregion->lock);

	अगर (d->exec_mipi_pmic_seq_element) अणु
		ret = d->exec_mipi_pmic_seq_element(पूर्णांकel_pmic_opregion->regmap,
						    i2c_address, reg_address,
						    value, mask);
	पूर्ण अन्यथा अगर (d->pmic_i2c_address) अणु
		अगर (i2c_address == d->pmic_i2c_address) अणु
			ret = regmap_update_bits(पूर्णांकel_pmic_opregion->regmap,
						 reg_address, mask, value);
		पूर्ण अन्यथा अणु
			pr_err("%s: Unexpected i2c-addr: 0x%02x (reg-addr 0x%x value 0x%x mask 0x%x)\n",
			       __func__, i2c_address, reg_address, value, mask);
			ret = -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("%s: Not implemented\n", __func__);
		pr_warn("%s: i2c-addr: 0x%x reg-addr 0x%x value 0x%x mask 0x%x\n",
			__func__, i2c_address, reg_address, value, mask);
		ret = -EOPNOTSUPP;
	पूर्ण

	mutex_unlock(&पूर्णांकel_pmic_opregion->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element);
