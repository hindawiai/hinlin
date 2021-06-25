<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * adc.h  -- Driver क्रम NXP PCF50633 ADC
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * All rights reserved.
 */

#अगर_अघोषित __LINUX_MFD_PCF50633_ADC_H
#घोषणा __LINUX_MFD_PCF50633_ADC_H

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/platक्रमm_device.h>

/* ADC Registers */
#घोषणा PCF50633_REG_ADCC3		0x52
#घोषणा PCF50633_REG_ADCC2		0x53
#घोषणा PCF50633_REG_ADCC1		0x54
#घोषणा PCF50633_REG_ADCS1		0x55
#घोषणा PCF50633_REG_ADCS2		0x56
#घोषणा PCF50633_REG_ADCS3		0x57

#घोषणा PCF50633_ADCC1_ADCSTART		0x01
#घोषणा PCF50633_ADCC1_RES_8BIT		0x02
#घोषणा PCF50633_ADCC1_RES_10BIT	0x00
#घोषणा PCF50633_ADCC1_AVERAGE_NO	0x00
#घोषणा PCF50633_ADCC1_AVERAGE_4	0x04
#घोषणा PCF50633_ADCC1_AVERAGE_8	0x08
#घोषणा PCF50633_ADCC1_AVERAGE_16	0x0c
#घोषणा PCF50633_ADCC1_MUX_BATSNS_RES	0x00
#घोषणा PCF50633_ADCC1_MUX_BATSNS_SUBTR	0x10
#घोषणा PCF50633_ADCC1_MUX_ADCIN2_RES	0x20
#घोषणा PCF50633_ADCC1_MUX_ADCIN2_SUBTR	0x30
#घोषणा PCF50633_ADCC1_MUX_BATTEMP	0x60
#घोषणा PCF50633_ADCC1_MUX_ADCIN1	0x70
#घोषणा PCF50633_ADCC1_AVERAGE_MASK	0x0c
#घोषणा PCF50633_ADCC1_ADCMUX_MASK	0xf0

#घोषणा PCF50633_ADCC2_RATIO_NONE	0x00
#घोषणा PCF50633_ADCC2_RATIO_BATTEMP	0x01
#घोषणा PCF50633_ADCC2_RATIO_ADCIN1	0x02
#घोषणा PCF50633_ADCC2_RATIO_BOTH	0x03
#घोषणा PCF50633_ADCC2_RATIOSETTL_100US 0x04

#घोषणा PCF50633_ADCC3_ACCSW_EN		0x01
#घोषणा PCF50633_ADCC3_NTCSW_EN		0x04
#घोषणा PCF50633_ADCC3_RES_DIV_TWO	0x10
#घोषणा PCF50633_ADCC3_RES_DIV_THREE	0x00

#घोषणा PCF50633_ADCS3_REF_NTCSW	0x00
#घोषणा PCF50633_ADCS3_REF_ACCSW	0x10
#घोषणा PCF50633_ADCS3_REF_2V0		0x20
#घोषणा PCF50633_ADCS3_REF_VISA		0x30
#घोषणा PCF50633_ADCS3_REF_2V0_2	0x70
#घोषणा PCF50633_ADCS3_ADCRDY		0x80

#घोषणा PCF50633_ADCS3_ADCDAT1L_MASK	0x03
#घोषणा PCF50633_ADCS3_ADCDAT2L_MASK	0x0c
#घोषणा PCF50633_ADCS3_ADCDAT2L_SHIFT	2
#घोषणा PCF50633_ASCS3_REF_MASK		0x70

बाह्य पूर्णांक
pcf50633_adc_async_पढ़ो(काष्ठा pcf50633 *pcf, पूर्णांक mux, पूर्णांक avg,
		व्योम (*callback)(काष्ठा pcf50633 *, व्योम *, पूर्णांक),
		व्योम *callback_param);
बाह्य पूर्णांक
pcf50633_adc_sync_पढ़ो(काष्ठा pcf50633 *pcf, पूर्णांक mux, पूर्णांक avg);

#पूर्ण_अगर /* __LINUX_PCF50633_ADC_H */
