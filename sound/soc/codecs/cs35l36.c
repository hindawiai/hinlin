<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// cs35l36.c -- CS35L36 ALSA SoC audio driver
//
// Copyright 2018 Cirrus Logic, Inc.
//
// Author: James Schulman <james.schulman@cirrus.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs35l36.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/completion.h>

#समावेश "cs35l36.h"

/*
 * Some fields take zero as a valid value so use a high bit flag that won't
 * get written to the device to mark those.
 */
#घोषणा CS35L36_VALID_PDATA 0x80000000

अटल स्थिर अक्षर * स्थिर cs35l36_supplies[] = अणु
	"VA",
	"VP",
पूर्ण;

काष्ठा  cs35l36_निजी अणु
	काष्ठा device *dev;
	काष्ठा cs35l36_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[2];
	पूर्णांक num_supplies;
	पूर्णांक clksrc;
	पूर्णांक chip_version;
	पूर्णांक rev_id;
	पूर्णांक ldm_mode_sel;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

काष्ठा cs35l36_pll_config अणु
	पूर्णांक freq;
	पूर्णांक clk_cfg;
	पूर्णांक fll_igain;
पूर्ण;

अटल स्थिर काष्ठा cs35l36_pll_config cs35l36_pll_sysclk[] = अणु
	अणु32768,		0x00, 0x05पूर्ण,
	अणु8000,		0x01, 0x03पूर्ण,
	अणु11025,		0x02, 0x03पूर्ण,
	अणु12000,		0x03, 0x03पूर्ण,
	अणु16000,		0x04, 0x04पूर्ण,
	अणु22050,		0x05, 0x04पूर्ण,
	अणु24000,		0x06, 0x04पूर्ण,
	अणु32000,		0x07, 0x05पूर्ण,
	अणु44100,		0x08, 0x05पूर्ण,
	अणु48000,		0x09, 0x05पूर्ण,
	अणु88200,		0x0A, 0x06पूर्ण,
	अणु96000,		0x0B, 0x06पूर्ण,
	अणु128000,	0x0C, 0x07पूर्ण,
	अणु176400,	0x0D, 0x07पूर्ण,
	अणु192000,	0x0E, 0x07पूर्ण,
	अणु256000,	0x0F, 0x08पूर्ण,
	अणु352800,	0x10, 0x08पूर्ण,
	अणु384000,	0x11, 0x08पूर्ण,
	अणु512000,	0x12, 0x09पूर्ण,
	अणु705600,	0x13, 0x09पूर्ण,
	अणु750000,	0x14, 0x09पूर्ण,
	अणु768000,	0x15, 0x09पूर्ण,
	अणु1000000,	0x16, 0x0Aपूर्ण,
	अणु1024000,	0x17, 0x0Aपूर्ण,
	अणु1200000,	0x18, 0x0Aपूर्ण,
	अणु1411200,	0x19, 0x0Aपूर्ण,
	अणु1500000,	0x1A, 0x0Aपूर्ण,
	अणु1536000,	0x1B, 0x0Aपूर्ण,
	अणु2000000,	0x1C, 0x0Aपूर्ण,
	अणु2048000,	0x1D, 0x0Aपूर्ण,
	अणु2400000,	0x1E, 0x0Aपूर्ण,
	अणु2822400,	0x1F, 0x0Aपूर्ण,
	अणु3000000,	0x20, 0x0Aपूर्ण,
	अणु3072000,	0x21, 0x0Aपूर्ण,
	अणु3200000,	0x22, 0x0Aपूर्ण,
	अणु4000000,	0x23, 0x0Aपूर्ण,
	अणु4096000,	0x24, 0x0Aपूर्ण,
	अणु4800000,	0x25, 0x0Aपूर्ण,
	अणु5644800,	0x26, 0x0Aपूर्ण,
	अणु6000000,	0x27, 0x0Aपूर्ण,
	अणु6144000,	0x28, 0x0Aपूर्ण,
	अणु6250000,	0x29, 0x08पूर्ण,
	अणु6400000,	0x2A, 0x0Aपूर्ण,
	अणु6500000,	0x2B, 0x08पूर्ण,
	अणु6750000,	0x2C, 0x09पूर्ण,
	अणु7526400,	0x2D, 0x0Aपूर्ण,
	अणु8000000,	0x2E, 0x0Aपूर्ण,
	अणु8192000,	0x2F, 0x0Aपूर्ण,
	अणु9600000,	0x30, 0x0Aपूर्ण,
	अणु11289600,	0x31, 0x0Aपूर्ण,
	अणु12000000,	0x32, 0x0Aपूर्ण,
	अणु12288000,	0x33, 0x0Aपूर्ण,
	अणु12500000,	0x34, 0x08पूर्ण,
	अणु12800000,	0x35, 0x0Aपूर्ण,
	अणु13000000,	0x36, 0x0Aपूर्ण,
	अणु13500000,	0x37, 0x0Aपूर्ण,
	अणु19200000,	0x38, 0x0Aपूर्ण,
	अणु22579200,	0x39, 0x0Aपूर्ण,
	अणु24000000,	0x3A, 0x0Aपूर्ण,
	अणु24576000,	0x3B, 0x0Aपूर्ण,
	अणु25000000,	0x3C, 0x0Aपूर्ण,
	अणु25600000,	0x3D, 0x0Aपूर्ण,
	अणु26000000,	0x3E, 0x0Aपूर्ण,
	अणु27000000,	0x3F, 0x0Aपूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष cs35l36_reg[] = अणु
	अणुCS35L36_TESTKEY_CTRL,			0x00000000पूर्ण,
	अणुCS35L36_USERKEY_CTL,			0x00000000पूर्ण,
	अणुCS35L36_OTP_CTRL1,			0x00002460पूर्ण,
	अणुCS35L36_OTP_CTRL2,			0x00000000पूर्ण,
	अणुCS35L36_OTP_CTRL3,			0x00000000पूर्ण,
	अणुCS35L36_OTP_CTRL4,			0x00000000पूर्ण,
	अणुCS35L36_OTP_CTRL5,			0x00000000पूर्ण,
	अणुCS35L36_PAC_CTL1,			0x00000004पूर्ण,
	अणुCS35L36_PAC_CTL2,			0x00000000पूर्ण,
	अणुCS35L36_PAC_CTL3,			0x00000000पूर्ण,
	अणुCS35L36_PWR_CTRL1,			0x00000000पूर्ण,
	अणुCS35L36_PWR_CTRL2,			0x00003321पूर्ण,
	अणुCS35L36_PWR_CTRL3,			0x01000010पूर्ण,
	अणुCS35L36_CTRL_OVRRIDE,			0x00000002पूर्ण,
	अणुCS35L36_AMP_OUT_MUTE,			0x00000000पूर्ण,
	अणुCS35L36_OTP_TRIM_STATUS,		0x00000000पूर्ण,
	अणुCS35L36_DISCH_FILT,			0x00000000पूर्ण,
	अणुCS35L36_PROTECT_REL_ERR,		0x00000000पूर्ण,
	अणुCS35L36_PAD_INTERFACE,			0x00000038पूर्ण,
	अणुCS35L36_PLL_CLK_CTRL,			0x00000010पूर्ण,
	अणुCS35L36_GLOBAL_CLK_CTRL,		0x00000003पूर्ण,
	अणुCS35L36_ADC_CLK_CTRL,			0x00000000पूर्ण,
	अणुCS35L36_SWIRE_CLK_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_SP_SCLK_CLK_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_EN,			0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_TX_ID,			0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_PWR_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_DATA_TX,		0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_TX_STATUS,		0x00000002पूर्ण,
	अणुCS35L36_MDSYNC_RX_STATUS,		0x00000000पूर्ण,
	अणुCS35L36_MDSYNC_ERR_STATUS,		0x00000000पूर्ण,
	अणुCS35L36_BSTCVRT_VCTRL1,		0x00000000पूर्ण,
	अणुCS35L36_BSTCVRT_VCTRL2,		0x00000001पूर्ण,
	अणुCS35L36_BSTCVRT_PEAK_CUR,		0x0000004Aपूर्ण,
	अणुCS35L36_BSTCVRT_SFT_RAMP,		0x00000003पूर्ण,
	अणुCS35L36_BSTCVRT_COEFF,			0x00002424पूर्ण,
	अणुCS35L36_BSTCVRT_SLOPE_LBST,		0x00005800पूर्ण,
	अणुCS35L36_BSTCVRT_SW_FREQ,		0x00010000पूर्ण,
	अणुCS35L36_BSTCVRT_DCM_CTRL,		0x00002001पूर्ण,
	अणुCS35L36_BSTCVRT_DCM_MODE_FORCE,	0x00000000पूर्ण,
	अणुCS35L36_BSTCVRT_OVERVOLT_CTRL,		0x00000130पूर्ण,
	अणुCS35L36_VPI_LIMIT_MODE,		0x00000000पूर्ण,
	अणुCS35L36_VPI_LIMIT_MINMAX,		0x00003000पूर्ण,
	अणुCS35L36_VPI_VP_THLD,			0x00101010पूर्ण,
	अणुCS35L36_VPI_TRACK_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_VPI_TRIG_MODE_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_VPI_TRIG_STEPS,		0x00000000पूर्ण,
	अणुCS35L36_VI_SPKMON_FILT,		0x00000003पूर्ण,
	अणुCS35L36_VI_SPKMON_GAIN,		0x00000909पूर्ण,
	अणुCS35L36_VI_SPKMON_IP_SEL,		0x00000000पूर्ण,
	अणुCS35L36_DTEMP_WARN_THLD,		0x00000002पूर्ण,
	अणुCS35L36_DTEMP_STATUS,			0x00000000पूर्ण,
	अणुCS35L36_VPVBST_FS_SEL,			0x00000001पूर्ण,
	अणुCS35L36_VPVBST_VP_CTRL,		0x000001C0पूर्ण,
	अणुCS35L36_VPVBST_VBST_CTRL,		0x000001C0पूर्ण,
	अणुCS35L36_ASP_TX_PIN_CTRL,		0x00000028पूर्ण,
	अणुCS35L36_ASP_RATE_CTRL,			0x00090000पूर्ण,
	अणुCS35L36_ASP_FORMAT,			0x00000002पूर्ण,
	अणुCS35L36_ASP_FRAME_CTRL,		0x00180018पूर्ण,
	अणुCS35L36_ASP_TX1_TX2_SLOT,		0x00010000पूर्ण,
	अणुCS35L36_ASP_TX3_TX4_SLOT,		0x00030002पूर्ण,
	अणुCS35L36_ASP_TX5_TX6_SLOT,		0x00050004पूर्ण,
	अणुCS35L36_ASP_TX7_TX8_SLOT,		0x00070006पूर्ण,
	अणुCS35L36_ASP_RX1_SLOT,			0x00000000पूर्ण,
	अणुCS35L36_ASP_RX_TX_EN,			0x00000000पूर्ण,
	अणुCS35L36_ASP_RX1_SEL,			0x00000008पूर्ण,
	अणुCS35L36_ASP_TX1_SEL,			0x00000018पूर्ण,
	अणुCS35L36_ASP_TX2_SEL,			0x00000019पूर्ण,
	अणुCS35L36_ASP_TX3_SEL,			0x00000028पूर्ण,
	अणुCS35L36_ASP_TX4_SEL,			0x00000029पूर्ण,
	अणुCS35L36_ASP_TX5_SEL,			0x00000020पूर्ण,
	अणुCS35L36_ASP_TX6_SEL,			0x00000000पूर्ण,
	अणुCS35L36_SWIRE_P1_TX1_SEL,		0x00000018पूर्ण,
	अणुCS35L36_SWIRE_P1_TX2_SEL,		0x00000019पूर्ण,
	अणुCS35L36_SWIRE_P2_TX1_SEL,		0x00000028पूर्ण,
	अणुCS35L36_SWIRE_P2_TX2_SEL,		0x00000029पूर्ण,
	अणुCS35L36_SWIRE_P2_TX3_SEL,		0x00000020पूर्ण,
	अणुCS35L36_SWIRE_DP1_FIFO_CFG,		0x0000001Bपूर्ण,
	अणुCS35L36_SWIRE_DP2_FIFO_CFG,		0x0000001Bपूर्ण,
	अणुCS35L36_SWIRE_DP3_FIFO_CFG,		0x0000001Bपूर्ण,
	अणुCS35L36_SWIRE_PCM_RX_DATA,		0x00000000पूर्ण,
	अणुCS35L36_SWIRE_FS_SEL,			0x00000001पूर्ण,
	अणुCS35L36_AMP_DIG_VOL_CTRL,		0x00008000पूर्ण,
	अणुCS35L36_VPBR_CFG,			0x02AA1905पूर्ण,
	अणुCS35L36_VBBR_CFG,			0x02AA1905पूर्ण,
	अणुCS35L36_VPBR_STATUS,			0x00000000पूर्ण,
	अणुCS35L36_VBBR_STATUS,			0x00000000पूर्ण,
	अणुCS35L36_OVERTEMP_CFG,			0x00000001पूर्ण,
	अणुCS35L36_AMP_ERR_VOL,			0x00000000पूर्ण,
	अणुCS35L36_CLASSH_CFG,			0x000B0405पूर्ण,
	अणुCS35L36_CLASSH_FET_DRV_CFG,		0x00000111पूर्ण,
	अणुCS35L36_NG_CFG,			0x00000033पूर्ण,
	अणुCS35L36_AMP_GAIN_CTRL,			0x00000273पूर्ण,
	अणुCS35L36_PWM_MOD_IO_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_PWM_MOD_STATUS,		0x00000000पूर्ण,
	अणुCS35L36_DAC_MSM_CFG,			0x00000000पूर्ण,
	अणुCS35L36_AMP_SLOPE_CTRL,		0x00000B00पूर्ण,
	अणुCS35L36_AMP_PDM_VOLUME,		0x00000000पूर्ण,
	अणुCS35L36_AMP_PDM_RATE_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_PDM_CH_SEL,			0x00000000पूर्ण,
	अणुCS35L36_AMP_NG_CTRL,			0x0000212Fपूर्ण,
	अणुCS35L36_PDM_HIGHFILT_CTRL,		0x00000000पूर्ण,
	अणुCS35L36_PAC_INT0_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT1_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT2_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT3_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT4_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT5_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT6_CTRL,			0x00000001पूर्ण,
	अणुCS35L36_PAC_INT7_CTRL,			0x00000001पूर्ण,
