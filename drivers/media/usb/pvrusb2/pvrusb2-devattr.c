<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2007 Mike Isely <isely@pobox.com>
 */

/*

This source file should encompass ALL per-device type inक्रमmation क्रम the
driver.  To define a new device, add elements to the pvr2_device_table and
pvr2_device_desc काष्ठाures.

*/

#समावेश "pvrusb2-devattr.h"
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
/* This is needed in order to pull in tuner type ids... */
#समावेश <linux/i2c.h>
#समावेश <media/tuner.h>
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "lgdt330x.h"
#समावेश "s5h1409.h"
#समावेश "s5h1411.h"
#समावेश "tda10048.h"
#समावेश "tda18271.h"
#समावेश "tda8290.h"
#समावेश "tuner-simple.h"
#समावेश "si2157.h"
#समावेश "lgdt3306a.h"
#समावेश "si2168.h"
#पूर्ण_अगर


/*------------------------------------------------------------------------*/
/* Hauppauge PVR-USB2 Model 29xxx */

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_29xxx[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_SAA7115 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_MSP3400 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_DEMOD पूर्ण,
पूर्ण;

#घोषणा PVR2_FIRMWARE_29xxx "v4l-pvrusb2-29xxx-01.fw"
अटल स्थिर अक्षर *pvr2_fw1_names_29xxx[] = अणु
		PVR2_FIRMWARE_29xxx,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_29xxx = अणु
		.description = "WinTV PVR USB2 Model 29xxx",
		.लघुname = "29xxx",
		.client_table.lst = pvr2_cli_29xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_29xxx),
		.fx2_firmware.lst = pvr2_fw1_names_29xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_29xxx),
		.flag_has_hauppauge_rom = !0,
		.flag_has_analogtuner = !0,
		.flag_has_fmradio = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_29XXX,
पूर्ण;



/*------------------------------------------------------------------------*/
/* Hauppauge PVR-USB2 Model 24xxx */

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_24xxx[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_CX25840 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_WM8775 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_DEMOD पूर्ण,
पूर्ण;

#घोषणा PVR2_FIRMWARE_24xxx "v4l-pvrusb2-24xxx-01.fw"
अटल स्थिर अक्षर *pvr2_fw1_names_24xxx[] = अणु
		PVR2_FIRMWARE_24xxx,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_24xxx = अणु
		.description = "WinTV PVR USB2 Model 24xxx",
		.लघुname = "24xxx",
		.client_table.lst = pvr2_cli_24xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_24xxx),
		.fx2_firmware.lst = pvr2_fw1_names_24xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_24xxx),
		.flag_has_cx25840 = !0,
		.flag_has_wm8775 = !0,
		.flag_has_hauppauge_rom = !0,
		.flag_has_analogtuner = !0,
		.flag_has_fmradio = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_24XXX,
पूर्ण;



/*------------------------------------------------------------------------*/
/* GOTVIEW USB2.0 DVD2 */

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_gotview_2[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_CX25840 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_DEMOD पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_gotview_2 = अणु
		.description = "Gotview USB 2.0 DVD 2",
		.लघुname = "gv2",
		.client_table.lst = pvr2_cli_gotview_2,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_gotview_2),
		.flag_has_cx25840 = !0,
		.शेष_tuner_type = TUNER_PHILIPS_FM1216ME_MK3,
		.flag_has_analogtuner = !0,
		.flag_has_fmradio = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_GOTVIEW,
पूर्ण;



/*------------------------------------------------------------------------*/
/* GOTVIEW USB2.0 DVD Deluxe */

/* (same module list as gotview_2) */

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_gotview_2d = अणु
		.description = "Gotview USB 2.0 DVD Deluxe",
		.लघुname = "gv2d",
		.client_table.lst = pvr2_cli_gotview_2,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_gotview_2),
		.flag_has_cx25840 = !0,
		.शेष_tuner_type = TUNER_PHILIPS_FM1216ME_MK3,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_GOTVIEW,
पूर्ण;



/*------------------------------------------------------------------------*/
/* Terratec Grअसलter AV400 */

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_av400[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_CX25840 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_av400 = अणु
		.description = "Terratec Grabster AV400",
		.लघुname = "av400",
		.flag_is_experimental = 1,
		.client_table.lst = pvr2_cli_av400,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_av400),
		.flag_has_cx25840 = !0,
		.flag_has_analogtuner = 0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_AV400,
