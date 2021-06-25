<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ALSA SoC TLV320AIC31xx CODEC Driver Definitions
 *
 * Copyright (C) 2014-2017 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित _TLV320AIC31XX_H
#घोषणा _TLV320AIC31XX_H

#घोषणा AIC31XX_RATES	SNDRV_PCM_RATE_8000_192000

#घोषणा AIC31XX_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S20_3LE | \
			 SNDRV_PCM_FMTBIT_S24_3LE | \
			 SNDRV_PCM_FMTBIT_S24_LE | \
			 SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा AIC31XX_STEREO_CLASS_D_BIT	BIT(1)
#घोषणा AIC31XX_MINIDSP_BIT		BIT(2)
#घोषणा DAC31XX_BIT			BIT(3)

#घोषणा AIC31XX_JACK_MASK (SND_JACK_HEADPHONE | \
			   SND_JACK_HEADSET | \
			   SND_JACK_BTN_0)

क्रमागत aic31xx_type अणु
	AIC3100	= 0,
	AIC3110 = AIC31XX_STEREO_CLASS_D_BIT,
	AIC3120 = AIC31XX_MINIDSP_BIT,
	AIC3111 = AIC31XX_STEREO_CLASS_D_BIT | AIC31XX_MINIDSP_BIT,
	DAC3100 = DAC31XX_BIT,
	DAC3101 = DAC31XX_BIT | AIC31XX_STEREO_CLASS_D_BIT,
पूर्ण;

काष्ठा aic31xx_pdata अणु
	क्रमागत aic31xx_type codec_type;
	अचिन्हित पूर्णांक gpio_reset;
	पूर्णांक micbias_vg;
पूर्ण;

#घोषणा AIC31XX_REG(page, reg)	((page * 128) + reg)

#घोषणा AIC31XX_PAGECTL		AIC31XX_REG(0, 0) /* Page Control Register */

