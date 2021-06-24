<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#अगर_अघोषित __LINUX_XHCI_HCD_H
#घोषणा __LINUX_XHCI_HCD_H

#समावेश <linux/usb.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

/* Code sharing between pci-quirks and xhci hcd */
#समावेश	"xhci-ext-caps.h"
#समावेश "pci-quirks.h"

/* xHCI PCI Configuration Registers */
#घोषणा XHCI_SBRN_OFFSET	(0x60)

/* Max number of USB devices क्रम any host controller - limit in section 6.1 */
#घोषणा MAX_HC_SLOTS		256
/* Section 5.3.3 - MaxPorts */
#घोषणा MAX_HC_PORTS		127

/*
 * xHCI रेजिस्टर पूर्णांकerface.
 * This corresponds to the eXtensible Host Controller Interface (xHCI)
 * Revision 0.95 specअगरication
 */

/**
 * काष्ठा xhci_cap_regs - xHCI Host Controller Capability Registers.
 * @hc_capbase:		length of the capabilities रेजिस्टर and HC version number
 * @hcs_params1:	HCSPARAMS1 - Structural Parameters 1
 * @hcs_params2:	HCSPARAMS2 - Structural Parameters 2
 * @hcs_params3:	HCSPARAMS3 - Structural Parameters 3
 * @hcc_params:		HCCPARAMS - Capability Parameters
 * @db_off:		DBOFF - Doorbell array offset
 * @run_regs_off:	RTSOFF - Runसमय रेजिस्टर space offset
 * @hcc_params2:	HCCPARAMS2 Capability Parameters 2, xhci 1.1 only
 */
काष्ठा xhci_cap_regs अणु
	__le32	hc_capbase;
	__le32	hcs_params1;
	__le32	hcs_params2;
	__le32	hcs_params3;
	__le32	hcc_params;
	__le32	db_off;
	__le32	run_regs_off;
	__le32	hcc_params2; /* xhci 1.1 */
	/* Reserved up to (CAPLENGTH - 0x1C) */
पूर्ण;

/* hc_capbase biपंचांगasks */
/* bits 7:0 - how दीर्घ is the Capabilities रेजिस्टर */
#घोषणा HC_LENGTH(p)		XHCI_HC_LENGTH(p)
/* bits 31:16	*/
#घोषणा HC_VERSION(p)		(((p) >> 16) & 0xffff)

/* HCSPARAMS1 - hcs_params1 - biपंचांगasks */
/* bits 0:7, Max Device Slots */
#घोषणा HCS_MAX_SLOTS(p)	(((p) >> 0) & 0xff)
#घोषणा HCS_SLOTS_MASK		0xff
/* bits 8:18, Max Interrupters */
#घोषणा HCS_MAX_INTRS(p)	(((p) >> 8) & 0x7ff)
/* bits 24:31, Max Ports - max value is 0x7F = 127 ports */
#घोषणा HCS_MAX_PORTS(p)	(((p) >> 24) & 0x7f)

/* HCSPARAMS2 - hcs_params2 - biपंचांगasks */
/* bits 0:3, frames or uframes that SW needs to queue transactions
 * ahead of the HW to meet periodic deadlines */
#घोषणा HCS_IST(p)		(((p) >> 0) & 0xf)
/* bits 4:7, max number of Event Ring segments */
#घोषणा HCS_ERST_MAX(p)		(((p) >> 4) & 0xf)
/* bits 21:25 Hi 5 bits of Scratchpad buffers SW must allocate क्रम the HW */
/* bit 26 Scratchpad restore - क्रम save/restore HW state - not used yet */
/* bits 27:31 Lo 5 bits of Scratchpad buffers SW must allocate क्रम the HW */
#घोषणा HCS_MAX_SCRATCHPAD(p)   ((((p) >> 16) & 0x3e0) | (((p) >> 27) & 0x1f))

/* HCSPARAMS3 - hcs_params3 - biपंचांगasks */
/* bits 0:7, Max U1 to U0 latency क्रम the roothub ports */
#घोषणा HCS_U1_LATENCY(p)	(((p) >> 0) & 0xff)
/* bits 16:31, Max U2 to U0 latency क्रम the roothub ports */
#घोषणा HCS_U2_LATENCY(p)	(((p) >> 16) & 0xffff)

/* HCCPARAMS - hcc_params - biपंचांगasks */
/* true: HC can use 64-bit address poपूर्णांकers */
#घोषणा HCC_64BIT_ADDR(p)	((p) & (1 << 0))
/* true: HC can करो bandwidth negotiation */
#घोषणा HCC_BANDWIDTH_NEG(p)	((p) & (1 << 1))
/* true: HC uses 64-byte Device Context काष्ठाures
 * FIXME 64-byte context काष्ठाures aren't supported yet.
 */
#घोषणा HCC_64BYTE_CONTEXT(p)	((p) & (1 << 2))
/* true: HC has port घातer चयनes */
#घोषणा HCC_PPC(p)		((p) & (1 << 3))
/* true: HC has port indicators */
#घोषणा HCS_INDICATOR(p)	((p) & (1 << 4))
/* true: HC has Light HC Reset Capability */
#घोषणा HCC_LIGHT_RESET(p)	((p) & (1 << 5))
/* true: HC supports latency tolerance messaging */
#घोषणा HCC_LTC(p)		((p) & (1 << 6))
/* true: no secondary Stream ID Support */
#घोषणा HCC_NSS(p)		((p) & (1 << 7))
/* true: HC supports Stopped - Short Packet */
#घोषणा HCC_SPC(p)		((p) & (1 << 9))
/* true: HC has Contiguous Frame ID Capability */
#घोषणा HCC_CFC(p)		((p) & (1 << 11))
/* Max size क्रम Primary Stream Arrays - 2^(n+1), where n is bits 12:15 */
#घोषणा HCC_MAX_PSA(p)		(1 << ((((p) >> 12) & 0xf) + 1))
/* Extended Capabilities poपूर्णांकer from PCI base - section 5.3.6 */
#घोषणा HCC_EXT_CAPS(p)		XHCI_HCC_EXT_CAPS(p)

#घोषणा CTX_SIZE(_hcc)		(HCC_64BYTE_CONTEXT(_hcc) ? 64 : 32)

/* db_off biपंचांगask - bits 0:1 reserved */
#घोषणा	DBOFF_MASK	(~0x3)

/* run_regs_off biपंचांगask - bits 0:4 reserved */
#घोषणा	RTSOFF_MASK	(~0x1f)

/* HCCPARAMS2 - hcc_params2 - biपंचांगasks */
/* true: HC supports U3 entry Capability */
#घोषणा	HCC2_U3C(p)		((p) & (1 << 0))
/* true: HC supports Configure endpoपूर्णांक command Max निकास latency too large */
#घोषणा	HCC2_CMC(p)		((p) & (1 << 1))
/* true: HC supports Force Save context Capability */
#घोषणा	HCC2_FSC(p)		((p) & (1 << 2))
/* true: HC supports Compliance Transition Capability */
#घोषणा	HCC2_CTC(p)		((p) & (1 << 3))
/* true: HC support Large ESIT payload Capability > 48k */
#घोषणा	HCC2_LEC(p)		((p) & (1 << 4))
/* true: HC support Configuration Inक्रमmation Capability */
#घोषणा	HCC2_CIC(p)		((p) & (1 << 5))
/* true: HC support Extended TBC Capability, Isoc burst count > 65535 */
#घोषणा	HCC2_ETC(p)		((p) & (1 << 6))

/* Number of रेजिस्टरs per port */
#घोषणा	NUM_PORT_REGS	4

#घोषणा PORTSC		0
#घोषणा PORTPMSC	1
#घोषणा PORTLI		2
#घोषणा PORTHLPMC	3

/**
 * काष्ठा xhci_op_regs - xHCI Host Controller Operational Registers.
 * @command:		USBCMD - xHC command रेजिस्टर
 * @status:		USBSTS - xHC status रेजिस्टर
 * @page_size:		This indicates the page size that the host controller
 * 			supports.  If bit n is set, the HC supports a page size
 * 			of 2^(n+12), up to a 128MB page size.
 * 			4K is the minimum page size.
 * @cmd_ring:		CRP - 64-bit Command Ring Poपूर्णांकer
 * @dcbaa_ptr:		DCBAAP - 64-bit Device Context Base Address Array Poपूर्णांकer
 * @config_reg:		CONFIG - Configure Register
 * @port_status_base:	PORTSCn - base address क्रम Port Status and Control
 * 			Each port has a Port Status and Control रेजिस्टर,
 * 			followed by a Port Power Management Status and Control
 * 			रेजिस्टर, a Port Link Info रेजिस्टर, and a reserved
 * 			रेजिस्टर.
 * @port_घातer_base:	PORTPMSCn - base address क्रम
 * 			Port Power Management Status and Control
 * @port_link_base:	PORTLIn - base address क्रम Port Link Info (current
 * 			Link PM state and control) क्रम USB 2.1 and USB 3.0
 * 			devices.
 */
काष्ठा xhci_op_regs अणु
	__le32	command;
	__le32	status;
	__le32	page_size;
	__le32	reserved1;
	__le32	reserved2;
	__le32	dev_notअगरication;
	__le64	cmd_ring;
	/* rsvd: offset 0x20-2F */
	__le32	reserved3[4];
	__le64	dcbaa_ptr;
	__le32	config_reg;
	/* rsvd: offset 0x3C-3FF */
	__le32	reserved4[241];
	/* port 1 रेजिस्टरs, which serve as a base address क्रम other ports */
	__le32	port_status_base;
	__le32	port_घातer_base;
	__le32	port_link_base;
	__le32	reserved5;
	/* रेजिस्टरs क्रम ports 2-255 */
	__le32	reserved6[NUM_PORT_REGS*254];
पूर्ण;

/* USBCMD - USB command - command biपंचांगasks */
/* start/stop HC execution - करो not ग_लिखो unless HC is halted*/
#घोषणा CMD_RUN		XHCI_CMD_RUN
/* Reset HC - resets पूर्णांकernal HC state machine and all रेजिस्टरs (except
 * PCI config regs).  HC करोes NOT drive a USB reset on the करोwnstream ports.
 * The xHCI driver must reinitialize the xHC after setting this bit.
 */
#घोषणा CMD_RESET	(1 << 1)
/* Event Interrupt Enable - a '1' allows पूर्णांकerrupts from the host controller */
#घोषणा CMD_EIE		XHCI_CMD_EIE
/* Host System Error Interrupt Enable - get out-of-band संकेत क्रम HC errors */
#घोषणा CMD_HSEIE	XHCI_CMD_HSEIE
/* bits 4:6 are reserved (and should be preserved on ग_लिखोs). */
/* light reset (port status stays unchanged) - reset completed when this is 0 */
#घोषणा CMD_LRESET	(1 << 7)
/* host controller save/restore state. */
#घोषणा CMD_CSS		(1 << 8)
#घोषणा CMD_CRS		(1 << 9)
/* Enable Wrap Event - '1' means xHC generates an event when MFINDEX wraps. */
#घोषणा CMD_EWE		XHCI_CMD_EWE
/* MFINDEX घातer management - '1' means xHC can stop MFINDEX counter अगर all root
 * hubs are in U3 (selective suspend), disconnect, disabled, or घातered-off.
 * '0' means the xHC can घातer it off अगर all ports are in the disconnect,
 * disabled, or घातered-off state.
 */
#घोषणा CMD_PM_INDEX	(1 << 11)
/* bit 14 Extended TBC Enable, changes Isoc TRB fields to support larger TBC */
#घोषणा CMD_ETE		(1 << 14)
/* bits 15:31 are reserved (and should be preserved on ग_लिखोs). */

/* IMAN - Interrupt Management Register */
#घोषणा IMAN_IE		(1 << 1)
#घोषणा IMAN_IP		(1 << 0)

/* USBSTS - USB status - status biपंचांगasks */
/* HC not running - set to 1 when run/stop bit is cleared. */
#घोषणा STS_HALT	XHCI_STS_HALT
/* serious error, e.g. PCI parity error.  The HC will clear the run/stop bit. */
#घोषणा STS_FATAL	(1 << 2)
/* event पूर्णांकerrupt - clear this prior to clearing any IP flags in IR set*/
#घोषणा STS_EINT	(1 << 3)
/* port change detect */
#घोषणा STS_PORT	(1 << 4)
/* bits 5:7 reserved and zeroed */
/* save state status - '1' means xHC is saving state */
#घोषणा STS_SAVE	(1 << 8)
/* restore state status - '1' means xHC is restoring state */
#घोषणा STS_RESTORE	(1 << 9)
/* true: save or restore error */
#घोषणा STS_SRE		(1 << 10)
/* true: Controller Not Ready to accept करोorbell or op reg ग_लिखोs after reset */
#घोषणा STS_CNR		XHCI_STS_CNR
/* true: पूर्णांकernal Host Controller Error - SW needs to reset and reinitialize */
#घोषणा STS_HCE		(1 << 12)
/* bits 13:31 reserved and should be preserved */

/*
 * DNCTRL - Device Notअगरication Control Register - dev_notअगरication biपंचांगasks
 * Generate a device notअगरication event when the HC sees a transaction with a
 * notअगरication type that matches a bit set in this bit field.
 */
#घोषणा	DEV_NOTE_MASK		(0xffff)
#घोषणा ENABLE_DEV_NOTE(x)	(1 << (x))
/* Most of the device notअगरication types should only be used क्रम debug.
 * SW करोes need to pay attention to function wake notअगरications.
 */
#घोषणा	DEV_NOTE_FWAKE		ENABLE_DEV_NOTE(1)

/* CRCR - Command Ring Control Register - cmd_ring biपंचांगasks */
/* bit 0 is the command ring cycle state */
/* stop ring operation after completion of the currently executing command */
#घोषणा CMD_RING_PAUSE		(1 << 1)
/* stop ring immediately - पात the currently executing command */
#घोषणा CMD_RING_ABORT		(1 << 2)
/* true: command ring is running */
#घोषणा CMD_RING_RUNNING	(1 << 3)
/* bits 4:5 reserved and should be preserved */
/* Command Ring poपूर्णांकer - bit mask क्रम the lower 32 bits. */
#घोषणा CMD_RING_RSVD_BITS	(0x3f)

/* CONFIG - Configure Register - config_reg biपंचांगasks */
/* bits 0:7 - maximum number of device slots enabled (NumSlotsEn) */
#घोषणा MAX_DEVS(p)	((p) & 0xff)
/* bit 8: U3 Entry Enabled, निश्चित PLC when root port enters U3, xhci 1.1 */
#घोषणा CONFIG_U3E		(1 << 8)
/* bit 9: Configuration Inक्रमmation Enable, xhci 1.1 */
#घोषणा CONFIG_CIE		(1 << 9)
/* bits 10:31 - reserved and should be preserved */

/* PORTSC - Port Status and Control Register - port_status_base biपंचांगasks */
/* true: device connected */
#घोषणा PORT_CONNECT	(1 << 0)
/* true: port enabled */
#घोषणा PORT_PE		(1 << 1)
/* bit 2 reserved and zeroed */
/* true: port has an over-current condition */
#घोषणा PORT_OC		(1 << 3)
/* true: port reset संकेतing निश्चितed */
#घोषणा PORT_RESET	(1 << 4)
/* Port Link State - bits 5:8
 * A पढ़ो gives the current link PM state of the port,
 * a ग_लिखो with Link State Write Strobe set sets the link state.
 */
#घोषणा PORT_PLS_MASK	(0xf << 5)
#घोषणा XDEV_U0		(0x0 << 5)
#घोषणा XDEV_U1		(0x1 << 5)
#घोषणा XDEV_U2		(0x2 << 5)
#घोषणा XDEV_U3		(0x3 << 5)
#घोषणा XDEV_DISABLED	(0x4 << 5)
#घोषणा XDEV_RXDETECT	(0x5 << 5)
#घोषणा XDEV_INACTIVE	(0x6 << 5)
#घोषणा XDEV_POLLING	(0x7 << 5)
#घोषणा XDEV_RECOVERY	(0x8 << 5)
#घोषणा XDEV_HOT_RESET	(0x9 << 5)
#घोषणा XDEV_COMP_MODE	(0xa << 5)
#घोषणा XDEV_TEST_MODE	(0xb << 5)
#घोषणा XDEV_RESUME	(0xf << 5)

