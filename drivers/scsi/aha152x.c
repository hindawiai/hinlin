<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* aha152x.c -- Adaptec AHA-152x driver
 * Author: Jथञrgen E. Fischer, fischer@norbit.de
 * Copyright 1993-2004 Jथञrgen E. Fischer
 *
 * $Id: aha152x.c,v 2.7 2004/01/24 11:42:59 fischer Exp $
 *
 * $Log: aha152x.c,v $
 * Revision 2.7  2004/01/24 11:42:59  fischer
 * - gather code that is not used by PCMCIA at the end
 * - move request_region क्रम !PCMCIA हाल to detection
 * - migration to new scsi host api (हटाओ legacy code)
 * - मुक्त host scribble beक्रमe scsi_करोne
 * - fix error handling
 * - one isapnp device added to id_table
 *
 * Revision 2.6  2003/10/30 20:52:47  fischer
 * - पूर्णांकerfaces changes क्रम kernel 2.6
 * - aha152x_probe_one पूर्णांकroduced क्रम pcmcia stub
 * - fixed pnpdev handling
 * - instead of allocation a new one, reuse command क्रम request sense after check condition and reset
 * - fixes race in is_complete
 *
 * Revision 2.5  2002/04/14 11:24:53  fischer
 * - isapnp support
 * - पात fixed
 * - 2.5 support
 *
 * Revision 2.4  2000/12/16 12:53:56  fischer
 * - allow REQUEST SENSE to be queued
 * - handle shared PCI पूर्णांकerrupts
 *
 * Revision 2.3  2000/11/04 16:40:26  fischer
 * - handle data overruns
 * - extend समयout क्रम data phases
 *
 * Revision 2.2  2000/08/08 19:54:53  fischer
 * - minor changes
 *
 * Revision 2.1  2000/05/17 16:23:17  fischer
 * - signature update
 * - fix क्रम data out w/o scatter gather
 *
 * Revision 2.0  1999/12/25 15:07:32  fischer
 * - पूर्णांकerrupt routine completly reworked
 * - basic support क्रम new eh code
 *
 * Revision 1.21  1999/11/10 23:46:36  fischer
 * - शेष to synchronous operation
 * - synchronous negotiation fixed
 * - added समयout to loops
 * - debugging output can be controlled through procfs
 *
 * Revision 1.20  1999/11/07 18:37:31  fischer
 * - synchronous operation works
 * - resid support क्रम sg driver
 *
 * Revision 1.19  1999/11/02 22:39:59  fischer
 * - moved leading comments to README.aha152x
 * - new additional module parameters
 * - updates क्रम 2.3
 * - support क्रम the Tripace TC1550 controller
 * - पूर्णांकerrupt handling changed
 *
 * Revision 1.18  1996/09/07 20:10:40  fischer
 * - fixed can_queue handling (multiple outstanding commands working again)
 *
 * Revision 1.17  1996/08/17 16:05:14  fischer
 * - biosparam improved
 * - पूर्णांकerrupt verअगरication
 * - updated करोcumentation
 * - cleanups
 *
 * Revision 1.16  1996/06/09 00:04:56  root
 * - added configuration symbols क्रम insmod (aha152x/aha152x1)
 *
 * Revision 1.15  1996/04/30 14:52:06  fischer
 * - proc info fixed
 * - support क्रम extended translation क्रम >1GB disks
 *
 * Revision 1.14  1996/01/17  15:11:20  fischer
 * - fixed lockup in MESSAGE IN phase after reconnection
 *
 * Revision 1.13  1996/01/09  02:15:53  fischer
 * - some cleanups
 * - moved request_irq behind controller initialization
 *   (to aव्योम spurious पूर्णांकerrupts)
 *
 * Revision 1.12  1995/12/16  12:26:07  fischer
 * - barrier()s added
 * - configurable RESET delay added
 *
 * Revision 1.11  1995/12/06  21:18:35  fischer
 * - some minor updates
 *
 * Revision 1.10  1995/07/22  19:18:45  fischer
 * - support क्रम 2 controllers
 * - started synchronous data transfers (not working yet)
 *
 * Revision 1.9  1995/03/18  09:20:24  root
 * - patches क्रम PCMCIA and modules
 *
 * Revision 1.8  1995/01/21  22:07:19  root
 * - snarf_region => request_region
 * - aha152x_पूर्णांकr पूर्णांकerface change
 *
 * Revision 1.7  1995/01/02  23:19:36  root
 * - updated COMMAND_SIZE to cmd_len
 * - changed sti() to restore_flags()
 * - fixed some #अगर_घोषित which generated warnings
 *
 * Revision 1.6  1994/11/24  20:35:27  root
 * - problem with odd number of bytes in fअगरo fixed
 *
 * Revision 1.5  1994/10/30  14:39:56  root
 * - पात code fixed
 * - debugging improved
 *
 * Revision 1.4  1994/09/12  11:33:01  root
 * - irqaction to request_irq
 * - पातion updated
 *
 * Revision 1.3  1994/08/04  13:53:05  root
 * - updates क्रम mid-level-driver changes
 * - accept unexpected BUSFREE phase as error condition
 * - parity check now configurable
 *
 * Revision 1.2  1994/07/03  12:56:36  root
 * - cleaned up debugging code
 * - more tweaking on reset delays
 * - updated पात/reset code (pretty untested...)
 *
 * Revision 1.1  1994/05/28  21:18:49  root
 * - update क्रम mid-level पूर्णांकerface change (पात-reset)
 * - delays after resets adjusted क्रम some slow devices
 *
 * Revision 1.0  1994/03/25  12:52:00  root
 * - Fixed "more data than expected" problem
 * - added new BIOS signatures
 *
 * Revision 0.102  1994/01/31  20:44:12  root
 * - minor changes in insw/outsw handling
 *
 * Revision 0.101  1993/12/13  01:16:27  root
 * - fixed STATUS phase (non-GOOD stati were dropped someबार;
 *   fixes problems with CD-ROM sector size detection & media change)
 *
 * Revision 0.100  1993/12/10  16:58:47  root
 * - fix क्रम unsuccessful selections in हाल of non-continuous id assignments
 *   on the scsi bus.
 *
 * Revision 0.99  1993/10/24  16:19:59  root
 * - fixed DATA IN (rare पढ़ो errors gone)
 *
 * Revision 0.98  1993/10/17  12:54:44  root
 * - fixed some recent fixes (shame on me)
 * - moved initialization of scratch area to aha152x_queue
 *
 * Revision 0.97  1993/10/09  18:53:53  root
 * - DATA IN fixed. Rarely left data in the fअगरo.
 *
 * Revision 0.96  1993/10/03  00:53:59  root
 * - minor changes on DATA IN
 *
 * Revision 0.95  1993/09/24  10:36:01  root
 * - change handling of MSGI after reselection
 * - fixed sti/cli
 * - minor changes
 *
 * Revision 0.94  1993/09/18  14:08:22  root
 * - fixed bug in multiple outstanding command code
 * - changed detection
 * - support क्रम kernel command line configuration
 * - reset corrected
 * - changed message handling
 *
 * Revision 0.93  1993/09/15  20:41:19  root
 * - fixed bugs with multiple outstanding commands
 *
 * Revision 0.92  1993/09/13  02:46:33  root
 * - multiple outstanding commands work (no problems with IBM drive)
 *
 * Revision 0.91  1993/09/12  20:51:46  root
 * added multiple outstanding commands
 * (some problem with this $%&? IBM device reमुख्य)
 *
 * Revision 0.9  1993/09/12  11:11:22  root
 * - corrected स्वतः-configuration
 * - changed the स्वतः-configuration (added some '#define's)
 * - added support क्रम dis-/reconnection
 *
 * Revision 0.8  1993/09/06  23:09:39  root
 * - added support क्रम the drive activity light
 * - minor changes
 *
 * Revision 0.7  1993/09/05  14:30:15  root
 * - improved phase detection
 * - now using the new snarf_region code of 0.99pl13
 *
 * Revision 0.6  1993/09/02  11:01:38  root
 * first खुला release; added some signatures and biosparam()
 *
 * Revision 0.5  1993/08/30  10:23:30  root
 * fixed timing problems with my IBM drive
 *
 * Revision 0.4  1993/08/29  14:06:52  root
 * fixed some problems with समयouts due incomplete commands
 *
 * Revision 0.3  1993/08/28  15:55:03  root
 * writing data works too.  mounted and worked on a करोs partition
 *
 * Revision 0.2  1993/08/27  22:42:07  root
 * पढ़ोing data works.  Mounted a msकरोs partition.
 *
 * Revision 0.1  1993/08/25  13:38:30  root
 * first "damn thing doesn't work" version
 *
 * Revision 0.0  1993/08/14  19:54:25  root
 * empty function bodies; detect() works.
 *
 **************************************************************************

 see Documentation/scsi/aha152x.rst क्रम configuration details

 **************************************************************************/

#समावेश <linux/module.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <scsi/scsicam.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश "aha152x.h"

अटल LIST_HEAD(aha152x_host_list);


/* DEFINES */

/* For PCMCIA cards, always use AUTOCONF */
#अगर defined(AHA152X_PCMCIA) || defined(MODULE)
#अगर !defined(AUTOCONF)
#घोषणा AUTOCONF
#पूर्ण_अगर
#पूर्ण_अगर

#अगर !defined(AUTOCONF) && !defined(SETUP0)
#त्रुटि define AUTOCONF or SETUP0
#पूर्ण_अगर

#घोषणा	DO_LOCK(flags)		spin_lock_irqsave(&QLOCK,flags)
#घोषणा	DO_UNLOCK(flags)	spin_unlock_irqrestore(&QLOCK,flags)

#घोषणा LEAD		"(scsi%d:%d:%d) "
#घोषणा INFO_LEAD	KERN_INFO	LEAD
#घोषणा CMDINFO(cmd) \
			(cmd) ? ((cmd)->device->host->host_no) : -1, \
                        (cmd) ? ((cmd)->device->id & 0x0f) : -1, \
			(cmd) ? ((u8)(cmd)->device->lun & 0x07) : -1

अटल अंतरभूत व्योम
CMD_INC_RESID(काष्ठा scsi_cmnd *cmd, पूर्णांक inc)
अणु
	scsi_set_resid(cmd, scsi_get_resid(cmd) + inc);
पूर्ण

#घोषणा DELAY_DEFAULT 1000

#अगर defined(AHA152X_PCMCIA)
#घोषणा IRQ_MIN 0
#घोषणा IRQ_MAX 16
#अन्यथा
#घोषणा IRQ_MIN 9
#अगर defined(__PPC)
#घोषणा IRQ_MAX (nr_irqs-1)
#अन्यथा
#घोषणा IRQ_MAX 12
#पूर्ण_अगर
#पूर्ण_अगर

क्रमागत अणु
	not_issued	= 0x0001,	/* command not yet issued */
	selecting	= 0x0002,	/* target is being selected */
	identअगरied	= 0x0004,	/* IDENTIFY was sent */
	disconnected	= 0x0008,	/* target disconnected */
	completed	= 0x0010,	/* target sent COMMAND COMPLETE */
	पातed		= 0x0020,	/* ABORT was sent */
	resetted	= 0x0040,	/* BUS DEVICE RESET was sent */
	spiordy		= 0x0080,	/* रुकोing क्रम SPIORDY to उठाओ */
	syncneg		= 0x0100,	/* synchronous negotiation in progress */
	पातing	= 0x0200,	/* ABORT is pending */
	resetting	= 0x0400,	/* BUS DEVICE RESET is pending */
	check_condition = 0x0800,	/* requesting sense after CHECK CONDITION */
पूर्ण;

MODULE_AUTHOR("Jथञrgen Fischer");
MODULE_DESCRIPTION(AHA152X_REVID);
MODULE_LICENSE("GPL");

#अगर !defined(AHA152X_PCMCIA)
#अगर defined(MODULE)
अटल पूर्णांक io[] = अणु0, 0पूर्ण;
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(io,"base io address of controller");

अटल पूर्णांक irq[] = अणु0, 0पूर्ण;
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq,"interrupt for controller");

अटल पूर्णांक scsiid[] = अणु7, 7पूर्ण;
module_param_array(scsiid, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(scsiid,"scsi id of controller");

अटल पूर्णांक reconnect[] = अणु1, 1पूर्ण;
module_param_array(reconnect, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(reconnect,"allow targets to disconnect");

अटल पूर्णांक parity[] = अणु1, 1पूर्ण;
module_param_array(parity, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(parity,"use scsi parity");

अटल पूर्णांक sync[] = अणु1, 1पूर्ण;
module_param_array(sync, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(sync,"use synchronous transfers");

अटल पूर्णांक delay[] = अणुDELAY_DEFAULT, DELAY_DEFAULTपूर्ण;
module_param_array(delay, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(delay,"scsi reset delay");

अटल पूर्णांक exttrans[] = अणु0, 0पूर्ण;
module_param_array(exttrans, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(exttrans,"use extended translation");

अटल पूर्णांक aha152x[] = अणु0, 11, 7, 1, 1, 0, DELAY_DEFAULT, 0पूर्ण;
module_param_array(aha152x, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(aha152x, "parameters for first controller");

अटल पूर्णांक aha152x1[] = अणु0, 11, 7, 1, 1, 0, DELAY_DEFAULT, 0पूर्ण;
module_param_array(aha152x1, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(aha152x1, "parameters for second controller");
#पूर्ण_अगर /* MODULE */

#अगर_घोषित __ISAPNP__
अटल काष्ठा isapnp_device_id id_table[] = अणु
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1502), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1505), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1510), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1515), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1520), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x2015), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1522), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x2215), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1530), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x3015), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x1532), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x3215), 0 पूर्ण,
	अणु ISAPNP_ANY_ID, ISAPNP_ANY_ID,	ISAPNP_VENDOR('A', 'D', 'P'), ISAPNP_FUNCTION(0x6360), 0 पूर्ण,
	अणु ISAPNP_DEVICE_SINGLE_END, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(isapnp, id_table);
#पूर्ण_अगर /* ISAPNP */

#पूर्ण_अगर /* !AHA152X_PCMCIA */

अटल काष्ठा scsi_host_ढाँचा aha152x_driver_ढाँचा;

/*
 * पूर्णांकernal states of the host
 *
 */
क्रमागत aha152x_state अणु
	idle=0,
	unknown,
	selकरो,
	seldi,
	selto,
	busमुक्त,
	msgo,
	cmd,
	msgi,
	status,
	datai,
	datao,
	parerr,
	rsti,
	maxstate
पूर्ण;

/*
 * current state inक्रमmation of the host
 *
 */
काष्ठा aha152x_hostdata अणु
	काष्ठा scsi_cmnd *issue_SC;
		/* pending commands to issue */

	काष्ठा scsi_cmnd *current_SC;
		/* current command on the bus */

	काष्ठा scsi_cmnd *disconnected_SC;
		/* commands that disconnected */

	काष्ठा scsi_cmnd *करोne_SC;
		/* command that was completed */

	spinlock_t lock;
		/* host lock */

#अगर defined(AHA152X_STAT)
	पूर्णांक	      total_commands;
	पूर्णांक	      disconnections;
	पूर्णांक	      busमुक्त_without_any_action;
	पूर्णांक	      busमुक्त_without_old_command;
	पूर्णांक	      busमुक्त_without_new_command;
	पूर्णांक	      busमुक्त_without_करोne_command;
	पूर्णांक	      busमुक्त_with_check_condition;
	पूर्णांक	      count[maxstate];
	पूर्णांक	      count_trans[maxstate];
	अचिन्हित दीर्घ समय[maxstate];
