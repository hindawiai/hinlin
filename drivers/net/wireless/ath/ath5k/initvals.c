<शैली गुरु>
/*
 * Initial रेजिस्टर settings functions
 *
 * Copyright (c) 2004-2007 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2009 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Jiri Slaby <jirislaby@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
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
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"

/**
 * काष्ठा ath5k_ini - Mode-independent initial रेजिस्टर ग_लिखोs
 * @ini_रेजिस्टर: Register address
 * @ini_value: Default value
 * @ini_mode: 0 to ग_लिखो 1 to पढ़ो (and clear)
 */
काष्ठा ath5k_ini अणु
	u16	ini_रेजिस्टर;
	u32	ini_value;

	क्रमागत अणु
		AR5K_INI_WRITE = 0,	/* Default */
		AR5K_INI_READ = 1,
	पूर्ण ini_mode;
पूर्ण;

/**
 * काष्ठा ath5k_ini_mode - Mode specअगरic initial रेजिस्टर values
 * @mode_रेजिस्टर: Register address
 * @mode_value: Set of values क्रम each क्रमागत ath5k_driver_mode
 */
काष्ठा ath5k_ini_mode अणु
	u16	mode_रेजिस्टर;
	u32	mode_value[3];
पूर्ण;

/* Initial रेजिस्टर settings क्रम AR5210 */
अटल स्थिर काष्ठा ath5k_ini ar5210_ini[] = अणु
	/* PCU and MAC रेजिस्टरs */
	अणु AR5K_NOQCU_TXDP0,	0 पूर्ण,
	अणु AR5K_NOQCU_TXDP1,	0 पूर्ण,
	अणु AR5K_RXDP,		0 पूर्ण,
	अणु AR5K_CR,		0 पूर्ण,
	अणु AR5K_ISR,		0, AR5K_INI_READ पूर्ण,
	अणु AR5K_IMR,		0 पूर्ण,
	अणु AR5K_IER,		AR5K_IER_DISABLE पूर्ण,
	अणु AR5K_BSR,		0, AR5K_INI_READ पूर्ण,
	अणु AR5K_TXCFG,		AR5K_DMASIZE_128B पूर्ण,
	अणु AR5K_RXCFG,		AR5K_DMASIZE_128B पूर्ण,
	अणु AR5K_CFG,		AR5K_INIT_CFG पूर्ण,
	अणु AR5K_TOPS,		8 पूर्ण,
	अणु AR5K_RXNOFRM,		8 पूर्ण,
	अणु AR5K_RPGTO,		0 पूर्ण,
	अणु AR5K_TXNOFRM,		0 पूर्ण,
	अणु AR5K_SFR,		0 पूर्ण,
	अणु AR5K_MIBC,		0 पूर्ण,
	अणु AR5K_MISC,		0 पूर्ण,
	अणु AR5K_RX_FILTER_5210,	0 पूर्ण,
	अणु AR5K_MCAST_FILTER0_5210, 0 पूर्ण,
	अणु AR5K_MCAST_FILTER1_5210, 0 पूर्ण,
	अणु AR5K_TX_MASK0,	0 पूर्ण,
	अणु AR5K_TX_MASK1,	0 पूर्ण,
	अणु AR5K_CLR_TMASK,	0 पूर्ण,
	अणु AR5K_TRIG_LVL,	AR5K_TUNE_MIN_TX_FIFO_THRES पूर्ण,
	अणु AR5K_DIAG_SW_5210,	0 पूर्ण,
	अणु AR5K_RSSI_THR,	AR5K_TUNE_RSSI_THRES पूर्ण,
	अणु AR5K_TSF_L32_5210,	0 पूर्ण,
	अणु AR5K_TIMER0_5210,	0 पूर्ण,
	अणु AR5K_TIMER1_5210,	0xffffffff पूर्ण,
	अणु AR5K_TIMER2_5210,	0xffffffff पूर्ण,
	अणु AR5K_TIMER3_5210,	1 पूर्ण,
	अणु AR5K_CFP_DUR_5210,	0 पूर्ण,
	अणु AR5K_CFP_PERIOD_5210,	0 पूर्ण,
	/* PHY रेजिस्टरs */
	अणु AR5K_PHY(0),	0x00000047 पूर्ण,
	अणु AR5K_PHY_AGC,	0x00000000 पूर्ण,
	अणु AR5K_PHY(3),	0x09848ea6 पूर्ण,
	अणु AR5K_PHY(4),	0x3d32e000 पूर्ण,
	अणु AR5K_PHY(5),	0x0000076b पूर्ण,
	अणु AR5K_PHY_ACT,	AR5K_PHY_ACT_DISABLE पूर्ण,
	अणु AR5K_PHY(8),	0x02020200 पूर्ण,
	अणु AR5K_PHY(9),	0x00000e0e पूर्ण,
	अणु AR5K_PHY(10),	0x0a020201 पूर्ण,
	अणु AR5K_PHY(11),	0x00036ffc पूर्ण,
	अणु AR5K_PHY(12),	0x00000000 पूर्ण,
	अणु AR5K_PHY(13),	0x00000e0e पूर्ण,
	अणु AR5K_PHY(14),	0x00000007 पूर्ण,
	अणु AR5K_PHY(15),	0x00020100 पूर्ण,
	अणु AR5K_PHY(16),	0x89630000 पूर्ण,
	अणु AR5K_PHY(17),	0x1372169c पूर्ण,
	अणु AR5K_PHY(18),	0x0018b633 पूर्ण,
	अणु AR5K_PHY(19),	0x1284613c पूर्ण,
	अणु AR5K_PHY(20),	0x0de8b8e0 पूर्ण,
	अणु AR5K_PHY(21),	0x00074859 पूर्ण,
	अणु AR5K_PHY(22),	0x7e80beba पूर्ण,
	अणु AR5K_PHY(23),	0x313a665e पूर्ण,
	अणु AR5K_PHY_AGCCTL, 0x00001d08 पूर्ण,
	अणु AR5K_PHY(25),	0x0001ce00 पूर्ण,
	अणु AR5K_PHY(26),	0x409a4190 पूर्ण,
	अणु AR5K_PHY(28),	0x0000000f पूर्ण,
	अणु AR5K_PHY(29),	0x00000080 पूर्ण,
	अणु AR5K_PHY(30),	0x00000004 पूर्ण,
	अणु AR5K_PHY(31),	0x00000018 पूर्ण,	/* 0x987c */
	अणु AR5K_PHY(64),	0x00000000 पूर्ण,	/* 0x9900 */
	अणु AR5K_PHY(65),	0x00000000 पूर्ण,
	अणु AR5K_PHY(66),	0x00000000 पूर्ण,
	अणु AR5K_PHY(67),	0x00800000 पूर्ण,
	अणु AR5K_PHY(68),	0x00000003 पूर्ण,
	/* BB gain table (64bytes) */
	अणु AR5K_BB_GAIN(0), 0x00000000 पूर्ण,
	अणु AR5K_BB_GAIN(1), 0x00000020 पूर्ण,
	अणु AR5K_BB_GAIN(2), 0x00000010 पूर्ण,
	अणु AR5K_BB_GAIN(3), 0x00000030 पूर्ण,
	अणु AR5K_BB_GAIN(4), 0x00000008 पूर्ण,
	अणु AR5K_BB_GAIN(5), 0x00000028 पूर्ण,
	अणु AR5K_BB_GAIN(6), 0x00000028 पूर्ण,
	अणु AR5K_BB_GAIN(7), 0x00000004 पूर्ण,
	अणु AR5K_BB_GAIN(8), 0x00000024 पूर्ण,
	अणु AR5K_BB_GAIN(9), 0x00000014 पूर्ण,
	अणु AR5K_BB_GAIN(10), 0x00000034 पूर्ण,
	अणु AR5K_BB_GAIN(11), 0x0000000c पूर्ण,
	अणु AR5K_BB_GAIN(12), 0x0000002c पूर्ण,
	अणु AR5K_BB_GAIN(13), 0x00000002 पूर्ण,
	अणु AR5K_BB_GAIN(14), 0x00000022 पूर्ण,
	अणु AR5K_BB_GAIN(15), 0x00000012 पूर्ण,
	अणु AR5K_BB_GAIN(16), 0x00000032 पूर्ण,
	अणु AR5K_BB_GAIN(17), 0x0000000a पूर्ण,
	अणु AR5K_BB_GAIN(18), 0x0000002a पूर्ण,
	अणु AR5K_BB_GAIN(19), 0x00000001 पूर्ण,
	अणु AR5K_BB_GAIN(20), 0x00000021 पूर्ण,
	अणु AR5K_BB_GAIN(21), 0x00000011 पूर्ण,
	अणु AR5K_BB_GAIN(22), 0x00000031 पूर्ण,
	अणु AR5K_BB_GAIN(23), 0x00000009 पूर्ण,
	अणु AR5K_BB_GAIN(24), 0x00000029 पूर्ण,
	अणु AR5K_BB_GAIN(25), 0x00000005 पूर्ण,
	अणु AR5K_BB_GAIN(26), 0x00000025 पूर्ण,
	अणु AR5K_BB_GAIN(27), 0x00000015 पूर्ण,
	अणु AR5K_BB_GAIN(28), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(29), 0x0000000d पूर्ण,
	अणु AR5K_BB_GAIN(30), 0x0000002d पूर्ण,
	अणु AR5K_BB_GAIN(31), 0x00000003 पूर्ण,
	अणु AR5K_BB_GAIN(32), 0x00000023 पूर्ण,
	अणु AR5K_BB_GAIN(33), 0x00000013 पूर्ण,
	अणु AR5K_BB_GAIN(34), 0x00000033 पूर्ण,
	अणु AR5K_BB_GAIN(35), 0x0000000b पूर्ण,
	अणु AR5K_BB_GAIN(36), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(37), 0x00000007 पूर्ण,
	अणु AR5K_BB_GAIN(38), 0x00000027 पूर्ण,
	अणु AR5K_BB_GAIN(39), 0x00000017 पूर्ण,
	अणु AR5K_BB_GAIN(40), 0x00000037 पूर्ण,
	अणु AR5K_BB_GAIN(41), 0x0000000f पूर्ण,
	अणु AR5K_BB_GAIN(42), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(43), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(44), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(45), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(46), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(47), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(48), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(49), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(50), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(51), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(52), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(53), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(54), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(55), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(56), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(57), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(58), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(59), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(60), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(61), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(62), 0x0000002f पूर्ण,
	अणु AR5K_BB_GAIN(63), 0x0000002f पूर्ण,
	/* 5110 RF gain table (64btes) */
	अणु AR5K_RF_GAIN(0), 0x0000001d पूर्ण,
	अणु AR5K_RF_GAIN(1), 0x0000005d पूर्ण,
	अणु AR5K_RF_GAIN(2), 0x0000009d पूर्ण,
	अणु AR5K_RF_GAIN(3), 0x000000dd पूर्ण,
	अणु AR5K_RF_GAIN(4), 0x0000011d पूर्ण,
	अणु AR5K_RF_GAIN(5), 0x00000021 पूर्ण,
	अणु AR5K_RF_GAIN(6), 0x00000061 पूर्ण,
	अणु AR5K_RF_GAIN(7), 0x000000a1 पूर्ण,
	अणु AR5K_RF_GAIN(8), 0x000000e1 पूर्ण,
	अणु AR5K_RF_GAIN(9), 0x00000031 पूर्ण,
	अणु AR5K_RF_GAIN(10), 0x00000071 पूर्ण,
	अणु AR5K_RF_GAIN(11), 0x000000b1 पूर्ण,
	अणु AR5K_RF_GAIN(12), 0x0000001c पूर्ण,
	अणु AR5K_RF_GAIN(13), 0x0000005c पूर्ण,
	अणु AR5K_RF_GAIN(14), 0x00000029 पूर्ण,
	अणु AR5K_RF_GAIN(15), 0x00000069 पूर्ण,
	अणु AR5K_RF_GAIN(16), 0x000000a9 पूर्ण,
	अणु AR5K_RF_GAIN(17), 0x00000020 पूर्ण,
	अणु AR5K_RF_GAIN(18), 0x00000019 पूर्ण,
	अणु AR5K_RF_GAIN(19), 0x00000059 पूर्ण,
	अणु AR5K_RF_GAIN(20), 0x00000099 पूर्ण,
	अणु AR5K_RF_GAIN(21), 0x00000030 पूर्ण,
	अणु AR5K_RF_GAIN(22), 0x00000005 पूर्ण,
	अणु AR5K_RF_GAIN(23), 0x00000025 पूर्ण,
	अणु AR5K_RF_GAIN(24), 0x00000065 पूर्ण,
	अणु AR5K_RF_GAIN(25), 0x000000a5 पूर्ण,
	अणु AR5K_RF_GAIN(26), 0x00000028 पूर्ण,
	अणु AR5K_RF_GAIN(27), 0x00000068 पूर्ण,
	अणु AR5K_RF_GAIN(28), 0x0000001f पूर्ण,
	अणु AR5K_RF_GAIN(29), 0x0000001e पूर्ण,
	अणु AR5K_RF_GAIN(30), 0x00000018 पूर्ण,
	अणु AR5K_RF_GAIN(31), 0x00000058 पूर्ण,
	अणु AR5K_RF_GAIN(32), 0x00000098 पूर्ण,
	अणु AR5K_RF_GAIN(33), 0x00000003 पूर्ण,
	अणु AR5K_RF_GAIN(34), 0x00000004 पूर्ण,
	अणु AR5K_RF_GAIN(35), 0x00000044 पूर्ण,
	अणु AR5K_RF_GAIN(36), 0x00000084 पूर्ण,
	अणु AR5K_RF_GAIN(37), 0x00000013 पूर्ण,
	अणु AR5K_RF_GAIN(38), 0x00000012 पूर्ण,
	अणु AR5K_RF_GAIN(39), 0x00000052 पूर्ण,
	अणु AR5K_RF_GAIN(40), 0x00000092 पूर्ण,
	अणु AR5K_RF_GAIN(41), 0x000000d2 पूर्ण,
	अणु AR5K_RF_GAIN(42), 0x0000002b पूर्ण,
	अणु AR5K_RF_GAIN(43), 0x0000002a पूर्ण,
	अणु AR5K_RF_GAIN(44), 0x0000006a पूर्ण,
	अणु AR5K_RF_GAIN(45), 0x000000aa पूर्ण,
	अणु AR5K_RF_GAIN(46), 0x0000001b पूर्ण,
	अणु AR5K_RF_GAIN(47), 0x0000001a पूर्ण,
	अणु AR5K_RF_GAIN(48), 0x0000005a पूर्ण,
	अणु AR5K_RF_GAIN(49), 0x0000009a पूर्ण,
	अणु AR5K_RF_GAIN(50), 0x000000da पूर्ण,
	अणु AR5K_RF_GAIN(51), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(52), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(53), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(54), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(55), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(56), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(57), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(58), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(59), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(60), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(61), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(62), 0x00000006 पूर्ण,
	अणु AR5K_RF_GAIN(63), 0x00000006 पूर्ण,
	/* PHY activation */
	अणु AR5K_PHY(53), 0x00000020 पूर्ण,
	अणु AR5K_PHY(51), 0x00000004 पूर्ण,
	अणु AR5K_PHY(50), 0x00060106 पूर्ण,
	अणु AR5K_PHY(39), 0x0000006d पूर्ण,
	अणु AR5K_PHY(48), 0x00000000 पूर्ण,
	अणु AR5K_PHY(52), 0x00000014 पूर्ण,
	अणु AR5K_PHY_ACT, AR5K_PHY_ACT_ENABLE पूर्ण,
