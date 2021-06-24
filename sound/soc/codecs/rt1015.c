<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt1015.c  --  RT1015 ALSA SoC audio amplअगरier driver
//
// Copyright 2019 Realtek Semiconductor Corp.
//
// Author: Jack Yu <jack.yu@realtek.com>
//
//

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/rt1015.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "rl6231.h"
#समावेश "rt1015.h"

अटल स्थिर काष्ठा rt1015_platक्रमm_data i2s_शेष_platक्रमm_data = अणु
	.घातer_up_delay_ms = 50,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt1015_reg[] = अणु
	अणु 0x0000, 0x0000 पूर्ण,
	अणु 0x0004, 0xa000 पूर्ण,
	अणु 0x0006, 0x0003 पूर्ण,
	अणु 0x000a, 0x081e पूर्ण,
	अणु 0x000c, 0x0006 पूर्ण,
	अणु 0x000e, 0x0000 पूर्ण,
	अणु 0x0010, 0x0000 पूर्ण,
	अणु 0x0012, 0x0000 पूर्ण,
	अणु 0x0014, 0x0000 पूर्ण,
	अणु 0x0016, 0x0000 पूर्ण,
	अणु 0x0018, 0x0000 पूर्ण,
	अणु 0x0020, 0x8000 पूर्ण,
	अणु 0x0022, 0x8043 पूर्ण,
	अणु 0x0076, 0x0000 पूर्ण,
	अणु 0x0078, 0x0000 पूर्ण,
	अणु 0x007a, 0x0002 पूर्ण,
	अणु 0x007c, 0x10ec पूर्ण,
	अणु 0x007d, 0x1015 पूर्ण,
	अणु 0x00f0, 0x5000 पूर्ण,
	अणु 0x00f2, 0x004c पूर्ण,
	अणु 0x00f3, 0xecfe पूर्ण,
	अणु 0x00f4, 0x0000 पूर्ण,
	अणु 0x00f6, 0x0400 पूर्ण,
	अणु 0x0100, 0x0028 पूर्ण,
	अणु 0x0102, 0xff02 पूर्ण,
	अणु 0x0104, 0xa213 पूर्ण,
	अणु 0x0106, 0x200c पूर्ण,
	अणु 0x010c, 0x0000 पूर्ण,
	अणु 0x010e, 0x0058 पूर्ण,
	अणु 0x0111, 0x0200 पूर्ण,
	अणु 0x0112, 0x0400 पूर्ण,
	अणु 0x0114, 0x0022 पूर्ण,
	अणु 0x0116, 0x0000 पूर्ण,
	अणु 0x0118, 0x0000 पूर्ण,
	अणु 0x011a, 0x0123 पूर्ण,
	अणु 0x011c, 0x4567 पूर्ण,
	अणु 0x0300, 0x203d पूर्ण,
	अणु 0x0302, 0x001e पूर्ण,
	अणु 0x0311, 0x0000 पूर्ण,
	अणु 0x0313, 0x6014 पूर्ण,
	अणु 0x0314, 0x00a2 पूर्ण,
	अणु 0x031a, 0x00a0 पूर्ण,
	अणु 0x031c, 0x001f पूर्ण,
	अणु 0x031d, 0xffff पूर्ण,
	अणु 0x031e, 0x0000 पूर्ण,
	अणु 0x031f, 0x0000 पूर्ण,
	अणु 0x0320, 0x0000 पूर्ण,
	अणु 0x0321, 0x0000 पूर्ण,
	अणु 0x0322, 0xd7df पूर्ण,
	अणु 0x0328, 0x10b2 पूर्ण,
	अणु 0x0329, 0x0175 पूर्ण,
	अणु 0x032a, 0x36ad पूर्ण,
	अणु 0x032b, 0x7e55 पूर्ण,
	अणु 0x032c, 0x0520 पूर्ण,
	अणु 0x032d, 0xaa00 पूर्ण,
	अणु 0x032e, 0x570e पूर्ण,
	अणु 0x0330, 0xe180 पूर्ण,
	अणु 0x0332, 0x0034 पूर्ण,
	अणु 0x0334, 0x0001 पूर्ण,
	अणु 0x0336, 0x0010 पूर्ण,
	अणु 0x0338, 0x0000 पूर्ण,
	अणु 0x04fa, 0x0030 पूर्ण,
	अणु 0x04fc, 0x35c8 पूर्ण,
	अणु 0x04fe, 0x0800 पूर्ण,
	अणु 0x0500, 0x0400 पूर्ण,
	अणु 0x0502, 0x1000 पूर्ण,
	अणु 0x0504, 0x0000 पूर्ण,
	अणु 0x0506, 0x04ff पूर्ण,
	अणु 0x0508, 0x0010 पूर्ण,
	अणु 0x050a, 0x001a पूर्ण,
	अणु 0x0519, 0x1c68 पूर्ण,
	अणु 0x051a, 0x0ccc पूर्ण,
	अणु 0x051b, 0x0666 पूर्ण,
	अणु 0x051d, 0x0000 पूर्ण,
	अणु 0x051f, 0x0000 पूर्ण,
	अणु 0x0536, 0x061c पूर्ण,
	अणु 0x0538, 0x0000 पूर्ण,
	अणु 0x053a, 0x0000 पूर्ण,
	अणु 0x053c, 0x0000 पूर्ण,
	अणु 0x053d, 0x0000 पूर्ण,
	अणु 0x053e, 0x0000 पूर्ण,
	अणु 0x053f, 0x0000 पूर्ण,
	अणु 0x0540, 0x0000 पूर्ण,
	अणु 0x0541, 0x0000 पूर्ण,
	अणु 0x0542, 0x0000 पूर्ण,
	अणु 0x0543, 0x0000 पूर्ण,
	अणु 0x0544, 0x0000 पूर्ण,
	अणु 0x0568, 0x0000 पूर्ण,
	अणु 0x056a, 0x0000 पूर्ण,
	अणु 0x1000, 0x0040 पूर्ण,
	अणु 0x1002, 0x5405 पूर्ण,
	अणु 0x1006, 0x5515 पूर्ण,
	अणु 0x1007, 0x05f7 पूर्ण,
	अणु 0x1009, 0x0b0a पूर्ण,
	अणु 0x100a, 0x00ef पूर्ण,
	अणु 0x100d, 0x0003 पूर्ण,
	अणु 0x1010, 0xa433 पूर्ण,
	अणु 0x1020, 0x0000 पूर्ण,
	अणु 0x1200, 0x5a01 पूर्ण,
	अणु 0x1202, 0x6524 पूर्ण,
	अणु 0x1204, 0x1f00 पूर्ण,
	अणु 0x1206, 0x0000 पूर्ण,
	अणु 0x1208, 0x0000 पूर्ण,
	अणु 0x120a, 0x0000 पूर्ण,
	अणु 0x120c, 0x0000 पूर्ण,
	अणु 0x120e, 0x0000 पूर्ण,
	अणु 0x1210, 0x0000 पूर्ण,
	अणु 0x1212, 0x0000 पूर्ण,
	अणु 0x1300, 0x10a1 पूर्ण,
	अणु 0x1302, 0x12ff पूर्ण,
	अणु 0x1304, 0x0400 पूर्ण,
	अणु 0x1305, 0x0844 पूर्ण,
	अणु 0x1306, 0x4611 पूर्ण,
	अणु 0x1308, 0x555e पूर्ण,
	अणु 0x130a, 0x0000 पूर्ण,
	अणु 0x130c, 0x2000 पूर्ण,
	अणु 0x130e, 0x0100 पूर्ण,
	अणु 0x130f, 0x0001 पूर्ण,
	अणु 0x1310, 0x0000 पूर्ण,
	अणु 0x1312, 0x0000 पूर्ण,
	अणु 0x1314, 0x0000 पूर्ण,
	अणु 0x1316, 0x0000 पूर्ण,
	अणु 0x1318, 0x0000 पूर्ण,
	अणु 0x131a, 0x0000 पूर्ण,
	अणु 0x1322, 0x0029 पूर्ण,
	अणु 0x1323, 0x4a52 पूर्ण,
	अणु 0x1324, 0x002c पूर्ण,
	अणु 0x1325, 0x0b02 पूर्ण,
	अणु 0x1326, 0x002d पूर्ण,
	अणु 0x1327, 0x6b5a पूर्ण,
	अणु 0x1328, 0x002e पूर्ण,
	अणु 0x1329, 0xcbb2 पूर्ण,
	अणु 0x132a, 0x0030 पूर्ण,
	अणु 0x132b, 0x2c0b पूर्ण,
	अणु 0x1330, 0x0031 पूर्ण,
	अणु 0x1331, 0x8c63 पूर्ण,
	अणु 0x1332, 0x0032 पूर्ण,
	अणु 0x1333, 0xecbb पूर्ण,
	अणु 0x1334, 0x0034 पूर्ण,
	अणु 0x1335, 0x4d13 पूर्ण,
	अणु 0x1336, 0x0037 पूर्ण,
	अणु 0x1337, 0x0dc3 पूर्ण,
	अणु 0x1338, 0x003d पूर्ण,
	अणु 0x1339, 0xef7b पूर्ण,
	अणु 0x133a, 0x0044 पूर्ण,
	अणु 0x133b, 0xd134 पूर्ण,
	अणु 0x133c, 0x0047 पूर्ण,
	अणु 0x133d, 0x91e4 पूर्ण,
	अणु 0x133e, 0x004d पूर्ण,
	अणु 0x133f, 0xc370 पूर्ण,
	अणु 0x1340, 0x0053 पूर्ण,
	अणु 0x1341, 0xf4fd पूर्ण,
	अणु 0x1342, 0x0060 पूर्ण,
	अणु 0x1343, 0x5816 पूर्ण,
	अणु 0x1344, 0x006c पूर्ण,
	अणु 0x1345, 0xbb2e पूर्ण,
	अणु 0x1346, 0x0072 पूर्ण,
	अणु 0x1347, 0xecbb पूर्ण,
	अणु 0x1348, 0x0076 पूर्ण,
	अणु 0x1349, 0x5d97 पूर्ण,
