<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MAX3421 Host Controller driver क्रम USB.
 *
 * Author: David Mosberger-Tang <davidm@egauge.net>
 *
 * (C) Copyright 2014 David Mosberger-Tang <davidm@egauge.net>
 *
 * MAX3421 is a chip implementing a USB 2.0 Full-/Low-Speed host
 * controller on a SPI bus.
 *
 * Based on:
 *	o MAX3421E datasheet
 *		https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX3421E.pdf
 *	o MAX3421E Programming Guide
 *		https://www.hdl.co.jp/ftpdata/utl-001/AN3785.pdf
 *	o gadget/dummy_hcd.c
 *		For USB HCD implementation.
 *	o Arduino MAX3421 driver
 *	     https://github.com/felis/USB_Host_Shield_2.0/blob/master/Usb.cpp
 *
 * This file is licenced under the GPL v2.
 *
 * Important note on worst-हाल (full-speed) packet size स्थिरraपूर्णांकs
 * (See USB 2.0 Section 5.6.3 and following):
 *
 *	- control:	  64 bytes
 *	- isochronous:	1023 bytes
 *	- पूर्णांकerrupt:	  64 bytes
 *	- bulk:		  64 bytes
 *
 * Since the MAX3421 FIFO size is 64 bytes, we करो not have to work about
 * multi-FIFO ग_लिखोs/पढ़ोs क्रम a single USB packet *except* क्रम isochronous
 * transfers.  We करोn't support isochronous transfers at this समय, so we
 * just assume that a USB packet always fits पूर्णांकo a single FIFO buffer.
 *
 * NOTE: The June 2006 version of "MAX3421E Programming Guide"
 * (AN3785) has conflicting info क्रम the RCVDAVIRQ bit:
 *
 *	The description of RCVDAVIRQ says "The CPU *must* clear
 *	this IRQ bit (by writing a 1 to it) beक्रमe पढ़ोing the
 *	RCVFIFO data.
 *
 * However, the earlier section on "Programming BULK-IN
 * Transfers" says * that:
 *
 *	After the CPU retrieves the data, it clears the
 *	RCVDAVIRQ bit.
 *
 * The December 2006 version has been corrected and it consistently
 * states the second behavior is the correct one.
 *
 * Synchronous SPI transactions sleep so we can't perक्रमm any such
 * transactions जबतक holding a spin-lock (and/or जबतक पूर्णांकerrupts are
 * masked).  To achieve this, all SPI transactions are issued from a
 * single thपढ़ो (max3421_spi_thपढ़ो).
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/of.h>

#समावेश <linux/platक्रमm_data/max3421-hcd.h>

#घोषणा DRIVER_DESC	"MAX3421 USB Host-Controller Driver"
#घोषणा DRIVER_VERSION	"1.0"

/* 11-bit counter that wraps around (USB 2.0 Section 8.3.3): */
#घोषणा USB_MAX_FRAME_NUMBER	0x7ff
#घोषणा USB_MAX_RETRIES		3 /* # of retries beक्रमe error is reported */

/*
 * Max. # of बार we're willing to retransmit a request immediately in
 * resposne to a NAK.  Afterwards, we fall back on trying once a frame.
 */
#घोषणा NAK_MAX_FAST_RETRANSMITS	2

#घोषणा POWER_BUDGET	500	/* in mA; use 8 क्रम low-घातer port testing */

/* Port-change mask: */
#घोषणा PORT_C_MASK	((USB_PORT_STAT_C_CONNECTION |	\
			  USB_PORT_STAT_C_ENABLE |	\
			  USB_PORT_STAT_C_SUSPEND |	\
			  USB_PORT_STAT_C_OVERCURRENT | \
			  USB_PORT_STAT_C_RESET) << 16)

#घोषणा MAX3421_GPOUT_COUNT	8

क्रमागत max3421_rh_state अणु
	MAX3421_RH_RESET,
	MAX3421_RH_SUSPENDED,
	MAX3421_RH_RUNNING
पूर्ण;

क्रमागत pkt_state अणु
	PKT_STATE_SETUP,	/* रुकोing to send setup packet to ctrl pipe */
	PKT_STATE_TRANSFER,	/* रुकोing to xfer transfer_buffer */
	PKT_STATE_TERMINATE	/* रुकोing to terminate control transfer */
पूर्ण;

क्रमागत scheduling_pass अणु
	SCHED_PASS_PERIODIC,
	SCHED_PASS_NON_PERIODIC,
	SCHED_PASS_DONE
पूर्ण;

/* Bit numbers क्रम max3421_hcd->toकरो: */
क्रमागत अणु
	ENABLE_IRQ = 0,
	RESET_HCD,
	RESET_PORT,
	CHECK_UNLINK,
	IOPIN_UPDATE
पूर्ण;

काष्ठा max3421_dma_buf अणु
	u8 data[2];
पूर्ण;

काष्ठा max3421_hcd अणु
	spinlock_t lock;

	काष्ठा task_काष्ठा *spi_thपढ़ो;

	काष्ठा max3421_hcd *next;

	क्रमागत max3421_rh_state rh_state;
	/* lower 16 bits contain port status, upper 16 bits the change mask: */
	u32 port_status;

	अचिन्हित active:1;

	काष्ठा list_head ep_list;	/* list of EP's with work */

	/*
	 * The following are owned by spi_thपढ़ो (may be accessed by
	 * SPI-thपढ़ो without acquiring the HCD lock:
	 */
	u8 rev;				/* chip revision */
	u16 frame_number;
	/*
	 * kदो_स्मृति'd buffers guaranteed to be in separate (DMA)
	 * cache-lines:
	 */
	काष्ठा max3421_dma_buf *tx;
	काष्ठा max3421_dma_buf *rx;
	/*
	 * URB we're currently processing.  Must not be reset to शून्य
	 * unless MAX3421E chip is idle:
	 */
	काष्ठा urb *curr_urb;
	क्रमागत scheduling_pass sched_pass;
	काष्ठा usb_device *loaded_dev;	/* dev that's loaded पूर्णांकo the chip */
	पूर्णांक loaded_epnum;		/* epnum whose toggles are loaded */
	पूर्णांक urb_करोne;			/* > 0 -> no errors, < 0: त्रुटि_सं */
	माप_प्रकार curr_len;
	u8 hien;
	u8 mode;
	u8 iopins[2];
	अचिन्हित दीर्घ toकरो;
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ err_stat[16];
#पूर्ण_अगर
पूर्ण;

काष्ठा max3421_ep अणु
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा list_head ep_list;
	u32 naks;
	u16 last_active;		/* frame # this ep was last active */
	क्रमागत pkt_state pkt_state;
	u8 retries;
	u8 retransmit;			/* packet needs retransmission */
पूर्ण;

अटल काष्ठा max3421_hcd *max3421_hcd_list;

#घोषणा MAX3421_FIFO_SIZE	64

#घोषणा MAX3421_SPI_सूची_RD	0	/* पढ़ो रेजिस्टर from MAX3421 */
#घोषणा MAX3421_SPI_सूची_WR	1	/* ग_लिखो रेजिस्टर to MAX3421 */

/* SPI commands: */
#घोषणा MAX3421_SPI_सूची_SHIFT	1
#घोषणा MAX3421_SPI_REG_SHIFT	3

#घोषणा MAX3421_REG_RCVFIFO	1
#घोषणा MAX3421_REG_SNDFIFO	2
#घोषणा MAX3421_REG_SUDFIFO	4
#घोषणा MAX3421_REG_RCVBC	6
#घोषणा MAX3421_REG_SNDBC	7
#घोषणा MAX3421_REG_USBIRQ	13
#घोषणा MAX3421_REG_USBIEN	14
#घोषणा MAX3421_REG_USBCTL	15
#घोषणा MAX3421_REG_CPUCTL	16
#घोषणा MAX3421_REG_PINCTL	17
#घोषणा MAX3421_REG_REVISION	18
#घोषणा MAX3421_REG_IOPINS1	20
#घोषणा MAX3421_REG_IOPINS2	21
#घोषणा MAX3421_REG_GPINIRQ	22
#घोषणा MAX3421_REG_GPINIEN	23
#घोषणा MAX3421_REG_GPINPOL	24
#घोषणा MAX3421_REG_HIRQ	25
#घोषणा MAX3421_REG_HIEN	26
#घोषणा MAX3421_REG_MODE	27
#घोषणा MAX3421_REG_PERADDR	28
#घोषणा MAX3421_REG_HCTL	29
#घोषणा MAX3421_REG_HXFR	30
#घोषणा MAX3421_REG_HRSL	31

क्रमागत अणु
	MAX3421_USBIRQ_OSCOKIRQ_BIT = 0,
	MAX3421_USBIRQ_NOVBUSIRQ_BIT = 5,
	MAX3421_USBIRQ_VBUSIRQ_BIT
पूर्ण;

क्रमागत अणु
	MAX3421_CPUCTL_IE_BIT = 0,
	MAX3421_CPUCTL_PULSEWID0_BIT = 6,
	MAX3421_CPUCTL_PULSEWID1_BIT
