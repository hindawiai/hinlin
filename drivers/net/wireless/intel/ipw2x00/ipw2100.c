<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

  Copyright(c) 2003 - 2006 Intel Corporation. All rights reserved.


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

  Portions of this file are based on the sample_* files provided by Wireless
  Extensions 0.26 package and copyright (c) 1997-2003 Jean Tourrilhes
  <jt@hpl.hp.com>

  Portions of this file are based on the Host AP project,
  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
    <j@w1.fi>
  Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>

  Portions of ipw2100_mod_firmware_load, ipw2100_करो_mod_firmware_load, and
  ipw2100_fw_load are loosely based on drivers/sound/sound_firmware.c
  available in the 2.4.25 kernel sources, and are copyright (c) Alan Cox

******************************************************************************/
/*

 Initial driver on which this is based was developed by Janusz Gorycki,
 Maciej Urbaniak, and Maciej Sosnowski.

 Promiscuous mode support added by Jacek Wysoczynski and Maciej Urbaniak.

Theory of Operation

Tx - Commands and Data

Firmware and host share a circular queue of Transmit Buffer Descriptors (TBDs)
Each TBD contains a poपूर्णांकer to the physical (dma_addr_t) address of data being
sent to the firmware as well as the length of the data.

The host ग_लिखोs to the TBD queue at the WRITE index.  The WRITE index poपूर्णांकs
to the _next_ packet to be written and is advanced when after the TBD has been
filled.

The firmware pulls from the TBD queue at the READ index.  The READ index poपूर्णांकs
to the currently being पढ़ो entry, and is advanced once the firmware is
करोne with a packet.

When data is sent to the firmware, the first TBD is used to indicate to the
firmware अगर a Command or Data is being sent.  If it is Command, all of the
command inक्रमmation is contained within the physical address referred to by the
TBD.  If it is Data, the first TBD indicates the type of data packet, number
of fragments, etc.  The next TBD then refers to the actual packet location.

The Tx flow cycle is as follows:

1) ipw2100_tx() is called by kernel with SKB to transmit
2) Packet is move from the tx_मुक्त_list and appended to the transmit pending
   list (tx_pend_list)
3) work is scheduled to move pending packets पूर्णांकo the shared circular queue.
4) when placing packet in the circular queue, the incoming SKB is DMA mapped
   to a physical address.  That address is entered पूर्णांकo a TBD.  Two TBDs are
   filled out.  The first indicating a data packet, the second referring to the
   actual payload data.
5) the packet is हटाओd from tx_pend_list and placed on the end of the
   firmware pending list (fw_pend_list)
6) firmware is notअगरied that the WRITE index has
7) Once the firmware has processed the TBD, INTA is triggered.
8) For each Tx पूर्णांकerrupt received from the firmware, the READ index is checked
   to see which TBDs are करोne being processed.
9) For each TBD that has been processed, the ISR pulls the oldest packet
   from the fw_pend_list.
10)The packet काष्ठाure contained in the fw_pend_list is then used
   to unmap the DMA address and to मुक्त the SKB originally passed to the driver
   from the kernel.
11)The packet काष्ठाure is placed onto the tx_मुक्त_list

The above steps are the same क्रम commands, only the msg_मुक्त_list/msg_pend_list
are used instead of tx_मुक्त_list/tx_pend_list

...

Critical Sections / Locking :

There are two locks utilized.  The first is the low level lock (priv->low_lock)
that protects the following:

- Access to the Tx/Rx queue lists via priv->low_lock. The lists are as follows:

  tx_मुक्त_list : Holds pre-allocated Tx buffers.
    TAIL modअगरied in __ipw2100_tx_process()
    HEAD modअगरied in ipw2100_tx()

  tx_pend_list : Holds used Tx buffers रुकोing to go पूर्णांकo the TBD ring
    TAIL modअगरied ipw2100_tx()
    HEAD modअगरied by ipw2100_tx_send_data()

  msg_मुक्त_list : Holds pre-allocated Msg (Command) buffers
    TAIL modअगरied in __ipw2100_tx_process()
    HEAD modअगरied in ipw2100_hw_send_command()

  msg_pend_list : Holds used Msg buffers रुकोing to go पूर्णांकo the TBD ring
    TAIL modअगरied in ipw2100_hw_send_command()
    HEAD modअगरied in ipw2100_tx_send_commands()

  The flow of data on the TX side is as follows:

  MSG_FREE_LIST + COMMAND => MSG_PEND_LIST => TBD => MSG_FREE_LIST
  TX_FREE_LIST + DATA => TX_PEND_LIST => TBD => TX_FREE_LIST

  The methods that work on the TBD ring are रक्षित via priv->low_lock.

- The पूर्णांकernal data state of the device itself
- Access to the firmware पढ़ो/ग_लिखो indexes क्रम the BD queues
  and associated logic

All बाह्यal entry functions are locked with the priv->action_lock to ensure
that only one बाह्यal action is invoked at a समय.


*/

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/unistd.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/firmware.h>
#समावेश <linux/acpi.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pm_qos.h>

#समावेश <net/lib80211.h>

#समावेश "ipw2100.h"
#समावेश "ipw.h"

#घोषणा IPW2100_VERSION "git-1.2.2"

#घोषणा DRV_NAME	"ipw2100"
#घोषणा DRV_VERSION	IPW2100_VERSION
#घोषणा DRV_DESCRIPTION	"Intel(R) PRO/Wireless 2100 Network Driver"
#घोषणा DRV_COPYRIGHT	"Copyright(c) 2003-2006 Intel Corporation"

अटल काष्ठा pm_qos_request ipw2100_pm_qos_req;

/* Debugging stuff */
#अगर_घोषित CONFIG_IPW2100_DEBUG
#घोषणा IPW2100_RX_DEBUG	/* Reception debugging */
#पूर्ण_अगर

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_COPYRIGHT);
MODULE_LICENSE("GPL");

अटल पूर्णांक debug = 0;
अटल पूर्णांक network_mode = 0;
अटल पूर्णांक channel = 0;
अटल पूर्णांक associate = 0;
अटल पूर्णांक disable = 0;
#अगर_घोषित CONFIG_PM
अटल काष्ठा ipw2100_fw ipw2100_firmware;
#पूर्ण_अगर

#समावेश <linux/moduleparam.h>
module_param(debug, पूर्णांक, 0444);
module_param_named(mode, network_mode, पूर्णांक, 0444);
module_param(channel, पूर्णांक, 0444);
module_param(associate, पूर्णांक, 0444);
module_param(disable, पूर्णांक, 0444);

MODULE_PARM_DESC(debug, "debug level");
MODULE_PARM_DESC(mode, "network mode (0=BSS,1=IBSS,2=Monitor)");
MODULE_PARM_DESC(channel, "channel");
MODULE_PARM_DESC(associate, "auto associate when scanning (default off)");
MODULE_PARM_DESC(disable, "manually disable the radio (default 0 [radio on])");

अटल u32 ipw2100_debug_level = IPW_DL_NONE;

#अगर_घोषित CONFIG_IPW2100_DEBUG
#घोषणा IPW_DEBUG(level, message...) \
करो अणु \
	अगर (ipw2100_debug_level & (level)) अणु \
		prपूर्णांकk(KERN_DEBUG "ipw2100: %s ", __func__); \
		prपूर्णांकk(message); \
	पूर्ण \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा IPW_DEBUG(level, message...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_IPW2100_DEBUG */

#अगर_घोषित CONFIG_IPW2100_DEBUG
अटल स्थिर अक्षर *command_types[] = अणु
	"undefined",
	"unused",		/* HOST_ATTENTION */
	"HOST_COMPLETE",
	"unused",		/* SLEEP */
	"unused",		/* HOST_POWER_DOWN */
	"unused",
	"SYSTEM_CONFIG",
	"unused",		/* SET_IMR */
	"SSID",
	"MANDATORY_BSSID",
	"AUTHENTICATION_TYPE",
	"ADAPTER_ADDRESS",
	"PORT_TYPE",
	"INTERNATIONAL_MODE",
	"CHANNEL",
	"RTS_THRESHOLD",
	"FRAG_THRESHOLD",
	"POWER_MODE",
	"TX_RATES",
	"BASIC_TX_RATES",
	"WEP_KEY_INFO",
	"unused",
	"unused",
	"unused",
	"unused",
	"WEP_KEY_INDEX",
	"WEP_FLAGS",
	"ADD_MULTICAST",
	"CLEAR_ALL_MULTICAST",
	"BEACON_INTERVAL",
	"ATIM_WINDOW",
	"CLEAR_STATISTICS",
	"undefined",
	"undefined",
	"undefined",
	"undefined",
	"TX_POWER_INDEX",
	"undefined",
	"undefined",
	"undefined",
	"undefined",
	"undefined",
	"undefined",
	"BROADCAST_SCAN",
	"CARD_DISABLE",
	"PREFERRED_BSSID",
	"SET_SCAN_OPTIONS",
	"SCAN_DWELL_TIME",
	"SWEEP_TABLE",
	"AP_OR_STATION_TABLE",
	"GROUP_ORDINALS",
	"SHORT_RETRY_LIMIT",
	"LONG_RETRY_LIMIT",
	"unused",		/* SAVE_CALIBRATION */
	"unused",		/* RESTORE_CALIBRATION */
	"undefined",
	"undefined",
	"undefined",
	"HOST_PRE_POWER_DOWN",
	"unused",		/* HOST_INTERRUPT_COALESCING */
	"undefined",
	"CARD_DISABLE_PHY_OFF",
	"MSDU_TX_RATES",
	"undefined",
	"SET_STATION_STAT_BITS",
	"CLEAR_STATIONS_STAT_BITS",
	"LEAP_ROGUE_MODE",
	"SET_SECURITY_INFORMATION",
	"DISASSOCIATION_BSSID",
	"SET_WPA_ASS_IE"
पूर्ण;
#पूर्ण_अगर

अटल स्थिर दीर्घ ipw2100_frequencies[] = अणु
	2412, 2417, 2422, 2427,
	2432, 2437, 2442, 2447,
	2452, 2457, 2462, 2467,
	2472, 2484
पूर्ण;

#घोषणा FREQ_COUNT	ARRAY_SIZE(ipw2100_frequencies)

अटल काष्ठा ieee80211_rate ipw2100_bg_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
पूर्ण;

#घोषणा RATE_COUNT ARRAY_SIZE(ipw2100_bg_rates)

/* Pre-decl until we get the code solid and then we can clean it up */
अटल व्योम ipw2100_tx_send_commands(काष्ठा ipw2100_priv *priv);
अटल व्योम ipw2100_tx_send_data(काष्ठा ipw2100_priv *priv);
अटल पूर्णांक ipw2100_adapter_setup(काष्ठा ipw2100_priv *priv);

अटल व्योम ipw2100_queues_initialize(काष्ठा ipw2100_priv *priv);
अटल व्योम ipw2100_queues_मुक्त(काष्ठा ipw2100_priv *priv);
अटल पूर्णांक ipw2100_queues_allocate(काष्ठा ipw2100_priv *priv);

अटल पूर्णांक ipw2100_fw_करोwnload(काष्ठा ipw2100_priv *priv,
			       काष्ठा ipw2100_fw *fw);
अटल पूर्णांक ipw2100_get_firmware(काष्ठा ipw2100_priv *priv,
				काष्ठा ipw2100_fw *fw);
अटल पूर्णांक ipw2100_get_fwversion(काष्ठा ipw2100_priv *priv, अक्षर *buf,
				 माप_प्रकार max);
अटल पूर्णांक ipw2100_get_ucodeversion(काष्ठा ipw2100_priv *priv, अक्षर *buf,
				    माप_प्रकार max);
अटल व्योम ipw2100_release_firmware(काष्ठा ipw2100_priv *priv,
				     काष्ठा ipw2100_fw *fw);
अटल पूर्णांक ipw2100_ucode_करोwnload(काष्ठा ipw2100_priv *priv,
				  काष्ठा ipw2100_fw *fw);
अटल व्योम ipw2100_wx_event_work(काष्ठा work_काष्ठा *work);
अटल काष्ठा iw_statistics *ipw2100_wx_wireless_stats(काष्ठा net_device *dev);
अटल स्थिर काष्ठा iw_handler_def ipw2100_wx_handler_def;

अटल अंतरभूत व्योम पढ़ो_रेजिस्टर(काष्ठा net_device *dev, u32 reg, u32 * val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	*val = ioपढ़ो32(priv->ioaddr + reg);
	IPW_DEBUG_IO("r: 0x%08X => 0x%08X\n", reg, *val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_रेजिस्टर(काष्ठा net_device *dev, u32 reg, u32 val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	ioग_लिखो32(val, priv->ioaddr + reg);
	IPW_DEBUG_IO("w: 0x%08X <= 0x%08X\n", reg, val);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_रेजिस्टर_word(काष्ठा net_device *dev, u32 reg,
				      u16 * val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	*val = ioपढ़ो16(priv->ioaddr + reg);
	IPW_DEBUG_IO("r: 0x%08X => %04X\n", reg, *val);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_रेजिस्टर_byte(काष्ठा net_device *dev, u32 reg, u8 * val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	*val = ioपढ़ो8(priv->ioaddr + reg);
	IPW_DEBUG_IO("r: 0x%08X => %02X\n", reg, *val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_रेजिस्टर_word(काष्ठा net_device *dev, u32 reg, u16 val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	ioग_लिखो16(val, priv->ioaddr + reg);
	IPW_DEBUG_IO("w: 0x%08X <= %04X\n", reg, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_रेजिस्टर_byte(काष्ठा net_device *dev, u32 reg, u8 val)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	ioग_लिखो8(val, priv->ioaddr + reg);
	IPW_DEBUG_IO("w: 0x%08X =< %02X\n", reg, val);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_nic_dword(काष्ठा net_device *dev, u32 addr, u32 * val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	पढ़ो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_nic_dword(काष्ठा net_device *dev, u32 addr, u32 val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_nic_word(काष्ठा net_device *dev, u32 addr, u16 * val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	पढ़ो_रेजिस्टर_word(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_nic_word(काष्ठा net_device *dev, u32 addr, u16 val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	ग_लिखो_रेजिस्टर_word(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_nic_byte(काष्ठा net_device *dev, u32 addr, u8 * val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	पढ़ो_रेजिस्टर_byte(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_nic_byte(काष्ठा net_device *dev, u32 addr, u8 val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
	ग_लिखो_रेजिस्टर_byte(dev, IPW_REG_INसूचीECT_ACCESS_DATA, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_nic_स्वतः_inc_address(काष्ठा net_device *dev, u32 addr)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_ADDRESS,
		       addr & IPW_REG_INसूचीECT_ADDR_MASK);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_nic_dword_स्वतः_inc(काष्ठा net_device *dev, u32 val)
अणु
	ग_लिखो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_DATA, val);
पूर्ण

अटल व्योम ग_लिखो_nic_memory(काष्ठा net_device *dev, u32 addr, u32 len,
				    स्थिर u8 * buf)
अणु
	u32 aligned_addr;
	u32 aligned_len;
	u32 dअगर_len;
	u32 i;

	/* पढ़ो first nibble byte by byte */
	aligned_addr = addr & (~0x3);
	dअगर_len = addr - aligned_addr;
	अगर (dअगर_len) अणु
		/* Start पढ़ोing at aligned_addr + dअगर_len */
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
			       aligned_addr);
		क्रम (i = dअगर_len; i < 4; i++, buf++)
			ग_लिखो_रेजिस्टर_byte(dev,
					    IPW_REG_INसूचीECT_ACCESS_DATA + i,
					    *buf);

		len -= dअगर_len;
		aligned_addr += 4;
	पूर्ण

	/* पढ़ो DWs through स्वतःincrement रेजिस्टरs */
	ग_लिखो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_ADDRESS, aligned_addr);
	aligned_len = len & (~0x3);
	क्रम (i = 0; i < aligned_len; i += 4, buf += 4, aligned_addr += 4)
		ग_लिखो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_DATA, *(u32 *) buf);

	/* copy the last nibble */
	dअगर_len = len - aligned_len;
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS, aligned_addr);
	क्रम (i = 0; i < dअगर_len; i++, buf++)
		ग_लिखो_रेजिस्टर_byte(dev, IPW_REG_INसूचीECT_ACCESS_DATA + i,
				    *buf);
पूर्ण

अटल व्योम पढ़ो_nic_memory(काष्ठा net_device *dev, u32 addr, u32 len,
				   u8 * buf)
अणु
	u32 aligned_addr;
	u32 aligned_len;
	u32 dअगर_len;
	u32 i;

	/* पढ़ो first nibble byte by byte */
	aligned_addr = addr & (~0x3);
	dअगर_len = addr - aligned_addr;
	अगर (dअगर_len) अणु
		/* Start पढ़ोing at aligned_addr + dअगर_len */
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS,
			       aligned_addr);
		क्रम (i = dअगर_len; i < 4; i++, buf++)
			पढ़ो_रेजिस्टर_byte(dev,
					   IPW_REG_INसूचीECT_ACCESS_DATA + i,
					   buf);

		len -= dअगर_len;
		aligned_addr += 4;
	पूर्ण

	/* पढ़ो DWs through स्वतःincrement रेजिस्टरs */
	ग_लिखो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_ADDRESS, aligned_addr);
	aligned_len = len & (~0x3);
	क्रम (i = 0; i < aligned_len; i += 4, buf += 4, aligned_addr += 4)
		पढ़ो_रेजिस्टर(dev, IPW_REG_AUTOINCREMENT_DATA, (u32 *) buf);

	/* copy the last nibble */
	dअगर_len = len - aligned_len;
	ग_लिखो_रेजिस्टर(dev, IPW_REG_INसूचीECT_ACCESS_ADDRESS, aligned_addr);
	क्रम (i = 0; i < dअगर_len; i++, buf++)
		पढ़ो_रेजिस्टर_byte(dev, IPW_REG_INसूचीECT_ACCESS_DATA + i, buf);
पूर्ण

अटल bool ipw2100_hw_is_adapter_in_प्रणाली(काष्ठा net_device *dev)
अणु
	u32 dbg;

	पढ़ो_रेजिस्टर(dev, IPW_REG_DOA_DEBUG_AREA_START, &dbg);

	वापस dbg == IPW_DATA_DOA_DEBUG_VALUE;
पूर्ण

अटल पूर्णांक ipw2100_get_ordinal(काष्ठा ipw2100_priv *priv, u32 ord,
			       व्योम *val, u32 * len)
अणु
	काष्ठा ipw2100_ordinals *ordinals = &priv->ordinals;
	u32 addr;
	u32 field_info;
	u16 field_len;
	u16 field_count;
	u32 total_length;

	अगर (ordinals->table1_addr == 0) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": attempt to use fw ordinals "
		       "before they have been loaded.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ORDINAL_TABLE_ONE(ordinals, ord)) अणु
		अगर (*len < IPW_ORD_TAB_1_ENTRY_SIZE) अणु
			*len = IPW_ORD_TAB_1_ENTRY_SIZE;

			prपूर्णांकk(KERN_WARNING DRV_NAME
			       ": ordinal buffer length too small, need %zd\n",
			       IPW_ORD_TAB_1_ENTRY_SIZE);

			वापस -EINVAL;
		पूर्ण

		पढ़ो_nic_dword(priv->net_dev,
			       ordinals->table1_addr + (ord << 2), &addr);
		पढ़ो_nic_dword(priv->net_dev, addr, val);

		*len = IPW_ORD_TAB_1_ENTRY_SIZE;

		वापस 0;
	पूर्ण

	अगर (IS_ORDINAL_TABLE_TWO(ordinals, ord)) अणु

		ord -= IPW_START_ORD_TAB_2;

		/* get the address of statistic */
		पढ़ो_nic_dword(priv->net_dev,
			       ordinals->table2_addr + (ord << 3), &addr);

		/* get the second DW of statistics ;
		 * two 16-bit words - first is length, second is count */
		पढ़ो_nic_dword(priv->net_dev,
			       ordinals->table2_addr + (ord << 3) + माप(u32),
			       &field_info);

		/* get each entry length */
		field_len = *((u16 *) & field_info);

		/* get number of entries */
		field_count = *(((u16 *) & field_info) + 1);

		/* पात अगर no enough memory */
		total_length = field_len * field_count;
		अगर (total_length > *len) अणु
			*len = total_length;
			वापस -EINVAL;
		पूर्ण

		*len = total_length;
		अगर (!total_length)
			वापस 0;

		/* पढ़ो the ordinal data from the SRAM */
		पढ़ो_nic_memory(priv->net_dev, addr, total_length, val);

		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_WARNING DRV_NAME ": ordinal %d neither in table 1 nor "
	       "in table 2\n", ord);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ipw2100_set_ordinal(काष्ठा ipw2100_priv *priv, u32 ord, u32 * val,
			       u32 * len)
अणु
	काष्ठा ipw2100_ordinals *ordinals = &priv->ordinals;
	u32 addr;

	अगर (IS_ORDINAL_TABLE_ONE(ordinals, ord)) अणु
		अगर (*len != IPW_ORD_TAB_1_ENTRY_SIZE) अणु
			*len = IPW_ORD_TAB_1_ENTRY_SIZE;
			IPW_DEBUG_INFO("wrong size\n");
			वापस -EINVAL;
		पूर्ण

		पढ़ो_nic_dword(priv->net_dev,
			       ordinals->table1_addr + (ord << 2), &addr);

		ग_लिखो_nic_dword(priv->net_dev, addr, *val);

		*len = IPW_ORD_TAB_1_ENTRY_SIZE;

		वापस 0;
	पूर्ण

	IPW_DEBUG_INFO("wrong table\n");
	अगर (IS_ORDINAL_TABLE_TWO(ordinals, ord))
		वापस -EINVAL;

	वापस -EINVAL;
पूर्ण

अटल अक्षर *snprपूर्णांक_line(अक्षर *buf, माप_प्रकार count,
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

	वापस buf;
पूर्ण

अटल व्योम prपूर्णांकk_buf(पूर्णांक level, स्थिर u8 * data, u32 len)
अणु
	अक्षर line[81];
	u32 ofs = 0;
	अगर (!(ipw2100_debug_level & level))
		वापस;

	जबतक (len) अणु
		prपूर्णांकk(KERN_DEBUG "%s\n",
		       snprपूर्णांक_line(line, माप(line), &data[ofs],
				    min(len, 16U), ofs));
		ofs += 16;
		len -= min(len, 16U);
	पूर्ण
पूर्ण

#घोषणा MAX_RESET_BACKOFF 10

अटल व्योम schedule_reset(काष्ठा ipw2100_priv *priv)
अणु
	समय64_t now = kसमय_get_bootसमय_seconds();

	/* If we haven't received a reset request within the backoff period,
	 * then we can reset the backoff पूर्णांकerval so this reset occurs
	 * immediately */
	अगर (priv->reset_backoff &&
	    (now - priv->last_reset > priv->reset_backoff))
		priv->reset_backoff = 0;

	priv->last_reset = now;

	अगर (!(priv->status & STATUS_RESET_PENDING)) अणु
		IPW_DEBUG_INFO("%s: Scheduling firmware restart (%llds).\n",
			       priv->net_dev->name, priv->reset_backoff);
		netअगर_carrier_off(priv->net_dev);
		netअगर_stop_queue(priv->net_dev);
		priv->status |= STATUS_RESET_PENDING;
		अगर (priv->reset_backoff)
			schedule_delayed_work(&priv->reset_work,
					      priv->reset_backoff * HZ);
		अन्यथा
			schedule_delayed_work(&priv->reset_work, 0);

		अगर (priv->reset_backoff < MAX_RESET_BACKOFF)
			priv->reset_backoff++;

		wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);
	पूर्ण अन्यथा
		IPW_DEBUG_INFO("%s: Firmware restart already in progress.\n",
			       priv->net_dev->name);

पूर्ण

#घोषणा HOST_COMPLETE_TIMEOUT (2 * HZ)
अटल पूर्णांक ipw2100_hw_send_command(काष्ठा ipw2100_priv *priv,
				   काष्ठा host_command *cmd)
अणु
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	IPW_DEBUG_HC("Sending %s command (#%d), %d bytes\n",
		     command_types[cmd->host_command], cmd->host_command,
		     cmd->host_command_length);
	prपूर्णांकk_buf(IPW_DL_HC, (u8 *) cmd->host_command_parameters,
		   cmd->host_command_length);

	spin_lock_irqsave(&priv->low_lock, flags);

	अगर (priv->fatal_error) अणु
		IPW_DEBUG_INFO
		    ("Attempt to send command while hardware in fatal error condition.\n");
		err = -EIO;
		जाओ fail_unlock;
	पूर्ण

	अगर (!(priv->status & STATUS_RUNNING)) अणु
		IPW_DEBUG_INFO
		    ("Attempt to send command while hardware is not running.\n");
		err = -EIO;
		जाओ fail_unlock;
	पूर्ण

	अगर (priv->status & STATUS_CMD_ACTIVE) अणु
		IPW_DEBUG_INFO
		    ("Attempt to send command while another command is pending.\n");
		err = -EBUSY;
		जाओ fail_unlock;
	पूर्ण

	अगर (list_empty(&priv->msg_मुक्त_list)) अणु
		IPW_DEBUG_INFO("no available msg buffers\n");
		जाओ fail_unlock;
	पूर्ण

	priv->status |= STATUS_CMD_ACTIVE;
	priv->messages_sent++;

	element = priv->msg_मुक्त_list.next;

	packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);
	packet->jअगरfy_start = jअगरfies;

	/* initialize the firmware command packet */
	packet->info.c_काष्ठा.cmd->host_command_reg = cmd->host_command;
	packet->info.c_काष्ठा.cmd->host_command_reg1 = cmd->host_command1;
	packet->info.c_काष्ठा.cmd->host_command_len_reg =
	    cmd->host_command_length;
	packet->info.c_काष्ठा.cmd->sequence = cmd->host_command_sequence;

	स_नकल(packet->info.c_काष्ठा.cmd->host_command_params_reg,
	       cmd->host_command_parameters,
	       माप(packet->info.c_काष्ठा.cmd->host_command_params_reg));

	list_del(element);
	DEC_STAT(&priv->msg_मुक्त_stat);

	list_add_tail(element, &priv->msg_pend_list);
	INC_STAT(&priv->msg_pend_stat);

	ipw2100_tx_send_commands(priv);
	ipw2100_tx_send_data(priv);

	spin_unlock_irqrestore(&priv->low_lock, flags);

	/*
	 * We must रुको क्रम this command to complete beक्रमe another
	 * command can be sent...  but अगर we रुको more than 3 seconds
	 * then there is a problem.
	 */

	err =
	    रुको_event_पूर्णांकerruptible_समयout(priv->रुको_command_queue,
					     !(priv->
					       status & STATUS_CMD_ACTIVE),
					     HOST_COMPLETE_TIMEOUT);

	अगर (err == 0) अणु
		IPW_DEBUG_INFO("Command completion failed out after %dms.\n",
			       1000 * (HOST_COMPLETE_TIMEOUT / HZ));
		priv->fatal_error = IPW2100_ERR_MSG_TIMEOUT;
		priv->status &= ~STATUS_CMD_ACTIVE;
		schedule_reset(priv);
		वापस -EIO;
	पूर्ण

	अगर (priv->fatal_error) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": %s: firmware fatal error\n",
		       priv->net_dev->name);
		वापस -EIO;
	पूर्ण

	/* !!!!! HACK TEST !!!!!
	 * When lots of debug trace statements are enabled, the driver
	 * करोesn't seem to have as many firmware restart cycles...
	 *
	 * As a test, we're sticking in a 1/100s delay here */
	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(10));

	वापस 0;

      fail_unlock:
	spin_unlock_irqrestore(&priv->low_lock, flags);

	वापस err;
पूर्ण

/*
 * Verअगरy the values and data access of the hardware
 * No locks needed or used.  No functions called.
 */
अटल पूर्णांक ipw2100_verअगरy(काष्ठा ipw2100_priv *priv)
अणु
	u32 data1, data2;
	u32 address;

	u32 val1 = 0x76543210;
	u32 val2 = 0xFEDCBA98;

	/* Doमुख्य 0 check - all values should be DOA_DEBUG */
	क्रम (address = IPW_REG_DOA_DEBUG_AREA_START;
	     address < IPW_REG_DOA_DEBUG_AREA_END; address += माप(u32)) अणु
		पढ़ो_रेजिस्टर(priv->net_dev, address, &data1);
		अगर (data1 != IPW_DATA_DOA_DEBUG_VALUE)
			वापस -EIO;
	पूर्ण

	/* Doमुख्य 1 check - use arbitrary पढ़ो/ग_लिखो compare  */
	क्रम (address = 0; address < 5; address++) अणु
		/* The memory area is not used now */
		ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x32,
			       val1);
		ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x36,
			       val2);
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x32,
			      &data1);
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_DOMAIN_1_OFFSET + 0x36,
			      &data2);
		अगर (val1 == data1 && val2 == data2)
			वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 *
 * Loop until the CARD_DISABLED bit is the same value as the
 * supplied parameter
 *
 * TODO: See अगर it would be more efficient to करो a रुको/wake
 *       cycle and have the completion event trigger the wakeup
 *
 */
#घोषणा IPW_CARD_DISABLE_COMPLETE_WAIT		    100	// 100 milli
अटल पूर्णांक ipw2100_रुको_क्रम_card_state(काष्ठा ipw2100_priv *priv, पूर्णांक state)
अणु
	पूर्णांक i;
	u32 card_state;
	u32 len = माप(card_state);
	पूर्णांक err;

	क्रम (i = 0; i <= IPW_CARD_DISABLE_COMPLETE_WAIT * 1000; i += 50) अणु
		err = ipw2100_get_ordinal(priv, IPW_ORD_CARD_DISABLED,
					  &card_state, &len);
		अगर (err) अणु
			IPW_DEBUG_INFO("Query of CARD_DISABLED ordinal "
				       "failed.\n");
			वापस 0;
		पूर्ण

		/* We'll अवरोध out अगर either the HW state says it is
		 * in the state we want, or अगर HOST_COMPLETE command
		 * finishes */
		अगर ((card_state == state) ||
		    ((priv->status & STATUS_ENABLED) ?
		     IPW_HW_STATE_ENABLED : IPW_HW_STATE_DISABLED) == state) अणु
			अगर (state == IPW_HW_STATE_ENABLED)
				priv->status |= STATUS_ENABLED;
			अन्यथा
				priv->status &= ~STATUS_ENABLED;

			वापस 0;
		पूर्ण

		udelay(50);
	पूर्ण

	IPW_DEBUG_INFO("ipw2100_wait_for_card_state to %s state timed out\n",
		       state ? "DISABLED" : "ENABLED");
	वापस -EIO;
पूर्ण

/*********************************************************************
    Procedure   :   sw_reset_and_घड़ी
    Purpose     :   Asserts s/w reset, निश्चितs घड़ी initialization
                    and रुकोs क्रम घड़ी stabilization
 ********************************************************************/
अटल पूर्णांक sw_reset_and_घड़ी(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;
	u32 r;

	// निश्चित s/w reset
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_SW_RESET);

	// रुको क्रम घड़ी stabilization
	क्रम (i = 0; i < 1000; i++) अणु
		udelay(IPW_WAIT_RESET_ARC_COMPLETE_DELAY);

		// check घड़ी पढ़ोy bit
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, &r);
		अगर (r & IPW_AUX_HOST_RESET_REG_PRINCETON_RESET)
			अवरोध;
	पूर्ण

	अगर (i == 1000)
		वापस -EIO;	// TODO: better error value

	/* set "initialization complete" bit to move adapter to
	 * D0 state */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_GP_CNTRL,
		       IPW_AUX_HOST_GP_CNTRL_BIT_INIT_DONE);

	/* रुको क्रम घड़ी stabilization */
	क्रम (i = 0; i < 10000; i++) अणु
		udelay(IPW_WAIT_CLOCK_STABILIZATION_DELAY * 4);

		/* check घड़ी पढ़ोy bit */
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_GP_CNTRL, &r);
		अगर (r & IPW_AUX_HOST_GP_CNTRL_BIT_CLOCK_READY)
			अवरोध;
	पूर्ण

	अगर (i == 10000)
		वापस -EIO;	/* TODO: better error value */

	/* set D0 standby bit */
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_GP_CNTRL, &r);
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_GP_CNTRL,
		       r | IPW_AUX_HOST_GP_CNTRL_BIT_HOST_ALLOWS_STANDBY);

	वापस 0;
पूर्ण

/*********************************************************************
    Procedure   :   ipw2100_करोwnload_firmware
    Purpose     :   Initiaze adapter after घातer on.
                    The sequence is:
                    1. निश्चित s/w reset first!
                    2. awake घड़ीs & रुको क्रम घड़ी stabilization
                    3. hold ARC (करोn't ask me why...)
                    4. load Dino ucode and reset/घड़ी init again
                    5. zero-out shared mem
                    6. करोwnload f/w
 *******************************************************************/
अटल पूर्णांक ipw2100_करोwnload_firmware(काष्ठा ipw2100_priv *priv)
अणु
	u32 address;
	पूर्णांक err;

#अगर_अघोषित CONFIG_PM
	/* Fetch the firmware and microcode */
	काष्ठा ipw2100_fw ipw2100_firmware;
#पूर्ण_अगर

	अगर (priv->fatal_error) अणु
		IPW_DEBUG_ERROR("%s: ipw2100_download_firmware called after "
				"fatal error %d.  Interface must be brought down.\n",
				priv->net_dev->name, priv->fatal_error);
		वापस -EINVAL;
	पूर्ण
#अगर_घोषित CONFIG_PM
	अगर (!ipw2100_firmware.version) अणु
		err = ipw2100_get_firmware(priv, &ipw2100_firmware);
		अगर (err) अणु
			IPW_DEBUG_ERROR("%s: ipw2100_get_firmware failed: %d\n",
					priv->net_dev->name, err);
			priv->fatal_error = IPW2100_ERR_FW_LOAD;
			जाओ fail;
		पूर्ण
	पूर्ण
#अन्यथा
	err = ipw2100_get_firmware(priv, &ipw2100_firmware);
	अगर (err) अणु
		IPW_DEBUG_ERROR("%s: ipw2100_get_firmware failed: %d\n",
				priv->net_dev->name, err);
		priv->fatal_error = IPW2100_ERR_FW_LOAD;
		जाओ fail;
	पूर्ण
