<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_BOOTPARAMS_HEADER_H__
#घोषणा __RSI_BOOTPARAMS_HEADER_H__

#घोषणा CRYSTAL_GOOD_TIME                BIT(0)
#घोषणा BOOTUP_MODE_INFO                 BIT(1)
#घोषणा WIFI_TAPLL_CONFIGS               BIT(5)
#घोषणा WIFI_PLL960_CONFIGS              BIT(6)
#घोषणा WIFI_AFEPLL_CONFIGS              BIT(7)
#घोषणा WIFI_SWITCH_CLK_CONFIGS          BIT(8)

#घोषणा TA_PLL_M_VAL_20                  9
#घोषणा TA_PLL_N_VAL_20                  0
#घोषणा TA_PLL_P_VAL_20                  4

#घोषणा PLL960_M_VAL_20                  0x14
#घोषणा PLL960_N_VAL_20                  0
#घोषणा PLL960_P_VAL_20                  5

#घोषणा UMAC_CLK_40MHZ                   80

#घोषणा TA_PLL_M_VAL_40                  9
#घोषणा TA_PLL_N_VAL_40                  0
#घोषणा TA_PLL_P_VAL_40                  4

#घोषणा PLL960_M_VAL_40                  0x14
#घोषणा PLL960_N_VAL_40                  0
#घोषणा PLL960_P_VAL_40                  5

#घोषणा UMAC_CLK_20BW \
	(((TA_PLL_M_VAL_20 + 1) * 40) / \
	 ((TA_PLL_N_VAL_20 + 1) * (TA_PLL_P_VAL_20 + 1)))
#घोषणा VALID_20 \
	(WIFI_TAPLL_CONFIGS | WIFI_PLL960_CONFIGS | WIFI_AFEPLL_CONFIGS | \
	 WIFI_SWITCH_CLK_CONFIGS | BOOTUP_MODE_INFO | CRYSTAL_GOOD_TIME)
#घोषणा UMAC_CLK_40BW   \
	(((TA_PLL_M_VAL_40 + 1) * 40) / \
	 ((TA_PLL_N_VAL_40 + 1) * (TA_PLL_P_VAL_40 + 1)))
#घोषणा VALID_40 \
	(WIFI_PLL960_CONFIGS | WIFI_AFEPLL_CONFIGS | WIFI_SWITCH_CLK_CONFIGS | \
	 WIFI_TAPLL_CONFIGS | CRYSTAL_GOOD_TIME | BOOTUP_MODE_INFO)

/* काष्ठाure to store configs related to TAPLL programming */
काष्ठा tapll_info अणु
	__le16 pll_reg_1;
	__le16 pll_reg_2;
पूर्ण __packed;

/* काष्ठाure to store configs related to PLL960 programming */
काष्ठा pll960_info अणु
	__le16 pll_reg_1;
	__le16 pll_reg_2;
	__le16 pll_reg_3;
पूर्ण __packed;

/* काष्ठाure to store configs related to AFEPLL programming */
काष्ठा afepll_info अणु
	__le16 pll_reg;
पूर्ण __packed;

/* काष्ठाure to store configs related to pll configs */
काष्ठा pll_config अणु
	काष्ठा tapll_info tapll_info_g;
	काष्ठा pll960_info pll960_info_g;
	काष्ठा afepll_info afepll_info_g;
पूर्ण __packed;

काष्ठा pll_config_9116 अणु
	__le16 pll_ctrl_set_reg;
	__le16 pll_ctrl_clr_reg;
	__le16 pll_modem_conig_reg;
	__le16 soc_clk_config_reg;
	__le16 adc_dac_strm1_config_reg;
	__le16 adc_dac_strm2_config_reg;
पूर्ण __packed;

/* काष्ठाure to store configs related to UMAC clk programming */
काष्ठा चयन_clk अणु
	__le16 चयन_clk_info;
	/* If चयन_bbp_lmac_clk_reg is set then this value will be programmed
	 * पूर्णांकo reg
	 */
	__le16 bbp_lmac_clk_reg_val;
	/* अगर चयन_umac_clk is set then this value will be programmed */
	__le16 umac_घड़ी_reg_config;
	/* अगर चयन_qspi_clk is set then this value will be programmed */
	__le16 qspi_uart_घड़ी_reg_config;
