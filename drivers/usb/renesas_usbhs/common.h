<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ */
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित RENESAS_USB_DRIVER_H
#घोषणा RENESAS_USB_DRIVER_H

#समावेश <linux/clk.h>
#समावेश <linux/extcon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/usb/renesas_usbhs.h>

काष्ठा usbhs_priv;

#समावेश "mod.h"
#समावेश "pipe.h"

/*
 *
 *		रेजिस्टर define
 *
 */
#घोषणा SYSCFG		0x0000
#घोषणा BUSWAIT		0x0002
#घोषणा DVSTCTR		0x0008
#घोषणा TESTMODE	0x000C
#घोषणा CFIFO		0x0014
#घोषणा CFIFOSEL	0x0020
#घोषणा CFIFOCTR	0x0022
#घोषणा D0FIFO		0x0100
#घोषणा D0FIFOSEL	0x0028
#घोषणा D0FIFOCTR	0x002A
#घोषणा D1FIFO		0x0120
#घोषणा D1FIFOSEL	0x002C
#घोषणा D1FIFOCTR	0x002E
#घोषणा INTENB0		0x0030
#घोषणा INTENB1		0x0032
#घोषणा BRDYENB		0x0036
#घोषणा NRDYENB		0x0038
#घोषणा BEMPENB		0x003A
#घोषणा INTSTS0		0x0040
#घोषणा INTSTS1		0x0042
#घोषणा BRDYSTS		0x0046
#घोषणा NRDYSTS		0x0048
#घोषणा BEMPSTS		0x004A
#घोषणा FRMNUM		0x004C
#घोषणा USBREQ		0x0054	/* USB request type रेजिस्टर */
#घोषणा USBVAL		0x0056	/* USB request value रेजिस्टर */
#घोषणा USBINDX		0x0058	/* USB request index रेजिस्टर */
#घोषणा USBLENG		0x005A	/* USB request length रेजिस्टर */
#घोषणा DCPCFG		0x005C
#घोषणा DCPMAXP		0x005E
#घोषणा DCPCTR		0x0060
#घोषणा PIPESEL		0x0064
#घोषणा PIPECFG		0x0068
#घोषणा PIPEBUF		0x006A
#घोषणा PIPEMAXP	0x006C
#घोषणा PIPEPERI	0x006E
#घोषणा PIPEnCTR	0x0070
#घोषणा PIPE1TRE	0x0090
#घोषणा PIPE1TRN	0x0092
#घोषणा PIPE2TRE	0x0094
#घोषणा PIPE2TRN	0x0096
#घोषणा PIPE3TRE	0x0098
#घोषणा PIPE3TRN	0x009A
#घोषणा PIPE4TRE	0x009C
#घोषणा PIPE4TRN	0x009E
#घोषणा PIPE5TRE	0x00A0
#घोषणा PIPE5TRN	0x00A2
#घोषणा PIPEBTRE	0x00A4
#घोषणा PIPEBTRN	0x00A6
#घोषणा PIPECTRE	0x00A8
#घोषणा PIPECTRN	0x00AA
#घोषणा PIPEDTRE	0x00AC
#घोषणा PIPEDTRN	0x00AE
#घोषणा PIPEETRE	0x00B0
#घोषणा PIPEETRN	0x00B2
#घोषणा PIPEFTRE	0x00B4
#घोषणा PIPEFTRN	0x00B6
#घोषणा PIPE9TRE	0x00B8
#घोषणा PIPE9TRN	0x00BA
#घोषणा PIPEATRE	0x00BC
#घोषणा PIPEATRN	0x00BE
#घोषणा DEVADD0		0x00D0 /* Device address n configuration */
#घोषणा DEVADD1		0x00D2
#घोषणा DEVADD2		0x00D4
#घोषणा DEVADD3		0x00D6
#घोषणा DEVADD4		0x00D8
#घोषणा DEVADD5		0x00DA
#घोषणा DEVADD6		0x00DC
#घोषणा DEVADD7		0x00DE
#घोषणा DEVADD8		0x00E0
#घोषणा DEVADD9		0x00E2
#घोषणा DEVADDA		0x00E4
#घोषणा D2FIFOSEL	0x00F0	/* क्रम R-Car Gen2 */
#घोषणा D2FIFOCTR	0x00F2	/* क्रम R-Car Gen2 */
#घोषणा D3FIFOSEL	0x00F4	/* क्रम R-Car Gen2 */
#घोषणा D3FIFOCTR	0x00F6	/* क्रम R-Car Gen2 */
#घोषणा SUSPMODE	0x0102	/* क्रम RZ/A */