पूर्ण;

अटल bool rt1015_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1015_RESET:
	हाल RT1015_CLK_DET:
	हाल RT1015_SIL_DET:
	हाल RT1015_VER_ID:
	हाल RT1015_VENDOR_ID:
	हाल RT1015_DEVICE_ID:
	हाल RT1015_PRO_ALT:
	हाल RT1015_MAN_I2C:
	हाल RT1015_DAC3:
	हाल RT1015_VBAT_TEST_OUT1:
	हाल RT1015_VBAT_TEST_OUT2:
	हाल RT1015_VBAT_PROT_ATT:
	हाल RT1015_VBAT_DET_CODE:
	हाल RT1015_SMART_BST_CTRL1:
	हाल RT1015_SPK_DC_DETECT1:
	हाल RT1015_SPK_DC_DETECT4:
	हाल RT1015_SPK_DC_DETECT5:
	हाल RT1015_DC_CALIB_CLSD1:
	हाल RT1015_DC_CALIB_CLSD5:
	हाल RT1015_DC_CALIB_CLSD6:
	हाल RT1015_DC_CALIB_CLSD7:
	हाल RT1015_DC_CALIB_CLSD8:
	हाल RT1015_S_BST_TIMING_INTER1:
	हाल RT1015_OSCK_STA:
	हाल RT1015_MONO_DYNA_CTRL1:
	हाल RT1015_MONO_DYNA_CTRL5:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt1015_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT1015_RESET:
	हाल RT1015_CLK2:
	हाल RT1015_CLK3:
	हाल RT1015_PLL1:
	हाल RT1015_PLL2:
	हाल RT1015_DUM_RW1:
	हाल RT1015_DUM_RW2:
	हाल RT1015_DUM_RW3:
	हाल RT1015_DUM_RW4:
	हाल RT1015_DUM_RW5:
	हाल RT1015_DUM_RW6:
	हाल RT1015_CLK_DET:
	हाल RT1015_SIL_DET:
	हाल RT1015_CUSTOMER_ID:
	हाल RT1015_PCODE_FWVER:
	हाल RT1015_VER_ID:
	हाल RT1015_VENDOR_ID:
	हाल RT1015_DEVICE_ID:
	हाल RT1015_PAD_DRV1:
	हाल RT1015_PAD_DRV2:
	हाल RT1015_GAT_BOOST:
	हाल RT1015_PRO_ALT:
	हाल RT1015_OSCK_STA:
	हाल RT1015_MAN_I2C:
	हाल RT1015_DAC1:
	हाल RT1015_DAC2:
	हाल RT1015_DAC3:
	हाल RT1015_ADC1:
	हाल RT1015_ADC2:
	हाल RT1015_TDM_MASTER:
	हाल RT1015_TDM_TCON:
	हाल RT1015_TDM1_1:
	हाल RT1015_TDM1_2:
	हाल RT1015_TDM1_3:
	हाल RT1015_TDM1_4:
	हाल RT1015_TDM1_5:
	हाल RT1015_MIXER1:
	हाल RT1015_MIXER2:
	हाल RT1015_ANA_PROTECT1:
	हाल RT1015_ANA_CTRL_SEQ1:
	हाल RT1015_ANA_CTRL_SEQ2:
	हाल RT1015_VBAT_DET_DEB:
	हाल RT1015_VBAT_VOLT_DET1:
	हाल RT1015_VBAT_VOLT_DET2:
	हाल RT1015_VBAT_TEST_OUT1:
	हाल RT1015_VBAT_TEST_OUT2:
	हाल RT1015_VBAT_PROT_ATT:
	हाल RT1015_VBAT_DET_CODE:
	हाल RT1015_PWR1:
	हाल RT1015_PWR4:
	हाल RT1015_PWR5:
	हाल RT1015_PWR6:
	हाल RT1015_PWR7:
	हाल RT1015_PWR8:
	हाल RT1015_PWR9:
	हाल RT1015_CLASSD_SEQ:
	हाल RT1015_SMART_BST_CTRL1:
	हाल RT1015_SMART_BST_CTRL2:
	हाल RT1015_ANA_CTRL1:
	हाल RT1015_ANA_CTRL2:
	हाल RT1015_PWR_STATE_CTRL:
	हाल RT1015_MONO_DYNA_CTRL:
	हाल RT1015_MONO_DYNA_CTRL1:
	हाल RT1015_MONO_DYNA_CTRL2:
	हाल RT1015_MONO_DYNA_CTRL3:
	हाल RT1015_MONO_DYNA_CTRL4:
	हाल RT1015_MONO_DYNA_CTRL5:
	हाल RT1015_SPK_VOL:
	हाल RT1015_SHORT_DETTOP1:
	हाल RT1015_SHORT_DETTOP2:
	हाल RT1015_SPK_DC_DETECT1:
	हाल RT1015_SPK_DC_DETECT2:
	हाल RT1015_SPK_DC_DETECT3:
	हाल RT1015_SPK_DC_DETECT4:
	हाल RT1015_SPK_DC_DETECT5:
	हाल RT1015_BAT_RPO_STEP1:
	हाल RT1015_BAT_RPO_STEP2:
	हाल RT1015_BAT_RPO_STEP3:
	हाल RT1015_BAT_RPO_STEP4:
	हाल RT1015_BAT_RPO_STEP5:
	हाल RT1015_BAT_RPO_STEP6:
	हाल RT1015_BAT_RPO_STEP7:
	हाल RT1015_BAT_RPO_STEP8:
	हाल RT1015_BAT_RPO_STEP9:
	हाल RT1015_BAT_RPO_STEP10:
	हाल RT1015_BAT_RPO_STEP11:
	हाल RT1015_BAT_RPO_STEP12:
	हाल RT1015_SPREAD_SPEC1:
	हाल RT1015_SPREAD_SPEC2:
	हाल RT1015_PAD_STATUS:
	हाल RT1015_PADS_PULLING_CTRL1:
	हाल RT1015_PADS_DRIVING:
	हाल RT1015_SYS_RST1:
	हाल RT1015_SYS_RST2:
	हाल RT1015_SYS_GATING1:
	हाल RT1015_TEST_MODE1:
	हाल RT1015_TEST_MODE2:
	हाल RT1015_TIMING_CTRL1:
	हाल RT1015_PLL_INT:
	हाल RT1015_TEST_OUT1:
	हाल RT1015_DC_CALIB_CLSD1:
	हाल RT1015_DC_CALIB_CLSD2:
	हाल RT1015_DC_CALIB_CLSD3:
	हाल RT1015_DC_CALIB_CLSD4:
	हाल RT1015_DC_CALIB_CLSD5:
	हाल RT1015_DC_CALIB_CLSD6:
	हाल RT1015_DC_CALIB_CLSD7:
	हाल RT1015_DC_CALIB_CLSD8:
	हाल RT1015_DC_CALIB_CLSD9:
	हाल RT1015_DC_CALIB_CLSD10:
	हाल RT1015_CLSD_INTERNAL1:
	हाल RT1015_CLSD_INTERNAL2:
	हाल RT1015_CLSD_INTERNAL3:
	हाल RT1015_CLSD_INTERNAL4:
	हाल RT1015_CLSD_INTERNAL5:
	हाल RT1015_CLSD_INTERNAL6:
	हाल RT1015_CLSD_INTERNAL7:
	हाल RT1015_CLSD_INTERNAL8:
	हाल RT1015_CLSD_INTERNAL9:
	हाल RT1015_CLSD_OCP_CTRL:
	हाल RT1015_VREF_LV:
	हाल RT1015_MBIAS1:
	हाल RT1015_MBIAS2:
	हाल RT1015_MBIAS3:
	हाल RT1015_MBIAS4:
	हाल RT1015_VREF_LV1:
	हाल RT1015_S_BST_TIMING_INTER1:
	हाल RT1015_S_BST_TIMING_INTER2:
	हाल RT1015_S_BST_TIMING_INTER3:
	हाल RT1015_S_BST_TIMING_INTER4:
	हाल RT1015_S_BST_TIMING_INTER5:
	हाल RT1015_S_BST_TIMING_INTER6:
	हाल RT1015_S_BST_TIMING_INTER7:
	हाल RT1015_S_BST_TIMING_INTER8:
	हाल RT1015_S_BST_TIMING_INTER9:
	हाल RT1015_S_BST_TIMING_INTER10:
	हाल RT1015_S_BST_TIMING_INTER11:
	हाल RT1015_S_BST_TIMING_INTER12:
	हाल RT1015_S_BST_TIMING_INTER13:
	हाल RT1015_S_BST_TIMING_INTER14:
	हाल RT1015_S_BST_TIMING_INTER15:
	हाल RT1015_S_BST_TIMING_INTER16:
	हाल RT1015_S_BST_TIMING_INTER17:
	हाल RT1015_S_BST_TIMING_INTER18:
	हाल RT1015_S_BST_TIMING_INTER19:
	हाल RT1015_S_BST_TIMING_INTER20:
	हाल RT1015_S_BST_TIMING_INTER21:
	हाल RT1015_S_BST_TIMING_INTER22:
	हाल RT1015_S_BST_TIMING_INTER23:
	हाल RT1015_S_BST_TIMING_INTER24:
	हाल RT1015_S_BST_TIMING_INTER25:
	हाल RT1015_S_BST_TIMING_INTER26:
	हाल RT1015_S_BST_TIMING_INTER27:
	हाल RT1015_S_BST_TIMING_INTER28:
	हाल RT1015_S_BST_TIMING_INTER29:
	हाल RT1015_S_BST_TIMING_INTER30:
	हाल RT1015_S_BST_TIMING_INTER31:
	हाल RT1015_S_BST_TIMING_INTER32:
	हाल RT1015_S_BST_TIMING_INTER33:
	हाल RT1015_S_BST_TIMING_INTER34:
	हाल RT1015_S_BST_TIMING_INTER35:
	हाल RT1015_S_BST_TIMING_INTER36:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -9525, 75, 0);