पूर्ण __packed;

#घोषणा RSI_SWITCH_TASS_CLK			BIT(0)
#घोषणा RSI_SWITCH_QSPI_CLK			BIT(1)
#घोषणा RSI_SWITCH_SLP_CLK_2_32			BIT(2)
#घोषणा RSI_SWITCH_WLAN_BBP_LMAC_CLK_REG	BIT(3)
#घोषणा RSI_SWITCH_ZBBT_BBP_LMAC_CLK_REG	BIT(4)
#घोषणा RSI_SWITCH_BBP_LMAC_CLK_REG		BIT(5)
#घोषणा RSI_MODEM_CLK_160MHZ			BIT(6)

काष्ठा चयन_clk_9116 अणु
	__le32 चयन_clk_info;
	__le32 tass_घड़ी_reg;
	__le32 wlan_bbp_lmac_clk_reg_val;
	__le32 zbbt_bbp_lmac_clk_reg_val;
	__le32 bbp_lmac_clk_en_val;
पूर्ण __packed;

काष्ठा device_clk_info अणु
	काष्ठा pll_config pll_config_g;
	काष्ठा चयन_clk चयन_clk_g;
पूर्ण __packed;

काष्ठा device_clk_info_9116 अणु
	काष्ठा pll_config_9116 pll_config_9116_g;
	काष्ठा चयन_clk_9116 चयन_clk_9116_g;
पूर्ण __packed;

काष्ठा bootup_params अणु
	__le16 magic_number;
	__le16 crystal_good_समय;
	__le32 valid;
	__le32 reserved_क्रम_valids;
	__le16 bootup_mode_info;
	/* configuration used क्रम digital loop back */
	__le16 digital_loop_back_params;
	__le16 rtls_बारtamp_en;
	__le16 host_spi_पूर्णांकr_cfg;
	काष्ठा device_clk_info device_clk_info[3];
	/* ulp buckboost रुको समय  */
	__le32 buckboost_wakeup_cnt;
	/* pmu wakeup रुको समय & WDT EN info */
	__le16 pmu_wakeup_रुको;
	u8 shutकरोwn_रुको_समय;
	/* Sleep घड़ी source selection */
	u8 pmu_slp_clkout_sel;
	/* WDT programming values */
	__le32 wdt_prog_value;
	/* WDT soc reset delay */
	__le32 wdt_soc_rst_delay;
	/* dcdc modes configs */
	__le32 dcdc_operation_mode;
	__le32 soc_reset_रुको_cnt;
	__le32 रुकोing_समय_at_fresh_sleep;
	__le32 max_threshold_to_aव्योम_sleep;
	u8 beacon_resedue_alg_en;
पूर्ण __packed;

काष्ठा bootup_params_9116 अणु
	__le16 magic_number;
#घोषणा LOADED_TOKEN  0x5AA5   /* Bootup params are installed by host
				* or OTP/FLASH (Bootloader)
				*/
#घोषणा ROM_TOKEN     0x55AA   /* Bootup params are taken from ROM
				* itself in MCU mode.
				*/
	__le16 crystal_good_समय;
	__le32 valid;
	__le32 reserved_क्रम_valids;
	__le16 bootup_mode_info;
#घोषणा BT_COEXIST		BIT(0)
#घोषणा BOOTUP_MODE		(BIT(2) | BIT(1))
#घोषणा CUR_DEV_MODE_9116	(bootup_params_9116.bootup_mode_info >> 1)
	__le16 digital_loop_back_params;
	__le16 rtls_बारtamp_en;
	__le16 host_spi_पूर्णांकr_cfg;
	काष्ठा device_clk_info_9116 device_clk_info_9116[1];
	__le32 buckboost_wakeup_cnt;
	__le16 pmu_wakeup_रुको;
	u8 shutकरोwn_रुको_समय;
	u8 pmu_slp_clkout_sel;
	__le32 wdt_prog_value;
	__le32 wdt_soc_rst_delay;
	__le32 dcdc_operation_mode;
	__le32 soc_reset_रुको_cnt;
	__le32 रुकोing_समय_at_fresh_sleep;
	__le32 max_threshold_to_aव्योम_sleep;
	u8 beacon_resedue_alg_en;
पूर्ण __packed;

#पूर्ण_अगर
