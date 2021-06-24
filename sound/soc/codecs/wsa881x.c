<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2015-2017, The Linux Foundation.
// Copyright (c) 2019, Linaro Limited

#समावेश <linux/bitops.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा WSA881X_DIGITAL_BASE		0x3000
#घोषणा WSA881X_ANALOG_BASE		0x3100

/* Digital रेजिस्टर address space */
#घोषणा WSA881X_CHIP_ID0			(WSA881X_DIGITAL_BASE + 0x0000)
#घोषणा WSA881X_CHIP_ID1			(WSA881X_DIGITAL_BASE + 0x0001)
#घोषणा WSA881X_CHIP_ID2			(WSA881X_DIGITAL_BASE + 0x0002)
#घोषणा WSA881X_CHIP_ID3			(WSA881X_DIGITAL_BASE + 0x0003)
#घोषणा WSA881X_BUS_ID				(WSA881X_DIGITAL_BASE + 0x0004)
#घोषणा WSA881X_CDC_RST_CTL			(WSA881X_DIGITAL_BASE + 0x0005)
#घोषणा WSA881X_CDC_TOP_CLK_CTL			(WSA881X_DIGITAL_BASE + 0x0006)
#घोषणा WSA881X_CDC_ANA_CLK_CTL			(WSA881X_DIGITAL_BASE + 0x0007)
#घोषणा WSA881X_CDC_DIG_CLK_CTL			(WSA881X_DIGITAL_BASE + 0x0008)
#घोषणा WSA881X_CLOCK_CONFIG			(WSA881X_DIGITAL_BASE + 0x0009)
#घोषणा WSA881X_ANA_CTL				(WSA881X_DIGITAL_BASE + 0x000A)
#घोषणा WSA881X_SWR_RESET_EN			(WSA881X_DIGITAL_BASE + 0x000B)
#घोषणा WSA881X_RESET_CTL			(WSA881X_DIGITAL_BASE + 0x000C)
#घोषणा WSA881X_TADC_VALUE_CTL			(WSA881X_DIGITAL_BASE + 0x000F)
#घोषणा WSA881X_TEMP_DETECT_CTL			(WSA881X_DIGITAL_BASE + 0x0010)
#घोषणा WSA881X_TEMP_MSB			(WSA881X_DIGITAL_BASE + 0x0011)
#घोषणा WSA881X_TEMP_LSB			(WSA881X_DIGITAL_BASE + 0x0012)
#घोषणा WSA881X_TEMP_CONFIG0			(WSA881X_DIGITAL_BASE + 0x0013)
#घोषणा WSA881X_TEMP_CONFIG1			(WSA881X_DIGITAL_BASE + 0x0014)
#घोषणा WSA881X_CDC_CLIP_CTL			(WSA881X_DIGITAL_BASE + 0x0015)
#घोषणा WSA881X_SDM_PDM9_LSB			(WSA881X_DIGITAL_BASE + 0x0016)
#घोषणा WSA881X_SDM_PDM9_MSB			(WSA881X_DIGITAL_BASE + 0x0017)
#घोषणा WSA881X_CDC_RX_CTL			(WSA881X_DIGITAL_BASE + 0x0018)
#घोषणा WSA881X_DEM_BYPASS_DATA0		(WSA881X_DIGITAL_BASE + 0x0019)
#घोषणा WSA881X_DEM_BYPASS_DATA1		(WSA881X_DIGITAL_BASE + 0x001A)
#घोषणा WSA881X_DEM_BYPASS_DATA2		(WSA881X_DIGITAL_BASE + 0x001B)
#घोषणा WSA881X_DEM_BYPASS_DATA3		(WSA881X_DIGITAL_BASE + 0x001C)
#घोषणा WSA881X_OTP_CTRL0			(WSA881X_DIGITAL_BASE + 0x001D)
#घोषणा WSA881X_OTP_CTRL1			(WSA881X_DIGITAL_BASE + 0x001E)
#घोषणा WSA881X_HDRIVE_CTL_GROUP1		(WSA881X_DIGITAL_BASE + 0x001F)
#घोषणा WSA881X_INTR_MODE			(WSA881X_DIGITAL_BASE + 0x0020)
#घोषणा WSA881X_INTR_MASK			(WSA881X_DIGITAL_BASE + 0x0021)
#घोषणा WSA881X_INTR_STATUS			(WSA881X_DIGITAL_BASE + 0x0022)
#घोषणा WSA881X_INTR_CLEAR			(WSA881X_DIGITAL_BASE + 0x0023)
#घोषणा WSA881X_INTR_LEVEL			(WSA881X_DIGITAL_BASE + 0x0024)
#घोषणा WSA881X_INTR_SET			(WSA881X_DIGITAL_BASE + 0x0025)
#घोषणा WSA881X_INTR_TEST			(WSA881X_DIGITAL_BASE + 0x0026)
#घोषणा WSA881X_PDM_TEST_MODE			(WSA881X_DIGITAL_BASE + 0x0030)
#घोषणा WSA881X_ATE_TEST_MODE			(WSA881X_DIGITAL_BASE + 0x0031)
#घोषणा WSA881X_PIN_CTL_MODE			(WSA881X_DIGITAL_BASE + 0x0032)
#घोषणा WSA881X_PIN_CTL_OE			(WSA881X_DIGITAL_BASE + 0x0033)
#घोषणा WSA881X_PIN_WDATA_IOPAD			(WSA881X_DIGITAL_BASE + 0x0034)
#घोषणा WSA881X_PIN_STATUS			(WSA881X_DIGITAL_BASE + 0x0035)
#घोषणा WSA881X_DIG_DEBUG_MODE			(WSA881X_DIGITAL_BASE + 0x0037)
#घोषणा WSA881X_DIG_DEBUG_SEL			(WSA881X_DIGITAL_BASE + 0x0038)
#घोषणा WSA881X_DIG_DEBUG_EN			(WSA881X_DIGITAL_BASE + 0x0039)
#घोषणा WSA881X_SWR_HM_TEST1			(WSA881X_DIGITAL_BASE + 0x003B)
#घोषणा WSA881X_SWR_HM_TEST2			(WSA881X_DIGITAL_BASE + 0x003C)
#घोषणा WSA881X_TEMP_DETECT_DBG_CTL		(WSA881X_DIGITAL_BASE + 0x003D)
#घोषणा WSA881X_TEMP_DEBUG_MSB			(WSA881X_DIGITAL_BASE + 0x003E)
#घोषणा WSA881X_TEMP_DEBUG_LSB			(WSA881X_DIGITAL_BASE + 0x003F)
#घोषणा WSA881X_SAMPLE_EDGE_SEL			(WSA881X_DIGITAL_BASE + 0x0044)
#घोषणा WSA881X_IOPAD_CTL			(WSA881X_DIGITAL_BASE + 0x0045)
#घोषणा WSA881X_SPARE_0				(WSA881X_DIGITAL_BASE + 0x0050)
#घोषणा WSA881X_SPARE_1				(WSA881X_DIGITAL_BASE + 0x0051)
#घोषणा WSA881X_SPARE_2				(WSA881X_DIGITAL_BASE + 0x0052)
#घोषणा WSA881X_OTP_REG_0			(WSA881X_DIGITAL_BASE + 0x0080)
#घोषणा WSA881X_OTP_REG_1			(WSA881X_DIGITAL_BASE + 0x0081)
#घोषणा WSA881X_OTP_REG_2			(WSA881X_DIGITAL_BASE + 0x0082)
#घोषणा WSA881X_OTP_REG_3			(WSA881X_DIGITAL_BASE + 0x0083)
#घोषणा WSA881X_OTP_REG_4			(WSA881X_DIGITAL_BASE + 0x0084)
#घोषणा WSA881X_OTP_REG_5			(WSA881X_DIGITAL_BASE + 0x0085)
#घोषणा WSA881X_OTP_REG_6			(WSA881X_DIGITAL_BASE + 0x0086)
#घोषणा WSA881X_OTP_REG_7			(WSA881X_DIGITAL_BASE + 0x0087)
#घोषणा WSA881X_OTP_REG_8			(WSA881X_DIGITAL_BASE + 0x0088)
#घोषणा WSA881X_OTP_REG_9			(WSA881X_DIGITAL_BASE + 0x0089)
#घोषणा WSA881X_OTP_REG_10			(WSA881X_DIGITAL_BASE + 0x008A)
#घोषणा WSA881X_OTP_REG_11			(WSA881X_DIGITAL_BASE + 0x008B)
#घोषणा WSA881X_OTP_REG_12			(WSA881X_DIGITAL_BASE + 0x008C)
#घोषणा WSA881X_OTP_REG_13			(WSA881X_DIGITAL_BASE + 0x008D)
#घोषणा WSA881X_OTP_REG_14			(WSA881X_DIGITAL_BASE + 0x008E)
#घोषणा WSA881X_OTP_REG_15			(WSA881X_DIGITAL_BASE + 0x008F)
#घोषणा WSA881X_OTP_REG_16			(WSA881X_DIGITAL_BASE + 0x0090)
#घोषणा WSA881X_OTP_REG_17			(WSA881X_DIGITAL_BASE + 0x0091)
#घोषणा WSA881X_OTP_REG_18			(WSA881X_DIGITAL_BASE + 0x0092)
#घोषणा WSA881X_OTP_REG_19			(WSA881X_DIGITAL_BASE + 0x0093)
#घोषणा WSA881X_OTP_REG_20			(WSA881X_DIGITAL_BASE + 0x0094)
#घोषणा WSA881X_OTP_REG_21			(WSA881X_DIGITAL_BASE + 0x0095)
#घोषणा WSA881X_OTP_REG_22			(WSA881X_DIGITAL_BASE + 0x0096)
#घोषणा WSA881X_OTP_REG_23			(WSA881X_DIGITAL_BASE + 0x0097)
#घोषणा WSA881X_OTP_REG_24			(WSA881X_DIGITAL_BASE + 0x0098)
#घोषणा WSA881X_OTP_REG_25			(WSA881X_DIGITAL_BASE + 0x0099)
#घोषणा WSA881X_OTP_REG_26			(WSA881X_DIGITAL_BASE + 0x009A)
#घोषणा WSA881X_OTP_REG_27			(WSA881X_DIGITAL_BASE + 0x009B)
#घोषणा WSA881X_OTP_REG_28			(WSA881X_DIGITAL_BASE + 0x009C)
#घोषणा WSA881X_OTP_REG_29			(WSA881X_DIGITAL_BASE + 0x009D)
#घोषणा WSA881X_OTP_REG_30			(WSA881X_DIGITAL_BASE + 0x009E)
#घोषणा WSA881X_OTP_REG_31			(WSA881X_DIGITAL_BASE + 0x009F)
#घोषणा WSA881X_OTP_REG_63			(WSA881X_DIGITAL_BASE + 0x00BF)

