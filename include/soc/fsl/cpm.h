<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPM_H
#घोषणा __CPM_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <soc/fsl/qe/qe.h>

/*
 * SPI Parameter RAM common to QE and CPM.
 */
काष्ठा spi_pram अणु
	__be16	rbase;	/* Rx Buffer descriptor base address */
	__be16	tbase;	/* Tx Buffer descriptor base address */
	u8	rfcr;	/* Rx function code */
	u8	tfcr;	/* Tx function code */
	__be16	mrblr;	/* Max receive buffer length */
	__be32	rstate;	/* Internal */
	__be32	rdp;	/* Internal */
	__be16	rbptr;	/* Internal */
	__be16	rbc;	/* Internal */
	__be32	rxपंचांगp;	/* Internal */
	__be32	tstate;	/* Internal */
	__be32	tdp;	/* Internal */
	__be16	tbptr;	/* Internal */
	__be16	tbc;	/* Internal */
	__be32	txपंचांगp;	/* Internal */
	__be32	res;	/* Tx temp. */
	__be16  rpbase;	/* Relocation poपूर्णांकer (CPM1 only) */
	__be16	res1;	/* Reserved */
पूर्ण;

/*
 * USB Controller pram common to QE and CPM.
 */
काष्ठा usb_ctlr अणु
	u8	usb_usmod;
	u8	usb_usadr;
	u8	usb_uscom;
	u8	res1[1];
	__be16	usb_usep[4];
	u8	res2[4];
	__be16	usb_usber;
	u8	res3[2];
	__be16	usb_usbmr;
	u8	res4[1];
	u8	usb_usbs;
	/* Fields करोwn below are QE-only */
	__be16	usb_ussft;
	u8	res5[2];
	__be16	usb_usfrn;
	u8	res6[0x22];
पूर्ण __attribute__ ((packed));

/*
 * Function code bits, usually generic to devices.
 */
#अगर_घोषित CONFIG_CPM1
#घोषणा CPMFCR_GBL	((u_अक्षर)0x00)	/* Flag करोesn't exist in CPM1 */
#घोषणा CPMFCR_TC2	((u_अक्षर)0x00)	/* Flag करोesn't exist in CPM1 */
#घोषणा CPMFCR_DTB	((u_अक्षर)0x00)	/* Flag करोesn't exist in CPM1 */
#घोषणा CPMFCR_BDB	((u_अक्षर)0x00)	/* Flag करोesn't exist in CPM1 */
#अन्यथा
#घोषणा CPMFCR_GBL	((u_अक्षर)0x20)	/* Set memory snooping */
#घोषणा CPMFCR_TC2	((u_अक्षर)0x04)	/* Transfer code 2 value */
#घोषणा CPMFCR_DTB	((u_अक्षर)0x02)	/* Use local bus क्रम data when set */
#घोषणा CPMFCR_BDB	((u_अक्षर)0x01)	/* Use local bus क्रम BD when set */
#पूर्ण_अगर
#घोषणा CPMFCR_EB	((u_अक्षर)0x10)	/* Set big endian byte order */

/* Opcodes common to CPM1 and CPM2
*/
#घोषणा CPM_CR_INIT_TRX		((uलघु)0x0000)
#घोषणा CPM_CR_INIT_RX		((uलघु)0x0001)
#घोषणा CPM_CR_INIT_TX		((uलघु)0x0002)
#घोषणा CPM_CR_HUNT_MODE	((uलघु)0x0003)
#घोषणा CPM_CR_STOP_TX		((uलघु)0x0004)
#घोषणा CPM_CR_GRA_STOP_TX	((uलघु)0x0005)
#घोषणा CPM_CR_RESTART_TX	((uलघु)0x0006)
#घोषणा CPM_CR_CLOSE_RX_BD	((uलघु)0x0007)
#घोषणा CPM_CR_SET_GADDR	((uलघु)0x0008)
#घोषणा CPM_CR_SET_TIMER	((uलघु)0x0008)
#घोषणा CPM_CR_STOP_IDMA	((uलघु)0x000b)

/* Buffer descriptors used by many of the CPM protocols. */
प्रकार काष्ठा cpm_buf_desc अणु
	uलघु	cbd_sc;		/* Status and Control */
	uलघु	cbd_datlen;	/* Data length in buffer */
	uपूर्णांक	cbd_bufaddr;	/* Buffer address in host memory */
