<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-2-Clause)
/*
 * Copyright (c) 2003, 2004
 *	Damien Bergamini <damien.bergamini@मुक्त.fr>. All rights reserved.
 *
 * Copyright (c) 2005-2007 Matthieu Castet <castet.matthieu@मुक्त.fr>
 * Copyright (c) 2005-2007 Stanislaw Gruszka <stf_xl@wp.pl>
 *
 * HISTORY : some part of the code was base on ueagle 1.3 BSD driver,
 * Damien Bergamini agree to put his code under a DUAL GPL/BSD license.
 *
 * The rest of the code was was rewritten from scratch.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "usbatm.h"

#घोषणा EAGLEUSBVERSION "ueagle 1.4"


/*
 * Debug macros
 */
#घोषणा uea_dbg(usb_dev, क्रमmat, args...)	\
	करो अणु \
		अगर (debug >= 1) \
			dev_dbg(&(usb_dev)->dev, \
				"[ueagle-atm dbg] %s: " क्रमmat, \
					__func__, ##args); \
	पूर्ण जबतक (0)

#घोषणा uea_vdbg(usb_dev, क्रमmat, args...)	\
	करो अणु \
		अगर (debug >= 2) \
			dev_dbg(&(usb_dev)->dev, \
				"[ueagle-atm vdbg]  " क्रमmat, ##args); \
	पूर्ण जबतक (0)

#घोषणा uea_enters(usb_dev) \
	uea_vdbg(usb_dev, "entering %s\n" , __func__)

#घोषणा uea_leaves(usb_dev) \
	uea_vdbg(usb_dev, "leaving  %s\n" , __func__)

#घोषणा uea_err(usb_dev, क्रमmat, args...) \
	dev_err(&(usb_dev)->dev , "[UEAGLE-ATM] " क्रमmat , ##args)

#घोषणा uea_warn(usb_dev, क्रमmat, args...) \
	dev_warn(&(usb_dev)->dev , "[Ueagle-atm] " क्रमmat, ##args)

#घोषणा uea_info(usb_dev, क्रमmat, args...) \
	dev_info(&(usb_dev)->dev , "[ueagle-atm] " क्रमmat, ##args)

काष्ठा पूर्णांकr_pkt;

/* cmv's from firmware */
काष्ठा uea_cmvs_v1 अणु
	u32 address;
	u16 offset;
	u32 data;
पूर्ण __packed;

काष्ठा uea_cmvs_v2 अणु
	u32 group;
	u32 address;
	u32 offset;
	u32 data;
पूर्ण __packed;

/* inक्रमmation about currently processed cmv */
काष्ठा cmv_dsc_e1 अणु
	u8 function;
	u16 idx;
	u32 address;
	u16 offset;
पूर्ण;

काष्ठा cmv_dsc_e4 अणु
	u16 function;
	u16 offset;
	u16 address;
	u16 group;
पूर्ण;

जोड़ cmv_dsc अणु
	काष्ठा cmv_dsc_e1 e1;
	काष्ठा cmv_dsc_e4 e4;
पूर्ण;

काष्ठा uea_softc अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा usbaपंचांग_data *usbaपंचांग;

	पूर्णांक modem_index;
	अचिन्हित पूर्णांक driver_info;
	पूर्णांक annex;
#घोषणा ANNEXA 0
#घोषणा ANNEXB 1

	पूर्णांक booting;
	पूर्णांक reset;

	रुको_queue_head_t sync_q;

	काष्ठा task_काष्ठा *kthपढ़ो;
	u32 data;
	u32 data1;

	पूर्णांक cmv_ack;
	जोड़ cmv_dsc cmv_dsc;

	काष्ठा work_काष्ठा task;
	u16 pageno;
	u16 ovl;

	स्थिर काष्ठा firmware *dsp_firm;
	काष्ठा urb *urb_पूर्णांक;

	व्योम (*dispatch_cmv)(काष्ठा uea_softc *, काष्ठा पूर्णांकr_pkt *);
	व्योम (*schedule_load_page)(काष्ठा uea_softc *, काष्ठा पूर्णांकr_pkt *);
	पूर्णांक (*stat)(काष्ठा uea_softc *);
	पूर्णांक (*send_cmvs)(काष्ठा uea_softc *);

	/* keep in sync with eaglectl */
	काष्ठा uea_stats अणु
		काष्ठा अणु
			u32 state;
			u32 flags;
			u32 mflags;
			u32 vidcpe;
			u32 vidco;
			u32 dsrate;
			u32 usrate;
			u32 dsunc;
			u32 usunc;
			u32 dscorr;
			u32 uscorr;
			u32 txflow;
			u32 rxflow;
			u32 usattenuation;
			u32 dsattenuation;
			u32 dsmargin;
			u32 usmargin;
			u32 firmid;
		पूर्ण phy;
	पूर्ण stats;
पूर्ण;

/*
 * Elsa IDs
 */
#घोषणा ELSA_VID		0x05CC
#घोषणा ELSA_PID_PSTFIRM	0x3350
#घोषणा ELSA_PID_PREFIRM	0x3351

#घोषणा ELSA_PID_A_PREFIRM	0x3352
#घोषणा ELSA_PID_A_PSTFIRM	0x3353
#घोषणा ELSA_PID_B_PREFIRM	0x3362
#घोषणा ELSA_PID_B_PSTFIRM	0x3363

/*
 * Devolo IDs : pots अगर (pid & 0x10)
 */
#घोषणा DEVOLO_VID			0x1039
#घोषणा DEVOLO_EAGLE_I_A_PID_PSTFIRM	0x2110
#घोषणा DEVOLO_EAGLE_I_A_PID_PREFIRM	0x2111

#घोषणा DEVOLO_EAGLE_I_B_PID_PSTFIRM	0x2100
#घोषणा DEVOLO_EAGLE_I_B_PID_PREFIRM	0x2101

#घोषणा DEVOLO_EAGLE_II_A_PID_PSTFIRM	0x2130
#घोषणा DEVOLO_EAGLE_II_A_PID_PREFIRM	0x2131

#घोषणा DEVOLO_EAGLE_II_B_PID_PSTFIRM	0x2120
#घोषणा DEVOLO_EAGLE_II_B_PID_PREFIRM	0x2121

/*
 * Reference design USB IDs
 */
#घोषणा ANALOG_VID		0x1110
#घोषणा ADI930_PID_PREFIRM	0x9001
#घोषणा ADI930_PID_PSTFIRM	0x9000

#घोषणा EAGLE_I_PID_PREFIRM	0x9010	/* Eagle I */
#घोषणा EAGLE_I_PID_PSTFIRM	0x900F	/* Eagle I */

#घोषणा EAGLE_IIC_PID_PREFIRM	0x9024	/* Eagle IIC */
#घोषणा EAGLE_IIC_PID_PSTFIRM	0x9023	/* Eagle IIC */

#घोषणा EAGLE_II_PID_PREFIRM	0x9022	/* Eagle II */
#घोषणा EAGLE_II_PID_PSTFIRM	0x9021	/* Eagle II */

#घोषणा EAGLE_III_PID_PREFIRM	0x9032	/* Eagle III */
#घोषणा EAGLE_III_PID_PSTFIRM	0x9031	/* Eagle III */

#घोषणा EAGLE_IV_PID_PREFIRM	0x9042  /* Eagle IV */
#घोषणा EAGLE_IV_PID_PSTFIRM	0x9041  /* Eagle IV */

/*
 * USR USB IDs
 */
#घोषणा USR_VID			0x0BAF
#घोषणा MILLER_A_PID_PREFIRM	0x00F2
#घोषणा MILLER_A_PID_PSTFIRM	0x00F1
#घोषणा MILLER_B_PID_PREFIRM	0x00FA
#घोषणा MILLER_B_PID_PSTFIRM	0x00F9
#घोषणा HEINEKEN_A_PID_PREFIRM	0x00F6
#घोषणा HEINEKEN_A_PID_PSTFIRM	0x00F5
#घोषणा HEINEKEN_B_PID_PREFIRM	0x00F8
#घोषणा HEINEKEN_B_PID_PSTFIRM	0x00F7

#घोषणा PREFIRM 0
#घोषणा PSTFIRM (1<<7)
#घोषणा AUTO_ANNEX_A (1<<8)
#घोषणा AUTO_ANNEX_B (1<<9)

क्रमागत अणु
	ADI930 = 0,
	EAGLE_I,
	EAGLE_II,
	EAGLE_III,
	EAGLE_IV
पूर्ण;

/* macros क्रम both काष्ठा usb_device_id and काष्ठा uea_softc */
#घोषणा UEA_IS_PREFIRM(x) \
	(!((x)->driver_info & PSTFIRM))
#घोषणा UEA_CHIP_VERSION(x) \
	((x)->driver_info & 0xf)

#घोषणा IS_ISDN(x) \
	((x)->annex & ANNEXB)

#घोषणा INS_TO_USBDEV(ins) (ins->usb_dev)

#घोषणा GET_STATUS(data) \
	((data >> 8) & 0xf)

#घोषणा IS_OPERATIONAL(sc) \
	((UEA_CHIP_VERSION(sc) != EAGLE_IV) ? \
	(GET_STATUS(sc->stats.phy.state) == 2) : \
	(sc->stats.phy.state == 7))

/*
 * Set of macros to handle unaligned data in the firmware blob.
 * The FW_GET_BYTE() macro is provided only क्रम consistency.
 */

#घोषणा FW_GET_BYTE(p) (*((__u8 *) (p)))

#घोषणा FW_सूची "ueagle-atm/"
#घोषणा EAGLE_FIRMWARE FW_सूची "eagle.fw"
#घोषणा ADI930_FIRMWARE FW_सूची "adi930.fw"
#घोषणा EAGLE_I_FIRMWARE FW_सूची "eagleI.fw"
#घोषणा EAGLE_II_FIRMWARE FW_सूची "eagleII.fw"
#घोषणा EAGLE_III_FIRMWARE FW_सूची "eagleIII.fw"
#घोषणा EAGLE_IV_FIRMWARE FW_सूची "eagleIV.fw"

#घोषणा DSP4I_FIRMWARE FW_सूची "DSP4i.bin"
#घोषणा DSP4P_FIRMWARE FW_सूची "DSP4p.bin"
#घोषणा DSP9I_FIRMWARE FW_सूची "DSP9i.bin"
#घोषणा DSP9P_FIRMWARE FW_सूची "DSP9p.bin"
#घोषणा DSPEI_FIRMWARE FW_सूची "DSPei.bin"
#घोषणा DSPEP_FIRMWARE FW_सूची "DSPep.bin"
#घोषणा FPGA930_FIRMWARE FW_सूची "930-fpga.bin"

#घोषणा CMV4P_FIRMWARE FW_सूची "CMV4p.bin"
#घोषणा CMV4PV2_FIRMWARE FW_सूची "CMV4p.bin.v2"
#घोषणा CMV4I_FIRMWARE FW_सूची "CMV4i.bin"
#घोषणा CMV4IV2_FIRMWARE FW_सूची "CMV4i.bin.v2"
#घोषणा CMV9P_FIRMWARE FW_सूची "CMV9p.bin"
#घोषणा CMV9PV2_FIRMWARE FW_सूची "CMV9p.bin.v2"
#घोषणा CMV9I_FIRMWARE FW_सूची "CMV9i.bin"
#घोषणा CMV9IV2_FIRMWARE FW_सूची "CMV9i.bin.v2"
#घोषणा CMVEP_FIRMWARE FW_सूची "CMVep.bin"
#घोषणा CMVEPV2_FIRMWARE FW_सूची "CMVep.bin.v2"
#घोषणा CMVEI_FIRMWARE FW_सूची "CMVei.bin"
#घोषणा CMVEIV2_FIRMWARE FW_सूची "CMVei.bin.v2"

#घोषणा UEA_FW_NAME_MAX 30
#घोषणा NB_MODEM 4

#घोषणा BULK_TIMEOUT 300
#घोषणा CTRL_TIMEOUT 1000

#घोषणा ACK_TIMEOUT msecs_to_jअगरfies(3000)

#घोषणा UEA_INTR_IFACE_NO	0
#घोषणा UEA_US_IFACE_NO		1
#घोषणा UEA_DS_IFACE_NO		2

#घोषणा FASTEST_ISO_INTF	8

#घोषणा UEA_BULK_DATA_PIPE	0x02
#घोषणा UEA_IDMA_PIPE		0x04
#घोषणा UEA_INTR_PIPE		0x04
#घोषणा UEA_ISO_DATA_PIPE	0x08

#घोषणा UEA_E1_SET_BLOCK	0x0001
#घोषणा UEA_E4_SET_BLOCK	0x002c
#घोषणा UEA_SET_MODE		0x0003
#घोषणा UEA_SET_2183_DATA	0x0004
#घोषणा UEA_SET_TIMEOUT		0x0011

#घोषणा UEA_LOOPBACK_OFF	0x0002
#घोषणा UEA_LOOPBACK_ON		0x0003
#घोषणा UEA_BOOT_IDMA		0x0006
#घोषणा UEA_START_RESET		0x0007
#घोषणा UEA_END_RESET		0x0008

#घोषणा UEA_SWAP_MAILBOX	(0x3fcd | 0x4000)
#घोषणा UEA_MPTX_START		(0x3fce | 0x4000)
#घोषणा UEA_MPTX_MAILBOX	(0x3fd6 | 0x4000)
#घोषणा UEA_MPRX_MAILBOX	(0x3fdf | 0x4000)

/* block inक्रमmation in eagle4 dsp firmware  */
काष्ठा block_index अणु
	__le32 PageOffset;
	__le32 NotLastBlock;
	__le32 dummy;
	__le32 PageSize;
	__le32 PageAddress;
	__le16 dummy1;
	__le16 PageNumber;
पूर्ण __packed;

#घोषणा E4_IS_BOOT_PAGE(PageSize) ((le32_to_cpu(PageSize)) & 0x80000000)
#घोषणा E4_PAGE_BYTES(PageSize) ((le32_to_cpu(PageSize) & 0x7fffffff) * 4)

#घोषणा E4_L1_STRING_HEADER 0x10
#घोषणा E4_MAX_PAGE_NUMBER 0x58
#घोषणा E4_NO_SWAPPAGE_HEADERS 0x31

/* l1_code is eagle4 dsp firmware क्रमmat */
काष्ठा l1_code अणु
	u8 string_header[E4_L1_STRING_HEADER];
	u8 page_number_to_block_index[E4_MAX_PAGE_NUMBER];
	काष्ठा block_index page_header[E4_NO_SWAPPAGE_HEADERS];
	u8 code[];
पूर्ण __packed;

/* काष्ठाures describing a block within a DSP page */
काष्ठा block_info_e1 अणु
	__le16 wHdr;
	__le16 wAddress;
	__le16 wSize;
	__le16 wOvlOffset;
	__le16 wOvl;		/* overlay */
	__le16 wLast;
पूर्ण __packed;
#घोषणा E1_BLOCK_INFO_SIZE 12

काष्ठा block_info_e4 अणु
	__be16 wHdr;
	__u8 bBootPage;
	__u8 bPageNumber;
	__be32 dwSize;
	__be32 dwAddress;
	__be16 wReserved;
पूर्ण __packed;
#घोषणा E4_BLOCK_INFO_SIZE 14

#घोषणा UEA_BIHDR 0xabcd
#घोषणा UEA_RESERVED 0xffff

/* स्थिरants describing cmv type */
#घोषणा E1_PREAMBLE 0x535c
#घोषणा E1_MODEMTOHOST 0x01
#घोषणा E1_HOSTTOMODEM 0x10

#घोषणा E1_MEMACCESS 0x1
#घोषणा E1_ADSLसूचीECTIVE 0x7
#घोषणा E1_FUNCTION_TYPE(f) ((f) >> 4)
#घोषणा E1_FUNCTION_SUBTYPE(f) ((f) & 0x0f)

#घोषणा E4_MEMACCESS 0
#घोषणा E4_ADSLसूचीECTIVE 0xf
#घोषणा E4_FUNCTION_TYPE(f) ((f) >> 8)
#घोषणा E4_FUNCTION_SIZE(f) ((f) & 0x0f)
#घोषणा E4_FUNCTION_SUBTYPE(f) (((f) >> 4) & 0x0f)

/* क्रम MEMACCESS */
#घोषणा E1_REQUESTREAD	0x0
#घोषणा E1_REQUESTWRITE	0x1
#घोषणा E1_REPLYREAD	0x2
#घोषणा E1_REPLYWRITE	0x3

#घोषणा E4_REQUESTREAD	0x0
#घोषणा E4_REQUESTWRITE	0x4
#घोषणा E4_REPLYREAD	(E4_REQUESTREAD | 1)
#घोषणा E4_REPLYWRITE	(E4_REQUESTWRITE | 1)

/* क्रम ADSLसूचीECTIVE */
#घोषणा E1_KERNELREADY 0x0
#घोषणा E1_MODEMREADY  0x1

#घोषणा E4_KERNELREADY 0x0
#घोषणा E4_MODEMREADY  0x1

#घोषणा E1_MAKEFUNCTION(t, s) (((t) & 0xf) << 4 | ((s) & 0xf))
#घोषणा E4_MAKEFUNCTION(t, st, s) (((t) & 0xf) << 8 | \
	((st) & 0xf) << 4 | ((s) & 0xf))

#घोषणा E1_MAKESA(a, b, c, d)						\
	(((c) & 0xff) << 24 |						\
	 ((d) & 0xff) << 16 |						\
	 ((a) & 0xff) << 8  |						\
	 ((b) & 0xff))

#घोषणा E1_GETSA1(a) ((a >> 8) & 0xff)
#घोषणा E1_GETSA2(a) (a & 0xff)
#घोषणा E1_GETSA3(a) ((a >> 24) & 0xff)
#घोषणा E1_GETSA4(a) ((a >> 16) & 0xff)

#घोषणा E1_SA_CNTL E1_MAKESA('C', 'N', 'T', 'L')
#घोषणा E1_SA_DIAG E1_MAKESA('D', 'I', 'A', 'G')
#घोषणा E1_SA_INFO E1_MAKESA('I', 'N', 'F', 'O')
#घोषणा E1_SA_OPTN E1_MAKESA('O', 'P', 'T', 'N')
#घोषणा E1_SA_RATE E1_MAKESA('R', 'A', 'T', 'E')
#घोषणा E1_SA_STAT E1_MAKESA('S', 'T', 'A', 'T')

#घोषणा E4_SA_CNTL 1
#घोषणा E4_SA_STAT 2
#घोषणा E4_SA_INFO 3
#घोषणा E4_SA_TEST 4
#घोषणा E4_SA_OPTN 5
#घोषणा E4_SA_RATE 6
#घोषणा E4_SA_DIAG 7
#घोषणा E4_SA_CNFG 8

/* काष्ठाures representing a CMV (Configuration and Management Variable) */
काष्ठा cmv_e1 अणु
	__le16 wPreamble;
	__u8 bDirection;
	__u8 bFunction;
	__le16 wIndex;
	__le32 dwSymbolicAddress;
	__le16 wOffsetAddress;
	__le32 dwData;
पूर्ण __packed;

काष्ठा cmv_e4 अणु
	__be16 wGroup;
	__be16 wFunction;
	__be16 wOffset;
	__be16 wAddress;
	__be32 dwData[6];
पूर्ण __packed;

/* काष्ठाures representing swap inक्रमmation */
काष्ठा swap_info_e1 अणु
	__u8 bSwapPageNo;
	__u8 bOvl;		/* overlay */
पूर्ण __packed;

काष्ठा swap_info_e4 अणु
	__u8 bSwapPageNo;
पूर्ण __packed;

/* काष्ठाures representing पूर्णांकerrupt data */
#घोषणा e1_bSwapPageNo	u.e1.s1.swapinfo.bSwapPageNo
#घोषणा e1_bOvl		u.e1.s1.swapinfo.bOvl
#घोषणा e4_bSwapPageNo  u.e4.s1.swapinfo.bSwapPageNo

#घोषणा INT_LOADSWAPPAGE 0x0001
#घोषणा INT_INCOMINGCMV  0x0002

जोड़ पूर्णांकr_data_e1 अणु
	काष्ठा अणु
		काष्ठा swap_info_e1 swapinfo;
		__le16 wDataSize;
	पूर्ण __packed s1;
	काष्ठा अणु
		काष्ठा cmv_e1 cmv;
		__le16 wDataSize;
	पूर्ण __packed s2;
पूर्ण __packed;

जोड़ पूर्णांकr_data_e4 अणु
	काष्ठा अणु
		काष्ठा swap_info_e4 swapinfo;
		__le16 wDataSize;
	पूर्ण __packed s1;
	काष्ठा अणु
		काष्ठा cmv_e4 cmv;
		__le16 wDataSize;
	पूर्ण __packed s2;
पूर्ण __packed;

काष्ठा पूर्णांकr_pkt अणु
	__u8 bType;
	__u8 bNotअगरication;
	__le16 wValue;
	__le16 wIndex;
	__le16 wLength;
	__le16 wInterrupt;
	जोड़ अणु
		जोड़ पूर्णांकr_data_e1 e1;
		जोड़ पूर्णांकr_data_e4 e4;
	पूर्ण u;
पूर्ण __packed;

#घोषणा E1_INTR_PKT_SIZE 28
#घोषणा E4_INTR_PKT_SIZE 64

अटल काष्ठा usb_driver uea_driver;
अटल DEFINE_MUTEX(uea_mutex);
अटल स्थिर अक्षर * स्थिर chip_name[] = अणु
	"ADI930", "Eagle I", "Eagle II", "Eagle III", "Eagle IV"पूर्ण;

अटल पूर्णांक modem_index;
अटल अचिन्हित पूर्णांक debug;
अटल अचिन्हित पूर्णांक altsetting[NB_MODEM] = अणु
				[0 ... (NB_MODEM - 1)] = FASTEST_ISO_INTFपूर्ण;
अटल bool sync_रुको[NB_MODEM];
अटल अक्षर *cmv_file[NB_MODEM];
अटल पूर्णांक annex[NB_MODEM];

module_param(debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "module debug level (0=off,1=on,2=verbose)");
module_param_array(altsetting, uपूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(altsetting, "alternate setting for incoming traffic: 0=bulk, "
			     "1=isoc slowest, ... , 8=isoc fastest (default)");
module_param_array(sync_रुको, bool, शून्य, 0644);
MODULE_PARM_DESC(sync_रुको, "wait the synchronisation before starting ATM");
module_param_array(cmv_file, अक्षरp, शून्य, 0644);
MODULE_PARM_DESC(cmv_file,
		"file name with configuration and management variables");
module_param_array(annex, uपूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(annex,
		"manually set annex a/b (0=auto, 1=annex a, 2=annex b)");

#घोषणा uea_रुको(sc, cond, समयo) \
(अणु \
	पूर्णांक _r = रुको_event_पूर्णांकerruptible_समयout(sc->sync_q, \
			(cond) || kthपढ़ो_should_stop(), समयo); \
	अगर (kthपढ़ो_should_stop()) \
		_r = -ENODEV; \
	_r; \
पूर्ण)

#घोषणा UPDATE_ATM_STAT(type, val) \
	करो अणु \
		अगर (sc->usbaपंचांग->aपंचांग_dev) \
			sc->usbaपंचांग->aपंचांग_dev->type = val; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_ATM_SIGNAL(val) \
	करो अणु \
		अगर (sc->usbaपंचांग->aपंचांग_dev) \
			aपंचांग_dev_संकेत_change(sc->usbaपंचांग->aपंचांग_dev, val); \
	पूर्ण जबतक (0)


/* Firmware loading */
#घोषणा LOAD_INTERNAL     0xA0
#घोषणा F8051_USBCS       0x7f92

/*
 * uea_send_modem_cmd - Send a command क्रम pre-firmware devices.
 */
अटल पूर्णांक uea_send_modem_cmd(काष्ठा usb_device *usb,
			      u16 addr, u16 size, स्थिर u8 *buff)
अणु
	पूर्णांक ret = -ENOMEM;
	u8 *xfer_buff;

	xfer_buff = kmemdup(buff, size, GFP_KERNEL);
	अगर (xfer_buff) अणु
		ret = usb_control_msg(usb,
				      usb_sndctrlpipe(usb, 0),
				      LOAD_INTERNAL,
				      USB_सूची_OUT | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE, addr, 0, xfer_buff,
				      size, CTRL_TIMEOUT);
		kमुक्त(xfer_buff);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस (ret == size) ? 0 : -EIO;
पूर्ण

अटल व्योम uea_upload_pre_firmware(स्थिर काष्ठा firmware *fw_entry,
								व्योम *context)
अणु
	काष्ठा usb_device *usb = context;
	स्थिर u8 *pfw;
	u8 value;
	u32 crc = 0;
	पूर्णांक ret, size;

	uea_enters(usb);
	अगर (!fw_entry) अणु
		uea_err(usb, "firmware is not available\n");
		जाओ err;
	पूर्ण

	pfw = fw_entry->data;
	size = fw_entry->size;
	अगर (size < 4)
		जाओ err_fw_corrupted;

	crc = get_unaligned_le32(pfw);
	pfw += 4;
	size -= 4;
	अगर (crc32_be(0, pfw, size) != crc)
		जाओ err_fw_corrupted;

	/*
	 * Start to upload firmware : send reset
	 */
	value = 1;
	ret = uea_send_modem_cmd(usb, F8051_USBCS, माप(value), &value);

	अगर (ret < 0) अणु
		uea_err(usb, "modem reset failed with error %d\n", ret);
		जाओ err;
	पूर्ण

	जबतक (size > 3) अणु
		u8 len = FW_GET_BYTE(pfw);
		u16 add = get_unaligned_le16(pfw + 1);

		size -= len + 3;
		अगर (size < 0)
			जाओ err_fw_corrupted;

		ret = uea_send_modem_cmd(usb, add, len, pfw + 3);
		अगर (ret < 0) अणु
			uea_err(usb, "uploading firmware data failed "
					"with error %d\n", ret);
			जाओ err;
		पूर्ण
		pfw += len + 3;
	पूर्ण

	अगर (size != 0)
		जाओ err_fw_corrupted;

	/*
	 * Tell the modem we finish : de-निश्चित reset
	 */
	value = 0;
	ret = uea_send_modem_cmd(usb, F8051_USBCS, 1, &value);
	अगर (ret < 0)
		uea_err(usb, "modem de-assert failed with error %d\n", ret);
	अन्यथा
		uea_info(usb, "firmware uploaded\n");

	जाओ err;

err_fw_corrupted:
	uea_err(usb, "firmware is corrupted\n");
err:
	release_firmware(fw_entry);
	uea_leaves(usb);
पूर्ण

/*
 * uea_load_firmware - Load usb firmware क्रम pre-firmware devices.
 */
अटल पूर्णांक uea_load_firmware(काष्ठा usb_device *usb, अचिन्हित पूर्णांक ver)
अणु
	पूर्णांक ret;
	अक्षर *fw_name = EAGLE_FIRMWARE;

	uea_enters(usb);
	uea_info(usb, "pre-firmware device, uploading firmware\n");

	चयन (ver) अणु
	हाल ADI930:
		fw_name = ADI930_FIRMWARE;
		अवरोध;
	हाल EAGLE_I:
		fw_name = EAGLE_I_FIRMWARE;
		अवरोध;
	हाल EAGLE_II:
		fw_name = EAGLE_II_FIRMWARE;
		अवरोध;
	हाल EAGLE_III:
		fw_name = EAGLE_III_FIRMWARE;
		अवरोध;
	हाल EAGLE_IV:
		fw_name = EAGLE_IV_FIRMWARE;
		अवरोध;
	पूर्ण

	ret = request_firmware_noरुको(THIS_MODULE, 1, fw_name, &usb->dev,
					GFP_KERNEL, usb,
					uea_upload_pre_firmware);
	अगर (ret)
		uea_err(usb, "firmware %s is not available\n", fw_name);
	अन्यथा
		uea_info(usb, "loading firmware %s\n", fw_name);

	uea_leaves(usb);
	वापस ret;
पूर्ण

/* modem management : dsp firmware, send/पढ़ो CMV, monitoring statistic
 */

/*
 * Make sure that the DSP code provided is safe to use.
 */
अटल पूर्णांक check_dsp_e1(स्थिर u8 *dsp, अचिन्हित पूर्णांक len)
अणु
	u8 pagecount, blockcount;
	u16 blocksize;
	u32 pageoffset;
	अचिन्हित पूर्णांक i, j, p, pp;

	pagecount = FW_GET_BYTE(dsp);
	p = 1;

	/* enough space क्रम page offsets? */
	अगर (p + 4 * pagecount > len)
		वापस 1;

	क्रम (i = 0; i < pagecount; i++) अणु

		pageoffset = get_unaligned_le32(dsp + p);
		p += 4;

		अगर (pageoffset == 0)
			जारी;

		/* enough space क्रम blockcount? */
		अगर (pageoffset >= len)
			वापस 1;

		pp = pageoffset;
		blockcount = FW_GET_BYTE(dsp + pp);
		pp += 1;

		क्रम (j = 0; j < blockcount; j++) अणु

			/* enough space क्रम block header? */
			अगर (pp + 4 > len)
				वापस 1;

			pp += 2;	/* skip blockaddr */
			blocksize = get_unaligned_le16(dsp + pp);
			pp += 2;

			/* enough space क्रम block data? */
			अगर (pp + blocksize > len)
				वापस 1;

			pp += blocksize;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_dsp_e4(स्थिर u8 *dsp, पूर्णांक len)
अणु
	पूर्णांक i;
	काष्ठा l1_code *p = (काष्ठा l1_code *) dsp;
	अचिन्हित पूर्णांक sum = p->code - dsp;

	अगर (len < sum)
		वापस 1;

	अगर (म_भेद("STRATIPHY ANEXA", p->string_header) != 0 &&
	    म_भेद("STRATIPHY ANEXB", p->string_header) != 0)
		वापस 1;

	क्रम (i = 0; i < E4_MAX_PAGE_NUMBER; i++) अणु
		काष्ठा block_index *blockidx;
		u8 blockno = p->page_number_to_block_index[i];
		अगर (blockno >= E4_NO_SWAPPAGE_HEADERS)
			जारी;

		करो अणु
			u64 l;

			अगर (blockno >= E4_NO_SWAPPAGE_HEADERS)
				वापस 1;

			blockidx = &p->page_header[blockno++];
			अगर ((u8 *)(blockidx + 1) - dsp  >= len)
				वापस 1;

			अगर (le16_to_cpu(blockidx->PageNumber) != i)
				वापस 1;

			l = E4_PAGE_BYTES(blockidx->PageSize);
			sum += l;
			l += le32_to_cpu(blockidx->PageOffset);
			अगर (l > len)
				वापस 1;

		/* zero is zero regardless endianes */
		पूर्ण जबतक (blockidx->NotLastBlock);
	पूर्ण

	वापस (sum == len) ? 0 : 1;
पूर्ण

/*
 * send data to the idma pipe
 * */
अटल पूर्णांक uea_idma_ग_लिखो(काष्ठा uea_softc *sc, स्थिर व्योम *data, u32 size)
अणु
	पूर्णांक ret = -ENOMEM;
	u8 *xfer_buff;
	पूर्णांक bytes_पढ़ो;

	xfer_buff = kmemdup(data, size, GFP_KERNEL);
	अगर (!xfer_buff) अणु
		uea_err(INS_TO_USBDEV(sc), "can't allocate xfer_buff\n");
		वापस ret;
	पूर्ण

	ret = usb_bulk_msg(sc->usb_dev,
			 usb_sndbulkpipe(sc->usb_dev, UEA_IDMA_PIPE),
			 xfer_buff, size, &bytes_पढ़ो, BULK_TIMEOUT);

	kमुक्त(xfer_buff);
	अगर (ret < 0)
		वापस ret;
	अगर (size != bytes_पढ़ो) अणु
		uea_err(INS_TO_USBDEV(sc), "size != bytes_read %d %d\n", size,
		       bytes_पढ़ो);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक request_dsp(काष्ठा uea_softc *sc)
अणु
	पूर्णांक ret;
	अक्षर *dsp_name;

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV) अणु
		अगर (IS_ISDN(sc))
			dsp_name = DSP4I_FIRMWARE;
		अन्यथा
			dsp_name = DSP4P_FIRMWARE;
	पूर्ण अन्यथा अगर (UEA_CHIP_VERSION(sc) == ADI930) अणु
		अगर (IS_ISDN(sc))
			dsp_name = DSP9I_FIRMWARE;
		अन्यथा
			dsp_name = DSP9P_FIRMWARE;
	पूर्ण अन्यथा अणु
		अगर (IS_ISDN(sc))
			dsp_name = DSPEI_FIRMWARE;
		अन्यथा
			dsp_name = DSPEP_FIRMWARE;
	पूर्ण

	ret = request_firmware(&sc->dsp_firm, dsp_name, &sc->usb_dev->dev);
	अगर (ret < 0) अणु
		uea_err(INS_TO_USBDEV(sc),
		       "requesting firmware %s failed with error %d\n",
			dsp_name, ret);
		वापस ret;
	पूर्ण

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV)
		ret = check_dsp_e4(sc->dsp_firm->data, sc->dsp_firm->size);
	अन्यथा
		ret = check_dsp_e1(sc->dsp_firm->data, sc->dsp_firm->size);

	अगर (ret) अणु
		uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n",
		       dsp_name);
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = शून्य;
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The uea_load_page() function must be called within a process context
 */
अटल व्योम uea_load_page_e1(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uea_softc *sc = container_of(work, काष्ठा uea_softc, task);
	u16 pageno = sc->pageno;
	u16 ovl = sc->ovl;
	काष्ठा block_info_e1 bi;

	स्थिर u8 *p;
	u8 pagecount, blockcount;
	u16 blockaddr, blocksize;
	u32 pageoffset;
	पूर्णांक i;

	/* reload firmware when reboot start and it's loaded alपढ़ोy */
	अगर (ovl == 0 && pageno == 0) अणु
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = शून्य;
	पूर्ण

	अगर (sc->dsp_firm == शून्य && request_dsp(sc) < 0)
		वापस;

	p = sc->dsp_firm->data;
	pagecount = FW_GET_BYTE(p);
	p += 1;

	अगर (pageno >= pagecount)
		जाओ bad1;

	p += 4 * pageno;
	pageoffset = get_unaligned_le32(p);

	अगर (pageoffset == 0)
		जाओ bad1;

	p = sc->dsp_firm->data + pageoffset;
	blockcount = FW_GET_BYTE(p);
	p += 1;

	uea_dbg(INS_TO_USBDEV(sc),
	       "sending %u blocks for DSP page %u\n", blockcount, pageno);

	bi.wHdr = cpu_to_le16(UEA_BIHDR);
	bi.wOvl = cpu_to_le16(ovl);
	bi.wOvlOffset = cpu_to_le16(ovl | 0x8000);

	क्रम (i = 0; i < blockcount; i++) अणु
		blockaddr = get_unaligned_le16(p);
		p += 2;

		blocksize = get_unaligned_le16(p);
		p += 2;

		bi.wSize = cpu_to_le16(blocksize);
		bi.wAddress = cpu_to_le16(blockaddr);
		bi.wLast = cpu_to_le16((i == blockcount - 1) ? 1 : 0);

		/* send block info through the IDMA pipe */
		अगर (uea_idma_ग_लिखो(sc, &bi, E1_BLOCK_INFO_SIZE))
			जाओ bad2;

		/* send block data through the IDMA pipe */
		अगर (uea_idma_ग_लिखो(sc, p, blocksize))
			जाओ bad2;

		p += blocksize;
	पूर्ण

	वापस;

bad2:
	uea_err(INS_TO_USBDEV(sc), "sending DSP block %u failed\n", i);
	वापस;
bad1:
	uea_err(INS_TO_USBDEV(sc), "invalid DSP page %u requested\n", pageno);
पूर्ण

अटल व्योम __uea_load_page_e4(काष्ठा uea_softc *sc, u8 pageno, पूर्णांक boot)
अणु
	काष्ठा block_info_e4 bi;
	काष्ठा block_index *blockidx;
	काष्ठा l1_code *p = (काष्ठा l1_code *) sc->dsp_firm->data;
	u8 blockno = p->page_number_to_block_index[pageno];

	bi.wHdr = cpu_to_be16(UEA_BIHDR);
	bi.bBootPage = boot;
	bi.bPageNumber = pageno;
	bi.wReserved = cpu_to_be16(UEA_RESERVED);

	करो अणु
		स्थिर u8 *blockoffset;
		अचिन्हित पूर्णांक blocksize;

		blockidx = &p->page_header[blockno];
		blocksize = E4_PAGE_BYTES(blockidx->PageSize);
		blockoffset = sc->dsp_firm->data + le32_to_cpu(
							blockidx->PageOffset);

		bi.dwSize = cpu_to_be32(blocksize);
		bi.dwAddress = cpu_to_be32(le32_to_cpu(blockidx->PageAddress));

		uea_dbg(INS_TO_USBDEV(sc),
			"sending block %u for DSP page "
			"%u size %u address %x\n",
			blockno, pageno, blocksize,
			le32_to_cpu(blockidx->PageAddress));

		/* send block info through the IDMA pipe */
		अगर (uea_idma_ग_लिखो(sc, &bi, E4_BLOCK_INFO_SIZE))
			जाओ bad;

		/* send block data through the IDMA pipe */
		अगर (uea_idma_ग_लिखो(sc, blockoffset, blocksize))
			जाओ bad;

		blockno++;
	पूर्ण जबतक (blockidx->NotLastBlock);

	वापस;

bad:
	uea_err(INS_TO_USBDEV(sc), "sending DSP block %u failed\n", blockno);
	वापस;
पूर्ण

अटल व्योम uea_load_page_e4(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uea_softc *sc = container_of(work, काष्ठा uea_softc, task);
	u8 pageno = sc->pageno;
	पूर्णांक i;
	काष्ठा block_info_e4 bi;
	काष्ठा l1_code *p;

	uea_dbg(INS_TO_USBDEV(sc), "sending DSP page %u\n", pageno);

	/* reload firmware when reboot start and it's loaded alपढ़ोy */
	अगर (pageno == 0) अणु
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = शून्य;
	पूर्ण

	अगर (sc->dsp_firm == शून्य && request_dsp(sc) < 0)
		वापस;

	p = (काष्ठा l1_code *) sc->dsp_firm->data;
	अगर (pageno >= le16_to_cpu(p->page_header[0].PageNumber)) अणु
		uea_err(INS_TO_USBDEV(sc), "invalid DSP "
						"page %u requested\n", pageno);
		वापस;
	पूर्ण

	अगर (pageno != 0) अणु
		__uea_load_page_e4(sc, pageno, 0);
		वापस;
	पूर्ण

	uea_dbg(INS_TO_USBDEV(sc),
	       "sending Main DSP page %u\n", p->page_header[0].PageNumber);

	क्रम (i = 0; i < le16_to_cpu(p->page_header[0].PageNumber); i++) अणु
		अगर (E4_IS_BOOT_PAGE(p->page_header[i].PageSize))
			__uea_load_page_e4(sc, i, 1);
	पूर्ण

	uea_dbg(INS_TO_USBDEV(sc) , "sending start bi\n");

	bi.wHdr = cpu_to_be16(UEA_BIHDR);
	bi.bBootPage = 0;
	bi.bPageNumber = 0xff;
	bi.wReserved = cpu_to_be16(UEA_RESERVED);
	bi.dwSize = cpu_to_be32(E4_PAGE_BYTES(p->page_header[0].PageSize));
	bi.dwAddress = cpu_to_be32(le32_to_cpu(p->page_header[0].PageAddress));

	/* send block info through the IDMA pipe */
	अगर (uea_idma_ग_लिखो(sc, &bi, E4_BLOCK_INFO_SIZE))
		uea_err(INS_TO_USBDEV(sc), "sending DSP start bi failed\n");
पूर्ण

अटल अंतरभूत व्योम wake_up_cmv_ack(काष्ठा uea_softc *sc)
अणु
	BUG_ON(sc->cmv_ack);
	sc->cmv_ack = 1;
	wake_up(&sc->sync_q);
पूर्ण

अटल अंतरभूत पूर्णांक रुको_cmv_ack(काष्ठा uea_softc *sc)
अणु
	पूर्णांक ret = uea_रुको(sc, sc->cmv_ack , ACK_TIMEOUT);

	sc->cmv_ack = 0;

	uea_dbg(INS_TO_USBDEV(sc), "wait_event_timeout : %d ms\n",
			jअगरfies_to_msecs(ret));

	अगर (ret < 0)
		वापस ret;

	वापस (ret == 0) ? -ETIMEDOUT : 0;
पूर्ण

#घोषणा UCDC_SEND_ENCAPSULATED_COMMAND 0x00

अटल पूर्णांक uea_request(काष्ठा uea_softc *sc,
		u16 value, u16 index, u16 size, स्थिर व्योम *data)
अणु
	u8 *xfer_buff;
	पूर्णांक ret = -ENOMEM;

	xfer_buff = kmemdup(data, size, GFP_KERNEL);
	अगर (!xfer_buff) अणु
		uea_err(INS_TO_USBDEV(sc), "can't allocate xfer_buff\n");
		वापस ret;
	पूर्ण

	ret = usb_control_msg(sc->usb_dev, usb_sndctrlpipe(sc->usb_dev, 0),
			      UCDC_SEND_ENCAPSULATED_COMMAND,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      value, index, xfer_buff, size, CTRL_TIMEOUT);

	kमुक्त(xfer_buff);
	अगर (ret < 0) अणु
		uea_err(INS_TO_USBDEV(sc), "usb_control_msg error %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != size) अणु
		uea_err(INS_TO_USBDEV(sc),
		       "usb_control_msg send only %d bytes (instead of %d)\n",
		       ret, size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uea_cmv_e1(काष्ठा uea_softc *sc,
		u8 function, u32 address, u16 offset, u32 data)
अणु
	काष्ठा cmv_e1 cmv;
	पूर्णांक ret;

	uea_enters(INS_TO_USBDEV(sc));
	uea_vdbg(INS_TO_USBDEV(sc), "Function : %d-%d, Address : %c%c%c%c, "
			"offset : 0x%04x, data : 0x%08x\n",
			E1_FUNCTION_TYPE(function),
			E1_FUNCTION_SUBTYPE(function),
			E1_GETSA1(address), E1_GETSA2(address),
			E1_GETSA3(address),
			E1_GETSA4(address), offset, data);

	/* we send a request, but we expect a reply */
	sc->cmv_dsc.e1.function = function | 0x2;
	sc->cmv_dsc.e1.idx++;
	sc->cmv_dsc.e1.address = address;
	sc->cmv_dsc.e1.offset = offset;

	cmv.wPreamble = cpu_to_le16(E1_PREAMBLE);
	cmv.bDirection = E1_HOSTTOMODEM;
	cmv.bFunction = function;
	cmv.wIndex = cpu_to_le16(sc->cmv_dsc.e1.idx);
	put_unaligned_le32(address, &cmv.dwSymbolicAddress);
	cmv.wOffsetAddress = cpu_to_le16(offset);
	put_unaligned_le32(data >> 16 | data << 16, &cmv.dwData);

	ret = uea_request(sc, UEA_E1_SET_BLOCK, UEA_MPTX_START,
							माप(cmv), &cmv);
	अगर (ret < 0)
		वापस ret;
	ret = रुको_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

अटल पूर्णांक uea_cmv_e4(काष्ठा uea_softc *sc,
		u16 function, u16 group, u16 address, u16 offset, u32 data)
अणु
	काष्ठा cmv_e4 cmv;
	पूर्णांक ret;

	uea_enters(INS_TO_USBDEV(sc));
	स_रखो(&cmv, 0, माप(cmv));

	uea_vdbg(INS_TO_USBDEV(sc), "Function : %d-%d, Group : 0x%04x, "
		 "Address : 0x%04x, offset : 0x%04x, data : 0x%08x\n",
		 E4_FUNCTION_TYPE(function), E4_FUNCTION_SUBTYPE(function),
		 group, address, offset, data);

	/* we send a request, but we expect a reply */
	sc->cmv_dsc.e4.function = function | (0x1 << 4);
	sc->cmv_dsc.e4.offset = offset;
	sc->cmv_dsc.e4.address = address;
	sc->cmv_dsc.e4.group = group;

	cmv.wFunction = cpu_to_be16(function);
	cmv.wGroup = cpu_to_be16(group);
	cmv.wAddress = cpu_to_be16(address);
	cmv.wOffset = cpu_to_be16(offset);
	cmv.dwData[0] = cpu_to_be32(data);

	ret = uea_request(sc, UEA_E4_SET_BLOCK, UEA_MPTX_START,
							माप(cmv), &cmv);
	अगर (ret < 0)
		वापस ret;
	ret = रुको_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक uea_पढ़ो_cmv_e1(काष्ठा uea_softc *sc,
		u32 address, u16 offset, u32 *data)
अणु
	पूर्णांक ret = uea_cmv_e1(sc, E1_MAKEFUNCTION(E1_MEMACCESS, E1_REQUESTREAD),
			  address, offset, 0);
	अगर (ret < 0)
		uea_err(INS_TO_USBDEV(sc),
			"reading cmv failed with error %d\n", ret);
	अन्यथा
		*data = sc->data;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक uea_पढ़ो_cmv_e4(काष्ठा uea_softc *sc,
		u8 size, u16 group, u16 address, u16 offset, u32 *data)
अणु
	पूर्णांक ret = uea_cmv_e4(sc, E4_MAKEFUNCTION(E4_MEMACCESS,
							E4_REQUESTREAD, size),
			  group, address, offset, 0);
	अगर (ret < 0)
		uea_err(INS_TO_USBDEV(sc),
			"reading cmv failed with error %d\n", ret);
	अन्यथा अणु
		*data = sc->data;
		/* size is in 16-bit word quantities */
		अगर (size > 2)
			*(data + 1) = sc->data1;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक uea_ग_लिखो_cmv_e1(काष्ठा uea_softc *sc,
		u32 address, u16 offset, u32 data)
अणु
	पूर्णांक ret = uea_cmv_e1(sc, E1_MAKEFUNCTION(E1_MEMACCESS, E1_REQUESTWRITE),
			  address, offset, data);
	अगर (ret < 0)
		uea_err(INS_TO_USBDEV(sc),
			"writing cmv failed with error %d\n", ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक uea_ग_लिखो_cmv_e4(काष्ठा uea_softc *sc,
		u8 size, u16 group, u16 address, u16 offset, u32 data)
अणु
	पूर्णांक ret = uea_cmv_e4(sc, E4_MAKEFUNCTION(E4_MEMACCESS,
							E4_REQUESTWRITE, size),
			  group, address, offset, data);
	अगर (ret < 0)
		uea_err(INS_TO_USBDEV(sc),
			"writing cmv failed with error %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम uea_set_bulk_समयout(काष्ठा uea_softc *sc, u32 dsrate)
अणु
	पूर्णांक ret;
	u16 समयout;

	/* in bulk mode the modem have problem with high rate
	 * changing पूर्णांकernal timing could improve things, but the
	 * value is mysterious.
	 * ADI930 करोn't support it (-EPIPE error).
	 */

	अगर (UEA_CHIP_VERSION(sc) == ADI930 ||
	    altsetting[sc->modem_index] > 0 ||
	    sc->stats.phy.dsrate == dsrate)
		वापस;

	/* Original timming (1Mbit/s) from ADI (used in winकरोws driver) */
	समयout = (dsrate <= 1024*1024) ? 0 : 1;
	ret = uea_request(sc, UEA_SET_TIMEOUT, समयout, 0, शून्य);
	uea_info(INS_TO_USBDEV(sc), "setting new timeout %d%s\n",
		 समयout,  ret < 0 ? " failed" : "");

पूर्ण

/*
 * Monitor the modem and update the stat
 * वापस 0 अगर everything is ok
 * वापस < 0 अगर an error occurs (-EAGAIN reboot needed)
 */
अटल पूर्णांक uea_stat_e1(काष्ठा uea_softc *sc)
अणु
	u32 data;
	पूर्णांक ret;

	uea_enters(INS_TO_USBDEV(sc));
	data = sc->stats.phy.state;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_STAT, 0, &sc->stats.phy.state);
	अगर (ret < 0)
		वापस ret;

	चयन (GET_STATUS(sc->stats.phy.state)) अणु
	हाल 0:		/* not yet synchronized */
		uea_dbg(INS_TO_USBDEV(sc),
		       "modem not yet synchronized\n");
		वापस 0;

	हाल 1:		/* initialization */
		uea_dbg(INS_TO_USBDEV(sc), "modem initializing\n");
		वापस 0;

	हाल 2:		/* operational */
		uea_vdbg(INS_TO_USBDEV(sc), "modem operational\n");
		अवरोध;

	हाल 3:		/* fail ... */
		uea_info(INS_TO_USBDEV(sc), "modem synchronization failed"
					" (may be try other cmv/dsp)\n");
		वापस -EAGAIN;

	हाल 4 ... 6:	/* test state */
		uea_warn(INS_TO_USBDEV(sc),
				"modem in test mode - not supported\n");
		वापस -EAGAIN;

	हाल 7:		/* fast-retain ... */
		uea_info(INS_TO_USBDEV(sc), "modem in fast-retain mode\n");
		वापस 0;
	शेष:
		uea_err(INS_TO_USBDEV(sc), "modem invalid SW mode %d\n",
			GET_STATUS(sc->stats.phy.state));
		वापस -EAGAIN;
	पूर्ण

	अगर (GET_STATUS(data) != 2) अणु
		uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_OFF, 0, शून्य);
		uea_info(INS_TO_USBDEV(sc), "modem operational\n");

		/* release the dsp firmware as it is not needed until
		 * the next failure
		 */
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = शून्य;
	पूर्ण

	/* always update it as aपंचांग layer could not be init when we चयन to
	 * operational state
	 */
	UPDATE_ATM_SIGNAL(ATM_PHY_SIG_FOUND);

	/* wake up processes रुकोing क्रम synchronization */
	wake_up(&sc->sync_q);

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 2, &sc->stats.phy.flags);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.mflags |= sc->stats.phy.flags;

	/* in हाल of a flags ( क्रम example delineation LOSS (& 0x10)),
	 * we check the status again in order to detect the failure earlier
	 */
	अगर (sc->stats.phy.flags) अणु
		uea_dbg(INS_TO_USBDEV(sc), "Stat flag = 0x%x\n",
		       sc->stats.phy.flags);
		वापस 0;
	पूर्ण

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_RATE, 0, &data);
	अगर (ret < 0)
		वापस ret;

	uea_set_bulk_समयout(sc, (data >> 16) * 32);
	sc->stats.phy.dsrate = (data >> 16) * 32;
	sc->stats.phy.usrate = (data & 0xffff) * 32;
	UPDATE_ATM_STAT(link_rate, sc->stats.phy.dsrate * 1000 / 424);

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 23, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.dsattenuation = (data & 0xff) / 2;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 47, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.usattenuation = (data & 0xff) / 2;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 25, &sc->stats.phy.dsmargin);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 49, &sc->stats.phy.usmargin);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 51, &sc->stats.phy.rxflow);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 52, &sc->stats.phy.txflow);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 54, &sc->stats.phy.dsunc);
	अगर (ret < 0)
		वापस ret;

	/* only क्रम atu-c */
	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 58, &sc->stats.phy.usunc);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 53, &sc->stats.phy.dscorr);
	अगर (ret < 0)
		वापस ret;

	/* only क्रम atu-c */
	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_DIAG, 57, &sc->stats.phy.uscorr);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_INFO, 8, &sc->stats.phy.vidco);
	अगर (ret < 0)
		वापस ret;

	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_INFO, 13, &sc->stats.phy.vidcpe);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uea_stat_e4(काष्ठा uea_softc *sc)
