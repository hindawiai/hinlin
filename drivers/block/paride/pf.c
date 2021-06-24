<शैली गुरु>
/* 
        pf.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                            Under the terms of the GNU General Public License.

        This is the high-level driver क्रम parallel port ATAPI disk
        drives based on chips supported by the paride module.

        By शेष, the driver will स्वतःprobe क्रम a single parallel
        port ATAPI disk drive, but अगर their inभागidual parameters are
        specअगरied, the driver can handle up to 4 drives.

        The behaviour of the pf driver can be altered by setting
        some parameters from the insmod command line.  The following
        parameters are adjustable:

            drive0      These four arguments can be arrays of       
            drive1      1-7 पूर्णांकegers as follows:
            drive2
            drive3      <prt>,<pro>,<uni>,<mod>,<slv>,<lun>,<dly>

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

                <slv>   ATAPI CDroms can be jumpered to master or slave.
                        Set this to 0 to choose the master drive, 1 to
                        choose the slave, -1 (the शेष) to choose the
                        first drive found.

		<lun>   Some ATAPI devices support multiple LUNs.
                        One example is the ATAPI PD/CD drive from
                        Matshita/Panasonic.  This device has a 
                        CD drive on LUN 0 and a PD drive on LUN 1.
                        By शेष, the driver will search क्रम the
                        first LUN with a supported device.  Set 
                        this parameter to क्रमce it to use a specअगरic
                        LUN.  (शेष -1)

                <dly>   some parallel ports require the driver to 
                        go more slowly.  -1 sets a शेष value that
                        should work with the chosen protocol.  Otherwise,
                        set this to a small पूर्णांकeger, the larger it is
                        the slower the port i/o.  In some हालs, setting
                        this to zero will speed up the device. (शेष -1)

	    major	You may use this parameter to override the
			शेष major number (47) that this driver
			will use.  Be sure to change the device
			name as well.

	    name	This parameter is a अक्षरacter string that
			contains the name the kernel will use क्रम this
			device (in /proc output, क्रम instance).
			(शेष "pf").

            cluster     The driver will attempt to aggregate requests
                        क्रम adjacent blocks पूर्णांकo larger multi-block
                        clusters.  The maximum cluster size (in 512
                        byte sectors) is set with this parameter.
                        (शेष 64)

            verbose     This parameter controls the amount of logging
                        that the driver will करो.  Set it to 0 क्रम
                        normal operation, 1 to see स्वतःprobe progress
                        messages, or 2 to see additional debugging
                        output.  (शेष 0)
 
	    nice        This parameter controls the driver's use of
			idle CPU समय, at the expense of some speed.

        If this driver is built पूर्णांकo the kernel, you can use the
        following command line parameters, with the same values
        as the corresponding module parameters listed above:

            pf.drive0
            pf.drive1
            pf.drive2
            pf.drive3
	    pf.cluster
            pf.nice

        In addition, you can use the parameter pf.disable to disable
        the driver entirely.

*/

/* Changes:

	1.01	GRG 1998.05.03  Changes क्रम SMP.  Eliminate sti().
				Fix क्रम drives that करोn't clear STAT_ERR
			        until after next CDB delivered.
				Small change in pf_completion to round
				up transfer size.
	1.02    GRG 1998.06.16  Eliminated an Ugh
	1.03    GRG 1998.08.16  Use HZ in loop timings, extra debugging
	1.04    GRG 1998.09.24  Added jumbo support

*/

#घोषणा PF_VERSION      "1.04"
#घोषणा PF_MAJOR	47
#घोषणा PF_NAME		"pf"
#घोषणा PF_UNITS	4

#समावेश <linux/types.h>

/* Here are things one can override from the insmod command.
   Most are स्वतःprobed by paride unless set here.  Verbose is off
   by शेष.

*/

अटल bool verbose = 0;
अटल पूर्णांक major = PF_MAJOR;
अटल अक्षर *name = PF_NAME;
अटल पूर्णांक cluster = 64;
अटल पूर्णांक nice = 0;
अटल पूर्णांक disable = 0;

अटल पूर्णांक drive0[7] = अणु 0, 0, 0, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive1[7] = अणु 0, 0, 0, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive2[7] = अणु 0, 0, 0, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive3[7] = अणु 0, 0, 0, -1, -1, -1, -1 पूर्ण;

अटल पूर्णांक (*drives[4])[7] = अणु&drive0, &drive1, &drive2, &drive3पूर्ण;
अटल पूर्णांक pf_drive_count;

क्रमागत अणुD_PRT, D_PRO, D_UNI, D_MOD, D_SLV, D_LUN, D_DLYपूर्ण;

/* end of parameters */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