/* Analog Register address space */
#घोषणा WSA881X_BIAS_REF_CTRL			(WSA881X_ANALOG_BASE + 0x0000)
#घोषणा WSA881X_BIAS_TEST			(WSA881X_ANALOG_BASE + 0x0001)
#घोषणा WSA881X_BIAS_BIAS			(WSA881X_ANALOG_BASE + 0x0002)
#घोषणा WSA881X_TEMP_OP				(WSA881X_ANALOG_BASE + 0x0003)
#घोषणा WSA881X_TEMP_IREF_CTRL			(WSA881X_ANALOG_BASE + 0x0004)
#घोषणा WSA881X_TEMP_ISENS_CTRL			(WSA881X_ANALOG_BASE + 0x0005)
#घोषणा WSA881X_TEMP_CLK_CTRL			(WSA881X_ANALOG_BASE + 0x0006)
#घोषणा WSA881X_TEMP_TEST			(WSA881X_ANALOG_BASE + 0x0007)
#घोषणा WSA881X_TEMP_BIAS			(WSA881X_ANALOG_BASE + 0x0008)
#घोषणा WSA881X_TEMP_ADC_CTRL			(WSA881X_ANALOG_BASE + 0x0009)
#घोषणा WSA881X_TEMP_DOUT_MSB			(WSA881X_ANALOG_BASE + 0x000A)
#घोषणा WSA881X_TEMP_DOUT_LSB			(WSA881X_ANALOG_BASE + 0x000B)
#घोषणा WSA881X_ADC_EN_MODU_V			(WSA881X_ANALOG_BASE + 0x0010)
#घोषणा WSA881X_ADC_EN_MODU_I			(WSA881X_ANALOG_BASE + 0x0011)
#घोषणा WSA881X_ADC_EN_DET_TEST_V		(WSA881X_ANALOG_BASE + 0x0012)
#घोषणा WSA881X_ADC_EN_DET_TEST_I		(WSA881X_ANALOG_BASE + 0x0013)
#घोषणा WSA881X_ADC_SEL_IBIAS			(WSA881X_ANALOG_BASE + 0x0014)
#घोषणा WSA881X_ADC_EN_SEL_IBAIS		(WSA881X_ANALOG_BASE + 0x0015)
#घोषणा WSA881X_SPKR_DRV_EN			(WSA881X_ANALOG_BASE + 0x001A)
#घोषणा WSA881X_SPKR_DRV_GAIN			(WSA881X_ANALOG_BASE + 0x001B)
#घोषणा WSA881X_PA_GAIN_SEL_MASK		BIT(3)
#घोषणा WSA881X_PA_GAIN_SEL_REG			BIT(3)
#घोषणा WSA881X_PA_GAIN_SEL_DRE			0
#घोषणा WSA881X_SPKR_PAG_GAIN_MASK		GENMASK(7, 4)
#घोषणा WSA881X_SPKR_DAC_CTL			(WSA881X_ANALOG_BASE + 0x001C)
#घोषणा WSA881X_SPKR_DRV_DBG			(WSA881X_ANALOG_BASE + 0x001D)
#घोषणा WSA881X_SPKR_PWRSTG_DBG			(WSA881X_ANALOG_BASE + 0x001E)
#घोषणा WSA881X_SPKR_OCP_CTL			(WSA881X_ANALOG_BASE + 0x001F)
#घोषणा WSA881X_SPKR_OCP_MASK			GENMASK(7, 6)
#घोषणा WSA881X_SPKR_OCP_EN			BIT(7)
#घोषणा WSA881X_SPKR_OCP_HOLD			BIT(6)
#घोषणा WSA881X_SPKR_CLIP_CTL			(WSA881X_ANALOG_BASE + 0x0020)
#घोषणा WSA881X_SPKR_BBM_CTL			(WSA881X_ANALOG_BASE + 0x0021)
#घोषणा WSA881X_SPKR_MISC_CTL1			(WSA881X_ANALOG_BASE + 0x0022)
#घोषणा WSA881X_SPKR_MISC_CTL2			(WSA881X_ANALOG_BASE + 0x0023)
#घोषणा WSA881X_SPKR_BIAS_INT			(WSA881X_ANALOG_BASE + 0x0024)
#घोषणा WSA881X_SPKR_PA_INT			(WSA881X_ANALOG_BASE + 0x0025)
#घोषणा WSA881X_SPKR_BIAS_CAL			(WSA881X_ANALOG_BASE + 0x0026)
#घोषणा WSA881X_SPKR_BIAS_PSRR			(WSA881X_ANALOG_BASE + 0x0027)
#घोषणा WSA881X_SPKR_STATUS1			(WSA881X_ANALOG_BASE + 0x0028)
#घोषणा WSA881X_SPKR_STATUS2			(WSA881X_ANALOG_BASE + 0x0029)
#घोषणा WSA881X_BOOST_EN_CTL			(WSA881X_ANALOG_BASE + 0x002A)
#घोषणा WSA881X_BOOST_EN_MASK			BIT(7)
#घोषणा WSA881X_BOOST_EN			BIT(7)
#घोषणा WSA881X_BOOST_CURRENT_LIMIT		(WSA881X_ANALOG_BASE + 0x002B)
#घोषणा WSA881X_BOOST_PS_CTL			(WSA881X_ANALOG_BASE + 0x002C)
#घोषणा WSA881X_BOOST_PRESET_OUT1		(WSA881X_ANALOG_BASE + 0x002D)
#घोषणा WSA881X_BOOST_PRESET_OUT2		(WSA881X_ANALOG_BASE + 0x002E)
#घोषणा WSA881X_BOOST_FORCE_OUT			(WSA881X_ANALOG_BASE + 0x002F)
#घोषणा WSA881X_BOOST_LDO_PROG			(WSA881X_ANALOG_BASE + 0x0030)
#घोषणा WSA881X_BOOST_SLOPE_COMP_ISENSE_FB	(WSA881X_ANALOG_BASE + 0x0031)
#घोषणा WSA881X_BOOST_RON_CTL			(WSA881X_ANALOG_BASE + 0x0032)
#घोषणा WSA881X_BOOST_LOOP_STABILITY		(WSA881X_ANALOG_BASE + 0x0033)
#घोषणा WSA881X_BOOST_ZX_CTL			(WSA881X_ANALOG_BASE + 0x0034)
#घोषणा WSA881X_BOOST_START_CTL			(WSA881X_ANALOG_BASE + 0x0035)
#घोषणा WSA881X_BOOST_MISC1_CTL			(WSA881X_ANALOG_BASE + 0x0036)
#घोषणा WSA881X_BOOST_MISC2_CTL			(WSA881X_ANALOG_BASE + 0x0037)
#घोषणा WSA881X_BOOST_MISC3_CTL			(WSA881X_ANALOG_BASE + 0x0038)
#घोषणा WSA881X_BOOST_ATEST_CTL			(WSA881X_ANALOG_BASE + 0x0039)
#घोषणा WSA881X_SPKR_PROT_FE_GAIN		(WSA881X_ANALOG_BASE + 0x003A)
#घोषणा WSA881X_SPKR_PROT_FE_CM_LDO_SET		(WSA881X_ANALOG_BASE + 0x003B)
#घोषणा WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET1	(WSA881X_ANALOG_BASE + 0x003C)
#घोषणा WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET2	(WSA881X_ANALOG_BASE + 0x003D)
#घोषणा WSA881X_SPKR_PROT_ATEST1		(WSA881X_ANALOG_BASE + 0x003E)
#घोषणा WSA881X_SPKR_PROT_ATEST2		(WSA881X_ANALOG_BASE + 0x003F)
#घोषणा WSA881X_SPKR_PROT_FE_VSENSE_VCM		(WSA881X_ANALOG_BASE + 0x0040)
#घोषणा WSA881X_SPKR_PROT_FE_VSENSE_BIAS_SET1	(WSA881X_ANALOG_BASE + 0x0041)
#घोषणा WSA881X_BONGO_RESRV_REG1		(WSA881X_ANALOG_BASE + 0x0042)
#घोषणा WSA881X_BONGO_RESRV_REG2		(WSA881X_ANALOG_BASE + 0x0043)
#घोषणा WSA881X_SPKR_PROT_SAR			(WSA881X_ANALOG_BASE + 0x0044)
#घोषणा WSA881X_SPKR_STATUS3			(WSA881X_ANALOG_BASE + 0x0045)

