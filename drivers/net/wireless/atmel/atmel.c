<शैली गुरु>
/*** -*- linux-c -*- **********************************************************

     Driver क्रम Aपंचांगel at76c502 at76c504 and at76c506 wireless cards.

	Copyright 2000-2001 ATMEL Corporation.
	Copyright 2003-2004 Simon Kelley.

    This code was developed from version 2.1.1 of the Aपंचांगel drivers,
    released by Aपंचांगel corp. under the GPL in December 2002. It also
    includes code from the Linux aironet drivers (C) Benjamin Reed,
    and the Linux PCMCIA package, (C) David Hinds and the Linux wireless
    extensions, (C) Jean Tourrilhes.

    The firmware module क्रम पढ़ोing the MAC address of the card comes from
    net.russotto.AपंचांगelMACFW, written by Matthew T. Russotto and copyright
    by him. net.russotto.AपंचांगelMACFW is used under the GPL license version 2.
    This file contains the module in binary क्रमm and, under the terms
    of the GPL, in source क्रमm. The source is located at the end of the file.

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with Aपंचांगel wireless lan drivers; अगर not, see
    <http://www.gnu.org/licenses/>.

    For all queries about this code, please contact the current author,
    Simon Kelley <simon@thekelleys.org.uk> and not Aपंचांगel Corporation.

    Credit is due to HP UK and Cambridge Online Systems Ltd क्रम supplying
    hardware used during development of this driver.

******************************************************************************/

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/crc32.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/cfg80211.h>
#समावेश "atmel.h"

#घोषणा DRIVER_MAJOR 0
#घोषणा DRIVER_MINOR 98

MODULE_AUTHOR("Simon Kelley");
MODULE_DESCRIPTION("Support for Atmel at76c50x 802.11 wireless ethernet cards.");
MODULE_LICENSE("GPL");

/* The name of the firmware file to be loaded
   over-rides any स्वतःmatic selection */
अटल अक्षर *firmware = शून्य;
module_param(firmware, अक्षरp, 0);

/* table of firmware file names */
अटल काष्ठा अणु
	AपंचांगelFWType fw_type;
	स्थिर अक्षर *fw_file;
	स्थिर अक्षर *fw_file_ext;
पूर्ण fw_table[] = अणु
	अणु ATMEL_FW_TYPE_502,		"atmel_at76c502",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_502D,		"atmel_at76c502d",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_502E,		"atmel_at76c502e",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_502_3COM,	"atmel_at76c502_3com",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_504,		"atmel_at76c504",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_504_2958,	"atmel_at76c504_2958",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_504A_2958,	"atmel_at76c504a_2958",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_506,		"atmel_at76c506",	"bin" पूर्ण,
	अणु ATMEL_FW_TYPE_NONE,		शून्य,			शून्य पूर्ण
पूर्ण;
MODULE_FIRMWARE("atmel_at76c502-wpa.bin");
MODULE_FIRMWARE("atmel_at76c502.bin");
MODULE_FIRMWARE("atmel_at76c502d-wpa.bin");
MODULE_FIRMWARE("atmel_at76c502d.bin");
MODULE_FIRMWARE("atmel_at76c502e-wpa.bin");
MODULE_FIRMWARE("atmel_at76c502e.bin");
MODULE_FIRMWARE("atmel_at76c502_3com-wpa.bin");
MODULE_FIRMWARE("atmel_at76c502_3com.bin");
MODULE_FIRMWARE("atmel_at76c504-wpa.bin");
MODULE_FIRMWARE("atmel_at76c504.bin");
MODULE_FIRMWARE("atmel_at76c504_2958-wpa.bin");
MODULE_FIRMWARE("atmel_at76c504_2958.bin");
MODULE_FIRMWARE("atmel_at76c504a_2958-wpa.bin");
MODULE_FIRMWARE("atmel_at76c504a_2958.bin");
MODULE_FIRMWARE("atmel_at76c506-wpa.bin");
MODULE_FIRMWARE("atmel_at76c506.bin");

#घोषणा MAX_SSID_LENGTH 32
#घोषणा MGMT_JIFFIES (256 * HZ / 100)

#घोषणा MAX_BSS_ENTRIES	64

/* रेजिस्टरs */
#घोषणा GCR  0x00    /* (SIR0)  General Configuration Register */
#घोषणा BSR  0x02    /* (SIR1)  Bank Switching Select Register */
#घोषणा AR   0x04
#घोषणा DR   0x08
#घोषणा MR1  0x12    /* Mirror Register 1 */
#घोषणा MR2  0x14    /* Mirror Register 2 */
#घोषणा MR3  0x16    /* Mirror Register 3 */
#घोषणा MR4  0x18    /* Mirror Register 4 */

#घोषणा GPR1                            0x0c
#घोषणा GPR2                            0x0e
#घोषणा GPR3                            0x10
/*
 * Constants क्रम the GCR रेजिस्टर.
 */
#घोषणा GCR_REMAP     0x0400          /* Remap पूर्णांकernal SRAM to 0 */
#घोषणा GCR_SWRES     0x0080          /* BIU reset (ARM and PAI are NOT reset) */
#घोषणा GCR_CORES     0x0060          /* Core Reset (ARM and PAI are reset) */
#घोषणा GCR_ENINT     0x0002          /* Enable Interrupts */
#घोषणा GCR_ACKINT    0x0008          /* Acknowledge Interrupts */

#घोषणा BSS_SRAM      0x0200          /* AMBA module selection --> SRAM */
#घोषणा BSS_IRAM      0x0100          /* AMBA module selection --> IRAM */
/*
 *Constants क्रम the MR रेजिस्टरs.
 */
#घोषणा MAC_INIT_COMPLETE       0x0001        /* MAC init has been completed */
#घोषणा MAC_BOOT_COMPLETE       0x0010        /* MAC boot has been completed */
#घोषणा MAC_INIT_OK             0x0002        /* MAC boot has been completed */

#घोषणा MIB_MAX_DATA_BYTES    212
#घोषणा MIB_HEADER_SIZE       4    /* first four fields */

काष्ठा get_set_mib अणु
	u8 type;
	u8 size;
	u8 index;
	u8 reserved;
	u8 data[MIB_MAX_DATA_BYTES];
पूर्ण;

काष्ठा rx_desc अणु
	u32          Next;
	u16          MsduPos;
	u16          MsduSize;

	u8           State;
	u8           Status;
	u8           Rate;
	u8           Rssi;
	u8           LinkQuality;
	u8           PreambleType;
	u16          Duration;
	u32          RxTime;
पूर्ण;

#घोषणा RX_DESC_FLAG_VALID       0x80
#घोषणा RX_DESC_FLAG_CONSUMED    0x40
#घोषणा RX_DESC_FLAG_IDLE        0x00

#घोषणा RX_STATUS_SUCCESS        0x00

#घोषणा RX_DESC_MSDU_POS_OFFSET      4
#घोषणा RX_DESC_MSDU_SIZE_OFFSET     6
#घोषणा RX_DESC_FLAGS_OFFSET         8
#घोषणा RX_DESC_STATUS_OFFSET        9
#घोषणा RX_DESC_RSSI_OFFSET          11
#घोषणा RX_DESC_LINK_QUALITY_OFFSET  12
#घोषणा RX_DESC_PREAMBLE_TYPE_OFFSET 13
#घोषणा RX_DESC_DURATION_OFFSET      14
#घोषणा RX_DESC_RX_TIME_OFFSET       16

काष्ठा tx_desc अणु
	u32       NextDescriptor;
	u16       TxStartOfFrame;
	u16       TxLength;

	u8        TxState;
	u8        TxStatus;
	u8        RetryCount;

	u8        TxRate;

	u8        KeyIndex;
	u8        ChiperType;
	u8        ChipreLength;
	u8        Reserved1;

	u8        Reserved;
	u8        PacketType;
	u16       HostTxLength;
पूर्ण;

#घोषणा TX_DESC_NEXT_OFFSET          0
#घोषणा TX_DESC_POS_OFFSET           4
#घोषणा TX_DESC_SIZE_OFFSET          6
#घोषणा TX_DESC_FLAGS_OFFSET         8
#घोषणा TX_DESC_STATUS_OFFSET        9
#घोषणा TX_DESC_RETRY_OFFSET         10
#घोषणा TX_DESC_RATE_OFFSET          11
#घोषणा TX_DESC_KEY_INDEX_OFFSET     12
#घोषणा TX_DESC_CIPHER_TYPE_OFFSET   13
#घोषणा TX_DESC_CIPHER_LENGTH_OFFSET 14
#घोषणा TX_DESC_PACKET_TYPE_OFFSET   17
#घोषणा TX_DESC_HOST_LENGTH_OFFSET   18

/*
 * Host-MAC पूर्णांकerface
 */

#घोषणा TX_STATUS_SUCCESS       0x00

#घोषणा TX_FIRM_OWN             0x80
#घोषणा TX_DONE                 0x40

#घोषणा TX_ERROR                0x01

#घोषणा TX_PACKET_TYPE_DATA     0x01
#घोषणा TX_PACKET_TYPE_MGMT     0x02

#घोषणा ISR_EMPTY               0x00        /* no bits set in ISR */
#घोषणा ISR_TxCOMPLETE          0x01        /* packet transmitted */
#घोषणा ISR_RxCOMPLETE          0x02        /* packet received */
#घोषणा ISR_RxFRAMELOST         0x04        /* Rx Frame lost */
#घोषणा ISR_FATAL_ERROR         0x08        /* Fatal error */
#घोषणा ISR_COMMAND_COMPLETE    0x10        /* command completed */
#घोषणा ISR_OUT_OF_RANGE        0x20        /* command completed */
#घोषणा ISR_IBSS_MERGE          0x40        /* (4.1.2.30): IBSS merge */
#घोषणा ISR_GENERIC_IRQ         0x80

#घोषणा Local_Mib_Type          0x01
#घोषणा Mac_Address_Mib_Type    0x02
#घोषणा Mac_Mib_Type            0x03
#घोषणा Statistics_Mib_Type     0x04
#घोषणा Mac_Mgmt_Mib_Type       0x05
#घोषणा Mac_Wep_Mib_Type        0x06
#घोषणा Phy_Mib_Type            0x07
#घोषणा Multi_Doमुख्य_MIB        0x08

#घोषणा MAC_MGMT_MIB_CUR_BSSID_POS            14
#घोषणा MAC_MIB_FRAG_THRESHOLD_POS            8
#घोषणा MAC_MIB_RTS_THRESHOLD_POS             10
#घोषणा MAC_MIB_SHORT_RETRY_POS               16
#घोषणा MAC_MIB_LONG_RETRY_POS                17
#घोषणा MAC_MIB_SHORT_RETRY_LIMIT_POS         16
#घोषणा MAC_MGMT_MIB_BEACON_PER_POS           0
#घोषणा MAC_MGMT_MIB_STATION_ID_POS           6
#घोषणा MAC_MGMT_MIB_CUR_PRIVACY_POS          11
#घोषणा MAC_MGMT_MIB_CUR_BSSID_POS            14
#घोषणा MAC_MGMT_MIB_PS_MODE_POS              53
#घोषणा MAC_MGMT_MIB_LISTEN_INTERVAL_POS      54
#घोषणा MAC_MGMT_MIB_MULTI_DOMAIN_IMPLEMENTED 56
#घोषणा MAC_MGMT_MIB_MULTI_DOMAIN_ENABLED     57
#घोषणा PHY_MIB_CHANNEL_POS                   14
#घोषणा PHY_MIB_RATE_SET_POS                  20
#घोषणा PHY_MIB_REG_DOMAIN_POS                26
#घोषणा LOCAL_MIB_AUTO_TX_RATE_POS            3
#घोषणा LOCAL_MIB_SSID_SIZE                   5
#घोषणा LOCAL_MIB_TX_PROMISCUOUS_POS          6
#घोषणा LOCAL_MIB_TX_MGMT_RATE_POS            7
#घोषणा LOCAL_MIB_TX_CONTROL_RATE_POS         8
#घोषणा LOCAL_MIB_PREAMBLE_TYPE               9
#घोषणा MAC_ADDR_MIB_MAC_ADDR_POS             0

#घोषणा         CMD_Set_MIB_Vars              0x01
#घोषणा         CMD_Get_MIB_Vars              0x02
#घोषणा         CMD_Scan                      0x03
#घोषणा         CMD_Join                      0x04
#घोषणा         CMD_Start                     0x05
#घोषणा         CMD_EnableRadio               0x06
#घोषणा         CMD_DisableRadio              0x07
#घोषणा         CMD_SiteSurvey                0x0B

#घोषणा         CMD_STATUS_IDLE                   0x00
#घोषणा         CMD_STATUS_COMPLETE               0x01
#घोषणा         CMD_STATUS_UNKNOWN                0x02
#घोषणा         CMD_STATUS_INVALID_PARAMETER      0x03
#घोषणा         CMD_STATUS_FUNCTION_NOT_SUPPORTED 0x04
#घोषणा         CMD_STATUS_TIME_OUT               0x07
#घोषणा         CMD_STATUS_IN_PROGRESS            0x08
#घोषणा         CMD_STATUS_REJECTED_RADIO_OFF     0x09
#घोषणा         CMD_STATUS_HOST_ERROR             0xFF
#घोषणा         CMD_STATUS_BUSY                   0xFE

#घोषणा CMD_BLOCK_COMMAND_OFFSET        0
#घोषणा CMD_BLOCK_STATUS_OFFSET         1
#घोषणा CMD_BLOCK_PARAMETERS_OFFSET     4

#घोषणा SCAN_OPTIONS_SITE_SURVEY        0x80

#घोषणा MGMT_FRAME_BODY_OFFSET		24
#घोषणा MAX_AUTHENTICATION_RETRIES	3
#घोषणा MAX_ASSOCIATION_RETRIES		3

#घोषणा AUTHENTICATION_RESPONSE_TIME_OUT  1000

#घोषणा MAX_WIRELESS_BODY  2316 /* mtu is 2312, CRC is 4 */
#घोषणा LOOP_RETRY_LIMIT   500000

#घोषणा ACTIVE_MODE	1
#घोषणा PS_MODE		2

#घोषणा MAX_ENCRYPTION_KEYS 4
#घोषणा MAX_ENCRYPTION_KEY_SIZE 40

/*
 * 802.11 related definitions
 */

/*
 * Regulatory Doमुख्यs
 */

#घोषणा REG_DOMAIN_FCC		0x10	/* Channels	1-11	USA				*/
#घोषणा REG_DOMAIN_DOC		0x20	/* Channel	1-11	Canada				*/
#घोषणा REG_DOMAIN_ETSI		0x30	/* Channel	1-13	Europe (ex Spain/France)	*/
#घोषणा REG_DOMAIN_SPAIN	0x31	/* Channel	10-11	Spain				*/
#घोषणा REG_DOMAIN_FRANCE	0x32	/* Channel	10-13	France				*/
#घोषणा REG_DOMAIN_MKK		0x40	/* Channel	14	Japan				*/
#घोषणा REG_DOMAIN_MKK1		0x41	/* Channel	1-14	Japan(MKK1)			*/
#घोषणा REG_DOMAIN_ISRAEL	0x50	/* Channel	3-9	ISRAEL				*/

#घोषणा BSS_TYPE_AD_HOC		1
#घोषणा BSS_TYPE_INFRASTRUCTURE 2

#घोषणा SCAN_TYPE_ACTIVE	0
#घोषणा SCAN_TYPE_PASSIVE	1

#घोषणा LONG_PREAMBLE		0
#घोषणा SHORT_PREAMBLE		1
#घोषणा AUTO_PREAMBLE		2

#घोषणा DATA_FRAME_WS_HEADER_SIZE   30

/* promiscuous mode control */
#घोषणा PROM_MODE_OFF			0x0
#घोषणा PROM_MODE_UNKNOWN		0x1
#घोषणा PROM_MODE_CRC_FAILED		0x2
#घोषणा PROM_MODE_DUPLICATED		0x4
#घोषणा PROM_MODE_MGMT			0x8
#घोषणा PROM_MODE_CTRL			0x10
#घोषणा PROM_MODE_BAD_PROTOCOL		0x20

#घोषणा IFACE_INT_STATUS_OFFSET		0
#घोषणा IFACE_INT_MASK_OFFSET		1
#घोषणा IFACE_LOCKOUT_HOST_OFFSET	2
#घोषणा IFACE_LOCKOUT_MAC_OFFSET	3
#घोषणा IFACE_FUNC_CTRL_OFFSET		28
#घोषणा IFACE_MAC_STAT_OFFSET		30
#घोषणा IFACE_GENERIC_INT_TYPE_OFFSET	32

#घोषणा CIPHER_SUITE_NONE     0
#घोषणा CIPHER_SUITE_WEP_64   1
#घोषणा CIPHER_SUITE_TKIP     2
#घोषणा CIPHER_SUITE_AES      3
#घोषणा CIPHER_SUITE_CCX      4
#घोषणा CIPHER_SUITE_WEP_128  5

/*
 * IFACE MACROS & definitions
 */

/*
 * FuncCtrl field:
 */
#घोषणा FUNC_CTRL_TxENABLE		0x10
#घोषणा FUNC_CTRL_RxENABLE		0x20
#घोषणा FUNC_CTRL_INIT_COMPLETE		0x01

/* A stub firmware image which पढ़ोs the MAC address from NVRAM on the card.
   For copyright inक्रमmation and source see the end of this file. */
अटल u8 mac_पढ़ोer[] = अणु
	0x06, 0x00, 0x00, 0xea, 0x04, 0x00, 0x00, 0xea, 0x03, 0x00, 0x00, 0xea, 0x02, 0x00, 0x00, 0xea,
	0x01, 0x00, 0x00, 0xea, 0x00, 0x00, 0x00, 0xea, 0xff, 0xff, 0xff, 0xea, 0xfe, 0xff, 0xff, 0xea,
	0xd3, 0x00, 0xa0, 0xe3, 0x00, 0xf0, 0x21, 0xe1, 0x0e, 0x04, 0xa0, 0xe3, 0x00, 0x10, 0xa0, 0xe3,
	0x81, 0x11, 0xa0, 0xe1, 0x00, 0x10, 0x81, 0xe3, 0x00, 0x10, 0x80, 0xe5, 0x1c, 0x10, 0x90, 0xe5,
	0x10, 0x10, 0xc1, 0xe3, 0x1c, 0x10, 0x80, 0xe5, 0x01, 0x10, 0xa0, 0xe3, 0x08, 0x10, 0x80, 0xe5,
	0x02, 0x03, 0xa0, 0xe3, 0x00, 0x10, 0xa0, 0xe3, 0xb0, 0x10, 0xc0, 0xe1, 0xb4, 0x10, 0xc0, 0xe1,
	0xb8, 0x10, 0xc0, 0xe1, 0xbc, 0x10, 0xc0, 0xe1, 0x56, 0xdc, 0xa0, 0xe3, 0x21, 0x00, 0x00, 0xeb,
	0x0a, 0x00, 0xa0, 0xe3, 0x1a, 0x00, 0x00, 0xeb, 0x10, 0x00, 0x00, 0xeb, 0x07, 0x00, 0x00, 0xeb,
	0x02, 0x03, 0xa0, 0xe3, 0x02, 0x14, 0xa0, 0xe3, 0xb4, 0x10, 0xc0, 0xe1, 0x4c, 0x10, 0x9f, 0xe5,
	0xbc, 0x10, 0xc0, 0xe1, 0x10, 0x10, 0xa0, 0xe3, 0xb8, 0x10, 0xc0, 0xe1, 0xfe, 0xff, 0xff, 0xea,
	0x00, 0x40, 0x2d, 0xe9, 0x00, 0x20, 0xa0, 0xe3, 0x02, 0x3c, 0xa0, 0xe3, 0x00, 0x10, 0xa0, 0xe3,
	0x28, 0x00, 0x9f, 0xe5, 0x37, 0x00, 0x00, 0xeb, 0x00, 0x40, 0xbd, 0xe8, 0x1e, 0xff, 0x2f, 0xe1,
	0x00, 0x40, 0x2d, 0xe9, 0x12, 0x2e, 0xa0, 0xe3, 0x06, 0x30, 0xa0, 0xe3, 0x00, 0x10, 0xa0, 0xe3,
	0x02, 0x04, 0xa0, 0xe3, 0x2f, 0x00, 0x00, 0xeb, 0x00, 0x40, 0xbd, 0xe8, 0x1e, 0xff, 0x2f, 0xe1,
	0x00, 0x02, 0x00, 0x02, 0x80, 0x01, 0x90, 0xe0, 0x01, 0x00, 0x00, 0x0a, 0x01, 0x00, 0x50, 0xe2,
	0xfc, 0xff, 0xff, 0xea, 0x1e, 0xff, 0x2f, 0xe1, 0x80, 0x10, 0xa0, 0xe3, 0xf3, 0x06, 0xa0, 0xe3,
	0x00, 0x10, 0x80, 0xe5, 0x00, 0x10, 0xa0, 0xe3, 0x00, 0x10, 0x80, 0xe5, 0x01, 0x10, 0xa0, 0xe3,
	0x04, 0x10, 0x80, 0xe5, 0x00, 0x10, 0x80, 0xe5, 0x0e, 0x34, 0xa0, 0xe3, 0x1c, 0x10, 0x93, 0xe5,
	0x02, 0x1a, 0x81, 0xe3, 0x1c, 0x10, 0x83, 0xe5, 0x58, 0x11, 0x9f, 0xe5, 0x30, 0x10, 0x80, 0xe5,
	0x54, 0x11, 0x9f, 0xe5, 0x34, 0x10, 0x80, 0xe5, 0x38, 0x10, 0x80, 0xe5, 0x3c, 0x10, 0x80, 0xe5,
	0x10, 0x10, 0x90, 0xe5, 0x08, 0x00, 0x90, 0xe5, 0x1e, 0xff, 0x2f, 0xe1, 0xf3, 0x16, 0xa0, 0xe3,
	0x08, 0x00, 0x91, 0xe5, 0x05, 0x00, 0xa0, 0xe3, 0x0c, 0x00, 0x81, 0xe5, 0x10, 0x00, 0x91, 0xe5,
	0x02, 0x00, 0x10, 0xe3, 0xfc, 0xff, 0xff, 0x0a, 0xff, 0x00, 0xa0, 0xe3, 0x0c, 0x00, 0x81, 0xe5,
	0x10, 0x00, 0x91, 0xe5, 0x02, 0x00, 0x10, 0xe3, 0xfc, 0xff, 0xff, 0x0a, 0x08, 0x00, 0x91, 0xe5,
	0x10, 0x00, 0x91, 0xe5, 0x01, 0x00, 0x10, 0xe3, 0xfc, 0xff, 0xff, 0x0a, 0x08, 0x00, 0x91, 0xe5,
	0xff, 0x00, 0x00, 0xe2, 0x1e, 0xff, 0x2f, 0xe1, 0x30, 0x40, 0x2d, 0xe9, 0x00, 0x50, 0xa0, 0xe1,
	0x03, 0x40, 0xa0, 0xe1, 0xa2, 0x02, 0xa0, 0xe1, 0x08, 0x00, 0x00, 0xe2, 0x03, 0x00, 0x80, 0xe2,
	0xd8, 0x10, 0x9f, 0xe5, 0x00, 0x00, 0xc1, 0xe5, 0x01, 0x20, 0xc1, 0xe5, 0xe2, 0xff, 0xff, 0xeb,
	0x01, 0x00, 0x10, 0xe3, 0xfc, 0xff, 0xff, 0x1a, 0x14, 0x00, 0xa0, 0xe3, 0xc4, 0xff, 0xff, 0xeb,
	0x04, 0x20, 0xa0, 0xe1, 0x05, 0x10, 0xa0, 0xe1, 0x02, 0x00, 0xa0, 0xe3, 0x01, 0x00, 0x00, 0xeb,
	0x30, 0x40, 0xbd, 0xe8, 0x1e, 0xff, 0x2f, 0xe1, 0x70, 0x40, 0x2d, 0xe9, 0xf3, 0x46, 0xa0, 0xe3,
	0x00, 0x30, 0xa0, 0xe3, 0x00, 0x00, 0x50, 0xe3, 0x08, 0x00, 0x00, 0x9a, 0x8c, 0x50, 0x9f, 0xe5,
	0x03, 0x60, 0xd5, 0xe7, 0x0c, 0x60, 0x84, 0xe5, 0x10, 0x60, 0x94, 0xe5, 0x02, 0x00, 0x16, 0xe3,
	0xfc, 0xff, 0xff, 0x0a, 0x01, 0x30, 0x83, 0xe2, 0x00, 0x00, 0x53, 0xe1, 0xf7, 0xff, 0xff, 0x3a,
	0xff, 0x30, 0xa0, 0xe3, 0x0c, 0x30, 0x84, 0xe5, 0x08, 0x00, 0x94, 0xe5, 0x10, 0x00, 0x94, 0xe5,
	0x01, 0x00, 0x10, 0xe3, 0xfc, 0xff, 0xff, 0x0a, 0x08, 0x00, 0x94, 0xe5, 0x00, 0x00, 0xa0, 0xe3,
	0x00, 0x00, 0x52, 0xe3, 0x0b, 0x00, 0x00, 0x9a, 0x10, 0x50, 0x94, 0xe5, 0x02, 0x00, 0x15, 0xe3,
	0xfc, 0xff, 0xff, 0x0a, 0x0c, 0x30, 0x84, 0xe5, 0x10, 0x50, 0x94, 0xe5, 0x01, 0x00, 0x15, 0xe3,
	0xfc, 0xff, 0xff, 0x0a, 0x08, 0x50, 0x94, 0xe5, 0x01, 0x50, 0xc1, 0xe4, 0x01, 0x00, 0x80, 0xe2,
	0x02, 0x00, 0x50, 0xe1, 0xf3, 0xff, 0xff, 0x3a, 0xc8, 0x00, 0xa0, 0xe3, 0x98, 0xff, 0xff, 0xeb,
	0x70, 0x40, 0xbd, 0xe8, 0x1e, 0xff, 0x2f, 0xe1, 0x01, 0x0c, 0x00, 0x02, 0x01, 0x02, 0x00, 0x02,
	0x00, 0x01, 0x00, 0x02
