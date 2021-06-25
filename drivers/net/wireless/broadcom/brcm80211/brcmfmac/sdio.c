<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <defs.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश <brcm_hw_ids.h>
#समावेश <soc.h>
#समावेश "sdio.h"
#समावेश "chip.h"
#समावेश "firmware.h"
#समावेश "core.h"
#समावेश "common.h"
#समावेश "bcdc.h"

#घोषणा DCMD_RESP_TIMEOUT	msecs_to_jअगरfies(2500)
#घोषणा CTL_DONE_TIMEOUT	msecs_to_jअगरfies(2500)

/* watermark expressed in number of words */
#घोषणा DEFAULT_F2_WATERMARK    0x8
#घोषणा CY_4373_F2_WATERMARK    0x40
#घोषणा CY_4373_F1_MESBUSYCTRL  (CY_4373_F2_WATERMARK | SBSDIO_MESBUSYCTRL_ENAB)
#घोषणा CY_43012_F2_WATERMARK    0x60
#घोषणा CY_43012_MES_WATERMARK  0x50
#घोषणा CY_43012_MESBUSYCTRL    (CY_43012_MES_WATERMARK | \
				 SBSDIO_MESBUSYCTRL_ENAB)
#घोषणा CY_4339_F2_WATERMARK    48
#घोषणा CY_4339_MES_WATERMARK	80
#घोषणा CY_4339_MESBUSYCTRL	(CY_4339_MES_WATERMARK | \
				 SBSDIO_MESBUSYCTRL_ENAB)
#घोषणा CY_43455_F2_WATERMARK	0x60
#घोषणा CY_43455_MES_WATERMARK	0x50
#घोषणा CY_43455_MESBUSYCTRL	(CY_43455_MES_WATERMARK | \
				 SBSDIO_MESBUSYCTRL_ENAB)
#घोषणा CY_435X_F2_WATERMARK	0x40
#घोषणा CY_435X_F1_MESBUSYCTRL	(CY_435X_F2_WATERMARK | \
				 SBSDIO_MESBUSYCTRL_ENAB)

#अगर_घोषित DEBUG

#घोषणा BRCMF_TRAP_INFO_SIZE	80

#घोषणा CBUF_LEN	(128)

/* Device console log buffer state */
#घोषणा CONSOLE_BUFFER_MAX	2024

काष्ठा rte_log_le अणु
	__le32 buf;		/* Can't be poपूर्णांकer on (64-bit) hosts */
	__le32 buf_size;
	__le32 idx;
	अक्षर *_buf_compat;	/* Redundant poपूर्णांकer क्रम backward compat. */
पूर्ण;

काष्ठा rte_console अणु
	/* Virtual UART
	 * When there is no UART (e.g. Quickturn),
	 * the host should ग_लिखो a complete
	 * input line directly पूर्णांकo cbuf and then ग_लिखो
	 * the length पूर्णांकo vcons_in.
	 * This may also be used when there is a real UART
	 * (at risk of conflicting with
	 * the real UART).  vcons_out is currently unused.
	 */
	uपूर्णांक vcons_in;
	uपूर्णांक vcons_out;

	/* Output (logging) buffer
	 * Console output is written to a ring buffer log_buf at index log_idx.
	 * The host may पढ़ो the output when it sees log_idx advance.
	 * Output will be lost अगर the output wraps around faster than the host
	 * polls.
	 */
	काष्ठा rte_log_le log_le;

	/* Console input line buffer
	 * Characters are पढ़ो one at a समय पूर्णांकo cbuf
	 * until <CR> is received, then
	 * the buffer is processed as a command line.
	 * Also used क्रम भव UART.
	 */
	uपूर्णांक cbuf_idx;
	अक्षर cbuf[CBUF_LEN];
पूर्ण;

#पूर्ण_अगर				/* DEBUG */
#समावेश <chipcommon.h>

#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "tracepoint.h"

#घोषणा TXQLEN		2048	/* bulk tx queue length */
#घोषणा TXHI		(TXQLEN - 256)	/* turn on flow control above TXHI */
#घोषणा TXLOW		(TXHI - 256)	/* turn off flow control below TXLOW */
#घोषणा PRIOMASK	7

#घोषणा TXRETRIES	2	/* # of retries क्रम tx frames */

#घोषणा BRCMF_RXBOUND	50	/* Default क्रम max rx frames in
				 one scheduling */

#घोषणा BRCMF_TXBOUND	20	/* Default क्रम max tx frames in
				 one scheduling */

#घोषणा BRCMF_TXMINMAX	1	/* Max tx frames अगर rx still pending */

#घोषणा MEMBLOCK	2048	/* Block size used क्रम करोwnloading
				 of करोngle image */
#घोषणा MAX_DATA_BUF	(32 * 1024)	/* Must be large enough to hold
				 biggest possible glom */

#घोषणा BRCMF_FIRSTREAD	(1 << 6)

#घोषणा BRCMF_CONSOLE	10	/* watchकरोg पूर्णांकerval to poll console */

/* SBSDIO_DEVICE_CTL */

/* 1: device will निश्चित busy संकेत when receiving CMD53 */
#घोषणा SBSDIO_DEVCTL_SETBUSY		0x01
/* 1: निश्चितion of sdio पूर्णांकerrupt is synchronous to the sdio घड़ी */
#घोषणा SBSDIO_DEVCTL_SPI_INTR_SYNC	0x02
/* 1: mask all पूर्णांकerrupts to host except the chipActive (rev 8) */
#घोषणा SBSDIO_DEVCTL_CA_INT_ONLY	0x04
/* 1: isolate पूर्णांकernal sdio संकेतs, put बाह्यal pads in tri-state; requires
 * sdio bus घातer cycle to clear (rev 9) */
#घोषणा SBSDIO_DEVCTL_PADS_ISO		0x08
/* 1: enable F2 Watermark */
#घोषणा SBSDIO_DEVCTL_F2WM_ENAB		0x10
/* Force SD->SB reset mapping (rev 11) */
#घोषणा SBSDIO_DEVCTL_SB_RST_CTL	0x30
/*   Determined by CoreControl bit */
#घोषणा SBSDIO_DEVCTL_RST_CORECTL	0x00
/*   Force backplane reset */
#घोषणा SBSDIO_DEVCTL_RST_BPRESET	0x10
/*   Force no backplane reset */
#घोषणा SBSDIO_DEVCTL_RST_NOBPRESET	0x20

/* direct(mapped) cis space */

/* MAPPED common CIS address */
#घोषणा SBSDIO_CIS_BASE_COMMON		0x1000
/* maximum bytes in one CIS */
#घोषणा SBSDIO_CIS_SIZE_LIMIT		0x200
/* cis offset addr is < 17 bits */
#घोषणा SBSDIO_CIS_OFT_ADDR_MASK	0x1FFFF

/* manfid tuple length, include tuple, link bytes */
#घोषणा SBSDIO_CIS_MANFID_TUPLE_LEN	6

#घोषणा SD_REG(field) \
		(दुरत्व(काष्ठा sdpcmd_regs, field))

/* SDIO function 1 रेजिस्टर CHIPCLKCSR */
/* Force ALP request to backplane */
#घोषणा SBSDIO_FORCE_ALP		0x01
/* Force HT request to backplane */
#घोषणा SBSDIO_FORCE_HT			0x02
/* Force ILP request to backplane */
#घोषणा SBSDIO_FORCE_ILP		0x04
/* Make ALP पढ़ोy (घातer up xtal) */
#घोषणा SBSDIO_ALP_AVAIL_REQ		0x08
/* Make HT पढ़ोy (घातer up PLL) */
#घोषणा SBSDIO_HT_AVAIL_REQ		0x10
/* Squelch घड़ी requests from HW */
#घोषणा SBSDIO_FORCE_HW_CLKREQ_OFF	0x20
/* Status: ALP is पढ़ोy */
#घोषणा SBSDIO_ALP_AVAIL		0x40
/* Status: HT is पढ़ोy */
#घोषणा SBSDIO_HT_AVAIL			0x80
#घोषणा SBSDIO_CSR_MASK			0x1F
#घोषणा SBSDIO_AVBITS		(SBSDIO_HT_AVAIL | SBSDIO_ALP_AVAIL)
#घोषणा SBSDIO_ALPAV(regval)	((regval) & SBSDIO_AVBITS)
#घोषणा SBSDIO_HTAV(regval)	(((regval) & SBSDIO_AVBITS) == SBSDIO_AVBITS)
#घोषणा SBSDIO_ALPONLY(regval)	(SBSDIO_ALPAV(regval) && !SBSDIO_HTAV(regval))
#घोषणा SBSDIO_CLKAV(regval, alponly) \
	(SBSDIO_ALPAV(regval) && (alponly ? 1 : SBSDIO_HTAV(regval)))

/* पूर्णांकstatus */
#घोषणा I_SMB_SW0	(1 << 0)	/* To SB Mail S/W पूर्णांकerrupt 0 */
#घोषणा I_SMB_SW1	(1 << 1)	/* To SB Mail S/W पूर्णांकerrupt 1 */
#घोषणा I_SMB_SW2	(1 << 2)	/* To SB Mail S/W पूर्णांकerrupt 2 */
#घोषणा I_SMB_SW3	(1 << 3)	/* To SB Mail S/W पूर्णांकerrupt 3 */
#घोषणा I_SMB_SW_MASK	0x0000000f	/* To SB Mail S/W पूर्णांकerrupts mask */
#घोषणा I_SMB_SW_SHIFT	0	/* To SB Mail S/W पूर्णांकerrupts shअगरt */
#घोषणा I_HMB_SW0	(1 << 4)	/* To Host Mail S/W पूर्णांकerrupt 0 */
#घोषणा I_HMB_SW1	(1 << 5)	/* To Host Mail S/W पूर्णांकerrupt 1 */
#घोषणा I_HMB_SW2	(1 << 6)	/* To Host Mail S/W पूर्णांकerrupt 2 */
#घोषणा I_HMB_SW3	(1 << 7)	/* To Host Mail S/W पूर्णांकerrupt 3 */
#घोषणा I_HMB_SW_MASK	0x000000f0	/* To Host Mail S/W पूर्णांकerrupts mask */
#घोषणा I_HMB_SW_SHIFT	4	/* To Host Mail S/W पूर्णांकerrupts shअगरt */
#घोषणा I_WR_OOSYNC	(1 << 8)	/* Write Frame Out Of Sync */
#घोषणा I_RD_OOSYNC	(1 << 9)	/* Read Frame Out Of Sync */
#घोषणा	I_PC		(1 << 10)	/* descriptor error */
#घोषणा	I_PD		(1 << 11)	/* data error */
#घोषणा	I_DE		(1 << 12)	/* Descriptor protocol Error */
#घोषणा	I_RU		(1 << 13)	/* Receive descriptor Underflow */
#घोषणा	I_RO		(1 << 14)	/* Receive fअगरo Overflow */
#घोषणा	I_XU		(1 << 15)	/* Transmit fअगरo Underflow */
#घोषणा	I_RI		(1 << 16)	/* Receive Interrupt */
#घोषणा I_BUSPWR	(1 << 17)	/* SDIO Bus Power Change (rev 9) */
#घोषणा I_XMTDATA_AVAIL (1 << 23)	/* bits in fअगरo */
#घोषणा	I_XI		(1 << 24)	/* Transmit Interrupt */
#घोषणा I_RF_TERM	(1 << 25)	/* Read Frame Terminate */
#घोषणा I_WF_TERM	(1 << 26)	/* Write Frame Terminate */
#घोषणा I_PCMCIA_XU	(1 << 27)	/* PCMCIA Transmit FIFO Underflow */
#घोषणा I_SBINT		(1 << 28)	/* sbपूर्णांकstatus Interrupt */
#घोषणा I_CHIPACTIVE	(1 << 29)	/* chip from करोze to active state */
#घोषणा I_SRESET	(1 << 30)	/* CCCR RES पूर्णांकerrupt */
#घोषणा I_IOE2		(1U << 31)	/* CCCR IOE2 Bit Changed */
#घोषणा	I_ERRORS	(I_PC | I_PD | I_DE | I_RU | I_RO | I_XU)
#घोषणा I_DMA		(I_RI | I_XI | I_ERRORS)

/* corecontrol */
#घोषणा CC_CISRDY		(1 << 0)	/* CIS Ready */
#घोषणा CC_BPRESEN		(1 << 1)	/* CCCR RES संकेत */
#घोषणा CC_F2RDY		(1 << 2)	/* set CCCR IOR2 bit */
#घोषणा CC_CLRPADSISO		(1 << 3)	/* clear SDIO pads isolation */
#घोषणा CC_XMTDATAAVAIL_MODE	(1 << 4)
#घोषणा CC_XMTDATAAVAIL_CTRL	(1 << 5)

/* SDA_FRAMECTRL */
#घोषणा SFC_RF_TERM	(1 << 0)	/* Read Frame Terminate */
#घोषणा SFC_WF_TERM	(1 << 1)	/* Write Frame Terminate */
#घोषणा SFC_CRC4WOOS	(1 << 2)	/* CRC error क्रम ग_लिखो out of sync */
#घोषणा SFC_ABORTALL	(1 << 3)	/* Abort all in-progress frames */

/*
 * Software allocation of To SB Mailbox resources
 */

/* tosbmailbox bits corresponding to पूर्णांकstatus bits */
#घोषणा SMB_NAK		(1 << 0)	/* Frame NAK */
#घोषणा SMB_INT_ACK	(1 << 1)	/* Host Interrupt ACK */
#घोषणा SMB_USE_OOB	(1 << 2)	/* Use OOB Wakeup */
#घोषणा SMB_DEV_INT	(1 << 3)	/* Miscellaneous Interrupt */

/* tosbmailboxdata */
#घोषणा SMB_DATA_VERSION_SHIFT	16	/* host protocol version */

/*
 * Software allocation of To Host Mailbox resources
 */

/* पूर्णांकstatus bits */
#घोषणा I_HMB_FC_STATE	I_HMB_SW0	/* Flow Control State */
#घोषणा I_HMB_FC_CHANGE	I_HMB_SW1	/* Flow Control State Changed */
#घोषणा I_HMB_FRAME_IND	I_HMB_SW2	/* Frame Indication */
#घोषणा I_HMB_HOST_INT	I_HMB_SW3	/* Miscellaneous Interrupt */

/* tohosपंचांगailboxdata */
#घोषणा HMB_DATA_NAKHANDLED	0x0001	/* retransmit NAK'd frame */
#घोषणा HMB_DATA_DEVREADY	0x0002	/* talk to host after enable */
#घोषणा HMB_DATA_FC		0x0004	/* per prio flowcontrol update flag */
#घोषणा HMB_DATA_FWREADY	0x0008	/* fw पढ़ोy क्रम protocol activity */
#घोषणा HMB_DATA_FWHALT		0x0010	/* firmware halted */

#घोषणा HMB_DATA_FCDATA_MASK	0xff000000
#घोषणा HMB_DATA_FCDATA_SHIFT	24

#घोषणा HMB_DATA_VERSION_MASK	0x00ff0000
#घोषणा HMB_DATA_VERSION_SHIFT	16

/*
 * Software-defined protocol header
 */

/* Current protocol version */
#घोषणा SDPCM_PROT_VERSION	4

/*
 * Shared काष्ठाure between करोngle and the host.
 * The काष्ठाure contains poपूर्णांकers to trap or निश्चित inक्रमmation.
 */
#घोषणा SDPCM_SHARED_VERSION       0x0003
#घोषणा SDPCM_SHARED_VERSION_MASK  0x00FF
#घोषणा SDPCM_SHARED_ASSERT_BUILT  0x0100
#घोषणा SDPCM_SHARED_ASSERT        0x0200
#घोषणा SDPCM_SHARED_TRAP          0x0400

/* Space क्रम header पढ़ो, limit क्रम data packets */
#घोषणा MAX_HDR_READ	(1 << 6)
#घोषणा MAX_RX_DATASZ	2048

/* Bump up limit on रुकोing क्रम HT to account क्रम first startup;
 * अगर the image is करोing a CRC calculation beक्रमe programming the PMU
 * क्रम HT availability, it could take a couple hundred ms more, so
 * max out at a 1 second (1000000us).
 */
#अघोषित PMU_MAX_TRANSITION_DLY
#घोषणा PMU_MAX_TRANSITION_DLY 1000000

/* Value क्रम ChipClockCSR during initial setup */
#घोषणा BRCMF_INIT_CLKCTL1	(SBSDIO_FORCE_HW_CLKREQ_OFF |	\
					SBSDIO_ALP_AVAIL_REQ)

/* Flags क्रम SDH calls */
#घोषणा F2SYNC	(SDIO_REQ_4BYTE | SDIO_REQ_FIXED)

#घोषणा BRCMF_IDLE_ACTIVE	0	/* Do not request any SD घड़ी change
					 * when idle
					 */
#घोषणा BRCMF_IDLE_INTERVAL	1

#घोषणा KSO_WAIT_US 50
#घोषणा MAX_KSO_ATTEMPTS (PMU_MAX_TRANSITION_DLY/KSO_WAIT_US)
#घोषणा BRCMF_SDIO_MAX_ACCESS_ERRORS	5

#अगर_घोषित DEBUG
/* Device console log buffer state */
काष्ठा brcmf_console अणु
	uपूर्णांक count;		/* Poll पूर्णांकerval msec counter */
	uपूर्णांक log_addr;		/* Log काष्ठा address (fixed) */
	काष्ठा rte_log_le log_le;	/* Log काष्ठा (host copy) */
	uपूर्णांक bufsize;		/* Size of log buffer */
	u8 *buf;		/* Log buffer (host copy) */
	uपूर्णांक last;		/* Last buffer पढ़ो index */
पूर्ण;

काष्ठा brcmf_trap_info अणु
	__le32		type;
	__le32		epc;
	__le32		cpsr;
	__le32		spsr;
	__le32		r0;	/* a1 */
	__le32		r1;	/* a2 */
	__le32		r2;	/* a3 */
	__le32		r3;	/* a4 */
	__le32		r4;	/* v1 */
	__le32		r5;	/* v2 */
	__le32		r6;	/* v3 */
	__le32		r7;	/* v4 */
	__le32		r8;	/* v5 */
	__le32		r9;	/* sb/v6 */
	__le32		r10;	/* sl/v7 */
	__le32		r11;	/* fp/v8 */
	__le32		r12;	/* ip */
	__le32		r13;	/* sp */
	__le32		r14;	/* lr */
	__le32		pc;	/* r15 */
पूर्ण;
#पूर्ण_अगर				/* DEBUG */

काष्ठा sdpcm_shared अणु
	u32 flags;
	u32 trap_addr;
	u32 निश्चित_exp_addr;
	u32 निश्चित_file_addr;
	u32 निश्चित_line;
	u32 console_addr;	/* Address of काष्ठा rte_console */
	u32 msgtrace_addr;
	u8 tag[32];
	u32 brpt_addr;
पूर्ण;

काष्ठा sdpcm_shared_le अणु
	__le32 flags;
	__le32 trap_addr;
	__le32 निश्चित_exp_addr;
	__le32 निश्चित_file_addr;
	__le32 निश्चित_line;
	__le32 console_addr;	/* Address of काष्ठा rte_console */
	__le32 msgtrace_addr;
	u8 tag[32];
	__le32 brpt_addr;
पूर्ण;

/* करोngle SDIO bus specअगरic header info */
काष्ठा brcmf_sdio_hdrinfo अणु
	u8 seq_num;
	u8 channel;
	u16 len;
	u16 len_left;
	u16 len_nxtfrm;
	u8 dat_offset;
	bool lastfrm;
	u16 tail_pad;
पूर्ण;

/*
 * hold counter variables
 */
काष्ठा brcmf_sdio_count अणु
	uपूर्णांक पूर्णांकrcount;		/* Count of device पूर्णांकerrupt callbacks */
	uपूर्णांक lastपूर्णांकrs;		/* Count as of last watchकरोg समयr */
	uपूर्णांक pollcnt;		/* Count of active polls */
	uपूर्णांक regfails;		/* Count of R_REG failures */
	uपूर्णांक tx_sderrs;		/* Count of tx attempts with sd errors */
	uपूर्णांक fcqueued;		/* Tx packets that got queued */
	uपूर्णांक rxrtx;		/* Count of rtx requests (NAK to करोngle) */
	uपूर्णांक rx_tooदीर्घ;	/* Receive frames too दीर्घ to receive */
	uपूर्णांक rxc_errors;	/* SDIO errors when पढ़ोing control frames */
	uपूर्णांक rx_hdrfail;	/* SDIO errors on header पढ़ोs */
	uपूर्णांक rx_badhdr;		/* Bad received headers (roosync?) */
	uपूर्णांक rx_badseq;		/* Mismatched rx sequence number */
	uपूर्णांक fc_rcvd;		/* Number of flow-control events received */
	uपूर्णांक fc_xoff;		/* Number which turned on flow-control */
	uपूर्णांक fc_xon;		/* Number which turned off flow-control */
	uपूर्णांक rxglomfail;	/* Failed deglom attempts */
	uपूर्णांक rxglomframes;	/* Number of glom frames (superframes) */
	uपूर्णांक rxglompkts;	/* Number of packets from glom frames */
	uपूर्णांक f2rxhdrs;		/* Number of header पढ़ोs */
	uपूर्णांक f2rxdata;		/* Number of frame data पढ़ोs */
	uपूर्णांक f2txdata;		/* Number of f2 frame ग_लिखोs */
	uपूर्णांक f1regdata;		/* Number of f1 रेजिस्टर accesses */
	uपूर्णांक tickcnt;		/* Number of watchकरोg been schedule */
	uदीर्घ tx_ctlerrs;	/* Err of sending ctrl frames */
	uदीर्घ tx_ctlpkts;	/* Ctrl frames sent to करोngle */
	uदीर्घ rx_ctlerrs;	/* Err of processing rx ctrl frames */
	uदीर्घ rx_ctlpkts;	/* Ctrl frames processed from करोngle */
	uदीर्घ rx_पढ़ोahead_cnt;	/* packets where header पढ़ो-ahead was used */
पूर्ण;

/* misc chip info needed by some of the routines */
/* Private data क्रम SDIO bus पूर्णांकeraction */
काष्ठा brcmf_sdio अणु
	काष्ठा brcmf_sdio_dev *sdiodev;	/* sdio device handler */
	काष्ठा brcmf_chip *ci;	/* Chip info काष्ठा */
	काष्ठा brcmf_core *sdio_core; /* sdio core info काष्ठा */

	u32 hostपूर्णांकmask;	/* Copy of Host Interrupt Mask */
	atomic_t पूर्णांकstatus;	/* Intstatus bits (events) pending */
	atomic_t fcstate;	/* State of करोngle flow-control */

	uपूर्णांक blocksize;		/* Block size of SDIO transfers */
	uपूर्णांक roundup;		/* Max roundup limit */

	काष्ठा pktq txq;	/* Queue length used क्रम flow-control */
	u8 flowcontrol;	/* per prio flow control biपंचांगask */
	u8 tx_seq;		/* Transmit sequence number (next) */
	u8 tx_max;		/* Maximum transmit sequence allowed */

	u8 *hdrbuf;		/* buffer क्रम handling rx frame */
	u8 *rxhdr;		/* Header of current rx frame (in hdrbuf) */
	u8 rx_seq;		/* Receive sequence number (expected) */
	काष्ठा brcmf_sdio_hdrinfo cur_पढ़ो;
				/* info of current पढ़ो frame */
	bool rxskip;		/* Skip receive (aरुकोing NAK ACK) */
	bool rxpending;		/* Data frame pending in करोngle */

	uपूर्णांक rxbound;		/* Rx frames to पढ़ो beक्रमe resched */
	uपूर्णांक txbound;		/* Tx frames to send beक्रमe resched */
	uपूर्णांक txminmax;

	काष्ठा sk_buff *glomd;	/* Packet containing glomming descriptor */
	काष्ठा sk_buff_head glom; /* Packet list क्रम glommed superframe */

	u8 *rxbuf;		/* Buffer क्रम receiving control packets */
	uपूर्णांक rxblen;		/* Allocated length of rxbuf */
	u8 *rxctl;		/* Aligned poपूर्णांकer पूर्णांकo rxbuf */
	u8 *rxctl_orig;		/* poपूर्णांकer क्रम मुक्तing rxctl */
	uपूर्णांक rxlen;		/* Length of valid data in buffer */
	spinlock_t rxctl_lock;	/* protection lock क्रम ctrl frame resources */

	u8 sdpcm_ver;	/* Bus protocol reported by करोngle */

	bool पूर्णांकr;		/* Use पूर्णांकerrupts */
	bool poll;		/* Use polling */
	atomic_t ipend;		/* Device पूर्णांकerrupt is pending */
	uपूर्णांक spurious;		/* Count of spurious पूर्णांकerrupts */
	uपूर्णांक pollrate;		/* Ticks between device polls */
	uपूर्णांक polltick;		/* Tick counter */

