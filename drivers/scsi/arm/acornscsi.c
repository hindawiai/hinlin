<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/acornscsi.c
 *
 *  Acorn SCSI 3 driver
 *  By R.M.King.
 *
 * Abanकरोned using the Select and Transfer command since there were
 * some nasty races between our software and the target devices that
 * were not easy to solve, and the device errata had a lot of entries
 * क्रम this command, some of them quite nasty...
 *
 * Changelog:
 *  26-Sep-1997	RMK	Re-jigged to use the queue module.
 *			Re-coded state machine to be based on driver
 *			state not scsi state.  Should be easier to debug.
 *			Added acornscsi_release to clean up properly.
 *			Updated proc/scsi reporting.
 *  05-Oct-1997	RMK	Implemented writing to SCSI devices.
 *  06-Oct-1997	RMK	Corrected small (non-serious) bug with the connect/
 *			reconnect race condition causing a warning message.
 *  12-Oct-1997	RMK	Added catch क्रम re-entering पूर्णांकerrupt routine.
 *  15-Oct-1997	RMK	Improved handling of commands.
 *  27-Jun-1998	RMK	Changed यंत्र/delay.h to linux/delay.h.
 *  13-Dec-1998	RMK	Better पात code and command handling.  Extra state
 *			transitions added to allow करोdgy devices to work.
 */
#घोषणा DEBUG_NO_WRITE	1
#घोषणा DEBUG_QUEUES	2
#घोषणा DEBUG_DMA	4
#घोषणा DEBUG_ABORT	8
#घोषणा DEBUG_DISCON	16
#घोषणा DEBUG_CONNECT	32
#घोषणा DEBUG_PHASES	64
#घोषणा DEBUG_WRITE	128
#घोषणा DEBUG_LINK	256
#घोषणा DEBUG_MESSAGES	512
#घोषणा DEBUG_RESET	1024
#घोषणा DEBUG_ALL	(DEBUG_RESET|DEBUG_MESSAGES|DEBUG_LINK|DEBUG_WRITE|\
			 DEBUG_PHASES|DEBUG_CONNECT|DEBUG_DISCON|DEBUG_ABORT|\
			 DEBUG_DMA|DEBUG_QUEUES)

/* DRIVER CONFIGURATION
 *
 * SCSI-II Tagged queue support.
 *
 * I करोn't have any SCSI devices that support it, so it is totally untested
 * (except to make sure that it करोesn't पूर्णांकerfere with any non-tagging
 * devices).  It is not fully implemented either - what happens when a
 * tagging device reconnects???
 *
 * You can tell अगर you have a device that supports tagged queueing my
 * cating (eg) /proc/scsi/acornscsi/0 and see अगर the SCSI revision is reported
 * as '2 TAG'.
 *
 * Also note that CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE is normally set in the config
 * scripts, but disabled here.  Once debugged, हटाओ the #अघोषित, otherwise to debug,
 * comment out the undef.
 */
#अघोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
/*
 * SCSI-II Synchronous transfer support.
 *
 * Tried and tested...
 *
 * SDTR_SIZE	  - maximum number of un-acknowledged bytes (0 = off, 12 = max)
 * SDTR_PERIOD	  - period of REQ संकेत (min=125, max=1020)
 * DEFAULT_PERIOD - शेष REQ period.
 */
#घोषणा SDTR_SIZE	12
#घोषणा SDTR_PERIOD	125
#घोषणा DEFAULT_PERIOD	500

/*
 * Debugging inक्रमmation
 *
 * DEBUG	  - bit mask from list above
 * DEBUG_TARGET   - is defined to the target number अगर you want to debug
 *		    a specअगरic target. [only recon/ग_लिखो/dma].
 */
#घोषणा DEBUG (DEBUG_RESET|DEBUG_WRITE|DEBUG_NO_WRITE)
/* only allow writing to SCSI device 0 */
#घोषणा NO_WRITE 0xFE
/*#घोषणा DEBUG_TARGET 2*/
/*
 * Select समयout समय (in 10ms units)
 *
 * This is the समयout used between the start of selection and the WD33C93
 * chip deciding that the device isn't responding.
 */
#घोषणा TIMEOUT_TIME 10
/*
 * Define this अगर you want to have verbose explanation of SCSI
 * status/messages.
 */
#अघोषित CONFIG_ACORNSCSI_CONSTANTS
/*
 * Define this अगर you want to use the on board DMAC [करोn't हटाओ this option]
 * If not set, then use PIO mode (not currently supported).
 */
#घोषणा USE_DMAC

/*
 * ====================================================================================
 */

#अगर_घोषित DEBUG_TARGET
#घोषणा DBG(cmd,xxx...) \
  अगर (cmd->device->id == DEBUG_TARGET) अणु \
    xxx; \
  पूर्ण
#अन्यथा
#घोषणा DBG(cmd,xxx...) xxx
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/ecard.h>

#समावेश "../scsi.h"
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>
#समावेश "acornscsi.h"
#समावेश "msgqueue.h"
#समावेश "scsi.h"

#समावेश <scsi/scsicam.h>

#घोषणा VER_MAJOR 2
#घोषणा VER_MINOR 0
#घोषणा VER_PATCH 6

#अगर_घोषित USE_DMAC
/*
 * DMAC setup parameters
 */ 
#घोषणा INIT_DEVCON0	(DEVCON0_RQL|DEVCON0_EXW|DEVCON0_CMP)
#घोषणा INIT_DEVCON1	(DEVCON1_BHLD)
#घोषणा DMAC_READ	(MODECON_READ)
#घोषणा DMAC_WRITE	(MODECON_WRITE)
#घोषणा INIT_SBICDMA	(CTRL_DMABURST)

#घोषणा scsi_xferred	have_data_in

/*
 * Size of on-board DMA buffer
 */
#घोषणा DMAC_BUFFER_SIZE	65536
#पूर्ण_अगर

#घोषणा STATUS_BUFFER_TO_PRINT	24

अचिन्हित पूर्णांक sdtr_period = SDTR_PERIOD;
अचिन्हित पूर्णांक sdtr_size   = SDTR_SIZE;

अटल व्योम acornscsi_करोne(AS_Host *host, काष्ठा scsi_cmnd **SCpntp,
			   अचिन्हित पूर्णांक result);
अटल पूर्णांक acornscsi_reconnect_finish(AS_Host *host);
अटल व्योम acornscsi_dma_cleanup(AS_Host *host);
अटल व्योम acornscsi_पातcmd(AS_Host *host, अचिन्हित अक्षर tag);

/* ====================================================================================
 * Miscellaneous
 */

/* Offsets from MEMC base */
#घोषणा SBIC_REGIDX	0x2000
#घोषणा SBIC_REGVAL	0x2004
#घोषणा DMAC_OFFSET	0x3000

/* Offsets from FAST IOC base */
#घोषणा INT_REG		0x2000
#घोषणा PAGE_REG	0x3000

