<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/kn05.h
 *
 *	DECstation/DECप्रणाली 5000/260 (4max+ or KN05), 5000/150 (4min
 *	or KN04-BA), Personal DECstation/DECप्रणाली 5000/50 (4maxine or
 *	KN04-CA) and DECप्रणाली 5900/260 (KN05) R4k CPU card MB ASIC
 *	definitions.
 *
 *	Copyright (C) 2002, 2003, 2005, 2008  Maciej W. Rozycki
 *
 *	WARNING!  All this inक्रमmation is pure guesswork based on the
 *	ROM.  It is provided here in hope it will give someone some
 *	food क्रम thought.  No करोcumentation क्रम the KN05 nor the KN04
 *	module has been located so far.
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN05_H
#घोषणा __ASM_MIPS_DEC_KN05_H

#समावेश <यंत्र/dec/ioasic_addrs.h>

/*
 * The oncard MB (Memory Buffer) ASIC provides an additional address
 * decoder.  Certain address ranges within the "high" 16 slots are
 * passed to the I/O ASIC's decoder like with the KN03 or KN02-BA/CA.
 * Others are handled locally.  "Low" slots are always passed.
 */
#घोषणा KN4K_SLOT_BASE	0x1fc00000

#घोषणा KN4K_MB_ROM	(0*IOASIC_SLOT_SIZE)	/* KN05/KN04 card ROM */
#घोषणा KN4K_IOCTL	(1*IOASIC_SLOT_SIZE)	/* I/O ASIC */
#घोषणा KN4K_ESAR	(2*IOASIC_SLOT_SIZE)	/* LANCE MAC address chip */
#घोषणा KN4K_LANCE	(3*IOASIC_SLOT_SIZE)	/* LANCE Ethernet */
#घोषणा KN4K_MB_INT	(4*IOASIC_SLOT_SIZE)	/* MB पूर्णांकerrupt रेजिस्टर */
#घोषणा KN4K_MB_EA	(5*IOASIC_SLOT_SIZE)	/* MB error address? */
#घोषणा KN4K_MB_EC	(6*IOASIC_SLOT_SIZE)	/* MB error ??? */
#घोषणा KN4K_MB_CSR	(7*IOASIC_SLOT_SIZE)	/* MB control & status */
#घोषणा KN4K_RES_08	(8*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_RES_09	(9*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_RES_10	(10*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_RES_11	(11*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_SCSI	(12*IOASIC_SLOT_SIZE)	/* ASC SCSI */
#घोषणा KN4K_RES_13	(13*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_RES_14	(14*IOASIC_SLOT_SIZE)	/* unused? */
#घोषणा KN4K_RES_15	(15*IOASIC_SLOT_SIZE)	/* unused? */

/*
 * MB ASIC पूर्णांकerrupt bits.
 */
#घोषणा KN4K_MB_INR_MB		4	/* ??? */
#घोषणा KN4K_MB_INR_MT		3	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN4K_MB_INR_RES_2	2	/* unused */
#घोषणा KN4K_MB_INR_RTC		1	/* RTC */
#घोषणा KN4K_MB_INR_TC		0	/* I/O ASIC cascade */

/*
 * Bits क्रम the MB पूर्णांकerrupt रेजिस्टर.
 * The रेजिस्टर appears पढ़ो-only.
 */
#घोषणा KN4K_MB_INT_IRQ		(0x1f<<0)	/* CPU Int[4:0] status. */
#घोषणा KN4K_MB_INT_IRQ_N(n)	(1<<(n))	/* Inभागidual status bits. */

/*
 * Bits क्रम the MB control & status रेजिस्टर.
 * Set to 0x00bf8001 क्रम KN05 and to 0x003f8000 क्रम KN04 by the firmware.
 */
#घोषणा KN4K_MB_CSR_PF		(1<<0)		/* PreFetching enable? */
#घोषणा KN4K_MB_CSR_F		(1<<1)		/* ??? */
#घोषणा KN4K_MB_CSR_ECC		(0xff<<2)	/* ??? */
#घोषणा KN4K_MB_CSR_OD		(1<<10)		/* ??? */
#घोषणा KN4K_MB_CSR_CP		(1<<11)		/* ??? */
#घोषणा KN4K_MB_CSR_UNC		(1<<12)		/* ??? */
#घोषणा KN4K_MB_CSR_IM		(1<<13)		/* ??? */
#घोषणा KN4K_MB_CSR_NC		(1<<14)		/* ??? */
#घोषणा KN4K_MB_CSR_EE		(1<<15)		/* (bus) Exception Enable? */
#घोषणा KN4K_MB_CSR_MSK		(0x1f<<16)	/* CPU Int[4:0] mask */
#घोषणा KN4K_MB_CSR_MSK_N(n)	(1<<((n)+16))	/* Inभागidual mask bits. */
#घोषणा KN4K_MB_CSR_FW		(1<<21)		/* ??? */
#घोषणा KN4K_MB_CSR_W		(1<<31)		/* ??? */

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN05_H */