/* true: port has घातer (see HCC_PPC) */
#घोषणा PORT_POWER	(1 << 9)
/* bits 10:13 indicate device speed:
 * 0 - undefined speed - port hasn't be initialized by a reset yet
 * 1 - full speed
 * 2 - low speed
 * 3 - high speed
 * 4 - super speed
 * 5-15 reserved
 */
#घोषणा DEV_SPEED_MASK		(0xf << 10)
#घोषणा	XDEV_FS			(0x1 << 10)
#घोषणा	XDEV_LS			(0x2 << 10)
#घोषणा	XDEV_HS			(0x3 << 10)
#घोषणा	XDEV_SS			(0x4 << 10)
#घोषणा	XDEV_SSP		(0x5 << 10)
#घोषणा DEV_UNDEFSPEED(p)	(((p) & DEV_SPEED_MASK) == (0x0<<10))
#घोषणा DEV_FULLSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_FS)
#घोषणा DEV_LOWSPEED(p)		(((p) & DEV_SPEED_MASK) == XDEV_LS)
#घोषणा DEV_HIGHSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_HS)
#घोषणा DEV_SUPERSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_SS)
#घोषणा DEV_SUPERSPEEDPLUS(p)	(((p) & DEV_SPEED_MASK) == XDEV_SSP)
#घोषणा DEV_SUPERSPEED_ANY(p)	(((p) & DEV_SPEED_MASK) >= XDEV_SS)
#घोषणा DEV_PORT_SPEED(p)	(((p) >> 10) & 0x0f)

/* Bits 20:23 in the Slot Context are the speed क्रम the device */
#घोषणा	SLOT_SPEED_FS		(XDEV_FS << 10)
#घोषणा	SLOT_SPEED_LS		(XDEV_LS << 10)
#घोषणा	SLOT_SPEED_HS		(XDEV_HS << 10)
#घोषणा	SLOT_SPEED_SS		(XDEV_SS << 10)
#घोषणा	SLOT_SPEED_SSP		(XDEV_SSP << 10)
/* Port Indicator Control */
#घोषणा PORT_LED_OFF	(0 << 14)
#घोषणा PORT_LED_AMBER	(1 << 14)
#घोषणा PORT_LED_GREEN	(2 << 14)
#घोषणा PORT_LED_MASK	(3 << 14)
/* Port Link State Write Strobe - set this when changing link state */
#घोषणा PORT_LINK_STROBE	(1 << 16)
/* true: connect status change */
#घोषणा PORT_CSC	(1 << 17)
/* true: port enable change */
#घोषणा PORT_PEC	(1 << 18)
/* true: warm reset क्रम a USB 3.0 device is करोne.  A "hot" reset माला_दो the port
 * पूर्णांकo an enabled state, and the device पूर्णांकo the शेष state.  A "warm" reset
 * also resets the link, क्रमcing the device through the link training sequence.
 * SW can also look at the Port Reset रेजिस्टर to see when warm reset is करोne.
 */
#घोषणा PORT_WRC	(1 << 19)
/* true: over-current change */
#घोषणा PORT_OCC	(1 << 20)
/* true: reset change - 1 to 0 transition of PORT_RESET */
#घोषणा PORT_RC		(1 << 21)
/* port link status change - set on some port link state transitions:
 *  Transition				Reason
 *  ------------------------------------------------------------------------------
 *  - U3 to Resume			Wakeup संकेतing from a device
 *  - Resume to Recovery to U0		USB 3.0 device resume
 *  - Resume to U0			USB 2.0 device resume
 *  - U3 to Recovery to U0		Software resume of USB 3.0 device complete
 *  - U3 to U0				Software resume of USB 2.0 device complete
 *  - U2 to U0				L1 resume of USB 2.1 device complete
 *  - U0 to U0 (???)			L1 entry rejection by USB 2.1 device
 *  - U0 to disabled			L1 entry error with USB 2.1 device
 *  - Any state to inactive		Error on USB 3.0 port
 */
#घोषणा PORT_PLC	(1 << 22)
/* port configure error change - port failed to configure its link partner */
#घोषणा PORT_CEC	(1 << 23)
#घोषणा PORT_CHANGE_MASK	(PORT_CSC | PORT_PEC | PORT_WRC | PORT_OCC | \
				 PORT_RC | PORT_PLC | PORT_CEC)


/* Cold Attach Status - xHC can set this bit to report device attached during
 * Sx state. Warm port reset should be perfomed to clear this bit and move port
 * to connected state.
 */
#घोषणा PORT_CAS	(1 << 24)
/* wake on connect (enable) */
#घोषणा PORT_WKCONN_E	(1 << 25)
/* wake on disconnect (enable) */
#घोषणा PORT_WKDISC_E	(1 << 26)
/* wake on over-current (enable) */
#घोषणा PORT_WKOC_E	(1 << 27)
/* bits 28:29 reserved */
/* true: device is non-removable - क्रम USB 3.0 roothub emulation */
#घोषणा PORT_DEV_REMOVE	(1 << 30)
/* Initiate a warm port reset - complete when PORT_WRC is '1' */
#घोषणा PORT_WR		(1 << 31)

/* We mark duplicate entries with -1 */
#घोषणा DUPLICATE_ENTRY ((u8)(-1))

/* Port Power Management Status and Control - port_घातer_base biपंचांगasks */
/* Inactivity समयr value क्रम transitions पूर्णांकo U1, in microseconds.
 * Timeout can be up to 127us.  0xFF means an infinite समयout.
 */
#घोषणा PORT_U1_TIMEOUT(p)	((p) & 0xff)
#घोषणा PORT_U1_TIMEOUT_MASK	0xff
/* Inactivity समयr value क्रम transitions पूर्णांकo U2 */
#घोषणा PORT_U2_TIMEOUT(p)	(((p) & 0xff) << 8)
#घोषणा PORT_U2_TIMEOUT_MASK	(0xff << 8)
/* Bits 24:31 क्रम port testing */

/* USB2 Protocol PORTSPMSC */
#घोषणा	PORT_L1S_MASK		7
#घोषणा	PORT_L1S_SUCCESS	1
#घोषणा	PORT_RWE		(1 << 3)
#घोषणा	PORT_HIRD(p)		(((p) & 0xf) << 4)
#घोषणा	PORT_HIRD_MASK		(0xf << 4)
#घोषणा	PORT_L1DS_MASK		(0xff << 8)
#घोषणा	PORT_L1DS(p)		(((p) & 0xff) << 8)
#घोषणा	PORT_HLE		(1 << 16)
#घोषणा PORT_TEST_MODE_SHIFT	28

/* USB3 Protocol PORTLI  Port Link Inक्रमmation */
#घोषणा PORT_RX_LANES(p)	(((p) >> 16) & 0xf)
#घोषणा PORT_TX_LANES(p)	(((p) >> 20) & 0xf)

/* USB2 Protocol PORTHLPMC */
#घोषणा PORT_HIRDM(p)((p) & 3)
#घोषणा PORT_L1_TIMEOUT(p)(((p) & 0xff) << 2)
#घोषणा PORT_BESLD(p)(((p) & 0xf) << 10)

/* use 512 microseconds as USB2 LPM L1 शेष समयout. */
#घोषणा XHCI_L1_TIMEOUT		512

/* Set शेष HIRD/BESL value to 4 (350/400us) क्रम USB2 L1 LPM resume latency.
 * Safe to use with mixed HIRD and BESL प्रणालीs (host and device) and is used
 * by other operating प्रणालीs.
 *
 * XHCI 1.0 errata 8/14/12 Table 13 notes:
 * "Software should choose xHC BESL/BESLD field values that करो not violate a
 * device's resume latency requirements,
 * e.g. not program values > '4' if BLC = '1' and a HIRD device is attached,
 * or not program values < '4' if BLC = '0' and a BESL device is attached.
 */
#घोषणा XHCI_DEFAULT_BESL	4

/*
 * USB3 specअगरication define a 360ms tPollingLFPSTiemout क्रम USB3 ports
 * to complete link training. usually link trainig completes much faster
 * so check status 10 बार with 36ms sleep in places we need to रुको क्रम
 * polling to complete.
 */
#घोषणा XHCI_PORT_POLLING_LFPS_TIME  36

/**
 * काष्ठा xhci_पूर्णांकr_reg - Interrupt Register Set
 * @irq_pending:	IMAN - Interrupt Management Register.  Used to enable
 *			पूर्णांकerrupts and check क्रम pending पूर्णांकerrupts.
 * @irq_control:	IMOD - Interrupt Moderation Register.
 * 			Used to throttle पूर्णांकerrupts.
 * @erst_size:		Number of segments in the Event Ring Segment Table (ERST).
 * @erst_base:		ERST base address.
 * @erst_dequeue:	Event ring dequeue poपूर्णांकer.
 *
 * Each पूर्णांकerrupter (defined by a MSI-X vector) has an event ring and an Event
 * Ring Segment Table (ERST) associated with it.  The event ring is comprised of
 * multiple segments of the same size.  The HC places events on the ring and
 * "updates the Cycle bit in the TRBs to indicate to software the current
 * position of the Enqueue Poपूर्णांकer." The HCD (Linux) processes those events and
 * updates the dequeue poपूर्णांकer.
 */
काष्ठा xhci_पूर्णांकr_reg अणु
	__le32	irq_pending;
	__le32	irq_control;
	__le32	erst_size;
	__le32	rsvd;
	__le64	erst_base;
	__le64	erst_dequeue;
पूर्ण;

/* irq_pending biपंचांगasks */
#घोषणा	ER_IRQ_PENDING(p)	((p) & 0x1)
/* bits 2:31 need to be preserved */
/* THIS IS BUGGY - FIXME - IP IS WRITE 1 TO CLEAR */
#घोषणा	ER_IRQ_CLEAR(p)		((p) & 0xfffffffe)
#घोषणा	ER_IRQ_ENABLE(p)	((ER_IRQ_CLEAR(p)) | 0x2)
#घोषणा	ER_IRQ_DISABLE(p)	((ER_IRQ_CLEAR(p)) & ~(0x2))

/* irq_control biपंचांगasks */
/* Minimum पूर्णांकerval between पूर्णांकerrupts (in 250ns पूर्णांकervals).  The पूर्णांकerval
 * between पूर्णांकerrupts will be दीर्घer अगर there are no events on the event ring.
 * Default is 4000 (1 ms).
 */
#घोषणा ER_IRQ_INTERVAL_MASK	(0xffff)
/* Counter used to count करोwn the समय to the next पूर्णांकerrupt - HW use only */
#घोषणा ER_IRQ_COUNTER_MASK	(0xffff << 16)

/* erst_size biपंचांगasks */
/* Preserve bits 16:31 of erst_size */
#घोषणा	ERST_SIZE_MASK		(0xffff << 16)

/* erst_dequeue biपंचांगasks */
/* Dequeue ERST Segment Index (DESI) - Segment number (or alias)
 * where the current dequeue poपूर्णांकer lies.  This is an optional HW hपूर्णांक.
 */
#घोषणा ERST_DESI_MASK		(0x7)
/* Event Handler Busy (EHB) - is the event ring scheduled to be serviced by
 * a work queue (or delayed service routine)?
 */
#घोषणा ERST_EHB		(1 << 3)
#घोषणा ERST_PTR_MASK		(0xf)

/**
 * काष्ठा xhci_run_regs
 * @microframe_index:
 * 		MFINDEX - current microframe number
 *
 * Section 5.5 Host Controller Runसमय Registers:
 * "Software should पढ़ो and ग_लिखो these रेजिस्टरs using only Dword (32 bit)
 * or larger accesses"
 */
काष्ठा xhci_run_regs अणु
	__le32			microframe_index;
	__le32			rsvd[7];
	काष्ठा xhci_पूर्णांकr_reg	ir_set[128];
पूर्ण;

/**
 * काष्ठा करोorbell_array
 *
 * Bits  0 -  7: Endpoपूर्णांक target
 * Bits  8 - 15: RsvdZ
 * Bits 16 - 31: Stream ID
 *
 * Section 5.6
 */
काष्ठा xhci_करोorbell_array अणु
	__le32	करोorbell[256];
पूर्ण;

#घोषणा DB_VALUE(ep, stream)	((((ep) + 1) & 0xff) | ((stream) << 16))
#घोषणा DB_VALUE_HOST		0x00000000

/**
 * काष्ठा xhci_protocol_caps
 * @revision:		major revision, minor revision, capability ID,
 *			and next capability poपूर्णांकer.
 * @name_string:	Four ASCII अक्षरacters to say which spec this xHC
 *			follows, typically "USB ".
 * @port_info:		Port offset, count, and protocol-defined inक्रमmation.
 */
काष्ठा xhci_protocol_caps अणु
	u32	revision;
	u32	name_string;
	u32	port_info;
पूर्ण;

#घोषणा	XHCI_EXT_PORT_MAJOR(x)	(((x) >> 24) & 0xff)
#घोषणा	XHCI_EXT_PORT_MINOR(x)	(((x) >> 16) & 0xff)
#घोषणा	XHCI_EXT_PORT_PSIC(x)	(((x) >> 28) & 0x0f)
#घोषणा	XHCI_EXT_PORT_OFF(x)	((x) & 0xff)
#घोषणा	XHCI_EXT_PORT_COUNT(x)	(((x) >> 8) & 0xff)

#घोषणा	XHCI_EXT_PORT_PSIV(x)	(((x) >> 0) & 0x0f)
#घोषणा	XHCI_EXT_PORT_PSIE(x)	(((x) >> 4) & 0x03)
#घोषणा	XHCI_EXT_PORT_PLT(x)	(((x) >> 6) & 0x03)
#घोषणा	XHCI_EXT_PORT_PFD(x)	(((x) >> 8) & 0x01)
#घोषणा	XHCI_EXT_PORT_LP(x)	(((x) >> 14) & 0x03)
#घोषणा	XHCI_EXT_PORT_PSIM(x)	(((x) >> 16) & 0xffff)

#घोषणा PLT_MASK        (0x03 << 6)
#घोषणा PLT_SYM         (0x00 << 6)
#घोषणा PLT_ASYM_RX     (0x02 << 6)
#घोषणा PLT_ASYM_TX     (0x03 << 6)

/**
 * काष्ठा xhci_container_ctx
 * @type: Type of context.  Used to calculated offsets to contained contexts.
 * @size: Size of the context data
 * @bytes: The raw context data given to HW
 * @dma: dma address of the bytes
 *
 * Represents either a Device or Input context.  Holds a poपूर्णांकer to the raw
 * memory used क्रम the context (bytes) and dma address of it (dma).
 */
काष्ठा xhci_container_ctx अणु
	अचिन्हित type;
#घोषणा XHCI_CTX_TYPE_DEVICE  0x1
#घोषणा XHCI_CTX_TYPE_INPUT   0x2

	पूर्णांक size;

	u8 *bytes;
	dma_addr_t dma;
पूर्ण;

/**
 * काष्ठा xhci_slot_ctx
 * @dev_info:	Route string, device speed, hub info, and last valid endpoपूर्णांक
 * @dev_info2:	Max निकास latency क्रम device number, root hub port number
 * @tt_info:	tt_info is used to स्थिरruct split transaction tokens
 * @dev_state:	slot state and device address
 *
 * Slot Context - section 6.2.1.1.  This assumes the HC uses 32-byte context
 * काष्ठाures.  If the HC uses 64-byte contexts, there is an additional 32 bytes
 * reserved at the end of the slot context क्रम HC पूर्णांकernal use.
 */
काष्ठा xhci_slot_ctx अणु
	__le32	dev_info;
	__le32	dev_info2;
	__le32	tt_info;
	__le32	dev_state;
	/* offset 0x10 to 0x1f reserved क्रम HC पूर्णांकernal use */
	__le32	reserved[4];
पूर्ण;