पूर्ण;

काष्ठा aपंचांगel_निजी अणु
	व्योम *card; /* Bus dependent काष्ठाure varies क्रम PCcard */
	पूर्णांक (*present_callback)(व्योम *); /* And callback which uses it */
	अक्षर firmware_id[32];
	AपंचांगelFWType firmware_type;
	u8 *firmware;
	पूर्णांक firmware_length;
	काष्ठा समयr_list management_समयr;
	काष्ठा net_device *dev;
	काष्ठा device *sys_dev;
	काष्ठा iw_statistics wstats;
	spinlock_t irqlock, समयrlock;	/* spinlocks */
	क्रमागत अणु BUS_TYPE_PCCARD, BUS_TYPE_PCI पूर्ण bus_type;
	क्रमागत अणु
		CARD_TYPE_PARALLEL_FLASH,
		CARD_TYPE_SPI_FLASH,
		CARD_TYPE_EEPROM
	पूर्ण card_type;
	पूर्णांक करो_rx_crc; /* If we need to CRC incoming packets */
	पूर्णांक probe_crc; /* set अगर we करोn't yet know */
	पूर्णांक crc_ok_cnt, crc_ko_cnt; /* counters क्रम probing */
	u16 rx_desc_head;
	u16 tx_desc_मुक्त, tx_desc_head, tx_desc_tail, tx_desc_previous;
	u16 tx_मुक्त_mem, tx_buff_head, tx_buff_tail;

	u16 frag_seq, frag_len, frag_no;
	u8 frag_source[6];

	u8 wep_is_on, शेष_key, exclude_unencrypted, encryption_level;
	u8 group_cipher_suite, pairwise_cipher_suite;
	u8 wep_keys[MAX_ENCRYPTION_KEYS][MAX_ENCRYPTION_KEY_SIZE];
	पूर्णांक wep_key_len[MAX_ENCRYPTION_KEYS];
	पूर्णांक use_wpa, radio_on_broken; /* firmware dependent stuff. */

	u16 host_info_base;
	काष्ठा host_info_काष्ठा अणु
		/* NB this is matched to the hardware, करोn't change. */
		u8 अस्थिर पूर्णांक_status;
		u8 अस्थिर पूर्णांक_mask;
		u8 अस्थिर lockout_host;
		u8 अस्थिर lockout_mac;

		u16 tx_buff_pos;
		u16 tx_buff_size;
		u16 tx_desc_pos;
		u16 tx_desc_count;

		u16 rx_buff_pos;
		u16 rx_buff_size;
		u16 rx_desc_pos;
		u16 rx_desc_count;

		u16 build_version;
		u16 command_pos;

		u16 major_version;
		u16 minor_version;

		u16 func_ctrl;
		u16 mac_status;
		u16 generic_IRQ_type;
		u8  reserved[2];
	पूर्ण host_info;

	क्रमागत अणु
		STATION_STATE_SCANNING,
		STATION_STATE_JOINNING,
		STATION_STATE_AUTHENTICATING,
		STATION_STATE_ASSOCIATING,
		STATION_STATE_READY,
		STATION_STATE_REASSOCIATING,
		STATION_STATE_DOWN,
		STATION_STATE_MGMT_ERROR
	पूर्ण station_state;

	पूर्णांक operating_mode, घातer_mode;
	अचिन्हित दीर्घ last_qual;
	पूर्णांक beacons_this_sec;
	पूर्णांक channel;
	पूर्णांक reg_करोमुख्य, config_reg_करोमुख्य;
	पूर्णांक tx_rate;
	पूर्णांक स्वतः_tx_rate;
	पूर्णांक rts_threshold;
	पूर्णांक frag_threshold;
	पूर्णांक दीर्घ_retry, लघु_retry;
	पूर्णांक preamble;
	पूर्णांक शेष_beacon_period, beacon_period, listen_पूर्णांकerval;
	पूर्णांक CurrentAuthentTransactionSeqNum, ExpectedAuthentTransactionSeqNum;
	पूर्णांक AuthenticationRequestRetryCnt, AssociationRequestRetryCnt, ReAssociationRequestRetryCnt;
	क्रमागत अणु
		SITE_SURVEY_IDLE,
		SITE_SURVEY_IN_PROGRESS,
		SITE_SURVEY_COMPLETED
	पूर्ण site_survey_state;
	अचिन्हित दीर्घ last_survey;

	पूर्णांक station_was_associated, station_is_associated;
	पूर्णांक fast_scan;

	काष्ठा bss_info अणु
		पूर्णांक channel;
		पूर्णांक SSIDsize;
		पूर्णांक RSSI;
		पूर्णांक UsingWEP;
		पूर्णांक preamble;
		पूर्णांक beacon_period;
		पूर्णांक BSStype;
		u8 BSSID[6];
		u8 SSID[MAX_SSID_LENGTH];
	पूर्ण BSSinfo[MAX_BSS_ENTRIES];
	पूर्णांक BSS_list_entries, current_BSS;
	पूर्णांक connect_to_any_BSS;
	पूर्णांक SSID_size, new_SSID_size;
	u8 CurrentBSSID[6], BSSID[6];
	u8 SSID[MAX_SSID_LENGTH], new_SSID[MAX_SSID_LENGTH];
	u64 last_beacon_बारtamp;
	u8 rx_buf[MAX_WIRELESS_BODY];
पूर्ण;

अटल u8 aपंचांगel_basic_rates[4] = अणु0x82, 0x84, 0x0b, 0x16पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक reg_करोमुख्य;
	पूर्णांक min, max;
	अक्षर *name;
पूर्ण channel_table[] = अणु अणु REG_DOMAIN_FCC, 1, 11, "USA" पूर्ण,
		      अणु REG_DOMAIN_DOC, 1, 11, "Canada" पूर्ण,
		      अणु REG_DOMAIN_ETSI, 1, 13, "Europe" पूर्ण,
		      अणु REG_DOMAIN_SPAIN, 10, 11, "Spain" पूर्ण,
		      अणु REG_DOMAIN_FRANCE, 10, 13, "France" पूर्ण,
		      अणु REG_DOMAIN_MKK, 14, 14, "MKK" पूर्ण,
		      अणु REG_DOMAIN_MKK1, 1, 14, "MKK1" पूर्ण,
		      अणु REG_DOMAIN_ISRAEL, 3, 9, "Israel"पूर्ण पूर्ण;

अटल व्योम build_wpa_mib(काष्ठा aपंचांगel_निजी *priv);
अटल पूर्णांक aपंचांगel_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम aपंचांगel_copy_to_card(काष्ठा net_device *dev, u16 dest,
			       स्थिर अचिन्हित अक्षर *src, u16 len);
अटल व्योम aपंचांगel_copy_to_host(काष्ठा net_device *dev, अचिन्हित अक्षर *dest,
			       u16 src, u16 len);
अटल व्योम aपंचांगel_set_gcr(काष्ठा net_device *dev, u16 mask);
अटल व्योम aपंचांगel_clear_gcr(काष्ठा net_device *dev, u16 mask);
अटल पूर्णांक aपंचांगel_lock_mac(काष्ठा aपंचांगel_निजी *priv);
अटल व्योम aपंचांगel_wmem32(काष्ठा aपंचांगel_निजी *priv, u16 pos, u32 data);
अटल व्योम aपंचांगel_command_irq(काष्ठा aपंचांगel_निजी *priv);
अटल पूर्णांक aपंचांगel_validate_channel(काष्ठा aपंचांगel_निजी *priv, पूर्णांक channel);
अटल व्योम aपंचांगel_management_frame(काष्ठा aपंचांगel_निजी *priv,
				   काष्ठा ieee80211_hdr *header,
				   u16 frame_len, u8 rssi);
अटल व्योम aपंचांगel_management_समयr(काष्ठा समयr_list *t);
अटल व्योम aपंचांगel_send_command(काष्ठा aपंचांगel_निजी *priv, पूर्णांक command,
			       व्योम *cmd, पूर्णांक cmd_size);
अटल पूर्णांक aपंचांगel_send_command_रुको(काष्ठा aपंचांगel_निजी *priv, पूर्णांक command,
				   व्योम *cmd, पूर्णांक cmd_size);
अटल व्योम aपंचांगel_transmit_management_frame(काष्ठा aपंचांगel_निजी *priv,
					    काष्ठा ieee80211_hdr *header,
					    u8 *body, पूर्णांक body_len);

अटल u8 aपंचांगel_get_mib8(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index);
अटल व्योम aपंचांगel_set_mib8(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			   u8 data);
अटल व्योम aपंचांगel_set_mib16(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			    u16 data);
अटल व्योम aपंचांगel_set_mib(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			  u8 *data, पूर्णांक data_len);
अटल व्योम aपंचांगel_get_mib(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			  u8 *data, पूर्णांक data_len);
अटल व्योम aपंचांगel_scan(काष्ठा aपंचांगel_निजी *priv, पूर्णांक specअगरic_ssid);
अटल व्योम aपंचांगel_join_bss(काष्ठा aपंचांगel_निजी *priv, पूर्णांक bss_index);
अटल व्योम aपंचांगel_smooth_qual(काष्ठा aपंचांगel_निजी *priv);
अटल व्योम aपंचांगel_ग_लिखोAR(काष्ठा net_device *dev, u16 data);
अटल पूर्णांक probe_aपंचांगel_card(काष्ठा net_device *dev);
अटल पूर्णांक reset_aपंचांगel_card(काष्ठा net_device *dev);
अटल व्योम aपंचांगel_enter_state(काष्ठा aपंचांगel_निजी *priv, पूर्णांक new_state);
पूर्णांक aपंचांगel_खोलो (काष्ठा net_device *dev);

अटल अंतरभूत u16 aपंचांगel_hi(काष्ठा aपंचांगel_निजी *priv, u16 offset)
अणु
	वापस priv->host_info_base + offset;
पूर्ण

अटल अंतरभूत u16 aपंचांगel_co(काष्ठा aपंचांगel_निजी *priv, u16 offset)
अणु
	वापस priv->host_info.command_pos + offset;
पूर्ण

अटल अंतरभूत u16 aपंचांगel_rx(काष्ठा aपंचांगel_निजी *priv, u16 offset, u16 desc)
अणु
	वापस priv->host_info.rx_desc_pos + (माप(काष्ठा rx_desc) * desc) + offset;
पूर्ण

अटल अंतरभूत u16 aपंचांगel_tx(काष्ठा aपंचांगel_निजी *priv, u16 offset, u16 desc)
अणु
	वापस priv->host_info.tx_desc_pos + (माप(काष्ठा tx_desc) * desc) + offset;
पूर्ण

अटल अंतरभूत u8 aपंचांगel_पढ़ो8(काष्ठा net_device *dev, u16 offset)
अणु
	वापस inb(dev->base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_ग_लिखो8(काष्ठा net_device *dev, u16 offset, u8 data)
अणु
	outb(data, dev->base_addr + offset);
पूर्ण

अटल अंतरभूत u16 aपंचांगel_पढ़ो16(काष्ठा net_device *dev, u16 offset)
अणु
	वापस inw(dev->base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_ग_लिखो16(काष्ठा net_device *dev, u16 offset, u16 data)
अणु
	outw(data, dev->base_addr + offset);
पूर्ण

अटल अंतरभूत u8 aपंचांगel_rmem8(काष्ठा aपंचांगel_निजी *priv, u16 pos)
अणु
	aपंचांगel_ग_लिखोAR(priv->dev, pos);
	वापस aपंचांगel_पढ़ो8(priv->dev, DR);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_wmem8(काष्ठा aपंचांगel_निजी *priv, u16 pos, u16 data)
अणु
	aपंचांगel_ग_लिखोAR(priv->dev, pos);
	aपंचांगel_ग_लिखो8(priv->dev, DR, data);
पूर्ण

अटल अंतरभूत u16 aपंचांगel_rmem16(काष्ठा aपंचांगel_निजी *priv, u16 pos)
अणु
	aपंचांगel_ग_लिखोAR(priv->dev, pos);
	वापस aपंचांगel_पढ़ो16(priv->dev, DR);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_wmem16(काष्ठा aपंचांगel_निजी *priv, u16 pos, u16 data)
अणु
	aपंचांगel_ग_लिखोAR(priv->dev, pos);
	aपंचांगel_ग_लिखो16(priv->dev, DR, data);
पूर्ण

अटल स्थिर काष्ठा iw_handler_def aपंचांगel_handler_def;

अटल व्योम tx_करोne_irq(काष्ठा aपंचांगel_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0;
	     aपंचांगel_rmem8(priv, aपंचांगel_tx(priv, TX_DESC_FLAGS_OFFSET, priv->tx_desc_head)) == TX_DONE &&
		     i < priv->host_info.tx_desc_count;
	     i++) अणु
		u8 status = aपंचांगel_rmem8(priv, aपंचांगel_tx(priv, TX_DESC_STATUS_OFFSET, priv->tx_desc_head));
		u16 msdu_size = aपंचांगel_rmem16(priv, aपंचांगel_tx(priv, TX_DESC_SIZE_OFFSET, priv->tx_desc_head));
		u8 type = aपंचांगel_rmem8(priv, aपंचांगel_tx(priv, TX_DESC_PACKET_TYPE_OFFSET, priv->tx_desc_head));

		aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_FLAGS_OFFSET, priv->tx_desc_head), 0);

		priv->tx_मुक्त_mem += msdu_size;
		priv->tx_desc_मुक्त++;

		अगर (priv->tx_buff_head + msdu_size > (priv->host_info.tx_buff_pos + priv->host_info.tx_buff_size))
			priv->tx_buff_head = 0;
		अन्यथा
			priv->tx_buff_head += msdu_size;

		अगर (priv->tx_desc_head < (priv->host_info.tx_desc_count - 1))
			priv->tx_desc_head++ ;
		अन्यथा
			priv->tx_desc_head = 0;

		अगर (type == TX_PACKET_TYPE_DATA) अणु
			अगर (status == TX_STATUS_SUCCESS)
				priv->dev->stats.tx_packets++;
			अन्यथा
				priv->dev->stats.tx_errors++;
			netअगर_wake_queue(priv->dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल u16 find_tx_buff(काष्ठा aपंचांगel_निजी *priv, u16 len)
अणु
	u16 bottom_मुक्त = priv->host_info.tx_buff_size - priv->tx_buff_tail;

	अगर (priv->tx_desc_मुक्त == 3 || priv->tx_मुक्त_mem < len)
		वापस 0;

	अगर (bottom_मुक्त >= len)
		वापस priv->host_info.tx_buff_pos + priv->tx_buff_tail;

	अगर (priv->tx_मुक्त_mem - bottom_मुक्त >= len) अणु
		priv->tx_buff_tail = 0;
		वापस priv->host_info.tx_buff_pos;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tx_update_descriptor(काष्ठा aपंचांगel_निजी *priv, पूर्णांक is_bcast,
				 u16 len, u16 buff, u8 type)
अणु
	aपंचांगel_wmem16(priv, aपंचांगel_tx(priv, TX_DESC_POS_OFFSET, priv->tx_desc_tail), buff);
	aपंचांगel_wmem16(priv, aपंचांगel_tx(priv, TX_DESC_SIZE_OFFSET, priv->tx_desc_tail), len);
	अगर (!priv->use_wpa)
		aपंचांगel_wmem16(priv, aपंचांगel_tx(priv, TX_DESC_HOST_LENGTH_OFFSET, priv->tx_desc_tail), len);
	aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_PACKET_TYPE_OFFSET, priv->tx_desc_tail), type);
	aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_RATE_OFFSET, priv->tx_desc_tail), priv->tx_rate);
	aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_RETRY_OFFSET, priv->tx_desc_tail), 0);
	अगर (priv->use_wpa) अणु
		पूर्णांक cipher_type, cipher_length;
		अगर (is_bcast) अणु
			cipher_type = priv->group_cipher_suite;
			अगर (cipher_type == CIPHER_SUITE_WEP_64 ||
			    cipher_type == CIPHER_SUITE_WEP_128)
				cipher_length = 8;
			अन्यथा अगर (cipher_type == CIPHER_SUITE_TKIP)
				cipher_length = 12;
			अन्यथा अगर (priv->pairwise_cipher_suite == CIPHER_SUITE_WEP_64 ||
				 priv->pairwise_cipher_suite == CIPHER_SUITE_WEP_128) अणु
				cipher_type = priv->pairwise_cipher_suite;
				cipher_length = 8;
			पूर्ण अन्यथा अणु
				cipher_type = CIPHER_SUITE_NONE;
				cipher_length = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			cipher_type = priv->pairwise_cipher_suite;
			अगर (cipher_type == CIPHER_SUITE_WEP_64 ||
			    cipher_type == CIPHER_SUITE_WEP_128)
				cipher_length = 8;
			अन्यथा अगर (cipher_type == CIPHER_SUITE_TKIP)
				cipher_length = 12;
			अन्यथा अगर (priv->group_cipher_suite == CIPHER_SUITE_WEP_64 ||
				 priv->group_cipher_suite == CIPHER_SUITE_WEP_128) अणु
				cipher_type = priv->group_cipher_suite;
				cipher_length = 8;
			पूर्ण अन्यथा अणु
				cipher_type = CIPHER_SUITE_NONE;
				cipher_length = 0;
			पूर्ण
		पूर्ण

		aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_CIPHER_TYPE_OFFSET, priv->tx_desc_tail),
			    cipher_type);
		aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_CIPHER_LENGTH_OFFSET, priv->tx_desc_tail),
			    cipher_length);
	पूर्ण
	aपंचांगel_wmem32(priv, aपंचांगel_tx(priv, TX_DESC_NEXT_OFFSET, priv->tx_desc_tail), 0x80000000L);
	aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_FLAGS_OFFSET, priv->tx_desc_tail), TX_FIRM_OWN);
	अगर (priv->tx_desc_previous != priv->tx_desc_tail)
		aपंचांगel_wmem32(priv, aपंचांगel_tx(priv, TX_DESC_NEXT_OFFSET, priv->tx_desc_previous), 0);
	priv->tx_desc_previous = priv->tx_desc_tail;
	अगर (priv->tx_desc_tail < (priv->host_info.tx_desc_count - 1))
		priv->tx_desc_tail++;
	अन्यथा
		priv->tx_desc_tail = 0;
	priv->tx_desc_मुक्त--;
	priv->tx_मुक्त_mem -= len;
पूर्ण