अणु
	u32 data;
	u32 पंचांगp_arr[2];
	पूर्णांक ret;

	uea_enters(INS_TO_USBDEV(sc));
	data = sc->stats.phy.state;

	/* XXX only need to be करोne beक्रमe operationnal... */
	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_STAT, 0, 0, &sc->stats.phy.state);
	अगर (ret < 0)
		वापस ret;

	चयन (sc->stats.phy.state) अणु
	हाल 0x0:	/* not yet synchronized */
	हाल 0x1:
	हाल 0x3:
	हाल 0x4:
		uea_dbg(INS_TO_USBDEV(sc), "modem not yet "
						"synchronized\n");
		वापस 0;
	हाल 0x5:	/* initialization */
	हाल 0x6:
	हाल 0x9:
	हाल 0xa:
		uea_dbg(INS_TO_USBDEV(sc), "modem initializing\n");
		वापस 0;
	हाल 0x2:	/* fail ... */
		uea_info(INS_TO_USBDEV(sc), "modem synchronization "
				"failed (may be try other cmv/dsp)\n");
		वापस -EAGAIN;
	हाल 0x7:	/* operational */
		अवरोध;
	शेष:
		uea_warn(INS_TO_USBDEV(sc), "unknown state: %x\n",
						sc->stats.phy.state);
		वापस 0;
	पूर्ण

	अगर (data != 7) अणु
		uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_OFF, 0, शून्य);
		uea_info(INS_TO_USBDEV(sc), "modem operational\n");

		/* release the dsp firmware as it is not needed until
		 * the next failure
		 */
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = शून्य;
	पूर्ण

	/* always update it as aपंचांग layer could not be init when we चयन to
	 * operational state
	 */
	UPDATE_ATM_SIGNAL(ATM_PHY_SIG_FOUND);

	/* wake up processes रुकोing क्रम synchronization */
	wake_up(&sc->sync_q);

	/* TODO improve this state machine :
	 * we need some CMV info : what they करो and their unit
	 * we should find the equivalent of eagle3- CMV
	 */
	/* check flags */
	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_DIAG, 0, 0, &sc->stats.phy.flags);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.mflags |= sc->stats.phy.flags;

	/* in हाल of a flags ( क्रम example delineation LOSS (& 0x10)),
	 * we check the status again in order to detect the failure earlier
	 */
	अगर (sc->stats.phy.flags) अणु
		uea_dbg(INS_TO_USBDEV(sc), "Stat flag = 0x%x\n",
		       sc->stats.phy.flags);
		अगर (sc->stats.phy.flags & 1) /* delineation LOSS */
			वापस -EAGAIN;
		अगर (sc->stats.phy.flags & 0x4000) /* Reset Flag */
			वापस -EAGAIN;
		वापस 0;
	पूर्ण

	/* rate data may be in upper or lower half of 64 bit word, strange */
	ret = uea_पढ़ो_cmv_e4(sc, 4, E4_SA_RATE, 0, 0, पंचांगp_arr);
	अगर (ret < 0)
		वापस ret;
	data = (पंचांगp_arr[0]) ? पंचांगp_arr[0] : पंचांगp_arr[1];
	sc->stats.phy.usrate = data / 1000;

	ret = uea_पढ़ो_cmv_e4(sc, 4, E4_SA_RATE, 1, 0, पंचांगp_arr);
	अगर (ret < 0)
		वापस ret;
	data = (पंचांगp_arr[0]) ? पंचांगp_arr[0] : पंचांगp_arr[1];
	uea_set_bulk_समयout(sc, data / 1000);
	sc->stats.phy.dsrate = data / 1000;
	UPDATE_ATM_STAT(link_rate, sc->stats.phy.dsrate * 1000 / 424);

	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_INFO, 68, 1, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.dsattenuation = data / 10;

	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_INFO, 69, 1, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.usattenuation = data / 10;

	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_INFO, 68, 3, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.dsmargin = data / 2;

	ret = uea_पढ़ो_cmv_e4(sc, 1, E4_SA_INFO, 69, 3, &data);
	अगर (ret < 0)
		वापस ret;
	sc->stats.phy.usmargin = data / 10;

	वापस 0;
