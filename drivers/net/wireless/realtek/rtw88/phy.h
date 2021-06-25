<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_PHY_H_
#घोषणा __RTW_PHY_H_

#समावेश "debug.h"

बाह्य u8 rtw_cck_rates[];
बाह्य u8 rtw_ofdm_rates[];
बाह्य u8 rtw_ht_1s_rates[];
बाह्य u8 rtw_ht_2s_rates[];
बाह्य u8 rtw_vht_1s_rates[];
बाह्य u8 rtw_vht_2s_rates[];
बाह्य u8 *rtw_rate_section[];
बाह्य u8 rtw_rate_size[];

व्योम rtw_phy_init(काष्ठा rtw_dev *rtwdev);
व्योम rtw_phy_dynamic_mechanism(काष्ठा rtw_dev *rtwdev);
u8 rtw_phy_rf_घातer_2_rssi(s8 *rf_घातer, u8 path_num);
u32 rtw_phy_पढ़ो_rf(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
		    u32 addr, u32 mask);
u32 rtw_phy_पढ़ो_rf_sipi(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			 u32 addr, u32 mask);
bool rtw_phy_ग_लिखो_rf_reg_sipi(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			       u32 addr, u32 mask, u32 data);
bool rtw_phy_ग_लिखो_rf_reg(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			  u32 addr, u32 mask, u32 data);
bool rtw_phy_ग_लिखो_rf_reg_mix(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			      u32 addr, u32 mask, u32 data);
व्योम rtw_phy_setup_phy_cond(काष्ठा rtw_dev *rtwdev, u32 pkg);
व्योम rtw_parse_tbl_phy_cond(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl);
व्योम rtw_parse_tbl_bb_pg(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl);
व्योम rtw_parse_tbl_txpwr_lmt(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl);
व्योम rtw_phy_cfg_mac(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		     u32 addr, u32 data);
व्योम rtw_phy_cfg_agc(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		     u32 addr, u32 data);
व्योम rtw_phy_cfg_bb(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		    u32 addr, u32 data);
व्योम rtw_phy_cfg_rf(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		    u32 addr, u32 data);
व्योम rtw_phy_init_tx_घातer(काष्ठा rtw_dev *rtwdev);
व्योम rtw_phy_load_tables(काष्ठा rtw_dev *rtwdev);
u8 rtw_phy_get_tx_घातer_index(काष्ठा rtw_dev *rtwdev, u8 rf_path, u8 rate,
			      क्रमागत rtw_bandwidth bw, u8 channel, u8 regd);
व्योम rtw_phy_set_tx_घातer_level(काष्ठा rtw_dev *rtwdev, u8 channel);
व्योम rtw_phy_tx_घातer_by_rate_config(काष्ठा rtw_hal *hal);
व्योम rtw_phy_tx_घातer_limit_config(काष्ठा rtw_hal *hal);
व्योम rtw_phy_pwrtrack_avg(काष्ठा rtw_dev *rtwdev, u8 thermal, u8 path);
bool rtw_phy_pwrtrack_thermal_changed(काष्ठा rtw_dev *rtwdev, u8 thermal,
				      u8 path);
u8 rtw_phy_pwrtrack_get_delta(काष्ठा rtw_dev *rtwdev, u8 path);
s8 rtw_phy_pwrtrack_get_pwridx(काष्ठा rtw_dev *rtwdev,
			       काष्ठा rtw_swing_table *swing_table,
			       u8 tbl_path, u8 therm_path, u8 delta);
bool rtw_phy_pwrtrack_need_lck(काष्ठा rtw_dev *rtwdev);
bool rtw_phy_pwrtrack_need_iqk(काष्ठा rtw_dev *rtwdev);
व्योम rtw_phy_config_swing_table(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_swing_table *swing_table);
व्योम rtw_phy_parsing_cfo(काष्ठा rtw_dev *rtwdev,
			 काष्ठा rtw_rx_pkt_stat *pkt_stat);

काष्ठा rtw_txpwr_lmt_cfg_pair अणु
	u8 regd;
	u8 band;
	u8 bw;
	u8 rs;
	u8 ch;
	s8 txpwr_lmt;
पूर्ण;

काष्ठा rtw_phy_pg_cfg_pair अणु
	u32 band;
	u32 rf_path;
	u32 tx_num;
	u32 addr;
	u32 biपंचांगask;
	u32 data;
पूर्ण;

#घोषणा RTW_DECL_TABLE_PHY_COND_CORE(name, cfg, path)	\
स्थिर काष्ठा rtw_table name ## _tbl = अणु			\
	.data = name,					\
	.size = ARRAY_SIZE(name),			\
	.parse = rtw_parse_tbl_phy_cond,		\
	.करो_cfg = cfg,					\
	.rf_path = path,				\
