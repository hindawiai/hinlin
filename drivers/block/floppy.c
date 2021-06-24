<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/block/floppy.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1993, 1994  Alain Knaff
 *  Copyright (C) 1998 Alan Cox
 */

/*
 * 02.12.91 - Changed to अटल variables to indicate need क्रम reset
 * and recalibrate. This makes some things easier (output_byte reset
 * checking etc), and means less पूर्णांकerrupt jumping in हाल of errors,
 * so the code is hopefully easier to understand.
 */

/*
 * This file is certainly a mess. I've tried my best to get it working,
 * but I करोn't like programming floppies, and I have only one anyway.
 * Urgel. I should check क्रम more errors, and करो more graceful error
 * recovery. Seems there are problems with several drives. I've tried to
 * correct them. No promises.
 */

/*
 * As with hd.c, all routines within this file can (and will) be called
 * by पूर्णांकerrupts, so extreme caution is needed. A hardware पूर्णांकerrupt
 * handler may not sleep, or a kernel panic will happen. Thus I cannot
 * call "floppy-on" directly, but have to set a special समयr पूर्णांकerrupt
 * etc.
 */

/*
 * 28.02.92 - made track-buffering routines, based on the routines written
 * by entropy@wपूर्णांकermute.wpi.edu (Lawrence Foard). Linus.
 */

/*
 * Automatic floppy-detection and क्रमmatting written by Werner Almesberger
 * (almesber@nessie.cs.id.ethz.ch), who also corrected some problems with
 * the floppy-change संकेत detection.
 */

/*
 * 1992/7/22 -- Hennus Bergman: Added better error reporting, fixed
 * FDC data overrun bug, added some preliminary stuff क्रम vertical
 * recording support.
 *
 * 1992/9/17: Added DMA allocation & DMA functions. -- hhb.
 *
 * TODO: Errors are still not counted properly.
 */

/* 1992/9/20
 * Modअगरications क्रम ``Sector Shअगरting'' by Rob Hooft (hooft@chem.ruu.nl)
 * modeled after the मुक्तware MS-DOS program fdक्रमmat/88 V1.8 by
 * Christoph H. Hochst\"atter.
 * I have fixed the shअगरt values to the ones I always use. Maybe a new
 * ioctl() should be created to be able to modअगरy them.
 * There is a bug in the driver that makes it impossible to क्रमmat a
 * floppy as the first thing after bootup.
 */

/*
 * 1993/4/29 -- Linus -- cleaned up the समयr handling in the kernel, and
 * this helped the floppy driver as well. Much cleaner, and still seems to
 * work.
 */

/* 1994/6/24 --bbroad-- added the floppy table entries and made
 * minor modअगरications to allow 2.88 floppies to be run.
 */

/* 1994/7/13 -- Paul Vojta -- modअगरied the probing code to allow three or more
 * disk types.
 */

/*
 * 1994/8/8 -- Alain Knaff -- Switched to fdpatch driver: Support क्रम bigger
 * क्रमmat bug fixes, but unक्रमtunately some new bugs too...
 */

/* 1994/9/17 -- Koen Holपंचांगan -- added logging of physical floppy ग_लिखो
 * errors to allow safe writing by specialized programs.
 */

/* 1995/4/24 -- Dan Fandrich -- added support क्रम Commoकरोre 1581 3.5" disks
 * by defining bit 1 of the "stretch" parameter to mean put sectors on the
 * opposite side of the disk, leaving the sector IDs alone (i.e. Commoकरोre's
 * drives are "upside-down").
 */

/*
 * 1995/8/26 -- Andreas Busse -- added Mips support.
 */

/*
 * 1995/10/18 -- Ralf Baechle -- Portability cleanup; move machine dependent
 * features to यंत्र/floppy.h.
 */

/*
 * 1998/1/21 -- Riअक्षरd Gooch <rgooch@atnf.csiro.au> -- devfs support
 */

/*
 * 1998/05/07 -- Russell King -- More portability cleanups; moved definition of
 * पूर्णांकerrupt and dma channel to यंत्र/floppy.h. Cleaned up some क्रमmatting &
 * use of '0' क्रम शून्य.
 */

/*
 * 1998/06/07 -- Alan Cox -- Merged the 2.0.34 fixes क्रम resource allocation
 * failures.
 */

/*
 * 1998/09/20 -- David Weinehall -- Added slow-करोwn code क्रम buggy PS/2-drives.
 */

/*
 * 1999/08/13 -- Paul Slooपंचांगan -- floppy stopped working on Alpha after 24
 * days, 6 hours, 32 minutes and 32 seconds (i.e. MAXINT jअगरfies; पूर्णांकs were
 * being used to store jअगरfies, which are अचिन्हित दीर्घs).
 */

/*
 * 2000/08/28 -- Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 * - get rid of check_region
 * - s/suser/capable/
 */

/*
 * 2001/08/26 -- Paul Gorपंचांगaker - fix insmod oops on machines with no
 * floppy controller (lingering task on list after module is gone... boom.)
 */

/*
 * 2002/02/07 -- Anton Altaparmakov - Fix io ports reservation to correct range
 * (0x3f2-0x3f5, 0x3f7). This fix is a bit of a hack but the proper fix
 * requires many non-obvious changes in arch dependent code.
 */

/* 2003/07/28 -- Daniele Bellucci <bellucda@tiscali.it>.
 * Better audit of रेजिस्टर_blkdev.
 */

#घोषणा REALLY_SLOW_IO

#घोषणा DEBUGT 2