/* dev_info biपंचांगasks */
/* Route String - 0:19 */
#घोषणा ROUTE_STRING_MASK	(0xfffff)
/* Device speed - values defined by PORTSC Device Speed field - 20:23 */
#घोषणा DEV_SPEED	(0xf << 20)
#घोषणा GET_DEV_SPEED(n) (((n) & DEV_SPEED) >> 20)
/* bit 24 reserved */
/* Is this LS/FS device connected through a HS hub? - bit 25 */
#घोषणा DEV_MTT		(0x1 << 25)
/* Set अगर the device is a hub - bit 26 */
#घोषणा DEV_HUB		(0x1 << 26)
/* Index of the last valid endpoपूर्णांक context in this device context - 27:31 */
#घोषणा LAST_CTX_MASK	(0x1f << 27)
#घोषणा LAST_CTX(p)	((p) << 27)
#घोषणा LAST_CTX_TO_EP_NUM(p)	(((p) >> 27) - 1)
#घोषणा SLOT_FLAG	(1 << 0)
#घोषणा EP0_FLAG	(1 << 1)

/* dev_info2 biपंचांगasks */
/* Max Exit Latency (ms) - worst हाल समय to wake up all links in dev path */
#घोषणा MAX_EXIT	(0xffff)
/* Root hub port number that is needed to access the USB device */
#घोषणा ROOT_HUB_PORT(p)	(((p) & 0xff) << 16)
#घोषणा DEVINFO_TO_ROOT_HUB_PORT(p)	(((p) >> 16) & 0xff)
/* Maximum number of ports under a hub device */
#घोषणा XHCI_MAX_PORTS(p)	(((p) & 0xff) << 24)
#घोषणा DEVINFO_TO_MAX_PORTS(p)	(((p) & (0xff << 24)) >> 24)

/* tt_info biपंचांगasks */
/*
 * TT Hub Slot ID - क्रम low or full speed devices attached to a high-speed hub
 * The Slot ID of the hub that isolates the high speed संकेतing from
 * this low or full-speed device.  '0' अगर attached to root hub port.
 */
#घोषणा TT_SLOT		(0xff)
/*
 * The number of the करोwnstream facing port of the high-speed hub
 * '0' अगर the device is not low or full speed.
 */
#घोषणा TT_PORT		(0xff << 8)
#घोषणा TT_THINK_TIME(p)	(((p) & 0x3) << 16)
#घोषणा GET_TT_THINK_TIME(p)	(((p) & (0x3 << 16)) >> 16)

/* dev_state biपंचांगasks */
/* USB device address - asचिन्हित by the HC */
#घोषणा DEV_ADDR_MASK	(0xff)
/* bits 8:26 reserved */
/* Slot state */
#घोषणा SLOT_STATE	(0x1f << 27)
#घोषणा GET_SLOT_STATE(p)	(((p) & (0x1f << 27)) >> 27)

#घोषणा SLOT_STATE_DISABLED	0
#घोषणा SLOT_STATE_ENABLED	SLOT_STATE_DISABLED
#घोषणा SLOT_STATE_DEFAULT	1
#घोषणा SLOT_STATE_ADDRESSED	2
#घोषणा SLOT_STATE_CONFIGURED	3

/**
 * काष्ठा xhci_ep_ctx
 * @ep_info:	endpoपूर्णांक state, streams, mult, and पूर्णांकerval inक्रमmation.
 * @ep_info2:	inक्रमmation on endpoपूर्णांक type, max packet size, max burst size,
 * 		error count, and whether the HC will क्रमce an event क्रम all
 * 		transactions.
 * @deq:	64-bit ring dequeue poपूर्णांकer address.  If the endpoपूर्णांक only
 * 		defines one stream, this poपूर्णांकs to the endpoपूर्णांक transfer ring.
 * 		Otherwise, it poपूर्णांकs to a stream context array, which has a
 * 		ring poपूर्णांकer क्रम each flow.
 * @tx_info:
 * 		Average TRB lengths क्रम the endpoपूर्णांक ring and
 * 		max payload within an Endpoपूर्णांक Service Interval Time (ESIT).
 *
 * Endpoपूर्णांक Context - section 6.2.1.2.  This assumes the HC uses 32-byte context
 * काष्ठाures.  If the HC uses 64-byte contexts, there is an additional 32 bytes
 * reserved at the end of the endpoपूर्णांक context क्रम HC पूर्णांकernal use.
 */
काष्ठा xhci_ep_ctx अणु
	__le32	ep_info;
	__le32	ep_info2;
	__le64	deq;
	__le32	tx_info;
	/* offset 0x14 - 0x1f reserved क्रम HC पूर्णांकernal use */
	__le32	reserved[3];
पूर्ण;

/* ep_info biपंचांगasks */
/*
 * Endpoपूर्णांक State - bits 0:2
 * 0 - disabled
 * 1 - running
 * 2 - halted due to halt condition - ok to manipulate endpoपूर्णांक ring
 * 3 - stopped
 * 4 - TRB error
 * 5-7 - reserved
 */
#घोषणा EP_STATE_MASK		(0x7)
#घोषणा EP_STATE_DISABLED	0
#घोषणा EP_STATE_RUNNING	1
#घोषणा EP_STATE_HALTED		2
#घोषणा EP_STATE_STOPPED	3
#घोषणा EP_STATE_ERROR		4
#घोषणा GET_EP_CTX_STATE(ctx)	(le32_to_cpu((ctx)->ep_info) & EP_STATE_MASK)

/* Mult - Max number of burtst within an पूर्णांकerval, in EP companion desc. */
#घोषणा EP_MULT(p)		(((p) & 0x3) << 8)
#घोषणा CTX_TO_EP_MULT(p)	(((p) >> 8) & 0x3)
/* bits 10:14 are Max Primary Streams */
/* bit 15 is Linear Stream Array */
/* Interval - period between requests to an endpoपूर्णांक - 125u increments. */
#घोषणा EP_INTERVAL(p)			(((p) & 0xff) << 16)
#घोषणा EP_INTERVAL_TO_UFRAMES(p)	(1 << (((p) >> 16) & 0xff))
#घोषणा CTX_TO_EP_INTERVAL(p)		(((p) >> 16) & 0xff)
#घोषणा EP_MAXPSTREAMS_MASK		(0x1f << 10)
#घोषणा EP_MAXPSTREAMS(p)		(((p) << 10) & EP_MAXPSTREAMS_MASK)
#घोषणा CTX_TO_EP_MAXPSTREAMS(p)	(((p) & EP_MAXPSTREAMS_MASK) >> 10)
/* Endpoपूर्णांक is set up with a Linear Stream Array (vs. Secondary Stream Array) */
#घोषणा	EP_HAS_LSA		(1 << 15)
/* hosts with LEC=1 use bits 31:24 as ESIT high bits. */
#घोषणा CTX_TO_MAX_ESIT_PAYLOAD_HI(p)	(((p) >> 24) & 0xff)

/* ep_info2 biपंचांगasks */
/*
 * Force Event - generate transfer events क्रम all TRBs क्रम this endpoपूर्णांक
 * This will tell the HC to ignore the IOC and ISP flags (क्रम debugging only).
 */
#घोषणा	FORCE_EVENT	(0x1)
#घोषणा ERROR_COUNT(p)	(((p) & 0x3) << 1)
#घोषणा CTX_TO_EP_TYPE(p)	(((p) >> 3) & 0x7)
#घोषणा EP_TYPE(p)	((p) << 3)
#घोषणा ISOC_OUT_EP	1
#घोषणा BULK_OUT_EP	2
#घोषणा INT_OUT_EP	3
#घोषणा CTRL_EP		4
#घोषणा ISOC_IN_EP	5
#घोषणा BULK_IN_EP	6
#घोषणा INT_IN_EP	7
/* bit 6 reserved */
/* bit 7 is Host Initiate Disable - क्रम disabling stream selection */
#घोषणा MAX_BURST(p)	(((p)&0xff) << 8)
#घोषणा CTX_TO_MAX_BURST(p)	(((p) >> 8) & 0xff)
#घोषणा MAX_PACKET(p)	(((p)&0xffff) << 16)
#घोषणा MAX_PACKET_MASK		(0xffff << 16)
#घोषणा MAX_PACKET_DECODED(p)	(((p) >> 16) & 0xffff)

/* tx_info biपंचांगasks */
#घोषणा EP_AVG_TRB_LENGTH(p)		((p) & 0xffff)
#घोषणा EP_MAX_ESIT_PAYLOAD_LO(p)	(((p) & 0xffff) << 16)
#घोषणा EP_MAX_ESIT_PAYLOAD_HI(p)	((((p) >> 16) & 0xff) << 24)
#घोषणा CTX_TO_MAX_ESIT_PAYLOAD(p)	(((p) >> 16) & 0xffff)

/* deq biपंचांगasks */
#घोषणा EP_CTX_CYCLE_MASK		(1 << 0)
#घोषणा SCTX_DEQ_MASK			(~0xfL)


/**
 * काष्ठा xhci_input_control_context
 * Input control context; see section 6.2.5.
 *
 * @drop_context:	set the bit of the endpoपूर्णांक context you want to disable
 * @add_context:	set the bit of the endpoपूर्णांक context you want to enable
 */
काष्ठा xhci_input_control_ctx अणु
	__le32	drop_flags;
	__le32	add_flags;
	__le32	rsvd2[6];
पूर्ण;

#घोषणा	EP_IS_ADDED(ctrl_ctx, i) \
	(le32_to_cpu(ctrl_ctx->add_flags) & (1 << (i + 1)))
#घोषणा	EP_IS_DROPPED(ctrl_ctx, i)       \
	(le32_to_cpu(ctrl_ctx->drop_flags) & (1 << (i + 1)))

/* Represents everything that is needed to issue a command on the command ring.
 * It's useful to pre-allocate these क्रम commands that cannot fail due to
 * out-of-memory errors, like मुक्तing streams.
 */
काष्ठा xhci_command अणु
	/* Input context क्रम changing device state */
	काष्ठा xhci_container_ctx	*in_ctx;
	u32				status;
	पूर्णांक				slot_id;
	/* If completion is null, no one is रुकोing on this command
	 * and the काष्ठाure can be मुक्तd after the command completes.
	 */
	काष्ठा completion		*completion;
	जोड़ xhci_trb			*command_trb;
	काष्ठा list_head		cmd_list;
पूर्ण;

/* drop context biपंचांगasks */
#घोषणा	DROP_EP(x)	(0x1 << x)
/* add context biपंचांगasks */
#घोषणा	ADD_EP(x)	(0x1 << x)

काष्ठा xhci_stream_ctx अणु
	/* 64-bit stream ring address, cycle state, and stream type */
	__le64	stream_ring;
	/* offset 0x14 - 0x1f reserved क्रम HC पूर्णांकernal use */
	__le32	reserved[2];
पूर्ण;

/* Stream Context Types (section 6.4.1) - bits 3:1 of stream ctx deq ptr */
#घोषणा	SCT_FOR_CTX(p)		(((p) & 0x7) << 1)
/* Secondary stream array type, dequeue poपूर्णांकer is to a transfer ring */
#घोषणा	SCT_SEC_TR		0
/* Primary stream array type, dequeue poपूर्णांकer is to a transfer ring */
#घोषणा	SCT_PRI_TR		1
/* Dequeue poपूर्णांकer is क्रम a secondary stream array (SSA) with 8 entries */
#घोषणा SCT_SSA_8		2
#घोषणा SCT_SSA_16		3
#घोषणा SCT_SSA_32		4
#घोषणा SCT_SSA_64		5
#घोषणा SCT_SSA_128		6
#घोषणा SCT_SSA_256		7

/* Assume no secondary streams क्रम now */
काष्ठा xhci_stream_info अणु
	काष्ठा xhci_ring		**stream_rings;
	/* Number of streams, including stream 0 (which drivers can't use) */
	अचिन्हित पूर्णांक			num_streams;
	/* The stream context array may be bigger than
	 * the number of streams the driver asked क्रम
	 */
	काष्ठा xhci_stream_ctx		*stream_ctx_array;
	अचिन्हित पूर्णांक			num_stream_ctxs;
	dma_addr_t			ctx_array_dma;
	/* For mapping physical TRB addresses to segments in stream rings */
	काष्ठा radix_tree_root		trb_address_map;
	काष्ठा xhci_command		*मुक्त_streams_command;
पूर्ण;

#घोषणा	SMALL_STREAM_ARRAY_SIZE		256
#घोषणा	MEDIUM_STREAM_ARRAY_SIZE	1024

/* Some Intel xHCI host controllers need software to keep track of the bus
 * bandwidth.  Keep track of endpoपूर्णांक info here.  Each root port is allocated
 * the full bus bandwidth.  We must also treat TTs (including each port under a
 * multi-TT hub) as a separate bandwidth करोमुख्य.  The direct memory पूर्णांकerface
 * (DMI) also limits the total bandwidth (across all करोमुख्यs) that can be used.
 */
काष्ठा xhci_bw_info अणु
	/* ep_पूर्णांकerval is zero-based */
	अचिन्हित पूर्णांक		ep_पूर्णांकerval;
	/* mult and num_packets are one-based */
	अचिन्हित पूर्णांक		mult;
	अचिन्हित पूर्णांक		num_packets;
	अचिन्हित पूर्णांक		max_packet_size;
	अचिन्हित पूर्णांक		max_esit_payload;
	अचिन्हित पूर्णांक		type;
पूर्ण;

/* "Block" sizes in bytes the hardware uses क्रम dअगरferent device speeds.
 * The logic in this part of the hardware limits the number of bits the hardware
 * can use, so must represent bandwidth in a less precise manner to mimic what
 * the scheduler hardware computes.
 */
#घोषणा	FS_BLOCK	1
#घोषणा	HS_BLOCK	4
#घोषणा	SS_BLOCK	16
#घोषणा	DMI_BLOCK	32

/* Each device speed has a protocol overhead (CRC, bit stuffing, etc) associated
 * with each byte transferred.  SuperSpeed devices have an initial overhead to
 * set up bursts.  These are in blocks, see above.  LS overhead has alपढ़ोy been
 * translated पूर्णांकo FS blocks.
 */
#घोषणा DMI_OVERHEAD 8
#घोषणा DMI_OVERHEAD_BURST 4
#घोषणा SS_OVERHEAD 8
#घोषणा SS_OVERHEAD_BURST 32
#घोषणा HS_OVERHEAD 26
#घोषणा FS_OVERHEAD 20
#घोषणा LS_OVERHEAD 128
/* The TTs need to claim roughly twice as much bandwidth (94 bytes per
 * microframe ~= 24Mbps) of the HS bus as the devices can actually use because
 * of overhead associated with split transfers crossing microframe boundaries.
 * 31 blocks is pure protocol overhead.
 */
#घोषणा TT_HS_OVERHEAD (31 + 94)
#घोषणा TT_DMI_OVERHEAD (25 + 12)

/* Bandwidth limits in blocks */
#घोषणा FS_BW_LIMIT		1285
#घोषणा TT_BW_LIMIT		1320
#घोषणा HS_BW_LIMIT		1607
#घोषणा SS_BW_LIMIT_IN		3906
#घोषणा DMI_BW_LIMIT_IN		3906
#घोषणा SS_BW_LIMIT_OUT		3906
#घोषणा DMI_BW_LIMIT_OUT	3906

/* Percentage of bus bandwidth reserved क्रम non-periodic transfers */
#घोषणा FS_BW_RESERVED		10
#घोषणा HS_BW_RESERVED		20
#घोषणा SS_BW_RESERVED		10

काष्ठा xhci_virt_ep अणु
	काष्ठा xhci_virt_device		*vdev;	/* parent */
	अचिन्हित पूर्णांक			ep_index;
	काष्ठा xhci_ring		*ring;
	/* Related to endpoपूर्णांकs that are configured to use stream IDs only */
	काष्ठा xhci_stream_info		*stream_info;
	/* Temporary storage in हाल the configure endpoपूर्णांक command fails and we
	 * have to restore the device state to the previous state
	 */
	काष्ठा xhci_ring		*new_ring;
	अचिन्हित पूर्णांक			ep_state;