अटल स्थिर अक्षर * स्थिर rt1015_din_source_select[] = अणु
	"Left",
	"Right",
	"Left + Right average",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1015_mono_lr_sel, RT1015_PAD_DRV2, 4,
	rt1015_din_source_select);

अटल स्थिर अक्षर * स्थिर rt1015_boost_mode[] = अणु
	"Bypass", "Adaptive", "Fixed Adaptive"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rt1015_boost_mode_क्रमागत, 0, 0,
	rt1015_boost_mode);

अटल पूर्णांक rt1015_boost_mode_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1015_priv *rt1015 =
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt1015->boost_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_boost_mode_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1015_priv *rt1015 =
		snd_soc_component_get_drvdata(component);
	पूर्णांक boost_mode = ucontrol->value.पूर्णांकeger.value[0];

	चयन (boost_mode) अणु
	हाल BYPASS:
		snd_soc_component_update_bits(component,
			RT1015_SMART_BST_CTRL1, RT1015_ABST_AUTO_EN_MASK |
			RT1015_ABST_FIX_TGT_MASK | RT1015_BYPASS_SWR_REG_MASK,
			RT1015_ABST_REG_MODE | RT1015_ABST_FIX_TGT_DIS |
			RT1015_BYPASS_SWRREG_BYPASS);
		अवरोध;
	हाल ADAPTIVE:
		snd_soc_component_update_bits(component,
			RT1015_SMART_BST_CTRL1, RT1015_ABST_AUTO_EN_MASK |
			RT1015_ABST_FIX_TGT_MASK | RT1015_BYPASS_SWR_REG_MASK,
			RT1015_ABST_AUTO_MODE | RT1015_ABST_FIX_TGT_DIS |
			RT1015_BYPASS_SWRREG_PASS);
		अवरोध;
	हाल FIXED_ADAPTIVE:
		snd_soc_component_update_bits(component,
			RT1015_SMART_BST_CTRL1, RT1015_ABST_AUTO_EN_MASK |
			RT1015_ABST_FIX_TGT_MASK | RT1015_BYPASS_SWR_REG_MASK,
			RT1015_ABST_AUTO_MODE | RT1015_ABST_FIX_TGT_EN |
			RT1015_BYPASS_SWRREG_PASS);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown boost control.\n");
		वापस -EINVAL;
	पूर्ण

	rt1015->boost_mode = boost_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_bypass_boost_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1015_priv *rt1015 =
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = rt1015->bypass_boost;

	वापस 0;
