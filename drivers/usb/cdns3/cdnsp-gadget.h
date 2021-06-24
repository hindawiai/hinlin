<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 * Code based on Linux XHCI driver.
 * Origin: Copyright (C) 2008 Intel Corp.
 */
#अगर_अघोषित __LINUX_CDNSP_GADGET_H
#घोषणा __LINUX_CDNSP_GADGET_H

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/irq.h>

/* Max number slots - only 1 is allowed. */
#घोषणा CDNSP_DEV_MAX_SLOTS	1

#घोषणा CDNSP_EP0_SETUP_SIZE	512

/* One control and 15 क्रम in and 15 क्रम out endpoपूर्णांकs. */
#घोषणा CDNSP_ENDPOINTS_NUM	31

/* Best Efक्रमt Service Latency. */
#घोषणा CDNSP_DEFAULT_BESL	0

/* Device Controller command शेष समयout value in us */
#घोषणा CDNSP_CMD_TIMEOUT	(15 * 1000)

/* Up to 16 ms to halt an device controller */
#घोषणा CDNSP_MAX_HALT_USEC	(16 * 1000)

#घोषणा CDNSP_CTX_SIZE	2112

/*
 * Controller रेजिस्टर पूर्णांकerface.
 */

/**
 * काष्ठा cdnsp_cap_regs - CDNSP Registers.
 * @hc_capbase:	Length of the capabilities रेजिस्टर and controller
 *              version number
 * @hcs_params1: HCSPARAMS1 - Structural Parameters 1
 * @hcs_params2: HCSPARAMS2 - Structural Parameters 2
 * @hcs_params3: HCSPARAMS3 - Structural Parameters 3
 * @hcc_params: HCCPARAMS - Capability Parameters
 * @db_off: DBOFF - Doorbell array offset
 * @run_regs_off: RTSOFF - Runसमय रेजिस्टर space offset
 * @hcc_params2: HCCPARAMS2 Capability Parameters 2,
 */
काष्ठा cdnsp_cap_regs अणु
	__le32 hc_capbase;
	__le32 hcs_params1;
	__le32 hcs_params2;
	__le32 hcs_params3;
	__le32 hcc_params;
	__le32 db_off;
	__le32 run_regs_off;
	__le32 hcc_params2;
	/* Reserved up to (CAPLENGTH - 0x1C) */
पूर्ण;

/* hc_capbase biपंचांगasks. */
/* bits 7:0 - how दीर्घ is the Capabilities रेजिस्टर. */
#घोषणा HC_LENGTH(p)		(((p) >> 00) & GENMASK(7, 0))
/* bits 31:16	*/
#घोषणा HC_VERSION(p)		(((p) >> 16) & GENMASK(15, 1))

/* HCSPARAMS1 - hcs_params1 - biपंचांगasks */
/* bits 0:7, Max Device Endpoपूर्णांकs */
#घोषणा HCS_ENDPOINTS_MASK	GENMASK(7, 0)
#घोषणा HCS_ENDPOINTS(p)	(((p) & HCS_ENDPOINTS_MASK) >> 0)

/* HCCPARAMS offset from PCI base address */
#घोषणा HCC_PARAMS_OFFSET	0x10

/* HCCPARAMS - hcc_params - biपंचांगasks */
/* 1: device controller can use 64-bit address poपूर्णांकers. */
#घोषणा HCC_64BIT_ADDR(p)	((p) & BIT(0))
/* 1: device controller uses 64-byte Device Context काष्ठाures. */
#घोषणा HCC_64BYTE_CONTEXT(p)	((p) & BIT(2))
/* Max size क्रम Primary Stream Arrays - 2^(n+1), where n is bits 12:15. */
#घोषणा HCC_MAX_PSA(p)		((((p) >> 12) & 0xf) + 1)
/* Extended Capabilities poपूर्णांकer from PCI base. */
#घोषणा HCC_EXT_CAPS(p)		(((p) & GENMASK(31, 16)) >> 16)

#घोषणा CTX_SIZE(_hcc)		(HCC_64BYTE_CONTEXT(_hcc) ? 64 : 32)

/* db_off biपंचांगask - bits 0:1 reserved. */
#घोषणा DBOFF_MASK	GENMASK(31, 2)

/* run_regs_off biपंचांगask - bits 0:4 reserved. */
#घोषणा RTSOFF_MASK	GENMASK(31, 5)

/**
 * काष्ठा cdnsp_op_regs - Device Controller Operational Registers.
 * @command: USBCMD - Controller command रेजिस्टर.
 * @status: USBSTS - Controller status रेजिस्टर.
 * @page_size: This indicates the page size that the device controller supports.
 *             If bit n is set, the controller supports a page size of 2^(n+12),
 *             up to a 128MB page size. 4K is the minimum page size.
 * @dnctrl: DNCTRL - Device notअगरication control रेजिस्टर.
 * @cmd_ring: CRP - 64-bit Command Ring Poपूर्णांकer.
 * @dcbaa_ptr: DCBAAP - 64-bit Device Context Base Address Array Poपूर्णांकer.
 * @config_reg: CONFIG - Configure Register
 * @port_reg_base: PORTSCn - base address क्रम Port Status and Control
 *                 Each port has a Port Status and Control रेजिस्टर,
 *                 followed by a Port Power Management Status and Control
 *                 रेजिस्टर, a Port Link Info रेजिस्टर, and a reserved
 *                 रेजिस्टर.
 */
काष्ठा cdnsp_op_regs अणु
	__le32 command;
	__le32 status;
	__le32 page_size;
	__le32 reserved1;
	__le32 reserved2;
	__le32 dnctrl;
	__le64 cmd_ring;
	/* rsvd: offset 0x20-2F. */
	__le32 reserved3[4];
	__le64 dcbaa_ptr;
	__le32 config_reg;
	/* rsvd: offset 0x3C-3FF. */
	__le32 reserved4[241];
	/* port 1 रेजिस्टरs, which serve as a base address क्रम other ports. */
	__le32 port_reg_base;
पूर्ण;

/* Number of रेजिस्टरs per port. */
#घोषणा NUM_PORT_REGS	4

/**
 * काष्ठा cdnsp_port_regs - Port Registers.
 * @portsc: PORTSC - Port Status and Control Register.
 * @portpmsc: PORTPMSC - Port Power Managements Status and Control Register.
 * @portli: PORTLI - Port Link Info रेजिस्टर.
 */
काष्ठा cdnsp_port_regs अणु
	__le32 portsc;
	__le32 portpmsc;
	__le32 portli;
	__le32 reserved;
पूर्ण;

/*
 * These bits are Read Only (RO) and should be saved and written to the
 * रेजिस्टरs: 0 (connect status) and  10:13 (port speed).
 * These bits are also sticky - meaning they're in the AUX well and they aren't
 * changed by a hot and warm.
 */
#घोषणा CDNSP_PORT_RO	(PORT_CONNECT | DEV_SPEED_MASK)

/*
 * These bits are RW; writing a 0 clears the bit, writing a 1 sets the bit:
 * bits 5:8 (link state), 25:26  ("wake on" enable state)
 */
#घोषणा CDNSP_PORT_RWS	(PORT_PLS_MASK | PORT_WKCONN_E | PORT_WKDISC_E)

/*
 * These bits are RW; writing a 1 clears the bit, writing a 0 has no effect:
 * bits 1 (port enable/disable), 17  ( connect changed),
 * 21 (port reset changed) , 22 (Port Link State Change),
 */
#घोषणा CDNSP_PORT_RW1CS (PORT_PED | PORT_CSC | PORT_RC | PORT_PLC)

/* USBCMD - USB command - biपंचांगasks. */
/* Run/Stop, controller execution - करो not ग_लिखो unless controller is halted.*/
#घोषणा CMD_R_S		BIT(0)
/*
 * Reset device controller - resets पूर्णांकernal controller state machine and all
 * रेजिस्टरs (except PCI config regs).
 */
#घोषणा CMD_RESET	BIT(1)
/* Event Interrupt Enable - a '1' allows पूर्णांकerrupts from the controller. */
#घोषणा CMD_INTE	BIT(2)
/*
 * Device System Error Interrupt Enable - get out-of-band संकेत क्रम
 * controller errors.
 */
#घोषणा CMD_DSEIE	BIT(3)
/* device controller save/restore state. */
#घोषणा CMD_CSS		BIT(8)
#घोषणा CMD_CRS		BIT(9)
/*
 * Enable Wrap Event - '1' means device controller generates an event
 * when MFINDEX wraps.
 */
#घोषणा CMD_EWE		BIT(10)
/* 1: device enabled */
#घोषणा CMD_DEVEN	BIT(17)
/* bits 18:31 are reserved (and should be preserved on ग_लिखोs). */

/* Command रेजिस्टर values to disable पूर्णांकerrupts. */
#घोषणा CDNSP_IRQS	(CMD_INTE | CMD_DSEIE | CMD_EWE)

/* USBSTS - USB status - biपंचांगasks */
/* controller not running - set to 1 when run/stop bit is cleared. */
#घोषणा STS_HALT	BIT(0)
/*
 * serious error, e.g. PCI parity error. The controller will clear
 * the run/stop bit.
 */
#घोषणा STS_FATAL	BIT(2)
/* event पूर्णांकerrupt - clear this prior to clearing any IP flags in IR set.*/
#घोषणा STS_EINT	BIT(3)
/* port change detect */
#घोषणा STS_PCD		BIT(4)
/* save state status - '1' means device controller is saving state. */
#घोषणा STS_SSS		BIT(8)
/* restore state status - '1' means controllers is restoring state. */
#घोषणा STS_RSS		BIT(9)
/* 1: save or restore error */
#घोषणा STS_SRE		BIT(10)
/* 1: device Not Ready to accept करोorbell or op reg ग_लिखोs after reset. */
#घोषणा STS_CNR		BIT(11)
/* 1: पूर्णांकernal Device Controller Error.*/
#घोषणा STS_HCE		BIT(12)