#घोषणा SWRS_SCP_FRAME_CTRL_BANK(m)		(0x60 + 0x10 * (m))
#घोषणा SWRS_SCP_HOST_CLK_DIV2_CTL_BANK(m)	(0xE0 + 0x10 * (m))
#घोषणा SWR_SLV_MAX_REG_ADDR	0x390
#घोषणा SWR_SLV_START_REG_ADDR	0x40
#घोषणा SWR_SLV_MAX_BUF_LEN	20
#घोषणा BYTES_PER_LINE		12
#घोषणा SWR_SLV_RD_BUF_LEN	8
#घोषणा SWR_SLV_WR_BUF_LEN	32
#घोषणा SWR_SLV_MAX_DEVICES	2
#घोषणा WSA881X_MAX_SWR_PORTS   4
#घोषणा WSA881X_VERSION_ENTRY_SIZE 27
#घोषणा WSA881X_OCP_CTL_TIMER_SEC 2
#घोषणा WSA881X_OCP_CTL_TEMP_CELSIUS 25
#घोषणा WSA881X_OCP_CTL_POLL_TIMER_SEC 60

#घोषणा WSA881X_PA_GAIN_TLV(xname, reg, shअगरt, max, invert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = wsa881x_put_pa_gain, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण

अटल काष्ठा reg_शेष wsa881x_शेषs[] = अणु
	अणु WSA881X_CHIP_ID0, 0x00 पूर्ण,
	अणु WSA881X_CHIP_ID1, 0x00 पूर्ण,
	अणु WSA881X_CHIP_ID2, 0x00 पूर्ण,
	अणु WSA881X_CHIP_ID3, 0x02 पूर्ण,
	अणु WSA881X_BUS_ID, 0x00 पूर्ण,
	अणु WSA881X_CDC_RST_CTL, 0x00 पूर्ण,
	अणु WSA881X_CDC_TOP_CLK_CTL, 0x03 पूर्ण,
	अणु WSA881X_CDC_ANA_CLK_CTL, 0x00 पूर्ण,
	अणु WSA881X_CDC_DIG_CLK_CTL, 0x00 पूर्ण,
	अणु WSA881X_CLOCK_CONFIG, 0x00 पूर्ण,
	अणु WSA881X_ANA_CTL, 0x08 पूर्ण,
	अणु WSA881X_SWR_RESET_EN, 0x00 पूर्ण,
	अणु WSA881X_TEMP_DETECT_CTL, 0x01 पूर्ण,
	अणु WSA881X_TEMP_MSB, 0x00 पूर्ण,
	अणु WSA881X_TEMP_LSB, 0x00 पूर्ण,
	अणु WSA881X_TEMP_CONFIG0, 0x00 पूर्ण,
	अणु WSA881X_TEMP_CONFIG1, 0x00 पूर्ण,
	अणु WSA881X_CDC_CLIP_CTL, 0x03 पूर्ण,
	अणु WSA881X_SDM_PDM9_LSB, 0x00 पूर्ण,
	अणु WSA881X_SDM_PDM9_MSB, 0x00 पूर्ण,
	अणु WSA881X_CDC_RX_CTL, 0x7E पूर्ण,
	अणु WSA881X_DEM_BYPASS_DATA0, 0x00 पूर्ण,
	अणु WSA881X_DEM_BYPASS_DATA1, 0x00 पूर्ण,
	अणु WSA881X_DEM_BYPASS_DATA2, 0x00 पूर्ण,
	अणु WSA881X_DEM_BYPASS_DATA3, 0x00 पूर्ण,
	अणु WSA881X_OTP_CTRL0, 0x00 पूर्ण,
	अणु WSA881X_OTP_CTRL1, 0x00 पूर्ण,
	अणु WSA881X_HDRIVE_CTL_GROUP1, 0x00 पूर्ण,
	अणु WSA881X_INTR_MODE, 0x00 पूर्ण,
	अणु WSA881X_INTR_STATUS, 0x00 पूर्ण,
	अणु WSA881X_INTR_CLEAR, 0x00 पूर्ण,
	अणु WSA881X_INTR_LEVEL, 0x00 पूर्ण,
	अणु WSA881X_INTR_SET, 0x00 पूर्ण,
	अणु WSA881X_INTR_TEST, 0x00 पूर्ण,
	अणु WSA881X_PDM_TEST_MODE, 0x00 पूर्ण,
	अणु WSA881X_ATE_TEST_MODE, 0x00 पूर्ण,
	अणु WSA881X_PIN_CTL_MODE, 0x00 पूर्ण,
	अणु WSA881X_PIN_CTL_OE, 0x00 पूर्ण,
	अणु WSA881X_PIN_WDATA_IOPAD, 0x00 पूर्ण,
	अणु WSA881X_PIN_STATUS, 0x00 पूर्ण,
	अणु WSA881X_DIG_DEBUG_MODE, 0x00 पूर्ण,
	अणु WSA881X_DIG_DEBUG_SEL, 0x00 पूर्ण,
	अणु WSA881X_DIG_DEBUG_EN, 0x00 पूर्ण,
	अणु WSA881X_SWR_HM_TEST1, 0x08 पूर्ण,
	अणु WSA881X_SWR_HM_TEST2, 0x00 पूर्ण,
	अणु WSA881X_TEMP_DETECT_DBG_CTL, 0x00 पूर्ण,
	अणु WSA881X_TEMP_DEBUG_MSB, 0x00 पूर्ण,
	अणु WSA881X_TEMP_DEBUG_LSB, 0x00 पूर्ण,
	अणु WSA881X_SAMPLE_EDGE_SEL, 0x0C पूर्ण,
	अणु WSA881X_SPARE_0, 0x00 पूर्ण,
	अणु WSA881X_SPARE_1, 0x00 पूर्ण,
	अणु WSA881X_SPARE_2, 0x00 पूर्ण,
	अणु WSA881X_OTP_REG_0, 0x01 पूर्ण,
	अणु WSA881X_OTP_REG_1, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_2, 0xC0 पूर्ण,
	अणु WSA881X_OTP_REG_3, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_4, 0xC0 पूर्ण,
	अणु WSA881X_OTP_REG_5, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_6, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_7, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_8, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_9, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_10, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_11, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_12, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_13, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_14, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_15, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_16, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_17, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_18, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_19, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_20, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_21, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_22, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_23, 0xFF पूर्ण,
	अणु WSA881X_OTP_REG_24, 0x03 पूर्ण,
	अणु WSA881X_OTP_REG_25, 0x01 पूर्ण,
	अणु WSA881X_OTP_REG_26, 0x03 पूर्ण,
	अणु WSA881X_OTP_REG_27, 0x11 पूर्ण,
	अणु WSA881X_OTP_REG_63, 0x40 पूर्ण,
	/* WSA881x Analog रेजिस्टरs */
	अणु WSA881X_BIAS_REF_CTRL, 0x6C पूर्ण,
	अणु WSA881X_BIAS_TEST, 0x16 पूर्ण,
	अणु WSA881X_BIAS_BIAS, 0xF0 पूर्ण,
	अणु WSA881X_TEMP_OP, 0x00 पूर्ण,
	अणु WSA881X_TEMP_IREF_CTRL, 0x56 पूर्ण,
	अणु WSA881X_TEMP_ISENS_CTRL, 0x47 पूर्ण,
	अणु WSA881X_TEMP_CLK_CTRL, 0x87 पूर्ण,
	अणु WSA881X_TEMP_TEST, 0x00 पूर्ण,
	अणु WSA881X_TEMP_BIAS, 0x51 पूर्ण,
	अणु WSA881X_TEMP_DOUT_MSB, 0x00 पूर्ण,
	अणु WSA881X_TEMP_DOUT_LSB, 0x00 पूर्ण,
	अणु WSA881X_ADC_EN_MODU_V, 0x00 पूर्ण,
	अणु WSA881X_ADC_EN_MODU_I, 0x00 पूर्ण,
	अणु WSA881X_ADC_EN_DET_TEST_V, 0x00 पूर्ण,
	अणु WSA881X_ADC_EN_DET_TEST_I, 0x00 पूर्ण,
	अणु WSA881X_ADC_EN_SEL_IBAIS, 0x10 पूर्ण,
	अणु WSA881X_SPKR_DRV_EN, 0x74 पूर्ण,
	अणु WSA881X_SPKR_DRV_DBG, 0x15 पूर्ण,
	अणु WSA881X_SPKR_PWRSTG_DBG, 0x00 पूर्ण,
	अणु WSA881X_SPKR_OCP_CTL, 0xD4 पूर्ण,
	अणु WSA881X_SPKR_CLIP_CTL, 0x90 पूर्ण,
	अणु WSA881X_SPKR_PA_INT, 0x54 पूर्ण,
	अणु WSA881X_SPKR_BIAS_CAL, 0xAC पूर्ण,
	अणु WSA881X_SPKR_STATUS1, 0x00 पूर्ण,
	अणु WSA881X_SPKR_STATUS2, 0x00 पूर्ण,
	अणु WSA881X_BOOST_EN_CTL, 0x18 पूर्ण,
	अणु WSA881X_BOOST_CURRENT_LIMIT, 0x7A पूर्ण,
	अणु WSA881X_BOOST_PRESET_OUT2, 0x70 पूर्ण,
	अणु WSA881X_BOOST_FORCE_OUT, 0x0E पूर्ण,
	अणु WSA881X_BOOST_LDO_PROG, 0x16 पूर्ण,
	अणु WSA881X_BOOST_SLOPE_COMP_ISENSE_FB, 0x71 पूर्ण,
	अणु WSA881X_BOOST_RON_CTL, 0x0F पूर्ण,
	अणु WSA881X_BOOST_ZX_CTL, 0x34 पूर्ण,
	अणु WSA881X_BOOST_START_CTL, 0x23 पूर्ण,
	अणु WSA881X_BOOST_MISC1_CTL, 0x80 पूर्ण,
	अणु WSA881X_BOOST_MISC2_CTL, 0x00 पूर्ण,
	अणु WSA881X_BOOST_MISC3_CTL, 0x00 पूर्ण,
	अणु WSA881X_BOOST_ATEST_CTL, 0x00 पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_GAIN, 0x46 पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_CM_LDO_SET, 0x3B पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET1, 0x8D पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET2, 0x8D पूर्ण,
	अणु WSA881X_SPKR_PROT_ATEST1, 0x01 पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_VSENSE_VCM, 0x8D पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_VSENSE_BIAS_SET1, 0x4D पूर्ण,
	अणु WSA881X_SPKR_PROT_SAR, 0x00 पूर्ण,
	अणु WSA881X_SPKR_STATUS3, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wsa881x_pre_pmu_pa_2_0[] = अणु
	अणु WSA881X_SPKR_DRV_GAIN, 0x41, 0 पूर्ण,
	अणु WSA881X_SPKR_MISC_CTL1, 0x87, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence wsa881x_vi_txfe_en_2_0[] = अणु
	अणु WSA881X_SPKR_PROT_FE_VSENSE_VCM, 0x85, 0 पूर्ण,
	अणु WSA881X_SPKR_PROT_ATEST2, 0x0A, 0 पूर्ण,
	अणु WSA881X_SPKR_PROT_FE_GAIN, 0x47, 0 पूर्ण,
