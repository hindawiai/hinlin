<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * USBSS device controller driver header file
 *
 * Copyright (C) 2018-2019 Cadence.
 * Copyright (C) 2017-2018 NXP
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *         Pawel Jez <pjez@cadence.com>
 *         Peter Chen <peter.chen@nxp.com>
 */
#अगर_अघोषित __LINUX_CDNS3_GADGET
#घोषणा __LINUX_CDNS3_GADGET
#समावेश <linux/usb/gadget.h>
#समावेश <linux/dma-direction.h>

/*
 * USBSS-DEV रेजिस्टर पूर्णांकerface.
 * This corresponds to the USBSS Device Controller Interface
 */

/**
 * काष्ठा cdns3_usb_regs - device controller रेजिस्टरs.
 * @usb_conf:      Global Configuration.
 * @usb_sts:       Global Status.
 * @usb_cmd:       Global Command.
 * @usb_itpn:      ITP/SOF number.
 * @usb_lpm:       Global Command.
 * @usb_ien:       USB Interrupt Enable.
 * @usb_ists:      USB Interrupt Status.
 * @ep_sel:        Endpoपूर्णांक Select.
 * @ep_traddr:     Endpoपूर्णांक Transfer Ring Address.
 * @ep_cfg:        Endpoपूर्णांक Configuration.
 * @ep_cmd:        Endpoपूर्णांक Command.
 * @ep_sts:        Endpoपूर्णांक Status.
 * @ep_sts_sid:    Endpoपूर्णांक Status.
 * @ep_sts_en:     Endpoपूर्णांक Status Enable.
 * @drbl:          Doorbell.
 * @ep_ien:        EP Interrupt Enable.
 * @ep_ists:       EP Interrupt Status.
 * @usb_pwr:       Global Power Configuration.
 * @usb_conf2:     Global Configuration 2.
 * @usb_cap1:      Capability 1.
 * @usb_cap2:      Capability 2.
 * @usb_cap3:      Capability 3.
 * @usb_cap4:      Capability 4.
 * @usb_cap5:      Capability 5.
 * @usb_cap6:      Capability 6.
 * @usb_cpkt1:     Custom Packet 1.
 * @usb_cpkt2:     Custom Packet 2.
 * @usb_cpkt3:     Custom Packet 3.
 * @ep_dma_ext_addr: Upper address क्रम DMA operations.
 * @buf_addr:      Address क्रम On-chip Buffer operations.
 * @buf_data:      Data क्रम On-chip Buffer operations.
 * @buf_ctrl:      On-chip Buffer Access Control.
 * @dtrans:        DMA Transfer Mode.
 * @tdl_from_trb:  Source of TD Configuration.
 * @tdl_beh:       TDL Behavior Configuration.
 * @ep_tdl:        Endpoपूर्णांक TDL.
 * @tdl_beh2:      TDL Behavior 2 Configuration.
 * @dma_adv_td:    DMA Advance TD Configuration.
 * @reserved1:     Reserved.
 * @cfg_regs:      Configuration.
 * @reserved2:     Reserved.
 * @dma_axi_ctrl:  AXI Control.
 * @dma_axi_id:    AXI ID रेजिस्टर.
 * @dma_axi_cap:   AXI Capability.
 * @dma_axi_ctrl0: AXI Control 0.
 * @dma_axi_ctrl1: AXI Control 1.
 */
काष्ठा cdns3_usb_regs अणु
	__le32 usb_conf;
	__le32 usb_sts;
	__le32 usb_cmd;
	__le32 usb_itpn;
	__le32 usb_lpm;
	__le32 usb_ien;
	__le32 usb_ists;
	__le32 ep_sel;
	__le32 ep_traddr;
	__le32 ep_cfg;
	__le32 ep_cmd;
	__le32 ep_sts;
	__le32 ep_sts_sid;
	__le32 ep_sts_en;
	__le32 drbl;
	__le32 ep_ien;
	__le32 ep_ists;
	__le32 usb_pwr;
	__le32 usb_conf2;
	__le32 usb_cap1;
	__le32 usb_cap2;
	__le32 usb_cap3;
	__le32 usb_cap4;
	__le32 usb_cap5;
	__le32 usb_cap6;
	__le32 usb_cpkt1;
	__le32 usb_cpkt2;
	__le32 usb_cpkt3;
	__le32 ep_dma_ext_addr;
	__le32 buf_addr;
	__le32 buf_data;
	__le32 buf_ctrl;
	__le32 dtrans;
	__le32 tdl_from_trb;
	__le32 tdl_beh;
	__le32 ep_tdl;
	__le32 tdl_beh2;
	__le32 dma_adv_td;
	__le32 reserved1[26];
	__le32 cfg_reg1;
	__le32 dbg_link1;
	__le32 dbg_link2;
	__le32 cfg_regs[74];
	__le32 reserved2[51];
	__le32 dma_axi_ctrl;
	__le32 dma_axi_id;
	__le32 dma_axi_cap;
	__le32 dma_axi_ctrl0;
	__le32 dma_axi_ctrl1;
पूर्ण;

/* USB_CONF - biपंचांगasks */
/* Reset USB device configuration. */
#घोषणा USB_CONF_CFGRST		BIT(0)
/* Set Configuration. */
#घोषणा USB_CONF_CFGSET		BIT(1)
/* Disconnect USB device in SuperSpeed. */
#घोषणा USB_CONF_USB3DIS	BIT(3)
/* Disconnect USB device in HS/FS */
#घोषणा USB_CONF_USB2DIS	BIT(4)
/* Little Endian access - शेष */
#घोषणा USB_CONF_LENDIAN	BIT(5)
/*
 * Big Endian access. Driver assume that byte order क्रम
 * SFRs access always is as Little Endian so this bit
 * is not used.
 */
#घोषणा USB_CONF_BENDIAN	BIT(6)
/* Device software reset. */
#घोषणा USB_CONF_SWRST		BIT(7)
/* Singular DMA transfer mode. Only क्रम VER < DEV_VER_V3*/
#घोषणा USB_CONF_DSING		BIT(8)
/* Multiple DMA transfers mode. Only क्रम VER < DEV_VER_V3 */
#घोषणा USB_CONF_DMULT		BIT(9)
/* DMA घड़ी turn-off enable. */
#घोषणा USB_CONF_DMAOFFEN	BIT(10)
/* DMA घड़ी turn-off disable. */
#घोषणा USB_CONF_DMAOFFDS	BIT(11)
/* Clear Force Full Speed. */
#घोषणा USB_CONF_CFORCE_FS	BIT(12)
/* Set Force Full Speed. */
#घोषणा USB_CONF_SFORCE_FS	BIT(13)
/* Device enable. */
#घोषणा USB_CONF_DEVEN		BIT(14)
/* Device disable. */
#घोषणा USB_CONF_DEVDS		BIT(15)
/* L1 LPM state entry enable (used in HS/FS mode). */
#घोषणा USB_CONF_L1EN		BIT(16)
/* L1 LPM state entry disable (used in HS/FS mode). */
#घोषणा USB_CONF_L1DS		BIT(17)
/* USB 2.0 घड़ी gate disable. */
#घोषणा USB_CONF_CLK2OFFEN	BIT(18)
/* USB 2.0 घड़ी gate enable. */
#घोषणा USB_CONF_CLK2OFFDS	BIT(19)
/* L0 LPM state entry request (used in HS/FS mode). */
#घोषणा USB_CONF_LGO_L0		BIT(20)
/* USB 3.0 घड़ी gate disable. */
#घोषणा USB_CONF_CLK3OFFEN	BIT(21)
/* USB 3.0 घड़ी gate enable. */
#घोषणा USB_CONF_CLK3OFFDS	BIT(22)
/* Bit 23 is reserved*/
/* U1 state entry enable (used in SS mode). */
#घोषणा USB_CONF_U1EN		BIT(24)
/* U1 state entry disable (used in SS mode). */
#घोषणा USB_CONF_U1DS		BIT(25)
/* U2 state entry enable (used in SS mode). */
#घोषणा USB_CONF_U2EN		BIT(26)
/* U2 state entry disable (used in SS mode). */
#घोषणा USB_CONF_U2DS		BIT(27)
/* U0 state entry request (used in SS mode). */
#घोषणा USB_CONF_LGO_U0		BIT(28)
/* U1 state entry request (used in SS mode). */
#घोषणा USB_CONF_LGO_U1		BIT(29)
/* U2 state entry request (used in SS mode). */
#घोषणा USB_CONF_LGO_U2		BIT(30)
/* SS.Inactive state entry request (used in SS mode) */
#घोषणा USB_CONF_LGO_SSINACT	BIT(31)

/* USB_STS - biपंचांगasks */
/*
 * Configuration status.
 * 1 - device is in the configured state.
 * 0 - device is not configured.
 */
#घोषणा USB_STS_CFGSTS_MASK	BIT(0)
#घोषणा USB_STS_CFGSTS(p)	((p) & USB_STS_CFGSTS_MASK)
/*
 * On-chip memory overflow.
 * 0 - On-chip memory status OK.
 * 1 - On-chip memory overflow.
 */