#घोषणा SET_DEQ_PENDING		(1 << 0)
#घोषणा EP_HALTED		(1 << 1)	/* For stall handling */
#घोषणा EP_STOP_CMD_PENDING	(1 << 2)	/* For URB cancellation */
/* Transitioning the endpoपूर्णांक to using streams, करोn't enqueue URBs */
#घोषणा EP_GETTING_STREAMS	(1 << 3)
#घोषणा EP_HAS_STREAMS		(1 << 4)
/* Transitioning the endpoपूर्णांक to not using streams, करोn't enqueue URBs */
#घोषणा EP_GETTING_NO_STREAMS	(1 << 5)
#घोषणा EP_HARD_CLEAR_TOGGLE	(1 << 6)
#घोषणा EP_SOFT_CLEAR_TOGGLE	(1 << 7)
/* usb_hub_clear_tt_buffer is in progress */
#घोषणा EP_CLEARING_TT		(1 << 8)
	/* ----  Related to URB cancellation ---- */
	काष्ठा list_head	cancelled_td_list;
	/* Watchकरोg समयr क्रम stop endpoपूर्णांक command to cancel URBs */
	काष्ठा समयr_list	stop_cmd_समयr;
	काष्ठा xhci_hcd		*xhci;
	/* Dequeue poपूर्णांकer and dequeue segment क्रम a submitted Set TR Dequeue
	 * command.  We'll need to update the ring's dequeue segment and dequeue
	 * poपूर्णांकer after the command completes.
	 */
	काष्ठा xhci_segment	*queued_deq_seg;
	जोड़ xhci_trb		*queued_deq_ptr;
	/*
	 * Someबार the xHC can not process isochronous endpoपूर्णांक ring quickly
	 * enough, and it will miss some isoc tds on the ring and generate
	 * a Missed Service Error Event.
	 * Set skip flag when receive a Missed Service Error Event and
	 * process the missed tds on the endpoपूर्णांक ring.
	 */
	bool			skip;
	/* Bandwidth checking storage */
	काष्ठा xhci_bw_info	bw_info;
	काष्ठा list_head	bw_endpoपूर्णांक_list;
	/* Isoch Frame ID checking storage */
	पूर्णांक			next_frame_id;
	/* Use new Isoch TRB layout needed क्रम extended TBC support */
	bool			use_extended_tbc;
पूर्ण;

क्रमागत xhci_overhead_type अणु
	LS_OVERHEAD_TYPE = 0,
	FS_OVERHEAD_TYPE,
	HS_OVERHEAD_TYPE,
पूर्ण;

काष्ठा xhci_पूर्णांकerval_bw अणु
	अचिन्हित पूर्णांक		num_packets;
	/* Sorted by max packet size.
	 * Head of the list is the greatest max packet size.
	 */
	काष्ठा list_head	endpoपूर्णांकs;
	/* How many endpoपूर्णांकs of each speed are present. */
	अचिन्हित पूर्णांक		overhead[3];
पूर्ण;

#घोषणा	XHCI_MAX_INTERVAL	16

काष्ठा xhci_पूर्णांकerval_bw_table अणु
	अचिन्हित पूर्णांक		पूर्णांकerval0_esit_payload;
	काष्ठा xhci_पूर्णांकerval_bw	पूर्णांकerval_bw[XHCI_MAX_INTERVAL];
	/* Includes reserved bandwidth क्रम async endpoपूर्णांकs */
	अचिन्हित पूर्णांक		bw_used;
	अचिन्हित पूर्णांक		ss_bw_in;
	अचिन्हित पूर्णांक		ss_bw_out;
पूर्ण;

#घोषणा EP_CTX_PER_DEV		31

काष्ठा xhci_virt_device अणु
	पूर्णांक				slot_id;
	काष्ठा usb_device		*udev;
	/*
	 * Commands to the hardware are passed an "input context" that
	 * tells the hardware what to change in its data काष्ठाures.
	 * The hardware will वापस changes in an "output context" that
	 * software must allocate क्रम the hardware.  We need to keep
	 * track of input and output contexts separately because
	 * these commands might fail and we करोn't trust the hardware.
	 */
	काष्ठा xhci_container_ctx       *out_ctx;
	/* Used क्रम addressing devices and configuration changes */
	काष्ठा xhci_container_ctx       *in_ctx;
	काष्ठा xhci_virt_ep		eps[EP_CTX_PER_DEV];
	u8				fake_port;
	u8				real_port;
	काष्ठा xhci_पूर्णांकerval_bw_table	*bw_table;
	काष्ठा xhci_tt_bw_info		*tt_info;
	/*
	 * flags क्रम state tracking based on events and issued commands.
	 * Software can not rely on states from output contexts because of
	 * latency between events and xHC updating output context values.
	 * See xhci 1.1 section 4.8.3 क्रम more details
	 */
	अचिन्हित दीर्घ			flags;
#घोषणा VDEV_PORT_ERROR			BIT(0) /* Port error, link inactive */

	/* The current max निकास latency क्रम the enabled USB3 link states. */
	u16				current_mel;
	/* Used क्रम the debugfs पूर्णांकerfaces. */
	व्योम				*debugfs_निजी;
पूर्ण;

/*
 * For each roothub, keep track of the bandwidth inक्रमmation क्रम each periodic
 * पूर्णांकerval.
 *
 * If a high speed hub is attached to the roothub, each TT associated with that
 * hub is a separate bandwidth करोमुख्य.  The पूर्णांकerval inक्रमmation क्रम the
 * endpoपूर्णांकs on the devices under that TT will appear in the TT काष्ठाure.
 */
काष्ठा xhci_root_port_bw_info अणु
	काष्ठा list_head		tts;
	अचिन्हित पूर्णांक			num_active_tts;
	काष्ठा xhci_पूर्णांकerval_bw_table	bw_table;
पूर्ण;

काष्ठा xhci_tt_bw_info अणु
	काष्ठा list_head		tt_list;
	पूर्णांक				slot_id;
	पूर्णांक				ttport;
	काष्ठा xhci_पूर्णांकerval_bw_table	bw_table;
	पूर्णांक				active_eps;
पूर्ण;


/**
 * काष्ठा xhci_device_context_array
 * @dev_context_ptr	array of 64-bit DMA addresses क्रम device contexts
 */
काष्ठा xhci_device_context_array अणु
	/* 64-bit device addresses; we only ग_लिखो 32-bit addresses */
	__le64			dev_context_ptrs[MAX_HC_SLOTS];
	/* निजी xHCD poपूर्णांकers */
	dma_addr_t	dma;
पूर्ण;
/* TODO: ग_लिखो function to set the 64-bit device DMA address */
/*
 * TODO: change this to be dynamically sized at HC mem init समय since the HC
 * might not be able to handle the maximum number of devices possible.
 */


काष्ठा xhci_transfer_event अणु
	/* 64-bit buffer address, or immediate data */
	__le64	buffer;
	__le32	transfer_len;
	/* This field is पूर्णांकerpreted dअगरferently based on the type of TRB */
	__le32	flags;
पूर्ण;

/* Transfer event TRB length bit mask */
/* bits 0:23 */
#घोषणा	EVENT_TRB_LEN(p)		((p) & 0xffffff)

/** Transfer Event bit fields **/
#घोषणा	TRB_TO_EP_ID(p)	(((p) >> 16) & 0x1f)

/* Completion Code - only applicable क्रम some types of TRBs */
#घोषणा	COMP_CODE_MASK		(0xff << 24)
#घोषणा GET_COMP_CODE(p)	(((p) & COMP_CODE_MASK) >> 24)
#घोषणा COMP_INVALID				0
#घोषणा COMP_SUCCESS				1
#घोषणा COMP_DATA_BUFFER_ERROR			2
#घोषणा COMP_BABBLE_DETECTED_ERROR		3
#घोषणा COMP_USB_TRANSACTION_ERROR		4
#घोषणा COMP_TRB_ERROR				5
#घोषणा COMP_STALL_ERROR			6
#घोषणा COMP_RESOURCE_ERROR			7
#घोषणा COMP_BANDWIDTH_ERROR			8
#घोषणा COMP_NO_SLOTS_AVAILABLE_ERROR		9
#घोषणा COMP_INVALID_STREAM_TYPE_ERROR		10
#घोषणा COMP_SLOT_NOT_ENABLED_ERROR		11
#घोषणा COMP_ENDPOINT_NOT_ENABLED_ERROR		12
#घोषणा COMP_SHORT_PACKET			13
#घोषणा COMP_RING_UNDERRUN			14
#घोषणा COMP_RING_OVERRUN			15
#घोषणा COMP_VF_EVENT_RING_FULL_ERROR		16
#घोषणा COMP_PARAMETER_ERROR			17
#घोषणा COMP_BANDWIDTH_OVERRUN_ERROR		18
#घोषणा COMP_CONTEXT_STATE_ERROR		19
#घोषणा COMP_NO_PING_RESPONSE_ERROR		20
#घोषणा COMP_EVENT_RING_FULL_ERROR		21
#घोषणा COMP_INCOMPATIBLE_DEVICE_ERROR		22
#घोषणा COMP_MISSED_SERVICE_ERROR		23
#घोषणा COMP_COMMAND_RING_STOPPED		24
#घोषणा COMP_COMMAND_ABORTED			25
#घोषणा COMP_STOPPED				26
#घोषणा COMP_STOPPED_LENGTH_INVALID		27
#घोषणा COMP_STOPPED_SHORT_PACKET		28
#घोषणा COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR	29
#घोषणा COMP_ISOCH_BUFFER_OVERRUN		31
#घोषणा COMP_EVENT_LOST_ERROR			32
#घोषणा COMP_UNDEFINED_ERROR			33
#घोषणा COMP_INVALID_STREAM_ID_ERROR		34
#घोषणा COMP_SECONDARY_BANDWIDTH_ERROR		35
#घोषणा COMP_SPLIT_TRANSACTION_ERROR		36

अटल अंतरभूत स्थिर अक्षर *xhci_trb_comp_code_string(u8 status)
अणु
	चयन (status) अणु
	हाल COMP_INVALID:
		वापस "Invalid";
	हाल COMP_SUCCESS:
		वापस "Success";
	हाल COMP_DATA_BUFFER_ERROR:
		वापस "Data Buffer Error";
	हाल COMP_BABBLE_DETECTED_ERROR:
		वापस "Babble Detected";
	हाल COMP_USB_TRANSACTION_ERROR:
		वापस "USB Transaction Error";
	हाल COMP_TRB_ERROR:
		वापस "TRB Error";
	हाल COMP_STALL_ERROR:
		वापस "Stall Error";
	हाल COMP_RESOURCE_ERROR:
		वापस "Resource Error";
	हाल COMP_BANDWIDTH_ERROR:
		वापस "Bandwidth Error";
	हाल COMP_NO_SLOTS_AVAILABLE_ERROR:
		वापस "No Slots Available Error";
	हाल COMP_INVALID_STREAM_TYPE_ERROR:
		वापस "Invalid Stream Type Error";
	हाल COMP_SLOT_NOT_ENABLED_ERROR:
		वापस "Slot Not Enabled Error";
	हाल COMP_ENDPOINT_NOT_ENABLED_ERROR:
		वापस "Endpoint Not Enabled Error";
	हाल COMP_SHORT_PACKET:
		वापस "Short Packet";
	हाल COMP_RING_UNDERRUN:
		वापस "Ring Underrun";
	हाल COMP_RING_OVERRUN:
		वापस "Ring Overrun";
	हाल COMP_VF_EVENT_RING_FULL_ERROR:
		वापस "VF Event Ring Full Error";
	हाल COMP_PARAMETER_ERROR:
		वापस "Parameter Error";
	हाल COMP_BANDWIDTH_OVERRUN_ERROR:
		वापस "Bandwidth Overrun Error";
	हाल COMP_CONTEXT_STATE_ERROR:
		वापस "Context State Error";
	हाल COMP_NO_PING_RESPONSE_ERROR:
		वापस "No Ping Response Error";
	हाल COMP_EVENT_RING_FULL_ERROR:
		वापस "Event Ring Full Error";
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		वापस "Incompatible Device Error";
	हाल COMP_MISSED_SERVICE_ERROR:
		वापस "Missed Service Error";
	हाल COMP_COMMAND_RING_STOPPED:
		वापस "Command Ring Stopped";
	हाल COMP_COMMAND_ABORTED:
		वापस "Command Aborted";
	हाल COMP_STOPPED:
		वापस "Stopped";
	हाल COMP_STOPPED_LENGTH_INVALID:
		वापस "Stopped - Length Invalid";
	हाल COMP_STOPPED_SHORT_PACKET:
		वापस "Stopped - Short Packet";
	हाल COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:
		वापस "Max Exit Latency Too Large Error";
	हाल COMP_ISOCH_BUFFER_OVERRUN:
		वापस "Isoch Buffer Overrun";
	हाल COMP_EVENT_LOST_ERROR:
		वापस "Event Lost Error";
	हाल COMP_UNDEFINED_ERROR:
		वापस "Undefined Error";
	हाल COMP_INVALID_STREAM_ID_ERROR:
		वापस "Invalid Stream ID Error";
	हाल COMP_SECONDARY_BANDWIDTH_ERROR:
		वापस "Secondary Bandwidth Error";
	हाल COMP_SPLIT_TRANSACTION_ERROR:
		वापस "Split Transaction Error";
	शेष:
		वापस "Unknown!!";
	पूर्ण
पूर्ण

काष्ठा xhci_link_trb अणु
	/* 64-bit segment poपूर्णांकer*/
	__le64 segment_ptr;
	__le32 पूर्णांकr_target;
	__le32 control;
पूर्ण;

/* control bitfields */
#घोषणा LINK_TOGGLE	(0x1<<1)

/* Command completion event TRB */
काष्ठा xhci_event_cmd अणु
	/* Poपूर्णांकer to command TRB, or the value passed by the event data trb */
	__le64 cmd_trb;
	__le32 status;
	__le32 flags;
पूर्ण;

/* flags biपंचांगasks */

/* Address device - disable SetAddress */
#घोषणा TRB_BSR		(1<<9)

/* Configure Endpoपूर्णांक - Deconfigure */
#घोषणा TRB_DC		(1<<9)

/* Stop Ring - Transfer State Preserve */
#घोषणा TRB_TSP		(1<<9)

क्रमागत xhci_ep_reset_type अणु
	EP_HARD_RESET,
	EP_SOFT_RESET,
पूर्ण;

/* Force Event */
#घोषणा TRB_TO_VF_INTR_TARGET(p)	(((p) & (0x3ff << 22)) >> 22)
#घोषणा TRB_TO_VF_ID(p)			(((p) & (0xff << 16)) >> 16)

/* Set Latency Tolerance Value */
#घोषणा TRB_TO_BELT(p)			(((p) & (0xfff << 16)) >> 16)

/* Get Port Bandwidth */
#घोषणा TRB_TO_DEV_SPEED(p)		(((p) & (0xf << 16)) >> 16)

/* Force Header */
#घोषणा TRB_TO_PACKET_TYPE(p)		((p) & 0x1f)
#घोषणा TRB_TO_ROOTHUB_PORT(p)		(((p) & (0xff << 24)) >> 24)

क्रमागत xhci_setup_dev अणु
	SETUP_CONTEXT_ONLY,
	SETUP_CONTEXT_ADDRESS,
पूर्ण;

/* bits 16:23 are the भव function ID */
/* bits 24:31 are the slot ID */
#घोषणा TRB_TO_SLOT_ID(p)	(((p) & (0xff<<24)) >> 24)
#घोषणा SLOT_ID_FOR_TRB(p)	(((p) & 0xff) << 24)

/* Stop Endpoपूर्णांक TRB - ep_index to endpoपूर्णांक ID क्रम this TRB */
#घोषणा TRB_TO_EP_INDEX(p)		((((p) & (0x1f << 16)) >> 16) - 1)
#घोषणा	EP_ID_FOR_TRB(p)		((((p) + 1) & 0x1f) << 16)

#घोषणा SUSPEND_PORT_FOR_TRB(p)		(((p) & 1) << 23)
#घोषणा TRB_TO_SUSPEND_PORT(p)		(((p) & (1 << 23)) >> 23)
#घोषणा LAST_EP_INDEX			30

/* Set TR Dequeue Poपूर्णांकer command TRB fields, 6.4.3.9 */
#घोषणा TRB_TO_STREAM_ID(p)		((((p) & (0xffff << 16)) >> 16))
#घोषणा STREAM_ID_FOR_TRB(p)		((((p)) & 0xffff) << 16)
#घोषणा SCT_FOR_TRB(p)			(((p) << 1) & 0x7)