#पूर्ण_अगर
	priv->firmware_version = ipw2100_firmware.version;

	/* s/w reset and घड़ी stabilization */
	err = sw_reset_and_घड़ी(priv);
	अगर (err) अणु
		IPW_DEBUG_ERROR("%s: sw_reset_and_clock failed: %d\n",
				priv->net_dev->name, err);
		जाओ fail;
	पूर्ण

	err = ipw2100_verअगरy(priv);
	अगर (err) अणु
		IPW_DEBUG_ERROR("%s: ipw2100_verify failed: %d\n",
				priv->net_dev->name, err);
		जाओ fail;
	पूर्ण

	/* Hold ARC */
	ग_लिखो_nic_dword(priv->net_dev,
			IPW_INTERNAL_REGISTER_HALT_AND_RESET, 0x80000000);

	/* allow ARC to run */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, 0);

	/* load microcode */
	err = ipw2100_ucode_करोwnload(priv, &ipw2100_firmware);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": %s: Error loading microcode: %d\n",
		       priv->net_dev->name, err);
		जाओ fail;
	पूर्ण

	/* release ARC */
	ग_लिखो_nic_dword(priv->net_dev,
			IPW_INTERNAL_REGISTER_HALT_AND_RESET, 0x00000000);

	/* s/w reset and घड़ी stabilization (again!!!) */
	err = sw_reset_and_घड़ी(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: sw_reset_and_clock failed: %d\n",
		       priv->net_dev->name, err);
		जाओ fail;
	पूर्ण

	/* load f/w */
	err = ipw2100_fw_करोwnload(priv, &ipw2100_firmware);
	अगर (err) अणु
		IPW_DEBUG_ERROR("%s: Error loading firmware: %d\n",
				priv->net_dev->name, err);
		जाओ fail;
	पूर्ण
#अगर_अघोषित CONFIG_PM
	/*
	 * When the .resume method of the driver is called, the other
	 * part of the प्रणाली, i.e. the ide driver could still stay in
	 * the suspend stage. This prevents us from loading the firmware
	 * from the disk.  --YZ
	 */

	/* मुक्त any storage allocated क्रम firmware image */
	ipw2100_release_firmware(priv, &ipw2100_firmware);
#पूर्ण_अगर

	/* zero out Doमुख्य 1 area indirectly (Si requirement) */
	क्रम (address = IPW_HOST_FW_SHARED_AREA0;
	     address < IPW_HOST_FW_SHARED_AREA0_END; address += 4)
		ग_लिखो_nic_dword(priv->net_dev, address, 0);
	क्रम (address = IPW_HOST_FW_SHARED_AREA1;
	     address < IPW_HOST_FW_SHARED_AREA1_END; address += 4)
		ग_लिखो_nic_dword(priv->net_dev, address, 0);
	क्रम (address = IPW_HOST_FW_SHARED_AREA2;
	     address < IPW_HOST_FW_SHARED_AREA2_END; address += 4)
		ग_लिखो_nic_dword(priv->net_dev, address, 0);
	क्रम (address = IPW_HOST_FW_SHARED_AREA3;
	     address < IPW_HOST_FW_SHARED_AREA3_END; address += 4)
		ग_लिखो_nic_dword(priv->net_dev, address, 0);
	क्रम (address = IPW_HOST_FW_INTERRUPT_AREA;
	     address < IPW_HOST_FW_INTERRUPT_AREA_END; address += 4)
		ग_लिखो_nic_dword(priv->net_dev, address, 0);

	वापस 0;

      fail:
	ipw2100_release_firmware(priv, &ipw2100_firmware);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम ipw2100_enable_पूर्णांकerrupts(काष्ठा ipw2100_priv *priv)
अणु
	अगर (priv->status & STATUS_INT_ENABLED)
		वापस;
	priv->status |= STATUS_INT_ENABLED;
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_INTA_MASK, IPW_INTERRUPT_MASK);
पूर्ण

अटल अंतरभूत व्योम ipw2100_disable_पूर्णांकerrupts(काष्ठा ipw2100_priv *priv)
अणु
	अगर (!(priv->status & STATUS_INT_ENABLED))
		वापस;
	priv->status &= ~STATUS_INT_ENABLED;
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_INTA_MASK, 0x0);
पूर्ण

अटल व्योम ipw2100_initialize_ordinals(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा ipw2100_ordinals *ord = &priv->ordinals;

	IPW_DEBUG_INFO("enter\n");

	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_ORDINALS_TABLE_1,
		      &ord->table1_addr);

	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_ORDINALS_TABLE_2,
		      &ord->table2_addr);

	पढ़ो_nic_dword(priv->net_dev, ord->table1_addr, &ord->table1_size);
	पढ़ो_nic_dword(priv->net_dev, ord->table2_addr, &ord->table2_size);

	ord->table2_size &= 0x0000FFFF;

	IPW_DEBUG_INFO("table 1 size: %d\n", ord->table1_size);
	IPW_DEBUG_INFO("table 2 size: %d\n", ord->table2_size);
	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल अंतरभूत व्योम ipw2100_hw_set_gpio(काष्ठा ipw2100_priv *priv)
अणु
	u32 reg = 0;
	/*
	 * Set GPIO 3 writable by FW; GPIO 1 writable
	 * by driver and enable घड़ी
	 */
	reg = (IPW_BIT_GPIO_GPIO3_MASK | IPW_BIT_GPIO_GPIO1_ENABLE |
	       IPW_BIT_GPIO_LED_OFF);
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_GPIO, reg);
पूर्ण

अटल पूर्णांक rf_समाप्त_active(काष्ठा ipw2100_priv *priv)
अणु
#घोषणा MAX_RF_KILL_CHECKS 5
#घोषणा RF_KILL_CHECK_DELAY 40

	अचिन्हित लघु value = 0;
	u32 reg = 0;
	पूर्णांक i;

	अगर (!(priv->hw_features & HW_FEATURE_RFKILL)) अणु
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, false);
		priv->status &= ~STATUS_RF_KILL_HW;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < MAX_RF_KILL_CHECKS; i++) अणु
		udelay(RF_KILL_CHECK_DELAY);
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_GPIO, &reg);
		value = (value << 1) | ((reg & IPW_BIT_GPIO_RF_KILL) ? 0 : 1);
	पूर्ण

	अगर (value == 0) अणु
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, true);
		priv->status |= STATUS_RF_KILL_HW;
	पूर्ण अन्यथा अणु
		wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, false);
		priv->status &= ~STATUS_RF_KILL_HW;
	पूर्ण

	वापस (value == 0);
पूर्ण

अटल पूर्णांक ipw2100_get_hw_features(काष्ठा ipw2100_priv *priv)
अणु
	u32 addr, len;
	u32 val;

	/*
	 * EEPROM_SRAM_DB_START_ADDRESS using ordinal in ordinal table 1
	 */
	len = माप(addr);
	अगर (ipw2100_get_ordinal
	    (priv, IPW_ORD_EEPROM_SRAM_DB_BLOCK_START_ADDRESS, &addr, &len)) अणु
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		वापस -EIO;
	पूर्ण

	IPW_DEBUG_INFO("EEPROM address: %08X\n", addr);

	/*
	 * EEPROM version is the byte at offset 0xfd in firmware
	 * We पढ़ो 4 bytes, then shअगरt out the byte we actually want */
	पढ़ो_nic_dword(priv->net_dev, addr + 0xFC, &val);
	priv->eeprom_version = (val >> 24) & 0xFF;
	IPW_DEBUG_INFO("EEPROM version: %d\n", priv->eeprom_version);

	/*
	 *  HW RF Kill enable is bit 0 in byte at offset 0x21 in firmware
	 *
	 *  notice that the EEPROM bit is reverse polarity, i.e.
	 *     bit = 0  signअगरies HW RF समाप्त चयन is supported
	 *     bit = 1  signअगरies HW RF समाप्त चयन is NOT supported
	 */
	पढ़ो_nic_dword(priv->net_dev, addr + 0x20, &val);
	अगर (!((val >> 24) & 0x01))
		priv->hw_features |= HW_FEATURE_RFKILL;

	IPW_DEBUG_INFO("HW RF Kill: %ssupported.\n",
		       (priv->hw_features & HW_FEATURE_RFKILL) ? "" : "not ");

	वापस 0;
पूर्ण

/*
 * Start firmware execution after घातer on and initialization
 * The sequence is:
 *  1. Release ARC
 *  2. Wait क्रम f/w initialization completes;
 */
अटल पूर्णांक ipw2100_start_adapter(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;
	u32 पूर्णांकa, पूर्णांकa_mask, gpio;

	IPW_DEBUG_INFO("enter\n");

	अगर (priv->status & STATUS_RUNNING)
		वापस 0;

	/*
	 * Initialize the hw - drive adapter to DO state by setting
	 * init_करोne bit. Wait क्रम clk_पढ़ोy bit and Download
	 * fw & dino ucode
	 */
	अगर (ipw2100_करोwnload_firmware(priv)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: Failed to power on the adapter.\n",
		       priv->net_dev->name);
		वापस -EIO;
	पूर्ण

	/* Clear the Tx, Rx and Msg queues and the r/w indexes
	 * in the firmware RBD and TBD ring queue */
	ipw2100_queues_initialize(priv);

	ipw2100_hw_set_gpio(priv);

	/* TODO -- Look at disabling पूर्णांकerrupts here to make sure none
	 * get fired during FW initialization */

	/* Release ARC - clear reset bit */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, 0);

	/* रुको क्रम f/w initialization complete */
	IPW_DEBUG_FW("Waiting for f/w initialization to complete...\n");
	i = 5000;
	करो अणु
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(40));
		/* Toकरो... रुको क्रम sync command ... */

		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_INTA, &पूर्णांकa);

		/* check "init done" bit */
		अगर (पूर्णांकa & IPW2100_INTA_FW_INIT_DONE) अणु
			/* reset "init done" bit */
			ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_INTA,
				       IPW2100_INTA_FW_INIT_DONE);
			अवरोध;
		पूर्ण

		/* check error conditions : we check these after the firmware
		 * check so that अगर there is an error, the पूर्णांकerrupt handler
		 * will see it and the adapter will be reset */
		अगर (पूर्णांकa &
		    (IPW2100_INTA_FATAL_ERROR | IPW2100_INTA_PARITY_ERROR)) अणु
			/* clear error conditions */
			ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_INTA,
				       IPW2100_INTA_FATAL_ERROR |
				       IPW2100_INTA_PARITY_ERROR);
		पूर्ण
	पूर्ण जबतक (--i);

	/* Clear out any pending INTAs since we aren't supposed to have
	 * पूर्णांकerrupts enabled at this poपूर्णांक... */
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_INTA, &पूर्णांकa);
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_INTA_MASK, &पूर्णांकa_mask);
	पूर्णांकa &= IPW_INTERRUPT_MASK;
	/* Clear out any pending पूर्णांकerrupts */
	अगर (पूर्णांकa & पूर्णांकa_mask)
		ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_INTA, पूर्णांकa);

	IPW_DEBUG_FW("f/w initialization complete: %s\n",
		     i ? "SUCCESS" : "FAILED");

	अगर (!i) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       ": %s: Firmware did not initialize.\n",
		       priv->net_dev->name);
		वापस -EIO;
	पूर्ण

	/* allow firmware to ग_लिखो to GPIO1 & GPIO3 */
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_GPIO, &gpio);

	gpio |= (IPW_BIT_GPIO_GPIO1_MASK | IPW_BIT_GPIO_GPIO3_MASK);

	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_GPIO, gpio);

	/* Ready to receive commands */
	priv->status |= STATUS_RUNNING;

	/* The adapter has been reset; we are not associated */
	priv->status &= ~(STATUS_ASSOCIATING | STATUS_ASSOCIATED);

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ipw2100_reset_fatalerror(काष्ठा ipw2100_priv *priv)
अणु
	अगर (!priv->fatal_error)
		वापस;

	priv->fatal_errors[priv->fatal_index++] = priv->fatal_error;
	priv->fatal_index %= IPW2100_ERROR_QUEUE;
	priv->fatal_error = 0;
पूर्ण

/* NOTE: Our पूर्णांकerrupt is disabled when this method is called */
अटल पूर्णांक ipw2100_घातer_cycle_adapter(काष्ठा ipw2100_priv *priv)
अणु
	u32 reg;
	पूर्णांक i;

	IPW_DEBUG_INFO("Power cycling the hardware.\n");

	ipw2100_hw_set_gpio(priv);

	/* Step 1. Stop Master Assert */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_STOP_MASTER);

	/* Step 2. Wait क्रम stop Master Assert
	 *         (not more than 50us, otherwise ret error */
	i = 5;
	करो अणु
		udelay(IPW_WAIT_RESET_MASTER_ASSERT_COMPLETE_DELAY);
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, &reg);

		अगर (reg & IPW_AUX_HOST_RESET_REG_MASTER_DISABLED)
			अवरोध;
	पूर्ण जबतक (--i);

	priv->status &= ~STATUS_RESET_PENDING;

	अगर (!i) अणु
		IPW_DEBUG_INFO
		    ("exit - waited too long for master assert stop\n");
		वापस -EIO;
	पूर्ण

	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_SW_RESET);

	/* Reset any fatal_error conditions */
	ipw2100_reset_fatalerror(priv);

	/* At this poपूर्णांक, the adapter is now stopped and disabled */
	priv->status &= ~(STATUS_RUNNING | STATUS_ASSOCIATING |
			  STATUS_ASSOCIATED | STATUS_ENABLED);

	वापस 0;
पूर्ण

/*
 * Send the CARD_DISABLE_PHY_OFF command to the card to disable it
 *
 * After disabling, अगर the card was associated, a STATUS_ASSN_LOST will be sent.
 *
 * STATUS_CARD_DISABLE_NOTIFICATION will be sent regardless of
 * अगर STATUS_ASSN_LOST is sent.
 */
अटल पूर्णांक ipw2100_hw_phy_off(काष्ठा ipw2100_priv *priv)
अणु

#घोषणा HW_PHY_OFF_LOOP_DELAY (msecs_to_jअगरfies(50))

	काष्ठा host_command cmd = अणु
		.host_command = CARD_DISABLE_PHY_OFF,
		.host_command_sequence = 0,
		.host_command_length = 0,
	पूर्ण;
	पूर्णांक err, i;
	u32 val1, val2;

	IPW_DEBUG_HC("CARD_DISABLE_PHY_OFF\n");

	/* Turn off the radio */
	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 2500; i++) अणु
		पढ़ो_nic_dword(priv->net_dev, IPW2100_CONTROL_REG, &val1);
		पढ़ो_nic_dword(priv->net_dev, IPW2100_COMMAND, &val2);

		अगर ((val1 & IPW2100_CONTROL_PHY_OFF) &&
		    (val2 & IPW2100_COMMAND_PHY_OFF))
			वापस 0;

		schedule_समयout_unपूर्णांकerruptible(HW_PHY_OFF_LOOP_DELAY);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक ipw2100_enable_adapter(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = HOST_COMPLETE,
		.host_command_sequence = 0,
		.host_command_length = 0
	पूर्ण;
	पूर्णांक err = 0;

	IPW_DEBUG_HC("HOST_COMPLETE\n");

	अगर (priv->status & STATUS_ENABLED)
		वापस 0;

	mutex_lock(&priv->adapter_mutex);

	अगर (rf_समाप्त_active(priv)) अणु
		IPW_DEBUG_HC("Command aborted due to RF kill active.\n");
		जाओ fail_up;
	पूर्ण

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err) अणु
		IPW_DEBUG_INFO("Failed to send HOST_COMPLETE command\n");
		जाओ fail_up;
	पूर्ण

	err = ipw2100_रुको_क्रम_card_state(priv, IPW_HW_STATE_ENABLED);
	अगर (err) अणु
		IPW_DEBUG_INFO("%s: card not responding to init command.\n",
			       priv->net_dev->name);
		जाओ fail_up;
	पूर्ण

	अगर (priv->stop_hang_check) अणु
		priv->stop_hang_check = 0;
		schedule_delayed_work(&priv->hang_check, HZ / 2);
	पूर्ण

      fail_up:
	mutex_unlock(&priv->adapter_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_hw_stop_adapter(काष्ठा ipw2100_priv *priv)
अणु
#घोषणा HW_POWER_DOWN_DELAY (msecs_to_jअगरfies(100))

	काष्ठा host_command cmd = अणु
		.host_command = HOST_PRE_POWER_DOWN,
		.host_command_sequence = 0,
		.host_command_length = 0,
	पूर्ण;
	पूर्णांक err, i;
	u32 reg;

	अगर (!(priv->status & STATUS_RUNNING))
		वापस 0;

	priv->status |= STATUS_STOPPING;

	/* We can only shut करोwn the card अगर the firmware is operational.  So,
	 * अगर we haven't reset since a fatal_error, then we can not send the
	 * shutकरोwn commands. */
	अगर (!priv->fatal_error) अणु
		/* First, make sure the adapter is enabled so that the PHY_OFF
		 * command can shut it करोwn */
		ipw2100_enable_adapter(priv);

		err = ipw2100_hw_phy_off(priv);
		अगर (err)
			prपूर्णांकk(KERN_WARNING DRV_NAME
			       ": Error disabling radio %d\n", err);

		/*
		 * If in D0-standby mode going directly to D3 may cause a
		 * PCI bus violation.  Thereक्रमe we must change out of the D0
		 * state.
		 *
		 * Sending the PREPARE_FOR_POWER_DOWN will restrict the
		 * hardware from going पूर्णांकo standby mode and will transition
		 * out of D0-standby अगर it is alपढ़ोy in that state.
		 *
		 * STATUS_PREPARE_POWER_DOWN_COMPLETE will be sent by the
		 * driver upon completion.  Once received, the driver can
		 * proceed to the D3 state.
		 *
		 * Prepare क्रम घातer करोwn command to fw.  This command would
		 * take HW out of D0-standby and prepare it क्रम D3 state.
		 *
		 * Currently FW करोes not support event notअगरication क्रम this
		 * event. Thereक्रमe, skip रुकोing क्रम it.  Just रुको a fixed
		 * 100ms
		 */
		IPW_DEBUG_HC("HOST_PRE_POWER_DOWN\n");

		err = ipw2100_hw_send_command(priv, &cmd);
		अगर (err)
			prपूर्णांकk(KERN_WARNING DRV_NAME ": "
			       "%s: Power down command failed: Error %d\n",
			       priv->net_dev->name, err);
		अन्यथा
			schedule_समयout_unपूर्णांकerruptible(HW_POWER_DOWN_DELAY);
	पूर्ण

	priv->status &= ~STATUS_ENABLED;

	/*
	 * Set GPIO 3 writable by FW; GPIO 1 writable
	 * by driver and enable घड़ी
	 */
	ipw2100_hw_set_gpio(priv);

	/*
	 * Power करोwn adapter.  Sequence:
	 * 1. Stop master निश्चित (RESET_REG[9]=1)
	 * 2. Wait क्रम stop master (RESET_REG[8]==1)
	 * 3. S/w reset निश्चित (RESET_REG[7] = 1)
	 */

	/* Stop master निश्चित */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_STOP_MASTER);

	/* रुको stop master not more than 50 usec.
	 * Otherwise वापस error. */
	क्रम (i = 5; i > 0; i--) अणु
		udelay(10);

		/* Check master stop bit */
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, &reg);

		अगर (reg & IPW_AUX_HOST_RESET_REG_MASTER_DISABLED)
			अवरोध;
	पूर्ण

	अगर (i == 0)
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       ": %s: Could now power down adapter.\n",
		       priv->net_dev->name);

	/* निश्चित s/w reset */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_SW_RESET);

	priv->status &= ~(STATUS_RUNNING | STATUS_STOPPING);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_disable_adapter(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = CARD_DISABLE,
		.host_command_sequence = 0,
		.host_command_length = 0
	पूर्ण;
	पूर्णांक err = 0;

	IPW_DEBUG_HC("CARD_DISABLE\n");

	अगर (!(priv->status & STATUS_ENABLED))
		वापस 0;

	/* Make sure we clear the associated state */
	priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);

	अगर (!priv->stop_hang_check) अणु
		priv->stop_hang_check = 1;
		cancel_delayed_work(&priv->hang_check);
	पूर्ण

	mutex_lock(&priv->adapter_mutex);

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       ": exit - failed to send CARD_DISABLE command\n");
		जाओ fail_up;
	पूर्ण

	err = ipw2100_रुको_क्रम_card_state(priv, IPW_HW_STATE_DISABLED);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       ": exit - card failed to change to DISABLED\n");
		जाओ fail_up;
	पूर्ण

	IPW_DEBUG_INFO("TODO: implement scan state machine\n");

      fail_up:
	mutex_unlock(&priv->adapter_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_scan_options(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = SET_SCAN_OPTIONS,
		.host_command_sequence = 0,
		.host_command_length = 8
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_INFO("enter\n");

	IPW_DEBUG_SCAN("setting scan options\n");

	cmd.host_command_parameters[0] = 0;

	अगर (!(priv->config & CFG_ASSOCIATE))
		cmd.host_command_parameters[0] |= IPW_SCAN_NOASSOCIATE;
	अगर ((priv->ieee->sec.flags & SEC_ENABLED) && priv->ieee->sec.enabled)
		cmd.host_command_parameters[0] |= IPW_SCAN_MIXED_CELL;
	अगर (priv->config & CFG_PASSIVE_SCAN)
		cmd.host_command_parameters[0] |= IPW_SCAN_PASSIVE;

	cmd.host_command_parameters[1] = priv->channel_mask;

	err = ipw2100_hw_send_command(priv, &cmd);

	IPW_DEBUG_HC("SET_SCAN_OPTIONS 0x%04X\n",
		     cmd.host_command_parameters[0]);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_start_scan(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = BROADCAST_SCAN,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("START_SCAN\n");

	cmd.host_command_parameters[0] = 0;

	/* No scanning अगर in monitor mode */
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR)
		वापस 1;

	अगर (priv->status & STATUS_SCANNING) अणु
		IPW_DEBUG_SCAN("Scan requested while already in scan...\n");
		वापस 0;
	पूर्ण

	IPW_DEBUG_INFO("enter\n");

	/* Not clearing here; करोing so makes iwlist always वापस nothing...
	 *
	 * We should modअगरy the table logic to use aging tables vs. clearing
	 * the table on each scan start.
	 */
	IPW_DEBUG_SCAN("starting scan\n");

	priv->status |= STATUS_SCANNING;
	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		priv->status &= ~STATUS_SCANNING;

	IPW_DEBUG_INFO("exit\n");

	वापस err;
पूर्ण

अटल स्थिर काष्ठा libipw_geo ipw_geos[] = अणु
	अणु			/* Restricted */
	 "---",
	 .bg_channels = 14,
	 .bg = अणुअणु2412, 1पूर्ण, अणु2417, 2पूर्ण, अणु2422, 3पूर्ण,
		अणु2427, 4पूर्ण, अणु2432, 5पूर्ण, अणु2437, 6पूर्ण,
		अणु2442, 7पूर्ण, अणु2447, 8पूर्ण, अणु2452, 9पूर्ण,
		अणु2457, 10पूर्ण, अणु2462, 11पूर्ण, अणु2467, 12पूर्ण,
		अणु2472, 13पूर्ण, अणु2484, 14पूर्णपूर्ण,
	 पूर्ण,
पूर्ण;

अटल पूर्णांक ipw2100_up(काष्ठा ipw2100_priv *priv, पूर्णांक deferred)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	u32 lock;
	u32 ord_len = माप(lock);

	/* Age scan list entries found beक्रमe suspend */
	अगर (priv->suspend_समय) अणु
		libipw_networks_age(priv->ieee, priv->suspend_समय);
		priv->suspend_समय = 0;
	पूर्ण

	/* Quiet अगर manually disabled. */
	अगर (priv->status & STATUS_RF_KILL_SW) अणु
		IPW_DEBUG_INFO("%s: Radio is disabled by Manual Disable "
			       "switch\n", priv->net_dev->name);
		वापस 0;
	पूर्ण

	/* the ipw2100 hardware really करोesn't want घातer management delays
	 * दीर्घer than 175usec
	 */
	cpu_latency_qos_update_request(&ipw2100_pm_qos_req, 175);

	/* If the पूर्णांकerrupt is enabled, turn it off... */
	spin_lock_irqsave(&priv->low_lock, flags);
	ipw2100_disable_पूर्णांकerrupts(priv);

	/* Reset any fatal_error conditions */
	ipw2100_reset_fatalerror(priv);
	spin_unlock_irqrestore(&priv->low_lock, flags);

	अगर (priv->status & STATUS_POWERED ||
	    (priv->status & STATUS_RESET_PENDING)) अणु
		/* Power cycle the card ... */
		err = ipw2100_घातer_cycle_adapter(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
			       ": %s: Could not cycle adapter.\n",
			       priv->net_dev->name);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा
		priv->status |= STATUS_POWERED;

	/* Load the firmware, start the घड़ीs, etc. */
	err = ipw2100_start_adapter(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: Failed to start the firmware.\n",
		       priv->net_dev->name);
		जाओ निकास;
	पूर्ण

	ipw2100_initialize_ordinals(priv);

	/* Determine capabilities of this particular HW configuration */
	err = ipw2100_get_hw_features(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: Failed to determine HW features.\n",
		       priv->net_dev->name);
		जाओ निकास;
	पूर्ण

	/* Initialize the geo */
	libipw_set_geo(priv->ieee, &ipw_geos[0]);
	priv->ieee->freq_band = LIBIPW_24GHZ_BAND;

	lock = LOCK_NONE;
	err = ipw2100_set_ordinal(priv, IPW_ORD_PERS_DB_LOCK, &lock, &ord_len);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: Failed to clear ordinal lock.\n",
		       priv->net_dev->name);
		जाओ निकास;
	पूर्ण

	priv->status &= ~STATUS_SCANNING;

	अगर (rf_समाप्त_active(priv)) अणु
		prपूर्णांकk(KERN_INFO "%s: Radio is disabled by RF switch.\n",
		       priv->net_dev->name);

		अगर (priv->stop_rf_समाप्त) अणु
			priv->stop_rf_समाप्त = 0;
			schedule_delayed_work(&priv->rf_समाप्त,
					      round_jअगरfies_relative(HZ));
		पूर्ण

		deferred = 1;
	पूर्ण

	/* Turn on the पूर्णांकerrupt so that commands can be processed */
	ipw2100_enable_पूर्णांकerrupts(priv);

	/* Send all of the commands that must be sent prior to
	 * HOST_COMPLETE */
	err = ipw2100_adapter_setup(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": %s: Failed to start the card.\n",
		       priv->net_dev->name);
		जाओ निकास;
	पूर्ण

	अगर (!deferred) अणु
		/* Enable the adapter - sends HOST_COMPLETE */
		err = ipw2100_enable_adapter(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME ": "
			       "%s: failed in call to enable adapter.\n",
			       priv->net_dev->name);
			ipw2100_hw_stop_adapter(priv);
			जाओ निकास;
		पूर्ण

		/* Start a scan . . . */
		ipw2100_set_scan_options(priv);
		ipw2100_start_scan(priv);
	पूर्ण

      निकास:
	वापस err;
पूर्ण

अटल व्योम ipw2100_करोwn(काष्ठा ipw2100_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	जोड़ iwreq_data wrqu = अणु
		.ap_addr = अणु
			    .sa_family = ARPHRD_ETHERपूर्ण
	पूर्ण;
	पूर्णांक associated = priv->status & STATUS_ASSOCIATED;

	/* Kill the RF चयन समयr */
	अगर (!priv->stop_rf_समाप्त) अणु
		priv->stop_rf_समाप्त = 1;
		cancel_delayed_work(&priv->rf_समाप्त);
	पूर्ण

	/* Kill the firmware hang check समयr */
	अगर (!priv->stop_hang_check) अणु
		priv->stop_hang_check = 1;
		cancel_delayed_work(&priv->hang_check);
	पूर्ण

	/* Kill any pending resets */
	अगर (priv->status & STATUS_RESET_PENDING)
		cancel_delayed_work(&priv->reset_work);

	/* Make sure the पूर्णांकerrupt is on so that FW commands will be
	 * processed correctly */
	spin_lock_irqsave(&priv->low_lock, flags);
	ipw2100_enable_पूर्णांकerrupts(priv);
	spin_unlock_irqrestore(&priv->low_lock, flags);

	अगर (ipw2100_hw_stop_adapter(priv))
		prपूर्णांकk(KERN_ERR DRV_NAME ": %s: Error stopping adapter.\n",
		       priv->net_dev->name);

	/* Do not disable the पूर्णांकerrupt until _after_ we disable
	 * the adaptor.  Otherwise the CARD_DISABLE command will never
	 * be ack'd by the firmware */
	spin_lock_irqsave(&priv->low_lock, flags);
	ipw2100_disable_पूर्णांकerrupts(priv);
	spin_unlock_irqrestore(&priv->low_lock, flags);

	cpu_latency_qos_update_request(&ipw2100_pm_qos_req,
				       PM_QOS_DEFAULT_VALUE);

	/* We have to संकेत any supplicant अगर we are disassociating */
	अगर (associated)
		wireless_send_event(priv->net_dev, SIOCGIWAP, &wrqu, शून्य);

	priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);
	netअगर_carrier_off(priv->net_dev);
	netअगर_stop_queue(priv->net_dev);
पूर्ण

अटल पूर्णांक ipw2100_wdev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	स्थिर काष्ठा libipw_geo *geo = libipw_get_geo(priv->ieee);
	काष्ठा wireless_dev *wdev = &priv->ieee->wdev;
	पूर्णांक i;

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
			ipw2100_करोwn(priv);
			वापस -ENOMEM;
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
		bg_band->bitrates = ipw2100_bg_rates;
		bg_band->n_bitrates = RATE_COUNT;

		wdev->wiphy->bands[NL80211_BAND_2GHZ] = bg_band;
	पूर्ण

	wdev->wiphy->cipher_suites = ipw_cipher_suites;
	wdev->wiphy->n_cipher_suites = ARRAY_SIZE(ipw_cipher_suites);

	set_wiphy_dev(wdev->wiphy, &priv->pci_dev->dev);
	अगर (wiphy_रेजिस्टर(wdev->wiphy))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल व्योम ipw2100_reset_adapter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv =
		container_of(work, काष्ठा ipw2100_priv, reset_work.work);
	अचिन्हित दीर्घ flags;
	जोड़ iwreq_data wrqu = अणु
		.ap_addr = अणु
			    .sa_family = ARPHRD_ETHERपूर्ण
	पूर्ण;
	पूर्णांक associated = priv->status & STATUS_ASSOCIATED;

	spin_lock_irqsave(&priv->low_lock, flags);
	IPW_DEBUG_INFO(": %s: Restarting adapter.\n", priv->net_dev->name);
	priv->resets++;
	priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);
	priv->status |= STATUS_SECURITY_UPDATED;

	/* Force a घातer cycle even अगर पूर्णांकerface hasn't been खोलोed
	 * yet */
	cancel_delayed_work(&priv->reset_work);
	priv->status |= STATUS_RESET_PENDING;
	spin_unlock_irqrestore(&priv->low_lock, flags);

	mutex_lock(&priv->action_mutex);
	/* stop समयd checks so that they करोn't पूर्णांकerfere with reset */
	priv->stop_hang_check = 1;
	cancel_delayed_work(&priv->hang_check);

	/* We have to संकेत any supplicant अगर we are disassociating */
	अगर (associated)
		wireless_send_event(priv->net_dev, SIOCGIWAP, &wrqu, शून्य);

	ipw2100_up(priv, 0);
	mutex_unlock(&priv->action_mutex);

पूर्ण

अटल व्योम isr_indicate_associated(काष्ठा ipw2100_priv *priv, u32 status)
अणु

#घोषणा MAC_ASSOCIATION_READ_DELAY (HZ)
	पूर्णांक ret;
	अचिन्हित पूर्णांक len, essid_len;
	अक्षर essid[IW_ESSID_MAX_SIZE];
	u32 txrate;
	u32 chan;
	अक्षर *txratename;
	u8 bssid[ETH_ALEN];

	/*
	 * TBD: BSSID is usually 00:00:00:00:00:00 here and not
	 *      an actual MAC of the AP. Seems like FW sets this
	 *      address too late. Read it later and expose through
	 *      /proc or schedule a later task to query and update
	 */

	essid_len = IW_ESSID_MAX_SIZE;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_SSID,
				  essid, &essid_len);
	अगर (ret) अणु
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		वापस;
	पूर्ण

	len = माप(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_CURRENT_TX_RATE, &txrate, &len);
	अगर (ret) अणु
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		वापस;
	पूर्ण

	len = माप(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_OUR_FREQ, &chan, &len);
	अगर (ret) अणु
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		वापस;
	पूर्ण
	len = ETH_ALEN;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_AP_BSSID, bssid,
				  &len);
	अगर (ret) अणु
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);
		वापस;
	पूर्ण
	स_नकल(priv->ieee->bssid, bssid, ETH_ALEN);

	चयन (txrate) अणु
	हाल TX_RATE_1_MBIT:
		txratename = "1Mbps";
		अवरोध;
	हाल TX_RATE_2_MBIT:
		txratename = "2Mbsp";
		अवरोध;
	हाल TX_RATE_5_5_MBIT:
		txratename = "5.5Mbps";
		अवरोध;
	हाल TX_RATE_11_MBIT:
		txratename = "11Mbps";
		अवरोध;
	शेष:
		IPW_DEBUG_INFO("Unknown rate: %d\n", txrate);
		txratename = "unknown rate";
		अवरोध;
	पूर्ण

	IPW_DEBUG_INFO("%s: Associated with '%*pE' at %s, channel %d (BSSID=%pM)\n",
		       priv->net_dev->name, essid_len, essid,
		       txratename, chan, bssid);

	/* now we copy पढ़ो ssid पूर्णांकo dev */
	अगर (!(priv->config & CFG_STATIC_ESSID)) अणु
		priv->essid_len = min((u8) essid_len, (u8) IW_ESSID_MAX_SIZE);
		स_नकल(priv->essid, essid, priv->essid_len);
	पूर्ण
	priv->channel = chan;
	स_नकल(priv->bssid, bssid, ETH_ALEN);

	priv->status |= STATUS_ASSOCIATING;
	priv->connect_start = kसमय_get_bootसमय_seconds();

	schedule_delayed_work(&priv->wx_event_work, HZ / 10);
पूर्ण

अटल पूर्णांक ipw2100_set_essid(काष्ठा ipw2100_priv *priv, अक्षर *essid,
			     पूर्णांक length, पूर्णांक batch_mode)