पूर्ण

अटल व्योम rt1015_calibrate(काष्ठा rt1015_priv *rt1015)
अणु
	काष्ठा snd_soc_component *component = rt1015->component;
	काष्ठा regmap *regmap = rt1015->regmap;

	snd_soc_dapm_mutex_lock(&component->dapm);
	regcache_cache_bypass(regmap, true);

	regmap_ग_लिखो(regmap, RT1015_CLK_DET, 0x0000);
	regmap_ग_लिखो(regmap, RT1015_PWR4, 0x00B2);
	regmap_ग_लिखो(regmap, RT1015_PWR_STATE_CTRL, 0x0009);
	msleep(100);
	regmap_ग_लिखो(regmap, RT1015_PWR_STATE_CTRL, 0x000A);
	msleep(100);
	regmap_ग_लिखो(regmap, RT1015_PWR_STATE_CTRL, 0x000C);
	msleep(100);
	regmap_ग_लिखो(regmap, RT1015_CLSD_INTERNAL8, 0x2028);
	regmap_ग_लिखो(regmap, RT1015_CLSD_INTERNAL9, 0x0140);
	regmap_ग_लिखो(regmap, RT1015_PWR_STATE_CTRL, 0x000D);
	msleep(300);
	regmap_ग_लिखो(regmap, RT1015_PWR_STATE_CTRL, 0x0008);
	regmap_ग_लिखो(regmap, RT1015_SYS_RST1, 0x05F5);
	regmap_ग_लिखो(regmap, RT1015_CLK_DET, 0x8000);

	regcache_cache_bypass(regmap, false);
	regcache_mark_dirty(regmap);
	regcache_sync(regmap);
	snd_soc_dapm_mutex_unlock(&component->dapm);