/* CRCR - Command Ring Control Register - cmd_ring biपंचांगasks. */
/* bit 0 is the command ring cycle state. */
#घोषणा CMD_RING_CS		BIT(0)
/* stop ring immediately - पात the currently executing command. */
#घोषणा CMD_RING_ABORT		BIT(2)
/*
 * Command Ring Busy.
 * Set when Doorbell रेजिस्टर is written with DB क्रम command and cleared when
 * the controller reached end of CR.
 */
#घोषणा CMD_RING_BUSY(p)	((p) & BIT(4))
/* 1: command ring is running */
#घोषणा CMD_RING_RUNNING	BIT(3)
/* Command Ring poपूर्णांकer - bit mask क्रम the lower 32 bits. */
#घोषणा CMD_RING_RSVD_BITS	GENMASK(5, 0)

/* CONFIG - Configure Register - config_reg biपंचांगasks. */
/* bits 0:7 - maximum number of device slots enabled. */
#घोषणा MAX_DEVS		GENMASK(7, 0)
/* bit 8: U3 Entry Enabled, निश्चित PLC when controller enters U3. */
#घोषणा CONFIG_U3E		BIT(8)

/* PORTSC - Port Status and Control Register - port_reg_base biपंचांगasks */
/* 1: device connected. */
#घोषणा PORT_CONNECT		BIT(0)
/* 1: port enabled. */
#घोषणा PORT_PED		BIT(1)
/* 1: port reset संकेतing निश्चितed. */
#घोषणा PORT_RESET		BIT(4)
/*
 * Port Link State - bits 5:8
 * A पढ़ो gives the current link PM state of the port,
 * a ग_लिखो with Link State Write Strobe sets the link state.
 */
#घोषणा PORT_PLS_MASK		GENMASK(8, 5)
#घोषणा XDEV_U0			(0x0 << 5)
#घोषणा XDEV_U1			(0x1 << 5)
#घोषणा XDEV_U2			(0x2 << 5)
#घोषणा XDEV_U3			(0x3 << 5)
#घोषणा XDEV_DISABLED		(0x4 << 5)
#घोषणा XDEV_RXDETECT		(0x5 << 5)
#घोषणा XDEV_INACTIVE		(0x6 << 5)
#घोषणा XDEV_POLLING		(0x7 << 5)
#घोषणा XDEV_RECOVERY		(0x8 << 5)
#घोषणा XDEV_HOT_RESET		(0x9 << 5)
#घोषणा XDEV_COMP_MODE		(0xa << 5)
#घोषणा XDEV_TEST_MODE		(0xb << 5)
#घोषणा XDEV_RESUME		(0xf << 5)
/* 1: port has घातer. */
#घोषणा PORT_POWER		BIT(9)
/*
 * bits 10:13 indicate device speed:
 * 0 - undefined speed - port hasn't be initialized by a reset yet
 * 1 - full speed
 * 2 - Reserved (Low Speed not supported
 * 3 - high speed
 * 4 - super speed
 * 5 - super speed
 * 6-15 reserved
 */
#घोषणा DEV_SPEED_MASK		GENMASK(13, 10)
#घोषणा XDEV_FS			(0x1 << 10)
#घोषणा XDEV_HS			(0x3 << 10)
#घोषणा XDEV_SS			(0x4 << 10)
#घोषणा XDEV_SSP		(0x5 << 10)
#घोषणा DEV_UNDEFSPEED(p)	(((p) & DEV_SPEED_MASK) == (0x0 << 10))
#घोषणा DEV_FULLSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_FS)
#घोषणा DEV_HIGHSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_HS)
#घोषणा DEV_SUPERSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_SS)
#घोषणा DEV_SUPERSPEEDPLUS(p)	(((p) & DEV_SPEED_MASK) == XDEV_SSP)
#घोषणा DEV_SUPERSPEED_ANY(p)	(((p) & DEV_SPEED_MASK) >= XDEV_SS)
#घोषणा DEV_PORT_SPEED(p)	(((p) >> 10) & 0x0f)
/* Port Link State Write Strobe - set this when changing link state */
#घोषणा PORT_LINK_STROBE	BIT(16)
/* 1: connect status change */
#घोषणा PORT_CSC		BIT(17)
/* 1: warm reset क्रम a USB 3.0 device is करोne. */
#घोषणा PORT_WRC		BIT(19)
/* 1: reset change - 1 to 0 transition of PORT_RESET */
#घोषणा PORT_RC			BIT(21)
/*
 * port link status change - set on some port link state transitions:
 * Transition			Reason
 * ----------------------------------------------------------------------------
 * - U3 to Resume		Wakeup संकेतing from a device
 * - Resume to Recovery to U0	USB 3.0 device resume
 * - Resume to U0		USB 2.0 device resume
 * - U3 to Recovery to U0	Software resume of USB 3.0 device complete
 * - U3 to U0			Software resume of USB 2.0 device complete
 * - U2 to U0			L1 resume of USB 2.1 device complete
 * - U0 to U0			L1 entry rejection by USB 2.1 device
 * - U0 to disabled		L1 entry error with USB 2.1 device
 * - Any state to inactive	Error on USB 3.0 port
 */
#घोषणा PORT_PLC		BIT(22)
/* Port configure error change - port failed to configure its link partner. */
#घोषणा PORT_CEC		BIT(23)
/* Wake on connect (enable). */
#घोषणा PORT_WKCONN_E		BIT(25)
/* Wake on disconnect (enable). */
#घोषणा PORT_WKDISC_E		BIT(26)
/* Indicates अगर Warm Reset is being received. */
#घोषणा PORT_WR			BIT(31)

#घोषणा PORT_CHANGE_BITS (PORT_CSC | PORT_WRC | PORT_RC | PORT_PLC | PORT_CEC)

/* PORTPMSCUSB3 - Port Power Management Status and Control - biपंचांगasks. */
/*  Enables U1 entry. */
#घोषणा PORT_U1_TIMEOUT_MASK	GENMASK(7, 0)
#घोषणा PORT_U1_TIMEOUT(p)	((p) & PORT_U1_TIMEOUT_MASK)
/* Enables U2 entry .*/
#घोषणा PORT_U2_TIMEOUT_MASK	GENMASK(14, 8)
#घोषणा PORT_U2_TIMEOUT(p)	(((p) << 8) & PORT_U2_TIMEOUT_MASK)

/* PORTPMSCUSB2 - Port Power Management Status and Control - biपंचांगasks. */
#घोषणा PORT_L1S_MASK		GENMASK(2, 0)
#घोषणा PORT_L1S(p)		((p) & PORT_L1S_MASK)
#घोषणा PORT_L1S_ACK		PORT_L1S(1)
#घोषणा PORT_L1S_NYET		PORT_L1S(2)
#घोषणा PORT_L1S_STALL		PORT_L1S(3)
#घोषणा PORT_L1S_TIMEOUT	PORT_L1S(4)
/* Remote Wake Enable. */
#घोषणा PORT_RWE		BIT(3)
/* Best Efक्रमt Service Latency (BESL). */
#घोषणा PORT_BESL(p)		(((p) << 4) & GENMASK(7, 4))
/* Hardware LPM Enable (HLE). */
#घोषणा PORT_HLE		BIT(16)
/* Received Best Efक्रमt Service Latency (BESL). */
#घोषणा PORT_RRBESL(p)		(((p) & GENMASK(20, 17)) >> 17)
/* Port Test Control. */
#घोषणा PORT_TEST_MODE_MASK	GENMASK(31, 28)
#घोषणा PORT_TEST_MODE(p)	(((p) << 28) & PORT_TEST_MODE_MASK)

/**
 * काष्ठा cdnsp_पूर्णांकr_reg - Interrupt Register Set.
 * @irq_pending: IMAN - Interrupt Management Register. Used to enable
 *               पूर्णांकerrupts and check क्रम pending पूर्णांकerrupts.
 * @irq_control: IMOD - Interrupt Moderation Register.
 *               Used to throttle पूर्णांकerrupts.
 * @erst_size: Number of segments in the Event Ring Segment Table (ERST).
 * @erst_base: ERST base address.
 * @erst_dequeue: Event ring dequeue poपूर्णांकer.
 *
 * Each पूर्णांकerrupter (defined by a MSI-X vector) has an event ring and an Event
 * Ring Segment Table (ERST) associated with it. The event ring is comprised of
 * multiple segments of the same size. The controller places events on the ring
 * and "updates the Cycle bit in the TRBs to indicate to software the current
 * position of the Enqueue Poपूर्णांकer." The driver processes those events and
 * updates the dequeue poपूर्णांकer.
 */
काष्ठा cdnsp_पूर्णांकr_reg अणु
	__le32 irq_pending;
	__le32 irq_control;
	__le32 erst_size;
	__le32 rsvd;
	__le64 erst_base;
	__le64 erst_dequeue;
पूर्ण;

/* IMAN - Interrupt Management Register - irq_pending biपंचांगasks l. */
#घोषणा IMAN_IE			BIT(1)
#घोषणा IMAN_IP			BIT(0)
/* bits 2:31 need to be preserved */
#घोषणा IMAN_IE_SET(p)		(((p) & IMAN_IE) | 0x2)
#घोषणा IMAN_IE_CLEAR(p)	(((p) & IMAN_IE) & ~(0x2))

/* IMOD - Interrupter Moderation Register - irq_control biपंचांगasks. */
/*
 * Minimum पूर्णांकerval between पूर्णांकerrupts (in 250ns पूर्णांकervals). The पूर्णांकerval
 * between पूर्णांकerrupts will be दीर्घer अगर there are no events on the event ring.
 * Default is 4000 (1 ms).
 */
#घोषणा IMOD_INTERVAL_MASK	GENMASK(15, 0)
/* Counter used to count करोwn the समय to the next पूर्णांकerrupt - HW use only */
#घोषणा IMOD_COUNTER_MASK	GENMASK(31, 16)
#घोषणा IMOD_DEFAULT_INTERVAL	0