पूर्ण;

/* Initial रेजिस्टर settings क्रम AR5211 */
अटल स्थिर काष्ठा ath5k_ini ar5211_ini[] = अणु
	अणु AR5K_RXDP,		0x00000000 पूर्ण,
	अणु AR5K_RTSD0,		0x84849c9c पूर्ण,
	अणु AR5K_RTSD1,		0x7c7c7c7c पूर्ण,
	अणु AR5K_RXCFG,		0x00000005 पूर्ण,
	अणु AR5K_MIBC,		0x00000000 पूर्ण,
	अणु AR5K_TOPS,		0x00000008 पूर्ण,
	अणु AR5K_RXNOFRM,		0x00000008 पूर्ण,
	अणु AR5K_TXNOFRM,		0x00000010 पूर्ण,
	अणु AR5K_RPGTO,		0x00000000 पूर्ण,
	अणु AR5K_RFCNT,		0x0000001f पूर्ण,
	अणु AR5K_QUEUE_TXDP(0),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(1),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(2),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(3),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(4),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(5),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(6),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(7),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(8),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(9),	0x00000000 पूर्ण,
	अणु AR5K_DCU_FP,		0x00000000 पूर्ण,
	अणु AR5K_STA_ID1,		0x00000000 पूर्ण,
	अणु AR5K_BSS_ID0,		0x00000000 पूर्ण,
	अणु AR5K_BSS_ID1,		0x00000000 पूर्ण,
	अणु AR5K_RSSI_THR,	0x00000000 पूर्ण,
	अणु AR5K_CFP_PERIOD_5211,	0x00000000 पूर्ण,
	अणु AR5K_TIMER0_5211,	0x00000030 पूर्ण,
	अणु AR5K_TIMER1_5211,	0x0007ffff पूर्ण,
	अणु AR5K_TIMER2_5211,	0x01ffffff पूर्ण,
	अणु AR5K_TIMER3_5211,	0x00000031 पूर्ण,
	अणु AR5K_CFP_DUR_5211,	0x00000000 पूर्ण,
	अणु AR5K_RX_FILTER_5211,	0x00000000 पूर्ण,
	अणु AR5K_MCAST_FILTER0_5211, 0x00000000 पूर्ण,
	अणु AR5K_MCAST_FILTER1_5211, 0x00000002 पूर्ण,
	अणु AR5K_DIAG_SW_5211,	0x00000000 पूर्ण,
	अणु AR5K_ADDAC_TEST,	0x00000000 पूर्ण,
	अणु AR5K_DEFAULT_ANTENNA,	0x00000000 पूर्ण,
	/* PHY रेजिस्टरs */
	अणु AR5K_PHY_AGC,	0x00000000 पूर्ण,
	अणु AR5K_PHY(3),	0x2d849093 पूर्ण,
	अणु AR5K_PHY(4),	0x7d32e000 पूर्ण,
	अणु AR5K_PHY(5),	0x00000f6b पूर्ण,
	अणु AR5K_PHY_ACT,	0x00000000 पूर्ण,
	अणु AR5K_PHY(11),	0x00026ffe पूर्ण,
	अणु AR5K_PHY(12),	0x00000000 पूर्ण,
	अणु AR5K_PHY(15),	0x00020100 पूर्ण,
	अणु AR5K_PHY(16),	0x206a017a पूर्ण,
	अणु AR5K_PHY(19),	0x1284613c पूर्ण,
	अणु AR5K_PHY(21),	0x00000859 पूर्ण,
	अणु AR5K_PHY(26),	0x409a4190 पूर्ण,	/* 0x9868 */
	अणु AR5K_PHY(27),	0x050cb081 पूर्ण,
	अणु AR5K_PHY(28),	0x0000000f पूर्ण,
	अणु AR5K_PHY(29),	0x00000080 पूर्ण,
	अणु AR5K_PHY(30),	0x0000000c पूर्ण,
	अणु AR5K_PHY(64),	0x00000000 पूर्ण,
	अणु AR5K_PHY(65),	0x00000000 पूर्ण,
	अणु AR5K_PHY(66),	0x00000000 पूर्ण,
	अणु AR5K_PHY(67),	0x00800000 पूर्ण,
	अणु AR5K_PHY(68),	0x00000001 पूर्ण,
	अणु AR5K_PHY(71),	0x0000092a पूर्ण,
	अणु AR5K_PHY_IQ,	0x00000000 पूर्ण,
	अणु AR5K_PHY(73),	0x00058a05 पूर्ण,
	अणु AR5K_PHY(74),	0x00000001 पूर्ण,
	अणु AR5K_PHY(75),	0x00000000 पूर्ण,
	अणु AR5K_PHY_PAPD_PROBE, 0x00000000 पूर्ण,
	अणु AR5K_PHY(77),	0x00000000 पूर्ण,	/* 0x9934 */
	अणु AR5K_PHY(78),	0x00000000 पूर्ण,	/* 0x9938 */
	अणु AR5K_PHY(79),	0x0000003f पूर्ण,	/* 0x993c */
	अणु AR5K_PHY(80),	0x00000004 पूर्ण,
	अणु AR5K_PHY(82),	0x00000000 पूर्ण,
	अणु AR5K_PHY(83),	0x00000000 पूर्ण,
	अणु AR5K_PHY(84),	0x00000000 पूर्ण,
	अणु AR5K_PHY_RADAR, 0x5d50f14c पूर्ण,
	अणु AR5K_PHY(86),	0x00000018 पूर्ण,
	अणु AR5K_PHY(87),	0x004b6a8e पूर्ण,
	/* Initial Power table (32bytes)
	 * common on all cards/modes.
	 * Note: Table is rewritten during
	 * txघातer setup later using calibration
	 * data etc. so next ग_लिखो is non-common */
	अणु AR5K_PHY_PCDAC_TXPOWER(1), 0x06ff05ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(2), 0x07ff07ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(3), 0x08ff08ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(4), 0x09ff09ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(5), 0x0aff0aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(6), 0x0bff0bff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(7), 0x0cff0cff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(8), 0x0dff0dff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(9), 0x0fff0eff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(10), 0x12ff12ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(11), 0x14ff13ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(12), 0x16ff15ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(13), 0x19ff17ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(14), 0x1bff1aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(15), 0x1eff1dff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(16), 0x23ff20ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(17), 0x27ff25ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(18), 0x2cff29ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(19), 0x31ff2fff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(20), 0x37ff34ff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(21), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(22), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(23), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(24), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(25), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(26), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(27), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(28), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(29), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(30), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER(31), 0x3aff3aff पूर्ण,
	अणु AR5K_PHY_CCKTXCTL, 0x00000000 पूर्ण,
	अणु AR5K_PHY(642), 0x503e4646 पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ, 0x6480416c पूर्ण,
	अणु AR5K_PHY(644), 0x0199a003 पूर्ण,
	अणु AR5K_PHY(645), 0x044cd610 पूर्ण,
	अणु AR5K_PHY(646), 0x13800040 पूर्ण,
	अणु AR5K_PHY(647), 0x1be00060 पूर्ण,
	अणु AR5K_PHY(648), 0x0c53800a पूर्ण,
	अणु AR5K_PHY(649), 0x0014df3b पूर्ण,
	अणु AR5K_PHY(650), 0x000001b5 पूर्ण,
	अणु AR5K_PHY(651), 0x00000020 पूर्ण,
