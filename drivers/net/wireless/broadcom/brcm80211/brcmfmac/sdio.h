<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	BRCMFMAC_SDIO_H
#घोषणा	BRCMFMAC_SDIO_H

#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश "firmware.h"

#घोषणा SDIOD_FBR_SIZE		0x100

/* io_en */
#घोषणा SDIO_FUNC_ENABLE_1	0x02
#घोषणा SDIO_FUNC_ENABLE_2	0x04

/* io_rdys */
#घोषणा SDIO_FUNC_READY_1	0x02
#घोषणा SDIO_FUNC_READY_2	0x04

/* पूर्णांकr_status */
#घोषणा INTR_STATUS_FUNC1	0x2
#घोषणा INTR_STATUS_FUNC2	0x4

/* mask of रेजिस्टर map */
#घोषणा REG_F0_REG_MASK		0x7FF
#घोषणा REG_F1_MISC_MASK	0x1FFFF

/* function 0 venकरोr specअगरic CCCR रेजिस्टरs */

#घोषणा SDIO_CCCR_BRCM_CARDCAP			0xf0
#घोषणा SDIO_CCCR_BRCM_CARDCAP_CMD14_SUPPORT	BIT(1)
#घोषणा SDIO_CCCR_BRCM_CARDCAP_CMD14_EXT	BIT(2)
#घोषणा SDIO_CCCR_BRCM_CARDCAP_CMD_NODEC	BIT(3)

/* Interrupt enable bits क्रम each function */
#घोषणा SDIO_CCCR_IEN_FUNC0			BIT(0)
#घोषणा SDIO_CCCR_IEN_FUNC1			BIT(1)
#घोषणा SDIO_CCCR_IEN_FUNC2			BIT(2)

#घोषणा SDIO_CCCR_BRCM_CARDCTRL			0xf1
#घोषणा SDIO_CCCR_BRCM_CARDCTRL_WLANRESET	BIT(1)

#घोषणा SDIO_CCCR_BRCM_SEPINT			0xf2
#घोषणा SDIO_CCCR_BRCM_SEPINT_MASK		BIT(0)
#घोषणा SDIO_CCCR_BRCM_SEPINT_OE		BIT(1)
#घोषणा SDIO_CCCR_BRCM_SEPINT_ACT_HI		BIT(2)

/* function 1 miscellaneous रेजिस्टरs */

/* sprom command and status */
#घोषणा SBSDIO_SPROM_CS			0x10000
/* sprom info रेजिस्टर */
#घोषणा SBSDIO_SPROM_INFO		0x10001
/* sprom indirect access data byte 0 */
#घोषणा SBSDIO_SPROM_DATA_LOW		0x10002
/* sprom indirect access data byte 1 */
#घोषणा SBSDIO_SPROM_DATA_HIGH		0x10003
/* sprom indirect access addr byte 0 */
#घोषणा SBSDIO_SPROM_ADDR_LOW		0x10004
/* gpio select */
#घोषणा SBSDIO_GPIO_SELECT		0x10005
/* gpio output */
#घोषणा SBSDIO_GPIO_OUT			0x10006
/* gpio enable */
#घोषणा SBSDIO_GPIO_EN			0x10007
/* rev < 7, watermark क्रम sdio device TX path */
#घोषणा SBSDIO_WATERMARK		0x10008
/* control busy संकेत generation */
#घोषणा SBSDIO_DEVICE_CTL		0x10009