#पूर्ण_अगर

	पूर्णांक commands;		/* current number of commands */

	पूर्णांक reconnect;		/* disconnection allowed */
	पूर्णांक parity;		/* parity checking enabled */
	पूर्णांक synchronous;	/* synchronous transferes enabled */
	पूर्णांक delay;		/* reset out delay */
	पूर्णांक ext_trans;		/* extended translation enabled */

	पूर्णांक swपूर्णांक;		/* software-पूर्णांकerrupt was fired during detect() */
	पूर्णांक service;		/* bh needs to be run */
	पूर्णांक in_पूर्णांकr;		/* bh is running */

	/* current state,
	   previous state,
	   last state dअगरferent from current state */
	क्रमागत aha152x_state state, prevstate, laststate;

	पूर्णांक target;
		/* reconnecting target */

	अचिन्हित अक्षर syncrate[8];
		/* current synchronous transfer agreements */

	अचिन्हित अक्षर syncneg[8];
		/* 0: no negotiation;
		 * 1: negotiation in progress;
		 * 2: negotiation completed
		 */

	पूर्णांक cmd_i;
		/* number of sent bytes of current command */

	पूर्णांक msgi_len;
		/* number of received message bytes */
	अचिन्हित अक्षर msgi[256];
		/* received message bytes */

	पूर्णांक msgo_i, msgo_len;
		/* number of sent bytes and length of current messages */
	अचिन्हित अक्षर msgo[256];
		/* pending messages */

	पूर्णांक data_len;
		/* number of sent/received bytes in dataphase */

	अचिन्हित दीर्घ io_port0;
	अचिन्हित दीर्घ io_port1;

#अगर_घोषित __ISAPNP__
	काष्ठा pnp_dev *pnpdev;
#पूर्ण_अगर
	काष्ठा list_head host_list;
पूर्ण;


/*
 * host specअगरic command extension
 *
 */
काष्ठा aha152x_scdata अणु
	काष्ठा scsi_cmnd *next;	/* next sc in queue */
	काष्ठा completion *करोne;/* semaphore to block on */
	काष्ठा scsi_eh_save ses;
पूर्ण;

/* access macros क्रम hostdata */

#घोषणा HOSTDATA(shpnt)		((काष्ठा aha152x_hostdata *) &shpnt->hostdata)

#घोषणा HOSTNO			((shpnt)->host_no)

#घोषणा CURRENT_SC		(HOSTDATA(shpnt)->current_SC)
#घोषणा DONE_SC			(HOSTDATA(shpnt)->करोne_SC)
#घोषणा ISSUE_SC		(HOSTDATA(shpnt)->issue_SC)
#घोषणा DISCONNECTED_SC		(HOSTDATA(shpnt)->disconnected_SC)
#घोषणा QLOCK			(HOSTDATA(shpnt)->lock)
#घोषणा QLOCKER			(HOSTDATA(shpnt)->locker)
#घोषणा QLOCKERL		(HOSTDATA(shpnt)->lockerl)

#घोषणा STATE			(HOSTDATA(shpnt)->state)
#घोषणा PREVSTATE		(HOSTDATA(shpnt)->prevstate)
#घोषणा LASTSTATE		(HOSTDATA(shpnt)->laststate)

#घोषणा RECONN_TARGET		(HOSTDATA(shpnt)->target)

#घोषणा CMD_I			(HOSTDATA(shpnt)->cmd_i)

#घोषणा MSGO(i)			(HOSTDATA(shpnt)->msgo[i])
#घोषणा MSGO_I			(HOSTDATA(shpnt)->msgo_i)
#घोषणा MSGOLEN			(HOSTDATA(shpnt)->msgo_len)
#घोषणा ADDMSGO(x)		(MSGOLEN<256 ? (व्योम)(MSGO(MSGOLEN++)=x) : aha152x_error(shpnt,"MSGO overflow"))

#घोषणा MSGI(i)			(HOSTDATA(shpnt)->msgi[i])
#घोषणा MSGILEN			(HOSTDATA(shpnt)->msgi_len)
#घोषणा ADDMSGI(x)		(MSGILEN<256 ? (व्योम)(MSGI(MSGILEN++)=x) : aha152x_error(shpnt,"MSGI overflow"))

#घोषणा DATA_LEN		(HOSTDATA(shpnt)->data_len)

#घोषणा SYNCRATE		(HOSTDATA(shpnt)->syncrate[CURRENT_SC->device->id])
#घोषणा SYNCNEG			(HOSTDATA(shpnt)->syncneg[CURRENT_SC->device->id])

#घोषणा DELAY			(HOSTDATA(shpnt)->delay)
#घोषणा EXT_TRANS		(HOSTDATA(shpnt)->ext_trans)
#घोषणा TC1550			(HOSTDATA(shpnt)->tc1550)
#घोषणा RECONNECT		(HOSTDATA(shpnt)->reconnect)
#घोषणा PARITY			(HOSTDATA(shpnt)->parity)
#घोषणा SYNCHRONOUS		(HOSTDATA(shpnt)->synchronous)

#घोषणा HOSTIOPORT0		(HOSTDATA(shpnt)->io_port0)
#घोषणा HOSTIOPORT1		(HOSTDATA(shpnt)->io_port1)

#घोषणा SCDATA(SCpnt)		((काष्ठा aha152x_scdata *) (SCpnt)->host_scribble)
#घोषणा SCNEXT(SCpnt)		SCDATA(SCpnt)->next
#घोषणा SCSEM(SCpnt)		SCDATA(SCpnt)->करोne

#घोषणा SG_ADDRESS(buffer)	((अक्षर *) sg_virt((buffer)))

/* state handling */
अटल व्योम seldi_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम selकरो_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम selto_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम busमुक्त_run(काष्ठा Scsi_Host *shpnt);

अटल व्योम msgo_init(काष्ठा Scsi_Host *shpnt);
अटल व्योम msgo_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम msgo_end(काष्ठा Scsi_Host *shpnt);

अटल व्योम cmd_init(काष्ठा Scsi_Host *shpnt);
अटल व्योम cmd_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम cmd_end(काष्ठा Scsi_Host *shpnt);

अटल व्योम datai_init(काष्ठा Scsi_Host *shpnt);
अटल व्योम datai_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम datai_end(काष्ठा Scsi_Host *shpnt);

अटल व्योम datao_init(काष्ठा Scsi_Host *shpnt);
अटल व्योम datao_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम datao_end(काष्ठा Scsi_Host *shpnt);

अटल व्योम status_run(काष्ठा Scsi_Host *shpnt);

अटल व्योम msgi_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम msgi_end(काष्ठा Scsi_Host *shpnt);

अटल व्योम parerr_run(काष्ठा Scsi_Host *shpnt);
अटल व्योम rsti_run(काष्ठा Scsi_Host *shpnt);

अटल व्योम is_complete(काष्ठा Scsi_Host *shpnt);

/*
 * driver states
 *
 */
अटल काष्ठा अणु
	अक्षर		*name;
	व्योम		(*init)(काष्ठा Scsi_Host *);
	व्योम		(*run)(काष्ठा Scsi_Host *);
	व्योम		(*end)(काष्ठा Scsi_Host *);
	पूर्णांक		spio;
पूर्ण states[] = अणु
	अणु "idle",	शून्य,		शून्य,		शून्य,		0पूर्ण,
	अणु "unknown",	शून्य,		शून्य,		शून्य,		0पूर्ण,
	अणु "seldo",	शून्य,		selकरो_run,	शून्य,		0पूर्ण,
	अणु "seldi",	शून्य,		seldi_run,	शून्य,		0पूर्ण,
	अणु "selto",	शून्य,		selto_run,	शून्य,		0पूर्ण,
	अणु "busfree",	शून्य,		busमुक्त_run,	शून्य,		0पूर्ण,
	अणु "msgo",	msgo_init,	msgo_run,	msgo_end,	1पूर्ण,
	अणु "cmd",	cmd_init,	cmd_run,	cmd_end,	1पूर्ण,
	अणु "msgi",	शून्य,		msgi_run,	msgi_end,	1पूर्ण,
	अणु "status",	शून्य,		status_run,	शून्य,		1पूर्ण,
	अणु "datai",	datai_init,	datai_run,	datai_end,	0पूर्ण,
	अणु "datao",	datao_init,	datao_run,	datao_end,	0पूर्ण,
	अणु "parerr",	शून्य,		parerr_run,	शून्य,		0पूर्ण,
	अणु "rsti",	शून्य,		rsti_run,	शून्य,		0पूर्ण,
पूर्ण;

/* setup & पूर्णांकerrupt */
अटल irqवापस_t पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम reset_ports(काष्ठा Scsi_Host *shpnt);
अटल व्योम aha152x_error(काष्ठा Scsi_Host *shpnt, अक्षर *msg);
अटल व्योम करोne(काष्ठा Scsi_Host *shpnt, पूर्णांक error);

/* diagnostics */
अटल व्योम show_command(काष्ठा scsi_cmnd * ptr);
अटल व्योम show_queues(काष्ठा Scsi_Host *shpnt);
अटल व्योम disp_enपूर्णांकr(काष्ठा Scsi_Host *shpnt);


/*
 *  queue services:
 *
 */
अटल अंतरभूत व्योम append_SC(काष्ठा scsi_cmnd **SC, काष्ठा scsi_cmnd *new_SC)
अणु
	काष्ठा scsi_cmnd *end;

	SCNEXT(new_SC) = शून्य;
	अगर (!*SC)
		*SC = new_SC;
	अन्यथा अणु
		क्रम (end = *SC; SCNEXT(end); end = SCNEXT(end))
			;
		SCNEXT(end) = new_SC;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा scsi_cmnd *हटाओ_first_SC(काष्ठा scsi_cmnd ** SC)
अणु
	काष्ठा scsi_cmnd *ptr;

	ptr = *SC;
	अगर (ptr) अणु
		*SC = SCNEXT(*SC);
		SCNEXT(ptr)=शून्य;
	पूर्ण
	वापस ptr;
पूर्ण

अटल अंतरभूत काष्ठा scsi_cmnd *हटाओ_lun_SC(काष्ठा scsi_cmnd ** SC,
					      पूर्णांक target, पूर्णांक lun)
अणु
	काष्ठा scsi_cmnd *ptr, *prev;

	क्रम (ptr = *SC, prev = शून्य;
	     ptr && ((ptr->device->id != target) || (ptr->device->lun != lun));
	     prev = ptr, ptr = SCNEXT(ptr))
	     ;

	अगर (ptr) अणु
		अगर (prev)
			SCNEXT(prev) = SCNEXT(ptr);
		अन्यथा
			*SC = SCNEXT(ptr);

		SCNEXT(ptr)=शून्य;
	पूर्ण

	वापस ptr;
पूर्ण

अटल अंतरभूत काष्ठा scsi_cmnd *हटाओ_SC(काष्ठा scsi_cmnd **SC,
					  काष्ठा scsi_cmnd *SCp)
अणु
	काष्ठा scsi_cmnd *ptr, *prev;

	क्रम (ptr = *SC, prev = शून्य;
	     ptr && SCp!=ptr;
	     prev = ptr, ptr = SCNEXT(ptr))
	     ;

	अगर (ptr) अणु
		अगर (prev)
			SCNEXT(prev) = SCNEXT(ptr);
		अन्यथा
			*SC = SCNEXT(ptr);

		SCNEXT(ptr)=शून्य;
	पूर्ण

	वापस ptr;
पूर्ण