/* Page 0 Registers */
#घोषणा AIC31XX_RESET		AIC31XX_REG(0, 1) /* Software reset रेजिस्टर */
#घोषणा AIC31XX_OT_FLAG		AIC31XX_REG(0, 3) /* OT FLAG रेजिस्टर */
#घोषणा AIC31XX_CLKMUX		AIC31XX_REG(0, 4) /* Clock घड़ी Gen muxing, Multiplexers*/
#घोषणा AIC31XX_PLLPR		AIC31XX_REG(0, 5) /* PLL P and R-VAL रेजिस्टर */
#घोषणा AIC31XX_PLLJ		AIC31XX_REG(0, 6) /* PLL J-VAL रेजिस्टर */
#घोषणा AIC31XX_PLLDMSB		AIC31XX_REG(0, 7) /* PLL D-VAL MSB रेजिस्टर */
#घोषणा AIC31XX_PLLDLSB		AIC31XX_REG(0, 8) /* PLL D-VAL LSB रेजिस्टर */
#घोषणा AIC31XX_NDAC		AIC31XX_REG(0, 11) /* DAC NDAC_VAL रेजिस्टर*/
#घोषणा AIC31XX_MDAC		AIC31XX_REG(0, 12) /* DAC MDAC_VAL रेजिस्टर */
#घोषणा AIC31XX_DOSRMSB		AIC31XX_REG(0, 13) /* DAC OSR setting रेजिस्टर 1, MSB value */
#घोषणा AIC31XX_DOSRLSB		AIC31XX_REG(0, 14) /* DAC OSR setting रेजिस्टर 2, LSB value */
#घोषणा AIC31XX_MINI_DSP_INPOL	AIC31XX_REG(0, 16)
#घोषणा AIC31XX_NADC		AIC31XX_REG(0, 18) /* Clock setting रेजिस्टर 8, PLL */
#घोषणा AIC31XX_MADC		AIC31XX_REG(0, 19) /* Clock setting रेजिस्टर 9, PLL */
#घोषणा AIC31XX_AOSR		AIC31XX_REG(0, 20) /* ADC Oversampling (AOSR) Register */
#घोषणा AIC31XX_CLKOUTMUX	AIC31XX_REG(0, 25) /* Clock setting रेजिस्टर 9, Multiplexers */
#घोषणा AIC31XX_CLKOUTMVAL	AIC31XX_REG(0, 26) /* Clock setting रेजिस्टर 10, CLOCKOUT M भागider value */
#घोषणा AIC31XX_IFACE1		AIC31XX_REG(0, 27) /* Audio Interface Setting Register 1 */
#घोषणा AIC31XX_DATA_OFFSET	AIC31XX_REG(0, 28) /* Audio Data Slot Offset Programming */
#घोषणा AIC31XX_IFACE2		AIC31XX_REG(0, 29) /* Audio Interface Setting Register 2 */
#घोषणा AIC31XX_BCLKN		AIC31XX_REG(0, 30) /* Clock setting रेजिस्टर 11, BCLK N Divider */
#घोषणा AIC31XX_IFACESEC1	AIC31XX_REG(0, 31) /* Audio Interface Setting Register 3, Secondary Audio Interface */
#घोषणा AIC31XX_IFACESEC2	AIC31XX_REG(0, 32) /* Audio Interface Setting Register 4 */
#घोषणा AIC31XX_IFACESEC3	AIC31XX_REG(0, 33) /* Audio Interface Setting Register 5 */
#घोषणा AIC31XX_I2C		AIC31XX_REG(0, 34) /* I2C Bus Condition */
#घोषणा AIC31XX_ADCFLAG		AIC31XX_REG(0, 36) /* ADC FLAG */
#घोषणा AIC31XX_DACFLAG1	AIC31XX_REG(0, 37) /* DAC Flag Registers */
#घोषणा AIC31XX_DACFLAG2	AIC31XX_REG(0, 38)
#घोषणा AIC31XX_OFFLAG		AIC31XX_REG(0, 39) /* Sticky Interrupt flag (overflow) */
#घोषणा AIC31XX_INTRDACFLAG	AIC31XX_REG(0, 44) /* Sticy DAC Interrupt flags */
#घोषणा AIC31XX_INTRADCFLAG	AIC31XX_REG(0, 45) /* Sticy ADC Interrupt flags */
#घोषणा AIC31XX_INTRDACFLAG2	AIC31XX_REG(0, 46) /* DAC Interrupt flags 2 */
#घोषणा AIC31XX_INTRADCFLAG2	AIC31XX_REG(0, 47) /* ADC Interrupt flags 2 */
#घोषणा AIC31XX_INT1CTRL	AIC31XX_REG(0, 48) /* INT1 पूर्णांकerrupt control */
#घोषणा AIC31XX_INT2CTRL	AIC31XX_REG(0, 49) /* INT2 पूर्णांकerrupt control */
#घोषणा AIC31XX_GPIO1		AIC31XX_REG(0, 51) /* GPIO1 control */
#घोषणा AIC31XX_DACPRB		AIC31XX_REG(0, 60)
#घोषणा AIC31XX_ADCPRB		AIC31XX_REG(0, 61) /* ADC Inकाष्ठाion Set Register */
#घोषणा AIC31XX_DACSETUP	AIC31XX_REG(0, 63) /* DAC channel setup रेजिस्टर */
#घोषणा AIC31XX_DACMUTE		AIC31XX_REG(0, 64) /* DAC Mute and volume control रेजिस्टर */
#घोषणा AIC31XX_LDACVOL		AIC31XX_REG(0, 65) /* Left DAC channel digital volume control */
#घोषणा AIC31XX_RDACVOL		AIC31XX_REG(0, 66) /* Right DAC channel digital volume control */
#घोषणा AIC31XX_HSDETECT	AIC31XX_REG(0, 67) /* Headset detection */
#घोषणा AIC31XX_ADCSETUP	AIC31XX_REG(0, 81) /* ADC Digital Mic */
#घोषणा AIC31XX_ADCFGA		AIC31XX_REG(0, 82) /* ADC Digital Volume Control Fine Adjust */
#घोषणा AIC31XX_ADCVOL		AIC31XX_REG(0, 83) /* ADC Digital Volume Control Coarse Adjust */

/* Page 1 Registers */
#घोषणा AIC31XX_HPDRIVER	AIC31XX_REG(1, 31) /* Headphone drivers */
#घोषणा AIC31XX_SPKAMP		AIC31XX_REG(1, 32) /* Class-D Speakear Amplअगरier */
#घोषणा AIC31XX_HPPOP		AIC31XX_REG(1, 33) /* HP Output Drivers POP Removal Settings */
#घोषणा AIC31XX_SPPGARAMP	AIC31XX_REG(1, 34) /* Output Driver PGA Ramp-Down Period Control */
#घोषणा AIC31XX_DACMIXERROUTE	AIC31XX_REG(1, 35) /* DAC_L and DAC_R Output Mixer Routing */
#घोषणा AIC31XX_LANALOGHPL	AIC31XX_REG(1, 36) /* Left Analog Vol to HPL */
#घोषणा AIC31XX_RANALOGHPR	AIC31XX_REG(1, 37) /* Right Analog Vol to HPR */
#घोषणा AIC31XX_LANALOGSPL	AIC31XX_REG(1, 38) /* Left Analog Vol to SPL */
#घोषणा AIC31XX_RANALOGSPR	AIC31XX_REG(1, 39) /* Right Analog Vol to SPR */
#घोषणा AIC31XX_HPLGAIN		AIC31XX_REG(1, 40) /* HPL Driver */
#घोषणा AIC31XX_HPRGAIN		AIC31XX_REG(1, 41) /* HPR Driver */
#घोषणा AIC31XX_SPLGAIN		AIC31XX_REG(1, 42) /* SPL Driver */
#घोषणा AIC31XX_SPRGAIN		AIC31XX_REG(1, 43) /* SPR Driver */
#घोषणा AIC31XX_HPCONTROL	AIC31XX_REG(1, 44) /* HP Driver Control */
#घोषणा AIC31XX_MICBIAS		AIC31XX_REG(1, 46) /* MIC Bias Control */
#घोषणा AIC31XX_MICPGA		AIC31XX_REG(1, 47) /* MIC PGA*/
#घोषणा AIC31XX_MICPGAPI	AIC31XX_REG(1, 48) /* Delta-Sigma Mono ADC Channel Fine-Gain Input Selection क्रम P-Terminal */
#घोषणा AIC31XX_MICPGAMI	AIC31XX_REG(1, 49) /* ADC Input Selection क्रम M-Terminal */
#घोषणा AIC31XX_MICPGACM	AIC31XX_REG(1, 50) /* Input CM Settings */

