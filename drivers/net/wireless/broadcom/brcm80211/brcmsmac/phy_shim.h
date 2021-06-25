<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * phy_shim.h: stuff defined in phy_shim.c and included only by the phy
 */

#अगर_अघोषित _BRCM_PHY_SHIM_H_
#घोषणा _BRCM_PHY_SHIM_H_

#समावेश "types.h"

#घोषणा RADAR_TYPE_NONE		0	/* Radar type None */
#घोषणा RADAR_TYPE_ETSI_1	1	/* ETSI 1 Radar type */
#घोषणा RADAR_TYPE_ETSI_2	2	/* ETSI 2 Radar type */
#घोषणा RADAR_TYPE_ETSI_3	3	/* ETSI 3 Radar type */
#घोषणा RADAR_TYPE_ITU_E	4	/* ITU E Radar type */
#घोषणा RADAR_TYPE_ITU_K	5	/* ITU K Radar type */
#घोषणा RADAR_TYPE_UNCLASSIFIED	6	/* Unclassअगरied Radar type  */
#घोषणा RADAR_TYPE_BIN5		7	/* दीर्घ pulse radar type */
#घोषणा RADAR_TYPE_STG2		8	/* staggered-2 radar */
#घोषणा RADAR_TYPE_STG3		9	/* staggered-3 radar */
#घोषणा RADAR_TYPE_FRA		10	/* French radar */

/* French radar pulse widths */
#घोषणा FRA_T1_20MHZ	52770
#घोषणा FRA_T2_20MHZ	61538
#घोषणा FRA_T3_20MHZ	66002
#घोषणा FRA_T1_40MHZ	105541
#घोषणा FRA_T2_40MHZ	123077
#घोषणा FRA_T3_40MHZ	132004
#घोषणा FRA_ERR_20MHZ	60
#घोषणा FRA_ERR_40MHZ	120

#घोषणा ANTSEL_NA		0 /* No boardlevel selection available */
#घोषणा ANTSEL_2x4		1 /* 2x4 boardlevel selection available */
#घोषणा ANTSEL_2x3		2 /* 2x3 CB2 boardlevel selection available */

/* Rx Antenna भागersity control values */
#घोषणा	ANT_RX_DIV_FORCE_0	0	/* Use antenna 0 */
#घोषणा	ANT_RX_DIV_FORCE_1	1	/* Use antenna 1 */
#घोषणा	ANT_RX_DIV_START_1	2	/* Choose starting with 1 */
#घोषणा	ANT_RX_DIV_START_0	3	/* Choose starting with 0 */
#घोषणा	ANT_RX_DIV_ENABLE	3	/* APHY bbConfig Enable RX Diversity */
#घोषणा ANT_RX_DIV_DEF		ANT_RX_DIV_START_0 /* शेष antभाग setting */

#घोषणा WL_ANT_RX_MAX		2	/* max 2 receive antennas */
#घोषणा WL_ANT_HT_RX_MAX	3	/* max 3 receive antennas/cores */
#घोषणा WL_ANT_IDX_1		0	/* antenna index 1 */
#घोषणा WL_ANT_IDX_2		1	/* antenna index 2 */

/* values क्रम n_preamble_type */
#घोषणा BRCMS_N_PREAMBLE_MIXEDMODE	0
#घोषणा BRCMS_N_PREAMBLE_GF		1
#घोषणा BRCMS_N_PREAMBLE_GF_BRCM          2

#घोषणा WL_TX_POWER_RATES_LEGACY	45
#घोषणा WL_TX_POWER_MCS20_FIRST	        12
#घोषणा WL_TX_POWER_MCS20_NUM	        16
#घोषणा WL_TX_POWER_MCS40_FIRST	        28
#घोषणा WL_TX_POWER_MCS40_NUM	        17


#घोषणा WL_TX_POWER_RATES	       101
#घोषणा WL_TX_POWER_CCK_FIRST	       0
#घोषणा WL_TX_POWER_CCK_NUM	       4
/* Index क्रम first 20MHz OFDM SISO rate */
#घोषणा WL_TX_POWER_OFDM_FIRST	       4
/* Index क्रम first 20MHz OFDM CDD rate */
#घोषणा WL_TX_POWER_OFDM20_CDD_FIRST   12
/* Index क्रम first 40MHz OFDM SISO rate */
#घोषणा WL_TX_POWER_OFDM40_SISO_FIRST  52
/* Index क्रम first 40MHz OFDM CDD rate */
#घोषणा WL_TX_POWER_OFDM40_CDD_FIRST   60
#घोषणा WL_TX_POWER_OFDM_NUM	       8
/* Index क्रम first 20MHz MCS SISO rate */
#घोषणा WL_TX_POWER_MCS20_SISO_FIRST   20
/* Index क्रम first 20MHz MCS CDD rate */
#घोषणा WL_TX_POWER_MCS20_CDD_FIRST    28
/* Index क्रम first 20MHz MCS STBC rate */
#घोषणा WL_TX_POWER_MCS20_STBC_FIRST   36
/* Index क्रम first 20MHz MCS SDM rate */
#घोषणा WL_TX_POWER_MCS20_SDM_FIRST    44
/* Index क्रम first 40MHz MCS SISO rate */
#घोषणा WL_TX_POWER_MCS40_SISO_FIRST   68
/* Index क्रम first 40MHz MCS CDD rate */
#घोषणा WL_TX_POWER_MCS40_CDD_FIRST    76
/* Index क्रम first 40MHz MCS STBC rate */
#घोषणा WL_TX_POWER_MCS40_STBC_FIRST   84
/* Index क्रम first 40MHz MCS SDM rate */
#घोषणा WL_TX_POWER_MCS40_SDM_FIRST    92
#घोषणा WL_TX_POWER_MCS_1_STREAM_NUM   8
#घोषणा WL_TX_POWER_MCS_2_STREAM_NUM   8
/* Index क्रम 40MHz rate MCS 32 */
#घोषणा WL_TX_POWER_MCS_32	       100
#घोषणा WL_TX_POWER_MCS_32_NUM	       1