/* SB Address Winकरोw Low (b15) */
#घोषणा SBSDIO_FUNC1_SBADDRLOW		0x1000A
/* SB Address Winकरोw Mid (b23:b16) */
#घोषणा SBSDIO_FUNC1_SBADDRMID		0x1000B
/* SB Address Winकरोw High (b31:b24)    */
#घोषणा SBSDIO_FUNC1_SBADDRHIGH		0x1000C
/* Frame Control (frame term/पात) */
#घोषणा SBSDIO_FUNC1_FRAMECTRL		0x1000D
/* ChipClockCSR (ALP/HT ctl/status) */
#घोषणा SBSDIO_FUNC1_CHIPCLKCSR		0x1000E
/* SdioPullUp (on cmd, d0-d2) */
#घोषणा SBSDIO_FUNC1_SDIOPULLUP		0x1000F
/* Write Frame Byte Count Low */
#घोषणा SBSDIO_FUNC1_WFRAMEBCLO		0x10019
/* Write Frame Byte Count High */
#घोषणा SBSDIO_FUNC1_WFRAMEBCHI		0x1001A
/* Read Frame Byte Count Low */
#घोषणा SBSDIO_FUNC1_RFRAMEBCLO		0x1001B
/* Read Frame Byte Count High */
#घोषणा SBSDIO_FUNC1_RFRAMEBCHI		0x1001C
/* MesBusyCtl (rev 11) */
#घोषणा SBSDIO_FUNC1_MESBUSYCTRL	0x1001D
/* Watermark क्रम sdio device RX path */
#घोषणा SBSDIO_MESBUSY_RXFIFO_WM_MASK	0x7F
#घोषणा SBSDIO_MESBUSY_RXFIFO_WM_SHIFT	0
/* Enable busy capability क्रम MES access */
#घोषणा SBSDIO_MESBUSYCTRL_ENAB		0x80
#घोषणा SBSDIO_MESBUSYCTRL_ENAB_SHIFT	7

/* Sdio Core Rev 12 */
#घोषणा SBSDIO_FUNC1_WAKEUPCTRL		0x1001E
#घोषणा SBSDIO_FUNC1_WCTRL_ALPWAIT_MASK		0x1
#घोषणा SBSDIO_FUNC1_WCTRL_ALPWAIT_SHIFT	0
#घोषणा SBSDIO_FUNC1_WCTRL_HTWAIT_MASK		0x2
#घोषणा SBSDIO_FUNC1_WCTRL_HTWAIT_SHIFT		1
#घोषणा SBSDIO_FUNC1_SLEEPCSR		0x1001F
#घोषणा SBSDIO_FUNC1_SLEEPCSR_KSO_MASK		0x1
#घोषणा SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT		0
#घोषणा SBSDIO_FUNC1_SLEEPCSR_KSO_EN		1
#घोषणा SBSDIO_FUNC1_SLEEPCSR_DEVON_MASK	0x2
#घोषणा SBSDIO_FUNC1_SLEEPCSR_DEVON_SHIFT	1

#घोषणा SBSDIO_FUNC1_MISC_REG_START	0x10000	/* f1 misc रेजिस्टर start */
#घोषणा SBSDIO_FUNC1_MISC_REG_LIMIT	0x1001F	/* f1 misc रेजिस्टर end */

/* function 1 OCP space */

/* sb offset addr is <= 15 bits, 32k */
#घोषणा SBSDIO_SB_OFT_ADDR_MASK		0x07FFF
#घोषणा SBSDIO_SB_OFT_ADDR_LIMIT	0x08000
/* with b15, maps to 32-bit SB access */
#घोषणा SBSDIO_SB_ACCESS_2_4B_FLAG	0x08000

/* Address bits from SBADDR regs */
#घोषणा SBSDIO_SBWINDOW_MASK		0xffff8000

#घोषणा SDIOH_READ              0	/* Read request */
#घोषणा SDIOH_WRITE             1	/* Write request */

#घोषणा SDIOH_DATA_FIX          0	/* Fixed addressing */
#घोषणा SDIOH_DATA_INC          1	/* Incremental addressing */

/* पूर्णांकernal वापस code */
#घोषणा SUCCESS	0
#घोषणा ERROR	1

/* Packet alignment क्रम most efficient SDIO (can change based on platक्रमm) */
#घोषणा BRCMF_SDALIGN	(1 << 6)

/* watchकरोg polling पूर्णांकerval */
#घोषणा BRCMF_WD_POLL	msecs_to_jअगरfies(10)