/* SYSCFG */
#घोषणा SCKE	(1 << 10)	/* USB Module Clock Enable */
#घोषणा CNEN	(1 << 8)	/* Single-ended receiver operation Enable */
#घोषणा HSE	(1 << 7)	/* High-Speed Operation Enable */
#घोषणा DCFM	(1 << 6)	/* Controller Function Select */
#घोषणा DRPD	(1 << 5)	/* D+ Line/D- Line Resistance Control */
#घोषणा DPRPU	(1 << 4)	/* D+ Line Resistance Control */
#घोषणा USBE	(1 << 0)	/* USB Module Operation Enable */
#घोषणा UCKSEL	(1 << 2)	/* Clock Select क्रम RZ/A1 */
#घोषणा UPLLE	(1 << 1)	/* USB PLL Enable क्रम RZ/A1 */

/* DVSTCTR */
#घोषणा EXTLP	(1 << 10)	/* Controls the EXTLP pin output state */
#घोषणा PWEN	(1 << 9)	/* Controls the PWEN pin output state */
#घोषणा USBRST	(1 << 6)	/* Bus Reset Output */
#घोषणा UACT	(1 << 4)	/* USB Bus Enable */
#घोषणा RHST	(0x7)		/* Reset Handshake */
#घोषणा  RHST_LOW_SPEED  1	/* Low-speed connection */
#घोषणा  RHST_FULL_SPEED 2	/* Full-speed connection */
#घोषणा  RHST_HIGH_SPEED 3	/* High-speed connection */

/* CFIFOSEL */
#घोषणा DREQE	(1 << 12)	/* DMA Transfer Request Enable */
#घोषणा MBW_32	(0x2 << 10)	/* CFIFO Port Access Bit Width */

/* CFIFOCTR */
#घोषणा BVAL	(1 << 15)	/* Buffer Memory Enable Flag */
#घोषणा BCLR	(1 << 14)	/* CPU buffer clear */
#घोषणा FRDY	(1 << 13)	/* FIFO Port Ready */
#घोषणा DTLN_MASK (0x0FFF)	/* Receive Data Length */

/* INTENB0 */
#घोषणा VBSE	(1 << 15)	/* Enable IRQ VBUS_0 and VBUSIN_0 */
#घोषणा RSME	(1 << 14)	/* Enable IRQ Resume */
#घोषणा SOFE	(1 << 13)	/* Enable IRQ Frame Number Update */
#घोषणा DVSE	(1 << 12)	/* Enable IRQ Device State Transition */
#घोषणा CTRE	(1 << 11)	/* Enable IRQ Control Stage Transition */
#घोषणा BEMPE	(1 << 10)	/* Enable IRQ Buffer Empty */
#घोषणा NRDYE	(1 << 9)	/* Enable IRQ Buffer Not Ready Response */
#घोषणा BRDYE	(1 << 8)	/* Enable IRQ Buffer Ready */

/* INTENB1 */
#घोषणा BCHGE	(1 << 14)	/* USB Bus Change Interrupt Enable */
#घोषणा DTCHE	(1 << 12)	/* Disconnection Detect Interrupt Enable */
#घोषणा ATTCHE	(1 << 11)	/* Connection Detect Interrupt Enable */
#घोषणा खातापूर्णERRE	(1 << 6)	/* खातापूर्ण Error Detect Interrupt Enable */
#घोषणा SIGNE	(1 << 5)	/* Setup Transaction Error Interrupt Enable */
#घोषणा SACKE	(1 << 4)	/* Setup Transaction ACK Interrupt Enable */

/* INTSTS0 */
#घोषणा VBINT	(1 << 15)	/* VBUS0_0 and VBUS1_0 Interrupt Status */
#घोषणा DVST	(1 << 12)	/* Device State Transition Interrupt Status */
#घोषणा CTRT	(1 << 11)	/* Control Stage Interrupt Status */
#घोषणा BEMP	(1 << 10)	/* Buffer Empty Interrupt Status */
#घोषणा BRDY	(1 << 8)	/* Buffer Ready Interrupt Status */
#घोषणा VBSTS	(1 << 7)	/* VBUS_0 and VBUSIN_0 Input Status */
#घोषणा VALID	(1 << 3)	/* USB Request Receive */