अटल DEFINE_MUTEX(pf_mutex);
अटल DEFINE_SPINLOCK(pf_spin_lock);

module_param(verbose, bool, 0644);
module_param(major, पूर्णांक, 0);
module_param(name, अक्षरp, 0);
module_param(cluster, पूर्णांक, 0);
module_param(nice, पूर्णांक, 0);
module_param_array(drive0, पूर्णांक, शून्य, 0);
module_param_array(drive1, पूर्णांक, शून्य, 0);
module_param_array(drive2, पूर्णांक, शून्य, 0);
module_param_array(drive3, पूर्णांक, शून्य, 0);

#समावेश "paride.h"
#समावेश "pseudo.h"

/* स्थिरants क्रम faking geometry numbers */

#घोषणा PF_FD_MAX	8192	/* use FD geometry under this size */
#घोषणा PF_FD_HDS	2
#घोषणा PF_FD_SPT	18
#घोषणा PF_HD_HDS	64
#घोषणा PF_HD_SPT	32

#घोषणा PF_MAX_RETRIES  5
#घोषणा PF_TMO          800	/* पूर्णांकerrupt समयout in jअगरfies */
#घोषणा PF_SPIN_DEL     50	/* spin delay in micro-seconds  */

#घोषणा PF_SPIN         (1000000*PF_TMO)/(HZ*PF_SPIN_DEL)

#घोषणा STAT_ERR        0x00001
#घोषणा STAT_INDEX      0x00002
#घोषणा STAT_ECC        0x00004
#घोषणा STAT_DRQ        0x00008
#घोषणा STAT_SEEK       0x00010
#घोषणा STAT_WRERR      0x00020
#घोषणा STAT_READY      0x00040
#घोषणा STAT_BUSY       0x00080

#घोषणा ATAPI_REQ_SENSE		0x03
#घोषणा ATAPI_LOCK		0x1e
#घोषणा ATAPI_DOOR		0x1b
#घोषणा ATAPI_MODE_SENSE	0x5a
#घोषणा ATAPI_CAPACITY		0x25
#घोषणा ATAPI_IDENTIFY		0x12
#घोषणा ATAPI_READ_10		0x28
#घोषणा ATAPI_WRITE_10		0x2a

अटल पूर्णांक pf_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल blk_status_t pf_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				स्थिर काष्ठा blk_mq_queue_data *bd);
अटल पूर्णांक pf_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक pf_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo);

अटल व्योम pf_release(काष्ठा gendisk *disk, भ_शेषe_t mode);

अटल पूर्णांक pf_detect(व्योम);
अटल व्योम करो_pf_पढ़ो(व्योम);
अटल व्योम करो_pf_पढ़ो_start(व्योम);
अटल व्योम करो_pf_ग_लिखो(व्योम);
अटल व्योम करो_pf_ग_लिखो_start(व्योम);
अटल व्योम करो_pf_पढ़ो_drq(व्योम);
अटल व्योम करो_pf_ग_लिखो_करोne(व्योम);

#घोषणा PF_NM           0
#घोषणा PF_RO           1
#घोषणा PF_RW           2

#घोषणा PF_NAMELEN      8

काष्ठा pf_unit अणु
	काष्ठा pi_adapter pia;	/* पूर्णांकerface to paride layer */
	काष्ठा pi_adapter *pi;
	पूर्णांक removable;		/* removable media device  ?  */
	पूर्णांक media_status;	/* media present ?  WP ? */
	पूर्णांक drive;		/* drive */
	पूर्णांक lun;
	पूर्णांक access;		/* count of active खोलोs ... */
	पूर्णांक present;		/* device present ? */
	अक्षर name[PF_NAMELEN];	/* pf0, pf1, ... */
	काष्ठा gendisk *disk;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा list_head rq_list;
पूर्ण;

अटल काष्ठा pf_unit units[PF_UNITS];

अटल पूर्णांक pf_identअगरy(काष्ठा pf_unit *pf);
अटल व्योम pf_lock(काष्ठा pf_unit *pf, पूर्णांक func);
अटल व्योम pf_eject(काष्ठा pf_unit *pf);
अटल अचिन्हित पूर्णांक pf_check_events(काष्ठा gendisk *disk,
				    अचिन्हित पूर्णांक clearing);

अटल अक्षर pf_scratch[512];	/* scratch block buffer */

/* the variables below are used मुख्यly in the I/O request engine, which
   processes only one request at a समय.
*/