/* erst_size biपंचांगasks. */
/* Preserve bits 16:31 of erst_size. */
#घोषणा ERST_SIZE_MASK		GENMASK(31, 16)

/* erst_dequeue biपंचांगasks. */
/*
 * Dequeue ERST Segment Index (DESI) - Segment number (or alias)
 * where the current dequeue poपूर्णांकer lies. This is an optional HW hपूर्णांक.
 */
#घोषणा ERST_DESI_MASK		GENMASK(2, 0)
/* Event Handler Busy (EHB) - is the event ring scheduled to be serviced. */
#घोषणा ERST_EHB		BIT(3)
#घोषणा ERST_PTR_MASK		GENMASK(3, 0)

/**
 * काष्ठा cdnsp_run_regs
 * @microframe_index: MFINDEX - current microframe number.
 * @ir_set: Array of Interrupter रेजिस्टरs.
 *
 * Device Controller Runसमय Registers:
 * "Software should पढ़ो and ग_लिखो these रेजिस्टरs using only Dword (32 bit)
 * or larger accesses"
 */
काष्ठा cdnsp_run_regs अणु
	__le32 microframe_index;
	__le32 rsvd[7];
	काष्ठा cdnsp_पूर्णांकr_reg ir_set[128];
पूर्ण;

/**
 * USB2.0 Port Peripheral Configuration Registers.
 * @ext_cap: Header रेजिस्टर क्रम Extended Capability.
 * @port_reg1: Timer Configuration Register.
 * @port_reg2: Timer Configuration Register.
 * @port_reg3: Timer Configuration Register.
 * @port_reg4: Timer Configuration Register.
 * @port_reg5: Timer Configuration Register.
 * @port_reg6: Chicken bits क्रम USB20PPP.
 */
काष्ठा cdnsp_20port_cap अणु
	__le32 ext_cap;
	__le32 port_reg1;
	__le32 port_reg2;
	__le32 port_reg3;
	__le32 port_reg4;
	__le32 port_reg5;
	__le32 port_reg6;
पूर्ण;

/* Extended capability रेजिस्टर fields */
#घोषणा EXT_CAPS_ID(p)			(((p) >> 0) & GENMASK(7, 0))
#घोषणा EXT_CAPS_NEXT(p)		(((p) >> 8) & GENMASK(7, 0))
/* Extended capability IDs - ID 0 reserved */
#घोषणा EXT_CAPS_PROTOCOL		2

/* USB 2.0 Port Peripheral Configuration Extended Capability */
#घोषणा EXT_CAP_CFG_DEV_20PORT_CAP_ID	0xC1
/*
 * Setting this bit to '1' enables स्वतःmatic wakeup from L1 state on transfer
 * TRB prepared when USBSSP operates in USB2.0 mode.
 */
#घोषणा PORT_REG6_L1_L0_HW_EN		BIT(1)
/*
 * Setting this bit to '1' क्रमces Full Speed when USBSSP operates in USB2.0
 * mode (disables High Speed).
 */
#घोषणा PORT_REG6_FORCE_FS		BIT(0)

/**
 * USB3.x Port Peripheral Configuration Registers.
 * @ext_cap: Header रेजिस्टर क्रम Extended Capability.
 * @mode_addr: Miscellaneous 3xPORT operation mode configuration रेजिस्टर.
 * @mode_2: 3x Port Control Register 2.
 */
काष्ठा cdnsp_3xport_cap अणु
	__le32 ext_cap;
	__le32 mode_addr;
	__le32 reserved[52];
	__le32 mode_2;
पूर्ण;

/* Extended Capability Header क्रम 3XPort Configuration Registers. */
#घोषणा D_XEC_CFG_3XPORT_CAP		0xC0
#घोषणा CFG_3XPORT_SSP_SUPPORT		BIT(31)
#घोषणा CFG_3XPORT_U1_PIPE_CLK_GATE_EN	BIT(0)

/* Revision Extended Capability ID */
#घोषणा RTL_REV_CAP			0xC4
#घोषणा RTL_REV_CAP_RX_BUFF_CMD_SIZE	BITMASK(31, 24)
#घोषणा RTL_REV_CAP_RX_BUFF_SIZE	BITMASK(15, 0)
#घोषणा RTL_REV_CAP_TX_BUFF_CMD_SIZE	BITMASK(31, 24)
#घोषणा RTL_REV_CAP_TX_BUFF_SIZE	BITMASK(15, 0)

#घोषणा CDNSP_VER_1 0x00000000
#घोषणा CDNSP_VER_2 0x10000000

#घोषणा CDNSP_IF_EP_EXIST(pdev, ep_num, dir) \
			 (पढ़ोl(&(pdev)->rev_cap->ep_supported) & \
			 (BIT(ep_num) << ((dir) ? 0 : 16)))

/**
 * काष्ठा cdnsp_rev_cap - controller capabilities.
 * @ext_cap: Header क्रम RTL Revision Extended Capability.
 * @rtl_revision: RTL revision.
 * @rx_buff_size: Rx buffer sizes.
 * @tx_buff_size: Tx buffer sizes.
 * @ep_supported: Supported endpoपूर्णांकs.
 * @ctrl_revision: Controller revision ID.
 */
काष्ठा cdnsp_rev_cap अणु
	__le32 ext_cap;
	__le32 rtl_revision;
	__le32 rx_buff_size;
	__le32 tx_buff_size;
	__le32 ep_supported;
	__le32 ctrl_revision;
पूर्ण;

/* USB2.0 Port Peripheral Configuration Registers. */
#घोषणा D_XEC_PRE_REGS_CAP		0xC8
#घोषणा REG_CHICKEN_BITS_2_OFFSET	0x48
#घोषणा CHICKEN_XDMA_2_TP_CACHE_DIS	BIT(28)

/* XBUF Extended Capability ID. */
#घोषणा XBUF_CAP_ID			0xCB
#घोषणा XBUF_RX_TAG_MASK_0_OFFSET	0x1C
#घोषणा XBUF_RX_TAG_MASK_1_OFFSET	0x24
#घोषणा XBUF_TX_CMD_OFFSET		0x2C

/**
 * काष्ठा cdnsp_करोorbell_array.
 * @cmd_db: Command ring करोorbell रेजिस्टर.
 * @ep_db: Endpoपूर्णांक ring करोorbell रेजिस्टर.
 *         Bits 0 - 7: Endpoपूर्णांक target.
 *         Bits 8 - 15: RsvdZ.
 *         Bits 16 - 31: Stream ID.
 */
काष्ठा cdnsp_करोorbell_array अणु
	__le32 cmd_db;
	__le32 ep_db;
पूर्ण;

#घोषणा DB_VALUE(ep, stream)		((((ep) + 1) & 0xff) | ((stream) << 16))
#घोषणा DB_VALUE_EP0_OUT(ep, stream)	((ep) & 0xff)
#घोषणा DB_VALUE_CMD			0x00000000

/**
 * काष्ठा cdnsp_container_ctx.
 * @type: Type of context. Used to calculated offsets to contained contexts.
 * @size: Size of the context data.
 * @ctx_size: context data काष्ठाure size - 64 or 32 bits.
 * @dma: dma address of the bytes.
 * @bytes: The raw context data given to HW.
 *
 * Represents either a Device or Input context. Holds a poपूर्णांकer to the raw
 * memory used क्रम the context (bytes) and dma address of it (dma).
 */
काष्ठा cdnsp_container_ctx अणु
	अचिन्हित पूर्णांक type;
#घोषणा CDNSP_CTX_TYPE_DEVICE	0x1
#घोषणा CDNSP_CTX_TYPE_INPUT	0x2
	पूर्णांक size;
	पूर्णांक ctx_size;
	dma_addr_t dma;
	u8 *bytes;
पूर्ण;

/**
 * काष्ठा cdnsp_slot_ctx
 * @dev_info: Device speed, and last valid endpoपूर्णांक.
 * @dev_port: Device port number that is needed to access the USB device.
 * @पूर्णांक_target: Interrupter target number.
 * @dev_state: Slot state and device address.
 *
 * Slot Context - This assumes the controller uses 32-byte context
 * काष्ठाures. If the controller uses 64-byte contexts, there is an additional
 * 32 bytes reserved at the end of the slot context क्रम controller पूर्णांकernal use.
 */
काष्ठा cdnsp_slot_ctx अणु
	__le32 dev_info;
	__le32 dev_port;
	__le32 पूर्णांक_target;
	__le32 dev_state;
	/* offset 0x10 to 0x1f reserved क्रम controller पूर्णांकernal use. */
	__le32 reserved[4];
पूर्ण;

/* Bits 20:23 in the Slot Context are the speed क्रम the device. */
#घोषणा SLOT_SPEED_FS		(XDEV_FS << 10)
#घोषणा SLOT_SPEED_HS		(XDEV_HS << 10)
#घोषणा SLOT_SPEED_SS		(XDEV_SS << 10)
#घोषणा SLOT_SPEED_SSP		(XDEV_SSP << 10)

/* dev_info biपंचांगasks. */
/* Device speed - values defined by PORTSC Device Speed field - 20:23. */
#घोषणा DEV_SPEED		GENMASK(23, 20)
#घोषणा GET_DEV_SPEED(n)	(((n) & DEV_SPEED) >> 20)
/* Index of the last valid endpoपूर्णांक context in this device context - 27:31. */
#घोषणा LAST_CTX_MASK		((अचिन्हित पूर्णांक)GENMASK(31, 27))
#घोषणा LAST_CTX(p)		((p) << 27)
#घोषणा LAST_CTX_TO_EP_NUM(p)	(((p) >> 27) - 1)
#घोषणा SLOT_FLAG		BIT(0)
#घोषणा EP0_FLAG		BIT(1)

/* dev_port biपंचांगasks */
/* Device port number that is needed to access the USB device. */
#घोषणा DEV_PORT(p)		(((p) & 0xff) << 16)