#अगर_घोषित DEBUG
	uपूर्णांक console_पूर्णांकerval;
	काष्ठा brcmf_console console;	/* Console output polling support */
	uपूर्णांक console_addr;	/* Console address from shared काष्ठा */
#पूर्ण_अगर				/* DEBUG */

	uपूर्णांक clkstate;		/* State of sd and backplane घड़ी(s) */
	s32 idleसमय;		/* Control क्रम activity समयout */
	s32 idlecount;		/* Activity समयout counter */
	s32 idleघड़ी;		/* How to set bus driver when idle */
	bool rxflow_mode;	/* Rx flow control mode */
	bool rxflow;		/* Is rx flow control on */
	bool alp_only;		/* Don't use HT घड़ी (ALP only) */

	u8 *ctrl_frame_buf;
	u16 ctrl_frame_len;
	bool ctrl_frame_stat;
	पूर्णांक ctrl_frame_err;

	spinlock_t txq_lock;		/* protect bus->txq */
	रुको_queue_head_t ctrl_रुको;
	रुको_queue_head_t dcmd_resp_रुको;

	काष्ठा समयr_list समयr;
	काष्ठा completion watchकरोg_रुको;
	काष्ठा task_काष्ठा *watchकरोg_tsk;
	bool wd_active;

	काष्ठा workqueue_काष्ठा *brcmf_wq;
	काष्ठा work_काष्ठा datawork;
	bool dpc_triggered;
	bool dpc_running;

	bool txoff;		/* Transmit flow-controlled */
	काष्ठा brcmf_sdio_count sdcnt;
	bool sr_enabled; /* SaveRestore enabled */
	bool sleeping;

	u8 tx_hdrlen;		/* sdio bus header length क्रम tx packet */
	bool txglom;		/* host tx glomming enable flag */
	u16 head_align;		/* buffer poपूर्णांकer alignment */
	u16 sgentry_align;	/* scatter-gather buffer alignment */
पूर्ण;

/* clkstate */
#घोषणा CLK_NONE	0
#घोषणा CLK_SDONLY	1
#घोषणा CLK_PENDING	2
#घोषणा CLK_AVAIL	3

#अगर_घोषित DEBUG
अटल पूर्णांक qcount[NUMPRIO];
#पूर्ण_अगर				/* DEBUG */

#घोषणा DEFAULT_SDIO_DRIVE_STRENGTH	6	/* in milliamps */

#घोषणा RETRYCHAN(chan) ((chan) == SDPCM_EVENT_CHANNEL)

/* Limit on rounding up frames */
अटल स्थिर uपूर्णांक max_roundup = 512;

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
#घोषणा ALIGNMENT  8
#अन्यथा
#घोषणा ALIGNMENT  4
#पूर्ण_अगर

क्रमागत brcmf_sdio_frmtype अणु
	BRCMF_SDIO_FT_NORMAL,
	BRCMF_SDIO_FT_SUPER,
	BRCMF_SDIO_FT_SUB,
पूर्ण;

#घोषणा SDIOD_DRVSTR_KEY(chip, pmu)     (((chip) << 16) | (pmu))

/* SDIO Pad drive strength to select value mappings */
काष्ठा sdiod_drive_str अणु
	u8 strength;	/* Pad Drive Strength in mA */
	u8 sel;		/* Chip-specअगरic select value */
पूर्ण;

/* SDIO Drive Strength to sel value table क्रम PMU Rev 11 (1.8V) */
अटल स्थिर काष्ठा sdiod_drive_str sdiod_drvstr_tab1_1v8[] = अणु
	अणु32, 0x6पूर्ण,
	अणु26, 0x7पूर्ण,
	अणु22, 0x4पूर्ण,
	अणु16, 0x5पूर्ण,
	अणु12, 0x2पूर्ण,
	अणु8, 0x3पूर्ण,
	अणु4, 0x0पूर्ण,
	अणु0, 0x1पूर्ण
पूर्ण;

/* SDIO Drive Strength to sel value table क्रम PMU Rev 13 (1.8v) */
अटल स्थिर काष्ठा sdiod_drive_str sdiod_drive_strength_tab5_1v8[] = अणु
	अणु6, 0x7पूर्ण,
	अणु5, 0x6पूर्ण,
	अणु4, 0x5पूर्ण,
	अणु3, 0x4पूर्ण,
	अणु2, 0x2पूर्ण,
	अणु1, 0x1पूर्ण,
	अणु0, 0x0पूर्ण
पूर्ण;

/* SDIO Drive Strength to sel value table क्रम PMU Rev 17 (1.8v) */
अटल स्थिर काष्ठा sdiod_drive_str sdiod_drvstr_tab6_1v8[] = अणु
	अणु3, 0x3पूर्ण,
	अणु2, 0x2पूर्ण,
	अणु1, 0x1पूर्ण,
	अणु0, 0x0पूर्ण पूर्ण;

/* SDIO Drive Strength to sel value table क्रम 43143 PMU Rev 17 (3.3V) */
अटल स्थिर काष्ठा sdiod_drive_str sdiod_drvstr_tab2_3v3[] = अणु
	अणु16, 0x7पूर्ण,
	अणु12, 0x5पूर्ण,
	अणु8,  0x3पूर्ण,
	अणु4,  0x1पूर्ण
पूर्ण;

BRCMF_FW_DEF(43143, "brcmfmac43143-sdio");
BRCMF_FW_DEF(43241B0, "brcmfmac43241b0-sdio");
BRCMF_FW_DEF(43241B4, "brcmfmac43241b4-sdio");
BRCMF_FW_DEF(43241B5, "brcmfmac43241b5-sdio");
BRCMF_FW_DEF(4329, "brcmfmac4329-sdio");
BRCMF_FW_DEF(4330, "brcmfmac4330-sdio");
BRCMF_FW_DEF(4334, "brcmfmac4334-sdio");
BRCMF_FW_DEF(43340, "brcmfmac43340-sdio");
BRCMF_FW_DEF(4335, "brcmfmac4335-sdio");
BRCMF_FW_DEF(43362, "brcmfmac43362-sdio");
BRCMF_FW_DEF(4339, "brcmfmac4339-sdio");
BRCMF_FW_DEF(43430A0, "brcmfmac43430a0-sdio");
/* Note the names are not postfixed with a1 क्रम backward compatibility */
BRCMF_FW_DEF(43430A1, "brcmfmac43430-sdio");
BRCMF_FW_DEF(43455, "brcmfmac43455-sdio");
BRCMF_FW_DEF(43456, "brcmfmac43456-sdio");
BRCMF_FW_DEF(4354, "brcmfmac4354-sdio");
BRCMF_FW_DEF(4356, "brcmfmac4356-sdio");
BRCMF_FW_DEF(4359, "brcmfmac4359-sdio");
BRCMF_FW_DEF(4373, "brcmfmac4373-sdio");
BRCMF_FW_DEF(43012, "brcmfmac43012-sdio");

/* firmware config files */
MODULE_FIRMWARE(BRCMF_FW_DEFAULT_PATH "brcm/brcmfmac*-sdio.*.txt");
MODULE_FIRMWARE(BRCMF_FW_DEFAULT_PATH "brcm/brcmfmac*-pcie.*.txt");

अटल स्थिर काष्ठा brcmf_firmware_mapping brcmf_sdio_fwnames[] = अणु
	BRCMF_FW_ENTRY(BRCM_CC_43143_CHIP_ID, 0xFFFFFFFF, 43143),
	BRCMF_FW_ENTRY(BRCM_CC_43241_CHIP_ID, 0x0000001F, 43241B0),
	BRCMF_FW_ENTRY(BRCM_CC_43241_CHIP_ID, 0x00000020, 43241B4),
	BRCMF_FW_ENTRY(BRCM_CC_43241_CHIP_ID, 0xFFFFFFC0, 43241B5),
	BRCMF_FW_ENTRY(BRCM_CC_4329_CHIP_ID, 0xFFFFFFFF, 4329),
	BRCMF_FW_ENTRY(BRCM_CC_4330_CHIP_ID, 0xFFFFFFFF, 4330),
	BRCMF_FW_ENTRY(BRCM_CC_4334_CHIP_ID, 0xFFFFFFFF, 4334),
	BRCMF_FW_ENTRY(BRCM_CC_43340_CHIP_ID, 0xFFFFFFFF, 43340),
	BRCMF_FW_ENTRY(BRCM_CC_43341_CHIP_ID, 0xFFFFFFFF, 43340),
	BRCMF_FW_ENTRY(BRCM_CC_4335_CHIP_ID, 0xFFFFFFFF, 4335),
	BRCMF_FW_ENTRY(BRCM_CC_43362_CHIP_ID, 0xFFFFFFFE, 43362),
	BRCMF_FW_ENTRY(BRCM_CC_4339_CHIP_ID, 0xFFFFFFFF, 4339),
	BRCMF_FW_ENTRY(BRCM_CC_43430_CHIP_ID, 0x00000001, 43430A0),
	BRCMF_FW_ENTRY(BRCM_CC_43430_CHIP_ID, 0xFFFFFFFE, 43430A1),
	BRCMF_FW_ENTRY(BRCM_CC_4345_CHIP_ID, 0x00000200, 43456),
	BRCMF_FW_ENTRY(BRCM_CC_4345_CHIP_ID, 0xFFFFFDC0, 43455),
	BRCMF_FW_ENTRY(BRCM_CC_4354_CHIP_ID, 0xFFFFFFFF, 4354),
	BRCMF_FW_ENTRY(BRCM_CC_4356_CHIP_ID, 0xFFFFFFFF, 4356),
	BRCMF_FW_ENTRY(BRCM_CC_4359_CHIP_ID, 0xFFFFFFFF, 4359),
	BRCMF_FW_ENTRY(CY_CC_4373_CHIP_ID, 0xFFFFFFFF, 4373),
	BRCMF_FW_ENTRY(CY_CC_43012_CHIP_ID, 0xFFFFFFFF, 43012)
पूर्ण;

#घोषणा TXCTL_CREDITS	2

अटल व्योम pkt_align(काष्ठा sk_buff *p, पूर्णांक len, पूर्णांक align)
अणु
	uपूर्णांक datalign;
	datalign = (अचिन्हित दीर्घ)(p->data);
	datalign = roundup(datalign, (align)) - datalign;
	अगर (datalign)
		skb_pull(p, datalign);
	__skb_trim(p, len);
पूर्ण

/* To check अगर there's winकरोw offered */
अटल bool data_ok(काष्ठा brcmf_sdio *bus)
अणु
	u8 tx_rsv = 0;

	/* Reserve TXCTL_CREDITS credits क्रम txctl when it is पढ़ोy to send */
	अगर (bus->ctrl_frame_stat)
		tx_rsv = TXCTL_CREDITS;

	वापस (bus->tx_max - bus->tx_seq - tx_rsv) != 0 &&
	       ((bus->tx_max - bus->tx_seq - tx_rsv) & 0x80) == 0;

पूर्ण

/* To check अगर there's winकरोw offered */
अटल bool txctl_ok(काष्ठा brcmf_sdio *bus)
अणु
	वापस (bus->tx_max - bus->tx_seq) != 0 &&
	       ((bus->tx_max - bus->tx_seq) & 0x80) == 0;
पूर्ण

अटल पूर्णांक
brcmf_sdio_kso_control(काष्ठा brcmf_sdio *bus, bool on)
अणु
	u8 wr_val = 0, rd_val, cmp_val, bmask;
	पूर्णांक err = 0;
	पूर्णांक err_cnt = 0;
	पूर्णांक try_cnt = 0;

	brcmf_dbg(TRACE, "Enter: on=%d\n", on);

	sdio_retune_crc_disable(bus->sdiodev->func1);

	/* Cannot re-tune अगर device is asleep; defer till we're awake */
	अगर (on)
		sdio_retune_hold_now(bus->sdiodev->func1);

	wr_val = (on << SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT);
	/* 1st KSO ग_लिखो goes to AOS wake up core अगर device is asleep  */
	brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, wr_val, &err);

	/* In हाल of 43012 chip, the chip could go करोwn immediately after
	 * KSO bit is cleared. So the further पढ़ोs of KSO रेजिस्टर could
	 * fail. Thereby just bailing out immediately after clearing KSO
	 * bit, to aव्योम polling of KSO bit.
	 */
	अगर (!on && bus->ci->chip == CY_CC_43012_CHIP_ID)
		वापस err;

	अगर (on) अणु
		/* device WAKEUP through KSO:
		 * ग_लिखो bit 0 & पढ़ो back until
		 * both bits 0 (kso bit) & 1 (dev on status) are set
		 */
		cmp_val = SBSDIO_FUNC1_SLEEPCSR_KSO_MASK |
			  SBSDIO_FUNC1_SLEEPCSR_DEVON_MASK;
		bmask = cmp_val;
		usleep_range(2000, 3000);
	पूर्ण अन्यथा अणु
		/* Put device to sleep, turn off KSO */
		cmp_val = 0;
		/* only check क्रम bit0, bit1(dev on status) may not
		 * get cleared right away
		 */
		bmask = SBSDIO_FUNC1_SLEEPCSR_KSO_MASK;
	पूर्ण

	करो अणु
		/* reliable KSO bit set/clr:
		 * the sdiod sleep ग_लिखो access is synced to PMU 32khz clk
		 * just one ग_लिखो attempt may fail,
		 * पढ़ो it back until it matches written value
		 */
		rd_val = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR,
					   &err);
		अगर (!err) अणु
			अगर ((rd_val & bmask) == cmp_val)
				अवरोध;
			err_cnt = 0;
		पूर्ण
		/* bail out upon subsequent access errors */
		अगर (err && (err_cnt++ > BRCMF_SDIO_MAX_ACCESS_ERRORS))
			अवरोध;

		udelay(KSO_WAIT_US);
		brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, wr_val,
				   &err);

	पूर्ण जबतक (try_cnt++ < MAX_KSO_ATTEMPTS);

	अगर (try_cnt > 2)
		brcmf_dbg(SDIO, "try_cnt=%d rd_val=0x%x err=%d\n", try_cnt,
			  rd_val, err);

	अगर (try_cnt > MAX_KSO_ATTEMPTS)
		brcmf_err("max tries: rd_val=0x%x err=%d\n", rd_val, err);

	अगर (on)
		sdio_retune_release(bus->sdiodev->func1);

	sdio_retune_crc_enable(bus->sdiodev->func1);

	वापस err;
पूर्ण

#घोषणा HOSTINTMASK		(I_HMB_SW_MASK | I_CHIPACTIVE)

/* Turn backplane घड़ी on or off */
अटल पूर्णांक brcmf_sdio_htclk(काष्ठा brcmf_sdio *bus, bool on, bool penकरोk)
अणु
	पूर्णांक err;
	u8 clkctl, clkreq, devctl;
	अचिन्हित दीर्घ समयout;

	brcmf_dbg(SDIO, "Enter\n");

	clkctl = 0;

	अगर (bus->sr_enabled) अणु
		bus->clkstate = (on ? CLK_AVAIL : CLK_SDONLY);
		वापस 0;
	पूर्ण

	अगर (on) अणु
		/* Request HT Avail */
		clkreq =
		    bus->alp_only ? SBSDIO_ALP_AVAIL_REQ : SBSDIO_HT_AVAIL_REQ;

		brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				   clkreq, &err);
		अगर (err) अणु
			brcmf_err("HT Avail request error: %d\n", err);
			वापस -EBADE;
		पूर्ण

		/* Check current status */
		clkctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR, &err);
		अगर (err) अणु
			brcmf_err("HT Avail read error: %d\n", err);
			वापस -EBADE;
		पूर्ण

		/* Go to pending and aरुको पूर्णांकerrupt अगर appropriate */
		अगर (!SBSDIO_CLKAV(clkctl, bus->alp_only) && penकरोk) अणु
			/* Allow only घड़ी-available पूर्णांकerrupt */
			devctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			अगर (err) अणु
				brcmf_err("Devctl error setting CA: %d\n", err);
				वापस -EBADE;
			पूर्ण

			devctl |= SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
			brcmf_dbg(SDIO, "CLKCTL: set PENDING\n");
			bus->clkstate = CLK_PENDING;

			वापस 0;
		पूर्ण अन्यथा अगर (bus->clkstate == CLK_PENDING) अणु
			/* Cancel CA-only पूर्णांकerrupt filter */
			devctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
		पूर्ण

		/* Otherwise, रुको here (polling) क्रम HT Avail */
		समयout = jअगरfies +
			  msecs_to_jअगरfies(PMU_MAX_TRANSITION_DLY/1000);
		जबतक (!SBSDIO_CLKAV(clkctl, bus->alp_only)) अणु
			clkctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   &err);
			अगर (समय_after(jअगरfies, समयout))
				अवरोध;
			अन्यथा
				usleep_range(5000, 10000);
		पूर्ण
		अगर (err) अणु
			brcmf_err("HT Avail request error: %d\n", err);
			वापस -EBADE;
		पूर्ण
		अगर (!SBSDIO_CLKAV(clkctl, bus->alp_only)) अणु
			brcmf_err("HT Avail timeout (%d): clkctl 0x%02x\n",
				  PMU_MAX_TRANSITION_DLY, clkctl);
			वापस -EBADE;
		पूर्ण

		/* Mark घड़ी available */
		bus->clkstate = CLK_AVAIL;
		brcmf_dbg(SDIO, "CLKCTL: turned ON\n");

#अगर defined(DEBUG)
		अगर (!bus->alp_only) अणु
			अगर (SBSDIO_ALPONLY(clkctl))
				brcmf_err("HT Clock should be on\n");
		पूर्ण
#पूर्ण_अगर				/* defined (DEBUG) */

	पूर्ण अन्यथा अणु
		clkreq = 0;

		अगर (bus->clkstate == CLK_PENDING) अणु
			/* Cancel CA-only पूर्णांकerrupt filter */
			devctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
		पूर्ण

		bus->clkstate = CLK_SDONLY;
		brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				   clkreq, &err);
		brcmf_dbg(SDIO, "CLKCTL: turned OFF\n");
		अगर (err) अणु
			brcmf_err("Failed access turning clock off: %d\n",
				  err);
			वापस -EBADE;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Change idle/active SD state */
अटल पूर्णांक brcmf_sdio_sdclk(काष्ठा brcmf_sdio *bus, bool on)
अणु
	brcmf_dbg(SDIO, "Enter\n");

	अगर (on)
		bus->clkstate = CLK_SDONLY;
	अन्यथा
		bus->clkstate = CLK_NONE;

	वापस 0;
पूर्ण

/* Transition SD and backplane घड़ी पढ़ोiness */
अटल पूर्णांक brcmf_sdio_clkctl(काष्ठा brcmf_sdio *bus, uपूर्णांक target, bool penकरोk)
अणु
#अगर_घोषित DEBUG
	uपूर्णांक oldstate = bus->clkstate;
#पूर्ण_अगर				/* DEBUG */

	brcmf_dbg(SDIO, "Enter\n");

	/* Early निकास अगर we're alपढ़ोy there */
	अगर (bus->clkstate == target)
		वापस 0;

	चयन (target) अणु
	हाल CLK_AVAIL:
		/* Make sure SD घड़ी is available */
		अगर (bus->clkstate == CLK_NONE)
			brcmf_sdio_sdclk(bus, true);
		/* Now request HT Avail on the backplane */
		brcmf_sdio_htclk(bus, true, penकरोk);
		अवरोध;

	हाल CLK_SDONLY:
		/* Remove HT request, or bring up SD घड़ी */
		अगर (bus->clkstate == CLK_NONE)
			brcmf_sdio_sdclk(bus, true);
		अन्यथा अगर (bus->clkstate == CLK_AVAIL)
			brcmf_sdio_htclk(bus, false, false);
		अन्यथा
			brcmf_err("request for %d -> %d\n",
				  bus->clkstate, target);
		अवरोध;

	हाल CLK_NONE:
		/* Make sure to हटाओ HT request */
		अगर (bus->clkstate == CLK_AVAIL)
			brcmf_sdio_htclk(bus, false, false);
		/* Now हटाओ the SD घड़ी */
		brcmf_sdio_sdclk(bus, false);
		अवरोध;
	पूर्ण
#अगर_घोषित DEBUG
	brcmf_dbg(SDIO, "%d -> %d\n", oldstate, bus->clkstate);
#पूर्ण_अगर				/* DEBUG */

	वापस 0;
पूर्ण

अटल पूर्णांक
brcmf_sdio_bus_sleep(काष्ठा brcmf_sdio *bus, bool sleep, bool penकरोk)
अणु
	पूर्णांक err = 0;
	u8 clkcsr;

	brcmf_dbg(SDIO, "Enter: request %s currently %s\n",
		  (sleep ? "SLEEP" : "WAKE"),
		  (bus->sleeping ? "SLEEP" : "WAKE"));

	/* If SR is enabled control bus state with KSO */
	अगर (bus->sr_enabled) अणु
		/* Done अगर we're alपढ़ोy in the requested state */
		अगर (sleep == bus->sleeping)
			जाओ end;

		/* Going to sleep */
		अगर (sleep) अणु
			clkcsr = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   &err);
			अगर ((clkcsr & SBSDIO_CSR_MASK) == 0) अणु
				brcmf_dbg(SDIO, "no clock, set ALP\n");
				brcmf_sdiod_ग_लिखोb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   SBSDIO_ALP_AVAIL_REQ, &err);
			पूर्ण
			err = brcmf_sdio_kso_control(bus, false);
		पूर्ण अन्यथा अणु
			err = brcmf_sdio_kso_control(bus, true);
		पूर्ण
		अगर (err) अणु
			brcmf_err("error while changing bus sleep state %d\n",
				  err);
			जाओ करोne;
		पूर्ण
	पूर्ण

end:
	/* control घड़ीs */
	अगर (sleep) अणु
		अगर (!bus->sr_enabled)
			brcmf_sdio_clkctl(bus, CLK_NONE, penकरोk);
	पूर्ण अन्यथा अणु
		brcmf_sdio_clkctl(bus, CLK_AVAIL, penकरोk);
		brcmf_sdio_wd_समयr(bus, true);
	पूर्ण
	bus->sleeping = sleep;
	brcmf_dbg(SDIO, "new state %s\n",
		  (sleep ? "SLEEP" : "WAKE"));
करोne:
	brcmf_dbg(SDIO, "Exit: err=%d\n", err);
	वापस err;

पूर्ण

#अगर_घोषित DEBUG
अटल अंतरभूत bool brcmf_sdio_valid_shared_address(u32 addr)
अणु
	वापस !(addr == 0 || ((~addr >> 16) & 0xffff) == (addr & 0xffff));
पूर्ण

अटल पूर्णांक brcmf_sdio_पढ़ोshared(काष्ठा brcmf_sdio *bus,
				 काष्ठा sdpcm_shared *sh)