पूर्ण

अटल पूर्णांक rt1015_bypass_boost_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा rt1015_priv *rt1015 =
		snd_soc_component_get_drvdata(component);

	अगर (rt1015->dac_is_used) अणु
		dev_err(component->dev, "DAC is being used!\n");
		वापस -EBUSY;
	पूर्ण

	rt1015->bypass_boost = ucontrol->value.पूर्णांकeger.value[0];
	अगर (rt1015->bypass_boost == RT1015_Bypass_Boost &&
			!rt1015->cali_करोne) अणु
		rt1015_calibrate(rt1015);
		rt1015->cali_करोne = 1;

		regmap_ग_लिखो(rt1015->regmap, RT1015_MONO_DYNA_CTRL, 0x0010);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt1015_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt1015_priv *rt1015 = container_of(work, काष्ठा rt1015_priv,
						flush_work.work);
	काष्ठा snd_soc_component *component = rt1015->component;
	अचिन्हित पूर्णांक val, i;

	क्रम (i = 0; i < 200; ++i) अणु
		usleep_range(1000, 1500);
		dev_dbg(component->dev, "Flush DAC (retry:%u)\n", i);
		regmap_पढ़ो(rt1015->regmap, RT1015_CLK_DET, &val);
		अगर (val & 0x800)
			अवरोध;
	पूर्ण

	regmap_ग_लिखो(rt1015->regmap, RT1015_SYS_RST1, 0x0597);
	regmap_ग_लिखो(rt1015->regmap, RT1015_SYS_RST1, 0x05f7);
	regmap_ग_लिखो(rt1015->regmap, RT1015_MAN_I2C, 0x0028);

	अगर (val & 0x800)
		dev_dbg(component->dev, "Flush DAC completed.\n");
	अन्यथा
		dev_warn(component->dev, "Fail to flush DAC data.\n");
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt1015_snd_controls[] = अणु
	SOC_SINGLE_TLV("DAC Playback Volume", RT1015_DAC1, RT1015_DAC_VOL_SFT,
		127, 0, dac_vol_tlv),
	SOC_DOUBLE("DAC Playback Switch", RT1015_DAC3,
		RT1015_DA_MUTE_SFT, RT1015_DVOL_MUTE_FLAG_SFT, 1, 1),
	SOC_ENUM_EXT("Boost Mode", rt1015_boost_mode_क्रमागत,
		rt1015_boost_mode_get, rt1015_boost_mode_put),
	SOC_ENUM("Mono LR Select", rt1015_mono_lr_sel),
	SOC_SINGLE_EXT("Bypass Boost", SND_SOC_NOPM, 0, 1, 0,
		rt1015_bypass_boost_get, rt1015_bypass_boost_put),