/* Link TRB specअगरic fields */
#घोषणा TRB_TC			(1<<1)

/* Port Status Change Event TRB fields */
/* Port ID - bits 31:24 */
#घोषणा GET_PORT_ID(p)		(((p) & (0xff << 24)) >> 24)

#घोषणा EVENT_DATA		(1 << 2)

/* Normal TRB fields */
/* transfer_len biपंचांगasks - bits 0:16 */
#घोषणा	TRB_LEN(p)		((p) & 0x1ffff)
/* TD Size, packets reमुख्यing in this TD, bits 21:17 (5 bits, so max 31) */
#घोषणा TRB_TD_SIZE(p)          (min((p), (u32)31) << 17)
#घोषणा GET_TD_SIZE(p)		(((p) & 0x3e0000) >> 17)
/* xhci 1.1 uses the TD_SIZE field क्रम TBC अगर Extended TBC is enabled (ETE) */
#घोषणा TRB_TD_SIZE_TBC(p)      (min((p), (u32)31) << 17)
/* Interrupter Target - which MSI-X vector to target the completion event at */
#घोषणा TRB_INTR_TARGET(p)	(((p) & 0x3ff) << 22)
#घोषणा GET_INTR_TARGET(p)	(((p) >> 22) & 0x3ff)
/* Total burst count field, Rsvdz on xhci 1.1 with Extended TBC enabled (ETE) */
#घोषणा TRB_TBC(p)		(((p) & 0x3) << 7)
#घोषणा TRB_TLBPC(p)		(((p) & 0xf) << 16)

/* Cycle bit - indicates TRB ownership by HC or HCD */
#घोषणा TRB_CYCLE		(1<<0)
/*
 * Force next event data TRB to be evaluated beक्रमe task चयन.
 * Used to pass OS data back after a TD completes.
 */
#घोषणा TRB_ENT			(1<<1)
/* Interrupt on लघु packet */
#घोषणा TRB_ISP			(1<<2)
/* Set PCIe no snoop attribute */
#घोषणा TRB_NO_SNOOP		(1<<3)
/* Chain multiple TRBs पूर्णांकo a TD */
#घोषणा TRB_CHAIN		(1<<4)
/* Interrupt on completion */
#घोषणा TRB_IOC			(1<<5)
/* The buffer poपूर्णांकer contains immediate data */
#घोषणा TRB_IDT			(1<<6)
/* TDs smaller than this might use IDT */
#घोषणा TRB_IDT_MAX_SIZE	8

/* Block Event Interrupt */
#घोषणा	TRB_BEI			(1<<9)

/* Control transfer TRB specअगरic fields */
#घोषणा TRB_सूची_IN		(1<<16)
#घोषणा	TRB_TX_TYPE(p)		((p) << 16)
#घोषणा	TRB_DATA_OUT		2
#घोषणा	TRB_DATA_IN		3

/* Isochronous TRB specअगरic fields */
#घोषणा TRB_SIA			(1<<31)
#घोषणा TRB_FRAME_ID(p)		(((p) & 0x7ff) << 20)

/* TRB cache size क्रम xHC with TRB cache */
#घोषणा TRB_CACHE_SIZE_HS	8
#घोषणा TRB_CACHE_SIZE_SS	16

काष्ठा xhci_generic_trb अणु
	__le32 field[4];
पूर्ण;

जोड़ xhci_trb अणु
	काष्ठा xhci_link_trb		link;
	काष्ठा xhci_transfer_event	trans_event;
	काष्ठा xhci_event_cmd		event_cmd;
	काष्ठा xhci_generic_trb		generic;
पूर्ण;

/* TRB bit mask */
#घोषणा	TRB_TYPE_BITMASK	(0xfc00)
#घोषणा TRB_TYPE(p)		((p) << 10)
#घोषणा TRB_FIELD_TO_TYPE(p)	(((p) & TRB_TYPE_BITMASK) >> 10)
/* TRB type IDs */
/* bulk, पूर्णांकerrupt, isoc scatter/gather, and control data stage */
#घोषणा TRB_NORMAL		1
/* setup stage क्रम control transfers */
#घोषणा TRB_SETUP		2
/* data stage क्रम control transfers */
#घोषणा TRB_DATA		3
/* status stage क्रम control transfers */
#घोषणा TRB_STATUS		4
/* isoc transfers */
#घोषणा TRB_ISOC		5
/* TRB क्रम linking ring segments */
#घोषणा TRB_LINK		6
#घोषणा TRB_EVENT_DATA		7
/* Transfer Ring No-op (not क्रम the command ring) */
#घोषणा TRB_TR_NOOP		8
/* Command TRBs */
/* Enable Slot Command */
#घोषणा TRB_ENABLE_SLOT		9
/* Disable Slot Command */
#घोषणा TRB_DISABLE_SLOT	10
/* Address Device Command */
#घोषणा TRB_ADDR_DEV		11
/* Configure Endpoपूर्णांक Command */
#घोषणा TRB_CONFIG_EP		12
/* Evaluate Context Command */
#घोषणा TRB_EVAL_CONTEXT	13
/* Reset Endpoपूर्णांक Command */
#घोषणा TRB_RESET_EP		14
/* Stop Transfer Ring Command */
#घोषणा TRB_STOP_RING		15
/* Set Transfer Ring Dequeue Poपूर्णांकer Command */
#घोषणा TRB_SET_DEQ		16
/* Reset Device Command */
#घोषणा TRB_RESET_DEV		17
/* Force Event Command (opt) */
#घोषणा TRB_FORCE_EVENT		18
/* Negotiate Bandwidth Command (opt) */
#घोषणा TRB_NEG_BANDWIDTH	19
/* Set Latency Tolerance Value Command (opt) */
#घोषणा TRB_SET_LT		20
/* Get port bandwidth Command */
#घोषणा TRB_GET_BW		21
/* Force Header Command - generate a transaction or link management packet */
#घोषणा TRB_FORCE_HEADER	22
/* No-op Command - not क्रम transfer rings */
#घोषणा TRB_CMD_NOOP		23
/* TRB IDs 24-31 reserved */
/* Event TRBS */
/* Transfer Event */
#घोषणा TRB_TRANSFER		32
/* Command Completion Event */
#घोषणा TRB_COMPLETION		33
/* Port Status Change Event */
#घोषणा TRB_PORT_STATUS		34
/* Bandwidth Request Event (opt) */
#घोषणा TRB_BANDWIDTH_EVENT	35
/* Doorbell Event (opt) */
#घोषणा TRB_DOORBELL		36
/* Host Controller Event */
#घोषणा TRB_HC_EVENT		37
/* Device Notअगरication Event - device sent function wake notअगरication */
#घोषणा TRB_DEV_NOTE		38
/* MFINDEX Wrap Event - microframe counter wrapped */
#घोषणा TRB_MFINDEX_WRAP	39
/* TRB IDs 40-47 reserved, 48-63 is venकरोr-defined */
#घोषणा TRB_VENDOR_DEFINED_LOW	48
/* Nec venकरोr-specअगरic command completion event. */
#घोषणा	TRB_NEC_CMD_COMP	48
/* Get NEC firmware revision. */
#घोषणा	TRB_NEC_GET_FW		49

अटल अंतरभूत स्थिर अक्षर *xhci_trb_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल TRB_NORMAL:
		वापस "Normal";
	हाल TRB_SETUP:
		वापस "Setup Stage";
	हाल TRB_DATA:
		वापस "Data Stage";
	हाल TRB_STATUS:
		वापस "Status Stage";
	हाल TRB_ISOC:
		वापस "Isoch";
	हाल TRB_LINK:
		वापस "Link";
	हाल TRB_EVENT_DATA:
		वापस "Event Data";
	हाल TRB_TR_NOOP:
		वापस "No-Op";
	हाल TRB_ENABLE_SLOT:
		वापस "Enable Slot Command";
	हाल TRB_DISABLE_SLOT:
		वापस "Disable Slot Command";
	हाल TRB_ADDR_DEV:
		वापस "Address Device Command";
	हाल TRB_CONFIG_EP:
		वापस "Configure Endpoint Command";
	हाल TRB_EVAL_CONTEXT:
		वापस "Evaluate Context Command";
	हाल TRB_RESET_EP:
		वापस "Reset Endpoint Command";
	हाल TRB_STOP_RING:
		वापस "Stop Ring Command";
	हाल TRB_SET_DEQ:
		वापस "Set TR Dequeue Pointer Command";
	हाल TRB_RESET_DEV:
		वापस "Reset Device Command";
	हाल TRB_FORCE_EVENT:
		वापस "Force Event Command";
	हाल TRB_NEG_BANDWIDTH:
		वापस "Negotiate Bandwidth Command";
	हाल TRB_SET_LT:
		वापस "Set Latency Tolerance Value Command";
	हाल TRB_GET_BW:
		वापस "Get Port Bandwidth Command";
	हाल TRB_FORCE_HEADER:
		वापस "Force Header Command";
	हाल TRB_CMD_NOOP:
		वापस "No-Op Command";
	हाल TRB_TRANSFER:
		वापस "Transfer Event";
	हाल TRB_COMPLETION:
		वापस "Command Completion Event";
	हाल TRB_PORT_STATUS:
		वापस "Port Status Change Event";
	हाल TRB_BANDWIDTH_EVENT:
		वापस "Bandwidth Request Event";
	हाल TRB_DOORBELL:
		वापस "Doorbell Event";
	हाल TRB_HC_EVENT:
		वापस "Host Controller Event";
	हाल TRB_DEV_NOTE:
		वापस "Device Notification Event";
	हाल TRB_MFINDEX_WRAP:
		वापस "MFINDEX Wrap Event";
	हाल TRB_NEC_CMD_COMP:
		वापस "NEC Command Completion Event";
	हाल TRB_NEC_GET_FW:
		वापस "NET Get Firmware Revision Command";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

#घोषणा TRB_TYPE_LINK(x)	(((x) & TRB_TYPE_BITMASK) == TRB_TYPE(TRB_LINK))
/* Above, but क्रम __le32 types -- can aव्योम work by swapping स्थिरants: */
#घोषणा TRB_TYPE_LINK_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
				 cpu_to_le32(TRB_TYPE(TRB_LINK)))
#घोषणा TRB_TYPE_NOOP_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
				 cpu_to_le32(TRB_TYPE(TRB_TR_NOOP)))

#घोषणा NEC_FW_MINOR(p)		(((p) >> 0) & 0xff)
#घोषणा NEC_FW_MAJOR(p)		(((p) >> 8) & 0xff)

/*
 * TRBS_PER_SEGMENT must be a multiple of 4,
 * since the command ring is 64-byte aligned.
 * It must also be greater than 16.
 */
#घोषणा TRBS_PER_SEGMENT	256
/* Allow two commands + a link TRB, aदीर्घ with any reserved command TRBs */
#घोषणा MAX_RSVD_CMD_TRBS	(TRBS_PER_SEGMENT - 3)
#घोषणा TRB_SEGMENT_SIZE	(TRBS_PER_SEGMENT*16)
#घोषणा TRB_SEGMENT_SHIFT	(ilog2(TRB_SEGMENT_SIZE))
/* TRB buffer poपूर्णांकers can't cross 64KB boundaries */
#घोषणा TRB_MAX_BUFF_SHIFT		16
#घोषणा TRB_MAX_BUFF_SIZE	(1 << TRB_MAX_BUFF_SHIFT)
/* How much data is left beक्रमe the 64KB boundary? */
#घोषणा TRB_BUFF_LEN_UP_TO_BOUNDARY(addr)	(TRB_MAX_BUFF_SIZE - \
					(addr & (TRB_MAX_BUFF_SIZE - 1)))
#घोषणा MAX_SOFT_RETRY		3

काष्ठा xhci_segment अणु
	जोड़ xhci_trb		*trbs;
	/* निजी to HCD */
	काष्ठा xhci_segment	*next;
	dma_addr_t		dma;
	/* Max packet sized bounce buffer क्रम td-fragmant alignment */
	dma_addr_t		bounce_dma;
	व्योम			*bounce_buf;
	अचिन्हित पूर्णांक		bounce_offs;
	अचिन्हित पूर्णांक		bounce_len;
पूर्ण;

क्रमागत xhci_cancelled_td_status अणु
	TD_सूचीTY = 0,
	TD_HALTED,
	TD_CLEARING_CACHE,
	TD_CLEARED,
पूर्ण;

काष्ठा xhci_td अणु
	काष्ठा list_head	td_list;
	काष्ठा list_head	cancelled_td_list;
	पूर्णांक			status;
	क्रमागत xhci_cancelled_td_status	cancel_status;
	काष्ठा urb		*urb;
	काष्ठा xhci_segment	*start_seg;
	जोड़ xhci_trb		*first_trb;
	जोड़ xhci_trb		*last_trb;
	काष्ठा xhci_segment	*last_trb_seg;
	काष्ठा xhci_segment	*bounce_seg;
	/* actual_length of the URB has alपढ़ोy been set */
	bool			urb_length_set;
	अचिन्हित पूर्णांक		num_trbs;
पूर्ण;

/* xHCI command शेष समयout value */
#घोषणा XHCI_CMD_DEFAULT_TIMEOUT	(5 * HZ)

/* command descriptor */
काष्ठा xhci_cd अणु
	काष्ठा xhci_command	*command;
	जोड़ xhci_trb		*cmd_trb;
पूर्ण;

क्रमागत xhci_ring_type अणु
	TYPE_CTRL = 0,
	TYPE_ISOC,
	TYPE_BULK,
	TYPE_INTR,
	TYPE_STREAM,
	TYPE_COMMAND,
	TYPE_EVENT,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *xhci_ring_type_string(क्रमागत xhci_ring_type type)
अणु
	चयन (type) अणु
	हाल TYPE_CTRL:
		वापस "CTRL";
	हाल TYPE_ISOC:
		वापस "ISOC";
	हाल TYPE_BULK:
		वापस "BULK";
	हाल TYPE_INTR:
		वापस "INTR";
	हाल TYPE_STREAM:
		वापस "STREAM";
	हाल TYPE_COMMAND:
		वापस "CMD";
	हाल TYPE_EVENT:
		वापस "EVENT";
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

काष्ठा xhci_ring अणु
	काष्ठा xhci_segment	*first_seg;
	काष्ठा xhci_segment	*last_seg;
	जोड़  xhci_trb		*enqueue;
	काष्ठा xhci_segment	*enq_seg;
	जोड़  xhci_trb		*dequeue;
	काष्ठा xhci_segment	*deq_seg;
	काष्ठा list_head	td_list;
	/*
	 * Write the cycle state पूर्णांकo the TRB cycle field to give ownership of
	 * the TRB to the host controller (अगर we are the producer), or to check
	 * अगर we own the TRB (अगर we are the consumer).  See section 4.9.1.
	 */
	u32			cycle_state;
	अचिन्हित पूर्णांक            err_count;
	अचिन्हित पूर्णांक		stream_id;
	अचिन्हित पूर्णांक		num_segs;
	अचिन्हित पूर्णांक		num_trbs_मुक्त;
	अचिन्हित पूर्णांक		num_trbs_मुक्त_temp;
	अचिन्हित पूर्णांक		bounce_buf_len;
	क्रमागत xhci_ring_type	type;
	bool			last_td_was_लघु;
	काष्ठा radix_tree_root	*trb_address_map;
पूर्ण;

काष्ठा xhci_erst_entry अणु
	/* 64-bit event ring segment address */
	__le64	seg_addr;
	__le32	seg_size;
	/* Set to zero */
	__le32	rsvd;
पूर्ण;

काष्ठा xhci_erst अणु
	काष्ठा xhci_erst_entry	*entries;
	अचिन्हित पूर्णांक		num_entries;
	/* xhci->event_ring keeps track of segment dma addresses */
	dma_addr_t		erst_dma_addr;
	/* Num entries the ERST can contain */
	अचिन्हित पूर्णांक		erst_size;
पूर्ण;

काष्ठा xhci_scratchpad अणु
	u64 *sp_array;
	dma_addr_t sp_dma;
	व्योम **sp_buffers;