अटल अंतरभूत व्योम sbic_arm_ग_लिखो(AS_Host *host, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
    ग_लिखोb(reg, host->base + SBIC_REGIDX);
    ग_लिखोb(value, host->base + SBIC_REGVAL);
पूर्ण

अटल अंतरभूत पूर्णांक sbic_arm_पढ़ो(AS_Host *host, अचिन्हित पूर्णांक reg)
अणु
    अगर(reg == SBIC_ASR)
	   वापस पढ़ोl(host->base + SBIC_REGIDX) & 255;
    ग_लिखोb(reg, host->base + SBIC_REGIDX);
    वापस पढ़ोl(host->base + SBIC_REGVAL) & 255;
पूर्ण

#घोषणा sbic_arm_ग_लिखोnext(host, val)	ग_लिखोb((val), (host)->base + SBIC_REGVAL)
#घोषणा sbic_arm_पढ़ोnext(host) 	पढ़ोb((host)->base + SBIC_REGVAL)

#अगर_घोषित USE_DMAC
#घोषणा dmac_पढ़ो(host,reg) \
	पढ़ोb((host)->base + DMAC_OFFSET + ((reg) << 2))

#घोषणा dmac_ग_लिखो(host,reg,value) \
	(अणु ग_लिखोb((value), (host)->base + DMAC_OFFSET + ((reg) << 2)); पूर्ण)

#घोषणा dmac_clearपूर्णांकr(host) 	ग_लिखोb(0, (host)->fast + INT_REG)

अटल अंतरभूत अचिन्हित पूर्णांक dmac_address(AS_Host *host)
अणु
    वापस dmac_पढ़ो(host, DMAC_TXADRHI) << 16 |
	   dmac_पढ़ो(host, DMAC_TXADRMD) << 8 |
	   dmac_पढ़ो(host, DMAC_TXADRLO);
पूर्ण

अटल
व्योम acornscsi_dumpdma(AS_Host *host, अक्षर *where)
अणु
	अचिन्हित पूर्णांक mode, addr, len;

	mode = dmac_पढ़ो(host, DMAC_MODECON);
	addr = dmac_address(host);
	len  = dmac_पढ़ो(host, DMAC_TXCNTHI) << 8 |
	       dmac_पढ़ो(host, DMAC_TXCNTLO);

	prपूर्णांकk("scsi%d: %s: DMAC %02x @%06x+%04x msk %02x, ",
		host->host->host_no, where,
		mode, addr, (len + 1) & 0xffff,
		dmac_पढ़ो(host, DMAC_MASKREG));

	prपूर्णांकk("DMA @%06x, ", host->dma.start_addr);
	prपूर्णांकk("BH @%p +%04x, ", host->scsi.SCp.ptr,
		host->scsi.SCp.this_residual);
	prपूर्णांकk("DT @+%04x ST @+%04x", host->dma.transferred,
		host->scsi.SCp.scsi_xferred);
	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर

अटल
अचिन्हित दीर्घ acornscsi_sbic_xfcount(AS_Host *host)
अणु
    अचिन्हित दीर्घ length;

    length = sbic_arm_पढ़ो(host, SBIC_TRANSCNTH) << 16;
    length |= sbic_arm_पढ़ोnext(host) << 8;
    length |= sbic_arm_पढ़ोnext(host);

    वापस length;
पूर्ण

अटल पूर्णांक
acornscsi_sbic_रुको(AS_Host *host, पूर्णांक stat_mask, पूर्णांक stat, पूर्णांक समयout, अक्षर *msg)
अणु
	पूर्णांक asr;

	करो अणु
		asr = sbic_arm_पढ़ो(host, SBIC_ASR);

		अगर ((asr & stat_mask) == stat)
			वापस 0;

		udelay(1);
	पूर्ण जबतक (--समयout);

	prपूर्णांकk("scsi%d: timeout while %s\n", host->host->host_no, msg);

	वापस -1;
पूर्ण

अटल
पूर्णांक acornscsi_sbic_issuecmd(AS_Host *host, पूर्णांक command)
अणु
    अगर (acornscsi_sbic_रुको(host, ASR_CIP, 0, 1000, "issuing command"))
	वापस -1;

    sbic_arm_ग_लिखो(host, SBIC_CMND, command);

    वापस 0;
पूर्ण

अटल व्योम
acornscsi_csdelay(अचिन्हित पूर्णांक cs)
अणु
    अचिन्हित दीर्घ target_jअगरfies, flags;

    target_jअगरfies = jअगरfies + 1 + cs * HZ / 100;

    local_save_flags(flags);
    local_irq_enable();

    जबतक (समय_beक्रमe(jअगरfies, target_jअगरfies)) barrier();

    local_irq_restore(flags);
पूर्ण

अटल
व्योम acornscsi_resetcard(AS_Host *host)
अणु
    अचिन्हित पूर्णांक i, समयout;

    /* निश्चित reset line */
    host->card.page_reg = 0x80;
    ग_लिखोb(host->card.page_reg, host->fast + PAGE_REG);

    /* रुको 3 cs.  SCSI standard says 25ms. */
    acornscsi_csdelay(3);

    host->card.page_reg = 0;
    ग_लिखोb(host->card.page_reg, host->fast + PAGE_REG);

    /*
     * Should get a reset from the card
     */
    समयout = 1000;
    करो अणु
	अगर (पढ़ोb(host->fast + INT_REG) & 8)
	    अवरोध;
	udelay(1);
    पूर्ण जबतक (--समयout);

    अगर (समयout == 0)
	prपूर्णांकk("scsi%d: timeout while resetting card\n",
		host->host->host_no);

    sbic_arm_पढ़ो(host, SBIC_ASR);
    sbic_arm_पढ़ो(host, SBIC_SSR);

    /* setup sbic - WD33C93A */
    sbic_arm_ग_लिखो(host, SBIC_OWNID, OWNID_EAF | host->host->this_id);
    sbic_arm_ग_लिखो(host, SBIC_CMND, CMND_RESET);

    /*
     * Command should cause a reset पूर्णांकerrupt
     */
    समयout = 1000;
    करो अणु
	अगर (पढ़ोb(host->fast + INT_REG) & 8)
	    अवरोध;
	udelay(1);
    पूर्ण जबतक (--समयout);

    अगर (समयout == 0)
	prपूर्णांकk("scsi%d: timeout while resetting card\n",
		host->host->host_no);

    sbic_arm_पढ़ो(host, SBIC_ASR);
    अगर (sbic_arm_पढ़ो(host, SBIC_SSR) != 0x01)
	prपूर्णांकk(KERN_CRIT "scsi%d: WD33C93A didn't give enhanced reset interrupt\n",
		host->host->host_no);

    sbic_arm_ग_लिखो(host, SBIC_CTRL, INIT_SBICDMA | CTRL_IDI);
    sbic_arm_ग_लिखो(host, SBIC_TIMEOUT, TIMEOUT_TIME);
    sbic_arm_ग_लिखो(host, SBIC_SYNCHTRANSFER, SYNCHTRANSFER_2DBA);
    sbic_arm_ग_लिखो(host, SBIC_SOURCEID, SOURCEID_ER | SOURCEID_DSP);

    host->card.page_reg = 0x40;
    ग_लिखोb(host->card.page_reg, host->fast + PAGE_REG);

    /* setup dmac - uPC71071 */
    dmac_ग_लिखो(host, DMAC_INIT, 0);
#अगर_घोषित USE_DMAC
    dmac_ग_लिखो(host, DMAC_INIT, INIT_8BIT);
    dmac_ग_लिखो(host, DMAC_CHANNEL, CHANNEL_0);
    dmac_ग_लिखो(host, DMAC_DEVCON0, INIT_DEVCON0);
    dmac_ग_लिखो(host, DMAC_DEVCON1, INIT_DEVCON1);
#पूर्ण_अगर

    host->SCpnt = शून्य;
    host->scsi.phase = PHASE_IDLE;
    host->scsi.disconnectable = 0;

    स_रखो(host->busyluns, 0, माप(host->busyluns));

    क्रम (i = 0; i < 8; i++) अणु
	host->device[i].sync_state = SYNC_NEGOCIATE;
	host->device[i].disconnect_ok = 1;
    पूर्ण

    /* रुको 25 cs.  SCSI standard says 250ms. */
    acornscsi_csdelay(25);
पूर्ण

/*=============================================================================================
 * Utility routines (eg. debug)
 */
#अगर_घोषित CONFIG_ACORNSCSI_CONSTANTS
अटल अक्षर *acornscsi_पूर्णांकerrupttype[] = अणु
  "rst",  "suc",  "p/a",  "3",
  "term", "5",	  "6",	  "7",
  "serv", "9",	  "a",	  "b",
  "c",	  "d",	  "e",	  "f"
पूर्ण;

अटल चिन्हित अक्षर acornscsi_map[] = अणु
  0,  1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1,  2, -1, -1,  -1, -1,  3, -1,   4,	5,  6,	7,   8,  9, 10, 11,
 12, 13, 14, -1,  -1, -1, -1, -1,   4,	5,  6,	7,   8,  9, 10, 11,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 15, 16, 17, 18,  19, -1, -1, 20,   4,	5,  6,	7,   8,  9, 10, 11,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 21, 22, -1, -1,  -1, 23, -1, -1,   4,	5,  6,	7,   8,  9, 10, 11,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,
 -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1,  -1, -1, -1, -1
पूर्ण;      

अटल अक्षर *acornscsi_पूर्णांकerruptcode[] = अणु
    /* 0 */
    "reset - normal mode",	/* 00 */
    "reset - advanced mode",	/* 01 */

    /* 2 */
    "sel",			/* 11 */
    "sel+xfer", 		/* 16 */
    "data-out", 		/* 18 */
    "data-in",			/* 19 */
    "cmd",			/* 1A */
    "stat",			/* 1B */
    "??-out",			/* 1C */
    "??-in",			/* 1D */
    "msg-out",			/* 1E */
    "msg-in",			/* 1F */

    /* 12 */
    "/ACK asserted",		/* 20 */
    "save-data-ptr",		/* 21 */
    "{re}sel",			/* 22 */

    /* 15 */
    "inv cmd",			/* 40 */
    "unexpected disconnect",	/* 41 */
    "sel timeout",		/* 42 */
    "P err",			/* 43 */
    "P err+ATN",		/* 44 */
    "bad status byte",		/* 47 */

    /* 21 */
    "resel, no id",		/* 80 */
    "resel",			/* 81 */
    "discon",			/* 85 */
पूर्ण;

अटल
व्योम prपूर्णांक_scsi_status(अचिन्हित पूर्णांक ssr)
अणु
    अगर (acornscsi_map[ssr] != -1)
	prपूर्णांकk("%s:%s",
		acornscsi_पूर्णांकerrupttype[(ssr >> 4)],
		acornscsi_पूर्णांकerruptcode[acornscsi_map[ssr]]);
    अन्यथा
	prपूर्णांकk("%X:%X", ssr >> 4, ssr & 0x0f);    
पूर्ण    
#पूर्ण_अगर

अटल
व्योम prपूर्णांक_sbic_status(पूर्णांक asr, पूर्णांक ssr, पूर्णांक cmdphase)
अणु
#अगर_घोषित CONFIG_ACORNSCSI_CONSTANTS
    prपूर्णांकk("sbic: %c%c%c%c%c%c ",
	    asr & ASR_INT ? 'I' : 'i',
	    asr & ASR_LCI ? 'L' : 'l',
	    asr & ASR_BSY ? 'B' : 'b',
	    asr & ASR_CIP ? 'C' : 'c',
	    asr & ASR_PE  ? 'P' : 'p',
	    asr & ASR_DBR ? 'D' : 'd');
    prपूर्णांकk("scsi: ");
    prपूर्णांक_scsi_status(ssr);
    prपूर्णांकk(" ph %02X\n", cmdphase);
#अन्यथा
    prपूर्णांकk("sbic: %02X scsi: %X:%X ph: %02X\n",
	    asr, (ssr & 0xf0)>>4, ssr & 0x0f, cmdphase);
#पूर्ण_अगर
पूर्ण

अटल व्योम
acornscsi_dumplogline(AS_Host *host, पूर्णांक target, पूर्णांक line)
अणु
	अचिन्हित दीर्घ prev;
	चिन्हित पूर्णांक ptr;

	ptr = host->status_ptr[target] - STATUS_BUFFER_TO_PRINT;
	अगर (ptr < 0)
		ptr += STATUS_BUFFER_SIZE;

	prपूर्णांकk("%c: %3s:", target == 8 ? 'H' : '0' + target,
		line == 0 ? "ph" : line == 1 ? "ssr" : "int");

	prev = host->status[target][ptr].when;

	क्रम (; ptr != host->status_ptr[target]; ptr = (ptr + 1) & (STATUS_BUFFER_SIZE - 1)) अणु
		अचिन्हित दीर्घ समय_dअगरf;

		अगर (!host->status[target][ptr].when)
			जारी;

		चयन (line) अणु
		हाल 0:
			prपूर्णांकk("%c%02X", host->status[target][ptr].irq ? '-' : ' ',
					 host->status[target][ptr].ph);
			अवरोध;

		हाल 1:
			prपूर्णांकk(" %02X", host->status[target][ptr].ssr);
			अवरोध;

		हाल 2:
			समय_dअगरf = host->status[target][ptr].when - prev;
			prev = host->status[target][ptr].when;
			अगर (समय_dअगरf == 0)
				prपूर्णांकk("==^");
			अन्यथा अगर (समय_dअगरf >= 100)
				prपूर्णांकk("   ");
			अन्यथा
				prपूर्णांकk(" %02ld", समय_dअगरf);
			अवरोध;
		पूर्ण
	पूर्ण

	prपूर्णांकk("\n");
पूर्ण

अटल
व्योम acornscsi_dumplog(AS_Host *host, पूर्णांक target)
अणु
    करो अणु
	acornscsi_dumplogline(host, target, 0);
	acornscsi_dumplogline(host, target, 1);
	acornscsi_dumplogline(host, target, 2);

	अगर (target == 8)
	    अवरोध;

	target = 8;
    पूर्ण जबतक (1);
पूर्ण

अटल
अक्षर acornscsi_target(AS_Host *host)
अणु
	अगर (host->SCpnt)
		वापस '0' + host->SCpnt->device->id;
	वापस 'H';
पूर्ण

/*
 * Prototype: cmdtype_t acornscsi_cmdtype(पूर्णांक command)
 * Purpose  : dअगरferentiate READ from WRITE from other commands
 * Params   : command - command to पूर्णांकerpret
 * Returns  : CMD_READ	- command पढ़ोs data,
 *	      CMD_WRITE - command ग_लिखोs data,
 *	      CMD_MISC	- everything अन्यथा
 */
अटल अंतरभूत
cmdtype_t acornscsi_cmdtype(पूर्णांक command)
अणु
    चयन (command) अणु
    हाल WRITE_6:  हाल WRITE_10:  हाल WRITE_12:
	वापस CMD_WRITE;
    हाल READ_6:   हाल READ_10:   हाल READ_12:
	वापस CMD_READ;
    शेष:
	वापस CMD_MISC;
    पूर्ण
पूर्ण

/*
 * Prototype: पूर्णांक acornscsi_datadirection(पूर्णांक command)
 * Purpose  : dअगरferentiate between commands that have a DATA IN phase
 *	      and a DATA OUT phase
 * Params   : command - command to पूर्णांकerpret
 * Returns  : DATAसूची_OUT - data out phase expected
 *	      DATAसूची_IN  - data in phase expected
 */
अटल
datadir_t acornscsi_datadirection(पूर्णांक command)
अणु
    चयन (command) अणु
    हाल CHANGE_DEFINITION:	हाल COMPARE:		हाल COPY:
    हाल COPY_VERIFY:		हाल LOG_SELECT:	हाल MODE_SELECT:
    हाल MODE_SELECT_10:	हाल SEND_DIAGNOSTIC:	हाल WRITE_BUFFER:
    हाल FORMAT_UNIT:		हाल REASSIGN_BLOCKS:	हाल RESERVE:
    हाल SEARCH_EQUAL:		हाल SEARCH_HIGH:	हाल SEARCH_LOW:
    हाल WRITE_6:		हाल WRITE_10:		हाल WRITE_VERIFY:
    हाल UPDATE_BLOCK:		हाल WRITE_LONG:	हाल WRITE_SAME:
    हाल SEARCH_HIGH_12:	हाल SEARCH_EQUAL_12:	हाल SEARCH_LOW_12:
    हाल WRITE_12:		हाल WRITE_VERIFY_12:	हाल SET_WINDOW:
    हाल MEDIUM_SCAN:		हाल SEND_VOLUME_TAG:	हाल 0xea:
	वापस DATAसूची_OUT;
    शेष:
	वापस DATAसूची_IN;
    पूर्ण
पूर्ण

/*
 * Purpose  : provide values क्रम synchronous transfers with 33C93.
 * Copyright: Copyright (c) 1996 John Shअगरflett, GeoLog Consulting
 *	Modअगरied by Russell King क्रम 8MHz WD33C93A
 */
अटल काष्ठा sync_xfer_tbl अणु
    अचिन्हित पूर्णांक period_ns;
    अचिन्हित अक्षर reg_value;
पूर्ण sync_xfer_table[] = अणु
    अणु	1, 0x20 पूर्ण,    अणु 249, 0x20 पूर्ण,	अणु 374, 0x30 पूर्ण,
    अणु 499, 0x40 पूर्ण,    अणु 624, 0x50 पूर्ण,	अणु 749, 0x60 पूर्ण,
    अणु 874, 0x70 पूर्ण,    अणु 999, 0x00 पूर्ण,	अणु   0,	  0 पूर्ण
पूर्ण;

/*
 * Prototype: पूर्णांक acornscsi_getperiod(अचिन्हित अक्षर syncxfer)
 * Purpose  : period क्रम the synchronous transfer setting
 * Params   : syncxfer SYNCXFER रेजिस्टर value
 * Returns  : period in ns.
 */
अटल
पूर्णांक acornscsi_getperiod(अचिन्हित अक्षर syncxfer)
अणु
    पूर्णांक i;

    syncxfer &= 0xf0;
    अगर (syncxfer == 0x10)
	syncxfer = 0;

    क्रम (i = 1; sync_xfer_table[i].period_ns; i++)
	अगर (syncxfer == sync_xfer_table[i].reg_value)
	    वापस sync_xfer_table[i].period_ns;
    वापस 0;
पूर्ण

/*
 * Prototype: पूर्णांक round_period(अचिन्हित पूर्णांक period)
 * Purpose  : वापस index पूर्णांकo above table क्रम a required REQ period
 * Params   : period - समय (ns) क्रम REQ
 * Returns  : table index
 * Copyright: Copyright (c) 1996 John Shअगरflett, GeoLog Consulting
 */
अटल अंतरभूत
पूर्णांक round_period(अचिन्हित पूर्णांक period)
अणु
    पूर्णांक i;

    क्रम (i = 1; sync_xfer_table[i].period_ns; i++) अणु
	अगर ((period <= sync_xfer_table[i].period_ns) &&
	    (period > sync_xfer_table[i - 1].period_ns))
	    वापस i;
    पूर्ण
    वापस 7;
पूर्ण

/*
 * Prototype: अचिन्हित अक्षर calc_sync_xfer(अचिन्हित पूर्णांक period, अचिन्हित पूर्णांक offset)
 * Purpose  : calculate value क्रम 33c93s SYNC रेजिस्टर
 * Params   : period - समय (ns) क्रम REQ
 *	      offset - offset in bytes between REQ/ACK
 * Returns  : value क्रम SYNC रेजिस्टर
 * Copyright: Copyright (c) 1996 John Shअगरflett, GeoLog Consulting
 */
अटल
अचिन्हित अक्षर __maybe_unused calc_sync_xfer(अचिन्हित पूर्णांक period,
					    अचिन्हित पूर्णांक offset)
अणु
    वापस sync_xfer_table[round_period(period)].reg_value |
		((offset < SDTR_SIZE) ? offset : SDTR_SIZE);
पूर्ण

/* ====================================================================================
 * Command functions
 */
/*
 * Function: acornscsi_kick(AS_Host *host)
 * Purpose : kick next command to पूर्णांकerface
 * Params  : host - host to send command to
 * Returns : INTR_IDLE अगर idle, otherwise INTR_PROCESSING
 * Notes   : पूर्णांकerrupts are always disabled!
 */
अटल
पूर्णांकr_ret_t acornscsi_kick(AS_Host *host)
अणु
    पूर्णांक from_queue = 0;
    काष्ठा scsi_cmnd *SCpnt;

    /* first check to see अगर a command is रुकोing to be executed */
    SCpnt = host->origSCpnt;
    host->origSCpnt = शून्य;

    /* retrieve next command */
    अगर (!SCpnt) अणु
	SCpnt = queue_हटाओ_exclude(&host->queues.issue, host->busyluns);
	अगर (!SCpnt)
	    वापस INTR_IDLE;

	from_queue = 1;
    पूर्ण

    अगर (host->scsi.disconnectable && host->SCpnt) अणु
	queue_add_cmd_tail(&host->queues.disconnected, host->SCpnt);
	host->scsi.disconnectable = 0;
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	DBG(host->SCpnt, prपूर्णांकk("scsi%d.%c: moved command to disconnected queue\n",
		host->host->host_no, acornscsi_target(host)));
#पूर्ण_अगर
	host->SCpnt = शून्य;
    पूर्ण

    /*
     * If we have an पूर्णांकerrupt pending, then we may have been reselected.
     * In this हाल, we करोn't want to ग_लिखो to the रेजिस्टरs
     */
    अगर (!(sbic_arm_पढ़ो(host, SBIC_ASR) & (ASR_INT|ASR_BSY|ASR_CIP))) अणु
	sbic_arm_ग_लिखो(host, SBIC_DESTID, SCpnt->device->id);
	sbic_arm_ग_लिखो(host, SBIC_CMND, CMND_SELWITHATN);
    पूर्ण

    /*
     * claim host busy - all of these must happen atomically wrt
     * our पूर्णांकerrupt routine.  Failure means command loss.
     */
    host->scsi.phase = PHASE_CONNECTING;
    host->SCpnt = SCpnt;
    host->scsi.SCp = SCpnt->SCp;
    host->dma.xfer_setup = 0;
    host->dma.xfer_required = 0;
    host->dma.xfer_करोne = 0;

#अगर (DEBUG & (DEBUG_ABORT|DEBUG_CONNECT))
    DBG(SCpnt,prपूर्णांकk("scsi%d.%c: starting cmd %02X\n",
	    host->host->host_no, '0' + SCpnt->device->id,
	    SCpnt->cmnd[0]));
#पूर्ण_अगर

    अगर (from_queue) अणु
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
	/*
	 * tagged queueing - allocate a new tag to this command
	 */
	अगर (SCpnt->device->simple_tags) अणु
	    SCpnt->device->current_tag += 1;
	    अगर (SCpnt->device->current_tag == 0)
		SCpnt->device->current_tag = 1;
	    SCpnt->tag = SCpnt->device->current_tag;
	पूर्ण अन्यथा
#पूर्ण_अगर
	    set_bit(SCpnt->device->id * 8 +
		    (u8)(SCpnt->device->lun & 0x07), host->busyluns);

	host->stats.हटाओs += 1;

	चयन (acornscsi_cmdtype(SCpnt->cmnd[0])) अणु
	हाल CMD_WRITE:
	    host->stats.ग_लिखोs += 1;
	    अवरोध;
	हाल CMD_READ:
	    host->stats.पढ़ोs += 1;
	    अवरोध;
	हाल CMD_MISC:
	    host->stats.miscs += 1;
	    अवरोध;
	पूर्ण
    पूर्ण

    वापस INTR_PROCESSING;
पूर्ण    

/*
 * Function: व्योम acornscsi_करोne(AS_Host *host, काष्ठा scsi_cmnd **SCpntp, अचिन्हित पूर्णांक result)
 * Purpose : complete processing क्रम command
 * Params  : host   - पूर्णांकerface that completed
 *	     result - driver byte of result
 */
अटल व्योम acornscsi_करोne(AS_Host *host, काष्ठा scsi_cmnd **SCpntp,
			   अचिन्हित पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *SCpnt = *SCpntp;

    /* clean up */
    sbic_arm_ग_लिखो(host, SBIC_SOURCEID, SOURCEID_ER | SOURCEID_DSP);

    host->stats.fins += 1;

    अगर (SCpnt) अणु
	*SCpntp = शून्य;

	acornscsi_dma_cleanup(host);

	SCpnt->result = result << 16 | host->scsi.SCp.Message << 8 | host->scsi.SCp.Status;

	/*
	 * In theory, this should not happen.  In practice, it seems to.
	 * Only trigger an error अगर the device attempts to report all happy
	 * but with untransferred buffers...  If we करोn't करो something, then
	 * data loss will occur.  Should we check SCpnt->underflow here?
	 * It करोesn't appear to be set to something meaningful by the higher
	 * levels all the समय.
	 */
	अगर (result == DID_OK) अणु
		पूर्णांक xfer_warn = 0;

		अगर (SCpnt->underflow == 0) अणु
			अगर (host->scsi.SCp.ptr &&
			    acornscsi_cmdtype(SCpnt->cmnd[0]) != CMD_MISC)
				xfer_warn = 1;
		पूर्ण अन्यथा अणु
			अगर (host->scsi.SCp.scsi_xferred < SCpnt->underflow ||
			    host->scsi.SCp.scsi_xferred != host->dma.transferred)
				xfer_warn = 1;
		पूर्ण

		/* ANSI standard says: (SCSI-2 Rev 10c Sect 5.6.6)
		 *  Tarमाला_लो which अवरोध data transfers पूर्णांकo multiple
		 *  connections shall end each successful connection
		 *  (except possibly the last) with a SAVE DATA
		 *  POINTER - DISCONNECT message sequence.
		 *
		 * This makes it dअगरficult to ensure that a transfer has
		 * completed.  If we reach the end of a transfer during
		 * the command, then we can only have finished the transfer.
		 * thereक्रमe, अगर we seem to have some data reमुख्यing, this
		 * is not a problem.
		 */
		अगर (host->dma.xfer_करोne)
			xfer_warn = 0;

		अगर (xfer_warn) अणु
		    चयन (status_byte(SCpnt->result)) अणु
		    हाल CHECK_CONDITION:
		    हाल COMMAND_TERMINATED:
		    हाल BUSY:
		    हाल QUEUE_FULL:
		    हाल RESERVATION_CONFLICT:
			अवरोध;

		    शेष:
			scmd_prपूर्णांकk(KERN_ERR, SCpnt,
				    "incomplete data transfer detected: "
				    "result=%08X", SCpnt->result);
			scsi_prपूर्णांक_command(SCpnt);
			acornscsi_dumpdma(host, "done");
			acornscsi_dumplog(host, SCpnt->device->id);
			set_host_byte(SCpnt, DID_ERROR);
		    पूर्ण
		पूर्ण
	पूर्ण

	अगर (!SCpnt->scsi_करोne)
	    panic("scsi%d.H: null scsi_done function in acornscsi_done", host->host->host_no);

	clear_bit(SCpnt->device->id * 8 +
		  (u8)(SCpnt->device->lun & 0x7), host->busyluns);

	SCpnt->scsi_करोne(SCpnt);
    पूर्ण अन्यथा
	prपूर्णांकk("scsi%d: null command in acornscsi_done", host->host->host_no);

    host->scsi.phase = PHASE_IDLE;
पूर्ण

/* ====================================================================================
 * DMA routines
 */
/*
 * Purpose  : update SCSI Data Poपूर्णांकer
 * Notes    : this will only be one SG entry or less
 */
अटल
व्योम acornscsi_data_updateptr(AS_Host *host, काष्ठा scsi_poपूर्णांकer *SCp, अचिन्हित पूर्णांक length)
अणु
    SCp->ptr += length;
    SCp->this_residual -= length;

    अगर (SCp->this_residual == 0 && next_SCp(SCp) == 0)
	host->dma.xfer_करोne = 1;
पूर्ण

/*
 * Prototype: व्योम acornscsi_data_पढ़ो(AS_Host *host, अक्षर *ptr,
 *				अचिन्हित पूर्णांक start_addr, अचिन्हित पूर्णांक length)
 * Purpose  : पढ़ो data from DMA RAM
 * Params   : host - host to transfer from
 *	      ptr  - DRAM address
 *	      start_addr - host mem address
 *	      length - number of bytes to transfer
 * Notes    : this will only be one SG entry or less
 */
अटल
व्योम acornscsi_data_पढ़ो(AS_Host *host, अक्षर *ptr,
				 अचिन्हित पूर्णांक start_addr, अचिन्हित पूर्णांक length)
अणु
    बाह्य व्योम __acornscsi_in(व्योम __iomem *, अक्षर *buf, पूर्णांक len);
    अचिन्हित पूर्णांक page, offset, len = length;

    page = (start_addr >> 12);
    offset = start_addr & ((1 << 12) - 1);

    ग_लिखोb((page & 0x3f) | host->card.page_reg, host->fast + PAGE_REG);

    जबतक (len > 0) अणु
	अचिन्हित पूर्णांक this_len;

	अगर (len + offset > (1 << 12))
	    this_len = (1 << 12) - offset;
	अन्यथा
	    this_len = len;

	__acornscsi_in(host->base + (offset << 1), ptr, this_len);

	offset += this_len;
	ptr += this_len;
	len -= this_len;

	अगर (offset == (1 << 12)) अणु
	    offset = 0;
	    page ++;
	    ग_लिखोb((page & 0x3f) | host->card.page_reg, host->fast + PAGE_REG);
	पूर्ण
    पूर्ण
    ग_लिखोb(host->card.page_reg, host->fast + PAGE_REG);
पूर्ण

/*
 * Prototype: व्योम acornscsi_data_ग_लिखो(AS_Host *host, अक्षर *ptr,
 *				अचिन्हित पूर्णांक start_addr, अचिन्हित पूर्णांक length)
 * Purpose  : ग_लिखो data to DMA RAM
 * Params   : host - host to transfer from
 *	      ptr  - DRAM address
 *	      start_addr - host mem address
 *	      length - number of bytes to transfer
 * Notes    : this will only be one SG entry or less
 */
अटल
व्योम acornscsi_data_ग_लिखो(AS_Host *host, अक्षर *ptr,
				 अचिन्हित पूर्णांक start_addr, अचिन्हित पूर्णांक length)
अणु
    बाह्य व्योम __acornscsi_out(व्योम __iomem *, अक्षर *buf, पूर्णांक len);
    अचिन्हित पूर्णांक page, offset, len = length;

    page = (start_addr >> 12);
    offset = start_addr & ((1 << 12) - 1);

    ग_लिखोb((page & 0x3f) | host->card.page_reg, host->fast + PAGE_REG);

    जबतक (len > 0) अणु
	अचिन्हित पूर्णांक this_len;

	अगर (len + offset > (1 << 12))
	    this_len = (1 << 12) - offset;
	अन्यथा
	    this_len = len;

	__acornscsi_out(host->base + (offset << 1), ptr, this_len);

	offset += this_len;
	ptr += this_len;
	len -= this_len;

	अगर (offset == (1 << 12)) अणु
	    offset = 0;
	    page ++;
	    ग_लिखोb((page & 0x3f) | host->card.page_reg, host->fast + PAGE_REG);
	पूर्ण
    पूर्ण
    ग_लिखोb(host->card.page_reg, host->fast + PAGE_REG);
पूर्ण

/* =========================================================================================
 * On-board DMA routines
 */
#अगर_घोषित USE_DMAC
/*
 * Prototype: व्योम acornscsi_dmastop(AS_Host *host)
 * Purpose  : stop all DMA
 * Params   : host - host on which to stop DMA
 * Notes    : This is called when leaving DATA IN/OUT phase,
 *	      or when पूर्णांकerface is RESET
 */
अटल अंतरभूत
व्योम acornscsi_dma_stop(AS_Host *host)
अणु
    dmac_ग_लिखो(host, DMAC_MASKREG, MASK_ON);
    dmac_clearपूर्णांकr(host);

#अगर (DEBUG & DEBUG_DMA)
    DBG(host->SCpnt, acornscsi_dumpdma(host, "stop"));
#पूर्ण_अगर
पूर्ण

/*
 * Function: व्योम acornscsi_dma_setup(AS_Host *host, dmadir_t direction)
 * Purpose : setup DMA controller क्रम data transfer
 * Params  : host - host to setup
 *	     direction - data transfer direction
 * Notes   : This is called when entering DATA I/O phase, not
 *	     जबतक we're in a DATA I/O phase
 */
अटल
व्योम acornscsi_dma_setup(AS_Host *host, dmadir_t direction)
अणु
    अचिन्हित पूर्णांक address, length, mode;

    host->dma.direction = direction;

    dmac_ग_लिखो(host, DMAC_MASKREG, MASK_ON);

    अगर (direction == DMA_OUT) अणु
#अगर (DEBUG & DEBUG_NO_WRITE)
	अगर (NO_WRITE & (1 << host->SCpnt->device->id)) अणु
	    prपूर्णांकk(KERN_CRIT "scsi%d.%c: I can't handle DMA_OUT!\n",
		    host->host->host_no, acornscsi_target(host));
	    वापस;
	पूर्ण
#पूर्ण_अगर
	mode = DMAC_WRITE;
    पूर्ण अन्यथा
	mode = DMAC_READ;

    /*
     * Allocate some buffer space, limited to half the buffer size
     */
    length = min_t(अचिन्हित पूर्णांक, host->scsi.SCp.this_residual, DMAC_BUFFER_SIZE / 2);
    अगर (length) अणु
	host->dma.start_addr = address = host->dma.मुक्त_addr;
	host->dma.मुक्त_addr = (host->dma.मुक्त_addr + length) &
				(DMAC_BUFFER_SIZE - 1);

	/*
	 * Transfer data to DMA memory
	 */
	अगर (direction == DMA_OUT)
	    acornscsi_data_ग_लिखो(host, host->scsi.SCp.ptr, host->dma.start_addr,
				length);

	length -= 1;
	dmac_ग_लिखो(host, DMAC_TXCNTLO, length);
	dmac_ग_लिखो(host, DMAC_TXCNTHI, length >> 8);
	dmac_ग_लिखो(host, DMAC_TXADRLO, address);
	dmac_ग_लिखो(host, DMAC_TXADRMD, address >> 8);
	dmac_ग_लिखो(host, DMAC_TXADRHI, 0);
	dmac_ग_लिखो(host, DMAC_MODECON, mode);
	dmac_ग_लिखो(host, DMAC_MASKREG, MASK_OFF);

#अगर (DEBUG & DEBUG_DMA)
	DBG(host->SCpnt, acornscsi_dumpdma(host, "strt"));
#पूर्ण_अगर
	host->dma.xfer_setup = 1;
    पूर्ण
पूर्ण

/*
 * Function: व्योम acornscsi_dma_cleanup(AS_Host *host)
 * Purpose : ensure that all DMA transfers are up-to-date & host->scsi.SCp is correct
 * Params  : host - host to finish
 * Notes   : This is called when a command is:
 *		terminating, RESTORE_POINTERS, SAVE_POINTERS, DISCONNECT
 *	   : This must not वापस until all transfers are completed.
 */
अटल
व्योम acornscsi_dma_cleanup(AS_Host *host)
अणु
    dmac_ग_लिखो(host, DMAC_MASKREG, MASK_ON);
    dmac_clearपूर्णांकr(host);

    /*
     * Check क्रम a pending transfer
     */
    अगर (host->dma.xfer_required) अणु
	host->dma.xfer_required = 0;
	अगर (host->dma.direction == DMA_IN)
	    acornscsi_data_पढ़ो(host, host->dma.xfer_ptr,
				 host->dma.xfer_start, host->dma.xfer_length);
    पूर्ण

    /*
     * Has a transfer been setup?
     */
    अगर (host->dma.xfer_setup) अणु
	अचिन्हित पूर्णांक transferred;

	host->dma.xfer_setup = 0;

#अगर (DEBUG & DEBUG_DMA)
	DBG(host->SCpnt, acornscsi_dumpdma(host, "cupi"));
#पूर्ण_अगर

	/*
	 * Calculate number of bytes transferred from DMA.
	 */
	transferred = dmac_address(host) - host->dma.start_addr;
	host->dma.transferred += transferred;

	अगर (host->dma.direction == DMA_IN)
	    acornscsi_data_पढ़ो(host, host->scsi.SCp.ptr,
				 host->dma.start_addr, transferred);

	/*
	 * Update SCSI poपूर्णांकers
	 */
	acornscsi_data_updateptr(host, &host->scsi.SCp, transferred);
#अगर (DEBUG & DEBUG_DMA)
	DBG(host->SCpnt, acornscsi_dumpdma(host, "cupo"));
#पूर्ण_अगर
    पूर्ण
पूर्ण

/*
 * Function: व्योम acornscsi_dmacपूर्णांकr(AS_Host *host)
 * Purpose : handle पूर्णांकerrupts from DMAC device
 * Params  : host - host to process
 * Notes   : If पढ़ोing, we schedule the पढ़ो to मुख्य memory &
 *	     allow the transfer to जारी.
 *	   : If writing, we fill the onboard DMA memory from मुख्य
 *	     memory.
 *	   : Called whenever DMAC finished it's current transfer.
 */
अटल
व्योम acornscsi_dma_पूर्णांकr(AS_Host *host)
अणु
    अचिन्हित पूर्णांक address, length, transferred;

#अगर (DEBUG & DEBUG_DMA)
    DBG(host->SCpnt, acornscsi_dumpdma(host, "inti"));
#पूर्ण_अगर

    dmac_ग_लिखो(host, DMAC_MASKREG, MASK_ON);
    dmac_clearपूर्णांकr(host);

    /*
     * Calculate amount transferred via DMA
     */
    transferred = dmac_address(host) - host->dma.start_addr;
    host->dma.transferred += transferred;

    /*
     * Schedule DMA transfer off board
     */
    अगर (host->dma.direction == DMA_IN) अणु
	host->dma.xfer_start = host->dma.start_addr;
	host->dma.xfer_length = transferred;
	host->dma.xfer_ptr = host->scsi.SCp.ptr;
	host->dma.xfer_required = 1;
    पूर्ण

    acornscsi_data_updateptr(host, &host->scsi.SCp, transferred);

    /*
     * Allocate some buffer space, limited to half the on-board RAM size
     */
    length = min_t(अचिन्हित पूर्णांक, host->scsi.SCp.this_residual, DMAC_BUFFER_SIZE / 2);
    अगर (length) अणु
	host->dma.start_addr = address = host->dma.मुक्त_addr;
	host->dma.मुक्त_addr = (host->dma.मुक्त_addr + length) &
				(DMAC_BUFFER_SIZE - 1);

	/*
	 * Transfer data to DMA memory
	 */
	अगर (host->dma.direction == DMA_OUT)
	    acornscsi_data_ग_लिखो(host, host->scsi.SCp.ptr, host->dma.start_addr,
				length);

	length -= 1;
	dmac_ग_लिखो(host, DMAC_TXCNTLO, length);
	dmac_ग_लिखो(host, DMAC_TXCNTHI, length >> 8);
	dmac_ग_लिखो(host, DMAC_TXADRLO, address);
	dmac_ग_लिखो(host, DMAC_TXADRMD, address >> 8);
	dmac_ग_लिखो(host, DMAC_TXADRHI, 0);
	dmac_ग_लिखो(host, DMAC_MASKREG, MASK_OFF);

#अगर (DEBUG & DEBUG_DMA)
	DBG(host->SCpnt, acornscsi_dumpdma(host, "into"));
#पूर्ण_अगर
    पूर्ण अन्यथा अणु
	host->dma.xfer_setup = 0;
#अगर 0
	/*
	 * If the पूर्णांकerface still wants more, then this is an error.
	 * We give it another byte, but we also attempt to उठाओ an
	 * attention condition.  We जारी giving one byte until
	 * the device recognises the attention.
	 */
	अगर (dmac_पढ़ो(host, DMAC_STATUS) & STATUS_RQ0) अणु
	    acornscsi_पातcmd(host, host->SCpnt->tag);

	    dmac_ग_लिखो(host, DMAC_TXCNTLO, 0);
	    dmac_ग_लिखो(host, DMAC_TXCNTHI, 0);
	    dmac_ग_लिखो(host, DMAC_TXADRLO, 0);
	    dmac_ग_लिखो(host, DMAC_TXADRMD, 0);
	    dmac_ग_लिखो(host, DMAC_TXADRHI, 0);
	    dmac_ग_लिखो(host, DMAC_MASKREG, MASK_OFF);
	पूर्ण
#पूर्ण_अगर
    पूर्ण
पूर्ण

/*
 * Function: व्योम acornscsi_dma_xfer(AS_Host *host)
 * Purpose : transfer data between AcornSCSI and memory
 * Params  : host - host to process
 */
अटल
व्योम acornscsi_dma_xfer(AS_Host *host)
अणु
    host->dma.xfer_required = 0;

    अगर (host->dma.direction == DMA_IN)
	acornscsi_data_पढ़ो(host, host->dma.xfer_ptr,
				host->dma.xfer_start, host->dma.xfer_length);
पूर्ण

/*
 * Function: व्योम acornscsi_dma_adjust(AS_Host *host)
 * Purpose : adjust DMA poपूर्णांकers & count क्रम bytes transferred to
 *	     SBIC but not SCSI bus.
 * Params  : host - host to adjust DMA count क्रम
 */
अटल
व्योम acornscsi_dma_adjust(AS_Host *host)
अणु
    अगर (host->dma.xfer_setup) अणु
	चिन्हित दीर्घ transferred;
#अगर (DEBUG & (DEBUG_DMA|DEBUG_WRITE))
	DBG(host->SCpnt, acornscsi_dumpdma(host, "adji"));
#पूर्ण_अगर
	/*
	 * Calculate correct DMA address - DMA is ahead of SCSI bus जबतक
	 * writing.
	 *  host->scsi.SCp.scsi_xferred is the number of bytes
	 *  actually transferred to/from the SCSI bus.
	 *  host->dma.transferred is the number of bytes transferred
	 *  over DMA since host->dma.start_addr was last set.
	 *
	 * real_dma_addr = host->dma.start_addr + host->scsi.SCp.scsi_xferred
	 *		   - host->dma.transferred
	 */
	transferred = host->scsi.SCp.scsi_xferred - host->dma.transferred;
	अगर (transferred < 0)
	    prपूर्णांकk("scsi%d.%c: Ack! DMA write correction %ld < 0!\n",
		    host->host->host_no, acornscsi_target(host), transferred);
	अन्यथा अगर (transferred == 0)
	    host->dma.xfer_setup = 0;
	अन्यथा अणु
	    transferred += host->dma.start_addr;
	    dmac_ग_लिखो(host, DMAC_TXADRLO, transferred);
	    dmac_ग_लिखो(host, DMAC_TXADRMD, transferred >> 8);
	    dmac_ग_लिखो(host, DMAC_TXADRHI, transferred >> 16);
#अगर (DEBUG & (DEBUG_DMA|DEBUG_WRITE))
	    DBG(host->SCpnt, acornscsi_dumpdma(host, "adjo"));
#पूर्ण_अगर
	पूर्ण
    पूर्ण
पूर्ण
#पूर्ण_अगर

/* =========================================================================================
 * Data I/O
 */
अटल पूर्णांक
acornscsi_ग_लिखो_pio(AS_Host *host, अक्षर *bytes, पूर्णांक *ptr, पूर्णांक len, अचिन्हित पूर्णांक max_समयout)
अणु
	अचिन्हित पूर्णांक asr, समयout = max_समयout;
	पूर्णांक my_ptr = *ptr;

	जबतक (my_ptr < len) अणु
		asr = sbic_arm_पढ़ो(host, SBIC_ASR);

		अगर (asr & ASR_DBR) अणु
			समयout = max_समयout;

			sbic_arm_ग_लिखो(host, SBIC_DATA, bytes[my_ptr++]);
		पूर्ण अन्यथा अगर (asr & ASR_INT)
			अवरोध;
		अन्यथा अगर (--समयout == 0)
			अवरोध;
		udelay(1);
	पूर्ण

	*ptr = my_ptr;

	वापस (समयout == 0) ? -1 : 0;
पूर्ण

/*
 * Function: व्योम acornscsi_sendcommand(AS_Host *host)
 * Purpose : send a command to a target
 * Params  : host - host which is connected to target
 */
अटल व्योम
acornscsi_sendcommand(AS_Host *host)
अणु
	काष्ठा scsi_cmnd *SCpnt = host->SCpnt;

    sbic_arm_ग_लिखो(host, SBIC_TRANSCNTH, 0);
    sbic_arm_ग_लिखोnext(host, 0);
    sbic_arm_ग_लिखोnext(host, SCpnt->cmd_len - host->scsi.SCp.sent_command);

    acornscsi_sbic_issuecmd(host, CMND_XFERINFO);

    अगर (acornscsi_ग_लिखो_pio(host, SCpnt->cmnd,
	(पूर्णांक *)&host->scsi.SCp.sent_command, SCpnt->cmd_len, 1000000))
	prपूर्णांकk("scsi%d: timeout while sending command\n", host->host->host_no);

    host->scsi.phase = PHASE_COMMAND;
पूर्ण

अटल
व्योम acornscsi_sendmessage(AS_Host *host)
अणु
    अचिन्हित पूर्णांक message_length = msgqueue_msglength(&host->scsi.msgs);
    अचिन्हित पूर्णांक msgnr;
    काष्ठा message *msg;

#अगर (DEBUG & DEBUG_MESSAGES)
    prपूर्णांकk("scsi%d.%c: sending message ",
	    host->host->host_no, acornscsi_target(host));
#पूर्ण_अगर

    चयन (message_length) अणु
    हाल 0:
	acornscsi_sbic_issuecmd(host, CMND_XFERINFO | CMND_SBT);

	acornscsi_sbic_रुको(host, ASR_DBR, ASR_DBR, 1000, "sending message 1");

	sbic_arm_ग_लिखो(host, SBIC_DATA, NOP);

	host->scsi.last_message = NOP;
#अगर (DEBUG & DEBUG_MESSAGES)
	prपूर्णांकk("NOP");
#पूर्ण_अगर
	अवरोध;

    हाल 1:
	acornscsi_sbic_issuecmd(host, CMND_XFERINFO | CMND_SBT);
	msg = msgqueue_geपंचांगsg(&host->scsi.msgs, 0);

	acornscsi_sbic_रुको(host, ASR_DBR, ASR_DBR, 1000, "sending message 2");

	sbic_arm_ग_लिखो(host, SBIC_DATA, msg->msg[0]);

	host->scsi.last_message = msg->msg[0];
#अगर (DEBUG & DEBUG_MESSAGES)
	spi_prपूर्णांक_msg(msg->msg);
#पूर्ण_अगर
	अवरोध;

    शेष:
	/*
	 * ANSI standard says: (SCSI-2 Rev 10c Sect 5.6.14)
	 * 'When a target sends this (MESSAGE_REJECT) message, it
	 *  shall change to MESSAGE IN phase and send this message
	 *  prior to requesting additional message bytes from the
	 *  initiator.  This provides an पूर्णांकerlock so that the
	 *  initiator can determine which message byte is rejected.
	 */
	sbic_arm_ग_लिखो(host, SBIC_TRANSCNTH, 0);
	sbic_arm_ग_लिखोnext(host, 0);
	sbic_arm_ग_लिखोnext(host, message_length);
	acornscsi_sbic_issuecmd(host, CMND_XFERINFO);

	msgnr = 0;
	जबतक ((msg = msgqueue_geपंचांगsg(&host->scsi.msgs, msgnr++)) != शून्य) अणु
	    अचिन्हित पूर्णांक i;
#अगर (DEBUG & DEBUG_MESSAGES)
	    spi_prपूर्णांक_msg(msg);
#पूर्ण_अगर
	    i = 0;
	    अगर (acornscsi_ग_लिखो_pio(host, msg->msg, &i, msg->length, 1000000))
		prपूर्णांकk("scsi%d: timeout while sending message\n", host->host->host_no);

	    host->scsi.last_message = msg->msg[0];
	    अगर (msg->msg[0] == EXTENDED_MESSAGE)
		host->scsi.last_message |= msg->msg[2] << 8;

	    अगर (i != msg->length)
		अवरोध;
	पूर्ण
	अवरोध;
    पूर्ण
#अगर (DEBUG & DEBUG_MESSAGES)
    prपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण

/*
 * Function: व्योम acornscsi_पढ़ोstatusbyte(AS_Host *host)
 * Purpose : Read status byte from connected target
 * Params  : host - host connected to target
 */
अटल
व्योम acornscsi_पढ़ोstatusbyte(AS_Host *host)
अणु
    acornscsi_sbic_issuecmd(host, CMND_XFERINFO|CMND_SBT);
    acornscsi_sbic_रुको(host, ASR_DBR, ASR_DBR, 1000, "reading status byte");
    host->scsi.SCp.Status = sbic_arm_पढ़ो(host, SBIC_DATA);
पूर्ण

/*
 * Function: अचिन्हित अक्षर acornscsi_पढ़ोmessagebyte(AS_Host *host)
 * Purpose : Read one message byte from connected target
 * Params  : host - host connected to target
 */
अटल
अचिन्हित अक्षर acornscsi_पढ़ोmessagebyte(AS_Host *host)
अणु
    अचिन्हित अक्षर message;

    acornscsi_sbic_issuecmd(host, CMND_XFERINFO | CMND_SBT);

    acornscsi_sbic_रुको(host, ASR_DBR, ASR_DBR, 1000, "for message byte");

    message = sbic_arm_पढ़ो(host, SBIC_DATA);

    /* रुको क्रम MSGIN-XFER-PAUSED */
    acornscsi_sbic_रुको(host, ASR_INT, ASR_INT, 1000, "for interrupt after message byte");

    sbic_arm_पढ़ो(host, SBIC_SSR);

    वापस message;
पूर्ण

/*
 * Function: व्योम acornscsi_message(AS_Host *host)
 * Purpose : Read complete message from connected target & action message
 * Params  : host - host connected to target
 */
अटल
व्योम acornscsi_message(AS_Host *host)
अणु
    अचिन्हित अक्षर message[16];
    अचिन्हित पूर्णांक msgidx = 0, msglen = 1;

    करो अणु
	message[msgidx] = acornscsi_पढ़ोmessagebyte(host);

	चयन (msgidx) अणु
	हाल 0:
	    अगर (message[0] == EXTENDED_MESSAGE ||
		(message[0] >= 0x20 && message[0] <= 0x2f))
		msglen = 2;
	    अवरोध;

	हाल 1:
	    अगर (message[0] == EXTENDED_MESSAGE)
		msglen += message[msgidx];
	    अवरोध;
	पूर्ण
	msgidx += 1;
	अगर (msgidx < msglen) अणु
	    acornscsi_sbic_issuecmd(host, CMND_NEGATEACK);

	    /* रुको क्रम next msg-in */
	    acornscsi_sbic_रुको(host, ASR_INT, ASR_INT, 1000, "for interrupt after negate ack");
	    sbic_arm_पढ़ो(host, SBIC_SSR);
	पूर्ण
    पूर्ण जबतक (msgidx < msglen);

#अगर (DEBUG & DEBUG_MESSAGES)
    prपूर्णांकk("scsi%d.%c: message in: ",
	    host->host->host_no, acornscsi_target(host));
    spi_prपूर्णांक_msg(message);
    prपूर्णांकk("\n");
#पूर्ण_अगर

    अगर (host->scsi.phase == PHASE_RECONNECTED) अणु
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.17)
	 * 'Whenever a target reconnects to an initiator to जारी
	 *  a tagged I/O process, the SIMPLE QUEUE TAG message shall
	 *  be sent immediately following the IDENTIFY message...'
	 */
	अगर (message[0] == SIMPLE_QUEUE_TAG)
	    host->scsi.reconnected.tag = message[1];
	अगर (acornscsi_reconnect_finish(host))
	    host->scsi.phase = PHASE_MSGIN;
    पूर्ण

    चयन (message[0]) अणु
    हाल ABORT_TASK_SET:
    हाल ABORT_TASK:
    हाल COMMAND_COMPLETE:
	अगर (host->scsi.phase != PHASE_STATUSIN) अणु
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: command complete following non-status in phase?\n",
		    host->host->host_no, acornscsi_target(host));
	    acornscsi_dumplog(host, host->SCpnt->device->id);
	पूर्ण
	host->scsi.phase = PHASE_DONE;
	host->scsi.SCp.Message = message[0];
	अवरोध;

    हाल SAVE_POINTERS:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.20)
	 * 'The SAVE DATA POINTER message is sent from a target to
	 *  direct the initiator to copy the active data poपूर्णांकer to
	 *  the saved data poपूर्णांकer क्रम the current I/O process.
	 */
	acornscsi_dma_cleanup(host);
	host->SCpnt->SCp = host->scsi.SCp;
	host->SCpnt->SCp.sent_command = 0;
	host->scsi.phase = PHASE_MSGIN;
	अवरोध;

    हाल RESTORE_POINTERS:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.19)
	 * 'The RESTORE POINTERS message is sent from a target to
	 *  direct the initiator to copy the most recently saved
	 *  command, data, and status poपूर्णांकers क्रम the I/O process
	 *  to the corresponding active poपूर्णांकers.  The command and
	 *  status poपूर्णांकers shall be restored to the beginning of
	 *  the present command and status areas.'
	 */
	acornscsi_dma_cleanup(host);
	host->scsi.SCp = host->SCpnt->SCp;
	host->scsi.phase = PHASE_MSGIN;
	अवरोध;

    हाल DISCONNECT:
	/*
	 * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 6.4.2)
	 * 'On those occasions when an error or exception condition occurs
	 *  and the target elects to repeat the inक्रमmation transfer, the
	 *  target may repeat the transfer either issuing a RESTORE POINTERS
	 *  message or by disconnecting without issuing a SAVE POINTERS
	 *  message.  When reconnection is completed, the most recent
	 *  saved poपूर्णांकer values are restored.'
	 */
	acornscsi_dma_cleanup(host);
	host->scsi.phase = PHASE_DISCONNECT;
	अवरोध;

    हाल MESSAGE_REJECT:
#अगर 0 /* this isn't needed any more */
	/*
	 * If we were negociating sync transfer, we करोn't yet know अगर
	 * this REJECT is क्रम the sync transfer or क्रम the tagged queue/wide
	 * transfer.  Re-initiate sync transfer negotiation now, and अगर
	 * we got a REJECT in response to SDTR, then it'll be set to DONE.
	 */
	अगर (host->device[host->SCpnt->device->id].sync_state == SYNC_SENT_REQUEST)
	    host->device[host->SCpnt->device->id].sync_state = SYNC_NEGOCIATE;
#पूर्ण_अगर

	/*
	 * If we have any messages रुकोing to go out, then निश्चित ATN now
	 */
	अगर (msgqueue_msglength(&host->scsi.msgs))
	    acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);

	चयन (host->scsi.last_message) अणु
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
	हाल HEAD_OF_QUEUE_TAG:
	हाल ORDERED_QUEUE_TAG:
	हाल SIMPLE_QUEUE_TAG:
	    /*
	     * ANSI standard says: (Section SCSI-2 Rev. 10c Sect 5.6.17)
	     *  If a target करोes not implement tagged queuing and a queue tag
	     *  message is received, it shall respond with a MESSAGE REJECT
	     *  message and accept the I/O process as अगर it were untagged.
	     */
	    prपूर्णांकk(KERN_NOTICE "scsi%d.%c: disabling tagged queueing\n",
		    host->host->host_no, acornscsi_target(host));
	    host->SCpnt->device->simple_tags = 0;
	    set_bit(host->SCpnt->device->id * 8 +
		    (u8)(host->SCpnt->device->lun & 0x7), host->busyluns);
	    अवरोध;