/**
 * क्रमागत brcmf_sdiod_state - the state of the bus.
 *
 * @BRCMF_SDIOD_DOWN: Device can be accessed, no DPC.
 * @BRCMF_SDIOD_DATA: Ready क्रम data transfers, DPC enabled.
 * @BRCMF_SDIOD_NOMEDIUM: No medium access to करोngle possible.
 */
क्रमागत brcmf_sdiod_state अणु
	BRCMF_SDIOD_DOWN,
	BRCMF_SDIOD_DATA,
	BRCMF_SDIOD_NOMEDIUM
पूर्ण;

काष्ठा brcmf_sdreg अणु
	पूर्णांक func;
	पूर्णांक offset;
	पूर्णांक value;
पूर्ण;

काष्ठा brcmf_sdio;
काष्ठा brcmf_sdiod_मुक्तzer;

काष्ठा brcmf_sdio_dev अणु
	काष्ठा sdio_func *func1;
	काष्ठा sdio_func *func2;
	u32 sbwad;			/* Save backplane winकरोw address */
	काष्ठा brcmf_core *cc_core;	/* chipcommon core info काष्ठा */
	काष्ठा brcmf_sdio *bus;
	काष्ठा device *dev;
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा brcmf_mp_device *settings;
	bool oob_irq_requested;
	bool sd_irq_requested;
	bool irq_en;			/* irq enable flags */
	spinlock_t irq_en_lock;
	bool sg_support;
	uपूर्णांक max_request_size;
	uलघु max_segment_count;
	uपूर्णांक max_segment_size;
	uपूर्णांक txglomsz;
	काष्ठा sg_table sgtable;
	अक्षर fw_name[BRCMF_FW_NAME_LEN];
	अक्षर nvram_name[BRCMF_FW_NAME_LEN];
	bool wowl_enabled;
	क्रमागत brcmf_sdiod_state state;
	काष्ठा brcmf_sdiod_मुक्तzer *मुक्तzer;
पूर्ण;

