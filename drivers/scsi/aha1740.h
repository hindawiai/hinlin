<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AHA1740_H

/* $Id$
 *
 * Header file क्रम the adaptec 1740 driver क्रम Linux
 *
 * With minor revisions 3/31/93
 * Written and (C) 1992,1993 Brad McLean.  See aha1740.c
 * क्रम more info
 *
 */

#समावेश <linux/types.h>

#घोषणा SLOTSIZE	0x5c

/* EISA configuration रेजिस्टरs & values */
#घोषणा	HID0(base)	(base + 0x0)
#घोषणा	HID1(base)	(base + 0x1)
#घोषणा HID2(base)	(base + 0x2)
#घोषणा	HID3(base)	(base + 0x3)
#घोषणा	EBCNTRL(base)	(base + 0x4)
#घोषणा	PORTADR(base)	(base + 0x40)
#घोषणा BIOSADR(base)	(base + 0x41)
#घोषणा INTDEF(base)	(base + 0x42)
#घोषणा SCSIDEF(base)	(base + 0x43)
#घोषणा BUSDEF(base)	(base + 0x44)
#घोषणा	RESV0(base)	(base + 0x45)
#घोषणा RESV1(base)	(base + 0x46)
#घोषणा	RESV2(base)	(base + 0x47)

#घोषणा	HID_MFG	"ADP"
#घोषणा	HID_PRD 0
#घोषणा HID_REV 2
#घोषणा EBCNTRL_VALUE 1
#घोषणा PORTADDR_ENH 0x80
/* READ */
#घोषणा	G2INTST(base)	(base + 0x56)
#घोषणा G2STAT(base)	(base + 0x57)
#घोषणा	MBOXIN0(base)	(base + 0x58)
#घोषणा	MBOXIN1(base)	(base + 0x59)
#घोषणा	MBOXIN2(base)	(base + 0x5a)
#घोषणा	MBOXIN3(base)	(base + 0x5b)
#घोषणा G2STAT2(base)	(base + 0x5c)

#घोषणा G2INTST_MASK		0xf0	/* isolate the status */
#घोषणा	G2INTST_CCBGOOD		0x10	/* CCB Completed */
#घोषणा	G2INTST_CCBRETRY	0x50	/* CCB Completed with a retry */
#घोषणा	G2INTST_HARDFAIL	0x70	/* Adapter Hardware Failure */
#घोषणा	G2INTST_CMDGOOD		0xa0	/* Immediate command success */
#घोषणा G2INTST_CCBERROR	0xc0	/* CCB Completed with error */
#घोषणा	G2INTST_ASNEVENT	0xd0	/* Asynchronous Event Notअगरication */
#घोषणा	G2INTST_CMDERROR	0xe0	/* Immediate command error */

#घोषणा G2STAT_MBXOUT	4	/* Mailbox Out Empty Bit */
#घोषणा	G2STAT_INTPEND	2	/* Interrupt Pending Bit */
#घोषणा	G2STAT_BUSY	1	/* Busy Bit (attention pending) */

#घोषणा G2STAT2_READY	0	/* Host Ready Bit */

/* WRITE (and ReadBack) */
#घोषणा	MBOXOUT0(base)	(base + 0x50)
#घोषणा	MBOXOUT1(base)	(base + 0x51)
#घोषणा	MBOXOUT2(base)	(base + 0x52)
#घोषणा	MBOXOUT3(base)	(base + 0x53)
#घोषणा	ATTN(base)	(base + 0x54)
#घोषणा G2CNTRL(base)	(base + 0x55)

#घोषणा	ATTN_IMMED	0x10	/* Immediate Command */
#घोषणा	ATTN_START	0x40	/* Start CCB */
#घोषणा	ATTN_ABORT	0x50	/* Abort CCB */

#घोषणा G2CNTRL_HRST	0x80	/* Hard Reset */
#घोषणा G2CNTRL_IRST	0x40	/* Clear EISA Interrupt */
#घोषणा G2CNTRL_HRDY	0x20	/* Sets HOST पढ़ोy */

/* This is used with scatter-gather */
काष्ठा aha1740_chain अणु
	u32 dataptr;		/* Location of data */
	u32 datalen;		/* Size of this part of chain */
