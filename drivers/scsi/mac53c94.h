<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mac53c94.h: definitions क्रम the driver क्रम the 53c94 SCSI bus adaptor
 * found on Power Macपूर्णांकosh computers, controlling the बाह्यal SCSI chain.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */
#अगर_अघोषित _MAC53C94_H
#घोषणा _MAC53C94_H

/*
 * Registers in the 53C94 controller.
 */

काष्ठा mac53c94_regs अणु
	अचिन्हित अक्षर	count_lo;
	अक्षर pad0[15];
	अचिन्हित अक्षर	count_mid;
	अक्षर pad1[15];
	अचिन्हित अक्षर	fअगरo;
	अक्षर pad2[15];
	अचिन्हित अक्षर	command;
	अक्षर pad3[15];
	अचिन्हित अक्षर	status;
	अक्षर pad4[15];
	अचिन्हित अक्षर	पूर्णांकerrupt;
	अक्षर pad5[15];
	अचिन्हित अक्षर	seqstep;
	अक्षर pad6[15];
	अचिन्हित अक्षर	flags;
	अक्षर pad7[15];
	अचिन्हित अक्षर	config1;
	अक्षर pad8[15];
	अचिन्हित अक्षर	clk_factor;
	अक्षर pad9[15];
	अचिन्हित अक्षर	test;
	अक्षर pad10[15];
	अचिन्हित अक्षर	config2;
	अक्षर pad11[15];
	अचिन्हित अक्षर	config3;
	अक्षर pad12[15];
	अचिन्हित अक्षर	config4;
	अक्षर pad13[15];
	अचिन्हित अक्षर	count_hi;
	अक्षर pad14[15];
	अचिन्हित अक्षर	fअगरo_res;
	अक्षर pad15[15];
पूर्ण;

/*
 * Alternate functions क्रम some रेजिस्टरs.
 */
#घोषणा dest_id		status
#घोषणा sel_समयout	पूर्णांकerrupt
#घोषणा sync_period	seqstep
#घोषणा sync_offset	flags

/*
 * Bits in command रेजिस्टर.
 */
#घोषणा CMD_DMA_MODE	0x80
#घोषणा CMD_MODE_MASK	0x70
#घोषणा CMD_MODE_INIT	0x10
#घोषणा CMD_MODE_TARG	0x20
#घोषणा CMD_MODE_DISC	0x40

#घोषणा CMD_NOP		0
#घोषणा CMD_FLUSH	1
#घोषणा CMD_RESET	2
#घोषणा CMD_SCSI_RESET	3

#घोषणा CMD_XFER_DATA	0x10
#घोषणा CMD_I_COMPLETE	0x11
#घोषणा CMD_ACCEPT_MSG	0x12
#घोषणा CMD_XFER_PAD	0x18
#घोषणा CMD_SET_ATN	0x1a
#घोषणा CMD_CLR_ATN	0x1b

#घोषणा CMD_SEND_MSG	0x20
#घोषणा CMD_SEND_STATUS	0x21
#घोषणा CMD_SEND_DATA	0x22
#घोषणा CMD_DISC_SEQ	0x23
#घोषणा CMD_TERMINATE	0x24
#घोषणा CMD_T_COMPLETE	0x25
#घोषणा CMD_DISCONNECT	0x27
#घोषणा CMD_RECV_MSG	0x28
#घोषणा CMD_RECV_CDB	0x29
#घोषणा CMD_RECV_DATA	0x2a
#घोषणा CMD_RECV_CMD	0x2b
#घोषणा CMD_ABORT_DMA	0x04

#घोषणा CMD_RESELECT	0x40
#घोषणा CMD_SELECT	0x41
#घोषणा CMD_SELECT_ATN	0x42
#घोषणा CMD_SELATN_STOP	0x43
#घोषणा CMD_ENABLE_SEL	0x44
#घोषणा CMD_DISABLE_SEL	0x45
#घोषणा CMD_SEL_ATN3	0x46
#घोषणा CMD_RESEL_ATN3	0x47

/*
 * Bits in status रेजिस्टर.
 */
#घोषणा STAT_IRQ	0x80
#घोषणा STAT_ERROR	0x40
#घोषणा STAT_PARITY	0x20
#घोषणा STAT_TC_ZERO	0x10
#घोषणा STAT_DONE	0x08
#घोषणा STAT_PHASE	0x07
#घोषणा STAT_MSG	0x04
#घोषणा STAT_CD		0x02
#घोषणा STAT_IO		0x01

/*
 * Bits in पूर्णांकerrupt रेजिस्टर.
 */
