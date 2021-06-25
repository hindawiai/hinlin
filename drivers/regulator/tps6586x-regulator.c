<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम TI TPS6586x
 *
 * Copyright (C) 2010 Compulab Ltd.
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based on da903x
 * Copyright (C) 2006-2008 Marvell International Ltd.
 * Copyright (C) 2008 Compulab Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/tps6586x.h>

/* supply control and voltage setting  */
#घोषणा TPS6586X_SUPPLYENA	0x10
#घोषणा TPS6586X_SUPPLYENB	0x11
#घोषणा TPS6586X_SUPPLYENC	0x12
#घोषणा TPS6586X_SUPPLYEND	0x13
#घोषणा TPS6586X_SUPPLYENE	0x14
#घोषणा TPS6586X_VCC1		0x20
#घोषणा TPS6586X_VCC2		0x21
#घोषणा TPS6586X_SM1V1		0x23
#घोषणा TPS6586X_SM1V2		0x24
#घोषणा TPS6586X_SM1SL		0x25
#घोषणा TPS6586X_SM0V1		0x26
#घोषणा TPS6586X_SM0V2		0x27
#घोषणा TPS6586X_SM0SL		0x28
#घोषणा TPS6586X_LDO2AV1	0x29
#घोषणा TPS6586X_LDO2AV2	0x2A
#घोषणा TPS6586X_LDO2BV1	0x2F
#घोषणा TPS6586X_LDO2BV2	0x30
#घोषणा TPS6586X_LDO4V1		0x32
#घोषणा TPS6586X_LDO4V2		0x33

/* converter settings  */
#घोषणा TPS6586X_SUPPLYV1	0x41
#घोषणा TPS6586X_SUPPLYV2	0x42
#घोषणा TPS6586X_SUPPLYV3	0x43
#घोषणा TPS6586X_SUPPLYV4	0x44
#घोषणा TPS6586X_SUPPLYV5	0x45
#घोषणा TPS6586X_SUPPLYV6	0x46
#घोषणा TPS6586X_SMODE1		0x47
#घोषणा TPS6586X_SMODE2		0x48

काष्ठा tps6586x_regulator अणु
	काष्ठा regulator_desc desc;

	पूर्णांक enable_bit[2];
	पूर्णांक enable_reg[2];
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps6586x_rw_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps6586x_rw_linear_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps6586x_ro_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps6586x_sys_regulator_ops = अणु
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tps6586x_lकरो0_voltages[] = अणु
	1200000, 1500000, 1800000, 2500000, 2700000, 2850000, 3100000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tps6586x_lकरो_voltages[] = अणु
	1250000, 1500000, 1800000, 2500000, 2700000, 2850000, 3100000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tps658640_rtc_voltages[] = अणु
	2500000, 2850000, 3100000, 3300000,
पूर्ण;

#घोषणा TPS6586X_REGULATOR(_id, _ops, _pin_name, vdata, vreg, shअगरt, nbits, \
			   ereg0, ebit0, ereg1, ebit1, goreg, gobit)	\
	.desc	= अणु							\
		.supply_name = _pin_name,				\
		.name	= "REG-" #_id,					\
		.ops	= &tps6586x_## _ops ## _regulator_ops,		\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= TPS6586X_ID_##_id,				\
		.n_voltages = ARRAY_SIZE(vdata##_voltages),		\
		.volt_table = vdata##_voltages,				\
		.owner	= THIS_MODULE,					\
		.enable_reg = TPS6586X_SUPPLY##ereg0,			\
		.enable_mask = 1 << (ebit0),				\
		.vsel_reg = TPS6586X_##vreg,				\
		.vsel_mask = ((1 << (nbits)) - 1) << (shअगरt),		\
		.apply_reg = (goreg),				\
		.apply_bit = (gobit),				\
	पूर्ण,								\
	.enable_reg[0]	= TPS6586X_SUPPLY##ereg0,			\
	.enable_bit[0]	= (ebit0),					\
	.enable_reg[1]	= TPS6586X_SUPPLY##ereg1,			\
	.enable_bit[1]	= (ebit1),

#घोषणा TPS6586X_REGULATOR_LINEAR(_id, _ops, _pin_name, n_volt, min_uv,	\
				  uv_step, vreg, shअगरt, nbits, ereg0,	\
				  ebit0, ereg1, ebit1, goreg, gobit)	\
	.desc	= अणु							\
		.supply_name = _pin_name,				\
		.name	= "REG-" #_id,					\
		.ops	= &tps6586x_## _ops ## _regulator_ops,		\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= TPS6586X_ID_##_id,				\
		.n_voltages = n_volt,					\
		.min_uV = min_uv,					\
		.uV_step = uv_step,					\
		.owner	= THIS_MODULE,					\
		.enable_reg = TPS6586X_SUPPLY##ereg0,			\
		.enable_mask = 1 << (ebit0),				\
		.vsel_reg = TPS6586X_##vreg,				\
		.vsel_mask = ((1 << (nbits)) - 1) << (shअगरt),		\
		.apply_reg = (goreg),				\
		.apply_bit = (gobit),				\
	पूर्ण,								\
	.enable_reg[0]	= TPS6586X_SUPPLY##ereg0,			\
	.enable_bit[0]	= (ebit0),					\
	.enable_reg[1]	= TPS6586X_SUPPLY##ereg1,			\
	.enable_bit[1]	= (ebit1),

