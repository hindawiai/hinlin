<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
**  Device driver क्रम the PCI-SCSI NCR538XX controller family.
**
**  Copyright (C) 1994  Wolfgang Stanglmeier
**  Copyright (C) 1998-2001  Gerard Roudier <groudier@मुक्त.fr>
**
**
**-----------------------------------------------------------------------------
**
**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver
**  and is currently मुख्यtained by
**
**          Gerard Roudier              <groudier@मुक्त.fr>
**
**  Being given that this driver originates from the FreeBSD version, and
**  in order to keep synergy on both, any suggested enhancements and corrections
**  received on Linux are स्वतःmatically a potential candidate क्रम the FreeBSD 
**  version.
**
**  The original driver has been written क्रम 386bsd and FreeBSD by
**          Wolfgang Stanglmeier        <wolf@cologne.de>
**          Stefan Esser                <se@mi.Uni-Koeln.de>
**
**  And has been ported to NetBSD by
**          Charles M. Hannum           <mycroft@gnu.ai.mit.edu>
**
**  NVRAM detection and पढ़ोing.
**    Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
**
**  Added support क्रम MIPS big endian प्रणालीs.
**    Carsten Langgaard, carstenl@mips.com
**    Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
**
**  Added support क्रम HP PARISC big endian प्रणालीs.
**    Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
**
*******************************************************************************
*/

#अगर_अघोषित NCR53C8XX_H
#घोषणा NCR53C8XX_H

#समावेश <scsi/scsi_host.h>


/*
**	If you want a driver as small as possible, करोnnot define the 
**	following options.
*/
#घोषणा SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
#घोषणा SCSI_NCR_DEBUG_INFO_SUPPORT

/*
**	To disable पूर्णांकegrity checking, करो not define the 
**	following option.
*/
#अगर_घोषित	CONFIG_SCSI_NCR53C8XX_INTEGRITY_CHECK
#	define SCSI_NCR_ENABLE_INTEGRITY_CHECK
#पूर्ण_अगर

/* ---------------------------------------------------------------------
** Take पूर्णांकo account kernel configured parameters.
** Most of these options can be overridden at startup by a command line.
** ---------------------------------------------------------------------
*/

/*
 * For Ultra2 and Ultra3 SCSI support option, use special features. 
 *
 * Value (शेष) means:
 *	bit 0 : all features enabled, except:
 *		bit 1 : PCI Write And Invalidate.
 *		bit 2 : Data Phase Mismatch handling from SCRIPTS.
 *
 * Use boot options ncr53c8xx=specf:1 अगर you want all chip features to be 
 * enabled by the driver.
 */
#घोषणा	SCSI_NCR_SETUP_SPECIAL_FEATURES		(3)

#घोषणा SCSI_NCR_MAX_SYNC			(80)

/*
 * Allow tags from 2 to 256, शेष 8
 */
#अगर_घोषित	CONFIG_SCSI_NCR53C8XX_MAX_TAGS
#अगर	CONFIG_SCSI_NCR53C8XX_MAX_TAGS < 2
#घोषणा SCSI_NCR_MAX_TAGS	(2)
#या_अगर	CONFIG_SCSI_NCR53C8XX_MAX_TAGS > 256
#घोषणा SCSI_NCR_MAX_TAGS	(256)
#अन्यथा
#घोषणा	SCSI_NCR_MAX_TAGS	CONFIG_SCSI_NCR53C8XX_MAX_TAGS
#पूर्ण_अगर
#अन्यथा
#घोषणा SCSI_NCR_MAX_TAGS	(8)
#पूर्ण_अगर

/*
 * Allow tagged command queuing support अगर configured with शेष number 
 * of tags set to max (see above).
 */
#अगर_घोषित	CONFIG_SCSI_NCR53C8XX_DEFAULT_TAGS
#घोषणा	SCSI_NCR_SETUP_DEFAULT_TAGS	CONFIG_SCSI_NCR53C8XX_DEFAULT_TAGS
#या_अगर	defined CONFIG_SCSI_NCR53C8XX_TAGGED_QUEUE
#घोषणा	SCSI_NCR_SETUP_DEFAULT_TAGS	SCSI_NCR_MAX_TAGS
#अन्यथा
#घोषणा	SCSI_NCR_SETUP_DEFAULT_TAGS	(0)
#पूर्ण_अगर

/*
 * Immediate arbitration
 */
#अगर defined(CONFIG_SCSI_NCR53C8XX_IARB)
#घोषणा SCSI_NCR_IARB_SUPPORT
#पूर्ण_अगर

/*
 * Sync transfer frequency at startup.
 * Allow from 5Mhz to 80Mhz शेष 20 Mhz.
 */
#अगर_अघोषित	CONFIG_SCSI_NCR53C8XX_SYNC
#घोषणा	CONFIG_SCSI_NCR53C8XX_SYNC	(20)
#या_अगर	CONFIG_SCSI_NCR53C8XX_SYNC > SCSI_NCR_MAX_SYNC
#अघोषित	CONFIG_SCSI_NCR53C8XX_SYNC
#घोषणा	CONFIG_SCSI_NCR53C8XX_SYNC	SCSI_NCR_MAX_SYNC
#पूर्ण_अगर

#अगर	CONFIG_SCSI_NCR53C8XX_SYNC == 0
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC	(255)
#या_अगर	CONFIG_SCSI_NCR53C8XX_SYNC <= 5
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC	(50)
#या_अगर	CONFIG_SCSI_NCR53C8XX_SYNC <= 20
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC	(250/(CONFIG_SCSI_NCR53C8XX_SYNC))
#या_अगर	CONFIG_SCSI_NCR53C8XX_SYNC <= 33
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC	(11)
#या_अगर	CONFIG_SCSI_NCR53C8XX_SYNC <= 40
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC	(10)
#अन्यथा
#घोषणा	SCSI_NCR_SETUP_DEFAULT_SYNC 	(9)
#पूर्ण_अगर

/*
 * Disallow disconnections at boot-up
 */
#अगर_घोषित CONFIG_SCSI_NCR53C8XX_NO_DISCONNECT
#घोषणा SCSI_NCR_SETUP_DISCONNECTION	(0)
#अन्यथा
#घोषणा SCSI_NCR_SETUP_DISCONNECTION	(1)
#पूर्ण_अगर

/*
 * Force synchronous negotiation क्रम all tarमाला_लो
 */
#अगर_घोषित CONFIG_SCSI_NCR53C8XX_FORCE_SYNC_NEGO
#घोषणा SCSI_NCR_SETUP_FORCE_SYNC_NEGO	(1)
#अन्यथा
#घोषणा SCSI_NCR_SETUP_FORCE_SYNC_NEGO	(0)
#पूर्ण_अगर

/*
 * Disable master parity checking (flawed hardwares need that)
 */
#अगर_घोषित CONFIG_SCSI_NCR53C8XX_DISABLE_MPARITY_CHECK
#घोषणा SCSI_NCR_SETUP_MASTER_PARITY	(0)
#अन्यथा
#घोषणा SCSI_NCR_SETUP_MASTER_PARITY	(1)
#पूर्ण_अगर

/*
 * Disable scsi parity checking (flawed devices may need that)
 */
