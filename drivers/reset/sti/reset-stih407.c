<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 STMicroelectronics (R&D) Limited
 * Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/reset/stih407-resets.h>
#समावेश "reset-syscfg.h"

/* STiH407 Peripheral घातerकरोwn definitions. */
अटल स्थिर अक्षर stih407_core[] = "st,stih407-core-syscfg";
अटल स्थिर अक्षर stih407_sbc_reg[] = "st,stih407-sbc-reg-syscfg";
अटल स्थिर अक्षर stih407_lpm[] = "st,stih407-lpm-syscfg";

#घोषणा STIH407_PDN_0(_bit) \
	_SYSCFG_RST_CH(stih407_core, SYSCFG_5000, _bit, SYSSTAT_5500, _bit)
#घोषणा STIH407_PDN_1(_bit) \
	_SYSCFG_RST_CH(stih407_core, SYSCFG_5001, _bit, SYSSTAT_5501, _bit)
#घोषणा STIH407_PDN_ETH(_bit, _stat) \
	_SYSCFG_RST_CH(stih407_sbc_reg, SYSCFG_4032, _bit, SYSSTAT_4520, _stat)

/* Powerकरोwn requests control 0 */
#घोषणा SYSCFG_5000	0x0
#घोषणा SYSSTAT_5500	0x7d0
/* Powerकरोwn requests control 1 (High Speed Links) */
#घोषणा SYSCFG_5001	0x4
#घोषणा SYSSTAT_5501	0x7d4

/* Ethernet घातerकरोwn/status/reset */
#घोषणा SYSCFG_4032	0x80
#घोषणा SYSSTAT_4520	0x820
#घोषणा SYSCFG_4002	0x8

अटल स्थिर काष्ठा syscfg_reset_channel_data stih407_घातerकरोwns[] = अणु
	[STIH407_EMISS_POWERDOWN] = STIH407_PDN_0(1),
	[STIH407_न_अंकD_POWERDOWN] = STIH407_PDN_0(0),
	[STIH407_USB3_POWERDOWN] = STIH407_PDN_1(6),
	[STIH407_USB2_PORT1_POWERDOWN] = STIH407_PDN_1(5),
	[STIH407_USB2_PORT0_POWERDOWN] = STIH407_PDN_1(4),
	[STIH407_PCIE1_POWERDOWN] = STIH407_PDN_1(3),
	[STIH407_PCIE0_POWERDOWN] = STIH407_PDN_1(2),
	[STIH407_SATA1_POWERDOWN] = STIH407_PDN_1(1),
	[STIH407_SATA0_POWERDOWN] = STIH407_PDN_1(0),
	[STIH407_ETH1_POWERDOWN] = STIH407_PDN_ETH(0, 2),
पूर्ण;

/* Reset Generator control 0/1 */
#घोषणा SYSCFG_5128	0x200
#घोषणा SYSCFG_5131	0x20c
#घोषणा SYSCFG_5132	0x210

#घोषणा LPM_SYSCFG_1	0x4	/* Softreset IRB & SBC UART */

#घोषणा STIH407_SRST_CORE(_reg, _bit) \
	_SYSCFG_RST_CH_NO_ACK(stih407_core, _reg, _bit)

#घोषणा STIH407_SRST_SBC(_reg, _bit) \
	_SYSCFG_RST_CH_NO_ACK(stih407_sbc_reg, _reg, _bit)

#घोषणा STIH407_SRST_LPM(_reg, _bit) \
	_SYSCFG_RST_CH_NO_ACK(stih407_lpm, _reg, _bit)