#घोषणा TPS6586X_LDO(_id, _pname, vdata, vreg, shअगरt, nbits,		\
		     ereg0, ebit0, ereg1, ebit1)			\
अणु									\
	TPS6586X_REGULATOR(_id, rw, _pname, vdata, vreg, shअगरt, nbits,	\
			   ereg0, ebit0, ereg1, ebit1, 0, 0)		\
पूर्ण

#घोषणा TPS6586X_LDO_LINEAR(_id, _pname, n_volt, min_uv, uv_step, vreg,	\
			    shअगरt, nbits, ereg0, ebit0, ereg1, ebit1)	\
अणु									\
	TPS6586X_REGULATOR_LINEAR(_id, rw_linear, _pname, n_volt,	\
				  min_uv, uv_step, vreg, shअगरt, nbits,	\
				  ereg0, ebit0, ereg1, ebit1, 0, 0)	\
पूर्ण

#घोषणा TPS6586X_FIXED_LDO(_id, _pname, vdata, vreg, shअगरt, nbits,	\
			  ereg0, ebit0, ereg1, ebit1)			\
अणु									\
	TPS6586X_REGULATOR(_id, ro, _pname, vdata, vreg, shअगरt, nbits,	\
			   ereg0, ebit0, ereg1, ebit1, 0, 0)		\
पूर्ण

#घोषणा TPS6586X_DVM(_id, _pname, n_volt, min_uv, uv_step, vreg, shअगरt,	\
		     nbits, ereg0, ebit0, ereg1, ebit1, goreg, gobit)	\
अणु									\
	TPS6586X_REGULATOR_LINEAR(_id, rw_linear, _pname, n_volt,	\
				  min_uv, uv_step, vreg, shअगरt, nbits,	\
				  ereg0, ebit0, ereg1, ebit1, goreg,	\
				  gobit)				\
पूर्ण

#घोषणा TPS6586X_SYS_REGULATOR()					\
अणु									\
	.desc	= अणु							\
		.supply_name = "sys",					\
		.name	= "REG-SYS",					\
		.ops	= &tps6586x_sys_regulator_ops,			\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= TPS6586X_ID_SYS,				\
		.owner	= THIS_MODULE,					\
	पूर्ण,								\
पूर्ण