#अगर_घोषित CONFIG_SCSI_NCR53C8XX_DISABLE_PARITY_CHECK
#घोषणा SCSI_NCR_SETUP_SCSI_PARITY	(0)
#अन्यथा
#घोषणा SCSI_NCR_SETUP_SCSI_PARITY	(1)
#पूर्ण_अगर

/*
 * Settle समय after reset at boot-up
 */
#घोषणा SCSI_NCR_SETUP_SETTLE_TIME	(2)

/*
**	Bridge quirks work-around option शेषed to 1.
*/
#अगर_अघोषित	SCSI_NCR_PCIQ_WORK_AROUND_OPT
#घोषणा	SCSI_NCR_PCIQ_WORK_AROUND_OPT	1
#पूर्ण_अगर

/*
**	Work-around common bridge misbehaviour.
**
**	- Do not flush posted ग_लिखोs in the opposite 
**	  direction on पढ़ो.
**	- May reorder DMA ग_लिखोs to memory.
**
**	This option should not affect perक्रमmances 
**	signअगरicantly, so it is the शेष.
*/
#अगर	SCSI_NCR_PCIQ_WORK_AROUND_OPT == 1
#घोषणा	SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
#घोषणा	SCSI_NCR_PCIQ_MAY_REORDER_WRITES
#घोषणा	SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS

/*
**	Same as option 1, but also deal with 
**	misconfigured पूर्णांकerrupts.
**
**	- Edge triggered instead of level sensitive.
**	- No पूर्णांकerrupt line connected.
**	- IRQ number misconfigured.
**	
**	If no पूर्णांकerrupt is delivered, the driver will 
**	catch the पूर्णांकerrupt conditions 10 बार per 
**	second. No need to say that this option is 
**	not recommended.
*/
#या_अगर	SCSI_NCR_PCIQ_WORK_AROUND_OPT == 2
#घोषणा	SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
#घोषणा	SCSI_NCR_PCIQ_MAY_REORDER_WRITES
#घोषणा	SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS
#घोषणा	SCSI_NCR_PCIQ_BROKEN_INTR

/*
**	Some bridge designers decided to flush 
**	everything prior to deliver the पूर्णांकerrupt.
**	This option tries to deal with such a 
**	behaviour.
*/
#या_अगर	SCSI_NCR_PCIQ_WORK_AROUND_OPT == 3
#घोषणा	SCSI_NCR_PCIQ_SYNC_ON_INTR
#पूर्ण_अगर

/*
**	Other parameters not configurable with "make config"
**	Aव्योम to change these स्थिरants, unless you know what you are करोing.
*/

#घोषणा SCSI_NCR_ALWAYS_SIMPLE_TAG
#घोषणा SCSI_NCR_MAX_SCATTER	(127)
#घोषणा SCSI_NCR_MAX_TARGET	(16)

/*
**   Compute some desirable value क्रम CAN_QUEUE 
**   and CMD_PER_LUN.
**   The driver will use lower values अगर these 
**   ones appear to be too large.
*/
#घोषणा SCSI_NCR_CAN_QUEUE	(8*SCSI_NCR_MAX_TAGS + 2*SCSI_NCR_MAX_TARGET)
#घोषणा SCSI_NCR_CMD_PER_LUN	(SCSI_NCR_MAX_TAGS)

#घोषणा SCSI_NCR_SG_TABLESIZE	(SCSI_NCR_MAX_SCATTER)
#घोषणा SCSI_NCR_TIMER_INTERVAL	(HZ)

#घोषणा SCSI_NCR_MAX_LUN	(16)

/*
 *  IO functions definition क्रम big/little endian CPU support.
 *  For now, the NCR is only supported in little endian addressing mode, 
 */

#अगर_घोषित	__BIG_ENDIAN

#घोषणा	inw_l2b		inw
#घोषणा	inl_l2b		inl
#घोषणा	outw_b2l	outw
#घोषणा	outl_b2l	outl

#घोषणा	पढ़ोb_raw	पढ़ोb
#घोषणा	ग_लिखोb_raw	ग_लिखोb

#अगर defined(SCSI_NCR_BIG_ENDIAN)
#घोषणा	पढ़ोw_l2b	__raw_पढ़ोw
#घोषणा	पढ़ोl_l2b	__raw_पढ़ोl
#घोषणा	ग_लिखोw_b2l	__raw_ग_लिखोw
#घोषणा	ग_लिखोl_b2l	__raw_ग_लिखोl
#घोषणा	पढ़ोw_raw	__raw_पढ़ोw
#घोषणा	पढ़ोl_raw	__raw_पढ़ोl
#घोषणा	ग_लिखोw_raw	__raw_ग_लिखोw
#घोषणा	ग_लिखोl_raw	__raw_ग_लिखोl
#अन्यथा	/* Other big-endian */
#घोषणा	पढ़ोw_l2b	पढ़ोw
#घोषणा	पढ़ोl_l2b	पढ़ोl
#घोषणा	ग_लिखोw_b2l	ग_लिखोw
#घोषणा	ग_लिखोl_b2l	ग_लिखोl
#घोषणा	पढ़ोw_raw	पढ़ोw
#घोषणा	पढ़ोl_raw	पढ़ोl
#घोषणा	ग_लिखोw_raw	ग_लिखोw
#घोषणा	ग_लिखोl_raw	ग_लिखोl
#पूर्ण_अगर

#अन्यथा	/* little endian */

#घोषणा	inw_raw		inw
#घोषणा	inl_raw		inl
#घोषणा	outw_raw	outw
#घोषणा	outl_raw	outl

#घोषणा	पढ़ोb_raw	पढ़ोb
#घोषणा	पढ़ोw_raw	पढ़ोw
#घोषणा	पढ़ोl_raw	पढ़ोl
#घोषणा	ग_लिखोb_raw	ग_लिखोb
#घोषणा	ग_लिखोw_raw	ग_लिखोw
#घोषणा	ग_लिखोl_raw	ग_लिखोl

#पूर्ण_अगर

#अगर !defined(__hppa__) && !defined(__mips__)
#अगर_घोषित	SCSI_NCR_BIG_ENDIAN
#त्रुटि	"The NCR in BIG ENDIAN addressing mode is not (yet) supported"
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा MEMORY_BARRIER()	mb()


/*
 *  If the NCR uses big endian addressing mode over the 
 *  PCI, actual io रेजिस्टर addresses क्रम byte and word 
 *  accesses must be changed according to lane routing.
 *  Btw, ncr_offb() and ncr_offw() macros only apply to 
 *  स्थिरants and so करोnnot generate bloated code.
 */

#अगर	defined(SCSI_NCR_BIG_ENDIAN)

#घोषणा ncr_offb(o)	(((o)&~3)+((~((o)&3))&3))
#घोषणा ncr_offw(o)	(((o)&~3)+((~((o)&3))&2))

#अन्यथा

#घोषणा ncr_offb(o)	(o)
#घोषणा ncr_offw(o)	(o)

#पूर्ण_अगर

/*
 *  If the CPU and the NCR use same endian-ness addressing,
 *  no byte reordering is needed क्रम script patching.
 *  Macro cpu_to_scr() is to be used क्रम script patching.
 *  Macro scr_to_cpu() is to be used क्रम getting a DWORD 
 *  from the script.
 */

#अगर	defined(__BIG_ENDIAN) && !defined(SCSI_NCR_BIG_ENDIAN)

