<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Raspberry Pi driver क्रम firmware controlled घड़ीs
 *
 * Even though clk-bcm2835 provides an पूर्णांकerface to the hardware रेजिस्टरs क्रम
 * the प्रणाली घड़ीs we've had to factor out 'pllb' as the firmware 'owns' it.
 * We're not allowed to change it directly as we might race with the
 * over-temperature and under-voltage protections provided by the firmware.
 *
 * Copyright (C) 2019 Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/bcm2835/raspberrypi-firmware.h>

क्रमागत rpi_firmware_clk_id अणु
	RPI_FIRMWARE_EMMC_CLK_ID = 1,
	RPI_FIRMWARE_UART_CLK_ID,
	RPI_FIRMWARE_ARM_CLK_ID,
	RPI_FIRMWARE_CORE_CLK_ID,
	RPI_FIRMWARE_V3D_CLK_ID,
	RPI_FIRMWARE_H264_CLK_ID,
	RPI_FIRMWARE_ISP_CLK_ID,
	RPI_FIRMWARE_SDRAM_CLK_ID,
	RPI_FIRMWARE_PIXEL_CLK_ID,
	RPI_FIRMWARE_PWM_CLK_ID,
	RPI_FIRMWARE_HEVC_CLK_ID,
	RPI_FIRMWARE_EMMC2_CLK_ID,
	RPI_FIRMWARE_M2MC_CLK_ID,
	RPI_FIRMWARE_PIXEL_BVB_CLK_ID,
	RPI_FIRMWARE_NUM_CLK_ID,
पूर्ण;

अटल अक्षर *rpi_firmware_clk_names[] = अणु
	[RPI_FIRMWARE_EMMC_CLK_ID]	= "emmc",
	[RPI_FIRMWARE_UART_CLK_ID]	= "uart",
	[RPI_FIRMWARE_ARM_CLK_ID]	= "arm",
	[RPI_FIRMWARE_CORE_CLK_ID]	= "core",
	[RPI_FIRMWARE_V3D_CLK_ID]	= "v3d",
	[RPI_FIRMWARE_H264_CLK_ID]	= "h264",
	[RPI_FIRMWARE_ISP_CLK_ID]	= "isp",
	[RPI_FIRMWARE_SDRAM_CLK_ID]	= "sdram",
	[RPI_FIRMWARE_PIXEL_CLK_ID]	= "pixel",
	[RPI_FIRMWARE_PWM_CLK_ID]	= "pwm",
	[RPI_FIRMWARE_HEVC_CLK_ID]	= "hevc",
	[RPI_FIRMWARE_EMMC2_CLK_ID]	= "emmc2",
	[RPI_FIRMWARE_M2MC_CLK_ID]	= "m2mc",
	[RPI_FIRMWARE_PIXEL_BVB_CLK_ID]	= "pixel-bvb",
पूर्ण;

#घोषणा RPI_FIRMWARE_STATE_ENABLE_BIT	BIT(0)
#घोषणा RPI_FIRMWARE_STATE_WAIT_BIT	BIT(1)

काष्ठा raspberrypi_clk अणु
	काष्ठा device *dev;
	काष्ठा rpi_firmware *firmware;
	काष्ठा platक्रमm_device *cpufreq;
पूर्ण;

काष्ठा raspberrypi_clk_data अणु
	काष्ठा clk_hw hw;

	अचिन्हित पूर्णांक id;

	काष्ठा raspberrypi_clk *rpi;
पूर्ण;

/*
 * Structure of the message passed to Raspberry Pi's firmware in order to
 * change घड़ी rates. The 'disable_turbo' option is only available to the ARM
 * घड़ी (pllb) which we enable by शेष as turbo mode will alter multiple
 * घड़ीs at once.
 *
 * Even though we're able to access the clock registers directly we're bound to
 * use the firmware पूर्णांकerface as the firmware ultimately takes care of
 * mitigating overheating/undervoltage situations and we would be changing
 * frequencies behind his back.
 *
 * For more inक्रमmation on the firmware पूर्णांकerface check:
 * https://github.com/raspberrypi/firmware/wiki/Mailbox-property-पूर्णांकerface
 */
काष्ठा raspberrypi_firmware_prop अणु
	__le32 id;
	__le32 val;
	__le32 disable_turbo;
पूर्ण __packed;

अटल पूर्णांक raspberrypi_घड़ी_property(काष्ठा rpi_firmware *firmware,
				      स्थिर काष्ठा raspberrypi_clk_data *data,
				      u32 tag, u32 *val)