#पूर्ण_अगर
	हाल EXTENDED_MESSAGE | (EXTENDED_SDTR << 8):
	    /*
	     * Target can't handle synchronous transfers
	     */
	    prपूर्णांकk(KERN_NOTICE "scsi%d.%c: Using asynchronous transfer\n",
		    host->host->host_no, acornscsi_target(host));
	    host->device[host->SCpnt->device->id].sync_xfer = SYNCHTRANSFER_2DBA;
	    host->device[host->SCpnt->device->id].sync_state = SYNC_ASYNCHRONOUS;
	    sbic_arm_ग_लिखो(host, SBIC_SYNCHTRANSFER, host->device[host->SCpnt->device->id].sync_xfer);
	    अवरोध;

	शेष:
	    अवरोध;
	पूर्ण
	अवरोध;

    हाल SIMPLE_QUEUE_TAG:
	/* tag queue reconnect... message[1] = queue tag.  Prपूर्णांक something to indicate something happened! */
	prपूर्णांकk("scsi%d.%c: reconnect queue tag %02X\n",
		host->host->host_no, acornscsi_target(host),
		message[1]);
	अवरोध;

    हाल EXTENDED_MESSAGE:
	चयन (message[2]) अणु
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_SYNC
	हाल EXTENDED_SDTR:
	    अगर (host->device[host->SCpnt->device->id].sync_state == SYNC_SENT_REQUEST) अणु
		/*
		 * We requested synchronous transfers.  This isn't quite right...
		 * We can only say अगर this succeeded अगर we proceed on to execute the
		 * command from this message.  If we get a MESSAGE PARITY ERROR,
		 * and the target retries fail, then we fallback to asynchronous mode
		 */
		host->device[host->SCpnt->device->id].sync_state = SYNC_COMPLETED;
		prपूर्णांकk(KERN_NOTICE "scsi%d.%c: Using synchronous transfer, offset %d, %d ns\n",
			host->host->host_no, acornscsi_target(host),
			message[4], message[3] * 4);
		host->device[host->SCpnt->device->id].sync_xfer =
			calc_sync_xfer(message[3] * 4, message[4]);
	    पूर्ण अन्यथा अणु
		अचिन्हित अक्षर period, length;
		/*
		 * Target requested synchronous transfers.  The agreement is only
		 * to be in operation AFTER the target leaves message out phase.
		 */
		acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
		period = max_t(अचिन्हित पूर्णांक, message[3], sdtr_period / 4);
		length = min_t(अचिन्हित पूर्णांक, message[4], sdtr_size);
		msgqueue_addmsg(&host->scsi.msgs, 5, EXTENDED_MESSAGE, 3,
				 EXTENDED_SDTR, period, length);
		host->device[host->SCpnt->device->id].sync_xfer =
			calc_sync_xfer(period * 4, length);
	    पूर्ण
	    sbic_arm_ग_लिखो(host, SBIC_SYNCHTRANSFER, host->device[host->SCpnt->device->id].sync_xfer);
	    अवरोध;