अटल netdev_tx_t start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा ieee80211_hdr header;
	अचिन्हित दीर्घ flags;
	u16 buff, frame_ctl, len = (ETH_ZLEN < skb->len) ? skb->len : ETH_ZLEN;

	अगर (priv->card && priv->present_callback &&
	    !(*priv->present_callback)(priv->card)) अणु
		dev->stats.tx_errors++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (priv->station_state != STATION_STATE_READY) अणु
		dev->stats.tx_errors++;
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* first ensure the समयr func cannot run */
	spin_lock_bh(&priv->समयrlock);
	/* then stop the hardware ISR */
	spin_lock_irqsave(&priv->irqlock, flags);
	/* nb करोing the above in the opposite order will deadlock */

	/* The Wireless Header is 30 bytes. In the Ethernet packet we "cut" the
	   12 first bytes (containing DA/SA) and put them in the appropriate
	   fields of the Wireless Header. Thus the packet length is then the
	   initial + 18 (+30-12) */

	अगर (!(buff = find_tx_buff(priv, len + 18))) अणु
		dev->stats.tx_dropped++;
		spin_unlock_irqrestore(&priv->irqlock, flags);
		spin_unlock_bh(&priv->समयrlock);
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	frame_ctl = IEEE80211_FTYPE_DATA;
	header.duration_id = 0;
	header.seq_ctrl = 0;
	अगर (priv->wep_is_on)
		frame_ctl |= IEEE80211_FCTL_PROTECTED;
	अगर (priv->operating_mode == IW_MODE_ADHOC) अणु
		skb_copy_from_linear_data(skb, &header.addr1, ETH_ALEN);
		स_नकल(&header.addr2, dev->dev_addr, ETH_ALEN);
		स_नकल(&header.addr3, priv->BSSID, ETH_ALEN);
	पूर्ण अन्यथा अणु
		frame_ctl |= IEEE80211_FCTL_TODS;
		स_नकल(&header.addr1, priv->CurrentBSSID, ETH_ALEN);
		स_नकल(&header.addr2, dev->dev_addr, ETH_ALEN);
		skb_copy_from_linear_data(skb, &header.addr3, ETH_ALEN);
	पूर्ण

	अगर (priv->use_wpa)
		स_नकल(&header.addr4, rfc1042_header, ETH_ALEN);

	header.frame_control = cpu_to_le16(frame_ctl);
	/* Copy the wireless header पूर्णांकo the card */
	aपंचांगel_copy_to_card(dev, buff, (अचिन्हित अक्षर *)&header, DATA_FRAME_WS_HEADER_SIZE);
	/* Copy the packet sans its 802.3 header addresses which have been replaced */
	aपंचांगel_copy_to_card(dev, buff + DATA_FRAME_WS_HEADER_SIZE, skb->data + 12, len - 12);
	priv->tx_buff_tail += len - 12 + DATA_FRAME_WS_HEADER_SIZE;

	/* low bit of first byte of destination tells us अगर broadcast */
	tx_update_descriptor(priv, *(skb->data) & 0x01, len + 18, buff, TX_PACKET_TYPE_DATA);
	dev->stats.tx_bytes += len;

	spin_unlock_irqrestore(&priv->irqlock, flags);
	spin_unlock_bh(&priv->समयrlock);
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम aपंचांगel_transmit_management_frame(काष्ठा aपंचांगel_निजी *priv,
					    काष्ठा ieee80211_hdr *header,
					    u8 *body, पूर्णांक body_len)
अणु
	u16 buff;
	पूर्णांक len = MGMT_FRAME_BODY_OFFSET + body_len;

	अगर (!(buff = find_tx_buff(priv, len)))
		वापस;

	aपंचांगel_copy_to_card(priv->dev, buff, (u8 *)header, MGMT_FRAME_BODY_OFFSET);
	aपंचांगel_copy_to_card(priv->dev, buff + MGMT_FRAME_BODY_OFFSET, body, body_len);
	priv->tx_buff_tail += len;
	tx_update_descriptor(priv, header->addr1[0] & 0x01, len, buff, TX_PACKET_TYPE_MGMT);
पूर्ण

अटल व्योम fast_rx_path(काष्ठा aपंचांगel_निजी *priv,
			 काष्ठा ieee80211_hdr *header,
			 u16 msdu_size, u16 rx_packet_loc, u32 crc)
अणु
	/* fast path: unfragmented packet copy directly पूर्णांकo skbuf */
	u8 mac4[6];
	काष्ठा sk_buff	*skb;
	अचिन्हित अक्षर *skbp;

	/* get the final, mac 4 header field, this tells us encapsulation */
	aपंचांगel_copy_to_host(priv->dev, mac4, rx_packet_loc + 24, 6);
	msdu_size -= 6;

	अगर (priv->करो_rx_crc) अणु
		crc = crc32_le(crc, mac4, 6);
		msdu_size -= 4;
	पूर्ण

	अगर (!(skb = dev_alloc_skb(msdu_size + 14))) अणु
		priv->dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	skb_reserve(skb, 2);
	skbp = skb_put(skb, msdu_size + 12);
	aपंचांगel_copy_to_host(priv->dev, skbp + 12, rx_packet_loc + 30, msdu_size);

	अगर (priv->करो_rx_crc) अणु
		u32 netcrc;
		crc = crc32_le(crc, skbp + 12, msdu_size);
		aपंचांगel_copy_to_host(priv->dev, (व्योम *)&netcrc, rx_packet_loc + 30 + msdu_size, 4);
		अगर ((crc ^ 0xffffffff) != netcrc) अणु
			priv->dev->stats.rx_crc_errors++;
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	स_नकल(skbp, header->addr1, ETH_ALEN); /* destination address */
	अगर (le16_to_cpu(header->frame_control) & IEEE80211_FCTL_FROMDS)
		स_नकल(&skbp[ETH_ALEN], header->addr3, ETH_ALEN);
	अन्यथा
		स_नकल(&skbp[ETH_ALEN], header->addr2, ETH_ALEN); /* source address */

	skb->protocol = eth_type_trans(skb, priv->dev);
	skb->ip_summed = CHECKSUM_NONE;
	netअगर_rx(skb);
	priv->dev->stats.rx_bytes += 12 + msdu_size;
	priv->dev->stats.rx_packets++;
पूर्ण

/* Test to see अगर the packet in card memory at packet_loc has a valid CRC
   It करोesn't matter that this is slow: it is only used to proble the first few
   packets. */
अटल पूर्णांक probe_crc(काष्ठा aपंचांगel_निजी *priv, u16 packet_loc, u16 msdu_size)
अणु
	पूर्णांक i = msdu_size - 4;
	u32 netcrc, crc = 0xffffffff;

	अगर (msdu_size < 4)
		वापस 0;

	aपंचांगel_copy_to_host(priv->dev, (व्योम *)&netcrc, packet_loc + i, 4);

	aपंचांगel_ग_लिखोAR(priv->dev, packet_loc);
	जबतक (i--) अणु
		u8 octet = aपंचांगel_पढ़ो8(priv->dev, DR);
		crc = crc32_le(crc, &octet, 1);
	पूर्ण

	वापस (crc ^ 0xffffffff) == netcrc;
पूर्ण

अटल व्योम frag_rx_path(काष्ठा aपंचांगel_निजी *priv,
			 काष्ठा ieee80211_hdr *header,
			 u16 msdu_size, u16 rx_packet_loc, u32 crc, u16 seq_no,
			 u8 frag_no, पूर्णांक more_frags)
अणु
	u8 mac4[ETH_ALEN];
	u8 source[ETH_ALEN];
	काष्ठा sk_buff *skb;

	अगर (le16_to_cpu(header->frame_control) & IEEE80211_FCTL_FROMDS)
		स_नकल(source, header->addr3, ETH_ALEN);
	अन्यथा
		स_नकल(source, header->addr2, ETH_ALEN);

	rx_packet_loc += 24; /* skip header */

	अगर (priv->करो_rx_crc)
		msdu_size -= 4;

	अगर (frag_no == 0) अणु /* first fragment */
		aपंचांगel_copy_to_host(priv->dev, mac4, rx_packet_loc, ETH_ALEN);
		msdu_size -= ETH_ALEN;
		rx_packet_loc += ETH_ALEN;

		अगर (priv->करो_rx_crc)
			crc = crc32_le(crc, mac4, 6);

		priv->frag_seq = seq_no;
		priv->frag_no = 1;
		priv->frag_len = msdu_size;
		स_नकल(priv->frag_source, source, ETH_ALEN);
		स_नकल(&priv->rx_buf[ETH_ALEN], source, ETH_ALEN);
		स_नकल(priv->rx_buf, header->addr1, ETH_ALEN);

		aपंचांगel_copy_to_host(priv->dev, &priv->rx_buf[12], rx_packet_loc, msdu_size);

		अगर (priv->करो_rx_crc) अणु
			u32 netcrc;
			crc = crc32_le(crc, &priv->rx_buf[12], msdu_size);
			aपंचांगel_copy_to_host(priv->dev, (व्योम *)&netcrc, rx_packet_loc + msdu_size, 4);
			अगर ((crc ^ 0xffffffff) != netcrc) अणु
				priv->dev->stats.rx_crc_errors++;
				eth_broadcast_addr(priv->frag_source);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (priv->frag_no == frag_no &&
		   priv->frag_seq == seq_no &&
		   स_भेद(priv->frag_source, source, ETH_ALEN) == 0) अणु

		aपंचांगel_copy_to_host(priv->dev, &priv->rx_buf[12 + priv->frag_len],
				   rx_packet_loc, msdu_size);
		अगर (priv->करो_rx_crc) अणु
			u32 netcrc;
			crc = crc32_le(crc,
				       &priv->rx_buf[12 + priv->frag_len],
				       msdu_size);
			aपंचांगel_copy_to_host(priv->dev, (व्योम *)&netcrc, rx_packet_loc + msdu_size, 4);
			अगर ((crc ^ 0xffffffff) != netcrc) अणु
				priv->dev->stats.rx_crc_errors++;
				eth_broadcast_addr(priv->frag_source);
				more_frags = 1; /* करोn't send broken assembly */
			पूर्ण
		पूर्ण

		priv->frag_len += msdu_size;
		priv->frag_no++;

		अगर (!more_frags) अणु /* last one */
			eth_broadcast_addr(priv->frag_source);
			अगर (!(skb = dev_alloc_skb(priv->frag_len + 14))) अणु
				priv->dev->stats.rx_dropped++;
			पूर्ण अन्यथा अणु
				skb_reserve(skb, 2);
				skb_put_data(skb, priv->rx_buf,
				             priv->frag_len + 12);
				skb->protocol = eth_type_trans(skb, priv->dev);
				skb->ip_summed = CHECKSUM_NONE;
				netअगर_rx(skb);
				priv->dev->stats.rx_bytes += priv->frag_len + 12;
				priv->dev->stats.rx_packets++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		priv->wstats.discard.fragment++;
पूर्ण

अटल व्योम rx_करोne_irq(काष्ठा aपंचांगel_निजी *priv)
अणु
	पूर्णांक i;
	काष्ठा ieee80211_hdr header;

	क्रम (i = 0;
	     aपंचांगel_rmem8(priv, aपंचांगel_rx(priv, RX_DESC_FLAGS_OFFSET, priv->rx_desc_head)) == RX_DESC_FLAG_VALID &&
		     i < priv->host_info.rx_desc_count;
	     i++) अणु

		u16 msdu_size, rx_packet_loc, frame_ctl, seq_control;
		u8 status = aपंचांगel_rmem8(priv, aपंचांगel_rx(priv, RX_DESC_STATUS_OFFSET, priv->rx_desc_head));
		u32 crc = 0xffffffff;

		अगर (status != RX_STATUS_SUCCESS) अणु
			अगर (status == 0xc1) /* determined by experiment */
				priv->wstats.discard.nwid++;
			अन्यथा
				priv->dev->stats.rx_errors++;
			जाओ next;
		पूर्ण

		msdu_size = aपंचांगel_rmem16(priv, aपंचांगel_rx(priv, RX_DESC_MSDU_SIZE_OFFSET, priv->rx_desc_head));
		rx_packet_loc = aपंचांगel_rmem16(priv, aपंचांगel_rx(priv, RX_DESC_MSDU_POS_OFFSET, priv->rx_desc_head));

		अगर (msdu_size < 30) अणु
			priv->dev->stats.rx_errors++;
			जाओ next;
		पूर्ण

		/* Get header as far as end of seq_ctrl */
		aपंचांगel_copy_to_host(priv->dev, (अक्षर *)&header, rx_packet_loc, 24);
		frame_ctl = le16_to_cpu(header.frame_control);
		seq_control = le16_to_cpu(header.seq_ctrl);

		/* probe क्रम CRC use here अगर needed  once five packets have
		   arrived with the same crc status, we assume we know what's
		   happening and stop probing */
		अगर (priv->probe_crc) अणु
			अगर (!priv->wep_is_on || !(frame_ctl & IEEE80211_FCTL_PROTECTED)) अणु
				priv->करो_rx_crc = probe_crc(priv, rx_packet_loc, msdu_size);
			पूर्ण अन्यथा अणु
				priv->करो_rx_crc = probe_crc(priv, rx_packet_loc + 24, msdu_size - 24);
			पूर्ण
			अगर (priv->करो_rx_crc) अणु
				अगर (priv->crc_ok_cnt++ > 5)
					priv->probe_crc = 0;
			पूर्ण अन्यथा अणु
				अगर (priv->crc_ko_cnt++ > 5)
					priv->probe_crc = 0;
			पूर्ण
		पूर्ण

		/* करोn't CRC header when WEP in use */
		अगर (priv->करो_rx_crc && (!priv->wep_is_on || !(frame_ctl & IEEE80211_FCTL_PROTECTED))) अणु
			crc = crc32_le(0xffffffff, (अचिन्हित अक्षर *)&header, 24);
		पूर्ण
		msdu_size -= 24; /* header */

		अगर ((frame_ctl & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_DATA) अणु
			पूर्णांक more_fragments = frame_ctl & IEEE80211_FCTL_MOREFRAGS;
			u8 packet_fragment_no = seq_control & IEEE80211_SCTL_FRAG;
			u16 packet_sequence_no = (seq_control & IEEE80211_SCTL_SEQ) >> 4;

			अगर (!more_fragments && packet_fragment_no == 0) अणु
				fast_rx_path(priv, &header, msdu_size, rx_packet_loc, crc);
			पूर्ण अन्यथा अणु
				frag_rx_path(priv, &header, msdu_size, rx_packet_loc, crc,
					     packet_sequence_no, packet_fragment_no, more_fragments);
			पूर्ण
		पूर्ण

		अगर ((frame_ctl & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_MGMT) अणु
			/* copy rest of packet पूर्णांकo buffer */
			aपंचांगel_copy_to_host(priv->dev, (अचिन्हित अक्षर *)&priv->rx_buf, rx_packet_loc + 24, msdu_size);

			/* we use the same buffer क्रम frag reassembly and control packets */
			eth_broadcast_addr(priv->frag_source);

			अगर (priv->करो_rx_crc) अणु
				/* last 4 octets is crc */
				msdu_size -= 4;
				crc = crc32_le(crc, (अचिन्हित अक्षर *)&priv->rx_buf, msdu_size);
				अगर ((crc ^ 0xffffffff) != (*((u32 *)&priv->rx_buf[msdu_size]))) अणु
					priv->dev->stats.rx_crc_errors++;
					जाओ next;
				पूर्ण
			पूर्ण

			aपंचांगel_management_frame(priv, &header, msdu_size,
					       aपंचांगel_rmem8(priv, aपंचांगel_rx(priv, RX_DESC_RSSI_OFFSET, priv->rx_desc_head)));
		पूर्ण

next:
		/* release descriptor */
		aपंचांगel_wmem8(priv, aपंचांगel_rx(priv, RX_DESC_FLAGS_OFFSET, priv->rx_desc_head), RX_DESC_FLAG_CONSUMED);

		अगर (priv->rx_desc_head < (priv->host_info.rx_desc_count - 1))
			priv->rx_desc_head++;
		अन्यथा
			priv->rx_desc_head = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t service_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	u8 isr;
	पूर्णांक i = -1;
	अटल स्थिर u8 irq_order[] = अणु
		ISR_OUT_OF_RANGE,
		ISR_RxCOMPLETE,
		ISR_TxCOMPLETE,
		ISR_RxFRAMELOST,
		ISR_FATAL_ERROR,
		ISR_COMMAND_COMPLETE,
		ISR_IBSS_MERGE,
		ISR_GENERIC_IRQ
	पूर्ण;

	अगर (priv->card && priv->present_callback &&
	    !(*priv->present_callback)(priv->card))
		वापस IRQ_HANDLED;

	/* In this state upper-level code assumes it can mess with
	   the card unhampered by पूर्णांकerrupts which may change रेजिस्टर state.
	   Note that even though the card shouldn't generate पूर्णांकerrupts
	   the पूर्णांकurrupt line may be shared. This allows card setup
	   to go on without disabling पूर्णांकerrupts क्रम a दीर्घ समय. */
	अगर (priv->station_state == STATION_STATE_DOWN)
		वापस IRQ_NONE;

	aपंचांगel_clear_gcr(dev, GCR_ENINT); /* disable पूर्णांकerrupts */

	जबतक (1) अणु
		अगर (!aपंचांगel_lock_mac(priv)) अणु
			/* failed to contact card */
			prपूर्णांकk(KERN_ALERT "%s: failed to contact MAC.\n", dev->name);
			वापस IRQ_HANDLED;
		पूर्ण

		isr = aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_INT_STATUS_OFFSET));
		aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_MAC_OFFSET), 0);

		अगर (!isr) अणु
			aपंचांगel_set_gcr(dev, GCR_ENINT); /* enable पूर्णांकerrupts */
			वापस i == -1 ? IRQ_NONE : IRQ_HANDLED;
		पूर्ण

		aपंचांगel_set_gcr(dev, GCR_ACKINT); /* acknowledge पूर्णांकerrupt */

		क्रम (i = 0; i < ARRAY_SIZE(irq_order); i++)
			अगर (isr & irq_order[i])
				अवरोध;

		अगर (!aपंचांगel_lock_mac(priv)) अणु
			/* failed to contact card */
			prपूर्णांकk(KERN_ALERT "%s: failed to contact MAC.\n", dev->name);
			वापस IRQ_HANDLED;
		पूर्ण

		isr = aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_INT_STATUS_OFFSET));
		isr ^= irq_order[i];
		aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_INT_STATUS_OFFSET), isr);
		aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_MAC_OFFSET), 0);

		चयन (irq_order[i]) अणु

		हाल ISR_OUT_OF_RANGE:
			अगर (priv->operating_mode == IW_MODE_INFRA &&
			    priv->station_state == STATION_STATE_READY) अणु
				priv->station_is_associated = 0;
				aपंचांगel_scan(priv, 1);
			पूर्ण
			अवरोध;

		हाल ISR_RxFRAMELOST:
			priv->wstats.discard.misc++;
			fallthrough;
		हाल ISR_RxCOMPLETE:
			rx_करोne_irq(priv);
			अवरोध;

		हाल ISR_TxCOMPLETE:
			tx_करोne_irq(priv);
			अवरोध;

		हाल ISR_FATAL_ERROR:
			prपूर्णांकk(KERN_ALERT "%s: *** FATAL error interrupt ***\n", dev->name);
			aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			अवरोध;

		हाल ISR_COMMAND_COMPLETE:
			aपंचांगel_command_irq(priv);
			अवरोध;

		हाल ISR_IBSS_MERGE:
			aपंचांगel_get_mib(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_CUR_BSSID_POS,
				      priv->CurrentBSSID, 6);
			/* The WPA stuff cares about the current AP address */
			अगर (priv->use_wpa)
				build_wpa_mib(priv);
			अवरोध;
		हाल ISR_GENERIC_IRQ:
			prपूर्णांकk(KERN_INFO "%s: Generic_irq received.\n", dev->name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा iw_statistics *aपंचांगel_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* update the link quality here in हाल we are seeing no beacons
	   at all to drive the process */
	aपंचांगel_smooth_qual(priv);

	priv->wstats.status = priv->station_state;

	अगर (priv->operating_mode == IW_MODE_INFRA) अणु
		अगर (priv->station_state != STATION_STATE_READY) अणु
			priv->wstats.qual.qual = 0;
			priv->wstats.qual.level = 0;
			priv->wstats.qual.updated = (IW_QUAL_QUAL_INVALID
					| IW_QUAL_LEVEL_INVALID);
		पूर्ण
		priv->wstats.qual.noise = 0;
		priv->wstats.qual.updated |= IW_QUAL_NOISE_INVALID;
	पूर्ण अन्यथा अणु
		/* Quality levels cannot be determined in ad-hoc mode,
		   because we can 'hear' more that one remote station. */
		priv->wstats.qual.qual = 0;
		priv->wstats.qual.level	= 0;
		priv->wstats.qual.noise	= 0;
		priv->wstats.qual.updated = IW_QUAL_QUAL_INVALID
					| IW_QUAL_LEVEL_INVALID
					| IW_QUAL_NOISE_INVALID;
		priv->wstats.miss.beacon = 0;
	पूर्ण

	वापस &priv->wstats;
पूर्ण

अटल पूर्णांक aपंचांगel_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	स_नकल (dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस aपंचांगel_खोलो(dev);
पूर्ण

EXPORT_SYMBOL(aपंचांगel_खोलो);

पूर्णांक aपंचांगel_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक i, channel, err;

	/* any scheduled समयr is no दीर्घer needed and might screw things up.. */
	del_समयr_sync(&priv->management_समयr);

	/* Interrupts will not touch the card once in this state... */
	priv->station_state = STATION_STATE_DOWN;

	अगर (priv->new_SSID_size) अणु
		स_नकल(priv->SSID, priv->new_SSID, priv->new_SSID_size);
		priv->SSID_size = priv->new_SSID_size;
		priv->new_SSID_size = 0;
	पूर्ण
	priv->BSS_list_entries = 0;

	priv->AuthenticationRequestRetryCnt = 0;
	priv->AssociationRequestRetryCnt = 0;
	priv->ReAssociationRequestRetryCnt = 0;
	priv->CurrentAuthentTransactionSeqNum = 0x0001;
	priv->ExpectedAuthentTransactionSeqNum = 0x0002;

	priv->site_survey_state = SITE_SURVEY_IDLE;
	priv->station_is_associated = 0;

	err = reset_aपंचांगel_card(dev);
	अगर (err)
		वापस err;

	अगर (priv->config_reg_करोमुख्य) अणु
		priv->reg_करोमुख्य = priv->config_reg_करोमुख्य;
		aपंचांगel_set_mib8(priv, Phy_Mib_Type, PHY_MIB_REG_DOMAIN_POS, priv->reg_करोमुख्य);
	पूर्ण अन्यथा अणु
		priv->reg_करोमुख्य = aपंचांगel_get_mib8(priv, Phy_Mib_Type, PHY_MIB_REG_DOMAIN_POS);
		क्रम (i = 0; i < ARRAY_SIZE(channel_table); i++)
			अगर (priv->reg_करोमुख्य == channel_table[i].reg_करोमुख्य)
				अवरोध;
		अगर (i == ARRAY_SIZE(channel_table)) अणु
			priv->reg_करोमुख्य = REG_DOMAIN_MKK1;
			prपूर्णांकk(KERN_ALERT "%s: failed to get regulatory domain: assuming MKK1.\n", dev->name);
		पूर्ण
	पूर्ण

	अगर ((channel = aपंचांगel_validate_channel(priv, priv->channel)))
		priv->channel = channel;

	/* this moves station_state on.... */
	aपंचांगel_scan(priv, 1);

	aपंचांगel_set_gcr(priv->dev, GCR_ENINT); /* enable पूर्णांकerrupts */
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* Send event to userspace that we are disassociating */
	अगर (priv->station_state == STATION_STATE_READY) अणु
		जोड़ iwreq_data wrqu;

		wrqu.data.length = 0;
		wrqu.data.flags = 0;
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		eth_zero_addr(wrqu.ap_addr.sa_data);
		wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, शून्य);
	पूर्ण

	aपंचांगel_enter_state(priv, STATION_STATE_DOWN);

	अगर (priv->bus_type == BUS_TYPE_PCCARD)
		aपंचांगel_ग_लिखो16(dev, GCR, 0x0060);
	aपंचांगel_ग_लिखो16(dev, GCR, 0x0040);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_validate_channel(काष्ठा aपंचांगel_निजी *priv, पूर्णांक channel)
अणु
	/* check that channel is OK, अगर so वापस zero,
	   अन्यथा वापस suitable शेष channel */
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(channel_table); i++)
		अगर (priv->reg_करोमुख्य == channel_table[i].reg_करोमुख्य) अणु
			अगर (channel >= channel_table[i].min &&
			    channel <= channel_table[i].max)
				वापस 0;
			अन्यथा
				वापस channel_table[i].min;
		पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक aपंचांगel_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा aपंचांगel_निजी *priv = m->निजी;
	पूर्णांक i;
	अक्षर *s, *r, *c;

	seq_म_लिखो(m, "Driver version:\t\t%d.%d\n", DRIVER_MAJOR, DRIVER_MINOR);

	अगर (priv->station_state != STATION_STATE_DOWN) अणु
		seq_म_लिखो(m,
			   "Firmware version:\t%d.%d build %d\n"
			   "Firmware location:\t",
			   priv->host_info.major_version,
			   priv->host_info.minor_version,
			   priv->host_info.build_version);

		अगर (priv->card_type != CARD_TYPE_EEPROM)
			seq_माला_दो(m, "on card\n");
		अन्यथा अगर (priv->firmware)
			seq_म_लिखो(m, "%s loaded by host\n", priv->firmware_id);
		अन्यथा
			seq_म_लिखो(m, "%s loaded by hotplug\n", priv->firmware_id);

		चयन (priv->card_type) अणु
		हाल CARD_TYPE_PARALLEL_FLASH:
			c = "Parallel flash";
			अवरोध;
		हाल CARD_TYPE_SPI_FLASH:
			c = "SPI flash\n";
			अवरोध;
		हाल CARD_TYPE_EEPROM:
			c = "EEPROM";
			अवरोध;
		शेष:
			c = "<unknown>";
		पूर्ण

		r = "<unknown>";
		क्रम (i = 0; i < ARRAY_SIZE(channel_table); i++)
			अगर (priv->reg_करोमुख्य == channel_table[i].reg_करोमुख्य)
				r = channel_table[i].name;

		seq_म_लिखो(m, "MAC memory type:\t%s\n", c);
		seq_म_लिखो(m, "Regulatory domain:\t%s\n", r);
		seq_म_लिखो(m, "Host CRC checking:\t%s\n",
			 priv->करो_rx_crc ? "On" : "Off");
		seq_म_लिखो(m, "WPA-capable firmware:\t%s\n",
			 priv->use_wpa ? "Yes" : "No");
	पूर्ण

	चयन (priv->station_state) अणु
	हाल STATION_STATE_SCANNING:
		s = "Scanning";
		अवरोध;
	हाल STATION_STATE_JOINNING:
		s = "Joining";
		अवरोध;
	हाल STATION_STATE_AUTHENTICATING:
		s = "Authenticating";
		अवरोध;
	हाल STATION_STATE_ASSOCIATING:
		s = "Associating";
		अवरोध;
	हाल STATION_STATE_READY:
		s = "Ready";
		अवरोध;
	हाल STATION_STATE_REASSOCIATING:
		s = "Reassociating";
		अवरोध;
	हाल STATION_STATE_MGMT_ERROR:
		s = "Management error";
		अवरोध;
	हाल STATION_STATE_DOWN:
		s = "Down";
		अवरोध;
	शेष:
		s = "<unknown>";
	पूर्ण

	seq_म_लिखो(m, "Current state:\t\t%s\n", s);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops aपंचांगel_netdev_ops = अणु
	.nकरो_खोलो 		= aपंचांगel_खोलो,
	.nकरो_stop		= aपंचांगel_बंद,
	.nकरो_set_mac_address 	= aपंचांगel_set_mac_address,
	.nकरो_start_xmit 	= start_tx,
	.nकरो_करो_ioctl 		= aपंचांगel_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