#घोषणा cpu_to_scr(dw)	cpu_to_le32(dw)
#घोषणा scr_to_cpu(dw)	le32_to_cpu(dw)

#या_अगर	defined(__LITTLE_ENDIAN) && defined(SCSI_NCR_BIG_ENDIAN)

#घोषणा cpu_to_scr(dw)	cpu_to_be32(dw)
#घोषणा scr_to_cpu(dw)	be32_to_cpu(dw)

#अन्यथा

#घोषणा cpu_to_scr(dw)	(dw)
#घोषणा scr_to_cpu(dw)	(dw)

#पूर्ण_अगर

/*
 *  Access to the controller chip.
 *
 *  If the CPU and the NCR use same endian-ness addressing,
 *  no byte reordering is needed क्रम accessing chip io 
 *  रेजिस्टरs. Functions suffixed by '_raw' are assumed 
 *  to access the chip over the PCI without करोing byte 
 *  reordering. Functions suffixed by '_l2b' are 
 *  assumed to perक्रमm little-endian to big-endian byte 
 *  reordering, those suffixed by '_b2l' blah, blah,
 *  blah, ...
 */

/*
 *  MEMORY mapped IO input / output
 */

#घोषणा INB_OFF(o)		पढ़ोb_raw((अक्षर __iomem *)np->reg + ncr_offb(o))
#घोषणा OUTB_OFF(o, val)	ग_लिखोb_raw((val), (अक्षर __iomem *)np->reg + ncr_offb(o))

#अगर	defined(__BIG_ENDIAN) && !defined(SCSI_NCR_BIG_ENDIAN)

#घोषणा INW_OFF(o)		पढ़ोw_l2b((अक्षर __iomem *)np->reg + ncr_offw(o))
#घोषणा INL_OFF(o)		पढ़ोl_l2b((अक्षर __iomem *)np->reg + (o))

#घोषणा OUTW_OFF(o, val)	ग_लिखोw_b2l((val), (अक्षर __iomem *)np->reg + ncr_offw(o))
#घोषणा OUTL_OFF(o, val)	ग_लिखोl_b2l((val), (अक्षर __iomem *)np->reg + (o))

#या_अगर	defined(__LITTLE_ENDIAN) && defined(SCSI_NCR_BIG_ENDIAN)

#घोषणा INW_OFF(o)		पढ़ोw_b2l((अक्षर __iomem *)np->reg + ncr_offw(o))
#घोषणा INL_OFF(o)		पढ़ोl_b2l((अक्षर __iomem *)np->reg + (o))

#घोषणा OUTW_OFF(o, val)	ग_लिखोw_l2b((val), (अक्षर __iomem *)np->reg + ncr_offw(o))
#घोषणा OUTL_OFF(o, val)	ग_लिखोl_l2b((val), (अक्षर __iomem *)np->reg + (o))

#अन्यथा

#अगर_घोषित CONFIG_SCSI_NCR53C8XX_NO_WORD_TRANSFERS
/* Only 8 or 32 bit transfers allowed */
#घोषणा INW_OFF(o)		(पढ़ोb((अक्षर __iomem *)np->reg + ncr_offw(o)) << 8 | पढ़ोb((अक्षर __iomem *)np->reg + ncr_offw(o) + 1))
#अन्यथा
#घोषणा INW_OFF(o)		पढ़ोw_raw((अक्षर __iomem *)np->reg + ncr_offw(o))
#पूर्ण_अगर
#घोषणा INL_OFF(o)		पढ़ोl_raw((अक्षर __iomem *)np->reg + (o))

#अगर_घोषित CONFIG_SCSI_NCR53C8XX_NO_WORD_TRANSFERS
/* Only 8 or 32 bit transfers allowed */
#घोषणा OUTW_OFF(o, val)	करो अणु ग_लिखोb((अक्षर)((val) >> 8), (अक्षर __iomem *)np->reg + ncr_offw(o)); ग_लिखोb((अक्षर)(val), (अक्षर __iomem *)np->reg + ncr_offw(o) + 1); पूर्ण जबतक (0)
#अन्यथा
#घोषणा OUTW_OFF(o, val)	ग_लिखोw_raw((val), (अक्षर __iomem *)np->reg + ncr_offw(o))
#पूर्ण_अगर
#घोषणा OUTL_OFF(o, val)	ग_लिखोl_raw((val), (अक्षर __iomem *)np->reg + (o))

#पूर्ण_अगर

#घोषणा INB(r)		INB_OFF (दुरत्व(काष्ठा ncr_reg,r))
#घोषणा INW(r)		INW_OFF (दुरत्व(काष्ठा ncr_reg,r))
#घोषणा INL(r)		INL_OFF (दुरत्व(काष्ठा ncr_reg,r))

#घोषणा OUTB(r, val)	OUTB_OFF (दुरत्व(काष्ठा ncr_reg,r), (val))
#घोषणा OUTW(r, val)	OUTW_OFF (दुरत्व(काष्ठा ncr_reg,r), (val))
#घोषणा OUTL(r, val)	OUTL_OFF (दुरत्व(काष्ठा ncr_reg,r), (val))

/*
 *  Set bit field ON, OFF 
 */

#घोषणा OUTONB(r, m)	OUTB(r, INB(r) | (m))
#घोषणा OUTOFFB(r, m)	OUTB(r, INB(r) & ~(m))
#घोषणा OUTONW(r, m)	OUTW(r, INW(r) | (m))
#घोषणा OUTOFFW(r, m)	OUTW(r, INW(r) & ~(m))
#घोषणा OUTONL(r, m)	OUTL(r, INL(r) | (m))
#घोषणा OUTOFFL(r, m)	OUTL(r, INL(r) & ~(m))

/*
 *  We normally want the chip to have a consistent view
 *  of driver पूर्णांकernal data काष्ठाures when we restart it.
 *  Thus these macros.
 */
#घोषणा OUTL_DSP(v)				\
	करो अणु					\
		MEMORY_BARRIER();		\
		OUTL (nc_dsp, (v));		\
	पूर्ण जबतक (0)

#घोषणा OUTONB_STD()				\
	करो अणु					\
		MEMORY_BARRIER();		\
		OUTONB (nc_dcntl, (STD|NOCOM));	\
	पूर्ण जबतक (0)


/*
**   NCR53C8XX devices features table.
*/
काष्ठा ncr_chip अणु
	अचिन्हित लघु	revision_id;
	अचिन्हित अक्षर	burst_max;	/* log-base-2 of max burst */
	अचिन्हित अक्षर	offset_max;
	अचिन्हित अक्षर	nr_भागisor;
	अचिन्हित पूर्णांक	features;
