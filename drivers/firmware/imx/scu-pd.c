<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *	Dong Aisheng <aisheng.करोng@nxp.com>
 *
 * Implementation of the SCU based Power Doमुख्यs
 *
 * NOTE: a better implementation suggested by Ulf Hansson is using a
 * single global घातer करोमुख्य and implement the ->attach|detach_dev()
 * callback क्रम the genpd and use the regular of_genpd_add_provider_simple().
 * From within the ->attach_dev(), we could get the OF node क्रम
 * the device that is being attached and then parse the घातer-करोमुख्य
 * cell containing the "resource id" and store that in the per device
 * काष्ठा generic_pm_करोमुख्य_data (we have व्योम poपूर्णांकer there क्रम
 * storing these kind of things).
 *
 * Additionally, we need to implement the ->stop() and ->start()
 * callbacks of genpd, which is where you "power on/off" devices,
 * rather than using the above ->घातer_on|off() callbacks.
 *
 * However, there're two known issues:
 * 1. The ->attach_dev() of घातer करोमुख्य infraकाष्ठाure still करोes
 *    not support multi करोमुख्यs हाल as the काष्ठा device *dev passed
 *    in is a भव PD device, it करोes not help क्रम parsing the real
 *    device resource id from device tree, so it's unware of which
 *    real sub घातer करोमुख्य of device should be attached.
 *
 *    The framework needs some proper extension to support multi घातer
 *    करोमुख्य हालs.
 *
 *    Update: Genpd assigns the ->of_node क्रम the भव device beक्रमe it
 *    invokes ->attach_dev() callback, hence parsing क्रम device resources via
 *    DT should work fine.
 *
 * 2. It also अवरोधs most of current drivers as the driver probe sequence
 *    behavior changed अगर removing ->घातer_on|off() callback and use
 *    ->start() and ->stop() instead. genpd_dev_pm_attach will only घातer
 *    up the करोमुख्य and attach device, but will not call .start() which
 *    relies on device runसमय pm. That means the device घातer is still
 *    not up beक्रमe running driver probe function. For SCU enabled
 *    platक्रमms, all device drivers accessing रेजिस्टरs/घड़ी without घातer
 *    करोमुख्य enabled will trigger a HW access error. That means we need fix
 *    most drivers probe sequence with proper runसमय pm.
 *
 *    Update: Runसमय PM support isn't necessary. Instead, this can easily be
 *    fixed in drivers by adding a call to dev_pm_करोमुख्य_start() during probe.
 *
 * In summary, the second part needs to be addressed via minor updates to the
 * relevant drivers, beक्रमe the "single global power domain" model can be used.
 *
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/firmware/imx/svc/rm.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>

/* SCU Power Mode Protocol definition */
काष्ठा imx_sc_msg_req_set_resource_घातer_mode अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u16 resource;
	u8 mode;
पूर्ण __packed __aligned(4);

#घोषणा IMX_SCU_PD_NAME_SIZE 20
काष्ठा imx_sc_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य pd;
	अक्षर name[IMX_SCU_PD_NAME_SIZE];
	u32 rsrc;
पूर्ण;

काष्ठा imx_sc_pd_range अणु
	अक्षर *name;
	u32 rsrc;
	u8 num;

	/* add करोमुख्य index */
	bool postfix;
	u8 start_from;
पूर्ण;

काष्ठा imx_sc_pd_soc अणु
	स्थिर काष्ठा imx_sc_pd_range *pd_ranges;
	u8 num_ranges;
पूर्ण;

अटल पूर्णांक imx_con_rsrc;