पूर्ण

अटल व्योम cmvs_file_name(काष्ठा uea_softc *sc, अक्षर *स्थिर cmv_name, पूर्णांक ver)
अणु
	अक्षर file_arr[] = "CMVxy.bin";
	अक्षर *file;

	kernel_param_lock(THIS_MODULE);
	/* set proper name corresponding modem version and line type */
	अगर (cmv_file[sc->modem_index] == शून्य) अणु
		अगर (UEA_CHIP_VERSION(sc) == ADI930)
			file_arr[3] = '9';
		अन्यथा अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV)
			file_arr[3] = '4';
		अन्यथा
			file_arr[3] = 'e';

		file_arr[4] = IS_ISDN(sc) ? 'i' : 'p';
		file = file_arr;
	पूर्ण अन्यथा
		file = cmv_file[sc->modem_index];

	म_नकल(cmv_name, FW_सूची);
	strlcat(cmv_name, file, UEA_FW_NAME_MAX);
	अगर (ver == 2)
		strlcat(cmv_name, ".v2", UEA_FW_NAME_MAX);
	kernel_param_unlock(THIS_MODULE);
पूर्ण

अटल पूर्णांक request_cmvs_old(काष्ठा uea_softc *sc,
		 व्योम **cmvs, स्थिर काष्ठा firmware **fw)
