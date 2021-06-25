<शैली गुरु>

/*
 * Adaptec AIC7xxx device driver क्रम Linux.
 *
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7xxx_osm.c#235 $
 *
 * Copyright (c) 1994 John Aycock
 *   The University of Calgary Deparपंचांगent of Computer Science.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Sources include the Adaptec 1740 driver (aha1740.c), the Ultrastor 24F
 * driver (ultrastor.c), various Linux kernel source, the Adaptec EISA
 * config file (!adp7771.cfg), the Adaptec AHA-2740A Series User's Guide,
 * the Linux Kernel Hacker's Guide, Writing a SCSI Device Driver क्रम Linux,
 * the Adaptec 1542 driver (aha1542.c), the Adaptec EISA overlay file
 * (adp7770.ovl), the Adaptec AHA-2740 Series Technical Reference Manual,
 * the Adaptec AIC-7770 Data Book, the ANSI SCSI specअगरication, the
 * ANSI SCSI-2 specअगरication (draft 10c), ...
 *
 * --------------------------------------------------------------------------
 *
 *  Modअगरications by Daniel M. Eischen (deischen@iworks.InterWorks.org):
 *
 *  Substantially modअगरied to include support क्रम wide and twin bus
 *  adapters, DMAing of SCBs, tagged queueing, IRQ sharing, bug fixes,
 *  SCB paging, and other rework of the code.
 *
 * --------------------------------------------------------------------------
 * Copyright (c) 1994-2000 Justin T. Gibbs.
 * Copyright (c) 2000-2001 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 *---------------------------------------------------------------------------
 *
 *  Thanks also go to (in alphabetical order) the following:
 *
 *    Rory Bolt     - Sequencer bug fixes
 *    Jay Estabrook - Initial DEC Alpha support
 *    Doug Ledक्रमd  - Much needed पात/reset bug fixes
 *    Kai Makisara  - DMAing of SCBs
 *
 *  A Boot समय option was also added क्रम not resetting the scsi bus.
 *
 *    Form:  aic7xxx=extended
 *           aic7xxx=no_reset
 *           aic7xxx=verbose
 *
 *  Daniel M. Eischen, deischen@iworks.InterWorks.org, 1/23/97
 *
 *  Id: aic7xxx.c,v 4.1 1997/06/12 08:23:42 deang Exp
 */

/*
 * Further driver modअगरications made by Doug Ledक्रमd <dledक्रमd@redhat.com>
 *
 * Copyright (c) 1997-1999 Doug Ledक्रमd
 *
 * These changes are released under the same licensing terms as the FreeBSD
 * driver written by Justin Gibbs.  Please see his Copyright notice above
 * क्रम the exact terms and conditions covering my changes as well as the
 * warranty statement.
 *
 * Modअगरications made to the aic7xxx.c,v 4.1 driver from Dan Eischen include
 * but are not limited to:
 *
 *  1: Import of the latest FreeBSD sequencer code क्रम this driver
 *  2: Modअगरication of kernel code to accommodate dअगरferent sequencer semantics
 *  3: Extensive changes throughout kernel portion of driver to improve
 *     पात/reset processing and error hanndling
 *  4: Other work contributed by various people on the Internet
 *  5: Changes to prपूर्णांकk inक्रमmation and verbosity selection code
 *  6: General reliability related changes, especially in IRQ management
 *  7: Modअगरications to the शेष probe/attach order क्रम supported cards
 *  8: SMP मित्रliness has been improved
 *
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_inline.h"
#समावेश <scsi/scsicam.h>

अटल काष्ठा scsi_transport_ढाँचा *ahc_linux_transport_ढाँचा = शून्य;

#समावेश <linux/init.h>		/* __setup */
#समावेश <linux/mm.h>		/* For fetching प्रणाली memory size */
#समावेश <linux/blkdev.h>		/* For block_size() */
#समावेश <linux/delay.h>	/* For ssleep/msleep */
#समावेश <linux/slab.h>


/*
 * Set this to the delay in seconds after SCSI bus reset.
 * Note, we honor this only क्रम the initial bus reset.
 * The scsi error recovery code perक्रमms its own bus settle
 * delay handling क्रम error recovery actions.
 */
#अगर_घोषित CONFIG_AIC7XXX_RESET_DELAY_MS
#घोषणा AIC7XXX_RESET_DELAY CONFIG_AIC7XXX_RESET_DELAY_MS
#अन्यथा
#घोषणा AIC7XXX_RESET_DELAY 5000
#पूर्ण_अगर

/*
 * To change the शेष number of tagged transactions allowed per-device,
 * add a line to the lilo.conf file like:
 * append="aic7xxx=verbose,tag_info:{{32,32,32,32},{32,32,32,32}}"
 * which will result in the first four devices on the first two
 * controllers being set to a tagged queue depth of 32.
 *
 * The tag_commands is an array of 16 to allow क्रम wide and twin adapters.
 * Twin adapters will use indexes 0-7 क्रम channel 0, and indexes 8-15
 * क्रम channel 1.
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t tag_commands[16];	/* Allow क्रम wide/twin adapters. */
पूर्ण adapter_tag_info_t;

/*
 * Modअगरy this as you see fit क्रम your प्रणाली.
 *
 * 0			tagged queuing disabled
 * 1 <= n <= 253	n == max tags ever dispatched.
 *
 * The driver will throttle the number of commands dispatched to a
 * device अगर it वापसs queue full.  For devices with a fixed maximum
 * queue depth, the driver will eventually determine this depth and
 * lock it in (a console message is prपूर्णांकed to indicate that a lock
 * has occurred).  On some devices, queue full is वापसed क्रम a temporary
 * resource लघुage.  These devices will वापस queue full at varying
 * depths.  The driver will throttle back when the queue fulls occur and
 * attempt to slowly increase the depth over समय as the device recovers
 * from the resource लघुage.
 *
 * In this example, the first line will disable tagged queueing क्रम all
 * the devices on the first probed aic7xxx adapter.
 *
 * The second line enables tagged queueing with 4 commands/LUN क्रम IDs
 * (0, 2-11, 13-15), disables tagged queueing क्रम ID 12, and tells the
 * driver to attempt to use up to 64 tags क्रम ID 1.
 *
 * The third line is the same as the first line.
 *
 * The fourth line disables tagged queueing क्रम devices 0 and 3.  It
 * enables tagged queueing क्रम the other IDs, with 16 commands/LUN
 * क्रम IDs 1 and 4, 127 commands/LUN क्रम ID 8, and 4 commands/LUN क्रम
 * IDs 2, 5-7, and 9-15.
 */

/*
 * NOTE: The below काष्ठाure is क्रम reference only, the actual काष्ठाure
 *       to modअगरy in order to change things is just below this comment block.
adapter_tag_info_t aic7xxx_tag_info[] =
अणु
	अणुअणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण,
	अणुअणु4, 64, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4पूर्णपूर्ण,
	अणुअणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण,
	अणुअणु0, 16, 4, 0, 16, 4, 4, 4, 127, 4, 4, 4, 4, 4, 4, 4पूर्णपूर्ण
पूर्ण;
*/

#अगर_घोषित CONFIG_AIC7XXX_CMDS_PER_DEVICE
#घोषणा AIC7XXX_CMDS_PER_DEVICE CONFIG_AIC7XXX_CMDS_PER_DEVICE
#अन्यथा
#घोषणा AIC7XXX_CMDS_PER_DEVICE AHC_MAX_QUEUE
#पूर्ण_अगर

#घोषणा AIC7XXX_CONFIGED_TAG_COMMANDS अणु					\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE,		\
	AIC7XXX_CMDS_PER_DEVICE, AIC7XXX_CMDS_PER_DEVICE		\
पूर्ण

/*
 * By शेष, use the number of commands specअगरied by
 * the users kernel configuration.
 */
अटल adapter_tag_info_t aic7xxx_tag_info[] =
अणु
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC7XXX_CONFIGED_TAG_COMMANDSपूर्ण
पूर्ण;

/*
 * There should be a specअगरic वापस value क्रम this in scsi.h, but
 * it seems that most drivers ignore it.
 */
#घोषणा DID_UNDERFLOW   DID_ERROR