अटल स्थिर काष्ठा imx_sc_pd_range imx8qxp_scu_pd_ranges[] = अणु
	/* LSIO SS */
	अणु "pwm", IMX_SC_R_PWM_0, 8, true, 0 पूर्ण,
	अणु "gpio", IMX_SC_R_GPIO_0, 8, true, 0 पूर्ण,
	अणु "gpt", IMX_SC_R_GPT_0, 5, true, 0 पूर्ण,
	अणु "kpp", IMX_SC_R_KPP, 1, false, 0 पूर्ण,
	अणु "fspi", IMX_SC_R_FSPI_0, 2, true, 0 पूर्ण,
	अणु "mu_a", IMX_SC_R_MU_0A, 14, true, 0 पूर्ण,
	अणु "mu_b", IMX_SC_R_MU_5B, 9, true, 5 पूर्ण,

	/* CONN SS */
	अणु "usb", IMX_SC_R_USB_0, 2, true, 0 पूर्ण,
	अणु "usb0phy", IMX_SC_R_USB_0_PHY, 1, false, 0 पूर्ण,
	अणु "usb2", IMX_SC_R_USB_2, 1, false, 0 पूर्ण,
	अणु "usb2phy", IMX_SC_R_USB_2_PHY, 1, false, 0 पूर्ण,
	अणु "sdhc", IMX_SC_R_SDHC_0, 3, true, 0 पूर्ण,
	अणु "enet", IMX_SC_R_ENET_0, 2, true, 0 पूर्ण,
	अणु "nand", IMX_SC_R_न_अंकD, 1, false, 0 पूर्ण,
	अणु "mlb", IMX_SC_R_MLB_0, 1, true, 0 पूर्ण,

	/* AUDIO SS */
	अणु "audio-pll0", IMX_SC_R_AUDIO_PLL_0, 1, false, 0 पूर्ण,
	अणु "audio-pll1", IMX_SC_R_AUDIO_PLL_1, 1, false, 0 पूर्ण,
	अणु "audio-clk-0", IMX_SC_R_AUDIO_CLK_0, 1, false, 0 पूर्ण,
	अणु "audio-clk-1", IMX_SC_R_AUDIO_CLK_1, 1, false, 0 पूर्ण,
	अणु "dma0-ch", IMX_SC_R_DMA_0_CH0, 16, true, 0 पूर्ण,
	अणु "dma1-ch", IMX_SC_R_DMA_1_CH0, 16, true, 0 पूर्ण,
	अणु "dma2-ch", IMX_SC_R_DMA_2_CH0, 5, true, 0 पूर्ण,
	अणु "asrc0", IMX_SC_R_ASRC_0, 1, false, 0 पूर्ण,
	अणु "asrc1", IMX_SC_R_ASRC_1, 1, false, 0 पूर्ण,
	अणु "esai0", IMX_SC_R_ESAI_0, 1, false, 0 पूर्ण,
	अणु "spdif0", IMX_SC_R_SPDIF_0, 1, false, 0 पूर्ण,
	अणु "spdif1", IMX_SC_R_SPDIF_1, 1, false, 0 पूर्ण,
	अणु "sai", IMX_SC_R_SAI_0, 3, true, 0 पूर्ण,
	अणु "sai3", IMX_SC_R_SAI_3, 1, false, 0 पूर्ण,
	अणु "sai4", IMX_SC_R_SAI_4, 1, false, 0 पूर्ण,
	अणु "sai5", IMX_SC_R_SAI_5, 1, false, 0 पूर्ण,
	अणु "sai6", IMX_SC_R_SAI_6, 1, false, 0 पूर्ण,
	अणु "sai7", IMX_SC_R_SAI_7, 1, false, 0 पूर्ण,
	अणु "amix", IMX_SC_R_AMIX, 1, false, 0 पूर्ण,
	अणु "mqs0", IMX_SC_R_MQS_0, 1, false, 0 पूर्ण,
	अणु "dsp", IMX_SC_R_DSP, 1, false, 0 पूर्ण,
	अणु "dsp-ram", IMX_SC_R_DSP_RAM, 1, false, 0 पूर्ण,

	/* DMA SS */
	अणु "can", IMX_SC_R_CAN_0, 3, true, 0 पूर्ण,
	अणु "ftm", IMX_SC_R_FTM_0, 2, true, 0 पूर्ण,
	अणु "lpi2c", IMX_SC_R_I2C_0, 4, true, 0 पूर्ण,
	अणु "adc", IMX_SC_R_ADC_0, 2, true, 0 पूर्ण,
	अणु "lcd", IMX_SC_R_LCD_0, 1, true, 0 पूर्ण,
	अणु "lcd0-pwm", IMX_SC_R_LCD_0_PWM_0, 1, true, 0 पूर्ण,
	अणु "lpuart", IMX_SC_R_UART_0, 4, true, 0 पूर्ण,
	अणु "lpspi", IMX_SC_R_SPI_0, 4, true, 0 पूर्ण,
	अणु "irqstr_dsp", IMX_SC_R_IRQSTR_DSP, 1, false, 0 पूर्ण,

	/* VPU SS */
	अणु "vpu", IMX_SC_R_VPU, 1, false, 0 पूर्ण,
	अणु "vpu-pid", IMX_SC_R_VPU_PID0, 8, true, 0 पूर्ण,
	अणु "vpu-dec0", IMX_SC_R_VPU_DEC_0, 1, false, 0 पूर्ण,
	अणु "vpu-enc0", IMX_SC_R_VPU_ENC_0, 1, false, 0 पूर्ण,

	/* GPU SS */
	अणु "gpu0-pid", IMX_SC_R_GPU_0_PID0, 4, true, 0 पूर्ण,

	/* HSIO SS */
	अणु "pcie-b", IMX_SC_R_PCIE_B, 1, false, 0 पूर्ण,
	अणु "serdes-1", IMX_SC_R_SERDES_1, 1, false, 0 पूर्ण,
	अणु "hsio-gpio", IMX_SC_R_HSIO_GPIO, 1, false, 0 पूर्ण,

	/* MIPI SS */
	अणु "mipi0", IMX_SC_R_MIPI_0, 1, false, 0 पूर्ण,
	अणु "mipi0-pwm0", IMX_SC_R_MIPI_0_PWM_0, 1, false, 0 पूर्ण,
	अणु "mipi0-i2c", IMX_SC_R_MIPI_0_I2C_0, 2, true, 0 पूर्ण,

	अणु "mipi1", IMX_SC_R_MIPI_1, 1, false, 0 पूर्ण,
	अणु "mipi1-pwm0", IMX_SC_R_MIPI_1_PWM_0, 1, false, 0 पूर्ण,
	अणु "mipi1-i2c", IMX_SC_R_MIPI_1_I2C_0, 2, true, 0 पूर्ण,

	/* LVDS SS */
	अणु "lvds0", IMX_SC_R_LVDS_0, 1, false, 0 पूर्ण,
	अणु "lvds1", IMX_SC_R_LVDS_1, 1, false, 0 पूर्ण,

	/* DC SS */
	अणु "dc0", IMX_SC_R_DC_0, 1, false, 0 पूर्ण,
	अणु "dc0-pll", IMX_SC_R_DC_0_PLL_0, 2, true, 0 पूर्ण,
	अणु "dc0-video", IMX_SC_R_DC_0_VIDEO0, 2, true, 0 पूर्ण,

	/* CM40 SS */
	अणु "cm40-i2c", IMX_SC_R_M4_0_I2C, 1, false, 0 पूर्ण,
	अणु "cm40-intmux", IMX_SC_R_M4_0_INTMUX, 1, false, 0 पूर्ण,
	अणु "cm40-pid", IMX_SC_R_M4_0_PID0, 5, true, 0पूर्ण,
	अणु "cm40-mu-a1", IMX_SC_R_M4_0_MU_1A, 1, false, 0पूर्ण,
	अणु "cm40-lpuart", IMX_SC_R_M4_0_UART, 1, false, 0पूर्ण,

	/* CM41 SS */
	अणु "cm41-i2c", IMX_SC_R_M4_1_I2C, 1, false, 0 पूर्ण,
	अणु "cm41-intmux", IMX_SC_R_M4_1_INTMUX, 1, false, 0 पूर्ण,
	अणु "cm41-pid", IMX_SC_R_M4_1_PID0, 5, true, 0पूर्ण,
	अणु "cm41-mu-a1", IMX_SC_R_M4_1_MU_1A, 1, false, 0पूर्ण,
	अणु "cm41-lpuart", IMX_SC_R_M4_1_UART, 1, false, 0पूर्ण,

	/* IMAGE SS */
	अणु "img-jpegdec-mp", IMX_SC_R_MJPEG_DEC_MP, 1, false, 0 पूर्ण,
	अणु "img-jpegdec-s0", IMX_SC_R_MJPEG_DEC_S0, 4, true, 0 पूर्ण,
	अणु "img-jpegenc-mp", IMX_SC_R_MJPEG_ENC_MP, 1, false, 0 पूर्ण,
	अणु "img-jpegenc-s0", IMX_SC_R_MJPEG_ENC_S0, 4, true, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx_sc_pd_soc imx8qxp_scu_pd = अणु
	.pd_ranges = imx8qxp_scu_pd_ranges,
	.num_ranges = ARRAY_SIZE(imx8qxp_scu_pd_ranges),
