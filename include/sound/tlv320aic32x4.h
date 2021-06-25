<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tlv320aic32x4.h  --  TLV320AIC32X4 Soc Audio driver platक्रमm data
 *
 * Copyright 2011 Vista Silicon S.L.
 *
 * Author: Javier Martin <javier.martin@vista-silicon.com>
 */

#अगर_अघोषित _AIC32X4_PDATA_H
#घोषणा _AIC32X4_PDATA_H

#घोषणा AIC32X4_PWR_MICBIAS_2075_LDOIN		0x00000001
#घोषणा AIC32X4_PWR_AVDD_DVDD_WEAK_DISABLE	0x00000002
#घोषणा AIC32X4_PWR_AIC32X4_LDO_ENABLE		0x00000004
#घोषणा AIC32X4_PWR_CMMODE_LDOIN_RANGE_18_36	0x00000008
#घोषणा AIC32X4_PWR_CMMODE_HP_LDOIN_POWERED	0x00000010

#घोषणा AIC32X4_MICPGA_ROUTE_LMIC_IN2R_10K	0x00000001
#घोषणा AIC32X4_MICPGA_ROUTE_RMIC_IN1L_10K	0x00000002

/* GPIO API */
#घोषणा AIC32X4_MFPX_DEFAULT_VALUE	0xff

#घोषणा AIC32X4_MFP1_DIN_DISABLED	0
#घोषणा AIC32X4_MFP1_DIN_ENABLED	0x2
#घोषणा AIC32X4_MFP1_GPIO_IN		0x4

#घोषणा AIC32X4_MFP2_GPIO_OUT_LOW	0x0
#घोषणा AIC32X4_MFP2_GPIO_OUT_HIGH	0x1

#घोषणा AIC32X4_MFP_GPIO_ENABLED	0x4

#घोषणा AIC32X4_MFP5_GPIO_DISABLED	0x0
#घोषणा AIC32X4_MFP5_GPIO_INPUT		0x8
#घोषणा AIC32X4_MFP5_GPIO_OUTPUT	0xc
#घोषणा AIC32X4_MFP5_GPIO_OUT_LOW	0x0
#घोषणा AIC32X4_MFP5_GPIO_OUT_HIGH	0x1

काष्ठा aic32x4_setup_data अणु
	अचिन्हित पूर्णांक gpio_func[5];
पूर्ण;

काष्ठा aic32x4_pdata अणु
	काष्ठा aic32x4_setup_data *setup;
	u32 घातer_cfg;
	u32 micpga_routing;
	bool swapdacs;
	पूर्णांक rstn_gpio;
पूर्ण;

#पूर्ण_अगर