#घोषणा FE_LED0		(1<<0)
#घोषणा FE_WIDE		(1<<1)    /* Wide data transfers */
#घोषणा FE_ULTRA	(1<<2)	  /* Ultra speed 20Mtrans/sec */
#घोषणा FE_DBLR		(1<<4)	  /* Clock द्विगुनr present */
#घोषणा FE_QUAD		(1<<5)	  /* Clock quadrupler present */
#घोषणा FE_ERL		(1<<6)    /* Enable पढ़ो line */
#घोषणा FE_CLSE		(1<<7)    /* Cache line size enable */
#घोषणा FE_WRIE		(1<<8)    /* Write & Invalidate enable */
#घोषणा FE_ERMP		(1<<9)    /* Enable पढ़ो multiple */
#घोषणा FE_BOF		(1<<10)   /* Burst opcode fetch */
#घोषणा FE_DFS		(1<<11)   /* DMA fअगरo size */
#घोषणा FE_PFEN		(1<<12)   /* Prefetch enable */
#घोषणा FE_LDSTR	(1<<13)   /* Load/Store supported */
#घोषणा FE_RAM		(1<<14)   /* On chip RAM present */
#घोषणा FE_VARCLK	(1<<15)   /* SCSI घड़ी may vary */
#घोषणा FE_RAM8K	(1<<16)   /* On chip RAM sized 8Kb */
#घोषणा FE_64BIT	(1<<17)   /* Have a 64-bit PCI पूर्णांकerface */
#घोषणा FE_IO256	(1<<18)   /* Requires full 256 bytes in PCI space */
#घोषणा FE_NOPM		(1<<19)   /* Scripts handles phase mismatch */
#घोषणा FE_LEDC		(1<<20)   /* Hardware control of LED */
#घोषणा FE_DIFF		(1<<21)   /* Support Dअगरferential SCSI */
#घोषणा FE_66MHZ 	(1<<23)   /* 66MHz PCI Support */
#घोषणा FE_DAC	 	(1<<24)   /* Support DAC cycles (64 bit addressing) */
#घोषणा FE_ISTAT1 	(1<<25)   /* Have ISTAT1, MBOX0, MBOX1 रेजिस्टरs */
#घोषणा FE_DAC_IN_USE	(1<<26)	  /* Platक्रमm करोes DAC cycles */
#घोषणा FE_EHP		(1<<27)   /* 720: Even host parity */
#घोषणा FE_MUX		(1<<28)   /* 720: Multiplexed bus */
#घोषणा FE_EA		(1<<29)   /* 720: Enable Ack */

#घोषणा FE_CACHE_SET	(FE_ERL|FE_CLSE|FE_WRIE|FE_ERMP)
#घोषणा FE_SCSI_SET	(FE_WIDE|FE_ULTRA|FE_DBLR|FE_QUAD|F_CLK80)
#घोषणा FE_SPECIAL_SET	(FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM)
पूर्ण;


/*
**	Driver setup काष्ठाure.
**
**	This काष्ठाure is initialized from linux config options.
**	It can be overridden at boot-up by the boot command line.
*/
#घोषणा SCSI_NCR_MAX_EXCLUDES 8
काष्ठा ncr_driver_setup अणु
	u8	master_parity;
	u8	scsi_parity;
	u8	disconnection;
	u8	special_features;
	u8	क्रमce_sync_nego;
	u8	reverse_probe;
	u8	pci_fix_up;
	u8	use_nvram;
	u8	verbose;
	u8	शेष_tags;
	u16	शेष_sync;
	u16	debug;
	u8	burst_max;
	u8	led_pin;
	u8	max_wide;
	u8	settle_delay;
	u8	dअगरf_support;
	u8	irqm;
	u8	bus_check;
	u8	optimize;
	u8	recovery;
	u8	host_id;
	u16	iarb;
	u32	excludes[SCSI_NCR_MAX_EXCLUDES];
	अक्षर	tag_ctrl[100];
पूर्ण;

/*
**	Initial setup.
**	Can be overridden at startup by a command line.
*/
#घोषणा SCSI_NCR_DRIVER_SETUP			\
अणु						\
	SCSI_NCR_SETUP_MASTER_PARITY,		\
	SCSI_NCR_SETUP_SCSI_PARITY,		\
	SCSI_NCR_SETUP_DISCONNECTION,		\
	SCSI_NCR_SETUP_SPECIAL_FEATURES,	\
	SCSI_NCR_SETUP_FORCE_SYNC_NEGO,		\
	0,					\
	0,					\
	1,					\
	0,					\
	SCSI_NCR_SETUP_DEFAULT_TAGS,		\
	SCSI_NCR_SETUP_DEFAULT_SYNC,		\
	0x00,					\
	7,					\
	0,					\
	1,					\
	SCSI_NCR_SETUP_SETTLE_TIME,		\
	0,					\
	0,					\
	1,					\
	0,					\
	0,					\
	255,					\
	0x00					\
पूर्ण

/*
**	Boot fail safe setup.
**	Override initial setup from boot command line:
**	ncr53c8xx=safe:y
*/
#घोषणा SCSI_NCR_DRIVER_SAFE_SETUP		\
अणु						\
	0,					\
	1,					\
	0,					\
	0,					\
	0,					\
	0,					\
	0,					\
	1,					\
	2,					\
	0,					\
	255,					\
	0x00,					\
	255,					\
	0,					\
	0,					\
	10,					\
	1,					\
	1,					\
	1,					\
	0,					\
	0,					\
	255					\
पूर्ण

/**************** ORIGINAL CONTENT of ncrreg.h from FreeBSD ******************/

/*-----------------------------------------------------------------
**
**	The ncr 53c810 रेजिस्टर काष्ठाure.
**
**-----------------------------------------------------------------
*/

काष्ठा ncr_reg अणु
/*00*/  u8	nc_scntl0;    /* full arb., ena parity, par->ATN  */

/*01*/  u8	nc_scntl1;    /* no reset                         */
        #घोषणा   ISCON   0x10  /* connected to scsi		    */
        #घोषणा   CRST    0x08  /* क्रमce reset                      */
        #घोषणा   IARB    0x02  /* immediate arbitration            */

/*02*/  u8	nc_scntl2;    /* no disconnect expected           */
	#घोषणा   SDU     0x80  /* cmd: disconnect will उठाओ error */
	#घोषणा   CHM     0x40  /* sta: chained mode                */
	#घोषणा   WSS     0x08  /* sta: wide scsi send           [W]*/
	#घोषणा   WSR     0x01  /* sta: wide scsi received       [W]*/

/*03*/  u8	nc_scntl3;    /* cnf प्रणाली घड़ी dependent       */
	#घोषणा   EWS     0x08  /* cmd: enable wide scsi         [W]*/
	#घोषणा   ULTRA   0x80  /* cmd: ULTRA enable                */
				/* bits 0-2, 7 rsvd क्रम C1010       */

/*04*/  u8	nc_scid;	/* cnf host adapter scsi address    */
	#घोषणा   RRE     0x40  /* r/w:e enable response to resel.  */
	#घोषणा   SRE     0x20  /* r/w:e enable response to select  */

/*05*/  u8	nc_sxfer;	/* ### Sync speed and count         */
				/* bits 6-7 rsvd क्रम C1010          */

/*06*/  u8	nc_sdid;	/* ### Destination-ID               */

/*07*/  u8	nc_gpreg;	/* ??? IO-Pins                      */

/*08*/  u8	nc_sfbr;	/* ### First byte in phase          */

/*09*/  u8	nc_socl;
	#घोषणा   CREQ	  0x80	/* r/w: SCSI-REQ                    */
	#घोषणा   CACK	  0x40	/* r/w: SCSI-ACK                    */
	#घोषणा   CBSY	  0x20	/* r/w: SCSI-BSY                    */
	#घोषणा   CSEL	  0x10	/* r/w: SCSI-SEL                    */
	#घोषणा   CATN	  0x08	/* r/w: SCSI-ATN                    */
	#घोषणा   CMSG	  0x04	/* r/w: SCSI-MSG                    */
	#घोषणा   CC_D	  0x02	/* r/w: SCSI-C_D                    */
	#घोषणा   CI_O	  0x01	/* r/w: SCSI-I_O                    */