#घोषणा INTR_RESET	0x80	/* SCSI bus was reset */
#घोषणा INTR_ILL_CMD	0x40	/* illegal command */
#घोषणा INTR_DISCONNECT	0x20	/* we got disconnected */
#घोषणा INTR_BUS_SERV	0x10	/* bus service requested */
#घोषणा INTR_DONE	0x08	/* function completed */
#घोषणा INTR_RESELECTED	0x04	/* we were reselected */
#घोषणा INTR_SEL_ATN	0x02	/* we were selected, ATN निश्चितed */
#घोषणा INTR_SELECT	0x01	/* we were selected, ATN negated */

/*
 * Encoding क्रम the select समयout.
 */
#घोषणा TIMO_VAL(x)	((x) * 5000 / 7682)

/*
 * Bits in sequence step रेजिस्टर.
 */
#घोषणा SS_MASK		7
#घोषणा SS_ARB_SEL	0	/* Selection & arbitration complete */
#घोषणा SS_MSG_SENT	1	/* One message byte sent */
#घोषणा SS_NOT_CMD	2	/* Not in command phase */
#घोषणा SS_PHASE_CHG	3	/* Early phase change, cmd bytes lost */
#घोषणा SS_DONE		4	/* Command was sent OK */

/*
 * Encoding क्रम sync transfer period.
 */
#घोषणा SYNCP_MASK	0x1f
#घोषणा SYNCP_MIN	4
#घोषणा SYNCP_MAX	31

/*
 * Bits in flags रेजिस्टर.
 */
#घोषणा FLAGS_FIFO_LEV	0x1f
#घोषणा FLAGS_SEQ_STEP	0xe0

/*
 * Encoding क्रम sync offset.
 */
#घोषणा SYNCO_MASK	0x0f
#घोषणा SYNCO_ASS_CTRL	0x30	/* REQ/ACK निश्चितion control */
#घोषणा SYNCO_NEG_CTRL	0xc0	/* REQ/ACK negation control */

/*
 * Bits in config1 रेजिस्टर.
 */
#घोषणा CF1_SLOW_CABLE	0x80	/* Slow cable mode */
#घोषणा CF1_NO_RES_REP	0x40	/* Disable SCSI reset reports */
#घोषणा CF1_PAR_TEST	0x20	/* Parity test mode enable */
#घोषणा CF1_PAR_ENABLE	0x10	/* Enable parity checks */
#घोषणा CF1_TEST	0x08	/* Chip tests */
#घोषणा CF1_MY_ID	0x07	/* Controller's address on bus */

/*
 * Encoding क्रम clk_factor रेजिस्टर.
 */
#घोषणा CLKF_MASK	7
#घोषणा CLKF_VAL(freq)	((((freq) + 4999999) / 5000000) & CLKF_MASK)

/*
 * Bits in test mode रेजिस्टर.
 */
#घोषणा TEST_TARGET	1	/* target test mode */
#घोषणा TEST_INITIATOR	2	/* initiator test mode */
#घोषणा TEST_TRISTATE	4	/* tristate (hi-z) test mode */

/*
 * Bits in config2 रेजिस्टर.
 */
#घोषणा CF2_RFB		0x80
#घोषणा CF2_FEATURE_EN	0x40	/* enable features / phase latch */
#घोषणा CF2_BYTECTRL	0x20
#घोषणा CF2_DREQ_HIZ	0x10
#घोषणा CF2_SCSI2	0x08
#घोषणा CF2_PAR_ABORT	0x04	/* bad parity target पात */
#घोषणा CF2_REG_PARERR	0x02	/* रेजिस्टर parity error */
#घोषणा CF2_DMA_PARERR	0x01	/* DMA parity error */

/*
 * Bits in the config3 रेजिस्टर.
 */
#घोषणा CF3_ID_MSG_CHK	0x80
#घोषणा CF3_3B_MSGS	0x40
#घोषणा CF3_CDB10	0x20
#घोषणा CF3_FASTSCSI	0x10	/* enable fast SCSI support */
#घोषणा CF3_FASTCLOCK	0x08
#घोषणा CF3_SAVERESID	0x04
#घोषणा CF3_ALT_DMA	0x02
#घोषणा CF3_THRESH_8	0x01

/*
 * Bits in the config4 रेजिस्टर.
 */
#घोषणा CF4_EAN		0x04
#घोषणा CF4_TEST	0x02
#घोषणा CF4_BBTE	0x01

#पूर्ण_अगर /* _MAC53C94_H */