काष्ठा net_device *init_aपंचांगel_card(अचिन्हित लघु irq, अचिन्हित दीर्घ port,
				   स्थिर AपंचांगelFWType fw_type,
				   काष्ठा device *sys_dev,
				   पूर्णांक (*card_present)(व्योम *), व्योम *card)
अणु
	काष्ठा net_device *dev;
	काष्ठा aपंचांगel_निजी *priv;
	पूर्णांक rc;

	/* Create the network device object. */
	dev = alloc_etherdev(माप(*priv));
	अगर (!dev)
		वापस शून्य;

	अगर (dev_alloc_name(dev, dev->name) < 0) अणु
		prपूर्णांकk(KERN_ERR "atmel: Couldn't get name!\n");
		जाओ err_out_मुक्त;
	पूर्ण

	priv = netdev_priv(dev);
	priv->dev = dev;
	priv->sys_dev = sys_dev;
	priv->present_callback = card_present;
	priv->card = card;
	priv->firmware = शून्य;
	priv->firmware_type = fw_type;
	अगर (firmware) /* module parameter */
		strlcpy(priv->firmware_id, firmware, माप(priv->firmware_id));
	priv->bus_type = card_present ? BUS_TYPE_PCCARD : BUS_TYPE_PCI;
	priv->station_state = STATION_STATE_DOWN;
	priv->करो_rx_crc = 0;
	/* For PCMCIA cards, some chips need CRC, some करोn't
	   so we have to probe. */
	अगर (priv->bus_type == BUS_TYPE_PCCARD) अणु
		priv->probe_crc = 1;
		priv->crc_ok_cnt = priv->crc_ko_cnt = 0;
	पूर्ण अन्यथा
		priv->probe_crc = 0;
	priv->last_qual = jअगरfies;
	priv->last_beacon_बारtamp = 0;
	स_रखो(priv->frag_source, 0xff, माप(priv->frag_source));
	eth_zero_addr(priv->BSSID);
	priv->CurrentBSSID[0] = 0xFF; /* Initialize to something invalid.... */
	priv->station_was_associated = 0;

	priv->last_survey = jअगरfies;
	priv->preamble = LONG_PREAMBLE;
	priv->operating_mode = IW_MODE_INFRA;
	priv->connect_to_any_BSS = 0;
	priv->config_reg_करोमुख्य = 0;
	priv->reg_करोमुख्य = 0;
	priv->tx_rate = 3;
	priv->स्वतः_tx_rate = 1;
	priv->channel = 4;
	priv->घातer_mode = 0;
	priv->SSID[0] = '\0';
	priv->SSID_size = 0;
	priv->new_SSID_size = 0;
	priv->frag_threshold = 2346;
	priv->rts_threshold = 2347;
	priv->लघु_retry = 7;
	priv->दीर्घ_retry = 4;

	priv->wep_is_on = 0;
	priv->शेष_key = 0;
	priv->encryption_level = 0;
	priv->exclude_unencrypted = 0;
	priv->group_cipher_suite = priv->pairwise_cipher_suite = CIPHER_SUITE_NONE;
	priv->use_wpa = 0;
	स_रखो(priv->wep_keys, 0, माप(priv->wep_keys));
	स_रखो(priv->wep_key_len, 0, माप(priv->wep_key_len));

	priv->शेष_beacon_period = priv->beacon_period = 100;
	priv->listen_पूर्णांकerval = 1;

	समयr_setup(&priv->management_समयr, aपंचांगel_management_समयr, 0);
	spin_lock_init(&priv->irqlock);
	spin_lock_init(&priv->समयrlock);

	dev->netdev_ops = &aपंचांगel_netdev_ops;
	dev->wireless_handlers = &aपंचांगel_handler_def;
	dev->irq = irq;
	dev->base_addr = port;

	/* MTU range: 68 - 2312 */
	dev->min_mtu = 68;
	dev->max_mtu = MAX_WIRELESS_BODY - ETH_FCS_LEN;

	SET_NETDEV_DEV(dev, sys_dev);

	अगर ((rc = request_irq(dev->irq, service_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev))) अणु
		prपूर्णांकk(KERN_ERR "%s: register interrupt %d failed, rc %d\n", dev->name, irq, rc);
		जाओ err_out_मुक्त;
	पूर्ण

	अगर (!request_region(dev->base_addr, 32,
			    priv->bus_type == BUS_TYPE_PCCARD ?  "atmel_cs" : "atmel_pci")) अणु
		जाओ err_out_irq;
	पूर्ण

	अगर (रेजिस्टर_netdev(dev))
		जाओ err_out_res;

	अगर (!probe_aपंचांगel_card(dev)) अणु
		unरेजिस्टर_netdev(dev);
		जाओ err_out_res;
	पूर्ण

	netअगर_carrier_off(dev);

	अगर (!proc_create_single_data("driver/atmel", 0, शून्य, aपंचांगel_proc_show,
			priv))
		prपूर्णांकk(KERN_WARNING "atmel: unable to create /proc entry.\n");

	prपूर्णांकk(KERN_INFO "%s: Atmel at76c50x. Version %d.%d. MAC %pM\n",
	       dev->name, DRIVER_MAJOR, DRIVER_MINOR, dev->dev_addr);

	वापस dev;

err_out_res:
	release_region(dev->base_addr, 32);
err_out_irq:
	मुक्त_irq(dev->irq, dev);
err_out_मुक्त:
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(init_aपंचांगel_card);

व्योम stop_aपंचांगel_card(काष्ठा net_device *dev)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* put a brick on it... */
	अगर (priv->bus_type == BUS_TYPE_PCCARD)
		aपंचांगel_ग_लिखो16(dev, GCR, 0x0060);
	aपंचांगel_ग_लिखो16(dev, GCR, 0x0040);

	del_समयr_sync(&priv->management_समयr);
	unरेजिस्टर_netdev(dev);
	हटाओ_proc_entry("driver/atmel", शून्य);
	मुक्त_irq(dev->irq, dev);
	kमुक्त(priv->firmware);
	release_region(dev->base_addr, 32);
	मुक्त_netdev(dev);
पूर्ण

EXPORT_SYMBOL(stop_aपंचांगel_card);