पूर्ण;

अटल bool cs35l36_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L36_SW_RESET:
	हाल CS35L36_SW_REV:
	हाल CS35L36_HW_REV:
	हाल CS35L36_TESTKEY_CTRL:
	हाल CS35L36_USERKEY_CTL:
	हाल CS35L36_OTP_MEM30:
	हाल CS35L36_OTP_CTRL1:
	हाल CS35L36_OTP_CTRL2:
	हाल CS35L36_OTP_CTRL3:
	हाल CS35L36_OTP_CTRL4:
	हाल CS35L36_OTP_CTRL5:
	हाल CS35L36_PAC_CTL1:
	हाल CS35L36_PAC_CTL2:
	हाल CS35L36_PAC_CTL3:
	हाल CS35L36_DEVICE_ID:
	हाल CS35L36_FAB_ID:
	हाल CS35L36_REV_ID:
	हाल CS35L36_PWR_CTRL1:
	हाल CS35L36_PWR_CTRL2:
	हाल CS35L36_PWR_CTRL3:
	हाल CS35L36_CTRL_OVRRIDE:
	हाल CS35L36_AMP_OUT_MUTE:
	हाल CS35L36_OTP_TRIM_STATUS:
	हाल CS35L36_DISCH_FILT:
	हाल CS35L36_PROTECT_REL_ERR:
	हाल CS35L36_PAD_INTERFACE:
	हाल CS35L36_PLL_CLK_CTRL:
	हाल CS35L36_GLOBAL_CLK_CTRL:
	हाल CS35L36_ADC_CLK_CTRL:
	हाल CS35L36_SWIRE_CLK_CTRL:
	हाल CS35L36_SP_SCLK_CLK_CTRL:
	हाल CS35L36_TST_FS_MON0:
	हाल CS35L36_MDSYNC_EN:
	हाल CS35L36_MDSYNC_TX_ID:
	हाल CS35L36_MDSYNC_PWR_CTRL:
	हाल CS35L36_MDSYNC_DATA_TX:
	हाल CS35L36_MDSYNC_TX_STATUS:
	हाल CS35L36_MDSYNC_RX_STATUS:
	हाल CS35L36_MDSYNC_ERR_STATUS:
	हाल CS35L36_BSTCVRT_VCTRL1:
	हाल CS35L36_BSTCVRT_VCTRL2:
	हाल CS35L36_BSTCVRT_PEAK_CUR:
	हाल CS35L36_BSTCVRT_SFT_RAMP:
	हाल CS35L36_BSTCVRT_COEFF:
	हाल CS35L36_BSTCVRT_SLOPE_LBST:
	हाल CS35L36_BSTCVRT_SW_FREQ:
	हाल CS35L36_BSTCVRT_DCM_CTRL:
	हाल CS35L36_BSTCVRT_DCM_MODE_FORCE:
	हाल CS35L36_BSTCVRT_OVERVOLT_CTRL:
	हाल CS35L36_BST_TST_MANUAL:
	हाल CS35L36_BST_ANA2_TEST:
	हाल CS35L36_VPI_LIMIT_MODE:
	हाल CS35L36_VPI_LIMIT_MINMAX:
	हाल CS35L36_VPI_VP_THLD:
	हाल CS35L36_VPI_TRACK_CTRL:
	हाल CS35L36_VPI_TRIG_MODE_CTRL:
	हाल CS35L36_VPI_TRIG_STEPS:
	हाल CS35L36_VI_SPKMON_FILT:
	हाल CS35L36_VI_SPKMON_GAIN:
	हाल CS35L36_VI_SPKMON_IP_SEL:
	हाल CS35L36_DTEMP_WARN_THLD:
	हाल CS35L36_DTEMP_STATUS:
	हाल CS35L36_VPVBST_FS_SEL:
	हाल CS35L36_VPVBST_VP_CTRL:
	हाल CS35L36_VPVBST_VBST_CTRL:
	हाल CS35L36_ASP_TX_PIN_CTRL:
	हाल CS35L36_ASP_RATE_CTRL:
	हाल CS35L36_ASP_FORMAT:
	हाल CS35L36_ASP_FRAME_CTRL:
	हाल CS35L36_ASP_TX1_TX2_SLOT:
	हाल CS35L36_ASP_TX3_TX4_SLOT:
	हाल CS35L36_ASP_TX5_TX6_SLOT:
	हाल CS35L36_ASP_TX7_TX8_SLOT:
	हाल CS35L36_ASP_RX1_SLOT:
	हाल CS35L36_ASP_RX_TX_EN:
	हाल CS35L36_ASP_RX1_SEL:
	हाल CS35L36_ASP_TX1_SEL:
	हाल CS35L36_ASP_TX2_SEL:
	हाल CS35L36_ASP_TX3_SEL:
	हाल CS35L36_ASP_TX4_SEL:
	हाल CS35L36_ASP_TX5_SEL:
	हाल CS35L36_ASP_TX6_SEL:
	हाल CS35L36_SWIRE_P1_TX1_SEL:
	हाल CS35L36_SWIRE_P1_TX2_SEL:
	हाल CS35L36_SWIRE_P2_TX1_SEL:
	हाल CS35L36_SWIRE_P2_TX2_SEL:
	हाल CS35L36_SWIRE_P2_TX3_SEL:
	हाल CS35L36_SWIRE_DP1_FIFO_CFG:
	हाल CS35L36_SWIRE_DP2_FIFO_CFG:
	हाल CS35L36_SWIRE_DP3_FIFO_CFG:
	हाल CS35L36_SWIRE_PCM_RX_DATA:
	हाल CS35L36_SWIRE_FS_SEL:
	हाल CS35L36_AMP_DIG_VOL_CTRL:
	हाल CS35L36_VPBR_CFG:
	हाल CS35L36_VBBR_CFG:
	हाल CS35L36_VPBR_STATUS:
	हाल CS35L36_VBBR_STATUS:
	हाल CS35L36_OVERTEMP_CFG:
	हाल CS35L36_AMP_ERR_VOL:
	हाल CS35L36_CLASSH_CFG:
	हाल CS35L36_CLASSH_FET_DRV_CFG:
	हाल CS35L36_NG_CFG:
	हाल CS35L36_AMP_GAIN_CTRL:
	हाल CS35L36_PWM_MOD_IO_CTRL:
	हाल CS35L36_PWM_MOD_STATUS:
	हाल CS35L36_DAC_MSM_CFG:
	हाल CS35L36_AMP_SLOPE_CTRL:
	हाल CS35L36_AMP_PDM_VOLUME:
	हाल CS35L36_AMP_PDM_RATE_CTRL:
	हाल CS35L36_PDM_CH_SEL:
	हाल CS35L36_AMP_NG_CTRL:
	हाल CS35L36_PDM_HIGHFILT_CTRL:
	हाल CS35L36_INT1_STATUS:
	हाल CS35L36_INT2_STATUS:
	हाल CS35L36_INT3_STATUS:
	हाल CS35L36_INT4_STATUS:
	हाल CS35L36_INT1_RAW_STATUS:
	हाल CS35L36_INT2_RAW_STATUS:
	हाल CS35L36_INT3_RAW_STATUS:
	हाल CS35L36_INT4_RAW_STATUS:
	हाल CS35L36_INT1_MASK:
	हाल CS35L36_INT2_MASK:
	हाल CS35L36_INT3_MASK:
	हाल CS35L36_INT4_MASK:
	हाल CS35L36_INT1_EDGE_LVL_CTRL:
	हाल CS35L36_INT3_EDGE_LVL_CTRL:
	हाल CS35L36_PAC_INT_STATUS:
	हाल CS35L36_PAC_INT_RAW_STATUS:
	हाल CS35L36_PAC_INT_FLUSH_CTRL:
	हाल CS35L36_PAC_INT0_CTRL:
	हाल CS35L36_PAC_INT1_CTRL:
	हाल CS35L36_PAC_INT2_CTRL:
	हाल CS35L36_PAC_INT3_CTRL:
	हाल CS35L36_PAC_INT4_CTRL:
	हाल CS35L36_PAC_INT5_CTRL:
	हाल CS35L36_PAC_INT6_CTRL:
	हाल CS35L36_PAC_INT7_CTRL:
		वापस true;
	शेष:
		अगर (reg >= CS35L36_PAC_PMEM_WORD0 &&
			reg <= CS35L36_PAC_PMEM_WORD1023)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l36_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L36_TESTKEY_CTRL:
	हाल CS35L36_USERKEY_CTL:
	हाल CS35L36_TST_FS_MON0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l36_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L36_SW_RESET:
	हाल CS35L36_SW_REV:
	हाल CS35L36_HW_REV:
	हाल CS35L36_TESTKEY_CTRL:
	हाल CS35L36_USERKEY_CTL:
	हाल CS35L36_DEVICE_ID:
	हाल CS35L36_FAB_ID:
	हाल CS35L36_REV_ID:
	हाल CS35L36_INT1_STATUS:
	हाल CS35L36_INT2_STATUS:
	हाल CS35L36_INT3_STATUS:
	हाल CS35L36_INT4_STATUS:
	हाल CS35L36_INT1_RAW_STATUS:
	हाल CS35L36_INT2_RAW_STATUS:
	हाल CS35L36_INT3_RAW_STATUS:
	हाल CS35L36_INT4_RAW_STATUS:
	हाल CS35L36_INT1_MASK:
	हाल CS35L36_INT2_MASK:
	हाल CS35L36_INT3_MASK:
	हाल CS35L36_INT4_MASK:
	हाल CS35L36_INT1_EDGE_LVL_CTRL:
	हाल CS35L36_INT3_EDGE_LVL_CTRL:
	हाल CS35L36_PAC_INT_STATUS:
	हाल CS35L36_PAC_INT_RAW_STATUS:
	हाल CS35L36_PAC_INT_FLUSH_CTRL:
		वापस true;
	शेष:
		अगर (reg >= CS35L36_PAC_PMEM_WORD0 &&
			reg <= CS35L36_PAC_PMEM_WORD1023)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(dig_vol_tlv, -10200, 25, 0);