पूर्ण;

/* These beदीर्घ in scsi.h */
#घोषणा any2scsi(up, p)				\
(up)[0] = (((अचिन्हित दीर्घ)(p)) >> 16)  ;	\
(up)[1] = (((अचिन्हित दीर्घ)(p)) >> 8);		\
(up)[2] = ((अचिन्हित दीर्घ)(p));

#घोषणा scsi2पूर्णांक(up) ( (((दीर्घ)*(up)) << 16) + (((दीर्घ)(up)[1]) << 8) + ((दीर्घ)(up)[2]) )

#घोषणा xany2scsi(up, p)	\
(up)[0] = ((दीर्घ)(p)) >> 24;	\
(up)[1] = ((दीर्घ)(p)) >> 16;	\
(up)[2] = ((दीर्घ)(p)) >> 8;	\
(up)[3] = ((दीर्घ)(p));

#घोषणा xscsi2पूर्णांक(up) ( (((दीर्घ)(up)[0]) << 24) + (((दीर्घ)(up)[1]) << 16) \
		      + (((दीर्घ)(up)[2]) <<  8) +  ((दीर्घ)(up)[3]) )

#घोषणा MAX_CDB 12
#घोषणा MAX_SENSE 14
#घोषणा MAX_STATUS 32

काष्ठा ecb अणु			/* Enhanced Control Block 6.1 */
	u16 cmdw;		/* Command Word */
	/* Flag Word 1 */
	u16 cne:1,		/* Control Block Chaining */
	:6, di:1,		/* Disable Interrupt */
	:2, ses:1,		/* Suppress Underrun error */
	:1, sg:1,		/* Scatter/Gather */
	:1, dsb:1,		/* Disable Status Block */
	 ars:1;			/* Automatic Request Sense */
	/* Flag Word 2 */
	u16 lun:3,		/* Logical Unit */
	 tag:1,			/* Tagged Queuing */
	 tt:2,			/* Tag Type */
	 nd:1,			/* No Disconnect */
	:1, dat:1,		/* Data transfer - check direction */
	 dir:1,			/* Direction of transfer 1 = datain */
	 st:1,			/* Suppress Transfer */
	 chk:1,			/* Calculate Checksum */
	:2, rec:1,:1;		/* Error Recovery */
	u16 nil0;		/* nothing */
	u32 dataptr;		/* Data or Scatter List ptr */
	u32 datalen;		/* Data or Scatter List len */
	u32 statusptr;		/* Status Block ptr */
	u32 linkptr;		/* Chain Address */
	u32 nil1;		/* nothing */
	u32 senseptr;		/* Sense Info Poपूर्णांकer */
	u8 senselen;		/* Sense Length */
	u8 cdblen;		/* CDB Length */
	u16 datacheck;		/* Data checksum */
	u8 cdb[MAX_CDB];	/* CDB area */
/* Hardware defined portion ends here, rest is driver defined */
	u8 sense[MAX_SENSE];	/* Sense area */
	u8 status[MAX_STATUS];	/* Status area */
	काष्ठा scsi_cmnd *SCpnt;	/* Link to the SCSI Command Block */
	व्योम (*करोne) (काष्ठा scsi_cmnd *);	/* Completion Function */
पूर्ण;

#घोषणा	AHA1740CMD_NOP	 0x00	/* No OP */
#घोषणा AHA1740CMD_INIT	 0x01	/* Initiator SCSI Command */
#घोषणा AHA1740CMD_DIAG	 0x05	/* Run Diagnostic Command */
#घोषणा AHA1740CMD_SCSI	 0x06	/* Initialize SCSI */
#घोषणा AHA1740CMD_SENSE 0x08	/* Read Sense Inक्रमmation */
#घोषणा AHA1740CMD_DOWN  0x09	/* Download Firmware (yeah, I bet!) */
#घोषणा AHA1740CMD_RINQ  0x0a	/* Read Host Adapter Inquiry Data */
#घोषणा AHA1740CMD_TARG  0x10	/* Target SCSI Command */

#घोषणा AHA1740_ECBS 32
#घोषणा AHA1740_SCATTER 16

#पूर्ण_अगर