अणु
	पूर्णांक ret, size;
	u8 *data;
	अक्षर cmv_name[UEA_FW_NAME_MAX]; /* 30 bytes stack variable */

	cmvs_file_name(sc, cmv_name, 1);
	ret = request_firmware(fw, cmv_name, &sc->usb_dev->dev);
	अगर (ret < 0) अणु
		uea_err(INS_TO_USBDEV(sc),
		       "requesting firmware %s failed with error %d\n",
		       cmv_name, ret);
		वापस ret;
	पूर्ण

	data = (u8 *) (*fw)->data;
	size = (*fw)->size;
	अगर (size < 1)
		जाओ err_fw_corrupted;

	अगर (size != *data * माप(काष्ठा uea_cmvs_v1) + 1)
		जाओ err_fw_corrupted;

	*cmvs = (व्योम *)(data + 1);
	वापस *data;

err_fw_corrupted:
	uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n", cmv_name);
	release_firmware(*fw);
	वापस -EILSEQ;
पूर्ण

अटल पूर्णांक request_cmvs(काष्ठा uea_softc *sc,
		 व्योम **cmvs, स्थिर काष्ठा firmware **fw, पूर्णांक *ver)
अणु
	पूर्णांक ret, size;
	u32 crc;
	u8 *data;
	अक्षर cmv_name[UEA_FW_NAME_MAX]; /* 30 bytes stack variable */

	cmvs_file_name(sc, cmv_name, 2);
	ret = request_firmware(fw, cmv_name, &sc->usb_dev->dev);
	अगर (ret < 0) अणु
		/* अगर caller can handle old version, try to provide it */
		अगर (*ver == 1) अणु
			uea_warn(INS_TO_USBDEV(sc), "requesting "
							"firmware %s failed, "
				"try to get older cmvs\n", cmv_name);
			वापस request_cmvs_old(sc, cmvs, fw);
		पूर्ण
		uea_err(INS_TO_USBDEV(sc),
		       "requesting firmware %s failed with error %d\n",
		       cmv_name, ret);
		वापस ret;
	पूर्ण

	size = (*fw)->size;
	data = (u8 *) (*fw)->data;
	अगर (size < 4 || म_भेदन(data, "cmv2", 4) != 0) अणु
		अगर (*ver == 1) अणु
			uea_warn(INS_TO_USBDEV(sc), "firmware %s is corrupted,"
				" try to get older cmvs\n", cmv_name);
			release_firmware(*fw);
			वापस request_cmvs_old(sc, cmvs, fw);
		पूर्ण
		जाओ err_fw_corrupted;
	पूर्ण

	*ver = 2;

	data += 4;
	size -= 4;
	अगर (size < 5)
		जाओ err_fw_corrupted;

	crc = get_unaligned_le32(data);
	data += 4;
	size -= 4;
	अगर (crc32_be(0, data, size) != crc)
		जाओ err_fw_corrupted;

	अगर (size != *data * माप(काष्ठा uea_cmvs_v2) + 1)
		जाओ err_fw_corrupted;

	*cmvs = (व्योम *) (data + 1);
	वापस *data;