अणु
	u32 addr = 0;
	पूर्णांक rv;
	u32 shaddr = 0;
	काष्ठा sdpcm_shared_le sh_le;
	__le32 addr_le;

	sdio_claim_host(bus->sdiodev->func1);
	brcmf_sdio_bus_sleep(bus, false, false);

	/*
	 * Read last word in socram to determine
	 * address of sdpcm_shared काष्ठाure
	 */
	shaddr = bus->ci->rambase + bus->ci->ramsize - 4;
	अगर (!bus->ci->rambase && brcmf_chip_sr_capable(bus->ci))
		shaddr -= bus->ci->srsize;
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, shaddr,
			       (u8 *)&addr_le, 4);
	अगर (rv < 0)
		जाओ fail;

	/*
	 * Check अगर addr is valid.
	 * NVRAM length at the end of memory should have been overwritten.
	 */
	addr = le32_to_cpu(addr_le);
	अगर (!brcmf_sdio_valid_shared_address(addr)) अणु
		brcmf_err("invalid sdpcm_shared address 0x%08X\n", addr);
		rv = -EINVAL;
		जाओ fail;
	पूर्ण

	brcmf_dbg(INFO, "sdpcm_shared address 0x%08X\n", addr);

	/* Read hndrte_shared काष्ठाure */
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr, (u8 *)&sh_le,
			       माप(काष्ठा sdpcm_shared_le));
	अगर (rv < 0)
		जाओ fail;

	sdio_release_host(bus->sdiodev->func1);

	/* Endianness */
	sh->flags = le32_to_cpu(sh_le.flags);
	sh->trap_addr = le32_to_cpu(sh_le.trap_addr);
	sh->निश्चित_exp_addr = le32_to_cpu(sh_le.निश्चित_exp_addr);
	sh->निश्चित_file_addr = le32_to_cpu(sh_le.निश्चित_file_addr);
	sh->निश्चित_line = le32_to_cpu(sh_le.निश्चित_line);
	sh->console_addr = le32_to_cpu(sh_le.console_addr);
	sh->msgtrace_addr = le32_to_cpu(sh_le.msgtrace_addr);

	अगर ((sh->flags & SDPCM_SHARED_VERSION_MASK) > SDPCM_SHARED_VERSION) अणु
		brcmf_err("sdpcm shared version unsupported: dhd %d dongle %d\n",
			  SDPCM_SHARED_VERSION,
			  sh->flags & SDPCM_SHARED_VERSION_MASK);
		वापस -EPROTO;
	पूर्ण
	वापस 0;

fail:
	brcmf_err("unable to obtain sdpcm_shared info: rv=%d (addr=0x%x)\n",
		  rv, addr);
	sdio_release_host(bus->sdiodev->func1);
	वापस rv;
पूर्ण

अटल व्योम brcmf_sdio_get_console_addr(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा sdpcm_shared sh;

	अगर (brcmf_sdio_पढ़ोshared(bus, &sh) == 0)
		bus->console_addr = sh.console_addr;
पूर्ण
#अन्यथा
अटल व्योम brcmf_sdio_get_console_addr(काष्ठा brcmf_sdio *bus)
अणु
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल u32 brcmf_sdio_hosपंचांगail(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_sdio_dev *sdiod = bus->sdiodev;
	काष्ठा brcmf_core *core = bus->sdio_core;
	u32 पूर्णांकstatus = 0;
	u32 hmb_data;
	u8 fcbits;
	पूर्णांक ret;

	brcmf_dbg(SDIO, "Enter\n");

	/* Read mailbox data and ack that we did so */
	hmb_data = brcmf_sdiod_पढ़ोl(sdiod,
				     core->base + SD_REG(tohosपंचांगailboxdata),
				     &ret);

	अगर (!ret)
		brcmf_sdiod_ग_लिखोl(sdiod, core->base + SD_REG(tosbmailbox),
				   SMB_INT_ACK, &ret);

	bus->sdcnt.f1regdata += 2;

	/* करोngle indicates the firmware has halted/crashed */
	अगर (hmb_data & HMB_DATA_FWHALT) अणु
		brcmf_dbg(SDIO, "mailbox indicates firmware halted\n");
		brcmf_fw_crashed(&sdiod->func1->dev);
	पूर्ण

	/* Dongle recomposed rx frames, accept them again */
	अगर (hmb_data & HMB_DATA_NAKHANDLED) अणु
		brcmf_dbg(SDIO, "Dongle reports NAK handled, expect rtx of %d\n",
			  bus->rx_seq);
		अगर (!bus->rxskip)
			brcmf_err("unexpected NAKHANDLED!\n");

		bus->rxskip = false;
		पूर्णांकstatus |= I_HMB_FRAME_IND;
	पूर्ण

	/*
	 * DEVREADY करोes not occur with gSPI.
	 */
	अगर (hmb_data & (HMB_DATA_DEVREADY | HMB_DATA_FWREADY)) अणु
		bus->sdpcm_ver =
		    (hmb_data & HMB_DATA_VERSION_MASK) >>
		    HMB_DATA_VERSION_SHIFT;
		अगर (bus->sdpcm_ver != SDPCM_PROT_VERSION)
			brcmf_err("Version mismatch, dongle reports %d, "
				  "expecting %d\n",
				  bus->sdpcm_ver, SDPCM_PROT_VERSION);
		अन्यथा
			brcmf_dbg(SDIO, "Dongle ready, protocol version %d\n",
				  bus->sdpcm_ver);

		/*
		 * Retrieve console state address now that firmware should have
		 * updated it.
		 */
		brcmf_sdio_get_console_addr(bus);
	पूर्ण

	/*
	 * Flow Control has been moved पूर्णांकo the RX headers and this out of band
	 * method isn't used any more.
	 * reमुख्यing backward compatible with older करोngles.
	 */
	अगर (hmb_data & HMB_DATA_FC) अणु
		fcbits = (hmb_data & HMB_DATA_FCDATA_MASK) >>
							HMB_DATA_FCDATA_SHIFT;

		अगर (fcbits & ~bus->flowcontrol)
			bus->sdcnt.fc_xoff++;

		अगर (bus->flowcontrol & ~fcbits)
			bus->sdcnt.fc_xon++;

		bus->sdcnt.fc_rcvd++;
		bus->flowcontrol = fcbits;
	पूर्ण

	/* Shouldn't be any others */
	अगर (hmb_data & ~(HMB_DATA_DEVREADY |
			 HMB_DATA_NAKHANDLED |
			 HMB_DATA_FC |
			 HMB_DATA_FWREADY |
			 HMB_DATA_FWHALT |
			 HMB_DATA_FCDATA_MASK | HMB_DATA_VERSION_MASK))
		brcmf_err("Unknown mailbox data content: 0x%02x\n",
			  hmb_data);

	वापस पूर्णांकstatus;
पूर्ण

अटल व्योम brcmf_sdio_rxfail(काष्ठा brcmf_sdio *bus, bool पात, bool rtx)
अणु
	काष्ठा brcmf_sdio_dev *sdiod = bus->sdiodev;
	काष्ठा brcmf_core *core = bus->sdio_core;
	uपूर्णांक retries = 0;
	u16 lastrbc;
	u8 hi, lo;
	पूर्णांक err;

	brcmf_err("%sterminate frame%s\n",
		  पात ? "abort command, " : "",
		  rtx ? ", send NAK" : "");

	अगर (पात)
		brcmf_sdiod_पात(bus->sdiodev, bus->sdiodev->func2);

	brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_FRAMECTRL, SFC_RF_TERM,
			   &err);
	bus->sdcnt.f1regdata++;

	/* Wait until the packet has been flushed (device/FIFO stable) */
	क्रम (lastrbc = retries = 0xffff; retries > 0; retries--) अणु
		hi = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_FUNC1_RFRAMEBCHI,
				       &err);
		lo = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_FUNC1_RFRAMEBCLO,
				       &err);
		bus->sdcnt.f1regdata += 2;

		अगर ((hi == 0) && (lo == 0))
			अवरोध;

		अगर ((hi > (lastrbc >> 8)) && (lo > (lastrbc & 0x00ff))) अणु
			brcmf_err("count growing: last 0x%04x now 0x%04x\n",
				  lastrbc, (hi << 8) + lo);
		पूर्ण
		lastrbc = (hi << 8) + lo;
	पूर्ण

	अगर (!retries)
		brcmf_err("count never zeroed: last 0x%04x\n", lastrbc);
	अन्यथा
		brcmf_dbg(SDIO, "flush took %d iterations\n", 0xffff - retries);

	अगर (rtx) अणु
		bus->sdcnt.rxrtx++;
		brcmf_sdiod_ग_लिखोl(sdiod, core->base + SD_REG(tosbmailbox),
				   SMB_NAK, &err);

		bus->sdcnt.f1regdata++;
		अगर (err == 0)
			bus->rxskip = true;
	पूर्ण

	/* Clear partial in any हाल */
	bus->cur_पढ़ो.len = 0;
पूर्ण

अटल व्योम brcmf_sdio_txfail(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev = bus->sdiodev;
	u8 i, hi, lo;

	/* On failure, पात the command and terminate the frame */
	brcmf_err("sdio error, abort command and terminate frame\n");
	bus->sdcnt.tx_sderrs++;

	brcmf_sdiod_पात(sdiodev, sdiodev->func2);
	brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_FRAMECTRL, SFC_WF_TERM, शून्य);
	bus->sdcnt.f1regdata++;

	क्रम (i = 0; i < 3; i++) अणु
		hi = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_WFRAMEBCHI, शून्य);
		lo = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_WFRAMEBCLO, शून्य);
		bus->sdcnt.f1regdata += 2;
		अगर ((hi == 0) && (lo == 0))
			अवरोध;
	पूर्ण
पूर्ण

