<शैली गुरु>
/* 
	pcd.c	(c) 1997-8  Grant R. Guenther <grant@torque.net>
		            Under the terms of the GNU General Public License.

	This is a high-level driver क्रम parallel port ATAPI CD-ROM
        drives based on chips supported by the paride module.

        By शेष, the driver will स्वतःprobe क्रम a single parallel
        port ATAPI CD-ROM drive, but अगर their inभागidual parameters are
        specअगरied, the driver can handle up to 4 drives.

        The behaviour of the pcd driver can be altered by setting
        some parameters from the insmod command line.  The following
        parameters are adjustable:

            drive0      These four arguments can be arrays of       
            drive1      1-6 पूर्णांकegers as follows:
            drive2
            drive3      <prt>,<pro>,<uni>,<mod>,<slv>,<dly>

                        Where,

                <prt>   is the base of the parallel port address क्रम
                        the corresponding drive.  (required)

                <pro>   is the protocol number क्रम the adapter that
                        supports this drive.  These numbers are
                        logged by 'paride' when the protocol modules
                        are initialised.  (0 अगर not given)

                <uni>   क्रम those adapters that support chained
                        devices, this is the unit selector क्रम the
                        chain of devices on the given port.  It should
                        be zero क्रम devices that करोn't support chaining.
                        (0 अगर not given)

                <mod>   this can be -1 to choose the best mode, or one
                        of the mode numbers supported by the adapter.
                        (-1 अगर not given)

		<slv>   ATAPI CD-ROMs can be jumpered to master or slave.
			Set this to 0 to choose the master drive, 1 to
                        choose the slave, -1 (the शेष) to choose the
			first drive found.

                <dly>   some parallel ports require the driver to 
                        go more slowly.  -1 sets a शेष value that
                        should work with the chosen protocol.  Otherwise,
                        set this to a small पूर्णांकeger, the larger it is
                        the slower the port i/o.  In some हालs, setting
                        this to zero will speed up the device. (शेष -1)
                        
            major       You may use this parameter to override the
                        शेष major number (46) that this driver
                        will use.  Be sure to change the device
                        name as well.

            name        This parameter is a अक्षरacter string that
                        contains the name the kernel will use क्रम this
                        device (in /proc output, क्रम instance).
                        (शेष "pcd")

            verbose     This parameter controls the amount of logging
                        that the driver will करो.  Set it to 0 क्रम
                        normal operation, 1 to see स्वतःprobe progress
                        messages, or 2 to see additional debugging
                        output.  (शेष 0)
  
            nice        This parameter controls the driver's use of
                        idle CPU समय, at the expense of some speed.
 
	If this driver is built पूर्णांकo the kernel, you can use the
        following kernel command line parameters, with the same values
        as the corresponding module parameters listed above:

	    pcd.drive0
	    pcd.drive1
	    pcd.drive2
	    pcd.drive3
	    pcd.nice

        In addition, you can use the parameter pcd.disable to disable
        the driver entirely.

*/

/* Changes:

	1.01	GRG 1998.01.24	Added test unit पढ़ोy support
	1.02    GRG 1998.05.06  Changes to pcd_completion, पढ़ोy_रुको,
				and loosen पूर्णांकerpretation of ATAPI
			        standard क्रम clearing error status.
				Use spinlocks. Eliminate sti().
	1.03    GRG 1998.06.16  Eliminated an Ugh
	1.04	GRG 1998.08.15  Added extra debugging, improvements to
				pcd_completion, use HZ in loop timing
	1.05	GRG 1998.08.16	Conक्रमmed to "Uniform CD-ROM" standard
	1.06    GRG 1998.08.19  Added audio ioctl support
	1.07    GRG 1998.09.24  Increased reset समयout, added jumbo support

*/

#घोषणा	PCD_VERSION	"1.07"
#घोषणा PCD_MAJOR	46
#घोषणा PCD_NAME	"pcd"
#घोषणा PCD_UNITS	4

/* Here are things one can override from the insmod command.
   Most are स्वतःprobed by paride unless set here.  Verbose is off
   by शेष.

*/

अटल पूर्णांक verbose = 0;
अटल पूर्णांक major = PCD_MAJOR;
अटल अक्षर *name = PCD_NAME;
अटल पूर्णांक nice = 0;
अटल पूर्णांक disable = 0;