#घोषणा USB_STS_OV_MASK		BIT(1)
#घोषणा USB_STS_OV(p)		((p) & USB_STS_OV_MASK)
/*
 * SuperSpeed connection status.
 * 0 - USB in SuperSpeed mode disconnected.
 * 1 - USB in SuperSpeed mode connected.
 */
#घोषणा USB_STS_USB3CONS_MASK	BIT(2)
#घोषणा USB_STS_USB3CONS(p)	((p) & USB_STS_USB3CONS_MASK)
/*
 * DMA transfer configuration status.
 * 0 - single request.
 * 1 - multiple TRB chain
 * Supported only क्रम controller version <  DEV_VER_V3
 */
#घोषणा USB_STS_DTRANS_MASK	BIT(3)
#घोषणा USB_STS_DTRANS(p)	((p) & USB_STS_DTRANS_MASK)
/*
 * Device speed.
 * 0 - Undefined (value after reset).
 * 1 - Low speed
 * 2 - Full speed
 * 3 - High speed
 * 4 - Super speed
 */
#घोषणा USB_STS_USBSPEED_MASK	GENMASK(6, 4)
#घोषणा USB_STS_USBSPEED(p)	(((p) & USB_STS_USBSPEED_MASK) >> 4)
#घोषणा USB_STS_LS		(0x1 << 4)
#घोषणा USB_STS_FS		(0x2 << 4)
#घोषणा USB_STS_HS		(0x3 << 4)
#घोषणा USB_STS_SS		(0x4 << 4)
#घोषणा DEV_UNDEFSPEED(p)	(((p) & USB_STS_USBSPEED_MASK) == (0x0 << 4))
#घोषणा DEV_LOWSPEED(p)		(((p) & USB_STS_USBSPEED_MASK) == USB_STS_LS)
#घोषणा DEV_FULLSPEED(p)	(((p) & USB_STS_USBSPEED_MASK) == USB_STS_FS)
#घोषणा DEV_HIGHSPEED(p)	(((p) & USB_STS_USBSPEED_MASK) == USB_STS_HS)
#घोषणा DEV_SUPERSPEED(p)	(((p) & USB_STS_USBSPEED_MASK) == USB_STS_SS)
/*
 * Endianness क्रम SFR access.
 * 0 - Little Endian order (शेष after hardware reset).
 * 1 - Big Endian order
 */
#घोषणा USB_STS_ENDIAN_MASK	BIT(7)
#घोषणा USB_STS_ENDIAN(p)	((p) & USB_STS_ENDIAN_MASK)
/*
 * HS/FS घड़ी turn-off status.
 * 0 - hsfs घड़ी is always on.
 * 1 - hsfs घड़ी turn-off in L2 (HS/FS mode) is enabled
 *          (शेष after hardware reset).
 */
#घोषणा USB_STS_CLK2OFF_MASK	BIT(8)
#घोषणा USB_STS_CLK2OFF(p)	((p) & USB_STS_CLK2OFF_MASK)
/*
 * PCLK घड़ी turn-off status.
 * 0 - pclk घड़ी is always on.
 * 1 - pclk घड़ी turn-off in U3 (SS mode) is enabled
 *          (शेष after hardware reset).
 */
#घोषणा USB_STS_CLK3OFF_MASK	BIT(9)
#घोषणा USB_STS_CLK3OFF(p)	((p) & USB_STS_CLK3OFF_MASK)
/*
 * Controller in reset state.
 * 0 - Internal reset is active.
 * 1 - Internal reset is not active and controller is fully operational.
 */
#घोषणा USB_STS_IN_RST_MASK	BIT(10)
#घोषणा USB_STS_IN_RST(p)	((p) & USB_STS_IN_RST_MASK)
/*
 * Status of the "TDL calculation basing on TRB" feature.
 * 0 - disabled
 * 1 - enabled
 * Supported only क्रम DEV_VER_V2 controller version.
 */
#घोषणा USB_STS_TDL_TRB_ENABLED	BIT(11)
/*
 * Device enable Status.
 * 0 - USB device is disabled (VBUS input is disconnected from पूर्णांकernal logic).
 * 1 - USB device is enabled (VBUS input is connected to the पूर्णांकernal logic).
 */
#घोषणा USB_STS_DEVS_MASK	BIT(14)
#घोषणा USB_STS_DEVS(p)		((p) & USB_STS_DEVS_MASK)
/*
 * Address status.
 * 0 - USB device is शेष state.
 * 1 - USB device is at least in address state.
 */
#घोषणा USB_STS_ADDRESSED_MASK	BIT(15)
#घोषणा USB_STS_ADDRESSED(p)	((p) & USB_STS_ADDRESSED_MASK)
/*
 * L1 LPM state enable status (used in HS/FS mode).
 * 0 - Entering to L1 LPM state disabled.
 * 1 - Entering to L1 LPM state enabled.
 */
#घोषणा USB_STS_L1ENS_MASK	BIT(16)
#घोषणा USB_STS_L1ENS(p)	((p) & USB_STS_L1ENS_MASK)
/*
 * Internal VBUS connection status (used both in HS/FS  and SS mode).
 * 0 - पूर्णांकernal VBUS is not detected.
 * 1 - पूर्णांकernal VBUS is detected.
 */
#घोषणा USB_STS_VBUSS_MASK	BIT(17)
#घोषणा USB_STS_VBUSS(p)	((p) & USB_STS_VBUSS_MASK)
/*
 * HS/FS LPM  state (used in FS/HS mode).
 * 0 - L0 State
 * 1 - L1 State
 * 2 - L2 State
 * 3 - L3 State
 */
#घोषणा USB_STS_LPMST_MASK	GENMASK(19, 18)
#घोषणा DEV_L0_STATE(p)		(((p) & USB_STS_LPMST_MASK) == (0x0 << 18))
#घोषणा DEV_L1_STATE(p)		(((p) & USB_STS_LPMST_MASK) == (0x1 << 18))
#घोषणा DEV_L2_STATE(p)		(((p) & USB_STS_LPMST_MASK) == (0x2 << 18))
#घोषणा DEV_L3_STATE(p)		(((p) & USB_STS_LPMST_MASK) == (0x3 << 18))
/*
 * Disable HS status (used in FS/HS mode).
 * 0 - the disconnect bit क्रम HS/FS mode is set .
 * 1 - the disconnect bit क्रम HS/FS mode is not set.
 */
#घोषणा USB_STS_USB2CONS_MASK	BIT(20)
#घोषणा USB_STS_USB2CONS(p)	((p) & USB_STS_USB2CONS_MASK)
/*
 * HS/FS mode connection status (used in FS/HS mode).
 * 0 - High Speed operations in USB2.0 (FS/HS) mode not disabled.
 * 1 - High Speed operations in USB2.0 (FS/HS).
 */
#घोषणा USB_STS_DISABLE_HS_MASK	BIT(21)
#घोषणा USB_STS_DISABLE_HS(p)	((p) & USB_STS_DISABLE_HS_MASK)
/*
 * U1 state enable status (used in SS mode).
 * 0 - Entering to  U1 state disabled.
 * 1 - Entering to  U1 state enabled.
 */
#घोषणा USB_STS_U1ENS_MASK	BIT(24)
#घोषणा USB_STS_U1ENS(p)	((p) & USB_STS_U1ENS_MASK)
/*
 * U2 state enable status (used in SS mode).
 * 0 - Entering to  U2 state disabled.
 * 1 - Entering to  U2 state enabled.
 */
#घोषणा USB_STS_U2ENS_MASK	BIT(25)
#घोषणा USB_STS_U2ENS(p)	((p) & USB_STS_U2ENS_MASK)
/*
 * SuperSpeed Link LTSSM state. This field reflects USBSS-DEV current
 * SuperSpeed link state
 */
#घोषणा USB_STS_LST_MASK	GENMASK(29, 26)
#घोषणा DEV_LST_U0		(((p) & USB_STS_LST_MASK) == (0x0 << 26))
#घोषणा DEV_LST_U1		(((p) & USB_STS_LST_MASK) == (0x1 << 26))
#घोषणा DEV_LST_U2		(((p) & USB_STS_LST_MASK) == (0x2 << 26))
#घोषणा DEV_LST_U3		(((p) & USB_STS_LST_MASK) == (0x3 << 26))
#घोषणा DEV_LST_DISABLED	(((p) & USB_STS_LST_MASK) == (0x4 << 26))
#घोषणा DEV_LST_RXDETECT	(((p) & USB_STS_LST_MASK) == (0x5 << 26))
#घोषणा DEV_LST_INACTIVE	(((p) & USB_STS_LST_MASK) == (0x6 << 26))
#घोषणा DEV_LST_POLLING		(((p) & USB_STS_LST_MASK) == (0x7 << 26))
#घोषणा DEV_LST_RECOVERY	(((p) & USB_STS_LST_MASK) == (0x8 << 26))
#घोषणा DEV_LST_HOT_RESET	(((p) & USB_STS_LST_MASK) == (0x9 << 26))
#घोषणा DEV_LST_COMP_MODE	(((p) & USB_STS_LST_MASK) == (0xa << 26))
#घोषणा DEV_LST_LB_STATE	(((p) & USB_STS_LST_MASK) == (0xb << 26))
/*
 * DMA घड़ी turn-off status.
 * 0 - DMA घड़ी is always on (शेष after hardware reset).
 * 1 - DMA घड़ी turn-off in U1, U2 and U3 (SS mode) is enabled.
 */