अटल irqवापस_t swपूर्णांकr(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *shpnt = dev_id;

	HOSTDATA(shpnt)->swपूर्णांक++;

	SETPORT(DMACNTRL0, INTEN);
	वापस IRQ_HANDLED;
पूर्ण

काष्ठा Scsi_Host *aha152x_probe_one(काष्ठा aha152x_setup *setup)
अणु
	काष्ठा Scsi_Host *shpnt;

	shpnt = scsi_host_alloc(&aha152x_driver_ढाँचा, माप(काष्ठा aha152x_hostdata));
	अगर (!shpnt) अणु
		prपूर्णांकk(KERN_ERR "aha152x: scsi_host_alloc failed\n");
		वापस शून्य;
	पूर्ण

	स_रखो(HOSTDATA(shpnt), 0, माप *HOSTDATA(shpnt));
	INIT_LIST_HEAD(&HOSTDATA(shpnt)->host_list);

	/* need to have host रेजिस्टरed beक्रमe triggering any पूर्णांकerrupt */
	list_add_tail(&HOSTDATA(shpnt)->host_list, &aha152x_host_list);

	shpnt->io_port   = setup->io_port;
	shpnt->n_io_port = IO_RANGE;
	shpnt->irq       = setup->irq;

	अगर (!setup->tc1550) अणु
		HOSTIOPORT0 = setup->io_port;
		HOSTIOPORT1 = setup->io_port;
	पूर्ण अन्यथा अणु
		HOSTIOPORT0 = setup->io_port+0x10;
		HOSTIOPORT1 = setup->io_port-0x10;
	पूर्ण

	spin_lock_init(&QLOCK);
	RECONNECT   = setup->reconnect;
	SYNCHRONOUS = setup->synchronous;
	PARITY      = setup->parity;
	DELAY       = setup->delay;
	EXT_TRANS   = setup->ext_trans;

	SETPORT(SCSIID, setup->scsiid << 4);
	shpnt->this_id = setup->scsiid;

	अगर (setup->reconnect)
		shpnt->can_queue = AHA152X_MAXQUEUE;

	/* RESET OUT */
	prपूर्णांकk("aha152x: resetting bus...\n");
	SETPORT(SCSISEQ, SCSIRSTO);
	mdelay(256);
	SETPORT(SCSISEQ, 0);
	mdelay(DELAY);

	reset_ports(shpnt);

	prपूर्णांकk(KERN_INFO
	       "aha152x%d%s: "
	       "vital data: rev=%x, "
	       "io=0x%03lx (0x%03lx/0x%03lx), "
	       "irq=%d, "
	       "scsiid=%d, "
	       "reconnect=%s, "
	       "parity=%s, "
	       "synchronous=%s, "
	       "delay=%d, "
	       "extended translation=%s\n",
	       shpnt->host_no, setup->tc1550 ? " (tc1550 mode)" : "",
	       GETPORT(REV) & 0x7,
	       shpnt->io_port, HOSTIOPORT0, HOSTIOPORT1,
	       shpnt->irq,
	       shpnt->this_id,
	       RECONNECT ? "enabled" : "disabled",
	       PARITY ? "enabled" : "disabled",
	       SYNCHRONOUS ? "enabled" : "disabled",
	       DELAY,
	       EXT_TRANS ? "enabled" : "disabled");

	/* not expecting any पूर्णांकerrupts */
	SETPORT(SIMODE0, 0);
	SETPORT(SIMODE1, 0);

	अगर (request_irq(shpnt->irq, swपूर्णांकr, IRQF_SHARED, "aha152x", shpnt)) अणु
		prपूर्णांकk(KERN_ERR "aha152x%d: irq %d busy.\n", shpnt->host_no, shpnt->irq);
		जाओ out_host_put;
	पूर्ण

	HOSTDATA(shpnt)->swपूर्णांक = 0;

	prपूर्णांकk(KERN_INFO "aha152x%d: trying software interrupt, ", shpnt->host_no);

	mb();
	SETPORT(DMACNTRL0, SWINT|INTEN);
	mdelay(1000);
	मुक्त_irq(shpnt->irq, shpnt);

	अगर (!HOSTDATA(shpnt)->swपूर्णांक) अणु
		अगर (TESTHI(DMASTAT, INTSTAT)) अणु
			prपूर्णांकk("lost.\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk("failed.\n");
		पूर्ण

		SETPORT(DMACNTRL0, INTEN);

		prपूर्णांकk(KERN_ERR "aha152x%d: irq %d possibly wrong.  "
				"Please verify.\n", shpnt->host_no, shpnt->irq);
		जाओ out_host_put;
	पूर्ण
	prपूर्णांकk("ok.\n");


	/* clear पूर्णांकerrupts */
	SETPORT(SSTAT0, 0x7f);
	SETPORT(SSTAT1, 0xef);

	अगर (request_irq(shpnt->irq, पूर्णांकr, IRQF_SHARED, "aha152x", shpnt)) अणु
		prपूर्णांकk(KERN_ERR "aha152x%d: failed to reassign irq %d.\n", shpnt->host_no, shpnt->irq);
		जाओ out_host_put;
	पूर्ण

	अगर( scsi_add_host(shpnt, शून्य) ) अणु
		मुक्त_irq(shpnt->irq, shpnt);
		prपूर्णांकk(KERN_ERR "aha152x%d: failed to add host.\n", shpnt->host_no);
		जाओ out_host_put;
	पूर्ण

	scsi_scan_host(shpnt);

	वापस shpnt;

out_host_put:
	list_del(&HOSTDATA(shpnt)->host_list);
	scsi_host_put(shpnt);

	वापस शून्य;
पूर्ण

व्योम aha152x_release(काष्ठा Scsi_Host *shpnt)
अणु
	अगर (!shpnt)
		वापस;

	scsi_हटाओ_host(shpnt);
	अगर (shpnt->irq)
		मुक्त_irq(shpnt->irq, shpnt);

#अगर !defined(AHA152X_PCMCIA)
	अगर (shpnt->io_port)
		release_region(shpnt->io_port, IO_RANGE);
#पूर्ण_अगर

#अगर_घोषित __ISAPNP__
	अगर (HOSTDATA(shpnt)->pnpdev)
		pnp_device_detach(HOSTDATA(shpnt)->pnpdev);
#पूर्ण_अगर

	list_del(&HOSTDATA(shpnt)->host_list);
	scsi_host_put(shpnt);
पूर्ण


/*
 * setup controller to generate पूर्णांकerrupts depending
 * on current state (lock has to be acquired)
 *
 */
अटल पूर्णांक setup_expected_पूर्णांकerrupts(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(CURRENT_SC) अणु
		CURRENT_SC->SCp.phase |= 1 << 16;

		अगर(CURRENT_SC->SCp.phase & selecting) अणु
			SETPORT(SSTAT1, SELTO);
			SETPORT(SIMODE0, ENSELDO | (DISCONNECTED_SC ? ENSELDI : 0));
			SETPORT(SIMODE1, ENSELTIMO);
		पूर्ण अन्यथा अणु
			SETPORT(SIMODE0, (CURRENT_SC->SCp.phase & spiordy) ? ENSPIORDY : 0);
			SETPORT(SIMODE1, ENPHASEMIS | ENSCSIRST | ENSCSIPERR | ENBUSFREE);
		पूर्ण
	पूर्ण अन्यथा अगर(STATE==seldi) अणु
		SETPORT(SIMODE0, 0);
		SETPORT(SIMODE1, ENPHASEMIS | ENSCSIRST | ENSCSIPERR | ENBUSFREE);
	पूर्ण अन्यथा अणु
		SETPORT(SIMODE0, DISCONNECTED_SC ? ENSELDI : 0);
		SETPORT(SIMODE1, ENSCSIRST | ( (ISSUE_SC||DONE_SC) ? ENBUSFREE : 0));
	पूर्ण

	अगर(!HOSTDATA(shpnt)->in_पूर्णांकr)
		SETBITS(DMACNTRL0, INTEN);

	वापस TESTHI(DMASTAT, INTSTAT);
पूर्ण


/*
 *  Queue a command and setup पूर्णांकerrupts क्रम a मुक्त bus.
 */
अटल पूर्णांक aha152x_पूर्णांकernal_queue(काष्ठा scsi_cmnd *SCpnt,
				  काष्ठा completion *complete,
				  पूर्णांक phase, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *shpnt = SCpnt->device->host;
	अचिन्हित दीर्घ flags;

	SCpnt->scsi_करोne	= करोne;
	SCpnt->SCp.phase	= not_issued | phase;
	SCpnt->SCp.Status	= 0x1; /* Ilegal status by SCSI standard */
	SCpnt->SCp.Message	= 0;
	SCpnt->SCp.have_data_in	= 0;
	SCpnt->SCp.sent_command	= 0;

	अगर(SCpnt->SCp.phase & (resetting|check_condition)) अणु
		अगर (!SCpnt->host_scribble || SCSEM(SCpnt) || SCNEXT(SCpnt)) अणु
			scmd_prपूर्णांकk(KERN_ERR, SCpnt, "cannot reuse command\n");
			वापस FAILED;
		पूर्ण
	पूर्ण अन्यथा अणु
		SCpnt->host_scribble = kदो_स्मृति(माप(काष्ठा aha152x_scdata), GFP_ATOMIC);
		अगर(!SCpnt->host_scribble) अणु
			scmd_prपूर्णांकk(KERN_ERR, SCpnt, "allocation failed\n");
			वापस FAILED;
		पूर्ण
	पूर्ण

	SCNEXT(SCpnt)		= शून्य;
	SCSEM(SCpnt)		= complete;

	/* setup scratch area
	   SCp.ptr              : buffer poपूर्णांकer
	   SCp.this_residual    : buffer length
	   SCp.buffer           : next buffer
	   SCp.phase            : current state of the command */

	अगर ((phase & resetting) || !scsi_sglist(SCpnt)) अणु
		SCpnt->SCp.ptr           = शून्य;
		SCpnt->SCp.this_residual = 0;
		scsi_set_resid(SCpnt, 0);
		SCpnt->SCp.buffer           = शून्य;
	पूर्ण अन्यथा अणु
		scsi_set_resid(SCpnt, scsi_bufflen(SCpnt));
		SCpnt->SCp.buffer           = scsi_sglist(SCpnt);
		SCpnt->SCp.ptr              = SG_ADDRESS(SCpnt->SCp.buffer);
		SCpnt->SCp.this_residual    = SCpnt->SCp.buffer->length;
	पूर्ण

	DO_LOCK(flags);

#अगर defined(AHA152X_STAT)
	HOSTDATA(shpnt)->total_commands++;
#पूर्ण_अगर

	/* Turn led on, when this is the first command. */
	HOSTDATA(shpnt)->commands++;
	अगर (HOSTDATA(shpnt)->commands==1)
		SETPORT(PORTA, 1);

	append_SC(&ISSUE_SC, SCpnt);

	अगर(!HOSTDATA(shpnt)->in_पूर्णांकr)
		setup_expected_पूर्णांकerrupts(shpnt);

	DO_UNLOCK(flags);

	वापस 0;
पूर्ण

/*
 *  queue a command
 *
 */
अटल पूर्णांक aha152x_queue_lck(काष्ठा scsi_cmnd *SCpnt,
			     व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	वापस aha152x_पूर्णांकernal_queue(SCpnt, शून्य, 0, करोne);
पूर्ण

अटल DEF_SCSI_QCMD(aha152x_queue)


/*
 *
 */
अटल व्योम reset_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	अगर(SCSEM(SCpnt)) अणु
		complete(SCSEM(SCpnt));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "aha152x: reset_done w/o completion\n");
	पूर्ण
पूर्ण

/*
 *  Abort a command
 *
 */
अटल पूर्णांक aha152x_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा Scsi_Host *shpnt = SCpnt->device->host;
	काष्ठा scsi_cmnd *ptr;
	अचिन्हित दीर्घ flags;

	DO_LOCK(flags);

	ptr=हटाओ_SC(&ISSUE_SC, SCpnt);

	अगर(ptr) अणु
		HOSTDATA(shpnt)->commands--;
		अगर (!HOSTDATA(shpnt)->commands)
			SETPORT(PORTA, 0);
		DO_UNLOCK(flags);

		kमुक्त(SCpnt->host_scribble);
		SCpnt->host_scribble=शून्य;

		वापस SUCCESS;
	पूर्ण

	DO_UNLOCK(flags);

	/*
	 * FIXME:
	 * क्रम current command: queue ABORT क्रम message out and उठाओ ATN
	 * क्रम disconnected command: pseuकरो SC with ABORT message or ABORT on reselection?
	 *
	 */

	scmd_prपूर्णांकk(KERN_ERR, SCpnt,
		    "cannot abort running or disconnected command\n");

	वापस FAILED;
पूर्ण

/*
 * Reset a device
 *
 */
अटल पूर्णांक aha152x_device_reset(काष्ठा scsi_cmnd * SCpnt)
अणु
	काष्ठा Scsi_Host *shpnt = SCpnt->device->host;
	DECLARE_COMPLETION(करोne);
	पूर्णांक ret, issued, disconnected;
	अचिन्हित अक्षर old_cmd_len = SCpnt->cmd_len;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयleft;

	अगर(CURRENT_SC==SCpnt) अणु
		scmd_prपूर्णांकk(KERN_ERR, SCpnt, "cannot reset current device\n");
		वापस FAILED;
	पूर्ण

	DO_LOCK(flags);
	issued       = हटाओ_SC(&ISSUE_SC, SCpnt) == शून्य;
	disconnected = issued && हटाओ_SC(&DISCONNECTED_SC, SCpnt);
	DO_UNLOCK(flags);

	SCpnt->cmd_len         = 0;

	aha152x_पूर्णांकernal_queue(SCpnt, &करोne, resetting, reset_करोne);

	समयleft = रुको_क्रम_completion_समयout(&करोne, 100*HZ);
	अगर (!समयleft) अणु
		/* हटाओ command from issue queue */
		DO_LOCK(flags);
		हटाओ_SC(&ISSUE_SC, SCpnt);
		DO_UNLOCK(flags);
	पूर्ण

	SCpnt->cmd_len         = old_cmd_len;

	DO_LOCK(flags);

	अगर(SCpnt->SCp.phase & resetted) अणु
		HOSTDATA(shpnt)->commands--;
		अगर (!HOSTDATA(shpnt)->commands)
			SETPORT(PORTA, 0);
		kमुक्त(SCpnt->host_scribble);
		SCpnt->host_scribble=शून्य;

		ret = SUCCESS;
	पूर्ण अन्यथा अणु
		/* requeue */
		अगर(!issued) अणु
			append_SC(&ISSUE_SC, SCpnt);
		पूर्ण अन्यथा अगर(disconnected) अणु
			append_SC(&DISCONNECTED_SC, SCpnt);
		पूर्ण

		ret = FAILED;
	पूर्ण

	DO_UNLOCK(flags);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_hard_reset_SCs(काष्ठा Scsi_Host *shpnt,
				काष्ठा scsi_cmnd **SCs)
अणु
	काष्ठा scsi_cmnd *ptr;

	ptr=*SCs;
	जबतक(ptr) अणु
		काष्ठा scsi_cmnd *next;

		अगर(SCDATA(ptr)) अणु
			next = SCNEXT(ptr);
		पूर्ण अन्यथा अणु
			scmd_prपूर्णांकk(KERN_DEBUG, ptr,
				    "queue corrupted at %p\n", ptr);
			next = शून्य;
		पूर्ण

		अगर (!ptr->device->soft_reset) अणु
			हटाओ_SC(SCs, ptr);
			HOSTDATA(shpnt)->commands--;
			kमुक्त(ptr->host_scribble);
			ptr->host_scribble=शून्य;
		पूर्ण

		ptr = next;
	पूर्ण
पूर्ण

/*
 * Reset the bus
 *
 * AIC-6260 has a hard reset (MRST संकेत), but apparently
 * one cannot trigger it via software. So live with
 * a soft reset; no-one seemed to have cared.
 */
अटल पूर्णांक aha152x_bus_reset_host(काष्ठा Scsi_Host *shpnt)
अणु
	अचिन्हित दीर्घ flags;

	DO_LOCK(flags);

	मुक्त_hard_reset_SCs(shpnt, &ISSUE_SC);
	मुक्त_hard_reset_SCs(shpnt, &DISCONNECTED_SC);

	SETPORT(SCSISEQ, SCSIRSTO);
	mdelay(256);
	SETPORT(SCSISEQ, 0);
	mdelay(DELAY);

	setup_expected_पूर्णांकerrupts(shpnt);
	अगर(HOSTDATA(shpnt)->commands==0)
		SETPORT(PORTA, 0);

	DO_UNLOCK(flags);

	वापस SUCCESS;
पूर्ण

/*
 * Reset the bus
 *
 */
अटल पूर्णांक aha152x_bus_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	वापस aha152x_bus_reset_host(SCpnt->device->host);
पूर्ण

/*
 *  Restore शेष values to the AIC-6260 रेजिस्टरs and reset the fअगरos
 *
 */
अटल व्योम reset_ports(काष्ठा Scsi_Host *shpnt)
अणु
	अचिन्हित दीर्घ flags;

	/* disable पूर्णांकerrupts */
	SETPORT(DMACNTRL0, RSTFIFO);

	SETPORT(SCSISEQ, 0);

	SETPORT(SXFRCTL1, 0);
	SETPORT(SCSISIG, 0);
	SETRATE(0);

	/* clear all पूर्णांकerrupt conditions */
	SETPORT(SSTAT0, 0x7f);
	SETPORT(SSTAT1, 0xef);

	SETPORT(SSTAT4, SYNCERR | FWERR | FRERR);

	SETPORT(DMACNTRL0, 0);
	SETPORT(DMACNTRL1, 0);

	SETPORT(BRSTCNTRL, 0xf1);

	/* clear SCSI fअगरos and transfer count */
	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	DO_LOCK(flags);
	setup_expected_पूर्णांकerrupts(shpnt);
	DO_UNLOCK(flags);
पूर्ण

/*
 * Reset the host (bus and controller)
 *
 */
पूर्णांक aha152x_host_reset_host(काष्ठा Scsi_Host *shpnt)
अणु
	aha152x_bus_reset_host(shpnt);
	reset_ports(shpnt);

	वापस SUCCESS;
पूर्ण

/*
 * Return the "logical geometry"
 *
 */
अटल पूर्णांक aha152x_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		sector_t capacity, पूर्णांक *info_array)
अणु
	काष्ठा Scsi_Host *shpnt = sdev->host;

	/* try शेष translation */
	info_array[0] = 64;
	info_array[1] = 32;
	info_array[2] = (अचिन्हित दीर्घ)capacity / (64 * 32);

	/* क्रम disks >1GB करो some guessing */
	अगर (info_array[2] >= 1024) अणु
		पूर्णांक info[3];

		/* try to figure out the geometry from the partition table */
		अगर (scsicam_bios_param(bdev, capacity, info) < 0 ||
		    !((info[0] == 64 && info[1] == 32) || (info[0] == 255 && info[1] == 63))) अणु
			अगर (EXT_TRANS) अणु
				prपूर्णांकk(KERN_NOTICE
				       "aha152x: unable to verify geometry for disk with >1GB.\n"
				       "         using extended translation.\n");
				info_array[0] = 255;
				info_array[1] = 63;
				info_array[2] = (अचिन्हित दीर्घ)capacity / (255 * 63);
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_NOTICE
				       "aha152x: unable to verify geometry for disk with >1GB.\n"
				       "         Using default translation. Please verify yourself.\n"
				       "         Perhaps you need to enable extended translation in the driver.\n"
				       "         See Documentation/scsi/aha152x.rst for details.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			info_array[0] = info[0];
			info_array[1] = info[1];
			info_array[2] = info[2];

			अगर (info[0] == 255 && !EXT_TRANS) अणु
				prपूर्णांकk(KERN_NOTICE
				       "aha152x: current partition table is using extended translation.\n"
				       "         using it also, although it's not explicitly enabled.\n");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Internal करोne function
 *
 */
अटल व्योम करोne(काष्ठा Scsi_Host *shpnt, पूर्णांक error)
अणु
	अगर (CURRENT_SC) अणु
		अगर(DONE_SC)
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
				    "there's already a completed command %p "
				    "- will cause abort\n", DONE_SC);

		DONE_SC = CURRENT_SC;
		CURRENT_SC = शून्य;
		DONE_SC->result = error;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "aha152x: done() called outside of command\n");
पूर्ण

अटल काष्ठा work_काष्ठा aha152x_tq;

/*
 * Run service completions on the card with पूर्णांकerrupts enabled.
 *
 */
अटल व्योम run(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aha152x_hostdata *hd;

	list_क्रम_each_entry(hd, &aha152x_host_list, host_list) अणु
		काष्ठा Scsi_Host *shost = container_of((व्योम *)hd, काष्ठा Scsi_Host, hostdata);

		is_complete(shost);
	पूर्ण
पूर्ण

/*
 * Interrupt handler
 *
 */
अटल irqवापस_t पूर्णांकr(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *shpnt = dev_id;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर rev, dmacntrl0;

	/*
	 * Read a couple of रेजिस्टरs that are known to not be all 1's. If
	 * we पढ़ो all 1's (-1), that means that either:
	 *
	 * a. The host adapter chip has gone bad, and we cannot control it,
	 *	OR
	 * b. The host adapter is a PCMCIA card that has been ejected
	 *
	 * In either हाल, we cannot करो anything with the host adapter at
	 * this poपूर्णांक in समय. So just ignore the पूर्णांकerrupt and वापस.
	 * In the latter हाल, the पूर्णांकerrupt might actually be meant क्रम
	 * someone अन्यथा sharing this IRQ, and that driver will handle it.
	 */
	rev = GETPORT(REV);
	dmacntrl0 = GETPORT(DMACNTRL0);
	अगर ((rev == 0xFF) && (dmacntrl0 == 0xFF))
		वापस IRQ_NONE;

	अगर( TESTLO(DMASTAT, INTSTAT) )
		वापस IRQ_NONE;

	/* no more पूर्णांकerrupts from the controller, जबतक we're busy.
	   INTEN is restored by the BH handler */
	CLRBITS(DMACNTRL0, INTEN);

	DO_LOCK(flags);
	अगर( HOSTDATA(shpnt)->service==0 ) अणु
		HOSTDATA(shpnt)->service=1;

		/* Poke the BH handler */
		INIT_WORK(&aha152x_tq, run);
		schedule_work(&aha152x_tq);
	पूर्ण
	DO_UNLOCK(flags);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * busमुक्त phase
 * - handle completition/disconnection/error of current command
 * - start selection क्रम next command (अगर any)
 */
अटल व्योम busमुक्त_run(काष्ठा Scsi_Host *shpnt)
अणु
	अचिन्हित दीर्घ flags;
#अगर defined(AHA152X_STAT)
	पूर्णांक action=0;
#पूर्ण_अगर

	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	SETPORT(SSTAT1, CLRBUSFREE);

	अगर(CURRENT_SC) अणु
#अगर defined(AHA152X_STAT)
		action++;
#पूर्ण_अगर
		CURRENT_SC->SCp.phase &= ~syncneg;

		अगर(CURRENT_SC->SCp.phase & completed) अणु
			/* target sent COMMAND COMPLETE */
			करोne(shpnt, (CURRENT_SC->SCp.Status & 0xff) | ((CURRENT_SC->SCp.Message & 0xff) << 8) | (DID_OK << 16));

		पूर्ण अन्यथा अगर(CURRENT_SC->SCp.phase & पातed) अणु
			करोne(shpnt, (CURRENT_SC->SCp.Status & 0xff) | ((CURRENT_SC->SCp.Message & 0xff) << 8) | (DID_ABORT << 16));

		पूर्ण अन्यथा अगर(CURRENT_SC->SCp.phase & resetted) अणु
			करोne(shpnt, (CURRENT_SC->SCp.Status & 0xff) | ((CURRENT_SC->SCp.Message & 0xff) << 8) | (DID_RESET << 16));

		पूर्ण अन्यथा अगर(CURRENT_SC->SCp.phase & disconnected) अणु
			/* target sent DISCONNECT */
#अगर defined(AHA152X_STAT)
			HOSTDATA(shpnt)->disconnections++;
#पूर्ण_अगर
			append_SC(&DISCONNECTED_SC, CURRENT_SC);
			CURRENT_SC->SCp.phase |= 1 << 16;
			CURRENT_SC = शून्य;

		पूर्ण अन्यथा अणु
			करोne(shpnt, DID_ERROR << 16);
		पूर्ण
#अगर defined(AHA152X_STAT)
	पूर्ण अन्यथा अणु
		HOSTDATA(shpnt)->busमुक्त_without_old_command++;
#पूर्ण_अगर
	पूर्ण

	DO_LOCK(flags);

	अगर(DONE_SC) अणु
#अगर defined(AHA152X_STAT)
		action++;
#पूर्ण_अगर

		अगर(DONE_SC->SCp.phase & check_condition) अणु
			काष्ठा scsi_cmnd *cmd = HOSTDATA(shpnt)->करोne_SC;
			काष्ठा aha152x_scdata *sc = SCDATA(cmd);

			scsi_eh_restore_cmnd(cmd, &sc->ses);

			cmd->SCp.Status = SAM_STAT_CHECK_CONDITION;

			HOSTDATA(shpnt)->commands--;
			अगर (!HOSTDATA(shpnt)->commands)
				SETPORT(PORTA, 0);	/* turn led off */
		पूर्ण अन्यथा अगर(DONE_SC->SCp.Status==SAM_STAT_CHECK_CONDITION) अणु
#अगर defined(AHA152X_STAT)
			HOSTDATA(shpnt)->busमुक्त_with_check_condition++;
#पूर्ण_अगर

			अगर(!(DONE_SC->SCp.phase & not_issued)) अणु
				काष्ठा aha152x_scdata *sc;
				काष्ठा scsi_cmnd *ptr = DONE_SC;
				DONE_SC=शून्य;

				sc = SCDATA(ptr);
				/* It was allocated in aha152x_पूर्णांकernal_queue? */
				BUG_ON(!sc);
				scsi_eh_prep_cmnd(ptr, &sc->ses, शून्य, 0, ~0);

				DO_UNLOCK(flags);
				aha152x_पूर्णांकernal_queue(ptr, शून्य, check_condition, ptr->scsi_करोne);
				DO_LOCK(flags);
			पूर्ण
		पूर्ण

		अगर(DONE_SC && DONE_SC->scsi_करोne) अणु
			काष्ठा scsi_cmnd *ptr = DONE_SC;
			DONE_SC=शून्य;

			/* turn led off, when no commands are in the driver */
			HOSTDATA(shpnt)->commands--;
			अगर (!HOSTDATA(shpnt)->commands)
				SETPORT(PORTA, 0);	/* turn led off */

			अगर(ptr->scsi_करोne != reset_करोne) अणु
				kमुक्त(ptr->host_scribble);
				ptr->host_scribble=शून्य;
			पूर्ण

			DO_UNLOCK(flags);
			ptr->scsi_करोne(ptr);
			DO_LOCK(flags);
		पूर्ण

		DONE_SC=शून्य;
#अगर defined(AHA152X_STAT)
	पूर्ण अन्यथा अणु
		HOSTDATA(shpnt)->busमुक्त_without_करोne_command++;
#पूर्ण_अगर
	पूर्ण

	अगर(ISSUE_SC)
		CURRENT_SC = हटाओ_first_SC(&ISSUE_SC);

	DO_UNLOCK(flags);

	अगर(CURRENT_SC) अणु
#अगर defined(AHA152X_STAT)
		action++;
#पूर्ण_अगर
		CURRENT_SC->SCp.phase |= selecting;

		/* clear selection समयout */
		SETPORT(SSTAT1, SELTO);

		SETPORT(SCSIID, (shpnt->this_id << OID_) | CURRENT_SC->device->id);
		SETPORT(SXFRCTL1, (PARITY ? ENSPCHK : 0 ) | ENSTIMER);
		SETPORT(SCSISEQ, ENSELO | ENAUTOATNO | (DISCONNECTED_SC ? ENRESELI : 0));
	पूर्ण अन्यथा अणु
#अगर defined(AHA152X_STAT)
		HOSTDATA(shpnt)->busमुक्त_without_new_command++;
#पूर्ण_अगर
		SETPORT(SCSISEQ, DISCONNECTED_SC ? ENRESELI : 0);
	पूर्ण

#अगर defined(AHA152X_STAT)
	अगर(!action)
		HOSTDATA(shpnt)->busमुक्त_without_any_action++;
#पूर्ण_अगर
पूर्ण

/*
 * Selection करोne (OUT)
 * - queue IDENTIFY message and SDTR to selected target क्रम message out
 *   (ATN निश्चितed स्वतःmagically via ENAUTOATNO in busमुक्त())
 */
अटल व्योम selकरो_run(काष्ठा Scsi_Host *shpnt)
अणु
	SETPORT(SCSISIG, 0);
	SETPORT(SSTAT1, CLRBUSFREE);
	SETPORT(SSTAT1, CLRPHASECHG);

	CURRENT_SC->SCp.phase &= ~(selecting|not_issued);

	SETPORT(SCSISEQ, 0);

	अगर (TESTLO(SSTAT0, SELDO)) अणु
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "aha152x: passing bus free condition\n");
		करोne(shpnt, DID_NO_CONNECT << 16);
		वापस;
	पूर्ण

	SETPORT(SSTAT0, CLRSELDO);

	ADDMSGO(IDENTIFY(RECONNECT, CURRENT_SC->device->lun));

	अगर (CURRENT_SC->SCp.phase & पातing) अणु
		ADDMSGO(ABORT);
	पूर्ण अन्यथा अगर (CURRENT_SC->SCp.phase & resetting) अणु
		ADDMSGO(BUS_DEVICE_RESET);
	पूर्ण अन्यथा अगर (SYNCNEG==0 && SYNCHRONOUS) अणु
		CURRENT_SC->SCp.phase |= syncneg;
		MSGOLEN += spi_populate_sync_msg(&MSGO(MSGOLEN), 50, 8);
		SYNCNEG=1;		/* negotiation in progress */
	पूर्ण

	SETRATE(SYNCRATE);
पूर्ण

/*
 * Selection समयout
 * - वापस command to mid-level with failure cause
 *
 */
अटल व्योम selto_run(काष्ठा Scsi_Host *shpnt)
अणु
	SETPORT(SCSISEQ, 0);
	SETPORT(SSTAT1, CLRSELTIMO);

	अगर (!CURRENT_SC)
		वापस;

	CURRENT_SC->SCp.phase &= ~selecting;

	अगर (CURRENT_SC->SCp.phase & पातed)
		करोne(shpnt, DID_ABORT << 16);
	अन्यथा अगर (TESTLO(SSTAT0, SELINGO))
		करोne(shpnt, DID_BUS_BUSY << 16);
	अन्यथा
		/* ARBITRATION won, but SELECTION failed */
		करोne(shpnt, DID_NO_CONNECT << 16);
पूर्ण

/*
 * Selection in करोne
 * - put current command back to issue queue
 *   (reconnection of a disconnected nexus instead
 *    of successful selection out)
 *
 */
अटल व्योम seldi_run(काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक selid;
	पूर्णांक target;
	अचिन्हित दीर्घ flags;

	SETPORT(SCSISIG, 0);
	SETPORT(SSTAT0, CLRSELDI);
	SETPORT(SSTAT1, CLRBUSFREE);
	SETPORT(SSTAT1, CLRPHASECHG);

	अगर(CURRENT_SC) अणु
		अगर(!(CURRENT_SC->SCp.phase & not_issued))
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
				    "command should not have been issued yet\n");

		DO_LOCK(flags);
		append_SC(&ISSUE_SC, CURRENT_SC);
		DO_UNLOCK(flags);

		CURRENT_SC = शून्य;
	पूर्ण

	अगर (!DISCONNECTED_SC)
		वापस;

	RECONN_TARGET=-1;

	selid = GETPORT(SELID) & ~(1 << shpnt->this_id);

	अगर (selid==0) अणु
		shost_prपूर्णांकk(KERN_INFO, shpnt,
			     "target id unknown (%02x)\n", selid);
		वापस;
	पूर्ण

	क्रम(target=7; !(selid & (1 << target)); target--)
		;

	अगर(selid & ~(1 << target)) अणु
		shost_prपूर्णांकk(KERN_INFO, shpnt,
			     "multiple targets reconnected (%02x)\n", selid);
	पूर्ण


	SETPORT(SCSIID, (shpnt->this_id << OID_) | target);
	SETPORT(SCSISEQ, 0);

	SETRATE(HOSTDATA(shpnt)->syncrate[target]);

	RECONN_TARGET=target;
पूर्ण

/*
 * message in phase
 * - handle initial message after reconnection to identअगरy
 *   reconnecting nexus
 * - queue command on DISCONNECTED_SC on DISCONNECT message
 * - set completed flag on COMMAND COMPLETE
 *   (other completition code moved to busमुक्त_run)
 * - handle response to SDTR
 * - clear synchronous transfer agreements on BUS RESET
 *
 * FIXME: what about SAVE POINTERS, RESTORE POINTERS?
 *
 */
अटल व्योम msgi_run(काष्ठा Scsi_Host *shpnt)
अणु
	क्रम(;;) अणु
		पूर्णांक sstat1 = GETPORT(SSTAT1);

		अगर(sstat1 & (PHASECHG|PHASEMIS|BUSFREE) || !(sstat1 & REQINIT))
			वापस;

		अगर (TESTLO(SSTAT0, SPIORDY))
			वापस;

		ADDMSGI(GETPORT(SCSIDAT));

		अगर(!CURRENT_SC) अणु
			अगर(LASTSTATE!=seldi) अणु
				shost_prपूर्णांकk(KERN_ERR, shpnt,
					     "message in w/o current command"
					     " not after reselection\n");
			पूर्ण

			/*
			 * Handle reselection
			 */
			अगर(!(MSGI(0) & IDENTIFY_BASE)) अणु
				shost_prपूर्णांकk(KERN_ERR, shpnt,
					     "target didn't identify after reselection\n");
				जारी;
			पूर्ण

			CURRENT_SC = हटाओ_lun_SC(&DISCONNECTED_SC, RECONN_TARGET, MSGI(0) & 0x3f);

			अगर (!CURRENT_SC) अणु
				show_queues(shpnt);
				shost_prपूर्णांकk(KERN_ERR, shpnt,
					     "no disconnected command"
					     " for target %d/%d\n",
					     RECONN_TARGET, MSGI(0) & 0x3f);
				जारी;
			पूर्ण

			CURRENT_SC->SCp.Message = MSGI(0);
			CURRENT_SC->SCp.phase &= ~disconnected;

			MSGILEN=0;

			/* next message अगर any */
			जारी;
		पूर्ण

		CURRENT_SC->SCp.Message = MSGI(0);

		चयन (MSGI(0)) अणु
		हाल DISCONNECT:
			अगर (!RECONNECT)
				scmd_prपूर्णांकk(KERN_WARNING, CURRENT_SC,
					    "target was not allowed to disconnect\n");

			CURRENT_SC->SCp.phase |= disconnected;
			अवरोध;

		हाल COMMAND_COMPLETE:
			CURRENT_SC->SCp.phase |= completed;
			अवरोध;

		हाल MESSAGE_REJECT:
			अगर (SYNCNEG==1) अणु
				scmd_prपूर्णांकk(KERN_INFO, CURRENT_SC,
					    "Synchronous Data Transfer Request"
					    " was rejected\n");
				SYNCNEG=2;	/* negotiation completed */
			पूर्ण अन्यथा
				scmd_prपूर्णांकk(KERN_INFO, CURRENT_SC,
					    "inbound message (MESSAGE REJECT)\n");
			अवरोध;

		हाल SAVE_POINTERS:
			अवरोध;

		हाल RESTORE_POINTERS:
			अवरोध;

		हाल EXTENDED_MESSAGE:
			अगर(MSGILEN<2 || MSGILEN<MSGI(1)+2) अणु
				/* not yet completed */
				जारी;
			पूर्ण

			चयन (MSGI(2)) अणु
			हाल EXTENDED_SDTR:
				अणु
					दीर्घ ticks;

					अगर (MSGI(1) != 3) अणु
						scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
							    "SDTR message length!=3\n");
						अवरोध;
					पूर्ण

					अगर (!HOSTDATA(shpnt)->synchronous)
						अवरोध;

					prपूर्णांकk(INFO_LEAD, CMDINFO(CURRENT_SC));
					spi_prपूर्णांक_msg(&MSGI(0));
					prपूर्णांकk("\n");

					ticks = (MSGI(3) * 4 + 49) / 50;

					अगर (syncneg) अणु
						/* negotiation in progress */
						अगर (ticks > 9 || MSGI(4) < 1 || MSGI(4) > 8) अणु
							ADDMSGO(MESSAGE_REJECT);
							scmd_prपूर्णांकk(KERN_INFO,
								    CURRENT_SC,
								    "received Synchronous Data Transfer Request invalid - rejected\n");
							अवरोध;
						पूर्ण

						SYNCRATE |= ((ticks - 2) << 4) + MSGI(4);
					पूर्ण अन्यथा अगर (ticks <= 9 && MSGI(4) >= 1) अणु
						ADDMSGO(EXTENDED_MESSAGE);
						ADDMSGO(3);
						ADDMSGO(EXTENDED_SDTR);
						अगर (ticks < 4) अणु
							ticks = 4;
							ADDMSGO(50);
						पूर्ण अन्यथा
							ADDMSGO(MSGI(3));

						अगर (MSGI(4) > 8)
							MSGI(4) = 8;

						ADDMSGO(MSGI(4));

						SYNCRATE |= ((ticks - 2) << 4) + MSGI(4);
					पूर्ण अन्यथा अणु
						/* requested SDTR is too slow, करो it asynchronously */
						scmd_prपूर्णांकk(KERN_INFO,
							    CURRENT_SC,
							    "Synchronous Data Transfer Request too slow - Rejecting\n");
						ADDMSGO(MESSAGE_REJECT);
					पूर्ण

					/* negotiation completed */
					SYNCNEG=2;
					SETRATE(SYNCRATE);
				पूर्ण
				अवरोध;

			हाल BUS_DEVICE_RESET:
				अणु
					पूर्णांक i;

					क्रम(i=0; i<8; i++) अणु
						HOSTDATA(shpnt)->syncrate[i]=0;
						HOSTDATA(shpnt)->syncneg[i]=0;
					पूर्ण

				पूर्ण
				अवरोध;

			हाल EXTENDED_MODIFY_DATA_POINTER:
			हाल EXTENDED_EXTENDED_IDENTIFY:
			हाल EXTENDED_WDTR:
			शेष:
				ADDMSGO(MESSAGE_REJECT);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण

		MSGILEN=0;
	पूर्ण
पूर्ण

अटल व्योम msgi_end(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(MSGILEN>0)
		scmd_prपूर्णांकk(KERN_WARNING, CURRENT_SC,
			    "target left before message completed (%d)\n",
			    MSGILEN);

	अगर (MSGOLEN > 0 && !(GETPORT(SSTAT1) & BUSFREE))
		SETPORT(SCSISIG, P_MSGI | SIG_ATNO);
पूर्ण

/*
 * message out phase
 *
 */
अटल व्योम msgo_init(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(MSGOLEN==0) अणु
		अगर((CURRENT_SC->SCp.phase & syncneg) && SYNCNEG==2 && SYNCRATE==0) अणु
			ADDMSGO(IDENTIFY(RECONNECT, CURRENT_SC->device->lun));
		पूर्ण अन्यथा अणु
			scmd_prपूर्णांकk(KERN_INFO, CURRENT_SC,
				    "unexpected MESSAGE OUT phase; rejecting\n");
			ADDMSGO(MESSAGE_REJECT);
		पूर्ण
	पूर्ण

पूर्ण

/*
 * message out phase
 *
 */
अटल व्योम msgo_run(काष्ठा Scsi_Host *shpnt)
अणु
	जबतक(MSGO_I<MSGOLEN) अणु
		अगर (TESTLO(SSTAT0, SPIORDY))
			वापस;

		अगर (MSGO_I==MSGOLEN-1) अणु
			/* Leave MESSAGE OUT after transfer */
			SETPORT(SSTAT1, CLRATNO);
		पूर्ण


		अगर (MSGO(MSGO_I) & IDENTIFY_BASE)
			CURRENT_SC->SCp.phase |= identअगरied;

		अगर (MSGO(MSGO_I)==ABORT)
			CURRENT_SC->SCp.phase |= पातed;

		अगर (MSGO(MSGO_I)==BUS_DEVICE_RESET)
			CURRENT_SC->SCp.phase |= resetted;

		SETPORT(SCSIDAT, MSGO(MSGO_I++));
	पूर्ण
पूर्ण

अटल व्योम msgo_end(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(MSGO_I<MSGOLEN) अणु
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "message sent incompletely (%d/%d)\n",
			    MSGO_I, MSGOLEN);
		अगर(SYNCNEG==1) अणु
			scmd_prपूर्णांकk(KERN_INFO, CURRENT_SC,
				    "Synchronous Data Transfer Request was rejected\n");
			SYNCNEG=2;
		पूर्ण
	पूर्ण

	MSGO_I  = 0;
	MSGOLEN = 0;
पूर्ण

/*
 * command phase
 *
 */
अटल व्योम cmd_init(काष्ठा Scsi_Host *shpnt)
अणु
	अगर (CURRENT_SC->SCp.sent_command) अणु
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "command already sent\n");
		करोne(shpnt, DID_ERROR << 16);
		वापस;
	पूर्ण

	CMD_I=0;
पूर्ण

/*
 * command phase
 *
 */
अटल व्योम cmd_run(काष्ठा Scsi_Host *shpnt)
अणु
	जबतक(CMD_I<CURRENT_SC->cmd_len) अणु
		अगर (TESTLO(SSTAT0, SPIORDY))
			वापस;

		SETPORT(SCSIDAT, CURRENT_SC->cmnd[CMD_I++]);
	पूर्ण
पूर्ण

अटल व्योम cmd_end(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(CMD_I<CURRENT_SC->cmd_len)
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "command sent incompletely (%d/%d)\n",
			    CMD_I, CURRENT_SC->cmd_len);
	अन्यथा
		CURRENT_SC->SCp.sent_command++;
पूर्ण

/*
 * status phase
 *
 */
अटल व्योम status_run(काष्ठा Scsi_Host *shpnt)
अणु
	अगर (TESTLO(SSTAT0, SPIORDY))
		वापस;

	CURRENT_SC->SCp.Status = GETPORT(SCSIDAT);

पूर्ण

/*
 * data in phase
 *
 */
अटल व्योम datai_init(काष्ठा Scsi_Host *shpnt)
अणु
	SETPORT(DMACNTRL0, RSTFIFO);
	SETPORT(DMACNTRL0, RSTFIFO|ENDMA);

	SETPORT(SXFRCTL0, CH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1|SCSIEN|DMAEN);

	SETPORT(SIMODE0, 0);
	SETPORT(SIMODE1, ENSCSIPERR | ENSCSIRST | ENPHASEMIS | ENBUSFREE);

	DATA_LEN=0;
पूर्ण

अटल व्योम datai_run(काष्ठा Scsi_Host *shpnt)
अणु
	अचिन्हित दीर्घ the_समय;
	पूर्णांक fअगरodata, data_count;

	/*
	 * loop जबतक the phase persists or the fअगरos are not empty
	 *
	 */
	जबतक(TESTLO(DMASTAT, INTSTAT) || TESTLO(DMASTAT, DFIFOEMP) || TESTLO(SSTAT2, SEMPTY)) अणु
		/* FIXME: maybe this should be करोne by setting up
		 * STCNT to trigger ENSWRAP पूर्णांकerrupt, instead of
		 * polling क्रम DFIFOFULL
		 */
		the_समय=jअगरfies + 100*HZ;
		जबतक(TESTLO(DMASTAT, DFIFOFULL|INTSTAT) && समय_beक्रमe(jअगरfies,the_समय))
			barrier();

		अगर(TESTLO(DMASTAT, DFIFOFULL|INTSTAT)) अणु
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC, "datai timeout\n");
			अवरोध;
		पूर्ण

		अगर(TESTHI(DMASTAT, DFIFOFULL)) अणु
			fअगरodata = 128;
		पूर्ण अन्यथा अणु
			the_समय=jअगरfies + 100*HZ;
			जबतक(TESTLO(SSTAT2, SEMPTY) && समय_beक्रमe(jअगरfies,the_समय))
				barrier();

			अगर(TESTLO(SSTAT2, SEMPTY)) अणु
				scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
					    "datai sempty timeout");
				अवरोध;
			पूर्ण

			fअगरodata = GETPORT(FIFOSTAT);
		पूर्ण

		अगर(CURRENT_SC->SCp.this_residual>0) अणु
			जबतक(fअगरodata>0 && CURRENT_SC->SCp.this_residual>0) अणु
				data_count = fअगरodata > CURRENT_SC->SCp.this_residual ?
						CURRENT_SC->SCp.this_residual :
						fअगरodata;
				fअगरodata -= data_count;

				अगर (data_count & 1) अणु
					SETPORT(DMACNTRL0, ENDMA|_8BIT);
					*CURRENT_SC->SCp.ptr++ = GETPORT(DATAPORT);
					CURRENT_SC->SCp.this_residual--;
					DATA_LEN++;
					SETPORT(DMACNTRL0, ENDMA);
				पूर्ण

				अगर (data_count > 1) अणु
					data_count >>= 1;
					insw(DATAPORT, CURRENT_SC->SCp.ptr, data_count);
					CURRENT_SC->SCp.ptr += 2 * data_count;
					CURRENT_SC->SCp.this_residual -= 2 * data_count;
					DATA_LEN += 2 * data_count;
				पूर्ण

				अगर (CURRENT_SC->SCp.this_residual == 0 &&
				    !sg_is_last(CURRENT_SC->SCp.buffer)) अणु
					/* advance to next buffer */
					CURRENT_SC->SCp.buffer = sg_next(CURRENT_SC->SCp.buffer);
					CURRENT_SC->SCp.ptr           = SG_ADDRESS(CURRENT_SC->SCp.buffer);
					CURRENT_SC->SCp.this_residual = CURRENT_SC->SCp.buffer->length;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (fअगरodata > 0) अणु
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
				    "no buffers left for %d(%d) bytes"
				    " (data overrun!?)\n",
				    fअगरodata, GETPORT(FIFOSTAT));
			SETPORT(DMACNTRL0, ENDMA|_8BIT);
			जबतक(fअगरodata>0) अणु
				GETPORT(DATAPORT);
				fअगरodata--;
				DATA_LEN++;
			पूर्ण
			SETPORT(DMACNTRL0, ENDMA|_8BIT);
		पूर्ण
	पूर्ण

	अगर(TESTLO(DMASTAT, INTSTAT) ||
	   TESTLO(DMASTAT, DFIFOEMP) ||
	   TESTLO(SSTAT2, SEMPTY) ||
	   GETPORT(FIFOSTAT)>0) अणु
		/*
		 * something went wrong, अगर there's something left in the fअगरos
		 * or the phase didn't change
		 */
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "fifos should be empty and phase should have changed\n");
	पूर्ण

	अगर(DATA_LEN!=GETSTCNT()) अणु
		scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
			    "manual transfer count differs from automatic "
			    "(count=%d;stcnt=%d;diff=%d;fifostat=%d)",
			    DATA_LEN, GETSTCNT(), GETSTCNT()-DATA_LEN,
			    GETPORT(FIFOSTAT));
		mdelay(10000);
	पूर्ण