/* dev_state biपंचांगasks */
/* USB device address - asचिन्हित by the controller. */
#घोषणा DEV_ADDR_MASK		GENMASK(7, 0)
/* Slot state */
#घोषणा SLOT_STATE		GENMASK(31, 27)
#घोषणा GET_SLOT_STATE(p)	(((p) & SLOT_STATE) >> 27)

#घोषणा SLOT_STATE_DISABLED	0
#घोषणा SLOT_STATE_ENABLED	SLOT_STATE_DISABLED
#घोषणा SLOT_STATE_DEFAULT	1
#घोषणा SLOT_STATE_ADDRESSED	2
#घोषणा SLOT_STATE_CONFIGURED	3

/**
 * काष्ठा cdnsp_ep_ctx.
 * @ep_info: Endpoपूर्णांक state, streams, mult, and पूर्णांकerval inक्रमmation.
 * @ep_info2: Inक्रमmation on endpoपूर्णांक type, max packet size, max burst size,
 *            error count, and whether the controller will क्रमce an event क्रम
 *            all transactions.
 * @deq: 64-bit ring dequeue poपूर्णांकer address. If the endpoपूर्णांक only
 *       defines one stream, this poपूर्णांकs to the endpoपूर्णांक transfer ring.
 *       Otherwise, it poपूर्णांकs to a stream context array, which has a
 *       ring poपूर्णांकer क्रम each flow.
 * @tx_info: Average TRB lengths क्रम the endpoपूर्णांक ring and
 *	     max payload within an Endpoपूर्णांक Service Interval Time (ESIT).
 *
 * Endpoपूर्णांक Context - This assumes the controller uses 32-byte context
 * काष्ठाures. If the controller uses 64-byte contexts, there is an additional
 * 32 bytes reserved at the end of the endpoपूर्णांक context क्रम controller पूर्णांकernal
 * use.
 */
काष्ठा cdnsp_ep_ctx अणु
	__le32 ep_info;
	__le32 ep_info2;
	__le64 deq;
	__le32 tx_info;
	/* offset 0x14 - 0x1f reserved क्रम controller पूर्णांकernal use. */
	__le32 reserved[3];
पूर्ण;

/* ep_info biपंचांगasks. */
/*
 * Endpoपूर्णांक State - bits 0:2:
 * 0 - disabled
 * 1 - running
 * 2 - halted due to halt condition
 * 3 - stopped
 * 4 - TRB error
 * 5-7 - reserved
 */
#घोषणा EP_STATE_MASK		GENMASK(3, 0)
#घोषणा EP_STATE_DISABLED	0
#घोषणा EP_STATE_RUNNING	1
#घोषणा EP_STATE_HALTED		2
#घोषणा EP_STATE_STOPPED	3
#घोषणा EP_STATE_ERROR		4
#घोषणा GET_EP_CTX_STATE(ctx)	(le32_to_cpu((ctx)->ep_info) & EP_STATE_MASK)

/* Mult - Max number of burst within an पूर्णांकerval, in EP companion desc. */
#घोषणा EP_MULT(p)			(((p) << 8) & GENMASK(9, 8))
#घोषणा CTX_TO_EP_MULT(p)		(((p) & GENMASK(9, 8)) >> 8)
/* bits 10:14 are Max Primary Streams. */
/* bit 15 is Linear Stream Array. */
/* Interval - period between requests to an endpoपूर्णांक - 125u increments. */
#घोषणा EP_INTERVAL(p)			(((p) << 16) & GENMASK(23, 16))
#घोषणा EP_INTERVAL_TO_UFRAMES(p)	(1 << (((p) & GENMASK(23, 16)) >> 16))
#घोषणा CTX_TO_EP_INTERVAL(p)		(((p) & GENMASK(23, 16)) >> 16)
#घोषणा EP_MAXPSTREAMS_MASK		GENMASK(14, 10)
#घोषणा EP_MAXPSTREAMS(p)		(((p) << 10) & EP_MAXPSTREAMS_MASK)
#घोषणा CTX_TO_EP_MAXPSTREAMS(p)	(((p) & EP_MAXPSTREAMS_MASK) >> 10)
/* Endpoपूर्णांक is set up with a Linear Stream Array (vs. Secondary Stream Array) */
#घोषणा EP_HAS_LSA			BIT(15)

/* ep_info2 biपंचांगasks */
#घोषणा ERROR_COUNT(p)		(((p) & 0x3) << 1)
#घोषणा CTX_TO_EP_TYPE(p)	(((p) >> 3) & 0x7)
#घोषणा EP_TYPE(p)		((p) << 3)
#घोषणा ISOC_OUT_EP		1
#घोषणा BULK_OUT_EP		2
#घोषणा INT_OUT_EP		3
#घोषणा CTRL_EP			4
#घोषणा ISOC_IN_EP		5
#घोषणा BULK_IN_EP		6
#घोषणा INT_IN_EP		7
/* bit 6 reserved. */
/* bit 7 is Device Initiate Disable - क्रम disabling stream selection. */
#घोषणा MAX_BURST(p)		(((p) << 8) & GENMASK(15, 8))
#घोषणा CTX_TO_MAX_BURST(p)	(((p) & GENMASK(15, 8)) >> 8)
#घोषणा MAX_PACKET(p)		(((p) << 16) & GENMASK(31, 16))
#घोषणा MAX_PACKET_MASK		GENMASK(31, 16)
#घोषणा MAX_PACKET_DECODED(p)	(((p) & GENMASK(31, 16)) >> 16)

/* tx_info biपंचांगasks. */
#घोषणा EP_AVG_TRB_LENGTH(p)		((p) & GENMASK(15, 0))
#घोषणा EP_MAX_ESIT_PAYLOAD_LO(p)	(((p) << 16) & GENMASK(31, 16))
#घोषणा EP_MAX_ESIT_PAYLOAD_HI(p)	((((p) & GENMASK(23, 16)) >> 16) << 24)
#घोषणा CTX_TO_MAX_ESIT_PAYLOAD_LO(p)	(((p) & GENMASK(31, 16)) >> 16)
#घोषणा CTX_TO_MAX_ESIT_PAYLOAD_HI(p)	(((p) & GENMASK(31, 24)) >> 24)

/* deq biपंचांगasks. */
#घोषणा EP_CTX_CYCLE_MASK		BIT(0)
#घोषणा CTX_DEQ_MASK			(~0xfL)

/**
 * काष्ठा cdnsp_input_control_context
 * Input control context;
 *
 * @drop_context: Set the bit of the endpoपूर्णांक context you want to disable.
 * @add_context: Set the bit of the endpoपूर्णांक context you want to enable.
 */
काष्ठा cdnsp_input_control_ctx अणु
	__le32 drop_flags;
	__le32 add_flags;
	__le32 rsvd2[6];
पूर्ण;

/**
 * Represents everything that is needed to issue a command on the command ring.
 *
 * @in_ctx: Poपूर्णांकer to input context काष्ठाure.
 * @status: Command Completion Code क्रम last command.
 * @command_trb: Poपूर्णांकer to command TRB.
 */
काष्ठा cdnsp_command अणु
	/* Input context क्रम changing device state. */
	काष्ठा cdnsp_container_ctx *in_ctx;
	u32 status;
	जोड़ cdnsp_trb *command_trb;
पूर्ण;

/**
 * Stream context काष्ठाure.
 *
 * @stream_ring: 64-bit stream ring address, cycle state, and stream type.
 * @reserved: offset 0x14 - 0x1f reserved क्रम controller पूर्णांकernal use.
 */
काष्ठा cdnsp_stream_ctx अणु
	__le64 stream_ring;
	__le32 reserved[2];
पूर्ण;

/* Stream Context Types - bits 3:1 of stream ctx deq ptr. */
#घोषणा SCT_FOR_CTX(p)		(((p) << 1) & GENMASK(3, 1))
/* Secondary stream array type, dequeue poपूर्णांकer is to a transfer ring. */
#घोषणा SCT_SEC_TR		0
/* Primary stream array type, dequeue poपूर्णांकer is to a transfer ring. */
#घोषणा SCT_PRI_TR		1

/**
 *  काष्ठा cdnsp_stream_info: Representing everything that is needed to
 *                            supports stream capable endpoपूर्णांकs.
 *  @stream_rings: Array of poपूर्णांकers containing Transfer rings क्रम all
 *                 supported streams.
 *  @num_streams: Number of streams, including stream 0.
 *  @stream_ctx_array: The stream context array may be bigger than the number
 *                     of streams the driver asked क्रम.
 *  @num_stream_ctxs: Number of streams.
 *  @ctx_array_dma: Dma address of Context Stream Array.
 *  @trb_address_map: For mapping physical TRB addresses to segments in
 *                    stream rings.
 *  @td_count: Number of TDs associated with endpoपूर्णांक.
 *  @first_prime_det: First PRIME packet detected.
 *  @drbls_count: Number of allowed करोorbells.
 */
काष्ठा cdnsp_stream_info अणु
	काष्ठा cdnsp_ring **stream_rings;
	अचिन्हित पूर्णांक num_streams;
	काष्ठा cdnsp_stream_ctx *stream_ctx_array;
	अचिन्हित पूर्णांक num_stream_ctxs;
	dma_addr_t ctx_array_dma;
	काष्ठा radix_tree_root trb_address_map;
	पूर्णांक td_count;
	u8 first_prime_det;
#घोषणा STREAM_DRBL_FIFO_DEPTH 2
	u8 drbls_count;
पूर्ण;

#घोषणा STREAM_LOG_STREAMS 4
#घोषणा STREAM_NUM_STREAMS BIT(STREAM_LOG_STREAMS)

#अगर STREAM_LOG_STREAMS > 16 && STREAM_LOG_STREAMS < 1
#त्रुटि "Not suupported stream value"
#पूर्ण_अगर