अटल पूर्णांक pf_retries = 0;	/* i/o error retry count */
अटल पूर्णांक pf_busy = 0;		/* request being processed ? */
अटल काष्ठा request *pf_req;	/* current request */
अटल पूर्णांक pf_block;		/* address of next requested block */
अटल पूर्णांक pf_count;		/* number of blocks still to करो */
अटल पूर्णांक pf_run;		/* sectors in current cluster */
अटल पूर्णांक pf_cmd;		/* current command READ/WRITE */
अटल काष्ठा pf_unit *pf_current;/* unit of current request */
अटल पूर्णांक pf_mask;		/* stopper क्रम pseuकरो-पूर्णांक */
अटल अक्षर *pf_buf;		/* buffer क्रम request in progress */
अटल व्योम *par_drv;		/* reference of parport driver */

/* kernel glue काष्ठाures */

अटल स्थिर काष्ठा block_device_operations pf_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pf_खोलो,
	.release	= pf_release,
	.ioctl		= pf_ioctl,
	.compat_ioctl	= pf_ioctl,
	.getgeo		= pf_getgeo,
	.check_events	= pf_check_events,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops pf_mq_ops = अणु
	.queue_rq	= pf_queue_rq,
पूर्ण;

अटल व्योम __init pf_init_units(व्योम)
अणु
	काष्ठा pf_unit *pf;
	पूर्णांक unit;

	pf_drive_count = 0;
	क्रम (unit = 0, pf = units; unit < PF_UNITS; unit++, pf++) अणु
		काष्ठा gendisk *disk;

		disk = alloc_disk(1);
		अगर (!disk)
			जारी;

		disk->queue = blk_mq_init_sq_queue(&pf->tag_set, &pf_mq_ops,
							1, BLK_MQ_F_SHOULD_MERGE);
		अगर (IS_ERR(disk->queue)) अणु
			disk->queue = शून्य;
			put_disk(disk);
			जारी;
		पूर्ण

		INIT_LIST_HEAD(&pf->rq_list);
		disk->queue->queuedata = pf;
		blk_queue_max_segments(disk->queue, cluster);
		blk_queue_bounce_limit(disk->queue, BLK_BOUNCE_HIGH);
		pf->disk = disk;
		pf->pi = &pf->pia;
		pf->media_status = PF_NM;
		pf->drive = (*drives[unit])[D_SLV];
		pf->lun = (*drives[unit])[D_LUN];
		snम_लिखो(pf->name, PF_NAMELEN, "%s%d", name, unit);
		disk->major = major;
		disk->first_minor = unit;
		म_नकल(disk->disk_name, pf->name);
		disk->fops = &pf_fops;
		disk->events = DISK_EVENT_MEDIA_CHANGE;
		अगर (!(*drives[unit])[D_PRT])
			pf_drive_count++;
	पूर्ण
पूर्ण

अटल पूर्णांक pf_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा pf_unit *pf = bdev->bd_disk->निजी_data;
	पूर्णांक ret;

	mutex_lock(&pf_mutex);
	pf_identअगरy(pf);

	ret = -ENODEV;
	अगर (pf->media_status == PF_NM)
		जाओ out;

	ret = -EROFS;
	अगर ((pf->media_status == PF_RO) && (mode & FMODE_WRITE))
		जाओ out;

	ret = 0;
	pf->access++;
	अगर (pf->removable)
		pf_lock(pf, 1);