पूर्ण;

अटल पूर्णांक rt1015_is_sys_clk_from_pll(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);

	अगर (rt1015->sysclk_src == RT1015_SCLK_S_PLL)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक r1015_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		rt1015->dac_is_used = 1;
		अगर (rt1015->bypass_boost == RT1015_Enable_Boost) अणु
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST1, 0x05f7);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST2, 0x0b0a);
			snd_soc_component_ग_लिखो(component,
				RT1015_GAT_BOOST, 0xacfe);
			snd_soc_component_ग_लिखो(component,
				RT1015_PWR9, 0xaa00);
			snd_soc_component_ग_लिखो(component,
				RT1015_GAT_BOOST, 0xecfe);
		पूर्ण अन्यथा अणु
			snd_soc_component_ग_लिखो(component,
				0x032d, 0xaa60);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST1, 0x05f7);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST2, 0x0b0a);
			snd_soc_component_ग_लिखो(component,
				RT1015_PWR_STATE_CTRL, 0x008e);
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt1015->regmap, RT1015_MAN_I2C, 0x00a8);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		अगर (rt1015->bypass_boost == RT1015_Enable_Boost) अणु
			snd_soc_component_ग_लिखो(component,
				RT1015_PWR9, 0xa800);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST1, 0x05f5);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST2, 0x0b9a);
		पूर्ण अन्यथा अणु
			snd_soc_component_ग_लिखो(component,
				0x032d, 0xaa60);
			snd_soc_component_ग_लिखो(component,
				RT1015_PWR_STATE_CTRL, 0x0088);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST1, 0x05f5);
			snd_soc_component_ग_लिखो(component,
				RT1015_SYS_RST2, 0x0b9a);
		पूर्ण
		rt1015->dac_is_used = 0;

		cancel_delayed_work_sync(&rt1015->flush_work);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_amp_drv_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक ret, ret2;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = snd_soc_component_पढ़ो(component, RT1015_CLK_DET);
		ret2 = snd_soc_component_पढ़ो(component, RT1015_SPK_DC_DETECT1);
		अगर (!((ret >> 15) & 0x1)) अणु
			snd_soc_component_update_bits(component, RT1015_CLK_DET,
				RT1015_EN_BCLK_DET_MASK, RT1015_EN_BCLK_DET);
			dev_dbg(component->dev, "BCLK Detection Enabled.\n");
		पूर्ण
		अगर (!((ret2 >> 12) & 0x1)) अणु
			snd_soc_component_update_bits(component, RT1015_SPK_DC_DETECT1,
				RT1015_EN_CLA_D_DC_DET_MASK, RT1015_EN_CLA_D_DC_DET);
			dev_dbg(component->dev, "Class-D DC Detection Enabled.\n");
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (rt1015->hw_config == RT1015_HW_28)
			schedule_delayed_work(&rt1015->flush_work, msecs_to_jअगरfies(10));
		msleep(rt1015->pdata.घातer_up_delay_ms);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1015_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("PLL", RT1015_PWR1, RT1015_PWR_PLL_BIT, 0,
		शून्य, 0),
	SND_SOC_DAPM_AIF_IN("AIFRX", "AIF Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0,
		r1015_dac_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DRV_E("Amp Drv", SND_SOC_NOPM, 0, 0, शून्य, 0,
			rt1015_amp_drv_event, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPO"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1015_dapm_routes[] = अणु
	अणु "DAC", शून्य, "AIFRX" पूर्ण,
	अणु "DAC", शून्य, "PLL", rt1015_is_sys_clk_from_pllपूर्ण,
	अणु "Amp Drv", शून्य, "DAC" पूर्ण,
	अणु "SPO", शून्य, "Amp Drv" पूर्ण,
पूर्ण;

अटल पूर्णांक rt1015_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);
	पूर्णांक pre_भाग, bclk_ms, frame_size, lrck;
	अचिन्हित पूर्णांक val_len = 0;

	lrck = params_rate(params);
	pre_भाग = rl6231_get_clk_info(rt1015->sysclk, lrck);
	अगर (pre_भाग < 0) अणु
		dev_err(component->dev, "Unsupported clock rate\n");
		वापस -EINVAL;
	पूर्ण

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0) अणु
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		वापस -EINVAL;
	पूर्ण

	bclk_ms = frame_size > 32;

	dev_dbg(component->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_भाग, dai->id);

	dev_dbg(component->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				lrck, pre_भाग, dai->id);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val_len = RT1015_I2S_DL_20;
		अवरोध;
	हाल 24:
		val_len = RT1015_I2S_DL_24;
		अवरोध;
	हाल 8:
		val_len = RT1015_I2S_DL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1015_TDM_MASTER,
		RT1015_I2S_DL_MASK, val_len);
	snd_soc_component_update_bits(component, RT1015_CLK2,
		RT1015_FS_PD_MASK, pre_भाग << RT1015_FS_PD_SFT);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक reg_val = 0, reg_val2 = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		reg_val |= RT1015_TCON_TDM_MS_M;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		reg_val |= RT1015_TCON_TDM_MS_S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		reg_val2 |= RT1015_TDM_INV_BCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1015_I2S_M_DF_LEFT;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1015_I2S_M_DF_PCM_A;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1015_I2S_M_DF_PCM_B;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, RT1015_TDM_MASTER,
			RT1015_TCON_TDM_MS_MASK | RT1015_I2S_M_DF_MASK,
			reg_val);
	snd_soc_component_update_bits(component, RT1015_TDM1_1,
			RT1015_TDM_INV_BCLK_MASK, reg_val2);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_set_component_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg_val = 0;

	अगर (freq == rt1015->sysclk && clk_id == rt1015->sysclk_src)
		वापस 0;

	चयन (clk_id) अणु
	हाल RT1015_SCLK_S_MCLK:
		reg_val |= RT1015_CLK_SYS_PRE_SEL_MCLK;
		अवरोध;

	हाल RT1015_SCLK_S_PLL:
		reg_val |= RT1015_CLK_SYS_PRE_SEL_PLL;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	rt1015->sysclk = freq;
	rt1015->sysclk_src = clk_id;

	dev_dbg(component->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	snd_soc_component_update_bits(component, RT1015_CLK2,
			RT1015_CLK_SYS_PRE_SEL_MASK, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_set_component_pll(काष्ठा snd_soc_component *component,
		पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
		अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);
	काष्ठा rl6231_pll_code pll_code;
	पूर्णांक ret;

	अगर (!freq_in || !freq_out) अणु
		dev_dbg(component->dev, "PLL disabled\n");

		rt1015->pll_in = 0;
		rt1015->pll_out = 0;

		वापस 0;
	पूर्ण

	अगर (source == rt1015->pll_src && freq_in == rt1015->pll_in &&
		freq_out == rt1015->pll_out)
		वापस 0;

	चयन (source) अणु
	हाल RT1015_PLL_S_MCLK:
		snd_soc_component_update_bits(component, RT1015_CLK2,
			RT1015_PLL_SEL_MASK, RT1015_PLL_SEL_PLL_SRC2);
		अवरोध;

	हाल RT1015_PLL_S_BCLK:
		snd_soc_component_update_bits(component, RT1015_CLK2,
			RT1015_PLL_SEL_MASK, RT1015_PLL_SEL_BCLK);
		अवरोध;

	शेष:
		dev_err(component->dev, "Unknown PLL Source %d\n", source);
		वापस -EINVAL;
	पूर्ण

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_ग_लिखो(component, RT1015_PLL1,
		((pll_code.m_bp ? 0 : pll_code.m_code) << RT1015_PLL_M_SFT) |
		(pll_code.m_bp << RT1015_PLL_M_BP_SFT) |
		pll_code.n_code);
	snd_soc_component_ग_लिखो(component, RT1015_PLL2,
		pll_code.k_code);

	rt1015->pll_in = freq_in;
	rt1015->pll_out = freq_out;
	rt1015->pll_src = source;

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val = 0, rx_slotnum, tx_slotnum;
	पूर्णांक ret = 0, first_bit;

	चयन (slots) अणु
	हाल 2:
		val |= RT1015_I2S_TX_2CH;
		अवरोध;
	हाल 4:
		val |= RT1015_I2S_TX_4CH;
		अवरोध;
	हाल 6:
		val |= RT1015_I2S_TX_6CH;
		अवरोध;
	हाल 8:
		val |= RT1015_I2S_TX_8CH;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	चयन (slot_width) अणु
	हाल 16:
		val |= RT1015_I2S_CH_TX_LEN_16B;
		अवरोध;
	हाल 20:
		val |= RT1015_I2S_CH_TX_LEN_20B;
		अवरोध;
	हाल 24:
		val |= RT1015_I2S_CH_TX_LEN_24B;
		अवरोध;
	हाल 32:
		val |= RT1015_I2S_CH_TX_LEN_32B;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	/* Rx slot configuration */
	rx_slotnum = hweight_दीर्घ(rx_mask);
	अगर (rx_slotnum != 1) अणु
		ret = -EINVAL;
		dev_err(component->dev, "too many rx slots or zero slot\n");
		जाओ _set_tdm_err_;
	पूर्ण

	/* This is an assumption that the प्रणाली sends stereo audio to the amplअगरier typically.
	 * And the stereo audio is placed in slot 0/2/4/6 as the starting slot.
	 * The users could select the channel from L/R/L+R by "Mono LR Select" control.
	 */
	first_bit = __ffs(rx_mask);
	चयन (first_bit) अणु
	हाल 0:
	हाल 2:
	हाल 4:
	हाल 6:
		snd_soc_component_update_bits(component,
			RT1015_TDM1_4,
			RT1015_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1015_TDM_I2S_TX_R_DAC1_1_MASK,
			(first_bit << RT1015_TDM_I2S_TX_L_DAC1_1_SFT) |
			((first_bit+1) << RT1015_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	हाल 1:
	हाल 3:
	हाल 5:
	हाल 7:
		snd_soc_component_update_bits(component,
			RT1015_TDM1_4,
			RT1015_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1015_TDM_I2S_TX_R_DAC1_1_MASK,
			((first_bit-1) << RT1015_TDM_I2S_TX_L_DAC1_1_SFT) |
			(first_bit << RT1015_TDM_I2S_TX_R_DAC1_1_SFT));
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ _set_tdm_err_;
	पूर्ण

	/* Tx slot configuration */
	tx_slotnum = hweight_दीर्घ(tx_mask);
	अगर (tx_slotnum) अणु
		ret = -EINVAL;
		dev_err(component->dev, "doesn't need to support tx slots\n");
		जाओ _set_tdm_err_;
	पूर्ण

	snd_soc_component_update_bits(component, RT1015_TDM1_1,
		RT1015_I2S_CH_TX_MASK | RT1015_I2S_CH_RX_MASK |
		RT1015_I2S_CH_TX_LEN_MASK | RT1015_I2S_CH_RX_LEN_MASK, val);

_set_tdm_err_:
	वापस ret;
पूर्ण

अटल पूर्णांक rt1015_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1015_priv *rt1015 =
		snd_soc_component_get_drvdata(component);

	rt1015->component = component;
	INIT_DELAYED_WORK(&rt1015->flush_work, rt1015_flush_work);

	वापस 0;
पूर्ण

अटल व्योम rt1015_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&rt1015->flush_work);
	regmap_ग_लिखो(rt1015->regmap, RT1015_RESET, 0);
पूर्ण

#घोषणा RT1015_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा RT1015_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt1015_aअगर_dai_ops = अणु
	.hw_params = rt1015_hw_params,
	.set_fmt = rt1015_set_dai_fmt,
	.set_tdm_slot = rt1015_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1015_dai[] = अणु
	अणु
		.name = "rt1015-aif",
		.id = 0,
		.playback = अणु
			.stream_name = "AIF Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = RT1015_STEREO_RATES,
			.क्रमmats = RT1015_FORMATS,
		पूर्ण,
		.ops = &rt1015_aअगर_dai_ops,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1015_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1015->regmap, true);
	regcache_mark_dirty(rt1015->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt1015_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1015_priv *rt1015 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt1015->regmap, false);
	regcache_sync(rt1015->regmap);

	अगर (rt1015->cali_करोne)
		rt1015_calibrate(rt1015);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1015_suspend शून्य
#घोषणा rt1015_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt1015 = अणु
	.probe = rt1015_probe,
	.हटाओ = rt1015_हटाओ,
	.suspend = rt1015_suspend,
	.resume = rt1015_resume,
	.controls = rt1015_snd_controls,
	.num_controls = ARRAY_SIZE(rt1015_snd_controls),
	.dapm_widमाला_लो = rt1015_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt1015_dapm_widमाला_लो),
	.dapm_routes = rt1015_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(rt1015_dapm_routes),
	.set_sysclk = rt1015_set_component_sysclk,
	.set_pll = rt1015_set_component_pll,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt1015_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = RT1015_S_BST_TIMING_INTER36,
	.अस्थिर_reg = rt1015_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt1015_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt1015_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt1015_reg),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt1015_i2c_id[] = अणु
	अणु "rt1015", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt1015_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rt1015_of_match[] = अणु
	अणु .compatible = "realtek,rt1015", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1015_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1015_acpi_match[] = अणु
	अणु"10EC1015", 0,पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1015_acpi_match);