/* sdio core रेजिस्टरs */
काष्ठा sdpcmd_regs अणु
	u32 corecontrol;		/* 0x00, rev8 */
	u32 corestatus;			/* rev8 */
	u32 PAD[1];
	u32 biststatus;			/* rev8 */

	/* PCMCIA access */
	u16 pcmciamesportaladdr;	/* 0x010, rev8 */
	u16 PAD[1];
	u16 pcmciamesportalmask;	/* rev8 */
	u16 PAD[1];
	u16 pcmciawrframebc;		/* rev8 */
	u16 PAD[1];
	u16 pcmciaunderflowसमयr;	/* rev8 */
	u16 PAD[1];

	/* पूर्णांकerrupt */
	u32 पूर्णांकstatus;			/* 0x020, rev8 */
	u32 hostपूर्णांकmask;		/* rev8 */
	u32 पूर्णांकmask;			/* rev8 */
	u32 sbपूर्णांकstatus;		/* rev8 */
	u32 sbपूर्णांकmask;			/* rev8 */
	u32 funcपूर्णांकmask;		/* rev4 */
	u32 PAD[2];
	u32 tosbmailbox;		/* 0x040, rev8 */
	u32 tohosपंचांगailbox;		/* rev8 */
	u32 tosbmailboxdata;		/* rev8 */
	u32 tohosपंचांगailboxdata;		/* rev8 */

	/* synchronized access to रेजिस्टरs in SDIO घड़ी करोमुख्य */
	u32 sdioaccess;			/* 0x050, rev8 */
	u32 PAD[3];

	/* PCMCIA frame control */
	u8 pcmciaframectrl;		/* 0x060, rev8 */
	u8 PAD[3];
	u8 pcmciawatermark;		/* rev8 */
	u8 PAD[155];

	/* पूर्णांकerrupt batching control */
	u32 पूर्णांकrcvlazy;			/* 0x100, rev8 */
	u32 PAD[3];

	/* counters */
	u32 cmd52rd;			/* 0x110, rev8 */
	u32 cmd52wr;			/* rev8 */
	u32 cmd53rd;			/* rev8 */
	u32 cmd53wr;			/* rev8 */
	u32 पात;			/* rev8 */
	u32 datacrcerror;		/* rev8 */
	u32 rकरोutofsync;		/* rev8 */
	u32 wroutofsync;		/* rev8 */
	u32 ग_लिखोbusy;			/* rev8 */
	u32 पढ़ोरुको;			/* rev8 */
	u32 पढ़ोterm;			/* rev8 */
	u32 ग_लिखोterm;			/* rev8 */
	u32 PAD[40];
	u32 घड़ीctlstatus;		/* rev8 */
	u32 PAD[7];

	u32 PAD[128];			/* DMA engines */

	/* SDIO/PCMCIA CIS region */
	अक्षर cis[512];			/* 0x400-0x5ff, rev6 */

	/* PCMCIA function control रेजिस्टरs */
	अक्षर pcmciafcr[256];		/* 0x600-6ff, rev6 */
	u16 PAD[55];

	/* PCMCIA backplane access */
	u16 backplanecsr;		/* 0x76E, rev6 */
	u16 backplaneaddr0;		/* rev6 */
	u16 backplaneaddr1;		/* rev6 */
	u16 backplaneaddr2;		/* rev6 */
	u16 backplaneaddr3;		/* rev6 */
	u16 backplanedata0;		/* rev6 */
	u16 backplanedata1;		/* rev6 */
	u16 backplanedata2;		/* rev6 */
	u16 backplanedata3;		/* rev6 */
	u16 PAD[31];

	/* sprom "size" & "blank" info */
	u16 spromstatus;		/* 0x7BE, rev2 */
	u32 PAD[464];

	u16 PAD[0x80];
पूर्ण;

