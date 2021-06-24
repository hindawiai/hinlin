<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Driver क्रम the PPA3 parallel port SCSI HBA embedded in 
 * the Iomega ZIP drive
 * 
 * (c) 1996     Grant R. Guenther  grant@torque.net
 *              David Campbell
 *
 *      All comments to David.
 */

#अगर_अघोषित _PPA_H
#घोषणा _PPA_H

#घोषणा   PPA_VERSION   "2.07 (for Linux 2.4.x)"

/* 
 * this driver has been hacked by Matteo Frigo (athena@theory.lcs.mit.edu)
 * to support EPP and scatter-gather.                        [0.26-athena]
 *
 * additional hacks by David Campbell
 * in response to this driver "mis-behaving" on his machine.
 *      Fixed EPP to handle "software" changing of EPP port data direction.
 *      Chased करोwn EPP समयouts
 *      Made this driver "kernel version friendly"           [0.28-athena]
 *
 * [ Stuff हटाओd ]
 *
 * Corrected ppa.h क्रम 2.1.x kernels (>=2.1.85)
 * Modअगरied "Nat Semi Kludge" क्रम extended chipsets
 *                                                      [1.41]
 *
 * Fixed id_probe क्रम EPP 1.9 chipsets (misdetected as EPP 1.7)
 *                                                      [1.42]
 *
 * Development solely क्रम 2.1.x kernels from now on!
 *                                                      [2.00]
 *
 * Hack and slash at the init code (EPP device check routine)
 * Added INSANE option.
 *                                                      [2.01]
 *
 * Patch applied to sync against the 2.1.x kernel code
 * Included qboot_zip.sh
 *                                                      [2.02]
 *
 * Cleaned up the mess left by someone अन्यथा trying to fix the
 * यंत्र section to keep egcc happy. The यंत्र section no दीर्घer
 * exists, the nibble code is *almost* as fast as the यंत्र code
 * providing it is compiled with egcc.
 *
 * Other clean ups include the follow changes:
 *    CONFIG_SCSI_PPA_HAVE_PEDANTIC => CONFIG_SCSI_IZIP_EPP16
 *    added CONFIG_SCSI_IZIP_SLOW_CTR option
 *                                                      [2.03]
 *
 * Use ppa_रुको() to check क्रम पढ़ोy AND connected status bits
 * Add ppa_रुको() calls to ppa_completion()
 *  by Peter Cherriman <pjc@ecs.soton.ac.uk> and
 *     Tim Waugh <twaugh@redhat.com>
 *							[2.04]
 *
 * Fix kernel panic on scsi समयout, 2000-08-18		[2.05]
 *
 * Aव्योम io_request_lock problems.
 * John Cavan <johncavan@home.com>			[2.06]
 *
 * Busy रुको क्रम connected status bit in ppa_completion()
 *  in order to cope with some hardware that has this bit low
 *  क्रम लघु periods of समय.
 * Add udelay() to ppa_select()
 *  by Peter Cherriman <pjc@ecs.soton.ac.uk> and
 *     Oleg Makarenko <omakarenko@cyberplat.ru>         
 *                                                      [2.07]
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
#घोषणा   PPA_AUTODETECT        0	/* Autodetect mode                */
#घोषणा   PPA_NIBBLE            1	/* work in standard 4 bit mode    */
#घोषणा   PPA_PS2               2	/* PS/2 byte mode         */
#घोषणा   PPA_EPP_8             3	/* EPP mode, 8 bit                */
#घोषणा   PPA_EPP_16            4	/* EPP mode, 16 bit               */
#घोषणा   PPA_EPP_32            5	/* EPP mode, 32 bit               */
#घोषणा   PPA_UNKNOWN           6	/* Just in हाल...                */

अटल अक्षर *PPA_MODE_STRING[] =
अणु
    "Autodetect",
    "SPP",
    "PS/2",
    "EPP 8 bit",
    "EPP 16 bit",
#अगर_घोषित CONFIG_SCSI_IZIP_EPP16
    "EPP 16 bit",
#अन्यथा
    "EPP 32 bit",
#पूर्ण_अगर
    "Unknown"पूर्ण;

/* other options */
#घोषणा PPA_BURST_SIZE	512	/* data burst size */
#घोषणा PPA_SELECT_TMO  5000	/* how दीर्घ to रुको क्रम target ? */
#घोषणा PPA_SPIN_TMO    50000	/* ppa_रुको loop limiter */
#घोषणा PPA_RECON_TMO   500	/* scsi reconnection loop limiter */
#घोषणा PPA_DEBUG	0	/* debugging option */
#घोषणा IN_EPP_MODE(x) (x == PPA_EPP_8 || x == PPA_EPP_16 || x == PPA_EPP_32)

/* args to ppa_connect */
#घोषणा CONNECT_EPP_MAYBE 1
#घोषणा CONNECT_NORMAL  0

#घोषणा r_dtr(x)        (अचिन्हित अक्षर)inb((x))
#घोषणा r_str(x)        (अचिन्हित अक्षर)inb((x)+1)
#घोषणा r_ctr(x)        (अचिन्हित अक्षर)inb((x)+2)
#घोषणा r_epp(x)        (अचिन्हित अक्षर)inb((x)+4)
#घोषणा r_fअगरo(x)       (अचिन्हित अक्षर)inb((x)) /* x must be base_hi */
					/* On PCI is base+0x400 != base_hi */
#घोषणा r_ecr(x)        (अचिन्हित अक्षर)inb((x)+0x2) /* x must be base_hi */

#घोषणा w_dtr(x,y)      outb(y, (x))
#घोषणा w_str(x,y)      outb(y, (x)+1)
#घोषणा w_epp(x,y)      outb(y, (x)+4)
#घोषणा w_fअगरo(x,y)     outb(y, (x))	/* x must be base_hi */
#घोषणा w_ecr(x,y)      outb(y, (x)+0x2)/* x must be base_hi */

#अगर_घोषित CONFIG_SCSI_IZIP_SLOW_CTR
#घोषणा w_ctr(x,y)      outb_p(y, (x)+2)
#अन्यथा
#घोषणा w_ctr(x,y)      outb(y, (x)+2)
#पूर्ण_अगर

अटल पूर्णांक ppa_engine(ppa_काष्ठा *, काष्ठा scsi_cmnd *);

#पूर्ण_अगर				/* _PPA_H */
