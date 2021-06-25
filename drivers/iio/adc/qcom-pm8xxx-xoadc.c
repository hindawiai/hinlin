<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm PM8xxx PMIC XOADC driver
 *
 * These ADCs are known as HK/XO (house keeping / chrystal oscillator)
 * "XO" in "XOADC" means Chrystal Oscillator. It's a bunch of
 * specअगरic-purpose and general purpose ADC converters and channels.
 *
 * Copyright (C) 2017 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/iio/adc/qcom-vadc-common.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>

/*
 * Definitions क्रम the "user processor" रेजिस्टरs lअगरted from the v3.4
 * Qualcomm tree. Their kernel has two out-of-tree drivers क्रम the ADC:
 * drivers/misc/pmic8058-xoadc.c
 * drivers/hwmon/pm8xxx-adc.c
 * None of them contain any complete रेजिस्टर specअगरication, so this is
 * a best efक्रमt of combining the inक्रमmation.
 */

/* These appear to be "battery monitor" रेजिस्टरs */
#घोषणा ADC_ARB_BTM_CNTRL1			0x17e
#घोषणा ADC_ARB_BTM_CNTRL1_EN_BTM		BIT(0)
#घोषणा ADC_ARB_BTM_CNTRL1_SEL_OP_MODE		BIT(1)
#घोषणा ADC_ARB_BTM_CNTRL1_MEAS_INTERVAL1	BIT(2)
#घोषणा ADC_ARB_BTM_CNTRL1_MEAS_INTERVAL2	BIT(3)
#घोषणा ADC_ARB_BTM_CNTRL1_MEAS_INTERVAL3	BIT(4)
#घोषणा ADC_ARB_BTM_CNTRL1_MEAS_INTERVAL4	BIT(5)
#घोषणा ADC_ARB_BTM_CNTRL1_EOC			BIT(6)
#घोषणा ADC_ARB_BTM_CNTRL1_REQ			BIT(7)

#घोषणा ADC_ARB_BTM_AMUX_CNTRL			0x17f
#घोषणा ADC_ARB_BTM_ANA_PARAM			0x180
#घोषणा ADC_ARB_BTM_DIG_PARAM			0x181
#घोषणा ADC_ARB_BTM_RSV				0x182
#घोषणा ADC_ARB_BTM_DATA1			0x183
#घोषणा ADC_ARB_BTM_DATA0			0x184
#घोषणा ADC_ARB_BTM_BAT_COOL_THR1		0x185
#घोषणा ADC_ARB_BTM_BAT_COOL_THR0		0x186
#घोषणा ADC_ARB_BTM_BAT_WARM_THR1		0x187
#घोषणा ADC_ARB_BTM_BAT_WARM_THR0		0x188
#घोषणा ADC_ARB_BTM_CNTRL2			0x18c

/* Proper ADC रेजिस्टरs */

#घोषणा ADC_ARB_USRP_CNTRL			0x197
#घोषणा ADC_ARB_USRP_CNTRL_EN_ARB		BIT(0)
#घोषणा ADC_ARB_USRP_CNTRL_RSV1			BIT(1)
#घोषणा ADC_ARB_USRP_CNTRL_RSV2			BIT(2)
#घोषणा ADC_ARB_USRP_CNTRL_RSV3			BIT(3)
#घोषणा ADC_ARB_USRP_CNTRL_RSV4			BIT(4)
#घोषणा ADC_ARB_USRP_CNTRL_RSV5			BIT(5)
#घोषणा ADC_ARB_USRP_CNTRL_EOC			BIT(6)
#घोषणा ADC_ARB_USRP_CNTRL_REQ			BIT(7)

#घोषणा ADC_ARB_USRP_AMUX_CNTRL			0x198
/*
 * The channel mask includes the bits selecting channel mux and prescaler
 * on PM8058, or channel mux and premux on PM8921.
 */
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_CHAN_MASK	0xfc
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_RSV0		BIT(0)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_RSV1		BIT(1)
/* On PM8058 this is prescaling, on PM8921 this is premux */
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_PRESCALEMUX0	BIT(2)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_PRESCALEMUX1	BIT(3)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_SEL0		BIT(4)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_SEL1		BIT(5)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_SEL2		BIT(6)
#घोषणा ADC_ARB_USRP_AMUX_CNTRL_SEL3		BIT(7)
#घोषणा ADC_AMUX_PREMUX_SHIFT			2
#घोषणा ADC_AMUX_SEL_SHIFT			4

/* We know very little about the bits in this रेजिस्टर */
#घोषणा ADC_ARB_USRP_ANA_PARAM			0x199
#घोषणा ADC_ARB_USRP_ANA_PARAM_DIS		0xFE
#घोषणा ADC_ARB_USRP_ANA_PARAM_EN		0xFF

#घोषणा ADC_ARB_USRP_DIG_PARAM			0x19A
#घोषणा ADC_ARB_USRP_DIG_PARAM_SEL_SHIFT0	BIT(0)
#घोषणा ADC_ARB_USRP_DIG_PARAM_SEL_SHIFT1	BIT(1)
#घोषणा ADC_ARB_USRP_DIG_PARAM_CLK_RATE0	BIT(2)
#घोषणा ADC_ARB_USRP_DIG_PARAM_CLK_RATE1	BIT(3)
#घोषणा ADC_ARB_USRP_DIG_PARAM_EOC		BIT(4)
/*
 * On a later ADC the decimation factors are defined as
 * 00 = 512, 01 = 1024, 10 = 2048, 11 = 4096 so assume this
 * holds also क्रम this older XOADC.
 */