पूर्ण;

काष्ठा urb_priv अणु
	पूर्णांक	num_tds;
	पूर्णांक	num_tds_करोne;
	काष्ठा	xhci_td	td[];
पूर्ण;

/*
 * Each segment table entry is 4*32bits दीर्घ.  1K seems like an ok size:
 * (1K bytes * 8bytes/bit) / (4*32 bits) = 64 segment entries in the table,
 * meaning 64 ring segments.
 * Initial allocated size of the ERST, in number of entries */
#घोषणा	ERST_NUM_SEGS	1
/* Initial allocated size of the ERST, in number of entries */
#घोषणा	ERST_SIZE	64
/* Initial number of event segment rings allocated */
#घोषणा	ERST_ENTRIES	1
/* Poll every 60 seconds */
#घोषणा	POLL_TIMEOUT	60
/* Stop endpoपूर्णांक command समयout (secs) क्रम URB cancellation watchकरोg समयr */
#घोषणा XHCI_STOP_EP_CMD_TIMEOUT	5
/* XXX: Make these module parameters */

काष्ठा s3_save अणु
	u32	command;
	u32	dev_nt;
	u64	dcbaa_ptr;
	u32	config_reg;
	u32	irq_pending;
	u32	irq_control;
	u32	erst_size;
	u64	erst_base;
	u64	erst_dequeue;
पूर्ण;

/* Use क्रम lpm */
काष्ठा dev_info अणु
	u32			dev_id;
	काष्ठा	list_head	list;
पूर्ण;

काष्ठा xhci_bus_state अणु
	अचिन्हित दीर्घ		bus_suspended;
	अचिन्हित दीर्घ		next_statechange;

	/* Port suspend arrays are indexed by the portnum of the fake roothub */
	/* ports suspend status arrays - max 31 ports क्रम USB2, 15 क्रम USB3 */
	u32			port_c_suspend;
	u32			suspended_ports;
	u32			port_remote_wakeup;
	अचिन्हित दीर्घ		resume_करोne[USB_MAXCHILDREN];
	/* which ports have started to resume */
	अचिन्हित दीर्घ		resuming_ports;
	/* Which ports are रुकोing on RExit to U0 transition. */
	अचिन्हित दीर्घ		rनिकास_ports;
	काष्ठा completion	rनिकास_करोne[USB_MAXCHILDREN];
	काष्ठा completion	u3निकास_करोne[USB_MAXCHILDREN];
पूर्ण;


/*
 * It can take up to 20 ms to transition from RExit to U0 on the
 * Intel Lynx Poपूर्णांक LP xHCI host.
 */
#घोषणा	XHCI_MAX_REXIT_TIMEOUT_MS	20
काष्ठा xhci_port_cap अणु
	u32			*psi;	/* array of protocol speed ID entries */
	u8			psi_count;
	u8			psi_uid_count;
	u8			maj_rev;
	u8			min_rev;
पूर्ण;

काष्ठा xhci_port अणु
	__le32 __iomem		*addr;
	पूर्णांक			hw_portnum;
	पूर्णांक			hcd_portnum;
	काष्ठा xhci_hub		*rhub;
	काष्ठा xhci_port_cap	*port_cap;
पूर्ण;

काष्ठा xhci_hub अणु
	काष्ठा xhci_port	**ports;
	अचिन्हित पूर्णांक		num_ports;
	काष्ठा usb_hcd		*hcd;
	/* keep track of bus suspend info */
	काष्ठा xhci_bus_state   bus_state;
	/* supported prococol extended capabiliy values */
	u8			maj_rev;
	u8			min_rev;
पूर्ण;

/* There is one xhci_hcd काष्ठाure per controller */
काष्ठा xhci_hcd अणु
	काष्ठा usb_hcd *मुख्य_hcd;
	काष्ठा usb_hcd *shared_hcd;
	/* glue to PCI and HCD framework */
	काष्ठा xhci_cap_regs __iomem *cap_regs;
	काष्ठा xhci_op_regs __iomem *op_regs;
	काष्ठा xhci_run_regs __iomem *run_regs;
	काष्ठा xhci_करोorbell_array __iomem *dba;
	/* Our HCD's current पूर्णांकerrupter रेजिस्टर set */
	काष्ठा	xhci_पूर्णांकr_reg __iomem *ir_set;

	/* Cached रेजिस्टर copies of पढ़ो-only HC data */
	__u32		hcs_params1;
	__u32		hcs_params2;
	__u32		hcs_params3;
	__u32		hcc_params;
	__u32		hcc_params2;

	spinlock_t	lock;

	/* packed release number */
	u8		sbrn;
	u16		hci_version;
	u8		max_slots;
	u8		max_पूर्णांकerrupters;
	u8		max_ports;
	u8		isoc_threshold;
	/* imod_पूर्णांकerval in ns (I * 250ns) */
	u32		imod_पूर्णांकerval;
	पूर्णांक		event_ring_max;
	/* 4KB min, 128MB max */
	पूर्णांक		page_size;
	/* Valid values are 12 to 20, inclusive */
	पूर्णांक		page_shअगरt;
	/* msi-x vectors */
	पूर्णांक		msix_count;
	/* optional घड़ीs */
	काष्ठा clk		*clk;
	काष्ठा clk		*reg_clk;
	/* optional reset controller */
	काष्ठा reset_control *reset;
	/* data काष्ठाures */
	काष्ठा xhci_device_context_array *dcbaa;
	काष्ठा xhci_ring	*cmd_ring;
	अचिन्हित पूर्णांक            cmd_ring_state;
#घोषणा CMD_RING_STATE_RUNNING         (1 << 0)
#घोषणा CMD_RING_STATE_ABORTED         (1 << 1)
#घोषणा CMD_RING_STATE_STOPPED         (1 << 2)
	काष्ठा list_head        cmd_list;
	अचिन्हित पूर्णांक		cmd_ring_reserved_trbs;
	काष्ठा delayed_work	cmd_समयr;
	काष्ठा completion	cmd_ring_stop_completion;
	काष्ठा xhci_command	*current_cmd;
	काष्ठा xhci_ring	*event_ring;
	काष्ठा xhci_erst	erst;
	/* Scratchpad */
	काष्ठा xhci_scratchpad  *scratchpad;
	/* Store LPM test failed devices' inक्रमmation */
	काष्ठा list_head	lpm_failed_devs;

	/* slot enabling and address device helpers */
	/* these are not thपढ़ो safe so use mutex */
	काष्ठा mutex mutex;
	/* For USB 3.0 LPM enable/disable. */
	काष्ठा xhci_command		*lpm_command;
	/* Internal mirror of the HW's dcbaa */
	काष्ठा xhci_virt_device	*devs[MAX_HC_SLOTS];
	/* For keeping track of bandwidth करोमुख्यs per roothub. */
	काष्ठा xhci_root_port_bw_info	*rh_bw;

	/* DMA pools */
	काष्ठा dma_pool	*device_pool;
	काष्ठा dma_pool	*segment_pool;
	काष्ठा dma_pool	*small_streams_pool;
	काष्ठा dma_pool	*medium_streams_pool;

	/* Host controller watchकरोg समयr काष्ठाures */
	अचिन्हित पूर्णांक		xhc_state;

	u32			command;
	काष्ठा s3_save		s3;
/* Host controller is dying - not responding to commands. "I'm not dead yet!"
 *
 * xHC पूर्णांकerrupts have been disabled and a watchकरोg समयr will (or has alपढ़ोy)
 * halt the xHCI host, and complete all URBs with an -ESHUTDOWN code.  Any code
 * that sees this status (other than the समयr that set it) should stop touching
 * hardware immediately.  Interrupt handlers should वापस immediately when
 * they see this status (any समय they drop and re-acquire xhci->lock).
 * xhci_urb_dequeue() should call usb_hcd_check_unlink_urb() and वापस without
 * putting the TD on the canceled list, etc.
 *
 * There are no reports of xHCI host controllers that display this issue.
 */
#घोषणा XHCI_STATE_DYING	(1 << 0)
#घोषणा XHCI_STATE_HALTED	(1 << 1)
#घोषणा XHCI_STATE_REMOVING	(1 << 2)
	अचिन्हित दीर्घ दीर्घ	quirks;
#घोषणा	XHCI_LINK_TRB_QUIRK	BIT_ULL(0)
#घोषणा XHCI_RESET_EP_QUIRK	BIT_ULL(1)
#घोषणा XHCI_NEC_HOST		BIT_ULL(2)
#घोषणा XHCI_AMD_PLL_FIX	BIT_ULL(3)
#घोषणा XHCI_SPURIOUS_SUCCESS	BIT_ULL(4)
/*
 * Certain Intel host controllers have a limit to the number of endpoपूर्णांक
 * contexts they can handle.  Ideally, they would संकेत that they can't handle
 * anymore endpoपूर्णांक contexts by वापसing a Resource Error क्रम the Configure
 * Endpoपूर्णांक command, but they करोn't.  Instead they expect software to keep track
 * of the number of active endpoपूर्णांकs क्रम them, across configure endpoपूर्णांक
 * commands, reset device commands, disable slot commands, and address device
 * commands.
 */
#घोषणा XHCI_EP_LIMIT_QUIRK	BIT_ULL(5)
#घोषणा XHCI_BROKEN_MSI		BIT_ULL(6)
#घोषणा XHCI_RESET_ON_RESUME	BIT_ULL(7)
#घोषणा	XHCI_SW_BW_CHECKING	BIT_ULL(8)
#घोषणा XHCI_AMD_0x96_HOST	BIT_ULL(9)
#घोषणा XHCI_TRUST_TX_LENGTH	BIT_ULL(10)
#घोषणा XHCI_LPM_SUPPORT	BIT_ULL(11)
#घोषणा XHCI_INTEL_HOST		BIT_ULL(12)
#घोषणा XHCI_SPURIOUS_REBOOT	BIT_ULL(13)
#घोषणा XHCI_COMP_MODE_QUIRK	BIT_ULL(14)
#घोषणा XHCI_AVOID_BEI		BIT_ULL(15)
#घोषणा XHCI_PLAT		BIT_ULL(16)
#घोषणा XHCI_SLOW_SUSPEND	BIT_ULL(17)
#घोषणा XHCI_SPURIOUS_WAKEUP	BIT_ULL(18)
/* For controllers with a broken beyond repair streams implementation */
#घोषणा XHCI_BROKEN_STREAMS	BIT_ULL(19)
#घोषणा XHCI_PME_STUCK_QUIRK	BIT_ULL(20)
#घोषणा XHCI_MTK_HOST		BIT_ULL(21)
#घोषणा XHCI_SSIC_PORT_UNUSED	BIT_ULL(22)
#घोषणा XHCI_NO_64BIT_SUPPORT	BIT_ULL(23)
#घोषणा XHCI_MISSING_CAS	BIT_ULL(24)
/* For controller with a broken Port Disable implementation */
#घोषणा XHCI_BROKEN_PORT_PED	BIT_ULL(25)
#घोषणा XHCI_LIMIT_ENDPOINT_INTERVAL_7	BIT_ULL(26)
#घोषणा XHCI_U2_DISABLE_WAKE	BIT_ULL(27)
#घोषणा XHCI_ASMEDIA_MODIFY_FLOWCONTROL	BIT_ULL(28)
#घोषणा XHCI_HW_LPM_DISABLE	BIT_ULL(29)
#घोषणा XHCI_SUSPEND_DELAY	BIT_ULL(30)
#घोषणा XHCI_INTEL_USB_ROLE_SW	BIT_ULL(31)
#घोषणा XHCI_ZERO_64B_REGS	BIT_ULL(32)
#घोषणा XHCI_DEFAULT_PM_RUNTIME_ALLOW	BIT_ULL(33)
#घोषणा XHCI_RESET_PLL_ON_DISCONNECT	BIT_ULL(34)
#घोषणा XHCI_SNPS_BROKEN_SUSPEND    BIT_ULL(35)
#घोषणा XHCI_RENESAS_FW_QUIRK	BIT_ULL(36)
#घोषणा XHCI_SKIP_PHY_INIT	BIT_ULL(37)
#घोषणा XHCI_DISABLE_SPARSE	BIT_ULL(38)
#घोषणा XHCI_SG_TRB_CACHE_SIZE_QUIRK	BIT_ULL(39)
#घोषणा XHCI_NO_SOFT_RETRY	BIT_ULL(40)
#घोषणा XHCI_BROKEN_D3COLD	BIT_ULL(41)

	अचिन्हित पूर्णांक		num_active_eps;
	अचिन्हित पूर्णांक		limit_active_eps;
	काष्ठा xhci_port	*hw_ports;
	काष्ठा xhci_hub		usb2_rhub;
	काष्ठा xhci_hub		usb3_rhub;
	/* support xHCI 1.0 spec USB2 hardware LPM */
	अचिन्हित		hw_lpm_support:1;
	/* Broken Suspend flag क्रम SNPS Suspend resume issue */
	अचिन्हित		broken_suspend:1;
	/* cached usb2 extened protocol capabilites */
	u32                     *ext_caps;
	अचिन्हित पूर्णांक            num_ext_caps;
	/* cached extended protocol port capabilities */
	काष्ठा xhci_port_cap	*port_caps;
	अचिन्हित पूर्णांक		num_port_caps;
	/* Compliance Mode Recovery Data */
	काष्ठा समयr_list	comp_mode_recovery_समयr;
	u32			port_status_u0;
	u16			test_mode;
/* Compliance Mode Timer Triggered every 2 seconds */
#घोषणा COMP_MODE_RCVRY_MSECS 2000

	काष्ठा dentry		*debugfs_root;
	काष्ठा dentry		*debugfs_slots;
	काष्ठा list_head	regset_list;

	व्योम			*dbc;
	/* platक्रमm-specअगरic data -- must come last */
	अचिन्हित दीर्घ		priv[] __aligned(माप(s64));
पूर्ण;

/* Platक्रमm specअगरic overrides to generic XHCI hc_driver ops */
काष्ठा xhci_driver_overrides अणु
	माप_प्रकार extra_priv_size;
	पूर्णांक (*reset)(काष्ठा usb_hcd *hcd);
	पूर्णांक (*start)(काष्ठा usb_hcd *hcd);
	पूर्णांक (*add_endpoपूर्णांक)(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
			    काष्ठा usb_host_endpoपूर्णांक *ep);
	पूर्णांक (*drop_endpoपूर्णांक)(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
			     काष्ठा usb_host_endpoपूर्णांक *ep);
	पूर्णांक (*check_bandwidth)(काष्ठा usb_hcd *, काष्ठा usb_device *);
	व्योम (*reset_bandwidth)(काष्ठा usb_hcd *, काष्ठा usb_device *);
पूर्ण;

#घोषणा	XHCI_CFC_DELAY		10