/* Bits, masks, and shअगरts */

/* AIC31XX_CLKMUX */
#घोषणा AIC31XX_PLL_CLKIN_MASK		GENMASK(3, 2)
#घोषणा AIC31XX_PLL_CLKIN_SHIFT		(2)
#घोषणा AIC31XX_PLL_CLKIN_MCLK		0x00
#घोषणा AIC31XX_PLL_CLKIN_BCKL		0x01
#घोषणा AIC31XX_PLL_CLKIN_GPIO1		0x02
#घोषणा AIC31XX_PLL_CLKIN_DIN		0x03
#घोषणा AIC31XX_CODEC_CLKIN_MASK	GENMASK(1, 0)
#घोषणा AIC31XX_CODEC_CLKIN_SHIFT	(0)
#घोषणा AIC31XX_CODEC_CLKIN_MCLK	0x00
#घोषणा AIC31XX_CODEC_CLKIN_BCLK	0x01
#घोषणा AIC31XX_CODEC_CLKIN_GPIO1	0x02
#घोषणा AIC31XX_CODEC_CLKIN_PLL		0x03

/* AIC31XX_PLLPR */
/* AIC31XX_NDAC */
/* AIC31XX_MDAC */
/* AIC31XX_NADC */
/* AIC31XX_MADC */
/* AIC31XX_BCLKN */
#घोषणा AIC31XX_PLL_MASK		GENMASK(6, 0)
#घोषणा AIC31XX_PM_MASK			BIT(7)

/* AIC31XX_IFACE1 */
#घोषणा AIC31XX_IFACE1_DATATYPE_MASK	GENMASK(7, 6)
#घोषणा AIC31XX_IFACE1_DATATYPE_SHIFT	(6)
#घोषणा AIC31XX_I2S_MODE		0x00
#घोषणा AIC31XX_DSP_MODE		0x01
#घोषणा AIC31XX_RIGHT_JUSTIFIED_MODE	0x02
#घोषणा AIC31XX_LEFT_JUSTIFIED_MODE	0x03
#घोषणा AIC31XX_IFACE1_DATALEN_MASK	GENMASK(5, 4)
#घोषणा AIC31XX_IFACE1_DATALEN_SHIFT	(4)
#घोषणा AIC31XX_WORD_LEN_16BITS		0x00
#घोषणा AIC31XX_WORD_LEN_20BITS		0x01
#घोषणा AIC31XX_WORD_LEN_24BITS		0x02
#घोषणा AIC31XX_WORD_LEN_32BITS		0x03
#घोषणा AIC31XX_IFACE1_MASTER_MASK	GENMASK(3, 2)
#घोषणा AIC31XX_BCLK_MASTER		BIT(2)
#घोषणा AIC31XX_WCLK_MASTER		BIT(3)

/* AIC31XX_DATA_OFFSET */
#घोषणा AIC31XX_DATA_OFFSET_MASK	GENMASK(7, 0)

/* AIC31XX_IFACE2 */
#घोषणा AIC31XX_BCLKINV_MASK		BIT(3)
#घोषणा AIC31XX_BDIVCLK_MASK		GENMASK(1, 0)
#घोषणा AIC31XX_DAC2BCLK		0x00
#घोषणा AIC31XX_DACMOD2BCLK		0x01
#घोषणा AIC31XX_ADC2BCLK		0x02
#घोषणा AIC31XX_ADCMOD2BCLK		0x03
#घोषणा AIC31XX_KEEP_I2SCLK		BIT(2)

