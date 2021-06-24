<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 MaxLinear, Inc.
 *
 * This driver is a hardware monitoring driver क्रम PVT controller
 * (MR75203) which is used to configure & control Moortec embedded
 * analog IP to enable multiple embedded temperature sensor(TS),
 * voltage monitor(VM) & process detector(PD) modules.
 */
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

/* PVT Common रेजिस्टर */
#घोषणा PVT_IP_CONFIG	0x04
#घोषणा TS_NUM_MSK	GENMASK(4, 0)
#घोषणा TS_NUM_SFT	0
#घोषणा PD_NUM_MSK	GENMASK(12, 8)
#घोषणा PD_NUM_SFT	8
#घोषणा VM_NUM_MSK	GENMASK(20, 16)
#घोषणा VM_NUM_SFT	16
#घोषणा CH_NUM_MSK	GENMASK(31, 24)
#घोषणा CH_NUM_SFT	24

/* Macro Common Register */
#घोषणा CLK_SYNTH		0x00
#घोषणा CLK_SYNTH_LO_SFT	0
#घोषणा CLK_SYNTH_HI_SFT	8
#घोषणा CLK_SYNTH_HOLD_SFT	16
#घोषणा CLK_SYNTH_EN		BIT(24)
#घोषणा CLK_SYS_CYCLES_MAX	514
#घोषणा CLK_SYS_CYCLES_MIN	2
#घोषणा HZ_PER_MHZ		1000000L

#घोषणा SDIF_DISABLE	0x04

#घोषणा SDIF_STAT	0x08
#घोषणा SDIF_BUSY	BIT(0)
#घोषणा SDIF_LOCK	BIT(1)

#घोषणा SDIF_W		0x0c
#घोषणा SDIF_PROG	BIT(31)
#घोषणा SDIF_WRN_W	BIT(27)
#घोषणा SDIF_WRN_R	0x00
#घोषणा SDIF_ADDR_SFT	24

#घोषणा SDIF_HALT	0x10
#घोषणा SDIF_CTRL	0x14
#घोषणा SDIF_SMPL_CTRL	0x20

/* TS & PD Inभागidual Macro Register */
#घोषणा COM_REG_SIZE	0x40

#घोषणा SDIF_DONE(n)	(COM_REG_SIZE + 0x14 + 0x40 * (n))
#घोषणा SDIF_SMPL_DONE	BIT(0)

#घोषणा SDIF_DATA(n)	(COM_REG_SIZE + 0x18 + 0x40 * (n))
#घोषणा SAMPLE_DATA_MSK	GENMASK(15, 0)

#घोषणा HILO_RESET(n)	(COM_REG_SIZE + 0x2c + 0x40 * (n))

/* VM Inभागidual Macro Register */
#घोषणा VM_COM_REG_SIZE	0x200
#घोषणा VM_SDIF_DONE(n)	(VM_COM_REG_SIZE + 0x34 + 0x200 * (n))
#घोषणा VM_SDIF_DATA(n)	(VM_COM_REG_SIZE + 0x40 + 0x200 * (n))

/* SDA Slave Register */
#घोषणा IP_CTRL			0x00
#घोषणा IP_RST_REL		BIT(1)
#घोषणा IP_RUN_CONT		BIT(3)
#घोषणा IP_AUTO			BIT(8)
#घोषणा IP_VM_MODE		BIT(10)

#घोषणा IP_CFG			0x01
#घोषणा CFG0_MODE_2		BIT(0)
#घोषणा CFG0_PARALLEL_OUT	0
#घोषणा CFG0_12_BIT		0
#घोषणा CFG1_VOL_MEAS_MODE	0
#घोषणा CFG1_PARALLEL_OUT	0
#घोषणा CFG1_14_BIT		0

#घोषणा IP_DATA		0x03

#घोषणा IP_POLL		0x04
#घोषणा VM_CH_INIT	BIT(20)
#घोषणा VM_CH_REQ	BIT(21)

#घोषणा IP_TMR			0x05
#घोषणा POWER_DELAY_CYCLE_256	0x80
#घोषणा POWER_DELAY_CYCLE_64	0x40

#घोषणा PVT_POLL_DELAY_US	20
#घोषणा PVT_POLL_TIMEOUT_US	20000
#घोषणा PVT_H_CONST		100000
#घोषणा PVT_CAL5_CONST		2047
#घोषणा PVT_G_CONST		40000
#घोषणा PVT_CONV_BITS		10
#घोषणा PVT_N_CONST		90
#घोषणा PVT_R_CONST		245805