#अन्यथा
	    /* We करो not accept synchronous transfers.  Respond with a
	     * MESSAGE_REJECT.
	     */
#पूर्ण_अगर

	हाल EXTENDED_WDTR:
	    /* The WD33C93A is only 8-bit.  We respond with a MESSAGE_REJECT
	     * to a wide data transfer request.
	     */
	शेष:
	    acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
	    msgqueue_flush(&host->scsi.msgs);
	    msgqueue_addmsg(&host->scsi.msgs, 1, MESSAGE_REJECT);
	    अवरोध;
	पूर्ण
	अवरोध;

    शेष: /* reject message */
	prपूर्णांकk(KERN_ERR "scsi%d.%c: unrecognised message %02X, rejecting\n",
		host->host->host_no, acornscsi_target(host),
		message[0]);
	acornscsi_sbic_issuecmd(host, CMND_ASSERTATN);
	msgqueue_flush(&host->scsi.msgs);
	msgqueue_addmsg(&host->scsi.msgs, 1, MESSAGE_REJECT);
	host->scsi.phase = PHASE_MSGIN;
	अवरोध;
    पूर्ण
    acornscsi_sbic_issuecmd(host, CMND_NEGATEACK);
पूर्ण

/*
 * Function: पूर्णांक acornscsi_buildmessages(AS_Host *host)
 * Purpose : build the connection messages क्रम a host
 * Params  : host - host to add messages to
 */
अटल
व्योम acornscsi_buildmessages(AS_Host *host)
अणु
#अगर 0
    /* करोes the device need resetting? */
    अगर (cmd_reset) अणु
	msgqueue_addmsg(&host->scsi.msgs, 1, BUS_DEVICE_RESET);
	वापस;
    पूर्ण
#पूर्ण_अगर

    msgqueue_addmsg(&host->scsi.msgs, 1,
		     IDENTIFY(host->device[host->SCpnt->device->id].disconnect_ok,
			     host->SCpnt->device->lun));

#अगर 0
    /* करोes the device need the current command पातed */
    अगर (cmd_पातed) अणु
	acornscsi_पातcmd(host->SCpnt->tag);
	वापस;
    पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    अगर (host->SCpnt->tag) अणु
	अचिन्हित पूर्णांक tag_type;

	अगर (host->SCpnt->cmnd[0] == REQUEST_SENSE ||
	    host->SCpnt->cmnd[0] == TEST_UNIT_READY ||
	    host->SCpnt->cmnd[0] == INQUIRY)
	    tag_type = HEAD_OF_QUEUE_TAG;
	अन्यथा
	    tag_type = SIMPLE_QUEUE_TAG;
	msgqueue_addmsg(&host->scsi.msgs, 2, tag_type, host->SCpnt->tag);
    पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCSI_ACORNSCSI_SYNC
    अगर (host->device[host->SCpnt->device->id].sync_state == SYNC_NEGOCIATE) अणु
	host->device[host->SCpnt->device->id].sync_state = SYNC_SENT_REQUEST;
	msgqueue_addmsg(&host->scsi.msgs, 5,
			 EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
			 sdtr_period / 4, sdtr_size);
    पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Function: पूर्णांक acornscsi_starttransfer(AS_Host *host)
 * Purpose : transfer data to/from connected target
 * Params  : host - host to which target is connected
 * Returns : 0 अगर failure
 */
अटल
पूर्णांक acornscsi_starttransfer(AS_Host *host)
अणु
    पूर्णांक residual;

    अगर (!host->scsi.SCp.ptr /*&& host->scsi.SCp.this_residual*/) अणु
	prपूर्णांकk(KERN_ERR "scsi%d.%c: null buffer passed to acornscsi_starttransfer\n",
		host->host->host_no, acornscsi_target(host));
	वापस 0;
    पूर्ण

    residual = scsi_bufflen(host->SCpnt) - host->scsi.SCp.scsi_xferred;

    sbic_arm_ग_लिखो(host, SBIC_SYNCHTRANSFER, host->device[host->SCpnt->device->id].sync_xfer);
    sbic_arm_ग_लिखोnext(host, residual >> 16);
    sbic_arm_ग_लिखोnext(host, residual >> 8);
    sbic_arm_ग_लिखोnext(host, residual);
    acornscsi_sbic_issuecmd(host, CMND_XFERINFO);
    वापस 1;
पूर्ण

/* =========================================================================================
 * Connection & Disconnection
 */
/*
 * Function : acornscsi_reconnect(AS_Host *host)
 * Purpose  : reconnect a previously disconnected command
 * Params   : host - host specअगरic data
 * Remarks  : SCSI spec says:
 *		'The set of active poपूर्णांकers is restored from the set
 *		 of saved poपूर्णांकers upon reconnection of the I/O process'
 */
