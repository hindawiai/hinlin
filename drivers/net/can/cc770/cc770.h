<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Core driver क्रम the CC770 and AN82527 CAN controllers
 *
 * Copyright (C) 2009, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#अगर_अघोषित CC770_DEV_H
#घोषणा CC770_DEV_H

#समावेश <linux/can/dev.h>

काष्ठा cc770_msgobj अणु
	u8 ctrl0;
	u8 ctrl1;
	u8 id[4];
	u8 config;
	u8 data[8];
	u8 करोntuse;		/* padding */
पूर्ण __packed;

काष्ठा cc770_regs अणु
	जोड़ अणु
		काष्ठा cc770_msgobj msgobj[16]; /* Message object 1..15 */
		काष्ठा अणु
			u8 control;		/* Control Register */
			u8 status;		/* Status Register */
			u8 cpu_पूर्णांकerface;	/* CPU Interface Register */
			u8 करोntuse1;
			u8 high_speed_पढ़ो[2];	/* High Speed Read */
			u8 global_mask_std[2];	/* Standard Global Mask */
			u8 global_mask_ext[4];	/* Extended Global Mask */
			u8 msg15_mask[4];	/* Message 15 Mask */
			u8 करोntuse2[15];
			u8 clkout;		/* Clock Out Register */
			u8 करोntuse3[15];
			u8 bus_config;		/* Bus Configuration Register */
			u8 करोntuse4[15];
			u8 bit_timing_0;	/* Bit Timing Register byte 0 */
			u8 करोntuse5[15];
			u8 bit_timing_1;	/* Bit Timing Register byte 1 */
			u8 करोntuse6[15];
			u8 पूर्णांकerrupt;		/* Interrupt Register */
			u8 करोntuse7[15];
			u8 rx_error_counter;	/* Receive Error Counter */
			u8 करोntuse8[15];
			u8 tx_error_counter;	/* Transmit Error Counter */
			u8 करोntuse9[31];
			u8 p1_conf;
			u8 करोntuse10[15];
			u8 p2_conf;
			u8 करोntuse11[15];
			u8 p1_in;
			u8 करोntuse12[15];
			u8 p2_in;
			u8 करोntuse13[15];
			u8 p1_out;
			u8 करोntuse14[15];
			u8 p2_out;
			u8 करोntuse15[15];
			u8 serial_reset_addr;
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

/* Control Register (0x00) */
#घोषणा CTRL_INI	0x01	/* Initialization */
#घोषणा CTRL_IE		0x02	/* Interrupt Enable */
#घोषणा CTRL_SIE	0x04	/* Status Interrupt Enable */
#घोषणा CTRL_EIE	0x08	/* Error Interrupt Enable */
#घोषणा CTRL_EAF	0x20	/* Enable additional functions */
#घोषणा CTRL_CCE	0x40	/* Change Configuration Enable */

/* Status Register (0x01) */
#घोषणा STAT_LEC_STUFF	0x01	/* Stuff error */
#घोषणा STAT_LEC_FORM	0x02	/* Form error */
#घोषणा STAT_LEC_ACK	0x03	/* Acknowledgement error */
#घोषणा STAT_LEC_BIT1	0x04	/* Bit1 error */
#घोषणा STAT_LEC_BIT0	0x05	/* Bit0 error */
#घोषणा STAT_LEC_CRC	0x06	/* CRC error */
#घोषणा STAT_LEC_MASK	0x07	/* Last Error Code mask */
#घोषणा STAT_TXOK	0x08	/* Transmit Message Successfully */
#घोषणा STAT_RXOK	0x10	/* Receive Message Successfully */
#घोषणा STAT_WAKE	0x20	/* Wake Up Status */
#घोषणा STAT_WARN	0x40	/* Warning Status */
#घोषणा STAT_BOFF	0x80	/* Bus Off Status */

/*
 * CPU Interface Register (0x02)
 * Clock Out Register (0x1f)
 * Bus Configuration Register (0x2f)
 *
 * see include/linux/can/platक्रमm/cc770.h
 */

/* Message Control Register 0 (Base Address + 0x0) */
#घोषणा INTPND_RES	0x01	/* No Interrupt pending */
#घोषणा INTPND_SET	0x02	/* Interrupt pending */
#घोषणा INTPND_UNC	0x03
#घोषणा RXIE_RES	0x04	/* Receive Interrupt Disable */
#घोषणा RXIE_SET	0x08	/* Receive Interrupt Enable */
#घोषणा RXIE_UNC	0x0c
#घोषणा TXIE_RES	0x10	/* Transmit Interrupt Disable */
#घोषणा TXIE_SET	0x20	/* Transmit Interrupt Enable */
#घोषणा TXIE_UNC	0x30
#घोषणा MSGVAL_RES	0x40	/* Message Invalid */
#घोषणा MSGVAL_SET	0x80	/* Message Valid */
#घोषणा MSGVAL_UNC	0xc0

