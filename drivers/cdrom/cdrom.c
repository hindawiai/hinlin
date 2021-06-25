<शैली गुरु>
/* linux/drivers/cdrom/cdrom.c
   Copyright (c) 1996, 1997 David A. van Leeuwen.
   Copyright (c) 1997, 1998 Erik Andersen <andersee@debian.org>
   Copyright (c) 1998, 1999 Jens Axboe <axboe@image.dk>

   May be copied or modअगरied under the terms of the GNU General Public
   License.  See linux/COPYING क्रम more inक्रमmation.

   Unअगरorm CD-ROM driver क्रम Linux.
   See Documentation/cdrom/cdrom-standard.rst क्रम usage inक्रमmation.

   The routines in the file provide a unअगरorm पूर्णांकerface between the
   software that uses CD-ROMs and the various low-level drivers that
   actually talk to the hardware. Suggestions are welcome.
   Patches that work are more welcome though.  ;-)

 To Do List:
 ----------------------------------

 -- Modअगरy sysctl/proc पूर्णांकerface. I plan on having one directory per
 drive, with entries क्रम outputing general drive inक्रमmation, and sysctl
 based tunable parameters such as whether the tray should स्वतः-बंद क्रम
 that drive. Suggestions (or patches) क्रम this welcome!


 Revision History
 ----------------------------------
 1.00  Date Unknown -- David van Leeuwen <david@पंचांग.tno.nl>
 -- Initial version by David A. van Leeuwen. I करोn't have a detailed
  changelog क्रम the 1.x series, David?

2.00  Dec  2, 1997 -- Erik Andersen <andersee@debian.org>
  -- New मुख्यtainer! As David A. van Leeuwen has been too busy to actively
  मुख्यtain and improve this driver, I am now carrying on the torch. If
  you have a problem with this driver, please feel मुक्त to contact me.

  -- Added (rudimentary) sysctl पूर्णांकerface. I realize this is really weak
  right now, and is _very_ badly implemented. It will be improved...

  -- Modअगरied CDROM_DISC_STATUS so that it is now incorporated पूर्णांकo
  the Unअगरorm CD-ROM driver via the cdrom_count_tracks function.
  The cdrom_count_tracks function helps resolve some of the false
  assumptions of the CDROM_DISC_STATUS ioctl, and is also used to check
  क्रम the correct media type when mounting or playing audio from a CD.

  -- Remove the calls to verअगरy_area and only use the copy_from_user and
  copy_to_user stuff, since these calls now provide their own memory
  checking with the 2.1.x kernels.

  -- Major update to वापस codes so that errors from low-level drivers
  are passed on through (thanks to Gerd Knorr क्रम poपूर्णांकing out this
  problem).

  -- Made it so अगर a function isn't implemented in a low-level driver,
  ENOSYS is now वापसed instead of EINVAL.

  -- Simplअगरied some complex logic so that the source code is easier to पढ़ो.

  -- Other stuff I probably क्रमgot to mention (lots of changes).

2.01 to 2.11 Dec 1997-Jan 1998
  -- TO-DO!  Write changelogs क्रम 2.01 to 2.12.

2.12  Jan  24, 1998 -- Erik Andersen <andersee@debian.org>
  -- Fixed a bug in the IOCTL_IN and IOCTL_OUT macros.  It turns out that
  copy_*_user करोes not वापस EFAULT on error, but instead वापसs the number 
  of bytes not copied.  I was वापसing whatever non-zero stuff came back from 
  the copy_*_user functions directly, which would result in strange errors.

2.13  July 17, 1998 -- Erik Andersen <andersee@debian.org>
  -- Fixed a bug in CDROM_SELECT_SPEED where you couldn't lower the speed
  of the drive.  Thanks to Tobias Ringstr|m <tori@prosolvia.se> क्रम poपूर्णांकing
  this out and providing a simple fix.
  -- Fixed the procfs-unload-module bug with the fill_inode procfs callback.
  thanks to Andrea Arcangeli
  -- Fixed it so that the /proc entry now also shows up when cdrom is
  compiled पूर्णांकo the kernel.  Beक्रमe it only worked when loaded as a module.

  2.14 August 17, 1998 -- Erik Andersen <andersee@debian.org>
  -- Fixed a bug in cdrom_media_changed and handling of reporting that
  the media had changed क्रम devices that _करोn't_ implement media_changed.  
  Thanks to Grant R. Guenther <grant@torque.net> क्रम spotting this bug.
  -- Made a few things more pedanticly correct.

2.50 Oct 19, 1998 - Jens Axboe <axboe@image.dk>
  -- New मुख्यtainers! Erik was too busy to जारी the work on the driver,
  so now Chris Zwilling <chris@cloudnet.com> and Jens Axboe <axboe@image.dk>
  will करो their best to follow in his footsteps
  
  2.51 Dec 20, 1998 - Jens Axboe <axboe@image.dk>
  -- Check अगर drive is capable of करोing what we ask beक्रमe blindly changing
  cdi->options in various ioctl.
  -- Added version to proc entry.
  
  2.52 Jan 16, 1999 - Jens Axboe <axboe@image.dk>
  -- Fixed an error in खोलो_क्रम_data where we would someबार not वापस
  the correct error value. Thanks Huba Gaspar <huba@softcell.hu>.
  -- Fixed module usage count - usage was based on /proc/sys/dev
  instead of /proc/sys/dev/cdrom. This could lead to an oops when other
  modules had entries in dev. Feb 02 - real bug was in sysctl.c where
  dev would be हटाओd even though it was used. cdrom.c just illuminated
  that bug.
  
  2.53 Feb 22, 1999 - Jens Axboe <axboe@image.dk>
  -- Fixup of several ioctl calls, in particular CDROM_SET_OPTIONS has
  been "rewritten" because capabilities and options aren't in sync. They
  should be...
  -- Added CDROM_LOCKDOOR ioctl. Locks the करोor and keeps it that way.
  -- Added CDROM_RESET ioctl.
  -- Added CDROM_DEBUG ioctl. Enable debug messages on-the-fly.
  -- Added CDROM_GET_CAPABILITY ioctl. This relieves userspace programs
  from parsing /proc/sys/dev/cdrom/info.
  
  2.54 Mar 15, 1999 - Jens Axboe <axboe@image.dk>
  -- Check capability mask from low level driver when counting tracks as
  per suggestion from Corey J. Scotts <cstotts@blue.weeg.uiowa.edu>.
  
  2.55 Apr 25, 1999 - Jens Axboe <axboe@image.dk>
  -- स्वतःबंद was mistakenly checked against CDC_OPEN_TRAY instead of
  CDC_CLOSE_TRAY.
  -- proc info didn't mask against capabilities mask.
  
  3.00 Aug 5, 1999 - Jens Axboe <axboe@image.dk>
  -- Unअगरied audio ioctl handling across CD-ROM drivers. A lot of the
  code was duplicated beक्रमe. Drives that support the generic packet
  पूर्णांकerface are now being fed packets from here instead.
  -- First attempt at adding support क्रम MMC2 commands - क्रम DVD and
  CD-R(W) drives. Only the DVD parts are in now - the पूर्णांकerface used is
  the same as क्रम the audio ioctls.
  -- ioctl cleanups. अगर a drive couldn't play audio, it didn't get
  a change to perक्रमm device specअगरic ioctls as well.
  -- Defined CDROM_CAN(CDC_XXX) क्रम checking the capabilities.
  -- Put in sysctl files क्रम स्वतःबंद, स्वतःeject, check_media, debug,
  and lock.
  -- /proc/sys/dev/cdrom/info has been updated to also contain info about
  CD-Rx and DVD capabilities.
  -- Now शेष to checking media type.
  -- CDROM_SEND_PACKET ioctl added. The infraकाष्ठाure was in place क्रम
  करोing this anyway, with the generic_packet addition.
  
  3.01 Aug 6, 1999 - Jens Axboe <axboe@image.dk>
  -- Fix up the sysctl handling so that the option flags get set
  correctly.
  -- Fix up ioctl handling so the device specअगरic ones actually get
  called :).
  
  3.02 Aug 8, 1999 - Jens Axboe <axboe@image.dk>
  -- Fixed volume control on SCSI drives (or others with दीर्घer audio
  page).
  -- Fixed a couple of DVD minors. Thanks to Andrew T. Veliath
  <andrewtv@usa.net> क्रम telling me and क्रम having defined the various
  DVD काष्ठाures and ioctls in the first place! He deचिन्हित the original
  DVD patches क्रम ide-cd and जबतक I rearranged and unअगरied them, the
  पूर्णांकerface is still the same.
  
  3.03 Sep 1, 1999 - Jens Axboe <axboe@image.dk>
  -- Moved the rest of the audio ioctls from the CD-ROM drivers here. Only
  CDROMREADTOCENTRY and CDROMREADTOCHDR are left.
  -- Moved the CDROMREADxxx ioctls in here.
  -- Defined the cdrom_get_last_written and cdrom_get_next_block as ioctls
  and exported functions.
  -- Erik Andersen <andersen@xmission.com> modअगरied all SCMD_ commands
  to now पढ़ो GPCMD_ क्रम the new generic packet पूर्णांकerface. All low level
  drivers are updated as well.
  -- Various other cleanups.

  3.04 Sep 12, 1999 - Jens Axboe <axboe@image.dk>
  -- Fixed a couple of possible memory leaks (अगर an operation failed and
  we didn't मुक्त the buffer beक्रमe वापसing the error).
  -- Integrated Unअगरorm CD Changer handling from Riअक्षरd Sharman
  <rsharman@pobox.com>.
  -- Defined CD_DVD and CD_CHANGER log levels.
  -- Fixed the CDROMREADxxx ioctls.
  -- CDROMPLAYTRKIND uses the GPCMD_PLAY_AUDIO_MSF command - too few
  drives supported it. We lose the index part, however.
  -- Small modअगरications to accommodate खोलोs of /dev/hdc1, required
  क्रम ide-cd to handle multisession discs.
  -- Export cdrom_mode_sense and cdrom_mode_select.
  -- init_cdrom_command() क्रम setting up a cgc command.
  
  3.05 Oct 24, 1999 - Jens Axboe <axboe@image.dk>
  -- Changed the पूर्णांकerface क्रम CDROM_SEND_PACKET. Beक्रमe it was भवly
  impossible to send the drive data in a sensible way.
  -- Lowered stack usage in mmc_ioctl(), dvd_पढ़ो_disckey(), and
  dvd_पढ़ो_manufact.
  -- Added setup of ग_लिखो mode क्रम packet writing.
  -- Fixed CDDA ripping with cdda2wav - accept much larger requests of
  number of frames and split the पढ़ोs in blocks of 8.

  3.06 Dec 13, 1999 - Jens Axboe <axboe@image.dk>
  -- Added support क्रम changing the region of DVD drives.
  -- Added sense data to generic command.

  3.07 Feb 2, 2000 - Jens Axboe <axboe@suse.de>
  -- Do same "read header length" trick in cdrom_get_disc_info() as
  we करो in cdrom_get_track_info() -- some drive करोn't obey specs and
  fail अगर they can't supply the full Mt Fuji size table.
  -- Deleted stuff related to setting up ग_लिखो modes. It has a dअगरferent
  home now.
  -- Clear header length in mode_select unconditionally.
  -- Removed the रेजिस्टर_disk() that was added, not needed here.

  3.08 May 1, 2000 - Jens Axboe <axboe@suse.de>
  -- Fix direction flag in setup_send_key and setup_report_key. This
  gave some SCSI adapters problems.
  -- Always वापस -EROFS क्रम ग_लिखो खोलोs
  -- Convert to module_init/module_निकास style init and हटाओ some
  of the #अगर_घोषित MODULE stuff
  -- Fix several dvd errors - DVD_LU_SEND_ASF should pass agid,
  DVD_HOST_SEND_RPC_STATE did not set buffer size in cdb, and
  dvd_करो_auth passed uninitialized data to drive because init_cdrom_command
  did not clear a 0 sized buffer.
  
  3.09 May 12, 2000 - Jens Axboe <axboe@suse.de>
  -- Fix Video-CD on SCSI drives that करोn't support READ_CD command. In
  that हाल चयन block size and issue plain READ_10 again, then चयन
  back.

  3.10 Jun 10, 2000 - Jens Axboe <axboe@suse.de>
  -- Fix volume control on CD's - old SCSI-II drives now use their own
  code, as करोing MODE6 stuff in here is really not my पूर्णांकention.
  -- Use READ_DISC_INFO क्रम more reliable end-of-disc.

  3.11 Jun 12, 2000 - Jens Axboe <axboe@suse.de>
  -- Fix bug in getting rpc phase 2 region info.
  -- Reinstate "correct" CDROMPLAYTRKIND

   3.12 Oct 18, 2000 - Jens Axboe <axboe@suse.de>
  -- Use quiet bit on packet commands not known to work

   3.20 Dec 17, 2003 - Jens Axboe <axboe@suse.de>
  -- Various fixes and lots of cleanups not listed :-)
  -- Locking fixes
  -- Mt Rainier support
  -- DVD-RAM ग_लिखो खोलो fixes

  Nov 5 2001, Aug 8 2002. Modअगरied by Andy Polyakov
  <appro@fy.chalmers.se> to support MMC-3 compliant DVD+RW units.

  Modअगरied by Nigel Kukard <nkukard@lbsd.net> - support DVD+RW
  2.4.x patch by Andy Polyakov <appro@fy.chalmers.se>

-------------------------------------------------------------------------*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा REVISION "Revision: 3.20"
#घोषणा VERSION "Id: cdrom.c 3.20 2003/12/17"

/* I use an error-log mask to give fine grain control over the type of
   messages dumped to the प्रणाली logs.  The available masks include: */
#घोषणा CD_NOTHING      0x0
#घोषणा CD_WARNING	0x1
#घोषणा CD_REG_UNREG	0x2
#घोषणा CD_DO_IOCTL	0x4
#घोषणा CD_OPEN		0x8
#घोषणा CD_CLOSE	0x10
#घोषणा CD_COUNT_TRACKS 0x20
#घोषणा CD_CHANGER	0x40
#घोषणा CD_DVD		0x80

/* Define this to हटाओ _all_ the debugging messages */
/* #घोषणा ERRLOGMASK CD_NOTHING */
#घोषणा ERRLOGMASK CD_WARNING
/* #घोषणा ERRLOGMASK (CD_WARNING|CD_OPEN|CD_COUNT_TRACKS|CD_CLOSE) */
/* #घोषणा ERRLOGMASK (CD_WARNING|CD_REG_UNREG|CD_DO_IOCTL|CD_OPEN|CD_CLOSE|CD_COUNT_TRACKS) */

#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/major.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h> 
#समावेश <linux/cdrom.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/init.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/बार.h>
#समावेश <linux/uaccess.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_request.h>

/* used to tell the module to turn on full debugging messages */
अटल bool debug;
/* शेष compatibility mode */
अटल bool स्वतःबंद=1;
अटल bool स्वतःeject;
अटल bool lockकरोor = 1;
/* will we ever get to use this... sigh. */
अटल bool check_media_type;
/* स्वतःmatically restart mrw क्रमmat */
अटल bool mrw_क्रमmat_restart = 1;
module_param(debug, bool, 0);
module_param(स्वतःबंद, bool, 0);
module_param(स्वतःeject, bool, 0);
module_param(lockकरोor, bool, 0);
module_param(check_media_type, bool, 0);
module_param(mrw_क्रमmat_restart, bool, 0);

अटल DEFINE_MUTEX(cdrom_mutex);

अटल स्थिर अक्षर *mrw_क्रमmat_status[] = अणु
	"not mrw",
	"bgformat inactive",
	"bgformat active",
	"mrw complete",
पूर्ण;

अटल स्थिर अक्षर *mrw_address_space[] = अणु "DMA", "GAA" पूर्ण;

