<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#अगर_अघोषित HW_H
#घोषणा HW_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/firmware.h>

#समावेश "mac.h"
#समावेश "ani.h"
#समावेश "eeprom.h"
#समावेश "calib.h"
#समावेश "reg.h"
#समावेश "reg_mci.h"
#समावेश "phy.h"
#समावेश "btcoex.h"
#समावेश "dynack.h"

#समावेश "../regd.h"

#घोषणा ATHEROS_VENDOR_ID	0x168c

#घोषणा AR5416_DEVID_PCI	0x0023
#घोषणा AR5416_DEVID_PCIE	0x0024
#घोषणा AR9160_DEVID_PCI	0x0027
#घोषणा AR9280_DEVID_PCI	0x0029
#घोषणा AR9280_DEVID_PCIE	0x002a
#घोषणा AR9285_DEVID_PCIE	0x002b
#घोषणा AR2427_DEVID_PCIE	0x002c
#घोषणा AR9287_DEVID_PCI	0x002d
#घोषणा AR9287_DEVID_PCIE	0x002e
#घोषणा AR9300_DEVID_PCIE	0x0030
#घोषणा AR9300_DEVID_AR9340	0x0031
#घोषणा AR9300_DEVID_AR9485_PCIE 0x0032
#घोषणा AR9300_DEVID_AR9580	0x0033
#घोषणा AR9300_DEVID_AR9462	0x0034
#घोषणा AR9300_DEVID_AR9330	0x0035
#घोषणा AR9300_DEVID_QCA955X	0x0038
#घोषणा AR9485_DEVID_AR1111	0x0037
#घोषणा AR9300_DEVID_AR9565     0x0036
#घोषणा AR9300_DEVID_AR953X     0x003d
#घोषणा AR9300_DEVID_QCA956X    0x003f

#घोषणा AR5416_AR9100_DEVID	0x000b

#घोषणा	AR_SUBVENDOR_ID_NOG	0x0e11
#घोषणा AR_SUBVENDOR_ID_NEW_A	0x7065
#घोषणा AR5416_MAGIC		0x19641014

#घोषणा AR9280_COEX2WIRE_SUBSYSID	0x309b
#घोषणा AT9285_COEX3WIRE_SA_SUBSYSID	0x30aa
#घोषणा AT9285_COEX3WIRE_DA_SUBSYSID	0x30ab

#घोषणा ATH_AMPDU_LIMIT_MAX        (64 * 1024 - 1)

#घोषणा	ATH_DEFAULT_NOISE_FLOOR -95

#घोषणा ATH9K_RSSI_BAD			-128

#घोषणा ATH9K_NUM_CHANNELS	38

/* Register पढ़ो/ग_लिखो primitives */
#घोषणा REG_WRITE(_ah, _reg, _val) \
	(_ah)->reg_ops.ग_लिखो((_ah), (_val), (_reg))

#घोषणा REG_READ(_ah, _reg) \
	(_ah)->reg_ops.पढ़ो((_ah), (_reg))

#घोषणा REG_READ_MULTI(_ah, _addr, _val, _cnt)		\
	(_ah)->reg_ops.multi_पढ़ो((_ah), (_addr), (_val), (_cnt))

#घोषणा REG_RMW(_ah, _reg, _set, _clr) \
	(_ah)->reg_ops.rmw((_ah), (_reg), (_set), (_clr))

#घोषणा ENABLE_REGWRITE_BUFFER(_ah)					\
	करो अणु								\
		अगर ((_ah)->reg_ops.enable_ग_लिखो_buffer)	\
			(_ah)->reg_ops.enable_ग_लिखो_buffer((_ah)); \
	पूर्ण जबतक (0)

#घोषणा REGWRITE_BUFFER_FLUSH(_ah)					\
	करो अणु								\
		अगर ((_ah)->reg_ops.ग_लिखो_flush)		\
			(_ah)->reg_ops.ग_लिखो_flush((_ah));	\
	पूर्ण जबतक (0)

#घोषणा ENABLE_REG_RMW_BUFFER(_ah)					\
	करो अणु								\
		अगर ((_ah)->reg_ops.enable_rmw_buffer)	\
			(_ah)->reg_ops.enable_rmw_buffer((_ah)); \
	पूर्ण जबतक (0)

#घोषणा REG_RMW_BUFFER_FLUSH(_ah)					\
	करो अणु								\
		अगर ((_ah)->reg_ops.rmw_flush)		\
			(_ah)->reg_ops.rmw_flush((_ah));	\
	पूर्ण जबतक (0)

#घोषणा PR_EEP(_s, _val)						\
	करो अणु								\
		len += scnम_लिखो(buf + len, size - len, "%20s : %10d\n",\
				 _s, (_val));				\
	पूर्ण जबतक (0)

