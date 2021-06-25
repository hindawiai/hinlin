<शैली गुरु>
/*
 * Adaptec AIC79xx device driver क्रम Linux.
 *
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic79xx_osm.c#171 $
 *
 * --------------------------------------------------------------------------
 * Copyright (c) 1994-2000 Justin T. Gibbs.
 * Copyright (c) 1997-1999 Doug Ledक्रमd
 * Copyright (c) 2000-2003 Adaptec Inc.
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
 */

#समावेश "aic79xx_osm.h"
#समावेश "aic79xx_inline.h"
#समावेश <scsi/scsicam.h>

अटल काष्ठा scsi_transport_ढाँचा *ahd_linux_transport_ढाँचा = शून्य;

#समावेश <linux/init.h>		/* __setup */
#समावेश <linux/mm.h>		/* For fetching प्रणाली memory size */
#समावेश <linux/blkdev.h>		/* For block_size() */
#समावेश <linux/delay.h>	/* For ssleep/msleep */
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

/*
 * Bucket size क्रम counting good commands in between bad ones.
 */
#घोषणा AHD_LINUX_ERR_THRESH	1000

/*
 * Set this to the delay in seconds after SCSI bus reset.
 * Note, we honor this only क्रम the initial bus reset.
 * The scsi error recovery code perक्रमms its own bus settle
 * delay handling क्रम error recovery actions.
 */
#अगर_घोषित CONFIG_AIC79XX_RESET_DELAY_MS
#घोषणा AIC79XX_RESET_DELAY CONFIG_AIC79XX_RESET_DELAY_MS
#अन्यथा
#घोषणा AIC79XX_RESET_DELAY 5000
#पूर्ण_अगर

/*
 * To change the शेष number of tagged transactions allowed per-device,
 * add a line to the lilo.conf file like:
 * append="aic79xx=verbose,tag_info:{{32,32,32,32},{32,32,32,32}}"
 * which will result in the first four devices on the first two
 * controllers being set to a tagged queue depth of 32.
 *
 * The tag_commands is an array of 16 to allow क्रम wide and twin adapters.
 * Twin adapters will use indexes 0-7 क्रम channel 0, and indexes 8-15
 * क्रम channel 1.
 */
प्रकार काष्ठा अणु
	uपूर्णांक16_t tag_commands[16];	/* Allow क्रम wide/twin adapters. */
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
 * the devices on the first probed aic79xx adapter.
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
adapter_tag_info_t aic79xx_tag_info[] =
अणु
	अणुअणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण,
	अणुअणु4, 64, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4पूर्णपूर्ण,
	अणुअणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण,
	अणुअणु0, 16, 4, 0, 16, 4, 4, 4, 127, 4, 4, 4, 4, 4, 4, 4पूर्णपूर्ण
पूर्ण;
*/

#अगर_घोषित CONFIG_AIC79XX_CMDS_PER_DEVICE
#घोषणा AIC79XX_CMDS_PER_DEVICE CONFIG_AIC79XX_CMDS_PER_DEVICE
#अन्यथा
#घोषणा AIC79XX_CMDS_PER_DEVICE AHD_MAX_QUEUE
#पूर्ण_अगर

#घोषणा AIC79XX_CONFIGED_TAG_COMMANDS अणु					\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE,		\
	AIC79XX_CMDS_PER_DEVICE, AIC79XX_CMDS_PER_DEVICE		\
पूर्ण

/*
 * By शेष, use the number of commands specअगरied by
 * the users kernel configuration.
 */
अटल adapter_tag_info_t aic79xx_tag_info[] =
अणु
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण,
	अणुAIC79XX_CONFIGED_TAG_COMMANDSपूर्ण
पूर्ण;

/*
 * The I/O cell on the chip is very configurable in respect to its analog
 * अक्षरacteristics.  Set the शेषs here; they can be overriden with
 * the proper insmod parameters.
 */
काष्ठा ahd_linux_iocell_opts
अणु
	uपूर्णांक8_t	precomp;
	uपूर्णांक8_t	slewrate;
	uपूर्णांक8_t amplitude;
पूर्ण;
#घोषणा AIC79XX_DEFAULT_PRECOMP		0xFF
#घोषणा AIC79XX_DEFAULT_SLEWRATE	0xFF
#घोषणा AIC79XX_DEFAULT_AMPLITUDE	0xFF
#घोषणा AIC79XX_DEFAULT_IOOPTS			\
अणु						\
	AIC79XX_DEFAULT_PRECOMP,		\
	AIC79XX_DEFAULT_SLEWRATE,		\
	AIC79XX_DEFAULT_AMPLITUDE		\
पूर्ण
#घोषणा AIC79XX_PRECOMP_INDEX	0
#घोषणा AIC79XX_SLEWRATE_INDEX	1
#घोषणा AIC79XX_AMPLITUDE_INDEX	2
अटल स्थिर काष्ठा ahd_linux_iocell_opts aic79xx_iocell_info[] =
अणु
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS,
	AIC79XX_DEFAULT_IOOPTS
पूर्ण;

/*
 * There should be a specअगरic वापस value क्रम this in scsi.h, but
 * it seems that most drivers ignore it.
 */
#घोषणा DID_UNDERFLOW   DID_ERROR