पूर्ण;

/* Initial mode-specअगरic settings क्रम AR5211
 * 5211 supports OFDM-only g (draft g) but we
 * need to test it ! */
अटल स्थिर काष्ठा ath5k_ini_mode ar5211_ini_mode[] = अणु
	अणु AR5K_TXCFG,
	/*	A          B           G       */
	   अणु 0x00000015, 0x0000001d, 0x00000015 पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(0),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(1),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(2),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(3),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(4),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(5),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(6),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(7),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(8),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(9),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_SLOT,
	   अणु 0x00000168, 0x000001b8, 0x00000168 पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_SIFS,
	   अणु 0x00000230, 0x000000b0, 0x00000230 पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_EIFS,
	   अणु 0x00000d98, 0x00001f48, 0x00000d98 पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_MISC,
	   अणु 0x0000a0e0, 0x00005880, 0x0000a0e0 पूर्ण पूर्ण,
	अणु AR5K_TIME_OUT,
	   अणु 0x04000400, 0x20003000, 0x04000400 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x0e8d8fa7, 0x01608f95, 0x0e8d8fa7 पूर्ण पूर्ण,
	अणु AR5K_PHY(8),
	   अणु 0x02020200, 0x02010200, 0x02020200 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL2,
	   अणु 0x00000e0e, 0x00000707, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05010000, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e0e, 0x00000e0e, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000007, 0x0000000b, 0x0000000b पूर्ण पूर्ण,
	अणु AR5K_PHY_SETTLING,
	   अणु 0x1372169c, 0x137216a8, 0x1372169c पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018ba67, 0x0018ba69, 0x0018ba69 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0c28b4e0, 0x0c28b4e0, 0x0c28b4e0 पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7e800d2e, 0x7ec00d2e, 0x7e800d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x31375d5e, 0x313a5d5e, 0x31375d5e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCTL,
	   अणु 0x0000bd10, 0x0000bd38, 0x0000bd10 पूर्ण पूर्ण,
	अणु AR5K_PHY_NF,
	   अणु 0x0001ce00, 0x0001ce00, 0x0001ce00 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x00002710, 0x0000157c, 0x00002710 पूर्ण पूर्ण,
	अणु AR5K_PHY(70),
	   अणु 0x00000190, 0x00000084, 0x00000190 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0x6fe01020, 0x6fe00920, 0x6fe01020 पूर्ण पूर्ण,
	अणु AR5K_PHY_PCDAC_TXPOWER_BASE,
	   अणु 0x05ff14ff, 0x05ff14ff, 0x05ff19ff पूर्ण पूर्ण,
	अणु AR5K_RF_BUFFER_CONTROL_4,
	   अणु 0x00000010, 0x00000010, 0x00000010 पूर्ण पूर्ण,
पूर्ण;