/* वापस total length of buffer chain */
अटल uपूर्णांक brcmf_sdio_glom_len(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा sk_buff *p;
	uपूर्णांक total;

	total = 0;
	skb_queue_walk(&bus->glom, p)
		total += p->len;
	वापस total;
पूर्ण

अटल व्योम brcmf_sdio_मुक्त_glom(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा sk_buff *cur, *next;

	skb_queue_walk_safe(&bus->glom, cur, next) अणु
		skb_unlink(cur, &bus->glom);
		brcmu_pkt_buf_मुक्त_skb(cur);
	पूर्ण
पूर्ण

/**
 * brcmfmac sdio bus specअगरic header
 * This is the lowest layer header wrapped on the packets transmitted between
 * host and WiFi करोngle which contains inक्रमmation needed क्रम SDIO core and
 * firmware
 *
 * It consists of 3 parts: hardware header, hardware extension header and
 * software header
 * hardware header (frame tag) - 4 bytes
 * Byte 0~1: Frame length
 * Byte 2~3: Checksum, bit-wise inverse of frame length
 * hardware extension header - 8 bytes
 * Tx glom mode only, N/A क्रम Rx or normal Tx
 * Byte 0~1: Packet length excluding hw frame tag
 * Byte 2: Reserved
 * Byte 3: Frame flags, bit 0: last frame indication
 * Byte 4~5: Reserved
 * Byte 6~7: Tail padding length
 * software header - 8 bytes
 * Byte 0: Rx/Tx sequence number
 * Byte 1: 4 MSB Channel number, 4 LSB arbitrary flag
 * Byte 2: Length of next data frame, reserved क्रम Tx
 * Byte 3: Data offset
 * Byte 4: Flow control bits, reserved क्रम Tx
 * Byte 5: Maximum Sequence number allowed by firmware क्रम Tx, N/A क्रम Tx packet
 * Byte 6~7: Reserved
 */
#घोषणा SDPCM_HWHDR_LEN			4
#घोषणा SDPCM_HWEXT_LEN			8
#घोषणा SDPCM_SWHDR_LEN			8
#घोषणा SDPCM_HDRLEN			(SDPCM_HWHDR_LEN + SDPCM_SWHDR_LEN)
/* software header */
#घोषणा SDPCM_SEQ_MASK			0x000000ff
#घोषणा SDPCM_SEQ_WRAP			256
#घोषणा SDPCM_CHANNEL_MASK		0x00000f00
#घोषणा SDPCM_CHANNEL_SHIFT		8
#घोषणा SDPCM_CONTROL_CHANNEL		0	/* Control */
#घोषणा SDPCM_EVENT_CHANNEL		1	/* Asyc Event Indication */
#घोषणा SDPCM_DATA_CHANNEL		2	/* Data Xmit/Recv */
#घोषणा SDPCM_GLOM_CHANNEL		3	/* Coalesced packets */
#घोषणा SDPCM_TEST_CHANNEL		15	/* Test/debug packets */
#घोषणा SDPCM_GLOMDESC(p)		(((u8 *)p)[1] & 0x80)
#घोषणा SDPCM_NEXTLEN_MASK		0x00ff0000
#घोषणा SDPCM_NEXTLEN_SHIFT		16
#घोषणा SDPCM_DOFFSET_MASK		0xff000000
#घोषणा SDPCM_DOFFSET_SHIFT		24
#घोषणा SDPCM_FCMASK_MASK		0x000000ff
#घोषणा SDPCM_WINDOW_MASK		0x0000ff00
#घोषणा SDPCM_WINDOW_SHIFT		8

अटल अंतरभूत u8 brcmf_sdio_getdम_से_भfset(u8 *swheader)
अणु
	u32 hdrvalue;
	hdrvalue = le32_to_cpu(*(__le32 *)swheader);
	वापस (u8)((hdrvalue & SDPCM_DOFFSET_MASK) >> SDPCM_DOFFSET_SHIFT);
पूर्ण

अटल अंतरभूत bool brcmf_sdio_fromevntchan(u8 *swheader)
अणु
	u32 hdrvalue;
	u8 ret;

	hdrvalue = le32_to_cpu(*(__le32 *)swheader);
	ret = (u8)((hdrvalue & SDPCM_CHANNEL_MASK) >> SDPCM_CHANNEL_SHIFT);

	वापस (ret == SDPCM_EVENT_CHANNEL);
पूर्ण

अटल पूर्णांक brcmf_sdio_hdparse(काष्ठा brcmf_sdio *bus, u8 *header,
			      काष्ठा brcmf_sdio_hdrinfo *rd,
			      क्रमागत brcmf_sdio_frmtype type)
अणु
	u16 len, checksum;
	u8 rx_seq, fc, tx_seq_max;
	u32 swheader;

	trace_brcmf_sdpcm_hdr(SDPCM_RX, header);

	/* hw header */
	len = get_unaligned_le16(header);
	checksum = get_unaligned_le16(header + माप(u16));
	/* All zero means no more to पढ़ो */
	अगर (!(len | checksum)) अणु
		bus->rxpending = false;
		वापस -ENODATA;
	पूर्ण
	अगर ((u16)(~(len ^ checksum))) अणु
		brcmf_err("HW header checksum error\n");
		bus->sdcnt.rx_badhdr++;
		brcmf_sdio_rxfail(bus, false, false);
		वापस -EIO;
	पूर्ण
	अगर (len < SDPCM_HDRLEN) अणु
		brcmf_err("HW header length error\n");
		वापस -EPROTO;
	पूर्ण
	अगर (type == BRCMF_SDIO_FT_SUPER &&
	    (roundup(len, bus->blocksize) != rd->len)) अणु
		brcmf_err("HW superframe header length error\n");
		वापस -EPROTO;
	पूर्ण
	अगर (type == BRCMF_SDIO_FT_SUB && len > rd->len) अणु
		brcmf_err("HW subframe header length error\n");
		वापस -EPROTO;
	पूर्ण
	rd->len = len;

	/* software header */
	header += SDPCM_HWHDR_LEN;
	swheader = le32_to_cpu(*(__le32 *)header);
	अगर (type == BRCMF_SDIO_FT_SUPER && SDPCM_GLOMDESC(header)) अणु
		brcmf_err("Glom descriptor found in superframe head\n");
		rd->len = 0;
		वापस -EINVAL;
	पूर्ण
	rx_seq = (u8)(swheader & SDPCM_SEQ_MASK);
	rd->channel = (swheader & SDPCM_CHANNEL_MASK) >> SDPCM_CHANNEL_SHIFT;
	अगर (len > MAX_RX_DATASZ && rd->channel != SDPCM_CONTROL_CHANNEL &&
	    type != BRCMF_SDIO_FT_SUPER) अणु
		brcmf_err("HW header length too long\n");
		bus->sdcnt.rx_tooदीर्घ++;
		brcmf_sdio_rxfail(bus, false, false);
		rd->len = 0;
		वापस -EPROTO;
	पूर्ण
	अगर (type == BRCMF_SDIO_FT_SUPER && rd->channel != SDPCM_GLOM_CHANNEL) अणु
		brcmf_err("Wrong channel for superframe\n");
		rd->len = 0;
		वापस -EINVAL;
	पूर्ण
	अगर (type == BRCMF_SDIO_FT_SUB && rd->channel != SDPCM_DATA_CHANNEL &&
	    rd->channel != SDPCM_EVENT_CHANNEL) अणु
		brcmf_err("Wrong channel for subframe\n");
		rd->len = 0;
		वापस -EINVAL;
	पूर्ण
	rd->dat_offset = brcmf_sdio_getdम_से_भfset(header);
	अगर (rd->dat_offset < SDPCM_HDRLEN || rd->dat_offset > rd->len) अणु
		brcmf_err("seq %d: bad data offset\n", rx_seq);
		bus->sdcnt.rx_badhdr++;
		brcmf_sdio_rxfail(bus, false, false);
		rd->len = 0;
		वापस -ENXIO;
	पूर्ण
	अगर (rd->seq_num != rx_seq) अणु
		brcmf_dbg(SDIO, "seq %d, expected %d\n", rx_seq, rd->seq_num);
		bus->sdcnt.rx_badseq++;
		rd->seq_num = rx_seq;
	पूर्ण
	/* no need to check the reset क्रम subframe */
	अगर (type == BRCMF_SDIO_FT_SUB)
		वापस 0;
	rd->len_nxtfrm = (swheader & SDPCM_NEXTLEN_MASK) >> SDPCM_NEXTLEN_SHIFT;
	अगर (rd->len_nxtfrm << 4 > MAX_RX_DATASZ) अणु
		/* only warm क्रम NON glom packet */
		अगर (rd->channel != SDPCM_GLOM_CHANNEL)
			brcmf_err("seq %d: next length error\n", rx_seq);
		rd->len_nxtfrm = 0;
	पूर्ण
	swheader = le32_to_cpu(*(__le32 *)(header + 4));
	fc = swheader & SDPCM_FCMASK_MASK;
	अगर (bus->flowcontrol != fc) अणु
		अगर (~bus->flowcontrol & fc)
			bus->sdcnt.fc_xoff++;
		अगर (bus->flowcontrol & ~fc)
			bus->sdcnt.fc_xon++;
		bus->sdcnt.fc_rcvd++;
		bus->flowcontrol = fc;
	पूर्ण
	tx_seq_max = (swheader & SDPCM_WINDOW_MASK) >> SDPCM_WINDOW_SHIFT;
	अगर ((u8)(tx_seq_max - bus->tx_seq) > 0x40) अणु
		brcmf_err("seq %d: max tx seq number error\n", rx_seq);
		tx_seq_max = bus->tx_seq + 2;
	पूर्ण
	bus->tx_max = tx_seq_max;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम brcmf_sdio_update_hwhdr(u8 *header, u16 frm_length)
अणु
	*(__le16 *)header = cpu_to_le16(frm_length);
	*(((__le16 *)header) + 1) = cpu_to_le16(~frm_length);
पूर्ण

अटल व्योम brcmf_sdio_hdpack(काष्ठा brcmf_sdio *bus, u8 *header,
			      काष्ठा brcmf_sdio_hdrinfo *hd_info)
अणु
	u32 hdrval;
	u8 hdr_offset;

	brcmf_sdio_update_hwhdr(header, hd_info->len);
	hdr_offset = SDPCM_HWHDR_LEN;

	अगर (bus->txglom) अणु
		hdrval = (hd_info->len - hdr_offset) | (hd_info->lastfrm << 24);
		*((__le32 *)(header + hdr_offset)) = cpu_to_le32(hdrval);
		hdrval = (u16)hd_info->tail_pad << 16;
		*(((__le32 *)(header + hdr_offset)) + 1) = cpu_to_le32(hdrval);
		hdr_offset += SDPCM_HWEXT_LEN;
	पूर्ण

	hdrval = hd_info->seq_num;
	hdrval |= (hd_info->channel << SDPCM_CHANNEL_SHIFT) &
		  SDPCM_CHANNEL_MASK;
	hdrval |= (hd_info->dat_offset << SDPCM_DOFFSET_SHIFT) &
		  SDPCM_DOFFSET_MASK;
	*((__le32 *)(header + hdr_offset)) = cpu_to_le32(hdrval);
	*(((__le32 *)(header + hdr_offset)) + 1) = 0;
	trace_brcmf_sdpcm_hdr(SDPCM_TX + !!(bus->txglom), header);
पूर्ण

अटल u8 brcmf_sdio_rxglom(काष्ठा brcmf_sdio *bus, u8 rxseq)
अणु
	u16 dlen, totlen;
	u8 *dptr, num = 0;
	u16 sublen;
	काष्ठा sk_buff *pfirst, *pnext;

	पूर्णांक errcode;
	u8 करोff;

	काष्ठा brcmf_sdio_hdrinfo rd_new;

	/* If packets, issue पढ़ो(s) and send up packet chain */
	/* Return sequence numbers consumed? */

	brcmf_dbg(SDIO, "start: glomd %p glom %p\n",
		  bus->glomd, skb_peek(&bus->glom));

	/* If there's a descriptor, generate the packet chain */
	अगर (bus->glomd) अणु
		pfirst = pnext = शून्य;
		dlen = (u16) (bus->glomd->len);
		dptr = bus->glomd->data;
		अगर (!dlen || (dlen & 1)) अणु
			brcmf_err("bad glomd len(%d), ignore descriptor\n",
				  dlen);
			dlen = 0;
		पूर्ण

		क्रम (totlen = num = 0; dlen; num++) अणु
			/* Get (and move past) next length */
			sublen = get_unaligned_le16(dptr);
			dlen -= माप(u16);
			dptr += माप(u16);
			अगर ((sublen < SDPCM_HDRLEN) ||
			    ((num == 0) && (sublen < (2 * SDPCM_HDRLEN)))) अणु
				brcmf_err("descriptor len %d bad: %d\n",
					  num, sublen);
				pnext = शून्य;
				अवरोध;
			पूर्ण
			अगर (sublen % bus->sgentry_align) अणु
				brcmf_err("sublen %d not multiple of %d\n",
					  sublen, bus->sgentry_align);
			पूर्ण
			totlen += sublen;

			/* For last frame, adjust पढ़ो len so total
				 is a block multiple */
			अगर (!dlen) अणु
				sublen +=
				    (roundup(totlen, bus->blocksize) - totlen);
				totlen = roundup(totlen, bus->blocksize);
			पूर्ण

			/* Allocate/chain packet क्रम next subframe */
			pnext = brcmu_pkt_buf_get_skb(sublen + bus->sgentry_align);
			अगर (pnext == शून्य) अणु
				brcmf_err("bcm_pkt_buf_get_skb failed, num %d len %d\n",
					  num, sublen);
				अवरोध;
			पूर्ण
			skb_queue_tail(&bus->glom, pnext);

			/* Adhere to start alignment requirements */
			pkt_align(pnext, sublen, bus->sgentry_align);
		पूर्ण

		/* If all allocations succeeded, save packet chain
			 in bus काष्ठाure */
		अगर (pnext) अणु
			brcmf_dbg(GLOM, "allocated %d-byte packet chain for %d subframes\n",
				  totlen, num);
			अगर (BRCMF_GLOM_ON() && bus->cur_पढ़ो.len &&
			    totlen != bus->cur_पढ़ो.len) अणु
				brcmf_dbg(GLOM, "glomdesc mismatch: nextlen %d glomdesc %d rxseq %d\n",
					  bus->cur_पढ़ो.len, totlen, rxseq);
			पूर्ण
			pfirst = pnext = शून्य;
		पूर्ण अन्यथा अणु
			brcmf_sdio_मुक्त_glom(bus);
			num = 0;
		पूर्ण

		/* Done with descriptor packet */
		brcmu_pkt_buf_मुक्त_skb(bus->glomd);
		bus->glomd = शून्य;
		bus->cur_पढ़ो.len = 0;
	पूर्ण

	/* Ok -- either we just generated a packet chain,
		 or had one from beक्रमe */
	अगर (!skb_queue_empty(&bus->glom)) अणु
		अगर (BRCMF_GLOM_ON()) अणु
			brcmf_dbg(GLOM, "try superframe read, packet chain:\n");
			skb_queue_walk(&bus->glom, pnext) अणु
				brcmf_dbg(GLOM, "    %p: %p len 0x%04x (%d)\n",
					  pnext, (u8 *) (pnext->data),
					  pnext->len, pnext->len);
			पूर्ण
		पूर्ण

		pfirst = skb_peek(&bus->glom);
		dlen = (u16) brcmf_sdio_glom_len(bus);

		/* Do an SDIO पढ़ो क्रम the superframe.  Configurable iovar to
		 * पढ़ो directly पूर्णांकo the chained packet, or allocate a large
		 * packet and and copy पूर्णांकo the chain.
		 */
		sdio_claim_host(bus->sdiodev->func1);
		errcode = brcmf_sdiod_recv_chain(bus->sdiodev,
						 &bus->glom, dlen);
		sdio_release_host(bus->sdiodev->func1);
		bus->sdcnt.f2rxdata++;

		/* On failure, समाप्त the superframe */
		अगर (errcode < 0) अणु
			brcmf_err("glom read of %d bytes failed: %d\n",
				  dlen, errcode);

			sdio_claim_host(bus->sdiodev->func1);
			brcmf_sdio_rxfail(bus, true, false);
			bus->sdcnt.rxglomfail++;
			brcmf_sdio_मुक्त_glom(bus);
			sdio_release_host(bus->sdiodev->func1);
			वापस 0;
		पूर्ण

		brcmf_dbg_hex_dump(BRCMF_GLOM_ON(),
				   pfirst->data, min_t(पूर्णांक, pfirst->len, 48),
				   "SUPERFRAME:\n");

		rd_new.seq_num = rxseq;
		rd_new.len = dlen;
		sdio_claim_host(bus->sdiodev->func1);
		errcode = brcmf_sdio_hdparse(bus, pfirst->data, &rd_new,
					     BRCMF_SDIO_FT_SUPER);
		sdio_release_host(bus->sdiodev->func1);
		bus->cur_पढ़ो.len = rd_new.len_nxtfrm << 4;

		/* Remove superframe header, remember offset */
		skb_pull(pfirst, rd_new.dat_offset);
		num = 0;

		/* Validate all the subframe headers */
		skb_queue_walk(&bus->glom, pnext) अणु
			/* leave when invalid subframe is found */
			अगर (errcode)
				अवरोध;

			rd_new.len = pnext->len;
			rd_new.seq_num = rxseq++;
			sdio_claim_host(bus->sdiodev->func1);
			errcode = brcmf_sdio_hdparse(bus, pnext->data, &rd_new,
						     BRCMF_SDIO_FT_SUB);
			sdio_release_host(bus->sdiodev->func1);
			brcmf_dbg_hex_dump(BRCMF_GLOM_ON(),
					   pnext->data, 32, "subframe:\n");

			num++;
		पूर्ण

		अगर (errcode) अणु
			/* Terminate frame on error */
			sdio_claim_host(bus->sdiodev->func1);
			brcmf_sdio_rxfail(bus, true, false);
			bus->sdcnt.rxglomfail++;
			brcmf_sdio_मुक्त_glom(bus);
			sdio_release_host(bus->sdiodev->func1);
			bus->cur_पढ़ो.len = 0;
			वापस 0;
		पूर्ण

		/* Basic SD framing looks ok - process each packet (header) */

		skb_queue_walk_safe(&bus->glom, pfirst, pnext) अणु
			dptr = (u8 *) (pfirst->data);
			sublen = get_unaligned_le16(dptr);
			करोff = brcmf_sdio_getdम_से_भfset(&dptr[SDPCM_HWHDR_LEN]);

			brcmf_dbg_hex_dump(BRCMF_BYTES_ON() && BRCMF_DATA_ON(),
					   dptr, pfirst->len,
					   "Rx Subframe Data:\n");

			__skb_trim(pfirst, sublen);
			skb_pull(pfirst, करोff);

			अगर (pfirst->len == 0) अणु
				skb_unlink(pfirst, &bus->glom);
				brcmu_pkt_buf_मुक्त_skb(pfirst);
				जारी;
			पूर्ण

			brcmf_dbg_hex_dump(BRCMF_GLOM_ON(),
					   pfirst->data,
					   min_t(पूर्णांक, pfirst->len, 32),
					   "subframe %d to stack, %p (%p/%d) nxt/lnk %p/%p\n",
					   bus->glom.qlen, pfirst, pfirst->data,
					   pfirst->len, pfirst->next,
					   pfirst->prev);
			skb_unlink(pfirst, &bus->glom);
			अगर (brcmf_sdio_fromevntchan(&dptr[SDPCM_HWHDR_LEN]))
				brcmf_rx_event(bus->sdiodev->dev, pfirst);
			अन्यथा
				brcmf_rx_frame(bus->sdiodev->dev, pfirst,
					       false, false);
			bus->sdcnt.rxglompkts++;
		पूर्ण

		bus->sdcnt.rxglomframes++;
	पूर्ण
	वापस num;
पूर्ण

अटल पूर्णांक brcmf_sdio_dcmd_resp_रुको(काष्ठा brcmf_sdio *bus, uपूर्णांक *condition,
				     bool *pending)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक समयout = DCMD_RESP_TIMEOUT;

	/* Wait until control frame is available */
	add_रुको_queue(&bus->dcmd_resp_रुको, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);

	जबतक (!(*condition) && (!संकेत_pending(current) && समयout))
		समयout = schedule_समयout(समयout);

	अगर (संकेत_pending(current))
		*pending = true;

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&bus->dcmd_resp_रुको, &रुको);

	वापस समयout;
पूर्ण

अटल पूर्णांक brcmf_sdio_dcmd_resp_wake(काष्ठा brcmf_sdio *bus)
अणु
	wake_up_पूर्णांकerruptible(&bus->dcmd_resp_रुको);

	वापस 0;
पूर्ण
अटल व्योम
brcmf_sdio_पढ़ो_control(काष्ठा brcmf_sdio *bus, u8 *hdr, uपूर्णांक len, uपूर्णांक करोff)
अणु
	uपूर्णांक rdlen, pad;
	u8 *buf = शून्य, *rbuf;
	पूर्णांक sdret;

	brcmf_dbg(SDIO, "Enter\n");
	अगर (bus->rxblen)
		buf = vzalloc(bus->rxblen);
	अगर (!buf)
		जाओ करोne;

	rbuf = bus->rxbuf;
	pad = ((अचिन्हित दीर्घ)rbuf % bus->head_align);
	अगर (pad)
		rbuf += (bus->head_align - pad);

	/* Copy the alपढ़ोy-पढ़ो portion over */
	स_नकल(buf, hdr, BRCMF_FIRSTREAD);
	अगर (len <= BRCMF_FIRSTREAD)
		जाओ gotpkt;

	/* Raise rdlen to next SDIO block to aव्योम tail command */
	rdlen = len - BRCMF_FIRSTREAD;
	अगर (bus->roundup && bus->blocksize && (rdlen > bus->blocksize)) अणु
		pad = bus->blocksize - (rdlen % bus->blocksize);
		अगर ((pad <= bus->roundup) && (pad < bus->blocksize) &&
		    ((len + pad) < bus->sdiodev->bus_अगर->maxctl))
			rdlen += pad;
	पूर्ण अन्यथा अगर (rdlen % bus->head_align) अणु
		rdlen += bus->head_align - (rdlen % bus->head_align);
	पूर्ण

	/* Drop अगर the पढ़ो is too big or it exceeds our maximum */
	अगर ((rdlen + BRCMF_FIRSTREAD) > bus->sdiodev->bus_अगर->maxctl) अणु
		brcmf_err("%d-byte control read exceeds %d-byte buffer\n",
			  rdlen, bus->sdiodev->bus_अगर->maxctl);
		brcmf_sdio_rxfail(bus, false, false);
		जाओ करोne;
	पूर्ण

	अगर ((len - करोff) > bus->sdiodev->bus_अगर->maxctl) अणु
		brcmf_err("%d-byte ctl frame (%d-byte ctl data) exceeds %d-byte limit\n",
			  len, len - करोff, bus->sdiodev->bus_अगर->maxctl);
		bus->sdcnt.rx_tooदीर्घ++;
		brcmf_sdio_rxfail(bus, false, false);
		जाओ करोne;
	पूर्ण

	/* Read reमुख्य of frame body */
	sdret = brcmf_sdiod_recv_buf(bus->sdiodev, rbuf, rdlen);
	bus->sdcnt.f2rxdata++;

	/* Control frame failures need retransmission */
	अगर (sdret < 0) अणु
		brcmf_err("read %d control bytes failed: %d\n",
			  rdlen, sdret);
		bus->sdcnt.rxc_errors++;
		brcmf_sdio_rxfail(bus, true, true);
		जाओ करोne;
	पूर्ण अन्यथा
		स_नकल(buf + BRCMF_FIRSTREAD, rbuf, rdlen);

gotpkt:

	brcmf_dbg_hex_dump(BRCMF_BYTES_ON() && BRCMF_CTL_ON(),
			   buf, len, "RxCtrl:\n");

	/* Poपूर्णांक to valid data and indicate its length */
	spin_lock_bh(&bus->rxctl_lock);
	अगर (bus->rxctl) अणु
		brcmf_err("last control frame is being processed.\n");
		spin_unlock_bh(&bus->rxctl_lock);
		vमुक्त(buf);
		जाओ करोne;
	पूर्ण
	bus->rxctl = buf + करोff;
	bus->rxctl_orig = buf;
	bus->rxlen = len - करोff;
	spin_unlock_bh(&bus->rxctl_lock);

करोne:
	/* Awake any रुकोers */
	brcmf_sdio_dcmd_resp_wake(bus);
पूर्ण

/* Pad पढ़ो to blocksize क्रम efficiency */
अटल व्योम brcmf_sdio_pad(काष्ठा brcmf_sdio *bus, u16 *pad, u16 *rdlen)
अणु
	अगर (bus->roundup && bus->blocksize && *rdlen > bus->blocksize) अणु
		*pad = bus->blocksize - (*rdlen % bus->blocksize);
		अगर (*pad <= bus->roundup && *pad < bus->blocksize &&
		    *rdlen + *pad + BRCMF_FIRSTREAD < MAX_RX_DATASZ)
			*rdlen += *pad;
	पूर्ण अन्यथा अगर (*rdlen % bus->head_align) अणु
		*rdlen += bus->head_align - (*rdlen % bus->head_align);
	पूर्ण
पूर्ण

अटल uपूर्णांक brcmf_sdio_पढ़ोframes(काष्ठा brcmf_sdio *bus, uपूर्णांक maxframes)
अणु
	काष्ठा sk_buff *pkt;		/* Packet क्रम event or data frames */
	u16 pad;		/* Number of pad bytes to पढ़ो */
	uपूर्णांक rxleft = 0;	/* Reमुख्यing number of frames allowed */
	पूर्णांक ret;		/* Return code from calls */
	uपूर्णांक rxcount = 0;	/* Total frames पढ़ो */
	काष्ठा brcmf_sdio_hdrinfo *rd = &bus->cur_पढ़ो, rd_new;
	u8 head_पढ़ो = 0;

	brcmf_dbg(SDIO, "Enter\n");

	/* Not finished unless we encounter no more frames indication */
	bus->rxpending = true;

	क्रम (rd->seq_num = bus->rx_seq, rxleft = maxframes;
	     !bus->rxskip && rxleft && bus->sdiodev->state == BRCMF_SDIOD_DATA;
	     rd->seq_num++, rxleft--) अणु

		/* Handle glomming separately */
		अगर (bus->glomd || !skb_queue_empty(&bus->glom)) अणु
			u8 cnt;
			brcmf_dbg(GLOM, "calling rxglom: glomd %p, glom %p\n",
				  bus->glomd, skb_peek(&bus->glom));
			cnt = brcmf_sdio_rxglom(bus, rd->seq_num);
			brcmf_dbg(GLOM, "rxglom returned %d\n", cnt);
			rd->seq_num += cnt - 1;
			rxleft = (rxleft > cnt) ? (rxleft - cnt) : 1;
			जारी;
		पूर्ण

		rd->len_left = rd->len;
		/* पढ़ो header first क्रम unknow frame length */
		sdio_claim_host(bus->sdiodev->func1);
		अगर (!rd->len) अणु
			ret = brcmf_sdiod_recv_buf(bus->sdiodev,
						   bus->rxhdr, BRCMF_FIRSTREAD);
			bus->sdcnt.f2rxhdrs++;
			अगर (ret < 0) अणु
				brcmf_err("RXHEADER FAILED: %d\n",
					  ret);
				bus->sdcnt.rx_hdrfail++;
				brcmf_sdio_rxfail(bus, true, true);
				sdio_release_host(bus->sdiodev->func1);
				जारी;
			पूर्ण

			brcmf_dbg_hex_dump(BRCMF_BYTES_ON() || BRCMF_HDRS_ON(),
					   bus->rxhdr, SDPCM_HDRLEN,
					   "RxHdr:\n");

			अगर (brcmf_sdio_hdparse(bus, bus->rxhdr, rd,
					       BRCMF_SDIO_FT_NORMAL)) अणु
				sdio_release_host(bus->sdiodev->func1);
				अगर (!bus->rxpending)
					अवरोध;
				अन्यथा
					जारी;
			पूर्ण

			अगर (rd->channel == SDPCM_CONTROL_CHANNEL) अणु
				brcmf_sdio_पढ़ो_control(bus, bus->rxhdr,
							rd->len,
							rd->dat_offset);
				/* prepare the descriptor क्रम the next पढ़ो */
				rd->len = rd->len_nxtfrm << 4;
				rd->len_nxtfrm = 0;
				/* treat all packet as event अगर we करोn't know */
				rd->channel = SDPCM_EVENT_CHANNEL;
				sdio_release_host(bus->sdiodev->func1);
				जारी;
			पूर्ण
			rd->len_left = rd->len > BRCMF_FIRSTREAD ?
				       rd->len - BRCMF_FIRSTREAD : 0;
			head_पढ़ो = BRCMF_FIRSTREAD;
		पूर्ण

		brcmf_sdio_pad(bus, &pad, &rd->len_left);

		pkt = brcmu_pkt_buf_get_skb(rd->len_left + head_पढ़ो +
					    bus->head_align);
		अगर (!pkt) अणु
			/* Give up on data, request rtx of events */
			brcmf_err("brcmu_pkt_buf_get_skb failed\n");
			brcmf_sdio_rxfail(bus, false,
					    RETRYCHAN(rd->channel));
			sdio_release_host(bus->sdiodev->func1);
			जारी;
		पूर्ण
		skb_pull(pkt, head_पढ़ो);
		pkt_align(pkt, rd->len_left, bus->head_align);

		ret = brcmf_sdiod_recv_pkt(bus->sdiodev, pkt);
		bus->sdcnt.f2rxdata++;
		sdio_release_host(bus->sdiodev->func1);

		अगर (ret < 0) अणु
			brcmf_err("read %d bytes from channel %d failed: %d\n",
				  rd->len, rd->channel, ret);
			brcmu_pkt_buf_मुक्त_skb(pkt);
			sdio_claim_host(bus->sdiodev->func1);
			brcmf_sdio_rxfail(bus, true,
					    RETRYCHAN(rd->channel));
			sdio_release_host(bus->sdiodev->func1);
			जारी;
		पूर्ण

		अगर (head_पढ़ो) अणु
			skb_push(pkt, head_पढ़ो);
			स_नकल(pkt->data, bus->rxhdr, head_पढ़ो);
			head_पढ़ो = 0;
		पूर्ण अन्यथा अणु
			स_नकल(bus->rxhdr, pkt->data, SDPCM_HDRLEN);
			rd_new.seq_num = rd->seq_num;
			sdio_claim_host(bus->sdiodev->func1);
			अगर (brcmf_sdio_hdparse(bus, bus->rxhdr, &rd_new,
					       BRCMF_SDIO_FT_NORMAL)) अणु
				rd->len = 0;
				brcmf_sdio_rxfail(bus, true, true);
				sdio_release_host(bus->sdiodev->func1);
				brcmu_pkt_buf_मुक्त_skb(pkt);
				जारी;
			पूर्ण
			bus->sdcnt.rx_पढ़ोahead_cnt++;
			अगर (rd->len != roundup(rd_new.len, 16)) अणु
				brcmf_err("frame length mismatch:read %d, should be %d\n",
					  rd->len,
					  roundup(rd_new.len, 16) >> 4);
				rd->len = 0;
				brcmf_sdio_rxfail(bus, true, true);
				sdio_release_host(bus->sdiodev->func1);
				brcmu_pkt_buf_मुक्त_skb(pkt);
				जारी;
			पूर्ण
			sdio_release_host(bus->sdiodev->func1);
			rd->len_nxtfrm = rd_new.len_nxtfrm;
			rd->channel = rd_new.channel;
			rd->dat_offset = rd_new.dat_offset;

			brcmf_dbg_hex_dump(!(BRCMF_BYTES_ON() &&
					     BRCMF_DATA_ON()) &&
					   BRCMF_HDRS_ON(),
					   bus->rxhdr, SDPCM_HDRLEN,
					   "RxHdr:\n");

			अगर (rd_new.channel == SDPCM_CONTROL_CHANNEL) अणु
				brcmf_err("readahead on control packet %d?\n",
					  rd_new.seq_num);
				/* Force retry w/normal header पढ़ो */
				rd->len = 0;
				sdio_claim_host(bus->sdiodev->func1);
				brcmf_sdio_rxfail(bus, false, true);
				sdio_release_host(bus->sdiodev->func1);
				brcmu_pkt_buf_मुक्त_skb(pkt);
				जारी;
			पूर्ण
		पूर्ण

		brcmf_dbg_hex_dump(BRCMF_BYTES_ON() && BRCMF_DATA_ON(),
				   pkt->data, rd->len, "Rx Data:\n");

		/* Save superframe descriptor and allocate packet frame */
		अगर (rd->channel == SDPCM_GLOM_CHANNEL) अणु
			अगर (SDPCM_GLOMDESC(&bus->rxhdr[SDPCM_HWHDR_LEN])) अणु
				brcmf_dbg(GLOM, "glom descriptor, %d bytes:\n",
					  rd->len);
				brcmf_dbg_hex_dump(BRCMF_GLOM_ON(),
						   pkt->data, rd->len,
						   "Glom Data:\n");
				__skb_trim(pkt, rd->len);
				skb_pull(pkt, SDPCM_HDRLEN);
				bus->glomd = pkt;
			पूर्ण अन्यथा अणु
				brcmf_err("%s: glom superframe w/o "
					  "descriptor!\n", __func__);
				sdio_claim_host(bus->sdiodev->func1);
				brcmf_sdio_rxfail(bus, false, false);
				sdio_release_host(bus->sdiodev->func1);
			पूर्ण
			/* prepare the descriptor क्रम the next पढ़ो */
			rd->len = rd->len_nxtfrm << 4;
			rd->len_nxtfrm = 0;
			/* treat all packet as event अगर we करोn't know */
			rd->channel = SDPCM_EVENT_CHANNEL;
			जारी;
		पूर्ण

		/* Fill in packet len and prio, deliver upward */
		__skb_trim(pkt, rd->len);
		skb_pull(pkt, rd->dat_offset);

		अगर (pkt->len == 0)
			brcmu_pkt_buf_मुक्त_skb(pkt);
		अन्यथा अगर (rd->channel == SDPCM_EVENT_CHANNEL)
			brcmf_rx_event(bus->sdiodev->dev, pkt);
		अन्यथा
			brcmf_rx_frame(bus->sdiodev->dev, pkt,
				       false, false);

		/* prepare the descriptor क्रम the next पढ़ो */
		rd->len = rd->len_nxtfrm << 4;
		rd->len_nxtfrm = 0;
		/* treat all packet as event अगर we करोn't know */
		rd->channel = SDPCM_EVENT_CHANNEL;
	पूर्ण

	rxcount = maxframes - rxleft;
	/* Message अगर we hit the limit */
	अगर (!rxleft)
		brcmf_dbg(DATA, "hit rx limit of %d frames\n", maxframes);
	अन्यथा
		brcmf_dbg(DATA, "processed %d frames\n", rxcount);
	/* Back off rxseq अगर aरुकोing rtx, update rx_seq */
	अगर (bus->rxskip)
		rd->seq_num--;
	bus->rx_seq = rd->seq_num;

	वापस rxcount;
पूर्ण

अटल व्योम
brcmf_sdio_रुको_event_wakeup(काष्ठा brcmf_sdio *bus)
अणु
	wake_up_पूर्णांकerruptible(&bus->ctrl_रुको);
	वापस;
पूर्ण

अटल पूर्णांक brcmf_sdio_txpkt_hdalign(काष्ठा brcmf_sdio *bus, काष्ठा sk_buff *pkt)
अणु
	काष्ठा brcmf_bus_stats *stats;
	u16 head_pad;
	u8 *dat_buf;

	dat_buf = (u8 *)(pkt->data);

	/* Check head padding */
	head_pad = ((अचिन्हित दीर्घ)dat_buf % bus->head_align);
	अगर (head_pad) अणु
		अगर (skb_headroom(pkt) < head_pad) अणु
			stats = &bus->sdiodev->bus_अगर->stats;
			atomic_inc(&stats->pktcowed);
			अगर (skb_cow_head(pkt, head_pad)) अणु
				atomic_inc(&stats->pktcow_failed);
				वापस -ENOMEM;
			पूर्ण
			head_pad = 0;
		पूर्ण
		skb_push(pkt, head_pad);
		dat_buf = (u8 *)(pkt->data);
	पूर्ण
	स_रखो(dat_buf, 0, head_pad + bus->tx_hdrlen);
	वापस head_pad;
पूर्ण

/*
 * काष्ठा brcmf_skbuff_cb reserves first two bytes in sk_buff::cb क्रम
 * bus layer usage.
 */
/* flag marking a dummy skb added क्रम DMA alignment requirement */
#घोषणा ALIGN_SKB_FLAG		0x8000
/* bit mask of data length chopped from the previous packet */
#घोषणा ALIGN_SKB_CHOP_LEN_MASK	0x7fff

अटल पूर्णांक brcmf_sdio_txpkt_prep_sg(काष्ठा brcmf_sdio *bus,
				    काष्ठा sk_buff_head *pktq,
				    काष्ठा sk_buff *pkt, u16 total_len)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev;
	काष्ठा sk_buff *pkt_pad;
	u16 tail_pad, tail_chop, chain_pad;
	अचिन्हित पूर्णांक blksize;
	bool lastfrm;
	पूर्णांक ntail, ret;

	sdiodev = bus->sdiodev;
	blksize = sdiodev->func2->cur_blksize;
	/* sg entry alignment should be a भागisor of block size */
	WARN_ON(blksize % bus->sgentry_align);

	/* Check tail padding */
	lastfrm = skb_queue_is_last(pktq, pkt);
	tail_pad = 0;
	tail_chop = pkt->len % bus->sgentry_align;
	अगर (tail_chop)
		tail_pad = bus->sgentry_align - tail_chop;
	chain_pad = (total_len + tail_pad) % blksize;
	अगर (lastfrm && chain_pad)
		tail_pad += blksize - chain_pad;
	अगर (skb_tailroom(pkt) < tail_pad && pkt->len > blksize) अणु
		pkt_pad = brcmu_pkt_buf_get_skb(tail_pad + tail_chop +
						bus->head_align);
		अगर (pkt_pad == शून्य)
			वापस -ENOMEM;
		ret = brcmf_sdio_txpkt_hdalign(bus, pkt_pad);
		अगर (unlikely(ret < 0)) अणु
			kमुक्त_skb(pkt_pad);
			वापस ret;
		पूर्ण
		स_नकल(pkt_pad->data,
		       pkt->data + pkt->len - tail_chop,
		       tail_chop);
		*(u16 *)(pkt_pad->cb) = ALIGN_SKB_FLAG + tail_chop;
		skb_trim(pkt, pkt->len - tail_chop);
		skb_trim(pkt_pad, tail_pad + tail_chop);
		__skb_queue_after(pktq, pkt, pkt_pad);
	पूर्ण अन्यथा अणु
		ntail = pkt->data_len + tail_pad -
			(pkt->end - pkt->tail);
		अगर (skb_cloned(pkt) || ntail > 0)
			अगर (pskb_expand_head(pkt, 0, ntail, GFP_ATOMIC))
				वापस -ENOMEM;
		अगर (skb_linearize(pkt))
			वापस -ENOMEM;
		__skb_put(pkt, tail_pad);
	पूर्ण

	वापस tail_pad;
पूर्ण

/**
 * brcmf_sdio_txpkt_prep - packet preparation क्रम transmit
 * @bus: brcmf_sdio काष्ठाure poपूर्णांकer
 * @pktq: packet list poपूर्णांकer
 * @chan: भव channel to transmit the packet
 *
 * Processes to be applied to the packet
 *	- Align data buffer poपूर्णांकer
 *	- Align data buffer length
 *	- Prepare header
 * Return: negative value अगर there is error
 */
अटल पूर्णांक
brcmf_sdio_txpkt_prep(काष्ठा brcmf_sdio *bus, काष्ठा sk_buff_head *pktq,
		      uपूर्णांक chan)
अणु
	u16 head_pad, total_len;
	काष्ठा sk_buff *pkt_next;
	u8 txseq;
	पूर्णांक ret;
	काष्ठा brcmf_sdio_hdrinfo hd_info = अणु0पूर्ण;

	txseq = bus->tx_seq;
	total_len = 0;
	skb_queue_walk(pktq, pkt_next) अणु
		/* alignment packet inserted in previous
		 * loop cycle can be skipped as it is
		 * alपढ़ोy properly aligned and करोes not
		 * need an sdpcm header.
		 */
		अगर (*(u16 *)(pkt_next->cb) & ALIGN_SKB_FLAG)
			जारी;

		/* align packet data poपूर्णांकer */
		ret = brcmf_sdio_txpkt_hdalign(bus, pkt_next);
		अगर (ret < 0)
			वापस ret;
		head_pad = (u16)ret;
		अगर (head_pad)
			स_रखो(pkt_next->data + bus->tx_hdrlen, 0, head_pad);

		total_len += pkt_next->len;

		hd_info.len = pkt_next->len;
		hd_info.lastfrm = skb_queue_is_last(pktq, pkt_next);
		अगर (bus->txglom && pktq->qlen > 1) अणु
			ret = brcmf_sdio_txpkt_prep_sg(bus, pktq,
						       pkt_next, total_len);
			अगर (ret < 0)
				वापस ret;
			hd_info.tail_pad = (u16)ret;
			total_len += (u16)ret;
		पूर्ण

		hd_info.channel = chan;
		hd_info.dat_offset = head_pad + bus->tx_hdrlen;
		hd_info.seq_num = txseq++;

		/* Now fill the header */
		brcmf_sdio_hdpack(bus, pkt_next->data, &hd_info);

		अगर (BRCMF_BYTES_ON() &&
		    ((BRCMF_CTL_ON() && chan == SDPCM_CONTROL_CHANNEL) ||
		     (BRCMF_DATA_ON() && chan != SDPCM_CONTROL_CHANNEL)))
			brcmf_dbg_hex_dump(true, pkt_next->data, hd_info.len,
					   "Tx Frame:\n");
		अन्यथा अगर (BRCMF_HDRS_ON())
			brcmf_dbg_hex_dump(true, pkt_next->data,
					   head_pad + bus->tx_hdrlen,
					   "Tx Header:\n");
	पूर्ण
	/* Hardware length tag of the first packet should be total
	 * length of the chain (including padding)
	 */
	अगर (bus->txglom)
		brcmf_sdio_update_hwhdr(__skb_peek(pktq)->data, total_len);
	वापस 0;
पूर्ण

/**
 * brcmf_sdio_txpkt_postp - packet post processing क्रम transmit
 * @bus: brcmf_sdio काष्ठाure poपूर्णांकer
 * @pktq: packet list poपूर्णांकer
 *
 * Processes to be applied to the packet
 *	- Remove head padding
 *	- Remove tail padding
 */
अटल व्योम
brcmf_sdio_txpkt_postp(काष्ठा brcmf_sdio *bus, काष्ठा sk_buff_head *pktq)
अणु
	u8 *hdr;
	u32 dat_offset;
	u16 tail_pad;
	u16 dummy_flags, chop_len;
	काष्ठा sk_buff *pkt_next, *पंचांगp, *pkt_prev;

	skb_queue_walk_safe(pktq, pkt_next, पंचांगp) अणु
		dummy_flags = *(u16 *)(pkt_next->cb);
		अगर (dummy_flags & ALIGN_SKB_FLAG) अणु
			chop_len = dummy_flags & ALIGN_SKB_CHOP_LEN_MASK;
			अगर (chop_len) अणु
				pkt_prev = pkt_next->prev;
				skb_put(pkt_prev, chop_len);
			पूर्ण
			__skb_unlink(pkt_next, pktq);
			brcmu_pkt_buf_मुक्त_skb(pkt_next);
		पूर्ण अन्यथा अणु
			hdr = pkt_next->data + bus->tx_hdrlen - SDPCM_SWHDR_LEN;
			dat_offset = le32_to_cpu(*(__le32 *)hdr);
			dat_offset = (dat_offset & SDPCM_DOFFSET_MASK) >>
				     SDPCM_DOFFSET_SHIFT;
			skb_pull(pkt_next, dat_offset);
			अगर (bus->txglom) अणु
				tail_pad = le16_to_cpu(*(__le16 *)(hdr - 2));
				skb_trim(pkt_next, pkt_next->len - tail_pad);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Writes a HW/SW header पूर्णांकo the packet and sends it. */
/* Assumes: (a) header space alपढ़ोy there, (b) caller holds lock */
अटल पूर्णांक brcmf_sdio_txpkt(काष्ठा brcmf_sdio *bus, काष्ठा sk_buff_head *pktq,
			    uपूर्णांक chan)
अणु
	पूर्णांक ret;
	काष्ठा sk_buff *pkt_next, *पंचांगp;

	brcmf_dbg(TRACE, "Enter\n");

	ret = brcmf_sdio_txpkt_prep(bus, pktq, chan);
	अगर (ret)
		जाओ करोne;

	sdio_claim_host(bus->sdiodev->func1);
	ret = brcmf_sdiod_send_pkt(bus->sdiodev, pktq);
	bus->sdcnt.f2txdata++;

	अगर (ret < 0)
		brcmf_sdio_txfail(bus);

	sdio_release_host(bus->sdiodev->func1);

करोne:
	brcmf_sdio_txpkt_postp(bus, pktq);
	अगर (ret == 0)
		bus->tx_seq = (bus->tx_seq + pktq->qlen) % SDPCM_SEQ_WRAP;
	skb_queue_walk_safe(pktq, pkt_next, पंचांगp) अणु
		__skb_unlink(pkt_next, pktq);
		brcmf_proto_bcdc_txcomplete(bus->sdiodev->dev, pkt_next,
					    ret == 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल uपूर्णांक brcmf_sdio_sendfromq(काष्ठा brcmf_sdio *bus, uपूर्णांक maxframes)
अणु
	काष्ठा sk_buff *pkt;
	काष्ठा sk_buff_head pktq;
	u32 पूर्णांकstat_addr = bus->sdio_core->base + SD_REG(पूर्णांकstatus);
	u32 पूर्णांकstatus = 0;
	पूर्णांक ret = 0, prec_out, i;
	uपूर्णांक cnt = 0;
	u8 tx_prec_map, pkt_num;

	brcmf_dbg(TRACE, "Enter\n");

	tx_prec_map = ~bus->flowcontrol;

	/* Send frames until the limit or some other event */
	क्रम (cnt = 0; (cnt < maxframes) && data_ok(bus);) अणु
		pkt_num = 1;
		अगर (bus->txglom)
			pkt_num = min_t(u8, bus->tx_max - bus->tx_seq,
					bus->sdiodev->txglomsz);
		pkt_num = min_t(u32, pkt_num,
				brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol));
		__skb_queue_head_init(&pktq);
		spin_lock_bh(&bus->txq_lock);
		क्रम (i = 0; i < pkt_num; i++) अणु
			pkt = brcmu_pktq_mdeq(&bus->txq, tx_prec_map,
					      &prec_out);
			अगर (pkt == शून्य)
				अवरोध;
			__skb_queue_tail(&pktq, pkt);
		पूर्ण
		spin_unlock_bh(&bus->txq_lock);
		अगर (i == 0)
			अवरोध;

		ret = brcmf_sdio_txpkt(bus, &pktq, SDPCM_DATA_CHANNEL);

		cnt += i;

		/* In poll mode, need to check क्रम other events */
		अगर (!bus->पूर्णांकr) अणु
			/* Check device status, संकेत pending पूर्णांकerrupt */
			sdio_claim_host(bus->sdiodev->func1);
			पूर्णांकstatus = brcmf_sdiod_पढ़ोl(bus->sdiodev,
						      पूर्णांकstat_addr, &ret);
			sdio_release_host(bus->sdiodev->func1);

			bus->sdcnt.f2txdata++;
			अगर (ret != 0)
				अवरोध;
			अगर (पूर्णांकstatus & bus->hostपूर्णांकmask)
				atomic_set(&bus->ipend, 1);
		पूर्ण
	पूर्ण

	/* Deflow-control stack अगर needed */
	अगर ((bus->sdiodev->state == BRCMF_SDIOD_DATA) &&
	    bus->txoff && (pktq_len(&bus->txq) < TXLOW)) अणु
		bus->txoff = false;
		brcmf_proto_bcdc_txflowblock(bus->sdiodev->dev, false);
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक brcmf_sdio_tx_ctrlframe(काष्ठा brcmf_sdio *bus, u8 *frame, u16 len)
अणु
	u8 करोff;
	u16 pad;
	uपूर्णांक retries = 0;
	काष्ठा brcmf_sdio_hdrinfo hd_info = अणु0पूर्ण;
	पूर्णांक ret;

	brcmf_dbg(SDIO, "Enter\n");

	/* Back the poपूर्णांकer to make room क्रम bus header */
	frame -= bus->tx_hdrlen;
	len += bus->tx_hdrlen;

	/* Add alignment padding (optional क्रम ctl frames) */
	करोff = ((अचिन्हित दीर्घ)frame % bus->head_align);
	अगर (करोff) अणु
		frame -= करोff;
		len += करोff;
		स_रखो(frame + bus->tx_hdrlen, 0, करोff);
	पूर्ण

	/* Round send length to next SDIO block */
	pad = 0;
	अगर (bus->roundup && bus->blocksize && (len > bus->blocksize)) अणु
		pad = bus->blocksize - (len % bus->blocksize);
		अगर ((pad > bus->roundup) || (pad >= bus->blocksize))
			pad = 0;
	पूर्ण अन्यथा अगर (len % bus->head_align) अणु
		pad = bus->head_align - (len % bus->head_align);
	पूर्ण
	len += pad;

	hd_info.len = len - pad;
	hd_info.channel = SDPCM_CONTROL_CHANNEL;
	hd_info.dat_offset = करोff + bus->tx_hdrlen;
	hd_info.seq_num = bus->tx_seq;
	hd_info.lastfrm = true;
	hd_info.tail_pad = pad;
	brcmf_sdio_hdpack(bus, frame, &hd_info);

	अगर (bus->txglom)
		brcmf_sdio_update_hwhdr(frame, len);

	brcmf_dbg_hex_dump(BRCMF_BYTES_ON() && BRCMF_CTL_ON(),
			   frame, len, "Tx Frame:\n");
	brcmf_dbg_hex_dump(!(BRCMF_BYTES_ON() && BRCMF_CTL_ON()) &&
			   BRCMF_HDRS_ON(),
			   frame, min_t(u16, len, 16), "TxHdr:\n");

	करो अणु
		ret = brcmf_sdiod_send_buf(bus->sdiodev, frame, len);

		अगर (ret < 0)
			brcmf_sdio_txfail(bus);
		अन्यथा
			bus->tx_seq = (bus->tx_seq + 1) % SDPCM_SEQ_WRAP;
	पूर्ण जबतक (ret < 0 && retries++ < TXRETRIES);

	वापस ret;
पूर्ण

अटल bool brcmf_chip_is_ulp(काष्ठा brcmf_chip *ci)
अणु
	अगर (ci->chip == CY_CC_43012_CHIP_ID)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम brcmf_sdio_bus_stop(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;
	काष्ठा brcmf_core *core = bus->sdio_core;
	u32 local_hostपूर्णांकmask;
	u8 saveclk, bpreq;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (bus->watchकरोg_tsk) अणु
		send_sig(संक_इति, bus->watchकरोg_tsk, 1);
		kthपढ़ो_stop(bus->watchकरोg_tsk);
		bus->watchकरोg_tsk = शून्य;
	पूर्ण

	अगर (sdiodev->state != BRCMF_SDIOD_NOMEDIUM) अणु
		sdio_claim_host(sdiodev->func1);

		/* Enable घड़ी क्रम device पूर्णांकerrupts */
		brcmf_sdio_bus_sleep(bus, false, false);

		/* Disable and clear पूर्णांकerrupts at the chip level also */
		brcmf_sdiod_ग_लिखोl(sdiodev, core->base + SD_REG(hostपूर्णांकmask),
				   0, शून्य);

		local_hostपूर्णांकmask = bus->hostपूर्णांकmask;
		bus->hostपूर्णांकmask = 0;

		/* Force backplane घड़ीs to assure F2 पूर्णांकerrupt propagates */
		saveclk = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
					    &err);
		अगर (!err) अणु
			bpreq = saveclk;
			bpreq |= brcmf_chip_is_ulp(bus->ci) ?
				SBSDIO_HT_AVAIL_REQ : SBSDIO_FORCE_HT;
			brcmf_sdiod_ग_लिखोb(sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR,
					   bpreq, &err);
		पूर्ण
		अगर (err)
			brcmf_err("Failed to force clock for F2: err %d\n",
				  err);

		/* Turn off the bus (F2), मुक्त any pending packets */
		brcmf_dbg(INTR, "disable SDIO interrupts\n");
		sdio_disable_func(sdiodev->func2);

		/* Clear any pending पूर्णांकerrupts now that F2 is disabled */
		brcmf_sdiod_ग_लिखोl(sdiodev, core->base + SD_REG(पूर्णांकstatus),
				   local_hostपूर्णांकmask, शून्य);

		sdio_release_host(sdiodev->func1);
	पूर्ण
	/* Clear the data packet queues */
	brcmu_pktq_flush(&bus->txq, true, शून्य, शून्य);

	/* Clear any held glomming stuff */
	brcmu_pkt_buf_मुक्त_skb(bus->glomd);
	brcmf_sdio_मुक्त_glom(bus);

	/* Clear rx control and wake any रुकोers */
	spin_lock_bh(&bus->rxctl_lock);
	bus->rxlen = 0;
	spin_unlock_bh(&bus->rxctl_lock);
	brcmf_sdio_dcmd_resp_wake(bus);

	/* Reset some F2 state stuff */
	bus->rxskip = false;
	bus->tx_seq = bus->rx_seq = 0;
पूर्ण

अटल अंतरभूत व्योम brcmf_sdio_clrपूर्णांकr(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev;
	अचिन्हित दीर्घ flags;

	sdiodev = bus->sdiodev;
	अगर (sdiodev->oob_irq_requested) अणु
		spin_lock_irqsave(&sdiodev->irq_en_lock, flags);
		अगर (!sdiodev->irq_en && !atomic_पढ़ो(&bus->ipend)) अणु
			enable_irq(sdiodev->settings->bus.sdio.oob_irq_nr);
			sdiodev->irq_en = true;
		पूर्ण
		spin_unlock_irqrestore(&sdiodev->irq_en_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_sdio_पूर्णांकr_rstatus(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_core *core = bus->sdio_core;
	u32 addr;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	addr = core->base + SD_REG(पूर्णांकstatus);

	val = brcmf_sdiod_पढ़ोl(bus->sdiodev, addr, &ret);
	bus->sdcnt.f1regdata++;
	अगर (ret != 0)
		वापस ret;

	val &= bus->hostपूर्णांकmask;
	atomic_set(&bus->fcstate, !!(val & I_HMB_FC_STATE));

	/* Clear पूर्णांकerrupts */
	अगर (val) अणु
		brcmf_sdiod_ग_लिखोl(bus->sdiodev, addr, val, &ret);
		bus->sdcnt.f1regdata++;
		atomic_or(val, &bus->पूर्णांकstatus);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम brcmf_sdio_dpc(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_sdio_dev *sdiod = bus->sdiodev;
	u32 newstatus = 0;
	u32 पूर्णांकstat_addr = bus->sdio_core->base + SD_REG(पूर्णांकstatus);
	अचिन्हित दीर्घ पूर्णांकstatus;
	uपूर्णांक txlimit = bus->txbound;	/* Tx frames to send beक्रमe resched */
	uपूर्णांक framecnt;			/* Temporary counter of tx/rx frames */
	पूर्णांक err = 0;

	brcmf_dbg(SDIO, "Enter\n");

	sdio_claim_host(bus->sdiodev->func1);

	/* If रुकोing क्रम HTAVAIL, check status */
	अगर (!bus->sr_enabled && bus->clkstate == CLK_PENDING) अणु
		u8 clkctl, devctl = 0;

#अगर_घोषित DEBUG
		/* Check क्रम inconsistent device control */
		devctl = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   &err);
#पूर्ण_अगर				/* DEBUG */

		/* Read CSR, अगर घड़ी on चयन to AVAIL, अन्यथा ignore */
		clkctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR, &err);

		brcmf_dbg(SDIO, "DPC: PENDING, devctl 0x%02x clkctl 0x%02x\n",
			  devctl, clkctl);

		अगर (SBSDIO_HTAV(clkctl)) अणु
			devctl = brcmf_sdiod_पढ़ोb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_ग_लिखोb(bus->sdiodev,
					   SBSDIO_DEVICE_CTL, devctl, &err);
			bus->clkstate = CLK_AVAIL;
		पूर्ण
	पूर्ण

	/* Make sure backplane घड़ी is on */
	brcmf_sdio_bus_sleep(bus, false, true);

	/* Pending पूर्णांकerrupt indicates new device status */
	अगर (atomic_पढ़ो(&bus->ipend) > 0) अणु
		atomic_set(&bus->ipend, 0);
		err = brcmf_sdio_पूर्णांकr_rstatus(bus);
	पूर्ण

	/* Start with leftover status bits */
	पूर्णांकstatus = atomic_xchg(&bus->पूर्णांकstatus, 0);

	/* Handle flow-control change: पढ़ो new state in हाल our ack
	 * crossed another change पूर्णांकerrupt.  If change still set, assume
	 * FC ON क्रम safety, let next loop through करो the debounce.
	 */
	अगर (पूर्णांकstatus & I_HMB_FC_CHANGE) अणु
		पूर्णांकstatus &= ~I_HMB_FC_CHANGE;
		brcmf_sdiod_ग_लिखोl(sdiod, पूर्णांकstat_addr, I_HMB_FC_CHANGE, &err);

		newstatus = brcmf_sdiod_पढ़ोl(sdiod, पूर्णांकstat_addr, &err);

		bus->sdcnt.f1regdata += 2;
		atomic_set(&bus->fcstate,
			   !!(newstatus & (I_HMB_FC_STATE | I_HMB_FC_CHANGE)));
		पूर्णांकstatus |= (newstatus & bus->hostपूर्णांकmask);
	पूर्ण

	/* Handle host mailbox indication */
	अगर (पूर्णांकstatus & I_HMB_HOST_INT) अणु
		पूर्णांकstatus &= ~I_HMB_HOST_INT;
		पूर्णांकstatus |= brcmf_sdio_hosपंचांगail(bus);
	पूर्ण

	sdio_release_host(bus->sdiodev->func1);

	/* Generally करोn't ask क्रम these, can get CRC errors... */
	अगर (पूर्णांकstatus & I_WR_OOSYNC) अणु
		brcmf_err("Dongle reports WR_OOSYNC\n");
		पूर्णांकstatus &= ~I_WR_OOSYNC;
	पूर्ण

	अगर (पूर्णांकstatus & I_RD_OOSYNC) अणु
		brcmf_err("Dongle reports RD_OOSYNC\n");
		पूर्णांकstatus &= ~I_RD_OOSYNC;
	पूर्ण

	अगर (पूर्णांकstatus & I_SBINT) अणु
		brcmf_err("Dongle reports SBINT\n");
		पूर्णांकstatus &= ~I_SBINT;
	पूर्ण

	/* Would be active due to wake-wlan in gSPI */
	अगर (पूर्णांकstatus & I_CHIPACTIVE) अणु
		brcmf_dbg(SDIO, "Dongle reports CHIPACTIVE\n");
		पूर्णांकstatus &= ~I_CHIPACTIVE;
	पूर्ण

	/* Ignore frame indications अगर rxskip is set */
	अगर (bus->rxskip)
		पूर्णांकstatus &= ~I_HMB_FRAME_IND;

	/* On frame indication, पढ़ो available frames */
	अगर ((पूर्णांकstatus & I_HMB_FRAME_IND) && (bus->clkstate == CLK_AVAIL)) अणु
		brcmf_sdio_पढ़ोframes(bus, bus->rxbound);
		अगर (!bus->rxpending)
			पूर्णांकstatus &= ~I_HMB_FRAME_IND;
	पूर्ण

	/* Keep still-pending events क्रम next scheduling */
	अगर (पूर्णांकstatus)
		atomic_or(पूर्णांकstatus, &bus->पूर्णांकstatus);

	brcmf_sdio_clrपूर्णांकr(bus);

	अगर (bus->ctrl_frame_stat && (bus->clkstate == CLK_AVAIL) &&
	    txctl_ok(bus)) अणु
		sdio_claim_host(bus->sdiodev->func1);
		अगर (bus->ctrl_frame_stat) अणु
			err = brcmf_sdio_tx_ctrlframe(bus,  bus->ctrl_frame_buf,
						      bus->ctrl_frame_len);
			bus->ctrl_frame_err = err;
			wmb();
			bus->ctrl_frame_stat = false;
			अगर (err)
				brcmf_err("sdio ctrlframe tx failed err=%d\n",
					  err);
		पूर्ण
		sdio_release_host(bus->sdiodev->func1);
		brcmf_sdio_रुको_event_wakeup(bus);
	पूर्ण
	/* Send queued frames (limit 1 अगर rx may still be pending) */
	अगर ((bus->clkstate == CLK_AVAIL) && !atomic_पढ़ो(&bus->fcstate) &&
	    brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol) && txlimit &&
	    data_ok(bus)) अणु
		framecnt = bus->rxpending ? min(txlimit, bus->txminmax) :
					    txlimit;
		brcmf_sdio_sendfromq(bus, framecnt);
	पूर्ण

	अगर ((bus->sdiodev->state != BRCMF_SDIOD_DATA) || (err != 0)) अणु
		brcmf_err("failed backplane access over SDIO, halting operation\n");
		atomic_set(&bus->पूर्णांकstatus, 0);
		अगर (bus->ctrl_frame_stat) अणु
			sdio_claim_host(bus->sdiodev->func1);
			अगर (bus->ctrl_frame_stat) अणु
				bus->ctrl_frame_err = -ENODEV;
				wmb();
				bus->ctrl_frame_stat = false;
				brcmf_sdio_रुको_event_wakeup(bus);
			पूर्ण
			sdio_release_host(bus->sdiodev->func1);
		पूर्ण
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&bus->पूर्णांकstatus) ||
		   atomic_पढ़ो(&bus->ipend) > 0 ||
		   (!atomic_पढ़ो(&bus->fcstate) &&
		    brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol) &&
		    data_ok(bus))) अणु
		bus->dpc_triggered = true;
	पूर्ण
