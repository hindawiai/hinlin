<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <odm.h>

#घोषणा IQK_DELAY_TIME_88E	    10
#घोषणा index_mapping_NUM_88E	    15
#घोषणा AVG_THERMAL_NUM_88E	    4

bool rtl88eu_phy_mac_config(काष्ठा adapter *adapt);
bool rtl88eu_phy_rf_config(काष्ठा adapter *adapt);
bool rtl88eu_phy_bb_config(काष्ठा adapter *adapt);

u32 phy_query_bb_reg(काष्ठा adapter *adapt, u32 regaddr, u32 biपंचांगask);
व्योम phy_set_bb_reg(काष्ठा adapter *adapt, u32 regaddr, u32 biपंचांगask, u32 data);
u32 rtw_hal_पढ़ो_rfreg(काष्ठा adapter *adapt, क्रमागत rf_radio_path rf_path,
		     u32 reg_addr, u32 bit_mask);
व्योम phy_set_rf_reg(काष्ठा adapter *adapt, क्रमागत rf_radio_path rf_path,
		    u32 reg_addr, u32 bit_mask, u32 data);

व्योम phy_set_tx_घातer_level(काष्ठा adapter *adapt, u8 channel);

व्योम rtl88eu_dm_txघातer_track_adjust(काष्ठा odm_dm_काष्ठा *dm_odm,
				     u8 type, u8 *dir, u32 *out_ग_लिखो);

व्योम rtl88eu_dm_txघातer_tracking_callback_thermalmeter(काष्ठा adapter *adapt);
व्योम rtl88eu_phy_iq_calibrate(काष्ठा adapter *adapter, bool recovery);
व्योम rtl88eu_phy_lc_calibrate(काष्ठा adapter *adapter);
