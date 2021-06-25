<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Intel Corporation.
 * Lei Chuanhua <Chuanhua.lei@पूर्णांकel.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#घोषणा RCU_RST_STAT	0x0024
#घोषणा RCU_RST_REQ	0x0048

#घोषणा REG_OFFSET_MASK	GENMASK(31, 16)
#घोषणा BIT_OFFSET_MASK	GENMASK(15, 8)
#घोषणा STAT_BIT_OFFSET_MASK	GENMASK(7, 0)

#घोषणा to_reset_data(x)	container_of(x, काष्ठा पूर्णांकel_reset_data, rcdev)

काष्ठा पूर्णांकel_reset_soc अणु
	bool legacy;
	u32 reset_cell_count;
पूर्ण;

काष्ठा पूर्णांकel_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा notअगरier_block restart_nb;
	स्थिर काष्ठा पूर्णांकel_reset_soc *soc_data;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	u32 reboot_id;
पूर्ण;

अटल स्थिर काष्ठा regmap_config पूर्णांकel_rcu_regmap_config = अणु
	.name =		"intel-reset",
	.reg_bits =	32,
	.reg_stride =	4,
	.val_bits =	32,
	.fast_io =	true,
पूर्ण;

/*
 * Reset status रेजिस्टर offset relative to
 * the reset control रेजिस्टर(X) is X + 4
 */
अटल u32 id_to_reg_and_bit_offsets(काष्ठा पूर्णांकel_reset_data *data,
				     अचिन्हित दीर्घ id, u32 *rst_req,
				     u32 *req_bit, u32 *stat_bit)
अणु
	*rst_req = FIELD_GET(REG_OFFSET_MASK, id);
	*req_bit = FIELD_GET(BIT_OFFSET_MASK, id);

	अगर (data->soc_data->legacy)
		*stat_bit = FIELD_GET(STAT_BIT_OFFSET_MASK, id);
	अन्यथा
		*stat_bit = *req_bit;

	अगर (data->soc_data->legacy && *rst_req == RCU_RST_REQ)
		वापस RCU_RST_STAT;
	अन्यथा
		वापस *rst_req + 0x4;
पूर्ण

अटल पूर्णांक पूर्णांकel_set_clr_bits(काष्ठा पूर्णांकel_reset_data *data, अचिन्हित दीर्घ id,
			      bool set)
अणु
	u32 rst_req, req_bit, rst_stat, stat_bit, val;
	पूर्णांक ret;

	rst_stat = id_to_reg_and_bit_offsets(data, id, &rst_req,
					     &req_bit, &stat_bit);

	val = set ? BIT(req_bit) : 0;
	ret = regmap_update_bits(data->regmap, rst_req,  BIT(req_bit), val);
	अगर (ret)
		वापस ret;

	वापस regmap_पढ़ो_poll_समयout(data->regmap, rst_stat, val,
					set == !!(val & BIT(stat_bit)), 20,
					200);
पूर्ण