अटल DECLARE_TLV_DB_SCALE(amp_gain_tlv, 0, 1, 1);

अटल स्थिर अक्षर * स्थिर cs35l36_pcm_sftramp_text[] =  अणु
	"Off", ".5ms", "1ms", "2ms", "4ms", "8ms", "15ms", "30ms"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm_sft_ramp, CS35L36_AMP_DIG_VOL_CTRL, 0,
			    cs35l36_pcm_sftramp_text);

अटल पूर्णांक cs35l36_ldm_sel_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = cs35l36->ldm_mode_sel;

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_ldm_sel_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);
	पूर्णांक val = (ucontrol->value.पूर्णांकeger.value[0]) ? CS35L36_NG_AMP_EN_MASK :
						       0;

	cs35l36->ldm_mode_sel = val;

	regmap_update_bits(cs35l36->regmap, CS35L36_NG_CFG,
			   CS35L36_NG_AMP_EN_MASK, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cs35l36_aud_controls[] = अणु
	SOC_SINGLE_SX_TLV("Digital PCM Volume", CS35L36_AMP_DIG_VOL_CTRL,
		3, 0x4D0, 0x390, dig_vol_tlv),
	SOC_SINGLE_TLV("Analog PCM Volume", CS35L36_AMP_GAIN_CTRL, 5, 0x13, 0,
		amp_gain_tlv),
	SOC_ENUM("PCM Soft Ramp", pcm_sft_ramp),
	SOC_SINGLE("Amp Gain Zero-Cross Switch", CS35L36_AMP_GAIN_CTRL,
		CS35L36_AMP_ZC_SHIFT, 1, 0),
	SOC_SINGLE("PDM LDM Enter Ramp Switch", CS35L36_DAC_MSM_CFG,
		CS35L36_PDM_LDM_ENTER_SHIFT, 1, 0),
	SOC_SINGLE("PDM LDM Exit Ramp Switch", CS35L36_DAC_MSM_CFG,
		CS35L36_PDM_LDM_EXIT_SHIFT, 1, 0),
	SOC_SINGLE_BOOL_EXT("LDM Select Switch", 0, cs35l36_ldm_sel_get,
		cs35l36_ldm_sel_put),
पूर्ण;

अटल पूर्णांक cs35l36_मुख्य_amp_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);
	u32 reg;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL1,
				   CS35L36_GLOBAL_EN_MASK,
				   1 << CS35L36_GLOBAL_EN_SHIFT);

		usleep_range(2000, 2100);

		regmap_पढ़ो(cs35l36->regmap, CS35L36_INT4_RAW_STATUS, &reg);

		अगर (WARN_ON_ONCE(reg & CS35L36_PLL_UNLOCK_MASK))
			dev_crit(cs35l36->dev, "PLL Unlocked\n");

		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RX1_SEL,
				   CS35L36_PCM_RX_SEL_MASK,
				   CS35L36_PCM_RX_SEL_PCM);
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_OUT_MUTE,
				   CS35L36_AMP_MUTE_MASK,
				   0 << CS35L36_AMP_MUTE_SHIFT);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RX1_SEL,
				   CS35L36_PCM_RX_SEL_MASK,
				   CS35L36_PCM_RX_SEL_ZERO);
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_OUT_MUTE,
				   CS35L36_AMP_MUTE_MASK,
				   1 << CS35L36_AMP_MUTE_SHIFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL1,
				   CS35L36_GLOBAL_EN_MASK,
				   0 << CS35L36_GLOBAL_EN_SHIFT);

		usleep_range(2000, 2100);
		अवरोध;
	शेष:
		dev_dbg(component->dev, "Invalid event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_boost_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (!cs35l36->pdata.बाह्य_boost)
			regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL2,
					   CS35L36_BST_EN_MASK,
					   CS35L36_BST_EN <<
					   CS35L36_BST_EN_SHIFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (!cs35l36->pdata.बाह्य_boost)
			regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL2,
					   CS35L36_BST_EN_MASK,
					   CS35L36_BST_DIS_VP <<
					   CS35L36_BST_EN_SHIFT);
		अवरोध;
	शेष:
		dev_dbg(component->dev, "Invalid event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर cs35l36_chan_text[] = अणु
	"RX1",
	"RX2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(chansel_क्रमागत, CS35L36_ASP_RX1_SLOT, 0,
			    cs35l36_chan_text);