err_fw_corrupted:
	uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n", cmv_name);
	release_firmware(*fw);
	वापस -EILSEQ;
पूर्ण

अटल पूर्णांक uea_send_cmvs_e1(काष्ठा uea_softc *sc)
अणु
	पूर्णांक i, ret, len;
	व्योम *cmvs_ptr;
	स्थिर काष्ठा firmware *cmvs_fw;
	पूर्णांक ver = 1; /* we can handle v1 cmv firmware version; */

	/* Enter in R-IDLE (cmv) until inकाष्ठाed otherwise */
	ret = uea_ग_लिखो_cmv_e1(sc, E1_SA_CNTL, 0, 1);
	अगर (ret < 0)
		वापस ret;

	/* Dump firmware version */
	ret = uea_पढ़ो_cmv_e1(sc, E1_SA_INFO, 10, &sc->stats.phy.firmid);
	अगर (ret < 0)
		वापस ret;
	uea_info(INS_TO_USBDEV(sc), "ATU-R firmware version : %x\n",
			sc->stats.phy.firmid);

	/* get options */
	ret = len = request_cmvs(sc, &cmvs_ptr, &cmvs_fw, &ver);
	अगर (ret < 0)
		वापस ret;

	/* send options */
	अगर (ver == 1) अणु
		काष्ठा uea_cmvs_v1 *cmvs_v1 = cmvs_ptr;

		uea_warn(INS_TO_USBDEV(sc), "use deprecated cmvs version, "
			"please update your firmware\n");

		क्रम (i = 0; i < len; i++) अणु
			ret = uea_ग_लिखो_cmv_e1(sc,
				get_unaligned_le32(&cmvs_v1[i].address),
				get_unaligned_le16(&cmvs_v1[i].offset),
				get_unaligned_le32(&cmvs_v1[i].data));
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (ver == 2) अणु
		काष्ठा uea_cmvs_v2 *cmvs_v2 = cmvs_ptr;

		क्रम (i = 0; i < len; i++) अणु
			ret = uea_ग_लिखो_cmv_e1(sc,
				get_unaligned_le32(&cmvs_v2[i].address),
				(u16) get_unaligned_le32(&cmvs_v2[i].offset),
				get_unaligned_le32(&cmvs_v2[i].data));
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This really should not happen */
		uea_err(INS_TO_USBDEV(sc), "bad cmvs version %d\n", ver);
		जाओ out;
	पूर्ण

	/* Enter in R-ACT-REQ */
	ret = uea_ग_लिखो_cmv_e1(sc, E1_SA_CNTL, 0, 2);
	uea_vdbg(INS_TO_USBDEV(sc), "Entering in R-ACT-REQ state\n");
	uea_info(INS_TO_USBDEV(sc), "modem started, waiting "
						"synchronization...\n");