#घोषणा USB_STS_DMAOFF_MASK	BIT(30)
#घोषणा USB_STS_DMAOFF(p)	((p) & USB_STS_DMAOFF_MASK)
/*
 * SFR Endian status.
 * 0 - Little Endian order (शेष after hardware reset).
 * 1 - Big Endian order.
 */
#घोषणा USB_STS_ENDIAN2_MASK	BIT(31)
#घोषणा USB_STS_ENDIAN2(p)	((p) & USB_STS_ENDIAN2_MASK)

/* USB_CMD -  biपंचांगasks */
/* Set Function Address */
#घोषणा USB_CMD_SET_ADDR	BIT(0)
/*
 * Function Address This field is saved to the device only when the field
 * SET_ADDR is set '1 ' during ग_लिखो to USB_CMD रेजिस्टर.
 * Software is responsible क्रम entering the address of the device during
 * SET_ADDRESS request service. This field should be set immediately after
 * the SETUP packet is decoded, and prior to confirmation of the status phase
 */
#घोषणा USB_CMD_FADDR_MASK	GENMASK(7, 1)
#घोषणा USB_CMD_FADDR(p)	(((p) << 1) & USB_CMD_FADDR_MASK)
/* Send Function Wake Device Notअगरication TP (used only in SS mode). */
#घोषणा USB_CMD_SDNFW		BIT(8)
/* Set Test Mode (used only in HS/FS mode). */
#घोषणा USB_CMD_STMODE		BIT(9)
/* Test mode selector (used only in HS/FS mode) */
#घोषणा USB_STS_TMODE_SEL_MASK	GENMASK(11, 10)
#घोषणा USB_STS_TMODE_SEL(p)	(((p) << 10) & USB_STS_TMODE_SEL_MASK)
/*
 *  Send Latency Tolerance Message Device Notअगरication TP (used only
 *  in SS mode).
 */
#घोषणा USB_CMD_SDNLTM		BIT(12)
/* Send Custom Transaction Packet (used only in SS mode) */
#घोषणा USB_CMD_SPKT		BIT(13)
/*Device Notअगरication 'Function Wake' - Interface value (only in SS mode. */
#घोषणा USB_CMD_DNFW_INT_MASK	GENMASK(23, 16)
#घोषणा USB_STS_DNFW_INT(p)	(((p) << 16) & USB_CMD_DNFW_INT_MASK)
/*
 * Device Notअगरication 'Latency Tolerance Message' -373 BELT value [7:0]
 * (used only in SS mode).
 */
#घोषणा USB_CMD_DNLTM_BELT_MASK	GENMASK(27, 16)
#घोषणा USB_STS_DNLTM_BELT(p)	(((p) << 16) & USB_CMD_DNLTM_BELT_MASK)

/* USB_ITPN - biपंचांगasks */
/*
 * ITP(SS) / SOF (HS/FS) number
 * In SS mode this field represent number of last ITP received from host.
 * In HS/FS mode this field represent number of last SOF received from host.
 */
#घोषणा USB_ITPN_MASK		GENMASK(13, 0)
#घोषणा USB_ITPN(p)		((p) & USB_ITPN_MASK)

/* USB_LPM - biपंचांगasks */
/* Host Initiated Resume Duration. */
#घोषणा USB_LPM_HIRD_MASK	GENMASK(3, 0)
#घोषणा USB_LPM_HIRD(p)		((p) & USB_LPM_HIRD_MASK)
/* Remote Wakeup Enable (bRemoteWake). */
#घोषणा USB_LPM_BRW		BIT(4)

/* USB_IEN - biपंचांगasks */
/* SS connection पूर्णांकerrupt enable */
#घोषणा USB_IEN_CONIEN		BIT(0)
/* SS disconnection पूर्णांकerrupt enable. */
#घोषणा USB_IEN_DISIEN		BIT(1)
/* USB SS warm reset पूर्णांकerrupt enable. */
#घोषणा USB_IEN_UWRESIEN	BIT(2)
/* USB SS hot reset पूर्णांकerrupt enable */
#घोषणा USB_IEN_UHRESIEN	BIT(3)
/* SS link U3 state enter पूर्णांकerrupt enable (suspend).*/
#घोषणा USB_IEN_U3ENTIEN	BIT(4)
/* SS link U3 state निकास पूर्णांकerrupt enable (wakeup). */
#घोषणा USB_IEN_U3EXTIEN	BIT(5)
/* SS link U2 state enter पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_U2ENTIEN	BIT(6)
/* SS link U2 state निकास पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_U2EXTIEN	BIT(7)
/* SS link U1 state enter पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_U1ENTIEN	BIT(8)
/* SS link U1 state निकास पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_U1EXTIEN	BIT(9)
/* ITP/SOF packet detected पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_ITPIEN		BIT(10)
/* Wakeup पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_WAKEIEN		BIT(11)
/* Send Custom Packet पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_SPKTIEN		BIT(12)
/* HS/FS mode connection पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_CON2IEN		BIT(16)
/* HS/FS mode disconnection पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_DIS2IEN		BIT(17)
/* USB reset (HS/FS mode) पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_U2RESIEN	BIT(18)
/* LPM L2 state enter पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_L2ENTIEN	BIT(20)
/* LPM  L2 state निकास पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_L2EXTIEN	BIT(21)
/* LPM L1 state enter पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_L1ENTIEN	BIT(24)
/* LPM  L1 state निकास पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_L1EXTIEN	BIT(25)
/* Configuration reset पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_CFGRESIEN	BIT(26)
/* Start of the USB SS warm reset पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_UWRESSIEN	BIT(28)
/* End of the USB SS warm reset पूर्णांकerrupt enable.*/
#घोषणा USB_IEN_UWRESEIEN	BIT(29)

#घोषणा USB_IEN_INIT  (USB_IEN_U2RESIEN | USB_ISTS_DIS2I | USB_IEN_CON2IEN \
		       | USB_IEN_UHRESIEN | USB_IEN_UWRESIEN | USB_IEN_DISIEN \
		       | USB_IEN_CONIEN | USB_IEN_U3EXTIEN | USB_IEN_L2ENTIEN \
		       | USB_IEN_L2EXTIEN | USB_IEN_L1ENTIEN | USB_IEN_U3ENTIEN)

/* USB_ISTS - biपंचांगasks */
/* SS Connection detected. */
#घोषणा USB_ISTS_CONI		BIT(0)
/* SS Disconnection detected. */
#घोषणा USB_ISTS_DISI		BIT(1)
/* UUSB warm reset detectede. */
#घोषणा USB_ISTS_UWRESI		BIT(2)
/* USB hot reset detected. */
#घोषणा USB_ISTS_UHRESI		BIT(3)
/* U3 link state enter detected (suspend).*/
#घोषणा USB_ISTS_U3ENTI		BIT(4)
/* U3 link state निकास detected (wakeup). */
#घोषणा USB_ISTS_U3EXTI		BIT(5)
/* U2 link state enter detected.*/
#घोषणा USB_ISTS_U2ENTI		BIT(6)
/* U2 link state निकास detected.*/
#घोषणा USB_ISTS_U2EXTI		BIT(7)
/* U1 link state enter detected.*/
#घोषणा USB_ISTS_U1ENTI		BIT(8)
/* U1 link state निकास detected.*/
#घोषणा USB_ISTS_U1EXTI		BIT(9)
/* ITP/SOF packet detected.*/
#घोषणा USB_ISTS_ITPI		BIT(10)
/* Wakeup detected.*/
#घोषणा USB_ISTS_WAKEI		BIT(11)
/* Send Custom Packet detected.*/
#घोषणा USB_ISTS_SPKTI		BIT(12)
/* HS/FS mode connection detected.*/
#घोषणा USB_ISTS_CON2I		BIT(16)
/* HS/FS mode disconnection detected.*/
#घोषणा USB_ISTS_DIS2I		BIT(17)
/* USB reset (HS/FS mode) detected.*/
#घोषणा USB_ISTS_U2RESI		BIT(18)
/* LPM L2 state enter detected.*/
#घोषणा USB_ISTS_L2ENTI		BIT(20)
/* LPM  L2 state निकास detected.*/
#घोषणा USB_ISTS_L2EXTI		BIT(21)
/* LPM L1 state enter detected.*/
#घोषणा USB_ISTS_L1ENTI		BIT(24)
/* LPM L1 state निकास detected.*/
#घोषणा USB_ISTS_L1EXTI		BIT(25)
/* USB configuration reset detected.*/
#घोषणा USB_ISTS_CFGRESI	BIT(26)
/* Start of the USB warm reset detected.*/
#घोषणा USB_ISTS_UWRESSI	BIT(28)
/* End of the USB warm reset detected.*/
#घोषणा USB_ISTS_UWRESEI	BIT(29)