पूर्ण;



/*------------------------------------------------------------------------*/
/* OnAir Creator */

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
अटल काष्ठा lgdt330x_config pvr2_lgdt3303_config = अणु
	.demod_chip          = LGDT3303,
	.घड़ी_polarity_flip = 1,
पूर्ण;

अटल पूर्णांक pvr2_lgdt3303_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(lgdt330x_attach, &pvr2_lgdt3303_config,
				 0x0e,
				 &adap->channel.hdw->i2c_adap);
	अगर (adap->fe[0])
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक pvr2_lgh06xf_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	dvb_attach(simple_tuner_attach, adap->fe[0],
		   &adap->channel.hdw->i2c_adap, 0x61,
		   TUNER_LG_TDVS_H06XF);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_onair_creator_fe_props = अणु
	.frontend_attach = pvr2_lgdt3303_attach,
	.tuner_attach    = pvr2_lgh06xf_attach,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_onair_creator[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_SAA7115 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_CS53L32A पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_onair_creator = अणु
		.description = "OnAir Creator Hybrid USB tuner",
		.लघुname = "oac",
		.client_table.lst = pvr2_cli_onair_creator,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_onair_creator),
		.शेष_tuner_type = TUNER_LG_TDVS_H06XF,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.flag_digital_requires_cx23416 = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_ONAIR,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_ONAIR,
		.शेष_std_mask = V4L2_STD_NTSC_M,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_onair_creator_fe_props,
#पूर्ण_अगर
पूर्ण;



/*------------------------------------------------------------------------*/
/* OnAir USB 2.0 */

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
अटल काष्ठा lgdt330x_config pvr2_lgdt3302_config = अणु
	.demod_chip          = LGDT3302,
पूर्ण;

अटल पूर्णांक pvr2_lgdt3302_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(lgdt330x_attach, &pvr2_lgdt3302_config,
				 0x0e,
				 &adap->channel.hdw->i2c_adap);
	अगर (adap->fe[0])
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक pvr2_fcv1236d_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	dvb_attach(simple_tuner_attach, adap->fe[0],
		   &adap->channel.hdw->i2c_adap, 0x61,
		   TUNER_PHILIPS_FCV1236D);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_onair_usb2_fe_props = अणु
	.frontend_attach = pvr2_lgdt3302_attach,
	.tuner_attach    = pvr2_fcv1236d_attach,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_onair_usb2[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_SAA7115 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_CS53L32A पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_onair_usb2 = अणु
		.description = "OnAir USB2 Hybrid USB tuner",
		.लघुname = "oa2",
		.client_table.lst = pvr2_cli_onair_usb2,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_onair_usb2),
		.शेष_tuner_type = TUNER_PHILIPS_FCV1236D,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.flag_digital_requires_cx23416 = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_ONAIR,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_ONAIR,
		.शेष_std_mask = V4L2_STD_NTSC_M,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_onair_usb2_fe_props,
#पूर्ण_अगर
पूर्ण;



/*------------------------------------------------------------------------*/
/* Hauppauge PVR-USB2 Model 73xxx */

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
अटल काष्ठा tda10048_config hauppauge_tda10048_config = अणु
	.demod_address  = 0x10 >> 1,
	.output_mode    = TDA10048_PARALLEL_OUTPUT,
	.fwbulkग_लिखोlen = TDA10048_BULKWRITE_50,
	.inversion      = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3800,
	.dtv8_अगर_freq_khz = TDA10048_IF_4300,
	.clk_freq_khz   = TDA10048_CLK_16000,
	.disable_gate_access = 1,
पूर्ण;