out:
	release_firmware(cmvs_fw);
	वापस ret;
पूर्ण

अटल पूर्णांक uea_send_cmvs_e4(काष्ठा uea_softc *sc)
अणु
	पूर्णांक i, ret, len;
	व्योम *cmvs_ptr;
	स्थिर काष्ठा firmware *cmvs_fw;
	पूर्णांक ver = 2; /* we can only handle v2 cmv firmware version; */

	/* Enter in R-IDLE (cmv) until inकाष्ठाed otherwise */
	ret = uea_ग_लिखो_cmv_e4(sc, 1, E4_SA_CNTL, 0, 0, 1);
	अगर (ret < 0)
		वापस ret;

	/* Dump firmware version */
	/* XXX करोn't पढ़ो the 3th byte as it is always 6 */
	ret = uea_पढ़ो_cmv_e4(sc, 2, E4_SA_INFO, 55, 0, &sc->stats.phy.firmid);
	अगर (ret < 0)
		वापस ret;
	uea_info(INS_TO_USBDEV(sc), "ATU-R firmware version : %x\n",
			sc->stats.phy.firmid);


	/* get options */
	ret = len = request_cmvs(sc, &cmvs_ptr, &cmvs_fw, &ver);
	अगर (ret < 0)
		वापस ret;

	/* send options */
	अगर (ver == 2) अणु
		काष्ठा uea_cmvs_v2 *cmvs_v2 = cmvs_ptr;

		क्रम (i = 0; i < len; i++) अणु
			ret = uea_ग_लिखो_cmv_e4(sc, 1,
				get_unaligned_le32(&cmvs_v2[i].group),
				get_unaligned_le32(&cmvs_v2[i].address),
				get_unaligned_le32(&cmvs_v2[i].offset),
				get_unaligned_le32(&cmvs_v2[i].data));
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This really should not happen */
		uea_err(INS_TO_USBDEV(sc), "bad cmvs version %d\n", ver);
		जाओ out;
	पूर्ण

	/* Enter in R-ACT-REQ */
	ret = uea_ग_लिखो_cmv_e4(sc, 1, E4_SA_CNTL, 0, 0, 2);
	uea_vdbg(INS_TO_USBDEV(sc), "Entering in R-ACT-REQ state\n");
	uea_info(INS_TO_USBDEV(sc), "modem started, waiting "
						"synchronization...\n");
out:
	release_firmware(cmvs_fw);
	वापस ret;
पूर्ण

/* Start boot post firmware modem:
 * - send reset commands through usb control pipe
 * - start workqueue क्रम DSP loading
 * - send CMV options to modem
 */

अटल पूर्णांक uea_start_reset(काष्ठा uea_softc *sc)
अणु
	u16 zero = 0;	/* ;-) */
	पूर्णांक ret;

	uea_enters(INS_TO_USBDEV(sc));
	uea_info(INS_TO_USBDEV(sc), "(re)booting started\n");

	/* mask पूर्णांकerrupt */
	sc->booting = 1;
	/* We need to set this here because, a ack समयout could have occurred,
	 * but beक्रमe we start the reboot, the ack occurs and set this to 1.
	 * So we will failed to रुको Ready CMV.
	 */
	sc->cmv_ack = 0;
	UPDATE_ATM_SIGNAL(ATM_PHY_SIG_LOST);

	/* reset statistics */
	स_रखो(&sc->stats, 0, माप(काष्ठा uea_stats));

	/* tell the modem that we want to boot in IDMA mode */
	uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_ON, 0, शून्य);
	uea_request(sc, UEA_SET_MODE, UEA_BOOT_IDMA, 0, शून्य);

	/* enter reset mode */
	uea_request(sc, UEA_SET_MODE, UEA_START_RESET, 0, शून्य);

	/* original driver use 200ms, but winकरोws driver use 100ms */
	ret = uea_रुको(sc, 0, msecs_to_jअगरfies(100));
	अगर (ret < 0)
		वापस ret;

	/* leave reset mode */
	uea_request(sc, UEA_SET_MODE, UEA_END_RESET, 0, शून्य);

	अगर (UEA_CHIP_VERSION(sc) != EAGLE_IV) अणु
		/* clear tx and rx mailboxes */
		uea_request(sc, UEA_SET_2183_DATA, UEA_MPTX_MAILBOX, 2, &zero);
		uea_request(sc, UEA_SET_2183_DATA, UEA_MPRX_MAILBOX, 2, &zero);
		uea_request(sc, UEA_SET_2183_DATA, UEA_SWAP_MAILBOX, 2, &zero);
	पूर्ण

	ret = uea_रुको(sc, 0, msecs_to_jअगरfies(1000));
	अगर (ret < 0)
		वापस ret;

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV)
		sc->cmv_dsc.e4.function = E4_MAKEFUNCTION(E4_ADSLसूचीECTIVE,
							E4_MODEMREADY, 1);
	अन्यथा
		sc->cmv_dsc.e1.function = E1_MAKEFUNCTION(E1_ADSLसूचीECTIVE,
							E1_MODEMREADY);

	/* demask पूर्णांकerrupt */
	sc->booting = 0;

	/* start loading DSP */
	sc->pageno = 0;
	sc->ovl = 0;
	schedule_work(&sc->task);

	/* रुको क्रम modem पढ़ोy CMV */
	ret = रुको_cmv_ack(sc);
	अगर (ret < 0)
		वापस ret;

	uea_vdbg(INS_TO_USBDEV(sc), "Ready CMV received\n");

	ret = sc->send_cmvs(sc);
	अगर (ret < 0)
		वापस ret;

	sc->reset = 0;
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

/*
 * In हाल of an error रुको 1s beक्रमe rebooting the modem
 * अगर the modem करोn't request reboot (-EAGAIN).
 * Monitor the modem every 1s.
 */

अटल पूर्णांक uea_kthपढ़ो(व्योम *data)
अणु
	काष्ठा uea_softc *sc = data;
	पूर्णांक ret = -EAGAIN;

	set_मुक्तzable();
	uea_enters(INS_TO_USBDEV(sc));
	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (ret < 0 || sc->reset)
			ret = uea_start_reset(sc);
		अगर (!ret)
			ret = sc->stat(sc);
		अगर (ret != -EAGAIN)
			uea_रुको(sc, 0, msecs_to_jअगरfies(1000));
		try_to_मुक्तze();
	पूर्ण
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

/* Load second usb firmware क्रम ADI930 chip */
अटल पूर्णांक load_XILINX_firmware(काष्ठा uea_softc *sc)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक ret, size, u, ln;
	स्थिर u8 *pfw;
	u8 value;
	अक्षर *fw_name = FPGA930_FIRMWARE;

	uea_enters(INS_TO_USBDEV(sc));

	ret = request_firmware(&fw_entry, fw_name, &sc->usb_dev->dev);
	अगर (ret) अणु
		uea_err(INS_TO_USBDEV(sc), "firmware %s is not available\n",
		       fw_name);
		जाओ err0;
	पूर्ण

	pfw = fw_entry->data;
	size = fw_entry->size;
	अगर (size != 0x577B) अणु
		uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n",
		       fw_name);
		ret = -EILSEQ;
		जाओ err1;
	पूर्ण
	क्रम (u = 0; u < size; u += ln) अणु
		ln = min(size - u, 64);
		ret = uea_request(sc, 0xe, 0, ln, pfw + u);
		अगर (ret < 0) अणु
			uea_err(INS_TO_USBDEV(sc),
			       "elsa download data failed (%d)\n", ret);
			जाओ err1;
		पूर्ण
	पूर्ण

	/* finish to send the fpga */
	ret = uea_request(sc, 0xe, 1, 0, शून्य);
	अगर (ret < 0) अणु
		uea_err(INS_TO_USBDEV(sc),
				"elsa download data failed (%d)\n", ret);
		जाओ err1;
	पूर्ण

	/* Tell the modem we finish : de-निश्चित reset */
	value = 0;
	ret = uea_send_modem_cmd(sc->usb_dev, 0xe, 1, &value);
	अगर (ret < 0)
		uea_err(sc->usb_dev, "elsa de-assert failed with error"
								" %d\n", ret);

err1:
	release_firmware(fw_entry);
err0:
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

/* The modem send us an ack. First with check अगर it right */
अटल व्योम uea_dispatch_cmv_e1(काष्ठा uea_softc *sc, काष्ठा पूर्णांकr_pkt *पूर्णांकr)
अणु
	काष्ठा cmv_dsc_e1 *dsc = &sc->cmv_dsc.e1;
	काष्ठा cmv_e1 *cmv = &पूर्णांकr->u.e1.s2.cmv;

	uea_enters(INS_TO_USBDEV(sc));
	अगर (le16_to_cpu(cmv->wPreamble) != E1_PREAMBLE)
		जाओ bad1;

	अगर (cmv->bDirection != E1_MODEMTOHOST)
		जाओ bad1;

	/* FIXME : ADI930 reply wrong preambule (func = 2, sub = 2) to
	 * the first MEMACCESS cmv. Ignore it...
	 */
	अगर (cmv->bFunction != dsc->function) अणु
		अगर (UEA_CHIP_VERSION(sc) == ADI930
				&& cmv->bFunction ==  E1_MAKEFUNCTION(2, 2)) अणु
			cmv->wIndex = cpu_to_le16(dsc->idx);
			put_unaligned_le32(dsc->address,
						&cmv->dwSymbolicAddress);
			cmv->wOffsetAddress = cpu_to_le16(dsc->offset);
		पूर्ण अन्यथा
			जाओ bad2;
	पूर्ण

	अगर (cmv->bFunction == E1_MAKEFUNCTION(E1_ADSLसूचीECTIVE,
							E1_MODEMREADY)) अणु
		wake_up_cmv_ack(sc);
		uea_leaves(INS_TO_USBDEV(sc));
		वापस;
	पूर्ण

	/* in हाल of MEMACCESS */
	अगर (le16_to_cpu(cmv->wIndex) != dsc->idx ||
	    get_unaligned_le32(&cmv->dwSymbolicAddress) != dsc->address ||
	    le16_to_cpu(cmv->wOffsetAddress) != dsc->offset)
		जाओ bad2;

	sc->data = get_unaligned_le32(&cmv->dwData);
	sc->data = sc->data << 16 | sc->data >> 16;

	wake_up_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	वापस;

bad2:
	uea_err(INS_TO_USBDEV(sc), "unexpected cmv received, "
			"Function : %d, Subfunction : %d\n",
			E1_FUNCTION_TYPE(cmv->bFunction),
			E1_FUNCTION_SUBTYPE(cmv->bFunction));
	uea_leaves(INS_TO_USBDEV(sc));
	वापस;

bad1:
	uea_err(INS_TO_USBDEV(sc), "invalid cmv received, "
			"wPreamble %d, bDirection %d\n",
			le16_to_cpu(cmv->wPreamble), cmv->bDirection);
	uea_leaves(INS_TO_USBDEV(sc));
पूर्ण

/* The modem send us an ack. First with check अगर it right */
अटल व्योम uea_dispatch_cmv_e4(काष्ठा uea_softc *sc, काष्ठा पूर्णांकr_pkt *पूर्णांकr)
अणु
	काष्ठा cmv_dsc_e4 *dsc = &sc->cmv_dsc.e4;
	काष्ठा cmv_e4 *cmv = &पूर्णांकr->u.e4.s2.cmv;

	uea_enters(INS_TO_USBDEV(sc));
	uea_dbg(INS_TO_USBDEV(sc), "cmv %x %x %x %x %x %x\n",
		be16_to_cpu(cmv->wGroup), be16_to_cpu(cmv->wFunction),
		be16_to_cpu(cmv->wOffset), be16_to_cpu(cmv->wAddress),
		be32_to_cpu(cmv->dwData[0]), be32_to_cpu(cmv->dwData[1]));

	अगर (be16_to_cpu(cmv->wFunction) != dsc->function)
		जाओ bad2;

	अगर (be16_to_cpu(cmv->wFunction) == E4_MAKEFUNCTION(E4_ADSLसूचीECTIVE,
						E4_MODEMREADY, 1)) अणु
		wake_up_cmv_ack(sc);
		uea_leaves(INS_TO_USBDEV(sc));
		वापस;
	पूर्ण

	/* in हाल of MEMACCESS */
	अगर (be16_to_cpu(cmv->wOffset) != dsc->offset ||
	    be16_to_cpu(cmv->wGroup) != dsc->group ||
	    be16_to_cpu(cmv->wAddress) != dsc->address)
		जाओ bad2;

	sc->data = be32_to_cpu(cmv->dwData[0]);
	sc->data1 = be32_to_cpu(cmv->dwData[1]);
	wake_up_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	वापस;