अटल
पूर्णांक acornscsi_reconnect(AS_Host *host)
अणु
    अचिन्हित पूर्णांक target, lun, ok = 0;

    target = sbic_arm_पढ़ो(host, SBIC_SOURCEID);

    अगर (!(target & 8))
	prपूर्णांकk(KERN_ERR "scsi%d: invalid source id after reselection "
		"- device fault?\n",
		host->host->host_no);

    target &= 7;

    अगर (host->SCpnt && !host->scsi.disconnectable) अणु
	prपूर्णांकk(KERN_ERR "scsi%d.%d: reconnected while command in "
		"progress to target %d?\n",
		host->host->host_no, target, host->SCpnt->device->id);
	host->SCpnt = शून्य;
    पूर्ण

    lun = sbic_arm_पढ़ो(host, SBIC_DATA) & 7;

    host->scsi.reconnected.target = target;
    host->scsi.reconnected.lun = lun;
    host->scsi.reconnected.tag = 0;

    अगर (host->scsi.disconnectable && host->SCpnt &&
	host->SCpnt->device->id == target && host->SCpnt->device->lun == lun)
	ok = 1;

    अगर (!ok && queue_probetgtlun(&host->queues.disconnected, target, lun))
	ok = 1;

    ADD_STATUS(target, 0x81, host->scsi.phase, 0);

    अगर (ok) अणु
	host->scsi.phase = PHASE_RECONNECTED;
    पूर्ण अन्यथा अणु
	/* this करोesn't seem to work */
	prपूर्णांकk(KERN_ERR "scsi%d.%c: reselected with no command "
		"to reconnect with\n",
		host->host->host_no, '0' + target);
	acornscsi_dumplog(host, target);
	acornscsi_पातcmd(host, 0);
	अगर (host->SCpnt) अणु
	    queue_add_cmd_tail(&host->queues.disconnected, host->SCpnt);
	    host->SCpnt = शून्य;
	पूर्ण
    पूर्ण
    acornscsi_sbic_issuecmd(host, CMND_NEGATEACK);
    वापस !ok;
पूर्ण

/*
 * Function: पूर्णांक acornscsi_reconnect_finish(AS_Host *host)
 * Purpose : finish reconnecting a command
 * Params  : host - host to complete
 * Returns : 0 अगर failed
 */
अटल
पूर्णांक acornscsi_reconnect_finish(AS_Host *host)
अणु
    अगर (host->scsi.disconnectable && host->SCpnt) अणु
	host->scsi.disconnectable = 0;
	अगर (host->SCpnt->device->id  == host->scsi.reconnected.target &&
	    host->SCpnt->device->lun == host->scsi.reconnected.lun &&
	    host->SCpnt->tag         == host->scsi.reconnected.tag) अणु
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	    DBG(host->SCpnt, prपूर्णांकk("scsi%d.%c: reconnected",
		    host->host->host_no, acornscsi_target(host)));
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
	    queue_add_cmd_tail(&host->queues.disconnected, host->SCpnt);
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	    DBG(host->SCpnt, prपूर्णांकk("scsi%d.%c: had to move command "
		    "to disconnected queue\n",
		    host->host->host_no, acornscsi_target(host)));
#पूर्ण_अगर
	    host->SCpnt = शून्य;
	पूर्ण
    पूर्ण
    अगर (!host->SCpnt) अणु
	host->SCpnt = queue_हटाओ_tgtluntag(&host->queues.disconnected,
				host->scsi.reconnected.target,
				host->scsi.reconnected.lun,
				host->scsi.reconnected.tag);
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	DBG(host->SCpnt, prपूर्णांकk("scsi%d.%c: had to get command",
		host->host->host_no, acornscsi_target(host)));
#पूर्ण_अगर
    पूर्ण

    अगर (!host->SCpnt)
	acornscsi_पातcmd(host, host->scsi.reconnected.tag);
    अन्यथा अणु
	/*
	 * Restore data poपूर्णांकer from SAVED poपूर्णांकers.
	 */
	host->scsi.SCp = host->SCpnt->SCp;
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	prपूर्णांकk(", data pointers: [%p, %X]",
		host->scsi.SCp.ptr, host->scsi.SCp.this_residual);
#पूर्ण_अगर
    पूर्ण
#अगर (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
    prपूर्णांकk("\n");
#पूर्ण_अगर

    host->dma.transferred = host->scsi.SCp.scsi_xferred;

    वापस host->SCpnt != शून्य;
पूर्ण

/*
 * Function: व्योम acornscsi_disconnect_unexpected(AS_Host *host)
 * Purpose : handle an unexpected disconnect
 * Params  : host - host on which disconnect occurred
 */
अटल
व्योम acornscsi_disconnect_unexpected(AS_Host *host)
अणु
    prपूर्णांकk(KERN_ERR "scsi%d.%c: unexpected disconnect\n",
	    host->host->host_no, acornscsi_target(host));
#अगर (DEBUG & DEBUG_ABORT)
    acornscsi_dumplog(host, 8);
#पूर्ण_अगर

    acornscsi_करोne(host, &host->SCpnt, DID_ERROR);
पूर्ण

/*
 * Function: व्योम acornscsi_पातcmd(AS_host *host, अचिन्हित अक्षर tag)
 * Purpose : पात a currently executing command
 * Params  : host - host with connected command to पात
 *	     tag  - tag to पात
 */
अटल
व्योम acornscsi_पातcmd(AS_Host *host, अचिन्हित अक्षर tag)
अणु
    host->scsi.phase = PHASE_ABORTED;
    sbic_arm_ग_लिखो(host, SBIC_CMND, CMND_ASSERTATN);

    msgqueue_flush(&host->scsi.msgs);
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    अगर (tag)
	msgqueue_addmsg(&host->scsi.msgs, 2, ABORT_TAG, tag);
    अन्यथा
#पूर्ण_अगर
	msgqueue_addmsg(&host->scsi.msgs, 1, ABORT);
पूर्ण

/* ==========================================================================================
 * Interrupt routines.
 */
/*
 * Function: पूर्णांक acornscsi_sbicपूर्णांकr(AS_Host *host)
 * Purpose : handle पूर्णांकerrupts from SCSI device
 * Params  : host - host to process
 * Returns : INTR_PROCESS अगर expecting another SBIC पूर्णांकerrupt
 *	     INTR_IDLE अगर no पूर्णांकerrupt
 *	     INTR_NEXT_COMMAND अगर we have finished processing the command
 */
अटल
पूर्णांकr_ret_t acornscsi_sbicपूर्णांकr(AS_Host *host, पूर्णांक in_irq)
अणु
    अचिन्हित पूर्णांक asr, ssr;

    asr = sbic_arm_पढ़ो(host, SBIC_ASR);
    अगर (!(asr & ASR_INT))
	वापस INTR_IDLE;

    ssr = sbic_arm_पढ़ो(host, SBIC_SSR);

#अगर (DEBUG & DEBUG_PHASES)
    prपूर्णांक_sbic_status(asr, ssr, host->scsi.phase);