पूर्ण

अटल काष्ठा pktq *brcmf_sdio_bus_gettxq(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;

	वापस &bus->txq;
पूर्ण

अटल bool brcmf_sdio_prec_enq(काष्ठा pktq *q, काष्ठा sk_buff *pkt, पूर्णांक prec)
अणु
	काष्ठा sk_buff *p;
	पूर्णांक eprec = -1;		/* precedence to evict from */

	/* Fast हाल, precedence queue is not full and we are also not
	 * exceeding total queue length
	 */
	अगर (!pktq_pfull(q, prec) && !pktq_full(q)) अणु
		brcmu_pktq_penq(q, prec, pkt);
		वापस true;
	पूर्ण

	/* Determine precedence from which to evict packet, अगर any */
	अगर (pktq_pfull(q, prec)) अणु
		eprec = prec;
	पूर्ण अन्यथा अगर (pktq_full(q)) अणु
		p = brcmu_pktq_peek_tail(q, &eprec);
		अगर (eprec > prec)
			वापस false;
	पूर्ण

	/* Evict अगर needed */
	अगर (eprec >= 0) अणु
		/* Detect queueing to unconfigured precedence */
		अगर (eprec == prec)
			वापस false;	/* refuse newer (incoming) packet */
		/* Evict packet according to discard policy */
		p = brcmu_pktq_pdeq_tail(q, eprec);
		अगर (p == शून्य)
			brcmf_err("brcmu_pktq_pdeq_tail() failed\n");
		brcmu_pkt_buf_मुक्त_skb(p);
	पूर्ण

	/* Enqueue */
	p = brcmu_pktq_penq(q, prec, pkt);
	अगर (p == शून्य)
		brcmf_err("brcmu_pktq_penq() failed\n");

	वापस p != शून्य;
पूर्ण

अटल पूर्णांक brcmf_sdio_bus_txdata(काष्ठा device *dev, काष्ठा sk_buff *pkt)
अणु
	पूर्णांक ret = -EBADE;
	uपूर्णांक prec;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;

	brcmf_dbg(TRACE, "Enter: pkt: data %p len %d\n", pkt->data, pkt->len);
	अगर (sdiodev->state != BRCMF_SDIOD_DATA)
		वापस -EIO;

	/* Add space क्रम the header */
	skb_push(pkt, bus->tx_hdrlen);
	/* precondition: IS_ALIGNED((अचिन्हित दीर्घ)(pkt->data), 2) */

	/* In WLAN, priority is always set by the AP using WMM parameters
	 * and this need not always follow the standard 802.1d priority.
	 * Based on AP WMM config, map from 802.1d priority to corresponding
	 * precedence level.
	 */
	prec = brcmf_map_prio_to_prec(bus_अगर->drvr->config,
				      (pkt->priority & PRIOMASK));

	/* Check क्रम existing queue, current flow-control,
			 pending event, or pending घड़ी */
	brcmf_dbg(TRACE, "deferring pktq len %d\n", pktq_len(&bus->txq));
	bus->sdcnt.fcqueued++;

	/* Priority based enq */
	spin_lock_bh(&bus->txq_lock);
	/* reset bus_flags in packet cb */
	*(u16 *)(pkt->cb) = 0;
	अगर (!brcmf_sdio_prec_enq(&bus->txq, pkt, prec)) अणु
		skb_pull(pkt, bus->tx_hdrlen);
		brcmf_err("out of bus->txq !!!\n");
		ret = -ENOSR;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	अगर (pktq_len(&bus->txq) >= TXHI) अणु
		bus->txoff = true;
		brcmf_proto_bcdc_txflowblock(dev, true);
	पूर्ण
	spin_unlock_bh(&bus->txq_lock);

#अगर_घोषित DEBUG
	अगर (pktq_plen(&bus->txq, prec) > qcount[prec])
		qcount[prec] = pktq_plen(&bus->txq, prec);
#पूर्ण_अगर

	brcmf_sdio_trigger_dpc(bus);
	वापस ret;
पूर्ण

#अगर_घोषित DEBUG
#घोषणा CONSOLE_LINE_MAX	192

अटल पूर्णांक brcmf_sdio_पढ़ोconsole(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_console *c = &bus->console;
	u8 line[CONSOLE_LINE_MAX], ch;
	u32 n, idx, addr;
	पूर्णांक rv;

	/* Don't करो anything until FWREADY updates console address */
	अगर (bus->console_addr == 0)
		वापस 0;

	/* Read console log काष्ठा */
	addr = bus->console_addr + दुरत्व(काष्ठा rte_console, log_le);
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr, (u8 *)&c->log_le,
			       माप(c->log_le));
	अगर (rv < 0)
		वापस rv;

	/* Allocate console buffer (one समय only) */
	अगर (c->buf == शून्य) अणु
		c->bufsize = le32_to_cpu(c->log_le.buf_size);
		c->buf = kदो_स्मृति(c->bufsize, GFP_ATOMIC);
		अगर (c->buf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	idx = le32_to_cpu(c->log_le.idx);

	/* Protect against corrupt value */
	अगर (idx > c->bufsize)
		वापस -EBADE;

	/* Skip पढ़ोing the console buffer अगर the index poपूर्णांकer
	 has not moved */
	अगर (idx == c->last)
		वापस 0;

	/* Read the console buffer */
	addr = le32_to_cpu(c->log_le.buf);
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr, c->buf, c->bufsize);
	अगर (rv < 0)
		वापस rv;

	जबतक (c->last != idx) अणु
		क्रम (n = 0; n < CONSOLE_LINE_MAX - 2; n++) अणु
			अगर (c->last == idx) अणु
				/* This would output a partial line.
				 * Instead, back up
				 * the buffer poपूर्णांकer and output this
				 * line next समय around.
				 */
				अगर (c->last >= n)
					c->last -= n;
				अन्यथा
					c->last = c->bufsize - n;
				जाओ अवरोध2;
			पूर्ण
			ch = c->buf[c->last];
			c->last = (c->last + 1) % c->bufsize;
			अगर (ch == '\n')
				अवरोध;
			line[n] = ch;
		पूर्ण

		अगर (n > 0) अणु
			अगर (line[n - 1] == '\r')
				n--;
			line[n] = 0;
			pr_debug("CONSOLE: %s\n", line);
		पूर्ण
	पूर्ण
अवरोध2:

	वापस 0;
पूर्ण
#पूर्ण_अगर				/* DEBUG */

अटल पूर्णांक
brcmf_sdio_bus_txctl(काष्ठा device *dev, अचिन्हित अक्षर *msg, uपूर्णांक msglen)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;
	पूर्णांक ret;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (sdiodev->state != BRCMF_SDIOD_DATA)
		वापस -EIO;

	/* Send from dpc */
	bus->ctrl_frame_buf = msg;
	bus->ctrl_frame_len = msglen;
	wmb();
	bus->ctrl_frame_stat = true;

	brcmf_sdio_trigger_dpc(bus);
	रुको_event_पूर्णांकerruptible_समयout(bus->ctrl_रुको, !bus->ctrl_frame_stat,
					 CTL_DONE_TIMEOUT);
	ret = 0;
	अगर (bus->ctrl_frame_stat) अणु
		sdio_claim_host(bus->sdiodev->func1);
		अगर (bus->ctrl_frame_stat) अणु
			brcmf_dbg(SDIO, "ctrl_frame timeout\n");
			bus->ctrl_frame_stat = false;
			ret = -ETIMEDOUT;
		पूर्ण
		sdio_release_host(bus->sdiodev->func1);
	पूर्ण
	अगर (!ret) अणु
		brcmf_dbg(SDIO, "ctrl_frame complete, err=%d\n",
			  bus->ctrl_frame_err);
		rmb();
		ret = bus->ctrl_frame_err;
	पूर्ण

	अगर (ret)
		bus->sdcnt.tx_ctlerrs++;
	अन्यथा
		bus->sdcnt.tx_ctlpkts++;

	वापस ret;
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक brcmf_sdio_dump_console(काष्ठा seq_file *seq, काष्ठा brcmf_sdio *bus,
				   काष्ठा sdpcm_shared *sh)
अणु
	u32 addr, console_ptr, console_size, console_index;
	अक्षर *conbuf = शून्य;
	__le32 sh_val;
	पूर्णांक rv;

	/* obtain console inक्रमmation from device memory */
	addr = sh->console_addr + दुरत्व(काष्ठा rte_console, log_le);
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr,
			       (u8 *)&sh_val, माप(u32));
	अगर (rv < 0)
		वापस rv;
	console_ptr = le32_to_cpu(sh_val);

	addr = sh->console_addr + दुरत्व(काष्ठा rte_console, log_le.buf_size);
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr,
			       (u8 *)&sh_val, माप(u32));
	अगर (rv < 0)
		वापस rv;
	console_size = le32_to_cpu(sh_val);

	addr = sh->console_addr + दुरत्व(काष्ठा rte_console, log_le.idx);
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, addr,
			       (u8 *)&sh_val, माप(u32));
	अगर (rv < 0)
		वापस rv;
	console_index = le32_to_cpu(sh_val);

	/* allocate buffer क्रम console data */
	अगर (console_size <= CONSOLE_BUFFER_MAX)
		conbuf = vzalloc(console_size+1);

	अगर (!conbuf)
		वापस -ENOMEM;

	/* obtain the console data from device */
	conbuf[console_size] = '\0';
	rv = brcmf_sdiod_ramrw(bus->sdiodev, false, console_ptr, (u8 *)conbuf,
			       console_size);
	अगर (rv < 0)
		जाओ करोne;

	rv = seq_ग_लिखो(seq, conbuf + console_index,
		       console_size - console_index);
	अगर (rv < 0)
		जाओ करोne;

	अगर (console_index > 0)
		rv = seq_ग_लिखो(seq, conbuf, console_index - 1);

