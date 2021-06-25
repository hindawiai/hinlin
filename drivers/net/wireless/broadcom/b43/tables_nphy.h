<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_TABLES_NPHY_H_
#घोषणा B43_TABLES_NPHY_H_

#समावेश <linux/types.h>

काष्ठा b43_phy_n_sfo_cfg अणु
	u16 phy_bw1a;
	u16 phy_bw2;
	u16 phy_bw3;
	u16 phy_bw4;
	u16 phy_bw5;
	u16 phy_bw6;
पूर्ण;

काष्ठा b43_wldev;

काष्ठा nphy_txiqcal_ladder अणु
	u8 percent;
	u8 g_env;
पूर्ण;

काष्ठा nphy_rf_control_override_rev2 अणु
	u8 addr0;
	u8 addr1;
	u16 bmask;
	u8 shअगरt;
पूर्ण;

काष्ठा nphy_rf_control_override_rev3 अणु
	u16 val_mask;
	u8 val_shअगरt;
	u8 en_addr0;
	u8 val_addr0;
	u8 en_addr1;
	u8 val_addr1;
पूर्ण;

काष्ठा nphy_rf_control_override_rev7 अणु
	u16 field;
	u16 val_addr_core0;
	u16 val_addr_core1;
	u16 val_mask;
	u8 val_shअगरt;
पूर्ण;

काष्ठा nphy_gain_ctl_workaround_entry अणु
	s8 lna1_gain[4];
	s8 lna2_gain[4];
	u8 gain_db[10];
	u8 gain_bits[10];

	u16 init_gain;
	u16 rfseq_init[4];

	u16 cliphi_gain;
	u16 clipmd_gain;
	u16 cliplo_gain;

	u16 crsmin;
	u16 crsminl;
	u16 crsminu;

	u16 nbclip;
	u16 wlclip;
पूर्ण;

/* Get entry with workaround values क्रम gain ctl. Does not वापस शून्य. */
काष्ठा nphy_gain_ctl_workaround_entry *b43_nphy_get_gain_ctl_workaround_ent(
	काष्ठा b43_wldev *dev, bool ghz5, bool ext_lna);


/* The N-PHY tables. */
#घोषणा B43_NTAB_TYPEMASK		0xF0000000
#घोषणा B43_NTAB_8BIT			0x10000000
#घोषणा B43_NTAB_16BIT			0x20000000
#घोषणा B43_NTAB_32BIT			0x30000000
#घोषणा B43_NTAB8(table, offset)	(((table) << 10) | (offset) | B43_NTAB_8BIT)
#घोषणा B43_NTAB16(table, offset)	(((table) << 10) | (offset) | B43_NTAB_16BIT)
#घोषणा B43_NTAB32(table, offset)	(((table) << 10) | (offset) | B43_NTAB_32BIT)