/**
 * काष्ठा cdnsp_ep - extended device side representation of USB endpoपूर्णांक.
 * @endpoपूर्णांक: usb endpoपूर्णांक
 * @pending_req_list: List of requests queuing on transfer ring.
 * @pdev: Device associated with this endpoपूर्णांक.
 * @number: Endpoपूर्णांक number (1 - 15).
 * idx: The device context index (DCI).
 * पूर्णांकerval: Interval between packets used क्रम ISOC endpoपूर्णांक.
 * @name: A human पढ़ोable name e.g. ep1out.
 * @direction: Endpoपूर्णांक direction.
 * @buffering: Number of on-chip buffers related to endpoपूर्णांक.
 * @buffering_period; Number of on-chip buffers related to periodic endpoपूर्णांक.
 * @in_ctx: Poपूर्णांकer to input endpoपूर्णांक context काष्ठाure.
 * @out_ctx: Poपूर्णांकer to output endpoपूर्णांक context काष्ठाure.
 * @ring: Poपूर्णांकer to transfer ring.
 * @stream_info: Hold stream inक्रमmation.
 * @ep_state: Current state of endpoपूर्णांक.
 * @skip: Someबार the controller can not process isochronous endpoपूर्णांक ring
 *        quickly enough, and it will miss some isoc tds on the ring and
 *        generate Missed Service Error Event.
 *        Set skip flag when receive a Missed Service Error Event and
 *        process the missed tds on the endpoपूर्णांक ring.
 */
काष्ठा cdnsp_ep अणु
	काष्ठा usb_ep endpoपूर्णांक;
	काष्ठा list_head pending_list;
	काष्ठा cdnsp_device *pdev;
	u8 number;
	u8 idx;
	u32 पूर्णांकerval;
	अक्षर name[20];
	u8 direction;
	u8 buffering;
	u8 buffering_period;
	काष्ठा cdnsp_ep_ctx *in_ctx;
	काष्ठा cdnsp_ep_ctx *out_ctx;
	काष्ठा cdnsp_ring *ring;
	काष्ठा cdnsp_stream_info stream_info;
	अचिन्हित पूर्णांक ep_state;
#घोषणा EP_ENABLED		BIT(0)
#घोषणा EP_DIS_IN_RROGRESS	BIT(1)
#घोषणा EP_HALTED		BIT(2)
#घोषणा EP_STOPPED		BIT(3)
#घोषणा EP_WEDGE		BIT(4)
#घोषणा EP0_HALTED_STATUS	BIT(5)
#घोषणा EP_HAS_STREAMS		BIT(6)
#घोषणा EP_UNCONFIGURED		BIT(7)

	bool skip;
पूर्ण;

/**
 * काष्ठा cdnsp_device_context_array
 * @dev_context_ptr: Array of 64-bit DMA addresses क्रम device contexts.
 * @dma: DMA address क्रम device contexts काष्ठाure.
 */
काष्ठा cdnsp_device_context_array अणु
	__le64 dev_context_ptrs[CDNSP_DEV_MAX_SLOTS + 1];
	dma_addr_t dma;
पूर्ण;

/**
 * काष्ठा cdnsp_transfer_event.
 * @buffer: 64-bit buffer address, or immediate data.
 * @transfer_len: Data length transferred.
 * @flags: Field is पूर्णांकerpreted dअगरferently based on the type of TRB.
 */
काष्ठा cdnsp_transfer_event अणु
	__le64 buffer;
	__le32 transfer_len;
	__le32 flags;
पूर्ण;

/* Invalidate event after disabling endpoपूर्णांक. */
#घोषणा TRB_EVENT_INVALIDATE 8

/* Transfer event TRB length bit mask. */
/* bits 0:23 */
#घोषणा EVENT_TRB_LEN(p)			((p) & GENMASK(23, 0))
/* Completion Code - only applicable क्रम some types of TRBs */
#घोषणा COMP_CODE_MASK				(0xff << 24)
#घोषणा GET_COMP_CODE(p)			(((p) & COMP_CODE_MASK) >> 24)
#घोषणा COMP_INVALID				0
#घोषणा COMP_SUCCESS				1
#घोषणा COMP_DATA_BUFFER_ERROR			2
#घोषणा COMP_BABBLE_DETECTED_ERROR		3
#घोषणा COMP_TRB_ERROR				5
#घोषणा COMP_RESOURCE_ERROR			7
#घोषणा COMP_NO_SLOTS_AVAILABLE_ERROR		9
#घोषणा COMP_INVALID_STREAM_TYPE_ERROR		10
#घोषणा COMP_SLOT_NOT_ENABLED_ERROR		11
#घोषणा COMP_ENDPOINT_NOT_ENABLED_ERROR		12
#घोषणा COMP_SHORT_PACKET			13
#घोषणा COMP_RING_UNDERRUN			14
#घोषणा COMP_RING_OVERRUN			15
#घोषणा COMP_VF_EVENT_RING_FULL_ERROR		16
#घोषणा COMP_PARAMETER_ERROR			17
#घोषणा COMP_CONTEXT_STATE_ERROR		19
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

/*Transfer Event NRDY bit fields */
#घोषणा TRB_TO_DEV_STREAM(p)			((p) & GENMASK(16, 0))
#घोषणा TRB_TO_HOST_STREAM(p)			((p) & GENMASK(16, 0))
#घोषणा STREAM_PRIME_ACK			0xFFFE
#घोषणा STREAM_REJECTED				0xFFFF

/** Transfer Event bit fields **/
#घोषणा TRB_TO_EP_ID(p)				(((p) & GENMASK(20, 16)) >> 16)

/**
 * काष्ठा cdnsp_link_trb
 * @segment_ptr: 64-bit segment poपूर्णांकer.
 * @पूर्णांकr_target: Interrupter target.
 * @control: Flags.
 */
काष्ठा cdnsp_link_trb अणु
	__le64 segment_ptr;
	__le32 पूर्णांकr_target;
	__le32 control;
पूर्ण;

/* control bitfields */
#घोषणा LINK_TOGGLE	BIT(1)

/**
 * काष्ठा cdnsp_event_cmd - Command completion event TRB.
 * cmd_trb: Poपूर्णांकer to command TRB, or the value passed by the event data trb
 * status: Command completion parameters and error code.
 * flags: Flags.
 */
काष्ठा cdnsp_event_cmd अणु
	__le64 cmd_trb;
	__le32 status;
	__le32 flags;
पूर्ण;

/* flags biपंचांगasks */

/* Address device - disable SetAddress. */
#घोषणा TRB_BSR		BIT(9)

/* Configure Endpoपूर्णांक - Deconfigure. */
#घोषणा TRB_DC		BIT(9)

/* Force Header */
#घोषणा TRB_FH_TO_PACKET_TYPE(p)	((p) & GENMASK(4, 0))
#घोषणा TRB_FH_TR_PACKET		0x4
#घोषणा TRB_FH_TO_DEVICE_ADDRESS(p)	(((p) << 25) & GENMASK(31, 25))
#घोषणा TRB_FH_TR_PACKET_DEV_NOT	0x6
#घोषणा TRB_FH_TO_NOT_TYPE(p)		(((p) << 4) & GENMASK(7, 4))
#घोषणा TRB_FH_TR_PACKET_FUNCTION_WAKE	0x1
#घोषणा TRB_FH_TO_INTERFACE(p)		(((p) << 8) & GENMASK(15, 8))

क्रमागत cdnsp_setup_dev अणु
	SETUP_CONTEXT_ONLY,
	SETUP_CONTEXT_ADDRESS,
पूर्ण;

/* bits 24:31 are the slot ID. */
#घोषणा TRB_TO_SLOT_ID(p)		(((p) & GENMASK(31, 24)) >> 24)
#घोषणा SLOT_ID_FOR_TRB(p)		(((p) << 24) & GENMASK(31, 24))

/* Stop Endpoपूर्णांक TRB - ep_index to endpoपूर्णांक ID क्रम this TRB. */
#घोषणा TRB_TO_EP_INDEX(p)		(((p) >> 16) & 0x1f)

#घोषणा EP_ID_FOR_TRB(p)		((((p) + 1) << 16) & GENMASK(20, 16))

#घोषणा SUSPEND_PORT_FOR_TRB(p)		(((p) & 1) << 23)
#घोषणा TRB_TO_SUSPEND_PORT(p)		(((p) >> 23) & 0x1)
#घोषणा LAST_EP_INDEX			30

/* Set TR Dequeue Poपूर्णांकer command TRB fields. */
#घोषणा TRB_TO_STREAM_ID(p)		((((p) & GENMASK(31, 16)) >> 16))
#घोषणा STREAM_ID_FOR_TRB(p)		((((p)) << 16) & GENMASK(31, 16))
#घोषणा SCT_FOR_TRB(p)			(((p) << 1) & 0x7)

/* Link TRB specअगरic fields. */
#घोषणा TRB_TC				BIT(1)

/* Port Status Change Event TRB fields. */
/* Port ID - bits 31:24. */
#घोषणा GET_PORT_ID(p)			(((p) & GENMASK(31, 24)) >> 24)
#घोषणा SET_PORT_ID(p)			(((p) << 24) & GENMASK(31, 24))
#घोषणा EVENT_DATA			BIT(2)

/* Normal TRB fields. */
/* transfer_len biपंचांगasks - bits 0:16. */
#घोषणा TRB_LEN(p)			((p) & GENMASK(16, 0))
/* TD Size, packets reमुख्यing in this TD, bits 21:17 (5 bits, so max 31). */
#घोषणा TRB_TD_SIZE(p)			(min((p), (u32)31) << 17)
#घोषणा GET_TD_SIZE(p)			(((p) & GENMASK(21, 17)) >> 17)
/*
 * Controller uses the TD_SIZE field क्रम TBC अगर Extended TBC
 * is enabled (ETE).
 */
#घोषणा TRB_TD_SIZE_TBC(p)		(min((p), (u32)31) << 17)
/* Interrupter Target - which MSI-X vector to target the completion event at. */
#घोषणा TRB_INTR_TARGET(p)		(((p) << 22) & GENMASK(31, 22))
#घोषणा GET_INTR_TARGET(p)		(((p) & GENMASK(31, 22)) >> 22)
/*
 * Total burst count field, Rsvdz on controller with Extended TBC
 * enabled (ETE).
 */