/* Initial रेजिस्टर settings क्रम AR5212 and newer chips */
अटल स्थिर काष्ठा ath5k_ini ar5212_ini_common_start[] = अणु
	अणु AR5K_RXDP,		0x00000000 पूर्ण,
	अणु AR5K_RXCFG,		0x00000005 पूर्ण,
	अणु AR5K_MIBC,		0x00000000 पूर्ण,
	अणु AR5K_TOPS,		0x00000008 पूर्ण,
	अणु AR5K_RXNOFRM,		0x00000008 पूर्ण,
	अणु AR5K_TXNOFRM,		0x00000010 पूर्ण,
	अणु AR5K_RPGTO,		0x00000000 पूर्ण,
	अणु AR5K_RFCNT,		0x0000001f पूर्ण,
	अणु AR5K_QUEUE_TXDP(0),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(1),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(2),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(3),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(4),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(5),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(6),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(7),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(8),	0x00000000 पूर्ण,
	अणु AR5K_QUEUE_TXDP(9),	0x00000000 पूर्ण,
	अणु AR5K_DCU_FP,		0x00000000 पूर्ण,
	अणु AR5K_DCU_TXP,		0x00000000 पूर्ण,
	/* Tx filter table 0 (32 entries) */
	अणु AR5K_DCU_TX_FILTER_0(0),  0x00000000 पूर्ण, /* DCU 0 */
	अणु AR5K_DCU_TX_FILTER_0(1),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(2),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(3),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(4),  0x00000000 पूर्ण, /* DCU 1 */
	अणु AR5K_DCU_TX_FILTER_0(5),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(6),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(7),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(8),  0x00000000 पूर्ण, /* DCU 2 */
	अणु AR5K_DCU_TX_FILTER_0(9),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(10), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(11), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(12), 0x00000000 पूर्ण, /* DCU 3 */
	अणु AR5K_DCU_TX_FILTER_0(13), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(14), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(15), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(16), 0x00000000 पूर्ण, /* DCU 4 */
	अणु AR5K_DCU_TX_FILTER_0(17), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(18), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(19), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(20), 0x00000000 पूर्ण, /* DCU 5 */
	अणु AR5K_DCU_TX_FILTER_0(21), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(22), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(23), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(24), 0x00000000 पूर्ण, /* DCU 6 */
	अणु AR5K_DCU_TX_FILTER_0(25), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(26), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(27), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(28), 0x00000000 पूर्ण, /* DCU 7 */
	अणु AR5K_DCU_TX_FILTER_0(29), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(30), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_0(31), 0x00000000 पूर्ण,
	/* Tx filter table 1 (16 entries) */
	अणु AR5K_DCU_TX_FILTER_1(0),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(1),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(2),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(3),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(4),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(5),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(6),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(7),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(8),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(9),  0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(10), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(11), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(12), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(13), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(14), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_1(15), 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_CLR, 0x00000000 पूर्ण,
	अणु AR5K_DCU_TX_FILTER_SET, 0x00000000 पूर्ण,
	अणु AR5K_STA_ID1,		0x00000000 पूर्ण,
	अणु AR5K_BSS_ID0,		0x00000000 पूर्ण,
	अणु AR5K_BSS_ID1,		0x00000000 पूर्ण,
	अणु AR5K_BEACON_5211,	0x00000000 पूर्ण,
	अणु AR5K_CFP_PERIOD_5211, 0x00000000 पूर्ण,
	अणु AR5K_TIMER0_5211,	0x00000030 पूर्ण,
	अणु AR5K_TIMER1_5211,	0x0007ffff पूर्ण,
	अणु AR5K_TIMER2_5211,	0x01ffffff पूर्ण,
	अणु AR5K_TIMER3_5211,	0x00000031 पूर्ण,
	अणु AR5K_CFP_DUR_5211,	0x00000000 पूर्ण,
	अणु AR5K_RX_FILTER_5211,	0x00000000 पूर्ण,
	अणु AR5K_DIAG_SW_5211,	0x00000000 पूर्ण,
	अणु AR5K_ADDAC_TEST,	0x00000000 पूर्ण,
	अणु AR5K_DEFAULT_ANTENNA,	0x00000000 पूर्ण,
	अणु AR5K_FRAME_CTL_QOSM,	0x000fc78f पूर्ण,
	अणु AR5K_XRMODE,		0x2a82301a पूर्ण,
	अणु AR5K_XRDELAY,		0x05dc01e0 पूर्ण,
	अणु AR5K_XRTIMEOUT,	0x1f402710 पूर्ण,
	अणु AR5K_XRCHIRP,		0x01f40000 पूर्ण,
	अणु AR5K_XRSTOMP,		0x00001e1c पूर्ण,
	अणु AR5K_SLEEP0,		0x0002aaaa पूर्ण,
	अणु AR5K_SLEEP1,		0x02005555 पूर्ण,
	अणु AR5K_SLEEP2,		0x00000000 पूर्ण,
	अणु AR_BSSMSKL,		0xffffffff पूर्ण,
	अणु AR_BSSMSKU,		0x0000ffff पूर्ण,
	अणु AR5K_TXPC,		0x00000000 पूर्ण,
	अणु AR5K_PROFCNT_TX,	0x00000000 पूर्ण,
	अणु AR5K_PROFCNT_RX,	0x00000000 पूर्ण,
	अणु AR5K_PROFCNT_RXCLR,	0x00000000 पूर्ण,
	अणु AR5K_PROFCNT_CYCLE,	0x00000000 पूर्ण,
	अणु AR5K_QUIET_CTL1,	0x00000088 पूर्ण,
	/* Initial rate duration table (32 entries )*/
	अणु AR5K_RATE_DUR(0),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(1),	0x0000008c पूर्ण,
	अणु AR5K_RATE_DUR(2),	0x000000e4 पूर्ण,
	अणु AR5K_RATE_DUR(3),	0x000002d5 पूर्ण,
	अणु AR5K_RATE_DUR(4),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(5),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(6),	0x000000a0 पूर्ण,
	अणु AR5K_RATE_DUR(7),	0x000001c9 पूर्ण,
	अणु AR5K_RATE_DUR(8),	0x0000002c पूर्ण,
	अणु AR5K_RATE_DUR(9),	0x0000002c पूर्ण,
	अणु AR5K_RATE_DUR(10),	0x00000030 पूर्ण,
	अणु AR5K_RATE_DUR(11),	0x0000003c पूर्ण,
	अणु AR5K_RATE_DUR(12),	0x0000002c पूर्ण,
	अणु AR5K_RATE_DUR(13),	0x0000002c पूर्ण,
	अणु AR5K_RATE_DUR(14),	0x00000030 पूर्ण,
	अणु AR5K_RATE_DUR(15),	0x0000003c पूर्ण,
	अणु AR5K_RATE_DUR(16),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(17),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(18),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(19),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(20),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(21),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(22),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(23),	0x00000000 पूर्ण,
	अणु AR5K_RATE_DUR(24),	0x000000d5 पूर्ण,
	अणु AR5K_RATE_DUR(25),	0x000000df पूर्ण,
	अणु AR5K_RATE_DUR(26),	0x00000102 पूर्ण,
	अणु AR5K_RATE_DUR(27),	0x0000013a पूर्ण,
	अणु AR5K_RATE_DUR(28),	0x00000075 पूर्ण,
	अणु AR5K_RATE_DUR(29),	0x0000007f पूर्ण,
	अणु AR5K_RATE_DUR(30),	0x000000a2 पूर्ण,
	अणु AR5K_RATE_DUR(31),	0x00000000 पूर्ण,
	अणु AR5K_QUIET_CTL2,	0x00010002 पूर्ण,
	अणु AR5K_TSF_PARM,	0x00000001 पूर्ण,
	अणु AR5K_QOS_NOACK,	0x000000c0 पूर्ण,
	अणु AR5K_PHY_ERR_FIL,	0x00000000 पूर्ण,
	अणु AR5K_XRLAT_TX,	0x00000168 पूर्ण,
	अणु AR5K_ACKSIFS,		0x00000000 पूर्ण,
	/* Rate -> db table
	 * notice ...03<-02<-01<-00 ! */
	अणु AR5K_RATE2DB(0),	0x03020100 पूर्ण,
	अणु AR5K_RATE2DB(1),	0x07060504 पूर्ण,
	अणु AR5K_RATE2DB(2),	0x0b0a0908 पूर्ण,
	अणु AR5K_RATE2DB(3),	0x0f0e0d0c पूर्ण,
	अणु AR5K_RATE2DB(4),	0x13121110 पूर्ण,
	अणु AR5K_RATE2DB(5),	0x17161514 पूर्ण,
	अणु AR5K_RATE2DB(6),	0x1b1a1918 पूर्ण,
	अणु AR5K_RATE2DB(7),	0x1f1e1d1c पूर्ण,
	/* Db -> Rate table */
	अणु AR5K_DB2RATE(0),	0x03020100 पूर्ण,
	अणु AR5K_DB2RATE(1),	0x07060504 पूर्ण,
	अणु AR5K_DB2RATE(2),	0x0b0a0908 पूर्ण,
	अणु AR5K_DB2RATE(3),	0x0f0e0d0c पूर्ण,
	अणु AR5K_DB2RATE(4),	0x13121110 पूर्ण,
	अणु AR5K_DB2RATE(5),	0x17161514 पूर्ण,
	अणु AR5K_DB2RATE(6),	0x1b1a1918 पूर्ण,
	अणु AR5K_DB2RATE(7),	0x1f1e1d1c पूर्ण,
	/* PHY रेजिस्टरs (Common settings
	 * क्रम all chips/modes) */
	अणु AR5K_PHY(3),		0xad848e19 पूर्ण,
	अणु AR5K_PHY(4),		0x7d28e000 पूर्ण,
	अणु AR5K_PHY_TIMING_3,	0x9c0a9f6b पूर्ण,
	अणु AR5K_PHY_ACT,		0x00000000 पूर्ण,
	अणु AR5K_PHY(16),		0x206a017a पूर्ण,
	अणु AR5K_PHY(21),		0x00000859 पूर्ण,
	अणु AR5K_PHY_BIN_MASK_1,	0x00000000 पूर्ण,
	अणु AR5K_PHY_BIN_MASK_2,	0x00000000 पूर्ण,
	अणु AR5K_PHY_BIN_MASK_3,	0x00000000 पूर्ण,
	अणु AR5K_PHY_BIN_MASK_CTL, 0x00800000 पूर्ण,
	अणु AR5K_PHY_ANT_CTL,	0x00000001 पूर्ण,
	/*अणु AR5K_PHY(71), 0x0000092a पूर्ण,*/ /* Old value */
	अणु AR5K_PHY_MAX_RX_LEN,	0x00000c80 पूर्ण,
	अणु AR5K_PHY_IQ,		0x05100000 पूर्ण,
	अणु AR5K_PHY_WARM_RESET,	0x00000001 पूर्ण,
	अणु AR5K_PHY_CTL,		0x00000004 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE1, 0x1e1f2022 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE2, 0x0a0b0c0d पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE_MAX, 0x0000003f पूर्ण,
	अणु AR5K_PHY(82),		0x9280b212 पूर्ण,
	अणु AR5K_PHY_RADAR,	0x5d50e188 पूर्ण,
	/*अणु AR5K_PHY(86), 0x000000ff पूर्ण,*/
	अणु AR5K_PHY(87),		0x004b6a8e पूर्ण,
	अणु AR5K_PHY_NFTHRES,	0x000003ce पूर्ण,
	अणु AR5K_PHY_RESTART,	0x192fb515 पूर्ण,
	अणु AR5K_PHY(94),		0x00000001 पूर्ण,
	अणु AR5K_PHY_RFBUS_REQ,	0x00000000 पूर्ण,
	/*अणु AR5K_PHY(644), 0x0080a333 पूर्ण,*/ /* Old value */
	/*अणु AR5K_PHY(645), 0x00206c10 पूर्ण,*/ /* Old value */
	अणु AR5K_PHY(644),	0x00806333 पूर्ण,
	अणु AR5K_PHY(645),	0x00106c10 पूर्ण,
	अणु AR5K_PHY(646),	0x009c4060 पूर्ण,
	/* अणु AR5K_PHY(647), 0x1483800a पूर्ण, */
	/* अणु AR5K_PHY(648), 0x01831061 पूर्ण, */ /* Old value */
	अणु AR5K_PHY(648),	0x018830c6 पूर्ण,
	अणु AR5K_PHY(649),	0x00000400 पूर्ण,
	/*अणु AR5K_PHY(650), 0x000001b5 पूर्ण,*/
	अणु AR5K_PHY(651),	0x00000000 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE3, 0x20202020 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE4, 0x20202020 पूर्ण,
	/*अणु AR5K_PHY(655), 0x13c889af पूर्ण,*/
	अणु AR5K_PHY(656),	0x38490a20 पूर्ण,
	अणु AR5K_PHY(657),	0x00007bb6 पूर्ण,
	अणु AR5K_PHY(658),	0x0fff3ffc पूर्ण,
पूर्ण;

/* Initial mode-specअगरic settings क्रम AR5212 (Written beक्रमe ar5212_ini) */
अटल स्थिर काष्ठा ath5k_ini_mode ar5212_ini_mode_start[] = अणु
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(0),
	/*	A/XR          B           G       */
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(1),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(2),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(3),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(4),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(5),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(6),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(7),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(8),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_QUEUE_DFS_LOCAL_IFS(9),
	   अणु 0x002ffc0f, 0x002ffc1f, 0x002ffc0f पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_SIFS,
	   अणु 0x00000230, 0x000000b0, 0x00000160 पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_SLOT,
	   अणु 0x00000168, 0x000001b8, 0x0000018c पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_EIFS,
	   अणु 0x00000e60, 0x00001f1c, 0x00003e38 पूर्ण पूर्ण,
	अणु AR5K_DCU_GBL_IFS_MISC,
	   अणु 0x0000a0e0, 0x00005880, 0x0000b0e0 पूर्ण पूर्ण,
	अणु AR5K_TIME_OUT,
	   अणु 0x03e803e8, 0x04200420, 0x08400840 पूर्ण पूर्ण,
	अणु AR5K_PHY(8),
	   अणु 0x02020200, 0x02010200, 0x02020200 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL2,
	   अणु 0x00000e0e, 0x00000707, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_SETTLING,
	   अणु 0x1372161c, 0x13721722, 0x137216a2 पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCTL,
	   अणु 0x00009d10, 0x00009d18, 0x00009d18 पूर्ण पूर्ण,
	अणु AR5K_PHY_NF,
	   अणु 0x0001ce00, 0x0001ce00, 0x0001ce00 पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_HIGH_THR,
	   अणु 0x409a4190, 0x409a4190, 0x409a4190 पूर्ण पूर्ण,
	अणु AR5K_PHY(70),
	   अणु 0x000001b8, 0x00000084, 0x00000108 पूर्ण पूर्ण,
	अणु AR5K_PHY_OFDM_SELFCORR,
	   अणु 0x10058a05, 0x10058a05, 0x10058a05 पूर्ण पूर्ण,
	अणु 0xa230,
	   अणु 0x00000000, 0x00000000, 0x00000108 पूर्ण पूर्ण,
पूर्ण;

/* Initial mode-specअगरic settings क्रम AR5212 + RF5111
 * (Written after ar5212_ini) */
अटल स्थिर काष्ठा ath5k_ini_mode rf5111_ini_mode_end[] = अणु
	अणु AR5K_TXCFG,
	/*	A/XR          B           G       */
	   अणु 0x00008015, 0x00008015, 0x00008015 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x128d8fa7, 0x04e00f95, 0x12e00fab पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05010100, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e0e, 0x00000e0e, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000007, 0x0000000b, 0x0000000b पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018da5a, 0x0018ca69, 0x0018ca69 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0de8b4e0, 0x0de8b4e0, 0x0de8b4e0 पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7e800d2e, 0x7ee84d2e, 0x7ee84d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x3137665e, 0x3137665e, 0x3137665e पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_LOW_THR,
	   अणु 0x050cb081, 0x050cb081, 0x050cb080 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x00002710, 0x0000157c, 0x00002af8 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0xf7b81020, 0xf7b80d20, 0xf7b81020 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ,
	   अणु 0x642c416a, 0x6440416a, 0x6440416a पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_RX_CTL_4,
	   अणु 0x1883800a, 0x1873800a, 0x1883800a पूर्ण पूर्ण,
पूर्ण;

