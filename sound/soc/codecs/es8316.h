<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright Everest Semiconductor Co.,Ltd
 *
 * Author: David Yang <yangxiaohua@everest-semi.com>
 */

#अगर_अघोषित _ES8316_H
#घोषणा _ES8316_H

/*
 * ES8316 रेजिस्टर space
 */

/* Reset Control */
#घोषणा ES8316_RESET		0x00

/* Clock Management */
#घोषणा ES8316_CLKMGR_CLKSW	0x01
#घोषणा ES8316_CLKMGR_CLKSEL	0x02
#घोषणा ES8316_CLKMGR_ADCOSR	0x03
#घोषणा ES8316_CLKMGR_ADCDIV1	0x04
#घोषणा ES8316_CLKMGR_ADCDIV2	0x05
#घोषणा ES8316_CLKMGR_DACDIV1	0x06
#घोषणा ES8316_CLKMGR_DACDIV2	0x07
#घोषणा ES8316_CLKMGR_CPDIV	0x08

/* Serial Data Port Control */
#घोषणा ES8316_SERDATA1		0x09
#घोषणा ES8316_SERDATA_ADC	0x0a
#घोषणा ES8316_SERDATA_DAC	0x0b

/* System Control */
#घोषणा ES8316_SYS_VMIDSEL	0x0c
#घोषणा ES8316_SYS_PDN		0x0d
#घोषणा ES8316_SYS_LP1		0x0e
#घोषणा ES8316_SYS_LP2		0x0f
#घोषणा ES8316_SYS_VMIDLOW	0x10
#घोषणा ES8316_SYS_VSEL		0x11
#घोषणा ES8316_SYS_REF		0x12

/* Headphone Mixer */
#घोषणा ES8316_HPMIX_SEL	0x13
#घोषणा ES8316_HPMIX_SWITCH	0x14
#घोषणा ES8316_HPMIX_PDN	0x15
#घोषणा ES8316_HPMIX_VOL	0x16

/* Charge Pump Headphone driver */
#घोषणा ES8316_CPHP_OUTEN	0x17
#घोषणा ES8316_CPHP_ICAL_VOL	0x18
#घोषणा ES8316_CPHP_PDN1	0x19
#घोषणा ES8316_CPHP_PDN2	0x1a
#घोषणा ES8316_CPHP_LDOCTL	0x1b

/* Calibration */
#घोषणा ES8316_CAL_TYPE		0x1c
#घोषणा ES8316_CAL_SET		0x1d
#घोषणा ES8316_CAL_HPLIV	0x1e
#घोषणा ES8316_CAL_HPRIV	0x1f
#घोषणा ES8316_CAL_HPLMV	0x20
#घोषणा ES8316_CAL_HPRMV	0x21

/* ADC Control */
#घोषणा ES8316_ADC_PDN_LINSEL	0x22
#घोषणा ES8316_ADC_PGAGAIN	0x23
#घोषणा ES8316_ADC_D2SEPGA	0x24
#घोषणा ES8316_ADC_DMIC		0x25
#घोषणा ES8316_ADC_MUTE		0x26
#घोषणा ES8316_ADC_VOLUME	0x27
#घोषणा ES8316_ADC_ALC1		0x29
#घोषणा ES8316_ADC_ALC2		0x2a
#घोषणा ES8316_ADC_ALC3		0x2b
#घोषणा ES8316_ADC_ALC4		0x2c
#घोषणा ES8316_ADC_ALC5		0x2d
#घोषणा ES8316_ADC_ALC_NG	0x2e

/* DAC Control */
#घोषणा ES8316_DAC_PDN		0x2f
#घोषणा ES8316_DAC_SET1		0x30
#घोषणा ES8316_DAC_SET2		0x31
#घोषणा ES8316_DAC_SET3		0x32
#घोषणा ES8316_DAC_VOLL		0x33
#घोषणा ES8316_DAC_VOLR		0x34

/* GPIO */
#घोषणा ES8316_GPIO_SEL		0x4d
#घोषणा ES8316_GPIO_DEBOUNCE	0x4e
#घोषणा ES8316_GPIO_FLAG	0x4f

/* Test mode */
#घोषणा ES8316_TESTMODE		0x50
#घोषणा ES8316_TEST1		0x51
#घोषणा ES8316_TEST2		0x52
#घोषणा ES8316_TEST3		0x53

/*
 * Field definitions
 */

/* ES8316_RESET */
#घोषणा ES8316_RESET_CSM_ON		0x80

/* ES8316_CLKMGR_CLKSW */
#घोषणा ES8316_CLKMGR_CLKSW_MCLK_ON	0x40
#घोषणा ES8316_CLKMGR_CLKSW_BCLK_ON	0x20

/* ES8316_SERDATA1 */
#घोषणा ES8316_SERDATA1_MASTER		0x80
#घोषणा ES8316_SERDATA1_BCLK_INV	0x20

/* ES8316_SERDATA_ADC and _DAC */
#घोषणा ES8316_SERDATA2_FMT_MASK	0x3
#घोषणा ES8316_SERDATA2_FMT_I2S		0x00
#घोषणा ES8316_SERDATA2_FMT_LEFTJ	0x01
#घोषणा ES8316_SERDATA2_FMT_RIGHTJ	0x02
#घोषणा ES8316_SERDATA2_FMT_PCM		0x03
#घोषणा ES8316_SERDATA2_ADCLRP		0x20
#घोषणा ES8316_SERDATA2_LEN_MASK	0x1c
#घोषणा ES8316_SERDATA2_LEN_24		0x00
#घोषणा ES8316_SERDATA2_LEN_20		0x04
#घोषणा ES8316_SERDATA2_LEN_18		0x08
#घोषणा ES8316_SERDATA2_LEN_16		0x0c
#घोषणा ES8316_SERDATA2_LEN_32		0x10

/* ES8316_GPIO_DEBOUNCE	*/
#घोषणा ES8316_GPIO_ENABLE_INTERRUPT		0x02

/* ES8316_GPIO_FLAG */
#घोषणा ES8316_GPIO_FLAG_GM_NOT_SHORTED		0x02
#घोषणा ES8316_GPIO_FLAG_HP_NOT_INSERTED	0x04

#पूर्ण_अगर