#घोषणा ADC_ARB_USRP_DIG_PARAM_DEC_RATE0	BIT(5)
#घोषणा ADC_ARB_USRP_DIG_PARAM_DEC_RATE1	BIT(6)
#घोषणा ADC_ARB_USRP_DIG_PARAM_EN		BIT(7)
#घोषणा ADC_DIG_PARAM_DEC_SHIFT			5

#घोषणा ADC_ARB_USRP_RSV			0x19B
#घोषणा ADC_ARB_USRP_RSV_RST			BIT(0)
#घोषणा ADC_ARB_USRP_RSV_DTEST0			BIT(1)
#घोषणा ADC_ARB_USRP_RSV_DTEST1			BIT(2)
#घोषणा ADC_ARB_USRP_RSV_OP			BIT(3)
#घोषणा ADC_ARB_USRP_RSV_IP_SEL0		BIT(4)
#घोषणा ADC_ARB_USRP_RSV_IP_SEL1		BIT(5)
#घोषणा ADC_ARB_USRP_RSV_IP_SEL2		BIT(6)
#घोषणा ADC_ARB_USRP_RSV_TRM			BIT(7)
#घोषणा ADC_RSV_IP_SEL_SHIFT			4

#घोषणा ADC_ARB_USRP_DATA0			0x19D
#घोषणा ADC_ARB_USRP_DATA1			0x19C

/*
 * Physical channels which MUST exist on all PM variants in order to provide
 * proper reference poपूर्णांकs क्रम calibration.
 *
 * @PM8XXX_CHANNEL_INTERNAL: 625mV reference channel
 * @PM8XXX_CHANNEL_125V: 1250mV reference channel
 * @PM8XXX_CHANNEL_INTERNAL_2: 325mV reference channel
 * @PM8XXX_CHANNEL_MUXOFF: channel to reduce input load on mux, apparently also
 * measures XO temperature
 */
#घोषणा PM8XXX_CHANNEL_INTERNAL		0x0c
#घोषणा PM8XXX_CHANNEL_125V		0x0d
#घोषणा PM8XXX_CHANNEL_INTERNAL_2	0x0e
#घोषणा PM8XXX_CHANNEL_MUXOFF		0x0f

/*
 * PM8058 AMUX premux scaling, two bits. This is करोne of the channel beक्रमe
 * reaching the AMUX.
 */
#घोषणा PM8058_AMUX_PRESCALE_0 0x0 /* No scaling on the संकेत */
#घोषणा PM8058_AMUX_PRESCALE_1 0x1 /* Unity scaling selected by the user */
#घोषणा PM8058_AMUX_PRESCALE_1_DIV3 0x2 /* 1/3 prescaler on the input */

/* Defines reference voltage क्रम the XOADC */
#घोषणा AMUX_RSV0 0x0 /* XO_IN/XOADC_GND, special selection to पढ़ो XO temp */
#घोषणा AMUX_RSV1 0x1 /* PMIC_IN/XOADC_GND */
#घोषणा AMUX_RSV2 0x2 /* PMIC_IN/BMS_CSP */
#घोषणा AMUX_RSV3 0x3 /* not used */
#घोषणा AMUX_RSV4 0x4 /* XOADC_GND/XOADC_GND */
#घोषणा AMUX_RSV5 0x5 /* XOADC_VREF/XOADC_GND */
#घोषणा XOADC_RSV_MAX 5 /* 3 bits 0..7, 3 and 6,7 are invalid */

/**
 * काष्ठा xoadc_channel - encodes channel properties and शेषs
 * @datasheet_name: the hardwaनाम of this channel
 * @pre_scale_mux: prescale (PM8058) or premux (PM8921) क्रम selecting
 * this channel. Both this and the amux channel is needed to uniquely
 * identअगरy a channel. Values 0..3.
 * @amux_channel: value of the ADC_ARB_USRP_AMUX_CNTRL रेजिस्टर क्रम this
 * channel, bits 4..7, selects the amux, values 0..f
 * @prescale: the channels have hard-coded prescale ratios defined
 * by the hardware, this tells us what it is
 * @type: corresponding IIO channel type, usually IIO_VOLTAGE or
 * IIO_TEMP
 * @scale_fn_type: the liner पूर्णांकerpolation etc to convert the
 * ADC code to the value that IIO expects, in uV or millicelsius
 * etc. This scale function can be pretty elaborate अगर dअगरferent
 * thermistors are connected or other hardware अक्षरacteristics are
 * deployed.
 * @amux_ip_rsv: ratiometric scale value used by the analog muxer: this
 * selects the reference voltage क्रम ratiometric scaling
 */
काष्ठा xoadc_channel अणु
	स्थिर अक्षर *datasheet_name;
	u8 pre_scale_mux:2;
	u8 amux_channel:4;
	स्थिर काष्ठा vadc_prescale_ratio prescale;
	क्रमागत iio_chan_type type;
	क्रमागत vadc_scale_fn_type scale_fn_type;
	u8 amux_ip_rsv:3;
पूर्ण;

