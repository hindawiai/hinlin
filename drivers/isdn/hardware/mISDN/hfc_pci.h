<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  specअगरic defines क्रम CCD's HFC 2BDS0 PCI chips
 *
 * Author     Werner Cornelius (werner@isdn4linux.de)
 *
 * Copyright 1999  by Werner Cornelius (werner@isdn4linux.de)
 */

/*
 * thresholds क्रम transparent B-channel mode
 * change mask and threshold simultaneously
 */
#घोषणा HFCPCI_BTRANS_THRESHOLD 128
#घोषणा HFCPCI_FILLEMPTY	64
#घोषणा HFCPCI_BTRANS_THRESMASK 0x00

/* defines क्रम PCI config */
#घोषणा PCI_ENA_MEMIO		0x02
#घोषणा PCI_ENA_MASTER		0x04

/* GCI/IOM bus monitor रेजिस्टरs */
#घोषणा HCFPCI_C_I		0x08
#घोषणा HFCPCI_TRxR		0x0C
#घोषणा HFCPCI_MON1_D		0x28
#घोषणा HFCPCI_MON2_D		0x2C

/* GCI/IOM bus बारlot रेजिस्टरs */
#घोषणा HFCPCI_B1_SSL		0x80
#घोषणा HFCPCI_B2_SSL		0x84
#घोषणा HFCPCI_AUX1_SSL		0x88
#घोषणा HFCPCI_AUX2_SSL		0x8C
#घोषणा HFCPCI_B1_RSL		0x90
#घोषणा HFCPCI_B2_RSL		0x94
#घोषणा HFCPCI_AUX1_RSL		0x98
#घोषणा HFCPCI_AUX2_RSL		0x9C

/* GCI/IOM bus data रेजिस्टरs */
#घोषणा HFCPCI_B1_D		0xA0
#घोषणा HFCPCI_B2_D		0xA4
#घोषणा HFCPCI_AUX1_D		0xA8
#घोषणा HFCPCI_AUX2_D		0xAC

/* GCI/IOM bus configuration रेजिस्टरs */
#घोषणा HFCPCI_MST_EMOD		0xB4
#घोषणा HFCPCI_MST_MODE		0xB8
#घोषणा HFCPCI_CONNECT		0xBC


/* Interrupt and status रेजिस्टरs */
#घोषणा HFCPCI_FIFO_EN		0x44
#घोषणा HFCPCI_TRM		0x48
#घोषणा HFCPCI_B_MODE		0x4C
#घोषणा HFCPCI_CHIP_ID		0x58
#घोषणा HFCPCI_CIRM		0x60
#घोषणा HFCPCI_CTMT		0x64
#घोषणा HFCPCI_INT_M1		0x68
#घोषणा HFCPCI_INT_M2		0x6C
#घोषणा HFCPCI_INT_S1		0x78
#घोषणा HFCPCI_INT_S2		0x7C
#घोषणा HFCPCI_STATUS		0x70

/* S/T section रेजिस्टरs */
#घोषणा HFCPCI_STATES		0xC0
#घोषणा HFCPCI_SCTRL		0xC4
#घोषणा HFCPCI_SCTRL_E		0xC8
#घोषणा HFCPCI_SCTRL_R		0xCC
#घोषणा HFCPCI_SQ		0xD0
#घोषणा HFCPCI_CLKDEL		0xDC
#घोषणा HFCPCI_B1_REC		0xF0
#घोषणा HFCPCI_B1_SEND		0xF0
#घोषणा HFCPCI_B2_REC		0xF4
#घोषणा HFCPCI_B2_SEND		0xF4
#घोषणा HFCPCI_D_REC		0xF8
#घोषणा HFCPCI_D_SEND		0xF8
#घोषणा HFCPCI_E_REC		0xFC


/* bits in status रेजिस्टर (READ) */
#घोषणा HFCPCI_PCI_PROC		0x02
#घोषणा HFCPCI_NBUSY		0x04
#घोषणा HFCPCI_TIMER_ELAP	0x10
#घोषणा HFCPCI_STATINT		0x20
#घोषणा HFCPCI_FRAMEINT		0x40
#घोषणा HFCPCI_ANYINT		0x80

/* bits in CTMT (Write) */
#घोषणा HFCPCI_CLTIMER		0x80
#घोषणा HFCPCI_TIM3_125		0x04
#घोषणा HFCPCI_TIM25		0x10
#घोषणा HFCPCI_TIM50		0x14
#घोषणा HFCPCI_TIM400		0x18
#घोषणा HFCPCI_TIM800		0x1C
#घोषणा HFCPCI_AUTO_TIMER	0x20
#घोषणा HFCPCI_TRANSB2		0x02
#घोषणा HFCPCI_TRANSB1		0x01

/* bits in CIRM (Write) */
#घोषणा HFCPCI_AUX_MSK		0x07
#घोषणा HFCPCI_RESET		0x08
#घोषणा HFCPCI_B1_REV		0x40
#घोषणा HFCPCI_B2_REV		0x80

/* bits in INT_M1 and INT_S1 */
#घोषणा HFCPCI_INTS_B1TRANS	0x01
#घोषणा HFCPCI_INTS_B2TRANS	0x02
#घोषणा HFCPCI_INTS_DTRANS	0x04
#घोषणा HFCPCI_INTS_B1REC	0x08
#घोषणा HFCPCI_INTS_B2REC	0x10
#घोषणा HFCPCI_INTS_DREC	0x20
#घोषणा HFCPCI_INTS_L1STATE	0x40
#घोषणा HFCPCI_INTS_TIMER	0x80

