<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AHA1542_H_
#घोषणा _AHA1542_H_

#समावेश <linux/types.h>

/* I/O Port पूर्णांकerface 4.2 */
/* READ */
#घोषणा STATUS(base) base
#घोषणा STST	BIT(7)		/* Self Test in Progress */
#घोषणा DIAGF	BIT(6)		/* Internal Diagnostic Failure */
#घोषणा INIT	BIT(5)		/* Mailbox Initialization Required */
#घोषणा IDLE	BIT(4)		/* SCSI Host Adapter Idle */
#घोषणा CDF	BIT(3)		/* Command/Data Out Port Full */
#घोषणा DF	BIT(2)		/* Data In Port Full */
/* BIT(1) is reserved */
#घोषणा INVDCMD	BIT(0)		/* Invalid H A Command */
#घोषणा STATMASK (STST | DIAGF | INIT | IDLE | CDF | DF | INVDCMD)

#घोषणा INTRFLAGS(base) (STATUS(base)+2)
#घोषणा ANYINTR	BIT(7)		/* Any Interrupt */
#घोषणा SCRD	BIT(3)		/* SCSI Reset Detected */
#घोषणा HACC	BIT(2)		/* HA Command Complete */
#घोषणा MBOA	BIT(1)		/* MBO Empty */
#घोषणा MBIF	BIT(0)		/* MBI Full */
#घोषणा INTRMASK (ANYINTR | SCRD | HACC | MBOA | MBIF)

/* WRITE */
#घोषणा CONTROL(base) STATUS(base)
#घोषणा HRST	BIT(7)		/* Hard Reset */
#घोषणा SRST	BIT(6)		/* Soft Reset */
#घोषणा IRST	BIT(5)		/* Interrupt Reset */
#घोषणा SCRST	BIT(4)		/* SCSI Bus Reset */

/* READ/WRITE */
#घोषणा DATA(base) (STATUS(base)+1)
#घोषणा CMD_NOP		0x00	/* No Operation */
#घोषणा CMD_MBINIT	0x01	/* Mailbox Initialization */
#घोषणा CMD_START_SCSI	0x02	/* Start SCSI Command */
#घोषणा CMD_INQUIRY	0x04	/* Adapter Inquiry */
#घोषणा CMD_EMBOI	0x05	/* Enable MailBox Out Interrupt */
#घोषणा CMD_BUSON_TIME	0x07	/* Set Bus-On Time */
#घोषणा CMD_BUSOFF_TIME	0x08	/* Set Bus-Off Time */
#घोषणा CMD_DMASPEED	0x09	/* Set AT Bus Transfer Speed */
#घोषणा CMD_RETDEVS	0x0a	/* Return Installed Devices */
#घोषणा CMD_RETCONF	0x0b	/* Return Configuration Data */
#घोषणा CMD_RETSETUP	0x0d	/* Return Setup Data */
#घोषणा CMD_ECHO	0x1f	/* ECHO Command Data */

#घोषणा CMD_EXTBIOS     0x28    /* Return extend bios inक्रमmation only 1542C */
#घोषणा CMD_MBENABLE    0x29    /* Set Mailbox Interface enable only 1542C */

/* Mailbox Definition 5.2.1 and 5.2.2 */
काष्ठा mailbox अणु
	u8 status;	/* Command/Status */
	u8 ccbptr[3];	/* msb, .., lsb */
पूर्ण;

/* This is used with scatter-gather */
काष्ठा chain अणु
	u8 datalen[3];	/* Size of this part of chain */
	u8 dataptr[3];	/* Location of data */
पूर्ण;

/* These beदीर्घ in scsi.h also */
अटल अंतरभूत व्योम any2scsi(u8 *p, u32 v)
अणु
	p[0] = v >> 16;
	p[1] = v >> 8;
	p[2] = v;
पूर्ण

#घोषणा scsi2पूर्णांक(up) ( (((दीर्घ)*(up)) << 16) + (((दीर्घ)(up)[1]) << 8) + ((दीर्घ)(up)[2]) )

#घोषणा xscsi2पूर्णांक(up) ( (((दीर्घ)(up)[0]) << 24) + (((दीर्घ)(up)[1]) << 16) \
		      + (((दीर्घ)(up)[2]) <<  8) +  ((दीर्घ)(up)[3]) )

#घोषणा MAX_CDB 12
#घोषणा MAX_SENSE 14

/* Command Control Block (CCB), 5.3 */
काष्ठा ccb अणु
	u8 op;		/* Command Control Block Operation Code: */
			/* 0x00: SCSI Initiator CCB, 0x01: SCSI Target CCB, */
			/* 0x02: SCSI Initiator CCB with Scatter/Gather, */
			/* 0x81: SCSI Bus Device Reset CCB */
	u8 idlun;	/* Address and Direction Control: */
			/* Bits 7-5: op=0, 2: Target ID, op=1: Initiator ID */
			/* Bit	4: Outbound data transfer, length is checked */
			/* Bit	3:  Inbound data transfer, length is checked */
			/* Bits 2-0: Logical Unit Number */
	u8 cdblen;	/* SCSI Command Length */
	u8 rsalen;	/* Request Sense Allocation Length/Disable Auto Sense */
	u8 datalen[3];	/* Data Length  (MSB, ..., LSB) */
	u8 dataptr[3];	/* Data Poपूर्णांकer (MSB, ..., LSB) */
	u8 linkptr[3];	/* Link Poपूर्णांकer (MSB, ..., LSB) */
	u8 commlinkid;	/* Command Linking Identअगरier */
	u8 hastat;	/* Host  Adapter Status (HASTAT) */
	u8 tarstat;	/* Target Device Status (TARSTAT) */
	u8 reserved[2];
	u8 cdb[MAX_CDB + MAX_SENSE];	/* SCSI Command Descriptor Block */
					/* followed by the Auto Sense data */
पूर्ण;

#घोषणा AHA1542_REGION_SIZE 4
#घोषणा AHA1542_MAILBOXES 8

#पूर्ण_अगर /* _AHA1542_H_ */