काष्ठा pvt_device अणु
	काष्ठा regmap		*c_map;
	काष्ठा regmap		*t_map;
	काष्ठा regmap		*p_map;
	काष्ठा regmap		*v_map;
	काष्ठा clk		*clk;
	काष्ठा reset_control	*rst;
	u32			t_num;
	u32			p_num;
	u32			v_num;
	u32			ip_freq;
	u8			*vm_idx;
पूर्ण;

अटल umode_t pvt_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		अगर (attr == hwmon_temp_input)
			वापस 0444;
		अवरोध;
	हाल hwmon_in:
		अगर (attr == hwmon_in_input)
			वापस 0444;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा pvt_device *pvt = dev_get_drvdata(dev);
	काष्ठा regmap *t_map = pvt->t_map;
	u32 stat, nbs;
	पूर्णांक ret;
	u64 पंचांगp;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		ret = regmap_पढ़ो_poll_समयout(t_map, SDIF_DONE(channel),
					       stat, stat & SDIF_SMPL_DONE,
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		ret = regmap_पढ़ो(t_map, SDIF_DATA(channel), &nbs);
		अगर(ret < 0)
			वापस ret;

		nbs &= SAMPLE_DATA_MSK;

		/*
		 * Convert the रेजिस्टर value to
		 * degrees centigrade temperature
		 */
		पंचांगp = nbs * PVT_H_CONST;
		करो_भाग(पंचांगp, PVT_CAL5_CONST);
		*val = पंचांगp - PVT_G_CONST - pvt->ip_freq;

		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक pvt_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा pvt_device *pvt = dev_get_drvdata(dev);
	काष्ठा regmap *v_map = pvt->v_map;
	u32 n, stat;
	u8 vm_idx;
	पूर्णांक ret;

	अगर (channel >= pvt->v_num)
		वापस -EINVAL;

	vm_idx = pvt->vm_idx[channel];

	चयन (attr) अणु
	हाल hwmon_in_input:
		ret = regmap_पढ़ो_poll_समयout(v_map, VM_SDIF_DONE(vm_idx),
					       stat, stat & SDIF_SMPL_DONE,
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		ret = regmap_पढ़ो(v_map, VM_SDIF_DATA(vm_idx), &n);
		अगर(ret < 0)
			वापस ret;

		n &= SAMPLE_DATA_MSK;
		/* Convert the N bitstream count पूर्णांकo voltage */
		*val = (PVT_N_CONST * n - PVT_R_CONST) >> PVT_CONV_BITS;

		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक pvt_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस pvt_पढ़ो_temp(dev, attr, channel, val);
	हाल hwmon_in:
		वापस pvt_पढ़ो_in(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर u32 pvt_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info pvt_chip = अणु
	.type = hwmon_chip,
	.config = pvt_chip_config,
पूर्ण;

अटल काष्ठा hwmon_channel_info pvt_temp = अणु
	.type = hwmon_temp,
पूर्ण;

अटल काष्ठा hwmon_channel_info pvt_in = अणु
	.type = hwmon_in,
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops pvt_hwmon_ops = अणु
	.is_visible = pvt_is_visible,
	.पढ़ो = pvt_पढ़ो,
पूर्ण;

अटल काष्ठा hwmon_chip_info pvt_chip_info = अणु
	.ops = &pvt_hwmon_ops,
पूर्ण;

अटल पूर्णांक pvt_init(काष्ठा pvt_device *pvt)
अणु
	u16 sys_freq, key, middle, low = 4, high = 8;
	काष्ठा regmap *t_map = pvt->t_map;
	काष्ठा regmap *p_map = pvt->p_map;
	काष्ठा regmap *v_map = pvt->v_map;
	u32 t_num = pvt->t_num;
	u32 p_num = pvt->p_num;
	u32 v_num = pvt->v_num;
	u32 clk_synth, val;
	पूर्णांक ret;

	sys_freq = clk_get_rate(pvt->clk) / HZ_PER_MHZ;
	जबतक (high >= low) अणु
		middle = (low + high + 1) / 2;
		key = DIV_ROUND_CLOSEST(sys_freq, middle);
		अगर (key > CLK_SYS_CYCLES_MAX) अणु
			low = middle + 1;
			जारी;
		पूर्ण अन्यथा अगर (key < CLK_SYS_CYCLES_MIN) अणु
			high = middle - 1;
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The प्रणाली supports 'clk_sys' to 'clk_ip' frequency ratios
	 * from 2:1 to 512:1
	 */
	key = clamp_val(key, CLK_SYS_CYCLES_MIN, CLK_SYS_CYCLES_MAX) - 2;

	clk_synth = ((key + 1) >> 1) << CLK_SYNTH_LO_SFT |
		    (key >> 1) << CLK_SYNTH_HI_SFT |
		    (key >> 1) << CLK_SYNTH_HOLD_SFT | CLK_SYNTH_EN;

	pvt->ip_freq = sys_freq * 100 / (key + 2);

	अगर (t_num) अणु
		ret = regmap_ग_लिखो(t_map, SDIF_SMPL_CTRL, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(t_map, SDIF_HALT, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(t_map, CLK_SYNTH, clk_synth);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(t_map, SDIF_DISABLE, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(t_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = CFG0_MODE_2 | CFG0_PARALLEL_OUT | CFG0_12_BIT |
		      IP_CFG << SDIF_ADDR_SFT | SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(t_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(t_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = POWER_DELAY_CYCLE_256 | IP_TMR << SDIF_ADDR_SFT |
			      SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(t_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(t_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = IP_RST_REL | IP_RUN_CONT | IP_AUTO |
		      IP_CTRL << SDIF_ADDR_SFT |
		      SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(t_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;
	पूर्ण

	अगर (p_num) अणु
		ret = regmap_ग_लिखो(p_map, SDIF_HALT, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(p_map, SDIF_DISABLE, BIT(p_num) - 1);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(p_map, CLK_SYNTH, clk_synth);
		अगर(ret < 0)
			वापस ret;
	पूर्ण

	अगर (v_num) अणु
		ret = regmap_ग_लिखो(v_map, SDIF_SMPL_CTRL, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(v_map, SDIF_HALT, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(v_map, CLK_SYNTH, clk_synth);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(v_map, SDIF_DISABLE, 0x0);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(v_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = CFG1_VOL_MEAS_MODE | CFG1_PARALLEL_OUT |
		      CFG1_14_BIT | IP_CFG << SDIF_ADDR_SFT |
		      SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(v_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(v_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = POWER_DELAY_CYCLE_64 | IP_TMR << SDIF_ADDR_SFT |
		      SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(v_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(v_map, SDIF_STAT,
					       val, !(val & SDIF_BUSY),
					       PVT_POLL_DELAY_US,
					       PVT_POLL_TIMEOUT_US);
		अगर (ret)
			वापस ret;

		val = IP_RST_REL | IP_RUN_CONT | IP_AUTO | IP_VM_MODE |
		      IP_CTRL << SDIF_ADDR_SFT |
		      SDIF_WRN_W | SDIF_PROG;
		ret = regmap_ग_लिखो(v_map, SDIF_W, val);
		अगर(ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा regmap_config pvt_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
पूर्ण;

अटल पूर्णांक pvt_get_regmap(काष्ठा platक्रमm_device *pdev, अक्षर *reg_name,
			  काष्ठा pvt_device *pvt)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap **reg_map;
	व्योम __iomem *io_base;

	अगर (!म_भेद(reg_name, "common"))
		reg_map = &pvt->c_map;
	अन्यथा अगर (!म_भेद(reg_name, "ts"))
		reg_map = &pvt->t_map;
	अन्यथा अगर (!म_भेद(reg_name, "pd"))
		reg_map = &pvt->p_map;
	अन्यथा अगर (!म_भेद(reg_name, "vm"))
		reg_map = &pvt->v_map;
	अन्यथा
		वापस -EINVAL;

	io_base = devm_platक्रमm_ioremap_resource_byname(pdev, reg_name);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	pvt_regmap_config.name = reg_name;
	*reg_map = devm_regmap_init_mmio(dev, io_base, &pvt_regmap_config);
	अगर (IS_ERR(*reg_map)) अणु
		dev_err(dev, "failed to init register map\n");
		वापस PTR_ERR(*reg_map);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pvt_clk_disable(व्योम *data)
अणु
	काष्ठा pvt_device *pvt = data;

	clk_disable_unprepare(pvt->clk);
पूर्ण

अटल पूर्णांक pvt_clk_enable(काष्ठा device *dev, काष्ठा pvt_device *pvt)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(pvt->clk);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, pvt_clk_disable, pvt);
पूर्ण

अटल व्योम pvt_reset_control_निश्चित(व्योम *data)
अणु
	काष्ठा pvt_device *pvt = data;

	reset_control_निश्चित(pvt->rst);
पूर्ण

अटल पूर्णांक pvt_reset_control_deनिश्चित(काष्ठा device *dev, काष्ठा pvt_device *pvt)
अणु
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(pvt->rst);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, pvt_reset_control_निश्चित, pvt);
पूर्ण

अटल पूर्णांक mr75203_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा hwmon_channel_info **pvt_info;
	u32 ts_num, vm_num, pd_num, val, index, i;
	काष्ठा device *dev = &pdev->dev;
	u32 *temp_config, *in_config;
	काष्ठा device *hwmon_dev;
	काष्ठा pvt_device *pvt;
	पूर्णांक ret;

	pvt = devm_kzalloc(dev, माप(*pvt), GFP_KERNEL);
	अगर (!pvt)
		वापस -ENOMEM;

	ret = pvt_get_regmap(pdev, "common", pvt);
	अगर (ret)
		वापस ret;

	pvt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pvt->clk))
		वापस dev_err_probe(dev, PTR_ERR(pvt->clk), "failed to get clock\n");

	ret = pvt_clk_enable(dev, pvt);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	pvt->rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(pvt->rst))
		वापस dev_err_probe(dev, PTR_ERR(pvt->rst),
				     "failed to get reset control\n");

	ret = pvt_reset_control_deनिश्चित(dev, pvt);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "cannot deassert reset control\n");

	ret = regmap_पढ़ो(pvt->c_map, PVT_IP_CONFIG, &val);
	अगर(ret < 0)
		वापस ret;

	ts_num = (val & TS_NUM_MSK) >> TS_NUM_SFT;
	pd_num = (val & PD_NUM_MSK) >> PD_NUM_SFT;
	vm_num = (val & VM_NUM_MSK) >> VM_NUM_SFT;
	pvt->t_num = ts_num;
	pvt->p_num = pd_num;
	pvt->v_num = vm_num;
	val = 0;
	अगर (ts_num)
		val++;
	अगर (vm_num)
		val++;
	अगर (!val)
		वापस -ENODEV;

	pvt_info = devm_kसुस्मृति(dev, val + 2, माप(*pvt_info), GFP_KERNEL);
	अगर (!pvt_info)
		वापस -ENOMEM;
	pvt_info[0] = &pvt_chip;
	index = 1;

	अगर (ts_num) अणु
		ret = pvt_get_regmap(pdev, "ts", pvt);
		अगर (ret)
			वापस ret;

		temp_config = devm_kसुस्मृति(dev, ts_num + 1,
					   माप(*temp_config), GFP_KERNEL);
		अगर (!temp_config)
			वापस -ENOMEM;

		स_रखो32(temp_config, HWMON_T_INPUT, ts_num);
		pvt_temp.config = temp_config;
		pvt_info[index++] = &pvt_temp;
	पूर्ण

	अगर (pd_num) अणु
		ret = pvt_get_regmap(pdev, "pd", pvt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (vm_num) अणु
		u32 num = vm_num;

		ret = pvt_get_regmap(pdev, "vm", pvt);
		अगर (ret)
			वापस ret;

		pvt->vm_idx = devm_kसुस्मृति(dev, vm_num, माप(*pvt->vm_idx),
					   GFP_KERNEL);
		अगर (!pvt->vm_idx)
			वापस -ENOMEM;

		ret = device_property_पढ़ो_u8_array(dev, "intel,vm-map",
						    pvt->vm_idx, vm_num);
		अगर (ret) अणु
			num = 0;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < vm_num; i++)
				अगर (pvt->vm_idx[i] >= vm_num ||
				    pvt->vm_idx[i] == 0xff) अणु
					num = i;
					अवरोध;
				पूर्ण
		पूर्ण

		/*
		 * Inहाल पूर्णांकel,vm-map property is not defined, we assume
		 * incremental channel numbers.
		 */
		क्रम (i = num; i < vm_num; i++)
			pvt->vm_idx[i] = i;

		in_config = devm_kसुस्मृति(dev, num + 1,
					 माप(*in_config), GFP_KERNEL);
		अगर (!in_config)
			वापस -ENOMEM;

		स_रखो32(in_config, HWMON_I_INPUT, num);
		in_config[num] = 0;
		pvt_in.config = in_config;

		pvt_info[index++] = &pvt_in;
	पूर्ण

	ret = pvt_init(pvt);
	अगर (ret) अणु
		dev_err(dev, "failed to init pvt: %d\n", ret);
		वापस ret;
	पूर्ण

	pvt_chip_info.info = pvt_info;
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, "pvt",
							 pvt,
							 &pvt_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id moortec_pvt_of_match[] = अणु
	अणु .compatible = "moortec,mr75203" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, moortec_pvt_of_match);

अटल काष्ठा platक्रमm_driver moortec_pvt_driver = अणु
	.driver = अणु
		.name = "moortec-pvt",
		.of_match_table = moortec_pvt_of_match,
	पूर्ण,
	.probe = mr75203_probe,
पूर्ण;
module_platक्रमm_driver(moortec_pvt_driver);

MODULE_LICENSE("GPL v2");