bad2:
	uea_err(INS_TO_USBDEV(sc), "unexpected cmv received, "
			"Function : %d, Subfunction : %d\n",
			E4_FUNCTION_TYPE(cmv->wFunction),
			E4_FUNCTION_SUBTYPE(cmv->wFunction));
	uea_leaves(INS_TO_USBDEV(sc));
	वापस;
पूर्ण

अटल व्योम uea_schedule_load_page_e1(काष्ठा uea_softc *sc,
						काष्ठा पूर्णांकr_pkt *पूर्णांकr)
अणु
	sc->pageno = पूर्णांकr->e1_bSwapPageNo;
	sc->ovl = पूर्णांकr->e1_bOvl >> 4 | पूर्णांकr->e1_bOvl << 4;
	schedule_work(&sc->task);
पूर्ण

अटल व्योम uea_schedule_load_page_e4(काष्ठा uea_softc *sc,
						काष्ठा पूर्णांकr_pkt *पूर्णांकr)
अणु
	sc->pageno = पूर्णांकr->e4_bSwapPageNo;
	schedule_work(&sc->task);
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल व्योम uea_पूर्णांकr(काष्ठा urb *urb)
अणु
	काष्ठा uea_softc *sc = urb->context;
	काष्ठा पूर्णांकr_pkt *पूर्णांकr = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	uea_enters(INS_TO_USBDEV(sc));

	अगर (unlikely(status < 0)) अणु
		uea_err(INS_TO_USBDEV(sc), "uea_intr() failed with %d\n",
		       status);
		वापस;
	पूर्ण

	/* device-to-host पूर्णांकerrupt */
	अगर (पूर्णांकr->bType != 0x08 || sc->booting) अणु
		uea_err(INS_TO_USBDEV(sc), "wrong interrupt\n");
		जाओ resubmit;
	पूर्ण

	चयन (le16_to_cpu(पूर्णांकr->wInterrupt)) अणु
	हाल INT_LOADSWAPPAGE:
		sc->schedule_load_page(sc, पूर्णांकr);
		अवरोध;

	हाल INT_INCOMINGCMV:
		sc->dispatch_cmv(sc, पूर्णांकr);
		अवरोध;

	शेष:
		uea_err(INS_TO_USBDEV(sc), "unknown interrupt %u\n",
		       le16_to_cpu(पूर्णांकr->wInterrupt));
	पूर्ण

resubmit:
	usb_submit_urb(sc->urb_पूर्णांक, GFP_ATOMIC);
पूर्ण

/*
 * Start the modem : init the data and start kernel thपढ़ो
 */
अटल पूर्णांक uea_boot(काष्ठा uea_softc *sc, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा पूर्णांकr_pkt *पूर्णांकr;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक size;

	uea_enters(INS_TO_USBDEV(sc));

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV) अणु
		size = E4_INTR_PKT_SIZE;
		sc->dispatch_cmv = uea_dispatch_cmv_e4;
		sc->schedule_load_page = uea_schedule_load_page_e4;
		sc->stat = uea_stat_e4;
		sc->send_cmvs = uea_send_cmvs_e4;
		INIT_WORK(&sc->task, uea_load_page_e4);
	पूर्ण अन्यथा अणु
		size = E1_INTR_PKT_SIZE;
		sc->dispatch_cmv = uea_dispatch_cmv_e1;
		sc->schedule_load_page = uea_schedule_load_page_e1;
		sc->stat = uea_stat_e1;
		sc->send_cmvs = uea_send_cmvs_e1;
		INIT_WORK(&sc->task, uea_load_page_e1);
	पूर्ण

	init_रुकोqueue_head(&sc->sync_q);

	अगर (UEA_CHIP_VERSION(sc) == ADI930)
		load_XILINX_firmware(sc);

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1) अणु
		ret = -ENODEV;
		जाओ err0;
	पूर्ण

	पूर्णांकr = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!पूर्णांकr)
		जाओ err0;

	sc->urb_पूर्णांक = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!sc->urb_पूर्णांक)
		जाओ err1;

	usb_fill_पूर्णांक_urb(sc->urb_पूर्णांक, sc->usb_dev,
			 usb_rcvपूर्णांकpipe(sc->usb_dev, UEA_INTR_PIPE),
			 पूर्णांकr, size, uea_पूर्णांकr, sc,
			 पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc.bInterval);

	ret = usb_submit_urb(sc->urb_पूर्णांक, GFP_KERNEL);
	अगर (ret < 0) अणु
		uea_err(INS_TO_USBDEV(sc),
		       "urb submission failed with error %d\n", ret);
		जाओ err1;
	पूर्ण

	/* Create worker thपढ़ो, but करोn't start it here.  Start it after
	 * all usbaपंचांग generic initialization is करोne.
	 */
	sc->kthपढ़ो = kthपढ़ो_create(uea_kthपढ़ो, sc, "ueagle-atm");
	अगर (IS_ERR(sc->kthपढ़ो)) अणु
		uea_err(INS_TO_USBDEV(sc), "failed to create thread\n");
		ret = PTR_ERR(sc->kthपढ़ो);
		जाओ err2;
	पूर्ण

	uea_leaves(INS_TO_USBDEV(sc));
	वापस 0;

err2:
	usb_समाप्त_urb(sc->urb_पूर्णांक);
err1:
	usb_मुक्त_urb(sc->urb_पूर्णांक);
	sc->urb_पूर्णांक = शून्य;
	kमुक्त(पूर्णांकr);
err0:
	uea_leaves(INS_TO_USBDEV(sc));
	वापस ret;
पूर्ण

/*
 * Stop the modem : समाप्त kernel thपढ़ो and मुक्त data
 */
अटल व्योम uea_stop(काष्ठा uea_softc *sc)
अणु
	पूर्णांक ret;
	uea_enters(INS_TO_USBDEV(sc));
	ret = kthपढ़ो_stop(sc->kthपढ़ो);
	uea_dbg(INS_TO_USBDEV(sc), "kthread finish with status %d\n", ret);

	uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_ON, 0, शून्य);

	usb_समाप्त_urb(sc->urb_पूर्णांक);
	kमुक्त(sc->urb_पूर्णांक->transfer_buffer);
	usb_मुक्त_urb(sc->urb_पूर्णांक);

	/* flush the work item, when no one can schedule it */
	flush_work(&sc->task);

	release_firmware(sc->dsp_firm);
	uea_leaves(INS_TO_USBDEV(sc));
पूर्ण

/* syfs पूर्णांकerface */
अटल काष्ठा uea_softc *dev_to_uea(काष्ठा device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usbaपंचांग_data *usbaपंचांग;

	पूर्णांकf = to_usb_पूर्णांकerface(dev);
	अगर (!पूर्णांकf)
		वापस शून्य;

	usbaपंचांग = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!usbaपंचांग)
		वापस शून्य;

	वापस usbaपंचांग->driver_data;
पूर्ण

अटल sमाप_प्रकार stat_status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा uea_softc *sc;

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	अगर (!sc)
		जाओ out;
	ret = snम_लिखो(buf, 10, "%08x\n", sc->stats.phy.state);