पूर्ण;

/* Default रेजिस्टर reset values क्रम WSA881x rev 2.0 */
अटल काष्ठा reg_sequence wsa881x_rev_2_0[] = अणु
	अणु WSA881X_RESET_CTL, 0x00, 0x00 पूर्ण,
	अणु WSA881X_TADC_VALUE_CTL, 0x01, 0x00 पूर्ण,
	अणु WSA881X_INTR_MASK, 0x1B, 0x00 पूर्ण,
	अणु WSA881X_IOPAD_CTL, 0x00, 0x00 पूर्ण,
	अणु WSA881X_OTP_REG_28, 0x3F, 0x00 पूर्ण,
	अणु WSA881X_OTP_REG_29, 0x3F, 0x00 पूर्ण,
	अणु WSA881X_OTP_REG_30, 0x01, 0x00 पूर्ण,
	अणु WSA881X_OTP_REG_31, 0x01, 0x00 पूर्ण,
	अणु WSA881X_TEMP_ADC_CTRL, 0x03, 0x00 पूर्ण,
	अणु WSA881X_ADC_SEL_IBIAS, 0x45, 0x00 पूर्ण,
	अणु WSA881X_SPKR_DRV_GAIN, 0xC1, 0x00 पूर्ण,
	अणु WSA881X_SPKR_DAC_CTL, 0x42, 0x00 पूर्ण,
	अणु WSA881X_SPKR_BBM_CTL, 0x02, 0x00 पूर्ण,
	अणु WSA881X_SPKR_MISC_CTL1, 0x40, 0x00 पूर्ण,
	अणु WSA881X_SPKR_MISC_CTL2, 0x07, 0x00 पूर्ण,
	अणु WSA881X_SPKR_BIAS_INT, 0x5F, 0x00 पूर्ण,
	अणु WSA881X_SPKR_BIAS_PSRR, 0x44, 0x00 पूर्ण,
	अणु WSA881X_BOOST_PS_CTL, 0xA0, 0x00 पूर्ण,
	अणु WSA881X_BOOST_PRESET_OUT1, 0xB7, 0x00 पूर्ण,
	अणु WSA881X_BOOST_LOOP_STABILITY, 0x8D, 0x00 पूर्ण,
	अणु WSA881X_SPKR_PROT_ATEST2, 0x02, 0x00 पूर्ण,
	अणु WSA881X_BONGO_RESRV_REG1, 0x5E, 0x00 पूर्ण,
	अणु WSA881X_BONGO_RESRV_REG2, 0x07, 0x00 पूर्ण,
