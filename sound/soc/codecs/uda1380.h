<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Audio support क्रम Philips UDA1380
 *
 * Copyright (c) 2005 Giorgio Padrin <giorgio@mandarinlogiq.org>
 */

#अगर_अघोषित _UDA1380_H
#घोषणा _UDA1380_H

#घोषणा UDA1380_CLK	0x00
#घोषणा UDA1380_IFACE	0x01
#घोषणा UDA1380_PM	0x02
#घोषणा UDA1380_AMIX	0x03
#घोषणा UDA1380_HP	0x04
#घोषणा UDA1380_MVOL	0x10
#घोषणा UDA1380_MIXVOL	0x11
#घोषणा UDA1380_MODE	0x12
#घोषणा UDA1380_DEEMP	0x13
#घोषणा UDA1380_MIXER	0x14
#घोषणा UDA1380_INTSTAT	0x18
#घोषणा UDA1380_DEC	0x20
#घोषणा UDA1380_PGA	0x21
#घोषणा UDA1380_ADC	0x22
#घोषणा UDA1380_AGC	0x23
#घोषणा UDA1380_DECSTAT	0x28
#घोषणा UDA1380_RESET	0x7f

#घोषणा UDA1380_CACHEREGNUM 0x24

/* Register flags */
#घोषणा R00_EN_ADC	0x0800
#घोषणा R00_EN_DEC	0x0400
#घोषणा R00_EN_DAC	0x0200
#घोषणा R00_EN_INT	0x0100
#घोषणा R00_DAC_CLK	0x0010
#घोषणा R01_SFORI_I2S   0x0000
#घोषणा R01_SFORI_LSB16 0x0100
#घोषणा R01_SFORI_LSB18 0x0200
#घोषणा R01_SFORI_LSB20 0x0300
#घोषणा R01_SFORI_MSB   0x0500
#घोषणा R01_SFORI_MASK  0x0700
#घोषणा R01_SFORO_I2S   0x0000
#घोषणा R01_SFORO_LSB16 0x0001
#घोषणा R01_SFORO_LSB18 0x0002
#घोषणा R01_SFORO_LSB20 0x0003
#घोषणा R01_SFORO_LSB24 0x0004
#घोषणा R01_SFORO_MSB   0x0005
#घोषणा R01_SFORO_MASK  0x0007
#घोषणा R01_SEL_SOURCE  0x0040
#घोषणा R01_SIM		0x0010
#घोषणा R02_PON_PLL	0x8000
#घोषणा R02_PON_HP	0x2000
#घोषणा R02_PON_DAC	0x0400
#घोषणा R02_PON_BIAS	0x0100
#घोषणा R02_EN_AVC	0x0080
#घोषणा R02_PON_AVC	0x0040
#घोषणा R02_PON_LNA	0x0010
#घोषणा R02_PON_PGAL	0x0008
#घोषणा R02_PON_ADCL	0x0004
#घोषणा R02_PON_PGAR	0x0002
#घोषणा R02_PON_ADCR	0x0001
#घोषणा R13_MTM		0x4000
#घोषणा R14_SILENCE	0x0080
#घोषणा R14_SDET_ON	0x0040
#घोषणा R21_MT_ADC	0x8000
#घोषणा R22_SEL_LNA	0x0008
#घोषणा R22_SEL_MIC	0x0004
#घोषणा R22_SKIP_DCFIL	0x0002
#घोषणा R23_AGC_EN	0x0001

#पूर्ण_अगर /* _UDA1380_H */