/* Common क्रम all modes */
अटल स्थिर काष्ठा ath5k_ini rf5111_ini_common_end[] = अणु
	अणु AR5K_DCU_FP,		0x00000000 पूर्ण,
	अणु AR5K_PHY_AGC,		0x00000000 पूर्ण,
	अणु AR5K_PHY_ADC_CTL,	0x00022ffe पूर्ण,
	अणु 0x983c,		0x00020100 पूर्ण,
	अणु AR5K_PHY_GAIN_OFFSET,	0x1284613c पूर्ण,
	अणु AR5K_PHY_PAPD_PROBE,	0x00004883 पूर्ण,
	अणु 0x9940,		0x00000004 पूर्ण,
	अणु 0x9958,		0x000000ff पूर्ण,
	अणु 0x9974,		0x00000000 पूर्ण,
	अणु AR5K_PHY_SPENDING,	0x00000018 पूर्ण,
	अणु AR5K_PHY_CCKTXCTL,	0x00000000 पूर्ण,
	अणु AR5K_PHY_CCK_CROSSCORR, 0xd03e6788 पूर्ण,
	अणु AR5K_PHY_DAG_CCK_CTL,	0x000001b5 पूर्ण,
	अणु 0xa23c,		0x13c889af पूर्ण,
पूर्ण;


/* Initial mode-specअगरic settings क्रम AR5212 + RF5112
 * (Written after ar5212_ini) */
अटल स्थिर काष्ठा ath5k_ini_mode rf5112_ini_mode_end[] = अणु
	अणु AR5K_TXCFG,
	/*	A/XR          B           G       */
	   अणु 0x00008015, 0x00008015, 0x00008015 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x128d93a7, 0x04e01395, 0x12e013ab पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05020100, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e0e, 0x00000e0e, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000007, 0x0000000b, 0x0000000b पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018da6d, 0x0018ca75, 0x0018ca75 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0de8b4e0, 0x0de8b4e0, 0x0de8b4e0 पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7e800d2e, 0x7ee80d2e, 0x7ee80d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x3137665e, 0x3137665e, 0x3137665e पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_LOW_THR,
	   अणु 0x050cb081, 0x050cb081, 0x050cb081 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x000007d0, 0x0000044c, 0x00000898 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0xf7b81020, 0xf7b80d10, 0xf7b81010 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCKTXCTL,
	   अणु 0x00000000, 0x00000008, 0x00000008 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_CROSSCORR,
	   अणु 0xd6be6788, 0xd03e6788, 0xd03e6788 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ,
	   अणु 0x642c0140, 0x6442c160, 0x6442c160 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_RX_CTL_4,
	   अणु 0x1883800a, 0x1873800a, 0x1883800a पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ath5k_ini rf5112_ini_common_end[] = अणु
	अणु AR5K_DCU_FP,		0x00000000 पूर्ण,
	अणु AR5K_PHY_AGC,		0x00000000 पूर्ण,
	अणु AR5K_PHY_ADC_CTL,	0x00022ffe पूर्ण,
	अणु 0x983c,		0x00020100 पूर्ण,
	अणु AR5K_PHY_GAIN_OFFSET,	0x1284613c पूर्ण,
	अणु AR5K_PHY_PAPD_PROBE,	0x00004882 पूर्ण,
	अणु 0x9940,		0x00000004 पूर्ण,
	अणु 0x9958,		0x000000ff पूर्ण,
	अणु 0x9974,		0x00000000 पूर्ण,
	अणु AR5K_PHY_DAG_CCK_CTL,	0x000001b5 पूर्ण,
	अणु 0xa23c,		0x13c889af पूर्ण,
पूर्ण;


/* Initial mode-specअगरic settings क्रम RF5413/5414
 * (Written after ar5212_ini) */
अटल स्थिर काष्ठा ath5k_ini_mode rf5413_ini_mode_end[] = अणु
	अणु AR5K_TXCFG,
	/*	A/XR          B           G       */
	   अणु 0x00000015, 0x00000015, 0x00000015 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x128d93a7, 0x04e01395, 0x12e013ab पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05020100, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e0e, 0x00000e0e, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000007, 0x0000000b, 0x0000000b पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018fa61, 0x001a1a63, 0x001a1a63 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0c98b4e0, 0x0c98b0da, 0x0c98b0da पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7ec80d2e, 0x7ec80d2e, 0x7ec80d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x3139605e, 0x3139605e, 0x3139605e पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_LOW_THR,
	   अणु 0x050cb081, 0x050cb081, 0x050cb081 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x000007d0, 0x0000044c, 0x00000898 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0xf7b81000, 0xf7b80d00, 0xf7b81000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCKTXCTL,
	   अणु 0x00000000, 0x00000000, 0x00000000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_CROSSCORR,
	   अणु 0xd6be6788, 0xd03e6788, 0xd03e6788 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ,
	   अणु 0x002ec1e0, 0x002ac120, 0x002ac120 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_RX_CTL_4,
	   अणु 0x1883800a, 0x1863800a, 0x1883800a पूर्ण पूर्ण,
	अणु 0xa300,
	   अणु 0x18010000, 0x18010000, 0x18010000 पूर्ण पूर्ण,
	अणु 0xa304,
	   अणु 0x30032602, 0x30032602, 0x30032602 पूर्ण पूर्ण,
	अणु 0xa308,
	   अणु 0x48073e06, 0x48073e06, 0x48073e06 पूर्ण पूर्ण,
	अणु 0xa30c,
	   अणु 0x560b4c0a, 0x560b4c0a, 0x560b4c0a पूर्ण पूर्ण,
	अणु 0xa310,
	   अणु 0x641a600f, 0x641a600f, 0x641a600f पूर्ण पूर्ण,
	अणु 0xa314,
	   अणु 0x784f6e1b, 0x784f6e1b, 0x784f6e1b पूर्ण पूर्ण,
	अणु 0xa318,
	   अणु 0x868f7c5a, 0x868f7c5a, 0x868f7c5a पूर्ण पूर्ण,
	अणु 0xa31c,
	   अणु 0x90cf865b, 0x8ecf865b, 0x8ecf865b पूर्ण पूर्ण,
	अणु 0xa320,
	   अणु 0x9d4f970f, 0x9b4f970f, 0x9b4f970f पूर्ण पूर्ण,
	अणु 0xa324,
	   अणु 0xa7cfa38f, 0xa3cf9f8f, 0xa3cf9f8f पूर्ण पूर्ण,
	अणु 0xa328,
	   अणु 0xb55faf1f, 0xb35faf1f, 0xb35faf1f पूर्ण पूर्ण,
	अणु 0xa32c,
	   अणु 0xbddfb99f, 0xbbdfb99f, 0xbbdfb99f पूर्ण पूर्ण,
	अणु 0xa330,
	   अणु 0xcb7fc53f, 0xcb7fc73f, 0xcb7fc73f पूर्ण पूर्ण,
	अणु 0xa334,
	   अणु 0xd5ffd1bf, 0xd3ffd1bf, 0xd3ffd1bf पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ath5k_ini rf5413_ini_common_end[] = अणु
	अणु AR5K_DCU_FP,		0x000003e0 पूर्ण,
	अणु AR5K_5414_CBCFG,	0x00000010 पूर्ण,
	अणु AR5K_SEQ_MASK,	0x0000000f पूर्ण,
	अणु 0x809c,		0x00000000 पूर्ण,
	अणु 0x80a0,		0x00000000 पूर्ण,
	अणु AR5K_MIC_QOS_CTL,	0x00000000 पूर्ण,
	अणु AR5K_MIC_QOS_SEL,	0x00000000 पूर्ण,
	अणु AR5K_MISC_MODE,	0x00000000 पूर्ण,
	अणु AR5K_OFDM_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_CCK_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1_MASK, 0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2_MASK, 0x00000000 पूर्ण,
	अणु AR5K_TSF_THRES,	0x00000000 पूर्ण,
	अणु 0x8140,		0x800003f9 पूर्ण,
	अणु 0x8144,		0x00000000 पूर्ण,
	अणु AR5K_PHY_AGC,		0x00000000 पूर्ण,
	अणु AR5K_PHY_ADC_CTL,	0x0000a000 पूर्ण,
	अणु 0x983c,		0x00200400 पूर्ण,
	अणु AR5K_PHY_GAIN_OFFSET, 0x1284233c पूर्ण,
	अणु AR5K_PHY_SCR,		0x0000001f पूर्ण,
	अणु AR5K_PHY_SLMT,	0x00000080 पूर्ण,
	अणु AR5K_PHY_SCAL,	0x0000000e पूर्ण,
	अणु 0x9958,		0x00081fff पूर्ण,
	अणु AR5K_PHY_TIMING_7,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TIMING_8,	0x02800000 पूर्ण,
	अणु AR5K_PHY_TIMING_11,	0x00000000 पूर्ण,
	अणु AR5K_PHY_HEAVY_CLIP_ENABLE, 0x00000000 पूर्ण,
	अणु 0x99e4,		0xaaaaaaaa पूर्ण,
	अणु 0x99e8,		0x3c466478 पूर्ण,
	अणु 0x99ec,		0x000000aa पूर्ण,
	अणु AR5K_PHY_SCLOCK,	0x0000000c पूर्ण,
	अणु AR5K_PHY_SDELAY,	0x000000ff पूर्ण,
	अणु AR5K_PHY_SPENDING,	0x00000014 पूर्ण,
	अणु AR5K_PHY_DAG_CCK_CTL, 0x000009b5 पूर्ण,
	अणु 0xa23c,		0x93c889af पूर्ण,
	अणु AR5K_PHY_FAST_ADC,	0x00000001 पूर्ण,
	अणु 0xa250,		0x0000a000 पूर्ण,
	अणु AR5K_PHY_BLUETOOTH,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG1,	0x0cc75380 पूर्ण,
	अणु 0xa25c,		0x0f0f0f01 पूर्ण,
	अणु 0xa260,		0x5f690f01 पूर्ण,
	अणु 0xa264,		0x00418a11 पूर्ण,
	अणु 0xa268,		0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG5,	0x0c30c16a पूर्ण,
	अणु 0xa270, 0x00820820 पूर्ण,
	अणु 0xa274, 0x081b7caa पूर्ण,
	अणु 0xa278, 0x1ce739ce पूर्ण,
	अणु 0xa27c, 0x051701ce पूर्ण,
	अणु 0xa338, 0x00000000 पूर्ण,
	अणु 0xa33c, 0x00000000 पूर्ण,
	अणु 0xa340, 0x00000000 पूर्ण,
	अणु 0xa344, 0x00000000 पूर्ण,
	अणु 0xa348, 0x3fffffff पूर्ण,
	अणु 0xa34c, 0x3fffffff पूर्ण,
	अणु 0xa350, 0x3fffffff पूर्ण,
	अणु 0xa354, 0x0003ffff पूर्ण,
	अणु 0xa358, 0x79a8aa1f पूर्ण,
	अणु 0xa35c, 0x066c420f पूर्ण,
	अणु 0xa360, 0x0f282207 पूर्ण,
	अणु 0xa364, 0x17601685 पूर्ण,
	अणु 0xa368, 0x1f801104 पूर्ण,
	अणु 0xa36c, 0x37a00c03 पूर्ण,
	अणु 0xa370, 0x3fc40883 पूर्ण,
	अणु 0xa374, 0x57c00803 पूर्ण,
	अणु 0xa378, 0x5fd80682 पूर्ण,
	अणु 0xa37c, 0x7fe00482 पूर्ण,
	अणु 0xa380, 0x7f3c7bba पूर्ण,
	अणु 0xa384, 0xf3307ff0 पूर्ण,