पूर्ण cbd_t;

/* Buffer descriptor control/status used by serial
 */

#घोषणा BD_SC_EMPTY	(0x8000)	/* Receive is empty */
#घोषणा BD_SC_READY	(0x8000)	/* Transmit is पढ़ोy */
#घोषणा BD_SC_WRAP	(0x2000)	/* Last buffer descriptor */
#घोषणा BD_SC_INTRPT	(0x1000)	/* Interrupt on change */
#घोषणा BD_SC_LAST	(0x0800)	/* Last buffer in frame */
#घोषणा BD_SC_TC	(0x0400)	/* Transmit CRC */
#घोषणा BD_SC_CM	(0x0200)	/* Continuous mode */
#घोषणा BD_SC_ID	(0x0100)	/* Rec'd too many idles */
#घोषणा BD_SC_P		(0x0100)	/* xmt preamble */
#घोषणा BD_SC_BR	(0x0020)	/* Break received */
#घोषणा BD_SC_FR	(0x0010)	/* Framing error */
#घोषणा BD_SC_PR	(0x0008)	/* Parity error */
#घोषणा BD_SC_NAK	(0x0004)	/* NAK - did not respond */
#घोषणा BD_SC_OV	(0x0002)	/* Overrun */
#घोषणा BD_SC_UN	(0x0002)	/* Underrun */
#घोषणा BD_SC_CD	(0x0001)	/* */
#घोषणा BD_SC_CL	(0x0001)	/* Collision */

/* Buffer descriptor control/status used by Ethernet receive.
 * Common to SCC and FCC.
 */
#घोषणा BD_ENET_RX_EMPTY	(0x8000)
#घोषणा BD_ENET_RX_WRAP		(0x2000)
#घोषणा BD_ENET_RX_INTR		(0x1000)
#घोषणा BD_ENET_RX_LAST		(0x0800)
#घोषणा BD_ENET_RX_FIRST	(0x0400)
#घोषणा BD_ENET_RX_MISS		(0x0100)
#घोषणा BD_ENET_RX_BC		(0x0080)	/* FCC Only */
#घोषणा BD_ENET_RX_MC		(0x0040)	/* FCC Only */
#घोषणा BD_ENET_RX_LG		(0x0020)
#घोषणा BD_ENET_RX_NO		(0x0010)
#घोषणा BD_ENET_RX_SH		(0x0008)
#घोषणा BD_ENET_RX_CR		(0x0004)
#घोषणा BD_ENET_RX_OV		(0x0002)
#घोषणा BD_ENET_RX_CL		(0x0001)
#घोषणा BD_ENET_RX_STATS	(0x01ff)	/* All status bits */

/* Buffer descriptor control/status used by Ethernet transmit.
 * Common to SCC and FCC.
 */
#घोषणा BD_ENET_TX_READY	(0x8000)
#घोषणा BD_ENET_TX_PAD		(0x4000)
#घोषणा BD_ENET_TX_WRAP		(0x2000)
#घोषणा BD_ENET_TX_INTR		(0x1000)
#घोषणा BD_ENET_TX_LAST		(0x0800)
#घोषणा BD_ENET_TX_TC		(0x0400)
#घोषणा BD_ENET_TX_DEF		(0x0200)
#घोषणा BD_ENET_TX_HB		(0x0100)
#घोषणा BD_ENET_TX_LC		(0x0080)
#घोषणा BD_ENET_TX_RL		(0x0040)
#घोषणा BD_ENET_TX_RCMASK	(0x003c)
#घोषणा BD_ENET_TX_UN		(0x0002)
#घोषणा BD_ENET_TX_CSL		(0x0001)
#घोषणा BD_ENET_TX_STATS	(0x03ff)	/* All status bits */

/* Buffer descriptor control/status used by Transparent mode SCC.
 */
#घोषणा BD_SCC_TX_LAST		(0x0800)

/* Buffer descriptor control/status used by I2C.
 */
#घोषणा BD_I2C_START		(0x0400)

#अगर_घोषित CONFIG_CPM
पूर्णांक cpm_command(u32 command, u8 opcode);
#अन्यथा
अटल अंतरभूत पूर्णांक cpm_command(u32 command, u8 opcode)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPM */

पूर्णांक cpm2_gpiochip_add32(काष्ठा device *dev);

#पूर्ण_अगर