अटल स्थिर काष्ठा snd_kcontrol_new cs35l36_chan_mux =
		SOC_DAPM_ENUM("Input Mux", chansel_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new amp_enable_ctrl =
		SOC_DAPM_SINGLE_AUTODISABLE("Switch", CS35L36_AMP_OUT_MUTE,
					    CS35L36_AMP_MUTE_SHIFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new boost_ctrl =
		SOC_DAPM_SINGLE_VIRT("Switch", 1);

अटल स्थिर अक्षर * स्थिर asp_tx_src_text[] = अणु
	"Zero Fill", "ASPRX1", "VMON", "IMON", "ERRVOL", "VPMON", "VBSTMON"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक asp_tx_src_values[] = अणु
	0x00, 0x08, 0x18, 0x19, 0x20, 0x28, 0x29
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx1_src_क्रमागत, CS35L36_ASP_TX1_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx1_src =
		SOC_DAPM_ENUM("ASPTX1SRC", asp_tx1_src_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx2_src_क्रमागत, CS35L36_ASP_TX2_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx2_src =
		SOC_DAPM_ENUM("ASPTX2SRC", asp_tx2_src_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx3_src_क्रमागत, CS35L36_ASP_TX3_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx3_src =
		SOC_DAPM_ENUM("ASPTX3SRC", asp_tx3_src_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx4_src_क्रमागत, CS35L36_ASP_TX4_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx4_src =
		SOC_DAPM_ENUM("ASPTX4SRC", asp_tx4_src_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx5_src_क्रमागत, CS35L36_ASP_TX5_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx5_src =
		SOC_DAPM_ENUM("ASPTX5SRC", asp_tx5_src_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(asp_tx6_src_क्रमागत, CS35L36_ASP_TX6_SEL, 0,
				  CS35L36_APS_TX_SEL_MASK, asp_tx_src_text,
				  asp_tx_src_values);

अटल स्थिर काष्ठा snd_kcontrol_new asp_tx6_src =
		SOC_DAPM_ENUM("ASPTX6SRC", asp_tx6_src_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget cs35l36_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Channel Mux", SND_SOC_NOPM, 0, 0, &cs35l36_chan_mux),
	SND_SOC_DAPM_AIF_IN("SDIN", शून्य, 0, CS35L36_ASP_RX_TX_EN, 16, 0),

	SND_SOC_DAPM_OUT_DRV_E("Main AMP", CS35L36_PWR_CTRL2, 0, 0, शून्य, 0,
			       cs35l36_मुख्य_amp_event, SND_SOC_DAPM_POST_PMD |
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_SWITCH("AMP Enable", SND_SOC_NOPM, 0, 1, &amp_enable_ctrl),
	SND_SOC_DAPM_MIXER("CLASS H", CS35L36_PWR_CTRL3, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH_E("BOOST Enable", SND_SOC_NOPM, 0, 0, &boost_ctrl,
			      cs35l36_boost_event, SND_SOC_DAPM_POST_PMD |
			      SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_AIF_OUT("ASPTX1", शून्य, 0, CS35L36_ASP_RX_TX_EN, 0, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX2", शून्य, 1, CS35L36_ASP_RX_TX_EN, 1, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX3", शून्य, 2, CS35L36_ASP_RX_TX_EN, 2, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX4", शून्य, 3, CS35L36_ASP_RX_TX_EN, 3, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX5", शून्य, 4, CS35L36_ASP_RX_TX_EN, 4, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX6", शून्य, 5, CS35L36_ASP_RX_TX_EN, 5, 0),

	SND_SOC_DAPM_MUX("ASPTX1SRC", SND_SOC_NOPM, 0, 0, &asp_tx1_src),
	SND_SOC_DAPM_MUX("ASPTX2SRC", SND_SOC_NOPM, 0, 0, &asp_tx2_src),
	SND_SOC_DAPM_MUX("ASPTX3SRC", SND_SOC_NOPM, 0, 0, &asp_tx3_src),
	SND_SOC_DAPM_MUX("ASPTX4SRC", SND_SOC_NOPM, 0, 0, &asp_tx4_src),
	SND_SOC_DAPM_MUX("ASPTX5SRC", SND_SOC_NOPM, 0, 0, &asp_tx5_src),
	SND_SOC_DAPM_MUX("ASPTX6SRC", SND_SOC_NOPM, 0, 0, &asp_tx6_src),

	SND_SOC_DAPM_ADC("VMON ADC", शून्य, CS35L36_PWR_CTRL2, 12, 0),
	SND_SOC_DAPM_ADC("IMON ADC", शून्य, CS35L36_PWR_CTRL2, 13, 0),
	SND_SOC_DAPM_ADC("VPMON ADC", शून्य, CS35L36_PWR_CTRL2, 8, 0),
	SND_SOC_DAPM_ADC("VBSTMON ADC", शून्य, CS35L36_PWR_CTRL2, 9, 0),

	SND_SOC_DAPM_INPUT("VP"),
	SND_SOC_DAPM_INPUT("VBST"),
	SND_SOC_DAPM_INPUT("VSENSE"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l36_audio_map[] = अणु
	अणु"VPMON ADC", शून्य, "VP"पूर्ण,
	अणु"VBSTMON ADC", शून्य, "VBST"पूर्ण,
	अणु"IMON ADC", शून्य, "VSENSE"पूर्ण,
	अणु"VMON ADC", शून्य, "VSENSE"पूर्ण,

	अणु"ASPTX1SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX1SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX1SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX1SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX2SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX2SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX2SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX2SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX3SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX3SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX3SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX3SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX4SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX4SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX4SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX4SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX5SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX5SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX5SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX5SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX6SRC", "IMON", "IMON ADC"पूर्ण,
	अणु"ASPTX6SRC", "VMON", "VMON ADC"पूर्ण,
	अणु"ASPTX6SRC", "VBSTMON", "VBSTMON ADC"पूर्ण,
	अणु"ASPTX6SRC", "VPMON", "VPMON ADC"पूर्ण,

	अणु"ASPTX1", शून्य, "ASPTX1SRC"पूर्ण,
	अणु"ASPTX2", शून्य, "ASPTX2SRC"पूर्ण,
	अणु"ASPTX3", शून्य, "ASPTX3SRC"पूर्ण,
	अणु"ASPTX4", शून्य, "ASPTX4SRC"पूर्ण,
	अणु"ASPTX5", शून्य, "ASPTX5SRC"पूर्ण,
	अणु"ASPTX6", शून्य, "ASPTX6SRC"पूर्ण,

	अणु"AMP Capture", शून्य, "ASPTX1"पूर्ण,
	अणु"AMP Capture", शून्य, "ASPTX2"पूर्ण,
	अणु"AMP Capture", शून्य, "ASPTX3"पूर्ण,
	अणु"AMP Capture", शून्य, "ASPTX4"पूर्ण,
	अणु"AMP Capture", शून्य, "ASPTX5"पूर्ण,
	अणु"AMP Capture", शून्य, "ASPTX6"पूर्ण,

	अणु"AMP Enable", "Switch", "AMP Playback"पूर्ण,
	अणु"SDIN", शून्य, "AMP Enable"पूर्ण,
	अणु"Channel Mux", "RX1", "SDIN"पूर्ण,
	अणु"Channel Mux", "RX2", "SDIN"पूर्ण,
	अणु"BOOST Enable", "Switch", "Channel Mux"पूर्ण,
	अणु"CLASS H", शून्य, "BOOST Enable"पूर्ण,
	अणु"Main AMP", शून्य, "Channel Mux"पूर्ण,
	अणु"Main AMP", शून्य, "CLASS H"पूर्ण,
	अणु"SPK", शून्य, "Main AMP"पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l36_set_dai_fmt(काष्ठा snd_soc_dai *component_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component_dai->component);
	अचिन्हित पूर्णांक asp_fmt, lrclk_fmt, sclk_fmt, slave_mode, clk_frc;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		slave_mode = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		slave_mode = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_TX_PIN_CTRL,
				CS35L36_SCLK_MSTR_MASK,
				slave_mode << CS35L36_SCLK_MSTR_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RATE_CTRL,
				CS35L36_LRCLK_MSTR_MASK,
				slave_mode << CS35L36_LRCLK_MSTR_SHIFT);

	चयन (fmt & SND_SOC_DAIFMT_CLOCK_MASK) अणु
	हाल SND_SOC_DAIFMT_CONT:
		clk_frc = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_GATED:
		clk_frc = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_TX_PIN_CTRL,
			   CS35L36_SCLK_FRC_MASK, clk_frc <<
			   CS35L36_SCLK_FRC_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RATE_CTRL,
			   CS35L36_LRCLK_FRC_MASK, clk_frc <<
			   CS35L36_LRCLK_FRC_SHIFT);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		asp_fmt = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		asp_fmt = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_IF:
		lrclk_fmt = 1;
		sclk_fmt = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		lrclk_fmt = 0;
		sclk_fmt = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		lrclk_fmt = 1;
		sclk_fmt = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		lrclk_fmt = 0;
		sclk_fmt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_RATE_CTRL,
			   CS35L36_LRCLK_INV_MASK,
			   lrclk_fmt << CS35L36_LRCLK_INV_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_TX_PIN_CTRL,
			   CS35L36_SCLK_INV_MASK,
			   sclk_fmt << CS35L36_SCLK_INV_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_ASP_FORMAT,
			   CS35L36_ASP_FMT_MASK, asp_fmt);

	वापस 0;
पूर्ण

काष्ठा cs35l36_global_fs_config अणु
	पूर्णांक rate;
	पूर्णांक fs_cfg;
पूर्ण;

अटल स्थिर काष्ठा cs35l36_global_fs_config cs35l36_fs_rates[] = अणु
	अणु12000, 0x01पूर्ण,
	अणु24000, 0x02पूर्ण,
	अणु48000, 0x03पूर्ण,
	अणु96000, 0x04पूर्ण,
	अणु192000, 0x05पूर्ण,
	अणु384000, 0x06पूर्ण,
	अणु11025, 0x09पूर्ण,
	अणु22050, 0x0Aपूर्ण,
	अणु44100, 0x0Bपूर्ण,
	अणु88200, 0x0Cपूर्ण,
	अणु176400, 0x0Dपूर्ण,
	अणु8000, 0x11पूर्ण,
	अणु16000, 0x12पूर्ण,
	अणु32000, 0x13पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l36_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(dai->component);
	अचिन्हित पूर्णांक asp_width, global_fs = params_rate(params);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs35l36_fs_rates); i++) अणु
		अगर (global_fs == cs35l36_fs_rates[i].rate)
			regmap_update_bits(cs35l36->regmap,
					   CS35L36_GLOBAL_CLK_CTRL,
					   CS35L36_GLOBAL_FS_MASK,
					   cs35l36_fs_rates[i].fs_cfg <<
					   CS35L36_GLOBAL_FS_SHIFT);
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		asp_width = CS35L36_ASP_WIDTH_16;
		अवरोध;
	हाल 24:
		asp_width = CS35L36_ASP_WIDTH_24;
		अवरोध;
	हाल 32:
		asp_width = CS35L36_ASP_WIDTH_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_FRAME_CTRL,
				   CS35L36_ASP_RX_WIDTH_MASK,
				   asp_width << CS35L36_ASP_RX_WIDTH_SHIFT);
	पूर्ण अन्यथा अणु
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_FRAME_CTRL,
				   CS35L36_ASP_TX_WIDTH_MASK,
				   asp_width << CS35L36_ASP_TX_WIDTH_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_dai_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);
	पूर्णांक fs1, fs2;

	अगर (freq > CS35L36_FS_NOM_6MHZ) अणु
		fs1 = CS35L36_FS1_DEFAULT_VAL;
		fs2 = CS35L36_FS2_DEFAULT_VAL;
	पूर्ण अन्यथा अणु
		fs1 = 3 * ((CS35L36_FS_NOM_6MHZ * 4 + freq - 1) / freq) + 4;
		fs2 = 5 * ((CS35L36_FS_NOM_6MHZ * 4 + freq - 1) / freq) + 4;
	पूर्ण

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_UNLOCK1);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_UNLOCK2);

	regmap_update_bits(cs35l36->regmap, CS35L36_TST_FS_MON0,
			   CS35L36_FS1_WINDOW_MASK | CS35L36_FS2_WINDOW_MASK,
			   fs1 | (fs2 << CS35L36_FS2_WINDOW_SHIFT));

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_LOCK1);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_LOCK2);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cs35l36_pll_config *cs35l36_get_clk_config(
		काष्ठा cs35l36_निजी *cs35l36, पूर्णांक freq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs35l36_pll_sysclk); i++) अणु
		अगर (cs35l36_pll_sysclk[i].freq == freq)
			वापस &cs35l36_pll_sysclk[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs35l36_src_rates[] = अणु
	8000, 12000, 11025, 16000, 22050, 24000, 32000,
	44100, 48000, 88200, 96000, 176400, 192000, 384000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs35l36_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(cs35l36_src_rates),
	.list   = cs35l36_src_rates,
पूर्ण;

अटल पूर्णांक cs35l36_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &cs35l36_स्थिरraपूर्णांकs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l36_ops = अणु
	.startup = cs35l36_pcm_startup,
	.set_fmt = cs35l36_set_dai_fmt,
	.hw_params = cs35l36_pcm_hw_params,
	.set_sysclk = cs35l36_dai_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs35l36_dai[] = अणु
	अणु
		.name = "cs35l36-pcm",
		.id = 0,
		.playback = अणु
			.stream_name = "AMP Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS35L36_RX_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AMP Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS35L36_TX_FORMATS,
		पूर्ण,
		.ops = &cs35l36_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l36_component_set_sysclk(काष्ठा snd_soc_component *component,
				पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq,
				पूर्णांक dir)
अणु
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा cs35l36_pll_config *clk_cfg;
	पूर्णांक prev_clksrc;
	bool pdm_चयन;

	prev_clksrc = cs35l36->clksrc;

	चयन (clk_id) अणु
	हाल 0:
		cs35l36->clksrc = CS35L36_PLLSRC_SCLK;
		अवरोध;
	हाल 1:
		cs35l36->clksrc = CS35L36_PLLSRC_LRCLK;
		अवरोध;
	हाल 2:
		cs35l36->clksrc = CS35L36_PLLSRC_PDMCLK;
		अवरोध;
	हाल 3:
		cs35l36->clksrc = CS35L36_PLLSRC_SELF;
		अवरोध;
	हाल 4:
		cs35l36->clksrc = CS35L36_PLLSRC_MCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	clk_cfg = cs35l36_get_clk_config(cs35l36, freq);
	अगर (clk_cfg == शून्य) अणु
		dev_err(component->dev, "Invalid CLK Config Freq: %d\n", freq);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_PLL_OPENLOOP_MASK,
			   1 << CS35L36_PLL_OPENLOOP_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_REFCLK_FREQ_MASK,
			   clk_cfg->clk_cfg << CS35L36_REFCLK_FREQ_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_PLL_REFCLK_EN_MASK,
			   0 << CS35L36_PLL_REFCLK_EN_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_PLL_CLK_SEL_MASK,
			   cs35l36->clksrc);
	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_PLL_OPENLOOP_MASK,
			   0 << CS35L36_PLL_OPENLOOP_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_PLL_CLK_CTRL,
			   CS35L36_PLL_REFCLK_EN_MASK,
			   1 << CS35L36_PLL_REFCLK_EN_SHIFT);

	अगर (cs35l36->rev_id == CS35L36_REV_A0) अणु
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK2);

		regmap_ग_लिखो(cs35l36->regmap, CS35L36_DCO_CTRL, 0x00036DA8);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_MISC_CTRL, 0x0100EE0E);

		regmap_update_bits(cs35l36->regmap, CS35L36_PLL_LOOP_PARAMS,
				   CS35L36_PLL_IGAIN_MASK,
				   CS35L36_PLL_IGAIN <<
				   CS35L36_PLL_IGAIN_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_PLL_LOOP_PARAMS,
				   CS35L36_PLL_FFL_IGAIN_MASK,
				   clk_cfg->fll_igain);

		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK2);
	पूर्ण

	अगर (cs35l36->clksrc == CS35L36_PLLSRC_PDMCLK) अणु
		pdm_चयन = cs35l36->ldm_mode_sel &&
			     (prev_clksrc != CS35L36_PLLSRC_PDMCLK);

		अगर (pdm_चयन)
			regmap_update_bits(cs35l36->regmap, CS35L36_NG_CFG,
					   CS35L36_NG_DELAY_MASK,
					   0 << CS35L36_NG_DELAY_SHIFT);

		regmap_update_bits(cs35l36->regmap, CS35L36_DAC_MSM_CFG,
				   CS35L36_PDM_MODE_MASK,
				   1 << CS35L36_PDM_MODE_SHIFT);

		अगर (pdm_चयन)
			regmap_update_bits(cs35l36->regmap, CS35L36_NG_CFG,
					   CS35L36_NG_DELAY_MASK,
					   3 << CS35L36_NG_DELAY_SHIFT);
	पूर्ण अन्यथा अणु
		pdm_चयन = cs35l36->ldm_mode_sel &&
			     (prev_clksrc == CS35L36_PLLSRC_PDMCLK);

		अगर (pdm_चयन)
			regmap_update_bits(cs35l36->regmap, CS35L36_NG_CFG,
					   CS35L36_NG_DELAY_MASK,
					   0 << CS35L36_NG_DELAY_SHIFT);

		regmap_update_bits(cs35l36->regmap, CS35L36_DAC_MSM_CFG,
				   CS35L36_PDM_MODE_MASK,
				   0 << CS35L36_PDM_MODE_SHIFT);

		अगर (pdm_चयन)
			regmap_update_bits(cs35l36->regmap, CS35L36_NG_CFG,
					   CS35L36_NG_DELAY_MASK,
					   3 << CS35L36_NG_DELAY_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_boost_inductor(काष्ठा cs35l36_निजी *cs35l36, पूर्णांक inductor)
अणु
	regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_COEFF,
			   CS35L36_BSTCVRT_K1_MASK, 0x3C);
	regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_COEFF,
			   CS35L36_BSTCVRT_K2_MASK,
			   0x3C << CS35L36_BSTCVRT_K2_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_SW_FREQ,
			   CS35L36_BSTCVRT_CCMFREQ_MASK, 0x00);

	चयन (inductor) अणु
	हाल 1000: /* 1 uH */
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_SLOPE_LBST,
				   CS35L36_BSTCVRT_SLOPE_MASK,
				   0x75 << CS35L36_BSTCVRT_SLOPE_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_SLOPE_LBST,
				   CS35L36_BSTCVRT_LBSTVAL_MASK, 0x00);
		अवरोध;
	हाल 1200: /* 1.2 uH */
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_SLOPE_LBST,
				   CS35L36_BSTCVRT_SLOPE_MASK,
				   0x6B << CS35L36_BSTCVRT_SLOPE_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_SLOPE_LBST,
				   CS35L36_BSTCVRT_LBSTVAL_MASK, 0x01);
		अवरोध;
	शेष:
		dev_err(cs35l36->dev, "%s Invalid Inductor Value %d uH\n",
			__func__, inductor);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs35l36_निजी *cs35l36 =
			snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर ((cs35l36->rev_id == CS35L36_REV_A0) && cs35l36->pdata.dcm_mode) अणु
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_DCM_CTRL,
				   CS35L36_DCM_AUTO_MASK,
				   CS35L36_DCM_AUTO_MASK);

		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK2);

		regmap_update_bits(cs35l36->regmap, CS35L36_BST_TST_MANUAL,
				   CS35L36_BST_MAN_IPKCOMP_MASK,
				   0 << CS35L36_BST_MAN_IPKCOMP_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BST_TST_MANUAL,
				   CS35L36_BST_MAN_IPKCOMP_EN_MASK,
				   CS35L36_BST_MAN_IPKCOMP_EN_MASK);

		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
				CS35L36_TEST_LOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
				CS35L36_TEST_LOCK2);
	पूर्ण

	अगर (cs35l36->pdata.amp_pcm_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_AMP_DIG_VOL_CTRL,
				   CS35L36_AMP_PCM_INV_MASK,
				   CS35L36_AMP_PCM_INV_MASK);

	अगर (cs35l36->pdata.multi_amp_mode)
		regmap_update_bits(cs35l36->regmap, CS35L36_ASP_TX_PIN_CTRL,
				   CS35L36_ASP_TX_HIZ_MASK,
				   CS35L36_ASP_TX_HIZ_MASK);

	अगर (cs35l36->pdata.imon_pol_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_VI_SPKMON_FILT,
				   CS35L36_IMON_POL_MASK, 0);

	अगर (cs35l36->pdata.vmon_pol_inv)
		regmap_update_bits(cs35l36->regmap, CS35L36_VI_SPKMON_FILT,
				   CS35L36_VMON_POL_MASK, 0);

	अगर (cs35l36->pdata.bst_vctl)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL1,
				   CS35L35_BSTCVRT_CTL_MASK,
				   cs35l36->pdata.bst_vctl);

	अगर (cs35l36->pdata.bst_vctl_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL2,
				   CS35L35_BSTCVRT_CTL_SEL_MASK,
				   cs35l36->pdata.bst_vctl_sel);

	अगर (cs35l36->pdata.bst_ipk)
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_PEAK_CUR,
				   CS35L36_BST_IPK_MASK,
				   cs35l36->pdata.bst_ipk);

	अगर (cs35l36->pdata.boost_ind) अणु
		ret = cs35l36_boost_inductor(cs35l36, cs35l36->pdata.boost_ind);
		अगर (ret < 0) अणु
			dev_err(cs35l36->dev,
				"Boost inductor config failed(%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (cs35l36->pdata.temp_warn_thld)
		regmap_update_bits(cs35l36->regmap, CS35L36_DTEMP_WARN_THLD,
				   CS35L36_TEMP_THLD_MASK,
				   cs35l36->pdata.temp_warn_thld);

	अगर (cs35l36->pdata.irq_drv_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
				   CS35L36_INT_DRV_SEL_MASK,
				   cs35l36->pdata.irq_drv_sel <<
				   CS35L36_INT_DRV_SEL_SHIFT);

	अगर (cs35l36->pdata.irq_gpio_sel)
		regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
				   CS35L36_INT_GPIO_SEL_MASK,
				   cs35l36->pdata.irq_gpio_sel <<
				   CS35L36_INT_GPIO_SEL_SHIFT);

	/*
	 * Rev B0 has 2 versions
	 * L36 is 10V
	 * L37 is 12V
	 * If L36 we need to clamp some values क्रम safety
	 * after probe has setup dt values. We want to make
	 * sure we करोnt miss any values set in probe
	 */
	अगर (cs35l36->chip_version == CS35L36_10V_L36) अणु
		regmap_update_bits(cs35l36->regmap,
				   CS35L36_BSTCVRT_OVERVOLT_CTRL,
				   CS35L36_BST_OVP_THLD_MASK,
				   CS35L36_BST_OVP_THLD_11V);

		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_UNLOCK2);

		regmap_update_bits(cs35l36->regmap, CS35L36_BST_ANA2_TEST,
				   CS35L36_BST_OVP_TRIM_MASK,
				   CS35L36_BST_OVP_TRIM_11V <<
				   CS35L36_BST_OVP_TRIM_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL2,
				   CS35L36_BST_CTRL_LIM_MASK,
				   1 << CS35L36_BST_CTRL_LIM_SHIFT);
		regmap_update_bits(cs35l36->regmap, CS35L36_BSTCVRT_VCTRL1,
				   CS35L35_BSTCVRT_CTL_MASK,
				   CS35L36_BST_CTRL_10V_CLAMP);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK1);
		regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			     CS35L36_TEST_LOCK2);
	पूर्ण

	/*
	 * RevA and B require the disabling of
	 * SYNC_GLOBAL_OVR when GLOBAL_EN = 0.
	 * Just turn it off from शेष
	 */
	regmap_update_bits(cs35l36->regmap, CS35L36_CTRL_OVRRIDE,
			   CS35L36_SYNC_GLOBAL_OVR_MASK,
			   0 << CS35L36_SYNC_GLOBAL_OVR_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs35l36 = अणु
	.probe			= &cs35l36_component_probe,
	.set_sysclk		= cs35l36_component_set_sysclk,
	.dapm_widमाला_लो		= cs35l36_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs35l36_dapm_widमाला_लो),
	.dapm_routes		= cs35l36_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs35l36_audio_map),
	.controls		= cs35l36_aud_controls,
	.num_controls		= ARRAY_SIZE(cs35l36_aud_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा regmap_config cs35l36_regmap = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = CS35L36_PAC_PMEM_WORD1023,
	.reg_शेषs = cs35l36_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs35l36_reg),
	.precious_reg = cs35l36_precious_reg,
	.अस्थिर_reg = cs35l36_अस्थिर_reg,
	.पढ़ोable_reg = cs35l36_पढ़ोable_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल irqवापस_t cs35l36_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs35l36_निजी *cs35l36 = data;
	अचिन्हित पूर्णांक status[4];
	अचिन्हित पूर्णांक masks[4];
	पूर्णांक ret = IRQ_NONE;

	/* ack the irq by पढ़ोing all status रेजिस्टरs */
	regmap_bulk_पढ़ो(cs35l36->regmap, CS35L36_INT1_STATUS, status,
			 ARRAY_SIZE(status));

	regmap_bulk_पढ़ो(cs35l36->regmap, CS35L36_INT1_MASK, masks,
			 ARRAY_SIZE(masks));

	/* Check to see अगर unmasked bits are active */
	अगर (!(status[0] & ~masks[0]) && !(status[1] & ~masks[1]) &&
		!(status[2] & ~masks[2]) && !(status[3] & ~masks[3])) अणु
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * The following पूर्णांकerrupts require a
	 * protection release cycle to get the
	 * speaker out of Safe-Mode.
	 */
	अगर (status[2] & CS35L36_AMP_SHORT_ERR) अणु
		dev_crit(cs35l36->dev, "Amp short error\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_AMP_SHORT_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_AMP_SHORT_ERR_RLS,
				   CS35L36_AMP_SHORT_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_AMP_SHORT_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT3_STATUS,
				   CS35L36_AMP_SHORT_ERR,
				   CS35L36_AMP_SHORT_ERR);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status[0] & CS35L36_TEMP_WARN) अणु
		dev_crit(cs35l36->dev, "Over temperature warning\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_WARN_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_WARN_ERR_RLS,
				   CS35L36_TEMP_WARN_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_WARN_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT1_STATUS,
				   CS35L36_TEMP_WARN, CS35L36_TEMP_WARN);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status[0] & CS35L36_TEMP_ERR) अणु
		dev_crit(cs35l36->dev, "Over temperature error\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, CS35L36_TEMP_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT1_STATUS,
				   CS35L36_TEMP_ERR, CS35L36_TEMP_ERR);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status[0] & CS35L36_BST_OVP_ERR) अणु
		dev_crit(cs35l36->dev, "VBST Over Voltage error\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, CS35L36_TEMP_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_TEMP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT1_STATUS,
				   CS35L36_BST_OVP_ERR, CS35L36_BST_OVP_ERR);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status[0] & CS35L36_BST_DCM_UVP_ERR) अणु
		dev_crit(cs35l36->dev, "DCM VBST Under Voltage Error\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_UVP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_UVP_ERR_RLS,
				   CS35L36_BST_UVP_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_UVP_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT1_STATUS,
				   CS35L36_BST_DCM_UVP_ERR,
				   CS35L36_BST_DCM_UVP_ERR);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (status[0] & CS35L36_BST_SHORT_ERR) अणु
		dev_crit(cs35l36->dev, "LBST SHORT error!\n");
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_SHORT_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_SHORT_ERR_RLS,
				   CS35L36_BST_SHORT_ERR_RLS);
		regmap_update_bits(cs35l36->regmap, CS35L36_PROTECT_REL_ERR,
				   CS35L36_BST_SHORT_ERR_RLS, 0);
		regmap_update_bits(cs35l36->regmap, CS35L36_INT1_STATUS,
				   CS35L36_BST_SHORT_ERR,
				   CS35L36_BST_SHORT_ERR);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cs35l36_handle_of_data(काष्ठा i2c_client *i2c_client,
				काष्ठा cs35l36_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	काष्ठा cs35l36_vpbr_cfg *vpbr_config = &pdata->vpbr_config;
	काष्ठा device_node *vpbr_node;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!np)
		वापस 0;

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-ctl-millivolt", &val);
	अगर (!ret) अणु
		अगर (val < 2550 || val > 12000) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val);
			वापस -EINVAL;
		पूर्ण
		pdata->bst_vctl = (((val - 2550) / 100) + 1) << 1;
	पूर्ण अन्यथा अणु
		dev_err(&i2c_client->dev,
			"Unable to find required parameter 'cirrus,boost-ctl-millivolt'");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-ctl-select", &val);
	अगर (!ret)
		pdata->bst_vctl_sel = val | CS35L36_VALID_PDATA;

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-peak-milliamp", &val);
	अगर (!ret) अणु
		अगर (val < 1600 || val > 4500) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %u mA\n", val);
			वापस -EINVAL;
		पूर्ण

		pdata->bst_ipk = (val - 1600) / 50;
	पूर्ण अन्यथा अणु
		dev_err(&i2c_client->dev,
			"Unable to find required parameter 'cirrus,boost-peak-milliamp'");
		वापस -EINVAL;
	पूर्ण

	pdata->multi_amp_mode = of_property_पढ़ो_bool(np,
					"cirrus,multi-amp-mode");

	pdata->dcm_mode = of_property_पढ़ो_bool(np,
					"cirrus,dcm-mode-enable");

	pdata->amp_pcm_inv = of_property_पढ़ो_bool(np,
					"cirrus,amp-pcm-inv");

	pdata->imon_pol_inv = of_property_पढ़ो_bool(np,
					"cirrus,imon-pol-inv");

	pdata->vmon_pol_inv = of_property_पढ़ो_bool(np,
					"cirrus,vmon-pol-inv");

	अगर (of_property_पढ़ो_u32(np, "cirrus,temp-warn-threshold", &val) >= 0)
		pdata->temp_warn_thld = val | CS35L36_VALID_PDATA;

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-ind-nanohenry", &val) >= 0) अणु
		pdata->boost_ind = val;
	पूर्ण अन्यथा अणु
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,irq-drive-select", &val) >= 0)
		pdata->irq_drv_sel = val | CS35L36_VALID_PDATA;

	अगर (of_property_पढ़ो_u32(np, "cirrus,irq-gpio-select", &val) >= 0)
		pdata->irq_gpio_sel = val | CS35L36_VALID_PDATA;

	/* VPBR Config */
	vpbr_node = of_get_child_by_name(np, "cirrus,vpbr-config");
	vpbr_config->is_present = vpbr_node ? true : false;
	अगर (vpbr_config->is_present) अणु
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-en",
					 &val) >= 0)
			vpbr_config->vpbr_en = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-thld",
					 &val) >= 0)
			vpbr_config->vpbr_thld = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-atk-rate",
					 &val) >= 0)
			vpbr_config->vpbr_atk_rate = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-atk-vol",
					 &val) >= 0)
			vpbr_config->vpbr_atk_vol = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-max-attn",
					 &val) >= 0)
			vpbr_config->vpbr_max_attn = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-wait",
					 &val) >= 0)
			vpbr_config->vpbr_रुको = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-rel-rate",
					 &val) >= 0)
			vpbr_config->vpbr_rel_rate = val;
		अगर (of_property_पढ़ो_u32(vpbr_node, "cirrus,vpbr-mute-en",
					 &val) >= 0)
			vpbr_config->vpbr_mute_en = val;
	पूर्ण
	of_node_put(vpbr_node);

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l36_pac(काष्ठा cs35l36_निजी *cs35l36)
अणु
	पूर्णांक ret, count;
	अचिन्हित पूर्णांक val;

	अगर (cs35l36->rev_id != CS35L36_REV_B0)
		वापस 0;

	/*
	 * Magic code क्रम पूर्णांकernal PAC
	 */
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
		     CS35L36_TEST_UNLOCK1);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
		     CS35L36_TEST_UNLOCK2);

	usleep_range(9500, 10500);

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_PAC_CTL1,
		     CS35L36_PAC_RESET);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_PAC_CTL3,
		     CS35L36_PAC_MEM_ACCESS);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_PAC_PMEM_WORD0,
		     CS35L36_B0_PAC_PATCH);

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_PAC_CTL3,
		     CS35L36_PAC_MEM_ACCESS_CLR);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_PAC_CTL1,
		     CS35L36_PAC_ENABLE_MASK);

	usleep_range(9500, 10500);

	ret = regmap_पढ़ो(cs35l36->regmap, CS35L36_INT4_STATUS, &val);
	अगर (ret < 0) अणु
		dev_err(cs35l36->dev, "Failed to read int4_status %d\n", ret);
		वापस ret;
	पूर्ण

	count = 0;
	जबतक (!(val & CS35L36_MCU_CONFIG_CLR)) अणु
		usleep_range(100, 200);
		count++;

		ret = regmap_पढ़ो(cs35l36->regmap, CS35L36_INT4_STATUS,
				  &val);
		अगर (ret < 0) अणु
			dev_err(cs35l36->dev, "Failed to read int4_status %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (count >= 100)
			वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_INT4_STATUS,
		     CS35L36_MCU_CONFIG_CLR);
	regmap_update_bits(cs35l36->regmap, CS35L36_PAC_CTL1,
			   CS35L36_PAC_ENABLE_MASK, 0);

	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
		     CS35L36_TEST_LOCK1);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
		     CS35L36_TEST_LOCK2);

	वापस 0;