#पूर्ण_अगर

अटल व्योम rt1015_parse_dt(काष्ठा rt1015_priv *rt1015, काष्ठा device *dev)
अणु
	device_property_पढ़ो_u32(dev, "realtek,power-up-delay-ms",
		&rt1015->pdata.घातer_up_delay_ms);
पूर्ण

अटल पूर्णांक rt1015_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt1015_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt1015_priv *rt1015;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt1015 = devm_kzalloc(&i2c->dev, माप(*rt1015), GFP_KERNEL);
	अगर (!rt1015)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt1015);

	rt1015->pdata = i2s_शेष_platक्रमm_data;

	अगर (pdata)
		rt1015->pdata = *pdata;
	अन्यथा
		rt1015_parse_dt(rt1015, &i2c->dev);

	rt1015->regmap = devm_regmap_init_i2c(i2c, &rt1015_regmap);
	अगर (IS_ERR(rt1015->regmap)) अणु
		ret = PTR_ERR(rt1015->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	rt1015->hw_config = (i2c->addr == 0x29) ? RT1015_HW_29 : RT1015_HW_28;

	ret = regmap_पढ़ो(rt1015->regmap, RT1015_DEVICE_ID, &val);
	अगर (ret) अणु
		dev_err(&i2c->dev,
			"Failed to read device register: %d\n", ret);
		वापस ret;
	पूर्ण अन्यथा अगर ((val != RT1015_DEVICE_ID_VAL) &&
			(val != RT1015_DEVICE_ID_VAL2)) अणु
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1015\n", val);
		वापस -ENODEV;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
		&soc_component_dev_rt1015,
		rt1015_dai, ARRAY_SIZE(rt1015_dai));
पूर्ण

अटल व्योम rt1015_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt1015_priv *rt1015 = i2c_get_clientdata(client);

	regmap_ग_लिखो(rt1015->regmap, RT1015_RESET, 0);
पूर्ण

अटल काष्ठा i2c_driver rt1015_i2c_driver = अणु
	.driver = अणु
		.name = "rt1015",
		.of_match_table = of_match_ptr(rt1015_of_match),
		.acpi_match_table = ACPI_PTR(rt1015_acpi_match),
	पूर्ण,
	.probe = rt1015_i2c_probe,
	.shutकरोwn = rt1015_i2c_shutकरोwn,
	.id_table = rt1015_i2c_id,
पूर्ण;
module_i2c_driver(rt1015_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1015 driver");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