#घोषणा DPRINT(क्रमmat, args...) \
	pr_info("floppy%d: " क्रमmat, current_drive, ##args)

#घोषणा DCL_DEBUG		/* debug disk change line */
#अगर_घोषित DCL_DEBUG
#घोषणा debug_dcl(test, fmt, args...) \
	करो अणु अगर ((test) & FD_DEBUG) DPRINT(fmt, ##args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा debug_dcl(test, fmt, args...) \
	करो अणु अगर (0) DPRINT(fmt, ##args); पूर्ण जबतक (0)
#पूर्ण_अगर

/* करो prपूर्णांक messages क्रम unexpected पूर्णांकerrupts */
अटल पूर्णांक prपूर्णांक_unex = 1;
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/fdreg.h>
#समावेश <linux/fd.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/bपन.स>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/mc146818rtc.h>	/* CMOS defines */
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/async.h>
#समावेश <linux/compat.h>

/*
 * PS/2 floppies have much slower step rates than regular floppies.
 * It's been recommended that take about 1/4 of the शेष speed
 * in some more extreme हालs.
 */
अटल DEFINE_MUTEX(floppy_mutex);
अटल पूर्णांक slow_floppy;

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

अटल पूर्णांक FLOPPY_IRQ = 6;
अटल पूर्णांक FLOPPY_DMA = 2;
अटल पूर्णांक can_use_भव_dma = 2;
/* =======
 * can use भव DMA:
 * 0 = use of भव DMA disallowed by config
 * 1 = use of भव DMA prescribed by config
 * 2 = no भव DMA preference configured.  By शेष try hard DMA,
 * but fall back on भव DMA when not enough memory available
 */

अटल पूर्णांक use_भव_dma;
/* =======
 * use भव DMA
 * 0 using hard DMA
 * 1 using भव DMA
 * This variable is set to भव when a DMA mem problem arises, and
 * reset back in floppy_grab_irq_and_dma.
 * It is not safe to reset it in other circumstances, because the floppy
 * driver may have several buffers in use at once, and we करो currently not
 * record each buffers capabilities
 */

अटल DEFINE_SPINLOCK(floppy_lock);

अटल अचिन्हित लघु भव_dma_port = 0x3f0;
irqवापस_t floppy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक set_करोr(पूर्णांक fdc, अक्षर mask, अक्षर data);

#घोषणा K_64	0x10000		/* 64KB */

/* the following is the mask of allowed drives. By शेष units 2 and
 * 3 of both floppy controllers are disabled, because चयनing on the
 * motor of these drives causes प्रणाली hangs on some PCI computers. drive
 * 0 is the low bit (0x1), and drive 7 is the high bit (0x80). Bits are on अगर
 * a drive is allowed.
 *
 * NOTE: This must come beक्रमe we include the arch floppy header because
 *       some ports reference this variable from there. -DaveM
 */

अटल पूर्णांक allowed_drive_mask = 0x33;

#समावेश <यंत्र/floppy.h>

अटल पूर्णांक irqdma_allocated;

#समावेश <linux/blk-mq.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/cdrom.h>	/* क्रम the compatibility eject ioctl */
#समावेश <linux/completion.h>

अटल LIST_HEAD(floppy_reqs);
अटल काष्ठा request *current_req;
अटल पूर्णांक set_next_request(व्योम);

#अगर_अघोषित fd_get_dma_residue
#घोषणा fd_get_dma_residue() get_dma_residue(FLOPPY_DMA)
#पूर्ण_अगर

/* Dma Memory related stuff */

#अगर_अघोषित fd_dma_mem_मुक्त
#घोषणा fd_dma_mem_मुक्त(addr, size) मुक्त_pages(addr, get_order(size))
#पूर्ण_अगर

#अगर_अघोषित fd_dma_mem_alloc
#घोषणा fd_dma_mem_alloc(size) __get_dma_pages(GFP_KERNEL, get_order(size))
#पूर्ण_अगर

#अगर_अघोषित fd_cacheflush
#घोषणा fd_cacheflush(addr, size) /* nothing... */
#पूर्ण_अगर

अटल अंतरभूत व्योम fallback_on_nodma_alloc(अक्षर **addr, माप_प्रकार l)
अणु
#अगर_घोषित FLOPPY_CAN_FALLBACK_ON_NODMA
	अगर (*addr)
		वापस;		/* we have the memory */
	अगर (can_use_भव_dma != 2)
		वापस;		/* no fallback allowed */
	pr_info("DMA memory shortage. Temporarily falling back on virtual DMA\n");
	*addr = (अक्षर *)nodma_mem_alloc(l);
#अन्यथा
	वापस;
#पूर्ण_अगर
पूर्ण

/* End dma memory related stuff */

अटल अचिन्हित दीर्घ fake_change;
अटल bool initialized;

#घोषणा ITYPE(x)	(((x) >> 2) & 0x1f)
#घोषणा TOMINOR(x)	((x & 3) | ((x & 4) << 5))
#घोषणा UNIT(x)		((x) & 0x03)		/* drive on fdc */
#घोषणा FDC(x)		(((x) & 0x04) >> 2)	/* fdc of drive */
	/* reverse mapping from unit and fdc to drive */
#घोषणा REVDRIVE(fdc, unit) ((unit) + ((fdc) << 2))

#घोषणा PH_HEAD(floppy, head) (((((floppy)->stretch & 2) >> 1) ^ head) << 2)
#घोषणा STRETCH(floppy)	((floppy)->stretch & FD_STRETCH)

/* पढ़ो/ग_लिखो commands */
#घोषणा COMMAND			0
#घोषणा DR_SELECT		1
#घोषणा TRACK			2
#घोषणा HEAD			3
#घोषणा SECTOR			4
#घोषणा SIZECODE		5
#घोषणा SECT_PER_TRACK		6
#घोषणा GAP			7
#घोषणा SIZECODE2		8
#घोषणा NR_RW 9

/* क्रमmat commands */
#घोषणा F_SIZECODE		2
#घोषणा F_SECT_PER_TRACK	3
#घोषणा F_GAP			4
#घोषणा F_FILL			5
#घोषणा NR_F 6

/*
 * Maximum disk size (in kilobytes).
 * This शेष is used whenever the current disk size is unknown.
 * [Now it is rather a minimum]
 */
#घोषणा MAX_DISK_SIZE 4		/* 3984 */

/*
 * globals used by 'result()'
 */
अटल अचिन्हित अक्षर reply_buffer[FD_RAW_REPLY_SIZE];
अटल पूर्णांक inr;		/* size of reply buffer, when called from पूर्णांकerrupt */
#घोषणा ST0		0
#घोषणा ST1		1
#घोषणा ST2		2
#घोषणा ST3		0	/* result of GETSTATUS */
#घोषणा R_TRACK		3
#घोषणा R_HEAD		4
#घोषणा R_SECTOR	5
#घोषणा R_SIZECODE	6

#घोषणा SEL_DLY		(2 * HZ / 100)

/*
 * this काष्ठा defines the dअगरferent floppy drive types.
 */
अटल काष्ठा अणु
	काष्ठा floppy_drive_params params;
	स्थिर अक्षर *name;	/* name prपूर्णांकed जबतक booting */
पूर्ण शेष_drive_params[] = अणु
/* NOTE: the समय values in jअगरfies should be in msec!
 CMOS drive type
  |     Maximum data rate supported by drive type
  |     |   Head load समय, msec
  |     |   |   Head unload समय, msec (not used)
  |     |   |   |     Step rate पूर्णांकerval, usec
  |     |   |   |     |       Time needed क्रम spinup समय (jअगरfies)
  |     |   |   |     |       |      Timeout क्रम spinning करोwn (jअगरfies)
  |     |   |   |     |       |      |   Spinकरोwn offset (where disk stops)
  |     |   |   |     |       |      |   |     Select delay
  |     |   |   |     |       |      |   |     |     RPS
  |     |   |   |     |       |      |   |     |     |    Max number of tracks
  |     |   |   |     |       |      |   |     |     |    |     Interrupt समयout
  |     |   |   |     |       |      |   |     |     |    |     |   Max nonपूर्णांकlv. sectors
  |     |   |   |     |       |      |   |     |     |    |     |   | -Max Errors- flags */
अणुअणु0,  500, 16, 16, 8000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  80, 3*HZ, 20, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 7, 4, 8, 2, 1, 5, 3,10पूर्ण, 3*HZ/2, 0 पूर्ण, "unknown" पूर्ण,

अणुअणु1,  300, 16, 16, 8000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  40, 3*HZ, 17, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 1, 0, 0, 0, 0, 0, 0, 0पूर्ण, 3*HZ/2, 1 पूर्ण, "360K PC" पूर्ण, /*5 1/4 360 KB PC*/

अणुअणु2,  500, 16, 16, 6000, 4*HZ/10, 3*HZ, 14, SEL_DLY, 6,  83, 3*HZ, 17, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 2, 5, 6,23,10,20,12, 0पूर्ण, 3*HZ/2, 2 पूर्ण, "1.2M" पूर्ण, /*5 1/4 HD AT*/

अणुअणु3,  250, 16, 16, 3000,    1*HZ, 3*HZ,  0, SEL_DLY, 5,  83, 3*HZ, 20, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 4,22,21,30, 3, 0, 0, 0पूर्ण, 3*HZ/2, 4 पूर्ण, "720k" पूर्ण, /*3 1/2 DD*/

अणुअणु4,  500, 16, 16, 4000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 20, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 7, 4,25,22,31,21,29,11पूर्ण, 3*HZ/2, 7 पूर्ण, "1.44M" पूर्ण, /*3 1/2 HD*/

अणुअणु5, 1000, 15,  8, 3000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 40, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 7, 8, 4,25,28,22,31,21पूर्ण, 3*HZ/2, 8 पूर्ण, "2.88M AMI BIOS" पूर्ण, /*3 1/2 ED*/

अणुअणु6, 1000, 15,  8, 3000, 4*HZ/10, 3*HZ, 10, SEL_DLY, 5,  83, 3*HZ, 40, अणु3,1,2,0,2पूर्ण, 0,
      0, अणु 7, 8, 4,25,28,22,31,21पूर्ण, 3*HZ/2, 8 पूर्ण, "2.88M" पूर्ण /*3 1/2 ED*/
/*    |  --स्वतःdetected क्रमmats---    |      |      |
 *    पढ़ो_track                      |      |    Name prपूर्णांकed when booting
 *				      |     Native क्रमmat
 *	            Frequency of disk change checks */
पूर्ण;

अटल काष्ठा floppy_drive_params drive_params[N_DRIVE];
अटल काष्ठा floppy_drive_काष्ठा drive_state[N_DRIVE];
अटल काष्ठा floppy_ग_लिखो_errors ग_लिखो_errors[N_DRIVE];
अटल काष्ठा समयr_list motor_off_समयr[N_DRIVE];
अटल काष्ठा blk_mq_tag_set tag_sets[N_DRIVE];
अटल काष्ठा block_device *खोलोed_bdev[N_DRIVE];
अटल DEFINE_MUTEX(खोलो_lock);
अटल काष्ठा floppy_raw_cmd *raw_cmd, शेष_raw_cmd;

/*
 * This काष्ठा defines the dअगरferent floppy types.
 *
 * Bit 0 of 'stretch' tells अगर the tracks need to be द्विगुनd क्रम some
 * types (e.g. 360kB diskette in 1.2MB drive, etc.).  Bit 1 of 'stretch'
 * tells अगर the disk is in Commoकरोre 1581 क्रमmat, which means side 0 sectors
 * are located on side 1 of the disk but with a side 0 ID, and vice-versa.
 * This is the same as the Sharp MZ-80 5.25" CP/M disk क्रमmat, except that the
 * 1581's logical side 0 is on physical side 1, whereas the Sharp's logical
 * side 0 is on physical side 0 (but with the misnamed sector IDs).
 * 'stretch' should probably be नामd to something more general, like
 * 'options'.
 *
 * Bits 2 through 9 of 'stretch' tell the number of the first sector.
 * The LSB (bit 2) is flipped. For most disks, the first sector
 * is 1 (represented by 0x00<<2).  For some CP/M and music sampler
 * disks (such as Ensoniq EPS 16plus) it is 0 (represented as 0x01<<2).
 * For Amstrad CPC disks it is 0xC1 (represented as 0xC0<<2).
 *
 * Other parameters should be self-explanatory (see also setfdprm(8)).
 */
/*
	    Size
	     |  Sectors per track
	     |  | Head
	     |  | |  Tracks
	     |  | |  | Stretch
	     |  | |  | |  Gap 1 size
	     |  | |  | |    |  Data rate, | 0x40 क्रम perp
	     |  | |  | |    |    |  Spec1 (stepping rate, head unload
	     |  | |  | |    |    |    |    /fmt gap (gap2) */
अटल काष्ठा floppy_काष्ठा floppy_type[32] = अणु
	अणु    0, 0,0, 0,0,0x00,0x00,0x00,0x00,शून्य    पूर्ण,	/*  0 no testing    */
	अणु  720, 9,2,40,0,0x2A,0x02,0xDF,0x50,"d360"  पूर्ण, /*  1 360KB PC      */
	अणु 2400,15,2,80,0,0x1B,0x00,0xDF,0x54,"h1200" पूर्ण,	/*  2 1.2MB AT      */
	अणु  720, 9,1,80,0,0x2A,0x02,0xDF,0x50,"D360"  पूर्ण,	/*  3 360KB SS 3.5" */
	अणु 1440, 9,2,80,0,0x2A,0x02,0xDF,0x50,"D720"  पूर्ण,	/*  4 720KB 3.5"    */
	अणु  720, 9,2,40,1,0x23,0x01,0xDF,0x50,"h360"  पूर्ण,	/*  5 360KB AT      */
	अणु 1440, 9,2,80,0,0x23,0x01,0xDF,0x50,"h720"  पूर्ण,	/*  6 720KB AT      */
	अणु 2880,18,2,80,0,0x1B,0x00,0xCF,0x6C,"H1440" पूर्ण,	/*  7 1.44MB 3.5"   */
	अणु 5760,36,2,80,0,0x1B,0x43,0xAF,0x54,"E2880" पूर्ण,	/*  8 2.88MB 3.5"   */
	अणु 6240,39,2,80,0,0x1B,0x43,0xAF,0x28,"E3120" पूर्ण,	/*  9 3.12MB 3.5"   */

	अणु 2880,18,2,80,0,0x25,0x00,0xDF,0x02,"h1440" पूर्ण, /* 10 1.44MB 5.25"  */
	अणु 3360,21,2,80,0,0x1C,0x00,0xCF,0x0C,"H1680" पूर्ण, /* 11 1.68MB 3.5"   */
	अणु  820,10,2,41,1,0x25,0x01,0xDF,0x2E,"h410"  पूर्ण,	/* 12 410KB 5.25"   */
	अणु 1640,10,2,82,0,0x25,0x02,0xDF,0x2E,"H820"  पूर्ण,	/* 13 820KB 3.5"    */
	अणु 2952,18,2,82,0,0x25,0x00,0xDF,0x02,"h1476" पूर्ण,	/* 14 1.48MB 5.25"  */
	अणु 3444,21,2,82,0,0x25,0x00,0xDF,0x0C,"H1722" पूर्ण,	/* 15 1.72MB 3.5"   */
	अणु  840,10,2,42,1,0x25,0x01,0xDF,0x2E,"h420"  पूर्ण,	/* 16 420KB 5.25"   */
	अणु 1660,10,2,83,0,0x25,0x02,0xDF,0x2E,"H830"  पूर्ण,	/* 17 830KB 3.5"    */
	अणु 2988,18,2,83,0,0x25,0x00,0xDF,0x02,"h1494" पूर्ण,	/* 18 1.49MB 5.25"  */
	अणु 3486,21,2,83,0,0x25,0x00,0xDF,0x0C,"H1743" पूर्ण, /* 19 1.74 MB 3.5"  */

	अणु 1760,11,2,80,0,0x1C,0x09,0xCF,0x00,"h880"  पूर्ण, /* 20 880KB 5.25"   */
	अणु 2080,13,2,80,0,0x1C,0x01,0xCF,0x00,"D1040" पूर्ण, /* 21 1.04MB 3.5"   */
	अणु 2240,14,2,80,0,0x1C,0x19,0xCF,0x00,"D1120" पूर्ण, /* 22 1.12MB 3.5"   */
	अणु 3200,20,2,80,0,0x1C,0x20,0xCF,0x2C,"h1600" पूर्ण, /* 23 1.6MB 5.25"   */
	अणु 3520,22,2,80,0,0x1C,0x08,0xCF,0x2e,"H1760" पूर्ण, /* 24 1.76MB 3.5"   */
	अणु 3840,24,2,80,0,0x1C,0x20,0xCF,0x00,"H1920" पूर्ण, /* 25 1.92MB 3.5"   */
	अणु 6400,40,2,80,0,0x25,0x5B,0xCF,0x00,"E3200" पूर्ण, /* 26 3.20MB 3.5"   */
	अणु 7040,44,2,80,0,0x25,0x5B,0xCF,0x00,"E3520" पूर्ण, /* 27 3.52MB 3.5"   */
	अणु 7680,48,2,80,0,0x25,0x63,0xCF,0x00,"E3840" पूर्ण, /* 28 3.84MB 3.5"   */
	अणु 3680,23,2,80,0,0x1C,0x10,0xCF,0x00,"H1840" पूर्ण, /* 29 1.84MB 3.5"   */

	अणु 1600,10,2,80,0,0x25,0x02,0xDF,0x2E,"D800"  पूर्ण,	/* 30 800KB 3.5"    */
	अणु 3200,20,2,80,0,0x1C,0x00,0xCF,0x2C,"H1600" पूर्ण, /* 31 1.6MB 3.5"    */
पूर्ण;

अटल काष्ठा gendisk *disks[N_DRIVE][ARRAY_SIZE(floppy_type)];

#घोषणा SECTSIZE (_FD_SECTSIZE(*floppy))

/* Auto-detection: Disk type used until the next media change occurs. */
अटल काष्ठा floppy_काष्ठा *current_type[N_DRIVE];

/*
 * User-provided type inक्रमmation. current_type poपूर्णांकs to
 * the respective entry of this array.
 */
अटल काष्ठा floppy_काष्ठा user_params[N_DRIVE];

अटल sector_t floppy_sizes[256];

अटल अक्षर floppy_device_name[] = "floppy";

/*
 * The driver is trying to determine the correct media क्रमmat
 * जबतक probing is set. rw_पूर्णांकerrupt() clears it after a
 * successful access.
 */
अटल पूर्णांक probing;

/* Synchronization of FDC access. */
#घोषणा FD_COMMAND_NONE		-1
#घोषणा FD_COMMAND_ERROR	2
#घोषणा FD_COMMAND_OKAY		3

अटल अस्थिर पूर्णांक command_status = FD_COMMAND_NONE;
अटल अचिन्हित दीर्घ fdc_busy;
अटल DECLARE_WAIT_QUEUE_HEAD(fdc_रुको);
अटल DECLARE_WAIT_QUEUE_HEAD(command_करोne);

/* Errors during क्रमmatting are counted here. */
अटल पूर्णांक क्रमmat_errors;

/* Format request descriptor. */
अटल काष्ठा क्रमmat_descr क्रमmat_req;

/*
 * Rate is 0 क्रम 500kb/s, 1 क्रम 300kbps, 2 क्रम 250kbps
 * Spec1 is 0xSH, where S is stepping rate (F=1ms, E=2ms, D=3ms etc),
 * H is head unload समय (1=16ms, 2=32ms, etc)
 */

/*
 * Track buffer
 * Because these are written to by the DMA controller, they must
 * not contain a 64k byte boundary crossing, or data will be
 * corrupted/lost.
 */
अटल अक्षर *floppy_track_buffer;
अटल पूर्णांक max_buffer_sectors;

अटल पूर्णांक *errors;
प्रकार व्योम (*करोne_f)(पूर्णांक);
अटल स्थिर काष्ठा cont_t अणु
	व्योम (*पूर्णांकerrupt)(व्योम);
				/* this is called after the पूर्णांकerrupt of the
				 * मुख्य command */
	व्योम (*reकरो)(व्योम);	/* this is called to retry the operation */
	व्योम (*error)(व्योम);	/* this is called to tally an error */
	करोne_f करोne;		/* this is called to say अगर the operation has
				 * succeeded/failed */
पूर्ण *cont;

अटल व्योम floppy_पढ़ोy(व्योम);
अटल व्योम floppy_start(व्योम);
अटल व्योम process_fd_request(व्योम);
अटल व्योम recalibrate_floppy(व्योम);
अटल व्योम floppy_shutकरोwn(काष्ठा work_काष्ठा *);

अटल पूर्णांक floppy_request_regions(पूर्णांक);
अटल व्योम floppy_release_regions(पूर्णांक);
अटल पूर्णांक floppy_grab_irq_and_dma(व्योम);
अटल व्योम floppy_release_irq_and_dma(व्योम);

/*
 * The "reset" variable should be tested whenever an पूर्णांकerrupt is scheduled,
 * after the commands have been sent. This is to ensure that the driver करोesn't
 * get wedged when the पूर्णांकerrupt करोesn't come because of a failed command.
 * reset करोesn't need to be tested beक्रमe sending commands, because
 * output_byte is स्वतःmatically disabled when reset is set.
 */
अटल व्योम reset_fdc(व्योम);
अटल पूर्णांक floppy_revalidate(काष्ठा gendisk *disk);

/*
 * These are global variables, as that's the easiest way to give
 * inक्रमmation to पूर्णांकerrupts. They are the data used क्रम the current
 * request.
 */
#घोषणा NO_TRACK	-1
#घोषणा NEED_1_RECAL	-2
#घोषणा NEED_2_RECAL	-3

अटल atomic_t usage_count = ATOMIC_INIT(0);

/* buffer related variables */
अटल पूर्णांक buffer_track = -1;
अटल पूर्णांक buffer_drive = -1;
अटल पूर्णांक buffer_min = -1;
अटल पूर्णांक buffer_max = -1;

/* fdc related variables, should end up in a काष्ठा */
अटल काष्ठा floppy_fdc_state fdc_state[N_FDC];
अटल पूर्णांक current_fdc;			/* current fdc */

अटल काष्ठा workqueue_काष्ठा *floppy_wq;

अटल काष्ठा floppy_काष्ठा *_floppy = floppy_type;
अटल अचिन्हित अक्षर current_drive;
अटल दीर्घ current_count_sectors;
अटल अचिन्हित अक्षर fsector_t;	/* sector in track */
अटल अचिन्हित अक्षर in_sector_offset;	/* offset within physical sector,
					 * expressed in units of 512 bytes */

अटल अंतरभूत अचिन्हित अक्षर fdc_inb(पूर्णांक fdc, पूर्णांक reg)
अणु
	वापस fd_inb(fdc_state[fdc].address, reg);
पूर्ण

अटल अंतरभूत व्योम fdc_outb(अचिन्हित अक्षर value, पूर्णांक fdc, पूर्णांक reg)
अणु
	fd_outb(value, fdc_state[fdc].address, reg);
पूर्ण

अटल अंतरभूत bool drive_no_geom(पूर्णांक drive)
अणु
	वापस !current_type[drive] && !ITYPE(drive_state[drive].fd_device);
पूर्ण

#अगर_अघोषित fd_eject
अटल अंतरभूत पूर्णांक fd_eject(पूर्णांक drive)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * Debugging
 * =========
 */
#अगर_घोषित DEBUGT
अटल दीर्घ अचिन्हित debugसमयr;

अटल अंतरभूत व्योम set_debugt(व्योम)
अणु
	debugसमयr = jअगरfies;
पूर्ण

अटल अंतरभूत व्योम debugt(स्थिर अक्षर *func, स्थिर अक्षर *msg)
अणु
	अगर (drive_params[current_drive].flags & DEBUGT)
		pr_info("%s:%s dtime=%lu\n", func, msg, jअगरfies - debugसमयr);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम set_debugt(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम debugt(स्थिर अक्षर *func, स्थिर अक्षर *msg) अणु पूर्ण
#पूर्ण_अगर /* DEBUGT */


अटल DECLARE_DELAYED_WORK(fd_समयout, floppy_shutकरोwn);
अटल स्थिर अक्षर *समयout_message;

अटल व्योम is_alive(स्थिर अक्षर *func, स्थिर अक्षर *message)
अणु
	/* this routine checks whether the floppy driver is "alive" */
	अगर (test_bit(0, &fdc_busy) && command_status < 2 &&
	    !delayed_work_pending(&fd_समयout)) अणु
		DPRINT("%s: timeout handler died.  %s\n", func, message);
	पूर्ण
पूर्ण

अटल व्योम (*करो_floppy)(व्योम) = शून्य;

#घोषणा OLOGSIZE 20

अटल व्योम (*lasthandler)(व्योम);
अटल अचिन्हित दीर्घ पूर्णांकerruptjअगरfies;
अटल अचिन्हित दीर्घ resultjअगरfies;
अटल पूर्णांक resultsize;
अटल अचिन्हित दीर्घ lastreकरो;

अटल काष्ठा output_log अणु
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर status;
	अचिन्हित दीर्घ jअगरfies;
पूर्ण output_log[OLOGSIZE];

अटल पूर्णांक output_log_pos;

#घोषणा MAXTIMEOUT -2

अटल व्योम __reschedule_समयout(पूर्णांक drive, स्थिर अक्षर *message)
अणु
	अचिन्हित दीर्घ delay;

	अगर (drive < 0 || drive >= N_DRIVE) अणु
		delay = 20UL * HZ;
		drive = 0;
	पूर्ण अन्यथा
		delay = drive_params[drive].समयout;

	mod_delayed_work(floppy_wq, &fd_समयout, delay);
	अगर (drive_params[drive].flags & FD_DEBUG)
		DPRINT("reschedule timeout %s\n", message);
	समयout_message = message;
पूर्ण

अटल व्योम reschedule_समयout(पूर्णांक drive, स्थिर अक्षर *message)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&floppy_lock, flags);
	__reschedule_समयout(drive, message);
	spin_unlock_irqrestore(&floppy_lock, flags);
पूर्ण

#घोषणा INFBOUND(a, b) (a) = max_t(पूर्णांक, a, b)
#घोषणा SUPBOUND(a, b) (a) = min_t(पूर्णांक, a, b)

/*
 * Bottom half floppy driver.
 * ==========================
 *
 * This part of the file contains the code talking directly to the hardware,
 * and also the मुख्य service loop (seek-configure-spinup-command)
 */

/*
 * disk change.
 * This routine is responsible क्रम मुख्यtaining the FD_DISK_CHANGE flag,
 * and the last_checked date.
 *
 * last_checked is the date of the last check which showed 'no disk change'
 * FD_DISK_CHANGE is set under two conditions:
 * 1. The floppy has been changed after some i/o to that floppy alपढ़ोy
 *    took place.
 * 2. No floppy disk is in the drive. This is करोne in order to ensure that
 *    requests are quickly flushed in हाल there is no disk in the drive. It
 *    follows that FD_DISK_CHANGE can only be cleared अगर there is a disk in
 *    the drive.
 *
 * For 1., maxblock is observed. Maxblock is 0 अगर no i/o has taken place yet.
 * For 2., FD_DISK_NEWCHANGE is watched. FD_DISK_NEWCHANGE is cleared on
 *  each seek. If a disk is present, the disk change line should also be
 *  cleared on each seek. Thus, अगर FD_DISK_NEWCHANGE is clear, but the disk
 *  change line is set, this means either that no disk is in the drive, or
 *  that it has been हटाओd since the last seek.
 *
 * This means that we really have a third possibility too:
 *  The floppy has been changed after the last seek.
 */

अटल पूर्णांक disk_change(पूर्णांक drive)
अणु
	पूर्णांक fdc = FDC(drive);

	अगर (समय_beक्रमe(jअगरfies, drive_state[drive].select_date + drive_params[drive].select_delay))
		DPRINT("WARNING disk change called early\n");
	अगर (!(fdc_state[fdc].करोr & (0x10 << UNIT(drive))) ||
	    (fdc_state[fdc].करोr & 3) != UNIT(drive) || fdc != FDC(drive)) अणु
		DPRINT("probing disk change on unselected drive\n");
		DPRINT("drive=%d fdc=%d dor=%x\n", drive, FDC(drive),
		       (अचिन्हित पूर्णांक)fdc_state[fdc].करोr);
	पूर्ण

	debug_dcl(drive_params[drive].flags,
		  "checking disk change line for drive %d\n", drive);
	debug_dcl(drive_params[drive].flags, "jiffies=%lu\n", jअगरfies);
	debug_dcl(drive_params[drive].flags, "disk change line=%x\n",
		  fdc_inb(fdc, FD_सूची) & 0x80);
	debug_dcl(drive_params[drive].flags, "flags=%lx\n",
		  drive_state[drive].flags);

	अगर (drive_params[drive].flags & FD_BROKEN_DCL)
		वापस test_bit(FD_DISK_CHANGED_BIT,
				&drive_state[drive].flags);
	अगर ((fdc_inb(fdc, FD_सूची) ^ drive_params[drive].flags) & 0x80) अणु
		set_bit(FD_VERIFY_BIT, &drive_state[drive].flags);
					/* verअगरy ग_लिखो protection */

		अगर (drive_state[drive].maxblock)	/* mark it changed */
			set_bit(FD_DISK_CHANGED_BIT,
				&drive_state[drive].flags);

		/* invalidate its geometry */
		अगर (drive_state[drive].keep_data >= 0) अणु
			अगर ((drive_params[drive].flags & FTD_MSG) &&
			    current_type[drive] != शून्य)
				DPRINT("Disk type is undefined after disk change\n");
			current_type[drive] = शून्य;
			floppy_sizes[TOMINOR(drive)] = MAX_DISK_SIZE << 1;
		पूर्ण

		वापस 1;
	पूर्ण अन्यथा अणु
		drive_state[drive].last_checked = jअगरfies;
		clear_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[drive].flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_selected(पूर्णांक करोr, पूर्णांक unit)
अणु
	वापस ((करोr & (0x10 << unit)) && (करोr & 3) == unit);
पूर्ण

अटल bool is_पढ़ोy_state(पूर्णांक status)
अणु
	पूर्णांक state = status & (STATUS_READY | STATUS_सूची | STATUS_DMA);
	वापस state == STATUS_READY;
पूर्ण

अटल पूर्णांक set_करोr(पूर्णांक fdc, अक्षर mask, अक्षर data)
अणु
	अचिन्हित अक्षर unit;
	अचिन्हित अक्षर drive;
	अचिन्हित अक्षर newकरोr;
	अचिन्हित अक्षर oldकरोr;

	अगर (fdc_state[fdc].address == -1)
		वापस -1;

	oldकरोr = fdc_state[fdc].करोr;
	newकरोr = (oldकरोr & mask) | data;
	अगर (newकरोr != oldकरोr) अणु
		unit = oldकरोr & 0x3;
		अगर (is_selected(oldकरोr, unit) && !is_selected(newकरोr, unit)) अणु
			drive = REVDRIVE(fdc, unit);
			debug_dcl(drive_params[drive].flags,
				  "calling disk change from set_dor\n");
			disk_change(drive);
		पूर्ण
		fdc_state[fdc].करोr = newकरोr;
		fdc_outb(newकरोr, fdc, FD_DOR);

		unit = newकरोr & 0x3;
		अगर (!is_selected(oldकरोr, unit) && is_selected(newकरोr, unit)) अणु
			drive = REVDRIVE(fdc, unit);
			drive_state[drive].select_date = jअगरfies;
		पूर्ण
	पूर्ण
	वापस oldकरोr;
पूर्ण

अटल व्योम twaddle(पूर्णांक fdc, पूर्णांक drive)
अणु
	अगर (drive_params[drive].select_delay)
		वापस;
	fdc_outb(fdc_state[fdc].करोr & ~(0x10 << UNIT(drive)),
		 fdc, FD_DOR);
	fdc_outb(fdc_state[fdc].करोr, fdc, FD_DOR);
	drive_state[drive].select_date = jअगरfies;
पूर्ण

/*
 * Reset all driver inक्रमmation about the specअगरied fdc.
 * This is needed after a reset, and after a raw command.
 */
अटल व्योम reset_fdc_info(पूर्णांक fdc, पूर्णांक mode)
अणु
	पूर्णांक drive;

	fdc_state[fdc].spec1 = fdc_state[fdc].spec2 = -1;
	fdc_state[fdc].need_configure = 1;
	fdc_state[fdc].perp_mode = 1;
	fdc_state[fdc].rawcmd = 0;
	क्रम (drive = 0; drive < N_DRIVE; drive++)
		अगर (FDC(drive) == fdc &&
		    (mode || drive_state[drive].track != NEED_1_RECAL))
			drive_state[drive].track = NEED_2_RECAL;
पूर्ण

/*
 * selects the fdc and drive, and enables the fdc's input/dma.
 * Both current_drive and current_fdc are changed to match the new drive.
 */
अटल व्योम set_fdc(पूर्णांक drive)
अणु
	अचिन्हित पूर्णांक fdc;

	अगर (drive < 0 || drive >= N_DRIVE) अणु
		pr_info("bad drive value %d\n", drive);
		वापस;
	पूर्ण

	fdc = FDC(drive);
	अगर (fdc >= N_FDC) अणु
		pr_info("bad fdc value\n");
		वापस;
	पूर्ण

	set_करोr(fdc, ~0, 8);
#अगर N_FDC > 1
	set_करोr(1 - fdc, ~8, 0);
#पूर्ण_अगर
	अगर (fdc_state[fdc].rawcmd == 2)
		reset_fdc_info(fdc, 1);
	अगर (fdc_inb(fdc, FD_STATUS) != STATUS_READY)
		fdc_state[fdc].reset = 1;

	current_drive = drive;
	current_fdc = fdc;
पूर्ण

/*
 * locks the driver.
 * Both current_drive and current_fdc are changed to match the new drive.
 */
अटल पूर्णांक lock_fdc(पूर्णांक drive)
अणु
	अगर (WARN(atomic_पढ़ो(&usage_count) == 0,
		 "Trying to lock fdc while usage count=0\n"))
		वापस -1;

	अगर (रुको_event_पूर्णांकerruptible(fdc_रुको, !test_and_set_bit(0, &fdc_busy)))
		वापस -EINTR;

	command_status = FD_COMMAND_NONE;

	reschedule_समयout(drive, "lock fdc");
	set_fdc(drive);
	वापस 0;
पूर्ण

/* unlocks the driver */
अटल व्योम unlock_fdc(व्योम)
अणु
	अगर (!test_bit(0, &fdc_busy))
		DPRINT("FDC access conflict!\n");

	raw_cmd = शून्य;
	command_status = FD_COMMAND_NONE;
	cancel_delayed_work(&fd_समयout);
	करो_floppy = शून्य;
	cont = शून्य;
	clear_bit(0, &fdc_busy);
	wake_up(&fdc_रुको);
पूर्ण

/* चयनes the motor off after a given समयout */
अटल व्योम motor_off_callback(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ nr = t - motor_off_समयr;
	अचिन्हित अक्षर mask = ~(0x10 << UNIT(nr));

	अगर (WARN_ON_ONCE(nr >= N_DRIVE))
		वापस;

	set_करोr(FDC(nr), mask, 0);
पूर्ण

/* schedules motor off */
अटल व्योम floppy_off(अचिन्हित पूर्णांक drive)
अणु
	अचिन्हित दीर्घ अस्थिर delta;
	पूर्णांक fdc = FDC(drive);

	अगर (!(fdc_state[fdc].करोr & (0x10 << UNIT(drive))))
		वापस;

	del_समयr(motor_off_समयr + drive);

	/* make spindle stop in a position which minimizes spinup समय
	 * next समय */
	अगर (drive_params[drive].rps) अणु
		delta = jअगरfies - drive_state[drive].first_पढ़ो_date + HZ -
		    drive_params[drive].spinकरोwn_offset;
		delta = ((delta * drive_params[drive].rps) % HZ) / drive_params[drive].rps;
		motor_off_समयr[drive].expires =
		    jअगरfies + drive_params[drive].spinकरोwn - delta;
	पूर्ण
	add_समयr(motor_off_समयr + drive);
पूर्ण

/*
 * cycle through all N_DRIVE floppy drives, क्रम disk change testing.
 * stopping at current drive. This is करोne beक्रमe any दीर्घ operation, to
 * be sure to have up to date disk change inक्रमmation.
 */
अटल व्योम scandrives(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक drive;
	पूर्णांक saved_drive;

	अगर (drive_params[current_drive].select_delay)
		वापस;

	saved_drive = current_drive;
	क्रम (i = 0; i < N_DRIVE; i++) अणु
		drive = (saved_drive + i + 1) % N_DRIVE;
		अगर (drive_state[drive].fd_ref == 0 || drive_params[drive].select_delay != 0)
			जारी;	/* skip बंदd drives */
		set_fdc(drive);
		अगर (!(set_करोr(current_fdc, ~3, UNIT(drive) | (0x10 << UNIT(drive))) &
		      (0x10 << UNIT(drive))))
			/* चयन the motor off again, अगर it was off to
			 * begin with */
			set_करोr(current_fdc, ~(0x10 << UNIT(drive)), 0);
	पूर्ण
	set_fdc(saved_drive);
पूर्ण

अटल व्योम empty(व्योम)
अणु
पूर्ण

अटल व्योम (*floppy_work_fn)(व्योम);

अटल व्योम floppy_work_workfn(काष्ठा work_काष्ठा *work)
अणु
	floppy_work_fn();
पूर्ण

अटल DECLARE_WORK(floppy_work, floppy_work_workfn);

अटल व्योम schedule_bh(व्योम (*handler)(व्योम))
अणु
	WARN_ON(work_pending(&floppy_work));

	floppy_work_fn = handler;
	queue_work(floppy_wq, &floppy_work);
पूर्ण

अटल व्योम (*fd_समयr_fn)(व्योम) = शून्य;

अटल व्योम fd_समयr_workfn(काष्ठा work_काष्ठा *work)
अणु
	fd_समयr_fn();
पूर्ण

अटल DECLARE_DELAYED_WORK(fd_समयr, fd_समयr_workfn);

अटल व्योम cancel_activity(व्योम)
अणु
	करो_floppy = शून्य;
	cancel_delayed_work_sync(&fd_समयr);
	cancel_work_sync(&floppy_work);
पूर्ण

/* this function makes sure that the disk stays in the drive during the
 * transfer */
अटल व्योम fd_watchकरोg(व्योम)
अणु
	debug_dcl(drive_params[current_drive].flags,
		  "calling disk change from watchdog\n");

	अगर (disk_change(current_drive)) अणु
		DPRINT("disk removed during i/o\n");
		cancel_activity();
		cont->करोne(0);
		reset_fdc();
	पूर्ण अन्यथा अणु
		cancel_delayed_work(&fd_समयr);
		fd_समयr_fn = fd_watchकरोg;
		queue_delayed_work(floppy_wq, &fd_समयr, HZ / 10);
	पूर्ण
पूर्ण

अटल व्योम मुख्य_command_पूर्णांकerrupt(व्योम)
अणु
	cancel_delayed_work(&fd_समयr);
	cont->पूर्णांकerrupt();
पूर्ण

/* रुकोs क्रम a delay (spinup or select) to pass */
अटल पूर्णांक fd_रुको_क्रम_completion(अचिन्हित दीर्घ expires,
				  व्योम (*function)(व्योम))
अणु
	अगर (fdc_state[current_fdc].reset) अणु
		reset_fdc();	/* करो the reset during sleep to win समय
				 * अगर we करोn't need to sleep, it's a good
				 * occasion anyways */
		वापस 1;
	पूर्ण

	अगर (समय_beक्रमe(jअगरfies, expires)) अणु
		cancel_delayed_work(&fd_समयr);
		fd_समयr_fn = function;
		queue_delayed_work(floppy_wq, &fd_समयr, expires - jअगरfies);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम setup_DMA(व्योम)
अणु
	अचिन्हित दीर्घ f;

	अगर (raw_cmd->length == 0) अणु
		prपूर्णांक_hex_dump(KERN_INFO, "zero dma transfer size: ",
			       DUMP_PREFIX_NONE, 16, 1,
			       raw_cmd->fullcmd, raw_cmd->cmd_count, false);
		cont->करोne(0);
		fdc_state[current_fdc].reset = 1;
		वापस;
	पूर्ण
	अगर (((अचिन्हित दीर्घ)raw_cmd->kernel_data) % 512) अणु
		pr_info("non aligned address: %p\n", raw_cmd->kernel_data);
		cont->करोne(0);
		fdc_state[current_fdc].reset = 1;
		वापस;
	पूर्ण
	f = claim_dma_lock();
	fd_disable_dma();
#अगर_घोषित fd_dma_setup
	अगर (fd_dma_setup(raw_cmd->kernel_data, raw_cmd->length,
			 (raw_cmd->flags & FD_RAW_READ) ?
			 DMA_MODE_READ : DMA_MODE_WRITE,
			 fdc_state[current_fdc].address) < 0) अणु
		release_dma_lock(f);
		cont->करोne(0);
		fdc_state[current_fdc].reset = 1;
		वापस;
	पूर्ण
	release_dma_lock(f);
#अन्यथा
	fd_clear_dma_ff();
	fd_cacheflush(raw_cmd->kernel_data, raw_cmd->length);
	fd_set_dma_mode((raw_cmd->flags & FD_RAW_READ) ?
			DMA_MODE_READ : DMA_MODE_WRITE);
	fd_set_dma_addr(raw_cmd->kernel_data);
	fd_set_dma_count(raw_cmd->length);
	भव_dma_port = fdc_state[current_fdc].address;
	fd_enable_dma();
	release_dma_lock(f);
#पूर्ण_अगर
पूर्ण

अटल व्योम show_floppy(पूर्णांक fdc);

/* रुकोs until the fdc becomes पढ़ोy */
अटल पूर्णांक रुको_til_पढ़ोy(पूर्णांक fdc)
अणु
	पूर्णांक status;
	पूर्णांक counter;

	अगर (fdc_state[fdc].reset)
		वापस -1;
	क्रम (counter = 0; counter < 10000; counter++) अणु
		status = fdc_inb(fdc, FD_STATUS);
		अगर (status & STATUS_READY)
			वापस status;
	पूर्ण
	अगर (initialized) अणु
		DPRINT("Getstatus times out (%x) on fdc %d\n", status, fdc);
		show_floppy(fdc);
	पूर्ण
	fdc_state[fdc].reset = 1;
	वापस -1;
पूर्ण

/* sends a command byte to the fdc */
अटल पूर्णांक output_byte(पूर्णांक fdc, अक्षर byte)
अणु
	पूर्णांक status = रुको_til_पढ़ोy(fdc);

	अगर (status < 0)
		वापस -1;

	अगर (is_पढ़ोy_state(status)) अणु
		fdc_outb(byte, fdc, FD_DATA);
		output_log[output_log_pos].data = byte;
		output_log[output_log_pos].status = status;
		output_log[output_log_pos].jअगरfies = jअगरfies;
		output_log_pos = (output_log_pos + 1) % OLOGSIZE;
		वापस 0;
	पूर्ण
	fdc_state[fdc].reset = 1;
	अगर (initialized) अणु
		DPRINT("Unable to send byte %x to FDC. Fdc=%x Status=%x\n",
		       byte, fdc, status);
		show_floppy(fdc);
	पूर्ण
	वापस -1;
पूर्ण

/* माला_लो the response from the fdc */
अटल पूर्णांक result(पूर्णांक fdc)
अणु
	पूर्णांक i;
	पूर्णांक status = 0;

	क्रम (i = 0; i < FD_RAW_REPLY_SIZE; i++) अणु
		status = रुको_til_पढ़ोy(fdc);
		अगर (status < 0)
			अवरोध;
		status &= STATUS_सूची | STATUS_READY | STATUS_BUSY | STATUS_DMA;
		अगर ((status & ~STATUS_BUSY) == STATUS_READY) अणु
			resultjअगरfies = jअगरfies;
			resultsize = i;
			वापस i;
		पूर्ण
		अगर (status == (STATUS_सूची | STATUS_READY | STATUS_BUSY))
			reply_buffer[i] = fdc_inb(fdc, FD_DATA);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (initialized) अणु
		DPRINT("get result error. Fdc=%d Last status=%x Read bytes=%d\n",
		       fdc, status, i);
		show_floppy(fdc);
	पूर्ण
	fdc_state[fdc].reset = 1;
	वापस -1;
पूर्ण

#घोषणा MORE_OUTPUT -2
/* करोes the fdc need more output? */
अटल पूर्णांक need_more_output(पूर्णांक fdc)
अणु
	पूर्णांक status = रुको_til_पढ़ोy(fdc);

	अगर (status < 0)
		वापस -1;

	अगर (is_पढ़ोy_state(status))
		वापस MORE_OUTPUT;

	वापस result(fdc);
पूर्ण

/* Set perpendicular mode as required, based on data rate, अगर supported.
 * 82077 Now tested. 1Mbps data rate only possible with 82077-1.
 */
अटल व्योम perpendicular_mode(पूर्णांक fdc)
अणु
	अचिन्हित अक्षर perp_mode;

	अगर (raw_cmd->rate & 0x40) अणु
		चयन (raw_cmd->rate & 3) अणु
		हाल 0:
			perp_mode = 2;
			अवरोध;
		हाल 3:
			perp_mode = 3;
			अवरोध;
		शेष:
			DPRINT("Invalid data rate for perpendicular mode!\n");
			cont->करोne(0);
			fdc_state[fdc].reset = 1;
					/*
					 * convenient way to वापस to
					 * reकरो without too much hassle
					 * (deep stack et al.)
					 */
			वापस;
		पूर्ण
	पूर्ण अन्यथा
		perp_mode = 0;

	अगर (fdc_state[fdc].perp_mode == perp_mode)
		वापस;
	अगर (fdc_state[fdc].version >= FDC_82077_ORIG) अणु
		output_byte(fdc, FD_PERPENDICULAR);
		output_byte(fdc, perp_mode);
		fdc_state[fdc].perp_mode = perp_mode;
	पूर्ण अन्यथा अगर (perp_mode) अणु
		DPRINT("perpendicular mode not supported by this FDC.\n");
	पूर्ण
पूर्ण				/* perpendicular_mode */

अटल पूर्णांक fअगरo_depth = 0xa;
अटल पूर्णांक no_fअगरo;

अटल पूर्णांक fdc_configure(पूर्णांक fdc)
अणु
	/* Turn on FIFO */
	output_byte(fdc, FD_CONFIGURE);
	अगर (need_more_output(fdc) != MORE_OUTPUT)
		वापस 0;
	output_byte(fdc, 0);
	output_byte(fdc, 0x10 | (no_fअगरo & 0x20) | (fअगरo_depth & 0xf));
	output_byte(fdc, 0);    /* pre-compensation from track 0 upwards */
	वापस 1;
पूर्ण

#घोषणा NOMINAL_DTR 500

/* Issue a "SPECIFY" command to set the step rate समय, head unload समय,
 * head load समय, and DMA disable flag to values needed by floppy.
 *
 * The value "dtr" is the data transfer rate in Kbps.  It is needed
 * to account क्रम the data rate-based scaling करोne by the 82072 and 82077
 * FDC types.  This parameter is ignored क्रम other types of FDCs (i.e.
 * 8272a).
 *
 * Note that changing the data transfer rate has a (probably deleterious)
 * effect on the parameters subject to scaling क्रम 82072/82077 FDCs, so
 * fdc_specअगरy is called again after each data transfer rate
 * change.
 *
 * srt: 1000 to 16000 in microseconds
 * hut: 16 to 240 milliseconds
 * hlt: 2 to 254 milliseconds
 *
 * These values are rounded up to the next highest available delay समय.
 */
अटल व्योम fdc_specअगरy(पूर्णांक fdc, पूर्णांक drive)
अणु
	अचिन्हित अक्षर spec1;
	अचिन्हित अक्षर spec2;
	अचिन्हित दीर्घ srt;
	अचिन्हित दीर्घ hlt;
	अचिन्हित दीर्घ hut;
	अचिन्हित दीर्घ dtr = NOMINAL_DTR;
	अचिन्हित दीर्घ scale_dtr = NOMINAL_DTR;
	पूर्णांक hlt_max_code = 0x7f;
	पूर्णांक hut_max_code = 0xf;

	अगर (fdc_state[fdc].need_configure &&
	    fdc_state[fdc].version >= FDC_82072A) अणु
		fdc_configure(fdc);
		fdc_state[fdc].need_configure = 0;
	पूर्ण

	चयन (raw_cmd->rate & 0x03) अणु
	हाल 3:
		dtr = 1000;
		अवरोध;
	हाल 1:
		dtr = 300;
		अगर (fdc_state[fdc].version >= FDC_82078) अणु
			/* chose the शेष rate table, not the one
			 * where 1 = 2 Mbps */
			output_byte(fdc, FD_DRIVESPEC);
			अगर (need_more_output(fdc) == MORE_OUTPUT) अणु
				output_byte(fdc, UNIT(drive));
				output_byte(fdc, 0xc0);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2:
		dtr = 250;
		अवरोध;
	पूर्ण

	अगर (fdc_state[fdc].version >= FDC_82072) अणु
		scale_dtr = dtr;
		hlt_max_code = 0x00;	/* 0==256msec*dtr0/dtr (not linear!) */
		hut_max_code = 0x0;	/* 0==256msec*dtr0/dtr (not linear!) */
	पूर्ण

	/* Convert step rate from microseconds to milliseconds and 4 bits */
	srt = 16 - DIV_ROUND_UP(drive_params[drive].srt * scale_dtr / 1000,
				NOMINAL_DTR);
	अगर (slow_floppy)
		srt = srt / 4;

	SUPBOUND(srt, 0xf);
	INFBOUND(srt, 0);

	hlt = DIV_ROUND_UP(drive_params[drive].hlt * scale_dtr / 2,
			   NOMINAL_DTR);
	अगर (hlt < 0x01)
		hlt = 0x01;
	अन्यथा अगर (hlt > 0x7f)
		hlt = hlt_max_code;

	hut = DIV_ROUND_UP(drive_params[drive].hut * scale_dtr / 16,
			   NOMINAL_DTR);
	अगर (hut < 0x1)
		hut = 0x1;
	अन्यथा अगर (hut > 0xf)
		hut = hut_max_code;

	spec1 = (srt << 4) | hut;
	spec2 = (hlt << 1) | (use_भव_dma & 1);

	/* If these parameters did not change, just वापस with success */
	अगर (fdc_state[fdc].spec1 != spec1 ||
	    fdc_state[fdc].spec2 != spec2) अणु
		/* Go ahead and set spec1 and spec2 */
		output_byte(fdc, FD_SPECIFY);
		output_byte(fdc, fdc_state[fdc].spec1 = spec1);
		output_byte(fdc, fdc_state[fdc].spec2 = spec2);
	पूर्ण
पूर्ण				/* fdc_specअगरy */

/* Set the FDC's data transfer rate on behalf of the specअगरied drive.
 * NOTE: with 82072/82077 FDCs, changing the data rate requires a reissue
 * of the specअगरy command (i.e. using the fdc_specअगरy function).
 */
अटल पूर्णांक fdc_dtr(व्योम)
अणु
	/* If data rate not alपढ़ोy set to desired value, set it. */
	अगर ((raw_cmd->rate & 3) == fdc_state[current_fdc].dtr)
		वापस 0;

	/* Set dtr */
	fdc_outb(raw_cmd->rate & 3, current_fdc, FD_DCR);

	/* TODO: some FDC/drive combinations (C&T 82C711 with TEAC 1.2MB)
	 * need a stabilization period of several milliseconds to be
	 * enक्रमced after data rate changes beक्रमe R/W operations.
	 * Pause 5 msec to aव्योम trouble. (Needs to be 2 jअगरfies)
	 */
	fdc_state[current_fdc].dtr = raw_cmd->rate & 3;
	वापस fd_रुको_क्रम_completion(jअगरfies + 2UL * HZ / 100, floppy_पढ़ोy);
पूर्ण				/* fdc_dtr */

अटल व्योम tell_sector(व्योम)
अणु
	pr_cont(": track %d, head %d, sector %d, size %d",
		reply_buffer[R_TRACK], reply_buffer[R_HEAD],
		reply_buffer[R_SECTOR],
		reply_buffer[R_SIZECODE]);
पूर्ण				/* tell_sector */

अटल व्योम prपूर्णांक_errors(व्योम)
अणु
	DPRINT("");
	अगर (reply_buffer[ST0] & ST0_ECE) अणु
		pr_cont("Recalibrate failed!");
	पूर्ण अन्यथा अगर (reply_buffer[ST2] & ST2_CRC) अणु
		pr_cont("data CRC error");
		tell_sector();
	पूर्ण अन्यथा अगर (reply_buffer[ST1] & ST1_CRC) अणु
		pr_cont("CRC error");
		tell_sector();
	पूर्ण अन्यथा अगर ((reply_buffer[ST1] & (ST1_MAM | ST1_ND)) ||
		   (reply_buffer[ST2] & ST2_MAM)) अणु
		अगर (!probing) अणु
			pr_cont("sector not found");
			tell_sector();
		पूर्ण अन्यथा
			pr_cont("probe failed...");
	पूर्ण अन्यथा अगर (reply_buffer[ST2] & ST2_WC) अणु	/* seek error */
		pr_cont("wrong cylinder");
	पूर्ण अन्यथा अगर (reply_buffer[ST2] & ST2_BC) अणु	/* cylinder marked as bad */
		pr_cont("bad cylinder");
	पूर्ण अन्यथा अणु
		pr_cont("unknown error. ST[0..2] are: 0x%x 0x%x 0x%x",
			reply_buffer[ST0], reply_buffer[ST1],
			reply_buffer[ST2]);
		tell_sector();
	पूर्ण
	pr_cont("\n");
पूर्ण

/*
 * OK, this error पूर्णांकerpreting routine is called after a
 * DMA पढ़ो/ग_लिखो has succeeded
 * or failed, so we check the results, and copy any buffers.
 * hhb: Added better error reporting.
 * ak: Made this पूर्णांकo a separate routine.
 */
अटल पूर्णांक पूर्णांकerpret_errors(व्योम)
अणु
	अक्षर bad;

	अगर (inr != 7) अणु
		DPRINT("-- FDC reply error\n");
		fdc_state[current_fdc].reset = 1;
		वापस 1;
	पूर्ण

	/* check IC to find cause of पूर्णांकerrupt */
	चयन (reply_buffer[ST0] & ST0_INTR) अणु
	हाल 0x40:		/* error occurred during command execution */
		अगर (reply_buffer[ST1] & ST1_EOC)
			वापस 0;	/* occurs with pseuकरो-DMA */
		bad = 1;
		अगर (reply_buffer[ST1] & ST1_WP) अणु
			DPRINT("Drive is write protected\n");
			clear_bit(FD_DISK_WRITABLE_BIT,
				  &drive_state[current_drive].flags);
			cont->करोne(0);
			bad = 2;
		पूर्ण अन्यथा अगर (reply_buffer[ST1] & ST1_ND) अणु
			set_bit(FD_NEED_TWADDLE_BIT,
				&drive_state[current_drive].flags);
		पूर्ण अन्यथा अगर (reply_buffer[ST1] & ST1_OR) अणु
			अगर (drive_params[current_drive].flags & FTD_MSG)
				DPRINT("Over/Underrun - retrying\n");
			bad = 0;
		पूर्ण अन्यथा अगर (*errors >= drive_params[current_drive].max_errors.reporting) अणु
			prपूर्णांक_errors();
		पूर्ण
		अगर (reply_buffer[ST2] & ST2_WC || reply_buffer[ST2] & ST2_BC)
			/* wrong cylinder => recal */
			drive_state[current_drive].track = NEED_2_RECAL;
		वापस bad;
	हाल 0x80:		/* invalid command given */
		DPRINT("Invalid FDC command given!\n");
		cont->करोne(0);
		वापस 2;
	हाल 0xc0:
		DPRINT("Abnormal termination caused by polling\n");
		cont->error();
		वापस 2;
	शेष:		/* (0) Normal command termination */
		वापस 0;
	पूर्ण
पूर्ण

/*
 * This routine is called when everything should be correctly set up
 * क्रम the transfer (i.e. floppy motor is on, the correct floppy is
 * selected, and the head is sitting on the right track).
 */
अटल व्योम setup_rw_floppy(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक r;
	पूर्णांक flags;
	अचिन्हित दीर्घ पढ़ोy_date;
	व्योम (*function)(व्योम);

	flags = raw_cmd->flags;
	अगर (flags & (FD_RAW_READ | FD_RAW_WRITE))
		flags |= FD_RAW_INTR;

	अगर ((flags & FD_RAW_SPIN) && !(flags & FD_RAW_NO_MOTOR)) अणु
		पढ़ोy_date = drive_state[current_drive].spinup_date + drive_params[current_drive].spinup;
		/* If spinup will take a दीर्घ समय, rerun scandrives
		 * again just beक्रमe spinup completion. Beware that
		 * after scandrives, we must again रुको क्रम selection.
		 */
		अगर (समय_after(पढ़ोy_date, jअगरfies + drive_params[current_drive].select_delay)) अणु
			पढ़ोy_date -= drive_params[current_drive].select_delay;
			function = floppy_start;
		पूर्ण अन्यथा
			function = setup_rw_floppy;

		/* रुको until the floppy is spinning fast enough */
		अगर (fd_रुको_क्रम_completion(पढ़ोy_date, function))
			वापस;
	पूर्ण
	अगर ((flags & FD_RAW_READ) || (flags & FD_RAW_WRITE))
		setup_DMA();

	अगर (flags & FD_RAW_INTR)
		करो_floppy = मुख्य_command_पूर्णांकerrupt;

	r = 0;
	क्रम (i = 0; i < raw_cmd->cmd_count; i++)
		r |= output_byte(current_fdc, raw_cmd->fullcmd[i]);

	debugt(__func__, "rw_command");

	अगर (r) अणु
		cont->error();
		reset_fdc();
		वापस;
	पूर्ण

	अगर (!(flags & FD_RAW_INTR)) अणु
		inr = result(current_fdc);
		cont->पूर्णांकerrupt();
	पूर्ण अन्यथा अगर (flags & FD_RAW_NEED_DISK)
		fd_watchकरोg();
पूर्ण

अटल पूर्णांक blind_seek;

/*
 * This is the routine called after every seek (or recalibrate) पूर्णांकerrupt
 * from the floppy controller.
 */
अटल व्योम seek_पूर्णांकerrupt(व्योम)
अणु
	debugt(__func__, "");
	अगर (inr != 2 || (reply_buffer[ST0] & 0xF8) != 0x20) अणु
		DPRINT("seek failed\n");
		drive_state[current_drive].track = NEED_2_RECAL;
		cont->error();
		cont->reकरो();
		वापस;
	पूर्ण
	अगर (drive_state[current_drive].track >= 0 &&
	    drive_state[current_drive].track != reply_buffer[ST1] &&
	    !blind_seek) अणु
		debug_dcl(drive_params[current_drive].flags,
			  "clearing NEWCHANGE flag because of effective seek\n");
		debug_dcl(drive_params[current_drive].flags, "jiffies=%lu\n",
			  jअगरfies);
		clear_bit(FD_DISK_NEWCHANGE_BIT,
			  &drive_state[current_drive].flags);
					/* effective seek */
		drive_state[current_drive].select_date = jअगरfies;
	पूर्ण
	drive_state[current_drive].track = reply_buffer[ST1];
	floppy_पढ़ोy();
पूर्ण

अटल व्योम check_wp(पूर्णांक fdc, पूर्णांक drive)
अणु
	अगर (test_bit(FD_VERIFY_BIT, &drive_state[drive].flags)) अणु
					/* check ग_लिखो protection */
		output_byte(fdc, FD_GETSTATUS);
		output_byte(fdc, UNIT(drive));
		अगर (result(fdc) != 1) अणु
			fdc_state[fdc].reset = 1;
			वापस;
		पूर्ण
		clear_bit(FD_VERIFY_BIT, &drive_state[drive].flags);
		clear_bit(FD_NEED_TWADDLE_BIT,
			  &drive_state[drive].flags);
		debug_dcl(drive_params[drive].flags,
			  "checking whether disk is write protected\n");
		debug_dcl(drive_params[drive].flags, "wp=%x\n",
			  reply_buffer[ST3] & 0x40);
		अगर (!(reply_buffer[ST3] & 0x40))
			set_bit(FD_DISK_WRITABLE_BIT,
				&drive_state[drive].flags);
		अन्यथा
			clear_bit(FD_DISK_WRITABLE_BIT,
				  &drive_state[drive].flags);
	पूर्ण
पूर्ण

अटल व्योम seek_floppy(व्योम)
अणु
	पूर्णांक track;

	blind_seek = 0;

	debug_dcl(drive_params[current_drive].flags,
		  "calling disk change from %s\n", __func__);

	अगर (!test_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[current_drive].flags) &&
	    disk_change(current_drive) && (raw_cmd->flags & FD_RAW_NEED_DISK)) अणु
		/* the media changed flag should be cleared after the seek.
		 * If it isn't, this means that there is really no disk in
		 * the drive.
		 */
		set_bit(FD_DISK_CHANGED_BIT,
			&drive_state[current_drive].flags);
		cont->करोne(0);
		cont->reकरो();
		वापस;
	पूर्ण
	अगर (drive_state[current_drive].track <= NEED_1_RECAL) अणु
		recalibrate_floppy();
		वापस;
	पूर्ण अन्यथा अगर (test_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[current_drive].flags) &&
		   (raw_cmd->flags & FD_RAW_NEED_DISK) &&
		   (drive_state[current_drive].track <= NO_TRACK || drive_state[current_drive].track == raw_cmd->track)) अणु
		/* we seek to clear the media-changed condition. Does anybody
		 * know a more elegant way, which works on all drives? */
		अगर (raw_cmd->track)
			track = raw_cmd->track - 1;
		अन्यथा अणु
			अगर (drive_params[current_drive].flags & FD_SILENT_DCL_CLEAR) अणु
				set_करोr(current_fdc, ~(0x10 << UNIT(current_drive)), 0);
				blind_seek = 1;
				raw_cmd->flags |= FD_RAW_NEED_SEEK;
			पूर्ण
			track = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		check_wp(current_fdc, current_drive);
		अगर (raw_cmd->track != drive_state[current_drive].track &&
		    (raw_cmd->flags & FD_RAW_NEED_SEEK))
			track = raw_cmd->track;
		अन्यथा अणु
			setup_rw_floppy();
			वापस;
		पूर्ण
	पूर्ण

	करो_floppy = seek_पूर्णांकerrupt;
	output_byte(current_fdc, FD_SEEK);
	output_byte(current_fdc, UNIT(current_drive));
	अगर (output_byte(current_fdc, track) < 0) अणु
		reset_fdc();
		वापस;
	पूर्ण
	debugt(__func__, "");
पूर्ण

अटल व्योम recal_पूर्णांकerrupt(व्योम)
अणु
	debugt(__func__, "");
	अगर (inr != 2)
		fdc_state[current_fdc].reset = 1;
	अन्यथा अगर (reply_buffer[ST0] & ST0_ECE) अणु
		चयन (drive_state[current_drive].track) अणु
		हाल NEED_1_RECAL:
			debugt(__func__, "need 1 recal");
			/* after a second recalibrate, we still haven't
			 * reached track 0. Probably no drive. Raise an
			 * error, as failing immediately might upset
			 * computers possessed by the Devil :-) */
			cont->error();
			cont->reकरो();
			वापस;
		हाल NEED_2_RECAL:
			debugt(__func__, "need 2 recal");
			/* If we alपढ़ोy did a recalibrate,
			 * and we are not at track 0, this
			 * means we have moved. (The only way
			 * not to move at recalibration is to
			 * be alपढ़ोy at track 0.) Clear the
			 * new change flag */
			debug_dcl(drive_params[current_drive].flags,
				  "clearing NEWCHANGE flag because of second recalibrate\n");

			clear_bit(FD_DISK_NEWCHANGE_BIT,
				  &drive_state[current_drive].flags);
			drive_state[current_drive].select_date = jअगरfies;
			fallthrough;
		शेष:
			debugt(__func__, "default");
			/* Recalibrate moves the head by at
			 * most 80 steps. If after one
			 * recalibrate we करोn't have reached
			 * track 0, this might mean that we
			 * started beyond track 80.  Try
			 * again.  */
			drive_state[current_drive].track = NEED_1_RECAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		drive_state[current_drive].track = reply_buffer[ST1];
	floppy_पढ़ोy();
पूर्ण

अटल व्योम prपूर्णांक_result(अक्षर *message, पूर्णांक inr)
अणु
	पूर्णांक i;

	DPRINT("%s ", message);
	अगर (inr >= 0)
		क्रम (i = 0; i < inr; i++)
			pr_cont("repl[%d]=%x ", i, reply_buffer[i]);
	pr_cont("\n");
पूर्ण

/* पूर्णांकerrupt handler. Note that this can be called बाह्यally on the Sparc */
irqवापस_t floppy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक करो_prपूर्णांक;
	अचिन्हित दीर्घ f;
	व्योम (*handler)(व्योम) = करो_floppy;

	lasthandler = handler;
	पूर्णांकerruptjअगरfies = jअगरfies;

	f = claim_dma_lock();
	fd_disable_dma();
	release_dma_lock(f);

	करो_floppy = शून्य;
	अगर (current_fdc >= N_FDC || fdc_state[current_fdc].address == -1) अणु
		/* we करोn't even know which FDC is the culprit */
		pr_info("DOR0=%x\n", fdc_state[0].करोr);
		pr_info("floppy interrupt on bizarre fdc %d\n", current_fdc);
		pr_info("handler=%ps\n", handler);
		is_alive(__func__, "bizarre fdc");
		वापस IRQ_NONE;
	पूर्ण

	fdc_state[current_fdc].reset = 0;
	/* We have to clear the reset flag here, because apparently on boxes
	 * with level triggered पूर्णांकerrupts (PS/2, Sparc, ...), it is needed to
	 * emit SENSEI's to clear the पूर्णांकerrupt line. And fdc_state[fdc].reset
	 * blocks the emission of the SENSEI's.
	 * It is OK to emit floppy commands because we are in an पूर्णांकerrupt
	 * handler here, and thus we have to fear no पूर्णांकerference of other
	 * activity.
	 */

	करो_prपूर्णांक = !handler && prपूर्णांक_unex && initialized;

	inr = result(current_fdc);
	अगर (करो_prपूर्णांक)
		prपूर्णांक_result("unexpected interrupt", inr);
	अगर (inr == 0) अणु
		पूर्णांक max_sensei = 4;
		करो अणु
			output_byte(current_fdc, FD_SENSEI);
			inr = result(current_fdc);
			अगर (करो_prपूर्णांक)
				prपूर्णांक_result("sensei", inr);
			max_sensei--;
		पूर्ण जबतक ((reply_buffer[ST0] & 0x83) != UNIT(current_drive) &&
			 inr == 2 && max_sensei);
	पूर्ण
	अगर (!handler) अणु
		fdc_state[current_fdc].reset = 1;
		वापस IRQ_NONE;
	पूर्ण
	schedule_bh(handler);
	is_alive(__func__, "normal interrupt end");

	/* FIXME! Was it really क्रम us? */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम recalibrate_floppy(व्योम)
अणु
	debugt(__func__, "");
	करो_floppy = recal_पूर्णांकerrupt;
	output_byte(current_fdc, FD_RECALIBRATE);
	अगर (output_byte(current_fdc, UNIT(current_drive)) < 0)
		reset_fdc();
पूर्ण

/*
 * Must करो 4 FD_SENSEIs after reset because of ``drive polling''.
 */
अटल व्योम reset_पूर्णांकerrupt(व्योम)
अणु
	debugt(__func__, "");
	result(current_fdc);		/* get the status पढ़ोy क्रम set_fdc */
	अगर (fdc_state[current_fdc].reset) अणु
		pr_info("reset set in interrupt, calling %ps\n", cont->error);
		cont->error();	/* a reset just after a reset. BAD! */
	पूर्ण
	cont->reकरो();
पूर्ण

/*
 * reset is करोne by pulling bit 2 of DOR low क्रम a जबतक (old FDCs),
 * or by setting the self clearing bit 7 of STATUS (newer FDCs).
 * This WILL trigger an पूर्णांकerrupt, causing the handlers in the current
 * cont's ->reकरो() to be called via reset_पूर्णांकerrupt().
 */
अटल व्योम reset_fdc(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	करो_floppy = reset_पूर्णांकerrupt;
	fdc_state[current_fdc].reset = 0;
	reset_fdc_info(current_fdc, 0);

	/* Pseuकरो-DMA may पूर्णांकercept 'reset finished' पूर्णांकerrupt.  */
	/* Irrelevant क्रम प्रणालीs with true DMA (i386).          */

	flags = claim_dma_lock();
	fd_disable_dma();
	release_dma_lock(flags);

	अगर (fdc_state[current_fdc].version >= FDC_82072A)
		fdc_outb(0x80 | (fdc_state[current_fdc].dtr & 3),
			 current_fdc, FD_STATUS);
	अन्यथा अणु
		fdc_outb(fdc_state[current_fdc].करोr & ~0x04, current_fdc, FD_DOR);
		udelay(FD_RESET_DELAY);
		fdc_outb(fdc_state[current_fdc].करोr, current_fdc, FD_DOR);
	पूर्ण
पूर्ण

अटल व्योम show_floppy(पूर्णांक fdc)
अणु
	पूर्णांक i;

	pr_info("\n");
	pr_info("floppy driver state\n");
	pr_info("-------------------\n");
	pr_info("now=%lu last interrupt=%lu diff=%lu last called handler=%ps\n",
		jअगरfies, पूर्णांकerruptjअगरfies, jअगरfies - पूर्णांकerruptjअगरfies,
		lasthandler);

	pr_info("timeout_message=%s\n", समयout_message);
	pr_info("last output bytes:\n");
	क्रम (i = 0; i < OLOGSIZE; i++)
		pr_info("%2x %2x %lu\n",
			output_log[(i + output_log_pos) % OLOGSIZE].data,
			output_log[(i + output_log_pos) % OLOGSIZE].status,
			output_log[(i + output_log_pos) % OLOGSIZE].jअगरfies);
	pr_info("last result at %lu\n", resultjअगरfies);
	pr_info("last redo_fd_request at %lu\n", lastreकरो);
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1,
		       reply_buffer, resultsize, true);

	pr_info("status=%x\n", fdc_inb(fdc, FD_STATUS));
	pr_info("fdc_busy=%lu\n", fdc_busy);
	अगर (करो_floppy)
		pr_info("do_floppy=%ps\n", करो_floppy);
	अगर (work_pending(&floppy_work))
		pr_info("floppy_work.func=%ps\n", floppy_work.func);
	अगर (delayed_work_pending(&fd_समयr))
		pr_info("delayed work.function=%p expires=%ld\n",
		       fd_समयr.work.func,
		       fd_समयr.समयr.expires - jअगरfies);
	अगर (delayed_work_pending(&fd_समयout))
		pr_info("timer_function=%p expires=%ld\n",
		       fd_समयout.work.func,
		       fd_समयout.समयr.expires - jअगरfies);

	pr_info("cont=%p\n", cont);
	pr_info("current_req=%p\n", current_req);
	pr_info("command_status=%d\n", command_status);
	pr_info("\n");
पूर्ण

अटल व्योम floppy_shutकरोwn(काष्ठा work_काष्ठा *arg)
अणु
	अचिन्हित दीर्घ flags;

	अगर (initialized)
		show_floppy(current_fdc);
	cancel_activity();

	flags = claim_dma_lock();
	fd_disable_dma();
	release_dma_lock(flags);

	/* aव्योम dma going to a अक्रमom drive after shutकरोwn */

	अगर (initialized)
		DPRINT("floppy timeout called\n");
	fdc_state[current_fdc].reset = 1;
	अगर (cont) अणु
		cont->करोne(0);
		cont->reकरो();	/* this will recall reset when needed */
	पूर्ण अन्यथा अणु
		pr_info("no cont in shutdown!\n");
		process_fd_request();
	पूर्ण
	is_alive(__func__, "");
पूर्ण

/* start motor, check media-changed condition and ग_लिखो protection */
अटल पूर्णांक start_motor(व्योम (*function)(व्योम))
अणु
	पूर्णांक mask;
	पूर्णांक data;

	mask = 0xfc;
	data = UNIT(current_drive);
	अगर (!(raw_cmd->flags & FD_RAW_NO_MOTOR)) अणु
		अगर (!(fdc_state[current_fdc].करोr & (0x10 << UNIT(current_drive)))) अणु
			set_debugt();
			/* no पढ़ो since this drive is running */
			drive_state[current_drive].first_पढ़ो_date = 0;
			/* note motor start समय अगर motor is not yet running */
			drive_state[current_drive].spinup_date = jअगरfies;
			data |= (0x10 << UNIT(current_drive));
		पूर्ण
	पूर्ण अन्यथा अगर (fdc_state[current_fdc].करोr & (0x10 << UNIT(current_drive)))
		mask &= ~(0x10 << UNIT(current_drive));

	/* starts motor and selects floppy */
	del_समयr(motor_off_समयr + current_drive);
	set_करोr(current_fdc, mask, data);

	/* रुको_क्रम_completion also schedules reset अगर needed. */
	वापस fd_रुको_क्रम_completion(drive_state[current_drive].select_date + drive_params[current_drive].select_delay,
				      function);
पूर्ण

अटल व्योम floppy_पढ़ोy(व्योम)
अणु
	अगर (fdc_state[current_fdc].reset) अणु
		reset_fdc();
		वापस;
	पूर्ण
	अगर (start_motor(floppy_पढ़ोy))
		वापस;
	अगर (fdc_dtr())
		वापस;

	debug_dcl(drive_params[current_drive].flags,
		  "calling disk change from floppy_ready\n");
	अगर (!(raw_cmd->flags & FD_RAW_NO_MOTOR) &&
	    disk_change(current_drive) && !drive_params[current_drive].select_delay)
		twaddle(current_fdc, current_drive);	/* this clears the dcl on certain
				 * drive/controller combinations */

#अगर_घोषित fd_chose_dma_mode
	अगर ((raw_cmd->flags & FD_RAW_READ) || (raw_cmd->flags & FD_RAW_WRITE)) अणु
		अचिन्हित दीर्घ flags = claim_dma_lock();
		fd_chose_dma_mode(raw_cmd->kernel_data, raw_cmd->length);
		release_dma_lock(flags);
	पूर्ण
#पूर्ण_अगर

	अगर (raw_cmd->flags & (FD_RAW_NEED_SEEK | FD_RAW_NEED_DISK)) अणु
		perpendicular_mode(current_fdc);
		fdc_specअगरy(current_fdc, current_drive); /* must be करोne here because of hut, hlt ... */
		seek_floppy();
	पूर्ण अन्यथा अणु
		अगर ((raw_cmd->flags & FD_RAW_READ) ||
		    (raw_cmd->flags & FD_RAW_WRITE))
			fdc_specअगरy(current_fdc, current_drive);
		setup_rw_floppy();
	पूर्ण
पूर्ण

अटल व्योम floppy_start(व्योम)
अणु
	reschedule_समयout(current_drive, "floppy start");

	scandrives();
	debug_dcl(drive_params[current_drive].flags,
		  "setting NEWCHANGE in floppy_start\n");
	set_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[current_drive].flags);
	floppy_पढ़ोy();
पूर्ण

/*
 * ========================================================================
 * here ends the bottom half. Exported routines are:
 * floppy_start, floppy_off, floppy_पढ़ोy, lock_fdc, unlock_fdc, set_fdc,
 * start_motor, reset_fdc, reset_fdc_info, पूर्णांकerpret_errors.
 * Initialization also uses output_byte, result, set_करोr, floppy_पूर्णांकerrupt
 * and set_करोr.
 * ========================================================================
 */
/*
 * General purpose continuations.
 * ==============================
 */

अटल व्योम करो_wakeup(व्योम)
अणु
	reschedule_समयout(MAXTIMEOUT, "do wakeup");
	cont = शून्य;
	command_status += 2;
	wake_up(&command_करोne);
पूर्ण

अटल स्थिर काष्ठा cont_t wakeup_cont = अणु
	.पूर्णांकerrupt	= empty,
	.reकरो		= करो_wakeup,
	.error		= empty,
	.करोne		= (करोne_f)empty
पूर्ण;

अटल स्थिर काष्ठा cont_t पूर्णांकr_cont = अणु
	.पूर्णांकerrupt	= empty,
	.reकरो		= process_fd_request,
	.error		= empty,
	.करोne		= (करोne_f)empty
पूर्ण;

/* schedules handler, रुकोing क्रम completion. May be पूर्णांकerrupted, will then
 * वापस -EINTR, in which हाल the driver will स्वतःmatically be unlocked.
 */
अटल पूर्णांक रुको_til_करोne(व्योम (*handler)(व्योम), bool पूर्णांकerruptible)
अणु
	पूर्णांक ret;

	schedule_bh(handler);

	अगर (पूर्णांकerruptible)
		रुको_event_पूर्णांकerruptible(command_करोne, command_status >= 2);
	अन्यथा
		रुको_event(command_करोne, command_status >= 2);

	अगर (command_status < 2) अणु
		cancel_activity();
		cont = &पूर्णांकr_cont;
		reset_fdc();
		वापस -EINTR;
	पूर्ण

	अगर (fdc_state[current_fdc].reset)
		command_status = FD_COMMAND_ERROR;
	अगर (command_status == FD_COMMAND_OKAY)
		ret = 0;
	अन्यथा
		ret = -EIO;
	command_status = FD_COMMAND_NONE;
	वापस ret;
पूर्ण

अटल व्योम generic_करोne(पूर्णांक result)
अणु
	command_status = result;
	cont = &wakeup_cont;
पूर्ण

अटल व्योम generic_success(व्योम)
अणु
	cont->करोne(1);
पूर्ण

अटल व्योम generic_failure(व्योम)
अणु
	cont->करोne(0);
पूर्ण

अटल व्योम success_and_wakeup(व्योम)
अणु
	generic_success();
	cont->reकरो();
पूर्ण

/*
 * क्रमmatting and rw support.
 * ==========================
 */

अटल पूर्णांक next_valid_क्रमmat(पूर्णांक drive)
अणु
	पूर्णांक probed_क्रमmat;

	probed_क्रमmat = drive_state[drive].probed_क्रमmat;
	जबतक (1) अणु
		अगर (probed_क्रमmat >= FD_AUTODETECT_SIZE ||
		    !drive_params[drive].स्वतःdetect[probed_क्रमmat]) अणु
			drive_state[drive].probed_क्रमmat = 0;
			वापस 1;
		पूर्ण
		अगर (floppy_type[drive_params[drive].स्वतःdetect[probed_क्रमmat]].sect) अणु
			drive_state[drive].probed_क्रमmat = probed_क्रमmat;
			वापस 0;
		पूर्ण
		probed_क्रमmat++;
	पूर्ण
पूर्ण

अटल व्योम bad_flp_पूर्णांकr(व्योम)
अणु
	पूर्णांक err_count;

	अगर (probing) अणु
		drive_state[current_drive].probed_क्रमmat++;
		अगर (!next_valid_क्रमmat(current_drive))
			वापस;
	पूर्ण
	err_count = ++(*errors);
	INFBOUND(ग_लिखो_errors[current_drive].badness, err_count);
	अगर (err_count > drive_params[current_drive].max_errors.पात)
		cont->करोne(0);
	अगर (err_count > drive_params[current_drive].max_errors.reset)
		fdc_state[current_fdc].reset = 1;
	अन्यथा अगर (err_count > drive_params[current_drive].max_errors.recal)
		drive_state[current_drive].track = NEED_2_RECAL;
पूर्ण

अटल व्योम set_floppy(पूर्णांक drive)
अणु
	पूर्णांक type = ITYPE(drive_state[drive].fd_device);

	अगर (type)
		_floppy = floppy_type + type;
	अन्यथा
		_floppy = current_type[drive];
पूर्ण

/*
 * क्रमmatting support.
 * ===================
 */
अटल व्योम क्रमmat_पूर्णांकerrupt(व्योम)
अणु
	चयन (पूर्णांकerpret_errors()) अणु
	हाल 1:
		cont->error();
	हाल 2:
		अवरोध;
	हाल 0:
		cont->करोne(1);
	पूर्ण
	cont->reकरो();
पूर्ण

#घोषणा FM_MODE(x, y) ((y) & ~(((x)->rate & 0x80) >> 1))
#घोषणा CT(x) ((x) | 0xc0)

अटल व्योम setup_क्रमmat_params(पूर्णांक track)
अणु
	पूर्णांक n;
	पूर्णांक il;
	पूर्णांक count;
	पूर्णांक head_shअगरt;
	पूर्णांक track_shअगरt;
	काष्ठा fparm अणु
		अचिन्हित अक्षर track, head, sect, size;
	पूर्ण *here = (काष्ठा fparm *)floppy_track_buffer;

	raw_cmd = &शेष_raw_cmd;
	raw_cmd->track = track;

	raw_cmd->flags = (FD_RAW_WRITE | FD_RAW_INTR | FD_RAW_SPIN |
			  FD_RAW_NEED_DISK | FD_RAW_NEED_SEEK);
	raw_cmd->rate = _floppy->rate & 0x43;
	raw_cmd->cmd_count = NR_F;
	raw_cmd->cmd[COMMAND] = FM_MODE(_floppy, FD_FORMAT);
	raw_cmd->cmd[DR_SELECT] = UNIT(current_drive) + PH_HEAD(_floppy, क्रमmat_req.head);
	raw_cmd->cmd[F_SIZECODE] = FD_SIZECODE(_floppy);
	raw_cmd->cmd[F_SECT_PER_TRACK] = _floppy->sect << 2 >> raw_cmd->cmd[F_SIZECODE];
	raw_cmd->cmd[F_GAP] = _floppy->fmt_gap;
	raw_cmd->cmd[F_FILL] = FD_FILL_BYTE;

	raw_cmd->kernel_data = floppy_track_buffer;
	raw_cmd->length = 4 * raw_cmd->cmd[F_SECT_PER_TRACK];

	अगर (!raw_cmd->cmd[F_SECT_PER_TRACK])
		वापस;

	/* allow क्रम about 30ms क्रम data transport per track */
	head_shअगरt = (raw_cmd->cmd[F_SECT_PER_TRACK] + 5) / 6;

	/* a ``cylinder'' is two tracks plus a little stepping समय */
	track_shअगरt = 2 * head_shअगरt + 3;

	/* position of logical sector 1 on this track */
	n = (track_shअगरt * क्रमmat_req.track + head_shअगरt * क्रमmat_req.head)
	    % raw_cmd->cmd[F_SECT_PER_TRACK];

	/* determine पूर्णांकerleave */
	il = 1;
	अगर (_floppy->fmt_gap < 0x22)
		il++;

	/* initialize field */
	क्रम (count = 0; count < raw_cmd->cmd[F_SECT_PER_TRACK]; ++count) अणु
		here[count].track = क्रमmat_req.track;
		here[count].head = क्रमmat_req.head;
		here[count].sect = 0;
		here[count].size = raw_cmd->cmd[F_SIZECODE];
	पूर्ण
	/* place logical sectors */
	क्रम (count = 1; count <= raw_cmd->cmd[F_SECT_PER_TRACK]; ++count) अणु
		here[n].sect = count;
		n = (n + il) % raw_cmd->cmd[F_SECT_PER_TRACK];
		अगर (here[n].sect) अणु	/* sector busy, find next मुक्त sector */
			++n;
			अगर (n >= raw_cmd->cmd[F_SECT_PER_TRACK]) अणु
				n -= raw_cmd->cmd[F_SECT_PER_TRACK];
				जबतक (here[n].sect)
					++n;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (_floppy->stretch & FD_SECTBASEMASK) अणु
		क्रम (count = 0; count < raw_cmd->cmd[F_SECT_PER_TRACK]; count++)
			here[count].sect += FD_SECTBASE(_floppy) - 1;
	पूर्ण
पूर्ण

अटल व्योम reकरो_क्रमmat(व्योम)
अणु
	buffer_track = -1;
	setup_क्रमmat_params(क्रमmat_req.track << STRETCH(_floppy));
	floppy_start();
	debugt(__func__, "queue format request");
पूर्ण

अटल स्थिर काष्ठा cont_t क्रमmat_cont = अणु
	.पूर्णांकerrupt	= क्रमmat_पूर्णांकerrupt,
	.reकरो		= reकरो_क्रमmat,
	.error		= bad_flp_पूर्णांकr,
	.करोne		= generic_करोne
पूर्ण;

अटल पूर्णांक करो_क्रमmat(पूर्णांक drive, काष्ठा क्रमmat_descr *पंचांगp_क्रमmat_req)
अणु
	पूर्णांक ret;

	अगर (lock_fdc(drive))
		वापस -EINTR;

	set_floppy(drive);
	अगर (!_floppy ||
	    _floppy->track > drive_params[current_drive].tracks ||
	    पंचांगp_क्रमmat_req->track >= _floppy->track ||
	    पंचांगp_क्रमmat_req->head >= _floppy->head ||
	    (_floppy->sect << 2) % (1 << FD_SIZECODE(_floppy)) ||
	    !_floppy->fmt_gap) अणु
		process_fd_request();
		वापस -EINVAL;
	पूर्ण
	क्रमmat_req = *पंचांगp_क्रमmat_req;
	क्रमmat_errors = 0;
	cont = &क्रमmat_cont;
	errors = &क्रमmat_errors;
	ret = रुको_til_करोne(reकरो_क्रमmat, true);
	अगर (ret == -EINTR)
		वापस -EINTR;
	process_fd_request();
	वापस ret;
पूर्ण

/*
 * Buffer पढ़ो/ग_लिखो and support
 * =============================
 */

अटल व्योम floppy_end_request(काष्ठा request *req, blk_status_t error)
अणु
	अचिन्हित पूर्णांक nr_sectors = current_count_sectors;
	अचिन्हित पूर्णांक drive = (अचिन्हित दीर्घ)req->rq_disk->निजी_data;

	/* current_count_sectors can be zero अगर transfer failed */
	अगर (error)
		nr_sectors = blk_rq_cur_sectors(req);
	अगर (blk_update_request(req, error, nr_sectors << 9))
		वापस;
	__blk_mq_end_request(req, error);

	/* We're करोne with the request */
	floppy_off(drive);
	current_req = शून्य;
पूर्ण

/* new request_करोne. Can handle physical sectors which are smaller than a
 * logical buffer */
अटल व्योम request_करोne(पूर्णांक uptodate)
अणु
	काष्ठा request *req = current_req;
	पूर्णांक block;
	अक्षर msg[माप("request done ") + माप(पूर्णांक) * 3];

	probing = 0;
	snम_लिखो(msg, माप(msg), "request done %d", uptodate);
	reschedule_समयout(MAXTIMEOUT, msg);

	अगर (!req) अणु
		pr_info("floppy.c: no request in request_done\n");
		वापस;
	पूर्ण

	अगर (uptodate) अणु
		/* मुख्यtain values क्रम invalidation on geometry
		 * change */
		block = current_count_sectors + blk_rq_pos(req);
		INFBOUND(drive_state[current_drive].maxblock, block);
		अगर (block > _floppy->sect)
			drive_state[current_drive].maxtrack = 1;

		floppy_end_request(req, 0);
	पूर्ण अन्यथा अणु
		अगर (rq_data_dir(req) == WRITE) अणु
			/* record ग_लिखो error inक्रमmation */
			ग_लिखो_errors[current_drive].ग_लिखो_errors++;
			अगर (ग_लिखो_errors[current_drive].ग_लिखो_errors == 1) अणु
				ग_लिखो_errors[current_drive].first_error_sector = blk_rq_pos(req);
				ग_लिखो_errors[current_drive].first_error_generation = drive_state[current_drive].generation;
			पूर्ण
			ग_लिखो_errors[current_drive].last_error_sector = blk_rq_pos(req);
			ग_लिखो_errors[current_drive].last_error_generation = drive_state[current_drive].generation;
		पूर्ण
		floppy_end_request(req, BLK_STS_IOERR);
	पूर्ण
पूर्ण

/* Interrupt handler evaluating the result of the r/w operation */
अटल व्योम rw_पूर्णांकerrupt(व्योम)
अणु
	पूर्णांक eoc;
	पूर्णांक ssize;
	पूर्णांक heads;
	पूर्णांक nr_sectors;

	अगर (reply_buffer[R_HEAD] >= 2) अणु
		/* some Toshiba floppy controllers occasionnally seem to
		 * वापस bogus पूर्णांकerrupts after पढ़ो/ग_लिखो operations, which
		 * can be recognized by a bad head number (>= 2) */
		वापस;
	पूर्ण

	अगर (!drive_state[current_drive].first_पढ़ो_date)
		drive_state[current_drive].first_पढ़ो_date = jअगरfies;

	nr_sectors = 0;
	ssize = DIV_ROUND_UP(1 << raw_cmd->cmd[SIZECODE], 4);

	अगर (reply_buffer[ST1] & ST1_EOC)
		eoc = 1;
	अन्यथा
		eoc = 0;

	अगर (raw_cmd->cmd[COMMAND] & 0x80)
		heads = 2;
	अन्यथा
		heads = 1;

	nr_sectors = (((reply_buffer[R_TRACK] - raw_cmd->cmd[TRACK]) * heads +
		       reply_buffer[R_HEAD] - raw_cmd->cmd[HEAD]) * raw_cmd->cmd[SECT_PER_TRACK] +
		      reply_buffer[R_SECTOR] - raw_cmd->cmd[SECTOR] + eoc) << raw_cmd->cmd[SIZECODE] >> 2;

	अगर (nr_sectors / ssize >
	    DIV_ROUND_UP(in_sector_offset + current_count_sectors, ssize)) अणु
		DPRINT("long rw: %x instead of %lx\n",
		       nr_sectors, current_count_sectors);
		pr_info("rs=%d s=%d\n", reply_buffer[R_SECTOR],
			raw_cmd->cmd[SECTOR]);
		pr_info("rh=%d h=%d\n", reply_buffer[R_HEAD],
			raw_cmd->cmd[HEAD]);
		pr_info("rt=%d t=%d\n", reply_buffer[R_TRACK],
			raw_cmd->cmd[TRACK]);
		pr_info("heads=%d eoc=%d\n", heads, eoc);
		pr_info("spt=%d st=%d ss=%d\n",
			raw_cmd->cmd[SECT_PER_TRACK], fsector_t, ssize);
		pr_info("in_sector_offset=%d\n", in_sector_offset);
	पूर्ण

	nr_sectors -= in_sector_offset;
	INFBOUND(nr_sectors, 0);
	SUPBOUND(current_count_sectors, nr_sectors);

	चयन (पूर्णांकerpret_errors()) अणु
	हाल 2:
		cont->reकरो();
		वापस;
	हाल 1:
		अगर (!current_count_sectors) अणु
			cont->error();
			cont->reकरो();
			वापस;
		पूर्ण
		अवरोध;
	हाल 0:
		अगर (!current_count_sectors) अणु
			cont->reकरो();
			वापस;
		पूर्ण
		current_type[current_drive] = _floppy;
		floppy_sizes[TOMINOR(current_drive)] = _floppy->size;
		अवरोध;
	पूर्ण

	अगर (probing) अणु
		अगर (drive_params[current_drive].flags & FTD_MSG)
			DPRINT("Auto-detected floppy type %s in fd%d\n",
			       _floppy->name, current_drive);
		current_type[current_drive] = _floppy;
		floppy_sizes[TOMINOR(current_drive)] = _floppy->size;
		probing = 0;
	पूर्ण

	अगर (CT(raw_cmd->cmd[COMMAND]) != FD_READ) अणु
		/* transfer directly from buffer */
		cont->करोne(1);
	पूर्ण अन्यथा अणु
		buffer_track = raw_cmd->track;
		buffer_drive = current_drive;
		INFBOUND(buffer_max, nr_sectors + fsector_t);
	पूर्ण
	cont->reकरो();
पूर्ण

/* Compute the maximal transfer size */
अटल पूर्णांक transfer_size(पूर्णांक ssize, पूर्णांक max_sector, पूर्णांक max_size)
अणु
	SUPBOUND(max_sector, fsector_t + max_size);

	/* alignment */
	max_sector -= (max_sector % _floppy->sect) % ssize;

	/* transfer size, beginning not aligned */
	current_count_sectors = max_sector - fsector_t;

	वापस max_sector;
पूर्ण

/*
 * Move data from/to the track buffer to/from the buffer cache.
 */
अटल व्योम copy_buffer(पूर्णांक ssize, पूर्णांक max_sector, पूर्णांक max_sector_2)
अणु
	पूर्णांक reमुख्यing;		/* number of transferred 512-byte sectors */
	काष्ठा bio_vec bv;
	अक्षर *dma_buffer;
	पूर्णांक size;
	काष्ठा req_iterator iter;

	max_sector = transfer_size(ssize,
				   min(max_sector, max_sector_2),
				   blk_rq_sectors(current_req));

	अगर (current_count_sectors <= 0 && CT(raw_cmd->cmd[COMMAND]) == FD_WRITE &&
	    buffer_max > fsector_t + blk_rq_sectors(current_req))
		current_count_sectors = min_t(पूर्णांक, buffer_max - fsector_t,
					      blk_rq_sectors(current_req));

	reमुख्यing = current_count_sectors << 9;
	अगर (reमुख्यing > blk_rq_bytes(current_req) && CT(raw_cmd->cmd[COMMAND]) == FD_WRITE) अणु
		DPRINT("in copy buffer\n");
		pr_info("current_count_sectors=%ld\n", current_count_sectors);
		pr_info("remaining=%d\n", reमुख्यing >> 9);
		pr_info("current_req->nr_sectors=%u\n",
			blk_rq_sectors(current_req));
		pr_info("current_req->current_nr_sectors=%u\n",
			blk_rq_cur_sectors(current_req));
		pr_info("max_sector=%d\n", max_sector);
		pr_info("ssize=%d\n", ssize);
	पूर्ण

	buffer_max = max(max_sector, buffer_max);

	dma_buffer = floppy_track_buffer + ((fsector_t - buffer_min) << 9);

	size = blk_rq_cur_bytes(current_req);

	rq_क्रम_each_segment(bv, current_req, iter) अणु
		अगर (!reमुख्यing)
			अवरोध;

		size = bv.bv_len;
		SUPBOUND(size, reमुख्यing);
		अगर (dma_buffer + size >
		    floppy_track_buffer + (max_buffer_sectors << 10) ||
		    dma_buffer < floppy_track_buffer) अणु
			DPRINT("buffer overrun in copy buffer %d\n",
			       (पूर्णांक)((floppy_track_buffer - dma_buffer) >> 9));
			pr_info("fsector_t=%d buffer_min=%d\n",
				fsector_t, buffer_min);
			pr_info("current_count_sectors=%ld\n",
				current_count_sectors);
			अगर (CT(raw_cmd->cmd[COMMAND]) == FD_READ)
				pr_info("read\n");
			अगर (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE)
				pr_info("write\n");
			अवरोध;
		पूर्ण

		अगर (CT(raw_cmd->cmd[COMMAND]) == FD_READ)
			स_नकल_to_page(bv.bv_page, bv.bv_offset, dma_buffer,
				       size);
		अन्यथा
			स_नकल_from_page(dma_buffer, bv.bv_page, bv.bv_offset,
					 size);

		reमुख्यing -= size;
		dma_buffer += size;
	पूर्ण
	अगर (reमुख्यing) अणु
		अगर (reमुख्यing > 0)
			max_sector -= reमुख्यing >> 9;
		DPRINT("weirdness: remaining %d\n", reमुख्यing >> 9);
	पूर्ण
पूर्ण

/* work around a bug in pseuकरो DMA
 * (on some FDCs) pseuकरो DMA करोes not stop when the CPU stops
 * sending data.  Hence we need a dअगरferent way to संकेत the
 * transfer length:  We use raw_cmd->cmd[SECT_PER_TRACK].  Unक्रमtunately, this
 * करोes not work with MT, hence we can only transfer one head at
 * a समय
 */
अटल व्योम भवdmabug_workaround(व्योम)
अणु
	पूर्णांक hard_sectors;
	पूर्णांक end_sector;

	अगर (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE) अणु
		raw_cmd->cmd[COMMAND] &= ~0x80;	/* चयन off multiple track mode */

		hard_sectors = raw_cmd->length >> (7 + raw_cmd->cmd[SIZECODE]);
		end_sector = raw_cmd->cmd[SECTOR] + hard_sectors - 1;
		अगर (end_sector > raw_cmd->cmd[SECT_PER_TRACK]) अणु
			pr_info("too many sectors %d > %d\n",
				end_sector, raw_cmd->cmd[SECT_PER_TRACK]);
			वापस;
		पूर्ण
		raw_cmd->cmd[SECT_PER_TRACK] = end_sector;
					/* make sure raw_cmd->cmd[SECT_PER_TRACK]
					 * poपूर्णांकs to end of transfer */
	पूर्ण
पूर्ण

/*
 * Formulate a पढ़ो/ग_लिखो request.
 * this routine decides where to load the data (directly to buffer, or to
 * पंचांगp floppy area), how much data to load (the size of the buffer, the whole
 * track, or a single sector)
 * All floppy_track_buffer handling goes in here. If we ever add track buffer
 * allocation on the fly, it should be करोne here. No other part should need
 * modअगरication.
 */

अटल पूर्णांक make_raw_rw_request(व्योम)
अणु
	पूर्णांक aligned_sector_t;
	पूर्णांक max_sector;
	पूर्णांक max_size;
	पूर्णांक tracksize;
	पूर्णांक ssize;

	अगर (WARN(max_buffer_sectors == 0, "VFS: Block I/O scheduled on unopened device\n"))
		वापस 0;

	set_fdc((दीर्घ)current_req->rq_disk->निजी_data);

	raw_cmd = &शेष_raw_cmd;
	raw_cmd->flags = FD_RAW_SPIN | FD_RAW_NEED_DISK | FD_RAW_NEED_SEEK;
	raw_cmd->cmd_count = NR_RW;
	अगर (rq_data_dir(current_req) == READ) अणु
		raw_cmd->flags |= FD_RAW_READ;
		raw_cmd->cmd[COMMAND] = FM_MODE(_floppy, FD_READ);
	पूर्ण अन्यथा अगर (rq_data_dir(current_req) == WRITE) अणु
		raw_cmd->flags |= FD_RAW_WRITE;
		raw_cmd->cmd[COMMAND] = FM_MODE(_floppy, FD_WRITE);
	पूर्ण अन्यथा अणु
		DPRINT("%s: unknown command\n", __func__);
		वापस 0;
	पूर्ण

	max_sector = _floppy->sect * _floppy->head;

	raw_cmd->cmd[TRACK] = (पूर्णांक)blk_rq_pos(current_req) / max_sector;
	fsector_t = (पूर्णांक)blk_rq_pos(current_req) % max_sector;
	अगर (_floppy->track && raw_cmd->cmd[TRACK] >= _floppy->track) अणु
		अगर (blk_rq_cur_sectors(current_req) & 1) अणु
			current_count_sectors = 1;
			वापस 1;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	raw_cmd->cmd[HEAD] = fsector_t / _floppy->sect;

	अगर (((_floppy->stretch & (FD_SWAPSIDES | FD_SECTBASEMASK)) ||
	     test_bit(FD_NEED_TWADDLE_BIT, &drive_state[current_drive].flags)) &&
	    fsector_t < _floppy->sect)
		max_sector = _floppy->sect;

	/* 2M disks have phantom sectors on the first track */
	अगर ((_floppy->rate & FD_2M) && (!raw_cmd->cmd[TRACK]) && (!raw_cmd->cmd[HEAD])) अणु
		max_sector = 2 * _floppy->sect / 3;
		अगर (fsector_t >= max_sector) अणु
			current_count_sectors =
			    min_t(पूर्णांक, _floppy->sect - fsector_t,
				  blk_rq_sectors(current_req));
			वापस 1;
		पूर्ण
		raw_cmd->cmd[SIZECODE] = 2;
	पूर्ण अन्यथा
		raw_cmd->cmd[SIZECODE] = FD_SIZECODE(_floppy);
	raw_cmd->rate = _floppy->rate & 0x43;
	अगर ((_floppy->rate & FD_2M) &&
	    (raw_cmd->cmd[TRACK] || raw_cmd->cmd[HEAD]) && raw_cmd->rate == 2)
		raw_cmd->rate = 1;

	अगर (raw_cmd->cmd[SIZECODE])
		raw_cmd->cmd[SIZECODE2] = 0xff;
	अन्यथा
		raw_cmd->cmd[SIZECODE2] = 0x80;
	raw_cmd->track = raw_cmd->cmd[TRACK] << STRETCH(_floppy);
	raw_cmd->cmd[DR_SELECT] = UNIT(current_drive) + PH_HEAD(_floppy, raw_cmd->cmd[HEAD]);
	raw_cmd->cmd[GAP] = _floppy->gap;
	ssize = DIV_ROUND_UP(1 << raw_cmd->cmd[SIZECODE], 4);
	raw_cmd->cmd[SECT_PER_TRACK] = _floppy->sect << 2 >> raw_cmd->cmd[SIZECODE];
	raw_cmd->cmd[SECTOR] = ((fsector_t % _floppy->sect) << 2 >> raw_cmd->cmd[SIZECODE]) +
	    FD_SECTBASE(_floppy);

	/* tracksize describes the size which can be filled up with sectors
	 * of size ssize.
	 */
	tracksize = _floppy->sect - _floppy->sect % ssize;
	अगर (tracksize < _floppy->sect) अणु
		raw_cmd->cmd[SECT_PER_TRACK]++;
		अगर (tracksize <= fsector_t % _floppy->sect)
			raw_cmd->cmd[SECTOR]--;

		/* अगर we are beyond tracksize, fill up using smaller sectors */
		जबतक (tracksize <= fsector_t % _floppy->sect) अणु
			जबतक (tracksize + ssize > _floppy->sect) अणु
				raw_cmd->cmd[SIZECODE]--;
				ssize >>= 1;
			पूर्ण
			raw_cmd->cmd[SECTOR]++;
			raw_cmd->cmd[SECT_PER_TRACK]++;
			tracksize += ssize;
		पूर्ण
		max_sector = raw_cmd->cmd[HEAD] * _floppy->sect + tracksize;
	पूर्ण अन्यथा अगर (!raw_cmd->cmd[TRACK] && !raw_cmd->cmd[HEAD] && !(_floppy->rate & FD_2M) && probing) अणु
		max_sector = _floppy->sect;
	पूर्ण अन्यथा अगर (!raw_cmd->cmd[HEAD] && CT(raw_cmd->cmd[COMMAND]) == FD_WRITE) अणु
		/* क्रम भव DMA bug workaround */
		max_sector = _floppy->sect;
	पूर्ण

	in_sector_offset = (fsector_t % _floppy->sect) % ssize;
	aligned_sector_t = fsector_t - in_sector_offset;
	max_size = blk_rq_sectors(current_req);
	अगर ((raw_cmd->track == buffer_track) &&
	    (current_drive == buffer_drive) &&
	    (fsector_t >= buffer_min) && (fsector_t < buffer_max)) अणु
		/* data alपढ़ोy in track buffer */
		अगर (CT(raw_cmd->cmd[COMMAND]) == FD_READ) अणु
			copy_buffer(1, max_sector, buffer_max);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (in_sector_offset || blk_rq_sectors(current_req) < ssize) अणु
		अगर (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE) अणु
			अचिन्हित पूर्णांक sectors;

			sectors = fsector_t + blk_rq_sectors(current_req);
			अगर (sectors > ssize && sectors < ssize + ssize)
				max_size = ssize + ssize;
			अन्यथा
				max_size = ssize;
		पूर्ण
		raw_cmd->flags &= ~FD_RAW_WRITE;
		raw_cmd->flags |= FD_RAW_READ;
		raw_cmd->cmd[COMMAND] = FM_MODE(_floppy, FD_READ);
	पूर्ण

	अगर (CT(raw_cmd->cmd[COMMAND]) == FD_READ)
		max_size = max_sector;	/* unbounded */

	/* claim buffer track अगर needed */
	अगर (buffer_track != raw_cmd->track ||	/* bad track */
	    buffer_drive != current_drive ||	/* bad drive */
	    fsector_t > buffer_max ||
	    fsector_t < buffer_min ||
	    ((CT(raw_cmd->cmd[COMMAND]) == FD_READ ||
	      (!in_sector_offset && blk_rq_sectors(current_req) >= ssize)) &&
	     max_sector > 2 * max_buffer_sectors + buffer_min &&
	     max_size + fsector_t > 2 * max_buffer_sectors + buffer_min)) अणु
		/* not enough space */
		buffer_track = -1;
		buffer_drive = current_drive;
		buffer_max = buffer_min = aligned_sector_t;
	पूर्ण
	raw_cmd->kernel_data = floppy_track_buffer +
		((aligned_sector_t - buffer_min) << 9);

	अगर (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE) अणु
		/* copy ग_लिखो buffer to track buffer.
		 * अगर we get here, we know that the ग_लिखो
		 * is either aligned or the data alपढ़ोy in the buffer
		 * (buffer will be overwritten) */
		अगर (in_sector_offset && buffer_track == -1)
			DPRINT("internal error offset !=0 on write\n");
		buffer_track = raw_cmd->track;
		buffer_drive = current_drive;
		copy_buffer(ssize, max_sector,
			    2 * max_buffer_sectors + buffer_min);
	पूर्ण अन्यथा
		transfer_size(ssize, max_sector,
			      2 * max_buffer_sectors + buffer_min -
			      aligned_sector_t);

	/* round up current_count_sectors to get dma xfer size */
	raw_cmd->length = in_sector_offset + current_count_sectors;
	raw_cmd->length = ((raw_cmd->length - 1) | (ssize - 1)) + 1;
	raw_cmd->length <<= 9;
	अगर ((raw_cmd->length < current_count_sectors << 9) ||
	    (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE &&
	     (aligned_sector_t + (raw_cmd->length >> 9) > buffer_max ||
	      aligned_sector_t < buffer_min)) ||
	    raw_cmd->length % (128 << raw_cmd->cmd[SIZECODE]) ||
	    raw_cmd->length <= 0 || current_count_sectors <= 0) अणु
		DPRINT("fractionary current count b=%lx s=%lx\n",
		       raw_cmd->length, current_count_sectors);
		pr_info("addr=%d, length=%ld\n",
			(पूर्णांक)((raw_cmd->kernel_data -
			       floppy_track_buffer) >> 9),
			current_count_sectors);
		pr_info("st=%d ast=%d mse=%d msi=%d\n",
			fsector_t, aligned_sector_t, max_sector, max_size);
		pr_info("ssize=%x SIZECODE=%d\n", ssize, raw_cmd->cmd[SIZECODE]);
		pr_info("command=%x SECTOR=%d HEAD=%d, TRACK=%d\n",
			raw_cmd->cmd[COMMAND], raw_cmd->cmd[SECTOR],
			raw_cmd->cmd[HEAD], raw_cmd->cmd[TRACK]);
		pr_info("buffer drive=%d\n", buffer_drive);
		pr_info("buffer track=%d\n", buffer_track);
		pr_info("buffer_min=%d\n", buffer_min);
		pr_info("buffer_max=%d\n", buffer_max);
		वापस 0;
	पूर्ण

	अगर (raw_cmd->kernel_data < floppy_track_buffer ||
	    current_count_sectors < 0 ||
	    raw_cmd->length < 0 ||
	    raw_cmd->kernel_data + raw_cmd->length >
	    floppy_track_buffer + (max_buffer_sectors << 10)) अणु
		DPRINT("buffer overrun in schedule dma\n");
		pr_info("fsector_t=%d buffer_min=%d current_count=%ld\n",
			fsector_t, buffer_min, raw_cmd->length >> 9);
		pr_info("current_count_sectors=%ld\n",
			current_count_sectors);
		अगर (CT(raw_cmd->cmd[COMMAND]) == FD_READ)
			pr_info("read\n");
		अगर (CT(raw_cmd->cmd[COMMAND]) == FD_WRITE)
			pr_info("write\n");
		वापस 0;
	पूर्ण
	अगर (raw_cmd->length == 0) अणु
		DPRINT("zero dma transfer attempted from make_raw_request\n");
		वापस 0;
	पूर्ण

	भवdmabug_workaround();
	वापस 2;
पूर्ण

अटल पूर्णांक set_next_request(व्योम)
अणु
	current_req = list_first_entry_or_null(&floppy_reqs, काष्ठा request,
					       queuelist);
	अगर (current_req) अणु
		current_req->error_count = 0;
		list_del_init(&current_req->queuelist);
	पूर्ण
	वापस current_req != शून्य;
पूर्ण

/* Starts or जारीs processing request. Will स्वतःmatically unlock the
 * driver at end of request.
 */
अटल व्योम reकरो_fd_request(व्योम)
अणु
	पूर्णांक drive;
	पूर्णांक पंचांगp;

	lastreकरो = jअगरfies;
	अगर (current_drive < N_DRIVE)
		floppy_off(current_drive);

करो_request:
	अगर (!current_req) अणु
		पूर्णांक pending;

		spin_lock_irq(&floppy_lock);
		pending = set_next_request();
		spin_unlock_irq(&floppy_lock);
		अगर (!pending) अणु
			करो_floppy = शून्य;
			unlock_fdc();
			वापस;
		पूर्ण
	पूर्ण
	drive = (दीर्घ)current_req->rq_disk->निजी_data;
	set_fdc(drive);
	reschedule_समयout(current_drive, "redo fd request");

	set_floppy(drive);
	raw_cmd = &शेष_raw_cmd;
	raw_cmd->flags = 0;
	अगर (start_motor(reकरो_fd_request))
		वापस;

	disk_change(current_drive);
	अगर (test_bit(current_drive, &fake_change) ||
	    test_bit(FD_DISK_CHANGED_BIT, &drive_state[current_drive].flags)) अणु
		DPRINT("disk absent or changed during operation\n");
		request_करोne(0);
		जाओ करो_request;
	पूर्ण
	अगर (!_floppy) अणु	/* Autodetection */
		अगर (!probing) अणु
			drive_state[current_drive].probed_क्रमmat = 0;
			अगर (next_valid_क्रमmat(current_drive)) अणु
				DPRINT("no autodetectable formats\n");
				_floppy = शून्य;
				request_करोne(0);
				जाओ करो_request;
			पूर्ण
		पूर्ण
		probing = 1;
		_floppy = floppy_type + drive_params[current_drive].स्वतःdetect[drive_state[current_drive].probed_क्रमmat];
	पूर्ण अन्यथा
		probing = 0;
	errors = &(current_req->error_count);
	पंचांगp = make_raw_rw_request();
	अगर (पंचांगp < 2) अणु
		request_करोne(पंचांगp);
		जाओ करो_request;
	पूर्ण

	अगर (test_bit(FD_NEED_TWADDLE_BIT, &drive_state[current_drive].flags))
		twaddle(current_fdc, current_drive);
	schedule_bh(floppy_start);
	debugt(__func__, "queue fd request");
	वापस;
पूर्ण

अटल स्थिर काष्ठा cont_t rw_cont = अणु
	.पूर्णांकerrupt	= rw_पूर्णांकerrupt,
	.reकरो		= reकरो_fd_request,
	.error		= bad_flp_पूर्णांकr,
	.करोne		= request_करोne
पूर्ण;

/* schedule the request and स्वतःmatically unlock the driver on completion */
अटल व्योम process_fd_request(व्योम)
अणु
	cont = &rw_cont;
	schedule_bh(reकरो_fd_request);
पूर्ण

अटल blk_status_t floppy_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				    स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	blk_mq_start_request(bd->rq);

	अगर (WARN(max_buffer_sectors == 0,
		 "VFS: %s called on non-open device\n", __func__))
		वापस BLK_STS_IOERR;

	अगर (WARN(atomic_पढ़ो(&usage_count) == 0,
		 "warning: usage count=0, current_req=%p sect=%ld flags=%llx\n",
		 current_req, (दीर्घ)blk_rq_pos(current_req),
		 (अचिन्हित दीर्घ दीर्घ) current_req->cmd_flags))
		वापस BLK_STS_IOERR;

	अगर (test_and_set_bit(0, &fdc_busy)) अणु
		/* fdc busy, this new request will be treated when the
		   current one is करोne */
		is_alive(__func__, "old request running");
		वापस BLK_STS_RESOURCE;
	पूर्ण

	spin_lock_irq(&floppy_lock);
	list_add_tail(&bd->rq->queuelist, &floppy_reqs);
	spin_unlock_irq(&floppy_lock);

	command_status = FD_COMMAND_NONE;
	__reschedule_समयout(MAXTIMEOUT, "fd_request");
	set_fdc(0);
	process_fd_request();
	is_alive(__func__, "");
	वापस BLK_STS_OK;
पूर्ण

अटल स्थिर काष्ठा cont_t poll_cont = अणु
	.पूर्णांकerrupt	= success_and_wakeup,
	.reकरो		= floppy_पढ़ोy,
	.error		= generic_failure,
	.करोne		= generic_करोne
पूर्ण;

अटल पूर्णांक poll_drive(bool पूर्णांकerruptible, पूर्णांक flag)
अणु
	/* no स्वतः-sense, just clear dcl */
	raw_cmd = &शेष_raw_cmd;
	raw_cmd->flags = flag;
	raw_cmd->track = 0;
	raw_cmd->cmd_count = 0;
	cont = &poll_cont;
	debug_dcl(drive_params[current_drive].flags,
		  "setting NEWCHANGE in poll_drive\n");
	set_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[current_drive].flags);

	वापस रुको_til_करोne(floppy_पढ़ोy, पूर्णांकerruptible);
पूर्ण

/*
 * User triggered reset
 * ====================
 */

अटल व्योम reset_पूर्णांकr(व्योम)
अणु
	pr_info("weird, reset interrupt called\n");
पूर्ण

अटल स्थिर काष्ठा cont_t reset_cont = अणु
	.पूर्णांकerrupt	= reset_पूर्णांकr,
	.reकरो		= success_and_wakeup,
	.error		= generic_failure,
	.करोne		= generic_करोne
पूर्ण;

/*
 * Resets the FDC connected to drive <drive>.
 * Both current_drive and current_fdc are changed to match the new drive.
 */
अटल पूर्णांक user_reset_fdc(पूर्णांक drive, पूर्णांक arg, bool पूर्णांकerruptible)
अणु
	पूर्णांक ret;

	अगर (lock_fdc(drive))
		वापस -EINTR;

	अगर (arg == FD_RESET_ALWAYS)
		fdc_state[current_fdc].reset = 1;
	अगर (fdc_state[current_fdc].reset) अणु
		/* note: reset_fdc will take care of unlocking the driver
		 * on completion.
		 */
		cont = &reset_cont;
		ret = रुको_til_करोne(reset_fdc, पूर्णांकerruptible);
		अगर (ret == -EINTR)
			वापस -EINTR;
	पूर्ण
	process_fd_request();
	वापस 0;
पूर्ण

/*
 * Misc Ioctl's and support
 * ========================
 */
अटल अंतरभूत पूर्णांक fd_copyout(व्योम __user *param, स्थिर व्योम *address,
			     अचिन्हित दीर्घ size)
अणु
	वापस copy_to_user(param, address, size) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक fd_copyin(व्योम __user *param, व्योम *address,
			    अचिन्हित दीर्घ size)
अणु
	वापस copy_from_user(address, param, size) ? -EFAULT : 0;
पूर्ण

अटल स्थिर अक्षर *drive_name(पूर्णांक type, पूर्णांक drive)
अणु
	काष्ठा floppy_काष्ठा *floppy;

	अगर (type)
		floppy = floppy_type + type;
	अन्यथा अणु
		अगर (drive_params[drive].native_क्रमmat)
			floppy = floppy_type + drive_params[drive].native_क्रमmat;
		अन्यथा
			वापस "(null)";
	पूर्ण
	अगर (floppy->name)
		वापस floppy->name;
	अन्यथा
		वापस "(null)";
पूर्ण

/* raw commands */
अटल व्योम raw_cmd_करोne(पूर्णांक flag)
अणु
	अगर (!flag) अणु
		raw_cmd->flags |= FD_RAW_FAILURE;
		raw_cmd->flags |= FD_RAW_HARDFAILURE;
	पूर्ण अन्यथा अणु
		raw_cmd->reply_count = inr;
		अगर (raw_cmd->reply_count > FD_RAW_REPLY_SIZE)
			raw_cmd->reply_count = 0;
		स_नकल(raw_cmd->reply, reply_buffer, raw_cmd->reply_count);

		अगर (raw_cmd->flags & (FD_RAW_READ | FD_RAW_WRITE)) अणु
			अचिन्हित दीर्घ flags;
			flags = claim_dma_lock();
			raw_cmd->length = fd_get_dma_residue();
			release_dma_lock(flags);
		पूर्ण

		अगर ((raw_cmd->flags & FD_RAW_SOFTFAILURE) &&
		    (!raw_cmd->reply_count || (raw_cmd->reply[0] & 0xc0)))
			raw_cmd->flags |= FD_RAW_FAILURE;

		अगर (disk_change(current_drive))
			raw_cmd->flags |= FD_RAW_DISK_CHANGE;
		अन्यथा
			raw_cmd->flags &= ~FD_RAW_DISK_CHANGE;
		अगर (raw_cmd->flags & FD_RAW_NO_MOTOR_AFTER)
			motor_off_callback(&motor_off_समयr[current_drive]);

		अगर (raw_cmd->next &&
		    (!(raw_cmd->flags & FD_RAW_FAILURE) ||
		     !(raw_cmd->flags & FD_RAW_STOP_IF_FAILURE)) &&
		    ((raw_cmd->flags & FD_RAW_FAILURE) ||
		     !(raw_cmd->flags & FD_RAW_STOP_IF_SUCCESS))) अणु
			raw_cmd = raw_cmd->next;
			वापस;
		पूर्ण
	पूर्ण
	generic_करोne(flag);
पूर्ण

अटल स्थिर काष्ठा cont_t raw_cmd_cont = अणु
	.पूर्णांकerrupt	= success_and_wakeup,
	.reकरो		= floppy_start,
	.error		= generic_failure,
	.करोne		= raw_cmd_करोne
पूर्ण;

अटल पूर्णांक raw_cmd_copyout(पूर्णांक cmd, व्योम __user *param,
				  काष्ठा floppy_raw_cmd *ptr)
अणु
	पूर्णांक ret;

	जबतक (ptr) अणु
		काष्ठा floppy_raw_cmd cmd = *ptr;
		cmd.next = शून्य;
		cmd.kernel_data = शून्य;
		ret = copy_to_user(param, &cmd, माप(cmd));
		अगर (ret)
			वापस -EFAULT;
		param += माप(काष्ठा floppy_raw_cmd);
		अगर ((ptr->flags & FD_RAW_READ) && ptr->buffer_length) अणु
			अगर (ptr->length >= 0 &&
			    ptr->length <= ptr->buffer_length) अणु
				दीर्घ length = ptr->buffer_length - ptr->length;
				ret = fd_copyout(ptr->data, ptr->kernel_data,
						 length);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		ptr = ptr->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम raw_cmd_मुक्त(काष्ठा floppy_raw_cmd **ptr)
अणु
	काष्ठा floppy_raw_cmd *next;
	काष्ठा floppy_raw_cmd *this;

	this = *ptr;
	*ptr = शून्य;
	जबतक (this) अणु
		अगर (this->buffer_length) अणु
			fd_dma_mem_मुक्त((अचिन्हित दीर्घ)this->kernel_data,
					this->buffer_length);
			this->buffer_length = 0;
		पूर्ण
		next = this->next;
		kमुक्त(this);
		this = next;
	पूर्ण
पूर्ण

अटल पूर्णांक raw_cmd_copyin(पूर्णांक cmd, व्योम __user *param,
				 काष्ठा floppy_raw_cmd **rcmd)
अणु
	काष्ठा floppy_raw_cmd *ptr;
	पूर्णांक ret;

	*rcmd = शून्य;

loop:
	ptr = kदो_स्मृति(माप(काष्ठा floppy_raw_cmd), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;
	*rcmd = ptr;
	ret = copy_from_user(ptr, param, माप(*ptr));
	ptr->next = शून्य;
	ptr->buffer_length = 0;
	ptr->kernel_data = शून्य;
	अगर (ret)
		वापस -EFAULT;
	param += माप(काष्ठा floppy_raw_cmd);
	अगर (ptr->cmd_count > FD_RAW_CMD_FULLSIZE)
		वापस -EINVAL;

	स_रखो(ptr->reply, 0, FD_RAW_REPLY_SIZE);
	ptr->resultcode = 0;

	अगर (ptr->flags & (FD_RAW_READ | FD_RAW_WRITE)) अणु
		अगर (ptr->length <= 0)
			वापस -EINVAL;
		ptr->kernel_data = (अक्षर *)fd_dma_mem_alloc(ptr->length);
		fallback_on_nodma_alloc(&ptr->kernel_data, ptr->length);
		अगर (!ptr->kernel_data)
			वापस -ENOMEM;
		ptr->buffer_length = ptr->length;
	पूर्ण
	अगर (ptr->flags & FD_RAW_WRITE) अणु
		ret = fd_copyin(ptr->data, ptr->kernel_data, ptr->length);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ptr->flags & FD_RAW_MORE) अणु
		rcmd = &(ptr->next);
		ptr->rate &= 0x43;
		जाओ loop;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raw_cmd_ioctl(पूर्णांक cmd, व्योम __user *param)
अणु
	काष्ठा floppy_raw_cmd *my_raw_cmd;
	पूर्णांक drive;
	पूर्णांक ret2;
	पूर्णांक ret;

	अगर (fdc_state[current_fdc].rawcmd <= 1)
		fdc_state[current_fdc].rawcmd = 1;
	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		अगर (FDC(drive) != current_fdc)
			जारी;
		अगर (drive == current_drive) अणु
			अगर (drive_state[drive].fd_ref > 1) अणु
				fdc_state[current_fdc].rawcmd = 2;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (drive_state[drive].fd_ref) अणु
			fdc_state[current_fdc].rawcmd = 2;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fdc_state[current_fdc].reset)
		वापस -EIO;

	ret = raw_cmd_copyin(cmd, param, &my_raw_cmd);
	अगर (ret) अणु
		raw_cmd_मुक्त(&my_raw_cmd);
		वापस ret;
	पूर्ण

	raw_cmd = my_raw_cmd;
	cont = &raw_cmd_cont;
	ret = रुको_til_करोne(floppy_start, true);
	debug_dcl(drive_params[current_drive].flags,
		  "calling disk change from raw_cmd ioctl\n");

	अगर (ret != -EINTR && fdc_state[current_fdc].reset)
		ret = -EIO;

	drive_state[current_drive].track = NO_TRACK;

	ret2 = raw_cmd_copyout(cmd, param, my_raw_cmd);
	अगर (!ret)
		ret = ret2;
	raw_cmd_मुक्त(&my_raw_cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक invalidate_drive(काष्ठा block_device *bdev)
अणु
	/* invalidate the buffer track to क्रमce a reपढ़ो */
	set_bit((दीर्घ)bdev->bd_disk->निजी_data, &fake_change);
	process_fd_request();
	अगर (bdev_check_media_change(bdev))
		floppy_revalidate(bdev->bd_disk);
	वापस 0;
पूर्ण

अटल पूर्णांक set_geometry(अचिन्हित पूर्णांक cmd, काष्ठा floppy_काष्ठा *g,
			       पूर्णांक drive, पूर्णांक type, काष्ठा block_device *bdev)
अणु
	पूर्णांक cnt;

	/* sanity checking क्रम parameters. */
	अगर ((पूर्णांक)g->sect <= 0 ||
	    (पूर्णांक)g->head <= 0 ||
	    /* check क्रम overflow in max_sector */
	    (पूर्णांक)(g->sect * g->head) <= 0 ||
	    /* check क्रम zero in raw_cmd->cmd[F_SECT_PER_TRACK] */
	    (अचिन्हित अक्षर)((g->sect << 2) >> FD_SIZECODE(g)) == 0 ||
	    g->track <= 0 || g->track > drive_params[drive].tracks >> STRETCH(g) ||
	    /* check अगर reserved bits are set */
	    (g->stretch & ~(FD_STRETCH | FD_SWAPSIDES | FD_SECTBASEMASK)) != 0)
		वापस -EINVAL;
	अगर (type) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		mutex_lock(&खोलो_lock);
		अगर (lock_fdc(drive)) अणु
			mutex_unlock(&खोलो_lock);
			वापस -EINTR;
		पूर्ण
		floppy_type[type] = *g;
		floppy_type[type].name = "user format";
		क्रम (cnt = type << 2; cnt < (type << 2) + 4; cnt++)
			floppy_sizes[cnt] = floppy_sizes[cnt + 0x80] =
			    floppy_type[type].size + 1;
		process_fd_request();
		क्रम (cnt = 0; cnt < N_DRIVE; cnt++) अणु
			काष्ठा block_device *bdev = खोलोed_bdev[cnt];
			अगर (!bdev || ITYPE(drive_state[cnt].fd_device) != type)
				जारी;
			__invalidate_device(bdev, true);
		पूर्ण
		mutex_unlock(&खोलो_lock);
	पूर्ण अन्यथा अणु
		पूर्णांक oldStretch;

		अगर (lock_fdc(drive))
			वापस -EINTR;
		अगर (cmd != FDDEFPRM) अणु
			/* notice a disk change immediately, अन्यथा
			 * we lose our settings immediately*/
			अगर (poll_drive(true, FD_RAW_NEED_DISK) == -EINTR)
				वापस -EINTR;
		पूर्ण
		oldStretch = g->stretch;
		user_params[drive] = *g;
		अगर (buffer_drive == drive)
			SUPBOUND(buffer_max, user_params[drive].sect);
		current_type[drive] = &user_params[drive];
		floppy_sizes[drive] = user_params[drive].size;
		अगर (cmd == FDDEFPRM)
			drive_state[current_drive].keep_data = -1;
		अन्यथा
			drive_state[current_drive].keep_data = 1;
		/* invalidation. Invalidate only when needed, i.e.
		 * when there are alपढ़ोy sectors in the buffer cache
		 * whose number will change. This is useful, because
		 * mtools often changes the geometry of the disk after
		 * looking at the boot block */
		अगर (drive_state[current_drive].maxblock > user_params[drive].sect ||
		    drive_state[current_drive].maxtrack ||
		    ((user_params[drive].sect ^ oldStretch) &
		     (FD_SWAPSIDES | FD_SECTBASEMASK)))
			invalidate_drive(bdev);
		अन्यथा
			process_fd_request();
	पूर्ण
	वापस 0;
पूर्ण

/* handle obsolete ioctl's */
अटल अचिन्हित पूर्णांक ioctl_table[] = अणु
	FDCLRPRM,
	FDSETPRM,
	FDDEFPRM,
	FDGETPRM,
	FDMSGON,
	FDMSGOFF,
	FDFMTBEG,
	FDFMTTRK,
	FDFMTEND,
	FDSETEMSGTRESH,
	FDFLUSH,
	FDSETMAXERRS,
	FDGETMAXERRS,
	FDGETDRVTYP,
	FDSETDRVPRM,
	FDGETDRVPRM,
	FDGETDRVSTAT,
	FDPOLLDRVSTAT,
	FDRESET,
	FDGETFDCSTAT,
	FDWERRORCLR,
	FDWERRORGET,
	FDRAWCMD,
	FDEJECT,
	FDTWADDLE
पूर्ण;

अटल पूर्णांक normalize_ioctl(अचिन्हित पूर्णांक *cmd, पूर्णांक *size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ioctl_table); i++) अणु
		अगर ((*cmd & 0xffff) == (ioctl_table[i] & 0xffff)) अणु
			*size = _IOC_SIZE(*cmd);
			*cmd = ioctl_table[i];
			अगर (*size > _IOC_SIZE(*cmd)) अणु
				pr_info("ioctl not yet supported\n");
				वापस -EFAULT;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_floppy_geometry(पूर्णांक drive, पूर्णांक type, काष्ठा floppy_काष्ठा **g)
अणु
	अगर (type)
		*g = &floppy_type[type];
	अन्यथा अणु
		अगर (lock_fdc(drive))
			वापस -EINTR;
		अगर (poll_drive(false, 0) == -EINTR)
			वापस -EINTR;
		process_fd_request();
		*g = current_type[drive];
	पूर्ण
	अगर (!*g)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक fd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	पूर्णांक drive = (दीर्घ)bdev->bd_disk->निजी_data;
	पूर्णांक type = ITYPE(drive_state[drive].fd_device);
	काष्ठा floppy_काष्ठा *g;
	पूर्णांक ret;

	ret = get_floppy_geometry(drive, type, &g);
	अगर (ret)
		वापस ret;

	geo->heads = g->head;
	geo->sectors = g->sect;
	geo->cylinders = g->track;
	वापस 0;
पूर्ण

अटल bool valid_floppy_drive_params(स्थिर लघु स्वतःdetect[FD_AUTODETECT_SIZE],
		पूर्णांक native_क्रमmat)
अणु
	माप_प्रकार floppy_type_size = ARRAY_SIZE(floppy_type);
	माप_प्रकार i = 0;

	क्रम (i = 0; i < FD_AUTODETECT_SIZE; ++i) अणु
		अगर (स्वतःdetect[i] < 0 ||
		    स्वतःdetect[i] >= floppy_type_size)
			वापस false;
	पूर्ण

	अगर (native_क्रमmat < 0 || native_क्रमmat >= floppy_type_size)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक fd_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
		    अचिन्हित दीर्घ param)