/**
 * काष्ठा xoadc_variant - encodes the XOADC variant अक्षरacteristics
 * @name: name of this PMIC variant
 * @channels: the hardware channels and respective settings and शेषs
 * @broken_ratiometric: अगर the PMIC has broken ratiometric scaling (this
 * is a known problem on PM8058)
 * @prescaling: this variant uses AMUX bits 2 & 3 क्रम prescaling (PM8058)
 * @second_level_mux: this variant uses AMUX bits 2 & 3 क्रम a second level
 * mux
 */
काष्ठा xoadc_variant अणु
	स्थिर अक्षर name[16];
	स्थिर काष्ठा xoadc_channel *channels;
	bool broken_ratiometric;
	bool prescaling;
	bool second_level_mux;
पूर्ण;

/*
 * XOADC_CHAN macro parameters:
 * _dname: the name of the channel
 * _presmux: prescaler (PM8058) or premux (PM8921) setting क्रम this channel
 * _amux: the value in bits 2..7 of the ADC_ARB_USRP_AMUX_CNTRL रेजिस्टर
 * क्रम this channel. On some PMICs some of the bits select a prescaler, and
 * on some PMICs some of the bits select various complex multiplex settings.
 * _type: IIO channel type
 * _prक्रमागत: prescaler numerator (भागidend)
 * _preden: prescaler denominator (भागisor)
 * _scale: scaling function type, this selects how the raw valued is mangled
 * to output the actual processed measurement
 * _amip: analog mux input parent when using ratiometric measurements
 */
#घोषणा XOADC_CHAN(_dname, _presmux, _amux, _type, _prक्रमागत, _preden, _scale, _amip) \
	अणु								\
		.datasheet_name = __stringअगरy(_dname),			\
		.pre_scale_mux = _presmux,				\
		.amux_channel = _amux,					\
		.prescale = अणु .num = _prक्रमागत, .den = _preden पूर्ण,		\
		.type = _type,						\
		.scale_fn_type = _scale,				\
		.amux_ip_rsv = _amip,					\
	पूर्ण

/*
 * Taken from arch/arm/mach-msm/board-9615.c in the venकरोr tree:
 * TODO: incomplete, needs testing.
 */
अटल स्थिर काष्ठा xoadc_channel pm8018_xoadc_channels[] = अणु
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VPH_PWR, 0x00, 0x02, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCALE_PMIC_THERM, AMUX_RSV1),
	/* Used क्रम battery ID or battery temperature */
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV2),
	XOADC_CHAN(INTERNAL, 0x00, 0x0c, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCALE_XOTHERM, AMUX_RSV0),
	अणु पूर्ण, /* Sentinel */
पूर्ण;

/*
 * Taken from arch/arm/mach-msm/board-8930-pmic.c in the venकरोr tree:
 * TODO: needs testing.
 */