अटल काष्ठा tda829x_config tda829x_no_probe = अणु
	.probe_tuner = TDA829X_DONT_PROBE,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_dvbt_std_map = अणु
	.dvbt_6   = अणु .अगर_freq = 3300, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_7   = अणु .अगर_freq = 3800, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_8   = अणु .अगर_freq = 4300, .agc_mode = 3, .std = 6,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_tda18271_dvb_config = अणु
	.std_map = &hauppauge_tda18271_dvbt_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल पूर्णांक pvr2_tda10048_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(tda10048_attach, &hauppauge_tda10048_config,
				 &adap->channel.hdw->i2c_adap);
	अगर (adap->fe[0])
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक pvr2_73xxx_tda18271_8295_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	dvb_attach(tda829x_attach, adap->fe[0],
		   &adap->channel.hdw->i2c_adap, 0x42,
		   &tda829x_no_probe);
	dvb_attach(tda18271_attach, adap->fe[0], 0x60,
		   &adap->channel.hdw->i2c_adap,
		   &hauppauge_tda18271_dvb_config);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_73xxx_dvb_props = अणु
	.frontend_attach = pvr2_tda10048_attach,
	.tuner_attach    = pvr2_73xxx_tda18271_8295_attach,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_73xxx[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_CX25840 पूर्ण,
	अणु .module_id = PVR2_CLIENT_ID_TUNER,
	  .i2c_address_list = "\x42"पूर्ण,
पूर्ण;

#घोषणा PVR2_FIRMWARE_73xxx "v4l-pvrusb2-73xxx-01.fw"
अटल स्थिर अक्षर *pvr2_fw1_names_73xxx[] = अणु
		PVR2_FIRMWARE_73xxx,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_73xxx = अणु
		.description = "WinTV HVR-1900 Model 73xxx",
		.लघुname = "73xxx",
		.client_table.lst = pvr2_cli_73xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_73xxx),
		.fx2_firmware.lst = pvr2_fw1_names_73xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_73xxx),
		.flag_has_cx25840 = !0,
		.flag_has_hauppauge_rom = !0,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.flag_fx2_16kb = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_HAUPPAUGE,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_ZILOG,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_73xxx_dvb_props,
#पूर्ण_अगर
पूर्ण;



/*------------------------------------------------------------------------*/
/* Hauppauge PVR-USB2 Model 75xxx */

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
अटल काष्ठा s5h1409_config pvr2_s5h1409_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_PARALLEL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_अगर        = 4000,
	.inversion     = S5H1409_INVERSION_ON,
	.status_mode   = S5H1409_DEMODLOCKING,
पूर्ण;

अटल काष्ठा s5h1411_config pvr2_s5h1411_config = अणु
	.output_mode   = S5H1411_PARALLEL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_अगर        = S5H1411_IF_44000,
	.qam_अगर        = S5H1411_IF_4000,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 5380, .agc_mode = 3, .std = 3,
		      .अगर_lvl = 6, .rfagc_top = 0x37, पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 6, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_tda18271_config = अणु
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल पूर्णांक pvr2_s5h1409_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(s5h1409_attach, &pvr2_s5h1409_config,
				 &adap->channel.hdw->i2c_adap);
	अगर (adap->fe[0])
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक pvr2_s5h1411_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(s5h1411_attach, &pvr2_s5h1411_config,
				 &adap->channel.hdw->i2c_adap);
	अगर (adap->fe[0])
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक pvr2_tda18271_8295_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	dvb_attach(tda829x_attach, adap->fe[0],
		   &adap->channel.hdw->i2c_adap, 0x42,
		   &tda829x_no_probe);
	dvb_attach(tda18271_attach, adap->fe[0], 0x60,
		   &adap->channel.hdw->i2c_adap,
		   &hauppauge_tda18271_config);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_750xx_dvb_props = अणु
	.frontend_attach = pvr2_s5h1409_attach,
	.tuner_attach    = pvr2_tda18271_8295_attach,
पूर्ण;

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_751xx_dvb_props = अणु
	.frontend_attach = pvr2_s5h1411_attach,
	.tuner_attach    = pvr2_tda18271_8295_attach,
पूर्ण;
#पूर्ण_अगर

#घोषणा PVR2_FIRMWARE_75xxx "v4l-pvrusb2-73xxx-01.fw"
अटल स्थिर अक्षर *pvr2_fw1_names_75xxx[] = अणु
		PVR2_FIRMWARE_75xxx,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_750xx = अणु
		.description = "WinTV HVR-1950 Model 750xx",
		.लघुname = "750xx",
		.client_table.lst = pvr2_cli_73xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_73xxx),
		.fx2_firmware.lst = pvr2_fw1_names_75xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_75xxx),
		.flag_has_cx25840 = !0,
		.flag_has_hauppauge_rom = !0,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.flag_fx2_16kb = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_HAUPPAUGE,
		.शेष_std_mask = V4L2_STD_NTSC_M,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_ZILOG,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_750xx_dvb_props,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_751xx = अणु
		.description = "WinTV HVR-1950 Model 751xx",
		.लघुname = "751xx",
		.client_table.lst = pvr2_cli_73xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_73xxx),
		.fx2_firmware.lst = pvr2_fw1_names_75xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_75xxx),
		.flag_has_cx25840 = !0,
		.flag_has_hauppauge_rom = !0,
		.flag_has_analogtuner = !0,
		.flag_has_composite = !0,
		.flag_has_svideo = !0,
		.flag_fx2_16kb = !0,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_HAUPPAUGE,
		.शेष_std_mask = V4L2_STD_NTSC_M,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_ZILOG,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_751xx_dvb_props,