/* convert between an HCD poपूर्णांकer and the corresponding EHCI_HCD */
अटल अंतरभूत काष्ठा xhci_hcd *hcd_to_xhci(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_hcd *primary_hcd;

	अगर (usb_hcd_is_primary_hcd(hcd))
		primary_hcd = hcd;
	अन्यथा
		primary_hcd = hcd->primary_hcd;

	वापस (काष्ठा xhci_hcd *) (primary_hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *xhci_to_hcd(काष्ठा xhci_hcd *xhci)
अणु
	वापस xhci->मुख्य_hcd;
पूर्ण

#घोषणा xhci_dbg(xhci, fmt, args...) \
	dev_dbg(xhci_to_hcd(xhci)->self.controller , fmt , ## args)
#घोषणा xhci_err(xhci, fmt, args...) \
	dev_err(xhci_to_hcd(xhci)->self.controller , fmt , ## args)
#घोषणा xhci_warn(xhci, fmt, args...) \
	dev_warn(xhci_to_hcd(xhci)->self.controller , fmt , ## args)
#घोषणा xhci_warn_ratelimited(xhci, fmt, args...) \
	dev_warn_ratelimited(xhci_to_hcd(xhci)->self.controller , fmt , ## args)
#घोषणा xhci_info(xhci, fmt, args...) \
	dev_info(xhci_to_hcd(xhci)->self.controller , fmt , ## args)

/*
 * Registers should always be accessed with द्विगुन word or quad word accesses.
 *
 * Some xHCI implementations may support 64-bit address poपूर्णांकers.  Registers
 * with 64-bit address poपूर्णांकers should be written to with dword accesses by
 * writing the low dword first (ptr[0]), then the high dword (ptr[1]) second.
 * xHCI implementations that करो not support 64-bit address poपूर्णांकers will ignore
 * the high dword, and ग_लिखो order is irrelevant.
 */
अटल अंतरभूत u64 xhci_पढ़ो_64(स्थिर काष्ठा xhci_hcd *xhci,
		__le64 __iomem *regs)
अणु
	वापस lo_hi_पढ़ोq(regs);
पूर्ण
अटल अंतरभूत व्योम xhci_ग_लिखो_64(काष्ठा xhci_hcd *xhci,
				 स्थिर u64 val, __le64 __iomem *regs)
अणु
	lo_hi_ग_लिखोq(val, regs);
पूर्ण

अटल अंतरभूत पूर्णांक xhci_link_trb_quirk(काष्ठा xhci_hcd *xhci)
अणु
	वापस xhci->quirks & XHCI_LINK_TRB_QUIRK;
पूर्ण

/* xHCI debugging */
अक्षर *xhci_get_slot_state(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *ctx);
व्योम xhci_dbg_trace(काष्ठा xhci_hcd *xhci, व्योम (*trace)(काष्ठा va_क्रमmat *),
			स्थिर अक्षर *fmt, ...);

/* xHCI memory management */
व्योम xhci_mem_cleanup(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_mem_init(काष्ठा xhci_hcd *xhci, gfp_t flags);
व्योम xhci_मुक्त_virt_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id);
पूर्णांक xhci_alloc_virt_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id, काष्ठा usb_device *udev, gfp_t flags);
पूर्णांक xhci_setup_addressable_virt_dev(काष्ठा xhci_hcd *xhci, काष्ठा usb_device *udev);
व्योम xhci_copy_ep0_dequeue_पूर्णांकo_input_ctx(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev);
अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_index(काष्ठा usb_endpoपूर्णांक_descriptor *desc);
अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_address(अचिन्हित पूर्णांक ep_index);
अचिन्हित पूर्णांक xhci_last_valid_endpoपूर्णांक(u32 added_ctxs);
व्योम xhci_endpoपूर्णांक_zero(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_device *virt_dev, काष्ठा usb_host_endpoपूर्णांक *ep);
व्योम xhci_update_tt_active_eps(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		पूर्णांक old_active_eps);
व्योम xhci_clear_endpoपूर्णांक_bw_info(काष्ठा xhci_bw_info *bw_info);
व्योम xhci_update_bw_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_input_control_ctx *ctrl_ctx,
		काष्ठा xhci_virt_device *virt_dev);
व्योम xhci_endpoपूर्णांक_copy(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_container_ctx *out_ctx,
		अचिन्हित पूर्णांक ep_index);
व्योम xhci_slot_copy(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_container_ctx *out_ctx);
पूर्णांक xhci_endpoपूर्णांक_init(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_device *virt_dev,
		काष्ठा usb_device *udev, काष्ठा usb_host_endpoपूर्णांक *ep,
		gfp_t mem_flags);
काष्ठा xhci_ring *xhci_ring_alloc(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_segs, अचिन्हित पूर्णांक cycle_state,
		क्रमागत xhci_ring_type type, अचिन्हित पूर्णांक max_packet, gfp_t flags);
व्योम xhci_ring_मुक्त(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring);
पूर्णांक xhci_ring_expansion(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
		अचिन्हित पूर्णांक num_trbs, gfp_t flags);
पूर्णांक xhci_alloc_erst(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ring *evt_ring,
		काष्ठा xhci_erst *erst,
		gfp_t flags);
व्योम xhci_initialize_ring_info(काष्ठा xhci_ring *ring,
			अचिन्हित पूर्णांक cycle_state);
व्योम xhci_मुक्त_erst(काष्ठा xhci_hcd *xhci, काष्ठा xhci_erst *erst);
व्योम xhci_मुक्त_endpoपूर्णांक_ring(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		अचिन्हित पूर्णांक ep_index);
काष्ठा xhci_stream_info *xhci_alloc_stream_info(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_stream_ctxs,
		अचिन्हित पूर्णांक num_streams,
		अचिन्हित पूर्णांक max_packet, gfp_t flags);
व्योम xhci_मुक्त_stream_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_stream_info *stream_info);
व्योम xhci_setup_streams_ep_input_ctx(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ep_ctx *ep_ctx,
		काष्ठा xhci_stream_info *stream_info);
व्योम xhci_setup_no_streams_ep_input_ctx(काष्ठा xhci_ep_ctx *ep_ctx,
		काष्ठा xhci_virt_ep *ep);
व्योम xhci_मुक्त_device_endpoपूर्णांक_resources(काष्ठा xhci_hcd *xhci,
	काष्ठा xhci_virt_device *virt_dev, bool drop_control_ep);
काष्ठा xhci_ring *xhci_dma_to_transfer_ring(
		काष्ठा xhci_virt_ep *ep,
		u64 address);
काष्ठा xhci_command *xhci_alloc_command(काष्ठा xhci_hcd *xhci,
		bool allocate_completion, gfp_t mem_flags);
काष्ठा xhci_command *xhci_alloc_command_with_ctx(काष्ठा xhci_hcd *xhci,
		bool allocate_completion, gfp_t mem_flags);
व्योम xhci_urb_मुक्त_priv(काष्ठा urb_priv *urb_priv);
व्योम xhci_मुक्त_command(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_command *command);
काष्ठा xhci_container_ctx *xhci_alloc_container_ctx(काष्ठा xhci_hcd *xhci,
		पूर्णांक type, gfp_t flags);
व्योम xhci_मुक्त_container_ctx(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *ctx);

/* xHCI host controller glue */
प्रकार व्योम (*xhci_get_quirks_t)(काष्ठा device *, काष्ठा xhci_hcd *);
पूर्णांक xhci_handshake(व्योम __iomem *ptr, u32 mask, u32 करोne, पूर्णांक usec);
व्योम xhci_quiesce(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_halt(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_start(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_reset(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_run(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_gen_setup(काष्ठा usb_hcd *hcd, xhci_get_quirks_t get_quirks);
व्योम xhci_shutकरोwn(काष्ठा usb_hcd *hcd);
व्योम xhci_init_driver(काष्ठा hc_driver *drv,
		      स्थिर काष्ठा xhci_driver_overrides *over);
पूर्णांक xhci_add_endpoपूर्णांक(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		      काष्ठा usb_host_endpoपूर्णांक *ep);
पूर्णांक xhci_drop_endpoपूर्णांक(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		       काष्ठा usb_host_endpoपूर्णांक *ep);
पूर्णांक xhci_check_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev);
व्योम xhci_reset_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev);
पूर्णांक xhci_disable_slot(काष्ठा xhci_hcd *xhci, u32 slot_id);
पूर्णांक xhci_ext_cap_init(काष्ठा xhci_hcd *xhci);

पूर्णांक xhci_suspend(काष्ठा xhci_hcd *xhci, bool करो_wakeup);
पूर्णांक xhci_resume(काष्ठा xhci_hcd *xhci, bool hibernated);

irqवापस_t xhci_irq(काष्ठा usb_hcd *hcd);
irqवापस_t xhci_msi_irq(पूर्णांक irq, व्योम *hcd);
पूर्णांक xhci_alloc_dev(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev);
पूर्णांक xhci_alloc_tt_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		काष्ठा usb_device *hdev,
		काष्ठा usb_tt *tt, gfp_t mem_flags);

/* xHCI ring, segment, TRB, and TD functions */
dma_addr_t xhci_trb_virt_to_dma(काष्ठा xhci_segment *seg, जोड़ xhci_trb *trb);
काष्ठा xhci_segment *trb_in_td(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_segment *start_seg, जोड़ xhci_trb *start_trb,
		जोड़ xhci_trb *end_trb, dma_addr_t suspect_dma, bool debug);
पूर्णांक xhci_is_venकरोr_info_code(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक trb_comp_code);
व्योम xhci_ring_cmd_db(काष्ठा xhci_hcd *xhci);
पूर्णांक xhci_queue_slot_control(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 trb_type, u32 slot_id);
पूर्णांक xhci_queue_address_device(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		dma_addr_t in_ctx_ptr, u32 slot_id, क्रमागत xhci_setup_dev);
पूर्णांक xhci_queue_venकरोr_command(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 field1, u32 field2, u32 field3, u32 field4);
पूर्णांक xhci_queue_stop_endpoपूर्णांक(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index, पूर्णांक suspend);
पूर्णांक xhci_queue_ctrl_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags, काष्ठा urb *urb,
		पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index);
पूर्णांक xhci_queue_bulk_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags, काष्ठा urb *urb,
		पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index);
पूर्णांक xhci_queue_पूर्णांकr_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags, काष्ठा urb *urb,
		पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index);
पूर्णांक xhci_queue_isoc_tx_prepare(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index);
पूर्णांक xhci_queue_configure_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_command *cmd, dma_addr_t in_ctx_ptr, u32 slot_id,
		bool command_must_succeed);
पूर्णांक xhci_queue_evaluate_context(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		dma_addr_t in_ctx_ptr, u32 slot_id, bool command_must_succeed);
पूर्णांक xhci_queue_reset_ep(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index,
		क्रमागत xhci_ep_reset_type reset_type);
पूर्णांक xhci_queue_reset_device(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 slot_id);
व्योम xhci_cleanup_stalled_ring(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक slot_id,
			       अचिन्हित पूर्णांक ep_index, अचिन्हित पूर्णांक stream_id,
			       काष्ठा xhci_td *td);
व्योम xhci_stop_endpoपूर्णांक_command_watchकरोg(काष्ठा समयr_list *t);
व्योम xhci_handle_command_समयout(काष्ठा work_काष्ठा *work);

व्योम xhci_ring_ep_करोorbell(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index, अचिन्हित पूर्णांक stream_id);
व्योम xhci_ring_करोorbell_क्रम_active_rings(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index);
व्योम xhci_cleanup_command_queue(काष्ठा xhci_hcd *xhci);
व्योम inc_deq(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring);
अचिन्हित पूर्णांक count_trbs(u64 addr, u64 len);

/* xHCI roothub code */
व्योम xhci_set_link_state(काष्ठा xhci_hcd *xhci, काष्ठा xhci_port *port,
				u32 link_state);
व्योम xhci_test_and_clear_bit(काष्ठा xhci_hcd *xhci, काष्ठा xhci_port *port,
				u32 port_bit);
पूर्णांक xhci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue, u16 wIndex,
		अक्षर *buf, u16 wLength);
पूर्णांक xhci_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf);
पूर्णांक xhci_find_raw_port_number(काष्ठा usb_hcd *hcd, पूर्णांक port1);
काष्ठा xhci_hub *xhci_get_rhub(काष्ठा usb_hcd *hcd);

व्योम xhci_hc_died(काष्ठा xhci_hcd *xhci);

#अगर_घोषित CONFIG_PM
पूर्णांक xhci_bus_suspend(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_bus_resume(काष्ठा usb_hcd *hcd);
अचिन्हित दीर्घ xhci_get_resuming_ports(काष्ठा usb_hcd *hcd);
#अन्यथा
#घोषणा	xhci_bus_suspend	शून्य
#घोषणा	xhci_bus_resume		शून्य
#घोषणा	xhci_get_resuming_ports	शून्य
#पूर्ण_अगर	/* CONFIG_PM */

u32 xhci_port_state_to_neutral(u32 state);
पूर्णांक xhci_find_slot_id_by_port(काष्ठा usb_hcd *hcd, काष्ठा xhci_hcd *xhci,
		u16 port);
व्योम xhci_ring_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id);

/* xHCI contexts */
काष्ठा xhci_input_control_ctx *xhci_get_input_control_ctx(काष्ठा xhci_container_ctx *ctx);
काष्ठा xhci_slot_ctx *xhci_get_slot_ctx(काष्ठा xhci_hcd *xhci, काष्ठा xhci_container_ctx *ctx);
काष्ठा xhci_ep_ctx *xhci_get_ep_ctx(काष्ठा xhci_hcd *xhci, काष्ठा xhci_container_ctx *ctx, अचिन्हित पूर्णांक ep_index);

काष्ठा xhci_ring *xhci_triad_to_transfer_ring(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index,
		अचिन्हित पूर्णांक stream_id);

अटल अंतरभूत काष्ठा xhci_ring *xhci_urb_to_transfer_ring(काष्ठा xhci_hcd *xhci,
								काष्ठा urb *urb)
अणु
	वापस xhci_triad_to_transfer_ring(xhci, urb->dev->slot_id,
					xhci_get_endpoपूर्णांक_index(&urb->ep->desc),
					urb->stream_id);
पूर्ण

/*
 * TODO: As per spec Isochronous IDT transmissions are supported. We bypass
 * them anyways as we where unable to find a device that matches the
 * स्थिरraपूर्णांकs.
 */
अटल अंतरभूत bool xhci_urb_suitable_क्रम_idt(काष्ठा urb *urb)
अणु
	अगर (!usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc) && usb_urb_dir_out(urb) &&
	    usb_endpoपूर्णांक_maxp(&urb->ep->desc) >= TRB_IDT_MAX_SIZE &&
	    urb->transfer_buffer_length <= TRB_IDT_MAX_SIZE &&
	    !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP) &&
	    !urb->num_sgs)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत अक्षर *xhci_slot_state_string(u32 state)
अणु
	चयन (state) अणु
	हाल SLOT_STATE_ENABLED:
		वापस "enabled/disabled";
	हाल SLOT_STATE_DEFAULT:
		वापस "default";
	हाल SLOT_STATE_ADDRESSED:
		वापस "addressed";
	हाल SLOT_STATE_CONFIGURED:
		वापस "configured";
	शेष:
		वापस "reserved";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_trb(u32 field0, u32 field1, u32 field2,
		u32 field3)
