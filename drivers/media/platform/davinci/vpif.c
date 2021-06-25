<शैली गुरु>
/*
 * vpअगर - Video Port Interface driver
 * VPIF is a receiver and transmitter क्रम video data. It has two channels(0, 1)
 * that receiving video byte stream and two channels(2, 3) क्रम video output.
 * The hardware supports SDTV, HDTV क्रमmats, raw data capture.
 * Currently, the driver supports NTSC and PAL standards.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/of_graph.h>

#समावेश "vpif.h"

MODULE_DESCRIPTION("TI DaVinci Video Port Interface driver");
MODULE_LICENSE("GPL");

#घोषणा VPIF_DRIVER_NAME	"vpif"
MODULE_ALIAS("platform:" VPIF_DRIVER_NAME);

#घोषणा VPIF_CH0_MAX_MODES	22
#घोषणा VPIF_CH1_MAX_MODES	2
#घोषणा VPIF_CH2_MAX_MODES	15
#घोषणा VPIF_CH3_MAX_MODES	2

DEFINE_SPINLOCK(vpअगर_lock);
EXPORT_SYMBOL_GPL(vpअगर_lock);

व्योम __iomem *vpअगर_base;
EXPORT_SYMBOL_GPL(vpअगर_base);

/*
 * vpअगर_ch_params: video standard configuration parameters क्रम vpअगर
 *
 * The table must include all presets from supported subdevices.
 */
स्थिर काष्ठा vpअगर_channel_config_params vpअगर_ch_params[] = अणु
	/* HDTV क्रमmats */
	अणु
		.name = "480p59_94",
		.width = 720,
		.height = 480,
		.frm_fmt = 1,
		.ycmux_mode = 0,
		.eav2sav = 138-8,
		.sav2eav = 720,
		.l1 = 1,
		.l3 = 43,
		.l5 = 523,
		.vsize = 525,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_720X480P59_94,
	पूर्ण,
	अणु
		.name = "576p50",
		.width = 720,
		.height = 576,
		.frm_fmt = 1,
		.ycmux_mode = 0,
		.eav2sav = 144-8,
		.sav2eav = 720,
		.l1 = 1,
		.l3 = 45,
		.l5 = 621,
		.vsize = 625,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_720X576P50,
	पूर्ण,
	अणु
		.name = "720p50",
		.width = 1280,
		.height = 720,
		.frm_fmt = 1,
		.ycmux_mode = 0,
		.eav2sav = 700-8,
		.sav2eav = 1280,
		.l1 = 1,
		.l3 = 26,
		.l5 = 746,
		.vsize = 750,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_1280X720P50,
	पूर्ण,
	अणु
		.name = "720p60",
		.width = 1280,
		.height = 720,
		.frm_fmt = 1,
		.ycmux_mode = 0,
		.eav2sav = 370 - 8,
		.sav2eav = 1280,
		.l1 = 1,
		.l3 = 26,
		.l5 = 746,
		.vsize = 750,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_1280X720P60,
	पूर्ण,
	अणु
		.name = "1080I50",
		.width = 1920,
		.height = 1080,
		.frm_fmt = 0,
		.ycmux_mode = 0,
		.eav2sav = 720 - 8,
		.sav2eav = 1920,
		.l1 = 1,
		.l3 = 21,
		.l5 = 561,
		.l7 = 563,
		.l9 = 584,
		.l11 = 1124,
		.vsize = 1125,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_1920X1080I50,
	पूर्ण,
	अणु
		.name = "1080I60",
		.width = 1920,
		.height = 1080,
		.frm_fmt = 0,
		.ycmux_mode = 0,
		.eav2sav = 280 - 8,
		.sav2eav = 1920,
		.l1 = 1,
		.l3 = 21,
		.l5 = 561,
		.l7 = 563,
		.l9 = 584,
		.l11 = 1124,
		.vsize = 1125,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_1920X1080I60,
	पूर्ण,
	अणु
		.name = "1080p60",
		.width = 1920,
		.height = 1080,
		.frm_fmt = 1,
		.ycmux_mode = 0,
		.eav2sav = 280 - 8,
		.sav2eav = 1920,
		.l1 = 1,
		.l3 = 42,
		.l5 = 1122,
		.vsize = 1125,
		.capture_क्रमmat = 0,
		.vbi_supported = 0,
		.hd_sd = 1,
		.dv_timings = V4L2_DV_BT_CEA_1920X1080P60,
	पूर्ण,

	/* SDTV क्रमmats */
	अणु
		.name = "NTSC_M",
		.width = 720,
		.height = 480,
		.frm_fmt = 0,
		.ycmux_mode = 1,
		.eav2sav = 268,
		.sav2eav = 1440,
		.l1 = 1,
		.l3 = 23,
		.l5 = 263,
		.l7 = 266,
		.l9 = 286,
		.l11 = 525,
		.vsize = 525,
		.capture_क्रमmat = 0,
		.vbi_supported = 1,
		.hd_sd = 0,
		.stdid = V4L2_STD_525_60,
	पूर्ण,
	अणु
		.name = "PAL_BDGHIK",
		.width = 720,
		.height = 576,
		.frm_fmt = 0,
		.ycmux_mode = 1,
		.eav2sav = 280,
		.sav2eav = 1440,
		.l1 = 1,
		.l3 = 23,
		.l5 = 311,
		.l7 = 313,
		.l9 = 336,
		.l11 = 624,
		.vsize = 625,
		.capture_क्रमmat = 0,
		.vbi_supported = 1,
		.hd_sd = 0,
		.stdid = V4L2_STD_625_50,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(vpअगर_ch_params);

