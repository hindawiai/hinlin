<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Legacy platक्रमm_data quirks
 *
 * Copyright (C) 2016 BayLibre, Inc
 */
#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <media/i2c/tvp514x.h>
#समावेश <media/i2c/adv7343.h>

#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>

काष्ठा pdata_init अणु
	स्थिर अक्षर *compatible;
	व्योम (*fn)(व्योम);
पूर्ण;

#घोषणा TVP5147_CH0		"tvp514x-0"
#घोषणा TVP5147_CH1		"tvp514x-1"

/* VPIF capture configuration */
अटल काष्ठा tvp514x_platक्रमm_data tvp5146_pdata = अणु
		.clk_polarity = 0,
		.hs_polarity  = 1,
		.vs_polarity  = 1,
पूर्ण;

#घोषणा TVP514X_STD_ALL (V4L2_STD_NTSC | V4L2_STD_PAL)

अटल काष्ठा vpअगर_input da850_ch0_inमाला_दो[] = अणु
	अणु
		.input = अणु
			.index = 0,
			.name  = "Composite",
			.type  = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std   = TVP514X_STD_ALL,
		पूर्ण,
		.input_route = INPUT_CVBS_VI2B,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH0,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_input da850_ch1_inमाला_दो[] = अणु
	अणु
		.input = अणु
			.index = 0,
			.name  = "S-Video",
			.type  = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std   = TVP514X_STD_ALL,
		पूर्ण,
		.input_route = INPUT_SVIDEO_VI2C_VI1C,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH1,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_subdev_info da850_vpअगर_capture_sdev_info[] = अणु
	अणु
		.name = TVP5147_CH0,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
	अणु
		.name = TVP5147_CH1,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5c),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_capture_config da850_vpअगर_capture_config = अणु
	.subdev_info = da850_vpअगर_capture_sdev_info,
	.subdev_count = ARRAY_SIZE(da850_vpअगर_capture_sdev_info),
	.chan_config[0] = अणु
		.inमाला_दो = da850_ch0_inमाला_दो,
		.input_count = ARRAY_SIZE(da850_ch0_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol  = 1,
			.vd_pol  = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.chan_config[1] = अणु
		.inमाला_दो = da850_ch1_inमाला_दो,
		.input_count = ARRAY_SIZE(da850_ch1_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol  = 1,
			.vd_pol  = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.card_name = "DA850/OMAP-L138 Video Capture",
पूर्ण;

अटल व्योम __init da850_vpअगर_legacy_रेजिस्टर_capture(व्योम)
अणु
	पूर्णांक ret;

	ret = da850_रेजिस्टर_vpअगर_capture(&da850_vpअगर_capture_config);
	अगर (ret)
		pr_warn("%s: VPIF capture setup failed: %d\n",
			__func__, ret);
पूर्ण

अटल व्योम __init da850_vpअगर_capture_legacy_init_lcdk(व्योम)
अणु
	da850_vpअगर_capture_config.subdev_count = 1;
	da850_vpअगर_legacy_रेजिस्टर_capture();
पूर्ण

अटल व्योम __init da850_vpअगर_capture_legacy_init_evm(व्योम)
अणु
	da850_vpअगर_legacy_रेजिस्टर_capture();
पूर्ण

अटल काष्ठा adv7343_platक्रमm_data adv7343_pdata = अणु
	.mode_config = अणु
		.dac = अणु 1, 1, 1 पूर्ण,
	पूर्ण,
	.sd_config = अणु
		.sd_dac_out = अणु 1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_subdev_info da850_vpअगर_subdev[] = अणु
	अणु
		.name = "adv7343",
		.board_info = अणु
			I2C_BOARD_INFO("adv7343", 0x2a),
			.platक्रमm_data = &adv7343_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vpअगर_output da850_ch0_outमाला_दो[] = अणु
	अणु
		.output = अणु
			.index = 0,
			.name = "Composite",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_STD,
			.std = V4L2_STD_ALL,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_COMPOSITE_ID,
	पूर्ण,
	अणु
		.output = अणु
			.index = 1,
			.name = "S-Video",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_STD,
			.std = V4L2_STD_ALL,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_SVIDEO_ID,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_display_config da850_vpअगर_display_config = अणु
	.subdevinfo   = da850_vpअगर_subdev,
	.subdev_count = ARRAY_SIZE(da850_vpअगर_subdev),
	.chan_config[0] = अणु
		.outमाला_दो = da850_ch0_outमाला_दो,
		.output_count = ARRAY_SIZE(da850_ch0_outमाला_दो),
	पूर्ण,
	.card_name    = "DA850/OMAP-L138 Video Display",
पूर्ण;

अटल व्योम __init da850_vpअगर_display_legacy_init_evm(व्योम)
अणु
	पूर्णांक ret;

	ret = da850_रेजिस्टर_vpअगर_display(&da850_vpअगर_display_config);
	अगर (ret)
		pr_warn("%s: VPIF display setup failed: %d\n",
			__func__, ret);
पूर्ण

अटल व्योम pdata_quirks_check(काष्ठा pdata_init *quirks)
अणु
	जबतक (quirks->compatible) अणु
		अगर (of_machine_is_compatible(quirks->compatible)) अणु
			अगर (quirks->fn)
				quirks->fn();
		पूर्ण
		quirks++;
	पूर्ण
पूर्ण

अटल काष्ठा pdata_init pdata_quirks[] __initdata = अणु
	अणु "ti,da850-lcdk", da850_vpअगर_capture_legacy_init_lcdk, पूर्ण,
	अणु "ti,da850-evm", da850_vpअगर_display_legacy_init_evm, पूर्ण,
	अणु "ti,da850-evm", da850_vpअगर_capture_legacy_init_evm, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

व्योम __init pdata_quirks_init(व्योम)
अणु
	pdata_quirks_check(pdata_quirks);
पूर्ण