/* AIC31XX_ADCFLAG */
#घोषणा AIC31XX_ADCPWRSTATUS_MASK	BIT(6)

/* AIC31XX_DACFLAG1 */
#घोषणा AIC31XX_LDACPWRSTATUS_MASK	BIT(7)
#घोषणा AIC31XX_HPLDRVPWRSTATUS_MASK	BIT(5)
#घोषणा AIC31XX_SPLDRVPWRSTATUS_MASK	BIT(4)
#घोषणा AIC31XX_RDACPWRSTATUS_MASK	BIT(3)
#घोषणा AIC31XX_HPRDRVPWRSTATUS_MASK	BIT(1)
#घोषणा AIC31XX_SPRDRVPWRSTATUS_MASK	BIT(0)

/* AIC31XX_OFFLAG */
#घोषणा AIC31XX_DAC_OF_LEFT		BIT(7)
#घोषणा AIC31XX_DAC_OF_RIGHT		BIT(6)
#घोषणा AIC31XX_DAC_OF_SHIFTER		BIT(5)
#घोषणा AIC31XX_ADC_OF			BIT(3)
#घोषणा AIC31XX_ADC_OF_SHIFTER		BIT(1)

/* AIC31XX_INTRDACFLAG */
#घोषणा AIC31XX_HPLSCDETECT		BIT(7)
#घोषणा AIC31XX_HPRSCDETECT		BIT(6)
#घोषणा AIC31XX_BUTTONPRESS		BIT(5)
#घोषणा AIC31XX_HSPLUG			BIT(4)
#घोषणा AIC31XX_LDRCTHRES		BIT(3)
#घोषणा AIC31XX_RDRCTHRES		BIT(2)
#घोषणा AIC31XX_DACSINT			BIT(1)
#घोषणा AIC31XX_DACAINT			BIT(0)

/* AIC31XX_INT1CTRL */
#घोषणा AIC31XX_HSPLUGDET		BIT(7)
#घोषणा AIC31XX_BUTTONPRESSDET		BIT(6)
#घोषणा AIC31XX_DRCTHRES		BIT(5)
#घोषणा AIC31XX_AGCNOISE		BIT(4)
#घोषणा AIC31XX_SC			BIT(3)
#घोषणा AIC31XX_ENGINE			BIT(2)

/* AIC31XX_GPIO1 */
#घोषणा AIC31XX_GPIO1_FUNC_MASK		GENMASK(5, 2)
#घोषणा AIC31XX_GPIO1_FUNC_SHIFT	2
#घोषणा AIC31XX_GPIO1_DISABLED		0x00
#घोषणा AIC31XX_GPIO1_INPUT		0x01
#घोषणा AIC31XX_GPIO1_GPI		0x02
#घोषणा AIC31XX_GPIO1_GPO		0x03
#घोषणा AIC31XX_GPIO1_CLKOUT		0x04
#घोषणा AIC31XX_GPIO1_INT1		0x05
#घोषणा AIC31XX_GPIO1_INT2		0x06
#घोषणा AIC31XX_GPIO1_ADC_WCLK		0x07
#घोषणा AIC31XX_GPIO1_SBCLK		0x08
#घोषणा AIC31XX_GPIO1_SWCLK		0x09
#घोषणा AIC31XX_GPIO1_ADC_MOD_CLK	0x10
#घोषणा AIC31XX_GPIO1_SDOUT		0x11

/* AIC31XX_DACMUTE */
#घोषणा AIC31XX_DACMUTE_MASK		GENMASK(3, 2)

/* AIC31XX_HSDETECT */
#घोषणा AIC31XX_HSD_ENABLE		BIT(7)
#घोषणा AIC31XX_HSD_TYPE_MASK		GENMASK(6, 5)
#घोषणा AIC31XX_HSD_TYPE_SHIFT		5
#घोषणा AIC31XX_HSD_NONE		0x00
#घोषणा AIC31XX_HSD_HP			0x01
#घोषणा AIC31XX_HSD_HS			0x03

/* AIC31XX_HPDRIVER */
#घोषणा AIC31XX_HPD_OCMV_MASK		GENMASK(4, 3)
#घोषणा AIC31XX_HPD_OCMV_SHIFT		3
#घोषणा AIC31XX_HPD_OCMV_1_35V		0x0
#घोषणा AIC31XX_HPD_OCMV_1_5V		0x1
#घोषणा AIC31XX_HPD_OCMV_1_65V		0x2
#घोषणा AIC31XX_HPD_OCMV_1_8V		0x3

/* AIC31XX_MICBIAS */
#घोषणा AIC31XX_MICBIAS_MASK		GENMASK(1, 0)
#घोषणा AIC31XX_MICBIAS_SHIFT		0

#पूर्ण_अगर	/* _TLV320AIC31XX_H */