/* Static N-PHY tables */
#घोषणा B43_NTAB_FRAMESTRUCT		B43_NTAB32(0x0A, 0x000) /* Frame Struct Table */
#घोषणा B43_NTAB_FRAMESTRUCT_SIZE	832
#घोषणा B43_NTAB_FRAMELT		B43_NTAB8 (0x18, 0x000) /* Frame Lookup Table */
#घोषणा B43_NTAB_FRAMELT_SIZE		32
#घोषणा B43_NTAB_TMAP			B43_NTAB32(0x0C, 0x000) /* T Map Table */
#घोषणा B43_NTAB_TMAP_SIZE		448
#घोषणा B43_NTAB_TDTRN			B43_NTAB32(0x0E, 0x000) /* TDTRN Table */
#घोषणा B43_NTAB_TDTRN_SIZE		704
#घोषणा B43_NTAB_INTLEVEL		B43_NTAB32(0x0D, 0x000) /* Int Level Table */
#घोषणा B43_NTAB_INTLEVEL_SIZE		7
#घोषणा B43_NTAB_PILOT			B43_NTAB16(0x0B, 0x000) /* Pilot Table */
#घोषणा B43_NTAB_PILOT_SIZE		88
#घोषणा B43_NTAB_PILOTLT		B43_NTAB32(0x14, 0x000) /* Pilot Lookup Table */
#घोषणा B43_NTAB_PILOTLT_SIZE		6
#घोषणा B43_NTAB_TDI20A0		B43_NTAB32(0x13, 0x080) /* TDI Table 20 Antenna 0 */
#घोषणा B43_NTAB_TDI20A0_SIZE		55
#घोषणा B43_NTAB_TDI20A1		B43_NTAB32(0x13, 0x100) /* TDI Table 20 Antenna 1 */
#घोषणा B43_NTAB_TDI20A1_SIZE		55
#घोषणा B43_NTAB_TDI40A0		B43_NTAB32(0x13, 0x280) /* TDI Table 40 Antenna 0 */
#घोषणा B43_NTAB_TDI40A0_SIZE		110
#घोषणा B43_NTAB_TDI40A1		B43_NTAB32(0x13, 0x300) /* TDI Table 40 Antenna 1 */
#घोषणा B43_NTAB_TDI40A1_SIZE		110
#घोषणा B43_NTAB_BDI			B43_NTAB16(0x15, 0x000) /* BDI Table */
#घोषणा B43_NTAB_BDI_SIZE		6
#घोषणा B43_NTAB_CHANEST		B43_NTAB32(0x16, 0x000) /* Channel Estimate Table */
#घोषणा B43_NTAB_CHANEST_SIZE		96
#घोषणा B43_NTAB_MCS			B43_NTAB8 (0x12, 0x000) /* MCS Table */
#घोषणा B43_NTAB_MCS_SIZE		128

/* Volatile N-PHY tables */
#घोषणा B43_NTAB_NOISEVAR10		B43_NTAB32(0x10, 0x000) /* Noise Var Table 10 */
#घोषणा B43_NTAB_NOISEVAR10_SIZE	256
#घोषणा B43_NTAB_NOISEVAR11		B43_NTAB32(0x10, 0x080) /* Noise Var Table 11 */
#घोषणा B43_NTAB_NOISEVAR11_SIZE	256
#घोषणा B43_NTAB_C0_ESTPLT		B43_NTAB8 (0x1A, 0x000) /* Estimate Power Lookup Table Core 0 */
#घोषणा B43_NTAB_C0_ESTPLT_SIZE		64
#घोषणा B43_NTAB_C0_ADJPLT		B43_NTAB8 (0x1A, 0x040) /* Adjust Power Lookup Table Core 0 */
#घोषणा B43_NTAB_C0_ADJPLT_SIZE		128
#घोषणा B43_NTAB_C0_GAINCTL		B43_NTAB32(0x1A, 0x0C0) /* Gain Control Lookup Table Core 0 */
#घोषणा B43_NTAB_C0_GAINCTL_SIZE	128
#घोषणा B43_NTAB_C0_IQLT		B43_NTAB32(0x1A, 0x140) /* IQ Lookup Table Core 0 */
#घोषणा B43_NTAB_C0_IQLT_SIZE		128
#घोषणा B43_NTAB_C0_LOFEEDTH		B43_NTAB16(0x1A, 0x1C0) /* Local Oscillator Feed Through Lookup Table Core 0 */
#घोषणा B43_NTAB_C0_LOFEEDTH_SIZE	128
#घोषणा B43_NTAB_C1_ESTPLT		B43_NTAB8 (0x1B, 0x000) /* Estimate Power Lookup Table Core 1 */
#घोषणा B43_NTAB_C1_ESTPLT_SIZE		64
#घोषणा B43_NTAB_C1_ADJPLT		B43_NTAB8 (0x1B, 0x040) /* Adjust Power Lookup Table Core 1 */
#घोषणा B43_NTAB_C1_ADJPLT_SIZE		128
#घोषणा B43_NTAB_C1_GAINCTL		B43_NTAB32(0x1B, 0x0C0) /* Gain Control Lookup Table Core 1 */
#घोषणा B43_NTAB_C1_GAINCTL_SIZE	128
#घोषणा B43_NTAB_C1_IQLT		B43_NTAB32(0x1B, 0x140) /* IQ Lookup Table Core 1 */
#घोषणा B43_NTAB_C1_IQLT_SIZE		128
#घोषणा B43_NTAB_C1_LOFEEDTH		B43_NTAB16(0x1B, 0x1C0) /* Local Oscillator Feed Through Lookup Table Core 1 */
#घोषणा B43_NTAB_C1_LOFEEDTH_SIZE	128

