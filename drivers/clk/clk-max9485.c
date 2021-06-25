<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <dt-bindings/घड़ी/maxim,max9485.h>

#घोषणा MAX9485_NUM_CLKS 4

/* This chip has only one रेजिस्टर of 8 bit width. */

#घोषणा MAX9485_FS_12KHZ	(0 << 0)
#घोषणा MAX9485_FS_32KHZ	(1 << 0)
#घोषणा MAX9485_FS_44_1KHZ	(2 << 0)
#घोषणा MAX9485_FS_48KHZ	(3 << 0)

#घोषणा MAX9485_SCALE_256	(0 << 2)
#घोषणा MAX9485_SCALE_384	(1 << 2)
#घोषणा MAX9485_SCALE_768	(2 << 2)

#घोषणा MAX9485_DOUBLE		BIT(4)
#घोषणा MAX9485_CLKOUT1_ENABLE	BIT(5)
#घोषणा MAX9485_CLKOUT2_ENABLE	BIT(6)
#घोषणा MAX9485_MCLK_ENABLE	BIT(7)
#घोषणा MAX9485_FREQ_MASK	0x1f

काष्ठा max9485_rate अणु
	अचिन्हित दीर्घ out;
	u8 reg_value;
पूर्ण;

/*
 * Ordered by frequency. For frequency the hardware can generate with
 * multiple settings, the one with lowest jitter is listed first.
 */
अटल स्थिर काष्ठा max9485_rate max9485_rates[] = अणु
	अणु  3072000, MAX9485_FS_12KHZ   | MAX9485_SCALE_256 पूर्ण,
	अणु  4608000, MAX9485_FS_12KHZ   | MAX9485_SCALE_384 पूर्ण,
	अणु  8192000, MAX9485_FS_32KHZ   | MAX9485_SCALE_256 पूर्ण,
	अणु  9126000, MAX9485_FS_12KHZ   | MAX9485_SCALE_768 पूर्ण,
	अणु 11289600, MAX9485_FS_44_1KHZ | MAX9485_SCALE_256 पूर्ण,
	अणु 12288000, MAX9485_FS_48KHZ   | MAX9485_SCALE_256 पूर्ण,
	अणु 12288000, MAX9485_FS_32KHZ   | MAX9485_SCALE_384 पूर्ण,
	अणु 16384000, MAX9485_FS_32KHZ   | MAX9485_SCALE_256 | MAX9485_DOUBLE पूर्ण,
	अणु 16934400, MAX9485_FS_44_1KHZ | MAX9485_SCALE_384 पूर्ण,
	अणु 18384000, MAX9485_FS_48KHZ   | MAX9485_SCALE_384 पूर्ण,
	अणु 22579200, MAX9485_FS_44_1KHZ | MAX9485_SCALE_256 | MAX9485_DOUBLE पूर्ण,
	अणु 24576000, MAX9485_FS_48KHZ   | MAX9485_SCALE_256 | MAX9485_DOUBLE पूर्ण,
	अणु 24576000, MAX9485_FS_32KHZ   | MAX9485_SCALE_384 | MAX9485_DOUBLE पूर्ण,
	अणु 24576000, MAX9485_FS_32KHZ   | MAX9485_SCALE_768 पूर्ण,
	अणु 33868800, MAX9485_FS_44_1KHZ | MAX9485_SCALE_384 | MAX9485_DOUBLE पूर्ण,
	अणु 33868800, MAX9485_FS_44_1KHZ | MAX9485_SCALE_768 पूर्ण,
	अणु 36864000, MAX9485_FS_48KHZ   | MAX9485_SCALE_384 | MAX9485_DOUBLE पूर्ण,
	अणु 36864000, MAX9485_FS_48KHZ   | MAX9485_SCALE_768 पूर्ण,
	अणु 49152000, MAX9485_FS_32KHZ   | MAX9485_SCALE_768 | MAX9485_DOUBLE पूर्ण,
	अणु 67737600, MAX9485_FS_44_1KHZ | MAX9485_SCALE_768 | MAX9485_DOUBLE पूर्ण,
	अणु 73728000, MAX9485_FS_48KHZ   | MAX9485_SCALE_768 | MAX9485_DOUBLE पूर्ण,
	अणु पूर्ण /* sentinel */
पूर्ण;

काष्ठा max9485_driver_data;

काष्ठा max9485_clk_hw अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_init_data init;
	u8 enable_bit;
	काष्ठा max9485_driver_data *drvdata;
पूर्ण;