पूर्ण;

क्रमागत wsa_port_ids अणु
	WSA881X_PORT_DAC,
	WSA881X_PORT_COMP,
	WSA881X_PORT_BOOST,
	WSA881X_PORT_VISENSE,
पूर्ण;

/* 4 ports */
अटल काष्ठा sdw_dpn_prop wsa_sink_dpn_prop[WSA881X_MAX_SWR_PORTS] = अणु
	अणु
		/* DAC */
		.num = 1,
		.type = SDW_DPN_SIMPLE,
		.min_ch = 1,
		.max_ch = 1,
		.simple_ch_prep_sm = true,
		.पढ़ो_only_wordlength = true,
	पूर्ण, अणु
		/* COMP */
		.num = 2,
		.type = SDW_DPN_SIMPLE,
		.min_ch = 1,
		.max_ch = 1,
		.simple_ch_prep_sm = true,
		.पढ़ो_only_wordlength = true,
	पूर्ण, अणु
		/* BOOST */
		.num = 3,
		.type = SDW_DPN_SIMPLE,
		.min_ch = 1,
		.max_ch = 1,
		.simple_ch_prep_sm = true,
		.पढ़ो_only_wordlength = true,
	पूर्ण, अणु
		/* VISENSE */
		.num = 4,
		.type = SDW_DPN_SIMPLE,
		.min_ch = 1,
		.max_ch = 1,
		.simple_ch_prep_sm = true,
		.पढ़ो_only_wordlength = true,
	पूर्ण
पूर्ण;

अटल काष्ठा sdw_port_config wsa881x_pconfig[WSA881X_MAX_SWR_PORTS] = अणु
	अणु
		.num = 1,
		.ch_mask = 0x1,
	पूर्ण, अणु
		.num = 2,
		.ch_mask = 0xf,
	पूर्ण, अणु
		.num = 3,
		.ch_mask = 0x3,
	पूर्ण, अणु	/* IV feedback */
		.num = 4,
		.ch_mask = 0x3,
	पूर्ण,
पूर्ण;