out:
	mutex_unlock(&pf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक pf_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा pf_unit *pf = bdev->bd_disk->निजी_data;
	sector_t capacity = get_capacity(pf->disk);

	अगर (capacity < PF_FD_MAX) अणु
		geo->cylinders = sector_भाग(capacity, PF_FD_HDS * PF_FD_SPT);
		geo->heads = PF_FD_HDS;
		geo->sectors = PF_FD_SPT;
	पूर्ण अन्यथा अणु
		geo->cylinders = sector_भाग(capacity, PF_HD_HDS * PF_HD_SPT);
		geo->heads = PF_HD_HDS;
		geo->sectors = PF_HD_SPT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pf_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pf_unit *pf = bdev->bd_disk->निजी_data;

	अगर (cmd != CDROMEJECT)
		वापस -EINVAL;

	अगर (pf->access != 1)
		वापस -EBUSY;
	mutex_lock(&pf_mutex);
	pf_eject(pf);
	mutex_unlock(&pf_mutex);

	वापस 0;
पूर्ण

अटल व्योम pf_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा pf_unit *pf = disk->निजी_data;

	mutex_lock(&pf_mutex);
	अगर (pf->access <= 0) अणु
		mutex_unlock(&pf_mutex);
		WARN_ON(1);
		वापस;
	पूर्ण

	pf->access--;

	अगर (!pf->access && pf->removable)
		pf_lock(pf, 0);

	mutex_unlock(&pf_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक pf_check_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक clearing)
अणु
	वापस DISK_EVENT_MEDIA_CHANGE;
पूर्ण

अटल अंतरभूत पूर्णांक status_reg(काष्ठा pf_unit *pf)
अणु
	वापस pi_पढ़ो_regr(pf->pi, 1, 6);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_reg(काष्ठा pf_unit *pf, पूर्णांक reg)
अणु
	वापस pi_पढ़ो_regr(pf->pi, 0, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा pf_unit *pf, पूर्णांक reg, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(pf->pi, 0, reg, val);
पूर्ण

अटल पूर्णांक pf_रुको(काष्ठा pf_unit *pf, पूर्णांक go, पूर्णांक stop, अक्षर *fun, अक्षर *msg)
अणु
	पूर्णांक j, r, e, s, p;

	j = 0;
	जबतक ((((r = status_reg(pf)) & go) || (stop && (!(r & stop))))
	       && (j++ < PF_SPIN))
		udelay(PF_SPIN_DEL);

	अगर ((r & (STAT_ERR & stop)) || (j > PF_SPIN)) अणु
		s = पढ़ो_reg(pf, 7);
		e = पढ़ो_reg(pf, 1);
		p = पढ़ो_reg(pf, 2);
		अगर (j > PF_SPIN)
			e |= 0x100;
		अगर (fun)
			prपूर्णांकk("%s: %s %s: alt=0x%x stat=0x%x err=0x%x"
			       " loop=%d phase=%d\n",
			       pf->name, fun, msg, r, s, e, j, p);
		वापस (e << 8) + s;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pf_command(काष्ठा pf_unit *pf, अक्षर *cmd, पूर्णांक dlen, अक्षर *fun)
अणु
	pi_connect(pf->pi);

	ग_लिखो_reg(pf, 6, 0xa0+0x10*pf->drive);

	अगर (pf_रुको(pf, STAT_BUSY | STAT_DRQ, 0, fun, "before command")) अणु
		pi_disconnect(pf->pi);
		वापस -1;
	पूर्ण

	ग_लिखो_reg(pf, 4, dlen % 256);
	ग_लिखो_reg(pf, 5, dlen / 256);
	ग_लिखो_reg(pf, 7, 0xa0);	/* ATAPI packet command */

	अगर (pf_रुको(pf, STAT_BUSY, STAT_DRQ, fun, "command DRQ")) अणु
		pi_disconnect(pf->pi);
		वापस -1;
	पूर्ण

	अगर (पढ़ो_reg(pf, 2) != 1) अणु
		prपूर्णांकk("%s: %s: command phase error\n", pf->name, fun);
		pi_disconnect(pf->pi);
		वापस -1;
	पूर्ण

	pi_ग_लिखो_block(pf->pi, cmd, 12);

	वापस 0;
पूर्ण

अटल पूर्णांक pf_completion(काष्ठा pf_unit *pf, अक्षर *buf, अक्षर *fun)
अणु
	पूर्णांक r, s, n;

	r = pf_रुको(pf, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
		    fun, "completion");

	अगर ((पढ़ो_reg(pf, 2) & 2) && (पढ़ो_reg(pf, 7) & STAT_DRQ)) अणु
		n = (((पढ़ो_reg(pf, 4) + 256 * पढ़ो_reg(pf, 5)) +
		      3) & 0xfffc);
		pi_पढ़ो_block(pf->pi, buf, n);
	पूर्ण

	s = pf_रुको(pf, STAT_BUSY, STAT_READY | STAT_ERR, fun, "data done");

	pi_disconnect(pf->pi);

	वापस (r ? r : s);
पूर्ण

अटल व्योम pf_req_sense(काष्ठा pf_unit *pf, पूर्णांक quiet)
अणु
	अक्षर rs_cmd[12] =
	    अणु ATAPI_REQ_SENSE, pf->lun << 5, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[16];
	पूर्णांक r;

	r = pf_command(pf, rs_cmd, 16, "Request sense");
	mdelay(1);
	अगर (!r)
		pf_completion(pf, buf, "Request sense");

	अगर ((!r) && (!quiet))
		prपूर्णांकk("%s: Sense key: %x, ASC: %x, ASQ: %x\n",
		       pf->name, buf[2] & 0xf, buf[12], buf[13]);
पूर्ण

अटल पूर्णांक pf_atapi(काष्ठा pf_unit *pf, अक्षर *cmd, पूर्णांक dlen, अक्षर *buf, अक्षर *fun)
अणु
	पूर्णांक r;

	r = pf_command(pf, cmd, dlen, fun);
	mdelay(1);
	अगर (!r)
		r = pf_completion(pf, buf, fun);
	अगर (r)
		pf_req_sense(pf, !fun);

	वापस r;
पूर्ण

अटल व्योम pf_lock(काष्ठा pf_unit *pf, पूर्णांक func)
अणु
	अक्षर lo_cmd[12] = अणु ATAPI_LOCK, pf->lun << 5, 0, 0, func, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	pf_atapi(pf, lo_cmd, 0, pf_scratch, func ? "lock" : "unlock");
पूर्ण

अटल व्योम pf_eject(काष्ठा pf_unit *pf)
अणु
	अक्षर ej_cmd[12] = अणु ATAPI_DOOR, pf->lun << 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	pf_lock(pf, 0);
	pf_atapi(pf, ej_cmd, 0, pf_scratch, "eject");
पूर्ण

#घोषणा PF_RESET_TMO   30	/* in tenths of a second */

अटल व्योम pf_sleep(पूर्णांक cs)
अणु
	schedule_समयout_पूर्णांकerruptible(cs);
पूर्ण

/* the ATAPI standard actually specअगरies the contents of all 7 रेजिस्टरs
   after a reset, but the specअगरication is ambiguous concerning the last
   two bytes, and dअगरferent drives पूर्णांकerpret the standard dअगरferently.
 */

अटल पूर्णांक pf_reset(काष्ठा pf_unit *pf)
अणु
	पूर्णांक i, k, flg;
	पूर्णांक expect[5] = अणु 1, 1, 1, 0x14, 0xeb पूर्ण;

	pi_connect(pf->pi);
	ग_लिखो_reg(pf, 6, 0xa0+0x10*pf->drive);
	ग_लिखो_reg(pf, 7, 8);

	pf_sleep(20 * HZ / 1000);

	k = 0;
	जबतक ((k++ < PF_RESET_TMO) && (status_reg(pf) & STAT_BUSY))
		pf_sleep(HZ / 10);

	flg = 1;
	क्रम (i = 0; i < 5; i++)
		flg &= (पढ़ो_reg(pf, i + 1) == expect[i]);

	अगर (verbose) अणु
		prपूर्णांकk("%s: Reset (%d) signature = ", pf->name, k);
		क्रम (i = 0; i < 5; i++)
			prपूर्णांकk("%3x", पढ़ो_reg(pf, i + 1));
		अगर (!flg)
			prपूर्णांकk(" (incorrect)");
		prपूर्णांकk("\n");
	पूर्ण

	pi_disconnect(pf->pi);
	वापस flg - 1;
पूर्ण

अटल व्योम pf_mode_sense(काष्ठा pf_unit *pf)
अणु
	अक्षर ms_cmd[12] =
	    अणु ATAPI_MODE_SENSE, pf->lun << 5, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0 पूर्ण;
	अक्षर buf[8];

	pf_atapi(pf, ms_cmd, 8, buf, "mode sense");
	pf->media_status = PF_RW;
	अगर (buf[3] & 0x80)
		pf->media_status = PF_RO;
पूर्ण

अटल व्योम xs(अक्षर *buf, अक्षर *targ, पूर्णांक offs, पूर्णांक len)
अणु
	पूर्णांक j, k, l;

	j = 0;
	l = 0;
	क्रम (k = 0; k < len; k++)
		अगर ((buf[k + offs] != 0x20) || (buf[k + offs] != l))
			l = targ[j++] = buf[k + offs];
	अगर (l == 0x20)
		j--;
	targ[j] = 0;
पूर्ण

अटल पूर्णांक xl(अक्षर *buf, पूर्णांक offs)
अणु
	पूर्णांक v, k;

	v = 0;
	क्रम (k = 0; k < 4; k++)
		v = v * 256 + (buf[k + offs] & 0xff);
	वापस v;
पूर्ण

अटल व्योम pf_get_capacity(काष्ठा pf_unit *pf)
अणु
	अक्षर rc_cmd[12] = अणु ATAPI_CAPACITY, pf->lun << 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[8];
	पूर्णांक bs;

	अगर (pf_atapi(pf, rc_cmd, 8, buf, "get capacity")) अणु
		pf->media_status = PF_NM;
		वापस;
	पूर्ण
	set_capacity(pf->disk, xl(buf, 0) + 1);
	bs = xl(buf, 4);
	अगर (bs != 512) अणु
		set_capacity(pf->disk, 0);
		अगर (verbose)
			prपूर्णांकk("%s: Drive %d, LUN %d,"
			       " unsupported block size %d\n",
			       pf->name, pf->drive, pf->lun, bs);
	पूर्ण
पूर्ण

अटल पूर्णांक pf_identअगरy(काष्ठा pf_unit *pf)
अणु
	पूर्णांक dt, s;
	अक्षर *ms[2] = अणु "master", "slave" पूर्ण;
	अक्षर mf[10], id[18];
	अक्षर id_cmd[12] =
	    अणु ATAPI_IDENTIFY, pf->lun << 5, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[36];

	s = pf_atapi(pf, id_cmd, 36, buf, "identify");
	अगर (s)
		वापस -1;

	dt = buf[0] & 0x1f;
	अगर ((dt != 0) && (dt != 7)) अणु
		अगर (verbose)
			prपूर्णांकk("%s: Drive %d, LUN %d, unsupported type %d\n",
			       pf->name, pf->drive, pf->lun, dt);
		वापस -1;
	पूर्ण

	xs(buf, mf, 8, 8);
	xs(buf, id, 16, 16);

	pf->removable = (buf[1] & 0x80);

	pf_mode_sense(pf);
	pf_mode_sense(pf);
	pf_mode_sense(pf);

	pf_get_capacity(pf);

	prपूर्णांकk("%s: %s %s, %s LUN %d, type %d",
	       pf->name, mf, id, ms[pf->drive], pf->lun, dt);
	अगर (pf->removable)
		prपूर्णांकk(", removable");
	अगर (pf->media_status == PF_NM)
		prपूर्णांकk(", no media\n");
	अन्यथा अणु
		अगर (pf->media_status == PF_RO)
			prपूर्णांकk(", RO");
		prपूर्णांकk(", %llu blocks\n",
			(अचिन्हित दीर्घ दीर्घ)get_capacity(pf->disk));
	पूर्ण
	वापस 0;
पूर्ण

/*	वापसs  0, with id set अगर drive is detected
	        -1, अगर drive detection failed
*/
अटल पूर्णांक pf_probe(काष्ठा pf_unit *pf)
अणु
	अगर (pf->drive == -1) अणु
		क्रम (pf->drive = 0; pf->drive <= 1; pf->drive++)
			अगर (!pf_reset(pf)) अणु
				अगर (pf->lun != -1)
					वापस pf_identअगरy(pf);
				अन्यथा
					क्रम (pf->lun = 0; pf->lun < 8; pf->lun++)
						अगर (!pf_identअगरy(pf))
							वापस 0;
			पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pf_reset(pf))
			वापस -1;
		अगर (pf->lun != -1)
			वापस pf_identअगरy(pf);
		क्रम (pf->lun = 0; pf->lun < 8; pf->lun++)
			अगर (!pf_identअगरy(pf))
				वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक pf_detect(व्योम)
अणु
	काष्ठा pf_unit *pf = units;
	पूर्णांक k, unit;

	prपूर्णांकk("%s: %s version %s, major %d, cluster %d, nice %d\n",
	       name, name, PF_VERSION, major, cluster, nice);

	par_drv = pi_रेजिस्टर_driver(name);
	अगर (!par_drv) अणु
		pr_err("failed to register %s driver\n", name);
		वापस -1;
	पूर्ण
	k = 0;
	अगर (pf_drive_count == 0) अणु
		अगर (pi_init(pf->pi, 1, -1, -1, -1, -1, -1, pf_scratch, PI_PF,
			    verbose, pf->name)) अणु
			अगर (!pf_probe(pf) && pf->disk) अणु
				pf->present = 1;
				k++;
			पूर्ण अन्यथा
				pi_release(pf->pi);
		पूर्ण

	पूर्ण अन्यथा
		क्रम (unit = 0; unit < PF_UNITS; unit++, pf++) अणु
			पूर्णांक *conf = *drives[unit];
			अगर (!conf[D_PRT])
				जारी;
			अगर (pi_init(pf->pi, 0, conf[D_PRT], conf[D_MOD],
				    conf[D_UNI], conf[D_PRO], conf[D_DLY],
				    pf_scratch, PI_PF, verbose, pf->name)) अणु
				अगर (pf->disk && !pf_probe(pf)) अणु
					pf->present = 1;
					k++;
				पूर्ण अन्यथा
					pi_release(pf->pi);
			पूर्ण
		पूर्ण
	अगर (k)
		वापस 0;

	prपूर्णांकk("%s: No ATAPI disk detected\n", name);
	क्रम (pf = units, unit = 0; unit < PF_UNITS; pf++, unit++) अणु
		अगर (!pf->disk)
			जारी;
		blk_cleanup_queue(pf->disk->queue);
		pf->disk->queue = शून्य;
		blk_mq_मुक्त_tag_set(&pf->tag_set);
		put_disk(pf->disk);
	पूर्ण
	pi_unरेजिस्टर_driver(par_drv);
	वापस -1;
पूर्ण

/* The i/o request engine */

अटल पूर्णांक pf_start(काष्ठा pf_unit *pf, पूर्णांक cmd, पूर्णांक b, पूर्णांक c)
अणु
	पूर्णांक i;
	अक्षर io_cmd[12] = अणु cmd, pf->lun << 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		io_cmd[5 - i] = b & 0xff;
		b = b >> 8;
	पूर्ण

	io_cmd[8] = c & 0xff;
	io_cmd[7] = (c >> 8) & 0xff;

	i = pf_command(pf, io_cmd, c * 512, "start i/o");

	mdelay(1);

	वापस i;
पूर्ण

अटल पूर्णांक pf_पढ़ोy(व्योम)
अणु
	वापस (((status_reg(pf_current) & (STAT_BUSY | pf_mask)) == pf_mask));
पूर्ण

अटल पूर्णांक pf_queue;

अटल पूर्णांक set_next_request(व्योम)
अणु
	काष्ठा pf_unit *pf;
	पूर्णांक old_pos = pf_queue;

	करो अणु
		pf = &units[pf_queue];
		अगर (++pf_queue == PF_UNITS)
			pf_queue = 0;
		अगर (pf->present && !list_empty(&pf->rq_list)) अणु
			pf_req = list_first_entry(&pf->rq_list, काष्ठा request,
							queuelist);
			list_del_init(&pf_req->queuelist);
			blk_mq_start_request(pf_req);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pf_queue != old_pos);

	वापस pf_req != शून्य;
