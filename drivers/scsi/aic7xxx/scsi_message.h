<शैली गुरु>
/*
 * This file is in the खुला करोमुख्य.
 * $FreeBSD: src/sys/cam/scsi/scsi_message.h,v 1.2 2000/05/01 20:21:29 peter Exp $
 */

/* Messages (1 byte) */		     /* I/T (M)andatory or (O)ptional */
#घोषणा MSG_SAVEDATAPOINTER	0x02 /* O/O */
#घोषणा MSG_RESTOREPOINTERS	0x03 /* O/O */
#घोषणा MSG_DISCONNECT		0x04 /* O/O */
#घोषणा MSG_MESSAGE_REJECT	0x07 /* M/M */
#घोषणा MSG_NOOP		0x08 /* M/M */

/* Messages (2 byte) */
#घोषणा MSG_SIMPLE_Q_TAG	0x20 /* O/O */
#घोषणा MSG_IGN_WIDE_RESIDUE	0x23 /* O/O */

/* Identअगरy message */		     /* M/M */	
#घोषणा MSG_IDENTIFYFLAG	0x80 
#घोषणा MSG_IDENTIFY_DISCFLAG	0x40 
#घोषणा MSG_IDENTIFY(lun, disc)	(((disc) ? 0xc0 : MSG_IDENTIFYFLAG) | (lun))
#घोषणा MSG_ISIDENTIFY(m)	((m) & MSG_IDENTIFYFLAG)
#घोषणा MSG_IDENTIFY_LUNMASK	0x3F 

/* Extended messages (opcode and length) */
#घोषणा MSG_EXT_SDTR_LEN	0x03

#घोषणा MSG_EXT_WDTR_LEN	0x02
#घोषणा MSG_EXT_WDTR_BUS_8_BIT	0x00
#घोषणा MSG_EXT_WDTR_BUS_16_BIT	0x01
#घोषणा MSG_EXT_WDTR_BUS_32_BIT	0x02 /* Deprecated in SPI3 */

#घोषणा MSG_EXT_PPR_LEN		0x06
#घोषणा	MSG_EXT_PPR_PCOMP_EN	0x80
#घोषणा	MSG_EXT_PPR_RTI		0x40
#घोषणा	MSG_EXT_PPR_RD_STRM	0x20
#घोषणा	MSG_EXT_PPR_WR_FLOW	0x10
#घोषणा	MSG_EXT_PPR_HOLD_MCS	0x08
#घोषणा	MSG_EXT_PPR_QAS_REQ	0x04
#घोषणा	MSG_EXT_PPR_DT_REQ	0x02
#घोषणा MSG_EXT_PPR_IU_REQ	0x01