/* sslpnphy specअगरics */
/* Index क्रम first 20MHz MCS SISO rate */
#घोषणा WL_TX_POWER_MCS20_SISO_FIRST_SSN   12

/* काष्ठा tx_घातer::flags bits */
#घोषणा WL_TX_POWER_F_ENABLED	1
#घोषणा WL_TX_POWER_F_HW	2
#घोषणा WL_TX_POWER_F_MIMO	4
#घोषणा WL_TX_POWER_F_SISO	8

/* values to क्रमce tx/rx chain */
#घोषणा BRCMS_N_TXRX_CHAIN0		0
#घोषणा BRCMS_N_TXRX_CHAIN1		1

काष्ठा brcms_phy;

काष्ठा phy_shim_info *wlc_phy_shim_attach(काष्ठा brcms_hardware *wlc_hw,
					  काष्ठा brcms_info *wl,
					  काष्ठा brcms_c_info *wlc);
व्योम wlc_phy_shim_detach(काष्ठा phy_shim_info *physhim);

/* PHY to WL utility functions */
काष्ठा wlapi_समयr *wlapi_init_समयr(काष्ठा phy_shim_info *physhim,
				     व्योम (*fn)(काष्ठा brcms_phy *pi),
				     व्योम *arg, स्थिर अक्षर *name);
व्योम wlapi_मुक्त_समयr(काष्ठा wlapi_समयr *t);
व्योम wlapi_add_समयr(काष्ठा wlapi_समयr *t, uपूर्णांक ms, पूर्णांक periodic);
bool wlapi_del_समयr(काष्ठा wlapi_समयr *t);
व्योम wlapi_पूर्णांकrson(काष्ठा phy_shim_info *physhim);
u32 wlapi_पूर्णांकrsoff(काष्ठा phy_shim_info *physhim);
व्योम wlapi_पूर्णांकrsrestore(काष्ठा phy_shim_info *physhim, u32 macपूर्णांकmask);

व्योम wlapi_bmac_ग_लिखो_shm(काष्ठा phy_shim_info *physhim, uपूर्णांक offset, u16 v);
u16 wlapi_bmac_पढ़ो_shm(काष्ठा phy_shim_info *physhim, uपूर्णांक offset);
व्योम wlapi_bmac_mhf(काष्ठा phy_shim_info *physhim, u8 idx, u16 mask, u16 val,
		    पूर्णांक bands);
व्योम wlapi_bmac_corereset(काष्ठा phy_shim_info *physhim, u32 flags);
व्योम wlapi_suspend_mac_and_रुको(काष्ठा phy_shim_info *physhim);
व्योम wlapi_चयन_macfreq(काष्ठा phy_shim_info *physhim, u8 spurmode);
व्योम wlapi_enable_mac(काष्ठा phy_shim_info *physhim);
व्योम wlapi_bmac_mctrl(काष्ठा phy_shim_info *physhim, u32 mask, u32 val);
व्योम wlapi_bmac_phy_reset(काष्ठा phy_shim_info *physhim);
व्योम wlapi_bmac_bw_set(काष्ठा phy_shim_info *physhim, u16 bw);
व्योम wlapi_bmac_phyclk_fgc(काष्ठा phy_shim_info *physhim, bool clk);
व्योम wlapi_bmac_macphyclk_set(काष्ठा phy_shim_info *physhim, bool clk);
व्योम wlapi_bmac_core_phypll_ctl(काष्ठा phy_shim_info *physhim, bool on);
व्योम wlapi_bmac_core_phypll_reset(काष्ठा phy_shim_info *physhim);
व्योम wlapi_bmac_ucode_wake_override_phyreg_set(काष्ठा phy_shim_info *physhim);
व्योम wlapi_bmac_ucode_wake_override_phyreg_clear(काष्ठा phy_shim_info *physhim);
व्योम wlapi_bmac_ग_लिखो_ढाँचा_ram(काष्ठा phy_shim_info *physhim, पूर्णांक o,
				   पूर्णांक len, व्योम *buf);
u16 wlapi_bmac_rate_shm_offset(काष्ठा phy_shim_info *physhim, u8 rate);
व्योम wlapi_ucode_sample_init(काष्ठा phy_shim_info *physhim);
व्योम wlapi_copyfrom_objmem(काष्ठा phy_shim_info *physhim, uपूर्णांक, व्योम *buf,
			   पूर्णांक, u32 sel);
व्योम wlapi_copyto_objmem(काष्ठा phy_shim_info *physhim, uपूर्णांक, स्थिर व्योम *buf,
			 पूर्णांक, u32);

व्योम wlapi_high_update_phy_mode(काष्ठा phy_shim_info *physhim, u32 phy_mode);
u16 wlapi_bmac_get_txant(काष्ठा phy_shim_info *physhim);

#पूर्ण_अगर				/* _BRCM_PHY_SHIM_H_ */