पूर्ण

अटल व्योम datai_end(काष्ठा Scsi_Host *shpnt)
अणु
	CMD_INC_RESID(CURRENT_SC, -GETSTCNT());

	SETPORT(SXFRCTL0, CH1|CLRSTCNT);
	SETPORT(DMACNTRL0, 0);
पूर्ण

/*
 * data out phase
 *
 */
अटल व्योम datao_init(काष्ठा Scsi_Host *shpnt)
अणु
	SETPORT(DMACNTRL0, WRITE_READ | RSTFIFO);
	SETPORT(DMACNTRL0, WRITE_READ | ENDMA);

	SETPORT(SXFRCTL0, CH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1|SCSIEN|DMAEN);

	SETPORT(SIMODE0, 0);
	SETPORT(SIMODE1, ENSCSIPERR | ENSCSIRST | ENPHASEMIS | ENBUSFREE );

	DATA_LEN = scsi_get_resid(CURRENT_SC);
पूर्ण

अटल व्योम datao_run(काष्ठा Scsi_Host *shpnt)
अणु
	अचिन्हित दीर्घ the_समय;
	पूर्णांक data_count;

	/* until phase changes or all data sent */
	जबतक(TESTLO(DMASTAT, INTSTAT) && CURRENT_SC->SCp.this_residual>0) अणु
		data_count = 128;
		अगर(data_count > CURRENT_SC->SCp.this_residual)
			data_count=CURRENT_SC->SCp.this_residual;

		अगर(TESTLO(DMASTAT, DFIFOEMP)) अणु
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
				    "datao fifo not empty (%d)",
				    GETPORT(FIFOSTAT));
			अवरोध;
		पूर्ण

		अगर(data_count & 1) अणु
			SETPORT(DMACNTRL0,WRITE_READ|ENDMA|_8BIT);
			SETPORT(DATAPORT, *CURRENT_SC->SCp.ptr++);
			CURRENT_SC->SCp.this_residual--;
			CMD_INC_RESID(CURRENT_SC, -1);
			SETPORT(DMACNTRL0,WRITE_READ|ENDMA);
		पूर्ण

		अगर(data_count > 1) अणु
			data_count >>= 1;
			outsw(DATAPORT, CURRENT_SC->SCp.ptr, data_count);
			CURRENT_SC->SCp.ptr           += 2 * data_count;
			CURRENT_SC->SCp.this_residual -= 2 * data_count;
			CMD_INC_RESID(CURRENT_SC, -2 * data_count);
		पूर्ण

		अगर (CURRENT_SC->SCp.this_residual == 0 &&
		    !sg_is_last(CURRENT_SC->SCp.buffer)) अणु
			/* advance to next buffer */
			CURRENT_SC->SCp.buffer = sg_next(CURRENT_SC->SCp.buffer);
			CURRENT_SC->SCp.ptr           = SG_ADDRESS(CURRENT_SC->SCp.buffer);
			CURRENT_SC->SCp.this_residual = CURRENT_SC->SCp.buffer->length;
		पूर्ण

		the_समय=jअगरfies + 100*HZ;
		जबतक(TESTLO(DMASTAT, DFIFOEMP|INTSTAT) && समय_beक्रमe(jअगरfies,the_समय))
			barrier();

		अगर(TESTLO(DMASTAT, DFIFOEMP|INTSTAT)) अणु
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC, "dataout timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम datao_end(काष्ठा Scsi_Host *shpnt)
अणु
	अगर(TESTLO(DMASTAT, DFIFOEMP)) अणु
		u32 datao_cnt = GETSTCNT();
		पूर्णांक datao_out = DATA_LEN - scsi_get_resid(CURRENT_SC);
		पूर्णांक करोne;
		काष्ठा scatterlist *sg = scsi_sglist(CURRENT_SC);

		CMD_INC_RESID(CURRENT_SC, datao_out - datao_cnt);

		करोne = scsi_bufflen(CURRENT_SC) - scsi_get_resid(CURRENT_SC);
		/* Locate the first SG entry not yet sent */
		जबतक (करोne > 0 && !sg_is_last(sg)) अणु
			अगर (करोne < sg->length)
				अवरोध;
			करोne -= sg->length;
			sg = sg_next(sg);
		पूर्ण

		CURRENT_SC->SCp.buffer = sg;
		CURRENT_SC->SCp.ptr = SG_ADDRESS(CURRENT_SC->SCp.buffer) + करोne;
		CURRENT_SC->SCp.this_residual = CURRENT_SC->SCp.buffer->length -
			करोne;
	पूर्ण

	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	SETPORT(DMACNTRL0, 0);