/*0a*/  u8	nc_ssid;

/*0b*/  u8	nc_sbcl;

/*0c*/  u8	nc_dstat;
        #घोषणा   DFE     0x80  /* sta: dma fअगरo empty              */
        #घोषणा   MDPE    0x40  /* पूर्णांक: master data parity error    */
        #घोषणा   BF      0x20  /* पूर्णांक: script: bus fault           */
        #घोषणा   ABRT    0x10  /* पूर्णांक: script: command पातed     */
        #घोषणा   SSI     0x08  /* पूर्णांक: script: single step         */
        #घोषणा   SIR     0x04  /* पूर्णांक: script: पूर्णांकerrupt inकाष्ठा. */
        #घोषणा   IID     0x01  /* पूर्णांक: script: illegal inकाष्ठा.   */

/*0d*/  u8	nc_sstat0;
        #घोषणा   ILF     0x80  /* sta: data in SIDL रेजिस्टर lsb   */
        #घोषणा   ORF     0x40  /* sta: data in SODR रेजिस्टर lsb   */
        #घोषणा   OLF     0x20  /* sta: data in SODL रेजिस्टर lsb   */
        #घोषणा   AIP     0x10  /* sta: arbitration in progress     */
        #घोषणा   LOA     0x08  /* sta: arbitration lost            */
        #घोषणा   WOA     0x04  /* sta: arbitration won             */
        #घोषणा   IRST    0x02  /* sta: scsi reset संकेत           */
        #घोषणा   SDP     0x01  /* sta: scsi parity संकेत          */

/*0e*/  u8	nc_sstat1;
	#घोषणा   FF3210  0xf0	/* sta: bytes in the scsi fअगरo      */

/*0f*/  u8	nc_sstat2;
        #घोषणा   ILF1    0x80  /* sta: data in SIDL रेजिस्टर msb[W]*/
        #घोषणा   ORF1    0x40  /* sta: data in SODR रेजिस्टर msb[W]*/
        #घोषणा   OLF1    0x20  /* sta: data in SODL रेजिस्टर msb[W]*/
        #घोषणा   DM      0x04  /* sta: DIFFSENS mismatch (895/6 only) */
        #घोषणा   LDSC    0x02  /* sta: disconnect & reconnect      */

/*10*/  u8	nc_dsa;	/* --> Base page                    */
/*11*/  u8	nc_dsa1;
/*12*/  u8	nc_dsa2;
/*13*/  u8	nc_dsa3;

/*14*/  u8	nc_istat;	/* --> Main Command and status      */
        #घोषणा   CABRT   0x80  /* cmd: पात current operation     */
        #घोषणा   SRST    0x40  /* mod: reset chip                  */
        #घोषणा   SIGP    0x20  /* r/w: message from host to ncr    */
        #घोषणा   SEM     0x10  /* r/w: message between host + ncr  */
        #घोषणा   CON     0x08  /* sta: connected to scsi           */
        #घोषणा   INTF    0x04  /* sta: पूर्णांक on the fly (reset by wr)*/
        #घोषणा   SIP     0x02  /* sta: scsi-पूर्णांकerrupt              */
        #घोषणा   DIP     0x01  /* sta: host/script पूर्णांकerrupt       */

/*15*/  u8	nc_istat1;	/* 896 and later cores only */
        #घोषणा   FLSH    0x04  /* sta: chip is flushing            */
        #घोषणा   SRUN    0x02  /* sta: scripts are running         */
        #घोषणा   SIRQD   0x01  /* r/w: disable INT pin             */

/*16*/  u8	nc_mbox0;	/* 896 and later cores only */
/*17*/  u8	nc_mbox1;	/* 896 and later cores only */

/*18*/	u8	nc_ctest0;
	#घोषणा   EHP     0x04	/* 720 even host parity             */
/*19*/  u8	nc_ctest1;

/*1a*/  u8	nc_ctest2;
	#घोषणा   CSIGP   0x40
				/* bits 0-2,7 rsvd क्रम C1010        */

/*1b*/  u8	nc_ctest3;
	#घोषणा   FLF     0x08  /* cmd: flush dma fअगरo              */
	#घोषणा   CLF	  0x04	/* cmd: clear dma fअगरo		    */
	#घोषणा   FM      0x02  /* mod: fetch pin mode              */
	#घोषणा   WRIE    0x01  /* mod: ग_लिखो and invalidate enable */
				/* bits 4-7 rsvd क्रम C1010          */

/*1c*/  u32    nc_temp;	/* ### Temporary stack              */

/*20*/	u8	nc_dfअगरo;
/*21*/  u8	nc_ctest4;
	#घोषणा   MUX     0x80  /* 720 host bus multiplex mode      */
	#घोषणा   BDIS    0x80  /* mod: burst disable               */
	#घोषणा   MPEE    0x08  /* mod: master parity error enable  */

/*22*/  u8	nc_ctest5;
	#घोषणा   DFS     0x20  /* mod: dma fअगरo size               */
				/* bits 0-1, 3-7 rsvd क्रम C1010          */
/*23*/  u8	nc_ctest6;

/*24*/  u32    nc_dbc;	/* ### Byte count and command       */
/*28*/  u32    nc_dnad;	/* ### Next command रेजिस्टर        */
/*2c*/  u32    nc_dsp;	/* --> Script Poपूर्णांकer               */
/*30*/  u32    nc_dsps;	/* --> Script poपूर्णांकer save/opcode#2 */

/*34*/  u8	nc_scratcha;  /* Temporary रेजिस्टर a            */
/*35*/  u8	nc_scratcha1;
/*36*/  u8	nc_scratcha2;
/*37*/  u8	nc_scratcha3;

/*38*/  u8	nc_dmode;
	#घोषणा   BL_2    0x80  /* mod: burst length shअगरt value +2 */
	#घोषणा   BL_1    0x40  /* mod: burst length shअगरt value +1 */
	#घोषणा   ERL     0x08  /* mod: enable पढ़ो line            */
	#घोषणा   ERMP    0x04  /* mod: enable पढ़ो multiple        */
	#घोषणा   BOF     0x02  /* mod: burst op code fetch         */

/*39*/  u8	nc_dien;
/*3a*/  u8	nc_sbr;

/*3b*/  u8	nc_dcntl;	/* --> Script execution control     */
	#घोषणा   CLSE    0x80  /* mod: cache line size enable      */
	#घोषणा   PFF     0x40  /* cmd: pre-fetch flush             */
	#घोषणा   PFEN    0x20  /* mod: pre-fetch enable            */
	#घोषणा   EA      0x20  /* mod: 720 enable-ack              */
	#घोषणा   SSM     0x10  /* mod: single step mode            */
	#घोषणा   IRQM    0x08  /* mod: irq mode (1 = totem pole !) */
	#घोषणा   STD     0x04  /* cmd: start dma mode              */
	#घोषणा   IRQD    0x02  /* mod: irq disable                 */
 	#घोषणा	  NOCOM   0x01	/* cmd: protect sfbr जबतक reselect */
				/* bits 0-1 rsvd क्रम C1010          */

/*3c*/  u32	nc_adder;