#घोषणा TRB_TBC(p)			(((p) & 0x3) << 7)
#घोषणा TRB_TLBPC(p)			(((p) & 0xf) << 16)

/* Cycle bit - indicates TRB ownership by driver or driver.*/
#घोषणा TRB_CYCLE			BIT(0)
/*
 * Force next event data TRB to be evaluated beक्रमe task चयन.
 * Used to pass OS data back after a TD completes.
 */
#घोषणा TRB_ENT				BIT(1)
/* Interrupt on लघु packet. */
#घोषणा TRB_ISP				BIT(2)
/* Set PCIe no snoop attribute. */
#घोषणा TRB_NO_SNOOP			BIT(3)
/* Chain multiple TRBs पूर्णांकo a TD. */
#घोषणा TRB_CHAIN			BIT(4)
/* Interrupt on completion. */
#घोषणा TRB_IOC				BIT(5)
/* The buffer poपूर्णांकer contains immediate data. */
#घोषणा TRB_IDT				BIT(6)
/* 0 - NRDY during data stage, 1 - NRDY during status stage (only control). */
#घोषणा TRB_STAT			BIT(7)
/* Block Event Interrupt. */
#घोषणा TRB_BEI				BIT(9)

/* Control transfer TRB specअगरic fields. */
#घोषणा TRB_सूची_IN			BIT(16)

/* TRB bit mask in Data Stage TRB */
#घोषणा TRB_SETUPID_BITMASK		GENMASK(9, 8)
#घोषणा TRB_SETUPID(p)			((p) << 8)
#घोषणा TRB_SETUPID_TO_TYPE(p)		(((p) & TRB_SETUPID_BITMASK) >> 8)

#घोषणा TRB_SETUP_SPEEDID_USB3		0x1
#घोषणा TRB_SETUP_SPEEDID_USB2		0x0
#घोषणा TRB_SETUP_SPEEDID(p)		((p) & (1 << 7))

#घोषणा TRB_SETUPSTAT_ACK		0x1
#घोषणा TRB_SETUPSTAT_STALL		0x0
#घोषणा TRB_SETUPSTAT(p)		((p) << 6)

/* Isochronous TRB specअगरic fields */
#घोषणा TRB_SIA				BIT(31)
#घोषणा TRB_FRAME_ID(p)			(((p) << 20) & GENMASK(30, 20))

काष्ठा cdnsp_generic_trb अणु
	__le32 field[4];
पूर्ण;

जोड़ cdnsp_trb अणु
	काष्ठा cdnsp_link_trb link;
	काष्ठा cdnsp_transfer_event trans_event;
	काष्ठा cdnsp_event_cmd event_cmd;
	काष्ठा cdnsp_generic_trb generic;
पूर्ण;

/* TRB bit mask. */
#घोषणा TRB_TYPE_BITMASK	GENMASK(15, 10)
#घोषणा TRB_TYPE(p)		((p) << 10)
#घोषणा TRB_FIELD_TO_TYPE(p)	(((p) & TRB_TYPE_BITMASK) >> 10)

/* TRB type IDs. */
/* bulk, पूर्णांकerrupt, isoc scatter/gather, and control data stage. */
#घोषणा TRB_NORMAL		1
/* Setup Stage क्रम control transfers. */
#घोषणा TRB_SETUP		2
/* Data Stage क्रम control transfers. */
#घोषणा TRB_DATA		3
/* Status Stage क्रम control transfers. */
#घोषणा TRB_STATUS		4
/* ISOC transfers. */
#घोषणा TRB_ISOC		5
/* TRB क्रम linking ring segments. */
#घोषणा TRB_LINK		6
#घोषणा TRB_EVENT_DATA		7
/* Transfer Ring No-op (not क्रम the command ring). */
#घोषणा TRB_TR_NOOP		8

/* Command TRBs */
/* Enable Slot Command. */
#घोषणा TRB_ENABLE_SLOT		9
/* Disable Slot Command. */
#घोषणा TRB_DISABLE_SLOT	10
/* Address Device Command. */
#घोषणा TRB_ADDR_DEV		11
/* Configure Endpoपूर्णांक Command. */
#घोषणा TRB_CONFIG_EP		12
/* Evaluate Context Command. */
#घोषणा TRB_EVAL_CONTEXT	13
/* Reset Endpoपूर्णांक Command. */
#घोषणा TRB_RESET_EP		14
/* Stop Transfer Ring Command. */
#घोषणा TRB_STOP_RING		15
/* Set Transfer Ring Dequeue Poपूर्णांकer Command. */
#घोषणा TRB_SET_DEQ		16
/* Reset Device Command. */
#घोषणा TRB_RESET_DEV		17
/* Force Event Command (opt). */
#घोषणा TRB_FORCE_EVENT		18
/* Force Header Command - generate a transaction or link management packet. */
#घोषणा TRB_FORCE_HEADER	22
/* No-op Command - not क्रम transfer rings. */
#घोषणा TRB_CMD_NOOP		23
/* TRB IDs 24-31 reserved. */

/* Event TRBS. */
/* Transfer Event. */
#घोषणा TRB_TRANSFER		32
/* Command Completion Event. */
#घोषणा TRB_COMPLETION		33
/* Port Status Change Event. */
#घोषणा TRB_PORT_STATUS		34
/* Device Controller Event. */
#घोषणा TRB_HC_EVENT		37
/* MFINDEX Wrap Event - microframe counter wrapped. */
#घोषणा TRB_MFINDEX_WRAP	39
/* TRB IDs 40-47 reserved. */
/* Endpoपूर्णांक Not Ready Event. */
#घोषणा TRB_ENDPOINT_NRDY	48
/* TRB IDs 49-53 reserved. */
/* Halt Endpoपूर्णांक Command. */
#घोषणा TRB_HALT_ENDPOINT	54
/* Doorbell Overflow Event. */
#घोषणा TRB_DRB_OVERFLOW	57
/* Flush Endpoपूर्णांक Command. */
#घोषणा TRB_FLUSH_ENDPOINT	58

#घोषणा TRB_TYPE_LINK(x)	(((x) & TRB_TYPE_BITMASK) == TRB_TYPE(TRB_LINK))
#घोषणा TRB_TYPE_LINK_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
					cpu_to_le32(TRB_TYPE(TRB_LINK)))
#घोषणा TRB_TYPE_NOOP_LE32(x)	(((x) & cpu_to_le32(TRB_TYPE_BITMASK)) == \
					cpu_to_le32(TRB_TYPE(TRB_TR_NOOP)))

/*
 * TRBS_PER_SEGMENT must be a multiple of 4.
 * The command ring is 64-byte aligned, so it must also be greater than 16.
 */
#घोषणा TRBS_PER_SEGMENT		256
#घोषणा TRBS_PER_EVENT_SEGMENT		256
#घोषणा TRBS_PER_EV_DEQ_UPDATE		100
#घोषणा TRB_SEGMENT_SIZE		(TRBS_PER_SEGMENT * 16)
#घोषणा TRB_SEGMENT_SHIFT		(ilog2(TRB_SEGMENT_SIZE))
/* TRB buffer poपूर्णांकers can't cross 64KB boundaries. */
#घोषणा TRB_MAX_BUFF_SHIFT		16
#घोषणा TRB_MAX_BUFF_SIZE		BIT(TRB_MAX_BUFF_SHIFT)
/* How much data is left beक्रमe the 64KB boundary? */
#घोषणा TRB_BUFF_LEN_UP_TO_BOUNDARY(addr) (TRB_MAX_BUFF_SIZE - \
					((addr) & (TRB_MAX_BUFF_SIZE - 1)))

/**
 * काष्ठा cdnsp_segment - segment related data.
 * @trbs: Array of Transfer Request Blocks.
 * @next: Poपूर्णांकer to the next segment.
 * @dma: DMA address of current segment.
 * @bounce_dma: Bounce  buffer DMA address .
 * @bounce_buf: Bounce buffer भव address.
 * bounce_offs: Bounce buffer offset.
 * bounce_len: Bounce buffer length.
 */
काष्ठा cdnsp_segment अणु
	जोड़ cdnsp_trb *trbs;
	काष्ठा cdnsp_segment *next;
	dma_addr_t dma;
	/* Max packet sized bounce buffer क्रम td-fragmant alignment */
	dma_addr_t bounce_dma;
	व्योम *bounce_buf;
	अचिन्हित पूर्णांक bounce_offs;
	अचिन्हित पूर्णांक bounce_len;
पूर्ण;

/**
 * काष्ठा cdnsp_td - Transfer Descriptor object.
 * @td_list: Used क्रम binding TD with ep_ring->td_list.
 * @preq: Request associated with this TD
 * @start_seg: Segment containing the first_trb in TD.
 * @first_trb: First TRB क्रम this TD.
 * @last_trb: Last TRB related with TD.
 * @bounce_seg: Bounce segment क्रम this TD.
 * @request_length_set: actual_length of the request has alपढ़ोy been set.
 * @drbl - TD has been added to HW scheduler - only क्रम stream capable
 *         endpoपूर्णांकs.
 */
काष्ठा cdnsp_td अणु
	काष्ठा list_head td_list;
	काष्ठा cdnsp_request *preq;
	काष्ठा cdnsp_segment *start_seg;
	जोड़ cdnsp_trb *first_trb;
	जोड़ cdnsp_trb *last_trb;
	काष्ठा cdnsp_segment *bounce_seg;
	bool request_length_set;
	bool drbl;
पूर्ण;

/**
 * काष्ठा cdnsp_dequeue_state - New dequeue poपूर्णांकer क्रम Transfer Ring.
 * @new_deq_seg: New dequeue segment.
 * @new_deq_ptr: New dequeue poपूर्णांकer.
 * @new_cycle_state: New cycle state.
 * @stream_id: stream id क्रम which new dequeue poपूर्णांकer has been selected.
 */