अणु
	काष्ठा raspberrypi_firmware_prop msg = अणु
		.id = cpu_to_le32(data->id),
		.val = cpu_to_le32(*val),
		.disable_turbo = cpu_to_le32(1),
	पूर्ण;
	पूर्णांक ret;

	ret = rpi_firmware_property(firmware, tag, &msg, माप(msg));
	अगर (ret)
		वापस ret;

	*val = le32_to_cpu(msg.val);

	वापस 0;
पूर्ण

अटल पूर्णांक raspberrypi_fw_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा raspberrypi_clk_data *data =
		container_of(hw, काष्ठा raspberrypi_clk_data, hw);
	काष्ठा raspberrypi_clk *rpi = data->rpi;
	u32 val = 0;
	पूर्णांक ret;

	ret = raspberrypi_घड़ी_property(rpi->firmware, data,
					 RPI_FIRMWARE_GET_CLOCK_STATE, &val);
	अगर (ret)
		वापस 0;

	वापस !!(val & RPI_FIRMWARE_STATE_ENABLE_BIT);
पूर्ण


अटल अचिन्हित दीर्घ raspberrypi_fw_get_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा raspberrypi_clk_data *data =
		container_of(hw, काष्ठा raspberrypi_clk_data, hw);
	काष्ठा raspberrypi_clk *rpi = data->rpi;
	u32 val = 0;
	पूर्णांक ret;

	ret = raspberrypi_घड़ी_property(rpi->firmware, data,
					 RPI_FIRMWARE_GET_CLOCK_RATE, &val);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक raspberrypi_fw_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा raspberrypi_clk_data *data =
		container_of(hw, काष्ठा raspberrypi_clk_data, hw);
	काष्ठा raspberrypi_clk *rpi = data->rpi;
	u32 _rate = rate;
	पूर्णांक ret;

	ret = raspberrypi_घड़ी_property(rpi->firmware, data,
					 RPI_FIRMWARE_SET_CLOCK_RATE, &_rate);
	अगर (ret)
		dev_err_ratelimited(rpi->dev, "Failed to change %s frequency: %d",
				    clk_hw_get_name(hw), ret);

	वापस ret;
पूर्ण

अटल पूर्णांक raspberrypi_fw_dumb_determine_rate(काष्ठा clk_hw *hw,
					      काष्ठा clk_rate_request *req)
अणु
	/*
	 * The firmware will करो the rounding but that isn't part of
	 * the पूर्णांकerface with the firmware, so we just करो our best
	 * here.
	 */
	req->rate = clamp(req->rate, req->min_rate, req->max_rate);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops raspberrypi_firmware_clk_ops = अणु
	.is_prepared	= raspberrypi_fw_is_prepared,
	.recalc_rate	= raspberrypi_fw_get_rate,
	.determine_rate	= raspberrypi_fw_dumb_determine_rate,
	.set_rate	= raspberrypi_fw_set_rate,
पूर्ण;

अटल काष्ठा clk_hw *raspberrypi_clk_रेजिस्टर(काष्ठा raspberrypi_clk *rpi,
					       अचिन्हित पूर्णांक parent,
					       अचिन्हित पूर्णांक id)