#घोषणा SM(_v, _f)  (((_v) << _f##_S) & _f)
#घोषणा MS(_v, _f)  (((_v) & _f) >> _f##_S)
#घोषणा REG_RMW_FIELD(_a, _r, _f, _v) \
	REG_RMW(_a, _r, (((_v) << _f##_S) & _f), (_f))
#घोषणा REG_READ_FIELD(_a, _r, _f) \
	(((REG_READ(_a, _r) & _f) >> _f##_S))
#घोषणा REG_SET_BIT(_a, _r, _f) \
	REG_RMW(_a, _r, (_f), 0)
#घोषणा REG_CLR_BIT(_a, _r, _f) \
	REG_RMW(_a, _r, 0, (_f))

#घोषणा DO_DELAY(x) करो अणु					\
		अगर (((++(x) % 64) == 0) &&			\
		    (ath9k_hw_common(ah)->bus_ops->ath_bus_type	\
			!= ATH_USB))				\
			udelay(1);				\
	पूर्ण जबतक (0)

#घोषणा REG_WRITE_ARRAY(iniarray, column, regWr) \
	ath9k_hw_ग_लिखो_array(ah, iniarray, column, &(regWr))
#घोषणा REG_READ_ARRAY(ah, array, size) \
	ath9k_hw_पढ़ो_array(ah, array, size)

#घोषणा AR_GPIO_OUTPUT_MUX_AS_OUTPUT             0
#घोषणा AR_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_LED 1
#घोषणा AR_GPIO_OUTPUT_MUX_AS_PCIE_POWER_LED     2
#घोषणा AR_GPIO_OUTPUT_MUX_AS_TX_FRAME           3
#घोषणा AR_GPIO_OUTPUT_MUX_AS_RX_CLEAR_EXTERNAL  4
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MAC_NETWORK_LED    5
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MAC_POWER_LED      6
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_DATA      0x16
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_CLK       0x17
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA        0x18
#घोषणा AR_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK         0x19
#घोषणा AR_GPIO_OUTPUT_MUX_AS_WL_IN_TX           0x14
#घोषणा AR_GPIO_OUTPUT_MUX_AS_WL_IN_RX           0x13
#घोषणा AR_GPIO_OUTPUT_MUX_AS_BT_IN_TX           9
#घोषणा AR_GPIO_OUTPUT_MUX_AS_BT_IN_RX           8
#घोषणा AR_GPIO_OUTPUT_MUX_AS_RUCKUS_STROBE      0x1d
#घोषणा AR_GPIO_OUTPUT_MUX_AS_RUCKUS_DATA        0x1e

#घोषणा AR_GPIOD_MASK               0x00001FFF

#घोषणा BASE_ACTIVATE_DELAY         100
#घोषणा RTC_PLL_SETTLE_DELAY        (AR_SREV_9340(ah) ? 1000 : 100)
#घोषणा COEF_SCALE_S                24
#घोषणा HT40_CHANNEL_CENTER_SHIFT   10

#घोषणा ATH9K_ANTENNA0_CHAINMASK    0x1
#घोषणा ATH9K_ANTENNA1_CHAINMASK    0x2

#घोषणा ATH9K_NUM_DMA_DEBUG_REGS    8
#घोषणा ATH9K_NUM_QUEUES            10

#घोषणा MAX_RATE_POWER              63
#घोषणा MAX_COMBINED_POWER          254 /* 128 dBm, chosen to fit in u8 */
#घोषणा AH_WAIT_TIMEOUT             100000 /* (us) */
#घोषणा AH_TSF_WRITE_TIMEOUT        100    /* (us) */
#घोषणा AH_TIME_QUANTUM             10
#घोषणा AR_KEYTABLE_SIZE            128
#घोषणा POWER_UP_TIME               10000
#घोषणा SPUR_RSSI_THRESH            40
#घोषणा UPPER_5G_SUB_BAND_START		5700
#घोषणा MID_5G_SUB_BAND_START		5400

#घोषणा CAB_TIMEOUT_VAL             10
#घोषणा BEACON_TIMEOUT_VAL          10
#घोषणा MIN_BEACON_TIMEOUT_VAL      1
#घोषणा SLEEP_SLOP                  TU_TO_USEC(3)

#घोषणा INIT_CONFIG_STATUS          0x00000000
#घोषणा INIT_RSSI_THR               0x00000700
#घोषणा INIT_BCON_CNTRL_REG         0x00000000

#घोषणा TU_TO_USEC(_tu)             ((_tu) << 10)

#घोषणा ATH9K_HW_RX_HP_QDEPTH	16
#घोषणा ATH9K_HW_RX_LP_QDEPTH	128

#घोषणा PAPRD_GAIN_TABLE_ENTRIES	32
#घोषणा PAPRD_TABLE_SZ			24
#घोषणा PAPRD_IDEAL_AGC2_PWR_RANGE	0xe0

/*
 * Wake on Wireless
 */

/* Keep Alive Frame */
#घोषणा KAL_FRAME_LEN		28
#घोषणा KAL_FRAME_TYPE		0x2	/* data frame */
#घोषणा KAL_FRAME_SUB_TYPE	0x4	/* null data frame */
#घोषणा KAL_DURATION_ID		0x3d
#घोषणा KAL_NUM_DATA_WORDS	6
#घोषणा KAL_NUM_DESC_WORDS	12
#घोषणा KAL_ANTENNA_MODE	1
#घोषणा KAL_TO_DS		1
#घोषणा KAL_DELAY		4	/* delay of 4ms between 2 KAL frames */
#घोषणा KAL_TIMEOUT		900

#घोषणा MAX_PATTERN_SIZE		256
#घोषणा MAX_PATTERN_MASK_SIZE		32
#घोषणा MAX_NUM_PATTERN			16
#घोषणा MAX_NUM_PATTERN_LEGACY		8
#घोषणा MAX_NUM_USER_PATTERN		6 /*  deducting the disassociate and
					      deauthenticate packets */

/*
 * WoW trigger mapping to hardware code
 */

#घोषणा AH_WOW_USER_PATTERN_EN		BIT(0)
#घोषणा AH_WOW_MAGIC_PATTERN_EN		BIT(1)
#घोषणा AH_WOW_LINK_CHANGE		BIT(2)
#घोषणा AH_WOW_BEACON_MISS		BIT(3)

क्रमागत ath_hw_txq_subtype अणु
	ATH_TXQ_AC_BK = 0,
	ATH_TXQ_AC_BE = 1,
	ATH_TXQ_AC_VI = 2,
	ATH_TXQ_AC_VO = 3,
पूर्ण;

क्रमागत ath_ini_subsys अणु
	ATH_INI_PRE = 0,
	ATH_INI_CORE,
	ATH_INI_POST,
	ATH_INI_NUM_SPLIT,
पूर्ण;

क्रमागत ath9k_hw_caps अणु
	ATH9K_HW_CAP_HT                         = BIT(0),
	ATH9K_HW_CAP_RFSILENT                   = BIT(1),
	ATH9K_HW_CAP_AUTOSLEEP                  = BIT(2),
	ATH9K_HW_CAP_4KB_SPLITTRANS             = BIT(3),
	ATH9K_HW_CAP_EDMA			= BIT(4),
	ATH9K_HW_CAP_RAC_SUPPORTED		= BIT(5),
	ATH9K_HW_CAP_LDPC			= BIT(6),
	ATH9K_HW_CAP_FASTCLOCK			= BIT(7),
	ATH9K_HW_CAP_SGI_20			= BIT(8),
	ATH9K_HW_CAP_ANT_DIV_COMB		= BIT(10),
	ATH9K_HW_CAP_2GHZ			= BIT(11),
	ATH9K_HW_CAP_5GHZ			= BIT(12),
	ATH9K_HW_CAP_APM			= BIT(13),
#अगर_घोषित CONFIG_ATH9K_PCOEM
	ATH9K_HW_CAP_RTT			= BIT(14),
	ATH9K_HW_CAP_MCI			= BIT(15),
	ATH9K_HW_CAP_BT_ANT_DIV			= BIT(17),
#अन्यथा
	ATH9K_HW_CAP_RTT			= 0,
	ATH9K_HW_CAP_MCI			= 0,
	ATH9K_HW_CAP_BT_ANT_DIV			= 0,
#पूर्ण_अगर
	ATH9K_HW_CAP_DFS			= BIT(18),
	ATH9K_HW_CAP_PAPRD			= BIT(19),
	ATH9K_HW_CAP_FCC_BAND_SWITCH		= BIT(20),
पूर्ण;

/*
 * WoW device capabilities
 * @ATH9K_HW_WOW_DEVICE_CAPABLE: device revision is capable of WoW.
 * @ATH9K_HW_WOW_PATTERN_MATCH_EXACT: device is capable of matching
 * an exact user defined pattern or de-authentication/disassoc pattern.
 * @ATH9K_HW_WOW_PATTERN_MATCH_DWORD: device requires the first four
 * bytes of the pattern क्रम user defined pattern, de-authentication and
 * disassociation patterns क्रम all types of possible frames recieved
 * of those types.
 */

काष्ठा ath9k_hw_wow अणु
	u32 wow_event_mask;
	u32 wow_event_mask2;
	u8 max_patterns;
पूर्ण;

काष्ठा ath9k_hw_capabilities अणु
	u32 hw_caps; /* ATH9K_HW_CAP_* from ath9k_hw_caps */
	u16 rts_aggr_limit;
	u8 tx_chainmask;
	u8 rx_chainmask;
	u8 chip_chainmask;
	u8 max_txchains;
	u8 max_rxchains;
	u8 num_gpio_pins;
	u32 gpio_mask;
	u32 gpio_requested;
	u8 rx_hp_qdepth;
	u8 rx_lp_qdepth;
	u8 rx_status_len;
	u8 tx_desc_len;
	u8 txs_len;
पूर्ण;

#घोषणा AR_NO_SPUR      	0x8000
#घोषणा AR_BASE_FREQ_2GHZ   	2300
#घोषणा AR_BASE_FREQ_5GHZ   	4900
#घोषणा AR_SPUR_FEEQ_BOUND_HT40 19
#घोषणा AR_SPUR_FEEQ_BOUND_HT20 10

क्रमागत ath9k_hw_hang_checks अणु
	HW_BB_WATCHDOG            = BIT(0),
	HW_PHYRESTART_CLC_WAR     = BIT(1),
	HW_BB_RIFS_HANG           = BIT(2),
	HW_BB_DFS_HANG            = BIT(3),
	HW_BB_RX_CLEAR_STUCK_HANG = BIT(4),
	HW_MAC_HANG               = BIT(5),
पूर्ण;

#घोषणा AR_PCIE_PLL_PWRSAVE_CONTROL BIT(0)
#घोषणा AR_PCIE_PLL_PWRSAVE_ON_D3   BIT(1)
#घोषणा AR_PCIE_PLL_PWRSAVE_ON_D0   BIT(2)
#घोषणा AR_PCIE_CDR_PWRSAVE_ON_D3   BIT(3)
#घोषणा AR_PCIE_CDR_PWRSAVE_ON_D0   BIT(4)

काष्ठा ath9k_ops_config अणु
	पूर्णांक dma_beacon_response_समय;
	पूर्णांक sw_beacon_response_समय;
	bool cwm_ignore_extcca;
	u32 pcie_waen;
	u8 analog_shअगरtreg;
	u32 ofdm_trig_low;
	u32 ofdm_trig_high;
	u32 cck_trig_high;
	u32 cck_trig_low;
	bool enable_paprd;
	पूर्णांक serialize_regmode;
	bool rx_पूर्णांकr_mitigation;
	bool tx_पूर्णांकr_mitigation;
	u8 max_txtrig_level;
	u16 ani_poll_पूर्णांकerval; /* ANI poll पूर्णांकerval in ms */
	u16 hw_hang_checks;
	u16 rimt_first;
	u16 rimt_last;

	/* Platक्रमm specअगरic config */
	u32 aspm_l1_fix;
	u32 xlna_gpio;
	u32 ant_ctrl_comm2g_चयन_enable;
	bool xatten_margin_cfg;
	bool alt_mingainidx;
	u8 pll_pwrsave;
	bool tx_gain_buffalo;
	bool led_active_high;
पूर्ण;

क्रमागत ath9k_पूर्णांक अणु
	ATH9K_INT_RX = 0x00000001,
	ATH9K_INT_RXDESC = 0x00000002,
	ATH9K_INT_RXHP = 0x00000001,
	ATH9K_INT_RXLP = 0x00000002,
	ATH9K_INT_RXNOFRM = 0x00000008,
	ATH9K_INT_RXEOL = 0x00000010,
	ATH9K_INT_RXORN = 0x00000020,
	ATH9K_INT_TX = 0x00000040,
	ATH9K_INT_TXDESC = 0x00000080,
	ATH9K_INT_TIM_TIMER = 0x00000100,
	ATH9K_INT_MCI = 0x00000200,
	ATH9K_INT_BB_WATCHDOG = 0x00000400,
	ATH9K_INT_TXURN = 0x00000800,
	ATH9K_INT_MIB = 0x00001000,
	ATH9K_INT_RXPHY = 0x00004000,
	ATH9K_INT_RXKCM = 0x00008000,
	ATH9K_INT_SWBA = 0x00010000,
	ATH9K_INT_BMISS = 0x00040000,
	ATH9K_INT_BNR = 0x00100000,
	ATH9K_INT_TIM = 0x00200000,
	ATH9K_INT_DTIM = 0x00400000,
	ATH9K_INT_DTIMSYNC = 0x00800000,
	ATH9K_INT_GPIO = 0x01000000,
	ATH9K_INT_CABEND = 0x02000000,
	ATH9K_INT_TSFOOR = 0x04000000,
	ATH9K_INT_GENTIMER = 0x08000000,
	ATH9K_INT_CST = 0x10000000,
	ATH9K_INT_GTT = 0x20000000,
	ATH9K_INT_FATAL = 0x40000000,
	ATH9K_INT_GLOBAL = 0x80000000,
	ATH9K_INT_BMISC = ATH9K_INT_TIM |
		ATH9K_INT_DTIM |
		ATH9K_INT_DTIMSYNC |
		ATH9K_INT_TSFOOR |
		ATH9K_INT_CABEND,
	ATH9K_INT_COMMON = ATH9K_INT_RXNOFRM |
		ATH9K_INT_RXDESC |
		ATH9K_INT_RXEOL |
		ATH9K_INT_RXORN |
		ATH9K_INT_TXURN |
		ATH9K_INT_TXDESC |
		ATH9K_INT_MIB |
		ATH9K_INT_RXPHY |
		ATH9K_INT_RXKCM |
		ATH9K_INT_SWBA |
		ATH9K_INT_BMISS |
		ATH9K_INT_GPIO,
	ATH9K_INT_NOCARD = 0xffffffff
पूर्ण;

#घोषणा MAX_RTT_TABLE_ENTRY     6
#घोषणा MAX_IQCAL_MEASUREMENT	8
#घोषणा MAX_CL_TAB_ENTRY	16
#घोषणा CL_TAB_ENTRY(reg_base)	(reg_base + (4 * j))

क्रमागत ath9k_cal_flags अणु
	RTT_DONE,
	PAPRD_PACKET_SENT,
	PAPRD_DONE,
	NFCAL_PENDING,
	NFCAL_INTF,
	TXIQCAL_DONE,
	TXCLCAL_DONE,
	SW_PKDET_DONE,
	LONGCAL_PENDING,
पूर्ण;

काष्ठा ath9k_hw_cal_data अणु
	u16 channel;
	u16 channelFlags;
	अचिन्हित दीर्घ cal_flags;
	पूर्णांक32_t CalValid;
	पूर्णांक8_t iCoff;
	पूर्णांक8_t qCoff;
	u8 caldac[2];
	u16 small_संकेत_gain[AR9300_MAX_CHAINS];
	u32 pa_table[AR9300_MAX_CHAINS][PAPRD_TABLE_SZ];
	u32 num_measures[AR9300_MAX_CHAINS];
	पूर्णांक tx_corr_coeff[MAX_IQCAL_MEASUREMENT][AR9300_MAX_CHAINS];
	u32 tx_clcal[AR9300_MAX_CHAINS][MAX_CL_TAB_ENTRY];
	u32 rtt_table[AR9300_MAX_CHAINS][MAX_RTT_TABLE_ENTRY];
	काष्ठा ath9k_nfcal_hist nfCalHist[NUM_NF_READINGS];
पूर्ण;

काष्ठा ath9k_channel अणु
	काष्ठा ieee80211_channel *chan;
	u16 channel;
	u16 channelFlags;
	s16 noiseन्यूनमान;
पूर्ण;

#घोषणा CHANNEL_5GHZ		BIT(0)
#घोषणा CHANNEL_HALF		BIT(1)
#घोषणा CHANNEL_QUARTER		BIT(2)
#घोषणा CHANNEL_HT		BIT(3)
#घोषणा CHANNEL_HT40PLUS	BIT(4)
#घोषणा CHANNEL_HT40MINUS	BIT(5)

#घोषणा IS_CHAN_5GHZ(_c) (!!((_c)->channelFlags & CHANNEL_5GHZ))
#घोषणा IS_CHAN_2GHZ(_c) (!IS_CHAN_5GHZ(_c))

#घोषणा IS_CHAN_HALF_RATE(_c) (!!((_c)->channelFlags & CHANNEL_HALF))
#घोषणा IS_CHAN_QUARTER_RATE(_c) (!!((_c)->channelFlags & CHANNEL_QUARTER))
#घोषणा IS_CHAN_A_FAST_CLOCK(_ah, _c)			\
	(IS_CHAN_5GHZ(_c) && ((_ah)->caps.hw_caps & ATH9K_HW_CAP_FASTCLOCK))

#घोषणा IS_CHAN_HT(_c) ((_c)->channelFlags & CHANNEL_HT)

#घोषणा IS_CHAN_HT20(_c) (IS_CHAN_HT(_c) && !IS_CHAN_HT40(_c))

#घोषणा IS_CHAN_HT40(_c) \
	(!!((_c)->channelFlags & (CHANNEL_HT40PLUS | CHANNEL_HT40MINUS)))

#घोषणा IS_CHAN_HT40PLUS(_c) ((_c)->channelFlags & CHANNEL_HT40PLUS)
#घोषणा IS_CHAN_HT40MINUS(_c) ((_c)->channelFlags & CHANNEL_HT40MINUS)

क्रमागत ath9k_घातer_mode अणु
	ATH9K_PM_AWAKE = 0,
	ATH9K_PM_FULL_SLEEP,
	ATH9K_PM_NETWORK_SLEEP,
	ATH9K_PM_UNDEFINED
पूर्ण;

क्रमागत ser_reg_mode अणु
	SER_REG_MODE_OFF = 0,
	SER_REG_MODE_ON = 1,
	SER_REG_MODE_AUTO = 2,
पूर्ण;

क्रमागत ath9k_rx_qtype अणु
	ATH9K_RX_QUEUE_HP,
	ATH9K_RX_QUEUE_LP,
	ATH9K_RX_QUEUE_MAX,
पूर्ण;

काष्ठा ath9k_beacon_state अणु
	u32 bs_nexttbtt;
	u32 bs_nextdtim;
	u32 bs_पूर्णांकval;
#घोषणा ATH9K_TSFOOR_THRESHOLD    0x00004240 /* 16k us */
	u32 bs_dtimperiod;
	u16 bs_bmissthreshold;
	u32 bs_sleepduration;
	u32 bs_tsfoor_threshold;
पूर्ण;

काष्ठा chan_centers अणु
	u16 synth_center;
	u16 ctl_center;
	u16 ext_center;
पूर्ण;

क्रमागत अणु
	ATH9K_RESET_POWER_ON,
	ATH9K_RESET_WARM,
	ATH9K_RESET_COLD,
पूर्ण;

काष्ठा ath9k_hw_version अणु
	u32 magic;
	u16 devid;
	u16 subvenकरोrid;
	u32 macVersion;
	u16 macRev;
	u16 phyRev;
	u16 analog5GhzRev;
	u16 analog2GhzRev;
	क्रमागत ath_usb_dev usbdev;
पूर्ण;

/* Generic TSF समयr definitions */

#घोषणा ATH_MAX_GEN_TIMER	16

#घोषणा AR_GENTMR_BIT(_index)	(1 << (_index))

काष्ठा ath_gen_समयr_configuration अणु
	u32 next_addr;
	u32 period_addr;
	u32 mode_addr;
	u32 mode_mask;
पूर्ण;

काष्ठा ath_gen_समयr अणु
	व्योम (*trigger)(व्योम *arg);
	व्योम (*overflow)(व्योम *arg);
	व्योम *arg;
	u8 index;
पूर्ण;

काष्ठा ath_gen_समयr_table अणु
	काष्ठा ath_gen_समयr *समयrs[ATH_MAX_GEN_TIMER];
	u16 समयr_mask;
	bool tsf2_enabled;
पूर्ण;

काष्ठा ath_hw_antcomb_conf अणु
	u8 मुख्य_lna_conf;
	u8 alt_lna_conf;
	u8 fast_भाग_bias;
	u8 मुख्य_gaपूर्णांकb;
	u8 alt_gaपूर्णांकb;
	पूर्णांक lna1_lna2_delta;
	पूर्णांक lna1_lna2_चयन_delta;
	u8 भाग_group;
पूर्ण;

/**
 * काष्ठा ath_hw_radar_conf - radar detection initialization parameters
 *
 * @pulse_inband: threshold क्रम checking the ratio of in-band घातer
 *	to total घातer क्रम लघु radar pulses (half dB steps)
 * @pulse_inband_step: threshold क्रम checking an in-band घातer to total
 *	घातer ratio increase क्रम लघु radar pulses (half dB steps)
 * @pulse_height: threshold क्रम detecting the beginning of a लघु
 *	radar pulse (dB step)
 * @pulse_rssi: threshold क्रम detecting अगर a लघु radar pulse is
 *	gone (dB step)
 * @pulse_maxlen: maximum pulse length (0.8 us steps)
 *
 * @radar_rssi: RSSI threshold क्रम starting दीर्घ radar detection (dB steps)
 * @radar_inband: threshold क्रम checking the ratio of in-band घातer
 *	to total घातer क्रम दीर्घ radar pulses (half dB steps)
 * @fir_घातer: threshold क्रम detecting the end of a दीर्घ radar pulse (dB)
 *
 * @ext_channel: enable extension channel radar detection
 */
काष्ठा ath_hw_radar_conf अणु
	अचिन्हित पूर्णांक pulse_inband;
	अचिन्हित पूर्णांक pulse_inband_step;
	अचिन्हित पूर्णांक pulse_height;
	अचिन्हित पूर्णांक pulse_rssi;
	अचिन्हित पूर्णांक pulse_maxlen;

	अचिन्हित पूर्णांक radar_rssi;
	अचिन्हित पूर्णांक radar_inband;
	पूर्णांक fir_घातer;

	bool ext_channel;
पूर्ण;

/**
 * काष्ठा ath_hw_निजी_ops - callbacks used पूर्णांकernally by hardware code
 *
 * This काष्ठाure contains निजी callbacks deचिन्हित to only be used पूर्णांकernally
 * by the hardware core.
 *
 * @init_cal_settings: setup types of calibrations supported
 * @init_cal: starts actual calibration
 *
 * @init_mode_gain_regs: Initialize TX/RX gain रेजिस्टरs
 *
 * @rf_set_freq: change frequency
 * @spur_mitigate_freq: spur mitigation
 * @set_rf_regs:
 * @compute_pll_control: compute the PLL control value to use क्रम
 *	AR_RTC_PLL_CONTROL क्रम a given channel
 * @setup_calibration: set up calibration
 * @iscal_supported: used to query अगर a type of calibration is supported
 *
 * @ani_cache_ini_regs: cache the values क्रम ANI from the initial
 *	रेजिस्टर settings through the रेजिस्टर initialization.
 */
काष्ठा ath_hw_निजी_ops अणु
	व्योम (*init_hang_checks)(काष्ठा ath_hw *ah);
	bool (*detect_mac_hang)(काष्ठा ath_hw *ah);
	bool (*detect_bb_hang)(काष्ठा ath_hw *ah);

	/* Calibration ops */
	व्योम (*init_cal_settings)(काष्ठा ath_hw *ah);
	bool (*init_cal)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);

	व्योम (*init_mode_gain_regs)(काष्ठा ath_hw *ah);
	व्योम (*setup_calibration)(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_cal_list *currCal);

	/* PHY ops */
	पूर्णांक (*rf_set_freq)(काष्ठा ath_hw *ah,
			   काष्ठा ath9k_channel *chan);
	व्योम (*spur_mitigate_freq)(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan);
	bool (*set_rf_regs)(काष्ठा ath_hw *ah,
			    काष्ठा ath9k_channel *chan,
			    u16 modesIndex);
	व्योम (*set_channel_regs)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
	व्योम (*init_bb)(काष्ठा ath_hw *ah,
			काष्ठा ath9k_channel *chan);
	पूर्णांक (*process_ini)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
	व्योम (*olc_init)(काष्ठा ath_hw *ah);
	व्योम (*set_rभ_शेषe)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
	व्योम (*mark_phy_inactive)(काष्ठा ath_hw *ah);
	व्योम (*set_delta_slope)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
	bool (*rfbus_req)(काष्ठा ath_hw *ah);
	व्योम (*rfbus_करोne)(काष्ठा ath_hw *ah);
	व्योम (*restore_chainmask)(काष्ठा ath_hw *ah);
	u32 (*compute_pll_control)(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan);
	bool (*ani_control)(काष्ठा ath_hw *ah, क्रमागत ath9k_ani_cmd cmd,
			    पूर्णांक param);
	व्योम (*करो_getnf)(काष्ठा ath_hw *ah, पूर्णांक16_t nfarray[NUM_NF_READINGS]);
	व्योम (*set_radar_params)(काष्ठा ath_hw *ah,
				 काष्ठा ath_hw_radar_conf *conf);
	पूर्णांक (*fast_chan_change)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
				u8 *ini_reloaded);

	/* ANI */
	व्योम (*ani_cache_ini_regs)(काष्ठा ath_hw *ah);

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	bool (*is_aic_enabled)(काष्ठा ath_hw *ah);
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */
पूर्ण;

/**
 * काष्ठा ath_spec_scan - parameters क्रम Atheros spectral scan
 *
 * @enabled: enable/disable spectral scan
 * @लघु_repeat: controls whether the chip is in spectral scan mode
 *		  क्रम 4 usec (enabled) or 204 usec (disabled)
 * @count: number of scan results requested. There are special meanings
 *	   in some chip revisions:
 *	   AR92xx: highest bit set (>=128) क्रम endless mode
 *		   (spectral scan won't stopped until explicitly disabled)
 *	   AR9300 and newer: 0 क्रम endless mode
 * @endless: true अगर endless mode is पूर्णांकended. Otherwise, count value is
 *           corrected to the next possible value.
 * @period: समय duration between successive spectral scan entry poपूर्णांकs
 *	    (period*256*Tclk). Tclk = ath_common->घड़ीrate
 * @fft_period: PHY passes FFT frames to MAC every (fft_period+1)*4uS
 *
 * Note: Tclk = 40MHz or 44MHz depending upon operating mode.
 *	 Typically it's 44MHz in 2/5GHz on later chips, but there's
 *	 a "fast clock" check क्रम this in 5GHz.
 *
 */
काष्ठा ath_spec_scan अणु
	bool enabled;
	bool लघु_repeat;
	bool endless;
	u8 count;
	u8 period;
	u8 fft_period;
पूर्ण;

/**
 * काष्ठा ath_hw_ops - callbacks used by hardware code and driver code
 *
 * This काष्ठाure contains callbacks deचिन्हित to to be used पूर्णांकernally by
 * hardware code and also by the lower level driver.
 *
 * @config_pci_घातersave:
 * @calibrate: periodic calibration क्रम NF, ANI, IQ, ADC gain, ADC-DC
 *
 * @spectral_scan_config: set parameters क्रम spectral scan and enable/disable it
 * @spectral_scan_trigger: trigger a spectral scan run
 * @spectral_scan_रुको: रुको क्रम a spectral scan run to finish
 */
काष्ठा ath_hw_ops अणु
	व्योम (*config_pci_घातersave)(काष्ठा ath_hw *ah,
				     bool घातer_off);
	व्योम (*rx_enable)(काष्ठा ath_hw *ah);
	व्योम (*set_desc_link)(व्योम *ds, u32 link);
	पूर्णांक (*calibrate)(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			 u8 rxchainmask, bool दीर्घcal);
	bool (*get_isr)(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked,
			u32 *sync_cause_p);
	व्योम (*set_txdesc)(काष्ठा ath_hw *ah, व्योम *ds,
			   काष्ठा ath_tx_info *i);
	पूर्णांक (*proc_txdesc)(काष्ठा ath_hw *ah, व्योम *ds,
			   काष्ठा ath_tx_status *ts);
	पूर्णांक (*get_duration)(काष्ठा ath_hw *ah, स्थिर व्योम *ds, पूर्णांक index);
	व्योम (*antभाग_comb_conf_get)(काष्ठा ath_hw *ah,
			काष्ठा ath_hw_antcomb_conf *antconf);
	व्योम (*antभाग_comb_conf_set)(काष्ठा ath_hw *ah,
			काष्ठा ath_hw_antcomb_conf *antconf);
	व्योम (*spectral_scan_config)(काष्ठा ath_hw *ah,
				     काष्ठा ath_spec_scan *param);
	व्योम (*spectral_scan_trigger)(काष्ठा ath_hw *ah);
	व्योम (*spectral_scan_रुको)(काष्ठा ath_hw *ah);

	व्योम (*tx99_start)(काष्ठा ath_hw *ah, u32 qnum);
	व्योम (*tx99_stop)(काष्ठा ath_hw *ah);
	व्योम (*tx99_set_txघातer)(काष्ठा ath_hw *ah, u8 घातer);

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	व्योम (*set_bt_ant_भागersity)(काष्ठा ath_hw *hw, bool enable);
#पूर्ण_अगर
पूर्ण;

काष्ठा ath_nf_limits अणु
	s16 max;
	s16 min;
	s16 nominal;
	s16 cal[AR5416_MAX_CHAINS];
	s16 pwr[AR5416_MAX_CHAINS];
पूर्ण;

क्रमागत ath_cal_list अणु
	TX_IQ_CAL         =	BIT(0),
	TX_IQ_ON_AGC_CAL  =	BIT(1),
	TX_CL_CAL         =	BIT(2),
पूर्ण;

/* ah_flags */
#घोषणा AH_USE_EEPROM   0x1
#घोषणा AH_UNPLUGGED    0x2 /* The card has been physically हटाओd. */
#घोषणा AH_FASTCC       0x4
#घोषणा AH_NO_EEP_SWAP  0x8 /* Do not swap EEPROM data */

काष्ठा ath_hw अणु
	काष्ठा ath_ops reg_ops;

	काष्ठा device *dev;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ath_common common;
	काष्ठा ath9k_hw_version hw_version;
	काष्ठा ath9k_ops_config config;
	काष्ठा ath9k_hw_capabilities caps;
	काष्ठा ath9k_channel channels[ATH9K_NUM_CHANNELS];
	काष्ठा ath9k_channel *curchan;

	जोड़ अणु
		काष्ठा ar5416_eeprom_def def;
		काष्ठा ar5416_eeprom_4k map4k;
		काष्ठा ar9287_eeprom map9287;
		काष्ठा ar9300_eeprom ar9300_eep;
	पूर्ण eeprom;
	स्थिर काष्ठा eeprom_ops *eep_ops;

	bool sw_mgmt_crypto_tx;
	bool sw_mgmt_crypto_rx;
	bool is_pciexpress;
	bool aspm_enabled;
	bool is_monitoring;
	bool need_an_top2_fixup;
	u16 tx_trig_level;

	u32 nf_regs[6];
	काष्ठा ath_nf_limits nf_2g;
	काष्ठा ath_nf_limits nf_5g;
	u16 rfsilent;
	u32 rfसमाप्त_gpio;
	u32 rfसमाप्त_polarity;
	u32 ah_flags;
	s16 nf_override;

	bool reset_घातer_on;
	bool htc_reset_init;

	क्रमागत nl80211_अगरtype opmode;
	क्रमागत ath9k_घातer_mode घातer_mode;

	s8 noise;
	काष्ठा ath9k_hw_cal_data *caldata;
	काष्ठा ath9k_pacal_info pacal_info;
	काष्ठा ar5416Stats stats;
	काष्ठा ath9k_tx_queue_info txq[ATH9K_NUM_TX_QUEUES];
	DECLARE_BITMAP(pending_del_keymap, ATH_KEYMAX);

	क्रमागत ath9k_पूर्णांक imask;
	u32 imrs2_reg;
	u32 txok_पूर्णांकerrupt_mask;
	u32 txerr_पूर्णांकerrupt_mask;
	u32 txdesc_पूर्णांकerrupt_mask;
	u32 txeol_पूर्णांकerrupt_mask;
	u32 txurn_पूर्णांकerrupt_mask;
	atomic_t पूर्णांकr_ref_cnt;
	bool chip_fullsleep;
	u32 modes_index;

	/* Calibration */
	u32 supp_cals;
	अचिन्हित दीर्घ cal_start_समय;
	काष्ठा ath9k_cal_list iq_caldata;
	काष्ठा ath9k_cal_list adcgain_caldata;
	काष्ठा ath9k_cal_list adcdc_caldata;
	काष्ठा ath9k_cal_list *cal_list;
	काष्ठा ath9k_cal_list *cal_list_last;
	काष्ठा ath9k_cal_list *cal_list_curr;
#घोषणा totalPowerMeasI meas0.unsign
#घोषणा totalPowerMeasQ meas1.unsign
#घोषणा totalIqCorrMeas meas2.sign
#घोषणा totalAdcIOddPhase  meas0.unsign
#घोषणा totalAdcIEvenPhase meas1.unsign
#घोषणा totalAdcQOddPhase  meas2.unsign
#घोषणा totalAdcQEvenPhase meas3.unsign
#घोषणा totalAdcDcOffsetIOddPhase  meas0.sign
#घोषणा totalAdcDcOffsetIEvenPhase meas1.sign
#घोषणा totalAdcDcOffsetQOddPhase  meas2.sign
#घोषणा totalAdcDcOffsetQEvenPhase meas3.sign
	जोड़ अणु
		u32 unsign[AR5416_MAX_CHAINS];
		पूर्णांक32_t sign[AR5416_MAX_CHAINS];
	पूर्ण meas0;
	जोड़ अणु
		u32 unsign[AR5416_MAX_CHAINS];
		पूर्णांक32_t sign[AR5416_MAX_CHAINS];
	पूर्ण meas1;
	जोड़ अणु
		u32 unsign[AR5416_MAX_CHAINS];
		पूर्णांक32_t sign[AR5416_MAX_CHAINS];
	पूर्ण meas2;
	जोड़ अणु
		u32 unsign[AR5416_MAX_CHAINS];
		पूर्णांक32_t sign[AR5416_MAX_CHAINS];
	पूर्ण meas3;
	u16 cal_samples;
	u8 enabled_cals;

	u32 sta_id1_शेषs;
	u32 misc_mode;

	/* Private to hardware code */
	काष्ठा ath_hw_निजी_ops निजी_ops;
	/* Accessed by the lower level driver */
	काष्ठा ath_hw_ops ops;

	/* Used to program the radio on non single-chip devices */
	u32 *analogBank6Data;

	पूर्णांक coverage_class;
	u32 slotसमय;
	u32 globaltxसमयout;

	/* ANI */
	u32 aniperiod;
	क्रमागत ath9k_ani_cmd ani_function;
	u32 ani_skip_count;
	काष्ठा ar5416AniState ani;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	काष्ठा ath_btcoex_hw btcoex_hw;
#पूर्ण_अगर

	u32 पूर्णांकr_txqs;
	u8 txchainmask;
	u8 rxchainmask;

	काष्ठा ath_hw_radar_conf radar_conf;

	u32 originalGain[22];
	पूर्णांक initPDADC;
	पूर्णांक PDADCdelta;
	पूर्णांक led_pin;
	u32 gpio_mask;
	u32 gpio_val;

	काष्ठा ar5416IniArray ini_dfs;
	काष्ठा ar5416IniArray iniModes;
	काष्ठा ar5416IniArray iniCommon;
	काष्ठा ar5416IniArray iniBB_RfGain;
	काष्ठा ar5416IniArray iniBank6;
	काष्ठा ar5416IniArray iniAddac;
	काष्ठा ar5416IniArray iniPcieSerdes;
	काष्ठा ar5416IniArray iniPcieSerdesLowPower;
	काष्ठा ar5416IniArray iniModesFastClock;
	काष्ठा ar5416IniArray iniAdditional;
	काष्ठा ar5416IniArray iniModesRxGain;
	काष्ठा ar5416IniArray ini_modes_rx_gain_bounds;
	काष्ठा ar5416IniArray iniModesTxGain;
	काष्ठा ar5416IniArray iniCckfirNormal;
	काष्ठा ar5416IniArray iniCckfirJapan2484;
	काष्ठा ar5416IniArray iniModes_9271_ANI_reg;
	काष्ठा ar5416IniArray ini_radio_post_sys2ant;
	काष्ठा ar5416IniArray ini_modes_rxgain_xlna;
	काष्ठा ar5416IniArray ini_modes_rxgain_bb_core;
	काष्ठा ar5416IniArray ini_modes_rxgain_bb_postamble;

	काष्ठा ar5416IniArray iniMac[ATH_INI_NUM_SPLIT];
	काष्ठा ar5416IniArray iniBB[ATH_INI_NUM_SPLIT];
	काष्ठा ar5416IniArray iniRadio[ATH_INI_NUM_SPLIT];
	काष्ठा ar5416IniArray iniSOC[ATH_INI_NUM_SPLIT];

	u32 पूर्णांकr_gen_समयr_trigger;
	u32 पूर्णांकr_gen_समयr_thresh;
	काष्ठा ath_gen_समयr_table hw_gen_समयrs;

	काष्ठा ar9003_txs *ts_ring;
	u32 ts_paddr_start;
	u32 ts_paddr_end;
	u16 ts_tail;
	u16 ts_size;

	u32 bb_watchकरोg_last_status;
	u32 bb_watchकरोg_समयout_ms; /* in ms, 0 to disable */
	u8 bb_hang_rx_ofdm; /* true अगर bb hang due to rx_ofdm */

	अचिन्हित पूर्णांक paprd_target_घातer;
	अचिन्हित पूर्णांक paprd_training_घातer;
	अचिन्हित पूर्णांक paprd_ratemask;
	अचिन्हित पूर्णांक paprd_ratemask_ht40;
	bool paprd_table_ग_लिखो_करोne;
	u32 paprd_gain_table_entries[PAPRD_GAIN_TABLE_ENTRIES];
	u8 paprd_gain_table_index[PAPRD_GAIN_TABLE_ENTRIES];
	/*
	 * Store the permanent value of Reg 0x4004in WARegVal
	 * so we करोnt have to R/M/W. We should not be पढ़ोing
	 * this रेजिस्टर when in sleep states.
	 */
	u32 WARegVal;

	/* Enterprise mode cap */
	u32 ent_mode;

#अगर_घोषित CONFIG_ATH9K_WOW
	काष्ठा ath9k_hw_wow wow;
#पूर्ण_अगर
	bool is_clk_25mhz;
	पूर्णांक (*get_mac_revision)(व्योम);
	पूर्णांक (*बाह्यal_reset)(व्योम);
	bool disable_2ghz;
	bool disable_5ghz;

	स्थिर काष्ठा firmware *eeprom_blob;

	काष्ठा ath_dynack dynack;

	bool tpc_enabled;
	u8 tx_घातer[Ar5416RateSize];
	u8 tx_घातer_stbc[Ar5416RateSize];
	bool msi_enabled;
	u32 msi_mask;
	u32 msi_reg;
पूर्ण;

काष्ठा ath_bus_ops अणु
	क्रमागत ath_bus_type ath_bus_type;
	व्योम (*पढ़ो_cachesize)(काष्ठा ath_common *common, पूर्णांक *csz);
	bool (*eeprom_पढ़ो)(काष्ठा ath_common *common, u32 off, u16 *data);
	व्योम (*bt_coex_prep)(काष्ठा ath_common *common);
	व्योम (*aspm_init)(काष्ठा ath_common *common);
पूर्ण;

अटल अंतरभूत काष्ठा ath_common *ath9k_hw_common(काष्ठा ath_hw *ah)
अणु
	वापस &ah->common;
पूर्ण

अटल अंतरभूत काष्ठा ath_regulatory *ath9k_hw_regulatory(काष्ठा ath_hw *ah)
अणु
	वापस &(ath9k_hw_common(ah)->regulatory);
पूर्ण

अटल अंतरभूत काष्ठा ath_hw_निजी_ops *ath9k_hw_निजी_ops(काष्ठा ath_hw *ah)
अणु
	वापस &ah->निजी_ops;
पूर्ण

अटल अंतरभूत काष्ठा ath_hw_ops *ath9k_hw_ops(काष्ठा ath_hw *ah)
अणु
	वापस &ah->ops;
पूर्ण

अटल अंतरभूत u8 get_streams(पूर्णांक mask)
अणु
	वापस !!(mask & BIT(0)) + !!(mask & BIT(1)) + !!(mask & BIT(2));
पूर्ण

/* Initialization, Detach, Reset */
व्योम ath9k_hw_deinit(काष्ठा ath_hw *ah);
पूर्णांक ath9k_hw_init(काष्ठा ath_hw *ah);
पूर्णांक ath9k_hw_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
		   काष्ठा ath9k_hw_cal_data *caldata, bool fastcc);
पूर्णांक ath9k_hw_fill_cap_info(काष्ठा ath_hw *ah);
u32 ath9k_regd_get_ctl(काष्ठा ath_regulatory *reg, काष्ठा ath9k_channel *chan);

/* GPIO / RFKILL / Antennae */
व्योम ath9k_hw_gpio_request_in(काष्ठा ath_hw *ah, u32 gpio, स्थिर अक्षर *label);
व्योम ath9k_hw_gpio_request_out(काष्ठा ath_hw *ah, u32 gpio, स्थिर अक्षर *label,
			       u32 ah_संकेत_type);
व्योम ath9k_hw_gpio_मुक्त(काष्ठा ath_hw *ah, u32 gpio);
u32 ath9k_hw_gpio_get(काष्ठा ath_hw *ah, u32 gpio);
व्योम ath9k_hw_set_gpio(काष्ठा ath_hw *ah, u32 gpio, u32 val);
व्योम ath9k_hw_setantenna(काष्ठा ath_hw *ah, u32 antenna);

/* General Operation */
व्योम ath9k_hw_synth_delay(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			  पूर्णांक hw_delay);
bool ath9k_hw_रुको(काष्ठा ath_hw *ah, u32 reg, u32 mask, u32 val, u32 समयout);
व्योम ath9k_hw_ग_लिखो_array(काष्ठा ath_hw *ah, स्थिर काष्ठा ar5416IniArray *array,
			  पूर्णांक column, अचिन्हित पूर्णांक *ग_लिखोcnt);
व्योम ath9k_hw_पढ़ो_array(काष्ठा ath_hw *ah, u32 array[][2], पूर्णांक size);
u32 ath9k_hw_reverse_bits(u32 val, u32 n);
u16 ath9k_hw_computetxसमय(काष्ठा ath_hw *ah,
			   u8 phy, पूर्णांक kbps,
			   u32 frameLen, u16 rateix, bool लघुPreamble);
व्योम ath9k_hw_get_channel_centers(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan,
				  काष्ठा chan_centers *centers);
u32 ath9k_hw_getrxfilter(काष्ठा ath_hw *ah);
व्योम ath9k_hw_setrxfilter(काष्ठा ath_hw *ah, u32 bits);
bool ath9k_hw_phy_disable(काष्ठा ath_hw *ah);
bool ath9k_hw_disable(काष्ठा ath_hw *ah);
व्योम ath9k_hw_set_txघातerlimit(काष्ठा ath_hw *ah, u32 limit, bool test);
व्योम ath9k_hw_setopmode(काष्ठा ath_hw *ah);
व्योम ath9k_hw_seपंचांगcastfilter(काष्ठा ath_hw *ah, u32 filter0, u32 filter1);
व्योम ath9k_hw_ग_लिखो_associd(काष्ठा ath_hw *ah);
u32 ath9k_hw_gettsf32(काष्ठा ath_hw *ah);
u64 ath9k_hw_gettsf64(काष्ठा ath_hw *ah);
व्योम ath9k_hw_settsf64(काष्ठा ath_hw *ah, u64 tsf64);
व्योम ath9k_hw_reset_tsf(काष्ठा ath_hw *ah);
u32 ath9k_hw_get_tsf_offset(काष्ठा बारpec64 *last, काष्ठा बारpec64 *cur);
व्योम ath9k_hw_set_tsfadjust(काष्ठा ath_hw *ah, bool set);
व्योम ath9k_hw_init_global_settings(काष्ठा ath_hw *ah);
u32 ar9003_get_pll_sqsum_dvc(काष्ठा ath_hw *ah);
व्योम ath9k_hw_set11nmac2040(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
व्योम ath9k_hw_beaconinit(काष्ठा ath_hw *ah, u32 next_beacon, u32 beacon_period);
व्योम ath9k_hw_set_sta_beacon_समयrs(काष्ठा ath_hw *ah,
				    स्थिर काष्ठा ath9k_beacon_state *bs);
व्योम ath9k_hw_check_nav(काष्ठा ath_hw *ah);
bool ath9k_hw_check_alive(काष्ठा ath_hw *ah);

bool ath9k_hw_setघातer(काष्ठा ath_hw *ah, क्रमागत ath9k_घातer_mode mode);

/* Generic hw समयr primitives */
काष्ठा ath_gen_समयr *ath_gen_समयr_alloc(काष्ठा ath_hw *ah,
					  व्योम (*trigger)(व्योम *),
					  व्योम (*overflow)(व्योम *),
					  व्योम *arg,
					  u8 समयr_index);
व्योम ath9k_hw_gen_समयr_start(काष्ठा ath_hw *ah,
			      काष्ठा ath_gen_समयr *समयr,
			      u32 समयr_next,
			      u32 समयr_period);
व्योम ath9k_hw_gen_समयr_start_tsf2(काष्ठा ath_hw *ah);
व्योम ath9k_hw_gen_समयr_stop(काष्ठा ath_hw *ah, काष्ठा ath_gen_समयr *समयr);

व्योम ath_gen_समयr_मुक्त(काष्ठा ath_hw *ah, काष्ठा ath_gen_समयr *समयr);
व्योम ath_gen_समयr_isr(काष्ठा ath_hw *hw);

व्योम ath9k_hw_name(काष्ठा ath_hw *ah, अक्षर *hw_name, माप_प्रकार len);

/* PHY */
व्योम ath9k_hw_get_delta_slope_vals(काष्ठा ath_hw *ah, u32 coef_scaled,
				   u32 *coef_mantissa, u32 *coef_exponent);
व्योम ath9k_hw_apply_txघातer(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			    bool test);

/*
 * Code Specअगरic to AR5008, AR9001 or AR9002,
 * we stuff these here to aव्योम callbacks क्रम AR9003.
 */
पूर्णांक ar9002_hw_rf_claim(काष्ठा ath_hw *ah);
व्योम ar9002_hw_enable_async_fअगरo(काष्ठा ath_hw *ah);

/*
 * Code specअगरic to AR9003, we stuff these here to aव्योम callbacks
 * क्रम older families
 */
bool ar9003_hw_bb_watchकरोg_check(काष्ठा ath_hw *ah);
व्योम ar9003_hw_bb_watchकरोg_config(काष्ठा ath_hw *ah);
व्योम ar9003_hw_bb_watchकरोg_पढ़ो(काष्ठा ath_hw *ah);
व्योम ar9003_hw_bb_watchकरोg_dbg_info(काष्ठा ath_hw *ah);
व्योम ar9003_hw_disable_phy_restart(काष्ठा ath_hw *ah);
व्योम ar9003_paprd_enable(काष्ठा ath_hw *ah, bool val);
व्योम ar9003_paprd_populate_single_table(काष्ठा ath_hw *ah,
					काष्ठा ath9k_hw_cal_data *caldata,
					पूर्णांक chain);
पूर्णांक ar9003_paprd_create_curve(काष्ठा ath_hw *ah,
			      काष्ठा ath9k_hw_cal_data *caldata, पूर्णांक chain);
व्योम ar9003_paprd_setup_gain_table(काष्ठा ath_hw *ah, पूर्णांक chain);
पूर्णांक ar9003_paprd_init_table(काष्ठा ath_hw *ah);
bool ar9003_paprd_is_करोne(काष्ठा ath_hw *ah);
bool ar9003_is_paprd_enabled(काष्ठा ath_hw *ah);
व्योम ar9003_hw_set_chain_masks(काष्ठा ath_hw *ah, u8 rx, u8 tx);
व्योम ar9003_hw_init_rate_txघातer(काष्ठा ath_hw *ah, u8 *rate_array,
				 काष्ठा ath9k_channel *chan);
व्योम ar5008_hw_cmn_spur_mitigate(काष्ठा ath_hw *ah,
				 काष्ठा ath9k_channel *chan, पूर्णांक bin);
व्योम ar5008_hw_init_rate_txघातer(काष्ठा ath_hw *ah, पूर्णांक16_t *rate_array,
				 काष्ठा ath9k_channel *chan, पूर्णांक ht40_delta);

/* Hardware family op attach helpers */
पूर्णांक ar5008_hw_attach_phy_ops(काष्ठा ath_hw *ah);
व्योम ar9002_hw_attach_phy_ops(काष्ठा ath_hw *ah);
व्योम ar9003_hw_attach_phy_ops(काष्ठा ath_hw *ah);

व्योम ar9002_hw_attach_calib_ops(काष्ठा ath_hw *ah);
व्योम ar9003_hw_attach_calib_ops(काष्ठा ath_hw *ah);

पूर्णांक ar9002_hw_attach_ops(काष्ठा ath_hw *ah);
व्योम ar9003_hw_attach_ops(काष्ठा ath_hw *ah);

व्योम ar9002_hw_load_ani_reg(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);

व्योम ath9k_ani_reset(काष्ठा ath_hw *ah, bool is_scanning);
व्योम ath9k_hw_ani_monitor(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);

व्योम ath9k_hw_set_ack_समयout(काष्ठा ath_hw *ah, u32 us);
व्योम ath9k_hw_set_cts_समयout(काष्ठा ath_hw *ah, u32 us);
व्योम ath9k_hw_setslotसमय(काष्ठा ath_hw *ah, u32 us);

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
व्योम ar9003_hw_attach_aic_ops(काष्ठा ath_hw *ah);
अटल अंतरभूत bool ath9k_hw_btcoex_is_enabled(काष्ठा ath_hw *ah)
अणु
	वापस ah->btcoex_hw.enabled;
पूर्ण
अटल अंतरभूत bool ath9k_hw_mci_is_enabled(काष्ठा ath_hw *ah)
अणु
	वापस ah->common.btcoex_enabled &&
	       (ah->caps.hw_caps & ATH9K_HW_CAP_MCI);

पूर्ण
व्योम ath9k_hw_btcoex_enable(काष्ठा ath_hw *ah);
अटल अंतरभूत क्रमागत ath_btcoex_scheme
ath9k_hw_get_btcoex_scheme(काष्ठा ath_hw *ah)
अणु
	वापस ah->btcoex_hw.scheme;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ar9003_hw_attach_aic_ops(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत bool ath9k_hw_btcoex_is_enabled(काष्ठा ath_hw *ah)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool ath9k_hw_mci_is_enabled(काष्ठा ath_hw *ah)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम ath9k_hw_btcoex_enable(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत क्रमागत ath_btcoex_scheme
ath9k_hw_get_btcoex_scheme(काष्ठा ath_hw *ah)
अणु
	वापस ATH_BTCOEX_CFG_NONE;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */


#अगर_घोषित CONFIG_ATH9K_WOW
पूर्णांक ath9k_hw_wow_apply_pattern(काष्ठा ath_hw *ah, u8 *user_pattern,
			       u8 *user_mask, पूर्णांक pattern_count,
			       पूर्णांक pattern_len);
u32 ath9k_hw_wow_wakeup(काष्ठा ath_hw *ah);
व्योम ath9k_hw_wow_enable(काष्ठा ath_hw *ah, u32 pattern_enable);
#अन्यथा
अटल अंतरभूत पूर्णांक ath9k_hw_wow_apply_pattern(काष्ठा ath_hw *ah,
					     u8 *user_pattern,
					     u8 *user_mask,
					     पूर्णांक pattern_count,
					     पूर्णांक pattern_len)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u32 ath9k_hw_wow_wakeup(काष्ठा ath_hw *ah)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ath9k_hw_wow_enable(काष्ठा ath_hw *ah, u32 pattern_enable)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा ATH9K_CLOCK_RATE_CCK		22
#घोषणा ATH9K_CLOCK_RATE_5GHZ_OFDM	40
#घोषणा ATH9K_CLOCK_RATE_2GHZ_OFDM	44
#घोषणा ATH9K_CLOCK_FAST_RATE_5GHZ_OFDM 44

#पूर्ण_अगर
