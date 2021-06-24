<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

  Copyright(c) 2003 - 2006 Intel Corporation. All rights reserved.

  802.11 status code portion of this file from ethereal-0.10.6:
    Copyright 2000, Axis Communications AB
    Ethereal - Network traffic analyzer
    By Gerald Combs <gerald@ethereal.com>
    Copyright 1998 Gerald Combs


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <net/cfg80211-wext.h>
#समावेश "ipw2200.h"
#समावेश "ipw.h"


#अगर_अघोषित KBUILD_EXTMOD
#घोषणा VK "k"
#अन्यथा
#घोषणा VK
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_DEBUG
#घोषणा VD "d"
#अन्यथा
#घोषणा VD
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_MONITOR
#घोषणा VM "m"
#अन्यथा
#घोषणा VM
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
#घोषणा VP "p"
#अन्यथा
#घोषणा VP
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_RADIOTAP
#घोषणा VR "r"
#अन्यथा
#घोषणा VR
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_QOS
#घोषणा VQ "q"
#अन्यथा
#घोषणा VQ
#पूर्ण_अगर

#घोषणा IPW2200_VERSION "1.2.2" VK VD VM VP VR VQ
#घोषणा DRV_DESCRIPTION	"Intel(R) PRO/Wireless 2200/2915 Network Driver"
#घोषणा DRV_COPYRIGHT	"Copyright(c) 2003-2006 Intel Corporation"
#घोषणा DRV_VERSION     IPW2200_VERSION

#घोषणा ETH_P_80211_STATS (ETH_P_80211_RAW + 1)

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_COPYRIGHT);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("ipw2200-ibss.fw");
#अगर_घोषित CONFIG_IPW2200_MONITOR
MODULE_FIRMWARE("ipw2200-sniffer.fw");
#पूर्ण_अगर
MODULE_FIRMWARE("ipw2200-bss.fw");

अटल पूर्णांक cmdlog = 0;
अटल पूर्णांक debug = 0;
अटल पूर्णांक शेष_channel = 0;
अटल पूर्णांक network_mode = 0;

अटल u32 ipw_debug_level;
अटल पूर्णांक associate;
अटल पूर्णांक स्वतः_create = 1;
अटल पूर्णांक led_support = 1;
अटल पूर्णांक disable = 0;
अटल पूर्णांक bt_coexist = 0;
अटल पूर्णांक hwcrypto = 0;
अटल पूर्णांक roaming = 1;
अटल स्थिर अक्षर ipw_modes[] = अणु
	'a', 'b', 'g', '?'
पूर्ण;
अटल पूर्णांक antenna = CFG_SYS_ANTENNA_BOTH;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
अटल पूर्णांक rtap_अगरace = 0;     /* def: 0 -- करो not create rtap पूर्णांकerface */
#पूर्ण_अगर

अटल काष्ठा ieee80211_rate ipw2200_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60 पूर्ण,
	अणु .bitrate = 90 पूर्ण,
	अणु .bitrate = 120 पूर्ण,
	अणु .bitrate = 180 पूर्ण,
	अणु .bitrate = 240 पूर्ण,
	अणु .bitrate = 360 पूर्ण,
	अणु .bitrate = 480 पूर्ण,
	अणु .bitrate = 540 पूर्ण
पूर्ण;

#घोषणा ipw2200_a_rates		(ipw2200_rates + 4)
#घोषणा ipw2200_num_a_rates	8
#घोषणा ipw2200_bg_rates	(ipw2200_rates + 0)
#घोषणा ipw2200_num_bg_rates	12

/* Ugly macro to convert literal channel numbers पूर्णांकo their mhz equivalents
 * There are certianly some conditions that will अवरोध this (like feeding it '30')
 * but they shouldn't arise since nothing talks on channel 30. */
#घोषणा ieee80211chan2mhz(x) \
	(((x) <= 14) ? \
	(((x) == 14) ? 2484 : ((x) * 5) + 2407) : \
	((x) + 1000) * 5)

#अगर_घोषित CONFIG_IPW2200_QOS
अटल पूर्णांक qos_enable = 0;
अटल पूर्णांक qos_burst_enable = 0;
अटल पूर्णांक qos_no_ack_mask = 0;
अटल पूर्णांक burst_duration_CCK = 0;
अटल पूर्णांक burst_duration_OFDM = 0;

अटल काष्ठा libipw_qos_parameters def_qos_parameters_OFDM = अणु
	अणुQOS_TX0_CW_MIN_OFDM, QOS_TX1_CW_MIN_OFDM, QOS_TX2_CW_MIN_OFDM,
	 QOS_TX3_CW_MIN_OFDMपूर्ण,
	अणुQOS_TX0_CW_MAX_OFDM, QOS_TX1_CW_MAX_OFDM, QOS_TX2_CW_MAX_OFDM,
	 QOS_TX3_CW_MAX_OFDMपूर्ण,
	अणुQOS_TX0_AIFS, QOS_TX1_AIFS, QOS_TX2_AIFS, QOS_TX3_AIFSपूर्ण,
	अणुQOS_TX0_ACM, QOS_TX1_ACM, QOS_TX2_ACM, QOS_TX3_ACMपूर्ण,
	अणुQOS_TX0_TXOP_LIMIT_OFDM, QOS_TX1_TXOP_LIMIT_OFDM,
	 QOS_TX2_TXOP_LIMIT_OFDM, QOS_TX3_TXOP_LIMIT_OFDMपूर्ण
पूर्ण;

अटल काष्ठा libipw_qos_parameters def_qos_parameters_CCK = अणु
	अणुQOS_TX0_CW_MIN_CCK, QOS_TX1_CW_MIN_CCK, QOS_TX2_CW_MIN_CCK,
	 QOS_TX3_CW_MIN_CCKपूर्ण,
	अणुQOS_TX0_CW_MAX_CCK, QOS_TX1_CW_MAX_CCK, QOS_TX2_CW_MAX_CCK,
	 QOS_TX3_CW_MAX_CCKपूर्ण,
	अणुQOS_TX0_AIFS, QOS_TX1_AIFS, QOS_TX2_AIFS, QOS_TX3_AIFSपूर्ण,
	अणुQOS_TX0_ACM, QOS_TX1_ACM, QOS_TX2_ACM, QOS_TX3_ACMपूर्ण,
	अणुQOS_TX0_TXOP_LIMIT_CCK, QOS_TX1_TXOP_LIMIT_CCK, QOS_TX2_TXOP_LIMIT_CCK,
	 QOS_TX3_TXOP_LIMIT_CCKपूर्ण
पूर्ण;

अटल काष्ठा libipw_qos_parameters def_parameters_OFDM = अणु
	अणुDEF_TX0_CW_MIN_OFDM, DEF_TX1_CW_MIN_OFDM, DEF_TX2_CW_MIN_OFDM,
	 DEF_TX3_CW_MIN_OFDMपूर्ण,
	अणुDEF_TX0_CW_MAX_OFDM, DEF_TX1_CW_MAX_OFDM, DEF_TX2_CW_MAX_OFDM,
	 DEF_TX3_CW_MAX_OFDMपूर्ण,
	अणुDEF_TX0_AIFS, DEF_TX1_AIFS, DEF_TX2_AIFS, DEF_TX3_AIFSपूर्ण,
	अणुDEF_TX0_ACM, DEF_TX1_ACM, DEF_TX2_ACM, DEF_TX3_ACMपूर्ण,
	अणुDEF_TX0_TXOP_LIMIT_OFDM, DEF_TX1_TXOP_LIMIT_OFDM,
	 DEF_TX2_TXOP_LIMIT_OFDM, DEF_TX3_TXOP_LIMIT_OFDMपूर्ण
पूर्ण;

अटल काष्ठा libipw_qos_parameters def_parameters_CCK = अणु
	अणुDEF_TX0_CW_MIN_CCK, DEF_TX1_CW_MIN_CCK, DEF_TX2_CW_MIN_CCK,
	 DEF_TX3_CW_MIN_CCKपूर्ण,
	अणुDEF_TX0_CW_MAX_CCK, DEF_TX1_CW_MAX_CCK, DEF_TX2_CW_MAX_CCK,
	 DEF_TX3_CW_MAX_CCKपूर्ण,
	अणुDEF_TX0_AIFS, DEF_TX1_AIFS, DEF_TX2_AIFS, DEF_TX3_AIFSपूर्ण,
	अणुDEF_TX0_ACM, DEF_TX1_ACM, DEF_TX2_ACM, DEF_TX3_ACMपूर्ण,
	अणुDEF_TX0_TXOP_LIMIT_CCK, DEF_TX1_TXOP_LIMIT_CCK, DEF_TX2_TXOP_LIMIT_CCK,
	 DEF_TX3_TXOP_LIMIT_CCKपूर्ण
पूर्ण;

अटल u8 qos_oui[QOS_OUI_LEN] = अणु 0x00, 0x50, 0xF2 पूर्ण;

अटल पूर्णांक from_priority_to_tx_queue[] = अणु
	IPW_TX_QUEUE_1, IPW_TX_QUEUE_2, IPW_TX_QUEUE_2, IPW_TX_QUEUE_1,
	IPW_TX_QUEUE_3, IPW_TX_QUEUE_3, IPW_TX_QUEUE_4, IPW_TX_QUEUE_4
पूर्ण;

अटल u32 ipw_qos_get_burst_duration(काष्ठा ipw_priv *priv);

अटल पूर्णांक ipw_send_qos_params_command(काष्ठा ipw_priv *priv, काष्ठा libipw_qos_parameters
				       *qos_param);
अटल पूर्णांक ipw_send_qos_info_command(काष्ठा ipw_priv *priv, काष्ठा libipw_qos_inक्रमmation_element
				     *qos_param);
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

अटल काष्ठा iw_statistics *ipw_get_wireless_stats(काष्ठा net_device *dev);
अटल व्योम ipw_हटाओ_current_network(काष्ठा ipw_priv *priv);
अटल व्योम ipw_rx(काष्ठा ipw_priv *priv);
अटल पूर्णांक ipw_queue_tx_reclaim(काष्ठा ipw_priv *priv,
				काष्ठा clx2_tx_queue *txq, पूर्णांक qindex);
अटल पूर्णांक ipw_queue_reset(काष्ठा ipw_priv *priv);

अटल पूर्णांक ipw_queue_tx_hcmd(काष्ठा ipw_priv *priv, पूर्णांक hcmd, व्योम *buf,
			     पूर्णांक len, पूर्णांक sync);

अटल व्योम ipw_tx_queue_मुक्त(काष्ठा ipw_priv *);

अटल काष्ठा ipw_rx_queue *ipw_rx_queue_alloc(काष्ठा ipw_priv *);
अटल व्योम ipw_rx_queue_मुक्त(काष्ठा ipw_priv *, काष्ठा ipw_rx_queue *);
अटल व्योम ipw_rx_queue_replenish(व्योम *);
अटल पूर्णांक ipw_up(काष्ठा ipw_priv *);
अटल व्योम ipw_bg_up(काष्ठा work_काष्ठा *work);
अटल व्योम ipw_करोwn(काष्ठा ipw_priv *);
अटल व्योम ipw_bg_करोwn(काष्ठा work_काष्ठा *work);
अटल पूर्णांक ipw_config(काष्ठा ipw_priv *);
अटल पूर्णांक init_supported_rates(काष्ठा ipw_priv *priv,
				काष्ठा ipw_supported_rates *prates);
अटल व्योम ipw_set_hwcrypto_keys(काष्ठा ipw_priv *);
अटल व्योम ipw_send_wep_keys(काष्ठा ipw_priv *, पूर्णांक);

अटल पूर्णांक snprपूर्णांक_line(अक्षर *buf, माप_प्रकार count,
			स्थिर u8 * data, u32 len, u32 ofs)
अणु
	पूर्णांक out, i, j, l;
	अक्षर c;

	out = scnम_लिखो(buf, count, "%08X", ofs);

	क्रम (l = 0, i = 0; i < 2; i++) अणु
		out += scnम_लिखो(buf + out, count - out, " ");
		क्रम (j = 0; j < 8 && l < len; j++, l++)
			out += scnम_लिखो(buf + out, count - out, "%02X ",
					data[(i * 8 + j)]);
		क्रम (; j < 8; j++)
			out += scnम_लिखो(buf + out, count - out, "   ");
	पूर्ण

	out += scnम_लिखो(buf + out, count - out, " ");
	क्रम (l = 0, i = 0; i < 2; i++) अणु
		out += scnम_लिखो(buf + out, count - out, " ");
		क्रम (j = 0; j < 8 && l < len; j++, l++) अणु
			c = data[(i * 8 + j)];
			अगर (!isascii(c) || !है_छाप(c))
				c = '.';

			out += scnम_लिखो(buf + out, count - out, "%c", c);
		पूर्ण

		क्रम (; j < 8; j++)
			out += scnम_लिखो(buf + out, count - out, " ");
	पूर्ण

	वापस out;
पूर्ण

अटल व्योम prपूर्णांकk_buf(पूर्णांक level, स्थिर u8 * data, u32 len)
अणु
	अक्षर line[81];
	u32 ofs = 0;
	अगर (!(ipw_debug_level & level))
		वापस;

	जबतक (len) अणु
		snprपूर्णांक_line(line, माप(line), &data[ofs],
			     min(len, 16U), ofs);
		prपूर्णांकk(KERN_DEBUG "%s\n", line);
		ofs += 16;
		len -= min(len, 16U);
	पूर्ण
पूर्ण

अटल पूर्णांक snprपूर्णांकk_buf(u8 * output, माप_प्रकार size, स्थिर u8 * data, माप_प्रकार len)
अणु
	माप_प्रकार out = size;
	u32 ofs = 0;
	पूर्णांक total = 0;

	जबतक (size && len) अणु
		out = snprपूर्णांक_line(output, size, &data[ofs],
				   min_t(माप_प्रकार, len, 16U), ofs);

		ofs += 16;
		output += out;
		size -= out;
		len -= min_t(माप_प्रकार, len, 16U);
		total += out;
	पूर्ण
	वापस total;
पूर्ण

/* alias क्रम 32-bit indirect पढ़ो (क्रम SRAM/reg above 4K), with debug wrapper */
अटल u32 _ipw_पढ़ो_reg32(काष्ठा ipw_priv *priv, u32 reg);
#घोषणा ipw_पढ़ो_reg32(a, b) _ipw_पढ़ो_reg32(a, b)

/* alias क्रम 8-bit indirect पढ़ो (क्रम SRAM/reg above 4K), with debug wrapper */
अटल u8 _ipw_पढ़ो_reg8(काष्ठा ipw_priv *ipw, u32 reg);
#घोषणा ipw_पढ़ो_reg8(a, b) _ipw_पढ़ो_reg8(a, b)

/* 8-bit indirect ग_लिखो (क्रम SRAM/reg above 4K), with debug wrapper */
अटल व्योम _ipw_ग_लिखो_reg8(काष्ठा ipw_priv *priv, u32 reg, u8 value);
अटल अंतरभूत व्योम ipw_ग_लिखो_reg8(काष्ठा ipw_priv *a, u32 b, u8 c)
अणु
	IPW_DEBUG_IO("%s %d: write_indirect8(0x%08X, 0x%08X)\n", __खाता__,
		     __LINE__, (u32) (b), (u32) (c));
	_ipw_ग_लिखो_reg8(a, b, c);
पूर्ण

/* 16-bit indirect ग_लिखो (क्रम SRAM/reg above 4K), with debug wrapper */
अटल व्योम _ipw_ग_लिखो_reg16(काष्ठा ipw_priv *priv, u32 reg, u16 value);
अटल अंतरभूत व्योम ipw_ग_लिखो_reg16(काष्ठा ipw_priv *a, u32 b, u16 c)
अणु
	IPW_DEBUG_IO("%s %d: write_indirect16(0x%08X, 0x%08X)\n", __खाता__,
		     __LINE__, (u32) (b), (u32) (c));
	_ipw_ग_लिखो_reg16(a, b, c);
पूर्ण

/* 32-bit indirect ग_लिखो (क्रम SRAM/reg above 4K), with debug wrapper */
अटल व्योम _ipw_ग_लिखो_reg32(काष्ठा ipw_priv *priv, u32 reg, u32 value);
अटल अंतरभूत व्योम ipw_ग_लिखो_reg32(काष्ठा ipw_priv *a, u32 b, u32 c)
अणु
	IPW_DEBUG_IO("%s %d: write_indirect32(0x%08X, 0x%08X)\n", __खाता__,
		     __LINE__, (u32) (b), (u32) (c));
	_ipw_ग_लिखो_reg32(a, b, c);
पूर्ण

/* 8-bit direct ग_लिखो (low 4K) */
अटल अंतरभूत व्योम _ipw_ग_लिखो8(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs,
		u8 val)
अणु
	ग_लिखोb(val, ipw->hw_base + ofs);
पूर्ण

/* 8-bit direct ग_लिखो (क्रम low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_ग_लिखो8(ipw, ofs, val) करो अणु \
	IPW_DEBUG_IO("%s %d: write_direct8(0x%08X, 0x%08X)\n", __खाता__, \
			__LINE__, (u32)(ofs), (u32)(val)); \
	_ipw_ग_लिखो8(ipw, ofs, val); \
पूर्ण जबतक (0)

/* 16-bit direct ग_लिखो (low 4K) */
अटल अंतरभूत व्योम _ipw_ग_लिखो16(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs,
		u16 val)
अणु
	ग_लिखोw(val, ipw->hw_base + ofs);
पूर्ण

/* 16-bit direct ग_लिखो (क्रम low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_ग_लिखो16(ipw, ofs, val) करो अणु \
	IPW_DEBUG_IO("%s %d: write_direct16(0x%08X, 0x%08X)\n", __खाता__, \
			__LINE__, (u32)(ofs), (u32)(val)); \
	_ipw_ग_लिखो16(ipw, ofs, val); \
पूर्ण जबतक (0)

/* 32-bit direct ग_लिखो (low 4K) */
अटल अंतरभूत व्योम _ipw_ग_लिखो32(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs,
		u32 val)
अणु
	ग_लिखोl(val, ipw->hw_base + ofs);
पूर्ण

/* 32-bit direct ग_लिखो (क्रम low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_ग_लिखो32(ipw, ofs, val) करो अणु \
	IPW_DEBUG_IO("%s %d: write_direct32(0x%08X, 0x%08X)\n", __खाता__, \
			__LINE__, (u32)(ofs), (u32)(val)); \
	_ipw_ग_लिखो32(ipw, ofs, val); \
पूर्ण जबतक (0)

/* 8-bit direct पढ़ो (low 4K) */
अटल अंतरभूत u8 _ipw_पढ़ो8(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs)
अणु
	वापस पढ़ोb(ipw->hw_base + ofs);
पूर्ण

/* alias to 8-bit direct पढ़ो (low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_पढ़ो8(ipw, ofs) (अणु \
	IPW_DEBUG_IO("%s %d: read_direct8(0x%08X)\n", __खाता__, __LINE__, \
			(u32)(ofs)); \
	_ipw_पढ़ो8(ipw, ofs); \
पूर्ण)

/* 16-bit direct पढ़ो (low 4K) */
अटल अंतरभूत u16 _ipw_पढ़ो16(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs)
अणु
	वापस पढ़ोw(ipw->hw_base + ofs);
पूर्ण

/* alias to 16-bit direct पढ़ो (low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_पढ़ो16(ipw, ofs) (अणु \
	IPW_DEBUG_IO("%s %d: read_direct16(0x%08X)\n", __खाता__, __LINE__, \
			(u32)(ofs)); \
	_ipw_पढ़ो16(ipw, ofs); \
पूर्ण)

/* 32-bit direct पढ़ो (low 4K) */
अटल अंतरभूत u32 _ipw_पढ़ो32(काष्ठा ipw_priv *ipw, अचिन्हित दीर्घ ofs)
अणु
	वापस पढ़ोl(ipw->hw_base + ofs);
पूर्ण

/* alias to 32-bit direct पढ़ो (low 4K of SRAM/regs), with debug wrapper */
#घोषणा ipw_पढ़ो32(ipw, ofs) (अणु \
	IPW_DEBUG_IO("%s %d: read_direct32(0x%08X)\n", __खाता__, __LINE__, \
			(u32)(ofs)); \
	_ipw_पढ़ो32(ipw, ofs); \
पूर्ण)

अटल व्योम _ipw_पढ़ो_indirect(काष्ठा ipw_priv *, u32, u8 *, पूर्णांक);
/* alias to multi-byte पढ़ो (SRAM/regs above 4K), with debug wrapper */
#घोषणा ipw_पढ़ो_indirect(a, b, c, d) (अणु \
	IPW_DEBUG_IO("%s %d: read_indirect(0x%08X) %u bytes\n", __खाता__, \
			__LINE__, (u32)(b), (u32)(d)); \
	_ipw_पढ़ो_indirect(a, b, c, d); \
पूर्ण)

/* alias to multi-byte पढ़ो (SRAM/regs above 4K), with debug wrapper */
अटल व्योम _ipw_ग_लिखो_indirect(काष्ठा ipw_priv *priv, u32 addr, u8 * data,
				पूर्णांक num);
#घोषणा ipw_ग_लिखो_indirect(a, b, c, d) करो अणु \
	IPW_DEBUG_IO("%s %d: write_indirect(0x%08X) %u bytes\n", __खाता__, \
			__LINE__, (u32)(b), (u32)(d)); \
	_ipw_ग_लिखो_indirect(a, b, c, d); \
पूर्ण जबतक (0)

/* 32-bit indirect ग_लिखो (above 4K) */
अटल व्योम _ipw_ग_लिखो_reg32(काष्ठा ipw_priv *priv, u32 reg, u32 value)
अणु
	IPW_DEBUG_IO(" %p : reg = 0x%8X : value = 0x%8X\n", priv, reg, value);
	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, reg);
	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_DATA, value);
पूर्ण

/* 8-bit indirect ग_लिखो (above 4K) */
अटल व्योम _ipw_ग_लिखो_reg8(काष्ठा ipw_priv *priv, u32 reg, u8 value)
अणु
	u32 aligned_addr = reg & IPW_INसूचीECT_ADDR_MASK;	/* dword align */
	u32 dअगर_len = reg - aligned_addr;

	IPW_DEBUG_IO(" reg = 0x%8X : value = 0x%8X\n", reg, value);
	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
	_ipw_ग_लिखो8(priv, IPW_INसूचीECT_DATA + dअगर_len, value);
पूर्ण

/* 16-bit indirect ग_लिखो (above 4K) */
अटल व्योम _ipw_ग_लिखो_reg16(काष्ठा ipw_priv *priv, u32 reg, u16 value)
अणु
	u32 aligned_addr = reg & IPW_INसूचीECT_ADDR_MASK;	/* dword align */
	u32 dअगर_len = (reg - aligned_addr) & (~0x1ul);

	IPW_DEBUG_IO(" reg = 0x%8X : value = 0x%8X\n", reg, value);
	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
	_ipw_ग_लिखो16(priv, IPW_INसूचीECT_DATA + dअगर_len, value);
पूर्ण

/* 8-bit indirect पढ़ो (above 4K) */
अटल u8 _ipw_पढ़ो_reg8(काष्ठा ipw_priv *priv, u32 reg)
अणु
	u32 word;
	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, reg & IPW_INसूचीECT_ADDR_MASK);
	IPW_DEBUG_IO(" reg = 0x%8X :\n", reg);
	word = _ipw_पढ़ो32(priv, IPW_INसूचीECT_DATA);
	वापस (word >> ((reg & 0x3) * 8)) & 0xff;
पूर्ण

/* 32-bit indirect पढ़ो (above 4K) */
अटल u32 _ipw_पढ़ो_reg32(काष्ठा ipw_priv *priv, u32 reg)
अणु
	u32 value;

	IPW_DEBUG_IO("%p : reg = 0x%08x\n", priv, reg);

	_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, reg);
	value = _ipw_पढ़ो32(priv, IPW_INसूचीECT_DATA);
	IPW_DEBUG_IO(" reg = 0x%4X : value = 0x%4x\n", reg, value);
	वापस value;
पूर्ण

/* General purpose, no alignment requirement, iterative (multi-byte) पढ़ो, */
/*    क्रम area above 1st 4K of SRAM/reg space */
अटल व्योम _ipw_पढ़ो_indirect(काष्ठा ipw_priv *priv, u32 addr, u8 * buf,
			       पूर्णांक num)
अणु
	u32 aligned_addr = addr & IPW_INसूचीECT_ADDR_MASK;	/* dword align */
	u32 dअगर_len = addr - aligned_addr;
	u32 i;

	IPW_DEBUG_IO("addr = %i, buf = %p, num = %i\n", addr, buf, num);

	अगर (num <= 0) अणु
		वापस;
	पूर्ण

	/* Read the first dword (or portion) byte by byte */
	अगर (unlikely(dअगर_len)) अणु
		_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
		/* Start पढ़ोing at aligned_addr + dअगर_len */
		क्रम (i = dअगर_len; ((i < 4) && (num > 0)); i++, num--)
			*buf++ = _ipw_पढ़ो8(priv, IPW_INसूचीECT_DATA + i);
		aligned_addr += 4;
	पूर्ण

	/* Read all of the middle dwords as dwords, with स्वतः-increment */
	_ipw_ग_लिखो32(priv, IPW_AUTOINC_ADDR, aligned_addr);
	क्रम (; num >= 4; buf += 4, aligned_addr += 4, num -= 4)
		*(u32 *) buf = _ipw_पढ़ो32(priv, IPW_AUTOINC_DATA);

	/* Read the last dword (or portion) byte by byte */
	अगर (unlikely(num)) अणु
		_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
		क्रम (i = 0; num > 0; i++, num--)
			*buf++ = ipw_पढ़ो8(priv, IPW_INसूचीECT_DATA + i);
	पूर्ण
पूर्ण

/* General purpose, no alignment requirement, iterative (multi-byte) ग_लिखो, */
/*    क्रम area above 1st 4K of SRAM/reg space */
अटल व्योम _ipw_ग_लिखो_indirect(काष्ठा ipw_priv *priv, u32 addr, u8 * buf,
				पूर्णांक num)
अणु
	u32 aligned_addr = addr & IPW_INसूचीECT_ADDR_MASK;	/* dword align */
	u32 dअगर_len = addr - aligned_addr;
	u32 i;

	IPW_DEBUG_IO("addr = %i, buf = %p, num = %i\n", addr, buf, num);

	अगर (num <= 0) अणु
		वापस;
	पूर्ण

	/* Write the first dword (or portion) byte by byte */
	अगर (unlikely(dअगर_len)) अणु
		_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
		/* Start writing at aligned_addr + dअगर_len */
		क्रम (i = dअगर_len; ((i < 4) && (num > 0)); i++, num--, buf++)
			_ipw_ग_लिखो8(priv, IPW_INसूचीECT_DATA + i, *buf);
		aligned_addr += 4;
	पूर्ण

	/* Write all of the middle dwords as dwords, with स्वतः-increment */
	_ipw_ग_लिखो32(priv, IPW_AUTOINC_ADDR, aligned_addr);
	क्रम (; num >= 4; buf += 4, aligned_addr += 4, num -= 4)
		_ipw_ग_लिखो32(priv, IPW_AUTOINC_DATA, *(u32 *) buf);

	/* Write the last dword (or portion) byte by byte */
	अगर (unlikely(num)) अणु
		_ipw_ग_लिखो32(priv, IPW_INसूचीECT_ADDR, aligned_addr);
		क्रम (i = 0; num > 0; i++, num--, buf++)
			_ipw_ग_लिखो8(priv, IPW_INसूचीECT_DATA + i, *buf);
	पूर्ण
पूर्ण

/* General purpose, no alignment requirement, iterative (multi-byte) ग_लिखो, */
/*    क्रम 1st 4K of SRAM/regs space */
अटल व्योम ipw_ग_लिखो_direct(काष्ठा ipw_priv *priv, u32 addr, व्योम *buf,
			     पूर्णांक num)
अणु
	स_नकल_toio((priv->hw_base + addr), buf, num);
पूर्ण

/* Set bit(s) in low 4K of SRAM/regs */
अटल अंतरभूत व्योम ipw_set_bit(काष्ठा ipw_priv *priv, u32 reg, u32 mask)
अणु
	ipw_ग_लिखो32(priv, reg, ipw_पढ़ो32(priv, reg) | mask);
पूर्ण

/* Clear bit(s) in low 4K of SRAM/regs */
अटल अंतरभूत व्योम ipw_clear_bit(काष्ठा ipw_priv *priv, u32 reg, u32 mask)
अणु
	ipw_ग_लिखो32(priv, reg, ipw_पढ़ो32(priv, reg) & ~mask);
पूर्ण

अटल अंतरभूत व्योम __ipw_enable_पूर्णांकerrupts(काष्ठा ipw_priv *priv)
अणु
	अगर (priv->status & STATUS_INT_ENABLED)
		वापस;
	priv->status |= STATUS_INT_ENABLED;
	ipw_ग_लिखो32(priv, IPW_INTA_MASK_R, IPW_INTA_MASK_ALL);
पूर्ण

अटल अंतरभूत व्योम __ipw_disable_पूर्णांकerrupts(काष्ठा ipw_priv *priv)
अणु
	अगर (!(priv->status & STATUS_INT_ENABLED))
		वापस;
	priv->status &= ~STATUS_INT_ENABLED;
	ipw_ग_लिखो32(priv, IPW_INTA_MASK_R, ~IPW_INTA_MASK_ALL);
पूर्ण

अटल अंतरभूत व्योम ipw_enable_पूर्णांकerrupts(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->irq_lock, flags);
	__ipw_enable_पूर्णांकerrupts(priv);
	spin_unlock_irqrestore(&priv->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम ipw_disable_पूर्णांकerrupts(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->irq_lock, flags);
	__ipw_disable_पूर्णांकerrupts(priv);
	spin_unlock_irqrestore(&priv->irq_lock, flags);
पूर्ण

अटल अक्षर *ipw_error_desc(u32 val)
अणु
	चयन (val) अणु
	हाल IPW_FW_ERROR_OK:
		वापस "ERROR_OK";
	हाल IPW_FW_ERROR_FAIL:
		वापस "ERROR_FAIL";
	हाल IPW_FW_ERROR_MEMORY_UNDERFLOW:
		वापस "MEMORY_UNDERFLOW";
	हाल IPW_FW_ERROR_MEMORY_OVERFLOW:
		वापस "MEMORY_OVERFLOW";
	हाल IPW_FW_ERROR_BAD_PARAM:
		वापस "BAD_PARAM";
	हाल IPW_FW_ERROR_BAD_CHECKSUM:
		वापस "BAD_CHECKSUM";
	हाल IPW_FW_ERROR_NMI_INTERRUPT:
		वापस "NMI_INTERRUPT";
	हाल IPW_FW_ERROR_BAD_DATABASE:
		वापस "BAD_DATABASE";
	हाल IPW_FW_ERROR_ALLOC_FAIL:
		वापस "ALLOC_FAIL";
	हाल IPW_FW_ERROR_DMA_UNDERRUN:
		वापस "DMA_UNDERRUN";
	हाल IPW_FW_ERROR_DMA_STATUS:
		वापस "DMA_STATUS";
	हाल IPW_FW_ERROR_DINO_ERROR:
		वापस "DINO_ERROR";
	हाल IPW_FW_ERROR_EEPROM_ERROR:
		वापस "EEPROM_ERROR";
	हाल IPW_FW_ERROR_SYSASSERT:
		वापस "SYSASSERT";
	हाल IPW_FW_ERROR_FATAL_ERROR:
		वापस "FATAL_ERROR";
	शेष:
		वापस "UNKNOWN_ERROR";
	पूर्ण
पूर्ण

अटल व्योम ipw_dump_error_log(काष्ठा ipw_priv *priv,
			       काष्ठा ipw_fw_error *error)
अणु
	u32 i;

	अगर (!error) अणु
		IPW_ERROR("Error allocating and capturing error log.  "
			  "Nothing to dump.\n");
		वापस;
	पूर्ण

	IPW_ERROR("Start IPW Error Log Dump:\n");
	IPW_ERROR("Status: 0x%08X, Config: %08X\n",
		  error->status, error->config);

	क्रम (i = 0; i < error->elem_len; i++)
		IPW_ERROR("%s %i 0x%08x  0x%08x  0x%08x  0x%08x  0x%08x\n",
			  ipw_error_desc(error->elem[i].desc),
			  error->elem[i].समय,
			  error->elem[i].blink1,
			  error->elem[i].blink2,
			  error->elem[i].link1,
			  error->elem[i].link2, error->elem[i].data);
	क्रम (i = 0; i < error->log_len; i++)
		IPW_ERROR("%i\t0x%08x\t%i\n",
			  error->log[i].समय,
			  error->log[i].data, error->log[i].event);
पूर्ण

अटल अंतरभूत पूर्णांक ipw_is_init(काष्ठा ipw_priv *priv)
अणु
	वापस (priv->status & STATUS_INIT) ? 1 : 0;
पूर्ण

अटल पूर्णांक ipw_get_ordinal(काष्ठा ipw_priv *priv, u32 ord, व्योम *val, u32 * len)
अणु
	u32 addr, field_info, field_len, field_count, total_len;

	IPW_DEBUG_ORD("ordinal = %i\n", ord);

	अगर (!priv || !val || !len) अणु
		IPW_DEBUG_ORD("Invalid argument\n");
		वापस -EINVAL;
	पूर्ण

	/* verअगरy device ordinal tables have been initialized */
	अगर (!priv->table0_addr || !priv->table1_addr || !priv->table2_addr) अणु
		IPW_DEBUG_ORD("Access ordinals before initialization\n");
		वापस -EINVAL;
	पूर्ण

	चयन (IPW_ORD_TABLE_ID_MASK & ord) अणु
	हाल IPW_ORD_TABLE_0_MASK:
		/*
		 * TABLE 0: Direct access to a table of 32 bit values
		 *
		 * This is a very simple table with the data directly
		 * पढ़ो from the table
		 */

		/* हटाओ the table id from the ordinal */
		ord &= IPW_ORD_TABLE_VALUE_MASK;

		/* boundary check */
		अगर (ord > priv->table0_len) अणु
			IPW_DEBUG_ORD("ordinal value (%i) longer then "
				      "max (%i)\n", ord, priv->table0_len);
			वापस -EINVAL;
		पूर्ण

		/* verअगरy we have enough room to store the value */
		अगर (*len < माप(u32)) अणु
			IPW_DEBUG_ORD("ordinal buffer length too small, "
				      "need %zd\n", माप(u32));
			वापस -EINVAL;
		पूर्ण

		IPW_DEBUG_ORD("Reading TABLE0[%i] from offset 0x%08x\n",
			      ord, priv->table0_addr + (ord << 2));

		*len = माप(u32);
		ord <<= 2;
		*((u32 *) val) = ipw_पढ़ो32(priv, priv->table0_addr + ord);
		अवरोध;

	हाल IPW_ORD_TABLE_1_MASK:
		/*
		 * TABLE 1: Indirect access to a table of 32 bit values
		 *
		 * This is a fairly large table of u32 values each
		 * representing starting addr क्रम the data (which is
		 * also a u32)
		 */

		/* हटाओ the table id from the ordinal */
		ord &= IPW_ORD_TABLE_VALUE_MASK;

		/* boundary check */
		अगर (ord > priv->table1_len) अणु
			IPW_DEBUG_ORD("ordinal value too long\n");
			वापस -EINVAL;
		पूर्ण

		/* verअगरy we have enough room to store the value */
		अगर (*len < माप(u32)) अणु
			IPW_DEBUG_ORD("ordinal buffer length too small, "
				      "need %zd\n", माप(u32));
			वापस -EINVAL;
		पूर्ण

		*((u32 *) val) =
		    ipw_पढ़ो_reg32(priv, (priv->table1_addr + (ord << 2)));
		*len = माप(u32);
		अवरोध;

	हाल IPW_ORD_TABLE_2_MASK:
		/*
		 * TABLE 2: Indirect access to a table of variable sized values
		 *
		 * This table consist of six values, each containing
		 *     - dword containing the starting offset of the data
		 *     - dword containing the lengh in the first 16bits
		 *       and the count in the second 16bits
		 */

		/* हटाओ the table id from the ordinal */
		ord &= IPW_ORD_TABLE_VALUE_MASK;

		/* boundary check */
		अगर (ord > priv->table2_len) अणु
			IPW_DEBUG_ORD("ordinal value too long\n");
			वापस -EINVAL;
		पूर्ण

		/* get the address of statistic */
		addr = ipw_पढ़ो_reg32(priv, priv->table2_addr + (ord << 3));

		/* get the second DW of statistics ;
		 * two 16-bit words - first is length, second is count */
		field_info =
		    ipw_पढ़ो_reg32(priv,
				   priv->table2_addr + (ord << 3) +
				   माप(u32));

		/* get each entry length */
		field_len = *((u16 *) & field_info);

		/* get number of entries */
		field_count = *(((u16 *) & field_info) + 1);

		/* पात अगर not enough memory */
		total_len = field_len * field_count;
		अगर (total_len > *len) अणु
			*len = total_len;
			वापस -EINVAL;
		पूर्ण

		*len = total_len;
		अगर (!total_len)
			वापस 0;

		IPW_DEBUG_ORD("addr = 0x%08x, total_len = %i, "
			      "field_info = 0x%08x\n",
			      addr, total_len, field_info);
		ipw_पढ़ो_indirect(priv, addr, val, total_len);
		अवरोध;

	शेष:
		IPW_DEBUG_ORD("Invalid ordinal!\n");
		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipw_init_ordinals(काष्ठा ipw_priv *priv)
अणु
	priv->table0_addr = IPW_ORDINALS_TABLE_LOWER;
	priv->table0_len = ipw_पढ़ो32(priv, priv->table0_addr);

	IPW_DEBUG_ORD("table 0 offset at 0x%08x, len = %i\n",
		      priv->table0_addr, priv->table0_len);

	priv->table1_addr = ipw_पढ़ो32(priv, IPW_ORDINALS_TABLE_1);
	priv->table1_len = ipw_पढ़ो_reg32(priv, priv->table1_addr);

	IPW_DEBUG_ORD("table 1 offset at 0x%08x, len = %i\n",
		      priv->table1_addr, priv->table1_len);

	priv->table2_addr = ipw_पढ़ो32(priv, IPW_ORDINALS_TABLE_2);
	priv->table2_len = ipw_पढ़ो_reg32(priv, priv->table2_addr);
	priv->table2_len &= 0x0000ffff;	/* use first two bytes */

	IPW_DEBUG_ORD("table 2 offset at 0x%08x, len = %i\n",
		      priv->table2_addr, priv->table2_len);

पूर्ण

अटल u32 ipw_रेजिस्टर_toggle(u32 reg)
अणु
	reg &= ~IPW_START_STANDBY;
	अगर (reg & IPW_GATE_ODMA)
		reg &= ~IPW_GATE_ODMA;
	अगर (reg & IPW_GATE_IDMA)
		reg &= ~IPW_GATE_IDMA;
	अगर (reg & IPW_GATE_ADMA)
		reg &= ~IPW_GATE_ADMA;
	वापस reg;
पूर्ण

/*
 * LED behavior:
 * - On radio ON, turn on any LEDs that require to be on during start
 * - On initialization, start unassociated blink
 * - On association, disable unassociated blink
 * - On disassociation, start unassociated blink
 * - On radio OFF, turn off any LEDs started during radio on
 *
 */
#घोषणा LD_TIME_LINK_ON msecs_to_jअगरfies(300)
#घोषणा LD_TIME_LINK_OFF msecs_to_jअगरfies(2700)
#घोषणा LD_TIME_ACT_ON msecs_to_jअगरfies(250)

अटल व्योम ipw_led_link_on(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	u32 led;

	/* If configured to not use LEDs, or nic_type is 1,
	 * then we करोn't toggle a LINK led */
	अगर (priv->config & CFG_NO_LED || priv->nic_type == EEPROM_NIC_TYPE_1)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (!(priv->status & STATUS_RF_KILL_MASK) &&
	    !(priv->status & STATUS_LED_LINK_ON)) अणु
		IPW_DEBUG_LED("Link LED On\n");
		led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
		led |= priv->led_association_on;

		led = ipw_रेजिस्टर_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

		priv->status |= STATUS_LED_LINK_ON;

		/* If we aren't associated, schedule turning the LED off */
		अगर (!(priv->status & STATUS_ASSOCIATED))
			schedule_delayed_work(&priv->led_link_off,
					      LD_TIME_LINK_ON);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_bg_led_link_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, led_link_on.work);
	mutex_lock(&priv->mutex);
	ipw_led_link_on(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_led_link_off(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	u32 led;

	/* If configured not to use LEDs, or nic type is 1,
	 * then we करोn't goggle the LINK led. */
	अगर (priv->config & CFG_NO_LED || priv->nic_type == EEPROM_NIC_TYPE_1)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (priv->status & STATUS_LED_LINK_ON) अणु
		led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
		led &= priv->led_association_off;
		led = ipw_रेजिस्टर_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

		IPW_DEBUG_LED("Link LED Off\n");

		priv->status &= ~STATUS_LED_LINK_ON;

		/* If we aren't associated and the radio is on, schedule
		 * turning the LED on (blink जबतक unassociated) */
		अगर (!(priv->status & STATUS_RF_KILL_MASK) &&
		    !(priv->status & STATUS_ASSOCIATED))
			schedule_delayed_work(&priv->led_link_on,
					      LD_TIME_LINK_OFF);

	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_bg_led_link_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, led_link_off.work);
	mutex_lock(&priv->mutex);
	ipw_led_link_off(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम __ipw_led_activity_on(काष्ठा ipw_priv *priv)
अणु
	u32 led;

	अगर (priv->config & CFG_NO_LED)
		वापस;

	अगर (priv->status & STATUS_RF_KILL_MASK)
		वापस;

	अगर (!(priv->status & STATUS_LED_ACT_ON)) अणु
		led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
		led |= priv->led_activity_on;

		led = ipw_रेजिस्टर_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

		IPW_DEBUG_LED("Activity LED On\n");

		priv->status |= STATUS_LED_ACT_ON;

		cancel_delayed_work(&priv->led_act_off);
		schedule_delayed_work(&priv->led_act_off, LD_TIME_ACT_ON);
	पूर्ण अन्यथा अणु
		/* Reschedule LED off क्रम full समय period */
		cancel_delayed_work(&priv->led_act_off);
		schedule_delayed_work(&priv->led_act_off, LD_TIME_ACT_ON);
	पूर्ण
पूर्ण

#अगर 0
व्योम ipw_led_activity_on(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&priv->lock, flags);
	__ipw_led_activity_on(priv);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
#पूर्ण_अगर  /*  0  */

अटल व्योम ipw_led_activity_off(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	u32 led;

	अगर (priv->config & CFG_NO_LED)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (priv->status & STATUS_LED_ACT_ON) अणु
		led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
		led &= priv->led_activity_off;

		led = ipw_रेजिस्टर_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

		IPW_DEBUG_LED("Activity LED Off\n");

		priv->status &= ~STATUS_LED_ACT_ON;
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_bg_led_activity_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, led_act_off.work);
	mutex_lock(&priv->mutex);
	ipw_led_activity_off(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_led_band_on(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	u32 led;

	/* Only nic type 1 supports mode LEDs */
	अगर (priv->config & CFG_NO_LED ||
	    priv->nic_type != EEPROM_NIC_TYPE_1 || !priv->assoc_network)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);

	led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
	अगर (priv->assoc_network->mode == IEEE_A) अणु
		led |= priv->led_ofdm_on;
		led &= priv->led_association_off;
		IPW_DEBUG_LED("Mode LED On: 802.11a\n");
	पूर्ण अन्यथा अगर (priv->assoc_network->mode == IEEE_G) अणु
		led |= priv->led_ofdm_on;
		led |= priv->led_association_on;
		IPW_DEBUG_LED("Mode LED On: 802.11g\n");
	पूर्ण अन्यथा अणु
		led &= priv->led_ofdm_off;
		led |= priv->led_association_on;
		IPW_DEBUG_LED("Mode LED On: 802.11b\n");
	पूर्ण

	led = ipw_रेजिस्टर_toggle(led);

	IPW_DEBUG_LED("Reg: 0x%08X\n", led);
	ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_led_band_off(काष्ठा ipw_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	u32 led;

	/* Only nic type 1 supports mode LEDs */
	अगर (priv->config & CFG_NO_LED || priv->nic_type != EEPROM_NIC_TYPE_1)
		वापस;

	spin_lock_irqsave(&priv->lock, flags);

	led = ipw_पढ़ो_reg32(priv, IPW_EVENT_REG);
	led &= priv->led_ofdm_off;
	led &= priv->led_association_off;

	led = ipw_रेजिस्टर_toggle(led);

	IPW_DEBUG_LED("Reg: 0x%08X\n", led);
	ipw_ग_लिखो_reg32(priv, IPW_EVENT_REG, led);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_led_radio_on(काष्ठा ipw_priv *priv)
अणु
	ipw_led_link_on(priv);
पूर्ण

अटल व्योम ipw_led_radio_off(काष्ठा ipw_priv *priv)
अणु
	ipw_led_activity_off(priv);
	ipw_led_link_off(priv);
पूर्ण

अटल व्योम ipw_led_link_up(काष्ठा ipw_priv *priv)
अणु
	/* Set the Link Led on क्रम all nic types */
	ipw_led_link_on(priv);
पूर्ण

अटल व्योम ipw_led_link_करोwn(काष्ठा ipw_priv *priv)
अणु
	ipw_led_activity_off(priv);
	ipw_led_link_off(priv);

	अगर (priv->status & STATUS_RF_KILL_MASK)
		ipw_led_radio_off(priv);
पूर्ण

अटल व्योम ipw_led_init(काष्ठा ipw_priv *priv)
अणु
	priv->nic_type = priv->eeprom[EEPROM_NIC_TYPE];

	/* Set the शेष PINs क्रम the link and activity leds */
	priv->led_activity_on = IPW_ACTIVITY_LED;
	priv->led_activity_off = ~(IPW_ACTIVITY_LED);

	priv->led_association_on = IPW_ASSOCIATED_LED;
	priv->led_association_off = ~(IPW_ASSOCIATED_LED);

	/* Set the शेष PINs क्रम the OFDM leds */
	priv->led_ofdm_on = IPW_OFDM_LED;
	priv->led_ofdm_off = ~(IPW_OFDM_LED);

	चयन (priv->nic_type) अणु
	हाल EEPROM_NIC_TYPE_1:
		/* In this NIC type, the LEDs are reversed.... */
		priv->led_activity_on = IPW_ASSOCIATED_LED;
		priv->led_activity_off = ~(IPW_ASSOCIATED_LED);
		priv->led_association_on = IPW_ACTIVITY_LED;
		priv->led_association_off = ~(IPW_ACTIVITY_LED);

		अगर (!(priv->config & CFG_NO_LED))
			ipw_led_band_on(priv);

		/* And we करोn't blink link LEDs क्रम this nic, so
		 * just वापस here */
		वापस;

	हाल EEPROM_NIC_TYPE_3:
	हाल EEPROM_NIC_TYPE_2:
	हाल EEPROM_NIC_TYPE_4:
	हाल EEPROM_NIC_TYPE_0:
		अवरोध;

	शेष:
		IPW_DEBUG_INFO("Unknown NIC type from EEPROM: %d\n",
			       priv->nic_type);
		priv->nic_type = EEPROM_NIC_TYPE_0;
		अवरोध;
	पूर्ण

	अगर (!(priv->config & CFG_NO_LED)) अणु
		अगर (priv->status & STATUS_ASSOCIATED)
			ipw_led_link_on(priv);
		अन्यथा
			ipw_led_link_off(priv);
	पूर्ण
पूर्ण

अटल व्योम ipw_led_shutकरोwn(काष्ठा ipw_priv *priv)
अणु
	ipw_led_activity_off(priv);
	ipw_led_link_off(priv);
	ipw_led_band_off(priv);
	cancel_delayed_work(&priv->led_link_on);
	cancel_delayed_work(&priv->led_link_off);
	cancel_delayed_work(&priv->led_act_off);
पूर्ण

/*
 * The following adds a new attribute to the sysfs representation
 * of this device driver (i.e. a new file in /sys/bus/pci/drivers/ipw/)
 * used क्रम controlling the debug level.
 *
 * See the level definitions in ipw क्रम details.
 */
अटल sमाप_प्रकार debug_level_show(काष्ठा device_driver *d, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%08X\n", ipw_debug_level);
पूर्ण

अटल sमाप_प्रकार debug_level_store(काष्ठा device_driver *d, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अक्षर *p = (अक्षर *)buf;
	u32 val;

	अगर (p[1] == 'x' || p[1] == 'X' || p[0] == 'x' || p[0] == 'X') अणु
		p++;
		अगर (p[0] == 'x' || p[0] == 'X')
			p++;
		val = simple_म_से_अदीर्घ(p, &p, 16);
	पूर्ण अन्यथा
		val = simple_म_से_अदीर्घ(p, &p, 10);
	अगर (p == buf)
		prपूर्णांकk(KERN_INFO DRV_NAME
		       ": %s is not in hex or decimal form.\n", buf);
	अन्यथा
		ipw_debug_level = val;

	वापस strnlen(buf, count);
पूर्ण
अटल DRIVER_ATTR_RW(debug_level);

अटल अंतरभूत u32 ipw_get_event_log_len(काष्ठा ipw_priv *priv)
अणु
	/* length = 1st dword in log */
	वापस ipw_पढ़ो_reg32(priv, ipw_पढ़ो32(priv, IPW_EVENT_LOG));
पूर्ण

अटल व्योम ipw_capture_event_log(काष्ठा ipw_priv *priv,
				  u32 log_len, काष्ठा ipw_event *log)
अणु
	u32 base;

	अगर (log_len) अणु
		base = ipw_पढ़ो32(priv, IPW_EVENT_LOG);
		ipw_पढ़ो_indirect(priv, base + माप(base) + माप(u32),
				  (u8 *) log, माप(*log) * log_len);
	पूर्ण
पूर्ण

अटल काष्ठा ipw_fw_error *ipw_alloc_error_log(काष्ठा ipw_priv *priv)
अणु
	काष्ठा ipw_fw_error *error;
	u32 log_len = ipw_get_event_log_len(priv);
	u32 base = ipw_पढ़ो32(priv, IPW_ERROR_LOG);
	u32 elem_len = ipw_पढ़ो_reg32(priv, base);

	error = kदो_स्मृति(माप(*error) +
			माप(*error->elem) * elem_len +
			माप(*error->log) * log_len, GFP_ATOMIC);
	अगर (!error) अणु
		IPW_ERROR("Memory allocation for firmware error log "
			  "failed.\n");
		वापस शून्य;
	पूर्ण
	error->jअगरfies = jअगरfies;
	error->status = priv->status;
	error->config = priv->config;
	error->elem_len = elem_len;
	error->log_len = log_len;
	error->elem = (काष्ठा ipw_error_elem *)error->payload;
	error->log = (काष्ठा ipw_event *)(error->elem + elem_len);

	ipw_capture_event_log(priv, log_len, error->log);

	अगर (elem_len)
		ipw_पढ़ो_indirect(priv, base + माप(base), (u8 *) error->elem,
				  माप(*error->elem) * elem_len);

	वापस error;
पूर्ण

अटल sमाप_प्रकार show_event_log(काष्ठा device *d,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	u32 log_len = ipw_get_event_log_len(priv);
	u32 log_size;
	काष्ठा ipw_event *log;
	u32 len = 0, i;

	/* not using min() because of its strict type checking */
	log_size = PAGE_SIZE / माप(*log) > log_len ?
			माप(*log) * log_len : PAGE_SIZE;
	log = kzalloc(log_size, GFP_KERNEL);
	अगर (!log) अणु
		IPW_ERROR("Unable to allocate memory for log\n");
		वापस 0;
	पूर्ण
	log_len = log_size / माप(*log);
	ipw_capture_event_log(priv, log_len, log);

	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%08X", log_len);
	क्रम (i = 0; i < log_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"\n%08X%08X%08X",
				log[i].समय, log[i].event, log[i].data);
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	kमुक्त(log);
	वापस len;
पूर्ण

अटल DEVICE_ATTR(event_log, 0444, show_event_log, शून्य);

अटल sमाप_प्रकार show_error(काष्ठा device *d,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	u32 len = 0, i;
	अगर (!priv->error)
		वापस 0;
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"%08lX%08X%08X%08X",
			priv->error->jअगरfies,
			priv->error->status,
			priv->error->config, priv->error->elem_len);
	क्रम (i = 0; i < priv->error->elem_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"\n%08X%08X%08X%08X%08X%08X%08X",
				priv->error->elem[i].समय,
				priv->error->elem[i].desc,
				priv->error->elem[i].blink1,
				priv->error->elem[i].blink2,
				priv->error->elem[i].link1,
				priv->error->elem[i].link2,
				priv->error->elem[i].data);

	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"\n%08X", priv->error->log_len);
	क्रम (i = 0; i < priv->error->log_len; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"\n%08X%08X%08X",
				priv->error->log[i].समय,
				priv->error->log[i].event,
				priv->error->log[i].data);
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	वापस len;
पूर्ण

अटल sमाप_प्रकार clear_error(काष्ठा device *d,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	kमुक्त(priv->error);
	priv->error = शून्य;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(error, 0644, show_error, clear_error);

अटल sमाप_प्रकार show_cmd_log(काष्ठा device *d,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	u32 len = 0, i;
	अगर (!priv->cmdlog)
		वापस 0;
	क्रम (i = (priv->cmdlog_pos + 1) % priv->cmdlog_len;
	     (i != priv->cmdlog_pos) && (len < PAGE_SIZE);
	     i = (i + 1) % priv->cmdlog_len) अणु
		len +=
		    scnम_लिखो(buf + len, PAGE_SIZE - len,
			     "\n%08lX%08X%08X%08X\n", priv->cmdlog[i].jअगरfies,
			     priv->cmdlog[i].retcode, priv->cmdlog[i].cmd.cmd,
			     priv->cmdlog[i].cmd.len);
		len +=
		    snprपूर्णांकk_buf(buf + len, PAGE_SIZE - len,
				 (u8 *) priv->cmdlog[i].cmd.param,
				 priv->cmdlog[i].cmd.len);
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	पूर्ण
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	वापस len;
पूर्ण

अटल DEVICE_ATTR(cmd_log, 0444, show_cmd_log, शून्य);

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
अटल व्योम ipw_prom_मुक्त(काष्ठा ipw_priv *priv);
अटल पूर्णांक ipw_prom_alloc(काष्ठा ipw_priv *priv);
अटल sमाप_प्रकार store_rtap_अगरace(काष्ठा device *d,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	पूर्णांक rc = 0;

	अगर (count < 1)
		वापस -EINVAL;

	चयन (buf[0]) अणु
	हाल '0':
		अगर (!rtap_अगरace)
			वापस count;

		अगर (netअगर_running(priv->prom_net_dev)) अणु
			IPW_WARNING("Interface is up.  Cannot unregister.\n");
			वापस count;
		पूर्ण

		ipw_prom_मुक्त(priv);
		rtap_अगरace = 0;
		अवरोध;

	हाल '1':
		अगर (rtap_अगरace)
			वापस count;

		rc = ipw_prom_alloc(priv);
		अगर (!rc)
			rtap_अगरace = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rc) अणु
		IPW_ERROR("Failed to register promiscuous network "
			  "device (error %d).\n", rc);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_rtap_अगरace(काष्ठा device *d,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	अगर (rtap_अगरace)
		वापस प्र_लिखो(buf, "%s", priv->prom_net_dev->name);
	अन्यथा अणु
		buf[0] = '-';
		buf[1] = '1';
		buf[2] = '\0';
		वापस 3;
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(rtap_अगरace, 0600, show_rtap_अगरace, store_rtap_अगरace);

अटल sमाप_प्रकार store_rtap_filter(काष्ठा device *d,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	अगर (!priv->prom_priv) अणु
		IPW_ERROR("Attempting to set filter without "
			  "rtap_iface enabled.\n");
		वापस -EPERM;
	पूर्ण

	priv->prom_priv->filter = simple_म_से_दीर्घ(buf, शून्य, 0);

	IPW_DEBUG_INFO("Setting rtap filter to " BIT_FMT16 "\n",
		       BIT_ARG16(priv->prom_priv->filter));

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_rtap_filter(काष्ठा device *d,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%04X",
		       priv->prom_priv ? priv->prom_priv->filter : 0);
पूर्ण

अटल DEVICE_ATTR(rtap_filter, 0600, show_rtap_filter, store_rtap_filter);
#पूर्ण_अगर

अटल sमाप_प्रकार show_scan_age(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%d\n", priv->ieee->scan_age);
पूर्ण

अटल sमाप_प्रकार store_scan_age(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	अक्षर buffer[] = "00000000";
	अचिन्हित दीर्घ len =
	    (माप(buffer) - 1) > count ? count : माप(buffer) - 1;
	अचिन्हित दीर्घ val;
	अक्षर *p = buffer;

	IPW_DEBUG_INFO("enter\n");

	म_नकलन(buffer, buf, len);
	buffer[len] = 0;

	अगर (p[1] == 'x' || p[1] == 'X' || p[0] == 'x' || p[0] == 'X') अणु
		p++;
		अगर (p[0] == 'x' || p[0] == 'X')
			p++;
		val = simple_म_से_अदीर्घ(p, &p, 16);
	पूर्ण अन्यथा
		val = simple_म_से_अदीर्घ(p, &p, 10);
	अगर (p == buffer) अणु
		IPW_DEBUG_INFO("%s: user supplied invalid value.\n", dev->name);
	पूर्ण अन्यथा अणु
		priv->ieee->scan_age = val;
		IPW_DEBUG_INFO("set scan_age = %u\n", priv->ieee->scan_age);
	पूर्ण

	IPW_DEBUG_INFO("exit\n");
	वापस len;
पूर्ण

अटल DEVICE_ATTR(scan_age, 0644, show_scan_age, store_scan_age);

अटल sमाप_प्रकार show_led(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%d\n", (priv->config & CFG_NO_LED) ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार store_led(काष्ठा device *d, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	IPW_DEBUG_INFO("enter\n");

	अगर (count == 0)
		वापस 0;

	अगर (*buf == 0) अणु
		IPW_DEBUG_LED("Disabling LED control.\n");
		priv->config |= CFG_NO_LED;
		ipw_led_shutकरोwn(priv);
	पूर्ण अन्यथा अणु
		IPW_DEBUG_LED("Enabling LED control.\n");
		priv->config &= ~CFG_NO_LED;
		ipw_led_init(priv);
	पूर्ण

	IPW_DEBUG_INFO("exit\n");
	वापस count;
पूर्ण

अटल DEVICE_ATTR(led, 0644, show_led, store_led);

अटल sमाप_प्रकार show_status(काष्ठा device *d,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *p = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)p->status);
पूर्ण

अटल DEVICE_ATTR(status, 0444, show_status, शून्य);

अटल sमाप_प्रकार show_cfg(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा ipw_priv *p = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)p->config);
पूर्ण

अटल DEVICE_ATTR(cfg, 0444, show_cfg, शून्य);

अटल sमाप_प्रकार show_nic_type(काष्ठा device *d,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "TYPE: %d\n", priv->nic_type);
पूर्ण

अटल DEVICE_ATTR(nic_type, 0444, show_nic_type, शून्य);

अटल sमाप_प्रकार show_ucode_version(काष्ठा device *d,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 len = माप(u32), पंचांगp = 0;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	अगर (ipw_get_ordinal(p, IPW_ORD_STAT_UCODE_VERSION, &पंचांगp, &len))
		वापस 0;

	वापस प्र_लिखो(buf, "0x%08x\n", पंचांगp);
पूर्ण

अटल DEVICE_ATTR(ucode_version, 0644, show_ucode_version, शून्य);

अटल sमाप_प्रकार show_rtc(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	u32 len = माप(u32), पंचांगp = 0;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	अगर (ipw_get_ordinal(p, IPW_ORD_STAT_RTC, &पंचांगp, &len))
		वापस 0;

	वापस प्र_लिखो(buf, "0x%08x\n", पंचांगp);
पूर्ण

अटल DEVICE_ATTR(rtc, 0644, show_rtc, शून्य);

/*
 * Add a device attribute to view/control the delay between eeprom
 * operations.
 */
अटल sमाप_प्रकार show_eeprom_delay(काष्ठा device *d,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw_priv *p = dev_get_drvdata(d);
	पूर्णांक n = p->eeprom_delay;
	वापस प्र_लिखो(buf, "%i\n", n);
पूर्ण
अटल sमाप_प्रकार store_eeprom_delay(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *p = dev_get_drvdata(d);
	माला_पूछो(buf, "%i", &p->eeprom_delay);
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(eeprom_delay, 0644, show_eeprom_delay, store_eeprom_delay);

अटल sमाप_प्रकार show_command_event_reg(काष्ठा device *d,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 reg = 0;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	reg = ipw_पढ़ो_reg32(p, IPW_INTERNAL_CMD_EVENT);
	वापस प्र_लिखो(buf, "0x%08x\n", reg);
पूर्ण
अटल sमाप_प्रकार store_command_event_reg(काष्ठा device *d,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 reg;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	माला_पूछो(buf, "%x", &reg);
	ipw_ग_लिखो_reg32(p, IPW_INTERNAL_CMD_EVENT, reg);
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(command_event_reg, 0644,
		   show_command_event_reg, store_command_event_reg);

अटल sमाप_प्रकार show_mem_gpio_reg(काष्ठा device *d,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 reg = 0;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	reg = ipw_पढ़ो_reg32(p, 0x301100);
	वापस प्र_लिखो(buf, "0x%08x\n", reg);
पूर्ण
अटल sमाप_प्रकार store_mem_gpio_reg(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 reg;
	काष्ठा ipw_priv *p = dev_get_drvdata(d);

	माला_पूछो(buf, "%x", &reg);
	ipw_ग_लिखो_reg32(p, 0x301100, reg);
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(mem_gpio_reg, 0644, show_mem_gpio_reg, store_mem_gpio_reg);

अटल sमाप_प्रकार show_indirect_dword(काष्ठा device *d,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 reg = 0;
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	अगर (priv->status & STATUS_INसूचीECT_DWORD)
		reg = ipw_पढ़ो_reg32(priv, priv->indirect_dword);
	अन्यथा
		reg = 0;

	वापस प्र_लिखो(buf, "0x%08x\n", reg);
पूर्ण
अटल sमाप_प्रकार store_indirect_dword(काष्ठा device *d,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	माला_पूछो(buf, "%x", &priv->indirect_dword);
	priv->status |= STATUS_INसूचीECT_DWORD;
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(indirect_dword, 0644,
		   show_indirect_dword, store_indirect_dword);

अटल sमाप_प्रकार show_indirect_byte(काष्ठा device *d,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 reg = 0;
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	अगर (priv->status & STATUS_INसूचीECT_BYTE)
		reg = ipw_पढ़ो_reg8(priv, priv->indirect_byte);
	अन्यथा
		reg = 0;

	वापस प्र_लिखो(buf, "0x%02x\n", reg);
पूर्ण
अटल sमाप_प्रकार store_indirect_byte(काष्ठा device *d,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	माला_पूछो(buf, "%x", &priv->indirect_byte);
	priv->status |= STATUS_INसूचीECT_BYTE;
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(indirect_byte, 0644,
		   show_indirect_byte, store_indirect_byte);

अटल sमाप_प्रकार show_direct_dword(काष्ठा device *d,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 reg = 0;
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	अगर (priv->status & STATUS_सूचीECT_DWORD)
		reg = ipw_पढ़ो32(priv, priv->direct_dword);
	अन्यथा
		reg = 0;

	वापस प्र_लिखो(buf, "0x%08x\n", reg);
पूर्ण
अटल sमाप_प्रकार store_direct_dword(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	माला_पूछो(buf, "%x", &priv->direct_dword);
	priv->status |= STATUS_सूचीECT_DWORD;
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(direct_dword, 0644, show_direct_dword, store_direct_dword);

अटल पूर्णांक rf_समाप्त_active(काष्ठा ipw_priv *priv)
अणु
	अगर (0 == (ipw_पढ़ो32(priv, 0x30) & 0x10000)) अणु
		priv->status |= STATUS_RF_KILL_HW;
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, true);
	पूर्ण अन्यथा अणु
		priv->status &= ~STATUS_RF_KILL_HW;
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, false);
	पूर्ण

	वापस (priv->status & STATUS_RF_KILL_HW) ? 1 : 0;
पूर्ण

अटल sमाप_प्रकार show_rf_समाप्त(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	/* 0 - RF समाप्त not enabled
	   1 - SW based RF समाप्त active (sysfs)
	   2 - HW based RF समाप्त active
	   3 - Both HW and SW baed RF समाप्त active */
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	पूर्णांक val = ((priv->status & STATUS_RF_KILL_SW) ? 0x1 : 0x0) |
	    (rf_समाप्त_active(priv) ? 0x2 : 0x0);
	वापस प्र_लिखो(buf, "%i\n", val);
पूर्ण

अटल पूर्णांक ipw_radio_समाप्त_sw(काष्ठा ipw_priv *priv, पूर्णांक disable_radio)
अणु
	अगर ((disable_radio ? 1 : 0) ==
	    ((priv->status & STATUS_RF_KILL_SW) ? 1 : 0))
		वापस 0;

	IPW_DEBUG_RF_KILL("Manual SW RF Kill set to: RADIO  %s\n",
			  disable_radio ? "OFF" : "ON");

	अगर (disable_radio) अणु
		priv->status |= STATUS_RF_KILL_SW;

		cancel_delayed_work(&priv->request_scan);
		cancel_delayed_work(&priv->request_direct_scan);
		cancel_delayed_work(&priv->request_passive_scan);
		cancel_delayed_work(&priv->scan_event);
		schedule_work(&priv->करोwn);
	पूर्ण अन्यथा अणु
		priv->status &= ~STATUS_RF_KILL_SW;
		अगर (rf_समाप्त_active(priv)) अणु
			IPW_DEBUG_RF_KILL("Can not turn radio back on - "
					  "disabled by HW switch\n");
			/* Make sure the RF_KILL check समयr is running */
			cancel_delayed_work(&priv->rf_समाप्त);
			schedule_delayed_work(&priv->rf_समाप्त,
					      round_jअगरfies_relative(2 * HZ));
		पूर्ण अन्यथा
			schedule_work(&priv->up);
	पूर्ण

	वापस 1;
पूर्ण

अटल sमाप_प्रकार store_rf_समाप्त(काष्ठा device *d, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);

	ipw_radio_समाप्त_sw(priv, buf[0] == '1');

	वापस count;
पूर्ण

अटल DEVICE_ATTR(rf_समाप्त, 0644, show_rf_समाप्त, store_rf_समाप्त);

अटल sमाप_प्रकार show_speed_scan(काष्ठा device *d, काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	पूर्णांक pos = 0, len = 0;
	अगर (priv->config & CFG_SPEED_SCAN) अणु
		जबतक (priv->speed_scan[pos] != 0)
			len += प्र_लिखो(&buf[len], "%d ",
				       priv->speed_scan[pos++]);
		वापस len + प्र_लिखो(&buf[len], "\n");
	पूर्ण

	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_speed_scan(काष्ठा device *d, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	पूर्णांक channel, pos = 0;
	स्थिर अक्षर *p = buf;

	/* list of space separated channels to scan, optionally ending with 0 */
	जबतक ((channel = simple_म_से_दीर्घ(p, शून्य, 0))) अणु
		अगर (pos == MAX_SPEED_SCAN - 1) अणु
			priv->speed_scan[pos] = 0;
			अवरोध;
		पूर्ण

		अगर (libipw_is_valid_channel(priv->ieee, channel))
			priv->speed_scan[pos++] = channel;
		अन्यथा
			IPW_WARNING("Skipping invalid channel request: %d\n",
				    channel);
		p = म_अक्षर(p, ' ');
		अगर (!p)
			अवरोध;
		जबतक (*p == ' ' || *p == '\t')
			p++;
	पूर्ण

	अगर (pos == 0)
		priv->config &= ~CFG_SPEED_SCAN;
	अन्यथा अणु
		priv->speed_scan_pos = 0;
		priv->config |= CFG_SPEED_SCAN;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(speed_scan, 0644, show_speed_scan, store_speed_scan);

अटल sमाप_प्रकार show_net_stats(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%c\n", (priv->config & CFG_NET_STATS) ? '1' : '0');
पूर्ण

अटल sमाप_प्रकार store_net_stats(काष्ठा device *d, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	अगर (buf[0] == '1')
		priv->config |= CFG_NET_STATS;
	अन्यथा
		priv->config &= ~CFG_NET_STATS;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(net_stats, 0644, show_net_stats, store_net_stats);

अटल sमाप_प्रकार show_channels(काष्ठा device *d,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(d);
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	पूर्णांक len = 0, i;

	len = प्र_लिखो(&buf[len],
		      "Displaying %d channels in 2.4Ghz band "
		      "(802.11bg):\n", geo->bg_channels);

	क्रम (i = 0; i < geo->bg_channels; i++) अणु
		len += प्र_लिखो(&buf[len], "%d: BSS%s%s, %s, Band %s.\n",
			       geo->bg[i].channel,
			       geo->bg[i].flags & LIBIPW_CH_RADAR_DETECT ?
			       " (radar spectrum)" : "",
			       ((geo->bg[i].flags & LIBIPW_CH_NO_IBSS) ||
				(geo->bg[i].flags & LIBIPW_CH_RADAR_DETECT))
			       ? "" : ", IBSS",
			       geo->bg[i].flags & LIBIPW_CH_PASSIVE_ONLY ?
			       "passive only" : "active/passive",
			       geo->bg[i].flags & LIBIPW_CH_B_ONLY ?
			       "B" : "B/G");
	पूर्ण

	len += प्र_लिखो(&buf[len],
		       "Displaying %d channels in 5.2Ghz band "
		       "(802.11a):\n", geo->a_channels);
	क्रम (i = 0; i < geo->a_channels; i++) अणु
		len += प्र_लिखो(&buf[len], "%d: BSS%s%s, %s.\n",
			       geo->a[i].channel,
			       geo->a[i].flags & LIBIPW_CH_RADAR_DETECT ?
			       " (radar spectrum)" : "",
			       ((geo->a[i].flags & LIBIPW_CH_NO_IBSS) ||
				(geo->a[i].flags & LIBIPW_CH_RADAR_DETECT))
			       ? "" : ", IBSS",
			       geo->a[i].flags & LIBIPW_CH_PASSIVE_ONLY ?
			       "passive only" : "active/passive");
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(channels, 0400, show_channels, शून्य);

अटल व्योम notअगरy_wx_assoc_event(काष्ठा ipw_priv *priv)
अणु
	जोड़ iwreq_data wrqu;
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	अगर (priv->status & STATUS_ASSOCIATED)
		स_नकल(wrqu.ap_addr.sa_data, priv->bssid, ETH_ALEN);
	अन्यथा
		eth_zero_addr(wrqu.ap_addr.sa_data);
	wireless_send_event(priv->net_dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

अटल व्योम ipw_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ipw_priv *priv = from_tasklet(priv, t, irq_tasklet);
	u32 पूर्णांकa, पूर्णांकa_mask, handled = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->irq_lock, flags);

	पूर्णांकa = ipw_पढ़ो32(priv, IPW_INTA_RW);
	पूर्णांकa_mask = ipw_पढ़ो32(priv, IPW_INTA_MASK_R);

	अगर (पूर्णांकa == 0xFFFFFFFF) अणु
		/* Hardware disappeared */
		IPW_WARNING("TASKLET INTA == 0xFFFFFFFF\n");
		/* Only handle the cached INTA values */
		पूर्णांकa = 0;
	पूर्ण
	पूर्णांकa &= (IPW_INTA_MASK_ALL & पूर्णांकa_mask);

	/* Add any cached INTA values that need to be handled */
	पूर्णांकa |= priv->isr_पूर्णांकa;

	spin_unlock_irqrestore(&priv->irq_lock, flags);

	spin_lock_irqsave(&priv->lock, flags);

	/* handle all the justअगरications क्रम the पूर्णांकerrupt */
	अगर (पूर्णांकa & IPW_INTA_BIT_RX_TRANSFER) अणु
		ipw_rx(priv);
		handled |= IPW_INTA_BIT_RX_TRANSFER;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_TX_CMD_QUEUE) अणु
		IPW_DEBUG_HC("Command completed.\n");
		ipw_queue_tx_reclaim(priv, &priv->txq_cmd, -1);
		priv->status &= ~STATUS_HCMD_ACTIVE;
		wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);
		handled |= IPW_INTA_BIT_TX_CMD_QUEUE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_TX_QUEUE_1) अणु
		IPW_DEBUG_TX("TX_QUEUE_1\n");
		ipw_queue_tx_reclaim(priv, &priv->txq[0], 0);
		handled |= IPW_INTA_BIT_TX_QUEUE_1;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_TX_QUEUE_2) अणु
		IPW_DEBUG_TX("TX_QUEUE_2\n");
		ipw_queue_tx_reclaim(priv, &priv->txq[1], 1);
		handled |= IPW_INTA_BIT_TX_QUEUE_2;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_TX_QUEUE_3) अणु
		IPW_DEBUG_TX("TX_QUEUE_3\n");
		ipw_queue_tx_reclaim(priv, &priv->txq[2], 2);
		handled |= IPW_INTA_BIT_TX_QUEUE_3;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_TX_QUEUE_4) अणु
		IPW_DEBUG_TX("TX_QUEUE_4\n");
		ipw_queue_tx_reclaim(priv, &priv->txq[3], 3);
		handled |= IPW_INTA_BIT_TX_QUEUE_4;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_STATUS_CHANGE) अणु
		IPW_WARNING("STATUS_CHANGE\n");
		handled |= IPW_INTA_BIT_STATUS_CHANGE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_BEACON_PERIOD_EXPIRED) अणु
		IPW_WARNING("TX_PERIOD_EXPIRED\n");
		handled |= IPW_INTA_BIT_BEACON_PERIOD_EXPIRED;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE) अणु
		IPW_WARNING("HOST_CMD_DONE\n");
		handled |= IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_FW_INITIALIZATION_DONE) अणु
		IPW_WARNING("FW_INITIALIZATION_DONE\n");
		handled |= IPW_INTA_BIT_FW_INITIALIZATION_DONE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE) अणु
		IPW_WARNING("PHY_OFF_DONE\n");
		handled |= IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_RF_KILL_DONE) अणु
		IPW_DEBUG_RF_KILL("RF_KILL_DONE\n");
		priv->status |= STATUS_RF_KILL_HW;
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, true);
		wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);
		priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);
		cancel_delayed_work(&priv->request_scan);
		cancel_delayed_work(&priv->request_direct_scan);
		cancel_delayed_work(&priv->request_passive_scan);
		cancel_delayed_work(&priv->scan_event);
		schedule_work(&priv->link_करोwn);
		schedule_delayed_work(&priv->rf_समाप्त, 2 * HZ);
		handled |= IPW_INTA_BIT_RF_KILL_DONE;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_FATAL_ERROR) अणु
		IPW_WARNING("Firmware error detected.  Restarting.\n");
		अगर (priv->error) अणु
			IPW_DEBUG_FW("Sysfs 'error' log already exists.\n");
			अगर (ipw_debug_level & IPW_DL_FW_ERRORS) अणु
				काष्ठा ipw_fw_error *error =
				    ipw_alloc_error_log(priv);
				ipw_dump_error_log(priv, error);
				kमुक्त(error);
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->error = ipw_alloc_error_log(priv);
			अगर (priv->error)
				IPW_DEBUG_FW("Sysfs 'error' log captured.\n");
			अन्यथा
				IPW_DEBUG_FW("Error allocating sysfs 'error' "
					     "log.\n");
			अगर (ipw_debug_level & IPW_DL_FW_ERRORS)
				ipw_dump_error_log(priv, priv->error);
		पूर्ण

		/* XXX: If hardware encryption is क्रम WPA/WPA2,
		 * we have to notअगरy the supplicant. */
		अगर (priv->ieee->sec.encrypt) अणु
			priv->status &= ~STATUS_ASSOCIATED;
			notअगरy_wx_assoc_event(priv);
		पूर्ण

		/* Keep the restart process from trying to send host
		 * commands by clearing the INIT status bit */
		priv->status &= ~STATUS_INIT;

		/* Cancel currently queued command. */
		priv->status &= ~STATUS_HCMD_ACTIVE;
		wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);

		schedule_work(&priv->adapter_restart);
		handled |= IPW_INTA_BIT_FATAL_ERROR;
	पूर्ण

	अगर (पूर्णांकa & IPW_INTA_BIT_PARITY_ERROR) अणु
		IPW_ERROR("Parity error\n");
		handled |= IPW_INTA_BIT_PARITY_ERROR;
	पूर्ण

	अगर (handled != पूर्णांकa) अणु
		IPW_ERROR("Unhandled INTA bits 0x%08x\n", पूर्णांकa & ~handled);
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	/* enable all पूर्णांकerrupts */
	ipw_enable_पूर्णांकerrupts(priv);
पूर्ण

#घोषणा IPW_CMD(x) हाल IPW_CMD_ ## x : वापस #x
अटल अक्षर *get_cmd_string(u8 cmd)
अणु
	चयन (cmd) अणु
		IPW_CMD(HOST_COMPLETE);
		IPW_CMD(POWER_DOWN);
		IPW_CMD(SYSTEM_CONFIG);
		IPW_CMD(MULTICAST_ADDRESS);
		IPW_CMD(SSID);
		IPW_CMD(ADAPTER_ADDRESS);
		IPW_CMD(PORT_TYPE);
		IPW_CMD(RTS_THRESHOLD);
		IPW_CMD(FRAG_THRESHOLD);
		IPW_CMD(POWER_MODE);
		IPW_CMD(WEP_KEY);
		IPW_CMD(TGI_TX_KEY);
		IPW_CMD(SCAN_REQUEST);
		IPW_CMD(SCAN_REQUEST_EXT);
		IPW_CMD(ASSOCIATE);
		IPW_CMD(SUPPORTED_RATES);
		IPW_CMD(SCAN_ABORT);
		IPW_CMD(TX_FLUSH);
		IPW_CMD(QOS_PARAMETERS);
		IPW_CMD(DINO_CONFIG);
		IPW_CMD(RSN_CAPABILITIES);
		IPW_CMD(RX_KEY);
		IPW_CMD(CARD_DISABLE);
		IPW_CMD(SEED_NUMBER);
		IPW_CMD(TX_POWER);
		IPW_CMD(COUNTRY_INFO);
		IPW_CMD(AIRONET_INFO);
		IPW_CMD(AP_TX_POWER);
		IPW_CMD(CCKM_INFO);
		IPW_CMD(CCX_VER_INFO);
		IPW_CMD(SET_CALIBRATION);
		IPW_CMD(SENSITIVITY_CALIB);
		IPW_CMD(RETRY_LIMIT);
		IPW_CMD(IPW_PRE_POWER_DOWN);
		IPW_CMD(VAP_BEACON_TEMPLATE);
		IPW_CMD(VAP_DTIM_PERIOD);
		IPW_CMD(EXT_SUPPORTED_RATES);
		IPW_CMD(VAP_LOCAL_TX_PWR_CONSTRAINT);
		IPW_CMD(VAP_QUIET_INTERVALS);
		IPW_CMD(VAP_CHANNEL_SWITCH);
		IPW_CMD(VAP_MANDATORY_CHANNELS);
		IPW_CMD(VAP_CELL_PWR_LIMIT);
		IPW_CMD(VAP_CF_PARAM_SET);
		IPW_CMD(VAP_SET_BEACONING_STATE);
		IPW_CMD(MEASUREMENT);
		IPW_CMD(POWER_CAPABILITY);
		IPW_CMD(SUPPORTED_CHANNELS);
		IPW_CMD(TPC_REPORT);
		IPW_CMD(WME_INFO);
		IPW_CMD(PRODUCTION_COMMAND);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

#घोषणा HOST_COMPLETE_TIMEOUT HZ

अटल पूर्णांक __ipw_send_cmd(काष्ठा ipw_priv *priv, काष्ठा host_cmd *cmd)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ now, end;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->status & STATUS_HCMD_ACTIVE) अणु
		IPW_ERROR("Failed to send %s: Already sending a command.\n",
			  get_cmd_string(cmd->cmd));
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस -EAGAIN;
	पूर्ण

	priv->status |= STATUS_HCMD_ACTIVE;

	अगर (priv->cmdlog) अणु
		priv->cmdlog[priv->cmdlog_pos].jअगरfies = jअगरfies;
		priv->cmdlog[priv->cmdlog_pos].cmd.cmd = cmd->cmd;
		priv->cmdlog[priv->cmdlog_pos].cmd.len = cmd->len;
		स_नकल(priv->cmdlog[priv->cmdlog_pos].cmd.param, cmd->param,
		       cmd->len);
		priv->cmdlog[priv->cmdlog_pos].retcode = -1;
	पूर्ण

	IPW_DEBUG_HC("%s command (#%d) %d bytes: 0x%08X\n",
		     get_cmd_string(cmd->cmd), cmd->cmd, cmd->len,
		     priv->status);

#अगर_अघोषित DEBUG_CMD_WEP_KEY
	अगर (cmd->cmd == IPW_CMD_WEP_KEY)
		IPW_DEBUG_HC("WEP_KEY command masked out for secure.\n");
	अन्यथा
#पूर्ण_अगर
		prपूर्णांकk_buf(IPW_DL_HOST_COMMAND, (u8 *) cmd->param, cmd->len);

	rc = ipw_queue_tx_hcmd(priv, cmd->cmd, cmd->param, cmd->len, 0);
	अगर (rc) अणु
		priv->status &= ~STATUS_HCMD_ACTIVE;
		IPW_ERROR("Failed to send %s: Reason %d\n",
			  get_cmd_string(cmd->cmd), rc);
		spin_unlock_irqrestore(&priv->lock, flags);
		जाओ निकास;
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	now = jअगरfies;
	end = now + HOST_COMPLETE_TIMEOUT;
again:
	rc = रुको_event_पूर्णांकerruptible_समयout(priv->रुको_command_queue,
					      !(priv->
						status & STATUS_HCMD_ACTIVE),
					      end - now);
	अगर (rc < 0) अणु
		now = jअगरfies;
		अगर (समय_beक्रमe(now, end))
			जाओ again;
		rc = 0;
	पूर्ण

	अगर (rc == 0) अणु
		spin_lock_irqsave(&priv->lock, flags);
		अगर (priv->status & STATUS_HCMD_ACTIVE) अणु
			IPW_ERROR("Failed to send %s: Command timed out.\n",
				  get_cmd_string(cmd->cmd));
			priv->status &= ~STATUS_HCMD_ACTIVE;
			spin_unlock_irqrestore(&priv->lock, flags);
			rc = -EIO;
			जाओ निकास;
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण अन्यथा
		rc = 0;

	अगर (priv->status & STATUS_RF_KILL_HW) अणु
		IPW_ERROR("Failed to send %s: Aborted due to RF kill switch.\n",
			  get_cmd_string(cmd->cmd));
		rc = -EIO;
		जाओ निकास;
	पूर्ण

      निकास:
	अगर (priv->cmdlog) अणु
		priv->cmdlog[priv->cmdlog_pos++].retcode = rc;
		priv->cmdlog_pos %= priv->cmdlog_len;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक ipw_send_cmd_simple(काष्ठा ipw_priv *priv, u8 command)
अणु
	काष्ठा host_cmd cmd = अणु
		.cmd = command,
	पूर्ण;

	वापस __ipw_send_cmd(priv, &cmd);
पूर्ण

अटल पूर्णांक ipw_send_cmd_pdu(काष्ठा ipw_priv *priv, u8 command, u8 len,
			    व्योम *data)
अणु
	काष्ठा host_cmd cmd = अणु
		.cmd = command,
		.len = len,
		.param = data,
	पूर्ण;

	वापस __ipw_send_cmd(priv, &cmd);
पूर्ण

अटल पूर्णांक ipw_send_host_complete(काष्ठा ipw_priv *priv)
अणु
	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_simple(priv, IPW_CMD_HOST_COMPLETE);
पूर्ण

अटल पूर्णांक ipw_send_प्रणाली_config(काष्ठा ipw_priv *priv)
अणु
	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SYSTEM_CONFIG,
				माप(priv->sys_config),
				&priv->sys_config);
पूर्ण

अटल पूर्णांक ipw_send_ssid(काष्ठा ipw_priv *priv, u8 * ssid, पूर्णांक len)
अणु
	अगर (!priv || !ssid) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SSID, min(len, IW_ESSID_MAX_SIZE),
				ssid);
पूर्ण

अटल पूर्णांक ipw_send_adapter_address(काष्ठा ipw_priv *priv, u8 * mac)
अणु
	अगर (!priv || !mac) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	IPW_DEBUG_INFO("%s: Setting MAC to %pM\n",
		       priv->net_dev->name, mac);

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_ADAPTER_ADDRESS, ETH_ALEN, mac);
पूर्ण

अटल व्योम ipw_adapter_restart(व्योम *adapter)
अणु
	काष्ठा ipw_priv *priv = adapter;

	अगर (priv->status & STATUS_RF_KILL_MASK)
		वापस;

	ipw_करोwn(priv);

	अगर (priv->assoc_network &&
	    (priv->assoc_network->capability & WLAN_CAPABILITY_IBSS))
		ipw_हटाओ_current_network(priv);

	अगर (ipw_up(priv)) अणु
		IPW_ERROR("Failed to up device\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ipw_bg_adapter_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, adapter_restart);
	mutex_lock(&priv->mutex);
	ipw_adapter_restart(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_पात_scan(काष्ठा ipw_priv *priv);

#घोषणा IPW_SCAN_CHECK_WATCHDOG	(5 * HZ)

अटल व्योम ipw_scan_check(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;

	अगर (priv->status & STATUS_SCAN_ABORTING) अणु
		IPW_DEBUG_SCAN("Scan completion watchdog resetting "
			       "adapter after (%dms).\n",
			       jअगरfies_to_msecs(IPW_SCAN_CHECK_WATCHDOG));
		schedule_work(&priv->adapter_restart);
	पूर्ण अन्यथा अगर (priv->status & STATUS_SCANNING) अणु
		IPW_DEBUG_SCAN("Scan completion watchdog aborting scan "
			       "after (%dms).\n",
			       jअगरfies_to_msecs(IPW_SCAN_CHECK_WATCHDOG));
		ipw_पात_scan(priv);
		schedule_delayed_work(&priv->scan_check, HZ);
	पूर्ण
पूर्ण

अटल व्योम ipw_bg_scan_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, scan_check.work);
	mutex_lock(&priv->mutex);
	ipw_scan_check(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ipw_send_scan_request_ext(काष्ठा ipw_priv *priv,
				     काष्ठा ipw_scan_request_ext *request)
अणु
	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SCAN_REQUEST_EXT,
				माप(*request), request);
पूर्ण

अटल पूर्णांक ipw_send_scan_पात(काष्ठा ipw_priv *priv)
अणु
	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_simple(priv, IPW_CMD_SCAN_ABORT);
पूर्ण

अटल पूर्णांक ipw_set_sensitivity(काष्ठा ipw_priv *priv, u16 sens)
अणु
	काष्ठा ipw_sensitivity_calib calib = अणु
		.beacon_rssi_raw = cpu_to_le16(sens),
	पूर्ण;

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SENSITIVITY_CALIB, माप(calib),
				&calib);
पूर्ण

अटल पूर्णांक ipw_send_associate(काष्ठा ipw_priv *priv,
			      काष्ठा ipw_associate *associate)
अणु
	अगर (!priv || !associate) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_ASSOCIATE, माप(*associate),
				associate);
पूर्ण

अटल पूर्णांक ipw_send_supported_rates(काष्ठा ipw_priv *priv,
				    काष्ठा ipw_supported_rates *rates)
अणु
	अगर (!priv || !rates) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SUPPORTED_RATES, माप(*rates),
				rates);
पूर्ण

अटल पूर्णांक ipw_set_अक्रमom_seed(काष्ठा ipw_priv *priv)
अणु
	u32 val;

	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	get_अक्रमom_bytes(&val, माप(val));

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_SEED_NUMBER, माप(val), &val);
पूर्ण

अटल पूर्णांक ipw_send_card_disable(काष्ठा ipw_priv *priv, u32 phy_off)
अणु
	__le32 v = cpu_to_le32(phy_off);
	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_CARD_DISABLE, माप(v), &v);
पूर्ण

अटल पूर्णांक ipw_send_tx_घातer(काष्ठा ipw_priv *priv, काष्ठा ipw_tx_घातer *घातer)
अणु
	अगर (!priv || !घातer) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_TX_POWER, माप(*घातer), घातer);
पूर्ण

अटल पूर्णांक ipw_set_tx_घातer(काष्ठा ipw_priv *priv)
अणु
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	काष्ठा ipw_tx_घातer tx_घातer;
	s8 max_घातer;
	पूर्णांक i;

	स_रखो(&tx_घातer, 0, माप(tx_घातer));

	/* configure device क्रम 'G' band */
	tx_घातer.ieee_mode = IPW_G_MODE;
	tx_घातer.num_channels = geo->bg_channels;
	क्रम (i = 0; i < geo->bg_channels; i++) अणु
		max_घातer = geo->bg[i].max_घातer;
		tx_घातer.channels_tx_घातer[i].channel_number =
		    geo->bg[i].channel;
		tx_घातer.channels_tx_घातer[i].tx_घातer = max_घातer ?
		    min(max_घातer, priv->tx_घातer) : priv->tx_घातer;
	पूर्ण
	अगर (ipw_send_tx_घातer(priv, &tx_घातer))
		वापस -EIO;

	/* configure device to also handle 'B' band */
	tx_घातer.ieee_mode = IPW_B_MODE;
	अगर (ipw_send_tx_घातer(priv, &tx_घातer))
		वापस -EIO;

	/* configure device to also handle 'A' band */
	अगर (priv->ieee->abg_true) अणु
		tx_घातer.ieee_mode = IPW_A_MODE;
		tx_घातer.num_channels = geo->a_channels;
		क्रम (i = 0; i < tx_घातer.num_channels; i++) अणु
			max_घातer = geo->a[i].max_घातer;
			tx_घातer.channels_tx_घातer[i].channel_number =
			    geo->a[i].channel;
			tx_घातer.channels_tx_घातer[i].tx_घातer = max_घातer ?
			    min(max_घातer, priv->tx_घातer) : priv->tx_घातer;
		पूर्ण
		अगर (ipw_send_tx_घातer(priv, &tx_घातer))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_send_rts_threshold(काष्ठा ipw_priv *priv, u16 rts)
अणु
	काष्ठा ipw_rts_threshold rts_threshold = अणु
		.rts_threshold = cpu_to_le16(rts),
	पूर्ण;

	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_RTS_THRESHOLD,
				माप(rts_threshold), &rts_threshold);
पूर्ण

अटल पूर्णांक ipw_send_frag_threshold(काष्ठा ipw_priv *priv, u16 frag)
अणु
	काष्ठा ipw_frag_threshold frag_threshold = अणु
		.frag_threshold = cpu_to_le16(frag),
	पूर्ण;

	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_FRAG_THRESHOLD,
				माप(frag_threshold), &frag_threshold);
पूर्ण

अटल पूर्णांक ipw_send_घातer_mode(काष्ठा ipw_priv *priv, u32 mode)
अणु
	__le32 param;

	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	/* If on battery, set to 3, अगर AC set to CAM, अन्यथा user
	 * level */
	चयन (mode) अणु
	हाल IPW_POWER_BATTERY:
		param = cpu_to_le32(IPW_POWER_INDEX_3);
		अवरोध;
	हाल IPW_POWER_AC:
		param = cpu_to_le32(IPW_POWER_MODE_CAM);
		अवरोध;
	शेष:
		param = cpu_to_le32(mode);
		अवरोध;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_POWER_MODE, माप(param),
				&param);
पूर्ण

अटल पूर्णांक ipw_send_retry_limit(काष्ठा ipw_priv *priv, u8 slimit, u8 llimit)
अणु
	काष्ठा ipw_retry_limit retry_limit = अणु
		.लघु_retry_limit = slimit,
		.दीर्घ_retry_limit = llimit
	पूर्ण;

	अगर (!priv) अणु
		IPW_ERROR("Invalid args\n");
		वापस -1;
	पूर्ण

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_RETRY_LIMIT, माप(retry_limit),
				&retry_limit);
पूर्ण

/*
 * The IPW device contains a Microwire compatible EEPROM that stores
 * various data like the MAC address.  Usually the firmware has exclusive
 * access to the eeprom, but during device initialization (beक्रमe the
 * device driver has sent the HostComplete command to the firmware) the
 * device driver has पढ़ो access to the EEPROM by way of indirect addressing
 * through a couple of memory mapped रेजिस्टरs.
 *
 * The following is a simplअगरied implementation क्रम pulling data out of the
 * the eeprom, aदीर्घ with some helper functions to find inक्रमmation in
 * the per device निजी data's copy of the eeprom.
 *
 * NOTE: To better understand how these functions work (i.e what is a chip
 *       select and why करो have to keep driving the eeprom घड़ी?), पढ़ो
 *       just about any data sheet क्रम a Microwire compatible EEPROM.
 */

/* ग_लिखो a 32 bit value पूर्णांकo the indirect accessor रेजिस्टर */
अटल अंतरभूत व्योम eeprom_ग_लिखो_reg(काष्ठा ipw_priv *p, u32 data)
अणु
	ipw_ग_लिखो_reg32(p, FW_MEM_REG_EEPROM_ACCESS, data);

	/* the eeprom requires some समय to complete the operation */
	udelay(p->eeprom_delay);
पूर्ण

/* perक्रमm a chip select operation */
अटल व्योम eeprom_cs(काष्ठा ipw_priv *priv)
अणु
	eeprom_ग_लिखो_reg(priv, 0);
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS);
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS | EEPROM_BIT_SK);
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS);
पूर्ण

/* perक्रमm a chip select operation */
अटल व्योम eeprom_disable_cs(काष्ठा ipw_priv *priv)
अणु
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS);
	eeprom_ग_लिखो_reg(priv, 0);
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_SK);
पूर्ण

/* push a single bit करोwn to the eeprom */
अटल अंतरभूत व्योम eeprom_ग_लिखो_bit(काष्ठा ipw_priv *p, u8 bit)
अणु
	पूर्णांक d = (bit ? EEPROM_BIT_DI : 0);
	eeprom_ग_लिखो_reg(p, EEPROM_BIT_CS | d);
	eeprom_ग_लिखो_reg(p, EEPROM_BIT_CS | d | EEPROM_BIT_SK);
पूर्ण

/* push an opcode followed by an address करोwn to the eeprom */
अटल व्योम eeprom_op(काष्ठा ipw_priv *priv, u8 op, u8 addr)
अणु
	पूर्णांक i;

	eeprom_cs(priv);
	eeprom_ग_लिखो_bit(priv, 1);
	eeprom_ग_लिखो_bit(priv, op & 2);
	eeprom_ग_लिखो_bit(priv, op & 1);
	क्रम (i = 7; i >= 0; i--) अणु
		eeprom_ग_लिखो_bit(priv, addr & (1 << i));
	पूर्ण
पूर्ण

/* pull 16 bits off the eeprom, one bit at a समय */
अटल u16 eeprom_पढ़ो_u16(काष्ठा ipw_priv *priv, u8 addr)
अणु
	पूर्णांक i;
	u16 r = 0;

	/* Send READ Opcode */
	eeprom_op(priv, EEPROM_CMD_READ, addr);

	/* Send dummy bit */
	eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS);

	/* Read the byte off the eeprom one bit at a समय */
	क्रम (i = 0; i < 16; i++) अणु
		u32 data = 0;
		eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS | EEPROM_BIT_SK);
		eeprom_ग_लिखो_reg(priv, EEPROM_BIT_CS);
		data = ipw_पढ़ो_reg32(priv, FW_MEM_REG_EEPROM_ACCESS);
		r = (r << 1) | ((data & EEPROM_BIT_DO) ? 1 : 0);
	पूर्ण

	/* Send another dummy bit */
	eeprom_ग_लिखो_reg(priv, 0);
	eeprom_disable_cs(priv);

	वापस r;
पूर्ण

/* helper function क्रम pulling the mac address out of the निजी */
/* data's copy of the eeprom data                                 */
अटल व्योम eeprom_parse_mac(काष्ठा ipw_priv *priv, u8 * mac)
अणु
	स_नकल(mac, &priv->eeprom[EEPROM_MAC_ADDRESS], ETH_ALEN);
पूर्ण

अटल व्योम ipw_पढ़ो_eeprom(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक i;
	__le16 *eeprom = (__le16 *) priv->eeprom;

	IPW_DEBUG_TRACE(">>\n");

	/* पढ़ो entire contents of eeprom पूर्णांकo निजी buffer */
	क्रम (i = 0; i < 128; i++)
		eeprom[i] = cpu_to_le16(eeprom_पढ़ो_u16(priv, (u8) i));

	IPW_DEBUG_TRACE("<<\n");
पूर्ण

/*
 * Either the device driver (i.e. the host) or the firmware can
 * load eeprom data पूर्णांकo the designated region in SRAM.  If neither
 * happens then the FW will shutकरोwn with a fatal error.
 *
 * In order to संकेत the FW to load the EEPROM, the EEPROM_LOAD_DISABLE
 * bit needs region of shared SRAM needs to be non-zero.
 */
अटल व्योम ipw_eeprom_init_sram(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक i;

	IPW_DEBUG_TRACE(">>\n");

	/*
	   If the data looks correct, then copy it to our निजी
	   copy.  Otherwise let the firmware know to perक्रमm the operation
	   on its own.
	 */
	अगर (priv->eeprom[EEPROM_VERSION] != 0) अणु
		IPW_DEBUG_INFO("Writing EEPROM data into SRAM\n");

		/* ग_लिखो the eeprom data to sram */
		क्रम (i = 0; i < IPW_EEPROM_IMAGE_SIZE; i++)
			ipw_ग_लिखो8(priv, IPW_EEPROM_DATA + i, priv->eeprom[i]);

		/* Do not load eeprom data on fatal error or suspend */
		ipw_ग_लिखो32(priv, IPW_EEPROM_LOAD_DISABLE, 0);
	पूर्ण अन्यथा अणु
		IPW_DEBUG_INFO("Enabling FW initialization of SRAM\n");

		/* Load eeprom data on fatal error or suspend */
		ipw_ग_लिखो32(priv, IPW_EEPROM_LOAD_DISABLE, 1);
	पूर्ण

	IPW_DEBUG_TRACE("<<\n");
पूर्ण

अटल व्योम ipw_zero_memory(काष्ठा ipw_priv *priv, u32 start, u32 count)
अणु
	count >>= 2;
	अगर (!count)
		वापस;
	_ipw_ग_लिखो32(priv, IPW_AUTOINC_ADDR, start);
	जबतक (count--)
		_ipw_ग_लिखो32(priv, IPW_AUTOINC_DATA, 0);
पूर्ण

अटल अंतरभूत व्योम ipw_fw_dma_reset_command_blocks(काष्ठा ipw_priv *priv)
अणु
	ipw_zero_memory(priv, IPW_SHARED_SRAM_DMA_CONTROL,
			CB_NUMBER_OF_ELEMENTS_SMALL *
			माप(काष्ठा command_block));
पूर्ण

अटल पूर्णांक ipw_fw_dma_enable(काष्ठा ipw_priv *priv)
अणु				/* start dma engine but no transfers yet */

	IPW_DEBUG_FW(">> :\n");

	/* Start the dma */
	ipw_fw_dma_reset_command_blocks(priv);

	/* Write CB base address */
	ipw_ग_लिखो_reg32(priv, IPW_DMA_I_CB_BASE, IPW_SHARED_SRAM_DMA_CONTROL);

	IPW_DEBUG_FW("<< :\n");
	वापस 0;
पूर्ण

अटल व्योम ipw_fw_dma_पात(काष्ठा ipw_priv *priv)
अणु
	u32 control = 0;

	IPW_DEBUG_FW(">> :\n");

	/* set the Stop and Abort bit */
	control = DMA_CONTROL_SMALL_CB_CONST_VALUE | DMA_CB_STOP_AND_ABORT;
	ipw_ग_लिखो_reg32(priv, IPW_DMA_I_DMA_CONTROL, control);
	priv->sram_desc.last_cb_index = 0;

	IPW_DEBUG_FW("<<\n");
पूर्ण

अटल पूर्णांक ipw_fw_dma_ग_लिखो_command_block(काष्ठा ipw_priv *priv, पूर्णांक index,
					  काष्ठा command_block *cb)
अणु
	u32 address =
	    IPW_SHARED_SRAM_DMA_CONTROL +
	    (माप(काष्ठा command_block) * index);
	IPW_DEBUG_FW(">> :\n");

	ipw_ग_लिखो_indirect(priv, address, (u8 *) cb,
			   (पूर्णांक)माप(काष्ठा command_block));

	IPW_DEBUG_FW("<< :\n");
	वापस 0;

पूर्ण

अटल पूर्णांक ipw_fw_dma_kick(काष्ठा ipw_priv *priv)
अणु
	u32 control = 0;
	u32 index = 0;

	IPW_DEBUG_FW(">> :\n");

	क्रम (index = 0; index < priv->sram_desc.last_cb_index; index++)
		ipw_fw_dma_ग_लिखो_command_block(priv, index,
					       &priv->sram_desc.cb_list[index]);

	/* Enable the DMA in the CSR रेजिस्टर */
	ipw_clear_bit(priv, IPW_RESET_REG,
		      IPW_RESET_REG_MASTER_DISABLED |
		      IPW_RESET_REG_STOP_MASTER);

	/* Set the Start bit. */
	control = DMA_CONTROL_SMALL_CB_CONST_VALUE | DMA_CB_START;
	ipw_ग_लिखो_reg32(priv, IPW_DMA_I_DMA_CONTROL, control);

	IPW_DEBUG_FW("<< :\n");
	वापस 0;
पूर्ण

अटल व्योम ipw_fw_dma_dump_command_block(काष्ठा ipw_priv *priv)
अणु
	u32 address;
	u32 रेजिस्टर_value = 0;
	u32 cb_fields_address = 0;

	IPW_DEBUG_FW(">> :\n");
	address = ipw_पढ़ो_reg32(priv, IPW_DMA_I_CURRENT_CB);
	IPW_DEBUG_FW_INFO("Current CB is 0x%x\n", address);

	/* Read the DMA Controlor रेजिस्टर */
	रेजिस्टर_value = ipw_पढ़ो_reg32(priv, IPW_DMA_I_DMA_CONTROL);
	IPW_DEBUG_FW_INFO("IPW_DMA_I_DMA_CONTROL is 0x%x\n", रेजिस्टर_value);

	/* Prपूर्णांक the CB values */
	cb_fields_address = address;
	रेजिस्टर_value = ipw_पढ़ो_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Control Field is 0x%x\n", रेजिस्टर_value);

	cb_fields_address += माप(u32);
	रेजिस्टर_value = ipw_पढ़ो_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Source Field is 0x%x\n", रेजिस्टर_value);

	cb_fields_address += माप(u32);
	रेजिस्टर_value = ipw_पढ़ो_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Destination Field is 0x%x\n",
			  रेजिस्टर_value);

	cb_fields_address += माप(u32);
	रेजिस्टर_value = ipw_पढ़ो_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Status Field is 0x%x\n", रेजिस्टर_value);

	IPW_DEBUG_FW(">> :\n");
पूर्ण

अटल पूर्णांक ipw_fw_dma_command_block_index(काष्ठा ipw_priv *priv)
अणु
	u32 current_cb_address = 0;
	u32 current_cb_index = 0;

	IPW_DEBUG_FW("<< :\n");
	current_cb_address = ipw_पढ़ो_reg32(priv, IPW_DMA_I_CURRENT_CB);

	current_cb_index = (current_cb_address - IPW_SHARED_SRAM_DMA_CONTROL) /
	    माप(काष्ठा command_block);

	IPW_DEBUG_FW_INFO("Current CB index 0x%x address = 0x%X\n",
			  current_cb_index, current_cb_address);

	IPW_DEBUG_FW(">> :\n");
	वापस current_cb_index;

पूर्ण

अटल पूर्णांक ipw_fw_dma_add_command_block(काष्ठा ipw_priv *priv,
					u32 src_address,
					u32 dest_address,
					u32 length,
					पूर्णांक पूर्णांकerrupt_enabled, पूर्णांक is_last)
अणु

	u32 control = CB_VALID | CB_SRC_LE | CB_DEST_LE | CB_SRC_AUTOINC |
	    CB_SRC_IO_GATED | CB_DEST_AUTOINC | CB_SRC_SIZE_LONG |
	    CB_DEST_SIZE_LONG;
	काष्ठा command_block *cb;
	u32 last_cb_element = 0;

	IPW_DEBUG_FW_INFO("src_address=0x%x dest_address=0x%x length=0x%x\n",
			  src_address, dest_address, length);

	अगर (priv->sram_desc.last_cb_index >= CB_NUMBER_OF_ELEMENTS_SMALL)
		वापस -1;

	last_cb_element = priv->sram_desc.last_cb_index;
	cb = &priv->sram_desc.cb_list[last_cb_element];
	priv->sram_desc.last_cb_index++;

	/* Calculate the new CB control word */
	अगर (पूर्णांकerrupt_enabled)
		control |= CB_INT_ENABLED;

	अगर (is_last)
		control |= CB_LAST_VALID;

	control |= length;

	/* Calculate the CB Element's checksum value */
	cb->status = control ^ src_address ^ dest_address;

	/* Copy the Source and Destination addresses */
	cb->dest_addr = dest_address;
	cb->source_addr = src_address;

	/* Copy the Control Word last */
	cb->control = control;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_fw_dma_add_buffer(काष्ठा ipw_priv *priv, dma_addr_t *src_address,
				 पूर्णांक nr, u32 dest_address, u32 len)
अणु
	पूर्णांक ret, i;
	u32 size;

	IPW_DEBUG_FW(">>\n");
	IPW_DEBUG_FW_INFO("nr=%d dest_address=0x%x len=0x%x\n",
			  nr, dest_address, len);

	क्रम (i = 0; i < nr; i++) अणु
		size = min_t(u32, len - i * CB_MAX_LENGTH, CB_MAX_LENGTH);
		ret = ipw_fw_dma_add_command_block(priv, src_address[i],
						   dest_address +
						   i * CB_MAX_LENGTH, size,
						   0, 0);
		अगर (ret) अणु
			IPW_DEBUG_FW_INFO(": Failed\n");
			वापस -1;
		पूर्ण अन्यथा
			IPW_DEBUG_FW_INFO(": Added new cb\n");
	पूर्ण

	IPW_DEBUG_FW("<<\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_fw_dma_रुको(काष्ठा ipw_priv *priv)
अणु
	u32 current_index = 0, previous_index;
	u32 watchकरोg = 0;

	IPW_DEBUG_FW(">> :\n");

	current_index = ipw_fw_dma_command_block_index(priv);
	IPW_DEBUG_FW_INFO("sram_desc.last_cb_index:0x%08X\n",
			  (पूर्णांक)priv->sram_desc.last_cb_index);

	जबतक (current_index < priv->sram_desc.last_cb_index) अणु
		udelay(50);
		previous_index = current_index;
		current_index = ipw_fw_dma_command_block_index(priv);

		अगर (previous_index < current_index) अणु
			watchकरोg = 0;
			जारी;
		पूर्ण
		अगर (++watchकरोg > 400) अणु
			IPW_DEBUG_FW_INFO("Timeout\n");
			ipw_fw_dma_dump_command_block(priv);
			ipw_fw_dma_पात(priv);
			वापस -1;
		पूर्ण
	पूर्ण

	ipw_fw_dma_पात(priv);

	/*Disable the DMA in the CSR रेजिस्टर */
	ipw_set_bit(priv, IPW_RESET_REG,
		    IPW_RESET_REG_MASTER_DISABLED | IPW_RESET_REG_STOP_MASTER);

	IPW_DEBUG_FW("<< dmaWaitSync\n");
	वापस 0;
पूर्ण

अटल व्योम ipw_हटाओ_current_network(काष्ठा ipw_priv *priv)
अणु
	काष्ठा list_head *element, *safe;
	काष्ठा libipw_network *network = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->ieee->lock, flags);
	list_क्रम_each_safe(element, safe, &priv->ieee->network_list) अणु
		network = list_entry(element, काष्ठा libipw_network, list);
		अगर (ether_addr_equal(network->bssid, priv->bssid)) अणु
			list_del(element);
			list_add_tail(&network->list,
				      &priv->ieee->network_मुक्त_list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->ieee->lock, flags);
पूर्ण

/*
 * Check that card is still alive.
 * Reads debug रेजिस्टर from करोमुख्य0.
 * If card is present, pre-defined value should
 * be found there.
 *
 * @param priv
 * @वापस 1 अगर card is present, 0 otherwise
 */
अटल अंतरभूत पूर्णांक ipw_alive(काष्ठा ipw_priv *priv)
अणु
	वापस ipw_पढ़ो32(priv, 0x90) == 0xd55555d5;
पूर्ण

/* समयout in msec, attempted in 10-msec quanta */
अटल पूर्णांक ipw_poll_bit(काष्ठा ipw_priv *priv, u32 addr, u32 mask,
			       पूर्णांक समयout)
अणु
	पूर्णांक i = 0;

	करो अणु
		अगर ((ipw_पढ़ो32(priv, addr) & mask) == mask)
			वापस i;
		mdelay(10);
		i += 10;
	पूर्ण जबतक (i < समयout);

	वापस -ETIME;
पूर्ण

/* These functions load the firmware and micro code क्रम the operation of
 * the ipw hardware.  It assumes the buffer has all the bits क्रम the
 * image and the caller is handling the memory allocation and clean up.
 */

अटल पूर्णांक ipw_stop_master(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc;

	IPW_DEBUG_TRACE(">>\n");
	/* stop master. typical delay - 0 */
	ipw_set_bit(priv, IPW_RESET_REG, IPW_RESET_REG_STOP_MASTER);

	/* समयout is in msec, polled in 10-msec quanta */
	rc = ipw_poll_bit(priv, IPW_RESET_REG,
			  IPW_RESET_REG_MASTER_DISABLED, 100);
	अगर (rc < 0) अणु
		IPW_ERROR("wait for stop master failed after 100ms\n");
		वापस -1;
	पूर्ण

	IPW_DEBUG_INFO("stop master %dms\n", rc);

	वापस rc;
पूर्ण

अटल व्योम ipw_arc_release(काष्ठा ipw_priv *priv)
अणु
	IPW_DEBUG_TRACE(">>\n");
	mdelay(5);

	ipw_clear_bit(priv, IPW_RESET_REG, CBD_RESET_REG_PRINCETON_RESET);

	/* no one knows timing, क्रम safety add some delay */
	mdelay(5);
पूर्ण

काष्ठा fw_chunk अणु
	__le32 address;
	__le32 length;
पूर्ण;

अटल पूर्णांक ipw_load_ucode(काष्ठा ipw_priv *priv, u8 * data, माप_प्रकार len)
अणु
	पूर्णांक rc = 0, i, addr;
	u8 cr = 0;
	__le16 *image;

	image = (__le16 *) data;

	IPW_DEBUG_TRACE(">>\n");

	rc = ipw_stop_master(priv);

	अगर (rc < 0)
		वापस rc;

	क्रम (addr = IPW_SHARED_LOWER_BOUND;
	     addr < IPW_REGISTER_DOMAIN1_END; addr += 4) अणु
		ipw_ग_लिखो32(priv, addr, 0);
	पूर्ण

	/* no ucode (yet) */
	स_रखो(&priv->dino_alive, 0, माप(priv->dino_alive));
	/* destroy DMA queues */
	/* reset sequence */

	ipw_ग_लिखो_reg32(priv, IPW_MEM_HALT_AND_RESET, IPW_BIT_HALT_RESET_ON);
	ipw_arc_release(priv);
	ipw_ग_लिखो_reg32(priv, IPW_MEM_HALT_AND_RESET, IPW_BIT_HALT_RESET_OFF);
	mdelay(1);

	/* reset PHY */
	ipw_ग_लिखो_reg32(priv, IPW_INTERNAL_CMD_EVENT, IPW_BASEBAND_POWER_DOWN);
	mdelay(1);

	ipw_ग_लिखो_reg32(priv, IPW_INTERNAL_CMD_EVENT, 0);
	mdelay(1);

	/* enable ucode store */
	ipw_ग_लिखो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0x0);
	ipw_ग_लिखो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, DINO_ENABLE_CS);
	mdelay(1);

	/* ग_लिखो ucode */
	/*
	 * @bug
	 * Do NOT set indirect address रेजिस्टर once and then
	 * store data to indirect data रेजिस्टर in the loop.
	 * It seems very reasonable, but in this हाल DINO करो not
	 * accept ucode. It is essential to set address each समय.
	 */
	/* load new ipw uCode */
	क्रम (i = 0; i < len / 2; i++)
		ipw_ग_लिखो_reg16(priv, IPW_BASEBAND_CONTROL_STORE,
				le16_to_cpu(image[i]));

	/* enable DINO */
	ipw_ग_लिखो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0);
	ipw_ग_लिखो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, DINO_ENABLE_SYSTEM);

	/* this is where the igx / win driver deveates from the VAP driver. */

	/* रुको क्रम alive response */
	क्रम (i = 0; i < 100; i++) अणु
		/* poll क्रम incoming data */
		cr = ipw_पढ़ो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS);
		अगर (cr & DINO_RXFIFO_DATA)
			अवरोध;
		mdelay(1);
	पूर्ण

	अगर (cr & DINO_RXFIFO_DATA) अणु
		/* alive_command_responce size is NOT multiple of 4 */
		__le32 response_buffer[(माप(priv->dino_alive) + 3) / 4];

		क्रम (i = 0; i < ARRAY_SIZE(response_buffer); i++)
			response_buffer[i] =
			    cpu_to_le32(ipw_पढ़ो_reg32(priv,
						       IPW_BASEBAND_RX_FIFO_READ));
		स_नकल(&priv->dino_alive, response_buffer,
		       माप(priv->dino_alive));
		अगर (priv->dino_alive.alive_command == 1
		    && priv->dino_alive.ucode_valid == 1) अणु
			rc = 0;
			IPW_DEBUG_INFO
			    ("Microcode OK, rev. %d (0x%x) dev. %d (0x%x) "
			     "of %02d/%02d/%02d %02d:%02d\n",
			     priv->dino_alive.software_revision,
			     priv->dino_alive.software_revision,
			     priv->dino_alive.device_identअगरier,
			     priv->dino_alive.device_identअगरier,
			     priv->dino_alive.समय_stamp[0],
			     priv->dino_alive.समय_stamp[1],
			     priv->dino_alive.समय_stamp[2],
			     priv->dino_alive.समय_stamp[3],
			     priv->dino_alive.समय_stamp[4]);
		पूर्ण अन्यथा अणु
			IPW_DEBUG_INFO("Microcode is not alive\n");
			rc = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		IPW_DEBUG_INFO("No alive response from DINO\n");
		rc = -ETIME;
	पूर्ण

	/* disable DINO, otherwise क्रम some reason
	   firmware have problem getting alive resp. */
	ipw_ग_लिखो_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक ipw_load_firmware(काष्ठा ipw_priv *priv, u8 * data, माप_प्रकार len)
अणु
	पूर्णांक ret = -1;
	पूर्णांक offset = 0;
	काष्ठा fw_chunk *chunk;
	पूर्णांक total_nr = 0;
	पूर्णांक i;
	काष्ठा dma_pool *pool;
	व्योम **virts;
	dma_addr_t *phys;

	IPW_DEBUG_TRACE("<< :\n");

	virts = kदो_स्मृति_array(CB_NUMBER_OF_ELEMENTS_SMALL, माप(व्योम *),
			      GFP_KERNEL);
	अगर (!virts)
		वापस -ENOMEM;

	phys = kदो_स्मृति_array(CB_NUMBER_OF_ELEMENTS_SMALL, माप(dma_addr_t),
			     GFP_KERNEL);
	अगर (!phys) अणु
		kमुक्त(virts);
		वापस -ENOMEM;
	पूर्ण
	pool = dma_pool_create("ipw2200", &priv->pci_dev->dev, CB_MAX_LENGTH, 0,
			       0);
	अगर (!pool) अणु
		IPW_ERROR("dma_pool_create failed\n");
		kमुक्त(phys);
		kमुक्त(virts);
		वापस -ENOMEM;
	पूर्ण

	/* Start the Dma */
	ret = ipw_fw_dma_enable(priv);

	/* the DMA is alपढ़ोy पढ़ोy this would be a bug. */
	BUG_ON(priv->sram_desc.last_cb_index > 0);

	करो अणु
		u32 chunk_len;
		u8 *start;
		पूर्णांक size;
		पूर्णांक nr = 0;

		chunk = (काष्ठा fw_chunk *)(data + offset);
		offset += माप(काष्ठा fw_chunk);
		chunk_len = le32_to_cpu(chunk->length);
		start = data + offset;

		nr = (chunk_len + CB_MAX_LENGTH - 1) / CB_MAX_LENGTH;
		क्रम (i = 0; i < nr; i++) अणु
			virts[total_nr] = dma_pool_alloc(pool, GFP_KERNEL,
							 &phys[total_nr]);
			अगर (!virts[total_nr]) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			size = min_t(u32, chunk_len - i * CB_MAX_LENGTH,
				     CB_MAX_LENGTH);
			स_नकल(virts[total_nr], start, size);
			start += size;
			total_nr++;
			/* We करोn't support fw chunk larger than 64*8K */
			BUG_ON(total_nr > CB_NUMBER_OF_ELEMENTS_SMALL);
		पूर्ण

		/* build DMA packet and queue up क्रम sending */
		/* dma to chunk->address, the chunk->length bytes from data +
		 * offeset*/
		/* Dma loading */
		ret = ipw_fw_dma_add_buffer(priv, &phys[total_nr - nr],
					    nr, le32_to_cpu(chunk->address),
					    chunk_len);
		अगर (ret) अणु
			IPW_DEBUG_INFO("dmaAddBuffer Failed\n");
			जाओ out;
		पूर्ण

		offset += chunk_len;
	पूर्ण जबतक (offset < len);

	/* Run the DMA and रुको क्रम the answer */
	ret = ipw_fw_dma_kick(priv);
	अगर (ret) अणु
		IPW_ERROR("dmaKick Failed\n");
		जाओ out;
	पूर्ण

	ret = ipw_fw_dma_रुको(priv);
	अगर (ret) अणु
		IPW_ERROR("dmaWaitSync Failed\n");
		जाओ out;
	पूर्ण
 out:
	क्रम (i = 0; i < total_nr; i++)
		dma_pool_मुक्त(pool, virts[i], phys[i]);

	dma_pool_destroy(pool);
	kमुक्त(phys);
	kमुक्त(virts);

	वापस ret;
पूर्ण

/* stop nic */
अटल पूर्णांक ipw_stop_nic(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc = 0;

	/* stop */
	ipw_ग_लिखो32(priv, IPW_RESET_REG, IPW_RESET_REG_STOP_MASTER);

	rc = ipw_poll_bit(priv, IPW_RESET_REG,
			  IPW_RESET_REG_MASTER_DISABLED, 500);
	अगर (rc < 0) अणु
		IPW_ERROR("wait for reg master disabled failed after 500ms\n");
		वापस rc;
	पूर्ण

	ipw_set_bit(priv, IPW_RESET_REG, CBD_RESET_REG_PRINCETON_RESET);

	वापस rc;
पूर्ण

अटल व्योम ipw_start_nic(काष्ठा ipw_priv *priv)
अणु
	IPW_DEBUG_TRACE(">>\n");

	/* prvHwStartNic  release ARC */
	ipw_clear_bit(priv, IPW_RESET_REG,
		      IPW_RESET_REG_MASTER_DISABLED |
		      IPW_RESET_REG_STOP_MASTER |
		      CBD_RESET_REG_PRINCETON_RESET);

	/* enable घातer management */
	ipw_set_bit(priv, IPW_GP_CNTRL_RW,
		    IPW_GP_CNTRL_BIT_HOST_ALLOWS_STANDBY);

	IPW_DEBUG_TRACE("<<\n");
पूर्ण

अटल पूर्णांक ipw_init_nic(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc;

	IPW_DEBUG_TRACE(">>\n");
	/* reset */
	/*prvHwInitNic */
	/* set "initialization complete" bit to move adapter to D0 state */
	ipw_set_bit(priv, IPW_GP_CNTRL_RW, IPW_GP_CNTRL_BIT_INIT_DONE);

	/* low-level PLL activation */
	ipw_ग_लिखो32(priv, IPW_READ_INT_REGISTER,
		    IPW_BIT_INT_HOST_SRAM_READ_INT_REGISTER);

	/* रुको क्रम घड़ी stabilization */
	rc = ipw_poll_bit(priv, IPW_GP_CNTRL_RW,
			  IPW_GP_CNTRL_BIT_CLOCK_READY, 250);
	अगर (rc < 0)
		IPW_DEBUG_INFO("FAILED wait for clock stablization\n");

	/* निश्चित SW reset */
	ipw_set_bit(priv, IPW_RESET_REG, IPW_RESET_REG_SW_RESET);

	udelay(10);

	/* set "initialization complete" bit to move adapter to D0 state */
	ipw_set_bit(priv, IPW_GP_CNTRL_RW, IPW_GP_CNTRL_BIT_INIT_DONE);

	IPW_DEBUG_TRACE(">>\n");
	वापस 0;
पूर्ण

/* Call this function from process context, it will sleep in request_firmware.
 * Probe is an ok place to call this from.
 */
अटल पूर्णांक ipw_reset_nic(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	IPW_DEBUG_TRACE(">>\n");

	rc = ipw_init_nic(priv);

	spin_lock_irqsave(&priv->lock, flags);
	/* Clear the 'host command active' bit... */
	priv->status &= ~STATUS_HCMD_ACTIVE;
	wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);
	priv->status &= ~(STATUS_SCANNING | STATUS_SCAN_ABORTING);
	wake_up_पूर्णांकerruptible(&priv->रुको_state);
	spin_unlock_irqrestore(&priv->lock, flags);

	IPW_DEBUG_TRACE("<<\n");
	वापस rc;
पूर्ण


काष्ठा ipw_fw अणु
	__le32 ver;
	__le32 boot_size;
	__le32 ucode_size;
	__le32 fw_size;
	u8 data[];
पूर्ण;

अटल पूर्णांक ipw_get_fw(काष्ठा ipw_priv *priv,
		      स्थिर काष्ठा firmware **raw, स्थिर अक्षर *name)
अणु
	काष्ठा ipw_fw *fw;
	पूर्णांक rc;

	/* ask firmware_class module to get the boot firmware off disk */
	rc = request_firmware(raw, name, &priv->pci_dev->dev);
	अगर (rc < 0) अणु
		IPW_ERROR("%s request_firmware failed: Reason %d\n", name, rc);
		वापस rc;
	पूर्ण

	अगर ((*raw)->size < माप(*fw)) अणु
		IPW_ERROR("%s is too small (%zd)\n", name, (*raw)->size);
		वापस -EINVAL;
	पूर्ण

	fw = (व्योम *)(*raw)->data;

	अगर ((*raw)->size < माप(*fw) + le32_to_cpu(fw->boot_size) +
	    le32_to_cpu(fw->ucode_size) + le32_to_cpu(fw->fw_size)) अणु
		IPW_ERROR("%s is too small or corrupt (%zd)\n",
			  name, (*raw)->size);
		वापस -EINVAL;
	पूर्ण

	IPW_DEBUG_INFO("Read firmware '%s' image v%d.%d (%zd bytes)\n",
		       name,
		       le32_to_cpu(fw->ver) >> 16,
		       le32_to_cpu(fw->ver) & 0xff,
		       (*raw)->size - माप(*fw));
	वापस 0;
पूर्ण

#घोषणा IPW_RX_BUF_SIZE (3000)

अटल व्योम ipw_rx_queue_reset(काष्ठा ipw_priv *priv,
				      काष्ठा ipw_rx_queue *rxq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&rxq->lock, flags);

	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);

	/* Fill the rx_used queue with _all_ of the Rx buffers */
	क्रम (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++) अणु
		/* In the reset function, these buffers may have been allocated
		 * to an SKB, so we need to unmap and मुक्त potential storage */
		अगर (rxq->pool[i].skb != शून्य) अणु
			dma_unmap_single(&priv->pci_dev->dev,
					 rxq->pool[i].dma_addr,
					 IPW_RX_BUF_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(rxq->pool[i].skb);
			rxq->pool[i].skb = शून्य;
		पूर्ण
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);
	पूर्ण

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->पढ़ो = rxq->ग_लिखो = 0;
	rxq->मुक्त_count = 0;
	spin_unlock_irqrestore(&rxq->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fw_loaded = 0;
अटल स्थिर काष्ठा firmware *raw = शून्य;

अटल व्योम मुक्त_firmware(व्योम)
अणु
	अगर (fw_loaded) अणु
		release_firmware(raw);
		raw = शून्य;
		fw_loaded = 0;
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा मुक्त_firmware() करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक ipw_load(काष्ठा ipw_priv *priv)
अणु
#अगर_अघोषित CONFIG_PM
	स्थिर काष्ठा firmware *raw = शून्य;
#पूर्ण_अगर
	काष्ठा ipw_fw *fw;
	u8 *boot_img, *ucode_img, *fw_img;
	u8 *name = शून्य;
	पूर्णांक rc = 0, retries = 3;

	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		name = "ipw2200-ibss.fw";
		अवरोध;
#अगर_घोषित CONFIG_IPW2200_MONITOR
	हाल IW_MODE_MONITOR:
		name = "ipw2200-sniffer.fw";
		अवरोध;
#पूर्ण_अगर
	हाल IW_MODE_INFRA:
		name = "ipw2200-bss.fw";
		अवरोध;
	पूर्ण

	अगर (!name) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

#अगर_घोषित CONFIG_PM
	अगर (!fw_loaded) अणु
#पूर्ण_अगर
		rc = ipw_get_fw(priv, &raw, name);
		अगर (rc < 0)
			जाओ error;
#अगर_घोषित CONFIG_PM
	पूर्ण
#पूर्ण_अगर

	fw = (व्योम *)raw->data;
	boot_img = &fw->data[0];
	ucode_img = &fw->data[le32_to_cpu(fw->boot_size)];
	fw_img = &fw->data[le32_to_cpu(fw->boot_size) +
			   le32_to_cpu(fw->ucode_size)];

	अगर (!priv->rxq)
		priv->rxq = ipw_rx_queue_alloc(priv);
	अन्यथा
		ipw_rx_queue_reset(priv, priv->rxq);
	अगर (!priv->rxq) अणु
		IPW_ERROR("Unable to initialize Rx queue\n");
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

      retry:
	/* Ensure पूर्णांकerrupts are disabled */
	ipw_ग_लिखो32(priv, IPW_INTA_MASK_R, ~IPW_INTA_MASK_ALL);
	priv->status &= ~STATUS_INT_ENABLED;

	/* ack pending पूर्णांकerrupts */
	ipw_ग_लिखो32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

	ipw_stop_nic(priv);

	rc = ipw_reset_nic(priv);
	अगर (rc < 0) अणु
		IPW_ERROR("Unable to reset NIC\n");
		जाओ error;
	पूर्ण

	ipw_zero_memory(priv, IPW_NIC_SRAM_LOWER_BOUND,
			IPW_NIC_SRAM_UPPER_BOUND - IPW_NIC_SRAM_LOWER_BOUND);

	/* DMA the initial boot firmware पूर्णांकo the device */
	rc = ipw_load_firmware(priv, boot_img, le32_to_cpu(fw->boot_size));
	अगर (rc < 0) अणु
		IPW_ERROR("Unable to load boot firmware: %d\n", rc);
		जाओ error;
	पूर्ण

	/* kick start the device */
	ipw_start_nic(priv);

	/* रुको क्रम the device to finish its initial startup sequence */
	rc = ipw_poll_bit(priv, IPW_INTA_RW,
			  IPW_INTA_BIT_FW_INITIALIZATION_DONE, 500);
	अगर (rc < 0) अणु
		IPW_ERROR("device failed to boot initial fw image\n");
		जाओ error;
	पूर्ण
	IPW_DEBUG_INFO("initial device response after %dms\n", rc);

	/* ack fw init करोne पूर्णांकerrupt */
	ipw_ग_लिखो32(priv, IPW_INTA_RW, IPW_INTA_BIT_FW_INITIALIZATION_DONE);

	/* DMA the ucode पूर्णांकo the device */
	rc = ipw_load_ucode(priv, ucode_img, le32_to_cpu(fw->ucode_size));
	अगर (rc < 0) अणु
		IPW_ERROR("Unable to load ucode: %d\n", rc);
		जाओ error;
	पूर्ण

	/* stop nic */
	ipw_stop_nic(priv);

	/* DMA bss firmware पूर्णांकo the device */
	rc = ipw_load_firmware(priv, fw_img, le32_to_cpu(fw->fw_size));
	अगर (rc < 0) अणु
		IPW_ERROR("Unable to load firmware: %d\n", rc);
		जाओ error;
	पूर्ण
#अगर_घोषित CONFIG_PM
	fw_loaded = 1;
#पूर्ण_अगर

	ipw_ग_लिखो32(priv, IPW_EEPROM_LOAD_DISABLE, 0);

	rc = ipw_queue_reset(priv);
	अगर (rc < 0) अणु
		IPW_ERROR("Unable to initialize queues\n");
		जाओ error;
	पूर्ण

	/* Ensure पूर्णांकerrupts are disabled */
	ipw_ग_लिखो32(priv, IPW_INTA_MASK_R, ~IPW_INTA_MASK_ALL);
	/* ack pending पूर्णांकerrupts */
	ipw_ग_लिखो32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

	/* kick start the device */
	ipw_start_nic(priv);

	अगर (ipw_पढ़ो32(priv, IPW_INTA_RW) & IPW_INTA_BIT_PARITY_ERROR) अणु
		अगर (retries > 0) अणु
			IPW_WARNING("Parity error.  Retrying init.\n");
			retries--;
			जाओ retry;
		पूर्ण

		IPW_ERROR("TODO: Handle parity error -- schedule restart?\n");
		rc = -EIO;
		जाओ error;
	पूर्ण

	/* रुको क्रम the device */
	rc = ipw_poll_bit(priv, IPW_INTA_RW,
			  IPW_INTA_BIT_FW_INITIALIZATION_DONE, 500);
	अगर (rc < 0) अणु
		IPW_ERROR("device failed to start within 500ms\n");
		जाओ error;
	पूर्ण
	IPW_DEBUG_INFO("device response after %dms\n", rc);

	/* ack fw init करोne पूर्णांकerrupt */
	ipw_ग_लिखो32(priv, IPW_INTA_RW, IPW_INTA_BIT_FW_INITIALIZATION_DONE);

	/* पढ़ो eeprom data */
	priv->eeprom_delay = 1;
	ipw_पढ़ो_eeprom(priv);
	/* initialize the eeprom region of sram */
	ipw_eeprom_init_sram(priv);

	/* enable पूर्णांकerrupts */
	ipw_enable_पूर्णांकerrupts(priv);

	/* Ensure our queue has valid packets */
	ipw_rx_queue_replenish(priv);

	ipw_ग_लिखो32(priv, IPW_RX_READ_INDEX, priv->rxq->पढ़ो);

	/* ack pending पूर्णांकerrupts */
	ipw_ग_लिखो32(priv, IPW_INTA_RW, IPW_INTA_MASK_ALL);

#अगर_अघोषित CONFIG_PM
	release_firmware(raw);
#पूर्ण_अगर
	वापस 0;

      error:
	अगर (priv->rxq) अणु
		ipw_rx_queue_मुक्त(priv, priv->rxq);
		priv->rxq = शून्य;
	पूर्ण
	ipw_tx_queue_मुक्त(priv);
	release_firmware(raw);
#अगर_घोषित CONFIG_PM
	fw_loaded = 0;
	raw = शून्य;
#पूर्ण_अगर

	वापस rc;
पूर्ण

/*
 * DMA services
 *
 * Theory of operation
 *
 * A queue is a circular buffers with 'Read' and 'Write' poपूर्णांकers.
 * 2 empty entries always kept in the buffer to protect from overflow.
 *
 * For Tx queue, there are low mark and high mark limits. If, after queuing
 * the packet क्रम Tx, मुक्त space become < low mark, Tx queue stopped. When
 * reclaiming packets (on 'tx करोne IRQ), अगर मुक्त space become > high mark,
 * Tx queue resumed.
 *
 * The IPW operates with six queues, one receive queue in the device's
 * sram, one transmit queue क्रम sending commands to the device firmware,
 * and four transmit queues क्रम data.
 *
 * The four transmit queues allow क्रम perक्रमming quality of service (qos)
 * transmissions as per the 802.11 protocol.  Currently Linux करोes not
 * provide a mechanism to the user क्रम utilizing prioritized queues, so
 * we only utilize the first data transmit queue (queue1).
 */

/*
 * Driver allocates buffers of this size क्रम Rx
 */

/*
 * ipw_rx_queue_space - Return number of मुक्त slots available in queue.
 */
अटल पूर्णांक ipw_rx_queue_space(स्थिर काष्ठा ipw_rx_queue *q)
अणु
	पूर्णांक s = q->पढ़ो - q->ग_लिखो;
	अगर (s <= 0)
		s += RX_QUEUE_SIZE;
	/* keep some buffer to not confuse full and empty queue */
	s -= 2;
	अगर (s < 0)
		s = 0;
	वापस s;
पूर्ण

अटल अंतरभूत पूर्णांक ipw_tx_queue_space(स्थिर काष्ठा clx2_queue *q)
अणु
	पूर्णांक s = q->last_used - q->first_empty;
	अगर (s <= 0)
		s += q->n_bd;
	s -= 2;			/* keep some reserve to not confuse empty and full situations */
	अगर (s < 0)
		s = 0;
	वापस s;
पूर्ण

अटल अंतरभूत पूर्णांक ipw_queue_inc_wrap(पूर्णांक index, पूर्णांक n_bd)
अणु
	वापस (++index == n_bd) ? 0 : index;
पूर्ण

/*
 * Initialize common DMA queue काष्ठाure
 *
 * @param q                queue to init
 * @param count            Number of BD's to allocate. Should be घातer of 2
 * @param पढ़ो_रेजिस्टर    Address क्रम 'read' रेजिस्टर
 *                         (not offset within BAR, full address)
 * @param ग_लिखो_रेजिस्टर   Address क्रम 'write' रेजिस्टर
 *                         (not offset within BAR, full address)
 * @param base_रेजिस्टर    Address क्रम 'base' रेजिस्टर
 *                         (not offset within BAR, full address)
 * @param size             Address क्रम 'size' रेजिस्टर
 *                         (not offset within BAR, full address)
 */
अटल व्योम ipw_queue_init(काष्ठा ipw_priv *priv, काष्ठा clx2_queue *q,
			   पूर्णांक count, u32 पढ़ो, u32 ग_लिखो, u32 base, u32 size)
अणु
	q->n_bd = count;

	q->low_mark = q->n_bd / 4;
	अगर (q->low_mark < 4)
		q->low_mark = 4;

	q->high_mark = q->n_bd / 8;
	अगर (q->high_mark < 2)
		q->high_mark = 2;

	q->first_empty = q->last_used = 0;
	q->reg_r = पढ़ो;
	q->reg_w = ग_लिखो;

	ipw_ग_लिखो32(priv, base, q->dma_addr);
	ipw_ग_लिखो32(priv, size, count);
	ipw_ग_लिखो32(priv, पढ़ो, 0);
	ipw_ग_लिखो32(priv, ग_लिखो, 0);

	_ipw_पढ़ो32(priv, 0x90);
पूर्ण

अटल पूर्णांक ipw_queue_tx_init(काष्ठा ipw_priv *priv,
			     काष्ठा clx2_tx_queue *q,
			     पूर्णांक count, u32 पढ़ो, u32 ग_लिखो, u32 base, u32 size)
अणु
	काष्ठा pci_dev *dev = priv->pci_dev;

	q->txb = kदो_स्मृति_array(count, माप(q->txb[0]), GFP_KERNEL);
	अगर (!q->txb)
		वापस -ENOMEM;

	q->bd =
	    dma_alloc_coherent(&dev->dev, माप(q->bd[0]) * count,
			       &q->q.dma_addr, GFP_KERNEL);
	अगर (!q->bd) अणु
		IPW_ERROR("pci_alloc_consistent(%zd) failed\n",
			  माप(q->bd[0]) * count);
		kमुक्त(q->txb);
		q->txb = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ipw_queue_init(priv, &q->q, count, पढ़ो, ग_लिखो, base, size);
	वापस 0;
पूर्ण

/*
 * Free one TFD, those at index [txq->q.last_used].
 * Do NOT advance any indexes
 *
 * @param dev
 * @param txq
 */
अटल व्योम ipw_queue_tx_मुक्त_tfd(काष्ठा ipw_priv *priv,
				  काष्ठा clx2_tx_queue *txq)
अणु
	काष्ठा tfd_frame *bd = &txq->bd[txq->q.last_used];
	काष्ठा pci_dev *dev = priv->pci_dev;
	पूर्णांक i;

	/* classअगरy bd */
	अगर (bd->control_flags.message_type == TX_HOST_COMMAND_TYPE)
		/* nothing to cleanup after क्रम host commands */
		वापस;

	/* sanity check */
	अगर (le32_to_cpu(bd->u.data.num_chunks) > NUM_TFD_CHUNKS) अणु
		IPW_ERROR("Too many chunks: %i\n",
			  le32_to_cpu(bd->u.data.num_chunks));
		/* @toकरो issue fatal error, it is quite serious situation */
		वापस;
	पूर्ण

	/* unmap chunks अगर any */
	क्रम (i = 0; i < le32_to_cpu(bd->u.data.num_chunks); i++) अणु
		dma_unmap_single(&dev->dev,
				 le32_to_cpu(bd->u.data.chunk_ptr[i]),
				 le16_to_cpu(bd->u.data.chunk_len[i]),
				 DMA_TO_DEVICE);
		अगर (txq->txb[txq->q.last_used]) अणु
			libipw_txb_मुक्त(txq->txb[txq->q.last_used]);
			txq->txb[txq->q.last_used] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Deallocate DMA queue.
 *
 * Empty queue by removing and destroying all BD's.
 * Free all buffers.
 *
 * @param dev
 * @param q
 */
अटल व्योम ipw_queue_tx_मुक्त(काष्ठा ipw_priv *priv, काष्ठा clx2_tx_queue *txq)
अणु
	काष्ठा clx2_queue *q = &txq->q;
	काष्ठा pci_dev *dev = priv->pci_dev;

	अगर (q->n_bd == 0)
		वापस;

	/* first, empty all BD's */
	क्रम (; q->first_empty != q->last_used;
	     q->last_used = ipw_queue_inc_wrap(q->last_used, q->n_bd)) अणु
		ipw_queue_tx_मुक्त_tfd(priv, txq);
	पूर्ण

	/* मुक्त buffers beदीर्घing to queue itself */
	dma_मुक्त_coherent(&dev->dev, माप(txq->bd[0]) * q->n_bd, txq->bd,
			  q->dma_addr);
	kमुक्त(txq->txb);

	/* 0 fill whole काष्ठाure */
	स_रखो(txq, 0, माप(*txq));
पूर्ण

/*
 * Destroy all DMA queues and काष्ठाures
 *
 * @param priv
 */
अटल व्योम ipw_tx_queue_मुक्त(काष्ठा ipw_priv *priv)
अणु
	/* Tx CMD queue */
	ipw_queue_tx_मुक्त(priv, &priv->txq_cmd);

	/* Tx queues */
	ipw_queue_tx_मुक्त(priv, &priv->txq[0]);
	ipw_queue_tx_मुक्त(priv, &priv->txq[1]);
	ipw_queue_tx_मुक्त(priv, &priv->txq[2]);
	ipw_queue_tx_मुक्त(priv, &priv->txq[3]);
पूर्ण

अटल व्योम ipw_create_bssid(काष्ठा ipw_priv *priv, u8 * bssid)
अणु
	/* First 3 bytes are manufacturer */
	bssid[0] = priv->mac_addr[0];
	bssid[1] = priv->mac_addr[1];
	bssid[2] = priv->mac_addr[2];

	/* Last bytes are अक्रमom */
	get_अक्रमom_bytes(&bssid[3], ETH_ALEN - 3);

	bssid[0] &= 0xfe;	/* clear multicast bit */
	bssid[0] |= 0x02;	/* set local assignment bit (IEEE802) */
पूर्ण

अटल u8 ipw_add_station(काष्ठा ipw_priv *priv, u8 * bssid)
अणु
	काष्ठा ipw_station_entry entry;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_stations; i++) अणु
		अगर (ether_addr_equal(priv->stations[i], bssid)) अणु
			/* Another node is active in network */
			priv->missed_adhoc_beacons = 0;
			अगर (!(priv->config & CFG_STATIC_CHANNEL))
				/* when other nodes drop out, we drop out */
				priv->config &= ~CFG_ADHOC_PERSIST;

			वापस i;
		पूर्ण
	पूर्ण

	अगर (i == MAX_STATIONS)
		वापस IPW_INVALID_STATION;

	IPW_DEBUG_SCAN("Adding AdHoc station: %pM\n", bssid);

	entry.reserved = 0;
	entry.support_mode = 0;
	स_नकल(entry.mac_addr, bssid, ETH_ALEN);
	स_नकल(priv->stations[i], bssid, ETH_ALEN);
	ipw_ग_लिखो_direct(priv, IPW_STATION_TABLE_LOWER + i * माप(entry),
			 &entry, माप(entry));
	priv->num_stations++;

	वापस i;
पूर्ण

अटल u8 ipw_find_station(काष्ठा ipw_priv *priv, u8 * bssid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_stations; i++)
		अगर (ether_addr_equal(priv->stations[i], bssid))
			वापस i;

	वापस IPW_INVALID_STATION;
पूर्ण

अटल व्योम ipw_send_disassociate(काष्ठा ipw_priv *priv, पूर्णांक quiet)
अणु
	पूर्णांक err;

	अगर (priv->status & STATUS_ASSOCIATING) अणु
		IPW_DEBUG_ASSOC("Disassociating while associating.\n");
		schedule_work(&priv->disassociate);
		वापस;
	पूर्ण

	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		IPW_DEBUG_ASSOC("Disassociating while not associated.\n");
		वापस;
	पूर्ण

	IPW_DEBUG_ASSOC("Disassociation attempt from %pM "
			"on channel %d.\n",
			priv->assoc_request.bssid,
			priv->assoc_request.channel);

	priv->status &= ~(STATUS_ASSOCIATING | STATUS_ASSOCIATED);
	priv->status |= STATUS_DISASSOCIATING;

	अगर (quiet)
		priv->assoc_request.assoc_type = HC_DISASSOC_QUIET;
	अन्यथा
		priv->assoc_request.assoc_type = HC_DISASSOCIATE;

	err = ipw_send_associate(priv, &priv->assoc_request);
	अगर (err) अणु
		IPW_DEBUG_HC("Attempt to send [dis]associate command "
			     "failed.\n");
		वापस;
	पूर्ण

पूर्ण

अटल पूर्णांक ipw_disassociate(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;
	अगर (!(priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)))
		वापस 0;
	ipw_send_disassociate(data, 0);
	netअगर_carrier_off(priv->net_dev);
	वापस 1;
पूर्ण

अटल व्योम ipw_bg_disassociate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, disassociate);
	mutex_lock(&priv->mutex);
	ipw_disassociate(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_प्रणाली_config(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, प्रणाली_config);

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	अगर (priv->prom_net_dev && netअगर_running(priv->prom_net_dev)) अणु
		priv->sys_config.accept_all_data_frames = 1;
		priv->sys_config.accept_non_directed_frames = 1;
		priv->sys_config.accept_all_mgmt_bcpr = 1;
		priv->sys_config.accept_all_mgmt_frames = 1;
	पूर्ण
#पूर्ण_अगर

	ipw_send_प्रणाली_config(priv);
पूर्ण

काष्ठा ipw_status_code अणु
	u16 status;
	स्थिर अक्षर *reason;
पूर्ण;

अटल स्थिर काष्ठा ipw_status_code ipw_status_codes[] = अणु
	अणु0x00, "Successful"पूर्ण,
	अणु0x01, "Unspecified failure"पूर्ण,
	अणु0x0A, "Cannot support all requested capabilities in the "
	 "Capability information field"पूर्ण,
	अणु0x0B, "Reassociation denied due to inability to confirm that "
	 "association exists"पूर्ण,
	अणु0x0C, "Association denied due to reason outside the scope of this "
	 "standard"पूर्ण,
	अणु0x0D,
	 "Responding station does not support the specified authentication "
	 "algorithm"पूर्ण,
	अणु0x0E,
	 "Received an Authentication frame with authentication sequence "
	 "transaction sequence number out of expected sequence"पूर्ण,
	अणु0x0F, "Authentication rejected because of challenge failure"पूर्ण,
	अणु0x10, "Authentication rejected due to timeout waiting for next "
	 "frame in sequence"पूर्ण,
	अणु0x11, "Association denied because AP is unable to handle additional "
	 "associated stations"पूर्ण,
	अणु0x12,
	 "Association denied due to requesting station not supporting all "
	 "of the datarates in the BSSBasicServiceSet Parameter"पूर्ण,
	अणु0x13,
	 "Association denied due to requesting station not supporting "
	 "short preamble operation"पूर्ण,
	अणु0x14,
	 "Association denied due to requesting station not supporting "
	 "PBCC encoding"पूर्ण,
	अणु0x15,
	 "Association denied due to requesting station not supporting "
	 "channel agility"पूर्ण,
	अणु0x19,
	 "Association denied due to requesting station not supporting "
	 "short slot operation"पूर्ण,
	अणु0x1A,
	 "Association denied due to requesting station not supporting "
	 "DSSS-OFDM operation"पूर्ण,
	अणु0x28, "Invalid Information Element"पूर्ण,
	अणु0x29, "Group Cipher is not valid"पूर्ण,
	अणु0x2A, "Pairwise Cipher is not valid"पूर्ण,
	अणु0x2B, "AKMP is not valid"पूर्ण,
	अणु0x2C, "Unsupported RSN IE version"पूर्ण,
	अणु0x2D, "Invalid RSN IE Capabilities"पूर्ण,
	अणु0x2E, "Cipher suite is rejected per security policy"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *ipw_get_status_code(u16 status)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(ipw_status_codes); i++)
		अगर (ipw_status_codes[i].status == (status & 0xff))
			वापस ipw_status_codes[i].reason;
	वापस "Unknown status value.";
पूर्ण

अटल अंतरभूत व्योम average_init(काष्ठा average *avg)
अणु
	स_रखो(avg, 0, माप(*avg));
पूर्ण

#घोषणा DEPTH_RSSI 8
#घोषणा DEPTH_NOISE 16
अटल s16 exponential_average(s16 prev_avg, s16 val, u8 depth)
अणु
	वापस ((depth-1)*prev_avg +  val)/depth;
पूर्ण

अटल व्योम average_add(काष्ठा average *avg, s16 val)
अणु
	avg->sum -= avg->entries[avg->pos];
	avg->sum += val;
	avg->entries[avg->pos++] = val;
	अगर (unlikely(avg->pos == AVG_ENTRIES)) अणु
		avg->init = 1;
		avg->pos = 0;
	पूर्ण
पूर्ण

अटल s16 average_value(काष्ठा average *avg)
अणु
	अगर (!unlikely(avg->init)) अणु
		अगर (avg->pos)
			वापस avg->sum / avg->pos;
		वापस 0;
	पूर्ण

	वापस avg->sum / AVG_ENTRIES;
पूर्ण

अटल व्योम ipw_reset_stats(काष्ठा ipw_priv *priv)
अणु
	u32 len = माप(u32);

	priv->quality = 0;

	average_init(&priv->average_missed_beacons);
	priv->exp_avg_rssi = -60;
	priv->exp_avg_noise = -85 + 0x100;

	priv->last_rate = 0;
	priv->last_missed_beacons = 0;
	priv->last_rx_packets = 0;
	priv->last_tx_packets = 0;
	priv->last_tx_failures = 0;

	/* Firmware managed, reset only when NIC is restarted, so we have to
	 * normalize on the current value */
	ipw_get_ordinal(priv, IPW_ORD_STAT_RX_ERR_CRC,
			&priv->last_rx_err, &len);
	ipw_get_ordinal(priv, IPW_ORD_STAT_TX_FAILURE,
			&priv->last_tx_failures, &len);

	/* Driver managed, reset with each association */
	priv->missed_adhoc_beacons = 0;
	priv->missed_beacons = 0;
	priv->tx_packets = 0;
	priv->rx_packets = 0;

पूर्ण

अटल u32 ipw_get_max_rate(काष्ठा ipw_priv *priv)
अणु
	u32 i = 0x80000000;
	u32 mask = priv->rates_mask;
	/* If currently associated in B mode, restrict the maximum
	 * rate match to B rates */
	अगर (priv->assoc_request.ieee_mode == IPW_B_MODE)
		mask &= LIBIPW_CCK_RATES_MASK;

	/* TODO: Verअगरy that the rate is supported by the current rates
	 * list. */

	जबतक (i && !(mask & i))
		i >>= 1;
	चयन (i) अणु
	हाल LIBIPW_CCK_RATE_1MB_MASK:
		वापस 1000000;
	हाल LIBIPW_CCK_RATE_2MB_MASK:
		वापस 2000000;
	हाल LIBIPW_CCK_RATE_5MB_MASK:
		वापस 5500000;
	हाल LIBIPW_OFDM_RATE_6MB_MASK:
		वापस 6000000;
	हाल LIBIPW_OFDM_RATE_9MB_MASK:
		वापस 9000000;
	हाल LIBIPW_CCK_RATE_11MB_MASK:
		वापस 11000000;
	हाल LIBIPW_OFDM_RATE_12MB_MASK:
		वापस 12000000;
	हाल LIBIPW_OFDM_RATE_18MB_MASK:
		वापस 18000000;
	हाल LIBIPW_OFDM_RATE_24MB_MASK:
		वापस 24000000;
	हाल LIBIPW_OFDM_RATE_36MB_MASK:
		वापस 36000000;
	हाल LIBIPW_OFDM_RATE_48MB_MASK:
		वापस 48000000;
	हाल LIBIPW_OFDM_RATE_54MB_MASK:
		वापस 54000000;
	पूर्ण

	अगर (priv->ieee->mode == IEEE_B)
		वापस 11000000;
	अन्यथा
		वापस 54000000;
पूर्ण

अटल u32 ipw_get_current_rate(काष्ठा ipw_priv *priv)
अणु
	u32 rate, len = माप(rate);
	पूर्णांक err;

	अगर (!(priv->status & STATUS_ASSOCIATED))
		वापस 0;

	अगर (priv->tx_packets > IPW_REAL_RATE_RX_PACKET_THRESHOLD) अणु
		err = ipw_get_ordinal(priv, IPW_ORD_STAT_TX_CURR_RATE, &rate,
				      &len);
		अगर (err) अणु
			IPW_DEBUG_INFO("failed querying ordinals.\n");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		वापस ipw_get_max_rate(priv);

	चयन (rate) अणु
	हाल IPW_TX_RATE_1MB:
		वापस 1000000;
	हाल IPW_TX_RATE_2MB:
		वापस 2000000;
	हाल IPW_TX_RATE_5MB:
		वापस 5500000;
	हाल IPW_TX_RATE_6MB:
		वापस 6000000;
	हाल IPW_TX_RATE_9MB:
		वापस 9000000;
	हाल IPW_TX_RATE_11MB:
		वापस 11000000;
	हाल IPW_TX_RATE_12MB:
		वापस 12000000;
	हाल IPW_TX_RATE_18MB:
		वापस 18000000;
	हाल IPW_TX_RATE_24MB:
		वापस 24000000;
	हाल IPW_TX_RATE_36MB:
		वापस 36000000;
	हाल IPW_TX_RATE_48MB:
		वापस 48000000;
	हाल IPW_TX_RATE_54MB:
		वापस 54000000;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा IPW_STATS_INTERVAL (2 * HZ)
अटल व्योम ipw_gather_stats(काष्ठा ipw_priv *priv)
अणु
	u32 rx_err, rx_err_delta, rx_packets_delta;
	u32 tx_failures, tx_failures_delta, tx_packets_delta;
	u32 missed_beacons_percent, missed_beacons_delta;
	u32 quality = 0;
	u32 len = माप(u32);
	s16 rssi;
	u32 beacon_quality, संकेत_quality, tx_quality, rx_quality,
	    rate_quality;
	u32 max_rate;

	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		priv->quality = 0;
		वापस;
	पूर्ण

	/* Update the statistics */
	ipw_get_ordinal(priv, IPW_ORD_STAT_MISSED_BEACONS,
			&priv->missed_beacons, &len);
	missed_beacons_delta = priv->missed_beacons - priv->last_missed_beacons;
	priv->last_missed_beacons = priv->missed_beacons;
	अगर (priv->assoc_request.beacon_पूर्णांकerval) अणु
		missed_beacons_percent = missed_beacons_delta *
		    (HZ * le16_to_cpu(priv->assoc_request.beacon_पूर्णांकerval)) /
		    (IPW_STATS_INTERVAL * 10);
	पूर्ण अन्यथा अणु
		missed_beacons_percent = 0;
	पूर्ण
	average_add(&priv->average_missed_beacons, missed_beacons_percent);

	ipw_get_ordinal(priv, IPW_ORD_STAT_RX_ERR_CRC, &rx_err, &len);
	rx_err_delta = rx_err - priv->last_rx_err;
	priv->last_rx_err = rx_err;

	ipw_get_ordinal(priv, IPW_ORD_STAT_TX_FAILURE, &tx_failures, &len);
	tx_failures_delta = tx_failures - priv->last_tx_failures;
	priv->last_tx_failures = tx_failures;

	rx_packets_delta = priv->rx_packets - priv->last_rx_packets;
	priv->last_rx_packets = priv->rx_packets;

	tx_packets_delta = priv->tx_packets - priv->last_tx_packets;
	priv->last_tx_packets = priv->tx_packets;

	/* Calculate quality based on the following:
	 *
	 * Missed beacon: 100% = 0, 0% = 70% missed
	 * Rate: 60% = 1Mbs, 100% = Max
	 * Rx and Tx errors represent a straight % of total Rx/Tx
	 * RSSI: 100% = > -50,  0% = < -80
	 * Rx errors: 100% = 0, 0% = 50% missed
	 *
	 * The lowest computed quality is used.
	 *
	 */
#घोषणा BEACON_THRESHOLD 5
	beacon_quality = 100 - missed_beacons_percent;
	अगर (beacon_quality < BEACON_THRESHOLD)
		beacon_quality = 0;
	अन्यथा
		beacon_quality = (beacon_quality - BEACON_THRESHOLD) * 100 /
		    (100 - BEACON_THRESHOLD);
	IPW_DEBUG_STATS("Missed beacon: %3d%% (%d%%)\n",
			beacon_quality, missed_beacons_percent);

	priv->last_rate = ipw_get_current_rate(priv);
	max_rate = ipw_get_max_rate(priv);
	rate_quality = priv->last_rate * 40 / max_rate + 60;
	IPW_DEBUG_STATS("Rate quality : %3d%% (%dMbs)\n",
			rate_quality, priv->last_rate / 1000000);

	अगर (rx_packets_delta > 100 && rx_packets_delta + rx_err_delta)
		rx_quality = 100 - (rx_err_delta * 100) /
		    (rx_packets_delta + rx_err_delta);
	अन्यथा
		rx_quality = 100;
	IPW_DEBUG_STATS("Rx quality   : %3d%% (%u errors, %u packets)\n",
			rx_quality, rx_err_delta, rx_packets_delta);

	अगर (tx_packets_delta > 100 && tx_packets_delta + tx_failures_delta)
		tx_quality = 100 - (tx_failures_delta * 100) /
		    (tx_packets_delta + tx_failures_delta);
	अन्यथा
		tx_quality = 100;
	IPW_DEBUG_STATS("Tx quality   : %3d%% (%u errors, %u packets)\n",
			tx_quality, tx_failures_delta, tx_packets_delta);

	rssi = priv->exp_avg_rssi;
	संकेत_quality =
	    (100 *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) -
	     (priv->ieee->perfect_rssi - rssi) *
	     (15 * (priv->ieee->perfect_rssi - priv->ieee->worst_rssi) +
	      62 * (priv->ieee->perfect_rssi - rssi))) /
	    ((priv->ieee->perfect_rssi - priv->ieee->worst_rssi) *
	     (priv->ieee->perfect_rssi - priv->ieee->worst_rssi));
	अगर (संकेत_quality > 100)
		संकेत_quality = 100;
	अन्यथा अगर (संकेत_quality < 1)
		संकेत_quality = 0;

	IPW_DEBUG_STATS("Signal level : %3d%% (%d dBm)\n",
			संकेत_quality, rssi);

	quality = min(rx_quality, संकेत_quality);
	quality = min(tx_quality, quality);
	quality = min(rate_quality, quality);
	quality = min(beacon_quality, quality);
	अगर (quality == beacon_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to missed beacons.\n",
				quality);
	अगर (quality == rate_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to rate quality.\n",
				quality);
	अगर (quality == tx_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to Tx quality.\n",
				quality);
	अगर (quality == rx_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to Rx quality.\n",
				quality);
	अगर (quality == संकेत_quality)
		IPW_DEBUG_STATS("Quality (%d%%): Clamped to signal quality.\n",
				quality);

	priv->quality = quality;

	schedule_delayed_work(&priv->gather_stats, IPW_STATS_INTERVAL);
पूर्ण

अटल व्योम ipw_bg_gather_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, gather_stats.work);
	mutex_lock(&priv->mutex);
	ipw_gather_stats(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

/* Missed beacon behavior:
 * 1st missed -> roaming_threshold, just रुको, करोn't करो any scan/roam.
 * roaming_threshold -> disassociate_threshold, scan and roam क्रम better संकेत.
 * Above disassociate threshold, give up and stop scanning.
 * Roaming is disabled अगर disassociate_threshold <= roaming_threshold  */
अटल व्योम ipw_handle_missed_beacon(काष्ठा ipw_priv *priv,
					    पूर्णांक missed_count)
अणु
	priv->notअगर_missed_beacons = missed_count;

	अगर (missed_count > priv->disassociate_threshold &&
	    priv->status & STATUS_ASSOCIATED) अणु
		/* If associated and we've hit the missed
		 * beacon threshold, disassociate, turn
		 * off roaming, and पात any active scans */
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
			  IPW_DL_STATE | IPW_DL_ASSOC,
			  "Missed beacon: %d - disassociate\n", missed_count);
		priv->status &= ~STATUS_ROAMING;
		अगर (priv->status & STATUS_SCANNING) अणु
			IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
				  IPW_DL_STATE,
				  "Aborting scan with missed beacon.\n");
			schedule_work(&priv->पात_scan);
		पूर्ण

		schedule_work(&priv->disassociate);
		वापस;
	पूर्ण

	अगर (priv->status & STATUS_ROAMING) अणु
		/* If we are currently roaming, then just
		 * prपूर्णांक a debug statement... */
		IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
			  "Missed beacon: %d - roam in progress\n",
			  missed_count);
		वापस;
	पूर्ण

	अगर (roaming &&
	    (missed_count > priv->roaming_threshold &&
	     missed_count <= priv->disassociate_threshold)) अणु
		/* If we are not alपढ़ोy roaming, set the ROAM
		 * bit in the status and kick off a scan.
		 * This can happen several बार beक्रमe we reach
		 * disassociate_threshold. */
		IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
			  "Missed beacon: %d - initiate "
			  "roaming\n", missed_count);
		अगर (!(priv->status & STATUS_ROAMING)) अणु
			priv->status |= STATUS_ROAMING;
			अगर (!(priv->status & STATUS_SCANNING))
				schedule_delayed_work(&priv->request_scan, 0);
		पूर्ण
		वापस;
	पूर्ण

	अगर (priv->status & STATUS_SCANNING &&
	    missed_count > IPW_MB_SCAN_CANCEL_THRESHOLD) अणु
		/* Stop scan to keep fw from getting
		 * stuck (only अगर we aren't roaming --
		 * otherwise we'll never scan more than 2 or 3
		 * channels..) */
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF | IPW_DL_STATE,
			  "Aborting scan with missed beacon.\n");
		schedule_work(&priv->पात_scan);
	पूर्ण

	IPW_DEBUG_NOTIF("Missed beacon: %d\n", missed_count);
पूर्ण

अटल व्योम ipw_scan_event(काष्ठा work_काष्ठा *work)
अणु
	जोड़ iwreq_data wrqu;

	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, scan_event.work);

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(priv->net_dev, SIOCGIWSCAN, &wrqu, शून्य);
पूर्ण

अटल व्योम handle_scan_event(काष्ठा ipw_priv *priv)
अणु
	/* Only userspace-requested scan completion events go out immediately */
	अगर (!priv->user_requested_scan) अणु
		schedule_delayed_work(&priv->scan_event,
				      round_jअगरfies_relative(msecs_to_jअगरfies(4000)));
	पूर्ण अन्यथा अणु
		priv->user_requested_scan = 0;
		mod_delayed_work(प्रणाली_wq, &priv->scan_event, 0);
	पूर्ण
पूर्ण

/*
 * Handle host notअगरication packet.
 * Called from पूर्णांकerrupt routine
 */
अटल व्योम ipw_rx_notअगरication(काष्ठा ipw_priv *priv,
				       काष्ठा ipw_rx_notअगरication *notअगर)
अणु
	u16 size = le16_to_cpu(notअगर->size);

	IPW_DEBUG_NOTIF("type = %i (%d bytes)\n", notअगर->subtype, size);

	चयन (notअगर->subtype) अणु
	हाल HOST_NOTIFICATION_STATUS_ASSOCIATED:अणु
			काष्ठा notअगर_association *assoc = &notअगर->u.assoc;

			चयन (assoc->state) अणु
			हाल CMAS_ASSOCIATED:अणु
					IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
						  IPW_DL_ASSOC,
						  "associated: '%*pE' %pM\n",
						  priv->essid_len, priv->essid,
						  priv->bssid);

					चयन (priv->ieee->iw_mode) अणु
					हाल IW_MODE_INFRA:
						स_नकल(priv->ieee->bssid,
						       priv->bssid, ETH_ALEN);
						अवरोध;

					हाल IW_MODE_ADHOC:
						स_नकल(priv->ieee->bssid,
						       priv->bssid, ETH_ALEN);

						/* clear out the station table */
						priv->num_stations = 0;

						IPW_DEBUG_ASSOC
						    ("queueing adhoc check\n");
						schedule_delayed_work(
							&priv->adhoc_check,
							le16_to_cpu(priv->
							assoc_request.
							beacon_पूर्णांकerval));
						अवरोध;
					पूर्ण

					priv->status &= ~STATUS_ASSOCIATING;
					priv->status |= STATUS_ASSOCIATED;
					schedule_work(&priv->प्रणाली_config);

#अगर_घोषित CONFIG_IPW2200_QOS
#घोषणा IPW_GET_PACKET_STYPE(x) WLAN_FC_GET_STYPE( \
			 le16_to_cpu(((काष्ठा ieee80211_hdr *)(x))->frame_control))
					अगर ((priv->status & STATUS_AUTH) &&
					    (IPW_GET_PACKET_STYPE(&notअगर->u.raw)
					     == IEEE80211_STYPE_ASSOC_RESP)) अणु
						अगर ((माप
						     (काष्ठा
						      libipw_assoc_response)
						     <= size)
						    && (size <= 2314)) अणु
							काष्ठा
							libipw_rx_stats
							    stats = अणु
								.len = size - 1,
							पूर्ण;

							IPW_DEBUG_QOS
							    ("QoS Associate "
							     "size %d\n", size);
							libipw_rx_mgt(priv->
									 ieee,
									 (काष्ठा
									  libipw_hdr_4addr
									  *)
									 &notअगर->u.raw, &stats);
						पूर्ण
					पूर्ण
#पूर्ण_अगर

					schedule_work(&priv->link_up);

					अवरोध;
				पूर्ण

			हाल CMAS_AUTHENTICATED:अणु
					अगर (priv->
					    status & (STATUS_ASSOCIATED |
						      STATUS_AUTH)) अणु
						काष्ठा notअगर_authenticate *auth
						    = &notअगर->u.auth;
						IPW_DEBUG(IPW_DL_NOTIF |
							  IPW_DL_STATE |
							  IPW_DL_ASSOC,
							  "deauthenticated: '%*pE' %pM: (0x%04X) - %s\n",
							  priv->essid_len,
							  priv->essid,
							  priv->bssid,
							  le16_to_cpu(auth->status),
							  ipw_get_status_code
							  (le16_to_cpu
							   (auth->status)));

						priv->status &=
						    ~(STATUS_ASSOCIATING |
						      STATUS_AUTH |
						      STATUS_ASSOCIATED);

						schedule_work(&priv->link_करोwn);
						अवरोध;
					पूर्ण

					IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
						  IPW_DL_ASSOC,
						  "authenticated: '%*pE' %pM\n",
						  priv->essid_len, priv->essid,
						  priv->bssid);
					अवरोध;
				पूर्ण

			हाल CMAS_INIT:अणु
					अगर (priv->status & STATUS_AUTH) अणु
						काष्ठा
						    libipw_assoc_response
						*resp;
						resp =
						    (काष्ठा
						     libipw_assoc_response
						     *)&notअगर->u.raw;
						IPW_DEBUG(IPW_DL_NOTIF |
							  IPW_DL_STATE |
							  IPW_DL_ASSOC,
							  "association failed (0x%04X): %s\n",
							  le16_to_cpu(resp->status),
							  ipw_get_status_code
							  (le16_to_cpu
							   (resp->status)));
					पूर्ण

					IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
						  IPW_DL_ASSOC,
						  "disassociated: '%*pE' %pM\n",
						  priv->essid_len, priv->essid,
						  priv->bssid);

					priv->status &=
					    ~(STATUS_DISASSOCIATING |
					      STATUS_ASSOCIATING |
					      STATUS_ASSOCIATED | STATUS_AUTH);
					अगर (priv->assoc_network
					    && (priv->assoc_network->
						capability &
						WLAN_CAPABILITY_IBSS))
						ipw_हटाओ_current_network
						    (priv);

					schedule_work(&priv->link_करोwn);

					अवरोध;
				पूर्ण

			हाल CMAS_RX_ASSOC_RESP:
				अवरोध;

			शेष:
				IPW_ERROR("assoc: unknown (%d)\n",
					  assoc->state);
				अवरोध;
			पूर्ण

			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_AUTHENTICATE:अणु
			काष्ठा notअगर_authenticate *auth = &notअगर->u.auth;
			चयन (auth->state) अणु
			हाल CMAS_AUTHENTICATED:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
					  "authenticated: '%*pE' %pM\n",
					  priv->essid_len, priv->essid,
					  priv->bssid);
				priv->status |= STATUS_AUTH;
				अवरोध;

			हाल CMAS_INIT:
				अगर (priv->status & STATUS_AUTH) अणु
					IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
						  IPW_DL_ASSOC,
						  "authentication failed (0x%04X): %s\n",
						  le16_to_cpu(auth->status),
						  ipw_get_status_code(le16_to_cpu
								      (auth->
								       status)));
				पूर्ण
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC,
					  "deauthenticated: '%*pE' %pM\n",
					  priv->essid_len, priv->essid,
					  priv->bssid);

				priv->status &= ~(STATUS_ASSOCIATING |
						  STATUS_AUTH |
						  STATUS_ASSOCIATED);

				schedule_work(&priv->link_करोwn);
				अवरोध;

			हाल CMAS_TX_AUTH_SEQ_1:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_1\n");
				अवरोध;
			हाल CMAS_RX_AUTH_SEQ_2:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_2\n");
				अवरोध;
			हाल CMAS_AUTH_SEQ_1_PASS:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_1_PASS\n");
				अवरोध;
			हाल CMAS_AUTH_SEQ_1_FAIL:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_1_FAIL\n");
				अवरोध;
			हाल CMAS_TX_AUTH_SEQ_3:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_3\n");
				अवरोध;
			हाल CMAS_RX_AUTH_SEQ_4:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "RX_AUTH_SEQ_4\n");
				अवरोध;
			हाल CMAS_AUTH_SEQ_2_PASS:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUTH_SEQ_2_PASS\n");
				अवरोध;
			हाल CMAS_AUTH_SEQ_2_FAIL:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "AUT_SEQ_2_FAIL\n");
				अवरोध;
			हाल CMAS_TX_ASSOC:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "TX_ASSOC\n");
				अवरोध;
			हाल CMAS_RX_ASSOC_RESP:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "RX_ASSOC_RESP\n");

				अवरोध;
			हाल CMAS_ASSOCIATED:
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE |
					  IPW_DL_ASSOC, "ASSOCIATED\n");
				अवरोध;
			शेष:
				IPW_DEBUG_NOTIF("auth: failure - %d\n",
						auth->state);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_SCAN_CHANNEL_RESULT:अणु
			काष्ठा notअगर_channel_result *x =
			    &notअगर->u.channel_result;

			अगर (size == माप(*x)) अणु
				IPW_DEBUG_SCAN("Scan result for channel %d\n",
					       x->channel_num);
			पूर्ण अन्यथा अणु
				IPW_DEBUG_SCAN("Scan result of wrong size %d "
					       "(should be %zd)\n",
					       size, माप(*x));
			पूर्ण
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_SCAN_COMPLETED:अणु
			काष्ठा notअगर_scan_complete *x = &notअगर->u.scan_complete;
			अगर (size == माप(*x)) अणु
				IPW_DEBUG_SCAN
				    ("Scan completed: type %d, %d channels, "
				     "%d status\n", x->scan_type,
				     x->num_channels, x->status);
			पूर्ण अन्यथा अणु
				IPW_ERROR("Scan completed of wrong size %d "
					  "(should be %zd)\n",
					  size, माप(*x));
			पूर्ण

			priv->status &=
			    ~(STATUS_SCANNING | STATUS_SCAN_ABORTING);

			wake_up_पूर्णांकerruptible(&priv->रुको_state);
			cancel_delayed_work(&priv->scan_check);

			अगर (priv->status & STATUS_EXIT_PENDING)
				अवरोध;

			priv->ieee->scans++;

#अगर_घोषित CONFIG_IPW2200_MONITOR
			अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
				priv->status |= STATUS_SCAN_FORCED;
				schedule_delayed_work(&priv->request_scan, 0);
				अवरोध;
			पूर्ण
			priv->status &= ~STATUS_SCAN_FORCED;
#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */

			/* Do queued direct scans first */
			अगर (priv->status & STATUS_सूचीECT_SCAN_PENDING)
				schedule_delayed_work(&priv->request_direct_scan, 0);

			अगर (!(priv->status & (STATUS_ASSOCIATED |
					      STATUS_ASSOCIATING |
					      STATUS_ROAMING |
					      STATUS_DISASSOCIATING)))
				schedule_work(&priv->associate);
			अन्यथा अगर (priv->status & STATUS_ROAMING) अणु
				अगर (x->status == SCAN_COMPLETED_STATUS_COMPLETE)
					/* If a scan completed and we are in roam mode, then
					 * the scan that completed was the one requested as a
					 * result of entering roam... so, schedule the
					 * roam work */
					schedule_work(&priv->roam);
				अन्यथा
					/* Don't schedule अगर we पातed the scan */
					priv->status &= ~STATUS_ROAMING;
			पूर्ण अन्यथा अगर (priv->status & STATUS_SCAN_PENDING)
				schedule_delayed_work(&priv->request_scan, 0);
			अन्यथा अगर (priv->config & CFG_BACKGROUND_SCAN
				 && priv->status & STATUS_ASSOCIATED)
				schedule_delayed_work(&priv->request_scan,
						      round_jअगरfies_relative(HZ));

			/* Send an empty event to user space.
			 * We करोn't send the received data on the event because
			 * it would require us to करो complex transcoding, and
			 * we want to minimise the work करोne in the irq handler
			 * Use a request to extract the data.
			 * Also, we generate this even क्रम any scan, regardless
			 * on how the scan was initiated. User space can just
			 * sync on periodic scan to get fresh data...
			 * Jean II */
			अगर (x->status == SCAN_COMPLETED_STATUS_COMPLETE)
				handle_scan_event(priv);
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_FRAG_LENGTH:अणु
			काष्ठा notअगर_frag_length *x = &notअगर->u.frag_len;

			अगर (size == माप(*x))
				IPW_ERROR("Frag length: %d\n",
					  le16_to_cpu(x->frag_length));
			अन्यथा
				IPW_ERROR("Frag length of wrong size %d "
					  "(should be %zd)\n",
					  size, माप(*x));
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_LINK_DETERIORATION:अणु
			काष्ठा notअगर_link_deterioration *x =
			    &notअगर->u.link_deterioration;

			अगर (size == माप(*x)) अणु
				IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE,
					"link deterioration: type %d, cnt %d\n",
					x->silence_notअगरication_type,
					x->silence_count);
				स_नकल(&priv->last_link_deterioration, x,
				       माप(*x));
			पूर्ण अन्यथा अणु
				IPW_ERROR("Link Deterioration of wrong size %d "
					  "(should be %zd)\n",
					  size, माप(*x));
			पूर्ण
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_DINO_CONFIG_RESPONSE:अणु
			IPW_ERROR("Dino config\n");
			अगर (priv->hcmd
			    && priv->hcmd->cmd != HOST_CMD_DINO_CONFIG)
				IPW_ERROR("Unexpected DINO_CONFIG_RESPONSE\n");

			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_BEACON_STATE:अणु
			काष्ठा notअगर_beacon_state *x = &notअगर->u.beacon_state;
			अगर (size != माप(*x)) अणु
				IPW_ERROR
				    ("Beacon state of wrong size %d (should "
				     "be %zd)\n", size, माप(*x));
				अवरोध;
			पूर्ण

			अगर (le32_to_cpu(x->state) ==
			    HOST_NOTIFICATION_STATUS_BEACON_MISSING)
				ipw_handle_missed_beacon(priv,
							 le32_to_cpu(x->
								     number));

			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_STATUS_TGI_TX_KEY:अणु
			काष्ठा notअगर_tgi_tx_key *x = &notअगर->u.tgi_tx_key;
			अगर (size == माप(*x)) अणु
				IPW_ERROR("TGi Tx Key: state 0x%02x sec type "
					  "0x%02x station %d\n",
					  x->key_state, x->security_type,
					  x->station_index);
				अवरोध;
			पूर्ण

			IPW_ERROR
			    ("TGi Tx Key of wrong size %d (should be %zd)\n",
			     size, माप(*x));
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_CALIB_KEEP_RESULTS:अणु
			काष्ठा notअगर_calibration *x = &notअगर->u.calibration;

			अगर (size == माप(*x)) अणु
				स_नकल(&priv->calib, x, माप(*x));
				IPW_DEBUG_INFO("TODO: Calibration\n");
				अवरोध;
			पूर्ण

			IPW_ERROR
			    ("Calibration of wrong size %d (should be %zd)\n",
			     size, माप(*x));
			अवरोध;
		पूर्ण

	हाल HOST_NOTIFICATION_NOISE_STATS:अणु
			अगर (size == माप(u32)) अणु
				priv->exp_avg_noise =
				    exponential_average(priv->exp_avg_noise,
				    (u8) (le32_to_cpu(notअगर->u.noise.value) & 0xff),
				    DEPTH_NOISE);
				अवरोध;
			पूर्ण

			IPW_ERROR
			    ("Noise stat is wrong size %d (should be %zd)\n",
			     size, माप(u32));
			अवरोध;
		पूर्ण

	शेष:
		IPW_DEBUG_NOTIF("Unknown notification: "
				"subtype=%d,flags=0x%2x,size=%d\n",
				notअगर->subtype, notअगर->flags, size);
	पूर्ण
पूर्ण

/*
 * Destroys all DMA काष्ठाures and initialise them again
 *
 * @param priv
 * @वापस error code
 */
अटल पूर्णांक ipw_queue_reset(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc = 0;
	/* @toकरो customize queue sizes */
	पूर्णांक nTx = 64, nTxCmd = 8;
	ipw_tx_queue_मुक्त(priv);
	/* Tx CMD queue */
	rc = ipw_queue_tx_init(priv, &priv->txq_cmd, nTxCmd,
			       IPW_TX_CMD_QUEUE_READ_INDEX,
			       IPW_TX_CMD_QUEUE_WRITE_INDEX,
			       IPW_TX_CMD_QUEUE_BD_BASE,
			       IPW_TX_CMD_QUEUE_BD_SIZE);
	अगर (rc) अणु
		IPW_ERROR("Tx Cmd queue init failed\n");
		जाओ error;
	पूर्ण
	/* Tx queue(s) */
	rc = ipw_queue_tx_init(priv, &priv->txq[0], nTx,
			       IPW_TX_QUEUE_0_READ_INDEX,
			       IPW_TX_QUEUE_0_WRITE_INDEX,
			       IPW_TX_QUEUE_0_BD_BASE, IPW_TX_QUEUE_0_BD_SIZE);
	अगर (rc) अणु
		IPW_ERROR("Tx 0 queue init failed\n");
		जाओ error;
	पूर्ण
	rc = ipw_queue_tx_init(priv, &priv->txq[1], nTx,
			       IPW_TX_QUEUE_1_READ_INDEX,
			       IPW_TX_QUEUE_1_WRITE_INDEX,
			       IPW_TX_QUEUE_1_BD_BASE, IPW_TX_QUEUE_1_BD_SIZE);
	अगर (rc) अणु
		IPW_ERROR("Tx 1 queue init failed\n");
		जाओ error;
	पूर्ण
	rc = ipw_queue_tx_init(priv, &priv->txq[2], nTx,
			       IPW_TX_QUEUE_2_READ_INDEX,
			       IPW_TX_QUEUE_2_WRITE_INDEX,
			       IPW_TX_QUEUE_2_BD_BASE, IPW_TX_QUEUE_2_BD_SIZE);
	अगर (rc) अणु
		IPW_ERROR("Tx 2 queue init failed\n");
		जाओ error;
	पूर्ण
	rc = ipw_queue_tx_init(priv, &priv->txq[3], nTx,
			       IPW_TX_QUEUE_3_READ_INDEX,
			       IPW_TX_QUEUE_3_WRITE_INDEX,
			       IPW_TX_QUEUE_3_BD_BASE, IPW_TX_QUEUE_3_BD_SIZE);
	अगर (rc) अणु
		IPW_ERROR("Tx 3 queue init failed\n");
		जाओ error;
	पूर्ण
	/* statistics */
	priv->rx_bufs_min = 0;
	priv->rx_pend_max = 0;
	वापस rc;

      error:
	ipw_tx_queue_मुक्त(priv);
	वापस rc;
पूर्ण

/*
 * Reclaim Tx queue entries no more used by NIC.
 *
 * When FW advances 'R' index, all entries between old and
 * new 'R' index need to be reclaimed. As result, some मुक्त space
 * क्रमms. If there is enough मुक्त space (> low mark), wake Tx queue.
 *
 * @note Need to protect against garbage in 'R' index
 * @param priv
 * @param txq
 * @param qindex
 * @वापस Number of used entries reमुख्यs in the queue
 */
अटल पूर्णांक ipw_queue_tx_reclaim(काष्ठा ipw_priv *priv,
				काष्ठा clx2_tx_queue *txq, पूर्णांक qindex)
अणु
	u32 hw_tail;
	पूर्णांक used;
	काष्ठा clx2_queue *q = &txq->q;

	hw_tail = ipw_पढ़ो32(priv, q->reg_r);
	अगर (hw_tail >= q->n_bd) अणु
		IPW_ERROR
		    ("Read index for DMA queue (%d) is out of range [0-%d)\n",
		     hw_tail, q->n_bd);
		जाओ करोne;
	पूर्ण
	क्रम (; q->last_used != hw_tail;
	     q->last_used = ipw_queue_inc_wrap(q->last_used, q->n_bd)) अणु
		ipw_queue_tx_मुक्त_tfd(priv, txq);
		priv->tx_packets++;
	पूर्ण
      करोne:
	अगर ((ipw_tx_queue_space(q) > q->low_mark) &&
	    (qindex >= 0))
		netअगर_wake_queue(priv->net_dev);
	used = q->first_empty - q->last_used;
	अगर (used < 0)
		used += q->n_bd;

	वापस used;
पूर्ण

अटल पूर्णांक ipw_queue_tx_hcmd(काष्ठा ipw_priv *priv, पूर्णांक hcmd, व्योम *buf,
			     पूर्णांक len, पूर्णांक sync)
अणु
	काष्ठा clx2_tx_queue *txq = &priv->txq_cmd;
	काष्ठा clx2_queue *q = &txq->q;
	काष्ठा tfd_frame *tfd;

	अगर (ipw_tx_queue_space(q) < (sync ? 1 : 2)) अणु
		IPW_ERROR("No space for Tx\n");
		वापस -EBUSY;
	पूर्ण

	tfd = &txq->bd[q->first_empty];
	txq->txb[q->first_empty] = शून्य;

	स_रखो(tfd, 0, माप(*tfd));
	tfd->control_flags.message_type = TX_HOST_COMMAND_TYPE;
	tfd->control_flags.control_bits = TFD_NEED_IRQ_MASK;
	priv->hcmd_seq++;
	tfd->u.cmd.index = hcmd;
	tfd->u.cmd.length = len;
	स_नकल(tfd->u.cmd.payload, buf, len);
	q->first_empty = ipw_queue_inc_wrap(q->first_empty, q->n_bd);
	ipw_ग_लिखो32(priv, q->reg_w, q->first_empty);
	_ipw_पढ़ो32(priv, 0x90);

	वापस 0;
पूर्ण

/*
 * Rx theory of operation
 *
 * The host allocates 32 DMA target addresses and passes the host address
 * to the firmware at रेजिस्टर IPW_RFDS_TABLE_LOWER + N * RFD_SIZE where N is
 * 0 to 31
 *
 * Rx Queue Indexes
 * The host/firmware share two index रेजिस्टरs क्रम managing the Rx buffers.
 *
 * The READ index maps to the first position that the firmware may be writing
 * to -- the driver can पढ़ो up to (but not including) this position and get
 * good data.
 * The READ index is managed by the firmware once the card is enabled.
 *
 * The WRITE index maps to the last position the driver has पढ़ो from -- the
 * position preceding WRITE is the last slot the firmware can place a packet.
 *
 * The queue is empty (no good data) अगर WRITE = READ - 1, and is full अगर
 * WRITE = READ.
 *
 * During initialization the host sets up the READ queue position to the first
 * INDEX position, and WRITE to the last (READ - 1 wrapped)
 *
 * When the firmware places a packet in a buffer it will advance the READ index
 * and fire the RX पूर्णांकerrupt.  The driver can then query the READ index and
 * process as many packets as possible, moving the WRITE index क्रमward as it
 * resets the Rx queue buffers with new memory.
 *
 * The management in the driver is as follows:
 * + A list of pre-allocated SKBs is stored in ipw->rxq->rx_मुक्त.  When
 *   ipw->rxq->मुक्त_count drops to or below RX_LOW_WATERMARK, work is scheduled
 *   to replensish the ipw->rxq->rx_मुक्त.
 * + In ipw_rx_queue_replenish (scheduled) अगर 'processed' != 'read' then the
 *   ipw->rxq is replenished and the READ INDEX is updated (updating the
 *   'processed' and 'read' driver indexes as well)
 * + A received packet is processed and handed to the kernel network stack,
 *   detached from the ipw->rxq.  The driver 'processed' index is updated.
 * + The Host/Firmware ipw->rxq is replenished at tasklet समय from the rx_मुक्त
 *   list. If there are no allocated buffers in ipw->rxq->rx_मुक्त, the READ
 *   INDEX is not incremented and ipw->status(RX_STALLED) is set.  If there
 *   were enough मुक्त buffers and RX_STALLED is set it is cleared.
 *
 *
 * Driver sequence:
 *
 * ipw_rx_queue_alloc()       Allocates rx_मुक्त
 * ipw_rx_queue_replenish()   Replenishes rx_मुक्त list from rx_used, and calls
 *                            ipw_rx_queue_restock
 * ipw_rx_queue_restock()     Moves available buffers from rx_मुक्त पूर्णांकo Rx
 *                            queue, updates firmware poपूर्णांकers, and updates
 *                            the WRITE index.  If insufficient rx_मुक्त buffers
 *                            are available, schedules ipw_rx_queue_replenish
 *
 * -- enable पूर्णांकerrupts --
 * ISR - ipw_rx()             Detach ipw_rx_mem_buffers from pool up to the
 *                            READ INDEX, detaching the SKB from the pool.
 *                            Moves the packet buffer from queue to rx_used.
 *                            Calls ipw_rx_queue_restock to refill any empty
 *                            slots.
 * ...
 *
 */

/*
 * If there are slots in the RX queue that  need to be restocked,
 * and we have मुक्त pre-allocated buffers, fill the ranks as much
 * as we can pulling from rx_मुक्त.
 *
 * This moves the 'write' index forward to catch up with 'processed', and
 * also updates the memory address in the firmware to reference the new
 * target buffer.
 */
अटल व्योम ipw_rx_queue_restock(काष्ठा ipw_priv *priv)
अणु
	काष्ठा ipw_rx_queue *rxq = priv->rxq;
	काष्ठा list_head *element;
	काष्ठा ipw_rx_mem_buffer *rxb;
	अचिन्हित दीर्घ flags;
	पूर्णांक ग_लिखो;

	spin_lock_irqsave(&rxq->lock, flags);
	ग_लिखो = rxq->ग_लिखो;
	जबतक ((ipw_rx_queue_space(rxq) > 0) && (rxq->मुक्त_count)) अणु
		element = rxq->rx_मुक्त.next;
		rxb = list_entry(element, काष्ठा ipw_rx_mem_buffer, list);
		list_del(element);

		ipw_ग_लिखो32(priv, IPW_RFDS_TABLE_LOWER + rxq->ग_लिखो * RFD_SIZE,
			    rxb->dma_addr);
		rxq->queue[rxq->ग_लिखो] = rxb;
		rxq->ग_लिखो = (rxq->ग_लिखो + 1) % RX_QUEUE_SIZE;
		rxq->मुक्त_count--;
	पूर्ण
	spin_unlock_irqrestore(&rxq->lock, flags);

	/* If the pre-allocated buffer pool is dropping low, schedule to
	 * refill it */
	अगर (rxq->मुक्त_count <= RX_LOW_WATERMARK)
		schedule_work(&priv->rx_replenish);

	/* If we've added more space क्रम the firmware to place data, tell it */
	अगर (ग_लिखो != rxq->ग_लिखो)
		ipw_ग_लिखो32(priv, IPW_RX_WRITE_INDEX, rxq->ग_लिखो);
पूर्ण

/*
 * Move all used packet from rx_used to rx_मुक्त, allocating a new SKB क्रम each.
 * Also restock the Rx queue via ipw_rx_queue_restock.
 *
 * This is called as a scheduled work item (except क्रम during initialization)
 */
अटल व्योम ipw_rx_queue_replenish(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;
	काष्ठा ipw_rx_queue *rxq = priv->rxq;
	काष्ठा list_head *element;
	काष्ठा ipw_rx_mem_buffer *rxb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rxq->lock, flags);
	जबतक (!list_empty(&rxq->rx_used)) अणु
		element = rxq->rx_used.next;
		rxb = list_entry(element, काष्ठा ipw_rx_mem_buffer, list);
		rxb->skb = alloc_skb(IPW_RX_BUF_SIZE, GFP_ATOMIC);
		अगर (!rxb->skb) अणु
			prपूर्णांकk(KERN_CRIT "%s: Can not allocate SKB buffers.\n",
			       priv->net_dev->name);
			/* We करोn't reschedule replenish work here -- we will
			 * call the restock method and अगर it still needs
			 * more buffers it will schedule replenish */
			अवरोध;
		पूर्ण
		list_del(element);

		rxb->dma_addr =
		    dma_map_single(&priv->pci_dev->dev, rxb->skb->data,
				   IPW_RX_BUF_SIZE, DMA_FROM_DEVICE);

		list_add_tail(&rxb->list, &rxq->rx_मुक्त);
		rxq->मुक्त_count++;
	पूर्ण
	spin_unlock_irqrestore(&rxq->lock, flags);

	ipw_rx_queue_restock(priv);
पूर्ण

अटल व्योम ipw_bg_rx_queue_replenish(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, rx_replenish);
	mutex_lock(&priv->mutex);
	ipw_rx_queue_replenish(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

/* Assumes that the skb field of the buffers in 'pool' is kept accurate.
 * If an SKB has been detached, the POOL needs to have its SKB set to शून्य
 * This मुक्त routine walks the list of POOL entries and अगर SKB is set to
 * non शून्य it is unmapped and मुक्तd
 */
अटल व्योम ipw_rx_queue_मुक्त(काष्ठा ipw_priv *priv, काष्ठा ipw_rx_queue *rxq)
अणु
	पूर्णांक i;

	अगर (!rxq)
		वापस;

	क्रम (i = 0; i < RX_QUEUE_SIZE + RX_FREE_BUFFERS; i++) अणु
		अगर (rxq->pool[i].skb != शून्य) अणु
			dma_unmap_single(&priv->pci_dev->dev,
					 rxq->pool[i].dma_addr,
					 IPW_RX_BUF_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(rxq->pool[i].skb);
		पूर्ण
	पूर्ण

	kमुक्त(rxq);
पूर्ण

अटल काष्ठा ipw_rx_queue *ipw_rx_queue_alloc(काष्ठा ipw_priv *priv)
अणु
	काष्ठा ipw_rx_queue *rxq;
	पूर्णांक i;

	rxq = kzalloc(माप(*rxq), GFP_KERNEL);
	अगर (unlikely(!rxq)) अणु
		IPW_ERROR("memory allocation failed\n");
		वापस शून्य;
	पूर्ण
	spin_lock_init(&rxq->lock);
	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);

	/* Fill the rx_used queue with _all_ of the Rx buffers */
	क्रम (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++)
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->पढ़ो = rxq->ग_लिखो = 0;
	rxq->मुक्त_count = 0;

	वापस rxq;
पूर्ण

अटल पूर्णांक ipw_is_rate_in_mask(काष्ठा ipw_priv *priv, पूर्णांक ieee_mode, u8 rate)
अणु
	rate &= ~LIBIPW_BASIC_RATE_MASK;
	अगर (ieee_mode == IEEE_A) अणु
		चयन (rate) अणु
		हाल LIBIPW_OFDM_RATE_6MB:
			वापस priv->rates_mask & LIBIPW_OFDM_RATE_6MB_MASK ?
			    1 : 0;
		हाल LIBIPW_OFDM_RATE_9MB:
			वापस priv->rates_mask & LIBIPW_OFDM_RATE_9MB_MASK ?
			    1 : 0;
		हाल LIBIPW_OFDM_RATE_12MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_12MB_MASK ? 1 : 0;
		हाल LIBIPW_OFDM_RATE_18MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_18MB_MASK ? 1 : 0;
		हाल LIBIPW_OFDM_RATE_24MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_24MB_MASK ? 1 : 0;
		हाल LIBIPW_OFDM_RATE_36MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_36MB_MASK ? 1 : 0;
		हाल LIBIPW_OFDM_RATE_48MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_48MB_MASK ? 1 : 0;
		हाल LIBIPW_OFDM_RATE_54MB:
			वापस priv->
			    rates_mask & LIBIPW_OFDM_RATE_54MB_MASK ? 1 : 0;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	/* B and G mixed */
	चयन (rate) अणु
	हाल LIBIPW_CCK_RATE_1MB:
		वापस priv->rates_mask & LIBIPW_CCK_RATE_1MB_MASK ? 1 : 0;
	हाल LIBIPW_CCK_RATE_2MB:
		वापस priv->rates_mask & LIBIPW_CCK_RATE_2MB_MASK ? 1 : 0;
	हाल LIBIPW_CCK_RATE_5MB:
		वापस priv->rates_mask & LIBIPW_CCK_RATE_5MB_MASK ? 1 : 0;
	हाल LIBIPW_CCK_RATE_11MB:
		वापस priv->rates_mask & LIBIPW_CCK_RATE_11MB_MASK ? 1 : 0;
	पूर्ण

	/* If we are limited to B modulations, bail at this poपूर्णांक */
	अगर (ieee_mode == IEEE_B)
		वापस 0;

	/* G */
	चयन (rate) अणु
	हाल LIBIPW_OFDM_RATE_6MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_6MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_9MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_9MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_12MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_12MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_18MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_18MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_24MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_24MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_36MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_36MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_48MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_48MB_MASK ? 1 : 0;
	हाल LIBIPW_OFDM_RATE_54MB:
		वापस priv->rates_mask & LIBIPW_OFDM_RATE_54MB_MASK ? 1 : 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_compatible_rates(काष्ठा ipw_priv *priv,
				स्थिर काष्ठा libipw_network *network,
				काष्ठा ipw_supported_rates *rates)
अणु
	पूर्णांक num_rates, i;

	स_रखो(rates, 0, माप(*rates));
	num_rates = min(network->rates_len, (u8) IPW_MAX_RATES);
	rates->num_rates = 0;
	क्रम (i = 0; i < num_rates; i++) अणु
		अगर (!ipw_is_rate_in_mask(priv, network->mode,
					 network->rates[i])) अणु

			अगर (network->rates[i] & LIBIPW_BASIC_RATE_MASK) अणु
				IPW_DEBUG_SCAN("Adding masked mandatory "
					       "rate %02X\n",
					       network->rates[i]);
				rates->supported_rates[rates->num_rates++] =
				    network->rates[i];
				जारी;
			पूर्ण

			IPW_DEBUG_SCAN("Rate %02X masked : 0x%08X\n",
				       network->rates[i], priv->rates_mask);
			जारी;
		पूर्ण

		rates->supported_rates[rates->num_rates++] = network->rates[i];
	पूर्ण

	num_rates = min(network->rates_ex_len,
			(u8) (IPW_MAX_RATES - num_rates));
	क्रम (i = 0; i < num_rates; i++) अणु
		अगर (!ipw_is_rate_in_mask(priv, network->mode,
					 network->rates_ex[i])) अणु
			अगर (network->rates_ex[i] & LIBIPW_BASIC_RATE_MASK) अणु
				IPW_DEBUG_SCAN("Adding masked mandatory "
					       "rate %02X\n",
					       network->rates_ex[i]);
				rates->supported_rates[rates->num_rates++] =
				    network->rates[i];
				जारी;
			पूर्ण

			IPW_DEBUG_SCAN("Rate %02X masked : 0x%08X\n",
				       network->rates_ex[i], priv->rates_mask);
			जारी;
		पूर्ण

		rates->supported_rates[rates->num_rates++] =
		    network->rates_ex[i];
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम ipw_copy_rates(काष्ठा ipw_supported_rates *dest,
				  स्थिर काष्ठा ipw_supported_rates *src)
अणु
	u8 i;
	क्रम (i = 0; i < src->num_rates; i++)
		dest->supported_rates[i] = src->supported_rates[i];
	dest->num_rates = src->num_rates;
पूर्ण

/* TODO: Look at snअगरfed packets in the air to determine अगर the basic rate
 * mask should ever be used -- right now all callers to add the scan rates are
 * set with the modulation = CCK, so BASIC_RATE_MASK is never set... */
अटल व्योम ipw_add_cck_scan_rates(काष्ठा ipw_supported_rates *rates,
				   u8 modulation, u32 rate_mask)
अणु
	u8 basic_mask = (LIBIPW_OFDM_MODULATION == modulation) ?
	    LIBIPW_BASIC_RATE_MASK : 0;

	अगर (rate_mask & LIBIPW_CCK_RATE_1MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_BASIC_RATE_MASK | LIBIPW_CCK_RATE_1MB;

	अगर (rate_mask & LIBIPW_CCK_RATE_2MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_BASIC_RATE_MASK | LIBIPW_CCK_RATE_2MB;

	अगर (rate_mask & LIBIPW_CCK_RATE_5MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_CCK_RATE_5MB;

	अगर (rate_mask & LIBIPW_CCK_RATE_11MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_CCK_RATE_11MB;
पूर्ण

अटल व्योम ipw_add_ofdm_scan_rates(काष्ठा ipw_supported_rates *rates,
				    u8 modulation, u32 rate_mask)
अणु
	u8 basic_mask = (LIBIPW_OFDM_MODULATION == modulation) ?
	    LIBIPW_BASIC_RATE_MASK : 0;

	अगर (rate_mask & LIBIPW_OFDM_RATE_6MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_6MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_9MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_9MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_12MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_12MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_18MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_18MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_24MB_MASK)
		rates->supported_rates[rates->num_rates++] = basic_mask |
		    LIBIPW_OFDM_RATE_24MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_36MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_36MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_48MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_48MB;

	अगर (rate_mask & LIBIPW_OFDM_RATE_54MB_MASK)
		rates->supported_rates[rates->num_rates++] =
		    LIBIPW_OFDM_RATE_54MB;
पूर्ण

काष्ठा ipw_network_match अणु
	काष्ठा libipw_network *network;
	काष्ठा ipw_supported_rates rates;
पूर्ण;

अटल पूर्णांक ipw_find_adhoc_network(काष्ठा ipw_priv *priv,
				  काष्ठा ipw_network_match *match,
				  काष्ठा libipw_network *network,
				  पूर्णांक roaming)
अणु
	काष्ठा ipw_supported_rates rates;

	/* Verअगरy that this network's capability is compatible with the
	 * current mode (AdHoc or Infraकाष्ठाure) */
	अगर ((priv->ieee->iw_mode == IW_MODE_ADHOC &&
	     !(network->capability & WLAN_CAPABILITY_IBSS))) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded due to capability mismatch.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	अगर (unlikely(roaming)) अणु
		/* If we are roaming, then ensure check अगर this is a valid
		 * network to try and roam to */
		अगर ((network->ssid_len != match->network->ssid_len) ||
		    स_भेद(network->ssid, match->network->ssid,
			   network->ssid_len)) अणु
			IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of non-network ESSID.\n",
					network->ssid_len, network->ssid,
					network->bssid);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If an ESSID has been configured then compare the broadcast
		 * ESSID to ours */
		अगर ((priv->config & CFG_STATIC_ESSID) &&
		    ((network->ssid_len != priv->essid_len) ||
		     स_भेद(network->ssid, priv->essid,
			    min(network->ssid_len, priv->essid_len)))) अणु
			IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of ESSID mismatch: '%*pE'.\n",
					network->ssid_len, network->ssid,
					network->bssid, priv->essid_len,
					priv->essid);
			वापस 0;
		पूर्ण
	पूर्ण

	/* If the old network rate is better than this one, करोn't bother
	 * testing everything अन्यथा. */

	अगर (network->समय_stamp[0] < match->network->समय_stamp[0]) अणु
		IPW_DEBUG_MERGE("Network '%*pE excluded because newer than current network.\n",
				match->network->ssid_len, match->network->ssid);
		वापस 0;
	पूर्ण अन्यथा अगर (network->समय_stamp[1] < match->network->समय_stamp[1]) अणु
		IPW_DEBUG_MERGE("Network '%*pE excluded because newer than current network.\n",
				match->network->ssid_len, match->network->ssid);
		वापस 0;
	पूर्ण

	/* Now go through and see अगर the requested network is valid... */
	अगर (priv->ieee->scan_age != 0 &&
	    समय_after(jअगरfies, network->last_scanned + priv->ieee->scan_age)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of age: %ums.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				jअगरfies_to_msecs(jअगरfies -
						 network->last_scanned));
		वापस 0;
	पूर्ण

	अगर ((priv->config & CFG_STATIC_CHANNEL) &&
	    (network->channel != priv->channel)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of channel mismatch: %d != %d.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				network->channel, priv->channel);
		वापस 0;
	पूर्ण

	/* Verअगरy privacy compatibility */
	अगर (((priv->capability & CAP_PRIVACY_ON) ? 1 : 0) !=
	    ((network->capability & WLAN_CAPABILITY_PRIVACY) ? 1 : 0)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of privacy mismatch: %s != %s.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				priv->
				capability & CAP_PRIVACY_ON ? "on" : "off",
				network->
				capability & WLAN_CAPABILITY_PRIVACY ? "on" :
				"off");
		वापस 0;
	पूर्ण

	अगर (ether_addr_equal(network->bssid, priv->bssid)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of the same BSSID match: %pM.\n",
				network->ssid_len, network->ssid,
				network->bssid, priv->bssid);
		वापस 0;
	पूर्ण

	/* Filter out any incompatible freq / mode combinations */
	अगर (!libipw_is_valid_mode(priv->ieee, network->mode)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of invalid frequency/mode combination.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	/* Ensure that the rates supported by the driver are compatible with
	 * this AP, including verअगरication of basic rates (mandatory) */
	अगर (!ipw_compatible_rates(priv, network, &rates)) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because configured rate mask excludes AP mandatory rate.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	अगर (rates.num_rates == 0) अणु
		IPW_DEBUG_MERGE("Network '%*pE (%pM)' excluded because of no compatible rates.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	/* TODO: Perक्रमm any further minimal comparititive tests.  We करो not
	 * want to put too much policy logic here; पूर्णांकelligent scan selection
	 * should occur within a generic IEEE 802.11 user space tool.  */

	/* Set up 'new' AP to this network */
	ipw_copy_rates(&match->rates, &rates);
	match->network = network;
	IPW_DEBUG_MERGE("Network '%*pE (%pM)' is a viable match.\n",
			network->ssid_len, network->ssid, network->bssid);

	वापस 1;
पूर्ण

अटल व्योम ipw_merge_adhoc_network(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, merge_networks);
	काष्ठा libipw_network *network = शून्य;
	काष्ठा ipw_network_match match = अणु
		.network = priv->assoc_network
	पूर्ण;

	अगर ((priv->status & STATUS_ASSOCIATED) &&
	    (priv->ieee->iw_mode == IW_MODE_ADHOC)) अणु
		/* First pass through ROAM process -- look क्रम a better
		 * network */
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->ieee->lock, flags);
		list_क्रम_each_entry(network, &priv->ieee->network_list, list) अणु
			अगर (network != priv->assoc_network)
				ipw_find_adhoc_network(priv, &match, network,
						       1);
		पूर्ण
		spin_unlock_irqrestore(&priv->ieee->lock, flags);

		अगर (match.network == priv->assoc_network) अणु
			IPW_DEBUG_MERGE("No better ADHOC in this network to "
					"merge to.\n");
			वापस;
		पूर्ण

		mutex_lock(&priv->mutex);
		अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
			IPW_DEBUG_MERGE("remove network %*pE\n",
					priv->essid_len, priv->essid);
			ipw_हटाओ_current_network(priv);
		पूर्ण

		ipw_disassociate(priv);
		priv->assoc_network = match.network;
		mutex_unlock(&priv->mutex);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ipw_best_network(काष्ठा ipw_priv *priv,
			    काष्ठा ipw_network_match *match,
			    काष्ठा libipw_network *network, पूर्णांक roaming)
अणु
	काष्ठा ipw_supported_rates rates;

	/* Verअगरy that this network's capability is compatible with the
	 * current mode (AdHoc or Infraकाष्ठाure) */
	अगर ((priv->ieee->iw_mode == IW_MODE_INFRA &&
	     !(network->capability & WLAN_CAPABILITY_ESS)) ||
	    (priv->ieee->iw_mode == IW_MODE_ADHOC &&
	     !(network->capability & WLAN_CAPABILITY_IBSS))) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded due to capability mismatch.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	अगर (unlikely(roaming)) अणु
		/* If we are roaming, then ensure check अगर this is a valid
		 * network to try and roam to */
		अगर ((network->ssid_len != match->network->ssid_len) ||
		    स_भेद(network->ssid, match->network->ssid,
			   network->ssid_len)) अणु
			IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of non-network ESSID.\n",
					network->ssid_len, network->ssid,
					network->bssid);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If an ESSID has been configured then compare the broadcast
		 * ESSID to ours */
		अगर ((priv->config & CFG_STATIC_ESSID) &&
		    ((network->ssid_len != priv->essid_len) ||
		     स_भेद(network->ssid, priv->essid,
			    min(network->ssid_len, priv->essid_len)))) अणु
			IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of ESSID mismatch: '%*pE'.\n",
					network->ssid_len, network->ssid,
					network->bssid, priv->essid_len,
					priv->essid);
			वापस 0;
		पूर्ण
	पूर्ण

	/* If the old network rate is better than this one, करोn't bother
	 * testing everything अन्यथा. */
	अगर (match->network && match->network->stats.rssi > network->stats.rssi) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because '%*pE (%pM)' has a stronger signal.\n",
				network->ssid_len, network->ssid,
				network->bssid, match->network->ssid_len,
				match->network->ssid, match->network->bssid);
		वापस 0;
	पूर्ण

	/* If this network has alपढ़ोy had an association attempt within the
	 * last 3 seconds, करो not try and associate again... */
	अगर (network->last_associate &&
	    समय_after(network->last_associate + (HZ * 3UL), jअगरfies)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of storming (%ums since last assoc attempt).\n",
				network->ssid_len, network->ssid,
				network->bssid,
				jअगरfies_to_msecs(jअगरfies -
						 network->last_associate));
		वापस 0;
	पूर्ण

	/* Now go through and see अगर the requested network is valid... */
	अगर (priv->ieee->scan_age != 0 &&
	    समय_after(jअगरfies, network->last_scanned + priv->ieee->scan_age)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of age: %ums.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				jअगरfies_to_msecs(jअगरfies -
						 network->last_scanned));
		वापस 0;
	पूर्ण

	अगर ((priv->config & CFG_STATIC_CHANNEL) &&
	    (network->channel != priv->channel)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of channel mismatch: %d != %d.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				network->channel, priv->channel);
		वापस 0;
	पूर्ण

	/* Verअगरy privacy compatibility */
	अगर (((priv->capability & CAP_PRIVACY_ON) ? 1 : 0) !=
	    ((network->capability & WLAN_CAPABILITY_PRIVACY) ? 1 : 0)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of privacy mismatch: %s != %s.\n",
				network->ssid_len, network->ssid,
				network->bssid,
				priv->capability & CAP_PRIVACY_ON ? "on" :
				"off",
				network->capability &
				WLAN_CAPABILITY_PRIVACY ? "on" : "off");
		वापस 0;
	पूर्ण

	अगर ((priv->config & CFG_STATIC_BSSID) &&
	    !ether_addr_equal(network->bssid, priv->bssid)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of BSSID mismatch: %pM.\n",
				network->ssid_len, network->ssid,
				network->bssid, priv->bssid);
		वापस 0;
	पूर्ण

	/* Filter out any incompatible freq / mode combinations */
	अगर (!libipw_is_valid_mode(priv->ieee, network->mode)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of invalid frequency/mode combination.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	/* Filter out invalid channel in current GEO */
	अगर (!libipw_is_valid_channel(priv->ieee, network->channel)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of invalid channel in current GEO\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	/* Ensure that the rates supported by the driver are compatible with
	 * this AP, including verअगरication of basic rates (mandatory) */
	अगर (!ipw_compatible_rates(priv, network, &rates)) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because configured rate mask excludes AP mandatory rate.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	अगर (rates.num_rates == 0) अणु
		IPW_DEBUG_ASSOC("Network '%*pE (%pM)' excluded because of no compatible rates.\n",
				network->ssid_len, network->ssid,
				network->bssid);
		वापस 0;
	पूर्ण

	/* TODO: Perक्रमm any further minimal comparititive tests.  We करो not
	 * want to put too much policy logic here; पूर्णांकelligent scan selection
	 * should occur within a generic IEEE 802.11 user space tool.  */

	/* Set up 'new' AP to this network */
	ipw_copy_rates(&match->rates, &rates);
	match->network = network;

	IPW_DEBUG_ASSOC("Network '%*pE (%pM)' is a viable match.\n",
			network->ssid_len, network->ssid, network->bssid);

	वापस 1;
पूर्ण

अटल व्योम ipw_adhoc_create(काष्ठा ipw_priv *priv,
			     काष्ठा libipw_network *network)
अणु
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	पूर्णांक i;

	/*
	 * For the purposes of scanning, we can set our wireless mode
	 * to trigger scans across combinations of bands, but when it
	 * comes to creating a new ad-hoc network, we have tell the FW
	 * exactly which band to use.
	 *
	 * We also have the possibility of an invalid channel क्रम the
	 * chossen band.  Attempting to create a new ad-hoc network
	 * with an invalid channel क्रम wireless mode will trigger a
	 * FW fatal error.
	 *
	 */
	चयन (libipw_is_valid_channel(priv->ieee, priv->channel)) अणु
	हाल LIBIPW_52GHZ_BAND:
		network->mode = IEEE_A;
		i = libipw_channel_to_index(priv->ieee, priv->channel);
		BUG_ON(i == -1);
		अगर (geo->a[i].flags & LIBIPW_CH_PASSIVE_ONLY) अणु
			IPW_WARNING("Overriding invalid channel\n");
			priv->channel = geo->a[0].channel;
		पूर्ण
		अवरोध;

	हाल LIBIPW_24GHZ_BAND:
		अगर (priv->ieee->mode & IEEE_G)
			network->mode = IEEE_G;
		अन्यथा
			network->mode = IEEE_B;
		i = libipw_channel_to_index(priv->ieee, priv->channel);
		BUG_ON(i == -1);
		अगर (geo->bg[i].flags & LIBIPW_CH_PASSIVE_ONLY) अणु
			IPW_WARNING("Overriding invalid channel\n");
			priv->channel = geo->bg[0].channel;
		पूर्ण
		अवरोध;

	शेष:
		IPW_WARNING("Overriding invalid channel\n");
		अगर (priv->ieee->mode & IEEE_A) अणु
			network->mode = IEEE_A;
			priv->channel = geo->a[0].channel;
		पूर्ण अन्यथा अगर (priv->ieee->mode & IEEE_G) अणु
			network->mode = IEEE_G;
			priv->channel = geo->bg[0].channel;
		पूर्ण अन्यथा अणु
			network->mode = IEEE_B;
			priv->channel = geo->bg[0].channel;
		पूर्ण
		अवरोध;
	पूर्ण

	network->channel = priv->channel;
	priv->config |= CFG_ADHOC_PERSIST;
	ipw_create_bssid(priv, network->bssid);
	network->ssid_len = priv->essid_len;
	स_नकल(network->ssid, priv->essid, priv->essid_len);
	स_रखो(&network->stats, 0, माप(network->stats));
	network->capability = WLAN_CAPABILITY_IBSS;
	अगर (!(priv->config & CFG_PREAMBLE_LONG))
		network->capability |= WLAN_CAPABILITY_SHORT_PREAMBLE;
	अगर (priv->capability & CAP_PRIVACY_ON)
		network->capability |= WLAN_CAPABILITY_PRIVACY;
	network->rates_len = min(priv->rates.num_rates, MAX_RATES_LENGTH);
	स_नकल(network->rates, priv->rates.supported_rates, network->rates_len);
	network->rates_ex_len = priv->rates.num_rates - network->rates_len;
	स_नकल(network->rates_ex,
	       &priv->rates.supported_rates[network->rates_len],
	       network->rates_ex_len);
	network->last_scanned = 0;
	network->flags = 0;
	network->last_associate = 0;
	network->समय_stamp[0] = 0;
	network->समय_stamp[1] = 0;
	network->beacon_पूर्णांकerval = 100;	/* Default */
	network->listen_पूर्णांकerval = 10;	/* Default */
	network->atim_winकरोw = 0;	/* Default */
	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;
पूर्ण

अटल व्योम ipw_send_tgi_tx_key(काष्ठा ipw_priv *priv, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा ipw_tgi_tx_key key;

	अगर (!(priv->ieee->sec.flags & (1 << index)))
		वापस;

	key.key_id = index;
	स_नकल(key.key, priv->ieee->sec.keys[index], SCM_TEMPORAL_KEY_LENGTH);
	key.security_type = type;
	key.station_index = 0;	/* always 0 क्रम BSS */
	key.flags = 0;
	/* 0 क्रम new key; previous value of counter (after fatal error) */
	key.tx_counter[0] = cpu_to_le32(0);
	key.tx_counter[1] = cpu_to_le32(0);

	ipw_send_cmd_pdu(priv, IPW_CMD_TGI_TX_KEY, माप(key), &key);
पूर्ण

अटल व्योम ipw_send_wep_keys(काष्ठा ipw_priv *priv, पूर्णांक type)
अणु
	काष्ठा ipw_wep_key key;
	पूर्णांक i;

	key.cmd_id = DINO_CMD_WEP_KEY;
	key.seq_num = 0;

	/* Note: AES keys cannot be set क्रम multiple बार.
	 * Only set it at the first समय. */
	क्रम (i = 0; i < 4; i++) अणु
		key.key_index = i | type;
		अगर (!(priv->ieee->sec.flags & (1 << i))) अणु
			key.key_size = 0;
			जारी;
		पूर्ण

		key.key_size = priv->ieee->sec.key_sizes[i];
		स_नकल(key.key, priv->ieee->sec.keys[i], key.key_size);

		ipw_send_cmd_pdu(priv, IPW_CMD_WEP_KEY, माप(key), &key);
	पूर्ण
पूर्ण

अटल व्योम ipw_set_hw_decrypt_unicast(काष्ठा ipw_priv *priv, पूर्णांक level)
अणु
	अगर (priv->ieee->host_encrypt)
		वापस;

	चयन (level) अणु
	हाल SEC_LEVEL_3:
		priv->sys_config.disable_unicast_decryption = 0;
		priv->ieee->host_decrypt = 0;
		अवरोध;
	हाल SEC_LEVEL_2:
		priv->sys_config.disable_unicast_decryption = 1;
		priv->ieee->host_decrypt = 1;
		अवरोध;
	हाल SEC_LEVEL_1:
		priv->sys_config.disable_unicast_decryption = 0;
		priv->ieee->host_decrypt = 0;
		अवरोध;
	हाल SEC_LEVEL_0:
		priv->sys_config.disable_unicast_decryption = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ipw_set_hw_decrypt_multicast(काष्ठा ipw_priv *priv, पूर्णांक level)
अणु
	अगर (priv->ieee->host_encrypt)
		वापस;

	चयन (level) अणु
	हाल SEC_LEVEL_3:
		priv->sys_config.disable_multicast_decryption = 0;
		अवरोध;
	हाल SEC_LEVEL_2:
		priv->sys_config.disable_multicast_decryption = 1;
		अवरोध;
	हाल SEC_LEVEL_1:
		priv->sys_config.disable_multicast_decryption = 0;
		अवरोध;
	हाल SEC_LEVEL_0:
		priv->sys_config.disable_multicast_decryption = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ipw_set_hwcrypto_keys(काष्ठा ipw_priv *priv)
अणु
	चयन (priv->ieee->sec.level) अणु
	हाल SEC_LEVEL_3:
		अगर (priv->ieee->sec.flags & SEC_ACTIVE_KEY)
			ipw_send_tgi_tx_key(priv,
					    DCT_FLAG_EXT_SECURITY_CCM,
					    priv->ieee->sec.active_key);

		अगर (!priv->ieee->host_mc_decrypt)
			ipw_send_wep_keys(priv, DCW_WEP_KEY_SEC_TYPE_CCM);
		अवरोध;
	हाल SEC_LEVEL_2:
		अगर (priv->ieee->sec.flags & SEC_ACTIVE_KEY)
			ipw_send_tgi_tx_key(priv,
					    DCT_FLAG_EXT_SECURITY_TKIP,
					    priv->ieee->sec.active_key);
		अवरोध;
	हाल SEC_LEVEL_1:
		ipw_send_wep_keys(priv, DCW_WEP_KEY_SEC_TYPE_WEP);
		ipw_set_hw_decrypt_unicast(priv, priv->ieee->sec.level);
		ipw_set_hw_decrypt_multicast(priv, priv->ieee->sec.level);
		अवरोध;
	हाल SEC_LEVEL_0:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ipw_adhoc_check(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;

	अगर (priv->missed_adhoc_beacons++ > priv->disassociate_threshold &&
	    !(priv->config & CFG_ADHOC_PERSIST)) अणु
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
			  IPW_DL_STATE | IPW_DL_ASSOC,
			  "Missed beacon: %d - disassociate\n",
			  priv->missed_adhoc_beacons);
		ipw_हटाओ_current_network(priv);
		ipw_disassociate(priv);
		वापस;
	पूर्ण

	schedule_delayed_work(&priv->adhoc_check,
			      le16_to_cpu(priv->assoc_request.beacon_पूर्णांकerval));
पूर्ण

अटल व्योम ipw_bg_adhoc_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, adhoc_check.work);
	mutex_lock(&priv->mutex);
	ipw_adhoc_check(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_debug_config(काष्ठा ipw_priv *priv)
अणु
	IPW_DEBUG_INFO("Scan completed, no valid APs matched "
		       "[CFG 0x%08X]\n", priv->config);
	अगर (priv->config & CFG_STATIC_CHANNEL)
		IPW_DEBUG_INFO("Channel locked to %d\n", priv->channel);
	अन्यथा
		IPW_DEBUG_INFO("Channel unlocked.\n");
	अगर (priv->config & CFG_STATIC_ESSID)
		IPW_DEBUG_INFO("ESSID locked to '%*pE'\n",
			       priv->essid_len, priv->essid);
	अन्यथा
		IPW_DEBUG_INFO("ESSID unlocked.\n");
	अगर (priv->config & CFG_STATIC_BSSID)
		IPW_DEBUG_INFO("BSSID locked to %pM\n", priv->bssid);
	अन्यथा
		IPW_DEBUG_INFO("BSSID unlocked.\n");
	अगर (priv->capability & CAP_PRIVACY_ON)
		IPW_DEBUG_INFO("PRIVACY on\n");
	अन्यथा
		IPW_DEBUG_INFO("PRIVACY off\n");
	IPW_DEBUG_INFO("RATE MASK: 0x%08X\n", priv->rates_mask);
पूर्ण

अटल व्योम ipw_set_fixed_rate(काष्ठा ipw_priv *priv, पूर्णांक mode)
अणु
	/* TODO: Verअगरy that this works... */
	काष्ठा ipw_fixed_rate fr;
	u32 reg;
	u16 mask = 0;
	u16 new_tx_rates = priv->rates_mask;

	/* Identअगरy 'current FW band' and match it with the fixed
	 * Tx rates */

	चयन (priv->ieee->freq_band) अणु
	हाल LIBIPW_52GHZ_BAND:	/* A only */
		/* IEEE_A */
		अगर (priv->rates_mask & ~LIBIPW_OFDM_RATES_MASK) अणु
			/* Invalid fixed rate mask */
			IPW_DEBUG_WX
			    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
			new_tx_rates = 0;
			अवरोध;
		पूर्ण

		new_tx_rates >>= LIBIPW_OFDM_SHIFT_MASK_A;
		अवरोध;

	शेष:		/* 2.4Ghz or Mixed */
		/* IEEE_B */
		अगर (mode == IEEE_B) अणु
			अगर (new_tx_rates & ~LIBIPW_CCK_RATES_MASK) अणु
				/* Invalid fixed rate mask */
				IPW_DEBUG_WX
				    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
				new_tx_rates = 0;
			पूर्ण
			अवरोध;
		पूर्ण

		/* IEEE_G */
		अगर (new_tx_rates & ~(LIBIPW_CCK_RATES_MASK |
				    LIBIPW_OFDM_RATES_MASK)) अणु
			/* Invalid fixed rate mask */
			IPW_DEBUG_WX
			    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
			new_tx_rates = 0;
			अवरोध;
		पूर्ण

		अगर (LIBIPW_OFDM_RATE_6MB_MASK & new_tx_rates) अणु
			mask |= (LIBIPW_OFDM_RATE_6MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_6MB_MASK;
		पूर्ण

		अगर (LIBIPW_OFDM_RATE_9MB_MASK & new_tx_rates) अणु
			mask |= (LIBIPW_OFDM_RATE_9MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_9MB_MASK;
		पूर्ण

		अगर (LIBIPW_OFDM_RATE_12MB_MASK & new_tx_rates) अणु
			mask |= (LIBIPW_OFDM_RATE_12MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_12MB_MASK;
		पूर्ण

		new_tx_rates |= mask;
		अवरोध;
	पूर्ण

	fr.tx_rates = cpu_to_le16(new_tx_rates);

	reg = ipw_पढ़ो32(priv, IPW_MEM_FIXED_OVERRIDE);
	ipw_ग_लिखो_reg32(priv, reg, *(u32 *) & fr);
पूर्ण

अटल व्योम ipw_पात_scan(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक err;

	अगर (priv->status & STATUS_SCAN_ABORTING) अणु
		IPW_DEBUG_HC("Ignoring concurrent scan abort request.\n");
		वापस;
	पूर्ण
	priv->status |= STATUS_SCAN_ABORTING;

	err = ipw_send_scan_पात(priv);
	अगर (err)
		IPW_DEBUG_HC("Request to abort scan failed.\n");
पूर्ण

अटल व्योम ipw_add_scan_channels(काष्ठा ipw_priv *priv,
				  काष्ठा ipw_scan_request_ext *scan,
				  पूर्णांक scan_type)
अणु
	पूर्णांक channel_index = 0;
	स्थिर काष्ठा libipw_geo *geo;
	पूर्णांक i;

	geo = libipw_get_geo(priv->ieee);

	अगर (priv->ieee->freq_band & LIBIPW_52GHZ_BAND) अणु
		पूर्णांक start = channel_index;
		क्रम (i = 0; i < geo->a_channels; i++) अणु
			अगर ((priv->status & STATUS_ASSOCIATED) &&
			    geo->a[i].channel == priv->channel)
				जारी;
			channel_index++;
			scan->channels_list[channel_index] = geo->a[i].channel;
			ipw_set_scan_type(scan, channel_index,
					  geo->a[i].
					  flags & LIBIPW_CH_PASSIVE_ONLY ?
					  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN :
					  scan_type);
		पूर्ण

		अगर (start != channel_index) अणु
			scan->channels_list[start] = (u8) (IPW_A_MODE << 6) |
			    (channel_index - start);
			channel_index++;
		पूर्ण
	पूर्ण

	अगर (priv->ieee->freq_band & LIBIPW_24GHZ_BAND) अणु
		पूर्णांक start = channel_index;
		अगर (priv->config & CFG_SPEED_SCAN) अणु
			पूर्णांक index;
			u8 channels[LIBIPW_24GHZ_CHANNELS] = अणु
				/* nop out the list */
				[0] = 0
			पूर्ण;

			u8 channel;
			जबतक (channel_index < IPW_SCAN_CHANNELS - 1) अणु
				channel =
				    priv->speed_scan[priv->speed_scan_pos];
				अगर (channel == 0) अणु
					priv->speed_scan_pos = 0;
					channel = priv->speed_scan[0];
				पूर्ण
				अगर ((priv->status & STATUS_ASSOCIATED) &&
				    channel == priv->channel) अणु
					priv->speed_scan_pos++;
					जारी;
				पूर्ण

				/* If this channel has alपढ़ोy been
				 * added in scan, अवरोध from loop
				 * and this will be the first channel
				 * in the next scan.
				 */
				अगर (channels[channel - 1] != 0)
					अवरोध;

				channels[channel - 1] = 1;
				priv->speed_scan_pos++;
				channel_index++;
				scan->channels_list[channel_index] = channel;
				index =
				    libipw_channel_to_index(priv->ieee, channel);
				ipw_set_scan_type(scan, channel_index,
						  geo->bg[index].
						  flags &
						  LIBIPW_CH_PASSIVE_ONLY ?
						  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN
						  : scan_type);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < geo->bg_channels; i++) अणु
				अगर ((priv->status & STATUS_ASSOCIATED) &&
				    geo->bg[i].channel == priv->channel)
					जारी;
				channel_index++;
				scan->channels_list[channel_index] =
				    geo->bg[i].channel;
				ipw_set_scan_type(scan, channel_index,
						  geo->bg[i].
						  flags &
						  LIBIPW_CH_PASSIVE_ONLY ?
						  IPW_SCAN_PASSIVE_FULL_DWELL_SCAN
						  : scan_type);
			पूर्ण
		पूर्ण

		अगर (start != channel_index) अणु
			scan->channels_list[start] = (u8) (IPW_B_MODE << 6) |
			    (channel_index - start);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ipw_passive_dwell_समय(काष्ठा ipw_priv *priv)
अणु
	/* staying on passive channels दीर्घer than the DTIM पूर्णांकerval during a
	 * scan, जबतक associated, causes the firmware to cancel the scan
	 * without notअगरication. Hence, करोn't stay on passive channels दीर्घer
	 * than the beacon पूर्णांकerval.
	 */
	अगर (priv->status & STATUS_ASSOCIATED
	    && priv->assoc_network->beacon_पूर्णांकerval > 10)
		वापस priv->assoc_network->beacon_पूर्णांकerval - 10;
	अन्यथा
		वापस 120;
पूर्ण

अटल पूर्णांक ipw_request_scan_helper(काष्ठा ipw_priv *priv, पूर्णांक type, पूर्णांक direct)
अणु
	काष्ठा ipw_scan_request_ext scan;
	पूर्णांक err = 0, scan_type;

	अगर (!(priv->status & STATUS_INIT) ||
	    (priv->status & STATUS_EXIT_PENDING))
		वापस 0;

	mutex_lock(&priv->mutex);

	अगर (direct && (priv->direct_scan_ssid_len == 0)) अणु
		IPW_DEBUG_HC("Direct scan requested but no SSID to scan for\n");
		priv->status &= ~STATUS_सूचीECT_SCAN_PENDING;
		जाओ करोne;
	पूर्ण

	अगर (priv->status & STATUS_SCANNING) अणु
		IPW_DEBUG_HC("Concurrent scan requested.  Queuing.\n");
		priv->status |= direct ? STATUS_सूचीECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		जाओ करोne;
	पूर्ण

	अगर (!(priv->status & STATUS_SCAN_FORCED) &&
	    priv->status & STATUS_SCAN_ABORTING) अणु
		IPW_DEBUG_HC("Scan request while abort pending.  Queuing.\n");
		priv->status |= direct ? STATUS_सूचीECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		जाओ करोne;
	पूर्ण

	अगर (priv->status & STATUS_RF_KILL_MASK) अणु
		IPW_DEBUG_HC("Queuing scan due to RF Kill activation\n");
		priv->status |= direct ? STATUS_सूचीECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		जाओ करोne;
	पूर्ण

	स_रखो(&scan, 0, माप(scan));
	scan.full_scan_index = cpu_to_le32(libipw_get_scans(priv->ieee));

	अगर (type == IW_SCAN_TYPE_PASSIVE) अणु
		IPW_DEBUG_WX("use passive scanning\n");
		scan_type = IPW_SCAN_PASSIVE_FULL_DWELL_SCAN;
		scan.dwell_समय[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
			cpu_to_le16(ipw_passive_dwell_समय(priv));
		ipw_add_scan_channels(priv, &scan, scan_type);
		जाओ send_request;
	पूर्ण

	/* Use active scan by शेष. */
	अगर (priv->config & CFG_SPEED_SCAN)
		scan.dwell_समय[IPW_SCAN_ACTIVE_BROADCAST_SCAN] =
			cpu_to_le16(30);
	अन्यथा
		scan.dwell_समय[IPW_SCAN_ACTIVE_BROADCAST_SCAN] =
			cpu_to_le16(20);

	scan.dwell_समय[IPW_SCAN_ACTIVE_BROADCAST_AND_सूचीECT_SCAN] =
		cpu_to_le16(20);

	scan.dwell_समय[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
		cpu_to_le16(ipw_passive_dwell_समय(priv));
	scan.dwell_समय[IPW_SCAN_ACTIVE_सूचीECT_SCAN] = cpu_to_le16(20);

#अगर_घोषित CONFIG_IPW2200_MONITOR
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
		u8 channel;
		u8 band = 0;

		चयन (libipw_is_valid_channel(priv->ieee, priv->channel)) अणु
		हाल LIBIPW_52GHZ_BAND:
			band = (u8) (IPW_A_MODE << 6) | 1;
			channel = priv->channel;
			अवरोध;

		हाल LIBIPW_24GHZ_BAND:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = priv->channel;
			अवरोध;

		शेष:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = 9;
			अवरोध;
		पूर्ण

		scan.channels_list[0] = band;
		scan.channels_list[1] = channel;
		ipw_set_scan_type(&scan, 1, IPW_SCAN_PASSIVE_FULL_DWELL_SCAN);

		/* NOTE:  The card will sit on this channel क्रम this समय
		 * period.  Scan पातs are timing sensitive and frequently
		 * result in firmware restarts.  As such, it is best to
		 * set a small dwell_समय here and just keep re-issuing
		 * scans.  Otherwise fast channel hopping will not actually
		 * hop channels.
		 *
		 * TODO: Move SPEED SCAN support to all modes and bands */
		scan.dwell_समय[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
			cpu_to_le16(2000);
	पूर्ण अन्यथा अणु
#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */
		/* Honor direct scans first, otherwise अगर we are roaming make
		 * this a direct scan क्रम the current network.  Finally,
		 * ensure that every other scan is a fast channel hop scan */
		अगर (direct) अणु
			err = ipw_send_ssid(priv, priv->direct_scan_ssid,
			                    priv->direct_scan_ssid_len);
			अगर (err) अणु
				IPW_DEBUG_HC("Attempt to send SSID command  "
					     "failed\n");
				जाओ करोne;
			पूर्ण

			scan_type = IPW_SCAN_ACTIVE_BROADCAST_AND_सूचीECT_SCAN;
		पूर्ण अन्यथा अगर ((priv->status & STATUS_ROAMING)
			   || (!(priv->status & STATUS_ASSOCIATED)
			       && (priv->config & CFG_STATIC_ESSID)
			       && (le32_to_cpu(scan.full_scan_index) % 2))) अणु
			err = ipw_send_ssid(priv, priv->essid, priv->essid_len);
			अगर (err) अणु
				IPW_DEBUG_HC("Attempt to send SSID command "
					     "failed.\n");
				जाओ करोne;
			पूर्ण

			scan_type = IPW_SCAN_ACTIVE_BROADCAST_AND_सूचीECT_SCAN;
		पूर्ण अन्यथा
			scan_type = IPW_SCAN_ACTIVE_BROADCAST_SCAN;

		ipw_add_scan_channels(priv, &scan, scan_type);
#अगर_घोषित CONFIG_IPW2200_MONITOR
	पूर्ण
#पूर्ण_अगर

send_request:
	err = ipw_send_scan_request_ext(priv, &scan);
	अगर (err) अणु
		IPW_DEBUG_HC("Sending scan command failed: %08X\n", err);
		जाओ करोne;
	पूर्ण

	priv->status |= STATUS_SCANNING;
	अगर (direct) अणु
		priv->status &= ~STATUS_सूचीECT_SCAN_PENDING;
		priv->direct_scan_ssid_len = 0;
	पूर्ण अन्यथा
		priv->status &= ~STATUS_SCAN_PENDING;

	schedule_delayed_work(&priv->scan_check, IPW_SCAN_CHECK_WATCHDOG);
करोne:
	mutex_unlock(&priv->mutex);
	वापस err;
पूर्ण

अटल व्योम ipw_request_passive_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, request_passive_scan.work);
	ipw_request_scan_helper(priv, IW_SCAN_TYPE_PASSIVE, 0);
पूर्ण

अटल व्योम ipw_request_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, request_scan.work);
	ipw_request_scan_helper(priv, IW_SCAN_TYPE_ACTIVE, 0);
पूर्ण

अटल व्योम ipw_request_direct_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, request_direct_scan.work);
	ipw_request_scan_helper(priv, IW_SCAN_TYPE_ACTIVE, 1);
पूर्ण

अटल व्योम ipw_bg_पात_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, पात_scan);
	mutex_lock(&priv->mutex);
	ipw_पात_scan(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ipw_wpa_enable(काष्ठा ipw_priv *priv, पूर्णांक value)
अणु
	/* This is called when wpa_supplicant loads and बंदs the driver
	 * पूर्णांकerface. */
	priv->ieee->wpa_enabled = value;
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wpa_set_auth_algs(काष्ठा ipw_priv *priv, पूर्णांक value)
अणु
	काष्ठा libipw_device *ieee = priv->ieee;
	काष्ठा libipw_security sec = अणु
		.flags = SEC_AUTH_MODE,
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (value & IW_AUTH_ALG_SHARED_KEY) अणु
		sec.auth_mode = WLAN_AUTH_SHARED_KEY;
		ieee->खोलो_wep = 0;
	पूर्ण अन्यथा अगर (value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
		sec.auth_mode = WLAN_AUTH_OPEN;
		ieee->खोलो_wep = 1;
	पूर्ण अन्यथा अगर (value & IW_AUTH_ALG_LEAP) अणु
		sec.auth_mode = WLAN_AUTH_LEAP;
		ieee->खोलो_wep = 1;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (ieee->set_security)
		ieee->set_security(ieee->dev, &sec);
	अन्यथा
		ret = -EOPNOTSUPP;

	वापस ret;
पूर्ण

अटल व्योम ipw_wpa_assoc_frame(काष्ठा ipw_priv *priv, अक्षर *wpa_ie,
				पूर्णांक wpa_ie_len)
अणु
	/* make sure WPA is enabled */
	ipw_wpa_enable(priv, 1);
पूर्ण

अटल पूर्णांक ipw_set_rsn_capa(काष्ठा ipw_priv *priv,
			    अक्षर *capabilities, पूर्णांक length)
अणु
	IPW_DEBUG_HC("HOST_CMD_RSN_CAPABILITIES\n");

	वापस ipw_send_cmd_pdu(priv, IPW_CMD_RSN_CAPABILITIES, length,
				capabilities);
पूर्ण

/*
 * WE-18 support
 */

/* SIOCSIWGENIE */
अटल पूर्णांक ipw_wx_set_genie(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	u8 *buf;
	पूर्णांक err = 0;

	अगर (wrqu->data.length > MAX_WPA_IE_LEN ||
	    (wrqu->data.length && extra == शून्य))
		वापस -EINVAL;

	अगर (wrqu->data.length) अणु
		buf = kmemdup(extra, wrqu->data.length, GFP_KERNEL);
		अगर (buf == शून्य) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = wrqu->data.length;
	पूर्ण अन्यथा अणु
		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = शून्य;
		ieee->wpa_ie_len = 0;
	पूर्ण

	ipw_wpa_assoc_frame(priv, ieee->wpa_ie, ieee->wpa_ie_len);
      out:
	वापस err;
पूर्ण

/* SIOCGIWGENIE */
अटल पूर्णांक ipw_wx_get_genie(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	पूर्णांक err = 0;

	अगर (ieee->wpa_ie_len == 0 || ieee->wpa_ie == शून्य) अणु
		wrqu->data.length = 0;
		जाओ out;
	पूर्ण

	अगर (wrqu->data.length < ieee->wpa_ie_len) अणु
		err = -E2BIG;
		जाओ out;
	पूर्ण

	wrqu->data.length = ieee->wpa_ie_len;
	स_नकल(extra, ieee->wpa_ie, ieee->wpa_ie_len);

      out:
	वापस err;
पूर्ण

अटल पूर्णांक wext_cipher2level(पूर्णांक cipher)
अणु
	चयन (cipher) अणु
	हाल IW_AUTH_CIPHER_NONE:
		वापस SEC_LEVEL_0;
	हाल IW_AUTH_CIPHER_WEP40:
	हाल IW_AUTH_CIPHER_WEP104:
		वापस SEC_LEVEL_1;
	हाल IW_AUTH_CIPHER_TKIP:
		वापस SEC_LEVEL_2;
	हाल IW_AUTH_CIPHER_CCMP:
		वापस SEC_LEVEL_3;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/* SIOCSIWAUTH */
अटल पूर्णांक ipw_wx_set_auth(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	काष्ठा iw_param *param = &wrqu->param;
	काष्ठा lib80211_crypt_data *crypt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
		अवरोध;
	हाल IW_AUTH_CIPHER_PAIRWISE:
		ipw_set_hw_decrypt_unicast(priv,
					   wext_cipher2level(param->value));
		अवरोध;
	हाल IW_AUTH_CIPHER_GROUP:
		ipw_set_hw_decrypt_multicast(priv,
					     wext_cipher2level(param->value));
		अवरोध;
	हाल IW_AUTH_KEY_MGMT:
		/*
		 * ipw2200 करोes not use these parameters
		 */
		अवरोध;

	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		crypt = priv->ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx];
		अगर (!crypt || !crypt->ops->set_flags || !crypt->ops->get_flags)
			अवरोध;

		flags = crypt->ops->get_flags(crypt->priv);

		अगर (param->value)
			flags |= IEEE80211_CRYPTO_TKIP_COUNTERMEASURES;
		अन्यथा
			flags &= ~IEEE80211_CRYPTO_TKIP_COUNTERMEASURES;

		crypt->ops->set_flags(flags, crypt->priv);

		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:अणु
			/* HACK:
			 *
			 * wpa_supplicant calls set_wpa_enabled when the driver
			 * is loaded and unloaded, regardless of अगर WPA is being
			 * used.  No other calls are made which can be used to
			 * determine अगर encryption will be used or not prior to
			 * association being expected.  If encryption is not being
			 * used, drop_unencrypted is set to false, अन्यथा true -- we
			 * can use this to determine अगर the CAP_PRIVACY_ON bit should
			 * be set.
			 */
			काष्ठा libipw_security sec = अणु
				.flags = SEC_ENABLED,
				.enabled = param->value,
			पूर्ण;
			priv->ieee->drop_unencrypted = param->value;
			/* We only change SEC_LEVEL क्रम खोलो mode. Others
			 * are set by ipw_wpa_set_encryption.
			 */
			अगर (!param->value) अणु
				sec.flags |= SEC_LEVEL;
				sec.level = SEC_LEVEL_0;
			पूर्ण अन्यथा अणु
				sec.flags |= SEC_LEVEL;
				sec.level = SEC_LEVEL_1;
			पूर्ण
			अगर (priv->ieee->set_security)
				priv->ieee->set_security(priv->ieee->dev, &sec);
			अवरोध;
		पूर्ण

	हाल IW_AUTH_80211_AUTH_ALG:
		ret = ipw_wpa_set_auth_algs(priv, param->value);
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		ret = ipw_wpa_enable(priv, param->value);
		ipw_disassociate(priv);
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ieee->ieee802_1x = param->value;
		अवरोध;

	हाल IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = param->value;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

/* SIOCGIWAUTH */
अटल पूर्णांक ipw_wx_get_auth(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	काष्ठा lib80211_crypt_data *crypt;
	काष्ठा iw_param *param = &wrqu->param;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		/*
		 * wpa_supplicant will control these पूर्णांकernally
		 */
		वापस -EOPNOTSUPP;

	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		crypt = priv->ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx];
		अगर (!crypt || !crypt->ops->get_flags)
			अवरोध;

		param->value = (crypt->ops->get_flags(crypt->priv) &
				IEEE80211_CRYPTO_TKIP_COUNTERMEASURES) ? 1 : 0;

		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		param->value = ieee->drop_unencrypted;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		param->value = ieee->sec.auth_mode;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		param->value = ieee->wpa_enabled;
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		param->value = ieee->ieee802_1x;
		अवरोध;

	हाल IW_AUTH_ROAMING_CONTROL:
	हाल IW_AUTH_PRIVACY_INVOKED:
		param->value = ieee->privacy_invoked;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/* SIOCSIWENCODEEXT */
अटल पूर्णांक ipw_wx_set_encodeext(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;

	अगर (hwcrypto) अणु
		अगर (ext->alg == IW_ENCODE_ALG_TKIP) अणु
			/* IPW HW can't build TKIP MIC,
			   host decryption still needed */
			अगर (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY)
				priv->ieee->host_mc_decrypt = 1;
			अन्यथा अणु
				priv->ieee->host_encrypt = 0;
				priv->ieee->host_encrypt_msdu = 1;
				priv->ieee->host_decrypt = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->ieee->host_encrypt = 0;
			priv->ieee->host_encrypt_msdu = 0;
			priv->ieee->host_decrypt = 0;
			priv->ieee->host_mc_decrypt = 0;
		पूर्ण
	पूर्ण

	वापस libipw_wx_set_encodeext(priv->ieee, info, wrqu, extra);
पूर्ण

/* SIOCGIWENCODEEXT */
अटल पूर्णांक ipw_wx_get_encodeext(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_encodeext(priv->ieee, info, wrqu, extra);
पूर्ण

/* SIOCSIWMLME */
अटल पूर्णांक ipw_wx_set_mlme(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;

	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		/* silently ignore */
		अवरोध;

	हाल IW_MLME_DISASSOC:
		ipw_disassociate(priv);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IPW2200_QOS

/* QoS */
/*
* get the modulation type of the current network or
* the card current mode
*/
अटल u8 ipw_qos_current_mode(काष्ठा ipw_priv * priv)
अणु
	u8 mode = 0;

	अगर (priv->status & STATUS_ASSOCIATED) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->ieee->lock, flags);
		mode = priv->assoc_network->mode;
		spin_unlock_irqrestore(&priv->ieee->lock, flags);
	पूर्ण अन्यथा अणु
		mode = priv->ieee->mode;
	पूर्ण
	IPW_DEBUG_QOS("QoS network/card mode %d\n", mode);
	वापस mode;
पूर्ण

/*
* Handle management frame beacon and probe response
*/
अटल पूर्णांक ipw_qos_handle_probe_response(काष्ठा ipw_priv *priv,
					 पूर्णांक active_network,
					 काष्ठा libipw_network *network)
अणु
	u32 size = माप(काष्ठा libipw_qos_parameters);

	अगर (network->capability & WLAN_CAPABILITY_IBSS)
		network->qos_data.active = network->qos_data.supported;

	अगर (network->flags & NETWORK_HAS_QOS_MASK) अणु
		अगर (active_network &&
		    (network->flags & NETWORK_HAS_QOS_PARAMETERS))
			network->qos_data.active = network->qos_data.supported;

		अगर ((network->qos_data.active == 1) && (active_network == 1) &&
		    (network->flags & NETWORK_HAS_QOS_PARAMETERS) &&
		    (network->qos_data.old_param_count !=
		     network->qos_data.param_count)) अणु
			network->qos_data.old_param_count =
			    network->qos_data.param_count;
			schedule_work(&priv->qos_activate);
			IPW_DEBUG_QOS("QoS parameters change call "
				      "qos_activate\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((priv->ieee->mode == IEEE_B) || (network->mode == IEEE_B))
			स_नकल(&network->qos_data.parameters,
			       &def_parameters_CCK, size);
		अन्यथा
			स_नकल(&network->qos_data.parameters,
			       &def_parameters_OFDM, size);

		अगर ((network->qos_data.active == 1) && (active_network == 1)) अणु
			IPW_DEBUG_QOS("QoS was disabled call qos_activate\n");
			schedule_work(&priv->qos_activate);
		पूर्ण

		network->qos_data.active = 0;
		network->qos_data.supported = 0;
	पूर्ण
	अगर ((priv->status & STATUS_ASSOCIATED) &&
	    (priv->ieee->iw_mode == IW_MODE_ADHOC) && (active_network == 0)) अणु
		अगर (!ether_addr_equal(network->bssid, priv->bssid))
			अगर (network->capability & WLAN_CAPABILITY_IBSS)
				अगर ((network->ssid_len ==
				     priv->assoc_network->ssid_len) &&
				    !स_भेद(network->ssid,
					    priv->assoc_network->ssid,
					    network->ssid_len)) अणु
					schedule_work(&priv->merge_networks);
				पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
* This function set up the firmware to support QoS. It sends
* IPW_CMD_QOS_PARAMETERS and IPW_CMD_WME_INFO
*/
अटल पूर्णांक ipw_qos_activate(काष्ठा ipw_priv *priv,
			    काष्ठा libipw_qos_data *qos_network_data)
अणु
	पूर्णांक err;
	काष्ठा libipw_qos_parameters qos_parameters[QOS_QOS_SETS];
	काष्ठा libipw_qos_parameters *active_one = शून्य;
	u32 size = माप(काष्ठा libipw_qos_parameters);
	u32 burst_duration;
	पूर्णांक i;
	u8 type;

	type = ipw_qos_current_mode(priv);

	active_one = &(qos_parameters[QOS_PARAM_SET_DEF_CCK]);
	स_नकल(active_one, priv->qos_data.def_qos_parm_CCK, size);
	active_one = &(qos_parameters[QOS_PARAM_SET_DEF_OFDM]);
	स_नकल(active_one, priv->qos_data.def_qos_parm_OFDM, size);

	अगर (qos_network_data == शून्य) अणु
		अगर (type == IEEE_B) अणु
			IPW_DEBUG_QOS("QoS activate network mode %d\n", type);
			active_one = &def_parameters_CCK;
		पूर्ण अन्यथा
			active_one = &def_parameters_OFDM;

		स_नकल(&qos_parameters[QOS_PARAM_SET_ACTIVE], active_one, size);
		burst_duration = ipw_qos_get_burst_duration(priv);
		क्रम (i = 0; i < QOS_QUEUE_NUM; i++)
			qos_parameters[QOS_PARAM_SET_ACTIVE].tx_op_limit[i] =
			    cpu_to_le16(burst_duration);
	पूर्ण अन्यथा अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (type == IEEE_B) अणु
			IPW_DEBUG_QOS("QoS activate IBSS network mode %d\n",
				      type);
			अगर (priv->qos_data.qos_enable == 0)
				active_one = &def_parameters_CCK;
			अन्यथा
				active_one = priv->qos_data.def_qos_parm_CCK;
		पूर्ण अन्यथा अणु
			अगर (priv->qos_data.qos_enable == 0)
				active_one = &def_parameters_OFDM;
			अन्यथा
				active_one = priv->qos_data.def_qos_parm_OFDM;
		पूर्ण
		स_नकल(&qos_parameters[QOS_PARAM_SET_ACTIVE], active_one, size);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक active;

		spin_lock_irqsave(&priv->ieee->lock, flags);
		active_one = &(qos_network_data->parameters);
		qos_network_data->old_param_count =
		    qos_network_data->param_count;
		स_नकल(&qos_parameters[QOS_PARAM_SET_ACTIVE], active_one, size);
		active = qos_network_data->supported;
		spin_unlock_irqrestore(&priv->ieee->lock, flags);

		अगर (active == 0) अणु
			burst_duration = ipw_qos_get_burst_duration(priv);
			क्रम (i = 0; i < QOS_QUEUE_NUM; i++)
				qos_parameters[QOS_PARAM_SET_ACTIVE].
				    tx_op_limit[i] = cpu_to_le16(burst_duration);
		पूर्ण
	पूर्ण

	IPW_DEBUG_QOS("QoS sending IPW_CMD_QOS_PARAMETERS\n");
	err = ipw_send_qos_params_command(priv, &qos_parameters[0]);
	अगर (err)
		IPW_DEBUG_QOS("QoS IPW_CMD_QOS_PARAMETERS failed\n");

	वापस err;
पूर्ण

/*
* send IPW_CMD_WME_INFO to the firmware
*/
अटल पूर्णांक ipw_qos_set_info_element(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा libipw_qos_inक्रमmation_element qos_info;

	अगर (priv == शून्य)
		वापस -1;

	qos_info.elementID = QOS_ELEMENT_ID;
	qos_info.length = माप(काष्ठा libipw_qos_inक्रमmation_element) - 2;

	qos_info.version = QOS_VERSION_1;
	qos_info.ac_info = 0;

	स_नकल(qos_info.qui, qos_oui, QOS_OUI_LEN);
	qos_info.qui_type = QOS_OUI_TYPE;
	qos_info.qui_subtype = QOS_OUI_INFO_SUB_TYPE;

	ret = ipw_send_qos_info_command(priv, &qos_info);
	अगर (ret != 0) अणु
		IPW_DEBUG_QOS("QoS error calling ipw_send_qos_info_command\n");
	पूर्ण
	वापस ret;
पूर्ण

/*
* Set the QoS parameter with the association request काष्ठाure
*/
अटल पूर्णांक ipw_qos_association(काष्ठा ipw_priv *priv,
			       काष्ठा libipw_network *network)
अणु
	पूर्णांक err = 0;
	काष्ठा libipw_qos_data *qos_data = शून्य;
	काष्ठा libipw_qos_data ibss_data = अणु
		.supported = 1,
		.active = 1,
	पूर्ण;

	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		BUG_ON(!(network->capability & WLAN_CAPABILITY_IBSS));

		qos_data = &ibss_data;
		अवरोध;

	हाल IW_MODE_INFRA:
		qos_data = &network->qos_data;
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण

	err = ipw_qos_activate(priv, qos_data);
	अगर (err) अणु
		priv->assoc_request.policy_support &= ~HC_QOS_SUPPORT_ASSOC;
		वापस err;
	पूर्ण

	अगर (priv->qos_data.qos_enable && qos_data->supported) अणु
		IPW_DEBUG_QOS("QoS will be enabled for this association\n");
		priv->assoc_request.policy_support |= HC_QOS_SUPPORT_ASSOC;
		वापस ipw_qos_set_info_element(priv);
	पूर्ण

	वापस 0;
पूर्ण

/*
* handling the beaconing responses. अगर we get dअगरferent QoS setting
* off the network from the associated setting, adjust the QoS
* setting
*/
अटल व्योम ipw_qos_association_resp(काष्ठा ipw_priv *priv,
				    काष्ठा libipw_network *network)
अणु
	अचिन्हित दीर्घ flags;
	u32 size = माप(काष्ठा libipw_qos_parameters);
	पूर्णांक set_qos_param = 0;

	अगर ((priv == शून्य) || (network == शून्य) ||
	    (priv->assoc_network == शून्य))
		वापस;

	अगर (!(priv->status & STATUS_ASSOCIATED))
		वापस;

	अगर ((priv->ieee->iw_mode != IW_MODE_INFRA))
		वापस;

	spin_lock_irqsave(&priv->ieee->lock, flags);
	अगर (network->flags & NETWORK_HAS_QOS_PARAMETERS) अणु
		स_नकल(&priv->assoc_network->qos_data, &network->qos_data,
		       माप(काष्ठा libipw_qos_data));
		priv->assoc_network->qos_data.active = 1;
		अगर ((network->qos_data.old_param_count !=
		     network->qos_data.param_count)) अणु
			set_qos_param = 1;
			network->qos_data.old_param_count =
			    network->qos_data.param_count;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर ((network->mode == IEEE_B) || (priv->ieee->mode == IEEE_B))
			स_नकल(&priv->assoc_network->qos_data.parameters,
			       &def_parameters_CCK, size);
		अन्यथा
			स_नकल(&priv->assoc_network->qos_data.parameters,
			       &def_parameters_OFDM, size);
		priv->assoc_network->qos_data.active = 0;
		priv->assoc_network->qos_data.supported = 0;
		set_qos_param = 1;
	पूर्ण

	spin_unlock_irqrestore(&priv->ieee->lock, flags);

	अगर (set_qos_param == 1)
		schedule_work(&priv->qos_activate);
पूर्ण

अटल u32 ipw_qos_get_burst_duration(काष्ठा ipw_priv *priv)
अणु
	u32 ret = 0;

	अगर (!priv)
		वापस 0;

	अगर (!(priv->ieee->modulation & LIBIPW_OFDM_MODULATION))
		ret = priv->qos_data.burst_duration_CCK;
	अन्यथा
		ret = priv->qos_data.burst_duration_OFDM;

	वापस ret;
पूर्ण

/*
* Initialize the setting of QoS global
*/
अटल व्योम ipw_qos_init(काष्ठा ipw_priv *priv, पूर्णांक enable,
			 पूर्णांक burst_enable, u32 burst_duration_CCK,
			 u32 burst_duration_OFDM)
अणु
	priv->qos_data.qos_enable = enable;

	अगर (priv->qos_data.qos_enable) अणु
		priv->qos_data.def_qos_parm_CCK = &def_qos_parameters_CCK;
		priv->qos_data.def_qos_parm_OFDM = &def_qos_parameters_OFDM;
		IPW_DEBUG_QOS("QoS is enabled\n");
	पूर्ण अन्यथा अणु
		priv->qos_data.def_qos_parm_CCK = &def_parameters_CCK;
		priv->qos_data.def_qos_parm_OFDM = &def_parameters_OFDM;
		IPW_DEBUG_QOS("QoS is not enabled\n");
	पूर्ण

	priv->qos_data.burst_enable = burst_enable;

	अगर (burst_enable) अणु
		priv->qos_data.burst_duration_CCK = burst_duration_CCK;
		priv->qos_data.burst_duration_OFDM = burst_duration_OFDM;
	पूर्ण अन्यथा अणु
		priv->qos_data.burst_duration_CCK = 0;
		priv->qos_data.burst_duration_OFDM = 0;
	पूर्ण
पूर्ण

/*
* map the packet priority to the right TX Queue
*/
अटल पूर्णांक ipw_get_tx_queue_number(काष्ठा ipw_priv *priv, u16 priority)
अणु
	अगर (priority > 7 || !priv->qos_data.qos_enable)
		priority = 0;

	वापस from_priority_to_tx_queue[priority] - 1;
पूर्ण

अटल पूर्णांक ipw_is_qos_active(काष्ठा net_device *dev,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा libipw_qos_data *qos_data = शून्य;
	पूर्णांक active, supported;
	u8 *daddr = skb->data + ETH_ALEN;
	पूर्णांक unicast = !is_multicast_ether_addr(daddr);

	अगर (!(priv->status & STATUS_ASSOCIATED))
		वापस 0;

	qos_data = &priv->assoc_network->qos_data;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (unicast == 0)
			qos_data->active = 0;
		अन्यथा
			qos_data->active = qos_data->supported;
	पूर्ण
	active = qos_data->active;
	supported = qos_data->supported;
	IPW_DEBUG_QOS("QoS  %d network is QoS active %d  supported %d  "
		      "unicast %d\n",
		      priv->qos_data.qos_enable, active, supported, unicast);
	अगर (active && priv->qos_data.qos_enable)
		वापस 1;

	वापस 0;

पूर्ण
/*
* add QoS parameter to the TX command
*/
अटल पूर्णांक ipw_qos_set_tx_queue_command(काष्ठा ipw_priv *priv,
					u16 priority,
					काष्ठा tfd_data *tfd)
अणु
	पूर्णांक tx_queue_id = 0;


	tx_queue_id = from_priority_to_tx_queue[priority] - 1;
	tfd->tx_flags_ext |= DCT_FLAG_EXT_QOS_ENABLED;

	अगर (priv->qos_data.qos_no_ack_mask & (1UL << tx_queue_id)) अणु
		tfd->tx_flags &= ~DCT_FLAG_ACK_REQD;
		tfd->tfd.tfd_26.mchdr.qos_ctrl |= cpu_to_le16(CTRL_QOS_NO_ACK);
	पूर्ण
	वापस 0;
पूर्ण

/*
* background support to run QoS activate functionality
*/
अटल व्योम ipw_bg_qos_activate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, qos_activate);

	mutex_lock(&priv->mutex);

	अगर (priv->status & STATUS_ASSOCIATED)
		ipw_qos_activate(priv, &(priv->assoc_network->qos_data));

	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ipw_handle_probe_response(काष्ठा net_device *dev,
				     काष्ठा libipw_probe_response *resp,
				     काष्ठा libipw_network *network)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक active_network = ((priv->status & STATUS_ASSOCIATED) &&
			      (network == priv->assoc_network));

	ipw_qos_handle_probe_response(priv, active_network, network);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_handle_beacon(काष्ठा net_device *dev,
			     काष्ठा libipw_beacon *resp,
			     काष्ठा libipw_network *network)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक active_network = ((priv->status & STATUS_ASSOCIATED) &&
			      (network == priv->assoc_network));

	ipw_qos_handle_probe_response(priv, active_network, network);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_handle_assoc_response(काष्ठा net_device *dev,
				     काष्ठा libipw_assoc_response *resp,
				     काष्ठा libipw_network *network)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	ipw_qos_association_resp(priv, network);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_send_qos_params_command(काष्ठा ipw_priv *priv, काष्ठा libipw_qos_parameters
				       *qos_param)
अणु
	वापस ipw_send_cmd_pdu(priv, IPW_CMD_QOS_PARAMETERS,
				माप(*qos_param) * 3, qos_param);
पूर्ण

अटल पूर्णांक ipw_send_qos_info_command(काष्ठा ipw_priv *priv, काष्ठा libipw_qos_inक्रमmation_element
				     *qos_param)
अणु
	वापस ipw_send_cmd_pdu(priv, IPW_CMD_WME_INFO, माप(*qos_param),
				qos_param);
पूर्ण

#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

अटल पूर्णांक ipw_associate_network(काष्ठा ipw_priv *priv,
				 काष्ठा libipw_network *network,
				 काष्ठा ipw_supported_rates *rates, पूर्णांक roaming)
अणु
	पूर्णांक err;

	अगर (priv->config & CFG_FIXED_RATE)
		ipw_set_fixed_rate(priv, network->mode);

	अगर (!(priv->config & CFG_STATIC_ESSID)) अणु
		priv->essid_len = min(network->ssid_len,
				      (u8) IW_ESSID_MAX_SIZE);
		स_नकल(priv->essid, network->ssid, priv->essid_len);
	पूर्ण

	network->last_associate = jअगरfies;

	स_रखो(&priv->assoc_request, 0, माप(priv->assoc_request));
	priv->assoc_request.channel = network->channel;
	priv->assoc_request.auth_key = 0;

	अगर ((priv->capability & CAP_PRIVACY_ON) &&
	    (priv->ieee->sec.auth_mode == WLAN_AUTH_SHARED_KEY)) अणु
		priv->assoc_request.auth_type = AUTH_SHARED_KEY;
		priv->assoc_request.auth_key = priv->ieee->sec.active_key;

		अगर (priv->ieee->sec.level == SEC_LEVEL_1)
			ipw_send_wep_keys(priv, DCW_WEP_KEY_SEC_TYPE_WEP);

	पूर्ण अन्यथा अगर ((priv->capability & CAP_PRIVACY_ON) &&
		   (priv->ieee->sec.auth_mode == WLAN_AUTH_LEAP))
		priv->assoc_request.auth_type = AUTH_LEAP;
	अन्यथा
		priv->assoc_request.auth_type = AUTH_OPEN;

	अगर (priv->ieee->wpa_ie_len) अणु
		priv->assoc_request.policy_support = cpu_to_le16(0x02);	/* RSN active */
		ipw_set_rsn_capa(priv, priv->ieee->wpa_ie,
				 priv->ieee->wpa_ie_len);
	पूर्ण

	/*
	 * It is valid क्रम our ieee device to support multiple modes, but
	 * when it comes to associating to a given network we have to choose
	 * just one mode.
	 */
	अगर (network->mode & priv->ieee->mode & IEEE_A)
		priv->assoc_request.ieee_mode = IPW_A_MODE;
	अन्यथा अगर (network->mode & priv->ieee->mode & IEEE_G)
		priv->assoc_request.ieee_mode = IPW_G_MODE;
	अन्यथा अगर (network->mode & priv->ieee->mode & IEEE_B)
		priv->assoc_request.ieee_mode = IPW_B_MODE;

	priv->assoc_request.capability = cpu_to_le16(network->capability);
	अगर ((network->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
	    && !(priv->config & CFG_PREAMBLE_LONG)) अणु
		priv->assoc_request.preamble_length = DCT_FLAG_SHORT_PREAMBLE;
	पूर्ण अन्यथा अणु
		priv->assoc_request.preamble_length = DCT_FLAG_LONG_PREAMBLE;

		/* Clear the लघु preamble अगर we won't be supporting it */
		priv->assoc_request.capability &=
		    ~cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);
	पूर्ण

	/* Clear capability bits that aren't used in Ad Hoc */
	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC)
		priv->assoc_request.capability &=
		    ~cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT_TIME);

	IPW_DEBUG_ASSOC("%ssociation attempt: '%*pE', channel %d, 802.11%c [%d], %s[:%s], enc=%s%s%s%c%c\n",
			roaming ? "Rea" : "A",
			priv->essid_len, priv->essid,
			network->channel,
			ipw_modes[priv->assoc_request.ieee_mode],
			rates->num_rates,
			(priv->assoc_request.preamble_length ==
			 DCT_FLAG_LONG_PREAMBLE) ? "long" : "short",
			network->capability &
			WLAN_CAPABILITY_SHORT_PREAMBLE ? "short" : "long",
			priv->capability & CAP_PRIVACY_ON ? "on " : "off",
			priv->capability & CAP_PRIVACY_ON ?
			(priv->capability & CAP_SHARED_KEY ? "(shared)" :
			 "(open)") : "",
			priv->capability & CAP_PRIVACY_ON ? " key=" : "",
			priv->capability & CAP_PRIVACY_ON ?
			'1' + priv->ieee->sec.active_key : '.',
			priv->capability & CAP_PRIVACY_ON ? '.' : ' ');

	priv->assoc_request.beacon_पूर्णांकerval = cpu_to_le16(network->beacon_पूर्णांकerval);
	अगर ((priv->ieee->iw_mode == IW_MODE_ADHOC) &&
	    (network->समय_stamp[0] == 0) && (network->समय_stamp[1] == 0)) अणु
		priv->assoc_request.assoc_type = HC_IBSS_START;
		priv->assoc_request.assoc_tsf_msw = 0;
		priv->assoc_request.assoc_tsf_lsw = 0;
	पूर्ण अन्यथा अणु
		अगर (unlikely(roaming))
			priv->assoc_request.assoc_type = HC_REASSOCIATE;
		अन्यथा
			priv->assoc_request.assoc_type = HC_ASSOCIATE;
		priv->assoc_request.assoc_tsf_msw = cpu_to_le32(network->समय_stamp[1]);
		priv->assoc_request.assoc_tsf_lsw = cpu_to_le32(network->समय_stamp[0]);
	पूर्ण

	स_नकल(priv->assoc_request.bssid, network->bssid, ETH_ALEN);

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		eth_broadcast_addr(priv->assoc_request.dest);
		priv->assoc_request.atim_winकरोw = cpu_to_le16(network->atim_winकरोw);
	पूर्ण अन्यथा अणु
		स_नकल(priv->assoc_request.dest, network->bssid, ETH_ALEN);
		priv->assoc_request.atim_winकरोw = 0;
	पूर्ण

	priv->assoc_request.listen_पूर्णांकerval = cpu_to_le16(network->listen_पूर्णांकerval);

	err = ipw_send_ssid(priv, priv->essid, priv->essid_len);
	अगर (err) अणु
		IPW_DEBUG_HC("Attempt to send SSID command failed.\n");
		वापस err;
	पूर्ण

	rates->ieee_mode = priv->assoc_request.ieee_mode;
	rates->purpose = IPW_RATE_CONNECT;
	ipw_send_supported_rates(priv, rates);

	अगर (priv->assoc_request.ieee_mode == IPW_G_MODE)
		priv->sys_config.करोt11g_स्वतः_detection = 1;
	अन्यथा
		priv->sys_config.करोt11g_स्वतः_detection = 0;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC)
		priv->sys_config.answer_broadcast_ssid_probe = 1;
	अन्यथा
		priv->sys_config.answer_broadcast_ssid_probe = 0;

	err = ipw_send_प्रणाली_config(priv);
	अगर (err) अणु
		IPW_DEBUG_HC("Attempt to send sys config command failed.\n");
		वापस err;
	पूर्ण

	IPW_DEBUG_ASSOC("Association sensitivity: %d\n", network->stats.rssi);
	err = ipw_set_sensitivity(priv, network->stats.rssi + IPW_RSSI_TO_DBM);
	अगर (err) अणु
		IPW_DEBUG_HC("Attempt to send associate command failed.\n");
		वापस err;
	पूर्ण

	/*
	 * If preemption is enabled, it is possible क्रम the association
	 * to complete beक्रमe we वापस from ipw_send_associate.  Thereक्रमe
	 * we have to be sure and update our priviate data first.
	 */
	priv->channel = network->channel;
	स_नकल(priv->bssid, network->bssid, ETH_ALEN);
	priv->status |= STATUS_ASSOCIATING;
	priv->status &= ~STATUS_SECURITY_UPDATED;

	priv->assoc_network = network;

#अगर_घोषित CONFIG_IPW2200_QOS
	ipw_qos_association(priv, network);
#पूर्ण_अगर

	err = ipw_send_associate(priv, &priv->assoc_request);
	अगर (err) अणु
		IPW_DEBUG_HC("Attempt to send associate command failed.\n");
		वापस err;
	पूर्ण

	IPW_DEBUG(IPW_DL_STATE, "associating: '%*pE' %pM\n",
		  priv->essid_len, priv->essid, priv->bssid);

	वापस 0;
पूर्ण

अटल व्योम ipw_roam(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;
	काष्ठा libipw_network *network = शून्य;
	काष्ठा ipw_network_match match = अणु
		.network = priv->assoc_network
	पूर्ण;

	/* The roaming process is as follows:
	 *
	 * 1.  Missed beacon threshold triggers the roaming process by
	 *     setting the status ROAM bit and requesting a scan.
	 * 2.  When the scan completes, it schedules the ROAM work
	 * 3.  The ROAM work looks at all of the known networks क्रम one that
	 *     is a better network than the currently associated.  If none
	 *     found, the ROAM process is over (ROAM bit cleared)
	 * 4.  If a better network is found, a disassociation request is
	 *     sent.
	 * 5.  When the disassociation completes, the roam work is again
	 *     scheduled.  The second समय through, the driver is no दीर्घer
	 *     associated, and the newly selected network is sent an
	 *     association request.
	 * 6.  At this poपूर्णांक ,the roaming process is complete and the ROAM
	 *     status bit is cleared.
	 */

	/* If we are no दीर्घer associated, and the roaming bit is no दीर्घer
	 * set, then we are not actively roaming, so just वापस */
	अगर (!(priv->status & (STATUS_ASSOCIATED | STATUS_ROAMING)))
		वापस;

	अगर (priv->status & STATUS_ASSOCIATED) अणु
		/* First pass through ROAM process -- look क्रम a better
		 * network */
		अचिन्हित दीर्घ flags;
		u8 rssi = priv->assoc_network->stats.rssi;
		priv->assoc_network->stats.rssi = -128;
		spin_lock_irqsave(&priv->ieee->lock, flags);
		list_क्रम_each_entry(network, &priv->ieee->network_list, list) अणु
			अगर (network != priv->assoc_network)
				ipw_best_network(priv, &match, network, 1);
		पूर्ण
		spin_unlock_irqrestore(&priv->ieee->lock, flags);
		priv->assoc_network->stats.rssi = rssi;

		अगर (match.network == priv->assoc_network) अणु
			IPW_DEBUG_ASSOC("No better APs in this network to "
					"roam to.\n");
			priv->status &= ~STATUS_ROAMING;
			ipw_debug_config(priv);
			वापस;
		पूर्ण

		ipw_send_disassociate(priv, 1);
		priv->assoc_network = match.network;

		वापस;
	पूर्ण

	/* Second pass through ROAM process -- request association */
	ipw_compatible_rates(priv, priv->assoc_network, &match.rates);
	ipw_associate_network(priv, priv->assoc_network, &match.rates, 1);
	priv->status &= ~STATUS_ROAMING;
पूर्ण

अटल व्योम ipw_bg_roam(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, roam);
	mutex_lock(&priv->mutex);
	ipw_roam(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ipw_associate(व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;

	काष्ठा libipw_network *network = शून्य;
	काष्ठा ipw_network_match match = अणु
		.network = शून्य
	पूर्ण;
	काष्ठा ipw_supported_rates *rates;
	काष्ठा list_head *element;
	अचिन्हित दीर्घ flags;

	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
		IPW_DEBUG_ASSOC("Not attempting association (monitor mode)\n");
		वापस 0;
	पूर्ण

	अगर (priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) अणु
		IPW_DEBUG_ASSOC("Not attempting association (already in "
				"progress)\n");
		वापस 0;
	पूर्ण

	अगर (priv->status & STATUS_DISASSOCIATING) अणु
		IPW_DEBUG_ASSOC("Not attempting association (in disassociating)\n");
		schedule_work(&priv->associate);
		वापस 0;
	पूर्ण

	अगर (!ipw_is_init(priv) || (priv->status & STATUS_SCANNING)) अणु
		IPW_DEBUG_ASSOC("Not attempting association (scanning or not "
				"initialized)\n");
		वापस 0;
	पूर्ण

	अगर (!(priv->config & CFG_ASSOCIATE) &&
	    !(priv->config & (CFG_STATIC_ESSID | CFG_STATIC_BSSID))) अणु
		IPW_DEBUG_ASSOC("Not attempting association (associate=0)\n");
		वापस 0;
	पूर्ण

	/* Protect our use of the network_list */
	spin_lock_irqsave(&priv->ieee->lock, flags);
	list_क्रम_each_entry(network, &priv->ieee->network_list, list)
	    ipw_best_network(priv, &match, network, 0);

	network = match.network;
	rates = &match.rates;

	अगर (network == शून्य &&
	    priv->ieee->iw_mode == IW_MODE_ADHOC &&
	    priv->config & CFG_ADHOC_CREATE &&
	    priv->config & CFG_STATIC_ESSID &&
	    priv->config & CFG_STATIC_CHANNEL) अणु
		/* Use oldest network अगर the मुक्त list is empty */
		अगर (list_empty(&priv->ieee->network_मुक्त_list)) अणु
			काष्ठा libipw_network *oldest = शून्य;
			काष्ठा libipw_network *target;

			list_क्रम_each_entry(target, &priv->ieee->network_list, list) अणु
				अगर ((oldest == शून्य) ||
				    (target->last_scanned < oldest->last_scanned))
					oldest = target;
			पूर्ण

			/* If there are no more slots, expire the oldest */
			list_del(&oldest->list);
			target = oldest;
			IPW_DEBUG_ASSOC("Expired '%*pE' (%pM) from network list.\n",
					target->ssid_len, target->ssid,
					target->bssid);
			list_add_tail(&target->list,
				      &priv->ieee->network_मुक्त_list);
		पूर्ण

		element = priv->ieee->network_मुक्त_list.next;
		network = list_entry(element, काष्ठा libipw_network, list);
		ipw_adhoc_create(priv, network);
		rates = &priv->rates;
		list_del(element);
		list_add_tail(&network->list, &priv->ieee->network_list);
	पूर्ण
	spin_unlock_irqrestore(&priv->ieee->lock, flags);

	/* If we reached the end of the list, then we करोn't have any valid
	 * matching APs */
	अगर (!network) अणु
		ipw_debug_config(priv);

		अगर (!(priv->status & STATUS_SCANNING)) अणु
			अगर (!(priv->config & CFG_SPEED_SCAN))
				schedule_delayed_work(&priv->request_scan,
						      SCAN_INTERVAL);
			अन्यथा
				schedule_delayed_work(&priv->request_scan, 0);
		पूर्ण

		वापस 0;
	पूर्ण

	ipw_associate_network(priv, network, rates, 0);

	वापस 1;
पूर्ण

अटल व्योम ipw_bg_associate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, associate);
	mutex_lock(&priv->mutex);
	ipw_associate(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_rebuild_decrypted_skb(काष्ठा ipw_priv *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = le16_to_cpu(hdr->frame_control);
	अगर (!(fc & IEEE80211_FCTL_PROTECTED))
		वापस;

	fc &= ~IEEE80211_FCTL_PROTECTED;
	hdr->frame_control = cpu_to_le16(fc);
	चयन (priv->ieee->sec.level) अणु
	हाल SEC_LEVEL_3:
		/* Remove CCMP HDR */
		स_हटाओ(skb->data + LIBIPW_3ADDR_LEN,
			skb->data + LIBIPW_3ADDR_LEN + 8,
			skb->len - LIBIPW_3ADDR_LEN - 8);
		skb_trim(skb, skb->len - 16);	/* CCMP_HDR_LEN + CCMP_MIC_LEN */
		अवरोध;
	हाल SEC_LEVEL_2:
		अवरोध;
	हाल SEC_LEVEL_1:
		/* Remove IV */
		स_हटाओ(skb->data + LIBIPW_3ADDR_LEN,
			skb->data + LIBIPW_3ADDR_LEN + 4,
			skb->len - LIBIPW_3ADDR_LEN - 4);
		skb_trim(skb, skb->len - 8);	/* IV + ICV */
		अवरोध;
	हाल SEC_LEVEL_0:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unknown security level %d\n",
		       priv->ieee->sec.level);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ipw_handle_data_packet(काष्ठा ipw_priv *priv,
				   काष्ठा ipw_rx_mem_buffer *rxb,
				   काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	काष्ठा libipw_hdr_4addr *hdr;
	काष्ठा ipw_rx_packet *pkt = (काष्ठा ipw_rx_packet *)rxb->skb->data;

	/* We received data from the HW, so stop the watchकरोg */
	netअगर_trans_update(dev);

	/* We only process data packets अगर the
	 * पूर्णांकerface is खोलो */
	अगर (unlikely((le16_to_cpu(pkt->u.frame.length) + IPW_RX_FRAME_SIZE) >
		     skb_tailroom(rxb->skb))) अणु
		dev->stats.rx_errors++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Corruption detected! Oh no!\n");
		वापस;
	पूर्ण अन्यथा अगर (unlikely(!netअगर_running(priv->net_dev))) अणु
		dev->stats.rx_dropped++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		वापस;
	पूर्ण

	/* Advance skb->data to the start of the actual payload */
	skb_reserve(rxb->skb, दुरत्व(काष्ठा ipw_rx_packet, u.frame.data));

	/* Set the size of the skb to the size of the frame */
	skb_put(rxb->skb, le16_to_cpu(pkt->u.frame.length));

	IPW_DEBUG_RX("Rx packet of %d bytes.\n", rxb->skb->len);

	/* HW decrypt will not clear the WEP bit, MIC, PN, etc. */
	hdr = (काष्ठा libipw_hdr_4addr *)rxb->skb->data;
	अगर (priv->ieee->iw_mode != IW_MODE_MONITOR &&
	    (is_multicast_ether_addr(hdr->addr1) ?
	     !priv->ieee->host_mc_decrypt : !priv->ieee->host_decrypt))
		ipw_rebuild_decrypted_skb(priv, rxb->skb);

	अगर (!libipw_rx(priv->ieee, rxb->skb, stats))
		dev->stats.rx_errors++;
	अन्यथा अणु			/* libipw_rx succeeded, so it now owns the SKB */
		rxb->skb = शून्य;
		__ipw_led_activity_on(priv);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IPW2200_RADIOTAP
अटल व्योम ipw_handle_data_packet_monitor(काष्ठा ipw_priv *priv,
					   काष्ठा ipw_rx_mem_buffer *rxb,
					   काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	काष्ठा ipw_rx_packet *pkt = (काष्ठा ipw_rx_packet *)rxb->skb->data;
	काष्ठा ipw_rx_frame *frame = &pkt->u.frame;

	/* initial pull of some data */
	u16 received_channel = frame->received_channel;
	u8 antennaAndPhy = frame->antennaAndPhy;
	s8 antसंकेत = frame->rssi_dbm - IPW_RSSI_TO_DBM;	/* call it चिन्हित anyhow */
	u16 pktrate = frame->rate;

	/* Magic काष्ठा that slots पूर्णांकo the radiotap header -- no reason
	 * to build this manually element by element, we can ग_लिखो it much
	 * more efficiently than we can parse it. ORDER MATTERS HERE */
	काष्ठा ipw_rt_hdr *ipw_rt;

	अचिन्हित लघु len = le16_to_cpu(pkt->u.frame.length);

	/* We received data from the HW, so stop the watchकरोg */
	netअगर_trans_update(dev);

	/* We only process data packets अगर the
	 * पूर्णांकerface is खोलो */
	अगर (unlikely((le16_to_cpu(pkt->u.frame.length) + IPW_RX_FRAME_SIZE) >
		     skb_tailroom(rxb->skb))) अणु
		dev->stats.rx_errors++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Corruption detected! Oh no!\n");
		वापस;
	पूर्ण अन्यथा अगर (unlikely(!netअगर_running(priv->net_dev))) अणु
		dev->stats.rx_dropped++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		वापस;
	पूर्ण

	/* Libpcap 0.9.3+ can handle variable length radiotap, so we'll use
	 * that now */
	अगर (len > IPW_RX_BUF_SIZE - माप(काष्ठा ipw_rt_hdr)) अणु
		/* FIXME: Should alloc bigger skb instead */
		dev->stats.rx_dropped++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping too large packet in monitor\n");
		वापस;
	पूर्ण

	/* copy the frame itself */
	स_हटाओ(rxb->skb->data + माप(काष्ठा ipw_rt_hdr),
		rxb->skb->data + IPW_RX_FRAME_SIZE, len);

	ipw_rt = (काष्ठा ipw_rt_hdr *)rxb->skb->data;

	ipw_rt->rt_hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	ipw_rt->rt_hdr.it_pad = 0;	/* always good to zero */
	ipw_rt->rt_hdr.it_len = cpu_to_le16(माप(काष्ठा ipw_rt_hdr));	/* total header+data */

	/* Big bitfield of all the fields we provide in radiotap */
	ipw_rt->rt_hdr.it_present = cpu_to_le32(
	     (1 << IEEE80211_RADIOTAP_TSFT) |
	     (1 << IEEE80211_RADIOTAP_FLAGS) |
	     (1 << IEEE80211_RADIOTAP_RATE) |
	     (1 << IEEE80211_RADIOTAP_CHANNEL) |
	     (1 << IEEE80211_RADIOTAP_DBM_ANTSIGNAL) |
	     (1 << IEEE80211_RADIOTAP_DBM_ANTNOISE) |
	     (1 << IEEE80211_RADIOTAP_ANTENNA));

	/* Zero the flags, we'll add to them as we go */
	ipw_rt->rt_flags = 0;
	ipw_rt->rt_tsf = (u64)(frame->parent_tsf[3] << 24 |
			       frame->parent_tsf[2] << 16 |
			       frame->parent_tsf[1] << 8  |
			       frame->parent_tsf[0]);

	/* Convert संकेत to DBM */
	ipw_rt->rt_dbmसंकेत = antसंकेत;
	ipw_rt->rt_dbmnoise = (s8) le16_to_cpu(frame->noise);

	/* Convert the channel data and set the flags */
	ipw_rt->rt_channel = cpu_to_le16(ieee80211chan2mhz(received_channel));
	अगर (received_channel > 14) अणु	/* 802.11a */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16((IEEE80211_CHAN_OFDM | IEEE80211_CHAN_5GHZ));
	पूर्ण अन्यथा अगर (antennaAndPhy & 32) अणु	/* 802.11b */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16((IEEE80211_CHAN_CCK | IEEE80211_CHAN_2GHZ));
	पूर्ण अन्यथा अणु		/* 802.11g */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16(IEEE80211_CHAN_OFDM | IEEE80211_CHAN_2GHZ);
	पूर्ण

	/* set the rate in multiples of 500k/s */
	चयन (pktrate) अणु
	हाल IPW_TX_RATE_1MB:
		ipw_rt->rt_rate = 2;
		अवरोध;
	हाल IPW_TX_RATE_2MB:
		ipw_rt->rt_rate = 4;
		अवरोध;
	हाल IPW_TX_RATE_5MB:
		ipw_rt->rt_rate = 10;
		अवरोध;
	हाल IPW_TX_RATE_6MB:
		ipw_rt->rt_rate = 12;
		अवरोध;
	हाल IPW_TX_RATE_9MB:
		ipw_rt->rt_rate = 18;
		अवरोध;
	हाल IPW_TX_RATE_11MB:
		ipw_rt->rt_rate = 22;
		अवरोध;
	हाल IPW_TX_RATE_12MB:
		ipw_rt->rt_rate = 24;
		अवरोध;
	हाल IPW_TX_RATE_18MB:
		ipw_rt->rt_rate = 36;
		अवरोध;
	हाल IPW_TX_RATE_24MB:
		ipw_rt->rt_rate = 48;
		अवरोध;
	हाल IPW_TX_RATE_36MB:
		ipw_rt->rt_rate = 72;
		अवरोध;
	हाल IPW_TX_RATE_48MB:
		ipw_rt->rt_rate = 96;
		अवरोध;
	हाल IPW_TX_RATE_54MB:
		ipw_rt->rt_rate = 108;
		अवरोध;
	शेष:
		ipw_rt->rt_rate = 0;
		अवरोध;
	पूर्ण

	/* antenna number */
	ipw_rt->rt_antenna = (antennaAndPhy & 3);	/* Is this right? */

	/* set the preamble flag अगर we have it */
	अगर ((antennaAndPhy & 64))
		ipw_rt->rt_flags |= IEEE80211_RADIOTAP_F_SHORTPRE;

	/* Set the size of the skb to the size of the frame */
	skb_put(rxb->skb, len + माप(काष्ठा ipw_rt_hdr));

	IPW_DEBUG_RX("Rx packet of %d bytes.\n", rxb->skb->len);

	अगर (!libipw_rx(priv->ieee, rxb->skb, stats))
		dev->stats.rx_errors++;
	अन्यथा अणु			/* libipw_rx succeeded, so it now owns the SKB */
		rxb->skb = शून्य;
		/* no LED during capture */
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
#घोषणा libipw_is_probe_response(fc) \
   ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_MGMT && \
    (fc & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_PROBE_RESP )

#घोषणा libipw_is_management(fc) \
   ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_MGMT)

#घोषणा libipw_is_control(fc) \
   ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_CTL)

#घोषणा libipw_is_data(fc) \
   ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_DATA)

#घोषणा libipw_is_assoc_request(fc) \
   ((fc & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_ASSOC_REQ)

#घोषणा libipw_is_reassoc_request(fc) \
   ((fc & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_REASSOC_REQ)

अटल व्योम ipw_handle_promiscuous_rx(काष्ठा ipw_priv *priv,
				      काष्ठा ipw_rx_mem_buffer *rxb,
				      काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा net_device *dev = priv->prom_net_dev;
	काष्ठा ipw_rx_packet *pkt = (काष्ठा ipw_rx_packet *)rxb->skb->data;
	काष्ठा ipw_rx_frame *frame = &pkt->u.frame;
	काष्ठा ipw_rt_hdr *ipw_rt;

	/* First cache any inक्रमmation we need beक्रमe we overग_लिखो
	 * the inक्रमmation provided in the skb from the hardware */
	काष्ठा ieee80211_hdr *hdr;
	u16 channel = frame->received_channel;
	u8 phy_flags = frame->antennaAndPhy;
	s8 संकेत = frame->rssi_dbm - IPW_RSSI_TO_DBM;
	s8 noise = (s8) le16_to_cpu(frame->noise);
	u8 rate = frame->rate;
	अचिन्हित लघु len = le16_to_cpu(pkt->u.frame.length);
	काष्ठा sk_buff *skb;
	पूर्णांक hdr_only = 0;
	u16 filter = priv->prom_priv->filter;

	/* If the filter is set to not include Rx frames then वापस */
	अगर (filter & IPW_PROM_NO_RX)
		वापस;

	/* We received data from the HW, so stop the watchकरोg */
	netअगर_trans_update(dev);

	अगर (unlikely((len + IPW_RX_FRAME_SIZE) > skb_tailroom(rxb->skb))) अणु
		dev->stats.rx_errors++;
		IPW_DEBUG_DROP("Corruption detected! Oh no!\n");
		वापस;
	पूर्ण

	/* We only process data packets अगर the पूर्णांकerface is खोलो */
	अगर (unlikely(!netअगर_running(dev))) अणु
		dev->stats.rx_dropped++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		वापस;
	पूर्ण

	/* Libpcap 0.9.3+ can handle variable length radiotap, so we'll use
	 * that now */
	अगर (len > IPW_RX_BUF_SIZE - माप(काष्ठा ipw_rt_hdr)) अणु
		/* FIXME: Should alloc bigger skb instead */
		dev->stats.rx_dropped++;
		IPW_DEBUG_DROP("Dropping too large packet in monitor\n");
		वापस;
	पूर्ण

	hdr = (व्योम *)rxb->skb->data + IPW_RX_FRAME_SIZE;
	अगर (libipw_is_management(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_MGMT)
			वापस;
		अगर (filter & IPW_PROM_MGMT_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण अन्यथा अगर (libipw_is_control(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_CTL)
			वापस;
		अगर (filter & IPW_PROM_CTL_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण अन्यथा अगर (libipw_is_data(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_DATA)
			वापस;
		अगर (filter & IPW_PROM_DATA_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण

	/* Copy the SKB since this is क्रम the promiscuous side */
	skb = skb_copy(rxb->skb, GFP_ATOMIC);
	अगर (skb == शून्य) अणु
		IPW_ERROR("skb_clone failed for promiscuous copy.\n");
		वापस;
	पूर्ण

	/* copy the frame data to ग_लिखो after where the radiotap header goes */
	ipw_rt = (व्योम *)skb->data;

	अगर (hdr_only)
		len = libipw_get_hdrlen(le16_to_cpu(hdr->frame_control));

	स_नकल(ipw_rt->payload, hdr, len);

	ipw_rt->rt_hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	ipw_rt->rt_hdr.it_pad = 0;	/* always good to zero */
	ipw_rt->rt_hdr.it_len = cpu_to_le16(माप(*ipw_rt));	/* total header+data */

	/* Set the size of the skb to the size of the frame */
	skb_put(skb, माप(*ipw_rt) + len);

	/* Big bitfield of all the fields we provide in radiotap */
	ipw_rt->rt_hdr.it_present = cpu_to_le32(
	     (1 << IEEE80211_RADIOTAP_TSFT) |
	     (1 << IEEE80211_RADIOTAP_FLAGS) |
	     (1 << IEEE80211_RADIOTAP_RATE) |
	     (1 << IEEE80211_RADIOTAP_CHANNEL) |
	     (1 << IEEE80211_RADIOTAP_DBM_ANTSIGNAL) |
	     (1 << IEEE80211_RADIOTAP_DBM_ANTNOISE) |
	     (1 << IEEE80211_RADIOTAP_ANTENNA));

	/* Zero the flags, we'll add to them as we go */
	ipw_rt->rt_flags = 0;
	ipw_rt->rt_tsf = (u64)(frame->parent_tsf[3] << 24 |
			       frame->parent_tsf[2] << 16 |
			       frame->parent_tsf[1] << 8  |
			       frame->parent_tsf[0]);

	/* Convert to DBM */
	ipw_rt->rt_dbmसंकेत = संकेत;
	ipw_rt->rt_dbmnoise = noise;

	/* Convert the channel data and set the flags */
	ipw_rt->rt_channel = cpu_to_le16(ieee80211chan2mhz(channel));
	अगर (channel > 14) अणु	/* 802.11a */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16((IEEE80211_CHAN_OFDM | IEEE80211_CHAN_5GHZ));
	पूर्ण अन्यथा अगर (phy_flags & (1 << 5)) अणु	/* 802.11b */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16((IEEE80211_CHAN_CCK | IEEE80211_CHAN_2GHZ));
	पूर्ण अन्यथा अणु		/* 802.11g */
		ipw_rt->rt_chbiपंचांगask =
		    cpu_to_le16(IEEE80211_CHAN_OFDM | IEEE80211_CHAN_2GHZ);
	पूर्ण

	/* set the rate in multiples of 500k/s */
	चयन (rate) अणु
	हाल IPW_TX_RATE_1MB:
		ipw_rt->rt_rate = 2;
		अवरोध;
	हाल IPW_TX_RATE_2MB:
		ipw_rt->rt_rate = 4;
		अवरोध;
	हाल IPW_TX_RATE_5MB:
		ipw_rt->rt_rate = 10;
		अवरोध;
	हाल IPW_TX_RATE_6MB:
		ipw_rt->rt_rate = 12;
		अवरोध;
	हाल IPW_TX_RATE_9MB:
		ipw_rt->rt_rate = 18;
		अवरोध;
	हाल IPW_TX_RATE_11MB:
		ipw_rt->rt_rate = 22;
		अवरोध;
	हाल IPW_TX_RATE_12MB:
		ipw_rt->rt_rate = 24;
		अवरोध;
	हाल IPW_TX_RATE_18MB:
		ipw_rt->rt_rate = 36;
		अवरोध;
	हाल IPW_TX_RATE_24MB:
		ipw_rt->rt_rate = 48;
		अवरोध;
	हाल IPW_TX_RATE_36MB:
		ipw_rt->rt_rate = 72;
		अवरोध;
	हाल IPW_TX_RATE_48MB:
		ipw_rt->rt_rate = 96;
		अवरोध;
	हाल IPW_TX_RATE_54MB:
		ipw_rt->rt_rate = 108;
		अवरोध;
	शेष:
		ipw_rt->rt_rate = 0;
		अवरोध;
	पूर्ण

	/* antenna number */
	ipw_rt->rt_antenna = (phy_flags & 3);

	/* set the preamble flag अगर we have it */
	अगर (phy_flags & (1 << 6))
		ipw_rt->rt_flags |= IEEE80211_RADIOTAP_F_SHORTPRE;

	IPW_DEBUG_RX("Rx packet of %d bytes.\n", skb->len);

	अगर (!libipw_rx(priv->prom_priv->ieee, skb, stats)) अणु
		dev->stats.rx_errors++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक is_network_packet(काष्ठा ipw_priv *priv,
				    काष्ठा libipw_hdr_4addr *header)
अणु
	/* Filter incoming packets to determine अगर they are targeted toward
	 * this network, discarding packets coming from ourselves */
	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:	/* Header: Dest. | Source    | BSSID */
		/* packets from our adapter are dropped (echo) */
		अगर (ether_addr_equal(header->addr2, priv->net_dev->dev_addr))
			वापस 0;

		/* अणुbroad,multiपूर्णcast packets to our BSSID go through */
		अगर (is_multicast_ether_addr(header->addr1))
			वापस ether_addr_equal(header->addr3, priv->bssid);

		/* packets to our adapter go through */
		वापस ether_addr_equal(header->addr1,
					priv->net_dev->dev_addr);

	हाल IW_MODE_INFRA:	/* Header: Dest. | BSSID | Source */
		/* packets from our adapter are dropped (echo) */
		अगर (ether_addr_equal(header->addr3, priv->net_dev->dev_addr))
			वापस 0;

		/* अणुbroad,multiपूर्णcast packets to our BSS go through */
		अगर (is_multicast_ether_addr(header->addr1))
			वापस ether_addr_equal(header->addr2, priv->bssid);

		/* packets to our adapter go through */
		वापस ether_addr_equal(header->addr1,
					priv->net_dev->dev_addr);
	पूर्ण

	वापस 1;
पूर्ण

#घोषणा IPW_PACKET_RETRY_TIME HZ

अटल  पूर्णांक is_duplicate_packet(काष्ठा ipw_priv *priv,
				      काष्ठा libipw_hdr_4addr *header)
अणु
	u16 sc = le16_to_cpu(header->seq_ctl);
	u16 seq = WLAN_GET_SEQ_SEQ(sc);
	u16 frag = WLAN_GET_SEQ_FRAG(sc);
	u16 *last_seq, *last_frag;
	अचिन्हित दीर्घ *last_समय;

	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		अणु
			काष्ठा list_head *p;
			काष्ठा ipw_ibss_seq *entry = शून्य;
			u8 *mac = header->addr2;
			पूर्णांक index = mac[5] % IPW_IBSS_MAC_HASH_SIZE;

			list_क्रम_each(p, &priv->ibss_mac_hash[index]) अणु
				entry =
				    list_entry(p, काष्ठा ipw_ibss_seq, list);
				अगर (ether_addr_equal(entry->mac, mac))
					अवरोध;
			पूर्ण
			अगर (p == &priv->ibss_mac_hash[index]) अणु
				entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
				अगर (!entry) अणु
					IPW_ERROR
					    ("Cannot malloc new mac entry\n");
					वापस 0;
				पूर्ण
				स_नकल(entry->mac, mac, ETH_ALEN);
				entry->seq_num = seq;
				entry->frag_num = frag;
				entry->packet_समय = jअगरfies;
				list_add(&entry->list,
					 &priv->ibss_mac_hash[index]);
				वापस 0;
			पूर्ण
			last_seq = &entry->seq_num;
			last_frag = &entry->frag_num;
			last_समय = &entry->packet_समय;
			अवरोध;
		पूर्ण
	हाल IW_MODE_INFRA:
		last_seq = &priv->last_seq_num;
		last_frag = &priv->last_frag_num;
		last_समय = &priv->last_packet_समय;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर ((*last_seq == seq) &&
	    समय_after(*last_समय + IPW_PACKET_RETRY_TIME, jअगरfies)) अणु
		अगर (*last_frag == frag)
			जाओ drop;
		अगर (*last_frag + 1 != frag)
			/* out-of-order fragment */
			जाओ drop;
	पूर्ण अन्यथा
		*last_seq = seq;

	*last_frag = frag;
	*last_समय = jअगरfies;
	वापस 0;

      drop:
	/* Comment this line now since we observed the card receives
	 * duplicate packets but the FCTL_RETRY bit is not set in the
	 * IBSS mode with fragmentation enabled.
	 BUG_ON(!(le16_to_cpu(header->frame_control) & IEEE80211_FCTL_RETRY)); */
	वापस 1;
पूर्ण

अटल व्योम ipw_handle_mgmt_packet(काष्ठा ipw_priv *priv,
				   काष्ठा ipw_rx_mem_buffer *rxb,
				   काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा sk_buff *skb = rxb->skb;
	काष्ठा ipw_rx_packet *pkt = (काष्ठा ipw_rx_packet *)skb->data;
	काष्ठा libipw_hdr_4addr *header = (काष्ठा libipw_hdr_4addr *)
	    (skb->data + IPW_RX_FRAME_SIZE);

	libipw_rx_mgt(priv->ieee, header, stats);

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC &&
	    ((WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) ==
	      IEEE80211_STYPE_PROBE_RESP) ||
	     (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) ==
	      IEEE80211_STYPE_BEACON))) अणु
		अगर (ether_addr_equal(header->addr3, priv->bssid))
			ipw_add_station(priv, header->addr2);
	पूर्ण

	अगर (priv->config & CFG_NET_STATS) अणु
		IPW_DEBUG_HC("sending stat packet\n");

		/* Set the size of the skb to the size of the full
		 * ipw header and 802.11 frame */
		skb_put(skb, le16_to_cpu(pkt->u.frame.length) +
			IPW_RX_FRAME_SIZE);

		/* Advance past the ipw packet header to the 802.11 frame */
		skb_pull(skb, IPW_RX_FRAME_SIZE);

		/* Push the libipw_rx_stats beक्रमe the 802.11 frame */
		स_नकल(skb_push(skb, माप(*stats)), stats, माप(*stats));

		skb->dev = priv->ieee->dev;

		/* Poपूर्णांक raw at the libipw_stats */
		skb_reset_mac_header(skb);

		skb->pkt_type = PACKET_OTHERHOST;
		skb->protocol = cpu_to_be16(ETH_P_80211_STATS);
		स_रखो(skb->cb, 0, माप(rxb->skb->cb));
		netअगर_rx(skb);
		rxb->skb = शून्य;
	पूर्ण
पूर्ण

/*
 * Main entry function क्रम receiving a packet with 80211 headers.  This
 * should be called when ever the FW has notअगरied us that there is a new
 * skb in the receive queue.
 */
अटल व्योम ipw_rx(काष्ठा ipw_priv *priv)
अणु
	काष्ठा ipw_rx_mem_buffer *rxb;
	काष्ठा ipw_rx_packet *pkt;
	काष्ठा libipw_hdr_4addr *header;
	u32 r, i;
	u8 network_packet;
	u8 fill_rx = 0;

	r = ipw_पढ़ो32(priv, IPW_RX_READ_INDEX);
	ipw_पढ़ो32(priv, IPW_RX_WRITE_INDEX);
	i = priv->rxq->पढ़ो;

	अगर (ipw_rx_queue_space (priv->rxq) > (RX_QUEUE_SIZE / 2))
		fill_rx = 1;

	जबतक (i != r) अणु
		rxb = priv->rxq->queue[i];
		अगर (unlikely(rxb == शून्य)) अणु
			prपूर्णांकk(KERN_CRIT "Queue not allocated!\n");
			अवरोध;
		पूर्ण
		priv->rxq->queue[i] = शून्य;

		dma_sync_single_क्रम_cpu(&priv->pci_dev->dev, rxb->dma_addr,
					IPW_RX_BUF_SIZE, DMA_FROM_DEVICE);

		pkt = (काष्ठा ipw_rx_packet *)rxb->skb->data;
		IPW_DEBUG_RX("Packet: type=%02X seq=%02X bits=%02X\n",
			     pkt->header.message_type,
			     pkt->header.rx_seq_num, pkt->header.control_bits);

		चयन (pkt->header.message_type) अणु
		हाल RX_FRAME_TYPE:	/* 802.11 frame */  अणु
				काष्ठा libipw_rx_stats stats = अणु
					.rssi = pkt->u.frame.rssi_dbm -
					    IPW_RSSI_TO_DBM,
					.संकेत =
					    pkt->u.frame.rssi_dbm -
					    IPW_RSSI_TO_DBM + 0x100,
					.noise =
					    le16_to_cpu(pkt->u.frame.noise),
					.rate = pkt->u.frame.rate,
					.mac_समय = jअगरfies,
					.received_channel =
					    pkt->u.frame.received_channel,
					.freq =
					    (pkt->u.frame.
					     control & (1 << 0)) ?
					    LIBIPW_24GHZ_BAND :
					    LIBIPW_52GHZ_BAND,
					.len = le16_to_cpu(pkt->u.frame.length),
				पूर्ण;

				अगर (stats.rssi != 0)
					stats.mask |= LIBIPW_STATMASK_RSSI;
				अगर (stats.संकेत != 0)
					stats.mask |= LIBIPW_STATMASK_SIGNAL;
				अगर (stats.noise != 0)
					stats.mask |= LIBIPW_STATMASK_NOISE;
				अगर (stats.rate != 0)
					stats.mask |= LIBIPW_STATMASK_RATE;

				priv->rx_packets++;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	अगर (priv->prom_net_dev && netअगर_running(priv->prom_net_dev))
		ipw_handle_promiscuous_rx(priv, rxb, &stats);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_MONITOR
				अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
#अगर_घोषित CONFIG_IPW2200_RADIOTAP

                ipw_handle_data_packet_monitor(priv,
					       rxb,
					       &stats);
#अन्यथा
		ipw_handle_data_packet(priv, rxb,
				       &stats);
#पूर्ण_अगर
					अवरोध;
				पूर्ण
#पूर्ण_अगर

				header =
				    (काष्ठा libipw_hdr_4addr *)(rxb->skb->
								   data +
								   IPW_RX_FRAME_SIZE);
				/* TODO: Check Ad-Hoc dest/source and make sure
				 * that we are actually parsing these packets
				 * correctly -- we should probably use the
				 * frame control of the packet and disregard
				 * the current iw_mode */

				network_packet =
				    is_network_packet(priv, header);
				अगर (network_packet && priv->assoc_network) अणु
					priv->assoc_network->stats.rssi =
					    stats.rssi;
					priv->exp_avg_rssi =
					    exponential_average(priv->exp_avg_rssi,
					    stats.rssi, DEPTH_RSSI);
				पूर्ण

				IPW_DEBUG_RX("Frame: len=%u\n",
					     le16_to_cpu(pkt->u.frame.length));

				अगर (le16_to_cpu(pkt->u.frame.length) <
				    libipw_get_hdrlen(le16_to_cpu(
						    header->frame_ctl))) अणु
					IPW_DEBUG_DROP
					    ("Received packet is too small. "
					     "Dropping.\n");
					priv->net_dev->stats.rx_errors++;
					priv->wstats.discard.misc++;
					अवरोध;
				पूर्ण

				चयन (WLAN_FC_GET_TYPE
					(le16_to_cpu(header->frame_ctl))) अणु

				हाल IEEE80211_FTYPE_MGMT:
					ipw_handle_mgmt_packet(priv, rxb,
							       &stats);
					अवरोध;

				हाल IEEE80211_FTYPE_CTL:
					अवरोध;

				हाल IEEE80211_FTYPE_DATA:
					अगर (unlikely(!network_packet ||
						     is_duplicate_packet(priv,
									 header)))
					अणु
						IPW_DEBUG_DROP("Dropping: "
							       "%pM, "
							       "%pM, "
							       "%pM\n",
							       header->addr1,
							       header->addr2,
							       header->addr3);
						अवरोध;
					पूर्ण

					ipw_handle_data_packet(priv, rxb,
							       &stats);

					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण

		हाल RX_HOST_NOTIFICATION_TYPE:अणु
				IPW_DEBUG_RX
				    ("Notification: subtype=%02X flags=%02X size=%d\n",
				     pkt->u.notअगरication.subtype,
				     pkt->u.notअगरication.flags,
				     le16_to_cpu(pkt->u.notअगरication.size));
				ipw_rx_notअगरication(priv, &pkt->u.notअगरication);
				अवरोध;
			पूर्ण

		शेष:
			IPW_DEBUG_RX("Bad Rx packet of type %d\n",
				     pkt->header.message_type);
			अवरोध;
		पूर्ण

		/* For now we just करोn't re-use anything.  We can tweak this
		 * later to try and re-use notअगरication packets and SKBs that
		 * fail to Rx correctly */
		अगर (rxb->skb != शून्य) अणु
			dev_kमुक्त_skb_any(rxb->skb);
			rxb->skb = शून्य;
		पूर्ण

		dma_unmap_single(&priv->pci_dev->dev, rxb->dma_addr,
				 IPW_RX_BUF_SIZE, DMA_FROM_DEVICE);
		list_add_tail(&rxb->list, &priv->rxq->rx_used);

		i = (i + 1) % RX_QUEUE_SIZE;

		/* If there are a lot of unsued frames, restock the Rx queue
		 * so the ucode won't निश्चित */
		अगर (fill_rx) अणु
			priv->rxq->पढ़ो = i;
			ipw_rx_queue_replenish(priv);
		पूर्ण
	पूर्ण

	/* Backtrack one entry */
	priv->rxq->पढ़ो = i;
	ipw_rx_queue_restock(priv);
पूर्ण

#घोषणा DEFAULT_RTS_THRESHOLD     2304U
#घोषणा MIN_RTS_THRESHOLD         1U
#घोषणा MAX_RTS_THRESHOLD         2304U
#घोषणा DEFAULT_BEACON_INTERVAL   100U
#घोषणा	DEFAULT_SHORT_RETRY_LIMIT 7U
#घोषणा	DEFAULT_LONG_RETRY_LIMIT  4U

/*
 * ipw_sw_reset
 * @option: options to control dअगरferent reset behaviour
 * 	    0 = reset everything except the 'disable' module_param
 * 	    1 = reset everything and prपूर्णांक out driver info (क्रम probe only)
 * 	    2 = reset everything
 */
अटल पूर्णांक ipw_sw_reset(काष्ठा ipw_priv *priv, पूर्णांक option)
अणु
	पूर्णांक band, modulation;
	पूर्णांक old_mode = priv->ieee->iw_mode;

	/* Initialize module parameter values here */
	priv->config = 0;

	/* We शेष to disabling the LED code as right now it causes
	 * too many प्रणालीs to lock up... */
	अगर (!led_support)
		priv->config |= CFG_NO_LED;

	अगर (associate)
		priv->config |= CFG_ASSOCIATE;
	अन्यथा
		IPW_DEBUG_INFO("Auto associate disabled.\n");

	अगर (स्वतः_create)
		priv->config |= CFG_ADHOC_CREATE;
	अन्यथा
		IPW_DEBUG_INFO("Auto adhoc creation disabled.\n");

	priv->config &= ~CFG_STATIC_ESSID;
	priv->essid_len = 0;
	स_रखो(priv->essid, 0, IW_ESSID_MAX_SIZE);

	अगर (disable && option) अणु
		priv->status |= STATUS_RF_KILL_SW;
		IPW_DEBUG_INFO("Radio disabled.\n");
	पूर्ण

	अगर (शेष_channel != 0) अणु
		priv->config |= CFG_STATIC_CHANNEL;
		priv->channel = शेष_channel;
		IPW_DEBUG_INFO("Bind to static channel %d\n", शेष_channel);
		/* TODO: Validate that provided channel is in range */
	पूर्ण
#अगर_घोषित CONFIG_IPW2200_QOS
	ipw_qos_init(priv, qos_enable, qos_burst_enable,
		     burst_duration_CCK, burst_duration_OFDM);
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	चयन (network_mode) अणु
	हाल 1:
		priv->ieee->iw_mode = IW_MODE_ADHOC;
		priv->net_dev->type = ARPHRD_ETHER;

		अवरोध;
#अगर_घोषित CONFIG_IPW2200_MONITOR
	हाल 2:
		priv->ieee->iw_mode = IW_MODE_MONITOR;
#अगर_घोषित CONFIG_IPW2200_RADIOTAP
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
#अन्यथा
		priv->net_dev->type = ARPHRD_IEEE80211;
#पूर्ण_अगर
		अवरोध;
#पूर्ण_अगर
	शेष:
	हाल 0:
		priv->net_dev->type = ARPHRD_ETHER;
		priv->ieee->iw_mode = IW_MODE_INFRA;
		अवरोध;
	पूर्ण

	अगर (hwcrypto) अणु
		priv->ieee->host_encrypt = 0;
		priv->ieee->host_encrypt_msdu = 0;
		priv->ieee->host_decrypt = 0;
		priv->ieee->host_mc_decrypt = 0;
	पूर्ण
	IPW_DEBUG_INFO("Hardware crypto [%s]\n", hwcrypto ? "on" : "off");

	/* IPW2200/2915 is abled to करो hardware fragmentation. */
	priv->ieee->host_खोलो_frag = 0;

	अगर ((priv->pci_dev->device == 0x4223) ||
	    (priv->pci_dev->device == 0x4224)) अणु
		अगर (option == 1)
			prपूर्णांकk(KERN_INFO DRV_NAME
			       ": Detected Intel PRO/Wireless 2915ABG Network "
			       "Connection\n");
		priv->ieee->abg_true = 1;
		band = LIBIPW_52GHZ_BAND | LIBIPW_24GHZ_BAND;
		modulation = LIBIPW_OFDM_MODULATION |
		    LIBIPW_CCK_MODULATION;
		priv->adapter = IPW_2915ABG;
		priv->ieee->mode = IEEE_A | IEEE_G | IEEE_B;
	पूर्ण अन्यथा अणु
		अगर (option == 1)
			prपूर्णांकk(KERN_INFO DRV_NAME
			       ": Detected Intel PRO/Wireless 2200BG Network "
			       "Connection\n");

		priv->ieee->abg_true = 0;
		band = LIBIPW_24GHZ_BAND;
		modulation = LIBIPW_OFDM_MODULATION |
		    LIBIPW_CCK_MODULATION;
		priv->adapter = IPW_2200BG;
		priv->ieee->mode = IEEE_G | IEEE_B;
	पूर्ण

	priv->ieee->freq_band = band;
	priv->ieee->modulation = modulation;

	priv->rates_mask = LIBIPW_DEFAULT_RATES_MASK;

	priv->disassociate_threshold = IPW_MB_DISASSOCIATE_THRESHOLD_DEFAULT;
	priv->roaming_threshold = IPW_MB_ROAMING_THRESHOLD_DEFAULT;

	priv->rts_threshold = DEFAULT_RTS_THRESHOLD;
	priv->लघु_retry_limit = DEFAULT_SHORT_RETRY_LIMIT;
	priv->दीर्घ_retry_limit = DEFAULT_LONG_RETRY_LIMIT;

	/* If घातer management is turned on, शेष to AC mode */
	priv->घातer_mode = IPW_POWER_AC;
	priv->tx_घातer = IPW_TX_POWER_DEFAULT;

	वापस old_mode == priv->ieee->iw_mode;
पूर्ण

/*
 * This file defines the Wireless Extension handlers.  It करोes not
 * define any methods of hardware manipulation and relies on the
 * functions defined in ipw_मुख्य to provide the HW पूर्णांकeraction.
 *
 * The exception to this is the use of the ipw_get_ordinal()
 * function used to poll the hardware vs. making unnecessary calls.
 *
 */

अटल पूर्णांक ipw_set_channel(काष्ठा ipw_priv *priv, u8 channel)
अणु
	अगर (channel == 0) अणु
		IPW_DEBUG_INFO("Setting channel to ANY (0)\n");
		priv->config &= ~CFG_STATIC_CHANNEL;
		IPW_DEBUG_ASSOC("Attempting to associate with new "
				"parameters.\n");
		ipw_associate(priv);
		वापस 0;
	पूर्ण

	priv->config |= CFG_STATIC_CHANNEL;

	अगर (priv->channel == channel) अणु
		IPW_DEBUG_INFO("Request to set channel to current value (%d)\n",
			       channel);
		वापस 0;
	पूर्ण

	IPW_DEBUG_INFO("Setting channel to %i\n", (पूर्णांक)channel);
	priv->channel = channel;

#अगर_घोषित CONFIG_IPW2200_MONITOR
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
		पूर्णांक i;
		अगर (priv->status & STATUS_SCANNING) अणु
			IPW_DEBUG_SCAN("Scan abort triggered due to "
				       "channel change.\n");
			ipw_पात_scan(priv);
		पूर्ण

		क्रम (i = 1000; i && (priv->status & STATUS_SCANNING); i--)
			udelay(10);

		अगर (priv->status & STATUS_SCANNING)
			IPW_DEBUG_SCAN("Still scanning...\n");
		अन्यथा
			IPW_DEBUG_SCAN("Took %dms to abort current scan\n",
				       1000 - i);

		वापस 0;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */

	/* Network configuration changed -- क्रमce [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to channel change.\n");
	अगर (!ipw_disassociate(priv))
		ipw_associate(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_freq(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	काष्ठा iw_freq *fwrq = &wrqu->freq;
	पूर्णांक ret = 0, i;
	u8 channel, flags;
	पूर्णांक band;

	अगर (fwrq->m == 0) अणु
		IPW_DEBUG_WX("SET Freq/Channel -> any\n");
		mutex_lock(&priv->mutex);
		ret = ipw_set_channel(priv, 0);
		mutex_unlock(&priv->mutex);
		वापस ret;
	पूर्ण
	/* अगर setting by freq convert to channel */
	अगर (fwrq->e == 1) अणु
		channel = libipw_freq_to_channel(priv->ieee, fwrq->m);
		अगर (channel == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा
		channel = fwrq->m;

	अगर (!(band = libipw_is_valid_channel(priv->ieee, channel)))
		वापस -EINVAL;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		i = libipw_channel_to_index(priv->ieee, channel);
		अगर (i == -1)
			वापस -EINVAL;

		flags = (band == LIBIPW_24GHZ_BAND) ?
		    geo->bg[i].flags : geo->a[i].flags;
		अगर (flags & LIBIPW_CH_PASSIVE_ONLY) अणु
			IPW_DEBUG_WX("Invalid Ad-Hoc channel for 802.11a\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	IPW_DEBUG_WX("SET Freq/Channel -> %d\n", fwrq->m);
	mutex_lock(&priv->mutex);
	ret = ipw_set_channel(priv, channel);
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ipw_wx_get_freq(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	wrqu->freq.e = 0;

	/* If we are associated, trying to associate, or have a अटलally
	 * configured CHANNEL then वापस that; otherwise वापस ANY */
	mutex_lock(&priv->mutex);
	अगर (priv->config & CFG_STATIC_CHANNEL ||
	    priv->status & (STATUS_ASSOCIATING | STATUS_ASSOCIATED)) अणु
		पूर्णांक i;

		i = libipw_channel_to_index(priv->ieee, priv->channel);
		BUG_ON(i == -1);
		wrqu->freq.e = 1;

		चयन (libipw_is_valid_channel(priv->ieee, priv->channel)) अणु
		हाल LIBIPW_52GHZ_BAND:
			wrqu->freq.m = priv->ieee->geo.a[i].freq * 100000;
			अवरोध;

		हाल LIBIPW_24GHZ_BAND:
			wrqu->freq.m = priv->ieee->geo.bg[i].freq * 100000;
			अवरोध;

		शेष:
			BUG();
		पूर्ण
	पूर्ण अन्यथा
		wrqu->freq.m = 0;

	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET Freq/Channel -> %d\n", priv->channel);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_mode(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	IPW_DEBUG_WX("Set MODE: %d\n", wrqu->mode);

	चयन (wrqu->mode) अणु
#अगर_घोषित CONFIG_IPW2200_MONITOR
	हाल IW_MODE_MONITOR:
#पूर्ण_अगर
	हाल IW_MODE_ADHOC:
	हाल IW_MODE_INFRA:
		अवरोध;
	हाल IW_MODE_AUTO:
		wrqu->mode = IW_MODE_INFRA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (wrqu->mode == priv->ieee->iw_mode)
		वापस 0;

	mutex_lock(&priv->mutex);

	ipw_sw_reset(priv, 0);

#अगर_घोषित CONFIG_IPW2200_MONITOR
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR)
		priv->net_dev->type = ARPHRD_ETHER;

	अगर (wrqu->mode == IW_MODE_MONITOR)
#अगर_घोषित CONFIG_IPW2200_RADIOTAP
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
#अन्यथा
		priv->net_dev->type = ARPHRD_IEEE80211;
#पूर्ण_अगर
#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */

	/* Free the existing firmware and reset the fw_loaded
	 * flag so ipw_load() will bring in the new firmware */
	मुक्त_firmware();

	priv->ieee->iw_mode = wrqu->mode;

	schedule_work(&priv->adapter_restart);
	mutex_unlock(&priv->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw_wx_get_mode(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->mode = priv->ieee->iw_mode;
	IPW_DEBUG_WX("Get MODE -> %d\n", wrqu->mode);
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

/* Values are in microsecond */
अटल स्थिर s32 समयout_duration[] = अणु
	350000,
	250000,
	75000,
	37000,
	25000,
पूर्ण;

अटल स्थिर s32 period_duration[] = अणु
	400000,
	700000,
	1000000,
	1000000,
	1000000
पूर्ण;

अटल पूर्णांक ipw_wx_get_range(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	पूर्णांक i = 0, j;

	wrqu->data.length = माप(*range);
	स_रखो(range, 0, माप(*range));

	/* 54Mbs == ~27 Mb/s real (802.11g) */
	range->throughput = 27 * 1000 * 1000;

	range->max_qual.qual = 100;
	/* TODO: Find real max RSSI and stick here */
	range->max_qual.level = 0;
	range->max_qual.noise = 0;
	range->max_qual.updated = 7;	/* Updated all three */

	range->avg_qual.qual = 70;
	/* TODO: Find real 'good' to 'bad' threshold value क्रम RSSI */
	range->avg_qual.level = 0;	/* FIXME to real average level */
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7;	/* Updated all three */
	mutex_lock(&priv->mutex);
	range->num_bitrates = min(priv->rates.num_rates, (u8) IW_MAX_BITRATES);

	क्रम (i = 0; i < range->num_bitrates; i++)
		range->bitrate[i] = (priv->rates.supported_rates[i] & 0x7F) *
		    500000;

	range->max_rts = DEFAULT_RTS_THRESHOLD;
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = WEP_KEYS;

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

	i = 0;
	अगर (priv->ieee->mode & (IEEE_B | IEEE_G)) अणु
		क्रम (j = 0; j < geo->bg_channels && i < IW_MAX_FREQUENCIES; j++) अणु
			अगर ((priv->ieee->iw_mode == IW_MODE_ADHOC) &&
			    (geo->bg[j].flags & LIBIPW_CH_PASSIVE_ONLY))
				जारी;

			range->freq[i].i = geo->bg[j].channel;
			range->freq[i].m = geo->bg[j].freq * 100000;
			range->freq[i].e = 1;
			i++;
		पूर्ण
	पूर्ण

	अगर (priv->ieee->mode & IEEE_A) अणु
		क्रम (j = 0; j < geo->a_channels && i < IW_MAX_FREQUENCIES; j++) अणु
			अगर ((priv->ieee->iw_mode == IW_MODE_ADHOC) &&
			    (geo->a[j].flags & LIBIPW_CH_PASSIVE_ONLY))
				जारी;

			range->freq[i].i = geo->a[j].channel;
			range->freq[i].m = geo->a[j].freq * 100000;
			range->freq[i].e = 1;
			i++;
		पूर्ण
	पूर्ण

	range->num_channels = i;
	range->num_frequency = i;

	mutex_unlock(&priv->mutex);

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWTHRSPY) |
				IW_EVENT_CAPA_MASK(SIOCGIWAP) |
				IW_EVENT_CAPA_MASK(SIOCGIWSCAN));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
		IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE;

	IPW_DEBUG_WX("GET Range\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_wap(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	अगर (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		वापस -EINVAL;
	mutex_lock(&priv->mutex);
	अगर (is_broadcast_ether_addr(wrqu->ap_addr.sa_data) ||
	    is_zero_ether_addr(wrqu->ap_addr.sa_data)) अणु
		/* we disable mandatory BSSID association */
		IPW_DEBUG_WX("Setting AP BSSID to ANY\n");
		priv->config &= ~CFG_STATIC_BSSID;
		IPW_DEBUG_ASSOC("Attempting to associate with new "
				"parameters.\n");
		ipw_associate(priv);
		mutex_unlock(&priv->mutex);
		वापस 0;
	पूर्ण

	priv->config |= CFG_STATIC_BSSID;
	अगर (ether_addr_equal(priv->bssid, wrqu->ap_addr.sa_data)) अणु
		IPW_DEBUG_WX("BSSID set to current BSSID.\n");
		mutex_unlock(&priv->mutex);
		वापस 0;
	पूर्ण

	IPW_DEBUG_WX("Setting mandatory BSSID to %pM\n",
		     wrqu->ap_addr.sa_data);

	स_नकल(priv->bssid, wrqu->ap_addr.sa_data, ETH_ALEN);

	/* Network configuration changed -- क्रमce [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to BSSID change.\n");
	अगर (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_wap(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a अटलally
	 * configured BSSID then वापस that; otherwise वापस ANY */
	mutex_lock(&priv->mutex);
	अगर (priv->config & CFG_STATIC_BSSID ||
	    priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) अणु
		wrqu->ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(wrqu->ap_addr.sa_data, priv->bssid, ETH_ALEN);
	पूर्ण अन्यथा
		eth_zero_addr(wrqu->ap_addr.sa_data);

	IPW_DEBUG_WX("Getting WAP BSSID: %pM\n",
		     wrqu->ap_addr.sa_data);
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_essid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
        पूर्णांक length;

        mutex_lock(&priv->mutex);

        अगर (!wrqu->essid.flags)
        अणु
                IPW_DEBUG_WX("Setting ESSID to ANY\n");
                ipw_disassociate(priv);
                priv->config &= ~CFG_STATIC_ESSID;
                ipw_associate(priv);
                mutex_unlock(&priv->mutex);
                वापस 0;
        पूर्ण

	length = min((पूर्णांक)wrqu->essid.length, IW_ESSID_MAX_SIZE);

	priv->config |= CFG_STATIC_ESSID;

	अगर (priv->essid_len == length && !स_भेद(priv->essid, extra, length)
	    && (priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING))) अणु
		IPW_DEBUG_WX("ESSID set to current ESSID.\n");
		mutex_unlock(&priv->mutex);
		वापस 0;
	पूर्ण

	IPW_DEBUG_WX("Setting ESSID: '%*pE' (%d)\n", length, extra, length);

	priv->essid_len = length;
	स_नकल(priv->essid, extra, priv->essid_len);

	/* Network configuration changed -- क्रमce [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to ESSID change.\n");
	अगर (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_essid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a अटलally
	 * configured ESSID then वापस that; otherwise वापस ANY */
	mutex_lock(&priv->mutex);
	अगर (priv->config & CFG_STATIC_ESSID ||
	    priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) अणु
		IPW_DEBUG_WX("Getting essid: '%*pE'\n",
			     priv->essid_len, priv->essid);
		स_नकल(extra, priv->essid, priv->essid_len);
		wrqu->essid.length = priv->essid_len;
		wrqu->essid.flags = 1;	/* active */
	पूर्ण अन्यथा अणु
		IPW_DEBUG_WX("Getting essid: ANY\n");
		wrqu->essid.length = 0;
		wrqu->essid.flags = 0;	/* active */
	पूर्ण
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_nick(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	IPW_DEBUG_WX("Setting nick to '%s'\n", extra);
	अगर (wrqu->data.length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;
	mutex_lock(&priv->mutex);
	wrqu->data.length = min_t(माप_प्रकार, wrqu->data.length, माप(priv->nick));
	स_रखो(priv->nick, 0, माप(priv->nick));
	स_नकल(priv->nick, extra, wrqu->data.length);
	IPW_DEBUG_TRACE("<<\n");
	mutex_unlock(&priv->mutex);
	वापस 0;

पूर्ण

अटल पूर्णांक ipw_wx_get_nick(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	IPW_DEBUG_WX("Getting nick\n");
	mutex_lock(&priv->mutex);
	wrqu->data.length = म_माप(priv->nick);
	स_नकल(extra, priv->nick, wrqu->data.length);
	wrqu->data.flags = 1;	/* active */
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_sens(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	IPW_DEBUG_WX("Setting roaming threshold to %d\n", wrqu->sens.value);
	IPW_DEBUG_WX("Setting disassociate threshold to %d\n", 3*wrqu->sens.value);
	mutex_lock(&priv->mutex);

	अगर (wrqu->sens.fixed == 0)
	अणु
		priv->roaming_threshold = IPW_MB_ROAMING_THRESHOLD_DEFAULT;
		priv->disassociate_threshold = IPW_MB_DISASSOCIATE_THRESHOLD_DEFAULT;
		जाओ out;
	पूर्ण
	अगर ((wrqu->sens.value > IPW_MB_ROAMING_THRESHOLD_MAX) ||
	    (wrqu->sens.value < IPW_MB_ROAMING_THRESHOLD_MIN)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	priv->roaming_threshold = wrqu->sens.value;
	priv->disassociate_threshold = 3*wrqu->sens.value;
      out:
	mutex_unlock(&priv->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw_wx_get_sens(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->sens.fixed = 1;
	wrqu->sens.value = priv->roaming_threshold;
	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("GET roaming threshold -> %s %d\n",
		     wrqu->घातer.disabled ? "OFF" : "ON", wrqu->घातer.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_rate(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/* TODO: We should use semaphores or locks क्रम access to priv */
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	u32 target_rate = wrqu->bitrate.value;
	u32 fixed, mask;

	/* value = -1, fixed = 0 means स्वतः only, so we should use all rates offered by AP */
	/* value = X, fixed = 1 means only rate X */
	/* value = X, fixed = 0 means all rates lower equal X */

	अगर (target_rate == -1) अणु
		fixed = 0;
		mask = LIBIPW_DEFAULT_RATES_MASK;
		/* Now we should reassociate */
		जाओ apply;
	पूर्ण

	mask = 0;
	fixed = wrqu->bitrate.fixed;

	अगर (target_rate == 1000000 || !fixed)
		mask |= LIBIPW_CCK_RATE_1MB_MASK;
	अगर (target_rate == 1000000)
		जाओ apply;

	अगर (target_rate == 2000000 || !fixed)
		mask |= LIBIPW_CCK_RATE_2MB_MASK;
	अगर (target_rate == 2000000)
		जाओ apply;

	अगर (target_rate == 5500000 || !fixed)
		mask |= LIBIPW_CCK_RATE_5MB_MASK;
	अगर (target_rate == 5500000)
		जाओ apply;

	अगर (target_rate == 6000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_6MB_MASK;
	अगर (target_rate == 6000000)
		जाओ apply;

	अगर (target_rate == 9000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_9MB_MASK;
	अगर (target_rate == 9000000)
		जाओ apply;

	अगर (target_rate == 11000000 || !fixed)
		mask |= LIBIPW_CCK_RATE_11MB_MASK;
	अगर (target_rate == 11000000)
		जाओ apply;

	अगर (target_rate == 12000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_12MB_MASK;
	अगर (target_rate == 12000000)
		जाओ apply;

	अगर (target_rate == 18000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_18MB_MASK;
	अगर (target_rate == 18000000)
		जाओ apply;

	अगर (target_rate == 24000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_24MB_MASK;
	अगर (target_rate == 24000000)
		जाओ apply;

	अगर (target_rate == 36000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_36MB_MASK;
	अगर (target_rate == 36000000)
		जाओ apply;

	अगर (target_rate == 48000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_48MB_MASK;
	अगर (target_rate == 48000000)
		जाओ apply;

	अगर (target_rate == 54000000 || !fixed)
		mask |= LIBIPW_OFDM_RATE_54MB_MASK;
	अगर (target_rate == 54000000)
		जाओ apply;

	IPW_DEBUG_WX("invalid rate specified, returning error\n");
	वापस -EINVAL;

      apply:
	IPW_DEBUG_WX("Setting rate mask to 0x%08X [%s]\n",
		     mask, fixed ? "fixed" : "sub-rates");
	mutex_lock(&priv->mutex);
	अगर (mask == LIBIPW_DEFAULT_RATES_MASK) अणु
		priv->config &= ~CFG_FIXED_RATE;
		ipw_set_fixed_rate(priv, priv->ieee->mode);
	पूर्ण अन्यथा
		priv->config |= CFG_FIXED_RATE;

	अगर (priv->rates_mask == mask) अणु
		IPW_DEBUG_WX("Mask set to current mask.\n");
		mutex_unlock(&priv->mutex);
		वापस 0;
	पूर्ण

	priv->rates_mask = mask;

	/* Network configuration changed -- क्रमce [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to rates change.\n");
	अगर (!ipw_disassociate(priv))
		ipw_associate(priv);

	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_rate(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->bitrate.value = priv->last_rate;
	wrqu->bitrate.fixed = (priv->config & CFG_FIXED_RATE) ? 1 : 0;
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET Rate -> %d\n", wrqu->bitrate.value);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_rts(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	अगर (wrqu->rts.disabled || !wrqu->rts.fixed)
		priv->rts_threshold = DEFAULT_RTS_THRESHOLD;
	अन्यथा अणु
		अगर (wrqu->rts.value < MIN_RTS_THRESHOLD ||
		    wrqu->rts.value > MAX_RTS_THRESHOLD) अणु
			mutex_unlock(&priv->mutex);
			वापस -EINVAL;
		पूर्ण
		priv->rts_threshold = wrqu->rts.value;
	पूर्ण

	ipw_send_rts_threshold(priv, priv->rts_threshold);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("SET RTS Threshold -> %d\n", priv->rts_threshold);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_rts(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->rts.value = priv->rts_threshold;
	wrqu->rts.fixed = 0;	/* no स्वतः select */
	wrqu->rts.disabled = (wrqu->rts.value == DEFAULT_RTS_THRESHOLD);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET RTS Threshold -> %d\n", wrqu->rts.value);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_txघात(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	mutex_lock(&priv->mutex);
	अगर (ipw_radio_समाप्त_sw(priv, wrqu->घातer.disabled)) अणु
		err = -EINPROGRESS;
		जाओ out;
	पूर्ण

	अगर (!wrqu->घातer.fixed)
		wrqu->घातer.value = IPW_TX_POWER_DEFAULT;

	अगर (wrqu->घातer.flags != IW_TXPOW_DBM) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((wrqu->घातer.value > IPW_TX_POWER_MAX) ||
	    (wrqu->घातer.value < IPW_TX_POWER_MIN)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	priv->tx_घातer = wrqu->घातer.value;
	err = ipw_set_tx_घातer(priv);
      out:
	mutex_unlock(&priv->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw_wx_get_txघात(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->घातer.value = priv->tx_घातer;
	wrqu->घातer.fixed = 1;
	wrqu->घातer.flags = IW_TXPOW_DBM;
	wrqu->घातer.disabled = (priv->status & STATUS_RF_KILL_MASK) ? 1 : 0;
	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("GET TX Power -> %s %d\n",
		     wrqu->घातer.disabled ? "OFF" : "ON", wrqu->घातer.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_frag(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	अगर (wrqu->frag.disabled || !wrqu->frag.fixed)
		priv->ieee->fts = DEFAULT_FTS;
	अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD) अणु
			mutex_unlock(&priv->mutex);
			वापस -EINVAL;
		पूर्ण

		priv->ieee->fts = wrqu->frag.value & ~0x1;
	पूर्ण

	ipw_send_frag_threshold(priv, wrqu->frag.value);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("SET Frag Threshold -> %d\n", wrqu->frag.value);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_frag(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	wrqu->frag.value = priv->ieee->fts;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	wrqu->frag.disabled = (wrqu->frag.value == DEFAULT_FTS);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET Frag Threshold -> %d\n", wrqu->frag.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_retry(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	अगर (wrqu->retry.flags & IW_RETRY_LIFETIME || wrqu->retry.disabled)
		वापस -EINVAL;

	अगर (!(wrqu->retry.flags & IW_RETRY_LIMIT))
		वापस 0;

	अगर (wrqu->retry.value < 0 || wrqu->retry.value >= 255)
		वापस -EINVAL;

	mutex_lock(&priv->mutex);
	अगर (wrqu->retry.flags & IW_RETRY_SHORT)
		priv->लघु_retry_limit = (u8) wrqu->retry.value;
	अन्यथा अगर (wrqu->retry.flags & IW_RETRY_LONG)
		priv->दीर्घ_retry_limit = (u8) wrqu->retry.value;
	अन्यथा अणु
		priv->लघु_retry_limit = (u8) wrqu->retry.value;
		priv->दीर्घ_retry_limit = (u8) wrqu->retry.value;
	पूर्ण

	ipw_send_retry_limit(priv, priv->लघु_retry_limit,
			     priv->दीर्घ_retry_limit);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("SET retry limit -> short:%d long:%d\n",
		     priv->लघु_retry_limit, priv->दीर्घ_retry_limit);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_retry(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);

	mutex_lock(&priv->mutex);
	wrqu->retry.disabled = 0;

	अगर ((wrqu->retry.flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) अणु
		mutex_unlock(&priv->mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (wrqu->retry.flags & IW_RETRY_LONG) अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		wrqu->retry.value = priv->दीर्घ_retry_limit;
	पूर्ण अन्यथा अगर (wrqu->retry.flags & IW_RETRY_SHORT) अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_SHORT;
		wrqu->retry.value = priv->लघु_retry_limit;
	पूर्ण अन्यथा अणु
		wrqu->retry.flags = IW_RETRY_LIMIT;
		wrqu->retry.value = priv->लघु_retry_limit;
	पूर्ण
	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("GET retry -> %d\n", wrqu->retry.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_scan(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *)extra;
	काष्ठा delayed_work *work = शून्य;

	mutex_lock(&priv->mutex);

	priv->user_requested_scan = 1;

	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req)) अणु
		अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
			पूर्णांक len = min((पूर्णांक)req->essid_len,
			              (पूर्णांक)माप(priv->direct_scan_ssid));
			स_नकल(priv->direct_scan_ssid, req->essid, len);
			priv->direct_scan_ssid_len = len;
			work = &priv->request_direct_scan;
		पूर्ण अन्यथा अगर (req->scan_type == IW_SCAN_TYPE_PASSIVE) अणु
			work = &priv->request_passive_scan;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Normal active broadcast scan */
		work = &priv->request_scan;
	पूर्ण

	mutex_unlock(&priv->mutex);

	IPW_DEBUG_WX("Start scan\n");

	schedule_delayed_work(work, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_scan(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_scan(priv->ieee, info, wrqu, extra);
पूर्ण

अटल पूर्णांक ipw_wx_set_encode(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक ret;
	u32 cap = priv->capability;

	mutex_lock(&priv->mutex);
	ret = libipw_wx_set_encode(priv->ieee, info, wrqu, key);

	/* In IBSS mode, we need to notअगरy the firmware to update
	 * the beacon info after we changed the capability. */
	अगर (cap != priv->capability &&
	    priv->ieee->iw_mode == IW_MODE_ADHOC &&
	    priv->status & STATUS_ASSOCIATED)
		ipw_disassociate(priv);

	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ipw_wx_get_encode(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_encode(priv->ieee, info, wrqu, key);
पूर्ण

अटल पूर्णांक ipw_wx_set_घातer(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक err;
	mutex_lock(&priv->mutex);
	अगर (wrqu->घातer.disabled) अणु
		priv->घातer_mode = IPW_POWER_LEVEL(priv->घातer_mode);
		err = ipw_send_घातer_mode(priv, IPW_POWER_MODE_CAM);
		अगर (err) अणु
			IPW_DEBUG_WX("failed setting power mode.\n");
			mutex_unlock(&priv->mutex);
			वापस err;
		पूर्ण
		IPW_DEBUG_WX("SET Power Management Mode -> off\n");
		mutex_unlock(&priv->mutex);
		वापस 0;
	पूर्ण

	चयन (wrqu->घातer.flags & IW_POWER_MODE) अणु
	हाल IW_POWER_ON:	/* If not specअगरied */
	हाल IW_POWER_MODE:	/* If set all mask */
	हाल IW_POWER_ALL_R:	/* If explicitly state all */
		अवरोध;
	शेष:		/* Otherwise we करोn't support it */
		IPW_DEBUG_WX("SET PM Mode: %X not supported.\n",
			     wrqu->घातer.flags);
		mutex_unlock(&priv->mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If the user hasn't specअगरied a घातer management mode yet, शेष
	 * to BATTERY */
	अगर (IPW_POWER_LEVEL(priv->घातer_mode) == IPW_POWER_AC)
		priv->घातer_mode = IPW_POWER_ENABLED | IPW_POWER_BATTERY;
	अन्यथा
		priv->घातer_mode = IPW_POWER_ENABLED | priv->घातer_mode;

	err = ipw_send_घातer_mode(priv, IPW_POWER_LEVEL(priv->घातer_mode));
	अगर (err) अणु
		IPW_DEBUG_WX("failed setting power mode.\n");
		mutex_unlock(&priv->mutex);
		वापस err;
	पूर्ण

	IPW_DEBUG_WX("SET Power Management Mode -> 0x%02X\n", priv->घातer_mode);
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_घातer(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	अगर (!(priv->घातer_mode & IPW_POWER_ENABLED))
		wrqu->घातer.disabled = 1;
	अन्यथा
		wrqu->घातer.disabled = 0;

	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("GET Power Management Mode -> %02X\n", priv->घातer_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_घातermode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक mode = *(पूर्णांक *)extra;
	पूर्णांक err;

	mutex_lock(&priv->mutex);
	अगर ((mode < 1) || (mode > IPW_POWER_LIMIT))
		mode = IPW_POWER_AC;

	अगर (IPW_POWER_LEVEL(priv->घातer_mode) != mode) अणु
		err = ipw_send_घातer_mode(priv, mode);
		अगर (err) अणु
			IPW_DEBUG_WX("failed setting power mode.\n");
			mutex_unlock(&priv->mutex);
			वापस err;
		पूर्ण
		priv->घातer_mode = IPW_POWER_ENABLED | mode;
	पूर्ण
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

#घोषणा MAX_WX_STRING 80
अटल पूर्णांक ipw_wx_get_घातermode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक level = IPW_POWER_LEVEL(priv->घातer_mode);
	अक्षर *p = extra;

	p += scnम_लिखो(p, MAX_WX_STRING, "Power save level: %d ", level);

	चयन (level) अणु
	हाल IPW_POWER_AC:
		p += scnम_लिखो(p, MAX_WX_STRING - (p - extra), "(AC)");
		अवरोध;
	हाल IPW_POWER_BATTERY:
		p += scnम_लिखो(p, MAX_WX_STRING - (p - extra), "(BATTERY)");
		अवरोध;
	शेष:
		p += scnम_लिखो(p, MAX_WX_STRING - (p - extra),
			      "(Timeout %dms, Period %dms)",
			      समयout_duration[level - 1] / 1000,
			      period_duration[level - 1] / 1000);
	पूर्ण

	अगर (!(priv->घातer_mode & IPW_POWER_ENABLED))
		p += scnम_लिखो(p, MAX_WX_STRING - (p - extra), " OFF");

	wrqu->data.length = p - extra + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_wireless_mode(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक mode = *(पूर्णांक *)extra;
	u8 band = 0, modulation = 0;

	अगर (mode == 0 || mode & ~IEEE_MODE_MASK) अणु
		IPW_WARNING("Attempt to set invalid wireless mode: %d\n", mode);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&priv->mutex);
	अगर (priv->adapter == IPW_2915ABG) अणु
		priv->ieee->abg_true = 1;
		अगर (mode & IEEE_A) अणु
			band |= LIBIPW_52GHZ_BAND;
			modulation |= LIBIPW_OFDM_MODULATION;
		पूर्ण अन्यथा
			priv->ieee->abg_true = 0;
	पूर्ण अन्यथा अणु
		अगर (mode & IEEE_A) अणु
			IPW_WARNING("Attempt to set 2200BG into "
				    "802.11a mode\n");
			mutex_unlock(&priv->mutex);
			वापस -EINVAL;
		पूर्ण

		priv->ieee->abg_true = 0;
	पूर्ण

	अगर (mode & IEEE_B) अणु
		band |= LIBIPW_24GHZ_BAND;
		modulation |= LIBIPW_CCK_MODULATION;
	पूर्ण अन्यथा
		priv->ieee->abg_true = 0;

	अगर (mode & IEEE_G) अणु
		band |= LIBIPW_24GHZ_BAND;
		modulation |= LIBIPW_OFDM_MODULATION;
	पूर्ण अन्यथा
		priv->ieee->abg_true = 0;

	priv->ieee->mode = mode;
	priv->ieee->freq_band = band;
	priv->ieee->modulation = modulation;
	init_supported_rates(priv, &priv->rates);

	/* Network configuration changed -- क्रमce [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to mode change.\n");
	अगर (!ipw_disassociate(priv)) अणु
		ipw_send_supported_rates(priv, &priv->rates);
		ipw_associate(priv);
	पूर्ण

	/* Update the band LEDs */
	ipw_led_band_on(priv);

	IPW_DEBUG_WX("PRIV SET MODE: %c%c%c\n",
		     mode & IEEE_A ? 'a' : '.',
		     mode & IEEE_B ? 'b' : '.', mode & IEEE_G ? 'g' : '.');
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_wireless_mode(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	चयन (priv->ieee->mode) अणु
	हाल IEEE_A:
		म_नकलन(extra, "802.11a (1)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_B:
		म_नकलन(extra, "802.11b (2)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_A | IEEE_B:
		म_नकलन(extra, "802.11ab (3)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_G:
		म_नकलन(extra, "802.11g (4)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_A | IEEE_G:
		म_नकलन(extra, "802.11ag (5)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_B | IEEE_G:
		म_नकलन(extra, "802.11bg (6)", MAX_WX_STRING);
		अवरोध;
	हाल IEEE_A | IEEE_B | IEEE_G:
		म_नकलन(extra, "802.11abg (7)", MAX_WX_STRING);
		अवरोध;
	शेष:
		म_नकलन(extra, "unknown", MAX_WX_STRING);
		अवरोध;
	पूर्ण
	extra[MAX_WX_STRING - 1] = '\0';

	IPW_DEBUG_WX("PRIV GET MODE: %s\n", extra);

	wrqu->data.length = म_माप(extra) + 1;
	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_set_preamble(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक mode = *(पूर्णांक *)extra;
	mutex_lock(&priv->mutex);
	/* Switching from SHORT -> LONG requires a disassociation */
	अगर (mode == 1) अणु
		अगर (!(priv->config & CFG_PREAMBLE_LONG)) अणु
			priv->config |= CFG_PREAMBLE_LONG;

			/* Network configuration changed -- क्रमce [re]association */
			IPW_DEBUG_ASSOC
			    ("[re]association triggered due to preamble change.\n");
			अगर (!ipw_disassociate(priv))
				ipw_associate(priv);
		पूर्ण
		जाओ करोne;
	पूर्ण

	अगर (mode == 0) अणु
		priv->config &= ~CFG_PREAMBLE_LONG;
		जाओ करोne;
	पूर्ण
	mutex_unlock(&priv->mutex);
	वापस -EINVAL;

      करोne:
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_get_preamble(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	अगर (priv->config & CFG_PREAMBLE_LONG)
		snम_लिखो(wrqu->name, IFNAMSIZ, "long (1)");
	अन्यथा
		snम_लिखो(wrqu->name, IFNAMSIZ, "auto (0)");
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IPW2200_MONITOR
अटल पूर्णांक ipw_wx_set_monitor(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक *parms = (पूर्णांक *)extra;
	पूर्णांक enable = (parms[0] > 0);
	mutex_lock(&priv->mutex);
	IPW_DEBUG_WX("SET MONITOR: %d %d\n", enable, parms[1]);
	अगर (enable) अणु
		अगर (priv->ieee->iw_mode != IW_MODE_MONITOR) अणु
#अगर_घोषित CONFIG_IPW2200_RADIOTAP
			priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
#अन्यथा
			priv->net_dev->type = ARPHRD_IEEE80211;
#पूर्ण_अगर
			schedule_work(&priv->adapter_restart);
		पूर्ण

		ipw_set_channel(priv, parms[1]);
	पूर्ण अन्यथा अणु
		अगर (priv->ieee->iw_mode != IW_MODE_MONITOR) अणु
			mutex_unlock(&priv->mutex);
			वापस 0;
		पूर्ण
		priv->net_dev->type = ARPHRD_ETHER;
		schedule_work(&priv->adapter_restart);
	पूर्ण
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */

अटल पूर्णांक ipw_wx_reset(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	IPW_DEBUG_WX("RESET\n");
	schedule_work(&priv->adapter_restart);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_wx_sw_reset(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	जोड़ iwreq_data wrqu_sec = अणु
		.encoding = अणु
			     .flags = IW_ENCODE_DISABLED,
			     पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	IPW_DEBUG_WX("SW_RESET\n");

	mutex_lock(&priv->mutex);

	ret = ipw_sw_reset(priv, 2);
	अगर (!ret) अणु
		मुक्त_firmware();
		ipw_adapter_restart(priv);
	पूर्ण

	/* The SW reset bit might have been toggled on by the 'disable'
	 * module parameter, so take appropriate action */
	ipw_radio_समाप्त_sw(priv, priv->status & STATUS_RF_KILL_SW);

	mutex_unlock(&priv->mutex);
	libipw_wx_set_encode(priv->ieee, info, &wrqu_sec, शून्य);
	mutex_lock(&priv->mutex);

	अगर (!(priv->status & STATUS_RF_KILL_MASK)) अणु
		/* Configuration likely changed -- क्रमce [re]association */
		IPW_DEBUG_ASSOC("[re]association triggered due to sw "
				"reset.\n");
		अगर (!ipw_disassociate(priv))
			ipw_associate(priv);
	पूर्ण

	mutex_unlock(&priv->mutex);

	वापस 0;
पूर्ण

/* Rebase the WE IOCTLs to zero क्रम the handler array */
अटल iw_handler ipw_wx_handlers[] = अणु
	IW_HANDLER(SIOCGIWNAME, (iw_handler)cfg80211_wext_giwname),
	IW_HANDLER(SIOCSIWFREQ, ipw_wx_set_freq),
	IW_HANDLER(SIOCGIWFREQ, ipw_wx_get_freq),
	IW_HANDLER(SIOCSIWMODE, ipw_wx_set_mode),
	IW_HANDLER(SIOCGIWMODE, ipw_wx_get_mode),
	IW_HANDLER(SIOCSIWSENS, ipw_wx_set_sens),
	IW_HANDLER(SIOCGIWSENS, ipw_wx_get_sens),
	IW_HANDLER(SIOCGIWRANGE, ipw_wx_get_range),
	IW_HANDLER(SIOCSIWAP, ipw_wx_set_wap),
	IW_HANDLER(SIOCGIWAP, ipw_wx_get_wap),
	IW_HANDLER(SIOCSIWSCAN, ipw_wx_set_scan),
	IW_HANDLER(SIOCGIWSCAN, ipw_wx_get_scan),
	IW_HANDLER(SIOCSIWESSID, ipw_wx_set_essid),
	IW_HANDLER(SIOCGIWESSID, ipw_wx_get_essid),
	IW_HANDLER(SIOCSIWNICKN, ipw_wx_set_nick),
	IW_HANDLER(SIOCGIWNICKN, ipw_wx_get_nick),
	IW_HANDLER(SIOCSIWRATE, ipw_wx_set_rate),
	IW_HANDLER(SIOCGIWRATE, ipw_wx_get_rate),
	IW_HANDLER(SIOCSIWRTS, ipw_wx_set_rts),
	IW_HANDLER(SIOCGIWRTS, ipw_wx_get_rts),
	IW_HANDLER(SIOCSIWFRAG, ipw_wx_set_frag),
	IW_HANDLER(SIOCGIWFRAG, ipw_wx_get_frag),
	IW_HANDLER(SIOCSIWTXPOW, ipw_wx_set_txघात),
	IW_HANDLER(SIOCGIWTXPOW, ipw_wx_get_txघात),
	IW_HANDLER(SIOCSIWRETRY, ipw_wx_set_retry),
	IW_HANDLER(SIOCGIWRETRY, ipw_wx_get_retry),
	IW_HANDLER(SIOCSIWENCODE, ipw_wx_set_encode),
	IW_HANDLER(SIOCGIWENCODE, ipw_wx_get_encode),
	IW_HANDLER(SIOCSIWPOWER, ipw_wx_set_घातer),
	IW_HANDLER(SIOCGIWPOWER, ipw_wx_get_घातer),
	IW_HANDLER(SIOCSIWSPY, iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY, iw_handler_get_spy),
	IW_HANDLER(SIOCSIWTHRSPY, iw_handler_set_thrspy),
	IW_HANDLER(SIOCGIWTHRSPY, iw_handler_get_thrspy),
	IW_HANDLER(SIOCSIWGENIE, ipw_wx_set_genie),
	IW_HANDLER(SIOCGIWGENIE, ipw_wx_get_genie),
	IW_HANDLER(SIOCSIWMLME, ipw_wx_set_mlme),
	IW_HANDLER(SIOCSIWAUTH, ipw_wx_set_auth),
	IW_HANDLER(SIOCGIWAUTH, ipw_wx_get_auth),
	IW_HANDLER(SIOCSIWENCODEEXT, ipw_wx_set_encodeext),
	IW_HANDLER(SIOCGIWENCODEEXT, ipw_wx_get_encodeext),
पूर्ण;

क्रमागत अणु
	IPW_PRIV_SET_POWER = SIOCIWFIRSTPRIV,
	IPW_PRIV_GET_POWER,
	IPW_PRIV_SET_MODE,
	IPW_PRIV_GET_MODE,
	IPW_PRIV_SET_PREAMBLE,
	IPW_PRIV_GET_PREAMBLE,
	IPW_PRIV_RESET,
	IPW_PRIV_SW_RESET,
#अगर_घोषित CONFIG_IPW2200_MONITOR
	IPW_PRIV_SET_MONITOR,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा iw_priv_args ipw_priv_args[] = अणु
	अणु
	 .cmd = IPW_PRIV_SET_POWER,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_power"पूर्ण,
	अणु
	 .cmd = IPW_PRIV_GET_POWER,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | MAX_WX_STRING,
	 .name = "get_power"पूर्ण,
	अणु
	 .cmd = IPW_PRIV_SET_MODE,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_mode"पूर्ण,
	अणु
	 .cmd = IPW_PRIV_GET_MODE,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | MAX_WX_STRING,
	 .name = "get_mode"पूर्ण,
	अणु
	 .cmd = IPW_PRIV_SET_PREAMBLE,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_preamble"पूर्ण,
	अणु
	 .cmd = IPW_PRIV_GET_PREAMBLE,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ,
	 .name = "get_preamble"पूर्ण,
	अणु
	 IPW_PRIV_RESET,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 0, 0, "reset"पूर्ण,
	अणु
	 IPW_PRIV_SW_RESET,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 0, 0, "sw_reset"पूर्ण,
#अगर_घोषित CONFIG_IPW2200_MONITOR
	अणु
	 IPW_PRIV_SET_MONITOR,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "monitor"पूर्ण,
#पूर्ण_अगर				/* CONFIG_IPW2200_MONITOR */
पूर्ण;

अटल iw_handler ipw_priv_handler[] = अणु
	ipw_wx_set_घातermode,
	ipw_wx_get_घातermode,
	ipw_wx_set_wireless_mode,
	ipw_wx_get_wireless_mode,
	ipw_wx_set_preamble,
	ipw_wx_get_preamble,
	ipw_wx_reset,
	ipw_wx_sw_reset,
#अगर_घोषित CONFIG_IPW2200_MONITOR
	ipw_wx_set_monitor,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def ipw_wx_handler_def = अणु
	.standard = ipw_wx_handlers,
	.num_standard = ARRAY_SIZE(ipw_wx_handlers),
	.num_निजी = ARRAY_SIZE(ipw_priv_handler),
	.num_निजी_args = ARRAY_SIZE(ipw_priv_args),
	.निजी = ipw_priv_handler,
	.निजी_args = ipw_priv_args,
	.get_wireless_stats = ipw_get_wireless_stats,
पूर्ण;

/*
 * Get wireless statistics.
 * Called by /proc/net/wireless
 * Also called by SIOCGIWSTATS
 */
अटल काष्ठा iw_statistics *ipw_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा iw_statistics *wstats;

	wstats = &priv->wstats;

	/* अगर hw is disabled, then ipw_get_ordinal() can't be called.
	 * netdev->get_wireless_stats seems to be called beक्रमe fw is
	 * initialized.  STATUS_ASSOCIATED will only be set अगर the hw is up
	 * and associated; अगर not associcated, the values are all meaningless
	 * anyway, so set them all to शून्य and INVALID */
	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		wstats->miss.beacon = 0;
		wstats->discard.retries = 0;
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
		wstats->qual.updated = 7;
		wstats->qual.updated |= IW_QUAL_NOISE_INVALID |
		    IW_QUAL_QUAL_INVALID | IW_QUAL_LEVEL_INVALID;
		वापस wstats;
	पूर्ण

	wstats->qual.qual = priv->quality;
	wstats->qual.level = priv->exp_avg_rssi;
	wstats->qual.noise = priv->exp_avg_noise;
	wstats->qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED |
	    IW_QUAL_NOISE_UPDATED | IW_QUAL_DBM;

	wstats->miss.beacon = average_value(&priv->average_missed_beacons);
	wstats->discard.retries = priv->last_tx_failures;
	wstats->discard.code = priv->ieee->ieee_stats.rx_discards_undecryptable;

/*	अगर (ipw_get_ordinal(priv, IPW_ORD_STAT_TX_RETRY, &tx_retry, &len))
	जाओ fail_get_ordinal;
	wstats->discard.retries += tx_retry; */

	वापस wstats;
पूर्ण

/* net device stuff */

अटल  व्योम init_sys_config(काष्ठा ipw_sys_config *sys_config)
अणु
	स_रखो(sys_config, 0, माप(काष्ठा ipw_sys_config));
	sys_config->bt_coexistence = 0;
	sys_config->answer_broadcast_ssid_probe = 0;
	sys_config->accept_all_data_frames = 0;
	sys_config->accept_non_directed_frames = 1;
	sys_config->exclude_unicast_unencrypted = 0;
	sys_config->disable_unicast_decryption = 1;
	sys_config->exclude_multicast_unencrypted = 0;
	sys_config->disable_multicast_decryption = 1;
	अगर (antenna < CFG_SYS_ANTENNA_BOTH || antenna > CFG_SYS_ANTENNA_B)
		antenna = CFG_SYS_ANTENNA_BOTH;
	sys_config->antenna_भागersity = antenna;
	sys_config->pass_crc_to_host = 0;	/* TODO: See अगर 1 gives us FCS */
	sys_config->करोt11g_स्वतः_detection = 0;
	sys_config->enable_cts_to_self = 0;
	sys_config->bt_coexist_collision_thr = 0;
	sys_config->pass_noise_stats_to_host = 1;	/* 1 -- fix क्रम 256 */
	sys_config->silence_threshold = 0x1e;
पूर्ण

अटल पूर्णांक ipw_net_खोलो(काष्ठा net_device *dev)
अणु
	IPW_DEBUG_INFO("dev->open\n");
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_net_stop(काष्ठा net_device *dev)
अणु
	IPW_DEBUG_INFO("dev->close\n");
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

/*
toकरो:

modअगरy to send one tfd per fragment instead of using chunking.  otherwise
we need to heavily modअगरy the libipw_skb_to_txb.
*/

अटल पूर्णांक ipw_tx_skb(काष्ठा ipw_priv *priv, काष्ठा libipw_txb *txb,
			     पूर्णांक pri)
अणु
	काष्ठा libipw_hdr_3addrqos *hdr = (काष्ठा libipw_hdr_3addrqos *)
	    txb->fragments[0]->data;
	पूर्णांक i = 0;
	काष्ठा tfd_frame *tfd;
#अगर_घोषित CONFIG_IPW2200_QOS
	पूर्णांक tx_id = ipw_get_tx_queue_number(priv, pri);
	काष्ठा clx2_tx_queue *txq = &priv->txq[tx_id];
#अन्यथा
	काष्ठा clx2_tx_queue *txq = &priv->txq[0];
#पूर्ण_अगर
	काष्ठा clx2_queue *q = &txq->q;
	u8 id, hdr_len, unicast;
	पूर्णांक fc;

	अगर (!(priv->status & STATUS_ASSOCIATED))
		जाओ drop;

	hdr_len = libipw_get_hdrlen(le16_to_cpu(hdr->frame_ctl));
	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		unicast = !is_multicast_ether_addr(hdr->addr1);
		id = ipw_find_station(priv, hdr->addr1);
		अगर (id == IPW_INVALID_STATION) अणु
			id = ipw_add_station(priv, hdr->addr1);
			अगर (id == IPW_INVALID_STATION) अणु
				IPW_WARNING("Attempt to send data to "
					    "invalid cell: %pM\n",
					    hdr->addr1);
				जाओ drop;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IW_MODE_INFRA:
	शेष:
		unicast = !is_multicast_ether_addr(hdr->addr3);
		id = 0;
		अवरोध;
	पूर्ण

	tfd = &txq->bd[q->first_empty];
	txq->txb[q->first_empty] = txb;
	स_रखो(tfd, 0, माप(*tfd));
	tfd->u.data.station_number = id;

	tfd->control_flags.message_type = TX_FRAME_TYPE;
	tfd->control_flags.control_bits = TFD_NEED_IRQ_MASK;

	tfd->u.data.cmd_id = DINO_CMD_TX;
	tfd->u.data.len = cpu_to_le16(txb->payload_size);

	अगर (priv->assoc_request.ieee_mode == IPW_B_MODE)
		tfd->u.data.tx_flags_ext |= DCT_FLAG_EXT_MODE_CCK;
	अन्यथा
		tfd->u.data.tx_flags_ext |= DCT_FLAG_EXT_MODE_OFDM;

	अगर (priv->assoc_request.preamble_length == DCT_FLAG_SHORT_PREAMBLE)
		tfd->u.data.tx_flags |= DCT_FLAG_SHORT_PREAMBLE;

	fc = le16_to_cpu(hdr->frame_ctl);
	hdr->frame_ctl = cpu_to_le16(fc & ~IEEE80211_FCTL_MOREFRAGS);

	स_नकल(&tfd->u.data.tfd.tfd_24.mchdr, hdr, hdr_len);

	अगर (likely(unicast))
		tfd->u.data.tx_flags |= DCT_FLAG_ACK_REQD;

	अगर (txb->encrypted && !priv->ieee->host_encrypt) अणु
		चयन (priv->ieee->sec.level) अणु
		हाल SEC_LEVEL_3:
			tfd->u.data.tfd.tfd_24.mchdr.frame_ctl |=
			    cpu_to_le16(IEEE80211_FCTL_PROTECTED);
			/* XXX: ACK flag must be set क्रम CCMP even अगर it
			 * is a multicast/broadcast packet, because CCMP
			 * group communication encrypted by GTK is
			 * actually करोne by the AP. */
			अगर (!unicast)
				tfd->u.data.tx_flags |= DCT_FLAG_ACK_REQD;

			tfd->u.data.tx_flags &= ~DCT_FLAG_NO_WEP;
			tfd->u.data.tx_flags_ext |= DCT_FLAG_EXT_SECURITY_CCM;
			tfd->u.data.key_index = 0;
			tfd->u.data.key_index |= DCT_WEP_INDEX_USE_IMMEDIATE;
			अवरोध;
		हाल SEC_LEVEL_2:
			tfd->u.data.tfd.tfd_24.mchdr.frame_ctl |=
			    cpu_to_le16(IEEE80211_FCTL_PROTECTED);
			tfd->u.data.tx_flags &= ~DCT_FLAG_NO_WEP;
			tfd->u.data.tx_flags_ext |= DCT_FLAG_EXT_SECURITY_TKIP;
			tfd->u.data.key_index = DCT_WEP_INDEX_USE_IMMEDIATE;
			अवरोध;
		हाल SEC_LEVEL_1:
			tfd->u.data.tfd.tfd_24.mchdr.frame_ctl |=
			    cpu_to_le16(IEEE80211_FCTL_PROTECTED);
			tfd->u.data.key_index = priv->ieee->crypt_info.tx_keyidx;
			अगर (priv->ieee->sec.key_sizes[priv->ieee->crypt_info.tx_keyidx] <=
			    40)
				tfd->u.data.key_index |= DCT_WEP_KEY_64Bit;
			अन्यथा
				tfd->u.data.key_index |= DCT_WEP_KEY_128Bit;
			अवरोध;
		हाल SEC_LEVEL_0:
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "Unknown security level %d\n",
			       priv->ieee->sec.level);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		/* No hardware encryption */
		tfd->u.data.tx_flags |= DCT_FLAG_NO_WEP;

#अगर_घोषित CONFIG_IPW2200_QOS
	अगर (fc & IEEE80211_STYPE_QOS_DATA)
		ipw_qos_set_tx_queue_command(priv, pri, &(tfd->u.data));
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	/* payload */
	tfd->u.data.num_chunks = cpu_to_le32(min((u8) (NUM_TFD_CHUNKS - 2),
						 txb->nr_frags));
	IPW_DEBUG_FRAG("%i fragments being sent as %i chunks.\n",
		       txb->nr_frags, le32_to_cpu(tfd->u.data.num_chunks));
	क्रम (i = 0; i < le32_to_cpu(tfd->u.data.num_chunks); i++) अणु
		IPW_DEBUG_FRAG("Adding fragment %i of %i (%d bytes).\n",
			       i, le32_to_cpu(tfd->u.data.num_chunks),
			       txb->fragments[i]->len - hdr_len);
		IPW_DEBUG_TX("Dumping TX packet frag %i of %i (%d bytes):\n",
			     i, tfd->u.data.num_chunks,
			     txb->fragments[i]->len - hdr_len);
		prपूर्णांकk_buf(IPW_DL_TX, txb->fragments[i]->data + hdr_len,
			   txb->fragments[i]->len - hdr_len);

		tfd->u.data.chunk_ptr[i] =
		    cpu_to_le32(dma_map_single(&priv->pci_dev->dev,
					       txb->fragments[i]->data + hdr_len,
					       txb->fragments[i]->len - hdr_len,
					       DMA_TO_DEVICE));
		tfd->u.data.chunk_len[i] =
		    cpu_to_le16(txb->fragments[i]->len - hdr_len);
	पूर्ण

	अगर (i != txb->nr_frags) अणु
		काष्ठा sk_buff *skb;
		u16 reमुख्यing_bytes = 0;
		पूर्णांक j;

		क्रम (j = i; j < txb->nr_frags; j++)
			reमुख्यing_bytes += txb->fragments[j]->len - hdr_len;

		prपूर्णांकk(KERN_INFO "Trying to reallocate for %d bytes\n",
		       reमुख्यing_bytes);
		skb = alloc_skb(reमुख्यing_bytes, GFP_ATOMIC);
		अगर (skb != शून्य) अणु
			tfd->u.data.chunk_len[i] = cpu_to_le16(reमुख्यing_bytes);
			क्रम (j = i; j < txb->nr_frags; j++) अणु
				पूर्णांक size = txb->fragments[j]->len - hdr_len;

				prपूर्णांकk(KERN_INFO "Adding frag %d %d...\n",
				       j, size);
				skb_put_data(skb,
					     txb->fragments[j]->data + hdr_len,
					     size);
			पूर्ण
			dev_kमुक्त_skb_any(txb->fragments[i]);
			txb->fragments[i] = skb;
			tfd->u.data.chunk_ptr[i] =
			    cpu_to_le32(dma_map_single(&priv->pci_dev->dev,
						       skb->data,
						       reमुख्यing_bytes,
						       DMA_TO_DEVICE));

			le32_add_cpu(&tfd->u.data.num_chunks, 1);
		पूर्ण
	पूर्ण

	/* kick DMA */
	q->first_empty = ipw_queue_inc_wrap(q->first_empty, q->n_bd);
	ipw_ग_लिखो32(priv, q->reg_w, q->first_empty);

	अगर (ipw_tx_queue_space(q) < q->high_mark)
		netअगर_stop_queue(priv->net_dev);

	वापस NETDEV_TX_OK;

      drop:
	IPW_DEBUG_DROP("Silently dropping Tx packet.\n");
	libipw_txb_मुक्त(txb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ipw_net_is_queue_full(काष्ठा net_device *dev, पूर्णांक pri)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
#अगर_घोषित CONFIG_IPW2200_QOS
	पूर्णांक tx_id = ipw_get_tx_queue_number(priv, pri);
	काष्ठा clx2_tx_queue *txq = &priv->txq[tx_id];
#अन्यथा
	काष्ठा clx2_tx_queue *txq = &priv->txq[0];
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	अगर (ipw_tx_queue_space(&txq->q) < txq->q.high_mark)
		वापस 1;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
अटल व्योम ipw_handle_promiscuous_tx(काष्ठा ipw_priv *priv,
				      काष्ठा libipw_txb *txb)
अणु
	काष्ठा libipw_rx_stats dummystats;
	काष्ठा ieee80211_hdr *hdr;
	u8 n;
	u16 filter = priv->prom_priv->filter;
	पूर्णांक hdr_only = 0;

	अगर (filter & IPW_PROM_NO_TX)
		वापस;

	स_रखो(&dummystats, 0, माप(dummystats));

	/* Filtering of fragment chains is करोne against the first fragment */
	hdr = (व्योम *)txb->fragments[0]->data;
	अगर (libipw_is_management(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_MGMT)
			वापस;
		अगर (filter & IPW_PROM_MGMT_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण अन्यथा अगर (libipw_is_control(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_CTL)
			वापस;
		अगर (filter & IPW_PROM_CTL_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण अन्यथा अगर (libipw_is_data(le16_to_cpu(hdr->frame_control))) अणु
		अगर (filter & IPW_PROM_NO_DATA)
			वापस;
		अगर (filter & IPW_PROM_DATA_HEADER_ONLY)
			hdr_only = 1;
	पूर्ण

	क्रम(n=0; n<txb->nr_frags; ++n) अणु
		काष्ठा sk_buff *src = txb->fragments[n];
		काष्ठा sk_buff *dst;
		काष्ठा ieee80211_radiotap_header *rt_hdr;
		पूर्णांक len;

		अगर (hdr_only) अणु
			hdr = (व्योम *)src->data;
			len = libipw_get_hdrlen(le16_to_cpu(hdr->frame_control));
		पूर्ण अन्यथा
			len = src->len;

		dst = alloc_skb(len + माप(*rt_hdr) + माप(u16)*2, GFP_ATOMIC);
		अगर (!dst)
			जारी;

		rt_hdr = skb_put(dst, माप(*rt_hdr));

		rt_hdr->it_version = PKTHDR_RADIOTAP_VERSION;
		rt_hdr->it_pad = 0;
		rt_hdr->it_present = 0; /* after all, it's just an idea */
		rt_hdr->it_present |=  cpu_to_le32(1 << IEEE80211_RADIOTAP_CHANNEL);

		*(__le16*)skb_put(dst, माप(u16)) = cpu_to_le16(
			ieee80211chan2mhz(priv->channel));
		अगर (priv->channel > 14) 	/* 802.11a */
			*(__le16*)skb_put(dst, माप(u16)) =
				cpu_to_le16(IEEE80211_CHAN_OFDM |
					     IEEE80211_CHAN_5GHZ);
		अन्यथा अगर (priv->ieee->mode == IEEE_B) /* 802.11b */
			*(__le16*)skb_put(dst, माप(u16)) =
				cpu_to_le16(IEEE80211_CHAN_CCK |
					     IEEE80211_CHAN_2GHZ);
		अन्यथा 		/* 802.11g */
			*(__le16*)skb_put(dst, माप(u16)) =
				cpu_to_le16(IEEE80211_CHAN_OFDM |
				 IEEE80211_CHAN_2GHZ);

		rt_hdr->it_len = cpu_to_le16(dst->len);

		skb_copy_from_linear_data(src, skb_put(dst, len), len);

		अगर (!libipw_rx(priv->prom_priv->ieee, dst, &dummystats))
			dev_kमुक्त_skb_any(dst);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t ipw_net_hard_start_xmit(काष्ठा libipw_txb *txb,
					   काष्ठा net_device *dev, पूर्णांक pri)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	अचिन्हित दीर्घ flags;
	netdev_tx_t ret;

	IPW_DEBUG_TX("dev->xmit(%d bytes)\n", txb->payload_size);
	spin_lock_irqsave(&priv->lock, flags);

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	अगर (rtap_अगरace && netअगर_running(priv->prom_net_dev))
		ipw_handle_promiscuous_tx(priv, txb);
#पूर्ण_अगर

	ret = ipw_tx_skb(priv, txb, pri);
	अगर (ret == NETDEV_TX_OK)
		__ipw_led_activity_on(priv);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ipw_net_set_multicast_list(काष्ठा net_device *dev)
अणु

पूर्ण

अटल पूर्णांक ipw_net_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	mutex_lock(&priv->mutex);
	priv->config |= CFG_CUSTOM_MAC;
	स_नकल(priv->mac_addr, addr->sa_data, ETH_ALEN);
	prपूर्णांकk(KERN_INFO "%s: Setting MAC to %pM\n",
	       priv->net_dev->name, priv->mac_addr);
	schedule_work(&priv->adapter_restart);
	mutex_unlock(&priv->mutex);
	वापस 0;
पूर्ण

अटल व्योम ipw_ethtool_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ipw_priv *p = libipw_priv(dev);
	अक्षर vers[64];
	अक्षर date[32];
	u32 len;

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));

	len = माप(vers);
	ipw_get_ordinal(p, IPW_ORD_STAT_FW_VERSION, vers, &len);
	len = माप(date);
	ipw_get_ordinal(p, IPW_ORD_STAT_FW_DATE, date, &len);

	snम_लिखो(info->fw_version, माप(info->fw_version), "%s (%s)",
		 vers, date);
	strlcpy(info->bus_info, pci_name(p->pci_dev),
		माप(info->bus_info));
पूर्ण

अटल u32 ipw_ethtool_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	वापस (priv->status & STATUS_ASSOCIATED) != 0;
पूर्ण

अटल पूर्णांक ipw_ethtool_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस IPW_EEPROM_IMAGE_SIZE;
पूर्ण

अटल पूर्णांक ipw_ethtool_get_eeprom(काष्ठा net_device *dev,
				  काष्ठा ethtool_eeprom *eeprom, u8 * bytes)
अणु
	काष्ठा ipw_priv *p = libipw_priv(dev);

	अगर (eeprom->offset + eeprom->len > IPW_EEPROM_IMAGE_SIZE)
		वापस -EINVAL;
	mutex_lock(&p->mutex);
	स_नकल(bytes, &p->eeprom[eeprom->offset], eeprom->len);
	mutex_unlock(&p->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_ethtool_set_eeprom(काष्ठा net_device *dev,
				  काष्ठा ethtool_eeprom *eeprom, u8 * bytes)
अणु
	काष्ठा ipw_priv *p = libipw_priv(dev);
	पूर्णांक i;

	अगर (eeprom->offset + eeprom->len > IPW_EEPROM_IMAGE_SIZE)
		वापस -EINVAL;
	mutex_lock(&p->mutex);
	स_नकल(&p->eeprom[eeprom->offset], bytes, eeprom->len);
	क्रम (i = 0; i < IPW_EEPROM_IMAGE_SIZE; i++)
		ipw_ग_लिखो8(p, i + IPW_EEPROM_DATA, p->eeprom[i]);
	mutex_unlock(&p->mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ipw_ethtool_ops = अणु
	.get_link = ipw_ethtool_get_link,
	.get_drvinfo = ipw_ethtool_get_drvinfo,
	.get_eeprom_len = ipw_ethtool_get_eeprom_len,
	.get_eeprom = ipw_ethtool_get_eeprom,
	.set_eeprom = ipw_ethtool_set_eeprom,
पूर्ण;

अटल irqवापस_t ipw_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ipw_priv *priv = data;
	u32 पूर्णांकa, पूर्णांकa_mask;

	अगर (!priv)
		वापस IRQ_NONE;

	spin_lock(&priv->irq_lock);

	अगर (!(priv->status & STATUS_INT_ENABLED)) अणु
		/* IRQ is disabled */
		जाओ none;
	पूर्ण

	पूर्णांकa = ipw_पढ़ो32(priv, IPW_INTA_RW);
	पूर्णांकa_mask = ipw_पढ़ो32(priv, IPW_INTA_MASK_R);

	अगर (पूर्णांकa == 0xFFFFFFFF) अणु
		/* Hardware disappeared */
		IPW_WARNING("IRQ INTA == 0xFFFFFFFF\n");
		जाओ none;
	पूर्ण

	अगर (!(पूर्णांकa & (IPW_INTA_MASK_ALL & पूर्णांकa_mask))) अणु
		/* Shared पूर्णांकerrupt */
		जाओ none;
	पूर्ण

	/* tell the device to stop sending पूर्णांकerrupts */
	__ipw_disable_पूर्णांकerrupts(priv);

	/* ack current पूर्णांकerrupts */
	पूर्णांकa &= (IPW_INTA_MASK_ALL & पूर्णांकa_mask);
	ipw_ग_लिखो32(priv, IPW_INTA_RW, पूर्णांकa);

	/* Cache INTA value क्रम our tasklet */
	priv->isr_पूर्णांकa = पूर्णांकa;

	tasklet_schedule(&priv->irq_tasklet);

	spin_unlock(&priv->irq_lock);

	वापस IRQ_HANDLED;
      none:
	spin_unlock(&priv->irq_lock);
	वापस IRQ_NONE;
पूर्ण

अटल व्योम ipw_rf_समाप्त(व्योम *adapter)
अणु
	काष्ठा ipw_priv *priv = adapter;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (rf_समाप्त_active(priv)) अणु
		IPW_DEBUG_RF_KILL("RF Kill active, rescheduling GPIO check\n");
		schedule_delayed_work(&priv->rf_समाप्त, 2 * HZ);
		जाओ निकास_unlock;
	पूर्ण

	/* RF Kill is now disabled, so bring the device back up */

	अगर (!(priv->status & STATUS_RF_KILL_MASK)) अणु
		IPW_DEBUG_RF_KILL("HW RF Kill no longer active, restarting "
				  "device\n");

		/* we can not करो an adapter restart जबतक inside an irq lock */
		schedule_work(&priv->adapter_restart);
	पूर्ण अन्यथा
		IPW_DEBUG_RF_KILL("HW RF Kill deactivated.  SW RF Kill still "
				  "enabled\n");

      निकास_unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम ipw_bg_rf_समाप्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, rf_समाप्त.work);
	mutex_lock(&priv->mutex);
	ipw_rf_समाप्त(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_link_up(काष्ठा ipw_priv *priv)
अणु
	priv->last_seq_num = -1;
	priv->last_frag_num = -1;
	priv->last_packet_समय = 0;

	netअगर_carrier_on(priv->net_dev);

	cancel_delayed_work(&priv->request_scan);
	cancel_delayed_work(&priv->request_direct_scan);
	cancel_delayed_work(&priv->request_passive_scan);
	cancel_delayed_work(&priv->scan_event);
	ipw_reset_stats(priv);
	/* Ensure the rate is updated immediately */
	priv->last_rate = ipw_get_current_rate(priv);
	ipw_gather_stats(priv);
	ipw_led_link_up(priv);
	notअगरy_wx_assoc_event(priv);

	अगर (priv->config & CFG_BACKGROUND_SCAN)
		schedule_delayed_work(&priv->request_scan, HZ);
पूर्ण

अटल व्योम ipw_bg_link_up(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, link_up);
	mutex_lock(&priv->mutex);
	ipw_link_up(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_link_करोwn(काष्ठा ipw_priv *priv)
अणु
	ipw_led_link_करोwn(priv);
	netअगर_carrier_off(priv->net_dev);
	notअगरy_wx_assoc_event(priv);

	/* Cancel any queued work ... */
	cancel_delayed_work(&priv->request_scan);
	cancel_delayed_work(&priv->request_direct_scan);
	cancel_delayed_work(&priv->request_passive_scan);
	cancel_delayed_work(&priv->adhoc_check);
	cancel_delayed_work(&priv->gather_stats);

	ipw_reset_stats(priv);

	अगर (!(priv->status & STATUS_EXIT_PENDING)) अणु
		/* Queue up another scan... */
		schedule_delayed_work(&priv->request_scan, 0);
	पूर्ण अन्यथा
		cancel_delayed_work(&priv->scan_event);
पूर्ण

अटल व्योम ipw_bg_link_करोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, link_करोwn);
	mutex_lock(&priv->mutex);
	ipw_link_करोwn(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_setup_deferred_work(काष्ठा ipw_priv *priv)
अणु
	init_रुकोqueue_head(&priv->रुको_command_queue);
	init_रुकोqueue_head(&priv->रुको_state);

	INIT_DELAYED_WORK(&priv->adhoc_check, ipw_bg_adhoc_check);
	INIT_WORK(&priv->associate, ipw_bg_associate);
	INIT_WORK(&priv->disassociate, ipw_bg_disassociate);
	INIT_WORK(&priv->प्रणाली_config, ipw_प्रणाली_config);
	INIT_WORK(&priv->rx_replenish, ipw_bg_rx_queue_replenish);
	INIT_WORK(&priv->adapter_restart, ipw_bg_adapter_restart);
	INIT_DELAYED_WORK(&priv->rf_समाप्त, ipw_bg_rf_समाप्त);
	INIT_WORK(&priv->up, ipw_bg_up);
	INIT_WORK(&priv->करोwn, ipw_bg_करोwn);
	INIT_DELAYED_WORK(&priv->request_scan, ipw_request_scan);
	INIT_DELAYED_WORK(&priv->request_direct_scan, ipw_request_direct_scan);
	INIT_DELAYED_WORK(&priv->request_passive_scan, ipw_request_passive_scan);
	INIT_DELAYED_WORK(&priv->scan_event, ipw_scan_event);
	INIT_DELAYED_WORK(&priv->gather_stats, ipw_bg_gather_stats);
	INIT_WORK(&priv->पात_scan, ipw_bg_पात_scan);
	INIT_WORK(&priv->roam, ipw_bg_roam);
	INIT_DELAYED_WORK(&priv->scan_check, ipw_bg_scan_check);
	INIT_WORK(&priv->link_up, ipw_bg_link_up);
	INIT_WORK(&priv->link_करोwn, ipw_bg_link_करोwn);
	INIT_DELAYED_WORK(&priv->led_link_on, ipw_bg_led_link_on);
	INIT_DELAYED_WORK(&priv->led_link_off, ipw_bg_led_link_off);
	INIT_DELAYED_WORK(&priv->led_act_off, ipw_bg_led_activity_off);
	INIT_WORK(&priv->merge_networks, ipw_merge_adhoc_network);

#अगर_घोषित CONFIG_IPW2200_QOS
	INIT_WORK(&priv->qos_activate, ipw_bg_qos_activate);
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	tasklet_setup(&priv->irq_tasklet, ipw_irq_tasklet);
पूर्ण

अटल व्योम shim__set_security(काष्ठा net_device *dev,
			       काष्ठा libipw_security *sec)
अणु
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	पूर्णांक i;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (sec->flags & (1 << i)) अणु
			priv->ieee->sec.encode_alg[i] = sec->encode_alg[i];
			priv->ieee->sec.key_sizes[i] = sec->key_sizes[i];
			अगर (sec->key_sizes[i] == 0)
				priv->ieee->sec.flags &= ~(1 << i);
			अन्यथा अणु
				स_नकल(priv->ieee->sec.keys[i], sec->keys[i],
				       sec->key_sizes[i]);
				priv->ieee->sec.flags |= (1 << i);
			पूर्ण
			priv->status |= STATUS_SECURITY_UPDATED;
		पूर्ण अन्यथा अगर (sec->level != SEC_LEVEL_1)
			priv->ieee->sec.flags &= ~(1 << i);
	पूर्ण

	अगर (sec->flags & SEC_ACTIVE_KEY) अणु
		priv->ieee->sec.active_key = sec->active_key;
		priv->ieee->sec.flags |= SEC_ACTIVE_KEY;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण अन्यथा
		priv->ieee->sec.flags &= ~SEC_ACTIVE_KEY;

	अगर ((sec->flags & SEC_AUTH_MODE) &&
	    (priv->ieee->sec.auth_mode != sec->auth_mode)) अणु
		priv->ieee->sec.auth_mode = sec->auth_mode;
		priv->ieee->sec.flags |= SEC_AUTH_MODE;
		अगर (sec->auth_mode == WLAN_AUTH_SHARED_KEY)
			priv->capability |= CAP_SHARED_KEY;
		अन्यथा
			priv->capability &= ~CAP_SHARED_KEY;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	अगर (sec->flags & SEC_ENABLED && priv->ieee->sec.enabled != sec->enabled) अणु
		priv->ieee->sec.flags |= SEC_ENABLED;
		priv->ieee->sec.enabled = sec->enabled;
		priv->status |= STATUS_SECURITY_UPDATED;
		अगर (sec->enabled)
			priv->capability |= CAP_PRIVACY_ON;
		अन्यथा
			priv->capability &= ~CAP_PRIVACY_ON;
	पूर्ण

	अगर (sec->flags & SEC_ENCRYPT)
		priv->ieee->sec.encrypt = sec->encrypt;

	अगर (sec->flags & SEC_LEVEL && priv->ieee->sec.level != sec->level) अणु
		priv->ieee->sec.level = sec->level;
		priv->ieee->sec.flags |= SEC_LEVEL;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	अगर (!priv->ieee->host_encrypt && (sec->flags & SEC_ENCRYPT))
		ipw_set_hwcrypto_keys(priv);

	/* To match current functionality of ipw2100 (which works well w/
	 * various supplicants, we करोn't क्रमce a disassociate अगर the
	 * privacy capability changes ... */
#अगर 0
	अगर ((priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)) &&
	    (((priv->assoc_request.capability &
	       cpu_to_le16(WLAN_CAPABILITY_PRIVACY)) && !sec->enabled) ||
	     (!(priv->assoc_request.capability &
		cpu_to_le16(WLAN_CAPABILITY_PRIVACY)) && sec->enabled))) अणु
		IPW_DEBUG_ASSOC("Disassociating due to capability "
				"change.\n");
		ipw_disassociate(priv);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक init_supported_rates(काष्ठा ipw_priv *priv,
				काष्ठा ipw_supported_rates *rates)
अणु
	/* TODO: Mask out rates based on priv->rates_mask */

	स_रखो(rates, 0, माप(*rates));
	/* configure supported rates */
	चयन (priv->ieee->freq_band) अणु
	हाल LIBIPW_52GHZ_BAND:
		rates->ieee_mode = IPW_A_MODE;
		rates->purpose = IPW_RATE_CAPABILITIES;
		ipw_add_ofdm_scan_rates(rates, LIBIPW_CCK_MODULATION,
					LIBIPW_OFDM_DEFAULT_RATES_MASK);
		अवरोध;

	शेष:		/* Mixed or 2.4Ghz */
		rates->ieee_mode = IPW_G_MODE;
		rates->purpose = IPW_RATE_CAPABILITIES;
		ipw_add_cck_scan_rates(rates, LIBIPW_CCK_MODULATION,
				       LIBIPW_CCK_DEFAULT_RATES_MASK);
		अगर (priv->ieee->modulation & LIBIPW_OFDM_MODULATION) अणु
			ipw_add_ofdm_scan_rates(rates, LIBIPW_CCK_MODULATION,
						LIBIPW_OFDM_DEFAULT_RATES_MASK);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_config(काष्ठा ipw_priv *priv)
अणु
	/* This is only called from ipw_up, which resets/reloads the firmware
	   so, we करोn't need to first disable the card beक्रमe we configure
	   it */
	अगर (ipw_set_tx_घातer(priv))
		जाओ error;

	/* initialize adapter address */
	अगर (ipw_send_adapter_address(priv, priv->net_dev->dev_addr))
		जाओ error;

	/* set basic प्रणाली config settings */
	init_sys_config(&priv->sys_config);

	/* Support Bluetooth अगर we have BT h/w on board, and user wants to.
	 * Does not support BT priority yet (करोn't पात or defer our Tx) */
	अगर (bt_coexist) अणु
		अचिन्हित अक्षर bt_caps = priv->eeprom[EEPROM_SKU_CAPABILITY];

		अगर (bt_caps & EEPROM_SKU_CAP_BT_CHANNEL_SIG)
			priv->sys_config.bt_coexistence
			    |= CFG_BT_COEXISTENCE_SIGNAL_CHNL;
		अगर (bt_caps & EEPROM_SKU_CAP_BT_OOB)
			priv->sys_config.bt_coexistence
			    |= CFG_BT_COEXISTENCE_OOB;
	पूर्ण

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	अगर (priv->prom_net_dev && netअगर_running(priv->prom_net_dev)) अणु
		priv->sys_config.accept_all_data_frames = 1;
		priv->sys_config.accept_non_directed_frames = 1;
		priv->sys_config.accept_all_mgmt_bcpr = 1;
		priv->sys_config.accept_all_mgmt_frames = 1;
	पूर्ण
#पूर्ण_अगर

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC)
		priv->sys_config.answer_broadcast_ssid_probe = 1;
	अन्यथा
		priv->sys_config.answer_broadcast_ssid_probe = 0;

	अगर (ipw_send_प्रणाली_config(priv))
		जाओ error;

	init_supported_rates(priv, &priv->rates);
	अगर (ipw_send_supported_rates(priv, &priv->rates))
		जाओ error;

	/* Set request-to-send threshold */
	अगर (priv->rts_threshold) अणु
		अगर (ipw_send_rts_threshold(priv, priv->rts_threshold))
			जाओ error;
	पूर्ण
#अगर_घोषित CONFIG_IPW2200_QOS
	IPW_DEBUG_QOS("QoS: call ipw_qos_activate\n");
	ipw_qos_activate(priv, शून्य);
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	अगर (ipw_set_अक्रमom_seed(priv))
		जाओ error;

	/* final state transition to the RUN state */
	अगर (ipw_send_host_complete(priv))
		जाओ error;

	priv->status |= STATUS_INIT;

	ipw_led_init(priv);
	ipw_led_radio_on(priv);
	priv->notअगर_missed_beacons = 0;

	/* Set hardware WEP key अगर it is configured. */
	अगर ((priv->capability & CAP_PRIVACY_ON) &&
	    (priv->ieee->sec.level == SEC_LEVEL_1) &&
	    !(priv->ieee->host_encrypt || priv->ieee->host_decrypt))
		ipw_set_hwcrypto_keys(priv);

	वापस 0;

      error:
	वापस -EIO;
पूर्ण

/*
 * NOTE:
 *
 * These tables have been tested in conjunction with the
 * Intel PRO/Wireless 2200BG and 2915ABG Network Connection Adapters.
 *
 * Altering this values, using it on other hardware, or in geographies
 * not पूर्णांकended क्रम resale of the above mentioned Intel adapters has
 * not been tested.
 *
 * Remember to update the table in README.ipw2200 when changing this
 * table.
 *
 */
अटल स्थिर काष्ठा libipw_geo ipw_geos[] = अणु
	अणु			/* Restricted */
	 "---",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom US/Canada */
	 "ZZF",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 .a_channels = 8,
	 .a = अणुअणु5180, 36पूर्ण,
	       अणु5200, 40पूर्ण,
	       अणु5220, 44पूर्ण,
	       अणु5240, 48पूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Rest of World */
	 "ZZD",
	 .bg_channels = 13,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण, अणु2467, 12पूर्ण,
		अणु2472, 13पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom USA & Europe & High */
	 "ZZA",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 .a_channels = 13,
	 .a = अणुअणु5180, 36पूर्ण,
	       अणु5200, 40पूर्ण,
	       अणु5220, 44पूर्ण,
	       अणु5240, 48पूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5745, 149पूर्ण,
	       अणु5765, 153पूर्ण,
	       अणु5785, 157पूर्ण,
	       अणु5805, 161पूर्ण,
	       अणु5825, 165पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom NA & Europe */
	 "ZZB",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 .a_channels = 13,
	 .a = अणुअणु5180, 36पूर्ण,
	       अणु5200, 40पूर्ण,
	       अणु5220, 44पूर्ण,
	       अणु5240, 48पूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5745, 149, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5765, 153, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5785, 157, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5805, 161, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5825, 165, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom Japan */
	 "ZZC",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 .a_channels = 4,
	 .a = अणुअणु5170, 34पूर्ण, अणु5190, 38पूर्ण,
	       अणु5210, 42पूर्ण, अणु5230, 46पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom */
	 "ZZM",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Europe */
	 "ZZE",
	 .bg_channels = 13,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण, अणु2467, 12पूर्ण,
		अणु2472, 13पूर्णपूर्ण,
	 .a_channels = 19,
	 .a = अणुअणु5180, 36पूर्ण,
	       अणु5200, 40पूर्ण,
	       अणु5220, 44पूर्ण,
	       अणु5240, 48पूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5500, 100, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5520, 104, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5540, 108, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5560, 112, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5580, 116, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5600, 120, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5620, 124, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5640, 128, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5660, 132, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5680, 136, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5700, 140, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom Japan */
	 "ZZJ",
	 .bg_channels = 14,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण, अणु2467, 12पूर्ण,
		अणु2472, 13पूर्ण, अणु2484, 14, LIBIPW_CH_B_ONLYपूर्णपूर्ण,
	 .a_channels = 4,
	 .a = अणुअणु5170, 34पूर्ण, अणु5190, 38पूर्ण,
	       अणु5210, 42पूर्ण, अणु5230, 46पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Rest of World */
	 "ZZR",
	 .bg_channels = 14,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण, अणु2467, 12पूर्ण,
		अणु2472, 13पूर्ण, अणु2484, 14, LIBIPW_CH_B_ONLY |
			     LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण,

	अणु			/* High Band */
	 "ZZH",
	 .bg_channels = 13,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण,
		अणु2467, 12, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
		अणु2472, 13, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 .a_channels = 4,
	 .a = अणुअणु5745, 149पूर्ण, अणु5765, 153पूर्ण,
	       अणु5785, 157पूर्ण, अणु5805, 161पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Custom Europe */
	 "ZZG",
	 .bg_channels = 13,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण,
		अणु2467, 12पूर्ण, अणु2472, 13पूर्णपूर्ण,
	 .a_channels = 4,
	 .a = अणुअणु5180, 36पूर्ण, अणु5200, 40पूर्ण,
	       अणु5220, 44पूर्ण, अणु5240, 48पूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Europe */
	 "ZZK",
	 .bg_channels = 13,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण,
		अणु2467, 12, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
		अणु2472, 13, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 .a_channels = 24,
	 .a = अणुअणु5180, 36, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5200, 40, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5220, 44, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5240, 48, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5500, 100, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5520, 104, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5540, 108, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5560, 112, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5580, 116, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5600, 120, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5620, 124, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5640, 128, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5660, 132, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5680, 136, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5700, 140, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5745, 149, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5765, 153, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5785, 157, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5805, 161, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5825, 165, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण,

	अणु			/* Europe */
	 "ZZL",
	 .bg_channels = 11,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्णपूर्ण,
	 .a_channels = 13,
	 .a = अणुअणु5180, 36, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5200, 40, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5220, 44, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5240, 48, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5260, 52, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5280, 56, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5300, 60, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5320, 64, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5745, 149, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5765, 153, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5785, 157, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5805, 161, LIBIPW_CH_PASSIVE_ONLYपूर्ण,
	       अणु5825, 165, LIBIPW_CH_PASSIVE_ONLYपूर्णपूर्ण,
	 पूर्ण
पूर्ण;

अटल व्योम ipw_set_geo(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < ARRAY_SIZE(ipw_geos); j++) अणु
		अगर (!स_भेद(&priv->eeprom[EEPROM_COUNTRY_CODE],
			    ipw_geos[j].name, 3))
			अवरोध;
	पूर्ण

	अगर (j == ARRAY_SIZE(ipw_geos)) अणु
		IPW_WARNING("SKU [%c%c%c] not recognized.\n",
			    priv->eeprom[EEPROM_COUNTRY_CODE + 0],
			    priv->eeprom[EEPROM_COUNTRY_CODE + 1],
			    priv->eeprom[EEPROM_COUNTRY_CODE + 2]);
		j = 0;
	पूर्ण

	libipw_set_geo(priv->ieee, &ipw_geos[j]);
पूर्ण

#घोषणा MAX_HW_RESTARTS 5
अटल पूर्णांक ipw_up(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc, i;

	/* Age scan list entries found beक्रमe suspend */
	अगर (priv->suspend_समय) अणु
		libipw_networks_age(priv->ieee, priv->suspend_समय);
		priv->suspend_समय = 0;
	पूर्ण

	अगर (priv->status & STATUS_EXIT_PENDING)
		वापस -EIO;

	अगर (cmdlog && !priv->cmdlog) अणु
		priv->cmdlog = kसुस्मृति(cmdlog, माप(*priv->cmdlog),
				       GFP_KERNEL);
		अगर (priv->cmdlog == शून्य) अणु
			IPW_ERROR("Error allocating %d command log entries.\n",
				  cmdlog);
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			priv->cmdlog_len = cmdlog;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_HW_RESTARTS; i++) अणु
		/* Load the microcode, firmware, and eeprom.
		 * Also start the घड़ीs. */
		rc = ipw_load(priv);
		अगर (rc) अणु
			IPW_ERROR("Unable to load firmware: %d\n", rc);
			वापस rc;
		पूर्ण

		ipw_init_ordinals(priv);
		अगर (!(priv->config & CFG_CUSTOM_MAC))
			eeprom_parse_mac(priv, priv->mac_addr);
		स_नकल(priv->net_dev->dev_addr, priv->mac_addr, ETH_ALEN);

		ipw_set_geo(priv);

		अगर (priv->status & STATUS_RF_KILL_SW) अणु
			IPW_WARNING("Radio disabled by module parameter.\n");
			वापस 0;
		पूर्ण अन्यथा अगर (rf_समाप्त_active(priv)) अणु
			IPW_WARNING("Radio Frequency Kill Switch is On:\n"
				    "Kill switch must be turned off for "
				    "wireless networking to work.\n");
			schedule_delayed_work(&priv->rf_समाप्त, 2 * HZ);
			वापस 0;
		पूर्ण

		rc = ipw_config(priv);
		अगर (!rc) अणु
			IPW_DEBUG_INFO("Configured device on count %i\n", i);

			/* If configure to try and स्वतः-associate, kick
			 * off a scan. */
			schedule_delayed_work(&priv->request_scan, 0);

			वापस 0;
		पूर्ण

		IPW_DEBUG_INFO("Device configuration failed: 0x%08X\n", rc);
		IPW_DEBUG_INFO("Failed to config device on retry %d of %d\n",
			       i, MAX_HW_RESTARTS);

		/* We had an error bringing up the hardware, so take it
		 * all the way back करोwn so we can try again */
		ipw_करोwn(priv);
	पूर्ण

	/* tried to restart and config the device क्रम as दीर्घ as our
	 * patience could withstand */
	IPW_ERROR("Unable to initialize device after %d attempts.\n", i);

	वापस -EIO;
पूर्ण

अटल व्योम ipw_bg_up(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, up);
	mutex_lock(&priv->mutex);
	ipw_up(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ipw_deinit(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक i;

	अगर (priv->status & STATUS_SCANNING) अणु
		IPW_DEBUG_INFO("Aborting scan during shutdown.\n");
		ipw_पात_scan(priv);
	पूर्ण

	अगर (priv->status & STATUS_ASSOCIATED) अणु
		IPW_DEBUG_INFO("Disassociating during shutdown.\n");
		ipw_disassociate(priv);
	पूर्ण

	ipw_led_shutकरोwn(priv);

	/* Wait up to 1s क्रम status to change to not scanning and not
	 * associated (disassociation can take a जबतक क्रम a ful 802.11
	 * exchange */
	क्रम (i = 1000; i && (priv->status &
			     (STATUS_DISASSOCIATING |
			      STATUS_ASSOCIATED | STATUS_SCANNING)); i--)
		udelay(10);

	अगर (priv->status & (STATUS_DISASSOCIATING |
			    STATUS_ASSOCIATED | STATUS_SCANNING))
		IPW_DEBUG_INFO("Still associated or scanning...\n");
	अन्यथा
		IPW_DEBUG_INFO("Took %dms to de-init\n", 1000 - i);

	/* Attempt to disable the card */
	ipw_send_card_disable(priv, 0);

	priv->status &= ~STATUS_INIT;
पूर्ण

अटल व्योम ipw_करोwn(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक निकास_pending = priv->status & STATUS_EXIT_PENDING;

	priv->status |= STATUS_EXIT_PENDING;

	अगर (ipw_is_init(priv))
		ipw_deinit(priv);

	/* Wipe out the EXIT_PENDING status bit अगर we are not actually
	 * निकासing the module */
	अगर (!निकास_pending)
		priv->status &= ~STATUS_EXIT_PENDING;

	/* tell the device to stop sending पूर्णांकerrupts */
	ipw_disable_पूर्णांकerrupts(priv);

	/* Clear all bits but the RF Kill */
	priv->status &= STATUS_RF_KILL_MASK | STATUS_EXIT_PENDING;
	netअगर_carrier_off(priv->net_dev);

	ipw_stop_nic(priv);

	ipw_led_radio_off(priv);
पूर्ण

अटल व्योम ipw_bg_करोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw_priv *priv =
		container_of(work, काष्ठा ipw_priv, करोwn);
	mutex_lock(&priv->mutex);
	ipw_करोwn(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ipw_wdev_init(काष्ठा net_device *dev)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा ipw_priv *priv = libipw_priv(dev);
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	काष्ठा wireless_dev *wdev = &priv->ieee->wdev;

	स_नकल(wdev->wiphy->perm_addr, priv->mac_addr, ETH_ALEN);

	/* fill-out priv->ieee->bg_band */
	अगर (geo->bg_channels) अणु
		काष्ठा ieee80211_supported_band *bg_band = &priv->ieee->bg_band;

		bg_band->band = NL80211_BAND_2GHZ;
		bg_band->n_channels = geo->bg_channels;
		bg_band->channels = kसुस्मृति(geo->bg_channels,
					    माप(काष्ठा ieee80211_channel),
					    GFP_KERNEL);
		अगर (!bg_band->channels) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		/* translate geo->bg to bg_band.channels */
		क्रम (i = 0; i < geo->bg_channels; i++) अणु
			bg_band->channels[i].band = NL80211_BAND_2GHZ;
			bg_band->channels[i].center_freq = geo->bg[i].freq;
			bg_band->channels[i].hw_value = geo->bg[i].channel;
			bg_band->channels[i].max_घातer = geo->bg[i].max_घातer;
			अगर (geo->bg[i].flags & LIBIPW_CH_PASSIVE_ONLY)
				bg_band->channels[i].flags |=
					IEEE80211_CHAN_NO_IR;
			अगर (geo->bg[i].flags & LIBIPW_CH_NO_IBSS)
				bg_band->channels[i].flags |=
					IEEE80211_CHAN_NO_IR;
			अगर (geo->bg[i].flags & LIBIPW_CH_RADAR_DETECT)
				bg_band->channels[i].flags |=
					IEEE80211_CHAN_RADAR;
			/* No equivalent क्रम LIBIPW_CH_80211H_RULES,
			   LIBIPW_CH_UNIFORM_SPREADING, or
			   LIBIPW_CH_B_ONLY... */
		पूर्ण
		/* poपूर्णांक at bitrate info */
		bg_band->bitrates = ipw2200_bg_rates;
		bg_band->n_bitrates = ipw2200_num_bg_rates;

		wdev->wiphy->bands[NL80211_BAND_2GHZ] = bg_band;
	पूर्ण

	/* fill-out priv->ieee->a_band */
	अगर (geo->a_channels) अणु
		काष्ठा ieee80211_supported_band *a_band = &priv->ieee->a_band;

		a_band->band = NL80211_BAND_5GHZ;
		a_band->n_channels = geo->a_channels;
		a_band->channels = kसुस्मृति(geo->a_channels,
					   माप(काष्ठा ieee80211_channel),
					   GFP_KERNEL);
		अगर (!a_band->channels) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		/* translate geo->a to a_band.channels */
		क्रम (i = 0; i < geo->a_channels; i++) अणु
			a_band->channels[i].band = NL80211_BAND_5GHZ;
			a_band->channels[i].center_freq = geo->a[i].freq;
			a_band->channels[i].hw_value = geo->a[i].channel;
			a_band->channels[i].max_घातer = geo->a[i].max_घातer;
			अगर (geo->a[i].flags & LIBIPW_CH_PASSIVE_ONLY)
				a_band->channels[i].flags |=
					IEEE80211_CHAN_NO_IR;
			अगर (geo->a[i].flags & LIBIPW_CH_NO_IBSS)
				a_band->channels[i].flags |=
					IEEE80211_CHAN_NO_IR;
			अगर (geo->a[i].flags & LIBIPW_CH_RADAR_DETECT)
				a_band->channels[i].flags |=
					IEEE80211_CHAN_RADAR;
			/* No equivalent क्रम LIBIPW_CH_80211H_RULES,
			   LIBIPW_CH_UNIFORM_SPREADING, or
			   LIBIPW_CH_B_ONLY... */
		पूर्ण
		/* poपूर्णांक at bitrate info */
		a_band->bitrates = ipw2200_a_rates;
		a_band->n_bitrates = ipw2200_num_a_rates;

		wdev->wiphy->bands[NL80211_BAND_5GHZ] = a_band;
	पूर्ण

	wdev->wiphy->cipher_suites = ipw_cipher_suites;
	wdev->wiphy->n_cipher_suites = ARRAY_SIZE(ipw_cipher_suites);

	set_wiphy_dev(wdev->wiphy, &priv->pci_dev->dev);

	/* With that inक्रमmation in place, we can now रेजिस्टर the wiphy... */
	अगर (wiphy_रेजिस्टर(wdev->wiphy))
		rc = -EIO;
out:
	वापस rc;
पूर्ण

/* PCI driver stuff */
अटल स्थिर काष्ठा pci_device_id card_ids[] = अणु
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2701, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2702, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2711, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2712, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2721, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2722, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2731, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2732, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2741, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x103c, 0x2741, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2742, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2751, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2752, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2753, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2754, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2761, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, 0x1043, 0x8086, 0x2762, 0, 0, 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, 0x104f), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, 0x4220), 0पूर्ण,	/* BG */
	अणुPCI_VDEVICE(INTEL, 0x4221), 0पूर्ण,	/* BG */
	अणुPCI_VDEVICE(INTEL, 0x4223), 0पूर्ण,	/* ABG */
	अणुPCI_VDEVICE(INTEL, 0x4224), 0पूर्ण,	/* ABG */

	/* required last entry */
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, card_ids);

अटल काष्ठा attribute *ipw_sysfs_entries[] = अणु
	&dev_attr_rf_समाप्त.attr,
	&dev_attr_direct_dword.attr,
	&dev_attr_indirect_byte.attr,
	&dev_attr_indirect_dword.attr,
	&dev_attr_mem_gpio_reg.attr,
	&dev_attr_command_event_reg.attr,
	&dev_attr_nic_type.attr,
	&dev_attr_status.attr,
	&dev_attr_cfg.attr,
	&dev_attr_error.attr,
	&dev_attr_event_log.attr,
	&dev_attr_cmd_log.attr,
	&dev_attr_eeprom_delay.attr,
	&dev_attr_ucode_version.attr,
	&dev_attr_rtc.attr,
	&dev_attr_scan_age.attr,
	&dev_attr_led.attr,
	&dev_attr_speed_scan.attr,
	&dev_attr_net_stats.attr,
	&dev_attr_channels.attr,
#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	&dev_attr_rtap_अगरace.attr,
	&dev_attr_rtap_filter.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ipw_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = ipw_sysfs_entries,
पूर्ण;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
अटल पूर्णांक ipw_prom_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipw_prom_priv *prom_priv = libipw_priv(dev);
	काष्ठा ipw_priv *priv = prom_priv->priv;

	IPW_DEBUG_INFO("prom dev->open\n");
	netअगर_carrier_off(dev);

	अगर (priv->ieee->iw_mode != IW_MODE_MONITOR) अणु
		priv->sys_config.accept_all_data_frames = 1;
		priv->sys_config.accept_non_directed_frames = 1;
		priv->sys_config.accept_all_mgmt_bcpr = 1;
		priv->sys_config.accept_all_mgmt_frames = 1;

		ipw_send_प्रणाली_config(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipw_prom_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ipw_prom_priv *prom_priv = libipw_priv(dev);
	काष्ठा ipw_priv *priv = prom_priv->priv;

	IPW_DEBUG_INFO("prom dev->stop\n");

	अगर (priv->ieee->iw_mode != IW_MODE_MONITOR) अणु
		priv->sys_config.accept_all_data_frames = 0;
		priv->sys_config.accept_non_directed_frames = 0;
		priv->sys_config.accept_all_mgmt_bcpr = 0;
		priv->sys_config.accept_all_mgmt_frames = 0;

		ipw_send_प्रणाली_config(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t ipw_prom_hard_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	IPW_DEBUG_INFO("prom dev->xmit\n");
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ipw_prom_netdev_ops = अणु
	.nकरो_खोलो 		= ipw_prom_खोलो,
	.nकरो_stop		= ipw_prom_stop,
	.nकरो_start_xmit		= ipw_prom_hard_start_xmit,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक ipw_prom_alloc(काष्ठा ipw_priv *priv)
अणु
	पूर्णांक rc = 0;

	अगर (priv->prom_net_dev)
		वापस -EPERM;

	priv->prom_net_dev = alloc_libipw(माप(काष्ठा ipw_prom_priv), 1);
	अगर (priv->prom_net_dev == शून्य)
		वापस -ENOMEM;

	priv->prom_priv = libipw_priv(priv->prom_net_dev);
	priv->prom_priv->ieee = netdev_priv(priv->prom_net_dev);
	priv->prom_priv->priv = priv;

	म_नकल(priv->prom_net_dev->name, "rtap%d");
	स_नकल(priv->prom_net_dev->dev_addr, priv->mac_addr, ETH_ALEN);

	priv->prom_net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
	priv->prom_net_dev->netdev_ops = &ipw_prom_netdev_ops;

	priv->prom_net_dev->min_mtu = 68;
	priv->prom_net_dev->max_mtu = LIBIPW_DATA_LEN;

	priv->prom_priv->ieee->iw_mode = IW_MODE_MONITOR;
	SET_NETDEV_DEV(priv->prom_net_dev, &priv->pci_dev->dev);

	rc = रेजिस्टर_netdev(priv->prom_net_dev);
	अगर (rc) अणु
		मुक्त_libipw(priv->prom_net_dev, 1);
		priv->prom_net_dev = शून्य;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipw_prom_मुक्त(काष्ठा ipw_priv *priv)
अणु
	अगर (!priv->prom_net_dev)
		वापस;

	unरेजिस्टर_netdev(priv->prom_net_dev);
	मुक्त_libipw(priv->prom_net_dev, 1);

	priv->prom_net_dev = शून्य;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops ipw_netdev_ops = अणु
	.nकरो_खोलो		= ipw_net_खोलो,
	.nकरो_stop		= ipw_net_stop,
	.nकरो_set_rx_mode	= ipw_net_set_multicast_list,
	.nकरो_set_mac_address	= ipw_net_set_mac_address,
	.nकरो_start_xmit		= libipw_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक ipw_pci_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = 0;
	काष्ठा net_device *net_dev;
	व्योम __iomem *base;
	u32 length, val;
	काष्ठा ipw_priv *priv;
	पूर्णांक i;

	net_dev = alloc_libipw(माप(काष्ठा ipw_priv), 0);
	अगर (net_dev == शून्य) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	priv = libipw_priv(net_dev);
	priv->ieee = netdev_priv(net_dev);

	priv->net_dev = net_dev;
	priv->pci_dev = pdev;
	ipw_debug_level = debug;
	spin_lock_init(&priv->irq_lock);
	spin_lock_init(&priv->lock);
	क्रम (i = 0; i < IPW_IBSS_MAC_HASH_SIZE; i++)
		INIT_LIST_HEAD(&priv->ibss_mac_hash[i]);

	mutex_init(&priv->mutex);
	अगर (pci_enable_device(pdev)) अणु
		err = -ENODEV;
		जाओ out_मुक्त_libipw;
	पूर्ण

	pci_set_master(pdev);

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (!err)
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": No suitable DMA available.\n");
		जाओ out_pci_disable_device;
	पूर्ण

	pci_set_drvdata(pdev, priv);

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ out_pci_disable_device;

	/* We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	length = pci_resource_len(pdev, 0);
	priv->hw_len = length;

	base = pci_ioremap_bar(pdev, 0);
	अगर (!base) अणु
		err = -ENODEV;
		जाओ out_pci_release_regions;
	पूर्ण

	priv->hw_base = base;
	IPW_DEBUG_INFO("pci_resource_len = 0x%08x\n", length);
	IPW_DEBUG_INFO("pci_resource_base = %p\n", base);

	ipw_setup_deferred_work(priv);

	ipw_sw_reset(priv, 1);

	err = request_irq(pdev->irq, ipw_isr, IRQF_SHARED, DRV_NAME, priv);
	अगर (err) अणु
		IPW_ERROR("Error allocating IRQ %d\n", pdev->irq);
		जाओ out_iounmap;
	पूर्ण

	SET_NETDEV_DEV(net_dev, &pdev->dev);

	mutex_lock(&priv->mutex);

	priv->ieee->hard_start_xmit = ipw_net_hard_start_xmit;
	priv->ieee->set_security = shim__set_security;
	priv->ieee->is_queue_full = ipw_net_is_queue_full;

#अगर_घोषित CONFIG_IPW2200_QOS
	priv->ieee->is_qos_active = ipw_is_qos_active;
	priv->ieee->handle_probe_response = ipw_handle_beacon;
	priv->ieee->handle_beacon = ipw_handle_probe_response;
	priv->ieee->handle_assoc_response = ipw_handle_assoc_response;
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

	priv->ieee->perfect_rssi = -20;
	priv->ieee->worst_rssi = -85;

	net_dev->netdev_ops = &ipw_netdev_ops;
	priv->wireless_data.spy_data = &priv->ieee->spy_data;
	net_dev->wireless_data = &priv->wireless_data;
	net_dev->wireless_handlers = &ipw_wx_handler_def;
	net_dev->ethtool_ops = &ipw_ethtool_ops;

	net_dev->min_mtu = 68;
	net_dev->max_mtu = LIBIPW_DATA_LEN;

	err = sysfs_create_group(&pdev->dev.kobj, &ipw_attribute_group);
	अगर (err) अणु
		IPW_ERROR("failed to create sysfs device attributes\n");
		mutex_unlock(&priv->mutex);
		जाओ out_release_irq;
	पूर्ण

	अगर (ipw_up(priv)) अणु
		mutex_unlock(&priv->mutex);
		err = -EIO;
		जाओ out_हटाओ_sysfs;
	पूर्ण

	mutex_unlock(&priv->mutex);

	err = ipw_wdev_init(net_dev);
	अगर (err) अणु
		IPW_ERROR("failed to register wireless device\n");
		जाओ out_हटाओ_sysfs;
	पूर्ण

	err = रेजिस्टर_netdev(net_dev);
	अगर (err) अणु
		IPW_ERROR("failed to register network device\n");
		जाओ out_unरेजिस्टर_wiphy;
	पूर्ण

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	अगर (rtap_अगरace) अणु
	        err = ipw_prom_alloc(priv);
		अगर (err) अणु
			IPW_ERROR("Failed to register promiscuous network "
				  "device (error %d).\n", err);
			unरेजिस्टर_netdev(priv->net_dev);
			जाओ out_unरेजिस्टर_wiphy;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO DRV_NAME ": Detected geography %s (%d 802.11bg "
	       "channels, %d 802.11a channels)\n",
	       priv->ieee->geo.name, priv->ieee->geo.bg_channels,
	       priv->ieee->geo.a_channels);

	वापस 0;

      out_unरेजिस्टर_wiphy:
	wiphy_unरेजिस्टर(priv->ieee->wdev.wiphy);
	kमुक्त(priv->ieee->a_band.channels);
	kमुक्त(priv->ieee->bg_band.channels);
      out_हटाओ_sysfs:
	sysfs_हटाओ_group(&pdev->dev.kobj, &ipw_attribute_group);
      out_release_irq:
	मुक्त_irq(pdev->irq, priv);
      out_iounmap:
	iounmap(priv->hw_base);
      out_pci_release_regions:
	pci_release_regions(pdev);
      out_pci_disable_device:
	pci_disable_device(pdev);
      out_मुक्त_libipw:
	मुक्त_libipw(priv->net_dev, 0);
      out:
	वापस err;
पूर्ण

अटल व्योम ipw_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ipw_priv *priv = pci_get_drvdata(pdev);
	काष्ठा list_head *p, *q;
	पूर्णांक i;

	अगर (!priv)
		वापस;

	mutex_lock(&priv->mutex);

	priv->status |= STATUS_EXIT_PENDING;
	ipw_करोwn(priv);
	sysfs_हटाओ_group(&pdev->dev.kobj, &ipw_attribute_group);

	mutex_unlock(&priv->mutex);

	unरेजिस्टर_netdev(priv->net_dev);

	अगर (priv->rxq) अणु
		ipw_rx_queue_मुक्त(priv, priv->rxq);
		priv->rxq = शून्य;
	पूर्ण
	ipw_tx_queue_मुक्त(priv);

	अगर (priv->cmdlog) अणु
		kमुक्त(priv->cmdlog);
		priv->cmdlog = शून्य;
	पूर्ण

	/* make sure all works are inactive */
	cancel_delayed_work_sync(&priv->adhoc_check);
	cancel_work_sync(&priv->associate);
	cancel_work_sync(&priv->disassociate);
	cancel_work_sync(&priv->प्रणाली_config);
	cancel_work_sync(&priv->rx_replenish);
	cancel_work_sync(&priv->adapter_restart);
	cancel_delayed_work_sync(&priv->rf_समाप्त);
	cancel_work_sync(&priv->up);
	cancel_work_sync(&priv->करोwn);
	cancel_delayed_work_sync(&priv->request_scan);
	cancel_delayed_work_sync(&priv->request_direct_scan);
	cancel_delayed_work_sync(&priv->request_passive_scan);
	cancel_delayed_work_sync(&priv->scan_event);
	cancel_delayed_work_sync(&priv->gather_stats);
	cancel_work_sync(&priv->पात_scan);
	cancel_work_sync(&priv->roam);
	cancel_delayed_work_sync(&priv->scan_check);
	cancel_work_sync(&priv->link_up);
	cancel_work_sync(&priv->link_करोwn);
	cancel_delayed_work_sync(&priv->led_link_on);
	cancel_delayed_work_sync(&priv->led_link_off);
	cancel_delayed_work_sync(&priv->led_act_off);
	cancel_work_sync(&priv->merge_networks);

	/* Free MAC hash list क्रम ADHOC */
	क्रम (i = 0; i < IPW_IBSS_MAC_HASH_SIZE; i++) अणु
		list_क्रम_each_safe(p, q, &priv->ibss_mac_hash[i]) अणु
			list_del(p);
			kमुक्त(list_entry(p, काष्ठा ipw_ibss_seq, list));
		पूर्ण
	पूर्ण

	kमुक्त(priv->error);
	priv->error = शून्य;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	ipw_prom_मुक्त(priv);
#पूर्ण_अगर

	मुक्त_irq(pdev->irq, priv);
	iounmap(priv->hw_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	/* wiphy_unरेजिस्टर needs to be here, beक्रमe मुक्त_libipw */
	wiphy_unरेजिस्टर(priv->ieee->wdev.wiphy);
	kमुक्त(priv->ieee->a_band.channels);
	kमुक्त(priv->ieee->bg_band.channels);
	मुक्त_libipw(priv->net_dev, 0);
	मुक्त_firmware();
पूर्ण

अटल पूर्णांक __maybe_unused ipw_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा ipw_priv *priv = dev_get_drvdata(dev_d);
	काष्ठा net_device *dev = priv->net_dev;

	prपूर्णांकk(KERN_INFO "%s: Going into suspend...\n", dev->name);

	/* Take करोwn the device; घातers it off, etc. */
	ipw_करोwn(priv);

	/* Remove the PRESENT state of the device */
	netअगर_device_detach(dev);

	priv->suspend_at = kसमय_get_bootसमय_seconds();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ipw_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा ipw_priv *priv = pci_get_drvdata(pdev);
	काष्ठा net_device *dev = priv->net_dev;
	u32 val;

	prपूर्णांकk(KERN_INFO "%s: Coming out of suspend...\n", dev->name);

	/*
	 * Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep PCI Tx retries
	 * from पूर्णांकerfering with C3 CPU state. pci_restore_state won't help
	 * here since it only restores the first 64 bytes pci config header.
	 */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	/* Set the device back पूर्णांकo the PRESENT state; this will also wake
	 * the queue of needed */
	netअगर_device_attach(dev);

	priv->suspend_समय = kसमय_get_bootसमय_seconds() - priv->suspend_at;

	/* Bring the device back up */
	schedule_work(&priv->up);

	वापस 0;
पूर्ण

अटल व्योम ipw_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ipw_priv *priv = pci_get_drvdata(pdev);

	/* Take करोwn the device; घातers it off, etc. */
	ipw_करोwn(priv);

	pci_disable_device(pdev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ipw_pci_pm_ops, ipw_pci_suspend, ipw_pci_resume);

/* driver initialization stuff */
अटल काष्ठा pci_driver ipw_driver = अणु
	.name = DRV_NAME,
	.id_table = card_ids,
	.probe = ipw_pci_probe,
	.हटाओ = ipw_pci_हटाओ,
	.driver.pm = &ipw_pci_pm_ops,
	.shutकरोwn = ipw_pci_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init ipw_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO DRV_NAME ": " DRV_DESCRIPTION ", " DRV_VERSION "\n");
	prपूर्णांकk(KERN_INFO DRV_NAME ": " DRV_COPYRIGHT "\n");

	ret = pci_रेजिस्टर_driver(&ipw_driver);
	अगर (ret) अणु
		IPW_ERROR("Unable to initialize PCI module\n");
		वापस ret;
	पूर्ण

	ret = driver_create_file(&ipw_driver.driver, &driver_attr_debug_level);
	अगर (ret) अणु
		IPW_ERROR("Unable to create driver sysfs file\n");
		pci_unरेजिस्टर_driver(&ipw_driver);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास ipw_निकास(व्योम)
अणु
	driver_हटाओ_file(&ipw_driver.driver, &driver_attr_debug_level);
	pci_unरेजिस्टर_driver(&ipw_driver);
पूर्ण

module_param(disable, पूर्णांक, 0444);
MODULE_PARM_DESC(disable, "manually disable the radio (default 0 [radio on])");

module_param(associate, पूर्णांक, 0444);
MODULE_PARM_DESC(associate, "auto associate when scanning (default off)");

module_param(स्वतः_create, पूर्णांक, 0444);
MODULE_PARM_DESC(स्वतः_create, "auto create adhoc network (default on)");

module_param_named(led, led_support, पूर्णांक, 0444);
MODULE_PARM_DESC(led, "enable led control on some systems (default 1 on)");

module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "debug output mask");

module_param_named(channel, शेष_channel, पूर्णांक, 0444);
MODULE_PARM_DESC(channel, "channel to limit associate to (default 0 [ANY])");

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
module_param(rtap_अगरace, पूर्णांक, 0444);
MODULE_PARM_DESC(rtap_अगरace, "create the rtap interface (1 - create, default 0)");
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPW2200_QOS
module_param(qos_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(qos_enable, "enable all QoS functionalities");

module_param(qos_burst_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(qos_burst_enable, "enable QoS burst mode");

module_param(qos_no_ack_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(qos_no_ack_mask, "mask Tx_Queue to no ack");

module_param(burst_duration_CCK, पूर्णांक, 0444);
MODULE_PARM_DESC(burst_duration_CCK, "set CCK burst value");

module_param(burst_duration_OFDM, पूर्णांक, 0444);
MODULE_PARM_DESC(burst_duration_OFDM, "set OFDM burst value");
#पूर्ण_अगर				/* CONFIG_IPW2200_QOS */

#अगर_घोषित CONFIG_IPW2200_MONITOR
module_param_named(mode, network_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(mode, "network mode (0=BSS,1=IBSS,2=Monitor)");
#अन्यथा
module_param_named(mode, network_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(mode, "network mode (0=BSS,1=IBSS)");
#पूर्ण_अगर

module_param(bt_coexist, पूर्णांक, 0444);
MODULE_PARM_DESC(bt_coexist, "enable bluetooth coexistence (default off)");

module_param(hwcrypto, पूर्णांक, 0444);
MODULE_PARM_DESC(hwcrypto, "enable hardware crypto (default off)");

module_param(cmdlog, पूर्णांक, 0444);
MODULE_PARM_DESC(cmdlog,
		 "allocate a ring buffer for logging firmware commands");

module_param(roaming, पूर्णांक, 0444);
MODULE_PARM_DESC(roaming, "enable roaming support (default on)");

module_param(antenna, पूर्णांक, 0444);
MODULE_PARM_DESC(antenna, "select antenna 1=Main, 3=Aux, default 0 [both], 2=slow_diversity (choose the one with lower background noise)");

module_निकास(ipw_निकास);
module_init(ipw_init);