काष्ठा cdnsp_dequeue_state अणु
	काष्ठा cdnsp_segment *new_deq_seg;
	जोड़ cdnsp_trb *new_deq_ptr;
	पूर्णांक new_cycle_state;
	अचिन्हित पूर्णांक stream_id;
पूर्ण;

क्रमागत cdnsp_ring_type अणु
	TYPE_CTRL = 0,
	TYPE_ISOC,
	TYPE_BULK,
	TYPE_INTR,
	TYPE_STREAM,
	TYPE_COMMAND,
	TYPE_EVENT,
पूर्ण;

/**
 * काष्ठा cdnsp_ring - inक्रमmation describing transfer, command or event ring.
 * @first_seg: First segment on transfer ring.
 * @last_seg: Last segment on transfer ring.
 * @enqueue: SW enqueue poपूर्णांकer address.
 * @enq_seg: SW enqueue segment address.
 * @dequeue: SW dequeue poपूर्णांकer address.
 * @deq_seg: SW dequeue segment address.
 * @td_list: transfer descriptor list associated with this ring.
 * @cycle_state: Current cycle bit. Write the cycle state पूर्णांकo the TRB cycle
 *               field to give ownership of the TRB to the device controller
 *               (अगर we are the producer) or to check अगर we own the TRB
 *               (अगर we are the consumer).
 * @stream_id: Stream id
 * @stream_active: Stream is active - PRIME packet has been detected.
 * @stream_rejected: This ring has been rejected by host.
 * @num_tds: Number of TDs associated with ring.
 * @num_segs: Number of segments.
 * @num_trbs_मुक्त: Number of मुक्त TRBs on the ring.
 * @bounce_buf_len: Length of bounce buffer.
 * @type: Ring type - event, transfer, or command ring.
 * @last_td_was_लघु - TD is लघु TD.
 * @trb_address_map: For mapping physical TRB addresses to segments in
 *                   stream rings.
 */
काष्ठा cdnsp_ring अणु
	काष्ठा cdnsp_segment *first_seg;
	काष्ठा cdnsp_segment *last_seg;
	जोड़ cdnsp_trb	 *enqueue;
	काष्ठा cdnsp_segment *enq_seg;
	जोड़ cdnsp_trb	 *dequeue;
	काष्ठा cdnsp_segment *deq_seg;
	काष्ठा list_head td_list;
	u32 cycle_state;
	अचिन्हित पूर्णांक stream_id;
	अचिन्हित पूर्णांक stream_active;
	अचिन्हित पूर्णांक stream_rejected;
	पूर्णांक num_tds;
	अचिन्हित पूर्णांक num_segs;
	अचिन्हित पूर्णांक num_trbs_मुक्त;
	अचिन्हित पूर्णांक bounce_buf_len;
	क्रमागत cdnsp_ring_type type;
	bool last_td_was_लघु;
	काष्ठा radix_tree_root *trb_address_map;
पूर्ण;

/**
 * काष्ठा cdnsp_erst_entry - even ring segment table entry object.
 * @seg_addr: 64-bit event ring segment address.
 * seg_size: Number of TRBs in segment.;
 */
काष्ठा cdnsp_erst_entry अणु
	__le64 seg_addr;
	__le32 seg_size;
	/* Set to zero */
	__le32 rsvd;
पूर्ण;

/**
 * काष्ठा cdnsp_erst - even ring segment table क्रम event ring.
 * @entries: Array of event ring segments
 * @num_entries: Number of segments in entries array.
 * @erst_dma_addr: DMA address क्रम entries array.
 */
काष्ठा cdnsp_erst अणु
	काष्ठा cdnsp_erst_entry *entries;
	अचिन्हित पूर्णांक num_entries;
	dma_addr_t erst_dma_addr;
पूर्ण;

/**
 * काष्ठा cdnsp_request - extended device side representation of usb_request
 *                        object .
 * @td: Transfer descriptor associated with this request.
 * @request: Generic usb_request object describing single I/O request.
 * @list: Used to adding request to endpoपूर्णांक pending_list.
 * @pep: Extended representation of usb_ep object
 * @epnum: Endpoपूर्णांक number associated with usb request.
 * @direction: Endpoपूर्णांक direction क्रम usb request.
 */
काष्ठा cdnsp_request अणु
	काष्ठा	cdnsp_td td;
	काष्ठा usb_request request;
	काष्ठा list_head list;
	काष्ठा cdnsp_ep	 *pep;
	u8 epnum;
	अचिन्हित direction:1;
पूर्ण;

#घोषणा	ERST_NUM_SEGS	1

/* Stages used during क्रमागतeration process.*/
क्रमागत cdnsp_ep0_stage अणु
	CDNSP_SETUP_STAGE,
	CDNSP_DATA_STAGE,
	CDNSP_STATUS_STAGE,
पूर्ण;

/**
 * काष्ठा cdnsp_port - holds inक्रमmation about detected ports.
 * @port_num: Port number.
 * @exist: Indicate अगर port exist.
 * maj_rev: Major revision.
 * min_rev: Minor revision.
 */
काष्ठा cdnsp_port अणु
	काष्ठा cdnsp_port_regs __iomem *regs;
	u8 port_num;
	u8 exist;
	u8 maj_rev;
	u8 min_rev;
पूर्ण;

#घोषणा CDNSP_EXT_PORT_MAJOR(x)		(((x) >> 24) & 0xff)
#घोषणा CDNSP_EXT_PORT_MINOR(x)		(((x) >> 16) & 0xff)
#घोषणा CDNSP_EXT_PORT_OFF(x)		((x) & 0xff)
#घोषणा CDNSP_EXT_PORT_COUNT(x)		(((x) >> 8) & 0xff)

/**
 * काष्ठा cdnsp_device - represent USB device.
 * @dev: Poपूर्णांकer to device काष्ठाure associated whit this controller.
 * @gadget: Device side representation of the peripheral controller.
 * @gadget_driver: Poपूर्णांकer to the gadget driver.
 * @irq: IRQ line number used by device side.
 * @regs:IO device memory.
 * @cap_regs: Capability रेजिस्टरs.
 * @op_regs: Operational रेजिस्टरs.
 * @run_regs: Runसमय रेजिस्टरs.
 * @dba: Device base address रेजिस्टर.
 * @ir_set: Current पूर्णांकerrupter रेजिस्टर set.
 * @port20_regs: Port 2.0 Peripheral Configuration Registers.
 * @port3x_regs: USB3.x Port Peripheral Configuration Registers.
 * @rev_cap: Controller Capabilities Registers.
 * @hcs_params1: Cached रेजिस्टर copies of पढ़ो-only HCSPARAMS1
 * @hcc_params: Cached रेजिस्टर copies of पढ़ो-only HCCPARAMS1
 * @setup: Temporary buffer क्रम setup packet.
 * @ep0_preq: Internal allocated request used during क्रमागतeration.
 * @ep0_stage: ep0 stage during क्रमागतeration process.
 * @three_stage_setup: Three state or two state setup.
 * @ep0_expect_in: Data IN expected क्रम control transfer.
 * @setup_id: Setup identअगरier.
 * @setup_speed - Speed detected क्रम current SETUP packet.
 * @setup_buf: Buffer क्रम SETUP packet.
 * @device_address: Current device address.
 * @may_wakeup: remote wakeup enabled/disabled.
 * @lock: Lock used in पूर्णांकerrupt thपढ़ो context.
 * @hci_version: device controller version.
 * @dcbaa: Device context base address array.
 * @cmd_ring: Command ring.
 * @cmd: Represent all what is needed to issue command on Command Ring.
 * @event_ring: Event ring.
 * @erst: Event Ring Segment table
 * @slot_id: Current Slot ID. Should be 0 or 1.
 * @out_ctx: Output context.
 * @in_ctx: Input context.
 * @eps: array of endpoपूर्णांकs object associated with device.
 * @usb2_hw_lpm_capable: hardware lpm is enabled;
 * @u1_allowed: Allow device transition to U1 state.
 * @u2_allowed: Allow device transition to U2 state
 * @device_pool: DMA pool क्रम allocating input and output context.
 * @segment_pool: DMA pool क्रम allocating new segments.
 * @cdnsp_state: Current state of controller.
 * @link_state: Current link state.
 * @usb2_port - Port USB 2.0.
 * @usb3_port - Port USB 3.0.
 * @active_port - Current selected Port.
 * @test_mode: selected Test Mode.
 */
काष्ठा cdnsp_device अणु
	काष्ठा device *dev;
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *gadget_driver;
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *regs;

	/* Registers map */
	काष्ठा cdnsp_cap_regs __iomem *cap_regs;
	काष्ठा cdnsp_op_regs __iomem *op_regs;
	काष्ठा cdnsp_run_regs __iomem *run_regs;
	काष्ठा cdnsp_करोorbell_array __iomem *dba;
	काष्ठा	cdnsp_पूर्णांकr_reg __iomem *ir_set;
	काष्ठा cdnsp_20port_cap __iomem *port20_regs;
	काष्ठा cdnsp_3xport_cap __iomem *port3x_regs;
	काष्ठा cdnsp_rev_cap __iomem *rev_cap;

	/* Cached रेजिस्टर copies of पढ़ो-only CDNSP data */
	__u32 hcs_params1;
	__u32 hcs_params3;
	__u32 hcc_params;
	/* Lock used in पूर्णांकerrupt thपढ़ो context. */
	spinlock_t lock;
	काष्ठा usb_ctrlrequest setup;
	काष्ठा cdnsp_request ep0_preq;
	क्रमागत cdnsp_ep0_stage ep0_stage;
	u8 three_stage_setup;
	u8 ep0_expect_in;
	u8 setup_id;
	u8 setup_speed;
	व्योम *setup_buf;
	u8 device_address;
	पूर्णांक may_wakeup;
	u16 hci_version;

	/* data काष्ठाures */
	काष्ठा cdnsp_device_context_array *dcbaa;
	काष्ठा cdnsp_ring *cmd_ring;
	काष्ठा cdnsp_command cmd;
	काष्ठा cdnsp_ring *event_ring;
	काष्ठा cdnsp_erst erst;
	पूर्णांक slot_id;

	/*
	 * Commands to the hardware are passed an "input context" that
	 * tells the hardware what to change in its data काष्ठाures.
	 * The hardware will वापस changes in an "output context" that
	 * software must allocate क्रम the hardware. .
	 */
	काष्ठा cdnsp_container_ctx out_ctx;
	काष्ठा cdnsp_container_ctx in_ctx;
	काष्ठा cdnsp_ep eps[CDNSP_ENDPOINTS_NUM];
	u8 usb2_hw_lpm_capable:1;
	u8 u1_allowed:1;
	u8 u2_allowed:1;

	/* DMA pools */
	काष्ठा dma_pool *device_pool;
	काष्ठा dma_pool	*segment_pool;