करोne:
	vमुक्त(conbuf);
	वापस rv;
पूर्ण

अटल पूर्णांक brcmf_sdio_trap_info(काष्ठा seq_file *seq, काष्ठा brcmf_sdio *bus,
				काष्ठा sdpcm_shared *sh)
अणु
	पूर्णांक error;
	काष्ठा brcmf_trap_info tr;

	अगर ((sh->flags & SDPCM_SHARED_TRAP) == 0) अणु
		brcmf_dbg(INFO, "no trap in firmware\n");
		वापस 0;
	पूर्ण

	error = brcmf_sdiod_ramrw(bus->sdiodev, false, sh->trap_addr, (u8 *)&tr,
				  माप(काष्ठा brcmf_trap_info));
	अगर (error < 0)
		वापस error;

	अगर (seq)
		seq_म_लिखो(seq,
			   "dongle trap info: type 0x%x @ epc 0x%08x\n"
			   "  cpsr 0x%08x spsr 0x%08x sp 0x%08x\n"
			   "  lr   0x%08x pc   0x%08x offset 0x%x\n"
			   "  r0   0x%08x r1   0x%08x r2 0x%08x r3 0x%08x\n"
			   "  r4   0x%08x r5   0x%08x r6 0x%08x r7 0x%08x\n",
			   le32_to_cpu(tr.type), le32_to_cpu(tr.epc),
			   le32_to_cpu(tr.cpsr), le32_to_cpu(tr.spsr),
			   le32_to_cpu(tr.r13), le32_to_cpu(tr.r14),
			   le32_to_cpu(tr.pc), sh->trap_addr,
			   le32_to_cpu(tr.r0), le32_to_cpu(tr.r1),
			   le32_to_cpu(tr.r2), le32_to_cpu(tr.r3),
			   le32_to_cpu(tr.r4), le32_to_cpu(tr.r5),
			   le32_to_cpu(tr.r6), le32_to_cpu(tr.r7));
	अन्यथा
		pr_debug("dongle trap info: type 0x%x @ epc 0x%08x\n"
			 "  cpsr 0x%08x spsr 0x%08x sp 0x%08x\n"
			 "  lr   0x%08x pc   0x%08x offset 0x%x\n"
			 "  r0   0x%08x r1   0x%08x r2 0x%08x r3 0x%08x\n"
			 "  r4   0x%08x r5   0x%08x r6 0x%08x r7 0x%08x\n",
			 le32_to_cpu(tr.type), le32_to_cpu(tr.epc),
			 le32_to_cpu(tr.cpsr), le32_to_cpu(tr.spsr),
			 le32_to_cpu(tr.r13), le32_to_cpu(tr.r14),
			 le32_to_cpu(tr.pc), sh->trap_addr,
			 le32_to_cpu(tr.r0), le32_to_cpu(tr.r1),
			 le32_to_cpu(tr.r2), le32_to_cpu(tr.r3),
			 le32_to_cpu(tr.r4), le32_to_cpu(tr.r5),
			 le32_to_cpu(tr.r6), le32_to_cpu(tr.r7));
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_sdio_निश्चित_info(काष्ठा seq_file *seq, काष्ठा brcmf_sdio *bus,
				  काष्ठा sdpcm_shared *sh)
अणु
	पूर्णांक error = 0;
	अक्षर file[80] = "?";
	अक्षर expr[80] = "<???>";

	अगर ((sh->flags & SDPCM_SHARED_ASSERT_BUILT) == 0) अणु
		brcmf_dbg(INFO, "firmware not built with -assert\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((sh->flags & SDPCM_SHARED_ASSERT) == 0) अणु
		brcmf_dbg(INFO, "no assert in dongle\n");
		वापस 0;
	पूर्ण

	sdio_claim_host(bus->sdiodev->func1);
	अगर (sh->निश्चित_file_addr != 0) अणु
		error = brcmf_sdiod_ramrw(bus->sdiodev, false,
					  sh->निश्चित_file_addr, (u8 *)file, 80);
		अगर (error < 0)
			वापस error;
	पूर्ण
	अगर (sh->निश्चित_exp_addr != 0) अणु
		error = brcmf_sdiod_ramrw(bus->sdiodev, false,
					  sh->निश्चित_exp_addr, (u8 *)expr, 80);
		अगर (error < 0)
			वापस error;
	पूर्ण
	sdio_release_host(bus->sdiodev->func1);

	seq_म_लिखो(seq, "dongle assert: %s:%d: assert(%s)\n",
		   file, sh->निश्चित_line, expr);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_sdio_checkdied(काष्ठा brcmf_sdio *bus)
अणु
	पूर्णांक error;
	काष्ठा sdpcm_shared sh;

	error = brcmf_sdio_पढ़ोshared(bus, &sh);

	अगर (error < 0)
		वापस error;

	अगर ((sh.flags & SDPCM_SHARED_ASSERT_BUILT) == 0)
		brcmf_dbg(INFO, "firmware not built with -assert\n");
	अन्यथा अगर (sh.flags & SDPCM_SHARED_ASSERT)
		brcmf_err("assertion in dongle\n");

	अगर (sh.flags & SDPCM_SHARED_TRAP) अणु
		brcmf_err("firmware trap in dongle\n");
		brcmf_sdio_trap_info(शून्य, bus, &sh);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_sdio_died_dump(काष्ठा seq_file *seq, काष्ठा brcmf_sdio *bus)
अणु
	पूर्णांक error = 0;
	काष्ठा sdpcm_shared sh;

	error = brcmf_sdio_पढ़ोshared(bus, &sh);
	अगर (error < 0)
		जाओ करोne;

	error = brcmf_sdio_निश्चित_info(seq, bus, &sh);
	अगर (error < 0)
		जाओ करोne;

	error = brcmf_sdio_trap_info(seq, bus, &sh);
	अगर (error < 0)
		जाओ करोne;

	error = brcmf_sdio_dump_console(seq, bus, &sh);

करोne:
	वापस error;
पूर्ण

अटल पूर्णांक brcmf_sdio_क्रमensic_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	काष्ठा brcmf_sdio *bus = bus_अगर->bus_priv.sdio->bus;

	वापस brcmf_sdio_died_dump(seq, bus);
पूर्ण

अटल पूर्णांक brcmf_debugfs_sdio_count_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio_count *sdcnt = &sdiodev->bus->sdcnt;

	seq_म_लिखो(seq,
		   "intrcount:    %u\nlastintrs:    %u\n"
		   "pollcnt:      %u\nregfails:     %u\n"
		   "tx_sderrs:    %u\nfcqueued:     %u\n"
		   "rxrtx:        %u\nrx_toolong:   %u\n"
		   "rxc_errors:   %u\nrx_hdrfail:   %u\n"
		   "rx_badhdr:    %u\nrx_badseq:    %u\n"
		   "fc_rcvd:      %u\nfc_xoff:      %u\n"
		   "fc_xon:       %u\nrxglomfail:   %u\n"
		   "rxglomframes: %u\nrxglompkts:   %u\n"
		   "f2rxhdrs:     %u\nf2rxdata:     %u\n"
		   "f2txdata:     %u\nf1regdata:    %u\n"
		   "tickcnt:      %u\ntx_ctlerrs:   %lu\n"
		   "tx_ctlpkts:   %lu\nrx_ctlerrs:   %lu\n"
		   "rx_ctlpkts:   %lu\nrx_readahead: %lu\n",
		   sdcnt->पूर्णांकrcount, sdcnt->lastपूर्णांकrs,
		   sdcnt->pollcnt, sdcnt->regfails,
		   sdcnt->tx_sderrs, sdcnt->fcqueued,
		   sdcnt->rxrtx, sdcnt->rx_tooदीर्घ,
		   sdcnt->rxc_errors, sdcnt->rx_hdrfail,
		   sdcnt->rx_badhdr, sdcnt->rx_badseq,
		   sdcnt->fc_rcvd, sdcnt->fc_xoff,
		   sdcnt->fc_xon, sdcnt->rxglomfail,
		   sdcnt->rxglomframes, sdcnt->rxglompkts,
		   sdcnt->f2rxhdrs, sdcnt->f2rxdata,
		   sdcnt->f2txdata, sdcnt->f1regdata,
		   sdcnt->tickcnt, sdcnt->tx_ctlerrs,
		   sdcnt->tx_ctlpkts, sdcnt->rx_ctlerrs,
		   sdcnt->rx_ctlpkts, sdcnt->rx_पढ़ोahead_cnt);

	वापस 0;
पूर्ण

अटल व्योम brcmf_sdio_debugfs_create(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;
	काष्ठा dentry *dentry = brcmf_debugfs_get_devdir(drvr);

	अगर (IS_ERR_OR_शून्य(dentry))
		वापस;

	bus->console_पूर्णांकerval = BRCMF_CONSOLE;

	brcmf_debugfs_add_entry(drvr, "forensics", brcmf_sdio_क्रमensic_पढ़ो);
	brcmf_debugfs_add_entry(drvr, "counters",
				brcmf_debugfs_sdio_count_पढ़ो);
	debugfs_create_u32("console_interval", 0644, dentry,
			   &bus->console_पूर्णांकerval);
पूर्ण
#अन्यथा
अटल पूर्णांक brcmf_sdio_checkdied(काष्ठा brcmf_sdio *bus)
अणु
	वापस 0;
पूर्ण

अटल व्योम brcmf_sdio_debugfs_create(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल पूर्णांक
brcmf_sdio_bus_rxctl(काष्ठा device *dev, अचिन्हित अक्षर *msg, uपूर्णांक msglen)
अणु
	पूर्णांक समयleft;
	uपूर्णांक rxlen = 0;
	bool pending;
	u8 *buf;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (sdiodev->state != BRCMF_SDIOD_DATA)
		वापस -EIO;

	/* Wait until control frame is available */
	समयleft = brcmf_sdio_dcmd_resp_रुको(bus, &bus->rxlen, &pending);

	spin_lock_bh(&bus->rxctl_lock);
	rxlen = bus->rxlen;
	स_नकल(msg, bus->rxctl, min(msglen, rxlen));
	bus->rxctl = शून्य;
	buf = bus->rxctl_orig;
	bus->rxctl_orig = शून्य;
	bus->rxlen = 0;
	spin_unlock_bh(&bus->rxctl_lock);
	vमुक्त(buf);

	अगर (rxlen) अणु
		brcmf_dbg(CTL, "resumed on rxctl frame, got %d expected %d\n",
			  rxlen, msglen);
	पूर्ण अन्यथा अगर (समयleft == 0) अणु
		brcmf_err("resumed on timeout\n");
		brcmf_sdio_checkdied(bus);
	पूर्ण अन्यथा अगर (pending) अणु
		brcmf_dbg(CTL, "cancelled\n");
		वापस -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		brcmf_dbg(CTL, "resumed for unknown reason?\n");
		brcmf_sdio_checkdied(bus);
	पूर्ण

	अगर (rxlen)
		bus->sdcnt.rx_ctlpkts++;
	अन्यथा
		bus->sdcnt.rx_ctlerrs++;

	वापस rxlen ? (पूर्णांक)rxlen : -ETIMEDOUT;
पूर्ण

#अगर_घोषित DEBUG
अटल bool
brcmf_sdio_verअगरymemory(काष्ठा brcmf_sdio_dev *sdiodev, u32 ram_addr,
			u8 *ram_data, uपूर्णांक ram_sz)
अणु
	अक्षर *ram_cmp;
	पूर्णांक err;
	bool ret = true;
	पूर्णांक address;
	पूर्णांक offset;
	पूर्णांक len;

	/* पढ़ो back and verअगरy */
	brcmf_dbg(INFO, "Compare RAM dl & ul at 0x%08x; size=%d\n", ram_addr,
		  ram_sz);
	ram_cmp = kदो_स्मृति(MEMBLOCK, GFP_KERNEL);
	/* करो not proceed जबतक no memory but  */
	अगर (!ram_cmp)
		वापस true;

	address = ram_addr;
	offset = 0;
	जबतक (offset < ram_sz) अणु
		len = ((offset + MEMBLOCK) < ram_sz) ? MEMBLOCK :
		      ram_sz - offset;
		err = brcmf_sdiod_ramrw(sdiodev, false, address, ram_cmp, len);
		अगर (err) अणु
			brcmf_err("error %d on reading %d membytes at 0x%08x\n",
				  err, len, address);
			ret = false;
			अवरोध;
		पूर्ण अन्यथा अगर (स_भेद(ram_cmp, &ram_data[offset], len)) अणु
			brcmf_err("Downloaded RAM image is corrupted, block offset is %d, len is %d\n",
				  offset, len);
			ret = false;
			अवरोध;
		पूर्ण
		offset += len;
		address += len;
	पूर्ण

	kमुक्त(ram_cmp);

	वापस ret;
पूर्ण
#अन्यथा	/* DEBUG */
अटल bool
brcmf_sdio_verअगरymemory(काष्ठा brcmf_sdio_dev *sdiodev, u32 ram_addr,
			u8 *ram_data, uपूर्णांक ram_sz)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर	/* DEBUG */

अटल पूर्णांक brcmf_sdio_करोwnload_code_file(काष्ठा brcmf_sdio *bus,
					 स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	err = brcmf_sdiod_ramrw(bus->sdiodev, true, bus->ci->rambase,
				(u8 *)fw->data, fw->size);
	अगर (err)
		brcmf_err("error %d on writing %d membytes at 0x%08x\n",
			  err, (पूर्णांक)fw->size, bus->ci->rambase);
	अन्यथा अगर (!brcmf_sdio_verअगरymemory(bus->sdiodev, bus->ci->rambase,
					  (u8 *)fw->data, fw->size))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_sdio_करोwnload_nvram(काष्ठा brcmf_sdio *bus,
				     व्योम *vars, u32 varsz)
अणु
	पूर्णांक address;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	address = bus->ci->ramsize - varsz + bus->ci->rambase;
	err = brcmf_sdiod_ramrw(bus->sdiodev, true, address, vars, varsz);
	अगर (err)
		brcmf_err("error %d on writing %d nvram bytes at 0x%08x\n",
			  err, varsz, address);
	अन्यथा अगर (!brcmf_sdio_verअगरymemory(bus->sdiodev, address, vars, varsz))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_sdio_करोwnload_firmware(काष्ठा brcmf_sdio *bus,
					स्थिर काष्ठा firmware *fw,
					व्योम *nvram, u32 nvlen)
अणु
	पूर्णांक bcmerror;
	u32 rstvec;

	sdio_claim_host(bus->sdiodev->func1);
	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);

	rstvec = get_unaligned_le32(fw->data);
	brcmf_dbg(SDIO, "firmware rstvec: %x\n", rstvec);

	bcmerror = brcmf_sdio_करोwnload_code_file(bus, fw);
	release_firmware(fw);
	अगर (bcmerror) अणु
		brcmf_err("dongle image file download failed\n");
		brcmf_fw_nvram_मुक्त(nvram);
		जाओ err;
	पूर्ण

	bcmerror = brcmf_sdio_करोwnload_nvram(bus, nvram, nvlen);
	brcmf_fw_nvram_मुक्त(nvram);
	अगर (bcmerror) अणु
		brcmf_err("dongle nvram file download failed\n");
		जाओ err;
	पूर्ण

	/* Take arm out of reset */
	अगर (!brcmf_chip_set_active(bus->ci, rstvec)) अणु
		brcmf_err("error getting out of ARM core reset\n");
		जाओ err;
	पूर्ण

err:
	brcmf_sdio_clkctl(bus, CLK_SDONLY, false);
	sdio_release_host(bus->sdiodev->func1);
	वापस bcmerror;
पूर्ण

अटल bool brcmf_sdio_aos_no_decode(काष्ठा brcmf_sdio *bus)
अणु
	अगर (bus->ci->chip == CY_CC_43012_CHIP_ID)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम brcmf_sdio_sr_init(काष्ठा brcmf_sdio *bus)
अणु
	पूर्णांक err = 0;
	u8 val;
	u8 wakeupctrl;
	u8 cardcap;
	u8 chipclkcsr;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (brcmf_chip_is_ulp(bus->ci)) अणु
		wakeupctrl = SBSDIO_FUNC1_WCTRL_ALPWAIT_SHIFT;
		chipclkcsr = SBSDIO_HT_AVAIL_REQ;
	पूर्ण अन्यथा अणु
		wakeupctrl = SBSDIO_FUNC1_WCTRL_HTWAIT_SHIFT;
		chipclkcsr = SBSDIO_FORCE_HT;
	पूर्ण

	अगर (brcmf_sdio_aos_no_decode(bus)) अणु
		cardcap = SDIO_CCCR_BRCM_CARDCAP_CMD_NODEC;
	पूर्ण अन्यथा अणु
		cardcap = (SDIO_CCCR_BRCM_CARDCAP_CMD14_SUPPORT |
			   SDIO_CCCR_BRCM_CARDCAP_CMD14_EXT);
	पूर्ण

	val = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_FUNC1_WAKEUPCTRL, &err);
	अगर (err) अणु
		brcmf_err("error reading SBSDIO_FUNC1_WAKEUPCTRL\n");
		वापस;
	पूर्ण
	val |= 1 << wakeupctrl;
	brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_WAKEUPCTRL, val, &err);
	अगर (err) अणु
		brcmf_err("error writing SBSDIO_FUNC1_WAKEUPCTRL\n");
		वापस;
	पूर्ण

	/* Add CMD14 Support */
	brcmf_sdiod_func0_wb(bus->sdiodev, SDIO_CCCR_BRCM_CARDCAP,
			     cardcap,
			     &err);
	अगर (err) अणु
		brcmf_err("error writing SDIO_CCCR_BRCM_CARDCAP\n");
		वापस;
	पूर्ण

	brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
			   chipclkcsr, &err);
	अगर (err) अणु
		brcmf_err("error writing SBSDIO_FUNC1_CHIPCLKCSR\n");
		वापस;
	पूर्ण

	/* set flag */
	bus->sr_enabled = true;
	brcmf_dbg(INFO, "SR enabled\n");
