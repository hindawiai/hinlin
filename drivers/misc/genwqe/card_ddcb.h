<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __CARD_DDCB_H__
#घोषणा __CARD_DDCB_H__

/**
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "genwqe_driver.h"
#समावेश "card_base.h"

/**
 * काष्ठा ddcb - Device Driver Control Block DDCB
 * @hsi:        Hardware software पूर्णांकerlock
 * @shi:        Software hardware पूर्णांकerlock. Hsi and shi are used to पूर्णांकerlock
 *              software and hardware activities. We are using a compare and
 *              swap operation to ensure that there are no races when
 *              activating new DDCBs on the queue, or when we need to
 *              purge a DDCB from a running queue.
 * @acfunc:     Accelerator function addresses a unit within the chip
 * @cmd:        Command to work on
 * @cmकरोpts_16: Options क्रम the command
 * @asiv:       Input data
 * @asv:        Output data
 *
 * The DDCB data क्रमmat is big endian. Multiple consequtive DDBCs क्रमm
 * a DDCB queue.
 */
#घोषणा ASIV_LENGTH		104 /* Old specअगरication without ATS field */
#घोषणा ASIV_LENGTH_ATS		96  /* New specअगरication with ATS field */
#घोषणा ASV_LENGTH		64

काष्ठा ddcb अणु
	जोड़ अणु
		__be32 icrc_hsi_shi_32;	/* iCRC, Hardware/SW पूर्णांकerlock */
		काष्ठा अणु
			__be16	icrc_16;
			u8	hsi;
			u8	shi;
		पूर्ण;
	पूर्ण;
	u8  pre;		/* Preamble */
	u8  xdir;		/* Execution Directives */
	__be16 seqnum_16;	/* Sequence Number */

	u8  acfunc;		/* Accelerator Function.. */
	u8  cmd;		/* Command. */
	__be16 cmकरोpts_16;	/* Command Options */
	u8  sur;		/* Status Update Rate */
	u8  psp;		/* Protection Section Poपूर्णांकer */
	__be16 rsvd_0e_16;	/* Reserved invariant */

	__be64 fwiv_64;		/* Firmware Invariant. */

	जोड़ अणु
		काष्ठा अणु
			__be64 ats_64;  /* Address Translation Spec */
			u8     asiv[ASIV_LENGTH_ATS]; /* New ASIV */
		पूर्ण n;
		u8  __asiv[ASIV_LENGTH];	/* obsolete */
	पूर्ण;
	u8     asv[ASV_LENGTH];	/* Appl Spec Variant */

	__be16 rsvd_c0_16;	/* Reserved Variant */
	__be16 vcrc_16;		/* Variant CRC */
	__be32 rsvd_32;		/* Reserved unरक्षित */

	__be64 deque_ts_64;	/* Deque Time Stamp. */

	__be16 retc_16;		/* Return Code */
	__be16 attn_16;		/* Attention/Extended Error Codes */
	__be32 progress_32;	/* Progress indicator. */

	__be64 cmplt_ts_64;	/* Completion Time Stamp. */

	/* The following layout matches the new service layer क्रमmat */
	__be32 ibdc_32;		/* Inbound Data Count  (* 256) */
	__be32 obdc_32;		/* Outbound Data Count (* 256) */

	__be64 rsvd_SLH_64;	/* Reserved क्रम hardware */
	जोड़ अणु			/* निजी data क्रम driver */
		u8	priv[8];
		__be64	priv_64;
	पूर्ण;
	__be64 disp_ts_64;	/* Dispatch TimeStamp */
पूर्ण __attribute__((__packed__));

/* CRC polynomials क्रम DDCB */
#घोषणा CRC16_POLYNOMIAL	0x1021

/*
 * SHI: Software to Hardware Interlock
 *   This 1 byte field is written by software to पूर्णांकerlock the
 *   movement of one queue entry to another with the hardware in the
 *   chip.
 */
#घोषणा DDCB_SHI_INTR		0x04 /* Bit 2 */
#घोषणा DDCB_SHI_PURGE		0x02 /* Bit 1 */
#घोषणा DDCB_SHI_NEXT		0x01 /* Bit 0 */

/*
 * HSI: Hardware to Software पूर्णांकerlock
 * This 1 byte field is written by hardware to पूर्णांकerlock the movement
 * of one queue entry to another with the software in the chip.
 */
#घोषणा DDCB_HSI_COMPLETED	0x40 /* Bit 6 */
#घोषणा DDCB_HSI_FETCHED	0x04 /* Bit 2 */

/*
 * Accessing HSI/SHI is करोne 32-bit wide
 *   Normally 16-bit access would work too, but on some platक्रमms the
 *   16 compare and swap operation is not supported. Thereक्रमe
 *   चयनing to 32-bit such that those platक्रमms will work too.
 *
 *                                         iCRC HSI/SHI
 */
#घोषणा DDCB_INTR_BE32		cpu_to_be32(0x00000004)
#घोषणा DDCB_PURGE_BE32		cpu_to_be32(0x00000002)
#घोषणा DDCB_NEXT_BE32		cpu_to_be32(0x00000001)
#घोषणा DDCB_COMPLETED_BE32	cpu_to_be32(0x00004000)
#घोषणा DDCB_FETCHED_BE32	cpu_to_be32(0x00000400)

/* Definitions of DDCB presets */
#घोषणा DDCB_PRESET_PRE		0x80
#घोषणा ICRC_LENGTH(n)		((n) + 8 + 8 + 8)  /* used ASIV + hdr fields */
#घोषणा VCRC_LENGTH(n)		((n))		   /* used ASV */

/*
 * Genwqe Scatter Gather list
 *   Each element has up to 8 entries.
 *   The chaining element is element 0 cause of prefetching needs.
 */

/*
 * 0b0110 Chained descriptor. The descriptor is describing the next
 * descriptor list.
 */
#घोषणा SG_CHAINED		(0x6)

/*
 * 0b0010 First entry of a descriptor list. Start from a Buffer-Empty
 * condition.
 */
#घोषणा SG_DATA			(0x2)

/*
 * 0b0000 Early terminator. This is the last entry on the list
 * irregardless of the length indicated.
 */
#घोषणा SG_END_LIST		(0x0)

/**
 * काष्ठा sglist - Scatter gather list
 * @target_addr:       Either a dma addr of memory to work on or a
 *                     dma addr or a subsequent sglist block.
 * @len:               Length of the data block.
 * @flags:             See above.
 *
 * Depending on the command the GenWQE card can use a scatter gather
 * list to describe the memory it works on. Always 8 sg_entry's क्रमm
 * a block.
 */
काष्ठा sg_entry अणु
	__be64 target_addr;
	__be32 len;
	__be32 flags;
पूर्ण;

#पूर्ण_अगर /* __CARD_DDCB_H__ */