#घोषणा DVSQ_MASK		(0x7 << 4)	/* Device State */
#घोषणा  POWER_STATE		(0 << 4)
#घोषणा  DEFAULT_STATE		(1 << 4)
#घोषणा  ADDRESS_STATE		(2 << 4)
#घोषणा  CONFIGURATION_STATE	(3 << 4)
#घोषणा  SUSPENDED_STATE	(4 << 4)

#घोषणा CTSQ_MASK		(0x7)	/* Control Transfer Stage */
#घोषणा  IDLE_SETUP_STAGE	0	/* Idle stage or setup stage */
#घोषणा  READ_DATA_STAGE	1	/* Control पढ़ो data stage */
#घोषणा  READ_STATUS_STAGE	2	/* Control पढ़ो status stage */
#घोषणा  WRITE_DATA_STAGE	3	/* Control ग_लिखो data stage */
#घोषणा  WRITE_STATUS_STAGE	4	/* Control ग_लिखो status stage */
#घोषणा  NODATA_STATUS_STAGE	5	/* Control ग_लिखो NoData status stage */
#घोषणा  SEQUENCE_ERROR		6	/* Control transfer sequence error */

/* INTSTS1 */
#घोषणा OVRCR	(1 << 15) /* OVRCR Interrupt Status */
#घोषणा BCHG	(1 << 14) /* USB Bus Change Interrupt Status */
#घोषणा DTCH	(1 << 12) /* USB Disconnection Detect Interrupt Status */
#घोषणा ATTCH	(1 << 11) /* ATTCH Interrupt Status */
#घोषणा खातापूर्णERR	(1 << 6)  /* खातापूर्ण Error Detect Interrupt Status */
#घोषणा SIGN	(1 << 5)  /* Setup Transaction Error Interrupt Status */
#घोषणा SACK	(1 << 4)  /* Setup Transaction ACK Response Interrupt Status */

/* PIPECFG */
/* DCPCFG */
#घोषणा TYPE_NONE	(0 << 14)	/* Transfer Type */
#घोषणा TYPE_BULK	(1 << 14)
#घोषणा TYPE_INT	(2 << 14)
#घोषणा TYPE_ISO	(3 << 14)
#घोषणा BFRE		(1 << 10)	/* BRDY Interrupt Operation Spec. */
#घोषणा DBLB		(1 << 9)	/* Double Buffer Mode */
#घोषणा SHTNAK		(1 << 7)	/* Pipe Disable in Transfer End */
#घोषणा सूची_OUT		(1 << 4)	/* Transfer Direction */

/* PIPEMAXP */
/* DCPMAXP */
#घोषणा DEVSEL_MASK	(0xF << 12)	/* Device Select */
#घोषणा DCP_MAXP_MASK	(0x7F)
#घोषणा PIPE_MAXP_MASK	(0x7FF)

/* PIPEBUF */
#घोषणा बफ_मानE_SHIFT	10
#घोषणा बफ_मानE_MASK	(0x1F << बफ_मानE_SHIFT)
#घोषणा BUFNMB_MASK	(0xFF)

/* PIPEnCTR */
/* DCPCTR */
#घोषणा BSTS		(1 << 15)	/* Buffer Status */
#घोषणा SUREQ		(1 << 14)	/* Sending SETUP Token */
#घोषणा INBUFM		(1 << 14)	/* (PIPEnCTR) Transfer Buffer Monitor */
#घोषणा CSSTS		(1 << 12)	/* CSSTS Status */
#घोषणा	ACLRM		(1 << 9)	/* Buffer Auto-Clear Mode */
#घोषणा SQCLR		(1 << 8)	/* Toggle Bit Clear */
#घोषणा SQSET		(1 << 7)	/* Toggle Bit Set */
#घोषणा SQMON		(1 << 6)	/* Toggle Bit Check */
#घोषणा PBUSY		(1 << 5)	/* Pipe Busy */
#घोषणा PID_MASK	(0x3)		/* Response PID */
#घोषणा  PID_NAK	0
#घोषणा  PID_BUF	1
#घोषणा  PID_STALL10	2
#घोषणा  PID_STALL11	3

#घोषणा CCPL		(1 << 2)	/* Control Transfer End Enable */

/* PIPEnTRE */
#घोषणा TRENB		(1 << 9)	/* Transaction Counter Enable */
#घोषणा TRCLR		(1 << 8)	/* Transaction Counter Clear */

/* FRMNUM */
#घोषणा FRNM_MASK	(0x7FF)