पूर्ण;

/* Initial mode-specअगरic settings क्रम RF2413/2414
 * (Written after ar5212_ini) */
/* XXX: a mode ? */
अटल स्थिर काष्ठा ath5k_ini_mode rf2413_ini_mode_end[] = अणु
	अणु AR5K_TXCFG,
	/*	A/XR          B           G       */
	   अणु 0x00000015, 0x00000015, 0x00000015 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x128d93a7, 0x04e01395, 0x12e013ab पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05020000, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e00, 0x00000e00, 0x00000e00 पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000002, 0x0000000a, 0x0000000a पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018da6d, 0x001a6a64, 0x001a6a64 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0de8b4e0, 0x0de8b0da, 0x0c98b0da पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7e800d2e, 0x7ee80d2e, 0x7ec80d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x3137665e, 0x3137665e, 0x3139605e पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_LOW_THR,
	   अणु 0x050cb081, 0x050cb081, 0x050cb081 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x000007d0, 0x0000044c, 0x00000898 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0xf7b81000, 0xf7b80d00, 0xf7b81000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCKTXCTL,
	   अणु 0x00000000, 0x00000000, 0x00000000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_CROSSCORR,
	   अणु 0xd6be6788, 0xd03e6788, 0xd03e6788 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ,
	   अणु 0x002c0140, 0x0042c140, 0x0042c140 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_RX_CTL_4,
	   अणु 0x1883800a, 0x1863800a, 0x1883800a पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ath5k_ini rf2413_ini_common_end[] = अणु
	अणु AR5K_DCU_FP,		0x000003e0 पूर्ण,
	अणु AR5K_SEQ_MASK,	0x0000000f पूर्ण,
	अणु AR5K_MIC_QOS_CTL,	0x00000000 पूर्ण,
	अणु AR5K_MIC_QOS_SEL,	0x00000000 पूर्ण,
	अणु AR5K_MISC_MODE,	0x00000000 पूर्ण,
	अणु AR5K_OFDM_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_CCK_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1_MASK, 0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2_MASK, 0x00000000 पूर्ण,
	अणु AR5K_TSF_THRES,	0x00000000 पूर्ण,
	अणु 0x8140,		0x800000a8 पूर्ण,
	अणु 0x8144,		0x00000000 पूर्ण,
	अणु AR5K_PHY_AGC,		0x00000000 पूर्ण,
	अणु AR5K_PHY_ADC_CTL,	0x0000a000 पूर्ण,
	अणु 0x983c,		0x00200400 पूर्ण,
	अणु AR5K_PHY_GAIN_OFFSET,	0x1284233c पूर्ण,
	अणु AR5K_PHY_SCR,		0x0000001f पूर्ण,
	अणु AR5K_PHY_SLMT,	0x00000080 पूर्ण,
	अणु AR5K_PHY_SCAL,	0x0000000e पूर्ण,
	अणु 0x9958,		0x000000ff पूर्ण,
	अणु AR5K_PHY_TIMING_7,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TIMING_8,	0x02800000 पूर्ण,
	अणु AR5K_PHY_TIMING_11,	0x00000000 पूर्ण,
	अणु AR5K_PHY_HEAVY_CLIP_ENABLE, 0x00000000 पूर्ण,
	अणु 0x99e4,		0xaaaaaaaa पूर्ण,
	अणु 0x99e8,		0x3c466478 पूर्ण,
	अणु 0x99ec,		0x000000aa पूर्ण,
	अणु AR5K_PHY_SCLOCK,	0x0000000c पूर्ण,
	अणु AR5K_PHY_SDELAY,	0x000000ff पूर्ण,
	अणु AR5K_PHY_SPENDING,	0x00000014 पूर्ण,
	अणु AR5K_PHY_DAG_CCK_CTL,	0x000009b5 पूर्ण,
	अणु 0xa23c,		0x93c889af पूर्ण,
	अणु AR5K_PHY_FAST_ADC,	0x00000001 पूर्ण,
	अणु 0xa250,		0x0000a000 पूर्ण,
	अणु AR5K_PHY_BLUETOOTH,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG1,	0x0cc75380 पूर्ण,
	अणु 0xa25c,		0x0f0f0f01 पूर्ण,
	अणु 0xa260,		0x5f690f01 पूर्ण,
	अणु 0xa264,		0x00418a11 पूर्ण,
	अणु 0xa268,		0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG5,	0x0c30c16a पूर्ण,
	अणु 0xa270, 0x00820820 पूर्ण,
	अणु 0xa274, 0x001b7caa पूर्ण,
	अणु 0xa278, 0x1ce739ce पूर्ण,
	अणु 0xa27c, 0x051701ce पूर्ण,
	अणु 0xa300, 0x18010000 पूर्ण,
	अणु 0xa304, 0x30032602 पूर्ण,
	अणु 0xa308, 0x48073e06 पूर्ण,
	अणु 0xa30c, 0x560b4c0a पूर्ण,
	अणु 0xa310, 0x641a600f पूर्ण,
	अणु 0xa314, 0x784f6e1b पूर्ण,
	अणु 0xa318, 0x868f7c5a पूर्ण,
	अणु 0xa31c, 0x8ecf865b पूर्ण,
	अणु 0xa320, 0x9d4f970f पूर्ण,
	अणु 0xa324, 0xa5cfa18f पूर्ण,
	अणु 0xa328, 0xb55faf1f पूर्ण,
	अणु 0xa32c, 0xbddfb99f पूर्ण,
	अणु 0xa330, 0xcd7fc73f पूर्ण,
	अणु 0xa334, 0xd5ffd1bf पूर्ण,
	अणु 0xa338, 0x00000000 पूर्ण,
	अणु 0xa33c, 0x00000000 पूर्ण,
	अणु 0xa340, 0x00000000 पूर्ण,
	अणु 0xa344, 0x00000000 पूर्ण,
	अणु 0xa348, 0x3fffffff पूर्ण,
	अणु 0xa34c, 0x3fffffff पूर्ण,
	अणु 0xa350, 0x3fffffff पूर्ण,
	अणु 0xa354, 0x0003ffff पूर्ण,
	अणु 0xa358, 0x79a8aa1f पूर्ण,
	अणु 0xa35c, 0x066c420f पूर्ण,
	अणु 0xa360, 0x0f282207 पूर्ण,
	अणु 0xa364, 0x17601685 पूर्ण,
	अणु 0xa368, 0x1f801104 पूर्ण,
	अणु 0xa36c, 0x37a00c03 पूर्ण,
	अणु 0xa370, 0x3fc40883 पूर्ण,
	अणु 0xa374, 0x57c00803 पूर्ण,
	अणु 0xa378, 0x5fd80682 पूर्ण,
	अणु 0xa37c, 0x7fe00482 पूर्ण,
	अणु 0xa380, 0x7f3c7bba पूर्ण,
	अणु 0xa384, 0xf3307ff0 पूर्ण,
पूर्ण;

/* Initial mode-specअगरic settings क्रम RF2425
 * (Written after ar5212_ini) */