/* USB_SEL - biपंचांगasks */
#घोषणा EP_SEL_EPNO_MASK	GENMASK(3, 0)
/* Endpoपूर्णांक number. */
#घोषणा EP_SEL_EPNO(p)		((p) & EP_SEL_EPNO_MASK)
/* Endpoपूर्णांक direction bit - 0 - OUT, 1 - IN. */
#घोषणा EP_SEL_सूची		BIT(7)

#घोषणा select_ep_in(nr)	(EP_SEL_EPNO(p) | EP_SEL_सूची)
#घोषणा select_ep_out		(EP_SEL_EPNO(p))

/* EP_TRADDR - biपंचांगasks */
/* Transfer Ring address. */
#घोषणा EP_TRADDR_TRADDR(p)	((p))

/* EP_CFG - biपंचांगasks */
/* Endpoपूर्णांक enable */
#घोषणा EP_CFG_ENABLE		BIT(0)
/*
 *  Endpoपूर्णांक type.
 * 1 - isochronous
 * 2 - bulk
 * 3 - पूर्णांकerrupt
 */
#घोषणा EP_CFG_EPTYPE_MASK	GENMASK(2, 1)
#घोषणा EP_CFG_EPTYPE(p)	(((p) << 1)  & EP_CFG_EPTYPE_MASK)
/* Stream support enable (only in SS mode). */
#घोषणा EP_CFG_STREAM_EN	BIT(3)
/* TDL check (only in SS mode क्रम BULK EP). */
#घोषणा EP_CFG_TDL_CHK		BIT(4)
/* SID check (only in SS mode क्रम BULK OUT EP). */
#घोषणा EP_CFG_SID_CHK		BIT(5)
/* DMA transfer endianness. */
#घोषणा EP_CFG_EPENDIAN		BIT(7)
/* Max burst size (used only in SS mode). */
#घोषणा EP_CFG_MAXBURST_MASK	GENMASK(11, 8)
#घोषणा EP_CFG_MAXBURST(p)	(((p) << 8) & EP_CFG_MAXBURST_MASK)
/* ISO max burst. */
#घोषणा EP_CFG_MULT_MASK	GENMASK(15, 14)
#घोषणा EP_CFG_MULT(p)		(((p) << 14) & EP_CFG_MULT_MASK)
/* ISO max burst. */
#घोषणा EP_CFG_MAXPKTSIZE_MASK	GENMASK(26, 16)
#घोषणा EP_CFG_MAXPKTSIZE(p)	(((p) << 16) & EP_CFG_MAXPKTSIZE_MASK)
/* Max number of buffered packets. */
#घोषणा EP_CFG_BUFFERING_MASK	GENMASK(31, 27)
#घोषणा EP_CFG_BUFFERING(p)	(((p) << 27) & EP_CFG_BUFFERING_MASK)

/* EP_CMD - biपंचांगasks */
/* Endpoपूर्णांक reset. */
#घोषणा EP_CMD_EPRST		BIT(0)
/* Endpoपूर्णांक STALL set. */
#घोषणा EP_CMD_SSTALL		BIT(1)
/* Endpoपूर्णांक STALL clear. */
#घोषणा EP_CMD_CSTALL		BIT(2)
/* Send ERDY TP. */
#घोषणा EP_CMD_ERDY		BIT(3)
/* Request complete. */
#घोषणा EP_CMD_REQ_CMPL		BIT(5)
/* Transfer descriptor पढ़ोy. */
#घोषणा EP_CMD_DRDY		BIT(6)
/* Data flush. */
#घोषणा EP_CMD_DFLUSH		BIT(7)
/*
 * Transfer Descriptor Length ग_लिखो  (used only क्रम Bulk Stream capable
 * endpoपूर्णांकs in SS mode).
 * Bit Removed from DEV_VER_V3 controller version.
 */
#घोषणा EP_CMD_STDL		BIT(8)
/*
 * Transfer Descriptor Length (used only in SS mode क्रम bulk endpoपूर्णांकs).
 * Bits Removed from DEV_VER_V3 controller version.
 */
#घोषणा EP_CMD_TDL_MASK		GENMASK(15, 9)
#घोषणा EP_CMD_TDL_SET(p)	(((p) << 9) & EP_CMD_TDL_MASK)
#घोषणा EP_CMD_TDL_GET(p)	(((p) & EP_CMD_TDL_MASK) >> 9)
#घोषणा EP_CMD_TDL_MAX		(EP_CMD_TDL_MASK >> 9)

/* ERDY Stream ID value (used in SS mode). */
#घोषणा EP_CMD_ERDY_SID_MASK	GENMASK(31, 16)
#घोषणा EP_CMD_ERDY_SID(p)	(((p) << 16) & EP_CMD_ERDY_SID_MASK)

/* EP_STS - biपंचांगasks */
/* Setup transfer complete. */
#घोषणा EP_STS_SETUP		BIT(0)
/* Endpoपूर्णांक STALL status. */
#घोषणा EP_STS_STALL(p)		((p) & BIT(1))
/* Interrupt On Complete. */
#घोषणा EP_STS_IOC		BIT(2)
/* Interrupt on Short Packet. */
#घोषणा EP_STS_ISP		BIT(3)
/* Transfer descriptor missing. */
#घोषणा EP_STS_DESCMIS		BIT(4)
/* Stream Rejected (used only in SS mode) */
#घोषणा EP_STS_STREAMR		BIT(5)
/* EXIT from MOVE DATA State (used only क्रम stream transfers in SS mode). */
#घोषणा EP_STS_MD_EXIT		BIT(6)
/* TRB error. */
#घोषणा EP_STS_TRBERR		BIT(7)
/* Not पढ़ोy (used only in SS mode). */
#घोषणा EP_STS_NRDY		BIT(8)
/* DMA busy bit. */
#घोषणा EP_STS_DBUSY		BIT(9)
/* Endpoपूर्णांक Buffer Empty */
#घोषणा EP_STS_BUFFEMPTY(p)	((p) & BIT(10))
/* Current Cycle Status */
#घोषणा EP_STS_CCS(p)		((p) & BIT(11))
/* Prime (used only in SS mode. */
#घोषणा EP_STS_PRIME		BIT(12)
/* Stream error (used only in SS mode). */
#घोषणा EP_STS_SIDERR		BIT(13)
/* OUT size mismatch. */
#घोषणा EP_STS_OUTSMM		BIT(14)
/* ISO transmission error. */
#घोषणा EP_STS_ISOERR		BIT(15)
/* Host Packet Pending (only क्रम SS mode). */
#घोषणा EP_STS_HOSTPP(p)	((p) & BIT(16))
/* Stream Protocol State Machine State (only क्रम Bulk stream endpoपूर्णांकs). */
#घोषणा EP_STS_SPSMST_MASK		GENMASK(18, 17)
#घोषणा EP_STS_SPSMST_DISABLED(p)	(((p) & EP_STS_SPSMST_MASK) >> 17)
#घोषणा EP_STS_SPSMST_IDLE(p)		(((p) & EP_STS_SPSMST_MASK) >> 17)
#घोषणा EP_STS_SPSMST_START_STREAM(p)	(((p) & EP_STS_SPSMST_MASK) >> 17)
#घोषणा EP_STS_SPSMST_MOVE_DATA(p)	(((p) & EP_STS_SPSMST_MASK) >> 17)
/* Interrupt On Transfer complete. */
#घोषणा EP_STS_IOT		BIT(19)
/* OUT queue endpoपूर्णांक number. */
#घोषणा EP_STS_OUTQ_NO_MASK	GENMASK(27, 24)
#घोषणा EP_STS_OUTQ_NO(p)	(((p) & EP_STS_OUTQ_NO_MASK) >> 24)
/* OUT queue valid flag. */
#घोषणा EP_STS_OUTQ_VAL_MASK	BIT(28)
#घोषणा EP_STS_OUTQ_VAL(p)	((p) & EP_STS_OUTQ_VAL_MASK)
/* SETUP WAIT. */
#घोषणा EP_STS_STPWAIT		BIT(31)

/* EP_STS_SID - biपंचांगasks */
/* Stream ID (used only in SS mode). */
#घोषणा EP_STS_SID_MASK		GENMASK(15, 0)
#घोषणा EP_STS_SID(p)		((p) & EP_STS_SID_MASK)

/* EP_STS_EN - biपंचांगasks */
/* SETUP पूर्णांकerrupt enable. */
#घोषणा EP_STS_EN_SETUPEN	BIT(0)
/* OUT transfer missing descriptor enable. */
#घोषणा EP_STS_EN_DESCMISEN	BIT(4)
/* Stream Rejected enable. */
#घोषणा EP_STS_EN_STREAMREN	BIT(5)
/* Move Data Exit enable.*/
#घोषणा EP_STS_EN_MD_EXITEN	BIT(6)
/* TRB enable. */
#घोषणा EP_STS_EN_TRBERREN	BIT(7)
/* NRDY enable. */
#घोषणा EP_STS_EN_NRDYEN	BIT(8)
/* Prime enable. */
#घोषणा EP_STS_EN_PRIMEEEN	BIT(12)
/* Stream error enable. */
#घोषणा EP_STS_EN_SIDERREN	BIT(13)
/* OUT size mismatch enable. */
#घोषणा EP_STS_EN_OUTSMMEN	BIT(14)
/* ISO transmission error enable. */
#घोषणा EP_STS_EN_ISOERREN	BIT(15)
/* Interrupt on Transmission complete enable. */
#घोषणा EP_STS_EN_IOTEN		BIT(19)
/* Setup Wait पूर्णांकerrupt enable. */
#घोषणा EP_STS_EN_STPWAITEN	BIT(31)