व्योम
ahc_prपूर्णांक_path(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	prपूर्णांकk("(scsi%d:%c:%d:%d): ",
	       ahc->platक्रमm_data->host->host_no,
	       scb != शून्य ? SCB_GET_CHANNEL(ahc, scb) : 'X',
	       scb != शून्य ? SCB_GET_TARGET(ahc, scb) : -1,
	       scb != शून्य ? SCB_GET_LUN(scb) : -1);
पूर्ण

/*
 * XXX - these options apply unilaterally to _all_ 274x/284x/294x
 *       cards in the प्रणाली.  This should be fixed.  Exceptions to this
 *       rule are noted in the comments.
 */

/*
 * Skip the scsi bus reset.  Non 0 make us skip the reset at startup.  This
 * has no effect on any later resets that might occur due to things like
 * SCSI bus समयouts.
 */
अटल uपूर्णांक32_t aic7xxx_no_reset;

/*
 * Should we क्रमce EXTENDED translation on a controller.
 *     0 == Use whatever is in the SEEPROM or शेष to off
 *     1 == Use whatever is in the SEEPROM or शेष to on
 */
अटल uपूर्णांक32_t aic7xxx_extended;

/*
 * PCI bus parity checking of the Adaptec controllers.  This is somewhat
 * dubious at best.  To my knowledge, this option has never actually
 * solved a PCI parity problem, but on certain machines with broken PCI
 * chipset configurations where stray PCI transactions with bad parity are
 * the norm rather than the exception, the error messages can be overwhelming.
 * It's included in the driver क्रम completeness.
 *   0	   = Shut off PCI parity check
 *   non-0 = reverse polarity pci parity checking
 */
अटल uपूर्णांक32_t aic7xxx_pci_parity = ~0;

/*
 * There are lots of broken chipsets in the world.  Some of them will
 * violate the PCI spec when we issue byte sized memory ग_लिखोs to our
 * controller.  I/O mapped रेजिस्टर access, अगर allowed by the given
 * platक्रमm, will work in almost all हालs.
 */
uपूर्णांक32_t aic7xxx_allow_memio = ~0;

/*
 * So that we can set how दीर्घ each device is given as a selection समयout.
 * The table of values goes like this:
 *   0 - 256ms
 *   1 - 128ms
 *   2 - 64ms
 *   3 - 32ms
 * We शेष to 256ms because some older devices need a दीर्घer समय
 * to respond to initial selection.
 */
अटल uपूर्णांक32_t aic7xxx_selसमय;

/*
 * Certain devices करो not perक्रमm any aging on commands.  Should the
 * device be saturated by commands in one portion of the disk, it is
 * possible क्रम transactions on far away sectors to never be serviced.
 * To handle these devices, we can periodically send an ordered tag to
 * क्रमce all outstanding transactions to be serviced prior to a new
 * transaction.
 */
अटल uपूर्णांक32_t aic7xxx_periodic_otag;

/*
 * Module inक्रमmation and settable options.
 */
अटल अक्षर *aic7xxx = शून्य;

MODULE_AUTHOR("Maintainer: Hannes Reinecke <hare@suse.de>");
MODULE_DESCRIPTION("Adaptec AIC77XX/78XX SCSI Host Bus Adapter driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(AIC7XXX_DRIVER_VERSION);
module_param(aic7xxx, अक्षरp, 0444);
MODULE_PARM_DESC(aic7xxx,
"period-delimited options string:\n"
"	verbose			Enable verbose/diagnostic logging\n"
"	allow_memio		Allow device registers to be memory mapped\n"
"	debug			Bitmask of debug values to enable\n"
"	no_probe		Toggle EISA/VLB controller probing\n"
"	probe_eisa_vl		Toggle EISA/VLB controller probing\n"
"	no_reset		Suppress initial bus resets\n"
"	extended		Enable extended geometry on all controllers\n"
"	periodic_otag		Send an ordered tagged transaction\n"
"				periodically to prevent tag starvation.\n"
"				This may be required by some older disk\n"
"				drives or RAID arrays.\n"
"	tag_info:<tag_str>	Set per-target tag depth\n"
"	global_tag_depth:<int>	Global tag depth for every target\n"
"				on every bus\n"
"	seltime:<int>		Selection Timeout\n"
"				(0/256ms,1/128ms,2/64ms,3/32ms)\n"
"\n"
"	Sample modprobe configuration file:\n"
"	#	Toggle EISA/VLB probing\n"
"	#	Set tag depth on Controller 1/Target 1 to 10 tags\n"
"	#	Shorten the selection timeout to 128ms\n"
"\n"
"	options aic7xxx 'aic7xxx=probe_eisa_vl.tag_info:{{}.{.10}}.seltime:1'\n"
);

अटल व्योम ahc_linux_handle_scsi_status(काष्ठा ahc_softc *,
					 काष्ठा scsi_device *,
					 काष्ठा scb *);
अटल व्योम ahc_linux_queue_cmd_complete(काष्ठा ahc_softc *ahc,
					 काष्ठा scsi_cmnd *cmd);
अटल व्योम ahc_linux_मुक्तze_simq(काष्ठा ahc_softc *ahc);
अटल व्योम ahc_linux_release_simq(काष्ठा ahc_softc *ahc);
अटल पूर्णांक  ahc_linux_queue_recovery_cmd(काष्ठा scsi_cmnd *cmd, scb_flag flag);
अटल व्योम ahc_linux_initialize_scsi_bus(काष्ठा ahc_softc *ahc);
अटल u_पूर्णांक ahc_linux_user_tagdepth(काष्ठा ahc_softc *ahc,
				     काष्ठा ahc_devinfo *devinfo);
अटल व्योम ahc_linux_device_queue_depth(काष्ठा scsi_device *);
अटल पूर्णांक ahc_linux_run_command(काष्ठा ahc_softc*,
				 काष्ठा ahc_linux_device *,
				 काष्ठा scsi_cmnd *);
अटल व्योम ahc_linux_setup_tag_info_global(अक्षर *p);
अटल पूर्णांक  aic7xxx_setup(अक्षर *s);

अटल पूर्णांक ahc_linux_unit;


/************************** OS Utility Wrappers *******************************/
व्योम
ahc_delay(दीर्घ usec)
अणु
	/*
	 * udelay on Linux can have problems क्रम
	 * multi-millisecond रुकोs.  Wait at most
	 * 1024us per call.
	 */
	जबतक (usec > 0) अणु
		udelay(usec % 1024);
		usec -= 1024;
	पूर्ण
पूर्ण

/***************************** Low Level I/O **********************************/
uपूर्णांक8_t
ahc_inb(काष्ठा ahc_softc * ahc, दीर्घ port)
अणु
	uपूर्णांक8_t x;

	अगर (ahc->tag == BUS_SPACE_MEMIO) अणु
		x = पढ़ोb(ahc->bsh.maddr + port);
	पूर्ण अन्यथा अणु
		x = inb(ahc->bsh.ioport + port);
	पूर्ण
	mb();
	वापस (x);
पूर्ण

व्योम
ahc_outb(काष्ठा ahc_softc * ahc, दीर्घ port, uपूर्णांक8_t val)
अणु
	अगर (ahc->tag == BUS_SPACE_MEMIO) अणु
		ग_लिखोb(val, ahc->bsh.maddr + port);
	पूर्ण अन्यथा अणु
		outb(val, ahc->bsh.ioport + port);
	पूर्ण
	mb();
पूर्ण

व्योम
ahc_outsb(काष्ठा ahc_softc * ahc, दीर्घ port, uपूर्णांक8_t *array, पूर्णांक count)
अणु
	पूर्णांक i;

	/*
	 * There is probably a more efficient way to करो this on Linux
	 * but we करोn't use this क्रम anything speed critical and this
	 * should work.
	 */
	क्रम (i = 0; i < count; i++)
		ahc_outb(ahc, port, *array++);
पूर्ण

व्योम
ahc_insb(काष्ठा ahc_softc * ahc, दीर्घ port, uपूर्णांक8_t *array, पूर्णांक count)
अणु
	पूर्णांक i;

	/*
	 * There is probably a more efficient way to करो this on Linux
	 * but we करोn't use this क्रम anything speed critical and this
	 * should work.
	 */
	क्रम (i = 0; i < count; i++)
		*array++ = ahc_inb(ahc, port);
पूर्ण

/********************************* Inlines ************************************/
अटल व्योम ahc_linux_unmap_scb(काष्ठा ahc_softc*, काष्ठा scb*);

अटल पूर्णांक ahc_linux_map_seg(काष्ठा ahc_softc *ahc, काष्ठा scb *scb,
				      काष्ठा ahc_dma_seg *sg,
				      dma_addr_t addr, bus_माप_प्रकार len);

अटल व्योम
ahc_linux_unmap_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा scsi_cmnd *cmd;

	cmd = scb->io_ctx;
	ahc_sync_sglist(ahc, scb, BUS_DMASYNC_POSTWRITE);

	scsi_dma_unmap(cmd);
पूर्ण

अटल पूर्णांक
ahc_linux_map_seg(काष्ठा ahc_softc *ahc, काष्ठा scb *scb,
		  काष्ठा ahc_dma_seg *sg, dma_addr_t addr, bus_माप_प्रकार len)
अणु
	पूर्णांक	 consumed;

	अगर ((scb->sg_count + 1) > AHC_NSEG)
		panic("Too few segs for dma mapping.  "
		      "Increase AHC_NSEG\n");

	consumed = 1;
	sg->addr = ahc_htole32(addr & 0xFFFFFFFF);
	scb->platक्रमm_data->xfer_len += len;

	अगर (माप(dma_addr_t) > 4
	 && (ahc->flags & AHC_39BIT_ADDRESSING) != 0)
		len |= (addr >> 8) & AHC_SG_HIGH_ADDR_MASK;

	sg->len = ahc_htole32(len);
	वापस (consumed);
पूर्ण

/*
 * Return a string describing the driver.
 */
अटल स्थिर अक्षर *
ahc_linux_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर buffer[512];
	अक्षर	ahc_info[256];
	अक्षर   *bp;
	काष्ठा ahc_softc *ahc;

	bp = &buffer[0];
	ahc = *(काष्ठा ahc_softc **)host->hostdata;
	स_रखो(bp, 0, माप(buffer));
	म_नकल(bp, "Adaptec AIC7XXX EISA/VLB/PCI SCSI HBA DRIVER, Rev " AIC7XXX_DRIVER_VERSION "\n"
			"        <");
	म_जोड़ो(bp, ahc->description);
	म_जोड़ो(bp, ">\n"
			"        ");
	ahc_controller_info(ahc, ahc_info);
	म_जोड़ो(bp, ahc_info);
	म_जोड़ो(bp, "\n");

	वापस (bp);
पूर्ण

/*
 * Queue an SCB to the controller.
 */
अटल पूर्णांक
ahc_linux_queue_lck(काष्ठा scsi_cmnd * cmd, व्योम (*scsi_करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा	 ahc_softc *ahc;
	काष्ठा	 ahc_linux_device *dev = scsi_transport_device_data(cmd->device);
	पूर्णांक rtn = SCSI_MLQUEUE_HOST_BUSY;
	अचिन्हित दीर्घ flags;

	ahc = *(काष्ठा ahc_softc **)cmd->device->host->hostdata;

	ahc_lock(ahc, &flags);
	अगर (ahc->platक्रमm_data->qfrozen == 0) अणु
		cmd->scsi_करोne = scsi_करोne;
		cmd->result = CAM_REQ_INPROG << 16;
		rtn = ahc_linux_run_command(ahc, dev, cmd);
	पूर्ण
	ahc_unlock(ahc, &flags);

	वापस rtn;
पूर्ण

अटल DEF_SCSI_QCMD(ahc_linux_queue)

अटल अंतरभूत काष्ठा scsi_target **
ahc_linux_target_in_softc(काष्ठा scsi_target *starget)
अणु
	काष्ठा	ahc_softc *ahc =
		*((काष्ठा ahc_softc **)dev_to_shost(&starget->dev)->hostdata);
	अचिन्हित पूर्णांक target_offset;

	target_offset = starget->id;
	अगर (starget->channel != 0)
		target_offset += 8;

	वापस &ahc->platक्रमm_data->starget[target_offset];
पूर्ण

अटल पूर्णांक
ahc_linux_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा	ahc_softc *ahc =
		*((काष्ठा ahc_softc **)dev_to_shost(&starget->dev)->hostdata);
	काष्ठा seeprom_config *sc = ahc->seep_config;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_target **ahc_targp = ahc_linux_target_in_softc(starget);
	अचिन्हित लघु scsirate;
	काष्ठा ahc_devinfo devinfo;
	अक्षर channel = starget->channel + 'A';
	अचिन्हित पूर्णांक our_id = ahc->our_id;
	अचिन्हित पूर्णांक target_offset;

	target_offset = starget->id;
	अगर (starget->channel != 0)
		target_offset += 8;

	अगर (starget->channel)
		our_id = ahc->our_id_b;

	ahc_lock(ahc, &flags);

	BUG_ON(*ahc_targp != शून्य);

	*ahc_targp = starget;

	अगर (sc) अणु
		पूर्णांक maxsync = AHC_SYNCRATE_DT;
		पूर्णांक ultra = 0;
		पूर्णांक flags = sc->device_flags[target_offset];

		अगर (ahc->flags & AHC_NEWEEPROM_FMT) अणु
		    अगर (flags & CFSYNCHISULTRA)
			ultra = 1;
		पूर्ण अन्यथा अगर (flags & CFULTRAEN)
			ultra = 1;
		/* AIC nutहाल; 10MHz appears as ultra = 1, CFXFER = 0x04
		 * change it to ultra=0, CFXFER = 0 */
		अगर(ultra && (flags & CFXFER) == 0x04) अणु
			ultra = 0;
			flags &= ~CFXFER;
		पूर्ण

		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			scsirate = (flags & CFXFER) | (ultra ? 0x8 : 0);
		पूर्ण अन्यथा अणु
			scsirate = (flags & CFXFER) << 4;
			maxsync = ultra ? AHC_SYNCRATE_ULTRA :
				AHC_SYNCRATE_FAST;
		पूर्ण
		spi_max_width(starget) = (flags & CFWIDEB) ? 1 : 0;
		अगर (!(flags & CFSYNCH))
			spi_max_offset(starget) = 0;
		spi_min_period(starget) =
			ahc_find_period(ahc, scsirate, maxsync);
	पूर्ण
	ahc_compile_devinfo(&devinfo, our_id, starget->id,
			    CAM_LUN_WILDCARD, channel,
			    ROLE_INITIATOR);
	ahc_set_syncrate(ahc, &devinfo, शून्य, 0, 0, 0,
			 AHC_TRANS_GOAL, /*छोड़ोd*/FALSE);
	ahc_set_width(ahc, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
		      AHC_TRANS_GOAL, /*छोड़ोd*/FALSE);
	ahc_unlock(ahc, &flags);

	वापस 0;
पूर्ण

अटल व्योम
ahc_linux_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा scsi_target **ahc_targp = ahc_linux_target_in_softc(starget);

	*ahc_targp = शून्य;
पूर्ण

अटल पूर्णांक
ahc_linux_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा	ahc_softc *ahc =
		*((काष्ठा ahc_softc **)sdev->host->hostdata);
	काष्ठा scsi_target *starget = sdev->sdev_target;
	काष्ठा ahc_linux_device *dev;

	अगर (bootverbose)
		prपूर्णांकk("%s: Slave Alloc %d\n", ahc_name(ahc), sdev->id);

	dev = scsi_transport_device_data(sdev);
	स_रखो(dev, 0, माप(*dev));

	/*
	 * We start out lअगरe using untagged
	 * transactions of which we allow one.
	 */
	dev->खोलोings = 1;

	/*
	 * Set maxtags to 0.  This will be changed अगर we
	 * later determine that we are dealing with
	 * a tagged queuing capable device.
	 */
	dev->maxtags = 0;

	spi_period(starget) = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
ahc_linux_slave_configure(काष्ठा scsi_device *sdev)
अणु
	अगर (bootverbose)
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Slave Configure\n");

	ahc_linux_device_queue_depth(sdev);

	/* Initial Doमुख्य Validation */
	अगर (!spi_initial_dv(sdev->sdev_target))
		spi_dv_device(sdev);

	वापस 0;
पूर्ण

#अगर defined(__i386__)
/*
 * Return the disk geometry क्रम the given SCSI device.
 */
अटल पूर्णांक
ahc_linux_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		    sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक	 heads;
	पूर्णांक	 sectors;
	पूर्णांक	 cylinders;
	पूर्णांक	 extended;
	काष्ठा	 ahc_softc *ahc;
	u_पूर्णांक	 channel;

	ahc = *((काष्ठा ahc_softc **)sdev->host->hostdata);
	channel = sdev_channel(sdev);

	अगर (scsi_partsize(bdev, capacity, geom))
		वापस 0;

	heads = 64;
	sectors = 32;
	cylinders = aic_sector_भाग(capacity, heads, sectors);

	अगर (aic7xxx_extended != 0)
		extended = 1;
	अन्यथा अगर (channel == 0)
		extended = (ahc->flags & AHC_EXTENDED_TRANS_A) != 0;
	अन्यथा
		extended = (ahc->flags & AHC_EXTENDED_TRANS_B) != 0;
	अगर (extended && cylinders >= 1024) अणु
		heads = 255;
		sectors = 63;
		cylinders = aic_sector_भाग(capacity, heads, sectors);
	पूर्ण
	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;
	वापस (0);
पूर्ण
#पूर्ण_अगर

/*
 * Abort the current SCSI command(s).
 */
अटल पूर्णांक
ahc_linux_पात(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक error;

	error = ahc_linux_queue_recovery_cmd(cmd, SCB_ABORT);
	अगर (error != SUCCESS)
		prपूर्णांकk("aic7xxx_abort returns 0x%x\n", error);
	वापस (error);
पूर्ण

/*
 * Attempt to send a target reset message to the device that समयd out.
 */
अटल पूर्णांक
ahc_linux_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक error;

	error = ahc_linux_queue_recovery_cmd(cmd, SCB_DEVICE_RESET);
	अगर (error != SUCCESS)
		prपूर्णांकk("aic7xxx_dev_reset returns 0x%x\n", error);
	वापस (error);
पूर्ण

/*
 * Reset the SCSI bus.
 */
अटल पूर्णांक
ahc_linux_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ahc_softc *ahc;
	पूर्णांक    found;
	अचिन्हित दीर्घ flags;

	ahc = *(काष्ठा ahc_softc **)cmd->device->host->hostdata;

	ahc_lock(ahc, &flags);
	found = ahc_reset_channel(ahc, scmd_channel(cmd) + 'A',
				  /*initiate reset*/TRUE);
	ahc_unlock(ahc, &flags);

	अगर (bootverbose)
		prपूर्णांकk("%s: SCSI bus reset delivered. "
		       "%d SCBs aborted.\n", ahc_name(ahc), found);

	वापस SUCCESS;
पूर्ण

काष्ठा scsi_host_ढाँचा aic7xxx_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "aic7xxx",
	.proc_name		= "aic7xxx",
	.show_info		= ahc_linux_show_info,
	.ग_लिखो_info		= ahc_proc_ग_लिखो_seeprom,
	.info			= ahc_linux_info,
	.queuecommand		= ahc_linux_queue,
	.eh_पात_handler	= ahc_linux_पात,
	.eh_device_reset_handler = ahc_linux_dev_reset,
	.eh_bus_reset_handler	= ahc_linux_bus_reset,
#अगर defined(__i386__)
	.bios_param		= ahc_linux_biosparam,
#पूर्ण_अगर
	.can_queue		= AHC_MAX_QUEUE,
	.this_id		= -1,
	.max_sectors		= 8192,
	.cmd_per_lun		= 2,
	.slave_alloc		= ahc_linux_slave_alloc,
	.slave_configure	= ahc_linux_slave_configure,
	.target_alloc		= ahc_linux_target_alloc,
	.target_destroy		= ahc_linux_target_destroy,
पूर्ण;

/**************************** Tasklet Handler *********************************/

/******************************** Macros **************************************/
#घोषणा BUILD_SCSIID(ahc, cmd)						    \
	((((cmd)->device->id << TID_SHIFT) & TID)			    \
	| (((cmd)->device->channel == 0) ? (ahc)->our_id : (ahc)->our_id_b) \
	| (((cmd)->device->channel == 0) ? 0 : TWIN_CHNLB))

/******************************** Bus DMA *************************************/
पूर्णांक
ahc_dma_tag_create(काष्ठा ahc_softc *ahc, bus_dma_tag_t parent,
		   bus_माप_प्रकार alignment, bus_माप_प्रकार boundary,
		   dma_addr_t lowaddr, dma_addr_t highaddr,
		   bus_dma_filter_t *filter, व्योम *filterarg,
		   bus_माप_प्रकार maxsize, पूर्णांक nsegments,
		   bus_माप_प्रकार maxsegsz, पूर्णांक flags, bus_dma_tag_t *ret_tag)
अणु
	bus_dma_tag_t dmat;

	dmat = kदो_स्मृति(माप(*dmat), GFP_ATOMIC);
	अगर (dmat == शून्य)
		वापस (ENOMEM);

	/*
	 * Linux is very simplistic about DMA memory.  For now करोn't
	 * मुख्यtain all specअगरication inक्रमmation.  Once Linux supplies
	 * better facilities क्रम करोing these operations, or the
	 * needs of this particular driver change, we might need to करो
	 * more here.
	 */
	dmat->alignment = alignment;
	dmat->boundary = boundary;
	dmat->maxsize = maxsize;
	*ret_tag = dmat;
	वापस (0);
पूर्ण

व्योम
ahc_dma_tag_destroy(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat)
अणु
	kमुक्त(dmat);
पूर्ण

पूर्णांक
ahc_dmamem_alloc(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat, व्योम** vaddr,
		 पूर्णांक flags, bus_dmamap_t *mapp)
अणु
	/* XXX: check अगर we really need the GFP_ATOMIC and unwind this mess! */
	*vaddr = dma_alloc_coherent(ahc->dev, dmat->maxsize, mapp, GFP_ATOMIC);
	अगर (*vaddr == शून्य)
		वापस ENOMEM;
	वापस 0;
पूर्ण

व्योम
ahc_dmamem_मुक्त(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat,
		व्योम* vaddr, bus_dmamap_t map)
अणु
	dma_मुक्त_coherent(ahc->dev, dmat->maxsize, vaddr, map);
पूर्ण

पूर्णांक
ahc_dmamap_load(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map,
		व्योम *buf, bus_माप_प्रकार buflen, bus_dmamap_callback_t *cb,
		व्योम *cb_arg, पूर्णांक flags)
अणु
	/*
	 * Assume क्रम now that this will only be used during
	 * initialization and not क्रम per-transaction buffer mapping.
	 */
	bus_dma_segment_t stack_sg;

	stack_sg.ds_addr = map;
	stack_sg.ds_len = dmat->maxsize;
	cb(cb_arg, &stack_sg, /*nseg*/1, /*error*/0);
	वापस (0);
पूर्ण

व्योम
ahc_dmamap_destroy(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map)
अणु
पूर्ण

पूर्णांक
ahc_dmamap_unload(काष्ठा ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map)
अणु
	/* Nothing to करो */
	वापस (0);
पूर्ण

अटल व्योम
ahc_linux_setup_tag_info_global(अक्षर *p)
अणु
	पूर्णांक tags, i, j;

	tags = simple_म_से_अदीर्घ(p + 1, शून्य, 0) & 0xff;
	prपूर्णांकk("Setting Global Tags= %d\n", tags);

	क्रम (i = 0; i < ARRAY_SIZE(aic7xxx_tag_info); i++) अणु
		क्रम (j = 0; j < AHC_NUM_TARGETS; j++) अणु
			aic7xxx_tag_info[i].tag_commands[j] = tags;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ahc_linux_setup_tag_info(u_दीर्घ arg, पूर्णांक instance, पूर्णांक targ, पूर्णांक32_t value)
अणु

	अगर ((instance >= 0) && (targ >= 0)
	 && (instance < ARRAY_SIZE(aic7xxx_tag_info))
	 && (targ < AHC_NUM_TARGETS)) अणु
		aic7xxx_tag_info[instance].tag_commands[targ] = value & 0xff;
		अगर (bootverbose)
			prपूर्णांकk("tag_info[%d:%d] = %d\n", instance, targ, value);
	पूर्ण
पूर्ण

अटल अक्षर *
ahc_parse_brace_option(अक्षर *opt_name, अक्षर *opt_arg, अक्षर *end, पूर्णांक depth,
		       व्योम (*callback)(u_दीर्घ, पूर्णांक, पूर्णांक, पूर्णांक32_t),
		       u_दीर्घ callback_arg)
अणु
	अक्षर	*tok_end;
	अक्षर	*tok_end2;
	पूर्णांक      i;
	पूर्णांक      instance;
	पूर्णांक	 targ;
	पूर्णांक	 करोne;
	अक्षर	 tok_list[] = अणु'.', ',', '{', '}', '\0'पूर्ण;

	/* All options use a ':' name/arg separator */
	अगर (*opt_arg != ':')
		वापस (opt_arg);
	opt_arg++;
	instance = -1;
	targ = -1;
	करोne = FALSE;
	/*
	 * Restore separator that may be in
	 * the middle of our option argument.
	 */
	tok_end = म_अक्षर(opt_arg, '\0');
	अगर (tok_end < end)
		*tok_end = ',';
	जबतक (!करोne) अणु
		चयन (*opt_arg) अणु
		हाल '{':
			अगर (instance == -1) अणु
				instance = 0;
			पूर्ण अन्यथा अणु
				अगर (depth > 1) अणु
					अगर (targ == -1)
						targ = 0;
				पूर्ण अन्यथा अणु
					prपूर्णांकk("Malformed Option %s\n",
					       opt_name);
					करोne = TRUE;
				पूर्ण
			पूर्ण
			opt_arg++;
			अवरोध;
		हाल '}':
			अगर (targ != -1)
				targ = -1;
			अन्यथा अगर (instance != -1)
				instance = -1;
			opt_arg++;
			अवरोध;
		हाल ',':
		हाल '.':
			अगर (instance == -1)
				करोne = TRUE;
			अन्यथा अगर (targ >= 0)
				targ++;
			अन्यथा अगर (instance >= 0)
				instance++;
			opt_arg++;
			अवरोध;
		हाल '\0':
			करोne = TRUE;
			अवरोध;
		शेष:
			tok_end = end;
			क्रम (i = 0; tok_list[i]; i++) अणु
				tok_end2 = म_अक्षर(opt_arg, tok_list[i]);
				अगर ((tok_end2) && (tok_end2 < tok_end))
					tok_end = tok_end2;
			पूर्ण
			callback(callback_arg, instance, targ,
				 simple_म_से_दीर्घ(opt_arg, शून्य, 0));
			opt_arg = tok_end;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस (opt_arg);
पूर्ण

/*
 * Handle Linux boot parameters. This routine allows क्रम assigning a value
 * to a parameter with a ':' between the parameter and the value.
 * ie. aic7xxx=stpwlev:1,extended
 */
अटल पूर्णांक
aic7xxx_setup(अक्षर *s)
अणु
	पूर्णांक	i, n;
	अक्षर   *p;
	अक्षर   *end;

	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		uपूर्णांक32_t *flag;
	पूर्ण options[] = अणु
		अणु "extended", &aic7xxx_extended पूर्ण,
		अणु "no_reset", &aic7xxx_no_reset पूर्ण,
		अणु "verbose", &aic7xxx_verbose पूर्ण,
		अणु "allow_memio", &aic7xxx_allow_memioपूर्ण,
#अगर_घोषित AHC_DEBUG
		अणु "debug", &ahc_debug पूर्ण,
#पूर्ण_अगर
		अणु "periodic_otag", &aic7xxx_periodic_otag पूर्ण,
		अणु "pci_parity", &aic7xxx_pci_parity पूर्ण,
		अणु "seltime", &aic7xxx_selसमय पूर्ण,
		अणु "tag_info", शून्य पूर्ण,
		अणु "global_tag_depth", शून्य पूर्ण,
		अणु "dv", शून्य पूर्ण
	पूर्ण;

	end = म_अक्षर(s, '\0');

	/*
	 * XXX ia64 gcc isn't smart enough to know that ARRAY_SIZE
	 * will never be 0 in this हाल.
	 */
	n = 0;

	जबतक ((p = strsep(&s, ",.")) != शून्य) अणु
		अगर (*p == '\0')
			जारी;
		क्रम (i = 0; i < ARRAY_SIZE(options); i++) अणु

			n = म_माप(options[i].name);
			अगर (म_भेदन(options[i].name, p, n) == 0)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(options))
			जारी;

		अगर (म_भेदन(p, "global_tag_depth", n) == 0) अणु
			ahc_linux_setup_tag_info_global(p + n);
		पूर्ण अन्यथा अगर (म_भेदन(p, "tag_info", n) == 0) अणु
			s = ahc_parse_brace_option("tag_info", p + n, end,
			    2, ahc_linux_setup_tag_info, 0);
		पूर्ण अन्यथा अगर (p[n] == ':') अणु
			*(options[i].flag) = simple_म_से_अदीर्घ(p + n + 1, शून्य, 0);
		पूर्ण अन्यथा अगर (म_भेदन(p, "verbose", n) == 0) अणु
			*(options[i].flag) = 1;
		पूर्ण अन्यथा अणु
			*(options[i].flag) ^= 0xFFFFFFFF;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("aic7xxx=", aic7xxx_setup);

uपूर्णांक32_t aic7xxx_verbose;

पूर्णांक
ahc_linux_रेजिस्टर_host(काष्ठा ahc_softc *ahc, काष्ठा scsi_host_ढाँचा *ढाँचा)
अणु
	अक्षर	buf[80];
	काष्ठा	Scsi_Host *host;
	अक्षर	*new_name;
	u_दीर्घ	s;
	पूर्णांक	retval;

	ढाँचा->name = ahc->description;
	host = scsi_host_alloc(ढाँचा, माप(काष्ठा ahc_softc *));
	अगर (host == शून्य)
		वापस (ENOMEM);

	*((काष्ठा ahc_softc **)host->hostdata) = ahc;
	ahc->platक्रमm_data->host = host;
	host->can_queue = AHC_MAX_QUEUE;
	host->cmd_per_lun = 2;
	/* XXX No way to communicate the ID क्रम multiple channels */
	host->this_id = ahc->our_id;
	host->irq = ahc->platक्रमm_data->irq;
	host->max_id = (ahc->features & AHC_WIDE) ? 16 : 8;
	host->max_lun = AHC_NUM_LUNS;
	host->max_channel = (ahc->features & AHC_TWIN) ? 1 : 0;
	host->sg_tablesize = AHC_NSEG;
	ahc_lock(ahc, &s);
	ahc_set_unit(ahc, ahc_linux_unit++);
	ahc_unlock(ahc, &s);
	प्र_लिखो(buf, "scsi%d", host->host_no);
	new_name = kदो_स्मृति(म_माप(buf) + 1, GFP_ATOMIC);
	अगर (new_name != शून्य) अणु
		म_नकल(new_name, buf);
		ahc_set_name(ahc, new_name);
	पूर्ण
	host->unique_id = ahc->unit;
	ahc_linux_initialize_scsi_bus(ahc);
	ahc_पूर्णांकr_enable(ahc, TRUE);

	host->transportt = ahc_linux_transport_ढाँचा;

	retval = scsi_add_host(host, ahc->dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "aic7xxx: scsi_add_host failed\n");
		scsi_host_put(host);
		वापस retval;
	पूर्ण

	scsi_scan_host(host);
	वापस 0;
पूर्ण

/*
 * Place the SCSI bus पूर्णांकo a known state by either resetting it,
 * or क्रमcing transfer negotiations on the next command to any
 * target.
 */
अटल व्योम
ahc_linux_initialize_scsi_bus(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक i;
	पूर्णांक numtarg;
	अचिन्हित दीर्घ s;

	i = 0;
	numtarg = 0;

	ahc_lock(ahc, &s);

	अगर (aic7xxx_no_reset != 0)
		ahc->flags &= ~(AHC_RESET_BUS_A|AHC_RESET_BUS_B);

	अगर ((ahc->flags & AHC_RESET_BUS_A) != 0)
		ahc_reset_channel(ahc, 'A', /*initiate_reset*/TRUE);
	अन्यथा
		numtarg = (ahc->features & AHC_WIDE) ? 16 : 8;

	अगर ((ahc->features & AHC_TWIN) != 0) अणु

		अगर ((ahc->flags & AHC_RESET_BUS_B) != 0) अणु
			ahc_reset_channel(ahc, 'B', /*initiate_reset*/TRUE);
		पूर्ण अन्यथा अणु
			अगर (numtarg == 0)
				i = 8;
			numtarg += 8;
		पूर्ण
	पूर्ण

	/*
	 * Force negotiation to async क्रम all tarमाला_लो that
	 * will not see an initial bus reset.
	 */
	क्रम (; i < numtarg; i++) अणु
		काष्ठा ahc_devinfo devinfo;
		काष्ठा ahc_initiator_tinfo *tinfo;
		काष्ठा ahc_पंचांगode_tstate *tstate;
		u_पूर्णांक our_id;
		u_पूर्णांक target_id;
		अक्षर channel;

		channel = 'A';
		our_id = ahc->our_id;
		target_id = i;
		अगर (i > 7 && (ahc->features & AHC_TWIN) != 0) अणु
			channel = 'B';
			our_id = ahc->our_id_b;
			target_id = i % 8;
		पूर्ण
		tinfo = ahc_fetch_transinfo(ahc, channel, our_id,
					    target_id, &tstate);
		ahc_compile_devinfo(&devinfo, our_id, target_id,
				    CAM_LUN_WILDCARD, channel, ROLE_INITIATOR);
		ahc_update_neg_request(ahc, &devinfo, tstate,
				       tinfo, AHC_NEG_ALWAYS);
	पूर्ण
	ahc_unlock(ahc, &s);
	/* Give the bus some समय to recover */
	अगर ((ahc->flags & (AHC_RESET_BUS_A|AHC_RESET_BUS_B)) != 0) अणु
		ahc_linux_मुक्तze_simq(ahc);
		msleep(AIC7XXX_RESET_DELAY);
		ahc_linux_release_simq(ahc);
	पूर्ण
पूर्ण

पूर्णांक
ahc_platक्रमm_alloc(काष्ठा ahc_softc *ahc, व्योम *platक्रमm_arg)
अणु

	ahc->platक्रमm_data =
	    kzalloc(माप(काष्ठा ahc_platक्रमm_data), GFP_ATOMIC);
	अगर (ahc->platक्रमm_data == शून्य)
		वापस (ENOMEM);
	ahc->platक्रमm_data->irq = AHC_LINUX_NOIRQ;
	ahc_lockinit(ahc);
	ahc->selसमय = (aic7xxx_selसमय & 0x3) << 4;
	ahc->selसमय_b = (aic7xxx_selसमय & 0x3) << 4;
	अगर (aic7xxx_pci_parity == 0)
		ahc->flags |= AHC_DISABLE_PCI_PERR;

	वापस (0);
पूर्ण

व्योम
ahc_platक्रमm_मुक्त(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scsi_target *starget;
	पूर्णांक i;

	अगर (ahc->platक्रमm_data != शून्य) अणु
		/* destroy all of the device and target objects */
		क्रम (i = 0; i < AHC_NUM_TARGETS; i++) अणु
			starget = ahc->platक्रमm_data->starget[i];
			अगर (starget != शून्य) अणु
				ahc->platक्रमm_data->starget[i] = शून्य;
			पूर्ण
		पूर्ण

		अगर (ahc->platक्रमm_data->irq != AHC_LINUX_NOIRQ)
			मुक्त_irq(ahc->platक्रमm_data->irq, ahc);
		अगर (ahc->tag == BUS_SPACE_PIO
		 && ahc->bsh.ioport != 0)
			release_region(ahc->bsh.ioport, 256);
		अगर (ahc->tag == BUS_SPACE_MEMIO
		 && ahc->bsh.maddr != शून्य) अणु
			iounmap(ahc->bsh.maddr);
			release_mem_region(ahc->platक्रमm_data->mem_busaddr,
					   0x1000);
		पूर्ण

		अगर (ahc->platक्रमm_data->host)
			scsi_host_put(ahc->platक्रमm_data->host);

		kमुक्त(ahc->platक्रमm_data);
	पूर्ण
पूर्ण

व्योम
ahc_platक्रमm_मुक्तze_devq(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	ahc_platक्रमm_पात_scbs(ahc, SCB_GET_TARGET(ahc, scb),
				SCB_GET_CHANNEL(ahc, scb),
				SCB_GET_LUN(scb), SCB_LIST_शून्य,
				ROLE_UNKNOWN, CAM_REQUEUE_REQ);
पूर्ण

व्योम
ahc_platक्रमm_set_tags(काष्ठा ahc_softc *ahc, काष्ठा scsi_device *sdev,
		      काष्ठा ahc_devinfo *devinfo, ahc_queue_alg alg)
अणु
	काष्ठा ahc_linux_device *dev;
	पूर्णांक was_queuing;
	पूर्णांक now_queuing;

	अगर (sdev == शून्य)
		वापस;
	dev = scsi_transport_device_data(sdev);

	was_queuing = dev->flags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED);
	चयन (alg) अणु
	शेष:
	हाल AHC_QUEUE_NONE:
		now_queuing = 0;
		अवरोध;
	हाल AHC_QUEUE_BASIC:
		now_queuing = AHC_DEV_Q_BASIC;
		अवरोध;
	हाल AHC_QUEUE_TAGGED:
		now_queuing = AHC_DEV_Q_TAGGED;
		अवरोध;
	पूर्ण
	अगर ((dev->flags & AHC_DEV_FREEZE_TIL_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) अणु
		dev->flags |= AHC_DEV_FREEZE_TIL_EMPTY;
		dev->qfrozen++;
	पूर्ण

	dev->flags &= ~(AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED|AHC_DEV_PERIODIC_OTAG);
	अगर (now_queuing) अणु
		u_पूर्णांक usertags;

		usertags = ahc_linux_user_tagdepth(ahc, devinfo);
		अगर (!was_queuing) अणु
			/*
			 * Start out aggressively and allow our
			 * dynamic queue depth algorithm to take
			 * care of the rest.
			 */
			dev->maxtags = usertags;
			dev->खोलोings = dev->maxtags - dev->active;
		पूर्ण
		अगर (dev->maxtags == 0) अणु
			/*
			 * Queueing is disabled by the user.
			 */
			dev->खोलोings = 1;
		पूर्ण अन्यथा अगर (alg == AHC_QUEUE_TAGGED) अणु
			dev->flags |= AHC_DEV_Q_TAGGED;
			अगर (aic7xxx_periodic_otag != 0)
				dev->flags |= AHC_DEV_PERIODIC_OTAG;
		पूर्ण अन्यथा
			dev->flags |= AHC_DEV_Q_BASIC;
	पूर्ण अन्यथा अणु
		/* We can only have one खोलोing. */
		dev->maxtags = 0;
		dev->खोलोings =  1 - dev->active;
	पूर्ण
	चयन ((dev->flags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED))) अणु
	हाल AHC_DEV_Q_BASIC:
	हाल AHC_DEV_Q_TAGGED:
		scsi_change_queue_depth(sdev,
				dev->खोलोings + dev->active);
		अवरोध;
	शेष:
		/*
		 * We allow the OS to queue 2 untagged transactions to
		 * us at any समय even though we can only execute them
		 * serially on the controller/device.  This should
		 * हटाओ some latency.
		 */
		scsi_change_queue_depth(sdev, 2);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक
ahc_platक्रमm_पात_scbs(काष्ठा ahc_softc *ahc, पूर्णांक target, अक्षर channel,
			पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status)
अणु
	वापस 0;
पूर्ण

अटल u_पूर्णांक
ahc_linux_user_tagdepth(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	अटल पूर्णांक warned_user;
	u_पूर्णांक tags;

	tags = 0;
	अगर ((ahc->user_discenable & devinfo->target_mask) != 0) अणु
		अगर (ahc->unit >= ARRAY_SIZE(aic7xxx_tag_info)) अणु
			अगर (warned_user == 0) अणु

				prपूर्णांकk(KERN_WARNING
"aic7xxx: WARNING: Insufficient tag_info instances\n"
"aic7xxx: for installed controllers. Using defaults\n"
"aic7xxx: Please update the aic7xxx_tag_info array in\n"
"aic7xxx: the aic7xxx_osm..c source file.\n");
				warned_user++;
			पूर्ण
			tags = AHC_MAX_QUEUE;
		पूर्ण अन्यथा अणु
			adapter_tag_info_t *tag_info;

			tag_info = &aic7xxx_tag_info[ahc->unit];
			tags = tag_info->tag_commands[devinfo->target_offset];
			अगर (tags > AHC_MAX_QUEUE)
				tags = AHC_MAX_QUEUE;
		पूर्ण
	पूर्ण
	वापस (tags);
पूर्ण

/*
 * Determines the queue depth क्रम a given device.
 */
अटल व्योम
ahc_linux_device_queue_depth(काष्ठा scsi_device *sdev)
अणु
	काष्ठा	ahc_devinfo devinfo;
	u_पूर्णांक	tags;
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)sdev->host->hostdata);

	ahc_compile_devinfo(&devinfo,
			    sdev->sdev_target->channel == 0
			  ? ahc->our_id : ahc->our_id_b,
			    sdev->sdev_target->id, sdev->lun,
			    sdev->sdev_target->channel == 0 ? 'A' : 'B',
			    ROLE_INITIATOR);
	tags = ahc_linux_user_tagdepth(ahc, &devinfo);
	अगर (tags != 0 && sdev->tagged_supported != 0) अणु

		ahc_platक्रमm_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_TAGGED);
		ahc_send_async(ahc, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
		ahc_prपूर्णांक_devinfo(ahc, &devinfo);
		prपूर्णांकk("Tagged Queuing enabled.  Depth %d\n", tags);
	पूर्ण अन्यथा अणु
		ahc_platक्रमm_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_NONE);
		ahc_send_async(ahc, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahc_linux_run_command(काष्ठा ahc_softc *ahc, काष्ठा ahc_linux_device *dev,
		      काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा	 scb *scb;
	काष्ठा	 hardware_scb *hscb;
	काष्ठा	 ahc_initiator_tinfo *tinfo;
	काष्ठा	 ahc_पंचांगode_tstate *tstate;
	uपूर्णांक16_t mask;
	काष्ठा scb_tailq *untagged_q = शून्य;
	पूर्णांक nseg;

	/*
	 * Schedule us to run later.  The only reason we are not
	 * running is because the whole controller Q is frozen.
	 */
	अगर (ahc->platक्रमm_data->qfrozen != 0)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 * We only allow one untagged transaction
	 * per target in the initiator role unless
	 * we are storing a full busy target *lun*
	 * table in SCB space.
	 */
	अगर (!(cmd->flags & SCMD_TAGGED)
	    && (ahc->features & AHC_SCB_BTT) == 0) अणु
		पूर्णांक target_offset;

		target_offset = cmd->device->id + cmd->device->channel * 8;
		untagged_q = &(ahc->untagged_queues[target_offset]);
		अगर (!TAILQ_EMPTY(untagged_q))
			/* अगर we're alपढ़ोy executing an untagged command
			 * we're busy to another */
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	nseg = scsi_dma_map(cmd);
	अगर (nseg < 0)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 * Get an scb to use.
	 */
	scb = ahc_get_scb(ahc);
	अगर (!scb) अणु
		scsi_dma_unmap(cmd);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	scb->io_ctx = cmd;
	scb->platक्रमm_data->dev = dev;
	hscb = scb->hscb;
	cmd->host_scribble = (अक्षर *)scb;

	/*
	 * Fill out basics of the HSCB.
	 */
	hscb->control = 0;
	hscb->scsiid = BUILD_SCSIID(ahc, cmd);
	hscb->lun = cmd->device->lun;
	mask = SCB_GET_TARGET_MASK(ahc, scb);
	tinfo = ahc_fetch_transinfo(ahc, SCB_GET_CHANNEL(ahc, scb),
				    SCB_GET_OUR_ID(scb),
				    SCB_GET_TARGET(ahc, scb), &tstate);
	hscb->scsirate = tinfo->scsirate;
	hscb->scsioffset = tinfo->curr.offset;
	अगर ((tstate->ultraenb & mask) != 0)
		hscb->control |= ULTRAENB;

	अगर ((ahc->user_discenable & mask) != 0)
		hscb->control |= DISCENB;

	अगर ((tstate->स्वतः_negotiate & mask) != 0) अणु
		scb->flags |= SCB_AUTO_NEGOTIATE;
		scb->hscb->control |= MK_MESSAGE;
	पूर्ण

	अगर ((dev->flags & (AHC_DEV_Q_TAGGED|AHC_DEV_Q_BASIC)) != 0) अणु
		अगर (dev->commands_since_idle_or_otag == AHC_OTAG_THRESH
				&& (dev->flags & AHC_DEV_Q_TAGGED) != 0) अणु
			hscb->control |= ORDERED_QUEUE_TAG;
			dev->commands_since_idle_or_otag = 0;
		पूर्ण अन्यथा अणु
			hscb->control |= SIMPLE_QUEUE_TAG;
		पूर्ण
	पूर्ण

	hscb->cdb_len = cmd->cmd_len;
	अगर (hscb->cdb_len <= 12) अणु
		स_नकल(hscb->shared_data.cdb, cmd->cmnd, hscb->cdb_len);
	पूर्ण अन्यथा अणु
		स_नकल(hscb->cdb32, cmd->cmnd, hscb->cdb_len);
		scb->flags |= SCB_CDB32_PTR;
	पूर्ण

	scb->platक्रमm_data->xfer_len = 0;
	ahc_set_residual(scb, 0);
	ahc_set_sense_residual(scb, 0);
	scb->sg_count = 0;

	अगर (nseg > 0) अणु
		काष्ठा	ahc_dma_seg *sg;
		काष्ठा	scatterlist *cur_seg;
		पूर्णांक i;

		/* Copy the segments पूर्णांकo the SG list. */
		sg = scb->sg_list;
		/*
		 * The sg_count may be larger than nseg अगर
		 * a transfer crosses a 32bit page.
		 */
		scsi_क्रम_each_sg(cmd, cur_seg, nseg, i) अणु
			dma_addr_t addr;
			bus_माप_प्रकार len;
			पूर्णांक consumed;

			addr = sg_dma_address(cur_seg);
			len = sg_dma_len(cur_seg);
			consumed = ahc_linux_map_seg(ahc, scb,
						     sg, addr, len);
			sg += consumed;
			scb->sg_count += consumed;
		पूर्ण
		sg--;
		sg->len |= ahc_htole32(AHC_DMA_LAST_SEG);

		/*
		 * Reset the sg list poपूर्णांकer.
		 */
		scb->hscb->sgptr =
			ahc_htole32(scb->sg_list_phys | SG_FULL_RESID);

		/*
		 * Copy the first SG पूर्णांकo the "current"
		 * data poपूर्णांकer area.
		 */
		scb->hscb->dataptr = scb->sg_list->addr;
		scb->hscb->datacnt = scb->sg_list->len;
	पूर्ण अन्यथा अणु
		scb->hscb->sgptr = ahc_htole32(SG_LIST_शून्य);
		scb->hscb->dataptr = 0;
		scb->hscb->datacnt = 0;
		scb->sg_count = 0;
	पूर्ण

	LIST_INSERT_HEAD(&ahc->pending_scbs, scb, pending_links);
	dev->खोलोings--;
	dev->active++;
	dev->commands_issued++;
	अगर ((dev->flags & AHC_DEV_PERIODIC_OTAG) != 0)
		dev->commands_since_idle_or_otag++;

	scb->flags |= SCB_ACTIVE;
	अगर (untagged_q) अणु
		TAILQ_INSERT_TAIL(untagged_q, scb, links.tqe);
		scb->flags |= SCB_UNTAGGEDQ;
	पूर्ण
	ahc_queue_scb(ahc, scb);
	वापस 0;
पूर्ण

/*
 * SCSI controller पूर्णांकerrupt handler.
 */
irqवापस_t
ahc_linux_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा	ahc_softc *ahc;
	u_दीर्घ	flags;
	पूर्णांक	ours;

	ahc = (काष्ठा ahc_softc *) dev_id;
	ahc_lock(ahc, &flags);
	ours = ahc_पूर्णांकr(ahc);
	ahc_unlock(ahc, &flags);
	वापस IRQ_RETVAL(ours);
पूर्ण

व्योम
ahc_platक्रमm_flushwork(काष्ठा ahc_softc *ahc)
अणु

पूर्ण

व्योम
ahc_send_async(काष्ठा ahc_softc *ahc, अक्षर channel,
	       u_पूर्णांक target, u_पूर्णांक lun, ac_code code)
अणु
	चयन (code) अणु
	हाल AC_TRANSFER_NEG:
	अणु
		काष्ठा	scsi_target *starget;
		काष्ठा	ahc_initiator_tinfo *tinfo;
		काष्ठा	ahc_पंचांगode_tstate *tstate;
		पूर्णांक	target_offset;
		अचिन्हित पूर्णांक target_ppr_options;

		BUG_ON(target == CAM_TARGET_WILDCARD);

		tinfo = ahc_fetch_transinfo(ahc, channel,
						channel == 'A' ? ahc->our_id
							       : ahc->our_id_b,
						target, &tstate);

		/*
		 * Don't bother reporting results जबतक
		 * negotiations are still pending.
		 */
		अगर (tinfo->curr.period != tinfo->goal.period
		 || tinfo->curr.width != tinfo->goal.width
		 || tinfo->curr.offset != tinfo->goal.offset
		 || tinfo->curr.ppr_options != tinfo->goal.ppr_options)
			अगर (bootverbose == 0)
				अवरोध;

		/*
		 * Don't bother reporting results that
		 * are identical to those last reported.
		 */
		target_offset = target;
		अगर (channel == 'B')
			target_offset += 8;
		starget = ahc->platक्रमm_data->starget[target_offset];
		अगर (starget == शून्य)
			अवरोध;

		target_ppr_options =
			(spi_dt(starget) ? MSG_EXT_PPR_DT_REQ : 0)
			+ (spi_qas(starget) ? MSG_EXT_PPR_QAS_REQ : 0)
			+ (spi_iu(starget) ?  MSG_EXT_PPR_IU_REQ : 0);

		अगर (tinfo->curr.period == spi_period(starget)
		    && tinfo->curr.width == spi_width(starget)
		    && tinfo->curr.offset == spi_offset(starget)
		 && tinfo->curr.ppr_options == target_ppr_options)
			अगर (bootverbose == 0)
				अवरोध;

		spi_period(starget) = tinfo->curr.period;
		spi_width(starget) = tinfo->curr.width;
		spi_offset(starget) = tinfo->curr.offset;
		spi_dt(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_DT_REQ ? 1 : 0;
		spi_qas(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_QAS_REQ ? 1 : 0;
		spi_iu(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_IU_REQ ? 1 : 0;
		spi_display_xfer_agreement(starget);
		अवरोध;
	पूर्ण
	हाल AC_SENT_BDR:
	अणु
		WARN_ON(lun != CAM_LUN_WILDCARD);
		scsi_report_device_reset(ahc->platक्रमm_data->host,
					 channel - 'A', target);
		अवरोध;
	पूर्ण
	हाल AC_BUS_RESET:
		अगर (ahc->platक्रमm_data->host != शून्य) अणु
			scsi_report_bus_reset(ahc->platक्रमm_data->host,
					      channel - 'A');
		पूर्ण
		अवरोध;
	शेष:
		panic("ahc_send_async: Unexpected async event");
	पूर्ण
पूर्ण

/*
 * Calls the higher level scsi करोne function and मुक्तs the scb.
 */
व्योम
ahc_करोne(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा	   ahc_linux_device *dev;

	LIST_REMOVE(scb, pending_links);
	अगर ((scb->flags & SCB_UNTAGGEDQ) != 0) अणु
		काष्ठा scb_tailq *untagged_q;
		पूर्णांक target_offset;

		target_offset = SCB_GET_TARGET_OFFSET(ahc, scb);
		untagged_q = &(ahc->untagged_queues[target_offset]);
		TAILQ_REMOVE(untagged_q, scb, links.tqe);
		BUG_ON(!TAILQ_EMPTY(untagged_q));
	पूर्ण अन्यथा अगर ((scb->flags & SCB_ACTIVE) == 0) अणु
		/*
		 * Transactions पातed from the untagged queue may
		 * not have been dispatched to the controller, so
		 * only check the SCB_ACTIVE flag क्रम tagged transactions.
		 */
		prपूर्णांकk("SCB %d done'd twice\n", scb->hscb->tag);
		ahc_dump_card_state(ahc);
		panic("Stopping for safety");
	पूर्ण
	cmd = scb->io_ctx;
	dev = scb->platक्रमm_data->dev;
	dev->active--;
	dev->खोलोings++;
	अगर ((cmd->result & (CAM_DEV_QFRZN << 16)) != 0) अणु
		cmd->result &= ~(CAM_DEV_QFRZN << 16);
		dev->qfrozen--;
	पूर्ण
	ahc_linux_unmap_scb(ahc, scb);

	/*
	 * Guard against stale sense data.
	 * The Linux mid-layer assumes that sense
	 * was retrieved anyसमय the first byte of
	 * the sense buffer looks "sane".
	 */
	cmd->sense_buffer[0] = 0;
	अगर (ahc_get_transaction_status(scb) == CAM_REQ_INPROG) अणु
#अगर_घोषित AHC_REPORT_UNDERFLOWS
		uपूर्णांक32_t amount_xferred;

		amount_xferred =
		    ahc_get_transfer_length(scb) - ahc_get_residual(scb);
#पूर्ण_अगर
		अगर ((scb->flags & SCB_TRANSMISSION_ERROR) != 0) अणु
#अगर_घोषित AHC_DEBUG
			अगर ((ahc_debug & AHC_SHOW_MISC) != 0) अणु
				ahc_prपूर्णांक_path(ahc, scb);
				prपूर्णांकk("Set CAM_UNCOR_PARITY\n");
			पूर्ण
#पूर्ण_अगर
			ahc_set_transaction_status(scb, CAM_UNCOR_PARITY);
#अगर_घोषित AHC_REPORT_UNDERFLOWS
		/*
		 * This code is disabled by शेष as some
		 * clients of the SCSI प्रणाली करो not properly
		 * initialize the underflow parameter.  This
		 * results in spurious termination of commands
		 * that complete as expected (e.g. underflow is
		 * allowed as command can वापस variable amounts
		 * of data.
		 */
		पूर्ण अन्यथा अगर (amount_xferred < scb->io_ctx->underflow) अणु
			u_पूर्णांक i;

			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("CDB:");
			क्रम (i = 0; i < scb->io_ctx->cmd_len; i++)
				prपूर्णांकk(" 0x%x", scb->io_ctx->cmnd[i]);
			prपूर्णांकk("\n");
			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("Saw underflow (%ld of %ld bytes). "
			       "Treated as error\n",
				ahc_get_residual(scb),
				ahc_get_transfer_length(scb));
			ahc_set_transaction_status(scb, CAM_DATA_RUN_ERR);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ahc_set_transaction_status(scb, CAM_REQ_CMP);
		पूर्ण
	पूर्ण अन्यथा अगर (ahc_get_transaction_status(scb) == CAM_SCSI_STATUS_ERROR) अणु
		ahc_linux_handle_scsi_status(ahc, cmd->device, scb);
	पूर्ण

	अगर (dev->खोलोings == 1
	 && ahc_get_transaction_status(scb) == CAM_REQ_CMP
	 && ahc_get_scsi_status(scb) != SAM_STAT_TASK_SET_FULL)
		dev->tag_success_count++;
	/*
	 * Some devices deal with temporary पूर्णांकernal resource
	 * लघुages by वापसing queue full.  When the queue
	 * full occurrs, we throttle back.  Slowly try to get
	 * back to our previous queue depth.
	 */
	अगर ((dev->खोलोings + dev->active) < dev->maxtags
	 && dev->tag_success_count > AHC_TAG_SUCCESS_INTERVAL) अणु
		dev->tag_success_count = 0;
		dev->खोलोings++;
	पूर्ण

	अगर (dev->active == 0)
		dev->commands_since_idle_or_otag = 0;

	अगर ((scb->flags & SCB_RECOVERY_SCB) != 0) अणु
		prपूर्णांकk("Recovery SCB completes\n");
		अगर (ahc_get_transaction_status(scb) == CAM_BDR_SENT
		 || ahc_get_transaction_status(scb) == CAM_REQ_ABORTED)
			ahc_set_transaction_status(scb, CAM_CMD_TIMEOUT);

		अगर (ahc->platक्रमm_data->eh_करोne)
			complete(ahc->platक्रमm_data->eh_करोne);
	पूर्ण

	ahc_मुक्त_scb(ahc, scb);
	ahc_linux_queue_cmd_complete(ahc, cmd);
पूर्ण

अटल व्योम
ahc_linux_handle_scsi_status(काष्ठा ahc_softc *ahc,
			     काष्ठा scsi_device *sdev, काष्ठा scb *scb)
अणु
	काष्ठा	ahc_devinfo devinfo;
	काष्ठा ahc_linux_device *dev = scsi_transport_device_data(sdev);

	ahc_compile_devinfo(&devinfo,
			    ahc->our_id,
			    sdev->sdev_target->id, sdev->lun,
			    sdev->sdev_target->channel == 0 ? 'A' : 'B',
			    ROLE_INITIATOR);

	/*
	 * We करोn't currently trust the mid-layer to
	 * properly deal with queue full or busy.  So,
	 * when one occurs, we tell the mid-layer to
	 * unconditionally requeue the command to us
	 * so that we can retry it ourselves.  We also
	 * implement our own throttling mechanism so
	 * we करोn't clobber the device with too many
	 * commands.
	 */
	चयन (ahc_get_scsi_status(scb)) अणु
	शेष:
		अवरोध;
	हाल SAM_STAT_CHECK_CONDITION:
	हाल SAM_STAT_COMMAND_TERMINATED:
	अणु
		काष्ठा scsi_cmnd *cmd;

		/*
		 * Copy sense inक्रमmation to the OS's cmd
		 * काष्ठाure अगर it is available.
		 */
		cmd = scb->io_ctx;
		अगर (scb->flags & SCB_SENSE) अणु
			u_पूर्णांक sense_size;

			sense_size = min(माप(काष्ठा scsi_sense_data)
				       - ahc_get_sense_residual(scb),
					 (u_दीर्घ)SCSI_SENSE_BUFFERSIZE);
			स_नकल(cmd->sense_buffer,
			       ahc_get_sense_buf(ahc, scb), sense_size);
			अगर (sense_size < SCSI_SENSE_BUFFERSIZE)
				स_रखो(&cmd->sense_buffer[sense_size], 0,
				       SCSI_SENSE_BUFFERSIZE - sense_size);
			cmd->result |= (DRIVER_SENSE << 24);
#अगर_घोषित AHC_DEBUG
			अगर (ahc_debug & AHC_SHOW_SENSE) अणु
				पूर्णांक i;

				prपूर्णांकk("Copied %d bytes of sense data:",
				       sense_size);
				क्रम (i = 0; i < sense_size; i++) अणु
					अगर ((i & 0xF) == 0)
						prपूर्णांकk("\n");
					prपूर्णांकk("0x%x ", cmd->sense_buffer[i]);
				पूर्ण
				prपूर्णांकk("\n");
			पूर्ण
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SAM_STAT_TASK_SET_FULL:
	अणु
		/*
		 * By the समय the core driver has वापसed this
		 * command, all other commands that were queued
		 * to us but not the device have been वापसed.
		 * This ensures that dev->active is equal to
		 * the number of commands actually queued to
		 * the device.
		 */
		dev->tag_success_count = 0;
		अगर (dev->active != 0) अणु
			/*
			 * Drop our खोलोing count to the number
			 * of commands currently outstanding.
			 */
			dev->खोलोings = 0;
/*
			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("Dropping tag count to %d\n", dev->active);
 */
			अगर (dev->active == dev->tags_on_last_queuefull) अणु

				dev->last_queuefull_same_count++;
				/*
				 * If we repeatedly see a queue full
				 * at the same queue depth, this
				 * device has a fixed number of tag
				 * slots.  Lock in this tag depth
				 * so we stop seeing queue fulls from
				 * this device.
				 */
				अगर (dev->last_queuefull_same_count
				 == AHC_LOCK_TAGS_COUNT) अणु
					dev->maxtags = dev->active;
					ahc_prपूर्णांक_path(ahc, scb);
					prपूर्णांकk("Locking max tag count at %d\n",
					       dev->active);
				पूर्ण
			पूर्ण अन्यथा अणु
				dev->tags_on_last_queuefull = dev->active;
				dev->last_queuefull_same_count = 0;
			पूर्ण
			ahc_set_transaction_status(scb, CAM_REQUEUE_REQ);
			ahc_set_scsi_status(scb, SAM_STAT_GOOD);
			ahc_platक्रमm_set_tags(ahc, sdev, &devinfo,
				     (dev->flags & AHC_DEV_Q_BASIC)
				   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
			अवरोध;
		पूर्ण
		/*
		 * Drop करोwn to a single खोलोing, and treat this
		 * as अगर the target वापसed BUSY SCSI status.
		 */
		dev->खोलोings = 1;
		ahc_set_scsi_status(scb, SAM_STAT_BUSY);
		ahc_platक्रमm_set_tags(ahc, sdev, &devinfo,
			     (dev->flags & AHC_DEV_Q_BASIC)
			   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ahc_linux_queue_cmd_complete(काष्ठा ahc_softc *ahc, काष्ठा scsi_cmnd *cmd)
अणु
	/*
	 * Map CAM error codes पूर्णांकo Linux Error codes.  We
	 * aव्योम the conversion so that the DV code has the
	 * full error inक्रमmation available when making
	 * state change decisions.
	 */
	अणु
		u_पूर्णांक new_status;

		चयन (ahc_cmd_get_transaction_status(cmd)) अणु
		हाल CAM_REQ_INPROG:
		हाल CAM_REQ_CMP:
		हाल CAM_SCSI_STATUS_ERROR:
			new_status = DID_OK;
			अवरोध;
		हाल CAM_REQ_ABORTED:
			new_status = DID_ABORT;
			अवरोध;
		हाल CAM_BUSY:
			new_status = DID_BUS_BUSY;
			अवरोध;
		हाल CAM_REQ_INVALID:
		हाल CAM_PATH_INVALID:
			new_status = DID_BAD_TARGET;
			अवरोध;
		हाल CAM_SEL_TIMEOUT:
			new_status = DID_NO_CONNECT;
			अवरोध;
		हाल CAM_SCSI_BUS_RESET:
		हाल CAM_BDR_SENT:
			new_status = DID_RESET;
			अवरोध;
		हाल CAM_UNCOR_PARITY:
			new_status = DID_PARITY;
			अवरोध;
		हाल CAM_CMD_TIMEOUT:
			new_status = DID_TIME_OUT;
			अवरोध;
		हाल CAM_UA_ABORT:
		हाल CAM_REQ_CMP_ERR:
		हाल CAM_AUTOSENSE_FAIL:
		हाल CAM_NO_HBA:
		हाल CAM_DATA_RUN_ERR:
		हाल CAM_UNEXP_BUSFREE:
		हाल CAM_SEQUENCE_FAIL:
		हाल CAM_CCB_LEN_ERR:
		हाल CAM_PROVIDE_FAIL:
		हाल CAM_REQ_TERMIO:
		हाल CAM_UNREC_HBA_ERROR:
		हाल CAM_REQ_TOO_BIG:
			new_status = DID_ERROR;
			अवरोध;
		हाल CAM_REQUEUE_REQ:
			new_status = DID_REQUEUE;
			अवरोध;
		शेष:
			/* We should never get here */
			new_status = DID_ERROR;
			अवरोध;
		पूर्ण

		ahc_cmd_set_transaction_status(cmd, new_status);
	पूर्ण

	cmd->scsi_करोne(cmd);
पूर्ण

अटल व्योम
ahc_linux_मुक्तze_simq(काष्ठा ahc_softc *ahc)
अणु
	अचिन्हित दीर्घ s;

	ahc_lock(ahc, &s);
	ahc->platक्रमm_data->qfrozen++;
	अगर (ahc->platक्रमm_data->qfrozen == 1) अणु
		scsi_block_requests(ahc->platक्रमm_data->host);

		/* XXX What about Twin channels? */
		ahc_platक्रमm_पात_scbs(ahc, CAM_TARGET_WILDCARD, ALL_CHANNELS,
					CAM_LUN_WILDCARD, SCB_LIST_शून्य,
					ROLE_INITIATOR, CAM_REQUEUE_REQ);
	पूर्ण
	ahc_unlock(ahc, &s);
पूर्ण

अटल व्योम
ahc_linux_release_simq(काष्ठा ahc_softc *ahc)
अणु
	u_दीर्घ s;
	पूर्णांक    unblock_reqs;

	unblock_reqs = 0;
	ahc_lock(ahc, &s);
	अगर (ahc->platक्रमm_data->qfrozen > 0)
		ahc->platक्रमm_data->qfrozen--;
	अगर (ahc->platक्रमm_data->qfrozen == 0)
		unblock_reqs = 1;
	ahc_unlock(ahc, &s);
	/*
	 * There is still a race here.  The mid-layer
	 * should keep its own मुक्तze count and use
	 * a bottom half handler to run the queues
	 * so we can unblock with our own lock held.
	 */
	अगर (unblock_reqs)
		scsi_unblock_requests(ahc->platक्रमm_data->host);
पूर्ण

अटल पूर्णांक
ahc_linux_queue_recovery_cmd(काष्ठा scsi_cmnd *cmd, scb_flag flag)
अणु
	काष्ठा ahc_softc *ahc;
	काष्ठा ahc_linux_device *dev;
	काष्ठा scb *pending_scb;
	u_पूर्णांक  saved_scbptr;
	u_पूर्णांक  active_scb_index;
	u_पूर्णांक  last_phase;
	u_पूर्णांक  saved_scsiid;
	u_पूर्णांक  cdb_byte;
	पूर्णांक    retval;
	पूर्णांक    was_छोड़ोd;
	पूर्णांक    छोड़ोd;
	पूर्णांक    रुको;
	पूर्णांक    disconnected;
	अचिन्हित दीर्घ flags;

	pending_scb = शून्य;
	छोड़ोd = FALSE;
	रुको = FALSE;
	ahc = *(काष्ठा ahc_softc **)cmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, cmd, "Attempting to queue a%s message\n",
	       flag == SCB_ABORT ? "n ABORT" : " TARGET RESET");

	prपूर्णांकk("CDB:");
	क्रम (cdb_byte = 0; cdb_byte < cmd->cmd_len; cdb_byte++)
		prपूर्णांकk(" 0x%x", cmd->cmnd[cdb_byte]);
	prपूर्णांकk("\n");

	ahc_lock(ahc, &flags);

	/*
	 * First determine अगर we currently own this command.
	 * Start by searching the device queue.  If not found
	 * there, check the pending_scb list.  If not found
	 * at all, and the प्रणाली wanted us to just पात the
	 * command, वापस success.
	 */
	dev = scsi_transport_device_data(cmd->device);

	अगर (dev == शून्य) अणु
		/*
		 * No target device क्रम this command exists,
		 * so we must not still own the command.
		 */
		prपूर्णांकk("%s:%d:%d:%d: Is not an active device\n",
		       ahc_name(ahc), cmd->device->channel, cmd->device->id,
		       (u8)cmd->device->lun);
		retval = SUCCESS;
		जाओ no_cmd;
	पूर्ण

	अगर ((dev->flags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED)) == 0
	 && ahc_search_untagged_queues(ahc, cmd, cmd->device->id,
				       cmd->device->channel + 'A',
				       (u8)cmd->device->lun,
				       CAM_REQ_ABORTED, SEARCH_COMPLETE) != 0) अणु
		prपूर्णांकk("%s:%d:%d:%d: Command found on untagged queue\n",
		       ahc_name(ahc), cmd->device->channel, cmd->device->id,
		       (u8)cmd->device->lun);
		retval = SUCCESS;
		जाओ करोne;
	पूर्ण

	/*
	 * See अगर we can find a matching cmd in the pending list.
	 */
	LIST_FOREACH(pending_scb, &ahc->pending_scbs, pending_links) अणु
		अगर (pending_scb->io_ctx == cmd)
			अवरोध;
	पूर्ण

	अगर (pending_scb == शून्य && flag == SCB_DEVICE_RESET) अणु

		/* Any SCB क्रम this device will करो क्रम a target reset */
		LIST_FOREACH(pending_scb, &ahc->pending_scbs, pending_links) अणु
			अगर (ahc_match_scb(ahc, pending_scb, scmd_id(cmd),
					  scmd_channel(cmd) + 'A',
					  CAM_LUN_WILDCARD,
					  SCB_LIST_शून्य, ROLE_INITIATOR))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (pending_scb == शून्य) अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Command not found\n");
		जाओ no_cmd;
	पूर्ण

	अगर ((pending_scb->flags & SCB_RECOVERY_SCB) != 0) अणु
		/*
		 * We can't queue two recovery actions using the same SCB
		 */
		retval = FAILED;
		जाओ  करोne;
	पूर्ण

	/*
	 * Ensure that the card करोesn't करो anything
	 * behind our back and that we didn't "just" miss
	 * an पूर्णांकerrupt that would affect this cmd.
	 */
	was_छोड़ोd = ahc_is_छोड़ोd(ahc);
	ahc_छोड़ो_and_flushwork(ahc);
	छोड़ोd = TRUE;

	अगर ((pending_scb->flags & SCB_ACTIVE) == 0) अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Command already completed\n");
		जाओ no_cmd;
	पूर्ण

	prपूर्णांकk("%s: At time of recovery, card was %spaused\n",
	       ahc_name(ahc), was_छोड़ोd ? "" : "not ");
	ahc_dump_card_state(ahc);

	disconnected = TRUE;
	अगर (flag == SCB_ABORT) अणु
		अगर (ahc_search_qinfअगरo(ahc, cmd->device->id,
				       cmd->device->channel + 'A',
				       cmd->device->lun,
				       pending_scb->hscb->tag,
				       ROLE_INITIATOR, CAM_REQ_ABORTED,
				       SEARCH_COMPLETE) > 0) अणु
			prपूर्णांकk("%s:%d:%d:%d: Cmd aborted from QINFIFO\n",
			       ahc_name(ahc), cmd->device->channel,
			       cmd->device->id, (u8)cmd->device->lun);
			retval = SUCCESS;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (ahc_search_qinfअगरo(ahc, cmd->device->id,
				      cmd->device->channel + 'A',
				      cmd->device->lun,
				      pending_scb->hscb->tag,
				      ROLE_INITIATOR, /*status*/0,
				      SEARCH_COUNT) > 0) अणु
		disconnected = FALSE;
	पूर्ण

	अगर (disconnected && (ahc_inb(ahc, SEQ_FLAGS) & NOT_IDENTIFIED) == 0) अणु
		काष्ठा scb *bus_scb;

		bus_scb = ahc_lookup_scb(ahc, ahc_inb(ahc, SCB_TAG));
		अगर (bus_scb == pending_scb)
			disconnected = FALSE;
		अन्यथा अगर (flag != SCB_ABORT
		      && ahc_inb(ahc, SAVED_SCSIID) == pending_scb->hscb->scsiid
		      && ahc_inb(ahc, SAVED_LUN) == SCB_GET_LUN(pending_scb))
			disconnected = FALSE;
	पूर्ण

	/*
	 * At this poपूर्णांक, pending_scb is the scb associated with the
	 * passed in command.  That command is currently active on the
	 * bus, is in the disconnected state, or we're hoping to find
	 * a command क्रम the same target active on the bus to abuse to
	 * send a BDR.  Queue the appropriate message based on which of
	 * these states we are in.
	 */
	last_phase = ahc_inb(ahc, LASTPHASE);
	saved_scbptr = ahc_inb(ahc, SCBPTR);
	active_scb_index = ahc_inb(ahc, SCB_TAG);
	saved_scsiid = ahc_inb(ahc, SAVED_SCSIID);
	अगर (last_phase != P_BUSFREE
	 && (pending_scb->hscb->tag == active_scb_index
	  || (flag == SCB_DEVICE_RESET
	   && SCSIID_TARGET(ahc, saved_scsiid) == scmd_id(cmd)))) अणु

		/*
		 * We're active on the bus, so निश्चित ATN
		 * and hope that the target responds.
		 */
		pending_scb = ahc_lookup_scb(ahc, active_scb_index);
		pending_scb->flags |= SCB_RECOVERY_SCB|flag;
		ahc_outb(ahc, MSG_OUT, HOST_MSG);
		ahc_outb(ahc, SCSISIGO, last_phase|ATNO);
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Device is active, asserting ATN\n");
		रुको = TRUE;
	पूर्ण अन्यथा अगर (disconnected) अणु

		/*
		 * Actually re-queue this SCB in an attempt
		 * to select the device beक्रमe it reconnects.
		 * In either हाल (selection or reselection),
		 * we will now issue the approprate message
		 * to the समयd-out device.
		 *
		 * Set the MK_MESSAGE control bit indicating
		 * that we desire to send a message.  We
		 * also set the disconnected flag since
		 * in the paging हाल there is no guarantee
		 * that our SCB control byte matches the
		 * version on the card.  We करोn't want the
		 * sequencer to पात the command thinking
		 * an unsolicited reselection occurred.
		 */
		pending_scb->hscb->control |= MK_MESSAGE|DISCONNECTED;
		pending_scb->flags |= SCB_RECOVERY_SCB|flag;

		/*
		 * Remove any cached copy of this SCB in the
		 * disconnected list in preparation क्रम the
		 * queuing of our पात SCB.  We use the
		 * same element in the SCB, SCB_NEXT, क्रम
		 * both the qinfअगरo and the disconnected list.
		 */
		ahc_search_disc_list(ahc, cmd->device->id,
				     cmd->device->channel + 'A',
				     cmd->device->lun, pending_scb->hscb->tag,
				     /*stop_on_first*/TRUE,
				     /*हटाओ*/TRUE,
				     /*save_state*/FALSE);

		/*
		 * In the non-paging हाल, the sequencer will
		 * never re-reference the in-core SCB.
		 * To make sure we are notअगरied during
		 * reselection, set the MK_MESSAGE flag in
		 * the card's copy of the SCB.
		 */
		अगर ((ahc->flags & AHC_PAGESCBS) == 0) अणु
			ahc_outb(ahc, SCBPTR, pending_scb->hscb->tag);
			ahc_outb(ahc, SCB_CONTROL,
				 ahc_inb(ahc, SCB_CONTROL)|MK_MESSAGE);
		पूर्ण

		/*
		 * Clear out any entries in the QINFIFO first
		 * so we are the next SCB क्रम this target
		 * to run.
		 */
		ahc_search_qinfअगरo(ahc, cmd->device->id,
				   cmd->device->channel + 'A',
				   cmd->device->lun, SCB_LIST_शून्य,
				   ROLE_INITIATOR, CAM_REQUEUE_REQ,
				   SEARCH_COMPLETE);
		ahc_qinfअगरo_requeue_tail(ahc, pending_scb);
		ahc_outb(ahc, SCBPTR, saved_scbptr);
		ahc_prपूर्णांक_path(ahc, pending_scb);
		prपूर्णांकk("Device is disconnected, re-queuing SCB\n");
		रुको = TRUE;
	पूर्ण अन्यथा अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Unable to deliver message\n");
		retval = FAILED;
		जाओ करोne;
	पूर्ण

no_cmd:
	/*
	 * Our assumption is that अगर we करोn't have the command, no
	 * recovery action was required, so we वापस success.  Again,
	 * the semantics of the mid-layer recovery engine are not
	 * well defined, so this may change in समय.
	 */
	retval = SUCCESS;
करोne:
	अगर (छोड़ोd)
		ahc_unछोड़ो(ahc);
	अगर (रुको) अणु
		DECLARE_COMPLETION_ONSTACK(करोne);

		ahc->platक्रमm_data->eh_करोne = &करोne;
		ahc_unlock(ahc, &flags);

		prपूर्णांकk("Recovery code sleeping\n");
		अगर (!रुको_क्रम_completion_समयout(&करोne, 5 * HZ)) अणु
			ahc_lock(ahc, &flags);
			ahc->platक्रमm_data->eh_करोne = शून्य;
			ahc_unlock(ahc, &flags);

			prपूर्णांकk("Timer Expired\n");
			retval = FAILED;
		पूर्ण
		prपूर्णांकk("Recovery code awake\n");
	पूर्ण अन्यथा
		ahc_unlock(ahc, &flags);
	वापस (retval);
पूर्ण

अटल व्योम ahc_linux_set_width(काष्ठा scsi_target *starget, पूर्णांक width)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित दीर्घ flags;

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahc_lock(ahc, &flags);
	ahc_set_width(ahc, &devinfo, width, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण

अटल व्योम ahc_linux_set_period(काष्ठा scsi_target *starget, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_पंचांगode_tstate *tstate;
	काष्ठा ahc_initiator_tinfo *tinfo
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset = tinfo->goal.offset;
	स्थिर काष्ठा ahc_syncrate *syncrate;

	अगर (offset == 0)
		offset = MAX_OFFSET;

	अगर (period < 9)
		period = 9;	/* 12.5ns is our minimum */
	अगर (period == 9) अणु
		अगर (spi_max_width(starget))
			ppr_options |= MSG_EXT_PPR_DT_REQ;
		अन्यथा
			/* need wide क्रम DT and need DT क्रम 12.5 ns */
			period = 10;
	पूर्ण

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);

	/* all PPR requests apart from QAS require wide transfers */
	अगर (ppr_options & ~MSG_EXT_PPR_QAS_REQ) अणु
		अगर (spi_width(starget) == 0)
			ppr_options &= MSG_EXT_PPR_QAS_REQ;
	पूर्ण

	syncrate = ahc_find_syncrate(ahc, &period, &ppr_options,
				     AHC_SYNCRATE_DT);
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण

अटल व्योम ahc_linux_set_offset(काष्ठा scsi_target *starget, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_पंचांगode_tstate *tstate;
	काष्ठा ahc_initiator_tinfo *tinfo
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = 0;
	अचिन्हित पूर्णांक period = 0;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा ahc_syncrate *syncrate = शून्य;

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	अगर (offset != 0) अणु
		syncrate = ahc_find_syncrate(ahc, &period, &ppr_options,
					     AHC_SYNCRATE_DT);
		period = tinfo->goal.period;
		ppr_options = tinfo->goal.ppr_options;
	पूर्ण
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण

अटल व्योम ahc_linux_set_dt(काष्ठा scsi_target *starget, पूर्णांक dt)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_पंचांगode_tstate *tstate;
	काष्ठा ahc_initiator_tinfo *tinfo
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_DT_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक width = tinfo->goal.width;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा ahc_syncrate *syncrate;

	अगर (dt && spi_max_width(starget)) अणु
		ppr_options |= MSG_EXT_PPR_DT_REQ;
		अगर (!width)
			ahc_linux_set_width(starget, 1);
	पूर्ण अन्यथा अगर (period == 9)
		period = 10;	/* अगर resetting DT, period must be >= 25ns */

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	syncrate = ahc_find_syncrate(ahc, &period, &ppr_options,
				     AHC_SYNCRATE_DT);
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, tinfo->goal.offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण

#अगर 0
/* FIXME: This code claims to support IU and QAS.  However, the actual
 * sequencer code and aic7xxx_core have no support क्रम these parameters and
 * will get पूर्णांकo a bad state अगर they're negotiated.  Do not enable this
 * unless you know what you're करोing */
अटल व्योम ahc_linux_set_qas(काष्ठा scsi_target *starget, पूर्णांक qas)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_पंचांगode_tstate *tstate;
	काष्ठा ahc_initiator_tinfo *tinfo
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_QAS_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित दीर्घ flags;
	काष्ठा ahc_syncrate *syncrate;

	अगर (qas)
		ppr_options |= MSG_EXT_PPR_QAS_REQ;

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	syncrate = ahc_find_syncrate(ahc, &period, &ppr_options,
				     AHC_SYNCRATE_DT);
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, tinfo->goal.offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण

अटल व्योम ahc_linux_set_iu(काष्ठा scsi_target *starget, पूर्णांक iu)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahc_softc *ahc = *((काष्ठा ahc_softc **)shost->hostdata);
	काष्ठा ahc_पंचांगode_tstate *tstate;
	काष्ठा ahc_initiator_tinfo *tinfo
		= ahc_fetch_transinfo(ahc,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahc_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_IU_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित दीर्घ flags;
	काष्ठा ahc_syncrate *syncrate;

	अगर (iu)
		ppr_options |= MSG_EXT_PPR_IU_REQ;

	ahc_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	syncrate = ahc_find_syncrate(ahc, &period, &ppr_options,
				     AHC_SYNCRATE_DT);
	ahc_lock(ahc, &flags);
	ahc_set_syncrate(ahc, &devinfo, syncrate, period, tinfo->goal.offset,
			 ppr_options, AHC_TRANS_GOAL, FALSE);
	ahc_unlock(ahc, &flags);
पूर्ण
#पूर्ण_अगर

अटल व्योम ahc_linux_get_संकेतling(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ahc_softc *ahc = *(काष्ठा ahc_softc **)shost->hostdata;
	अचिन्हित दीर्घ flags;
	u8 mode;

	अगर (!(ahc->features & AHC_ULTRA2)) अणु
		/* non-LVD chipset, may not have SBLKCTL reg */
		spi_संकेतling(shost) =
			ahc->features & AHC_HVD ?
			SPI_SIGNAL_HVD :
			SPI_SIGNAL_SE;
		वापस;
	पूर्ण

	ahc_lock(ahc, &flags);
	ahc_छोड़ो(ahc);
	mode = ahc_inb(ahc, SBLKCTL);
	ahc_unछोड़ो(ahc);
	ahc_unlock(ahc, &flags);

	अगर (mode & ENAB40)
		spi_संकेतling(shost) = SPI_SIGNAL_LVD;
	अन्यथा अगर (mode & ENAB20)
		spi_संकेतling(shost) = SPI_SIGNAL_SE;
	अन्यथा
		spi_संकेतling(shost) = SPI_SIGNAL_UNKNOWN;
पूर्ण

अटल काष्ठा spi_function_ढाँचा ahc_linux_transport_functions = अणु
	.set_offset	= ahc_linux_set_offset,
	.show_offset	= 1,
	.set_period	= ahc_linux_set_period,
	.show_period	= 1,
	.set_width	= ahc_linux_set_width,
	.show_width	= 1,
	.set_dt		= ahc_linux_set_dt,
	.show_dt	= 1,
#अगर 0
	.set_iu		= ahc_linux_set_iu,
	.show_iu	= 1,
	.set_qas	= ahc_linux_set_qas,
	.show_qas	= 1,
#पूर्ण_अगर
	.get_संकेतling	= ahc_linux_get_संकेतling,
पूर्ण;



अटल पूर्णांक __init
ahc_linux_init(व्योम)
अणु
	/*
	 * If we've been passed any parameters, process them now.
	 */
	अगर (aic7xxx)
		aic7xxx_setup(aic7xxx);

	ahc_linux_transport_ढाँचा =
		spi_attach_transport(&ahc_linux_transport_functions);
	अगर (!ahc_linux_transport_ढाँचा)
		वापस -ENODEV;

	scsi_transport_reserve_device(ahc_linux_transport_ढाँचा,
				      माप(काष्ठा ahc_linux_device));

	ahc_linux_pci_init();
	ahc_linux_eisa_init();
	वापस 0;
पूर्ण

अटल व्योम
ahc_linux_निकास(व्योम)
अणु
	ahc_linux_pci_निकास();
	ahc_linux_eisa_निकास();
	spi_release_transport(ahc_linux_transport_ढाँचा);
पूर्ण

module_init(ahc_linux_init);
module_निकास(ahc_linux_निकास);