/* DEVADDn */
#घोषणा UPPHUB(x)	(((x) & 0xF) << 11)	/* HUB Register */
#घोषणा HUBPORT(x)	(((x) & 0x7) << 8)	/* HUB Port क्रम Target Device */
#घोषणा USBSPD(x)	(((x) & 0x3) << 6)	/* Device Transfer Rate */
#घोषणा USBSPD_SPEED_LOW	0x1
#घोषणा USBSPD_SPEED_FULL	0x2
#घोषणा USBSPD_SPEED_HIGH	0x3

/* SUSPMODE */
#घोषणा SUSPM		(1 << 14)	/* SuspendM Control */

/*
 *		काष्ठा
 */
काष्ठा usbhs_priv अणु

	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ irqflags;

	स्थिर काष्ठा renesas_usbhs_platक्रमm_callback *pfunc;
	काष्ठा renesas_usbhs_driver_param	dparam;

	काष्ठा delayed_work notअगरy_hotplug_work;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा extcon_dev *edev;

	spinlock_t		lock;

	/*
	 * module control
	 */
	काष्ठा usbhs_mod_info mod_info;

	/*
	 * pipe control
	 */
	काष्ठा usbhs_pipe_info pipe_info;

	/*
	 * fअगरo control
	 */
	काष्ठा usbhs_fअगरo_info fअगरo_info;

	काष्ठा phy *phy;
	काष्ठा reset_control *rsts;
	काष्ठा clk *clks[2];
पूर्ण;

/*
 * common
 */
u16 usbhs_पढ़ो(काष्ठा usbhs_priv *priv, u32 reg);
व्योम usbhs_ग_लिखो(काष्ठा usbhs_priv *priv, u32 reg, u16 data);
व्योम usbhs_bset(काष्ठा usbhs_priv *priv, u32 reg, u16 mask, u16 data);

#घोषणा usbhs_lock(p, f) spin_lock_irqsave(usbhs_priv_to_lock(p), f)
#घोषणा usbhs_unlock(p, f) spin_unlock_irqrestore(usbhs_priv_to_lock(p), f)

पूर्णांक usbhs_get_id_as_gadget(काष्ठा platक्रमm_device *pdev);

/*
 * sysconfig
 */
व्योम usbhs_sys_host_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable);
व्योम usbhs_sys_function_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable);
व्योम usbhs_sys_function_pullup(काष्ठा usbhs_priv *priv, पूर्णांक enable);
व्योम usbhs_sys_set_test_mode(काष्ठा usbhs_priv *priv, u16 mode);

/*
 * usb request
 */
व्योम usbhs_usbreq_get_val(काष्ठा usbhs_priv *priv, काष्ठा usb_ctrlrequest *req);
व्योम usbhs_usbreq_set_val(काष्ठा usbhs_priv *priv, काष्ठा usb_ctrlrequest *req);

/*
 * bus
 */
व्योम usbhs_bus_send_sof_enable(काष्ठा usbhs_priv *priv);
व्योम usbhs_bus_send_reset(काष्ठा usbhs_priv *priv);
पूर्णांक usbhs_bus_get_speed(काष्ठा usbhs_priv *priv);
पूर्णांक usbhs_vbus_ctrl(काष्ठा usbhs_priv *priv, पूर्णांक enable);
पूर्णांक usbhsc_schedule_notअगरy_hotplug(काष्ठा platक्रमm_device *pdev);

/*
 * frame
 */
पूर्णांक usbhs_frame_get_num(काष्ठा usbhs_priv *priv);

/*
 * device config
 */
पूर्णांक usbhs_set_device_config(काष्ठा usbhs_priv *priv, पूर्णांक devnum, u16 upphub,
			   u16 hubport, u16 speed);

/*
 * पूर्णांकerrupt functions
 */
व्योम usbhs_xxxsts_clear(काष्ठा usbhs_priv *priv, u16 sts_reg, u16 bit);

/*
 * data
 */
काष्ठा usbhs_priv *usbhs_pdev_to_priv(काष्ठा platक्रमm_device *pdev);
#घोषणा usbhs_get_dparam(priv, param)	(priv->dparam.param)
#घोषणा usbhs_priv_to_pdev(priv)	(priv->pdev)
#घोषणा usbhs_priv_to_dev(priv)		(&priv->pdev->dev)
#घोषणा usbhs_priv_to_lock(priv)	(&priv->lock)

#पूर्ण_अगर /* RENESAS_USB_DRIVER_H */