अणु
	पूर्णांक drive = (दीर्घ)bdev->bd_disk->निजी_data;
	पूर्णांक type = ITYPE(drive_state[drive].fd_device);
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक size;
	जोड़ inparam अणु
		काष्ठा floppy_काष्ठा g;	/* geometry */
		काष्ठा क्रमmat_descr f;
		काष्ठा floppy_max_errors max_errors;
		काष्ठा floppy_drive_params dp;
	पूर्ण inparam;		/* parameters coming from user space */
	स्थिर व्योम *outparam;	/* parameters passed back to user space */

	/* convert compatibility eject ioctls पूर्णांकo floppy eject ioctl.
	 * We करो this in order to provide a means to eject floppy disks beक्रमe
	 * installing the new fdutils package */
	अगर (cmd == CDROMEJECT ||	/* CD-ROM eject */
	    cmd == 0x6470) अणु		/* SunOS floppy eject */
		DPRINT("obsolete eject ioctl\n");
		DPRINT("please use floppycontrol --eject\n");
		cmd = FDEJECT;
	पूर्ण

	अगर (!((cmd & 0xff00) == 0x0200))
		वापस -EINVAL;

	/* convert the old style command पूर्णांकo a new style command */
	ret = normalize_ioctl(&cmd, &size);
	अगर (ret)
		वापस ret;

	/* permission checks */
	अगर (((cmd & 0x40) && !(mode & (FMODE_WRITE | FMODE_WRITE_IOCTL))) ||
	    ((cmd & 0x80) && !capable(CAP_SYS_ADMIN)))
		वापस -EPERM;

	अगर (WARN_ON(size < 0 || size > माप(inparam)))
		वापस -EINVAL;

	/* copyin */
	स_रखो(&inparam, 0, माप(inparam));
	अगर (_IOC_सूची(cmd) & _IOC_WRITE) अणु
		ret = fd_copyin((व्योम __user *)param, &inparam, size);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (cmd) अणु
	हाल FDEJECT:
		अगर (drive_state[drive].fd_ref != 1)
			/* somebody अन्यथा has this drive खोलो */
			वापस -EBUSY;
		अगर (lock_fdc(drive))
			वापस -EINTR;

		/* करो the actual eject. Fails on
		 * non-Sparc architectures */
		ret = fd_eject(UNIT(drive));

		set_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags);
		set_bit(FD_VERIFY_BIT, &drive_state[drive].flags);
		process_fd_request();
		वापस ret;
	हाल FDCLRPRM:
		अगर (lock_fdc(drive))
			वापस -EINTR;
		current_type[drive] = शून्य;
		floppy_sizes[drive] = MAX_DISK_SIZE << 1;
		drive_state[drive].keep_data = 0;
		वापस invalidate_drive(bdev);
	हाल FDSETPRM:
	हाल FDDEFPRM:
		वापस set_geometry(cmd, &inparam.g, drive, type, bdev);
	हाल FDGETPRM:
		ret = get_floppy_geometry(drive, type,
					  (काष्ठा floppy_काष्ठा **)&outparam);
		अगर (ret)
			वापस ret;
		स_नकल(&inparam.g, outparam,
				दुरत्व(काष्ठा floppy_काष्ठा, name));
		outparam = &inparam.g;
		अवरोध;
	हाल FDMSGON:
		drive_params[drive].flags |= FTD_MSG;
		वापस 0;
	हाल FDMSGOFF:
		drive_params[drive].flags &= ~FTD_MSG;
		वापस 0;
	हाल FDFMTBEG:
		अगर (lock_fdc(drive))
			वापस -EINTR;
		अगर (poll_drive(true, FD_RAW_NEED_DISK) == -EINTR)
			वापस -EINTR;
		ret = drive_state[drive].flags;
		process_fd_request();
		अगर (ret & FD_VERIFY)
			वापस -ENODEV;
		अगर (!(ret & FD_DISK_WRITABLE))
			वापस -EROFS;
		वापस 0;
	हाल FDFMTTRK:
		अगर (drive_state[drive].fd_ref != 1)
			वापस -EBUSY;
		वापस करो_क्रमmat(drive, &inparam.f);
	हाल FDFMTEND:
	हाल FDFLUSH:
		अगर (lock_fdc(drive))
			वापस -EINTR;
		वापस invalidate_drive(bdev);
	हाल FDSETEMSGTRESH:
		drive_params[drive].max_errors.reporting = (अचिन्हित लघु)(param & 0x0f);
		वापस 0;
	हाल FDGETMAXERRS:
		outparam = &drive_params[drive].max_errors;
		अवरोध;
	हाल FDSETMAXERRS:
		drive_params[drive].max_errors = inparam.max_errors;
		अवरोध;
	हाल FDGETDRVTYP:
		outparam = drive_name(type, drive);
		SUPBOUND(size, म_माप((स्थिर अक्षर *)outparam) + 1);
		अवरोध;
	हाल FDSETDRVPRM:
		अगर (!valid_floppy_drive_params(inparam.dp.स्वतःdetect,
				inparam.dp.native_क्रमmat))
			वापस -EINVAL;
		drive_params[drive] = inparam.dp;
		अवरोध;
	हाल FDGETDRVPRM:
		outparam = &drive_params[drive];
		अवरोध;
	हाल FDPOLLDRVSTAT:
		अगर (lock_fdc(drive))
			वापस -EINTR;
		अगर (poll_drive(true, FD_RAW_NEED_DISK) == -EINTR)
			वापस -EINTR;
		process_fd_request();
		fallthrough;
	हाल FDGETDRVSTAT:
		outparam = &drive_state[drive];
		अवरोध;
	हाल FDRESET:
		वापस user_reset_fdc(drive, (पूर्णांक)param, true);
	हाल FDGETFDCSTAT:
		outparam = &fdc_state[FDC(drive)];
		अवरोध;
	हाल FDWERRORCLR:
		स_रखो(&ग_लिखो_errors[drive], 0, माप(ग_लिखो_errors[drive]));
		वापस 0;
	हाल FDWERRORGET:
		outparam = &ग_लिखो_errors[drive];
		अवरोध;
	हाल FDRAWCMD:
		अगर (type)
			वापस -EINVAL;
		अगर (lock_fdc(drive))
			वापस -EINTR;
		set_floppy(drive);
		i = raw_cmd_ioctl(cmd, (व्योम __user *)param);
		अगर (i == -EINTR)
			वापस -EINTR;
		process_fd_request();
		वापस i;
	हाल FDTWADDLE:
		अगर (lock_fdc(drive))
			वापस -EINTR;
		twaddle(current_fdc, current_drive);
		process_fd_request();
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (_IOC_सूची(cmd) & _IOC_READ)
		वापस fd_copyout((व्योम __user *)param, outparam, size);

	वापस 0;