/* DRBL- biपंचांगasks */
#घोषणा DB_VALUE_BY_INDEX(index) (1 << (index))
#घोषणा DB_VALUE_EP0_OUT	BIT(0)
#घोषणा DB_VALUE_EP0_IN		BIT(16)

/* EP_IEN - biपंचांगasks */
#घोषणा EP_IEN(index)		(1 << (index))
#घोषणा EP_IEN_EP_OUT0		BIT(0)
#घोषणा EP_IEN_EP_IN0		BIT(16)

/* EP_ISTS - biपंचांगasks */
#घोषणा EP_ISTS(index)		(1 << (index))
#घोषणा EP_ISTS_EP_OUT0		BIT(0)
#घोषणा EP_ISTS_EP_IN0		BIT(16)

/* USB_PWR- biपंचांगasks */
/*Power Shut Off capability enable*/
#घोषणा PUSB_PWR_PSO_EN		BIT(0)
/*Power Shut Off capability disable*/
#घोषणा PUSB_PWR_PSO_DS		BIT(1)
/*
 * Enables turning-off Reference Clock.
 * This bit is optional and implemented only when support क्रम OTG is
 * implemented (indicated by OTG_READY bit set to '1').
 */
#घोषणा PUSB_PWR_STB_CLK_SWITCH_EN	BIT(8)
/*
 * Status bit indicating that operation required by STB_CLK_SWITCH_EN ग_लिखो
 * is completed
 */
#घोषणा PUSB_PWR_STB_CLK_SWITCH_DONE	BIT(9)
/* This bit inक्रमms अगर Fast Registers Access is enabled. */
#घोषणा PUSB_PWR_FST_REG_ACCESS_STAT	BIT(30)
/* Fast Registers Access Enable. */
#घोषणा PUSB_PWR_FST_REG_ACCESS		BIT(31)

/* USB_CONF2- biपंचांगasks */
/*
 * Writing 1 disables TDL calculation basing on TRB feature in controller
 * क्रम DMULT mode.
 * Bit supported only क्रम DEV_VER_V2 version.
 */
#घोषणा USB_CONF2_DIS_TDL_TRB		BIT(1)
/*
 * Writing 1 enables TDL calculation basing on TRB feature in controller
 * क्रम DMULT mode.
 * Bit supported only क्रम DEV_VER_V2 version.
 */
#घोषणा USB_CONF2_EN_TDL_TRB		BIT(2)

/* USB_CAP1- biपंचांगasks */
/*
 * SFR Interface type
 * These field reflects type of SFR पूर्णांकerface implemented:
 * 0x0 - OCP
 * 0x1 - AHB,
 * 0x2 - PLB
 * 0x3 - AXI
 * 0x4-0xF - reserved
 */
#घोषणा USB_CAP1_SFR_TYPE_MASK	GENMASK(3, 0)
#घोषणा DEV_SFR_TYPE_OCP(p)	(((p) & USB_CAP1_SFR_TYPE_MASK) == 0x0)
#घोषणा DEV_SFR_TYPE_AHB(p)	(((p) & USB_CAP1_SFR_TYPE_MASK) == 0x1)
#घोषणा DEV_SFR_TYPE_PLB(p)	(((p) & USB_CAP1_SFR_TYPE_MASK) == 0x2)
#घोषणा DEV_SFR_TYPE_AXI(p)	(((p) & USB_CAP1_SFR_TYPE_MASK) == 0x3)
/*
 * SFR Interface width
 * These field reflects width of SFR पूर्णांकerface implemented:
 * 0x0 - 8 bit पूर्णांकerface,
 * 0x1 - 16 bit पूर्णांकerface,
 * 0x2 - 32 bit पूर्णांकerface
 * 0x3 - 64 bit पूर्णांकerface
 * 0x4-0xF - reserved
 */
#घोषणा USB_CAP1_SFR_WIDTH_MASK	GENMASK(7, 4)
#घोषणा DEV_SFR_WIDTH_8(p)	(((p) & USB_CAP1_SFR_WIDTH_MASK) == (0x0 << 4))
#घोषणा DEV_SFR_WIDTH_16(p)	(((p) & USB_CAP1_SFR_WIDTH_MASK) == (0x1 << 4))
#घोषणा DEV_SFR_WIDTH_32(p)	(((p) & USB_CAP1_SFR_WIDTH_MASK) == (0x2 << 4))
#घोषणा DEV_SFR_WIDTH_64(p)	(((p) & USB_CAP1_SFR_WIDTH_MASK) == (0x3 << 4))
/*
 * DMA Interface type
 * These field reflects type of DMA पूर्णांकerface implemented:
 * 0x0 - OCP
 * 0x1 - AHB,
 * 0x2 - PLB
 * 0x3 - AXI
 * 0x4-0xF - reserved
 */
#घोषणा USB_CAP1_DMA_TYPE_MASK	GENMASK(11, 8)
#घोषणा DEV_DMA_TYPE_OCP(p)	(((p) & USB_CAP1_DMA_TYPE_MASK) == (0x0 << 8))
#घोषणा DEV_DMA_TYPE_AHB(p)	(((p) & USB_CAP1_DMA_TYPE_MASK) == (0x1 << 8))
#घोषणा DEV_DMA_TYPE_PLB(p)	(((p) & USB_CAP1_DMA_TYPE_MASK) == (0x2 << 8))
#घोषणा DEV_DMA_TYPE_AXI(p)	(((p) & USB_CAP1_DMA_TYPE_MASK) == (0x3 << 8))
/*
 * DMA Interface width
 * These field reflects width of DMA पूर्णांकerface implemented:
 * 0x0 - reserved,
 * 0x1 - reserved,
 * 0x2 - 32 bit पूर्णांकerface
 * 0x3 - 64 bit पूर्णांकerface
 * 0x4-0xF - reserved
 */
#घोषणा USB_CAP1_DMA_WIDTH_MASK	GENMASK(15, 12)
#घोषणा DEV_DMA_WIDTH_32(p)	(((p) & USB_CAP1_DMA_WIDTH_MASK) == (0x2 << 12))
#घोषणा DEV_DMA_WIDTH_64(p)	(((p) & USB_CAP1_DMA_WIDTH_MASK) == (0x3 << 12))
/*
 * USB3 PHY Interface type
 * These field reflects type of USB3 PHY पूर्णांकerface implemented:
 * 0x0 - USB PIPE,
 * 0x1 - RMMI,
 * 0x2-0xF - reserved
 */
#घोषणा USB_CAP1_U3PHY_TYPE_MASK GENMASK(19, 16)
#घोषणा DEV_U3PHY_PIPE(p) (((p) & USB_CAP1_U3PHY_TYPE_MASK) == (0x0 << 16))
#घोषणा DEV_U3PHY_RMMI(p) (((p) & USB_CAP1_U3PHY_TYPE_MASK) == (0x1 << 16))
/*
 * USB3 PHY Interface width
 * These field reflects width of USB3 PHY पूर्णांकerface implemented:
 * 0x0 - 8 bit PIPE पूर्णांकerface,
 * 0x1 - 16 bit PIPE पूर्णांकerface,
 * 0x2 - 32 bit PIPE पूर्णांकerface,
 * 0x3 - 64 bit PIPE पूर्णांकerface
 * 0x4-0xF - reserved
 * Note: When SSIC पूर्णांकerface is implemented this field shows the width of
 * पूर्णांकernal PIPE पूर्णांकerface. The RMMI पूर्णांकerface is always 20bit wide.
 */
#घोषणा USB_CAP1_U3PHY_WIDTH_MASK GENMASK(23, 20)
#घोषणा DEV_U3PHY_WIDTH_8(p) \
	(((p) & USB_CAP1_U3PHY_WIDTH_MASK) == (0x0 << 20))
#घोषणा DEV_U3PHY_WIDTH_16(p) \
	(((p) & USB_CAP1_U3PHY_WIDTH_MASK) == (0x1 << 16))
#घोषणा DEV_U3PHY_WIDTH_32(p) \
	(((p) & USB_CAP1_U3PHY_WIDTH_MASK) == (0x2 << 20))
#घोषणा DEV_U3PHY_WIDTH_64(p) \
	(((p) & USB_CAP1_U3PHY_WIDTH_MASK) == (0x3 << 16))

/*
 * USB2 PHY Interface enable
 * These field inक्रमms अगर USB2 PHY पूर्णांकerface is implemented:
 * 0x0 - पूर्णांकerface NOT implemented,
 * 0x1 - पूर्णांकerface implemented
 */
#घोषणा USB_CAP1_U2PHY_EN(p)	((p) & BIT(24))
/*
 * USB2 PHY Interface type
 * These field reflects type of USB2 PHY पूर्णांकerface implemented:
 * 0x0 - UTMI,
 * 0x1 - ULPI
 */