अटल काष्ठा tps6586x_regulator tps6586x_regulator[] = अणु
	TPS6586X_SYS_REGULATOR(),
	TPS6586X_LDO(LDO_0, "vinldo01", tps6586x_lकरो0, SUPPLYV1, 5, 3, ENC, 0,
					END, 0),
	TPS6586X_LDO(LDO_3, "vinldo23", tps6586x_lकरो, SUPPLYV4, 0, 3, ENC, 2,
					END, 2),
	TPS6586X_LDO(LDO_5, "REG-SYS", tps6586x_lकरो, SUPPLYV6, 0, 3, ENE, 6,
					ENE, 6),
	TPS6586X_LDO(LDO_6, "vinldo678", tps6586x_lकरो, SUPPLYV3, 0, 3, ENC, 4,
					END, 4),
	TPS6586X_LDO(LDO_7, "vinldo678", tps6586x_lकरो, SUPPLYV3, 3, 3, ENC, 5,
					END, 5),
	TPS6586X_LDO(LDO_8, "vinldo678", tps6586x_lकरो, SUPPLYV2, 5, 3, ENC, 6,
					END, 6),
	TPS6586X_LDO(LDO_9, "vinldo9", tps6586x_lकरो, SUPPLYV6, 3, 3, ENE, 7,
					ENE, 7),
	TPS6586X_LDO(LDO_RTC, "REG-SYS", tps6586x_lकरो, SUPPLYV4, 3, 3, V4, 7,
					V4, 7),
	TPS6586X_LDO_LINEAR(LDO_1, "vinldo01", 32, 725000, 25000, SUPPLYV1,
			    0, 5, ENC, 1, END, 1),
	TPS6586X_LDO_LINEAR(SM_2, "vin-sm2", 32, 3000000, 50000, SUPPLYV2,
			    0, 5, ENC, 7, END, 7),
	TPS6586X_DVM(LDO_2, "vinldo23", 32, 725000, 25000, LDO2BV1, 0, 5,
		     ENA, 3, ENB, 3, TPS6586X_VCC2, BIT(6)),
	TPS6586X_DVM(LDO_4, "vinldo4", 32, 1700000, 25000, LDO4V1, 0, 5,
		     ENC, 3, END, 3, TPS6586X_VCC1, BIT(6)),
	TPS6586X_DVM(SM_0, "vin-sm0", 32, 725000, 25000, SM0V1, 0, 5,
		     ENA, 1, ENB, 1, TPS6586X_VCC1, BIT(2)),
	TPS6586X_DVM(SM_1, "vin-sm1", 32, 725000, 25000, SM1V1, 0, 5,
		     ENA, 0, ENB, 0, TPS6586X_VCC1, BIT(0)),
पूर्ण;

अटल काष्ठा tps6586x_regulator tps658623_regulator[] = अणु
	TPS6586X_LDO_LINEAR(SM_2, "vin-sm2", 32, 1700000, 25000, SUPPLYV2,
			    0, 5, ENC, 7, END, 7),
पूर्ण;

अटल काष्ठा tps6586x_regulator tps658640_regulator[] = अणु
	TPS6586X_LDO(LDO_3, "vinldo23", tps6586x_lकरो0, SUPPLYV4, 0, 3,
					ENC, 2, END, 2),
	TPS6586X_LDO(LDO_5, "REG-SYS", tps6586x_lकरो0, SUPPLYV6, 0, 3,
					ENE, 6, ENE, 6),
	TPS6586X_LDO(LDO_6, "vinldo678", tps6586x_lकरो0, SUPPLYV3, 0, 3,
					ENC, 4, END, 4),
	TPS6586X_LDO(LDO_7, "vinldo678", tps6586x_lकरो0, SUPPLYV3, 3, 3,
					ENC, 5, END, 5),
	TPS6586X_LDO(LDO_8, "vinldo678", tps6586x_lकरो0, SUPPLYV2, 5, 3,
					ENC, 6, END, 6),
	TPS6586X_LDO(LDO_9, "vinldo9", tps6586x_lकरो0, SUPPLYV6, 3, 3,
					ENE, 7, ENE, 7),
	TPS6586X_LDO_LINEAR(SM_2, "vin-sm2", 32, 2150000, 50000, SUPPLYV2,
			    0, 5, ENC, 7, END, 7),

	TPS6586X_FIXED_LDO(LDO_RTC, "REG-SYS", tps658640_rtc, SUPPLYV4, 3, 2,
					V4, 7, V4, 7),
पूर्ण;

अटल काष्ठा tps6586x_regulator tps658643_regulator[] = अणु
	TPS6586X_LDO_LINEAR(SM_2, "vin-sm2", 32, 1025000, 25000, SUPPLYV2,
			    0, 5, ENC, 7, END, 7),
पूर्ण;

/*
 * TPS6586X has 2 enable bits that are OR'ed to determine the actual
 * regulator state. Clearing one of this bits allows चयनing
 * regulator on and of with single रेजिस्टर ग_लिखो.
 */
अटल अंतरभूत पूर्णांक tps6586x_regulator_preinit(काष्ठा device *parent,
					     काष्ठा tps6586x_regulator *ri)