अणु
	पूर्णांक ssid_len = min(length, IW_ESSID_MAX_SIZE);
	काष्ठा host_command cmd = अणु
		.host_command = SSID,
		.host_command_sequence = 0,
		.host_command_length = ssid_len
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("SSID: '%*pE'\n", ssid_len, essid);

	अगर (ssid_len)
		स_नकल(cmd.host_command_parameters, essid, ssid_len);

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	/* Bug in FW currently करोesn't honor bit 0 in SET_SCAN_OPTIONS to
	 * disable स्वतः association -- so we cheat by setting a bogus SSID */
	अगर (!ssid_len && !(priv->config & CFG_ASSOCIATE)) अणु
		पूर्णांक i;
		u8 *bogus = (u8 *) cmd.host_command_parameters;
		क्रम (i = 0; i < IW_ESSID_MAX_SIZE; i++)
			bogus[i] = 0x18 + i;
		cmd.host_command_length = IW_ESSID_MAX_SIZE;
	पूर्ण

	/* NOTE:  We always send the SSID command even अगर the provided ESSID is
	 * the same as what we currently think is set. */

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (!err) अणु
		स_रखो(priv->essid + ssid_len, 0, IW_ESSID_MAX_SIZE - ssid_len);
		स_नकल(priv->essid, essid, ssid_len);
		priv->essid_len = ssid_len;
	पूर्ण

	अगर (!batch_mode) अणु
		अगर (ipw2100_enable_adapter(priv))
			err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम isr_indicate_association_lost(काष्ठा ipw2100_priv *priv, u32 status)
अणु
	IPW_DEBUG(IPW_DL_NOTIF | IPW_DL_STATE | IPW_DL_ASSOC,
		  "disassociated: '%*pE' %pM\n", priv->essid_len, priv->essid,
		  priv->bssid);

	priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);

	अगर (priv->status & STATUS_STOPPING) अणु
		IPW_DEBUG_INFO("Card is stopping itself, discard ASSN_LOST.\n");
		वापस;
	पूर्ण

	eth_zero_addr(priv->bssid);
	eth_zero_addr(priv->ieee->bssid);

	netअगर_carrier_off(priv->net_dev);
	netअगर_stop_queue(priv->net_dev);

	अगर (!(priv->status & STATUS_RUNNING))
		वापस;

	अगर (priv->status & STATUS_SECURITY_UPDATED)
		schedule_delayed_work(&priv->security_work, 0);

	schedule_delayed_work(&priv->wx_event_work, 0);
पूर्ण

अटल व्योम isr_indicate_rf_समाप्त(काष्ठा ipw2100_priv *priv, u32 status)
अणु
	IPW_DEBUG_INFO("%s: RF Kill state changed to radio OFF.\n",
		       priv->net_dev->name);

	/* RF_KILL is now enabled (अन्यथा we wouldn't be here) */
	wiphy_rfसमाप्त_set_hw_state(priv->ieee->wdev.wiphy, true);
	priv->status |= STATUS_RF_KILL_HW;

	/* Make sure the RF Kill check समयr is running */
	priv->stop_rf_समाप्त = 0;
	mod_delayed_work(प्रणाली_wq, &priv->rf_समाप्त, round_jअगरfies_relative(HZ));
पूर्ण

अटल व्योम ipw2100_scan_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv = container_of(work, काष्ठा ipw2100_priv,
						 scan_event.work);
	जोड़ iwreq_data wrqu;

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(priv->net_dev, SIOCGIWSCAN, &wrqu, शून्य);
पूर्ण

अटल व्योम isr_scan_complete(काष्ठा ipw2100_priv *priv, u32 status)
अणु
	IPW_DEBUG_SCAN("scan complete\n");
	/* Age the scan results... */
	priv->ieee->scans++;
	priv->status &= ~STATUS_SCANNING;

	/* Only userspace-requested scan completion events go out immediately */
	अगर (!priv->user_requested_scan) अणु
		schedule_delayed_work(&priv->scan_event,
				      round_jअगरfies_relative(msecs_to_jअगरfies(4000)));
	पूर्ण अन्यथा अणु
		priv->user_requested_scan = 0;
		mod_delayed_work(प्रणाली_wq, &priv->scan_event, 0);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IPW2100_DEBUG
#घोषणा IPW2100_HANDLER(v, f) अणु v, f, # v पूर्ण
काष्ठा ipw2100_status_indicator अणु
	पूर्णांक status;
	व्योम (*cb) (काष्ठा ipw2100_priv * priv, u32 status);
	अक्षर *name;
पूर्ण;
#अन्यथा
#घोषणा IPW2100_HANDLER(v, f) अणु v, f पूर्ण
काष्ठा ipw2100_status_indicator अणु
	पूर्णांक status;
	व्योम (*cb) (काष्ठा ipw2100_priv * priv, u32 status);
पूर्ण;
#पूर्ण_अगर				/* CONFIG_IPW2100_DEBUG */

अटल व्योम isr_indicate_scanning(काष्ठा ipw2100_priv *priv, u32 status)
अणु
	IPW_DEBUG_SCAN("Scanning...\n");
	priv->status |= STATUS_SCANNING;
पूर्ण

अटल स्थिर काष्ठा ipw2100_status_indicator status_handlers[] = अणु
	IPW2100_HANDLER(IPW_STATE_INITIALIZED, शून्य),
	IPW2100_HANDLER(IPW_STATE_COUNTRY_FOUND, शून्य),
	IPW2100_HANDLER(IPW_STATE_ASSOCIATED, isr_indicate_associated),
	IPW2100_HANDLER(IPW_STATE_ASSN_LOST, isr_indicate_association_lost),
	IPW2100_HANDLER(IPW_STATE_ASSN_CHANGED, शून्य),
	IPW2100_HANDLER(IPW_STATE_SCAN_COMPLETE, isr_scan_complete),
	IPW2100_HANDLER(IPW_STATE_ENTERED_PSP, शून्य),
	IPW2100_HANDLER(IPW_STATE_LEFT_PSP, शून्य),
	IPW2100_HANDLER(IPW_STATE_RF_KILL, isr_indicate_rf_समाप्त),
	IPW2100_HANDLER(IPW_STATE_DISABLED, शून्य),
	IPW2100_HANDLER(IPW_STATE_POWER_DOWN, शून्य),
	IPW2100_HANDLER(IPW_STATE_SCANNING, isr_indicate_scanning),
	IPW2100_HANDLER(-1, शून्य)
पूर्ण;

अटल व्योम isr_status_change(काष्ठा ipw2100_priv *priv, पूर्णांक status)
अणु
	पूर्णांक i;

	अगर (status == IPW_STATE_SCANNING &&
	    priv->status & STATUS_ASSOCIATED &&
	    !(priv->status & STATUS_SCANNING)) अणु
		IPW_DEBUG_INFO("Scan detected while associated, with "
			       "no scan request.  Restarting firmware.\n");

		/* Wake up any sleeping jobs */
		schedule_reset(priv);
	पूर्ण

	क्रम (i = 0; status_handlers[i].status != -1; i++) अणु
		अगर (status == status_handlers[i].status) अणु
			IPW_DEBUG_NOTIF("Status change: %s\n",
					status_handlers[i].name);
			अगर (status_handlers[i].cb)
				status_handlers[i].cb(priv, status);
			priv->wstats.status = status;
			वापस;
		पूर्ण
	पूर्ण

	IPW_DEBUG_NOTIF("unknown status received: %04x\n", status);
पूर्ण

अटल व्योम isr_rx_complete_command(काष्ठा ipw2100_priv *priv,
				    काष्ठा ipw2100_cmd_header *cmd)
अणु
#अगर_घोषित CONFIG_IPW2100_DEBUG
	अगर (cmd->host_command_reg < ARRAY_SIZE(command_types)) अणु
		IPW_DEBUG_HC("Command completed '%s (%d)'\n",
			     command_types[cmd->host_command_reg],
			     cmd->host_command_reg);
	पूर्ण
#पूर्ण_अगर
	अगर (cmd->host_command_reg == HOST_COMPLETE)
		priv->status |= STATUS_ENABLED;

	अगर (cmd->host_command_reg == CARD_DISABLE)
		priv->status &= ~STATUS_ENABLED;

	priv->status &= ~STATUS_CMD_ACTIVE;

	wake_up_पूर्णांकerruptible(&priv->रुको_command_queue);
पूर्ण

#अगर_घोषित CONFIG_IPW2100_DEBUG
अटल स्थिर अक्षर *frame_types[] = अणु
	"COMMAND_STATUS_VAL",
	"STATUS_CHANGE_VAL",
	"P80211_DATA_VAL",
	"P8023_DATA_VAL",
	"HOST_NOTIFICATION_VAL"
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक ipw2100_alloc_skb(काष्ठा ipw2100_priv *priv,
				    काष्ठा ipw2100_rx_packet *packet)
अणु
	packet->skb = dev_alloc_skb(माप(काष्ठा ipw2100_rx));
	अगर (!packet->skb)
		वापस -ENOMEM;

	packet->rxp = (काष्ठा ipw2100_rx *)packet->skb->data;
	packet->dma_addr = dma_map_single(&priv->pci_dev->dev,
					  packet->skb->data,
					  माप(काष्ठा ipw2100_rx),
					  DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&priv->pci_dev->dev, packet->dma_addr)) अणु
		dev_kमुक्त_skb(packet->skb);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SEARCH_ERROR   0xffffffff
#घोषणा SEARCH_FAIL    0xfffffffe
#घोषणा SEARCH_SUCCESS 0xfffffff0
#घोषणा SEARCH_DISCARD 0
#घोषणा SEARCH_SNAPSHOT 1

#घोषणा SNAPSHOT_ADDR(ofs) (priv->snapshot[((ofs) >> 12) & 0xff] + ((ofs) & 0xfff))
अटल व्योम ipw2100_snapshot_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;
	अगर (!priv->snapshot[0])
		वापस;
	क्रम (i = 0; i < 0x30; i++)
		kमुक्त(priv->snapshot[i]);
	priv->snapshot[0] = शून्य;
पूर्ण

#अगर_घोषित IPW2100_DEBUG_C3
अटल पूर्णांक ipw2100_snapshot_alloc(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;
	अगर (priv->snapshot[0])
		वापस 1;
	क्रम (i = 0; i < 0x30; i++) अणु
		priv->snapshot[i] = kदो_स्मृति(0x1000, GFP_ATOMIC);
		अगर (!priv->snapshot[i]) अणु
			IPW_DEBUG_INFO("%s: Error allocating snapshot "
				       "buffer %d\n", priv->net_dev->name, i);
			जबतक (i > 0)
				kमुक्त(priv->snapshot[--i]);
			priv->snapshot[0] = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल u32 ipw2100_match_buf(काष्ठा ipw2100_priv *priv, u8 * in_buf,
				    माप_प्रकार len, पूर्णांक mode)
अणु
	u32 i, j;
	u32 पंचांगp;
	u8 *s, *d;
	u32 ret;

	s = in_buf;
	अगर (mode == SEARCH_SNAPSHOT) अणु
		अगर (!ipw2100_snapshot_alloc(priv))
			mode = SEARCH_DISCARD;
	पूर्ण

	क्रम (ret = SEARCH_FAIL, i = 0; i < 0x30000; i += 4) अणु
		पढ़ो_nic_dword(priv->net_dev, i, &पंचांगp);
		अगर (mode == SEARCH_SNAPSHOT)
			*(u32 *) SNAPSHOT_ADDR(i) = पंचांगp;
		अगर (ret == SEARCH_FAIL) अणु
			d = (u8 *) & पंचांगp;
			क्रम (j = 0; j < 4; j++) अणु
				अगर (*s != *d) अणु
					s = in_buf;
					जारी;
				पूर्ण

				s++;
				d++;

				अगर ((s - in_buf) == len)
					ret = (i + j) - len + 1;
			पूर्ण
		पूर्ण अन्यथा अगर (mode == SEARCH_DISCARD)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 *
 * 0) Disconnect the SKB from the firmware (just unmap)
 * 1) Pack the ETH header पूर्णांकo the SKB
 * 2) Pass the SKB to the network stack
 *
 * When packet is provided by the firmware, it contains the following:
 *
 * .  libipw_hdr
 * .  libipw_snap_hdr
 *
 * The size of the स्थिरructed ethernet
 *
 */
#अगर_घोषित IPW2100_RX_DEBUG
अटल u8 packet_data[IPW_RX_NIC_BUFFER_LENGTH];
#पूर्ण_अगर

अटल व्योम ipw2100_corruption_detected(काष्ठा ipw2100_priv *priv, पूर्णांक i)
अणु
#अगर_घोषित IPW2100_DEBUG_C3
	काष्ठा ipw2100_status *status = &priv->status_queue.drv[i];
	u32 match, reg;
	पूर्णांक j;
#पूर्ण_अगर

	IPW_DEBUG_INFO(": PCI latency error detected at 0x%04zX.\n",
		       i * माप(काष्ठा ipw2100_status));

#अगर_घोषित IPW2100_DEBUG_C3
	/* Halt the firmware so we can get a good image */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_STOP_MASTER);
	j = 5;
	करो अणु
		udelay(IPW_WAIT_RESET_MASTER_ASSERT_COMPLETE_DELAY);
		पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_RESET_REG, &reg);

		अगर (reg & IPW_AUX_HOST_RESET_REG_MASTER_DISABLED)
			अवरोध;
	पूर्ण जबतक (j--);

	match = ipw2100_match_buf(priv, (u8 *) status,
				  माप(काष्ठा ipw2100_status),
				  SEARCH_SNAPSHOT);
	अगर (match < SEARCH_SUCCESS)
		IPW_DEBUG_INFO("%s: DMA status match in Firmware at "
			       "offset 0x%06X, length %d:\n",
			       priv->net_dev->name, match,
			       माप(काष्ठा ipw2100_status));
	अन्यथा
		IPW_DEBUG_INFO("%s: No DMA status match in "
			       "Firmware.\n", priv->net_dev->name);

	prपूर्णांकk_buf((u8 *) priv->status_queue.drv,
		   माप(काष्ठा ipw2100_status) * RX_QUEUE_LENGTH);
#पूर्ण_अगर

	priv->fatal_error = IPW2100_ERR_C3_CORRUPTION;
	priv->net_dev->stats.rx_errors++;
	schedule_reset(priv);
पूर्ण

अटल व्योम isr_rx(काष्ठा ipw2100_priv *priv, पूर्णांक i,
			  काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	काष्ठा ipw2100_status *status = &priv->status_queue.drv[i];
	काष्ठा ipw2100_rx_packet *packet = &priv->rx_buffers[i];

	IPW_DEBUG_RX("Handler...\n");

	अगर (unlikely(status->frame_size > skb_tailroom(packet->skb))) अणु
		IPW_DEBUG_INFO("%s: frame_size (%u) > skb_tailroom (%u)!"
			       "  Dropping.\n",
			       dev->name,
			       status->frame_size, skb_tailroom(packet->skb));
		dev->stats.rx_errors++;
		वापस;
	पूर्ण

	अगर (unlikely(!netअगर_running(dev))) अणु
		dev->stats.rx_errors++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		वापस;
	पूर्ण

	अगर (unlikely(priv->ieee->iw_mode != IW_MODE_MONITOR &&
		     !(priv->status & STATUS_ASSOCIATED))) अणु
		IPW_DEBUG_DROP("Dropping packet while not associated.\n");
		priv->wstats.discard.misc++;
		वापस;
	पूर्ण

	dma_unmap_single(&priv->pci_dev->dev, packet->dma_addr,
			 माप(काष्ठा ipw2100_rx), DMA_FROM_DEVICE);

	skb_put(packet->skb, status->frame_size);

#अगर_घोषित IPW2100_RX_DEBUG
	/* Make a copy of the frame so we can dump it to the logs अगर
	 * libipw_rx fails */
	skb_copy_from_linear_data(packet->skb, packet_data,
				  min_t(u32, status->frame_size,
					     IPW_RX_NIC_BUFFER_LENGTH));
#पूर्ण_अगर

	अगर (!libipw_rx(priv->ieee, packet->skb, stats)) अणु
#अगर_घोषित IPW2100_RX_DEBUG
		IPW_DEBUG_DROP("%s: Non consumed packet:\n",
			       dev->name);
		prपूर्णांकk_buf(IPW_DL_DROP, packet_data, status->frame_size);
#पूर्ण_अगर
		dev->stats.rx_errors++;

		/* libipw_rx failed, so it didn't मुक्त the SKB */
		dev_kमुक्त_skb_any(packet->skb);
		packet->skb = शून्य;
	पूर्ण

	/* We need to allocate a new SKB and attach it to the RDB. */
	अगर (unlikely(ipw2100_alloc_skb(priv, packet))) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": "
		       "%s: Unable to allocate SKB onto RBD ring - disabling "
		       "adapter.\n", dev->name);
		/* TODO: schedule adapter shutकरोwn */
		IPW_DEBUG_INFO("TODO: Shutdown adapter...\n");
	पूर्ण

	/* Update the RDB entry */
	priv->rx_queue.drv[i].host_addr = packet->dma_addr;
पूर्ण

#अगर_घोषित CONFIG_IPW2100_MONITOR

अटल व्योम isr_rx_monitor(काष्ठा ipw2100_priv *priv, पूर्णांक i,
		   काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	काष्ठा ipw2100_status *status = &priv->status_queue.drv[i];
	काष्ठा ipw2100_rx_packet *packet = &priv->rx_buffers[i];

	/* Magic काष्ठा that slots पूर्णांकo the radiotap header -- no reason
	 * to build this manually element by element, we can ग_लिखो it much
	 * more efficiently than we can parse it. ORDER MATTERS HERE */
	काष्ठा ipw_rt_hdr अणु
		काष्ठा ieee80211_radiotap_header rt_hdr;
		s8 rt_dbmसंकेत; /* संकेत in dbM, kluged to चिन्हित */
	पूर्ण *ipw_rt;

	IPW_DEBUG_RX("Handler...\n");

	अगर (unlikely(status->frame_size > skb_tailroom(packet->skb) -
				माप(काष्ठा ipw_rt_hdr))) अणु
		IPW_DEBUG_INFO("%s: frame_size (%u) > skb_tailroom (%u)!"
			       "  Dropping.\n",
			       dev->name,
			       status->frame_size,
			       skb_tailroom(packet->skb));
		dev->stats.rx_errors++;
		वापस;
	पूर्ण

	अगर (unlikely(!netअगर_running(dev))) अणु
		dev->stats.rx_errors++;
		priv->wstats.discard.misc++;
		IPW_DEBUG_DROP("Dropping packet while interface is not up.\n");
		वापस;
	पूर्ण

	अगर (unlikely(priv->config & CFG_CRC_CHECK &&
		     status->flags & IPW_STATUS_FLAG_CRC_ERROR)) अणु
		IPW_DEBUG_RX("CRC error in packet.  Dropping.\n");
		dev->stats.rx_errors++;
		वापस;
	पूर्ण

	dma_unmap_single(&priv->pci_dev->dev, packet->dma_addr,
			 माप(काष्ठा ipw2100_rx), DMA_FROM_DEVICE);
	स_हटाओ(packet->skb->data + माप(काष्ठा ipw_rt_hdr),
		packet->skb->data, status->frame_size);

	ipw_rt = (काष्ठा ipw_rt_hdr *) packet->skb->data;

	ipw_rt->rt_hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	ipw_rt->rt_hdr.it_pad = 0; /* always good to zero */
	ipw_rt->rt_hdr.it_len = cpu_to_le16(माप(काष्ठा ipw_rt_hdr)); /* total hdr+data */

	ipw_rt->rt_hdr.it_present = cpu_to_le32(1 << IEEE80211_RADIOTAP_DBM_ANTSIGNAL);

	ipw_rt->rt_dbmसंकेत = status->rssi + IPW2100_RSSI_TO_DBM;

	skb_put(packet->skb, status->frame_size + माप(काष्ठा ipw_rt_hdr));

	अगर (!libipw_rx(priv->ieee, packet->skb, stats)) अणु
		dev->stats.rx_errors++;

		/* libipw_rx failed, so it didn't मुक्त the SKB */
		dev_kमुक्त_skb_any(packet->skb);
		packet->skb = शून्य;
	पूर्ण

	/* We need to allocate a new SKB and attach it to the RDB. */
	अगर (unlikely(ipw2100_alloc_skb(priv, packet))) अणु
		IPW_DEBUG_WARNING(
			"%s: Unable to allocate SKB onto RBD ring - disabling "
			"adapter.\n", dev->name);
		/* TODO: schedule adapter shutकरोwn */
		IPW_DEBUG_INFO("TODO: Shutdown adapter...\n");
	पूर्ण

	/* Update the RDB entry */
	priv->rx_queue.drv[i].host_addr = packet->dma_addr;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ipw2100_corruption_check(काष्ठा ipw2100_priv *priv, पूर्णांक i)
अणु
	काष्ठा ipw2100_status *status = &priv->status_queue.drv[i];
	काष्ठा ipw2100_rx *u = priv->rx_buffers[i].rxp;
	u16 frame_type = status->status_fields & STATUS_TYPE_MASK;

	चयन (frame_type) अणु
	हाल COMMAND_STATUS_VAL:
		वापस (status->frame_size != माप(u->rx_data.command));
	हाल STATUS_CHANGE_VAL:
		वापस (status->frame_size != माप(u->rx_data.status));
	हाल HOST_NOTIFICATION_VAL:
		वापस (status->frame_size < माप(u->rx_data.notअगरication));
	हाल P80211_DATA_VAL:
	हाल P8023_DATA_VAL:
#अगर_घोषित CONFIG_IPW2100_MONITOR
		वापस 0;
#अन्यथा
		चयन (WLAN_FC_GET_TYPE(le16_to_cpu(u->rx_data.header.frame_ctl))) अणु
		हाल IEEE80211_FTYPE_MGMT:
		हाल IEEE80211_FTYPE_CTL:
			वापस 0;
		हाल IEEE80211_FTYPE_DATA:
			वापस (status->frame_size >
				IPW_MAX_802_11_PAYLOAD_LENGTH);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 1;
पूर्ण

/*
 * ipw2100 पूर्णांकerrupts are disabled at this poपूर्णांक, and the ISR
 * is the only code that calls this method.  So, we करो not need
 * to play with any locks.
 *
 * RX Queue works as follows:
 *
 * Read index - firmware places packet in entry identअगरied by the
 *              Read index and advances Read index.  In this manner,
 *              Read index will always poपूर्णांक to the next packet to
 *              be filled--but not yet valid.
 *
 * Write index - driver fills this entry with an unused RBD entry.
 *               This entry has not filled by the firmware yet.
 *
 * In between the W and R indexes are the RBDs that have been received
 * but not yet processed.
 *
 * The process of handling packets will start at WRITE + 1 and advance
 * until it reaches the READ index.
 *
 * The WRITE index is cached in the variable 'priv->rx_queue.next'.
 *
 */
अटल व्योम __ipw2100_rx_process(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा ipw2100_bd_queue *rxq = &priv->rx_queue;
	काष्ठा ipw2100_status_queue *sq = &priv->status_queue;
	काष्ठा ipw2100_rx_packet *packet;
	u16 frame_type;
	u32 r, w, i, s;
	काष्ठा ipw2100_rx *u;
	काष्ठा libipw_rx_stats stats = अणु
		.mac_समय = jअगरfies,
	पूर्ण;

	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_RX_READ_INDEX, &r);
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_RX_WRITE_INDEX, &w);

	अगर (r >= rxq->entries) अणु
		IPW_DEBUG_RX("exit - bad read index\n");
		वापस;
	पूर्ण

	i = (rxq->next + 1) % rxq->entries;
	s = i;
	जबतक (i != r) अणु
		/* IPW_DEBUG_RX("r = %d : w = %d : processing = %d\n",
		   r, rxq->next, i); */

		packet = &priv->rx_buffers[i];

		/* Sync the DMA क्रम the RX buffer so CPU is sure to get
		 * the correct values */
		dma_sync_single_क्रम_cpu(&priv->pci_dev->dev, packet->dma_addr,
					माप(काष्ठा ipw2100_rx),
					DMA_FROM_DEVICE);

		अगर (unlikely(ipw2100_corruption_check(priv, i))) अणु
			ipw2100_corruption_detected(priv, i);
			जाओ increment;
		पूर्ण

		u = packet->rxp;
		frame_type = sq->drv[i].status_fields & STATUS_TYPE_MASK;
		stats.rssi = sq->drv[i].rssi + IPW2100_RSSI_TO_DBM;
		stats.len = sq->drv[i].frame_size;

		stats.mask = 0;
		अगर (stats.rssi != 0)
			stats.mask |= LIBIPW_STATMASK_RSSI;
		stats.freq = LIBIPW_24GHZ_BAND;

		IPW_DEBUG_RX("%s: '%s' frame type received (%d).\n",
			     priv->net_dev->name, frame_types[frame_type],
			     stats.len);

		चयन (frame_type) अणु
		हाल COMMAND_STATUS_VAL:
			/* Reset Rx watchकरोg */
			isr_rx_complete_command(priv, &u->rx_data.command);
			अवरोध;

		हाल STATUS_CHANGE_VAL:
			isr_status_change(priv, u->rx_data.status);
			अवरोध;

		हाल P80211_DATA_VAL:
		हाल P8023_DATA_VAL:
#अगर_घोषित CONFIG_IPW2100_MONITOR
			अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
				isr_rx_monitor(priv, i, &stats);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			अगर (stats.len < माप(काष्ठा libipw_hdr_3addr))
				अवरोध;
			चयन (WLAN_FC_GET_TYPE(le16_to_cpu(u->rx_data.header.frame_ctl))) अणु
			हाल IEEE80211_FTYPE_MGMT:
				libipw_rx_mgt(priv->ieee,
						 &u->rx_data.header, &stats);
				अवरोध;

			हाल IEEE80211_FTYPE_CTL:
				अवरोध;

			हाल IEEE80211_FTYPE_DATA:
				isr_rx(priv, i, &stats);
				अवरोध;

			पूर्ण
			अवरोध;
		पूर्ण

	      increment:
		/* clear status field associated with this RBD */
		rxq->drv[i].status.info.field = 0;

		i = (i + 1) % rxq->entries;
	पूर्ण

	अगर (i != s) अणु
		/* backtrack one entry, wrapping to end अगर at 0 */
		rxq->next = (i ? i : rxq->entries) - 1;

		ग_लिखो_रेजिस्टर(priv->net_dev,
			       IPW_MEM_HOST_SHARED_RX_WRITE_INDEX, rxq->next);
	पूर्ण
पूर्ण

/*
 * __ipw2100_tx_process
 *
 * This routine will determine whether the next packet on
 * the fw_pend_list has been processed by the firmware yet.
 *
 * If not, then it करोes nothing and वापसs.
 *
 * If so, then it हटाओs the item from the fw_pend_list, मुक्तs
 * any associated storage, and places the item back on the
 * मुक्त list of its source (either msg_मुक्त_list or tx_मुक्त_list)
 *
 * TX Queue works as follows:
 *
 * Read index - poपूर्णांकs to the next TBD that the firmware will
 *              process.  The firmware will पढ़ो the data, and once
 *              करोne processing, it will advance the Read index.
 *
 * Write index - driver fills this entry with an स्थिरructed TBD
 *               entry.  The Write index is not advanced until the
 *               packet has been configured.
 *
 * In between the W and R indexes are the TBDs that have NOT been
 * processed.  Lagging behind the R index are packets that have
 * been processed but have not been मुक्तd by the driver.
 *
 * In order to मुक्त old storage, an पूर्णांकernal index will be मुख्यtained
 * that poपूर्णांकs to the next packet to be मुक्तd.  When all used
 * packets have been मुक्तd, the oldest index will be the same as the
 * firmware's पढ़ो index.
 *
 * The OLDEST index is cached in the variable 'priv->tx_queue.oldest'
 *
 * Because the TBD काष्ठाure can not contain arbitrary data, the
 * driver must keep an पूर्णांकernal queue of cached allocations such that
 * it can put that data back पूर्णांकo the tx_मुक्त_list and msg_मुक्त_list
 * क्रम use by future command and data packets.
 *
 */
अटल पूर्णांक __ipw2100_tx_process(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा ipw2100_bd_queue *txq = &priv->tx_queue;
	काष्ठा ipw2100_bd *tbd;
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;
	पूर्णांक descriptors_used;
	पूर्णांक e, i;
	u32 r, w, frag_num = 0;

	अगर (list_empty(&priv->fw_pend_list))
		वापस 0;

	element = priv->fw_pend_list.next;

	packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);
	tbd = &txq->drv[packet->index];

	/* Determine how many TBD entries must be finished... */
	चयन (packet->type) अणु
	हाल COMMAND:
		/* COMMAND uses only one slot; करोn't advance */
		descriptors_used = 1;
		e = txq->oldest;
		अवरोध;

	हाल DATA:
		/* DATA uses two slots; advance and loop position. */
		descriptors_used = tbd->num_fragments;
		frag_num = tbd->num_fragments - 1;
		e = txq->oldest + frag_num;
		e %= txq->entries;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING DRV_NAME ": %s: Bad fw_pend_list entry!\n",
		       priv->net_dev->name);
		वापस 0;
	पूर्ण

	/* अगर the last TBD is not करोne by NIC yet, then packet is
	 * not पढ़ोy to be released.
	 *
	 */
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_TX_QUEUE_READ_INDEX,
		      &r);
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX,
		      &w);
	अगर (w != txq->next)
		prपूर्णांकk(KERN_WARNING DRV_NAME ": %s: write index mismatch\n",
		       priv->net_dev->name);

	/*
	 * txq->next is the index of the last packet written txq->oldest is
	 * the index of the r is the index of the next packet to be पढ़ो by
	 * firmware
	 */

	/*
	 * Quick graphic to help you visualize the following
	 * अगर / अन्यथा statement
	 *
	 * ===>|                     s---->|===============
	 *                               e>|
	 * | a | b | c | d | e | f | g | h | i | j | k | l
	 *       r---->|
	 *               w
	 *
	 * w - updated by driver
	 * r - updated by firmware
	 * s - start of oldest BD entry (txq->oldest)
	 * e - end of oldest BD entry
	 *
	 */
	अगर (!((r <= w && (e < r || e >= w)) || (e < r && e >= w))) अणु
		IPW_DEBUG_TX("exit - no processed packets ready to release.\n");
		वापस 0;
	पूर्ण

	list_del(element);
	DEC_STAT(&priv->fw_pend_stat);

#अगर_घोषित CONFIG_IPW2100_DEBUG
	अणु
		i = txq->oldest;
		IPW_DEBUG_TX("TX%d V=%p P=%04X T=%04X L=%d\n", i,
			     &txq->drv[i],
			     (u32) (txq->nic + i * माप(काष्ठा ipw2100_bd)),
			     txq->drv[i].host_addr, txq->drv[i].buf_length);

		अगर (packet->type == DATA) अणु
			i = (i + 1) % txq->entries;

			IPW_DEBUG_TX("TX%d V=%p P=%04X T=%04X L=%d\n", i,
				     &txq->drv[i],
				     (u32) (txq->nic + i *
					    माप(काष्ठा ipw2100_bd)),
				     (u32) txq->drv[i].host_addr,
				     txq->drv[i].buf_length);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	चयन (packet->type) अणु
	हाल DATA:
		अगर (txq->drv[txq->oldest].status.info.fields.txType != 0)
			prपूर्णांकk(KERN_WARNING DRV_NAME ": %s: Queue mismatch.  "
			       "Expecting DATA TBD but pulled "
			       "something else: ids %d=%d.\n",
			       priv->net_dev->name, txq->oldest, packet->index);

		/* DATA packet; we have to unmap and मुक्त the SKB */
		क्रम (i = 0; i < frag_num; i++) अणु
			tbd = &txq->drv[(packet->index + 1 + i) % txq->entries];

			IPW_DEBUG_TX("TX%d P=%08x L=%d\n",
				     (packet->index + 1 + i) % txq->entries,
				     tbd->host_addr, tbd->buf_length);

			dma_unmap_single(&priv->pci_dev->dev, tbd->host_addr,
					 tbd->buf_length, DMA_TO_DEVICE);
		पूर्ण

		libipw_txb_मुक्त(packet->info.d_काष्ठा.txb);
		packet->info.d_काष्ठा.txb = शून्य;

		list_add_tail(element, &priv->tx_मुक्त_list);
		INC_STAT(&priv->tx_मुक्त_stat);

		/* We have a मुक्त slot in the Tx queue, so wake up the
		 * transmit layer अगर it is stopped. */
		अगर (priv->status & STATUS_ASSOCIATED)
			netअगर_wake_queue(priv->net_dev);

		/* A packet was processed by the hardware, so update the
		 * watchकरोg */
		netअगर_trans_update(priv->net_dev);

		अवरोध;

	हाल COMMAND:
		अगर (txq->drv[txq->oldest].status.info.fields.txType != 1)
			prपूर्णांकk(KERN_WARNING DRV_NAME ": %s: Queue mismatch.  "
			       "Expecting COMMAND TBD but pulled "
			       "something else: ids %d=%d.\n",
			       priv->net_dev->name, txq->oldest, packet->index);

#अगर_घोषित CONFIG_IPW2100_DEBUG
		अगर (packet->info.c_काष्ठा.cmd->host_command_reg <
		    ARRAY_SIZE(command_types))
			IPW_DEBUG_TX("Command '%s (%d)' processed: %d.\n",
				     command_types[packet->info.c_काष्ठा.cmd->
						   host_command_reg],
				     packet->info.c_काष्ठा.cmd->
				     host_command_reg,
				     packet->info.c_काष्ठा.cmd->cmd_status_reg);
#पूर्ण_अगर

		list_add_tail(element, &priv->msg_मुक्त_list);
		INC_STAT(&priv->msg_मुक्त_stat);
		अवरोध;
	पूर्ण

	/* advance oldest used TBD poपूर्णांकer to start of next entry */
	txq->oldest = (e + 1) % txq->entries;
	/* increase available TBDs number */
	txq->available += descriptors_used;
	SET_STAT(&priv->txq_stat, txq->available);

	IPW_DEBUG_TX("packet latency (send to process)  %ld jiffies\n",
		     jअगरfies - packet->jअगरfy_start);

	वापस (!list_empty(&priv->fw_pend_list));
पूर्ण

अटल अंतरभूत व्योम __ipw2100_tx_complete(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i = 0;

	जबतक (__ipw2100_tx_process(priv) && i < 200)
		i++;

	अगर (i == 200) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": "
		       "%s: Driver is running slow (%d iters).\n",
		       priv->net_dev->name, i);
	पूर्ण
पूर्ण