#घोषणा DEV_U2PHY_ULPI(p)	((p) & BIT(25))
/*
 * USB2 PHY Interface width
 * These field reflects width of USB2 PHY पूर्णांकerface implemented:
 * 0x0 - 8 bit पूर्णांकerface,
 * 0x1 - 16 bit पूर्णांकerface,
 * Note: The ULPI पूर्णांकerface is always 8bit wide.
 */
#घोषणा DEV_U2PHY_WIDTH_16(p)	((p) & BIT(26))
/*
 * OTG Ready
 * 0x0 - pure device mode
 * 0x1 - some features and ports क्रम CDNS USB OTG controller are implemented.
 */
#घोषणा USB_CAP1_OTG_READY(p)	((p) & BIT(27))

/*
 * When set, indicates that controller supports स्वतःmatic पूर्णांकernal TDL
 * calculation basing on the size provided in TRB (TRB[22:17]) क्रम DMULT mode
 * Supported only क्रम DEV_VER_V2 controller version.
 */
#घोषणा USB_CAP1_TDL_FROM_TRB(p)	((p) & BIT(28))

/* USB_CAP2- biपंचांगasks */
/*
 * The actual size of the connected On-chip RAM memory in kB:
 * - 0 means 256 kB (max supported mem size)
 * - value other than 0 reflects the mem size in kB
 */
#घोषणा USB_CAP2_ACTUAL_MEM_SIZE(p) ((p) & GENMASK(7, 0))
/*
 * Max supported mem size
 * These field reflects width of on-chip RAM address bus width,
 * which determines max supported mem size:
 * 0x0-0x7 - reserved,
 * 0x8 - support क्रम 4kB mem,
 * 0x9 - support क्रम 8kB mem,
 * 0xA - support क्रम 16kB mem,
 * 0xB - support क्रम 32kB mem,
 * 0xC - support क्रम 64kB mem,
 * 0xD - support क्रम 128kB mem,
 * 0xE - support क्रम 256kB mem,
 * 0xF - reserved
 */
#घोषणा USB_CAP2_MAX_MEM_SIZE(p) ((p) & GENMASK(11, 8))

/* USB_CAP3- biपंचांगasks */
#घोषणा EP_IS_IMPLEMENTED(reg, index) ((reg) & (1 << (index)))

/* USB_CAP4- biपंचांगasks */
#घोषणा EP_SUPPORT_ISO(reg, index) ((reg) & (1 << (index)))

/* USB_CAP5- biपंचांगasks */
#घोषणा EP_SUPPORT_STREAM(reg, index) ((reg) & (1 << (index)))

/* USB_CAP6- biपंचांगasks */
/* The USBSS-DEV Controller  Internal build number. */
#घोषणा GET_DEV_BASE_VERSION(p) ((p) & GENMASK(23, 0))
/* The USBSS-DEV Controller version number. */
#घोषणा GET_DEV_CUSTOM_VERSION(p) ((p) & GENMASK(31, 24))

#घोषणा DEV_VER_NXP_V1		0x00024502
#घोषणा DEV_VER_TI_V1		0x00024509
#घोषणा DEV_VER_V2		0x0002450C
#घोषणा DEV_VER_V3		0x0002450d

/* DBG_LINK1- biपंचांगasks */
/*
 * LFPS_MIN_DET_U1_EXIT value This parameter configures the minimum
 * समय required क्रम decoding the received LFPS as an LFPS.U1_Exit.
 */
#घोषणा DBG_LINK1_LFPS_MIN_DET_U1_EXIT(p)	((p) & GENMASK(7, 0))
/*
 * LFPS_MIN_GEN_U1_EXIT value This parameter configures the minimum समय क्रम
 * phytxelecidle deनिश्चितion when LFPS.U1_Exit
 */
#घोषणा DBG_LINK1_LFPS_MIN_GEN_U1_EXIT_MASK	GENMASK(15, 8)
#घोषणा DBG_LINK1_LFPS_MIN_GEN_U1_EXIT(p)	(((p) << 8) & GENMASK(15, 8))
/*
 * RXDET_BREAK_DIS value This parameter configures terminating the Far-end
 * Receiver termination detection sequence:
 * 0: it is possible that USBSS_DEV will terminate Farend receiver
 *    termination detection sequence
 * 1: USBSS_DEV will not terminate Far-end receiver termination
 *    detection sequence
 */
#घोषणा DBG_LINK1_RXDET_BREAK_DIS		BIT(16)
/* LFPS_GEN_PING value This parameter configures the LFPS.Ping generation */
#घोषणा DBG_LINK1_LFPS_GEN_PING(p)		(((p) << 17) & GENMASK(21, 17))
/*
 * Set the LFPS_MIN_DET_U1_EXIT value Writing '1' to this bit ग_लिखोs the
 * LFPS_MIN_DET_U1_EXIT field value to the device. This bit is स्वतःmatically
 * cleared. Writing '0' has no effect
 */
#घोषणा DBG_LINK1_LFPS_MIN_DET_U1_EXIT_SET	BIT(24)
/*
 * Set the LFPS_MIN_GEN_U1_EXIT value. Writing '1' to this bit ग_लिखोs the
 * LFPS_MIN_GEN_U1_EXIT field value to the device. This bit is स्वतःmatically
 * cleared. Writing '0' has no effect
 */
#घोषणा DBG_LINK1_LFPS_MIN_GEN_U1_EXIT_SET	BIT(25)
/*
 * Set the RXDET_BREAK_DIS value Writing '1' to this bit ग_लिखोs
 * the RXDET_BREAK_DIS field value to the device. This bit is स्वतःmatically
 * cleared. Writing '0' has no effect
 */
#घोषणा DBG_LINK1_RXDET_BREAK_DIS_SET		BIT(26)
/*
 * Set the LFPS_GEN_PING_SET value Writing '1' to this bit ग_लिखोs
 * the LFPS_GEN_PING field value to the device. This bit is स्वतःmatically
 * cleared. Writing '0' has no effect."
 */
#घोषणा DBG_LINK1_LFPS_GEN_PING_SET		BIT(27)

/* DMA_AXI_CTRL- biपंचांगasks */
/* The mawprot pin configuration. */
#घोषणा DMA_AXI_CTRL_MARPROT(p) ((p) & GENMASK(2, 0))
/* The marprot pin configuration. */
#घोषणा DMA_AXI_CTRL_MAWPROT(p) (((p) & GENMASK(2, 0)) << 16)
#घोषणा DMA_AXI_CTRL_NON_SECURE 0x02

#घोषणा gadget_to_cdns3_device(g) (container_of(g, काष्ठा cdns3_device, gadget))

#घोषणा ep_to_cdns3_ep(ep) (container_of(ep, काष्ठा cdns3_endpoपूर्णांक, endpoपूर्णांक))

/*-------------------------------------------------------------------------*/
/*
 * USBSS-DEV DMA पूर्णांकerface.
 */
#घोषणा TRBS_PER_SEGMENT	600

#घोषणा ISO_MAX_INTERVAL	10

#घोषणा MAX_TRB_LENGTH          BIT(16)

#अगर TRBS_PER_SEGMENT < 2
#त्रुटि "Incorrect TRBS_PER_SEGMENT. Minimal Transfer Ring size is 2."
#पूर्ण_अगर

#घोषणा TRBS_PER_STREAM_SEGMENT 2

#अगर TRBS_PER_STREAM_SEGMENT < 2
#त्रुटि "Incorrect TRBS_PER_STREAMS_SEGMENT. Minimal Transfer Ring size is 2."
#पूर्ण_अगर

/*
 *Only क्रम ISOC endpoपूर्णांकs - maximum number of TRBs is calculated as
 * घात(2, bInterval-1) * number of usb requests. It is limitation made by
 * driver to save memory. Controller must prepare TRB क्रम each ITP even
 * अगर bInterval > 1. It's the reason why driver needs so many TRBs क्रम
 * isochronous endpoपूर्णांकs.
 */
#घोषणा TRBS_PER_ISOC_SEGMENT	(ISO_MAX_INTERVAL * 8)

#घोषणा GET_TRBS_PER_SEGMENT(ep_type) ((ep_type) == USB_ENDPOINT_XFER_ISOC ? \
				      TRBS_PER_ISOC_SEGMENT : TRBS_PER_SEGMENT)
/**
 * काष्ठा cdns3_trb - represent Transfer Descriptor block.
 * @buffer:	poपूर्णांकer to buffer data
 * @length:	length of data
 * @control:	control flags.
 *
 * This काष्ठाure describes transfer block serviced by DMA module.
 */
काष्ठा cdns3_trb अणु
	__le32 buffer;
	__le32 length;
	__le32 control;
पूर्ण;

#घोषणा TRB_SIZE		(माप(काष्ठा cdns3_trb))
#घोषणा TRB_RING_SIZE		(TRB_SIZE * TRBS_PER_SEGMENT)
#घोषणा TRB_STREAM_RING_SIZE	(TRB_SIZE * TRBS_PER_STREAM_SEGMENT)
#घोषणा TRB_ISO_RING_SIZE	(TRB_SIZE * TRBS_PER_ISOC_SEGMENT)
#घोषणा TRB_CTRL_RING_SIZE	(TRB_SIZE * 2)