अटल स्थिर काष्ठा xoadc_channel pm8038_xoadc_channels[] = अणु
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOLTAGE, 1, 6, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ICHG, 0x00, 0x03, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VPH_PWR, 0x00, 0x04, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX5, 0x00, 0x05, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX6, 0x00, 0x06, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX7, 0x00, 0x07, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* AMUX8 used क्रम battery temperature in most हालs */
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_TEMP, 1, 1, SCALE_THERM_100K_PULLUP, AMUX_RSV2),
	XOADC_CHAN(AMUX9, 0x00, 0x09, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOLTAGE, 1, 4, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCALE_PMIC_THERM, AMUX_RSV1),
	XOADC_CHAN(INTERNAL, 0x00, 0x0c, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(INTERNAL_2, 0x00, 0x0e, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCALE_XOTHERM, AMUX_RSV0),
	अणु पूर्ण, /* Sentinel */
पूर्ण;

/*
 * This was created by cross-referencing the venकरोr tree
 * arch/arm/mach-msm/board-msm8x60.c msm_adc_channels_data[]
 * with the "channel types" (first field) to find the right
 * configuration क्रम these channels on an MSM8x60 i.e. PM8058
 * setup.
 */
अटल स्थिर काष्ठा xoadc_channel pm8058_xoadc_channels[] = अणु
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOLTAGE, 1, 2, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOLTAGE, 1, 10, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ICHG, 0x00, 0x03, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VPH_PWR, 0x00, 0x04, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	/*
	 * AMUX channels 5 thru 9 are referred to as MPP5 thru MPP9 in
	 * some code and करोcumentation. But they are really just 5
	 * channels just like any other. They are connected to a चयनing
	 * matrix where they can be routed to any of the MPPs, not just
	 * 1-to-1 onto MPP5 thru 9, so naming them MPP5 thru MPP9 is
	 * very confusing.
	 */
	XOADC_CHAN(AMUX5, 0x00, 0x05, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX6, 0x00, 0x06, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX7, 0x00, 0x07, IIO_VOLTAGE, 1, 2, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_VOLTAGE, 1, 2, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX9, 0x00, 0x09, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCALE_PMIC_THERM, AMUX_RSV1),
	XOADC_CHAN(INTERNAL, 0x00, 0x0c, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(INTERNAL_2, 0x00, 0x0e, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCALE_XOTHERM, AMUX_RSV0),
	/* There are also "unity" and भागided by 3 channels (prescaler) but noone is using them */
	अणु पूर्ण, /* Sentinel */
पूर्ण;

/*
 * The PM8921 has some pre-muxing on its channels, this comes from the venकरोr tree
 * include/linux/mfd/pm8xxx/pm8xxx-adc.h
 * board-flo-pmic.c (Nexus 7) and board-8064-pmic.c
 */
अटल स्थिर काष्ठा xoadc_channel pm8921_xoadc_channels[] = अणु
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOLTAGE, 1, 6, SCALE_DEFAULT, AMUX_RSV1),
	/* channel "ICHG" is reserved and not used on PM8921 */
	XOADC_CHAN(VPH_PWR, 0x00, 0x04, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(IBAT, 0x00, 0x05, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* CHAN 6 & 7 (MPP1 & MPP2) are reserved क्रम MPP channels on PM8921 */
	XOADC_CHAN(BATT_THERM, 0x00, 0x08, IIO_TEMP, 1, 1, SCALE_THERM_100K_PULLUP, AMUX_RSV1),
	XOADC_CHAN(BATT_ID, 0x00, 0x09, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOLTAGE, 1, 4, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCALE_PMIC_THERM, AMUX_RSV1),
	XOADC_CHAN(INTERNAL, 0x00, 0x0c, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* FIXME: look पूर्णांकo the scaling of this temperature */
	XOADC_CHAN(CHG_TEMP, 0x00, 0x0e, IIO_TEMP, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCALE_XOTHERM, AMUX_RSV0),
	/* The following channels have premux bit 0 set to 1 (all end in 4) */
	XOADC_CHAN(ATEST_8, 0x01, 0x00, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* Set scaling to 1/2 based on the name क्रम these two */
	XOADC_CHAN(USB_SNS_DIV20, 0x01, 0x01, IIO_VOLTAGE, 1, 2, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DCIN_SNS_DIV20, 0x01, 0x02, IIO_VOLTAGE, 1, 2, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX3, 0x01, 0x03, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX4, 0x01, 0x04, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX5, 0x01, 0x05, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX6, 0x01, 0x06, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX7, 0x01, 0x07, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX8, 0x01, 0x08, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* Internal test संकेतs, I think */
	XOADC_CHAN(ATEST_1, 0x01, 0x09, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_2, 0x01, 0x0a, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_3, 0x01, 0x0b, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_4, 0x01, 0x0c, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_5, 0x01, 0x0d, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_6, 0x01, 0x0e, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_7, 0x01, 0x0f, IIO_VOLTAGE, 1, 1, SCALE_DEFAULT, AMUX_RSV1),
	/* The following channels have premux bit 1 set to 1 (all end in 8) */
	/* I guess even ATEST8 will be भागided by 3 here */
	XOADC_CHAN(ATEST_8, 0x02, 0x00, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	/* I guess भाग 2 भाग 3 becomes भाग 6 */
	XOADC_CHAN(USB_SNS_DIV20_DIV3, 0x02, 0x01, IIO_VOLTAGE, 1, 6, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(DCIN_SNS_DIV20_DIV3, 0x02, 0x02, IIO_VOLTAGE, 1, 6, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX3_DIV3, 0x02, 0x03, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX4_DIV3, 0x02, 0x04, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX5_DIV3, 0x02, 0x05, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX6_DIV3, 0x02, 0x06, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX7_DIV3, 0x02, 0x07, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(AMUX8_DIV3, 0x02, 0x08, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_1_DIV3, 0x02, 0x09, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_2_DIV3, 0x02, 0x0a, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_3_DIV3, 0x02, 0x0b, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_4_DIV3, 0x02, 0x0c, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_5_DIV3, 0x02, 0x0d, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_6_DIV3, 0x02, 0x0e, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	XOADC_CHAN(ATEST_7_DIV3, 0x02, 0x0f, IIO_VOLTAGE, 1, 3, SCALE_DEFAULT, AMUX_RSV1),
	अणु पूर्ण, /* Sentinel */
पूर्ण;

/**
 * काष्ठा pm8xxx_chan_info - ADC channel inक्रमmation
 * @name: name of this channel
 * @hwchan: poपूर्णांकer to hardware channel inक्रमmation (muxing & scaling settings)
 * @calibration: whether to use असलolute or ratiometric calibration
 * @scale_fn_type: scaling function type
 * @decimation: 0,1,2,3
 * @amux_ip_rsv: ratiometric scale value अगर using ratiometric
 * calibration: 0, 1, 2, 4, 5.
 */
काष्ठा pm8xxx_chan_info अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा xoadc_channel *hwchan;
	क्रमागत vadc_calibration calibration;
	u8 decimation:2;
	u8 amux_ip_rsv:3;
पूर्ण;

/**
 * काष्ठा pm8xxx_xoadc - state container क्रम the XOADC
 * @dev: poपूर्णांकer to device
 * @map: regmap to access रेजिस्टरs
 * @variant: XOADC variant अक्षरacteristics
 * @vref: reference voltage regulator
 * अक्षरacteristics of the channels, and sensible शेष settings
 * @nchans: number of channels, configured by the device tree
 * @chans: the channel inक्रमmation per-channel, configured by the device tree
 * @iio_chans: IIO channel specअगरiers
 * @graph: linear calibration parameters क्रम असलolute and
 * ratiometric measurements
 * @complete: completion to indicate end of conversion
 * @lock: lock to restrict access to the hardware to one client at the समय
 */
काष्ठा pm8xxx_xoadc अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	स्थिर काष्ठा xoadc_variant *variant;
	काष्ठा regulator *vref;
	अचिन्हित पूर्णांक nchans;
	काष्ठा pm8xxx_chan_info *chans;
	काष्ठा iio_chan_spec *iio_chans;
	काष्ठा vadc_linear_graph graph[2];
	काष्ठा completion complete;
	काष्ठा mutex lock;
पूर्ण;

अटल irqवापस_t pm8xxx_eoc_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा iio_dev *indio_dev = d;
	काष्ठा pm8xxx_xoadc *adc = iio_priv(indio_dev);

	complete(&adc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा pm8xxx_chan_info *
pm8xxx_get_channel(काष्ठा pm8xxx_xoadc *adc, u8 chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adc->nchans; i++) अणु
		काष्ठा pm8xxx_chan_info *ch = &adc->chans[i];
		अगर (ch->hwchan->amux_channel == chan)
			वापस ch;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक pm8xxx_पढ़ो_channel_rsv(काष्ठा pm8xxx_xoadc *adc,
				   स्थिर काष्ठा pm8xxx_chan_info *ch,
				   u8 rsv, u16 *adc_code,
				   bool क्रमce_ratiometric)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	u8 rsvmask, rsvval;
	u8 lsb, msb;

	dev_dbg(adc->dev, "read channel \"%s\", amux %d, prescale/mux: %d, rsv %d\n",
		ch->name, ch->hwchan->amux_channel, ch->hwchan->pre_scale_mux, rsv);

	mutex_lock(&adc->lock);

	/* Mux in this channel */
	val = ch->hwchan->amux_channel << ADC_AMUX_SEL_SHIFT;
	val |= ch->hwchan->pre_scale_mux << ADC_AMUX_PREMUX_SHIFT;
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_AMUX_CNTRL, val);
	अगर (ret)
		जाओ unlock;

	/* Set up ratiometric scale value, mask off all bits except these */
	rsvmask = (ADC_ARB_USRP_RSV_RST | ADC_ARB_USRP_RSV_DTEST0 |
		   ADC_ARB_USRP_RSV_DTEST1 | ADC_ARB_USRP_RSV_OP);
	अगर (adc->variant->broken_ratiometric && !क्रमce_ratiometric) अणु
		/*
		 * Apparently the PM8058 has some kind of bug which is
		 * reflected in the venकरोr tree drivers/misc/pmix8058-xoadc.c
		 * which just hardcodes the RSV selector to SEL1 (0x20) क्रम
		 * most हालs and SEL0 (0x10) क्रम the MUXOFF channel only.
		 * If we क्रमce ratiometric (currently only करोne when attempting
		 * to करो ratiometric calibration) this करोesn't seem to work
		 * very well and I suspect ratiometric conversion is simply
		 * broken or not supported on the PM8058.
		 *
		 * Maybe IO_SEL2 करोesn't exist on PM8058 and bits 4 & 5 select
		 * the mode alone.
		 *
		 * Some PM8058 रेजिस्टर करोcumentation would be nice to get
		 * this right.
		 */
		अगर (ch->hwchan->amux_channel == PM8XXX_CHANNEL_MUXOFF)
			rsvval = ADC_ARB_USRP_RSV_IP_SEL0;
		अन्यथा
			rsvval = ADC_ARB_USRP_RSV_IP_SEL1;
	पूर्ण अन्यथा अणु
		अगर (rsv == 0xff)
			rsvval = (ch->amux_ip_rsv << ADC_RSV_IP_SEL_SHIFT) |
				ADC_ARB_USRP_RSV_TRM;
		अन्यथा
			rsvval = (rsv << ADC_RSV_IP_SEL_SHIFT) |
				ADC_ARB_USRP_RSV_TRM;
	पूर्ण

	ret = regmap_update_bits(adc->map,
				 ADC_ARB_USRP_RSV,
				 ~rsvmask,
				 rsvval);
	अगर (ret)
		जाओ unlock;

	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_ANA_PARAM,
			   ADC_ARB_USRP_ANA_PARAM_DIS);
	अगर (ret)
		जाओ unlock;

	/* Decimation factor */
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_DIG_PARAM,
			   ADC_ARB_USRP_DIG_PARAM_SEL_SHIFT0 |
			   ADC_ARB_USRP_DIG_PARAM_SEL_SHIFT1 |
			   ch->decimation << ADC_DIG_PARAM_DEC_SHIFT);
	अगर (ret)
		जाओ unlock;

	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_ANA_PARAM,
			   ADC_ARB_USRP_ANA_PARAM_EN);
	अगर (ret)
		जाओ unlock;

	/* Enable the arbiter, the Qualcomm code करोes it twice like this */
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_CNTRL,
			   ADC_ARB_USRP_CNTRL_EN_ARB);
	अगर (ret)
		जाओ unlock;
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_CNTRL,
			   ADC_ARB_USRP_CNTRL_EN_ARB);
	अगर (ret)
		जाओ unlock;


	/* Fire a request! */
	reinit_completion(&adc->complete);
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_CNTRL,
			   ADC_ARB_USRP_CNTRL_EN_ARB |
			   ADC_ARB_USRP_CNTRL_REQ);
	अगर (ret)
		जाओ unlock;

	/* Next the पूर्णांकerrupt occurs */
	ret = रुको_क्रम_completion_समयout(&adc->complete,
					  VADC_CONV_TIME_MAX_US);
	अगर (!ret) अणु
		dev_err(adc->dev, "conversion timed out\n");
		ret = -ETIMEDOUT;
		जाओ unlock;
	पूर्ण

	ret = regmap_पढ़ो(adc->map, ADC_ARB_USRP_DATA0, &val);
	अगर (ret)
		जाओ unlock;
	lsb = val;
	ret = regmap_पढ़ो(adc->map, ADC_ARB_USRP_DATA1, &val);
	अगर (ret)
		जाओ unlock;
	msb = val;
	*adc_code = (msb << 8) | lsb;

	/* Turn off the ADC by setting the arbiter to 0 twice */
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_CNTRL, 0);
	अगर (ret)
		जाओ unlock;
	ret = regmap_ग_लिखो(adc->map, ADC_ARB_USRP_CNTRL, 0);
	अगर (ret)
		जाओ unlock;

unlock:
	mutex_unlock(&adc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_पढ़ो_channel(काष्ठा pm8xxx_xoadc *adc,
			       स्थिर काष्ठा pm8xxx_chan_info *ch,
			       u16 *adc_code)
अणु
	/*
	 * Normally we just use the ratiometric scale value (RSV) predefined
	 * क्रम the channel, but during calibration we need to modअगरy this
	 * so this wrapper is a helper hiding the more complex version.
	 */
	वापस pm8xxx_पढ़ो_channel_rsv(adc, ch, 0xff, adc_code, false);
पूर्ण

अटल पूर्णांक pm8xxx_calibrate_device(काष्ठा pm8xxx_xoadc *adc)
अणु
	स्थिर काष्ठा pm8xxx_chan_info *ch;
	u16 पढ़ो_1250v;
	u16 पढ़ो_0625v;
	u16 पढ़ो_nomux_rsv5;
	u16 पढ़ो_nomux_rsv4;
	पूर्णांक ret;

	adc->graph[VADC_CALIB_ABSOLUTE].dx = VADC_ABSOLUTE_RANGE_UV;
	adc->graph[VADC_CALIB_RATIOMETRIC].dx = VADC_RATIOMETRIC_RANGE;

	/* Common reference channel calibration */
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_125V);
	अगर (!ch)
		वापस -ENODEV;
	ret = pm8xxx_पढ़ो_channel(adc, ch, &पढ़ो_1250v);
	अगर (ret) अणु
		dev_err(adc->dev, "could not read 1.25V reference channel\n");
		वापस -ENODEV;
	पूर्ण
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_INTERNAL);
	अगर (!ch)
		वापस -ENODEV;
	ret = pm8xxx_पढ़ो_channel(adc, ch, &पढ़ो_0625v);
	अगर (ret) अणु
		dev_err(adc->dev, "could not read 0.625V reference channel\n");
		वापस -ENODEV;
	पूर्ण
	अगर (पढ़ो_1250v == पढ़ो_0625v) अणु
		dev_err(adc->dev, "read same ADC code for 1.25V and 0.625V\n");
		वापस -ENODEV;
	पूर्ण

	adc->graph[VADC_CALIB_ABSOLUTE].dy = पढ़ो_1250v - पढ़ो_0625v;
	adc->graph[VADC_CALIB_ABSOLUTE].gnd = पढ़ो_0625v;

	dev_info(adc->dev, "absolute calibration dx = %d uV, dy = %d units\n",
		 VADC_ABSOLUTE_RANGE_UV, adc->graph[VADC_CALIB_ABSOLUTE].dy);

	/* Ratiometric calibration */
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_MUXOFF);
	अगर (!ch)
		वापस -ENODEV;
	ret = pm8xxx_पढ़ो_channel_rsv(adc, ch, AMUX_RSV5,
				      &पढ़ो_nomux_rsv5, true);
	अगर (ret) अणु
		dev_err(adc->dev, "could not read MUXOFF reference channel\n");
		वापस -ENODEV;
	पूर्ण
	ret = pm8xxx_पढ़ो_channel_rsv(adc, ch, AMUX_RSV4,
				      &पढ़ो_nomux_rsv4, true);
	अगर (ret) अणु
		dev_err(adc->dev, "could not read MUXOFF reference channel\n");
		वापस -ENODEV;
	पूर्ण
	adc->graph[VADC_CALIB_RATIOMETRIC].dy =
		पढ़ो_nomux_rsv5 - पढ़ो_nomux_rsv4;
	adc->graph[VADC_CALIB_RATIOMETRIC].gnd = पढ़ो_nomux_rsv4;

	dev_info(adc->dev, "ratiometric calibration dx = %d, dy = %d units\n",
		 VADC_RATIOMETRIC_RANGE,
		 adc->graph[VADC_CALIB_RATIOMETRIC].dy);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा pm8xxx_xoadc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा pm8xxx_chan_info *ch;
	u16 adc_code;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ch = pm8xxx_get_channel(adc, chan->address);
		अगर (!ch) अणु
			dev_err(adc->dev, "no such channel %lu\n",
				chan->address);
			वापस -EINVAL;
		पूर्ण
		ret = pm8xxx_पढ़ो_channel(adc, ch, &adc_code);
		अगर (ret)
			वापस ret;

		ret = qcom_vadc_scale(ch->hwchan->scale_fn_type,
				      &adc->graph[ch->calibration],
				      &ch->hwchan->prescale,
				      (ch->calibration == VADC_CALIB_ABSOLUTE),
				      adc_code, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_RAW:
		ch = pm8xxx_get_channel(adc, chan->address);
		अगर (!ch) अणु
			dev_err(adc->dev, "no such channel %lu\n",
				chan->address);
			वापस -EINVAL;
		पूर्ण
		ret = pm8xxx_पढ़ो_channel(adc, ch, &adc_code);
		अगर (ret)
			वापस ret;

		*val = (पूर्णांक)adc_code;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक pm8xxx_of_xlate(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	काष्ठा pm8xxx_xoadc *adc = iio_priv(indio_dev);
	u8 pre_scale_mux;
	u8 amux_channel;
	अचिन्हित पूर्णांक i;

	/*
	 * First cell is prescaler or premux, second cell is analog
	 * mux.
	 */
	अगर (iiospec->args_count != 2) अणु
		dev_err(&indio_dev->dev, "wrong number of arguments for %pOFn need 2 got %d\n",
			iiospec->np,
			iiospec->args_count);
		वापस -EINVAL;
	पूर्ण
	pre_scale_mux = (u8)iiospec->args[0];
	amux_channel = (u8)iiospec->args[1];
	dev_dbg(&indio_dev->dev, "pre scale/mux: %02x, amux: %02x\n",
		pre_scale_mux, amux_channel);

	/* We need to match exactly on the prescale/premux and channel */
	क्रम (i = 0; i < adc->nchans; i++)
		अगर (adc->chans[i].hwchan->pre_scale_mux == pre_scale_mux &&
		    adc->chans[i].hwchan->amux_channel == amux_channel)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info pm8xxx_xoadc_info = अणु
	.of_xlate = pm8xxx_of_xlate,
	.पढ़ो_raw = pm8xxx_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक pm8xxx_xoadc_parse_channel(काष्ठा device *dev,
				      काष्ठा device_node *np,
				      स्थिर काष्ठा xoadc_channel *hw_channels,
				      काष्ठा iio_chan_spec *iio_chan,
				      काष्ठा pm8xxx_chan_info *ch)
अणु
	स्थिर अक्षर *name = np->name;
	स्थिर काष्ठा xoadc_channel *hwchan;
	u32 pre_scale_mux, amux_channel;
	u32 rsv, dec;
	पूर्णांक ret;
	पूर्णांक chid;

	ret = of_property_पढ़ो_u32_index(np, "reg", 0, &pre_scale_mux);
	अगर (ret) अणु
		dev_err(dev, "invalid pre scale/mux number %s\n", name);
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32_index(np, "reg", 1, &amux_channel);
	अगर (ret) अणु
		dev_err(dev, "invalid amux channel number %s\n", name);
		वापस ret;
	पूर्ण

	/* Find the right channel setting */
	chid = 0;
	hwchan = &hw_channels[0];
	जबतक (hwchan && hwchan->datasheet_name) अणु
		अगर (hwchan->pre_scale_mux == pre_scale_mux &&
		    hwchan->amux_channel == amux_channel)
			अवरोध;
		hwchan++;
		chid++;
	पूर्ण
	/* The sentinel करोes not have a name asचिन्हित */
	अगर (!hwchan->datasheet_name) अणु
		dev_err(dev, "could not locate channel %02x/%02x\n",
			pre_scale_mux, amux_channel);
		वापस -EINVAL;
	पूर्ण
	ch->name = name;
	ch->hwchan = hwchan;
	/* Everyone seems to use असलolute calibration except in special हालs */
	ch->calibration = VADC_CALIB_ABSOLUTE;
	/* Everyone seems to use शेष ("type 2") decimation */
	ch->decimation = VADC_DEF_DECIMATION;

	अगर (!of_property_पढ़ो_u32(np, "qcom,ratiometric", &rsv)) अणु
		ch->calibration = VADC_CALIB_RATIOMETRIC;
		अगर (rsv > XOADC_RSV_MAX) अणु
			dev_err(dev, "%s too large RSV value %d\n", name, rsv);
			वापस -EINVAL;
		पूर्ण
		अगर (rsv == AMUX_RSV3) अणु
			dev_err(dev, "%s invalid RSV value %d\n", name, rsv);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Optional decimation, अगर omitted we use the शेष */
	ret = of_property_पढ़ो_u32(np, "qcom,decimation", &dec);
	अगर (!ret) अणु
		ret = qcom_vadc_decimation_from_dt(dec);
		अगर (ret < 0) अणु
			dev_err(dev, "%s invalid decimation %d\n",
				name, dec);
			वापस ret;
		पूर्ण
		ch->decimation = ret;
	पूर्ण

	iio_chan->channel = chid;
	iio_chan->address = hwchan->amux_channel;
	iio_chan->datasheet_name = hwchan->datasheet_name;
	iio_chan->type = hwchan->type;
	/* All channels are raw or processed */
	iio_chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_PROCESSED);
	iio_chan->indexed = 1;

	dev_dbg(dev, "channel [PRESCALE/MUX: %02x AMUX: %02x] \"%s\" "
		"ref voltage: %d, decimation %d "
		"prescale %d/%d, scale function %d\n",
		hwchan->pre_scale_mux, hwchan->amux_channel, ch->name,
		ch->amux_ip_rsv, ch->decimation, hwchan->prescale.num,
		hwchan->prescale.den, hwchan->scale_fn_type);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_xoadc_parse_channels(काष्ठा pm8xxx_xoadc *adc,
				       काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	काष्ठा pm8xxx_chan_info *ch;
	पूर्णांक ret;
	पूर्णांक i;

	adc->nchans = of_get_available_child_count(np);
	अगर (!adc->nchans) अणु
		dev_err(adc->dev, "no channel children\n");
		वापस -ENODEV;
	पूर्ण
	dev_dbg(adc->dev, "found %d ADC channels\n", adc->nchans);

	adc->iio_chans = devm_kसुस्मृति(adc->dev, adc->nchans,
				      माप(*adc->iio_chans), GFP_KERNEL);
	अगर (!adc->iio_chans)
		वापस -ENOMEM;

	adc->chans = devm_kसुस्मृति(adc->dev, adc->nchans,
				  माप(*adc->chans), GFP_KERNEL);
	अगर (!adc->chans)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_available_child_of_node(np, child) अणु
		ch = &adc->chans[i];
		ret = pm8xxx_xoadc_parse_channel(adc->dev, child,
						 adc->variant->channels,
						 &adc->iio_chans[i],
						 ch);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
		i++;
	पूर्ण

	/* Check क्रम required channels */
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_125V);
	अगर (!ch) अणु
		dev_err(adc->dev, "missing 1.25V reference channel\n");
		वापस -ENODEV;
	पूर्ण
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_INTERNAL);
	अगर (!ch) अणु
		dev_err(adc->dev, "missing 0.625V reference channel\n");
		वापस -ENODEV;
	पूर्ण
	ch = pm8xxx_get_channel(adc, PM8XXX_CHANNEL_MUXOFF);
	अगर (!ch) अणु
		dev_err(adc->dev, "missing MUXOFF reference channel\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_xoadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा xoadc_variant *variant;
	काष्ठा pm8xxx_xoadc *adc;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regmap *map;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	variant = of_device_get_match_data(dev);
	अगर (!variant)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, indio_dev);

	adc = iio_priv(indio_dev);
	adc->dev = dev;
	adc->variant = variant;
	init_completion(&adc->complete);
	mutex_init(&adc->lock);

	ret = pm8xxx_xoadc_parse_channels(adc, np);
	अगर (ret)
		वापस ret;

	map = dev_get_regmap(dev->parent, शून्य);
	अगर (!map) अणु
		dev_err(dev, "parent regmap unavailable.\n");
		वापस -ENXIO;
	पूर्ण
	adc->map = map;

	/* Bring up regulator */
	adc->vref = devm_regulator_get(dev, "xoadc-ref");
	अगर (IS_ERR(adc->vref)) अणु
		dev_err(dev, "failed to get XOADC VREF regulator\n");
		वापस PTR_ERR(adc->vref);
	पूर्ण
	ret = regulator_enable(adc->vref);
	अगर (ret) अणु
		dev_err(dev, "failed to enable XOADC VREF regulator\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, platक्रमm_get_irq(pdev, 0),
			pm8xxx_eoc_irq, शून्य, 0, variant->name, indio_dev);
	अगर (ret) अणु
		dev_err(dev, "unable to request IRQ\n");
		जाओ out_disable_vref;
	पूर्ण

	indio_dev->name = variant->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &pm8xxx_xoadc_info;
	indio_dev->channels = adc->iio_chans;
	indio_dev->num_channels = adc->nchans;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ out_disable_vref;

	ret = pm8xxx_calibrate_device(adc);
	अगर (ret)
		जाओ out_unreg_device;

	dev_info(dev, "%s XOADC driver enabled\n", variant->name);

	वापस 0;

out_unreg_device:
	iio_device_unरेजिस्टर(indio_dev);
out_disable_vref:
	regulator_disable(adc->vref);

	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_xoadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा pm8xxx_xoadc *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	regulator_disable(adc->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xoadc_variant pm8018_variant = अणु
	.name = "PM8018-XOADC",
	.channels = pm8018_xoadc_channels,
पूर्ण;

अटल स्थिर काष्ठा xoadc_variant pm8038_variant = अणु
	.name = "PM8038-XOADC",
	.channels = pm8038_xoadc_channels,
पूर्ण;

अटल स्थिर काष्ठा xoadc_variant pm8058_variant = अणु
	.name = "PM8058-XOADC",
	.channels = pm8058_xoadc_channels,
	.broken_ratiometric = true,
	.prescaling = true,
पूर्ण;

अटल स्थिर काष्ठा xoadc_variant pm8921_variant = अणु
	.name = "PM8921-XOADC",
	.channels = pm8921_xoadc_channels,
	.second_level_mux = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pm8xxx_xoadc_id_table[] = अणु
	अणु
		.compatible = "qcom,pm8018-adc",
		.data = &pm8018_variant,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8038-adc",
		.data = &pm8038_variant,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8058-adc",
		.data = &pm8058_variant,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8921-adc",
		.data = &pm8921_variant,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_xoadc_id_table);

अटल काष्ठा platक्रमm_driver pm8xxx_xoadc_driver = अणु
	.driver		= अणु
		.name	= "pm8xxx-adc",
		.of_match_table = pm8xxx_xoadc_id_table,
	पूर्ण,
	.probe		= pm8xxx_xoadc_probe,
	.हटाओ		= pm8xxx_xoadc_हटाओ,
पूर्ण;
module_platक्रमm_driver(pm8xxx_xoadc_driver);

MODULE_DESCRIPTION("PM8xxx XOADC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pm8xxx-xoadc");