/* XXX: a mode ? */
अटल स्थिर काष्ठा ath5k_ini_mode rf2425_ini_mode_end[] = अणु
	अणु AR5K_TXCFG,
	/*	A/XR          B           G       */
	   अणु 0x00000015, 0x00000015, 0x00000015 पूर्ण पूर्ण,
	अणु AR5K_USEC_5211,
	   अणु 0x128d93a7, 0x04e01395, 0x12e013ab पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL3,
	   अणु 0x0a020001, 0x05020100, 0x0a020001 पूर्ण पूर्ण,
	अणु AR5K_PHY_RF_CTL4,
	   अणु 0x00000e0e, 0x00000e0e, 0x00000e0e पूर्ण पूर्ण,
	अणु AR5K_PHY_PA_CTL,
	   अणु 0x00000003, 0x0000000b, 0x0000000b पूर्ण पूर्ण,
	अणु AR5K_PHY_SETTLING,
	   अणु 0x1372161c, 0x13721722, 0x13721422 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN,
	   अणु 0x0018fa61, 0x00199a65, 0x00199a65 पूर्ण पूर्ण,
	अणु AR5K_PHY_DESIRED_SIZE,
	   अणु 0x0c98b4e0, 0x0c98b0da, 0x0c98b0da पूर्ण पूर्ण,
	अणु AR5K_PHY_SIG,
	   अणु 0x7ec80d2e, 0x7ec80d2e, 0x7ec80d2e पूर्ण पूर्ण,
	अणु AR5K_PHY_AGCCOARSE,
	   अणु 0x3139605e, 0x3139605e, 0x3139605e पूर्ण पूर्ण,
	अणु AR5K_PHY_WEAK_OFDM_LOW_THR,
	   अणु 0x050cb081, 0x050cb081, 0x050cb081 पूर्ण पूर्ण,
	अणु AR5K_PHY_RX_DELAY,
	   अणु 0x000007d0, 0x0000044c, 0x00000898 पूर्ण पूर्ण,
	अणु AR5K_PHY_FRAME_CTL_5211,
	   अणु 0xf7b81000, 0xf7b80d00, 0xf7b81000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCKTXCTL,
	   अणु 0x00000000, 0x00000000, 0x00000000 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_CROSSCORR,
	   अणु 0xd6be6788, 0xd03e6788, 0xd03e6788 पूर्ण पूर्ण,
	अणु AR5K_PHY_GAIN_2GHZ,
	   अणु 0x00000140, 0x0052c140, 0x0052c140 पूर्ण पूर्ण,
	अणु AR5K_PHY_CCK_RX_CTL_4,
	   अणु 0x1883800a, 0x1863800a, 0x1883800a पूर्ण पूर्ण,
	अणु 0xa324,
	   अणु 0xa7cfa7cf, 0xa7cfa7cf, 0xa7cfa7cf पूर्ण पूर्ण,
	अणु 0xa328,
	   अणु 0xa7cfa7cf, 0xa7cfa7cf, 0xa7cfa7cf पूर्ण पूर्ण,
	अणु 0xa32c,
	   अणु 0xa7cfa7cf, 0xa7cfa7cf, 0xa7cfa7cf पूर्ण पूर्ण,
	अणु 0xa330,
	   अणु 0xa7cfa7cf, 0xa7cfa7cf, 0xa7cfa7cf पूर्ण पूर्ण,
	अणु 0xa334,
	   अणु 0xa7cfa7cf, 0xa7cfa7cf, 0xa7cfa7cf पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ath5k_ini rf2425_ini_common_end[] = अणु
	अणु AR5K_DCU_FP,		0x000003e0 पूर्ण,
	अणु AR5K_SEQ_MASK,	0x0000000f पूर्ण,
	अणु 0x809c,		0x00000000 पूर्ण,
	अणु 0x80a0,		0x00000000 पूर्ण,
	अणु AR5K_MIC_QOS_CTL,	0x00000000 पूर्ण,
	अणु AR5K_MIC_QOS_SEL,	0x00000000 पूर्ण,
	अणु AR5K_MISC_MODE,	0x00000000 पूर्ण,
	अणु AR5K_OFDM_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_CCK_FIL_CNT,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT1_MASK, 0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2,	0x00000000 पूर्ण,
	अणु AR5K_PHYERR_CNT2_MASK, 0x00000000 पूर्ण,
	अणु AR5K_TSF_THRES,	0x00000000 पूर्ण,
	अणु 0x8140,		0x800003f9 पूर्ण,
	अणु 0x8144,		0x00000000 पूर्ण,
	अणु AR5K_PHY_AGC,		0x00000000 पूर्ण,
	अणु AR5K_PHY_ADC_CTL,	0x0000a000 पूर्ण,
	अणु 0x983c,		0x00200400 पूर्ण,
	अणु AR5K_PHY_GAIN_OFFSET, 0x1284233c पूर्ण,
	अणु AR5K_PHY_SCR,		0x0000001f पूर्ण,
	अणु AR5K_PHY_SLMT,	0x00000080 पूर्ण,
	अणु AR5K_PHY_SCAL,	0x0000000e पूर्ण,
	अणु 0x9958,		0x00081fff पूर्ण,
	अणु AR5K_PHY_TIMING_7,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TIMING_8,	0x02800000 पूर्ण,
	अणु AR5K_PHY_TIMING_11,	0x00000000 पूर्ण,
	अणु 0x99dc,		0xfebadbe8 पूर्ण,
	अणु AR5K_PHY_HEAVY_CLIP_ENABLE, 0x00000000 पूर्ण,
	अणु 0x99e4,		0xaaaaaaaa पूर्ण,
	अणु 0x99e8,		0x3c466478 पूर्ण,
	अणु 0x99ec,		0x000000aa पूर्ण,
	अणु AR5K_PHY_SCLOCK,	0x0000000c पूर्ण,
	अणु AR5K_PHY_SDELAY,	0x000000ff पूर्ण,
	अणु AR5K_PHY_SPENDING,	0x00000014 पूर्ण,
	अणु AR5K_PHY_DAG_CCK_CTL,	0x000009b5 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE3, 0x20202020 पूर्ण,
	अणु AR5K_PHY_TXPOWER_RATE4, 0x20202020 पूर्ण,
	अणु 0xa23c,		0x93c889af पूर्ण,
	अणु AR5K_PHY_FAST_ADC,	0x00000001 पूर्ण,
	अणु 0xa250,		0x0000a000 पूर्ण,
	अणु AR5K_PHY_BLUETOOTH,	0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG1,	0x0cc75380 पूर्ण,
	अणु 0xa25c,		0x0f0f0f01 पूर्ण,
	अणु 0xa260,		0x5f690f01 पूर्ण,
	अणु 0xa264,		0x00418a11 पूर्ण,
	अणु 0xa268,		0x00000000 पूर्ण,
	अणु AR5K_PHY_TPC_RG5,	0x0c30c166 पूर्ण,
	अणु 0xa270, 0x00820820 पूर्ण,
	अणु 0xa274, 0x081a3caa पूर्ण,
	अणु 0xa278, 0x1ce739ce पूर्ण,
	अणु 0xa27c, 0x051701ce पूर्ण,
	अणु 0xa300, 0x16010000 पूर्ण,
	अणु 0xa304, 0x2c032402 पूर्ण,
	अणु 0xa308, 0x48433e42 पूर्ण,
	अणु 0xa30c, 0x5a0f500b पूर्ण,
	अणु 0xa310, 0x6c4b624a पूर्ण,
	अणु 0xa314, 0x7e8b748a पूर्ण,
	अणु 0xa318, 0x96cf8ccb पूर्ण,
	अणु 0xa31c, 0xa34f9d0f पूर्ण,
	अणु 0xa320, 0xa7cfa58f पूर्ण,
	अणु 0xa348, 0x3fffffff पूर्ण,
	अणु 0xa34c, 0x3fffffff पूर्ण,
	अणु 0xa350, 0x3fffffff पूर्ण,
	अणु 0xa354, 0x0003ffff पूर्ण,
	अणु 0xa358, 0x79a8aa1f पूर्ण,
	अणु 0xa35c, 0x066c420f पूर्ण,
	अणु 0xa360, 0x0f282207 पूर्ण,
	अणु 0xa364, 0x17601685 पूर्ण,
	अणु 0xa368, 0x1f801104 पूर्ण,
	अणु 0xa36c, 0x37a00c03 पूर्ण,
	अणु 0xa370, 0x3fc40883 पूर्ण,
	अणु 0xa374, 0x57c00803 पूर्ण,
	अणु 0xa378, 0x5fd80682 पूर्ण,
	अणु 0xa37c, 0x7fe00482 पूर्ण,
	अणु 0xa380, 0x7f3c7bba पूर्ण,
	अणु 0xa384, 0xf3307ff0 पूर्ण,
पूर्ण;

/*
 * Initial BaseBand Gain settings क्रम RF5111/5112 (AR5210 comes with
 * RF5110 only so initial BB Gain settings are included in AR5K_AR5210_INI)
 */

/* RF5111 Initial BaseBand Gain settings */
अटल स्थिर काष्ठा ath5k_ini rf5111_ini_bbgain[] = अणु
	अणु AR5K_BB_GAIN(0), 0x00000000 पूर्ण,
	अणु AR5K_BB_GAIN(1), 0x00000020 पूर्ण,
	अणु AR5K_BB_GAIN(2), 0x00000010 पूर्ण,
	अणु AR5K_BB_GAIN(3), 0x00000030 पूर्ण,
	अणु AR5K_BB_GAIN(4), 0x00000008 पूर्ण,
	अणु AR5K_BB_GAIN(5), 0x00000028 पूर्ण,
	अणु AR5K_BB_GAIN(6), 0x00000004 पूर्ण,
	अणु AR5K_BB_GAIN(7), 0x00000024 पूर्ण,
	अणु AR5K_BB_GAIN(8), 0x00000014 पूर्ण,
	अणु AR5K_BB_GAIN(9), 0x00000034 पूर्ण,
	अणु AR5K_BB_GAIN(10), 0x0000000c पूर्ण,
	अणु AR5K_BB_GAIN(11), 0x0000002c पूर्ण,
	अणु AR5K_BB_GAIN(12), 0x00000002 पूर्ण,
	अणु AR5K_BB_GAIN(13), 0x00000022 पूर्ण,
	अणु AR5K_BB_GAIN(14), 0x00000012 पूर्ण,
	अणु AR5K_BB_GAIN(15), 0x00000032 पूर्ण,
	अणु AR5K_BB_GAIN(16), 0x0000000a पूर्ण,
	अणु AR5K_BB_GAIN(17), 0x0000002a पूर्ण,
	अणु AR5K_BB_GAIN(18), 0x00000006 पूर्ण,
	अणु AR5K_BB_GAIN(19), 0x00000026 पूर्ण,
	अणु AR5K_BB_GAIN(20), 0x00000016 पूर्ण,
	अणु AR5K_BB_GAIN(21), 0x00000036 पूर्ण,
	अणु AR5K_BB_GAIN(22), 0x0000000e पूर्ण,
	अणु AR5K_BB_GAIN(23), 0x0000002e पूर्ण,
	अणु AR5K_BB_GAIN(24), 0x00000001 पूर्ण,
	अणु AR5K_BB_GAIN(25), 0x00000021 पूर्ण,
	अणु AR5K_BB_GAIN(26), 0x00000011 पूर्ण,
	अणु AR5K_BB_GAIN(27), 0x00000031 पूर्ण,
	अणु AR5K_BB_GAIN(28), 0x00000009 पूर्ण,
	अणु AR5K_BB_GAIN(29), 0x00000029 पूर्ण,
	अणु AR5K_BB_GAIN(30), 0x00000005 पूर्ण,
	अणु AR5K_BB_GAIN(31), 0x00000025 पूर्ण,
	अणु AR5K_BB_GAIN(32), 0x00000015 पूर्ण,
	अणु AR5K_BB_GAIN(33), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(34), 0x0000000d पूर्ण,
	अणु AR5K_BB_GAIN(35), 0x0000002d पूर्ण,
	अणु AR5K_BB_GAIN(36), 0x00000003 पूर्ण,
	अणु AR5K_BB_GAIN(37), 0x00000023 पूर्ण,
	अणु AR5K_BB_GAIN(38), 0x00000013 पूर्ण,
	अणु AR5K_BB_GAIN(39), 0x00000033 पूर्ण,
	अणु AR5K_BB_GAIN(40), 0x0000000b पूर्ण,
	अणु AR5K_BB_GAIN(41), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(42), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(43), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(44), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(45), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(46), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(47), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(48), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(49), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(50), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(51), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(52), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(53), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(54), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(55), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(56), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(57), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(58), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(59), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(60), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(61), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(62), 0x00000002 पूर्ण,
	अणु AR5K_BB_GAIN(63), 0x00000016 पूर्ण,
पूर्ण;

