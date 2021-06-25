<शैली गुरु>
/*======================================================================

    Aironet driver क्रम 4500 and 4800 series cards

    This code is released under both the GPL version 2 and BSD licenses.
    Either license may be used.  The respective licenses are found at
    the end of this file.

    This code was developed by Benjamin Reed <breed@users.sourceक्रमge.net>
    including portions of which come from the Aironet PC4500
    Developer's Reference Manual and used with permission.  Copyright
    (C) 1999 Benjamin Reed.  All Rights Reserved.  Permission to use
    code in the Developer's manual was granted क्रम this driver by
    Aironet.  Major code contributions were received from Javier Achirica
    <achirica@users.sourceक्रमge.net> and Jean Tourrilhes <jt@hpl.hp.com>.
    Code was also पूर्णांकegrated from the Cisco Aironet driver क्रम Linux.
    Support क्रम MPI350 cards was added by Fabrice Bellet
    <fabrice@bellet.info>.

======================================================================*/

#समावेश <linux/err.h>
#समावेश <linux/init.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>

#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/bitops.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/skcipher.h>

#समावेश <net/cfg80211.h>
#समावेश <net/iw_handler.h>

#समावेश "airo.h"

#घोषणा DRV_NAME "airo"

#अगर_घोषित CONFIG_PCI
अटल स्थिर काष्ठा pci_device_id card_ids[] = अणु
	अणु 0x14b9, 1, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0x14b9, 0x4500, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0x14b9, 0x4800, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0x14b9, 0x0340, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0x14b9, 0x0350, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0x14b9, 0x5000, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0x14b9, 0xa504, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, card_ids);