अणु
	अटल अक्षर str[256];
	पूर्णांक type = TRB_FIELD_TO_TYPE(field3);

	चयन (type) अणु
	हाल TRB_LINK:
		प्र_लिखो(str,
			"LINK %08x%08x intr %d type '%s' flags %c:%c:%c:%c",
			field1, field0, GET_INTR_TARGET(field2),
			xhci_trb_type_string(type),
			field3 & TRB_IOC ? 'I' : 'i',
			field3 & TRB_CHAIN ? 'C' : 'c',
			field3 & TRB_TC ? 'T' : 't',
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_TRANSFER:
	हाल TRB_COMPLETION:
	हाल TRB_PORT_STATUS:
	हाल TRB_BANDWIDTH_EVENT:
	हाल TRB_DOORBELL:
	हाल TRB_HC_EVENT:
	हाल TRB_DEV_NOTE:
	हाल TRB_MFINDEX_WRAP:
		प्र_लिखो(str,
			"TRB %08x%08x status '%s' len %d slot %d ep %d type '%s' flags %c:%c",
			field1, field0,
			xhci_trb_comp_code_string(GET_COMP_CODE(field2)),
			EVENT_TRB_LEN(field2), TRB_TO_SLOT_ID(field3),
			/* Macro decrements 1, maybe it shouldn't?!? */
			TRB_TO_EP_INDEX(field3) + 1,
			xhci_trb_type_string(type),
			field3 & EVENT_DATA ? 'E' : 'e',
			field3 & TRB_CYCLE ? 'C' : 'c');

		अवरोध;
	हाल TRB_SETUP:
		प्र_लिखो(str, "bRequestType %02x bRequest %02x wValue %02x%02x wIndex %02x%02x wLength %d length %d TD size %d intr %d type '%s' flags %c:%c:%c",
				field0 & 0xff,
				(field0 & 0xff00) >> 8,
				(field0 & 0xff000000) >> 24,
				(field0 & 0xff0000) >> 16,
				(field1 & 0xff00) >> 8,
				field1 & 0xff,
				(field1 & 0xff000000) >> 16 |
				(field1 & 0xff0000) >> 16,
				TRB_LEN(field2), GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				xhci_trb_type_string(type),
				field3 & TRB_IDT ? 'I' : 'i',
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_DATA:
		प्र_लिखो(str, "Buffer %08x%08x length %d TD size %d intr %d type '%s' flags %c:%c:%c:%c:%c:%c:%c",
				field1, field0, TRB_LEN(field2), GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				xhci_trb_type_string(type),
				field3 & TRB_IDT ? 'I' : 'i',
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_NO_SNOOP ? 'S' : 's',
				field3 & TRB_ISP ? 'I' : 'i',
				field3 & TRB_ENT ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_STATUS:
		प्र_लिखो(str, "Buffer %08x%08x length %d TD size %d intr %d type '%s' flags %c:%c:%c:%c",
				field1, field0, TRB_LEN(field2), GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				xhci_trb_type_string(type),
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_ENT ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_NORMAL:
	हाल TRB_ISOC:
	हाल TRB_EVENT_DATA:
	हाल TRB_TR_NOOP:
		प्र_लिखो(str,
			"Buffer %08x%08x length %d TD size %d intr %d type '%s' flags %c:%c:%c:%c:%c:%c:%c:%c",
			field1, field0, TRB_LEN(field2), GET_TD_SIZE(field2),
			GET_INTR_TARGET(field2),
			xhci_trb_type_string(type),
			field3 & TRB_BEI ? 'B' : 'b',
			field3 & TRB_IDT ? 'I' : 'i',
			field3 & TRB_IOC ? 'I' : 'i',
			field3 & TRB_CHAIN ? 'C' : 'c',
			field3 & TRB_NO_SNOOP ? 'S' : 's',
			field3 & TRB_ISP ? 'I' : 'i',
			field3 & TRB_ENT ? 'E' : 'e',
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;

	हाल TRB_CMD_NOOP:
	हाल TRB_ENABLE_SLOT:
		प्र_लिखो(str,
			"%s: flags %c",
			xhci_trb_type_string(type),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_DISABLE_SLOT:
	हाल TRB_NEG_BANDWIDTH:
		प्र_लिखो(str,
			"%s: slot %d flags %c",
			xhci_trb_type_string(type),
			TRB_TO_SLOT_ID(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_ADDR_DEV:
		प्र_लिखो(str,
			"%s: ctx %08x%08x slot %d flags %c:%c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_SLOT_ID(field3),
			field3 & TRB_BSR ? 'B' : 'b',
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_CONFIG_EP:
		प्र_लिखो(str,
			"%s: ctx %08x%08x slot %d flags %c:%c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_SLOT_ID(field3),
			field3 & TRB_DC ? 'D' : 'd',
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_EVAL_CONTEXT:
		प्र_लिखो(str,
			"%s: ctx %08x%08x slot %d flags %c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_SLOT_ID(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_RESET_EP:
		प्र_लिखो(str,
			"%s: ctx %08x%08x slot %d ep %d flags %c:%c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_SLOT_ID(field3),
			/* Macro decrements 1, maybe it shouldn't?!? */
			TRB_TO_EP_INDEX(field3) + 1,
			field3 & TRB_TSP ? 'T' : 't',
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_STOP_RING:
		प्र_लिखो(str,
			"%s: slot %d sp %d ep %d flags %c",
			xhci_trb_type_string(type),
			TRB_TO_SLOT_ID(field3),
			TRB_TO_SUSPEND_PORT(field3),
			/* Macro decrements 1, maybe it shouldn't?!? */
			TRB_TO_EP_INDEX(field3) + 1,
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_SET_DEQ:
		प्र_लिखो(str,
			"%s: deq %08x%08x stream %d slot %d ep %d flags %c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_STREAM_ID(field2),
			TRB_TO_SLOT_ID(field3),
			/* Macro decrements 1, maybe it shouldn't?!? */
			TRB_TO_EP_INDEX(field3) + 1,
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_RESET_DEV:
		प्र_लिखो(str,
			"%s: slot %d flags %c",
			xhci_trb_type_string(type),
			TRB_TO_SLOT_ID(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_FORCE_EVENT:
		प्र_लिखो(str,
			"%s: event %08x%08x vf intr %d vf id %d flags %c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_VF_INTR_TARGET(field2),
			TRB_TO_VF_ID(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_SET_LT:
		प्र_लिखो(str,
			"%s: belt %d flags %c",
			xhci_trb_type_string(type),
			TRB_TO_BELT(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_GET_BW:
		प्र_लिखो(str,
			"%s: ctx %08x%08x slot %d speed %d flags %c",
			xhci_trb_type_string(type),
			field1, field0,
			TRB_TO_SLOT_ID(field3),
			TRB_TO_DEV_SPEED(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_FORCE_HEADER:
		प्र_लिखो(str,
			"%s: info %08x%08x%08x pkt type %d roothub port %d flags %c",
			xhci_trb_type_string(type),
			field2, field1, field0 & 0xffffffe0,
			TRB_TO_PACKET_TYPE(field0),
			TRB_TO_ROOTHUB_PORT(field3),
			field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	शेष:
		प्र_लिखो(str,
			"type '%s' -> raw %08x %08x %08x %08x",
			xhci_trb_type_string(type),
			field0, field1, field2, field3);
	पूर्ण

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_ctrl_ctx(अचिन्हित दीर्घ drop,
					       अचिन्हित दीर्घ add)
अणु
	अटल अक्षर	str[1024];
	अचिन्हित पूर्णांक	bit;
	पूर्णांक		ret = 0;

	अगर (drop) अणु
		ret = प्र_लिखो(str, "Drop:");
		क्रम_each_set_bit(bit, &drop, 32)
			ret += प्र_लिखो(str + ret, " %d%s",
				       bit / 2,
				       bit % 2 ? "in":"out");
		ret += प्र_लिखो(str + ret, ", ");
	पूर्ण

	अगर (add) अणु
		ret += प्र_लिखो(str + ret, "Add:%s%s",
			       (add & SLOT_FLAG) ? " slot":"",
			       (add & EP0_FLAG) ? " ep0":"");
		add &= ~(SLOT_FLAG | EP0_FLAG);
		क्रम_each_set_bit(bit, &add, 32)
			ret += प्र_लिखो(str + ret, " %d%s",
				       bit / 2,
				       bit % 2 ? "in":"out");
	पूर्ण
	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_slot_context(u32 info, u32 info2,
		u32 tt_info, u32 state)
अणु
	अटल अक्षर str[1024];
	u32 speed;
	u32 hub;
	u32 mtt;
	पूर्णांक ret = 0;

	speed = info & DEV_SPEED;
	hub = info & DEV_HUB;
	mtt = info & DEV_MTT;

	ret = प्र_लिखो(str, "RS %05x %s%s%s Ctx Entries %d MEL %d us Port# %d/%d",
			info & ROUTE_STRING_MASK,
			(अणु अक्षर *s;
			चयन (speed) अणु
			हाल SLOT_SPEED_FS:
				s = "full-speed";
				अवरोध;
			हाल SLOT_SPEED_LS:
				s = "low-speed";
				अवरोध;
			हाल SLOT_SPEED_HS:
				s = "high-speed";
				अवरोध;
			हाल SLOT_SPEED_SS:
				s = "super-speed";
				अवरोध;
			हाल SLOT_SPEED_SSP:
				s = "super-speed plus";
				अवरोध;
			शेष:
				s = "UNKNOWN speed";
			पूर्ण s; पूर्ण),
			mtt ? " multi-TT" : "",
			hub ? " Hub" : "",
			(info & LAST_CTX_MASK) >> 27,
			info2 & MAX_EXIT,
			DEVINFO_TO_ROOT_HUB_PORT(info2),
			DEVINFO_TO_MAX_PORTS(info2));

	ret += प्र_लिखो(str + ret, " [TT Slot %d Port# %d TTT %d Intr %d] Addr %d State %s",
			tt_info & TT_SLOT, (tt_info & TT_PORT) >> 8,
			GET_TT_THINK_TIME(tt_info), GET_INTR_TARGET(tt_info),
			state & DEV_ADDR_MASK,
			xhci_slot_state_string(GET_SLOT_STATE(state)));

	वापस str;
पूर्ण


अटल अंतरभूत स्थिर अक्षर *xhci_portsc_link_state_string(u32 portsc)
अणु
	चयन (portsc & PORT_PLS_MASK) अणु
	हाल XDEV_U0:
		वापस "U0";
	हाल XDEV_U1:
		वापस "U1";
	हाल XDEV_U2:
		वापस "U2";
	हाल XDEV_U3:
		वापस "U3";
	हाल XDEV_DISABLED:
		वापस "Disabled";
	हाल XDEV_RXDETECT:
		वापस "RxDetect";
	हाल XDEV_INACTIVE:
		वापस "Inactive";
	हाल XDEV_POLLING:
		वापस "Polling";
	हाल XDEV_RECOVERY:
		वापस "Recovery";
	हाल XDEV_HOT_RESET:
		वापस "Hot Reset";
	हाल XDEV_COMP_MODE:
		वापस "Compliance mode";
	हाल XDEV_TEST_MODE:
		वापस "Test mode";
	हाल XDEV_RESUME:
		वापस "Resume";
	शेष:
		अवरोध;
	पूर्ण
	वापस "Unknown";
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_portsc(u32 portsc)
अणु
	अटल अक्षर str[256];
	पूर्णांक ret;

	ret = प्र_लिखो(str, "%s %s %s Link:%s PortSpeed:%d ",
		      portsc & PORT_POWER	? "Powered" : "Powered-off",
		      portsc & PORT_CONNECT	? "Connected" : "Not-connected",
		      portsc & PORT_PE		? "Enabled" : "Disabled",
		      xhci_portsc_link_state_string(portsc),
		      DEV_PORT_SPEED(portsc));

	अगर (portsc & PORT_OC)
		ret += प्र_लिखो(str + ret, "OverCurrent ");
	अगर (portsc & PORT_RESET)
		ret += प्र_लिखो(str + ret, "In-Reset ");

	ret += प्र_लिखो(str + ret, "Change: ");
	अगर (portsc & PORT_CSC)
		ret += प्र_लिखो(str + ret, "CSC ");
	अगर (portsc & PORT_PEC)
		ret += प्र_लिखो(str + ret, "PEC ");
	अगर (portsc & PORT_WRC)
		ret += प्र_लिखो(str + ret, "WRC ");
	अगर (portsc & PORT_OCC)
		ret += प्र_लिखो(str + ret, "OCC ");
	अगर (portsc & PORT_RC)
		ret += प्र_लिखो(str + ret, "PRC ");
	अगर (portsc & PORT_PLC)
		ret += प्र_लिखो(str + ret, "PLC ");
	अगर (portsc & PORT_CEC)
		ret += प्र_लिखो(str + ret, "CEC ");
	अगर (portsc & PORT_CAS)
		ret += प्र_लिखो(str + ret, "CAS ");

	ret += प्र_लिखो(str + ret, "Wake: ");
	अगर (portsc & PORT_WKCONN_E)
		ret += प्र_लिखो(str + ret, "WCE ");
	अगर (portsc & PORT_WKDISC_E)
		ret += प्र_लिखो(str + ret, "WDE ");
	अगर (portsc & PORT_WKOC_E)
		ret += प्र_लिखो(str + ret, "WOE ");

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_usbsts(u32 usbsts)
अणु
	अटल अक्षर str[256];
	पूर्णांक ret = 0;

	अगर (usbsts == ~(u32)0)
		वापस " 0xffffffff";
	अगर (usbsts & STS_HALT)
		ret += प्र_लिखो(str + ret, " HCHalted");
	अगर (usbsts & STS_FATAL)
		ret += प्र_लिखो(str + ret, " HSE");
	अगर (usbsts & STS_EINT)
		ret += प्र_लिखो(str + ret, " EINT");
	अगर (usbsts & STS_PORT)
		ret += प्र_लिखो(str + ret, " PCD");
	अगर (usbsts & STS_SAVE)
		ret += प्र_लिखो(str + ret, " SSS");
	अगर (usbsts & STS_RESTORE)
		ret += प्र_लिखो(str + ret, " RSS");
	अगर (usbsts & STS_SRE)
		ret += प्र_लिखो(str + ret, " SRE");
	अगर (usbsts & STS_CNR)
		ret += प्र_लिखो(str + ret, " CNR");
	अगर (usbsts & STS_HCE)
		ret += प्र_लिखो(str + ret, " HCE");

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_करोorbell(u32 slot, u32 करोorbell)
अणु
	अटल अक्षर str[256];
	u8 ep;
	u16 stream;
	पूर्णांक ret;

	ep = (करोorbell & 0xff);
	stream = करोorbell >> 16;

	अगर (slot == 0) अणु
		प्र_लिखो(str, "Command Ring %d", करोorbell);
		वापस str;
	पूर्ण
	ret = प्र_लिखो(str, "Slot %d ", slot);
	अगर (ep > 0 && ep < 32)
		ret = प्र_लिखो(str + ret, "ep%d%s",
			      ep / 2,
			      ep % 2 ? "in" : "out");
	अन्यथा अगर (ep == 0 || ep < 248)
		ret = प्र_लिखो(str + ret, "Reserved %d", ep);
	अन्यथा
		ret = प्र_लिखो(str + ret, "Vendor Defined %d", ep);
	अगर (stream)
		ret = प्र_लिखो(str + ret, " Stream %d", stream);

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_ep_state_string(u8 state)
अणु
	चयन (state) अणु
	हाल EP_STATE_DISABLED:
		वापस "disabled";
	हाल EP_STATE_RUNNING:
		वापस "running";
	हाल EP_STATE_HALTED:
		वापस "halted";
	हाल EP_STATE_STOPPED:
		वापस "stopped";
	हाल EP_STATE_ERROR:
		वापस "error";
	शेष:
		वापस "INVALID";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_ep_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल ISOC_OUT_EP:
		वापस "Isoc OUT";
	हाल BULK_OUT_EP:
		वापस "Bulk OUT";
	हाल INT_OUT_EP:
		वापस "Int OUT";
	हाल CTRL_EP:
		वापस "Ctrl";
	हाल ISOC_IN_EP:
		वापस "Isoc IN";
	हाल BULK_IN_EP:
		वापस "Bulk IN";
	हाल INT_IN_EP:
		वापस "Int IN";
	शेष:
		वापस "INVALID";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *xhci_decode_ep_context(u32 info, u32 info2, u64 deq,
		u32 tx_info)
अणु
	अटल अक्षर str[1024];
	पूर्णांक ret;

	u32 esit;
	u16 maxp;
	u16 avg;

	u8 max_pstr;
	u8 ep_state;
	u8 पूर्णांकerval;
	u8 ep_type;
	u8 burst;
	u8 cerr;
	u8 mult;

	bool lsa;
	bool hid;

	esit = CTX_TO_MAX_ESIT_PAYLOAD_HI(info) << 16 |
		CTX_TO_MAX_ESIT_PAYLOAD(tx_info);

	ep_state = info & EP_STATE_MASK;
	max_pstr = CTX_TO_EP_MAXPSTREAMS(info);
	पूर्णांकerval = CTX_TO_EP_INTERVAL(info);
	mult = CTX_TO_EP_MULT(info) + 1;
	lsa = !!(info & EP_HAS_LSA);

	cerr = (info2 & (3 << 1)) >> 1;
	ep_type = CTX_TO_EP_TYPE(info2);
	hid = !!(info2 & (1 << 7));
	burst = CTX_TO_MAX_BURST(info2);
	maxp = MAX_PACKET_DECODED(info2);

	avg = EP_AVG_TRB_LENGTH(tx_info);

	ret = प्र_लिखो(str, "State %s mult %d max P. Streams %d %s",
			xhci_ep_state_string(ep_state), mult,
			max_pstr, lsa ? "LSA " : "");

	ret += प्र_लिखो(str + ret, "interval %d us max ESIT payload %d CErr %d ",
			(1 << पूर्णांकerval) * 125, esit, cerr);

	ret += प्र_लिखो(str + ret, "Type %s %sburst %d maxp %d deq %016llx ",
			xhci_ep_type_string(ep_type), hid ? "HID" : "",
			burst, maxp, deq);

	ret += प्र_लिखो(str + ret, "avg trb len %d", avg);

	वापस str;
पूर्ण

#पूर्ण_अगर /* __LINUX_XHCI_HCD_H */