अटल स्थिर काष्ठा syscfg_reset_channel_data stih407_softresets[] = अणु
	[STIH407_ETH1_SOFTRESET] = STIH407_SRST_SBC(SYSCFG_4002, 4),
	[STIH407_MMC1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 3),
	[STIH407_USB2_PORT0_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 28),
	[STIH407_USB2_PORT1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 29),
	[STIH407_PICOPHY_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 30),
	[STIH407_IRB_SOFTRESET] = STIH407_SRST_LPM(LPM_SYSCFG_1, 6),
	[STIH407_PCIE0_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 6),
	[STIH407_PCIE1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 15),
	[STIH407_SATA0_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 7),
	[STIH407_SATA1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 16),
	[STIH407_MIPHY0_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 4),
	[STIH407_MIPHY1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 13),
	[STIH407_MIPHY2_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 22),
	[STIH407_SATA0_PWR_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 5),
	[STIH407_SATA1_PWR_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 14),
	[STIH407_DELTA_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 3),
	[STIH407_BLITTER_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 10),
	[STIH407_HDTVOUT_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 11),
	[STIH407_HDQVDP_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 12),
	[STIH407_VDP_AUX_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 14),
	[STIH407_COMPO_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 15),
	[STIH407_HDMI_TX_PHY_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 21),
	[STIH407_JPEG_DEC_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 23),
	[STIH407_VP8_DEC_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 24),
	[STIH407_GPU_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 30),
	[STIH407_HVA_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 0),
	[STIH407_ERAM_HVA_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5132, 1),
	[STIH407_LPM_SOFTRESET] = STIH407_SRST_SBC(SYSCFG_4002, 2),
	[STIH407_KEYSCAN_SOFTRESET] = STIH407_SRST_LPM(LPM_SYSCFG_1, 8),
	[STIH407_ST231_AUD_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 26),
	[STIH407_ST231_DMU_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 27),
	[STIH407_ST231_GP0_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5131, 28),
	[STIH407_ST231_GP1_SOFTRESET] = STIH407_SRST_CORE(SYSCFG_5128, 2),
पूर्ण;

/* PicoPHY reset/control */
#घोषणा SYSCFG_5061	0x0f4

अटल स्थिर काष्ठा syscfg_reset_channel_data stih407_picophyresets[] = अणु
	[STIH407_PICOPHY0_RESET] = STIH407_SRST_CORE(SYSCFG_5061, 5),
	[STIH407_PICOPHY1_RESET] = STIH407_SRST_CORE(SYSCFG_5061, 6),
	[STIH407_PICOPHY2_RESET] = STIH407_SRST_CORE(SYSCFG_5061, 7),
पूर्ण;

अटल स्थिर काष्ठा syscfg_reset_controller_data stih407_घातerकरोwn_controller = अणु
	.रुको_क्रम_ack = true,
	.nr_channels = ARRAY_SIZE(stih407_घातerकरोwns),
	.channels = stih407_घातerकरोwns,
पूर्ण;

अटल स्थिर काष्ठा syscfg_reset_controller_data stih407_softreset_controller = अणु
	.रुको_क्रम_ack = false,
	.active_low = true,
	.nr_channels = ARRAY_SIZE(stih407_softresets),
	.channels = stih407_softresets,
पूर्ण;

अटल स्थिर काष्ठा syscfg_reset_controller_data stih407_picophyreset_controller = अणु
	.रुको_क्रम_ack = false,
	.nr_channels = ARRAY_SIZE(stih407_picophyresets),
	.channels = stih407_picophyresets,
पूर्ण;

अटल स्थिर काष्ठा of_device_id stih407_reset_match[] = अणु
	अणु
		.compatible = "st,stih407-powerdown",
		.data = &stih407_घातerकरोwn_controller,
	पूर्ण,
	अणु
		.compatible = "st,stih407-softreset",
		.data = &stih407_softreset_controller,
	पूर्ण,
	अणु
		.compatible = "st,stih407-picophyreset",
		.data = &stih407_picophyreset_controller,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver stih407_reset_driver = अणु
	.probe = syscfg_reset_probe,
	.driver = अणु
		.name = "reset-stih407",
		.of_match_table = stih407_reset_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init stih407_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&stih407_reset_driver);
पूर्ण

arch_initcall(stih407_reset_init);