#पूर्ण_अगर
पूर्ण;

/*------------------------------------------------------------------------*/
/*    Hauppauge PVR-USB2 Model 160000 / 160111 -- HVR-1955 / HVR-1975     */

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
अटल पूर्णांक pvr2_si2157_attach(काष्ठा pvr2_dvb_adapter *adap);
अटल पूर्णांक pvr2_si2168_attach(काष्ठा pvr2_dvb_adapter *adap);
अटल पूर्णांक pvr2_dual_fe_attach(काष्ठा pvr2_dvb_adapter *adap);
अटल पूर्णांक pvr2_lgdt3306a_attach(काष्ठा pvr2_dvb_adapter *adap);

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_160000_dvb_props = अणु
	.frontend_attach = pvr2_dual_fe_attach,
	.tuner_attach    = pvr2_si2157_attach,
पूर्ण;

अटल स्थिर काष्ठा pvr2_dvb_props pvr2_160111_dvb_props = अणु
	.frontend_attach = pvr2_lgdt3306a_attach,
	.tuner_attach    = pvr2_si2157_attach,
पूर्ण;

अटल पूर्णांक pvr2_si2157_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	काष्ठा si2157_config si2157_config = अणुपूर्ण;

	si2157_config.inversion = 1;
	si2157_config.fe = adap->fe[0];

	adap->i2c_client_tuner = dvb_module_probe("si2157", "si2177",
						  &adap->channel.hdw->i2c_adap,
						  0x60, &si2157_config);

	अगर (!adap->i2c_client_tuner)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_si2168_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा i2c_adapter *adapter;

	pr_debug("%s()\n", __func__);

	si2168_config.fe = &adap->fe[1];
	si2168_config.i2c_adapter = &adapter;
	si2168_config.ts_mode = SI2168_TS_PARALLEL; /*2, 1-serial, 2-parallel.*/
	si2168_config.ts_घड़ी_gapped = 1; /*0-disabled, 1-enabled.*/
	si2168_config.ts_घड़ी_inv = 0; /*0-not-invert, 1-invert*/
	si2168_config.spectral_inversion = 1; /*0-not-invert, 1-invert*/

	adap->i2c_client_demod[1] = dvb_module_probe("si2168", शून्य,
						     &adap->channel.hdw->i2c_adap,
						     0x64, &si2168_config);

	अगर (!adap->i2c_client_demod[1])
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_lgdt3306a_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	काष्ठा lgdt3306a_config lgdt3306a_config;
	काष्ठा i2c_adapter *adapter;

	pr_debug("%s()\n", __func__);

	lgdt3306a_config.fe = &adap->fe[0];
	lgdt3306a_config.i2c_adapter = &adapter;
	lgdt3306a_config.deny_i2c_rptr = 1;
	lgdt3306a_config.spectral_inversion = 1;
	lgdt3306a_config.qam_अगर_khz = 4000;
	lgdt3306a_config.vsb_अगर_khz = 3250;
	lgdt3306a_config.mpeg_mode = LGDT3306A_MPEG_PARALLEL;
	lgdt3306a_config.tpclk_edge = LGDT3306A_TPCLK_FALLING_EDGE;
	lgdt3306a_config.tpvalid_polarity = LGDT3306A_TP_VALID_LOW;
	lgdt3306a_config.xtalMHz = 25; /* demod घड़ी MHz; 24/25 supported */

	adap->i2c_client_demod[0] = dvb_module_probe("lgdt3306a", शून्य,
						     &adap->channel.hdw->i2c_adap,
						     0x59, &lgdt3306a_config);

	अगर (!adap->i2c_client_demod[0])
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_dual_fe_attach(काष्ठा pvr2_dvb_adapter *adap)
अणु
	pr_debug("%s()\n", __func__);

	अगर (pvr2_lgdt3306a_attach(adap) != 0)
		वापस -ENODEV;

	अगर (pvr2_si2168_attach(adap) != 0) अणु
		dvb_module_release(adap->i2c_client_demod[0]);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा PVR2_FIRMWARE_160xxx "v4l-pvrusb2-160xxx-01.fw"