पूर्ण;

क्रमागत अणु
	MAX3421_USBCTL_PWRDOWN_BIT = 4,
	MAX3421_USBCTL_CHIPRES_BIT
पूर्ण;

क्रमागत अणु
	MAX3421_PINCTL_GPXA_BIT	= 0,
	MAX3421_PINCTL_GPXB_BIT,
	MAX3421_PINCTL_POSINT_BIT,
	MAX3421_PINCTL_INTLEVEL_BIT,
	MAX3421_PINCTL_FDUPSPI_BIT,
	MAX3421_PINCTL_EP0INAK_BIT,
	MAX3421_PINCTL_EP2INAK_BIT,
	MAX3421_PINCTL_EP3INAK_BIT,
पूर्ण;

क्रमागत अणु
	MAX3421_HI_BUSEVENT_BIT = 0,	/* bus-reset/-resume */
	MAX3421_HI_RWU_BIT,		/* remote wakeup */
	MAX3421_HI_RCVDAV_BIT,		/* receive FIFO data available */
	MAX3421_HI_SNDBAV_BIT,		/* send buffer available */
	MAX3421_HI_SUSDN_BIT,		/* suspend operation करोne */
	MAX3421_HI_CONDET_BIT,		/* peripheral connect/disconnect */
	MAX3421_HI_FRAME_BIT,		/* frame generator */
	MAX3421_HI_HXFRDN_BIT,		/* host transfer करोne */
पूर्ण;

क्रमागत अणु
	MAX3421_HCTL_BUSRST_BIT = 0,
	MAX3421_HCTL_FRMRST_BIT,
	MAX3421_HCTL_SAMPLEBUS_BIT,
	MAX3421_HCTL_SIGRSM_BIT,
	MAX3421_HCTL_RCVTOG0_BIT,
	MAX3421_HCTL_RCVTOG1_BIT,
	MAX3421_HCTL_SNDTOG0_BIT,
	MAX3421_HCTL_SNDTOG1_BIT
पूर्ण;

क्रमागत अणु
	MAX3421_MODE_HOST_BIT = 0,
	MAX3421_MODE_LOWSPEED_BIT,
	MAX3421_MODE_HUBPRE_BIT,
	MAX3421_MODE_SOFKAENAB_BIT,
	MAX3421_MODE_SEPIRQ_BIT,
	MAX3421_MODE_DELAYISO_BIT,
	MAX3421_MODE_DMPULLDN_BIT,
	MAX3421_MODE_DPPULLDN_BIT
पूर्ण;

क्रमागत अणु
	MAX3421_HRSL_OK = 0,
	MAX3421_HRSL_BUSY,
	MAX3421_HRSL_BADREQ,
	MAX3421_HRSL_UNDEF,
	MAX3421_HRSL_NAK,
	MAX3421_HRSL_STALL,
	MAX3421_HRSL_TOGERR,
	MAX3421_HRSL_WRONGPID,
	MAX3421_HRSL_BADBC,
	MAX3421_HRSL_PIDERR,
	MAX3421_HRSL_PKTERR,
	MAX3421_HRSL_CRCERR,
	MAX3421_HRSL_KERR,
	MAX3421_HRSL_JERR,
	MAX3421_HRSL_TIMEOUT,
	MAX3421_HRSL_BABBLE,
	MAX3421_HRSL_RESULT_MASK = 0xf,
	MAX3421_HRSL_RCVTOGRD_BIT = 4,
	MAX3421_HRSL_SNDTOGRD_BIT,
	MAX3421_HRSL_KSTATUS_BIT,
	MAX3421_HRSL_JSTATUS_BIT
पूर्ण;

/* Return same error-codes as ohci.h:cc_to_error: */
अटल स्थिर पूर्णांक hrsl_to_error[] = अणु
	[MAX3421_HRSL_OK] =		0,
	[MAX3421_HRSL_BUSY] =		-EINVAL,
	[MAX3421_HRSL_BADREQ] =		-EINVAL,
	[MAX3421_HRSL_UNDEF] =		-EINVAL,
	[MAX3421_HRSL_NAK] =		-EAGAIN,
	[MAX3421_HRSL_STALL] =		-EPIPE,
	[MAX3421_HRSL_TOGERR] =		-EILSEQ,
	[MAX3421_HRSL_WRONGPID] =	-EPROTO,
	[MAX3421_HRSL_BADBC] =		-EREMOTEIO,
	[MAX3421_HRSL_PIDERR] =		-EPROTO,
	[MAX3421_HRSL_PKTERR] =		-EPROTO,
	[MAX3421_HRSL_CRCERR] =		-EILSEQ,
	[MAX3421_HRSL_KERR] =		-EIO,
	[MAX3421_HRSL_JERR] =		-EIO,
	[MAX3421_HRSL_TIMEOUT] =	-ETIME,
	[MAX3421_HRSL_BABBLE] =		-EOVERFLOW
पूर्ण;

/*
 * See https://www.beyondlogic.org/usbnutshell/usb4.shपंचांगl#Control क्रम a
 * reasonable overview of how control transfers use the the IN/OUT
 * tokens.
 */
#घोषणा MAX3421_HXFR_BULK_IN(ep)	(0x00 | (ep))	/* bulk or पूर्णांकerrupt */
#घोषणा MAX3421_HXFR_SETUP		 0x10
#घोषणा MAX3421_HXFR_BULK_OUT(ep)	(0x20 | (ep))	/* bulk or पूर्णांकerrupt */
#घोषणा MAX3421_HXFR_ISO_IN(ep)		(0x40 | (ep))
#घोषणा MAX3421_HXFR_ISO_OUT(ep)	(0x60 | (ep))
#घोषणा MAX3421_HXFR_HS_IN		 0x80		/* handshake in */
#घोषणा MAX3421_HXFR_HS_OUT		 0xa0		/* handshake out */

#घोषणा field(val, bit)	((val) << (bit))

अटल अंतरभूत s16
frame_dअगरf(u16 left, u16 right)
अणु
	वापस ((अचिन्हित) (left - right)) % (USB_MAX_FRAME_NUMBER + 1);
पूर्ण

