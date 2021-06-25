<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mesh.h: definitions क्रम the driver क्रम the MESH SCSI bus adaptor
 * (Macपूर्णांकosh Enhanced SCSI Hardware) found on Power Macपूर्णांकosh computers.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */
#अगर_अघोषित _MESH_H
#घोषणा _MESH_H

/*
 * Registers in the MESH controller.
 */

काष्ठा mesh_regs अणु
	अचिन्हित अक्षर	count_lo;
	अक्षर pad0[15];
	अचिन्हित अक्षर	count_hi;
	अक्षर pad1[15];
	अचिन्हित अक्षर	fअगरo;
	अक्षर pad2[15];
	अचिन्हित अक्षर	sequence;
	अक्षर pad3[15];
	अचिन्हित अक्षर	bus_status0;
	अक्षर pad4[15];
	अचिन्हित अक्षर	bus_status1;
	अक्षर pad5[15];
	अचिन्हित अक्षर	fअगरo_count;
	अक्षर pad6[15];
	अचिन्हित अक्षर	exception;
	अक्षर pad7[15];
	अचिन्हित अक्षर	error;
	अक्षर pad8[15];
	अचिन्हित अक्षर	पूर्णांकr_mask;
	अक्षर pad9[15];
	अचिन्हित अक्षर	पूर्णांकerrupt;
	अक्षर pad10[15];
	अचिन्हित अक्षर	source_id;
	अक्षर pad11[15];
	अचिन्हित अक्षर	dest_id;
	अक्षर pad12[15];
	अचिन्हित अक्षर	sync_params;
	अक्षर pad13[15];
	अचिन्हित अक्षर	mesh_id;
	अक्षर pad14[15];
	अचिन्हित अक्षर	sel_समयout;
	अक्षर pad15[15];
पूर्ण;

/* Bits in the sequence रेजिस्टर. */
#घोषणा SEQ_DMA_MODE	0x80	/* use DMA क्रम data transfer */
#घोषणा SEQ_TARGET	0x40	/* put the controller पूर्णांकo target mode */
#घोषणा SEQ_ATN		0x20	/* निश्चित ATN संकेत */
#घोषणा SEQ_ACTIVE_NEG	0x10	/* use active negation on REQ/ACK */
#घोषणा SEQ_CMD		0x0f	/* command bits: */
#घोषणा SEQ_ARBITRATE	1	/*  get the bus */
#घोषणा SEQ_SELECT	2	/*  select a target */
#घोषणा SEQ_COMMAND	3	/*  send a command */
#घोषणा SEQ_STATUS	4	/*  receive status */
#घोषणा SEQ_DATAOUT	5	/*  send data */
#घोषणा SEQ_DATAIN	6	/*  receive data */
#घोषणा SEQ_MSGOUT	7	/*  send a message */
#घोषणा SEQ_MSGIN	8	/*  receive a message */
#घोषणा SEQ_BUSFREE	9	/*  look क्रम bus मुक्त */
#घोषणा SEQ_ENBPARITY	0x0a	/*  enable parity checking */
#घोषणा SEQ_DISPARITY	0x0b	/*  disable parity checking */
#घोषणा SEQ_ENBRESEL	0x0c	/*  enable reselection */
#घोषणा SEQ_DISRESEL	0x0d	/*  disable reselection */
#घोषणा SEQ_RESETMESH	0x0e	/*  reset the controller */
#घोषणा SEQ_FLUSHFIFO	0x0f	/*  clear out the FIFO */

/* Bits in the bus_status0 and bus_status1 रेजिस्टरs:
   these correspond directly to the SCSI bus control संकेतs. */
#घोषणा BS0_REQ		0x20
#घोषणा BS0_ACK		0x10
#घोषणा BS0_ATN		0x08
#घोषणा BS0_MSG		0x04
#घोषणा BS0_CD		0x02
#घोषणा BS0_IO		0x01
#घोषणा BS1_RST		0x80
#घोषणा BS1_BSY		0x40
#घोषणा BS1_SEL		0x20

/* Bus phases defined by the bits in bus_status0 */
#घोषणा BS0_PHASE	(BS0_MSG+BS0_CD+BS0_IO)
#घोषणा BP_DATAOUT	0
#घोषणा BP_DATAIN	BS0_IO
#घोषणा BP_COMMAND	BS0_CD
#घोषणा BP_STATUS	(BS0_CD+BS0_IO)
#घोषणा BP_MSGOUT	(BS0_MSG+BS0_CD)
#घोषणा BP_MSGIN	(BS0_MSG+BS0_CD+BS0_IO)

/* Bits in the exception रेजिस्टर. */
#घोषणा EXC_SELWATN	0x20	/* (as target) we were selected with ATN */
#घोषणा EXC_SELECTED	0x10	/* (as target) we were selected w/o ATN */
#घोषणा EXC_RESELECTED	0x08	/* (as initiator) we were reselected */
#घोषणा EXC_ARBLOST	0x04	/* we lost arbitration */
#घोषणा EXC_PHASEMM	0x02	/* SCSI phase mismatch */
#घोषणा EXC_SELTO	0x01	/* selection समयout */

/* Bits in the error रेजिस्टर */
#घोषणा ERR_UNEXPDISC	0x40	/* target unexpectedly disconnected */
#घोषणा ERR_SCSIRESET	0x20	/* SCSI bus got reset on us */
#घोषणा ERR_SEQERR	0x10	/* we did something the chip didn't like */
#घोषणा ERR_PARITY	0x01	/* parity error was detected */

/* Bits in the पूर्णांकerrupt and पूर्णांकr_mask रेजिस्टरs */
#घोषणा INT_ERROR	0x04	/* error पूर्णांकerrupt */
#घोषणा INT_EXCEPTION	0x02	/* exception पूर्णांकerrupt */
#घोषणा INT_CMDDONE	0x01	/* command करोne पूर्णांकerrupt */

/* Fields in the sync_params रेजिस्टर */
#घोषणा SYNC_OFF(x)	((x) >> 4)	/* offset field */
#घोषणा SYNC_PER(x)	((x) & 0xf)	/* period field */
#घोषणा SYNC_PARAMS(o, p)	(((o) << 4) | (p))
#घोषणा ASYNC_PARAMS	2	/* sync_params value क्रम async xfers */

/*
 * Assuming a घड़ी frequency of 50MHz:
 *
 * The transfer period with SYNC_PER(sync_params) == x
 * is (x + 2) * 40ns, except that x == 0 gives 100ns.
 *
 * The units of the sel_समयout रेजिस्टर are 10ms.
 */


#पूर्ण_अगर /* _MESH_H */