पूर्ण

#घोषणा RTW_DECL_TABLE_PHY_COND(name, cfg)		\
	RTW_DECL_TABLE_PHY_COND_CORE(name, cfg, 0)

#घोषणा RTW_DECL_TABLE_RF_RADIO(name, path)		\
	RTW_DECL_TABLE_PHY_COND_CORE(name, rtw_phy_cfg_rf, RF_PATH_ ## path)

#घोषणा RTW_DECL_TABLE_BB_PG(name)			\
स्थिर काष्ठा rtw_table name ## _tbl = अणु			\
	.data = name,					\
	.size = ARRAY_SIZE(name),			\
	.parse = rtw_parse_tbl_bb_pg,			\
पूर्ण

#घोषणा RTW_DECL_TABLE_TXPWR_LMT(name)			\
स्थिर काष्ठा rtw_table name ## _tbl = अणु			\
	.data = name,					\
	.size = ARRAY_SIZE(name),			\
	.parse = rtw_parse_tbl_txpwr_lmt,		\
पूर्ण

अटल अंतरभूत स्थिर काष्ठा rtw_rfe_def *rtw_get_rfe_def(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	स्थिर काष्ठा rtw_rfe_def *rfe_def = शून्य;

	अगर (chip->rfe_defs_size == 0)
		वापस शून्य;

	अगर (efuse->rfe_option < chip->rfe_defs_size)
		rfe_def = &chip->rfe_defs[efuse->rfe_option];

	rtw_dbg(rtwdev, RTW_DBG_PHY, "use rfe_def[%d]\n", efuse->rfe_option);
	वापस rfe_def;
पूर्ण

अटल अंतरभूत पूर्णांक rtw_check_supported_rfe(काष्ठा rtw_dev *rtwdev)
अणु
	स्थिर काष्ठा rtw_rfe_def *rfe_def = rtw_get_rfe_def(rtwdev);

	अगर (!rfe_def || !rfe_def->phy_pg_tbl || !rfe_def->txpwr_lmt_tbl) अणु
		rtw_err(rtwdev, "rfe %d isn't supported\n",
			rtwdev->efuse.rfe_option);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rtw_phy_dig_ग_लिखो(काष्ठा rtw_dev *rtwdev, u8 igi);

काष्ठा rtw_घातer_params अणु
	u8 pwr_base;
	s8 pwr_offset;
	s8 pwr_limit;
	s8 pwr_remnant;
पूर्ण;

व्योम
rtw_get_tx_घातer_params(काष्ठा rtw_dev *rtwdev, u8 path,
			u8 rate, u8 bw, u8 ch, u8 regd,
			काष्ठा rtw_घातer_params *pwr_param);

क्रमागत rtw_phy_cck_pd_lv अणु
	CCK_PD_LV0,
	CCK_PD_LV1,
	CCK_PD_LV2,
	CCK_PD_LV3,
	CCK_PD_LV4,
	CCK_PD_LV_MAX,
पूर्ण;

#घोषणा	MASKBYTE0		0xff
#घोषणा	MASKBYTE1		0xff00
#घोषणा	MASKBYTE2		0xff0000
#घोषणा	MASKBYTE3		0xff000000
#घोषणा	MASKHWORD		0xffff0000
#घोषणा	MASKLWORD		0x0000ffff
#घोषणा	MASKDWORD		0xffffffff
#घोषणा RFREG_MASK		0xfffff

#घोषणा	MASK7BITS		0x7f
#घोषणा	MASK12BITS		0xfff
#घोषणा	MASKH4BITS		0xf0000000
#घोषणा	MASK20BITS		0xfffff
#घोषणा	MASK24BITS		0xffffff

#घोषणा MASKH3BYTES		0xffffff00
#घोषणा MASKL3BYTES		0x00ffffff
#घोषणा MASKBYTE2HIGHNIBBLE	0x00f00000
#घोषणा MASKBYTE3LOWNIBBLE	0x0f000000
#घोषणा	MASKL3BYTES		0x00ffffff

#घोषणा CCK_FA_AVG_RESET 0xffffffff

#घोषणा LSSI_READ_ADDR_MASK	0x7f800000
#घोषणा LSSI_READ_EDGE_MASK	0x80000000
#घोषणा LSSI_READ_DATA_MASK	0xfffff

#घोषणा RRSR_RATE_ORDER_MAX	0xfffff
#घोषणा RRSR_RATE_ORDER_CCK_LEN	4

#पूर्ण_अगर
