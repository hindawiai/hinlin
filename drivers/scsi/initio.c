<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**************************************************************************
 * Initio 9100 device driver क्रम Linux.
 *
 * Copyright (c) 1994-1998 Initio Corporation
 * Copyright (c) 1998 Bas Vermeulen <bvermeul@blackstar.xs4all.nl>
 * Copyright (c) 2004 Christoph Hellwig <hch@lst.de>
 * Copyright (c) 2007 Red Hat
 *
 *************************************************************************
 *
 * DESCRIPTION:
 *
 * This is the Linux low-level SCSI driver क्रम Initio INI-9X00U/UW SCSI host
 * adapters
 *
 * 08/06/97 hc	- v1.01h
 *		- Support inic-940 and inic-935
 * 09/26/97 hc	- v1.01i
 *		- Make correction from J.W. Schultz suggestion
 * 10/13/97 hc	- Support reset function
 * 10/21/97 hc	- v1.01j
 *		- Support 32 LUN (SCSI 3)
 * 01/14/98 hc	- v1.01k
 *		- Fix memory allocation problem
 * 03/04/98 hc	- v1.01l
 *		- Fix tape शुरुआत which will hang the प्रणाली problem
 *		- Set can_queue to initio_num_scb
 * 06/25/98 hc	- v1.01m
 *		- Get it work क्रम kernel version >= 2.1.75
 *		- Dynamic assign SCSI bus reset holding समय in initio_init()
 * 07/02/98 hc	- v1.01n
 *		- Support 0002134A
 * 08/07/98 hc  - v1.01o
 *		- Change the initio_पात_srb routine to use scsi_करोne. <01>
 * 09/07/98 hl  - v1.02
 *              - Change the INI9100U define and proc_dir_entry to
 *                reflect the newer Kernel 2.1.118, but the v1.o1o
 *                should work with Kernel 2.1.118.
 * 09/20/98 wh  - v1.02a
 *              - Support Abort command.
 *              - Handle reset routine.
 * 09/21/98 hl  - v1.03
 *              - हटाओ comments.
 * 12/09/98 bv	- v1.03a
 *		- Removed unused code
 * 12/13/98 bv	- v1.03b
 *		- Remove cli() locking क्रम kernels >= 2.1.95. This uses
 *		  spinlocks to serialize access to the pSRB_head and
 *		  pSRB_tail members of the HCS काष्ठाure.
 * 09/01/99 bv	- v1.03d
 *		- Fixed a deadlock problem in SMP.
 * 21/01/99 bv	- v1.03e
 *		- Add support क्रम the Domex 3192U PCI SCSI
 *		  This is a slightly modअगरied patch by
 *		  Brian Macy <bmacy@sunshinecomputing.com>
 * 22/02/99 bv	- v1.03f
 *		- Didn't detect the INIC-950 in 2.0.x correctly.
 *		  Now fixed.
 * 05/07/99 bv	- v1.03g
 *		- Changed the assumption that HZ = 100
 * 10/17/03 mc	- v1.04
 *		- added new DMA API support
 * 06/01/04 jmd	- v1.04a
 *		- Re-add reset_bus support
 **************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "initio.h"

#घोषणा SENSE_SIZE		14

#घोषणा i91u_MAXQUEUE		2
#घोषणा i91u_REVID "Initio INI-9X00U/UW SCSI device driver; Revision: 1.04a"

#अगर_घोषित DEBUG_i91u
अटल अचिन्हित पूर्णांक i91u_debug = DEBUG_DEFAULT;
#पूर्ण_अगर

अटल पूर्णांक initio_tag_enable = 1;

#अगर_घोषित DEBUG_i91u
अटल पूर्णांक setup_debug = 0;
#पूर्ण_अगर

अटल व्योम i91uSCBPost(u8 * pHcb, u8 * pScb);

#घोषणा DEBUG_INTERRUPT 0
#घोषणा DEBUG_QUEUE     0
#घोषणा DEBUG_STATE     0
#घोषणा INT_DISC	0

/*--- क्रमward references ---*/
अटल काष्ठा scsi_ctrl_blk *initio_find_busy_scb(काष्ठा initio_host * host, u16 tarlun);
अटल काष्ठा scsi_ctrl_blk *initio_find_करोne_scb(काष्ठा initio_host * host);

अटल पूर्णांक tulip_मुख्य(काष्ठा initio_host * host);