व्योम
ahd_prपूर्णांक_path(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	prपूर्णांकk("(scsi%d:%c:%d:%d): ",
	       ahd->platक्रमm_data->host->host_no,
	       scb != शून्य ? SCB_GET_CHANNEL(ahd, scb) : 'X',
	       scb != शून्य ? SCB_GET_TARGET(ahd, scb) : -1,
	       scb != शून्य ? SCB_GET_LUN(scb) : -1);
पूर्ण

/*
 * XXX - these options apply unilaterally to _all_ adapters
 *       cards in the प्रणाली.  This should be fixed.  Exceptions to this
 *       rule are noted in the comments.
 */

/*
 * Skip the scsi bus reset.  Non 0 make us skip the reset at startup.  This
 * has no effect on any later resets that might occur due to things like
 * SCSI bus समयouts.
 */
अटल uपूर्णांक32_t aic79xx_no_reset;

/*
 * Should we क्रमce EXTENDED translation on a controller.
 *     0 == Use whatever is in the SEEPROM or शेष to off
 *     1 == Use whatever is in the SEEPROM or शेष to on
 */
अटल uपूर्णांक32_t aic79xx_extended;

/*
 * PCI bus parity checking of the Adaptec controllers.  This is somewhat
 * dubious at best.  To my knowledge, this option has never actually
 * solved a PCI parity problem, but on certain machines with broken PCI
 * chipset configurations, it can generate tons of false error messages.
 * It's included in the driver क्रम completeness.
 *   0	   = Shut off PCI parity check
 *   non-0 = Enable PCI parity check
 *
 * NOTE: you can't actually pass -1 on the lilo prompt.  So, to set this
 * variable to -1 you would actually want to simply pass the variable
 * name without a number.  That will invert the 0 which will result in
 * -1.
 */
अटल uपूर्णांक32_t aic79xx_pci_parity = ~0;

/*
 * There are lots of broken chipsets in the world.  Some of them will
 * violate the PCI spec when we issue byte sized memory ग_लिखोs to our
 * controller.  I/O mapped रेजिस्टर access, अगर allowed by the given
 * platक्रमm, will work in almost all हालs.
 */
uपूर्णांक32_t aic79xx_allow_memio = ~0;

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
अटल uपूर्णांक32_t aic79xx_selसमय;

/*
 * Certain devices करो not perक्रमm any aging on commands.  Should the
 * device be saturated by commands in one portion of the disk, it is
 * possible क्रम transactions on far away sectors to never be serviced.
 * To handle these devices, we can periodically send an ordered tag to
 * क्रमce all outstanding transactions to be serviced prior to a new
 * transaction.
 */
अटल uपूर्णांक32_t aic79xx_periodic_otag;

/* Some storage boxes are using an LSI chip which has a bug making it
 * impossible to use aic79xx Rev B chip in 320 speeds.  The following
 * storage boxes have been reported to be buggy:
 * EonStor 3U 16-Bay: U16U-G3A3
 * EonStor 2U 12-Bay: U12U-G3A3
 * SentinelRAID: 2500F R5 / R6
 * SentinelRAID: 2500F R1
 * SentinelRAID: 2500F/1500F
 * SentinelRAID: 150F
 * 
 * To get around this LSI bug, you can set your board to 160 mode
 * or you can enable the SLOWCRC bit.
 */
uपूर्णांक32_t aic79xx_slowcrc;

/*
 * Module inक्रमmation and settable options.
 */
अटल अक्षर *aic79xx = शून्य;

MODULE_AUTHOR("Maintainer: Hannes Reinecke <hare@suse.de>");
MODULE_DESCRIPTION("Adaptec AIC790X U320 SCSI Host Bus Adapter driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(AIC79XX_DRIVER_VERSION);
module_param(aic79xx, अक्षरp, 0444);
MODULE_PARM_DESC(aic79xx,
"period-delimited options string:\n"
"	verbose			Enable verbose/diagnostic logging\n"
"	allow_memio		Allow device registers to be memory mapped\n"
"	debug			Bitmask of debug values to enable\n"
"	no_reset		Suppress initial bus resets\n"
"	extended		Enable extended geometry on all controllers\n"
"	periodic_otag		Send an ordered tagged transaction\n"
"				periodically to prevent tag starvation.\n"
"				This may be required by some older disk\n"
"				or drives/RAID arrays.\n"
"	tag_info:<tag_str>	Set per-target tag depth\n"
"	global_tag_depth:<int>	Global tag depth for all targets on all buses\n"
"	slewrate:<slewrate_list>Set the signal slew rate (0-15).\n"
"	precomp:<pcomp_list>	Set the signal precompensation (0-7).\n"
"	amplitude:<int>		Set the signal amplitude (0-7).\n"
"	seltime:<int>		Selection Timeout:\n"
"				(0/256ms,1/128ms,2/64ms,3/32ms)\n"
"	slowcrc			Turn on the SLOWCRC bit (Rev B only)\n"		 
"\n"
"	Sample modprobe configuration file:\n"
"	#	Enable verbose logging\n"
"	#	Set tag depth on Controller 2/Target 2 to 10 tags\n"
"	#	Shorten the selection timeout to 128ms\n"
"\n"
"	options aic79xx 'aic79xx=verbose.tag_info:{{}.{}.{..10}}.seltime:1'\n"
);

अटल व्योम ahd_linux_handle_scsi_status(काष्ठा ahd_softc *,
					 काष्ठा scsi_device *,
					 काष्ठा scb *);
अटल व्योम ahd_linux_queue_cmd_complete(काष्ठा ahd_softc *ahd,
					 काष्ठा scsi_cmnd *cmd);
अटल पूर्णांक ahd_linux_queue_पात_cmd(काष्ठा scsi_cmnd *cmd);
अटल व्योम ahd_linux_initialize_scsi_bus(काष्ठा ahd_softc *ahd);
अटल u_पूर्णांक ahd_linux_user_tagdepth(काष्ठा ahd_softc *ahd,
				     काष्ठा ahd_devinfo *devinfo);
अटल व्योम ahd_linux_device_queue_depth(काष्ठा scsi_device *);
अटल पूर्णांक ahd_linux_run_command(काष्ठा ahd_softc*,
				 काष्ठा ahd_linux_device *,
				 काष्ठा scsi_cmnd *);
अटल व्योम ahd_linux_setup_tag_info_global(अक्षर *p);
अटल पूर्णांक  aic79xx_setup(अक्षर *c);
अटल व्योम ahd_मुक्तze_simq(काष्ठा ahd_softc *ahd);
अटल व्योम ahd_release_simq(काष्ठा ahd_softc *ahd);

अटल पूर्णांक ahd_linux_unit;


/************************** OS Utility Wrappers *******************************/
व्योम ahd_delay(दीर्घ);
व्योम
ahd_delay(दीर्घ usec)
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
uपूर्णांक8_t ahd_inb(काष्ठा ahd_softc * ahd, दीर्घ port);
व्योम ahd_outb(काष्ठा ahd_softc * ahd, दीर्घ port, uपूर्णांक8_t val);
व्योम ahd_outw_atomic(काष्ठा ahd_softc * ahd,
				     दीर्घ port, uपूर्णांक16_t val);
व्योम ahd_outsb(काष्ठा ahd_softc * ahd, दीर्घ port,
			       uपूर्णांक8_t *, पूर्णांक count);
व्योम ahd_insb(काष्ठा ahd_softc * ahd, दीर्घ port,
			       uपूर्णांक8_t *, पूर्णांक count);

uपूर्णांक8_t
ahd_inb(काष्ठा ahd_softc * ahd, दीर्घ port)
अणु
	uपूर्णांक8_t x;

	अगर (ahd->tags[0] == BUS_SPACE_MEMIO) अणु
		x = पढ़ोb(ahd->bshs[0].maddr + port);
	पूर्ण अन्यथा अणु
		x = inb(ahd->bshs[(port) >> 8].ioport + ((port) & 0xFF));
	पूर्ण
	mb();
	वापस (x);
पूर्ण

#अगर 0 /* unused */
अटल uपूर्णांक16_t
ahd_inw_atomic(काष्ठा ahd_softc * ahd, दीर्घ port)
अणु
	uपूर्णांक8_t x;

	अगर (ahd->tags[0] == BUS_SPACE_MEMIO) अणु
		x = पढ़ोw(ahd->bshs[0].maddr + port);
	पूर्ण अन्यथा अणु
		x = inw(ahd->bshs[(port) >> 8].ioport + ((port) & 0xFF));
	पूर्ण
	mb();
	वापस (x);
पूर्ण
#पूर्ण_अगर

व्योम
ahd_outb(काष्ठा ahd_softc * ahd, दीर्घ port, uपूर्णांक8_t val)
अणु
	अगर (ahd->tags[0] == BUS_SPACE_MEMIO) अणु
		ग_लिखोb(val, ahd->bshs[0].maddr + port);
	पूर्ण अन्यथा अणु
		outb(val, ahd->bshs[(port) >> 8].ioport + (port & 0xFF));
	पूर्ण
	mb();
पूर्ण

व्योम
ahd_outw_atomic(काष्ठा ahd_softc * ahd, दीर्घ port, uपूर्णांक16_t val)
अणु
	अगर (ahd->tags[0] == BUS_SPACE_MEMIO) अणु
		ग_लिखोw(val, ahd->bshs[0].maddr + port);
	पूर्ण अन्यथा अणु
		outw(val, ahd->bshs[(port) >> 8].ioport + (port & 0xFF));
	पूर्ण
	mb();
पूर्ण

व्योम
ahd_outsb(काष्ठा ahd_softc * ahd, दीर्घ port, uपूर्णांक8_t *array, पूर्णांक count)
अणु
	पूर्णांक i;

	/*
	 * There is probably a more efficient way to करो this on Linux
	 * but we करोn't use this क्रम anything speed critical and this
	 * should work.
	 */
	क्रम (i = 0; i < count; i++)
		ahd_outb(ahd, port, *array++);
पूर्ण

व्योम
ahd_insb(काष्ठा ahd_softc * ahd, दीर्घ port, uपूर्णांक8_t *array, पूर्णांक count)
अणु
	पूर्णांक i;

	/*
	 * There is probably a more efficient way to करो this on Linux
	 * but we करोn't use this क्रम anything speed critical and this
	 * should work.
	 */
	क्रम (i = 0; i < count; i++)
		*array++ = ahd_inb(ahd, port);
पूर्ण

/******************************* PCI Routines *********************************/
uपूर्णांक32_t
ahd_pci_पढ़ो_config(ahd_dev_softc_t pci, पूर्णांक reg, पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 1:
	अणु
		uपूर्णांक8_t retval;

		pci_पढ़ो_config_byte(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	हाल 2:
	अणु
		uपूर्णांक16_t retval;
		pci_पढ़ो_config_word(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	हाल 4:
	अणु
		uपूर्णांक32_t retval;
		pci_पढ़ो_config_dword(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	शेष:
		panic("ahd_pci_read_config: Read size too big");
		/* NOTREACHED */
		वापस (0);
	पूर्ण
पूर्ण

व्योम
ahd_pci_ग_लिखो_config(ahd_dev_softc_t pci, पूर्णांक reg, uपूर्णांक32_t value, पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 1:
		pci_ग_लिखो_config_byte(pci, reg, value);
		अवरोध;
	हाल 2:
		pci_ग_लिखो_config_word(pci, reg, value);
		अवरोध;
	हाल 4:
		pci_ग_लिखो_config_dword(pci, reg, value);
		अवरोध;
	शेष:
		panic("ahd_pci_write_config: Write size too big");
		/* NOTREACHED */
	पूर्ण
पूर्ण

/****************************** Inlines ***************************************/
अटल व्योम ahd_linux_unmap_scb(काष्ठा ahd_softc*, काष्ठा scb*);

अटल व्योम
ahd_linux_unmap_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा scsi_cmnd *cmd;

	cmd = scb->io_ctx;
	ahd_sync_sglist(ahd, scb, BUS_DMASYNC_POSTWRITE);
	scsi_dma_unmap(cmd);
पूर्ण

/******************************** Macros **************************************/
#घोषणा BUILD_SCSIID(ahd, cmd)						\
	(((scmd_id(cmd) << TID_SHIFT) & TID) | (ahd)->our_id)

/*
 * Return a string describing the driver.
 */
अटल स्थिर अक्षर *
ahd_linux_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर buffer[512];
	अक्षर	ahd_info[256];
	अक्षर   *bp;
	काष्ठा ahd_softc *ahd;

	bp = &buffer[0];
	ahd = *(काष्ठा ahd_softc **)host->hostdata;
	स_रखो(bp, 0, माप(buffer));
	म_नकल(bp, "Adaptec AIC79XX PCI-X SCSI HBA DRIVER, Rev " AIC79XX_DRIVER_VERSION "\n"
			"        <");
	म_जोड़ो(bp, ahd->description);
	म_जोड़ो(bp, ">\n"
			"        ");
	ahd_controller_info(ahd, ahd_info);
	म_जोड़ो(bp, ahd_info);

	वापस (bp);
पूर्ण

/*
 * Queue an SCB to the controller.
 */
अटल पूर्णांक
ahd_linux_queue_lck(काष्ठा scsi_cmnd * cmd, व्योम (*scsi_करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा	 ahd_softc *ahd;
	काष्ठा	 ahd_linux_device *dev = scsi_transport_device_data(cmd->device);
	पूर्णांक rtn = SCSI_MLQUEUE_HOST_BUSY;

	ahd = *(काष्ठा ahd_softc **)cmd->device->host->hostdata;

	cmd->scsi_करोne = scsi_करोne;
	cmd->result = CAM_REQ_INPROG << 16;
	rtn = ahd_linux_run_command(ahd, dev, cmd);

	वापस rtn;
पूर्ण

अटल DEF_SCSI_QCMD(ahd_linux_queue)

अटल काष्ठा scsi_target **
ahd_linux_target_in_softc(काष्ठा scsi_target *starget)
अणु
	काष्ठा	ahd_softc *ahd =
		*((काष्ठा ahd_softc **)dev_to_shost(&starget->dev)->hostdata);
	अचिन्हित पूर्णांक target_offset;

	target_offset = starget->id;
	अगर (starget->channel != 0)
		target_offset += 8;

	वापस &ahd->platक्रमm_data->starget[target_offset];
पूर्ण

अटल पूर्णांक
ahd_linux_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा	ahd_softc *ahd =
		*((काष्ठा ahd_softc **)dev_to_shost(&starget->dev)->hostdata);
	काष्ठा seeprom_config *sc = ahd->seep_config;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_target **ahd_targp = ahd_linux_target_in_softc(starget);
	काष्ठा ahd_devinfo devinfo;
	काष्ठा ahd_initiator_tinfo *tinfo;
	काष्ठा ahd_पंचांगode_tstate *tstate;
	अक्षर channel = starget->channel + 'A';

	ahd_lock(ahd, &flags);

	BUG_ON(*ahd_targp != शून्य);

	*ahd_targp = starget;

	अगर (sc) अणु
		पूर्णांक flags = sc->device_flags[starget->id];

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    starget->id, &tstate);

		अगर ((flags  & CFPACKETIZED) == 0) अणु
			/* करोn't negotiate packetized (IU) transfers */
			spi_max_iu(starget) = 0;
		पूर्ण अन्यथा अणु
			अगर ((ahd->features & AHD_RTI) == 0)
				spi_rti(starget) = 0;
		पूर्ण

		अगर ((flags & CFQAS) == 0)
			spi_max_qas(starget) = 0;

		/* Transinfo values have been set to BIOS settings */
		spi_max_width(starget) = (flags & CFWIDEB) ? 1 : 0;
		spi_min_period(starget) = tinfo->user.period;
		spi_max_offset(starget) = tinfo->user.offset;
	पूर्ण

	tinfo = ahd_fetch_transinfo(ahd, channel, ahd->our_id,
				    starget->id, &tstate);
	ahd_compile_devinfo(&devinfo, ahd->our_id, starget->id,
			    CAM_LUN_WILDCARD, channel,
			    ROLE_INITIATOR);
	ahd_set_syncrate(ahd, &devinfo, 0, 0, 0,
			 AHD_TRANS_GOAL, /*छोड़ोd*/FALSE);
	ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
		      AHD_TRANS_GOAL, /*छोड़ोd*/FALSE);
	ahd_unlock(ahd, &flags);

	वापस 0;
पूर्ण

अटल व्योम
ahd_linux_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा scsi_target **ahd_targp = ahd_linux_target_in_softc(starget);

	*ahd_targp = शून्य;
पूर्ण

अटल पूर्णांक
ahd_linux_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा	ahd_softc *ahd =
		*((काष्ठा ahd_softc **)sdev->host->hostdata);
	काष्ठा ahd_linux_device *dev;

	अगर (bootverbose)
		prपूर्णांकk("%s: Slave Alloc %d\n", ahd_name(ahd), sdev->id);

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
	
	वापस (0);
पूर्ण

अटल पूर्णांक
ahd_linux_slave_configure(काष्ठा scsi_device *sdev)
अणु
	अगर (bootverbose)
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Slave Configure\n");

	ahd_linux_device_queue_depth(sdev);

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
ahd_linux_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		    sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक	 heads;
	पूर्णांक	 sectors;
	पूर्णांक	 cylinders;
	पूर्णांक	 extended;
	काष्ठा	 ahd_softc *ahd;

	ahd = *((काष्ठा ahd_softc **)sdev->host->hostdata);

	अगर (scsi_partsize(bdev, capacity, geom))
		वापस 0;

	heads = 64;
	sectors = 32;
	cylinders = aic_sector_भाग(capacity, heads, sectors);

	अगर (aic79xx_extended != 0)
		extended = 1;
	अन्यथा
		extended = (ahd->flags & AHD_EXTENDED_TRANS_A) != 0;
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
ahd_linux_पात(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक error;
	
	error = ahd_linux_queue_पात_cmd(cmd);

	वापस error;
पूर्ण

/*
 * Attempt to send a target reset message to the device that समयd out.
 */
अटल पूर्णांक
ahd_linux_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ahd_softc *ahd;
	काष्ठा ahd_linux_device *dev;
	काष्ठा scb *reset_scb;
	u_पूर्णांक  cdb_byte;
	पूर्णांक    retval = SUCCESS;
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	अचिन्हित दीर्घ flags;
	DECLARE_COMPLETION_ONSTACK(करोne);

	reset_scb = शून्य;

	ahd = *(काष्ठा ahd_softc **)cmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, cmd,
		    "Attempting to queue a TARGET RESET message:");

	prपूर्णांकk("CDB:");
	क्रम (cdb_byte = 0; cdb_byte < cmd->cmd_len; cdb_byte++)
		prपूर्णांकk(" 0x%x", cmd->cmnd[cdb_byte]);
	prपूर्णांकk("\n");

	/*
	 * Determine अगर we currently own this command.
	 */
	dev = scsi_transport_device_data(cmd->device);

	अगर (dev == शून्य) अणु
		/*
		 * No target device क्रम this command exists,
		 * so we must not still own the command.
		 */
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Is not an active device\n");
		वापस SUCCESS;
	पूर्ण

	/*
	 * Generate us a new SCB
	 */
	reset_scb = ahd_get_scb(ahd, AHD_NEVER_COL_IDX);
	अगर (!reset_scb) अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "No SCB available\n");
		वापस FAILED;
	पूर्ण

	tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
				    cmd->device->id, &tstate);
	reset_scb->io_ctx = cmd;
	reset_scb->platक्रमm_data->dev = dev;
	reset_scb->sg_count = 0;
	ahd_set_residual(reset_scb, 0);
	ahd_set_sense_residual(reset_scb, 0);
	reset_scb->platक्रमm_data->xfer_len = 0;
	reset_scb->hscb->control = 0;
	reset_scb->hscb->scsiid = BUILD_SCSIID(ahd,cmd);
	reset_scb->hscb->lun = cmd->device->lun;
	reset_scb->hscb->cdb_len = 0;
	reset_scb->hscb->task_management = SIU_TASKMGMT_LUN_RESET;
	reset_scb->flags |= SCB_DEVICE_RESET|SCB_RECOVERY_SCB|SCB_ACTIVE;
	अगर ((tinfo->curr.ppr_options & MSG_EXT_PPR_IU_REQ) != 0) अणु
		reset_scb->flags |= SCB_PACKETIZED;
	पूर्ण अन्यथा अणु
		reset_scb->hscb->control |= MK_MESSAGE;
	पूर्ण
	dev->खोलोings--;
	dev->active++;
	dev->commands_issued++;

	ahd_lock(ahd, &flags);

	LIST_INSERT_HEAD(&ahd->pending_scbs, reset_scb, pending_links);
	ahd_queue_scb(ahd, reset_scb);

	ahd->platक्रमm_data->eh_करोne = &करोne;
	ahd_unlock(ahd, &flags);

	prपूर्णांकk("%s: Device reset code sleeping\n", ahd_name(ahd));
	अगर (!रुको_क्रम_completion_समयout(&करोne, 5 * HZ)) अणु
		ahd_lock(ahd, &flags);
		ahd->platक्रमm_data->eh_करोne = शून्य;
		ahd_unlock(ahd, &flags);
		prपूर्णांकk("%s: Device reset timer expired (active %d)\n",
		       ahd_name(ahd), dev->active);
		retval = FAILED;
	पूर्ण
	prपूर्णांकk("%s: Device reset returning 0x%x\n", ahd_name(ahd), retval);

	वापस (retval);
पूर्ण

/*
 * Reset the SCSI bus.
 */
अटल पूर्णांक
ahd_linux_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ahd_softc *ahd;
	पूर्णांक    found;
	अचिन्हित दीर्घ flags;

	ahd = *(काष्ठा ahd_softc **)cmd->device->host->hostdata;
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
		prपूर्णांकk("%s: Bus reset called for cmd %p\n",
		       ahd_name(ahd), cmd);
#पूर्ण_अगर
	ahd_lock(ahd, &flags);

	found = ahd_reset_channel(ahd, scmd_channel(cmd) + 'A',
				  /*initiate reset*/TRUE);
	ahd_unlock(ahd, &flags);

	अगर (bootverbose)
		prपूर्णांकk("%s: SCSI bus reset delivered. "
		       "%d SCBs aborted.\n", ahd_name(ahd), found);

	वापस (SUCCESS);
पूर्ण

काष्ठा scsi_host_ढाँचा aic79xx_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "aic79xx",
	.proc_name		= "aic79xx",
	.show_info		= ahd_linux_show_info,
	.ग_लिखो_info	 	= ahd_proc_ग_लिखो_seeprom,
	.info			= ahd_linux_info,
	.queuecommand		= ahd_linux_queue,
	.eh_पात_handler	= ahd_linux_पात,
	.eh_device_reset_handler = ahd_linux_dev_reset,
	.eh_bus_reset_handler	= ahd_linux_bus_reset,
#अगर defined(__i386__)
	.bios_param		= ahd_linux_biosparam,
#पूर्ण_अगर
	.can_queue		= AHD_MAX_QUEUE,
	.this_id		= -1,
	.max_sectors		= 8192,
	.cmd_per_lun		= 2,
	.slave_alloc		= ahd_linux_slave_alloc,
	.slave_configure	= ahd_linux_slave_configure,
	.target_alloc		= ahd_linux_target_alloc,
	.target_destroy		= ahd_linux_target_destroy,
पूर्ण;

/******************************** Bus DMA *************************************/
पूर्णांक
ahd_dma_tag_create(काष्ठा ahd_softc *ahd, bus_dma_tag_t parent,
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
ahd_dma_tag_destroy(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat)
अणु
	kमुक्त(dmat);
पूर्ण

पूर्णांक
ahd_dmamem_alloc(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat, व्योम** vaddr,
		 पूर्णांक flags, bus_dmamap_t *mapp)
अणु
	*vaddr = dma_alloc_coherent(&ahd->dev_softc->dev, dmat->maxsize, mapp,
				    GFP_ATOMIC);
	अगर (*vaddr == शून्य)
		वापस (ENOMEM);
	वापस(0);
पूर्ण

व्योम
ahd_dmamem_मुक्त(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat,
		व्योम* vaddr, bus_dmamap_t map)
अणु
	dma_मुक्त_coherent(&ahd->dev_softc->dev, dmat->maxsize, vaddr, map);
पूर्ण

पूर्णांक
ahd_dmamap_load(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map,
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
ahd_dmamap_destroy(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map)
अणु
पूर्ण

पूर्णांक
ahd_dmamap_unload(काष्ठा ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map)
अणु
	/* Nothing to करो */
	वापस (0);
पूर्ण

/********************* Platक्रमm Dependent Functions ***************************/
अटल व्योम
ahd_linux_setup_iocell_info(u_दीर्घ index, पूर्णांक instance, पूर्णांक targ, पूर्णांक32_t value)
अणु

	अगर ((instance >= 0)
	 && (instance < ARRAY_SIZE(aic79xx_iocell_info))) अणु
		uपूर्णांक8_t *iocell_info;

		iocell_info = (uपूर्णांक8_t*)&aic79xx_iocell_info[instance];
		iocell_info[index] = value & 0xFFFF;
		अगर (bootverbose)
			prपूर्णांकk("iocell[%d:%ld] = %d\n", instance, index, value);
	पूर्ण
पूर्ण

अटल व्योम
ahd_linux_setup_tag_info_global(अक्षर *p)
अणु
	पूर्णांक tags, i, j;

	tags = simple_म_से_अदीर्घ(p + 1, शून्य, 0) & 0xff;
	prपूर्णांकk("Setting Global Tags= %d\n", tags);

	क्रम (i = 0; i < ARRAY_SIZE(aic79xx_tag_info); i++) अणु
		क्रम (j = 0; j < AHD_NUM_TARGETS; j++) अणु
			aic79xx_tag_info[i].tag_commands[j] = tags;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ahd_linux_setup_tag_info(u_दीर्घ arg, पूर्णांक instance, पूर्णांक targ, पूर्णांक32_t value)
अणु

	अगर ((instance >= 0) && (targ >= 0)
	 && (instance < ARRAY_SIZE(aic79xx_tag_info))
	 && (targ < AHD_NUM_TARGETS)) अणु
		aic79xx_tag_info[instance].tag_commands[targ] = value & 0x1FF;
		अगर (bootverbose)
			prपूर्णांकk("tag_info[%d:%d] = %d\n", instance, targ, value);
	पूर्ण
पूर्ण

अटल अक्षर *
ahd_parse_brace_option(अक्षर *opt_name, अक्षर *opt_arg, अक्षर *end, पूर्णांक depth,
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
 * ie. aic79xx=stpwlev:1,extended
 */
अटल पूर्णांक
aic79xx_setup(अक्षर *s)
अणु
	पूर्णांक	i, n;
	अक्षर   *p;
	अक्षर   *end;

	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		uपूर्णांक32_t *flag;
	पूर्ण options[] = अणु
		अणु "extended", &aic79xx_extended पूर्ण,
		अणु "no_reset", &aic79xx_no_reset पूर्ण,
		अणु "verbose", &aic79xx_verbose पूर्ण,
		अणु "allow_memio", &aic79xx_allow_memioपूर्ण,
#अगर_घोषित AHD_DEBUG
		अणु "debug", &ahd_debug पूर्ण,
#पूर्ण_अगर
		अणु "periodic_otag", &aic79xx_periodic_otag पूर्ण,
		अणु "pci_parity", &aic79xx_pci_parity पूर्ण,
		अणु "seltime", &aic79xx_selसमय पूर्ण,
		अणु "tag_info", शून्य पूर्ण,
		अणु "global_tag_depth", शून्यपूर्ण,
		अणु "slewrate", शून्य पूर्ण,
		अणु "precomp", शून्य पूर्ण,
		अणु "amplitude", शून्य पूर्ण,
		अणु "slowcrc", &aic79xx_slowcrc पूर्ण,
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
			ahd_linux_setup_tag_info_global(p + n);
		पूर्ण अन्यथा अगर (म_भेदन(p, "tag_info", n) == 0) अणु
			s = ahd_parse_brace_option("tag_info", p + n, end,
			    2, ahd_linux_setup_tag_info, 0);
		पूर्ण अन्यथा अगर (म_भेदन(p, "slewrate", n) == 0) अणु
			s = ahd_parse_brace_option("slewrate",
			    p + n, end, 1, ahd_linux_setup_iocell_info,
			    AIC79XX_SLEWRATE_INDEX);
		पूर्ण अन्यथा अगर (म_भेदन(p, "precomp", n) == 0) अणु
			s = ahd_parse_brace_option("precomp",
			    p + n, end, 1, ahd_linux_setup_iocell_info,
			    AIC79XX_PRECOMP_INDEX);
		पूर्ण अन्यथा अगर (म_भेदन(p, "amplitude", n) == 0) अणु
			s = ahd_parse_brace_option("amplitude",
			    p + n, end, 1, ahd_linux_setup_iocell_info,
			    AIC79XX_AMPLITUDE_INDEX);
		पूर्ण अन्यथा अगर (p[n] == ':') अणु
			*(options[i].flag) = simple_म_से_अदीर्घ(p + n + 1, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(p, "verbose", n)) अणु
			*(options[i].flag) = 1;
		पूर्ण अन्यथा अणु
			*(options[i].flag) ^= 0xFFFFFFFF;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("aic79xx=", aic79xx_setup);

uपूर्णांक32_t aic79xx_verbose;

पूर्णांक
ahd_linux_रेजिस्टर_host(काष्ठा ahd_softc *ahd, काष्ठा scsi_host_ढाँचा *ढाँचा)
अणु
	अक्षर	buf[80];
	काष्ठा	Scsi_Host *host;
	अक्षर	*new_name;
	u_दीर्घ	s;
	पूर्णांक	retval;

	ढाँचा->name = ahd->description;
	host = scsi_host_alloc(ढाँचा, माप(काष्ठा ahd_softc *));
	अगर (host == शून्य)
		वापस (ENOMEM);

	*((काष्ठा ahd_softc **)host->hostdata) = ahd;
	ahd->platक्रमm_data->host = host;
	host->can_queue = AHD_MAX_QUEUE;
	host->cmd_per_lun = 2;
	host->sg_tablesize = AHD_NSEG;
	host->this_id = ahd->our_id;
	host->irq = ahd->platक्रमm_data->irq;
	host->max_id = (ahd->features & AHD_WIDE) ? 16 : 8;
	host->max_lun = AHD_NUM_LUNS;
	host->max_channel = 0;
	host->sg_tablesize = AHD_NSEG;
	ahd_lock(ahd, &s);
	ahd_set_unit(ahd, ahd_linux_unit++);
	ahd_unlock(ahd, &s);
	प्र_लिखो(buf, "scsi%d", host->host_no);
	new_name = kदो_स्मृति(म_माप(buf) + 1, GFP_ATOMIC);
	अगर (new_name != शून्य) अणु
		म_नकल(new_name, buf);
		ahd_set_name(ahd, new_name);
	पूर्ण
	host->unique_id = ahd->unit;
	ahd_linux_initialize_scsi_bus(ahd);
	ahd_पूर्णांकr_enable(ahd, TRUE);

	host->transportt = ahd_linux_transport_ढाँचा;

	retval = scsi_add_host(host, &ahd->dev_softc->dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "aic79xx: scsi_add_host failed\n");
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
ahd_linux_initialize_scsi_bus(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक target_id;
	u_पूर्णांक numtarg;
	अचिन्हित दीर्घ s;

	target_id = 0;
	numtarg = 0;

	अगर (aic79xx_no_reset != 0)
		ahd->flags &= ~AHD_RESET_BUS_A;

	अगर ((ahd->flags & AHD_RESET_BUS_A) != 0)
		ahd_reset_channel(ahd, 'A', /*initiate_reset*/TRUE);
	अन्यथा
		numtarg = (ahd->features & AHD_WIDE) ? 16 : 8;

	ahd_lock(ahd, &s);

	/*
	 * Force negotiation to async क्रम all tarमाला_लो that
	 * will not see an initial bus reset.
	 */
	क्रम (; target_id < numtarg; target_id++) अणु
		काष्ठा ahd_devinfo devinfo;
		काष्ठा ahd_initiator_tinfo *tinfo;
		काष्ठा ahd_पंचांगode_tstate *tstate;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    target_id, &tstate);
		ahd_compile_devinfo(&devinfo, ahd->our_id, target_id,
				    CAM_LUN_WILDCARD, 'A', ROLE_INITIATOR);
		ahd_update_neg_request(ahd, &devinfo, tstate,
				       tinfo, AHD_NEG_ALWAYS);
	पूर्ण
	ahd_unlock(ahd, &s);
	/* Give the bus some समय to recover */
	अगर ((ahd->flags & AHD_RESET_BUS_A) != 0) अणु
		ahd_मुक्तze_simq(ahd);
		msleep(AIC79XX_RESET_DELAY);
		ahd_release_simq(ahd);
	पूर्ण
पूर्ण

पूर्णांक
ahd_platक्रमm_alloc(काष्ठा ahd_softc *ahd, व्योम *platक्रमm_arg)
अणु
	ahd->platक्रमm_data =
	    kzalloc(माप(काष्ठा ahd_platक्रमm_data), GFP_ATOMIC);
	अगर (ahd->platक्रमm_data == शून्य)
		वापस (ENOMEM);
	ahd->platक्रमm_data->irq = AHD_LINUX_NOIRQ;
	ahd_lockinit(ahd);
	ahd->selसमय = (aic79xx_selसमय & 0x3) << 4;
	वापस (0);
पूर्ण

व्योम
ahd_platक्रमm_मुक्त(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा scsi_target *starget;
	पूर्णांक i;

	अगर (ahd->platक्रमm_data != शून्य) अणु
		/* destroy all of the device and target objects */
		क्रम (i = 0; i < AHD_NUM_TARGETS; i++) अणु
			starget = ahd->platक्रमm_data->starget[i];
			अगर (starget != शून्य) अणु
				ahd->platक्रमm_data->starget[i] = शून्य;
			पूर्ण
		पूर्ण

		अगर (ahd->platक्रमm_data->irq != AHD_LINUX_NOIRQ)
			मुक्त_irq(ahd->platक्रमm_data->irq, ahd);
		अगर (ahd->tags[0] == BUS_SPACE_PIO
		 && ahd->bshs[0].ioport != 0)
			release_region(ahd->bshs[0].ioport, 256);
		अगर (ahd->tags[1] == BUS_SPACE_PIO
		 && ahd->bshs[1].ioport != 0)
			release_region(ahd->bshs[1].ioport, 256);
		अगर (ahd->tags[0] == BUS_SPACE_MEMIO
		 && ahd->bshs[0].maddr != शून्य) अणु
			iounmap(ahd->bshs[0].maddr);
			release_mem_region(ahd->platक्रमm_data->mem_busaddr,
					   0x1000);
		पूर्ण
		अगर (ahd->platक्रमm_data->host)
			scsi_host_put(ahd->platक्रमm_data->host);

		kमुक्त(ahd->platक्रमm_data);
	पूर्ण
पूर्ण

व्योम
ahd_platक्रमm_init(काष्ठा ahd_softc *ahd)
अणु
	/*
	 * Lookup and commit any modअगरied IO Cell options.
	 */
	अगर (ahd->unit < ARRAY_SIZE(aic79xx_iocell_info)) अणु
		स्थिर काष्ठा ahd_linux_iocell_opts *iocell_opts;

		iocell_opts = &aic79xx_iocell_info[ahd->unit];
		अगर (iocell_opts->precomp != AIC79XX_DEFAULT_PRECOMP)
			AHD_SET_PRECOMP(ahd, iocell_opts->precomp);
		अगर (iocell_opts->slewrate != AIC79XX_DEFAULT_SLEWRATE)
			AHD_SET_SLEWRATE(ahd, iocell_opts->slewrate);
		अगर (iocell_opts->amplitude != AIC79XX_DEFAULT_AMPLITUDE)
			AHD_SET_AMPLITUDE(ahd, iocell_opts->amplitude);
	पूर्ण

पूर्ण

व्योम
ahd_platक्रमm_मुक्तze_devq(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	ahd_platक्रमm_पात_scbs(ahd, SCB_GET_TARGET(ahd, scb),
				SCB_GET_CHANNEL(ahd, scb),
				SCB_GET_LUN(scb), SCB_LIST_शून्य,
				ROLE_UNKNOWN, CAM_REQUEUE_REQ);
पूर्ण

व्योम
ahd_platक्रमm_set_tags(काष्ठा ahd_softc *ahd, काष्ठा scsi_device *sdev,
		      काष्ठा ahd_devinfo *devinfo, ahd_queue_alg alg)
अणु
	काष्ठा ahd_linux_device *dev;
	पूर्णांक was_queuing;
	पूर्णांक now_queuing;

	अगर (sdev == शून्य)
		वापस;

	dev = scsi_transport_device_data(sdev);

	अगर (dev == शून्य)
		वापस;
	was_queuing = dev->flags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED);
	चयन (alg) अणु
	शेष:
	हाल AHD_QUEUE_NONE:
		now_queuing = 0;
		अवरोध; 
	हाल AHD_QUEUE_BASIC:
		now_queuing = AHD_DEV_Q_BASIC;
		अवरोध;
	हाल AHD_QUEUE_TAGGED:
		now_queuing = AHD_DEV_Q_TAGGED;
		अवरोध;
	पूर्ण
	अगर ((dev->flags & AHD_DEV_FREEZE_TIL_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) अणु
		dev->flags |= AHD_DEV_FREEZE_TIL_EMPTY;
		dev->qfrozen++;
	पूर्ण

	dev->flags &= ~(AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED|AHD_DEV_PERIODIC_OTAG);
	अगर (now_queuing) अणु
		u_पूर्णांक usertags;

		usertags = ahd_linux_user_tagdepth(ahd, devinfo);
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
		पूर्ण अन्यथा अगर (alg == AHD_QUEUE_TAGGED) अणु
			dev->flags |= AHD_DEV_Q_TAGGED;
			अगर (aic79xx_periodic_otag != 0)
				dev->flags |= AHD_DEV_PERIODIC_OTAG;
		पूर्ण अन्यथा
			dev->flags |= AHD_DEV_Q_BASIC;
	पूर्ण अन्यथा अणु
		/* We can only have one खोलोing. */
		dev->maxtags = 0;
		dev->खोलोings =  1 - dev->active;
	पूर्ण

	चयन ((dev->flags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED))) अणु
	हाल AHD_DEV_Q_BASIC:
	हाल AHD_DEV_Q_TAGGED:
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
		scsi_change_queue_depth(sdev, 1);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक
ahd_platक्रमm_पात_scbs(काष्ठा ahd_softc *ahd, पूर्णांक target, अक्षर channel,
			पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status)
अणु
	वापस 0;
पूर्ण

अटल u_पूर्णांक
ahd_linux_user_tagdepth(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	अटल पूर्णांक warned_user;
	u_पूर्णांक tags;

	tags = 0;
	अगर ((ahd->user_discenable & devinfo->target_mask) != 0) अणु
		अगर (ahd->unit >= ARRAY_SIZE(aic79xx_tag_info)) अणु

			अगर (warned_user == 0) अणु
				prपूर्णांकk(KERN_WARNING
"aic79xx: WARNING: Insufficient tag_info instances\n"
"aic79xx: for installed controllers.  Using defaults\n"
"aic79xx: Please update the aic79xx_tag_info array in\n"
"aic79xx: the aic79xx_osm.c source file.\n");
				warned_user++;
			पूर्ण
			tags = AHD_MAX_QUEUE;
		पूर्ण अन्यथा अणु
			adapter_tag_info_t *tag_info;

			tag_info = &aic79xx_tag_info[ahd->unit];
			tags = tag_info->tag_commands[devinfo->target_offset];
			अगर (tags > AHD_MAX_QUEUE)
				tags = AHD_MAX_QUEUE;
		पूर्ण
	पूर्ण
	वापस (tags);
पूर्ण

/*
 * Determines the queue depth क्रम a given device.
 */
अटल व्योम
ahd_linux_device_queue_depth(काष्ठा scsi_device *sdev)
अणु
	काष्ठा	ahd_devinfo devinfo;
	u_पूर्णांक	tags;
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)sdev->host->hostdata);

	ahd_compile_devinfo(&devinfo,
			    ahd->our_id,
			    sdev->sdev_target->id, sdev->lun,
			    sdev->sdev_target->channel == 0 ? 'A' : 'B',
			    ROLE_INITIATOR);
	tags = ahd_linux_user_tagdepth(ahd, &devinfo);
	अगर (tags != 0 && sdev->tagged_supported != 0) अणु

		ahd_platक्रमm_set_tags(ahd, sdev, &devinfo, AHD_QUEUE_TAGGED);
		ahd_send_async(ahd, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
		ahd_prपूर्णांक_devinfo(ahd, &devinfo);
		prपूर्णांकk("Tagged Queuing enabled.  Depth %d\n", tags);
	पूर्ण अन्यथा अणु
		ahd_platक्रमm_set_tags(ahd, sdev, &devinfo, AHD_QUEUE_NONE);
		ahd_send_async(ahd, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_linux_run_command(काष्ठा ahd_softc *ahd, काष्ठा ahd_linux_device *dev,
		      काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा	 scb *scb;
	काष्ठा	 hardware_scb *hscb;
	काष्ठा	 ahd_initiator_tinfo *tinfo;
	काष्ठा	 ahd_पंचांगode_tstate *tstate;
	u_पूर्णांक	 col_idx;
	uपूर्णांक16_t mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक nseg;

	nseg = scsi_dma_map(cmd);
	अगर (nseg < 0)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	ahd_lock(ahd, &flags);

	/*
	 * Get an scb to use.
	 */
	tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
				    cmd->device->id, &tstate);
	अगर ((dev->flags & (AHD_DEV_Q_TAGGED|AHD_DEV_Q_BASIC)) == 0
	 || (tinfo->curr.ppr_options & MSG_EXT_PPR_IU_REQ) != 0) अणु
		col_idx = AHD_NEVER_COL_IDX;
	पूर्ण अन्यथा अणु
		col_idx = AHD_BUILD_COL_IDX(cmd->device->id,
					    cmd->device->lun);
	पूर्ण
	अगर ((scb = ahd_get_scb(ahd, col_idx)) == शून्य) अणु
		ahd->flags |= AHD_RESOURCE_SHORTAGE;
		ahd_unlock(ahd, &flags);
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
	hscb->scsiid = BUILD_SCSIID(ahd, cmd);
	hscb->lun = cmd->device->lun;
	scb->hscb->task_management = 0;
	mask = SCB_GET_TARGET_MASK(ahd, scb);

	अगर ((ahd->user_discenable & mask) != 0)
		hscb->control |= DISCENB;

	अगर ((tinfo->curr.ppr_options & MSG_EXT_PPR_IU_REQ) != 0)
		scb->flags |= SCB_PACKETIZED;

	अगर ((tstate->स्वतः_negotiate & mask) != 0) अणु
		scb->flags |= SCB_AUTO_NEGOTIATE;
		scb->hscb->control |= MK_MESSAGE;
	पूर्ण

	अगर ((dev->flags & (AHD_DEV_Q_TAGGED|AHD_DEV_Q_BASIC)) != 0) अणु
		अगर (dev->commands_since_idle_or_otag == AHD_OTAG_THRESH
		 && (dev->flags & AHD_DEV_Q_TAGGED) != 0) अणु
			hscb->control |= ORDERED_QUEUE_TAG;
			dev->commands_since_idle_or_otag = 0;
		पूर्ण अन्यथा अणु
			hscb->control |= SIMPLE_QUEUE_TAG;
		पूर्ण
	पूर्ण

	hscb->cdb_len = cmd->cmd_len;
	स_नकल(hscb->shared_data.idata.cdb, cmd->cmnd, hscb->cdb_len);

	scb->platक्रमm_data->xfer_len = 0;
	ahd_set_residual(scb, 0);
	ahd_set_sense_residual(scb, 0);
	scb->sg_count = 0;

	अगर (nseg > 0) अणु
		व्योम *sg = scb->sg_list;
		काष्ठा scatterlist *cur_seg;
		पूर्णांक i;

		scb->platक्रमm_data->xfer_len = 0;

		scsi_क्रम_each_sg(cmd, cur_seg, nseg, i) अणु
			dma_addr_t addr;
			bus_माप_प्रकार len;

			addr = sg_dma_address(cur_seg);
			len = sg_dma_len(cur_seg);
			scb->platक्रमm_data->xfer_len += len;
			sg = ahd_sg_setup(ahd, scb, sg, addr, len,
					  i == (nseg - 1));
		पूर्ण
	पूर्ण

	LIST_INSERT_HEAD(&ahd->pending_scbs, scb, pending_links);
	dev->खोलोings--;
	dev->active++;
	dev->commands_issued++;

	अगर ((dev->flags & AHD_DEV_PERIODIC_OTAG) != 0)
		dev->commands_since_idle_or_otag++;
	scb->flags |= SCB_ACTIVE;
	ahd_queue_scb(ahd, scb);

	ahd_unlock(ahd, &flags);

	वापस 0;
पूर्ण

/*
 * SCSI controller पूर्णांकerrupt handler.
 */
irqवापस_t
ahd_linux_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा	ahd_softc *ahd;
	u_दीर्घ	flags;
	पूर्णांक	ours;

	ahd = (काष्ठा ahd_softc *) dev_id;
	ahd_lock(ahd, &flags); 
	ours = ahd_पूर्णांकr(ahd);
	ahd_unlock(ahd, &flags);
	वापस IRQ_RETVAL(ours);
पूर्ण

व्योम
ahd_send_async(काष्ठा ahd_softc *ahd, अक्षर channel,
	       u_पूर्णांक target, u_पूर्णांक lun, ac_code code)
अणु
	चयन (code) अणु
	हाल AC_TRANSFER_NEG:
	अणु
		काष्ठा  scsi_target *starget;
		काष्ठा	ahd_initiator_tinfo *tinfo;
		काष्ठा	ahd_पंचांगode_tstate *tstate;
		अचिन्हित पूर्णांक target_ppr_options;

		BUG_ON(target == CAM_TARGET_WILDCARD);

		tinfo = ahd_fetch_transinfo(ahd, channel, ahd->our_id,
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
		starget = ahd->platक्रमm_data->starget[target];
		अगर (starget == शून्य)
			अवरोध;

		target_ppr_options =
			(spi_dt(starget) ? MSG_EXT_PPR_DT_REQ : 0)
			+ (spi_qas(starget) ? MSG_EXT_PPR_QAS_REQ : 0)
			+ (spi_iu(starget) ?  MSG_EXT_PPR_IU_REQ : 0)
			+ (spi_rd_strm(starget) ? MSG_EXT_PPR_RD_STRM : 0)
			+ (spi_pcomp_en(starget) ? MSG_EXT_PPR_PCOMP_EN : 0)
			+ (spi_rti(starget) ? MSG_EXT_PPR_RTI : 0)
			+ (spi_wr_flow(starget) ? MSG_EXT_PPR_WR_FLOW : 0)
			+ (spi_hold_mcs(starget) ? MSG_EXT_PPR_HOLD_MCS : 0);

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
		spi_rd_strm(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_RD_STRM ? 1 : 0;
		spi_pcomp_en(starget) =  tinfo->curr.ppr_options & MSG_EXT_PPR_PCOMP_EN ? 1 : 0;
		spi_rti(starget) =  tinfo->curr.ppr_options &  MSG_EXT_PPR_RTI ? 1 : 0;
		spi_wr_flow(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_WR_FLOW ? 1 : 0;
		spi_hold_mcs(starget) = tinfo->curr.ppr_options & MSG_EXT_PPR_HOLD_MCS ? 1 : 0;
		spi_display_xfer_agreement(starget);
		अवरोध;
	पूर्ण
        हाल AC_SENT_BDR:
	अणु
		WARN_ON(lun != CAM_LUN_WILDCARD);
		scsi_report_device_reset(ahd->platक्रमm_data->host,
					 channel - 'A', target);
		अवरोध;
	पूर्ण
        हाल AC_BUS_RESET:
		अगर (ahd->platक्रमm_data->host != शून्य) अणु
			scsi_report_bus_reset(ahd->platक्रमm_data->host,
					      channel - 'A');
		पूर्ण
                अवरोध;
        शेष:
                panic("ahd_send_async: Unexpected async event");
        पूर्ण
पूर्ण

/*
 * Calls the higher level scsi करोne function and मुक्तs the scb.
 */
व्योम
ahd_करोne(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा	  ahd_linux_device *dev;

	अगर ((scb->flags & SCB_ACTIVE) == 0) अणु
		prपूर्णांकk("SCB %d done'd twice\n", SCB_GET_TAG(scb));
		ahd_dump_card_state(ahd);
		panic("Stopping for safety");
	पूर्ण
	LIST_REMOVE(scb, pending_links);
	cmd = scb->io_ctx;
	dev = scb->platक्रमm_data->dev;
	dev->active--;
	dev->खोलोings++;
	अगर ((cmd->result & (CAM_DEV_QFRZN << 16)) != 0) अणु
		cmd->result &= ~(CAM_DEV_QFRZN << 16);
		dev->qfrozen--;
	पूर्ण
	ahd_linux_unmap_scb(ahd, scb);

	/*
	 * Guard against stale sense data.
	 * The Linux mid-layer assumes that sense
	 * was retrieved anyसमय the first byte of
	 * the sense buffer looks "sane".
	 */
	cmd->sense_buffer[0] = 0;
	अगर (ahd_get_transaction_status(scb) == CAM_REQ_INPROG) अणु
#अगर_घोषित AHD_REPORT_UNDERFLOWS
		uपूर्णांक32_t amount_xferred;

		amount_xferred =
		    ahd_get_transfer_length(scb) - ahd_get_residual(scb);
#पूर्ण_अगर
		अगर ((scb->flags & SCB_TRANSMISSION_ERROR) != 0) अणु
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MISC) != 0) अणु
				ahd_prपूर्णांक_path(ahd, scb);
				prपूर्णांकk("Set CAM_UNCOR_PARITY\n");
			पूर्ण
#पूर्ण_अगर
			ahd_set_transaction_status(scb, CAM_UNCOR_PARITY);
#अगर_घोषित AHD_REPORT_UNDERFLOWS
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

			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("CDB:");
			क्रम (i = 0; i < scb->io_ctx->cmd_len; i++)
				prपूर्णांकk(" 0x%x", scb->io_ctx->cmnd[i]);
			prपूर्णांकk("\n");
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("Saw underflow (%ld of %ld bytes). "
			       "Treated as error\n",
				ahd_get_residual(scb),
				ahd_get_transfer_length(scb));
			ahd_set_transaction_status(scb, CAM_DATA_RUN_ERR);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ahd_set_transaction_status(scb, CAM_REQ_CMP);
		पूर्ण
	पूर्ण अन्यथा अगर (ahd_get_transaction_status(scb) == CAM_SCSI_STATUS_ERROR) अणु
		ahd_linux_handle_scsi_status(ahd, cmd->device, scb);
	पूर्ण

	अगर (dev->खोलोings == 1
	 && ahd_get_transaction_status(scb) == CAM_REQ_CMP
	 && ahd_get_scsi_status(scb) != SAM_STAT_TASK_SET_FULL)
		dev->tag_success_count++;
	/*
	 * Some devices deal with temporary पूर्णांकernal resource
	 * लघुages by वापसing queue full.  When the queue
	 * full occurrs, we throttle back.  Slowly try to get
	 * back to our previous queue depth.
	 */
	अगर ((dev->खोलोings + dev->active) < dev->maxtags
	 && dev->tag_success_count > AHD_TAG_SUCCESS_INTERVAL) अणु
		dev->tag_success_count = 0;
		dev->खोलोings++;
	पूर्ण

	अगर (dev->active == 0)
		dev->commands_since_idle_or_otag = 0;

	अगर ((scb->flags & SCB_RECOVERY_SCB) != 0) अणु
		prपूर्णांकk("Recovery SCB completes\n");
		अगर (ahd_get_transaction_status(scb) == CAM_BDR_SENT
		 || ahd_get_transaction_status(scb) == CAM_REQ_ABORTED)
			ahd_set_transaction_status(scb, CAM_CMD_TIMEOUT);

		अगर (ahd->platक्रमm_data->eh_करोne)
			complete(ahd->platक्रमm_data->eh_करोne);
	पूर्ण

	ahd_मुक्त_scb(ahd, scb);
	ahd_linux_queue_cmd_complete(ahd, cmd);
पूर्ण

अटल व्योम
ahd_linux_handle_scsi_status(काष्ठा ahd_softc *ahd,
			     काष्ठा scsi_device *sdev, काष्ठा scb *scb)
अणु
	काष्ठा	ahd_devinfo devinfo;
	काष्ठा ahd_linux_device *dev = scsi_transport_device_data(sdev);

	ahd_compile_devinfo(&devinfo,
			    ahd->our_id,
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
	चयन (ahd_get_scsi_status(scb)) अणु
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
		अगर ((scb->flags & (SCB_SENSE|SCB_PKT_SENSE)) != 0) अणु
			काष्ठा scsi_status_iu_header *siu;
			u_पूर्णांक sense_size;
			u_पूर्णांक sense_offset;

			अगर (scb->flags & SCB_SENSE) अणु
				sense_size = min(माप(काष्ठा scsi_sense_data)
					       - ahd_get_sense_residual(scb),
						 (u_दीर्घ)SCSI_SENSE_BUFFERSIZE);
				sense_offset = 0;
			पूर्ण अन्यथा अणु
				/*
				 * Copy only the sense data पूर्णांकo the provided
				 * buffer.
				 */
				siu = (काष्ठा scsi_status_iu_header *)
				    scb->sense_data;
				sense_size = min_t(माप_प्रकार,
						scsi_4btoul(siu->sense_length),
						SCSI_SENSE_BUFFERSIZE);
				sense_offset = SIU_SENSE_OFFSET(siu);
			पूर्ण

			स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			स_नकल(cmd->sense_buffer,
			       ahd_get_sense_buf(ahd, scb)
			       + sense_offset, sense_size);
			cmd->result |= (DRIVER_SENSE << 24);

#अगर_घोषित AHD_DEBUG
			अगर (ahd_debug & AHD_SHOW_SENSE) अणु
				पूर्णांक i;

				prपूर्णांकk("Copied %d bytes of sense data at %d:",
				       sense_size, sense_offset);
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
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_QFULL) != 0) अणु
				ahd_prपूर्णांक_path(ahd, scb);
				prपूर्णांकk("Dropping tag count to %d\n",
				       dev->active);
			पूर्ण
#पूर्ण_अगर
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
				 == AHD_LOCK_TAGS_COUNT) अणु
					dev->maxtags = dev->active;
					ahd_prपूर्णांक_path(ahd, scb);
					prपूर्णांकk("Locking max tag count at %d\n",
					       dev->active);
				पूर्ण
			पूर्ण अन्यथा अणु
				dev->tags_on_last_queuefull = dev->active;
				dev->last_queuefull_same_count = 0;
			पूर्ण
			ahd_set_transaction_status(scb, CAM_REQUEUE_REQ);
			ahd_set_scsi_status(scb, SAM_STAT_GOOD);
			ahd_platक्रमm_set_tags(ahd, sdev, &devinfo,
				     (dev->flags & AHD_DEV_Q_BASIC)
				   ? AHD_QUEUE_BASIC : AHD_QUEUE_TAGGED);
			अवरोध;
		पूर्ण
		/*
		 * Drop करोwn to a single खोलोing, and treat this
		 * as अगर the target वापसed BUSY SCSI status.
		 */
		dev->खोलोings = 1;
		ahd_platक्रमm_set_tags(ahd, sdev, &devinfo,
			     (dev->flags & AHD_DEV_Q_BASIC)
			   ? AHD_QUEUE_BASIC : AHD_QUEUE_TAGGED);
		ahd_set_scsi_status(scb, SAM_STAT_BUSY);
	पूर्ण
पूर्ण

अटल व्योम
ahd_linux_queue_cmd_complete(काष्ठा ahd_softc *ahd, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक status;
	पूर्णांक new_status = DID_OK;
	पूर्णांक करो_fallback = 0;
	पूर्णांक scsi_status;

	/*
	 * Map CAM error codes पूर्णांकo Linux Error codes.  We
	 * aव्योम the conversion so that the DV code has the
	 * full error inक्रमmation available when making
	 * state change decisions.
	 */

	status = ahd_cmd_get_transaction_status(cmd);
	चयन (status) अणु
	हाल CAM_REQ_INPROG:
	हाल CAM_REQ_CMP:
		new_status = DID_OK;
		अवरोध;
	हाल CAM_AUTOSENSE_FAIL:
		new_status = DID_ERROR;
		fallthrough;
	हाल CAM_SCSI_STATUS_ERROR:
		scsi_status = ahd_cmd_get_scsi_status(cmd);

		चयन(scsi_status) अणु
		हाल SAM_STAT_COMMAND_TERMINATED:
		हाल SAM_STAT_CHECK_CONDITION:
			अगर ((cmd->result >> 24) != DRIVER_SENSE) अणु
				करो_fallback = 1;
			पूर्ण अन्यथा अणु
				काष्ठा scsi_sense_data *sense;
				
				sense = (काष्ठा scsi_sense_data *)
					cmd->sense_buffer;
				अगर (sense->extra_len >= 5 &&
				    (sense->add_sense_code == 0x47
				     || sense->add_sense_code == 0x48))
					करो_fallback = 1;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
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
		करो_fallback = 1;
		अवरोध;
	हाल CAM_CMD_TIMEOUT:
		new_status = DID_TIME_OUT;
		करो_fallback = 1;
		अवरोध;
	हाल CAM_REQ_CMP_ERR:
	हाल CAM_UNEXP_BUSFREE:
	हाल CAM_DATA_RUN_ERR:
		new_status = DID_ERROR;
		करो_fallback = 1;
		अवरोध;
	हाल CAM_UA_ABORT:
	हाल CAM_NO_HBA:
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

	अगर (करो_fallback) अणु
		prपूर्णांकk("%s: device overrun (status %x) on %d:%d:%d\n",
		       ahd_name(ahd), status, cmd->device->channel,
		       cmd->device->id, (u8)cmd->device->lun);
	पूर्ण

	ahd_cmd_set_transaction_status(cmd, new_status);

	cmd->scsi_करोne(cmd);
पूर्ण

अटल व्योम
ahd_मुक्तze_simq(काष्ठा ahd_softc *ahd)
अणु
	scsi_block_requests(ahd->platक्रमm_data->host);
पूर्ण

अटल व्योम
ahd_release_simq(काष्ठा ahd_softc *ahd)
अणु
	scsi_unblock_requests(ahd->platक्रमm_data->host);
पूर्ण

अटल पूर्णांक
ahd_linux_queue_पात_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ahd_softc *ahd;
	काष्ठा ahd_linux_device *dev;
	काष्ठा scb *pending_scb;
	u_पूर्णांक  saved_scbptr;
	u_पूर्णांक  active_scbptr;
	u_पूर्णांक  last_phase;
	u_पूर्णांक  cdb_byte;
	पूर्णांक    retval = SUCCESS;
	पूर्णांक    was_छोड़ोd;
	पूर्णांक    छोड़ोd;
	पूर्णांक    रुको;
	पूर्णांक    disconnected;
	ahd_mode_state saved_modes;
	अचिन्हित दीर्घ flags;

	pending_scb = शून्य;
	छोड़ोd = FALSE;
	रुको = FALSE;
	ahd = *(काष्ठा ahd_softc **)cmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_INFO, cmd,
		    "Attempting to queue an ABORT message:");

	prपूर्णांकk("CDB:");
	क्रम (cdb_byte = 0; cdb_byte < cmd->cmd_len; cdb_byte++)
		prपूर्णांकk(" 0x%x", cmd->cmnd[cdb_byte]);
	prपूर्णांकk("\n");

	ahd_lock(ahd, &flags);

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
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Is not an active device\n");
		जाओ करोne;
	पूर्ण

	/*
	 * See अगर we can find a matching cmd in the pending list.
	 */
	LIST_FOREACH(pending_scb, &ahd->pending_scbs, pending_links) अणु
		अगर (pending_scb->io_ctx == cmd)
			अवरोध;
	पूर्ण

	अगर (pending_scb == शून्य) अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Command not found\n");
		जाओ करोne;
	पूर्ण

	अगर ((pending_scb->flags & SCB_RECOVERY_SCB) != 0) अणु
		/*
		 * We can't queue two recovery actions using the same SCB
		 */
		retval = FAILED;
		जाओ करोne;
	पूर्ण

	/*
	 * Ensure that the card करोesn't करो anything
	 * behind our back.  Also make sure that we
	 * didn't "just" miss an पूर्णांकerrupt that would
	 * affect this cmd.
	 */
	was_छोड़ोd = ahd_is_छोड़ोd(ahd);
	ahd_छोड़ो_and_flushwork(ahd);
	छोड़ोd = TRUE;

	अगर ((pending_scb->flags & SCB_ACTIVE) == 0) अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Command already completed\n");
		जाओ करोne;
	पूर्ण

	prपूर्णांकk("%s: At time of recovery, card was %spaused\n",
	       ahd_name(ahd), was_छोड़ोd ? "" : "not ");
	ahd_dump_card_state(ahd);

	disconnected = TRUE;
	अगर (ahd_search_qinfअगरo(ahd, cmd->device->id, 
			       cmd->device->channel + 'A',
			       cmd->device->lun,
			       pending_scb->hscb->tag,
			       ROLE_INITIATOR, CAM_REQ_ABORTED,
			       SEARCH_COMPLETE) > 0) अणु
		prपूर्णांकk("%s:%d:%d:%d: Cmd aborted from QINFIFO\n",
		       ahd_name(ahd), cmd->device->channel, 
		       cmd->device->id, (u8)cmd->device->lun);
		जाओ करोne;
	पूर्ण

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	last_phase = ahd_inb(ahd, LASTPHASE);
	saved_scbptr = ahd_get_scbptr(ahd);
	active_scbptr = saved_scbptr;
	अगर (disconnected && (ahd_inb(ahd, SEQ_FLAGS) & NOT_IDENTIFIED) == 0) अणु
		काष्ठा scb *bus_scb;

		bus_scb = ahd_lookup_scb(ahd, active_scbptr);
		अगर (bus_scb == pending_scb)
			disconnected = FALSE;
	पूर्ण

	/*
	 * At this poपूर्णांक, pending_scb is the scb associated with the
	 * passed in command.  That command is currently active on the
	 * bus or is in the disconnected state.
	 */
	ahd_inb(ahd, SAVED_SCSIID);
	अगर (last_phase != P_BUSFREE
	    && SCB_GET_TAG(pending_scb) == active_scbptr) अणु

		/*
		 * We're active on the bus, so निश्चित ATN
		 * and hope that the target responds.
		 */
		pending_scb = ahd_lookup_scb(ahd, active_scbptr);
		pending_scb->flags |= SCB_RECOVERY_SCB|SCB_ABORT;
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		ahd_outb(ahd, SCSISIGO, last_phase|ATNO);
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Device is active, asserting ATN\n");
		रुको = TRUE;
	पूर्ण अन्यथा अगर (disconnected) अणु

		/*
		 * Actually re-queue this SCB in an attempt
		 * to select the device beक्रमe it reconnects.
		 */
		pending_scb->flags |= SCB_RECOVERY_SCB|SCB_ABORT;
		ahd_set_scbptr(ahd, SCB_GET_TAG(pending_scb));
		pending_scb->hscb->cdb_len = 0;
		pending_scb->hscb->task_attribute = 0;
		pending_scb->hscb->task_management = SIU_TASKMGMT_ABORT_TASK;

		अगर ((pending_scb->flags & SCB_PACKETIZED) != 0) अणु
			/*
			 * Mark the SCB has having an outstanding
			 * task management function.  Should the command
			 * complete normally beक्रमe the task management
			 * function can be sent, the host will be notअगरied
			 * to पात our requeued SCB.
			 */
			ahd_outb(ahd, SCB_TASK_MANAGEMENT,
				 pending_scb->hscb->task_management);
		पूर्ण अन्यथा अणु
			/*
			 * If non-packetized, set the MK_MESSAGE control
			 * bit indicating that we desire to send a message.
			 * We also set the disconnected flag since there is
			 * no guarantee that our SCB control byte matches
			 * the version on the card.  We करोn't want the
			 * sequencer to पात the command thinking an
			 * unsolicited reselection occurred.
			 */
			pending_scb->hscb->control |= MK_MESSAGE|DISCONNECTED;

			/*
			 * The sequencer will never re-reference the
			 * in-core SCB.  To make sure we are notअगरied
			 * during reselection, set the MK_MESSAGE flag in
			 * the card's copy of the SCB.
			 */
			ahd_outb(ahd, SCB_CONTROL,
				 ahd_inb(ahd, SCB_CONTROL)|MK_MESSAGE);
		पूर्ण

		/*
		 * Clear out any entries in the QINFIFO first
		 * so we are the next SCB क्रम this target
		 * to run.
		 */
		ahd_search_qinfअगरo(ahd, cmd->device->id,
				   cmd->device->channel + 'A', cmd->device->lun,
				   SCB_LIST_शून्य, ROLE_INITIATOR,
				   CAM_REQUEUE_REQ, SEARCH_COMPLETE);
		ahd_qinfअगरo_requeue_tail(ahd, pending_scb);
		ahd_set_scbptr(ahd, saved_scbptr);
		ahd_prपूर्णांक_path(ahd, pending_scb);
		prपूर्णांकk("Device is disconnected, re-queuing SCB\n");
		रुको = TRUE;
	पूर्ण अन्यथा अणु
		scmd_prपूर्णांकk(KERN_INFO, cmd, "Unable to deliver message\n");
		retval = FAILED;
	पूर्ण


	ahd_restore_modes(ahd, saved_modes);
करोne:
	अगर (छोड़ोd)
		ahd_unछोड़ो(ahd);
	अगर (रुको) अणु
		DECLARE_COMPLETION_ONSTACK(करोne);

		ahd->platक्रमm_data->eh_करोne = &करोne;
		ahd_unlock(ahd, &flags);

		prपूर्णांकk("%s: Recovery code sleeping\n", ahd_name(ahd));
		अगर (!रुको_क्रम_completion_समयout(&करोne, 5 * HZ)) अणु
			ahd_lock(ahd, &flags);
			ahd->platक्रमm_data->eh_करोne = शून्य;
			ahd_unlock(ahd, &flags);
			prपूर्णांकk("%s: Timer Expired (active %d)\n",
			       ahd_name(ahd), dev->active);
			retval = FAILED;
		पूर्ण
		prपूर्णांकk("Recovery code awake\n");
	पूर्ण अन्यथा
		ahd_unlock(ahd, &flags);

	अगर (retval != SUCCESS)
		prपूर्णांकk("%s: Command abort returning 0x%x\n",
		       ahd_name(ahd), retval);

	वापस retval;
पूर्ण

अटल व्योम ahd_linux_set_width(काष्ठा scsi_target *starget, पूर्णांक width)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित दीर्घ flags;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_lock(ahd, &flags);
	ahd_set_width(ahd, &devinfo, width, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_period(काष्ठा scsi_target *starget, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options;
	अचिन्हित पूर्णांक dt;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset = tinfo->goal.offset;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: set period to %d\n", ahd_name(ahd), period);
#पूर्ण_अगर
	अगर (offset == 0)
		offset = MAX_OFFSET;

	अगर (period < 8)
		period = 8;
	अगर (period < 10) अणु
		अगर (spi_max_width(starget)) अणु
			ppr_options |= MSG_EXT_PPR_DT_REQ;
			अगर (period == 8)
				ppr_options |= MSG_EXT_PPR_IU_REQ;
		पूर्ण अन्यथा
			period = 10;
	पूर्ण

	dt = ppr_options & MSG_EXT_PPR_DT_REQ;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);

	/* all PPR requests apart from QAS require wide transfers */
	अगर (ppr_options & ~MSG_EXT_PPR_QAS_REQ) अणु
		अगर (spi_width(starget) == 0)
			ppr_options &= MSG_EXT_PPR_QAS_REQ;
	पूर्ण

	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_offset(काष्ठा scsi_target *starget, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = 0;
	अचिन्हित पूर्णांक period = 0;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: set offset to %d\n", ahd_name(ahd), offset);
#पूर्ण_अगर

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	अगर (offset != 0) अणु
		period = tinfo->goal.period;
		ppr_options = tinfo->goal.ppr_options;
		ahd_find_syncrate(ahd, &period, &ppr_options, 
				  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);
	पूर्ण

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, offset, ppr_options,
			 AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_dt(काष्ठा scsi_target *starget, पूर्णांक dt)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_DT_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक width = tinfo->goal.width;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s DT\n", ahd_name(ahd),
		       dt ? "enabling" : "disabling");
#पूर्ण_अगर
	अगर (dt && spi_max_width(starget)) अणु
		ppr_options |= MSG_EXT_PPR_DT_REQ;
		अगर (!width)
			ahd_linux_set_width(starget, 1);
	पूर्ण अन्यथा अणु
		अगर (period <= 9)
			period = 10; /* If resetting DT, period must be >= 25ns */
		/* IU is invalid without DT set */
		ppr_options &= ~MSG_EXT_PPR_IU_REQ;
	पूर्ण
	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_qas(काष्ठा scsi_target *starget, पूर्णांक qas)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_QAS_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s QAS\n", ahd_name(ahd),
		       qas ? "enabling" : "disabling");
#पूर्ण_अगर

	अगर (qas) अणु
		ppr_options |= MSG_EXT_PPR_QAS_REQ; 
	पूर्ण

	dt = ppr_options & MSG_EXT_PPR_DT_REQ;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_iu(काष्ठा scsi_target *starget, पूर्णांक iu)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_IU_REQ;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s IU\n", ahd_name(ahd),
		       iu ? "enabling" : "disabling");
#पूर्ण_अगर

	अगर (iu && spi_max_width(starget)) अणु
		ppr_options |= MSG_EXT_PPR_IU_REQ;
		ppr_options |= MSG_EXT_PPR_DT_REQ; /* IU requires DT */
	पूर्ण

	dt = ppr_options & MSG_EXT_PPR_DT_REQ;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_rd_strm(काष्ठा scsi_target *starget, पूर्णांक rdstrm)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_RD_STRM;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s Read Streaming\n", ahd_name(ahd),
		       rdstrm  ? "enabling" : "disabling");
#पूर्ण_अगर

	अगर (rdstrm && spi_max_width(starget))
		ppr_options |= MSG_EXT_PPR_RD_STRM;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_wr_flow(काष्ठा scsi_target *starget, पूर्णांक wrflow)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_WR_FLOW;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s Write Flow Control\n", ahd_name(ahd),
		       wrflow ? "enabling" : "disabling");
#पूर्ण_अगर

	अगर (wrflow && spi_max_width(starget))
		ppr_options |= MSG_EXT_PPR_WR_FLOW;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_rti(काष्ठा scsi_target *starget, पूर्णांक rti)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_RTI;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

	अगर ((ahd->features & AHD_RTI) == 0) अणु
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_DV) != 0)
			prपूर्णांकk("%s: RTI not available\n", ahd_name(ahd));
#पूर्ण_अगर
		वापस;
	पूर्ण

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s RTI\n", ahd_name(ahd),
		       rti ? "enabling" : "disabling");
#पूर्ण_अगर

	अगर (rti && spi_max_width(starget))
		ppr_options |= MSG_EXT_PPR_RTI;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_pcomp_en(काष्ठा scsi_target *starget, पूर्णांक pcomp)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_PCOMP_EN;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_DV) != 0)
		prपूर्णांकk("%s: %s Precompensation\n", ahd_name(ahd),
		       pcomp ? "Enable" : "Disable");
#पूर्ण_अगर

	अगर (pcomp && spi_max_width(starget)) अणु
		uपूर्णांक8_t precomp;

		अगर (ahd->unit < ARRAY_SIZE(aic79xx_iocell_info)) अणु
			स्थिर काष्ठा ahd_linux_iocell_opts *iocell_opts;

			iocell_opts = &aic79xx_iocell_info[ahd->unit];
			precomp = iocell_opts->precomp;
		पूर्ण अन्यथा अणु
			precomp = AIC79XX_DEFAULT_PRECOMP;
		पूर्ण
		ppr_options |= MSG_EXT_PPR_PCOMP_EN;
		AHD_SET_PRECOMP(ahd, precomp);
	पूर्ण अन्यथा अणु
		AHD_SET_PRECOMP(ahd, 0);
	पूर्ण

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_set_hold_mcs(काष्ठा scsi_target *starget, पूर्णांक hold)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा ahd_softc *ahd = *((काष्ठा ahd_softc **)shost->hostdata);
	काष्ठा ahd_पंचांगode_tstate *tstate;
	काष्ठा ahd_initiator_tinfo *tinfo 
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	काष्ठा ahd_devinfo devinfo;
	अचिन्हित पूर्णांक ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_HOLD_MCS;
	अचिन्हित पूर्णांक period = tinfo->goal.period;
	अचिन्हित पूर्णांक dt = ppr_options & MSG_EXT_PPR_DT_REQ;
	अचिन्हित दीर्घ flags;

	अगर (hold && spi_max_width(starget))
		ppr_options |= MSG_EXT_PPR_HOLD_MCS;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
पूर्ण

अटल व्योम ahd_linux_get_संकेतling(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ahd_softc *ahd = *(काष्ठा ahd_softc **)shost->hostdata;
	अचिन्हित दीर्घ flags;
	u8 mode;

	ahd_lock(ahd, &flags);
	ahd_छोड़ो(ahd);
	mode = ahd_inb(ahd, SBLKCTL);
	ahd_unछोड़ो(ahd);
	ahd_unlock(ahd, &flags);

	अगर (mode & ENAB40)
		spi_संकेतling(shost) = SPI_SIGNAL_LVD;
	अन्यथा अगर (mode & ENAB20)
		spi_संकेतling(shost) = SPI_SIGNAL_SE;
	अन्यथा
		spi_संकेतling(shost) = SPI_SIGNAL_UNKNOWN;
पूर्ण

अटल काष्ठा spi_function_ढाँचा ahd_linux_transport_functions = अणु
	.set_offset	= ahd_linux_set_offset,
	.show_offset	= 1,
	.set_period	= ahd_linux_set_period,
	.show_period	= 1,
	.set_width	= ahd_linux_set_width,
	.show_width	= 1,
	.set_dt		= ahd_linux_set_dt,
	.show_dt	= 1,
	.set_iu		= ahd_linux_set_iu,
	.show_iu	= 1,
	.set_qas	= ahd_linux_set_qas,
	.show_qas	= 1,
	.set_rd_strm	= ahd_linux_set_rd_strm,
	.show_rd_strm	= 1,
	.set_wr_flow	= ahd_linux_set_wr_flow,
	.show_wr_flow	= 1,
	.set_rti	= ahd_linux_set_rti,
	.show_rti	= 1,
	.set_pcomp_en	= ahd_linux_set_pcomp_en,
	.show_pcomp_en	= 1,
	.set_hold_mcs	= ahd_linux_set_hold_mcs,
	.show_hold_mcs	= 1,
	.get_संकेतling = ahd_linux_get_संकेतling,
पूर्ण;

अटल पूर्णांक __init
ahd_linux_init(व्योम)
अणु
	पूर्णांक	error = 0;

	/*
	 * If we've been passed any parameters, process them now.
	 */
	अगर (aic79xx)
		aic79xx_setup(aic79xx);

	ahd_linux_transport_ढाँचा =
		spi_attach_transport(&ahd_linux_transport_functions);
	अगर (!ahd_linux_transport_ढाँचा)
		वापस -ENODEV;

	scsi_transport_reserve_device(ahd_linux_transport_ढाँचा,
				      माप(काष्ठा ahd_linux_device));

	error = ahd_linux_pci_init();
	अगर (error)
		spi_release_transport(ahd_linux_transport_ढाँचा);
	वापस error;
पूर्ण

अटल व्योम __निकास
ahd_linux_निकास(व्योम)
अणु
	ahd_linux_pci_निकास();
	spi_release_transport(ahd_linux_transport_ढाँचा);
पूर्ण

module_init(ahd_linux_init);
module_निकास(ahd_linux_निकास);