पूर्ण

अटल व्योम cs35l36_apply_vpbr_config(काष्ठा cs35l36_निजी *cs35l36)
अणु
	काष्ठा cs35l36_platक्रमm_data *pdata = &cs35l36->pdata;
	काष्ठा cs35l36_vpbr_cfg *vpbr_config = &pdata->vpbr_config;

	regmap_update_bits(cs35l36->regmap, CS35L36_PWR_CTRL3,
			   CS35L36_VPBR_EN_MASK,
			   vpbr_config->vpbr_en <<
			   CS35L36_VPBR_EN_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_THLD_MASK,
			   vpbr_config->vpbr_thld <<
			   CS35L36_VPBR_THLD_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_MAX_ATTN_MASK,
			   vpbr_config->vpbr_max_attn <<
			   CS35L36_VPBR_MAX_ATTN_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_ATK_VOL_MASK,
			   vpbr_config->vpbr_atk_vol <<
			   CS35L36_VPBR_ATK_VOL_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_ATK_RATE_MASK,
			   vpbr_config->vpbr_atk_rate <<
			   CS35L36_VPBR_ATK_RATE_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_WAIT_MASK,
			   vpbr_config->vpbr_रुको <<
			   CS35L36_VPBR_WAIT_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_REL_RATE_MASK,
			   vpbr_config->vpbr_rel_rate <<
			   CS35L36_VPBR_REL_RATE_SHIFT);
	regmap_update_bits(cs35l36->regmap, CS35L36_VPBR_CFG,
			   CS35L36_VPBR_MUTE_EN_MASK,
			   vpbr_config->vpbr_mute_en <<
			   CS35L36_VPBR_MUTE_EN_SHIFT);