/*40*/  u16	nc_sien;	/* -->: पूर्णांकerrupt enable            */
/*42*/  u16	nc_sist;	/* <--: पूर्णांकerrupt status            */
        #घोषणा   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 only) */
        #घोषणा   STO     0x0400/* sta: समयout (select)            */
        #घोषणा   GEN     0x0200/* sta: समयout (general)           */
        #घोषणा   HTH     0x0100/* sta: समयout (handshake)         */
        #घोषणा   MA      0x80  /* sta: phase mismatch              */
        #घोषणा   CMP     0x40  /* sta: arbitration complete        */
        #घोषणा   SEL     0x20  /* sta: selected by another device  */
        #घोषणा   RSL     0x10  /* sta: reselected by another device*/
        #घोषणा   SGE     0x08  /* sta: gross error (over/underflow)*/
        #घोषणा   UDC     0x04  /* sta: unexpected disconnect       */
        #घोषणा   RST     0x02  /* sta: scsi bus reset detected     */
        #घोषणा   PAR     0x01  /* sta: scsi parity error           */

/*44*/  u8	nc_slpar;
/*45*/  u8	nc_swide;
/*46*/  u8	nc_macntl;
/*47*/  u8	nc_gpcntl;
/*48*/  u8	nc_sसमय0;    /* cmd: समयout क्रम select&handshake*/
/*49*/  u8	nc_sसमय1;    /* cmd: समयout user defined        */
/*4a*/  u16   nc_respid;    /* sta: Reselect-IDs                */

/*4c*/  u8	nc_stest0;

/*4d*/  u8	nc_stest1;
	#घोषणा   SCLK    0x80	/* Use the PCI घड़ी as SCSI घड़ी	*/
	#घोषणा   DBLEN   0x08	/* घड़ी द्विगुनr running		*/
	#घोषणा   DBLSEL  0x04	/* घड़ी द्विगुनr selected		*/
  

/*4e*/  u8	nc_stest2;
	#घोषणा   ROF     0x40	/* reset scsi offset (after gross error!) */
	#घोषणा   DIF     0x20  /* 720 SCSI dअगरferential mode             */
	#घोषणा   EXT     0x02  /* extended filtering                     */

/*4f*/  u8	nc_stest3;
	#घोषणा   TE     0x80	/* c: tolerAnt enable */
	#घोषणा   HSC    0x20	/* c: Halt SCSI Clock */
	#घोषणा   CSF    0x02	/* c: clear scsi fअगरo */

/*50*/  u16   nc_sidl;	/* Lowlevel: latched from scsi data */
/*52*/  u8	nc_stest4;
	#घोषणा   SMODE  0xc0	/* SCSI bus mode      (895/6 only) */
	#घोषणा    SMODE_HVD 0x40	/* High Voltage Dअगरferential       */
	#घोषणा    SMODE_SE  0x80	/* Single Ended                    */
	#घोषणा    SMODE_LVD 0xc0	/* Low Voltage Dअगरferential        */
	#घोषणा   LCKFRQ 0x20	/* Frequency Lock (895/6 only)     */
				/* bits 0-5 rsvd क्रम C1010          */

/*53*/  u8	nc_53_;
/*54*/  u16	nc_sodl;	/* Lowlevel: data out to scsi data  */
/*56*/	u8	nc_ccntl0;	/* Chip Control 0 (896)             */
	#घोषणा   ENPMJ  0x80	/* Enable Phase Mismatch Jump       */
	#घोषणा   PMJCTL 0x40	/* Phase Mismatch Jump Control      */
	#घोषणा   ENNDJ  0x20	/* Enable Non Data PM Jump          */
	#घोषणा   DISFC  0x10	/* Disable Auto FIFO Clear          */
	#घोषणा   DILS   0x02	/* Disable Internal Load/Store      */
	#घोषणा   DPR    0x01	/* Disable Pipe Req                 */

/*57*/	u8	nc_ccntl1;	/* Chip Control 1 (896)             */
	#घोषणा   ZMOD   0x80	/* High Impedance Mode              */
	#घोषणा	  DIC	 0x10	/* Disable Internal Cycles	    */
	#घोषणा   DDAC   0x08	/* Disable Dual Address Cycle       */
	#घोषणा   XTIMOD 0x04	/* 64-bit Table Ind. Indexing Mode  */
	#घोषणा   EXTIBMV 0x02	/* Enable 64-bit Table Ind. BMOV    */
	#घोषणा   EXDBMV 0x01	/* Enable 64-bit Direct BMOV        */

/*58*/  u16	nc_sbdl;	/* Lowlevel: data from scsi data    */
/*5a*/  u16	nc_5a_;

/*5c*/  u8	nc_scr0;	/* Working रेजिस्टर B               */
/*5d*/  u8	nc_scr1;	/*                                  */
/*5e*/  u8	nc_scr2;	/*                                  */
/*5f*/  u8	nc_scr3;	/*                                  */

/*60*/  u8	nc_scrx[64];	/* Working रेजिस्टर C-R             */
/*a0*/	u32	nc_mmrs;	/* Memory Move Read Selector        */
/*a4*/	u32	nc_mmws;	/* Memory Move Write Selector       */
/*a8*/	u32	nc_sfs;		/* Script Fetch Selector            */
/*ac*/	u32	nc_drs;		/* DSA Relative Selector            */
/*b0*/	u32	nc_sbms;	/* Static Block Move Selector       */
/*b4*/	u32	nc_dbms;	/* Dynamic Block Move Selector      */
/*b8*/	u32	nc_dnad64;	/* DMA Next Address 64              */
/*bc*/	u16	nc_scntl4;	/* C1010 only                       */
	#घोषणा   U3EN   0x80	/* Enable Ultra 3                   */
	#घोषणा   AIPEN	 0x40   /* Allow check upper byte lanes     */
	#घोषणा   XCLKH_DT 0x08 /* Extra घड़ी of data hold on DT
					transfer edge	            */
	#घोषणा   XCLKH_ST 0x04 /* Extra घड़ी of data hold on ST
					transfer edge	            */

/*be*/  u8	nc_aipcntl0;	/* Epat Control 1 C1010 only        */
/*bf*/  u8	nc_aipcntl1;	/* AIP Control C1010_66 Only        */

/*c0*/	u32	nc_pmjad1;	/* Phase Mismatch Jump Address 1    */
/*c4*/	u32	nc_pmjad2;	/* Phase Mismatch Jump Address 2    */
/*c8*/	u8	nc_rbc;		/* Reमुख्यing Byte Count             */
/*c9*/	u8	nc_rbc1;	/*                                  */
/*ca*/	u8	nc_rbc2;	/*                                  */
/*cb*/	u8	nc_rbc3;	/*                                  */

/*cc*/	u8	nc_ua;		/* Updated Address                  */
/*cd*/	u8	nc_ua1;		/*                                  */
/*ce*/	u8	nc_ua2;		/*                                  */
/*cf*/	u8	nc_ua3;		/*                                  */
/*d0*/	u32	nc_esa;		/* Entry Storage Address            */
/*d4*/	u8	nc_ia;		/* Inकाष्ठाion Address              */
/*d5*/	u8	nc_ia1;
/*d6*/	u8	nc_ia2;
/*d7*/	u8	nc_ia3;
/*d8*/	u32	nc_sbc;		/* SCSI Byte Count (3 bytes only)   */
/*dc*/	u32	nc_csbc;	/* Cumulative SCSI Byte Count       */

				/* Following क्रम C1010 only         */