out:
	mutex_unlock(&uea_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार stat_status_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा uea_softc *sc;

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	अगर (!sc)
		जाओ out;
	sc->reset = 1;
	ret = count;
out:
	mutex_unlock(&uea_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RW(stat_status);

अटल sमाप_प्रकार stat_human_status_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret = -ENODEV;
	पूर्णांक modem_state;
	काष्ठा uea_softc *sc;

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	अगर (!sc)
		जाओ out;

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV) अणु
		चयन (sc->stats.phy.state) अणु
		हाल 0x0:	/* not yet synchronized */
		हाल 0x1:
		हाल 0x3:
		हाल 0x4:
			modem_state = 0;
			अवरोध;
		हाल 0x5:	/* initialization */
		हाल 0x6:
		हाल 0x9:
		हाल 0xa:
			modem_state = 1;
			अवरोध;
		हाल 0x7:	/* operational */
			modem_state = 2;
			अवरोध;
		हाल 0x2:	/* fail ... */
			modem_state = 3;
			अवरोध;
		शेष:	/* unknown */
			modem_state = 4;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		modem_state = GET_STATUS(sc->stats.phy.state);

	चयन (modem_state) अणु
	हाल 0:
		ret = प्र_लिखो(buf, "Modem is booting\n");
		अवरोध;
	हाल 1:
		ret = प्र_लिखो(buf, "Modem is initializing\n");
		अवरोध;
	हाल 2:
		ret = प्र_लिखो(buf, "Modem is operational\n");
		अवरोध;
	हाल 3:
		ret = प्र_लिखो(buf, "Modem synchronization failed\n");
		अवरोध;
	शेष:
		ret = प्र_लिखो(buf, "Modem state is unknown\n");
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&uea_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(stat_human_status);

अटल sमाप_प्रकार stat_delin_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा uea_softc *sc;
	अक्षर *delin = "GOOD";

	mutex_lock(&uea_mutex);
	sc = dev_to_uea(dev);
	अगर (!sc)
		जाओ out;

	अगर (UEA_CHIP_VERSION(sc) == EAGLE_IV) अणु
		अगर (sc->stats.phy.flags & 0x4000)
			delin = "RESET";
		अन्यथा अगर (sc->stats.phy.flags & 0x0001)
			delin = "LOSS";
	पूर्ण अन्यथा अणु
		अगर (sc->stats.phy.flags & 0x0C00)
			delin = "ERROR";
		अन्यथा अगर (sc->stats.phy.flags & 0x0030)
			delin = "LOSS";
	पूर्ण

	ret = प्र_लिखो(buf, "%s\n", delin);
out:
	mutex_unlock(&uea_mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(stat_delin);

#घोषणा UEA_ATTR(name, reset)					\
								\
अटल sमाप_प्रकार stat_##name##_show(काष्ठा device *dev,		\
		काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	पूर्णांक ret = -ENODEV;					\
	काष्ठा uea_softc *sc;					\
								\
	mutex_lock(&uea_mutex);					\
	sc = dev_to_uea(dev);					\
	अगर (!sc)						\
		जाओ out;					\
	ret = snम_लिखो(buf, 10, "%08x\n", sc->stats.phy.name);	\
	अगर (reset)						\
		sc->stats.phy.name = 0;				\
out:								\
	mutex_unlock(&uea_mutex);				\
	वापस ret;						\
पूर्ण								\
								\
अटल DEVICE_ATTR_RO(stat_##name)

UEA_ATTR(mflags, 1);
UEA_ATTR(vidcpe, 0);
UEA_ATTR(usrate, 0);
UEA_ATTR(dsrate, 0);
UEA_ATTR(usattenuation, 0);
UEA_ATTR(dsattenuation, 0);
UEA_ATTR(usmargin, 0);
UEA_ATTR(dsmargin, 0);
UEA_ATTR(txflow, 0);
UEA_ATTR(rxflow, 0);
UEA_ATTR(uscorr, 0);
UEA_ATTR(dscorr, 0);
UEA_ATTR(usunc, 0);
UEA_ATTR(dsunc, 0);
UEA_ATTR(firmid, 0);

/* Retrieve the device End System Identअगरier (MAC) */

अटल पूर्णांक uea_getesi(काष्ठा uea_softc *sc, u_अक्षर *esi)
अणु
	अचिन्हित अक्षर mac_str[2 * ETH_ALEN + 1];
	पूर्णांक i;
	अगर (usb_string
	    (sc->usb_dev, sc->usb_dev->descriptor.iSerialNumber, mac_str,
	     माप(mac_str)) != 2 * ETH_ALEN)
		वापस 1;

	क्रम (i = 0; i < ETH_ALEN; i++)
		esi[i] = hex_to_bin(mac_str[2 * i]) * 16 +
			 hex_to_bin(mac_str[2 * i + 1]);

	वापस 0;
पूर्ण

/* ATM stuff */
अटल पूर्णांक uea_aपंचांग_खोलो(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	काष्ठा uea_softc *sc = usbaपंचांग->driver_data;

	वापस uea_getesi(sc, aपंचांग_dev->esi);
पूर्ण

अटल पूर्णांक uea_heavy(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा uea_softc *sc = usbaपंचांग->driver_data;

	रुको_event_पूर्णांकerruptible(sc->sync_q, IS_OPERATIONAL(sc));

	वापस 0;

पूर्ण

अटल पूर्णांक claim_पूर्णांकerface(काष्ठा usb_device *usb_dev,
			   काष्ठा usbaपंचांग_data *usbaपंचांग, पूर्णांक अगरnum)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usb_अगरnum_to_अगर(usb_dev, अगरnum);

	अगर (!पूर्णांकf) अणु
		uea_err(usb_dev, "interface %d not found\n", अगरnum);
		वापस -ENODEV;
	पूर्ण

	ret = usb_driver_claim_पूर्णांकerface(&uea_driver, पूर्णांकf, usbaपंचांग);
	अगर (ret != 0)
		uea_err(usb_dev, "can't claim interface %d, error %d\n", अगरnum,
		       ret);
	वापस ret;
पूर्ण

अटल काष्ठा attribute *uea_attrs[] = अणु
	&dev_attr_stat_status.attr,
	&dev_attr_stat_mflags.attr,
	&dev_attr_stat_human_status.attr,
	&dev_attr_stat_delin.attr,
	&dev_attr_stat_vidcpe.attr,
	&dev_attr_stat_usrate.attr,
	&dev_attr_stat_dsrate.attr,
	&dev_attr_stat_usattenuation.attr,
	&dev_attr_stat_dsattenuation.attr,
	&dev_attr_stat_usmargin.attr,
	&dev_attr_stat_dsmargin.attr,
	&dev_attr_stat_txflow.attr,
	&dev_attr_stat_rxflow.attr,
	&dev_attr_stat_uscorr.attr,
	&dev_attr_stat_dscorr.attr,
	&dev_attr_stat_usunc.attr,
	&dev_attr_stat_dsunc.attr,
	&dev_attr_stat_firmid.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(uea);

अटल पूर्णांक uea_bind(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा uea_softc *sc;
	पूर्णांक ret, अगरnum = पूर्णांकf->altsetting->desc.bInterfaceNumber;
	अचिन्हित पूर्णांक alt;

	uea_enters(usb);

	/* पूर्णांकerface 0 is क्रम firmware/monitoring */
	अगर (अगरnum != UEA_INTR_IFACE_NO)
		वापस -ENODEV;

	usbaपंचांग->flags = (sync_रुको[modem_index] ? 0 : UDSL_SKIP_HEAVY_INIT);

	/* पूर्णांकerface 1 is क्रम outbound traffic */
	ret = claim_पूर्णांकerface(usb, usbaपंचांग, UEA_US_IFACE_NO);
	अगर (ret < 0)
		वापस ret;

	/* ADI930 has only 2 पूर्णांकerfaces and inbound traffic is on पूर्णांकerface 1 */
	अगर (UEA_CHIP_VERSION(id) != ADI930) अणु
		/* पूर्णांकerface 2 is क्रम inbound traffic */
		ret = claim_पूर्णांकerface(usb, usbaपंचांग, UEA_DS_IFACE_NO);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	sc = kzalloc(माप(काष्ठा uea_softc), GFP_KERNEL);
	अगर (!sc)
		वापस -ENOMEM;

	sc->usb_dev = usb;
	usbaपंचांग->driver_data = sc;
	sc->usbaपंचांग = usbaपंचांग;
	sc->modem_index = (modem_index < NB_MODEM) ? modem_index++ : 0;
	sc->driver_info = id->driver_info;

	/* first try to use module parameter */
	अगर (annex[sc->modem_index] == 1)
		sc->annex = ANNEXA;
	अन्यथा अगर (annex[sc->modem_index] == 2)
		sc->annex = ANNEXB;
	/* try to स्वतःdetect annex */
	अन्यथा अगर (sc->driver_info & AUTO_ANNEX_A)
		sc->annex = ANNEXA;
	अन्यथा अगर (sc->driver_info & AUTO_ANNEX_B)
		sc->annex = ANNEXB;
	अन्यथा
		sc->annex = (le16_to_cpu
		(sc->usb_dev->descriptor.bcdDevice) & 0x80) ? ANNEXB : ANNEXA;

	alt = altsetting[sc->modem_index];
	/* ADI930 करोn't support iso */
	अगर (UEA_CHIP_VERSION(id) != ADI930 && alt > 0) अणु
		अगर (alt <= 8 &&
			usb_set_पूर्णांकerface(usb, UEA_DS_IFACE_NO, alt) == 0) अणु
			uea_dbg(usb, "set alternate %u for 2 interface\n", alt);
			uea_info(usb, "using iso mode\n");
			usbaपंचांग->flags |= UDSL_USE_ISOC | UDSL_IGNORE_EILSEQ;
		पूर्ण अन्यथा अणु
			uea_err(usb, "setting alternate %u failed for "
					"2 interface, using bulk mode\n", alt);
		पूर्ण
	पूर्ण

	ret = uea_boot(sc, पूर्णांकf);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	kमुक्त(sc);
	वापस ret;
पूर्ण

अटल व्योम uea_unbind(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा uea_softc *sc = usbaपंचांग->driver_data;

	uea_stop(sc);
	kमुक्त(sc);
पूर्ण

अटल काष्ठा usbaपंचांग_driver uea_usbaपंचांग_driver = अणु
	.driver_name = "ueagle-atm",
	.bind = uea_bind,
	.aपंचांग_start = uea_aपंचांग_खोलो,
	.unbind = uea_unbind,
	.heavy_init = uea_heavy,
	.bulk_in = UEA_BULK_DATA_PIPE,
	.bulk_out = UEA_BULK_DATA_PIPE,
	.isoc_in = UEA_ISO_DATA_PIPE,
पूर्ण;

अटल पूर्णांक uea_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक ret;

	uea_enters(usb);
	uea_info(usb, "ADSL device founded vid (%#X) pid (%#X) Rev (%#X): %s\n",
		le16_to_cpu(usb->descriptor.idVenकरोr),
		le16_to_cpu(usb->descriptor.idProduct),
		le16_to_cpu(usb->descriptor.bcdDevice),
		chip_name[UEA_CHIP_VERSION(id)]);

	usb_reset_device(usb);

	अगर (UEA_IS_PREFIRM(id))
		वापस uea_load_firmware(usb, UEA_CHIP_VERSION(id));

	ret = usbaपंचांग_usb_probe(पूर्णांकf, id, &uea_usbaपंचांग_driver);
	अगर (ret == 0) अणु
		काष्ठा usbaपंचांग_data *usbaपंचांग = usb_get_पूर्णांकfdata(पूर्णांकf);
		काष्ठा uea_softc *sc = usbaपंचांग->driver_data;

		/* Ensure carrier is initialized to off as early as possible */
		UPDATE_ATM_SIGNAL(ATM_PHY_SIG_LOST);

		/* Only start the worker thपढ़ो when all init is करोne */
		wake_up_process(sc->kthपढ़ो);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम uea_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक अगरnum = पूर्णांकf->altsetting->desc.bInterfaceNumber;
	uea_enters(usb);

	/* ADI930 has 2 पूर्णांकerfaces and eagle 3 पूर्णांकerfaces.
	 * Pre-firmware device has one पूर्णांकerface
	 */
	अगर (usb->config->desc.bNumInterfaces != 1 && अगरnum == 0) अणु
		mutex_lock(&uea_mutex);
		usbaपंचांग_usb_disconnect(पूर्णांकf);
		mutex_unlock(&uea_mutex);
		uea_info(usb, "ADSL device removed\n");
	पूर्ण

	uea_leaves(usb);
पूर्ण

/*
 * List of supported VID/PID
 */
अटल स्थिर काष्ठा usb_device_id uea_ids[] = अणु
	अणुUSB_DEVICE(ANALOG_VID,	ADI930_PID_PREFIRM),
		.driver_info = ADI930 | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	ADI930_PID_PSTFIRM),
		.driver_info = ADI930 | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_I_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_I_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_II_PID_PREFIRM),
		.driver_info = EAGLE_II | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_II_PID_PSTFIRM),
		.driver_info = EAGLE_II | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_IIC_PID_PREFIRM),
		.driver_info = EAGLE_II | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_IIC_PID_PSTFIRM),
		.driver_info = EAGLE_II | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_III_PID_PREFIRM),
		.driver_info = EAGLE_III | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_III_PID_PSTFIRM),
		.driver_info = EAGLE_III | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_IV_PID_PREFIRM),
		.driver_info = EAGLE_IV | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ANALOG_VID,	EAGLE_IV_PID_PSTFIRM),
		.driver_info = EAGLE_IV | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_I_A_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_I_A_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM | AUTO_ANNEX_Aपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_I_B_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_I_B_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM | AUTO_ANNEX_Bपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_II_A_PID_PREFIRM),
		.driver_info = EAGLE_II | PREFIRMपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_II_A_PID_PSTFIRM),
		.driver_info = EAGLE_II | PSTFIRM | AUTO_ANNEX_Aपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_II_B_PID_PREFIRM),
		.driver_info = EAGLE_II | PREFIRMपूर्ण,
	अणुUSB_DEVICE(DEVOLO_VID,	DEVOLO_EAGLE_II_B_PID_PSTFIRM),
		.driver_info = EAGLE_II | PSTFIRM | AUTO_ANNEX_Bपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_PREFIRM),
		.driver_info = ADI930 | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_PSTFIRM),
		.driver_info = ADI930 | PSTFIRMपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_A_PREFIRM),
		.driver_info = ADI930 | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_A_PSTFIRM),
		.driver_info = ADI930 | PSTFIRM | AUTO_ANNEX_Aपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_B_PREFIRM),
		.driver_info = ADI930 | PREFIRMपूर्ण,
	अणुUSB_DEVICE(ELSA_VID,	ELSA_PID_B_PSTFIRM),
		.driver_info = ADI930 | PSTFIRM | AUTO_ANNEX_Bपूर्ण,
	अणुUSB_DEVICE(USR_VID,	MILLER_A_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(USR_VID,	MILLER_A_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM  | AUTO_ANNEX_Aपूर्ण,
	अणुUSB_DEVICE(USR_VID,	MILLER_B_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(USR_VID,	MILLER_B_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM  | AUTO_ANNEX_Bपूर्ण,
	अणुUSB_DEVICE(USR_VID,	HEINEKEN_A_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(USR_VID,	HEINEKEN_A_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM | AUTO_ANNEX_Aपूर्ण,
	अणुUSB_DEVICE(USR_VID,	HEINEKEN_B_PID_PREFIRM),
		.driver_info = EAGLE_I | PREFIRMपूर्ण,
	अणुUSB_DEVICE(USR_VID,	HEINEKEN_B_PID_PSTFIRM),
		.driver_info = EAGLE_I | PSTFIRM | AUTO_ANNEX_Bपूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * USB driver descriptor
 */
अटल काष्ठा usb_driver uea_driver = अणु
	.name = "ueagle-atm",
	.id_table = uea_ids,
	.probe = uea_probe,
	.disconnect = uea_disconnect,
	.dev_groups = uea_groups,
पूर्ण;

MODULE_DEVICE_TABLE(usb, uea_ids);

module_usb_driver(uea_driver);

MODULE_AUTHOR("Damien Bergamini/Matthieu Castet/Stanislaw W. Gruszka");
MODULE_DESCRIPTION("ADI 930/Eagle USB ADSL Modem driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_FIRMWARE(EAGLE_FIRMWARE);
MODULE_FIRMWARE(ADI930_FIRMWARE);
MODULE_FIRMWARE(EAGLE_I_FIRMWARE);
MODULE_FIRMWARE(EAGLE_II_FIRMWARE);
MODULE_FIRMWARE(EAGLE_III_FIRMWARE);
MODULE_FIRMWARE(EAGLE_IV_FIRMWARE);
MODULE_FIRMWARE(DSP4I_FIRMWARE);
MODULE_FIRMWARE(DSP4P_FIRMWARE);
MODULE_FIRMWARE(DSP9I_FIRMWARE);
MODULE_FIRMWARE(DSP9P_FIRMWARE);
MODULE_FIRMWARE(DSPEI_FIRMWARE);
MODULE_FIRMWARE(DSPEP_FIRMWARE);
MODULE_FIRMWARE(FPGA930_FIRMWARE);
MODULE_FIRMWARE(CMV4P_FIRMWARE);
MODULE_FIRMWARE(CMV4PV2_FIRMWARE);
MODULE_FIRMWARE(CMV4I_FIRMWARE);
MODULE_FIRMWARE(CMV4IV2_FIRMWARE);
MODULE_FIRMWARE(CMV9P_FIRMWARE);
MODULE_FIRMWARE(CMV9PV2_FIRMWARE);
MODULE_FIRMWARE(CMV9I_FIRMWARE);
MODULE_FIRMWARE(CMV9IV2_FIRMWARE);
MODULE_FIRMWARE(CMVEP_FIRMWARE);
MODULE_FIRMWARE(CMVEPV2_FIRMWARE);
MODULE_FIRMWARE(CMVEI_FIRMWARE);
MODULE_FIRMWARE(CMVEIV2_FIRMWARE);