पूर्ण

/*
 * figure out what state we're in
 *
 */
अटल पूर्णांक update_state(काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक dataphase=0;
	अचिन्हित पूर्णांक stat0 = GETPORT(SSTAT0);
	अचिन्हित पूर्णांक stat1 = GETPORT(SSTAT1);

	PREVSTATE = STATE;
	STATE=unknown;

	अगर(stat1 & SCSIRSTI) अणु
		STATE=rsti;
		SETPORT(SCSISEQ,0);
		SETPORT(SSTAT1,SCSIRSTI);
	पूर्ण अन्यथा अगर (stat0 & SELDI && PREVSTATE == busमुक्त) अणु
		STATE=seldi;
	पूर्ण अन्यथा अगर(stat0 & SELDO && CURRENT_SC && (CURRENT_SC->SCp.phase & selecting)) अणु
		STATE=selकरो;
	पूर्ण अन्यथा अगर(stat1 & SELTO) अणु
		STATE=selto;
	पूर्ण अन्यथा अगर(stat1 & BUSFREE) अणु
		STATE=busमुक्त;
		SETPORT(SSTAT1,BUSFREE);
	पूर्ण अन्यथा अगर(stat1 & SCSIPERR) अणु
		STATE=parerr;
		SETPORT(SSTAT1,SCSIPERR);
	पूर्ण अन्यथा अगर(stat1 & REQINIT) अणु
		चयन(GETPORT(SCSISIG) & P_MASK) अणु
		हाल P_MSGI:	STATE=msgi;	अवरोध;
		हाल P_MSGO:	STATE=msgo;	अवरोध;
		हाल P_DATAO:	STATE=datao;	अवरोध;
		हाल P_DATAI:	STATE=datai;	अवरोध;
		हाल P_STATUS:	STATE=status;	अवरोध;
		हाल P_CMD:	STATE=cmd;	अवरोध;
		पूर्ण
		dataphase=1;
	पूर्ण

	अगर((stat0 & SELDI) && STATE!=seldi && !dataphase) अणु
		scmd_prपूर्णांकk(KERN_INFO, CURRENT_SC, "reselection missed?");
	पूर्ण

	अगर(STATE!=PREVSTATE) अणु
		LASTSTATE=PREVSTATE;
	पूर्ण

	वापस dataphase;
पूर्ण

/*
 * handle parity error
 *
 * FIXME: in which phase?
 *
 */
अटल व्योम parerr_run(काष्ठा Scsi_Host *shpnt)
अणु
	scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC, "parity error\n");
	करोne(shpnt, DID_PARITY << 16);