अटल bool wsa881x_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WSA881X_CHIP_ID0:
	हाल WSA881X_CHIP_ID1:
	हाल WSA881X_CHIP_ID2:
	हाल WSA881X_CHIP_ID3:
	हाल WSA881X_BUS_ID:
	हाल WSA881X_CDC_RST_CTL:
	हाल WSA881X_CDC_TOP_CLK_CTL:
	हाल WSA881X_CDC_ANA_CLK_CTL:
	हाल WSA881X_CDC_DIG_CLK_CTL:
	हाल WSA881X_CLOCK_CONFIG:
	हाल WSA881X_ANA_CTL:
	हाल WSA881X_SWR_RESET_EN:
	हाल WSA881X_RESET_CTL:
	हाल WSA881X_TADC_VALUE_CTL:
	हाल WSA881X_TEMP_DETECT_CTL:
	हाल WSA881X_TEMP_MSB:
	हाल WSA881X_TEMP_LSB:
	हाल WSA881X_TEMP_CONFIG0:
	हाल WSA881X_TEMP_CONFIG1:
	हाल WSA881X_CDC_CLIP_CTL:
	हाल WSA881X_SDM_PDM9_LSB:
	हाल WSA881X_SDM_PDM9_MSB:
	हाल WSA881X_CDC_RX_CTL:
	हाल WSA881X_DEM_BYPASS_DATA0:
	हाल WSA881X_DEM_BYPASS_DATA1:
	हाल WSA881X_DEM_BYPASS_DATA2:
	हाल WSA881X_DEM_BYPASS_DATA3:
	हाल WSA881X_OTP_CTRL0:
	हाल WSA881X_OTP_CTRL1:
	हाल WSA881X_HDRIVE_CTL_GROUP1:
	हाल WSA881X_INTR_MODE:
	हाल WSA881X_INTR_MASK:
	हाल WSA881X_INTR_STATUS:
	हाल WSA881X_INTR_CLEAR:
	हाल WSA881X_INTR_LEVEL:
	हाल WSA881X_INTR_SET:
	हाल WSA881X_INTR_TEST:
	हाल WSA881X_PDM_TEST_MODE:
	हाल WSA881X_ATE_TEST_MODE:
	हाल WSA881X_PIN_CTL_MODE:
	हाल WSA881X_PIN_CTL_OE:
	हाल WSA881X_PIN_WDATA_IOPAD:
	हाल WSA881X_PIN_STATUS:
	हाल WSA881X_DIG_DEBUG_MODE:
	हाल WSA881X_DIG_DEBUG_SEL:
	हाल WSA881X_DIG_DEBUG_EN:
	हाल WSA881X_SWR_HM_TEST1:
	हाल WSA881X_SWR_HM_TEST2:
	हाल WSA881X_TEMP_DETECT_DBG_CTL:
	हाल WSA881X_TEMP_DEBUG_MSB:
	हाल WSA881X_TEMP_DEBUG_LSB:
	हाल WSA881X_SAMPLE_EDGE_SEL:
	हाल WSA881X_IOPAD_CTL:
	हाल WSA881X_SPARE_0:
	हाल WSA881X_SPARE_1:
	हाल WSA881X_SPARE_2:
	हाल WSA881X_OTP_REG_0:
	हाल WSA881X_OTP_REG_1:
	हाल WSA881X_OTP_REG_2:
	हाल WSA881X_OTP_REG_3:
	हाल WSA881X_OTP_REG_4:
	हाल WSA881X_OTP_REG_5:
	हाल WSA881X_OTP_REG_6:
	हाल WSA881X_OTP_REG_7:
	हाल WSA881X_OTP_REG_8:
	हाल WSA881X_OTP_REG_9:
	हाल WSA881X_OTP_REG_10:
	हाल WSA881X_OTP_REG_11:
	हाल WSA881X_OTP_REG_12:
	हाल WSA881X_OTP_REG_13:
	हाल WSA881X_OTP_REG_14:
	हाल WSA881X_OTP_REG_15:
	हाल WSA881X_OTP_REG_16:
	हाल WSA881X_OTP_REG_17:
	हाल WSA881X_OTP_REG_18:
	हाल WSA881X_OTP_REG_19:
	हाल WSA881X_OTP_REG_20:
	हाल WSA881X_OTP_REG_21:
	हाल WSA881X_OTP_REG_22:
	हाल WSA881X_OTP_REG_23:
	हाल WSA881X_OTP_REG_24:
	हाल WSA881X_OTP_REG_25:
	हाल WSA881X_OTP_REG_26:
	हाल WSA881X_OTP_REG_27:
	हाल WSA881X_OTP_REG_28:
	हाल WSA881X_OTP_REG_29:
	हाल WSA881X_OTP_REG_30:
	हाल WSA881X_OTP_REG_31:
	हाल WSA881X_OTP_REG_63:
	हाल WSA881X_BIAS_REF_CTRL:
	हाल WSA881X_BIAS_TEST:
	हाल WSA881X_BIAS_BIAS:
	हाल WSA881X_TEMP_OP:
	हाल WSA881X_TEMP_IREF_CTRL:
	हाल WSA881X_TEMP_ISENS_CTRL:
	हाल WSA881X_TEMP_CLK_CTRL:
	हाल WSA881X_TEMP_TEST:
	हाल WSA881X_TEMP_BIAS:
	हाल WSA881X_TEMP_ADC_CTRL:
	हाल WSA881X_TEMP_DOUT_MSB:
	हाल WSA881X_TEMP_DOUT_LSB:
	हाल WSA881X_ADC_EN_MODU_V:
	हाल WSA881X_ADC_EN_MODU_I:
	हाल WSA881X_ADC_EN_DET_TEST_V:
	हाल WSA881X_ADC_EN_DET_TEST_I:
	हाल WSA881X_ADC_SEL_IBIAS:
	हाल WSA881X_ADC_EN_SEL_IBAIS:
	हाल WSA881X_SPKR_DRV_EN:
	हाल WSA881X_SPKR_DRV_GAIN:
	हाल WSA881X_SPKR_DAC_CTL:
	हाल WSA881X_SPKR_DRV_DBG:
	हाल WSA881X_SPKR_PWRSTG_DBG:
	हाल WSA881X_SPKR_OCP_CTL:
	हाल WSA881X_SPKR_CLIP_CTL:
	हाल WSA881X_SPKR_BBM_CTL:
	हाल WSA881X_SPKR_MISC_CTL1:
	हाल WSA881X_SPKR_MISC_CTL2:
	हाल WSA881X_SPKR_BIAS_INT:
	हाल WSA881X_SPKR_PA_INT:
	हाल WSA881X_SPKR_BIAS_CAL:
	हाल WSA881X_SPKR_BIAS_PSRR:
	हाल WSA881X_SPKR_STATUS1:
	हाल WSA881X_SPKR_STATUS2:
	हाल WSA881X_BOOST_EN_CTL:
	हाल WSA881X_BOOST_CURRENT_LIMIT:
	हाल WSA881X_BOOST_PS_CTL:
	हाल WSA881X_BOOST_PRESET_OUT1:
	हाल WSA881X_BOOST_PRESET_OUT2:
	हाल WSA881X_BOOST_FORCE_OUT:
	हाल WSA881X_BOOST_LDO_PROG:
	हाल WSA881X_BOOST_SLOPE_COMP_ISENSE_FB:
	हाल WSA881X_BOOST_RON_CTL:
	हाल WSA881X_BOOST_LOOP_STABILITY:
	हाल WSA881X_BOOST_ZX_CTL:
	हाल WSA881X_BOOST_START_CTL:
	हाल WSA881X_BOOST_MISC1_CTL:
	हाल WSA881X_BOOST_MISC2_CTL:
	हाल WSA881X_BOOST_MISC3_CTL:
	हाल WSA881X_BOOST_ATEST_CTL:
	हाल WSA881X_SPKR_PROT_FE_GAIN:
	हाल WSA881X_SPKR_PROT_FE_CM_LDO_SET:
	हाल WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET1:
	हाल WSA881X_SPKR_PROT_FE_ISENSE_BIAS_SET2:
	हाल WSA881X_SPKR_PROT_ATEST1:
	हाल WSA881X_SPKR_PROT_ATEST2:
	हाल WSA881X_SPKR_PROT_FE_VSENSE_VCM:
	हाल WSA881X_SPKR_PROT_FE_VSENSE_BIAS_SET1:
	हाल WSA881X_BONGO_RESRV_REG1:
	हाल WSA881X_BONGO_RESRV_REG2:
	हाल WSA881X_SPKR_PROT_SAR:
	हाल WSA881X_SPKR_STATUS3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wsa881x_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WSA881X_CHIP_ID0:
	हाल WSA881X_CHIP_ID1:
	हाल WSA881X_CHIP_ID2:
	हाल WSA881X_CHIP_ID3:
	हाल WSA881X_BUS_ID:
	हाल WSA881X_TEMP_MSB:
	हाल WSA881X_TEMP_LSB:
	हाल WSA881X_SDM_PDM9_LSB:
	हाल WSA881X_SDM_PDM9_MSB:
	हाल WSA881X_OTP_CTRL1:
	हाल WSA881X_INTR_STATUS:
	हाल WSA881X_ATE_TEST_MODE:
	हाल WSA881X_PIN_STATUS:
	हाल WSA881X_SWR_HM_TEST2:
	हाल WSA881X_SPKR_STATUS1:
	हाल WSA881X_SPKR_STATUS2:
	हाल WSA881X_SPKR_STATUS3:
	हाल WSA881X_OTP_REG_0:
	हाल WSA881X_OTP_REG_1:
	हाल WSA881X_OTP_REG_2:
	हाल WSA881X_OTP_REG_3:
	हाल WSA881X_OTP_REG_4:
	हाल WSA881X_OTP_REG_5:
	हाल WSA881X_OTP_REG_31:
	हाल WSA881X_TEMP_DOUT_MSB:
	हाल WSA881X_TEMP_DOUT_LSB:
	हाल WSA881X_TEMP_OP:
	हाल WSA881X_SPKR_PROT_SAR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा regmap_config wsa881x_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wsa881x_शेषs,
	.max_रेजिस्टर = WSA881X_SPKR_STATUS3,
	.num_reg_शेषs = ARRAY_SIZE(wsa881x_शेषs),
	.अस्थिर_reg = wsa881x_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = wsa881x_पढ़ोable_रेजिस्टर,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_NATIVE,
	.can_multi_ग_लिखो = true,
पूर्ण;

क्रमागत अणु
	G_18DB = 0,
	G_16P5DB,
	G_15DB,
	G_13P5DB,
	G_12DB,
	G_10P5DB,
	G_9DB,
	G_7P5DB,
	G_6DB,
	G_4P5DB,
	G_3DB,
	G_1P5DB,
	G_0DB,
पूर्ण;

/*
 * Private data Structure क्रम wsa881x. All parameters related to
 * WSA881X codec needs to be defined here.
 */
काष्ठा wsa881x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा sdw_slave *slave;
	काष्ठा sdw_stream_config sconfig;
	काष्ठा sdw_stream_runसमय *srunसमय;
	काष्ठा sdw_port_config port_config[WSA881X_MAX_SWR_PORTS];
	काष्ठा gpio_desc *sd_n;
	पूर्णांक version;
	पूर्णांक active_ports;
	bool port_prepared[WSA881X_MAX_SWR_PORTS];
	bool port_enable[WSA881X_MAX_SWR_PORTS];
पूर्ण;

अटल व्योम wsa881x_init(काष्ठा wsa881x_priv *wsa881x)
अणु
	काष्ठा regmap *rm = wsa881x->regmap;
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(rm, WSA881X_CHIP_ID1, &wsa881x->version);
	regmap_रेजिस्टर_patch(wsa881x->regmap, wsa881x_rev_2_0,
			      ARRAY_SIZE(wsa881x_rev_2_0));

	/* Enable software reset output from soundwire slave */
	regmap_update_bits(rm, WSA881X_SWR_RESET_EN, 0x07, 0x07);

	/* Bring out of analog reset */
	regmap_update_bits(rm, WSA881X_CDC_RST_CTL, 0x02, 0x02);

	/* Bring out of digital reset */
	regmap_update_bits(rm, WSA881X_CDC_RST_CTL, 0x01, 0x01);
	regmap_update_bits(rm, WSA881X_CLOCK_CONFIG, 0x10, 0x10);
	regmap_update_bits(rm, WSA881X_SPKR_OCP_CTL, 0x02, 0x02);
	regmap_update_bits(rm, WSA881X_SPKR_MISC_CTL1, 0xC0, 0x80);
	regmap_update_bits(rm, WSA881X_SPKR_MISC_CTL1, 0x06, 0x06);
	regmap_update_bits(rm, WSA881X_SPKR_BIAS_INT, 0xFF, 0x00);
	regmap_update_bits(rm, WSA881X_SPKR_PA_INT, 0xF0, 0x40);
	regmap_update_bits(rm, WSA881X_SPKR_PA_INT, 0x0E, 0x0E);
	regmap_update_bits(rm, WSA881X_BOOST_LOOP_STABILITY, 0x03, 0x03);
	regmap_update_bits(rm, WSA881X_BOOST_MISC2_CTL, 0xFF, 0x14);
	regmap_update_bits(rm, WSA881X_BOOST_START_CTL, 0x80, 0x80);
	regmap_update_bits(rm, WSA881X_BOOST_START_CTL, 0x03, 0x00);
	regmap_update_bits(rm, WSA881X_BOOST_SLOPE_COMP_ISENSE_FB, 0x0C, 0x04);
	regmap_update_bits(rm, WSA881X_BOOST_SLOPE_COMP_ISENSE_FB, 0x03, 0x00);

	regmap_पढ़ो(rm, WSA881X_OTP_REG_0, &val);
	अगर (val)
		regmap_update_bits(rm, WSA881X_BOOST_PRESET_OUT1, 0xF0, 0x70);

	regmap_update_bits(rm, WSA881X_BOOST_PRESET_OUT2, 0xF0, 0x30);
	regmap_update_bits(rm, WSA881X_SPKR_DRV_EN, 0x08, 0x08);
	regmap_update_bits(rm, WSA881X_BOOST_CURRENT_LIMIT, 0x0F, 0x08);
	regmap_update_bits(rm, WSA881X_SPKR_OCP_CTL, 0x30, 0x30);
	regmap_update_bits(rm, WSA881X_SPKR_OCP_CTL, 0x0C, 0x00);
	regmap_update_bits(rm, WSA881X_OTP_REG_28, 0x3F, 0x3A);
	regmap_update_bits(rm, WSA881X_BONGO_RESRV_REG1, 0xFF, 0xB2);
	regmap_update_bits(rm, WSA881X_BONGO_RESRV_REG2, 0xFF, 0x05);