पूर्ण

अटल व्योम pf_end_request(blk_status_t err)
अणु
	अगर (!pf_req)
		वापस;
	अगर (!blk_update_request(pf_req, err, blk_rq_cur_bytes(pf_req))) अणु
		__blk_mq_end_request(pf_req, err);
		pf_req = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pf_request(व्योम)
अणु
	अगर (pf_busy)
		वापस;
repeat:
	अगर (!pf_req && !set_next_request())
		वापस;

	pf_current = pf_req->rq_disk->निजी_data;
	pf_block = blk_rq_pos(pf_req);
	pf_run = blk_rq_sectors(pf_req);
	pf_count = blk_rq_cur_sectors(pf_req);

	अगर (pf_block + pf_count > get_capacity(pf_req->rq_disk)) अणु
		pf_end_request(BLK_STS_IOERR);
		जाओ repeat;
	पूर्ण

	pf_cmd = rq_data_dir(pf_req);
	pf_buf = bio_data(pf_req->bio);
	pf_retries = 0;

	pf_busy = 1;
	अगर (pf_cmd == READ)
		pi_करो_claimed(pf_current->pi, करो_pf_पढ़ो);
	अन्यथा अगर (pf_cmd == WRITE)
		pi_करो_claimed(pf_current->pi, करो_pf_ग_लिखो);
	अन्यथा अणु
		pf_busy = 0;
		pf_end_request(BLK_STS_IOERR);
		जाओ repeat;
	पूर्ण