#अगर (ERRLOGMASK != CD_NOTHING)
#घोषणा cd_dbg(type, fmt, ...)				\
करो अणु							\
	अगर ((ERRLOGMASK & type) || debug == 1)		\
		pr_debug(fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा cd_dbg(type, fmt, ...)				\
करो अणु							\
	अगर (0 && (ERRLOGMASK & type) || debug == 1)	\
		pr_debug(fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

/* The (cकरो->capability & ~cdi->mask & CDC_XXX) स्थिरruct was used in
   a lot of places. This macro makes the code more clear. */
#घोषणा CDROM_CAN(type) (cdi->ops->capability & ~cdi->mask & (type))

/*
 * Another popular OS uses 7 seconds as the hard समयout क्रम शेष
 * commands, so it is a good choice क्रम us as well.
 */
#घोषणा CDROM_DEF_TIMEOUT	(7 * HZ)

/* Not-exported routines. */

अटल व्योम cdrom_sysctl_रेजिस्टर(व्योम);

अटल LIST_HEAD(cdrom_list);

पूर्णांक cdrom_dummy_generic_packet(काष्ठा cdrom_device_info *cdi,
			       काष्ठा packet_command *cgc)
अणु
	अगर (cgc->sshdr) अणु
		cgc->sshdr->sense_key = 0x05;
		cgc->sshdr->asc = 0x20;
		cgc->sshdr->ascq = 0x00;
	पूर्ण

	cgc->stat = -EIO;
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(cdrom_dummy_generic_packet);

अटल पूर्णांक cdrom_flush_cache(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FLUSH_CACHE;

	cgc.समयout = 5 * 60 * HZ;

	वापस cdi->ops->generic_packet(cdi, &cgc);
पूर्ण

/* requires CD R/RW */
अटल पूर्णांक cdrom_get_disc_info(काष्ठा cdrom_device_info *cdi,
			       disc_inक्रमmation *di)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा packet_command cgc;
	पूर्णांक ret, buflen;

	/* set up command and get the disc info */
	init_cdrom_command(&cgc, di, माप(*di), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_DISC_INFO;
	cgc.cmd[8] = cgc.buflen = 2;
	cgc.quiet = 1;

	ret = cकरो->generic_packet(cdi, &cgc);
	अगर (ret)
		वापस ret;

	/* not all drives have the same disc_info length, so requeue
	 * packet with the length the drive tells us it can supply
	 */
	buflen = be16_to_cpu(di->disc_inक्रमmation_length) +
		माप(di->disc_inक्रमmation_length);

	अगर (buflen > माप(disc_inक्रमmation))
		buflen = माप(disc_inक्रमmation);

	cgc.cmd[8] = cgc.buflen = buflen;
	ret = cकरो->generic_packet(cdi, &cgc);
	अगर (ret)
		वापस ret;

	/* वापस actual fill size */
	वापस buflen;
पूर्ण

/* This macro makes sure we करोn't have to check on cdrom_device_ops
 * existence in the run-समय routines below. Change_capability is a
 * hack to have the capability flags defined स्थिर, जबतक we can still
 * change it here without gcc complaining at every line.
 */
#घोषणा ENSURE(cकरो, call, bits)					\
करो अणु								\
	अगर (cकरो->call == शून्य)					\
		WARN_ON_ONCE((cकरो)->capability & (bits));	\
पूर्ण जबतक (0)

/*
 * the first prototypes used 0x2c as the page code क्रम the mrw mode page,
 * subsequently this was changed to 0x03. probe the one used by this drive
 */
अटल पूर्णांक cdrom_mrw_probe_pc(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[16];

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.समयout = HZ;
	cgc.quiet = 1;

	अगर (!cdrom_mode_sense(cdi, &cgc, MRW_MODE_PC, 0)) अणु
		cdi->mrw_mode_page = MRW_MODE_PC;
		वापस 0;
	पूर्ण अन्यथा अगर (!cdrom_mode_sense(cdi, &cgc, MRW_MODE_PC_PRE1, 0)) अणु
		cdi->mrw_mode_page = MRW_MODE_PC_PRE1;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक cdrom_is_mrw(काष्ठा cdrom_device_info *cdi, पूर्णांक *ग_लिखो)
अणु
	काष्ठा packet_command cgc;
	काष्ठा mrw_feature_desc *mfd;
	अचिन्हित अक्षर buffer[16];
	पूर्णांक ret;

	*ग_लिखो = 0;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[3] = CDF_MRW;
	cgc.cmd[8] = माप(buffer);
	cgc.quiet = 1;

	अगर ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		वापस ret;

	mfd = (काष्ठा mrw_feature_desc *)&buffer[माप(काष्ठा feature_header)];
	अगर (be16_to_cpu(mfd->feature_code) != CDF_MRW)
		वापस 1;
	*ग_लिखो = mfd->ग_लिखो;

	अगर ((ret = cdrom_mrw_probe_pc(cdi))) अणु
		*ग_लिखो = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_mrw_bgक्रमmat(काष्ठा cdrom_device_info *cdi, पूर्णांक cont)
अणु
	काष्ठा packet_command cgc;
	अचिन्हित अक्षर buffer[12];
	पूर्णांक ret;

	pr_info("%sstarting format\n", cont ? "Re" : "");

	/*
	 * FmtData bit set (bit 4), क्रमmat type is 1
	 */
	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_WRITE);
	cgc.cmd[0] = GPCMD_FORMAT_UNIT;
	cgc.cmd[1] = (1 << 4) | 1;

	cgc.समयout = 5 * 60 * HZ;

	/*
	 * 4 byte क्रमmat list header, 8 byte क्रमmat list descriptor
	 */
	buffer[1] = 1 << 1;
	buffer[3] = 8;

	/*
	 * nr_blocks field
	 */
	buffer[4] = 0xff;
	buffer[5] = 0xff;
	buffer[6] = 0xff;
	buffer[7] = 0xff;

	buffer[8] = 0x24 << 2;
	buffer[11] = cont;

	ret = cdi->ops->generic_packet(cdi, &cgc);
	अगर (ret)
		pr_info("bgformat failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_mrw_bgक्रमmat_susp(काष्ठा cdrom_device_info *cdi, पूर्णांक immed)
अणु
	काष्ठा packet_command cgc;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_CLOSE_TRACK;

	/*
	 * Session = 1, Track = 0
	 */
	cgc.cmd[1] = !!immed;
	cgc.cmd[2] = 1 << 1;

	cgc.समयout = 5 * 60 * HZ;

	वापस cdi->ops->generic_packet(cdi, &cgc);
पूर्ण

अटल पूर्णांक cdrom_mrw_निकास(काष्ठा cdrom_device_info *cdi)
अणु
	disc_inक्रमmation di;
	पूर्णांक ret;

	ret = cdrom_get_disc_info(cdi, &di);
	अगर (ret < 0 || ret < (पूर्णांक)दुरत्व(typeof(di),disc_type))
		वापस 1;

	ret = 0;
	अगर (di.mrw_status == CDM_MRW_BGFORMAT_ACTIVE) अणु
		pr_info("issuing MRW background format suspend\n");
		ret = cdrom_mrw_bgक्रमmat_susp(cdi, 0);
	पूर्ण

	अगर (!ret && cdi->media_written)
		ret = cdrom_flush_cache(cdi);

	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_mrw_set_lba_space(काष्ठा cdrom_device_info *cdi, पूर्णांक space)
अणु
	काष्ठा packet_command cgc;
	काष्ठा mode_page_header *mph;
	अक्षर buffer[16];
	पूर्णांक ret, offset, size;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.buffer = buffer;
	cgc.buflen = माप(buffer);

	ret = cdrom_mode_sense(cdi, &cgc, cdi->mrw_mode_page, 0);
	अगर (ret)
		वापस ret;

	mph = (काष्ठा mode_page_header *)buffer;
	offset = be16_to_cpu(mph->desc_length);
	size = be16_to_cpu(mph->mode_data_length) + 2;

	buffer[offset + 3] = space;
	cgc.buflen = size;

	ret = cdrom_mode_select(cdi, &cgc);
	अगर (ret)
		वापस ret;

	pr_info("%s: mrw address space %s selected\n",
		cdi->name, mrw_address_space[space]);
	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_cdrom(काष्ठा gendisk *disk, काष्ठा cdrom_device_info *cdi)
अणु
	अटल अक्षर banner_prपूर्णांकed;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	cd_dbg(CD_OPEN, "entering register_cdrom\n");

	अगर (cकरो->खोलो == शून्य || cकरो->release == शून्य)
		वापस -EINVAL;
	अगर (!banner_prपूर्णांकed) अणु
		pr_info("Uniform CD-ROM driver " REVISION "\n");
		banner_prपूर्णांकed = 1;
		cdrom_sysctl_रेजिस्टर();
	पूर्ण

	cdi->disk = disk;
	disk->cdi = cdi;

	ENSURE(cकरो, drive_status, CDC_DRIVE_STATUS);
	अगर (cकरो->check_events == शून्य)
		WARN_ON_ONCE(cकरो->capability & (CDC_MEDIA_CHANGED | CDC_SELECT_DISC));
	ENSURE(cकरो, tray_move, CDC_CLOSE_TRAY | CDC_OPEN_TRAY);
	ENSURE(cकरो, lock_करोor, CDC_LOCK);
	ENSURE(cकरो, select_speed, CDC_SELECT_SPEED);
	ENSURE(cकरो, get_last_session, CDC_MULTI_SESSION);
	ENSURE(cकरो, get_mcn, CDC_MCN);
	ENSURE(cकरो, reset, CDC_RESET);
	ENSURE(cकरो, generic_packet, CDC_GENERIC_PACKET);
	cdi->mc_flags = 0;
	cdi->options = CDO_USE_FFLAGS;

	अगर (स्वतःबंद == 1 && CDROM_CAN(CDC_CLOSE_TRAY))
		cdi->options |= (पूर्णांक) CDO_AUTO_CLOSE;
	अगर (स्वतःeject == 1 && CDROM_CAN(CDC_OPEN_TRAY))
		cdi->options |= (पूर्णांक) CDO_AUTO_EJECT;
	अगर (lockकरोor == 1)
		cdi->options |= (पूर्णांक) CDO_LOCK;
	अगर (check_media_type == 1)
		cdi->options |= (पूर्णांक) CDO_CHECK_TYPE;

	अगर (CDROM_CAN(CDC_MRW_W))
		cdi->निकास = cdrom_mrw_निकास;

	अगर (cdi->disk)
		cdi->cdda_method = CDDA_BPC_FULL;
	अन्यथा
		cdi->cdda_method = CDDA_OLD;

	WARN_ON(!cकरो->generic_packet);

	cd_dbg(CD_REG_UNREG, "drive \"/dev/%s\" registered\n", cdi->name);
	mutex_lock(&cdrom_mutex);
	list_add(&cdi->list, &cdrom_list);
	mutex_unlock(&cdrom_mutex);
	वापस 0;
पूर्ण
#अघोषित ENSURE

व्योम unरेजिस्टर_cdrom(काष्ठा cdrom_device_info *cdi)
अणु
	cd_dbg(CD_OPEN, "entering unregister_cdrom\n");

	mutex_lock(&cdrom_mutex);
	list_del(&cdi->list);
	mutex_unlock(&cdrom_mutex);

	अगर (cdi->निकास)
		cdi->निकास(cdi);

	cd_dbg(CD_REG_UNREG, "drive \"/dev/%s\" unregistered\n", cdi->name);
पूर्ण

पूर्णांक cdrom_get_media_event(काष्ठा cdrom_device_info *cdi,
			  काष्ठा media_event_desc *med)
अणु
	काष्ठा packet_command cgc;
	अचिन्हित अक्षर buffer[8];
	काष्ठा event_header *eh = (काष्ठा event_header *)buffer;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_GET_EVENT_STATUS_NOTIFICATION;
	cgc.cmd[1] = 1;		/* IMMED */
	cgc.cmd[4] = 1 << 4;	/* media event */
	cgc.cmd[8] = माप(buffer);
	cgc.quiet = 1;

	अगर (cdi->ops->generic_packet(cdi, &cgc))
		वापस 1;

	अगर (be16_to_cpu(eh->data_len) < माप(*med))
		वापस 1;

	अगर (eh->nea || eh->notअगरication_class != 0x4)
		वापस 1;

	स_नकल(med, &buffer[माप(*eh)], माप(*med));
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_get_अक्रमom_writable(काष्ठा cdrom_device_info *cdi,
			      काष्ठा rwrt_feature_desc *rfd)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[24];
	पूर्णांक ret;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;	/* often 0x46 */
	cgc.cmd[3] = CDF_RWRT;			/* often 0x0020 */
	cgc.cmd[8] = माप(buffer);		/* often 0x18 */
	cgc.quiet = 1;

	अगर ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		वापस ret;

	स_नकल(rfd, &buffer[माप(काष्ठा feature_header)], माप (*rfd));
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_has_defect_mgt(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[16];
	__be16 *feature_code;
	पूर्णांक ret;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[3] = CDF_HWDM;
	cgc.cmd[8] = माप(buffer);
	cgc.quiet = 1;

	अगर ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		वापस ret;

	feature_code = (__be16 *) &buffer[माप(काष्ठा feature_header)];
	अगर (be16_to_cpu(*feature_code) == CDF_HWDM)
		वापस 0;

	वापस 1;
पूर्ण


अटल पूर्णांक cdrom_is_अक्रमom_writable(काष्ठा cdrom_device_info *cdi, पूर्णांक *ग_लिखो)
अणु
	काष्ठा rwrt_feature_desc rfd;
	पूर्णांक ret;

	*ग_लिखो = 0;

	अगर ((ret = cdrom_get_अक्रमom_writable(cdi, &rfd)))
		वापस ret;

	अगर (CDF_RWRT == be16_to_cpu(rfd.feature_code))
		*ग_लिखो = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_media_erasable(काष्ठा cdrom_device_info *cdi)
अणु
	disc_inक्रमmation di;
	पूर्णांक ret;

	ret = cdrom_get_disc_info(cdi, &di);
	अगर (ret < 0 || ret < दुरत्व(typeof(di), n_first_track))
		वापस -1;

	वापस di.erasable;
पूर्ण

/*
 * FIXME: check RO bit
 */
अटल पूर्णांक cdrom_dvdram_खोलो_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	पूर्णांक ret = cdrom_media_erasable(cdi);

	/*
	 * allow writable खोलो अगर media info पढ़ो worked and media is
	 * erasable, _or_ अगर it fails since not all drives support it
	 */
	अगर (!ret)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_mrw_खोलो_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	disc_inक्रमmation di;
	पूर्णांक ret;

	/*
	 * always reset to DMA lba space on खोलो
	 */
	अगर (cdrom_mrw_set_lba_space(cdi, MRW_LBA_DMA)) अणु
		pr_err("failed setting lba address space\n");
		वापस 1;
	पूर्ण

	ret = cdrom_get_disc_info(cdi, &di);
	अगर (ret < 0 || ret < दुरत्व(typeof(di),disc_type))
		वापस 1;

	अगर (!di.erasable)
		वापस 1;

	/*
	 * mrw_status
	 * 0	-	not MRW क्रमmatted
	 * 1	-	MRW bgक्रमmat started, but not running or complete
	 * 2	-	MRW bgक्रमmat in progress
	 * 3	-	MRW क्रमmatting complete
	 */
	ret = 0;
	pr_info("open: mrw_status '%s'\n", mrw_क्रमmat_status[di.mrw_status]);
	अगर (!di.mrw_status)
		ret = 1;
	अन्यथा अगर (di.mrw_status == CDM_MRW_BGFORMAT_INACTIVE &&
			mrw_क्रमmat_restart)
		ret = cdrom_mrw_bgक्रमmat(cdi, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक mo_खोलो_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[255];
	पूर्णांक ret;

	init_cdrom_command(&cgc, &buffer, 4, CGC_DATA_READ);
	cgc.quiet = 1;

	/*
	 * obtain ग_लिखो protect inक्रमmation as per
	 * drivers/scsi/sd.c:sd_पढ़ो_ग_लिखो_protect_flag
	 */

	ret = cdrom_mode_sense(cdi, &cgc, GPMODE_ALL_PAGES, 0);
	अगर (ret)
		ret = cdrom_mode_sense(cdi, &cgc, GPMODE_VENDOR_PAGE, 0);
	अगर (ret) अणु
		cgc.buflen = 255;
		ret = cdrom_mode_sense(cdi, &cgc, GPMODE_ALL_PAGES, 0);
	पूर्ण

	/* drive gave us no info, let the user go ahead */
	अगर (ret)
		वापस 0;

	वापस buffer[3] & 0x80;
पूर्ण

अटल पूर्णांक cdrom_ram_खोलो_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा rwrt_feature_desc rfd;
	पूर्णांक ret;

	अगर ((ret = cdrom_has_defect_mgt(cdi)))
		वापस ret;

	अगर ((ret = cdrom_get_अक्रमom_writable(cdi, &rfd)))
		वापस ret;
	अन्यथा अगर (CDF_RWRT == be16_to_cpu(rfd.feature_code))
		ret = !rfd.curr;

	cd_dbg(CD_OPEN, "can open for random write\n");
	वापस ret;
पूर्ण

अटल व्योम cdrom_mmc3_profile(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;
	अक्षर buffer[32];
	पूर्णांक ret, mmc3_profile;

	init_cdrom_command(&cgc, buffer, माप(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[1] = 0;
	cgc.cmd[2] = cgc.cmd[3] = 0;		/* Starting Feature Number */
	cgc.cmd[8] = माप(buffer);		/* Allocation Length */
	cgc.quiet = 1;

	अगर ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		mmc3_profile = 0xffff;
	अन्यथा
		mmc3_profile = (buffer[6] << 8) | buffer[7];

	cdi->mmc3_profile = mmc3_profile;
पूर्ण

अटल पूर्णांक cdrom_is_dvd_rw(काष्ठा cdrom_device_info *cdi)
अणु
	चयन (cdi->mmc3_profile) अणु
	हाल 0x12:	/* DVD-RAM	*/
	हाल 0x1A:	/* DVD+RW	*/
	हाल 0x43:	/* BD-RE	*/
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

/*
 * वापसs 0 क्रम ok to खोलो ग_लिखो, non-0 to disallow
 */
अटल पूर्णांक cdrom_खोलो_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	पूर्णांक mrw, mrw_ग_लिखो, ram_ग_लिखो;
	पूर्णांक ret = 1;

	mrw = 0;
	अगर (!cdrom_is_mrw(cdi, &mrw_ग_लिखो))
		mrw = 1;

	अगर (CDROM_CAN(CDC_MO_DRIVE))
		ram_ग_लिखो = 1;
	अन्यथा
		(व्योम) cdrom_is_अक्रमom_writable(cdi, &ram_ग_लिखो);
	
	अगर (mrw)
		cdi->mask &= ~CDC_MRW;
	अन्यथा
		cdi->mask |= CDC_MRW;

	अगर (mrw_ग_लिखो)
		cdi->mask &= ~CDC_MRW_W;
	अन्यथा
		cdi->mask |= CDC_MRW_W;

	अगर (ram_ग_लिखो)
		cdi->mask &= ~CDC_RAM;
	अन्यथा
		cdi->mask |= CDC_RAM;

	अगर (CDROM_CAN(CDC_MRW_W))
		ret = cdrom_mrw_खोलो_ग_लिखो(cdi);
	अन्यथा अगर (CDROM_CAN(CDC_DVD_RAM))
		ret = cdrom_dvdram_खोलो_ग_लिखो(cdi);
 	अन्यथा अगर (CDROM_CAN(CDC_RAM) &&
 		 !CDROM_CAN(CDC_CD_R|CDC_CD_RW|CDC_DVD|CDC_DVD_R|CDC_MRW|CDC_MO_DRIVE))
 		ret = cdrom_ram_खोलो_ग_लिखो(cdi);
	अन्यथा अगर (CDROM_CAN(CDC_MO_DRIVE))
		ret = mo_खोलो_ग_लिखो(cdi);
	अन्यथा अगर (!cdrom_is_dvd_rw(cdi))
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम cdrom_dvd_rw_बंद_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
	काष्ठा packet_command cgc;

	अगर (cdi->mmc3_profile != 0x1a) अणु
		cd_dbg(CD_CLOSE, "%s: No DVD+RW\n", cdi->name);
		वापस;
	पूर्ण

	अगर (!cdi->media_written) अणु
		cd_dbg(CD_CLOSE, "%s: DVD+RW media clean\n", cdi->name);
		वापस;
	पूर्ण

	pr_info("%s: dirty DVD+RW media, \"finalizing\"\n", cdi->name);

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_FLUSH_CACHE;
	cgc.समयout = 30*HZ;
	cdi->ops->generic_packet(cdi, &cgc);

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_CLOSE_TRACK;
	cgc.समयout = 3000*HZ;
	cgc.quiet = 1;
	cdi->ops->generic_packet(cdi, &cgc);

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_CLOSE_TRACK;
	cgc.cmd[2] = 2;	 /* Close session */
	cgc.quiet = 1;
	cgc.समयout = 3000*HZ;
	cdi->ops->generic_packet(cdi, &cgc);

	cdi->media_written = 0;
पूर्ण

अटल पूर्णांक cdrom_बंद_ग_लिखो(काष्ठा cdrom_device_info *cdi)
अणु
#अगर 0
	वापस cdrom_flush_cache(cdi);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* badly broken, I know. Is due क्रम a fixup anyसमय. */
अटल व्योम cdrom_count_tracks(काष्ठा cdrom_device_info *cdi, tracktype *tracks)
अणु
	काष्ठा cdrom_tochdr header;
	काष्ठा cdrom_tocentry entry;
	पूर्णांक ret, i;
	tracks->data = 0;
	tracks->audio = 0;
	tracks->cdi = 0;
	tracks->xa = 0;
	tracks->error = 0;
	cd_dbg(CD_COUNT_TRACKS, "entering cdrom_count_tracks\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO)) अणु
		tracks->error = CDS_NO_INFO;
		वापस;
	पूर्ण

	/* Grab the TOC header so we can see how many tracks there are */
	ret = cdi->ops->audio_ioctl(cdi, CDROMREADTOCHDR, &header);
	अगर (ret) अणु
		अगर (ret == -ENOMEDIUM)
			tracks->error = CDS_NO_DISC;
		अन्यथा
			tracks->error = CDS_NO_INFO;
		वापस;
	पूर्ण
	/* check what type of tracks are on this disc */
	entry.cdte_क्रमmat = CDROM_MSF;
	क्रम (i = header.cdth_trk0; i <= header.cdth_trk1; i++) अणु
		entry.cdte_track = i;
		अगर (cdi->ops->audio_ioctl(cdi, CDROMREADTOCENTRY, &entry)) अणु
			tracks->error = CDS_NO_INFO;
			वापस;
		पूर्ण
		अगर (entry.cdte_ctrl & CDROM_DATA_TRACK) अणु
			अगर (entry.cdte_क्रमmat == 0x10)
				tracks->cdi++;
			अन्यथा अगर (entry.cdte_क्रमmat == 0x20)
				tracks->xa++;
			अन्यथा
				tracks->data++;
		पूर्ण अन्यथा अणु
			tracks->audio++;
		पूर्ण
		cd_dbg(CD_COUNT_TRACKS, "track %d: format=%d, ctrl=%d\n",
		       i, entry.cdte_क्रमmat, entry.cdte_ctrl);
	पूर्ण
	cd_dbg(CD_COUNT_TRACKS, "disc has %d tracks: %d=audio %d=data %d=Cd-I %d=XA\n",
	       header.cdth_trk1, tracks->audio, tracks->data,
	       tracks->cdi, tracks->xa);
पूर्ण

अटल
पूर्णांक खोलो_क्रम_data(काष्ठा cdrom_device_info *cdi)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	tracktype tracks;
	cd_dbg(CD_OPEN, "entering open_for_data\n");
	/* Check अगर the driver can report drive status.  If it can, we
	   can करो clever things.  If it can't, well, we at least tried! */
	अगर (cकरो->drive_status != शून्य) अणु
		ret = cकरो->drive_status(cdi, CDSL_CURRENT);
		cd_dbg(CD_OPEN, "drive_status=%d\n", ret);
		अगर (ret == CDS_TRAY_OPEN) अणु
			cd_dbg(CD_OPEN, "the tray is open...\n");
			/* can/may i बंद it? */
			अगर (CDROM_CAN(CDC_CLOSE_TRAY) &&
			    cdi->options & CDO_AUTO_CLOSE) अणु
				cd_dbg(CD_OPEN, "trying to close the tray\n");
				ret=cकरो->tray_move(cdi,0);
				अगर (ret) अणु
					cd_dbg(CD_OPEN, "bummer. tried to close the tray but failed.\n");
					/* Ignore the error from the low
					level driver.  We करोn't care why it
					couldn't बंद the tray.  We only care 
					that there is no disc in the drive, 
					since that is the _REAL_ problem here.*/
					ret=-ENOMEDIUM;
					जाओ clean_up_and_वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				cd_dbg(CD_OPEN, "bummer. this drive can't close the tray.\n");
				ret=-ENOMEDIUM;
				जाओ clean_up_and_वापस;
			पूर्ण
			/* Ok, the करोor should be बंदd now.. Check again */
			ret = cकरो->drive_status(cdi, CDSL_CURRENT);
			अगर ((ret == CDS_NO_DISC) || (ret==CDS_TRAY_OPEN)) अणु
				cd_dbg(CD_OPEN, "bummer. the tray is still not closed.\n");
				cd_dbg(CD_OPEN, "tray might not contain a medium\n");
				ret=-ENOMEDIUM;
				जाओ clean_up_and_वापस;
			पूर्ण
			cd_dbg(CD_OPEN, "the tray is now closed\n");
		पूर्ण
		/* the करोor should be बंदd now, check क्रम the disc */
		ret = cकरो->drive_status(cdi, CDSL_CURRENT);
		अगर (ret!=CDS_DISC_OK) अणु
			ret = -ENOMEDIUM;
			जाओ clean_up_and_वापस;
		पूर्ण
	पूर्ण
	cdrom_count_tracks(cdi, &tracks);
	अगर (tracks.error == CDS_NO_DISC) अणु
		cd_dbg(CD_OPEN, "bummer. no disc.\n");
		ret=-ENOMEDIUM;
		जाओ clean_up_and_वापस;
	पूर्ण
	/* CD-Players which करोn't use O_NONBLOCK, workman
	 * क्रम example, need bit CDO_CHECK_TYPE cleared! */
	अगर (tracks.data==0) अणु
		अगर (cdi->options & CDO_CHECK_TYPE) अणु
		    /* give people a warning shot, now that CDO_CHECK_TYPE
		       is the शेष हाल! */
		    cd_dbg(CD_OPEN, "bummer. wrong media type.\n");
		    cd_dbg(CD_WARNING, "pid %d must open device O_NONBLOCK!\n",
			   (अचिन्हित पूर्णांक)task_pid_nr(current));
		    ret=-EMEDIUMTYPE;
		    जाओ clean_up_and_वापस;
		पूर्ण
		अन्यथा अणु
		    cd_dbg(CD_OPEN, "wrong media type, but CDO_CHECK_TYPE not set\n");
		पूर्ण
	पूर्ण

	cd_dbg(CD_OPEN, "all seems well, opening the devicen");

	/* all seems well, we can खोलो the device */
	ret = cकरो->खोलो(cdi, 0); /* खोलो क्रम data */
	cd_dbg(CD_OPEN, "opening the device gave me %d\n", ret);
	/* After all this careful checking, we shouldn't have problems
	   खोलोing the device, but we करोn't want the device locked अगर 
	   this somehow fails... */
	अगर (ret) अणु
		cd_dbg(CD_OPEN, "open device failed\n");
		जाओ clean_up_and_वापस;
	पूर्ण
	अगर (CDROM_CAN(CDC_LOCK) && (cdi->options & CDO_LOCK)) अणु
			cकरो->lock_करोor(cdi, 1);
			cd_dbg(CD_OPEN, "door locked\n");
	पूर्ण
	cd_dbg(CD_OPEN, "device opened successfully\n");
	वापस ret;

	/* Something failed.  Try to unlock the drive, because some drivers
	(notably ide-cd) lock the drive after every command.  This produced
	a nasty bug where after mount failed, the drive would reमुख्य locked!  
	This ensures that the drive माला_लो unlocked after a mount fails.  This 
	is a जाओ to aव्योम bloating the driver with redundant code. */ 
clean_up_and_वापस:
	cd_dbg(CD_OPEN, "open failed\n");
	अगर (CDROM_CAN(CDC_LOCK) && cdi->options & CDO_LOCK) अणु
			cकरो->lock_करोor(cdi, 0);
			cd_dbg(CD_OPEN, "door unlocked\n");
	पूर्ण
	वापस ret;
पूर्ण

/* We use the खोलो-option O_NONBLOCK to indicate that the
 * purpose of खोलोing is only क्रम subsequent ioctl() calls; no device
 * पूर्णांकegrity checks are perक्रमmed.
 *
 * We hope that all cd-player programs will aकरोpt this convention. It
 * is in their own पूर्णांकerest: device control becomes a lot easier
 * this way.
 */
पूर्णांक cdrom_खोलो(काष्ठा cdrom_device_info *cdi, काष्ठा block_device *bdev,
	       भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	cd_dbg(CD_OPEN, "entering cdrom_open\n");

	/* अगर this was a O_NONBLOCK खोलो and we should honor the flags,
	 * करो a quick खोलो without drive/disc पूर्णांकegrity checks. */
	cdi->use_count++;
	अगर ((mode & FMODE_NDELAY) && (cdi->options & CDO_USE_FFLAGS)) अणु
		ret = cdi->ops->खोलो(cdi, 1);
	पूर्ण अन्यथा अणु
		ret = खोलो_क्रम_data(cdi);
		अगर (ret)
			जाओ err;
		अगर (CDROM_CAN(CDC_GENERIC_PACKET))
			cdrom_mmc3_profile(cdi);
		अगर (mode & FMODE_WRITE) अणु
			ret = -EROFS;
			अगर (cdrom_खोलो_ग_लिखो(cdi))
				जाओ err_release;
			अगर (!CDROM_CAN(CDC_RAM))
				जाओ err_release;
			ret = 0;
			cdi->media_written = 0;
		पूर्ण
	पूर्ण

	अगर (ret)
		जाओ err;

	cd_dbg(CD_OPEN, "Use count for \"/dev/%s\" now %d\n",
	       cdi->name, cdi->use_count);
	वापस 0;
err_release:
	अगर (CDROM_CAN(CDC_LOCK) && cdi->options & CDO_LOCK) अणु
		cdi->ops->lock_करोor(cdi, 0);
		cd_dbg(CD_OPEN, "door unlocked\n");
	पूर्ण
	cdi->ops->release(cdi);
err:
	cdi->use_count--;
	वापस ret;
पूर्ण

/* This code is similar to that in खोलो_क्रम_data. The routine is called
   whenever an audio play operation is requested.
*/
अटल पूर्णांक check_क्रम_audio_disc(काष्ठा cdrom_device_info *cdi,
				स्थिर काष्ठा cdrom_device_ops *cकरो)
अणु
        पूर्णांक ret;
	tracktype tracks;
	cd_dbg(CD_OPEN, "entering check_for_audio_disc\n");
	अगर (!(cdi->options & CDO_CHECK_TYPE))
		वापस 0;
	अगर (cकरो->drive_status != शून्य) अणु
		ret = cकरो->drive_status(cdi, CDSL_CURRENT);
		cd_dbg(CD_OPEN, "drive_status=%d\n", ret);
		अगर (ret == CDS_TRAY_OPEN) अणु
			cd_dbg(CD_OPEN, "the tray is open...\n");
			/* can/may i बंद it? */
			अगर (CDROM_CAN(CDC_CLOSE_TRAY) &&
			    cdi->options & CDO_AUTO_CLOSE) अणु
				cd_dbg(CD_OPEN, "trying to close the tray\n");
				ret=cकरो->tray_move(cdi,0);
				अगर (ret) अणु
					cd_dbg(CD_OPEN, "bummer. tried to close tray but failed.\n");
					/* Ignore the error from the low
					level driver.  We करोn't care why it
					couldn't बंद the tray.  We only care 
					that there is no disc in the drive, 
					since that is the _REAL_ problem here.*/
					वापस -ENOMEDIUM;
				पूर्ण
			पूर्ण अन्यथा अणु
				cd_dbg(CD_OPEN, "bummer. this driver can't close the tray.\n");
				वापस -ENOMEDIUM;
			पूर्ण
			/* Ok, the करोor should be बंदd now.. Check again */
			ret = cकरो->drive_status(cdi, CDSL_CURRENT);
			अगर ((ret == CDS_NO_DISC) || (ret==CDS_TRAY_OPEN)) अणु
				cd_dbg(CD_OPEN, "bummer. the tray is still not closed.\n");
				वापस -ENOMEDIUM;
			पूर्ण	
			अगर (ret!=CDS_DISC_OK) अणु
				cd_dbg(CD_OPEN, "bummer. disc isn't ready.\n");
				वापस -EIO;
			पूर्ण	
			cd_dbg(CD_OPEN, "the tray is now closed\n");
		पूर्ण	
	पूर्ण
	cdrom_count_tracks(cdi, &tracks);
	अगर (tracks.error) 
		वापस(tracks.error);

	अगर (tracks.audio==0)
		वापस -EMEDIUMTYPE;

	वापस 0;
पूर्ण

व्योम cdrom_release(काष्ठा cdrom_device_info *cdi, भ_शेषe_t mode)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	पूर्णांक खोलोed_क्रम_data;

	cd_dbg(CD_CLOSE, "entering cdrom_release\n");

	अगर (cdi->use_count > 0)
		cdi->use_count--;

	अगर (cdi->use_count == 0) अणु
		cd_dbg(CD_CLOSE, "Use count for \"/dev/%s\" now zero\n",
		       cdi->name);
		cdrom_dvd_rw_बंद_ग_लिखो(cdi);

		अगर ((cकरो->capability & CDC_LOCK) && !cdi->keeplocked) अणु
			cd_dbg(CD_CLOSE, "Unlocking door!\n");
			cकरो->lock_करोor(cdi, 0);
		पूर्ण
	पूर्ण

	खोलोed_क्रम_data = !(cdi->options & CDO_USE_FFLAGS) ||
		!(mode & FMODE_NDELAY);

	/*
	 * flush cache on last ग_लिखो release
	 */
	अगर (CDROM_CAN(CDC_RAM) && !cdi->use_count && cdi->क्रम_data)
		cdrom_बंद_ग_लिखो(cdi);

	cकरो->release(cdi);
	अगर (cdi->use_count == 0) अणु      /* last process that बंदs dev*/
		अगर (खोलोed_क्रम_data &&
		    cdi->options & CDO_AUTO_EJECT && CDROM_CAN(CDC_OPEN_TRAY))
			cकरो->tray_move(cdi, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_mech_status(काष्ठा cdrom_device_info *cdi, 
				  काष्ठा cdrom_changer_info *buf)
अणु
	काष्ठा packet_command cgc;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	पूर्णांक length;

	/*
	 * Sanyo changer isn't spec compliant (doesn't use regular change
	 * LOAD_UNLOAD command, and it करोesn't implement the mech status
	 * command below
	 */
	अगर (cdi->sanyo_slot) अणु
		buf->hdr.nslots = 3;
		buf->hdr.curslot = cdi->sanyo_slot == 3 ? 0 : cdi->sanyo_slot;
		क्रम (length = 0; length < 3; length++) अणु
			buf->slots[length].disc_present = 1;
			buf->slots[length].change = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	length = माप(काष्ठा cdrom_mechstat_header) +
		 cdi->capacity * माप(काष्ठा cdrom_slot);

	init_cdrom_command(&cgc, buf, length, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_MECHANISM_STATUS;
	cgc.cmd[8] = (length >> 8) & 0xff;
	cgc.cmd[9] = length & 0xff;
	वापस cकरो->generic_packet(cdi, &cgc);
पूर्ण

अटल पूर्णांक cdrom_slot_status(काष्ठा cdrom_device_info *cdi, पूर्णांक slot)
अणु
	काष्ठा cdrom_changer_info *info;
	पूर्णांक ret;

	cd_dbg(CD_CHANGER, "entering cdrom_slot_status()\n");
	अगर (cdi->sanyo_slot)
		वापस CDS_NO_INFO;
	
	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर ((ret = cdrom_पढ़ो_mech_status(cdi, info)))
		जाओ out_मुक्त;

	अगर (info->slots[slot].disc_present)
		ret = CDS_DISC_OK;
	अन्यथा
		ret = CDS_NO_DISC;

out_मुक्त:
	kमुक्त(info);
	वापस ret;
पूर्ण

/* Return the number of slots क्रम an ATAPI/SCSI cdrom, 
 * वापस 1 अगर not a changer. 
 */
पूर्णांक cdrom_number_of_slots(काष्ठा cdrom_device_info *cdi) 
अणु
	पूर्णांक status;
	पूर्णांक nslots = 1;
	काष्ठा cdrom_changer_info *info;

	cd_dbg(CD_CHANGER, "entering cdrom_number_of_slots()\n");
	/* cdrom_पढ़ो_mech_status requires a valid value क्रम capacity: */
	cdi->capacity = 0; 

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर ((status = cdrom_पढ़ो_mech_status(cdi, info)) == 0)
		nslots = info->hdr.nslots;

	kमुक्त(info);
	वापस nslots;
पूर्ण


/* If SLOT < 0, unload the current slot.  Otherwise, try to load SLOT. */
अटल पूर्णांक cdrom_load_unload(काष्ठा cdrom_device_info *cdi, पूर्णांक slot) 
अणु
	काष्ठा packet_command cgc;

	cd_dbg(CD_CHANGER, "entering cdrom_load_unload()\n");
	अगर (cdi->sanyo_slot && slot < 0)
		वापस 0;

	init_cdrom_command(&cgc, शून्य, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_LOAD_UNLOAD;
	cgc.cmd[4] = 2 + (slot >= 0);
	cgc.cmd[8] = slot;
	cgc.समयout = 60 * HZ;

	/* The Sanyo 3 CD changer uses byte 7 of the 
	GPCMD_TEST_UNIT_READY to command to चयन CDs instead of
	using the GPCMD_LOAD_UNLOAD opcode. */
	अगर (cdi->sanyo_slot && -1 < slot) अणु
		cgc.cmd[0] = GPCMD_TEST_UNIT_READY;
		cgc.cmd[7] = slot;
		cgc.cmd[4] = cgc.cmd[8] = 0;
		cdi->sanyo_slot = slot ? slot : 3;
	पूर्ण

	वापस cdi->ops->generic_packet(cdi, &cgc);
पूर्ण

अटल पूर्णांक cdrom_select_disc(काष्ठा cdrom_device_info *cdi, पूर्णांक slot)
अणु
	काष्ठा cdrom_changer_info *info;
	पूर्णांक curslot;
	पूर्णांक ret;

	cd_dbg(CD_CHANGER, "entering cdrom_select_disc()\n");
	अगर (!CDROM_CAN(CDC_SELECT_DISC))
		वापस -EDRIVE_CANT_DO_THIS;

	अगर (cdi->ops->check_events)
		cdi->ops->check_events(cdi, 0, slot);

	अगर (slot == CDSL_NONE) अणु
		/* set media changed bits, on both queues */
		cdi->mc_flags = 0x3;
		वापस cdrom_load_unload(cdi, -1);
	पूर्ण

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर ((ret = cdrom_पढ़ो_mech_status(cdi, info))) अणु
		kमुक्त(info);
		वापस ret;
	पूर्ण

	curslot = info->hdr.curslot;
	kमुक्त(info);

	अगर (cdi->use_count > 1 || cdi->keeplocked) अणु
		अगर (slot == CDSL_CURRENT) अणु
	    		वापस curslot;
		पूर्ण अन्यथा अणु
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Specअगरying CDSL_CURRENT will attempt to load the currnet slot,
	which is useful अगर it had been previously unloaded.
	Whether it can or not, it वापसs the current slot. 
	Similarly,  अगर slot happens to be the current one, we still
	try and load it. */
	अगर (slot == CDSL_CURRENT)
		slot = curslot;

	/* set media changed bits on both queues */
	cdi->mc_flags = 0x3;
	अगर ((ret = cdrom_load_unload(cdi, slot)))
		वापस ret;

	वापस slot;
पूर्ण

/*
 * As cdrom implements an extra ioctl consumer क्रम media changed
 * event, it needs to buffer ->check_events() output, such that event
 * is not lost क्रम both the usual VFS and ioctl paths.
 * cdi->अणुvfs|ioctlपूर्ण_events are used to buffer pending events क्रम each
 * path.
 *
 * XXX: Locking is non-existent.  cdi->ops->check_events() can be
 * called in parallel and buffering fields are accessed without any
 * exclusion.  The original media_changed code had the same problem.
 * It might be better to simply deprecate CDROM_MEDIA_CHANGED ioctl
 * and हटाओ this cruft altogether.  It करोesn't have much usefulness
 * at this poपूर्णांक.
 */
अटल व्योम cdrom_update_events(काष्ठा cdrom_device_info *cdi,
				अचिन्हित पूर्णांक clearing)
अणु
	अचिन्हित पूर्णांक events;

	events = cdi->ops->check_events(cdi, clearing, CDSL_CURRENT);
	cdi->vfs_events |= events;
	cdi->ioctl_events |= events;
पूर्ण

अचिन्हित पूर्णांक cdrom_check_events(काष्ठा cdrom_device_info *cdi,
				अचिन्हित पूर्णांक clearing)
अणु
	अचिन्हित पूर्णांक events;

	cdrom_update_events(cdi, clearing);
	events = cdi->vfs_events;
	cdi->vfs_events = 0;
	वापस events;
पूर्ण
EXPORT_SYMBOL(cdrom_check_events);

/* We want to make media_changed accessible to the user through an
 * ioctl. The मुख्य problem now is that we must द्विगुन-buffer the
 * low-level implementation, to assure that the VFS and the user both
 * see a medium change once.
 */

अटल
पूर्णांक media_changed(काष्ठा cdrom_device_info *cdi, पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक mask = (1 << (queue & 1));
	पूर्णांक ret = !!(cdi->mc_flags & mask);
	bool changed;

	अगर (!CDROM_CAN(CDC_MEDIA_CHANGED))
		वापस ret;

	/* changed since last call? */
	BUG_ON(!queue);	/* shouldn't be called from VFS path */
	cdrom_update_events(cdi, DISK_EVENT_MEDIA_CHANGE);
	changed = cdi->ioctl_events & DISK_EVENT_MEDIA_CHANGE;
	cdi->ioctl_events = 0;

	अगर (changed) अणु
		cdi->mc_flags = 0x3;    /* set bit on both queues */
		ret |= 1;
		cdi->media_written = 0;
	पूर्ण

	cdi->mc_flags &= ~mask;         /* clear bit */
	वापस ret;
पूर्ण

/* Requests to the low-level drivers will /always/ be करोne in the
   following क्रमmat convention:

   CDROM_LBA: all data-related requests.
   CDROM_MSF: all audio-related requests.

   However, a low-level implementation is allowed to refuse this
   request, and वापस inक्रमmation in its own favorite क्रमmat.

   It करोesn't make sense /at all/ to ask क्रम a play_audio in LBA
   क्रमmat, or ask क्रम multi-session info in MSF क्रमmat. However, क्रम
   backward compatibility these क्रमmat requests will be satisfied, but
   the requests to the low-level drivers will be sanitized in the more
   meaningful क्रमmat indicated above.
 */

अटल
व्योम sanitize_क्रमmat(जोड़ cdrom_addr *addr,
		     u_अक्षर * curr, u_अक्षर requested)
अणु
	अगर (*curr == requested)
		वापस;                 /* nothing to be करोne! */
	अगर (requested == CDROM_LBA) अणु
		addr->lba = (पूर्णांक) addr->msf.frame +
			75 * (addr->msf.second - 2 + 60 * addr->msf.minute);
	पूर्ण अन्यथा अणु                        /* CDROM_MSF */
		पूर्णांक lba = addr->lba;
		addr->msf.frame = lba % 75;
		lba /= 75;
		lba += 2;
		addr->msf.second = lba % 60;
		addr->msf.minute = lba / 60;
	पूर्ण
	*curr = requested;
पूर्ण

व्योम init_cdrom_command(काष्ठा packet_command *cgc, व्योम *buf, पूर्णांक len,
			पूर्णांक type)
अणु
	स_रखो(cgc, 0, माप(काष्ठा packet_command));
	अगर (buf)
		स_रखो(buf, 0, len);
	cgc->buffer = (अक्षर *) buf;
	cgc->buflen = len;
	cgc->data_direction = type;
	cgc->समयout = CDROM_DEF_TIMEOUT;
पूर्ण

/* DVD handling */

#घोषणा copy_key(dest,src)	स_नकल((dest), (src), माप(dvd_key))
#घोषणा copy_chal(dest,src)	स_नकल((dest), (src), माप(dvd_challenge))

अटल व्योम setup_report_key(काष्ठा packet_command *cgc, अचिन्हित agid, अचिन्हित type)
अणु
	cgc->cmd[0] = GPCMD_REPORT_KEY;
	cgc->cmd[10] = type | (agid << 6);
	चयन (type) अणु
		हाल 0: हाल 8: हाल 5: अणु
			cgc->buflen = 8;
			अवरोध;
		पूर्ण
		हाल 1: अणु
			cgc->buflen = 16;
			अवरोध;
		पूर्ण
		हाल 2: हाल 4: अणु
			cgc->buflen = 12;
			अवरोध;
		पूर्ण
	पूर्ण
	cgc->cmd[9] = cgc->buflen;
	cgc->data_direction = CGC_DATA_READ;
पूर्ण

अटल व्योम setup_send_key(काष्ठा packet_command *cgc, अचिन्हित agid, अचिन्हित type)
अणु
	cgc->cmd[0] = GPCMD_SEND_KEY;
	cgc->cmd[10] = type | (agid << 6);
	चयन (type) अणु
		हाल 1: अणु
			cgc->buflen = 16;
			अवरोध;
		पूर्ण
		हाल 3: अणु
			cgc->buflen = 12;
			अवरोध;
		पूर्ण
		हाल 6: अणु
			cgc->buflen = 8;
			अवरोध;
		पूर्ण
	पूर्ण
	cgc->cmd[9] = cgc->buflen;
	cgc->data_direction = CGC_DATA_WRITE;
पूर्ण

अटल पूर्णांक dvd_करो_auth(काष्ठा cdrom_device_info *cdi, dvd_authinfo *ai)
अणु
	पूर्णांक ret;
	u_अक्षर buf[20];
	काष्ठा packet_command cgc;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	rpc_state_t rpc_state;

	स_रखो(buf, 0, माप(buf));
	init_cdrom_command(&cgc, buf, 0, CGC_DATA_READ);

	चयन (ai->type) अणु
	/* LU data send */
	हाल DVD_LU_SEND_AGID:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_AGID\n");
		cgc.quiet = 1;
		setup_report_key(&cgc, ai->lsa.agid, 0);

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		ai->lsa.agid = buf[7] >> 6;
		/* Returning data, let host change state */
		अवरोध;

	हाल DVD_LU_SEND_KEY1:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_KEY1\n");
		setup_report_key(&cgc, ai->lsk.agid, 2);

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		copy_key(ai->lsk.key, &buf[4]);
		/* Returning data, let host change state */
		अवरोध;

	हाल DVD_LU_SEND_CHALLENGE:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_CHALLENGE\n");
		setup_report_key(&cgc, ai->lsc.agid, 1);

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		copy_chal(ai->lsc.chal, &buf[4]);
		/* Returning data, let host change state */
		अवरोध;

	/* Post-auth key */
	हाल DVD_LU_SEND_TITLE_KEY:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_TITLE_KEY\n");
		cgc.quiet = 1;
		setup_report_key(&cgc, ai->lstk.agid, 4);
		cgc.cmd[5] = ai->lstk.lba;
		cgc.cmd[4] = ai->lstk.lba >> 8;
		cgc.cmd[3] = ai->lstk.lba >> 16;
		cgc.cmd[2] = ai->lstk.lba >> 24;

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		ai->lstk.cpm = (buf[4] >> 7) & 1;
		ai->lstk.cp_sec = (buf[4] >> 6) & 1;
		ai->lstk.cgms = (buf[4] >> 4) & 3;
		copy_key(ai->lstk.title_key, &buf[5]);
		/* Returning data, let host change state */
		अवरोध;

	हाल DVD_LU_SEND_ASF:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_ASF\n");
		setup_report_key(&cgc, ai->lsasf.agid, 5);
		
		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		ai->lsasf.asf = buf[7] & 1;
		अवरोध;

	/* LU data receive (LU changes state) */
	हाल DVD_HOST_SEND_CHALLENGE:
		cd_dbg(CD_DVD, "entering DVD_HOST_SEND_CHALLENGE\n");
		setup_send_key(&cgc, ai->hsc.agid, 1);
		buf[1] = 0xe;
		copy_chal(&buf[4], ai->hsc.chal);

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		ai->type = DVD_LU_SEND_KEY1;
		अवरोध;

	हाल DVD_HOST_SEND_KEY2:
		cd_dbg(CD_DVD, "entering DVD_HOST_SEND_KEY2\n");
		setup_send_key(&cgc, ai->hsk.agid, 3);
		buf[1] = 0xa;
		copy_key(&buf[4], ai->hsk.key);

		अगर ((ret = cकरो->generic_packet(cdi, &cgc))) अणु
			ai->type = DVD_AUTH_FAILURE;
			वापस ret;
		पूर्ण
		ai->type = DVD_AUTH_ESTABLISHED;
		अवरोध;

	/* Misc */
	हाल DVD_INVALIDATE_AGID:
		cgc.quiet = 1;
		cd_dbg(CD_DVD, "entering DVD_INVALIDATE_AGID\n");
		setup_report_key(&cgc, ai->lsa.agid, 0x3f);
		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;
		अवरोध;

	/* Get region settings */
	हाल DVD_LU_SEND_RPC_STATE:
		cd_dbg(CD_DVD, "entering DVD_LU_SEND_RPC_STATE\n");
		setup_report_key(&cgc, 0, 8);
		स_रखो(&rpc_state, 0, माप(rpc_state_t));
		cgc.buffer = (अक्षर *) &rpc_state;

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;

		ai->lrpcs.type = rpc_state.type_code;
		ai->lrpcs.vra = rpc_state.vra;
		ai->lrpcs.ucca = rpc_state.ucca;
		ai->lrpcs.region_mask = rpc_state.region_mask;
		ai->lrpcs.rpc_scheme = rpc_state.rpc_scheme;
		अवरोध;

	/* Set region settings */
	हाल DVD_HOST_SEND_RPC_STATE:
		cd_dbg(CD_DVD, "entering DVD_HOST_SEND_RPC_STATE\n");
		setup_send_key(&cgc, 0, 6);
		buf[1] = 6;
		buf[4] = ai->hrpcs.pdrc;

		अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
			वापस ret;
		अवरोध;

	शेष:
		cd_dbg(CD_WARNING, "Invalid DVD key ioctl (%d)\n", ai->type);
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_physical(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
				काष्ठा packet_command *cgc)
अणु
	अचिन्हित अक्षर buf[21], *base;
	काष्ठा dvd_layer *layer;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	पूर्णांक ret, layer_num = s->physical.layer_num;

	अगर (layer_num >= DVD_LAYERS)
		वापस -EINVAL;

	init_cdrom_command(cgc, buf, माप(buf), CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[6] = layer_num;
	cgc->cmd[7] = s->type;
	cgc->cmd[9] = cgc->buflen & 0xff;

	/*
	 * refrain from reporting errors on non-existing layers (मुख्यly)
	 */
	cgc->quiet = 1;

	ret = cकरो->generic_packet(cdi, cgc);
	अगर (ret)
		वापस ret;

	base = &buf[4];
	layer = &s->physical.layer[layer_num];

	/*
	 * place the data... really ugly, but at least we won't have to
	 * worry about endianess in userspace.
	 */
	स_रखो(layer, 0, माप(*layer));
	layer->book_version = base[0] & 0xf;
	layer->book_type = base[0] >> 4;
	layer->min_rate = base[1] & 0xf;
	layer->disc_size = base[1] >> 4;
	layer->layer_type = base[2] & 0xf;
	layer->track_path = (base[2] >> 4) & 1;
	layer->nlayers = (base[2] >> 5) & 3;
	layer->track_density = base[3] & 0xf;
	layer->linear_density = base[3] >> 4;
	layer->start_sector = base[5] << 16 | base[6] << 8 | base[7];
	layer->end_sector = base[9] << 16 | base[10] << 8 | base[11];
	layer->end_sector_l0 = base[13] << 16 | base[14] << 8 | base[15];
	layer->bca = base[16] >> 7;

	वापस 0;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_copyright(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
				काष्ठा packet_command *cgc)
अणु
	पूर्णांक ret;
	u_अक्षर buf[8];
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	init_cdrom_command(cgc, buf, माप(buf), CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[6] = s->copyright.layer_num;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = cgc->buflen >> 8;
	cgc->cmd[9] = cgc->buflen & 0xff;

	ret = cकरो->generic_packet(cdi, cgc);
	अगर (ret)
		वापस ret;

	s->copyright.cpst = buf[4];
	s->copyright.rmi = buf[5];

	वापस 0;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_disckey(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
				काष्ठा packet_command *cgc)
अणु
	पूर्णांक ret, size;
	u_अक्षर *buf;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	size = माप(s->disckey.value) + 4;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = size >> 8;
	cgc->cmd[9] = size & 0xff;
	cgc->cmd[10] = s->disckey.agid << 6;

	ret = cकरो->generic_packet(cdi, cgc);
	अगर (!ret)
		स_नकल(s->disckey.value, &buf[4], माप(s->disckey.value));

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_bca(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
			काष्ठा packet_command *cgc)
अणु
	पूर्णांक ret, size = 4 + 188;
	u_अक्षर *buf;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[9] = cgc->buflen & 0xff;

	ret = cकरो->generic_packet(cdi, cgc);
	अगर (ret)
		जाओ out;

	s->bca.len = buf[0] << 8 | buf[1];
	अगर (s->bca.len < 12 || s->bca.len > 188) अणु
		cd_dbg(CD_WARNING, "Received invalid BCA length (%d)\n",
		       s->bca.len);
		ret = -EIO;
		जाओ out;
	पूर्ण
	स_नकल(s->bca.value, &buf[4], s->bca.len);
	ret = 0;
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_manufact(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
				काष्ठा packet_command *cgc)
अणु
	पूर्णांक ret = 0, size;
	u_अक्षर *buf;
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	size = माप(s->manufact.value) + 4;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = size >> 8;
	cgc->cmd[9] = size & 0xff;

	ret = cकरो->generic_packet(cdi, cgc);
	अगर (ret)
		जाओ out;

	s->manufact.len = buf[0] << 8 | buf[1];
	अगर (s->manufact.len < 0) अणु
		cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d)\n",
		       s->manufact.len);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		अगर (s->manufact.len > 2048) अणु
			cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d): truncating to 2048\n",
			       s->manufact.len);
			s->manufact.len = 2048;
		पूर्ण
		स_नकल(s->manufact.value, &buf[4], s->manufact.len);
	पूर्ण

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक dvd_पढ़ो_काष्ठा(काष्ठा cdrom_device_info *cdi, dvd_काष्ठा *s,
				काष्ठा packet_command *cgc)
अणु
	चयन (s->type) अणु
	हाल DVD_STRUCT_PHYSICAL:
		वापस dvd_पढ़ो_physical(cdi, s, cgc);

	हाल DVD_STRUCT_COPYRIGHT:
		वापस dvd_पढ़ो_copyright(cdi, s, cgc);

	हाल DVD_STRUCT_DISCKEY:
		वापस dvd_पढ़ो_disckey(cdi, s, cgc);

	हाल DVD_STRUCT_BCA:
		वापस dvd_पढ़ो_bca(cdi, s, cgc);

	हाल DVD_STRUCT_MANUFACT:
		वापस dvd_पढ़ो_manufact(cdi, s, cgc);
		
	शेष:
		cd_dbg(CD_WARNING, ": Invalid DVD structure read requested (%d)\n",
		       s->type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक cdrom_mode_sense(काष्ठा cdrom_device_info *cdi,
		     काष्ठा packet_command *cgc,
		     पूर्णांक page_code, पूर्णांक page_control)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	स_रखो(cgc->cmd, 0, माप(cgc->cmd));

	cgc->cmd[0] = GPCMD_MODE_SENSE_10;
	cgc->cmd[2] = page_code | (page_control << 6);
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_READ;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

पूर्णांक cdrom_mode_select(काष्ठा cdrom_device_info *cdi,
		      काष्ठा packet_command *cgc)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	स_रखो(cgc->cmd, 0, माप(cgc->cmd));
	स_रखो(cgc->buffer, 0, 2);
	cgc->cmd[0] = GPCMD_MODE_SELECT_10;
	cgc->cmd[1] = 0x10;		/* PF */
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_WRITE;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_subchannel(काष्ठा cdrom_device_info *cdi,
				 काष्ठा cdrom_subchnl *subchnl, पूर्णांक mcn)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा packet_command cgc;
	अक्षर buffer[32];
	पूर्णांक ret;

	init_cdrom_command(&cgc, buffer, 16, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_SUBCHANNEL;
	cgc.cmd[1] = subchnl->cdsc_क्रमmat;/* MSF or LBA addressing */
	cgc.cmd[2] = 0x40;  /* request subQ data */
	cgc.cmd[3] = mcn ? 2 : 1;
	cgc.cmd[8] = 16;

	अगर ((ret = cकरो->generic_packet(cdi, &cgc)))
		वापस ret;

	subchnl->cdsc_audiostatus = cgc.buffer[1];
	subchnl->cdsc_ctrl = cgc.buffer[5] & 0xf;
	subchnl->cdsc_trk = cgc.buffer[6];
	subchnl->cdsc_ind = cgc.buffer[7];

	अगर (subchnl->cdsc_क्रमmat == CDROM_LBA) अणु
		subchnl->cdsc_असलaddr.lba = ((cgc.buffer[8] << 24) |
						(cgc.buffer[9] << 16) |
						(cgc.buffer[10] << 8) |
						(cgc.buffer[11]));
		subchnl->cdsc_reladdr.lba = ((cgc.buffer[12] << 24) |
						(cgc.buffer[13] << 16) |
						(cgc.buffer[14] << 8) |
						(cgc.buffer[15]));
	पूर्ण अन्यथा अणु
		subchnl->cdsc_reladdr.msf.minute = cgc.buffer[13];
		subchnl->cdsc_reladdr.msf.second = cgc.buffer[14];
		subchnl->cdsc_reladdr.msf.frame = cgc.buffer[15];
		subchnl->cdsc_असलaddr.msf.minute = cgc.buffer[9];
		subchnl->cdsc_असलaddr.msf.second = cgc.buffer[10];
		subchnl->cdsc_असलaddr.msf.frame = cgc.buffer[11];
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Specअगरic READ_10 पूर्णांकerface
 */
अटल पूर्णांक cdrom_पढ़ो_cd(काष्ठा cdrom_device_info *cdi,
			 काष्ठा packet_command *cgc, पूर्णांक lba,
			 पूर्णांक blocksize, पूर्णांक nblocks)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	स_रखो(&cgc->cmd, 0, माप(cgc->cmd));
	cgc->cmd[0] = GPCMD_READ_10;
	cgc->cmd[2] = (lba >> 24) & 0xff;
	cgc->cmd[3] = (lba >> 16) & 0xff;
	cgc->cmd[4] = (lba >>  8) & 0xff;
	cgc->cmd[5] = lba & 0xff;
	cgc->cmd[6] = (nblocks >> 16) & 0xff;
	cgc->cmd[7] = (nblocks >>  8) & 0xff;
	cgc->cmd[8] = nblocks & 0xff;
	cgc->buflen = blocksize * nblocks;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

/* very generic पूर्णांकerface क्रम पढ़ोing the various types of blocks */
अटल पूर्णांक cdrom_पढ़ो_block(काष्ठा cdrom_device_info *cdi,
			    काष्ठा packet_command *cgc,
			    पूर्णांक lba, पूर्णांक nblocks, पूर्णांक क्रमmat, पूर्णांक blksize)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;

	स_रखो(&cgc->cmd, 0, माप(cgc->cmd));
	cgc->cmd[0] = GPCMD_READ_CD;
	/* expected sector size - cdda,mode1,etc. */
	cgc->cmd[1] = क्रमmat << 2;
	/* starting address */
	cgc->cmd[2] = (lba >> 24) & 0xff;
	cgc->cmd[3] = (lba >> 16) & 0xff;
	cgc->cmd[4] = (lba >>  8) & 0xff;
	cgc->cmd[5] = lba & 0xff;
	/* number of blocks */
	cgc->cmd[6] = (nblocks >> 16) & 0xff;
	cgc->cmd[7] = (nblocks >>  8) & 0xff;
	cgc->cmd[8] = nblocks & 0xff;
	cgc->buflen = blksize * nblocks;
	
	/* set the header info वापसed */
	चयन (blksize) अणु
	हाल CD_FRAMESIZE_RAW0	: cgc->cmd[9] = 0x58; अवरोध;
	हाल CD_FRAMESIZE_RAW1	: cgc->cmd[9] = 0x78; अवरोध;
	हाल CD_FRAMESIZE_RAW	: cgc->cmd[9] = 0xf8; अवरोध;
	शेष			: cgc->cmd[9] = 0x10;
	पूर्ण
	
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_cdda_old(काष्ठा cdrom_device_info *cdi, __u8 __user *ubuf,
			       पूर्णांक lba, पूर्णांक nframes)
अणु
	काष्ठा packet_command cgc;
	पूर्णांक ret = 0;
	पूर्णांक nr;

	cdi->last_sense = 0;

	स_रखो(&cgc, 0, माप(cgc));

	/*
	 * start with will ra.nframes size, back करोwn अगर alloc fails
	 */
	nr = nframes;
	करो अणु
		cgc.buffer = kदो_स्मृति_array(nr, CD_FRAMESIZE_RAW, GFP_KERNEL);
		अगर (cgc.buffer)
			अवरोध;

		nr >>= 1;
	पूर्ण जबतक (nr);

	अगर (!nr)
		वापस -ENOMEM;

	cgc.data_direction = CGC_DATA_READ;
	जबतक (nframes > 0) अणु
		अगर (nr > nframes)
			nr = nframes;

		ret = cdrom_पढ़ो_block(cdi, &cgc, lba, nr, 1, CD_FRAMESIZE_RAW);
		अगर (ret)
			अवरोध;
		अगर (copy_to_user(ubuf, cgc.buffer, CD_FRAMESIZE_RAW * nr)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ubuf += CD_FRAMESIZE_RAW * nr;
		nframes -= nr;
		lba += nr;
	पूर्ण
	kमुक्त(cgc.buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_cdda_bpc(काष्ठा cdrom_device_info *cdi, __u8 __user *ubuf,
			       पूर्णांक lba, पूर्णांक nframes)
अणु
	काष्ठा request_queue *q = cdi->disk->queue;
	काष्ठा request *rq;
	काष्ठा scsi_request *req;
	काष्ठा bio *bio;
	अचिन्हित पूर्णांक len;
	पूर्णांक nr, ret = 0;

	अगर (!q)
		वापस -ENXIO;

	अगर (!blk_queue_scsi_passthrough(q)) अणु
		WARN_ONCE(true,
			  "Attempt read CDDA info through a non-SCSI queue\n");
		वापस -EINVAL;
	पूर्ण

	cdi->last_sense = 0;

	जबतक (nframes) अणु
		nr = nframes;
		अगर (cdi->cdda_method == CDDA_BPC_SINGLE)
			nr = 1;
		अगर (nr * CD_FRAMESIZE_RAW > (queue_max_sectors(q) << 9))
			nr = (queue_max_sectors(q) << 9) / CD_FRAMESIZE_RAW;

		len = nr * CD_FRAMESIZE_RAW;

		rq = blk_get_request(q, REQ_OP_SCSI_IN, 0);
		अगर (IS_ERR(rq)) अणु
			ret = PTR_ERR(rq);
			अवरोध;
		पूर्ण
		req = scsi_req(rq);

		ret = blk_rq_map_user(q, rq, शून्य, ubuf, len, GFP_KERNEL);
		अगर (ret) अणु
			blk_put_request(rq);
			अवरोध;
		पूर्ण

		req->cmd[0] = GPCMD_READ_CD;
		req->cmd[1] = 1 << 2;
		req->cmd[2] = (lba >> 24) & 0xff;
		req->cmd[3] = (lba >> 16) & 0xff;
		req->cmd[4] = (lba >>  8) & 0xff;
		req->cmd[5] = lba & 0xff;
		req->cmd[6] = (nr >> 16) & 0xff;
		req->cmd[7] = (nr >>  8) & 0xff;
		req->cmd[8] = nr & 0xff;
		req->cmd[9] = 0xf8;

		req->cmd_len = 12;
		rq->समयout = 60 * HZ;
		bio = rq->bio;

		blk_execute_rq(cdi->disk, rq, 0);
		अगर (scsi_req(rq)->result) अणु
			काष्ठा scsi_sense_hdr sshdr;

			ret = -EIO;
			scsi_normalize_sense(req->sense, req->sense_len,
					     &sshdr);
			cdi->last_sense = sshdr.sense_key;
		पूर्ण

		अगर (blk_rq_unmap_user(bio))
			ret = -EFAULT;
		blk_put_request(rq);

		अगर (ret)
			अवरोध;

		nframes -= nr;
		lba += nr;
		ubuf += len;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_पढ़ो_cdda(काष्ठा cdrom_device_info *cdi, __u8 __user *ubuf,
			   पूर्णांक lba, पूर्णांक nframes)
अणु
	पूर्णांक ret;

	अगर (cdi->cdda_method == CDDA_OLD)
		वापस cdrom_पढ़ो_cdda_old(cdi, ubuf, lba, nframes);

retry:
	/*
	 * क्रम anything अन्यथा than success and io error, we need to retry
	 */
	ret = cdrom_पढ़ो_cdda_bpc(cdi, ubuf, lba, nframes);
	अगर (!ret || ret != -EIO)
		वापस ret;

	/*
	 * I've seen drives get sense 4/8/3 udma crc errors on multi
	 * frame dma, so drop to single frame dma अगर we need to
	 */
	अगर (cdi->cdda_method == CDDA_BPC_FULL && nframes > 1) अणु
		pr_info("dropping to single frame dma\n");
		cdi->cdda_method = CDDA_BPC_SINGLE;
		जाओ retry;
	पूर्ण

	/*
	 * so we have an io error of some sort with multi frame dma. अगर the
	 * condition wasn't a hardware error
	 * problems, not क्रम any error
	 */
	अगर (cdi->last_sense != 0x04 && cdi->last_sense != 0x0b)
		वापस ret;

	pr_info("dropping to old style cdda (sense=%x)\n", cdi->last_sense);
	cdi->cdda_method = CDDA_OLD;
	वापस cdrom_पढ़ो_cdda_old(cdi, ubuf, lba, nframes);	
पूर्ण

पूर्णांक cdrom_multisession(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_multisession *info)
अणु
	u8 requested_क्रमmat;
	पूर्णांक ret;

	अगर (!(cdi->ops->capability & CDC_MULTI_SESSION))
		वापस -ENOSYS;

	requested_क्रमmat = info->addr_क्रमmat;
	अगर (requested_क्रमmat != CDROM_MSF && requested_क्रमmat != CDROM_LBA)
		वापस -EINVAL;
	info->addr_क्रमmat = CDROM_LBA;

	ret = cdi->ops->get_last_session(cdi, info);
	अगर (!ret)
		sanitize_क्रमmat(&info->addr, &info->addr_क्रमmat,
				requested_क्रमmat);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdrom_multisession);

अटल पूर्णांक cdrom_ioctl_multisession(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_multisession info;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROMMULTISESSION\n");

	अगर (copy_from_user(&info, argp, माप(info)))
		वापस -EFAULT;
	ret = cdrom_multisession(cdi, &info);
	अगर (ret)
		वापस ret;
	अगर (copy_to_user(argp, &info, माप(info)))
		वापस -EFAULT;

	cd_dbg(CD_DO_IOCTL, "CDROMMULTISESSION successful\n");
	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_ioctl_eject(काष्ठा cdrom_device_info *cdi)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROMEJECT\n");

	अगर (!CDROM_CAN(CDC_OPEN_TRAY))
		वापस -ENOSYS;
	अगर (cdi->use_count != 1 || cdi->keeplocked)
		वापस -EBUSY;
	अगर (CDROM_CAN(CDC_LOCK)) अणु
		पूर्णांक ret = cdi->ops->lock_करोor(cdi, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस cdi->ops->tray_move(cdi, 1);
पूर्ण

अटल पूर्णांक cdrom_ioctl_बंदtray(काष्ठा cdrom_device_info *cdi)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROMCLOSETRAY\n");

	अगर (!CDROM_CAN(CDC_CLOSE_TRAY))
		वापस -ENOSYS;
	वापस cdi->ops->tray_move(cdi, 0);
पूर्ण

अटल पूर्णांक cdrom_ioctl_eject_sw(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROMEJECT_SW\n");

	अगर (!CDROM_CAN(CDC_OPEN_TRAY))
		वापस -ENOSYS;
	अगर (cdi->keeplocked)
		वापस -EBUSY;

	cdi->options &= ~(CDO_AUTO_CLOSE | CDO_AUTO_EJECT);
	अगर (arg)
		cdi->options |= CDO_AUTO_CLOSE | CDO_AUTO_EJECT;
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_ioctl_media_changed(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा cdrom_changer_info *info;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROM_MEDIA_CHANGED\n");

	अगर (!CDROM_CAN(CDC_MEDIA_CHANGED))
		वापस -ENOSYS;

	/* cannot select disc or select current disc */
	अगर (!CDROM_CAN(CDC_SELECT_DISC) || arg == CDSL_CURRENT)
		वापस media_changed(cdi, 1);

	अगर (arg >= cdi->capacity)
		वापस -EINVAL;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	ret = cdrom_पढ़ो_mech_status(cdi, info);
	अगर (!ret)
		ret = info->slots[arg].change;
	kमुक्त(info);
	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_ioctl_set_options(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_SET_OPTIONS\n");

	/*
	 * Options need to be in sync with capability.
	 * Too late क्रम that, so we have to check each one separately.
	 */
	चयन (arg) अणु
	हाल CDO_USE_FFLAGS:
	हाल CDO_CHECK_TYPE:
		अवरोध;
	हाल CDO_LOCK:
		अगर (!CDROM_CAN(CDC_LOCK))
			वापस -ENOSYS;
		अवरोध;
	हाल 0:
		वापस cdi->options;
	/* शेष is basically CDO_[AUTO_CLOSE|AUTO_EJECT] */
	शेष:
		अगर (!CDROM_CAN(arg))
			वापस -ENOSYS;
	पूर्ण
	cdi->options |= (पूर्णांक) arg;
	वापस cdi->options;
पूर्ण

अटल पूर्णांक cdrom_ioctl_clear_options(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_CLEAR_OPTIONS\n");

	cdi->options &= ~(पूर्णांक) arg;
	वापस cdi->options;
पूर्ण

अटल पूर्णांक cdrom_ioctl_select_speed(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_SELECT_SPEED\n");

	अगर (!CDROM_CAN(CDC_SELECT_SPEED))
		वापस -ENOSYS;
	वापस cdi->ops->select_speed(cdi, arg);
पूर्ण

अटल पूर्णांक cdrom_ioctl_select_disc(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_SELECT_DISC\n");

	अगर (!CDROM_CAN(CDC_SELECT_DISC))
		वापस -ENOSYS;

	अगर (arg != CDSL_CURRENT && arg != CDSL_NONE) अणु
		अगर (arg >= cdi->capacity)
			वापस -EINVAL;
	पूर्ण

	/*
	 * ->select_disc is a hook to allow a driver-specअगरic way of
	 * seleting disc.  However, since there is no equivalent hook क्रम
	 * cdrom_slot_status this may not actually be useful...
	 */
	अगर (cdi->ops->select_disc)
		वापस cdi->ops->select_disc(cdi, arg);

	cd_dbg(CD_CHANGER, "Using generic cdrom_select_disc()\n");
	वापस cdrom_select_disc(cdi, arg);
पूर्ण

अटल पूर्णांक cdrom_ioctl_reset(काष्ठा cdrom_device_info *cdi,
		काष्ठा block_device *bdev)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_RESET\n");

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!CDROM_CAN(CDC_RESET))
		वापस -ENOSYS;
	invalidate_bdev(bdev);
	वापस cdi->ops->reset(cdi);
पूर्ण

अटल पूर्णांक cdrom_ioctl_lock_करोor(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "%socking door\n", arg ? "L" : "Unl");

	अगर (!CDROM_CAN(CDC_LOCK))
		वापस -EDRIVE_CANT_DO_THIS;

	cdi->keeplocked = arg ? 1 : 0;

	/*
	 * Don't unlock the करोor on multiple खोलोs by शेष, but allow
	 * root to करो so.
	 */
	अगर (cdi->use_count != 1 && !arg && !capable(CAP_SYS_ADMIN))
		वापस -EBUSY;
	वापस cdi->ops->lock_करोor(cdi, arg);
पूर्ण

अटल पूर्णांक cdrom_ioctl_debug(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "%sabling debug\n", arg ? "En" : "Dis");

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	debug = arg ? 1 : 0;
	वापस debug;
पूर्ण

अटल पूर्णांक cdrom_ioctl_get_capability(काष्ठा cdrom_device_info *cdi)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_GET_CAPABILITY\n");
	वापस (cdi->ops->capability & ~cdi->mask);
पूर्ण

/*
 * The following function is implemented, although very few audio
 * discs give Universal Product Code inक्रमmation, which should just be
 * the Medium Catalog Number on the box.  Note, that the way the code
 * is written on the CD is /not/ unअगरorm across all discs!
 */
अटल पूर्णांक cdrom_ioctl_get_mcn(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_mcn mcn;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROM_GET_MCN\n");

	अगर (!(cdi->ops->capability & CDC_MCN))
		वापस -ENOSYS;
	ret = cdi->ops->get_mcn(cdi, &mcn);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(argp, &mcn, माप(mcn)))
		वापस -EFAULT;
	cd_dbg(CD_DO_IOCTL, "CDROM_GET_MCN successful\n");
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_ioctl_drive_status(काष्ठा cdrom_device_info *cdi,
		अचिन्हित दीर्घ arg)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_DRIVE_STATUS\n");

	अगर (!(cdi->ops->capability & CDC_DRIVE_STATUS))
		वापस -ENOSYS;
	अगर (!CDROM_CAN(CDC_SELECT_DISC) ||
	    (arg == CDSL_CURRENT || arg == CDSL_NONE))
		वापस cdi->ops->drive_status(cdi, CDSL_CURRENT);
	अगर (arg >= cdi->capacity)
		वापस -EINVAL;
	वापस cdrom_slot_status(cdi, arg);
पूर्ण

/*
 * Ok, this is where problems start.  The current पूर्णांकerface क्रम the
 * CDROM_DISC_STATUS ioctl is flawed.  It makes the false assumption that
 * CDs are all CDS_DATA_1 or all CDS_AUDIO, etc.  Unक्रमtunately, जबतक this
 * is often the हाल, it is also very common क्रम CDs to have some tracks
 * with data, and some tracks with audio.  Just because I feel like it,
 * I declare the following to be the best way to cope.  If the CD has ANY
 * data tracks on it, it will be वापसed as a data CD.  If it has any XA
 * tracks, I will वापस it as that.  Now I could simplअगरy this पूर्णांकerface
 * by combining these  वापसs with the above, but this more clearly
 * demonstrates the problem with the current पूर्णांकerface.  Too bad this
 * wasn't deचिन्हित to use biपंचांगasks...         -Erik
 *
 * Well, now we have the option CDS_MIXED: a mixed-type CD.
 * User level programmers might feel the ioctl is not very useful.
 *					---david
 */
अटल पूर्णांक cdrom_ioctl_disc_status(काष्ठा cdrom_device_info *cdi)
अणु
	tracktype tracks;

	cd_dbg(CD_DO_IOCTL, "entering CDROM_DISC_STATUS\n");

	cdrom_count_tracks(cdi, &tracks);
	अगर (tracks.error)
		वापस tracks.error;

	/* Policy mode on */
	अगर (tracks.audio > 0) अणु
		अगर (!tracks.data && !tracks.cdi && !tracks.xa)
			वापस CDS_AUDIO;
		अन्यथा
			वापस CDS_MIXED;
	पूर्ण

	अगर (tracks.cdi > 0)
		वापस CDS_XA_2_2;
	अगर (tracks.xa > 0)
		वापस CDS_XA_2_1;
	अगर (tracks.data > 0)
		वापस CDS_DATA_1;
	/* Policy mode off */

	cd_dbg(CD_WARNING, "This disc doesn't have any tracks I recognize!\n");
	वापस CDS_NO_INFO;
पूर्ण

अटल पूर्णांक cdrom_ioctl_changer_nslots(काष्ठा cdrom_device_info *cdi)
अणु
	cd_dbg(CD_DO_IOCTL, "entering CDROM_CHANGER_NSLOTS\n");
	वापस cdi->capacity;
पूर्ण

अटल पूर्णांक cdrom_ioctl_get_subchnl(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_subchnl q;
	u8 requested, back;
	पूर्णांक ret;

	/* cd_dbg(CD_DO_IOCTL,"entering CDROMSUBCHNL\n");*/

	अगर (copy_from_user(&q, argp, माप(q)))
		वापस -EFAULT;

	requested = q.cdsc_क्रमmat;
	अगर (requested != CDROM_MSF && requested != CDROM_LBA)
		वापस -EINVAL;
	q.cdsc_क्रमmat = CDROM_MSF;

	ret = cdi->ops->audio_ioctl(cdi, CDROMSUBCHNL, &q);
	अगर (ret)
		वापस ret;

	back = q.cdsc_क्रमmat; /* local copy */
	sanitize_क्रमmat(&q.cdsc_असलaddr, &back, requested);
	sanitize_क्रमmat(&q.cdsc_reladdr, &q.cdsc_क्रमmat, requested);

	अगर (copy_to_user(argp, &q, माप(q)))
		वापस -EFAULT;
	/* cd_dbg(CD_DO_IOCTL, "CDROMSUBCHNL successful\n"); */
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_ioctl_पढ़ो_tochdr(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_tochdr header;
	पूर्णांक ret;

	/* cd_dbg(CD_DO_IOCTL, "entering CDROMREADTOCHDR\n"); */

	अगर (copy_from_user(&header, argp, माप(header)))
		वापस -EFAULT;

	ret = cdi->ops->audio_ioctl(cdi, CDROMREADTOCHDR, &header);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(argp, &header, माप(header)))
		वापस -EFAULT;
	/* cd_dbg(CD_DO_IOCTL, "CDROMREADTOCHDR successful\n"); */
	वापस 0;
पूर्ण

पूर्णांक cdrom_पढ़ो_tocentry(काष्ठा cdrom_device_info *cdi,
		काष्ठा cdrom_tocentry *entry)
अणु
	u8 requested_क्रमmat = entry->cdte_क्रमmat;
	पूर्णांक ret;

	अगर (requested_क्रमmat != CDROM_MSF && requested_क्रमmat != CDROM_LBA)
		वापस -EINVAL;

	/* make पूर्णांकerface to low-level unअगरorm */
	entry->cdte_क्रमmat = CDROM_MSF;
	ret = cdi->ops->audio_ioctl(cdi, CDROMREADTOCENTRY, entry);
	अगर (!ret)
		sanitize_क्रमmat(&entry->cdte_addr, &entry->cdte_क्रमmat,
				requested_क्रमmat);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdrom_पढ़ो_tocentry);

अटल पूर्णांक cdrom_ioctl_पढ़ो_tocentry(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_tocentry entry;
	पूर्णांक ret;

	अगर (copy_from_user(&entry, argp, माप(entry)))
		वापस -EFAULT;
	ret = cdrom_पढ़ो_tocentry(cdi, &entry);
	अगर (!ret && copy_to_user(argp, &entry, माप(entry)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

अटल पूर्णांक cdrom_ioctl_play_msf(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_msf msf;

	cd_dbg(CD_DO_IOCTL, "entering CDROMPLAYMSF\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;
	अगर (copy_from_user(&msf, argp, माप(msf)))
		वापस -EFAULT;
	वापस cdi->ops->audio_ioctl(cdi, CDROMPLAYMSF, &msf);
पूर्ण

अटल पूर्णांक cdrom_ioctl_play_trkind(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_ti ti;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROMPLAYTRKIND\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;
	अगर (copy_from_user(&ti, argp, माप(ti)))
		वापस -EFAULT;

	ret = check_क्रम_audio_disc(cdi, cdi->ops);
	अगर (ret)
		वापस ret;
	वापस cdi->ops->audio_ioctl(cdi, CDROMPLAYTRKIND, &ti);
पूर्ण
अटल पूर्णांक cdrom_ioctl_volctrl(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_volctrl volume;

	cd_dbg(CD_DO_IOCTL, "entering CDROMVOLCTRL\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;
	अगर (copy_from_user(&volume, argp, माप(volume)))
		वापस -EFAULT;
	वापस cdi->ops->audio_ioctl(cdi, CDROMVOLCTRL, &volume);
पूर्ण

अटल पूर्णांक cdrom_ioctl_volपढ़ो(काष्ठा cdrom_device_info *cdi,
		व्योम __user *argp)
अणु
	काष्ठा cdrom_volctrl volume;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROMVOLREAD\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;

	ret = cdi->ops->audio_ioctl(cdi, CDROMVOLREAD, &volume);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(argp, &volume, माप(volume)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_ioctl_audioctl(काष्ठा cdrom_device_info *cdi,
		अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "doing audio ioctl (start/stop/pause/resume)\n");

	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;
	ret = check_क्रम_audio_disc(cdi, cdi->ops);
	अगर (ret)
		वापस ret;
	वापस cdi->ops->audio_ioctl(cdi, cmd, शून्य);
पूर्ण

/*
 * Required when we need to use READ_10 to issue other than 2048 block
 * पढ़ोs
 */
अटल पूर्णांक cdrom_चयन_blocksize(काष्ठा cdrom_device_info *cdi, पूर्णांक size)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा packet_command cgc;
	काष्ठा modesel_head mh;

	स_रखो(&mh, 0, माप(mh));
	mh.block_desc_length = 0x08;
	mh.block_length_med = (size >> 8) & 0xff;
	mh.block_length_lo = size & 0xff;

	स_रखो(&cgc, 0, माप(cgc));
	cgc.cmd[0] = 0x15;
	cgc.cmd[1] = 1 << 4;
	cgc.cmd[4] = 12;
	cgc.buflen = माप(mh);
	cgc.buffer = (अक्षर *) &mh;
	cgc.data_direction = CGC_DATA_WRITE;
	mh.block_desc_length = 0x08;
	mh.block_length_med = (size >> 8) & 0xff;
	mh.block_length_lo = size & 0xff;

	वापस cकरो->generic_packet(cdi, &cgc);
पूर्ण

अटल पूर्णांक cdrom_get_track_info(काष्ठा cdrom_device_info *cdi,
				__u16 track, __u8 type, track_inक्रमmation *ti)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा packet_command cgc;
	पूर्णांक ret, buflen;

	init_cdrom_command(&cgc, ti, 8, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_TRACK_RZONE_INFO;
	cgc.cmd[1] = type & 3;
	cgc.cmd[4] = (track & 0xff00) >> 8;
	cgc.cmd[5] = track & 0xff;
	cgc.cmd[8] = 8;
	cgc.quiet = 1;

	ret = cकरो->generic_packet(cdi, &cgc);
	अगर (ret)
		वापस ret;

	buflen = be16_to_cpu(ti->track_inक्रमmation_length) +
		माप(ti->track_inक्रमmation_length);

	अगर (buflen > माप(track_inक्रमmation))
		buflen = माप(track_inक्रमmation);

	cgc.cmd[8] = cgc.buflen = buflen;
	ret = cकरो->generic_packet(cdi, &cgc);
	अगर (ret)
		वापस ret;

	/* वापस actual fill size */
	वापस buflen;
पूर्ण

/* वापस the last written block on the CD-R media. this is क्रम the udf
   file प्रणाली. */
पूर्णांक cdrom_get_last_written(काष्ठा cdrom_device_info *cdi, दीर्घ *last_written)
अणु
	काष्ठा cdrom_tocentry toc;
	disc_inक्रमmation di;
	track_inक्रमmation ti;
	__u32 last_track;
	पूर्णांक ret = -1, ti_size;

	अगर (!CDROM_CAN(CDC_GENERIC_PACKET))
		जाओ use_toc;

	ret = cdrom_get_disc_info(cdi, &di);
	अगर (ret < (पूर्णांक)(दुरत्व(typeof(di), last_track_lsb)
			+ माप(di.last_track_lsb)))
		जाओ use_toc;

	/* अगर unit didn't return msb, it's zeroed by cdrom_get_disc_info */
	last_track = (di.last_track_msb << 8) | di.last_track_lsb;
	ti_size = cdrom_get_track_info(cdi, last_track, 1, &ti);
	अगर (ti_size < (पूर्णांक)दुरत्व(typeof(ti), track_start))
		जाओ use_toc;

	/* अगर this track is blank, try the previous. */
	अगर (ti.blank) अणु
		अगर (last_track == 1)
			जाओ use_toc;
		last_track--;
		ti_size = cdrom_get_track_info(cdi, last_track, 1, &ti);
	पूर्ण

	अगर (ti_size < (पूर्णांक)(दुरत्व(typeof(ti), track_size)
				+ माप(ti.track_size)))
		जाओ use_toc;

	/* अगर last recorded field is valid, वापस it. */
	अगर (ti.lra_v && ti_size >= (पूर्णांक)(दुरत्व(typeof(ti), last_rec_address)
				+ माप(ti.last_rec_address))) अणु
		*last_written = be32_to_cpu(ti.last_rec_address);
	पूर्ण अन्यथा अणु
		/* make it up instead */
		*last_written = be32_to_cpu(ti.track_start) +
				be32_to_cpu(ti.track_size);
		अगर (ti.मुक्त_blocks)
			*last_written -= (be32_to_cpu(ti.मुक्त_blocks) + 7);
	पूर्ण
	वापस 0;

	/* this is where we end up अगर the drive either can't करो a
	   GPCMD_READ_DISC_INFO or GPCMD_READ_TRACK_RZONE_INFO or अगर
	   it करोesn't give enough inक्रमmation or fails. then we वापस
	   the toc contents. */
use_toc:
	अगर (!CDROM_CAN(CDC_PLAY_AUDIO))
		वापस -ENOSYS;

	toc.cdte_क्रमmat = CDROM_MSF;
	toc.cdte_track = CDROM_LEADOUT;
	अगर ((ret = cdi->ops->audio_ioctl(cdi, CDROMREADTOCENTRY, &toc)))
		वापस ret;
	sanitize_क्रमmat(&toc.cdte_addr, &toc.cdte_क्रमmat, CDROM_LBA);
	*last_written = toc.cdte_addr.lba;
	वापस 0;
पूर्ण

/* वापस the next writable block. also क्रम udf file प्रणाली. */
अटल पूर्णांक cdrom_get_next_writable(काष्ठा cdrom_device_info *cdi,
				   दीर्घ *next_writable)
अणु
	disc_inक्रमmation di;
	track_inक्रमmation ti;
	__u16 last_track;
	पूर्णांक ret, ti_size;

	अगर (!CDROM_CAN(CDC_GENERIC_PACKET))
		जाओ use_last_written;

	ret = cdrom_get_disc_info(cdi, &di);
	अगर (ret < 0 || ret < दुरत्व(typeof(di), last_track_lsb)
				+ माप(di.last_track_lsb))
		जाओ use_last_written;

	/* अगर unit didn't return msb, it's zeroed by cdrom_get_disc_info */
	last_track = (di.last_track_msb << 8) | di.last_track_lsb;
	ti_size = cdrom_get_track_info(cdi, last_track, 1, &ti);
	अगर (ti_size < 0 || ti_size < दुरत्व(typeof(ti), track_start))
		जाओ use_last_written;

	/* अगर this track is blank, try the previous. */
	अगर (ti.blank) अणु
		अगर (last_track == 1)
			जाओ use_last_written;
		last_track--;
		ti_size = cdrom_get_track_info(cdi, last_track, 1, &ti);
		अगर (ti_size < 0)
			जाओ use_last_written;
	पूर्ण

	/* अगर next recordable address field is valid, use it. */
	अगर (ti.nwa_v && ti_size >= दुरत्व(typeof(ti), next_writable)
				+ माप(ti.next_writable)) अणु
		*next_writable = be32_to_cpu(ti.next_writable);
		वापस 0;
	पूर्ण

use_last_written:
	ret = cdrom_get_last_written(cdi, next_writable);
	अगर (ret) अणु
		*next_writable = 0;
		वापस ret;
	पूर्ण अन्यथा अणु
		*next_writable += 7;
		वापस 0;
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_पढ़ो_data(काष्ठा cdrom_device_info *cdi,
					      व्योम __user *arg,
					      काष्ठा packet_command *cgc,
					      पूर्णांक cmd)
अणु
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा cdrom_msf msf;
	पूर्णांक blocksize = 0, क्रमmat = 0, lba;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल CDROMREADRAW:
		blocksize = CD_FRAMESIZE_RAW;
		अवरोध;
	हाल CDROMREADMODE1:
		blocksize = CD_FRAMESIZE;
		क्रमmat = 2;
		अवरोध;
	हाल CDROMREADMODE2:
		blocksize = CD_FRAMESIZE_RAW0;
		अवरोध;
	पूर्ण
	अगर (copy_from_user(&msf, (काष्ठा cdrom_msf __user *)arg, माप(msf)))
		वापस -EFAULT;
	lba = msf_to_lba(msf.cdmsf_min0, msf.cdmsf_sec0, msf.cdmsf_frame0);
	/* FIXME: we need upper bound checking, too!! */
	अगर (lba < 0)
		वापस -EINVAL;

	cgc->buffer = kzalloc(blocksize, GFP_KERNEL);
	अगर (cgc->buffer == शून्य)
		वापस -ENOMEM;

	स_रखो(&sshdr, 0, माप(sshdr));
	cgc->sshdr = &sshdr;
	cgc->data_direction = CGC_DATA_READ;
	ret = cdrom_पढ़ो_block(cdi, cgc, lba, 1, क्रमmat, blocksize);
	अगर (ret && sshdr.sense_key == 0x05 &&
	    sshdr.asc == 0x20 &&
	    sshdr.ascq == 0x00) अणु
		/*
		 * SCSI-II devices are not required to support
		 * READ_CD, so let's try चयनing block size
		 */
		अगर (blocksize != CD_FRAMESIZE) अणु
			ret = cdrom_चयन_blocksize(cdi, blocksize);
			अगर (ret)
				जाओ out;
		पूर्ण
		cgc->sshdr = शून्य;
		ret = cdrom_पढ़ो_cd(cdi, cgc, lba, blocksize, 1);
		अगर (blocksize != CD_FRAMESIZE)
			ret |= cdrom_चयन_blocksize(cdi, CD_FRAMESIZE);
	पूर्ण
	अगर (!ret && copy_to_user(arg, cgc->buffer, blocksize))
		ret = -EFAULT;
out:
	kमुक्त(cgc->buffer);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_पढ़ो_audio(काष्ठा cdrom_device_info *cdi,
					       व्योम __user *arg)
अणु
	काष्ठा cdrom_पढ़ो_audio ra;
	पूर्णांक lba;

#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_cdrom_पढ़ो_audio अणु
			जोड़ cdrom_addr	addr;
			u8			addr_क्रमmat;
			compat_पूर्णांक_t		nframes;
			compat_caddr_t		buf;
		पूर्ण ra32;

		अगर (copy_from_user(&ra32, arg, माप(ra32)))
			वापस -EFAULT;

		ra = (काष्ठा cdrom_पढ़ो_audio) अणु
			.addr		= ra32.addr,
			.addr_क्रमmat	= ra32.addr_क्रमmat,
			.nframes	= ra32.nframes,
			.buf		= compat_ptr(ra32.buf),
		पूर्ण;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (copy_from_user(&ra, (काष्ठा cdrom_पढ़ो_audio __user *)arg,
				   माप(ra)))
			वापस -EFAULT;
	पूर्ण

	अगर (ra.addr_क्रमmat == CDROM_MSF)
		lba = msf_to_lba(ra.addr.msf.minute,
				 ra.addr.msf.second,
				 ra.addr.msf.frame);
	अन्यथा अगर (ra.addr_क्रमmat == CDROM_LBA)
		lba = ra.addr.lba;
	अन्यथा
		वापस -EINVAL;

	/* FIXME: we need upper bound checking, too!! */
	अगर (lba < 0 || ra.nframes <= 0 || ra.nframes > CD_FRAMES)
		वापस -EINVAL;

	वापस cdrom_पढ़ो_cdda(cdi, ra.buf, lba, ra.nframes);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_subchannel(काष्ठा cdrom_device_info *cdi,
					       व्योम __user *arg)
अणु
	पूर्णांक ret;
	काष्ठा cdrom_subchnl q;
	u_अक्षर requested, back;
	अगर (copy_from_user(&q, (काष्ठा cdrom_subchnl __user *)arg, माप(q)))
		वापस -EFAULT;
	requested = q.cdsc_क्रमmat;
	अगर (!((requested == CDROM_MSF) ||
	      (requested == CDROM_LBA)))
		वापस -EINVAL;

	ret = cdrom_पढ़ो_subchannel(cdi, &q, 0);
	अगर (ret)
		वापस ret;
	back = q.cdsc_क्रमmat; /* local copy */
	sanitize_क्रमmat(&q.cdsc_असलaddr, &back, requested);
	sanitize_क्रमmat(&q.cdsc_reladdr, &q.cdsc_क्रमmat, requested);
	अगर (copy_to_user((काष्ठा cdrom_subchnl __user *)arg, &q, माप(q)))
		वापस -EFAULT;
	/* cd_dbg(CD_DO_IOCTL, "CDROMSUBCHNL successful\n"); */
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_play_msf(काष्ठा cdrom_device_info *cdi,
					     व्योम __user *arg,
					     काष्ठा packet_command *cgc)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा cdrom_msf msf;
	cd_dbg(CD_DO_IOCTL, "entering CDROMPLAYMSF\n");
	अगर (copy_from_user(&msf, (काष्ठा cdrom_msf __user *)arg, माप(msf)))
		वापस -EFAULT;
	cgc->cmd[0] = GPCMD_PLAY_AUDIO_MSF;
	cgc->cmd[3] = msf.cdmsf_min0;
	cgc->cmd[4] = msf.cdmsf_sec0;
	cgc->cmd[5] = msf.cdmsf_frame0;
	cgc->cmd[6] = msf.cdmsf_min1;
	cgc->cmd[7] = msf.cdmsf_sec1;
	cgc->cmd[8] = msf.cdmsf_frame1;
	cgc->data_direction = CGC_DATA_NONE;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_play_blk(काष्ठा cdrom_device_info *cdi,
					     व्योम __user *arg,
					     काष्ठा packet_command *cgc)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	काष्ठा cdrom_blk blk;
	cd_dbg(CD_DO_IOCTL, "entering CDROMPLAYBLK\n");
	अगर (copy_from_user(&blk, (काष्ठा cdrom_blk __user *)arg, माप(blk)))
		वापस -EFAULT;
	cgc->cmd[0] = GPCMD_PLAY_AUDIO_10;
	cgc->cmd[2] = (blk.from >> 24) & 0xff;
	cgc->cmd[3] = (blk.from >> 16) & 0xff;
	cgc->cmd[4] = (blk.from >>  8) & 0xff;
	cgc->cmd[5] = blk.from & 0xff;
	cgc->cmd[7] = (blk.len >> 8) & 0xff;
	cgc->cmd[8] = blk.len & 0xff;
	cgc->data_direction = CGC_DATA_NONE;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_volume(काष्ठा cdrom_device_info *cdi,
					   व्योम __user *arg,
					   काष्ठा packet_command *cgc,
					   अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा cdrom_volctrl volctrl;
	अचिन्हित अक्षर buffer[32];
	अक्षर mask[माप(buffer)];
	अचिन्हित लघु offset;
	पूर्णांक ret;

	cd_dbg(CD_DO_IOCTL, "entering CDROMVOLUME\n");

	अगर (copy_from_user(&volctrl, (काष्ठा cdrom_volctrl __user *)arg,
			   माप(volctrl)))
		वापस -EFAULT;

	cgc->buffer = buffer;
	cgc->buflen = 24;
	ret = cdrom_mode_sense(cdi, cgc, GPMODE_AUDIO_CTL_PAGE, 0);
	अगर (ret)
		वापस ret;
		
	/* originally the code depended on buffer[1] to determine
	   how much data is available क्रम transfer. buffer[1] is
	   unक्रमtunately ambigious and the only reliable way seem
	   to be to simply skip over the block descriptor... */
	offset = 8 + be16_to_cpu(*(__be16 *)(buffer + 6));

	अगर (offset + 16 > माप(buffer))
		वापस -E2BIG;

	अगर (offset + 16 > cgc->buflen) अणु
		cgc->buflen = offset + 16;
		ret = cdrom_mode_sense(cdi, cgc,
				       GPMODE_AUDIO_CTL_PAGE, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* sanity check */
	अगर ((buffer[offset] & 0x3f) != GPMODE_AUDIO_CTL_PAGE ||
	    buffer[offset + 1] < 14)
		वापस -EINVAL;

	/* now we have the current volume settings. अगर it was only
	   a CDROMVOLREAD, वापस these values */
	अगर (cmd == CDROMVOLREAD) अणु
		volctrl.channel0 = buffer[offset+9];
		volctrl.channel1 = buffer[offset+11];
		volctrl.channel2 = buffer[offset+13];
		volctrl.channel3 = buffer[offset+15];
		अगर (copy_to_user((काष्ठा cdrom_volctrl __user *)arg, &volctrl,
				 माप(volctrl)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
		
	/* get the volume mask */
	cgc->buffer = mask;
	ret = cdrom_mode_sense(cdi, cgc, GPMODE_AUDIO_CTL_PAGE, 1);
	अगर (ret)
		वापस ret;

	buffer[offset + 9]  = volctrl.channel0 & mask[offset + 9];
	buffer[offset + 11] = volctrl.channel1 & mask[offset + 11];
	buffer[offset + 13] = volctrl.channel2 & mask[offset + 13];
	buffer[offset + 15] = volctrl.channel3 & mask[offset + 15];

	/* set volume */
	cgc->buffer = buffer + offset - 8;
	स_रखो(cgc->buffer, 0, 8);
	वापस cdrom_mode_select(cdi, cgc);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_start_stop(काष्ठा cdrom_device_info *cdi,
					       काष्ठा packet_command *cgc,
					       पूर्णांक cmd)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	cd_dbg(CD_DO_IOCTL, "entering CDROMSTART/CDROMSTOP\n");
	cgc->cmd[0] = GPCMD_START_STOP_UNIT;
	cgc->cmd[1] = 1;
	cgc->cmd[4] = (cmd == CDROMSTART) ? 1 : 0;
	cgc->data_direction = CGC_DATA_NONE;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_छोड़ो_resume(काष्ठा cdrom_device_info *cdi,
						 काष्ठा packet_command *cgc,
						 पूर्णांक cmd)
अणु
	स्थिर काष्ठा cdrom_device_ops *cकरो = cdi->ops;
	cd_dbg(CD_DO_IOCTL, "entering CDROMPAUSE/CDROMRESUME\n");
	cgc->cmd[0] = GPCMD_PAUSE_RESUME;
	cgc->cmd[8] = (cmd == CDROMRESUME) ? 1 : 0;
	cgc->data_direction = CGC_DATA_NONE;
	वापस cकरो->generic_packet(cdi, cgc);
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_dvd_पढ़ो_काष्ठा(काष्ठा cdrom_device_info *cdi,
					      व्योम __user *arg,
					      काष्ठा packet_command *cgc)
अणु
	पूर्णांक ret;
	dvd_काष्ठा *s;
	पूर्णांक size = माप(dvd_काष्ठा);

	अगर (!CDROM_CAN(CDC_DVD))
		वापस -ENOSYS;

	s = memdup_user(arg, size);
	अगर (IS_ERR(s))
		वापस PTR_ERR(s);

	cd_dbg(CD_DO_IOCTL, "entering DVD_READ_STRUCT\n");

	ret = dvd_पढ़ो_काष्ठा(cdi, s, cgc);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(arg, s, size))
		ret = -EFAULT;
out:
	kमुक्त(s);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_dvd_auth(काष्ठा cdrom_device_info *cdi,
				       व्योम __user *arg)
अणु
	पूर्णांक ret;
	dvd_authinfo ai;
	अगर (!CDROM_CAN(CDC_DVD))
		वापस -ENOSYS;
	cd_dbg(CD_DO_IOCTL, "entering DVD_AUTH\n");
	अगर (copy_from_user(&ai, (dvd_authinfo __user *)arg, माप(ai)))
		वापस -EFAULT;
	ret = dvd_करो_auth(cdi, &ai);
	अगर (ret)
		वापस ret;
	अगर (copy_to_user((dvd_authinfo __user *)arg, &ai, माप(ai)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_next_writable(काष्ठा cdrom_device_info *cdi,
						  व्योम __user *arg)
अणु
	पूर्णांक ret;
	दीर्घ next = 0;
	cd_dbg(CD_DO_IOCTL, "entering CDROM_NEXT_WRITABLE\n");
	ret = cdrom_get_next_writable(cdi, &next);
	अगर (ret)
		वापस ret;
	अगर (copy_to_user((दीर्घ __user *)arg, &next, माप(next)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक mmc_ioctl_cdrom_last_written(काष्ठा cdrom_device_info *cdi,
						 व्योम __user *arg)
अणु
	पूर्णांक ret;
	दीर्घ last = 0;
	cd_dbg(CD_DO_IOCTL, "entering CDROM_LAST_WRITTEN\n");
	ret = cdrom_get_last_written(cdi, &last);
	अगर (ret)
		वापस ret;
	अगर (in_compat_syscall())
		वापस put_user(last, (__s32 __user *)arg);

	वापस put_user(last, (दीर्घ __user *)arg);
पूर्ण

अटल पूर्णांक mmc_ioctl(काष्ठा cdrom_device_info *cdi, अचिन्हित पूर्णांक cmd,
		     अचिन्हित दीर्घ arg)
अणु
	काष्ठा packet_command cgc;
	व्योम __user *userptr = (व्योम __user *)arg;

	स_रखो(&cgc, 0, माप(cgc));

	/* build a unअगरied command and queue it through
	   cकरो->generic_packet() */
	चयन (cmd) अणु
	हाल CDROMREADRAW:
	हाल CDROMREADMODE1:
	हाल CDROMREADMODE2:
		वापस mmc_ioctl_cdrom_पढ़ो_data(cdi, userptr, &cgc, cmd);
	हाल CDROMREADAUDIO:
		वापस mmc_ioctl_cdrom_पढ़ो_audio(cdi, userptr);
	हाल CDROMSUBCHNL:
		वापस mmc_ioctl_cdrom_subchannel(cdi, userptr);
	हाल CDROMPLAYMSF:
		वापस mmc_ioctl_cdrom_play_msf(cdi, userptr, &cgc);
	हाल CDROMPLAYBLK:
		वापस mmc_ioctl_cdrom_play_blk(cdi, userptr, &cgc);
	हाल CDROMVOLCTRL:
	हाल CDROMVOLREAD:
		वापस mmc_ioctl_cdrom_volume(cdi, userptr, &cgc, cmd);
	हाल CDROMSTART:
	हाल CDROMSTOP:
		वापस mmc_ioctl_cdrom_start_stop(cdi, &cgc, cmd);
	हाल CDROMPAUSE:
	हाल CDROMRESUME:
		वापस mmc_ioctl_cdrom_छोड़ो_resume(cdi, &cgc, cmd);
	हाल DVD_READ_STRUCT:
		वापस mmc_ioctl_dvd_पढ़ो_काष्ठा(cdi, userptr, &cgc);
	हाल DVD_AUTH:
		वापस mmc_ioctl_dvd_auth(cdi, userptr);
	हाल CDROM_NEXT_WRITABLE:
		वापस mmc_ioctl_cdrom_next_writable(cdi, userptr);
	हाल CDROM_LAST_WRITTEN:
		वापस mmc_ioctl_cdrom_last_written(cdi, userptr);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

/*
 * Just about every imaginable ioctl is supported in the Unअगरorm layer
 * these days.
 * ATAPI / SCSI specअगरic code now मुख्यly resides in mmc_ioctl().
 */
पूर्णांक cdrom_ioctl(काष्ठा cdrom_device_info *cdi, काष्ठा block_device *bdev,
		भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक ret;

	/*
	 * Try the generic SCSI command ioctl's first.
	 */
	ret = scsi_cmd_blk_ioctl(bdev, mode, cmd, argp);
	अगर (ret != -ENOTTY)
		वापस ret;

	चयन (cmd) अणु
	हाल CDROMMULTISESSION:
		वापस cdrom_ioctl_multisession(cdi, argp);
	हाल CDROMEJECT:
		वापस cdrom_ioctl_eject(cdi);
	हाल CDROMCLOSETRAY:
		वापस cdrom_ioctl_बंदtray(cdi);
	हाल CDROMEJECT_SW:
		वापस cdrom_ioctl_eject_sw(cdi, arg);
	हाल CDROM_MEDIA_CHANGED:
		वापस cdrom_ioctl_media_changed(cdi, arg);
	हाल CDROM_SET_OPTIONS:
		वापस cdrom_ioctl_set_options(cdi, arg);
	हाल CDROM_CLEAR_OPTIONS:
		वापस cdrom_ioctl_clear_options(cdi, arg);
	हाल CDROM_SELECT_SPEED:
		वापस cdrom_ioctl_select_speed(cdi, arg);
	हाल CDROM_SELECT_DISC:
		वापस cdrom_ioctl_select_disc(cdi, arg);
	हाल CDROMRESET:
		वापस cdrom_ioctl_reset(cdi, bdev);
	हाल CDROM_LOCKDOOR:
		वापस cdrom_ioctl_lock_करोor(cdi, arg);
	हाल CDROM_DEBUG:
		वापस cdrom_ioctl_debug(cdi, arg);
	हाल CDROM_GET_CAPABILITY:
		वापस cdrom_ioctl_get_capability(cdi);
	हाल CDROM_GET_MCN:
		वापस cdrom_ioctl_get_mcn(cdi, argp);
	हाल CDROM_DRIVE_STATUS:
		वापस cdrom_ioctl_drive_status(cdi, arg);
	हाल CDROM_DISC_STATUS:
		वापस cdrom_ioctl_disc_status(cdi);
	हाल CDROM_CHANGER_NSLOTS:
		वापस cdrom_ioctl_changer_nslots(cdi);
	पूर्ण

	/*
	 * Use the ioctls that are implemented through the generic_packet()
	 * पूर्णांकerface. this may look at bit funny, but अगर -ENOTTY is
	 * वापसed that particular ioctl is not implemented and we
	 * let it go through the device specअगरic ones.
	 */
	अगर (CDROM_CAN(CDC_GENERIC_PACKET)) अणु
		ret = mmc_ioctl(cdi, cmd, arg);
		अगर (ret != -ENOTTY)
			वापस ret;
	पूर्ण

	/*
	 * Note: most of the cd_dbg() calls are commented out here,
	 * because they fill up the sys log when CD players poll
	 * the drive.
	 */
	चयन (cmd) अणु
	हाल CDROMSUBCHNL:
		वापस cdrom_ioctl_get_subchnl(cdi, argp);
	हाल CDROMREADTOCHDR:
		वापस cdrom_ioctl_पढ़ो_tochdr(cdi, argp);
	हाल CDROMREADTOCENTRY:
		वापस cdrom_ioctl_पढ़ो_tocentry(cdi, argp);
	हाल CDROMPLAYMSF:
		वापस cdrom_ioctl_play_msf(cdi, argp);
	हाल CDROMPLAYTRKIND:
		वापस cdrom_ioctl_play_trkind(cdi, argp);
	हाल CDROMVOLCTRL:
		वापस cdrom_ioctl_volctrl(cdi, argp);
	हाल CDROMVOLREAD:
		वापस cdrom_ioctl_volपढ़ो(cdi, argp);
	हाल CDROMSTART:
	हाल CDROMSTOP:
	हाल CDROMPAUSE:
	हाल CDROMRESUME:
		वापस cdrom_ioctl_audioctl(cdi, cmd);
	पूर्ण

	वापस -ENOSYS;
पूर्ण

EXPORT_SYMBOL(cdrom_get_last_written);
EXPORT_SYMBOL(रेजिस्टर_cdrom);
EXPORT_SYMBOL(unरेजिस्टर_cdrom);
EXPORT_SYMBOL(cdrom_खोलो);
EXPORT_SYMBOL(cdrom_release);
EXPORT_SYMBOL(cdrom_ioctl);
EXPORT_SYMBOL(cdrom_number_of_slots);
EXPORT_SYMBOL(cdrom_mode_select);
EXPORT_SYMBOL(cdrom_mode_sense);
EXPORT_SYMBOL(init_cdrom_command);
EXPORT_SYMBOL(cdrom_get_media_event);

#अगर_घोषित CONFIG_SYSCTL

#घोषणा CDROM_STR_SIZE 1000

अटल काष्ठा cdrom_sysctl_settings अणु
	अक्षर	info[CDROM_STR_SIZE];	/* general info */
	पूर्णांक	स्वतःबंद;		/* बंद tray upon mount, etc */
	पूर्णांक	स्वतःeject;		/* eject on umount */
	पूर्णांक	debug;			/* turn on debugging messages */
	पूर्णांक	lock;			/* lock the करोor on device खोलो */
	पूर्णांक	check;			/* check media type */
पूर्ण cdrom_sysctl_settings;

क्रमागत cdrom_prपूर्णांक_option अणु
	CTL_NAME,
	CTL_SPEED,
	CTL_SLOTS,
	CTL_CAPABILITY
पूर्ण;

अटल पूर्णांक cdrom_prपूर्णांक_info(स्थिर अक्षर *header, पूर्णांक val, अक्षर *info,
				पूर्णांक *pos, क्रमागत cdrom_prपूर्णांक_option option)
अणु
	स्थिर पूर्णांक max_size = माप(cdrom_sysctl_settings.info);
	काष्ठा cdrom_device_info *cdi;
	पूर्णांक ret;

	ret = scnम_लिखो(info + *pos, max_size - *pos, header);
	अगर (!ret)
		वापस 1;

	*pos += ret;

	list_क्रम_each_entry(cdi, &cdrom_list, list) अणु
		चयन (option) अणु
		हाल CTL_NAME:
			ret = scnम_लिखो(info + *pos, max_size - *pos,
					"\t%s", cdi->name);
			अवरोध;
		हाल CTL_SPEED:
			ret = scnम_लिखो(info + *pos, max_size - *pos,
					"\t%d", cdi->speed);
			अवरोध;
		हाल CTL_SLOTS:
			ret = scnम_लिखो(info + *pos, max_size - *pos,
					"\t%d", cdi->capacity);
			अवरोध;
		हाल CTL_CAPABILITY:
			ret = scnम_लिखो(info + *pos, max_size - *pos,
					"\t%d", CDROM_CAN(val) != 0);
			अवरोध;
		शेष:
			pr_info("invalid option%d\n", option);
			वापस 1;
		पूर्ण
		अगर (!ret)
			वापस 1;
		*pos += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdrom_sysctl_info(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
                           व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक pos;
	अक्षर *info = cdrom_sysctl_settings.info;
	स्थिर पूर्णांक max_size = माप(cdrom_sysctl_settings.info);
	
	अगर (!*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	mutex_lock(&cdrom_mutex);

	pos = प्र_लिखो(info, "CD-ROM information, " VERSION "\n");
	
	अगर (cdrom_prपूर्णांक_info("\ndrive name:\t", 0, info, &pos, CTL_NAME))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\ndrive speed:\t", 0, info, &pos, CTL_SPEED))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\ndrive # of slots:", 0, info, &pos, CTL_SLOTS))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan close tray:\t",
				CDC_CLOSE_TRAY, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan open tray:\t",
				CDC_OPEN_TRAY, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan lock tray:\t",
				CDC_LOCK, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan change speed:",
				CDC_SELECT_SPEED, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan select disk:",
				CDC_SELECT_DISC, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan read multisession:",
				CDC_MULTI_SESSION, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan read MCN:\t",
				CDC_MCN, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nReports media changed:",
				CDC_MEDIA_CHANGED, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan play audio:\t",
				CDC_PLAY_AUDIO, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write CD-R:\t",
				CDC_CD_R, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write CD-RW:",
				CDC_CD_RW, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan read DVD:\t",
				CDC_DVD, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write DVD-R:",
				CDC_DVD_R, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write DVD-RAM:",
				CDC_DVD_RAM, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan read MRW:\t",
				CDC_MRW, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write MRW:\t",
				CDC_MRW_W, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (cdrom_prपूर्णांक_info("\nCan write RAM:\t",
				CDC_RAM, info, &pos, CTL_CAPABILITY))
		जाओ करोne;
	अगर (!scnम_लिखो(info + pos, max_size - pos, "\n\n"))
		जाओ करोne;
करोit:
	mutex_unlock(&cdrom_mutex);
	वापस proc_करोstring(ctl, ग_लिखो, buffer, lenp, ppos);
करोne:
	pr_info("info buffer too small\n");
	जाओ करोit;
पूर्ण

/* Unक्रमtunately, per device settings are not implemented through
   procfs/sysctl yet. When they are, this will naturally disappear. For now
   just update all drives. Later this will become the ढाँचा on which
   new रेजिस्टरed drives will be based. */
अटल व्योम cdrom_update_settings(व्योम)
अणु
	काष्ठा cdrom_device_info *cdi;

	mutex_lock(&cdrom_mutex);
	list_क्रम_each_entry(cdi, &cdrom_list, list) अणु
		अगर (स्वतःबंद && CDROM_CAN(CDC_CLOSE_TRAY))
			cdi->options |= CDO_AUTO_CLOSE;
		अन्यथा अगर (!स्वतःबंद)
			cdi->options &= ~CDO_AUTO_CLOSE;
		अगर (स्वतःeject && CDROM_CAN(CDC_OPEN_TRAY))
			cdi->options |= CDO_AUTO_EJECT;
		अन्यथा अगर (!स्वतःeject)
			cdi->options &= ~CDO_AUTO_EJECT;
		अगर (lockकरोor && CDROM_CAN(CDC_LOCK))
			cdi->options |= CDO_LOCK;
		अन्यथा अगर (!lockकरोor)
			cdi->options &= ~CDO_LOCK;
		अगर (check_media_type)
			cdi->options |= CDO_CHECK_TYPE;
		अन्यथा
			cdi->options &= ~CDO_CHECK_TYPE;
	पूर्ण
	mutex_unlock(&cdrom_mutex);
पूर्ण

अटल पूर्णांक cdrom_sysctl_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;
	
	ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो) अणु
	
		/* we only care क्रम 1 or 0. */
		स्वतःबंद        = !!cdrom_sysctl_settings.स्वतःबंद;
		स्वतःeject        = !!cdrom_sysctl_settings.स्वतःeject;
		debug	         = !!cdrom_sysctl_settings.debug;
		lockकरोor         = !!cdrom_sysctl_settings.lock;
		check_media_type = !!cdrom_sysctl_settings.check;

		/* update the option flags according to the changes. we
		   करोn't have per device options through sysctl yet,
		   but we will have and then this will disappear. */
		cdrom_update_settings();
	पूर्ण

        वापस ret;
पूर्ण

/* Place files in /proc/sys/dev/cdrom */
अटल काष्ठा ctl_table cdrom_table[] = अणु
	अणु
		.procname	= "info",
		.data		= &cdrom_sysctl_settings.info, 
		.maxlen		= CDROM_STR_SIZE,
		.mode		= 0444,
		.proc_handler	= cdrom_sysctl_info,
	पूर्ण,
	अणु
		.procname	= "autoclose",
		.data		= &cdrom_sysctl_settings.स्वतःबंद,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= cdrom_sysctl_handler,
	पूर्ण,
	अणु
		.procname	= "autoeject",
		.data		= &cdrom_sysctl_settings.स्वतःeject,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= cdrom_sysctl_handler,
	पूर्ण,
	अणु
		.procname	= "debug",
		.data		= &cdrom_sysctl_settings.debug,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= cdrom_sysctl_handler,
	पूर्ण,
	अणु
		.procname	= "lock",
		.data		= &cdrom_sysctl_settings.lock,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= cdrom_sysctl_handler,
	पूर्ण,
	अणु
		.procname	= "check_media",
		.data		= &cdrom_sysctl_settings.check,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= cdrom_sysctl_handler
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table cdrom_cdrom_table[] = अणु
	अणु
		.procname	= "cdrom",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= cdrom_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Make sure that /proc/sys/dev is there */
अटल काष्ठा ctl_table cdrom_root_table[] = अणु
	अणु
		.procname	= "dev",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= cdrom_cdrom_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल काष्ठा ctl_table_header *cdrom_sysctl_header;

अटल व्योम cdrom_sysctl_रेजिस्टर(व्योम)
अणु
	अटल atomic_t initialized = ATOMIC_INIT(0);

	अगर (!atomic_add_unless(&initialized, 1, 1))
		वापस;

	cdrom_sysctl_header = रेजिस्टर_sysctl_table(cdrom_root_table);

	/* set the शेषs */
	cdrom_sysctl_settings.स्वतःबंद = स्वतःबंद;
	cdrom_sysctl_settings.स्वतःeject = स्वतःeject;
	cdrom_sysctl_settings.debug = debug;
	cdrom_sysctl_settings.lock = lockकरोor;
	cdrom_sysctl_settings.check = check_media_type;
पूर्ण

अटल व्योम cdrom_sysctl_unरेजिस्टर(व्योम)
अणु
	अगर (cdrom_sysctl_header)
		unरेजिस्टर_sysctl_table(cdrom_sysctl_header);
पूर्ण

#अन्यथा /* CONFIG_SYSCTL */

अटल व्योम cdrom_sysctl_रेजिस्टर(व्योम)
अणु
पूर्ण

अटल व्योम cdrom_sysctl_unरेजिस्टर(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल पूर्णांक __init cdrom_init(व्योम)
अणु
	cdrom_sysctl_रेजिस्टर();

	वापस 0;
पूर्ण

अटल व्योम __निकास cdrom_निकास(व्योम)
अणु
	pr_info("Uniform CD-ROM driver unloaded\n");
	cdrom_sysctl_unरेजिस्टर();
पूर्ण

module_init(cdrom_init);
module_निकास(cdrom_निकास);
MODULE_LICENSE("GPL");