पूर्ण

अटल पूर्णांक wsa881x_component_probe(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा wsa881x_priv *wsa881x = snd_soc_component_get_drvdata(comp);

	snd_soc_component_init_regmap(comp, wsa881x->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_put_pa_gain(काष्ठा snd_kcontrol *kc,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kc);
	काष्ठा soc_mixer_control *mc =
			(काष्ठा soc_mixer_control *)kc->निजी_value;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	पूर्णांक val, ret, min_gain, max_gain;

	max_gain = (max - ucontrol->value.पूर्णांकeger.value[0]) & mask;
	/*
	 * Gain has to set incrementally in 4 steps
	 * as per HW sequence
	 */
	अगर (max_gain > G_4P5DB)
		min_gain = G_0DB;
	अन्यथा
		min_gain = max_gain + 3;
	/*
	 * 1ms delay is needed beक्रमe change in gain
	 * as per HW requirement.
	 */
	usleep_range(1000, 1010);

	क्रम (val = min_gain; max_gain <= val; val--) अणु
		ret = snd_soc_component_update_bits(comp,
			      WSA881X_SPKR_DRV_GAIN,
			      WSA881X_SPKR_PAG_GAIN_MASK,
			      val << 4);
		अगर (ret < 0)
			dev_err(comp->dev, "Failed to change PA gain");

		usleep_range(1000, 1010);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_get_port(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa881x_priv *data = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_mixer_control *mixer =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक portidx = mixer->reg;

	ucontrol->value.पूर्णांकeger.value[0] = data->port_enable[portidx];


	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_boost_ctrl(काष्ठा snd_soc_component *comp, bool enable)
अणु
	अगर (enable)
		snd_soc_component_update_bits(comp, WSA881X_BOOST_EN_CTL,
					      WSA881X_BOOST_EN_MASK,
					      WSA881X_BOOST_EN);
	अन्यथा
		snd_soc_component_update_bits(comp, WSA881X_BOOST_EN_CTL,
					      WSA881X_BOOST_EN_MASK, 0);
	/*
	 * 1.5ms sleep is needed after boost enable/disable as per
	 * HW requirement
	 */
	usleep_range(1500, 1510);
	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_set_port(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wsa881x_priv *data = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_mixer_control *mixer =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक portidx = mixer->reg;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		data->port_enable[portidx] = true;
	अन्यथा
		data->port_enable[portidx] = false;

	अगर (portidx == WSA881X_PORT_BOOST) /* Boost Switch */
		wsa881x_boost_ctrl(comp, data->port_enable[portidx]);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर smart_boost_lvl_text[] = अणु
	"6.625 V", "6.750 V", "6.875 V", "7.000 V",
	"7.125 V", "7.250 V", "7.375 V", "7.500 V",
	"7.625 V", "7.750 V", "7.875 V", "8.000 V",
	"8.125 V", "8.250 V", "8.375 V", "8.500 V"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत smart_boost_lvl_क्रमागत =
	SOC_ENUM_SINGLE(WSA881X_BOOST_PRESET_OUT1, 0,
			ARRAY_SIZE(smart_boost_lvl_text),
			smart_boost_lvl_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(pa_gain, 0, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wsa881x_snd_controls[] = अणु
	SOC_ENUM("Smart Boost Level", smart_boost_lvl_क्रमागत),
	WSA881X_PA_GAIN_TLV("PA Volume", WSA881X_SPKR_DRV_GAIN,
			    4, 0xC, 1, pa_gain),
	SOC_SINGLE_EXT("DAC Switch", WSA881X_PORT_DAC, 0, 1, 0,
		       wsa881x_get_port, wsa881x_set_port),
	SOC_SINGLE_EXT("COMP Switch", WSA881X_PORT_COMP, 0, 1, 0,
		       wsa881x_get_port, wsa881x_set_port),
	SOC_SINGLE_EXT("BOOST Switch", WSA881X_PORT_BOOST, 0, 1, 0,
		       wsa881x_get_port, wsa881x_set_port),
	SOC_SINGLE_EXT("VISENSE Switch", WSA881X_PORT_VISENSE, 0, 1, 0,
		       wsa881x_get_port, wsa881x_set_port),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wsa881x_audio_map[] = अणु
	अणु "RDAC", शून्य, "IN" पूर्ण,
	अणु "RDAC", शून्य, "DCLK" पूर्ण,
	अणु "RDAC", शून्य, "ACLK" पूर्ण,
	अणु "RDAC", शून्य, "Bandgap" पूर्ण,
	अणु "SPKR PGA", शून्य, "RDAC" पूर्ण,
	अणु "SPKR", शून्य, "SPKR PGA" पूर्ण,
पूर्ण;

अटल पूर्णांक wsa881x_visense_txfe_ctrl(काष्ठा snd_soc_component *comp,
				     bool enable)
अणु
	काष्ठा wsa881x_priv *wsa881x = snd_soc_component_get_drvdata(comp);

	अगर (enable) अणु
		regmap_multi_reg_ग_लिखो(wsa881x->regmap, wsa881x_vi_txfe_en_2_0,
				       ARRAY_SIZE(wsa881x_vi_txfe_en_2_0));
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(comp,
					      WSA881X_SPKR_PROT_FE_VSENSE_VCM,
					      0x08, 0x08);
		/*
		 * 200us sleep is needed after visense txfe disable as per
		 * HW requirement.
		 */
		usleep_range(200, 210);
		snd_soc_component_update_bits(comp, WSA881X_SPKR_PROT_FE_GAIN,
					      0x01, 0x00);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_visense_adc_ctrl(काष्ठा snd_soc_component *comp,
				    bool enable)
अणु
	snd_soc_component_update_bits(comp, WSA881X_ADC_EN_MODU_V, BIT(7),
				      (enable << 7));
	snd_soc_component_update_bits(comp, WSA881X_ADC_EN_MODU_I, BIT(7),
				      (enable << 7));
	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_spkr_pa_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wsa881x_priv *wsa881x = snd_soc_component_get_drvdata(comp);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(comp, WSA881X_SPKR_OCP_CTL,
					      WSA881X_SPKR_OCP_MASK,
					      WSA881X_SPKR_OCP_EN);
		regmap_multi_reg_ग_लिखो(wsa881x->regmap, wsa881x_pre_pmu_pa_2_0,
				       ARRAY_SIZE(wsa881x_pre_pmu_pa_2_0));

		snd_soc_component_update_bits(comp, WSA881X_SPKR_DRV_GAIN,
					      WSA881X_PA_GAIN_SEL_MASK,
					      WSA881X_PA_GAIN_SEL_REG);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (wsa881x->port_prepared[WSA881X_PORT_VISENSE]) अणु
			wsa881x_visense_txfe_ctrl(comp, true);
			snd_soc_component_update_bits(comp,
						      WSA881X_ADC_EN_SEL_IBAIS,
						      0x07, 0x01);
			wsa881x_visense_adc_ctrl(comp, true);
		पूर्ण

		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (wsa881x->port_prepared[WSA881X_PORT_VISENSE]) अणु
			wsa881x_visense_adc_ctrl(comp, false);
			wsa881x_visense_txfe_ctrl(comp, false);
		पूर्ण

		snd_soc_component_update_bits(comp, WSA881X_SPKR_OCP_CTL,
					      WSA881X_SPKR_OCP_MASK,
					      WSA881X_SPKR_OCP_EN |
					      WSA881X_SPKR_OCP_HOLD);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wsa881x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("IN"),
	SND_SOC_DAPM_DAC_E("RDAC", शून्य, WSA881X_SPKR_DAC_CTL, 7, 0,
			   शून्य,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("SPKR PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
			   wsa881x_spkr_pa_event, SND_SOC_DAPM_PRE_PMU |
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("DCLK", WSA881X_CDC_DIG_CLK_CTL, 0, 0, शून्य,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("ACLK", WSA881X_CDC_ANA_CLK_CTL, 0, 0, शून्य,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("Bandgap", WSA881X_TEMP_OP, 3, 0,
			    शून्य,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("SPKR"),
पूर्ण;

अटल पूर्णांक wsa881x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(dai->dev);
	पूर्णांक i;

	wsa881x->active_ports = 0;
	क्रम (i = 0; i < WSA881X_MAX_SWR_PORTS; i++) अणु
		अगर (!wsa881x->port_enable[i])
			जारी;

		wsa881x->port_config[wsa881x->active_ports] =
							wsa881x_pconfig[i];
		wsa881x->active_ports++;
	पूर्ण

	वापस sdw_stream_add_slave(wsa881x->slave, &wsa881x->sconfig,
				    wsa881x->port_config, wsa881x->active_ports,
				    wsa881x->srunसमय);
पूर्ण

अटल पूर्णांक wsa881x_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(dai->dev);

	sdw_stream_हटाओ_slave(wsa881x->slave, wsa881x->srunसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				  व्योम *stream, पूर्णांक direction)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(dai->dev);

	wsa881x->srunसमय = stream;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(dai->dev);

	अगर (mute)
		regmap_update_bits(wsa881x->regmap, WSA881X_SPKR_DRV_EN, 0x80,
				   0x00);
	अन्यथा
		regmap_update_bits(wsa881x->regmap, WSA881X_SPKR_DRV_EN, 0x80,
				   0x80);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops wsa881x_dai_ops = अणु
	.hw_params = wsa881x_hw_params,
	.hw_मुक्त = wsa881x_hw_मुक्त,
	.mute_stream = wsa881x_digital_mute,
	.set_sdw_stream = wsa881x_set_sdw_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wsa881x_dais[] = अणु
	अणु
		.name = "SPKR",
		.id = 0,
		.playback = अणु
			.stream_name = "SPKR Playback",
			.rates = SNDRV_PCM_RATE_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.rate_max = 48000,
			.rate_min = 48000,
			.channels_min = 1,
			.channels_max = 1,
		पूर्ण,
		.ops = &wsa881x_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver wsa881x_component_drv = अणु
	.name = "WSA881x",
	.probe = wsa881x_component_probe,
	.controls = wsa881x_snd_controls,
	.num_controls = ARRAY_SIZE(wsa881x_snd_controls),
	.dapm_widमाला_लो = wsa881x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wsa881x_dapm_widमाला_लो),
	.dapm_routes = wsa881x_audio_map,
	.num_dapm_routes = ARRAY_SIZE(wsa881x_audio_map),
पूर्ण;

अटल पूर्णांक wsa881x_update_status(काष्ठा sdw_slave *slave,
				 क्रमागत sdw_slave_status status)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(&slave->dev);

	अगर (status == SDW_SLAVE_ATTACHED && slave->dev_num > 0)
		wsa881x_init(wsa881x);

	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_port_prep(काष्ठा sdw_slave *slave,
			     काष्ठा sdw_prepare_ch *prepare_ch,
			     क्रमागत sdw_port_prep_ops state)
अणु
	काष्ठा wsa881x_priv *wsa881x = dev_get_drvdata(&slave->dev);

	अगर (state == SDW_OPS_PORT_POST_PREP)
		wsa881x->port_prepared[prepare_ch->num - 1] = true;
	अन्यथा
		wsa881x->port_prepared[prepare_ch->num - 1] = false;

	वापस 0;
पूर्ण

अटल पूर्णांक wsa881x_bus_config(काष्ठा sdw_slave *slave,
			      काष्ठा sdw_bus_params *params)
अणु
	sdw_ग_लिखो(slave, SWRS_SCP_HOST_CLK_DIV2_CTL_BANK(params->next_bank),
		  0x01);

	वापस 0;
पूर्ण

अटल काष्ठा sdw_slave_ops wsa881x_slave_ops = अणु
	.update_status = wsa881x_update_status,
	.bus_config = wsa881x_bus_config,
	.port_prep = wsa881x_port_prep,
पूर्ण;

अटल पूर्णांक wsa881x_probe(काष्ठा sdw_slave *pdev,
			 स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा wsa881x_priv *wsa881x;

	wsa881x = devm_kzalloc(&pdev->dev, माप(*wsa881x), GFP_KERNEL);
	अगर (!wsa881x)
		वापस -ENOMEM;

	wsa881x->sd_n = devm_gpiod_get_optional(&pdev->dev, "powerdown",
						GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(wsa881x->sd_n)) अणु
		dev_err(&pdev->dev, "Shutdown Control GPIO not found\n");
		वापस PTR_ERR(wsa881x->sd_n);
	पूर्ण

	dev_set_drvdata(&pdev->dev, wsa881x);
	wsa881x->slave = pdev;
	wsa881x->dev = &pdev->dev;
	wsa881x->sconfig.ch_count = 1;
	wsa881x->sconfig.bps = 1;
	wsa881x->sconfig.frame_rate = 48000;
	wsa881x->sconfig.direction = SDW_DATA_सूची_RX;
	wsa881x->sconfig.type = SDW_STREAM_PDM;
	pdev->prop.sink_ports = GENMASK(WSA881X_MAX_SWR_PORTS, 0);
	pdev->prop.sink_dpn_prop = wsa_sink_dpn_prop;
	pdev->prop.scp_पूर्णांक1_mask = SDW_SCP_INT1_BUS_CLASH | SDW_SCP_INT1_PARITY;
	gpiod_direction_output(wsa881x->sd_n, 1);

	wsa881x->regmap = devm_regmap_init_sdw(pdev, &wsa881x_regmap_config);
	अगर (IS_ERR(wsa881x->regmap)) अणु
		dev_err(&pdev->dev, "regmap_init failed\n");
		वापस PTR_ERR(wsa881x->regmap);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &wsa881x_component_drv,
					       wsa881x_dais,
					       ARRAY_SIZE(wsa881x_dais));
पूर्ण

अटल स्थिर काष्ठा sdw_device_id wsa881x_slave_id[] = अणु
	SDW_SLAVE_ENTRY(0x0217, 0x2010, 0),
	SDW_SLAVE_ENTRY(0x0217, 0x2110, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, wsa881x_slave_id);

अटल काष्ठा sdw_driver wsa881x_codec_driver = अणु
	.probe	= wsa881x_probe,
	.ops = &wsa881x_slave_ops,
	.id_table = wsa881x_slave_id,
	.driver = अणु
		.name	= "wsa881x-codec",
	पूर्ण
पूर्ण;
module_sdw_driver(wsa881x_codec_driver);

MODULE_DESCRIPTION("WSA881x codec driver");
MODULE_LICENSE("GPL v2");