/* Message Control Register 1 (Base Address + 0x01) */
#घोषणा NEWDAT_RES	0x01	/* No New Data */
#घोषणा NEWDAT_SET	0x02	/* New Data */
#घोषणा NEWDAT_UNC	0x03
#घोषणा MSGLST_RES	0x04	/* No Message Lost */
#घोषणा MSGLST_SET	0x08	/* Message Lost */
#घोषणा MSGLST_UNC	0x0c
#घोषणा CPUUPD_RES	0x04	/* No CPU Updating */
#घोषणा CPUUPD_SET	0x08	/* CPU Updating */
#घोषणा CPUUPD_UNC	0x0c
#घोषणा TXRQST_RES	0x10	/* No Transmission Request */
#घोषणा TXRQST_SET	0x20	/* Transmission Request */
#घोषणा TXRQST_UNC	0x30
#घोषणा RMTPND_RES	0x40	/* No Remote Request Pending */
#घोषणा RMTPND_SET	0x80	/* Remote Request Pending */
#घोषणा RMTPND_UNC	0xc0

/* Message Configuration Register (Base Address + 0x06) */
#घोषणा MSGCFG_XTD	0x04	/* Extended Identअगरier */
#घोषणा MSGCFG_सूची	0x08	/* Direction is Transmit */

#घोषणा MSGOBJ_FIRST	1
#घोषणा MSGOBJ_LAST	15

#घोषणा CC770_IO_SIZE	0x100
#घोषणा CC770_MAX_IRQ	20	/* max. number of पूर्णांकerrupts handled in ISR */
#घोषणा CC770_MAX_MSG	4	/* max. number of messages handled in ISR */

#घोषणा CC770_ECHO_SKB_MAX	1

#घोषणा cc770_पढ़ो_reg(priv, member)					\
	priv->पढ़ो_reg(priv, दुरत्व(काष्ठा cc770_regs, member))

#घोषणा cc770_ग_लिखो_reg(priv, member, value)				\
	priv->ग_लिखो_reg(priv, दुरत्व(काष्ठा cc770_regs, member), value)

/*
 * Message objects and flags used by this driver
 */
#घोषणा CC770_OBJ_FLAG_RX	0x01
#घोषणा CC770_OBJ_FLAG_RTR	0x02
#घोषणा CC770_OBJ_FLAG_EFF	0x04

क्रमागत अणु
	CC770_OBJ_RX0 = 0,	/* क्रम receiving normal messages */
	CC770_OBJ_RX1,		/* क्रम receiving normal messages */
	CC770_OBJ_RX_RTR0,	/* क्रम receiving remote transmission requests */
	CC770_OBJ_RX_RTR1,	/* क्रम receiving remote transmission requests */
	CC770_OBJ_TX,		/* क्रम sending messages */
	CC770_OBJ_MAX
पूर्ण;

#घोषणा obj2msgobj(o)	(MSGOBJ_LAST - (o)) /* message object 11..15 */

/*
 * CC770 निजी data काष्ठाure
 */
काष्ठा cc770_priv अणु
	काष्ठा can_priv can;	/* must be the first member */
	काष्ठा sk_buff *echo_skb;

	/* the lower-layer is responsible क्रम appropriate locking */
	u8 (*पढ़ो_reg)(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg);
	व्योम (*ग_लिखो_reg)(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg, u8 val);
	व्योम (*pre_irq)(स्थिर काष्ठा cc770_priv *priv);
	व्योम (*post_irq)(स्थिर काष्ठा cc770_priv *priv);

	व्योम *priv;		/* क्रम board-specअगरic data */
	काष्ठा net_device *dev;

	व्योम __iomem *reg_base;	 /* ioremap'ed address to रेजिस्टरs */
	अचिन्हित दीर्घ irq_flags; /* क्रम request_irq() */

	अचिन्हित अक्षर obj_flags[CC770_OBJ_MAX];
	u8 control_normal_mode;	/* Control रेजिस्टर क्रम normal mode */
	u8 cpu_पूर्णांकerface;	/* CPU पूर्णांकerface रेजिस्टर */
	u8 clkout;		/* Clock out रेजिस्टर */
	u8 bus_config;		/* Bus configuration रेजिस्टर */

	काष्ठा sk_buff *tx_skb;
पूर्ण;

काष्ठा net_device *alloc_cc770dev(पूर्णांक माप_priv);
व्योम मुक्त_cc770dev(काष्ठा net_device *dev);
पूर्णांक रेजिस्टर_cc770dev(काष्ठा net_device *dev);
व्योम unरेजिस्टर_cc770dev(काष्ठा net_device *dev);

#पूर्ण_अगर /* CC770_DEV_H */