/*e0*/  u16	nc_crcpad;	/* CRC Value                        */
/*e2*/  u8	nc_crccntl0;	/* CRC control रेजिस्टर             */
	#घोषणा   SNDCRC  0x10	/* Send CRC Request                 */
/*e3*/  u8	nc_crccntl1;	/* CRC control रेजिस्टर             */
/*e4*/  u32	nc_crcdata;	/* CRC data रेजिस्टर                */ 
/*e8*/  u32	nc_e8_;		/* rsvd 			    */
/*ec*/  u32	nc_ec_;		/* rsvd 			    */
/*f0*/  u16	nc_dfbc;	/* DMA FIFO byte count              */ 

पूर्ण;

/*-----------------------------------------------------------
**
**	Utility macros क्रम the script.
**
**-----------------------------------------------------------
*/

#घोषणा REGJ(p,r) (दुरत्व(काष्ठा ncr_reg, p ## r))
#घोषणा REG(r) REGJ (nc_, r)

प्रकार u32 ncrcmd;

/*-----------------------------------------------------------
**
**	SCSI phases
**
**	DT phases illegal क्रम ncr driver.
**
**-----------------------------------------------------------
*/

#घोषणा	SCR_DATA_OUT	0x00000000
#घोषणा	SCR_DATA_IN	0x01000000
#घोषणा	SCR_COMMAND	0x02000000
#घोषणा	SCR_STATUS	0x03000000
#घोषणा SCR_DT_DATA_OUT	0x04000000
#घोषणा SCR_DT_DATA_IN	0x05000000
#घोषणा SCR_MSG_OUT	0x06000000
#घोषणा SCR_MSG_IN      0x07000000

#घोषणा SCR_ILG_OUT	0x04000000
#घोषणा SCR_ILG_IN	0x05000000

/*-----------------------------------------------------------
**
**	Data transfer via SCSI.
**
**-----------------------------------------------------------
**
**	MOVE_ABS (LEN)
**	<<start address>>
**
**	MOVE_IND (LEN)
**	<<dnad_offset>>
**
**	MOVE_TBL
**	<<dnad_offset>>
**
**-----------------------------------------------------------
*/

#घोषणा OPC_MOVE          0x08000000

#घोषणा SCR_MOVE_ABS(l) ((0x00000000 | OPC_MOVE) | (l))
#घोषणा SCR_MOVE_IND(l) ((0x20000000 | OPC_MOVE) | (l))
#घोषणा SCR_MOVE_TBL     (0x10000000 | OPC_MOVE)

#घोषणा SCR_CHMOV_ABS(l) ((0x00000000) | (l))
#घोषणा SCR_CHMOV_IND(l) ((0x20000000) | (l))
#घोषणा SCR_CHMOV_TBL     (0x10000000)

काष्ठा scr_tblmove अणु
        u32  size;
        u32  addr;
पूर्ण;

/*-----------------------------------------------------------
**
**	Selection
**
**-----------------------------------------------------------
**
**	SEL_ABS | SCR_ID (0..15)    [ | REL_JMP]
**	<<alternate_address>>
**
**	SEL_TBL | << dnad_offset>>  [ | REL_JMP]
**	<<alternate_address>>
**
**-----------------------------------------------------------
*/

#घोषणा	SCR_SEL_ABS	0x40000000
#घोषणा	SCR_SEL_ABS_ATN	0x41000000
#घोषणा	SCR_SEL_TBL	0x42000000
#घोषणा	SCR_SEL_TBL_ATN	0x43000000


#अगर_घोषित SCSI_NCR_BIG_ENDIAN
काष्ठा scr_tblsel अणु
        u8	sel_scntl3;
        u8	sel_id;
        u8	sel_sxfer;
        u8	sel_scntl4;	
पूर्ण;
#अन्यथा
काष्ठा scr_tblsel अणु
        u8	sel_scntl4;	
        u8	sel_sxfer;
        u8	sel_id;
        u8	sel_scntl3;
पूर्ण;
#पूर्ण_अगर

#घोषणा SCR_JMP_REL     0x04000000
#घोषणा SCR_ID(id)	(((u32)(id)) << 16)

/*-----------------------------------------------------------
**
**	Waiting क्रम Disconnect or Reselect
**
**-----------------------------------------------------------
**
**	WAIT_DISC
**	dummy: <<alternate_address>>
**
**	WAIT_RESEL
**	<<alternate_address>>
**
**-----------------------------------------------------------
*/

#घोषणा	SCR_WAIT_DISC	0x48000000
#घोषणा SCR_WAIT_RESEL  0x50000000

/*-----------------------------------------------------------
**
**	Bit Set / Reset
**
**-----------------------------------------------------------
**
**	SET (flags अणु|.. पूर्ण)
**
**	CLR (flags अणु|.. पूर्ण)
**
**-----------------------------------------------------------
*/

#घोषणा SCR_SET(f)     (0x58000000 | (f))
#घोषणा SCR_CLR(f)     (0x60000000 | (f))

#घोषणा	SCR_CARRY	0x00000400
#घोषणा	SCR_TRG		0x00000200
#घोषणा	SCR_ACK		0x00000040
#घोषणा	SCR_ATN		0x00000008




/*-----------------------------------------------------------
**
**	Memory to memory move
**
**-----------------------------------------------------------
**
**	COPY (bytecount)
**	<< source_address >>
**	<< destination_address >>
**
**	SCR_COPY   sets the NO FLUSH option by शेष.
**	SCR_COPY_F करोes not set this option.
**
**	For chips which करो not support this option,
**	ncr_copy_and_bind() will हटाओ this bit.
**-----------------------------------------------------------
*/

#घोषणा SCR_NO_FLUSH 0x01000000

#घोषणा SCR_COPY(n) (0xc0000000 | SCR_NO_FLUSH | (n))
#घोषणा SCR_COPY_F(n) (0xc0000000 | (n))

/*-----------------------------------------------------------
**
**	Register move and binary operations
**
**-----------------------------------------------------------
**
**	SFBR_REG (reg, op, data)        reg  = SFBR op data
**	<< 0 >>
**
**	REG_SFBR (reg, op, data)        SFBR = reg op data
**	<< 0 >>
**
**	REG_REG  (reg, op, data)        reg  = reg op data
**	<< 0 >>
**
**-----------------------------------------------------------
**	On 810A, 860, 825A, 875, 895 and 896 chips the content 
**	of SFBR रेजिस्टर can be used as data (SCR_SFBR_DATA).
**	The 896 has additional IO रेजिस्टरs starting at 
**	offset 0x80. Bit 7 of रेजिस्टर offset is stored in 
**	bit 7 of the SCRIPTS inकाष्ठाion first DWORD.
**-----------------------------------------------------------
*/

#घोषणा SCR_REG_OFS(ofs) ((((ofs) & 0x7f) << 16ul) + ((ofs) & 0x80)) 

#घोषणा SCR_SFBR_REG(reg,op,data) \
        (0x68000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))

#घोषणा SCR_REG_SFBR(reg,op,data) \
        (0x70000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))

#घोषणा SCR_REG_REG(reg,op,data) \
        (0x78000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))