/* Volatile N-PHY tables, PHY revision >= 3 */
#घोषणा B43_NTAB_ANT_SW_CTL_R3		B43_NTAB16( 9,   0) /* antenna software control */

/* Static N-PHY tables, PHY revision >= 3 */
#घोषणा B43_NTAB_FRAMESTRUCT_R3		B43_NTAB32(10,   0) /* frame काष्ठा  */
#घोषणा B43_NTAB_PILOT_R3		B43_NTAB16(11,   0) /* pilot  */
#घोषणा B43_NTAB_TMAP_R3		B43_NTAB32(12,   0) /* TM AP  */
#घोषणा B43_NTAB_INTLEVEL_R3		B43_NTAB32(13,   0) /* INT LV  */
#घोषणा B43_NTAB_TDTRN_R3		B43_NTAB32(14,   0) /* TD TRN  */
#घोषणा B43_NTAB_NOISEVAR_R3		B43_NTAB32(16,   0) /* noise variance */
#घोषणा B43_NTAB_MCS_R3			B43_NTAB16(18,   0) /* MCS  */
#घोषणा B43_NTAB_TDI20A0_R3		B43_NTAB32(19, 128) /* TDI 20/0  */
#घोषणा B43_NTAB_TDI20A1_R3		B43_NTAB32(19, 256) /* TDI 20/1  */
#घोषणा B43_NTAB_TDI40A0_R3		B43_NTAB32(19, 640) /* TDI 40/0  */
#घोषणा B43_NTAB_TDI40A1_R3		B43_NTAB32(19, 768) /* TDI 40/1  */
#घोषणा B43_NTAB_PILOTLT_R3		B43_NTAB32(20,   0) /* PLT lookup  */
#घोषणा B43_NTAB_CHANEST_R3		B43_NTAB32(22,   0) /* channel estimate  */
#घोषणा B43_NTAB_FRAMELT_R3		 B43_NTAB8(24,   0) /* frame lookup  */
#घोषणा B43_NTAB_C0_ESTPLT_R3		 B43_NTAB8(26,   0) /* estimated घातer lookup 0  */
#घोषणा B43_NTAB_C0_ADJPLT_R3		 B43_NTAB8(26,  64) /* adjusted घातer lookup 0  */
#घोषणा B43_NTAB_C0_GAINCTL_R3		B43_NTAB32(26, 192) /* gain control lookup 0  */
#घोषणा B43_NTAB_C0_IQLT_R3		B43_NTAB32(26, 320) /* I/Q lookup 0  */
#घोषणा B43_NTAB_C0_LOFEEDTH_R3		B43_NTAB16(26, 448) /* Local Oscillator Feed Through lookup 0  */
#घोषणा B43_NTAB_C0_PAPD_COMP_R3	B43_NTAB16(26, 576)
#घोषणा B43_NTAB_C1_ESTPLT_R3		 B43_NTAB8(27,   0) /* estimated घातer lookup 1  */
#घोषणा B43_NTAB_C1_ADJPLT_R3		 B43_NTAB8(27,  64) /* adjusted घातer lookup 1  */
#घोषणा B43_NTAB_C1_GAINCTL_R3		B43_NTAB32(27, 192) /* gain control lookup 1  */
#घोषणा B43_NTAB_C1_IQLT_R3		B43_NTAB32(27, 320) /* I/Q lookup 1  */
#घोषणा B43_NTAB_C1_LOFEEDTH_R3		B43_NTAB16(27, 448) /* Local Oscillator Feed Through lookup 1 */
#घोषणा B43_NTAB_C1_PAPD_COMP_R3	B43_NTAB16(27, 576)