अटल व्योम ipw2100_tx_send_commands(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;
	काष्ठा ipw2100_bd_queue *txq = &priv->tx_queue;
	काष्ठा ipw2100_bd *tbd;
	पूर्णांक next = txq->next;

	जबतक (!list_empty(&priv->msg_pend_list)) अणु
		/* अगर there isn't enough space in TBD queue, then
		 * करोn't stuff a new one in.
		 * NOTE: 3 are needed as a command will take one,
		 *       and there is a minimum of 2 that must be
		 *       मुख्यtained between the r and w indexes
		 */
		अगर (txq->available <= 3) अणु
			IPW_DEBUG_TX("no room in tx_queue\n");
			अवरोध;
		पूर्ण

		element = priv->msg_pend_list.next;
		list_del(element);
		DEC_STAT(&priv->msg_pend_stat);

		packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);

		IPW_DEBUG_TX("using TBD at virt=%p, phys=%04X\n",
			     &txq->drv[txq->next],
			     (u32) (txq->nic + txq->next *
				      माप(काष्ठा ipw2100_bd)));

		packet->index = txq->next;

		tbd = &txq->drv[txq->next];

		/* initialize TBD */
		tbd->host_addr = packet->info.c_काष्ठा.cmd_phys;
		tbd->buf_length = माप(काष्ठा ipw2100_cmd_header);
		/* not marking number of fragments causes problems
		 * with f/w debug version */
		tbd->num_fragments = 1;
		tbd->status.info.field =
		    IPW_BD_STATUS_TX_FRAME_COMMAND |
		    IPW_BD_STATUS_TX_INTERRUPT_ENABLE;

		/* update TBD queue counters */
		txq->next++;
		txq->next %= txq->entries;
		txq->available--;
		DEC_STAT(&priv->txq_stat);

		list_add_tail(element, &priv->fw_pend_list);
		INC_STAT(&priv->fw_pend_stat);
	पूर्ण

	अगर (txq->next != next) अणु
		/* kick off the DMA by notअगरying firmware the
		 * ग_लिखो index has moved; make sure TBD stores are sync'd */
		wmb();
		ग_लिखो_रेजिस्टर(priv->net_dev,
			       IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX,
			       txq->next);
	पूर्ण
पूर्ण

/*
 * ipw2100_tx_send_data
 *
 */
अटल व्योम ipw2100_tx_send_data(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;
	काष्ठा ipw2100_bd_queue *txq = &priv->tx_queue;
	काष्ठा ipw2100_bd *tbd;
	पूर्णांक next = txq->next;
	पूर्णांक i = 0;
	काष्ठा ipw2100_data_header *ipw_hdr;
	काष्ठा libipw_hdr_3addr *hdr;

	जबतक (!list_empty(&priv->tx_pend_list)) अणु
		/* अगर there isn't enough space in TBD queue, then
		 * करोn't stuff a new one in.
		 * NOTE: 4 are needed as a data will take two,
		 *       and there is a minimum of 2 that must be
		 *       मुख्यtained between the r and w indexes
		 */
		element = priv->tx_pend_list.next;
		packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);

		अगर (unlikely(1 + packet->info.d_काष्ठा.txb->nr_frags >
			     IPW_MAX_BDS)) अणु
			/* TODO: Support merging buffers अगर more than
			 * IPW_MAX_BDS are used */
			IPW_DEBUG_INFO("%s: Maximum BD threshold exceeded.  "
				       "Increase fragmentation level.\n",
				       priv->net_dev->name);
		पूर्ण

		अगर (txq->available <= 3 + packet->info.d_काष्ठा.txb->nr_frags) अणु
			IPW_DEBUG_TX("no room in tx_queue\n");
			अवरोध;
		पूर्ण

		list_del(element);
		DEC_STAT(&priv->tx_pend_stat);

		tbd = &txq->drv[txq->next];

		packet->index = txq->next;

		ipw_hdr = packet->info.d_काष्ठा.data;
		hdr = (काष्ठा libipw_hdr_3addr *)packet->info.d_काष्ठा.txb->
		    fragments[0]->data;

		अगर (priv->ieee->iw_mode == IW_MODE_INFRA) अणु
			/* To DS: Addr1 = BSSID, Addr2 = SA,
			   Addr3 = DA */
			स_नकल(ipw_hdr->src_addr, hdr->addr2, ETH_ALEN);
			स_नकल(ipw_hdr->dst_addr, hdr->addr3, ETH_ALEN);
		पूर्ण अन्यथा अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
			/* not From/To DS: Addr1 = DA, Addr2 = SA,
			   Addr3 = BSSID */
			स_नकल(ipw_hdr->src_addr, hdr->addr2, ETH_ALEN);
			स_नकल(ipw_hdr->dst_addr, hdr->addr1, ETH_ALEN);
		पूर्ण

		ipw_hdr->host_command_reg = SEND;
		ipw_hdr->host_command_reg1 = 0;

		/* For now we only support host based encryption */
		ipw_hdr->needs_encryption = 0;
		ipw_hdr->encrypted = packet->info.d_काष्ठा.txb->encrypted;
		अगर (packet->info.d_काष्ठा.txb->nr_frags > 1)
			ipw_hdr->fragment_size =
			    packet->info.d_काष्ठा.txb->frag_size -
			    LIBIPW_3ADDR_LEN;
		अन्यथा
			ipw_hdr->fragment_size = 0;

		tbd->host_addr = packet->info.d_काष्ठा.data_phys;
		tbd->buf_length = माप(काष्ठा ipw2100_data_header);
		tbd->num_fragments = 1 + packet->info.d_काष्ठा.txb->nr_frags;
		tbd->status.info.field =
		    IPW_BD_STATUS_TX_FRAME_802_3 |
		    IPW_BD_STATUS_TX_FRAME_NOT_LAST_FRAGMENT;
		txq->next++;
		txq->next %= txq->entries;

		IPW_DEBUG_TX("data header tbd TX%d P=%08x L=%d\n",
			     packet->index, tbd->host_addr, tbd->buf_length);
#अगर_घोषित CONFIG_IPW2100_DEBUG
		अगर (packet->info.d_काष्ठा.txb->nr_frags > 1)
			IPW_DEBUG_FRAG("fragment Tx: %d frames\n",
				       packet->info.d_काष्ठा.txb->nr_frags);
#पूर्ण_अगर

		क्रम (i = 0; i < packet->info.d_काष्ठा.txb->nr_frags; i++) अणु
			tbd = &txq->drv[txq->next];
			अगर (i == packet->info.d_काष्ठा.txb->nr_frags - 1)
				tbd->status.info.field =
				    IPW_BD_STATUS_TX_FRAME_802_3 |
				    IPW_BD_STATUS_TX_INTERRUPT_ENABLE;
			अन्यथा
				tbd->status.info.field =
				    IPW_BD_STATUS_TX_FRAME_802_3 |
				    IPW_BD_STATUS_TX_FRAME_NOT_LAST_FRAGMENT;

			tbd->buf_length = packet->info.d_काष्ठा.txb->
			    fragments[i]->len - LIBIPW_3ADDR_LEN;

			tbd->host_addr = dma_map_single(&priv->pci_dev->dev,
							packet->info.d_काष्ठा.
							txb->fragments[i]->data +
							LIBIPW_3ADDR_LEN,
							tbd->buf_length,
							DMA_TO_DEVICE);
			अगर (dma_mapping_error(&priv->pci_dev->dev, tbd->host_addr)) अणु
				IPW_DEBUG_TX("dma mapping error\n");
				अवरोध;
			पूर्ण

			IPW_DEBUG_TX("data frag tbd TX%d P=%08x L=%d\n",
				     txq->next, tbd->host_addr,
				     tbd->buf_length);

			dma_sync_single_क्रम_device(&priv->pci_dev->dev,
						   tbd->host_addr,
						   tbd->buf_length,
						   DMA_TO_DEVICE);

			txq->next++;
			txq->next %= txq->entries;
		पूर्ण

		txq->available -= 1 + packet->info.d_काष्ठा.txb->nr_frags;
		SET_STAT(&priv->txq_stat, txq->available);

		list_add_tail(element, &priv->fw_pend_list);
		INC_STAT(&priv->fw_pend_stat);
	पूर्ण

	अगर (txq->next != next) अणु
		/* kick off the DMA by notअगरying firmware the
		 * ग_लिखो index has moved; make sure TBD stores are sync'd */
		ग_लिखो_रेजिस्टर(priv->net_dev,
			       IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX,
			       txq->next);
	पूर्ण
पूर्ण

अटल व्योम ipw2100_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ipw2100_priv *priv = from_tasklet(priv, t, irq_tasklet);
	काष्ठा net_device *dev = priv->net_dev;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकa, पंचांगp;

	spin_lock_irqsave(&priv->low_lock, flags);
	ipw2100_disable_पूर्णांकerrupts(priv);

	पढ़ो_रेजिस्टर(dev, IPW_REG_INTA, &पूर्णांकa);

	IPW_DEBUG_ISR("enter - INTA: 0x%08lX\n",
		      (अचिन्हित दीर्घ)पूर्णांकa & IPW_INTERRUPT_MASK);

	priv->in_isr++;
	priv->पूर्णांकerrupts++;

	/* We करो not loop and keep polling क्रम more पूर्णांकerrupts as this
	 * is frowned upon and करोesn't play nicely with other potentially
	 * chained IRQs */
	IPW_DEBUG_ISR("INTA: 0x%08lX\n",
		      (अचिन्हित दीर्घ)पूर्णांकa & IPW_INTERRUPT_MASK);

	अगर (पूर्णांकa & IPW2100_INTA_FATAL_ERROR) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       ": Fatal interrupt. Scheduling firmware restart.\n");
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_FATAL_ERROR);

		पढ़ो_nic_dword(dev, IPW_NIC_FATAL_ERROR, &priv->fatal_error);
		IPW_DEBUG_INFO("%s: Fatal error value: 0x%08X\n",
			       priv->net_dev->name, priv->fatal_error);

		पढ़ो_nic_dword(dev, IPW_ERROR_ADDR(priv->fatal_error), &पंचांगp);
		IPW_DEBUG_INFO("%s: Fatal error address value: 0x%08X\n",
			       priv->net_dev->name, पंचांगp);

		/* Wake up any sleeping jobs */
		schedule_reset(priv);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_PARITY_ERROR) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": ***** PARITY ERROR INTERRUPT !!!!\n");
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_PARITY_ERROR);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_RX_TRANSFER) अणु
		IPW_DEBUG_ISR("RX interrupt\n");

		priv->rx_पूर्णांकerrupts++;

		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_RX_TRANSFER);

		__ipw2100_rx_process(priv);
		__ipw2100_tx_complete(priv);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_TX_TRANSFER) अणु
		IPW_DEBUG_ISR("TX interrupt\n");

		priv->tx_पूर्णांकerrupts++;

		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_TX_TRANSFER);

		__ipw2100_tx_complete(priv);
		ipw2100_tx_send_commands(priv);
		ipw2100_tx_send_data(priv);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_TX_COMPLETE) अणु
		IPW_DEBUG_ISR("TX complete\n");
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_TX_COMPLETE);

		__ipw2100_tx_complete(priv);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_EVENT_INTERRUPT) अणु
		/* ipw2100_handle_event(dev); */
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_EVENT_INTERRUPT);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_FW_INIT_DONE) अणु
		IPW_DEBUG_ISR("FW init done interrupt\n");
		priv->पूर्णांकa_other++;

		पढ़ो_रेजिस्टर(dev, IPW_REG_INTA, &पंचांगp);
		अगर (पंचांगp & (IPW2100_INTA_FATAL_ERROR |
			   IPW2100_INTA_PARITY_ERROR)) अणु
			ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA,
				       IPW2100_INTA_FATAL_ERROR |
				       IPW2100_INTA_PARITY_ERROR);
		पूर्ण

		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_FW_INIT_DONE);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_STATUS_CHANGE) अणु
		IPW_DEBUG_ISR("Status change interrupt\n");
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA, IPW2100_INTA_STATUS_CHANGE);
	पूर्ण

	अगर (पूर्णांकa & IPW2100_INTA_SLAVE_MODE_HOST_COMMAND_DONE) अणु
		IPW_DEBUG_ISR("slave host mode interrupt\n");
		priv->पूर्णांकa_other++;
		ग_लिखो_रेजिस्टर(dev, IPW_REG_INTA,
			       IPW2100_INTA_SLAVE_MODE_HOST_COMMAND_DONE);
	पूर्ण

	priv->in_isr--;
	ipw2100_enable_पूर्णांकerrupts(priv);

	spin_unlock_irqrestore(&priv->low_lock, flags);

	IPW_DEBUG_ISR("exit\n");
पूर्ण

अटल irqवापस_t ipw2100_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ipw2100_priv *priv = data;
	u32 पूर्णांकa, पूर्णांकa_mask;

	अगर (!data)
		वापस IRQ_NONE;

	spin_lock(&priv->low_lock);

	/* We check to see अगर we should be ignoring पूर्णांकerrupts beक्रमe
	 * we touch the hardware.  During ucode load अगर we try and handle
	 * an पूर्णांकerrupt we can cause keyboard problems as well as cause
	 * the ucode to fail to initialize */
	अगर (!(priv->status & STATUS_INT_ENABLED)) अणु
		/* Shared IRQ */
		जाओ none;
	पूर्ण

	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_INTA_MASK, &पूर्णांकa_mask);
	पढ़ो_रेजिस्टर(priv->net_dev, IPW_REG_INTA, &पूर्णांकa);

	अगर (पूर्णांकa == 0xFFFFFFFF) अणु
		/* Hardware disappeared */
		prपूर्णांकk(KERN_WARNING DRV_NAME ": IRQ INTA == 0xFFFFFFFF\n");
		जाओ none;
	पूर्ण

	पूर्णांकa &= IPW_INTERRUPT_MASK;

	अगर (!(पूर्णांकa & पूर्णांकa_mask)) अणु
		/* Shared पूर्णांकerrupt */
		जाओ none;
	पूर्ण

	/* We disable the hardware पूर्णांकerrupt here just to prevent unneeded
	 * calls to be made.  We disable this again within the actual
	 * work tasklet, so अगर another part of the code re-enables the
	 * पूर्णांकerrupt, that is fine */
	ipw2100_disable_पूर्णांकerrupts(priv);

	tasklet_schedule(&priv->irq_tasklet);
	spin_unlock(&priv->low_lock);

	वापस IRQ_HANDLED;
      none:
	spin_unlock(&priv->low_lock);
	वापस IRQ_NONE;
पूर्ण

अटल netdev_tx_t ipw2100_tx(काष्ठा libipw_txb *txb,
			      काष्ठा net_device *dev, पूर्णांक pri)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->low_lock, flags);

	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		IPW_DEBUG_INFO("Can not transmit when not connected.\n");
		priv->net_dev->stats.tx_carrier_errors++;
		netअगर_stop_queue(dev);
		जाओ fail_unlock;
	पूर्ण

	अगर (list_empty(&priv->tx_मुक्त_list))
		जाओ fail_unlock;

	element = priv->tx_मुक्त_list.next;
	packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);

	packet->info.d_काष्ठा.txb = txb;

	IPW_DEBUG_TX("Sending fragment (%d bytes):\n", txb->fragments[0]->len);
	prपूर्णांकk_buf(IPW_DL_TX, txb->fragments[0]->data, txb->fragments[0]->len);

	packet->jअगरfy_start = jअगरfies;

	list_del(element);
	DEC_STAT(&priv->tx_मुक्त_stat);

	list_add_tail(element, &priv->tx_pend_list);
	INC_STAT(&priv->tx_pend_stat);

	ipw2100_tx_send_data(priv);

	spin_unlock_irqrestore(&priv->low_lock, flags);
	वापस NETDEV_TX_OK;

fail_unlock:
	netअगर_stop_queue(dev);
	spin_unlock_irqrestore(&priv->low_lock, flags);
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल पूर्णांक ipw2100_msg_allocate(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i, j, err = -EINVAL;
	व्योम *v;
	dma_addr_t p;

	priv->msg_buffers =
	    kदो_स्मृति_array(IPW_COMMAND_POOL_SIZE,
			  माप(काष्ठा ipw2100_tx_packet),
			  GFP_KERNEL);
	अगर (!priv->msg_buffers)
		वापस -ENOMEM;

	क्रम (i = 0; i < IPW_COMMAND_POOL_SIZE; i++) अणु
		v = dma_alloc_coherent(&priv->pci_dev->dev,
				       माप(काष्ठा ipw2100_cmd_header), &p,
				       GFP_KERNEL);
		अगर (!v) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME ": "
			       "%s: PCI alloc failed for msg "
			       "buffers.\n", priv->net_dev->name);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		priv->msg_buffers[i].type = COMMAND;
		priv->msg_buffers[i].info.c_काष्ठा.cmd =
		    (काष्ठा ipw2100_cmd_header *)v;
		priv->msg_buffers[i].info.c_काष्ठा.cmd_phys = p;
	पूर्ण

	अगर (i == IPW_COMMAND_POOL_SIZE)
		वापस 0;

	क्रम (j = 0; j < i; j++) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev,
				  माप(काष्ठा ipw2100_cmd_header),
				  priv->msg_buffers[j].info.c_काष्ठा.cmd,
				  priv->msg_buffers[j].info.c_काष्ठा.cmd_phys);
	पूर्ण

	kमुक्त(priv->msg_buffers);
	priv->msg_buffers = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_msg_initialize(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&priv->msg_मुक्त_list);
	INIT_LIST_HEAD(&priv->msg_pend_list);

	क्रम (i = 0; i < IPW_COMMAND_POOL_SIZE; i++)
		list_add_tail(&priv->msg_buffers[i].list, &priv->msg_मुक्त_list);
	SET_STAT(&priv->msg_मुक्त_stat, i);

	वापस 0;
पूर्ण

अटल व्योम ipw2100_msg_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;

	अगर (!priv->msg_buffers)
		वापस;

	क्रम (i = 0; i < IPW_COMMAND_POOL_SIZE; i++) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev,
				  माप(काष्ठा ipw2100_cmd_header),
				  priv->msg_buffers[i].info.c_काष्ठा.cmd,
				  priv->msg_buffers[i].info.c_काष्ठा.cmd_phys);
	पूर्ण

	kमुक्त(priv->msg_buffers);
	priv->msg_buffers = शून्य;
पूर्ण

अटल sमाप_प्रकार show_pci(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(d);
	अक्षर *out = buf;
	पूर्णांक i, j;
	u32 val;

	क्रम (i = 0; i < 16; i++) अणु
		out += प्र_लिखो(out, "[%08X] ", i * 16);
		क्रम (j = 0; j < 16; j += 4) अणु
			pci_पढ़ो_config_dword(pci_dev, i * 16 + j, &val);
			out += प्र_लिखो(out, "%08X ", val);
		पूर्ण
		out += प्र_लिखो(out, "\n");
	पूर्ण

	वापस out - buf;
पूर्ण

अटल DEVICE_ATTR(pci, 0444, show_pci, शून्य);

अटल sमाप_प्रकार show_cfg(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *p = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)p->config);
पूर्ण

अटल DEVICE_ATTR(cfg, 0444, show_cfg, शून्य);

अटल sमाप_प्रकार show_status(काष्ठा device *d, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *p = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)p->status);
पूर्ण

अटल DEVICE_ATTR(status, 0444, show_status, शून्य);