#पूर्ण_अगर

    ADD_STATUS(8, ssr, host->scsi.phase, in_irq);

    अगर (host->SCpnt && !host->scsi.disconnectable)
	ADD_STATUS(host->SCpnt->device->id, ssr, host->scsi.phase, in_irq);

    चयन (ssr) अणु
    हाल 0x00:				/* reset state - not advanced			*/
	prपूर्णांकk(KERN_ERR "scsi%d: reset in standard mode but wanted advanced mode.\n",
		host->host->host_no);
	/* setup sbic - WD33C93A */
	sbic_arm_ग_लिखो(host, SBIC_OWNID, OWNID_EAF | host->host->this_id);
	sbic_arm_ग_लिखो(host, SBIC_CMND, CMND_RESET);
	वापस INTR_IDLE;

    हाल 0x01:				/* reset state - advanced			*/
	sbic_arm_ग_लिखो(host, SBIC_CTRL, INIT_SBICDMA | CTRL_IDI);
	sbic_arm_ग_लिखो(host, SBIC_TIMEOUT, TIMEOUT_TIME);
	sbic_arm_ग_लिखो(host, SBIC_SYNCHTRANSFER, SYNCHTRANSFER_2DBA);
	sbic_arm_ग_लिखो(host, SBIC_SOURCEID, SOURCEID_ER | SOURCEID_DSP);
	msgqueue_flush(&host->scsi.msgs);
	वापस INTR_IDLE;

    हाल 0x41:				/* unexpected disconnect पातed command	*/
	acornscsi_disconnect_unexpected(host);
	वापस INTR_NEXT_COMMAND;
    पूर्ण

    चयन (host->scsi.phase) अणु
    हाल PHASE_CONNECTING:		/* STATE: command हटाओd from issue queue	*/
	चयन (ssr) अणु
	हाल 0x11:			/* -> PHASE_CONNECTED				*/
	    /* BUS FREE -> SELECTION */
	    host->scsi.phase = PHASE_CONNECTED;
	    msgqueue_flush(&host->scsi.msgs);
	    host->dma.transferred = host->scsi.SCp.scsi_xferred;
	    /* 33C93 gives next पूर्णांकerrupt indicating bus phase */
	    asr = sbic_arm_पढ़ो(host, SBIC_ASR);
	    अगर (!(asr & ASR_INT))
		अवरोध;
	    ssr = sbic_arm_पढ़ो(host, SBIC_SSR);
	    ADD_STATUS(8, ssr, host->scsi.phase, 1);
	    ADD_STATUS(host->SCpnt->device->id, ssr, host->scsi.phase, 1);
	    जाओ connected;
	    
	हाल 0x42:			/* select समयd out				*/
					/* -> PHASE_IDLE				*/
	    acornscsi_करोne(host, &host->SCpnt, DID_NO_CONNECT);
	    वापस INTR_NEXT_COMMAND;

	हाल 0x81:			/* -> PHASE_RECONNECTED or PHASE_ABORTED	*/
	    /* BUS FREE -> RESELECTION */
	    host->origSCpnt = host->SCpnt;
	    host->SCpnt = शून्य;
	    msgqueue_flush(&host->scsi.msgs);
	    acornscsi_reconnect(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_CONNECTING, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	    acornscsi_पातcmd(host, host->SCpnt->tag);
	पूर्ण
	वापस INTR_PROCESSING;

    connected:
    हाल PHASE_CONNECTED:		/* STATE: device selected ok			*/
	चयन (ssr) अणु
#अगर_घोषित NONSTANDARD
	हाल 0x8a:			/* -> PHASE_COMMAND, PHASE_COMMANDPAUSED	*/
	    /* SELECTION -> COMMAND */
	    acornscsi_sendcommand(host);
	    अवरोध;

	हाल 0x8b:			/* -> PHASE_STATUS				*/
	    /* SELECTION -> STATUS */
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;
#पूर्ण_अगर

	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* SELECTION ->MESSAGE OUT */
	    host->scsi.phase = PHASE_MSGOUT;
	    acornscsi_buildmessages(host);
	    acornscsi_sendmessage(host);
	    अवरोध;

	/* these should not happen */
	हाल 0x85:			/* target disconnected				*/
	    acornscsi_करोne(host, &host->SCpnt, DID_ERROR);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_CONNECTED, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	    acornscsi_पातcmd(host, host->SCpnt->tag);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_MSGOUT:			/* STATE: connected & sent IDENTIFY message	*/
	/*
	 * SCSI standard says that MESSAGE OUT phases can be followed by a
	 * DATA phase, STATUS phase, MESSAGE IN phase or COMMAND phase
	 */
	चयन (ssr) अणु
	हाल 0x8a:			/* -> PHASE_COMMAND, PHASE_COMMANDPAUSED	*/
	हाल 0x1a:			/* -> PHASE_COMMAND, PHASE_COMMANDPAUSED	*/
	    /* MESSAGE OUT -> COMMAND */
	    acornscsi_sendcommand(host);
	    अवरोध;

	हाल 0x8b:			/* -> PHASE_STATUS				*/
	हाल 0x1b:			/* -> PHASE_STATUS				*/
	    /* MESSAGE OUT -> STATUS */
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;

	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* MESSAGE_OUT(MESSAGE_IN) ->MESSAGE OUT */
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x4f:			/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	हाल 0x1f:			/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	    /* MESSAGE OUT -> MESSAGE IN */
	    acornscsi_message(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_MSGOUT, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_COMMAND: 		/* STATE: connected & command sent		*/
	चयन (ssr) अणु
	हाल 0x18:			/* -> PHASE_DATAOUT				*/
	    /* COMMAND -> DATA OUT */
	    अगर (host->scsi.SCp.sent_command != host->SCpnt->cmd_len)
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    acornscsi_dma_setup(host, DMA_OUT);
	    अगर (!acornscsi_starttransfer(host))
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    host->scsi.phase = PHASE_DATAOUT;
	    वापस INTR_IDLE;

	हाल 0x19:			/* -> PHASE_DATAIN				*/
	    /* COMMAND -> DATA IN */
	    अगर (host->scsi.SCp.sent_command != host->SCpnt->cmd_len)
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    acornscsi_dma_setup(host, DMA_IN);
	    अगर (!acornscsi_starttransfer(host))
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    host->scsi.phase = PHASE_DATAIN;
	    वापस INTR_IDLE;

	हाल 0x1b:			/* -> PHASE_STATUS				*/
	    /* COMMAND -> STATUS */
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;

	हाल 0x1e:			/* -> PHASE_MSGOUT				*/
	    /* COMMAND -> MESSAGE OUT */
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x1f:			/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	    /* COMMAND -> MESSAGE IN */
	    acornscsi_message(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_COMMAND, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_DISCONNECT:		/* STATE: connected, received DISCONNECT msg	*/
	अगर (ssr == 0x85) अणु		/* -> PHASE_IDLE				*/
	    host->scsi.disconnectable = 1;
	    host->scsi.reconnected.tag = 0;
	    host->scsi.phase = PHASE_IDLE;
	    host->stats.disconnects += 1;
	पूर्ण अन्यथा अणु
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_DISCONNECT, SSR %02X instead of disconnect?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_NEXT_COMMAND;

    हाल PHASE_IDLE:			/* STATE: disconnected				*/
	अगर (ssr == 0x81)		/* -> PHASE_RECONNECTED or PHASE_ABORTED	*/
	    acornscsi_reconnect(host);
	अन्यथा अणु
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_IDLE, SSR %02X while idle?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_RECONNECTED:		/* STATE: device reconnected to initiator	*/
	/*
	 * Command reconnected - अगर MESGIN, get message - it may be
	 * the tag.  If not, get command out of disconnected queue
	 */
	/*
	 * If we reconnected and we're not in MESSAGE IN phase after IDENTIFY,
	 * reconnect I_T_L command
	 */
	अगर (ssr != 0x8f && !acornscsi_reconnect_finish(host))
	    वापस INTR_IDLE;
	ADD_STATUS(host->SCpnt->device->id, ssr, host->scsi.phase, in_irq);
	चयन (ssr) अणु
	हाल 0x88:			/* data out phase				*/
					/* -> PHASE_DATAOUT				*/
	    /* MESSAGE IN -> DATA OUT */
	    acornscsi_dma_setup(host, DMA_OUT);
	    अगर (!acornscsi_starttransfer(host))
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    host->scsi.phase = PHASE_DATAOUT;
	    वापस INTR_IDLE;

	हाल 0x89:			/* data in phase				*/
					/* -> PHASE_DATAIN				*/
	    /* MESSAGE IN -> DATA IN */
	    acornscsi_dma_setup(host, DMA_IN);
	    अगर (!acornscsi_starttransfer(host))
		acornscsi_पातcmd(host, host->SCpnt->tag);
	    host->scsi.phase = PHASE_DATAIN;
	    वापस INTR_IDLE;

	हाल 0x8a:			/* command out					*/
	    /* MESSAGE IN -> COMMAND */
	    acornscsi_sendcommand(host);/* -> PHASE_COMMAND, PHASE_COMMANDPAUSED	*/
	    अवरोध;

	हाल 0x8b:			/* status in					*/
					/* -> PHASE_STATUSIN				*/
	    /* MESSAGE IN -> STATUS */
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;

	हाल 0x8e:			/* message out					*/
					/* -> PHASE_MSGOUT				*/
	    /* MESSAGE IN -> MESSAGE OUT */
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x8f:			/* message in					*/
	    acornscsi_message(host);	/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_RECONNECTED, SSR %02X after reconnect?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_DATAIN:			/* STATE: transferred data in			*/
	/*
	 * This is simple - अगर we disconnect then the DMA address & count is
	 * correct.
	 */
	चयन (ssr) अणु
	हाल 0x19:			/* -> PHASE_DATAIN				*/
	हाल 0x89:			/* -> PHASE_DATAIN				*/
	    acornscsi_पातcmd(host, host->SCpnt->tag);
	    वापस INTR_IDLE;

	हाल 0x1b:			/* -> PHASE_STATUSIN				*/
	हाल 0x4b:			/* -> PHASE_STATUSIN				*/
	हाल 0x8b:			/* -> PHASE_STATUSIN				*/
	    /* DATA IN -> STATUS */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;

	हाल 0x1e:			/* -> PHASE_MSGOUT				*/
	हाल 0x4e:			/* -> PHASE_MSGOUT				*/
	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* DATA IN -> MESSAGE OUT */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x1f:			/* message in					*/
	हाल 0x4f:			/* message in					*/
	हाल 0x8f:			/* message in					*/
	    /* DATA IN -> MESSAGE IN */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_message(host);	/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_DATAIN, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_DATAOUT: 		/* STATE: transferred data out			*/
	/*
	 * This is more complicated - अगर we disconnect, the DMA could be 12
	 * bytes ahead of us.  We need to correct this.
	 */
	चयन (ssr) अणु
	हाल 0x18:			/* -> PHASE_DATAOUT				*/
	हाल 0x88:			/* -> PHASE_DATAOUT				*/
	    acornscsi_पातcmd(host, host->SCpnt->tag);
	    वापस INTR_IDLE;

	हाल 0x1b:			/* -> PHASE_STATUSIN				*/
	हाल 0x4b:			/* -> PHASE_STATUSIN				*/
	हाल 0x8b:			/* -> PHASE_STATUSIN				*/
	    /* DATA OUT -> STATUS */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_dma_adjust(host);
	    acornscsi_पढ़ोstatusbyte(host);
	    host->scsi.phase = PHASE_STATUSIN;
	    अवरोध;

	हाल 0x1e:			/* -> PHASE_MSGOUT				*/
	हाल 0x4e:			/* -> PHASE_MSGOUT				*/
	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* DATA OUT -> MESSAGE OUT */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_dma_adjust(host);
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x1f:			/* message in					*/
	हाल 0x4f:			/* message in					*/
	हाल 0x8f:			/* message in					*/
	    /* DATA OUT -> MESSAGE IN */
	    host->scsi.SCp.scsi_xferred = scsi_bufflen(host->SCpnt) -
					  acornscsi_sbic_xfcount(host);
	    acornscsi_dma_stop(host);
	    acornscsi_dma_adjust(host);
	    acornscsi_message(host);	/* -> PHASE_MSGIN, PHASE_DISCONNECT		*/
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_DATAOUT, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_STATUSIN:		/* STATE: status in complete			*/
	चयन (ssr) अणु
	हाल 0x1f:			/* -> PHASE_MSGIN, PHASE_DONE, PHASE_DISCONNECT */
	हाल 0x8f:			/* -> PHASE_MSGIN, PHASE_DONE, PHASE_DISCONNECT */
	    /* STATUS -> MESSAGE IN */
	    acornscsi_message(host);
	    अवरोध;

	हाल 0x1e:			/* -> PHASE_MSGOUT				*/
	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* STATUS -> MESSAGE OUT */
	    acornscsi_sendmessage(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_STATUSIN, SSR %02X instead of MESSAGE_IN?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_MSGIN:			/* STATE: message in				*/
	चयन (ssr) अणु
	हाल 0x1e:			/* -> PHASE_MSGOUT				*/
	हाल 0x4e:			/* -> PHASE_MSGOUT				*/
	हाल 0x8e:			/* -> PHASE_MSGOUT				*/
	    /* MESSAGE IN -> MESSAGE OUT */
	    acornscsi_sendmessage(host);
	    अवरोध;

	हाल 0x1f:			/* -> PHASE_MSGIN, PHASE_DONE, PHASE_DISCONNECT */
	हाल 0x2f:
	हाल 0x4f:
	हाल 0x8f:
	    acornscsi_message(host);
	    अवरोध;

	हाल 0x85:
	    prपूर्णांकk("scsi%d.%c: strange message in disconnection\n",
		host->host->host_no, acornscsi_target(host));
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	    acornscsi_करोne(host, &host->SCpnt, DID_ERROR);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_MSGIN, SSR %02X after message in?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_DONE:			/* STATE: received status & message		*/
	चयन (ssr) अणु
	हाल 0x85:			/* -> PHASE_IDLE				*/
	    acornscsi_करोne(host, &host->SCpnt, DID_OK);
	    वापस INTR_NEXT_COMMAND;

	हाल 0x1e:
	हाल 0x8e:
	    acornscsi_sendmessage(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_DONE, SSR %02X instead of disconnect?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    हाल PHASE_ABORTED:
	चयन (ssr) अणु
	हाल 0x85:
	    अगर (host->SCpnt)
		acornscsi_करोne(host, &host->SCpnt, DID_ABORT);
	    अन्यथा अणु
		clear_bit(host->scsi.reconnected.target * 8 + host->scsi.reconnected.lun,
			  host->busyluns);
		host->scsi.phase = PHASE_IDLE;
	    पूर्ण
	    वापस INTR_NEXT_COMMAND;

	हाल 0x1e:
	हाल 0x2e:
	हाल 0x4e:
	हाल 0x8e:
	    acornscsi_sendmessage(host);
	    अवरोध;

	शेष:
	    prपूर्णांकk(KERN_ERR "scsi%d.%c: PHASE_ABORTED, SSR %02X?\n",
		    host->host->host_no, acornscsi_target(host), ssr);
	    acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
	पूर्ण
	वापस INTR_PROCESSING;

    शेष:
	prपूर्णांकk(KERN_ERR "scsi%d.%c: unknown driver phase %d\n",
		host->host->host_no, acornscsi_target(host), ssr);
	acornscsi_dumplog(host, host->SCpnt ? host->SCpnt->device->id : 8);
    पूर्ण
    वापस INTR_PROCESSING;
पूर्ण

/*
 * Prototype: व्योम acornscsi_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
 * Purpose  : handle पूर्णांकerrupts from Acorn SCSI card
 * Params   : irq    - पूर्णांकerrupt number
 *	      dev_id - device specअगरic data (AS_Host काष्ठाure)
 */
अटल irqवापस_t
acornscsi_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
    AS_Host *host = (AS_Host *)dev_id;
    पूर्णांकr_ret_t ret;
    पूर्णांक iostatus;
    पूर्णांक in_irq = 0;

    करो अणु
	ret = INTR_IDLE;

	iostatus = पढ़ोb(host->fast + INT_REG);

	अगर (iostatus & 2) अणु
	    acornscsi_dma_पूर्णांकr(host);
	    iostatus = पढ़ोb(host->fast + INT_REG);
	पूर्ण

	अगर (iostatus & 8)
	    ret = acornscsi_sbicपूर्णांकr(host, in_irq);

	/*
	 * If we have a transfer pending, start it.
	 * Only start it अगर the पूर्णांकerface has alपढ़ोy started transferring
	 * it's data
	 */
	अगर (host->dma.xfer_required)
	    acornscsi_dma_xfer(host);

	अगर (ret == INTR_NEXT_COMMAND)
	    ret = acornscsi_kick(host);

	in_irq = 1;
    पूर्ण जबतक (ret != INTR_IDLE);

    वापस IRQ_HANDLED;
पूर्ण

/*=============================================================================================
 * Interfaces between पूर्णांकerrupt handler and rest of scsi code
 */

/*
 * Function : acornscsi_queuecmd(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
 * Purpose  : queues a SCSI command
 * Params   : cmd  - SCSI command
 *	      करोne - function called on completion, with poपूर्णांकer to command descriptor
 * Returns  : 0, or < 0 on error.
 */
अटल पूर्णांक acornscsi_queuecmd_lck(काष्ठा scsi_cmnd *SCpnt,
		       व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
    AS_Host *host = (AS_Host *)SCpnt->device->host->hostdata;

    अगर (!करोne) अणु
	/* there should be some way of rejecting errors like this without panicing... */
	panic("scsi%d: queuecommand called with NULL done function [cmd=%p]",
		host->host->host_no, SCpnt);
	वापस -EINVAL;
    पूर्ण

#अगर (DEBUG & DEBUG_NO_WRITE)
    अगर (acornscsi_cmdtype(SCpnt->cmnd[0]) == CMD_WRITE && (NO_WRITE & (1 << SCpnt->device->id))) अणु
	prपूर्णांकk(KERN_CRIT "scsi%d.%c: WRITE attempted with NO_WRITE flag set\n",
	    host->host->host_no, '0' + SCpnt->device->id);
	SCpnt->result = DID_NO_CONNECT << 16;
	करोne(SCpnt);
	वापस 0;
    पूर्ण
#पूर्ण_अगर

    SCpnt->scsi_करोne = करोne;
    SCpnt->host_scribble = शून्य;
    SCpnt->result = 0;
    SCpnt->tag = 0;
    SCpnt->SCp.phase = (पूर्णांक)acornscsi_datadirection(SCpnt->cmnd[0]);
    SCpnt->SCp.sent_command = 0;
    SCpnt->SCp.scsi_xferred = 0;

    init_SCp(SCpnt);

    host->stats.queues += 1;

    अणु
	अचिन्हित दीर्घ flags;

	अगर (!queue_add_cmd_ordered(&host->queues.issue, SCpnt)) अणु
	    SCpnt->result = DID_ERROR << 16;
	    करोne(SCpnt);
	    वापस 0;
	पूर्ण
	local_irq_save(flags);
	अगर (host->scsi.phase == PHASE_IDLE)
	    acornscsi_kick(host);
	local_irq_restore(flags);
    पूर्ण
    वापस 0;
पूर्ण

DEF_SCSI_QCMD(acornscsi_queuecmd)

/*
 * Prototype: व्योम acornscsi_reportstatus(काष्ठा scsi_cmnd **SCpntp1, काष्ठा scsi_cmnd **SCpntp2, पूर्णांक result)
 * Purpose  : pass a result to *SCpntp1, and check अगर *SCpntp1 = *SCpntp2
 * Params   : SCpntp1 - poपूर्णांकer to command to वापस
 *	      SCpntp2 - poपूर्णांकer to command to check
 *	      result  - result to pass back to mid-level करोne function
 * Returns  : *SCpntp2 = शून्य अगर *SCpntp1 is the same command काष्ठाure as *SCpntp2.
 */
अटल अंतरभूत व्योम acornscsi_reportstatus(काष्ठा scsi_cmnd **SCpntp1,
					  काष्ठा scsi_cmnd **SCpntp2,
					  पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *SCpnt = *SCpntp1;

    अगर (SCpnt) अणु
	*SCpntp1 = शून्य;

	SCpnt->result = result;
	SCpnt->scsi_करोne(SCpnt);
    पूर्ण

    अगर (SCpnt == *SCpntp2)
	*SCpntp2 = शून्य;
पूर्ण

क्रमागत res_पात अणु res_not_running, res_success, res_success_clear, res_snooze पूर्ण;

/*
 * Prototype: क्रमागत res acornscsi_करो_पात(काष्ठा scsi_cmnd *SCpnt)
 * Purpose  : पात a command on this host
 * Params   : SCpnt - command to पात
 * Returns  : our पात status
 */
अटल क्रमागत res_पात acornscsi_करो_पात(AS_Host *host, काष्ठा scsi_cmnd *SCpnt)
अणु
	क्रमागत res_पात res = res_not_running;

	अगर (queue_हटाओ_cmd(&host->queues.issue, SCpnt)) अणु
		/*
		 * The command was on the issue queue, and has not been
		 * issued yet.  We can हटाओ the command from the queue,
		 * and acknowledge the पात.  Neither the devices nor the
		 * पूर्णांकerface know about the command.
		 */
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("on issue queue ");
//#पूर्ण_अगर
		res = res_success;
	पूर्ण अन्यथा अगर (queue_हटाओ_cmd(&host->queues.disconnected, SCpnt)) अणु
		/*
		 * The command was on the disconnected queue.  Simply
		 * acknowledge the पात condition, and when the target
		 * reconnects, we will give it an ABORT message.  The
		 * target should then disconnect, and we will clear
		 * the busylun bit.
		 */
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("on disconnected queue ");
//#पूर्ण_अगर
		res = res_success;
	पूर्ण अन्यथा अगर (host->SCpnt == SCpnt) अणु
		अचिन्हित दीर्घ flags;

//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("executing ");
//#पूर्ण_अगर

		local_irq_save(flags);
		चयन (host->scsi.phase) अणु
		/*
		 * If the पूर्णांकerface is idle, and the command is 'disconnectable',
		 * then it is the same as on the disconnected queue.  We simply
		 * हटाओ all traces of the command.  When the target reconnects,
		 * we will give it an ABORT message since the command could not
		 * be found.  When the target finally disconnects, we will clear
		 * the busylun bit.
		 */
		हाल PHASE_IDLE:
			अगर (host->scsi.disconnectable) अणु
				host->scsi.disconnectable = 0;
				host->SCpnt = शून्य;
				res = res_success;
			पूर्ण
			अवरोध;

		/*
		 * If the command has connected and करोne nothing further,
		 * simply क्रमce a disconnect.  We also need to clear the
		 * busylun bit.
		 */
		हाल PHASE_CONNECTED:
			sbic_arm_ग_लिखो(host, SBIC_CMND, CMND_DISCONNECT);
			host->SCpnt = शून्य;
			res = res_success_clear;
			अवरोध;

		शेष:
			acornscsi_पातcmd(host, host->SCpnt->tag);
			res = res_snooze;
		पूर्ण
		local_irq_restore(flags);
	पूर्ण अन्यथा अगर (host->origSCpnt == SCpnt) अणु
		/*
		 * The command will be executed next, but a command
		 * is currently using the पूर्णांकerface.  This is similar to
		 * being on the issue queue, except the busylun bit has
		 * been set.
		 */
		host->origSCpnt = शून्य;
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("waiting for execution ");
//#पूर्ण_अगर
		res = res_success_clear;
	पूर्ण अन्यथा
		prपूर्णांकk("unknown ");

	वापस res;
पूर्ण

/*
 * Prototype: पूर्णांक acornscsi_पात(काष्ठा scsi_cmnd *SCpnt)
 * Purpose  : पात a command on this host
 * Params   : SCpnt - command to पात
 * Returns  : one of SCSI_ABORT_ macros
 */
पूर्णांक acornscsi_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	AS_Host *host = (AS_Host *) SCpnt->device->host->hostdata;
	पूर्णांक result;

	host->stats.पातs += 1;

#अगर (DEBUG & DEBUG_ABORT)
	अणु
		पूर्णांक asr, ssr;
		asr = sbic_arm_पढ़ो(host, SBIC_ASR);
		ssr = sbic_arm_पढ़ो(host, SBIC_SSR);

		prपूर्णांकk(KERN_WARNING "acornscsi_abort: ");
		prपूर्णांक_sbic_status(asr, ssr, host->scsi.phase);
		acornscsi_dumplog(host, SCpnt->device->id);
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk("scsi%d: ", host->host->host_no);

	चयन (acornscsi_करो_पात(host, SCpnt)) अणु
	/*
	 * We managed to find the command and cleared it out.
	 * We करो not expect the command to be executing on the
	 * target, but we have set the busylun bit.
	 */
	हाल res_success_clear:
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("clear ");
//#पूर्ण_अगर
		clear_bit(SCpnt->device->id * 8 +
			  (u8)(SCpnt->device->lun & 0x7), host->busyluns);

	/*
	 * We found the command, and cleared it out.  Either
	 * the command is still known to be executing on the
	 * target, or the busylun bit is not set.
	 */
	हाल res_success:
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("success\n");
//#पूर्ण_अगर
		result = SUCCESS;
		अवरोध;

	/*
	 * We did find the command, but unक्रमtunately we couldn't
	 * unhook it from ourselves.  Wait some more, and अगर it
	 * still करोesn't complete, reset the पूर्णांकerface.
	 */
	हाल res_snooze:
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("snooze\n");
//#पूर्ण_अगर
		result = FAILED;
		अवरोध;

	/*
	 * The command could not be found (either because it completed,
	 * or it got dropped.
	 */
	शेष:
	हाल res_not_running:
		acornscsi_dumplog(host, SCpnt->device->id);
		result = FAILED;
//#अगर (DEBUG & DEBUG_ABORT)
		prपूर्णांकk("not running\n");
//#पूर्ण_अगर
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Prototype: पूर्णांक acornscsi_reset(काष्ठा scsi_cmnd *SCpnt)
 * Purpose  : reset a command on this host/reset this host
 * Params   : SCpnt  - command causing reset
 * Returns  : one of SCSI_RESET_ macros
 */
पूर्णांक acornscsi_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	AS_Host *host = (AS_Host *)SCpnt->device->host->hostdata;
	काष्ठा scsi_cmnd *SCptr;
    
    host->stats.resets += 1;

#अगर (DEBUG & DEBUG_RESET)
    अणु
	पूर्णांक asr, ssr, devidx;

	asr = sbic_arm_पढ़ो(host, SBIC_ASR);
	ssr = sbic_arm_पढ़ो(host, SBIC_SSR);

	prपूर्णांकk(KERN_WARNING "acornscsi_reset: ");
	prपूर्णांक_sbic_status(asr, ssr, host->scsi.phase);
	क्रम (devidx = 0; devidx < 9; devidx++)
	    acornscsi_dumplog(host, devidx);
    पूर्ण
#पूर्ण_अगर

    acornscsi_dma_stop(host);

    /*
     * करो hard reset.  This resets all devices on this host, and so we
     * must set the reset status on all commands.
     */
    acornscsi_resetcard(host);

    जबतक ((SCptr = queue_हटाओ(&host->queues.disconnected)) != शून्य)
	;

    वापस SUCCESS;
पूर्ण

/*==============================================================================================
 * initialisation & miscellaneous support
 */

/*
 * Function: अक्षर *acornscsi_info(काष्ठा Scsi_Host *host)
 * Purpose : वापस a string describing this पूर्णांकerface
 * Params  : host - host to give inक्रमmation on
 * Returns : a स्थिरant string
 */
स्थिर
अक्षर *acornscsi_info(काष्ठा Scsi_Host *host)
अणु
    अटल अक्षर string[100], *p;

    p = string;
    
    p += प्र_लिखो(string, "%s at port %08lX irq %d v%d.%d.%d"
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_SYNC
    " SYNC"
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    " TAG"
#पूर्ण_अगर
#अगर (DEBUG & DEBUG_NO_WRITE)
    " NOWRITE (" __stringअगरy(NO_WRITE) ")"
#पूर्ण_अगर
		, host->hostt->name, host->io_port, host->irq,
		VER_MAJOR, VER_MINOR, VER_PATCH);
    वापस string;
पूर्ण

अटल पूर्णांक acornscsi_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *instance)
अणु
    पूर्णांक devidx;
    काष्ठा scsi_device *scd;
    AS_Host *host;

    host  = (AS_Host *)instance->hostdata;
    
    seq_म_लिखो(m, "AcornSCSI driver v%d.%d.%d"
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_SYNC
    " SYNC"
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    " TAG"
#पूर्ण_अगर
#अगर (DEBUG & DEBUG_NO_WRITE)
    " NOWRITE (" __stringअगरy(NO_WRITE) ")"
#पूर्ण_अगर
		"\n\n", VER_MAJOR, VER_MINOR, VER_PATCH);

    seq_म_लिखो(m,	"SBIC: WD33C93A  Address: %p    IRQ : %d\n",
			host->base + SBIC_REGIDX, host->scsi.irq);
#अगर_घोषित USE_DMAC
    seq_म_लिखो(m,	"DMAC: uPC71071  Address: %p  IRQ : %d\n\n",
			host->base + DMAC_OFFSET, host->scsi.irq);
#पूर्ण_अगर

    seq_म_लिखो(m,	"Statistics:\n"
			"Queued commands: %-10u    Issued commands: %-10u\n"
			"Done commands  : %-10u    Reads          : %-10u\n"
			"Writes         : %-10u    Others         : %-10u\n"
			"Disconnects    : %-10u    Aborts         : %-10u\n"
			"Resets         : %-10u\n\nLast phases:",
			host->stats.queues,		host->stats.हटाओs,
			host->stats.fins,		host->stats.पढ़ोs,
			host->stats.ग_लिखोs,		host->stats.miscs,
			host->stats.disconnects,	host->stats.पातs,
			host->stats.resets);

    क्रम (devidx = 0; devidx < 9; devidx ++) अणु
	अचिन्हित पूर्णांक statptr, prev;

	seq_म_लिखो(m, "\n%c:", devidx == 8 ? 'H' : ('0' + devidx));
	statptr = host->status_ptr[devidx] - 10;

	अगर ((चिन्हित पूर्णांक)statptr < 0)
	    statptr += STATUS_BUFFER_SIZE;

	prev = host->status[devidx][statptr].when;

	क्रम (; statptr != host->status_ptr[devidx]; statptr = (statptr + 1) & (STATUS_BUFFER_SIZE - 1)) अणु
	    अगर (host->status[devidx][statptr].when) अणु
		seq_म_लिखो(m, "%c%02X:%02X+%2ld",
			host->status[devidx][statptr].irq ? '-' : ' ',
			host->status[devidx][statptr].ph,
			host->status[devidx][statptr].ssr,
			(host->status[devidx][statptr].when - prev) < 100 ?
				(host->status[devidx][statptr].when - prev) : 99);
		prev = host->status[devidx][statptr].when;
	    पूर्ण
	पूर्ण
    पूर्ण

    seq_म_लिखो(m, "\nAttached devices:\n");

    shost_क्रम_each_device(scd, instance) अणु
	seq_म_लिखो(m, "Device/Lun TaggedQ      Sync\n");
	seq_म_लिखो(m, "     %d/%llu   ", scd->id, scd->lun);
	अगर (scd->tagged_supported)
		seq_म_लिखो(m, "%3sabled(%3d) ",
			     scd->simple_tags ? "en" : "dis",
			     scd->current_tag);
	अन्यथा
		seq_म_लिखो(m, "unsupported  ");

	अगर (host->device[scd->id].sync_xfer & 15)
		seq_म_लिखो(m, "offset %d, %d ns\n",
			     host->device[scd->id].sync_xfer & 15,
			     acornscsi_getperiod(host->device[scd->id].sync_xfer));
	अन्यथा
		seq_म_लिखो(m, "async\n");

    पूर्ण
    वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा acornscsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.show_info		= acornscsi_show_info,
	.name			= "AcornSCSI",
	.info			= acornscsi_info,
	.queuecommand		= acornscsi_queuecmd,
	.eh_पात_handler	= acornscsi_पात,
	.eh_host_reset_handler	= acornscsi_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.proc_name		= "acornscsi",
पूर्ण;

अटल पूर्णांक acornscsi_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	AS_Host *ashost;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	host = scsi_host_alloc(&acornscsi_ढाँचा, माप(AS_Host));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_release;
	पूर्ण

	ashost = (AS_Host *)host->hostdata;

	ashost->base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	ashost->fast = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (!ashost->base || !ashost->fast) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	host->irq = ec->irq;
	ashost->host = host;
	ashost->scsi.irq = host->irq;

	ec->irqaddr	= ashost->fast + INT_REG;
	ec->irqmask	= 0x0a;

	ret = request_irq(host->irq, acornscsi_पूर्णांकr, 0, "acornscsi", ashost);
	अगर (ret) अणु
		prपूर्णांकk(KERN_CRIT "scsi%d: IRQ%d not free: %d\n",
			host->host_no, ashost->scsi.irq, ret);
		जाओ out_put;
	पूर्ण

	स_रखो(&ashost->stats, 0, माप (ashost->stats));
	queue_initialise(&ashost->queues.issue);
	queue_initialise(&ashost->queues.disconnected);
	msgqueue_initialise(&ashost->scsi.msgs);

	acornscsi_resetcard(ashost);

	ret = scsi_add_host(host, &ec->dev);
	अगर (ret)
		जाओ out_irq;

	scsi_scan_host(host);
	जाओ out;

 out_irq:
	मुक्त_irq(host->irq, ashost);
	msgqueue_मुक्त(&ashost->scsi.msgs);
	queue_मुक्त(&ashost->queues.disconnected);
	queue_मुक्त(&ashost->queues.issue);
 out_put:
	ecardm_iounmap(ec, ashost->fast);
	ecardm_iounmap(ec, ashost->base);
	scsi_host_put(host);
 out_release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम acornscsi_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	AS_Host *ashost = (AS_Host *)host->hostdata;

	ecard_set_drvdata(ec, शून्य);
	scsi_हटाओ_host(host);

	/*
	 * Put card पूर्णांकo RESET state
	 */
	ग_लिखोb(0x80, ashost->fast + PAGE_REG);

	मुक्त_irq(host->irq, ashost);

	msgqueue_मुक्त(&ashost->scsi.msgs);
	queue_मुक्त(&ashost->queues.disconnected);
	queue_मुक्त(&ashost->queues.issue);
	ecardm_iounmap(ec, ashost->fast);
	ecardm_iounmap(ec, ashost->base);
	scsi_host_put(host);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id acornscsi_cids[] = अणु
	अणु MANU_ACORN, PROD_ACORN_SCSI पूर्ण,
	अणु 0xffff, 0xffff पूर्ण,
पूर्ण;

अटल काष्ठा ecard_driver acornscsi_driver = अणु
	.probe		= acornscsi_probe,
	.हटाओ		= acornscsi_हटाओ,
	.id_table	= acornscsi_cids,
	.drv = अणु
		.name		= "acornscsi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init acornscsi_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&acornscsi_driver);
पूर्ण

अटल व्योम __निकास acornscsi_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&acornscsi_driver);
पूर्ण

module_init(acornscsi_init);
module_निकास(acornscsi_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("AcornSCSI driver");
MODULE_LICENSE("GPL");