#घोषणा      SCR_LOAD   0x00000000
#घोषणा      SCR_SHL    0x01000000
#घोषणा      SCR_OR     0x02000000
#घोषणा      SCR_XOR    0x03000000
#घोषणा      SCR_AND    0x04000000
#घोषणा      SCR_SHR    0x05000000
#घोषणा      SCR_ADD    0x06000000
#घोषणा      SCR_ADDC   0x07000000

#घोषणा      SCR_SFBR_DATA   (0x00800000>>8ul)	/* Use SFBR as data */

/*-----------------------------------------------------------
**
**	FROM_REG (reg)		  SFBR = reg
**	<< 0 >>
**
**	TO_REG	 (reg)		  reg  = SFBR
**	<< 0 >>
**
**	LOAD_REG (reg, data)	  reg  = <data>
**	<< 0 >>
**
**	LOAD_SFBR(data) 	  SFBR = <data>
**	<< 0 >>
**
**-----------------------------------------------------------
*/

#घोषणा	SCR_FROM_REG(reg) \
	SCR_REG_SFBR(reg,SCR_OR,0)

#घोषणा	SCR_TO_REG(reg) \
	SCR_SFBR_REG(reg,SCR_OR,0)

#घोषणा	SCR_LOAD_REG(reg,data) \
	SCR_REG_REG(reg,SCR_LOAD,data)

#घोषणा SCR_LOAD_SFBR(data) \
        (SCR_REG_SFBR (gpreg, SCR_LOAD, data))

/*-----------------------------------------------------------
**
**	LOAD  from memory   to रेजिस्टर.
**	STORE from रेजिस्टर to memory.
**
**	Only supported by 810A, 860, 825A, 875, 895 and 896.
**
**-----------------------------------------------------------
**
**	LOAD_ABS (LEN)
**	<<start address>>
**
**	LOAD_REL (LEN)        (DSA relative)
**	<<dsa_offset>>
**
**-----------------------------------------------------------
*/

#घोषणा SCR_REG_OFS2(ofs) (((ofs) & 0xff) << 16ul)
#घोषणा SCR_NO_FLUSH2	0x02000000
#घोषणा SCR_DSA_REL2	0x10000000

#घोषणा SCR_LOAD_R(reg, how, n) \
        (0xe1000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))

#घोषणा SCR_STORE_R(reg, how, n) \
        (0xe0000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))

#घोषणा SCR_LOAD_ABS(reg, n)	SCR_LOAD_R(reg, SCR_NO_FLUSH2, n)
#घोषणा SCR_LOAD_REL(reg, n)	SCR_LOAD_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2, n)
#घोषणा SCR_LOAD_ABS_F(reg, n)	SCR_LOAD_R(reg, 0, n)
#घोषणा SCR_LOAD_REL_F(reg, n)	SCR_LOAD_R(reg, SCR_DSA_REL2, n)

#घोषणा SCR_STORE_ABS(reg, n)	SCR_STORE_R(reg, SCR_NO_FLUSH2, n)
#घोषणा SCR_STORE_REL(reg, n)	SCR_STORE_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2,n)
#घोषणा SCR_STORE_ABS_F(reg, n)	SCR_STORE_R(reg, 0, n)
#घोषणा SCR_STORE_REL_F(reg, n)	SCR_STORE_R(reg, SCR_DSA_REL2, n)


/*-----------------------------------------------------------
**
**	Waiting क्रम Disconnect or Reselect
**
**-----------------------------------------------------------
**
**	JUMP            [ | IFTRUE/IFFALSE ( ... ) ]
**	<<address>>
**
**	JUMPR           [ | IFTRUE/IFFALSE ( ... ) ]
**	<<distance>>
**
**	CALL            [ | IFTRUE/IFFALSE ( ... ) ]
**	<<address>>
**
**	CALLR           [ | IFTRUE/IFFALSE ( ... ) ]
**	<<distance>>
**
**	RETURN          [ | IFTRUE/IFFALSE ( ... ) ]
**	<<dummy>>
**
**	INT             [ | IFTRUE/IFFALSE ( ... ) ]
**	<<ident>>
**
**	INT_FLY         [ | IFTRUE/IFFALSE ( ... ) ]
**	<<ident>>
**
**	Conditions:
**	     WHEN (phase)
**	     IF   (phase)
**	     CARRYSET
**	     DATA (data, mask)
**
**-----------------------------------------------------------
*/

#घोषणा SCR_NO_OP       0x80000000
#घोषणा SCR_JUMP        0x80080000
#घोषणा SCR_JUMP64      0x80480000
#घोषणा SCR_JUMPR       0x80880000
#घोषणा SCR_CALL        0x88080000
#घोषणा SCR_CALLR       0x88880000
#घोषणा SCR_RETURN      0x90080000
#घोषणा SCR_INT         0x98080000
#घोषणा SCR_INT_FLY     0x98180000

#घोषणा IFFALSE(arg)   (0x00080000 | (arg))
#घोषणा IFTRUE(arg)    (0x00000000 | (arg))

#घोषणा WHEN(phase)    (0x00030000 | (phase))
#घोषणा IF(phase)      (0x00020000 | (phase))

#घोषणा DATA(D)        (0x00040000 | ((D) & 0xff))
#घोषणा MASK(D,M)      (0x00040000 | (((M ^ 0xff) & 0xff) << 8ul)|((D) & 0xff))

#घोषणा CARRYSET       (0x00200000)

/*-----------------------------------------------------------
**
**	SCSI  स्थिरants.
**
**-----------------------------------------------------------
*/

/*
 * End of ncrreg from FreeBSD
 */

/*
	Build a scatter/gather entry.
	see sym53c8xx_2/sym_hipd.h क्रम more detailed sym_build_sge()
	implementation ;)
 */

#घोषणा ncr_build_sge(np, data, badd, len)	\
करो अणु						\
	(data)->addr = cpu_to_scr(badd);	\
	(data)->size = cpu_to_scr(len);		\
पूर्ण जबतक (0)

/*==========================================================
**
**	Structures used by the detection routine to transmit 
**	device configuration to the attach function.
**
**==========================================================
*/
काष्ठा ncr_slot अणु
	u_दीर्घ	base;
	u_दीर्घ	base_2;
	u_दीर्घ	base_c;
	u_दीर्घ	base_2_c;
	व्योम __iomem *base_v;
	व्योम __iomem *base_2_v;
	पूर्णांक	irq;
/* port and reg fields to use INB, OUTB macros */
	अस्थिर काष्ठा ncr_reg	__iomem *reg;
पूर्ण;

/*==========================================================
**
**	Structure used by detection routine to save data on 
**	each detected board क्रम attach.
**
**==========================================================
*/
काष्ठा ncr_device अणु
	काष्ठा device  *dev;
	काष्ठा ncr_slot  slot;
	काष्ठा ncr_chip  chip;
	u_अक्षर host_id;
	u8 dअगरferential;
पूर्ण;

बाह्य काष्ठा Scsi_Host *ncr_attach(काष्ठा scsi_host_ढाँचा *tpnt, पूर्णांक unit, काष्ठा ncr_device *device);
बाह्य व्योम ncr53c8xx_release(काष्ठा Scsi_Host *host);
irqवापस_t ncr53c8xx_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
बाह्य पूर्णांक ncr53c8xx_init(व्योम);
बाह्य व्योम ncr53c8xx_निकास(व्योम);

#पूर्ण_अगर /* NCR53C8XX_H */