पूर्ण

अटल पूर्णांक fd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	पूर्णांक ret;

	mutex_lock(&floppy_mutex);
	ret = fd_locked_ioctl(bdev, mode, cmd, param);
	mutex_unlock(&floppy_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_floppy_drive_params अणु
	अक्षर		cmos;
	compat_uदीर्घ_t	max_dtr;
	compat_uदीर्घ_t	hlt;
	compat_uदीर्घ_t	hut;
	compat_uदीर्घ_t	srt;
	compat_uदीर्घ_t	spinup;
	compat_uदीर्घ_t	spinकरोwn;
	अचिन्हित अक्षर	spinकरोwn_offset;
	अचिन्हित अक्षर	select_delay;
	अचिन्हित अक्षर	rps;
	अचिन्हित अक्षर	tracks;
	compat_uदीर्घ_t	समयout;
	अचिन्हित अक्षर	पूर्णांकerleave_sect;
	काष्ठा floppy_max_errors max_errors;
	अक्षर		flags;
	अक्षर		पढ़ो_track;
	लघु		स्वतःdetect[FD_AUTODETECT_SIZE];
	compat_पूर्णांक_t	checkfreq;
	compat_पूर्णांक_t	native_क्रमmat;
पूर्ण;

काष्ठा compat_floppy_drive_काष्ठा अणु
	चिन्हित अक्षर	flags;
	compat_uदीर्घ_t	spinup_date;
	compat_uदीर्घ_t	select_date;
	compat_uदीर्घ_t	first_पढ़ो_date;
	लघु		probed_क्रमmat;
	लघु		track;
	लघु		maxblock;
	लघु		maxtrack;
	compat_पूर्णांक_t	generation;
	compat_पूर्णांक_t	keep_data;
	compat_पूर्णांक_t	fd_ref;
	compat_पूर्णांक_t	fd_device;
	compat_पूर्णांक_t	last_checked;
	compat_caddr_t dmabuf;
	compat_पूर्णांक_t	bufblocks;
पूर्ण;

काष्ठा compat_floppy_fdc_state अणु
	compat_पूर्णांक_t	spec1;
	compat_पूर्णांक_t	spec2;
	compat_पूर्णांक_t	dtr;
	अचिन्हित अक्षर	version;
	अचिन्हित अक्षर	करोr;
	compat_uदीर्घ_t	address;
	अचिन्हित पूर्णांक	rawcmd:2;
	अचिन्हित पूर्णांक	reset:1;
	अचिन्हित पूर्णांक	need_configure:1;
	अचिन्हित पूर्णांक	perp_mode:2;
	अचिन्हित पूर्णांक	has_fअगरo:1;
	अचिन्हित पूर्णांक	driver_version;
	अचिन्हित अक्षर	track[4];
पूर्ण;

काष्ठा compat_floppy_ग_लिखो_errors अणु
	अचिन्हित पूर्णांक	ग_लिखो_errors;
	compat_uदीर्घ_t	first_error_sector;
	compat_पूर्णांक_t	first_error_generation;
	compat_uदीर्घ_t	last_error_sector;
	compat_पूर्णांक_t	last_error_generation;
	compat_uपूर्णांक_t	badness;
पूर्ण;

#घोषणा FDSETPRM32 _IOW(2, 0x42, काष्ठा compat_floppy_काष्ठा)
#घोषणा FDDEFPRM32 _IOW(2, 0x43, काष्ठा compat_floppy_काष्ठा)
#घोषणा FDSETDRVPRM32 _IOW(2, 0x90, काष्ठा compat_floppy_drive_params)
#घोषणा FDGETDRVPRM32 _IOR(2, 0x11, काष्ठा compat_floppy_drive_params)
#घोषणा FDGETDRVSTAT32 _IOR(2, 0x12, काष्ठा compat_floppy_drive_काष्ठा)
#घोषणा FDPOLLDRVSTAT32 _IOR(2, 0x13, काष्ठा compat_floppy_drive_काष्ठा)
#घोषणा FDGETFDCSTAT32 _IOR(2, 0x15, काष्ठा compat_floppy_fdc_state)
#घोषणा FDWERRORGET32  _IOR(2, 0x17, काष्ठा compat_floppy_ग_लिखो_errors)

अटल पूर्णांक compat_set_geometry(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
		    काष्ठा compat_floppy_काष्ठा __user *arg)
अणु
	काष्ठा floppy_काष्ठा v;
	पूर्णांक drive, type;
	पूर्णांक err;

	BUILD_BUG_ON(दुरत्व(काष्ठा floppy_काष्ठा, name) !=
		     दुरत्व(काष्ठा compat_floppy_काष्ठा, name));

	अगर (!(mode & (FMODE_WRITE | FMODE_WRITE_IOCTL)))
		वापस -EPERM;

	स_रखो(&v, 0, माप(काष्ठा floppy_काष्ठा));
	अगर (copy_from_user(&v, arg, दुरत्व(काष्ठा floppy_काष्ठा, name)))
		वापस -EFAULT;

	mutex_lock(&floppy_mutex);
	drive = (दीर्घ)bdev->bd_disk->निजी_data;
	type = ITYPE(drive_state[drive].fd_device);
	err = set_geometry(cmd == FDSETPRM32 ? FDSETPRM : FDDEFPRM,
			&v, drive, type, bdev);
	mutex_unlock(&floppy_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक compat_get_prm(पूर्णांक drive,
			  काष्ठा compat_floppy_काष्ठा __user *arg)
अणु
	काष्ठा compat_floppy_काष्ठा v;
	काष्ठा floppy_काष्ठा *p;
	पूर्णांक err;

	स_रखो(&v, 0, माप(v));
	mutex_lock(&floppy_mutex);
	err = get_floppy_geometry(drive, ITYPE(drive_state[drive].fd_device),
				  &p);
	अगर (err) अणु
		mutex_unlock(&floppy_mutex);
		वापस err;
	पूर्ण
	स_नकल(&v, p, दुरत्व(काष्ठा floppy_काष्ठा, name));
	mutex_unlock(&floppy_mutex);
	अगर (copy_to_user(arg, &v, माप(काष्ठा compat_floppy_काष्ठा)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_setdrvprm(पूर्णांक drive,
			    काष्ठा compat_floppy_drive_params __user *arg)
अणु
	काष्ठा compat_floppy_drive_params v;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&v, arg, माप(काष्ठा compat_floppy_drive_params)))
		वापस -EFAULT;
	अगर (!valid_floppy_drive_params(v.स्वतःdetect, v.native_क्रमmat))
		वापस -EINVAL;
	mutex_lock(&floppy_mutex);
	drive_params[drive].cmos = v.cmos;
	drive_params[drive].max_dtr = v.max_dtr;
	drive_params[drive].hlt = v.hlt;
	drive_params[drive].hut = v.hut;
	drive_params[drive].srt = v.srt;
	drive_params[drive].spinup = v.spinup;
	drive_params[drive].spinकरोwn = v.spinकरोwn;
	drive_params[drive].spinकरोwn_offset = v.spinकरोwn_offset;
	drive_params[drive].select_delay = v.select_delay;
	drive_params[drive].rps = v.rps;
	drive_params[drive].tracks = v.tracks;
	drive_params[drive].समयout = v.समयout;
	drive_params[drive].पूर्णांकerleave_sect = v.पूर्णांकerleave_sect;
	drive_params[drive].max_errors = v.max_errors;
	drive_params[drive].flags = v.flags;
	drive_params[drive].पढ़ो_track = v.पढ़ो_track;
	स_नकल(drive_params[drive].स्वतःdetect, v.स्वतःdetect,
	       माप(v.स्वतःdetect));
	drive_params[drive].checkfreq = v.checkfreq;
	drive_params[drive].native_क्रमmat = v.native_क्रमmat;
	mutex_unlock(&floppy_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक compat_getdrvprm(पूर्णांक drive,
			    काष्ठा compat_floppy_drive_params __user *arg)
अणु
	काष्ठा compat_floppy_drive_params v;

	स_रखो(&v, 0, माप(काष्ठा compat_floppy_drive_params));
	mutex_lock(&floppy_mutex);
	v.cmos = drive_params[drive].cmos;
	v.max_dtr = drive_params[drive].max_dtr;
	v.hlt = drive_params[drive].hlt;
	v.hut = drive_params[drive].hut;
	v.srt = drive_params[drive].srt;
	v.spinup = drive_params[drive].spinup;
	v.spinकरोwn = drive_params[drive].spinकरोwn;
	v.spinकरोwn_offset = drive_params[drive].spinकरोwn_offset;
	v.select_delay = drive_params[drive].select_delay;
	v.rps = drive_params[drive].rps;
	v.tracks = drive_params[drive].tracks;
	v.समयout = drive_params[drive].समयout;
	v.पूर्णांकerleave_sect = drive_params[drive].पूर्णांकerleave_sect;
	v.max_errors = drive_params[drive].max_errors;
	v.flags = drive_params[drive].flags;
	v.पढ़ो_track = drive_params[drive].पढ़ो_track;
	स_नकल(v.स्वतःdetect, drive_params[drive].स्वतःdetect,
	       माप(v.स्वतःdetect));
	v.checkfreq = drive_params[drive].checkfreq;
	v.native_क्रमmat = drive_params[drive].native_क्रमmat;
	mutex_unlock(&floppy_mutex);

	अगर (copy_to_user(arg, &v, माप(काष्ठा compat_floppy_drive_params)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_getdrvstat(पूर्णांक drive, bool poll,
			    काष्ठा compat_floppy_drive_काष्ठा __user *arg)
अणु
	काष्ठा compat_floppy_drive_काष्ठा v;

	स_रखो(&v, 0, माप(काष्ठा compat_floppy_drive_काष्ठा));
	mutex_lock(&floppy_mutex);

	अगर (poll) अणु
		अगर (lock_fdc(drive))
			जाओ Eपूर्णांकr;
		अगर (poll_drive(true, FD_RAW_NEED_DISK) == -EINTR)
			जाओ Eपूर्णांकr;
		process_fd_request();
	पूर्ण
	v.spinup_date = drive_state[drive].spinup_date;
	v.select_date = drive_state[drive].select_date;
	v.first_पढ़ो_date = drive_state[drive].first_पढ़ो_date;
	v.probed_क्रमmat = drive_state[drive].probed_क्रमmat;
	v.track = drive_state[drive].track;
	v.maxblock = drive_state[drive].maxblock;
	v.maxtrack = drive_state[drive].maxtrack;
	v.generation = drive_state[drive].generation;
	v.keep_data = drive_state[drive].keep_data;
	v.fd_ref = drive_state[drive].fd_ref;
	v.fd_device = drive_state[drive].fd_device;
	v.last_checked = drive_state[drive].last_checked;
	v.dmabuf = (uपूर्णांकptr_t) drive_state[drive].dmabuf;
	v.bufblocks = drive_state[drive].bufblocks;
	mutex_unlock(&floppy_mutex);

	अगर (copy_to_user(arg, &v, माप(काष्ठा compat_floppy_drive_काष्ठा)))
		वापस -EFAULT;
	वापस 0;
Eपूर्णांकr:
	mutex_unlock(&floppy_mutex);
	वापस -EINTR;
पूर्ण

अटल पूर्णांक compat_getfdcstat(पूर्णांक drive,
			    काष्ठा compat_floppy_fdc_state __user *arg)
अणु
	काष्ठा compat_floppy_fdc_state v32;
	काष्ठा floppy_fdc_state v;

	mutex_lock(&floppy_mutex);
	v = fdc_state[FDC(drive)];
	mutex_unlock(&floppy_mutex);

	स_रखो(&v32, 0, माप(काष्ठा compat_floppy_fdc_state));
	v32.spec1 = v.spec1;
	v32.spec2 = v.spec2;
	v32.dtr = v.dtr;
	v32.version = v.version;
	v32.करोr = v.करोr;
	v32.address = v.address;
	v32.rawcmd = v.rawcmd;
	v32.reset = v.reset;
	v32.need_configure = v.need_configure;
	v32.perp_mode = v.perp_mode;
	v32.has_fअगरo = v.has_fअगरo;
	v32.driver_version = v.driver_version;
	स_नकल(v32.track, v.track, 4);
	अगर (copy_to_user(arg, &v32, माप(काष्ठा compat_floppy_fdc_state)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_werrorget(पूर्णांक drive,
			    काष्ठा compat_floppy_ग_लिखो_errors __user *arg)
अणु
	काष्ठा compat_floppy_ग_लिखो_errors v32;
	काष्ठा floppy_ग_लिखो_errors v;

	स_रखो(&v32, 0, माप(काष्ठा compat_floppy_ग_लिखो_errors));
	mutex_lock(&floppy_mutex);
	v = ग_लिखो_errors[drive];
	mutex_unlock(&floppy_mutex);
	v32.ग_लिखो_errors = v.ग_लिखो_errors;
	v32.first_error_sector = v.first_error_sector;
	v32.first_error_generation = v.first_error_generation;
	v32.last_error_sector = v.last_error_sector;
	v32.last_error_generation = v.last_error_generation;
	v32.badness = v.badness;
	अगर (copy_to_user(arg, &v32, माप(काष्ठा compat_floppy_ग_लिखो_errors)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक fd_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
		    अचिन्हित दीर्घ param)
अणु
	पूर्णांक drive = (दीर्घ)bdev->bd_disk->निजी_data;
	चयन (cmd) अणु
	हाल CDROMEJECT: /* CD-ROM eject */
	हाल 0x6470:	 /* SunOS floppy eject */

	हाल FDMSGON:
	हाल FDMSGOFF:
	हाल FDSETEMSGTRESH:
	हाल FDFLUSH:
	हाल FDWERRORCLR:
	हाल FDEJECT:
	हाल FDCLRPRM:
	हाल FDFMTBEG:
	हाल FDRESET:
	हाल FDTWADDLE:
		वापस fd_ioctl(bdev, mode, cmd, param);
	हाल FDSETMAXERRS:
	हाल FDGETMAXERRS:
	हाल FDGETDRVTYP:
	हाल FDFMTEND:
	हाल FDFMTTRK:
	हाल FDRAWCMD:
		वापस fd_ioctl(bdev, mode, cmd,
				(अचिन्हित दीर्घ)compat_ptr(param));
	हाल FDSETPRM32:
	हाल FDDEFPRM32:
		वापस compat_set_geometry(bdev, mode, cmd, compat_ptr(param));
	हाल FDGETPRM32:
		वापस compat_get_prm(drive, compat_ptr(param));
	हाल FDSETDRVPRM32:
		वापस compat_setdrvprm(drive, compat_ptr(param));
	हाल FDGETDRVPRM32:
		वापस compat_getdrvprm(drive, compat_ptr(param));
	हाल FDPOLLDRVSTAT32:
		वापस compat_getdrvstat(drive, true, compat_ptr(param));
	हाल FDGETDRVSTAT32:
		वापस compat_getdrvstat(drive, false, compat_ptr(param));
	हाल FDGETFDCSTAT32:
		वापस compat_getfdcstat(drive, compat_ptr(param));
	हाल FDWERRORGET32:
		वापस compat_werrorget(drive, compat_ptr(param));
	पूर्ण
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init config_types(व्योम)
अणु
	bool has_drive = false;
	पूर्णांक drive;

	/* पढ़ो drive info out of physical CMOS */
	drive = 0;
	अगर (!drive_params[drive].cmos)
		drive_params[drive].cmos = FLOPPY0_TYPE;
	drive = 1;
	अगर (!drive_params[drive].cmos)
		drive_params[drive].cmos = FLOPPY1_TYPE;

	/* FIXME: additional physical CMOS drive detection should go here */

	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		अचिन्हित पूर्णांक type = drive_params[drive].cmos;
		काष्ठा floppy_drive_params *params;
		स्थिर अक्षर *name = शून्य;
		अक्षर temparea[32];

		अगर (type < ARRAY_SIZE(शेष_drive_params)) अणु
			params = &शेष_drive_params[type].params;
			अगर (type) अणु
				name = शेष_drive_params[type].name;
				allowed_drive_mask |= 1 << drive;
			पूर्ण अन्यथा
				allowed_drive_mask &= ~(1 << drive);
		पूर्ण अन्यथा अणु
			params = &शेष_drive_params[0].params;
			snम_लिखो(temparea, माप(temparea),
				 "unknown type %d (usb?)", type);
			name = temparea;
		पूर्ण
		अगर (name) अणु
			स्थिर अक्षर *prepend;
			अगर (!has_drive) अणु
				prepend = "";
				has_drive = true;
				pr_info("Floppy drive(s):");
			पूर्ण अन्यथा अणु
				prepend = ",";
			पूर्ण

			pr_cont("%s fd%d is %s", prepend, drive, name);
		पूर्ण
		drive_params[drive] = *params;
	पूर्ण

	अगर (has_drive)
		pr_cont("\n");
पूर्ण

अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	पूर्णांक drive = (दीर्घ)disk->निजी_data;

	mutex_lock(&floppy_mutex);
	mutex_lock(&खोलो_lock);
	अगर (!drive_state[drive].fd_ref--) अणु
		DPRINT("floppy_release with fd_ref == 0");
		drive_state[drive].fd_ref = 0;
	पूर्ण
	अगर (!drive_state[drive].fd_ref)
		खोलोed_bdev[drive] = शून्य;
	mutex_unlock(&खोलो_lock);
	mutex_unlock(&floppy_mutex);
पूर्ण

/*
 * floppy_खोलो check क्रम aliasing (/dev/fd0 can be the same as
 * /dev/PS0 etc), and disallows simultaneous access to the same
 * drive with dअगरferent device numbers.
 */
अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक drive = (दीर्घ)bdev->bd_disk->निजी_data;
	पूर्णांक old_dev, new_dev;
	पूर्णांक try;
	पूर्णांक res = -EBUSY;
	अक्षर *पंचांगp;

	mutex_lock(&floppy_mutex);
	mutex_lock(&खोलो_lock);
	old_dev = drive_state[drive].fd_device;
	अगर (खोलोed_bdev[drive] && खोलोed_bdev[drive] != bdev)
		जाओ out2;

	अगर (!drive_state[drive].fd_ref && (drive_params[drive].flags & FD_BROKEN_DCL)) अणु
		set_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags);
		set_bit(FD_VERIFY_BIT, &drive_state[drive].flags);
	पूर्ण

	drive_state[drive].fd_ref++;

	खोलोed_bdev[drive] = bdev;

	res = -ENXIO;

	अगर (!floppy_track_buffer) अणु
		/* अगर खोलोing an ED drive, reserve a big buffer,
		 * अन्यथा reserve a small one */
		अगर ((drive_params[drive].cmos == 6) || (drive_params[drive].cmos == 5))
			try = 64;	/* Only 48 actually useful */
		अन्यथा
			try = 32;	/* Only 24 actually useful */

		पंचांगp = (अक्षर *)fd_dma_mem_alloc(1024 * try);
		अगर (!पंचांगp && !floppy_track_buffer) अणु
			try >>= 1;	/* buffer only one side */
			INFBOUND(try, 16);
			पंचांगp = (अक्षर *)fd_dma_mem_alloc(1024 * try);
		पूर्ण
		अगर (!पंचांगp && !floppy_track_buffer)
			fallback_on_nodma_alloc(&पंचांगp, 2048 * try);
		अगर (!पंचांगp && !floppy_track_buffer) अणु
			DPRINT("Unable to allocate DMA memory\n");
			जाओ out;
		पूर्ण
		अगर (floppy_track_buffer) अणु
			अगर (पंचांगp)
				fd_dma_mem_मुक्त((अचिन्हित दीर्घ)पंचांगp, try * 1024);
		पूर्ण अन्यथा अणु
			buffer_min = buffer_max = -1;
			floppy_track_buffer = पंचांगp;
			max_buffer_sectors = try;
		पूर्ण
	पूर्ण

	new_dev = MINOR(bdev->bd_dev);
	drive_state[drive].fd_device = new_dev;
	set_capacity(disks[drive][ITYPE(new_dev)], floppy_sizes[new_dev]);
	अगर (old_dev != -1 && old_dev != new_dev) अणु
		अगर (buffer_drive == drive)
			buffer_track = -1;
	पूर्ण

	अगर (fdc_state[FDC(drive)].rawcmd == 1)
		fdc_state[FDC(drive)].rawcmd = 2;

	अगर (mode & (FMODE_READ|FMODE_WRITE)) अणु
		drive_state[drive].last_checked = 0;
		clear_bit(FD_OPEN_SHOULD_FAIL_BIT, &drive_state[drive].flags);
		अगर (bdev_check_media_change(bdev))
			floppy_revalidate(bdev->bd_disk);
		अगर (test_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags))
			जाओ out;
		अगर (test_bit(FD_OPEN_SHOULD_FAIL_BIT, &drive_state[drive].flags))
			जाओ out;
	पूर्ण

	res = -EROFS;

	अगर ((mode & FMODE_WRITE) &&
			!test_bit(FD_DISK_WRITABLE_BIT, &drive_state[drive].flags))
		जाओ out;

	mutex_unlock(&खोलो_lock);
	mutex_unlock(&floppy_mutex);
	वापस 0;
out:
	drive_state[drive].fd_ref--;

	अगर (!drive_state[drive].fd_ref)
		खोलोed_bdev[drive] = शून्य;
out2:
	mutex_unlock(&खोलो_lock);
	mutex_unlock(&floppy_mutex);
	वापस res;
पूर्ण

/*
 * Check अगर the disk has been changed or अगर a change has been faked.
 */
अटल अचिन्हित पूर्णांक floppy_check_events(काष्ठा gendisk *disk,
					अचिन्हित पूर्णांक clearing)
अणु
	पूर्णांक drive = (दीर्घ)disk->निजी_data;

	अगर (test_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags) ||
	    test_bit(FD_VERIFY_BIT, &drive_state[drive].flags))
		वापस DISK_EVENT_MEDIA_CHANGE;

	अगर (समय_after(jअगरfies, drive_state[drive].last_checked + drive_params[drive].checkfreq)) अणु
		अगर (lock_fdc(drive))
			वापस 0;
		poll_drive(false, 0);
		process_fd_request();
	पूर्ण

	अगर (test_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags) ||
	    test_bit(FD_VERIFY_BIT, &drive_state[drive].flags) ||
	    test_bit(drive, &fake_change) ||
	    drive_no_geom(drive))
		वापस DISK_EVENT_MEDIA_CHANGE;
	वापस 0;
पूर्ण

/*
 * This implements "read block 0" क्रम floppy_revalidate().
 * Needed क्रम क्रमmat स्वतःdetection, checking whether there is
 * a disk in the drive, and whether that disk is writable.
 */

काष्ठा rb0_cbdata अणु
	पूर्णांक drive;
	काष्ठा completion complete;
पूर्ण;

अटल व्योम floppy_rb0_cb(काष्ठा bio *bio)
अणु
	काष्ठा rb0_cbdata *cbdata = (काष्ठा rb0_cbdata *)bio->bi_निजी;
	पूर्णांक drive = cbdata->drive;

	अगर (bio->bi_status) अणु
		pr_info("floppy: error %d while reading block 0\n",
			bio->bi_status);
		set_bit(FD_OPEN_SHOULD_FAIL_BIT, &drive_state[drive].flags);
	पूर्ण
	complete(&cbdata->complete);
पूर्ण

अटल पूर्णांक __floppy_पढ़ो_block_0(काष्ठा block_device *bdev, पूर्णांक drive)
अणु
	काष्ठा bio bio;
	काष्ठा bio_vec bio_vec;
	काष्ठा page *page;
	काष्ठा rb0_cbdata cbdata;

	page = alloc_page(GFP_NOIO);
	अगर (!page) अणु
		process_fd_request();
		वापस -ENOMEM;
	पूर्ण

	cbdata.drive = drive;

	bio_init(&bio, &bio_vec, 1);
	bio_set_dev(&bio, bdev);
	bio_add_page(&bio, page, block_size(bdev), 0);

	bio.bi_iter.bi_sector = 0;
	bio.bi_flags |= (1 << BIO_QUIET);
	bio.bi_निजी = &cbdata;
	bio.bi_end_io = floppy_rb0_cb;
	bio_set_op_attrs(&bio, REQ_OP_READ, 0);

	init_completion(&cbdata.complete);

	submit_bio(&bio);
	process_fd_request();

	रुको_क्रम_completion(&cbdata.complete);

	__मुक्त_page(page);

	वापस 0;
पूर्ण

/* revalidate the floppy disk, i.e. trigger क्रमmat स्वतःdetection by पढ़ोing
 * the bootblock (block 0). "Autodetection" is also needed to check whether
 * there is a disk in the drive at all... Thus we also करो it क्रम fixed
 * geometry क्रमmats */
अटल पूर्णांक floppy_revalidate(काष्ठा gendisk *disk)
अणु
	पूर्णांक drive = (दीर्घ)disk->निजी_data;
	पूर्णांक cf;
	पूर्णांक res = 0;

	अगर (test_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags) ||
	    test_bit(FD_VERIFY_BIT, &drive_state[drive].flags) ||
	    test_bit(drive, &fake_change) ||
	    drive_no_geom(drive)) अणु
		अगर (WARN(atomic_पढ़ो(&usage_count) == 0,
			 "VFS: revalidate called on non-open device.\n"))
			वापस -EFAULT;

		res = lock_fdc(drive);
		अगर (res)
			वापस res;
		cf = (test_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags) ||
		      test_bit(FD_VERIFY_BIT, &drive_state[drive].flags));
		अगर (!(cf || test_bit(drive, &fake_change) || drive_no_geom(drive))) अणु
			process_fd_request();	/*alपढ़ोy करोne by another thपढ़ो */
			वापस 0;
		पूर्ण
		drive_state[drive].maxblock = 0;
		drive_state[drive].maxtrack = 0;
		अगर (buffer_drive == drive)
			buffer_track = -1;
		clear_bit(drive, &fake_change);
		clear_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags);
		अगर (cf)
			drive_state[drive].generation++;
		अगर (drive_no_geom(drive)) अणु
			/* स्वतः-sensing */
			res = __floppy_पढ़ो_block_0(खोलोed_bdev[drive], drive);
		पूर्ण अन्यथा अणु
			अगर (cf)
				poll_drive(false, FD_RAW_NEED_DISK);
			process_fd_request();
		पूर्ण
	पूर्ण
	set_capacity(disk, floppy_sizes[drive_state[drive].fd_device]);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा block_device_operations floppy_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= floppy_खोलो,
	.release		= floppy_release,
	.ioctl			= fd_ioctl,
	.getgeo			= fd_getgeo,
	.check_events		= floppy_check_events,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= fd_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/*
 * Floppy Driver initialization
 * =============================
 */

/* Determine the floppy disk controller type */
/* This routine was written by David C. Niemi */
अटल अक्षर __init get_fdc_version(पूर्णांक fdc)
अणु
	पूर्णांक r;

	output_byte(fdc, FD_DUMPREGS);	/* 82072 and better know DUMPREGS */
	अगर (fdc_state[fdc].reset)
		वापस FDC_NONE;
	r = result(fdc);
	अगर (r <= 0x00)
		वापस FDC_NONE;	/* No FDC present ??? */
	अगर ((r == 1) && (reply_buffer[ST0] == 0x80)) अणु
		pr_info("FDC %d is an 8272A\n", fdc);
		वापस FDC_8272A;	/* 8272a/765 करोn't know DUMPREGS */
	पूर्ण
	अगर (r != 10) अणु
		pr_info("FDC %d init: DUMPREGS: unexpected return of %d bytes.\n",
			fdc, r);
		वापस FDC_UNKNOWN;
	पूर्ण

	अगर (!fdc_configure(fdc)) अणु
		pr_info("FDC %d is an 82072\n", fdc);
		वापस FDC_82072;	/* 82072 करोesn't know CONFIGURE */
	पूर्ण

	output_byte(fdc, FD_PERPENDICULAR);
	अगर (need_more_output(fdc) == MORE_OUTPUT) अणु
		output_byte(fdc, 0);
	पूर्ण अन्यथा अणु
		pr_info("FDC %d is an 82072A\n", fdc);
		वापस FDC_82072A;	/* 82072A as found on Sparcs. */
	पूर्ण

	output_byte(fdc, FD_UNLOCK);
	r = result(fdc);
	अगर ((r == 1) && (reply_buffer[ST0] == 0x80)) अणु
		pr_info("FDC %d is a pre-1991 82077\n", fdc);
		वापस FDC_82077_ORIG;	/* Pre-1991 82077, करोesn't know
					 * LOCK/UNLOCK */
	पूर्ण
	अगर ((r != 1) || (reply_buffer[ST0] != 0x00)) अणु
		pr_info("FDC %d init: UNLOCK: unexpected return of %d bytes.\n",
			fdc, r);
		वापस FDC_UNKNOWN;
	पूर्ण
	output_byte(fdc, FD_PARTID);
	r = result(fdc);
	अगर (r != 1) अणु
		pr_info("FDC %d init: PARTID: unexpected return of %d bytes.\n",
			fdc, r);
		वापस FDC_UNKNOWN;
	पूर्ण
	अगर (reply_buffer[ST0] == 0x80) अणु
		pr_info("FDC %d is a post-1991 82077\n", fdc);
		वापस FDC_82077;	/* Revised 82077AA passes all the tests */
	पूर्ण
	चयन (reply_buffer[ST0] >> 5) अणु
	हाल 0x0:
		/* Either a 82078-1 or a 82078SL running at 5Volt */
		pr_info("FDC %d is an 82078.\n", fdc);
		वापस FDC_82078;
	हाल 0x1:
		pr_info("FDC %d is a 44pin 82078\n", fdc);
		वापस FDC_82078;
	हाल 0x2:
		pr_info("FDC %d is a S82078B\n", fdc);
		वापस FDC_S82078B;
	हाल 0x3:
		pr_info("FDC %d is a National Semiconductor PC87306\n", fdc);
		वापस FDC_87306;
	शेष:
		pr_info("FDC %d init: 82078 variant with unknown PARTID=%d.\n",
			fdc, reply_buffer[ST0] >> 5);
		वापस FDC_82078_UNKN;
	पूर्ण
पूर्ण				/* get_fdc_version */

/* lilo configuration */

अटल व्योम __init floppy_set_flags(पूर्णांक *पूर्णांकs, पूर्णांक param, पूर्णांक param2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(शेष_drive_params); i++) अणु
		अगर (param)
			शेष_drive_params[i].params.flags |= param2;
		अन्यथा
			शेष_drive_params[i].params.flags &= ~param2;
	पूर्ण
	DPRINT("%s flag 0x%x\n", param2 ? "Setting" : "Clearing", param);
पूर्ण

अटल व्योम __init daring(पूर्णांक *पूर्णांकs, पूर्णांक param, पूर्णांक param2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(शेष_drive_params); i++) अणु
		अगर (param) अणु
			शेष_drive_params[i].params.select_delay = 0;
			शेष_drive_params[i].params.flags |=
			    FD_SILENT_DCL_CLEAR;
		पूर्ण अन्यथा अणु
			शेष_drive_params[i].params.select_delay =
			    2 * HZ / 100;
			शेष_drive_params[i].params.flags &=
			    ~FD_SILENT_DCL_CLEAR;
		पूर्ण
	पूर्ण
	DPRINT("Assuming %s floppy hardware\n", param ? "standard" : "broken");
पूर्ण

अटल व्योम __init set_cmos(पूर्णांक *पूर्णांकs, पूर्णांक dummy, पूर्णांक dummy2)
अणु
	पूर्णांक current_drive = 0;

	अगर (पूर्णांकs[0] != 2) अणु
		DPRINT("wrong number of parameters for CMOS\n");
		वापस;
	पूर्ण
	current_drive = पूर्णांकs[1];
	अगर (current_drive < 0 || current_drive >= 8) अणु
		DPRINT("bad drive for set_cmos\n");
		वापस;
	पूर्ण
#अगर N_FDC > 1
	अगर (current_drive >= 4 && !FDC2)
		FDC2 = 0x370;
#पूर्ण_अगर
	drive_params[current_drive].cmos = पूर्णांकs[2];
	DPRINT("setting CMOS code to %d\n", पूर्णांकs[2]);
पूर्ण

अटल काष्ठा param_table अणु
	स्थिर अक्षर *name;
	व्योम (*fn) (पूर्णांक *पूर्णांकs, पूर्णांक param, पूर्णांक param2);
	पूर्णांक *var;
	पूर्णांक def_param;
	पूर्णांक param2;
पूर्ण config_params[] __initdata = अणु
	अणु"allowed_drive_mask", शून्य, &allowed_drive_mask, 0xff, 0पूर्ण, /* obsolete */
	अणु"all_drives", शून्य, &allowed_drive_mask, 0xff, 0पूर्ण,	/* obsolete */
	अणु"asus_pci", शून्य, &allowed_drive_mask, 0x33, 0पूर्ण,
	अणु"irq", शून्य, &FLOPPY_IRQ, 6, 0पूर्ण,
	अणु"dma", शून्य, &FLOPPY_DMA, 2, 0पूर्ण,
	अणु"daring", daring, शून्य, 1, 0पूर्ण,
#अगर N_FDC > 1
	अणु"two_fdc", शून्य, &FDC2, 0x370, 0पूर्ण,
	अणु"one_fdc", शून्य, &FDC2, 0, 0पूर्ण,
#पूर्ण_अगर
	अणु"thinkpad", floppy_set_flags, शून्य, 1, FD_INVERTED_DCLपूर्ण,
	अणु"broken_dcl", floppy_set_flags, शून्य, 1, FD_BROKEN_DCLपूर्ण,
	अणु"messages", floppy_set_flags, शून्य, 1, FTD_MSGपूर्ण,
	अणु"silent_dcl_clear", floppy_set_flags, शून्य, 1, FD_SILENT_DCL_CLEARपूर्ण,
	अणु"debug", floppy_set_flags, शून्य, 1, FD_DEBUGपूर्ण,
	अणु"nodma", शून्य, &can_use_भव_dma, 1, 0पूर्ण,
	अणु"omnibook", शून्य, &can_use_भव_dma, 1, 0पूर्ण,
	अणु"yesdma", शून्य, &can_use_भव_dma, 0, 0पूर्ण,
	अणु"fifo_depth", शून्य, &fअगरo_depth, 0xa, 0पूर्ण,
	अणु"nofifo", शून्य, &no_fअगरo, 0x20, 0पूर्ण,
	अणु"usefifo", शून्य, &no_fअगरo, 0, 0पूर्ण,
	अणु"cmos", set_cmos, शून्य, 0, 0पूर्ण,
	अणु"slow", शून्य, &slow_floppy, 1, 0पूर्ण,
	अणु"unexpected_interrupts", शून्य, &prपूर्णांक_unex, 1, 0पूर्ण,
	अणु"no_unexpected_interrupts", शून्य, &prपूर्णांक_unex, 0, 0पूर्ण,
	अणु"L40SX", शून्य, &prपूर्णांक_unex, 0, 0पूर्ण

	EXTRA_FLOPPY_PARAMS
पूर्ण;

अटल पूर्णांक __init floppy_setup(अक्षर *str)
अणु
	पूर्णांक i;
	पूर्णांक param;
	पूर्णांक पूर्णांकs[11];

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);
	अगर (str) अणु
		क्रम (i = 0; i < ARRAY_SIZE(config_params); i++) अणु
			अगर (म_भेद(str, config_params[i].name) == 0) अणु
				अगर (पूर्णांकs[0])
					param = पूर्णांकs[1];
				अन्यथा
					param = config_params[i].def_param;
				अगर (config_params[i].fn)
					config_params[i].fn(पूर्णांकs, param,
							    config_params[i].
							    param2);
				अगर (config_params[i].var) अणु
					DPRINT("%s=%d\n", str, param);
					*config_params[i].var = param;
				पूर्ण
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (str) अणु
		DPRINT("unknown floppy option [%s]\n", str);

		DPRINT("allowed options are:");
		क्रम (i = 0; i < ARRAY_SIZE(config_params); i++)
			pr_cont(" %s", config_params[i].name);
		pr_cont("\n");
	पूर्ण अन्यथा
		DPRINT("botched floppy option\n");
	DPRINT("Read Documentation/admin-guide/blockdev/floppy.rst\n");
	वापस 0;