अणु
	uपूर्णांक8_t val1, val2;
	पूर्णांक ret;

	अगर (ri->enable_reg[0] == ri->enable_reg[1] &&
	    ri->enable_bit[0] == ri->enable_bit[1])
			वापस 0;

	ret = tps6586x_पढ़ो(parent, ri->enable_reg[0], &val1);
	अगर (ret)
		वापस ret;

	ret = tps6586x_पढ़ो(parent, ri->enable_reg[1], &val2);
	अगर (ret)
		वापस ret;

	अगर (!(val2 & (1 << ri->enable_bit[1])))
		वापस 0;

	/*
	 * The regulator is on, but it's enabled with the bit we don't
	 * want to use, so we चयन the enable bits
	 */
	अगर (!(val1 & (1 << ri->enable_bit[0]))) अणु
		ret = tps6586x_set_bits(parent, ri->enable_reg[0],
					1 << ri->enable_bit[0]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस tps6586x_clr_bits(parent, ri->enable_reg[1],
				 1 << ri->enable_bit[1]);
पूर्ण

अटल पूर्णांक tps6586x_regulator_set_slew_rate(काष्ठा platक्रमm_device *pdev,
			पूर्णांक id, काष्ठा regulator_init_data *p)
अणु
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा tps6586x_settings *setting = p->driver_data;
	uपूर्णांक8_t reg;

	अगर (setting == शून्य)
		वापस 0;

	अगर (!(setting->slew_rate & TPS6586X_SLEW_RATE_SET))
		वापस 0;

	/* only SM0 and SM1 can have the slew rate settings */
	चयन (id) अणु
	हाल TPS6586X_ID_SM_0:
		reg = TPS6586X_SM0SL;
		अवरोध;
	हाल TPS6586X_ID_SM_1:
		reg = TPS6586X_SM1SL;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Only SM0/SM1 can set slew rate\n");
		वापस -EINVAL;
	पूर्ण

	वापस tps6586x_ग_लिखो(parent, reg,
			setting->slew_rate & TPS6586X_SLEW_RATE_MASK);
पूर्ण

अटल काष्ठा tps6586x_regulator *find_regulator_info(पूर्णांक id, पूर्णांक version)
अणु
	काष्ठा tps6586x_regulator *ri;
	काष्ठा tps6586x_regulator *table = शून्य;
	पूर्णांक num;
	पूर्णांक i;

	चयन (version) अणु
	हाल TPS658623:
	हाल TPS658624:
		table = tps658623_regulator;
		num = ARRAY_SIZE(tps658623_regulator);
		अवरोध;
	हाल TPS658640:
	हाल TPS658640v2:
		table = tps658640_regulator;
		num = ARRAY_SIZE(tps658640_regulator);
		अवरोध;
	हाल TPS658643:
		table = tps658643_regulator;
		num = ARRAY_SIZE(tps658643_regulator);
		अवरोध;
	पूर्ण

	/* Search version specअगरic table first */
	अगर (table) अणु
		क्रम (i = 0; i < num; i++) अणु
			ri = &table[i];
			अगर (ri->desc.id == id)
				वापस ri;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tps6586x_regulator); i++) अणु
		ri = &tps6586x_regulator[i];
		अगर (ri->desc.id == id)
			वापस ri;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा of_regulator_match tps6586x_matches[] = अणु
	अणु .name = "sys",     .driver_data = (व्योम *)TPS6586X_ID_SYS     पूर्ण,
	अणु .name = "sm0",     .driver_data = (व्योम *)TPS6586X_ID_SM_0    पूर्ण,
	अणु .name = "sm1",     .driver_data = (व्योम *)TPS6586X_ID_SM_1    पूर्ण,
	अणु .name = "sm2",     .driver_data = (व्योम *)TPS6586X_ID_SM_2    पूर्ण,
	अणु .name = "ldo0",    .driver_data = (व्योम *)TPS6586X_ID_LDO_0   पूर्ण,
	अणु .name = "ldo1",    .driver_data = (व्योम *)TPS6586X_ID_LDO_1   पूर्ण,
	अणु .name = "ldo2",    .driver_data = (व्योम *)TPS6586X_ID_LDO_2   पूर्ण,
	अणु .name = "ldo3",    .driver_data = (व्योम *)TPS6586X_ID_LDO_3   पूर्ण,
	अणु .name = "ldo4",    .driver_data = (व्योम *)TPS6586X_ID_LDO_4   पूर्ण,
	अणु .name = "ldo5",    .driver_data = (व्योम *)TPS6586X_ID_LDO_5   पूर्ण,
	अणु .name = "ldo6",    .driver_data = (व्योम *)TPS6586X_ID_LDO_6   पूर्ण,
	अणु .name = "ldo7",    .driver_data = (व्योम *)TPS6586X_ID_LDO_7   पूर्ण,
	अणु .name = "ldo8",    .driver_data = (व्योम *)TPS6586X_ID_LDO_8   पूर्ण,
	अणु .name = "ldo9",    .driver_data = (व्योम *)TPS6586X_ID_LDO_9   पूर्ण,
	अणु .name = "ldo_rtc", .driver_data = (व्योम *)TPS6586X_ID_LDO_RTC पूर्ण,