अटल पूर्णांक initio_next_state(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_1(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_2(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_3(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_4(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_5(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_6(काष्ठा initio_host * host);
अटल पूर्णांक initio_state_7(काष्ठा initio_host * host);
अटल पूर्णांक initio_xfer_data_in(काष्ठा initio_host * host);
अटल पूर्णांक initio_xfer_data_out(काष्ठा initio_host * host);
अटल पूर्णांक initio_xpad_in(काष्ठा initio_host * host);
अटल पूर्णांक initio_xpad_out(काष्ठा initio_host * host);
अटल पूर्णांक initio_status_msg(काष्ठा initio_host * host);

अटल पूर्णांक initio_msgin(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgin_sync(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgin_accept(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgout_reject(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgin_extend(काष्ठा initio_host * host);

अटल पूर्णांक initio_msgout_ide(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgout_पात_targ(काष्ठा initio_host * host);
अटल पूर्णांक initio_msgout_पात_tag(काष्ठा initio_host * host);

अटल पूर्णांक initio_bus_device_reset(काष्ठा initio_host * host);
अटल व्योम initio_select_atn(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb);
अटल व्योम initio_select_atn3(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb);
अटल व्योम initio_select_atn_stop(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb);
अटल पूर्णांक पूर्णांक_initio_busमुक्त(काष्ठा initio_host * host);
अटल पूर्णांक पूर्णांक_initio_scsi_rst(काष्ठा initio_host * host);
अटल पूर्णांक पूर्णांक_initio_bad_seq(काष्ठा initio_host * host);
अटल पूर्णांक पूर्णांक_initio_resel(काष्ठा initio_host * host);
अटल पूर्णांक initio_sync_करोne(काष्ठा initio_host * host);
अटल पूर्णांक wdtr_करोne(काष्ठा initio_host * host);
अटल पूर्णांक रुको_tulip(काष्ठा initio_host * host);
अटल पूर्णांक initio_रुको_करोne_disc(काष्ठा initio_host * host);
अटल पूर्णांक initio_रुको_disc(काष्ठा initio_host * host);
अटल व्योम tulip_scsi(काष्ठा initio_host * host);
अटल पूर्णांक initio_post_scsi_rst(काष्ठा initio_host * host);

अटल व्योम initio_se2_ew_en(अचिन्हित दीर्घ base);
अटल व्योम initio_se2_ew_ds(अचिन्हित दीर्घ base);
अटल पूर्णांक initio_se2_rd_all(अचिन्हित दीर्घ base);
अटल व्योम initio_se2_update_all(अचिन्हित दीर्घ base);	/* setup शेष pattern */
अटल व्योम initio_पढ़ो_eeprom(अचिन्हित दीर्घ base);

/* ---- INTERNAL VARIABLES ---- */

अटल NVRAM i91unvram;
अटल NVRAM *i91unvramp;

अटल u8 i91udftNvRam[64] =
अणु
	/*----------- header -----------*/
	0x25, 0xc9,		/* Signature    */
	0x40,			/* Size         */
	0x01,			/* Revision     */
	/* -- Host Adapter Structure -- */
	0x95,			/* ModelByte0   */
	0x00,			/* ModelByte1   */
	0x00,			/* ModelInfo    */
	0x01,			/* NumOfCh      */
	NBC1_DEFAULT,		/* BIOSConfig1  */
	0,			/* BIOSConfig2  */
	0,			/* HAConfig1    */
	0,			/* HAConfig2    */
	/* SCSI channel 0 and target Structure  */
	7,			/* SCSIid       */
	NCC1_DEFAULT,		/* SCSIconfig1  */
	0,			/* SCSIconfig2  */
	0x10,			/* NumSCSItarget */

	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,

	/* SCSI channel 1 and target Structure  */
	7,			/* SCSIid       */
	NCC1_DEFAULT,		/* SCSIconfig1  */
	0,			/* SCSIconfig2  */
	0x10,			/* NumSCSItarget */

	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT, NTC_DEFAULT,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0पूर्ण;			/*      - CheckSum -            */


अटल u8 initio_rate_tbl[8] =	/* fast 20      */
अणु
				/* nanosecond भागide by 4 */
	12,			/* 50ns,  20M   */
	18,			/* 75ns,  13.3M */
	25,			/* 100ns, 10M   */
	31,			/* 125ns, 8M    */
	37,			/* 150ns, 6.6M  */
	43,			/* 175ns, 5.7M  */
	50,			/* 200ns, 5M    */
	62			/* 250ns, 4M    */
पूर्ण;

अटल व्योम initio_करो_छोड़ो(अचिन्हित amount)
अणु
	/* Pause क्रम amount jअगरfies */
	अचिन्हित दीर्घ the_समय = jअगरfies + amount;

	जबतक (समय_beक्रमe_eq(jअगरfies, the_समय))
		cpu_relax();
पूर्ण

/*-- क्रमward reference --*/

/******************************************************************
 Input: inकाष्ठाion क्रम  Serial E2PROM

 EX: se2_rd(0 call se2_instr() to send address and पढ़ो command

	 StartBit  OP_Code   Address                Data
	 --------- --------  ------------------     -------
	 1         1 , 0     A5,A4,A3,A2,A1,A0      D15-D0

		 +-----------------------------------------------------
		 |
 CS -----+
			+--+  +--+  +--+  +--+  +--+
			^  |  ^  |  ^  |  ^  |  ^  |
			|  |  |  |  |  |  |  |  |  |
 CLK -------+  +--+  +--+  +--+  +--+  +--
 (leading edge trigger)

		 +--1-----1--+
		 | SB    OP  |  OP    A5    A4
 DI  ----+           +--0------------------
 (address and cmd sent to nvram)

	 -------------------------------------------+
												|
 DO                                             +---
 (data sent from nvram)


******************************************************************/

/**
 *	initio_se2_instr	-	bitbang an inकाष्ठाion
 *	@base: Base of InitIO controller
 *	@instr: Inकाष्ठाion क्रम serial E2PROM
 *
 *	Bitbang an inकाष्ठाion out to the serial E2Prom
 */

अटल व्योम initio_se2_instr(अचिन्हित दीर्घ base, u8 instr)
अणु
	पूर्णांक i;
	u8 b;

	outb(SE2CS | SE2DO, base + TUL_NVRAM);		/* cs+start bit */
	udelay(30);
	outb(SE2CS | SE2CLK | SE2DO, base + TUL_NVRAM);	/* +CLK */
	udelay(30);

	क्रम (i = 0; i < 8; i++) अणु
		अगर (instr & 0x80)
			b = SE2CS | SE2DO;		/* -CLK+dataBit */
		अन्यथा
			b = SE2CS;			/* -CLK */
		outb(b, base + TUL_NVRAM);
		udelay(30);
		outb(b | SE2CLK, base + TUL_NVRAM);	/* +CLK */
		udelay(30);
		instr <<= 1;
	पूर्ण
	outb(SE2CS, base + TUL_NVRAM);			/* -CLK */
	udelay(30);
पूर्ण


/**
 *	initio_se2_ew_en	-	Enable erase/ग_लिखो
 *	@base: Base address of InitIO controller
 *
 *	Enable erase/ग_लिखो state of serial EEPROM
 */
व्योम initio_se2_ew_en(अचिन्हित दीर्घ base)
अणु
	initio_se2_instr(base, 0x30);	/* EWEN */
	outb(0, base + TUL_NVRAM);	/* -CS  */
	udelay(30);
पूर्ण


/**
 *	initio_se2_ew_ds	-	Disable erase/ग_लिखो
 *	@base: Base address of InitIO controller
 *
 *	Disable erase/ग_लिखो state of serial EEPROM
 */
व्योम initio_se2_ew_ds(अचिन्हित दीर्घ base)
अणु
	initio_se2_instr(base, 0);	/* EWDS */
	outb(0, base + TUL_NVRAM);	/* -CS  */
	udelay(30);
पूर्ण


/**
 *	initio_se2_rd		-	पढ़ो E2PROM word
 *	@base: Base of InitIO controller
 *	@addr: Address of word in E2PROM
 *
 *	Read a word from the NV E2PROM device
 */
अटल u16 initio_se2_rd(अचिन्हित दीर्घ base, u8 addr)
अणु
	u8 instr, rb;
	u16 val = 0;
	पूर्णांक i;

	instr = (u8) (addr | 0x80);
	initio_se2_instr(base, instr);	/* READ INSTR */

	क्रम (i = 15; i >= 0; i--) अणु
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);	/* +CLK */
		udelay(30);
		outb(SE2CS, base + TUL_NVRAM);		/* -CLK */

		/* sample data after the following edge of घड़ी  */
		rb = inb(base + TUL_NVRAM);
		rb &= SE2DI;
		val += (rb << i);
		udelay(30);	/* 6/20/95 */
	पूर्ण

	outb(0, base + TUL_NVRAM);		/* no chip select */
	udelay(30);
	वापस val;
पूर्ण

/**
 *	initio_se2_wr		-	पढ़ो E2PROM word
 *	@base: Base of InitIO controller
 *	@addr: Address of word in E2PROM
 *	@val: Value to ग_लिखो
 *
 *	Write a word to the NV E2PROM device. Used when recovering from
 *	a problem with the NV.
 */
अटल व्योम initio_se2_wr(अचिन्हित दीर्घ base, u8 addr, u16 val)
अणु
	u8 rb;
	u8 instr;
	पूर्णांक i;

	instr = (u8) (addr | 0x40);
	initio_se2_instr(base, instr);	/* WRITE INSTR */
	क्रम (i = 15; i >= 0; i--) अणु
		अगर (val & 0x8000)
			outb(SE2CS | SE2DO, base + TUL_NVRAM);	/* -CLK+dataBit 1 */
		अन्यथा
			outb(SE2CS, base + TUL_NVRAM);		/* -CLK+dataBit 0 */
		udelay(30);
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);		/* +CLK */
		udelay(30);
		val <<= 1;
	पूर्ण
	outb(SE2CS, base + TUL_NVRAM);				/* -CLK */
	udelay(30);
	outb(0, base + TUL_NVRAM);				/* -CS  */
	udelay(30);

	outb(SE2CS, base + TUL_NVRAM);				/* +CS  */
	udelay(30);

	क्रम (;;) अणु
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);		/* +CLK */
		udelay(30);
		outb(SE2CS, base + TUL_NVRAM);			/* -CLK */
		udelay(30);
		अगर ((rb = inb(base + TUL_NVRAM)) & SE2DI)
			अवरोध;	/* ग_लिखो complete */
	पूर्ण
	outb(0, base + TUL_NVRAM);				/* -CS */
पूर्ण

/**
 *	initio_se2_rd_all	-	पढ़ो hostadapter NV configuration
 *	@base: Base address of InitIO controller
 *
 *	Reads the E2PROM data पूर्णांकo मुख्य memory. Ensures that the checksum
 *	and header marker are valid. Returns 1 on success -1 on error.
 */

अटल पूर्णांक initio_se2_rd_all(अचिन्हित दीर्घ base)
अणु
	पूर्णांक i;
	u16 chksum = 0;
	u16 *np;

	i91unvramp = &i91unvram;
	np = (u16 *) i91unvramp;
	क्रम (i = 0; i < 32; i++)
		*np++ = initio_se2_rd(base, i);

	/* Is signature "ini" ok ? */
	अगर (i91unvramp->NVM_Signature != INI_SIGNATURE)
		वापस -1;
	/* Is ckecksum ok ? */
	np = (u16 *) i91unvramp;
	क्रम (i = 0; i < 31; i++)
		chksum += *np++;
	अगर (i91unvramp->NVM_CheckSum != chksum)
		वापस -1;
	वापस 1;
पूर्ण

/**
 *	initio_se2_update_all		-	Update E2PROM
 *	@base: Base of InitIO controller
 *
 *	Update the E2PROM by wrting any changes पूर्णांकo the E2PROM
 *	chip, rewriting the checksum.
 */
अटल व्योम initio_se2_update_all(अचिन्हित दीर्घ base)
अणु				/* setup शेष pattern */
	पूर्णांक i;
	u16 chksum = 0;
	u16 *np, *np1;

	i91unvramp = &i91unvram;
	/* Calculate checksum first */
	np = (u16 *) i91udftNvRam;
	क्रम (i = 0; i < 31; i++)
		chksum += *np++;
	*np = chksum;
	initio_se2_ew_en(base);	/* Enable ग_लिखो  */

	np = (u16 *) i91udftNvRam;
	np1 = (u16 *) i91unvramp;
	क्रम (i = 0; i < 32; i++, np++, np1++) अणु
		अगर (*np != *np1)
			initio_se2_wr(base, i, *np);
	पूर्ण
	initio_se2_ew_ds(base);	/* Disable ग_लिखो   */
पूर्ण

/**
 *	initio_पढ़ो_eeprom		-	Retrieve configuration
 *	@base: Base of InitIO Host Adapter
 *
 *	Retrieve the host adapter configuration data from E2Prom. If the
 *	data is invalid then the शेषs are used and are also restored
 *	पूर्णांकo the E2PROM. This क्रमms the access poपूर्णांक क्रम the SCSI driver
 *	पूर्णांकo the E2PROM layer, the other functions क्रम the E2PROM are all
 *	पूर्णांकernal use.
 *
 *	Must be called single thपढ़ोed, uses a shared global area.
 */

अटल व्योम initio_पढ़ो_eeprom(अचिन्हित दीर्घ base)
अणु
	u8 gctrl;

	i91unvramp = &i91unvram;
	/* Enable EEProm programming */
	gctrl = inb(base + TUL_GCTRL);
	outb(gctrl | TUL_GCTRL_EEPROM_BIT, base + TUL_GCTRL);
	अगर (initio_se2_rd_all(base) != 1) अणु
		initio_se2_update_all(base);	/* setup शेष pattern */
		initio_se2_rd_all(base);	/* load again  */
	पूर्ण
	/* Disable EEProm programming */
	gctrl = inb(base + TUL_GCTRL);
	outb(gctrl & ~TUL_GCTRL_EEPROM_BIT, base + TUL_GCTRL);
पूर्ण

/**
 *	initio_stop_bm		-	stop bus master
 *	@host: InitIO we are stopping
 *
 *	Stop any pending DMA operation, पातing the DMA अगर necessary
 */

अटल व्योम initio_stop_bm(काष्ठा initio_host * host)
अणु

	अगर (inb(host->addr + TUL_XStatus) & XPEND) अणु	/* अगर DMA xfer is pending, पात DMA xfer */
		outb(TAX_X_ABT | TAX_X_CLR_FIFO, host->addr + TUL_XCmd);
		/* रुको Abort DMA xfer करोne */
		जबतक ((inb(host->addr + TUL_Int) & XABT) == 0)
			cpu_relax();
	पूर्ण
	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
पूर्ण

/**
 *	initio_reset_scsi		-	Reset SCSI host controller
 *	@host: InitIO host to reset
 *	@seconds: Recovery समय
 *
 *	Perक्रमm a full reset of the SCSI subप्रणाली.
 */

अटल पूर्णांक initio_reset_scsi(काष्ठा initio_host * host, पूर्णांक seconds)
अणु
	outb(TSC_RST_BUS, host->addr + TUL_SCtrl0);

	जबतक (!((host->jsपूर्णांक = inb(host->addr + TUL_SInt)) & TSS_SCSIRST_INT))
		cpu_relax();

	/* reset tulip chip */
	outb(0, host->addr + TUL_SSignal);

	/* Stall क्रम a जबतक, रुको क्रम target's firmware पढ़ोy,make it 2 sec ! */
	/* SONY 5200 tape drive won't work अगर only stall क्रम 1 sec */
	/* FIXME: this is a very दीर्घ busy रुको right now */
	initio_करो_छोड़ो(seconds * HZ);

	inb(host->addr + TUL_SInt);
	वापस SCSI_RESET_SUCCESS;
पूर्ण

/**
 *	initio_init		-	set up an InitIO host adapter
 *	@host: InitIO host adapter
 *	@bios_addr: BIOS address
 *
 *	Set up the host adapter and devices according to the configuration
 *	retrieved from the E2PROM.
 *
 *	Locking: Calls E2PROM layer code which is not re-enterable so must
 *	run single thपढ़ोed क्रम now.
 */

अटल व्योम initio_init(काष्ठा initio_host * host, u8 *bios_addr)
अणु
	पूर्णांक i;
	u8 *flags;
	u8 *heads;

	/* Get E2Prom configuration */
	initio_पढ़ो_eeprom(host->addr);
	अगर (i91unvramp->NVM_SCSIInfo[0].NVM_NumOfTarg == 8)
		host->max_tar = 8;
	अन्यथा
		host->max_tar = 16;

	host->config = i91unvramp->NVM_SCSIInfo[0].NVM_ChConfig1;

	host->scsi_id = i91unvramp->NVM_SCSIInfo[0].NVM_ChSCSIID;
	host->idmask = ~(1 << host->scsi_id);

#अगर_घोषित CHK_PARITY
	/* Enable parity error response */
	outb(inb(host->addr + TUL_PCMD) | 0x40, host->addr + TUL_PCMD);
#पूर्ण_अगर

	/* Mask all the पूर्णांकerrupt       */
	outb(0x1F, host->addr + TUL_Mask);

	initio_stop_bm(host);
	/* --- Initialize the tulip --- */
	outb(TSC_RST_CHIP, host->addr + TUL_SCtrl0);

	/* program HBA's SCSI ID        */
	outb(host->scsi_id << 4, host->addr + TUL_SScsiId);

	/* Enable Initiator Mode ,phase latch,alternate sync period mode,
	   disable SCSI reset */
	अगर (host->config & HCC_EN_PAR)
		host->sconf1 = (TSC_INITDEFAULT | TSC_EN_SCSI_PAR);
	अन्यथा
		host->sconf1 = (TSC_INITDEFAULT);
	outb(host->sconf1, host->addr + TUL_SConfig);

	/* Enable HW reselect */
	outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);

	outb(0, host->addr + TUL_SPeriod);

	/* selection समय out = 250 ms */
	outb(153, host->addr + TUL_STimeOut);

	/* Enable SCSI terminator */
	outb((host->config & (HCC_ACT_TERM1 | HCC_ACT_TERM2)),
		host->addr + TUL_XCtrl);
	outb(((host->config & HCC_AUTO_TERM) >> 4) |
		(inb(host->addr + TUL_GCTRL1) & 0xFE),
		host->addr + TUL_GCTRL1);

	क्रम (i = 0,
	     flags = & (i91unvramp->NVM_SCSIInfo[0].NVM_Targ0Config),
	     heads = bios_addr + 0x180;
	     i < host->max_tar;
	     i++, flags++) अणु
		host->tarमाला_लो[i].flags = *flags & ~(TCF_SYNC_DONE | TCF_WDTR_DONE);
		अगर (host->tarमाला_लो[i].flags & TCF_EN_255)
			host->tarमाला_लो[i].drv_flags = TCF_DRV_255_63;
		अन्यथा
			host->tarमाला_लो[i].drv_flags = 0;
		host->tarमाला_लो[i].js_period = 0;
		host->tarमाला_लो[i].sconfig0 = host->sconf1;
		host->tarमाला_लो[i].heads = *heads++;
		अगर (host->tarमाला_लो[i].heads == 255)
			host->tarमाला_लो[i].drv_flags = TCF_DRV_255_63;
		अन्यथा
			host->tarमाला_लो[i].drv_flags = 0;
		host->tarमाला_लो[i].sectors = *heads++;
		host->tarमाला_लो[i].flags &= ~TCF_BUSY;
		host->act_tags[i] = 0;
		host->max_tags[i] = 0xFF;
	पूर्ण			/* क्रम                          */
	prपूर्णांकk("i91u: PCI Base=0x%04X, IRQ=%d, BIOS=0x%04X0, SCSI ID=%d\n",
	       host->addr, host->pci_dev->irq,
	       host->bios_addr, host->scsi_id);
	/* Reset SCSI Bus */
	अगर (host->config & HCC_SCSI_RESET) अणु
		prपूर्णांकk(KERN_INFO "i91u: Reset SCSI Bus ... \n");
		initio_reset_scsi(host, 10);
	पूर्ण
	outb(0x17, host->addr + TUL_SCFG1);
	outb(0xE9, host->addr + TUL_SIntEnable);
पूर्ण

/**
 *	initio_alloc_scb		-	Allocate an SCB
 *	@host: InitIO host we are allocating क्रम
 *
 *	Walk the SCB list क्रम the controller and allocate a मुक्त SCB अगर
 *	one exists.
 */
अटल काष्ठा scsi_ctrl_blk *initio_alloc_scb(काष्ठा initio_host *host)
अणु
	काष्ठा scsi_ctrl_blk *scb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->avail_lock, flags);
	अगर ((scb = host->first_avail) != शून्य) अणु
#अगर DEBUG_QUEUE
		prपूर्णांकk("find scb at %p\n", scb);
#पूर्ण_अगर
		अगर ((host->first_avail = scb->next) == शून्य)
			host->last_avail = शून्य;
		scb->next = शून्य;
		scb->status = SCB_RENT;
	पूर्ण
	spin_unlock_irqrestore(&host->avail_lock, flags);
	वापस scb;
पूर्ण

/**
 *	initio_release_scb		-	Release an SCB
 *	@host: InitIO host that owns the SCB
 *	@cmnd: SCB command block being वापसed
 *
 *	Return an allocated SCB to the host मुक्त list
 */

अटल व्योम initio_release_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * cmnd)
अणु
	अचिन्हित दीर्घ flags;

#अगर DEBUG_QUEUE
	prपूर्णांकk("Release SCB %p; ", cmnd);
#पूर्ण_अगर
	spin_lock_irqsave(&(host->avail_lock), flags);
	cmnd->srb = शून्य;
	cmnd->status = 0;
	cmnd->next = शून्य;
	अगर (host->last_avail != शून्य) अणु
		host->last_avail->next = cmnd;
		host->last_avail = cmnd;
	पूर्ण अन्यथा अणु
		host->first_avail = cmnd;
		host->last_avail = cmnd;
	पूर्ण
	spin_unlock_irqrestore(&(host->avail_lock), flags);
पूर्ण

/***************************************************************************/
अटल व्योम initio_append_pend_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scbp)
अणु

#अगर DEBUG_QUEUE
	prपूर्णांकk("Append pend SCB %p; ", scbp);
#पूर्ण_अगर
	scbp->status = SCB_PEND;
	scbp->next = शून्य;
	अगर (host->last_pending != शून्य) अणु
		host->last_pending->next = scbp;
		host->last_pending = scbp;
	पूर्ण अन्यथा अणु
		host->first_pending = scbp;
		host->last_pending = scbp;
	पूर्ण
पूर्ण

/***************************************************************************/
अटल व्योम initio_push_pend_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scbp)
अणु

#अगर DEBUG_QUEUE
	prपूर्णांकk("Push pend SCB %p; ", scbp);
#पूर्ण_अगर
	scbp->status = SCB_PEND;
	अगर ((scbp->next = host->first_pending) != शून्य) अणु
		host->first_pending = scbp;
	पूर्ण अन्यथा अणु
		host->first_pending = scbp;
		host->last_pending = scbp;
	पूर्ण
पूर्ण

अटल काष्ठा scsi_ctrl_blk *initio_find_first_pend_scb(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *first;


	first = host->first_pending;
	जबतक (first != शून्य) अणु
		अगर (first->opcode != ExecSCSI)
			वापस first;
		अगर (first->tagmsg == 0) अणु
			अगर ((host->act_tags[first->target] == 0) &&
			    !(host->tarमाला_लो[first->target].flags & TCF_BUSY))
				वापस first;
		पूर्ण अन्यथा अणु
			अगर ((host->act_tags[first->target] >=
			  host->max_tags[first->target]) |
			    (host->tarमाला_लो[first->target].flags & TCF_BUSY)) अणु
				first = first->next;
				जारी;
			पूर्ण
			वापस first;
		पूर्ण
		first = first->next;
	पूर्ण
	वापस first;
पूर्ण

अटल व्योम initio_unlink_pend_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	काष्ठा scsi_ctrl_blk *पंचांगp, *prev;

#अगर DEBUG_QUEUE
	prपूर्णांकk("unlink pend SCB %p; ", scb);
#पूर्ण_अगर

	prev = पंचांगp = host->first_pending;
	जबतक (पंचांगp != शून्य) अणु
		अगर (scb == पंचांगp) अणु	/* Unlink this SCB              */
			अगर (पंचांगp == host->first_pending) अणु
				अगर ((host->first_pending = पंचांगp->next) == शून्य)
					host->last_pending = शून्य;
			पूर्ण अन्यथा अणु
				prev->next = पंचांगp->next;
				अगर (पंचांगp == host->last_pending)
					host->last_pending = prev;
			पूर्ण
			पंचांगp->next = शून्य;
			अवरोध;
		पूर्ण
		prev = पंचांगp;
		पंचांगp = पंचांगp->next;
	पूर्ण
पूर्ण

अटल व्योम initio_append_busy_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scbp)
अणु

#अगर DEBUG_QUEUE
	prपूर्णांकk("append busy SCB %p; ", scbp);
#पूर्ण_अगर
	अगर (scbp->tagmsg)
		host->act_tags[scbp->target]++;
	अन्यथा
		host->tarमाला_लो[scbp->target].flags |= TCF_BUSY;
	scbp->status = SCB_BUSY;
	scbp->next = शून्य;
	अगर (host->last_busy != शून्य) अणु
		host->last_busy->next = scbp;
		host->last_busy = scbp;
	पूर्ण अन्यथा अणु
		host->first_busy = scbp;
		host->last_busy = scbp;
	पूर्ण
पूर्ण

/***************************************************************************/
अटल काष्ठा scsi_ctrl_blk *initio_pop_busy_scb(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *पंचांगp;


	अगर ((पंचांगp = host->first_busy) != शून्य) अणु
		अगर ((host->first_busy = पंचांगp->next) == शून्य)
			host->last_busy = शून्य;
		पंचांगp->next = शून्य;
		अगर (पंचांगp->tagmsg)
			host->act_tags[पंचांगp->target]--;
		अन्यथा
			host->tarमाला_लो[पंचांगp->target].flags &= ~TCF_BUSY;
	पूर्ण
#अगर DEBUG_QUEUE
	prपूर्णांकk("Pop busy SCB %p; ", पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण

/***************************************************************************/
अटल व्योम initio_unlink_busy_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	काष्ठा scsi_ctrl_blk *पंचांगp, *prev;

#अगर DEBUG_QUEUE
	prपूर्णांकk("unlink busy SCB %p; ", scb);
#पूर्ण_अगर

	prev = पंचांगp = host->first_busy;
	जबतक (पंचांगp != शून्य) अणु
		अगर (scb == पंचांगp) अणु	/* Unlink this SCB              */
			अगर (पंचांगp == host->first_busy) अणु
				अगर ((host->first_busy = पंचांगp->next) == शून्य)
					host->last_busy = शून्य;
			पूर्ण अन्यथा अणु
				prev->next = पंचांगp->next;
				अगर (पंचांगp == host->last_busy)
					host->last_busy = prev;
			पूर्ण
			पंचांगp->next = शून्य;
			अगर (पंचांगp->tagmsg)
				host->act_tags[पंचांगp->target]--;
			अन्यथा
				host->tarमाला_लो[पंचांगp->target].flags &= ~TCF_BUSY;
			अवरोध;
		पूर्ण
		prev = पंचांगp;
		पंचांगp = पंचांगp->next;
	पूर्ण
	वापस;
पूर्ण

काष्ठा scsi_ctrl_blk *initio_find_busy_scb(काष्ठा initio_host * host, u16 tarlun)
अणु
	काष्ठा scsi_ctrl_blk *पंचांगp;
	u16 scbp_tarlun;


	पंचांगp = host->first_busy;
	जबतक (पंचांगp != शून्य) अणु
		scbp_tarlun = (पंचांगp->lun << 8) | (पंचांगp->target);
		अगर (scbp_tarlun == tarlun) अणु	/* Unlink this SCB              */
			अवरोध;
		पूर्ण
		पंचांगp = पंचांगp->next;
	पूर्ण
#अगर DEBUG_QUEUE
	prपूर्णांकk("find busy SCB %p; ", पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण

अटल व्योम initio_append_करोne_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scbp)
अणु
#अगर DEBUG_QUEUE
	prपूर्णांकk("append done SCB %p; ", scbp);
#पूर्ण_अगर

	scbp->status = SCB_DONE;
	scbp->next = शून्य;
	अगर (host->last_करोne != शून्य) अणु
		host->last_करोne->next = scbp;
		host->last_करोne = scbp;
	पूर्ण अन्यथा अणु
		host->first_करोne = scbp;
		host->last_करोne = scbp;
	पूर्ण
पूर्ण

काष्ठा scsi_ctrl_blk *initio_find_करोne_scb(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *पंचांगp;

	अगर ((पंचांगp = host->first_करोne) != शून्य) अणु
		अगर ((host->first_करोne = पंचांगp->next) == शून्य)
			host->last_करोne = शून्य;
		पंचांगp->next = शून्य;
	पूर्ण
#अगर DEBUG_QUEUE
	prपूर्णांकk("find done SCB %p; ",पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक initio_पात_srb(काष्ठा initio_host * host, काष्ठा scsi_cmnd *srbp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_ctrl_blk *पंचांगp, *prev;

	spin_lock_irqsave(&host->semaph_lock, flags);

	अगर ((host->semaph == 0) && (host->active == शून्य)) अणु
		/* disable Jयंत्रin SCSI Int        */
		outb(0x1F, host->addr + TUL_Mask);
		spin_unlock_irqrestore(&host->semaph_lock, flags);
		/* FIXME: synchronize_irq needed ? */
		tulip_मुख्य(host);
		spin_lock_irqsave(&host->semaph_lock, flags);
		host->semaph = 1;
		outb(0x0F, host->addr + TUL_Mask);
		spin_unlock_irqrestore(&host->semaph_lock, flags);
		वापस SCSI_ABORT_SNOOZE;
	पूर्ण
	prev = पंचांगp = host->first_pending;	/* Check Pend queue */
	जबतक (पंचांगp != शून्य) अणु
		/* 07/27/98 */
		अगर (पंचांगp->srb == srbp) अणु
			अगर (पंचांगp == host->active) अणु
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				वापस SCSI_ABORT_BUSY;
			पूर्ण अन्यथा अगर (पंचांगp == host->first_pending) अणु
				अगर ((host->first_pending = पंचांगp->next) == शून्य)
					host->last_pending = शून्य;
			पूर्ण अन्यथा अणु
				prev->next = पंचांगp->next;
				अगर (पंचांगp == host->last_pending)
					host->last_pending = prev;
			पूर्ण
			पंचांगp->hastat = HOST_ABORTED;
			पंचांगp->flags |= SCF_DONE;
			अगर (पंचांगp->flags & SCF_POST)
				(*पंचांगp->post) ((u8 *) host, (u8 *) पंचांगp);
			spin_unlock_irqrestore(&host->semaph_lock, flags);
			वापस SCSI_ABORT_SUCCESS;
		पूर्ण
		prev = पंचांगp;
		पंचांगp = पंचांगp->next;
	पूर्ण

	prev = पंचांगp = host->first_busy;	/* Check Busy queue */
	जबतक (पंचांगp != शून्य) अणु
		अगर (पंचांगp->srb == srbp) अणु
			अगर (पंचांगp == host->active) अणु
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				वापस SCSI_ABORT_BUSY;
			पूर्ण अन्यथा अगर (पंचांगp->tagmsg == 0) अणु
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				वापस SCSI_ABORT_BUSY;
			पूर्ण अन्यथा अणु
				host->act_tags[पंचांगp->target]--;
				अगर (पंचांगp == host->first_busy) अणु
					अगर ((host->first_busy = पंचांगp->next) == शून्य)
						host->last_busy = शून्य;
				पूर्ण अन्यथा अणु
					prev->next = पंचांगp->next;
					अगर (पंचांगp == host->last_busy)
						host->last_busy = prev;
				पूर्ण
				पंचांगp->next = शून्य;


				पंचांगp->hastat = HOST_ABORTED;
				पंचांगp->flags |= SCF_DONE;
				अगर (पंचांगp->flags & SCF_POST)
					(*पंचांगp->post) ((u8 *) host, (u8 *) पंचांगp);
				spin_unlock_irqrestore(&host->semaph_lock, flags);
				वापस SCSI_ABORT_SUCCESS;
			पूर्ण
		पूर्ण
		prev = पंचांगp;
		पंचांगp = पंचांगp->next;
	पूर्ण
	spin_unlock_irqrestore(&host->semaph_lock, flags);
	वापस SCSI_ABORT_NOT_RUNNING;
पूर्ण

/***************************************************************************/
अटल पूर्णांक initio_bad_seq(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;

	prपूर्णांकk("initio_bad_seg c=%d\n", host->index);

	अगर ((scb = host->active) != शून्य) अणु
		initio_unlink_busy_scb(host, scb);
		scb->hastat = HOST_BAD_PHAS;
		scb->tastat = 0;
		initio_append_करोne_scb(host, scb);
	पूर्ण
	initio_stop_bm(host);
	initio_reset_scsi(host, 8);	/* 7/29/98 */
	वापस initio_post_scsi_rst(host);
पूर्ण


/************************************************************************/
अटल व्योम initio_exec_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	अचिन्हित दीर्घ flags;

	scb->mode = 0;

	scb->sgidx = 0;
	scb->sgmax = scb->sglen;

	spin_lock_irqsave(&host->semaph_lock, flags);

	initio_append_pend_scb(host, scb);	/* Append this SCB to Pending queue */

/* VVVVV 07/21/98 */
	अगर (host->semaph == 1) अणु
		/* Disable Jयंत्रin SCSI Int */
		outb(0x1F, host->addr + TUL_Mask);
		host->semaph = 0;
		spin_unlock_irqrestore(&host->semaph_lock, flags);

		tulip_मुख्य(host);

		spin_lock_irqsave(&host->semaph_lock, flags);
		host->semaph = 1;
		outb(0x0F, host->addr + TUL_Mask);
	पूर्ण
	spin_unlock_irqrestore(&host->semaph_lock, flags);
	वापस;
पूर्ण

/***************************************************************************/
अटल पूर्णांक initio_isr(काष्ठा initio_host * host)
अणु
	अगर (inb(host->addr + TUL_Int) & TSS_INT_PENDING) अणु
		अगर (host->semaph == 1) अणु
			outb(0x1F, host->addr + TUL_Mask);
			/* Disable Tulip SCSI Int */
			host->semaph = 0;

			tulip_मुख्य(host);

			host->semaph = 1;
			outb(0x0F, host->addr + TUL_Mask);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tulip_मुख्य(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;

	क्रम (;;) अणु
		tulip_scsi(host);	/* Call tulip_scsi              */

		/* Walk the list of completed SCBs */
		जबतक ((scb = initio_find_करोne_scb(host)) != शून्य) अणु	/* find करोne entry */
			अगर (scb->tastat == INI_QUEUE_FULL) अणु
				host->max_tags[scb->target] =
				    host->act_tags[scb->target] - 1;
				scb->tastat = 0;
				initio_append_pend_scb(host, scb);
				जारी;
			पूर्ण
			अगर (!(scb->mode & SCM_RSENS)) अणु		/* not in स्वतः req. sense mode */
				अगर (scb->tastat == 2) अणु

					/* clr sync. nego flag */

					अगर (scb->flags & SCF_SENSE) अणु
						u8 len;
						len = scb->senselen;
						अगर (len == 0)
							len = 1;
						scb->buflen = scb->senselen;
						scb->bufptr = scb->senseptr;
						scb->flags &= ~(SCF_SG | SCF_सूची);	/* क्रम xfer_data_in */
						/* so, we won't report wrong direction in xfer_data_in,
						   and won't report HOST_DO_DU in state_6 */
						scb->mode = SCM_RSENS;
						scb->ident &= 0xBF;	/* Disable Disconnect */
						scb->tagmsg = 0;
						scb->tastat = 0;
						scb->cdblen = 6;
						scb->cdb[0] = SCSICMD_RequestSense;
						scb->cdb[1] = 0;
						scb->cdb[2] = 0;
						scb->cdb[3] = 0;
						scb->cdb[4] = len;
						scb->cdb[5] = 0;
						initio_push_pend_scb(host, scb);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु	/* in request sense mode */

				अगर (scb->tastat == 2) अणु		/* check contition status again after sending
									   requset sense cmd 0x3 */
					scb->hastat = HOST_BAD_PHAS;
				पूर्ण
				scb->tastat = 2;
			पूर्ण
			scb->flags |= SCF_DONE;
			अगर (scb->flags & SCF_POST) अणु
				/* FIXME: only one post method and lose casts */
				(*scb->post) ((u8 *) host, (u8 *) scb);
			पूर्ण
		पूर्ण		/* जबतक */
		/* find_active: */
		अगर (inb(host->addr + TUL_SStatus0) & TSS_INT_PENDING)
			जारी;
		अगर (host->active)	/* वापस to OS and रुको क्रम xfer_करोne_ISR/Selected_ISR */
			वापस 1;	/* वापस to OS, enable पूर्णांकerrupt */
		/* Check pending SCB            */
		अगर (initio_find_first_pend_scb(host) == शून्य)
			वापस 1;	/* वापस to OS, enable पूर्णांकerrupt */
	पूर्ण			/* End of क्रम loop */
	/* statement won't reach here */
पूर्ण

अटल व्योम tulip_scsi(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;
	काष्ठा target_control *active_tc;

	/* make sure to service पूर्णांकerrupt asap */
	अगर ((host->jsstatus0 = inb(host->addr + TUL_SStatus0)) & TSS_INT_PENDING) अणु
		host->phase = host->jsstatus0 & TSS_PH_MASK;
		host->jsstatus1 = inb(host->addr + TUL_SStatus1);
		host->jsपूर्णांक = inb(host->addr + TUL_SInt);
		अगर (host->jsपूर्णांक & TSS_SCSIRST_INT) अणु	/* SCSI bus reset detected      */
			पूर्णांक_initio_scsi_rst(host);
			वापस;
		पूर्ण
		अगर (host->jsपूर्णांक & TSS_RESEL_INT) अणु	/* अगर selected/reselected पूर्णांकerrupt */
			अगर (पूर्णांक_initio_resel(host) == 0)
				initio_next_state(host);
			वापस;
		पूर्ण
		अगर (host->jsपूर्णांक & TSS_SEL_TIMEOUT) अणु
			पूर्णांक_initio_busमुक्त(host);
			वापस;
		पूर्ण
		अगर (host->jsपूर्णांक & TSS_DISC_INT) अणु	/* BUS disconnection            */
			पूर्णांक_initio_busमुक्त(host);	/* unexpected bus मुक्त or sel समयout */
			वापस;
		पूर्ण
		अगर (host->jsपूर्णांक & (TSS_FUNC_COMP | TSS_BUS_SERV)) अणु	/* func complete or Bus service */
			अगर ((scb = host->active) != शून्य)
				initio_next_state(host);
			वापस;
		पूर्ण
	पूर्ण
	अगर (host->active != शून्य)
		वापस;

	अगर ((scb = initio_find_first_pend_scb(host)) == शून्य)
		वापस;

	/* program HBA's SCSI ID & target SCSI ID */
	outb((host->scsi_id << 4) | (scb->target & 0x0F),
		host->addr + TUL_SScsiId);
	अगर (scb->opcode == ExecSCSI) अणु
		active_tc = &host->tarमाला_लो[scb->target];

		अगर (scb->tagmsg)
			active_tc->drv_flags |= TCF_DRV_EN_TAG;
		अन्यथा
			active_tc->drv_flags &= ~TCF_DRV_EN_TAG;

		outb(active_tc->js_period, host->addr + TUL_SPeriod);
		अगर ((active_tc->flags & (TCF_WDTR_DONE | TCF_NO_WDTR)) == 0) अणु	/* करो wdtr negotiation          */
			initio_select_atn_stop(host, scb);
		पूर्ण अन्यथा अणु
			अगर ((active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0) अणु	/* करो sync negotiation          */
				initio_select_atn_stop(host, scb);
			पूर्ण अन्यथा अणु
				अगर (scb->tagmsg)
					initio_select_atn3(host, scb);
				अन्यथा
					initio_select_atn(host, scb);
			पूर्ण
		पूर्ण
		अगर (scb->flags & SCF_POLL) अणु
			जबतक (रुको_tulip(host) != -1) अणु
				अगर (initio_next_state(host) == -1)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (scb->opcode == BusDevRst) अणु
		initio_select_atn_stop(host, scb);
		scb->next_state = 8;
		अगर (scb->flags & SCF_POLL) अणु
			जबतक (रुको_tulip(host) != -1) अणु
				अगर (initio_next_state(host) == -1)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (scb->opcode == AbortCmd) अणु
		अगर (initio_पात_srb(host, scb->srb) != 0) अणु
			initio_unlink_pend_scb(host, scb);
			initio_release_scb(host, scb);
		पूर्ण अन्यथा अणु
			scb->opcode = BusDevRst;
			initio_select_atn_stop(host, scb);
			scb->next_state = 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		initio_unlink_pend_scb(host, scb);
		scb->hastat = 0x16;	/* bad command */
		initio_append_करोne_scb(host, scb);
	पूर्ण
	वापस;
पूर्ण

/**
 *	initio_next_state		-	Next SCSI state
 *	@host: InitIO host we are processing
 *
 *	Progress the active command block aदीर्घ the state machine
 *	until we hit a state which we must रुको क्रम activity to occur.
 *
 *	Returns zero or a negative code.
 */

अटल पूर्णांक initio_next_state(काष्ठा initio_host * host)
अणु
	पूर्णांक next;

	next = host->active->next_state;
	क्रम (;;) अणु
		चयन (next) अणु
		हाल 1:
			next = initio_state_1(host);
			अवरोध;
		हाल 2:
			next = initio_state_2(host);
			अवरोध;
		हाल 3:
			next = initio_state_3(host);
			अवरोध;
		हाल 4:
			next = initio_state_4(host);
			अवरोध;
		हाल 5:
			next = initio_state_5(host);
			अवरोध;
		हाल 6:
			next = initio_state_6(host);
			अवरोध;
		हाल 7:
			next = initio_state_7(host);
			अवरोध;
		हाल 8:
			वापस initio_bus_device_reset(host);
		शेष:
			वापस initio_bad_seq(host);
		पूर्ण
		अगर (next <= 0)
			वापस next;
	पूर्ण
पूर्ण


/**
 *	initio_state_1		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 *	Perक्रमm SCSI state processing क्रम Select/Attention/Stop
 */

अटल पूर्णांक initio_state_1(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;
#अगर DEBUG_STATE
	prपूर्णांकk("-s1-");
#पूर्ण_अगर

	/* Move the SCB from pending to busy */
	initio_unlink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addr + TUL_SConfig );
	/* ATN on */
	अगर (host->phase == MSG_OUT) अणु
		outb(TSC_EN_BUS_IN | TSC_HW_RESELECT, host->addr + TUL_SCtrl1);
		outb(scb->ident, host->addr + TUL_SFअगरo);

		अगर (scb->tagmsg) अणु
			outb(scb->tagmsg, host->addr + TUL_SFअगरo);
			outb(scb->tagid, host->addr + TUL_SFअगरo);
		पूर्ण
		अगर ((active_tc->flags & (TCF_WDTR_DONE | TCF_NO_WDTR)) == 0) अणु
			active_tc->flags |= TCF_WDTR_DONE;
			outb(EXTENDED_MESSAGE, host->addr + TUL_SFअगरo);
			outb(2, host->addr + TUL_SFअगरo);	/* Extended msg length */
			outb(EXTENDED_SDTR, host->addr + TUL_SFअगरo);	/* Sync request */
			outb(1, host->addr + TUL_SFअगरo);	/* Start from 16 bits */
		पूर्ण अन्यथा अगर ((active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0) अणु
			active_tc->flags |= TCF_SYNC_DONE;
			outb(EXTENDED_MESSAGE, host->addr + TUL_SFअगरo);
			outb(3, host->addr + TUL_SFअगरo);	/* extended msg length */
			outb(EXTENDED_SDTR, host->addr + TUL_SFअगरo);	/* sync request */
			outb(initio_rate_tbl[active_tc->flags & TCF_SCSI_RATE], host->addr + TUL_SFअगरo);
			outb(MAX_OFFSET, host->addr + TUL_SFअगरo);	/* REQ/ACK offset */
		पूर्ण
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;
	पूर्ण
	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
	outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)), host->addr + TUL_SSignal);
	/* Into beक्रमe CDB xfer */
	वापस 3;
पूर्ण


/**
 *	initio_state_2		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 * state after selection with attention
 * state after selection with attention3
 */

अटल पूर्णांक initio_state_2(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;
#अगर DEBUG_STATE
	prपूर्णांकk("-s2-");
#पूर्ण_अगर

	initio_unlink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addr + TUL_SConfig);

	अगर (host->jsstatus1 & TSS_CMD_PH_CMP)
		वापस 4;

	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
	outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)), host->addr + TUL_SSignal);
	/* Into beक्रमe CDB xfer */
	वापस 3;
पूर्ण

/**
 *	initio_state_3		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 * state beक्रमe CDB xfer is करोne
 */

अटल पूर्णांक initio_state_3(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;
	पूर्णांक i;

#अगर DEBUG_STATE
	prपूर्णांकk("-s3-");
#पूर्ण_अगर
	क्रम (;;) अणु
		चयन (host->phase) अणु
		हाल CMD_OUT:	/* Command out phase            */
			क्रम (i = 0; i < (पूर्णांक) scb->cdblen; i++)
				outb(scb->cdb[i], host->addr + TUL_SFअगरo);
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			अगर (रुको_tulip(host) == -1)
				वापस -1;
			अगर (host->phase == CMD_OUT)
				वापस initio_bad_seq(host);
			वापस 4;

		हाल MSG_IN:	/* Message in phase             */
			scb->next_state = 3;
			अगर (initio_msgin(host) == -1)
				वापस -1;
			अवरोध;

		हाल STATUS_IN:	/* Status phase                 */
			अगर (initio_status_msg(host) == -1)
				वापस -1;
			अवरोध;

		हाल MSG_OUT:	/* Message out phase            */
			अगर (active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) अणु
				outb(NOP, host->addr + TUL_SFअगरo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				अगर (रुको_tulip(host) == -1)
					वापस -1;
			पूर्ण अन्यथा अणु
				active_tc->flags |= TCF_SYNC_DONE;

				outb(EXTENDED_MESSAGE, host->addr + TUL_SFअगरo);
				outb(3, host->addr + TUL_SFअगरo);	/* ext. msg len */
				outb(EXTENDED_SDTR, host->addr + TUL_SFअगरo);	/* sync request */
				outb(initio_rate_tbl[active_tc->flags & TCF_SCSI_RATE], host->addr + TUL_SFअगरo);
				outb(MAX_OFFSET, host->addr + TUL_SFअगरo);	/* REQ/ACK offset */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				अगर (रुको_tulip(host) == -1)
					वापस -1;
				outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
				outb(inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7), host->addr + TUL_SSignal);

			पूर्ण
			अवरोध;
		शेष:
			वापस initio_bad_seq(host);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	initio_state_4		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 *	SCSI state machine. State 4
 */

अटल पूर्णांक initio_state_4(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;

#अगर DEBUG_STATE
	prपूर्णांकk("-s4-");
#पूर्ण_अगर
	अगर ((scb->flags & SCF_सूची) == SCF_NO_XF) अणु
		वापस 6;	/* Go to state 6 (After data) */
	पूर्ण
	क्रम (;;) अणु
		अगर (scb->buflen == 0)
			वापस 6;

		चयन (host->phase) अणु

		हाल STATUS_IN:	/* Status phase                 */
			अगर ((scb->flags & SCF_सूची) != 0)	/* अगर direction bit set then report data underrun */
				scb->hastat = HOST_DO_DU;
			अगर ((initio_status_msg(host)) == -1)
				वापस -1;
			अवरोध;

		हाल MSG_IN:	/* Message in phase             */
			scb->next_state = 0x4;
			अगर (initio_msgin(host) == -1)
				वापस -1;
			अवरोध;

		हाल MSG_OUT:	/* Message out phase            */
			अगर (host->jsstatus0 & TSS_PAR_ERROR) अणु
				scb->buflen = 0;
				scb->hastat = HOST_DO_DU;
				अगर (initio_msgout_ide(host) == -1)
					वापस -1;
				वापस 6;
			पूर्ण अन्यथा अणु
				outb(NOP, host->addr + TUL_SFअगरo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				अगर (रुको_tulip(host) == -1)
					वापस -1;
			पूर्ण
			अवरोध;

		हाल DATA_IN:	/* Data in phase                */
			वापस initio_xfer_data_in(host);

		हाल DATA_OUT:	/* Data out phase               */
			वापस initio_xfer_data_out(host);

		शेष:
			वापस initio_bad_seq(host);
		पूर्ण
	पूर्ण
पूर्ण


/**
 *	initio_state_5		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 *	State after dma xfer करोne or phase change beक्रमe xfer करोne
 */

अटल पूर्णांक initio_state_5(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	दीर्घ cnt, xcnt;		/* cannot use अचिन्हित !! code: अगर (xcnt < 0) */

#अगर DEBUG_STATE
	prपूर्णांकk("-s5-");
#पूर्ण_अगर
	/*------ get reमुख्यing count -------*/
	cnt = inl(host->addr + TUL_SCnt0) & 0x0FFFFFF;

	अगर (inb(host->addr + TUL_XCmd) & 0x20) अणु
		/* ----------------------- DATA_IN ----------------------------- */
		/* check scsi parity error */
		अगर (host->jsstatus0 & TSS_PAR_ERROR)
			scb->hastat = HOST_DO_DU;
		अगर (inb(host->addr + TUL_XStatus) & XPEND) अणु	/* DMA xfer pending, Send STOP  */
			/* tell Hardware  scsi xfer has been terminated */
			outb(inb(host->addr + TUL_XCtrl) | 0x80, host->addr + TUL_XCtrl);
			/* रुको until DMA xfer not pending */
			जबतक (inb(host->addr + TUL_XStatus) & XPEND)
				cpu_relax();
		पूर्ण
	पूर्ण अन्यथा अणु
		/*-------- DATA OUT -----------*/
		अगर ((inb(host->addr + TUL_SStatus1) & TSS_XFER_CMP) == 0) अणु
			अगर (host->active_tc->js_period & TSC_WIDE_SCSI)
				cnt += (inb(host->addr + TUL_SFअगरoCnt) & 0x1F) << 1;
			अन्यथा
				cnt += (inb(host->addr + TUL_SFअगरoCnt) & 0x1F);
		पूर्ण
		अगर (inb(host->addr + TUL_XStatus) & XPEND) अणु	/* अगर DMA xfer is pending, पात DMA xfer */
			outb(TAX_X_ABT, host->addr + TUL_XCmd);
			/* रुको Abort DMA xfer करोne */
			जबतक ((inb(host->addr + TUL_Int) & XABT) == 0)
				cpu_relax();
		पूर्ण
		अगर ((cnt == 1) && (host->phase == DATA_OUT)) अणु
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			अगर (रुको_tulip(host) == -1)
				वापस -1;
			cnt = 0;
		पूर्ण अन्यथा अणु
			अगर ((inb(host->addr + TUL_SStatus1) & TSS_XFER_CMP) == 0)
				outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
		पूर्ण
	पूर्ण
	अगर (cnt == 0) अणु
		scb->buflen = 0;
		वापस 6;	/* After Data */
	पूर्ण
	/* Update active data poपूर्णांकer */
	xcnt = (दीर्घ) scb->buflen - cnt;	/* xcnt== bytes alपढ़ोy xferred */
	scb->buflen = (u32) cnt;		/* cnt == bytes left to be xferred */
	अगर (scb->flags & SCF_SG) अणु
		काष्ठा sg_entry *sgp;
		अचिन्हित दीर्घ i;

		sgp = &scb->sglist[scb->sgidx];
		क्रम (i = scb->sgidx; i < scb->sgmax; sgp++, i++) अणु
			xcnt -= (दीर्घ) sgp->len;
			अगर (xcnt < 0) अणु		/* this sgp xfer half करोne */
				xcnt += (दीर्घ) sgp->len;	/* xcnt == bytes xferred in this sgp */
				sgp->data += (u32) xcnt;	/* new ptr to be xfer */
				sgp->len -= (u32) xcnt;	/* new len to be xfer */
				scb->bufptr += ((u32) (i - scb->sgidx) << 3);
				/* new SG table ptr */
				scb->sglen = (u8) (scb->sgmax - i);
				/* new SG table len */
				scb->sgidx = (u16) i;
				/* क्रम next disc and come in this loop */
				वापस 4;	/* Go to state 4                */
			पूर्ण
			/* अन्यथा (xcnt >= 0 , i.e. this sgp alपढ़ोy xferred */
		पूर्ण		/* क्रम */
		वापस 6;	/* Go to state 6                */
	पूर्ण अन्यथा अणु
		scb->bufptr += (u32) xcnt;
	पूर्ण
	वापस 4;		/* Go to state 4                */
पूर्ण

/**
 *	initio_state_6		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 *	State after Data phase
 */

अटल पूर्णांक initio_state_6(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;

#अगर DEBUG_STATE
	prपूर्णांकk("-s6-");
#पूर्ण_अगर
	क्रम (;;) अणु
		चयन (host->phase) अणु
		हाल STATUS_IN:	/* Status phase                 */
			अगर ((initio_status_msg(host)) == -1)
				वापस -1;
			अवरोध;

		हाल MSG_IN:	/* Message in phase             */
			scb->next_state = 6;
			अगर ((initio_msgin(host)) == -1)
				वापस -1;
			अवरोध;

		हाल MSG_OUT:	/* Message out phase            */
			outb(NOP, host->addr + TUL_SFअगरo);		/* msg nop */
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			अगर (रुको_tulip(host) == -1)
				वापस -1;
			अवरोध;

		हाल DATA_IN:	/* Data in phase                */
			वापस initio_xpad_in(host);

		हाल DATA_OUT:	/* Data out phase               */
			वापस initio_xpad_out(host);

		शेष:
			वापस initio_bad_seq(host);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	initio_state_7		-	SCSI state machine
 *	@host: InitIO host we are controlling
 *
 */

अटल पूर्णांक initio_state_7(काष्ठा initio_host * host)
अणु
	पूर्णांक cnt, i;

#अगर DEBUG_STATE
	prपूर्णांकk("-s7-");
#पूर्ण_अगर
	/* flush SCSI FIFO */
	cnt = inb(host->addr + TUL_SFअगरoCnt) & 0x1F;
	अगर (cnt) अणु
		क्रम (i = 0; i < cnt; i++)
			inb(host->addr + TUL_SFअगरo);
	पूर्ण
	चयन (host->phase) अणु
	हाल DATA_IN:		/* Data in phase                */
	हाल DATA_OUT:		/* Data out phase               */
		वापस initio_bad_seq(host);
	शेष:
		वापस 6;	/* Go to state 6                */
	पूर्ण
पूर्ण

/**
 *	initio_xfer_data_in	-	Commence data input
 *	@host: InitIO host in use
 *
 *	Commence a block of data transfer. The transfer itself will
 *	be managed by the controller and we will get a completion (or
 *	failure) पूर्णांकerrupt.
 */
अटल पूर्णांक initio_xfer_data_in(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;

	अगर ((scb->flags & SCF_सूची) == SCF_DOUT)
		वापस 6;	/* wrong direction */

	outl(scb->buflen, host->addr + TUL_SCnt0);
	outb(TSC_XF_DMA_IN, host->addr + TUL_SCmd);	/* 7/25/95 */

	अगर (scb->flags & SCF_SG) अणु	/* S/G xfer */
		outl(((u32) scb->sglen) << 3, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_SG_IN, host->addr + TUL_XCmd);
	पूर्ण अन्यथा अणु
		outl(scb->buflen, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_X_IN, host->addr + TUL_XCmd);
	पूर्ण
	scb->next_state = 0x5;
	वापस 0;		/* वापस to OS, रुको xfer करोne , let jas_isr come in */
पूर्ण

/**
 *	initio_xfer_data_out	-	Commence data output
 *	@host: InitIO host in use
 *
 *	Commence a block of data transfer. The transfer itself will
 *	be managed by the controller and we will get a completion (or
 *	failure) पूर्णांकerrupt.
 */

अटल पूर्णांक initio_xfer_data_out(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;

	अगर ((scb->flags & SCF_सूची) == SCF_DIN)
		वापस 6;	/* wrong direction */

	outl(scb->buflen, host->addr + TUL_SCnt0);
	outb(TSC_XF_DMA_OUT, host->addr + TUL_SCmd);

	अगर (scb->flags & SCF_SG) अणु	/* S/G xfer */
		outl(((u32) scb->sglen) << 3, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_SG_OUT, host->addr + TUL_XCmd);
	पूर्ण अन्यथा अणु
		outl(scb->buflen, host->addr + TUL_XCntH);
		outl(scb->bufptr, host->addr + TUL_XAddH);
		outb(TAX_X_OUT, host->addr + TUL_XCmd);
	पूर्ण

	scb->next_state = 0x5;
	वापस 0;		/* वापस to OS, रुको xfer करोne , let jas_isr come in */
पूर्ण

पूर्णांक initio_xpad_in(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;

	अगर ((scb->flags & SCF_सूची) != SCF_NO_DCHK)
		scb->hastat = HOST_DO_DU;	/* over run             */
	क्रम (;;) अणु
		अगर (active_tc->js_period & TSC_WIDE_SCSI)
			outl(2, host->addr + TUL_SCnt0);
		अन्यथा
			outl(1, host->addr + TUL_SCnt0);

		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;
		अगर (host->phase != DATA_IN) अणु
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			वापस 6;
		पूर्ण
		inb(host->addr + TUL_SFअगरo);
	पूर्ण
पूर्ण

पूर्णांक initio_xpad_out(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;

	अगर ((scb->flags & SCF_सूची) != SCF_NO_DCHK)
		scb->hastat = HOST_DO_DU;	/* over run             */
	क्रम (;;) अणु
		अगर (active_tc->js_period & TSC_WIDE_SCSI)
			outl(2, host->addr + TUL_SCnt0);
		अन्यथा
			outl(1, host->addr + TUL_SCnt0);

		outb(0, host->addr + TUL_SFअगरo);
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		अगर ((रुको_tulip(host)) == -1)
			वापस -1;
		अगर (host->phase != DATA_OUT) अणु	/* Disable wide CPU to allow पढ़ो 16 bits */
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			वापस 6;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक initio_status_msg(काष्ठा initio_host * host)
अणु				/* status & MSG_IN */
	काष्ठा scsi_ctrl_blk *scb = host->active;
	u8 msg;

	outb(TSC_CMD_COMP, host->addr + TUL_SCmd);
	अगर (रुको_tulip(host) == -1)
		वापस -1;

	/* get status */
	scb->tastat = inb(host->addr + TUL_SFअगरo);

	अगर (host->phase == MSG_OUT) अणु
		अगर (host->jsstatus0 & TSS_PAR_ERROR)
			outb(MSG_PARITY_ERROR, host->addr + TUL_SFअगरo);
		अन्यथा
			outb(NOP, host->addr + TUL_SFअगरo);
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		वापस रुको_tulip(host);
	पूर्ण
	अगर (host->phase == MSG_IN) अणु
		msg = inb(host->addr + TUL_SFअगरo);
		अगर (host->jsstatus0 & TSS_PAR_ERROR) अणु	/* Parity error                 */
			अगर ((initio_msgin_accept(host)) == -1)
				वापस -1;
			अगर (host->phase != MSG_OUT)
				वापस initio_bad_seq(host);
			outb(MSG_PARITY_ERROR, host->addr + TUL_SFअगरo);
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			वापस रुको_tulip(host);
		पूर्ण
		अगर (msg == 0) अणु	/* Command complete             */

			अगर ((scb->tastat & 0x18) == 0x10)	/* No link support              */
				वापस initio_bad_seq(host);
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
			वापस initio_रुको_करोne_disc(host);

		पूर्ण
		अगर (msg == LINKED_CMD_COMPLETE ||
		    msg == LINKED_FLG_CMD_COMPLETE) अणु
			अगर ((scb->tastat & 0x18) == 0x10)
				वापस initio_msgin_accept(host);
		पूर्ण
	पूर्ण
	वापस initio_bad_seq(host);
पूर्ण


/* scsi bus मुक्त */
पूर्णांक पूर्णांक_initio_busमुक्त(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;

	अगर (scb != शून्य) अणु
		अगर (scb->status & SCB_SELECT) अणु		/* selection समयout */
			initio_unlink_pend_scb(host, scb);
			scb->hastat = HOST_SEL_TOUT;
			initio_append_करोne_scb(host, scb);
		पूर्ण अन्यथा अणु	/* Unexpected bus मुक्त          */
			initio_unlink_busy_scb(host, scb);
			scb->hastat = HOST_BUS_FREE;
			initio_append_करोne_scb(host, scb);
		पूर्ण
		host->active = शून्य;
		host->active_tc = शून्य;
	पूर्ण
	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);		/* Flush SCSI FIFO  */
	outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
	outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect       */
	वापस -1;
पूर्ण


/**
 *	पूर्णांक_initio_scsi_rst	-	SCSI reset occurred
 *	@host: Host seeing the reset
 *
 *	A SCSI bus reset has occurred. Clean up any pending transfer
 *	the hardware is करोing by DMA and then पात all active and
 *	disconnected commands. The mid layer should sort the rest out
 *	क्रम us
 */

अटल पूर्णांक पूर्णांक_initio_scsi_rst(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;
	पूर्णांक i;

	/* अगर DMA xfer is pending, पात DMA xfer */
	अगर (inb(host->addr + TUL_XStatus) & 0x01) अणु
		outb(TAX_X_ABT | TAX_X_CLR_FIFO, host->addr + TUL_XCmd);
		/* रुको Abort DMA xfer करोne */
		जबतक ((inb(host->addr + TUL_Int) & 0x04) == 0)
			cpu_relax();
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
	पूर्ण
	/* Abort all active & disconnected scb */
	जबतक ((scb = initio_pop_busy_scb(host)) != शून्य) अणु
		scb->hastat = HOST_BAD_PHAS;
		initio_append_करोne_scb(host, scb);
	पूर्ण
	host->active = शून्य;
	host->active_tc = शून्य;

	/* clr sync nego. करोne flag */
	क्रम (i = 0; i < host->max_tar; i++)
		host->tarमाला_लो[i].flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE);
	वापस -1;
पूर्ण

/**
 *	पूर्णांक_initio_resel	-	Reselection occurred
 *	@host: InitIO host adapter
 *
 *	A SCSI reselection event has been संकेतled and the पूर्णांकerrupt
 *	is now being processed. Work out which command block needs attention
 *	and जारी processing that command.
 */

पूर्णांक पूर्णांक_initio_resel(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;
	काष्ठा target_control *active_tc;
	u8 tag, msg = 0;
	u8 tar, lun;

	अगर ((scb = host->active) != शून्य) अणु
		/* FIXME: Why check and not just clear ? */
		अगर (scb->status & SCB_SELECT)		/* अगर रुकोing क्रम selection complete */
			scb->status &= ~SCB_SELECT;
		host->active = शून्य;
	पूर्ण
	/* --------- get target id---------------------- */
	tar = inb(host->addr + TUL_SBusId);
	/* ------ get LUN from Identअगरy message----------- */
	lun = inb(host->addr + TUL_SIdent) & 0x0F;
	/* 07/22/98 from 0x1F -> 0x0F */
	active_tc = &host->tarमाला_लो[tar];
	host->active_tc = active_tc;
	outb(active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(active_tc->js_period, host->addr + TUL_SPeriod);

	/* ------------- tag queueing ? ------------------- */
	अगर (active_tc->drv_flags & TCF_DRV_EN_TAG) अणु
		अगर ((initio_msgin_accept(host)) == -1)
			वापस -1;
		अगर (host->phase != MSG_IN)
			जाओ no_tag;
		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;
		msg = inb(host->addr + TUL_SFअगरo);	/* Read Tag Message    */

		अगर (msg < SIMPLE_QUEUE_TAG || msg > ORDERED_QUEUE_TAG)
			/* Is simple Tag      */
			जाओ no_tag;

		अगर (initio_msgin_accept(host) == -1)
			वापस -1;

		अगर (host->phase != MSG_IN)
			जाओ no_tag;

		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;
		tag = inb(host->addr + TUL_SFअगरo);	/* Read Tag ID       */
		scb = host->scb + tag;
		अगर (scb->target != tar || scb->lun != lun) अणु
			वापस initio_msgout_पात_tag(host);
		पूर्ण
		अगर (scb->status != SCB_BUSY) अणु	/* 03/24/95             */
			वापस initio_msgout_पात_tag(host);
		पूर्ण
		host->active = scb;
		अगर ((initio_msgin_accept(host)) == -1)
			वापस -1;
	पूर्ण अन्यथा अणु		/* No tag               */
	      no_tag:
		अगर ((scb = initio_find_busy_scb(host, tar | (lun << 8))) == शून्य) अणु
			वापस initio_msgout_पात_targ(host);
		पूर्ण
		host->active = scb;
		अगर (!(active_tc->drv_flags & TCF_DRV_EN_TAG)) अणु
			अगर ((initio_msgin_accept(host)) == -1)
				वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	पूर्णांक_initio_bad_seq		-	out of phase
 *	@host: InitIO host flagging event
 *
 *	We have ended up out of phase somehow. Reset the host controller
 *	and throw all our toys out of the pram. Let the midlayer clean up
 */

अटल पूर्णांक पूर्णांक_initio_bad_seq(काष्ठा initio_host * host)
अणु				/* target wrong phase           */
	काष्ठा scsi_ctrl_blk *scb;
	पूर्णांक i;

	initio_reset_scsi(host, 10);

	जबतक ((scb = initio_pop_busy_scb(host)) != शून्य) अणु
		scb->hastat = HOST_BAD_PHAS;
		initio_append_करोne_scb(host, scb);
	पूर्ण
	क्रम (i = 0; i < host->max_tar; i++)
		host->tarमाला_लो[i].flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE);
	वापस -1;
पूर्ण


/**
 *	initio_msgout_पात_targ		-	पात a tag
 *	@host: InitIO host
 *
 *	Abort when the target/lun करोes not match or when our SCB is not
 *	busy. Used by untagged commands.
 */

अटल पूर्णांक initio_msgout_पात_targ(काष्ठा initio_host * host)
अणु

	outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);
	अगर (initio_msgin_accept(host) == -1)
		वापस -1;
	अगर (host->phase != MSG_OUT)
		वापस initio_bad_seq(host);

	outb(ABORT_TASK_SET, host->addr + TUL_SFअगरo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);

	वापस initio_रुको_disc(host);
पूर्ण

/**
 *	initio_msgout_पात_tag		-	पात a tag
 *	@host: InitIO host
 *
 *	Abort when the target/lun करोes not match or when our SCB is not
 *	busy. Used क्रम tagged commands.
 */

अटल पूर्णांक initio_msgout_पात_tag(काष्ठा initio_host * host)
अणु

	outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);
	अगर (initio_msgin_accept(host) == -1)
		वापस -1;
	अगर (host->phase != MSG_OUT)
		वापस initio_bad_seq(host);

	outb(ABORT_TASK, host->addr + TUL_SFअगरo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);

	वापस initio_रुको_disc(host);

पूर्ण

/**
 *	initio_msgin		-	Message in
 *	@host: InitIO Host
 *
 *	Process incoming message
 */
अटल पूर्णांक initio_msgin(काष्ठा initio_host * host)
अणु
	काष्ठा target_control *active_tc;

	क्रम (;;) अणु
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);

		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;

		चयन (inb(host->addr + TUL_SFअगरo)) अणु
		हाल DISCONNECT:	/* Disconnect msg */
			outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
			वापस initio_रुको_disc(host);
		हाल SAVE_POINTERS:
		हाल RESTORE_POINTERS:
		हाल NOP:
			initio_msgin_accept(host);
			अवरोध;
		हाल MESSAGE_REJECT:	/* Clear ATN first              */
			outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)),
				host->addr + TUL_SSignal);
			active_tc = host->active_tc;
			अगर ((active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0)	/* करो sync nego */
				outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN),
					host->addr + TUL_SSignal);
			initio_msgin_accept(host);
			अवरोध;
		हाल EXTENDED_MESSAGE:	/* extended msg */
			initio_msgin_extend(host);
			अवरोध;
		हाल IGNORE_WIDE_RESIDUE:
			initio_msgin_accept(host);
			अवरोध;
		हाल COMMAND_COMPLETE:
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
			वापस initio_रुको_करोne_disc(host);
		शेष:
			initio_msgout_reject(host);
			अवरोध;
		पूर्ण
		अगर (host->phase != MSG_IN)
			वापस host->phase;
	पूर्ण
	/* statement won't reach here */
पूर्ण

अटल पूर्णांक initio_msgout_reject(काष्ठा initio_host * host)
अणु
	outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);

	अगर (initio_msgin_accept(host) == -1)
		वापस -1;

	अगर (host->phase == MSG_OUT) अणु
		outb(MESSAGE_REJECT, host->addr + TUL_SFअगरo);		/* Msg reject           */
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		वापस रुको_tulip(host);
	पूर्ण
	वापस host->phase;
पूर्ण

अटल पूर्णांक initio_msgout_ide(काष्ठा initio_host * host)
अणु
	outb(INITIATOR_ERROR, host->addr + TUL_SFअगरo);		/* Initiator Detected Error */
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
	वापस रुको_tulip(host);
पूर्ण

अटल पूर्णांक initio_msgin_extend(काष्ठा initio_host * host)
अणु
	u8 len, idx;

	अगर (initio_msgin_accept(host) != MSG_IN)
		वापस host->phase;

	/* Get extended msg length      */
	outl(1, host->addr + TUL_SCnt0);
	outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
	अगर (रुको_tulip(host) == -1)
		वापस -1;

	len = inb(host->addr + TUL_SFअगरo);
	host->msg[0] = len;
	क्रम (idx = 1; len != 0; len--) अणु

		अगर ((initio_msgin_accept(host)) != MSG_IN)
			वापस host->phase;
		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		अगर (रुको_tulip(host) == -1)
			वापस -1;
		host->msg[idx++] = inb(host->addr + TUL_SFअगरo);
	पूर्ण
	अगर (host->msg[1] == 1) अणु		/* अगर it's synchronous data transfer request */
		u8 r;
		अगर (host->msg[0] != 3)	/* अगर length is not right */
			वापस initio_msgout_reject(host);
		अगर (host->active_tc->flags & TCF_NO_SYNC_NEGO) अणु	/* Set OFFSET=0 to करो async, nego back */
			host->msg[3] = 0;
		पूर्ण अन्यथा अणु
			अगर (initio_msgin_sync(host) == 0 &&
			    (host->active_tc->flags & TCF_SYNC_DONE)) अणु
				initio_sync_करोne(host);
				वापस initio_msgin_accept(host);
			पूर्ण
		पूर्ण

		r = inb(host->addr + TUL_SSignal);
		outb((r & (TSC_SET_ACK | 7)) | TSC_SET_ATN,
			host->addr + TUL_SSignal);
		अगर (initio_msgin_accept(host) != MSG_OUT)
			वापस host->phase;
		/* sync msg out */
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);

		initio_sync_करोne(host);

		outb(EXTENDED_MESSAGE, host->addr + TUL_SFअगरo);
		outb(3, host->addr + TUL_SFअगरo);
		outb(EXTENDED_SDTR, host->addr + TUL_SFअगरo);
		outb(host->msg[2], host->addr + TUL_SFअगरo);
		outb(host->msg[3], host->addr + TUL_SFअगरo);
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		वापस रुको_tulip(host);
	पूर्ण
	अगर (host->msg[0] != 2 || host->msg[1] != 3)
		वापस initio_msgout_reject(host);
	/* अगर it's WIDE DATA XFER REQ   */
	अगर (host->active_tc->flags & TCF_NO_WDTR) अणु
		host->msg[2] = 0;
	पूर्ण अन्यथा अणु
		अगर (host->msg[2] > 2)	/* > 32 bits            */
			वापस initio_msgout_reject(host);
		अगर (host->msg[2] == 2) अणु		/* == 32                */
			host->msg[2] = 1;
		पूर्ण अन्यथा अणु
			अगर ((host->active_tc->flags & TCF_NO_WDTR) == 0) अणु
				wdtr_करोne(host);
				अगर ((host->active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0)
					outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);
				वापस initio_msgin_accept(host);
			पूर्ण
		पूर्ण
	पूर्ण
	outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addr + TUL_SSignal);

	अगर (initio_msgin_accept(host) != MSG_OUT)
		वापस host->phase;
	/* WDTR msg out                 */
	outb(EXTENDED_MESSAGE, host->addr + TUL_SFअगरo);
	outb(2, host->addr + TUL_SFअगरo);
	outb(EXTENDED_WDTR, host->addr + TUL_SFअगरo);
	outb(host->msg[2], host->addr + TUL_SFअगरo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
	वापस रुको_tulip(host);
पूर्ण

अटल पूर्णांक initio_msgin_sync(काष्ठा initio_host * host)
अणु
	अक्षर शेष_period;

	शेष_period = initio_rate_tbl[host->active_tc->flags & TCF_SCSI_RATE];
	अगर (host->msg[3] > MAX_OFFSET) अणु
		host->msg[3] = MAX_OFFSET;
		अगर (host->msg[2] < शेष_period) अणु
			host->msg[2] = शेष_period;
			वापस 1;
		पूर्ण
		अगर (host->msg[2] >= 59)	/* Change to async              */
			host->msg[3] = 0;
		वापस 1;
	पूर्ण
	/* offset requests asynchronous transfers ? */
	अगर (host->msg[3] == 0) अणु
		वापस 0;
	पूर्ण
	अगर (host->msg[2] < शेष_period) अणु
		host->msg[2] = शेष_period;
		वापस 1;
	पूर्ण
	अगर (host->msg[2] >= 59) अणु
		host->msg[3] = 0;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wdtr_करोne(काष्ठा initio_host * host)
अणु
	host->active_tc->flags &= ~TCF_SYNC_DONE;
	host->active_tc->flags |= TCF_WDTR_DONE;

	host->active_tc->js_period = 0;
	अगर (host->msg[2])	/* अगर 16 bit */
		host->active_tc->js_period |= TSC_WIDE_SCSI;
	host->active_tc->sconfig0 &= ~TSC_ALT_PERIOD;
	outb(host->active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(host->active_tc->js_period, host->addr + TUL_SPeriod);

	वापस 1;
पूर्ण

अटल पूर्णांक initio_sync_करोne(काष्ठा initio_host * host)
अणु
	पूर्णांक i;

	host->active_tc->flags |= TCF_SYNC_DONE;

	अगर (host->msg[3]) अणु
		host->active_tc->js_period |= host->msg[3];
		क्रम (i = 0; i < 8; i++) अणु
			अगर (initio_rate_tbl[i] >= host->msg[2])	/* pick the big one */
				अवरोध;
		पूर्ण
		host->active_tc->js_period |= (i << 4);
		host->active_tc->sconfig0 |= TSC_ALT_PERIOD;
	पूर्ण
	outb(host->active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(host->active_tc->js_period, host->addr + TUL_SPeriod);

	वापस -1;
पूर्ण


अटल पूर्णांक initio_post_scsi_rst(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb;
	काष्ठा target_control *active_tc;
	पूर्णांक i;

	host->active = शून्य;
	host->active_tc = शून्य;
	host->flags = 0;

	जबतक ((scb = initio_pop_busy_scb(host)) != शून्य) अणु
		scb->hastat = HOST_BAD_PHAS;
		initio_append_करोne_scb(host, scb);
	पूर्ण
	/* clear sync करोne flag         */
	active_tc = &host->tarमाला_लो[0];
	क्रम (i = 0; i < host->max_tar; active_tc++, i++) अणु
		active_tc->flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE);
		/* Initialize the sync. xfer रेजिस्टर values to an asyn xfer */
		active_tc->js_period = 0;
		active_tc->sconfig0 = host->sconf1;
		host->act_tags[0] = 0;	/* 07/22/98 */
		host->tarमाला_लो[i].flags &= ~TCF_BUSY;	/* 07/22/98 */
	पूर्ण			/* क्रम */

	वापस -1;
पूर्ण

अटल व्योम initio_select_atn_stop(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	scb->status |= SCB_SELECT;
	scb->next_state = 0x1;
	host->active = scb;
	host->active_tc = &host->tarमाला_लो[scb->target];
	outb(TSC_SELATNSTOP, host->addr + TUL_SCmd);
पूर्ण


अटल व्योम initio_select_atn(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	पूर्णांक i;

	scb->status |= SCB_SELECT;
	scb->next_state = 0x2;

	outb(scb->ident, host->addr + TUL_SFअगरo);
	क्रम (i = 0; i < (पूर्णांक) scb->cdblen; i++)
		outb(scb->cdb[i], host->addr + TUL_SFअगरo);
	host->active_tc = &host->tarमाला_लो[scb->target];
	host->active = scb;
	outb(TSC_SEL_ATN, host->addr + TUL_SCmd);
पूर्ण

अटल व्योम initio_select_atn3(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * scb)
अणु
	पूर्णांक i;

	scb->status |= SCB_SELECT;
	scb->next_state = 0x2;

	outb(scb->ident, host->addr + TUL_SFअगरo);
	outb(scb->tagmsg, host->addr + TUL_SFअगरo);
	outb(scb->tagid, host->addr + TUL_SFअगरo);
	क्रम (i = 0; i < scb->cdblen; i++)
		outb(scb->cdb[i], host->addr + TUL_SFअगरo);
	host->active_tc = &host->tarमाला_लो[scb->target];
	host->active = scb;
	outb(TSC_SEL_ATN3, host->addr + TUL_SCmd);
पूर्ण

/**
 *	initio_bus_device_reset	-	 SCSI Bus Device Reset
 *	@host: InitIO host to reset
 *
 *	Perक्रमm a device reset and पात all pending SCBs क्रम the
 *	victim device
 */
पूर्णांक initio_bus_device_reset(काष्ठा initio_host * host)
अणु
	काष्ठा scsi_ctrl_blk *scb = host->active;
	काष्ठा target_control *active_tc = host->active_tc;
	काष्ठा scsi_ctrl_blk *पंचांगp, *prev;
	u8 tar;

	अगर (host->phase != MSG_OUT)
		वापस पूर्णांक_initio_bad_seq(host);	/* Unexpected phase */

	initio_unlink_pend_scb(host, scb);
	initio_release_scb(host, scb);


	tar = scb->target;	/* target                       */
	active_tc->flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE | TCF_BUSY);
	/* clr sync. nego & WDTR flags  07/22/98 */

	/* पात all SCB with same target */
	prev = पंचांगp = host->first_busy;	/* Check Busy queue */
	जबतक (पंचांगp != शून्य) अणु
		अगर (पंचांगp->target == tar) अणु
			/* unlink it */
			अगर (पंचांगp == host->first_busy) अणु
				अगर ((host->first_busy = पंचांगp->next) == शून्य)
					host->last_busy = शून्य;
			पूर्ण अन्यथा अणु
				prev->next = पंचांगp->next;
				अगर (पंचांगp == host->last_busy)
					host->last_busy = prev;
			पूर्ण
			पंचांगp->hastat = HOST_ABORTED;
			initio_append_करोne_scb(host, पंचांगp);
		पूर्ण
		/* Previous haven't change      */
		अन्यथा अणु
			prev = पंचांगp;
		पूर्ण
		पंचांगp = पंचांगp->next;
	पूर्ण
	outb(TARGET_RESET, host->addr + TUL_SFअगरo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
	वापस initio_रुको_disc(host);

पूर्ण

अटल पूर्णांक initio_msgin_accept(काष्ठा initio_host * host)
अणु
	outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
	वापस रुको_tulip(host);
पूर्ण

अटल पूर्णांक रुको_tulip(काष्ठा initio_host * host)
अणु

	जबतक (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0))
		 & TSS_INT_PENDING))
			cpu_relax();

	host->jsपूर्णांक = inb(host->addr + TUL_SInt);
	host->phase = host->jsstatus0 & TSS_PH_MASK;
	host->jsstatus1 = inb(host->addr + TUL_SStatus1);

	अगर (host->jsपूर्णांक & TSS_RESEL_INT)	/* अगर SCSI bus reset detected */
		वापस पूर्णांक_initio_resel(host);
	अगर (host->jsपूर्णांक & TSS_SEL_TIMEOUT)	/* अगर selected/reselected समयout पूर्णांकerrupt */
		वापस पूर्णांक_initio_busमुक्त(host);
	अगर (host->jsपूर्णांक & TSS_SCSIRST_INT)	/* अगर SCSI bus reset detected   */
		वापस पूर्णांक_initio_scsi_rst(host);

	अगर (host->jsपूर्णांक & TSS_DISC_INT) अणु	/* BUS disconnection            */
		अगर (host->flags & HCF_EXPECT_DONE_DISC) अणु
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
			initio_unlink_busy_scb(host, host->active);
			host->active->hastat = 0;
			initio_append_करोne_scb(host, host->active);
			host->active = शून्य;
			host->active_tc = शून्य;
			host->flags &= ~HCF_EXPECT_DONE_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
			वापस -1;
		पूर्ण
		अगर (host->flags & HCF_EXPECT_DISC) अणु
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
			host->active = शून्य;
			host->active_tc = शून्य;
			host->flags &= ~HCF_EXPECT_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
			वापस -1;
		पूर्ण
		वापस पूर्णांक_initio_busमुक्त(host);
	पूर्ण
	/* The old code really करोes the below. Can probably be हटाओd */
	अगर (host->jsपूर्णांक & (TSS_FUNC_COMP | TSS_BUS_SERV))
		वापस host->phase;
	वापस host->phase;
पूर्ण

अटल पूर्णांक initio_रुको_disc(काष्ठा initio_host * host)
अणु
	जबतक (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0)) & TSS_INT_PENDING))
		cpu_relax();

	host->jsपूर्णांक = inb(host->addr + TUL_SInt);

	अगर (host->jsपूर्णांक & TSS_SCSIRST_INT)	/* अगर SCSI bus reset detected */
		वापस पूर्णांक_initio_scsi_rst(host);
	अगर (host->jsपूर्णांक & TSS_DISC_INT) अणु	/* BUS disconnection */
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
		outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
		outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
		host->active = शून्य;
		वापस -1;
	पूर्ण
	वापस initio_bad_seq(host);
पूर्ण

अटल पूर्णांक initio_रुको_करोne_disc(काष्ठा initio_host * host)
अणु
	जबतक (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0))
		 & TSS_INT_PENDING))
		 cpu_relax();

	host->jsपूर्णांक = inb(host->addr + TUL_SInt);

	अगर (host->jsपूर्णांक & TSS_SCSIRST_INT)	/* अगर SCSI bus reset detected */
		वापस पूर्णांक_initio_scsi_rst(host);
	अगर (host->jsपूर्णांक & TSS_DISC_INT) अणु	/* BUS disconnection */
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);		/* Flush SCSI FIFO */
		outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
		outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);		/* Enable HW reselect */
		initio_unlink_busy_scb(host, host->active);

		initio_append_करोne_scb(host, host->active);
		host->active = शून्य;
		वापस -1;
	पूर्ण
	वापस initio_bad_seq(host);
पूर्ण

/**
 *	i91u_पूर्णांकr		-	IRQ handler
 *	@irqno: IRQ number
 *	@dev_id: IRQ identअगरier
 *
 *	Take the relevant locks and then invoke the actual isr processing
 *	code under the lock.
 */

अटल irqवापस_t i91u_पूर्णांकr(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *dev = dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;
	
	spin_lock_irqsave(dev->host_lock, flags);
	r = initio_isr((काष्ठा initio_host *)dev->hostdata);
	spin_unlock_irqrestore(dev->host_lock, flags);
	अगर (r)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण


/**
 *	initio_build_scb		-	Build the mappings and SCB
 *	@host: InitIO host taking the command
 *	@cblk: Firmware command block
 *	@cmnd: SCSI midlayer command block
 *
 *	Translate the असलtract SCSI command पूर्णांकo a firmware command block
 *	suitable क्रम feeding to the InitIO host controller. This also requires
 *	we build the scatter gather lists and ensure they are mapped properly.
 */

अटल व्योम initio_build_scb(काष्ठा initio_host * host, काष्ठा scsi_ctrl_blk * cblk, काष्ठा scsi_cmnd * cmnd)
अणु				/* Create corresponding SCB     */
	काष्ठा scatterlist *sglist;
	काष्ठा sg_entry *sg;		/* Poपूर्णांकer to SG list           */
	पूर्णांक i, nseg;
	दीर्घ total_len;
	dma_addr_t dma_addr;

	/* Fill in the command headers */
	cblk->post = i91uSCBPost;	/* i91u's callback routine      */
	cblk->srb = cmnd;
	cblk->opcode = ExecSCSI;
	cblk->flags = SCF_POST;	/* After SCSI करोne, call post routine */
	cblk->target = cmnd->device->id;
	cblk->lun = cmnd->device->lun;
	cblk->ident = cmnd->device->lun | DISC_ALLOW;

	cblk->flags |= SCF_SENSE;	/* Turn on स्वतः request sense   */

	/* Map the sense buffer पूर्णांकo bus memory */
	dma_addr = dma_map_single(&host->pci_dev->dev, cmnd->sense_buffer,
				  SENSE_SIZE, DMA_FROM_DEVICE);
	cblk->senseptr = (u32)dma_addr;
	cblk->senselen = SENSE_SIZE;
	cmnd->SCp.ptr = (अक्षर *)(अचिन्हित दीर्घ)dma_addr;
	cblk->cdblen = cmnd->cmd_len;

	/* Clear the वापसed status */
	cblk->hastat = 0;
	cblk->tastat = 0;
	/* Command the command */
	स_नकल(cblk->cdb, cmnd->cmnd, cmnd->cmd_len);

	/* Set up tags */
	अगर (cmnd->device->tagged_supported) अणु	/* Tag Support                  */
		cblk->tagmsg = SIMPLE_QUEUE_TAG;	/* Do simple tag only   */
	पूर्ण अन्यथा अणु
		cblk->tagmsg = 0;	/* No tag support               */
	पूर्ण

	/* toकरो handle map_sg error */
	nseg = scsi_dma_map(cmnd);
	BUG_ON(nseg < 0);
	अगर (nseg) अणु
		dma_addr = dma_map_single(&host->pci_dev->dev, &cblk->sglist[0],
					  माप(काष्ठा sg_entry) * TOTAL_SG_ENTRY,
					  DMA_BIसूचीECTIONAL);
		cblk->bufptr = (u32)dma_addr;
		cmnd->SCp.dma_handle = dma_addr;

		cblk->sglen = nseg;

		cblk->flags |= SCF_SG;	/* Turn on SG list flag       */
		total_len = 0;
		sg = &cblk->sglist[0];
		scsi_क्रम_each_sg(cmnd, sglist, cblk->sglen, i) अणु
			sg->data = cpu_to_le32((u32)sg_dma_address(sglist));
			sg->len = cpu_to_le32((u32)sg_dma_len(sglist));
			total_len += sg_dma_len(sglist);
			++sg;
		पूर्ण

		cblk->buflen = (scsi_bufflen(cmnd) > total_len) ?
			total_len : scsi_bufflen(cmnd);
	पूर्ण अन्यथा अणु	/* No data transfer required */
		cblk->buflen = 0;
		cblk->sglen = 0;
	पूर्ण
पूर्ण

/**
 *	i91u_queuecommand_lck	-	Queue a new command अगर possible
 *	@cmd: SCSI command block from the mid layer
 *	@करोne: Completion handler
 *
 *	Attempts to queue a new command with the host adapter. Will वापस
 *	zero अगर successful or indicate a host busy condition अगर not (which
 *	will cause the mid layer to call us again later with the command)
 */

अटल पूर्णांक i91u_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
		व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा initio_host *host = (काष्ठा initio_host *) cmd->device->host->hostdata;
	काष्ठा scsi_ctrl_blk *cmnd;

	cmd->scsi_करोne = करोne;

	cmnd = initio_alloc_scb(host);
	अगर (!cmnd)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	initio_build_scb(host, cmnd, cmd);
	initio_exec_scb(host, cmnd);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(i91u_queuecommand)

/**
 *	i91u_bus_reset		-	reset the SCSI bus
 *	@cmnd: Command block we want to trigger the reset क्रम
 *
 *	Initiate a SCSI bus reset sequence
 */

अटल पूर्णांक i91u_bus_reset(काष्ठा scsi_cmnd * cmnd)
अणु
	काष्ठा initio_host *host;

	host = (काष्ठा initio_host *) cmnd->device->host->hostdata;

	spin_lock_irq(cmnd->device->host->host_lock);
	initio_reset_scsi(host, 0);
	spin_unlock_irq(cmnd->device->host->host_lock);

	वापस SUCCESS;
पूर्ण

/**
 *	i91u_biosparam			-	वापस the "logical geometry
 *	@sdev: SCSI device
 *	@dev: Matching block device
 *	@capacity: Sector size of drive
 *	@info_array: Return space क्रम BIOS geometry
 *
 *	Map the device geometry in a manner compatible with the host
 *	controller BIOS behaviour.
 *
 *	FIXME: limited to 2^32 sector devices.
 */

अटल पूर्णांक i91u_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *dev,
		sector_t capacity, पूर्णांक *info_array)
अणु
	काष्ठा initio_host *host;		/* Poपूर्णांक to Host adapter control block */
	काष्ठा target_control *tc;

	host = (काष्ठा initio_host *) sdev->host->hostdata;
	tc = &host->tarमाला_लो[sdev->id];

	अगर (tc->heads) अणु
		info_array[0] = tc->heads;
		info_array[1] = tc->sectors;
		info_array[2] = (अचिन्हित दीर्घ)capacity / tc->heads / tc->sectors;
	पूर्ण अन्यथा अणु
		अगर (tc->drv_flags & TCF_DRV_255_63) अणु
			info_array[0] = 255;
			info_array[1] = 63;
			info_array[2] = (अचिन्हित दीर्घ)capacity / 255 / 63;
		पूर्ण अन्यथा अणु
			info_array[0] = 64;
			info_array[1] = 32;
			info_array[2] = (अचिन्हित दीर्घ)capacity >> 11;
		पूर्ण
	पूर्ण

#अगर defined(DEBUG_BIOSPARAM)
	अगर (i91u_debug & debug_biosparam) अणु
		prपूर्णांकk("bios geometry: head=%d, sec=%d, cyl=%d\n",
		       info_array[0], info_array[1], info_array[2]);
		prपूर्णांकk("WARNING: check, if the bios geometry is correct.\n");
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 *	i91u_unmap_scb		-	Unmap a command
 *	@pci_dev: PCI device the command is क्रम
 *	@cmnd: The command itself
 *
 *	Unmap any PCI mapping/IOMMU resources allocated when the command
 *	was mapped originally as part of initio_build_scb
 */

अटल व्योम i91u_unmap_scb(काष्ठा pci_dev *pci_dev, काष्ठा scsi_cmnd *cmnd)
अणु
	/* स्वतः sense buffer */
	अगर (cmnd->SCp.ptr) अणु
		dma_unmap_single(&pci_dev->dev,
				 (dma_addr_t)((अचिन्हित दीर्घ)cmnd->SCp.ptr),
				 SENSE_SIZE, DMA_FROM_DEVICE);
		cmnd->SCp.ptr = शून्य;
	पूर्ण

	/* request buffer */
	अगर (scsi_sg_count(cmnd)) अणु
		dma_unmap_single(&pci_dev->dev, cmnd->SCp.dma_handle,
				 माप(काष्ठा sg_entry) * TOTAL_SG_ENTRY,
				 DMA_BIसूचीECTIONAL);

		scsi_dma_unmap(cmnd);
	पूर्ण
पूर्ण

/*
 *	i91uSCBPost		-	SCSI callback
 *
 *	This is callback routine be called when tulip finish one
 *	SCSI command.
 */

अटल व्योम i91uSCBPost(u8 * host_mem, u8 * cblk_mem)
अणु
	काष्ठा scsi_cmnd *cmnd;	/* Poपूर्णांकer to SCSI request block */
	काष्ठा initio_host *host;
	काष्ठा scsi_ctrl_blk *cblk;

	host = (काष्ठा initio_host *) host_mem;
	cblk = (काष्ठा scsi_ctrl_blk *) cblk_mem;
	अगर ((cmnd = cblk->srb) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "i91uSCBPost: SRB pointer is empty\n");
		WARN_ON(1);
		initio_release_scb(host, cblk);	/* Release SCB क्रम current channel */
		वापस;
	पूर्ण

	/*
	 *	Remap the firmware error status पूर्णांकo a mid layer one
	 */
	चयन (cblk->hastat) अणु
	हाल 0x0:
	हाल 0xa:		/* Linked command complete without error and linked normally */
	हाल 0xb:		/* Linked command complete without error पूर्णांकerrupt generated */
		cblk->hastat = 0;
		अवरोध;

	हाल 0x11:		/* Selection समय out-The initiator selection or target
				   reselection was not complete within the SCSI Time out period */
		cblk->hastat = DID_TIME_OUT;
		अवरोध;

	हाल 0x14:		/* Target bus phase sequence failure-An invalid bus phase or bus
				   phase sequence was requested by the target. The host adapter
				   will generate a SCSI Reset Condition, notअगरying the host with
				   a SCRD पूर्णांकerrupt */
		cblk->hastat = DID_RESET;
		अवरोध;

	हाल 0x1a:		/* SCB Aborted. 07/21/98 */
		cblk->hastat = DID_ABORT;
		अवरोध;

	हाल 0x12:		/* Data overrun/underrun-The target attempted to transfer more data
				   than was allocated by the Data Length field or the sum of the
				   Scatter / Gather Data Length fields. */
	हाल 0x13:		/* Unexpected bus मुक्त-The target dropped the SCSI BSY at an unexpected समय. */
	हाल 0x16:		/* Invalid SCB Operation Code. */

	शेष:
		prपूर्णांकk("ini9100u: %x %x\n", cblk->hastat, cblk->tastat);
		cblk->hastat = DID_ERROR;	/* Couldn't find any better */
		अवरोध;
	पूर्ण

	cmnd->result = cblk->tastat | (cblk->hastat << 16);
	i91u_unmap_scb(host->pci_dev, cmnd);
	cmnd->scsi_करोne(cmnd);	/* Notअगरy प्रणाली DONE           */
	initio_release_scb(host, cblk);	/* Release SCB क्रम current channel */
पूर्ण

अटल काष्ठा scsi_host_ढाँचा initio_ढाँचा = अणु
	.proc_name		= "INI9100U",
	.name			= "Initio INI-9X00U/UW SCSI device driver",
	.queuecommand		= i91u_queuecommand,
	.eh_bus_reset_handler	= i91u_bus_reset,
	.bios_param		= i91u_biosparam,
	.can_queue		= MAX_TARGETS * i91u_MAXQUEUE,
	.this_id		= 1,
	.sg_tablesize		= SG_ALL,
पूर्ण;

अटल पूर्णांक initio_probe_one(काष्ठा pci_dev *pdev,
	स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा initio_host *host;
	u32 reg;
	u16 bios_seg;
	काष्ठा scsi_ctrl_blk *scb, *पंचांगp, *prev = शून्य /* silence gcc */;
	पूर्णांक num_scb, i, error;

	error = pci_enable_device(pdev);
	अगर (error)
		वापस error;

	pci_पढ़ो_config_dword(pdev, 0x44, (u32 *) & reg);
	bios_seg = (u16) (reg & 0xFF);
	अगर (((reg & 0xFF00) >> 8) == 0xFF)
		reg = 0;
	bios_seg = (bios_seg << 8) + ((u16) ((reg & 0xFF00) >> 8));

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_WARNING  "i91u: Could not set 32 bit DMA mask\n");
		error = -ENODEV;
		जाओ out_disable_device;
	पूर्ण
	shost = scsi_host_alloc(&initio_ढाँचा, माप(काष्ठा initio_host));
	अगर (!shost) अणु
		prपूर्णांकk(KERN_WARNING "initio: Could not allocate host structure.\n");
		error = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	host = (काष्ठा initio_host *)shost->hostdata;
	स_रखो(host, 0, माप(काष्ठा initio_host));
	host->addr = pci_resource_start(pdev, 0);
	host->bios_addr = bios_seg;

	अगर (!request_region(host->addr, 256, "i91u")) अणु
		prपूर्णांकk(KERN_WARNING "initio: I/O port range 0x%x is busy.\n", host->addr);
		error = -ENODEV;
		जाओ out_host_put;
	पूर्ण

	अगर (initio_tag_enable)	/* 1.01i */
		num_scb = MAX_TARGETS * i91u_MAXQUEUE;
	अन्यथा
		num_scb = MAX_TARGETS + 3;	/* 1-tape, 1-CD_ROM, 1- extra */

	क्रम (; num_scb >= MAX_TARGETS + 3; num_scb--) अणु
		i = num_scb * माप(काष्ठा scsi_ctrl_blk);
		अगर ((scb = kzalloc(i, GFP_DMA)) != शून्य)
			अवरोध;
	पूर्ण

	अगर (!scb) अणु
		prपूर्णांकk(KERN_WARNING "initio: Cannot allocate SCB array.\n");
		error = -ENOMEM;
		जाओ out_release_region;
	पूर्ण

	host->pci_dev = pdev;

	host->semaph = 1;
	spin_lock_init(&host->semaph_lock);
	host->num_scbs = num_scb;
	host->scb = scb;
	host->next_pending = scb;
	host->next_avail = scb;
	क्रम (i = 0, पंचांगp = scb; i < num_scb; i++, पंचांगp++) अणु
		पंचांगp->tagid = i;
		अगर (i != 0)
			prev->next = पंचांगp;
		prev = पंचांगp;
	पूर्ण
	prev->next = शून्य;
	host->scb_end = पंचांगp;
	host->first_avail = scb;
	host->last_avail = prev;
	spin_lock_init(&host->avail_lock);

	initio_init(host, phys_to_virt(((u32)bios_seg << 4)));

	host->jsstatus0 = 0;

	shost->io_port = host->addr;
	shost->n_io_port = 0xff;
	shost->can_queue = num_scb;		/* 03/05/98                      */
	shost->unique_id = host->addr;
	shost->max_id = host->max_tar;
	shost->max_lun = 32;	/* 10/21/97                     */
	shost->irq = pdev->irq;
	shost->this_id = host->scsi_id;	/* Assign HCS index           */
	shost->base = host->addr;
	shost->sg_tablesize = TOTAL_SG_ENTRY;

	error = request_irq(pdev->irq, i91u_पूर्णांकr, IRQF_SHARED, "i91u", shost);
	अगर (error < 0) अणु
		prपूर्णांकk(KERN_WARNING "initio: Unable to request IRQ %d\n", pdev->irq);
		जाओ out_मुक्त_scbs;
	पूर्ण

	pci_set_drvdata(pdev, shost);

	error = scsi_add_host(shost, &pdev->dev);
	अगर (error)
		जाओ out_मुक्त_irq;
	scsi_scan_host(shost);
	वापस 0;
out_मुक्त_irq:
	मुक्त_irq(pdev->irq, shost);
out_मुक्त_scbs:
	kमुक्त(host->scb);
out_release_region:
	release_region(host->addr, 256);
out_host_put:
	scsi_host_put(shost);
out_disable_device:
	pci_disable_device(pdev);
	वापस error;
पूर्ण

/**
 *	initio_हटाओ_one	-	control shutकरोwn
 *	@pdev:	PCI device being released
 *
 *	Release the resources asचिन्हित to this adapter after it has
 *	finished being used.
 */

अटल व्योम initio_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा initio_host *s = (काष्ठा initio_host *)host->hostdata;
	scsi_हटाओ_host(host);
	मुक्त_irq(pdev->irq, host);
	release_region(s->addr, 256);
	scsi_host_put(host);
	pci_disable_device(pdev);
पूर्ण

MODULE_LICENSE("GPL");

अटल काष्ठा pci_device_id initio_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_INIT, 0x9500, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INIT, 0x9400, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INIT, 0x9401, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INIT, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_DOMEX, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, initio_pci_tbl);

अटल काष्ठा pci_driver initio_pci_driver = अणु
	.name		= "initio",
	.id_table	= initio_pci_tbl,
	.probe		= initio_probe_one,
	.हटाओ		= initio_हटाओ_one,
पूर्ण;
module_pci_driver(initio_pci_driver);

MODULE_DESCRIPTION("Initio INI-9X00U/UW SCSI device driver");
MODULE_AUTHOR("Initio Corporation");
MODULE_LICENSE("GPL");