काष्ठा max9485_driver_data अणु
	काष्ठा clk *xclk;
	काष्ठा i2c_client *client;
	u8 reg_value;
	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा max9485_clk_hw hw[MAX9485_NUM_CLKS];
पूर्ण;

अटल अंतरभूत काष्ठा max9485_clk_hw *to_max9485_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा max9485_clk_hw, hw);
पूर्ण

अटल पूर्णांक max9485_update_bits(काष्ठा max9485_driver_data *drvdata,
			       u8 mask, u8 value)
अणु
	पूर्णांक ret;

	drvdata->reg_value &= ~mask;
	drvdata->reg_value |= value;

	dev_dbg(&drvdata->client->dev,
		"updating mask 0x%02x value 0x%02x -> 0x%02x\n",
		mask, value, drvdata->reg_value);

	ret = i2c_master_send(drvdata->client,
			      &drvdata->reg_value,
			      माप(drvdata->reg_value));

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक max9485_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा max9485_clk_hw *clk_hw = to_max9485_clk(hw);

	वापस max9485_update_bits(clk_hw->drvdata,
				   clk_hw->enable_bit,
				   clk_hw->enable_bit);
पूर्ण

अटल व्योम max9485_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा max9485_clk_hw *clk_hw = to_max9485_clk(hw);

	max9485_update_bits(clk_hw->drvdata, clk_hw->enable_bit, 0);
पूर्ण

/*
 * CLKOUT - configurable घड़ी output
 */
अटल पूर्णांक max9485_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा max9485_clk_hw *clk_hw = to_max9485_clk(hw);
	स्थिर काष्ठा max9485_rate *entry;

	क्रम (entry = max9485_rates; entry->out != 0; entry++)
		अगर (entry->out == rate)
			अवरोध;

	अगर (entry->out == 0)
		वापस -EINVAL;

	वापस max9485_update_bits(clk_hw->drvdata,
				   MAX9485_FREQ_MASK,
				   entry->reg_value);
पूर्ण

अटल अचिन्हित दीर्घ max9485_clkout_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा max9485_clk_hw *clk_hw = to_max9485_clk(hw);
	काष्ठा max9485_driver_data *drvdata = clk_hw->drvdata;
	u8 val = drvdata->reg_value & MAX9485_FREQ_MASK;
	स्थिर काष्ठा max9485_rate *entry;

	क्रम (entry = max9485_rates; entry->out != 0; entry++)
		अगर (val == entry->reg_value)
			वापस entry->out;

	वापस 0;
पूर्ण

अटल दीर्घ max9485_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा max9485_rate *curr, *prev = शून्य;

	क्रम (curr = max9485_rates; curr->out != 0; curr++) अणु
		/* Exact matches */
		अगर (curr->out == rate)
			वापस rate;

		/*
		 * Find the first entry that has a frequency higher than the
		 * requested one.
		 */
		अगर (curr->out > rate) अणु
			अचिन्हित पूर्णांक mid;

			/*
			 * If this is the first entry, clamp the value to the
			 * lowest possible frequency.
			 */
			अगर (!prev)
				वापस curr->out;

			/*
			 * Otherwise, determine whether the previous entry or
			 * current one is बंदr.
			 */
			mid = prev->out + ((curr->out - prev->out) / 2);

			वापस (mid > rate) ? prev->out : curr->out;
		पूर्ण

		prev = curr;
	पूर्ण

	/* If the last entry was still too high, clamp the value */
	वापस prev->out;
पूर्ण

काष्ठा max9485_clk अणु
	स्थिर अक्षर *name;
	पूर्णांक parent_index;
	स्थिर काष्ठा clk_ops ops;
	u8 enable_bit;
पूर्ण;

अटल स्थिर काष्ठा max9485_clk max9485_clks[MAX9485_NUM_CLKS] = अणु
	[MAX9485_MCLKOUT] = अणु
		.name = "mclkout",
		.parent_index = -1,
		.enable_bit = MAX9485_MCLK_ENABLE,
		.ops = अणु
			.prepare	= max9485_clk_prepare,
			.unprepare	= max9485_clk_unprepare,
		पूर्ण,
	पूर्ण,
	[MAX9485_CLKOUT] = अणु
		.name = "clkout",
		.parent_index = -1,
		.ops = अणु
			.set_rate	= max9485_clkout_set_rate,
			.round_rate	= max9485_clkout_round_rate,
			.recalc_rate	= max9485_clkout_recalc_rate,
		पूर्ण,
	पूर्ण,
	[MAX9485_CLKOUT1] = अणु
		.name = "clkout1",
		.parent_index = MAX9485_CLKOUT,
		.enable_bit = MAX9485_CLKOUT1_ENABLE,
		.ops = अणु
			.prepare	= max9485_clk_prepare,
			.unprepare	= max9485_clk_unprepare,
		पूर्ण,
	पूर्ण,
	[MAX9485_CLKOUT2] = अणु
		.name = "clkout2",
		.parent_index = MAX9485_CLKOUT,
		.enable_bit = MAX9485_CLKOUT2_ENABLE,
		.ops = अणु
			.prepare	= max9485_clk_prepare,
			.unprepare	= max9485_clk_unprepare,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *
max9485_of_clk_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा max9485_driver_data *drvdata = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	वापस &drvdata->hw[idx].hw;
पूर्ण

अटल पूर्णांक max9485_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max9485_driver_data *drvdata;
	काष्ठा device *dev = &client->dev;
	स्थिर अक्षर *xclk_name;
	पूर्णांक i, ret;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(drvdata->xclk))
		वापस PTR_ERR(drvdata->xclk);

	xclk_name = __clk_get_name(drvdata->xclk);

	drvdata->supply = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(drvdata->supply))
		वापस PTR_ERR(drvdata->supply);

	ret = regulator_enable(drvdata->supply);
	अगर (ret < 0)
		वापस ret;

	drvdata->reset_gpio =
		devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(drvdata->reset_gpio))
		वापस PTR_ERR(drvdata->reset_gpio);

	i2c_set_clientdata(client, drvdata);
	drvdata->client = client;

	ret = i2c_master_recv(drvdata->client, &drvdata->reg_value,
			      माप(drvdata->reg_value));
	अगर (ret < 0) अणु
		dev_warn(dev, "Unable to read device register: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < MAX9485_NUM_CLKS; i++) अणु
		पूर्णांक parent_index = max9485_clks[i].parent_index;
		स्थिर अक्षर *name;

		अगर (of_property_पढ़ो_string_index(dev->of_node,
						  "clock-output-names",
						  i, &name) == 0) अणु
			drvdata->hw[i].init.name = name;
		पूर्ण अन्यथा अणु
			drvdata->hw[i].init.name = max9485_clks[i].name;
		पूर्ण

		drvdata->hw[i].init.ops = &max9485_clks[i].ops;
		drvdata->hw[i].init.num_parents = 1;
		drvdata->hw[i].init.flags = 0;

		अगर (parent_index > 0) अणु
			drvdata->hw[i].init.parent_names =
				&drvdata->hw[parent_index].init.name;
			drvdata->hw[i].init.flags |= CLK_SET_RATE_PARENT;
		पूर्ण अन्यथा अणु
			drvdata->hw[i].init.parent_names = &xclk_name;
		पूर्ण

		drvdata->hw[i].enable_bit = max9485_clks[i].enable_bit;
		drvdata->hw[i].hw.init = &drvdata->hw[i].init;
		drvdata->hw[i].drvdata = drvdata;

		ret = devm_clk_hw_रेजिस्टर(dev, &drvdata->hw[i].hw);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, max9485_of_clk_get, drvdata);
पूर्ण

अटल पूर्णांक __maybe_unused max9485_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max9485_driver_data *drvdata = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(drvdata->reset_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max9485_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max9485_driver_data *drvdata = i2c_get_clientdata(client);
	पूर्णांक ret;

	gpiod_set_value_cansleep(drvdata->reset_gpio, 1);

	ret = i2c_master_send(client, &drvdata->reg_value,
			      माप(drvdata->reg_value));

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops max9485_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max9485_suspend, max9485_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id max9485_dt_ids[] = अणु
	अणु .compatible = "maxim,max9485", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max9485_dt_ids);

अटल स्थिर काष्ठा i2c_device_id max9485_i2c_ids[] = अणु
	अणु .name = "max9485", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max9485_i2c_ids);

अटल काष्ठा i2c_driver max9485_driver = अणु
	.driver = अणु
		.name		= "max9485",
		.pm		= &max9485_pm_ops,
		.of_match_table	= max9485_dt_ids,
	पूर्ण,
	.probe = max9485_i2c_probe,
	.id_table = max9485_i2c_ids,
पूर्ण;
module_i2c_driver(max9485_driver);

MODULE_AUTHOR("Daniel Mack <daniel@zonque.org>");
MODULE_DESCRIPTION("MAX9485 Programmable Audio Clock Generator");
MODULE_LICENSE("GPL v2");