/* Static N-PHY tables, PHY revision >= 7 */
#घोषणा B43_NTAB_TMAP_R7		B43_NTAB32(12,   0) /* TM AP */
#घोषणा B43_NTAB_NOISEVAR_R7		B43_NTAB32(16,   0) /* noise variance */

#घोषणा B43_NTAB_TX_IQLO_CAL_LOFT_LADDER_40_SIZE	18
#घोषणा B43_NTAB_TX_IQLO_CAL_LOFT_LADDER_20_SIZE	18
#घोषणा B43_NTAB_TX_IQLO_CAL_IQIMB_LADDER_40_SIZE	18
#घोषणा B43_NTAB_TX_IQLO_CAL_IQIMB_LADDER_20_SIZE	18
#घोषणा B43_NTAB_TX_IQLO_CAL_STARTCOEFS_REV3		11
#घोषणा B43_NTAB_TX_IQLO_CAL_STARTCOEFS			9
#घोषणा B43_NTAB_TX_IQLO_CAL_CMDS_RECAL_REV3		12
#घोषणा B43_NTAB_TX_IQLO_CAL_CMDS_RECAL			10
#घोषणा B43_NTAB_TX_IQLO_CAL_CMDS_FULLCAL		10
#घोषणा B43_NTAB_TX_IQLO_CAL_CMDS_FULLCAL_REV3		12

u32 b43_ntab_पढ़ो(काष्ठा b43_wldev *dev, u32 offset);
व्योम b43_ntab_पढ़ो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			 अचिन्हित पूर्णांक nr_elements, व्योम *_data);
व्योम b43_ntab_ग_लिखो(काष्ठा b43_wldev *dev, u32 offset, u32 value);
व्योम b43_ntab_ग_लिखो_bulk(काष्ठा b43_wldev *dev, u32 offset,
			  अचिन्हित पूर्णांक nr_elements, स्थिर व्योम *_data);

व्योम b43_nphy_tables_init(काष्ठा b43_wldev *dev);

स्थिर u32 *b43_nphy_get_tx_gain_table(काष्ठा b43_wldev *dev);

स्थिर s16 *b43_ntab_get_rf_pwr_offset_table(काष्ठा b43_wldev *dev);

बाह्य स्थिर s8 b43_ntab_papd_pga_gain_delta_ipa_2g[];

बाह्य स्थिर u16 tbl_iqcal_gainparams[2][9][8];
बाह्य स्थिर काष्ठा nphy_txiqcal_ladder ladder_lo[];
बाह्य स्थिर काष्ठा nphy_txiqcal_ladder ladder_iq[];
बाह्य स्थिर u16 loscale[];

बाह्य स्थिर u16 tbl_tx_iqlo_cal_loft_ladder_40[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_loft_ladder_20[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_iqimb_ladder_40[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_iqimb_ladder_20[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_startcoefs_nphyrev3[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_startcoefs[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_cmds_recal_nphyrev3[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_cmds_recal[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_cmds_fullcal[];
बाह्य स्थिर u16 tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3[];
बाह्य स्थिर s16 tbl_tx_filter_coef_rev4[7][15];

बाह्य स्थिर काष्ठा nphy_rf_control_override_rev2
	tbl_rf_control_override_rev2[];
बाह्य स्थिर काष्ठा nphy_rf_control_override_rev3
	tbl_rf_control_override_rev3[];
स्थिर काष्ठा nphy_rf_control_override_rev7 *b43_nphy_get_rf_ctl_over_rev7(
	काष्ठा b43_wldev *dev, u16 field, u8 override);

#पूर्ण_अगर /* B43_TABLES_NPHY_H_ */