/* bits in INT_M2 */
#घोषणा HFCPCI_PROC_TRANS	0x01
#घोषणा HFCPCI_GCI_I_CHG	0x02
#घोषणा HFCPCI_GCI_MON_REC	0x04
#घोषणा HFCPCI_IRQ_ENABLE	0x08
#घोषणा HFCPCI_PMESEL		0x80

/* bits in STATES */
#घोषणा HFCPCI_STATE_MSK	0x0F
#घोषणा HFCPCI_LOAD_STATE	0x10
#घोषणा HFCPCI_ACTIVATE		0x20
#घोषणा HFCPCI_DO_ACTION	0x40
#घोषणा HFCPCI_NT_G2_G3		0x80

/* bits in HFCD_MST_MODE */
#घोषणा HFCPCI_MASTER		0x01
#घोषणा HFCPCI_SLAVE		0x00
#घोषणा HFCPCI_F0IO_POSITIV	0x02
#घोषणा HFCPCI_F0_NEGATIV	0x04
#घोषणा HFCPCI_F0_2C4		0x08
/* reमुख्यing bits are क्रम codecs control */

/* bits in HFCD_SCTRL */
#घोषणा SCTRL_B1_ENA		0x01
#घोषणा SCTRL_B2_ENA		0x02
#घोषणा SCTRL_MODE_TE		0x00
#घोषणा SCTRL_MODE_NT		0x04
#घोषणा SCTRL_LOW_PRIO		0x08
#घोषणा SCTRL_SQ_ENA		0x10
#घोषणा SCTRL_TEST		0x20
#घोषणा SCTRL_NONE_CAP		0x40
#घोषणा SCTRL_PWR_DOWN		0x80

/* bits in SCTRL_E  */
#घोषणा HFCPCI_AUTO_AWAKE	0x01
#घोषणा HFCPCI_DBIT_1		0x04
#घोषणा HFCPCI_IGNORE_COL	0x08
#घोषणा HFCPCI_CHG_B1_B2	0x80

/* bits in FIFO_EN रेजिस्टर */
#घोषणा HFCPCI_FIFOEN_B1	0x03
#घोषणा HFCPCI_FIFOEN_B2	0x0C
#घोषणा HFCPCI_FIFOEN_DTX	0x10
#घोषणा HFCPCI_FIFOEN_B1TX	0x01
#घोषणा HFCPCI_FIFOEN_B1RX	0x02
#घोषणा HFCPCI_FIFOEN_B2TX	0x04
#घोषणा HFCPCI_FIFOEN_B2RX	0x08


/* definitions of fअगरo memory area */
#घोषणा MAX_D_FRAMES 15
#घोषणा MAX_B_FRAMES 31
#घोषणा B_SUB_VAL    0x200
#घोषणा B_FIFO_SIZE  (0x2000 - B_SUB_VAL)
#घोषणा D_FIFO_SIZE  512
#घोषणा D_FREG_MASK  0xF

काष्ठा zt अणु
	__le16 z1;  /* Z1 poपूर्णांकer 16 Bit */
	__le16 z2;  /* Z2 poपूर्णांकer 16 Bit */
पूर्ण;

काष्ठा dfअगरo अणु
	u_अक्षर data[D_FIFO_SIZE]; /* FIFO data space */
	u_अक्षर fill1[0x20A0 - D_FIFO_SIZE]; /* reserved, करो not use */
	u_अक्षर f1, f2; /* f poपूर्णांकers */
	u_अक्षर fill2[0x20C0 - 0x20A2]; /* reserved, करो not use */
	/* mask index with D_FREG_MASK क्रम access */
	काष्ठा zt za[MAX_D_FRAMES + 1];
	u_अक्षर fill3[0x4000 - 0x2100]; /* align 16K */
पूर्ण;

काष्ठा bzfअगरo अणु
	काष्ठा zt	za[MAX_B_FRAMES + 1]; /* only range 0x0..0x1F allowed */
	u_अक्षर		f1, f2; /* f poपूर्णांकers */
	u_अक्षर		fill[0x2100 - 0x2082]; /* alignment */
पूर्ण;


जोड़ fअगरo_area अणु
	काष्ठा अणु
		काष्ठा dfअगरo d_tx; /* D-send channel */
		काष्ठा dfअगरo d_rx; /* D-receive channel */
	पूर्ण d_chan;
	काष्ठा अणु
		u_अक्षर		fill1[0x200];
		u_अक्षर		txdat_b1[B_FIFO_SIZE];
		काष्ठा bzfअगरo	txbz_b1;
		काष्ठा bzfअगरo	txbz_b2;
		u_अक्षर		txdat_b2[B_FIFO_SIZE];
		u_अक्षर		fill2[D_FIFO_SIZE];
		u_अक्षर		rxdat_b1[B_FIFO_SIZE];
		काष्ठा bzfअगरo	rxbz_b1;
		काष्ठा bzfअगरo	rxbz_b2;
		u_अक्षर rxdat_b2[B_FIFO_SIZE];
	पूर्ण b_chans;
	u_अक्षर fill[32768];
पूर्ण;

#घोषणा Write_hfc(a, b, c) (ग_लिखोb(c, (a->hw.pci_io) + b))
#घोषणा Read_hfc(a, b) (पढ़ोb((a->hw.pci_io) + b))