पूर्ण

अटल पूर्णांक have_no_fdc = -ENODEV;

अटल sमाप_प्रकार floppy_cmos_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *p = to_platक्रमm_device(dev);
	पूर्णांक drive;

	drive = p->id;
	वापस प्र_लिखो(buf, "%X\n", drive_params[drive].cmos);
पूर्ण

अटल DEVICE_ATTR(cmos, 0444, floppy_cmos_show, शून्य);

अटल काष्ठा attribute *floppy_dev_attrs[] = अणु
	&dev_attr_cmos.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(floppy_dev);

अटल व्योम floppy_device_release(काष्ठा device *dev)
अणु
पूर्ण

अटल पूर्णांक floppy_resume(काष्ठा device *dev)
अणु
	पूर्णांक fdc;
	पूर्णांक saved_drive;

	saved_drive = current_drive;
	क्रम (fdc = 0; fdc < N_FDC; fdc++)
		अगर (fdc_state[fdc].address != -1)
			user_reset_fdc(REVDRIVE(fdc, 0), FD_RESET_ALWAYS, false);
	set_fdc(saved_drive);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops floppy_pm_ops = अणु
	.resume = floppy_resume,
	.restore = floppy_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver floppy_driver = अणु
	.driver = अणु
		   .name = "floppy",
		   .pm = &floppy_pm_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops floppy_mq_ops = अणु
	.queue_rq = floppy_queue_rq,