अटल पूर्णांक aपंचांगel_set_essid(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* Check अगर we asked क्रम `any' */
	अगर (dwrq->flags == 0) अणु
		priv->connect_to_any_BSS = 1;
	पूर्ण अन्यथा अणु
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;

		priv->connect_to_any_BSS = 0;

		/* Check the size of the string */
		अगर (dwrq->length > MAX_SSID_LENGTH)
			 वापस -E2BIG;
		अगर (index != 0)
			वापस -EINVAL;

		स_नकल(priv->new_SSID, extra, dwrq->length);
		priv->new_SSID_size = dwrq->length;
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_get_essid(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* Get the current SSID */
	अगर (priv->new_SSID_size != 0) अणु
		स_नकल(extra, priv->new_SSID, priv->new_SSID_size);
		dwrq->length = priv->new_SSID_size;
	पूर्ण अन्यथा अणु
		स_नकल(extra, priv->SSID, priv->SSID_size);
		dwrq->length = priv->SSID_size;
	पूर्ण

	dwrq->flags = !priv->connect_to_any_BSS; /* active */

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_get_wap(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा sockaddr *awrq,
			 अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	स_नकल(awrq->sa_data, priv->CurrentBSSID, ETH_ALEN);
	awrq->sa_family = ARPHRD_ETHER;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_encode(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा iw_poपूर्णांक *dwrq,
			    अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* Basic checking: करो we have a key to set ?
	 * Note : with the new API, it's impossible to get a शून्य poपूर्णांकer.
	 * Thereक्रमe, we need to check a key size == 0 instead.
	 * New version of iwconfig properly set the IW_ENCODE_NOKEY flag
	 * when no key is present (only change flags), but older versions
	 * करोn't करो it. - Jean II */
	अगर (dwrq->length > 0) अणु
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		पूर्णांक current_index = priv->शेष_key;
		/* Check the size of the key */
		अगर (dwrq->length > 13) अणु
			वापस -EINVAL;
		पूर्ण
		/* Check the index (none -> use current) */
		अगर (index < 0 || index >= 4)
			index = current_index;
		अन्यथा
			priv->शेष_key = index;
		/* Set the length */
		अगर (dwrq->length > 5)
			priv->wep_key_len[index] = 13;
		अन्यथा
			अगर (dwrq->length > 0)
				priv->wep_key_len[index] = 5;
			अन्यथा
				/* Disable the key */
				priv->wep_key_len[index] = 0;
		/* Check अगर the key is not marked as invalid */
		अगर (!(dwrq->flags & IW_ENCODE_NOKEY)) अणु
			/* Cleanup */
			स_रखो(priv->wep_keys[index], 0, 13);
			/* Copy the key in the driver */
			स_नकल(priv->wep_keys[index], extra, dwrq->length);
		पूर्ण
		/* WE specअगरy that अगर a valid key is set, encryption
		 * should be enabled (user may turn it off later)
		 * This is also how "iwconfig ethX key on" works */
		अगर (index == current_index &&
		    priv->wep_key_len[index] > 0) अणु
			priv->wep_is_on = 1;
			priv->exclude_unencrypted = 1;
			अगर (priv->wep_key_len[index] > 5) अणु
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
				priv->encryption_level = 2;
			पूर्ण अन्यथा अणु
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
				priv->encryption_level = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Do we want to just set the transmit key index ? */
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		अगर (index >= 0 && index < 4) अणु
			priv->शेष_key = index;
		पूर्ण अन्यथा
			/* Don't complain अगर only change the mode */
			अगर (!(dwrq->flags & IW_ENCODE_MODE))
				वापस -EINVAL;
	पूर्ण
	/* Read the flags */
	अगर (dwrq->flags & IW_ENCODE_DISABLED) अणु
		priv->wep_is_on = 0;
		priv->encryption_level = 0;
		priv->pairwise_cipher_suite = CIPHER_SUITE_NONE;
	पूर्ण अन्यथा अणु
		priv->wep_is_on = 1;
		अगर (priv->wep_key_len[priv->शेष_key] > 5) अणु
			priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
			priv->encryption_level = 2;
		पूर्ण अन्यथा अणु
			priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
			priv->encryption_level = 1;
		पूर्ण
	पूर्ण
	अगर (dwrq->flags & IW_ENCODE_RESTRICTED)
		priv->exclude_unencrypted = 1;
	अगर (dwrq->flags & IW_ENCODE_OPEN)
		priv->exclude_unencrypted = 0;

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक aपंचांगel_get_encode(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा iw_poपूर्णांक *dwrq,
			    अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;

	अगर (!priv->wep_is_on)
		dwrq->flags = IW_ENCODE_DISABLED;
	अन्यथा अणु
		अगर (priv->exclude_unencrypted)
			dwrq->flags = IW_ENCODE_RESTRICTED;
		अन्यथा
			dwrq->flags = IW_ENCODE_OPEN;
	पूर्ण
		/* Which key करो we want ? -1 -> tx index */
	अगर (index < 0 || index >= 4)
		index = priv->शेष_key;
	dwrq->flags |= index + 1;
	/* Copy the key to the user buffer */
	dwrq->length = priv->wep_key_len[index];
	अगर (dwrq->length > 16) अणु
		dwrq->length = 0;
	पूर्ण अन्यथा अणु
		स_रखो(extra, 0, 16);
		स_नकल(extra, priv->wep_keys[index], dwrq->length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_encodeext(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu,
			    अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, key_len, alg = ext->alg, set_key = 1;

	/* Determine and validate the key index */
	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (idx < 1 || idx > 4)
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा
		idx = priv->शेष_key;

	अगर (encoding->flags & IW_ENCODE_DISABLED)
	    alg = IW_ENCODE_ALG_NONE;

	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		priv->शेष_key = idx;
		set_key = ext->key_len > 0 ? 1 : 0;
	पूर्ण

	अगर (set_key) अणु
		/* Set the requested key first */
		चयन (alg) अणु
		हाल IW_ENCODE_ALG_NONE:
			priv->wep_is_on = 0;
			priv->encryption_level = 0;
			priv->pairwise_cipher_suite = CIPHER_SUITE_NONE;
			अवरोध;
		हाल IW_ENCODE_ALG_WEP:
			अगर (ext->key_len > 5) अणु
				priv->wep_key_len[idx] = 13;
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
				priv->encryption_level = 2;
			पूर्ण अन्यथा अगर (ext->key_len > 0) अणु
				priv->wep_key_len[idx] = 5;
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
				priv->encryption_level = 1;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
			priv->wep_is_on = 1;
			स_रखो(priv->wep_keys[idx], 0, 13);
			key_len = min ((पूर्णांक)ext->key_len, priv->wep_key_len[idx]);
			स_नकल(priv->wep_keys[idx], ext->key, key_len);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_get_encodeext(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu,
			    अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, max_key_len;

	max_key_len = encoding->length - माप(*ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (idx < 1 || idx > 4)
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा
		idx = priv->शेष_key;

	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	अगर (!priv->wep_is_on) अणु
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
	पूर्ण अन्यथा अणु
		अगर (priv->encryption_level > 0)
			ext->alg = IW_ENCODE_ALG_WEP;
		अन्यथा
			वापस -EINVAL;

		ext->key_len = priv->wep_key_len[idx];
		स_नकल(ext->key, priv->wep_keys[idx], ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा iw_param *param = &wrqu->param;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
	हाल IW_AUTH_PRIVACY_INVOKED:
		/*
		 * aपंचांगel करोes not use these parameters
		 */
		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		priv->exclude_unencrypted = param->value ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG: अणु
			अगर (param->value & IW_AUTH_ALG_SHARED_KEY) अणु
				priv->exclude_unencrypted = 1;
			पूर्ण अन्यथा अगर (param->value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
				priv->exclude_unencrypted = 0;
			पूर्ण अन्यथा
				वापस -EINVAL;
			अवरोध;
		पूर्ण

	हाल IW_AUTH_WPA_ENABLED:
		/* Silently accept disable of WPA */
		अगर (param->value > 0)
			वापस -EOPNOTSUPP;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_get_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा iw_param *param = &wrqu->param;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_DROP_UNENCRYPTED:
		param->value = priv->exclude_unencrypted;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (priv->exclude_unencrypted == 1)
			param->value = IW_AUTH_ALG_SHARED_KEY;
		अन्यथा
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		param->value = 0;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगel_get_name(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  अक्षर *cwrq,
			  अक्षर *extra)
अणु
	म_नकल(cwrq, "IEEE 802.11-DS");
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_rate(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	अगर (vwrq->fixed == 0) अणु
		priv->tx_rate = 3;
		priv->स्वतः_tx_rate = 1;
	पूर्ण अन्यथा अणु
		priv->स्वतः_tx_rate = 0;

		/* Which type of value ? */
		अगर ((vwrq->value < 4) && (vwrq->value >= 0)) अणु
			/* Setting by rate index */
			priv->tx_rate = vwrq->value;
		पूर्ण अन्यथा अणु
		/* Setting by frequency value */
			चयन (vwrq->value) अणु
			हाल  1000000:
				priv->tx_rate = 0;
				अवरोध;
			हाल  2000000:
				priv->tx_rate = 1;
				अवरोध;
			हाल  5500000:
				priv->tx_rate = 2;
				अवरोध;
			हाल 11000000:
				priv->tx_rate = 3;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_set_mode(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  __u32 *uwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	अगर (*uwrq != IW_MODE_ADHOC && *uwrq != IW_MODE_INFRA)
		वापस -EINVAL;

	priv->operating_mode = *uwrq;
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_get_mode(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  __u32 *uwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	*uwrq = priv->operating_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_get_rate(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	अगर (priv->स्वतः_tx_rate) अणु
		vwrq->fixed = 0;
		vwrq->value = 11000000;
	पूर्ण अन्यथा अणु
		vwrq->fixed = 1;
		चयन (priv->tx_rate) अणु
		हाल 0:
			vwrq->value =  1000000;
			अवरोध;
		हाल 1:
			vwrq->value =  2000000;
			अवरोध;
		हाल 2:
			vwrq->value =  5500000;
			अवरोध;
		हाल 3:
			vwrq->value = 11000000;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_घातer(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *vwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	priv->घातer_mode = vwrq->disabled ? 0 : 1;
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_get_घातer(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *vwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	vwrq->disabled = priv->घातer_mode ? 0 : 1;
	vwrq->flags = IW_POWER_ON;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_retry(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *vwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	अगर (!vwrq->disabled && (vwrq->flags & IW_RETRY_LIMIT)) अणु
		अगर (vwrq->flags & IW_RETRY_LONG)
			priv->दीर्घ_retry = vwrq->value;
		अन्यथा अगर (vwrq->flags & IW_RETRY_SHORT)
			priv->लघु_retry = vwrq->value;
		अन्यथा अणु
			/* No modअगरier : set both */
			priv->दीर्घ_retry = vwrq->value;
			priv->लघु_retry = vwrq->value;
		पूर्ण
		वापस -EINPROGRESS;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aपंचांगel_get_retry(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_param *vwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	vwrq->disabled = 0;      /* Can't be disabled */

	/* Note : by शेष, display the लघु retry number */
	अगर (vwrq->flags & IW_RETRY_LONG) अणु
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		vwrq->value = priv->दीर्घ_retry;
	पूर्ण अन्यथा अणु
		vwrq->flags = IW_RETRY_LIMIT;
		vwrq->value = priv->लघु_retry;
		अगर (priv->दीर्घ_retry != priv->लघु_retry)
			vwrq->flags |= IW_RETRY_SHORT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_rts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक rthr = vwrq->value;

	अगर (vwrq->disabled)
		rthr = 2347;
	अगर ((rthr < 0) || (rthr > 2347)) अणु
		वापस -EINVAL;
	पूर्ण
	priv->rts_threshold = rthr;

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक aपंचांगel_get_rts(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	vwrq->value = priv->rts_threshold;
	vwrq->disabled = (vwrq->value >= 2347);
	vwrq->fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_frag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक fthr = vwrq->value;

	अगर (vwrq->disabled)
		fthr = 2346;
	अगर ((fthr < 256) || (fthr > 2346)) अणु
		वापस -EINVAL;
	पूर्ण
	fthr &= ~0x1;	/* Get an even value - is it really needed ??? */
	priv->frag_threshold = fthr;

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक aपंचांगel_get_frag(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	vwrq->value = priv->frag_threshold;
	vwrq->disabled = (vwrq->value >= 2346);
	vwrq->fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_freq(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_freq *fwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक rc = -EINPROGRESS;		/* Call commit handler */

	/* If setting by frequency, convert to a channel */
	अगर (fwrq->e == 1) अणु
		पूर्णांक f = fwrq->m / 100000;

		/* Hack to fall through... */
		fwrq->e = 0;
		fwrq->m = ieee80211_frequency_to_channel(f);
	पूर्ण
	/* Setting by channel number */
	अगर (fwrq->m < 0 || fwrq->m > 1000 || fwrq->e > 0)
		rc = -EOPNOTSUPP;
	अन्यथा अणु
		पूर्णांक channel = fwrq->m;
		अगर (aपंचांगel_validate_channel(priv, channel) == 0) अणु
			priv->channel = channel;
		पूर्ण अन्यथा अणु
			rc = -EINVAL;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक aपंचांगel_get_freq(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_freq *fwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	fwrq->m = priv->channel;
	fwrq->e = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_scan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *dwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* Note : you may have realised that, as this is a SET operation,
	 * this is privileged and thereक्रमe a normal user can't
	 * perक्रमm scanning.
	 * This is not an error, जबतक the device perक्रमm scanning,
	 * traffic करोesn't flow, so it's a perfect DoS...
	 * Jean II */

	अगर (priv->station_state == STATION_STATE_DOWN)
		वापस -EAGAIN;

	/* Timeout old surveys. */
	अगर (समय_after(jअगरfies, priv->last_survey + 20 * HZ))
		priv->site_survey_state = SITE_SURVEY_IDLE;
	priv->last_survey = jअगरfies;

	/* Initiate a scan command */
	अगर (priv->site_survey_state == SITE_SURVEY_IN_PROGRESS)
		वापस -EBUSY;

	del_समयr_sync(&priv->management_समयr);
	spin_lock_irqsave(&priv->irqlock, flags);

	priv->site_survey_state = SITE_SURVEY_IN_PROGRESS;
	priv->fast_scan = 0;
	aपंचांगel_scan(priv, 0);
	spin_unlock_irqrestore(&priv->irqlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_get_scan(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *dwrq,
			  अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक i;
	अक्षर *current_ev = extra;
	काष्ठा iw_event	iwe;

	अगर (priv->site_survey_state != SITE_SURVEY_COMPLETED)
		वापस -EAGAIN;

	क्रम (i = 0; i < priv->BSS_list_entries; i++) अणु
		iwe.cmd = SIOCGIWAP;
		iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(iwe.u.ap_addr.sa_data, priv->BSSinfo[i].BSSID, ETH_ALEN);
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_ADDR_LEN);

		iwe.u.data.length =  priv->BSSinfo[i].SSIDsize;
		अगर (iwe.u.data.length > 32)
			iwe.u.data.length = 32;
		iwe.cmd = SIOCGIWESSID;
		iwe.u.data.flags = 1;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, priv->BSSinfo[i].SSID);

		iwe.cmd = SIOCGIWMODE;
		iwe.u.mode = priv->BSSinfo[i].BSStype;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_UINT_LEN);

		iwe.cmd = SIOCGIWFREQ;
		iwe.u.freq.m = priv->BSSinfo[i].channel;
		iwe.u.freq.e = 0;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_FREQ_LEN);

		/* Add quality statistics */
		iwe.cmd = IWEVQUAL;
		iwe.u.qual.level = priv->BSSinfo[i].RSSI;
		iwe.u.qual.qual  = iwe.u.qual.level;
		/* iwe.u.qual.noise  = SOMETHING */
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_QUAL_LEN);


		iwe.cmd = SIOCGIWENCODE;
		अगर (priv->BSSinfo[i].UsingWEP)
			iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
		अन्यथा
			iwe.u.data.flags = IW_ENCODE_DISABLED;
		iwe.u.data.length = 0;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, शून्य);
	पूर्ण

	/* Length of data */
	dwrq->length = (current_ev - extra);
	dwrq->flags = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_get_range(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा iw_range *range = (काष्ठा iw_range *) extra;
	पूर्णांक k, i, j;

	dwrq->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(काष्ठा iw_range));
	range->min_nwid = 0x0000;
	range->max_nwid = 0x0000;
	range->num_channels = 0;
	क्रम (j = 0; j < ARRAY_SIZE(channel_table); j++)
		अगर (priv->reg_करोमुख्य == channel_table[j].reg_करोमुख्य) अणु
			range->num_channels = channel_table[j].max - channel_table[j].min + 1;
			अवरोध;
		पूर्ण
	अगर (range->num_channels != 0) अणु
		क्रम (k = 0, i = channel_table[j].min; i <= channel_table[j].max; i++) अणु
			range->freq[k].i = i; /* List index */

			/* Values in MHz -> * 10^5 * 10 */
			range->freq[k].m = 100000 *
			 ieee80211_channel_to_frequency(i, NL80211_BAND_2GHZ);
			range->freq[k++].e = 1;
		पूर्ण
		range->num_frequency = k;
	पूर्ण

	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 0;
	range->max_qual.updated = IW_QUAL_NOISE_INVALID;

	range->avg_qual.qual = 50;
	range->avg_qual.level = 50;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = IW_QUAL_NOISE_INVALID;

	range->sensitivity = 0;

	range->bitrate[0] =  1000000;
	range->bitrate[1] =  2000000;
	range->bitrate[2] =  5500000;
	range->bitrate[3] = 11000000;
	range->num_bitrates = 4;

	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = 4;

	range->pmp_flags = IW_POWER_ON;
	range->pmt_flags = IW_POWER_ON;
	range->pm_capa = 0;

	range->we_version_source = WIRELESS_EXT;
	range->we_version_compiled = WIRELESS_EXT;
	range->retry_capa = IW_RETRY_LIMIT ;
	range->retry_flags = IW_RETRY_LIMIT;
	range->r_समय_flags = 0;
	range->min_retry = 1;
	range->max_retry = 65535;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_set_wap(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा sockaddr *awrq,
			 अक्षर *extra)
अणु
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	पूर्णांक i;
	अटल स्थिर u8 any[] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	अटल स्थिर u8 off[] = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अचिन्हित दीर्घ flags;

	अगर (awrq->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	अगर (!स_भेद(any, awrq->sa_data, 6) ||
	    !स_भेद(off, awrq->sa_data, 6)) अणु
		del_समयr_sync(&priv->management_समयr);
		spin_lock_irqsave(&priv->irqlock, flags);
		aपंचांगel_scan(priv, 1);
		spin_unlock_irqrestore(&priv->irqlock, flags);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < priv->BSS_list_entries; i++) अणु
		अगर (स_भेद(priv->BSSinfo[i].BSSID, awrq->sa_data, 6) == 0) अणु
			अगर (!priv->wep_is_on && priv->BSSinfo[i].UsingWEP) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अगर  (priv->wep_is_on && !priv->BSSinfo[i].UsingWEP) अणु
				वापस -EINVAL;
			पूर्ण अन्यथा अणु
				del_समयr_sync(&priv->management_समयr);
				spin_lock_irqsave(&priv->irqlock, flags);
				aपंचांगel_join_bss(priv, i);
				spin_unlock_irqrestore(&priv->irqlock, flags);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aपंचांगel_config_commit(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,	/* शून्य */
			       व्योम *zwrq,			/* शून्य */
			       अक्षर *extra)			/* शून्य */
अणु
	वापस aपंचांगel_खोलो(dev);
पूर्ण

अटल स्थिर iw_handler aपंचांगel_handler[] =
अणु
	(iw_handler) aपंचांगel_config_commit,	/* SIOCSIWCOMMIT */
	(iw_handler) aपंचांगel_get_name,		/* SIOCGIWNAME */
	(iw_handler) शून्य,			/* SIOCSIWNWID */
	(iw_handler) शून्य,			/* SIOCGIWNWID */
	(iw_handler) aपंचांगel_set_freq,		/* SIOCSIWFREQ */
	(iw_handler) aपंचांगel_get_freq,		/* SIOCGIWFREQ */
	(iw_handler) aपंचांगel_set_mode,		/* SIOCSIWMODE */
	(iw_handler) aपंचांगel_get_mode,		/* SIOCGIWMODE */
	(iw_handler) शून्य,			/* SIOCSIWSENS */
	(iw_handler) शून्य,			/* SIOCGIWSENS */
	(iw_handler) शून्य,			/* SIOCSIWRANGE */
	(iw_handler) aपंचांगel_get_range,           /* SIOCGIWRANGE */
	(iw_handler) शून्य,			/* SIOCSIWPRIV */
	(iw_handler) शून्य,			/* SIOCGIWPRIV */
	(iw_handler) शून्य,			/* SIOCSIWSTATS */
	(iw_handler) शून्य,			/* SIOCGIWSTATS */
	(iw_handler) शून्य,			/* SIOCSIWSPY */
	(iw_handler) शून्य,			/* SIOCGIWSPY */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) aपंचांगel_set_wap,		/* SIOCSIWAP */
	(iw_handler) aपंचांगel_get_wap,		/* SIOCGIWAP */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* SIOCGIWAPLIST */
	(iw_handler) aपंचांगel_set_scan,		/* SIOCSIWSCAN */
	(iw_handler) aपंचांगel_get_scan,		/* SIOCGIWSCAN */
	(iw_handler) aपंचांगel_set_essid,		/* SIOCSIWESSID */
	(iw_handler) aपंचांगel_get_essid,		/* SIOCGIWESSID */
	(iw_handler) शून्य,			/* SIOCSIWNICKN */
	(iw_handler) शून्य,			/* SIOCGIWNICKN */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) aपंचांगel_set_rate,		/* SIOCSIWRATE */
	(iw_handler) aपंचांगel_get_rate,		/* SIOCGIWRATE */
	(iw_handler) aपंचांगel_set_rts,		/* SIOCSIWRTS */
	(iw_handler) aपंचांगel_get_rts,		/* SIOCGIWRTS */
	(iw_handler) aपंचांगel_set_frag,		/* SIOCSIWFRAG */
	(iw_handler) aपंचांगel_get_frag,		/* SIOCGIWFRAG */
	(iw_handler) शून्य,			/* SIOCSIWTXPOW */
	(iw_handler) शून्य,			/* SIOCGIWTXPOW */
	(iw_handler) aपंचांगel_set_retry,		/* SIOCSIWRETRY */
	(iw_handler) aपंचांगel_get_retry,		/* SIOCGIWRETRY */
	(iw_handler) aपंचांगel_set_encode,		/* SIOCSIWENCODE */
	(iw_handler) aपंचांगel_get_encode,		/* SIOCGIWENCODE */
	(iw_handler) aपंचांगel_set_घातer,		/* SIOCSIWPOWER */
	(iw_handler) aपंचांगel_get_घातer,		/* SIOCGIWPOWER */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* SIOCSIWGENIE */
	(iw_handler) शून्य,			/* SIOCGIWGENIE */
	(iw_handler) aपंचांगel_set_auth,		/* SIOCSIWAUTH */
	(iw_handler) aपंचांगel_get_auth,		/* SIOCGIWAUTH */
	(iw_handler) aपंचांगel_set_encodeext,	/* SIOCSIWENCODEEXT */
	(iw_handler) aपंचांगel_get_encodeext,	/* SIOCGIWENCODEEXT */
	(iw_handler) शून्य,			/* SIOCSIWPMKSA */
पूर्ण;

अटल स्थिर iw_handler aपंचांगel_निजी_handler[] =
अणु
	शून्य,				/* SIOCIWFIRSTPRIV */
पूर्ण;

काष्ठा aपंचांगel_priv_ioctl अणु
	अक्षर id[32];
	अचिन्हित अक्षर __user *data;
	अचिन्हित लघु len;
पूर्ण;

#घोषणा ATMELFWL	SIOCIWFIRSTPRIV
#घोषणा ATMELIDIFC	ATMELFWL + 1
#घोषणा ATMELRD		ATMELFWL + 2
#घोषणा ATMELMAGIC 0x51807
#घोषणा REGDOMAINSZ 20

अटल स्थिर काष्ठा iw_priv_args aपंचांगel_निजी_args[] = अणु
	अणु
		.cmd = ATMELFWL,
		.set_args = IW_PRIV_TYPE_BYTE
				| IW_PRIV_SIZE_FIXED
				| माप(काष्ठा aपंचांगel_priv_ioctl),
		.get_args = IW_PRIV_TYPE_NONE,
		.name = "atmelfwl"
	पूर्ण, अणु
		.cmd = ATMELIDIFC,
		.set_args = IW_PRIV_TYPE_NONE,
		.get_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
		.name = "atmelidifc"
	पूर्ण, अणु
		.cmd = ATMELRD,
		.set_args = IW_PRIV_TYPE_CHAR | REGDOMAINSZ,
		.get_args = IW_PRIV_TYPE_NONE,
		.name = "regdomain"
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def aपंचांगel_handler_def = अणु
	.num_standard	= ARRAY_SIZE(aपंचांगel_handler),
	.num_निजी	= ARRAY_SIZE(aपंचांगel_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(aपंचांगel_निजी_args),
	.standard	= (iw_handler *) aपंचांगel_handler,
	.निजी	= (iw_handler *) aपंचांगel_निजी_handler,
	.निजी_args	= (काष्ठा iw_priv_args *) aपंचांगel_निजी_args,
	.get_wireless_stats = aपंचांगel_get_wireless_stats
पूर्ण;

अटल पूर्णांक aपंचांगel_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	काष्ठा aपंचांगel_priv_ioctl com;
	काष्ठा iwreq *wrq = (काष्ठा iwreq *) rq;
	अचिन्हित अक्षर *new_firmware;
	अक्षर करोमुख्य[REGDOMAINSZ + 1];

	चयन (cmd) अणु
	हाल ATMELIDIFC:
		wrq->u.param.value = ATMELMAGIC;
		अवरोध;

	हाल ATMELFWL:
		अगर (copy_from_user(&com, rq->अगरr_data, माप(com))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!capable(CAP_NET_ADMIN)) अणु
			rc = -EPERM;
			अवरोध;
		पूर्ण

		new_firmware = memdup_user(com.data, com.len);
		अगर (IS_ERR(new_firmware)) अणु
			rc = PTR_ERR(new_firmware);
			अवरोध;
		पूर्ण

		kमुक्त(priv->firmware);

		priv->firmware = new_firmware;
		priv->firmware_length = com.len;
		म_नकलन(priv->firmware_id, com.id, 31);
		priv->firmware_id[31] = '\0';
		अवरोध;

	हाल ATMELRD:
		अगर (copy_from_user(करोमुख्य, rq->अगरr_data, REGDOMAINSZ)) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!capable(CAP_NET_ADMIN)) अणु
			rc = -EPERM;
			अवरोध;
		पूर्ण

		करोमुख्य[REGDOMAINSZ] = 0;
		rc = -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(channel_table); i++) अणु
			अगर (!strहालcmp(channel_table[i].name, करोमुख्य)) अणु
				priv->config_reg_करोमुख्य = channel_table[i].reg_करोमुख्य;
				rc = 0;
			पूर्ण
		पूर्ण

		अगर (rc == 0 &&  priv->station_state != STATION_STATE_DOWN)
			rc = aपंचांगel_खोलो(dev);
		अवरोध;

	शेष:
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

काष्ठा auth_body अणु
	__le16 alg;
	__le16 trans_seq;
	__le16 status;
	u8 el_id;
	u8 chall_text_len;
	u8 chall_text[253];
पूर्ण;

अटल व्योम aपंचांगel_enter_state(काष्ठा aपंचांगel_निजी *priv, पूर्णांक new_state)
अणु
	पूर्णांक old_state = priv->station_state;

	अगर (new_state == old_state)
		वापस;

	priv->station_state = new_state;

	अगर (new_state == STATION_STATE_READY) अणु
		netअगर_start_queue(priv->dev);
		netअगर_carrier_on(priv->dev);
	पूर्ण

	अगर (old_state == STATION_STATE_READY) अणु
		netअगर_carrier_off(priv->dev);
		अगर (netअगर_running(priv->dev))
			netअगर_stop_queue(priv->dev);
		priv->last_beacon_बारtamp = 0;
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_scan(काष्ठा aपंचांगel_निजी *priv, पूर्णांक specअगरic_ssid)
अणु
	काष्ठा अणु
		u8 BSSID[ETH_ALEN];
		u8 SSID[MAX_SSID_LENGTH];
		u8 scan_type;
		u8 channel;
		__le16 BSS_type;
		__le16 min_channel_समय;
		__le16 max_channel_समय;
		u8 options;
		u8 SSID_size;
	पूर्ण cmd;

	eth_broadcast_addr(cmd.BSSID);

	अगर (priv->fast_scan) अणु
		cmd.SSID_size = priv->SSID_size;
		स_नकल(cmd.SSID, priv->SSID, priv->SSID_size);
		cmd.min_channel_समय = cpu_to_le16(10);
		cmd.max_channel_समय = cpu_to_le16(50);
	पूर्ण अन्यथा अणु
		priv->BSS_list_entries = 0;
		cmd.SSID_size = 0;
		cmd.min_channel_समय = cpu_to_le16(10);
		cmd.max_channel_समय = cpu_to_le16(120);
	पूर्ण

	cmd.options = 0;

	अगर (!specअगरic_ssid)
		cmd.options |= SCAN_OPTIONS_SITE_SURVEY;

	cmd.channel = (priv->channel & 0x7f);
	cmd.scan_type = SCAN_TYPE_ACTIVE;
	cmd.BSS_type = cpu_to_le16(priv->operating_mode == IW_MODE_ADHOC ?
		BSS_TYPE_AD_HOC : BSS_TYPE_INFRASTRUCTURE);

	aपंचांगel_send_command(priv, CMD_Scan, &cmd, माप(cmd));

	/* This must come after all hardware access to aव्योम being messed up
	   by stuff happening in पूर्णांकerrupt context after we leave STATE_DOWN */
	aपंचांगel_enter_state(priv, STATION_STATE_SCANNING);
पूर्ण

अटल व्योम join(काष्ठा aपंचांगel_निजी *priv, पूर्णांक type)
अणु
	काष्ठा अणु
		u8 BSSID[6];
		u8 SSID[MAX_SSID_LENGTH];
		u8 BSS_type; /* this is a लघु in a scan command - weird */
		u8 channel;
		__le16 समयout;
		u8 SSID_size;
		u8 reserved;
	पूर्ण cmd;

	cmd.SSID_size = priv->SSID_size;
	स_नकल(cmd.SSID, priv->SSID, priv->SSID_size);
	स_नकल(cmd.BSSID, priv->CurrentBSSID, ETH_ALEN);
	cmd.channel = (priv->channel & 0x7f);
	cmd.BSS_type = type;
	cmd.समयout = cpu_to_le16(2000);

	aपंचांगel_send_command(priv, CMD_Join, &cmd, माप(cmd));
पूर्ण

अटल व्योम start(काष्ठा aपंचांगel_निजी *priv, पूर्णांक type)
अणु
	काष्ठा अणु
		u8 BSSID[6];
		u8 SSID[MAX_SSID_LENGTH];
		u8 BSS_type;
		u8 channel;
		u8 SSID_size;
		u8 reserved[3];
	पूर्ण cmd;

	cmd.SSID_size = priv->SSID_size;
	स_नकल(cmd.SSID, priv->SSID, priv->SSID_size);
	स_नकल(cmd.BSSID, priv->BSSID, ETH_ALEN);
	cmd.BSS_type = type;
	cmd.channel = (priv->channel & 0x7f);

	aपंचांगel_send_command(priv, CMD_Start, &cmd, माप(cmd));
पूर्ण

अटल व्योम handle_beacon_probe(काष्ठा aपंचांगel_निजी *priv, u16 capability,
				u8 channel)
अणु
	पूर्णांक rejoin = 0;
	पूर्णांक new = capability & WLAN_CAPABILITY_SHORT_PREAMBLE ?
		SHORT_PREAMBLE : LONG_PREAMBLE;

	अगर (priv->preamble != new) अणु
		priv->preamble = new;
		rejoin = 1;
		aपंचांगel_set_mib8(priv, Local_Mib_Type, LOCAL_MIB_PREAMBLE_TYPE, new);
	पूर्ण

	अगर (priv->channel != channel) अणु
		priv->channel = channel;
		rejoin = 1;
		aपंचांगel_set_mib8(priv, Phy_Mib_Type, PHY_MIB_CHANNEL_POS, channel);
	पूर्ण

	अगर (rejoin) अणु
		priv->station_is_associated = 0;
		aपंचांगel_enter_state(priv, STATION_STATE_JOINNING);

		अगर (priv->operating_mode == IW_MODE_INFRA)
			join(priv, BSS_TYPE_INFRASTRUCTURE);
		अन्यथा
			join(priv, BSS_TYPE_AD_HOC);
	पूर्ण
पूर्ण

अटल व्योम send_authentication_request(काष्ठा aपंचांगel_निजी *priv, u16 प्रणाली,
					u8 *challenge, पूर्णांक challenge_len)
अणु
	काष्ठा ieee80211_hdr header;
	काष्ठा auth_body auth;

	header.frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_AUTH);
	header.duration_id = cpu_to_le16(0x8000);
	header.seq_ctrl = 0;
	स_नकल(header.addr1, priv->CurrentBSSID, ETH_ALEN);
	स_नकल(header.addr2, priv->dev->dev_addr, ETH_ALEN);
	स_नकल(header.addr3, priv->CurrentBSSID, ETH_ALEN);

	अगर (priv->wep_is_on && priv->CurrentAuthentTransactionSeqNum != 1)
		/* no WEP क्रम authentication frames with TrSeqNo 1 */
		header.frame_control |=  cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	auth.alg = cpu_to_le16(प्रणाली);

	auth.status = 0;
	auth.trans_seq = cpu_to_le16(priv->CurrentAuthentTransactionSeqNum);
	priv->ExpectedAuthentTransactionSeqNum = priv->CurrentAuthentTransactionSeqNum+1;
	priv->CurrentAuthentTransactionSeqNum += 2;

	अगर (challenge_len != 0)	अणु
		auth.el_id = 16; /* challenge_text */
		auth.chall_text_len = challenge_len;
		स_नकल(auth.chall_text, challenge, challenge_len);
		aपंचांगel_transmit_management_frame(priv, &header, (u8 *)&auth, 8 + challenge_len);
	पूर्ण अन्यथा अणु
		aपंचांगel_transmit_management_frame(priv, &header, (u8 *)&auth, 6);
	पूर्ण
पूर्ण

अटल व्योम send_association_request(काष्ठा aपंचांगel_निजी *priv, पूर्णांक is_reassoc)
अणु
	u8 *ssid_el_p;
	पूर्णांक bodysize;
	काष्ठा ieee80211_hdr header;
	काष्ठा ass_req_क्रमmat अणु
		__le16 capability;
		__le16 listen_पूर्णांकerval;
		u8 ap[ETH_ALEN]; /* nothing after here directly accessible */
		u8 ssid_el_id;
		u8 ssid_len;
		u8 ssid[MAX_SSID_LENGTH];
		u8 sup_rates_el_id;
		u8 sup_rates_len;
		u8 rates[4];
	पूर्ण body;

	header.frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
		(is_reassoc ? IEEE80211_STYPE_REASSOC_REQ : IEEE80211_STYPE_ASSOC_REQ));
	header.duration_id = cpu_to_le16(0x8000);
	header.seq_ctrl = 0;

	स_नकल(header.addr1, priv->CurrentBSSID, ETH_ALEN);
	स_नकल(header.addr2, priv->dev->dev_addr, ETH_ALEN);
	स_नकल(header.addr3, priv->CurrentBSSID, ETH_ALEN);

	body.capability = cpu_to_le16(WLAN_CAPABILITY_ESS);
	अगर (priv->wep_is_on)
		body.capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);
	अगर (priv->preamble == SHORT_PREAMBLE)
		body.capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);

	body.listen_पूर्णांकerval = cpu_to_le16(priv->listen_पूर्णांकerval * priv->beacon_period);

	/* current AP address - only in reassoc frame */
	अगर (is_reassoc) अणु
		स_नकल(body.ap, priv->CurrentBSSID, ETH_ALEN);
		ssid_el_p = &body.ssid_el_id;
		bodysize = 18 + priv->SSID_size;
	पूर्ण अन्यथा अणु
		ssid_el_p = &body.ap[0];
		bodysize = 12 + priv->SSID_size;
	पूर्ण

	ssid_el_p[0] = WLAN_EID_SSID;
	ssid_el_p[1] = priv->SSID_size;
	स_नकल(ssid_el_p + 2, priv->SSID, priv->SSID_size);
	ssid_el_p[2 + priv->SSID_size] = WLAN_EID_SUPP_RATES;
	ssid_el_p[3 + priv->SSID_size] = 4; /* len of supported rates */
	स_नकल(ssid_el_p + 4 + priv->SSID_size, aपंचांगel_basic_rates, 4);

	aपंचांगel_transmit_management_frame(priv, &header, (व्योम *)&body, bodysize);
पूर्ण

अटल पूर्णांक is_frame_from_current_bss(काष्ठा aपंचांगel_निजी *priv,
				     काष्ठा ieee80211_hdr *header)
अणु
	अगर (le16_to_cpu(header->frame_control) & IEEE80211_FCTL_FROMDS)
		वापस स_भेद(header->addr3, priv->CurrentBSSID, 6) == 0;
	अन्यथा
		वापस स_भेद(header->addr2, priv->CurrentBSSID, 6) == 0;
पूर्ण

अटल पूर्णांक retrieve_bss(काष्ठा aपंचांगel_निजी *priv)
अणु
	पूर्णांक i;
	पूर्णांक max_rssi = -128;
	पूर्णांक max_index = -1;

	अगर (priv->BSS_list_entries == 0)
		वापस -1;

	अगर (priv->connect_to_any_BSS) अणु
		/* Select a BSS with the max-RSSI but of the same type and of
		   the same WEP mode and that it is not marked as 'bad' (i.e.
		   we had previously failed to connect to this BSS with the
		   settings that we currently use) */
		priv->current_BSS = 0;
		क्रम (i = 0; i < priv->BSS_list_entries; i++) अणु
			अगर (priv->operating_mode == priv->BSSinfo[i].BSStype &&
			    ((!priv->wep_is_on && !priv->BSSinfo[i].UsingWEP) ||
			     (priv->wep_is_on && priv->BSSinfo[i].UsingWEP)) &&
			    !(priv->BSSinfo[i].channel & 0x80)) अणु
				max_rssi = priv->BSSinfo[i].RSSI;
				priv->current_BSS = max_index = i;
			पूर्ण
		पूर्ण
		वापस max_index;
	पूर्ण

	क्रम (i = 0; i < priv->BSS_list_entries; i++) अणु
		अगर (priv->SSID_size == priv->BSSinfo[i].SSIDsize &&
		    स_भेद(priv->SSID, priv->BSSinfo[i].SSID, priv->SSID_size) == 0 &&
		    priv->operating_mode == priv->BSSinfo[i].BSStype &&
		    aपंचांगel_validate_channel(priv, priv->BSSinfo[i].channel) == 0) अणु
			अगर (priv->BSSinfo[i].RSSI >= max_rssi) अणु
				max_rssi = priv->BSSinfo[i].RSSI;
				max_index = i;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस max_index;
पूर्ण

अटल व्योम store_bss_info(काष्ठा aपंचांगel_निजी *priv,
			   काष्ठा ieee80211_hdr *header, u16 capability,
			   u16 beacon_period, u8 channel, u8 rssi, u8 ssid_len,
			   u8 *ssid, पूर्णांक is_beacon)
अणु
	u8 *bss = capability & WLAN_CAPABILITY_ESS ? header->addr2 : header->addr3;
	पूर्णांक i, index;

	क्रम (index = -1, i = 0; i < priv->BSS_list_entries; i++)
		अगर (स_भेद(bss, priv->BSSinfo[i].BSSID, ETH_ALEN) == 0)
			index = i;

	/* If we process a probe and an entry from this BSS exists
	   we will update the BSS entry with the info from this BSS.
	   If we process a beacon we will only update RSSI */

	अगर (index == -1) अणु
		अगर (priv->BSS_list_entries == MAX_BSS_ENTRIES)
			वापस;
		index = priv->BSS_list_entries++;
		स_नकल(priv->BSSinfo[index].BSSID, bss, ETH_ALEN);
		priv->BSSinfo[index].RSSI = rssi;
	पूर्ण अन्यथा अणु
		अगर (rssi > priv->BSSinfo[index].RSSI)
			priv->BSSinfo[index].RSSI = rssi;
		अगर (is_beacon)
			वापस;
	पूर्ण

	priv->BSSinfo[index].channel = channel;
	priv->BSSinfo[index].beacon_period = beacon_period;
	priv->BSSinfo[index].UsingWEP = capability & WLAN_CAPABILITY_PRIVACY;
	स_नकल(priv->BSSinfo[index].SSID, ssid, ssid_len);
	priv->BSSinfo[index].SSIDsize = ssid_len;

	अगर (capability & WLAN_CAPABILITY_IBSS)
		priv->BSSinfo[index].BSStype = IW_MODE_ADHOC;
	अन्यथा अगर (capability & WLAN_CAPABILITY_ESS)
		priv->BSSinfo[index].BSStype = IW_MODE_INFRA;

	priv->BSSinfo[index].preamble = capability & WLAN_CAPABILITY_SHORT_PREAMBLE ?
		SHORT_PREAMBLE : LONG_PREAMBLE;
पूर्ण

अटल व्योम authenticate(काष्ठा aपंचांगel_निजी *priv, u16 frame_len)
अणु
	काष्ठा auth_body *auth = (काष्ठा auth_body *)priv->rx_buf;
	u16 status = le16_to_cpu(auth->status);
	u16 trans_seq_no = le16_to_cpu(auth->trans_seq);
	u16 प्रणाली = le16_to_cpu(auth->alg);

	अगर (status == WLAN_STATUS_SUCCESS && !priv->wep_is_on) अणु
		/* no WEP */
		अगर (priv->station_was_associated) अणु
			aपंचांगel_enter_state(priv, STATION_STATE_REASSOCIATING);
			send_association_request(priv, 1);
			वापस;
		पूर्ण अन्यथा अणु
			aपंचांगel_enter_state(priv, STATION_STATE_ASSOCIATING);
			send_association_request(priv, 0);
			वापस;
		पूर्ण
	पूर्ण

	अगर (status == WLAN_STATUS_SUCCESS && priv->wep_is_on) अणु
		पूर्णांक should_associate = 0;
		/* WEP */
		अगर (trans_seq_no != priv->ExpectedAuthentTransactionSeqNum)
			वापस;

		अगर (प्रणाली == WLAN_AUTH_OPEN) अणु
			अगर (trans_seq_no == 0x0002) अणु
				should_associate = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (प्रणाली == WLAN_AUTH_SHARED_KEY) अणु
			अगर (trans_seq_no == 0x0002 &&
			    auth->el_id == WLAN_EID_CHALLENGE) अणु
				send_authentication_request(priv, प्रणाली, auth->chall_text, auth->chall_text_len);
				वापस;
			पूर्ण अन्यथा अगर (trans_seq_no == 0x0004) अणु
				should_associate = 1;
			पूर्ण
		पूर्ण

		अगर (should_associate) अणु
			अगर (priv->station_was_associated) अणु
				aपंचांगel_enter_state(priv, STATION_STATE_REASSOCIATING);
				send_association_request(priv, 1);
				वापस;
			पूर्ण अन्यथा अणु
				aपंचांगel_enter_state(priv, STATION_STATE_ASSOCIATING);
				send_association_request(priv, 0);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (status == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG) अणु
		/* Flip back and क्रमth between WEP auth modes until the max
		 * authentication tries has been exceeded.
		 */
		अगर (प्रणाली == WLAN_AUTH_OPEN) अणु
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 1;
			send_authentication_request(priv, WLAN_AUTH_SHARED_KEY, शून्य, 0);
			वापस;
		पूर्ण अन्यथा अगर (प्रणाली == WLAN_AUTH_SHARED_KEY
			   && priv->wep_is_on) अणु
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 0;
			send_authentication_request(priv, WLAN_AUTH_OPEN, शून्य, 0);
			वापस;
		पूर्ण अन्यथा अगर (priv->connect_to_any_BSS) अणु
			पूर्णांक bss_index;

			priv->BSSinfo[(पूर्णांक)(priv->current_BSS)].channel |= 0x80;

			अगर ((bss_index  = retrieve_bss(priv)) != -1) अणु
				aपंचांगel_join_bss(priv, bss_index);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->AuthenticationRequestRetryCnt = 0;
	aपंचांगel_enter_state(priv,  STATION_STATE_MGMT_ERROR);
	priv->station_is_associated = 0;
पूर्ण

अटल व्योम associate(काष्ठा aपंचांगel_निजी *priv, u16 frame_len, u16 subtype)
अणु
	काष्ठा ass_resp_क्रमmat अणु
		__le16 capability;
		__le16 status;
		__le16 ass_id;
		u8 el_id;
		u8 length;
		u8 rates[4];
	पूर्ण *ass_resp = (काष्ठा ass_resp_क्रमmat *)priv->rx_buf;

	u16 status = le16_to_cpu(ass_resp->status);
	u16 ass_id = le16_to_cpu(ass_resp->ass_id);
	u16 rates_len = ass_resp->length > 4 ? 4 : ass_resp->length;

	जोड़ iwreq_data wrqu;

	अगर (frame_len < 8 + rates_len)
		वापस;

	अगर (status == WLAN_STATUS_SUCCESS) अणु
		अगर (subtype == IEEE80211_STYPE_ASSOC_RESP)
			priv->AssociationRequestRetryCnt = 0;
		अन्यथा
			priv->ReAssociationRequestRetryCnt = 0;

		aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type,
				MAC_MGMT_MIB_STATION_ID_POS, ass_id & 0x3fff);
		aपंचांगel_set_mib(priv, Phy_Mib_Type,
			      PHY_MIB_RATE_SET_POS, ass_resp->rates, rates_len);
		अगर (priv->घातer_mode == 0) अणु
			priv->listen_पूर्णांकerval = 1;
			aपंचांगel_set_mib8(priv, Mac_Mgmt_Mib_Type,
				       MAC_MGMT_MIB_PS_MODE_POS, ACTIVE_MODE);
			aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type,
					MAC_MGMT_MIB_LISTEN_INTERVAL_POS, 1);
		पूर्ण अन्यथा अणु
			priv->listen_पूर्णांकerval = 2;
			aपंचांगel_set_mib8(priv, Mac_Mgmt_Mib_Type,
				       MAC_MGMT_MIB_PS_MODE_POS,  PS_MODE);
			aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type,
					MAC_MGMT_MIB_LISTEN_INTERVAL_POS, 2);
		पूर्ण

		priv->station_is_associated = 1;
		priv->station_was_associated = 1;
		aपंचांगel_enter_state(priv, STATION_STATE_READY);

		/* Send association event to userspace */
		wrqu.data.length = 0;
		wrqu.data.flags = 0;
		स_नकल(wrqu.ap_addr.sa_data, priv->CurrentBSSID, ETH_ALEN);
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, शून्य);

		वापस;
	पूर्ण

	अगर (subtype == IEEE80211_STYPE_ASSOC_RESP &&
	    status != WLAN_STATUS_ASSOC_DENIED_RATES &&
	    status != WLAN_STATUS_CAPS_UNSUPPORTED &&
	    priv->AssociationRequestRetryCnt < MAX_ASSOCIATION_RETRIES) अणु
		mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
		priv->AssociationRequestRetryCnt++;
		send_association_request(priv, 0);
		वापस;
	पूर्ण

	अगर (subtype == IEEE80211_STYPE_REASSOC_RESP &&
	    status != WLAN_STATUS_ASSOC_DENIED_RATES &&
	    status != WLAN_STATUS_CAPS_UNSUPPORTED &&
	    priv->ReAssociationRequestRetryCnt < MAX_ASSOCIATION_RETRIES) अणु
		mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
		priv->ReAssociationRequestRetryCnt++;
		send_association_request(priv, 1);
		वापस;
	पूर्ण

	aपंचांगel_enter_state(priv,  STATION_STATE_MGMT_ERROR);
	priv->station_is_associated = 0;

	अगर (priv->connect_to_any_BSS) अणु
		पूर्णांक bss_index;
		priv->BSSinfo[(पूर्णांक)(priv->current_BSS)].channel |= 0x80;

		अगर ((bss_index = retrieve_bss(priv)) != -1)
			aपंचांगel_join_bss(priv, bss_index);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_join_bss(काष्ठा aपंचांगel_निजी *priv, पूर्णांक bss_index)
अणु
	काष्ठा bss_info *bss =  &priv->BSSinfo[bss_index];

	स_नकल(priv->CurrentBSSID, bss->BSSID, ETH_ALEN);
	स_नकल(priv->SSID, bss->SSID, priv->SSID_size = bss->SSIDsize);

	/* The WPA stuff cares about the current AP address */
	अगर (priv->use_wpa)
		build_wpa_mib(priv);

	/* When चयनing to AdHoc turn OFF Power Save अगर needed */

	अगर (bss->BSStype == IW_MODE_ADHOC &&
	    priv->operating_mode != IW_MODE_ADHOC &&
	    priv->घातer_mode) अणु
		priv->घातer_mode = 0;
		priv->listen_पूर्णांकerval = 1;
		aपंचांगel_set_mib8(priv, Mac_Mgmt_Mib_Type,
			       MAC_MGMT_MIB_PS_MODE_POS,  ACTIVE_MODE);
		aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type,
				MAC_MGMT_MIB_LISTEN_INTERVAL_POS, 1);
	पूर्ण

	priv->operating_mode = bss->BSStype;
	priv->channel = bss->channel & 0x7f;
	priv->beacon_period = bss->beacon_period;

	अगर (priv->preamble != bss->preamble) अणु
		priv->preamble = bss->preamble;
		aपंचांगel_set_mib8(priv, Local_Mib_Type,
			       LOCAL_MIB_PREAMBLE_TYPE, bss->preamble);
	पूर्ण

	अगर (!priv->wep_is_on && bss->UsingWEP) अणु
		aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
		priv->station_is_associated = 0;
		वापस;
	पूर्ण

	अगर (priv->wep_is_on && !bss->UsingWEP) अणु
		aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
		priv->station_is_associated = 0;
		वापस;
	पूर्ण

	aपंचांगel_enter_state(priv, STATION_STATE_JOINNING);

	अगर (priv->operating_mode == IW_MODE_INFRA)
		join(priv, BSS_TYPE_INFRASTRUCTURE);
	अन्यथा
		join(priv, BSS_TYPE_AD_HOC);
पूर्ण

अटल व्योम restart_search(काष्ठा aपंचांगel_निजी *priv)
अणु
	पूर्णांक bss_index;

	अगर (!priv->connect_to_any_BSS) अणु
		aपंचांगel_scan(priv, 1);
	पूर्ण अन्यथा अणु
		priv->BSSinfo[(पूर्णांक)(priv->current_BSS)].channel |= 0x80;

		अगर ((bss_index = retrieve_bss(priv)) != -1)
			aपंचांगel_join_bss(priv, bss_index);
		अन्यथा
			aपंचांगel_scan(priv, 0);
	पूर्ण
पूर्ण

अटल व्योम smooth_rssi(काष्ठा aपंचांगel_निजी *priv, u8 rssi)
अणु
	u8 old = priv->wstats.qual.level;
	u8 max_rssi = 42; /* 502-rmfd-revd max by experiment, शेष क्रम now */

	चयन (priv->firmware_type) अणु
	हाल ATMEL_FW_TYPE_502E:
		max_rssi = 63; /* 502-rmfd-reve max by experiment */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rssi = rssi * 100 / max_rssi;
	अगर ((rssi + old) % 2)
		priv->wstats.qual.level = (rssi + old) / 2 + 1;
	अन्यथा
		priv->wstats.qual.level = (rssi + old) / 2;
	priv->wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
	priv->wstats.qual.updated &= ~IW_QUAL_LEVEL_INVALID;
पूर्ण

अटल व्योम aपंचांगel_smooth_qual(काष्ठा aपंचांगel_निजी *priv)
अणु
	अचिन्हित दीर्घ समय_dअगरf = (jअगरfies - priv->last_qual) / HZ;
	जबतक (समय_dअगरf--) अणु
		priv->last_qual += HZ;
		priv->wstats.qual.qual = priv->wstats.qual.qual / 2;
		priv->wstats.qual.qual +=
			priv->beacons_this_sec * priv->beacon_period * (priv->wstats.qual.level + 100) / 4000;
		priv->beacons_this_sec = 0;
	पूर्ण
	priv->wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
	priv->wstats.qual.updated &= ~IW_QUAL_QUAL_INVALID;
पूर्ण

/* deals with incoming management frames. */
अटल व्योम aपंचांगel_management_frame(काष्ठा aपंचांगel_निजी *priv,
				   काष्ठा ieee80211_hdr *header,
				   u16 frame_len, u8 rssi)
अणु
	u16 subtype;

	subtype = le16_to_cpu(header->frame_control) & IEEE80211_FCTL_STYPE;
	चयन (subtype) अणु
	हाल IEEE80211_STYPE_BEACON:
	हाल IEEE80211_STYPE_PROBE_RESP:

		/* beacon frame has multiple variable-length fields -
		   never let an engineer loose with a data काष्ठाure design. */
		अणु
			काष्ठा beacon_क्रमmat अणु
				__le64 बारtamp;
				__le16 पूर्णांकerval;
				__le16 capability;
				u8 ssid_el_id;
				u8 ssid_length;
				/* ssid here */
				u8 rates_el_id;
				u8 rates_length;
				/* rates here */
				u8 ds_el_id;
				u8 ds_length;
				/* ds here */
			पूर्ण *beacon = (काष्ठा beacon_क्रमmat *)priv->rx_buf;

			u8 channel, rates_length, ssid_length;
			u64 बारtamp = le64_to_cpu(beacon->बारtamp);
			u16 beacon_पूर्णांकerval = le16_to_cpu(beacon->पूर्णांकerval);
			u16 capability = le16_to_cpu(beacon->capability);
			u8 *beaconp = priv->rx_buf;
			ssid_length = beacon->ssid_length;
			/* this blows chunks. */
			अगर (frame_len < 14 || frame_len < ssid_length + 15)
				वापस;
			rates_length = beaconp[beacon->ssid_length + 15];
			अगर (frame_len < ssid_length + rates_length + 18)
				वापस;
			अगर (ssid_length >  MAX_SSID_LENGTH)
				वापस;
			channel = beaconp[ssid_length + rates_length + 18];

			अगर (priv->station_state == STATION_STATE_READY) अणु
				smooth_rssi(priv, rssi);
				अगर (is_frame_from_current_bss(priv, header)) अणु
					priv->beacons_this_sec++;
					aपंचांगel_smooth_qual(priv);
					अगर (priv->last_beacon_बारtamp) अणु
						/* Note truncate this to 32 bits - kernel can't भागide a दीर्घ दीर्घ */
						u32 beacon_delay = बारtamp - priv->last_beacon_बारtamp;
						पूर्णांक beacons = beacon_delay / (beacon_पूर्णांकerval * 1000);
						अगर (beacons > 1)
							priv->wstats.miss.beacon += beacons - 1;
					पूर्ण
					priv->last_beacon_बारtamp = बारtamp;
					handle_beacon_probe(priv, capability, channel);
				पूर्ण
			पूर्ण

			अगर (priv->station_state == STATION_STATE_SCANNING)
				store_bss_info(priv, header, capability,
					       beacon_पूर्णांकerval, channel, rssi,
					       ssid_length,
					       &beacon->rates_el_id,
					       subtype == IEEE80211_STYPE_BEACON);
		पूर्ण
		अवरोध;

	हाल IEEE80211_STYPE_AUTH:

		अगर (priv->station_state == STATION_STATE_AUTHENTICATING)
			authenticate(priv, frame_len);

		अवरोध;

	हाल IEEE80211_STYPE_ASSOC_RESP:
	हाल IEEE80211_STYPE_REASSOC_RESP:

		अगर (priv->station_state == STATION_STATE_ASSOCIATING ||
		    priv->station_state == STATION_STATE_REASSOCIATING)
			associate(priv, frame_len, subtype);

		अवरोध;

	हाल IEEE80211_STYPE_DISASSOC:
		अगर (priv->station_is_associated &&
		    priv->operating_mode == IW_MODE_INFRA &&
		    is_frame_from_current_bss(priv, header)) अणु
			priv->station_was_associated = 0;
			priv->station_is_associated = 0;

			aपंचांगel_enter_state(priv, STATION_STATE_JOINNING);
			join(priv, BSS_TYPE_INFRASTRUCTURE);
		पूर्ण

		अवरोध;

	हाल IEEE80211_STYPE_DEAUTH:
		अगर (priv->operating_mode == IW_MODE_INFRA &&
		    is_frame_from_current_bss(priv, header)) अणु
			priv->station_was_associated = 0;

			aपंचांगel_enter_state(priv, STATION_STATE_JOINNING);
			join(priv, BSS_TYPE_INFRASTRUCTURE);
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

/* run when समयr expires */
अटल व्योम aपंचांगel_management_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा aपंचांगel_निजी *priv = from_समयr(priv, t, management_समयr);
	अचिन्हित दीर्घ flags;

	/* Check अगर the card has been yanked. */
	अगर (priv->card && priv->present_callback &&
		!(*priv->present_callback)(priv->card))
		वापस;

	spin_lock_irqsave(&priv->irqlock, flags);

	चयन (priv->station_state) अणु

	हाल STATION_STATE_AUTHENTICATING:
		अगर (priv->AuthenticationRequestRetryCnt >= MAX_AUTHENTICATION_RETRIES) अणु
			aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->AuthenticationRequestRetryCnt = 0;
			restart_search(priv);
		पूर्ण अन्यथा अणु
			पूर्णांक auth = WLAN_AUTH_OPEN;
			priv->AuthenticationRequestRetryCnt++;
			priv->CurrentAuthentTransactionSeqNum = 0x0001;
			mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
			अगर (priv->wep_is_on && priv->exclude_unencrypted)
				auth = WLAN_AUTH_SHARED_KEY;
			send_authentication_request(priv, auth, शून्य, 0);
	  पूर्ण
	  अवरोध;

	हाल STATION_STATE_ASSOCIATING:
		अगर (priv->AssociationRequestRetryCnt == MAX_ASSOCIATION_RETRIES) अणु
			aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->AssociationRequestRetryCnt = 0;
			restart_search(priv);
		पूर्ण अन्यथा अणु
			priv->AssociationRequestRetryCnt++;
			mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
			send_association_request(priv, 0);
		पूर्ण
	  अवरोध;

	हाल STATION_STATE_REASSOCIATING:
		अगर (priv->ReAssociationRequestRetryCnt == MAX_ASSOCIATION_RETRIES) अणु
			aपंचांगel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->ReAssociationRequestRetryCnt = 0;
			restart_search(priv);
		पूर्ण अन्यथा अणु
			priv->ReAssociationRequestRetryCnt++;
			mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
			send_association_request(priv, 1);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&priv->irqlock, flags);
पूर्ण

अटल व्योम aपंचांगel_command_irq(काष्ठा aपंचांगel_निजी *priv)
अणु
	u8 status = aपंचांगel_rmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_STATUS_OFFSET));
	u8 command = aपंचांगel_rmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_COMMAND_OFFSET));
	पूर्णांक fast_scan;
	जोड़ iwreq_data wrqu;

	अगर (status == CMD_STATUS_IDLE ||
	    status == CMD_STATUS_IN_PROGRESS)
		वापस;

	चयन (command) अणु
	हाल CMD_Start:
		अगर (status == CMD_STATUS_COMPLETE) अणु
			priv->station_was_associated = priv->station_is_associated;
			aपंचांगel_get_mib(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_CUR_BSSID_POS,
				      (u8 *)priv->CurrentBSSID, 6);
			aपंचांगel_enter_state(priv, STATION_STATE_READY);
		पूर्ण
		अवरोध;

	हाल CMD_Scan:
		fast_scan = priv->fast_scan;
		priv->fast_scan = 0;

		अगर (status != CMD_STATUS_COMPLETE) अणु
			aपंचांगel_scan(priv, 1);
		पूर्ण अन्यथा अणु
			पूर्णांक bss_index = retrieve_bss(priv);
			पूर्णांक notअगरy_scan_complete = 1;
			अगर (bss_index != -1) अणु
				aपंचांगel_join_bss(priv, bss_index);
			पूर्ण अन्यथा अगर (priv->operating_mode == IW_MODE_ADHOC &&
				   priv->SSID_size != 0) अणु
				start(priv, BSS_TYPE_AD_HOC);
			पूर्ण अन्यथा अणु
				priv->fast_scan = !fast_scan;
				aपंचांगel_scan(priv, 1);
				notअगरy_scan_complete = 0;
			पूर्ण
			priv->site_survey_state = SITE_SURVEY_COMPLETED;
			अगर (notअगरy_scan_complete) अणु
				wrqu.data.length = 0;
				wrqu.data.flags = 0;
				wireless_send_event(priv->dev, SIOCGIWSCAN, &wrqu, शून्य);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल CMD_SiteSurvey:
		priv->fast_scan = 0;

		अगर (status != CMD_STATUS_COMPLETE)
			वापस;

		priv->site_survey_state = SITE_SURVEY_COMPLETED;
		अगर (priv->station_is_associated) अणु
			aपंचांगel_enter_state(priv, STATION_STATE_READY);
			wrqu.data.length = 0;
			wrqu.data.flags = 0;
			wireless_send_event(priv->dev, SIOCGIWSCAN, &wrqu, शून्य);
		पूर्ण अन्यथा अणु
			aपंचांगel_scan(priv, 1);
		पूर्ण
		अवरोध;

	हाल CMD_Join:
		अगर (status == CMD_STATUS_COMPLETE) अणु
			अगर (priv->operating_mode == IW_MODE_ADHOC) अणु
				priv->station_was_associated = priv->station_is_associated;
				aपंचांगel_enter_state(priv, STATION_STATE_READY);
			पूर्ण अन्यथा अणु
				पूर्णांक auth = WLAN_AUTH_OPEN;
				priv->AuthenticationRequestRetryCnt = 0;
				aपंचांगel_enter_state(priv, STATION_STATE_AUTHENTICATING);

				mod_समयr(&priv->management_समयr, jअगरfies + MGMT_JIFFIES);
				priv->CurrentAuthentTransactionSeqNum = 0x0001;
				अगर (priv->wep_is_on && priv->exclude_unencrypted)
					auth = WLAN_AUTH_SHARED_KEY;
				send_authentication_request(priv, auth, शून्य, 0);
			पूर्ण
			वापस;
		पूर्ण

		aपंचांगel_scan(priv, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_wakeup_firmware(काष्ठा aपंचांगel_निजी *priv)
अणु
	काष्ठा host_info_काष्ठा *अगरace = &priv->host_info;
	u16 mr1, mr3;
	पूर्णांक i;

	अगर (priv->card_type == CARD_TYPE_SPI_FLASH)
		aपंचांगel_set_gcr(priv->dev, GCR_REMAP);

	/* wake up on-board processor */
	aपंचांगel_clear_gcr(priv->dev, 0x0040);
	aपंचांगel_ग_लिखो16(priv->dev, BSR, BSS_SRAM);

	अगर (priv->card_type == CARD_TYPE_SPI_FLASH)
		mdelay(100);

	/* and रुको क्रम it */
	क्रम (i = LOOP_RETRY_LIMIT; i; i--) अणु
		mr1 = aपंचांगel_पढ़ो16(priv->dev, MR1);
		mr3 = aपंचांगel_पढ़ो16(priv->dev, MR3);

		अगर (mr3 & MAC_BOOT_COMPLETE)
			अवरोध;
		अगर (mr1 & MAC_BOOT_COMPLETE &&
		    priv->bus_type == BUS_TYPE_PCCARD)
			अवरोध;
	पूर्ण

	अगर (i == 0) अणु
		prपूर्णांकk(KERN_ALERT "%s: MAC failed to boot.\n", priv->dev->name);
		वापस -EIO;
	पूर्ण

	अगर ((priv->host_info_base = aपंचांगel_पढ़ो16(priv->dev, MR2)) == 0xffff) अणु
		prपूर्णांकk(KERN_ALERT "%s: card missing.\n", priv->dev->name);
		वापस -ENODEV;
	पूर्ण

	/* now check क्रम completion of MAC initialization through
	   the FunCtrl field of the IFACE, poll MR1 to detect completion of
	   MAC initialization, check completion status, set पूर्णांकerrupt mask,
	   enables पूर्णांकerrupts and calls Tx and Rx initialization functions */

	aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_FUNC_CTRL_OFFSET), FUNC_CTRL_INIT_COMPLETE);

	क्रम (i = LOOP_RETRY_LIMIT; i; i--) अणु
		mr1 = aपंचांगel_पढ़ो16(priv->dev, MR1);
		mr3 = aपंचांगel_पढ़ो16(priv->dev, MR3);

		अगर (mr3 & MAC_INIT_COMPLETE)
			अवरोध;
		अगर (mr1 & MAC_INIT_COMPLETE &&
		    priv->bus_type == BUS_TYPE_PCCARD)
			अवरोध;
	पूर्ण

	अगर (i == 0) अणु
		prपूर्णांकk(KERN_ALERT "%s: MAC failed to initialise.\n",
				priv->dev->name);
		वापस -EIO;
	पूर्ण

	/* Check क्रम MAC_INIT_OK only on the रेजिस्टर that the MAC_INIT_OK was set */
	अगर ((mr3 & MAC_INIT_COMPLETE) &&
	    !(aपंचांगel_पढ़ो16(priv->dev, MR3) & MAC_INIT_OK)) अणु
		prपूर्णांकk(KERN_ALERT "%s: MAC failed MR3 self-test.\n", priv->dev->name);
		वापस -EIO;
	पूर्ण
	अगर ((mr1 & MAC_INIT_COMPLETE) &&
	    !(aपंचांगel_पढ़ो16(priv->dev, MR1) & MAC_INIT_OK)) अणु
		prपूर्णांकk(KERN_ALERT "%s: MAC failed MR1 self-test.\n", priv->dev->name);
		वापस -EIO;
	पूर्ण

	aपंचांगel_copy_to_host(priv->dev, (अचिन्हित अक्षर *)अगरace,
			   priv->host_info_base, माप(*अगरace));

	अगरace->tx_buff_pos = le16_to_cpu(अगरace->tx_buff_pos);
	अगरace->tx_buff_size = le16_to_cpu(अगरace->tx_buff_size);
	अगरace->tx_desc_pos = le16_to_cpu(अगरace->tx_desc_pos);
	अगरace->tx_desc_count = le16_to_cpu(अगरace->tx_desc_count);
	अगरace->rx_buff_pos = le16_to_cpu(अगरace->rx_buff_pos);
	अगरace->rx_buff_size = le16_to_cpu(अगरace->rx_buff_size);
	अगरace->rx_desc_pos = le16_to_cpu(अगरace->rx_desc_pos);
	अगरace->rx_desc_count = le16_to_cpu(अगरace->rx_desc_count);
	अगरace->build_version = le16_to_cpu(अगरace->build_version);
	अगरace->command_pos = le16_to_cpu(अगरace->command_pos);
	अगरace->major_version = le16_to_cpu(अगरace->major_version);
	अगरace->minor_version = le16_to_cpu(अगरace->minor_version);
	अगरace->func_ctrl = le16_to_cpu(अगरace->func_ctrl);
	अगरace->mac_status = le16_to_cpu(अगरace->mac_status);

	वापस 0;
पूर्ण

/* determine type of memory and MAC address */
अटल पूर्णांक probe_aपंचांगel_card(काष्ठा net_device *dev)
अणु
	पूर्णांक rc = 0;
	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);

	/* reset pccard */
	अगर (priv->bus_type == BUS_TYPE_PCCARD)
		aपंचांगel_ग_लिखो16(dev, GCR, 0x0060);

	aपंचांगel_ग_लिखो16(dev, GCR, 0x0040);
	msleep(500);

	अगर (aपंचांगel_पढ़ो16(dev, MR2) == 0) अणु
		/* No stored firmware so load a small stub which just
		   tells us the MAC address */
		पूर्णांक i;
		priv->card_type = CARD_TYPE_EEPROM;
		aपंचांगel_ग_लिखो16(dev, BSR, BSS_IRAM);
		aपंचांगel_copy_to_card(dev, 0, mac_पढ़ोer, माप(mac_पढ़ोer));
		aपंचांगel_set_gcr(dev, GCR_REMAP);
		aपंचांगel_clear_gcr(priv->dev, 0x0040);
		aपंचांगel_ग_लिखो16(dev, BSR, BSS_SRAM);
		क्रम (i = LOOP_RETRY_LIMIT; i; i--)
			अगर (aपंचांगel_पढ़ो16(dev, MR3) & MAC_BOOT_COMPLETE)
				अवरोध;
		अगर (i == 0) अणु
			prपूर्णांकk(KERN_ALERT "%s: MAC failed to boot MAC address reader.\n", dev->name);
		पूर्ण अन्यथा अणु
			aपंचांगel_copy_to_host(dev, dev->dev_addr, aपंचांगel_पढ़ो16(dev, MR2), 6);
			/* got address, now squash it again until the network
			   पूर्णांकerface is खोलोed */
			अगर (priv->bus_type == BUS_TYPE_PCCARD)
				aपंचांगel_ग_लिखो16(dev, GCR, 0x0060);
			aपंचांगel_ग_लिखो16(dev, GCR, 0x0040);
			rc = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (aपंचांगel_पढ़ो16(dev, MR4) == 0) अणु
		/* Mac address easy in this हाल. */
		priv->card_type = CARD_TYPE_PARALLEL_FLASH;
		aपंचांगel_ग_लिखो16(dev,  BSR, 1);
		aपंचांगel_copy_to_host(dev, dev->dev_addr, 0xc000, 6);
		aपंचांगel_ग_लिखो16(dev,  BSR, 0x200);
		rc = 1;
	पूर्ण अन्यथा अणु
		/* Standard firmware in flash, boot it up and ask
		   क्रम the Mac Address */
		priv->card_type = CARD_TYPE_SPI_FLASH;
		अगर (aपंचांगel_wakeup_firmware(priv) == 0) अणु
			aपंचांगel_get_mib(priv, Mac_Address_Mib_Type, 0, dev->dev_addr, 6);

			/* got address, now squash it again until the network
			   पूर्णांकerface is खोलोed */
			अगर (priv->bus_type == BUS_TYPE_PCCARD)
				aपंचांगel_ग_लिखो16(dev, GCR, 0x0060);
			aपंचांगel_ग_लिखो16(dev, GCR, 0x0040);
			rc = 1;
		पूर्ण
	पूर्ण

	अगर (rc) अणु
		अगर (dev->dev_addr[0] == 0xFF) अणु
			अटल स्थिर u8 शेष_mac[] = अणु
				0x00, 0x04, 0x25, 0x00, 0x00, 0x00
			पूर्ण;
			prपूर्णांकk(KERN_ALERT "%s: *** Invalid MAC address. UPGRADE Firmware ****\n", dev->name);
			स_नकल(dev->dev_addr, शेष_mac, ETH_ALEN);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* Move the encyption inक्रमmation on the MIB काष्ठाure.
   This routine is क्रम the pre-WPA firmware: later firmware has
   a dअगरferent क्रमmat MIB and a dअगरferent routine. */
अटल व्योम build_wep_mib(काष्ठा aपंचांगel_निजी *priv)
अणु
	काष्ठा अणु /* NB this is matched to the hardware, करोn't change. */
		u8 wep_is_on;
		u8 शेष_key; /* 0..3 */
		u8 reserved;
		u8 exclude_unencrypted;

		u32 WEPICV_error_count;
		u32 WEP_excluded_count;

		u8 wep_keys[MAX_ENCRYPTION_KEYS][13];
		u8 encryption_level; /* 0, 1, 2 */
		u8 reserved2[3];
	पूर्ण mib;
	पूर्णांक i;

	mib.wep_is_on = priv->wep_is_on;
	अगर (priv->wep_is_on) अणु
		अगर (priv->wep_key_len[priv->शेष_key] > 5)
			mib.encryption_level = 2;
		अन्यथा
			mib.encryption_level = 1;
	पूर्ण अन्यथा अणु
		mib.encryption_level = 0;
	पूर्ण

	mib.शेष_key = priv->शेष_key;
	mib.exclude_unencrypted = priv->exclude_unencrypted;

	क्रम (i = 0; i < MAX_ENCRYPTION_KEYS; i++)
		स_नकल(mib.wep_keys[i], priv->wep_keys[i], 13);

	aपंचांगel_set_mib(priv, Mac_Wep_Mib_Type, 0, (u8 *)&mib, माप(mib));
पूर्ण

अटल व्योम build_wpa_mib(काष्ठा aपंचांगel_निजी *priv)
अणु
	/* This is क्रम the later (WPA enabled) firmware. */

	काष्ठा अणु /* NB this is matched to the hardware, करोn't change. */
		u8 cipher_शेष_key_value[MAX_ENCRYPTION_KEYS][MAX_ENCRYPTION_KEY_SIZE];
		u8 receiver_address[ETH_ALEN];
		u8 wep_is_on;
		u8 शेष_key; /* 0..3 */
		u8 group_key;
		u8 exclude_unencrypted;
		u8 encryption_type;
		u8 reserved;

		u32 WEPICV_error_count;
		u32 WEP_excluded_count;

		u8 key_RSC[4][8];
	पूर्ण mib;

	पूर्णांक i;

	mib.wep_is_on = priv->wep_is_on;
	mib.exclude_unencrypted = priv->exclude_unencrypted;
	स_नकल(mib.receiver_address, priv->CurrentBSSID, ETH_ALEN);

	/* zero all the keys beक्रमe adding in valid ones. */
	स_रखो(mib.cipher_शेष_key_value, 0, माप(mib.cipher_शेष_key_value));

	अगर (priv->wep_is_on) अणु
		/* There's a comment in the Aपंचांगel code to the effect that this
		   is only valid when still using WEP, it may need to be set to
		   something to use WPA */
		स_रखो(mib.key_RSC, 0, माप(mib.key_RSC));

		mib.शेष_key = mib.group_key = 255;
		क्रम (i = 0; i < MAX_ENCRYPTION_KEYS; i++) अणु
			अगर (priv->wep_key_len[i] > 0) अणु
				स_नकल(mib.cipher_शेष_key_value[i], priv->wep_keys[i], MAX_ENCRYPTION_KEY_SIZE);
				अगर (i == priv->शेष_key) अणु
					mib.शेष_key = i;
					mib.cipher_शेष_key_value[i][MAX_ENCRYPTION_KEY_SIZE-1] = 7;
					mib.cipher_शेष_key_value[i][MAX_ENCRYPTION_KEY_SIZE-2] = priv->pairwise_cipher_suite;
				पूर्ण अन्यथा अणु
					mib.group_key = i;
					priv->group_cipher_suite = priv->pairwise_cipher_suite;
					mib.cipher_शेष_key_value[i][MAX_ENCRYPTION_KEY_SIZE-1] = 1;
					mib.cipher_शेष_key_value[i][MAX_ENCRYPTION_KEY_SIZE-2] = priv->group_cipher_suite;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (mib.शेष_key == 255)
			mib.शेष_key = mib.group_key != 255 ? mib.group_key : 0;
		अगर (mib.group_key == 255)
			mib.group_key = mib.शेष_key;

	पूर्ण

	aपंचांगel_set_mib(priv, Mac_Wep_Mib_Type, 0, (u8 *)&mib, माप(mib));
पूर्ण

अटल पूर्णांक reset_aपंचांगel_card(काष्ठा net_device *dev)
अणु
	/* करो everything necessary to wake up the hardware, including
	   रुकोing क्रम the lightning strike and throwing the knअगरe चयन....

	   set all the Mib values which matter in the card to match
	   their settings in the aपंचांगel_निजी काष्ठाure. Some of these
	   can be altered on the fly, but many (WEP, infraकाष्ठाure or ad-hoc)
	   can only be changed by tearing करोwn the world and coming back through
	   here.

	   This routine is also responsible क्रम initialising some
	   hardware-specअगरic fields in the aपंचांगel_निजी काष्ठाure,
	   including a copy of the firmware's hostinfo काष्ठाure
	   which is the route पूर्णांकo the rest of the firmware dataकाष्ठाures. */

	काष्ठा aपंचांगel_निजी *priv = netdev_priv(dev);
	u8 configuration;
	पूर्णांक old_state = priv->station_state;
	पूर्णांक err = 0;

	/* data to add to the firmware names, in priority order
	   this implemenents firmware versioning */

	अटल अक्षर *firmware_modअगरier[] = अणु
		"-wpa",
		"",
		शून्य
	पूर्ण;

	/* reset pccard */
	अगर (priv->bus_type == BUS_TYPE_PCCARD)
		aपंचांगel_ग_लिखो16(priv->dev, GCR, 0x0060);

	/* stop card , disable पूर्णांकerrupts */
	aपंचांगel_ग_लिखो16(priv->dev, GCR, 0x0040);

	अगर (priv->card_type == CARD_TYPE_EEPROM) अणु
		/* copy in firmware अगर needed */
		स्थिर काष्ठा firmware *fw_entry = शून्य;
		स्थिर अचिन्हित अक्षर *fw;
		पूर्णांक len = priv->firmware_length;
		अगर (!(fw = priv->firmware)) अणु
			अगर (priv->firmware_type == ATMEL_FW_TYPE_NONE) अणु
				अगर (म_माप(priv->firmware_id) == 0) अणु
					prपूर्णांकk(KERN_INFO
					       "%s: card type is unknown: assuming at76c502 firmware is OK.\n",
					       dev->name);
					prपूर्णांकk(KERN_INFO
					       "%s: if not, use the firmware= module parameter.\n",
					       dev->name);
					म_नकल(priv->firmware_id, "atmel_at76c502.bin");
				पूर्ण
				err = request_firmware(&fw_entry, priv->firmware_id, priv->sys_dev);
				अगर (err != 0) अणु
					prपूर्णांकk(KERN_ALERT
					       "%s: firmware %s is missing, cannot continue.\n",
					       dev->name, priv->firmware_id);
					वापस err;
				पूर्ण
			पूर्ण अन्यथा अणु
				पूर्णांक fw_index = 0;
				पूर्णांक success = 0;

				/* get firmware filename entry based on firmware type ID */
				जबतक (fw_table[fw_index].fw_type != priv->firmware_type
						&& fw_table[fw_index].fw_type != ATMEL_FW_TYPE_NONE)
					fw_index++;

				/* स्थिरruct the actual firmware file name */
				अगर (fw_table[fw_index].fw_type != ATMEL_FW_TYPE_NONE) अणु
					पूर्णांक i;
					क्रम (i = 0; firmware_modअगरier[i]; i++) अणु
						snम_लिखो(priv->firmware_id, 32, "%s%s.%s", fw_table[fw_index].fw_file,
							firmware_modअगरier[i], fw_table[fw_index].fw_file_ext);
						priv->firmware_id[31] = '\0';
						अगर (request_firmware(&fw_entry, priv->firmware_id, priv->sys_dev) == 0) अणु
							success = 1;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (!success) अणु
					prपूर्णांकk(KERN_ALERT
					       "%s: firmware %s is missing, cannot start.\n",
					       dev->name, priv->firmware_id);
					priv->firmware_id[0] = '\0';
					वापस -ENOENT;
				पूर्ण
			पूर्ण

			fw = fw_entry->data;
			len = fw_entry->size;
		पूर्ण

		अगर (len <= 0x6000) अणु
			aपंचांगel_ग_लिखो16(priv->dev, BSR, BSS_IRAM);
			aपंचांगel_copy_to_card(priv->dev, 0, fw, len);
			aपंचांगel_set_gcr(priv->dev, GCR_REMAP);
		पूर्ण अन्यथा अणु
			/* Remap */
			aपंचांगel_set_gcr(priv->dev, GCR_REMAP);
			aपंचांगel_ग_लिखो16(priv->dev, BSR, BSS_IRAM);
			aपंचांगel_copy_to_card(priv->dev, 0, fw, 0x6000);
			aपंचांगel_ग_लिखो16(priv->dev, BSR, 0x2ff);
			aपंचांगel_copy_to_card(priv->dev, 0x8000, &fw[0x6000], len - 0x6000);
		पूर्ण

		release_firmware(fw_entry);
	पूर्ण

	err = aपंचांगel_wakeup_firmware(priv);
	अगर (err != 0)
		वापस err;

	/* Check the version and set the correct flag क्रम wpa stuff,
	   old and new firmware is incompatible.
	   The pre-wpa 3com firmware reports major version 5,
	   the wpa 3com firmware is major version 4 and करोesn't need
	   the 3com broken-ness filter. */
	priv->use_wpa = (priv->host_info.major_version == 4);
	priv->radio_on_broken = (priv->host_info.major_version == 5);

	/* unmask all irq sources */
	aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_INT_MASK_OFFSET), 0xff);

	/* पूर्णांक Tx प्रणाली and enable Tx */
	aपंचांगel_wmem8(priv, aपंचांगel_tx(priv, TX_DESC_FLAGS_OFFSET, 0), 0);
	aपंचांगel_wmem32(priv, aपंचांगel_tx(priv, TX_DESC_NEXT_OFFSET, 0), 0x80000000L);
	aपंचांगel_wmem16(priv, aपंचांगel_tx(priv, TX_DESC_POS_OFFSET, 0), 0);
	aपंचांगel_wmem16(priv, aपंचांगel_tx(priv, TX_DESC_SIZE_OFFSET, 0), 0);

	priv->tx_desc_मुक्त = priv->host_info.tx_desc_count;
	priv->tx_desc_head = 0;
	priv->tx_desc_tail = 0;
	priv->tx_desc_previous = 0;
	priv->tx_मुक्त_mem = priv->host_info.tx_buff_size;
	priv->tx_buff_head = 0;
	priv->tx_buff_tail = 0;

	configuration = aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_FUNC_CTRL_OFFSET));
	aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_FUNC_CTRL_OFFSET),
				   configuration | FUNC_CTRL_TxENABLE);

	/* init Rx प्रणाली and enable */
	priv->rx_desc_head = 0;

	configuration = aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_FUNC_CTRL_OFFSET));
	aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_FUNC_CTRL_OFFSET),
				   configuration | FUNC_CTRL_RxENABLE);

	अगर (!priv->radio_on_broken) अणु
		अगर (aपंचांगel_send_command_रुको(priv, CMD_EnableRadio, शून्य, 0) ==
		    CMD_STATUS_REJECTED_RADIO_OFF) अणु
			prपूर्णांकk(KERN_INFO "%s: cannot turn the radio on.\n",
			       dev->name);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* set up enough MIB values to run. */
	aपंचांगel_set_mib8(priv, Local_Mib_Type, LOCAL_MIB_AUTO_TX_RATE_POS, priv->स्वतः_tx_rate);
	aपंचांगel_set_mib8(priv, Local_Mib_Type,  LOCAL_MIB_TX_PROMISCUOUS_POS,  PROM_MODE_OFF);
	aपंचांगel_set_mib16(priv, Mac_Mib_Type, MAC_MIB_RTS_THRESHOLD_POS, priv->rts_threshold);
	aपंचांगel_set_mib16(priv, Mac_Mib_Type, MAC_MIB_FRAG_THRESHOLD_POS, priv->frag_threshold);
	aपंचांगel_set_mib8(priv, Mac_Mib_Type, MAC_MIB_SHORT_RETRY_POS, priv->लघु_retry);
	aपंचांगel_set_mib8(priv, Mac_Mib_Type, MAC_MIB_LONG_RETRY_POS, priv->दीर्घ_retry);
	aपंचांगel_set_mib8(priv, Local_Mib_Type, LOCAL_MIB_PREAMBLE_TYPE, priv->preamble);
	aपंचांगel_set_mib(priv, Mac_Address_Mib_Type, MAC_ADDR_MIB_MAC_ADDR_POS,
		      priv->dev->dev_addr, 6);
	aपंचांगel_set_mib8(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_PS_MODE_POS, ACTIVE_MODE);
	aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_LISTEN_INTERVAL_POS, 1);
	aपंचांगel_set_mib16(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_BEACON_PER_POS, priv->शेष_beacon_period);
	aपंचांगel_set_mib(priv, Phy_Mib_Type, PHY_MIB_RATE_SET_POS, aपंचांगel_basic_rates, 4);
	aपंचांगel_set_mib8(priv, Mac_Mgmt_Mib_Type, MAC_MGMT_MIB_CUR_PRIVACY_POS, priv->wep_is_on);
	अगर (priv->use_wpa)
		build_wpa_mib(priv);
	अन्यथा
		build_wep_mib(priv);

	अगर (old_state == STATION_STATE_READY) अणु
		जोड़ iwreq_data wrqu;

		wrqu.data.length = 0;
		wrqu.data.flags = 0;
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		eth_zero_addr(wrqu.ap_addr.sa_data);
		wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_send_command(काष्ठा aपंचांगel_निजी *priv, पूर्णांक command,
			       व्योम *cmd, पूर्णांक cmd_size)
अणु
	अगर (cmd)
		aपंचांगel_copy_to_card(priv->dev, aपंचांगel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET),
				   cmd, cmd_size);

	aपंचांगel_wmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_COMMAND_OFFSET), command);
	aपंचांगel_wmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_STATUS_OFFSET), 0);
पूर्ण

अटल पूर्णांक aपंचांगel_send_command_रुको(काष्ठा aपंचांगel_निजी *priv, पूर्णांक command,
				   व्योम *cmd, पूर्णांक cmd_size)
अणु
	पूर्णांक i, status;

	aपंचांगel_send_command(priv, command, cmd, cmd_size);

	क्रम (i = 5000; i; i--) अणु
		status = aपंचांगel_rmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_STATUS_OFFSET));
		अगर (status != CMD_STATUS_IDLE &&
		    status != CMD_STATUS_IN_PROGRESS)
			अवरोध;
		udelay(20);
	पूर्ण

	अगर (i == 0) अणु
		prपूर्णांकk(KERN_ALERT "%s: failed to contact MAC.\n", priv->dev->name);
		status =  CMD_STATUS_HOST_ERROR;
	पूर्ण अन्यथा अणु
		अगर (command != CMD_EnableRadio)
			status = CMD_STATUS_COMPLETE;
	पूर्ण

	वापस status;
पूर्ण

अटल u8 aपंचांगel_get_mib8(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index)
अणु
	काष्ठा get_set_mib m;
	m.type = type;
	m.size = 1;
	m.index = index;

	aपंचांगel_send_command_रुको(priv, CMD_Get_MIB_Vars, &m, MIB_HEADER_SIZE + 1);
	वापस aपंचांगel_rmem8(priv, aपंचांगel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET + MIB_HEADER_SIZE));
पूर्ण

अटल व्योम aपंचांगel_set_mib8(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index, u8 data)
अणु
	काष्ठा get_set_mib m;
	m.type = type;
	m.size = 1;
	m.index = index;
	m.data[0] = data;

	aपंचांगel_send_command_रुको(priv, CMD_Set_MIB_Vars, &m, MIB_HEADER_SIZE + 1);
पूर्ण

अटल व्योम aपंचांगel_set_mib16(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			    u16 data)
अणु
	काष्ठा get_set_mib m;
	m.type = type;
	m.size = 2;
	m.index = index;
	m.data[0] = data;
	m.data[1] = data >> 8;

	aपंचांगel_send_command_रुको(priv, CMD_Set_MIB_Vars, &m, MIB_HEADER_SIZE + 2);
पूर्ण

अटल व्योम aपंचांगel_set_mib(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			  u8 *data, पूर्णांक data_len)
अणु
	काष्ठा get_set_mib m;
	m.type = type;
	m.size = data_len;
	m.index = index;

	अगर (data_len > MIB_MAX_DATA_BYTES)
		prपूर्णांकk(KERN_ALERT "%s: MIB buffer too small.\n", priv->dev->name);

	स_नकल(m.data, data, data_len);
	aपंचांगel_send_command_रुको(priv, CMD_Set_MIB_Vars, &m, MIB_HEADER_SIZE + data_len);
पूर्ण

अटल व्योम aपंचांगel_get_mib(काष्ठा aपंचांगel_निजी *priv, u8 type, u8 index,
			  u8 *data, पूर्णांक data_len)
अणु
	काष्ठा get_set_mib m;
	m.type = type;
	m.size = data_len;
	m.index = index;

	अगर (data_len > MIB_MAX_DATA_BYTES)
		prपूर्णांकk(KERN_ALERT "%s: MIB buffer too small.\n", priv->dev->name);

	aपंचांगel_send_command_रुको(priv, CMD_Get_MIB_Vars, &m, MIB_HEADER_SIZE + data_len);
	aपंचांगel_copy_to_host(priv->dev, data,
			   aपंचांगel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET + MIB_HEADER_SIZE), data_len);
पूर्ण

अटल व्योम aपंचांगel_ग_लिखोAR(काष्ठा net_device *dev, u16 data)
अणु
	पूर्णांक i;
	outw(data, dev->base_addr + AR);
	/* Address रेजिस्टर appears to need some convincing..... */
	क्रम (i = 0; data != inw(dev->base_addr + AR) && i < 10; i++)
		outw(data, dev->base_addr + AR);
पूर्ण

अटल व्योम aपंचांगel_copy_to_card(काष्ठा net_device *dev, u16 dest,
			       स्थिर अचिन्हित अक्षर *src, u16 len)
अणु
	पूर्णांक i;
	aपंचांगel_ग_लिखोAR(dev, dest);
	अगर (dest % 2) अणु
		aपंचांगel_ग_लिखो8(dev, DR, *src);
		src++; len--;
	पूर्ण
	क्रम (i = len; i > 1 ; i -= 2) अणु
		u8 lb = *src++;
		u8 hb = *src++;
		aपंचांगel_ग_लिखो16(dev, DR, lb | (hb << 8));
	पूर्ण
	अगर (i)
		aपंचांगel_ग_लिखो8(dev, DR, *src);
पूर्ण

अटल व्योम aपंचांगel_copy_to_host(काष्ठा net_device *dev, अचिन्हित अक्षर *dest,
			       u16 src, u16 len)
अणु
	पूर्णांक i;
	aपंचांगel_ग_लिखोAR(dev, src);
	अगर (src % 2) अणु
		*dest = aपंचांगel_पढ़ो8(dev, DR);
		dest++; len--;
	पूर्ण
	क्रम (i = len; i > 1 ; i -= 2) अणु
		u16 hw = aपंचांगel_पढ़ो16(dev, DR);
		*dest++ = hw;
		*dest++ = hw >> 8;
	पूर्ण
	अगर (i)
		*dest = aपंचांगel_पढ़ो8(dev, DR);
पूर्ण

अटल व्योम aपंचांगel_set_gcr(काष्ठा net_device *dev, u16 mask)
अणु
	outw(inw(dev->base_addr + GCR) | mask, dev->base_addr + GCR);
पूर्ण

अटल व्योम aपंचांगel_clear_gcr(काष्ठा net_device *dev, u16 mask)
अणु
	outw(inw(dev->base_addr + GCR) & ~mask, dev->base_addr + GCR);
पूर्ण

अटल पूर्णांक aपंचांगel_lock_mac(काष्ठा aपंचांगel_निजी *priv)
अणु
	पूर्णांक i, j = 20;
 retry:
	क्रम (i = 5000; i; i--) अणु
		अगर (!aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_HOST_OFFSET)))
			अवरोध;
		udelay(20);
	पूर्ण

	अगर (!i)
		वापस 0; /* समयd out */

	aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_MAC_OFFSET), 1);
	अगर (aपंचांगel_rmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_HOST_OFFSET))) अणु
		aपंचांगel_wmem8(priv, aपंचांगel_hi(priv, IFACE_LOCKOUT_MAC_OFFSET), 0);
		अगर (!j--)
			वापस 0; /* समयd out */
		जाओ retry;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम aपंचांगel_wmem32(काष्ठा aपंचांगel_निजी *priv, u16 pos, u32 data)
अणु
	aपंचांगel_ग_लिखोAR(priv->dev, pos);
	aपंचांगel_ग_लिखो16(priv->dev, DR, data); /* card is little-endian */
	aपंचांगel_ग_लिखो16(priv->dev, DR, data >> 16);
पूर्ण

/***************************************************************************/
/* There follows the source क्रमm of the MAC address पढ़ोing firmware       */
/***************************************************************************/
#अगर 0

/* Copyright 2003 Matthew T. Russotto                                      */
/* But derived from the Aपंचांगel 76C502 firmware written by Aपंचांगel and         */
/* included in "atmel wireless lan drivers" package                        */
/*
    This file is part of net.russotto.AपंचांगelMACFW, hereto referred to
    as AपंचांगelMACFW

    AपंचांगelMACFW is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.

    AपंचांगelMACFW is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with AपंचांगelMACFW; अगर not, see <http://www.gnu.org/licenses/>.

****************************************************************************/
/* This firmware should work on the 76C502 RFMD, RFMD_D, and RFMD_E        */
/* It will probably work on the 76C504 and 76C502 RFMD_3COM                */
/* It only works on SPI EEPROM versions of the card.                       */

/* This firmware initializes the SPI controller and घड़ी, पढ़ोs the MAC   */
/* address from the EEPROM पूर्णांकo SRAM, and माला_दो the SRAM offset of the MAC  */
/* address in MR2, and sets MR3 to 0x10 to indicate it is करोne             */
/* It also माला_दो a complete copy of the EEPROM in SRAM with the offset in   */
/* MR4, क्रम investigational purposes (maybe we can determine chip type     */
/* from that?)                                                             */

	.org 0
    .set MRBASE, 0x8000000
	.set CPSR_INITIAL, 0xD3 /* IRQ/FIQ disabled, ARM mode, Supervisor state */
	.set CPSR_USER, 0xD1 /* IRQ/FIQ disabled, ARM mode, USER state */
	.set SRAM_BASE,  0x02000000
	.set SP_BASE,    0x0F300000
	.set UNK_BASE,   0x0F000000 /* Some पूर्णांकernal device, but which one? */
	.set SPI_CGEN_BASE,  0x0E000000 /* Some पूर्णांकernal device, but which one? */
	.set UNK3_BASE,  0x02014000 /* Some पूर्णांकernal device, but which one? */
	.set STACK_BASE, 0x5600
	.set SP_SR, 0x10
	.set SP_TDRE, 2 /* status रेजिस्टर bit -- TDR empty */
	.set SP_RDRF, 1 /* status रेजिस्टर bit -- RDR full */
	.set SP_SWRST, 0x80
	.set SP_SPIEN, 0x1
	.set SP_CR, 0   /* control रेजिस्टर */
	.set SP_MR, 4   /* mode रेजिस्टर */
	.set SP_RDR, 0x08 /* Read Data Register */
	.set SP_TDR, 0x0C /* Transmit Data Register */
	.set SP_CSR0, 0x30 /* chip select रेजिस्टरs */
	.set SP_CSR1, 0x34
	.set SP_CSR2, 0x38
	.set SP_CSR3, 0x3C
	.set NVRAM_CMD_RDSR, 5 /* पढ़ो status रेजिस्टर */
	.set NVRAM_CMD_READ, 3 /* पढ़ो data */
	.set NVRAM_SR_RDY, 1 /* RDY bit.  This bit is inverted */
	.set SPI_8CLOCKS, 0xFF /* Writing this to the TDR करोesn't करो anything to the
				  serial output, since SO is normally high.  But it
				  करोes cause 8 घड़ी cycles and thus 8 bits to be
				  घड़ीed in to the chip.  See Aपंचांगel's SPI
				  controller (e.g. AT91M55800) timing and 4K
				  SPI EEPROM manuals */

	.set NVRAM_SCRATCH, 0x02000100  /* arbitrary area क्रम scratchpad memory */
	.set NVRAM_IMAGE, 0x02000200
	.set NVRAM_LENGTH, 0x0200
	.set MAC_ADDRESS_MIB, SRAM_BASE
	.set MAC_ADDRESS_LENGTH, 6
	.set MAC_BOOT_FLAG, 0x10
	.set MR1, 0
	.set MR2, 4
	.set MR3, 8
	.set MR4, 0xC
RESET_VECTOR:
	b RESET_HANDLER
UNDEF_VECTOR:
	b HALT1
SWI_VECTOR:
	b HALT1
IABORT_VECTOR:
	b HALT1
DABORT_VECTOR:
RESERVED_VECTOR:
	b HALT1
IRQ_VECTOR:
	b HALT1
FIQ_VECTOR:
	b HALT1
HALT1:	b HALT1
RESET_HANDLER:
	mov     r0, #CPSR_INITIAL
	msr	CPSR_c, r0	/* This is probably unnecessary */

/* I'm guessing this is initializing घड़ी generator electronics क्रम SPI */
	ldr	r0, =SPI_CGEN_BASE
	mov	r1, #0
	mov	r1, r1, lsl #3
	orr	r1, r1, #0
	str	r1, [r0]
	ldr	r1, [r0, #28]
	bic	r1, r1, #16
	str	r1, [r0, #28]
	mov	r1, #1
	str	r1, [r0, #8]

	ldr	r0, =MRBASE
	mov	r1, #0
	strh	r1, [r0, #MR1]
	strh	r1, [r0, #MR2]
	strh	r1, [r0, #MR3]
	strh	r1, [r0, #MR4]

	mov	sp, #STACK_BASE
	bl	SP_INIT
	mov	r0, #10
	bl	DELAY9
	bl	GET_MAC_ADDR
	bl	GET_WHOLE_NVRAM
	ldr	r0, =MRBASE
	ldr	r1, =MAC_ADDRESS_MIB
	strh	r1, [r0, #MR2]
	ldr	r1, =NVRAM_IMAGE
	strh	r1, [r0, #MR4]
	mov	r1, #MAC_BOOT_FLAG
	strh	r1, [r0, #MR3]
HALT2:	b HALT2
.func Get_Whole_NVRAM, GET_WHOLE_NVRAM
GET_WHOLE_NVRAM:
	sपंचांगdb	sp!, अणुlrपूर्ण
	mov	r2, #0 /* 0th bytes of NVRAM */
	mov	r3, #NVRAM_LENGTH
	mov	r1, #0		/* not used in routine */
	ldr	r0, =NVRAM_IMAGE
	bl	NVRAM_XFER
	ldmia	sp!, अणुlrपूर्ण
	bx	lr
.endfunc

.func Get_MAC_Addr, GET_MAC_ADDR
GET_MAC_ADDR:
	sपंचांगdb	sp!, अणुlrपूर्ण
	mov	r2, #0x120	/* address of MAC Address within NVRAM */
	mov	r3, #MAC_ADDRESS_LENGTH
	mov	r1, #0		/* not used in routine */
	ldr	r0, =MAC_ADDRESS_MIB
	bl	NVRAM_XFER
	ldmia	sp!, अणुlrपूर्ण
	bx	lr
.endfunc
.ltorg
.func Delay9, DELAY9
DELAY9:
	adds	r0, r0, r0, LSL #3   /* r0 = r0 * 9 */
DELAYLOOP:
	beq	DELAY9_करोne
	subs	r0, r0, #1
	b	DELAYLOOP
DELAY9_करोne:
	bx	lr
.endfunc

.func SP_Init, SP_INIT
SP_INIT:
	mov	r1, #SP_SWRST
	ldr	r0, =SP_BASE
	str	r1, [r0, #SP_CR] /* reset the SPI */
	mov	r1, #0
	str	r1, [r0, #SP_CR] /* release SPI from reset state */
	mov	r1, #SP_SPIEN
	str	r1, [r0, #SP_MR] /* set the SPI to MASTER mode*/
	str	r1, [r0, #SP_CR] /* enable the SPI */

/*  My guess would be this turns on the SPI घड़ी */
	ldr	r3, =SPI_CGEN_BASE
	ldr	r1, [r3, #28]
	orr	r1, r1, #0x2000
	str	r1, [r3, #28]

	ldr	r1, =0x2000c01
	str	r1, [r0, #SP_CSR0]
	ldr	r1, =0x2000201
	str	r1, [r0, #SP_CSR1]
	str	r1, [r0, #SP_CSR2]
	str	r1, [r0, #SP_CSR3]
	ldr	r1, [r0, #SP_SR]
	ldr	r0, [r0, #SP_RDR]
	bx	lr
.endfunc
.func NVRAM_Init, NVRAM_INIT
NVRAM_INIT:
	ldr	r1, =SP_BASE
	ldr	r0, [r1, #SP_RDR]
	mov	r0, #NVRAM_CMD_RDSR
	str	r0, [r1, #SP_TDR]
SP_loop1:
	ldr	r0, [r1, #SP_SR]
	tst	r0, #SP_TDRE
	beq	SP_loop1

	mov	r0, #SPI_8CLOCKS
	str	r0, [r1, #SP_TDR]
SP_loop2:
	ldr	r0, [r1, #SP_SR]
	tst	r0, #SP_TDRE
	beq	SP_loop2

	ldr	r0, [r1, #SP_RDR]
SP_loop3:
	ldr	r0, [r1, #SP_SR]
	tst	r0, #SP_RDRF
	beq	SP_loop3

	ldr	r0, [r1, #SP_RDR]
	and	r0, r0, #255
	bx	lr
.endfunc

.func NVRAM_Xfer, NVRAM_XFER
	/* r0 = dest address */
	/* r1 = not used */
	/* r2 = src address within NVRAM */
	/* r3 = length */
NVRAM_XFER:
	sपंचांगdb	sp!, अणुr4, r5, lrपूर्ण
	mov	r5, r0		/* save r0 (dest address) */
	mov	r4, r3		/* save r3 (length) */
	mov	r0, r2, LSR #5 /*  SPI memories put A8 in the command field */
	and	r0, r0, #8
	add	r0, r0, #NVRAM_CMD_READ
	ldr	r1, =NVRAM_SCRATCH
	strb	r0, [r1, #0]	/* save command in NVRAM_SCRATCH[0] */
	strb	r2, [r1, #1]    /* save low byte of source address in NVRAM_SCRATCH[1] */
_local1:
	bl	NVRAM_INIT
	tst	r0, #NVRAM_SR_RDY
	bne	_local1
	mov	r0, #20
	bl	DELAY9
	mov	r2, r4		/* length */
	mov	r1, r5		/* dest address */
	mov	r0, #2		/* bytes to transfer in command */
	bl	NVRAM_XFER2
	ldmia	sp!, अणुr4, r5, lrपूर्ण
	bx	lr
.endfunc

.func NVRAM_Xfer2, NVRAM_XFER2
NVRAM_XFER2:
	sपंचांगdb	sp!, अणुr4, r5, r6, lrपूर्ण
	ldr	r4, =SP_BASE
	mov	r3, #0
	cmp	r0, #0
	bls	_local2
	ldr	r5, =NVRAM_SCRATCH
_local4:
	ldrb	r6, [r5, r3]
	str	r6, [r4, #SP_TDR]
_local3:
	ldr	r6, [r4, #SP_SR]
	tst	r6, #SP_TDRE
	beq	_local3
	add	r3, r3, #1
	cmp	r3, r0 /* r0 is # of bytes to send out (command+addr) */
	blo	_local4
_local2:
	mov	r3, #SPI_8CLOCKS
	str	r3, [r4, #SP_TDR]
	ldr	r0, [r4, #SP_RDR]
_local5:
	ldr	r0, [r4, #SP_SR]
	tst	r0, #SP_RDRF
	beq	_local5
	ldr	r0, [r4, #SP_RDR] /* what's this byte?  It's the byte read while writing the TDR -- nonsense, because the NVRAM doesn't पढ़ो and ग_लिखो at the same समय */
	mov	r0, #0
	cmp	r2, #0  /* r2 is # of bytes to copy in */
	bls	_local6
_local7:
	ldr	r5, [r4, #SP_SR]
	tst	r5, #SP_TDRE
	beq	_local7
	str	r3, [r4, #SP_TDR]  /* r3 has SPI_8CLOCKS */
_local8:
	ldr	r5, [r4, #SP_SR]
	tst	r5, #SP_RDRF
	beq	_local8
	ldr	r5, [r4, #SP_RDR] /* but didn't we पढ़ो this byte above? */
	strb	r5, [r1], #1 /* postindexed */
	add	r0, r0, #1
	cmp	r0, r2
	blo	_local7 /* since we करोn't send another address, the NVRAM must be capable of sequential पढ़ोs */
_local6:
	mov	r0, #200
	bl	DELAY9
	ldmia	sp!, अणुr4, r5, r6, lrपूर्ण
	bx	lr
#पूर्ण_अगर