अटल पूर्णांक drive0[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive1[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive2[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive3[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;

अटल पूर्णांक (*drives[4])[6] = अणु&drive0, &drive1, &drive2, &drive3पूर्ण;
अटल पूर्णांक pcd_drive_count;

क्रमागत अणुD_PRT, D_PRO, D_UNI, D_MOD, D_SLV, D_DLYपूर्ण;

/* end of parameters */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

अटल DEFINE_MUTEX(pcd_mutex);
अटल DEFINE_SPINLOCK(pcd_lock);

module_param(verbose, पूर्णांक, 0644);
module_param(major, पूर्णांक, 0);
module_param(name, अक्षरp, 0);
module_param(nice, पूर्णांक, 0);
module_param_array(drive0, पूर्णांक, शून्य, 0);
module_param_array(drive1, पूर्णांक, शून्य, 0);
module_param_array(drive2, पूर्णांक, शून्य, 0);
module_param_array(drive3, पूर्णांक, शून्य, 0);

#समावेश "paride.h"
#समावेश "pseudo.h"

#घोषणा PCD_RETRIES	     5
#घोषणा PCD_TMO		   800	/* समयout in jअगरfies */
#घोषणा PCD_DELAY           50	/* spin delay in uS */
#घोषणा PCD_READY_TMO	    20	/* in seconds */
#घोषणा PCD_RESET_TMO	   100	/* in tenths of a second */

#घोषणा PCD_SPIN	(1000000*PCD_TMO)/(HZ*PCD_DELAY)

#घोषणा IDE_ERR		0x01
#घोषणा IDE_DRQ         0x08
#घोषणा IDE_READY       0x40
#घोषणा IDE_BUSY        0x80

अटल पूर्णांक pcd_खोलो(काष्ठा cdrom_device_info *cdi, पूर्णांक purpose);
अटल व्योम pcd_release(काष्ठा cdrom_device_info *cdi);
अटल पूर्णांक pcd_drive_status(काष्ठा cdrom_device_info *cdi, पूर्णांक slot_nr);
अटल अचिन्हित पूर्णांक pcd_check_events(काष्ठा cdrom_device_info *cdi,
				     अचिन्हित पूर्णांक clearing, पूर्णांक slot_nr);
अटल पूर्णांक pcd_tray_move(काष्ठा cdrom_device_info *cdi, पूर्णांक position);
अटल पूर्णांक pcd_lock_करोor(काष्ठा cdrom_device_info *cdi, पूर्णांक lock);
अटल पूर्णांक pcd_drive_reset(काष्ठा cdrom_device_info *cdi);
अटल पूर्णांक pcd_get_mcn(काष्ठा cdrom_device_info *cdi, काष्ठा cdrom_mcn *mcn);
अटल पूर्णांक pcd_audio_ioctl(काष्ठा cdrom_device_info *cdi,
			   अचिन्हित पूर्णांक cmd, व्योम *arg);
अटल पूर्णांक pcd_packet(काष्ठा cdrom_device_info *cdi,
		      काष्ठा packet_command *cgc);

अटल पूर्णांक pcd_detect(व्योम);
अटल व्योम pcd_probe_capabilities(व्योम);
अटल व्योम करो_pcd_पढ़ो_drq(व्योम);
अटल blk_status_t pcd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd);
अटल व्योम करो_pcd_पढ़ो(व्योम);

काष्ठा pcd_unit अणु
	काष्ठा pi_adapter pia;	/* पूर्णांकerface to paride layer */
	काष्ठा pi_adapter *pi;
	पूर्णांक drive;		/* master/slave */
	पूर्णांक last_sense;		/* result of last request sense */
	पूर्णांक changed;		/* media change seen */
	पूर्णांक present;		/* करोes this unit exist ? */
	अक्षर *name;		/* pcd0, pcd1, etc */
	काष्ठा cdrom_device_info info;	/* unअगरorm cdrom पूर्णांकerface */
	काष्ठा gendisk *disk;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा list_head rq_list;
पूर्ण;

अटल काष्ठा pcd_unit pcd[PCD_UNITS];

अटल अक्षर pcd_scratch[64];
अटल अक्षर pcd_buffer[2048];	/* raw block buffer */
अटल पूर्णांक pcd_bufblk = -1;	/* block in buffer, in CD units,
				   -1 क्रम nothing there. See also
				   pd_unit.
				 */

/* the variables below are used मुख्यly in the I/O request engine, which
   processes only one request at a समय.
*/

अटल काष्ठा pcd_unit *pcd_current; /* current request's drive */
अटल काष्ठा request *pcd_req;
अटल पूर्णांक pcd_retries;		/* retries on current request */
अटल पूर्णांक pcd_busy;		/* request being processed ? */
अटल पूर्णांक pcd_sector;		/* address of next requested sector */
अटल पूर्णांक pcd_count;		/* number of blocks still to करो */
अटल अक्षर *pcd_buf;		/* buffer क्रम request in progress */
अटल व्योम *par_drv;		/* reference of parport driver */

/* kernel glue काष्ठाures */

अटल पूर्णांक pcd_block_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा pcd_unit *cd = bdev->bd_disk->निजी_data;
	पूर्णांक ret;

	bdev_check_media_change(bdev);

	mutex_lock(&pcd_mutex);
	ret = cdrom_खोलो(&cd->info, bdev, mode);
	mutex_unlock(&pcd_mutex);

	वापस ret;
पूर्ण

अटल व्योम pcd_block_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा pcd_unit *cd = disk->निजी_data;
	mutex_lock(&pcd_mutex);
	cdrom_release(&cd->info, mode);
	mutex_unlock(&pcd_mutex);
पूर्ण

अटल पूर्णांक pcd_block_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pcd_unit *cd = bdev->bd_disk->निजी_data;
	पूर्णांक ret;

	mutex_lock(&pcd_mutex);
	ret = cdrom_ioctl(&cd->info, bdev, mode, cmd, arg);
	mutex_unlock(&pcd_mutex);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक pcd_block_check_events(काष्ठा gendisk *disk,
					   अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा pcd_unit *cd = disk->निजी_data;
	वापस cdrom_check_events(&cd->info, clearing);
पूर्ण

अटल स्थिर काष्ठा block_device_operations pcd_bकरोps = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pcd_block_खोलो,
	.release	= pcd_block_release,
	.ioctl		= pcd_block_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= blkdev_compat_ptr_ioctl,
#पूर्ण_अगर
	.check_events	= pcd_block_check_events,
पूर्ण;

अटल स्थिर काष्ठा cdrom_device_ops pcd_करोps = अणु
	.खोलो		= pcd_खोलो,
	.release	= pcd_release,
	.drive_status	= pcd_drive_status,
	.check_events	= pcd_check_events,
	.tray_move	= pcd_tray_move,
	.lock_करोor	= pcd_lock_करोor,
	.get_mcn	= pcd_get_mcn,
	.reset		= pcd_drive_reset,
	.audio_ioctl	= pcd_audio_ioctl,
	.generic_packet	= pcd_packet,
	.capability	= CDC_CLOSE_TRAY | CDC_OPEN_TRAY | CDC_LOCK |
			  CDC_MCN | CDC_MEDIA_CHANGED | CDC_RESET |
			  CDC_PLAY_AUDIO | CDC_GENERIC_PACKET | CDC_CD_R |
			  CDC_CD_RW,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops pcd_mq_ops = अणु
	.queue_rq	= pcd_queue_rq,
पूर्ण;

अटल व्योम pcd_init_units(व्योम)
अणु
	काष्ठा pcd_unit *cd;
	पूर्णांक unit;

	pcd_drive_count = 0;
	क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
		काष्ठा gendisk *disk = alloc_disk(1);

		अगर (!disk)
			जारी;

		disk->queue = blk_mq_init_sq_queue(&cd->tag_set, &pcd_mq_ops,
						   1, BLK_MQ_F_SHOULD_MERGE);
		अगर (IS_ERR(disk->queue)) अणु
			disk->queue = शून्य;
			put_disk(disk);
			जारी;
		पूर्ण

		INIT_LIST_HEAD(&cd->rq_list);
		disk->queue->queuedata = cd;
		blk_queue_bounce_limit(disk->queue, BLK_BOUNCE_HIGH);
		cd->disk = disk;
		cd->pi = &cd->pia;
		cd->present = 0;
		cd->last_sense = 0;
		cd->changed = 1;
		cd->drive = (*drives[unit])[D_SLV];
		अगर ((*drives[unit])[D_PRT])
			pcd_drive_count++;

		cd->name = &cd->info.name[0];
		snम_लिखो(cd->name, माप(cd->info.name), "%s%d", name, unit);
		cd->info.ops = &pcd_करोps;
		cd->info.handle = cd;
		cd->info.speed = 0;
		cd->info.capacity = 1;
		cd->info.mask = 0;
		disk->major = major;
		disk->first_minor = unit;
		म_नकल(disk->disk_name, cd->name);	/* umm... */
		disk->fops = &pcd_bकरोps;
		disk->flags = GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE;
		disk->events = DISK_EVENT_MEDIA_CHANGE;
	पूर्ण
पूर्ण

अटल पूर्णांक pcd_खोलो(काष्ठा cdrom_device_info *cdi, पूर्णांक purpose)
अणु
	काष्ठा pcd_unit *cd = cdi->handle;
	अगर (!cd->present)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम pcd_release(काष्ठा cdrom_device_info *cdi)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक status_reg(काष्ठा pcd_unit *cd)
अणु
	वापस pi_पढ़ो_regr(cd->pi, 1, 6);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_reg(काष्ठा pcd_unit *cd, पूर्णांक reg)
अणु
	वापस pi_पढ़ो_regr(cd->pi, 0, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा pcd_unit *cd, पूर्णांक reg, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(cd->pi, 0, reg, val);
पूर्ण

अटल पूर्णांक pcd_रुको(काष्ठा pcd_unit *cd, पूर्णांक go, पूर्णांक stop, अक्षर *fun, अक्षर *msg)
अणु
	पूर्णांक j, r, e, s, p;

	j = 0;
	जबतक ((((r = status_reg(cd)) & go) || (stop && (!(r & stop))))
	       && (j++ < PCD_SPIN))
		udelay(PCD_DELAY);

	अगर ((r & (IDE_ERR & stop)) || (j > PCD_SPIN)) अणु
		s = पढ़ो_reg(cd, 7);
		e = पढ़ो_reg(cd, 1);
		p = पढ़ो_reg(cd, 2);
		अगर (j > PCD_SPIN)
			e |= 0x100;
		अगर (fun)
			prपूर्णांकk("%s: %s %s: alt=0x%x stat=0x%x err=0x%x"
			       " loop=%d phase=%d\n",
			       cd->name, fun, msg, r, s, e, j, p);
		वापस (s << 8) + r;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcd_command(काष्ठा pcd_unit *cd, अक्षर *cmd, पूर्णांक dlen, अक्षर *fun)
अणु
	pi_connect(cd->pi);

	ग_लिखो_reg(cd, 6, 0xa0 + 0x10 * cd->drive);

	अगर (pcd_रुको(cd, IDE_BUSY | IDE_DRQ, 0, fun, "before command")) अणु
		pi_disconnect(cd->pi);
		वापस -1;
	पूर्ण

	ग_लिखो_reg(cd, 4, dlen % 256);
	ग_लिखो_reg(cd, 5, dlen / 256);
	ग_लिखो_reg(cd, 7, 0xa0);	/* ATAPI packet command */

	अगर (pcd_रुको(cd, IDE_BUSY, IDE_DRQ, fun, "command DRQ")) अणु
		pi_disconnect(cd->pi);
		वापस -1;
	पूर्ण

	अगर (पढ़ो_reg(cd, 2) != 1) अणु
		prपूर्णांकk("%s: %s: command phase error\n", cd->name, fun);
		pi_disconnect(cd->pi);
		वापस -1;
	पूर्ण

	pi_ग_लिखो_block(cd->pi, cmd, 12);

	वापस 0;
पूर्ण

अटल पूर्णांक pcd_completion(काष्ठा pcd_unit *cd, अक्षर *buf, अक्षर *fun)
अणु
	पूर्णांक r, d, p, n, k, j;

	r = -1;
	k = 0;
	j = 0;

	अगर (!pcd_रुको(cd, IDE_BUSY, IDE_DRQ | IDE_READY | IDE_ERR,
		      fun, "completion")) अणु
		r = 0;
		जबतक (पढ़ो_reg(cd, 7) & IDE_DRQ) अणु
			d = पढ़ो_reg(cd, 4) + 256 * पढ़ो_reg(cd, 5);
			n = (d + 3) & 0xfffc;
			p = पढ़ो_reg(cd, 2) & 3;

			अगर ((p == 2) && (n > 0) && (j == 0)) अणु
				pi_पढ़ो_block(cd->pi, buf, n);
				अगर (verbose > 1)
					prपूर्णांकk("%s: %s: Read %d bytes\n",
					       cd->name, fun, n);
				r = 0;
				j++;
			पूर्ण अन्यथा अणु
				अगर (verbose > 1)
					prपूर्णांकk
					    ("%s: %s: Unexpected phase %d, d=%d, k=%d\n",
					     cd->name, fun, p, d, k);
				अगर (verbose < 2)
					prपूर्णांकk_once(
					    "%s: WARNING: ATAPI phase errors\n",
					    cd->name);
				mdelay(1);
			पूर्ण
			अगर (k++ > PCD_TMO) अणु
				prपूर्णांकk("%s: Stuck DRQ\n", cd->name);
				अवरोध;
			पूर्ण
			अगर (pcd_रुको
			    (cd, IDE_BUSY, IDE_DRQ | IDE_READY | IDE_ERR, fun,
			     "completion")) अणु
				r = -1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	pi_disconnect(cd->pi);

	वापस r;
पूर्ण

अटल व्योम pcd_req_sense(काष्ठा pcd_unit *cd, अक्षर *fun)
अणु
	अक्षर rs_cmd[12] = अणु 0x03, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[16];
	पूर्णांक r, c;

	r = pcd_command(cd, rs_cmd, 16, "Request sense");
	mdelay(1);
	अगर (!r)
		pcd_completion(cd, buf, "Request sense");

	cd->last_sense = -1;
	c = 2;
	अगर (!r) अणु
		अगर (fun)
			prपूर्णांकk("%s: %s: Sense key: %x, ASC: %x, ASQ: %x\n",
			       cd->name, fun, buf[2] & 0xf, buf[12], buf[13]);
		c = buf[2] & 0xf;
		cd->last_sense =
		    c | ((buf[12] & 0xff) << 8) | ((buf[13] & 0xff) << 16);
	पूर्ण
	अगर ((c == 2) || (c == 6))
		cd->changed = 1;
पूर्ण

अटल पूर्णांक pcd_atapi(काष्ठा pcd_unit *cd, अक्षर *cmd, पूर्णांक dlen, अक्षर *buf, अक्षर *fun)
अणु
	पूर्णांक r;

	r = pcd_command(cd, cmd, dlen, fun);
	mdelay(1);
	अगर (!r)
		r = pcd_completion(cd, buf, fun);
	अगर (r)
		pcd_req_sense(cd, fun);

	वापस r;
पूर्ण

अटल पूर्णांक pcd_packet(काष्ठा cdrom_device_info *cdi, काष्ठा packet_command *cgc)
अणु
	वापस pcd_atapi(cdi->handle, cgc->cmd, cgc->buflen, cgc->buffer,
			 "generic packet");
पूर्ण

#घोषणा DBMSG(msg)	((verbose>1)?(msg):शून्य)

अटल अचिन्हित पूर्णांक pcd_check_events(काष्ठा cdrom_device_info *cdi,
				     अचिन्हित पूर्णांक clearing, पूर्णांक slot_nr)
अणु
	काष्ठा pcd_unit *cd = cdi->handle;
	पूर्णांक res = cd->changed;
	अगर (res)
		cd->changed = 0;
	वापस res ? DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

अटल पूर्णांक pcd_lock_करोor(काष्ठा cdrom_device_info *cdi, पूर्णांक lock)
अणु
	अक्षर un_cmd[12] = अणु 0x1e, 0, 0, 0, lock, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	वापस pcd_atapi(cdi->handle, un_cmd, 0, pcd_scratch,
			 lock ? "lock door" : "unlock door");
पूर्ण

अटल पूर्णांक pcd_tray_move(काष्ठा cdrom_device_info *cdi, पूर्णांक position)
अणु
	अक्षर ej_cmd[12] = अणु 0x1b, 0, 0, 0, 3 - position, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	वापस pcd_atapi(cdi->handle, ej_cmd, 0, pcd_scratch,
			 position ? "eject" : "close tray");
पूर्ण

अटल व्योम pcd_sleep(पूर्णांक cs)
अणु
	schedule_समयout_पूर्णांकerruptible(cs);
पूर्ण

अटल पूर्णांक pcd_reset(काष्ठा pcd_unit *cd)
अणु
	पूर्णांक i, k, flg;
	पूर्णांक expect[5] = अणु 1, 1, 1, 0x14, 0xeb पूर्ण;

	pi_connect(cd->pi);
	ग_लिखो_reg(cd, 6, 0xa0 + 0x10 * cd->drive);
	ग_लिखो_reg(cd, 7, 8);

	pcd_sleep(20 * HZ / 1000);	/* delay a bit */

	k = 0;
	जबतक ((k++ < PCD_RESET_TMO) && (status_reg(cd) & IDE_BUSY))
		pcd_sleep(HZ / 10);

	flg = 1;
	क्रम (i = 0; i < 5; i++)
		flg &= (पढ़ो_reg(cd, i + 1) == expect[i]);

	अगर (verbose) अणु
		prपूर्णांकk("%s: Reset (%d) signature = ", cd->name, k);
		क्रम (i = 0; i < 5; i++)
			prपूर्णांकk("%3x", पढ़ो_reg(cd, i + 1));
		अगर (!flg)
			prपूर्णांकk(" (incorrect)");
		prपूर्णांकk("\n");
	पूर्ण

	pi_disconnect(cd->pi);
	वापस flg - 1;
पूर्ण

अटल पूर्णांक pcd_drive_reset(काष्ठा cdrom_device_info *cdi)
अणु
	वापस pcd_reset(cdi->handle);
पूर्ण

अटल पूर्णांक pcd_पढ़ोy_रुको(काष्ठा pcd_unit *cd, पूर्णांक पंचांगo)
अणु
	अक्षर tr_cmd[12] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक k, p;

	k = 0;
	जबतक (k < पंचांगo) अणु
		cd->last_sense = 0;
		pcd_atapi(cd, tr_cmd, 0, शून्य, DBMSG("test unit ready"));
		p = cd->last_sense;
		अगर (!p)
			वापस 0;
		अगर (!(((p & 0xffff) == 0x0402) || ((p & 0xff) == 6)))
			वापस p;
		k++;
		pcd_sleep(HZ);
	पूर्ण
	वापस 0x000020;	/* समयout */
पूर्ण

अटल पूर्णांक pcd_drive_status(काष्ठा cdrom_device_info *cdi, पूर्णांक slot_nr)
अणु
	अक्षर rc_cmd[12] = अणु 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	काष्ठा pcd_unit *cd = cdi->handle;

	अगर (pcd_पढ़ोy_रुको(cd, PCD_READY_TMO))
		वापस CDS_DRIVE_NOT_READY;
	अगर (pcd_atapi(cd, rc_cmd, 8, pcd_scratch, DBMSG("check media")))
		वापस CDS_NO_DISC;
	वापस CDS_DISC_OK;
पूर्ण

अटल पूर्णांक pcd_identअगरy(काष्ठा pcd_unit *cd, अक्षर *id)
अणु
	पूर्णांक k, s;
	अक्षर id_cmd[12] = अणु 0x12, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	pcd_bufblk = -1;

	s = pcd_atapi(cd, id_cmd, 36, pcd_buffer, "identify");

	अगर (s)
		वापस -1;
	अगर ((pcd_buffer[0] & 0x1f) != 5) अणु
		अगर (verbose)
			prपूर्णांकk("%s: %s is not a CD-ROM\n",
			       cd->name, cd->drive ? "Slave" : "Master");
		वापस -1;
	पूर्ण
	स_नकल(id, pcd_buffer + 16, 16);
	id[16] = 0;
	k = 16;
	जबतक ((k >= 0) && (id[k] <= 0x20)) अणु
		id[k] = 0;
		k--;
	पूर्ण

	prपूर्णांकk("%s: %s: %s\n", cd->name, cd->drive ? "Slave" : "Master", id);

	वापस 0;
पूर्ण

/*
 * वापसs  0, with id set अगर drive is detected
 *	    -1, अगर drive detection failed
 */
अटल पूर्णांक pcd_probe(काष्ठा pcd_unit *cd, पूर्णांक ms, अक्षर *id)
अणु
	अगर (ms == -1) अणु
		क्रम (cd->drive = 0; cd->drive <= 1; cd->drive++)
			अगर (!pcd_reset(cd) && !pcd_identअगरy(cd, id))
				वापस 0;
	पूर्ण अन्यथा अणु
		cd->drive = ms;
		अगर (!pcd_reset(cd) && !pcd_identअगरy(cd, id))
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम pcd_probe_capabilities(व्योम)
अणु
	पूर्णांक unit, r;
	अक्षर buffer[32];
	अक्षर cmd[12] = अणु 0x5a, 1 << 3, 0x2a, 0, 0, 0, 0, 18, 0, 0, 0, 0 पूर्ण;
	काष्ठा pcd_unit *cd;

	क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
		अगर (!cd->present)
			जारी;
		r = pcd_atapi(cd, cmd, 18, buffer, "mode sense capabilities");
		अगर (r)
			जारी;
		/* we should now have the cap page */
		अगर ((buffer[11] & 1) == 0)
			cd->info.mask |= CDC_CD_R;
		अगर ((buffer[11] & 2) == 0)
			cd->info.mask |= CDC_CD_RW;
		अगर ((buffer[12] & 1) == 0)
			cd->info.mask |= CDC_PLAY_AUDIO;
		अगर ((buffer[14] & 1) == 0)
			cd->info.mask |= CDC_LOCK;
		अगर ((buffer[14] & 8) == 0)
			cd->info.mask |= CDC_OPEN_TRAY;
		अगर ((buffer[14] >> 6) == 0)
			cd->info.mask |= CDC_CLOSE_TRAY;
	पूर्ण
पूर्ण

अटल पूर्णांक pcd_detect(व्योम)
अणु
	अक्षर id[18];
	पूर्णांक k, unit;
	काष्ठा pcd_unit *cd;

	prपूर्णांकk("%s: %s version %s, major %d, nice %d\n",
	       name, name, PCD_VERSION, major, nice);

	par_drv = pi_रेजिस्टर_driver(name);
	अगर (!par_drv) अणु
		pr_err("failed to register %s driver\n", name);
		वापस -1;
	पूर्ण

	k = 0;
	अगर (pcd_drive_count == 0) अणु /* nothing spec'd - so स्वतःprobe क्रम 1 */
		cd = pcd;
		अगर (cd->disk && pi_init(cd->pi, 1, -1, -1, -1, -1, -1,
			    pcd_buffer, PI_PCD, verbose, cd->name)) अणु
			अगर (!pcd_probe(cd, -1, id)) अणु
				cd->present = 1;
				k++;
			पूर्ण अन्यथा
				pi_release(cd->pi);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
			पूर्णांक *conf = *drives[unit];
			अगर (!conf[D_PRT])
				जारी;
			अगर (!cd->disk)
				जारी;
			अगर (!pi_init(cd->pi, 0, conf[D_PRT], conf[D_MOD],
				     conf[D_UNI], conf[D_PRO], conf[D_DLY],
				     pcd_buffer, PI_PCD, verbose, cd->name)) 
				जारी;
			अगर (!pcd_probe(cd, conf[D_SLV], id)) अणु
				cd->present = 1;
				k++;
			पूर्ण अन्यथा
				pi_release(cd->pi);
		पूर्ण
	पूर्ण
	अगर (k)
		वापस 0;

	prपूर्णांकk("%s: No CD-ROM drive found\n", name);
	क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
		अगर (!cd->disk)
			जारी;
		blk_cleanup_queue(cd->disk->queue);
		cd->disk->queue = शून्य;
		blk_mq_मुक्त_tag_set(&cd->tag_set);
		put_disk(cd->disk);
	पूर्ण
	pi_unरेजिस्टर_driver(par_drv);
	वापस -1;
पूर्ण

/* I/O request processing */
अटल पूर्णांक pcd_queue;

अटल पूर्णांक set_next_request(व्योम)
अणु
	काष्ठा pcd_unit *cd;
	पूर्णांक old_pos = pcd_queue;

	करो अणु
		cd = &pcd[pcd_queue];
		अगर (++pcd_queue == PCD_UNITS)
			pcd_queue = 0;
		अगर (cd->present && !list_empty(&cd->rq_list)) अणु
			pcd_req = list_first_entry(&cd->rq_list, काष्ठा request,
							queuelist);
			list_del_init(&pcd_req->queuelist);
			blk_mq_start_request(pcd_req);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pcd_queue != old_pos);

	वापस pcd_req != शून्य;
पूर्ण

अटल व्योम pcd_request(व्योम)
अणु
	काष्ठा pcd_unit *cd;

	अगर (pcd_busy)
		वापस;

	अगर (!pcd_req && !set_next_request())
		वापस;

	cd = pcd_req->rq_disk->निजी_data;
	अगर (cd != pcd_current)
		pcd_bufblk = -1;
	pcd_current = cd;
	pcd_sector = blk_rq_pos(pcd_req);
	pcd_count = blk_rq_cur_sectors(pcd_req);
	pcd_buf = bio_data(pcd_req->bio);
	pcd_busy = 1;
	ps_set_पूर्णांकr(करो_pcd_पढ़ो, शून्य, 0, nice);
पूर्ण

अटल blk_status_t pcd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा pcd_unit *cd = hctx->queue->queuedata;

	अगर (rq_data_dir(bd->rq) != READ) अणु
		blk_mq_start_request(bd->rq);
		वापस BLK_STS_IOERR;
	पूर्ण

	spin_lock_irq(&pcd_lock);
	list_add_tail(&bd->rq->queuelist, &cd->rq_list);
	pcd_request();
	spin_unlock_irq(&pcd_lock);

	वापस BLK_STS_OK;
पूर्ण

अटल अंतरभूत व्योम next_request(blk_status_t err)
अणु
	अचिन्हित दीर्घ saved_flags;

	spin_lock_irqsave(&pcd_lock, saved_flags);
	अगर (!blk_update_request(pcd_req, err, blk_rq_cur_bytes(pcd_req))) अणु
		__blk_mq_end_request(pcd_req, err);
		pcd_req = शून्य;
	पूर्ण
	pcd_busy = 0;
	pcd_request();
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
पूर्ण

अटल पूर्णांक pcd_पढ़ोy(व्योम)
अणु
	वापस (((status_reg(pcd_current) & (IDE_BUSY | IDE_DRQ)) == IDE_DRQ));
पूर्ण

अटल व्योम pcd_transfer(व्योम)
अणु

	जबतक (pcd_count && (pcd_sector / 4 == pcd_bufblk)) अणु
		पूर्णांक o = (pcd_sector % 4) * 512;
		स_नकल(pcd_buf, pcd_buffer + o, 512);
		pcd_count--;
		pcd_buf += 512;
		pcd_sector++;
	पूर्ण
पूर्ण

अटल व्योम pcd_start(व्योम)
अणु
	पूर्णांक b, i;
	अक्षर rd_cmd[12] = अणु 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 पूर्ण;

	pcd_bufblk = pcd_sector / 4;
	b = pcd_bufblk;
	क्रम (i = 0; i < 4; i++) अणु
		rd_cmd[5 - i] = b & 0xff;
		b = b >> 8;
	पूर्ण

	अगर (pcd_command(pcd_current, rd_cmd, 2048, "read block")) अणु
		pcd_bufblk = -1;
		next_request(BLK_STS_IOERR);
		वापस;
	पूर्ण

	mdelay(1);

	ps_set_पूर्णांकr(करो_pcd_पढ़ो_drq, pcd_पढ़ोy, PCD_TMO, nice);
पूर्ण

अटल व्योम करो_pcd_पढ़ो(व्योम)
अणु
	pcd_busy = 1;
	pcd_retries = 0;
	pcd_transfer();
	अगर (!pcd_count) अणु
		next_request(0);
		वापस;
	पूर्ण

	pi_करो_claimed(pcd_current->pi, pcd_start);
पूर्ण

अटल व्योम करो_pcd_पढ़ो_drq(व्योम)
अणु
	अचिन्हित दीर्घ saved_flags;

	अगर (pcd_completion(pcd_current, pcd_buffer, "read block")) अणु
		अगर (pcd_retries < PCD_RETRIES) अणु
			mdelay(1);
			pcd_retries++;
			pi_करो_claimed(pcd_current->pi, pcd_start);
			वापस;
		पूर्ण
		pcd_bufblk = -1;
		next_request(BLK_STS_IOERR);
		वापस;
	पूर्ण

	करो_pcd_पढ़ो();
	spin_lock_irqsave(&pcd_lock, saved_flags);
	pcd_request();
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
पूर्ण

/* the audio_ioctl stuff is adapted from sr_ioctl.c */

अटल पूर्णांक pcd_audio_ioctl(काष्ठा cdrom_device_info *cdi, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा pcd_unit *cd = cdi->handle;

	चयन (cmd) अणु

	हाल CDROMREADTOCHDR:

		अणु
			अक्षर cmd[12] =
			    अणु GPCMD_READ_TOC_PMA_ATIP, 0, 0, 0, 0, 0, 0, 0, 12,
			 0, 0, 0 पूर्ण;
			काष्ठा cdrom_tochdr *tochdr =
			    (काष्ठा cdrom_tochdr *) arg;
			अक्षर buffer[32];
			पूर्णांक r;

			r = pcd_atapi(cd, cmd, 12, buffer, "read toc header");

			tochdr->cdth_trk0 = buffer[2];
			tochdr->cdth_trk1 = buffer[3];

			वापस r ? -EIO : 0;
		पूर्ण

	हाल CDROMREADTOCENTRY:

		अणु
			अक्षर cmd[12] =
			    अणु GPCMD_READ_TOC_PMA_ATIP, 0, 0, 0, 0, 0, 0, 0, 12,
			 0, 0, 0 पूर्ण;

			काष्ठा cdrom_tocentry *tocentry =
			    (काष्ठा cdrom_tocentry *) arg;
			अचिन्हित अक्षर buffer[32];
			पूर्णांक r;

			cmd[1] =
			    (tocentry->cdte_क्रमmat == CDROM_MSF ? 0x02 : 0);
			cmd[6] = tocentry->cdte_track;

			r = pcd_atapi(cd, cmd, 12, buffer, "read toc entry");

			tocentry->cdte_ctrl = buffer[5] & 0xf;
			tocentry->cdte_adr = buffer[5] >> 4;
			tocentry->cdte_datamode =
			    (tocentry->cdte_ctrl & 0x04) ? 1 : 0;
			अगर (tocentry->cdte_क्रमmat == CDROM_MSF) अणु
				tocentry->cdte_addr.msf.minute = buffer[9];
				tocentry->cdte_addr.msf.second = buffer[10];
				tocentry->cdte_addr.msf.frame = buffer[11];
			पूर्ण अन्यथा
				tocentry->cdte_addr.lba =
				    (((((buffer[8] << 8) + buffer[9]) << 8)
				      + buffer[10]) << 8) + buffer[11];

			वापस r ? -EIO : 0;
		पूर्ण

	शेष:

		वापस -ENOSYS;
	पूर्ण
पूर्ण

अटल पूर्णांक pcd_get_mcn(काष्ठा cdrom_device_info *cdi, काष्ठा cdrom_mcn *mcn)
अणु
	अक्षर cmd[12] =
	    अणु GPCMD_READ_SUBCHANNEL, 0, 0x40, 2, 0, 0, 0, 0, 24, 0, 0, 0 पूर्ण;
	अक्षर buffer[32];

	अगर (pcd_atapi(cdi->handle, cmd, 24, buffer, "get mcn"))
		वापस -EIO;

	स_नकल(mcn->medium_catalog_number, buffer + 9, 13);
	mcn->medium_catalog_number[13] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक __init pcd_init(व्योम)
अणु
	काष्ठा pcd_unit *cd;
	पूर्णांक unit;

	अगर (disable)
		वापस -EINVAL;

	pcd_init_units();

	अगर (pcd_detect())
		वापस -ENODEV;

	/* get the atapi capabilities page */
	pcd_probe_capabilities();

	अगर (रेजिस्टर_blkdev(major, name)) अणु
		क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
			अगर (!cd->disk)
				जारी;

			blk_cleanup_queue(cd->disk->queue);
			blk_mq_मुक्त_tag_set(&cd->tag_set);
			put_disk(cd->disk);
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
		अगर (cd->present) अणु
			रेजिस्टर_cdrom(cd->disk, &cd->info);
			cd->disk->निजी_data = cd;
			add_disk(cd->disk);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास pcd_निकास(व्योम)
अणु
	काष्ठा pcd_unit *cd;
	पूर्णांक unit;

	क्रम (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) अणु
		अगर (!cd->disk)
			जारी;

		अगर (cd->present) अणु
			del_gendisk(cd->disk);
			pi_release(cd->pi);
			unरेजिस्टर_cdrom(&cd->info);
		पूर्ण
		blk_cleanup_queue(cd->disk->queue);
		blk_mq_मुक्त_tag_set(&cd->tag_set);
		put_disk(cd->disk);
	पूर्ण
	unरेजिस्टर_blkdev(major, name);
	pi_unरेजिस्टर_driver(par_drv);
पूर्ण

MODULE_LICENSE("GPL");
module_init(pcd_init)
module_निकास(pcd_निकास)
