<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel MAX 10 BMC HWMON Driver
 *
 * Copyright (C) 2018-2020 Intel Corporation. All rights reserved.
 *
 */
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/mfd/पूर्णांकel-m10-bmc.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा m10bmc_sdata अणु
	अचिन्हित पूर्णांक reg_input;
	अचिन्हित पूर्णांक reg_max;
	अचिन्हित पूर्णांक reg_crit;
	अचिन्हित पूर्णांक reg_hyst;
	अचिन्हित पूर्णांक reg_min;
	अचिन्हित पूर्णांक multiplier;
	स्थिर अक्षर *label;
पूर्ण;

काष्ठा m10bmc_hwmon_board_data अणु
	स्थिर काष्ठा m10bmc_sdata *tables[hwmon_max];
	स्थिर काष्ठा hwmon_channel_info **hinfo;
पूर्ण;

काष्ठा m10bmc_hwmon अणु
	काष्ठा device *dev;
	काष्ठा hwmon_chip_info chip;
	अक्षर *hw_name;
	काष्ठा पूर्णांकel_m10bmc *m10bmc;
	स्थिर काष्ठा m10bmc_hwmon_board_data *bdata;
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata n3000bmc_temp_tbl[] = अणु
	अणु 0x100, 0x104, 0x108, 0x10c, 0x0, 500, "Board Temperature" पूर्ण,
	अणु 0x110, 0x114, 0x118, 0x0, 0x0, 500, "FPGA Die Temperature" पूर्ण,
	अणु 0x11c, 0x124, 0x120, 0x0, 0x0, 500, "QSFP0 Temperature" पूर्ण,
	अणु 0x12c, 0x134, 0x130, 0x0, 0x0, 500, "QSFP1 Temperature" पूर्ण,
	अणु 0x168, 0x0, 0x0, 0x0, 0x0, 500, "Retimer A Temperature" पूर्ण,
	अणु 0x16c, 0x0, 0x0, 0x0, 0x0, 500, "Retimer A SerDes Temperature" पूर्ण,
	अणु 0x170, 0x0, 0x0, 0x0, 0x0, 500, "Retimer B Temperature" पूर्ण,
	अणु 0x174, 0x0, 0x0, 0x0, 0x0, 500, "Retimer B SerDes Temperature" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata n3000bmc_in_tbl[] = अणु
	अणु 0x128, 0x0, 0x0, 0x0, 0x0, 1, "QSFP0 Supply Voltage" पूर्ण,
	अणु 0x138, 0x0, 0x0, 0x0, 0x0, 1, "QSFP1 Supply Voltage" पूर्ण,
	अणु 0x13c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Core Voltage" पूर्ण,
	अणु 0x144, 0x0, 0x0, 0x0, 0x0, 1, "12V Backplane Voltage" पूर्ण,
	अणु 0x14c, 0x0, 0x0, 0x0, 0x0, 1, "1.2V Voltage" पूर्ण,
	अणु 0x150, 0x0, 0x0, 0x0, 0x0, 1, "12V AUX Voltage" पूर्ण,
	अणु 0x158, 0x0, 0x0, 0x0, 0x0, 1, "1.8V Voltage" पूर्ण,
	अणु 0x15c, 0x0, 0x0, 0x0, 0x0, 1, "3.3V Voltage" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata n3000bmc_curr_tbl[] = अणु
	अणु 0x140, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Core Current" पूर्ण,
	अणु 0x148, 0x0, 0x0, 0x0, 0x0, 1, "12V Backplane Current" पूर्ण,
	अणु 0x154, 0x0, 0x0, 0x0, 0x0, 1, "12V AUX Current" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata n3000bmc_घातer_tbl[] = अणु
	अणु 0x160, 0x0, 0x0, 0x0, 0x0, 1000, "Board Power" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *n3000bmc_hinfo[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL),
	HWMON_CHANNEL_INFO(घातer,
			   HWMON_P_INPUT | HWMON_P_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata d5005bmc_temp_tbl[] = अणु
	अणु 0x100, 0x104, 0x108, 0x10c, 0x0, 500, "Board Inlet Air Temperature" पूर्ण,
	अणु 0x110, 0x114, 0x118, 0x0, 0x0, 500, "FPGA Core Temperature" पूर्ण,
	अणु 0x11c, 0x120, 0x124, 0x128, 0x0, 500, "Board Exhaust Air Temperature" पूर्ण,
	अणु 0x12c, 0x130, 0x134, 0x0, 0x0, 500, "FPGA Transceiver Temperature" पूर्ण,
	अणु 0x138, 0x13c, 0x140, 0x144, 0x0, 500, "RDIMM0 Temperature" पूर्ण,
	अणु 0x148, 0x14c, 0x150, 0x154, 0x0, 500, "RDIMM1 Temperature" पूर्ण,
	अणु 0x158, 0x15c, 0x160, 0x164, 0x0, 500, "RDIMM2 Temperature" पूर्ण,
	अणु 0x168, 0x16c, 0x170, 0x174, 0x0, 500, "RDIMM3 Temperature" पूर्ण,
	अणु 0x178, 0x17c, 0x180, 0x0, 0x0, 500, "QSFP0 Temperature" पूर्ण,
	अणु 0x188, 0x18c, 0x190, 0x0, 0x0, 500, "QSFP1 Temperature" पूर्ण,
	अणु 0x1a0, 0x1a4, 0x1a8, 0x0, 0x0, 500, "3.3v Temperature" पूर्ण,
	अणु 0x1bc, 0x1c0, 0x1c4, 0x0, 0x0, 500, "VCCERAM Temperature" पूर्ण,
	अणु 0x1d8, 0x1dc, 0x1e0, 0x0, 0x0, 500, "VCCR Temperature" पूर्ण,
	अणु 0x1f4, 0x1f8, 0x1fc, 0x0, 0x0, 500, "VCCT Temperature" पूर्ण,
	अणु 0x210, 0x214, 0x218, 0x0, 0x0, 500, "1.8v Temperature" पूर्ण,
	अणु 0x22c, 0x230, 0x234, 0x0, 0x0, 500, "12v Backplane Temperature" पूर्ण,
	अणु 0x248, 0x24c, 0x250, 0x0, 0x0, 500, "12v AUX Temperature" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata d5005bmc_in_tbl[] = अणु
	अणु 0x184, 0x0, 0x0, 0x0, 0x0, 1, "QSFP0 Supply Voltage" पूर्ण,
	अणु 0x194, 0x0, 0x0, 0x0, 0x0, 1, "QSFP1 Supply Voltage" पूर्ण,
	अणु 0x198, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Core Voltage" पूर्ण,
	अणु 0x1ac, 0x1b0, 0x1b4, 0x0, 0x0, 1, "3.3v Voltage" पूर्ण,
	अणु 0x1c8, 0x1cc, 0x1d0, 0x0, 0x0, 1, "VCCERAM Voltage" पूर्ण,
	अणु 0x1e4, 0x1e8, 0x1ec, 0x0, 0x0, 1, "VCCR Voltage" पूर्ण,
	अणु 0x200, 0x204, 0x208, 0x0, 0x0, 1, "VCCT Voltage" पूर्ण,
	अणु 0x21c, 0x220, 0x224, 0x0, 0x0, 1, "1.8v Voltage" पूर्ण,
	अणु 0x238, 0x0, 0x0, 0x0, 0x23c, 1, "12v Backplane Voltage" पूर्ण,
	अणु 0x254, 0x0, 0x0, 0x0, 0x258, 1, "12v AUX Voltage" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_sdata d5005bmc_curr_tbl[] = अणु
	अणु 0x19c, 0x0, 0x0, 0x0, 0x0, 1, "FPGA Core Current" पूर्ण,
	अणु 0x1b8, 0x0, 0x0, 0x0, 0x0, 1, "3.3v Current" पूर्ण,
	अणु 0x1d4, 0x0, 0x0, 0x0, 0x0, 1, "VCCERAM Current" पूर्ण,
	अणु 0x1f0, 0x0, 0x0, 0x0, 0x0, 1, "VCCR Current" पूर्ण,
	अणु 0x20c, 0x0, 0x0, 0x0, 0x0, 1, "VCCT Current" पूर्ण,
	अणु 0x228, 0x0, 0x0, 0x0, 0x0, 1, "1.8v Current" पूर्ण,
	अणु 0x240, 0x244, 0x0, 0x0, 0x0, 1, "12v Backplane Current" पूर्ण,
	अणु 0x25c, 0x260, 0x0, 0x0, 0x0, 1, "12v AUX Current" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा m10bmc_hwmon_board_data n3000bmc_hwmon_bdata = अणु
	.tables = अणु
		[hwmon_temp] = n3000bmc_temp_tbl,
		[hwmon_in] = n3000bmc_in_tbl,
		[hwmon_curr] = n3000bmc_curr_tbl,
		[hwmon_घातer] = n3000bmc_घातer_tbl,
	पूर्ण,

	.hinfo = n3000bmc_hinfo,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *d5005bmc_hinfo[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT |
			   HWMON_T_LABEL),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CRIT |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CRIT |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CRIT |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CRIT |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MAX | HWMON_I_CRIT |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_MAX | HWMON_C_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा m10bmc_hwmon_board_data d5005bmc_hwmon_bdata = अणु
	.tables = अणु
		[hwmon_temp] = d5005bmc_temp_tbl,
		[hwmon_in] = d5005bmc_in_tbl,
		[hwmon_curr] = d5005bmc_curr_tbl,
	पूर्ण,

	.hinfo = d5005bmc_hinfo,
पूर्ण;

अटल umode_t
m10bmc_hwmon_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल स्थिर काष्ठा m10bmc_sdata *
find_sensor_data(काष्ठा m10bmc_hwmon *hw, क्रमागत hwmon_sensor_types type,
		 पूर्णांक channel)
अणु
	स्थिर काष्ठा m10bmc_sdata *tbl;

	tbl = hw->bdata->tables[type];
	अगर (!tbl)
		वापस ERR_PTR(-EOPNOTSUPP);

	वापस &tbl[channel];
पूर्ण

अटल पूर्णांक करो_sensor_पढ़ो(काष्ठा m10bmc_hwmon *hw,
			  स्थिर काष्ठा m10bmc_sdata *data,
			  अचिन्हित पूर्णांक regoff, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = m10bmc_sys_पढ़ो(hw->m10bmc, regoff, &regval);
	अगर (ret)
		वापस ret;

	/*
	 * BMC Firmware will वापस 0xdeadbeef अगर the sensor value is invalid
	 * at that समय. This usually happens on sensor channels which connect
	 * to बाह्यal pluggable modules, e.g. QSFP temperature and voltage.
	 * When the QSFP is unplugged from cage, driver will get 0xdeadbeef
	 * from their रेजिस्टरs.
	 */
	अगर (regval == 0xdeadbeef)
		वापस -ENODATA;

	*val = regval * data->multiplier;

	वापस 0;
पूर्ण

अटल पूर्णांक m10bmc_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा m10bmc_hwmon *hw = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg = 0, reg_hyst = 0;
	स्थिर काष्ठा m10bmc_sdata *data;
	दीर्घ hyst, value;
	पूर्णांक ret;

	data = find_sensor_data(hw, type, channel);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			reg = data->reg_input;
			अवरोध;
		हाल hwmon_temp_max_hyst:
			reg_hyst = data->reg_hyst;
			fallthrough;
		हाल hwmon_temp_max:
			reg = data->reg_max;
			अवरोध;
		हाल hwmon_temp_crit_hyst:
			reg_hyst = data->reg_hyst;
			fallthrough;
		हाल hwmon_temp_crit:
			reg = data->reg_crit;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			reg = data->reg_input;
			अवरोध;
		हाल hwmon_in_max:
			reg = data->reg_max;
			अवरोध;
		हाल hwmon_in_crit:
			reg = data->reg_crit;
			अवरोध;
		हाल hwmon_in_min:
			reg = data->reg_min;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
			reg = data->reg_input;
			अवरोध;
		हाल hwmon_curr_max:
			reg = data->reg_max;
			अवरोध;
		हाल hwmon_curr_crit:
			reg = data->reg_crit;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_input:
			reg = data->reg_input;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!reg)
		वापस -EOPNOTSUPP;

	ret = करो_sensor_पढ़ो(hw, data, reg, &value);
	अगर (ret)
		वापस ret;

	अगर (reg_hyst) अणु
		ret = करो_sensor_पढ़ो(hw, data, reg_hyst, &hyst);
		अगर (ret)
			वापस ret;

		value -= hyst;
	पूर्ण

	*val = value;

	वापस 0;
पूर्ण

अटल पूर्णांक m10bmc_hwmon_पढ़ो_string(काष्ठा device *dev,
				    क्रमागत hwmon_sensor_types type,
				    u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	काष्ठा m10bmc_hwmon *hw = dev_get_drvdata(dev);
	स्थिर काष्ठा m10bmc_sdata *data;

	data = find_sensor_data(hw, type, channel);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	*str = data->label;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops m10bmc_hwmon_ops = अणु
	.is_visible = m10bmc_hwmon_is_visible,
	.पढ़ो = m10bmc_hwmon_पढ़ो,
	.पढ़ो_string = m10bmc_hwmon_पढ़ो_string,
पूर्ण;

अटल पूर्णांक m10bmc_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा पूर्णांकel_m10bmc *m10bmc = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *hwmon_dev, *dev = &pdev->dev;
	काष्ठा m10bmc_hwmon *hw;
	पूर्णांक i;

	hw = devm_kzalloc(dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	hw->dev = dev;
	hw->m10bmc = m10bmc;
	hw->bdata = (स्थिर काष्ठा m10bmc_hwmon_board_data *)id->driver_data;

	hw->chip.info = hw->bdata->hinfo;
	hw->chip.ops = &m10bmc_hwmon_ops;

	hw->hw_name = devm_kstrdup(dev, id->name, GFP_KERNEL);
	अगर (!hw->hw_name)
		वापस -ENOMEM;

	क्रम (i = 0; hw->hw_name[i]; i++)
		अगर (hwmon_is_bad_अक्षर(hw->hw_name[i]))
			hw->hw_name[i] = '_';

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, hw->hw_name,
							 hw, &hw->chip, शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id पूर्णांकel_m10bmc_hwmon_ids[] = अणु
	अणु
		.name = "n3000bmc-hwmon",
		.driver_data = (अचिन्हित दीर्घ)&n3000bmc_hwmon_bdata,
	पूर्ण,
	अणु
		.name = "d5005bmc-hwmon",
		.driver_data = (अचिन्हित दीर्घ)&d5005bmc_hwmon_bdata,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_m10bmc_hwmon_driver = अणु
	.probe = m10bmc_hwmon_probe,
	.driver = अणु
		.name = "intel-m10-bmc-hwmon",
	पूर्ण,
	.id_table = पूर्णांकel_m10bmc_hwmon_ids,
पूर्ण;
module_platक्रमm_driver(पूर्णांकel_m10bmc_hwmon_driver);

MODULE_DEVICE_TABLE(platक्रमm, पूर्णांकel_m10bmc_hwmon_ids);
MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel MAX 10 BMC hardware monitor");
MODULE_LICENSE("GPL");