पूर्ण

/* enable KSO bit */
अटल पूर्णांक brcmf_sdio_kso_init(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_core *core = bus->sdio_core;
	u8 val;
	पूर्णांक err = 0;

	brcmf_dbg(TRACE, "Enter\n");

	/* KSO bit added in SDIO core rev 12 */
	अगर (core->rev < 12)
		वापस 0;

	val = brcmf_sdiod_पढ़ोb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, &err);
	अगर (err) अणु
		brcmf_err("error reading SBSDIO_FUNC1_SLEEPCSR\n");
		वापस err;
	पूर्ण

	अगर (!(val & SBSDIO_FUNC1_SLEEPCSR_KSO_MASK)) अणु
		val |= (SBSDIO_FUNC1_SLEEPCSR_KSO_EN <<
			SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT);
		brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR,
				   val, &err);
		अगर (err) अणु
			brcmf_err("error writing SBSDIO_FUNC1_SLEEPCSR\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_sdio_bus_preinit(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;
	काष्ठा brcmf_core *core = bus->sdio_core;
	u32 value;
	__le32 iovar;
	पूर्णांक err;

	/* maxctl provided by common layer */
	अगर (WARN_ON(!bus_अगर->maxctl))
		वापस -EINVAL;

	/* Allocate control receive buffer */
	bus_अगर->maxctl += bus->roundup;
	value = roundup((bus_अगर->maxctl + SDPCM_HDRLEN), ALIGNMENT);
	value += bus->head_align;
	bus->rxbuf = kदो_स्मृति(value, GFP_ATOMIC);
	अगर (bus->rxbuf)
		bus->rxblen = value;

	/* the commands below use the terms tx and rx from
	 * a device perspective, ie. bus:txglom affects the
	 * bus transfers from device to host.
	 */
	अगर (core->rev < 12) अणु
		/* क्रम sdio core rev < 12, disable txgloming */
		iovar = 0;
		err = brcmf_iovar_data_set(dev, "bus:txglom", &iovar,
					   माप(iovar));
	पूर्ण अन्यथा अणु
		/* otherwise, set txglomalign */
		value = sdiodev->settings->bus.sdio.sd_sgentry_align;
		/* SDIO ADMA requires at least 32 bit alignment */
		iovar = cpu_to_le32(max_t(u32, value, ALIGNMENT));
		err = brcmf_iovar_data_set(dev, "bus:txglomalign", &iovar,
					   माप(iovar));
	पूर्ण

	अगर (err < 0)
		जाओ करोne;

	bus->tx_hdrlen = SDPCM_HWHDR_LEN + SDPCM_SWHDR_LEN;
	अगर (sdiodev->sg_support) अणु
		bus->txglom = false;
		iovar = cpu_to_le32(1);
		err = brcmf_iovar_data_set(bus->sdiodev->dev, "bus:rxglom",
					   &iovar, माप(iovar));
		अगर (err < 0) अणु
			/* bus:rxglom is allowed to fail */
			err = 0;
		पूर्ण अन्यथा अणु
			bus->txglom = true;
			bus->tx_hdrlen += SDPCM_HWEXT_LEN;
		पूर्ण
	पूर्ण
	brcmf_bus_add_txhdrlen(bus->sdiodev->dev, bus->tx_hdrlen);

करोne:
	वापस err;
पूर्ण

अटल माप_प्रकार brcmf_sdio_bus_get_ramsize(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;

	वापस bus->ci->ramsize - bus->ci->srsize;
पूर्ण

अटल पूर्णांक brcmf_sdio_bus_get_memdump(काष्ठा device *dev, व्योम *data,
				      माप_प्रकार mem_size)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiodev->bus;
	पूर्णांक err;
	पूर्णांक address;
	पूर्णांक offset;
	पूर्णांक len;

	brcmf_dbg(INFO, "dump at 0x%08x: size=%zu\n", bus->ci->rambase,
		  mem_size);

	address = bus->ci->rambase;
	offset = err = 0;
	sdio_claim_host(sdiodev->func1);
	जबतक (offset < mem_size) अणु
		len = ((offset + MEMBLOCK) < mem_size) ? MEMBLOCK :
		      mem_size - offset;
		err = brcmf_sdiod_ramrw(sdiodev, false, address, data, len);
		अगर (err) अणु
			brcmf_err("error %d on reading %d membytes at 0x%08x\n",
				  err, len, address);
			जाओ करोne;
		पूर्ण
		data += len;
		offset += len;
		address += len;
	पूर्ण

करोne:
	sdio_release_host(sdiodev->func1);
	वापस err;
पूर्ण

व्योम brcmf_sdio_trigger_dpc(काष्ठा brcmf_sdio *bus)
अणु
	अगर (!bus->dpc_triggered) अणु
		bus->dpc_triggered = true;
		queue_work(bus->brcmf_wq, &bus->datawork);
	पूर्ण
पूर्ण

व्योम brcmf_sdio_isr(काष्ठा brcmf_sdio *bus, bool in_isr)
अणु
	brcmf_dbg(TRACE, "Enter\n");

	अगर (!bus) अणु
		brcmf_err("bus is null pointer, exiting\n");
		वापस;
	पूर्ण

	/* Count the पूर्णांकerrupt call */
	bus->sdcnt.पूर्णांकrcount++;
	अगर (in_isr)
		atomic_set(&bus->ipend, 1);
	अन्यथा
		अगर (brcmf_sdio_पूर्णांकr_rstatus(bus)) अणु
			brcmf_err("failed backplane access\n");
		पूर्ण

	/* Disable additional पूर्णांकerrupts (is this needed now)? */
	अगर (!bus->पूर्णांकr)
		brcmf_err("isr w/o interrupt configured!\n");

	bus->dpc_triggered = true;
	queue_work(bus->brcmf_wq, &bus->datawork);
पूर्ण

अटल व्योम brcmf_sdio_bus_watchकरोg(काष्ठा brcmf_sdio *bus)
अणु
	brcmf_dbg(TIMER, "Enter\n");

	/* Poll period: check device अगर appropriate. */
	अगर (!bus->sr_enabled &&
	    bus->poll && (++bus->polltick >= bus->pollrate)) अणु
		u32 पूर्णांकstatus = 0;

		/* Reset poll tick */
		bus->polltick = 0;

		/* Check device अगर no पूर्णांकerrupts */
		अगर (!bus->पूर्णांकr ||
		    (bus->sdcnt.पूर्णांकrcount == bus->sdcnt.lastपूर्णांकrs)) अणु

			अगर (!bus->dpc_triggered) अणु
				u8 devpend;

				sdio_claim_host(bus->sdiodev->func1);
				devpend = brcmf_sdiod_func0_rb(bus->sdiodev,
						  SDIO_CCCR_INTx, शून्य);
				sdio_release_host(bus->sdiodev->func1);
				पूर्णांकstatus = devpend & (INTR_STATUS_FUNC1 |
						       INTR_STATUS_FUNC2);
			पूर्ण

			/* If there is something, make like the ISR and
				 schedule the DPC */
			अगर (पूर्णांकstatus) अणु
				bus->sdcnt.pollcnt++;
				atomic_set(&bus->ipend, 1);

				bus->dpc_triggered = true;
				queue_work(bus->brcmf_wq, &bus->datawork);
			पूर्ण
		पूर्ण

		/* Update पूर्णांकerrupt tracking */
		bus->sdcnt.lastपूर्णांकrs = bus->sdcnt.पूर्णांकrcount;
	पूर्ण
#अगर_घोषित DEBUG
	/* Poll क्रम console output periodically */
	अगर (bus->sdiodev->state == BRCMF_SDIOD_DATA && BRCMF_FWCON_ON() &&
	    bus->console_पूर्णांकerval != 0) अणु
		bus->console.count += jअगरfies_to_msecs(BRCMF_WD_POLL);
		अगर (bus->console.count >= bus->console_पूर्णांकerval) अणु
			bus->console.count -= bus->console_पूर्णांकerval;
			sdio_claim_host(bus->sdiodev->func1);
			/* Make sure backplane घड़ी is on */
			brcmf_sdio_bus_sleep(bus, false, false);
			अगर (brcmf_sdio_पढ़ोconsole(bus) < 0)
				/* stop on error */
				bus->console_पूर्णांकerval = 0;
			sdio_release_host(bus->sdiodev->func1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर				/* DEBUG */

	/* On idle समयout clear activity flag and/or turn off घड़ी */
	अगर (!bus->dpc_triggered) अणु
		rmb();
		अगर ((!bus->dpc_running) && (bus->idleसमय > 0) &&
		    (bus->clkstate == CLK_AVAIL)) अणु
			bus->idlecount++;
			अगर (bus->idlecount > bus->idleसमय) अणु
				brcmf_dbg(SDIO, "idle\n");
				sdio_claim_host(bus->sdiodev->func1);
#अगर_घोषित DEBUG
				अगर (!BRCMF_FWCON_ON() ||
				    bus->console_पूर्णांकerval == 0)
#पूर्ण_अगर
					brcmf_sdio_wd_समयr(bus, false);
				bus->idlecount = 0;
				brcmf_sdio_bus_sleep(bus, true, false);
				sdio_release_host(bus->sdiodev->func1);
			पूर्ण
		पूर्ण अन्यथा अणु
			bus->idlecount = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		bus->idlecount = 0;
	पूर्ण
पूर्ण

अटल व्योम brcmf_sdio_dataworker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_sdio *bus = container_of(work, काष्ठा brcmf_sdio,
					      datawork);

	bus->dpc_running = true;
	wmb();
	जबतक (READ_ONCE(bus->dpc_triggered)) अणु
		bus->dpc_triggered = false;
		brcmf_sdio_dpc(bus);
		bus->idlecount = 0;
	पूर्ण
	bus->dpc_running = false;
	अगर (brcmf_sdiod_मुक्तzing(bus->sdiodev)) अणु
		brcmf_sdiod_change_state(bus->sdiodev, BRCMF_SDIOD_DOWN);
		brcmf_sdiod_try_मुक्तze(bus->sdiodev);
		brcmf_sdiod_change_state(bus->sdiodev, BRCMF_SDIOD_DATA);
	पूर्ण
पूर्ण

अटल व्योम
brcmf_sdio_drivestrengthinit(काष्ठा brcmf_sdio_dev *sdiodev,
			     काष्ठा brcmf_chip *ci, u32 drivestrength)
अणु
	स्थिर काष्ठा sdiod_drive_str *str_tab = शून्य;
	u32 str_mask;
	u32 str_shअगरt;
	u32 i;
	u32 drivestrength_sel = 0;
	u32 cc_data_temp;
	u32 addr;

	अगर (!(ci->cc_caps & CC_CAP_PMU))
		वापस;

	चयन (SDIOD_DRVSTR_KEY(ci->chip, ci->pmurev)) अणु
	हाल SDIOD_DRVSTR_KEY(BRCM_CC_4330_CHIP_ID, 12):
		str_tab = sdiod_drvstr_tab1_1v8;
		str_mask = 0x00003800;
		str_shअगरt = 11;
		अवरोध;
	हाल SDIOD_DRVSTR_KEY(BRCM_CC_4334_CHIP_ID, 17):
		str_tab = sdiod_drvstr_tab6_1v8;
		str_mask = 0x00001800;
		str_shअगरt = 11;
		अवरोध;
	हाल SDIOD_DRVSTR_KEY(BRCM_CC_43143_CHIP_ID, 17):
		/* note: 43143 करोes not support tristate */
		i = ARRAY_SIZE(sdiod_drvstr_tab2_3v3) - 1;
		अगर (drivestrength >= sdiod_drvstr_tab2_3v3[i].strength) अणु
			str_tab = sdiod_drvstr_tab2_3v3;
			str_mask = 0x00000007;
			str_shअगरt = 0;
		पूर्ण अन्यथा
			brcmf_err("Invalid SDIO Drive strength for chip %s, strength=%d\n",
				  ci->name, drivestrength);
		अवरोध;
	हाल SDIOD_DRVSTR_KEY(BRCM_CC_43362_CHIP_ID, 13):
		str_tab = sdiod_drive_strength_tab5_1v8;
		str_mask = 0x00003800;
		str_shअगरt = 11;
		अवरोध;
	शेष:
		brcmf_dbg(INFO, "No SDIO driver strength init needed for chip %s rev %d pmurev %d\n",
			  ci->name, ci->chiprev, ci->pmurev);
		अवरोध;
	पूर्ण

	अगर (str_tab != शून्य) अणु
		काष्ठा brcmf_core *pmu = brcmf_chip_get_pmu(ci);

		क्रम (i = 0; str_tab[i].strength != 0; i++) अणु
			अगर (drivestrength >= str_tab[i].strength) अणु
				drivestrength_sel = str_tab[i].sel;
				अवरोध;
			पूर्ण
		पूर्ण
		addr = CORE_CC_REG(pmu->base, chipcontrol_addr);
		brcmf_sdiod_ग_लिखोl(sdiodev, addr, 1, शून्य);
		cc_data_temp = brcmf_sdiod_पढ़ोl(sdiodev, addr, शून्य);
		cc_data_temp &= ~str_mask;
		drivestrength_sel <<= str_shअगरt;
		cc_data_temp |= drivestrength_sel;
		brcmf_sdiod_ग_लिखोl(sdiodev, addr, cc_data_temp, शून्य);

		brcmf_dbg(INFO, "SDIO: %d mA (req=%d mA) drive strength selected, set to 0x%08x\n",
			  str_tab[i].strength, drivestrength, cc_data_temp);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_sdio_buscoreprep(व्योम *ctx)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev = ctx;
	पूर्णांक err = 0;
	u8 clkval, clkset;

	/* Try क्रमcing SDIO core to करो ALPAvail request only */
	clkset = SBSDIO_FORCE_HW_CLKREQ_OFF | SBSDIO_ALP_AVAIL_REQ;
	brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, clkset, &err);
	अगर (err) अणु
		brcmf_err("error writing for HT off\n");
		वापस err;
	पूर्ण

	/* If रेजिस्टर supported, रुको क्रम ALPAvail and then क्रमce ALP */
	/* This may take up to 15 milliseconds */
	clkval = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, शून्य);

	अगर ((clkval & ~SBSDIO_AVBITS) != clkset) अणु
		brcmf_err("ChipClkCSR access: wrote 0x%02x read 0x%02x\n",
			  clkset, clkval);
		वापस -EACCES;
	पूर्ण

	SPINWAIT(((clkval = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
					      शून्य)),
		 !SBSDIO_ALPAV(clkval)),
		 PMU_MAX_TRANSITION_DLY);

	अगर (!SBSDIO_ALPAV(clkval)) अणु
		brcmf_err("timeout on ALPAV wait, clkval 0x%02x\n",
			  clkval);
		वापस -EBUSY;
	पूर्ण

	clkset = SBSDIO_FORCE_HW_CLKREQ_OFF | SBSDIO_FORCE_ALP;
	brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, clkset, &err);
	udelay(65);

	/* Also, disable the extra SDIO pull-ups */
	brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_SDIOPULLUP, 0, शून्य);

	वापस 0;
पूर्ण

अटल व्योम brcmf_sdio_buscore_activate(व्योम *ctx, काष्ठा brcmf_chip *chip,
					u32 rstvec)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev = ctx;
	काष्ठा brcmf_core *core = sdiodev->bus->sdio_core;
	u32 reg_addr;

	/* clear all पूर्णांकerrupts */
	reg_addr = core->base + SD_REG(पूर्णांकstatus);
	brcmf_sdiod_ग_लिखोl(sdiodev, reg_addr, 0xFFFFFFFF, शून्य);

	अगर (rstvec)
		/* Write reset vector to address 0 */
		brcmf_sdiod_ramrw(sdiodev, true, 0, (व्योम *)&rstvec,
				  माप(rstvec));
पूर्ण

अटल u32 brcmf_sdio_buscore_पढ़ो32(व्योम *ctx, u32 addr)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev = ctx;
	u32 val, rev;

	val = brcmf_sdiod_पढ़ोl(sdiodev, addr, शून्य);

	/*
	 * this is a bit of special handling अगर पढ़ोing the chipcommon chipid
	 * रेजिस्टर. The 4339 is a next-gen of the 4335. It uses the same
	 * SDIO device id as 4335 and the chipid रेजिस्टर वापसs 4335 as well.
	 * It can be identअगरied as 4339 by looking at the chip revision. It
	 * is corrected here so the chip.c module has the right info.
	 */
	अगर (addr == CORE_CC_REG(SI_ENUM_BASE, chipid) &&
	    (sdiodev->func1->device == SDIO_DEVICE_ID_BROADCOM_4339 ||
	     sdiodev->func1->device == SDIO_DEVICE_ID_BROADCOM_4335_4339)) अणु
		rev = (val & CID_REV_MASK) >> CID_REV_SHIFT;
		अगर (rev >= 2) अणु
			val &= ~CID_ID_MASK;
			val |= BRCM_CC_4339_CHIP_ID;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम brcmf_sdio_buscore_ग_लिखो32(व्योम *ctx, u32 addr, u32 val)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev = ctx;

	brcmf_sdiod_ग_लिखोl(sdiodev, addr, val, शून्य);
पूर्ण

अटल स्थिर काष्ठा brcmf_buscore_ops brcmf_sdio_buscore_ops = अणु
	.prepare = brcmf_sdio_buscoreprep,
	.activate = brcmf_sdio_buscore_activate,
	.पढ़ो32 = brcmf_sdio_buscore_पढ़ो32,
	.ग_लिखो32 = brcmf_sdio_buscore_ग_लिखो32,
पूर्ण;

अटल bool
brcmf_sdio_probe_attach(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_sdio_dev *sdiodev;
	u8 clkctl = 0;
	पूर्णांक err = 0;
	पूर्णांक reg_addr;
	u32 reg_val;
	u32 drivestrength;

	sdiodev = bus->sdiodev;
	sdio_claim_host(sdiodev->func1);

	pr_debug("F1 signature read @0x18000000=0x%4x\n",
		 brcmf_sdiod_पढ़ोl(sdiodev, SI_ENUM_BASE, शून्य));

	/*
	 * Force PLL off until brcmf_chip_attach()
	 * programs PLL control regs
	 */

	brcmf_sdiod_ग_लिखोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, BRCMF_INIT_CLKCTL1,
			   &err);
	अगर (!err)
		clkctl = brcmf_sdiod_पढ़ोb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
					   &err);

	अगर (err || ((clkctl & ~SBSDIO_AVBITS) != BRCMF_INIT_CLKCTL1)) अणु
		brcmf_err("ChipClkCSR access: err %d wrote 0x%02x read 0x%02x\n",
			  err, BRCMF_INIT_CLKCTL1, clkctl);
		जाओ fail;
	पूर्ण

	bus->ci = brcmf_chip_attach(sdiodev, &brcmf_sdio_buscore_ops);
	अगर (IS_ERR(bus->ci)) अणु
		brcmf_err("brcmf_chip_attach failed!\n");
		bus->ci = शून्य;
		जाओ fail;
	पूर्ण

	/* Pick up the SDIO core info काष्ठा from chip.c */
	bus->sdio_core   = brcmf_chip_get_core(bus->ci, BCMA_CORE_SDIO_DEV);
	अगर (!bus->sdio_core)
		जाओ fail;

	/* Pick up the CHIPCOMMON core info काष्ठा, क्रम bulk IO in bcmsdh.c */
	sdiodev->cc_core = brcmf_chip_get_core(bus->ci, BCMA_CORE_CHIPCOMMON);
	अगर (!sdiodev->cc_core)
		जाओ fail;

	sdiodev->settings = brcmf_get_module_param(sdiodev->dev,
						   BRCMF_BUSTYPE_SDIO,
						   bus->ci->chip,
						   bus->ci->chiprev);
	अगर (!sdiodev->settings) अणु
		brcmf_err("Failed to get device parameters\n");
		जाओ fail;
	पूर्ण
	/* platक्रमm specअगरic configuration:
	 *   alignments must be at least 4 bytes क्रम ADMA
	 */
	bus->head_align = ALIGNMENT;
	bus->sgentry_align = ALIGNMENT;
	अगर (sdiodev->settings->bus.sdio.sd_head_align > ALIGNMENT)
		bus->head_align = sdiodev->settings->bus.sdio.sd_head_align;
	अगर (sdiodev->settings->bus.sdio.sd_sgentry_align > ALIGNMENT)
		bus->sgentry_align =
				sdiodev->settings->bus.sdio.sd_sgentry_align;

	/* allocate scatter-gather table. sg support
	 * will be disabled upon allocation failure.
	 */
	brcmf_sdiod_sgtable_alloc(sdiodev);