अणु
	काष्ठा raspberrypi_clk_data *data;
	काष्ठा clk_init_data init = अणुपूर्ण;
	u32 min_rate, max_rate;
	पूर्णांक ret;

	data = devm_kzalloc(rpi->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);
	data->rpi = rpi;
	data->id = id;

	init.name = devm_kaप्र_लिखो(rpi->dev, GFP_KERNEL,
				   "fw-clk-%s",
				   rpi_firmware_clk_names[id]);
	init.ops = &raspberrypi_firmware_clk_ops;
	init.flags = CLK_GET_RATE_NOCACHE;

	data->hw.init = &init;

	ret = raspberrypi_घड़ी_property(rpi->firmware, data,
					 RPI_FIRMWARE_GET_MIN_CLOCK_RATE,
					 &min_rate);
	अगर (ret) अणु
		dev_err(rpi->dev, "Failed to get clock %d min freq: %d",
			id, ret);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = raspberrypi_घड़ी_property(rpi->firmware, data,
					 RPI_FIRMWARE_GET_MAX_CLOCK_RATE,
					 &max_rate);
	अगर (ret) अणु
		dev_err(rpi->dev, "Failed to get clock %d max freq: %d\n",
			id, ret);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = devm_clk_hw_रेजिस्टर(rpi->dev, &data->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	clk_hw_set_rate_range(&data->hw, min_rate, max_rate);

	अगर (id == RPI_FIRMWARE_ARM_CLK_ID) अणु
		ret = devm_clk_hw_रेजिस्टर_clkdev(rpi->dev, &data->hw,
						  शून्य, "cpu0");
		अगर (ret) अणु
			dev_err(rpi->dev, "Failed to initialize clkdev\n");
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस &data->hw;
पूर्ण

काष्ठा rpi_firmware_get_घड़ीs_response अणु
	u32 parent;
	u32 id;
पूर्ण;

अटल पूर्णांक raspberrypi_discover_घड़ीs(काष्ठा raspberrypi_clk *rpi,
				       काष्ठा clk_hw_onecell_data *data)
अणु
	काष्ठा rpi_firmware_get_घड़ीs_response *clks;
	पूर्णांक ret;

	clks = devm_kसुस्मृति(rpi->dev,
			    माप(*clks), RPI_FIRMWARE_NUM_CLK_ID,
			    GFP_KERNEL);
	अगर (!clks)
		वापस -ENOMEM;

	ret = rpi_firmware_property(rpi->firmware, RPI_FIRMWARE_GET_CLOCKS,
				    clks,
				    माप(*clks) * RPI_FIRMWARE_NUM_CLK_ID);
	अगर (ret)
		वापस ret;

	जबतक (clks->id) अणु
		काष्ठा clk_hw *hw;

		चयन (clks->id) अणु
		हाल RPI_FIRMWARE_ARM_CLK_ID:
		हाल RPI_FIRMWARE_CORE_CLK_ID:
		हाल RPI_FIRMWARE_M2MC_CLK_ID:
		हाल RPI_FIRMWARE_V3D_CLK_ID:
		हाल RPI_FIRMWARE_PIXEL_BVB_CLK_ID:
			hw = raspberrypi_clk_रेजिस्टर(rpi, clks->parent,
						      clks->id);
			अगर (IS_ERR(hw))
				वापस PTR_ERR(hw);

			data->hws[clks->id] = hw;
			data->num = clks->id + 1;
			fallthrough;

		शेष:
			clks++;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raspberrypi_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा device_node *firmware_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_firmware *firmware;
	काष्ठा raspberrypi_clk *rpi;
	पूर्णांक ret;

	/*
	 * We can be probed either through the an old-fashioned
	 * platक्रमm device registration or through a DT node that is a
	 * child of the firmware node. Handle both हालs.
	 */
	अगर (dev->of_node)
		firmware_node = of_get_parent(dev->of_node);
	अन्यथा
		firmware_node = of_find_compatible_node(शून्य, शून्य,
							"raspberrypi,bcm2835-firmware");
	अगर (!firmware_node) अणु
		dev_err(dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	firmware = devm_rpi_firmware_get(&pdev->dev, firmware_node);
	of_node_put(firmware_node);
	अगर (!firmware)
		वापस -EPROBE_DEFER;

	rpi = devm_kzalloc(dev, माप(*rpi), GFP_KERNEL);
	अगर (!rpi)
		वापस -ENOMEM;

	rpi->dev = dev;
	rpi->firmware = firmware;
	platक्रमm_set_drvdata(pdev, rpi);

	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hws,
						 RPI_FIRMWARE_NUM_CLK_ID),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	ret = raspberrypi_discover_घड़ीs(rpi, clk_data);
	अगर (ret)
		वापस ret;

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					  clk_data);
	अगर (ret)
		वापस ret;

	rpi->cpufreq = platक्रमm_device_रेजिस्टर_data(dev, "raspberrypi-cpufreq",
						     -1, शून्य, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक raspberrypi_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा raspberrypi_clk *rpi = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(rpi->cpufreq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id raspberrypi_clk_match[] = अणु
	अणु .compatible = "raspberrypi,firmware-clocks" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, raspberrypi_clk_match);

अटल काष्ठा platक्रमm_driver raspberrypi_clk_driver = अणु
	.driver = अणु
		.name = "raspberrypi-clk",
		.of_match_table = raspberrypi_clk_match,
	पूर्ण,
	.probe          = raspberrypi_clk_probe,
	.हटाओ		= raspberrypi_clk_हटाओ,
पूर्ण;
module_platक्रमm_driver(raspberrypi_clk_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de>");
MODULE_DESCRIPTION("Raspberry Pi firmware clock driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:raspberrypi-clk");