पूर्ण

अटल स्थिर काष्ठा reg_sequence cs35l36_reva0_errata_patch[] = अणु
	अणु CS35L36_TESTKEY_CTRL,		CS35L36_TEST_UNLOCK1 पूर्ण,
	अणु CS35L36_TESTKEY_CTRL,		CS35L36_TEST_UNLOCK2 पूर्ण,
	/* Errata Writes */
	अणु CS35L36_OTP_CTRL1,		0x00002060 पूर्ण,
	अणु CS35L36_OTP_CTRL2,		0x00000001 पूर्ण,
	अणु CS35L36_OTP_CTRL1,		0x00002460 पूर्ण,
	अणु CS35L36_OTP_CTRL2,		0x00000001 पूर्ण,
	अणु 0x00002088,			0x012A1838 पूर्ण,
	अणु 0x00003014,			0x0100EE0E पूर्ण,
	अणु 0x00003008,			0x0008184A पूर्ण,
	अणु 0x00007418,			0x509001C8 पूर्ण,
	अणु 0x00007064,			0x0929A800 पूर्ण,
	अणु 0x00002D10,			0x0002C01C पूर्ण,
	अणु 0x0000410C,			0x00000A11 पूर्ण,
	अणु 0x00006E08,			0x8B19140C पूर्ण,
	अणु 0x00006454,			0x0300000A पूर्ण,
	अणु CS35L36_AMP_NG_CTRL,		0x000020EF पूर्ण,
	अणु 0x00007E34,			0x0000000E पूर्ण,
	अणु 0x0000410C,			0x00000A11 पूर्ण,
	अणु 0x00007410,			0x20514B00 पूर्ण,
	/* PAC Config */
	अणु CS35L36_CTRL_OVRRIDE,		0x00000000 पूर्ण,
	अणु CS35L36_PAC_INT0_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT1_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT2_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT3_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT4_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT5_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT6_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT7_CTRL,	0x00860001 पूर्ण,
	अणु CS35L36_PAC_INT_FLUSH_CTRL,	0x000000FF पूर्ण,
	अणु CS35L36_TESTKEY_CTRL,		CS35L36_TEST_LOCK1 पूर्ण,
	अणु CS35L36_TESTKEY_CTRL,		CS35L36_TEST_LOCK2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence cs35l36_revb0_errata_patch[] = अणु
	अणु CS35L36_TESTKEY_CTRL,	CS35L36_TEST_UNLOCK1 पूर्ण,
	अणु CS35L36_TESTKEY_CTRL, CS35L36_TEST_UNLOCK2 पूर्ण,
	अणु 0x00007064,		0x0929A800 पूर्ण,
	अणु 0x00007850,		0x00002FA9 पूर्ण,
	अणु 0x00007854,		0x0003F1D5 पूर्ण,
	अणु 0x00007858,		0x0003F5E3 पूर्ण,
	अणु 0x0000785C,		0x00001137 पूर्ण,
	अणु 0x00007860,		0x0001A7A5 पूर्ण,
	अणु 0x00007864,		0x0002F16A पूर्ण,
	अणु 0x00007868,		0x00003E21 पूर्ण,
	अणु 0x00007848,		0x00000001 पूर्ण,
	अणु 0x00003854,		0x05180240 पूर्ण,
	अणु 0x00007418,		0x509001C8 पूर्ण,
	अणु 0x0000394C,		0x028764BD पूर्ण,
	अणु CS35L36_TESTKEY_CTRL,	CS35L36_TEST_LOCK1 पूर्ण,
	अणु CS35L36_TESTKEY_CTRL, CS35L36_TEST_LOCK2 पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l36_i2c_probe(काष्ठा i2c_client *i2c_client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs35l36_निजी *cs35l36;
	काष्ठा device *dev = &i2c_client->dev;
	काष्ठा cs35l36_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा irq_data *irq_d;
	पूर्णांक ret, irq_pol, chip_irq_pol, i;
	u32 reg_id, reg_revid, l37_id_reg;

	cs35l36 = devm_kzalloc(dev, माप(काष्ठा cs35l36_निजी), GFP_KERNEL);
	अगर (!cs35l36)
		वापस -ENOMEM;

	cs35l36->dev = dev;

	i2c_set_clientdata(i2c_client, cs35l36);
	cs35l36->regmap = devm_regmap_init_i2c(i2c_client, &cs35l36_regmap);
	अगर (IS_ERR(cs35l36->regmap)) अणु
		ret = PTR_ERR(cs35l36->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	cs35l36->num_supplies = ARRAY_SIZE(cs35l36_supplies);
	क्रम (i = 0; i < ARRAY_SIZE(cs35l36_supplies); i++)
		cs35l36->supplies[i].supply = cs35l36_supplies[i];

	ret = devm_regulator_bulk_get(dev, cs35l36->num_supplies,
				      cs35l36->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs35l36->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(dev, माप(काष्ठा cs35l36_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (i2c_client->dev.of_node) अणु
			ret = cs35l36_handle_of_data(i2c_client, pdata);
			अगर (ret != 0)
				वापस ret;

		पूर्ण

		cs35l36->pdata = *pdata;
	पूर्ण

	ret = regulator_bulk_enable(cs35l36->num_supplies, cs35l36->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* वापसing शून्य can be an option अगर in stereo mode */
	cs35l36->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(cs35l36->reset_gpio)) अणु
		ret = PTR_ERR(cs35l36->reset_gpio);
		cs35l36->reset_gpio = शून्य;
		अगर (ret == -EBUSY) अणु
			dev_info(dev, "Reset line busy, assuming shared reset\n");
		पूर्ण अन्यथा अणु
			dev_err(dev, "Failed to get reset GPIO: %d\n", ret);
			जाओ err_disable_regs;
		पूर्ण
	पूर्ण

	अगर (cs35l36->reset_gpio)
		gpiod_set_value_cansleep(cs35l36->reset_gpio, 1);

	usleep_range(2000, 2100);

	/* initialize amplअगरier */
	ret = regmap_पढ़ो(cs35l36->regmap, CS35L36_SW_RESET, &reg_id);
	अगर (ret < 0) अणु
		dev_err(dev, "Get Device ID failed %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (reg_id != CS35L36_CHIP_ID) अणु
		dev_err(dev, "Device ID (%X). Expected ID %X\n", reg_id,
			CS35L36_CHIP_ID);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(cs35l36->regmap, CS35L36_REV_ID, &reg_revid);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed %d\n", ret);
		जाओ err;
	पूर्ण

	cs35l36->rev_id = reg_revid >> 8;

	ret = regmap_पढ़ो(cs35l36->regmap, CS35L36_OTP_MEM30, &l37_id_reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Failed to read otp_id Register %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर ((l37_id_reg & CS35L36_OTP_REV_MASK) == CS35L36_OTP_REV_L37)
		cs35l36->chip_version = CS35L36_12V_L37;
	अन्यथा
		cs35l36->chip_version = CS35L36_10V_L36;

	चयन (cs35l36->rev_id) अणु
	हाल CS35L36_REV_A0:
		ret = regmap_रेजिस्टर_patch(cs35l36->regmap,
				cs35l36_reva0_errata_patch,
				ARRAY_SIZE(cs35l36_reva0_errata_patch));
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to apply A0 errata patch %d\n",
				ret);
			जाओ err;
		पूर्ण
		अवरोध;
	हाल CS35L36_REV_B0:
		ret = cs35l36_pac(cs35l36);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to Trim OTP %d\n", ret);
			जाओ err;
		पूर्ण

		ret = regmap_रेजिस्टर_patch(cs35l36->regmap,
				cs35l36_revb0_errata_patch,
				ARRAY_SIZE(cs35l36_revb0_errata_patch));
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to apply B0 errata patch %d\n",
				ret);
			जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (pdata->vpbr_config.is_present)
		cs35l36_apply_vpbr_config(cs35l36);

	irq_d = irq_get_irq_data(i2c_client->irq);
	अगर (!irq_d) अणु
		dev_err(&i2c_client->dev, "Invalid IRQ: %d\n", i2c_client->irq);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	irq_pol = irqd_get_trigger_type(irq_d);

	चयन (irq_pol) अणु
	हाल IRQF_TRIGGER_FALLING:
	हाल IRQF_TRIGGER_LOW:
		chip_irq_pol = 0;
		अवरोध;
	हाल IRQF_TRIGGER_RISING:
	हाल IRQF_TRIGGER_HIGH:
		chip_irq_pol = 1;
		अवरोध;
	शेष:
		dev_err(cs35l36->dev, "Invalid IRQ polarity: %d\n", irq_pol);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
			   CS35L36_INT_POL_SEL_MASK,
			   chip_irq_pol << CS35L36_INT_POL_SEL_SHIFT);

	ret = devm_request_thपढ़ोed_irq(dev, i2c_client->irq, शून्य, cs35l36_irq,
					IRQF_ONESHOT | irq_pol, "cs35l36",
					cs35l36);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request IRQ: %d\n", ret);
		जाओ err;
	पूर्ण

	regmap_update_bits(cs35l36->regmap, CS35L36_PAD_INTERFACE,
			   CS35L36_INT_OUTPUT_EN_MASK, 1);

	/* Set पूर्णांकerrupt masks क्रम critical errors */
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_INT1_MASK,
		     CS35L36_INT1_MASK_DEFAULT);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_INT3_MASK,
		     CS35L36_INT3_MASK_DEFAULT);

	dev_info(&i2c_client->dev, "Cirrus Logic CS35L%d, Revision: %02X\n",
		 cs35l36->chip_version, reg_revid >> 8);

	ret =  devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_cs35l36,
					       cs35l36_dai,
					       ARRAY_SIZE(cs35l36_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "%s: Register component failed %d\n", __func__,
			ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	gpiod_set_value_cansleep(cs35l36->reset_gpio, 0);

err_disable_regs:
	regulator_bulk_disable(cs35l36->num_supplies, cs35l36->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक cs35l36_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs35l36_निजी *cs35l36 = i2c_get_clientdata(client);

	/* Reset पूर्णांकerrupt masks क्रम device removal */
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_INT1_MASK,
		     CS35L36_INT1_MASK_RESET);
	regmap_ग_लिखो(cs35l36->regmap, CS35L36_INT3_MASK,
		     CS35L36_INT3_MASK_RESET);

	अगर (cs35l36->reset_gpio)
		gpiod_set_value_cansleep(cs35l36->reset_gpio, 0);

	regulator_bulk_disable(cs35l36->num_supplies, cs35l36->supplies);

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा of_device_id cs35l36_of_match[] = अणु
	अणु.compatible = "cirrus,cs35l36"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs35l36_of_match);

अटल स्थिर काष्ठा i2c_device_id cs35l36_id[] = अणु
	अणु"cs35l36", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs35l36_id);

अटल काष्ठा i2c_driver cs35l36_i2c_driver = अणु
	.driver = अणु
		.name = "cs35l36",
		.of_match_table = cs35l36_of_match,
	पूर्ण,
	.id_table = cs35l36_id,
	.probe = cs35l36_i2c_probe,
	.हटाओ = cs35l36_i2c_हटाओ,
पूर्ण;
module_i2c_driver(cs35l36_i2c_driver);

MODULE_DESCRIPTION("ASoC CS35L36 driver");
MODULE_AUTHOR("James Schulman, Cirrus Logic Inc, <james.schulman@cirrus.com>");
MODULE_LICENSE("GPL");