पूर्ण

अटल blk_status_t pf_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा pf_unit *pf = hctx->queue->queuedata;

	spin_lock_irq(&pf_spin_lock);
	list_add_tail(&bd->rq->queuelist, &pf->rq_list);
	pf_request();
	spin_unlock_irq(&pf_spin_lock);

	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक pf_next_buf(व्योम)
अणु
	अचिन्हित दीर्घ saved_flags;

	pf_count--;
	pf_run--;
	pf_buf += 512;
	pf_block++;
	अगर (!pf_run)
		वापस 1;
	अगर (!pf_count) अणु
		spin_lock_irqsave(&pf_spin_lock, saved_flags);
		pf_end_request(0);
		spin_unlock_irqrestore(&pf_spin_lock, saved_flags);
		अगर (!pf_req)
			वापस 1;
		pf_count = blk_rq_cur_sectors(pf_req);
		pf_buf = bio_data(pf_req->bio);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम next_request(blk_status_t err)
अणु
	अचिन्हित दीर्घ saved_flags;

	spin_lock_irqsave(&pf_spin_lock, saved_flags);
	pf_end_request(err);
	pf_busy = 0;
	pf_request();
	spin_unlock_irqrestore(&pf_spin_lock, saved_flags);
पूर्ण

/* detach from the calling context - in हाल the spinlock is held */
अटल व्योम करो_pf_पढ़ो(व्योम)
अणु
	ps_set_पूर्णांकr(करो_pf_पढ़ो_start, शून्य, 0, nice);