अटल पूर्णांक airo_pci_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम airo_pci_हटाओ(काष्ठा pci_dev *);
अटल पूर्णांक __maybe_unused airo_pci_suspend(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused airo_pci_resume(काष्ठा device *dev);

अटल SIMPLE_DEV_PM_OPS(airo_pci_pm_ops,
			 airo_pci_suspend,
			 airo_pci_resume);

अटल काष्ठा pci_driver airo_driver = अणु
	.name      = DRV_NAME,
	.id_table  = card_ids,
	.probe     = airo_pci_probe,
	.हटाओ    = airo_pci_हटाओ,
	.driver.pm = &airo_pci_pm_ops,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI */

/* Include Wireless Extension definition and check version - Jean II */
#समावेश <linux/wireless.h>
#घोषणा WIRELESS_SPY		/* enable iwspy support */

#घोषणा CISCO_EXT		/* enable Cisco extensions */
#अगर_घोषित CISCO_EXT
#समावेश <linux/delay.h>
#पूर्ण_अगर

/* Hack to करो some घातer saving */
#घोषणा POWER_ON_DOWN

/* As you can see this list is HUGH!
   I really करोn't know what a lot of these counts are about, but they
   are all here क्रम completeness.  If the IGNLABEL macro is put in
   infront of the label, that statistic will not be included in the list
   of statistics in the /proc fileप्रणाली */

#घोषणा IGNLABEL(comment) शून्य
अटल स्थिर अक्षर *statsLabels[] = अणु
	"RxOverrun",
	IGNLABEL("RxPlcpCrcErr"),
	IGNLABEL("RxPlcpFormatErr"),
	IGNLABEL("RxPlcpLengthErr"),
	"RxMacCrcErr",
	"RxMacCrcOk",
	"RxWepErr",
	"RxWepOk",
	"RetryLong",
	"RetryShort",
	"MaxRetries",
	"NoAck",
	"NoCts",
	"RxAck",
	"RxCts",
	"TxAck",
	"TxRts",
	"TxCts",
	"TxMc",
	"TxBc",
	"TxUcFrags",
	"TxUcPackets",
	"TxBeacon",
	"RxBeacon",
	"TxSinColl",
	"TxMulColl",
	"DefersNo",
	"DefersProt",
	"DefersEngy",
	"DupFram",
	"RxFragDisc",
	"TxAged",
	"RxAged",
	"LostSync-MaxRetry",
	"LostSync-MissedBeacons",
	"LostSync-ArlExceeded",
	"LostSync-Deauth",
	"LostSync-Disassoced",
	"LostSync-TsfTiming",
	"HostTxMc",
	"HostTxBc",
	"HostTxUc",
	"HostTxFail",
	"HostRxMc",
	"HostRxBc",
	"HostRxUc",
	"HostRxDiscard",
	IGNLABEL("HmacTxMc"),
	IGNLABEL("HmacTxBc"),
	IGNLABEL("HmacTxUc"),
	IGNLABEL("HmacTxFail"),
	IGNLABEL("HmacRxMc"),
	IGNLABEL("HmacRxBc"),
	IGNLABEL("HmacRxUc"),
	IGNLABEL("HmacRxDiscard"),
	IGNLABEL("HmacRxAccepted"),
	"SsidMismatch",
	"ApMismatch",
	"RatesMismatch",
	"AuthReject",
	"AuthTimeout",
	"AssocReject",
	"AssocTimeout",
	IGNLABEL("ReasonOutsideTable"),
	IGNLABEL("ReasonStatus1"),
	IGNLABEL("ReasonStatus2"),
	IGNLABEL("ReasonStatus3"),
	IGNLABEL("ReasonStatus4"),
	IGNLABEL("ReasonStatus5"),
	IGNLABEL("ReasonStatus6"),
	IGNLABEL("ReasonStatus7"),
	IGNLABEL("ReasonStatus8"),
	IGNLABEL("ReasonStatus9"),
	IGNLABEL("ReasonStatus10"),
	IGNLABEL("ReasonStatus11"),
	IGNLABEL("ReasonStatus12"),
	IGNLABEL("ReasonStatus13"),
	IGNLABEL("ReasonStatus14"),
	IGNLABEL("ReasonStatus15"),
	IGNLABEL("ReasonStatus16"),
	IGNLABEL("ReasonStatus17"),
	IGNLABEL("ReasonStatus18"),
	IGNLABEL("ReasonStatus19"),
	"RxMan",
	"TxMan",
	"RxRefresh",
	"TxRefresh",
	"RxPoll",
	"TxPoll",
	"HostRetries",
	"LostSync-HostReq",
	"HostTxBytes",
	"HostRxBytes",
	"ElapsedUsec",
	"ElapsedSec",
	"LostSyncBetterAP",
	"PrivacyMismatch",
	"Jammed",
	"DiscRxNotWepped",
	"PhyEleMismatch",
	(अक्षर*)-1 पूर्ण;
#अगर_अघोषित RUN_AT
#घोषणा RUN_AT(x) (jअगरfies+(x))
#पूर्ण_अगर


/* These variables are क्रम insmod, since it seems that the rates
   can only be set in setup_card.  Rates should be a comma separated
   (no spaces) list of rates (up to 8). */

अटल पूर्णांक rates[8];
अटल अक्षर *ssids[3];

अटल पूर्णांक io[4];
अटल पूर्णांक irq[4];

अटल
पूर्णांक maxencrypt /* = 0 */; /* The highest rate that the card can encrypt at.
		       0 means no limit.  For old cards this was 4 */

अटल पूर्णांक स्वतः_wep /* = 0 */; /* If set, it tries to figure out the wep mode */
अटल पूर्णांक aux_bap /* = 0 */; /* Checks to see अगर the aux ports are needed to पढ़ो
		    the bap, needed on some older cards and buses. */
अटल पूर्णांक adhoc;

अटल पूर्णांक probe = 1;

अटल kuid_t proc_kuid;
अटल पूर्णांक proc_uid /* = 0 */;

अटल kgid_t proc_kgid;
अटल पूर्णांक proc_gid /* = 0 */;

अटल पूर्णांक airo_perm = 0555;

अटल पूर्णांक proc_perm = 0644;

MODULE_AUTHOR("Benjamin Reed");
MODULE_DESCRIPTION("Support for Cisco/Aironet 802.11 wireless ethernet cards.  "
		   "Direct support for ISA/PCI/MPI cards and support for PCMCIA when used with airo_cs.");
MODULE_LICENSE("Dual BSD/GPL");
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_array(rates, पूर्णांक, शून्य, 0);
module_param_array(ssids, अक्षरp, शून्य, 0);
module_param(स्वतः_wep, पूर्णांक, 0);
MODULE_PARM_DESC(स्वतः_wep,
		 "If non-zero, the driver will keep looping through the authentication options until an association is made.  "
		 "The value of auto_wep is number of the wep keys to check.  "
		 "A value of 2 will try using the key at index 0 and index 1.");
module_param(aux_bap, पूर्णांक, 0);
MODULE_PARM_DESC(aux_bap,
		 "If non-zero, the driver will switch into a mode that seems to work better for older cards with some older buses.  "
		 "Before switching it checks that the switch is needed.");
module_param(maxencrypt, पूर्णांक, 0);
MODULE_PARM_DESC(maxencrypt,
		 "The maximum speed that the card can do encryption.  "
		 "Units are in 512kbs.  "
		 "Zero (default) means there is no limit.  "
		 "Older cards used to be limited to 2mbs (4).");
module_param(adhoc, पूर्णांक, 0);
MODULE_PARM_DESC(adhoc, "If non-zero, the card will start in adhoc mode.");
module_param(probe, पूर्णांक, 0);
MODULE_PARM_DESC(probe, "If zero, the driver won't start the card.");

module_param(proc_uid, पूर्णांक, 0);
MODULE_PARM_DESC(proc_uid, "The uid that the /proc files will belong to.");
module_param(proc_gid, पूर्णांक, 0);
MODULE_PARM_DESC(proc_gid, "The gid that the /proc files will belong to.");
module_param(airo_perm, पूर्णांक, 0);
MODULE_PARM_DESC(airo_perm, "The permission bits of /proc/[driver/]aironet.");
module_param(proc_perm, पूर्णांक, 0);
MODULE_PARM_DESC(proc_perm, "The permission bits of the files in /proc");

/* This is a kind of sloppy hack to get this inक्रमmation to OUT4500 and
   IN4500.  I would be extremely पूर्णांकerested in the situation where this
   करोesn't work though!!! */
अटल पूर्णांक करो8bitIO /* = 0 */;

/* Return codes */
#घोषणा SUCCESS 0
#घोषणा ERROR -1
#घोषणा NO_PACKET -2

/* Commands */
#घोषणा NOP2		0x0000
#घोषणा MAC_ENABLE	0x0001
#घोषणा MAC_DISABLE	0x0002
#घोषणा CMD_LOSE_SYNC	0x0003 /* Not sure what this करोes... */
#घोषणा CMD_SOFTRESET	0x0004
#घोषणा HOSTSLEEP	0x0005
#घोषणा CMD_MAGIC_PKT	0x0006
#घोषणा CMD_SETWAKEMASK	0x0007
#घोषणा CMD_READCFG	0x0008
#घोषणा CMD_SETMODE	0x0009
#घोषणा CMD_ALLOCATETX	0x000a
#घोषणा CMD_TRANSMIT	0x000b
#घोषणा CMD_DEALLOCATETX 0x000c
#घोषणा NOP		0x0010
#घोषणा CMD_WORKAROUND	0x0011
#घोषणा CMD_ALLOCATEAUX 0x0020
#घोषणा CMD_ACCESS	0x0021
#घोषणा CMD_PCIBAP	0x0022
#घोषणा CMD_PCIAUX	0x0023
#घोषणा CMD_ALLOCBUF	0x0028
#घोषणा CMD_GETTLV	0x0029
#घोषणा CMD_PUTTLV	0x002a
#घोषणा CMD_DELTLV	0x002b
#घोषणा CMD_FINDNEXTTLV	0x002c
#घोषणा CMD_PSPNODES	0x0030
#घोषणा CMD_SETCW	0x0031
#घोषणा CMD_SETPCF	0x0032
#घोषणा CMD_SETPHYREG	0x003e
#घोषणा CMD_TXTEST	0x003f
#घोषणा MAC_ENABLETX	0x0101
#घोषणा CMD_LISTBSS	0x0103
#घोषणा CMD_SAVECFG	0x0108
#घोषणा CMD_ENABLEAUX	0x0111
#घोषणा CMD_WRITERID	0x0121
#घोषणा CMD_USEPSPNODES	0x0130
#घोषणा MAC_ENABLERX	0x0201

/* Command errors */
#घोषणा ERROR_QUALIF 0x00
#घोषणा ERROR_ILLCMD 0x01
#घोषणा ERROR_ILLFMT 0x02
#घोषणा ERROR_INVFID 0x03
#घोषणा ERROR_INVRID 0x04
#घोषणा ERROR_LARGE 0x05
#घोषणा ERROR_NDISABL 0x06
#घोषणा ERROR_ALLOCBSY 0x07
#घोषणा ERROR_NORD 0x0B
#घोषणा ERROR_NOWR 0x0C
#घोषणा ERROR_INVFIDTX 0x0D
#घोषणा ERROR_TESTACT 0x0E
#घोषणा ERROR_TAGNFND 0x12
#घोषणा ERROR_DECODE 0x20
#घोषणा ERROR_DESCUNAV 0x21
#घोषणा ERROR_BADLEN 0x22
#घोषणा ERROR_MODE 0x80
#घोषणा ERROR_HOP 0x81
#घोषणा ERROR_BINTER 0x82
#घोषणा ERROR_RXMODE 0x83
#घोषणा ERROR_MACADDR 0x84
#घोषणा ERROR_RATES 0x85
#घोषणा ERROR_ORDER 0x86
#घोषणा ERROR_SCAN 0x87
#घोषणा ERROR_AUTH 0x88
#घोषणा ERROR_PSMODE 0x89
#घोषणा ERROR_RTYPE 0x8A
#घोषणा ERROR_DIVER 0x8B
#घोषणा ERROR_SSID 0x8C
#घोषणा ERROR_APLIST 0x8D
#घोषणा ERROR_AUTOWAKE 0x8E
#घोषणा ERROR_LEAP 0x8F

/* Registers */
#घोषणा COMMAND 0x00
#घोषणा PARAM0 0x02
#घोषणा PARAM1 0x04
#घोषणा PARAM2 0x06
#घोषणा STATUS 0x08
#घोषणा RESP0 0x0a
#घोषणा RESP1 0x0c
#घोषणा RESP2 0x0e
#घोषणा LINKSTAT 0x10
#घोषणा SELECT0 0x18
#घोषणा OFFSET0 0x1c
#घोषणा RXFID 0x20
#घोषणा TXALLOCFID 0x22
#घोषणा TXCOMPLFID 0x24
#घोषणा DATA0 0x36
#घोषणा EVSTAT 0x30
#घोषणा EVINTEN 0x32
#घोषणा EVACK 0x34
#घोषणा SWS0 0x28
#घोषणा SWS1 0x2a
#घोषणा SWS2 0x2c
#घोषणा SWS3 0x2e
#घोषणा AUXPAGE 0x3A
#घोषणा AUXOFF 0x3C
#घोषणा AUXDATA 0x3E

#घोषणा FID_TX 1
#घोषणा FID_RX 2
/* Offset पूर्णांकo aux memory क्रम descriptors */
#घोषणा AUX_OFFSET 0x800
/* Size of allocated packets */
#घोषणा PKTSIZE 1840
#घोषणा RIDSIZE 2048
/* Size of the transmit queue */
#घोषणा MAXTXQ 64

/* BAP selectors */
#घोषणा BAP0 0 /* Used क्रम receiving packets */
#घोषणा BAP1 2 /* Used क्रम xmiting packets and working with RIDS */

/* Flags */
#घोषणा COMMAND_BUSY 0x8000

#घोषणा BAP_BUSY 0x8000
#घोषणा BAP_ERR 0x4000
#घोषणा BAP_DONE 0x2000

#घोषणा PROMISC 0xffff
#घोषणा NOPROMISC 0x0000

#घोषणा EV_CMD 0x10
#घोषणा EV_CLEARCOMMANDBUSY 0x4000
#घोषणा EV_RX 0x01
#घोषणा EV_TX 0x02
#घोषणा EV_TXEXC 0x04
#घोषणा EV_ALLOC 0x08
#घोषणा EV_LINK 0x80
#घोषणा EV_AWAKE 0x100
#घोषणा EV_TXCPY 0x400
#घोषणा EV_UNKNOWN 0x800
#घोषणा EV_MIC 0x1000 /* Message Integrity Check Interrupt */
#घोषणा EV_AWAKEN 0x2000
#घोषणा STATUS_INTS (EV_AWAKE|EV_LINK|EV_TXEXC|EV_TX|EV_TXCPY|EV_RX|EV_MIC)

#अगर_घोषित CHECK_UNKNOWN_INTS
#घोषणा IGNORE_INTS (EV_CMD | EV_UNKNOWN)
#अन्यथा
#घोषणा IGNORE_INTS (~STATUS_INTS)
#पूर्ण_अगर

/* RID TYPES */
#घोषणा RID_RW 0x20

/* The RIDs */
#घोषणा RID_CAPABILITIES 0xFF00
#घोषणा RID_APINFO     0xFF01
#घोषणा RID_RADIOINFO  0xFF02
#घोषणा RID_UNKNOWN3   0xFF03
#घोषणा RID_RSSI       0xFF04
#घोषणा RID_CONFIG     0xFF10
#घोषणा RID_SSID       0xFF11
#घोषणा RID_APLIST     0xFF12
#घोषणा RID_DRVNAME    0xFF13
#घोषणा RID_ETHERENCAP 0xFF14
#घोषणा RID_WEP_TEMP   0xFF15
#घोषणा RID_WEP_PERM   0xFF16
#घोषणा RID_MODULATION 0xFF17
#घोषणा RID_OPTIONS    0xFF18
#घोषणा RID_ACTUALCONFIG 0xFF20 /*पढ़ोonly*/
#घोषणा RID_FACTORYCONFIG 0xFF21
#घोषणा RID_UNKNOWN22  0xFF22
#घोषणा RID_LEAPUSERNAME 0xFF23
#घोषणा RID_LEAPPASSWORD 0xFF24
#घोषणा RID_STATUS     0xFF50
#घोषणा RID_BEACON_HST 0xFF51
#घोषणा RID_BUSY_HST   0xFF52
#घोषणा RID_RETRIES_HST 0xFF53
#घोषणा RID_UNKNOWN54  0xFF54
#घोषणा RID_UNKNOWN55  0xFF55
#घोषणा RID_UNKNOWN56  0xFF56
#घोषणा RID_MIC        0xFF57
#घोषणा RID_STATS16    0xFF60
#घोषणा RID_STATS16DELTA 0xFF61
#घोषणा RID_STATS16DELTACLEAR 0xFF62
#घोषणा RID_STATS      0xFF68
#घोषणा RID_STATSDELTA 0xFF69
#घोषणा RID_STATSDELTACLEAR 0xFF6A
#घोषणा RID_ECHOTEST_RID 0xFF70
#घोषणा RID_ECHOTEST_RESULTS 0xFF71
#घोषणा RID_BSSLISTFIRST 0xFF72
#घोषणा RID_BSSLISTNEXT  0xFF73
#घोषणा RID_WPA_BSSLISTFIRST 0xFF74
#घोषणा RID_WPA_BSSLISTNEXT  0xFF75

प्रकार काष्ठा अणु
	u16 cmd;
	u16 parm0;
	u16 parm1;
	u16 parm2;
पूर्ण Cmd;

प्रकार काष्ठा अणु
	u16 status;
	u16 rsp0;
	u16 rsp1;
	u16 rsp2;
पूर्ण Resp;

/*
 * Rids and endian-ness:  The Rids will always be in cpu endian, since
 * this all the patches from the big-endian guys end up करोing that.
 * so all rid access should use the पढ़ो/ग_लिखोXXXRid routines.
 */

/* This काष्ठाure came from an email sent to me from an engineer at
   aironet क्रम inclusion पूर्णांकo this driver */
प्रकार काष्ठा WepKeyRid WepKeyRid;
काष्ठा WepKeyRid अणु
	__le16 len;
	__le16 kindex;
	u8 mac[ETH_ALEN];
	__le16 klen;
	u8 key[16];
पूर्ण __packed;

/* These काष्ठाures are from the Aironet's PC4500 Developers Manual */
प्रकार काष्ठा Ssid Ssid;
काष्ठा Ssid अणु
	__le16 len;
	u8 ssid[32];
पूर्ण __packed;

प्रकार काष्ठा SsidRid SsidRid;
काष्ठा SsidRid अणु
	__le16 len;
	Ssid ssids[3];
पूर्ण __packed;

प्रकार काष्ठा ModulationRid ModulationRid;
काष्ठा ModulationRid अणु
        __le16 len;
        __le16 modulation;
#घोषणा MOD_DEFAULT cpu_to_le16(0)
#घोषणा MOD_CCK cpu_to_le16(1)
#घोषणा MOD_MOK cpu_to_le16(2)
पूर्ण __packed;

प्रकार काष्ठा ConfigRid ConfigRid;
काष्ठा ConfigRid अणु
	__le16 len; /* माप(ConfigRid) */
	__le16 opmode; /* operating mode */
#घोषणा MODE_STA_IBSS cpu_to_le16(0)
#घोषणा MODE_STA_ESS cpu_to_le16(1)
#घोषणा MODE_AP cpu_to_le16(2)
#घोषणा MODE_AP_RPTR cpu_to_le16(3)
#घोषणा MODE_CFG_MASK cpu_to_le16(0xff)
#घोषणा MODE_ETHERNET_HOST cpu_to_le16(0<<8) /* rx payloads converted */
#घोषणा MODE_LLC_HOST cpu_to_le16(1<<8) /* rx payloads left as is */
#घोषणा MODE_AIRONET_EXTEND cpu_to_le16(1<<9) /* enable Aironet extenstions */
#घोषणा MODE_AP_INTERFACE cpu_to_le16(1<<10) /* enable ap पूर्णांकerface extensions */
#घोषणा MODE_ANTENNA_ALIGN cpu_to_le16(1<<11) /* enable antenna alignment */
#घोषणा MODE_ETHER_LLC cpu_to_le16(1<<12) /* enable ethernet LLC */
#घोषणा MODE_LEAF_NODE cpu_to_le16(1<<13) /* enable leaf node bridge */
#घोषणा MODE_CF_POLLABLE cpu_to_le16(1<<14) /* enable CF pollable */
#घोषणा MODE_MIC cpu_to_le16(1<<15) /* enable MIC */
	__le16 rmode; /* receive mode */
#घोषणा RXMODE_BC_MC_ADDR cpu_to_le16(0)
#घोषणा RXMODE_BC_ADDR cpu_to_le16(1) /* ignore multicasts */
#घोषणा RXMODE_ADDR cpu_to_le16(2) /* ignore multicast and broadcast */
#घोषणा RXMODE_RFMON cpu_to_le16(3) /* wireless monitor mode */
#घोषणा RXMODE_RFMON_ANYBSS cpu_to_le16(4)
#घोषणा RXMODE_LANMON cpu_to_le16(5) /* lan style monitor -- data packets only */
#घोषणा RXMODE_MASK cpu_to_le16(255)
#घोषणा RXMODE_DISABLE_802_3_HEADER cpu_to_le16(1<<8) /* disables 802.3 header on rx */
#घोषणा RXMODE_FULL_MASK (RXMODE_MASK | RXMODE_DISABLE_802_3_HEADER)
#घोषणा RXMODE_NORMALIZED_RSSI cpu_to_le16(1<<9) /* वापस normalized RSSI */
	__le16 fragThresh;
	__le16 rtsThres;
	u8 macAddr[ETH_ALEN];
	u8 rates[8];
	__le16 लघुRetryLimit;
	__le16 दीर्घRetryLimit;
	__le16 txLअगरeसमय; /* in kusec */
	__le16 rxLअगरeसमय; /* in kusec */
	__le16 stationary;
	__le16 ordering;
	__le16 u16deviceType; /* क्रम overriding device type */
	__le16 cfpRate;
	__le16 cfpDuration;
	__le16 _reserved1[3];
	/*---------- Scanning/Associating ----------*/
	__le16 scanMode;
#घोषणा SCANMODE_ACTIVE cpu_to_le16(0)
#घोषणा SCANMODE_PASSIVE cpu_to_le16(1)
#घोषणा SCANMODE_AIROSCAN cpu_to_le16(2)
	__le16 probeDelay; /* in kusec */
	__le16 probeEnergyTimeout; /* in kusec */
        __le16 probeResponseTimeout;
	__le16 beaconListenTimeout;
	__le16 joinNetTimeout;
	__le16 authTimeout;
	__le16 authType;
#घोषणा AUTH_OPEN cpu_to_le16(0x1)
#घोषणा AUTH_ENCRYPT cpu_to_le16(0x101)
#घोषणा AUTH_SHAREDKEY cpu_to_le16(0x102)
#घोषणा AUTH_ALLOW_UNENCRYPTED cpu_to_le16(0x200)
	__le16 associationTimeout;
	__le16 specअगरiedApTimeout;
	__le16 offlineScanInterval;
	__le16 offlineScanDuration;
	__le16 linkLossDelay;
	__le16 maxBeaconLostTime;
	__le16 refreshInterval;
#घोषणा DISABLE_REFRESH cpu_to_le16(0xFFFF)
	__le16 _reserved1a[1];
	/*---------- Power save operation ----------*/
	__le16 घातerSaveMode;
#घोषणा POWERSAVE_CAM cpu_to_le16(0)
#घोषणा POWERSAVE_PSP cpu_to_le16(1)
#घोषणा POWERSAVE_PSPCAM cpu_to_le16(2)
	__le16 sleepForDtims;
	__le16 listenInterval;
	__le16 fastListenInterval;
	__le16 listenDecay;
	__le16 fastListenDelay;
	__le16 _reserved2[2];
	/*---------- Ap/Ibss config items ----------*/
	__le16 beaconPeriod;
	__le16 atimDuration;
	__le16 hopPeriod;
	__le16 channelSet;
	__le16 channel;
	__le16 dtimPeriod;
	__le16 bridgeDistance;
	__le16 radioID;
	/*---------- Radio configuration ----------*/
	__le16 radioType;
#घोषणा RADIOTYPE_DEFAULT cpu_to_le16(0)
#घोषणा RADIOTYPE_802_11 cpu_to_le16(1)
#घोषणा RADIOTYPE_LEGACY cpu_to_le16(2)
	u8 rxDiversity;
	u8 txDiversity;
	__le16 txPower;
#घोषणा TXPOWER_DEFAULT 0
	__le16 rssiThreshold;
#घोषणा RSSI_DEFAULT 0
        __le16 modulation;
#घोषणा PREAMBLE_AUTO cpu_to_le16(0)
#घोषणा PREAMBLE_LONG cpu_to_le16(1)
#घोषणा PREAMBLE_SHORT cpu_to_le16(2)
	__le16 preamble;
	__le16 homeProduct;
	__le16 radioSpecअगरic;
	/*---------- Aironet Extensions ----------*/
	u8 nodeName[16];
	__le16 arlThreshold;
	__le16 arlDecay;
	__le16 arlDelay;
	__le16 _reserved4[1];
	/*---------- Aironet Extensions ----------*/
	u8 magicAction;
#घोषणा MAGIC_ACTION_STSCHG 1
#घोषणा MAGIC_ACTION_RESUME 2
#घोषणा MAGIC_IGNORE_MCAST (1<<8)
#घोषणा MAGIC_IGNORE_BCAST (1<<9)
#घोषणा MAGIC_SWITCH_TO_PSP (0<<10)
#घोषणा MAGIC_STAY_IN_CAM (1<<10)
	u8 magicControl;
	__le16 स्वतःWake;
पूर्ण __packed;

प्रकार काष्ठा StatusRid StatusRid;
काष्ठा StatusRid अणु
	__le16 len;
	u8 mac[ETH_ALEN];
	__le16 mode;
	__le16 errorCode;
	__le16 sigQuality;
	__le16 SSIDlen;
	अक्षर SSID[32];
	अक्षर apName[16];
	u8 bssid[4][ETH_ALEN];
	__le16 beaconPeriod;
	__le16 dimPeriod;
	__le16 atimDuration;
	__le16 hopPeriod;
	__le16 channelSet;
	__le16 channel;
	__le16 hopsToBackbone;
	__le16 apTotalLoad;
	__le16 generatedLoad;
	__le16 accumulatedArl;
	__le16 संकेतQuality;
	__le16 currentXmitRate;
	__le16 apDevExtensions;
	__le16 normalizedSignalStrength;
	__le16 लघुPreamble;
	u8 apIP[4];
	u8 noisePercent; /* Noise percent in last second */
	u8 noisedBm; /* Noise dBm in last second */
	u8 noiseAvePercent; /* Noise percent in last minute */
	u8 noiseAvedBm; /* Noise dBm in last minute */
	u8 noiseMaxPercent; /* Highest noise percent in last minute */
	u8 noiseMaxdBm; /* Highest noise dbm in last minute */
	__le16 load;
	u8 carrier[4];
	__le16 assocStatus;
#घोषणा STAT_NOPACKETS 0
#घोषणा STAT_NOCARRIERSET 10
#घोषणा STAT_GOTCARRIERSET 11
#घोषणा STAT_WRONGSSID 20
#घोषणा STAT_BADCHANNEL 25
#घोषणा STAT_BADBITRATES 30
#घोषणा STAT_BADPRIVACY 35
#घोषणा STAT_APFOUND 40
#घोषणा STAT_APREJECTED 50
#घोषणा STAT_AUTHENTICATING 60
#घोषणा STAT_DEAUTHENTICATED 61
#घोषणा STAT_AUTHTIMEOUT 62
#घोषणा STAT_ASSOCIATING 70
#घोषणा STAT_DEASSOCIATED 71
#घोषणा STAT_ASSOCTIMEOUT 72
#घोषणा STAT_NOTAIROAP 73
#घोषणा STAT_ASSOCIATED 80
#घोषणा STAT_LEAPING 90
#घोषणा STAT_LEAPFAILED 91
#घोषणा STAT_LEAPTIMEDOUT 92
#घोषणा STAT_LEAPCOMPLETE 93
पूर्ण __packed;

प्रकार काष्ठा StatsRid StatsRid;
काष्ठा StatsRid अणु
	__le16 len;
	__le16 spacer;
	__le32 vals[100];
पूर्ण __packed;

प्रकार काष्ठा APListRid APListRid;
काष्ठा APListRid अणु
	__le16 len;
	u8 ap[4][ETH_ALEN];
पूर्ण __packed;

प्रकार काष्ठा CapabilityRid CapabilityRid;
काष्ठा CapabilityRid अणु
	__le16 len;
	अक्षर oui[3];
	अक्षर zero;
	__le16 prodNum;
	अक्षर manName[32];
	अक्षर prodName[16];
	अक्षर prodVer[8];
	अक्षर factoryAddr[ETH_ALEN];
	अक्षर aironetAddr[ETH_ALEN];
	__le16 radioType;
	__le16 country;
	अक्षर callid[ETH_ALEN];
	अक्षर supportedRates[8];
	अक्षर rxDiversity;
	अक्षर txDiversity;
	__le16 txPowerLevels[8];
	__le16 hardVer;
	__le16 hardCap;
	__le16 tempRange;
	__le16 softVer;
	__le16 softSubVer;
	__le16 पूर्णांकerfaceVer;
	__le16 softCap;
	__le16 bootBlockVer;
	__le16 requiredHard;
	__le16 extSoftCap;
पूर्ण __packed;

/* Only present on firmware >= 5.30.17 */
प्रकार काष्ठा BSSListRidExtra BSSListRidExtra;
काष्ठा BSSListRidExtra अणु
  __le16 unknown[4];
  u8 fixed[12]; /* WLAN management frame */
  u8 iep[624];
पूर्ण __packed;

प्रकार काष्ठा BSSListRid BSSListRid;
काष्ठा BSSListRid अणु
  __le16 len;
  __le16 index; /* First is 0 and 0xffff means end of list */
#घोषणा RADIO_FH 1 /* Frequency hopping radio type */
#घोषणा RADIO_DS 2 /* Direct sequence radio type */
#घोषणा RADIO_TMA 4 /* Proprietary radio used in old cards (2500) */
  __le16 radioType;
  u8 bssid[ETH_ALEN]; /* Mac address of the BSS */
  u8 zero;
  u8 ssidLen;
  u8 ssid[32];
  __le16 dBm;
#घोषणा CAP_ESS cpu_to_le16(1<<0)
#घोषणा CAP_IBSS cpu_to_le16(1<<1)
#घोषणा CAP_PRIVACY cpu_to_le16(1<<4)
#घोषणा CAP_SHORTHDR cpu_to_le16(1<<5)
  __le16 cap;
  __le16 beaconInterval;
  u8 rates[8]; /* Same as rates क्रम config rid */
  काष्ठा अणु /* For frequency hopping only */
    __le16 dwell;
    u8 hopSet;
    u8 hopPattern;
    u8 hopIndex;
    u8 fill;
  पूर्ण fh;
  __le16 dsChannel;
  __le16 atimWinकरोw;

  /* Only present on firmware >= 5.30.17 */
  BSSListRidExtra extra;
पूर्ण __packed;

प्रकार काष्ठा अणु
  BSSListRid bss;
  काष्ठा list_head list;
पूर्ण BSSListElement;

प्रकार काष्ठा tdsRssiEntry tdsRssiEntry;
काष्ठा tdsRssiEntry अणु
  u8 rssipct;
  u8 rssidBm;
पूर्ण __packed;

प्रकार काष्ठा tdsRssiRid tdsRssiRid;
काष्ठा tdsRssiRid अणु
  u16 len;
  tdsRssiEntry x[256];
पूर्ण __packed;

प्रकार काष्ठा MICRid MICRid;
काष्ठा MICRid अणु
	__le16 len;
	__le16 state;
	__le16 multicastValid;
	u8  multicast[16];
	__le16 unicastValid;
	u8  unicast[16];
पूर्ण __packed;

प्रकार काष्ठा MICBuffer MICBuffer;
काष्ठा MICBuffer अणु
	__be16 typelen;

	जोड़ अणु
	    u8 snap[8];
	    काष्ठा अणु
		u8 dsap;
		u8 ssap;
		u8 control;
		u8 orgcode[3];
		u8 fieldtype[2];
	    पूर्ण llc;
	पूर्ण u;
	__be32 mic;
	__be32 seq;
पूर्ण __packed;

प्रकार काष्ठा अणु
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
पूर्ण etherHead;

#घोषणा TXCTL_TXOK (1<<1) /* report अगर tx is ok */
#घोषणा TXCTL_TXEX (1<<2) /* report अगर tx fails */
#घोषणा TXCTL_802_3 (0<<3) /* 802.3 packet */
#घोषणा TXCTL_802_11 (1<<3) /* 802.11 mac packet */
#घोषणा TXCTL_ETHERNET (0<<4) /* payload has ethertype */
#घोषणा TXCTL_LLC (1<<4) /* payload is llc */
#घोषणा TXCTL_RELEASE (0<<5) /* release after completion */
#घोषणा TXCTL_NORELEASE (1<<5) /* on completion वापसs to host */

#घोषणा BUSY_FID 0x10000

#अगर_घोषित CISCO_EXT
#घोषणा AIROMAGIC	0xa55a
/* Warning : SIOCDEVPRIVATE may disapear during 2.5.X - Jean II */
#अगर_घोषित SIOCIWFIRSTPRIV
#अगर_घोषित SIOCDEVPRIVATE
#घोषणा AIROOLDIOCTL	SIOCDEVPRIVATE
#घोषणा AIROOLDIDIFC 	AIROOLDIOCTL + 1
#पूर्ण_अगर /* SIOCDEVPRIVATE */
#अन्यथा /* SIOCIWFIRSTPRIV */
#घोषणा SIOCIWFIRSTPRIV SIOCDEVPRIVATE
#पूर्ण_अगर /* SIOCIWFIRSTPRIV */
/* This may be wrong. When using the new SIOCIWFIRSTPRIV range, we probably
 * should use only "GET" ioctls (last bit set to 1). "SET" ioctls are root
 * only and करोn't वापस the modअगरied काष्ठा अगरreq to the application which
 * is usually a problem. - Jean II */
#घोषणा AIROIOCTL	SIOCIWFIRSTPRIV
#घोषणा AIROIDIFC 	AIROIOCTL + 1

/* Ioctl स्थिरants to be used in airo_ioctl.command */

#घोषणा	AIROGCAP  		0	// Capability rid
#घोषणा AIROGCFG		1       // USED A LOT
#घोषणा AIROGSLIST		2	// System ID list
#घोषणा AIROGVLIST		3       // List of specअगरied AP's
#घोषणा AIROGDRVNAM		4	//  NOTUSED
#घोषणा AIROGEHTENC		5	// NOTUSED
#घोषणा AIROGWEPKTMP		6
#घोषणा AIROGWEPKNV		7
#घोषणा AIROGSTAT		8
#घोषणा AIROGSTATSC32		9
#घोषणा AIROGSTATSD32		10
#घोषणा AIROGMICRID		11
#घोषणा AIROGMICSTATS		12
#घोषणा AIROGFLAGS		13
#घोषणा AIROGID			14
#घोषणा AIRORRID		15
#घोषणा AIRORSWVERSION		17

/* Leave gap of 40 commands after AIROGSTATSD32 क्रम future */

#घोषणा AIROPCAP               	AIROGSTATSD32 + 40
#घोषणा AIROPVLIST              AIROPCAP      + 1
#घोषणा AIROPSLIST		AIROPVLIST    + 1
#घोषणा AIROPCFG		AIROPSLIST    + 1
#घोषणा AIROPSIDS		AIROPCFG      + 1
#घोषणा AIROPAPLIST		AIROPSIDS     + 1
#घोषणा AIROPMACON		AIROPAPLIST   + 1	/* Enable mac  */
#घोषणा AIROPMACOFF		AIROPMACON    + 1 	/* Disable mac */
#घोषणा AIROPSTCLR		AIROPMACOFF   + 1
#घोषणा AIROPWEPKEY		AIROPSTCLR    + 1
#घोषणा AIROPWEPKEYNV		AIROPWEPKEY   + 1
#घोषणा AIROPLEAPPWD            AIROPWEPKEYNV + 1
#घोषणा AIROPLEAPUSR            AIROPLEAPPWD  + 1

/* Flash codes */

#घोषणा AIROFLSHRST	       AIROPWEPKEYNV  + 40
#घोषणा AIROFLSHGCHR           AIROFLSHRST    + 1
#घोषणा AIROFLSHSTFL           AIROFLSHGCHR   + 1
#घोषणा AIROFLSHPCHR           AIROFLSHSTFL   + 1
#घोषणा AIROFLPUTBUF           AIROFLSHPCHR   + 1
#घोषणा AIRORESTART            AIROFLPUTBUF   + 1

#घोषणा FLASHSIZE	32768
#घोषणा AUXMEMSIZE	(256 * 1024)

प्रकार काष्ठा aironet_ioctl अणु
	अचिन्हित लघु command;		// What to करो
	अचिन्हित लघु len;		// Len of data
	अचिन्हित लघु ridnum;		// rid number
	अचिन्हित अक्षर __user *data;	// d-data
पूर्ण aironet_ioctl;

अटल स्थिर अक्षर swversion[] = "2.1";
#पूर्ण_अगर /* CISCO_EXT */

#घोषणा NUM_MODULES       2
#घोषणा MIC_MSGLEN_MAX    2400
#घोषणा EMMH32_MSGLEN_MAX MIC_MSGLEN_MAX
#घोषणा AIRO_DEF_MTU      2312

प्रकार काष्ठा अणु
	u32   size;            // size
	u8    enabled;         // MIC enabled or not
	u32   rxSuccess;       // successful packets received
	u32   rxIncorrectMIC;  // pkts dropped due to incorrect MIC comparison
	u32   rxNotMICed;      // pkts dropped due to not being MIC'd
	u32   rxMICPlummed;    // pkts dropped due to not having a MIC plummed
	u32   rxWrongSequence; // pkts dropped due to sequence number violation
	u32   reserve[32];
पूर्ण mic_statistics;

प्रकार काष्ठा अणु
	__be32 coeff[((EMMH32_MSGLEN_MAX)+3)>>2];
	u64 accum;	// accumulated mic, reduced to u32 in final()
	पूर्णांक position;	// current position (byte offset) in message
	जोड़ अणु
		u8  d8[4];
		__be32 d32;
	पूर्ण part;	// saves partial message word across update() calls
पूर्ण emmh32_context;

प्रकार काष्ठा अणु
	emmh32_context seed;	    // Context - the seed
	u32		 rx;	    // Received sequence number
	u32		 tx;	    // Tx sequence number
	u32		 winकरोw;    // Start of winकरोw
	u8		 valid;	    // Flag to say अगर context is valid or not
	u8		 key[16];
पूर्ण miccntx;

प्रकार काष्ठा अणु
	miccntx mCtx;		// Multicast context
	miccntx uCtx;		// Unicast context
पूर्ण mic_module;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक  rid: 16;
	अचिन्हित पूर्णांक  len: 15;
	अचिन्हित पूर्णांक  valid: 1;
	dma_addr_t host_addr;
पूर्ण Rid;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक  offset: 15;
	अचिन्हित पूर्णांक  eoc: 1;
	अचिन्हित पूर्णांक  len: 15;
	अचिन्हित पूर्णांक  valid: 1;
	dma_addr_t host_addr;
पूर्ण TxFid;

काष्ठा rx_hdr अणु
	__le16 status, len;
	u8 rssi[2];
	u8 rate;
	u8 freq;
	__le16 पंचांगp[4];
पूर्ण __packed;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक  ctl: 15;
	अचिन्हित पूर्णांक  rdy: 1;
	अचिन्हित पूर्णांक  len: 15;
	अचिन्हित पूर्णांक  valid: 1;
	dma_addr_t host_addr;
पूर्ण RxFid;

/*
 * Host receive descriptor
 */
प्रकार काष्ठा अणु
	अचिन्हित अक्षर __iomem *card_ram_off; /* offset पूर्णांकo card memory of the
						desc */
	RxFid         rx_desc;		     /* card receive descriptor */
	अक्षर          *भव_host_addr;    /* भव address of host receive
					        buffer */
	पूर्णांक           pending;
पूर्ण HostRxDesc;

/*
 * Host transmit descriptor
 */
प्रकार काष्ठा अणु
	अचिन्हित अक्षर __iomem *card_ram_off;	     /* offset पूर्णांकo card memory of the
						desc */
	TxFid         tx_desc;		     /* card transmit descriptor */
	अक्षर          *भव_host_addr;    /* भव address of host receive
					        buffer */
	पूर्णांक           pending;
पूर्ण HostTxDesc;

/*
 * Host RID descriptor
 */
प्रकार काष्ठा अणु
	अचिन्हित अक्षर __iomem *card_ram_off;      /* offset पूर्णांकo card memory of the
					     descriptor */
	Rid           rid_desc;		  /* card RID descriptor */
	अक्षर          *भव_host_addr; /* भव address of host receive
					     buffer */
पूर्ण HostRidDesc;

प्रकार काष्ठा अणु
	u16 sw0;
	u16 sw1;
	u16 status;
	u16 len;
#घोषणा HOST_SET (1 << 0)
#घोषणा HOST_INT_TX (1 << 1) /* Interrupt on successful TX */
#घोषणा HOST_INT_TXERR (1 << 2) /* Interrupt on unseccessful TX */
#घोषणा HOST_LCC_PAYLOAD (1 << 4) /* LLC payload, 0 = Ethertype */
#घोषणा HOST_DONT_RLSE (1 << 5) /* Don't release buffer when करोne */
#घोषणा HOST_DONT_RETRY (1 << 6) /* Don't retry trयंत्रit */
#घोषणा HOST_CLR_AID (1 << 7) /* clear AID failure */
#घोषणा HOST_RTS (1 << 9) /* Force RTS use */
#घोषणा HOST_SHORT (1 << 10) /* Do लघु preamble */
	u16 ctl;
	u16 aid;
	u16 retries;
	u16 fill;
पूर्ण TxCtlHdr;

प्रकार काष्ठा अणु
        u16 ctl;
        u16 duration;
        अक्षर addr1[6];
        अक्षर addr2[6];
        अक्षर addr3[6];
        u16 seq;
        अक्षर addr4[6];
पूर्ण WअगरiHdr;


प्रकार काष्ठा अणु
	TxCtlHdr ctlhdr;
	u16 fill1;
	u16 fill2;
	WअगरiHdr wअगरihdr;
	u16 gaplen;
	u16 status;
पूर्ण WअगरiCtlHdr;

अटल WअगरiCtlHdr wअगरictlhdr8023 = अणु
	.ctlhdr = अणु
		.ctl	= HOST_DONT_RLSE,
	पूर्ण
पूर्ण;

// A few details needed क्रम WEP (Wireless Equivalent Privacy)
#घोषणा MAX_KEY_SIZE 13			// 128 (?) bits
#घोषणा MIN_KEY_SIZE  5			// 40 bits RC4 - WEP
प्रकार काष्ठा wep_key_t अणु
	u16	len;
	u8	key[16];	/* 40-bit and 104-bit keys */
पूर्ण wep_key_t;

/* List of Wireless Handlers (new API) */
अटल स्थिर काष्ठा iw_handler_def	airo_handler_def;

अटल स्थिर अक्षर version[] = "airo.c 0.6 (Ben Reed & Javier Achirica)";

काष्ठा airo_info;

अटल पूर्णांक get_dec_u16(अक्षर *buffer, पूर्णांक *start, पूर्णांक limit);
अटल व्योम OUT4500(काष्ठा airo_info *, u16 reg, u16 value);
अटल अचिन्हित लघु IN4500(काष्ठा airo_info *, u16 reg);
अटल u16 setup_card(काष्ठा airo_info*, u8 *mac, पूर्णांक lock);
अटल पूर्णांक enable_MAC(काष्ठा airo_info *ai, पूर्णांक lock);
अटल व्योम disable_MAC(काष्ठा airo_info *ai, पूर्णांक lock);
अटल व्योम enable_पूर्णांकerrupts(काष्ठा airo_info*);
अटल व्योम disable_पूर्णांकerrupts(काष्ठा airo_info*);
अटल u16 issuecommand(काष्ठा airo_info*, Cmd *pCmd, Resp *pRsp,
			bool may_sleep);
अटल पूर्णांक bap_setup(काष्ठा airo_info*, u16 rid, u16 offset, पूर्णांक whichbap);
अटल पूर्णांक aux_bap_पढ़ो(काष्ठा airo_info*, __le16 *pu16Dst, पूर्णांक bytelen,
			पूर्णांक whichbap);
अटल पूर्णांक fast_bap_पढ़ो(काष्ठा airo_info*, __le16 *pu16Dst, पूर्णांक bytelen,
			 पूर्णांक whichbap);
अटल पूर्णांक bap_ग_लिखो(काष्ठा airo_info*, स्थिर __le16 *pu16Src, पूर्णांक bytelen,
		     पूर्णांक whichbap);
अटल पूर्णांक PC4500_accessrid(काष्ठा airo_info*, u16 rid, u16 accmd);
अटल पूर्णांक PC4500_पढ़ोrid(काष्ठा airo_info*, u16 rid, व्योम *pBuf, पूर्णांक len, पूर्णांक lock);
अटल पूर्णांक PC4500_ग_लिखोrid(काष्ठा airo_info*, u16 rid, स्थिर व्योम
			   *pBuf, पूर्णांक len, पूर्णांक lock);
अटल पूर्णांक करो_ग_लिखोrid(काष्ठा airo_info*, u16 rid, स्थिर व्योम *rid_data,
			पूर्णांक len, पूर्णांक dummy);
अटल u16 transmit_allocate(काष्ठा airo_info*, पूर्णांक lenPayload, पूर्णांक raw);
अटल पूर्णांक transmit_802_3_packet(काष्ठा airo_info*, पूर्णांक len, अक्षर *pPacket,
				 bool may_sleep);
अटल पूर्णांक transmit_802_11_packet(काष्ठा airo_info*, पूर्णांक len, अक्षर *pPacket,
				  bool may_sleep);

अटल पूर्णांक mpi_send_packet(काष्ठा net_device *dev);
अटल व्योम mpi_unmap_card(काष्ठा pci_dev *pci);
अटल व्योम mpi_receive_802_3(काष्ठा airo_info *ai);
अटल व्योम mpi_receive_802_11(काष्ठा airo_info *ai);
अटल पूर्णांक रुकोbusy(काष्ठा airo_info *ai);

अटल irqवापस_t airo_पूर्णांकerrupt(पूर्णांक irq, व्योम* dev_id);
अटल पूर्णांक airo_thपढ़ो(व्योम *data);
अटल व्योम समयr_func(काष्ठा net_device *dev);
अटल पूर्णांक airo_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल काष्ठा iw_statistics *airo_get_wireless_stats(काष्ठा net_device *dev);
#अगर_घोषित CISCO_EXT
अटल पूर्णांक पढ़ोrids(काष्ठा net_device *dev, aironet_ioctl *comp);
अटल पूर्णांक ग_लिखोrids(काष्ठा net_device *dev, aironet_ioctl *comp);
अटल पूर्णांक flashcard(काष्ठा net_device *dev, aironet_ioctl *comp);
#पूर्ण_अगर /* CISCO_EXT */
अटल व्योम micinit(काष्ठा airo_info *ai);
अटल पूर्णांक micsetup(काष्ठा airo_info *ai);
अटल पूर्णांक encapsulate(काष्ठा airo_info *ai, etherHead *pPacket, MICBuffer *buffer, पूर्णांक len);
अटल पूर्णांक decapsulate(काष्ठा airo_info *ai, MICBuffer *mic, etherHead *pPacket, u16 payLen);

अटल u8 airo_rssi_to_dbm(tdsRssiEntry *rssi_rid, u8 rssi);
अटल u8 airo_dbm_to_pct(tdsRssiEntry *rssi_rid, u8 dbm);

अटल व्योम airo_networks_मुक्त(काष्ठा airo_info *ai);

काष्ठा airo_info अणु
	काष्ठा net_device             *dev;
	काष्ठा list_head              dev_list;
	/* Note, we can have MAX_FIDS outstanding.  FIDs are 16-bits, so we
	   use the high bit to mark whether it is in use. */
#घोषणा MAX_FIDS 6
#घोषणा MPI_MAX_FIDS 1
	u32                           fids[MAX_FIDS];
	ConfigRid config;
	अक्षर keyindex; // Used with स्वतः wep
	अक्षर defindex; // Used with स्वतः wep
	काष्ठा proc_dir_entry *proc_entry;
        spinlock_t aux_lock;
#घोषणा FLAG_RADIO_OFF	0	/* User disabling of MAC */
#घोषणा FLAG_RADIO_DOWN	1	/* अगरup/अगरकरोwn disabling of MAC */
#घोषणा FLAG_RADIO_MASK 0x03
#घोषणा FLAG_ENABLED	2
#घोषणा FLAG_ADHOC	3	/* Needed by MIC */
#घोषणा FLAG_MIC_CAPABLE 4
#घोषणा FLAG_UPDATE_MULTI 5
#घोषणा FLAG_UPDATE_UNI 6
#घोषणा FLAG_802_11	7
#घोषणा FLAG_PROMISC	8	/* IFF_PROMISC 0x100 - include/linux/अगर.h */
#घोषणा FLAG_PENDING_XMIT 9
#घोषणा FLAG_PENDING_XMIT11 10
#घोषणा FLAG_MPI	11
#घोषणा FLAG_REGISTERED	12
#घोषणा FLAG_COMMIT	13
#घोषणा FLAG_RESET	14
#घोषणा FLAG_FLASHING	15
#घोषणा FLAG_WPA_CAPABLE	16
	अचिन्हित दीर्घ flags;
#घोषणा JOB_DIE	0
#घोषणा JOB_XMIT	1
#घोषणा JOB_XMIT11	2
#घोषणा JOB_STATS	3
#घोषणा JOB_PROMISC	4
#घोषणा JOB_MIC	5
#घोषणा JOB_EVENT	6
#घोषणा JOB_AUTOWEP	7
#घोषणा JOB_SCAN_RESULTS  9
	अचिन्हित दीर्घ jobs;
	पूर्णांक (*bap_पढ़ो)(काष्ठा airo_info*, __le16 *pu16Dst, पूर्णांक bytelen,
			पूर्णांक whichbap);
	अचिन्हित लघु *flash;
	tdsRssiEntry *rssi;
	काष्ठा task_काष्ठा *list_bss_task;
	काष्ठा task_काष्ठा *airo_thपढ़ो_task;
	काष्ठा semaphore sem;
	रुको_queue_head_t thr_रुको;
	अचिन्हित दीर्घ expires;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		पूर्णांक fid;
	पूर्ण xmit, xmit11;
	काष्ठा net_device *wअगरidev;
	काष्ठा iw_statistics	wstats;		// wireless stats
	अचिन्हित दीर्घ		scan_समयout;	/* Time scan should be पढ़ो */
	काष्ठा iw_spy_data	spy_data;
	काष्ठा iw_खुला_data	wireless_data;
	/* MIC stuff */
	काष्ठा crypto_sync_skcipher	*tfm;
	mic_module		mod[2];
	mic_statistics		micstats;
	HostRxDesc rxfids[MPI_MAX_FIDS]; // rx/tx/config MPI350 descriptors
	HostTxDesc txfids[MPI_MAX_FIDS];
	HostRidDesc config_desc;
	अचिन्हित दीर्घ ridbus; // phys addr of config_desc
	काष्ठा sk_buff_head txq;// tx queue used by mpi350 code
	काष्ठा pci_dev          *pci;
	अचिन्हित अक्षर		__iomem *pcimem;
	अचिन्हित अक्षर		__iomem *pciaux;
	अचिन्हित अक्षर		*shared;
	dma_addr_t		shared_dma;
	pm_message_t		घातer;
	SsidRid			*SSID;
	APListRid		APList;
#घोषणा	PCI_SHARED_LEN		2*MPI_MAX_FIDS*PKTSIZE+RIDSIZE
	अक्षर			proc_name[IFNAMSIZ];

	पूर्णांक			wep_capable;
	पूर्णांक			max_wep_idx;
	पूर्णांक			last_auth;

	/* WPA-related stuff */
	अचिन्हित पूर्णांक bssListFirst;
	अचिन्हित पूर्णांक bssListNext;
	अचिन्हित पूर्णांक bssListRidLen;

	काष्ठा list_head network_list;
	काष्ठा list_head network_मुक्त_list;
	BSSListElement *networks;
पूर्ण;

अटल अंतरभूत पूर्णांक bap_पढ़ो(काष्ठा airo_info *ai, __le16 *pu16Dst, पूर्णांक bytelen,
			   पूर्णांक whichbap)
अणु
	वापस ai->bap_पढ़ो(ai, pu16Dst, bytelen, whichbap);
पूर्ण

अटल पूर्णांक setup_proc_entry(काष्ठा net_device *dev,
			     काष्ठा airo_info *apriv);
अटल पूर्णांक takeकरोwn_proc_entry(काष्ठा net_device *dev,
				काष्ठा airo_info *apriv);

अटल पूर्णांक cmdreset(काष्ठा airo_info *ai);
अटल पूर्णांक setflashmode(काष्ठा airo_info *ai);
अटल पूर्णांक flashgअक्षर(काष्ठा airo_info *ai, पूर्णांक matchbyte, पूर्णांक dwellसमय);
अटल पूर्णांक flashputbuf(काष्ठा airo_info *ai);
अटल पूर्णांक flashrestart(काष्ठा airo_info *ai, काष्ठा net_device *dev);

#घोषणा airo_prपूर्णांक(type, name, fmt, args...) \
	prपूर्णांकk(type DRV_NAME "(%s): " fmt "\n", name, ##args)

#घोषणा airo_prपूर्णांक_info(name, fmt, args...) \
	airo_prपूर्णांक(KERN_INFO, name, fmt, ##args)

#घोषणा airo_prपूर्णांक_dbg(name, fmt, args...) \
	airo_prपूर्णांक(KERN_DEBUG, name, fmt, ##args)

#घोषणा airo_prपूर्णांक_warn(name, fmt, args...) \
	airo_prपूर्णांक(KERN_WARNING, name, fmt, ##args)

#घोषणा airo_prपूर्णांक_err(name, fmt, args...) \
	airo_prपूर्णांक(KERN_ERR, name, fmt, ##args)

#घोषणा AIRO_FLASH(dev) (((काष्ठा airo_info *)dev->ml_priv)->flash)

/***********************************************************************
 *                              MIC ROUTINES                           *
 ***********************************************************************
 */

अटल पूर्णांक RxSeqValid(काष्ठा airo_info *ai, miccntx *context, पूर्णांक mcast, u32 micSeq);
अटल व्योम MoveWinकरोw(miccntx *context, u32 micSeq);
अटल व्योम emmh32_setseed(emmh32_context *context, u8 *pkey, पूर्णांक keylen,
			   काष्ठा crypto_sync_skcipher *tfm);
अटल व्योम emmh32_init(emmh32_context *context);
अटल व्योम emmh32_update(emmh32_context *context, u8 *pOctets, पूर्णांक len);
अटल व्योम emmh32_final(emmh32_context *context, u8 digest[4]);
अटल पूर्णांक flashpअक्षर(काष्ठा airo_info *ai, पूर्णांक byte, पूर्णांक dwellसमय);

अटल व्योम age_mic_context(miccntx *cur, miccntx *old, u8 *key, पूर्णांक key_len,
			    काष्ठा crypto_sync_skcipher *tfm)
अणु
	/* If the current MIC context is valid and its key is the same as
	 * the MIC रेजिस्टर, there's nothing to करो.
	 */
	अगर (cur->valid && (स_भेद(cur->key, key, key_len) == 0))
		वापस;

	/* Age current mic Context */
	स_नकल(old, cur, माप(*cur));

	/* Initialize new context */
	स_नकल(cur->key, key, key_len);
	cur->winकरोw  = 33; /* Winकरोw always poपूर्णांकs to the middle */
	cur->rx      = 0;  /* Rx Sequence numbers */
	cur->tx      = 0;  /* Tx sequence numbers */
	cur->valid   = 1;  /* Key is now valid */

	/* Give key to mic seed */
	emmh32_setseed(&cur->seed, key, key_len, tfm);
पूर्ण

/* micinit - Initialize mic seed */

अटल व्योम micinit(काष्ठा airo_info *ai)
अणु
	MICRid mic_rid;

	clear_bit(JOB_MIC, &ai->jobs);
	PC4500_पढ़ोrid(ai, RID_MIC, &mic_rid, माप(mic_rid), 0);
	up(&ai->sem);

	ai->micstats.enabled = (le16_to_cpu(mic_rid.state) & 0x00FF) ? 1 : 0;
	अगर (!ai->micstats.enabled) अणु
		/* So next समय we have a valid key and mic is enabled, we will
		 * update the sequence number अगर the key is the same as beक्रमe.
		 */
		ai->mod[0].uCtx.valid = 0;
		ai->mod[0].mCtx.valid = 0;
		वापस;
	पूर्ण

	अगर (mic_rid.multicastValid) अणु
		age_mic_context(&ai->mod[0].mCtx, &ai->mod[1].mCtx,
		                mic_rid.multicast, माप(mic_rid.multicast),
		                ai->tfm);
	पूर्ण

	अगर (mic_rid.unicastValid) अणु
		age_mic_context(&ai->mod[0].uCtx, &ai->mod[1].uCtx,
				mic_rid.unicast, माप(mic_rid.unicast),
				ai->tfm);
	पूर्ण
पूर्ण

/* micsetup - Get पढ़ोy क्रम business */

अटल पूर्णांक micsetup(काष्ठा airo_info *ai)
अणु
	पूर्णांक i;

	अगर (ai->tfm == शून्य)
		ai->tfm = crypto_alloc_sync_skcipher("ctr(aes)", 0, 0);

        अगर (IS_ERR(ai->tfm)) अणु
                airo_prपूर्णांक_err(ai->dev->name, "failed to load transform for AES");
                ai->tfm = शून्य;
                वापस ERROR;
        पूर्ण

	क्रम (i = 0; i < NUM_MODULES; i++) अणु
		स_रखो(&ai->mod[i].mCtx, 0, माप(miccntx));
		स_रखो(&ai->mod[i].uCtx, 0, माप(miccntx));
	पूर्ण
	वापस SUCCESS;
पूर्ण

अटल स्थिर u8 micsnap[] = अणु0xAA, 0xAA, 0x03, 0x00, 0x40, 0x96, 0x00, 0x02पूर्ण;

/*===========================================================================
 * Description: Mic a packet
 *
 *      Inमाला_दो: etherHead * poपूर्णांकer to an 802.3 frame
 *
 *     Returns: BOOLEAN अगर successful, otherwise false.
 *             PacketTxLen will be updated with the mic'd packets size.
 *
 *    Caveats: It is assumed that the frame buffer will alपढ़ोy
 *             be big enough to hold the larमाला_लो mic message possible.
 *            (No memory allocation is करोne here).
 *
 *    Author: sbraneky (10/15/01)
 *    Merciless hacks by rwilcher (1/14/02)
 */

अटल पूर्णांक encapsulate(काष्ठा airo_info *ai, etherHead *frame, MICBuffer *mic, पूर्णांक payLen)
अणु
	miccntx   *context;

	// Determine correct context
	// If not adhoc, always use unicast key

	अगर (test_bit(FLAG_ADHOC, &ai->flags) && (frame->da[0] & 0x1))
		context = &ai->mod[0].mCtx;
	अन्यथा
		context = &ai->mod[0].uCtx;

	अगर (!context->valid)
		वापस ERROR;

	mic->typelen = htons(payLen + 16); //Length of Mic'd packet

	स_नकल(&mic->u.snap, micsnap, माप(micsnap)); // Add Snap

	// Add Tx sequence
	mic->seq = htonl(context->tx);
	context->tx += 2;

	emmh32_init(&context->seed); // Mic the packet
	emmh32_update(&context->seed, frame->da, ETH_ALEN * 2); // DA, SA
	emmh32_update(&context->seed, (u8*)&mic->typelen, 10); // Type/Length and Snap
	emmh32_update(&context->seed, (u8*)&mic->seq, माप(mic->seq)); //SEQ
	emmh32_update(&context->seed, (u8*)(frame + 1), payLen); //payload
	emmh32_final(&context->seed, (u8*)&mic->mic);

	/*    New Type/length ?????????? */
	mic->typelen = 0; //Let NIC know it could be an oversized packet
	वापस SUCCESS;
पूर्ण

प्रकार क्रमागत अणु
    NONE,
    NOMIC,
    NOMICPLUMMED,
    SEQUENCE,
    INCORRECTMIC,
पूर्ण mic_error;

/*===========================================================================
 *  Description: Decapsulates a MIC'd packet and वापसs the 802.3 packet
 *               (हटाओs the MIC stuff) अगर packet is a valid packet.
 *
 *       Inमाला_दो: etherHead  poपूर्णांकer to the 802.3 packet
 *
 *      Returns: BOOLEAN - TRUE अगर packet should be dropped otherwise FALSE
 *
 *      Author: sbraneky (10/15/01)
 *    Merciless hacks by rwilcher (1/14/02)
 *---------------------------------------------------------------------------
 */

अटल पूर्णांक decapsulate(काष्ठा airo_info *ai, MICBuffer *mic, etherHead *eth, u16 payLen)
अणु
	पूर्णांक      i;
	u32      micSEQ;
	miccntx  *context;
	u8       digest[4];
	mic_error micError = NONE;

	// Check अगर the packet is a Mic'd packet

	अगर (!ai->micstats.enabled) अणु
		//No Mic set or Mic OFF but we received a MIC'd packet.
		अगर (स_भेद ((u8*)eth + 14, micsnap, माप(micsnap)) == 0) अणु
			ai->micstats.rxMICPlummed++;
			वापस ERROR;
		पूर्ण
		वापस SUCCESS;
	पूर्ण

	अगर (ntohs(mic->typelen) == 0x888E)
		वापस SUCCESS;

	अगर (स_भेद (mic->u.snap, micsnap, माप(micsnap)) != 0) अणु
	    // Mic enabled but packet isn't Mic'd
		ai->micstats.rxMICPlummed++;
	    	वापस ERROR;
	पूर्ण

	micSEQ = ntohl(mic->seq);            //store SEQ as CPU order

	//At this poपूर्णांक we a have a mic'd packet and mic is enabled
	//Now करो the mic error checking.

	//Receive seq must be odd
	अगर ((micSEQ & 1) == 0) अणु
		ai->micstats.rxWrongSequence++;
		वापस ERROR;
	पूर्ण

	क्रम (i = 0; i < NUM_MODULES; i++) अणु
		पूर्णांक mcast = eth->da[0] & 1;
		//Determine proper context
		context = mcast ? &ai->mod[i].mCtx : &ai->mod[i].uCtx;

		//Make sure context is valid
		अगर (!context->valid) अणु
			अगर (i == 0)
				micError = NOMICPLUMMED;
			जारी;
		पूर्ण
		//DeMic it

		अगर (!mic->typelen)
			mic->typelen = htons(payLen + माप(MICBuffer) - 2);

		emmh32_init(&context->seed);
		emmh32_update(&context->seed, eth->da, ETH_ALEN*2);
		emmh32_update(&context->seed, (u8 *)&mic->typelen, माप(mic->typelen)+माप(mic->u.snap));
		emmh32_update(&context->seed, (u8 *)&mic->seq, माप(mic->seq));
		emmh32_update(&context->seed, (u8 *)(eth + 1), payLen);
		//Calculate MIC
		emmh32_final(&context->seed, digest);

		अगर (स_भेद(digest, &mic->mic, 4)) अणु //Make sure the mics match
		  //Invalid Mic
			अगर (i == 0)
				micError = INCORRECTMIC;
			जारी;
		पूर्ण

		//Check Sequence number अगर mics pass
		अगर (RxSeqValid(ai, context, mcast, micSEQ) == SUCCESS) अणु
			ai->micstats.rxSuccess++;
			वापस SUCCESS;
		पूर्ण
		अगर (i == 0)
			micError = SEQUENCE;
	पूर्ण

	// Update statistics
	चयन (micError) अणु
		हाल NOMICPLUMMED: ai->micstats.rxMICPlummed++;   अवरोध;
		हाल SEQUENCE:    ai->micstats.rxWrongSequence++; अवरोध;
		हाल INCORRECTMIC: ai->micstats.rxIncorrectMIC++; अवरोध;
		हाल NONE:  अवरोध;
		हाल NOMIC: अवरोध;
	पूर्ण
	वापस ERROR;
पूर्ण

/*===========================================================================
 * Description:  Checks the Rx Seq number to make sure it is valid
 *               and hasn't alपढ़ोy been received
 *
 *     Inमाला_दो: miccntx - mic context to check seq against
 *             micSeq  - the Mic seq number
 *
 *    Returns: TRUE अगर valid otherwise FALSE.
 *
 *    Author: sbraneky (10/15/01)
 *    Merciless hacks by rwilcher (1/14/02)
 *---------------------------------------------------------------------------
 */

अटल पूर्णांक RxSeqValid(काष्ठा airo_info *ai, miccntx *context, पूर्णांक mcast, u32 micSeq)
अणु
	u32 seq, index;

	//Allow क्रम the ap being rebooted - अगर it is then use the next
	//sequence number of the current sequence number - might go backwards

	अगर (mcast) अणु
		अगर (test_bit(FLAG_UPDATE_MULTI, &ai->flags)) अणु
			clear_bit (FLAG_UPDATE_MULTI, &ai->flags);
			context->winकरोw = (micSeq > 33) ? micSeq : 33;
			context->rx     = 0;        // Reset rx
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(FLAG_UPDATE_UNI, &ai->flags)) अणु
		clear_bit (FLAG_UPDATE_UNI, &ai->flags);
		context->winकरोw = (micSeq > 33) ? micSeq : 33; // Move winकरोw
		context->rx     = 0;        // Reset rx
	पूर्ण

	//Make sequence number relative to START of winकरोw
	seq = micSeq - (context->winकरोw - 33);

	//Too old of a SEQ number to check.
	अगर ((s32)seq < 0)
		वापस ERROR;

	अगर (seq > 64) अणु
		//Winकरोw is infinite क्रमward
		MoveWinकरोw(context, micSeq);
		वापस SUCCESS;
	पूर्ण

	// We are in the winकरोw. Now check the context rx bit to see अगर it was alपढ़ोy sent
	seq >>= 1;         //भागide by 2 because we only have odd numbers
	index = 1 << seq;  //Get an index number

	अगर (!(context->rx & index)) अणु
		//micSEQ falls inside the winकरोw.
		//Add seqence number to the list of received numbers.
		context->rx |= index;

		MoveWinकरोw(context, micSeq);

		वापस SUCCESS;
	पूर्ण
	वापस ERROR;
पूर्ण

अटल व्योम MoveWinकरोw(miccntx *context, u32 micSeq)
अणु
	u32 shअगरt;

	//Move winकरोw अगर seq greater than the middle of the winकरोw
	अगर (micSeq > context->winकरोw) अणु
		shअगरt = (micSeq - context->winकरोw) >> 1;

		    //Shअगरt out old
		अगर (shअगरt < 32)
			context->rx >>= shअगरt;
		अन्यथा
			context->rx = 0;

		context->winकरोw = micSeq;      //Move winकरोw
	पूर्ण
पूर्ण

/*==============================================*/
/*========== EMMH ROUTINES  ====================*/
/*==============================================*/

/* mic accumulate */
#घोषणा MIC_ACCUM(val)	\
	context->accum += (u64)(val) * be32_to_cpu(context->coeff[coeff_position++]);

/* expand the key to fill the MMH coefficient array */
अटल व्योम emmh32_setseed(emmh32_context *context, u8 *pkey, पूर्णांक keylen,
			   काष्ठा crypto_sync_skcipher *tfm)
अणु
  /* take the keying material, expand अगर necessary, truncate at 16-bytes */
  /* run through AES counter mode to generate context->coeff[] */

	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);
	काष्ठा scatterlist sg;
	u8 iv[AES_BLOCK_SIZE] = अणुपूर्ण;
	पूर्णांक ret;

	crypto_sync_skcipher_setkey(tfm, pkey, 16);

	स_रखो(context->coeff, 0, माप(context->coeff));
	sg_init_one(&sg, context->coeff, माप(context->coeff));

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &sg, &sg, माप(context->coeff), iv);

	ret = crypto_skcipher_encrypt(req);
	WARN_ON_ONCE(ret);
पूर्ण

/* prepare क्रम calculation of a new mic */
अटल व्योम emmh32_init(emmh32_context *context)
अणु
	/* prepare क्रम new mic calculation */
	context->accum = 0;
	context->position = 0;
पूर्ण

/* add some bytes to the mic calculation */
अटल व्योम emmh32_update(emmh32_context *context, u8 *pOctets, पूर्णांक len)
अणु
	पूर्णांक	coeff_position, byte_position;

	अगर (len == 0) वापस;

	coeff_position = context->position >> 2;

	/* deal with partial 32-bit word left over from last update */
	byte_position = context->position & 3;
	अगर (byte_position) अणु
		/* have a partial word in part to deal with */
		करो अणु
			अगर (len == 0) वापस;
			context->part.d8[byte_position++] = *pOctets++;
			context->position++;
			len--;
		पूर्ण जबतक (byte_position < 4);
		MIC_ACCUM(ntohl(context->part.d32));
	पूर्ण

	/* deal with full 32-bit words */
	जबतक (len >= 4) अणु
		MIC_ACCUM(ntohl(*(__be32 *)pOctets));
		context->position += 4;
		pOctets += 4;
		len -= 4;
	पूर्ण

	/* deal with partial 32-bit word that will be left over from this update */
	byte_position = 0;
	जबतक (len > 0) अणु
		context->part.d8[byte_position++] = *pOctets++;
		context->position++;
		len--;
	पूर्ण
पूर्ण

/* mask used to zero empty bytes क्रम final partial word */
अटल u32 mask32[4] = अणु 0x00000000L, 0xFF000000L, 0xFFFF0000L, 0xFFFFFF00L पूर्ण;

/* calculate the mic */
अटल व्योम emmh32_final(emmh32_context *context, u8 digest[4])
अणु
	पूर्णांक	coeff_position, byte_position;
	u32	val;

	u64 sum, uपंचांगp;
	s64 sपंचांगp;

	coeff_position = context->position >> 2;

	/* deal with partial 32-bit word left over from last update */
	byte_position = context->position & 3;
	अगर (byte_position) अणु
		/* have a partial word in part to deal with */
		val = ntohl(context->part.d32);
		MIC_ACCUM(val & mask32[byte_position]);	/* zero empty bytes */
	पूर्ण

	/* reduce the accumulated u64 to a 32-bit MIC */
	sum = context->accum;
	sपंचांगp = (sum  & 0xffffffffLL) - ((sum >> 32)  * 15);
	uपंचांगp = (sपंचांगp & 0xffffffffLL) - ((sपंचांगp >> 32) * 15);
	sum = uपंचांगp & 0xffffffffLL;
	अगर (uपंचांगp > 0x10000000fLL)
		sum -= 15;

	val = (u32)sum;
	digest[0] = (val>>24) & 0xFF;
	digest[1] = (val>>16) & 0xFF;
	digest[2] = (val>>8) & 0xFF;
	digest[3] = val & 0xFF;
पूर्ण

अटल पूर्णांक पढ़ोBSSListRid(काष्ठा airo_info *ai, पूर्णांक first,
		      BSSListRid *list)
अणु
	Cmd cmd;
	Resp rsp;

	अगर (first == 1) अणु
		अगर (ai->flags & FLAG_RADIO_MASK) वापस -ENETDOWN;
		स_रखो(&cmd, 0, माप(cmd));
		cmd.cmd = CMD_LISTBSS;
		अगर (करोwn_पूर्णांकerruptible(&ai->sem))
			वापस -ERESTARTSYS;
		ai->list_bss_task = current;
		issuecommand(ai, &cmd, &rsp, true);
		up(&ai->sem);
		/* Let the command take effect */
		schedule_समयout_unपूर्णांकerruptible(3 * HZ);
		ai->list_bss_task = शून्य;
	पूर्ण
	वापस PC4500_पढ़ोrid(ai, first ? ai->bssListFirst : ai->bssListNext,
			    list, ai->bssListRidLen, 1);
पूर्ण

अटल पूर्णांक पढ़ोWepKeyRid(काष्ठा airo_info *ai, WepKeyRid *wkr, पूर्णांक temp, पूर्णांक lock)
अणु
	वापस PC4500_पढ़ोrid(ai, temp ? RID_WEP_TEMP : RID_WEP_PERM,
				wkr, माप(*wkr), lock);
पूर्ण

अटल पूर्णांक ग_लिखोWepKeyRid(काष्ठा airo_info *ai, WepKeyRid *wkr, पूर्णांक perm, पूर्णांक lock)
अणु
	पूर्णांक rc;
	rc = PC4500_ग_लिखोrid(ai, RID_WEP_TEMP, wkr, माप(*wkr), lock);
	अगर (rc!=SUCCESS)
		airo_prपूर्णांक_err(ai->dev->name, "WEP_TEMP set %x", rc);
	अगर (perm) अणु
		rc = PC4500_ग_लिखोrid(ai, RID_WEP_PERM, wkr, माप(*wkr), lock);
		अगर (rc!=SUCCESS)
			airo_prपूर्णांक_err(ai->dev->name, "WEP_PERM set %x", rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक पढ़ोSsidRid(काष्ठा airo_info*ai, SsidRid *ssidr)
अणु
	वापस PC4500_पढ़ोrid(ai, RID_SSID, ssidr, माप(*ssidr), 1);
पूर्ण

अटल पूर्णांक ग_लिखोSsidRid(काष्ठा airo_info*ai, SsidRid *pssidr, पूर्णांक lock)
अणु
	वापस PC4500_ग_लिखोrid(ai, RID_SSID, pssidr, माप(*pssidr), lock);
पूर्ण

अटल पूर्णांक पढ़ोConfigRid(काष्ठा airo_info *ai, पूर्णांक lock)
अणु
	पूर्णांक rc;
	ConfigRid cfg;

	अगर (ai->config.len)
		वापस SUCCESS;

	rc = PC4500_पढ़ोrid(ai, RID_ACTUALCONFIG, &cfg, माप(cfg), lock);
	अगर (rc != SUCCESS)
		वापस rc;

	ai->config = cfg;
	वापस SUCCESS;
पूर्ण

अटल अंतरभूत व्योम checkThrottle(काष्ठा airo_info *ai)
अणु
	पूर्णांक i;
/* Old hardware had a limit on encryption speed */
	अगर (ai->config.authType != AUTH_OPEN && maxencrypt) अणु
		क्रम (i = 0; i<8; i++) अणु
			अगर (ai->config.rates[i] > maxencrypt) अणु
				ai->config.rates[i] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखोConfigRid(काष्ठा airo_info *ai, पूर्णांक lock)
अणु
	ConfigRid cfgr;

	अगर (!test_bit (FLAG_COMMIT, &ai->flags))
		वापस SUCCESS;

	clear_bit (FLAG_COMMIT, &ai->flags);
	clear_bit (FLAG_RESET, &ai->flags);
	checkThrottle(ai);
	cfgr = ai->config;

	अगर ((cfgr.opmode & MODE_CFG_MASK) == MODE_STA_IBSS)
		set_bit(FLAG_ADHOC, &ai->flags);
	अन्यथा
		clear_bit(FLAG_ADHOC, &ai->flags);

	वापस PC4500_ग_लिखोrid(ai, RID_CONFIG, &cfgr, माप(cfgr), lock);
पूर्ण

अटल पूर्णांक पढ़ोStatusRid(काष्ठा airo_info *ai, StatusRid *statr, पूर्णांक lock)
अणु
	वापस PC4500_पढ़ोrid(ai, RID_STATUS, statr, माप(*statr), lock);
पूर्ण

अटल पूर्णांक ग_लिखोAPListRid(काष्ठा airo_info *ai, APListRid *aplr, पूर्णांक lock)
अणु
	वापस PC4500_ग_लिखोrid(ai, RID_APLIST, aplr, माप(*aplr), lock);
पूर्ण

अटल पूर्णांक पढ़ोCapabilityRid(काष्ठा airo_info *ai, CapabilityRid *capr, पूर्णांक lock)
अणु
	वापस PC4500_पढ़ोrid(ai, RID_CAPABILITIES, capr, माप(*capr), lock);
पूर्ण

अटल पूर्णांक पढ़ोStatsRid(काष्ठा airo_info*ai, StatsRid *sr, पूर्णांक rid, पूर्णांक lock)
अणु
	वापस PC4500_पढ़ोrid(ai, rid, sr, माप(*sr), lock);
पूर्ण

अटल व्योम try_स्वतः_wep(काष्ठा airo_info *ai)
अणु
	अगर (स्वतः_wep && !test_bit(FLAG_RADIO_DOWN, &ai->flags)) अणु
		ai->expires = RUN_AT(3*HZ);
		wake_up_पूर्णांकerruptible(&ai->thr_रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक airo_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक rc = 0;

	अगर (test_bit(FLAG_FLASHING, &ai->flags))
		वापस -EIO;

	/* Make sure the card is configured.
	 * Wireless Extensions may postpone config changes until the card
	 * is खोलो (to pipeline changes and speed-up card setup). If
	 * those changes are not yet committed, करो it now - Jean II */
	अगर (test_bit(FLAG_COMMIT, &ai->flags)) अणु
		disable_MAC(ai, 1);
		ग_लिखोConfigRid(ai, 1);
	पूर्ण

	अगर (ai->wअगरidev != dev) अणु
		clear_bit(JOB_DIE, &ai->jobs);
		ai->airo_thपढ़ो_task = kthपढ़ो_run(airo_thपढ़ो, dev, "%s",
						   dev->name);
		अगर (IS_ERR(ai->airo_thपढ़ो_task))
			वापस (पूर्णांक)PTR_ERR(ai->airo_thपढ़ो_task);

		rc = request_irq(dev->irq, airo_पूर्णांकerrupt, IRQF_SHARED,
			dev->name, dev);
		अगर (rc) अणु
			airo_prपूर्णांक_err(dev->name,
				"register interrupt %d failed, rc %d",
				dev->irq, rc);
			set_bit(JOB_DIE, &ai->jobs);
			kthपढ़ो_stop(ai->airo_thपढ़ो_task);
			वापस rc;
		पूर्ण

		/* Power on the MAC controller (which may have been disabled) */
		clear_bit(FLAG_RADIO_DOWN, &ai->flags);
		enable_पूर्णांकerrupts(ai);

		try_स्वतः_wep(ai);
	पूर्ण
	enable_MAC(ai, 1);

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t mpi_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	पूर्णांक npacks, pending;
	अचिन्हित दीर्घ flags;
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर (!skb) अणु
		airo_prपूर्णांक_err(dev->name, "%s: skb == NULL!",__func__);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb_padto(skb, ETH_ZLEN)) अणु
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	npacks = skb_queue_len (&ai->txq);

	अगर (npacks >= MAXTXQ - 1) अणु
		netअगर_stop_queue (dev);
		अगर (npacks > MAXTXQ) अणु
			dev->stats.tx_fअगरo_errors++;
			वापस NETDEV_TX_BUSY;
		पूर्ण
		skb_queue_tail (&ai->txq, skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&ai->aux_lock, flags);
	skb_queue_tail (&ai->txq, skb);
	pending = test_bit(FLAG_PENDING_XMIT, &ai->flags);
	spin_unlock_irqrestore(&ai->aux_lock, flags);
	netअगर_wake_queue (dev);

	अगर (pending == 0) अणु
		set_bit(FLAG_PENDING_XMIT, &ai->flags);
		mpi_send_packet (dev);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/*
 * @mpi_send_packet
 *
 * Attempt to transmit a packet. Can be called from पूर्णांकerrupt
 * or transmit . वापस number of packets we tried to send
 */

अटल पूर्णांक mpi_send_packet (काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *buffer;
	s16 len;
	__le16 *payloadLen;
	काष्ठा airo_info *ai = dev->ml_priv;
	u8 *sendbuf;

	/* get a packet to send */

	अगर ((skb = skb_dequeue(&ai->txq)) == शून्य) अणु
		airo_prपूर्णांक_err(dev->name,
			"%s: Dequeue'd zero in send_packet()",
			__func__);
		वापस 0;
	पूर्ण

	/* check min length*/
	len = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	buffer = skb->data;

	ai->txfids[0].tx_desc.offset = 0;
	ai->txfids[0].tx_desc.valid = 1;
	ai->txfids[0].tx_desc.eoc = 1;
	ai->txfids[0].tx_desc.len =len+माप(WअगरiHdr);

/*
 * Magic, the cards firmware needs a length count (2 bytes) in the host buffer
 * right after  TXFID_HDR.The TXFID_HDR contains the status लघु so payloadlen
 * is immediately after it. ------------------------------------------------
 *                         |TXFIDHDR+STATUS|PAYLOADLEN|802.3HDR|PACKETDATA|
 *                         ------------------------------------------------
 */

	स_नकल(ai->txfids[0].भव_host_addr,
		(अक्षर *)&wअगरictlhdr8023, माप(wअगरictlhdr8023));

	payloadLen = (__le16 *)(ai->txfids[0].भव_host_addr +
		माप(wअगरictlhdr8023));
	sendbuf = ai->txfids[0].भव_host_addr +
		माप(wअगरictlhdr8023) + 2 ;

	/*
	 * Firmware स्वतःmatically माला_दो 802 header on so
	 * we करोn't need to account क्रम it in the length
	 */
	अगर (test_bit(FLAG_MIC_CAPABLE, &ai->flags) && ai->micstats.enabled &&
		(ntohs(((__be16 *)buffer)[6]) != 0x888E)) अणु
		MICBuffer pMic;

		अगर (encapsulate(ai, (etherHead *)buffer, &pMic, len - माप(etherHead)) != SUCCESS)
			वापस ERROR;

		*payloadLen = cpu_to_le16(len-माप(etherHead)+माप(pMic));
		ai->txfids[0].tx_desc.len += माप(pMic);
		/* copy data पूर्णांकo airo dma buffer */
		स_नकल (sendbuf, buffer, माप(etherHead));
		buffer += माप(etherHead);
		sendbuf += माप(etherHead);
		स_नकल (sendbuf, &pMic, माप(pMic));
		sendbuf += माप(pMic);
		स_नकल (sendbuf, buffer, len - माप(etherHead));
	पूर्ण अन्यथा अणु
		*payloadLen = cpu_to_le16(len - माप(etherHead));

		netअगर_trans_update(dev);

		/* copy data पूर्णांकo airo dma buffer */
		स_नकल(sendbuf, buffer, len);
	पूर्ण

	स_नकल_toio(ai->txfids[0].card_ram_off,
		&ai->txfids[0].tx_desc, माप(TxFid));

	OUT4500(ai, EVACK, 8);

	dev_kमुक्त_skb_any(skb);
	वापस 1;
पूर्ण

अटल व्योम get_tx_error(काष्ठा airo_info *ai, s32 fid)
अणु
	__le16 status;

	अगर (fid < 0)
		status = ((WअगरiCtlHdr *)ai->txfids[0].भव_host_addr)->ctlhdr.status;
	अन्यथा अणु
		अगर (bap_setup(ai, ai->fids[fid] & 0xffff, 4, BAP0) != SUCCESS)
			वापस;
		bap_पढ़ो(ai, &status, 2, BAP0);
	पूर्ण
	अगर (le16_to_cpu(status) & 2) /* Too many retries */
		ai->dev->stats.tx_पातed_errors++;
	अगर (le16_to_cpu(status) & 4) /* Transmit lअगरeसमय exceeded */
		ai->dev->stats.tx_heartbeat_errors++;
	अगर (le16_to_cpu(status) & 8) /* Aid fail */
		अणु पूर्ण
	अगर (le16_to_cpu(status) & 0x10) /* MAC disabled */
		ai->dev->stats.tx_carrier_errors++;
	अगर (le16_to_cpu(status) & 0x20) /* Association lost */
		अणु पूर्ण
	/* We produce a TXDROP event only क्रम retry or lअगरeसमय
	 * exceeded, because that's the only status that really mean
	 * that this particular node went away.
	 * Other errors means that *we* screwed up. - Jean II */
	अगर ((le16_to_cpu(status) & 2) ||
	     (le16_to_cpu(status) & 4)) अणु
		जोड़ iwreq_data	wrqu;
		अक्षर junk[0x18];

		/* Faster to skip over useless data than to करो
		 * another bap_setup(). We are at offset 0x6 and
		 * need to go to 0x18 and पढ़ो 6 bytes - Jean II */
		bap_पढ़ो(ai, (__le16 *) junk, 0x18, BAP0);

		/* Copy 802.11 dest address.
		 * We use the 802.11 header because the frame may
		 * not be 802.3 or may be mangled...
		 * In Ad-Hoc mode, it will be the node address.
		 * In managed mode, it will be most likely the AP addr
		 * User space will figure out how to convert it to
		 * whatever it needs (IP address or अन्यथा).
		 * - Jean II */
		स_नकल(wrqu.addr.sa_data, junk + 0x12, ETH_ALEN);
		wrqu.addr.sa_family = ARPHRD_ETHER;

		/* Send event to user space */
		wireless_send_event(ai->dev, IWEVTXDROP, &wrqu, शून्य);
	पूर्ण
पूर्ण

अटल व्योम airo_end_xmit(काष्ठा net_device *dev, bool may_sleep)
अणु
	u16 status;
	पूर्णांक i;
	काष्ठा airo_info *priv = dev->ml_priv;
	काष्ठा sk_buff *skb = priv->xmit.skb;
	पूर्णांक fid = priv->xmit.fid;
	u32 *fids = priv->fids;

	clear_bit(JOB_XMIT, &priv->jobs);
	clear_bit(FLAG_PENDING_XMIT, &priv->flags);
	status = transmit_802_3_packet(priv, fids[fid], skb->data, may_sleep);
	up(&priv->sem);

	i = 0;
	अगर (status == SUCCESS) अणु
		netअगर_trans_update(dev);
		क्रम (; i < MAX_FIDS / 2 && (priv->fids[i] & 0xffff0000); i++);
	पूर्ण अन्यथा अणु
		priv->fids[fid] &= 0xffff;
		dev->stats.tx_winकरोw_errors++;
	पूर्ण
	अगर (i < MAX_FIDS / 2)
		netअगर_wake_queue(dev);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल netdev_tx_t airo_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	s16 len;
	पूर्णांक i, j;
	काष्ठा airo_info *priv = dev->ml_priv;
	u32 *fids = priv->fids;

	अगर (skb == शून्य) अणु
		airo_prपूर्णांक_err(dev->name, "%s: skb == NULL!", __func__);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb_padto(skb, ETH_ZLEN)) अणु
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Find a vacant FID */
	क्रम (i = 0; i < MAX_FIDS / 2 && (fids[i] & 0xffff0000); i++);
	क्रम (j = i + 1; j < MAX_FIDS / 2 && (fids[j] & 0xffff0000); j++);

	अगर (j >= MAX_FIDS / 2) अणु
		netअगर_stop_queue(dev);

		अगर (i == MAX_FIDS / 2) अणु
			dev->stats.tx_fअगरo_errors++;
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण
	/* check min length*/
	len = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
        /* Mark fid as used & save length क्रम later */
	fids[i] |= (len << 16);
	priv->xmit.skb = skb;
	priv->xmit.fid = i;
	अगर (करोwn_trylock(&priv->sem) != 0) अणु
		set_bit(FLAG_PENDING_XMIT, &priv->flags);
		netअगर_stop_queue(dev);
		set_bit(JOB_XMIT, &priv->jobs);
		wake_up_पूर्णांकerruptible(&priv->thr_रुको);
	पूर्ण अन्यथा
		airo_end_xmit(dev, false);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम airo_end_xmit11(काष्ठा net_device *dev, bool may_sleep)
अणु
	u16 status;
	पूर्णांक i;
	काष्ठा airo_info *priv = dev->ml_priv;
	काष्ठा sk_buff *skb = priv->xmit11.skb;
	पूर्णांक fid = priv->xmit11.fid;
	u32 *fids = priv->fids;

	clear_bit(JOB_XMIT11, &priv->jobs);
	clear_bit(FLAG_PENDING_XMIT11, &priv->flags);
	status = transmit_802_11_packet(priv, fids[fid], skb->data, may_sleep);
	up(&priv->sem);

	i = MAX_FIDS / 2;
	अगर (status == SUCCESS) अणु
		netअगर_trans_update(dev);
		क्रम (; i < MAX_FIDS && (priv->fids[i] & 0xffff0000); i++);
	पूर्ण अन्यथा अणु
		priv->fids[fid] &= 0xffff;
		dev->stats.tx_winकरोw_errors++;
	पूर्ण
	अगर (i < MAX_FIDS)
		netअगर_wake_queue(dev);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल netdev_tx_t airo_start_xmit11(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	s16 len;
	पूर्णांक i, j;
	काष्ठा airo_info *priv = dev->ml_priv;
	u32 *fids = priv->fids;

	अगर (test_bit(FLAG_MPI, &priv->flags)) अणु
		/* Not implemented yet क्रम MPI350 */
		netअगर_stop_queue(dev);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb == शून्य) अणु
		airo_prपूर्णांक_err(dev->name, "%s: skb == NULL!", __func__);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb_padto(skb, ETH_ZLEN)) अणु
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Find a vacant FID */
	क्रम (i = MAX_FIDS / 2; i < MAX_FIDS && (fids[i] & 0xffff0000); i++);
	क्रम (j = i + 1; j < MAX_FIDS && (fids[j] & 0xffff0000); j++);

	अगर (j >= MAX_FIDS) अणु
		netअगर_stop_queue(dev);

		अगर (i == MAX_FIDS) अणु
			dev->stats.tx_fअगरo_errors++;
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण
	/* check min length*/
	len = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
        /* Mark fid as used & save length क्रम later */
	fids[i] |= (len << 16);
	priv->xmit11.skb = skb;
	priv->xmit11.fid = i;
	अगर (करोwn_trylock(&priv->sem) != 0) अणु
		set_bit(FLAG_PENDING_XMIT11, &priv->flags);
		netअगर_stop_queue(dev);
		set_bit(JOB_XMIT11, &priv->jobs);
		wake_up_पूर्णांकerruptible(&priv->thr_रुको);
	पूर्ण अन्यथा
		airo_end_xmit11(dev, false);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम airo_पढ़ो_stats(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	StatsRid stats_rid;
	__le32 *vals = stats_rid.vals;

	clear_bit(JOB_STATS, &ai->jobs);
	अगर (ai->घातer.event) अणु
		up(&ai->sem);
		वापस;
	पूर्ण
	पढ़ोStatsRid(ai, &stats_rid, RID_STATS, 0);
	up(&ai->sem);

	dev->stats.rx_packets = le32_to_cpu(vals[43]) + le32_to_cpu(vals[44]) +
			       le32_to_cpu(vals[45]);
	dev->stats.tx_packets = le32_to_cpu(vals[39]) + le32_to_cpu(vals[40]) +
			       le32_to_cpu(vals[41]);
	dev->stats.rx_bytes = le32_to_cpu(vals[92]);
	dev->stats.tx_bytes = le32_to_cpu(vals[91]);
	dev->stats.rx_errors = le32_to_cpu(vals[0]) + le32_to_cpu(vals[2]) +
			      le32_to_cpu(vals[3]) + le32_to_cpu(vals[4]);
	dev->stats.tx_errors = le32_to_cpu(vals[42]) +
			      dev->stats.tx_fअगरo_errors;
	dev->stats.multicast = le32_to_cpu(vals[43]);
	dev->stats.collisions = le32_to_cpu(vals[89]);

	/* detailed rx_errors: */
	dev->stats.rx_length_errors = le32_to_cpu(vals[3]);
	dev->stats.rx_crc_errors = le32_to_cpu(vals[4]);
	dev->stats.rx_frame_errors = le32_to_cpu(vals[2]);
	dev->stats.rx_fअगरo_errors = le32_to_cpu(vals[0]);
पूर्ण

अटल काष्ठा net_device_stats *airo_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *local =  dev->ml_priv;

	अगर (!test_bit(JOB_STATS, &local->jobs)) अणु
		set_bit(JOB_STATS, &local->jobs);
		wake_up_पूर्णांकerruptible(&local->thr_रुको);
	पूर्ण

	वापस &dev->stats;
पूर्ण

अटल व्योम airo_set_promisc(काष्ठा airo_info *ai, bool may_sleep)
अणु
	Cmd cmd;
	Resp rsp;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = CMD_SETMODE;
	clear_bit(JOB_PROMISC, &ai->jobs);
	cmd.parm0=(ai->flags&IFF_PROMISC) ? PROMISC : NOPROMISC;
	issuecommand(ai, &cmd, &rsp, may_sleep);
	up(&ai->sem);
पूर्ण

अटल व्योम airo_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर ((dev->flags ^ ai->flags) & IFF_PROMISC) अणु
		change_bit(FLAG_PROMISC, &ai->flags);
		अगर (करोwn_trylock(&ai->sem) != 0) अणु
			set_bit(JOB_PROMISC, &ai->jobs);
			wake_up_पूर्णांकerruptible(&ai->thr_रुको);
		पूर्ण अन्यथा
			airo_set_promisc(ai, false);
	पूर्ण

	अगर ((dev->flags&IFF_ALLMULTI) || !netdev_mc_empty(dev)) अणु
		/* Turn on multicast.  (Should be alपढ़ोy setup...) */
	पूर्ण
पूर्ण

अटल पूर्णांक airo_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	काष्ठा sockaddr *addr = p;

	पढ़ोConfigRid(ai, 1);
	स_नकल (ai->config.macAddr, addr->sa_data, dev->addr_len);
	set_bit (FLAG_COMMIT, &ai->flags);
	disable_MAC(ai, 1);
	ग_लिखोConfigRid (ai, 1);
	enable_MAC(ai, 1);
	स_नकल (ai->dev->dev_addr, addr->sa_data, dev->addr_len);
	अगर (ai->wअगरidev)
		स_नकल (ai->wअगरidev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

अटल LIST_HEAD(airo_devices);

अटल व्योम add_airo_dev(काष्ठा airo_info *ai)
अणु
	/* Upper layers alपढ़ोy keep track of PCI devices,
	 * so we only need to remember our non-PCI cards. */
	अगर (!ai->pci)
		list_add_tail(&ai->dev_list, &airo_devices);
पूर्ण

अटल व्योम del_airo_dev(काष्ठा airo_info *ai)
अणु
	अगर (!ai->pci)
		list_del(&ai->dev_list);
पूर्ण

अटल पूर्णांक airo_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;

	netअगर_stop_queue(dev);

	अगर (ai->wअगरidev != dev) अणु
#अगर_घोषित POWER_ON_DOWN
		/* Shut घातer to the card. The idea is that the user can save
		 * घातer when he करोesn't need the card with "ifconfig down".
		 * That's the method that is most मित्रly towards the network
		 * stack (i.e. the network stack won't try to broadcast
		 * anything on the पूर्णांकerface and routes are gone. Jean II */
		set_bit(FLAG_RADIO_DOWN, &ai->flags);
		disable_MAC(ai, 1);
#पूर्ण_अगर
		disable_पूर्णांकerrupts(ai);

		मुक्त_irq(dev->irq, dev);

		set_bit(JOB_DIE, &ai->jobs);
		kthपढ़ो_stop(ai->airo_thपढ़ो_task);
	पूर्ण
	वापस 0;
पूर्ण

व्योम stop_airo_card(काष्ठा net_device *dev, पूर्णांक मुक्तres)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;

	set_bit(FLAG_RADIO_DOWN, &ai->flags);
	disable_MAC(ai, 1);
	disable_पूर्णांकerrupts(ai);
	takeकरोwn_proc_entry(dev, ai);
	अगर (test_bit(FLAG_REGISTERED, &ai->flags)) अणु
		unरेजिस्टर_netdev(dev);
		अगर (ai->wअगरidev) अणु
			unरेजिस्टर_netdev(ai->wअगरidev);
			मुक्त_netdev(ai->wअगरidev);
			ai->wअगरidev = शून्य;
		पूर्ण
		clear_bit(FLAG_REGISTERED, &ai->flags);
	पूर्ण
	/*
	 * Clean out tx queue
	 */
	अगर (test_bit(FLAG_MPI, &ai->flags) && !skb_queue_empty(&ai->txq)) अणु
		काष्ठा sk_buff *skb = शून्य;
		क्रम (;(skb = skb_dequeue(&ai->txq));)
			dev_kमुक्त_skb(skb);
	पूर्ण

	airo_networks_मुक्त (ai);

	kमुक्त(ai->flash);
	kमुक्त(ai->rssi);
	kमुक्त(ai->SSID);
	अगर (मुक्तres) अणु
		/* PCMCIA मुक्तs this stuff, so only क्रम PCI and ISA */
		release_region(dev->base_addr, 64);
		अगर (test_bit(FLAG_MPI, &ai->flags)) अणु
			अगर (ai->pci)
				mpi_unmap_card(ai->pci);
			अगर (ai->pcimem)
				iounmap(ai->pcimem);
			अगर (ai->pciaux)
				iounmap(ai->pciaux);
			dma_मुक्त_coherent(&ai->pci->dev, PCI_SHARED_LEN,
					  ai->shared, ai->shared_dma);
		पूर्ण
        पूर्ण
	crypto_मुक्त_sync_skcipher(ai->tfm);
	del_airo_dev(ai);
	मुक्त_netdev(dev);
पूर्ण

EXPORT_SYMBOL(stop_airo_card);

अटल पूर्णांक wll_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	स_नकल(haddr, skb_mac_header(skb) + 10, ETH_ALEN);
	वापस ETH_ALEN;
पूर्ण

अटल व्योम mpi_unmap_card(काष्ठा pci_dev *pci)
अणु
	अचिन्हित दीर्घ mem_start = pci_resource_start(pci, 1);
	अचिन्हित दीर्घ mem_len = pci_resource_len(pci, 1);
	अचिन्हित दीर्घ aux_start = pci_resource_start(pci, 2);
	अचिन्हित दीर्घ aux_len = AUXMEMSIZE;

	release_mem_region(aux_start, aux_len);
	release_mem_region(mem_start, mem_len);
पूर्ण

/*************************************************************
 *  This routine assumes that descriptors have been setup .
 *  Run at insmod समय or after reset when the descriptors
 *  have been initialized . Returns 0 अगर all is well nz
 *  otherwise . Does not allocate memory but sets up card
 *  using previously allocated descriptors.
 */
अटल पूर्णांक mpi_init_descriptors (काष्ठा airo_info *ai)
अणु
	Cmd cmd;
	Resp rsp;
	पूर्णांक i;
	पूर्णांक rc = SUCCESS;

	/* Alloc  card RX descriptors */
	netअगर_stop_queue(ai->dev);

	स_रखो(&rsp, 0, माप(rsp));
	स_रखो(&cmd, 0, माप(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = FID_RX;
	cmd.parm1 = (ai->rxfids[0].card_ram_off - ai->pciaux);
	cmd.parm2 = MPI_MAX_FIDS;
	rc = issuecommand(ai, &cmd, &rsp, true);
	अगर (rc != SUCCESS) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Couldn't allocate RX FID");
		वापस rc;
	पूर्ण

	क्रम (i = 0; i<MPI_MAX_FIDS; i++) अणु
		स_नकल_toio(ai->rxfids[i].card_ram_off,
			&ai->rxfids[i].rx_desc, माप(RxFid));
	पूर्ण

	/* Alloc card TX descriptors */

	स_रखो(&rsp, 0, माप(rsp));
	स_रखो(&cmd, 0, माप(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = FID_TX;
	cmd.parm1 = (ai->txfids[0].card_ram_off - ai->pciaux);
	cmd.parm2 = MPI_MAX_FIDS;

	क्रम (i = 0; i<MPI_MAX_FIDS; i++) अणु
		ai->txfids[i].tx_desc.valid = 1;
		स_नकल_toio(ai->txfids[i].card_ram_off,
			&ai->txfids[i].tx_desc, माप(TxFid));
	पूर्ण
	ai->txfids[i-1].tx_desc.eoc = 1; /* Last descriptor has EOC set */

	rc = issuecommand(ai, &cmd, &rsp, true);
	अगर (rc != SUCCESS) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Couldn't allocate TX FID");
		वापस rc;
	पूर्ण

	/* Alloc card Rid descriptor */
	स_रखो(&rsp, 0, माप(rsp));
	स_रखो(&cmd, 0, माप(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = RID_RW;
	cmd.parm1 = (ai->config_desc.card_ram_off - ai->pciaux);
	cmd.parm2 = 1; /* Magic number... */
	rc = issuecommand(ai, &cmd, &rsp, true);
	अगर (rc != SUCCESS) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Couldn't allocate RID");
		वापस rc;
	पूर्ण

	स_नकल_toio(ai->config_desc.card_ram_off,
		&ai->config_desc.rid_desc, माप(Rid));

	वापस rc;
पूर्ण

/*
 * We are setting up three things here:
 * 1) Map AUX memory क्रम descriptors: Rid, TxFid, or RxFid.
 * 2) Map PCI memory क्रम issuing commands.
 * 3) Allocate memory (shared) to send and receive ethernet frames.
 */
अटल पूर्णांक mpi_map_card(काष्ठा airo_info *ai, काष्ठा pci_dev *pci)
अणु
	अचिन्हित दीर्घ mem_start, mem_len, aux_start, aux_len;
	पूर्णांक rc = -1;
	पूर्णांक i;
	dma_addr_t busaddroff;
	अचिन्हित अक्षर *vpackoff;
	अचिन्हित अक्षर __iomem *pciaddroff;

	mem_start = pci_resource_start(pci, 1);
	mem_len = pci_resource_len(pci, 1);
	aux_start = pci_resource_start(pci, 2);
	aux_len = AUXMEMSIZE;

	अगर (!request_mem_region(mem_start, mem_len, DRV_NAME)) अणु
		airo_prपूर्णांक_err("", "Couldn't get region %x[%x]",
			(पूर्णांक)mem_start, (पूर्णांक)mem_len);
		जाओ out;
	पूर्ण
	अगर (!request_mem_region(aux_start, aux_len, DRV_NAME)) अणु
		airo_prपूर्णांक_err("", "Couldn't get region %x[%x]",
			(पूर्णांक)aux_start, (पूर्णांक)aux_len);
		जाओ मुक्त_region1;
	पूर्ण

	ai->pcimem = ioremap(mem_start, mem_len);
	अगर (!ai->pcimem) अणु
		airo_prपूर्णांक_err("", "Couldn't map region %x[%x]",
			(पूर्णांक)mem_start, (पूर्णांक)mem_len);
		जाओ मुक्त_region2;
	पूर्ण
	ai->pciaux = ioremap(aux_start, aux_len);
	अगर (!ai->pciaux) अणु
		airo_prपूर्णांक_err("", "Couldn't map region %x[%x]",
			(पूर्णांक)aux_start, (पूर्णांक)aux_len);
		जाओ मुक्त_memmap;
	पूर्ण

	/* Reserve PKTSIZE क्रम each fid and 2K क्रम the Rids */
	ai->shared = dma_alloc_coherent(&pci->dev, PCI_SHARED_LEN,
					&ai->shared_dma, GFP_KERNEL);
	अगर (!ai->shared) अणु
		airo_prपूर्णांक_err("", "Couldn't alloc_coherent %d",
			PCI_SHARED_LEN);
		जाओ मुक्त_auxmap;
	पूर्ण

	/*
	 * Setup descriptor RX, TX, CONFIG
	 */
	busaddroff = ai->shared_dma;
	pciaddroff = ai->pciaux + AUX_OFFSET;
	vpackoff   = ai->shared;

	/* RX descriptor setup */
	क्रम (i = 0; i < MPI_MAX_FIDS; i++) अणु
		ai->rxfids[i].pending = 0;
		ai->rxfids[i].card_ram_off = pciaddroff;
		ai->rxfids[i].भव_host_addr = vpackoff;
		ai->rxfids[i].rx_desc.host_addr = busaddroff;
		ai->rxfids[i].rx_desc.valid = 1;
		ai->rxfids[i].rx_desc.len = PKTSIZE;
		ai->rxfids[i].rx_desc.rdy = 0;

		pciaddroff += माप(RxFid);
		busaddroff += PKTSIZE;
		vpackoff   += PKTSIZE;
	पूर्ण

	/* TX descriptor setup */
	क्रम (i = 0; i < MPI_MAX_FIDS; i++) अणु
		ai->txfids[i].card_ram_off = pciaddroff;
		ai->txfids[i].भव_host_addr = vpackoff;
		ai->txfids[i].tx_desc.valid = 1;
		ai->txfids[i].tx_desc.host_addr = busaddroff;
		स_नकल(ai->txfids[i].भव_host_addr,
			&wअगरictlhdr8023, माप(wअगरictlhdr8023));

		pciaddroff += माप(TxFid);
		busaddroff += PKTSIZE;
		vpackoff   += PKTSIZE;
	पूर्ण
	ai->txfids[i-1].tx_desc.eoc = 1; /* Last descriptor has EOC set */

	/* Rid descriptor setup */
	ai->config_desc.card_ram_off = pciaddroff;
	ai->config_desc.भव_host_addr = vpackoff;
	ai->config_desc.rid_desc.host_addr = busaddroff;
	ai->ridbus = busaddroff;
	ai->config_desc.rid_desc.rid = 0;
	ai->config_desc.rid_desc.len = RIDSIZE;
	ai->config_desc.rid_desc.valid = 1;
	pciaddroff += माप(Rid);
	busaddroff += RIDSIZE;
	vpackoff   += RIDSIZE;

	/* Tell card about descriptors */
	अगर (mpi_init_descriptors (ai) != SUCCESS)
		जाओ मुक्त_shared;

	वापस 0;
 मुक्त_shared:
	dma_मुक्त_coherent(&pci->dev, PCI_SHARED_LEN, ai->shared,
			  ai->shared_dma);
 मुक्त_auxmap:
	iounmap(ai->pciaux);
 मुक्त_memmap:
	iounmap(ai->pcimem);
 मुक्त_region2:
	release_mem_region(aux_start, aux_len);
 मुक्त_region1:
	release_mem_region(mem_start, mem_len);
 out:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा header_ops airo_header_ops = अणु
	.parse = wll_header_parse,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops airo11_netdev_ops = अणु
	.nकरो_खोलो 		= airo_खोलो,
	.nकरो_stop 		= airo_बंद,
	.nकरो_start_xmit 	= airo_start_xmit11,
	.nकरो_get_stats 		= airo_get_stats,
	.nकरो_set_mac_address	= airo_set_mac_address,
	.nकरो_करो_ioctl		= airo_ioctl,
पूर्ण;

अटल व्योम wअगरi_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &airo11_netdev_ops;
	dev->header_ops = &airo_header_ops;
	dev->wireless_handlers = &airo_handler_def;

	dev->type               = ARPHRD_IEEE80211;
	dev->hard_header_len    = ETH_HLEN;
	dev->mtu                = AIRO_DEF_MTU;
	dev->min_mtu            = 68;
	dev->max_mtu            = MIC_MSGLEN_MAX;
	dev->addr_len           = ETH_ALEN;
	dev->tx_queue_len       = 100;

	eth_broadcast_addr(dev->broadcast);

	dev->flags              = IFF_BROADCAST|IFF_MULTICAST;
पूर्ण

अटल काष्ठा net_device *init_wअगरidev(काष्ठा airo_info *ai,
					काष्ठा net_device *ethdev)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev = alloc_netdev(0, "wifi%d", NET_NAME_UNKNOWN,
					      wअगरi_setup);
	अगर (!dev)
		वापस शून्य;
	dev->ml_priv = ethdev->ml_priv;
	dev->irq = ethdev->irq;
	dev->base_addr = ethdev->base_addr;
	dev->wireless_data = ethdev->wireless_data;
	SET_NETDEV_DEV(dev, ethdev->dev.parent);
	eth_hw_addr_inherit(dev, ethdev);
	err = रेजिस्टर_netdev(dev);
	अगर (err<0) अणु
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण
	वापस dev;
पूर्ण

अटल पूर्णांक reset_card(काष्ठा net_device *dev, पूर्णांक lock)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर (lock && करोwn_पूर्णांकerruptible(&ai->sem))
		वापस -1;
	रुकोbusy (ai);
	OUT4500(ai, COMMAND, CMD_SOFTRESET);
	msleep(200);
	रुकोbusy (ai);
	msleep(200);
	अगर (lock)
		up(&ai->sem);
	वापस 0;
पूर्ण

#घोषणा AIRO_MAX_NETWORK_COUNT	64
अटल पूर्णांक airo_networks_allocate(काष्ठा airo_info *ai)
अणु
	अगर (ai->networks)
		वापस 0;

	ai->networks = kसुस्मृति(AIRO_MAX_NETWORK_COUNT, माप(BSSListElement),
			       GFP_KERNEL);
	अगर (!ai->networks) अणु
		airo_prपूर्णांक_warn("", "Out of memory allocating beacons");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम airo_networks_मुक्त(काष्ठा airo_info *ai)
अणु
	kमुक्त(ai->networks);
	ai->networks = शून्य;
पूर्ण

अटल व्योम airo_networks_initialize(काष्ठा airo_info *ai)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&ai->network_मुक्त_list);
	INIT_LIST_HEAD(&ai->network_list);
	क्रम (i = 0; i < AIRO_MAX_NETWORK_COUNT; i++)
		list_add_tail(&ai->networks[i].list,
			      &ai->network_मुक्त_list);
पूर्ण

अटल स्थिर काष्ठा net_device_ops airo_netdev_ops = अणु
	.nकरो_खोलो		= airo_खोलो,
	.nकरो_stop		= airo_बंद,
	.nकरो_start_xmit		= airo_start_xmit,
	.nकरो_get_stats		= airo_get_stats,
	.nकरो_set_rx_mode	= airo_set_multicast_list,
	.nकरो_set_mac_address	= airo_set_mac_address,
	.nकरो_करो_ioctl		= airo_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mpi_netdev_ops = अणु
	.nकरो_खोलो		= airo_खोलो,
	.nकरो_stop		= airo_बंद,
	.nकरो_start_xmit		= mpi_start_xmit,
	.nकरो_get_stats		= airo_get_stats,
	.nकरो_set_rx_mode	= airo_set_multicast_list,
	.nकरो_set_mac_address	= airo_set_mac_address,
	.nकरो_करो_ioctl		= airo_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;


अटल काष्ठा net_device *_init_airo_card(अचिन्हित लघु irq, पूर्णांक port,
					   पूर्णांक is_pcmcia, काष्ठा pci_dev *pci,
					   काष्ठा device *dmdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा airo_info *ai;
	पूर्णांक i, rc;
	CapabilityRid cap_rid;

	/* Create the network device object. */
	dev = alloc_netdev(माप(*ai), "", NET_NAME_UNKNOWN, ether_setup);
	अगर (!dev) अणु
		airo_prपूर्णांक_err("", "Couldn't alloc_etherdev");
		वापस शून्य;
	पूर्ण

	ai = dev->ml_priv = netdev_priv(dev);
	ai->wअगरidev = शून्य;
	ai->flags = 1 << FLAG_RADIO_DOWN;
	ai->jobs = 0;
	ai->dev = dev;
	अगर (pci && (pci->device == 0x5000 || pci->device == 0xa504)) अणु
		airo_prपूर्णांक_dbg("", "Found an MPI350 card");
		set_bit(FLAG_MPI, &ai->flags);
	पूर्ण
	spin_lock_init(&ai->aux_lock);
	sema_init(&ai->sem, 1);
	ai->config.len = 0;
	ai->pci = pci;
	init_रुकोqueue_head (&ai->thr_रुको);
	ai->tfm = शून्य;
	add_airo_dev(ai);
	ai->APList.len = cpu_to_le16(माप(काष्ठा APListRid));

	अगर (airo_networks_allocate (ai))
		जाओ err_out_मुक्त;
	airo_networks_initialize (ai);

	skb_queue_head_init (&ai->txq);

	/* The Airo-specअगरic entries in the device काष्ठाure. */
	अगर (test_bit(FLAG_MPI,&ai->flags))
		dev->netdev_ops = &mpi_netdev_ops;
	अन्यथा
		dev->netdev_ops = &airo_netdev_ops;
	dev->wireless_handlers = &airo_handler_def;
	ai->wireless_data.spy_data = &ai->spy_data;
	dev->wireless_data = &ai->wireless_data;
	dev->irq = irq;
	dev->base_addr = port;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->max_mtu = MIC_MSGLEN_MAX;

	SET_NETDEV_DEV(dev, dmdev);

	reset_card (dev, 1);
	msleep(400);

	अगर (!is_pcmcia) अणु
		अगर (!request_region(dev->base_addr, 64, DRV_NAME)) अणु
			rc = -EBUSY;
			airo_prपूर्णांक_err(dev->name, "Couldn't request region");
			जाओ err_out_nets;
		पूर्ण
	पूर्ण

	अगर (test_bit(FLAG_MPI,&ai->flags)) अणु
		अगर (mpi_map_card(ai, pci)) अणु
			airo_prपूर्णांक_err("", "Could not map memory");
			जाओ err_out_res;
		पूर्ण
	पूर्ण

	अगर (probe) अणु
		अगर (setup_card(ai, dev->dev_addr, 1) != SUCCESS) अणु
			airo_prपूर्णांक_err(dev->name, "MAC could not be enabled");
			rc = -EIO;
			जाओ err_out_map;
		पूर्ण
	पूर्ण अन्यथा अगर (!test_bit(FLAG_MPI,&ai->flags)) अणु
		ai->bap_पढ़ो = fast_bap_पढ़ो;
		set_bit(FLAG_FLASHING, &ai->flags);
	पूर्ण

	म_नकल(dev->name, "eth%d");
	rc = रेजिस्टर_netdev(dev);
	अगर (rc) अणु
		airo_prपूर्णांक_err(dev->name, "Couldn't register_netdev");
		जाओ err_out_map;
	पूर्ण
	ai->wअगरidev = init_wअगरidev(ai, dev);
	अगर (!ai->wअगरidev)
		जाओ err_out_reg;

	rc = पढ़ोCapabilityRid(ai, &cap_rid, 1);
	अगर (rc != SUCCESS) अणु
		rc = -EIO;
		जाओ err_out_wअगरi;
	पूर्ण
	/* WEP capability discovery */
	ai->wep_capable = (cap_rid.softCap & cpu_to_le16(0x02)) ? 1 : 0;
	ai->max_wep_idx = (cap_rid.softCap & cpu_to_le16(0x80)) ? 3 : 0;

	airo_prपूर्णांक_info(dev->name, "Firmware version %x.%x.%02d",
	                ((le16_to_cpu(cap_rid.softVer) >> 8) & 0xF),
	                (le16_to_cpu(cap_rid.softVer) & 0xFF),
	                le16_to_cpu(cap_rid.softSubVer));

	/* Test क्रम WPA support */
	/* Only firmware versions 5.30.17 or better can करो WPA */
	अगर (le16_to_cpu(cap_rid.softVer) > 0x530
	 || (le16_to_cpu(cap_rid.softVer) == 0x530
	      && le16_to_cpu(cap_rid.softSubVer) >= 17)) अणु
		airo_prपूर्णांक_info(ai->dev->name, "WPA supported.");

		set_bit(FLAG_WPA_CAPABLE, &ai->flags);
		ai->bssListFirst = RID_WPA_BSSLISTFIRST;
		ai->bssListNext = RID_WPA_BSSLISTNEXT;
		ai->bssListRidLen = माप(BSSListRid);
	पूर्ण अन्यथा अणु
		airo_prपूर्णांक_info(ai->dev->name, "WPA unsupported with firmware "
			"versions older than 5.30.17.");

		ai->bssListFirst = RID_BSSLISTFIRST;
		ai->bssListNext = RID_BSSLISTNEXT;
		ai->bssListRidLen = माप(BSSListRid) - माप(BSSListRidExtra);
	पूर्ण

	set_bit(FLAG_REGISTERED,&ai->flags);
	airo_prपूर्णांक_info(dev->name, "MAC enabled %pM", dev->dev_addr);

	/* Allocate the transmit buffers */
	अगर (probe && !test_bit(FLAG_MPI,&ai->flags))
		क्रम (i = 0; i < MAX_FIDS; i++)
			ai->fids[i] = transmit_allocate(ai, AIRO_DEF_MTU, i>=MAX_FIDS/2);

	अगर (setup_proc_entry(dev, dev->ml_priv) < 0)
		जाओ err_out_wअगरi;

	वापस dev;

err_out_wअगरi:
	unरेजिस्टर_netdev(ai->wअगरidev);
	मुक्त_netdev(ai->wअगरidev);
err_out_reg:
	unरेजिस्टर_netdev(dev);
err_out_map:
	अगर (test_bit(FLAG_MPI,&ai->flags) && pci) अणु
		dma_मुक्त_coherent(&pci->dev, PCI_SHARED_LEN, ai->shared,
				  ai->shared_dma);
		iounmap(ai->pciaux);
		iounmap(ai->pcimem);
		mpi_unmap_card(ai->pci);
	पूर्ण
err_out_res:
	अगर (!is_pcmcia)
		release_region(dev->base_addr, 64);
err_out_nets:
	airo_networks_मुक्त(ai);
err_out_मुक्त:
	del_airo_dev(ai);
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण

काष्ठा net_device *init_airo_card(अचिन्हित लघु irq, पूर्णांक port, पूर्णांक is_pcmcia,
				  काष्ठा device *dmdev)
अणु
	वापस _init_airo_card (irq, port, is_pcmcia, शून्य, dmdev);
पूर्ण

EXPORT_SYMBOL(init_airo_card);

अटल पूर्णांक रुकोbusy (काष्ठा airo_info *ai)
अणु
	पूर्णांक delay = 0;
	जबतक ((IN4500(ai, COMMAND) & COMMAND_BUSY) && (delay < 10000)) अणु
		udelay (10);
		अगर ((++delay % 20) == 0)
			OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
	पूर्ण
	वापस delay < 10000;
पूर्ण

पूर्णांक reset_airo_card(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर (reset_card (dev, 1))
		वापस -1;

	अगर (setup_card(ai, dev->dev_addr, 1) != SUCCESS) अणु
		airo_prपूर्णांक_err(dev->name, "MAC could not be enabled");
		वापस -1;
	पूर्ण
	airo_prपूर्णांक_info(dev->name, "MAC enabled %pM", dev->dev_addr);
	/* Allocate the transmit buffers अगर needed */
	अगर (!test_bit(FLAG_MPI,&ai->flags))
		क्रम (i = 0; i < MAX_FIDS; i++)
			ai->fids[i] = transmit_allocate (ai, AIRO_DEF_MTU, i>=MAX_FIDS/2);

	enable_पूर्णांकerrupts(ai);
	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(reset_airo_card);

अटल व्योम airo_send_event(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	जोड़ iwreq_data wrqu;
	StatusRid status_rid;

	clear_bit(JOB_EVENT, &ai->jobs);
	PC4500_पढ़ोrid(ai, RID_STATUS, &status_rid, माप(status_rid), 0);
	up(&ai->sem);
	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	स_नकल(wrqu.ap_addr.sa_data, status_rid.bssid[0], ETH_ALEN);
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/* Send event to user space */
	wireless_send_event(dev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

अटल व्योम airo_process_scan_results (काष्ठा airo_info *ai)
अणु
	जोड़ iwreq_data	wrqu;
	BSSListRid bss;
	पूर्णांक rc;
	BSSListElement * loop_net;
	BSSListElement * पंचांगp_net;

	/* Blow away current list of scan results */
	list_क्रम_each_entry_safe (loop_net, पंचांगp_net, &ai->network_list, list) अणु
		list_move_tail (&loop_net->list, &ai->network_मुक्त_list);
		/* Don't blow away ->list, just BSS data */
		स_रखो (loop_net, 0, माप (loop_net->bss));
	पूर्ण

	/* Try to पढ़ो the first entry of the scan result */
	rc = PC4500_पढ़ोrid(ai, ai->bssListFirst, &bss, ai->bssListRidLen, 0);
	अगर ((rc) || (bss.index == cpu_to_le16(0xffff))) अणु
		/* No scan results */
		जाओ out;
	पूर्ण

	/* Read and parse all entries */
	पंचांगp_net = शून्य;
	जबतक ((!rc) && (bss.index != cpu_to_le16(0xffff))) अणु
		/* Grab a network off the मुक्त list */
		अगर (!list_empty(&ai->network_मुक्त_list)) अणु
			पंचांगp_net = list_entry(ai->network_मुक्त_list.next,
					    BSSListElement, list);
			list_del(ai->network_मुक्त_list.next);
		पूर्ण

		अगर (पंचांगp_net != शून्य) अणु
			स_नकल(पंचांगp_net, &bss, माप(पंचांगp_net->bss));
			list_add_tail(&पंचांगp_net->list, &ai->network_list);
			पंचांगp_net = शून्य;
		पूर्ण

		/* Read next entry */
		rc = PC4500_पढ़ोrid(ai, ai->bssListNext,
				    &bss, ai->bssListRidLen, 0);
	पूर्ण

out:
	/* ग_लिखो APList back (we cleared it in airo_set_scan) */
	disable_MAC(ai, 2);
	ग_लिखोAPListRid(ai, &ai->APList, 0);
	enable_MAC(ai, 0);

	ai->scan_समयout = 0;
	clear_bit(JOB_SCAN_RESULTS, &ai->jobs);
	up(&ai->sem);

	/* Send an empty event to user space.
	 * We करोn't send the received data on
	 * the event because it would require
	 * us to करो complex transcoding, and
	 * we want to minimise the work करोne in
	 * the irq handler. Use a request to
	 * extract the data - Jean II */
	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(ai->dev, SIOCGIWSCAN, &wrqu, शून्य);
पूर्ण

अटल पूर्णांक airo_thपढ़ो(व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक locked;

	set_मुक्तzable();
	जबतक (1) अणु
		/* make swsusp happy with our thपढ़ो */
		try_to_मुक्तze();

		अगर (test_bit(JOB_DIE, &ai->jobs))
			अवरोध;

		अगर (ai->jobs) अणु
			locked = करोwn_पूर्णांकerruptible(&ai->sem);
		पूर्ण अन्यथा अणु
			रुको_queue_entry_t रुको;

			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&ai->thr_रुको, &रुको);
			क्रम (;;) अणु
				set_current_state(TASK_INTERRUPTIBLE);
				अगर (ai->jobs)
					अवरोध;
				अगर (ai->expires || ai->scan_समयout) अणु
					अगर (ai->scan_समयout &&
							समय_after_eq(jअगरfies, ai->scan_समयout)) अणु
						set_bit(JOB_SCAN_RESULTS, &ai->jobs);
						अवरोध;
					पूर्ण अन्यथा अगर (ai->expires &&
							समय_after_eq(jअगरfies, ai->expires)) अणु
						set_bit(JOB_AUTOWEP, &ai->jobs);
						अवरोध;
					पूर्ण
					अगर (!kthपढ़ो_should_stop() &&
					    !मुक्तzing(current)) अणु
						अचिन्हित दीर्घ wake_at;
						अगर (!ai->expires || !ai->scan_समयout) अणु
							wake_at = max(ai->expires,
								ai->scan_समयout);
						पूर्ण अन्यथा अणु
							wake_at = min(ai->expires,
								ai->scan_समयout);
						पूर्ण
						schedule_समयout(wake_at - jअगरfies);
						जारी;
					पूर्ण
				पूर्ण अन्यथा अगर (!kthपढ़ो_should_stop() &&
					   !मुक्तzing(current)) अणु
					schedule();
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण
			__set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&ai->thr_रुको, &रुको);
			locked = 1;
		पूर्ण

		अगर (locked)
			जारी;

		अगर (test_bit(JOB_DIE, &ai->jobs)) अणु
			up(&ai->sem);
			अवरोध;
		पूर्ण

		अगर (ai->घातer.event || test_bit(FLAG_FLASHING, &ai->flags)) अणु
			up(&ai->sem);
			जारी;
		पूर्ण

		अगर (test_bit(JOB_XMIT, &ai->jobs))
			airo_end_xmit(dev, true);
		अन्यथा अगर (test_bit(JOB_XMIT11, &ai->jobs))
			airo_end_xmit11(dev, true);
		अन्यथा अगर (test_bit(JOB_STATS, &ai->jobs))
			airo_पढ़ो_stats(dev);
		अन्यथा अगर (test_bit(JOB_PROMISC, &ai->jobs))
			airo_set_promisc(ai, true);
		अन्यथा अगर (test_bit(JOB_MIC, &ai->jobs))
			micinit(ai);
		अन्यथा अगर (test_bit(JOB_EVENT, &ai->jobs))
			airo_send_event(dev);
		अन्यथा अगर (test_bit(JOB_AUTOWEP, &ai->jobs))
			समयr_func(dev);
		अन्यथा अगर (test_bit(JOB_SCAN_RESULTS, &ai->jobs))
			airo_process_scan_results(ai);
		अन्यथा  /* Shouldn't get here, but we make sure to unlock */
			up(&ai->sem);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक header_len(__le16 ctl)
अणु
	u16 fc = le16_to_cpu(ctl);
	चयन (fc & 0xc) अणु
	हाल 4:
		अगर ((fc & 0xe0) == 0xc0)
			वापस 10;	/* one-address control packet */
		वापस 16;	/* two-address control packet */
	हाल 8:
		अगर ((fc & 0x300) == 0x300)
			वापस 30;	/* WDS packet */
	पूर्ण
	वापस 24;
पूर्ण

अटल व्योम airo_handle_cisco_mic(काष्ठा airo_info *ai)
अणु
	अगर (test_bit(FLAG_MIC_CAPABLE, &ai->flags)) अणु
		set_bit(JOB_MIC, &ai->jobs);
		wake_up_पूर्णांकerruptible(&ai->thr_रुको);
	पूर्ण
पूर्ण

/* Airo Status codes */
#घोषणा STAT_NOBEACON	0x8000 /* Loss of sync - missed beacons */
#घोषणा STAT_MAXRETRIES	0x8001 /* Loss of sync - max retries */
#घोषणा STAT_MAXARL	0x8002 /* Loss of sync - average retry level exceeded*/
#घोषणा STAT_FORCELOSS	0x8003 /* Loss of sync - host request */
#घोषणा STAT_TSFSYNC	0x8004 /* Loss of sync - TSF synchronization */
#घोषणा STAT_DEAUTH	0x8100 /* low byte is 802.11 reason code */
#घोषणा STAT_DISASSOC	0x8200 /* low byte is 802.11 reason code */
#घोषणा STAT_ASSOC_FAIL	0x8400 /* low byte is 802.11 reason code */
#घोषणा STAT_AUTH_FAIL	0x0300 /* low byte is 802.11 reason code */
#घोषणा STAT_ASSOC	0x0400 /* Associated */
#घोषणा STAT_REASSOC    0x0600 /* Reassociated?  Only on firmware >= 5.30.17 */

अटल व्योम airo_prपूर्णांक_status(स्थिर अक्षर *devname, u16 status)
अणु
	u8 reason = status & 0xFF;

	चयन (status & 0xFF00) अणु
	हाल STAT_NOBEACON:
		चयन (status) अणु
		हाल STAT_NOBEACON:
			airo_prपूर्णांक_dbg(devname, "link lost (missed beacons)");
			अवरोध;
		हाल STAT_MAXRETRIES:
		हाल STAT_MAXARL:
			airo_prपूर्णांक_dbg(devname, "link lost (max retries)");
			अवरोध;
		हाल STAT_FORCELOSS:
			airo_prपूर्णांक_dbg(devname, "link lost (local choice)");
			अवरोध;
		हाल STAT_TSFSYNC:
			airo_prपूर्णांक_dbg(devname, "link lost (TSF sync lost)");
			अवरोध;
		शेष:
			airo_prपूर्णांक_dbg(devname, "unknown status %x\n", status);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल STAT_DEAUTH:
		airo_prपूर्णांक_dbg(devname, "deauthenticated (reason: %d)", reason);
		अवरोध;
	हाल STAT_DISASSOC:
		airo_prपूर्णांक_dbg(devname, "disassociated (reason: %d)", reason);
		अवरोध;
	हाल STAT_ASSOC_FAIL:
		airo_prपूर्णांक_dbg(devname, "association failed (reason: %d)",
			       reason);
		अवरोध;
	हाल STAT_AUTH_FAIL:
		airo_prपूर्णांक_dbg(devname, "authentication failed (reason: %d)",
			       reason);
		अवरोध;
	हाल STAT_ASSOC:
	हाल STAT_REASSOC:
		अवरोध;
	शेष:
		airo_prपूर्णांक_dbg(devname, "unknown status %x\n", status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम airo_handle_link(काष्ठा airo_info *ai)
अणु
	जोड़ iwreq_data wrqu;
	पूर्णांक scan_क्रमceloss = 0;
	u16 status;

	/* Get new status and acknowledge the link change */
	status = le16_to_cpu(IN4500(ai, LINKSTAT));
	OUT4500(ai, EVACK, EV_LINK);

	अगर ((status == STAT_FORCELOSS) && (ai->scan_समयout > 0))
		scan_क्रमceloss = 1;

	airo_prपूर्णांक_status(ai->dev->name, status);

	अगर ((status == STAT_ASSOC) || (status == STAT_REASSOC)) अणु
		अगर (स्वतः_wep)
			ai->expires = 0;
		अगर (ai->list_bss_task)
			wake_up_process(ai->list_bss_task);
		set_bit(FLAG_UPDATE_UNI, &ai->flags);
		set_bit(FLAG_UPDATE_MULTI, &ai->flags);

		set_bit(JOB_EVENT, &ai->jobs);
		wake_up_पूर्णांकerruptible(&ai->thr_रुको);

		netअगर_carrier_on(ai->dev);
	पूर्ण अन्यथा अगर (!scan_क्रमceloss) अणु
		अगर (स्वतः_wep && !ai->expires) अणु
			ai->expires = RUN_AT(3*HZ);
			wake_up_पूर्णांकerruptible(&ai->thr_रुको);
		पूर्ण

		/* Send event to user space */
		eth_zero_addr(wrqu.ap_addr.sa_data);
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		wireless_send_event(ai->dev, SIOCGIWAP, &wrqu, शून्य);
		netअगर_carrier_off(ai->dev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(ai->dev);
	पूर्ण
पूर्ण

अटल व्योम airo_handle_rx(काष्ठा airo_info *ai)
अणु
	काष्ठा sk_buff *skb = शून्य;
	__le16 fc, v, *buffer, पंचांगpbuf[4];
	u16 len, hdrlen = 0, gap, fid;
	काष्ठा rx_hdr hdr;
	पूर्णांक success = 0;

	अगर (test_bit(FLAG_MPI, &ai->flags)) अणु
		अगर (test_bit(FLAG_802_11, &ai->flags))
			mpi_receive_802_11(ai);
		अन्यथा
			mpi_receive_802_3(ai);
		OUT4500(ai, EVACK, EV_RX);
		वापस;
	पूर्ण

	fid = IN4500(ai, RXFID);

	/* Get the packet length */
	अगर (test_bit(FLAG_802_11, &ai->flags)) अणु
		bap_setup (ai, fid, 4, BAP0);
		bap_पढ़ो (ai, (__le16*)&hdr, माप(hdr), BAP0);
		/* Bad CRC. Ignore packet */
		अगर (le16_to_cpu(hdr.status) & 2)
			hdr.len = 0;
		अगर (ai->wअगरidev == शून्य)
			hdr.len = 0;
	पूर्ण अन्यथा अणु
		bap_setup(ai, fid, 0x36, BAP0);
		bap_पढ़ो(ai, &hdr.len, 2, BAP0);
	पूर्ण
	len = le16_to_cpu(hdr.len);

	अगर (len > AIRO_DEF_MTU) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Bad size %d", len);
		जाओ करोne;
	पूर्ण
	अगर (len == 0)
		जाओ करोne;

	अगर (test_bit(FLAG_802_11, &ai->flags)) अणु
		bap_पढ़ो(ai, &fc, माप (fc), BAP0);
		hdrlen = header_len(fc);
	पूर्ण अन्यथा
		hdrlen = ETH_ALEN * 2;

	skb = dev_alloc_skb(len + hdrlen + 2 + 2);
	अगर (!skb) अणु
		ai->dev->stats.rx_dropped++;
		जाओ करोne;
	पूर्ण

	skb_reserve(skb, 2); /* This way the IP header is aligned */
	buffer = skb_put(skb, len + hdrlen);
	अगर (test_bit(FLAG_802_11, &ai->flags)) अणु
		buffer[0] = fc;
		bap_पढ़ो(ai, buffer + 1, hdrlen - 2, BAP0);
		अगर (hdrlen == 24)
			bap_पढ़ो(ai, पंचांगpbuf, 6, BAP0);

		bap_पढ़ो(ai, &v, माप(v), BAP0);
		gap = le16_to_cpu(v);
		अगर (gap) अणु
			अगर (gap <= 8) अणु
				bap_पढ़ो(ai, पंचांगpbuf, gap, BAP0);
			पूर्ण अन्यथा अणु
				airo_prपूर्णांक_err(ai->dev->name, "gaplen too "
					"big. Problems will follow...");
			पूर्ण
		पूर्ण
		bap_पढ़ो(ai, buffer + hdrlen/2, len, BAP0);
	पूर्ण अन्यथा अणु
		MICBuffer micbuf;

		bap_पढ़ो(ai, buffer, ETH_ALEN * 2, BAP0);
		अगर (ai->micstats.enabled) अणु
			bap_पढ़ो(ai, (__le16 *) &micbuf, माप (micbuf), BAP0);
			अगर (ntohs(micbuf.typelen) > 0x05DC)
				bap_setup(ai, fid, 0x44, BAP0);
			अन्यथा अणु
				अगर (len <= माप (micbuf)) अणु
					dev_kमुक्त_skb_irq(skb);
					जाओ करोne;
				पूर्ण

				len -= माप(micbuf);
				skb_trim(skb, len + hdrlen);
			पूर्ण
		पूर्ण

		bap_पढ़ो(ai, buffer + ETH_ALEN, len, BAP0);
		अगर (decapsulate(ai, &micbuf, (etherHead*) buffer, len))
			dev_kमुक्त_skb_irq (skb);
		अन्यथा
			success = 1;
	पूर्ण

#अगर_घोषित WIRELESS_SPY
	अगर (success && (ai->spy_data.spy_number > 0)) अणु
		अक्षर *sa;
		काष्ठा iw_quality wstats;

		/* Prepare spy data : addr + qual */
		अगर (!test_bit(FLAG_802_11, &ai->flags)) अणु
			sa = (अक्षर *) buffer + 6;
			bap_setup(ai, fid, 8, BAP0);
			bap_पढ़ो(ai, (__le16 *) hdr.rssi, 2, BAP0);
		पूर्ण अन्यथा
			sa = (अक्षर *) buffer + 10;
		wstats.qual = hdr.rssi[0];
		अगर (ai->rssi)
			wstats.level = 0x100 - ai->rssi[hdr.rssi[1]].rssidBm;
		अन्यथा
			wstats.level = (hdr.rssi[1] + 321) / 2;
		wstats.noise = ai->wstats.qual.noise;
		wstats.updated =  IW_QUAL_LEVEL_UPDATED
				| IW_QUAL_QUAL_UPDATED
				| IW_QUAL_DBM;
		/* Update spy records */
		wireless_spy_update(ai->dev, sa, &wstats);
	पूर्ण
#पूर्ण_अगर /* WIRELESS_SPY */

करोne:
	OUT4500(ai, EVACK, EV_RX);

	अगर (success) अणु
		अगर (test_bit(FLAG_802_11, &ai->flags)) अणु
			skb_reset_mac_header(skb);
			skb->pkt_type = PACKET_OTHERHOST;
			skb->dev = ai->wअगरidev;
			skb->protocol = htons(ETH_P_802_2);
		पूर्ण अन्यथा
			skb->protocol = eth_type_trans(skb, ai->dev);
		skb->ip_summed = CHECKSUM_NONE;

		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल व्योम airo_handle_tx(काष्ठा airo_info *ai, u16 status)
अणु
	पूर्णांक i, index = -1;
	u16 fid;

	अगर (test_bit(FLAG_MPI, &ai->flags)) अणु
		अचिन्हित दीर्घ flags;

		अगर (status & EV_TXEXC)
			get_tx_error(ai, -1);

		spin_lock_irqsave(&ai->aux_lock, flags);
		अगर (!skb_queue_empty(&ai->txq)) अणु
			spin_unlock_irqrestore(&ai->aux_lock, flags);
			mpi_send_packet(ai->dev);
		पूर्ण अन्यथा अणु
			clear_bit(FLAG_PENDING_XMIT, &ai->flags);
			spin_unlock_irqrestore(&ai->aux_lock, flags);
			netअगर_wake_queue(ai->dev);
		पूर्ण
		OUT4500(ai, EVACK, status & (EV_TX | EV_TXCPY | EV_TXEXC));
		वापस;
	पूर्ण

	fid = IN4500(ai, TXCOMPLFID);

	क्रम (i = 0; i < MAX_FIDS; i++) अणु
		अगर ((ai->fids[i] & 0xffff) == fid)
			index = i;
	पूर्ण

	अगर (index != -1) अणु
		अगर (status & EV_TXEXC)
			get_tx_error(ai, index);

		OUT4500(ai, EVACK, status & (EV_TX | EV_TXEXC));

		/* Set up to be used again */
		ai->fids[index] &= 0xffff;
		अगर (index < MAX_FIDS / 2) अणु
			अगर (!test_bit(FLAG_PENDING_XMIT, &ai->flags))
				netअगर_wake_queue(ai->dev);
		पूर्ण अन्यथा अणु
			अगर (!test_bit(FLAG_PENDING_XMIT11, &ai->flags))
				netअगर_wake_queue(ai->wअगरidev);
		पूर्ण
	पूर्ण अन्यथा अणु
		OUT4500(ai, EVACK, status & (EV_TX | EV_TXCPY | EV_TXEXC));
		airo_prपूर्णांक_err(ai->dev->name, "Unallocated FID was used to xmit");
	पूर्ण
पूर्ण

अटल irqवापस_t airo_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	u16 status, savedInterrupts = 0;
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक handled = 0;

	अगर (!netअगर_device_present(dev))
		वापस IRQ_NONE;

	क्रम (;;) अणु
		status = IN4500(ai, EVSTAT);
		अगर (!(status & STATUS_INTS) || (status == 0xffff))
			अवरोध;

		handled = 1;

		अगर (status & EV_AWAKE) अणु
			OUT4500(ai, EVACK, EV_AWAKE);
			OUT4500(ai, EVACK, EV_AWAKE);
		पूर्ण

		अगर (!savedInterrupts) अणु
			savedInterrupts = IN4500(ai, EVINTEN);
			OUT4500(ai, EVINTEN, 0);
		पूर्ण

		अगर (status & EV_MIC) अणु
			OUT4500(ai, EVACK, EV_MIC);
			airo_handle_cisco_mic(ai);
		पूर्ण

		अगर (status & EV_LINK) अणु
			/* Link status changed */
			airo_handle_link(ai);
		पूर्ण

		/* Check to see अगर there is something to receive */
		अगर (status & EV_RX)
			airo_handle_rx(ai);

		/* Check to see अगर a packet has been transmitted */
		अगर (status & (EV_TX | EV_TXCPY | EV_TXEXC))
			airo_handle_tx(ai, status);

		अगर (status & ~STATUS_INTS & ~IGNORE_INTS) अणु
			airo_prपूर्णांक_warn(ai->dev->name, "Got weird status %x",
				status & ~STATUS_INTS & ~IGNORE_INTS);
		पूर्ण
	पूर्ण

	अगर (savedInterrupts)
		OUT4500(ai, EVINTEN, savedInterrupts);

	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 *  Routines to talk to the card
 */

/*
 *  This was originally written क्रम the 4500, hence the name
 *  NOTE:  If use with 8bit mode and SMP bad things will happen!
 *         Why would some one करो 8 bit IO in an SMP machine?!?
 */
अटल व्योम OUT4500(काष्ठा airo_info *ai, u16 reg, u16 val)
अणु
	अगर (test_bit(FLAG_MPI,&ai->flags))
		reg <<= 1;
	अगर (!करो8bitIO)
		outw(val, ai->dev->base_addr + reg);
	अन्यथा अणु
		outb(val & 0xff, ai->dev->base_addr + reg);
		outb(val >> 8, ai->dev->base_addr + reg + 1);
	पूर्ण
पूर्ण

अटल u16 IN4500(काष्ठा airo_info *ai, u16 reg)
अणु
	अचिन्हित लघु rc;

	अगर (test_bit(FLAG_MPI,&ai->flags))
		reg <<= 1;
	अगर (!करो8bitIO)
		rc = inw(ai->dev->base_addr + reg);
	अन्यथा अणु
		rc = inb(ai->dev->base_addr + reg);
		rc += ((पूर्णांक)inb(ai->dev->base_addr + reg + 1)) << 8;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक enable_MAC(काष्ठा airo_info *ai, पूर्णांक lock)
अणु
	पूर्णांक rc;
	Cmd cmd;
	Resp rsp;

	/* FLAG_RADIO_OFF : Radio disabled via /proc or Wireless Extensions
	 * FLAG_RADIO_DOWN : Radio disabled via "ifconfig ethX down"
	 * Note : we could try to use !netअगर_running(dev) in enable_MAC()
	 * instead of this flag, but I करोn't trust it *within* the
	 * खोलो/बंद functions, and testing both flags together is
	 * "cheaper" - Jean II */
	अगर (ai->flags & FLAG_RADIO_MASK) वापस SUCCESS;

	अगर (lock && करोwn_पूर्णांकerruptible(&ai->sem))
		वापस -ERESTARTSYS;

	अगर (!test_bit(FLAG_ENABLED, &ai->flags)) अणु
		स_रखो(&cmd, 0, माप(cmd));
		cmd.cmd = MAC_ENABLE;
		rc = issuecommand(ai, &cmd, &rsp, true);
		अगर (rc == SUCCESS)
			set_bit(FLAG_ENABLED, &ai->flags);
	पूर्ण अन्यथा
		rc = SUCCESS;

	अगर (lock)
	    up(&ai->sem);

	अगर (rc)
		airo_prपूर्णांक_err(ai->dev->name, "Cannot enable MAC");
	अन्यथा अगर ((rsp.status & 0xFF00) != 0) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Bad MAC enable reason=%x, "
			"rid=%x, offset=%d", rsp.rsp0, rsp.rsp1, rsp.rsp2);
		rc = ERROR;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम disable_MAC(काष्ठा airo_info *ai, पूर्णांक lock)
अणु
        Cmd cmd;
	Resp rsp;

	अगर (lock == 1 && करोwn_पूर्णांकerruptible(&ai->sem))
		वापस;

	अगर (test_bit(FLAG_ENABLED, &ai->flags)) अणु
		अगर (lock != 2) /* lock == 2 means करोn't disable carrier */
			netअगर_carrier_off(ai->dev);
		स_रखो(&cmd, 0, माप(cmd));
		cmd.cmd = MAC_DISABLE; // disable in हाल alपढ़ोy enabled
		issuecommand(ai, &cmd, &rsp, true);
		clear_bit(FLAG_ENABLED, &ai->flags);
	पूर्ण
	अगर (lock == 1)
		up(&ai->sem);
पूर्ण

अटल व्योम enable_पूर्णांकerrupts(काष्ठा airo_info *ai)
अणु
	/* Enable the पूर्णांकerrupts */
	OUT4500(ai, EVINTEN, STATUS_INTS);
पूर्ण

अटल व्योम disable_पूर्णांकerrupts(काष्ठा airo_info *ai)
अणु
	OUT4500(ai, EVINTEN, 0);
पूर्ण

अटल व्योम mpi_receive_802_3(काष्ठा airo_info *ai)
अणु
	RxFid rxd;
	पूर्णांक len = 0;
	काष्ठा sk_buff *skb;
	अक्षर *buffer;
	पूर्णांक off = 0;
	MICBuffer micbuf;

	स_नकल_fromio(&rxd, ai->rxfids[0].card_ram_off, माप(rxd));
	/* Make sure we got something */
	अगर (rxd.rdy && rxd.valid == 0) अणु
		len = rxd.len + 12;
		अगर (len < 12 || len > 2048)
			जाओ badrx;

		skb = dev_alloc_skb(len);
		अगर (!skb) अणु
			ai->dev->stats.rx_dropped++;
			जाओ badrx;
		पूर्ण
		buffer = skb_put(skb, len);
		स_नकल(buffer, ai->rxfids[0].भव_host_addr, ETH_ALEN * 2);
		अगर (ai->micstats.enabled) अणु
			स_नकल(&micbuf,
				ai->rxfids[0].भव_host_addr + ETH_ALEN * 2,
				माप(micbuf));
			अगर (ntohs(micbuf.typelen) <= 0x05DC) अणु
				अगर (len <= माप(micbuf) + ETH_ALEN * 2)
					जाओ badmic;

				off = माप(micbuf);
				skb_trim (skb, len - off);
			पूर्ण
		पूर्ण
		स_नकल(buffer + ETH_ALEN * 2,
			ai->rxfids[0].भव_host_addr + ETH_ALEN * 2 + off,
			len - ETH_ALEN * 2 - off);
		अगर (decapsulate (ai, &micbuf, (etherHead*)buffer, len - off - ETH_ALEN * 2)) अणु
badmic:
			dev_kमुक्त_skb_irq (skb);
			जाओ badrx;
		पूर्ण
#अगर_घोषित WIRELESS_SPY
		अगर (ai->spy_data.spy_number > 0) अणु
			अक्षर *sa;
			काष्ठा iw_quality wstats;
			/* Prepare spy data : addr + qual */
			sa = buffer + ETH_ALEN;
			wstats.qual = 0; /* XXX Where करो I get that info from ??? */
			wstats.level = 0;
			wstats.updated = 0;
			/* Update spy records */
			wireless_spy_update(ai->dev, sa, &wstats);
		पूर्ण
#पूर्ण_अगर /* WIRELESS_SPY */

		skb->ip_summed = CHECKSUM_NONE;
		skb->protocol = eth_type_trans(skb, ai->dev);
		netअगर_rx(skb);
	पूर्ण
badrx:
	अगर (rxd.valid == 0) अणु
		rxd.valid = 1;
		rxd.rdy = 0;
		rxd.len = PKTSIZE;
		स_नकल_toio(ai->rxfids[0].card_ram_off, &rxd, माप(rxd));
	पूर्ण
पूर्ण

अटल व्योम mpi_receive_802_11(काष्ठा airo_info *ai)
अणु
	RxFid rxd;
	काष्ठा sk_buff *skb = शून्य;
	u16 len, hdrlen = 0;
	__le16 fc;
	काष्ठा rx_hdr hdr;
	u16 gap;
	u16 *buffer;
	अक्षर *ptr = ai->rxfids[0].भव_host_addr + 4;

	स_नकल_fromio(&rxd, ai->rxfids[0].card_ram_off, माप(rxd));
	स_नकल ((अक्षर *)&hdr, ptr, माप(hdr));
	ptr += माप(hdr);
	/* Bad CRC. Ignore packet */
	अगर (le16_to_cpu(hdr.status) & 2)
		hdr.len = 0;
	अगर (ai->wअगरidev == शून्य)
		hdr.len = 0;
	len = le16_to_cpu(hdr.len);
	अगर (len > AIRO_DEF_MTU) अणु
		airo_prपूर्णांक_err(ai->dev->name, "Bad size %d", len);
		जाओ badrx;
	पूर्ण
	अगर (len == 0)
		जाओ badrx;

	fc = get_unaligned((__le16 *)ptr);
	hdrlen = header_len(fc);

	skb = dev_alloc_skb(len + hdrlen + 2);
	अगर (!skb) अणु
		ai->dev->stats.rx_dropped++;
		जाओ badrx;
	पूर्ण
	buffer = skb_put(skb, len + hdrlen);
	स_नकल ((अक्षर *)buffer, ptr, hdrlen);
	ptr += hdrlen;
	अगर (hdrlen == 24)
		ptr += 6;
	gap = get_unaligned_le16(ptr);
	ptr += माप(__le16);
	अगर (gap) अणु
		अगर (gap <= 8)
			ptr += gap;
		अन्यथा
			airo_prपूर्णांक_err(ai->dev->name,
			    "gaplen too big. Problems will follow...");
	पूर्ण
	स_नकल ((अक्षर *)buffer + hdrlen, ptr, len);
	ptr += len;
#अगर_घोषित IW_WIRELESS_SPY	  /* defined in iw_handler.h */
	अगर (ai->spy_data.spy_number > 0) अणु
		अक्षर *sa;
		काष्ठा iw_quality wstats;
		/* Prepare spy data : addr + qual */
		sa = (अक्षर*)buffer + 10;
		wstats.qual = hdr.rssi[0];
		अगर (ai->rssi)
			wstats.level = 0x100 - ai->rssi[hdr.rssi[1]].rssidBm;
		अन्यथा
			wstats.level = (hdr.rssi[1] + 321) / 2;
		wstats.noise = ai->wstats.qual.noise;
		wstats.updated = IW_QUAL_QUAL_UPDATED
			| IW_QUAL_LEVEL_UPDATED
			| IW_QUAL_DBM;
		/* Update spy records */
		wireless_spy_update(ai->dev, sa, &wstats);
	पूर्ण
#पूर्ण_अगर /* IW_WIRELESS_SPY */
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->dev = ai->wअगरidev;
	skb->protocol = htons(ETH_P_802_2);
	skb->ip_summed = CHECKSUM_NONE;
	netअगर_rx(skb);

badrx:
	अगर (rxd.valid == 0) अणु
		rxd.valid = 1;
		rxd.rdy = 0;
		rxd.len = PKTSIZE;
		स_नकल_toio(ai->rxfids[0].card_ram_off, &rxd, माप(rxd));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम set_auth_type(काष्ठा airo_info *local, पूर्णांक auth_type)
अणु
	local->config.authType = auth_type;
	/* Cache the last auth type used (of AUTH_OPEN and AUTH_ENCRYPT).
	 * Used by airo_set_auth()
	 */
	अगर (auth_type == AUTH_OPEN || auth_type == AUTH_ENCRYPT)
		local->last_auth = auth_type;
पूर्ण

अटल पूर्णांक noअंतरभूत_क्रम_stack airo_पढ़ोconfig(काष्ठा airo_info *ai, u8 *mac, पूर्णांक lock)
अणु
	पूर्णांक i, status;
	/* large variables, so करोn't अंतरभूत this function,
	 * maybe change to kदो_स्मृति
	 */
	tdsRssiRid rssi_rid;
	CapabilityRid cap_rid;

	kमुक्त(ai->SSID);
	ai->SSID = शून्य;
	// general configuration (पढ़ो/modअगरy/ग_लिखो)
	status = पढ़ोConfigRid(ai, lock);
	अगर (status != SUCCESS) वापस ERROR;

	status = पढ़ोCapabilityRid(ai, &cap_rid, lock);
	अगर (status != SUCCESS) वापस ERROR;

	status = PC4500_पढ़ोrid(ai, RID_RSSI, &rssi_rid, माप(rssi_rid), lock);
	अगर (status == SUCCESS) अणु
		अगर (ai->rssi || (ai->rssi = kदो_स्मृति(512, GFP_KERNEL)) != शून्य)
			स_नकल(ai->rssi, (u8*)&rssi_rid + 2, 512); /* Skip RID length member */
	पूर्ण
	अन्यथा अणु
		kमुक्त(ai->rssi);
		ai->rssi = शून्य;
		अगर (cap_rid.softCap & cpu_to_le16(8))
			ai->config.rmode |= RXMODE_NORMALIZED_RSSI;
		अन्यथा
			airo_prपूर्णांक_warn(ai->dev->name, "unknown received signal "
					"level scale");
	पूर्ण
	ai->config.opmode = adhoc ? MODE_STA_IBSS : MODE_STA_ESS;
	set_auth_type(ai, AUTH_OPEN);
	ai->config.modulation = MOD_CCK;

	अगर (le16_to_cpu(cap_rid.len) >= माप(cap_rid) &&
	    (cap_rid.extSoftCap & cpu_to_le16(1)) &&
	    micsetup(ai) == SUCCESS) अणु
		ai->config.opmode |= MODE_MIC;
		set_bit(FLAG_MIC_CAPABLE, &ai->flags);
	पूर्ण

	/* Save off the MAC */
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac[i] = ai->config.macAddr[i];
	पूर्ण

	/* Check to see अगर there are any insmod configured
	   rates to add */
	अगर (rates[0]) अणु
		स_रखो(ai->config.rates, 0, माप(ai->config.rates));
		क्रम (i = 0; i < 8 && rates[i]; i++) अणु
			ai->config.rates[i] = rates[i];
		पूर्ण
	पूर्ण
	set_bit (FLAG_COMMIT, &ai->flags);

	वापस SUCCESS;
पूर्ण


अटल u16 setup_card(काष्ठा airo_info *ai, u8 *mac, पूर्णांक lock)
अणु
	Cmd cmd;
	Resp rsp;
	पूर्णांक status;
	SsidRid mySsid;
	__le16 lastindex;
	WepKeyRid wkr;
	पूर्णांक rc;

	स_रखो(&mySsid, 0, माप(mySsid));
	kमुक्त (ai->flash);
	ai->flash = शून्य;

	/* The NOP is the first step in getting the card going */
	cmd.cmd = NOP;
	cmd.parm0 = cmd.parm1 = cmd.parm2 = 0;
	अगर (lock && करोwn_पूर्णांकerruptible(&ai->sem))
		वापस ERROR;
	अगर (issuecommand(ai, &cmd, &rsp, true) != SUCCESS) अणु
		अगर (lock)
			up(&ai->sem);
		वापस ERROR;
	पूर्ण
	disable_MAC(ai, 0);

	// Let's figure out अगर we need to use the AUX port
	अगर (!test_bit(FLAG_MPI,&ai->flags)) अणु
		cmd.cmd = CMD_ENABLEAUX;
		अगर (issuecommand(ai, &cmd, &rsp, true) != SUCCESS) अणु
			अगर (lock)
				up(&ai->sem);
			airo_prपूर्णांक_err(ai->dev->name, "Error checking for AUX port");
			वापस ERROR;
		पूर्ण
		अगर (!aux_bap || rsp.status & 0xff00) अणु
			ai->bap_पढ़ो = fast_bap_पढ़ो;
			airo_prपूर्णांक_dbg(ai->dev->name, "Doing fast bap_reads");
		पूर्ण अन्यथा अणु
			ai->bap_पढ़ो = aux_bap_पढ़ो;
			airo_prपूर्णांक_dbg(ai->dev->name, "Doing AUX bap_reads");
		पूर्ण
	पूर्ण
	अगर (lock)
		up(&ai->sem);
	अगर (ai->config.len == 0) अणु
		status = airo_पढ़ोconfig(ai, mac, lock);
		अगर (status != SUCCESS)
			वापस ERROR;
	पूर्ण

	/* Setup the SSIDs अगर present */
	अगर (ssids[0]) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 3 && ssids[i]; i++) अणु
			माप_प्रकार len = म_माप(ssids[i]);
			अगर (len > 32)
				len = 32;
			mySsid.ssids[i].len = cpu_to_le16(len);
			स_नकल(mySsid.ssids[i].ssid, ssids[i], len);
		पूर्ण
		mySsid.len = cpu_to_le16(माप(mySsid));
	पूर्ण

	status = ग_लिखोConfigRid(ai, lock);
	अगर (status != SUCCESS) वापस ERROR;

	/* Set up the SSID list */
	अगर (ssids[0]) अणु
		status = ग_लिखोSsidRid(ai, &mySsid, lock);
		अगर (status != SUCCESS) वापस ERROR;
	पूर्ण

	status = enable_MAC(ai, lock);
	अगर (status != SUCCESS)
		वापस ERROR;

	/* Grab the initial wep key, we gotta save it क्रम स्वतः_wep */
	rc = पढ़ोWepKeyRid(ai, &wkr, 1, lock);
	अगर (rc == SUCCESS) करो अणु
		lastindex = wkr.kindex;
		अगर (wkr.kindex == cpu_to_le16(0xffff)) अणु
			ai->defindex = wkr.mac[0];
		पूर्ण
		rc = पढ़ोWepKeyRid(ai, &wkr, 0, lock);
	पूर्ण जबतक (lastindex != wkr.kindex);

	try_स्वतः_wep(ai);

	वापस SUCCESS;
पूर्ण

अटल u16 issuecommand(काष्ठा airo_info *ai, Cmd *pCmd, Resp *pRsp,
			bool may_sleep)
अणु
        // Im really paranoid about letting it run क्रमever!
	पूर्णांक max_tries = 600000;

	अगर (IN4500(ai, EVSTAT) & EV_CMD)
		OUT4500(ai, EVACK, EV_CMD);

	OUT4500(ai, PARAM0, pCmd->parm0);
	OUT4500(ai, PARAM1, pCmd->parm1);
	OUT4500(ai, PARAM2, pCmd->parm2);
	OUT4500(ai, COMMAND, pCmd->cmd);

	जबतक (max_tries-- && (IN4500(ai, EVSTAT) & EV_CMD) == 0) अणु
		अगर ((IN4500(ai, COMMAND)) == pCmd->cmd)
			// PC4500 didn't notice command, try again
			OUT4500(ai, COMMAND, pCmd->cmd);
		अगर (may_sleep && (max_tries & 255) == 0)
			cond_resched();
	पूर्ण

	अगर (max_tries == -1) अणु
		airo_prपूर्णांक_err(ai->dev->name,
			"Max tries exceeded when issuing command");
		अगर (IN4500(ai, COMMAND) & COMMAND_BUSY)
			OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
		वापस ERROR;
	पूर्ण

	// command completed
	pRsp->status = IN4500(ai, STATUS);
	pRsp->rsp0 = IN4500(ai, RESP0);
	pRsp->rsp1 = IN4500(ai, RESP1);
	pRsp->rsp2 = IN4500(ai, RESP2);
	अगर ((pRsp->status & 0xff00)!=0 && pCmd->cmd != CMD_SOFTRESET)
		airo_prपूर्णांक_err(ai->dev->name,
			"cmd:%x status:%x rsp0:%x rsp1:%x rsp2:%x",
			pCmd->cmd, pRsp->status, pRsp->rsp0, pRsp->rsp1,
			pRsp->rsp2);

	// clear stuck command busy अगर necessary
	अगर (IN4500(ai, COMMAND) & COMMAND_BUSY) अणु
		OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
	पूर्ण
	// acknowledge processing the status/response
	OUT4500(ai, EVACK, EV_CMD);

	वापस SUCCESS;
पूर्ण

/* Sets up the bap to start exchange data.  whichbap should
 * be one of the BAP0 or BAP1 defines.  Locks should be held beक्रमe
 * calling! */
अटल पूर्णांक bap_setup(काष्ठा airo_info *ai, u16 rid, u16 offset, पूर्णांक whichbap)
अणु
	पूर्णांक समयout = 50;
	पूर्णांक max_tries = 3;

	OUT4500(ai, SELECT0+whichbap, rid);
	OUT4500(ai, OFFSET0+whichbap, offset);
	जबतक (1) अणु
		पूर्णांक status = IN4500(ai, OFFSET0+whichbap);
		अगर (status & BAP_BUSY) अणु
                        /* This isn't really a समयout, but its kinda
			   बंद */
			अगर (समयout--) अणु
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (status & BAP_ERR) अणु
			/* invalid rid or offset */
			airo_prपूर्णांक_err(ai->dev->name, "BAP error %x %d",
				status, whichbap);
			वापस ERROR;
		पूर्ण अन्यथा अगर (status & BAP_DONE) अणु // success
			वापस SUCCESS;
		पूर्ण
		अगर (!(max_tries--)) अणु
			airo_prपूर्णांक_err(ai->dev->name,
				"BAP setup error too many retries\n");
			वापस ERROR;
		पूर्ण
		// -- PC4500 missed it, try again
		OUT4500(ai, SELECT0+whichbap, rid);
		OUT4500(ai, OFFSET0+whichbap, offset);
		समयout = 50;
	पूर्ण
पूर्ण

/* should only be called by aux_bap_पढ़ो.  This aux function and the
   following use concepts not करोcumented in the developers guide.  I
   got them from a patch given to my by Aironet */
अटल u16 aux_setup(काष्ठा airo_info *ai, u16 page,
		     u16 offset, u16 *len)
अणु
	u16 next;

	OUT4500(ai, AUXPAGE, page);
	OUT4500(ai, AUXOFF, 0);
	next = IN4500(ai, AUXDATA);
	*len = IN4500(ai, AUXDATA)&0xff;
	अगर (offset != 4) OUT4500(ai, AUXOFF, offset);
	वापस next;
पूर्ण

/* requires call to bap_setup() first */
अटल पूर्णांक aux_bap_पढ़ो(काष्ठा airo_info *ai, __le16 *pu16Dst,
			पूर्णांक bytelen, पूर्णांक whichbap)
अणु
	u16 len;
	u16 page;
	u16 offset;
	u16 next;
	पूर्णांक words;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ai->aux_lock, flags);
	page = IN4500(ai, SWS0+whichbap);
	offset = IN4500(ai, SWS2+whichbap);
	next = aux_setup(ai, page, offset, &len);
	words = (bytelen+1)>>1;

	क्रम (i = 0; i<words;) अणु
		पूर्णांक count;
		count = (len>>1) < (words-i) ? (len>>1) : (words-i);
		अगर (!करो8bitIO)
			insw(ai->dev->base_addr+DATA0+whichbap,
			      pu16Dst+i, count);
		अन्यथा
			insb(ai->dev->base_addr+DATA0+whichbap,
			      pu16Dst+i, count << 1);
		i += count;
		अगर (i<words) अणु
			next = aux_setup(ai, next, 4, &len);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ai->aux_lock, flags);
	वापस SUCCESS;
पूर्ण


/* requires call to bap_setup() first */
अटल पूर्णांक fast_bap_पढ़ो(काष्ठा airo_info *ai, __le16 *pu16Dst,
			 पूर्णांक bytelen, पूर्णांक whichbap)
अणु
	bytelen = (bytelen + 1) & (~1); // round up to even value
	अगर (!करो8bitIO)
		insw(ai->dev->base_addr+DATA0+whichbap, pu16Dst, bytelen>>1);
	अन्यथा
		insb(ai->dev->base_addr+DATA0+whichbap, pu16Dst, bytelen);
	वापस SUCCESS;
पूर्ण

/* requires call to bap_setup() first */
अटल पूर्णांक bap_ग_लिखो(काष्ठा airo_info *ai, स्थिर __le16 *pu16Src,
		     पूर्णांक bytelen, पूर्णांक whichbap)
अणु
	bytelen = (bytelen + 1) & (~1); // round up to even value
	अगर (!करो8bitIO)
		outsw(ai->dev->base_addr+DATA0+whichbap,
		       pu16Src, bytelen>>1);
	अन्यथा
		outsb(ai->dev->base_addr+DATA0+whichbap, pu16Src, bytelen);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक PC4500_accessrid(काष्ठा airo_info *ai, u16 rid, u16 accmd)
अणु
	Cmd cmd; /* क्रम issuing commands */
	Resp rsp; /* response from commands */
	u16 status;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = accmd;
	cmd.parm0 = rid;
	status = issuecommand(ai, &cmd, &rsp, true);
	अगर (status != 0) वापस status;
	अगर ((rsp.status & 0x7F00) != 0) अणु
		वापस (accmd << 8) + (rsp.rsp0 & 0xFF);
	पूर्ण
	वापस 0;
पूर्ण

/*  Note, that we are using BAP1 which is also used by transmit, so
 *  we must get a lock. */
अटल पूर्णांक PC4500_पढ़ोrid(काष्ठा airo_info *ai, u16 rid, व्योम *pBuf, पूर्णांक len, पूर्णांक lock)
अणु
	u16 status;
        पूर्णांक rc = SUCCESS;

	अगर (lock) अणु
		अगर (करोwn_पूर्णांकerruptible(&ai->sem))
			वापस ERROR;
	पूर्ण
	अगर (test_bit(FLAG_MPI,&ai->flags)) अणु
		Cmd cmd;
		Resp rsp;

		स_रखो(&cmd, 0, माप(cmd));
		स_रखो(&rsp, 0, माप(rsp));
		ai->config_desc.rid_desc.valid = 1;
		ai->config_desc.rid_desc.len = RIDSIZE;
		ai->config_desc.rid_desc.rid = 0;
		ai->config_desc.rid_desc.host_addr = ai->ridbus;

		cmd.cmd = CMD_ACCESS;
		cmd.parm0 = rid;

		स_नकल_toio(ai->config_desc.card_ram_off,
			&ai->config_desc.rid_desc, माप(Rid));

		rc = issuecommand(ai, &cmd, &rsp, true);

		अगर (rsp.status & 0x7f00)
			rc = rsp.rsp0;
		अगर (!rc)
			स_नकल(pBuf, ai->config_desc.भव_host_addr, len);
		जाओ करोne;
	पूर्ण अन्यथा अणु
		अगर ((status = PC4500_accessrid(ai, rid, CMD_ACCESS))!=SUCCESS) अणु
	                rc = status;
	                जाओ करोne;
	        पूर्ण
		अगर (bap_setup(ai, rid, 0, BAP1) != SUCCESS) अणु
			rc = ERROR;
	                जाओ करोne;
	        पूर्ण
		// पढ़ो the rid length field
		bap_पढ़ो(ai, pBuf, 2, BAP1);
		// length क्रम reमुख्यing part of rid
		len = min(len, (पूर्णांक)le16_to_cpu(*(__le16*)pBuf)) - 2;

		अगर (len <= 2) अणु
			airo_prपूर्णांक_err(ai->dev->name,
				"Rid %x has a length of %d which is too short",
				(पूर्णांक)rid, (पूर्णांक)len);
			rc = ERROR;
	                जाओ करोne;
		पूर्ण
		// पढ़ो reमुख्यder of the rid
		rc = bap_पढ़ो(ai, ((__le16*)pBuf)+1, len, BAP1);
	पूर्ण
करोne:
	अगर (lock)
		up(&ai->sem);
	वापस rc;
पूर्ण

/*  Note, that we are using BAP1 which is also used by transmit, so
 *  make sure this isn't called when a transmit is happening */
अटल पूर्णांक PC4500_ग_लिखोrid(काष्ठा airo_info *ai, u16 rid,
			   स्थिर व्योम *pBuf, पूर्णांक len, पूर्णांक lock)
अणु
	u16 status;
	पूर्णांक rc = SUCCESS;

	*(__le16*)pBuf = cpu_to_le16((u16)len);

	अगर (lock) अणु
		अगर (करोwn_पूर्णांकerruptible(&ai->sem))
			वापस ERROR;
	पूर्ण
	अगर (test_bit(FLAG_MPI,&ai->flags)) अणु
		Cmd cmd;
		Resp rsp;

		अगर (test_bit(FLAG_ENABLED, &ai->flags) && (RID_WEP_TEMP != rid))
			airo_prपूर्णांक_err(ai->dev->name,
				"%s: MAC should be disabled (rid=%04x)",
				__func__, rid);
		स_रखो(&cmd, 0, माप(cmd));
		स_रखो(&rsp, 0, माप(rsp));

		ai->config_desc.rid_desc.valid = 1;
		ai->config_desc.rid_desc.len = *((u16 *)pBuf);
		ai->config_desc.rid_desc.rid = 0;

		cmd.cmd = CMD_WRITERID;
		cmd.parm0 = rid;

		स_नकल_toio(ai->config_desc.card_ram_off,
			&ai->config_desc.rid_desc, माप(Rid));

		अगर (len < 4 || len > 2047) अणु
			airo_prपूर्णांक_err(ai->dev->name, "%s: len=%d", __func__, len);
			rc = -1;
		पूर्ण अन्यथा अणु
			स_नकल(ai->config_desc.भव_host_addr,
				pBuf, len);

			rc = issuecommand(ai, &cmd, &rsp, true);
			अगर ((rc & 0xff00) != 0) अणु
				airo_prपूर्णांक_err(ai->dev->name, "%s: Write rid Error %d",
						__func__, rc);
				airo_prपूर्णांक_err(ai->dev->name, "%s: Cmd=%04x",
						__func__, cmd.cmd);
			पूर्ण

			अगर ((rsp.status & 0x7f00))
				rc = rsp.rsp0;
		पूर्ण
	पूर्ण अन्यथा अणु
		// --- first access so that we can ग_लिखो the rid data
		अगर ((status = PC4500_accessrid(ai, rid, CMD_ACCESS)) != 0) अणु
	                rc = status;
	                जाओ करोne;
	        पूर्ण
		// --- now ग_लिखो the rid data
		अगर (bap_setup(ai, rid, 0, BAP1) != SUCCESS) अणु
	                rc = ERROR;
	                जाओ करोne;
	        पूर्ण
		bap_ग_लिखो(ai, pBuf, len, BAP1);
		// ---now commit the rid data
		rc = PC4500_accessrid(ai, rid, 0x100|CMD_ACCESS);
	पूर्ण
करोne:
	अगर (lock)
		up(&ai->sem);
        वापस rc;
पूर्ण

/* Allocates a FID to be used क्रम transmitting packets.  We only use
   one क्रम now. */
अटल u16 transmit_allocate(काष्ठा airo_info *ai, पूर्णांक lenPayload, पूर्णांक raw)
अणु
	अचिन्हित पूर्णांक loop = 3000;
	Cmd cmd;
	Resp rsp;
	u16 txFid;
	__le16 txControl;

	cmd.cmd = CMD_ALLOCATETX;
	cmd.parm0 = lenPayload;
	अगर (करोwn_पूर्णांकerruptible(&ai->sem))
		वापस ERROR;
	अगर (issuecommand(ai, &cmd, &rsp, true) != SUCCESS) अणु
		txFid = ERROR;
		जाओ करोne;
	पूर्ण
	अगर ((rsp.status & 0xFF00) != 0) अणु
		txFid = ERROR;
		जाओ करोne;
	पूर्ण
	/* रुको क्रम the allocate event/indication
	 * It makes me kind of nervous that this can just sit here and spin,
	 * but in practice it only loops like four बार. */
	जबतक (((IN4500(ai, EVSTAT) & EV_ALLOC) == 0) && --loop);
	अगर (!loop) अणु
		txFid = ERROR;
		जाओ करोne;
	पूर्ण

	// get the allocated fid and acknowledge
	txFid = IN4500(ai, TXALLOCFID);
	OUT4500(ai, EVACK, EV_ALLOC);

	/*  The CARD is pretty cool since it converts the ethernet packet
	 *  पूर्णांकo 802.11.  Also note that we करोn't release the FID since we
	 *  will be using the same one over and over again. */
	/*  We only have to setup the control once since we are not
	 *  releasing the fid. */
	अगर (raw)
		txControl = cpu_to_le16(TXCTL_TXOK | TXCTL_TXEX | TXCTL_802_11
			| TXCTL_ETHERNET | TXCTL_NORELEASE);
	अन्यथा
		txControl = cpu_to_le16(TXCTL_TXOK | TXCTL_TXEX | TXCTL_802_3
			| TXCTL_ETHERNET | TXCTL_NORELEASE);
	अगर (bap_setup(ai, txFid, 0x0008, BAP1) != SUCCESS)
		txFid = ERROR;
	अन्यथा
		bap_ग_लिखो(ai, &txControl, माप(txControl), BAP1);

करोne:
	up(&ai->sem);

	वापस txFid;
पूर्ण

/* In general BAP1 is dedicated to transmiting packets.  However,
   since we need a BAP when accessing RIDs, we also use BAP1 क्रम that.
   Make sure the BAP1 spinlock is held when this is called. */
अटल पूर्णांक transmit_802_3_packet(काष्ठा airo_info *ai, पूर्णांक len, अक्षर *pPacket,
				 bool may_sleep)
अणु
	__le16 payloadLen;
	Cmd cmd;
	Resp rsp;
	पूर्णांक miclen = 0;
	u16 txFid = len;
	MICBuffer pMic;

	len >>= 16;

	अगर (len <= ETH_ALEN * 2) अणु
		airo_prपूर्णांक_warn(ai->dev->name, "Short packet %d", len);
		वापस ERROR;
	पूर्ण
	len -= ETH_ALEN * 2;

	अगर (test_bit(FLAG_MIC_CAPABLE, &ai->flags) && ai->micstats.enabled &&
	    (ntohs(((__be16 *)pPacket)[6]) != 0x888E)) अणु
		अगर (encapsulate(ai, (etherHead *)pPacket,&pMic, len) != SUCCESS)
			वापस ERROR;
		miclen = माप(pMic);
	पूर्ण
	// packet is destination[6], source[6], payload[len-12]
	// ग_लिखो the payload length and dst/src/payload
	अगर (bap_setup(ai, txFid, 0x0036, BAP1) != SUCCESS) वापस ERROR;
	/* The hardware addresses aren't counted as part of the payload, so
	 * we have to subtract the 12 bytes क्रम the addresses off */
	payloadLen = cpu_to_le16(len + miclen);
	bap_ग_लिखो(ai, &payloadLen, माप(payloadLen), BAP1);
	bap_ग_लिखो(ai, (__le16*)pPacket, माप(etherHead), BAP1);
	अगर (miclen)
		bap_ग_लिखो(ai, (__le16*)&pMic, miclen, BAP1);
	bap_ग_लिखो(ai, (__le16*)(pPacket + माप(etherHead)), len, BAP1);
	// issue the transmit command
	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = CMD_TRANSMIT;
	cmd.parm0 = txFid;
	अगर (issuecommand(ai, &cmd, &rsp, may_sleep) != SUCCESS)
		वापस ERROR;
	अगर ((rsp.status & 0xFF00) != 0) वापस ERROR;
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक transmit_802_11_packet(काष्ठा airo_info *ai, पूर्णांक len, अक्षर *pPacket,
				  bool may_sleep)
अणु
	__le16 fc, payloadLen;
	Cmd cmd;
	Resp rsp;
	पूर्णांक hdrlen;
	अटल u8 tail[(30-10) + 2 + 6] = अणु[30-10] = 6पूर्ण;
	/* padding of header to full size + le16 gaplen (6) + gaplen bytes */
	u16 txFid = len;
	len >>= 16;

	fc = *(__le16*)pPacket;
	hdrlen = header_len(fc);

	अगर (len < hdrlen) अणु
		airo_prपूर्णांक_warn(ai->dev->name, "Short packet %d", len);
		वापस ERROR;
	पूर्ण

	/* packet is 802.11 header +  payload
	 * ग_लिखो the payload length and dst/src/payload */
	अगर (bap_setup(ai, txFid, 6, BAP1) != SUCCESS) वापस ERROR;
	/* The 802.11 header aren't counted as part of the payload, so
	 * we have to subtract the header bytes off */
	payloadLen = cpu_to_le16(len-hdrlen);
	bap_ग_लिखो(ai, &payloadLen, माप(payloadLen), BAP1);
	अगर (bap_setup(ai, txFid, 0x0014, BAP1) != SUCCESS) वापस ERROR;
	bap_ग_लिखो(ai, (__le16 *)pPacket, hdrlen, BAP1);
	bap_ग_लिखो(ai, (__le16 *)(tail + (hdrlen - 10)), 38 - hdrlen, BAP1);

	bap_ग_लिखो(ai, (__le16 *)(pPacket + hdrlen), len - hdrlen, BAP1);
	// issue the transmit command
	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = CMD_TRANSMIT;
	cmd.parm0 = txFid;
	अगर (issuecommand(ai, &cmd, &rsp, may_sleep) != SUCCESS)
		वापस ERROR;
	अगर ((rsp.status & 0xFF00) != 0) वापस ERROR;
	वापस SUCCESS;
पूर्ण

/*
 *  This is the proc_fs routines.  It is a bit messier than I would
 *  like!  Feel मुक्त to clean it up!
 */

अटल sमाप_प्रकार proc_पढ़ो(काष्ठा file *file,
			  अक्षर __user *buffer,
			  माप_प्रकार len,
			  loff_t *offset);

अटल sमाप_प्रकार proc_ग_लिखो(काष्ठा file *file,
			   स्थिर अक्षर __user *buffer,
			   माप_प्रकार len,
			   loff_t *offset);
अटल पूर्णांक proc_बंद(काष्ठा inode *inode, काष्ठा file *file);

अटल पूर्णांक proc_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_statsdelta_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_status_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_SSID_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_APList_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_BSSList_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_config_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक proc_wepkey_खोलो(काष्ठा inode *inode, काष्ठा file *file);

अटल स्थिर काष्ठा proc_ops proc_statsdelta_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_खोलो	= proc_statsdelta_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_stats_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_खोलो	= proc_stats_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_status_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_खोलो	= proc_status_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_SSID_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_ग_लिखो	= proc_ग_लिखो,
	.proc_खोलो	= proc_SSID_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_BSSList_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_ग_लिखो	= proc_ग_लिखो,
	.proc_खोलो	= proc_BSSList_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_APList_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_ग_लिखो	= proc_ग_लिखो,
	.proc_खोलो	= proc_APList_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_config_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_ग_लिखो	= proc_ग_लिखो,
	.proc_खोलो	= proc_config_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_wepkey_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो,
	.proc_ग_लिखो	= proc_ग_लिखो,
	.proc_खोलो	= proc_wepkey_खोलो,
	.proc_release	= proc_बंद,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल काष्ठा proc_dir_entry *airo_entry;

काष्ठा proc_data अणु
	पूर्णांक release_buffer;
	पूर्णांक पढ़ोlen;
	अक्षर *rbuffer;
	पूर्णांक ग_लिखोlen;
	पूर्णांक maxग_लिखोlen;
	अक्षर *wbuffer;
	व्योम (*on_बंद) (काष्ठा inode *, काष्ठा file *);
पूर्ण;

अटल पूर्णांक setup_proc_entry(काष्ठा net_device *dev,
			     काष्ठा airo_info *apriv)
अणु
	काष्ठा proc_dir_entry *entry;

	/* First setup the device directory */
	म_नकल(apriv->proc_name, dev->name);
	apriv->proc_entry = proc_सूची_गढ़ो_mode(apriv->proc_name, airo_perm,
					    airo_entry);
	अगर (!apriv->proc_entry)
		वापस -ENOMEM;
	proc_set_user(apriv->proc_entry, proc_kuid, proc_kgid);

	/* Setup the StatsDelta */
	entry = proc_create_data("StatsDelta", 0444 & proc_perm,
				 apriv->proc_entry, &proc_statsdelta_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the Stats */
	entry = proc_create_data("Stats", 0444 & proc_perm,
				 apriv->proc_entry, &proc_stats_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the Status */
	entry = proc_create_data("Status", 0444 & proc_perm,
				 apriv->proc_entry, &proc_status_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the Config */
	entry = proc_create_data("Config", proc_perm,
				 apriv->proc_entry, &proc_config_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the SSID */
	entry = proc_create_data("SSID", proc_perm,
				 apriv->proc_entry, &proc_SSID_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the APList */
	entry = proc_create_data("APList", proc_perm,
				 apriv->proc_entry, &proc_APList_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the BSSList */
	entry = proc_create_data("BSSList", proc_perm,
				 apriv->proc_entry, &proc_BSSList_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);

	/* Setup the WepKey */
	entry = proc_create_data("WepKey", proc_perm,
				 apriv->proc_entry, &proc_wepkey_ops, dev);
	अगर (!entry)
		जाओ fail;
	proc_set_user(entry, proc_kuid, proc_kgid);
	वापस 0;

fail:
	हटाओ_proc_subtree(apriv->proc_name, airo_entry);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक takeकरोwn_proc_entry(काष्ठा net_device *dev,
				काष्ठा airo_info *apriv)
अणु
	हटाओ_proc_subtree(apriv->proc_name, airo_entry);
	वापस 0;
पूर्ण

/*
 *  What we want from the proc_fs is to be able to efficiently पढ़ो
 *  and ग_लिखो the configuration.  To करो this, we want to पढ़ो the
 *  configuration when the file is खोलोed and ग_लिखो it when the file is
 *  बंदd.  So basically we allocate a पढ़ो buffer at खोलो and fill it
 *  with data, and allocate a ग_लिखो buffer and पढ़ो it at बंद.
 */

/*
 *  The पढ़ो routine is generic, it relies on the pपुनः_स्मृतिated rbuffer
 *  to supply the data.
 */
अटल sमाप_प्रकार proc_पढ़ो(काष्ठा file *file,
			  अक्षर __user *buffer,
			  माप_प्रकार len,
			  loff_t *offset)
अणु
	काष्ठा proc_data *priv = file->निजी_data;

	अगर (!priv->rbuffer)
		वापस -EINVAL;

	वापस simple_पढ़ो_from_buffer(buffer, len, offset, priv->rbuffer,
					priv->पढ़ोlen);
पूर्ण

/*
 *  The ग_लिखो routine is generic, it fills in a pपुनः_स्मृतिated rbuffer
 *  to supply the data.
 */
अटल sमाप_प्रकार proc_ग_लिखो(काष्ठा file *file,
			   स्थिर अक्षर __user *buffer,
			   माप_प्रकार len,
			   loff_t *offset)
अणु
	sमाप_प्रकार ret;
	काष्ठा proc_data *priv = file->निजी_data;

	अगर (!priv->wbuffer)
		वापस -EINVAL;

	ret = simple_ग_लिखो_to_buffer(priv->wbuffer, priv->maxग_लिखोlen, offset,
					buffer, len);
	अगर (ret > 0)
		priv->ग_लिखोlen = max_t(पूर्णांक, priv->ग_लिखोlen, *offset);

	वापस ret;
पूर्ण

अटल पूर्णांक proc_status_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *apriv = dev->ml_priv;
	CapabilityRid cap_rid;
	StatusRid status_rid;
	u16 mode;
	पूर्णांक i;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(2048, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण

	पढ़ोStatusRid(apriv, &status_rid, 1);
	पढ़ोCapabilityRid(apriv, &cap_rid, 1);

	mode = le16_to_cpu(status_rid.mode);

        i = प्र_लिखो(data->rbuffer, "Status: %s%s%s%s%s%s%s%s%s\n",
                    mode & 1 ? "CFG ": "",
                    mode & 2 ? "ACT ": "",
                    mode & 0x10 ? "SYN ": "",
                    mode & 0x20 ? "LNK ": "",
                    mode & 0x40 ? "LEAP ": "",
                    mode & 0x80 ? "PRIV ": "",
                    mode & 0x100 ? "KEY ": "",
                    mode & 0x200 ? "WEP ": "",
                    mode & 0x8000 ? "ERR ": "");
	प्र_लिखो(data->rbuffer+i, "Mode: %x\n"
		 "Signal Strength: %d\n"
		 "Signal Quality: %d\n"
		 "SSID: %-.*s\n"
		 "AP: %-.16s\n"
		 "Freq: %d\n"
		 "BitRate: %dmbs\n"
		 "Driver Version: %s\n"
		 "Device: %s\nManufacturer: %s\nFirmware Version: %s\n"
		 "Radio type: %x\nCountry: %x\nHardware Version: %x\n"
		 "Software Version: %x\nSoftware Subversion: %x\n"
		 "Boot block version: %x\n",
		 le16_to_cpu(status_rid.mode),
		 le16_to_cpu(status_rid.normalizedSignalStrength),
		 le16_to_cpu(status_rid.संकेतQuality),
		 le16_to_cpu(status_rid.SSIDlen),
		 status_rid.SSID,
		 status_rid.apName,
		 le16_to_cpu(status_rid.channel),
		 le16_to_cpu(status_rid.currentXmitRate) / 2,
		 version,
		 cap_rid.prodName,
		 cap_rid.manName,
		 cap_rid.prodVer,
		 le16_to_cpu(cap_rid.radioType),
		 le16_to_cpu(cap_rid.country),
		 le16_to_cpu(cap_rid.hardVer),
		 le16_to_cpu(cap_rid.softVer),
		 le16_to_cpu(cap_rid.softSubVer),
		 le16_to_cpu(cap_rid.bootBlockVer));
	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_stats_rid_खोलो(काष्ठा inode*, काष्ठा file*, u16);
अटल पूर्णांक proc_statsdelta_खोलो(काष्ठा inode *inode,
				 काष्ठा file *file)
अणु
	अगर (file->f_mode&FMODE_WRITE) अणु
		वापस proc_stats_rid_खोलो(inode, file, RID_STATSDELTACLEAR);
	पूर्ण
	वापस proc_stats_rid_खोलो(inode, file, RID_STATSDELTA);
पूर्ण

अटल पूर्णांक proc_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस proc_stats_rid_खोलो(inode, file, RID_STATS);
पूर्ण

अटल पूर्णांक proc_stats_rid_खोलो(काष्ठा inode *inode,
				काष्ठा file *file,
				u16 rid)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *apriv = dev->ml_priv;
	StatsRid stats;
	पूर्णांक i, j;
	__le32 *vals = stats.vals;
	पूर्णांक len;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(4096, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण

	पढ़ोStatsRid(apriv, &stats, rid, 1);
	len = le16_to_cpu(stats.len);

        j = 0;
	क्रम (i = 0; statsLabels[i]!=(अक्षर *)-1 && i*4<len; i++) अणु
		अगर (!statsLabels[i]) जारी;
		अगर (j+म_माप(statsLabels[i])+16>4096) अणु
			airo_prपूर्णांक_warn(apriv->dev->name,
			       "Potentially disastrous buffer overflow averted!");
			अवरोध;
		पूर्ण
		j+=प्र_लिखो(data->rbuffer+j, "%s: %u\n", statsLabels[i],
				le32_to_cpu(vals[i]));
	पूर्ण
	अगर (i*4 >= len) अणु
		airo_prपूर्णांक_warn(apriv->dev->name, "Got a short rid");
	पूर्ण
	data->पढ़ोlen = j;
	वापस 0;
पूर्ण

अटल पूर्णांक get_dec_u16(अक्षर *buffer, पूर्णांक *start, पूर्णांक limit)
अणु
	u16 value;
	पूर्णांक valid = 0;
	क्रम (value = 0; *start < limit && buffer[*start] >= '0' &&
			buffer[*start] <= '9'; (*start)++) अणु
		valid = 1;
		value *= 10;
		value += buffer[*start] - '0';
	पूर्ण
	अगर (!valid) वापस -1;
	वापस value;
पूर्ण

अटल पूर्णांक airo_config_commit(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info, व्योम *zwrq,
			      अक्षर *extra);

अटल अंतरभूत पूर्णांक snअगरfing_mode(काष्ठा airo_info *ai)
अणु
	वापस (le16_to_cpu(ai->config.rmode) & le16_to_cpu(RXMODE_MASK)) >=
		le16_to_cpu(RXMODE_RFMON);
पूर्ण

अटल व्योम proc_config_on_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data = file->निजी_data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	अक्षर *line;

	अगर (!data->ग_लिखोlen) वापस;

	पढ़ोConfigRid(ai, 1);
	set_bit (FLAG_COMMIT, &ai->flags);

	line = data->wbuffer;
	जबतक (line[0]) अणु
/*** Mode processing */
		अगर (!म_भेदन(line, "Mode: ", 6)) अणु
			line += 6;
			अगर (snअगरfing_mode(ai))
				set_bit (FLAG_RESET, &ai->flags);
			ai->config.rmode &= ~RXMODE_FULL_MASK;
			clear_bit (FLAG_802_11, &ai->flags);
			ai->config.opmode &= ~MODE_CFG_MASK;
			ai->config.scanMode = SCANMODE_ACTIVE;
			अगर (line[0] == 'a') अणु
				ai->config.opmode |= MODE_STA_IBSS;
			पूर्ण अन्यथा अणु
				ai->config.opmode |= MODE_STA_ESS;
				अगर (line[0] == 'r') अणु
					ai->config.rmode |= RXMODE_RFMON | RXMODE_DISABLE_802_3_HEADER;
					ai->config.scanMode = SCANMODE_PASSIVE;
					set_bit (FLAG_802_11, &ai->flags);
				पूर्ण अन्यथा अगर (line[0] == 'y') अणु
					ai->config.rmode |= RXMODE_RFMON_ANYBSS | RXMODE_DISABLE_802_3_HEADER;
					ai->config.scanMode = SCANMODE_PASSIVE;
					set_bit (FLAG_802_11, &ai->flags);
				पूर्ण अन्यथा अगर (line[0] == 'l')
					ai->config.rmode |= RXMODE_LANMON;
			पूर्ण
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण

/*** Radio status */
		अन्यथा अगर (!म_भेदन(line,"Radio: ", 7)) अणु
			line += 7;
			अगर (!म_भेदन(line,"off", 3)) अणु
				set_bit (FLAG_RADIO_OFF, &ai->flags);
			पूर्ण अन्यथा अणु
				clear_bit (FLAG_RADIO_OFF, &ai->flags);
			पूर्ण
		पूर्ण
/*** NodeName processing */
		अन्यथा अगर (!म_भेदन(line, "NodeName: ", 10)) अणु
			पूर्णांक j;

			line += 10;
			स_रखो(ai->config.nodeName, 0, 16);
/* Do the name, assume a space between the mode and node name */
			क्रम (j = 0; j < 16 && line[j] != '\n'; j++) अणु
				ai->config.nodeName[j] = line[j];
			पूर्ण
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण

/*** PowerMode processing */
		अन्यथा अगर (!म_भेदन(line, "PowerMode: ", 11)) अणु
			line += 11;
			अगर (!म_भेदन(line, "PSPCAM", 6)) अणु
				ai->config.घातerSaveMode = POWERSAVE_PSPCAM;
				set_bit (FLAG_COMMIT, &ai->flags);
			पूर्ण अन्यथा अगर (!म_भेदन(line, "PSP", 3)) अणु
				ai->config.घातerSaveMode = POWERSAVE_PSP;
				set_bit (FLAG_COMMIT, &ai->flags);
			पूर्ण अन्यथा अणु
				ai->config.घातerSaveMode = POWERSAVE_CAM;
				set_bit (FLAG_COMMIT, &ai->flags);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(line, "DataRates: ", 11)) अणु
			पूर्णांक v, i = 0, k = 0; /* i is index पूर्णांकo line,
						k is index to rates */

			line += 11;
			जबतक ((v = get_dec_u16(line, &i, 3))!=-1) अणु
				ai->config.rates[k++] = (u8)v;
				line += i + 1;
				i = 0;
			पूर्ण
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "Channel: ", 9)) अणु
			पूर्णांक v, i = 0;
			line += 9;
			v = get_dec_u16(line, &i, i+3);
			अगर (v != -1) अणु
				ai->config.channelSet = cpu_to_le16(v);
				set_bit (FLAG_COMMIT, &ai->flags);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(line, "XmitPower: ", 11)) अणु
			पूर्णांक v, i = 0;
			line += 11;
			v = get_dec_u16(line, &i, i+3);
			अगर (v != -1) अणु
				ai->config.txPower = cpu_to_le16(v);
				set_bit (FLAG_COMMIT, &ai->flags);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(line, "WEP: ", 5)) अणु
			line += 5;
			चयन(line[0]) अणु
			हाल 's':
				set_auth_type(ai, AUTH_SHAREDKEY);
				अवरोध;
			हाल 'e':
				set_auth_type(ai, AUTH_ENCRYPT);
				अवरोध;
			शेष:
				set_auth_type(ai, AUTH_OPEN);
				अवरोध;
			पूर्ण
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "LongRetryLimit: ", 16)) अणु
			पूर्णांक v, i = 0;

			line += 16;
			v = get_dec_u16(line, &i, 3);
			v = (v<0) ? 0 : ((v>255) ? 255 : v);
			ai->config.दीर्घRetryLimit = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "ShortRetryLimit: ", 17)) अणु
			पूर्णांक v, i = 0;

			line += 17;
			v = get_dec_u16(line, &i, 3);
			v = (v<0) ? 0 : ((v>255) ? 255 : v);
			ai->config.लघुRetryLimit = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "RTSThreshold: ", 14)) अणु
			पूर्णांक v, i = 0;

			line += 14;
			v = get_dec_u16(line, &i, 4);
			v = (v<0) ? 0 : ((v>AIRO_DEF_MTU) ? AIRO_DEF_MTU : v);
			ai->config.rtsThres = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "TXMSDULifetime: ", 16)) अणु
			पूर्णांक v, i = 0;

			line += 16;
			v = get_dec_u16(line, &i, 5);
			v = (v<0) ? 0 : v;
			ai->config.txLअगरeसमय = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "RXMSDULifetime: ", 16)) अणु
			पूर्णांक v, i = 0;

			line += 16;
			v = get_dec_u16(line, &i, 5);
			v = (v<0) ? 0 : v;
			ai->config.rxLअगरeसमय = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "TXDiversity: ", 13)) अणु
			ai->config.txDiversity =
				(line[13]=='l') ? 1 :
				((line[13]=='r')? 2: 3);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "RXDiversity: ", 13)) अणु
			ai->config.rxDiversity =
				(line[13]=='l') ? 1 :
				((line[13]=='r')? 2: 3);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "FragThreshold: ", 15)) अणु
			पूर्णांक v, i = 0;

			line += 15;
			v = get_dec_u16(line, &i, 4);
			v = (v<256) ? 256 : ((v>AIRO_DEF_MTU) ? AIRO_DEF_MTU : v);
			v = v & 0xfffe; /* Make sure its even */
			ai->config.fragThresh = cpu_to_le16(v);
			set_bit (FLAG_COMMIT, &ai->flags);
		पूर्ण अन्यथा अगर (!म_भेदन(line, "Modulation: ", 12)) अणु
			line += 12;
			चयन(*line) अणु
			हाल 'd':  ai->config.modulation = MOD_DEFAULT; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			हाल 'c':  ai->config.modulation = MOD_CCK; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			हाल 'm':  ai->config.modulation = MOD_MOK; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			शेष: airo_prपूर्णांक_warn(ai->dev->name, "Unknown modulation");
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(line, "Preamble: ", 10)) अणु
			line += 10;
			चयन(*line) अणु
			हाल 'a': ai->config.preamble = PREAMBLE_AUTO; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			हाल 'l': ai->config.preamble = PREAMBLE_LONG; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			हाल 's': ai->config.preamble = PREAMBLE_SHORT; set_bit(FLAG_COMMIT, &ai->flags); अवरोध;
			शेष: airo_prपूर्णांक_warn(ai->dev->name, "Unknown preamble");
			पूर्ण
		पूर्ण अन्यथा अणु
			airo_prपूर्णांक_warn(ai->dev->name, "Couldn't figure out %s", line);
		पूर्ण
		जबतक (line[0] && line[0] != '\n') line++;
		अगर (line[0]) line++;
	पूर्ण
	airo_config_commit(dev, शून्य, शून्य, शून्य);