स्थिर अचिन्हित पूर्णांक vpअगर_ch_params_count = ARRAY_SIZE(vpअगर_ch_params);
EXPORT_SYMBOL_GPL(vpअगर_ch_params_count);

अटल अंतरभूत व्योम vpअगर_wr_bit(u32 reg, u32 bit, u32 val)
अणु
	अगर (val)
		vpअगर_set_bit(reg, bit);
	अन्यथा
		vpअगर_clr_bit(reg, bit);
पूर्ण

/* This काष्ठाure is used to keep track of VPIF size रेजिस्टर's offsets */
काष्ठा vpअगर_रेजिस्टरs अणु
	u32 h_cfg, v_cfg_00, v_cfg_01, v_cfg_02, v_cfg, ch_ctrl;
	u32 line_offset, vanc0_strt, vanc0_size, vanc1_strt;
	u32 vanc1_size, width_mask, len_mask;
	u8 max_modes;
पूर्ण;

अटल स्थिर काष्ठा vpअगर_रेजिस्टरs vpअगरregs[VPIF_NUM_CHANNELS] = अणु
	/* Channel0 */
	अणु
		VPIF_CH0_H_CFG, VPIF_CH0_V_CFG_00, VPIF_CH0_V_CFG_01,
		VPIF_CH0_V_CFG_02, VPIF_CH0_V_CFG_03, VPIF_CH0_CTRL,
		VPIF_CH0_IMG_ADD_OFST, 0, 0, 0, 0, 0x1FFF, 0xFFF,
		VPIF_CH0_MAX_MODES,
	पूर्ण,
	/* Channel1 */
	अणु
		VPIF_CH1_H_CFG, VPIF_CH1_V_CFG_00, VPIF_CH1_V_CFG_01,
		VPIF_CH1_V_CFG_02, VPIF_CH1_V_CFG_03, VPIF_CH1_CTRL,
		VPIF_CH1_IMG_ADD_OFST, 0, 0, 0, 0, 0x1FFF, 0xFFF,
		VPIF_CH1_MAX_MODES,
	पूर्ण,
	/* Channel2 */
	अणु
		VPIF_CH2_H_CFG, VPIF_CH2_V_CFG_00, VPIF_CH2_V_CFG_01,
		VPIF_CH2_V_CFG_02, VPIF_CH2_V_CFG_03, VPIF_CH2_CTRL,
		VPIF_CH2_IMG_ADD_OFST, VPIF_CH2_VANC0_STRT, VPIF_CH2_VANC0_SIZE,
		VPIF_CH2_VANC1_STRT, VPIF_CH2_VANC1_SIZE, 0x7FF, 0x7FF,
		VPIF_CH2_MAX_MODES
	पूर्ण,
	/* Channel3 */
	अणु
		VPIF_CH3_H_CFG, VPIF_CH3_V_CFG_00, VPIF_CH3_V_CFG_01,
		VPIF_CH3_V_CFG_02, VPIF_CH3_V_CFG_03, VPIF_CH3_CTRL,
		VPIF_CH3_IMG_ADD_OFST, VPIF_CH3_VANC0_STRT, VPIF_CH3_VANC0_SIZE,
		VPIF_CH3_VANC1_STRT, VPIF_CH3_VANC1_SIZE, 0x7FF, 0x7FF,
		VPIF_CH3_MAX_MODES
	पूर्ण,
पूर्ण;

/* vpअगर_set_mode_info:
 * This function is used to set horizontal and vertical config parameters
 * As per the standard in the channel, configure the values of L1, L3,
 * L5, L7  L9, L11 in VPIF Register , also ग_लिखो width and height
 */
अटल व्योम vpअगर_set_mode_info(स्थिर काष्ठा vpअगर_channel_config_params *config,
				u8 channel_id, u8 config_channel_id)