पूर्ण;

अटल काष्ठा imx_sc_ipc *pm_ipc_handle;

अटल अंतरभूत काष्ठा imx_sc_pm_करोमुख्य *
to_imx_sc_pd(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस container_of(genpd, काष्ठा imx_sc_pm_करोमुख्य, pd);
पूर्ण

अटल व्योम imx_sc_pd_get_console_rsrc(व्योम)
अणु
	काष्ठा of_phandle_args specs;
	पूर्णांक ret;

	अगर (!of_मानक_निकास)
		वापस;

	ret = of_parse_phandle_with_args(of_मानक_निकास, "power-domains",
					 "#power-domain-cells",
					 0, &specs);
	अगर (ret)
		वापस;

	imx_con_rsrc = specs.args[0];
पूर्ण

अटल पूर्णांक imx_sc_pd_घातer(काष्ठा generic_pm_करोमुख्य *करोमुख्य, bool घातer_on)
अणु
	काष्ठा imx_sc_msg_req_set_resource_घातer_mode msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	काष्ठा imx_sc_pm_करोमुख्य *pd;
	पूर्णांक ret;

	pd = to_imx_sc_pd(करोमुख्य);

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_SET_RESOURCE_POWER_MODE;
	hdr->size = 2;

	msg.resource = pd->rsrc;
	msg.mode = घातer_on ? IMX_SC_PM_PW_MODE_ON : IMX_SC_PM_PW_MODE_LP;

	ret = imx_scu_call_rpc(pm_ipc_handle, &msg, true);
	अगर (ret)
		dev_err(&करोमुख्य->dev, "failed to power %s resource %d ret %d\n",
			घातer_on ? "up" : "off", pd->rsrc, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_sc_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस imx_sc_pd_घातer(करोमुख्य, true);
पूर्ण

अटल पूर्णांक imx_sc_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस imx_sc_pd_घातer(करोमुख्य, false);
पूर्ण

अटल काष्ठा generic_pm_करोमुख्य *imx_scu_pd_xlate(काष्ठा of_phandle_args *spec,
						  व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *करोमुख्य = ERR_PTR(-ENOENT);
	काष्ठा genpd_onecell_data *pd_data = data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pd_data->num_करोमुख्यs; i++) अणु
		काष्ठा imx_sc_pm_करोमुख्य *sc_pd;

		sc_pd = to_imx_sc_pd(pd_data->करोमुख्यs[i]);
		अगर (sc_pd->rsrc == spec->args[0]) अणु
			करोमुख्य = &sc_pd->pd;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस करोमुख्य;
पूर्ण

अटल काष्ठा imx_sc_pm_करोमुख्य *
imx_scu_add_pm_करोमुख्य(काष्ठा device *dev, पूर्णांक idx,
		      स्थिर काष्ठा imx_sc_pd_range *pd_ranges)
अणु
	काष्ठा imx_sc_pm_करोमुख्य *sc_pd;
	bool is_off = true;
	पूर्णांक ret;

	अगर (!imx_sc_rm_is_resource_owned(pm_ipc_handle, pd_ranges->rsrc + idx))
		वापस शून्य;

	sc_pd = devm_kzalloc(dev, माप(*sc_pd), GFP_KERNEL);
	अगर (!sc_pd)
		वापस ERR_PTR(-ENOMEM);

	sc_pd->rsrc = pd_ranges->rsrc + idx;
	sc_pd->pd.घातer_off = imx_sc_pd_घातer_off;
	sc_pd->pd.घातer_on = imx_sc_pd_घातer_on;

	अगर (pd_ranges->postfix)
		snम_लिखो(sc_pd->name, माप(sc_pd->name),
			 "%s%i", pd_ranges->name, pd_ranges->start_from + idx);
	अन्यथा
		snम_लिखो(sc_pd->name, माप(sc_pd->name),
			 "%s", pd_ranges->name);

	sc_pd->pd.name = sc_pd->name;
	अगर (imx_con_rsrc == sc_pd->rsrc) अणु
		sc_pd->pd.flags = GENPD_FLAG_RPM_ALWAYS_ON;
		is_off = false;
	पूर्ण

	अगर (sc_pd->rsrc >= IMX_SC_R_LAST) अणु
		dev_warn(dev, "invalid pd %s rsrc id %d found",
			 sc_pd->name, sc_pd->rsrc);

		devm_kमुक्त(dev, sc_pd);
		वापस शून्य;
	पूर्ण

	ret = pm_genpd_init(&sc_pd->pd, शून्य, is_off);
	अगर (ret) अणु
		dev_warn(dev, "failed to init pd %s rsrc id %d",
			 sc_pd->name, sc_pd->rsrc);
		devm_kमुक्त(dev, sc_pd);
		वापस शून्य;
	पूर्ण

	वापस sc_pd;
पूर्ण

अटल पूर्णांक imx_scu_init_pm_करोमुख्यs(काष्ठा device *dev,
				    स्थिर काष्ठा imx_sc_pd_soc *pd_soc)
अणु
	स्थिर काष्ठा imx_sc_pd_range *pd_ranges = pd_soc->pd_ranges;
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	काष्ठा genpd_onecell_data *pd_data;
	काष्ठा imx_sc_pm_करोमुख्य *sc_pd;
	u32 count = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < pd_soc->num_ranges; i++)
		count += pd_ranges[i].num;

	करोमुख्यs = devm_kसुस्मृति(dev, count, माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs)
		वापस -ENOMEM;

	pd_data = devm_kzalloc(dev, माप(*pd_data), GFP_KERNEL);
	अगर (!pd_data)
		वापस -ENOMEM;

	count = 0;
	क्रम (i = 0; i < pd_soc->num_ranges; i++) अणु
		क्रम (j = 0; j < pd_ranges[i].num; j++) अणु
			sc_pd = imx_scu_add_pm_करोमुख्य(dev, j, &pd_ranges[i]);
			अगर (IS_ERR_OR_शून्य(sc_pd))
				जारी;

			करोमुख्यs[count++] = &sc_pd->pd;
			dev_dbg(dev, "added power domain %s\n", sc_pd->pd.name);
		पूर्ण
	पूर्ण

	pd_data->करोमुख्यs = करोमुख्यs;
	pd_data->num_करोमुख्यs = count;
	pd_data->xlate = imx_scu_pd_xlate;

	of_genpd_add_provider_onecell(dev->of_node, pd_data);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_sc_pd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा imx_sc_pd_soc *pd_soc;
	पूर्णांक ret;

	ret = imx_scu_get_handle(&pm_ipc_handle);
	अगर (ret)
		वापस ret;

	pd_soc = of_device_get_match_data(&pdev->dev);
	अगर (!pd_soc)
		वापस -ENODEV;

	imx_sc_pd_get_console_rsrc();

	वापस imx_scu_init_pm_करोमुख्यs(&pdev->dev, pd_soc);
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_sc_pd_match[] = अणु
	अणु .compatible = "fsl,imx8qxp-scu-pd", &imx8qxp_scu_pdपूर्ण,
	अणु .compatible = "fsl,scu-pd", &imx8qxp_scu_pdपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_sc_pd_driver = अणु
	.driver = अणु
		.name = "imx-scu-pd",
		.of_match_table = imx_sc_pd_match,
	पूर्ण,
	.probe = imx_sc_pd_probe,
पूर्ण;
builtin_platक्रमm_driver(imx_sc_pd_driver);

MODULE_AUTHOR("Dong Aisheng <aisheng.dong@nxp.com>");
MODULE_DESCRIPTION("IMX SCU Power Domain driver");
MODULE_LICENSE("GPL v2");