पूर्ण

अटल व्योम करो_pf_पढ़ो_start(व्योम)
अणु
	pf_busy = 1;

	अगर (pf_start(pf_current, ATAPI_READ_10, pf_block, pf_run)) अणु
		pi_disconnect(pf_current->pi);
		अगर (pf_retries < PF_MAX_RETRIES) अणु
			pf_retries++;
			pi_करो_claimed(pf_current->pi, करो_pf_पढ़ो_start);
			वापस;
		पूर्ण
		next_request(BLK_STS_IOERR);
		वापस;
	पूर्ण
	pf_mask = STAT_DRQ;
	ps_set_पूर्णांकr(करो_pf_पढ़ो_drq, pf_पढ़ोy, PF_TMO, nice);
पूर्ण

अटल व्योम करो_pf_पढ़ो_drq(व्योम)
अणु
	जबतक (1) अणु
		अगर (pf_रुको(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "read block", "completion") & STAT_ERR) अणु
			pi_disconnect(pf_current->pi);
			अगर (pf_retries < PF_MAX_RETRIES) अणु
				pf_req_sense(pf_current, 0);
				pf_retries++;
				pi_करो_claimed(pf_current->pi, करो_pf_पढ़ो_start);
				वापस;
			पूर्ण
			next_request(BLK_STS_IOERR);
			वापस;
		पूर्ण
		pi_पढ़ो_block(pf_current->pi, pf_buf, 512);
		अगर (pf_next_buf())
			अवरोध;
	पूर्ण
	pi_disconnect(pf_current->pi);
	next_request(0);
