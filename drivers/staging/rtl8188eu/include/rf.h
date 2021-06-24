<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा RF6052_MAX_TX_PWR	0x3F
#घोषणा RF6052_MAX_REG		0x3F

व्योम rtl88eu_phy_rf6052_set_bandwidth(काष्ठा adapter *adapt,
				      क्रमागत ht_channel_width bandwidth);
व्योम rtl88eu_phy_rf6052_set_cck_txघातer(काष्ठा adapter *adapt,
				       u8 *घातerlevel);
व्योम rtl88eu_phy_rf6052_set_ofdm_txघातer(काष्ठा adapter *adapt,
					 u8 *घातerlevel_ofdm,
					 u8 *घातerlevel_bw20,
					 u8 *घातerlevel_bw40, u8 channel);