/* TRB bit mask */
#घोषणा TRB_TYPE_BITMASK	GENMASK(15, 10)
#घोषणा TRB_TYPE(p)		((p) << 10)
#घोषणा TRB_FIELD_TO_TYPE(p)	(((p) & TRB_TYPE_BITMASK) >> 10)

/* TRB type IDs */
/* bulk, पूर्णांकerrupt, isoc , and control data stage */
#घोषणा TRB_NORMAL		1
/* TRB क्रम linking ring segments */
#घोषणा TRB_LINK		6

/* Cycle bit - indicates TRB ownership by driver or hw*/
#घोषणा TRB_CYCLE		BIT(0)
/*
 * When set to '1', the device will toggle its पूर्णांकerpretation of the Cycle bit
 */
#घोषणा TRB_TOGGLE		BIT(1)
/*
 * The controller will set it अगर OUTSMM (OUT size mismatch) is detected,
 * this bit is क्रम normal TRB
 */
#घोषणा TRB_SMM			BIT(1)

/*
 * Short Packet (SP). OUT EPs at DMULT=1 only. Indicates अगर the TRB was
 * processed जबतक USB लघु packet was received. No more buffers defined by
 * the TD will be used. DMA will स्वतःmatically advance to next TD.
 * - Shall be set to 0 by Software when putting TRB on the Transfer Ring
 * - Shall be set to 1 by Controller when Short Packet condition क्रम this TRB
 *   is detected independent अगर ISP is set or not.
 */
#घोषणा TRB_SP			BIT(1)

/* Interrupt on लघु packet*/
#घोषणा TRB_ISP			BIT(2)
/*Setting this bit enables FIFO DMA operation mode*/
#घोषणा TRB_FIFO_MODE		BIT(3)
/* Set PCIe no snoop attribute */
#घोषणा TRB_CHAIN		BIT(4)
/* Interrupt on completion */
#घोषणा TRB_IOC			BIT(5)

/* stream ID biपंचांगasks. */
#घोषणा TRB_STREAM_ID_BITMASK		GENMASK(31, 16)
#घोषणा TRB_STREAM_ID(p)		((p) << 16)
#घोषणा TRB_FIELD_TO_STREAMID(p)	(((p) & TRB_STREAM_ID_BITMASK) >> 16)

/* Size of TD expressed in USB packets क्रम HS/FS mode. */
#घोषणा TRB_TDL_HS_SIZE(p)	(((p) << 16) & GENMASK(31, 16))
#घोषणा TRB_TDL_HS_SIZE_GET(p)	(((p) & GENMASK(31, 16)) >> 16)

/* transfer_len biपंचांगasks. */
#घोषणा TRB_LEN(p)		((p) & GENMASK(16, 0))

/* Size of TD expressed in USB packets क्रम SS mode. */
#घोषणा TRB_TDL_SS_SIZE(p)	(((p) << 17) & GENMASK(23, 17))
#घोषणा TRB_TDL_SS_SIZE_GET(p)	(((p) & GENMASK(23, 17)) >> 17)

/* transfer_len biपंचांगasks - bits 31:24 */
#घोषणा TRB_BURST_LEN(p)	((अचिन्हित पूर्णांक)((p) << 24) & GENMASK(31, 24))
#घोषणा TRB_BURST_LEN_GET(p)	(((p) & GENMASK(31, 24)) >> 24)

/* Data buffer poपूर्णांकer biपंचांगasks*/
#घोषणा TRB_BUFFER(p)		((p) & GENMASK(31, 0))

/*-------------------------------------------------------------------------*/
/* Driver numeric स्थिरants */

/* Such declaration should be added to ch9.h */
#घोषणा USB_DEVICE_MAX_ADDRESS		127

/* Endpoपूर्णांक init values */
#घोषणा CDNS3_EP_MAX_PACKET_LIMIT	1024
#घोषणा CDNS3_EP_MAX_STREAMS		15
#घोषणा CDNS3_EP0_MAX_PACKET_LIMIT	512

/* All endpoपूर्णांकs including EP0 */
#घोषणा CDNS3_ENDPOINTS_MAX_COUNT	32
#घोषणा CDNS3_EP_ZLP_BUF_SIZE		1024

#घोषणा CDNS3_EP_BUF_SIZE		4	/* KB */
#घोषणा CDNS3_EP_ISO_HS_MULT		3
#घोषणा CDNS3_EP_ISO_SS_BURST		3
#घोषणा CDNS3_MAX_NUM_DESCMISS_BUF	32
#घोषणा CDNS3_DESCMIS_BUF_SIZE		2048	/* Bytes */
#घोषणा CDNS3_WA2_NUM_BUFFERS		128
/*-------------------------------------------------------------------------*/
/* Used काष्ठाs */

काष्ठा cdns3_device;

/**
 * काष्ठा cdns3_endpoपूर्णांक - extended device side representation of USB endpoपूर्णांक.
 * @endpoपूर्णांक: usb endpoपूर्णांक
 * @pending_req_list: list of requests queuing on transfer ring.
 * @deferred_req_list: list of requests रुकोing क्रम queuing on transfer ring.
 * @wa2_descmiss_req_list: list of requests पूर्णांकernally allocated by driver.
 * @trb_pool: transfer ring - array of transaction buffers
 * @trb_pool_dma: dma address of transfer ring
 * @cdns3_dev: device associated with this endpoपूर्णांक
 * @name: a human पढ़ोable name e.g. ep1out
 * @flags: specअगरy the current state of endpoपूर्णांक
 * @descmis_req: पूर्णांकernal transfer object used क्रम getting data from on-chip
 *     buffer. It can happen only अगर function driver करोesn't send usb_request
 *     object on समय.
 * @dir: endpoपूर्णांक direction
 * @num: endpoपूर्णांक number (1 - 15)
 * @type: set to bmAttributes & USB_ENDPOINT_XFERTYPE_MASK
 * @पूर्णांकerval: पूर्णांकerval between packets used क्रम ISOC endpoपूर्णांक.
 * @मुक्त_trbs: number of मुक्त TRBs in transfer ring
 * @num_trbs: number of all TRBs in transfer ring
 * @alloc_ring_size: size of the allocated TRB ring
 * @pcs: producer cycle state
 * @ccs: consumer cycle state
 * @enqueue: enqueue index in transfer ring
 * @dequeue: dequeue index in transfer ring
 * @trb_burst_size: number of burst used in trb.
 */
काष्ठा cdns3_endpoपूर्णांक अणु
	काष्ठा usb_ep		endpoपूर्णांक;
	काष्ठा list_head	pending_req_list;
	काष्ठा list_head	deferred_req_list;
	काष्ठा list_head	wa2_descmiss_req_list;
	पूर्णांक			wa2_counter;

	काष्ठा cdns3_trb	*trb_pool;
	dma_addr_t		trb_pool_dma;

	काष्ठा cdns3_device	*cdns3_dev;
	अक्षर			name[20];

#घोषणा EP_ENABLED		BIT(0)
#घोषणा EP_STALLED		BIT(1)
#घोषणा EP_STALL_PENDING	BIT(2)
#घोषणा EP_WEDGE		BIT(3)
#घोषणा EP_TRANSFER_STARTED	BIT(4)
#घोषणा EP_UPDATE_EP_TRBADDR	BIT(5)
#घोषणा EP_PENDING_REQUEST	BIT(6)
#घोषणा EP_RING_FULL		BIT(7)
#घोषणा EP_CLAIMED		BIT(8)
#घोषणा EP_DEFERRED_DRDY	BIT(9)
#घोषणा EP_QUIRK_ISO_OUT_EN	BIT(10)
#घोषणा EP_QUIRK_END_TRANSFER	BIT(11)
#घोषणा EP_QUIRK_EXTRA_BUF_DET	BIT(12)
#घोषणा EP_QUIRK_EXTRA_BUF_EN	BIT(13)
#घोषणा EP_TDLCHK_EN		BIT(15)
#घोषणा EP_CONFIGURED		BIT(16)
	u32			flags;

	काष्ठा cdns3_request	*descmis_req;

	u8			dir;
	u8			num;
	u8			type;
	पूर्णांक			पूर्णांकerval;

	पूर्णांक			मुक्त_trbs;
	पूर्णांक			num_trbs;
	पूर्णांक			alloc_ring_size;
	u8			pcs;
	u8			ccs;
	पूर्णांक			enqueue;
	पूर्णांक			dequeue;
	u8			trb_burst_size;

	अचिन्हित पूर्णांक		wa1_set:1;
	काष्ठा cdns3_trb	*wa1_trb;
	अचिन्हित पूर्णांक		wa1_trb_index;
	अचिन्हित पूर्णांक		wa1_cycle_bit:1;

	/* Stream related */
	अचिन्हित पूर्णांक		use_streams:1;
	अचिन्हित पूर्णांक		prime_flag:1;
	u32			ep_sts_pending;
	u16			last_stream_id;
	u16			pending_tdl;
	अचिन्हित पूर्णांक		stream_sg_idx;