अटल अंतरभूत काष्ठा max3421_hcd *
hcd_to_max3421(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा max3421_hcd *) hcd->hcd_priv;
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *
max3421_to_hcd(काष्ठा max3421_hcd *max3421_hcd)
अणु
	वापस container_of((व्योम *) max3421_hcd, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल u8
spi_rd8(काष्ठा usb_hcd *hcd, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(field(reg, MAX3421_SPI_REG_SHIFT) |
		 field(MAX3421_SPI_सूची_RD, MAX3421_SPI_सूची_SHIFT));

	transfer.tx_buf = max3421_hcd->tx->data;
	transfer.rx_buf = max3421_hcd->rx->data;
	transfer.len = 2;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);

	वापस max3421_hcd->rx->data[1];
पूर्ण

अटल व्योम
spi_wr8(काष्ठा usb_hcd *hcd, अचिन्हित पूर्णांक reg, u8 val)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा spi_transfer transfer;
	काष्ठा spi_message msg;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(field(reg, MAX3421_SPI_REG_SHIFT) |
		 field(MAX3421_SPI_सूची_WR, MAX3421_SPI_सूची_SHIFT));
	max3421_hcd->tx->data[1] = val;

	transfer.tx_buf = max3421_hcd->tx->data;
	transfer.len = 2;

	spi_message_add_tail(&transfer, &msg);
	spi_sync(spi, &msg);
पूर्ण

अटल व्योम
spi_rd_buf(काष्ठा usb_hcd *hcd, अचिन्हित पूर्णांक reg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message msg;

	स_रखो(transfer, 0, माप(transfer));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(field(reg, MAX3421_SPI_REG_SHIFT) |
		 field(MAX3421_SPI_सूची_RD, MAX3421_SPI_सूची_SHIFT));
	transfer[0].tx_buf = max3421_hcd->tx->data;
	transfer[0].len = 1;

	transfer[1].rx_buf = buf;
	transfer[1].len = len;

	spi_message_add_tail(&transfer[0], &msg);
	spi_message_add_tail(&transfer[1], &msg);
	spi_sync(spi, &msg);
पूर्ण

अटल व्योम
spi_wr_buf(काष्ठा usb_hcd *hcd, अचिन्हित पूर्णांक reg, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message msg;

	स_रखो(transfer, 0, माप(transfer));

	spi_message_init(&msg);

	max3421_hcd->tx->data[0] =
		(field(reg, MAX3421_SPI_REG_SHIFT) |
		 field(MAX3421_SPI_सूची_WR, MAX3421_SPI_सूची_SHIFT));

	transfer[0].tx_buf = max3421_hcd->tx->data;
	transfer[0].len = 1;

	transfer[1].tx_buf = buf;
	transfer[1].len = len;

	spi_message_add_tail(&transfer[0], &msg);
	spi_message_add_tail(&transfer[1], &msg);
	spi_sync(spi, &msg);
पूर्ण

/*
 * Figure out the correct setting क्रम the LOWSPEED and HUBPRE mode
 * bits.  The HUBPRE bit needs to be set when MAX3421E operates at
 * full speed, but it's talking to a low-speed device (i.e., through a
 * hub).  Setting that bit ensures that every low-speed packet is
 * preceded by a full-speed PRE PID.  Possible configurations:
 *
 * Hub speed:	Device speed:	=>	LOWSPEED bit:	HUBPRE bit:
 *	FULL	FULL		=>	0		0
 *	FULL	LOW		=>	1		1
 *	LOW	LOW		=>	1		0
 *	LOW	FULL		=>	1		0
 */
अटल व्योम
max3421_set_speed(काष्ठा usb_hcd *hcd, काष्ठा usb_device *dev)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mode_lowspeed, mode_hubpre, mode = max3421_hcd->mode;

	mode_lowspeed = BIT(MAX3421_MODE_LOWSPEED_BIT);
	mode_hubpre   = BIT(MAX3421_MODE_HUBPRE_BIT);
	अगर (max3421_hcd->port_status & USB_PORT_STAT_LOW_SPEED) अणु
		mode |=  mode_lowspeed;
		mode &= ~mode_hubpre;
	पूर्ण अन्यथा अगर (dev->speed == USB_SPEED_LOW) अणु
		mode |= mode_lowspeed | mode_hubpre;
	पूर्ण अन्यथा अणु
		mode &= ~(mode_lowspeed | mode_hubpre);
	पूर्ण
	अगर (mode != max3421_hcd->mode) अणु
		max3421_hcd->mode = mode;
		spi_wr8(hcd, MAX3421_REG_MODE, max3421_hcd->mode);
	पूर्ण

पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_set_address(काष्ठा usb_hcd *hcd, काष्ठा usb_device *dev, पूर्णांक epnum,
		    पूर्णांक क्रमce_toggles)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	पूर्णांक old_epnum, same_ep, rcvtog, sndtog;
	काष्ठा usb_device *old_dev;
	u8 hctl;

	old_dev = max3421_hcd->loaded_dev;
	old_epnum = max3421_hcd->loaded_epnum;

	same_ep = (dev == old_dev && epnum == old_epnum);
	अगर (same_ep && !क्रमce_toggles)
		वापस;

	अगर (old_dev && !same_ep) अणु
		/* save the old end-poपूर्णांकs toggles: */
		u8 hrsl = spi_rd8(hcd, MAX3421_REG_HRSL);

		rcvtog = (hrsl >> MAX3421_HRSL_RCVTOGRD_BIT) & 1;
		sndtog = (hrsl >> MAX3421_HRSL_SNDTOGRD_BIT) & 1;

		/* no locking: HCD (i.e., we) own toggles, करोn't we? */
		usb_settoggle(old_dev, old_epnum, 0, rcvtog);
		usb_settoggle(old_dev, old_epnum, 1, sndtog);
	पूर्ण
	/* setup new endpoपूर्णांक's toggle bits: */
	rcvtog = usb_gettoggle(dev, epnum, 0);
	sndtog = usb_gettoggle(dev, epnum, 1);
	hctl = (BIT(rcvtog + MAX3421_HCTL_RCVTOG0_BIT) |
		BIT(sndtog + MAX3421_HCTL_SNDTOG0_BIT));

	max3421_hcd->loaded_epnum = epnum;
	spi_wr8(hcd, MAX3421_REG_HCTL, hctl);

	/*
	 * Note: devnum क्रम one and the same device can change during
	 * address-assignment so it's best to just always load the
	 * address whenever the end-poपूर्णांक changed/was क्रमced.
	 */
	max3421_hcd->loaded_dev = dev;
	spi_wr8(hcd, MAX3421_REG_PERADDR, dev->devnum);
पूर्ण

अटल पूर्णांक
max3421_ctrl_setup(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	spi_wr_buf(hcd, MAX3421_REG_SUDFIFO, urb->setup_packet, 8);
	वापस MAX3421_HXFR_SETUP;
पूर्ण

अटल पूर्णांक
max3421_transfer_in(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	पूर्णांक epnum = usb_pipeendpoपूर्णांक(urb->pipe);

	max3421_hcd->curr_len = 0;
	max3421_hcd->hien |= BIT(MAX3421_HI_RCVDAV_BIT);
	वापस MAX3421_HXFR_BULK_IN(epnum);
पूर्ण

अटल पूर्णांक
max3421_transfer_out(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक fast_retransmit)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	पूर्णांक epnum = usb_pipeendpoपूर्णांक(urb->pipe);
	u32 max_packet;
	व्योम *src;

	src = urb->transfer_buffer + urb->actual_length;

	अगर (fast_retransmit) अणु
		अगर (max3421_hcd->rev == 0x12) अणु
			/* work around rev 0x12 bug: */
			spi_wr8(hcd, MAX3421_REG_SNDBC, 0);
			spi_wr8(hcd, MAX3421_REG_SNDFIFO, ((u8 *) src)[0]);
			spi_wr8(hcd, MAX3421_REG_SNDBC, max3421_hcd->curr_len);
		पूर्ण
		वापस MAX3421_HXFR_BULK_OUT(epnum);
	पूर्ण

	max_packet = usb_maxpacket(urb->dev, urb->pipe, 1);

	अगर (max_packet > MAX3421_FIFO_SIZE) अणु
		/*
		 * We करो not support isochronous transfers at this
		 * समय.
		 */
		dev_err(&spi->dev,
			"%s: packet-size of %u too big (limit is %u bytes)",
			__func__, max_packet, MAX3421_FIFO_SIZE);
		max3421_hcd->urb_करोne = -EMSGSIZE;
		वापस -EMSGSIZE;
	पूर्ण
	max3421_hcd->curr_len = min((urb->transfer_buffer_length -
				     urb->actual_length), max_packet);

	spi_wr_buf(hcd, MAX3421_REG_SNDFIFO, src, max3421_hcd->curr_len);
	spi_wr8(hcd, MAX3421_REG_SNDBC, max3421_hcd->curr_len);
	वापस MAX3421_HXFR_BULK_OUT(epnum);
पूर्ण

/*
 * Issue the next host-transfer command.
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_next_transfer(काष्ठा usb_hcd *hcd, पूर्णांक fast_retransmit)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा urb *urb = max3421_hcd->curr_urb;
	काष्ठा max3421_ep *max3421_ep;
	पूर्णांक cmd = -EINVAL;

	अगर (!urb)
		वापस;	/* nothing to करो */

	max3421_ep = urb->ep->hcpriv;

	चयन (max3421_ep->pkt_state) अणु
	हाल PKT_STATE_SETUP:
		cmd = max3421_ctrl_setup(hcd, urb);
		अवरोध;

	हाल PKT_STATE_TRANSFER:
		अगर (usb_urb_dir_in(urb))
			cmd = max3421_transfer_in(hcd, urb);
		अन्यथा
			cmd = max3421_transfer_out(hcd, urb, fast_retransmit);
		अवरोध;

	हाल PKT_STATE_TERMINATE:
		/*
		 * IN transfers are terminated with HS_OUT token,
		 * OUT transfers with HS_IN:
		 */
		अगर (usb_urb_dir_in(urb))
			cmd = MAX3421_HXFR_HS_OUT;
		अन्यथा
			cmd = MAX3421_HXFR_HS_IN;
		अवरोध;
	पूर्ण

	अगर (cmd < 0)
		वापस;

	/* issue the command and रुको क्रम host-xfer-करोne पूर्णांकerrupt: */

	spi_wr8(hcd, MAX3421_REG_HXFR, cmd);
	max3421_hcd->hien |= BIT(MAX3421_HI_HXFRDN_BIT);
पूर्ण

/*
 * Find the next URB to process and start its execution.
 *
 * At this समय, we करो not anticipate ever connecting a USB hub to the
 * MAX3421 chip, so at most USB device can be connected and we can use
 * a simplistic scheduler: at the start of a frame, schedule all
 * periodic transfers.  Once that is करोne, use the reमुख्यder of the
 * frame to process non-periodic (bulk & control) transfers.
 *
 * Preconditions:
 * o Caller must NOT hold HCD spinlock.
 * o max3421_hcd->curr_urb MUST BE शून्य.
 * o MAX3421E chip must be idle.
 */
अटल पूर्णांक
max3421_select_and_start_urb(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा urb *urb, *curr_urb = शून्य;
	काष्ठा max3421_ep *max3421_ep;
	पूर्णांक epnum, क्रमce_toggles = 0;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा list_head *pos;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	क्रम (;
	     max3421_hcd->sched_pass < SCHED_PASS_DONE;
	     ++max3421_hcd->sched_pass)
		list_क्रम_each(pos, &max3421_hcd->ep_list) अणु
			urb = शून्य;
			max3421_ep = container_of(pos, काष्ठा max3421_ep,
						  ep_list);
			ep = max3421_ep->ep;

			चयन (usb_endpoपूर्णांक_type(&ep->desc)) अणु
			हाल USB_ENDPOINT_XFER_ISOC:
			हाल USB_ENDPOINT_XFER_INT:
				अगर (max3421_hcd->sched_pass !=
				    SCHED_PASS_PERIODIC)
					जारी;
				अवरोध;

			हाल USB_ENDPOINT_XFER_CONTROL:
			हाल USB_ENDPOINT_XFER_BULK:
				अगर (max3421_hcd->sched_pass !=
				    SCHED_PASS_NON_PERIODIC)
					जारी;
				अवरोध;
			पूर्ण

			अगर (list_empty(&ep->urb_list))
				जारी;	/* nothing to करो */
			urb = list_first_entry(&ep->urb_list, काष्ठा urb,
					       urb_list);
			अगर (urb->unlinked) अणु
				dev_dbg(&spi->dev, "%s: URB %p unlinked=%d",
					__func__, urb, urb->unlinked);
				max3421_hcd->curr_urb = urb;
				max3421_hcd->urb_करोne = 1;
				spin_unlock_irqrestore(&max3421_hcd->lock,
						       flags);
				वापस 1;
			पूर्ण

			चयन (usb_endpoपूर्णांक_type(&ep->desc)) अणु
			हाल USB_ENDPOINT_XFER_CONTROL:
				/*
				 * Allow one control transaction per
				 * frame per endpoपूर्णांक:
				 */
				अगर (frame_dअगरf(max3421_ep->last_active,
					       max3421_hcd->frame_number) == 0)
					जारी;
				अवरोध;

			हाल USB_ENDPOINT_XFER_BULK:
				अगर (max3421_ep->retransmit
				    && (frame_dअगरf(max3421_ep->last_active,
						   max3421_hcd->frame_number)
					== 0))
					/*
					 * We alपढ़ोy tried this EP
					 * during this frame and got a
					 * NAK or error; रुको क्रम next frame
					 */
					जारी;
				अवरोध;

			हाल USB_ENDPOINT_XFER_ISOC:
			हाल USB_ENDPOINT_XFER_INT:
				अगर (frame_dअगरf(max3421_hcd->frame_number,
					       max3421_ep->last_active)
				    < urb->पूर्णांकerval)
					/*
					 * We alपढ़ोy processed this
					 * end-poपूर्णांक in the current
					 * frame
					 */
					जारी;
				अवरोध;
			पूर्ण

			/* move current ep to tail: */
			list_move_tail(pos, &max3421_hcd->ep_list);
			curr_urb = urb;
			जाओ करोne;
		पूर्ण
करोne:
	अगर (!curr_urb) अणु
		spin_unlock_irqrestore(&max3421_hcd->lock, flags);
		वापस 0;
	पूर्ण

	urb = max3421_hcd->curr_urb = curr_urb;
	epnum = usb_endpoपूर्णांक_num(&urb->ep->desc);
	अगर (max3421_ep->retransmit)
		/* restart (part of) a USB transaction: */
		max3421_ep->retransmit = 0;
	अन्यथा अणु
		/* start USB transaction: */
		अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc)) अणु
			/*
			 * See USB 2.0 spec section 8.6.1
			 * Initialization via SETUP Token:
			 */
			usb_settoggle(urb->dev, epnum, 0, 1);
			usb_settoggle(urb->dev, epnum, 1, 1);
			max3421_ep->pkt_state = PKT_STATE_SETUP;
			क्रमce_toggles = 1;
		पूर्ण अन्यथा
			max3421_ep->pkt_state = PKT_STATE_TRANSFER;
	पूर्ण

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);

	max3421_ep->last_active = max3421_hcd->frame_number;
	max3421_set_address(hcd, urb->dev, epnum, क्रमce_toggles);
	max3421_set_speed(hcd, urb->dev);
	max3421_next_transfer(hcd, 0);
	वापस 1;
पूर्ण

/*
 * Check all endpoपूर्णांकs क्रम URBs that got unlinked.
 *
 * Caller must NOT hold HCD spinlock.
 */
अटल पूर्णांक
max3421_check_unlink(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा max3421_ep *max3421_ep;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा urb *urb, *next;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&max3421_hcd->lock, flags);
	list_क्रम_each_entry(max3421_ep, &max3421_hcd->ep_list, ep_list) अणु
		ep = max3421_ep->ep;
		list_क्रम_each_entry_safe(urb, next, &ep->urb_list, urb_list) अणु
			अगर (urb->unlinked) अणु
				retval = 1;
				dev_dbg(&spi->dev, "%s: URB %p unlinked=%d",
					__func__, urb, urb->unlinked);
				usb_hcd_unlink_urb_from_ep(hcd, urb);
				spin_unlock_irqrestore(&max3421_hcd->lock,
						       flags);
				usb_hcd_giveback_urb(hcd, urb, 0);
				spin_lock_irqsave(&max3421_hcd->lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	वापस retval;
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_slow_retransmit(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा urb *urb = max3421_hcd->curr_urb;
	काष्ठा max3421_ep *max3421_ep;

	max3421_ep = urb->ep->hcpriv;
	max3421_ep->retransmit = 1;
	max3421_hcd->curr_urb = शून्य;
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_recv_data_available(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा urb *urb = max3421_hcd->curr_urb;
	माप_प्रकार reमुख्यing, transfer_size;
	u8 rcvbc;

	rcvbc = spi_rd8(hcd, MAX3421_REG_RCVBC);

	अगर (rcvbc > MAX3421_FIFO_SIZE)
		rcvbc = MAX3421_FIFO_SIZE;
	अगर (urb->actual_length >= urb->transfer_buffer_length)
		reमुख्यing = 0;
	अन्यथा
		reमुख्यing = urb->transfer_buffer_length - urb->actual_length;
	transfer_size = rcvbc;
	अगर (transfer_size > reमुख्यing)
		transfer_size = reमुख्यing;
	अगर (transfer_size > 0) अणु
		व्योम *dst = urb->transfer_buffer + urb->actual_length;

		spi_rd_buf(hcd, MAX3421_REG_RCVFIFO, dst, transfer_size);
		urb->actual_length += transfer_size;
		max3421_hcd->curr_len = transfer_size;
	पूर्ण

	/* ack the RCVDAV irq now that the FIFO has been पढ़ो: */
	spi_wr8(hcd, MAX3421_REG_HIRQ, BIT(MAX3421_HI_RCVDAV_BIT));
पूर्ण

अटल व्योम
max3421_handle_error(काष्ठा usb_hcd *hcd, u8 hrsl)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 result_code = hrsl & MAX3421_HRSL_RESULT_MASK;
	काष्ठा urb *urb = max3421_hcd->curr_urb;
	काष्ठा max3421_ep *max3421_ep = urb->ep->hcpriv;
	पूर्णांक चयन_sndfअगरo;

	/*
	 * If an OUT command results in any response other than OK
	 * (i.e., error or NAK), we have to perक्रमm a dummy-ग_लिखो to
	 * SNDBC so the FIFO माला_लो चयनed back to us.  Otherwise, we
	 * get out of sync with the SNDFIFO द्विगुन buffer.
	 */
	चयन_sndfअगरo = (max3421_ep->pkt_state == PKT_STATE_TRANSFER &&
			  usb_urb_dir_out(urb));

	चयन (result_code) अणु
	हाल MAX3421_HRSL_OK:
		वापस;			/* this shouldn't happen */

	हाल MAX3421_HRSL_WRONGPID:	/* received wrong PID */
	हाल MAX3421_HRSL_BUSY:		/* SIE busy */
	हाल MAX3421_HRSL_BADREQ:	/* bad val in HXFR */
	हाल MAX3421_HRSL_UNDEF:	/* reserved */
	हाल MAX3421_HRSL_KERR:		/* K-state instead of response */
	हाल MAX3421_HRSL_JERR:		/* J-state instead of response */
		/*
		 * packet experienced an error that we cannot recover
		 * from; report error
		 */
		max3421_hcd->urb_करोne = hrsl_to_error[result_code];
		dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
			__func__, hrsl);
		अवरोध;

	हाल MAX3421_HRSL_TOGERR:
		अगर (usb_urb_dir_in(urb))
			; /* करोn't करो anything (device will चयन toggle) */
		अन्यथा अणु
			/* flip the send toggle bit: */
			पूर्णांक sndtog = (hrsl >> MAX3421_HRSL_SNDTOGRD_BIT) & 1;

			sndtog ^= 1;
			spi_wr8(hcd, MAX3421_REG_HCTL,
				BIT(sndtog + MAX3421_HCTL_SNDTOG0_BIT));
		पूर्ण
		fallthrough;
	हाल MAX3421_HRSL_BADBC:	/* bad byte count */
	हाल MAX3421_HRSL_PIDERR:	/* received PID is corrupted */
	हाल MAX3421_HRSL_PKTERR:	/* packet error (stuff, EOP) */
	हाल MAX3421_HRSL_CRCERR:	/* CRC error */
	हाल MAX3421_HRSL_BABBLE:	/* device talked too दीर्घ */
	हाल MAX3421_HRSL_TIMEOUT:
		अगर (max3421_ep->retries++ < USB_MAX_RETRIES)
			/* retry the packet again in the next frame */
			max3421_slow_retransmit(hcd);
		अन्यथा अणु
			/* Based on ohci.h cc_to_err[]: */
			max3421_hcd->urb_करोne = hrsl_to_error[result_code];
			dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
				__func__, hrsl);
		पूर्ण
		अवरोध;

	हाल MAX3421_HRSL_STALL:
		dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
			__func__, hrsl);
		max3421_hcd->urb_करोne = hrsl_to_error[result_code];
		अवरोध;

	हाल MAX3421_HRSL_NAK:
		/*
		 * Device wasn't पढ़ोy क्रम data or has no data
		 * available: retry the packet again.
		 */
		अगर (max3421_ep->naks++ < NAK_MAX_FAST_RETRANSMITS) अणु
			max3421_next_transfer(hcd, 1);
			चयन_sndfअगरo = 0;
		पूर्ण अन्यथा
			max3421_slow_retransmit(hcd);
		अवरोध;
	पूर्ण
	अगर (चयन_sndfअगरo)
		spi_wr8(hcd, MAX3421_REG_SNDBC, 0);
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल पूर्णांक
max3421_transfer_in_करोne(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u32 max_packet;

	अगर (urb->actual_length >= urb->transfer_buffer_length)
		वापस 1;	/* पढ़ो is complete, so we're करोne */

	/*
	 * USB 2.0 Section 5.3.2 Pipes: packets must be full size
	 * except क्रम last one.
	 */
	max_packet = usb_maxpacket(urb->dev, urb->pipe, 0);
	अगर (max_packet > MAX3421_FIFO_SIZE) अणु
		/*
		 * We करो not support isochronous transfers at this
		 * समय...
		 */
		dev_err(&spi->dev,
			"%s: packet-size of %u too big (limit is %u bytes)",
			__func__, max_packet, MAX3421_FIFO_SIZE);
		वापस -EINVAL;
	पूर्ण

	अगर (max3421_hcd->curr_len < max_packet) अणु
		अगर (urb->transfer_flags & URB_SHORT_NOT_OK) अणु
			/*
			 * reमुख्यing > 0 and received an
			 * unexpected partial packet ->
			 * error
			 */
			वापस -EREMOTEIO;
		पूर्ण अन्यथा
			/* लघु पढ़ो, but it's OK */
			वापस 1;
	पूर्ण
	वापस 0;	/* not करोne */
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल पूर्णांक
max3421_transfer_out_करोne(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	urb->actual_length += max3421_hcd->curr_len;
	अगर (urb->actual_length < urb->transfer_buffer_length)
		वापस 0;
	अगर (urb->transfer_flags & URB_ZERO_PACKET) अणु
		/*
		 * Some hardware needs a zero-size packet at the end
		 * of a bulk-out transfer अगर the last transfer was a
		 * full-sized packet (i.e., such hardware use <
		 * max_packet as an indicator that the end of the
		 * packet has been reached).
		 */
		u32 max_packet = usb_maxpacket(urb->dev, urb->pipe, 1);

		अगर (max3421_hcd->curr_len == max_packet)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_host_transfer_करोne(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा urb *urb = max3421_hcd->curr_urb;
	काष्ठा max3421_ep *max3421_ep;
	u8 result_code, hrsl;
	पूर्णांक urb_करोne = 0;

	max3421_hcd->hien &= ~(BIT(MAX3421_HI_HXFRDN_BIT) |
			       BIT(MAX3421_HI_RCVDAV_BIT));

	hrsl = spi_rd8(hcd, MAX3421_REG_HRSL);
	result_code = hrsl & MAX3421_HRSL_RESULT_MASK;

#अगर_घोषित DEBUG
	++max3421_hcd->err_stat[result_code];
#पूर्ण_अगर

	max3421_ep = urb->ep->hcpriv;

	अगर (unlikely(result_code != MAX3421_HRSL_OK)) अणु
		max3421_handle_error(hcd, hrsl);
		वापस;
	पूर्ण

	max3421_ep->naks = 0;
	max3421_ep->retries = 0;
	चयन (max3421_ep->pkt_state) अणु

	हाल PKT_STATE_SETUP:
		अगर (urb->transfer_buffer_length > 0)
			max3421_ep->pkt_state = PKT_STATE_TRANSFER;
		अन्यथा
			max3421_ep->pkt_state = PKT_STATE_TERMINATE;
		अवरोध;

	हाल PKT_STATE_TRANSFER:
		अगर (usb_urb_dir_in(urb))
			urb_करोne = max3421_transfer_in_करोne(hcd, urb);
		अन्यथा
			urb_करोne = max3421_transfer_out_करोne(hcd, urb);
		अगर (urb_करोne > 0 && usb_pipetype(urb->pipe) == PIPE_CONTROL) अणु
			/*
			 * We aren't really करोne - we still need to
			 * terminate the control transfer:
			 */
			max3421_hcd->urb_करोne = urb_करोne = 0;
			max3421_ep->pkt_state = PKT_STATE_TERMINATE;
		पूर्ण
		अवरोध;

	हाल PKT_STATE_TERMINATE:
		urb_करोne = 1;
		अवरोध;
	पूर्ण

	अगर (urb_करोne)
		max3421_hcd->urb_करोne = urb_करोne;
	अन्यथा
		max3421_next_transfer(hcd, 0);
पूर्ण

/*
 * Caller must NOT hold HCD spinlock.
 */
अटल व्योम
max3421_detect_conn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	अचिन्हित पूर्णांक jk, have_conn = 0;
	u32 old_port_status, chg;
	अचिन्हित दीर्घ flags;
	u8 hrsl, mode;

	hrsl = spi_rd8(hcd, MAX3421_REG_HRSL);

	jk = ((((hrsl >> MAX3421_HRSL_JSTATUS_BIT) & 1) << 0) |
	      (((hrsl >> MAX3421_HRSL_KSTATUS_BIT) & 1) << 1));

	mode = max3421_hcd->mode;

	चयन (jk) अणु
	हाल 0x0: /* SE0: disconnect */
		/*
		 * Turn off SOFKAENAB bit to aव्योम getting पूर्णांकerrupt
		 * every milli-second:
		 */
		mode &= ~BIT(MAX3421_MODE_SOFKAENAB_BIT);
		अवरोध;

	हाल 0x1: /* J=0,K=1: low-speed (in full-speed or vice versa) */
	हाल 0x2: /* J=1,K=0: full-speed (in full-speed or vice versa) */
		अगर (jk == 0x2)
			/* need to चयन to the other speed: */
			mode ^= BIT(MAX3421_MODE_LOWSPEED_BIT);
		/* turn on SOFKAENAB bit: */
		mode |= BIT(MAX3421_MODE_SOFKAENAB_BIT);
		have_conn = 1;
		अवरोध;

	हाल 0x3: /* illegal */
		अवरोध;
	पूर्ण

	max3421_hcd->mode = mode;
	spi_wr8(hcd, MAX3421_REG_MODE, max3421_hcd->mode);

	spin_lock_irqsave(&max3421_hcd->lock, flags);
	old_port_status = max3421_hcd->port_status;
	अगर (have_conn)
		max3421_hcd->port_status |=  USB_PORT_STAT_CONNECTION;
	अन्यथा
		max3421_hcd->port_status &= ~USB_PORT_STAT_CONNECTION;
	अगर (mode & BIT(MAX3421_MODE_LOWSPEED_BIT))
		max3421_hcd->port_status |=  USB_PORT_STAT_LOW_SPEED;
	अन्यथा
		max3421_hcd->port_status &= ~USB_PORT_STAT_LOW_SPEED;
	chg = (old_port_status ^ max3421_hcd->port_status);
	max3421_hcd->port_status |= chg << 16;
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
पूर्ण

अटल irqवापस_t
max3421_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usb_hcd *hcd = dev_id;
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	अगर (max3421_hcd->spi_thपढ़ो &&
	    max3421_hcd->spi_thपढ़ो->state != TASK_RUNNING)
		wake_up_process(max3421_hcd->spi_thपढ़ो);
	अगर (!test_and_set_bit(ENABLE_IRQ, &max3421_hcd->toकरो))
		disable_irq_nosync(spi->irq);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित DEBUG

अटल व्योम
dump_eps(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा max3421_ep *max3421_ep;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	अक्षर ubuf[512], *dp, *end;
	अचिन्हित दीर्घ flags;
	काष्ठा urb *urb;
	पूर्णांक epnum, ret;

	spin_lock_irqsave(&max3421_hcd->lock, flags);
	list_क्रम_each_entry(max3421_ep, &max3421_hcd->ep_list, ep_list) अणु
		ep = max3421_ep->ep;

		dp = ubuf;
		end = dp + माप(ubuf);
		*dp = '\0';
		list_क्रम_each_entry(urb, &ep->urb_list, urb_list) अणु
			ret = snम_लिखो(dp, end - dp, " %p(%d.%s %d/%d)", urb,
				       usb_pipetype(urb->pipe),
				       usb_urb_dir_in(urb) ? "IN" : "OUT",
				       urb->actual_length,
				       urb->transfer_buffer_length);
			अगर (ret < 0 || ret >= end - dp)
				अवरोध;	/* error or buffer full */
			dp += ret;
		पूर्ण

		epnum = usb_endpoपूर्णांक_num(&ep->desc);
		pr_info("EP%0u %u lst %04u rtr %u nak %6u rxmt %u: %s\n",
			epnum, max3421_ep->pkt_state, max3421_ep->last_active,
			max3421_ep->retries, max3421_ep->naks,
			max3421_ep->retransmit, ubuf);
	पूर्ण
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
पूर्ण

#पूर्ण_अगर /* DEBUG */

/* Return zero अगर no work was perक्रमmed, 1 otherwise.  */
अटल पूर्णांक
max3421_handle_irqs(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u32 chg, old_port_status;
	अचिन्हित दीर्घ flags;
	u8 hirq;

	/*
	 * Read and ack pending पूर्णांकerrupts (CPU must never
	 * clear SNDBAV directly and RCVDAV must be cleared by
	 * max3421_recv_data_available()!):
	 */
	hirq = spi_rd8(hcd, MAX3421_REG_HIRQ);
	hirq &= max3421_hcd->hien;
	अगर (!hirq)
		वापस 0;

	spi_wr8(hcd, MAX3421_REG_HIRQ,
		hirq & ~(BIT(MAX3421_HI_SNDBAV_BIT) |
			 BIT(MAX3421_HI_RCVDAV_BIT)));

	अगर (hirq & BIT(MAX3421_HI_FRAME_BIT)) अणु
		max3421_hcd->frame_number = ((max3421_hcd->frame_number + 1)
					     & USB_MAX_FRAME_NUMBER);
		max3421_hcd->sched_pass = SCHED_PASS_PERIODIC;
	पूर्ण

	अगर (hirq & BIT(MAX3421_HI_RCVDAV_BIT))
		max3421_recv_data_available(hcd);

	अगर (hirq & BIT(MAX3421_HI_HXFRDN_BIT))
		max3421_host_transfer_करोne(hcd);

	अगर (hirq & BIT(MAX3421_HI_CONDET_BIT))
		max3421_detect_conn(hcd);

	/*
	 * Now process पूर्णांकerrupts that may affect HCD state
	 * other than the end-poपूर्णांकs:
	 */
	spin_lock_irqsave(&max3421_hcd->lock, flags);

	old_port_status = max3421_hcd->port_status;
	अगर (hirq & BIT(MAX3421_HI_BUSEVENT_BIT)) अणु
		अगर (max3421_hcd->port_status & USB_PORT_STAT_RESET) अणु
			/* BUSEVENT due to completion of Bus Reset */
			max3421_hcd->port_status &= ~USB_PORT_STAT_RESET;
			max3421_hcd->port_status |=  USB_PORT_STAT_ENABLE;
		पूर्ण अन्यथा अणु
			/* BUSEVENT due to completion of Bus Resume */
			pr_info("%s: BUSEVENT Bus Resume Done\n", __func__);
		पूर्ण
	पूर्ण
	अगर (hirq & BIT(MAX3421_HI_RWU_BIT))
		pr_info("%s: RWU\n", __func__);
	अगर (hirq & BIT(MAX3421_HI_SUSDN_BIT))
		pr_info("%s: SUSDN\n", __func__);

	chg = (old_port_status ^ max3421_hcd->port_status);
	max3421_hcd->port_status |= chg << 16;

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);

#अगर_घोषित DEBUG
	अणु
		अटल अचिन्हित दीर्घ last_समय;
		अक्षर sbuf[16 * 16], *dp, *end;
		पूर्णांक i;

		अगर (समय_after(jअगरfies, last_समय + 5*HZ)) अणु
			dp = sbuf;
			end = sbuf + माप(sbuf);
			*dp = '\0';
			क्रम (i = 0; i < 16; ++i) अणु
				पूर्णांक ret = snम_लिखो(dp, end - dp, " %lu",
						   max3421_hcd->err_stat[i]);
				अगर (ret < 0 || ret >= end - dp)
					अवरोध;	/* error or buffer full */
				dp += ret;
			पूर्ण
			pr_info("%s: hrsl_stats %s\n", __func__, sbuf);
			स_रखो(max3421_hcd->err_stat, 0,
			       माप(max3421_hcd->err_stat));
			last_समय = jअगरfies;

			dump_eps(hcd);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल पूर्णांक
max3421_reset_hcd(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	पूर्णांक समयout;

	/* perक्रमm a chip reset and रुको क्रम OSCIRQ संकेत to appear: */
	spi_wr8(hcd, MAX3421_REG_USBCTL, BIT(MAX3421_USBCTL_CHIPRES_BIT));
	/* clear reset: */
	spi_wr8(hcd, MAX3421_REG_USBCTL, 0);
	समयout = 1000;
	जबतक (1) अणु
		अगर (spi_rd8(hcd, MAX3421_REG_USBIRQ)
		    & BIT(MAX3421_USBIRQ_OSCOKIRQ_BIT))
			अवरोध;
		अगर (--समयout < 0) अणु
			dev_err(&spi->dev,
				"timed out waiting for oscillator OK signal");
			वापस 1;
		पूर्ण
		cond_resched();
	पूर्ण

	/*
	 * Turn on host mode, स्वतःmatic generation of SOF packets, and
	 * enable pull-करोwn रेजिस्टरs on DM/DP:
	 */
	max3421_hcd->mode = (BIT(MAX3421_MODE_HOST_BIT) |
			     BIT(MAX3421_MODE_SOFKAENAB_BIT) |
			     BIT(MAX3421_MODE_DMPULLDN_BIT) |
			     BIT(MAX3421_MODE_DPPULLDN_BIT));
	spi_wr8(hcd, MAX3421_REG_MODE, max3421_hcd->mode);

	/* reset frame-number: */
	max3421_hcd->frame_number = USB_MAX_FRAME_NUMBER;
	spi_wr8(hcd, MAX3421_REG_HCTL, BIT(MAX3421_HCTL_FRMRST_BIT));

	/* sample the state of the D+ and D- lines */
	spi_wr8(hcd, MAX3421_REG_HCTL, BIT(MAX3421_HCTL_SAMPLEBUS_BIT));
	max3421_detect_conn(hcd);

	/* enable frame, connection-detected, and bus-event पूर्णांकerrupts: */
	max3421_hcd->hien = (BIT(MAX3421_HI_FRAME_BIT) |
			     BIT(MAX3421_HI_CONDET_BIT) |
			     BIT(MAX3421_HI_BUSEVENT_BIT));
	spi_wr8(hcd, MAX3421_REG_HIEN, max3421_hcd->hien);

	/* enable पूर्णांकerrupts: */
	spi_wr8(hcd, MAX3421_REG_CPUCTL, BIT(MAX3421_CPUCTL_IE_BIT));
	वापस 1;
पूर्ण

अटल पूर्णांक
max3421_urb_करोne(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	अचिन्हित दीर्घ flags;
	काष्ठा urb *urb;
	पूर्णांक status;

	status = max3421_hcd->urb_करोne;
	max3421_hcd->urb_करोne = 0;
	अगर (status > 0)
		status = 0;
	urb = max3421_hcd->curr_urb;
	अगर (urb) अणु
		max3421_hcd->curr_urb = शून्य;
		spin_lock_irqsave(&max3421_hcd->lock, flags);
		usb_hcd_unlink_urb_from_ep(hcd, urb);
		spin_unlock_irqrestore(&max3421_hcd->lock, flags);

		/* must be called without the HCD spinlock: */
		usb_hcd_giveback_urb(hcd, urb, status);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक
max3421_spi_thपढ़ो(व्योम *dev_id)
अणु
	काष्ठा usb_hcd *hcd = dev_id;
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	पूर्णांक i, i_worked = 1;

	/* set full-duplex SPI mode, low-active पूर्णांकerrupt pin: */
	spi_wr8(hcd, MAX3421_REG_PINCTL,
		(BIT(MAX3421_PINCTL_FDUPSPI_BIT) |	/* full-duplex */
		 BIT(MAX3421_PINCTL_INTLEVEL_BIT)));	/* low-active irq */

	जबतक (!kthपढ़ो_should_stop()) अणु
		max3421_hcd->rev = spi_rd8(hcd, MAX3421_REG_REVISION);
		अगर (max3421_hcd->rev == 0x12 || max3421_hcd->rev == 0x13)
			अवरोध;
		dev_err(&spi->dev, "bad rev 0x%02x", max3421_hcd->rev);
		msleep(10000);
	पूर्ण
	dev_info(&spi->dev, "rev 0x%x, SPI clk %dHz, bpw %u, irq %d\n",
		 max3421_hcd->rev, spi->max_speed_hz, spi->bits_per_word,
		 spi->irq);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (!i_worked) अणु
			/*
			 * We'll be रुकोing क्रम wakeups from the hard
			 * पूर्णांकerrupt handler, so now is a good समय to
			 * sync our hien with the chip:
			 */
			spi_wr8(hcd, MAX3421_REG_HIEN, max3421_hcd->hien);

			set_current_state(TASK_INTERRUPTIBLE);
			अगर (test_and_clear_bit(ENABLE_IRQ, &max3421_hcd->toकरो))
				enable_irq(spi->irq);
			schedule();
			__set_current_state(TASK_RUNNING);
		पूर्ण

		i_worked = 0;

		अगर (max3421_hcd->urb_करोne)
			i_worked |= max3421_urb_करोne(hcd);
		अन्यथा अगर (max3421_handle_irqs(hcd))
			i_worked = 1;
		अन्यथा अगर (!max3421_hcd->curr_urb)
			i_worked |= max3421_select_and_start_urb(hcd);

		अगर (test_and_clear_bit(RESET_HCD, &max3421_hcd->toकरो))
			/* reset the HCD: */
			i_worked |= max3421_reset_hcd(hcd);
		अगर (test_and_clear_bit(RESET_PORT, &max3421_hcd->toकरो)) अणु
			/* perक्रमm a USB bus reset: */
			spi_wr8(hcd, MAX3421_REG_HCTL,
				BIT(MAX3421_HCTL_BUSRST_BIT));
			i_worked = 1;
		पूर्ण
		अगर (test_and_clear_bit(CHECK_UNLINK, &max3421_hcd->toकरो))
			i_worked |= max3421_check_unlink(hcd);
		अगर (test_and_clear_bit(IOPIN_UPDATE, &max3421_hcd->toकरो)) अणु
			/*
			 * IOPINS1/IOPINS2 करो not स्वतः-increment, so we can't
			 * use spi_wr_buf().
			 */
			क्रम (i = 0; i < ARRAY_SIZE(max3421_hcd->iopins); ++i) अणु
				u8 val = spi_rd8(hcd, MAX3421_REG_IOPINS1);

				val = ((val & 0xf0) |
				       (max3421_hcd->iopins[i] & 0x0f));
				spi_wr8(hcd, MAX3421_REG_IOPINS1 + i, val);
				max3421_hcd->iopins[i] = val;
			पूर्ण
			i_worked = 1;
		पूर्ण
	पूर्ण
	set_current_state(TASK_RUNNING);
	dev_info(&spi->dev, "SPI thread exiting");
	वापस 0;
पूर्ण

अटल पूर्णांक
max3421_reset_port(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	max3421_hcd->port_status &= ~(USB_PORT_STAT_ENABLE |
				      USB_PORT_STAT_LOW_SPEED);
	max3421_hcd->port_status |= USB_PORT_STAT_RESET;
	set_bit(RESET_PORT, &max3421_hcd->toकरो);
	wake_up_process(max3421_hcd->spi_thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक
max3421_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	hcd->self.sg_tablesize = 0;
	hcd->speed = HCD_USB2;
	hcd->self.root_hub->speed = USB_SPEED_FULL;
	set_bit(RESET_HCD, &max3421_hcd->toकरो);
	wake_up_process(max3421_hcd->spi_thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक
max3421_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	spin_lock_init(&max3421_hcd->lock);
	max3421_hcd->rh_state = MAX3421_RH_RUNNING;

	INIT_LIST_HEAD(&max3421_hcd->ep_list);

	hcd->घातer_budget = POWER_BUDGET;
	hcd->state = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;
	वापस 0;
पूर्ण

अटल व्योम
max3421_stop(काष्ठा usb_hcd *hcd)
अणु
पूर्ण

अटल पूर्णांक
max3421_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा max3421_ep *max3421_ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	चयन (usb_pipetype(urb->pipe)) अणु
	हाल PIPE_INTERRUPT:
	हाल PIPE_ISOCHRONOUS:
		अगर (urb->पूर्णांकerval < 0) अणु
			dev_err(&spi->dev,
			  "%s: interval=%d for intr-/iso-pipe; expected > 0\n",
				__func__, urb->पूर्णांकerval);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	max3421_ep = urb->ep->hcpriv;
	अगर (!max3421_ep) अणु
		/* माला_लो मुक्तd in max3421_endpoपूर्णांक_disable: */
		max3421_ep = kzalloc(माप(काष्ठा max3421_ep), GFP_ATOMIC);
		अगर (!max3421_ep) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
		max3421_ep->ep = urb->ep;
		max3421_ep->last_active = max3421_hcd->frame_number;
		urb->ep->hcpriv = max3421_ep;

		list_add_tail(&max3421_ep->ep_list, &max3421_hcd->ep_list);
	पूर्ण

	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval == 0) अणु
		/* Since we added to the queue, restart scheduling: */
		max3421_hcd->sched_pass = SCHED_PASS_PERIODIC;
		wake_up_process(max3421_hcd->spi_thपढ़ो);
	पूर्ण

out:
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक
max3421_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	/*
	 * This will set urb->unlinked which in turn causes the entry
	 * to be dropped at the next opportunity.
	 */
	retval = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (retval == 0) अणु
		set_bit(CHECK_UNLINK, &max3421_hcd->toकरो);
		wake_up_process(max3421_hcd->spi_thपढ़ो);
	पूर्ण
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	वापस retval;
पूर्ण

अटल व्योम
max3421_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	अगर (ep->hcpriv) अणु
		काष्ठा max3421_ep *max3421_ep = ep->hcpriv;

		/* हटाओ myself from the ep_list: */
		अगर (!list_empty(&max3421_ep->ep_list))
			list_del(&max3421_ep->ep_list);
		kमुक्त(max3421_ep);
		ep->hcpriv = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
पूर्ण

अटल पूर्णांक
max3421_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	वापस max3421_hcd->frame_number;
पूर्ण

/*
 * Should वापस a non-zero value when any port is undergoing a resume
 * transition जबतक the root hub is suspended.
 */
अटल पूर्णांक
max3421_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&max3421_hcd->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		जाओ करोne;

	*buf = 0;
	अगर ((max3421_hcd->port_status & PORT_C_MASK) != 0) अणु
		*buf = (1 << 1); /* a hub over-current condition exists */
		dev_dbg(hcd->self.controller,
			"port status 0x%08x has changes\n",
			max3421_hcd->port_status);
		retval = 1;
		अगर (max3421_hcd->rh_state == MAX3421_RH_SUSPENDED)
			usb_hcd_resume_root_hub(hcd);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	वापस retval;
पूर्ण

अटल अंतरभूत व्योम
hub_descriptor(काष्ठा usb_hub_descriptor *desc)
अणु
	स_रखो(desc, 0, माप(*desc));
	/*
	 * See Table 11-13: Hub Descriptor in USB 2.0 spec.
	 */
	desc->bDescriptorType = USB_DT_HUB; /* hub descriptor */
	desc->bDescLength = 9;
	desc->wHubCharacteristics = cpu_to_le16(HUB_CHAR_INDV_PORT_LPSM |
						HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = 1;
पूर्ण

/*
 * Set the MAX3421E general-purpose output with number PIN_NUMBER to
 * VALUE (0 or 1).  PIN_NUMBER may be in the range from 1-8.  For
 * any other value, this function acts as a no-op.
 */
अटल व्योम
max3421_gpout_set_value(काष्ठा usb_hcd *hcd, u8 pin_number, u8 value)
अणु
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mask, idx;

	--pin_number;
	अगर (pin_number >= MAX3421_GPOUT_COUNT)
		वापस;

	mask = 1u << (pin_number % 4);
	idx = pin_number / 4;

	अगर (value)
		max3421_hcd->iopins[idx] |=  mask;
	अन्यथा
		max3421_hcd->iopins[idx] &= ~mask;
	set_bit(IOPIN_UPDATE, &max3421_hcd->toकरो);
	wake_up_process(max3421_hcd->spi_thपढ़ो);
पूर्ण

अटल पूर्णांक
max3421_hub_control(काष्ठा usb_hcd *hcd, u16 type_req, u16 value, u16 index,
		    अक्षर *buf, u16 length)
अणु
	काष्ठा spi_device *spi = to_spi_device(hcd->self.controller);
	काष्ठा max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	काष्ठा max3421_hcd_platक्रमm_data *pdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	pdata = spi->dev.platक्रमm_data;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	चयन (type_req) अणु
	हाल ClearHubFeature:
		अवरोध;
	हाल ClearPortFeature:
		चयन (value) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hcd->self.controller, "power-off\n");
			max3421_gpout_set_value(hcd, pdata->vbus_gpout,
						!pdata->vbus_active_level);
			fallthrough;
		शेष:
			max3421_hcd->port_status &= ~(1 << value);
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		hub_descriptor((काष्ठा usb_hub_descriptor *) buf);
		अवरोध;

	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
	हाल GetPortErrorCount:
	हाल SetHubDepth:
		/* USB3 only */
		जाओ error;

	हाल GetHubStatus:
		*(__le32 *) buf = cpu_to_le32(0);
		अवरोध;

	हाल GetPortStatus:
		अगर (index != 1) अणु
			retval = -EPIPE;
			जाओ error;
		पूर्ण
		((__le16 *) buf)[0] = cpu_to_le16(max3421_hcd->port_status);
		((__le16 *) buf)[1] =
			cpu_to_le16(max3421_hcd->port_status >> 16);
		अवरोध;

	हाल SetHubFeature:
		retval = -EPIPE;
		अवरोध;

	हाल SetPortFeature:
		चयन (value) अणु
		हाल USB_PORT_FEAT_LINK_STATE:
		हाल USB_PORT_FEAT_U1_TIMEOUT:
		हाल USB_PORT_FEAT_U2_TIMEOUT:
		हाल USB_PORT_FEAT_BH_PORT_RESET:
			जाओ error;
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (max3421_hcd->active)
				max3421_hcd->port_status |=
					USB_PORT_STAT_SUSPEND;
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(hcd->self.controller, "power-on\n");
			max3421_hcd->port_status |= USB_PORT_STAT_POWER;
			max3421_gpout_set_value(hcd, pdata->vbus_gpout,
						pdata->vbus_active_level);
			अवरोध;
		हाल USB_PORT_FEAT_RESET:
			max3421_reset_port(hcd);
			fallthrough;
		शेष:
			अगर ((max3421_hcd->port_status & USB_PORT_STAT_POWER)
			    != 0)
				max3421_hcd->port_status |= (1 << value);
		पूर्ण
		अवरोध;

	शेष:
		dev_dbg(hcd->self.controller,
			"hub control req%04x v%04x i%04x l%d\n",
			type_req, value, index, length);
error:		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक
max3421_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक
max3421_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा hc_driver max3421_hcd_desc = अणु
	.description =		"max3421",
	.product_desc =		DRIVER_DESC,
	.hcd_priv_size =	माप(काष्ठा max3421_hcd),
	.flags =		HCD_USB11,
	.reset =		max3421_reset,
	.start =		max3421_start,
	.stop =			max3421_stop,
	.get_frame_number =	max3421_get_frame_number,
	.urb_enqueue =		max3421_urb_enqueue,
	.urb_dequeue =		max3421_urb_dequeue,
	.endpoपूर्णांक_disable =	max3421_endpoपूर्णांक_disable,
	.hub_status_data =	max3421_hub_status_data,
	.hub_control =		max3421_hub_control,
	.bus_suspend =		max3421_bus_suspend,
	.bus_resume =		max3421_bus_resume,
पूर्ण;

अटल पूर्णांक
max3421_of_vbus_en_pin(काष्ठा device *dev, काष्ठा max3421_hcd_platक्रमm_data *pdata)
अणु
	पूर्णांक retval;
	uपूर्णांक32_t value[2];

	अगर (!pdata)
		वापस -EINVAL;

	retval = of_property_पढ़ो_u32_array(dev->of_node, "maxim,vbus-en-pin", value, 2);
	अगर (retval) अणु
		dev_err(dev, "device tree node property 'maxim,vbus-en-pin' is missing\n");
		वापस retval;
	पूर्ण
	dev_info(dev, "property 'maxim,vbus-en-pin' value is <%d %d>\n", value[0], value[1]);

	pdata->vbus_gpout = value[0];
	pdata->vbus_active_level = value[1];

	वापस 0;
पूर्ण

अटल पूर्णांक
max3421_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा max3421_hcd *max3421_hcd;
	काष्ठा usb_hcd *hcd = शून्य;
	काष्ठा max3421_hcd_platक्रमm_data *pdata = शून्य;
	पूर्णांक retval;

	अगर (spi_setup(spi) < 0) अणु
		dev_err(&spi->dev, "Unable to setup SPI bus");
		वापस -EFAULT;
	पूर्ण

	अगर (!spi->irq) अणु
		dev_err(dev, "Failed to get SPI IRQ");
		वापस -EFAULT;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		pdata = devm_kzalloc(&spi->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		retval = max3421_of_vbus_en_pin(dev, pdata);
		अगर (retval)
			जाओ error;

		spi->dev.platक्रमm_data = pdata;
	पूर्ण

	pdata = spi->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&spi->dev, "driver configuration data is not provided\n");
		retval = -EFAULT;
		जाओ error;
	पूर्ण
	अगर (pdata->vbus_active_level > 1) अणु
		dev_err(&spi->dev, "vbus active level value %d is out of range (0/1)\n", pdata->vbus_active_level);
		retval = -EINVAL;
		जाओ error;
	पूर्ण
	अगर (pdata->vbus_gpout < 1 || pdata->vbus_gpout > MAX3421_GPOUT_COUNT) अणु
		dev_err(&spi->dev, "vbus gpout value %d is out of range (1..8)\n", pdata->vbus_gpout);
		retval = -EINVAL;
		जाओ error;
	पूर्ण

	retval = -ENOMEM;
	hcd = usb_create_hcd(&max3421_hcd_desc, &spi->dev,
			     dev_name(&spi->dev));
	अगर (!hcd) अणु
		dev_err(&spi->dev, "failed to create HCD structure\n");
		जाओ error;
	पूर्ण
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	max3421_hcd = hcd_to_max3421(hcd);
	max3421_hcd->next = max3421_hcd_list;
	max3421_hcd_list = max3421_hcd;
	INIT_LIST_HEAD(&max3421_hcd->ep_list);

	max3421_hcd->tx = kदो_स्मृति(माप(*max3421_hcd->tx), GFP_KERNEL);
	अगर (!max3421_hcd->tx)
		जाओ error;
	max3421_hcd->rx = kदो_स्मृति(माप(*max3421_hcd->rx), GFP_KERNEL);
	अगर (!max3421_hcd->rx)
		जाओ error;

	max3421_hcd->spi_thपढ़ो = kthपढ़ो_run(max3421_spi_thपढ़ो, hcd,
					      "max3421_spi_thread");
	अगर (max3421_hcd->spi_thपढ़ो == ERR_PTR(-ENOMEM)) अणु
		dev_err(&spi->dev,
			"failed to create SPI thread (out of memory)\n");
		जाओ error;
	पूर्ण

	retval = usb_add_hcd(hcd, 0, 0);
	अगर (retval) अणु
		dev_err(&spi->dev, "failed to add HCD\n");
		जाओ error;
	पूर्ण

	retval = request_irq(spi->irq, max3421_irq_handler,
			     IRQF_TRIGGER_LOW, "max3421", hcd);
	अगर (retval < 0) अणु
		dev_err(&spi->dev, "failed to request irq %d\n", spi->irq);
		जाओ error;
	पूर्ण
	वापस 0;

error:
	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node && pdata) अणु
		devm_kमुक्त(&spi->dev, pdata);
		spi->dev.platक्रमm_data = शून्य;
	पूर्ण

	अगर (hcd) अणु
		kमुक्त(max3421_hcd->tx);
		kमुक्त(max3421_hcd->rx);
		अगर (max3421_hcd->spi_thपढ़ो)
			kthपढ़ो_stop(max3421_hcd->spi_thपढ़ो);
		usb_put_hcd(hcd);
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक
max3421_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max3421_hcd *max3421_hcd = शून्य, **prev;
	काष्ठा usb_hcd *hcd = शून्य;
	अचिन्हित दीर्घ flags;

	क्रम (prev = &max3421_hcd_list; *prev; prev = &(*prev)->next) अणु
		max3421_hcd = *prev;
		hcd = max3421_to_hcd(max3421_hcd);
		अगर (hcd->self.controller == &spi->dev)
			अवरोध;
	पूर्ण
	अगर (!max3421_hcd) अणु
		dev_err(&spi->dev, "no MAX3421 HCD found for SPI device %p\n",
			spi);
		वापस -ENODEV;
	पूर्ण

	usb_हटाओ_hcd(hcd);

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	kthपढ़ो_stop(max3421_hcd->spi_thपढ़ो);
	*prev = max3421_hcd->next;

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);

	मुक्त_irq(spi->irq, hcd);

	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max3421_of_match_table[] = अणु
	अणु .compatible = "maxim,max3421", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max3421_of_match_table);

अटल काष्ठा spi_driver max3421_driver = अणु
	.probe		= max3421_probe,
	.हटाओ		= max3421_हटाओ,
	.driver		= अणु
		.name	= "max3421-hcd",
		.of_match_table = of_match_ptr(max3421_of_match_table),
	पूर्ण,
पूर्ण;

module_spi_driver(max3421_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("David Mosberger <davidm@egauge.net>");
MODULE_LICENSE("GPL");