पूर्ण

अटल स्थिर अक्षर *get_rmode(__le16 mode)
अणु
        चयन(mode & RXMODE_MASK) अणु
        हाल RXMODE_RFMON:  वापस "rfmon";
        हाल RXMODE_RFMON_ANYBSS:  वापस "yna (any) bss rfmon";
        हाल RXMODE_LANMON:  वापस "lanmon";
        पूर्ण
        वापस "ESS";
पूर्ण

अटल पूर्णांक proc_config_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक i;
	__le16 mode;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(2048, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	अगर ((data->wbuffer = kzalloc(2048, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (data->rbuffer);
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->maxग_लिखोlen = 2048;
	data->on_बंद = proc_config_on_बंद;

	पढ़ोConfigRid(ai, 1);

	mode = ai->config.opmode & MODE_CFG_MASK;
	i = प्र_लिखो(data->rbuffer,
		     "Mode: %s\n"
		     "Radio: %s\n"
		     "NodeName: %-16s\n"
		     "PowerMode: %s\n"
		     "DataRates: %d %d %d %d %d %d %d %d\n"
		     "Channel: %d\n"
		     "XmitPower: %d\n",
		     mode == MODE_STA_IBSS ? "adhoc" :
		     mode == MODE_STA_ESS ? get_rmode(ai->config.rmode):
		     mode == MODE_AP ? "AP" :
		     mode == MODE_AP_RPTR ? "AP RPTR" : "Error",
		     test_bit(FLAG_RADIO_OFF, &ai->flags) ? "off" : "on",
		     ai->config.nodeName,
		     ai->config.घातerSaveMode == POWERSAVE_CAM ? "CAM" :
		     ai->config.घातerSaveMode == POWERSAVE_PSP ? "PSP" :
		     ai->config.घातerSaveMode == POWERSAVE_PSPCAM ? "PSPCAM" :
		     "Error",
		     (पूर्णांक)ai->config.rates[0],
		     (पूर्णांक)ai->config.rates[1],
		     (पूर्णांक)ai->config.rates[2],
		     (पूर्णांक)ai->config.rates[3],
		     (पूर्णांक)ai->config.rates[4],
		     (पूर्णांक)ai->config.rates[5],
		     (पूर्णांक)ai->config.rates[6],
		     (पूर्णांक)ai->config.rates[7],
		     le16_to_cpu(ai->config.channelSet),
		     le16_to_cpu(ai->config.txPower)
		);
	प्र_लिखो(data->rbuffer + i,
		 "LongRetryLimit: %d\n"
		 "ShortRetryLimit: %d\n"
		 "RTSThreshold: %d\n"
		 "TXMSDULifetime: %d\n"
		 "RXMSDULifetime: %d\n"
		 "TXDiversity: %s\n"
		 "RXDiversity: %s\n"
		 "FragThreshold: %d\n"
		 "WEP: %s\n"
		 "Modulation: %s\n"
		 "Preamble: %s\n",
		 le16_to_cpu(ai->config.दीर्घRetryLimit),
		 le16_to_cpu(ai->config.लघुRetryLimit),
		 le16_to_cpu(ai->config.rtsThres),
		 le16_to_cpu(ai->config.txLअगरeसमय),
		 le16_to_cpu(ai->config.rxLअगरeसमय),
		 ai->config.txDiversity == 1 ? "left" :
		 ai->config.txDiversity == 2 ? "right" : "both",
		 ai->config.rxDiversity == 1 ? "left" :
		 ai->config.rxDiversity == 2 ? "right" : "both",
		 le16_to_cpu(ai->config.fragThresh),
		 ai->config.authType == AUTH_ENCRYPT ? "encrypt" :
		 ai->config.authType == AUTH_SHAREDKEY ? "shared" : "open",
		 ai->config.modulation == MOD_DEFAULT ? "default" :
		 ai->config.modulation == MOD_CCK ? "cck" :
		 ai->config.modulation == MOD_MOK ? "mok" : "error",
		 ai->config.preamble == PREAMBLE_AUTO ? "auto" :
		 ai->config.preamble == PREAMBLE_LONG ? "long" :
		 ai->config.preamble == PREAMBLE_SHORT ? "short" : "error"
		);
	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल व्योम proc_SSID_on_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data = file->निजी_data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	SsidRid SSID_rid;
	पूर्णांक i;
	अक्षर *p = data->wbuffer;
	अक्षर *end = p + data->ग_लिखोlen;

	अगर (!data->ग_लिखोlen)
		वापस;

	*end = '\n'; /* sentinel; we have space क्रम it */

	स_रखो(&SSID_rid, 0, माप(SSID_rid));

	क्रम (i = 0; i < 3 && p < end; i++) अणु
		पूर्णांक j = 0;
		/* copy up to 32 अक्षरacters from this line */
		जबतक (*p != '\n' && j < 32)
			SSID_rid.ssids[i].ssid[j++] = *p++;
		अगर (j == 0)
			अवरोध;
		SSID_rid.ssids[i].len = cpu_to_le16(j);
		/* skip to the beginning of the next line */
		जबतक (*p++ != '\n')
			;
	पूर्ण
	अगर (i)
		SSID_rid.len = cpu_to_le16(माप(SSID_rid));
	disable_MAC(ai, 1);
	ग_लिखोSsidRid(ai, &SSID_rid, 1);
	enable_MAC(ai, 1);
पूर्ण

अटल व्योम proc_APList_on_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data = file->निजी_data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	APListRid *APList_rid = &ai->APList;
	पूर्णांक i;

	अगर (!data->ग_लिखोlen) वापस;

	स_रखो(APList_rid, 0, माप(*APList_rid));
	APList_rid->len = cpu_to_le16(माप(*APList_rid));

	क्रम (i = 0; i < 4 && data->ग_लिखोlen >= (i + 1) * 6 * 3; i++)
		mac_pton(data->wbuffer + i * 6 * 3, APList_rid->ap[i]);

	disable_MAC(ai, 1);
	ग_लिखोAPListRid(ai, APList_rid, 1);
	enable_MAC(ai, 1);
पूर्ण

/* This function wraps PC4500_ग_लिखोrid with a MAC disable */
अटल पूर्णांक करो_ग_लिखोrid(काष्ठा airo_info *ai, u16 rid, स्थिर व्योम *rid_data,
			पूर्णांक len, पूर्णांक dummy)
अणु
	पूर्णांक rc;

	disable_MAC(ai, 1);
	rc = PC4500_ग_लिखोrid(ai, rid, rid_data, len, 1);
	enable_MAC(ai, 1);
	वापस rc;
पूर्ण

/* Returns the WEP key at the specअगरied index, or -1 अगर that key करोes
 * not exist.  The buffer is assumed to be at least 16 bytes in length.
 */
अटल पूर्णांक get_wep_key(काष्ठा airo_info *ai, u16 index, अक्षर *buf, u16 buflen)
अणु
	WepKeyRid wkr;
	पूर्णांक rc;
	__le16 lastindex;

	rc = पढ़ोWepKeyRid(ai, &wkr, 1, 1);
	अगर (rc != SUCCESS)
		वापस -1;
	करो अणु
		lastindex = wkr.kindex;
		अगर (le16_to_cpu(wkr.kindex) == index) अणु
			पूर्णांक klen = min_t(पूर्णांक, buflen, le16_to_cpu(wkr.klen));
			स_नकल(buf, wkr.key, klen);
			वापस klen;
		पूर्ण
		rc = पढ़ोWepKeyRid(ai, &wkr, 0, 1);
		अगर (rc != SUCCESS)
			वापस -1;
	पूर्ण जबतक (lastindex != wkr.kindex);
	वापस -1;
पूर्ण

अटल पूर्णांक get_wep_tx_idx(काष्ठा airo_info *ai)
अणु
	WepKeyRid wkr;
	पूर्णांक rc;
	__le16 lastindex;

	rc = पढ़ोWepKeyRid(ai, &wkr, 1, 1);
	अगर (rc != SUCCESS)
		वापस -1;
	करो अणु
		lastindex = wkr.kindex;
		अगर (wkr.kindex == cpu_to_le16(0xffff))
			वापस wkr.mac[0];
		rc = पढ़ोWepKeyRid(ai, &wkr, 0, 1);
		अगर (rc != SUCCESS)
			वापस -1;
	पूर्ण जबतक (lastindex != wkr.kindex);
	वापस -1;
पूर्ण

अटल पूर्णांक set_wep_key(काष्ठा airo_info *ai, u16 index, स्थिर अक्षर *key,
		       u16 keylen, पूर्णांक perm, पूर्णांक lock)
अणु
	अटल स्थिर अचिन्हित अक्षर macaddr[ETH_ALEN] = अणु 0x01, 0, 0, 0, 0, 0 पूर्ण;
	WepKeyRid wkr;
	पूर्णांक rc;

	अगर (WARN_ON(keylen == 0))
		वापस -1;

	स_रखो(&wkr, 0, माप(wkr));
	wkr.len = cpu_to_le16(माप(wkr));
	wkr.kindex = cpu_to_le16(index);
	wkr.klen = cpu_to_le16(keylen);
	स_नकल(wkr.key, key, keylen);
	स_नकल(wkr.mac, macaddr, ETH_ALEN);

	अगर (perm) disable_MAC(ai, lock);
	rc = ग_लिखोWepKeyRid(ai, &wkr, perm, lock);
	अगर (perm) enable_MAC(ai, lock);
	वापस rc;
पूर्ण

अटल पूर्णांक set_wep_tx_idx(काष्ठा airo_info *ai, u16 index, पूर्णांक perm, पूर्णांक lock)
अणु
	WepKeyRid wkr;
	पूर्णांक rc;

	स_रखो(&wkr, 0, माप(wkr));
	wkr.len = cpu_to_le16(माप(wkr));
	wkr.kindex = cpu_to_le16(0xffff);
	wkr.mac[0] = (अक्षर)index;

	अगर (perm) अणु
		ai->defindex = (अक्षर)index;
		disable_MAC(ai, lock);
	पूर्ण

	rc = ग_लिखोWepKeyRid(ai, &wkr, perm, lock);

	अगर (perm)
		enable_MAC(ai, lock);
	वापस rc;
पूर्ण

अटल व्योम proc_wepkey_on_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक i, rc;
	अक्षर key[16];
	u16 index = 0;
	पूर्णांक j = 0;

	स_रखो(key, 0, माप(key));

	data = file->निजी_data;
	अगर (!data->ग_लिखोlen) वापस;

	अगर (data->wbuffer[0] >= '0' && data->wbuffer[0] <= '3' &&
	    (data->wbuffer[1] == ' ' || data->wbuffer[1] == '\n')) अणु
		index = data->wbuffer[0] - '0';
		अगर (data->wbuffer[1] == '\n') अणु
			rc = set_wep_tx_idx(ai, index, 1, 1);
			अगर (rc < 0) अणु
				airo_prपूर्णांक_err(ai->dev->name, "failed to set "
				               "WEP transmit index to %d: %d.",
				               index, rc);
			पूर्ण
			वापस;
		पूर्ण
		j = 2;
	पूर्ण अन्यथा अणु
		airo_prपूर्णांक_err(ai->dev->name, "WepKey passed invalid key index");
		वापस;
	पूर्ण

	क्रम (i = 0; i < 16*3 && data->wbuffer[i+j]; i++) अणु
		चयन(i%3) अणु
		हाल 0:
			key[i/3] = hex_to_bin(data->wbuffer[i+j])<<4;
			अवरोध;
		हाल 1:
			key[i/3] |= hex_to_bin(data->wbuffer[i+j]);
			अवरोध;
		पूर्ण
	पूर्ण

	rc = set_wep_key(ai, index, key, i/3, 1, 1);
	अगर (rc < 0) अणु
		airo_prपूर्णांक_err(ai->dev->name, "failed to set WEP key at index "
		               "%d: %d.", index, rc);
	पूर्ण
पूर्ण

अटल पूर्णांक proc_wepkey_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	अक्षर *ptr;
	WepKeyRid wkr;
	__le16 lastindex;
	पूर्णांक j = 0;
	पूर्णांक rc;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	स_रखो(&wkr, 0, माप(wkr));
	data = file->निजी_data;
	अगर ((data->rbuffer = kzalloc(180, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->ग_लिखोlen = 0;
	data->maxग_लिखोlen = 80;
	अगर ((data->wbuffer = kzalloc(80, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (data->rbuffer);
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->on_बंद = proc_wepkey_on_बंद;

	ptr = data->rbuffer;
	म_नकल(ptr, "No wep keys\n");
	rc = पढ़ोWepKeyRid(ai, &wkr, 1, 1);
	अगर (rc == SUCCESS) करो अणु
		lastindex = wkr.kindex;
		अगर (wkr.kindex == cpu_to_le16(0xffff)) अणु
			j += प्र_लिखो(ptr+j, "Tx key = %d\n",
				     (पूर्णांक)wkr.mac[0]);
		पूर्ण अन्यथा अणु
			j += प्र_लिखो(ptr+j, "Key %d set with length = %d\n",
				     le16_to_cpu(wkr.kindex),
				     le16_to_cpu(wkr.klen));
		पूर्ण
		पढ़ोWepKeyRid(ai, &wkr, 0, 1);
	पूर्ण जबतक ((lastindex != wkr.kindex) && (j < 180-30));

	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_SSID_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक i;
	अक्षर *ptr;
	SsidRid SSID_rid;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(104, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->ग_लिखोlen = 0;
	data->maxग_लिखोlen = 33*3;
	/* allocate maxग_लिखोlen + 1; we'll want a sentinel */
	अगर ((data->wbuffer = kzalloc(33*3 + 1, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (data->rbuffer);
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->on_बंद = proc_SSID_on_बंद;

	पढ़ोSsidRid(ai, &SSID_rid);
	ptr = data->rbuffer;
	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक j;
		माप_प्रकार len = le16_to_cpu(SSID_rid.ssids[i].len);
		अगर (!len)
			अवरोध;
		अगर (len > 32)
			len = 32;
		क्रम (j = 0; j < len && SSID_rid.ssids[i].ssid[j]; j++)
			*ptr++ = SSID_rid.ssids[i].ssid[j];
		*ptr++ = '\n';
	पूर्ण
	*ptr = '\0';
	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_APList_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक i;
	अक्षर *ptr;
	APListRid *APList_rid = &ai->APList;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(104, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->ग_लिखोlen = 0;
	data->maxग_लिखोlen = 4*6*3;
	अगर ((data->wbuffer = kzalloc(data->maxग_लिखोlen, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (data->rbuffer);
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->on_बंद = proc_APList_on_बंद;

	ptr = data->rbuffer;
	क्रम (i = 0; i < 4; i++) अणु
// We end when we find a zero MAC
		अगर (!*(पूर्णांक*)APList_rid->ap[i] &&
		     !*(पूर्णांक*)&APList_rid->ap[i][2]) अवरोध;
		ptr += प्र_लिखो(ptr, "%pM\n", APList_rid->ap[i]);
	पूर्ण
	अगर (i==0) ptr += प्र_लिखो(ptr, "Not using specific APs\n");

	*ptr = '\0';
	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_BSSList_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data;
	काष्ठा net_device *dev = PDE_DATA(inode);
	काष्ठा airo_info *ai = dev->ml_priv;
	अक्षर *ptr;
	BSSListRid BSSList_rid;
	पूर्णांक rc;
	/* If करोLoseSync is not 1, we won't करो a Lose Sync */
	पूर्णांक करोLoseSync = -1;

	अगर ((file->निजी_data = kzalloc(माप(काष्ठा proc_data), GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;
	data = file->निजी_data;
	अगर ((data->rbuffer = kदो_स्मृति(1024, GFP_KERNEL)) == शून्य) अणु
		kमुक्त (file->निजी_data);
		वापस -ENOMEM;
	पूर्ण
	data->ग_लिखोlen = 0;
	data->maxग_लिखोlen = 0;
	data->wbuffer = शून्य;
	data->on_बंद = शून्य;

	अगर (file->f_mode & FMODE_WRITE) अणु
		अगर (!(file->f_mode & FMODE_READ)) अणु
			Cmd cmd;
			Resp rsp;

			अगर (ai->flags & FLAG_RADIO_MASK) अणु
				kमुक्त(data->rbuffer);
				kमुक्त(file->निजी_data);
				वापस -ENETDOWN;
			पूर्ण
			स_रखो(&cmd, 0, माप(cmd));
			cmd.cmd = CMD_LISTBSS;
			अगर (करोwn_पूर्णांकerruptible(&ai->sem)) अणु
				kमुक्त(data->rbuffer);
				kमुक्त(file->निजी_data);
				वापस -ERESTARTSYS;
			पूर्ण
			issuecommand(ai, &cmd, &rsp, true);
			up(&ai->sem);
			data->पढ़ोlen = 0;
			वापस 0;
		पूर्ण
		करोLoseSync = 1;
	पूर्ण
	ptr = data->rbuffer;
	/* There is a race condition here अगर there are concurrent खोलोs.
           Since it is a rare condition, we'll just live with it, otherwise
           we have to add a spin lock... */
	rc = पढ़ोBSSListRid(ai, करोLoseSync, &BSSList_rid);
	जबतक (rc == 0 && BSSList_rid.index != cpu_to_le16(0xffff)) अणु
		ptr += प्र_लिखो(ptr, "%pM %.*s rssi = %d",
			       BSSList_rid.bssid,
				(पूर्णांक)BSSList_rid.ssidLen,
				BSSList_rid.ssid,
				le16_to_cpu(BSSList_rid.dBm));
		ptr += प्र_लिखो(ptr, " channel = %d %s %s %s %s\n",
				le16_to_cpu(BSSList_rid.dsChannel),
				BSSList_rid.cap & CAP_ESS ? "ESS" : "",
				BSSList_rid.cap & CAP_IBSS ? "adhoc" : "",
				BSSList_rid.cap & CAP_PRIVACY ? "wep" : "",
				BSSList_rid.cap & CAP_SHORTHDR ? "shorthdr" : "");
		rc = पढ़ोBSSListRid(ai, 0, &BSSList_rid);
	पूर्ण
	*ptr = '\0';
	data->पढ़ोlen = म_माप(data->rbuffer);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_data *data = file->निजी_data;

	अगर (data->on_बंद != शून्य)
		data->on_बंद(inode, file);
	kमुक्त(data->rbuffer);
	kमुक्त(data->wbuffer);
	kमुक्त(data);
	वापस 0;
पूर्ण

/* Since the card करोesn't स्वतःmatically चयन to the right WEP mode,
   we will make it करो it.  If the card isn't associated, every secs we
   will चयन WEP modes to see अगर that will help.  If the card is
   associated we will check every minute to see अगर anything has
   changed. */
अटल व्योम समयr_func(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *apriv = dev->ml_priv;

/* We करोn't have a link so try changing the authtype */
	पढ़ोConfigRid(apriv, 0);
	disable_MAC(apriv, 0);
	चयन(apriv->config.authType) अणु
		हाल AUTH_ENCRYPT:
/* So drop to OPEN */
			apriv->config.authType = AUTH_OPEN;
			अवरोध;
		हाल AUTH_SHAREDKEY:
			अगर (apriv->keyindex < स्वतः_wep) अणु
				set_wep_tx_idx(apriv, apriv->keyindex, 0, 0);
				apriv->config.authType = AUTH_SHAREDKEY;
				apriv->keyindex++;
			पूर्ण अन्यथा अणु
			        /* Drop to ENCRYPT */
				apriv->keyindex = 0;
				set_wep_tx_idx(apriv, apriv->defindex, 0, 0);
				apriv->config.authType = AUTH_ENCRYPT;
			पूर्ण
			अवरोध;
		शेष:  /* We'll escalate to SHAREDKEY */
			apriv->config.authType = AUTH_SHAREDKEY;
	पूर्ण
	set_bit (FLAG_COMMIT, &apriv->flags);
	ग_लिखोConfigRid(apriv, 0);
	enable_MAC(apriv, 0);
	up(&apriv->sem);

/* Schedule check to see अगर the change worked */
	clear_bit(JOB_AUTOWEP, &apriv->jobs);
	apriv->expires = RUN_AT(HZ*3);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक airo_pci_probe(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *pent)
अणु
	काष्ठा net_device *dev;

	अगर (pci_enable_device(pdev))
		वापस -ENODEV;
	pci_set_master(pdev);

	अगर (pdev->device == 0x5000 || pdev->device == 0xa504)
			dev = _init_airo_card(pdev->irq, pdev->resource[0].start, 0, pdev, &pdev->dev);
	अन्यथा
			dev = _init_airo_card(pdev->irq, pdev->resource[2].start, 0, pdev, &pdev->dev);
	अगर (!dev) अणु
		pci_disable_device(pdev);
		वापस -ENODEV;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	वापस 0;
पूर्ण

अटल व्योम airo_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	airo_prपूर्णांक_info(dev->name, "Unregistering...");
	stop_airo_card(dev, 1);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused airo_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा airo_info *ai = dev->ml_priv;
	Cmd cmd;
	Resp rsp;

	अगर (!ai->SSID)
		ai->SSID = kदो_स्मृति(माप(SsidRid), GFP_KERNEL);
	अगर (!ai->SSID)
		वापस -ENOMEM;
	पढ़ोSsidRid(ai, ai->SSID);
	स_रखो(&cmd, 0, माप(cmd));
	/* the lock will be released at the end of the resume callback */
	अगर (करोwn_पूर्णांकerruptible(&ai->sem))
		वापस -EAGAIN;
	disable_MAC(ai, 0);
	netअगर_device_detach(dev);
	ai->घातer = PMSG_SUSPEND;
	cmd.cmd = HOSTSLEEP;
	issuecommand(ai, &cmd, &rsp, true);

	device_wakeup_enable(dev_d);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused airo_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा airo_info *ai = dev->ml_priv;
	pci_घातer_t prev_state = to_pci_dev(dev_d)->current_state;

	device_wakeup_disable(dev_d);

	अगर (prev_state != PCI_D1) अणु
		reset_card(dev, 0);
		mpi_init_descriptors(ai);
		setup_card(ai, dev->dev_addr, 0);
		clear_bit(FLAG_RADIO_OFF, &ai->flags);
		clear_bit(FLAG_PENDING_XMIT, &ai->flags);
	पूर्ण अन्यथा अणु
		OUT4500(ai, EVACK, EV_AWAKEN);
		OUT4500(ai, EVACK, EV_AWAKEN);
		msleep(100);
	पूर्ण

	set_bit(FLAG_COMMIT, &ai->flags);
	disable_MAC(ai, 0);
        msleep(200);
	अगर (ai->SSID) अणु
		ग_लिखोSsidRid(ai, ai->SSID, 0);
		kमुक्त(ai->SSID);
		ai->SSID = शून्य;
	पूर्ण
	ग_लिखोAPListRid(ai, &ai->APList, 0);
	ग_लिखोConfigRid(ai, 0);
	enable_MAC(ai, 0);
	ai->घातer = PMSG_ON;
	netअगर_device_attach(dev);
	netअगर_wake_queue(dev);
	enable_पूर्णांकerrupts(ai);
	up(&ai->sem);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init airo_init_module(व्योम)
अणु
	पूर्णांक i;

	proc_kuid = make_kuid(&init_user_ns, proc_uid);
	proc_kgid = make_kgid(&init_user_ns, proc_gid);
	अगर (!uid_valid(proc_kuid) || !gid_valid(proc_kgid))
		वापस -EINVAL;

	airo_entry = proc_सूची_गढ़ो_mode("driver/aironet", airo_perm, शून्य);

	अगर (airo_entry)
		proc_set_user(airo_entry, proc_kuid, proc_kgid);

	क्रम (i = 0; i < 4 && io[i] && irq[i]; i++) अणु
		airo_prपूर्णांक_info("", "Trying to configure ISA adapter at irq=%d "
			"io = 0x%x", irq[i], io[i]);
		अगर (init_airo_card(irq[i], io[i], 0, शून्य)) अणु
			/* करो nothing */ ;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PCI
	airo_prपूर्णांक_info("", "Probing for PCI adapters");
	i = pci_रेजिस्टर_driver(&airo_driver);
	airo_prपूर्णांक_info("", "Finished probing for PCI adapters");

	अगर (i) अणु
		हटाओ_proc_entry("driver/aironet", शून्य);
		वापस i;
	पूर्ण
#पूर्ण_अगर

	/* Always निकास with success, as we are a library module
	 * as well as a driver module
	 */
	वापस 0;
पूर्ण

अटल व्योम __निकास airo_cleanup_module(व्योम)
अणु
	काष्ठा airo_info *ai;
	जबतक (!list_empty(&airo_devices)) अणु
		ai = list_entry(airo_devices.next, काष्ठा airo_info, dev_list);
		airo_prपूर्णांक_info(ai->dev->name, "Unregistering...");
		stop_airo_card(ai->dev, 1);
	पूर्ण
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&airo_driver);
#पूर्ण_अगर
	हटाओ_proc_entry("driver/aironet", शून्य);
पूर्ण

/*
 * Initial Wireless Extension code क्रम Aironet driver by :
 *	Jean Tourrilhes <jt@hpl.hp.com> - HPL - 17 November 00
 * Conversion to new driver API by :
 *	Jean Tourrilhes <jt@hpl.hp.com> - HPL - 26 March 02
 * Javier also did a good amount of work here, adding some new extensions
 * and fixing my code. Let's just say that without him this code just
 * would not work at all... - Jean II
 */

अटल u8 airo_rssi_to_dbm (tdsRssiEntry *rssi_rid, u8 rssi)
अणु
	अगर (!rssi_rid)
		वापस 0;

	वापस (0x100 - rssi_rid[rssi].rssidBm);
पूर्ण

अटल u8 airo_dbm_to_pct (tdsRssiEntry *rssi_rid, u8 dbm)
अणु
	पूर्णांक i;

	अगर (!rssi_rid)
		वापस 0;

	क्रम (i = 0; i < 256; i++)
		अगर (rssi_rid[i].rssidBm == dbm)
			वापस rssi_rid[i].rssipct;

	वापस 0;
पूर्ण


अटल पूर्णांक airo_get_quality (StatusRid *status_rid, CapabilityRid *cap_rid)
अणु
	पूर्णांक quality = 0;
	u16 sq;

	अगर ((status_rid->mode & cpu_to_le16(0x3f)) != cpu_to_le16(0x3f))
		वापस 0;

	अगर (!(cap_rid->hardCap & cpu_to_le16(8)))
		वापस 0;

	sq = le16_to_cpu(status_rid->संकेतQuality);
	अगर (स_भेद(cap_rid->prodName, "350", 3))
		अगर (sq > 0x20)
			quality = 0;
		अन्यथा
			quality = 0x20 - sq;
	अन्यथा
		अगर (sq > 0xb0)
			quality = 0;
		अन्यथा अगर (sq < 0x10)
			quality = 0xa0;
		अन्यथा
			quality = 0xb0 - sq;
	वापस quality;
पूर्ण

#घोषणा airo_get_max_quality(cap_rid) (स_भेद((cap_rid)->prodName, "350", 3) ? 0x20 : 0xa0)
#घोषणा airo_get_avg_quality(cap_rid) (स_भेद((cap_rid)->prodName, "350", 3) ? 0x10 : 0x50)

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get protocol name
 */
अटल पूर्णांक airo_get_name(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 अक्षर *cwrq,
			 अक्षर *extra)
अणु
	म_नकल(cwrq, "IEEE 802.11-DS");
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set frequency
 */
अटल पूर्णांक airo_set_freq(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_freq *fwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
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
		/* We should करो a better check than that,
		 * based on the card capability !!! */
		अगर ((channel < 1) || (channel > 14)) अणु
			airo_prपूर्णांक_dbg(dev->name, "New channel value of %d is invalid!",
				fwrq->m);
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			पढ़ोConfigRid(local, 1);
			/* Yes ! We can set it !!! */
			local->config.channelSet = cpu_to_le16(channel);
			set_bit (FLAG_COMMIT, &local->flags);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get frequency
 */
अटल पूर्णांक airo_get_freq(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_freq *fwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	StatusRid status_rid;		/* Card status info */
	पूर्णांक ch;

	पढ़ोConfigRid(local, 1);
	अगर ((local->config.opmode & MODE_CFG_MASK) == MODE_STA_ESS)
		status_rid.channel = local->config.channelSet;
	अन्यथा
		पढ़ोStatusRid(local, &status_rid, 1);

	ch = le16_to_cpu(status_rid.channel);
	अगर ((ch > 0) && (ch < 15)) अणु
		fwrq->m = 100000 *
			ieee80211_channel_to_frequency(ch, NL80211_BAND_2GHZ);
		fwrq->e = 1;
	पूर्ण अन्यथा अणु
		fwrq->m = ch;
		fwrq->e = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set ESSID
 */
अटल पूर्णांक airo_set_essid(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *dwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	SsidRid SSID_rid;		/* SSIDs */

	/* Reload the list of current SSID */
	पढ़ोSsidRid(local, &SSID_rid);

	/* Check अगर we asked क्रम `any' */
	अगर (dwrq->flags == 0) अणु
		/* Just send an empty SSID list */
		स_रखो(&SSID_rid, 0, माप(SSID_rid));
	पूर्ण अन्यथा अणु
		अचिन्हित index = (dwrq->flags & IW_ENCODE_INDEX) - 1;

		/* Check the size of the string */
		अगर (dwrq->length > IW_ESSID_MAX_SIZE)
			वापस -E2BIG ;

		/* Check अगर index is valid */
		अगर (index >= ARRAY_SIZE(SSID_rid.ssids))
			वापस -EINVAL;

		/* Set the SSID */
		स_रखो(SSID_rid.ssids[index].ssid, 0,
		       माप(SSID_rid.ssids[index].ssid));
		स_नकल(SSID_rid.ssids[index].ssid, extra, dwrq->length);
		SSID_rid.ssids[index].len = cpu_to_le16(dwrq->length);
	पूर्ण
	SSID_rid.len = cpu_to_le16(माप(SSID_rid));
	/* Write it to the card */
	disable_MAC(local, 1);
	ग_लिखोSsidRid(local, &SSID_rid, 1);
	enable_MAC(local, 1);

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get ESSID
 */
अटल पूर्णांक airo_get_essid(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *dwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	StatusRid status_rid;		/* Card status info */

	पढ़ोStatusRid(local, &status_rid, 1);

	/* Note : अगर dwrq->flags != 0, we should
	 * get the relevant SSID from the SSID list... */

	/* Get the current SSID */
	स_नकल(extra, status_rid.SSID, le16_to_cpu(status_rid.SSIDlen));
	/* If none, we may want to get the one that was set */

	/* Push it out ! */
	dwrq->length = le16_to_cpu(status_rid.SSIDlen);
	dwrq->flags = 1; /* active */

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set AP address
 */
अटल पूर्णांक airo_set_wap(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			काष्ठा sockaddr *awrq,
			अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	Cmd cmd;
	Resp rsp;
	APListRid *APList_rid = &local->APList;

	अगर (awrq->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;
	अन्यथा अगर (is_broadcast_ether_addr(awrq->sa_data) ||
		 is_zero_ether_addr(awrq->sa_data)) अणु
		स_रखो(&cmd, 0, माप(cmd));
		cmd.cmd = CMD_LOSE_SYNC;
		अगर (करोwn_पूर्णांकerruptible(&local->sem))
			वापस -ERESTARTSYS;
		issuecommand(local, &cmd, &rsp, true);
		up(&local->sem);
	पूर्ण अन्यथा अणु
		स_रखो(APList_rid, 0, माप(*APList_rid));
		APList_rid->len = cpu_to_le16(माप(*APList_rid));
		स_नकल(APList_rid->ap[0], awrq->sa_data, ETH_ALEN);
		disable_MAC(local, 1);
		ग_लिखोAPListRid(local, APList_rid, 1);
		enable_MAC(local, 1);
	पूर्ण
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get AP address
 */
अटल पूर्णांक airo_get_wap(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			काष्ठा sockaddr *awrq,
			अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	StatusRid status_rid;		/* Card status info */

	पढ़ोStatusRid(local, &status_rid, 1);

	/* Tentative. This seems to work, wow, I'm lucky !!! */
	स_नकल(awrq->sa_data, status_rid.bssid[0], ETH_ALEN);
	awrq->sa_family = ARPHRD_ETHER;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Nickname
 */
अटल पूर्णांक airo_set_nick(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_poपूर्णांक *dwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	/* Check the size of the string */
	अगर (dwrq->length > 16) अणु
		वापस -E2BIG;
	पूर्ण
	पढ़ोConfigRid(local, 1);
	स_रखो(local->config.nodeName, 0, माप(local->config.nodeName));
	स_नकल(local->config.nodeName, extra, dwrq->length);
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Nickname
 */
अटल पूर्णांक airo_get_nick(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_poपूर्णांक *dwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	म_नकलन(extra, local->config.nodeName, 16);
	extra[16] = '\0';
	dwrq->length = म_माप(extra);

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Bit-Rate
 */
अटल पूर्णांक airo_set_rate(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	CapabilityRid cap_rid;		/* Card capability info */
	u8	brate = 0;
	पूर्णांक	i;

	/* First : get a valid bit rate value */
	पढ़ोCapabilityRid(local, &cap_rid, 1);

	/* Which type of value ? */
	अगर ((vwrq->value < 8) && (vwrq->value >= 0)) अणु
		/* Setting by rate index */
		/* Find value in the magic rate table */
		brate = cap_rid.supportedRates[vwrq->value];
	पूर्ण अन्यथा अणु
		/* Setting by frequency value */
		u8	normvalue = (u8) (vwrq->value/500000);

		/* Check अगर rate is valid */
		क्रम (i = 0 ; i < 8 ; i++) अणु
			अगर (normvalue == cap_rid.supportedRates[i]) अणु
				brate = normvalue;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* -1 deचिन्हित the max rate (mostly स्वतः mode) */
	अगर (vwrq->value == -1) अणु
		/* Get the highest available rate */
		क्रम (i = 0 ; i < 8 ; i++) अणु
			अगर (cap_rid.supportedRates[i] == 0)
				अवरोध;
		पूर्ण
		अगर (i != 0)
			brate = cap_rid.supportedRates[i - 1];
	पूर्ण
	/* Check that it is valid */
	अगर (brate == 0) अणु
		वापस -EINVAL;
	पूर्ण

	पढ़ोConfigRid(local, 1);
	/* Now, check अगर we want a fixed or स्वतः value */
	अगर (vwrq->fixed == 0) अणु
		/* Fill all the rates up to this max rate */
		स_रखो(local->config.rates, 0, 8);
		क्रम (i = 0 ; i < 8 ; i++) अणु
			local->config.rates[i] = cap_rid.supportedRates[i];
			अगर (local->config.rates[i] == brate)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fixed mode */
		/* One rate, fixed */
		स_रखो(local->config.rates, 0, 8);
		local->config.rates[0] = brate;
	पूर्ण
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Bit-Rate
 */
अटल पूर्णांक airo_get_rate(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	StatusRid status_rid;		/* Card status info */

	पढ़ोStatusRid(local, &status_rid, 1);

	vwrq->value = le16_to_cpu(status_rid.currentXmitRate) * 500000;
	/* If more than one rate, set स्वतः */
	पढ़ोConfigRid(local, 1);
	vwrq->fixed = (local->config.rates[1] == 0);

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set RTS threshold
 */
अटल पूर्णांक airo_set_rts(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			काष्ठा iw_param *vwrq,
			अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक rthr = vwrq->value;

	अगर (vwrq->disabled)
		rthr = AIRO_DEF_MTU;
	अगर ((rthr < 0) || (rthr > AIRO_DEF_MTU)) अणु
		वापस -EINVAL;
	पूर्ण
	पढ़ोConfigRid(local, 1);
	local->config.rtsThres = cpu_to_le16(rthr);
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get RTS threshold
 */
अटल पूर्णांक airo_get_rts(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			काष्ठा iw_param *vwrq,
			अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	vwrq->value = le16_to_cpu(local->config.rtsThres);
	vwrq->disabled = (vwrq->value >= AIRO_DEF_MTU);
	vwrq->fixed = 1;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Fragmentation threshold
 */
अटल पूर्णांक airo_set_frag(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक fthr = vwrq->value;

	अगर (vwrq->disabled)
		fthr = AIRO_DEF_MTU;
	अगर ((fthr < 256) || (fthr > AIRO_DEF_MTU)) अणु
		वापस -EINVAL;
	पूर्ण
	fthr &= ~0x1;	/* Get an even value - is it really needed ??? */
	पढ़ोConfigRid(local, 1);
	local->config.fragThresh = cpu_to_le16(fthr);
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Fragmentation threshold
 */
अटल पूर्णांक airo_get_frag(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	vwrq->value = le16_to_cpu(local->config.fragThresh);
	vwrq->disabled = (vwrq->value >= AIRO_DEF_MTU);
	vwrq->fixed = 1;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Mode of Operation
 */
अटल पूर्णांक airo_set_mode(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 __u32 *uwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक reset = 0;

	पढ़ोConfigRid(local, 1);
	अगर (snअगरfing_mode(local))
		reset = 1;

	चयन(*uwrq) अणु
		हाल IW_MODE_ADHOC:
			local->config.opmode &= ~MODE_CFG_MASK;
			local->config.opmode |= MODE_STA_IBSS;
			local->config.rmode &= ~RXMODE_FULL_MASK;
			local->config.scanMode = SCANMODE_ACTIVE;
			clear_bit (FLAG_802_11, &local->flags);
			अवरोध;
		हाल IW_MODE_INFRA:
			local->config.opmode &= ~MODE_CFG_MASK;
			local->config.opmode |= MODE_STA_ESS;
			local->config.rmode &= ~RXMODE_FULL_MASK;
			local->config.scanMode = SCANMODE_ACTIVE;
			clear_bit (FLAG_802_11, &local->flags);
			अवरोध;
		हाल IW_MODE_MASTER:
			local->config.opmode &= ~MODE_CFG_MASK;
			local->config.opmode |= MODE_AP;
			local->config.rmode &= ~RXMODE_FULL_MASK;
			local->config.scanMode = SCANMODE_ACTIVE;
			clear_bit (FLAG_802_11, &local->flags);
			अवरोध;
		हाल IW_MODE_REPEAT:
			local->config.opmode &= ~MODE_CFG_MASK;
			local->config.opmode |= MODE_AP_RPTR;
			local->config.rmode &= ~RXMODE_FULL_MASK;
			local->config.scanMode = SCANMODE_ACTIVE;
			clear_bit (FLAG_802_11, &local->flags);
			अवरोध;
		हाल IW_MODE_MONITOR:
			local->config.opmode &= ~MODE_CFG_MASK;
			local->config.opmode |= MODE_STA_ESS;
			local->config.rmode &= ~RXMODE_FULL_MASK;
			local->config.rmode |= RXMODE_RFMON | RXMODE_DISABLE_802_3_HEADER;
			local->config.scanMode = SCANMODE_PASSIVE;
			set_bit (FLAG_802_11, &local->flags);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	अगर (reset)
		set_bit (FLAG_RESET, &local->flags);
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Mode of Operation
 */
अटल पूर्णांक airo_get_mode(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 __u32 *uwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	/* If not managed, assume it's ad-hoc */
	चयन (local->config.opmode & MODE_CFG_MASK) अणु
		हाल MODE_STA_ESS:
			*uwrq = IW_MODE_INFRA;
			अवरोध;
		हाल MODE_AP:
			*uwrq = IW_MODE_MASTER;
			अवरोध;
		हाल MODE_AP_RPTR:
			*uwrq = IW_MODE_REPEAT;
			अवरोध;
		शेष:
			*uwrq = IW_MODE_ADHOC;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक valid_index(काष्ठा airo_info *ai, पूर्णांक index)
अणु
	वापस (index >= 0) && (index <= ai->max_wep_idx);
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Encryption Key
 */
अटल पूर्णांक airo_set_encode(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक perm = (dwrq->flags & IW_ENCODE_TEMP ? 0 : 1);
	__le16 currentAuthType = local->config.authType;
	पूर्णांक rc = 0;

	अगर (!local->wep_capable)
		वापस -EOPNOTSUPP;

	पढ़ोConfigRid(local, 1);

	/* Basic checking: करो we have a key to set ?
	 * Note : with the new API, it's impossible to get a शून्य poपूर्णांकer.
	 * Thereक्रमe, we need to check a key size == 0 instead.
	 * New version of iwconfig properly set the IW_ENCODE_NOKEY flag
	 * when no key is present (only change flags), but older versions
	 * करोn't करो it. - Jean II */
	अगर (dwrq->length > 0) अणु
		wep_key_t key;
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		पूर्णांक current_index;

		/* Check the size of the key */
		अगर (dwrq->length > MAX_KEY_SIZE) अणु
			वापस -EINVAL;
		पूर्ण

		current_index = get_wep_tx_idx(local);
		अगर (current_index < 0)
			current_index = 0;

		/* Check the index (none -> use current) */
		अगर (!valid_index(local, index))
			index = current_index;

		/* Set the length */
		अगर (dwrq->length > MIN_KEY_SIZE)
			key.len = MAX_KEY_SIZE;
		अन्यथा
			key.len = MIN_KEY_SIZE;
		/* Check अगर the key is not marked as invalid */
		अगर (!(dwrq->flags & IW_ENCODE_NOKEY)) अणु
			/* Cleanup */
			स_रखो(key.key, 0, MAX_KEY_SIZE);
			/* Copy the key in the driver */
			स_नकल(key.key, extra, dwrq->length);
			/* Send the key to the card */
			rc = set_wep_key(local, index, key.key, key.len, perm, 1);
			अगर (rc < 0) अणु
				airo_prपूर्णांक_err(local->dev->name, "failed to set"
				               " WEP key at index %d: %d.",
				               index, rc);
				वापस rc;
			पूर्ण
		पूर्ण
		/* WE specअगरy that अगर a valid key is set, encryption
		 * should be enabled (user may turn it off later)
		 * This is also how "iwconfig ethX key on" works */
		अगर ((index == current_index) && (key.len > 0) &&
		   (local->config.authType == AUTH_OPEN))
			set_auth_type(local, AUTH_ENCRYPT);
	पूर्ण अन्यथा अणु
		/* Do we want to just set the transmit key index ? */
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		अगर (valid_index(local, index)) अणु
			rc = set_wep_tx_idx(local, index, perm, 1);
			अगर (rc < 0) अणु
				airo_prपूर्णांक_err(local->dev->name, "failed to set"
				               " WEP transmit index to %d: %d.",
				               index, rc);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Don't complain अगर only change the mode */
			अगर (!(dwrq->flags & IW_ENCODE_MODE))
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Read the flags */
	अगर (dwrq->flags & IW_ENCODE_DISABLED)
		set_auth_type(local, AUTH_OPEN);	/* disable encryption */
	अगर (dwrq->flags & IW_ENCODE_RESTRICTED)
		set_auth_type(local, AUTH_SHAREDKEY);	/* Only Both */
	अगर (dwrq->flags & IW_ENCODE_OPEN)
		set_auth_type(local, AUTH_ENCRYPT);	/* Only Wep */
	/* Commit the changes to flags अगर needed */
	अगर (local->config.authType != currentAuthType)
		set_bit (FLAG_COMMIT, &local->flags);
	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Encryption Key
 */
अटल पूर्णांक airo_get_encode(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
	पूर्णांक wep_key_len;
	u8 buf[16];

	अगर (!local->wep_capable)
		वापस -EOPNOTSUPP;

	पढ़ोConfigRid(local, 1);

	/* Check encryption mode */
	चयन(local->config.authType)	अणु
		हाल AUTH_ENCRYPT:
			dwrq->flags = IW_ENCODE_OPEN;
			अवरोध;
		हाल AUTH_SHAREDKEY:
			dwrq->flags = IW_ENCODE_RESTRICTED;
			अवरोध;
		शेष:
		हाल AUTH_OPEN:
			dwrq->flags = IW_ENCODE_DISABLED;
			अवरोध;
	पूर्ण
	/* We can't वापस the key, so set the proper flag and वापस zero */
	dwrq->flags |= IW_ENCODE_NOKEY;
	स_रखो(extra, 0, 16);

	/* Which key करो we want ? -1 -> tx index */
	अगर (!valid_index(local, index)) अणु
		index = get_wep_tx_idx(local);
		अगर (index < 0)
			index = 0;
	पूर्ण
	dwrq->flags |= index + 1;

	/* Copy the key to the user buffer */
	wep_key_len = get_wep_key(local, index, &buf[0], माप(buf));
	अगर (wep_key_len < 0) अणु
		dwrq->length = 0;
	पूर्ण अन्यथा अणु
		dwrq->length = wep_key_len;
		स_नकल(extra, buf, dwrq->length);
	पूर्ण

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set extended Encryption parameters
 */
अटल पूर्णांक airo_set_encodeext(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu,
			    अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक perm = (encoding->flags & IW_ENCODE_TEMP ? 0 : 1);
	__le16 currentAuthType = local->config.authType;
	पूर्णांक idx, key_len, alg = ext->alg, set_key = 1, rc;
	wep_key_t key;

	अगर (!local->wep_capable)
		वापस -EOPNOTSUPP;

	पढ़ोConfigRid(local, 1);

	/* Determine and validate the key index */
	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (!valid_index(local, idx - 1))
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा अणु
		idx = get_wep_tx_idx(local);
		अगर (idx < 0)
			idx = 0;
	पूर्ण

	अगर (encoding->flags & IW_ENCODE_DISABLED)
		alg = IW_ENCODE_ALG_NONE;

	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		/* Only set transmit key index here, actual
		 * key is set below अगर needed.
		 */
		rc = set_wep_tx_idx(local, idx, perm, 1);
		अगर (rc < 0) अणु
			airo_prपूर्णांक_err(local->dev->name, "failed to set "
			               "WEP transmit index to %d: %d.",
			               idx, rc);
			वापस rc;
		पूर्ण
		set_key = ext->key_len > 0 ? 1 : 0;
	पूर्ण

	अगर (set_key) अणु
		/* Set the requested key first */
		स_रखो(key.key, 0, MAX_KEY_SIZE);
		चयन (alg) अणु
		हाल IW_ENCODE_ALG_NONE:
			key.len = 0;
			अवरोध;
		हाल IW_ENCODE_ALG_WEP:
			अगर (ext->key_len > MIN_KEY_SIZE) अणु
				key.len = MAX_KEY_SIZE;
			पूर्ण अन्यथा अगर (ext->key_len > 0) अणु
				key.len = MIN_KEY_SIZE;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
			key_len = min (ext->key_len, key.len);
			स_नकल(key.key, ext->key, key_len);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (key.len == 0) अणु
			rc = set_wep_tx_idx(local, idx, perm, 1);
			अगर (rc < 0) अणु
				airo_prपूर्णांक_err(local->dev->name,
					       "failed to set WEP transmit index to %d: %d.",
					       idx, rc);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = set_wep_key(local, idx, key.key, key.len, perm, 1);
			अगर (rc < 0) अणु
				airo_prपूर्णांक_err(local->dev->name,
					       "failed to set WEP key at index %d: %d.",
					       idx, rc);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Read the flags */
	अगर (encoding->flags & IW_ENCODE_DISABLED)
		set_auth_type(local, AUTH_OPEN);	/* disable encryption */
	अगर (encoding->flags & IW_ENCODE_RESTRICTED)
		set_auth_type(local, AUTH_SHAREDKEY);	/* Only Both */
	अगर (encoding->flags & IW_ENCODE_OPEN)
		set_auth_type(local, AUTH_ENCRYPT);
	/* Commit the changes to flags अगर needed */
	अगर (local->config.authType != currentAuthType)
		set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;
पूर्ण


/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get extended Encryption parameters
 */
अटल पूर्णांक airo_get_encodeext(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu,
			    अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, max_key_len, wep_key_len;
	u8 buf[16];

	अगर (!local->wep_capable)
		वापस -EOPNOTSUPP;

	पढ़ोConfigRid(local, 1);

	max_key_len = encoding->length - माप(*ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर (!valid_index(local, idx - 1))
			वापस -EINVAL;
		idx--;
	पूर्ण अन्यथा अणु
		idx = get_wep_tx_idx(local);
		अगर (idx < 0)
			idx = 0;
	पूर्ण

	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	/* Check encryption mode */
	चयन(local->config.authType) अणु
		हाल AUTH_ENCRYPT:
			encoding->flags = IW_ENCODE_ALG_WEP | IW_ENCODE_ENABLED;
			अवरोध;
		हाल AUTH_SHAREDKEY:
			encoding->flags = IW_ENCODE_ALG_WEP | IW_ENCODE_ENABLED;
			अवरोध;
		शेष:
		हाल AUTH_OPEN:
			encoding->flags = IW_ENCODE_ALG_NONE | IW_ENCODE_DISABLED;
			अवरोध;
	पूर्ण
	/* We can't वापस the key, so set the proper flag and वापस zero */
	encoding->flags |= IW_ENCODE_NOKEY;
	स_रखो(extra, 0, 16);

	/* Copy the key to the user buffer */
	wep_key_len = get_wep_key(local, idx, &buf[0], माप(buf));
	अगर (wep_key_len < 0) अणु
		ext->key_len = 0;
	पूर्ण अन्यथा अणु
		ext->key_len = wep_key_len;
		स_नकल(extra, buf, ext->key_len);
	पूर्ण

	वापस 0;
पूर्ण


/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set extended authentication parameters
 */
अटल पूर्णांक airo_set_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा iw_param *param = &wrqu->param;
	__le16 currentAuthType = local->config.authType;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
	हाल IW_AUTH_PRIVACY_INVOKED:
		/*
		 * airo करोes not use these parameters
		 */
		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		अगर (param->value) अणु
			/* Only change auth type अगर unencrypted */
			अगर (currentAuthType == AUTH_OPEN)
				set_auth_type(local, AUTH_ENCRYPT);
		पूर्ण अन्यथा अणु
			set_auth_type(local, AUTH_OPEN);
		पूर्ण

		/* Commit the changes to flags अगर needed */
		अगर (local->config.authType != currentAuthType)
			set_bit (FLAG_COMMIT, &local->flags);
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG: अणु
			अगर (param->value & IW_AUTH_ALG_SHARED_KEY) अणु
				set_auth_type(local, AUTH_SHAREDKEY);
			पूर्ण अन्यथा अगर (param->value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
				/* We करोn't know here अगर WEP खोलो प्रणाली or
				 * unencrypted mode was requested - so use the
				 * last mode (of these two) used last समय
				 */
				set_auth_type(local, local->last_auth);
			पूर्ण अन्यथा
				वापस -EINVAL;

			/* Commit the changes to flags अगर needed */
			अगर (local->config.authType != currentAuthType)
				set_bit (FLAG_COMMIT, &local->flags);
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


/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get extended authentication parameters
 */
अटल पूर्णांक airo_get_auth(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा iw_param *param = &wrqu->param;
	__le16 currentAuthType = local->config.authType;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_DROP_UNENCRYPTED:
		चयन (currentAuthType) अणु
		हाल AUTH_SHAREDKEY:
		हाल AUTH_ENCRYPT:
			param->value = 1;
			अवरोध;
		शेष:
			param->value = 0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		चयन (currentAuthType) अणु
		हाल AUTH_SHAREDKEY:
			param->value = IW_AUTH_ALG_SHARED_KEY;
			अवरोध;
		हाल AUTH_ENCRYPT:
		शेष:
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		param->value = 0;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण


/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Tx-Power
 */
अटल पूर्णांक airo_set_txघात(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	CapabilityRid cap_rid;		/* Card capability info */
	पूर्णांक i;
	पूर्णांक rc = -EINVAL;
	__le16 v = cpu_to_le16(vwrq->value);

	पढ़ोCapabilityRid(local, &cap_rid, 1);

	अगर (vwrq->disabled) अणु
		set_bit (FLAG_RADIO_OFF, &local->flags);
		set_bit (FLAG_COMMIT, &local->flags);
		वापस -EINPROGRESS;		/* Call commit handler */
	पूर्ण
	अगर (vwrq->flags != IW_TXPOW_MWATT) अणु
		वापस -EINVAL;
	पूर्ण
	clear_bit (FLAG_RADIO_OFF, &local->flags);
	क्रम (i = 0; i < 8 && cap_rid.txPowerLevels[i]; i++)
		अगर (v == cap_rid.txPowerLevels[i]) अणु
			पढ़ोConfigRid(local, 1);
			local->config.txPower = v;
			set_bit (FLAG_COMMIT, &local->flags);
			rc = -EINPROGRESS;	/* Call commit handler */
			अवरोध;
		पूर्ण
	वापस rc;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Tx-Power
 */
अटल पूर्णांक airo_get_txघात(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	vwrq->value = le16_to_cpu(local->config.txPower);
	vwrq->fixed = 1;	/* No घातer control */
	vwrq->disabled = test_bit(FLAG_RADIO_OFF, &local->flags);
	vwrq->flags = IW_TXPOW_MWATT;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Retry limits
 */
अटल पूर्णांक airo_set_retry(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	पूर्णांक rc = -EINVAL;

	अगर (vwrq->disabled) अणु
		वापस -EINVAL;
	पूर्ण
	पढ़ोConfigRid(local, 1);
	अगर (vwrq->flags & IW_RETRY_LIMIT) अणु
		__le16 v = cpu_to_le16(vwrq->value);
		अगर (vwrq->flags & IW_RETRY_LONG)
			local->config.दीर्घRetryLimit = v;
		अन्यथा अगर (vwrq->flags & IW_RETRY_SHORT)
			local->config.लघुRetryLimit = v;
		अन्यथा अणु
			/* No modअगरier : set both */
			local->config.दीर्घRetryLimit = v;
			local->config.लघुRetryLimit = v;
		पूर्ण
		set_bit (FLAG_COMMIT, &local->flags);
		rc = -EINPROGRESS;		/* Call commit handler */
	पूर्ण
	अगर (vwrq->flags & IW_RETRY_LIFETIME) अणु
		local->config.txLअगरeसमय = cpu_to_le16(vwrq->value / 1024);
		set_bit (FLAG_COMMIT, &local->flags);
		rc = -EINPROGRESS;		/* Call commit handler */
	पूर्ण
	वापस rc;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Retry limits
 */
अटल पूर्णांक airo_get_retry(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	vwrq->disabled = 0;      /* Can't be disabled */

	पढ़ोConfigRid(local, 1);
	/* Note : by शेष, display the min retry number */
	अगर ((vwrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) अणु
		vwrq->flags = IW_RETRY_LIFETIME;
		vwrq->value = le16_to_cpu(local->config.txLअगरeसमय) * 1024;
	पूर्ण अन्यथा अगर ((vwrq->flags & IW_RETRY_LONG)) अणु
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		vwrq->value = le16_to_cpu(local->config.दीर्घRetryLimit);
	पूर्ण अन्यथा अणु
		vwrq->flags = IW_RETRY_LIMIT;
		vwrq->value = le16_to_cpu(local->config.लघुRetryLimit);
		अगर (local->config.लघुRetryLimit != local->config.दीर्घRetryLimit)
			vwrq->flags |= IW_RETRY_SHORT;
	पूर्ण

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get range info
 */
अटल पूर्णांक airo_get_range(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *dwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा iw_range *range = (काष्ठा iw_range *) extra;
	CapabilityRid cap_rid;		/* Card capability info */
	पूर्णांक		i;
	पूर्णांक		k;

	पढ़ोCapabilityRid(local, &cap_rid, 1);

	dwrq->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(*range));
	range->min_nwid = 0x0000;
	range->max_nwid = 0x0000;
	range->num_channels = 14;
	/* Should be based on cap_rid.country to give only
	 * what the current card support */
	k = 0;
	क्रम (i = 0; i < 14; i++) अणु
		range->freq[k].i = i + 1; /* List index */
		range->freq[k].m = 100000 *
		     ieee80211_channel_to_frequency(i + 1, NL80211_BAND_2GHZ);
		range->freq[k++].e = 1;	/* Values in MHz -> * 10^5 * 10 */
	पूर्ण
	range->num_frequency = k;

	range->sensitivity = 65535;

	/* Hum... Should put the right values there */
	अगर (local->rssi)
		range->max_qual.qual = 100;	/* % */
	अन्यथा
		range->max_qual.qual = airo_get_max_quality(&cap_rid);
	range->max_qual.level = 0x100 - 120;	/* -120 dBm */
	range->max_qual.noise = 0x100 - 120;	/* -120 dBm */

	/* Experimental measurements - boundary 11/5.5 Mb/s */
	/* Note : with or without the (local->rssi), results
	 * are somewhat dअगरferent. - Jean II */
	अगर (local->rssi) अणु
		range->avg_qual.qual = 50;		/* % */
		range->avg_qual.level = 0x100 - 70;	/* -70 dBm */
	पूर्ण अन्यथा अणु
		range->avg_qual.qual = airo_get_avg_quality(&cap_rid);
		range->avg_qual.level = 0x100 - 80;	/* -80 dBm */
	पूर्ण
	range->avg_qual.noise = 0x100 - 85;		/* -85 dBm */

	क्रम (i = 0 ; i < 8 ; i++) अणु
		range->bitrate[i] = cap_rid.supportedRates[i] * 500000;
		अगर (range->bitrate[i] == 0)
			अवरोध;
	पूर्ण
	range->num_bitrates = i;

	/* Set an indication of the max TCP throughput
	 * in bit/s that we can expect using this पूर्णांकerface.
	 * May be use क्रम QoS stuff... Jean II */
	अगर (i > 2)
		range->throughput = 5000 * 1000;
	अन्यथा
		range->throughput = 1500 * 1000;

	range->min_rts = 0;
	range->max_rts = AIRO_DEF_MTU;
	range->min_frag = 256;
	range->max_frag = AIRO_DEF_MTU;

	अगर (cap_rid.softCap & cpu_to_le16(2)) अणु
		// WEP: RC4 40 bits
		range->encoding_size[0] = 5;
		// RC4 ~128 bits
		अगर (cap_rid.softCap & cpu_to_le16(0x100)) अणु
			range->encoding_size[1] = 13;
			range->num_encoding_sizes = 2;
		पूर्ण अन्यथा
			range->num_encoding_sizes = 1;
		range->max_encoding_tokens =
			cap_rid.softCap & cpu_to_le16(0x80) ? 4 : 1;
	पूर्ण अन्यथा अणु
		range->num_encoding_sizes = 0;
		range->max_encoding_tokens = 0;
	पूर्ण
	range->min_pmp = 0;
	range->max_pmp = 5000000;	/* 5 secs */
	range->min_pmt = 0;
	range->max_pmt = 65535 * 1024;	/* ??? */
	range->pmp_flags = IW_POWER_PERIOD;
	range->pmt_flags = IW_POWER_TIMEOUT;
	range->pm_capa = IW_POWER_PERIOD | IW_POWER_TIMEOUT | IW_POWER_ALL_R;

	/* Transmit Power - values are in mW */
	क्रम (i = 0 ; i < 8 ; i++) अणु
		range->txघातer[i] = le16_to_cpu(cap_rid.txPowerLevels[i]);
		अगर (range->txघातer[i] == 0)
			अवरोध;
	पूर्ण
	range->num_txघातer = i;
	range->txघातer_capa = IW_TXPOW_MWATT;
	range->we_version_source = 19;
	range->we_version_compiled = WIRELESS_EXT;
	range->retry_capa = IW_RETRY_LIMIT | IW_RETRY_LIFETIME;
	range->retry_flags = IW_RETRY_LIMIT;
	range->r_समय_flags = IW_RETRY_LIFETIME;
	range->min_retry = 1;
	range->max_retry = 65535;
	range->min_r_समय = 1024;
	range->max_r_समय = 65535 * 1024;

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWTHRSPY) |
				IW_EVENT_CAPA_MASK(SIOCGIWAP) |
				IW_EVENT_CAPA_MASK(SIOCGIWSCAN));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;
	range->event_capa[4] = IW_EVENT_CAPA_MASK(IWEVTXDROP);
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Power Management
 */
अटल पूर्णांक airo_set_घातer(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	अगर (vwrq->disabled) अणु
		अगर (snअगरfing_mode(local))
			वापस -EINVAL;
		local->config.घातerSaveMode = POWERSAVE_CAM;
		local->config.rmode &= ~RXMODE_MASK;
		local->config.rmode |= RXMODE_BC_MC_ADDR;
		set_bit (FLAG_COMMIT, &local->flags);
		वापस -EINPROGRESS;		/* Call commit handler */
	पूर्ण
	अगर ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) अणु
		local->config.fastListenDelay = cpu_to_le16((vwrq->value + 500) / 1024);
		local->config.घातerSaveMode = POWERSAVE_PSPCAM;
		set_bit (FLAG_COMMIT, &local->flags);
	पूर्ण अन्यथा अगर ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_PERIOD) अणु
		local->config.fastListenInterval =
		local->config.listenInterval =
			cpu_to_le16((vwrq->value + 500) / 1024);
		local->config.घातerSaveMode = POWERSAVE_PSPCAM;
		set_bit (FLAG_COMMIT, &local->flags);
	पूर्ण
	चयन (vwrq->flags & IW_POWER_MODE) अणु
		हाल IW_POWER_UNICAST_R:
			अगर (snअगरfing_mode(local))
				वापस -EINVAL;
			local->config.rmode &= ~RXMODE_MASK;
			local->config.rmode |= RXMODE_ADDR;
			set_bit (FLAG_COMMIT, &local->flags);
			अवरोध;
		हाल IW_POWER_ALL_R:
			अगर (snअगरfing_mode(local))
				वापस -EINVAL;
			local->config.rmode &= ~RXMODE_MASK;
			local->config.rmode |= RXMODE_BC_MC_ADDR;
			set_bit (FLAG_COMMIT, &local->flags);
			अवरोध;
		हाल IW_POWER_ON:
			/* This is broken, fixme ;-) */
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	// Note : we may want to factor local->need_commit here
	// Note2 : may also want to factor RXMODE_RFMON test
	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Power Management
 */
अटल पूर्णांक airo_get_घातer(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_param *vwrq,
			  अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	__le16 mode;

	पढ़ोConfigRid(local, 1);
	mode = local->config.घातerSaveMode;
	अगर ((vwrq->disabled = (mode == POWERSAVE_CAM)))
		वापस 0;
	अगर ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) अणु
		vwrq->value = le16_to_cpu(local->config.fastListenDelay) * 1024;
		vwrq->flags = IW_POWER_TIMEOUT;
	पूर्ण अन्यथा अणु
		vwrq->value = le16_to_cpu(local->config.fastListenInterval) * 1024;
		vwrq->flags = IW_POWER_PERIOD;
	पूर्ण
	अगर ((local->config.rmode & RXMODE_MASK) == RXMODE_ADDR)
		vwrq->flags |= IW_POWER_UNICAST_R;
	अन्यथा
		vwrq->flags |= IW_POWER_ALL_R;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Sensitivity
 */
अटल पूर्णांक airo_set_sens(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	local->config.rssiThreshold =
		cpu_to_le16(vwrq->disabled ? RSSI_DEFAULT : vwrq->value);
	set_bit (FLAG_COMMIT, &local->flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Sensitivity
 */
अटल पूर्णांक airo_get_sens(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_param *vwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	पढ़ोConfigRid(local, 1);
	vwrq->value = le16_to_cpu(local->config.rssiThreshold);
	vwrq->disabled = (vwrq->value == 0);
	vwrq->fixed = 1;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get AP List
 * Note : this is deprecated in favor of IWSCAN
 */
अटल पूर्णांक airo_get_aplist(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *dwrq,
			   अक्षर *extra)
अणु
	काष्ठा airo_info *local = dev->ml_priv;
	काष्ठा sockaddr *address = (काष्ठा sockaddr *) extra;
	काष्ठा iw_quality *qual;
	BSSListRid BSSList;
	पूर्णांक i;
	पूर्णांक loseSync = capable(CAP_NET_ADMIN) ? 1: -1;

	qual = kदो_स्मृति_array(IW_MAX_AP, माप(*qual), GFP_KERNEL);
	अगर (!qual)
		वापस -ENOMEM;

	क्रम (i = 0; i < IW_MAX_AP; i++) अणु
		u16 dBm;
		अगर (पढ़ोBSSListRid(local, loseSync, &BSSList))
			अवरोध;
		loseSync = 0;
		स_नकल(address[i].sa_data, BSSList.bssid, ETH_ALEN);
		address[i].sa_family = ARPHRD_ETHER;
		dBm = le16_to_cpu(BSSList.dBm);
		अगर (local->rssi) अणु
			qual[i].level = 0x100 - dBm;
			qual[i].qual = airo_dbm_to_pct(local->rssi, dBm);
			qual[i].updated = IW_QUAL_QUAL_UPDATED
					| IW_QUAL_LEVEL_UPDATED
					| IW_QUAL_DBM;
		पूर्ण अन्यथा अणु
			qual[i].level = (dBm + 321) / 2;
			qual[i].qual = 0;
			qual[i].updated = IW_QUAL_QUAL_INVALID
					| IW_QUAL_LEVEL_UPDATED
					| IW_QUAL_DBM;
		पूर्ण
		qual[i].noise = local->wstats.qual.noise;
		अगर (BSSList.index == cpu_to_le16(0xffff))
			अवरोध;
	पूर्ण
	अगर (!i) अणु
		StatusRid status_rid;		/* Card status info */
		पढ़ोStatusRid(local, &status_rid, 1);
		क्रम (i = 0;
		     i < min(IW_MAX_AP, 4) &&
			     (status_rid.bssid[i][0]
			      & status_rid.bssid[i][1]
			      & status_rid.bssid[i][2]
			      & status_rid.bssid[i][3]
			      & status_rid.bssid[i][4]
			      & status_rid.bssid[i][5])!=0xff &&
			     (status_rid.bssid[i][0]
			      | status_rid.bssid[i][1]
			      | status_rid.bssid[i][2]
			      | status_rid.bssid[i][3]
			      | status_rid.bssid[i][4]
			      | status_rid.bssid[i][5]);
		     i++) अणु
			स_नकल(address[i].sa_data,
			       status_rid.bssid[i], ETH_ALEN);
			address[i].sa_family = ARPHRD_ETHER;
		पूर्ण
	पूर्ण अन्यथा अणु
		dwrq->flags = 1; /* Should be define'd */
		स_नकल(extra + माप(काष्ठा sockaddr) * i, qual,
		       माप(काष्ठा iw_quality) * i);
	पूर्ण
	dwrq->length = i;

	kमुक्त(qual);
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : Initiate Scan
 */
अटल पूर्णांक airo_set_scan(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_poपूर्णांक *dwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	Cmd cmd;
	Resp rsp;
	पूर्णांक wake = 0;
	APListRid APList_rid_empty;

	/* Note : you may have realised that, as this is a SET operation,
	 * this is privileged and thereक्रमe a normal user can't
	 * perक्रमm scanning.
	 * This is not an error, जबतक the device perक्रमm scanning,
	 * traffic करोesn't flow, so it's a perfect DoS...
	 * Jean II */
	अगर (ai->flags & FLAG_RADIO_MASK) वापस -ENETDOWN;

	अगर (करोwn_पूर्णांकerruptible(&ai->sem))
		वापस -ERESTARTSYS;

	/* If there's already a scan in progress, don't
	 * trigger another one. */
	अगर (ai->scan_समयout > 0)
		जाओ out;

	/* Clear APList as it affects scan results */
	स_रखो(&APList_rid_empty, 0, माप(APList_rid_empty));
	APList_rid_empty.len = cpu_to_le16(माप(APList_rid_empty));
	disable_MAC(ai, 2);
	ग_लिखोAPListRid(ai, &APList_rid_empty, 0);
	enable_MAC(ai, 0);

	/* Initiate a scan command */
	ai->scan_समयout = RUN_AT(3*HZ);
	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd = CMD_LISTBSS;
	issuecommand(ai, &cmd, &rsp, true);
	wake = 1;

out:
	up(&ai->sem);
	अगर (wake)
		wake_up_पूर्णांकerruptible(&ai->thr_रुको);
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Translate scan data वापसed from the card to a card independent
 * क्रमmat that the Wireless Tools will understand - Jean II
 */
अटल अंतरभूत अक्षर *airo_translate_scan(काष्ठा net_device *dev,
					काष्ठा iw_request_info *info,
					अक्षर *current_ev,
					अक्षर *end_buf,
					BSSListRid *bss)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	काष्ठा iw_event		iwe;		/* Temporary buffer */
	__le16			capabilities;
	अक्षर *			current_val;	/* For rates */
	पूर्णांक			i;
	अक्षर *		buf;
	u16 dBm;

	/* First entry *MUST* be the AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, bss->bssid, ETH_ALEN);
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_ADDR_LEN);

	/* Other entries will be displayed in the order we give them */

	/* Add the ESSID */
	iwe.u.data.length = bss->ssidLen;
	अगर (iwe.u.data.length > 32)
		iwe.u.data.length = 32;
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, bss->ssid);

	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	capabilities = bss->cap;
	अगर (capabilities & (CAP_ESS | CAP_IBSS)) अणु
		अगर (capabilities & CAP_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_UINT_LEN);
	पूर्ण

	/* Add frequency */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = le16_to_cpu(bss->dsChannel);
	iwe.u.freq.m = 100000 *
	      ieee80211_channel_to_frequency(iwe.u.freq.m, NL80211_BAND_2GHZ);
	iwe.u.freq.e = 1;
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_FREQ_LEN);

	dBm = le16_to_cpu(bss->dBm);

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	अगर (ai->rssi) अणु
		iwe.u.qual.level = 0x100 - dBm;
		iwe.u.qual.qual = airo_dbm_to_pct(ai->rssi, dBm);
		iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED
				| IW_QUAL_LEVEL_UPDATED
				| IW_QUAL_DBM;
	पूर्ण अन्यथा अणु
		iwe.u.qual.level = (dBm + 321) / 2;
		iwe.u.qual.qual = 0;
		iwe.u.qual.updated = IW_QUAL_QUAL_INVALID
				| IW_QUAL_LEVEL_UPDATED
				| IW_QUAL_DBM;
	पूर्ण
	iwe.u.qual.noise = ai->wstats.qual.noise;
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_QUAL_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	अगर (capabilities & CAP_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, bss->ssid);

	/* Rate : stuffing multiple values in a single event require a bit
	 * more of magic - Jean II */
	current_val = current_ev + iwe_stream_lcp_len(info);

	iwe.cmd = SIOCGIWRATE;
	/* Those two flags are ignored... */
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	/* Max 8 values */
	क्रम (i = 0 ; i < 8 ; i++) अणु
		/* शून्य terminated */
		अगर (bss->rates[i] == 0)
			अवरोध;
		/* Bit rate given in 500 kb/s units (+ 0x80) */
		iwe.u.bitrate.value = ((bss->rates[i] & 0x7f) * 500000);
		/* Add new value to event */
		current_val = iwe_stream_add_value(info, current_ev,
						   current_val, end_buf,
						   &iwe, IW_EV_PARAM_LEN);
	पूर्ण
	/* Check अगर we added any event */
	अगर ((current_val - current_ev) > iwe_stream_lcp_len(info))
		current_ev = current_val;

	/* Beacon पूर्णांकerval */
	buf = kदो_स्मृति(30, GFP_KERNEL);
	अगर (buf) अणु
		iwe.cmd = IWEVCUSTOM;
		प्र_लिखो(buf, "bcn_int=%d", bss->beaconInterval);
		iwe.u.data.length = म_माप(buf);
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, buf);
		kमुक्त(buf);
	पूर्ण

	/* Put WPA/RSN Inक्रमmation Elements पूर्णांकo the event stream */
	अगर (test_bit(FLAG_WPA_CAPABLE, &ai->flags)) अणु
		अचिन्हित पूर्णांक num_null_ies = 0;
		u16 length = माप (bss->extra.iep);
		u8 *ie = (व्योम *)&bss->extra.iep;

		जबतक ((length >= 2) && (num_null_ies < 2)) अणु
			अगर (2 + ie[1] > length) अणु
				/* Invalid element, करोn't जारी parsing IE */
				अवरोध;
			पूर्ण

			चयन (ie[0]) अणु
			हाल WLAN_EID_SSID:
				/* Two zero-length SSID elements
				 * mean we're करोne parsing elements */
				अगर (!ie[1])
					num_null_ies++;
				अवरोध;

			हाल WLAN_EID_VENDOR_SPECIFIC:
				अगर (ie[1] >= 4 &&
				    ie[2] == 0x00 &&
				    ie[3] == 0x50 &&
				    ie[4] == 0xf2 &&
				    ie[5] == 0x01) अणु
					iwe.cmd = IWEVGENIE;
					/* 64 is an arbitrary cut-off */
					iwe.u.data.length = min(ie[1] + 2,
								64);
					current_ev = iwe_stream_add_poपूर्णांक(
							info, current_ev,
							end_buf, &iwe, ie);
				पूर्ण
				अवरोध;

			हाल WLAN_EID_RSN:
				iwe.cmd = IWEVGENIE;
				/* 64 is an arbitrary cut-off */
				iwe.u.data.length = min(ie[1] + 2, 64);
				current_ev = iwe_stream_add_poपूर्णांक(
					info, current_ev, end_buf,
					&iwe, ie);
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण

			length -= 2 + ie[1];
			ie += 2 + ie[1];
		पूर्ण
	पूर्ण
	वापस current_ev;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : Read Scan Results
 */
अटल पूर्णांक airo_get_scan(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 काष्ठा iw_poपूर्णांक *dwrq,
			 अक्षर *extra)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	BSSListElement *net;
	पूर्णांक err = 0;
	अक्षर *current_ev = extra;

	/* If a scan is in-progress, वापस -EAGAIN */
	अगर (ai->scan_समयout > 0)
		वापस -EAGAIN;

	अगर (करोwn_पूर्णांकerruptible(&ai->sem))
		वापस -EAGAIN;

	list_क्रम_each_entry (net, &ai->network_list, list) अणु
		/* Translate to WE क्रमmat this entry */
		current_ev = airo_translate_scan(dev, info, current_ev,
						 extra + dwrq->length,
						 &net->bss);

		/* Check अगर there is space क्रम one more entry */
		अगर ((extra + dwrq->length - current_ev) <= IW_EV_ADDR_LEN) अणु
			/* Ask user space to try again with a bigger buffer */
			err = -E2BIG;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Length of data */
	dwrq->length = (current_ev - extra);
	dwrq->flags = 0;	/* toकरो */

out:
	up(&ai->sem);
	वापस err;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Commit handler : called after a bunch of SET operations
 */
अटल पूर्णांक airo_config_commit(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,	/* शून्य */
			      व्योम *zwrq,			/* शून्य */
			      अक्षर *extra)			/* शून्य */
अणु
	काष्ठा airo_info *local = dev->ml_priv;

	अगर (!test_bit (FLAG_COMMIT, &local->flags))
		वापस 0;

	/* Some of the "SET" function may have modअगरied some of the
	 * parameters. It's now समय to commit them in the card */
	disable_MAC(local, 1);
	अगर (test_bit (FLAG_RESET, &local->flags)) अणु
		SsidRid SSID_rid;

		पढ़ोSsidRid(local, &SSID_rid);
		अगर (test_bit(FLAG_MPI,&local->flags))
			setup_card(local, dev->dev_addr, 1);
		अन्यथा
			reset_airo_card(dev);
		disable_MAC(local, 1);
		ग_लिखोSsidRid(local, &SSID_rid, 1);
		ग_लिखोAPListRid(local, &local->APList, 1);
	पूर्ण
	अगर (करोwn_पूर्णांकerruptible(&local->sem))
		वापस -ERESTARTSYS;
	ग_लिखोConfigRid(local, 0);
	enable_MAC(local, 0);
	अगर (test_bit (FLAG_RESET, &local->flags))
		airo_set_promisc(local, true);
	अन्यथा
		up(&local->sem);

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Structures to export the Wireless Handlers
 */

अटल स्थिर काष्ठा iw_priv_args airo_निजी_args[] = अणु
/*अणु cmd,         set_args,                            get_args, name पूर्ण */
  अणु AIROIOCTL, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | माप (aironet_ioctl),
    IW_PRIV_TYPE_BYTE | 2047, "airoioctl" पूर्ण,
  अणु AIROIDIFC, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | माप (aironet_ioctl),
    IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "airoidifc" पूर्ण,
पूर्ण;

अटल स्थिर iw_handler		airo_handler[] =
अणु
	(iw_handler) airo_config_commit,	/* SIOCSIWCOMMIT */
	(iw_handler) airo_get_name,		/* SIOCGIWNAME */
	(iw_handler) शून्य,			/* SIOCSIWNWID */
	(iw_handler) शून्य,			/* SIOCGIWNWID */
	(iw_handler) airo_set_freq,		/* SIOCSIWFREQ */
	(iw_handler) airo_get_freq,		/* SIOCGIWFREQ */
	(iw_handler) airo_set_mode,		/* SIOCSIWMODE */
	(iw_handler) airo_get_mode,		/* SIOCGIWMODE */
	(iw_handler) airo_set_sens,		/* SIOCSIWSENS */
	(iw_handler) airo_get_sens,		/* SIOCGIWSENS */
	(iw_handler) शून्य,			/* SIOCSIWRANGE */
	(iw_handler) airo_get_range,		/* SIOCGIWRANGE */
	(iw_handler) शून्य,			/* SIOCSIWPRIV */
	(iw_handler) शून्य,			/* SIOCGIWPRIV */
	(iw_handler) शून्य,			/* SIOCSIWSTATS */
	(iw_handler) शून्य,			/* SIOCGIWSTATS */
	iw_handler_set_spy,			/* SIOCSIWSPY */
	iw_handler_get_spy,			/* SIOCGIWSPY */
	iw_handler_set_thrspy,			/* SIOCSIWTHRSPY */
	iw_handler_get_thrspy,			/* SIOCGIWTHRSPY */
	(iw_handler) airo_set_wap,		/* SIOCSIWAP */
	(iw_handler) airo_get_wap,		/* SIOCGIWAP */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) airo_get_aplist,		/* SIOCGIWAPLIST */
	(iw_handler) airo_set_scan,		/* SIOCSIWSCAN */
	(iw_handler) airo_get_scan,		/* SIOCGIWSCAN */
	(iw_handler) airo_set_essid,		/* SIOCSIWESSID */
	(iw_handler) airo_get_essid,		/* SIOCGIWESSID */
	(iw_handler) airo_set_nick,		/* SIOCSIWNICKN */
	(iw_handler) airo_get_nick,		/* SIOCGIWNICKN */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) airo_set_rate,		/* SIOCSIWRATE */
	(iw_handler) airo_get_rate,		/* SIOCGIWRATE */
	(iw_handler) airo_set_rts,		/* SIOCSIWRTS */
	(iw_handler) airo_get_rts,		/* SIOCGIWRTS */
	(iw_handler) airo_set_frag,		/* SIOCSIWFRAG */
	(iw_handler) airo_get_frag,		/* SIOCGIWFRAG */
	(iw_handler) airo_set_txघात,		/* SIOCSIWTXPOW */
	(iw_handler) airo_get_txघात,		/* SIOCGIWTXPOW */
	(iw_handler) airo_set_retry,		/* SIOCSIWRETRY */
	(iw_handler) airo_get_retry,		/* SIOCGIWRETRY */
	(iw_handler) airo_set_encode,		/* SIOCSIWENCODE */
	(iw_handler) airo_get_encode,		/* SIOCGIWENCODE */
	(iw_handler) airo_set_घातer,		/* SIOCSIWPOWER */
	(iw_handler) airo_get_घातer,		/* SIOCGIWPOWER */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* SIOCSIWGENIE */
	(iw_handler) शून्य,			/* SIOCGIWGENIE */
	(iw_handler) airo_set_auth,		/* SIOCSIWAUTH */
	(iw_handler) airo_get_auth,		/* SIOCGIWAUTH */
	(iw_handler) airo_set_encodeext,	/* SIOCSIWENCODEEXT */
	(iw_handler) airo_get_encodeext,	/* SIOCGIWENCODEEXT */
	(iw_handler) शून्य,			/* SIOCSIWPMKSA */
पूर्ण;

/* Note : करोn't describe AIROIDIFC and AIROOLDIDIFC in here.
 * We want to क्रमce the use of the ioctl code, because those can't be
 * won't work the iw_handler code (because they simultaneously पढ़ो
 * and ग_लिखो data and iw_handler can't करो that).
 * Note that it's perfectly legal to पढ़ो/ग_लिखो on a single ioctl command,
 * you just can't use iwpriv and need to क्रमce it via the ioctl handler.
 * Jean II */
अटल स्थिर iw_handler		airo_निजी_handler[] =
अणु
	शून्य,				/* SIOCIWFIRSTPRIV */
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def	airo_handler_def =
अणु
	.num_standard	= ARRAY_SIZE(airo_handler),
	.num_निजी	= ARRAY_SIZE(airo_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(airo_निजी_args),
	.standard	= airo_handler,
	.निजी	= airo_निजी_handler,
	.निजी_args	= airo_निजी_args,
	.get_wireless_stats = airo_get_wireless_stats,
पूर्ण;

/*
 * This defines the configuration part of the Wireless Extensions
 * Note : irq and spinlock protection will occur in the subroutines
 *
 * TODO :
 *	o Check input value more carefully and fill correct values in range
 *	o Test and shakeout the bugs (अगर any)
 *
 * Jean II
 *
 * Javier Achirica did a great job of merging code from the unnamed CISCO
 * developer that added support क्रम flashing the card.
 */
अटल पूर्णांक airo_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक rc = 0;
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर (ai->घातer.event)
		वापस 0;

	चयन (cmd) अणु
#अगर_घोषित CISCO_EXT
	हाल AIROIDIFC:
#अगर_घोषित AIROOLDIDIFC
	हाल AIROOLDIDIFC:
#पूर्ण_अगर
	अणु
		पूर्णांक val = AIROMAGIC;
		aironet_ioctl com;
		अगर (copy_from_user(&com, rq->अगरr_data, माप(com)))
			rc = -EFAULT;
		अन्यथा अगर (copy_to_user(com.data, (अक्षर *)&val, माप(val)))
			rc = -EFAULT;
	पूर्ण
	अवरोध;

	हाल AIROIOCTL:
#अगर_घोषित AIROOLDIOCTL
	हाल AIROOLDIOCTL:
#पूर्ण_अगर
		/* Get the command काष्ठा and hand it off क्रम evaluation by
		 * the proper subfunction
		 */
	अणु
		aironet_ioctl com;
		अगर (copy_from_user(&com, rq->अगरr_data, माप(com))) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण

		/* Separate R/W functions bracket legality here
		 */
		अगर (com.command == AIRORSWVERSION) अणु
			अगर (copy_to_user(com.data, swversion, माप(swversion)))
				rc = -EFAULT;
			अन्यथा
				rc = 0;
		पूर्ण
		अन्यथा अगर (com.command <= AIRORRID)
			rc = पढ़ोrids(dev,&com);
		अन्यथा अगर (com.command >= AIROPCAP && com.command <= (AIROPLEAPUSR+2))
			rc = ग_लिखोrids(dev,&com);
		अन्यथा अगर (com.command >= AIROFLSHRST && com.command <= AIRORESTART)
			rc = flashcard(dev,&com);
		अन्यथा
			rc = -EINVAL;      /* Bad command in ioctl */
	पूर्ण
	अवरोध;
#पूर्ण_अगर /* CISCO_EXT */

	// All other calls are currently unsupported
	शेष:
		rc = -EOPNOTSUPP;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Get the Wireless stats out of the driver
 * Note : irq and spinlock protection will occur in the subroutines
 *
 * TODO :
 *	o Check अगर work in Ad-Hoc mode (otherwise, use SPY, as in wvlan_cs)
 *
 * Jean
 */
अटल व्योम airo_पढ़ो_wireless_stats(काष्ठा airo_info *local)
अणु
	StatusRid status_rid;
	StatsRid stats_rid;
	CapabilityRid cap_rid;
	__le32 *vals = stats_rid.vals;

	/* Get stats out of the card */
	अगर (local->घातer.event)
		वापस;

	पढ़ोCapabilityRid(local, &cap_rid, 0);
	पढ़ोStatusRid(local, &status_rid, 0);
	पढ़ोStatsRid(local, &stats_rid, RID_STATS, 0);

	/* The status */
	local->wstats.status = le16_to_cpu(status_rid.mode);

	/* Signal quality and co */
	अगर (local->rssi) अणु
		local->wstats.qual.level =
			airo_rssi_to_dbm(local->rssi,
					 le16_to_cpu(status_rid.sigQuality));
		/* normalizedSignalStrength appears to be a percentage */
		local->wstats.qual.qual =
			le16_to_cpu(status_rid.normalizedSignalStrength);
	पूर्ण अन्यथा अणु
		local->wstats.qual.level =
			(le16_to_cpu(status_rid.normalizedSignalStrength) + 321) / 2;
		local->wstats.qual.qual = airo_get_quality(&status_rid, &cap_rid);
	पूर्ण
	अगर (le16_to_cpu(status_rid.len) >= 124) अणु
		local->wstats.qual.noise = 0x100 - status_rid.noisedBm;
		local->wstats.qual.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
	पूर्ण अन्यथा अणु
		local->wstats.qual.noise = 0;
		local->wstats.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED | IW_QUAL_NOISE_INVALID | IW_QUAL_DBM;
	पूर्ण

	/* Packets discarded in the wireless adapter due to wireless
	 * specअगरic problems */
	local->wstats.discard.nwid = le32_to_cpu(vals[56]) +
				     le32_to_cpu(vals[57]) +
				     le32_to_cpu(vals[58]); /* SSID Mismatch */
	local->wstats.discard.code = le32_to_cpu(vals[6]);/* RxWepErr */
	local->wstats.discard.fragment = le32_to_cpu(vals[30]);
	local->wstats.discard.retries = le32_to_cpu(vals[10]);
	local->wstats.discard.misc = le32_to_cpu(vals[1]) +
				     le32_to_cpu(vals[32]);
	local->wstats.miss.beacon = le32_to_cpu(vals[34]);
पूर्ण

अटल काष्ठा iw_statistics *airo_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा airo_info *local =  dev->ml_priv;

	अगर (!करोwn_पूर्णांकerruptible(&local->sem)) अणु
		airo_पढ़ो_wireless_stats(local);
		up(&local->sem);
	पूर्ण
	वापस &local->wstats;
पूर्ण

#अगर_घोषित CISCO_EXT
/*
 * This just translates from driver IOCTL codes to the command codes to
 * feed to the radio's host पूर्णांकerface. Things can be added/deleted
 * as needed.  This represents the READ side of control I/O to
 * the card
 */
अटल पूर्णांक पढ़ोrids(काष्ठा net_device *dev, aironet_ioctl *comp)
अणु
	अचिन्हित लघु ridcode;
	अचिन्हित अक्षर *iobuf;
	पूर्णांक len;
	काष्ठा airo_info *ai = dev->ml_priv;

	अगर (test_bit(FLAG_FLASHING, &ai->flags))
		वापस -EIO;

	चयन(comp->command)
	अणु
	हाल AIROGCAP:      ridcode = RID_CAPABILITIES; अवरोध;
	हाल AIROGCFG:      ridcode = RID_CONFIG;
		अगर (test_bit(FLAG_COMMIT, &ai->flags)) अणु
			disable_MAC (ai, 1);
			ग_लिखोConfigRid (ai, 1);
			enable_MAC(ai, 1);
		पूर्ण
		अवरोध;
	हाल AIROGSLIST:    ridcode = RID_SSID;         अवरोध;
	हाल AIROGVLIST:    ridcode = RID_APLIST;       अवरोध;
	हाल AIROGDRVNAM:   ridcode = RID_DRVNAME;      अवरोध;
	हाल AIROGEHTENC:   ridcode = RID_ETHERENCAP;   अवरोध;
	हाल AIROGWEPKTMP:  ridcode = RID_WEP_TEMP;	अवरोध;
	हाल AIROGWEPKNV:   ridcode = RID_WEP_PERM;	अवरोध;
	हाल AIROGSTAT:     ridcode = RID_STATUS;       अवरोध;
	हाल AIROGSTATSD32: ridcode = RID_STATSDELTA;   अवरोध;
	हाल AIROGSTATSC32: ridcode = RID_STATS;        अवरोध;
	हाल AIROGMICSTATS:
		अगर (copy_to_user(comp->data, &ai->micstats,
				 min((पूर्णांक)comp->len, (पूर्णांक)माप(ai->micstats))))
			वापस -EFAULT;
		वापस 0;
	हाल AIRORRID:      ridcode = comp->ridnum;     अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ridcode == RID_WEP_TEMP || ridcode == RID_WEP_PERM) अणु
		/* Only super-user can पढ़ो WEP keys */
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
	पूर्ण

	अगर ((iobuf = kzalloc(RIDSIZE, GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;

	PC4500_पढ़ोrid(ai, ridcode, iobuf, RIDSIZE, 1);
	/* get the count of bytes in the rid  करोcs say 1st 2 bytes is it.
	 * then वापस it to the user
	 * 9/22/2000 Honor user given length
	 */
	len = comp->len;

	अगर (copy_to_user(comp->data, iobuf, min(len, (पूर्णांक)RIDSIZE))) अणु
		kमुक्त (iobuf);
		वापस -EFAULT;
	पूर्ण
	kमुक्त (iobuf);
	वापस 0;
पूर्ण

/*
 * Danger Will Robinson ग_लिखो the rids here
 */

अटल पूर्णांक ग_लिखोrids(काष्ठा net_device *dev, aironet_ioctl *comp)
अणु
	काष्ठा airo_info *ai = dev->ml_priv;
	पूर्णांक  ridcode;
        पूर्णांक  enabled;
	पूर्णांक (*ग_लिखोr)(काष्ठा airo_info *, u16 rid, स्थिर व्योम *, पूर्णांक, पूर्णांक);
	अचिन्हित अक्षर *iobuf;

	/* Only super-user can ग_लिखो RIDs */
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (test_bit(FLAG_FLASHING, &ai->flags))
		वापस -EIO;

	ridcode = 0;
	ग_लिखोr = करो_ग_लिखोrid;

	चयन(comp->command)
	अणु
	हाल AIROPSIDS:     ridcode = RID_SSID;         अवरोध;
	हाल AIROPCAP:      ridcode = RID_CAPABILITIES; अवरोध;
	हाल AIROPAPLIST:   ridcode = RID_APLIST;       अवरोध;
	हाल AIROPCFG: ai->config.len = 0;
			    clear_bit(FLAG_COMMIT, &ai->flags);
			    ridcode = RID_CONFIG;       अवरोध;
	हाल AIROPWEPKEYNV: ridcode = RID_WEP_PERM;     अवरोध;
	हाल AIROPLEAPUSR:  ridcode = RID_LEAPUSERNAME; अवरोध;
	हाल AIROPLEAPPWD:  ridcode = RID_LEAPPASSWORD; अवरोध;
	हाल AIROPWEPKEY:   ridcode = RID_WEP_TEMP; ग_लिखोr = PC4500_ग_लिखोrid;
		अवरोध;
	हाल AIROPLEAPUSR+1: ridcode = 0xFF2A;          अवरोध;
	हाल AIROPLEAPUSR+2: ridcode = 0xFF2B;          अवरोध;

		/* this is not really a rid but a command given to the card
		 * same with MAC off
		 */
	हाल AIROPMACON:
		अगर (enable_MAC(ai, 1) != 0)
			वापस -EIO;
		वापस 0;

		/*
		 * Evidently this code in the airo driver करोes not get a symbol
		 * as disable_MAC. it's probably so लघु the compiler करोes not gen one.
		 */
	हाल AIROPMACOFF:
		disable_MAC(ai, 1);
		वापस 0;

		/* This command merely clears the counts करोes not actually store any data
		 * only पढ़ोs rid. But as it changes the cards state, I put it in the
		 * ग_लिखोrid routines.
		 */
	हाल AIROPSTCLR:
		अगर ((iobuf = kदो_स्मृति(RIDSIZE, GFP_KERNEL)) == शून्य)
			वापस -ENOMEM;

		PC4500_पढ़ोrid(ai, RID_STATSDELTACLEAR, iobuf, RIDSIZE, 1);

		enabled = ai->micstats.enabled;
		स_रखो(&ai->micstats, 0, माप(ai->micstats));
		ai->micstats.enabled = enabled;

		अगर (copy_to_user(comp->data, iobuf,
				 min((पूर्णांक)comp->len, (पूर्णांक)RIDSIZE))) अणु
			kमुक्त (iobuf);
			वापस -EFAULT;
		पूर्ण
		kमुक्त (iobuf);
		वापस 0;

	शेष:
		वापस -EOPNOTSUPP;	/* Blarg! */
	पूर्ण
	अगर (comp->len > RIDSIZE)
		वापस -EINVAL;

	अगर ((iobuf = kदो_स्मृति(RIDSIZE, GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(iobuf, comp->data, comp->len)) अणु
		kमुक्त (iobuf);
		वापस -EFAULT;
	पूर्ण

	अगर (comp->command == AIROPCFG) अणु
		ConfigRid *cfg = (ConfigRid *)iobuf;

		अगर (test_bit(FLAG_MIC_CAPABLE, &ai->flags))
			cfg->opmode |= MODE_MIC;

		अगर ((cfg->opmode & MODE_CFG_MASK) == MODE_STA_IBSS)
			set_bit (FLAG_ADHOC, &ai->flags);
		अन्यथा
			clear_bit (FLAG_ADHOC, &ai->flags);
	पूर्ण

	अगर ((*ग_लिखोr)(ai, ridcode, iobuf, comp->len, 1)) अणु
		kमुक्त (iobuf);
		वापस -EIO;
	पूर्ण
	kमुक्त (iobuf);
	वापस 0;
पूर्ण

/*****************************************************************************
 * Ancillary flash / mod functions much black magic lurkes here              *
 *****************************************************************************
 */

/*
 * Flash command चयन table
 */

अटल पूर्णांक flashcard(काष्ठा net_device *dev, aironet_ioctl *comp)
अणु
	पूर्णांक z;

	/* Only super-user can modअगरy flash */
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	चयन(comp->command)
	अणु
	हाल AIROFLSHRST:
		वापस cmdreset((काष्ठा airo_info *)dev->ml_priv);

	हाल AIROFLSHSTFL:
		अगर (!AIRO_FLASH(dev) &&
		    (AIRO_FLASH(dev) = kदो_स्मृति(FLASHSIZE, GFP_KERNEL)) == शून्य)
			वापस -ENOMEM;
		वापस setflashmode((काष्ठा airo_info *)dev->ml_priv);

	हाल AIROFLSHGCHR: /* Get अक्षर from aux */
		अगर (comp->len != माप(पूर्णांक))
			वापस -EINVAL;
		अगर (copy_from_user(&z, comp->data, comp->len))
			वापस -EFAULT;
		वापस flashgअक्षर((काष्ठा airo_info *)dev->ml_priv, z, 8000);

	हाल AIROFLSHPCHR: /* Send अक्षर to card. */
		अगर (comp->len != माप(पूर्णांक))
			वापस -EINVAL;
		अगर (copy_from_user(&z, comp->data, comp->len))
			वापस -EFAULT;
		वापस flashpअक्षर((काष्ठा airo_info *)dev->ml_priv, z, 8000);

	हाल AIROFLPUTBUF: /* Send 32k to card */
		अगर (!AIRO_FLASH(dev))
			वापस -ENOMEM;
		अगर (comp->len > FLASHSIZE)
			वापस -EINVAL;
		अगर (copy_from_user(AIRO_FLASH(dev), comp->data, comp->len))
			वापस -EFAULT;

		flashputbuf((काष्ठा airo_info *)dev->ml_priv);
		वापस 0;

	हाल AIRORESTART:
		अगर (flashrestart((काष्ठा airo_info *)dev->ml_priv, dev))
			वापस -EIO;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा FLASH_COMMAND  0x7e7e

/*
 * STEP 1)
 * Disable MAC and करो soft reset on
 * card.
 */

अटल पूर्णांक cmdreset(काष्ठा airo_info *ai)
अणु
	disable_MAC(ai, 1);

	अगर (!रुकोbusy (ai)) अणु
		airo_prपूर्णांक_info(ai->dev->name, "Waitbusy hang before RESET");
		वापस -EBUSY;
	पूर्ण

	OUT4500(ai, COMMAND, CMD_SOFTRESET);

	ssleep(1);			/* WAS 600 12/7/00 */

	अगर (!रुकोbusy (ai)) अणु
		airo_prपूर्णांक_info(ai->dev->name, "Waitbusy hang AFTER RESET");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/* STEP 2)
 * Put the card in legendary flash
 * mode
 */

अटल पूर्णांक setflashmode (काष्ठा airo_info *ai)
अणु
	set_bit (FLAG_FLASHING, &ai->flags);

	OUT4500(ai, SWS0, FLASH_COMMAND);
	OUT4500(ai, SWS1, FLASH_COMMAND);
	अगर (probe) अणु
		OUT4500(ai, SWS0, FLASH_COMMAND);
		OUT4500(ai, COMMAND, 0x10);
	पूर्ण अन्यथा अणु
		OUT4500(ai, SWS2, FLASH_COMMAND);
		OUT4500(ai, SWS3, FLASH_COMMAND);
		OUT4500(ai, COMMAND, 0);
	पूर्ण
	msleep(500);		/* 500ms delay */

	अगर (!रुकोbusy(ai)) अणु
		clear_bit (FLAG_FLASHING, &ai->flags);
		airo_prपूर्णांक_info(ai->dev->name, "Waitbusy hang after setflash mode");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Put अक्षरacter to SWS0 रुको क्रम dwellसमय
 * x 50us क्रम  echo .
 */

अटल पूर्णांक flashpअक्षर(काष्ठा airo_info *ai, पूर्णांक byte, पूर्णांक dwellसमय)
अणु
	पूर्णांक echo;
	पूर्णांक रुकोसमय;

	byte |= 0x8000;

	अगर (dwellसमय == 0)
		dwellसमय = 200;

	रुकोसमय = dwellसमय;

	/* Wait क्रम busy bit d15 to go false indicating buffer empty */
	जबतक ((IN4500 (ai, SWS0) & 0x8000) && रुकोसमय > 0) अणु
		udelay (50);
		रुकोसमय -= 50;
	पूर्ण

	/* समयout क्रम busy clear रुको */
	अगर (रुकोसमय <= 0) अणु
		airo_prपूर्णांक_info(ai->dev->name, "flash putchar busywait timeout!");
		वापस -EBUSY;
	पूर्ण

	/* Port is clear now ग_लिखो byte and रुको क्रम it to echo back */
	करो अणु
		OUT4500(ai, SWS0, byte);
		udelay(50);
		dwellसमय -= 50;
		echo = IN4500(ai, SWS1);
	पूर्ण जबतक (dwellसमय >= 0 && echo != byte);

	OUT4500(ai, SWS1, 0);

	वापस (echo == byte) ? 0 : -EIO;
पूर्ण

/*
 * Get a अक्षरacter from the card matching matchbyte
 * Step 3)
 */
अटल पूर्णांक flashgअक्षर(काष्ठा airo_info *ai, पूर्णांक matchbyte, पूर्णांक dwellसमय)
अणु
	पूर्णांक           rअक्षर;
	अचिन्हित अक्षर rbyte = 0;

	करो अणु
		rअक्षर = IN4500(ai, SWS1);

		अगर (dwellसमय && !(0x8000 & rअक्षर)) अणु
			dwellसमय -= 10;
			mdelay(10);
			जारी;
		पूर्ण
		rbyte = 0xff & rअक्षर;

		अगर ((rbyte == matchbyte) && (0x8000 & rअक्षर)) अणु
			OUT4500(ai, SWS1, 0);
			वापस 0;
		पूर्ण
		अगर (rbyte == 0x81 || rbyte == 0x82 || rbyte == 0x83 || rbyte == 0x1a || 0xffff == rअक्षर)
			अवरोध;
		OUT4500(ai, SWS1, 0);

	पूर्ण जबतक (dwellसमय > 0);
	वापस -EIO;
पूर्ण

/*
 * Transfer 32k of firmware data from user buffer to our buffer and
 * send to the card
 */

अटल पूर्णांक flashputbuf(काष्ठा airo_info *ai)
अणु
	पूर्णांक            nwords;

	/* Write stuff */
	अगर (test_bit(FLAG_MPI,&ai->flags))
		स_नकल_toio(ai->pciaux + 0x8000, ai->flash, FLASHSIZE);
	अन्यथा अणु
		OUT4500(ai, AUXPAGE, 0x100);
		OUT4500(ai, AUXOFF, 0);

		क्रम (nwords = 0; nwords != FLASHSIZE / 2; nwords++) अणु
			OUT4500(ai, AUXDATA, ai->flash[nwords] & 0xffff);
		पूर्ण
	पूर्ण
	OUT4500(ai, SWS0, 0x8000);

	वापस 0;
पूर्ण

/*
 *
 */
अटल पूर्णांक flashrestart(काष्ठा airo_info *ai, काष्ठा net_device *dev)
अणु
	पूर्णांक    i, status;

	ssleep(1);			/* Added 12/7/00 */
	clear_bit (FLAG_FLASHING, &ai->flags);
	अगर (test_bit(FLAG_MPI, &ai->flags)) अणु
		status = mpi_init_descriptors(ai);
		अगर (status != SUCCESS)
			वापस status;
	पूर्ण
	status = setup_card(ai, dev->dev_addr, 1);

	अगर (!test_bit(FLAG_MPI,&ai->flags))
		क्रम (i = 0; i < MAX_FIDS; i++) अणु
			ai->fids[i] = transmit_allocate
				(ai, AIRO_DEF_MTU, i >= MAX_FIDS / 2);
		पूर्ण

	ssleep(1);			/* Added 12/7/00 */
	वापस status;
पूर्ण
#पूर्ण_अगर /* CISCO_EXT */

/*
    This program is मुक्त software; you can redistribute it and/or
    modअगरy it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    In addition:

    Redistribution and use in source and binary क्रमms, with or without
    modअगरication, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary क्रमm must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       करोcumentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to enकरोrse or promote
       products derived from this software without specअगरic prior written
       permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
    INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

module_init(airo_init_module);
module_निकास(airo_cleanup_module);