पूर्ण;

अटल काष्ठा platक्रमm_device floppy_device[N_DRIVE];

अटल bool floppy_available(पूर्णांक drive)
अणु
	अगर (!(allowed_drive_mask & (1 << drive)))
		वापस false;
	अगर (fdc_state[FDC(drive)].version == FDC_NONE)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक floppy_alloc_disk(अचिन्हित पूर्णांक drive, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gendisk *disk;
	पूर्णांक err;

	disk = alloc_disk(1);
	अगर (!disk)
		वापस -ENOMEM;

	disk->queue = blk_mq_init_queue(&tag_sets[drive]);
	अगर (IS_ERR(disk->queue)) अणु
		err = PTR_ERR(disk->queue);
		disk->queue = शून्य;
		put_disk(disk);
		वापस err;
	पूर्ण

	blk_queue_max_hw_sectors(disk->queue, 64);
	disk->major = FLOPPY_MAJOR;
	disk->first_minor = TOMINOR(drive) | (type << 2);
	disk->fops = &floppy_fops;
	disk->events = DISK_EVENT_MEDIA_CHANGE;
	अगर (type)
		प्र_लिखो(disk->disk_name, "fd%d_type%d", drive, type);
	अन्यथा
		प्र_लिखो(disk->disk_name, "fd%d", drive);
	/* to be cleaned up... */
	disk->निजी_data = (व्योम *)(दीर्घ)drive;
	disk->flags |= GENHD_FL_REMOVABLE;

	disks[drive][type] = disk;
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(floppy_probe_lock);

अटल व्योम floppy_probe(dev_t dev)
अणु
	अचिन्हित पूर्णांक drive = (MINOR(dev) & 3) | ((MINOR(dev) & 0x80) >> 5);
	अचिन्हित पूर्णांक type = (MINOR(dev) >> 2) & 0x1f;

	अगर (drive >= N_DRIVE || !floppy_available(drive) ||
	    type >= ARRAY_SIZE(floppy_type))
		वापस;

	mutex_lock(&floppy_probe_lock);
	अगर (!disks[drive][type]) अणु
		अगर (floppy_alloc_disk(drive, type) == 0)
			add_disk(disks[drive][type]);
	पूर्ण
	mutex_unlock(&floppy_probe_lock);
पूर्ण

अटल पूर्णांक __init करो_floppy_init(व्योम)
अणु
	पूर्णांक i, unit, drive, err;

	set_debugt();
	पूर्णांकerruptjअगरfies = resultjअगरfies = jअगरfies;

#अगर defined(CONFIG_PPC)
	अगर (check_legacy_ioport(FDC1))
		वापस -ENODEV;
#पूर्ण_अगर

	raw_cmd = शून्य;

	floppy_wq = alloc_ordered_workqueue("floppy", 0);
	अगर (!floppy_wq)
		वापस -ENOMEM;

	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		स_रखो(&tag_sets[drive], 0, माप(tag_sets[drive]));
		tag_sets[drive].ops = &floppy_mq_ops;
		tag_sets[drive].nr_hw_queues = 1;
		tag_sets[drive].nr_maps = 1;
		tag_sets[drive].queue_depth = 2;
		tag_sets[drive].numa_node = NUMA_NO_NODE;
		tag_sets[drive].flags = BLK_MQ_F_SHOULD_MERGE;
		err = blk_mq_alloc_tag_set(&tag_sets[drive]);
		अगर (err)
			जाओ out_put_disk;

		err = floppy_alloc_disk(drive, 0);
		अगर (err)
			जाओ out_put_disk;

		समयr_setup(&motor_off_समयr[drive], motor_off_callback, 0);
	पूर्ण

	err = __रेजिस्टर_blkdev(FLOPPY_MAJOR, "fd", floppy_probe);
	अगर (err)
		जाओ out_put_disk;

	err = platक्रमm_driver_रेजिस्टर(&floppy_driver);
	अगर (err)
		जाओ out_unreg_blkdev;

	क्रम (i = 0; i < 256; i++)
		अगर (ITYPE(i))
			floppy_sizes[i] = floppy_type[ITYPE(i)].size;
		अन्यथा
			floppy_sizes[i] = MAX_DISK_SIZE << 1;

	reschedule_समयout(MAXTIMEOUT, "floppy init");
	config_types();

	क्रम (i = 0; i < N_FDC; i++) अणु
		स_रखो(&fdc_state[i], 0, माप(*fdc_state));
		fdc_state[i].dtr = -1;
		fdc_state[i].करोr = 0x4;
#अगर defined(__sparc__) || defined(__mc68000__)
	/*sparcs/sun3x करोn't have a DOR reset which we can fall back on to */
#अगर_घोषित __mc68000__
		अगर (MACH_IS_SUN3X)
#पूर्ण_अगर
			fdc_state[i].version = FDC_82072A;
#पूर्ण_अगर
	पूर्ण

	use_भव_dma = can_use_भव_dma & 1;
	fdc_state[0].address = FDC1;
	अगर (fdc_state[0].address == -1) अणु
		cancel_delayed_work(&fd_समयout);
		err = -ENODEV;
		जाओ out_unreg_driver;
	पूर्ण
#अगर N_FDC > 1
	fdc_state[1].address = FDC2;
#पूर्ण_अगर

	current_fdc = 0;	/* reset fdc in हाल of unexpected पूर्णांकerrupt */
	err = floppy_grab_irq_and_dma();
	अगर (err) अणु
		cancel_delayed_work(&fd_समयout);
		err = -EBUSY;
		जाओ out_unreg_driver;
	पूर्ण

	/* initialise drive state */
	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		स_रखो(&drive_state[drive], 0, माप(drive_state[drive]));
		स_रखो(&ग_लिखो_errors[drive], 0, माप(ग_लिखो_errors[drive]));
		set_bit(FD_DISK_NEWCHANGE_BIT, &drive_state[drive].flags);
		set_bit(FD_DISK_CHANGED_BIT, &drive_state[drive].flags);
		set_bit(FD_VERIFY_BIT, &drive_state[drive].flags);
		drive_state[drive].fd_device = -1;
		floppy_track_buffer = शून्य;
		max_buffer_sectors = 0;
	पूर्ण
	/*
	 * Small 10 msec delay to let through any पूर्णांकerrupt that
	 * initialization might have triggered, to not
	 * confuse detection:
	 */
	msleep(10);

	क्रम (i = 0; i < N_FDC; i++) अणु
		fdc_state[i].driver_version = FD_DRIVER_VERSION;
		क्रम (unit = 0; unit < 4; unit++)
			fdc_state[i].track[unit] = 0;
		अगर (fdc_state[i].address == -1)
			जारी;
		fdc_state[i].rawcmd = 2;
		अगर (user_reset_fdc(REVDRIVE(i, 0), FD_RESET_ALWAYS, false)) अणु
			/* मुक्त ioports reserved by floppy_grab_irq_and_dma() */
			floppy_release_regions(i);
			fdc_state[i].address = -1;
			fdc_state[i].version = FDC_NONE;
			जारी;
		पूर्ण
		/* Try to determine the floppy controller type */
		fdc_state[i].version = get_fdc_version(i);
		अगर (fdc_state[i].version == FDC_NONE) अणु
			/* मुक्त ioports reserved by floppy_grab_irq_and_dma() */
			floppy_release_regions(i);
			fdc_state[i].address = -1;
			जारी;
		पूर्ण
		अगर (can_use_भव_dma == 2 &&
		    fdc_state[i].version < FDC_82072A)
			can_use_भव_dma = 0;

		have_no_fdc = 0;
		/* Not all FDCs seem to be able to handle the version command
		 * properly, so क्रमce a reset क्रम the standard FDC clones,
		 * to aव्योम पूर्णांकerrupt garbage.
		 */
		user_reset_fdc(REVDRIVE(i, 0), FD_RESET_ALWAYS, false);
	पूर्ण
	current_fdc = 0;
	cancel_delayed_work(&fd_समयout);
	current_drive = 0;
	initialized = true;
	अगर (have_no_fdc) अणु
		DPRINT("no floppy controllers found\n");
		err = have_no_fdc;
		जाओ out_release_dma;
	पूर्ण

	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		अगर (!floppy_available(drive))
			जारी;

		floppy_device[drive].name = floppy_device_name;
		floppy_device[drive].id = drive;
		floppy_device[drive].dev.release = floppy_device_release;
		floppy_device[drive].dev.groups = floppy_dev_groups;

		err = platक्रमm_device_रेजिस्टर(&floppy_device[drive]);
		अगर (err)
			जाओ out_हटाओ_drives;

		device_add_disk(&floppy_device[drive].dev, disks[drive][0],
				शून्य);
	पूर्ण

	वापस 0;

out_हटाओ_drives:
	जबतक (drive--) अणु
		अगर (floppy_available(drive)) अणु
			del_gendisk(disks[drive][0]);
			platक्रमm_device_unरेजिस्टर(&floppy_device[drive]);
		पूर्ण
	पूर्ण
out_release_dma:
	अगर (atomic_पढ़ो(&usage_count))
		floppy_release_irq_and_dma();
out_unreg_driver:
	platक्रमm_driver_unरेजिस्टर(&floppy_driver);
out_unreg_blkdev:
	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
out_put_disk:
	destroy_workqueue(floppy_wq);
	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		अगर (!disks[drive][0])
			अवरोध;
		del_समयr_sync(&motor_off_समयr[drive]);
		blk_cleanup_queue(disks[drive][0]->queue);
		disks[drive][0]->queue = शून्य;
		blk_mq_मुक्त_tag_set(&tag_sets[drive]);
		put_disk(disks[drive][0]);
	पूर्ण
	वापस err;
पूर्ण

#अगर_अघोषित MODULE
अटल __init व्योम floppy_async_init(व्योम *data, async_cookie_t cookie)
अणु
	करो_floppy_init();
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init floppy_init(व्योम)
अणु
#अगर_घोषित MODULE
	वापस करो_floppy_init();
#अन्यथा
	/* Don't hold up the bootup by the floppy initialization */
	async_schedule(floppy_async_init, शून्य);
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा io_region अणु
	पूर्णांक offset;
	पूर्णांक size;
पूर्ण io_regions[] = अणु
	अणु 2, 1 पूर्ण,
	/* address + 3 is someबार reserved by pnp bios क्रम motherboard */
	अणु 4, 2 पूर्ण,
	/* address + 6 is reserved, and may be taken by IDE.
	 * Unक्रमtunately, Adaptec करोesn't know this :-(, */
	अणु 7, 1 पूर्ण,
पूर्ण;

अटल व्योम floppy_release_allocated_regions(पूर्णांक fdc, स्थिर काष्ठा io_region *p)
अणु
	जबतक (p != io_regions) अणु
		p--;
		release_region(fdc_state[fdc].address + p->offset, p->size);
	पूर्ण
पूर्ण

#घोषणा ARRAY_END(X) (&((X)[ARRAY_SIZE(X)]))

अटल पूर्णांक floppy_request_regions(पूर्णांक fdc)
अणु
	स्थिर काष्ठा io_region *p;

	क्रम (p = io_regions; p < ARRAY_END(io_regions); p++) अणु
		अगर (!request_region(fdc_state[fdc].address + p->offset,
				    p->size, "floppy")) अणु
			DPRINT("Floppy io-port 0x%04lx in use\n",
			       fdc_state[fdc].address + p->offset);
			floppy_release_allocated_regions(fdc, p);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम floppy_release_regions(पूर्णांक fdc)
अणु
	floppy_release_allocated_regions(fdc, ARRAY_END(io_regions));
पूर्ण

अटल पूर्णांक floppy_grab_irq_and_dma(व्योम)
अणु
	पूर्णांक fdc;

	अगर (atomic_inc_वापस(&usage_count) > 1)
		वापस 0;

	/*
	 * We might have scheduled a मुक्त_irq(), रुको it to
	 * drain first:
	 */
	flush_workqueue(floppy_wq);

	अगर (fd_request_irq()) अणु
		DPRINT("Unable to grab IRQ%d for the floppy driver\n",
		       FLOPPY_IRQ);
		atomic_dec(&usage_count);
		वापस -1;
	पूर्ण
	अगर (fd_request_dma()) अणु
		DPRINT("Unable to grab DMA%d for the floppy driver\n",
		       FLOPPY_DMA);
		अगर (can_use_भव_dma & 2)
			use_भव_dma = can_use_भव_dma = 1;
		अगर (!(can_use_भव_dma & 1)) अणु
			fd_मुक्त_irq();
			atomic_dec(&usage_count);
			वापस -1;
		पूर्ण
	पूर्ण

	क्रम (fdc = 0; fdc < N_FDC; fdc++) अणु
		अगर (fdc_state[fdc].address != -1) अणु
			अगर (floppy_request_regions(fdc))
				जाओ cleanup;
		पूर्ण
	पूर्ण
	क्रम (fdc = 0; fdc < N_FDC; fdc++) अणु
		अगर (fdc_state[fdc].address != -1) अणु
			reset_fdc_info(fdc, 1);
			fdc_outb(fdc_state[fdc].करोr, fdc, FD_DOR);
		पूर्ण
	पूर्ण

	set_करोr(0, ~0, 8);	/* aव्योम immediate पूर्णांकerrupt */

	क्रम (fdc = 0; fdc < N_FDC; fdc++)
		अगर (fdc_state[fdc].address != -1)
			fdc_outb(fdc_state[fdc].करोr, fdc, FD_DOR);
	/*
	 * The driver will try and मुक्त resources and relies on us
	 * to know अगर they were allocated or not.
	 */
	current_fdc = 0;
	irqdma_allocated = 1;
	वापस 0;
cleanup:
	fd_मुक्त_irq();
	fd_मुक्त_dma();
	जबतक (--fdc >= 0)
		floppy_release_regions(fdc);
	current_fdc = 0;
	atomic_dec(&usage_count);
	वापस -1;
पूर्ण

अटल व्योम floppy_release_irq_and_dma(व्योम)
अणु
	पूर्णांक fdc;
#अगर_अघोषित __sparc__
	पूर्णांक drive;
#पूर्ण_अगर
	दीर्घ पंचांगpsize;
	अचिन्हित दीर्घ पंचांगpaddr;

	अगर (!atomic_dec_and_test(&usage_count))
		वापस;

	अगर (irqdma_allocated) अणु
		fd_disable_dma();
		fd_मुक्त_dma();
		fd_मुक्त_irq();
		irqdma_allocated = 0;
	पूर्ण
	set_करोr(0, ~0, 8);
#अगर N_FDC > 1
	set_करोr(1, ~8, 0);
#पूर्ण_अगर

	अगर (floppy_track_buffer && max_buffer_sectors) अणु
		पंचांगpsize = max_buffer_sectors * 1024;
		पंचांगpaddr = (अचिन्हित दीर्घ)floppy_track_buffer;
		floppy_track_buffer = शून्य;
		max_buffer_sectors = 0;
		buffer_min = buffer_max = -1;
		fd_dma_mem_मुक्त(पंचांगpaddr, पंचांगpsize);
	पूर्ण
#अगर_अघोषित __sparc__
	क्रम (drive = 0; drive < N_FDC * 4; drive++)
		अगर (समयr_pending(motor_off_समयr + drive))
			pr_info("motor off timer %d still active\n", drive);
#पूर्ण_अगर

	अगर (delayed_work_pending(&fd_समयout))
		pr_info("floppy timer still active:%s\n", समयout_message);
	अगर (delayed_work_pending(&fd_समयr))
		pr_info("auxiliary floppy timer still active\n");
	अगर (work_pending(&floppy_work))
		pr_info("work still pending\n");
	क्रम (fdc = 0; fdc < N_FDC; fdc++)
		अगर (fdc_state[fdc].address != -1)
			floppy_release_regions(fdc);
पूर्ण

#अगर_घोषित MODULE

अटल अक्षर *floppy;

अटल व्योम __init parse_floppy_cfg_string(अक्षर *cfg)
अणु
	अक्षर *ptr;

	जबतक (*cfg) अणु
		ptr = cfg;
		जबतक (*cfg && *cfg != ' ' && *cfg != '\t')
			cfg++;
		अगर (*cfg) अणु
			*cfg = '\0';
			cfg++;
		पूर्ण
		अगर (*ptr)
			floppy_setup(ptr);
	पूर्ण
पूर्ण

अटल पूर्णांक __init floppy_module_init(व्योम)
अणु
	अगर (floppy)
		parse_floppy_cfg_string(floppy);
	वापस floppy_init();
पूर्ण
module_init(floppy_module_init);

अटल व्योम __निकास floppy_module_निकास(व्योम)
अणु
	पूर्णांक drive, i;

	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
	platक्रमm_driver_unरेजिस्टर(&floppy_driver);

	destroy_workqueue(floppy_wq);

	क्रम (drive = 0; drive < N_DRIVE; drive++) अणु
		del_समयr_sync(&motor_off_समयr[drive]);

		अगर (floppy_available(drive)) अणु
			क्रम (i = 0; i < ARRAY_SIZE(floppy_type); i++) अणु
				अगर (disks[drive][i])
					del_gendisk(disks[drive][i]);
			पूर्ण
			platक्रमm_device_unरेजिस्टर(&floppy_device[drive]);
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(floppy_type); i++) अणु
			अगर (disks[drive][i])
				blk_cleanup_queue(disks[drive][i]->queue);
		पूर्ण
		blk_mq_मुक्त_tag_set(&tag_sets[drive]);

		/*
		 * These disks have not called add_disk().  Don't put करोwn
		 * queue reference in put_disk().
		 */
		अगर (!(allowed_drive_mask & (1 << drive)) ||
		    fdc_state[FDC(drive)].version == FDC_NONE) अणु
			क्रम (i = 0; i < ARRAY_SIZE(floppy_type); i++) अणु
				अगर (disks[drive][i])
					disks[drive][i]->queue = शून्य;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(floppy_type); i++) अणु
			अगर (disks[drive][i])
				put_disk(disks[drive][i]);
		पूर्ण
	पूर्ण

	cancel_delayed_work_sync(&fd_समयout);
	cancel_delayed_work_sync(&fd_समयr);

	अगर (atomic_पढ़ो(&usage_count))
		floppy_release_irq_and_dma();

	/* eject disk, अगर any */
	fd_eject(0);
पूर्ण

module_निकास(floppy_module_निकास);

module_param(floppy, अक्षरp, 0);
module_param(FLOPPY_IRQ, पूर्णांक, 0);
module_param(FLOPPY_DMA, पूर्णांक, 0);
MODULE_AUTHOR("Alain L. Knaff");
MODULE_LICENSE("GPL");

/* This करोesn't actually get used other than क्रम module inक्रमmation */
अटल स्थिर काष्ठा pnp_device_id floppy_pnpids[] = अणु
	अणु"PNP0700", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, floppy_pnpids);

#अन्यथा

__setup("floppy=", floppy_setup);
module_init(floppy_init)
#पूर्ण_अगर

MODULE_ALIAS_BLOCKDEV_MAJOR(FLOPPY_MAJOR);