#घोषणा CDNSP_STATE_HALTED		BIT(1)
#घोषणा CDNSP_STATE_DYING		BIT(2)
#घोषणा CDNSP_STATE_DISCONNECT_PENDING	BIT(3)
#घोषणा CDNSP_WAKEUP_PENDING		BIT(4)
	अचिन्हित पूर्णांक cdnsp_state;
	अचिन्हित पूर्णांक link_state;

	काष्ठा cdnsp_port usb2_port;
	काष्ठा cdnsp_port usb3_port;
	काष्ठा cdnsp_port *active_port;
	u16 test_mode;
पूर्ण;

/*
 * Registers should always be accessed with द्विगुन word or quad word accesses.
 *
 * Registers with 64-bit address poपूर्णांकers should be written to with
 * dword accesses by writing the low dword first (ptr[0]), then the high dword
 * (ptr[1]) second. controller implementations that करो not support 64-bit
 * address poपूर्णांकers will ignore the high dword, and ग_लिखो order is irrelevant.
 */
अटल अंतरभूत u64 cdnsp_पढ़ो_64(__le64 __iomem *regs)
अणु
	वापस lo_hi_पढ़ोq(regs);
पूर्ण

अटल अंतरभूत व्योम cdnsp_ग_लिखो_64(स्थिर u64 val, __le64 __iomem *regs)
अणु
	lo_hi_ग_लिखोq(val, regs);
पूर्ण

/* CDNSP memory management functions. */
व्योम cdnsp_mem_cleanup(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_mem_init(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_setup_addressable_priv_dev(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_copy_ep0_dequeue_पूर्णांकo_input_ctx(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_endpoपूर्णांक_zero(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *ep);
पूर्णांक cdnsp_endpoपूर्णांक_init(काष्ठा cdnsp_device *pdev,
			काष्ठा cdnsp_ep *pep,
			gfp_t mem_flags);
पूर्णांक cdnsp_ring_expansion(काष्ठा cdnsp_device *pdev,
			 काष्ठा cdnsp_ring *ring,
			 अचिन्हित पूर्णांक num_trbs, gfp_t flags);
काष्ठा cdnsp_ring *cdnsp_dma_to_transfer_ring(काष्ठा cdnsp_ep *ep, u64 address);
पूर्णांक cdnsp_alloc_stream_info(काष्ठा cdnsp_device *pdev,
			    काष्ठा cdnsp_ep *pep,
			    अचिन्हित पूर्णांक num_stream_ctxs,
			    अचिन्हित पूर्णांक num_streams);
पूर्णांक cdnsp_alloc_streams(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep);
व्योम cdnsp_मुक्त_endpoपूर्णांक_rings(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep);

/* Device controller glue. */
पूर्णांक cdnsp_find_next_ext_cap(व्योम __iomem *base, u32 start, पूर्णांक id);
पूर्णांक cdnsp_halt(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_died(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_reset(काष्ठा cdnsp_device *pdev);
irqवापस_t cdnsp_irq_handler(पूर्णांक irq, व्योम *priv);
पूर्णांक cdnsp_setup_device(काष्ठा cdnsp_device *pdev, क्रमागत cdnsp_setup_dev setup);
व्योम cdnsp_set_usb2_hardware_lpm(काष्ठा cdnsp_device *usbsssp_data,
				 काष्ठा usb_request *req, पूर्णांक enable);
irqवापस_t cdnsp_thपढ़ो_irq_handler(पूर्णांक irq, व्योम *data);

/* Ring, segment, TRB, and TD functions. */
dma_addr_t cdnsp_trb_virt_to_dma(काष्ठा cdnsp_segment *seg,
				 जोड़ cdnsp_trb *trb);
bool cdnsp_last_trb_on_seg(काष्ठा cdnsp_segment *seg, जोड़ cdnsp_trb *trb);
bool cdnsp_last_trb_on_ring(काष्ठा cdnsp_ring *ring,
			    काष्ठा cdnsp_segment *seg,
			    जोड़ cdnsp_trb *trb);
पूर्णांक cdnsp_रुको_क्रम_cmd_compl(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_update_erst_dequeue(काष्ठा cdnsp_device *pdev,
			       जोड़ cdnsp_trb *event_ring_deq,
			       u8 clear_ehb);
व्योम cdnsp_initialize_ring_info(काष्ठा cdnsp_ring *ring);
व्योम cdnsp_ring_cmd_db(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_queue_slot_control(काष्ठा cdnsp_device *pdev, u32 trb_type);
व्योम cdnsp_queue_address_device(काष्ठा cdnsp_device *pdev,
				dma_addr_t in_ctx_ptr,
				क्रमागत cdnsp_setup_dev setup);
व्योम cdnsp_queue_stop_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
			       अचिन्हित पूर्णांक ep_index);
पूर्णांक cdnsp_queue_ctrl_tx(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_request *preq);
पूर्णांक cdnsp_queue_bulk_tx(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_request *preq);
पूर्णांक cdnsp_queue_isoc_tx_prepare(काष्ठा cdnsp_device *pdev,
				काष्ठा cdnsp_request *preq);
व्योम cdnsp_queue_configure_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
				    dma_addr_t in_ctx_ptr);
व्योम cdnsp_queue_reset_ep(काष्ठा cdnsp_device *pdev, अचिन्हित पूर्णांक ep_index);
व्योम cdnsp_queue_halt_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
			       अचिन्हित पूर्णांक ep_index);
व्योम cdnsp_queue_flush_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
				अचिन्हित पूर्णांक ep_index);
व्योम cdnsp_क्रमce_header_wakeup(काष्ठा cdnsp_device *pdev, पूर्णांक पूर्णांकf_num);
व्योम cdnsp_queue_reset_device(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_queue_new_dequeue_state(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep,
				   काष्ठा cdnsp_dequeue_state *deq_state);
व्योम cdnsp_ring_करोorbell_क्रम_active_rings(काष्ठा cdnsp_device *pdev,
					  काष्ठा cdnsp_ep *pep);
व्योम cdnsp_inc_deq(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ring *ring);
व्योम cdnsp_set_link_state(काष्ठा cdnsp_device *pdev,
			  __le32 __iomem *port_regs, u32 link_state);
u32 cdnsp_port_state_to_neutral(u32 state);

/* CDNSP device controller contexts. */
पूर्णांक cdnsp_enable_slot(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_disable_slot(काष्ठा cdnsp_device *pdev);
काष्ठा cdnsp_input_control_ctx
	*cdnsp_get_input_control_ctx(काष्ठा cdnsp_container_ctx *ctx);
काष्ठा cdnsp_slot_ctx *cdnsp_get_slot_ctx(काष्ठा cdnsp_container_ctx *ctx);
काष्ठा cdnsp_ep_ctx *cdnsp_get_ep_ctx(काष्ठा cdnsp_container_ctx *ctx,
				      अचिन्हित पूर्णांक ep_index);
/* CDNSP gadget पूर्णांकerface. */
व्योम cdnsp_suspend_gadget(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_resume_gadget(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_disconnect_gadget(काष्ठा cdnsp_device *pdev);
व्योम cdnsp_gadget_giveback(काष्ठा cdnsp_ep *pep, काष्ठा cdnsp_request *preq,
			   पूर्णांक status);
पूर्णांक cdnsp_ep_enqueue(काष्ठा cdnsp_ep *pep, काष्ठा cdnsp_request *preq);
पूर्णांक cdnsp_ep_dequeue(काष्ठा cdnsp_ep *pep, काष्ठा cdnsp_request *preq);
अचिन्हित पूर्णांक cdnsp_port_speed(अचिन्हित पूर्णांक port_status);
व्योम cdnsp_irq_reset(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_halt_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
			काष्ठा cdnsp_ep *pep, पूर्णांक value);
पूर्णांक cdnsp_cmd_stop_ep(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep);
पूर्णांक cdnsp_cmd_flush_ep(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep);
व्योम cdnsp_setup_analyze(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_status_stage(काष्ठा cdnsp_device *pdev);
पूर्णांक cdnsp_reset_device(काष्ठा cdnsp_device *pdev);

/**
 * next_request - माला_लो the next request on the given list
 * @list: the request list to operate on
 *
 * Caller should take care of locking. This function वापस शून्य or the first
 * request available on list.
 */
अटल अंतरभूत काष्ठा cdnsp_request *next_request(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा cdnsp_request, list);
पूर्ण

#घोषणा to_cdnsp_ep(ep) (container_of(ep, काष्ठा cdnsp_ep, endpoपूर्णांक))
#घोषणा gadget_to_cdnsp(g) (container_of(g, काष्ठा cdnsp_device, gadget))
#घोषणा request_to_cdnsp_request(r) (container_of(r, काष्ठा cdnsp_request, \
				     request))
#घोषणा to_cdnsp_request(r) (container_of(r, काष्ठा cdnsp_request, request))
पूर्णांक cdnsp_हटाओ_request(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_request *preq,
			 काष्ठा cdnsp_ep *pep);

#पूर्ण_अगर /* __LINUX_CDNSP_GADGET_H */