अटल स्थिर अक्षर *pvr2_fw1_names_160xxx[] = अणु
		PVR2_FIRMWARE_160xxx,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_client_desc pvr2_cli_160xxx[] = अणु
	अणु .module_id = PVR2_CLIENT_ID_CX25840 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_160000 = अणु
		.description = "WinTV HVR-1975 Model 160000",
		.लघुname = "160000",
		.client_table.lst = pvr2_cli_160xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_160xxx),
		.fx2_firmware.lst = pvr2_fw1_names_160xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_160xxx),
		.शेष_tuner_type = TUNER_ABSENT,
		.flag_has_cx25840 = 1,
		.flag_has_hauppauge_rom = 1,
		.flag_has_analogtuner = 1,
		.flag_has_composite = 1,
		.flag_has_svideo = 1,
		.flag_fx2_16kb = 1,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_HAUPPAUGE,
		.शेष_std_mask = V4L2_STD_NTSC_M,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_ZILOG,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_160000_dvb_props,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pvr2_device_desc pvr2_device_160111 = अणु
		.description = "WinTV HVR-1955 Model 160111",
		.लघुname = "160111",
		.client_table.lst = pvr2_cli_160xxx,
		.client_table.cnt = ARRAY_SIZE(pvr2_cli_160xxx),
		.fx2_firmware.lst = pvr2_fw1_names_160xxx,
		.fx2_firmware.cnt = ARRAY_SIZE(pvr2_fw1_names_160xxx),
		.शेष_tuner_type = TUNER_ABSENT,
		.flag_has_cx25840 = 1,
		.flag_has_hauppauge_rom = 1,
		.flag_has_analogtuner = 1,
		.flag_has_composite = 1,
		.flag_has_svideo = 1,
		.flag_fx2_16kb = 1,
		.संकेत_routing_scheme = PVR2_ROUTING_SCHEME_HAUPPAUGE,
		.digital_control_scheme = PVR2_DIGITAL_SCHEME_HAUPPAUGE,
		.शेष_std_mask = V4L2_STD_NTSC_M,
		.led_scheme = PVR2_LED_SCHEME_HAUPPAUGE,
		.ir_scheme = PVR2_IR_SCHEME_ZILOG,
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
		.dvb_props = &pvr2_160111_dvb_props,
#पूर्ण_अगर
पूर्ण;

/*------------------------------------------------------------------------*/

काष्ठा usb_device_id pvr2_device_table[] = अणु
	अणु USB_DEVICE(0x2040, 0x2900),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_29xxxपूर्ण,
	अणु USB_DEVICE(0x2040, 0x2950), /* Logically identical to 2900 */
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_29xxxपूर्ण,
	अणु USB_DEVICE(0x2040, 0x2400),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_24xxxपूर्ण,
	अणु USB_DEVICE(0x1164, 0x0622),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_gotview_2पूर्ण,
	अणु USB_DEVICE(0x1164, 0x0602),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_gotview_2dपूर्ण,
	अणु USB_DEVICE(0x11ba, 0x1003),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_onair_creatorपूर्ण,
	अणु USB_DEVICE(0x11ba, 0x1001),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_onair_usb2पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7300),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_73xxxपूर्ण,
	अणु USB_DEVICE(0x2040, 0x7500),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_750xxपूर्ण,
	अणु USB_DEVICE(0x2040, 0x7501),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_751xxपूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0039),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_av400पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7502),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_160111पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7510),
	  .driver_info = (kernel_uदीर्घ_t)&pvr2_device_160000पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, pvr2_device_table);
MODULE_FIRMWARE(PVR2_FIRMWARE_29xxx);
MODULE_FIRMWARE(PVR2_FIRMWARE_24xxx);
MODULE_FIRMWARE(PVR2_FIRMWARE_73xxx);
MODULE_FIRMWARE(PVR2_FIRMWARE_75xxx);