पूर्ण

अटल व्योम करो_pf_ग_लिखो(व्योम)
अणु
	ps_set_पूर्णांकr(करो_pf_ग_लिखो_start, शून्य, 0, nice);
पूर्ण

अटल व्योम करो_pf_ग_लिखो_start(व्योम)
अणु
	pf_busy = 1;

	अगर (pf_start(pf_current, ATAPI_WRITE_10, pf_block, pf_run)) अणु
		pi_disconnect(pf_current->pi);
		अगर (pf_retries < PF_MAX_RETRIES) अणु
			pf_retries++;
			pi_करो_claimed(pf_current->pi, करो_pf_ग_लिखो_start);
			वापस;
		पूर्ण
		next_request(BLK_STS_IOERR);
		वापस;
	पूर्ण

	जबतक (1) अणु
		अगर (pf_रुको(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "write block", "data wait") & STAT_ERR) अणु
			pi_disconnect(pf_current->pi);
			अगर (pf_retries < PF_MAX_RETRIES) अणु
				pf_retries++;
				pi_करो_claimed(pf_current->pi, करो_pf_ग_लिखो_start);
				वापस;
			पूर्ण
			next_request(BLK_STS_IOERR);
			वापस;
		पूर्ण
		pi_ग_लिखो_block(pf_current->pi, pf_buf, 512);
		अगर (pf_next_buf())
			अवरोध;
	पूर्ण
	pf_mask = 0;
	ps_set_पूर्णांकr(करो_pf_ग_लिखो_करोne, pf_पढ़ोy, PF_TMO, nice);
पूर्ण

अटल व्योम करो_pf_ग_लिखो_करोne(व्योम)
अणु
	अगर (pf_रुको(pf_current, STAT_BUSY, 0, "write block", "done") & STAT_ERR) अणु
		pi_disconnect(pf_current->pi);
		अगर (pf_retries < PF_MAX_RETRIES) अणु
			pf_retries++;
			pi_करो_claimed(pf_current->pi, करो_pf_ग_लिखो_start);
			वापस;
		पूर्ण
		next_request(BLK_STS_IOERR);
		वापस;
	पूर्ण
	pi_disconnect(pf_current->pi);
	next_request(0);
पूर्ण

अटल पूर्णांक __init pf_init(व्योम)
अणु				/* preliminary initialisation */
	काष्ठा pf_unit *pf;
	पूर्णांक unit;

	अगर (disable)
		वापस -EINVAL;

	pf_init_units();

	अगर (pf_detect())
		वापस -ENODEV;
	pf_busy = 0;

	अगर (रेजिस्टर_blkdev(major, name)) अणु
		क्रम (pf = units, unit = 0; unit < PF_UNITS; pf++, unit++) अणु
			अगर (!pf->disk)
				जारी;
			blk_cleanup_queue(pf->disk->queue);
			blk_mq_मुक्त_tag_set(&pf->tag_set);
			put_disk(pf->disk);
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	क्रम (pf = units, unit = 0; unit < PF_UNITS; pf++, unit++) अणु
		काष्ठा gendisk *disk = pf->disk;

		अगर (!pf->present)
			जारी;
		disk->निजी_data = pf;
		add_disk(disk);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास pf_निकास(व्योम)
अणु
	काष्ठा pf_unit *pf;
	पूर्णांक unit;
	unरेजिस्टर_blkdev(major, name);
	क्रम (pf = units, unit = 0; unit < PF_UNITS; pf++, unit++) अणु
		अगर (!pf->disk)
			जारी;

		अगर (pf->present)
			del_gendisk(pf->disk);

		blk_cleanup_queue(pf->disk->queue);
		blk_mq_मुक्त_tag_set(&pf->tag_set);
		put_disk(pf->disk);

		अगर (pf->present)
			pi_release(pf->pi);
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
module_init(pf_init)
module_निकास(pf_निकास)