/* Register/deरेजिस्टर पूर्णांकerrupt handler. */
पूर्णांक brcmf_sdiod_पूर्णांकr_रेजिस्टर(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdiod_पूर्णांकr_unरेजिस्टर(काष्ठा brcmf_sdio_dev *sdiodev);

/* SDIO device रेजिस्टर access पूर्णांकerface */
/* Accessors क्रम SDIO Function 0 */
#घोषणा brcmf_sdiod_func0_rb(sdiodev, addr, r) \
	sdio_f0_पढ़ोb((sdiodev)->func1, (addr), (r))

#घोषणा brcmf_sdiod_func0_wb(sdiodev, addr, v, ret) \
	sdio_f0_ग_लिखोb((sdiodev)->func1, (v), (addr), (ret))

/* Accessors क्रम SDIO Function 1 */
#घोषणा brcmf_sdiod_पढ़ोb(sdiodev, addr, r) \
	sdio_पढ़ोb((sdiodev)->func1, (addr), (r))

#घोषणा brcmf_sdiod_ग_लिखोb(sdiodev, addr, v, ret) \
	sdio_ग_लिखोb((sdiodev)->func1, (v), (addr), (ret))

u32 brcmf_sdiod_पढ़ोl(काष्ठा brcmf_sdio_dev *sdiodev, u32 addr, पूर्णांक *ret);
व्योम brcmf_sdiod_ग_लिखोl(काष्ठा brcmf_sdio_dev *sdiodev, u32 addr, u32 data,
			पूर्णांक *ret);

/* Buffer transfer to/from device (client) core via cmd53.
 *   fn:       function number
 *   flags:    backplane width, address increment, sync/async
 *   buf:      poपूर्णांकer to memory data buffer
 *   nbytes:   number of bytes to transfer to/from buf
 *   pkt:      poपूर्णांकer to packet associated with buf (अगर any)
 *   complete: callback function क्रम command completion (async only)
 *   handle:   handle क्रम completion callback (first arg in callback)
 * Returns 0 or error code.
 * NOTE: Async operation is not currently supported.
 */
पूर्णांक brcmf_sdiod_send_pkt(काष्ठा brcmf_sdio_dev *sdiodev,
			 काष्ठा sk_buff_head *pktq);
पूर्णांक brcmf_sdiod_send_buf(काष्ठा brcmf_sdio_dev *sdiodev, u8 *buf, uपूर्णांक nbytes);

पूर्णांक brcmf_sdiod_recv_pkt(काष्ठा brcmf_sdio_dev *sdiodev, काष्ठा sk_buff *pkt);
पूर्णांक brcmf_sdiod_recv_buf(काष्ठा brcmf_sdio_dev *sdiodev, u8 *buf, uपूर्णांक nbytes);
पूर्णांक brcmf_sdiod_recv_chain(काष्ठा brcmf_sdio_dev *sdiodev,
			   काष्ठा sk_buff_head *pktq, uपूर्णांक totlen);

/* Flags bits */

/* Four-byte target (backplane) width (vs. two-byte) */
#घोषणा SDIO_REQ_4BYTE	0x1
/* Fixed address (FIFO) (vs. incrementing address) */
#घोषणा SDIO_REQ_FIXED	0x2

/* Read/ग_लिखो to memory block (F1, no FIFO) via CMD53 (sync only).
 *   rw:       पढ़ो or ग_लिखो (0/1)
 *   addr:     direct SDIO address
 *   buf:      poपूर्णांकer to memory data buffer
 *   nbytes:   number of bytes to transfer to/from buf
 * Returns 0 or error code.
 */
पूर्णांक brcmf_sdiod_ramrw(काष्ठा brcmf_sdio_dev *sdiodev, bool ग_लिखो, u32 address,
		      u8 *data, uपूर्णांक size);

/* Issue an पात to the specअगरied function */
पूर्णांक brcmf_sdiod_पात(काष्ठा brcmf_sdio_dev *sdiodev, काष्ठा sdio_func *func);

व्योम brcmf_sdiod_sgtable_alloc(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdiod_change_state(काष्ठा brcmf_sdio_dev *sdiodev,
			      क्रमागत brcmf_sdiod_state state);
#अगर_घोषित CONFIG_PM_SLEEP
bool brcmf_sdiod_मुक्तzing(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdiod_try_मुक्तze(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdiod_मुक्तzer_count(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdiod_मुक्तzer_uncount(काष्ठा brcmf_sdio_dev *sdiodev);
#अन्यथा
अटल अंतरभूत bool brcmf_sdiod_मुक्तzing(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम brcmf_sdiod_try_मुक्तze(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
पूर्ण
अटल अंतरभूत व्योम brcmf_sdiod_मुक्तzer_count(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
पूर्ण
अटल अंतरभूत व्योम brcmf_sdiod_मुक्तzer_uncount(काष्ठा brcmf_sdio_dev *sdiodev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

पूर्णांक brcmf_sdiod_probe(काष्ठा brcmf_sdio_dev *sdiodev);
पूर्णांक brcmf_sdiod_हटाओ(काष्ठा brcmf_sdio_dev *sdiodev);

काष्ठा brcmf_sdio *brcmf_sdio_probe(काष्ठा brcmf_sdio_dev *sdiodev);
व्योम brcmf_sdio_हटाओ(काष्ठा brcmf_sdio *bus);
व्योम brcmf_sdio_isr(काष्ठा brcmf_sdio *bus, bool in_isr);

व्योम brcmf_sdio_wd_समयr(काष्ठा brcmf_sdio *bus, bool active);
व्योम brcmf_sdio_wowl_config(काष्ठा device *dev, bool enabled);
पूर्णांक brcmf_sdio_sleep(काष्ठा brcmf_sdio *bus, bool sleep);
व्योम brcmf_sdio_trigger_dpc(काष्ठा brcmf_sdio *bus);

#पूर्ण_अगर /* BRCMFMAC_SDIO_H */