पूर्ण;

अटल काष्ठा tps6586x_platक्रमm_data *tps6586x_parse_regulator_dt(
		काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match **tps6586x_reg_matches)
अणु
	स्थिर अचिन्हित पूर्णांक num = ARRAY_SIZE(tps6586x_matches);
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	काष्ठा device_node *regs;
	स्थिर अक्षर *sys_rail = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा tps6586x_platक्रमm_data *pdata;
	पूर्णांक err;

	regs = of_get_child_by_name(np, "regulators");
	अगर (!regs) अणु
		dev_err(&pdev->dev, "regulator node not found\n");
		वापस शून्य;
	पूर्ण

	err = of_regulator_match(&pdev->dev, regs, tps6586x_matches, num);
	of_node_put(regs);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Regulator match failed, e %d\n", err);
		वापस शून्य;
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	क्रम (i = 0; i < num; i++) अणु
		uपूर्णांकptr_t id;
		अगर (!tps6586x_matches[i].init_data)
			जारी;

		pdata->reg_init_data[i] = tps6586x_matches[i].init_data;
		id = (uपूर्णांकptr_t)tps6586x_matches[i].driver_data;
		अगर (id == TPS6586X_ID_SYS)
			sys_rail = pdata->reg_init_data[i]->स्थिरraपूर्णांकs.name;

		अगर ((id == TPS6586X_ID_LDO_5) || (id == TPS6586X_ID_LDO_RTC))
			pdata->reg_init_data[i]->supply_regulator = sys_rail;
	पूर्ण
	*tps6586x_reg_matches = tps6586x_matches;
	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा tps6586x_platक्रमm_data *tps6586x_parse_regulator_dt(
		काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match **tps6586x_reg_matches)
अणु
	*tps6586x_reg_matches = शून्य;
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps6586x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6586x_regulator *ri = शून्य;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_init_data *reg_data;
	काष्ठा tps6586x_platक्रमm_data *pdata;
	काष्ठा of_regulator_match *tps6586x_reg_matches = शून्य;
	पूर्णांक version;
	पूर्णांक id;
	पूर्णांक err;

	dev_dbg(&pdev->dev, "Probing regulator\n");

	pdata = dev_get_platdata(pdev->dev.parent);
	अगर ((!pdata) && (pdev->dev.parent->of_node))
		pdata = tps6586x_parse_regulator_dt(pdev,
					&tps6586x_reg_matches);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Platform data not available, exiting\n");
		वापस -ENODEV;
	पूर्ण

	version = tps6586x_get_version(pdev->dev.parent);

	क्रम (id = 0; id < TPS6586X_ID_MAX_REGULATOR; ++id) अणु
		reg_data = pdata->reg_init_data[id];

		ri = find_regulator_info(id, version);

		अगर (!ri) अणु
			dev_err(&pdev->dev, "invalid regulator ID specified\n");
			वापस -EINVAL;
		पूर्ण

		err = tps6586x_regulator_preinit(pdev->dev.parent, ri);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"regulator %d preinit failed, e %d\n", id, err);
			वापस err;
		पूर्ण

		config.dev = pdev->dev.parent;
		config.init_data = reg_data;
		config.driver_data = ri;

		अगर (tps6586x_reg_matches)
			config.of_node = tps6586x_reg_matches[id].of_node;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
					ri->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण

		अगर (reg_data) अणु
			err = tps6586x_regulator_set_slew_rate(pdev, id,
					reg_data);
			अगर (err < 0) अणु
				dev_err(&pdev->dev,
					"Slew rate config failed, e %d\n", err);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, rdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps6586x_regulator_driver = अणु
	.driver	= अणु
		.name	= "tps6586x-regulator",
	पूर्ण,
	.probe		= tps6586x_regulator_probe,
पूर्ण;

अटल पूर्णांक __init tps6586x_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps6586x_regulator_driver);
पूर्ण
subsys_initcall(tps6586x_regulator_init);

अटल व्योम __निकास tps6586x_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps6586x_regulator_driver);
पूर्ण
module_निकास(tps6586x_regulator_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("Regulator Driver for TI TPS6586X PMIC");
MODULE_ALIAS("platform:tps6586x-regulator");