/* RF5112 Initial BaseBand Gain settings (Same क्रम RF5413/5414+) */
अटल स्थिर काष्ठा ath5k_ini rf5112_ini_bbgain[] = अणु
	अणु AR5K_BB_GAIN(0), 0x00000000 पूर्ण,
	अणु AR5K_BB_GAIN(1), 0x00000001 पूर्ण,
	अणु AR5K_BB_GAIN(2), 0x00000002 पूर्ण,
	अणु AR5K_BB_GAIN(3), 0x00000003 पूर्ण,
	अणु AR5K_BB_GAIN(4), 0x00000004 पूर्ण,
	अणु AR5K_BB_GAIN(5), 0x00000005 पूर्ण,
	अणु AR5K_BB_GAIN(6), 0x00000008 पूर्ण,
	अणु AR5K_BB_GAIN(7), 0x00000009 पूर्ण,
	अणु AR5K_BB_GAIN(8), 0x0000000a पूर्ण,
	अणु AR5K_BB_GAIN(9), 0x0000000b पूर्ण,
	अणु AR5K_BB_GAIN(10), 0x0000000c पूर्ण,
	अणु AR5K_BB_GAIN(11), 0x0000000d पूर्ण,
	अणु AR5K_BB_GAIN(12), 0x00000010 पूर्ण,
	अणु AR5K_BB_GAIN(13), 0x00000011 पूर्ण,
	अणु AR5K_BB_GAIN(14), 0x00000012 पूर्ण,
	अणु AR5K_BB_GAIN(15), 0x00000013 पूर्ण,
	अणु AR5K_BB_GAIN(16), 0x00000014 पूर्ण,
	अणु AR5K_BB_GAIN(17), 0x00000015 पूर्ण,
	अणु AR5K_BB_GAIN(18), 0x00000018 पूर्ण,
	अणु AR5K_BB_GAIN(19), 0x00000019 पूर्ण,
	अणु AR5K_BB_GAIN(20), 0x0000001a पूर्ण,
	अणु AR5K_BB_GAIN(21), 0x0000001b पूर्ण,
	अणु AR5K_BB_GAIN(22), 0x0000001c पूर्ण,
	अणु AR5K_BB_GAIN(23), 0x0000001d पूर्ण,
	अणु AR5K_BB_GAIN(24), 0x00000020 पूर्ण,
	अणु AR5K_BB_GAIN(25), 0x00000021 पूर्ण,
	अणु AR5K_BB_GAIN(26), 0x00000022 पूर्ण,
	अणु AR5K_BB_GAIN(27), 0x00000023 पूर्ण,
	अणु AR5K_BB_GAIN(28), 0x00000024 पूर्ण,
	अणु AR5K_BB_GAIN(29), 0x00000025 पूर्ण,
	अणु AR5K_BB_GAIN(30), 0x00000028 पूर्ण,
	अणु AR5K_BB_GAIN(31), 0x00000029 पूर्ण,
	अणु AR5K_BB_GAIN(32), 0x0000002a पूर्ण,
	अणु AR5K_BB_GAIN(33), 0x0000002b पूर्ण,
	अणु AR5K_BB_GAIN(34), 0x0000002c पूर्ण,
	अणु AR5K_BB_GAIN(35), 0x0000002d पूर्ण,
	अणु AR5K_BB_GAIN(36), 0x00000030 पूर्ण,
	अणु AR5K_BB_GAIN(37), 0x00000031 पूर्ण,
	अणु AR5K_BB_GAIN(38), 0x00000032 पूर्ण,
	अणु AR5K_BB_GAIN(39), 0x00000033 पूर्ण,
	अणु AR5K_BB_GAIN(40), 0x00000034 पूर्ण,
	अणु AR5K_BB_GAIN(41), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(42), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(43), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(44), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(45), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(46), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(47), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(48), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(49), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(50), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(51), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(52), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(53), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(54), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(55), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(56), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(57), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(58), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(59), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(60), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(61), 0x00000035 पूर्ण,
	अणु AR5K_BB_GAIN(62), 0x00000010 पूर्ण,
	अणु AR5K_BB_GAIN(63), 0x0000001a पूर्ण,
पूर्ण;


/**
 * ath5k_hw_ini_रेजिस्टरs() - Write initial रेजिस्टर dump common क्रम all modes
 * @ah: The &काष्ठा ath5k_hw
 * @size: Dump size
 * @ini_regs: The array of &काष्ठा ath5k_ini
 * @skip_pcu: Skip PCU रेजिस्टरs
 */
अटल व्योम
ath5k_hw_ini_रेजिस्टरs(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक size,
		स्थिर काष्ठा ath5k_ini *ini_regs, bool skip_pcu)
अणु
	अचिन्हित पूर्णांक i;

	/* Write initial रेजिस्टरs */
	क्रम (i = 0; i < size; i++) अणु
		/* Skip PCU रेजिस्टरs अगर
		 * requested */
		अगर (skip_pcu &&
				ini_regs[i].ini_रेजिस्टर >= AR5K_PCU_MIN &&
				ini_regs[i].ini_रेजिस्टर <= AR5K_PCU_MAX)
			जारी;

		चयन (ini_regs[i].ini_mode) अणु
		हाल AR5K_INI_READ:
			/* Cleared on पढ़ो */
			ath5k_hw_reg_पढ़ो(ah, ini_regs[i].ini_रेजिस्टर);
			अवरोध;
		हाल AR5K_INI_WRITE:
		शेष:
			AR5K_REG_WAIT(i);
			ath5k_hw_reg_ग_लिखो(ah, ini_regs[i].ini_value,
					ini_regs[i].ini_रेजिस्टर);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ath5k_hw_ini_mode_रेजिस्टरs() - Write initial mode-specअगरic रेजिस्टर dump
 * @ah: The &काष्ठा ath5k_hw
 * @size: Dump size
 * @ini_mode: The array of &काष्ठा ath5k_ini_mode
 * @mode: One of क्रमागत ath5k_driver_mode
 */
अटल व्योम
ath5k_hw_ini_mode_रेजिस्टरs(काष्ठा ath5k_hw *ah,
		अचिन्हित पूर्णांक size, स्थिर काष्ठा ath5k_ini_mode *ini_mode,
		u8 mode)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_ग_लिखो(ah, ini_mode[i].mode_value[mode],
			(u32)ini_mode[i].mode_रेजिस्टर);
	पूर्ण

पूर्ण

/**
 * ath5k_hw_ग_लिखो_initvals() - Write initial chip-specअगरic रेजिस्टर dump
 * @ah: The &काष्ठा ath5k_hw
 * @mode: One of क्रमागत ath5k_driver_mode
 * @skip_pcu: Skip PCU रेजिस्टरs
 *
 * Write initial chip-specअगरic रेजिस्टर dump, to get the chipset on a
 * clean and पढ़ोy-to-work state after warm reset.
 */
पूर्णांक
ath5k_hw_ग_लिखो_initvals(काष्ठा ath5k_hw *ah, u8 mode, bool skip_pcu)
अणु
	/*
	 * Write initial रेजिस्टर settings
	 */

	/* For AR5212 and compatible */
	अगर (ah->ah_version == AR5K_AR5212) अणु

		/* First set of mode-specअगरic settings */
		ath5k_hw_ini_mode_रेजिस्टरs(ah,
			ARRAY_SIZE(ar5212_ini_mode_start),
			ar5212_ini_mode_start, mode);

		/*
		 * Write initial settings common क्रम all modes
		 */
		ath5k_hw_ini_रेजिस्टरs(ah, ARRAY_SIZE(ar5212_ini_common_start),
				ar5212_ini_common_start, skip_pcu);

		/* Second set of mode-specअगरic settings */
		चयन (ah->ah_radio) अणु
		हाल AR5K_RF5111:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5111_ini_mode_end),
					rf5111_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5111_ini_common_end),
					rf5111_ini_common_end, skip_pcu);

			/* Baseband gain table */
			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5111_ini_bbgain),
					rf5111_ini_bbgain, skip_pcu);

			अवरोध;
		हाल AR5K_RF5112:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_mode_end),
					rf5112_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_common_end),
					rf5112_ini_common_end, skip_pcu);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_bbgain),
					rf5112_ini_bbgain, skip_pcu);

			अवरोध;
		हाल AR5K_RF5413:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5413_ini_mode_end),
					rf5413_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5413_ini_common_end),
					rf5413_ini_common_end, skip_pcu);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_bbgain),
					rf5112_ini_bbgain, skip_pcu);

			अवरोध;
		हाल AR5K_RF2316:
		हाल AR5K_RF2413:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2413_ini_mode_end),
					rf2413_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2413_ini_common_end),
					rf2413_ini_common_end, skip_pcu);

			/* Override settings from rf2413_ini_common_end */
			अगर (ah->ah_radio == AR5K_RF2316) अणु
				ath5k_hw_reg_ग_लिखो(ah, 0x00004000,
							AR5K_PHY_AGC);
				ath5k_hw_reg_ग_लिखो(ah, 0x081b7caa,
							0xa274);
			पूर्ण

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_bbgain),
					rf5112_ini_bbgain, skip_pcu);
			अवरोध;
		हाल AR5K_RF2317:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2413_ini_mode_end),
					rf2413_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2425_ini_common_end),
					rf2425_ini_common_end, skip_pcu);

			/* Override settings from rf2413_ini_mode_end */
			ath5k_hw_reg_ग_लिखो(ah, 0x00180a65, AR5K_PHY_GAIN);

			/* Override settings from rf2413_ini_common_end */
			ath5k_hw_reg_ग_लिखो(ah, 0x00004000, AR5K_PHY_AGC);
			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TPC_RG5,
				AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP, 0xa);
			ath5k_hw_reg_ग_लिखो(ah, 0x800000a8, 0x8140);
			ath5k_hw_reg_ग_लिखो(ah, 0x000000ff, 0x9958);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_bbgain),
					rf5112_ini_bbgain, skip_pcu);
			अवरोध;
		हाल AR5K_RF2425:

			ath5k_hw_ini_mode_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2425_ini_mode_end),
					rf2425_ini_mode_end, mode);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf2425_ini_common_end),
					rf2425_ini_common_end, skip_pcu);

			ath5k_hw_ini_रेजिस्टरs(ah,
					ARRAY_SIZE(rf5112_ini_bbgain),
					rf5112_ini_bbgain, skip_pcu);
			अवरोध;
		शेष:
			वापस -EINVAL;

		पूर्ण

	/* For AR5211 */
	पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5211) अणु

		/* AR5K_MODE_11B */
		अगर (mode > 2) अणु
			ATH5K_ERR(ah, "unsupported channel mode: %d\n", mode);
			वापस -EINVAL;
		पूर्ण

		/* Mode-specअगरic settings */
		ath5k_hw_ini_mode_रेजिस्टरs(ah, ARRAY_SIZE(ar5211_ini_mode),
				ar5211_ini_mode, mode);

		/*
		 * Write initial settings common क्रम all modes
		 */
		ath5k_hw_ini_रेजिस्टरs(ah, ARRAY_SIZE(ar5211_ini),
				ar5211_ini, skip_pcu);

		/* AR5211 only comes with 5111 */

		/* Baseband gain table */
		ath5k_hw_ini_रेजिस्टरs(ah, ARRAY_SIZE(rf5111_ini_bbgain),
				rf5111_ini_bbgain, skip_pcu);
	/* For AR5210 (क्रम mode settings check out ath5k_hw_reset_tx_queue) */
	पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5210) अणु
		ath5k_hw_ini_रेजिस्टरs(ah, ARRAY_SIZE(ar5210_ini),
				ar5210_ini, skip_pcu);
	पूर्ण

	वापस 0;
पूर्ण