पूर्ण;

/**
 * काष्ठा cdns3_aligned_buf - represent aligned buffer used क्रम DMA transfer
 * @buf: aligned to 8 bytes data buffer. Buffer address used in
 *       TRB shall be aligned to 8.
 * @dma: dma address
 * @size: size of buffer
 * @in_use: inक्रमm अगर this buffer is associated with usb_request
 * @list: used to adding instance of this object to list
 */
काष्ठा cdns3_aligned_buf अणु
	व्योम			*buf;
	dma_addr_t		dma;
	u32			size;
	क्रमागत dma_data_direction dir;
	अचिन्हित		in_use:1;
	काष्ठा list_head	list;
पूर्ण;

/**
 * काष्ठा cdns3_request - extended device side representation of usb_request
 *                        object .
 * @request: generic usb_request object describing single I/O request.
 * @priv_ep: extended representation of usb_ep object
 * @trb: the first TRB association with this request
 * @start_trb: number of the first TRB in transfer ring
 * @end_trb: number of the last TRB in transfer ring
 * @aligned_buf: object holds inक्रमmation about aligned buffer associated whit
 *               this endpoपूर्णांक
 * @flags: flag specअगरying special usage of request
 * @list: used by पूर्णांकernally allocated request to add to wa2_descmiss_req_list.
 * @finished_trb: number of trb has alपढ़ोy finished per request
 * @num_of_trb: how many trbs in this request
 */
काष्ठा cdns3_request अणु
	काष्ठा usb_request		request;
	काष्ठा cdns3_endpoपूर्णांक		*priv_ep;
	काष्ठा cdns3_trb		*trb;
	पूर्णांक				start_trb;
	पूर्णांक				end_trb;
	काष्ठा cdns3_aligned_buf	*aligned_buf;
#घोषणा REQUEST_PENDING			BIT(0)
#घोषणा REQUEST_INTERNAL		BIT(1)
#घोषणा REQUEST_INTERNAL_CH		BIT(2)
#घोषणा REQUEST_ZLP			BIT(3)
#घोषणा REQUEST_UNALIGNED		BIT(4)
	u32				flags;
	काष्ठा list_head		list;
	पूर्णांक				finished_trb;
	पूर्णांक				num_of_trb;
पूर्ण;

#घोषणा to_cdns3_request(r) (container_of(r, काष्ठा cdns3_request, request))

/*Stages used during क्रमागतeration process.*/
#घोषणा CDNS3_SETUP_STAGE		0x0
#घोषणा CDNS3_DATA_STAGE		0x1
#घोषणा CDNS3_STATUS_STAGE		0x2

/**
 * काष्ठा cdns3_device - represent USB device.
 * @dev: poपूर्णांकer to device काष्ठाure associated whit this controller
 * @sysdev: poपूर्णांकer to the DMA capable device
 * @gadget: device side representation of the peripheral controller
 * @gadget_driver: poपूर्णांकer to the gadget driver
 * @dev_ver: device controller version.
 * @lock: क्रम synchronizing
 * @regs: base address क्रम device side रेजिस्टरs
 * @setup_buf: used जबतक processing usb control requests
 * @setup_dma: dma address क्रम setup_buf
 * @zlp_buf - zlp buffer
 * @ep0_stage: ep0 stage during क्रमागतeration process.
 * @ep0_data_dir: direction क्रम control transfer
 * @eps: array of poपूर्णांकers to all endpoपूर्णांकs with exclusion ep0
 * @aligned_buf_list: list of aligned buffers पूर्णांकernally allocated by driver
 * @aligned_buf_wq: workqueue मुक्तing  no दीर्घer used aligned buf.
 * @selected_ep: actually selected endpoपूर्णांक. It's used only to improve
 *               perक्रमmance.
 * @isoch_delay: value from Set Isoch Delay request. Only valid on SS/SSP.
 * @u1_allowed: allow device transition to u1 state
 * @u2_allowed: allow device transition to u2 state
 * @is_selfघातered: device is self घातered
 * @setup_pending: setup packet is processing by gadget driver
 * @hw_configured_flag: hardware endpoपूर्णांक configuration was set.
 * @wake_up_flag: allow device to remote up the host
 * @status_completion_no_call: indicate that driver is रुकोing क्रम status s
 *     stage completion. It's used in deferred SET_CONFIGURATION request.
 * @onchip_buffers: number of available on-chip buffers.
 * @onchip_used_size: actual size of on-chip memory asचिन्हित to endpoपूर्णांकs.
 * @pending_status_wq: workqueue handling status stage क्रम deferred requests.
 * @pending_status_request: request क्रम which status stage was deferred
 */
काष्ठा cdns3_device अणु
	काष्ठा device			*dev;
	काष्ठा device			*sysdev;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*gadget_driver;

#घोषणा CDNS_REVISION_V0		0x00024501
#घोषणा CDNS_REVISION_V1		0x00024509
	u32				dev_ver;

	/* generic spin-lock क्रम drivers */
	spinlock_t			lock;

	काष्ठा cdns3_usb_regs		__iomem *regs;

	काष्ठा dma_pool			*eps_dma_pool;
	काष्ठा usb_ctrlrequest		*setup_buf;
	dma_addr_t			setup_dma;
	व्योम				*zlp_buf;

	u8				ep0_stage;
	पूर्णांक				ep0_data_dir;

	काष्ठा cdns3_endpoपूर्णांक		*eps[CDNS3_ENDPOINTS_MAX_COUNT];

	काष्ठा list_head		aligned_buf_list;
	काष्ठा work_काष्ठा		aligned_buf_wq;

	u32				selected_ep;
	u16				isoch_delay;

	अचिन्हित			रुको_क्रम_setup:1;
	अचिन्हित			u1_allowed:1;
	अचिन्हित			u2_allowed:1;
	अचिन्हित			is_selfघातered:1;
	अचिन्हित			setup_pending:1;
	अचिन्हित			hw_configured_flag:1;
	अचिन्हित			wake_up_flag:1;
	अचिन्हित			status_completion_no_call:1;
	अचिन्हित			using_streams:1;
	पूर्णांक				out_mem_is_allocated;

	काष्ठा work_काष्ठा		pending_status_wq;
	काष्ठा usb_request		*pending_status_request;

	/*in KB */
	u16				onchip_buffers;
	u16				onchip_used_size;
पूर्ण;

व्योम cdns3_set_रेजिस्टर_bit(व्योम __iomem *ptr, u32 mask);
dma_addr_t cdns3_trb_virt_to_dma(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				 काष्ठा cdns3_trb *trb);
क्रमागत usb_device_speed cdns3_get_speed(काष्ठा cdns3_device *priv_dev);
व्योम cdns3_pending_setup_status_handler(काष्ठा work_काष्ठा *work);
व्योम cdns3_hw_reset_eps_config(काष्ठा cdns3_device *priv_dev);
व्योम cdns3_set_hw_configuration(काष्ठा cdns3_device *priv_dev);
व्योम cdns3_select_ep(काष्ठा cdns3_device *priv_dev, u32 ep);
व्योम cdns3_allow_enable_l1(काष्ठा cdns3_device *priv_dev, पूर्णांक enable);
काष्ठा usb_request *cdns3_next_request(काष्ठा list_head *list);
व्योम cdns3_rearm_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep, u8 rearm);
पूर्णांक cdns3_allocate_trb_pool(काष्ठा cdns3_endpoपूर्णांक *priv_ep);
u8 cdns3_ep_addr_to_index(u8 ep_addr);
पूर्णांक cdns3_gadget_ep_set_wedge(काष्ठा usb_ep *ep);
पूर्णांक cdns3_gadget_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value);
व्योम __cdns3_gadget_ep_set_halt(काष्ठा cdns3_endpoपूर्णांक *priv_ep);
पूर्णांक __cdns3_gadget_ep_clear_halt(काष्ठा cdns3_endpoपूर्णांक *priv_ep);
काष्ठा usb_request *cdns3_gadget_ep_alloc_request(काष्ठा usb_ep *ep,
						  gfp_t gfp_flags);
व्योम cdns3_gadget_ep_मुक्त_request(काष्ठा usb_ep *ep,
				  काष्ठा usb_request *request);
पूर्णांक cdns3_gadget_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *request);
व्योम cdns3_gadget_giveback(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
			   काष्ठा cdns3_request *priv_req,
			   पूर्णांक status);

पूर्णांक cdns3_init_ep0(काष्ठा cdns3_device *priv_dev,
		   काष्ठा cdns3_endpoपूर्णांक *priv_ep);
व्योम cdns3_ep0_config(काष्ठा cdns3_device *priv_dev);
पूर्णांक cdns3_ep_config(काष्ठा cdns3_endpoपूर्णांक *priv_ep, bool enable);
व्योम cdns3_check_ep0_पूर्णांकerrupt_proceed(काष्ठा cdns3_device *priv_dev, पूर्णांक dir);
पूर्णांक __cdns3_gadget_wakeup(काष्ठा cdns3_device *priv_dev);

#पूर्ण_अगर /* __LINUX_CDNS3_GADGET */