पूर्ण

/*
 * handle reset in
 *
 */
अटल व्योम rsti_run(काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा scsi_cmnd *ptr;

	shost_prपूर्णांकk(KERN_NOTICE, shpnt, "scsi reset in\n");

	ptr=DISCONNECTED_SC;
	जबतक(ptr) अणु
		काष्ठा scsi_cmnd *next = SCNEXT(ptr);

		अगर (!ptr->device->soft_reset) अणु
			हटाओ_SC(&DISCONNECTED_SC, ptr);

			kमुक्त(ptr->host_scribble);
			ptr->host_scribble=शून्य;

			ptr->result =  DID_RESET << 16;
			ptr->scsi_करोne(ptr);
		पूर्ण

		ptr = next;
	पूर्ण

	अगर(CURRENT_SC && !CURRENT_SC->device->soft_reset)
		करोne(shpnt, DID_RESET << 16 );
पूर्ण


/*
 * bottom-half handler
 *
 */
अटल व्योम is_complete(काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक dataphase;
	अचिन्हित दीर्घ flags;
	पूर्णांक pending;

	अगर(!shpnt)
		वापस;

	DO_LOCK(flags);

	अगर( HOSTDATA(shpnt)->service==0 )  अणु
		DO_UNLOCK(flags);
		वापस;
	पूर्ण

	HOSTDATA(shpnt)->service = 0;

	अगर(HOSTDATA(shpnt)->in_पूर्णांकr) अणु
		DO_UNLOCK(flags);
		/* aha152x_error never वापसs.. */
		aha152x_error(shpnt, "bottom-half already running!?");
	पूर्ण
	HOSTDATA(shpnt)->in_पूर्णांकr++;

	/*
	 * loop जबतक there are पूर्णांकerrupt conditions pending
	 *
	 */
	करो अणु
		अचिन्हित दीर्घ start = jअगरfies;
		DO_UNLOCK(flags);

		dataphase=update_state(shpnt);

		/*
		 * end previous state
		 *
		 */
		अगर(PREVSTATE!=STATE && states[PREVSTATE].end)
			states[PREVSTATE].end(shpnt);

		/*
		 * disable SPIO mode अगर previous phase used it
		 * and this one करोesn't
		 *
		 */
		अगर(states[PREVSTATE].spio && !states[STATE].spio) अणु
			SETPORT(SXFRCTL0, CH1);
			SETPORT(DMACNTRL0, 0);
			अगर(CURRENT_SC)
				CURRENT_SC->SCp.phase &= ~spiordy;
		पूर्ण

		/*
		 * accept current dataphase phase
		 *
		 */
		अगर(dataphase) अणु
			SETPORT(SSTAT0, REQINIT);
			SETPORT(SCSISIG, GETPORT(SCSISIG) & P_MASK);
			SETPORT(SSTAT1, PHASECHG);
		पूर्ण

		/*
		 * enable SPIO mode अगर previous didn't use it
		 * and this one करोes
		 *
		 */
		अगर(!states[PREVSTATE].spio && states[STATE].spio) अणु
			SETPORT(DMACNTRL0, 0);
			SETPORT(SXFRCTL0, CH1|SPIOEN);
			अगर(CURRENT_SC)
				CURRENT_SC->SCp.phase |= spiordy;
		पूर्ण

		/*
		 * initialize क्रम new state
		 *
		 */
		अगर(PREVSTATE!=STATE && states[STATE].init)
			states[STATE].init(shpnt);

		/*
		 * handle current state
		 *
		 */
		अगर(states[STATE].run)
			states[STATE].run(shpnt);
		अन्यथा
			scmd_prपूर्णांकk(KERN_ERR, CURRENT_SC,
				    "unexpected state (%x)\n", STATE);

		/*
		 * setup controller to पूर्णांकerrupt on
		 * the next expected condition and
		 * loop अगर it's alपढ़ोy there
		 *
		 */
		DO_LOCK(flags);
		pending=setup_expected_पूर्णांकerrupts(shpnt);
#अगर defined(AHA152X_STAT)
		HOSTDATA(shpnt)->count[STATE]++;
		अगर(PREVSTATE!=STATE)
			HOSTDATA(shpnt)->count_trans[STATE]++;
		HOSTDATA(shpnt)->समय[STATE] += jअगरfies-start;
#पूर्ण_अगर

	पूर्ण जबतक(pending);

	/*
	 * enable पूर्णांकerrupts and leave bottom-half
	 *
	 */
	HOSTDATA(shpnt)->in_पूर्णांकr--;
	SETBITS(DMACNTRL0, INTEN);
	DO_UNLOCK(flags);
पूर्ण


/*
 * Dump the current driver status and panic
 */
अटल व्योम aha152x_error(काष्ठा Scsi_Host *shpnt, अक्षर *msg)
अणु
	shost_prपूर्णांकk(KERN_EMERG, shpnt, "%s\n", msg);
	show_queues(shpnt);
	panic("aha152x panic\n");
पूर्ण

/*
 * display enabled पूर्णांकerrupts
 */
अटल व्योम disp_enपूर्णांकr(काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक s0, s1;

	s0 = GETPORT(SIMODE0);
	s1 = GETPORT(SIMODE1);

	shost_prपूर्णांकk(KERN_DEBUG, shpnt,
		     "enabled interrupts (%s%s%s%s%s%s%s%s%s%s%s%s%s%s)\n",
		     (s0 & ENSELDO) ? "ENSELDO " : "",
		     (s0 & ENSELDI) ? "ENSELDI " : "",
		     (s0 & ENSELINGO) ? "ENSELINGO " : "",
		     (s0 & ENSWRAP) ? "ENSWRAP " : "",
		     (s0 & ENSDONE) ? "ENSDONE " : "",
		     (s0 & ENSPIORDY) ? "ENSPIORDY " : "",
		     (s0 & ENDMADONE) ? "ENDMADONE " : "",
		     (s1 & ENSELTIMO) ? "ENSELTIMO " : "",
		     (s1 & ENATNTARG) ? "ENATNTARG " : "",
		     (s1 & ENPHASEMIS) ? "ENPHASEMIS " : "",
		     (s1 & ENBUSFREE) ? "ENBUSFREE " : "",
		     (s1 & ENSCSIPERR) ? "ENSCSIPERR " : "",
		     (s1 & ENPHASECHG) ? "ENPHASECHG " : "",
		     (s1 & ENREQINIT) ? "ENREQINIT " : "");
पूर्ण

/*
 * Show the command data of a command
 */
अटल व्योम show_command(काष्ठा scsi_cmnd *ptr)
अणु
	scsi_prपूर्णांक_command(ptr);
	scmd_prपूर्णांकk(KERN_DEBUG, ptr,
		    "request_bufflen=%d; resid=%d; "
		    "phase |%s%s%s%s%s%s%s%s%s; next=0x%p",
		    scsi_bufflen(ptr), scsi_get_resid(ptr),
		    (ptr->SCp.phase & not_issued) ? "not issued|" : "",
		    (ptr->SCp.phase & selecting) ? "selecting|" : "",
		    (ptr->SCp.phase & identअगरied) ? "identified|" : "",
		    (ptr->SCp.phase & disconnected) ? "disconnected|" : "",
		    (ptr->SCp.phase & completed) ? "completed|" : "",
		    (ptr->SCp.phase & spiordy) ? "spiordy|" : "",
		    (ptr->SCp.phase & syncneg) ? "syncneg|" : "",
		    (ptr->SCp.phase & पातed) ? "aborted|" : "",
		    (ptr->SCp.phase & resetted) ? "resetted|" : "",
		    (SCDATA(ptr)) ? SCNEXT(ptr) : शून्य);
पूर्ण

/*
 * Dump the queued data
 */
अटल व्योम show_queues(काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा scsi_cmnd *ptr;
	अचिन्हित दीर्घ flags;

	DO_LOCK(flags);
	prपूर्णांकk(KERN_DEBUG "\nqueue status:\nissue_SC:\n");
	क्रम (ptr = ISSUE_SC; ptr; ptr = SCNEXT(ptr))
		show_command(ptr);
	DO_UNLOCK(flags);

	prपूर्णांकk(KERN_DEBUG "current_SC:\n");
	अगर (CURRENT_SC)
		show_command(CURRENT_SC);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "none\n");

	prपूर्णांकk(KERN_DEBUG "disconnected_SC:\n");
	क्रम (ptr = DISCONNECTED_SC; ptr; ptr = SCDATA(ptr) ? SCNEXT(ptr) : शून्य)
		show_command(ptr);

	disp_enपूर्णांकr(shpnt);
पूर्ण

अटल व्योम get_command(काष्ठा seq_file *m, काष्ठा scsi_cmnd * ptr)
अणु
	पूर्णांक i;

	seq_म_लिखो(m, "%p: target=%d; lun=%d; cmnd=( ",
		ptr, ptr->device->id, (u8)ptr->device->lun);

	क्रम (i = 0; i < COMMAND_SIZE(ptr->cmnd[0]); i++)
		seq_म_लिखो(m, "0x%02x ", ptr->cmnd[i]);

	seq_म_लिखो(m, "); resid=%d; residual=%d; buffers=%d; phase |",
		scsi_get_resid(ptr), ptr->SCp.this_residual,
		sg_nents(ptr->SCp.buffer) - 1);

	अगर (ptr->SCp.phase & not_issued)
		seq_माला_दो(m, "not issued|");
	अगर (ptr->SCp.phase & selecting)
		seq_माला_दो(m, "selecting|");
	अगर (ptr->SCp.phase & disconnected)
		seq_माला_दो(m, "disconnected|");
	अगर (ptr->SCp.phase & पातed)
		seq_माला_दो(m, "aborted|");
	अगर (ptr->SCp.phase & identअगरied)
		seq_माला_दो(m, "identified|");
	अगर (ptr->SCp.phase & completed)
		seq_माला_दो(m, "completed|");
	अगर (ptr->SCp.phase & spiordy)
		seq_माला_दो(m, "spiordy|");
	अगर (ptr->SCp.phase & syncneg)
		seq_माला_दो(m, "syncneg|");
	seq_म_लिखो(m, "; next=0x%p\n", SCNEXT(ptr));
पूर्ण

अटल व्योम get_ports(काष्ठा seq_file *m, काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक s;

	seq_म_लिखो(m, "\n%s: %s(%s) ", CURRENT_SC ? "on bus" : "waiting", states[STATE].name, states[PREVSTATE].name);

	s = GETPORT(SCSISEQ);
	seq_माला_दो(m, "SCSISEQ( ");
	अगर (s & TEMODEO)
		seq_माला_दो(m, "TARGET MODE ");
	अगर (s & ENSELO)
		seq_माला_दो(m, "SELO ");
	अगर (s & ENSELI)
		seq_माला_दो(m, "SELI ");
	अगर (s & ENRESELI)
		seq_माला_दो(m, "RESELI ");
	अगर (s & ENAUTOATNO)
		seq_माला_दो(m, "AUTOATNO ");
	अगर (s & ENAUTOATNI)
		seq_माला_दो(m, "AUTOATNI ");
	अगर (s & ENAUTOATNP)
		seq_माला_दो(m, "AUTOATNP ");
	अगर (s & SCSIRSTO)
		seq_माला_दो(m, "SCSIRSTO ");
	seq_माला_दो(m, ");");

	seq_माला_दो(m, " SCSISIG(");
	s = GETPORT(SCSISIG);
	चयन (s & P_MASK) अणु
	हाल P_DATAO:
		seq_माला_दो(m, "DATA OUT");
		अवरोध;
	हाल P_DATAI:
		seq_माला_दो(m, "DATA IN");
		अवरोध;
	हाल P_CMD:
		seq_माला_दो(m, "COMMAND");
		अवरोध;
	हाल P_STATUS:
		seq_माला_दो(m, "STATUS");
		अवरोध;
	हाल P_MSGO:
		seq_माला_दो(m, "MESSAGE OUT");
		अवरोध;
	हाल P_MSGI:
		seq_माला_दो(m, "MESSAGE IN");
		अवरोध;
	शेष:
		seq_माला_दो(m, "*invalid*");
		अवरोध;
	पूर्ण

	seq_माला_दो(m, "); ");

	seq_म_लिखो(m, "INTSTAT (%s); ", TESTHI(DMASTAT, INTSTAT) ? "hi" : "lo");

	seq_माला_दो(m, "SSTAT( ");
	s = GETPORT(SSTAT0);
	अगर (s & TARGET)
		seq_माला_दो(m, "TARGET ");
	अगर (s & SELDO)
		seq_माला_दो(m, "SELDO ");
	अगर (s & SELDI)
		seq_माला_दो(m, "SELDI ");
	अगर (s & SELINGO)
		seq_माला_दो(m, "SELINGO ");
	अगर (s & SWRAP)
		seq_माला_दो(m, "SWRAP ");
	अगर (s & SDONE)
		seq_माला_दो(m, "SDONE ");
	अगर (s & SPIORDY)
		seq_माला_दो(m, "SPIORDY ");
	अगर (s & DMADONE)
		seq_माला_दो(m, "DMADONE ");

	s = GETPORT(SSTAT1);
	अगर (s & SELTO)
		seq_माला_दो(m, "SELTO ");
	अगर (s & ATNTARG)
		seq_माला_दो(m, "ATNTARG ");
	अगर (s & SCSIRSTI)
		seq_माला_दो(m, "SCSIRSTI ");
	अगर (s & PHASEMIS)
		seq_माला_दो(m, "PHASEMIS ");
	अगर (s & BUSFREE)
		seq_माला_दो(m, "BUSFREE ");
	अगर (s & SCSIPERR)
		seq_माला_दो(m, "SCSIPERR ");
	अगर (s & PHASECHG)
		seq_माला_दो(m, "PHASECHG ");
	अगर (s & REQINIT)
		seq_माला_दो(m, "REQINIT ");
	seq_माला_दो(m, "); ");


	seq_माला_दो(m, "SSTAT( ");

	s = GETPORT(SSTAT0) & GETPORT(SIMODE0);

	अगर (s & TARGET)
		seq_माला_दो(m, "TARGET ");
	अगर (s & SELDO)
		seq_माला_दो(m, "SELDO ");
	अगर (s & SELDI)
		seq_माला_दो(m, "SELDI ");
	अगर (s & SELINGO)
		seq_माला_दो(m, "SELINGO ");
	अगर (s & SWRAP)
		seq_माला_दो(m, "SWRAP ");
	अगर (s & SDONE)
		seq_माला_दो(m, "SDONE ");
	अगर (s & SPIORDY)
		seq_माला_दो(m, "SPIORDY ");
	अगर (s & DMADONE)
		seq_माला_दो(m, "DMADONE ");

	s = GETPORT(SSTAT1) & GETPORT(SIMODE1);

	अगर (s & SELTO)
		seq_माला_दो(m, "SELTO ");
	अगर (s & ATNTARG)
		seq_माला_दो(m, "ATNTARG ");
	अगर (s & SCSIRSTI)
		seq_माला_दो(m, "SCSIRSTI ");
	अगर (s & PHASEMIS)
		seq_माला_दो(m, "PHASEMIS ");
	अगर (s & BUSFREE)
		seq_माला_दो(m, "BUSFREE ");
	अगर (s & SCSIPERR)
		seq_माला_दो(m, "SCSIPERR ");
	अगर (s & PHASECHG)
		seq_माला_दो(m, "PHASECHG ");
	अगर (s & REQINIT)
		seq_माला_दो(m, "REQINIT ");
	seq_माला_दो(m, "); ");

	seq_माला_दो(m, "SXFRCTL0( ");

	s = GETPORT(SXFRCTL0);
	अगर (s & SCSIEN)
		seq_माला_दो(m, "SCSIEN ");
	अगर (s & DMAEN)
		seq_माला_दो(m, "DMAEN ");
	अगर (s & CH1)
		seq_माला_दो(m, "CH1 ");
	अगर (s & CLRSTCNT)
		seq_माला_दो(m, "CLRSTCNT ");
	अगर (s & SPIOEN)
		seq_माला_दो(m, "SPIOEN ");
	अगर (s & CLRCH1)
		seq_माला_दो(m, "CLRCH1 ");
	seq_माला_दो(m, "); ");

	seq_माला_दो(m, "SIGNAL( ");

	s = GETPORT(SCSISIG);
	अगर (s & SIG_ATNI)
		seq_माला_दो(m, "ATNI ");
	अगर (s & SIG_SELI)
		seq_माला_दो(m, "SELI ");
	अगर (s & SIG_BSYI)
		seq_माला_दो(m, "BSYI ");
	अगर (s & SIG_REQI)
		seq_माला_दो(m, "REQI ");
	अगर (s & SIG_ACKI)
		seq_माला_दो(m, "ACKI ");
	seq_माला_दो(m, "); ");

	seq_म_लिखो(m, "SELID(%02x), ", GETPORT(SELID));

	seq_म_लिखो(m, "STCNT(%d), ", GETSTCNT());

	seq_माला_दो(m, "SSTAT2( ");

	s = GETPORT(SSTAT2);
	अगर (s & SOFFSET)
		seq_माला_दो(m, "SOFFSET ");
	अगर (s & SEMPTY)
		seq_माला_दो(m, "SEMPTY ");
	अगर (s & SFULL)
		seq_माला_दो(m, "SFULL ");
	seq_म_लिखो(m, "); SFCNT (%d); ", s & (SFULL | SFCNT));

	s = GETPORT(SSTAT3);
	seq_म_लिखो(m, "SCSICNT (%d), OFFCNT(%d), ", (s & 0xf0) >> 4, s & 0x0f);

	seq_माला_दो(m, "SSTAT4( ");
	s = GETPORT(SSTAT4);
	अगर (s & SYNCERR)
		seq_माला_दो(m, "SYNCERR ");
	अगर (s & FWERR)
		seq_माला_दो(m, "FWERR ");
	अगर (s & FRERR)
		seq_माला_दो(m, "FRERR ");
	seq_माला_दो(m, "); ");

	seq_माला_दो(m, "DMACNTRL0( ");
	s = GETPORT(DMACNTRL0);
	seq_म_लिखो(m, "%s ", s & _8BIT ? "8BIT" : "16BIT");
	seq_म_लिखो(m, "%s ", s & DMA ? "DMA" : "PIO");
	seq_म_लिखो(m, "%s ", s & WRITE_READ ? "WRITE" : "READ");
	अगर (s & ENDMA)
		seq_माला_दो(m, "ENDMA ");
	अगर (s & INTEN)
		seq_माला_दो(m, "INTEN ");
	अगर (s & RSTFIFO)
		seq_माला_दो(m, "RSTFIFO ");
	अगर (s & SWINT)
		seq_माला_दो(m, "SWINT ");
	seq_माला_दो(m, "); ");

	seq_माला_दो(m, "DMASTAT( ");
	s = GETPORT(DMASTAT);
	अगर (s & ATDONE)
		seq_माला_दो(m, "ATDONE ");
	अगर (s & WORDRDY)
		seq_माला_दो(m, "WORDRDY ");
	अगर (s & DFIFOFULL)
		seq_माला_दो(m, "DFIFOFULL ");
	अगर (s & DFIFOEMP)
		seq_माला_दो(m, "DFIFOEMP ");
	seq_माला_दो(m, ")\n");

	seq_माला_दो(m, "enabled interrupts( ");

	s = GETPORT(SIMODE0);
	अगर (s & ENSELDO)
		seq_माला_दो(m, "ENSELDO ");
	अगर (s & ENSELDI)
		seq_माला_दो(m, "ENSELDI ");
	अगर (s & ENSELINGO)
		seq_माला_दो(m, "ENSELINGO ");
	अगर (s & ENSWRAP)
		seq_माला_दो(m, "ENSWRAP ");
	अगर (s & ENSDONE)
		seq_माला_दो(m, "ENSDONE ");
	अगर (s & ENSPIORDY)
		seq_माला_दो(m, "ENSPIORDY ");
	अगर (s & ENDMADONE)
		seq_माला_दो(m, "ENDMADONE ");

	s = GETPORT(SIMODE1);
	अगर (s & ENSELTIMO)
		seq_माला_दो(m, "ENSELTIMO ");
	अगर (s & ENATNTARG)
		seq_माला_दो(m, "ENATNTARG ");
	अगर (s & ENPHASEMIS)
		seq_माला_दो(m, "ENPHASEMIS ");
	अगर (s & ENBUSFREE)
		seq_माला_दो(m, "ENBUSFREE ");
	अगर (s & ENSCSIPERR)
		seq_माला_दो(m, "ENSCSIPERR ");
	अगर (s & ENPHASECHG)
		seq_माला_दो(m, "ENPHASECHG ");
	अगर (s & ENREQINIT)
		seq_माला_दो(m, "ENREQINIT ");
	seq_माला_दो(m, ")\n");
पूर्ण

अटल पूर्णांक aha152x_set_info(काष्ठा Scsi_Host *shpnt, अक्षर *buffer, पूर्णांक length)
अणु
	अगर(!shpnt || !buffer || length<8 || म_भेदन("aha152x ", buffer, 8)!=0)
		वापस -EINVAL;

#अगर defined(AHA152X_STAT)
	अगर(length>13 && म_भेदन("reset", buffer+8, 5)==0) अणु
		पूर्णांक i;

		HOSTDATA(shpnt)->total_commands=0;
		HOSTDATA(shpnt)->disconnections=0;
		HOSTDATA(shpnt)->busमुक्त_without_any_action=0;
		HOSTDATA(shpnt)->busमुक्त_without_old_command=0;
		HOSTDATA(shpnt)->busमुक्त_without_new_command=0;
		HOSTDATA(shpnt)->busमुक्त_without_करोne_command=0;
		HOSTDATA(shpnt)->busमुक्त_with_check_condition=0;
		क्रम (i = idle; i<maxstate; i++) अणु
			HOSTDATA(shpnt)->count[i]=0;
			HOSTDATA(shpnt)->count_trans[i]=0;
			HOSTDATA(shpnt)->समय[i]=0;
		पूर्ण

		shost_prपूर्णांकk(KERN_INFO, shpnt, "aha152x: stats reset.\n");

	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		वापस -EINVAL;
	पूर्ण


	वापस length;
पूर्ण

अटल पूर्णांक aha152x_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shpnt)
अणु
	पूर्णांक i;
	काष्ठा scsi_cmnd *ptr;
	अचिन्हित दीर्घ flags;

	seq_माला_दो(m, AHA152X_REVID "\n");

	seq_म_लिखो(m, "ioports 0x%04lx to 0x%04lx\n",
		shpnt->io_port, shpnt->io_port + shpnt->n_io_port - 1);
	seq_म_लिखो(m, "interrupt 0x%02x\n", shpnt->irq);
	seq_म_लिखो(m, "disconnection/reconnection %s\n",
		RECONNECT ? "enabled" : "disabled");
	seq_म_लिखो(m, "parity checking %s\n",
		PARITY ? "enabled" : "disabled");
	seq_म_लिखो(m, "synchronous transfers %s\n",
		SYNCHRONOUS ? "enabled" : "disabled");
	seq_म_लिखो(m, "%d commands currently queued\n", HOSTDATA(shpnt)->commands);

	अगर(SYNCHRONOUS) अणु
		seq_माला_दो(m, "synchronously operating targets (tick=50 ns):\n");
		क्रम (i = 0; i < 8; i++)
			अगर (HOSTDATA(shpnt)->syncrate[i] & 0x7f)
				seq_म_लिखो(m, "target %d: period %dT/%dns; req/ack offset %d\n",
					i,
					(((HOSTDATA(shpnt)->syncrate[i] & 0x70) >> 4) + 2),
					(((HOSTDATA(shpnt)->syncrate[i] & 0x70) >> 4) + 2) * 50,
				    HOSTDATA(shpnt)->syncrate[i] & 0x0f);
	पूर्ण
	seq_माला_दो(m, "\nqueue status:\n");
	DO_LOCK(flags);
	अगर (ISSUE_SC) अणु
		seq_माला_दो(m, "not yet issued commands:\n");
		क्रम (ptr = ISSUE_SC; ptr; ptr = SCNEXT(ptr))
			get_command(m, ptr);
	पूर्ण अन्यथा
		seq_माला_दो(m, "no not yet issued commands\n");
	DO_UNLOCK(flags);

	अगर (CURRENT_SC) अणु
		seq_माला_दो(m, "current command:\n");
		get_command(m, CURRENT_SC);
	पूर्ण अन्यथा
		seq_माला_दो(m, "no current command\n");

	अगर (DISCONNECTED_SC) अणु
		seq_माला_दो(m, "disconnected commands:\n");
		क्रम (ptr = DISCONNECTED_SC; ptr; ptr = SCNEXT(ptr))
			get_command(m, ptr);
	पूर्ण अन्यथा
		seq_माला_दो(m, "no disconnected commands\n");

	get_ports(m, shpnt);

#अगर defined(AHA152X_STAT)
	seq_म_लिखो(m, "statistics:\n"
		"total commands:               %d\n"
		"disconnections:               %d\n"
		"busfree with check condition: %d\n"
		"busfree without old command:  %d\n"
		"busfree without new command:  %d\n"
		"busfree without done command: %d\n"
		"busfree without any action:   %d\n"
		"state      "
		"transitions  "
		"count        "
		"time\n",
		HOSTDATA(shpnt)->total_commands,
		HOSTDATA(shpnt)->disconnections,
		HOSTDATA(shpnt)->busमुक्त_with_check_condition,
		HOSTDATA(shpnt)->busमुक्त_without_old_command,
		HOSTDATA(shpnt)->busमुक्त_without_new_command,
		HOSTDATA(shpnt)->busमुक्त_without_करोne_command,
		HOSTDATA(shpnt)->busमुक्त_without_any_action);
	क्रम(i=0; i<maxstate; i++) अणु
		seq_म_लिखो(m, "%-10s %-12d %-12d %-12ld\n",
			states[i].name,
			HOSTDATA(shpnt)->count_trans[i],
			HOSTDATA(shpnt)->count[i],
			HOSTDATA(shpnt)->समय[i]);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक aha152x_adjust_queue(काष्ठा scsi_device *device)
अणु
	blk_queue_bounce_limit(device->request_queue, BLK_BOUNCE_HIGH);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा aha152x_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= AHA152X_REVID,
	.proc_name			= "aha152x",
	.show_info			= aha152x_show_info,
	.ग_लिखो_info			= aha152x_set_info,
	.queuecommand			= aha152x_queue,
	.eh_पात_handler		= aha152x_पात,
	.eh_device_reset_handler	= aha152x_device_reset,
	.eh_bus_reset_handler		= aha152x_bus_reset,
	.bios_param			= aha152x_biosparam,
	.can_queue			= 1,
	.this_id			= 7,
	.sg_tablesize			= SG_ALL,
	.dma_boundary			= PAGE_SIZE - 1,
	.slave_alloc			= aha152x_adjust_queue,
पूर्ण;

#अगर !defined(AHA152X_PCMCIA)
अटल पूर्णांक setup_count;
अटल काष्ठा aha152x_setup setup[2];

/* possible i/o addresses क्रम the AIC-6260; शेष first */
अटल अचिन्हित लघु ports[] = अणु 0x340, 0x140 पूर्ण;

#अगर !defined(SKIP_BIOSTEST)
/* possible locations क्रम the Adaptec BIOS; शेषs first */
अटल अचिन्हित पूर्णांक addresses[] =
अणु
	0xdc000,		/* शेष first */
	0xc8000,
	0xcc000,
	0xd0000,
	0xd4000,
	0xd8000,
	0xe0000,
	0xeb800,		/* VTech Platinum SMP */
	0xf0000,
पूर्ण;

/* signatures क्रम various AIC-6[23]60 based controllers.
   The poपूर्णांक in detecting signatures is to aव्योम useless and maybe
   harmful probes on ports. I'm not sure that all listed boards pass
   स्वतः-configuration. For those which fail the BIOS signature is
   obsolete, because user पूर्णांकervention to supply the configuration is
   needed anyway.  May be an inक्रमmation whether or not the BIOS supports
   extended translation could be also useful here. */
अटल काष्ठा signature अणु
	अचिन्हित अक्षर *signature;
	पूर्णांक sig_offset;
	पूर्णांक sig_length;
पूर्ण signatures[] =
अणु
	अणु "Adaptec AHA-1520 BIOS",	0x102e, 21 पूर्ण,
		/* Adaptec 152x */
	अणु "Adaptec AHA-1520B",		0x000b, 17 पूर्ण,
		/* Adaptec 152x rev B */
	अणु "Adaptec AHA-1520B",		0x0026, 17 पूर्ण,
		/* Iomega Jaz Jet ISA (AIC6370Q) */
	अणु "Adaptec ASW-B626 BIOS",	0x1029, 21 पूर्ण,
		/* on-board controller */
	अणु "Adaptec BIOS: ASW-B626",	0x000f, 22 पूर्ण,
		/* on-board controller */
	अणु "Adaptec ASW-B626 S2",	0x2e6c, 19 पूर्ण,
		/* on-board controller */
	अणु "Adaptec BIOS:AIC-6360",	0x000c, 21 पूर्ण,
		/* on-board controller */
	अणु "ScsiPro SP-360 BIOS",	0x2873, 19 पूर्ण,
		/* ScsiPro-Controller  */
	अणु "GA-400 LOCAL BUS SCSI BIOS", 0x102e, 26 पूर्ण,
		/* Gigabyte Local-Bus-SCSI */
	अणु "Adaptec BIOS:AVA-282X",	0x000c, 21 पूर्ण,
		/* Adaptec 282x */
	अणु "Adaptec IBM Dock II SCSI",   0x2edd, 24 पूर्ण,
		/* IBM Thinkpad Dock II */
	अणु "Adaptec BIOS:AHA-1532P",     0x001c, 22 पूर्ण,
		/* IBM Thinkpad Dock II SCSI */
	अणु "DTC3520A Host Adapter BIOS", 0x318a, 26 पूर्ण,
		/* DTC 3520A ISA SCSI */
पूर्ण;
#पूर्ण_अगर /* !SKIP_BIOSTEST */

/*
 * Test, अगर port_base is valid.
 *
 */
अटल पूर्णांक aha152x_porttest(पूर्णांक io_port)
अणु
	पूर्णांक i;

	SETPORT(io_port + O_DMACNTRL1, 0);	/* reset stack poपूर्णांकer */
	क्रम (i = 0; i < 16; i++)
		SETPORT(io_port + O_STACK, i);

	SETPORT(io_port + O_DMACNTRL1, 0);	/* reset stack poपूर्णांकer */
	क्रम (i = 0; i < 16 && GETPORT(io_port + O_STACK) == i; i++)
		;

	वापस (i == 16);
पूर्ण

अटल पूर्णांक tc1550_porttest(पूर्णांक io_port)
अणु
	पूर्णांक i;

	SETPORT(io_port + O_TC_DMACNTRL1, 0);	/* reset stack poपूर्णांकer */
	क्रम (i = 0; i < 16; i++)
		SETPORT(io_port + O_STACK, i);

	SETPORT(io_port + O_TC_DMACNTRL1, 0);	/* reset stack poपूर्णांकer */
	क्रम (i = 0; i < 16 && GETPORT(io_port + O_TC_STACK) == i; i++)
		;

	वापस (i == 16);
पूर्ण


अटल पूर्णांक checksetup(काष्ठा aha152x_setup *setup)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(ports) && (setup->io_port != ports[i]); i++)
		;

	अगर (i == ARRAY_SIZE(ports))
		वापस 0;

	अगर (!request_region(setup->io_port, IO_RANGE, "aha152x")) अणु
		prपूर्णांकk(KERN_ERR "aha152x: io port 0x%x busy.\n", setup->io_port);
		वापस 0;
	पूर्ण

	अगर( aha152x_porttest(setup->io_port) ) अणु
		setup->tc1550=0;
	पूर्ण अन्यथा अगर( tc1550_porttest(setup->io_port) ) अणु
		setup->tc1550=1;
	पूर्ण अन्यथा अणु
		release_region(setup->io_port, IO_RANGE);
		वापस 0;
	पूर्ण

	release_region(setup->io_port, IO_RANGE);

	अगर ((setup->irq < IRQ_MIN) || (setup->irq > IRQ_MAX))
		वापस 0;

	अगर ((setup->scsiid < 0) || (setup->scsiid > 7))
		वापस 0;

	अगर ((setup->reconnect < 0) || (setup->reconnect > 1))
		वापस 0;

	अगर ((setup->parity < 0) || (setup->parity > 1))
		वापस 0;

	अगर ((setup->synchronous < 0) || (setup->synchronous > 1))
		वापस 0;

	अगर ((setup->ext_trans < 0) || (setup->ext_trans > 1))
		वापस 0;


	वापस 1;
पूर्ण


अटल पूर्णांक __init aha152x_init(व्योम)
अणु
	पूर्णांक i, j, ok;
#अगर defined(AUTOCONF)
	aha152x_config conf;
#पूर्ण_अगर
#अगर_घोषित __ISAPNP__
	काष्ठा pnp_dev *dev=शून्य, *pnpdev[2] = अणुशून्य, शून्यपूर्ण;
#पूर्ण_अगर

	अगर ( setup_count ) अणु
		prपूर्णांकk(KERN_INFO "aha152x: processing commandline: ");

		क्रम (i = 0; i<setup_count; i++) अणु
			अगर (!checksetup(&setup[i])) अणु
				prपूर्णांकk(KERN_ERR "\naha152x: %s\n", setup[i].conf);
				prपूर्णांकk(KERN_ERR "aha152x: invalid line\n");
			पूर्ण
		पूर्ण
		prपूर्णांकk("ok\n");
	पूर्ण

#अगर defined(SETUP0)
	अगर (setup_count < ARRAY_SIZE(setup)) अणु
		काष्ठा aha152x_setup override = SETUP0;

		अगर (setup_count == 0 || (override.io_port != setup[0].io_port)) अणु
			अगर (!checksetup(&override)) अणु
				prपूर्णांकk(KERN_ERR "\naha152x: invalid override SETUP0={0x%x,%d,%d,%d,%d,%d,%d,%d}\n",
				       override.io_port,
				       override.irq,
				       override.scsiid,
				       override.reconnect,
				       override.parity,
				       override.synchronous,
				       override.delay,
				       override.ext_trans);
			पूर्ण अन्यथा
				setup[setup_count++] = override;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर defined(SETUP1)
	अगर (setup_count < ARRAY_SIZE(setup)) अणु
		काष्ठा aha152x_setup override = SETUP1;

		अगर (setup_count == 0 || (override.io_port != setup[0].io_port)) अणु
			अगर (!checksetup(&override)) अणु
				prपूर्णांकk(KERN_ERR "\naha152x: invalid override SETUP1={0x%x,%d,%d,%d,%d,%d,%d,%d}\n",
				       override.io_port,
				       override.irq,
				       override.scsiid,
				       override.reconnect,
				       override.parity,
				       override.synchronous,
				       override.delay,
				       override.ext_trans);
			पूर्ण अन्यथा
				setup[setup_count++] = override;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर defined(MODULE)
	अगर (setup_count<ARRAY_SIZE(setup) && (aha152x[0]!=0 || io[0]!=0 || irq[0]!=0)) अणु
		अगर(aha152x[0]!=0) अणु
			setup[setup_count].conf        = "";
			setup[setup_count].io_port     = aha152x[0];
			setup[setup_count].irq         = aha152x[1];
			setup[setup_count].scsiid      = aha152x[2];
			setup[setup_count].reconnect   = aha152x[3];
			setup[setup_count].parity      = aha152x[4];
			setup[setup_count].synchronous = aha152x[5];
			setup[setup_count].delay       = aha152x[6];
			setup[setup_count].ext_trans   = aha152x[7];
		पूर्ण अन्यथा अगर (io[0] != 0 || irq[0] != 0) अणु
			अगर(io[0]!=0)  setup[setup_count].io_port = io[0];
			अगर(irq[0]!=0) setup[setup_count].irq     = irq[0];

			setup[setup_count].scsiid      = scsiid[0];
			setup[setup_count].reconnect   = reconnect[0];
			setup[setup_count].parity      = parity[0];
			setup[setup_count].synchronous = sync[0];
			setup[setup_count].delay       = delay[0];
			setup[setup_count].ext_trans   = exttrans[0];
		पूर्ण

		अगर (checksetup(&setup[setup_count]))
			setup_count++;
		अन्यथा
			prपूर्णांकk(KERN_ERR "aha152x: invalid module params io=0x%x, irq=%d,scsiid=%d,reconnect=%d,parity=%d,sync=%d,delay=%d,exttrans=%d\n",
			       setup[setup_count].io_port,
			       setup[setup_count].irq,
			       setup[setup_count].scsiid,
			       setup[setup_count].reconnect,
			       setup[setup_count].parity,
			       setup[setup_count].synchronous,
			       setup[setup_count].delay,
			       setup[setup_count].ext_trans);
	पूर्ण

	अगर (setup_count<ARRAY_SIZE(setup) && (aha152x1[0]!=0 || io[1]!=0 || irq[1]!=0)) अणु
		अगर(aha152x1[0]!=0) अणु
			setup[setup_count].conf        = "";
			setup[setup_count].io_port     = aha152x1[0];
			setup[setup_count].irq         = aha152x1[1];
			setup[setup_count].scsiid      = aha152x1[2];
			setup[setup_count].reconnect   = aha152x1[3];
			setup[setup_count].parity      = aha152x1[4];
			setup[setup_count].synchronous = aha152x1[5];
			setup[setup_count].delay       = aha152x1[6];
			setup[setup_count].ext_trans   = aha152x1[7];
		पूर्ण अन्यथा अगर (io[1] != 0 || irq[1] != 0) अणु
			अगर(io[1]!=0)  setup[setup_count].io_port = io[1];
			अगर(irq[1]!=0) setup[setup_count].irq     = irq[1];

			setup[setup_count].scsiid      = scsiid[1];
			setup[setup_count].reconnect   = reconnect[1];
			setup[setup_count].parity      = parity[1];
			setup[setup_count].synchronous = sync[1];
			setup[setup_count].delay       = delay[1];
			setup[setup_count].ext_trans   = exttrans[1];
		पूर्ण
		अगर (checksetup(&setup[setup_count]))
			setup_count++;
		अन्यथा
			prपूर्णांकk(KERN_ERR "aha152x: invalid module params io=0x%x, irq=%d,scsiid=%d,reconnect=%d,parity=%d,sync=%d,delay=%d,exttrans=%d\n",
			       setup[setup_count].io_port,
			       setup[setup_count].irq,
			       setup[setup_count].scsiid,
			       setup[setup_count].reconnect,
			       setup[setup_count].parity,
			       setup[setup_count].synchronous,
			       setup[setup_count].delay,
			       setup[setup_count].ext_trans);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ISAPNP__
	क्रम(i=0; setup_count<ARRAY_SIZE(setup) && id_table[i].venकरोr; i++) अणु
		जबतक ( setup_count<ARRAY_SIZE(setup) &&
			(dev=pnp_find_dev(शून्य, id_table[i].venकरोr, id_table[i].function, dev)) ) अणु
			अगर (pnp_device_attach(dev) < 0)
				जारी;

			अगर (pnp_activate_dev(dev) < 0) अणु
				pnp_device_detach(dev);
				जारी;
			पूर्ण

			अगर (!pnp_port_valid(dev, 0)) अणु
				pnp_device_detach(dev);
				जारी;
			पूर्ण

			अगर (setup_count==1 && pnp_port_start(dev, 0)==setup[0].io_port) अणु
				pnp_device_detach(dev);
				जारी;
			पूर्ण

			setup[setup_count].io_port     = pnp_port_start(dev, 0);
			setup[setup_count].irq         = pnp_irq(dev, 0);
			setup[setup_count].scsiid      = 7;
			setup[setup_count].reconnect   = 1;
			setup[setup_count].parity      = 1;
			setup[setup_count].synchronous = 1;
			setup[setup_count].delay       = DELAY_DEFAULT;
			setup[setup_count].ext_trans   = 0;
#अगर defined(__ISAPNP__)
			pnpdev[setup_count]            = dev;
#पूर्ण_अगर
			prपूर्णांकk (KERN_INFO
				"aha152x: found ISAPnP adapter at io=0x%03x, irq=%d\n",
				setup[setup_count].io_port, setup[setup_count].irq);
			setup_count++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर defined(AUTOCONF)
	अगर (setup_count<ARRAY_SIZE(setup)) अणु
#अगर !defined(SKIP_BIOSTEST)
		ok = 0;
		क्रम (i = 0; i < ARRAY_SIZE(addresses) && !ok; i++) अणु
			व्योम __iomem *p = ioremap(addresses[i], 0x4000);
			अगर (!p)
				जारी;
			क्रम (j = 0; j<ARRAY_SIZE(signatures) && !ok; j++)
				ok = check_signature(p + signatures[j].sig_offset,
								signatures[j].signature, signatures[j].sig_length);
			iounmap(p);
		पूर्ण
		अगर (!ok && setup_count == 0)
			वापस -ENODEV;

		prपूर्णांकk(KERN_INFO "aha152x: BIOS test: passed, ");
#अन्यथा
		prपूर्णांकk(KERN_INFO "aha152x: ");
#पूर्ण_अगर				/* !SKIP_BIOSTEST */

		ok = 0;
		क्रम (i = 0; i < ARRAY_SIZE(ports) && setup_count < 2; i++) अणु
			अगर ((setup_count == 1) && (setup[0].io_port == ports[i]))
				जारी;

			अगर (!request_region(ports[i], IO_RANGE, "aha152x")) अणु
				prपूर्णांकk(KERN_ERR "aha152x: io port 0x%x busy.\n", ports[i]);
				जारी;
			पूर्ण

			अगर (aha152x_porttest(ports[i])) अणु
				setup[setup_count].tc1550  = 0;

				conf.cf_port =
				    (GETPORT(ports[i] + O_PORTA) << 8) + GETPORT(ports[i] + O_PORTB);
			पूर्ण अन्यथा अगर (tc1550_porttest(ports[i])) अणु
				setup[setup_count].tc1550  = 1;

				conf.cf_port =
				    (GETPORT(ports[i] + O_TC_PORTA) << 8) + GETPORT(ports[i] + O_TC_PORTB);
			पूर्ण अन्यथा अणु
				release_region(ports[i], IO_RANGE);
				जारी;
			पूर्ण

			release_region(ports[i], IO_RANGE);

			ok++;
			setup[setup_count].io_port = ports[i];
			setup[setup_count].irq = IRQ_MIN + conf.cf_irq;
			setup[setup_count].scsiid = conf.cf_id;
			setup[setup_count].reconnect = conf.cf_tardisc;
			setup[setup_count].parity = !conf.cf_parity;
			setup[setup_count].synchronous = conf.cf_syncneg;
			setup[setup_count].delay = DELAY_DEFAULT;
			setup[setup_count].ext_trans = 0;
			setup_count++;

		पूर्ण

		अगर (ok)
			prपूर्णांकk("auto configuration: ok, ");
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk("%d controller(s) configured\n", setup_count);

	क्रम (i=0; i<setup_count; i++) अणु
		अगर ( request_region(setup[i].io_port, IO_RANGE, "aha152x") ) अणु
			काष्ठा Scsi_Host *shpnt = aha152x_probe_one(&setup[i]);

			अगर( !shpnt ) अणु
				release_region(setup[i].io_port, IO_RANGE);
#अगर defined(__ISAPNP__)
			पूर्ण अन्यथा अगर( pnpdev[i] ) अणु
				HOSTDATA(shpnt)->pnpdev=pnpdev[i];
				pnpdev[i]=शून्य;
#पूर्ण_अगर
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "aha152x: io port 0x%x busy.\n", setup[i].io_port);
		पूर्ण

#अगर defined(__ISAPNP__)
		अगर( pnpdev[i] )
			pnp_device_detach(pnpdev[i]);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास aha152x_निकास(व्योम)
अणु
	काष्ठा aha152x_hostdata *hd, *पंचांगp;

	list_क्रम_each_entry_safe(hd, पंचांगp, &aha152x_host_list, host_list) अणु
		काष्ठा Scsi_Host *shost = container_of((व्योम *)hd, काष्ठा Scsi_Host, hostdata);

		aha152x_release(shost);
	पूर्ण
पूर्ण

module_init(aha152x_init);
module_निकास(aha152x_निकास);

#अगर !defined(MODULE)
अटल पूर्णांक __init aha152x_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[10];

	get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर(setup_count>=ARRAY_SIZE(setup)) अणु
		prपूर्णांकk(KERN_ERR "aha152x: you can only configure up to two controllers\n");
		वापस 1;
	पूर्ण

	setup[setup_count].conf        = str;
	setup[setup_count].io_port     = पूर्णांकs[0] >= 1 ? पूर्णांकs[1] : 0x340;
	setup[setup_count].irq         = पूर्णांकs[0] >= 2 ? पूर्णांकs[2] : 11;
	setup[setup_count].scsiid      = पूर्णांकs[0] >= 3 ? पूर्णांकs[3] : 7;
	setup[setup_count].reconnect   = पूर्णांकs[0] >= 4 ? पूर्णांकs[4] : 1;
	setup[setup_count].parity      = पूर्णांकs[0] >= 5 ? पूर्णांकs[5] : 1;
	setup[setup_count].synchronous = पूर्णांकs[0] >= 6 ? पूर्णांकs[6] : 1;
	setup[setup_count].delay       = पूर्णांकs[0] >= 7 ? पूर्णांकs[7] : DELAY_DEFAULT;
	setup[setup_count].ext_trans   = पूर्णांकs[0] >= 8 ? पूर्णांकs[8] : 0;
	अगर (पूर्णांकs[0] > 8) अणु                                                /*पूर्ण*/
		prपूर्णांकk(KERN_NOTICE "aha152x: usage: aha152x=<IOBASE>[,<IRQ>[,<SCSI ID>"
		       "[,<RECONNECT>[,<PARITY>[,<SYNCHRONOUS>[,<DELAY>[,<EXT_TRANS>]]]]]]]\n");
	पूर्ण अन्यथा अणु
		setup_count++;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
__setup("aha152x=", aha152x_setup);
#पूर्ण_अगर

#पूर्ण_अगर /* !AHA152X_PCMCIA */