अटल पूर्णांक पूर्णांकel_निश्चित_device(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा पूर्णांकel_reset_data *data = to_reset_data(rcdev);
	पूर्णांक ret;

	ret = पूर्णांकel_set_clr_bits(data, id, true);
	अगर (ret)
		dev_err(data->dev, "Reset assert failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_deनिश्चित_device(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा पूर्णांकel_reset_data *data = to_reset_data(rcdev);
	पूर्णांक ret;

	ret = पूर्णांकel_set_clr_bits(data, id, false);
	अगर (ret)
		dev_err(data->dev, "Reset deassert failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_reset_status(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा पूर्णांकel_reset_data *data = to_reset_data(rcdev);
	u32 rst_req, req_bit, rst_stat, stat_bit, val;
	पूर्णांक ret;

	rst_stat = id_to_reg_and_bit_offsets(data, id, &rst_req,
					     &req_bit, &stat_bit);
	ret = regmap_पढ़ो(data->regmap, rst_stat, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(stat_bit));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops पूर्णांकel_reset_ops = अणु
	.निश्चित =	पूर्णांकel_निश्चित_device,
	.deनिश्चित =	पूर्णांकel_deनिश्चित_device,
	.status	=	पूर्णांकel_reset_status,
पूर्ण;

अटल पूर्णांक पूर्णांकel_reset_xlate(काष्ठा reset_controller_dev *rcdev,
			     स्थिर काष्ठा of_phandle_args *spec)
अणु
	काष्ठा पूर्णांकel_reset_data *data = to_reset_data(rcdev);
	u32 id;

	अगर (spec->args[1] > 31)
		वापस -EINVAL;

	id = FIELD_PREP(REG_OFFSET_MASK, spec->args[0]);
	id |= FIELD_PREP(BIT_OFFSET_MASK, spec->args[1]);

	अगर (data->soc_data->legacy) अणु
		अगर (spec->args[2] > 31)
			वापस -EINVAL;

		id |= FIELD_PREP(STAT_BIT_OFFSET_MASK, spec->args[2]);
	पूर्ण

	वापस id;
पूर्ण

अटल पूर्णांक पूर्णांकel_reset_restart_handler(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा पूर्णांकel_reset_data *reset_data;

	reset_data = container_of(nb, काष्ठा पूर्णांकel_reset_data, restart_nb);
	पूर्णांकel_निश्चित_device(&reset_data->rcdev, reset_data->reboot_id);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक पूर्णांकel_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_reset_data *data;
	व्योम __iomem *base;
	u32 rb_id[3];
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->soc_data = of_device_get_match_data(dev);
	अगर (!data->soc_data)
		वापस -ENODEV;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	data->regmap = devm_regmap_init_mmio(dev, base,
					     &पूर्णांकel_rcu_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "regmap initialization failed\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	ret = device_property_पढ़ो_u32_array(dev, "intel,global-reset", rb_id,
					     data->soc_data->reset_cell_count);
	अगर (ret) अणु
		dev_err(dev, "Failed to get global reset offset!\n");
		वापस ret;
	पूर्ण

	data->dev =			dev;
	data->rcdev.of_node =		np;
	data->rcdev.owner =		dev->driver->owner;
	data->rcdev.ops	=		&पूर्णांकel_reset_ops;
	data->rcdev.of_xlate =		पूर्णांकel_reset_xlate;
	data->rcdev.of_reset_n_cells =	data->soc_data->reset_cell_count;
	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &data->rcdev);
	अगर (ret)
		वापस ret;

	data->reboot_id = FIELD_PREP(REG_OFFSET_MASK, rb_id[0]);
	data->reboot_id |= FIELD_PREP(BIT_OFFSET_MASK, rb_id[1]);

	अगर (data->soc_data->legacy)
		data->reboot_id |= FIELD_PREP(STAT_BIT_OFFSET_MASK, rb_id[2]);

	data->restart_nb.notअगरier_call =	पूर्णांकel_reset_restart_handler;
	data->restart_nb.priority =		128;
	रेजिस्टर_restart_handler(&data->restart_nb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_reset_soc xrx200_data = अणु
	.legacy =		true,
	.reset_cell_count =	3,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_reset_soc lgm_data = अणु
	.legacy =		false,
	.reset_cell_count =	2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पूर्णांकel_reset_match[] = अणु
	अणु .compatible = "intel,rcu-lgm", .data = &lgm_data पूर्ण,
	अणु .compatible = "intel,rcu-xrx200", .data = &xrx200_data पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_reset_driver = अणु
	.probe = पूर्णांकel_reset_probe,
	.driver = अणु
		.name = "intel-reset",
		.of_match_table = पूर्णांकel_reset_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकel_reset_driver);
पूर्ण

/*
 * RCU is प्रणाली core entity which is in Always On Doमुख्य whose घड़ीs
 * or resource initialization happens in प्रणाली core initialization.
 * Also, it is required क्रम most of the platक्रमm or architecture
 * specअगरic devices to perक्रमm reset operation as part of initialization.
 * So perक्रमm RCU as post core initialization.
 */
postcore_initcall(पूर्णांकel_reset_init);