अटल sमाप_प्रकार show_capability(काष्ठा device *d, काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *p = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08x\n", (पूर्णांक)p->capability);
पूर्ण

अटल DEVICE_ATTR(capability, 0444, show_capability, शून्य);

#घोषणा IPW2100_REG(x) अणु IPW_ ##x, #x पूर्ण
अटल स्थिर काष्ठा अणु
	u32 addr;
	स्थिर अक्षर *name;
पूर्ण hw_data[] = अणु
IPW2100_REG(REG_GP_CNTRL),
	    IPW2100_REG(REG_GPIO),
	    IPW2100_REG(REG_INTA),
	    IPW2100_REG(REG_INTA_MASK), IPW2100_REG(REG_RESET_REG),पूर्ण;
#घोषणा IPW2100_NIC(x, s) अणु x, #x, s पूर्ण
अटल स्थिर काष्ठा अणु
	u32 addr;
	स्थिर अक्षर *name;
	माप_प्रकार size;
पूर्ण nic_data[] = अणु
IPW2100_NIC(IPW2100_CONTROL_REG, 2),
	    IPW2100_NIC(0x210014, 1), IPW2100_NIC(0x210000, 1),पूर्ण;
#घोषणा IPW2100_ORD(x, d) अणु IPW_ORD_ ##x, #x, d पूर्ण
अटल स्थिर काष्ठा अणु
	u8 index;
	स्थिर अक्षर *name;
	स्थिर अक्षर *desc;
पूर्ण ord_data[] = अणु
IPW2100_ORD(STAT_TX_HOST_REQUESTS, "requested Host Tx's (MSDU)"),
	    IPW2100_ORD(STAT_TX_HOST_COMPLETE,
				"successful Host Tx's (MSDU)"),
	    IPW2100_ORD(STAT_TX_सूची_DATA,
				"successful Directed Tx's (MSDU)"),
	    IPW2100_ORD(STAT_TX_सूची_DATA1,
				"successful Directed Tx's (MSDU) @ 1MB"),
	    IPW2100_ORD(STAT_TX_सूची_DATA2,
				"successful Directed Tx's (MSDU) @ 2MB"),
	    IPW2100_ORD(STAT_TX_सूची_DATA5_5,
				"successful Directed Tx's (MSDU) @ 5_5MB"),
	    IPW2100_ORD(STAT_TX_सूची_DATA11,
				"successful Directed Tx's (MSDU) @ 11MB"),
	    IPW2100_ORD(STAT_TX_NOसूची_DATA1,
				"successful Non_Directed Tx's (MSDU) @ 1MB"),
	    IPW2100_ORD(STAT_TX_NOसूची_DATA2,
				"successful Non_Directed Tx's (MSDU) @ 2MB"),
	    IPW2100_ORD(STAT_TX_NOसूची_DATA5_5,
				"successful Non_Directed Tx's (MSDU) @ 5.5MB"),
	    IPW2100_ORD(STAT_TX_NOसूची_DATA11,
				"successful Non_Directed Tx's (MSDU) @ 11MB"),
	    IPW2100_ORD(STAT_शून्य_DATA, "successful NULL data Tx's"),
	    IPW2100_ORD(STAT_TX_RTS, "successful Tx RTS"),
	    IPW2100_ORD(STAT_TX_CTS, "successful Tx CTS"),
	    IPW2100_ORD(STAT_TX_ACK, "successful Tx ACK"),
	    IPW2100_ORD(STAT_TX_ASSN, "successful Association Tx's"),
	    IPW2100_ORD(STAT_TX_ASSN_RESP,
				"successful Association response Tx's"),
	    IPW2100_ORD(STAT_TX_REASSN,
				"successful Reassociation Tx's"),
	    IPW2100_ORD(STAT_TX_REASSN_RESP,
				"successful Reassociation response Tx's"),
	    IPW2100_ORD(STAT_TX_PROBE,
				"probes successfully transmitted"),
	    IPW2100_ORD(STAT_TX_PROBE_RESP,
				"probe responses successfully transmitted"),
	    IPW2100_ORD(STAT_TX_BEACON, "tx beacon"),
	    IPW2100_ORD(STAT_TX_ATIM, "Tx ATIM"),
	    IPW2100_ORD(STAT_TX_DISASSN,
				"successful Disassociation TX"),
	    IPW2100_ORD(STAT_TX_AUTH, "successful Authentication Tx"),
	    IPW2100_ORD(STAT_TX_DEAUTH,
				"successful Deauthentication TX"),
	    IPW2100_ORD(STAT_TX_TOTAL_BYTES,
				"Total successful Tx data bytes"),
	    IPW2100_ORD(STAT_TX_RETRIES, "Tx retries"),
	    IPW2100_ORD(STAT_TX_RETRY1, "Tx retries at 1MBPS"),
	    IPW2100_ORD(STAT_TX_RETRY2, "Tx retries at 2MBPS"),
	    IPW2100_ORD(STAT_TX_RETRY5_5, "Tx retries at 5.5MBPS"),
	    IPW2100_ORD(STAT_TX_RETRY11, "Tx retries at 11MBPS"),
	    IPW2100_ORD(STAT_TX_FAILURES, "Tx Failures"),
	    IPW2100_ORD(STAT_TX_MAX_TRIES_IN_HOP,
				"times max tries in a hop failed"),
	    IPW2100_ORD(STAT_TX_DISASSN_FAIL,
				"times disassociation failed"),
	    IPW2100_ORD(STAT_TX_ERR_CTS, "missed/bad CTS frames"),
	    IPW2100_ORD(STAT_TX_ERR_ACK, "tx err due to acks"),
	    IPW2100_ORD(STAT_RX_HOST, "packets passed to host"),
	    IPW2100_ORD(STAT_RX_सूची_DATA, "directed packets"),
	    IPW2100_ORD(STAT_RX_सूची_DATA1, "directed packets at 1MB"),
	    IPW2100_ORD(STAT_RX_सूची_DATA2, "directed packets at 2MB"),
	    IPW2100_ORD(STAT_RX_सूची_DATA5_5,
				"directed packets at 5.5MB"),
	    IPW2100_ORD(STAT_RX_सूची_DATA11, "directed packets at 11MB"),
	    IPW2100_ORD(STAT_RX_NOसूची_DATA, "nondirected packets"),
	    IPW2100_ORD(STAT_RX_NOसूची_DATA1,
				"nondirected packets at 1MB"),
	    IPW2100_ORD(STAT_RX_NOसूची_DATA2,
				"nondirected packets at 2MB"),
	    IPW2100_ORD(STAT_RX_NOसूची_DATA5_5,
				"nondirected packets at 5.5MB"),
	    IPW2100_ORD(STAT_RX_NOसूची_DATA11,
				"nondirected packets at 11MB"),
	    IPW2100_ORD(STAT_RX_शून्य_DATA, "null data rx's"),
	    IPW2100_ORD(STAT_RX_RTS, "Rx RTS"), IPW2100_ORD(STAT_RX_CTS,
								    "Rx CTS"),
	    IPW2100_ORD(STAT_RX_ACK, "Rx ACK"),
	    IPW2100_ORD(STAT_RX_CFEND, "Rx CF End"),
	    IPW2100_ORD(STAT_RX_CFEND_ACK, "Rx CF End + CF Ack"),
	    IPW2100_ORD(STAT_RX_ASSN, "Association Rx's"),
	    IPW2100_ORD(STAT_RX_ASSN_RESP, "Association response Rx's"),
	    IPW2100_ORD(STAT_RX_REASSN, "Reassociation Rx's"),
	    IPW2100_ORD(STAT_RX_REASSN_RESP,
				"Reassociation response Rx's"),
	    IPW2100_ORD(STAT_RX_PROBE, "probe Rx's"),
	    IPW2100_ORD(STAT_RX_PROBE_RESP, "probe response Rx's"),
	    IPW2100_ORD(STAT_RX_BEACON, "Rx beacon"),
	    IPW2100_ORD(STAT_RX_ATIM, "Rx ATIM"),
	    IPW2100_ORD(STAT_RX_DISASSN, "disassociation Rx"),
	    IPW2100_ORD(STAT_RX_AUTH, "authentication Rx"),
	    IPW2100_ORD(STAT_RX_DEAUTH, "deauthentication Rx"),
	    IPW2100_ORD(STAT_RX_TOTAL_BYTES,
				"Total rx data bytes received"),
	    IPW2100_ORD(STAT_RX_ERR_CRC, "packets with Rx CRC error"),
	    IPW2100_ORD(STAT_RX_ERR_CRC1, "Rx CRC errors at 1MB"),
	    IPW2100_ORD(STAT_RX_ERR_CRC2, "Rx CRC errors at 2MB"),
	    IPW2100_ORD(STAT_RX_ERR_CRC5_5, "Rx CRC errors at 5.5MB"),
	    IPW2100_ORD(STAT_RX_ERR_CRC11, "Rx CRC errors at 11MB"),
	    IPW2100_ORD(STAT_RX_DUPLICATE1,
				"duplicate rx packets at 1MB"),
	    IPW2100_ORD(STAT_RX_DUPLICATE2,
				"duplicate rx packets at 2MB"),
	    IPW2100_ORD(STAT_RX_DUPLICATE5_5,
				"duplicate rx packets at 5.5MB"),
	    IPW2100_ORD(STAT_RX_DUPLICATE11,
				"duplicate rx packets at 11MB"),
	    IPW2100_ORD(STAT_RX_DUPLICATE, "duplicate rx packets"),
	    IPW2100_ORD(PERS_DB_LOCK, "locking fw permanent  db"),
	    IPW2100_ORD(PERS_DB_SIZE, "size of fw permanent  db"),
	    IPW2100_ORD(PERS_DB_ADDR, "address of fw permanent  db"),
	    IPW2100_ORD(STAT_RX_INVALID_PROTOCOL,
				"rx frames with invalid protocol"),
	    IPW2100_ORD(SYS_BOOT_TIME, "Boot time"),
	    IPW2100_ORD(STAT_RX_NO_BUFFER,
				"rx frames rejected due to no buffer"),
	    IPW2100_ORD(STAT_RX_MISSING_FRAG,
				"rx frames dropped due to missing fragment"),
	    IPW2100_ORD(STAT_RX_ORPHAN_FRAG,
				"rx frames dropped due to non-sequential fragment"),
	    IPW2100_ORD(STAT_RX_ORPHAN_FRAME,
				"rx frames dropped due to unmatched 1st frame"),
	    IPW2100_ORD(STAT_RX_FRAG_AGEOUT,
				"rx frames dropped due to uncompleted frame"),
	    IPW2100_ORD(STAT_RX_ICV_ERRORS,
				"ICV errors during decryption"),
	    IPW2100_ORD(STAT_PSP_SUSPENSION, "times adapter suspended"),
	    IPW2100_ORD(STAT_PSP_BCN_TIMEOUT, "beacon timeout"),
	    IPW2100_ORD(STAT_PSP_POLL_TIMEOUT,
				"poll response timeouts"),
	    IPW2100_ORD(STAT_PSP_NONसूची_TIMEOUT,
				"timeouts waiting for last {broad,multi}cast pkt"),
	    IPW2100_ORD(STAT_PSP_RX_DTIMS, "PSP DTIMs received"),
	    IPW2100_ORD(STAT_PSP_RX_TIMS, "PSP TIMs received"),
	    IPW2100_ORD(STAT_PSP_STATION_ID, "PSP Station ID"),
	    IPW2100_ORD(LAST_ASSN_TIME, "RTC time of last association"),
	    IPW2100_ORD(STAT_PERCENT_MISSED_BCNS,
				"current calculation of % missed beacons"),
	    IPW2100_ORD(STAT_PERCENT_RETRIES,
				"current calculation of % missed tx retries"),
	    IPW2100_ORD(ASSOCIATED_AP_PTR,
				"0 if not associated, else pointer to AP table entry"),
	    IPW2100_ORD(AVAILABLE_AP_CNT,
				"AP's described in the AP table"),
	    IPW2100_ORD(AP_LIST_PTR, "Ptr to list of available APs"),
	    IPW2100_ORD(STAT_AP_ASSNS, "associations"),
	    IPW2100_ORD(STAT_ASSN_FAIL, "association failures"),
	    IPW2100_ORD(STAT_ASSN_RESP_FAIL,
				"failures due to response fail"),
	    IPW2100_ORD(STAT_FULL_SCANS, "full scans"),
	    IPW2100_ORD(CARD_DISABLED, "Card Disabled"),
	    IPW2100_ORD(STAT_ROAM_INHIBIT,
				"times roaming was inhibited due to activity"),
	    IPW2100_ORD(RSSI_AT_ASSN,
				"RSSI of associated AP at time of association"),
	    IPW2100_ORD(STAT_ASSN_CAUSE1,
				"reassociation: no probe response or TX on hop"),
	    IPW2100_ORD(STAT_ASSN_CAUSE2,
				"reassociation: poor tx/rx quality"),
	    IPW2100_ORD(STAT_ASSN_CAUSE3,
				"reassociation: tx/rx quality (excessive AP load"),
	    IPW2100_ORD(STAT_ASSN_CAUSE4,
				"reassociation: AP RSSI level"),
	    IPW2100_ORD(STAT_ASSN_CAUSE5,
				"reassociations due to load leveling"),
	    IPW2100_ORD(STAT_AUTH_FAIL, "times authentication failed"),
	    IPW2100_ORD(STAT_AUTH_RESP_FAIL,
				"times authentication response failed"),
	    IPW2100_ORD(STATION_TABLE_CNT,
				"entries in association table"),
	    IPW2100_ORD(RSSI_AVG_CURR, "Current avg RSSI"),
	    IPW2100_ORD(POWER_MGMT_MODE, "Power mode - 0=CAM, 1=PSP"),
	    IPW2100_ORD(COUNTRY_CODE,
				"IEEE country code as recv'd from beacon"),
	    IPW2100_ORD(COUNTRY_CHANNELS,
				"channels supported by country"),
	    IPW2100_ORD(RESET_CNT, "adapter resets (warm)"),
	    IPW2100_ORD(BEACON_INTERVAL, "Beacon interval"),
	    IPW2100_ORD(ANTENNA_DIVERSITY,
				"TRUE if antenna diversity is disabled"),
	    IPW2100_ORD(DTIM_PERIOD, "beacon intervals between DTIMs"),
	    IPW2100_ORD(OUR_FREQ,
				"current radio freq lower digits - channel ID"),
	    IPW2100_ORD(RTC_TIME, "current RTC time"),
	    IPW2100_ORD(PORT_TYPE, "operating mode"),
	    IPW2100_ORD(CURRENT_TX_RATE, "current tx rate"),
	    IPW2100_ORD(SUPPORTED_RATES, "supported tx rates"),
	    IPW2100_ORD(ATIM_WINDOW, "current ATIM Window"),
	    IPW2100_ORD(BASIC_RATES, "basic tx rates"),
	    IPW2100_ORD(NIC_HIGHEST_RATE, "NIC highest tx rate"),
	    IPW2100_ORD(AP_HIGHEST_RATE, "AP highest tx rate"),
	    IPW2100_ORD(CAPABILITIES,
				"Management frame capability field"),
	    IPW2100_ORD(AUTH_TYPE, "Type of authentication"),
	    IPW2100_ORD(RADIO_TYPE, "Adapter card platform type"),
	    IPW2100_ORD(RTS_THRESHOLD,
				"Min packet length for RTS handshaking"),
	    IPW2100_ORD(INT_MODE, "International mode"),
	    IPW2100_ORD(FRAGMENTATION_THRESHOLD,
				"protocol frag threshold"),
	    IPW2100_ORD(EEPROM_SRAM_DB_BLOCK_START_ADDRESS,
				"EEPROM offset in SRAM"),
	    IPW2100_ORD(EEPROM_SRAM_DB_BLOCK_SIZE,
				"EEPROM size in SRAM"),
	    IPW2100_ORD(EEPROM_SKU_CAPABILITY, "EEPROM SKU Capability"),
	    IPW2100_ORD(EEPROM_IBSS_11B_CHANNELS,
				"EEPROM IBSS 11b channel set"),
	    IPW2100_ORD(MAC_VERSION, "MAC Version"),
	    IPW2100_ORD(MAC_REVISION, "MAC Revision"),
	    IPW2100_ORD(RADIO_VERSION, "Radio Version"),
	    IPW2100_ORD(NIC_MANF_DATE_TIME, "MANF Date/Time STAMP"),
	    IPW2100_ORD(UCODE_VERSION, "Ucode Version"),पूर्ण;

अटल sमाप_प्रकार show_रेजिस्टरs(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	पूर्णांक i;
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	अक्षर *out = buf;
	u32 val = 0;

	out += प्र_लिखो(out, "%30s [Address ] : Hex\n", "Register");

	क्रम (i = 0; i < ARRAY_SIZE(hw_data); i++) अणु
		पढ़ो_रेजिस्टर(dev, hw_data[i].addr, &val);
		out += प्र_लिखो(out, "%30s [%08X] : %08X\n",
			       hw_data[i].name, hw_data[i].addr, val);
	पूर्ण

	वापस out - buf;
पूर्ण

अटल DEVICE_ATTR(रेजिस्टरs, 0444, show_रेजिस्टरs, शून्य);

अटल sमाप_प्रकार show_hardware(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	अक्षर *out = buf;
	पूर्णांक i;

	out += प्र_लिखो(out, "%30s [Address ] : Hex\n", "NIC entry");

	क्रम (i = 0; i < ARRAY_SIZE(nic_data); i++) अणु
		u8 पंचांगp8;
		u16 पंचांगp16;
		u32 पंचांगp32;

		चयन (nic_data[i].size) अणु
		हाल 1:
			पढ़ो_nic_byte(dev, nic_data[i].addr, &पंचांगp8);
			out += प्र_लिखो(out, "%30s [%08X] : %02X\n",
				       nic_data[i].name, nic_data[i].addr,
				       पंचांगp8);
			अवरोध;
		हाल 2:
			पढ़ो_nic_word(dev, nic_data[i].addr, &पंचांगp16);
			out += प्र_लिखो(out, "%30s [%08X] : %04X\n",
				       nic_data[i].name, nic_data[i].addr,
				       पंचांगp16);
			अवरोध;
		हाल 4:
			पढ़ो_nic_dword(dev, nic_data[i].addr, &पंचांगp32);
			out += प्र_लिखो(out, "%30s [%08X] : %08X\n",
				       nic_data[i].name, nic_data[i].addr,
				       पंचांगp32);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस out - buf;
पूर्ण

अटल DEVICE_ATTR(hardware, 0444, show_hardware, शून्य);

अटल sमाप_प्रकार show_memory(काष्ठा device *d, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	अटल अचिन्हित दीर्घ loop = 0;
	पूर्णांक len = 0;
	u32 buffer[4];
	पूर्णांक i;
	अक्षर line[81];

	अगर (loop >= 0x30000)
		loop = 0;

	/* sysfs provides us PAGE_SIZE buffer */
	जबतक (len < PAGE_SIZE - 128 && loop < 0x30000) अणु

		अगर (priv->snapshot[0])
			क्रम (i = 0; i < 4; i++)
				buffer[i] =
				    *(u32 *) SNAPSHOT_ADDR(loop + i * 4);
		अन्यथा
			क्रम (i = 0; i < 4; i++)
				पढ़ो_nic_dword(dev, loop + i * 4, &buffer[i]);

		अगर (priv->dump_raw)
			len += प्र_लिखो(buf + len,
				       "%c%c%c%c"
				       "%c%c%c%c"
				       "%c%c%c%c"
				       "%c%c%c%c",
				       ((u8 *) buffer)[0x0],
				       ((u8 *) buffer)[0x1],
				       ((u8 *) buffer)[0x2],
				       ((u8 *) buffer)[0x3],
				       ((u8 *) buffer)[0x4],
				       ((u8 *) buffer)[0x5],
				       ((u8 *) buffer)[0x6],
				       ((u8 *) buffer)[0x7],
				       ((u8 *) buffer)[0x8],
				       ((u8 *) buffer)[0x9],
				       ((u8 *) buffer)[0xa],
				       ((u8 *) buffer)[0xb],
				       ((u8 *) buffer)[0xc],
				       ((u8 *) buffer)[0xd],
				       ((u8 *) buffer)[0xe],
				       ((u8 *) buffer)[0xf]);
		अन्यथा
			len += प्र_लिखो(buf + len, "%s\n",
				       snprपूर्णांक_line(line, माप(line),
						    (u8 *) buffer, 16, loop));
		loop += 16;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार store_memory(काष्ठा device *d, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	स्थिर अक्षर *p = buf;

	(व्योम)dev;		/* समाप्त unused-var warning क्रम debug-only code */

	अगर (count < 1)
		वापस count;

	अगर (p[0] == '1' ||
	    (count >= 2 && छोटे(p[0]) == 'o' && tolower(p[1]) == 'n')) अणु
		IPW_DEBUG_INFO("%s: Setting memory dump to RAW mode.\n",
			       dev->name);
		priv->dump_raw = 1;

	पूर्ण अन्यथा अगर (p[0] == '0' || (count >= 2 && tolower(p[0]) == 'o' &&
				   छोटे(p[1]) == 'f')) अणु
		IPW_DEBUG_INFO("%s: Setting memory dump to HEX mode.\n",
			       dev->name);
		priv->dump_raw = 0;

	पूर्ण अन्यथा अगर (छोटे(p[0]) == 'r') अणु
		IPW_DEBUG_INFO("%s: Resetting firmware snapshot.\n", dev->name);
		ipw2100_snapshot_मुक्त(priv);

	पूर्ण अन्यथा
		IPW_DEBUG_INFO("%s: Usage: 0|on = HEX, 1|off = RAW, "
			       "reset = clear memory snapshot\n", dev->name);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(memory, 0644, show_memory, store_memory);

अटल sमाप_प्रकार show_ordinals(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	u32 val = 0;
	पूर्णांक len = 0;
	u32 val_len;
	अटल पूर्णांक loop = 0;

	अगर (priv->status & STATUS_RF_KILL_MASK)
		वापस 0;

	अगर (loop >= ARRAY_SIZE(ord_data))
		loop = 0;

	/* sysfs provides us PAGE_SIZE buffer */
	जबतक (len < PAGE_SIZE - 128 && loop < ARRAY_SIZE(ord_data)) अणु
		val_len = माप(u32);

		अगर (ipw2100_get_ordinal(priv, ord_data[loop].index, &val,
					&val_len))
			len += प्र_लिखो(buf + len, "[0x%02X] = ERROR    %s\n",
				       ord_data[loop].index,
				       ord_data[loop].desc);
		अन्यथा
			len += प्र_लिखो(buf + len, "[0x%02X] = 0x%08X %s\n",
				       ord_data[loop].index, val,
				       ord_data[loop].desc);
		loop++;
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(ordinals, 0444, show_ordinals, शून्य);

अटल sमाप_प्रकार show_stats(काष्ठा device *d, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	अक्षर *out = buf;

	out += प्र_लिखो(out, "interrupts: %d {tx: %d, rx: %d, other: %d}\n",
		       priv->पूर्णांकerrupts, priv->tx_पूर्णांकerrupts,
		       priv->rx_पूर्णांकerrupts, priv->पूर्णांकa_other);
	out += प्र_लिखो(out, "firmware resets: %d\n", priv->resets);
	out += प्र_लिखो(out, "firmware hangs: %d\n", priv->hangs);
#अगर_घोषित CONFIG_IPW2100_DEBUG
	out += प्र_लिखो(out, "packet mismatch image: %s\n",
		       priv->snapshot[0] ? "YES" : "NO");
#पूर्ण_अगर

	वापस out - buf;
पूर्ण

अटल DEVICE_ATTR(stats, 0444, show_stats, शून्य);

अटल पूर्णांक ipw2100_चयन_mode(काष्ठा ipw2100_priv *priv, u32 mode)
अणु
	पूर्णांक err;

	अगर (mode == priv->ieee->iw_mode)
		वापस 0;

	err = ipw2100_disable_adapter(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": %s: Could not disable adapter %d\n",
		       priv->net_dev->name, err);
		वापस err;
	पूर्ण

	चयन (mode) अणु
	हाल IW_MODE_INFRA:
		priv->net_dev->type = ARPHRD_ETHER;
		अवरोध;
	हाल IW_MODE_ADHOC:
		priv->net_dev->type = ARPHRD_ETHER;
		अवरोध;
#अगर_घोषित CONFIG_IPW2100_MONITOR
	हाल IW_MODE_MONITOR:
		priv->last_mode = priv->ieee->iw_mode;
		priv->net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
		अवरोध;
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */
	पूर्ण

	priv->ieee->iw_mode = mode;

#अगर_घोषित CONFIG_PM
	/* Indicate ipw2100_करोwnload_firmware करोwnload firmware
	 * from disk instead of memory. */
	ipw2100_firmware.version = 0;
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "%s: Resetting on mode change.\n", priv->net_dev->name);
	priv->reset_backoff = 0;
	schedule_reset(priv);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_पूर्णांकernals(काष्ठा device *d, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	पूर्णांक len = 0;

#घोषणा DUMP_VAR(x,y) len += प्र_लिखो(buf + len, # x ": %" y "\n", priv-> x)

	अगर (priv->status & STATUS_ASSOCIATED)
		len += प्र_लिखो(buf + len, "connected: %llu\n",
			       kसमय_get_bootसमय_seconds() - priv->connect_start);
	अन्यथा
		len += प्र_लिखो(buf + len, "not connected\n");

	DUMP_VAR(ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx], "p");
	DUMP_VAR(status, "08lx");
	DUMP_VAR(config, "08lx");
	DUMP_VAR(capability, "08lx");

	len +=
	    प्र_लिखो(buf + len, "last_rtc: %lu\n",
		    (अचिन्हित दीर्घ)priv->last_rtc);

	DUMP_VAR(fatal_error, "d");
	DUMP_VAR(stop_hang_check, "d");
	DUMP_VAR(stop_rf_समाप्त, "d");
	DUMP_VAR(messages_sent, "d");

	DUMP_VAR(tx_pend_stat.value, "d");
	DUMP_VAR(tx_pend_स्थिति.सi, "d");

	DUMP_VAR(tx_मुक्त_stat.value, "d");
	DUMP_VAR(tx_मुक्त_stat.lo, "d");

	DUMP_VAR(msg_मुक्त_stat.value, "d");
	DUMP_VAR(msg_मुक्त_stat.lo, "d");

	DUMP_VAR(msg_pend_stat.value, "d");
	DUMP_VAR(msg_pend_स्थिति.सi, "d");

	DUMP_VAR(fw_pend_stat.value, "d");
	DUMP_VAR(fw_pend_स्थिति.सi, "d");

	DUMP_VAR(txq_stat.value, "d");
	DUMP_VAR(txq_stat.lo, "d");

	DUMP_VAR(ieee->scans, "d");
	DUMP_VAR(reset_backoff, "lld");

	वापस len;
पूर्ण

अटल DEVICE_ATTR(पूर्णांकernals, 0444, show_पूर्णांकernals, शून्य);

अटल sमाप_प्रकार show_bssinfo(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	अक्षर essid[IW_ESSID_MAX_SIZE + 1];
	u8 bssid[ETH_ALEN];
	u32 chan = 0;
	अक्षर *out = buf;
	अचिन्हित पूर्णांक length;
	पूर्णांक ret;

	अगर (priv->status & STATUS_RF_KILL_MASK)
		वापस 0;

	स_रखो(essid, 0, माप(essid));
	स_रखो(bssid, 0, माप(bssid));

	length = IW_ESSID_MAX_SIZE;
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_SSID, essid, &length);
	अगर (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	length = माप(bssid);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_AP_BSSID,
				  bssid, &length);
	अगर (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	length = माप(u32);
	ret = ipw2100_get_ordinal(priv, IPW_ORD_OUR_FREQ, &chan, &length);
	अगर (ret)
		IPW_DEBUG_INFO("failed querying ordinals at line %d\n",
			       __LINE__);

	out += प्र_लिखो(out, "ESSID: %s\n", essid);
	out += प्र_लिखो(out, "BSSID:   %pM\n", bssid);
	out += प्र_लिखो(out, "Channel: %d\n", chan);

	वापस out - buf;
पूर्ण

अटल DEVICE_ATTR(bssinfo, 0444, show_bssinfo, शून्य);

#अगर_घोषित CONFIG_IPW2100_DEBUG
अटल sमाप_प्रकार debug_level_show(काष्ठा device_driver *d, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%08X\n", ipw2100_debug_level);
पूर्ण

अटल sमाप_प्रकार debug_level_store(काष्ठा device_driver *d,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(buf, 0, &val);
	अगर (ret)
		IPW_DEBUG_INFO(": %s is not in hex or decimal form.\n", buf);
	अन्यथा
		ipw2100_debug_level = val;

	वापस strnlen(buf, count);
पूर्ण
अटल DRIVER_ATTR_RW(debug_level);
#पूर्ण_अगर				/* CONFIG_IPW2100_DEBUG */

अटल sमाप_प्रकार show_fatal_error(काष्ठा device *d,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	अक्षर *out = buf;
	पूर्णांक i;

	अगर (priv->fatal_error)
		out += प्र_लिखो(out, "0x%08X\n", priv->fatal_error);
	अन्यथा
		out += प्र_लिखो(out, "0\n");

	क्रम (i = 1; i <= IPW2100_ERROR_QUEUE; i++) अणु
		अगर (!priv->fatal_errors[(priv->fatal_index - i) %
					IPW2100_ERROR_QUEUE])
			जारी;

		out += प्र_लिखो(out, "%d. 0x%08X\n", i,
			       priv->fatal_errors[(priv->fatal_index - i) %
						  IPW2100_ERROR_QUEUE]);
	पूर्ण

	वापस out - buf;
पूर्ण

अटल sमाप_प्रकार store_fatal_error(काष्ठा device *d,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	schedule_reset(priv);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(fatal_error, 0644, show_fatal_error, store_fatal_error);

अटल sमाप_प्रकार show_scan_age(काष्ठा device *d, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "%d\n", priv->ieee->scan_age);
पूर्ण

अटल sमाप_प्रकार store_scan_age(काष्ठा device *d, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	काष्ठा net_device *dev = priv->net_dev;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	(व्योम)dev;		/* समाप्त unused-var warning क्रम debug-only code */

	IPW_DEBUG_INFO("enter\n");

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret) अणु
		IPW_DEBUG_INFO("%s: user supplied invalid value.\n", dev->name);
	पूर्ण अन्यथा अणु
		priv->ieee->scan_age = val;
		IPW_DEBUG_INFO("set scan_age = %u\n", priv->ieee->scan_age);
	पूर्ण

	IPW_DEBUG_INFO("exit\n");
	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(scan_age, 0644, show_scan_age, store_scan_age);

अटल sमाप_प्रकार show_rf_समाप्त(काष्ठा device *d, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	/* 0 - RF समाप्त not enabled
	   1 - SW based RF समाप्त active (sysfs)
	   2 - HW based RF समाप्त active
	   3 - Both HW and SW baed RF समाप्त active */
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	पूर्णांक val = ((priv->status & STATUS_RF_KILL_SW) ? 0x1 : 0x0) |
	    (rf_समाप्त_active(priv) ? 0x2 : 0x0);
	वापस प्र_लिखो(buf, "%i\n", val);
पूर्ण

अटल पूर्णांक ipw_radio_समाप्त_sw(काष्ठा ipw2100_priv *priv, पूर्णांक disable_radio)
अणु
	अगर ((disable_radio ? 1 : 0) ==
	    (priv->status & STATUS_RF_KILL_SW ? 1 : 0))
		वापस 0;

	IPW_DEBUG_RF_KILL("Manual SW RF Kill set to: RADIO  %s\n",
			  disable_radio ? "OFF" : "ON");

	mutex_lock(&priv->action_mutex);

	अगर (disable_radio) अणु
		priv->status |= STATUS_RF_KILL_SW;
		ipw2100_करोwn(priv);
	पूर्ण अन्यथा अणु
		priv->status &= ~STATUS_RF_KILL_SW;
		अगर (rf_समाप्त_active(priv)) अणु
			IPW_DEBUG_RF_KILL("Can not turn radio back on - "
					  "disabled by HW switch\n");
			/* Make sure the RF_KILL check समयr is running */
			priv->stop_rf_समाप्त = 0;
			mod_delayed_work(प्रणाली_wq, &priv->rf_समाप्त,
					 round_jअगरfies_relative(HZ));
		पूर्ण अन्यथा
			schedule_reset(priv);
	पूर्ण

	mutex_unlock(&priv->action_mutex);
	वापस 1;
पूर्ण

अटल sमाप_प्रकार store_rf_समाप्त(काष्ठा device *d, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(d);
	ipw_radio_समाप्त_sw(priv, buf[0] == '1');
	वापस count;
पूर्ण

अटल DEVICE_ATTR(rf_समाप्त, 0644, show_rf_समाप्त, store_rf_समाप्त);

अटल काष्ठा attribute *ipw2100_sysfs_entries[] = अणु
	&dev_attr_hardware.attr,
	&dev_attr_रेजिस्टरs.attr,
	&dev_attr_ordinals.attr,
	&dev_attr_pci.attr,
	&dev_attr_stats.attr,
	&dev_attr_पूर्णांकernals.attr,
	&dev_attr_bssinfo.attr,
	&dev_attr_memory.attr,
	&dev_attr_scan_age.attr,
	&dev_attr_fatal_error.attr,
	&dev_attr_rf_समाप्त.attr,
	&dev_attr_cfg.attr,
	&dev_attr_status.attr,
	&dev_attr_capability.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ipw2100_attribute_group = अणु
	.attrs = ipw2100_sysfs_entries,
पूर्ण;

अटल पूर्णांक status_queue_allocate(काष्ठा ipw2100_priv *priv, पूर्णांक entries)
अणु
	काष्ठा ipw2100_status_queue *q = &priv->status_queue;

	IPW_DEBUG_INFO("enter\n");

	q->size = entries * माप(काष्ठा ipw2100_status);
	q->drv = dma_alloc_coherent(&priv->pci_dev->dev, q->size, &q->nic,
				    GFP_KERNEL);
	अगर (!q->drv) अणु
		IPW_DEBUG_WARNING("Can not allocate status queue.\n");
		वापस -ENOMEM;
	पूर्ण

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

अटल व्योम status_queue_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	IPW_DEBUG_INFO("enter\n");

	अगर (priv->status_queue.drv) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev,
				  priv->status_queue.size,
				  priv->status_queue.drv,
				  priv->status_queue.nic);
		priv->status_queue.drv = शून्य;
	पूर्ण

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल पूर्णांक bd_queue_allocate(काष्ठा ipw2100_priv *priv,
			     काष्ठा ipw2100_bd_queue *q, पूर्णांक entries)
अणु
	IPW_DEBUG_INFO("enter\n");

	स_रखो(q, 0, माप(काष्ठा ipw2100_bd_queue));

	q->entries = entries;
	q->size = entries * माप(काष्ठा ipw2100_bd);
	q->drv = dma_alloc_coherent(&priv->pci_dev->dev, q->size, &q->nic,
				    GFP_KERNEL);
	अगर (!q->drv) अणु
		IPW_DEBUG_INFO
		    ("can't allocate shared memory for buffer descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

अटल व्योम bd_queue_मुक्त(काष्ठा ipw2100_priv *priv, काष्ठा ipw2100_bd_queue *q)
अणु
	IPW_DEBUG_INFO("enter\n");

	अगर (!q)
		वापस;

	अगर (q->drv) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev, q->size, q->drv,
				  q->nic);
		q->drv = शून्य;
	पूर्ण

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल व्योम bd_queue_initialize(काष्ठा ipw2100_priv *priv,
				काष्ठा ipw2100_bd_queue *q, u32 base, u32 size,
				u32 r, u32 w)
अणु
	IPW_DEBUG_INFO("enter\n");

	IPW_DEBUG_INFO("initializing bd queue at virt=%p, phys=%08x\n", q->drv,
		       (u32) q->nic);

	ग_लिखो_रेजिस्टर(priv->net_dev, base, q->nic);
	ग_लिखो_रेजिस्टर(priv->net_dev, size, q->entries);
	ग_लिखो_रेजिस्टर(priv->net_dev, r, q->oldest);
	ग_लिखो_रेजिस्टर(priv->net_dev, w, q->next);

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल व्योम ipw2100_समाप्त_works(काष्ठा ipw2100_priv *priv)
अणु
	priv->stop_rf_समाप्त = 1;
	priv->stop_hang_check = 1;
	cancel_delayed_work_sync(&priv->reset_work);
	cancel_delayed_work_sync(&priv->security_work);
	cancel_delayed_work_sync(&priv->wx_event_work);
	cancel_delayed_work_sync(&priv->hang_check);
	cancel_delayed_work_sync(&priv->rf_समाप्त);
	cancel_delayed_work_sync(&priv->scan_event);
पूर्ण

अटल पूर्णांक ipw2100_tx_allocate(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i, j, err;
	व्योम *v;
	dma_addr_t p;

	IPW_DEBUG_INFO("enter\n");

	err = bd_queue_allocate(priv, &priv->tx_queue, TX_QUEUE_LENGTH);
	अगर (err) अणु
		IPW_DEBUG_ERROR("%s: failed bd_queue_allocate\n",
				priv->net_dev->name);
		वापस err;
	पूर्ण

	priv->tx_buffers = kदो_स्मृति_array(TX_PENDED_QUEUE_LENGTH,
					 माप(काष्ठा ipw2100_tx_packet),
					 GFP_KERNEL);
	अगर (!priv->tx_buffers) अणु
		bd_queue_मुक्त(priv, &priv->tx_queue);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < TX_PENDED_QUEUE_LENGTH; i++) अणु
		v = dma_alloc_coherent(&priv->pci_dev->dev,
				       माप(काष्ठा ipw2100_data_header), &p,
				       GFP_KERNEL);
		अगर (!v) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
			       ": %s: PCI alloc failed for tx " "buffers.\n",
			       priv->net_dev->name);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		priv->tx_buffers[i].type = DATA;
		priv->tx_buffers[i].info.d_काष्ठा.data =
		    (काष्ठा ipw2100_data_header *)v;
		priv->tx_buffers[i].info.d_काष्ठा.data_phys = p;
		priv->tx_buffers[i].info.d_काष्ठा.txb = शून्य;
	पूर्ण

	अगर (i == TX_PENDED_QUEUE_LENGTH)
		वापस 0;

	क्रम (j = 0; j < i; j++) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev,
				  माप(काष्ठा ipw2100_data_header),
				  priv->tx_buffers[j].info.d_काष्ठा.data,
				  priv->tx_buffers[j].info.d_काष्ठा.data_phys);
	पूर्ण

	kमुक्त(priv->tx_buffers);
	priv->tx_buffers = शून्य;

	वापस err;
पूर्ण

अटल व्योम ipw2100_tx_initialize(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;

	IPW_DEBUG_INFO("enter\n");

	/*
	 * reinitialize packet info lists
	 */
	INIT_LIST_HEAD(&priv->fw_pend_list);
	INIT_STAT(&priv->fw_pend_stat);

	/*
	 * reinitialize lists
	 */
	INIT_LIST_HEAD(&priv->tx_pend_list);
	INIT_LIST_HEAD(&priv->tx_मुक्त_list);
	INIT_STAT(&priv->tx_pend_stat);
	INIT_STAT(&priv->tx_मुक्त_stat);

	क्रम (i = 0; i < TX_PENDED_QUEUE_LENGTH; i++) अणु
		/* We simply drop any SKBs that have been queued क्रम
		 * transmit */
		अगर (priv->tx_buffers[i].info.d_काष्ठा.txb) अणु
			libipw_txb_मुक्त(priv->tx_buffers[i].info.d_काष्ठा.
					   txb);
			priv->tx_buffers[i].info.d_काष्ठा.txb = शून्य;
		पूर्ण

		list_add_tail(&priv->tx_buffers[i].list, &priv->tx_मुक्त_list);
	पूर्ण

	SET_STAT(&priv->tx_मुक्त_stat, i);

	priv->tx_queue.oldest = 0;
	priv->tx_queue.available = priv->tx_queue.entries;
	priv->tx_queue.next = 0;
	INIT_STAT(&priv->txq_stat);
	SET_STAT(&priv->txq_stat, priv->tx_queue.available);

	bd_queue_initialize(priv, &priv->tx_queue,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_BD_BASE,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_BD_SIZE,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_READ_INDEX,
			    IPW_MEM_HOST_SHARED_TX_QUEUE_WRITE_INDEX);

	IPW_DEBUG_INFO("exit\n");

पूर्ण

अटल व्योम ipw2100_tx_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;

	IPW_DEBUG_INFO("enter\n");

	bd_queue_मुक्त(priv, &priv->tx_queue);

	अगर (!priv->tx_buffers)
		वापस;

	क्रम (i = 0; i < TX_PENDED_QUEUE_LENGTH; i++) अणु
		अगर (priv->tx_buffers[i].info.d_काष्ठा.txb) अणु
			libipw_txb_मुक्त(priv->tx_buffers[i].info.d_काष्ठा.
					   txb);
			priv->tx_buffers[i].info.d_काष्ठा.txb = शून्य;
		पूर्ण
		अगर (priv->tx_buffers[i].info.d_काष्ठा.data)
			dma_मुक्त_coherent(&priv->pci_dev->dev,
					  माप(काष्ठा ipw2100_data_header),
					  priv->tx_buffers[i].info.d_काष्ठा.data,
					  priv->tx_buffers[i].info.d_काष्ठा.data_phys);
	पूर्ण

	kमुक्त(priv->tx_buffers);
	priv->tx_buffers = शून्य;

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल पूर्णांक ipw2100_rx_allocate(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i, j, err = -EINVAL;

	IPW_DEBUG_INFO("enter\n");

	err = bd_queue_allocate(priv, &priv->rx_queue, RX_QUEUE_LENGTH);
	अगर (err) अणु
		IPW_DEBUG_INFO("failed bd_queue_allocate\n");
		वापस err;
	पूर्ण

	err = status_queue_allocate(priv, RX_QUEUE_LENGTH);
	अगर (err) अणु
		IPW_DEBUG_INFO("failed status_queue_allocate\n");
		bd_queue_मुक्त(priv, &priv->rx_queue);
		वापस err;
	पूर्ण

	/*
	 * allocate packets
	 */
	priv->rx_buffers = kदो_स्मृति_array(RX_QUEUE_LENGTH,
					 माप(काष्ठा ipw2100_rx_packet),
					 GFP_KERNEL);
	अगर (!priv->rx_buffers) अणु
		IPW_DEBUG_INFO("can't allocate rx packet buffer table\n");

		bd_queue_मुक्त(priv, &priv->rx_queue);

		status_queue_मुक्त(priv);

		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < RX_QUEUE_LENGTH; i++) अणु
		काष्ठा ipw2100_rx_packet *packet = &priv->rx_buffers[i];

		err = ipw2100_alloc_skb(priv, packet);
		अगर (unlikely(err)) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		/* The BD holds the cache aligned address */
		priv->rx_queue.drv[i].host_addr = packet->dma_addr;
		priv->rx_queue.drv[i].buf_length = IPW_RX_NIC_BUFFER_LENGTH;
		priv->status_queue.drv[i].status_fields = 0;
	पूर्ण

	अगर (i == RX_QUEUE_LENGTH)
		वापस 0;

	क्रम (j = 0; j < i; j++) अणु
		dma_unmap_single(&priv->pci_dev->dev,
				 priv->rx_buffers[j].dma_addr,
				 माप(काष्ठा ipw2100_rx_packet),
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb(priv->rx_buffers[j].skb);
	पूर्ण

	kमुक्त(priv->rx_buffers);
	priv->rx_buffers = शून्य;

	bd_queue_मुक्त(priv, &priv->rx_queue);

	status_queue_मुक्त(priv);

	वापस err;
पूर्ण

अटल व्योम ipw2100_rx_initialize(काष्ठा ipw2100_priv *priv)
अणु
	IPW_DEBUG_INFO("enter\n");

	priv->rx_queue.oldest = 0;
	priv->rx_queue.available = priv->rx_queue.entries - 1;
	priv->rx_queue.next = priv->rx_queue.entries - 1;

	INIT_STAT(&priv->rxq_stat);
	SET_STAT(&priv->rxq_stat, priv->rx_queue.available);

	bd_queue_initialize(priv, &priv->rx_queue,
			    IPW_MEM_HOST_SHARED_RX_BD_BASE,
			    IPW_MEM_HOST_SHARED_RX_BD_SIZE,
			    IPW_MEM_HOST_SHARED_RX_READ_INDEX,
			    IPW_MEM_HOST_SHARED_RX_WRITE_INDEX);

	/* set up the status queue */
	ग_लिखो_रेजिस्टर(priv->net_dev, IPW_MEM_HOST_SHARED_RX_STATUS_BASE,
		       priv->status_queue.nic);

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल व्योम ipw2100_rx_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक i;

	IPW_DEBUG_INFO("enter\n");

	bd_queue_मुक्त(priv, &priv->rx_queue);
	status_queue_मुक्त(priv);

	अगर (!priv->rx_buffers)
		वापस;

	क्रम (i = 0; i < RX_QUEUE_LENGTH; i++) अणु
		अगर (priv->rx_buffers[i].rxp) अणु
			dma_unmap_single(&priv->pci_dev->dev,
					 priv->rx_buffers[i].dma_addr,
					 माप(काष्ठा ipw2100_rx),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(priv->rx_buffers[i].skb);
		पूर्ण
	पूर्ण

	kमुक्त(priv->rx_buffers);
	priv->rx_buffers = शून्य;

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल पूर्णांक ipw2100_पढ़ो_mac_address(काष्ठा ipw2100_priv *priv)
अणु
	u32 length = ETH_ALEN;
	u8 addr[ETH_ALEN];

	पूर्णांक err;

	err = ipw2100_get_ordinal(priv, IPW_ORD_STAT_ADAPTER_MAC, addr, &length);
	अगर (err) अणु
		IPW_DEBUG_INFO("MAC address read failed\n");
		वापस -EIO;
	पूर्ण

	स_नकल(priv->net_dev->dev_addr, addr, ETH_ALEN);
	IPW_DEBUG_INFO("card MAC is %pM\n", priv->net_dev->dev_addr);

	वापस 0;
पूर्ण

/********************************************************************
 *
 * Firmware Commands
 *
 ********************************************************************/

अटल पूर्णांक ipw2100_set_mac_address(काष्ठा ipw2100_priv *priv, पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = ADAPTER_ADDRESS,
		.host_command_sequence = 0,
		.host_command_length = ETH_ALEN
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("SET_MAC_ADDRESS\n");

	IPW_DEBUG_INFO("enter\n");

	अगर (priv->config & CFG_CUSTOM_MAC) अणु
		स_नकल(cmd.host_command_parameters, priv->mac_addr, ETH_ALEN);
		स_नकल(priv->net_dev->dev_addr, priv->mac_addr, ETH_ALEN);
	पूर्ण अन्यथा
		स_नकल(cmd.host_command_parameters, priv->net_dev->dev_addr,
		       ETH_ALEN);

	err = ipw2100_hw_send_command(priv, &cmd);

	IPW_DEBUG_INFO("exit\n");
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_port_type(काष्ठा ipw2100_priv *priv, u32 port_type,
				 पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = PORT_TYPE,
		.host_command_sequence = 0,
		.host_command_length = माप(u32)
	पूर्ण;
	पूर्णांक err;

	चयन (port_type) अणु
	हाल IW_MODE_INFRA:
		cmd.host_command_parameters[0] = IPW_BSS;
		अवरोध;
	हाल IW_MODE_ADHOC:
		cmd.host_command_parameters[0] = IPW_IBSS;
		अवरोध;
	पूर्ण

	IPW_DEBUG_HC("PORT_TYPE: %s\n",
		     port_type == IPW_IBSS ? "Ad-Hoc" : "Managed");

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
			       ": %s: Could not disable adapter %d\n",
			       priv->net_dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* send cmd to firmware */
	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_channel(काष्ठा ipw2100_priv *priv, u32 channel,
			       पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = CHANNEL,
		.host_command_sequence = 0,
		.host_command_length = माप(u32)
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = channel;

	IPW_DEBUG_HC("CHANNEL: %d\n", channel);

	/* If BSS then we करोn't support channel selection */
	अगर (priv->ieee->iw_mode == IW_MODE_INFRA)
		वापस 0;

	अगर ((channel != 0) &&
	    ((channel < REG_MIN_CHANNEL) || (channel > REG_MAX_CHANNEL)))
		वापस -EINVAL;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err) अणु
		IPW_DEBUG_INFO("Failed to set channel to %d", channel);
		वापस err;
	पूर्ण

	अगर (channel)
		priv->config |= CFG_STATIC_CHANNEL;
	अन्यथा
		priv->config &= ~CFG_STATIC_CHANNEL;

	priv->channel = channel;

	अगर (!batch_mode) अणु
		err = ipw2100_enable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_प्रणाली_config(काष्ठा ipw2100_priv *priv, पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = SYSTEM_CONFIG,
		.host_command_sequence = 0,
		.host_command_length = 12,
	पूर्ण;
	u32 ibss_mask, len = माप(u32);
	पूर्णांक err;

	/* Set प्रणाली configuration */

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC)
		cmd.host_command_parameters[0] |= IPW_CFG_IBSS_AUTO_START;

	cmd.host_command_parameters[0] |= IPW_CFG_IBSS_MASK |
	    IPW_CFG_BSS_MASK | IPW_CFG_802_1x_ENABLE;

	अगर (!(priv->config & CFG_LONG_PREAMBLE))
		cmd.host_command_parameters[0] |= IPW_CFG_PREAMBLE_AUTO;

	err = ipw2100_get_ordinal(priv,
				  IPW_ORD_EEPROM_IBSS_11B_CHANNELS,
				  &ibss_mask, &len);
	अगर (err)
		ibss_mask = IPW_IBSS_11B_DEFAULT_MASK;

	cmd.host_command_parameters[1] = REG_CHANNEL_MASK;
	cmd.host_command_parameters[2] = REG_CHANNEL_MASK & ibss_mask;

	/* 11b only */
	/*cmd.host_command_parameters[0] |= DIVERSITY_ANTENNA_A; */

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

/* If IPv6 is configured in the kernel then we करोn't want to filter out all
 * of the multicast packets as IPv6 needs some. */
#अगर !defined(CONFIG_IPV6) && !defined(CONFIG_IPV6_MODULE)
	cmd.host_command = ADD_MULTICAST;
	cmd.host_command_sequence = 0;
	cmd.host_command_length = 0;

	ipw2100_hw_send_command(priv, &cmd);
#पूर्ण_अगर
	अगर (!batch_mode) अणु
		err = ipw2100_enable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_tx_rates(काष्ठा ipw2100_priv *priv, u32 rate,
				पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = BASIC_TX_RATES,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = rate & TX_RATE_MASK;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	/* Set BASIC TX Rate first */
	ipw2100_hw_send_command(priv, &cmd);

	/* Set TX Rate */
	cmd.host_command = TX_RATES;
	ipw2100_hw_send_command(priv, &cmd);

	/* Set MSDU TX Rate */
	cmd.host_command = MSDU_TX_RATES;
	ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode) अणु
		err = ipw2100_enable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	priv->tx_rates = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_घातer_mode(काष्ठा ipw2100_priv *priv, पूर्णांक घातer_level)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = POWER_MODE,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = घातer_level;

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

	अगर (घातer_level == IPW_POWER_MODE_CAM)
		priv->घातer_mode = IPW_POWER_LEVEL(priv->घातer_mode);
	अन्यथा
		priv->घातer_mode = IPW_POWER_ENABLED | घातer_level;

#अगर_घोषित IPW2100_TX_POWER
	अगर (priv->port_type == IBSS && priv->adhoc_घातer != DFTL_IBSS_TX_POWER) अणु
		/* Set beacon पूर्णांकerval */
		cmd.host_command = TX_POWER_INDEX;
		cmd.host_command_parameters[0] = (u32) priv->adhoc_घातer;

		err = ipw2100_hw_send_command(priv, &cmd);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_rts_threshold(काष्ठा ipw2100_priv *priv, u32 threshold)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = RTS_THRESHOLD,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	अगर (threshold & RTS_DISABLED)
		cmd.host_command_parameters[0] = MAX_RTS_THRESHOLD;
	अन्यथा
		cmd.host_command_parameters[0] = threshold & ~RTS_DISABLED;

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

	priv->rts_threshold = threshold;

	वापस 0;
पूर्ण

#अगर 0
पूर्णांक ipw2100_set_fragmentation_threshold(काष्ठा ipw2100_priv *priv,
					u32 threshold, पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = FRAG_THRESHOLD,
		.host_command_sequence = 0,
		.host_command_length = 4,
		.host_command_parameters[0] = 0,
	पूर्ण;
	पूर्णांक err;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (threshold == 0)
		threshold = DEFAULT_FRAG_THRESHOLD;
	अन्यथा अणु
		threshold = max(threshold, MIN_FRAG_THRESHOLD);
		threshold = min(threshold, MAX_FRAG_THRESHOLD);
	पूर्ण

	cmd.host_command_parameters[0] = threshold;

	IPW_DEBUG_HC("FRAG_THRESHOLD: %u\n", threshold);

	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	अगर (!err)
		priv->frag_threshold = threshold;

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipw2100_set_लघु_retry(काष्ठा ipw2100_priv *priv, u32 retry)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = SHORT_RETRY_LIMIT,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = retry;

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

	priv->लघु_retry_limit = retry;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_दीर्घ_retry(काष्ठा ipw2100_priv *priv, u32 retry)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = LONG_RETRY_LIMIT,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = retry;

	err = ipw2100_hw_send_command(priv, &cmd);
	अगर (err)
		वापस err;

	priv->दीर्घ_retry_limit = retry;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_mandatory_bssid(काष्ठा ipw2100_priv *priv, u8 * bssid,
				       पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = MANDATORY_BSSID,
		.host_command_sequence = 0,
		.host_command_length = (bssid == शून्य) ? 0 : ETH_ALEN
	पूर्ण;
	पूर्णांक err;

#अगर_घोषित CONFIG_IPW2100_DEBUG
	अगर (bssid != शून्य)
		IPW_DEBUG_HC("MANDATORY_BSSID: %pM\n", bssid);
	अन्यथा
		IPW_DEBUG_HC("MANDATORY_BSSID: <clear>\n");
#पूर्ण_अगर
	/* अगर BSSID is empty then we disable mandatory bssid mode */
	अगर (bssid != शून्य)
		स_नकल(cmd.host_command_parameters, bssid, ETH_ALEN);

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_disassociate_bssid(काष्ठा ipw2100_priv *priv)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = DISASSOCIATION_BSSID,
		.host_command_sequence = 0,
		.host_command_length = ETH_ALEN
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("DISASSOCIATION_BSSID\n");

	/* The Firmware currently ignores the BSSID and just disassociates from
	 * the currently associated AP -- but in the off chance that a future
	 * firmware करोes use the BSSID provided here, we go ahead and try and
	 * set it to the currently associated AP's BSSID */
	स_नकल(cmd.host_command_parameters, priv->bssid, ETH_ALEN);

	err = ipw2100_hw_send_command(priv, &cmd);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_wpa_ie(काष्ठा ipw2100_priv *,
			      काष्ठा ipw2100_wpa_assoc_frame *, पूर्णांक)
    __attribute__ ((unused));

अटल पूर्णांक ipw2100_set_wpa_ie(काष्ठा ipw2100_priv *priv,
			      काष्ठा ipw2100_wpa_assoc_frame *wpa_frame,
			      पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = SET_WPA_IE,
		.host_command_sequence = 0,
		.host_command_length = माप(काष्ठा ipw2100_wpa_assoc_frame),
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("SET_WPA_IE\n");

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	स_नकल(cmd.host_command_parameters, wpa_frame,
	       माप(काष्ठा ipw2100_wpa_assoc_frame));

	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode) अणु
		अगर (ipw2100_enable_adapter(priv))
			err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

काष्ठा security_info_params अणु
	u32 allowed_ciphers;
	u16 version;
	u8 auth_mode;
	u8 replay_counters_number;
	u8 unicast_using_group;
पूर्ण __packed;

अटल पूर्णांक ipw2100_set_security_inक्रमmation(काष्ठा ipw2100_priv *priv,
					    पूर्णांक auth_mode,
					    पूर्णांक security_level,
					    पूर्णांक unicast_using_group,
					    पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = SET_SECURITY_INFORMATION,
		.host_command_sequence = 0,
		.host_command_length = माप(काष्ठा security_info_params)
	पूर्ण;
	काष्ठा security_info_params *security =
	    (काष्ठा security_info_params *)&cmd.host_command_parameters;
	पूर्णांक err;
	स_रखो(security, 0, माप(*security));

	/* If shared key AP authentication is turned on, then we need to
	 * configure the firmware to try and use it.
	 *
	 * Actual data encryption/decryption is handled by the host. */
	security->auth_mode = auth_mode;
	security->unicast_using_group = unicast_using_group;

	चयन (security_level) अणु
	शेष:
	हाल SEC_LEVEL_0:
		security->allowed_ciphers = IPW_NONE_CIPHER;
		अवरोध;
	हाल SEC_LEVEL_1:
		security->allowed_ciphers = IPW_WEP40_CIPHER |
		    IPW_WEP104_CIPHER;
		अवरोध;
	हाल SEC_LEVEL_2:
		security->allowed_ciphers = IPW_WEP40_CIPHER |
		    IPW_WEP104_CIPHER | IPW_TKIP_CIPHER;
		अवरोध;
	हाल SEC_LEVEL_2_CKIP:
		security->allowed_ciphers = IPW_WEP40_CIPHER |
		    IPW_WEP104_CIPHER | IPW_CKIP_CIPHER;
		अवरोध;
	हाल SEC_LEVEL_3:
		security->allowed_ciphers = IPW_WEP40_CIPHER |
		    IPW_WEP104_CIPHER | IPW_TKIP_CIPHER | IPW_CCMP_CIPHER;
		अवरोध;
	पूर्ण

	IPW_DEBUG_HC
	    ("SET_SECURITY_INFORMATION: auth:%d cipher:0x%02X (level %d)\n",
	     security->auth_mode, security->allowed_ciphers, security_level);

	security->replay_counters_number = 0;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_tx_घातer(काष्ठा ipw2100_priv *priv, u32 tx_घातer)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = TX_POWER_INDEX,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err = 0;
	u32 पंचांगp = tx_घातer;

	अगर (tx_घातer != IPW_TX_POWER_DEFAULT)
		पंचांगp = (tx_घातer - IPW_TX_POWER_MIN_DBM) * 16 /
		      (IPW_TX_POWER_MAX_DBM - IPW_TX_POWER_MIN_DBM);

	cmd.host_command_parameters[0] = पंचांगp;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC)
		err = ipw2100_hw_send_command(priv, &cmd);
	अगर (!err)
		priv->tx_घातer = tx_घातer;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_set_ibss_beacon_पूर्णांकerval(काष्ठा ipw2100_priv *priv,
					    u32 पूर्णांकerval, पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = BEACON_INTERVAL,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = पूर्णांकerval;

	IPW_DEBUG_INFO("enter\n");

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (!batch_mode) अणु
			err = ipw2100_disable_adapter(priv);
			अगर (err)
				वापस err;
		पूर्ण

		ipw2100_hw_send_command(priv, &cmd);

		अगर (!batch_mode) अणु
			err = ipw2100_enable_adapter(priv);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

अटल व्योम ipw2100_queues_initialize(काष्ठा ipw2100_priv *priv)
अणु
	ipw2100_tx_initialize(priv);
	ipw2100_rx_initialize(priv);
	ipw2100_msg_initialize(priv);
पूर्ण

अटल व्योम ipw2100_queues_मुक्त(काष्ठा ipw2100_priv *priv)
अणु
	ipw2100_tx_मुक्त(priv);
	ipw2100_rx_मुक्त(priv);
	ipw2100_msg_मुक्त(priv);
पूर्ण

अटल पूर्णांक ipw2100_queues_allocate(काष्ठा ipw2100_priv *priv)
अणु
	अगर (ipw2100_tx_allocate(priv) ||
	    ipw2100_rx_allocate(priv) || ipw2100_msg_allocate(priv))
		जाओ fail;

	वापस 0;

      fail:
	ipw2100_tx_मुक्त(priv);
	ipw2100_rx_मुक्त(priv);
	ipw2100_msg_मुक्त(priv);
	वापस -ENOMEM;
पूर्ण

#घोषणा IPW_PRIVACY_CAPABLE 0x0008

अटल पूर्णांक ipw2100_set_wep_flags(काष्ठा ipw2100_priv *priv, u32 flags,
				 पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = WEP_FLAGS,
		.host_command_sequence = 0,
		.host_command_length = 4
	पूर्ण;
	पूर्णांक err;

	cmd.host_command_parameters[0] = flags;

	IPW_DEBUG_HC("WEP_FLAGS: flags = 0x%08X\n", flags);

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
			       ": %s: Could not disable adapter %d\n",
			       priv->net_dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* send cmd to firmware */
	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

काष्ठा ipw2100_wep_key अणु
	u8 idx;
	u8 len;
	u8 key[13];
पूर्ण;

/* Macros to ease up priting WEP keys */
#घोषणा WEP_FMT_64  "%02X%02X%02X%02X-%02X"
#घोषणा WEP_FMT_128 "%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X"
#घोषणा WEP_STR_64(x) x[0],x[1],x[2],x[3],x[4]
#घोषणा WEP_STR_128(x) x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10]

/**
 * Set a the wep key
 *
 * @priv: काष्ठा to work on
 * @idx: index of the key we want to set
 * @key: ptr to the key data to set
 * @len: length of the buffer at @key
 * @batch_mode: FIXME perक्रमm the operation in batch mode, not
 *              disabling the device.
 *
 * @वापसs 0 अगर OK, < 0 त्रुटि_सं code on error.
 *
 * Fill out a command काष्ठाure with the new wep key, length an
 * index and send it करोwn the wire.
 */
अटल पूर्णांक ipw2100_set_key(काष्ठा ipw2100_priv *priv,
			   पूर्णांक idx, अक्षर *key, पूर्णांक len, पूर्णांक batch_mode)
अणु
	पूर्णांक keylen = len ? (len <= 5 ? 5 : 13) : 0;
	काष्ठा host_command cmd = अणु
		.host_command = WEP_KEY_INFO,
		.host_command_sequence = 0,
		.host_command_length = माप(काष्ठा ipw2100_wep_key),
	पूर्ण;
	काष्ठा ipw2100_wep_key *wep_key = (व्योम *)cmd.host_command_parameters;
	पूर्णांक err;

	IPW_DEBUG_HC("WEP_KEY_INFO: index = %d, len = %d/%d\n",
		     idx, keylen, len);

	/* NOTE: We करोn't check cached values in हाल the firmware was reset
	 * or some other problem is occurring.  If the user is setting the key,
	 * then we push the change */

	wep_key->idx = idx;
	wep_key->len = keylen;

	अगर (keylen) अणु
		स_नकल(wep_key->key, key, len);
		स_रखो(wep_key->key + len, 0, keylen - len);
	पूर्ण

	/* Will be optimized out on debug not being configured in */
	अगर (keylen == 0)
		IPW_DEBUG_WEP("%s: Clearing key %d\n",
			      priv->net_dev->name, wep_key->idx);
	अन्यथा अगर (keylen == 5)
		IPW_DEBUG_WEP("%s: idx: %d, len: %d key: " WEP_FMT_64 "\n",
			      priv->net_dev->name, wep_key->idx, wep_key->len,
			      WEP_STR_64(wep_key->key));
	अन्यथा
		IPW_DEBUG_WEP("%s: idx: %d, len: %d key: " WEP_FMT_128
			      "\n",
			      priv->net_dev->name, wep_key->idx, wep_key->len,
			      WEP_STR_128(wep_key->key));

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		/* FIXME: IPG: shouldn't this prink be in _disable_adapter()? */
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
			       ": %s: Could not disable adapter %d\n",
			       priv->net_dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* send cmd to firmware */
	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode) अणु
		पूर्णांक err2 = ipw2100_enable_adapter(priv);
		अगर (err == 0)
			err = err2;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_set_key_index(काष्ठा ipw2100_priv *priv,
				 पूर्णांक idx, पूर्णांक batch_mode)
अणु
	काष्ठा host_command cmd = अणु
		.host_command = WEP_KEY_INDEX,
		.host_command_sequence = 0,
		.host_command_length = 4,
		.host_command_parameters = अणुidxपूर्ण,
	पूर्ण;
	पूर्णांक err;

	IPW_DEBUG_HC("WEP_KEY_INDEX: index = %d\n", idx);

	अगर (idx < 0 || idx > 3)
		वापस -EINVAL;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME
			       ": %s: Could not disable adapter %d\n",
			       priv->net_dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* send cmd to firmware */
	err = ipw2100_hw_send_command(priv, &cmd);

	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_configure_security(काष्ठा ipw2100_priv *priv, पूर्णांक batch_mode)
अणु
	पूर्णांक i, err, auth_mode, sec_level, use_group;

	अगर (!(priv->status & STATUS_RUNNING))
		वापस 0;

	अगर (!batch_mode) अणु
		err = ipw2100_disable_adapter(priv);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!priv->ieee->sec.enabled) अणु
		err =
		    ipw2100_set_security_inक्रमmation(priv, IPW_AUTH_OPEN,
						     SEC_LEVEL_0, 0, 1);
	पूर्ण अन्यथा अणु
		auth_mode = IPW_AUTH_OPEN;
		अगर (priv->ieee->sec.flags & SEC_AUTH_MODE) अणु
			अगर (priv->ieee->sec.auth_mode == WLAN_AUTH_SHARED_KEY)
				auth_mode = IPW_AUTH_SHARED;
			अन्यथा अगर (priv->ieee->sec.auth_mode == WLAN_AUTH_LEAP)
				auth_mode = IPW_AUTH_LEAP_CISCO_ID;
		पूर्ण

		sec_level = SEC_LEVEL_0;
		अगर (priv->ieee->sec.flags & SEC_LEVEL)
			sec_level = priv->ieee->sec.level;

		use_group = 0;
		अगर (priv->ieee->sec.flags & SEC_UNICAST_GROUP)
			use_group = priv->ieee->sec.unicast_uses_group;

		err =
		    ipw2100_set_security_inक्रमmation(priv, auth_mode, sec_level,
						     use_group, 1);
	पूर्ण

	अगर (err)
		जाओ निकास;

	अगर (priv->ieee->sec.enabled) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर (!(priv->ieee->sec.flags & (1 << i))) अणु
				स_रखो(priv->ieee->sec.keys[i], 0, WEP_KEY_LEN);
				priv->ieee->sec.key_sizes[i] = 0;
			पूर्ण अन्यथा अणु
				err = ipw2100_set_key(priv, i,
						      priv->ieee->sec.keys[i],
						      priv->ieee->sec.
						      key_sizes[i], 1);
				अगर (err)
					जाओ निकास;
			पूर्ण
		पूर्ण

		ipw2100_set_key_index(priv, priv->ieee->crypt_info.tx_keyidx, 1);
	पूर्ण

	/* Always enable privacy so the Host can filter WEP packets अगर
	 * encrypted data is sent up */
	err =
	    ipw2100_set_wep_flags(priv,
				  priv->ieee->sec.
				  enabled ? IPW_PRIVACY_CAPABLE : 0, 1);
	अगर (err)
		जाओ निकास;

	priv->status &= ~STATUS_SECURITY_UPDATED;

      निकास:
	अगर (!batch_mode)
		ipw2100_enable_adapter(priv);

	वापस err;
पूर्ण

अटल व्योम ipw2100_security_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv =
		container_of(work, काष्ठा ipw2100_priv, security_work.work);

	/* If we happen to have reconnected beक्रमe we get a chance to
	 * process this, then update the security settings--which causes
	 * a disassociation to occur */
	अगर (!(priv->status & STATUS_ASSOCIATED) &&
	    priv->status & STATUS_SECURITY_UPDATED)
		ipw2100_configure_security(priv, 0);
पूर्ण

अटल व्योम shim__set_security(काष्ठा net_device *dev,
			       काष्ठा libipw_security *sec)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक i;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED))
		जाओ करोne;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (sec->flags & (1 << i)) अणु
			priv->ieee->sec.key_sizes[i] = sec->key_sizes[i];
			अगर (sec->key_sizes[i] == 0)
				priv->ieee->sec.flags &= ~(1 << i);
			अन्यथा
				स_नकल(priv->ieee->sec.keys[i], sec->keys[i],
				       sec->key_sizes[i]);
			अगर (sec->level == SEC_LEVEL_1) अणु
				priv->ieee->sec.flags |= (1 << i);
				priv->status |= STATUS_SECURITY_UPDATED;
			पूर्ण अन्यथा
				priv->ieee->sec.flags &= ~(1 << i);
		पूर्ण
	पूर्ण

	अगर ((sec->flags & SEC_ACTIVE_KEY) &&
	    priv->ieee->sec.active_key != sec->active_key) अणु
		priv->ieee->sec.active_key = sec->active_key;
		priv->ieee->sec.flags |= SEC_ACTIVE_KEY;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	अगर ((sec->flags & SEC_AUTH_MODE) &&
	    (priv->ieee->sec.auth_mode != sec->auth_mode)) अणु
		priv->ieee->sec.auth_mode = sec->auth_mode;
		priv->ieee->sec.flags |= SEC_AUTH_MODE;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	अगर (sec->flags & SEC_ENABLED && priv->ieee->sec.enabled != sec->enabled) अणु
		priv->ieee->sec.flags |= SEC_ENABLED;
		priv->ieee->sec.enabled = sec->enabled;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	अगर (sec->flags & SEC_ENCRYPT)
		priv->ieee->sec.encrypt = sec->encrypt;

	अगर (sec->flags & SEC_LEVEL && priv->ieee->sec.level != sec->level) अणु
		priv->ieee->sec.level = sec->level;
		priv->ieee->sec.flags |= SEC_LEVEL;
		priv->status |= STATUS_SECURITY_UPDATED;
	पूर्ण

	IPW_DEBUG_WEP("Security flags: %c %c%c%c%c %c%c%c%c\n",
		      priv->ieee->sec.flags & (1 << 8) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 7) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 6) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 5) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 4) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 3) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 2) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 1) ? '1' : '0',
		      priv->ieee->sec.flags & (1 << 0) ? '1' : '0');

/* As a temporary work around to enable WPA until we figure out why
 * wpa_supplicant toggles the security capability of the driver, which
 * क्रमces a disassociation with क्रमce_update...
 *
 *	अगर (क्रमce_update || !(priv->status & STATUS_ASSOCIATED))*/
	अगर (!(priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)))
		ipw2100_configure_security(priv, 0);
      करोne:
	mutex_unlock(&priv->action_mutex);
पूर्ण

अटल पूर्णांक ipw2100_adapter_setup(काष्ठा ipw2100_priv *priv)
अणु
	पूर्णांक err;
	पूर्णांक batch_mode = 1;
	u8 *bssid;

	IPW_DEBUG_INFO("enter\n");

	err = ipw2100_disable_adapter(priv);
	अगर (err)
		वापस err;
#अगर_घोषित CONFIG_IPW2100_MONITOR
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
		err = ipw2100_set_channel(priv, priv->channel, batch_mode);
		अगर (err)
			वापस err;

		IPW_DEBUG_INFO("exit\n");

		वापस 0;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */

	err = ipw2100_पढ़ो_mac_address(priv);
	अगर (err)
		वापस -EIO;

	err = ipw2100_set_mac_address(priv, batch_mode);
	अगर (err)
		वापस err;

	err = ipw2100_set_port_type(priv, priv->ieee->iw_mode, batch_mode);
	अगर (err)
		वापस err;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		err = ipw2100_set_channel(priv, priv->channel, batch_mode);
		अगर (err)
			वापस err;
	पूर्ण

	err = ipw2100_प्रणाली_config(priv, batch_mode);
	अगर (err)
		वापस err;

	err = ipw2100_set_tx_rates(priv, priv->tx_rates, batch_mode);
	अगर (err)
		वापस err;

	/* Default to घातer mode OFF */
	err = ipw2100_set_घातer_mode(priv, IPW_POWER_MODE_CAM);
	अगर (err)
		वापस err;

	err = ipw2100_set_rts_threshold(priv, priv->rts_threshold);
	अगर (err)
		वापस err;

	अगर (priv->config & CFG_STATIC_BSSID)
		bssid = priv->bssid;
	अन्यथा
		bssid = शून्य;
	err = ipw2100_set_mandatory_bssid(priv, bssid, batch_mode);
	अगर (err)
		वापस err;

	अगर (priv->config & CFG_STATIC_ESSID)
		err = ipw2100_set_essid(priv, priv->essid, priv->essid_len,
					batch_mode);
	अन्यथा
		err = ipw2100_set_essid(priv, शून्य, 0, batch_mode);
	अगर (err)
		वापस err;

	err = ipw2100_configure_security(priv, batch_mode);
	अगर (err)
		वापस err;

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		err =
		    ipw2100_set_ibss_beacon_पूर्णांकerval(priv,
						     priv->beacon_पूर्णांकerval,
						     batch_mode);
		अगर (err)
			वापस err;

		err = ipw2100_set_tx_घातer(priv, priv->tx_घातer);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	   err = ipw2100_set_fragmentation_threshold(
	   priv, priv->frag_threshold, batch_mode);
	   अगर (err)
	   वापस err;
	 */

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

/*************************************************************************
 *
 * EXTERNALLY CALLED METHODS
 *
 *************************************************************************/

/* This method is called by the network layer -- not to be confused with
 * ipw2100_set_mac_address() declared above called by this driver (and this
 * method as well) to talk to the firmware */
अटल पूर्णांक ipw2100_set_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक err = 0;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	mutex_lock(&priv->action_mutex);

	priv->config |= CFG_CUSTOM_MAC;
	स_नकल(priv->mac_addr, addr->sa_data, ETH_ALEN);

	err = ipw2100_set_mac_address(priv, 0);
	अगर (err)
		जाओ करोne;

	priv->reset_backoff = 0;
	mutex_unlock(&priv->action_mutex);
	ipw2100_reset_adapter(&priv->reset_work.work);
	वापस 0;

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अचिन्हित दीर्घ flags;
	IPW_DEBUG_INFO("dev->open\n");

	spin_lock_irqsave(&priv->low_lock, flags);
	अगर (priv->status & STATUS_ASSOCIATED) अणु
		netअगर_carrier_on(dev);
		netअगर_start_queue(dev);
	पूर्ण
	spin_unlock_irqrestore(&priv->low_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *element;
	काष्ठा ipw2100_tx_packet *packet;

	IPW_DEBUG_INFO("enter\n");

	spin_lock_irqsave(&priv->low_lock, flags);

	अगर (priv->status & STATUS_ASSOCIATED)
		netअगर_carrier_off(dev);
	netअगर_stop_queue(dev);

	/* Flush the TX queue ... */
	जबतक (!list_empty(&priv->tx_pend_list)) अणु
		element = priv->tx_pend_list.next;
		packet = list_entry(element, काष्ठा ipw2100_tx_packet, list);

		list_del(element);
		DEC_STAT(&priv->tx_pend_stat);

		libipw_txb_मुक्त(packet->info.d_काष्ठा.txb);
		packet->info.d_काष्ठा.txb = शून्य;

		list_add_tail(element, &priv->tx_मुक्त_list);
		INC_STAT(&priv->tx_मुक्त_stat);
	पूर्ण
	spin_unlock_irqrestore(&priv->low_lock, flags);

	IPW_DEBUG_INFO("exit\n");

	वापस 0;
पूर्ण

/*
 * TODO:  Fix this function... its just wrong
 */
अटल व्योम ipw2100_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	dev->stats.tx_errors++;

#अगर_घोषित CONFIG_IPW2100_MONITOR
	अगर (priv->ieee->iw_mode == IW_MODE_MONITOR)
		वापस;
#पूर्ण_अगर

	IPW_DEBUG_INFO("%s: TX timed out.  Scheduling firmware restart.\n",
		       dev->name);
	schedule_reset(priv);
पूर्ण

अटल पूर्णांक ipw2100_wpa_enable(काष्ठा ipw2100_priv *priv, पूर्णांक value)
अणु
	/* This is called when wpa_supplicant loads and बंदs the driver
	 * पूर्णांकerface. */
	priv->ieee->wpa_enabled = value;
	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wpa_set_auth_algs(काष्ठा ipw2100_priv *priv, पूर्णांक value)
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

अटल व्योम ipw2100_wpa_assoc_frame(काष्ठा ipw2100_priv *priv,
				    अक्षर *wpa_ie, पूर्णांक wpa_ie_len)
अणु

	काष्ठा ipw2100_wpa_assoc_frame frame;

	frame.fixed_ie_mask = 0;

	/* copy WPA IE */
	स_नकल(frame.var_ie, wpa_ie, wpa_ie_len);
	frame.var_ie_len = wpa_ie_len;

	/* make sure WPA is enabled */
	ipw2100_wpa_enable(priv, 1);
	ipw2100_set_wpa_ie(priv, &frame, 0);
पूर्ण

अटल व्योम ipw_ethtool_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अक्षर fw_ver[64], ucode_ver[64];

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));

	ipw2100_get_fwversion(priv, fw_ver, माप(fw_ver));
	ipw2100_get_ucodeversion(priv, ucode_ver, माप(ucode_ver));

	snम_लिखो(info->fw_version, माप(info->fw_version), "%s:%d:%s",
		 fw_ver, priv->eeprom_version, ucode_ver);

	strlcpy(info->bus_info, pci_name(priv->pci_dev),
		माप(info->bus_info));
पूर्ण

अटल u32 ipw2100_ethtool_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस (priv->status & STATUS_ASSOCIATED) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ipw2100_ethtool_ops = अणु
	.get_link = ipw2100_ethtool_get_link,
	.get_drvinfo = ipw_ethtool_get_drvinfo,
पूर्ण;

अटल व्योम ipw2100_hang_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv =
		container_of(work, काष्ठा ipw2100_priv, hang_check.work);
	अचिन्हित दीर्घ flags;
	u32 rtc = 0xa5a5a5a5;
	u32 len = माप(rtc);
	पूर्णांक restart = 0;

	spin_lock_irqsave(&priv->low_lock, flags);

	अगर (priv->fatal_error != 0) अणु
		/* If fatal_error is set then we need to restart */
		IPW_DEBUG_INFO("%s: Hardware fatal error detected.\n",
			       priv->net_dev->name);

		restart = 1;
	पूर्ण अन्यथा अगर (ipw2100_get_ordinal(priv, IPW_ORD_RTC_TIME, &rtc, &len) ||
		   (rtc == priv->last_rtc)) अणु
		/* Check अगर firmware is hung */
		IPW_DEBUG_INFO("%s: Firmware RTC stalled.\n",
			       priv->net_dev->name);

		restart = 1;
	पूर्ण

	अगर (restart) अणु
		/* Kill समयr */
		priv->stop_hang_check = 1;
		priv->hangs++;

		/* Restart the NIC */
		schedule_reset(priv);
	पूर्ण

	priv->last_rtc = rtc;

	अगर (!priv->stop_hang_check)
		schedule_delayed_work(&priv->hang_check, HZ / 2);

	spin_unlock_irqrestore(&priv->low_lock, flags);
पूर्ण

अटल व्योम ipw2100_rf_समाप्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv =
		container_of(work, काष्ठा ipw2100_priv, rf_समाप्त.work);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->low_lock, flags);

	अगर (rf_समाप्त_active(priv)) अणु
		IPW_DEBUG_RF_KILL("RF Kill active, rescheduling GPIO check\n");
		अगर (!priv->stop_rf_समाप्त)
			schedule_delayed_work(&priv->rf_समाप्त,
					      round_jअगरfies_relative(HZ));
		जाओ निकास_unlock;
	पूर्ण

	/* RF Kill is now disabled, so bring the device back up */

	अगर (!(priv->status & STATUS_RF_KILL_MASK)) अणु
		IPW_DEBUG_RF_KILL("HW RF Kill no longer active, restarting "
				  "device\n");
		schedule_reset(priv);
	पूर्ण अन्यथा
		IPW_DEBUG_RF_KILL("HW RF Kill deactivated.  SW RF Kill still "
				  "enabled\n");

      निकास_unlock:
	spin_unlock_irqrestore(&priv->low_lock, flags);
पूर्ण

अटल व्योम ipw2100_irq_tasklet(काष्ठा tasklet_काष्ठा *t);

अटल स्थिर काष्ठा net_device_ops ipw2100_netdev_ops = अणु
	.nकरो_खोलो		= ipw2100_खोलो,
	.nकरो_stop		= ipw2100_बंद,
	.nकरो_start_xmit		= libipw_xmit,
	.nकरो_tx_समयout		= ipw2100_tx_समयout,
	.nकरो_set_mac_address	= ipw2100_set_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/* Look पूर्णांकo using netdev deकाष्ठाor to shutकरोwn libipw? */

अटल काष्ठा net_device *ipw2100_alloc_device(काष्ठा pci_dev *pci_dev,
					       व्योम __iomem * ioaddr)
अणु
	काष्ठा ipw2100_priv *priv;
	काष्ठा net_device *dev;

	dev = alloc_libipw(माप(काष्ठा ipw2100_priv), 0);
	अगर (!dev)
		वापस शून्य;
	priv = libipw_priv(dev);
	priv->ieee = netdev_priv(dev);
	priv->pci_dev = pci_dev;
	priv->net_dev = dev;
	priv->ioaddr = ioaddr;

	priv->ieee->hard_start_xmit = ipw2100_tx;
	priv->ieee->set_security = shim__set_security;

	priv->ieee->perfect_rssi = -20;
	priv->ieee->worst_rssi = -85;

	dev->netdev_ops = &ipw2100_netdev_ops;
	dev->ethtool_ops = &ipw2100_ethtool_ops;
	dev->wireless_handlers = &ipw2100_wx_handler_def;
	priv->wireless_data.libipw = priv->ieee;
	dev->wireless_data = &priv->wireless_data;
	dev->watchकरोg_समयo = 3 * HZ;
	dev->irq = 0;
	dev->min_mtu = 68;
	dev->max_mtu = LIBIPW_DATA_LEN;

	/* NOTE: We करोn't use the wireless_handlers hook
	 * in dev as the प्रणाली will start throwing WX requests
	 * to us beक्रमe we're actually initialized and it just
	 * ends up causing problems.  So, we just handle
	 * the WX extensions through the ipw2100_ioctl पूर्णांकerface */

	/* स_रखो() माला_दो everything to 0, so we only have explicitly set
	 * those values that need to be something अन्यथा */

	/* If घातer management is turned on, शेष to AUTO mode */
	priv->घातer_mode = IPW_POWER_AUTO;

#अगर_घोषित CONFIG_IPW2100_MONITOR
	priv->config |= CFG_CRC_CHECK;
#पूर्ण_अगर
	priv->ieee->wpa_enabled = 0;
	priv->ieee->drop_unencrypted = 0;
	priv->ieee->privacy_invoked = 0;
	priv->ieee->ieee802_1x = 1;

	/* Set module parameters */
	चयन (network_mode) अणु
	हाल 1:
		priv->ieee->iw_mode = IW_MODE_ADHOC;
		अवरोध;
#अगर_घोषित CONFIG_IPW2100_MONITOR
	हाल 2:
		priv->ieee->iw_mode = IW_MODE_MONITOR;
		अवरोध;
#पूर्ण_अगर
	शेष:
	हाल 0:
		priv->ieee->iw_mode = IW_MODE_INFRA;
		अवरोध;
	पूर्ण

	अगर (disable == 1)
		priv->status |= STATUS_RF_KILL_SW;

	अगर (channel != 0 &&
	    ((channel >= REG_MIN_CHANNEL) && (channel <= REG_MAX_CHANNEL))) अणु
		priv->config |= CFG_STATIC_CHANNEL;
		priv->channel = channel;
	पूर्ण

	अगर (associate)
		priv->config |= CFG_ASSOCIATE;

	priv->beacon_पूर्णांकerval = DEFAULT_BEACON_INTERVAL;
	priv->लघु_retry_limit = DEFAULT_SHORT_RETRY_LIMIT;
	priv->दीर्घ_retry_limit = DEFAULT_LONG_RETRY_LIMIT;
	priv->rts_threshold = DEFAULT_RTS_THRESHOLD | RTS_DISABLED;
	priv->frag_threshold = DEFAULT_FTS | FRAG_DISABLED;
	priv->tx_घातer = IPW_TX_POWER_DEFAULT;
	priv->tx_rates = DEFAULT_TX_RATES;

	म_नकल(priv->nick, "ipw2100");

	spin_lock_init(&priv->low_lock);
	mutex_init(&priv->action_mutex);
	mutex_init(&priv->adapter_mutex);

	init_रुकोqueue_head(&priv->रुको_command_queue);

	netअगर_carrier_off(dev);

	INIT_LIST_HEAD(&priv->msg_मुक्त_list);
	INIT_LIST_HEAD(&priv->msg_pend_list);
	INIT_STAT(&priv->msg_मुक्त_stat);
	INIT_STAT(&priv->msg_pend_stat);

	INIT_LIST_HEAD(&priv->tx_मुक्त_list);
	INIT_LIST_HEAD(&priv->tx_pend_list);
	INIT_STAT(&priv->tx_मुक्त_stat);
	INIT_STAT(&priv->tx_pend_stat);

	INIT_LIST_HEAD(&priv->fw_pend_list);
	INIT_STAT(&priv->fw_pend_stat);

	INIT_DELAYED_WORK(&priv->reset_work, ipw2100_reset_adapter);
	INIT_DELAYED_WORK(&priv->security_work, ipw2100_security_work);
	INIT_DELAYED_WORK(&priv->wx_event_work, ipw2100_wx_event_work);
	INIT_DELAYED_WORK(&priv->hang_check, ipw2100_hang_check);
	INIT_DELAYED_WORK(&priv->rf_समाप्त, ipw2100_rf_समाप्त);
	INIT_DELAYED_WORK(&priv->scan_event, ipw2100_scan_event);

	tasklet_setup(&priv->irq_tasklet, ipw2100_irq_tasklet);

	/* NOTE:  We करो not start the deferred work क्रम status checks yet */
	priv->stop_rf_समाप्त = 1;
	priv->stop_hang_check = 1;

	वापस dev;
पूर्ण

अटल पूर्णांक ipw2100_pci_init_one(काष्ठा pci_dev *pci_dev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	व्योम __iomem *ioaddr;
	काष्ठा net_device *dev = शून्य;
	काष्ठा ipw2100_priv *priv = शून्य;
	पूर्णांक err = 0;
	पूर्णांक रेजिस्टरed = 0;
	u32 val;

	IPW_DEBUG_INFO("enter\n");

	अगर (!(pci_resource_flags(pci_dev, 0) & IORESOURCE_MEM)) अणु
		IPW_DEBUG_INFO("weird - resource type is not memory\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	ioaddr = pci_iomap(pci_dev, 0, 0);
	अगर (!ioaddr) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling ioremap.\n");
		err = -EIO;
		जाओ fail;
	पूर्ण

	/* allocate and initialize our net_device */
	dev = ipw2100_alloc_device(pci_dev, ioaddr);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling ipw2100_alloc_device.\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* set up PCI mappings क्रम device */
	err = pci_enable_device(pci_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling pci_enable_device.\n");
		वापस err;
	पूर्ण

	priv = libipw_priv(dev);

	pci_set_master(pci_dev);
	pci_set_drvdata(pci_dev, priv);

	err = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling pci_set_dma_mask.\n");
		pci_disable_device(pci_dev);
		वापस err;
	पूर्ण

	err = pci_request_regions(pci_dev, DRV_NAME);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling pci_request_regions.\n");
		pci_disable_device(pci_dev);
		वापस err;
	पूर्ण

	/* We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_पढ़ो_config_dword(pci_dev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pci_dev, 0x40, val & 0xffff00ff);

	अगर (!ipw2100_hw_is_adapter_in_प्रणाली(dev)) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Device not found via register read.\n");
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	SET_NETDEV_DEV(dev, &pci_dev->dev);

	/* Force पूर्णांकerrupts to be shut off on the device */
	priv->status |= STATUS_INT_ENABLED;
	ipw2100_disable_पूर्णांकerrupts(priv);

	/* Allocate and initialize the Tx/Rx queues and lists */
	अगर (ipw2100_queues_allocate(priv)) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling ipw2100_queues_allocate.\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	ipw2100_queues_initialize(priv);

	err = request_irq(pci_dev->irq,
			  ipw2100_पूर्णांकerrupt, IRQF_SHARED, dev->name, priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling request_irq: %d.\n", pci_dev->irq);
		जाओ fail;
	पूर्ण
	dev->irq = pci_dev->irq;

	IPW_DEBUG_INFO("Attempting to register device...\n");

	prपूर्णांकk(KERN_INFO DRV_NAME
	       ": Detected Intel PRO/Wireless 2100 Network Connection\n");

	err = ipw2100_up(priv, 1);
	अगर (err)
		जाओ fail;

	err = ipw2100_wdev_init(dev);
	अगर (err)
		जाओ fail;
	रेजिस्टरed = 1;

	/* Bring up the पूर्णांकerface.  Pre 0.46, after we रेजिस्टरed the
	 * network device we would call ipw2100_up.  This पूर्णांकroduced a race
	 * condition with newer hotplug configurations (network was coming
	 * up and making calls beक्रमe the device was initialized).
	 */
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
		       "Error calling register_netdev.\n");
		जाओ fail;
	पूर्ण
	रेजिस्टरed = 2;

	mutex_lock(&priv->action_mutex);

	IPW_DEBUG_INFO("%s: Bound to %s\n", dev->name, pci_name(pci_dev));

	/* perक्रमm this after रेजिस्टर_netdev so that dev->name is set */
	err = sysfs_create_group(&pci_dev->dev.kobj, &ipw2100_attribute_group);
	अगर (err)
		जाओ fail_unlock;

	/* If the RF Kill चयन is disabled, go ahead and complete the
	 * startup sequence */
	अगर (!(priv->status & STATUS_RF_KILL_MASK)) अणु
		/* Enable the adapter - sends HOST_COMPLETE */
		अगर (ipw2100_enable_adapter(priv)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
			       ": %s: failed in call to enable adapter.\n",
			       priv->net_dev->name);
			ipw2100_hw_stop_adapter(priv);
			err = -EIO;
			जाओ fail_unlock;
		पूर्ण

		/* Start a scan . . . */
		ipw2100_set_scan_options(priv);
		ipw2100_start_scan(priv);
	पूर्ण

	IPW_DEBUG_INFO("exit\n");

	priv->status |= STATUS_INITIALIZED;

	mutex_unlock(&priv->action_mutex);
out:
	वापस err;

      fail_unlock:
	mutex_unlock(&priv->action_mutex);
      fail:
	अगर (dev) अणु
		अगर (रेजिस्टरed >= 2)
			unरेजिस्टर_netdev(dev);

		अगर (रेजिस्टरed) अणु
			wiphy_unरेजिस्टर(priv->ieee->wdev.wiphy);
			kमुक्त(priv->ieee->bg_band.channels);
		पूर्ण

		ipw2100_hw_stop_adapter(priv);

		ipw2100_disable_पूर्णांकerrupts(priv);

		अगर (dev->irq)
			मुक्त_irq(dev->irq, priv);

		ipw2100_समाप्त_works(priv);

		/* These are safe to call even अगर they weren't allocated */
		ipw2100_queues_मुक्त(priv);
		sysfs_हटाओ_group(&pci_dev->dev.kobj,
				   &ipw2100_attribute_group);

		मुक्त_libipw(dev, 0);
	पूर्ण

	pci_iounmap(pci_dev, ioaddr);

	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);
	जाओ out;
पूर्ण

अटल व्योम ipw2100_pci_हटाओ_one(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा ipw2100_priv *priv = pci_get_drvdata(pci_dev);
	काष्ठा net_device *dev = priv->net_dev;

	mutex_lock(&priv->action_mutex);

	priv->status &= ~STATUS_INITIALIZED;

	sysfs_हटाओ_group(&pci_dev->dev.kobj, &ipw2100_attribute_group);

#अगर_घोषित CONFIG_PM
	अगर (ipw2100_firmware.version)
		ipw2100_release_firmware(priv, &ipw2100_firmware);
#पूर्ण_अगर
	/* Take करोwn the hardware */
	ipw2100_करोwn(priv);

	/* Release the mutex so that the network subप्रणाली can
	 * complete any needed calls पूर्णांकo the driver... */
	mutex_unlock(&priv->action_mutex);

	/* Unरेजिस्टर the device first - this results in बंद()
	 * being called अगर the device is खोलो.  If we मुक्त storage
	 * first, then बंद() will crash.
	 * FIXME: हटाओ the comment above. */
	unरेजिस्टर_netdev(dev);

	ipw2100_समाप्त_works(priv);

	ipw2100_queues_मुक्त(priv);

	/* Free potential debugging firmware snapshot */
	ipw2100_snapshot_मुक्त(priv);

	मुक्त_irq(dev->irq, priv);

	pci_iounmap(pci_dev, priv->ioaddr);

	/* wiphy_unरेजिस्टर needs to be here, beक्रमe मुक्त_libipw */
	wiphy_unरेजिस्टर(priv->ieee->wdev.wiphy);
	kमुक्त(priv->ieee->bg_band.channels);
	मुक्त_libipw(dev, 0);

	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);

	IPW_DEBUG_INFO("exit\n");
पूर्ण

अटल पूर्णांक __maybe_unused ipw2100_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा ipw2100_priv *priv = dev_get_drvdata(dev_d);
	काष्ठा net_device *dev = priv->net_dev;

	IPW_DEBUG_INFO("%s: Going into suspend...\n", dev->name);

	mutex_lock(&priv->action_mutex);
	अगर (priv->status & STATUS_INITIALIZED) अणु
		/* Take करोwn the device; घातers it off, etc. */
		ipw2100_करोwn(priv);
	पूर्ण

	/* Remove the PRESENT state of the device */
	netअगर_device_detach(dev);

	priv->suspend_at = kसमय_get_bootसमय_seconds();

	mutex_unlock(&priv->action_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ipw2100_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev_d);
	काष्ठा ipw2100_priv *priv = pci_get_drvdata(pci_dev);
	काष्ठा net_device *dev = priv->net_dev;
	u32 val;

	अगर (IPW2100_PM_DISABLED)
		वापस 0;

	mutex_lock(&priv->action_mutex);

	IPW_DEBUG_INFO("%s: Coming out of suspend...\n", dev->name);

	/*
	 * Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep PCI Tx retries
	 * from पूर्णांकerfering with C3 CPU state. pci_restore_state won't help
	 * here since it only restores the first 64 bytes pci config header.
	 */
	pci_पढ़ो_config_dword(pci_dev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pci_dev, 0x40, val & 0xffff00ff);

	/* Set the device back पूर्णांकo the PRESENT state; this will also wake
	 * the queue of needed */
	netअगर_device_attach(dev);

	priv->suspend_समय = kसमय_get_bootसमय_seconds() - priv->suspend_at;

	/* Bring the device back up */
	अगर (!(priv->status & STATUS_RF_KILL_SW))
		ipw2100_up(priv, 0);

	mutex_unlock(&priv->action_mutex);

	वापस 0;
पूर्ण

अटल व्योम ipw2100_shutकरोwn(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा ipw2100_priv *priv = pci_get_drvdata(pci_dev);

	/* Take करोwn the device; घातers it off, etc. */
	ipw2100_करोwn(priv);

	pci_disable_device(pci_dev);
पूर्ण

#घोषणा IPW2100_DEV_ID(x) अणु PCI_VENDOR_ID_INTEL, 0x1043, 0x8086, x पूर्ण

अटल स्थिर काष्ठा pci_device_id ipw2100_pci_id_table[] = अणु
	IPW2100_DEV_ID(0x2520),	/* IN 2100A mPCI 3A */
	IPW2100_DEV_ID(0x2521),	/* IN 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2524),	/* IN 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2525),	/* IN 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2526),	/* IN 2100A mPCI Gen A3 */
	IPW2100_DEV_ID(0x2522),	/* IN 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2523),	/* IN 2100 mPCI 3A */
	IPW2100_DEV_ID(0x2527),	/* IN 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2528),	/* IN 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2529),	/* IN 2100 mPCI 3B */
	IPW2100_DEV_ID(0x252B),	/* IN 2100 mPCI 3A */
	IPW2100_DEV_ID(0x252C),	/* IN 2100 mPCI 3A */
	IPW2100_DEV_ID(0x252D),	/* IN 2100 mPCI 3A */

	IPW2100_DEV_ID(0x2550),	/* IB 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2551),	/* IB 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2553),	/* IB 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2554),	/* IB 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2555),	/* IB 2100 mPCI 3B */

	IPW2100_DEV_ID(0x2560),	/* DE 2100A mPCI 3A */
	IPW2100_DEV_ID(0x2562),	/* DE 2100A mPCI 3A */
	IPW2100_DEV_ID(0x2563),	/* DE 2100A mPCI 3A */
	IPW2100_DEV_ID(0x2561),	/* DE 2100 mPCI 3A */
	IPW2100_DEV_ID(0x2565),	/* DE 2100 mPCI 3A */
	IPW2100_DEV_ID(0x2566),	/* DE 2100 mPCI 3A */
	IPW2100_DEV_ID(0x2567),	/* DE 2100 mPCI 3A */

	IPW2100_DEV_ID(0x2570),	/* GA 2100 mPCI 3B */

	IPW2100_DEV_ID(0x2580),	/* TO 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2582),	/* TO 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2583),	/* TO 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2581),	/* TO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2585),	/* TO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2586),	/* TO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2587),	/* TO 2100 mPCI 3B */

	IPW2100_DEV_ID(0x2590),	/* SO 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2592),	/* SO 2100A mPCI 3B */
	IPW2100_DEV_ID(0x2591),	/* SO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2593),	/* SO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2596),	/* SO 2100 mPCI 3B */
	IPW2100_DEV_ID(0x2598),	/* SO 2100 mPCI 3B */

	IPW2100_DEV_ID(0x25A0),	/* HP 2100 mPCI 3B */
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ipw2100_pci_id_table);

अटल SIMPLE_DEV_PM_OPS(ipw2100_pm_ops, ipw2100_suspend, ipw2100_resume);

अटल काष्ठा pci_driver ipw2100_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = ipw2100_pci_id_table,
	.probe = ipw2100_pci_init_one,
	.हटाओ = ipw2100_pci_हटाओ_one,
	.driver.pm = &ipw2100_pm_ops,
	.shutकरोwn = ipw2100_shutकरोwn,
पूर्ण;

/**
 * Initialize the ipw2100 driver/module
 *
 * @वापसs 0 अगर ok, < 0 त्रुटि_सं node con error.
 *
 * Note: we cannot init the /proc stuff until the PCI driver is there,
 * or we risk an unlikely race condition on someone accessing
 * uninitialized data in the PCI dev काष्ठा through /proc.
 */
अटल पूर्णांक __init ipw2100_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO DRV_NAME ": %s, %s\n", DRV_DESCRIPTION, DRV_VERSION);
	prपूर्णांकk(KERN_INFO DRV_NAME ": %s\n", DRV_COPYRIGHT);

	cpu_latency_qos_add_request(&ipw2100_pm_qos_req, PM_QOS_DEFAULT_VALUE);

	ret = pci_रेजिस्टर_driver(&ipw2100_pci_driver);
	अगर (ret)
		जाओ out;

#अगर_घोषित CONFIG_IPW2100_DEBUG
	ipw2100_debug_level = debug;
	ret = driver_create_file(&ipw2100_pci_driver.driver,
				 &driver_attr_debug_level);
#पूर्ण_अगर

out:
	वापस ret;
पूर्ण

/**
 * Cleanup ipw2100 driver registration
 */
अटल व्योम __निकास ipw2100_निकास(व्योम)
अणु
	/* FIXME: IPG: check that we have no instances of the devices खोलो */
#अगर_घोषित CONFIG_IPW2100_DEBUG
	driver_हटाओ_file(&ipw2100_pci_driver.driver,
			   &driver_attr_debug_level);
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&ipw2100_pci_driver);
	cpu_latency_qos_हटाओ_request(&ipw2100_pm_qos_req);
पूर्ण

module_init(ipw2100_init);
module_निकास(ipw2100_निकास);

अटल पूर्णांक ipw2100_wx_get_name(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अगर (!(priv->status & STATUS_ASSOCIATED))
		म_नकल(wrqu->name, "unassociated");
	अन्यथा
		snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11b");

	IPW_DEBUG_WX("Name: %s\n", wrqu->name);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_freq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा iw_freq *fwrq = &wrqu->freq;
	पूर्णांक err = 0;

	अगर (priv->ieee->iw_mode == IW_MODE_INFRA)
		वापस -EOPNOTSUPP;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* अगर setting by freq convert to channel */
	अगर (fwrq->e == 1) अणु
		अगर ((fwrq->m >= (पूर्णांक)2.412e8 && fwrq->m <= (पूर्णांक)2.487e8)) अणु
			पूर्णांक f = fwrq->m / 100000;
			पूर्णांक c = 0;

			जबतक ((c < REG_MAX_CHANNEL) &&
			       (f != ipw2100_frequencies[c]))
				c++;

			/* hack to fall through */
			fwrq->e = 0;
			fwrq->m = c + 1;
		पूर्ण
	पूर्ण

	अगर (fwrq->e > 0 || fwrq->m > 1000) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण अन्यथा अणु		/* Set the channel */
		IPW_DEBUG_WX("SET Freq/Channel -> %d\n", fwrq->m);
		err = ipw2100_set_channel(priv, fwrq->m, 0);
	पूर्ण

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_freq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->freq.e = 0;

	/* If we are associated, trying to associate, or have a अटलally
	 * configured CHANNEL then वापस that; otherwise वापस ANY */
	अगर (priv->config & CFG_STATIC_CHANNEL ||
	    priv->status & STATUS_ASSOCIATED)
		wrqu->freq.m = priv->channel;
	अन्यथा
		wrqu->freq.m = 0;

	IPW_DEBUG_WX("GET Freq/Channel -> %d\n", priv->channel);
	वापस 0;

पूर्ण

अटल पूर्णांक ipw2100_wx_set_mode(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	IPW_DEBUG_WX("SET Mode -> %d\n", wrqu->mode);

	अगर (wrqu->mode == priv->ieee->iw_mode)
		वापस 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	चयन (wrqu->mode) अणु
#अगर_घोषित CONFIG_IPW2100_MONITOR
	हाल IW_MODE_MONITOR:
		err = ipw2100_चयन_mode(priv, IW_MODE_MONITOR);
		अवरोध;
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */
	हाल IW_MODE_ADHOC:
		err = ipw2100_चयन_mode(priv, IW_MODE_ADHOC);
		अवरोध;
	हाल IW_MODE_INFRA:
	हाल IW_MODE_AUTO:
	शेष:
		err = ipw2100_चयन_mode(priv, IW_MODE_INFRA);
		अवरोध;
	पूर्ण

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_mode(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->mode = priv->ieee->iw_mode;
	IPW_DEBUG_WX("GET Mode -> %d\n", wrqu->mode);

	वापस 0;
पूर्ण

#घोषणा POWER_MODES 5

/* Values are in microsecond */
अटल स्थिर s32 समयout_duration[POWER_MODES] = अणु
	350000,
	250000,
	75000,
	37000,
	25000,
पूर्ण;

अटल स्थिर s32 period_duration[POWER_MODES] = अणु
	400000,
	700000,
	1000000,
	1000000,
	1000000
पूर्ण;

अटल पूर्णांक ipw2100_wx_get_range(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	u16 val;
	पूर्णांक i, level;

	wrqu->data.length = माप(*range);
	स_रखो(range, 0, माप(*range));

	/* Let's try to keep this काष्ठा in the same order as in
	 * linux/include/wireless.h
	 */

	/* TODO: See what values we can set, and हटाओ the ones we can't
	 * set, or fill them with some शेष data.
	 */

	/* ~5 Mb/s real (802.11b) */
	range->throughput = 5 * 1000 * 1000;

//      range->sensitivity;     /* संकेत level threshold range */

	range->max_qual.qual = 100;
	/* TODO: Find real max RSSI and stick here */
	range->max_qual.level = 0;
	range->max_qual.noise = 0;
	range->max_qual.updated = 7;	/* Updated all three */

	range->avg_qual.qual = 70;	/* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshold value क्रम RSSI */
	range->avg_qual.level = 20 + IPW2100_RSSI_TO_DBM;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7;	/* Updated all three */

	range->num_bitrates = RATE_COUNT;

	क्रम (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++) अणु
		range->bitrate[i] = ipw2100_bg_rates[i].bitrate * 100 * 1000;
	पूर्ण

	range->min_rts = MIN_RTS_THRESHOLD;
	range->max_rts = MAX_RTS_THRESHOLD;
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->min_pmp = period_duration[0];	/* Minimal PM period */
	range->max_pmp = period_duration[POWER_MODES - 1];	/* Maximal PM period */
	range->min_pmt = समयout_duration[POWER_MODES - 1];	/* Minimal PM समयout */
	range->max_pmt = समयout_duration[0];	/* Maximal PM समयout */

	/* How to decode max/min PM period */
	range->pmp_flags = IW_POWER_PERIOD;
	/* How to decode max/min PM period */
	range->pmt_flags = IW_POWER_TIMEOUT;
	/* What PM options are supported */
	range->pm_capa = IW_POWER_TIMEOUT | IW_POWER_PERIOD;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;	/* Dअगरferent token sizes */
	range->num_encoding_sizes = 2;	/* Number of entry in the list */
	range->max_encoding_tokens = WEP_KEYS;	/* Max number of tokens */
//      range->encoding_login_index;            /* token index क्रम login token */

	अगर (priv->ieee->iw_mode == IW_MODE_ADHOC) अणु
		range->txघातer_capa = IW_TXPOW_DBM;
		range->num_txघातer = IW_MAX_TXPOWER;
		क्रम (i = 0, level = (IPW_TX_POWER_MAX_DBM * 16);
		     i < IW_MAX_TXPOWER;
		     i++, level -=
		     ((IPW_TX_POWER_MAX_DBM -
		       IPW_TX_POWER_MIN_DBM) * 16) / (IW_MAX_TXPOWER - 1))
			range->txघातer[i] = level / 16;
	पूर्ण अन्यथा अणु
		range->txघातer_capa = 0;
		range->num_txघातer = 0;
	पूर्ण

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

//      range->retry_capa;      /* What retry options are supported */
//      range->retry_flags;     /* How to decode max/min retry limit */
//      range->r_समय_flags;    /* How to decode max/min retry lअगरe */
//      range->min_retry;       /* Minimal number of retries */
//      range->max_retry;       /* Maximal number of retries */
//      range->min_r_समय;      /* Minimal retry lअगरeसमय */
//      range->max_r_समय;      /* Maximal retry lअगरeसमय */

	range->num_channels = FREQ_COUNT;

	val = 0;
	क्रम (i = 0; i < FREQ_COUNT; i++) अणु
		// TODO: Include only legal frequencies क्रम some countries
//              अगर (local->channel_mask & (1 << i)) अणु
		range->freq[val].i = i + 1;
		range->freq[val].m = ipw2100_frequencies[i] * 100000;
		range->freq[val].e = 1;
		val++;
//              पूर्ण
		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण
	range->num_frequency = val;

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWAP));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
		IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	IPW_DEBUG_WX("GET Range\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_wap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	// sanity checks
	अगर (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (is_broadcast_ether_addr(wrqu->ap_addr.sa_data) ||
	    is_zero_ether_addr(wrqu->ap_addr.sa_data)) अणु
		/* we disable mandatory BSSID association */
		IPW_DEBUG_WX("exit - disable mandatory BSSID\n");
		priv->config &= ~CFG_STATIC_BSSID;
		err = ipw2100_set_mandatory_bssid(priv, शून्य, 0);
		जाओ करोne;
	पूर्ण

	priv->config |= CFG_STATIC_BSSID;
	स_नकल(priv->mandatory_bssid_mac, wrqu->ap_addr.sa_data, ETH_ALEN);

	err = ipw2100_set_mandatory_bssid(priv, wrqu->ap_addr.sa_data, 0);

	IPW_DEBUG_WX("SET BSSID -> %pM\n", wrqu->ap_addr.sa_data);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_wap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a अटलally
	 * configured BSSID then वापस that; otherwise वापस ANY */
	अगर (priv->config & CFG_STATIC_BSSID || priv->status & STATUS_ASSOCIATED) अणु
		wrqu->ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(wrqu->ap_addr.sa_data, priv->bssid, ETH_ALEN);
	पूर्ण अन्यथा
		eth_zero_addr(wrqu->ap_addr.sa_data);

	IPW_DEBUG_WX("Getting WAP BSSID: %pM\n", wrqu->ap_addr.sa_data);
	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अक्षर *essid = "";	/* ANY */
	पूर्णांक length = 0;
	पूर्णांक err = 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (wrqu->essid.flags && wrqu->essid.length) अणु
		length = wrqu->essid.length;
		essid = extra;
	पूर्ण

	अगर (length == 0) अणु
		IPW_DEBUG_WX("Setting ESSID to ANY\n");
		priv->config &= ~CFG_STATIC_ESSID;
		err = ipw2100_set_essid(priv, शून्य, 0, 0);
		जाओ करोne;
	पूर्ण

	length = min(length, IW_ESSID_MAX_SIZE);

	priv->config |= CFG_STATIC_ESSID;

	अगर (priv->essid_len == length && !स_भेद(priv->essid, extra, length)) अणु
		IPW_DEBUG_WX("ESSID set to current ESSID.\n");
		err = 0;
		जाओ करोne;
	पूर्ण

	IPW_DEBUG_WX("Setting ESSID: '%*pE' (%d)\n", length, essid, length);

	priv->essid_len = length;
	स_नकल(priv->essid, essid, priv->essid_len);

	err = ipw2100_set_essid(priv, essid, length, 0);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	/* If we are associated, trying to associate, or have a अटलally
	 * configured ESSID then वापस that; otherwise वापस ANY */
	अगर (priv->config & CFG_STATIC_ESSID || priv->status & STATUS_ASSOCIATED) अणु
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

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_nick(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	अगर (wrqu->data.length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;

	wrqu->data.length = min_t(माप_प्रकार, wrqu->data.length, माप(priv->nick));
	स_रखो(priv->nick, 0, माप(priv->nick));
	स_नकल(priv->nick, extra, wrqu->data.length);

	IPW_DEBUG_WX("SET Nickname -> %s\n", priv->nick);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_nick(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->data.length = म_माप(priv->nick);
	स_नकल(extra, priv->nick, wrqu->data.length);
	wrqu->data.flags = 1;	/* active */

	IPW_DEBUG_WX("GET Nickname -> %s\n", extra);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_rate(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	u32 target_rate = wrqu->bitrate.value;
	u32 rate;
	पूर्णांक err = 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	rate = 0;

	अगर (target_rate == 1000000 ||
	    (!wrqu->bitrate.fixed && target_rate > 1000000))
		rate |= TX_RATE_1_MBIT;
	अगर (target_rate == 2000000 ||
	    (!wrqu->bitrate.fixed && target_rate > 2000000))
		rate |= TX_RATE_2_MBIT;
	अगर (target_rate == 5500000 ||
	    (!wrqu->bitrate.fixed && target_rate > 5500000))
		rate |= TX_RATE_5_5_MBIT;
	अगर (target_rate == 11000000 ||
	    (!wrqu->bitrate.fixed && target_rate > 11000000))
		rate |= TX_RATE_11_MBIT;
	अगर (rate == 0)
		rate = DEFAULT_TX_RATES;

	err = ipw2100_set_tx_rates(priv, rate, 0);

	IPW_DEBUG_WX("SET Rate -> %04X\n", rate);
      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_rate(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक val;
	अचिन्हित पूर्णांक len = माप(val);
	पूर्णांक err = 0;

	अगर (!(priv->status & STATUS_ENABLED) ||
	    priv->status & STATUS_RF_KILL_MASK ||
	    !(priv->status & STATUS_ASSOCIATED)) अणु
		wrqu->bitrate.value = 0;
		वापस 0;
	पूर्ण

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	err = ipw2100_get_ordinal(priv, IPW_ORD_CURRENT_TX_RATE, &val, &len);
	अगर (err) अणु
		IPW_DEBUG_WX("failed querying ordinals.\n");
		जाओ करोne;
	पूर्ण

	चयन (val & TX_RATE_MASK) अणु
	हाल TX_RATE_1_MBIT:
		wrqu->bitrate.value = 1000000;
		अवरोध;
	हाल TX_RATE_2_MBIT:
		wrqu->bitrate.value = 2000000;
		अवरोध;
	हाल TX_RATE_5_5_MBIT:
		wrqu->bitrate.value = 5500000;
		अवरोध;
	हाल TX_RATE_11_MBIT:
		wrqu->bitrate.value = 11000000;
		अवरोध;
	शेष:
		wrqu->bitrate.value = 0;
	पूर्ण

	IPW_DEBUG_WX("GET Rate -> %d\n", wrqu->bitrate.value);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_rts(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक value, err;

	/* Auto RTS not yet supported */
	अगर (wrqu->rts.fixed == 0)
		वापस -EINVAL;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (wrqu->rts.disabled)
		value = priv->rts_threshold | RTS_DISABLED;
	अन्यथा अणु
		अगर (wrqu->rts.value < 1 || wrqu->rts.value > 2304) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
		value = wrqu->rts.value;
	पूर्ण

	err = ipw2100_set_rts_threshold(priv, value);

	IPW_DEBUG_WX("SET RTS Threshold -> 0x%08X\n", value);
      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_rts(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->rts.value = priv->rts_threshold & ~RTS_DISABLED;
	wrqu->rts.fixed = 1;	/* no स्वतः select */

	/* If RTS is set to the शेष value, then it is disabled */
	wrqu->rts.disabled = (priv->rts_threshold & RTS_DISABLED) ? 1 : 0;

	IPW_DEBUG_WX("GET RTS Threshold -> 0x%08X\n", wrqu->rts.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_txघात(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0, value;
	
	अगर (ipw_radio_समाप्त_sw(priv, wrqu->txघातer.disabled))
		वापस -EINPROGRESS;

	अगर (priv->ieee->iw_mode != IW_MODE_ADHOC)
		वापस 0;

	अगर ((wrqu->txघातer.flags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		वापस -EINVAL;

	अगर (wrqu->txघातer.fixed == 0)
		value = IPW_TX_POWER_DEFAULT;
	अन्यथा अणु
		अगर (wrqu->txघातer.value < IPW_TX_POWER_MIN_DBM ||
		    wrqu->txघातer.value > IPW_TX_POWER_MAX_DBM)
			वापस -EINVAL;

		value = wrqu->txघातer.value;
	पूर्ण

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	err = ipw2100_set_tx_घातer(priv, value);

	IPW_DEBUG_WX("SET TX Power -> %d\n", value);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_txघात(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->txघातer.disabled = (priv->status & STATUS_RF_KILL_MASK) ? 1 : 0;

	अगर (priv->tx_घातer == IPW_TX_POWER_DEFAULT) अणु
		wrqu->txघातer.fixed = 0;
		wrqu->txघातer.value = IPW_TX_POWER_MAX_DBM;
	पूर्ण अन्यथा अणु
		wrqu->txघातer.fixed = 1;
		wrqu->txघातer.value = priv->tx_घातer;
	पूर्ण

	wrqu->txघातer.flags = IW_TXPOW_DBM;

	IPW_DEBUG_WX("GET TX Power -> %d\n", wrqu->txघातer.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_frag(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	अगर (!wrqu->frag.fixed)
		वापस -EINVAL;

	अगर (wrqu->frag.disabled) अणु
		priv->frag_threshold |= FRAG_DISABLED;
		priv->ieee->fts = DEFAULT_FTS;
	पूर्ण अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;

		priv->ieee->fts = wrqu->frag.value & ~0x1;
		priv->frag_threshold = priv->ieee->fts;
	पूर्ण

	IPW_DEBUG_WX("SET Frag Threshold -> %d\n", priv->ieee->fts);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_frag(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	wrqu->frag.value = priv->frag_threshold & ~FRAG_DISABLED;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	wrqu->frag.disabled = (priv->frag_threshold & FRAG_DISABLED) ? 1 : 0;

	IPW_DEBUG_WX("GET Frag Threshold -> %d\n", wrqu->frag.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_retry(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	अगर (wrqu->retry.flags & IW_RETRY_LIFETIME || wrqu->retry.disabled)
		वापस -EINVAL;

	अगर (!(wrqu->retry.flags & IW_RETRY_LIMIT))
		वापस 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (wrqu->retry.flags & IW_RETRY_SHORT) अणु
		err = ipw2100_set_लघु_retry(priv, wrqu->retry.value);
		IPW_DEBUG_WX("SET Short Retry Limit -> %d\n",
			     wrqu->retry.value);
		जाओ करोne;
	पूर्ण

	अगर (wrqu->retry.flags & IW_RETRY_LONG) अणु
		err = ipw2100_set_दीर्घ_retry(priv, wrqu->retry.value);
		IPW_DEBUG_WX("SET Long Retry Limit -> %d\n",
			     wrqu->retry.value);
		जाओ करोne;
	पूर्ण

	err = ipw2100_set_लघु_retry(priv, wrqu->retry.value);
	अगर (!err)
		err = ipw2100_set_दीर्घ_retry(priv, wrqu->retry.value);

	IPW_DEBUG_WX("SET Both Retry Limits -> %d\n", wrqu->retry.value);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_retry(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	wrqu->retry.disabled = 0;	/* can't be disabled */

	अगर ((wrqu->retry.flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME)
		वापस -EINVAL;

	अगर (wrqu->retry.flags & IW_RETRY_LONG) अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		wrqu->retry.value = priv->दीर्घ_retry_limit;
	पूर्ण अन्यथा अणु
		wrqu->retry.flags =
		    (priv->लघु_retry_limit !=
		     priv->दीर्घ_retry_limit) ?
		    IW_RETRY_LIMIT | IW_RETRY_SHORT : IW_RETRY_LIMIT;

		wrqu->retry.value = priv->लघु_retry_limit;
	पूर्ण

	IPW_DEBUG_WX("GET Retry -> %d\n", wrqu->retry.value);

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_scan(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	IPW_DEBUG_WX("Initiating scan...\n");

	priv->user_requested_scan = 1;
	अगर (ipw2100_set_scan_options(priv) || ipw2100_start_scan(priv)) अणु
		IPW_DEBUG_WX("Start scan failed.\n");

		/* TODO: Mark a scan as pending so when hardware initialized
		 *       a scan starts */
	पूर्ण

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_scan(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_scan(priv->ieee, info, wrqu, extra);
पूर्ण

/*
 * Implementation based on code in hostap-driver v0.1.3 hostap_ioctl.c
 */
अटल पूर्णांक ipw2100_wx_set_encode(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	/*
	 * No check of STATUS_INITIALIZED required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस libipw_wx_set_encode(priv->ieee, info, wrqu, key);
पूर्ण

अटल पूर्णांक ipw2100_wx_get_encode(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu, अक्षर *key)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_encode(priv->ieee, info, wrqu, key);
पूर्ण

अटल पूर्णांक ipw2100_wx_set_घातer(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (wrqu->घातer.disabled) अणु
		priv->घातer_mode = IPW_POWER_LEVEL(priv->घातer_mode);
		err = ipw2100_set_घातer_mode(priv, IPW_POWER_MODE_CAM);
		IPW_DEBUG_WX("SET Power Management Mode -> off\n");
		जाओ करोne;
	पूर्ण

	चयन (wrqu->घातer.flags & IW_POWER_MODE) अणु
	हाल IW_POWER_ON:	/* If not specअगरied */
	हाल IW_POWER_MODE:	/* If set all mask */
	हाल IW_POWER_ALL_R:	/* If explicitly state all */
		अवरोध;
	शेष:		/* Otherwise we करोn't support it */
		IPW_DEBUG_WX("SET PM Mode: %X not supported.\n",
			     wrqu->घातer.flags);
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	/* If the user hasn't specअगरied a घातer management mode yet, शेष
	 * to BATTERY */
	priv->घातer_mode = IPW_POWER_ENABLED | priv->घातer_mode;
	err = ipw2100_set_घातer_mode(priv, IPW_POWER_LEVEL(priv->घातer_mode));

	IPW_DEBUG_WX("SET Power Management Mode -> 0x%02X\n", priv->घातer_mode);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;

पूर्ण

अटल पूर्णांक ipw2100_wx_get_घातer(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	अगर (!(priv->घातer_mode & IPW_POWER_ENABLED))
		wrqu->घातer.disabled = 1;
	अन्यथा अणु
		wrqu->घातer.disabled = 0;
		wrqu->घातer.flags = 0;
	पूर्ण

	IPW_DEBUG_WX("GET Power Management Mode -> %02X\n", priv->घातer_mode);

	वापस 0;
पूर्ण

/*
 * WE-18 WPA support
 */

/* SIOCSIWGENIE */
अटल पूर्णांक ipw2100_wx_set_genie(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	u8 *buf;

	अगर (!ieee->wpa_enabled)
		वापस -EOPNOTSUPP;

	अगर (wrqu->data.length > MAX_WPA_IE_LEN ||
	    (wrqu->data.length && extra == शून्य))
		वापस -EINVAL;

	अगर (wrqu->data.length) अणु
		buf = kmemdup(extra, wrqu->data.length, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;

		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = wrqu->data.length;
	पूर्ण अन्यथा अणु
		kमुक्त(ieee->wpa_ie);
		ieee->wpa_ie = शून्य;
		ieee->wpa_ie_len = 0;
	पूर्ण

	ipw2100_wpa_assoc_frame(priv, ieee->wpa_ie, ieee->wpa_ie_len);

	वापस 0;
पूर्ण

/* SIOCGIWGENIE */
अटल पूर्णांक ipw2100_wx_get_genie(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;

	अगर (ieee->wpa_ie_len == 0 || ieee->wpa_ie == शून्य) अणु
		wrqu->data.length = 0;
		वापस 0;
	पूर्ण

	अगर (wrqu->data.length < ieee->wpa_ie_len)
		वापस -E2BIG;

	wrqu->data.length = ieee->wpa_ie_len;
	स_नकल(extra, ieee->wpa_ie, ieee->wpa_ie_len);

	वापस 0;
पूर्ण

/* SIOCSIWAUTH */
अटल पूर्णांक ipw2100_wx_set_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा libipw_device *ieee = priv->ieee;
	काष्ठा iw_param *param = &wrqu->param;
	काष्ठा lib80211_crypt_data *crypt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
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
		ret = ipw2100_wpa_set_auth_algs(priv, param->value);
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		ret = ipw2100_wpa_enable(priv, param->value);
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ieee->ieee802_1x = param->value;
		अवरोध;

		//हाल IW_AUTH_ROAMING_CONTROL:
	हाल IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = param->value;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

/* SIOCGIWAUTH */
अटल पूर्णांक ipw2100_wx_get_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
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
		अवरोध;

	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		crypt = priv->ieee->crypt_info.crypt[priv->ieee->crypt_info.tx_keyidx];
		अगर (!crypt || !crypt->ops->get_flags) अणु
			IPW_DEBUG_WARNING("Can't get TKIP countermeasures: "
					  "crypt not set!\n");
			अवरोध;
		पूर्ण

		param->value = (crypt->ops->get_flags(crypt->priv) &
				IEEE80211_CRYPTO_TKIP_COUNTERMEASURES) ? 1 : 0;

		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		param->value = ieee->drop_unencrypted;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		param->value = priv->ieee->sec.auth_mode;
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
अटल पूर्णांक ipw2100_wx_set_encodeext(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस libipw_wx_set_encodeext(priv->ieee, info, wrqu, extra);
पूर्ण

/* SIOCGIWENCODEEXT */
अटल पूर्णांक ipw2100_wx_get_encodeext(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	वापस libipw_wx_get_encodeext(priv->ieee, info, wrqu, extra);
पूर्ण

/* SIOCSIWMLME */
अटल पूर्णांक ipw2100_wx_set_mlme(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;

	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		// silently ignore
		अवरोध;

	हाल IW_MLME_DISASSOC:
		ipw2100_disassociate_bssid(priv);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *
 * IWPRIV handlers
 *
 */
#अगर_घोषित CONFIG_IPW2100_MONITOR
अटल पूर्णांक ipw2100_wx_set_promisc(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक *parms = (पूर्णांक *)extra;
	पूर्णांक enable = (parms[0] > 0);
	पूर्णांक err = 0;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (enable) अणु
		अगर (priv->ieee->iw_mode == IW_MODE_MONITOR) अणु
			err = ipw2100_set_channel(priv, parms[1], 0);
			जाओ करोne;
		पूर्ण
		priv->channel = parms[1];
		err = ipw2100_चयन_mode(priv, IW_MODE_MONITOR);
	पूर्ण अन्यथा अणु
		अगर (priv->ieee->iw_mode == IW_MODE_MONITOR)
			err = ipw2100_चयन_mode(priv, priv->last_mode);
	पूर्ण
      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_reset(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	अगर (priv->status & STATUS_INITIALIZED)
		schedule_reset(priv);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ipw2100_wx_set_घातermode(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err = 0, mode = *(पूर्णांक *)extra;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर ((mode < 0) || (mode > POWER_MODES))
		mode = IPW_POWER_AUTO;

	अगर (IPW_POWER_LEVEL(priv->घातer_mode) != mode)
		err = ipw2100_set_घातer_mode(priv, mode);
      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

#घोषणा MAX_POWER_STRING 80
अटल पूर्णांक ipw2100_wx_get_घातermode(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक level = IPW_POWER_LEVEL(priv->घातer_mode);
	s32 समयout, period;

	अगर (!(priv->घातer_mode & IPW_POWER_ENABLED)) अणु
		snम_लिखो(extra, MAX_POWER_STRING,
			 "Power save level: %d (Off)", level);
	पूर्ण अन्यथा अणु
		चयन (level) अणु
		हाल IPW_POWER_MODE_CAM:
			snम_लिखो(extra, MAX_POWER_STRING,
				 "Power save level: %d (None)", level);
			अवरोध;
		हाल IPW_POWER_AUTO:
			snम_लिखो(extra, MAX_POWER_STRING,
				 "Power save level: %d (Auto)", level);
			अवरोध;
		शेष:
			समयout = समयout_duration[level - 1] / 1000;
			period = period_duration[level - 1] / 1000;
			snम_लिखो(extra, MAX_POWER_STRING,
				 "Power save level: %d "
				 "(Timeout %dms, Period %dms)",
				 level, समयout, period);
		पूर्ण
	पूर्ण

	wrqu->data.length = म_माप(extra) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_wx_set_preamble(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err, mode = *(पूर्णांक *)extra;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (mode == 1)
		priv->config |= CFG_LONG_PREAMBLE;
	अन्यथा अगर (mode == 0)
		priv->config &= ~CFG_LONG_PREAMBLE;
	अन्यथा अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	err = ipw2100_प्रणाली_config(priv, 0);

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_preamble(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	अगर (priv->config & CFG_LONG_PREAMBLE)
		snम_लिखो(wrqu->name, IFNAMSIZ, "long (1)");
	अन्यथा
		snम_लिखो(wrqu->name, IFNAMSIZ, "auto (0)");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IPW2100_MONITOR
अटल पूर्णांक ipw2100_wx_set_crc_check(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	पूर्णांक err, mode = *(पूर्णांक *)extra;

	mutex_lock(&priv->action_mutex);
	अगर (!(priv->status & STATUS_INITIALIZED)) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (mode == 1)
		priv->config |= CFG_CRC_CHECK;
	अन्यथा अगर (mode == 0)
		priv->config &= ~CFG_CRC_CHECK;
	अन्यथा अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	err = 0;

      करोne:
	mutex_unlock(&priv->action_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ipw2100_wx_get_crc_check(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * This can be called at any समय.  No action lock required
	 */

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);

	अगर (priv->config & CFG_CRC_CHECK)
		snम_लिखो(wrqu->name, IFNAMSIZ, "CRC checked (1)");
	अन्यथा
		snम_लिखो(wrqu->name, IFNAMSIZ, "CRC ignored (0)");

	वापस 0;
पूर्ण
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */

अटल iw_handler ipw2100_wx_handlers[] = अणु
	IW_HANDLER(SIOCGIWNAME, ipw2100_wx_get_name),
	IW_HANDLER(SIOCSIWFREQ, ipw2100_wx_set_freq),
	IW_HANDLER(SIOCGIWFREQ, ipw2100_wx_get_freq),
	IW_HANDLER(SIOCSIWMODE, ipw2100_wx_set_mode),
	IW_HANDLER(SIOCGIWMODE, ipw2100_wx_get_mode),
	IW_HANDLER(SIOCGIWRANGE, ipw2100_wx_get_range),
	IW_HANDLER(SIOCSIWAP, ipw2100_wx_set_wap),
	IW_HANDLER(SIOCGIWAP, ipw2100_wx_get_wap),
	IW_HANDLER(SIOCSIWMLME, ipw2100_wx_set_mlme),
	IW_HANDLER(SIOCSIWSCAN, ipw2100_wx_set_scan),
	IW_HANDLER(SIOCGIWSCAN, ipw2100_wx_get_scan),
	IW_HANDLER(SIOCSIWESSID, ipw2100_wx_set_essid),
	IW_HANDLER(SIOCGIWESSID, ipw2100_wx_get_essid),
	IW_HANDLER(SIOCSIWNICKN, ipw2100_wx_set_nick),
	IW_HANDLER(SIOCGIWNICKN, ipw2100_wx_get_nick),
	IW_HANDLER(SIOCSIWRATE, ipw2100_wx_set_rate),
	IW_HANDLER(SIOCGIWRATE, ipw2100_wx_get_rate),
	IW_HANDLER(SIOCSIWRTS, ipw2100_wx_set_rts),
	IW_HANDLER(SIOCGIWRTS, ipw2100_wx_get_rts),
	IW_HANDLER(SIOCSIWFRAG, ipw2100_wx_set_frag),
	IW_HANDLER(SIOCGIWFRAG, ipw2100_wx_get_frag),
	IW_HANDLER(SIOCSIWTXPOW, ipw2100_wx_set_txघात),
	IW_HANDLER(SIOCGIWTXPOW, ipw2100_wx_get_txघात),
	IW_HANDLER(SIOCSIWRETRY, ipw2100_wx_set_retry),
	IW_HANDLER(SIOCGIWRETRY, ipw2100_wx_get_retry),
	IW_HANDLER(SIOCSIWENCODE, ipw2100_wx_set_encode),
	IW_HANDLER(SIOCGIWENCODE, ipw2100_wx_get_encode),
	IW_HANDLER(SIOCSIWPOWER, ipw2100_wx_set_घातer),
	IW_HANDLER(SIOCGIWPOWER, ipw2100_wx_get_घातer),
	IW_HANDLER(SIOCSIWGENIE, ipw2100_wx_set_genie),
	IW_HANDLER(SIOCGIWGENIE, ipw2100_wx_get_genie),
	IW_HANDLER(SIOCSIWAUTH, ipw2100_wx_set_auth),
	IW_HANDLER(SIOCGIWAUTH, ipw2100_wx_get_auth),
	IW_HANDLER(SIOCSIWENCODEEXT, ipw2100_wx_set_encodeext),
	IW_HANDLER(SIOCGIWENCODEEXT, ipw2100_wx_get_encodeext),
पूर्ण;

#घोषणा IPW2100_PRIV_SET_MONITOR	SIOCIWFIRSTPRIV
#घोषणा IPW2100_PRIV_RESET		SIOCIWFIRSTPRIV+1
#घोषणा IPW2100_PRIV_SET_POWER		SIOCIWFIRSTPRIV+2
#घोषणा IPW2100_PRIV_GET_POWER		SIOCIWFIRSTPRIV+3
#घोषणा IPW2100_PRIV_SET_LONGPREAMBLE	SIOCIWFIRSTPRIV+4
#घोषणा IPW2100_PRIV_GET_LONGPREAMBLE	SIOCIWFIRSTPRIV+5
#घोषणा IPW2100_PRIV_SET_CRC_CHECK	SIOCIWFIRSTPRIV+6
#घोषणा IPW2100_PRIV_GET_CRC_CHECK	SIOCIWFIRSTPRIV+7

अटल स्थिर काष्ठा iw_priv_args ipw2100_निजी_args[] = अणु

#अगर_घोषित CONFIG_IPW2100_MONITOR
	अणु
	 IPW2100_PRIV_SET_MONITOR,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "monitor"पूर्ण,
	अणु
	 IPW2100_PRIV_RESET,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 0, 0, "reset"पूर्ण,
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */

	अणु
	 IPW2100_PRIV_SET_POWER,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "set_power"पूर्ण,
	अणु
	 IPW2100_PRIV_GET_POWER,
	 0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | MAX_POWER_STRING,
	 "get_power"पूर्ण,
	अणु
	 IPW2100_PRIV_SET_LONGPREAMBLE,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "set_preamble"पूर्ण,
	अणु
	 IPW2100_PRIV_GET_LONGPREAMBLE,
	 0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ, "get_preamble"पूर्ण,
#अगर_घोषित CONFIG_IPW2100_MONITOR
	अणु
	 IPW2100_PRIV_SET_CRC_CHECK,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "set_crc_check"पूर्ण,
	अणु
	 IPW2100_PRIV_GET_CRC_CHECK,
	 0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ, "get_crc_check"पूर्ण,
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */
पूर्ण;

अटल iw_handler ipw2100_निजी_handler[] = अणु
#अगर_घोषित CONFIG_IPW2100_MONITOR
	ipw2100_wx_set_promisc,
	ipw2100_wx_reset,
#अन्यथा				/* CONFIG_IPW2100_MONITOR */
	शून्य,
	शून्य,
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */
	ipw2100_wx_set_घातermode,
	ipw2100_wx_get_घातermode,
	ipw2100_wx_set_preamble,
	ipw2100_wx_get_preamble,
#अगर_घोषित CONFIG_IPW2100_MONITOR
	ipw2100_wx_set_crc_check,
	ipw2100_wx_get_crc_check,
#अन्यथा				/* CONFIG_IPW2100_MONITOR */
	शून्य,
	शून्य,
#पूर्ण_अगर				/* CONFIG_IPW2100_MONITOR */
पूर्ण;

/*
 * Get wireless statistics.
 * Called by /proc/net/wireless
 * Also called by SIOCGIWSTATS
 */
अटल काष्ठा iw_statistics *ipw2100_wx_wireless_stats(काष्ठा net_device *dev)
अणु
	क्रमागत अणु
		POOR = 30,
		FAIR = 60,
		GOOD = 80,
		VERY_GOOD = 90,
		EXCELLENT = 95,
		PERFECT = 100
	पूर्ण;
	पूर्णांक rssi_qual;
	पूर्णांक tx_qual;
	पूर्णांक beacon_qual;
	पूर्णांक quality;

	काष्ठा ipw2100_priv *priv = libipw_priv(dev);
	काष्ठा iw_statistics *wstats;
	u32 rssi, tx_retries, missed_beacons, tx_failures;
	u32 ord_len = माप(u32);

	अगर (!priv)
		वापस (काष्ठा iw_statistics *)शून्य;

	wstats = &priv->wstats;

	/* अगर hw is disabled, then ipw2100_get_ordinal() can't be called.
	 * ipw2100_wx_wireless_stats seems to be called beक्रमe fw is
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

	अगर (ipw2100_get_ordinal(priv, IPW_ORD_STAT_PERCENT_MISSED_BCNS,
				&missed_beacons, &ord_len))
		जाओ fail_get_ordinal;

	/* If we करोn't have a connection the quality and level is 0 */
	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
	पूर्ण अन्यथा अणु
		अगर (ipw2100_get_ordinal(priv, IPW_ORD_RSSI_AVG_CURR,
					&rssi, &ord_len))
			जाओ fail_get_ordinal;
		wstats->qual.level = rssi + IPW2100_RSSI_TO_DBM;
		अगर (rssi < 10)
			rssi_qual = rssi * POOR / 10;
		अन्यथा अगर (rssi < 15)
			rssi_qual = (rssi - 10) * (FAIR - POOR) / 5 + POOR;
		अन्यथा अगर (rssi < 20)
			rssi_qual = (rssi - 15) * (GOOD - FAIR) / 5 + FAIR;
		अन्यथा अगर (rssi < 30)
			rssi_qual = (rssi - 20) * (VERY_GOOD - GOOD) /
			    10 + GOOD;
		अन्यथा
			rssi_qual = (rssi - 30) * (PERFECT - VERY_GOOD) /
			    10 + VERY_GOOD;

		अगर (ipw2100_get_ordinal(priv, IPW_ORD_STAT_PERCENT_RETRIES,
					&tx_retries, &ord_len))
			जाओ fail_get_ordinal;

		अगर (tx_retries > 75)
			tx_qual = (90 - tx_retries) * POOR / 15;
		अन्यथा अगर (tx_retries > 70)
			tx_qual = (75 - tx_retries) * (FAIR - POOR) / 5 + POOR;
		अन्यथा अगर (tx_retries > 65)
			tx_qual = (70 - tx_retries) * (GOOD - FAIR) / 5 + FAIR;
		अन्यथा अगर (tx_retries > 50)
			tx_qual = (65 - tx_retries) * (VERY_GOOD - GOOD) /
			    15 + GOOD;
		अन्यथा
			tx_qual = (50 - tx_retries) *
			    (PERFECT - VERY_GOOD) / 50 + VERY_GOOD;

		अगर (missed_beacons > 50)
			beacon_qual = (60 - missed_beacons) * POOR / 10;
		अन्यथा अगर (missed_beacons > 40)
			beacon_qual = (50 - missed_beacons) * (FAIR - POOR) /
			    10 + POOR;
		अन्यथा अगर (missed_beacons > 32)
			beacon_qual = (40 - missed_beacons) * (GOOD - FAIR) /
			    18 + FAIR;
		अन्यथा अगर (missed_beacons > 20)
			beacon_qual = (32 - missed_beacons) *
			    (VERY_GOOD - GOOD) / 20 + GOOD;
		अन्यथा
			beacon_qual = (20 - missed_beacons) *
			    (PERFECT - VERY_GOOD) / 20 + VERY_GOOD;

		quality = min(tx_qual, rssi_qual);
		quality = min(beacon_qual, quality);

#अगर_घोषित CONFIG_IPW2100_DEBUG
		अगर (beacon_qual == quality)
			IPW_DEBUG_WX("Quality clamped by Missed Beacons\n");
		अन्यथा अगर (tx_qual == quality)
			IPW_DEBUG_WX("Quality clamped by Tx Retries\n");
		अन्यथा अगर (quality != 100)
			IPW_DEBUG_WX("Quality clamped by Signal Strength\n");
		अन्यथा
			IPW_DEBUG_WX("Quality not clamped.\n");
#पूर्ण_अगर

		wstats->qual.qual = quality;
		wstats->qual.level = rssi + IPW2100_RSSI_TO_DBM;
	पूर्ण

	wstats->qual.noise = 0;
	wstats->qual.updated = 7;
	wstats->qual.updated |= IW_QUAL_NOISE_INVALID;

	/* FIXME: this is percent and not a # */
	wstats->miss.beacon = missed_beacons;

	अगर (ipw2100_get_ordinal(priv, IPW_ORD_STAT_TX_FAILURES,
				&tx_failures, &ord_len))
		जाओ fail_get_ordinal;
	wstats->discard.retries = tx_failures;

	वापस wstats;

      fail_get_ordinal:
	IPW_DEBUG_WX("failed querying ordinals.\n");

	वापस (काष्ठा iw_statistics *)शून्य;
पूर्ण

अटल स्थिर काष्ठा iw_handler_def ipw2100_wx_handler_def = अणु
	.standard = ipw2100_wx_handlers,
	.num_standard = ARRAY_SIZE(ipw2100_wx_handlers),
	.num_निजी = ARRAY_SIZE(ipw2100_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(ipw2100_निजी_args),
	.निजी = (iw_handler *) ipw2100_निजी_handler,
	.निजी_args = (काष्ठा iw_priv_args *)ipw2100_निजी_args,
	.get_wireless_stats = ipw2100_wx_wireless_stats,
पूर्ण;

अटल व्योम ipw2100_wx_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipw2100_priv *priv =
		container_of(work, काष्ठा ipw2100_priv, wx_event_work.work);
	जोड़ iwreq_data wrqu;
	अचिन्हित पूर्णांक len = ETH_ALEN;

	अगर (priv->status & STATUS_STOPPING)
		वापस;

	mutex_lock(&priv->action_mutex);

	IPW_DEBUG_WX("enter\n");

	mutex_unlock(&priv->action_mutex);

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/* Fetch BSSID from the hardware */
	अगर (!(priv->status & (STATUS_ASSOCIATING | STATUS_ASSOCIATED)) ||
	    priv->status & STATUS_RF_KILL_MASK ||
	    ipw2100_get_ordinal(priv, IPW_ORD_STAT_ASSN_AP_BSSID,
				&priv->bssid, &len)) अणु
		eth_zero_addr(wrqu.ap_addr.sa_data);
	पूर्ण अन्यथा अणु
		/* We now have the BSSID, so can finish setting to the full
		 * associated state */
		स_नकल(wrqu.ap_addr.sa_data, priv->bssid, ETH_ALEN);
		स_नकल(priv->ieee->bssid, priv->bssid, ETH_ALEN);
		priv->status &= ~STATUS_ASSOCIATING;
		priv->status |= STATUS_ASSOCIATED;
		netअगर_carrier_on(priv->net_dev);
		netअगर_wake_queue(priv->net_dev);
	पूर्ण

	अगर (!(priv->status & STATUS_ASSOCIATED)) अणु
		IPW_DEBUG_WX("Configuring ESSID\n");
		mutex_lock(&priv->action_mutex);
		/* This is a disassociation event, so kick the firmware to
		 * look क्रम another AP */
		अगर (priv->config & CFG_STATIC_ESSID)
			ipw2100_set_essid(priv, priv->essid, priv->essid_len,
					  0);
		अन्यथा
			ipw2100_set_essid(priv, शून्य, 0, 0);
		mutex_unlock(&priv->action_mutex);
	पूर्ण

	wireless_send_event(priv->net_dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

#घोषणा IPW2100_FW_MAJOR_VERSION 1
#घोषणा IPW2100_FW_MINOR_VERSION 3

#घोषणा IPW2100_FW_MINOR(x) ((x & 0xff) >> 8)
#घोषणा IPW2100_FW_MAJOR(x) (x & 0xff)

#घोषणा IPW2100_FW_VERSION ((IPW2100_FW_MINOR_VERSION << 8) | \
                             IPW2100_FW_MAJOR_VERSION)

#घोषणा IPW2100_FW_PREFIX "ipw2100-" __stringअगरy(IPW2100_FW_MAJOR_VERSION) \
"." __stringअगरy(IPW2100_FW_MINOR_VERSION)

#घोषणा IPW2100_FW_NAME(x) IPW2100_FW_PREFIX "" x ".fw"

/*

BINARY FIRMWARE HEADER FORMAT

offset      length   desc
0           2        version
2           2        mode == 0:BSS,1:IBSS,2:MONITOR
4           4        fw_len
8           4        uc_len
C           fw_len   firmware data
12 + fw_len uc_len   microcode data

*/

काष्ठा ipw2100_fw_header अणु
	लघु version;
	लघु mode;
	अचिन्हित पूर्णांक fw_size;
	अचिन्हित पूर्णांक uc_size;
पूर्ण __packed;

अटल पूर्णांक ipw2100_mod_firmware_load(काष्ठा ipw2100_fw *fw)
अणु
	काष्ठा ipw2100_fw_header *h =
	    (काष्ठा ipw2100_fw_header *)fw->fw_entry->data;

	अगर (IPW2100_FW_MAJOR(h->version) != IPW2100_FW_MAJOR_VERSION) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": Firmware image not compatible "
		       "(detected version id of %u). "
		       "See Documentation/networking/device_drivers/wifi/intel/ipw2100.rst\n",
		       h->version);
		वापस 1;
	पूर्ण

	fw->version = h->version;
	fw->fw.data = fw->fw_entry->data + माप(काष्ठा ipw2100_fw_header);
	fw->fw.size = h->fw_size;
	fw->uc.data = fw->fw.data + h->fw_size;
	fw->uc.size = h->uc_size;

	वापस 0;
पूर्ण

अटल पूर्णांक ipw2100_get_firmware(काष्ठा ipw2100_priv *priv,
				काष्ठा ipw2100_fw *fw)
अणु
	अक्षर *fw_name;
	पूर्णांक rc;

	IPW_DEBUG_INFO("%s: Using hotplug firmware load.\n",
		       priv->net_dev->name);

	चयन (priv->ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		fw_name = IPW2100_FW_NAME("-i");
		अवरोध;
#अगर_घोषित CONFIG_IPW2100_MONITOR
	हाल IW_MODE_MONITOR:
		fw_name = IPW2100_FW_NAME("-p");
		अवरोध;
#पूर्ण_अगर
	हाल IW_MODE_INFRA:
	शेष:
		fw_name = IPW2100_FW_NAME("");
		अवरोध;
	पूर्ण

	rc = request_firmware(&fw->fw_entry, fw_name, &priv->pci_dev->dev);

	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": "
		       "%s: Firmware '%s' not available or load failed.\n",
		       priv->net_dev->name, fw_name);
		वापस rc;
	पूर्ण
	IPW_DEBUG_INFO("firmware data %p size %zd\n", fw->fw_entry->data,
		       fw->fw_entry->size);

	ipw2100_mod_firmware_load(fw);

	वापस 0;
पूर्ण

MODULE_FIRMWARE(IPW2100_FW_NAME("-i"));
#अगर_घोषित CONFIG_IPW2100_MONITOR
MODULE_FIRMWARE(IPW2100_FW_NAME("-p"));
#पूर्ण_अगर
MODULE_FIRMWARE(IPW2100_FW_NAME(""));

अटल व्योम ipw2100_release_firmware(काष्ठा ipw2100_priv *priv,
				     काष्ठा ipw2100_fw *fw)
अणु
	fw->version = 0;
	release_firmware(fw->fw_entry);
	fw->fw_entry = शून्य;
पूर्ण

अटल पूर्णांक ipw2100_get_fwversion(काष्ठा ipw2100_priv *priv, अक्षर *buf,
				 माप_प्रकार max)
अणु
	अक्षर ver[MAX_FW_VERSION_LEN];
	u32 len = MAX_FW_VERSION_LEN;
	u32 पंचांगp;
	पूर्णांक i;
	/* firmware version is an ascii string (max len of 14) */
	अगर (ipw2100_get_ordinal(priv, IPW_ORD_STAT_FW_VER_NUM, ver, &len))
		वापस -EIO;
	पंचांगp = max;
	अगर (len >= max)
		len = max - 1;
	क्रम (i = 0; i < len; i++)
		buf[i] = ver[i];
	buf[i] = '\0';
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक ipw2100_get_ucodeversion(काष्ठा ipw2100_priv *priv, अक्षर *buf,
				    माप_प्रकार max)
अणु
	u32 ver;
	u32 len = माप(ver);
	/* microcode version is a 32 bit पूर्णांकeger */
	अगर (ipw2100_get_ordinal(priv, IPW_ORD_UCODE_VERSION, &ver, &len))
		वापस -EIO;
	वापस snम_लिखो(buf, max, "%08X", ver);
पूर्ण

/*
 * On निकास, the firmware will have been मुक्तd from the fw list
 */
अटल पूर्णांक ipw2100_fw_करोwnload(काष्ठा ipw2100_priv *priv, काष्ठा ipw2100_fw *fw)
अणु
	/* firmware is स्थिरructed of N contiguous entries, each entry is
	 * काष्ठाured as:
	 *
	 * offset    sie         desc
	 * 0         4           address to ग_लिखो to
	 * 4         2           length of data run
	 * 6         length      data
	 */
	अचिन्हित पूर्णांक addr;
	अचिन्हित लघु len;

	स्थिर अचिन्हित अक्षर *firmware_data = fw->fw.data;
	अचिन्हित पूर्णांक firmware_data_left = fw->fw.size;

	जबतक (firmware_data_left > 0) अणु
		addr = *(u32 *) (firmware_data);
		firmware_data += 4;
		firmware_data_left -= 4;

		len = *(u16 *) (firmware_data);
		firmware_data += 2;
		firmware_data_left -= 2;

		अगर (len > 32) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME ": "
			       "Invalid firmware run-length of %d bytes\n",
			       len);
			वापस -EINVAL;
		पूर्ण

		ग_लिखो_nic_memory(priv->net_dev, addr, len, firmware_data);
		firmware_data += len;
		firmware_data_left -= len;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा symbol_alive_response अणु
	u8 cmd_id;
	u8 seq_num;
	u8 ucode_rev;
	u8 eeprom_valid;
	u16 valid_flags;
	u8 IEEE_addr[6];
	u16 flags;
	u16 pcb_rev;
	u16 घड़ी_settle_समय;	// 1us LSB
	u16 घातerup_settle_समय;	// 1us LSB
	u16 hop_settle_समय;	// 1us LSB
	u8 date[3];		// month, day, year
	u8 समय[2];		// hours, minutes
	u8 ucode_valid;
पूर्ण;

अटल पूर्णांक ipw2100_ucode_करोwnload(काष्ठा ipw2100_priv *priv,
				  काष्ठा ipw2100_fw *fw)
अणु
	काष्ठा net_device *dev = priv->net_dev;
	स्थिर अचिन्हित अक्षर *microcode_data = fw->uc.data;
	अचिन्हित पूर्णांक microcode_data_left = fw->uc.size;
	व्योम __iomem *reg = priv->ioaddr;

	काष्ठा symbol_alive_response response;
	पूर्णांक i, j;
	u8 data;

	/* Symbol control */
	ग_लिखो_nic_word(dev, IPW2100_CONTROL_REG, 0x703);
	पढ़ोl(reg);
	ग_लिखो_nic_word(dev, IPW2100_CONTROL_REG, 0x707);
	पढ़ोl(reg);

	/* HW config */
	ग_लिखो_nic_byte(dev, 0x210014, 0x72);	/* fअगरo width =16 */
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210014, 0x72);	/* fअगरo width =16 */
	पढ़ोl(reg);

	/* EN_CS_ACCESS bit to reset control store poपूर्णांकer */
	ग_लिखो_nic_byte(dev, 0x210000, 0x40);
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210000, 0x0);
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210000, 0x40);
	पढ़ोl(reg);

	/* copy microcode from buffer पूर्णांकo Symbol */

	जबतक (microcode_data_left > 0) अणु
		ग_लिखो_nic_byte(dev, 0x210010, *microcode_data++);
		ग_लिखो_nic_byte(dev, 0x210010, *microcode_data++);
		microcode_data_left -= 2;
	पूर्ण

	/* EN_CS_ACCESS bit to reset the control store poपूर्णांकer */
	ग_लिखो_nic_byte(dev, 0x210000, 0x0);
	पढ़ोl(reg);

	/* Enable System (Reg 0)
	 * first enable causes garbage in RX FIFO */
	ग_लिखो_nic_byte(dev, 0x210000, 0x0);
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210000, 0x80);
	पढ़ोl(reg);

	/* Reset External Baseband Reg */
	ग_लिखो_nic_word(dev, IPW2100_CONTROL_REG, 0x703);
	पढ़ोl(reg);
	ग_लिखो_nic_word(dev, IPW2100_CONTROL_REG, 0x707);
	पढ़ोl(reg);

	/* HW Config (Reg 5) */
	ग_लिखो_nic_byte(dev, 0x210014, 0x72);	// fअगरo width =16
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210014, 0x72);	// fअगरo width =16
	पढ़ोl(reg);

	/* Enable System (Reg 0)
	 * second enable should be OK */
	ग_लिखो_nic_byte(dev, 0x210000, 0x00);	// clear enable प्रणाली
	पढ़ोl(reg);
	ग_लिखो_nic_byte(dev, 0x210000, 0x80);	// set enable प्रणाली

	/* check Symbol is enabled - upped this from 5 as it wasn't always
	 * catching the update */
	क्रम (i = 0; i < 10; i++) अणु
		udelay(10);

		/* check Dino is enabled bit */
		पढ़ो_nic_byte(dev, 0x210000, &data);
		अगर (data & 0x1)
			अवरोध;
	पूर्ण

	अगर (i == 10) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": %s: Error initializing Symbol\n",
		       dev->name);
		वापस -EIO;
	पूर्ण

	/* Get Symbol alive response */
	क्रम (i = 0; i < 30; i++) अणु
		/* Read alive response काष्ठाure */
		क्रम (j = 0;
		     j < (माप(काष्ठा symbol_alive_response) >> 1); j++)
			पढ़ो_nic_word(dev, 0x210004, ((u16 *) & response) + j);

		अगर ((response.cmd_id == 1) && (response.ucode_valid == 0x1))
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (i == 30) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME
		       ": %s: No response from Symbol - hw not alive\n",
		       dev->name);
		prपूर्णांकk_buf(IPW_DL_ERROR, (u8 *) & response, माप(response));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