अणु
	u32 value;

	value = (config->eav2sav & vpअगरregs[config_channel_id].width_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->sav2eav & vpअगरregs[config_channel_id].width_mask);
	regw(value, vpअगरregs[channel_id].h_cfg);

	value = (config->l1 & vpअगरregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l3 & vpअगरregs[config_channel_id].len_mask);
	regw(value, vpअगरregs[channel_id].v_cfg_00);

	value = (config->l5 & vpअगरregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l7 & vpअगरregs[config_channel_id].len_mask);
	regw(value, vpअगरregs[channel_id].v_cfg_01);

	value = (config->l9 & vpअगरregs[config_channel_id].len_mask);
	value <<= VPIF_CH_LEN_SHIFT;
	value |= (config->l11 & vpअगरregs[config_channel_id].len_mask);
	regw(value, vpअगरregs[channel_id].v_cfg_02);

	value = (config->vsize & vpअगरregs[config_channel_id].len_mask);
	regw(value, vpअगरregs[channel_id].v_cfg);
पूर्ण

/* config_vpअगर_params
 * Function to set the parameters of a channel
 * Mainly modअगरies the channel ciontrol रेजिस्टर
 * It sets frame क्रमmat, yc mux mode
 */
अटल व्योम config_vpअगर_params(काष्ठा vpअगर_params *vpअगरparams,
				u8 channel_id, u8 found)
अणु
	स्थिर काष्ठा vpअगर_channel_config_params *config = &vpअगरparams->std_info;
	u32 value, ch_nip, reg;
	u8 start, end;
	पूर्णांक i;

	start = channel_id;
	end = channel_id + found;

	क्रम (i = start; i < end; i++) अणु
		reg = vpअगरregs[i].ch_ctrl;
		अगर (channel_id < 2)
			ch_nip = VPIF_CAPTURE_CH_NIP;
		अन्यथा
			ch_nip = VPIF_DISPLAY_CH_NIP;

		vpअगर_wr_bit(reg, ch_nip, config->frm_fmt);
		vpअगर_wr_bit(reg, VPIF_CH_YC_MUX_BIT, config->ycmux_mode);
		vpअगर_wr_bit(reg, VPIF_CH_INPUT_FIELD_FRAME_BIT,
					vpअगरparams->video_params.storage_mode);

		/* Set raster scanning SDR Format */
		vpअगर_clr_bit(reg, VPIF_CH_SDR_FMT_BIT);
		vpअगर_wr_bit(reg, VPIF_CH_DATA_MODE_BIT, config->capture_क्रमmat);

		अगर (channel_id > 1)	/* Set the Pixel enable bit */
			vpअगर_set_bit(reg, VPIF_DISPLAY_PIX_EN_BIT);
		अन्यथा अगर (config->capture_क्रमmat) अणु
			/* Set the polarity of various pins */
			vpअगर_wr_bit(reg, VPIF_CH_FID_POLARITY_BIT,
					vpअगरparams->अगरace.fid_pol);
			vpअगर_wr_bit(reg, VPIF_CH_V_VALID_POLARITY_BIT,
					vpअगरparams->अगरace.vd_pol);
			vpअगर_wr_bit(reg, VPIF_CH_H_VALID_POLARITY_BIT,
					vpअगरparams->अगरace.hd_pol);

			value = regr(reg);
			/* Set data width */
			value &= ~(0x3u <<
					VPIF_CH_DATA_WIDTH_BIT);
			value |= ((vpअगरparams->params.data_sz) <<
						     VPIF_CH_DATA_WIDTH_BIT);
			regw(value, reg);
		पूर्ण

		/* Write the pitch in the driver */
		regw((vpअगरparams->video_params.hpitch),
						vpअगरregs[i].line_offset);
	पूर्ण
पूर्ण

/* vpअगर_set_video_params
 * This function is used to set video parameters in VPIF रेजिस्टर
 */
पूर्णांक vpअगर_set_video_params(काष्ठा vpअगर_params *vpअगरparams, u8 channel_id)
अणु
	स्थिर काष्ठा vpअगर_channel_config_params *config = &vpअगरparams->std_info;
	पूर्णांक found = 1;

	vpअगर_set_mode_info(config, channel_id, channel_id);
	अगर (!config->ycmux_mode) अणु
		/* YC are on separate channels (HDTV क्रमmats) */
		vpअगर_set_mode_info(config, channel_id + 1, channel_id);
		found = 2;
	पूर्ण

	config_vpअगर_params(vpअगरparams, channel_id, found);

	regw(0x80, VPIF_REQ_SIZE);
	regw(0x01, VPIF_EMULATION_CTRL);

	वापस found;
पूर्ण
EXPORT_SYMBOL(vpअगर_set_video_params);

व्योम vpअगर_set_vbi_display_params(काष्ठा vpअगर_vbi_params *vbiparams,
				u8 channel_id)
