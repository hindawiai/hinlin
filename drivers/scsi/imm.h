<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*  Driver क्रम the Iomega MatchMaker parallel port SCSI HBA embedded in 
 * the Iomega ZIP Plus drive
 * 
 * (c) 1998     David Campbell
 *
 * Please note that I live in Perth, Western Australia. GMT+0800
 */

#अगर_अघोषित _IMM_H
#घोषणा _IMM_H

#घोषणा   IMM_VERSION   "2.05 (for Linux 2.4.0)"

/* 
 * 10 Apr 1998 (Good Friday) - Received EN144302 by email from Iomega.
 * Scarry thing is the level of support from one of their managers.
 * The onus is now on us (the developers) to shut up and start coding.
 *                                              11Apr98 [ 0.10 ]
 *
 * --- SNIP ---
 *
 * It manages to find the drive which is a good start. Writing data during
 * data phase is known to be broken (due to requirements of two byte ग_लिखोs).
 * Removing "Phase" debug messages.
 *
 * PS: Took four hours of coding after I bought a drive.
 *      ANZAC Day (Aus "War Veterans Holiday")  25Apr98 [ 0.14 ]
 *
 * Ten minutes later after a few fixes.... (LITERALLY!!!)
 * Have mounted disk, copied file, dismounted disk, remount disk, dअगरf file
 *                    -----  It actually works!!! -----
 *                                              25Apr98 [ 0.15 ]
 *
 * Twenty minutes of mucking around, rearanged the IEEE negotiate mechanism.
 * Now have byte mode working (only EPP and ECP to go now... :=)
 *                                              26Apr98 [ 0.16 ]
 *
 * Thirty minutes of further coding results in EPP working on my machine.
 *                                              27Apr98 [ 0.17 ]
 *
 * Due to work commiपंचांगents and inability to get a "true" ECP mode functioning
 * I have decided to code the parport support पूर्णांकo imm.
 *                                              09Jun98 [ 0.18 ]
 *
 * Driver is now out of beta testing.
 * Support क्रम parport has been added.
 * Now distributed with the ppa driver.
 *                                              12Jun98 [ 2.00 ]
 *
 * Err.. It appears that imm-2.00 was broken....
 *                                              18Jun98 [ 2.01 ]
 *
 * Patch applied to sync this against the Linux 2.1.x kernel code
 * Included qboot_zip.sh
 *                                              21Jun98 [ 2.02 ]
 *
 * Other clean ups include the follow changes:
 *    CONFIG_SCSI_PPA_HAVE_PEDANTIC => CONFIG_SCSI_IZIP_EPP16
 *    added CONFIG_SCSI_IZIP_SLOW_CTR option
 *                                                      [2.03]
 *  Fix kernel panic on scsi समयout.		20Aug00 [2.04]
 *
 *  Aव्योम io_request_lock problems.
 *  John Cavan <johncavan@home.com>		16Nov00 [2.05]
 */
/* ------ END OF USER CONFIGURABLE PARAMETERS ----- */

#समावेश  <linux/मानकघोष.स>
#समावेश  <linux/module.h>
#समावेश  <linux/kernel.h>
#समावेश  <linux/ioport.h>
#समावेश  <linux/delay.h>
#समावेश  <linux/proc_fs.h>
#समावेश  <linux/स्थिति.स>
#समावेश  <linux/blkdev.h>
#समावेश  <linux/sched.h>
#समावेश  <linux/पूर्णांकerrupt.h>

#समावेश  <यंत्र/पन.स>
#समावेश  <scsi/scsi_host.h>
/* batteries not included :-) */

/*
 * modes in which the driver can operate 
 */
#घोषणा   IMM_AUTODETECT        0	/* Autodetect mode                */
#घोषणा   IMM_NIBBLE            1	/* work in standard 4 bit mode    */
#घोषणा   IMM_PS2               2	/* PS/2 byte mode         */
#घोषणा   IMM_EPP_8             3	/* EPP mode, 8 bit                */
#घोषणा   IMM_EPP_16            4	/* EPP mode, 16 bit               */
#घोषणा   IMM_EPP_32            5	/* EPP mode, 32 bit               */
#घोषणा   IMM_UNKNOWN           6	/* Just in हाल...                */

अटल अक्षर *IMM_MODE_STRING[] =
अणु
	[IMM_AUTODETECT] = "Autodetect",
	[IMM_NIBBLE]	 = "SPP",
	[IMM_PS2]	 = "PS/2",
	[IMM_EPP_8]	 = "EPP 8 bit",
	[IMM_EPP_16]	 = "EPP 16 bit",
#अगर_घोषित CONFIG_SCSI_IZIP_EPP16
	[IMM_EPP_32]	 = "EPP 16 bit",
#अन्यथा
	[IMM_EPP_32]	 = "EPP 32 bit",
#पूर्ण_अगर
	[IMM_UNKNOWN]	 = "Unknown",
पूर्ण;

/* other options */
#घोषणा IMM_BURST_SIZE	512	/* data burst size */
#घोषणा IMM_SELECT_TMO  500	/* 500 how दीर्घ to रुको क्रम target ? */
#घोषणा IMM_SPIN_TMO    5000	/* 50000 imm_रुको loop limiter */
#घोषणा IMM_DEBUG	0	/* debugging option */
#घोषणा IN_EPP_MODE(x) (x == IMM_EPP_8 || x == IMM_EPP_16 || x == IMM_EPP_32)

/* args to imm_connect */
#घोषणा CONNECT_EPP_MAYBE 1
#घोषणा CONNECT_NORMAL  0

#घोषणा r_dtr(x)        (अचिन्हित अक्षर)inb((x))
#घोषणा r_str(x)        (अचिन्हित अक्षर)inb((x)+1)
#घोषणा r_ctr(x)        (अचिन्हित अक्षर)inb((x)+2)
#घोषणा r_epp(x)        (अचिन्हित अक्षर)inb((x)+4)
#घोषणा r_fअगरo(x)       (अचिन्हित अक्षर)inb((x))   /* x must be base_hi */
					/* On PCI is: base+0x400 != base_hi */
#घोषणा r_ecr(x)        (अचिन्हित अक्षर)inb((x)+2) /* x must be base_hi */

#घोषणा w_dtr(x,y)      outb(y, (x))
#घोषणा w_str(x,y)      outb(y, (x)+1)
#घोषणा w_epp(x,y)      outb(y, (x)+4)
#घोषणा w_fअगरo(x,y)     outb(y, (x))     /* x must be base_hi */
#घोषणा w_ecr(x,y)      outb(y, (x)+0x2) /* x must be base_hi */

#अगर_घोषित CONFIG_SCSI_IZIP_SLOW_CTR
#घोषणा w_ctr(x,y)      outb_p(y, (x)+2)
#अन्यथा
#घोषणा w_ctr(x,y)      outb(y, (x)+2)
#पूर्ण_अगर

अटल पूर्णांक imm_engine(imm_काष्ठा *, काष्ठा scsi_cmnd *);

#पूर्ण_अगर				/* _IMM_H */