#अगर_घोषित CONFIG_PM_SLEEP
	/* wowl can be supported when KEEP_POWER is true and (WAKE_SDIO_IRQ
	 * is true or when platक्रमm data OOB irq is true).
	 */
	अगर ((sdio_get_host_pm_caps(sdiodev->func1) & MMC_PM_KEEP_POWER) &&
	    ((sdio_get_host_pm_caps(sdiodev->func1) & MMC_PM_WAKE_SDIO_IRQ) ||
	     (sdiodev->settings->bus.sdio.oob_irq_supported)))
		sdiodev->bus_अगर->wowl_supported = true;
#पूर्ण_अगर

	अगर (brcmf_sdio_kso_init(bus)) अणु
		brcmf_err("error enabling KSO\n");
		जाओ fail;
	पूर्ण

	अगर (sdiodev->settings->bus.sdio.drive_strength)
		drivestrength = sdiodev->settings->bus.sdio.drive_strength;
	अन्यथा
		drivestrength = DEFAULT_SDIO_DRIVE_STRENGTH;
	brcmf_sdio_drivestrengthinit(sdiodev, bus->ci, drivestrength);

	/* Set card control so an SDIO card reset करोes a WLAN backplane reset */
	reg_val = brcmf_sdiod_func0_rb(sdiodev, SDIO_CCCR_BRCM_CARDCTRL, &err);
	अगर (err)
		जाओ fail;

	reg_val |= SDIO_CCCR_BRCM_CARDCTRL_WLANRESET;

	brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_BRCM_CARDCTRL, reg_val, &err);
	अगर (err)
		जाओ fail;

	/* set PMUControl so a backplane reset करोes PMU state reload */
	reg_addr = CORE_CC_REG(brcmf_chip_get_pmu(bus->ci)->base, pmucontrol);
	reg_val = brcmf_sdiod_पढ़ोl(sdiodev, reg_addr, &err);
	अगर (err)
		जाओ fail;

	reg_val |= (BCMA_CC_PMU_CTL_RES_RELOAD << BCMA_CC_PMU_CTL_RES_SHIFT);

	brcmf_sdiod_ग_लिखोl(sdiodev, reg_addr, reg_val, &err);
	अगर (err)
		जाओ fail;

	sdio_release_host(sdiodev->func1);

	brcmu_pktq_init(&bus->txq, (PRIOMASK + 1), TXQLEN);

	/* allocate header buffer */
	bus->hdrbuf = kzalloc(MAX_HDR_READ + bus->head_align, GFP_KERNEL);
	अगर (!bus->hdrbuf)
		वापस false;
	/* Locate an appropriately-aligned portion of hdrbuf */
	bus->rxhdr = (u8 *) roundup((अचिन्हित दीर्घ)&bus->hdrbuf[0],
				    bus->head_align);

	/* Set the poll and/or पूर्णांकerrupt flags */
	bus->पूर्णांकr = true;
	bus->poll = false;
	अगर (bus->poll)
		bus->pollrate = 1;

	वापस true;

fail:
	sdio_release_host(sdiodev->func1);
	वापस false;
पूर्ण

अटल पूर्णांक
brcmf_sdio_watchकरोg_thपढ़ो(व्योम *data)
अणु
	काष्ठा brcmf_sdio *bus = (काष्ठा brcmf_sdio *)data;
	पूर्णांक रुको;

	allow_संकेत(संक_इति);
	/* Run until संकेत received */
	brcmf_sdiod_मुक्तzer_count(bus->sdiodev);
	जबतक (1) अणु
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		brcmf_sdiod_मुक्तzer_uncount(bus->sdiodev);
		रुको = रुको_क्रम_completion_पूर्णांकerruptible(&bus->watchकरोg_रुको);
		brcmf_sdiod_मुक्तzer_count(bus->sdiodev);
		brcmf_sdiod_try_मुक्तze(bus->sdiodev);
		अगर (!रुको) अणु
			brcmf_sdio_bus_watchकरोg(bus);
			/* Count the tick क्रम reference */
			bus->sdcnt.tickcnt++;
			reinit_completion(&bus->watchकरोg_रुको);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
brcmf_sdio_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा brcmf_sdio *bus = from_समयr(bus, t, समयr);

	अगर (bus->watchकरोg_tsk) अणु
		complete(&bus->watchकरोg_रुको);
		/* Reschedule the watchकरोg */
		अगर (bus->wd_active)
			mod_समयr(&bus->समयr,
				  jअगरfies + BRCMF_WD_POLL);
	पूर्ण
पूर्ण

अटल
पूर्णांक brcmf_sdio_get_fwname(काष्ठा device *dev, स्थिर अक्षर *ext, u8 *fw_name)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ext, fw_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(bus_अगर->chip, bus_अगर->chiprev,
				       brcmf_sdio_fwnames,
				       ARRAY_SIZE(brcmf_sdio_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस -ENOMEM;

	kमुक्त(fwreq);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_sdio_bus_reset(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiodev = bus_अगर->bus_priv.sdio;

	brcmf_dbg(SDIO, "Enter\n");

	/* start by unरेजिस्टरing irqs */
	brcmf_sdiod_पूर्णांकr_unरेजिस्टर(sdiodev);

	brcmf_sdiod_हटाओ(sdiodev);

	/* reset the adapter */
	sdio_claim_host(sdiodev->func1);
	mmc_hw_reset(sdiodev->func1->card->host);
	sdio_release_host(sdiodev->func1);

	brcmf_bus_change_state(sdiodev->bus_अगर, BRCMF_BUS_DOWN);

	ret = brcmf_sdiod_probe(sdiodev);
	अगर (ret) अणु
		brcmf_err("Failed to probe after sdio device reset: ret %d\n",
			  ret);
		brcmf_sdiod_हटाओ(sdiodev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा brcmf_bus_ops brcmf_sdio_bus_ops = अणु
	.stop = brcmf_sdio_bus_stop,
	.preinit = brcmf_sdio_bus_preinit,
	.txdata = brcmf_sdio_bus_txdata,
	.txctl = brcmf_sdio_bus_txctl,
	.rxctl = brcmf_sdio_bus_rxctl,
	.gettxq = brcmf_sdio_bus_gettxq,
	.wowl_config = brcmf_sdio_wowl_config,
	.get_ramsize = brcmf_sdio_bus_get_ramsize,
	.get_memdump = brcmf_sdio_bus_get_memdump,
	.get_fwname = brcmf_sdio_get_fwname,
	.debugfs_create = brcmf_sdio_debugfs_create,
	.reset = brcmf_sdio_bus_reset
पूर्ण;

#घोषणा BRCMF_SDIO_FW_CODE	0
#घोषणा BRCMF_SDIO_FW_NVRAM	1

अटल व्योम brcmf_sdio_firmware_callback(काष्ठा device *dev, पूर्णांक err,
					 काष्ठा brcmf_fw_request *fwreq)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_sdio_dev *sdiod = bus_अगर->bus_priv.sdio;
	काष्ठा brcmf_sdio *bus = sdiod->bus;
	काष्ठा brcmf_core *core = bus->sdio_core;
	स्थिर काष्ठा firmware *code;
	व्योम *nvram;
	u32 nvram_len;
	u8 saveclk, bpreq;
	u8 devctl;

	brcmf_dbg(TRACE, "Enter: dev=%s, err=%d\n", dev_name(dev), err);

	अगर (err)
		जाओ fail;

	code = fwreq->items[BRCMF_SDIO_FW_CODE].binary;
	nvram = fwreq->items[BRCMF_SDIO_FW_NVRAM].nv_data.data;
	nvram_len = fwreq->items[BRCMF_SDIO_FW_NVRAM].nv_data.len;
	kमुक्त(fwreq);

	/* try to करोwnload image and nvram to the करोngle */
	bus->alp_only = true;
	err = brcmf_sdio_करोwnload_firmware(bus, code, nvram, nvram_len);
	अगर (err)
		जाओ fail;
	bus->alp_only = false;

	/* Start the watchकरोg समयr */
	bus->sdcnt.tickcnt = 0;
	brcmf_sdio_wd_समयr(bus, true);

	sdio_claim_host(sdiod->func1);

	/* Make sure backplane घड़ी is on, needed to generate F2 पूर्णांकerrupt */
	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);
	अगर (bus->clkstate != CLK_AVAIL)
		जाओ release;

	/* Force घड़ीs on backplane to be sure F2 पूर्णांकerrupt propagates */
	saveclk = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR, &err);
	अगर (!err) अणु
		bpreq = saveclk;
		bpreq |= brcmf_chip_is_ulp(bus->ci) ?
			SBSDIO_HT_AVAIL_REQ : SBSDIO_FORCE_HT;
		brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR,
				   bpreq, &err);
	पूर्ण
	अगर (err) अणु
		brcmf_err("Failed to force clock for F2: err %d\n", err);
		जाओ release;
	पूर्ण

	/* Enable function 2 (frame transfers) */
	brcmf_sdiod_ग_लिखोl(sdiod, core->base + SD_REG(tosbmailboxdata),
			   SDPCM_PROT_VERSION << SMB_DATA_VERSION_SHIFT, शून्य);

	err = sdio_enable_func(sdiod->func2);

	brcmf_dbg(INFO, "enable F2: err=%d\n", err);

	/* If F2 successfully enabled, set core and enable पूर्णांकerrupts */
	अगर (!err) अणु
		/* Set up the पूर्णांकerrupt mask and enable पूर्णांकerrupts */
		bus->hostपूर्णांकmask = HOSTINTMASK;
		brcmf_sdiod_ग_लिखोl(sdiod, core->base + SD_REG(hostपूर्णांकmask),
				   bus->hostपूर्णांकmask, शून्य);

		चयन (sdiod->func1->device) अणु
		हाल SDIO_DEVICE_ID_BROADCOM_CYPRESS_4373:
			brcmf_dbg(INFO, "set F2 watermark to 0x%x*4 bytes\n",
				  CY_4373_F2_WATERMARK);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   CY_4373_F2_WATERMARK, &err);
			devctl = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_DEVICE_CTL,
						   &err);
			devctl |= SBSDIO_DEVCTL_F2WM_ENAB;
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_DEVICE_CTL, devctl,
					   &err);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_MESBUSYCTRL,
					   CY_4373_F1_MESBUSYCTRL, &err);
			अवरोध;
		हाल SDIO_DEVICE_ID_BROADCOM_CYPRESS_43012:
			brcmf_dbg(INFO, "set F2 watermark to 0x%x*4 bytes\n",
				  CY_43012_F2_WATERMARK);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   CY_43012_F2_WATERMARK, &err);
			devctl = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_DEVICE_CTL,
						   &err);
			devctl |= SBSDIO_DEVCTL_F2WM_ENAB;
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_DEVICE_CTL, devctl,
					   &err);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_MESBUSYCTRL,
					   CY_43012_MESBUSYCTRL, &err);
			अवरोध;
		हाल SDIO_DEVICE_ID_BROADCOM_4329:
		हाल SDIO_DEVICE_ID_BROADCOM_4339:
			brcmf_dbg(INFO, "set F2 watermark to 0x%x*4 bytes\n",
				  CY_4339_F2_WATERMARK);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   CY_4339_F2_WATERMARK, &err);
			devctl = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_DEVICE_CTL,
						   &err);
			devctl |= SBSDIO_DEVCTL_F2WM_ENAB;
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_DEVICE_CTL, devctl,
					   &err);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_MESBUSYCTRL,
					   CY_4339_MESBUSYCTRL, &err);
			अवरोध;
		हाल SDIO_DEVICE_ID_BROADCOM_43455:
			brcmf_dbg(INFO, "set F2 watermark to 0x%x*4 bytes\n",
				  CY_43455_F2_WATERMARK);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   CY_43455_F2_WATERMARK, &err);
			devctl = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_DEVICE_CTL,
						   &err);
			devctl |= SBSDIO_DEVCTL_F2WM_ENAB;
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_DEVICE_CTL, devctl,
					   &err);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_MESBUSYCTRL,
					   CY_43455_MESBUSYCTRL, &err);
			अवरोध;
		हाल SDIO_DEVICE_ID_BROADCOM_4359:
		हाल SDIO_DEVICE_ID_BROADCOM_4354:
		हाल SDIO_DEVICE_ID_BROADCOM_4356:
			brcmf_dbg(INFO, "set F2 watermark to 0x%x*4 bytes\n",
				  CY_435X_F2_WATERMARK);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   CY_435X_F2_WATERMARK, &err);
			devctl = brcmf_sdiod_पढ़ोb(sdiod, SBSDIO_DEVICE_CTL,
						   &err);
			devctl |= SBSDIO_DEVCTL_F2WM_ENAB;
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_DEVICE_CTL, devctl,
					   &err);
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_MESBUSYCTRL,
					   CY_435X_F1_MESBUSYCTRL, &err);
			अवरोध;
		शेष:
			brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_WATERMARK,
					   DEFAULT_F2_WATERMARK, &err);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable F2 again */
		sdio_disable_func(sdiod->func2);
		जाओ checkdied;
	पूर्ण

	अगर (brcmf_chip_sr_capable(bus->ci)) अणु
		brcmf_sdio_sr_init(bus);
	पूर्ण अन्यथा अणु
		/* Restore previous घड़ी setting */
		brcmf_sdiod_ग_लिखोb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR,
				   saveclk, &err);
	पूर्ण

	अगर (err == 0) अणु
		/* Assign bus पूर्णांकerface call back */
		sdiod->bus_अगर->dev = sdiod->dev;
		sdiod->bus_अगर->ops = &brcmf_sdio_bus_ops;
		sdiod->bus_अगर->chip = bus->ci->chip;
		sdiod->bus_अगर->chiprev = bus->ci->chiprev;

		/* Allow full data communication using DPC from now on. */
		brcmf_sdiod_change_state(bus->sdiodev, BRCMF_SDIOD_DATA);

		err = brcmf_sdiod_पूर्णांकr_रेजिस्टर(sdiod);
		अगर (err != 0)
			brcmf_err("intr register failed:%d\n", err);
	पूर्ण

	/* If we didn't come up, turn off backplane घड़ी */
	अगर (err != 0) अणु
		brcmf_sdio_clkctl(bus, CLK_NONE, false);
		जाओ checkdied;
	पूर्ण

	sdio_release_host(sdiod->func1);

	err = brcmf_alloc(sdiod->dev, sdiod->settings);
	अगर (err) अणु
		brcmf_err("brcmf_alloc failed\n");
		जाओ claim;
	पूर्ण

	/* Attach to the common layer, reserve hdr space */
	err = brcmf_attach(sdiod->dev);
	अगर (err != 0) अणु
		brcmf_err("brcmf_attach failed\n");
		जाओ मुक्त;
	पूर्ण

	/* पढ़ोy */
	वापस;

मुक्त:
	brcmf_मुक्त(sdiod->dev);
claim:
	sdio_claim_host(sdiod->func1);
checkdied:
	brcmf_sdio_checkdied(bus);
release:
	sdio_release_host(sdiod->func1);
fail:
	brcmf_dbg(TRACE, "failed: dev=%s, err=%d\n", dev_name(dev), err);
	device_release_driver(&sdiod->func2->dev);
	device_release_driver(dev);
पूर्ण

अटल काष्ठा brcmf_fw_request *
brcmf_sdio_prepare_fw_request(काष्ठा brcmf_sdio *bus)
अणु
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ".bin", bus->sdiodev->fw_name पूर्ण,
		अणु ".txt", bus->sdiodev->nvram_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(bus->ci->chip, bus->ci->chiprev,
				       brcmf_sdio_fwnames,
				       ARRAY_SIZE(brcmf_sdio_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस शून्य;

	fwreq->items[BRCMF_SDIO_FW_CODE].type = BRCMF_FW_TYPE_BINARY;
	fwreq->items[BRCMF_SDIO_FW_NVRAM].type = BRCMF_FW_TYPE_NVRAM;
	fwreq->board_type = bus->sdiodev->settings->board_type;

	वापस fwreq;
पूर्ण

काष्ठा brcmf_sdio *brcmf_sdio_probe(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	पूर्णांक ret;
	काष्ठा brcmf_sdio *bus;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा brcmf_fw_request *fwreq;

	brcmf_dbg(TRACE, "Enter\n");

	/* Allocate निजी bus पूर्णांकerface state */
	bus = kzalloc(माप(काष्ठा brcmf_sdio), GFP_ATOMIC);
	अगर (!bus)
		जाओ fail;

	bus->sdiodev = sdiodev;
	sdiodev->bus = bus;
	skb_queue_head_init(&bus->glom);
	bus->txbound = BRCMF_TXBOUND;
	bus->rxbound = BRCMF_RXBOUND;
	bus->txminmax = BRCMF_TXMINMAX;
	bus->tx_seq = SDPCM_SEQ_WRAP - 1;

	/* single-thपढ़ोed workqueue */
	wq = alloc_ordered_workqueue("brcmf_wq/%s", WQ_MEM_RECLAIM,
				     dev_name(&sdiodev->func1->dev));
	अगर (!wq) अणु
		brcmf_err("insufficient memory to create txworkqueue\n");
		जाओ fail;
	पूर्ण
	brcmf_sdiod_मुक्तzer_count(sdiodev);
	INIT_WORK(&bus->datawork, brcmf_sdio_dataworker);
	bus->brcmf_wq = wq;

	/* attempt to attach to the करोngle */
	अगर (!(brcmf_sdio_probe_attach(bus))) अणु
		brcmf_err("brcmf_sdio_probe_attach failed\n");
		जाओ fail;
	पूर्ण

	spin_lock_init(&bus->rxctl_lock);
	spin_lock_init(&bus->txq_lock);
	init_रुकोqueue_head(&bus->ctrl_रुको);
	init_रुकोqueue_head(&bus->dcmd_resp_रुको);

	/* Set up the watchकरोg समयr */
	समयr_setup(&bus->समयr, brcmf_sdio_watchकरोg, 0);
	/* Initialize watchकरोg thपढ़ो */
	init_completion(&bus->watchकरोg_रुको);
	bus->watchकरोg_tsk = kthपढ़ो_run(brcmf_sdio_watchकरोg_thपढ़ो,
					bus, "brcmf_wdog/%s",
					dev_name(&sdiodev->func1->dev));
	अगर (IS_ERR(bus->watchकरोg_tsk)) अणु
		pr_warn("brcmf_watchdog thread failed to start\n");
		bus->watchकरोg_tsk = शून्य;
	पूर्ण
	/* Initialize DPC thपढ़ो */
	bus->dpc_triggered = false;
	bus->dpc_running = false;

	/* शेष sdio bus header length क्रम tx packet */
	bus->tx_hdrlen = SDPCM_HWHDR_LEN + SDPCM_SWHDR_LEN;

	/* Query the F2 block size, set roundup accordingly */
	bus->blocksize = bus->sdiodev->func2->cur_blksize;
	bus->roundup = min(max_roundup, bus->blocksize);

	sdio_claim_host(bus->sdiodev->func1);

	/* Disable F2 to clear any पूर्णांकermediate frame state on the करोngle */
	sdio_disable_func(bus->sdiodev->func2);

	bus->rxflow = false;

	/* Done with backplane-dependent accesses, can drop घड़ी... */
	brcmf_sdiod_ग_लिखोb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, 0, शून्य);

	sdio_release_host(bus->sdiodev->func1);

	/* ...and initialize घड़ी/घातer states */
	bus->clkstate = CLK_SDONLY;
	bus->idleसमय = BRCMF_IDLE_INTERVAL;
	bus->idleघड़ी = BRCMF_IDLE_ACTIVE;

	/* SR state */
	bus->sr_enabled = false;

	brcmf_dbg(INFO, "completed!!\n");

	fwreq = brcmf_sdio_prepare_fw_request(bus);
	अगर (!fwreq) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = brcmf_fw_get_firmwares(sdiodev->dev, fwreq,
				     brcmf_sdio_firmware_callback);
	अगर (ret != 0) अणु
		brcmf_err("async firmware request failed: %d\n", ret);
		kमुक्त(fwreq);
		जाओ fail;
	पूर्ण

	वापस bus;

fail:
	brcmf_sdio_हटाओ(bus);
	वापस शून्य;
पूर्ण

/* Detach and मुक्त everything */
व्योम brcmf_sdio_हटाओ(काष्ठा brcmf_sdio *bus)
अणु
	brcmf_dbg(TRACE, "Enter\n");

	अगर (bus) अणु
		/* Stop watchकरोg task */
		अगर (bus->watchकरोg_tsk) अणु
			send_sig(संक_इति, bus->watchकरोg_tsk, 1);
			kthपढ़ो_stop(bus->watchकरोg_tsk);
			bus->watchकरोg_tsk = शून्य;
		पूर्ण

		/* De-रेजिस्टर पूर्णांकerrupt handler */
		brcmf_sdiod_पूर्णांकr_unरेजिस्टर(bus->sdiodev);

		brcmf_detach(bus->sdiodev->dev);
		brcmf_मुक्त(bus->sdiodev->dev);

		cancel_work_sync(&bus->datawork);
		अगर (bus->brcmf_wq)
			destroy_workqueue(bus->brcmf_wq);

		अगर (bus->ci) अणु
			अगर (bus->sdiodev->state != BRCMF_SDIOD_NOMEDIUM) अणु
				sdio_claim_host(bus->sdiodev->func1);
				brcmf_sdio_wd_समयr(bus, false);
				brcmf_sdio_clkctl(bus, CLK_AVAIL, false);
				/* Leave the device in state where it is
				 * 'passive'. This is करोne by resetting all
				 * necessary cores.
				 */
				msleep(20);
				brcmf_chip_set_passive(bus->ci);
				brcmf_sdio_clkctl(bus, CLK_NONE, false);
				sdio_release_host(bus->sdiodev->func1);
			पूर्ण
			brcmf_chip_detach(bus->ci);
		पूर्ण
		अगर (bus->sdiodev->settings)
			brcmf_release_module_param(bus->sdiodev->settings);

		kमुक्त(bus->rxbuf);
		kमुक्त(bus->hdrbuf);
		kमुक्त(bus);
	पूर्ण

	brcmf_dbg(TRACE, "Disconnected\n");
पूर्ण

व्योम brcmf_sdio_wd_समयr(काष्ठा brcmf_sdio *bus, bool active)
अणु
	/* Totally stop the समयr */
	अगर (!active && bus->wd_active) अणु
		del_समयr_sync(&bus->समयr);
		bus->wd_active = false;
		वापस;
	पूर्ण

	/* करोn't start the wd until fw is loaded */
	अगर (bus->sdiodev->state != BRCMF_SDIOD_DATA)
		वापस;

	अगर (active) अणु
		अगर (!bus->wd_active) अणु
			/* Create समयr again when watchकरोg period is
			   dynamically changed or in the first instance
			 */
			bus->समयr.expires = jअगरfies + BRCMF_WD_POLL;
			add_समयr(&bus->समयr);
			bus->wd_active = true;
		पूर्ण अन्यथा अणु
			/* Re arm the समयr, at last watchकरोg period */
			mod_समयr(&bus->समयr, jअगरfies + BRCMF_WD_POLL);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक brcmf_sdio_sleep(काष्ठा brcmf_sdio *bus, bool sleep)
अणु
	पूर्णांक ret;

	sdio_claim_host(bus->sdiodev->func1);
	ret = brcmf_sdio_bus_sleep(bus, sleep, false);
	sdio_release_host(bus->sdiodev->func1);

	वापस ret;
पूर्ण