अणु
	u32 value;

	value = 0x3F8 & (vbiparams->hstart0);
	value |= 0x3FFFFFF & ((vbiparams->vstart0) << 16);
	regw(value, vpअगरregs[channel_id].vanc0_strt);

	value = 0x3F8 & (vbiparams->hstart1);
	value |= 0x3FFFFFF & ((vbiparams->vstart1) << 16);
	regw(value, vpअगरregs[channel_id].vanc1_strt);

	value = 0x3F8 & (vbiparams->hsize0);
	value |= 0x3FFFFFF & ((vbiparams->vsize0) << 16);
	regw(value, vpअगरregs[channel_id].vanc0_size);

	value = 0x3F8 & (vbiparams->hsize1);
	value |= 0x3FFFFFF & ((vbiparams->vsize1) << 16);
	regw(value, vpअगरregs[channel_id].vanc1_size);

पूर्ण
EXPORT_SYMBOL(vpअगर_set_vbi_display_params);

पूर्णांक vpअगर_channel_getfid(u8 channel_id)
अणु
	वापस (regr(vpअगरregs[channel_id].ch_ctrl) & VPIF_CH_FID_MASK)
					>> VPIF_CH_FID_SHIFT;
पूर्ण
EXPORT_SYMBOL(vpअगर_channel_getfid);

अटल पूर्णांक vpअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल काष्ठा resource	*res, *res_irq;
	काष्ठा platक्रमm_device *pdev_capture, *pdev_display;
	काष्ठा device_node *endpoपूर्णांक = शून्य;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vpअगर_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(vpअगर_base))
		वापस PTR_ERR(vpअगर_base);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get(&pdev->dev);

	dev_info(&pdev->dev, "vpif probe success\n");

	/*
	 * If VPIF Node has endpoपूर्णांकs, assume "new" DT support,
	 * where capture and display drivers करोn't have DT nodes
	 * so their devices need to be रेजिस्टरed manually here
	 * क्रम their legacy platक्रमm_drivers to work.
	 */
	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(pdev->dev.of_node,
					      endpoपूर्णांक);
	अगर (!endpoपूर्णांक)
		वापस 0;

	/*
	 * For DT platक्रमms, manually create platक्रमm_devices क्रम
	 * capture/display drivers.
	 */
	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq) अणु
		dev_warn(&pdev->dev, "Missing IRQ resource.\n");
		pm_runसमय_put(&pdev->dev);
		वापस -EINVAL;
	पूर्ण

	pdev_capture = devm_kzalloc(&pdev->dev, माप(*pdev_capture),
				    GFP_KERNEL);
	अगर (pdev_capture) अणु
		pdev_capture->name = "vpif_capture";
		pdev_capture->id = -1;
		pdev_capture->resource = res_irq;
		pdev_capture->num_resources = 1;
		pdev_capture->dev.dma_mask = pdev->dev.dma_mask;
		pdev_capture->dev.coherent_dma_mask = pdev->dev.coherent_dma_mask;
		pdev_capture->dev.parent = &pdev->dev;
		platक्रमm_device_रेजिस्टर(pdev_capture);
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "Unable to allocate memory for pdev_capture.\n");
	पूर्ण

	pdev_display = devm_kzalloc(&pdev->dev, माप(*pdev_display),
				    GFP_KERNEL);
	अगर (pdev_display) अणु
		pdev_display->name = "vpif_display";
		pdev_display->id = -1;
		pdev_display->resource = res_irq;
		pdev_display->num_resources = 1;
		pdev_display->dev.dma_mask = pdev->dev.dma_mask;
		pdev_display->dev.coherent_dma_mask = pdev->dev.coherent_dma_mask;
		pdev_display->dev.parent = &pdev->dev;
		platक्रमm_device_रेजिस्टर(pdev_display);
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "Unable to allocate memory for pdev_display.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक vpअगर_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_resume(काष्ठा device *dev)
अणु
	pm_runसमय_get(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vpअगर_pm = अणु
	.suspend        = vpअगर_suspend,
	.resume         = vpअगर_resume,
पूर्ण;

#घोषणा vpअगर_pm_ops (&vpअगर_pm)
#अन्यथा
#घोषणा vpअगर_pm_ops शून्य
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id vpअगर_of_match[] = अणु
	अणु .compatible = "ti,da850-vpif", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vpअगर_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver vpअगर_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(vpअगर_of_match),
		.name	= VPIF_DRIVER_NAME,
		.pm	= vpअगर_pm_ops,
	पूर्ण,
	.हटाओ = vpअगर_हटाओ,
	.probe = vpअगर_probe,
पूर्ण;

अटल व्योम vpअगर_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vpअगर_driver);
पूर्ण

अटल पूर्णांक __init vpअगर_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&vpअगर_driver);
पूर्ण
subsys_initcall(vpअगर_init);
module_निकास(vpअगर_निकास);

