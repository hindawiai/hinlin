<शैली गुरु>
/* 
        pd.c    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                            Under the terms of the GNU General Public License.

        This is the high-level driver क्रम parallel port IDE hard
        drives based on chips supported by the paride module.

	By शेष, the driver will स्वतःprobe क्रम a single parallel
	port IDE drive, but अगर their inभागidual parameters are
        specअगरied, the driver can handle up to 4 drives.

        The behaviour of the pd driver can be altered by setting
        some parameters from the insmod command line.  The following
        parameters are adjustable:
 
	    drive0  	These four arguments can be arrays of	    
	    drive1	1-8 पूर्णांकegers as follows:
	    drive2
	    drive3	<prt>,<pro>,<uni>,<mod>,<geo>,<sby>,<dly>,<slv>

			Where,

		<prt>	is the base of the parallel port address क्रम
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

		<geo>   this शेषs to 0 to indicate that the driver
			should use the CHS geometry provided by the drive
			itself.  If set to 1, the driver will provide
			a logical geometry with 64 heads and 32 sectors
			per track, to be consistent with most SCSI
		        drivers.  (0 अगर not given)

		<sby>   set this to zero to disable the घातer saving
			standby mode, अगर needed.  (1 अगर not given)

		<dly>   some parallel ports require the driver to 
			go more slowly.  -1 sets a शेष value that
			should work with the chosen protocol.  Otherwise,
			set this to a small पूर्णांकeger, the larger it is
			the slower the port i/o.  In some हालs, setting
			this to zero will speed up the device. (शेष -1)

		<slv>   IDE disks can be jumpered to master or slave.
                        Set this to 0 to choose the master drive, 1 to
                        choose the slave, -1 (the शेष) to choose the
                        first drive found.
			

            major       You may use this parameter to override the
                        शेष major number (45) that this driver
                        will use.  Be sure to change the device
                        name as well.

            name        This parameter is a अक्षरacter string that
                        contains the name the kernel will use क्रम this
                        device (in /proc output, क्रम instance).
			(शेष "pd")

	    cluster	The driver will attempt to aggregate requests
			क्रम adjacent blocks पूर्णांकo larger multi-block
			clusters.  The maximum cluster size (in 512
			byte sectors) is set with this parameter.
			(शेष 64)

	    verbose	This parameter controls the amount of logging
			that the driver will करो.  Set it to 0 क्रम 
			normal operation, 1 to see स्वतःprobe progress
			messages, or 2 to see additional debugging
			output.  (शेष 0)

            nice        This parameter controls the driver's use of
                        idle CPU समय, at the expense of some speed.

        If this driver is built पूर्णांकo the kernel, you can use kernel
        the following command line parameters, with the same values
        as the corresponding module parameters listed above:

            pd.drive0
            pd.drive1
            pd.drive2
            pd.drive3
            pd.cluster
            pd.nice

        In addition, you can use the parameter pd.disable to disable
        the driver entirely.
 
*/

/* Changes:

	1.01	GRG 1997.01.24	Restored pd_reset()
				Added eject ioctl
	1.02    GRG 1998.05.06  SMP spinlock changes, 
				Added slave support
	1.03    GRG 1998.06.16  Eliminate an Ugh.
	1.04	GRG 1998.08.15  Extra debugging, use HZ in loop timing
	1.05    GRG 1998.09.24  Added jumbo support

*/

#घोषणा PD_VERSION      "1.05"
#घोषणा PD_MAJOR	45
#घोषणा PD_NAME		"pd"
#घोषणा PD_UNITS	4

/* Here are things one can override from the insmod command.
   Most are स्वतःprobed by paride unless set here.  Verbose is off
   by शेष.

*/
#समावेश <linux/types.h>

अटल पूर्णांक verbose = 0;
अटल पूर्णांक major = PD_MAJOR;
अटल अक्षर *name = PD_NAME;
अटल पूर्णांक cluster = 64;
अटल पूर्णांक nice = 0;
अटल पूर्णांक disable = 0;

अटल पूर्णांक drive0[8] = अणु 0, 0, 0, -1, 0, 1, -1, -1 पूर्ण;
अटल पूर्णांक drive1[8] = अणु 0, 0, 0, -1, 0, 1, -1, -1 पूर्ण;
अटल पूर्णांक drive2[8] = अणु 0, 0, 0, -1, 0, 1, -1, -1 पूर्ण;
अटल पूर्णांक drive3[8] = अणु 0, 0, 0, -1, 0, 1, -1, -1 पूर्ण;

अटल पूर्णांक (*drives[4])[8] = अणु&drive0, &drive1, &drive2, &drive3पूर्ण;

क्रमागत अणुD_PRT, D_PRO, D_UNI, D_MOD, D_GEO, D_SBY, D_DLY, D_SLVपूर्ण;

/* end of parameters */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/cdrom.h>	/* क्रम the eject ioctl */
#समावेश <linux/blk-mq.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>

अटल DEFINE_MUTEX(pd_mutex);
अटल DEFINE_SPINLOCK(pd_lock);

module_param(verbose, पूर्णांक, 0);
module_param(major, पूर्णांक, 0);
module_param(name, अक्षरp, 0);
module_param(cluster, पूर्णांक, 0);
module_param(nice, पूर्णांक, 0);
module_param_array(drive0, पूर्णांक, शून्य, 0);
module_param_array(drive1, पूर्णांक, शून्य, 0);
module_param_array(drive2, पूर्णांक, शून्य, 0);
module_param_array(drive3, पूर्णांक, शून्य, 0);

#समावेश "paride.h"

#घोषणा PD_BITS    4

/* numbers क्रम "SCSI" geometry */

#घोषणा PD_LOG_HEADS    64
#घोषणा PD_LOG_SECTS    32

#घोषणा PD_ID_OFF       54
#घोषणा PD_ID_LEN       14

#घोषणा PD_MAX_RETRIES  5
#घोषणा PD_TMO          800	/* पूर्णांकerrupt समयout in jअगरfies */
#घोषणा PD_SPIN_DEL     50	/* spin delay in micro-seconds  */

#घोषणा PD_SPIN         (1000000*PD_TMO)/(HZ*PD_SPIN_DEL)

#घोषणा STAT_ERR        0x00001
#घोषणा STAT_INDEX      0x00002
#घोषणा STAT_ECC        0x00004
#घोषणा STAT_DRQ        0x00008
#घोषणा STAT_SEEK       0x00010
#घोषणा STAT_WRERR      0x00020
#घोषणा STAT_READY      0x00040
#घोषणा STAT_BUSY       0x00080

#घोषणा ERR_AMNF        0x00100
#घोषणा ERR_TK0NF       0x00200
#घोषणा ERR_ABRT        0x00400
#घोषणा ERR_MCR         0x00800
#घोषणा ERR_IDNF        0x01000
#घोषणा ERR_MC          0x02000
#घोषणा ERR_UNC         0x04000
#घोषणा ERR_TMO         0x10000

#घोषणा IDE_READ        	0x20
#घोषणा IDE_WRITE       	0x30
#घोषणा IDE_READ_VRFY		0x40
#घोषणा IDE_INIT_DEV_PARMS	0x91
#घोषणा IDE_STANDBY     	0x96
#घोषणा IDE_ACKCHANGE   	0xdb
#घोषणा IDE_DOORLOCK    	0xde
#घोषणा IDE_DOORUNLOCK  	0xdf
#घोषणा IDE_IDENTIFY    	0xec
#घोषणा IDE_EJECT		0xed

#घोषणा PD_NAMELEN	8

काष्ठा pd_unit अणु
	काष्ठा pi_adapter pia;	/* पूर्णांकerface to paride layer */
	काष्ठा pi_adapter *pi;
	पूर्णांक access;		/* count of active खोलोs ... */
	पूर्णांक capacity;		/* Size of this volume in sectors */
	पूर्णांक heads;		/* physical geometry */
	पूर्णांक sectors;
	पूर्णांक cylinders;
	पूर्णांक can_lba;
	पूर्णांक drive;		/* master=0 slave=1 */
	पूर्णांक changed;		/* Have we seen a disk change ? */
	पूर्णांक removable;		/* removable media device  ?  */
	पूर्णांक standby;
	पूर्णांक alt_geom;
	अक्षर name[PD_NAMELEN];	/* pda, pdb, etc ... */
	काष्ठा gendisk *gd;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा list_head rq_list;
पूर्ण;

अटल काष्ठा pd_unit pd[PD_UNITS];

काष्ठा pd_req अणु
	/* क्रम REQ_OP_DRV_IN: */
	क्रमागत action (*func)(काष्ठा pd_unit *disk);
पूर्ण;

अटल अक्षर pd_scratch[512];	/* scratch block buffer */

अटल अक्षर *pd_errs[17] = अणु "ERR", "INDEX", "ECC", "DRQ", "SEEK", "WRERR",
	"READY", "BUSY", "AMNF", "TK0NF", "ABRT", "MCR",
	"IDNF", "MC", "UNC", "???", "TMO"
पूर्ण;

अटल व्योम *par_drv;		/* reference of parport driver */

अटल अंतरभूत पूर्णांक status_reg(काष्ठा pd_unit *disk)
अणु
	वापस pi_पढ़ो_regr(disk->pi, 1, 6);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_reg(काष्ठा pd_unit *disk, पूर्णांक reg)
अणु
	वापस pi_पढ़ो_regr(disk->pi, 0, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_status(काष्ठा pd_unit *disk, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(disk->pi, 1, 6, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा pd_unit *disk, पूर्णांक reg, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(disk->pi, 0, reg, val);
पूर्ण

अटल अंतरभूत u8 DRIVE(काष्ठा pd_unit *disk)
अणु
	वापस 0xa0+0x10*disk->drive;
पूर्ण

/*  ide command पूर्णांकerface */

अटल व्योम pd_prपूर्णांक_error(काष्ठा pd_unit *disk, अक्षर *msg, पूर्णांक status)
अणु
	पूर्णांक i;

	prपूर्णांकk("%s: %s: status = 0x%x =", disk->name, msg, status);
	क्रम (i = 0; i < ARRAY_SIZE(pd_errs); i++)
		अगर (status & (1 << i))
			prपूर्णांकk(" %s", pd_errs[i]);
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम pd_reset(काष्ठा pd_unit *disk)
अणु				/* called only क्रम MASTER drive */
	ग_लिखो_status(disk, 4);
	udelay(50);
	ग_लिखो_status(disk, 0);
	udelay(250);
पूर्ण

#घोषणा DBMSG(msg)	((verbose>1)?(msg):शून्य)

अटल पूर्णांक pd_रुको_क्रम(काष्ठा pd_unit *disk, पूर्णांक w, अक्षर *msg)
अणु				/* polled रुको */
	पूर्णांक k, r, e;

	k = 0;
	जबतक (k < PD_SPIN) अणु
		r = status_reg(disk);
		k++;
		अगर (((r & w) == w) && !(r & STAT_BUSY))
			अवरोध;
		udelay(PD_SPIN_DEL);
	पूर्ण
	e = (पढ़ो_reg(disk, 1) << 8) + पढ़ो_reg(disk, 7);
	अगर (k >= PD_SPIN)
		e |= ERR_TMO;
	अगर ((e & (STAT_ERR | ERR_TMO)) && (msg != शून्य))
		pd_prपूर्णांक_error(disk, msg, e);
	वापस e;
पूर्ण

अटल व्योम pd_send_command(काष्ठा pd_unit *disk, पूर्णांक n, पूर्णांक s, पूर्णांक h, पूर्णांक c0, पूर्णांक c1, पूर्णांक func)
अणु
	ग_लिखो_reg(disk, 6, DRIVE(disk) + h);
	ग_लिखो_reg(disk, 1, 0);		/* the IDE task file */
	ग_लिखो_reg(disk, 2, n);
	ग_लिखो_reg(disk, 3, s);
	ग_लिखो_reg(disk, 4, c0);
	ग_लिखो_reg(disk, 5, c1);
	ग_लिखो_reg(disk, 7, func);

	udelay(1);
पूर्ण

अटल व्योम pd_ide_command(काष्ठा pd_unit *disk, पूर्णांक func, पूर्णांक block, पूर्णांक count)
अणु
	पूर्णांक c1, c0, h, s;

	अगर (disk->can_lba) अणु
		s = block & 255;
		c0 = (block >>= 8) & 255;
		c1 = (block >>= 8) & 255;
		h = ((block >>= 8) & 15) + 0x40;
	पूर्ण अन्यथा अणु
		s = (block % disk->sectors) + 1;
		h = (block /= disk->sectors) % disk->heads;
		c0 = (block /= disk->heads) % 256;
		c1 = (block >>= 8);
	पूर्ण
	pd_send_command(disk, count, s, h, c0, c1, func);
पूर्ण

/* The i/o request engine */

क्रमागत action अणुFail = 0, Ok = 1, Hold, Waitपूर्ण;

अटल काष्ठा request *pd_req;	/* current request */
अटल क्रमागत action (*phase)(व्योम);

अटल व्योम run_fsm(व्योम);

अटल व्योम ps_tq_पूर्णांक(काष्ठा work_काष्ठा *work);

अटल DECLARE_DELAYED_WORK(fsm_tq, ps_tq_पूर्णांक);

अटल व्योम schedule_fsm(व्योम)
अणु
	अगर (!nice)
		schedule_delayed_work(&fsm_tq, 0);
	अन्यथा
		schedule_delayed_work(&fsm_tq, nice-1);
पूर्ण

अटल व्योम ps_tq_पूर्णांक(काष्ठा work_काष्ठा *work)
अणु
	run_fsm();
पूर्ण

अटल क्रमागत action करो_pd_io_start(व्योम);
अटल क्रमागत action pd_special(व्योम);
अटल क्रमागत action करो_pd_पढ़ो_start(व्योम);
अटल क्रमागत action करो_pd_ग_लिखो_start(व्योम);
अटल क्रमागत action करो_pd_पढ़ो_drq(व्योम);
अटल क्रमागत action करो_pd_ग_लिखो_करोne(व्योम);

अटल पूर्णांक pd_queue;
अटल पूर्णांक pd_claimed;

अटल काष्ठा pd_unit *pd_current; /* current request's drive */
अटल PIA *pi_current; /* current request's PIA */

अटल पूर्णांक set_next_request(व्योम)
अणु
	काष्ठा gendisk *disk;
	काष्ठा request_queue *q;
	पूर्णांक old_pos = pd_queue;

	करो अणु
		disk = pd[pd_queue].gd;
		q = disk ? disk->queue : शून्य;
		अगर (++pd_queue == PD_UNITS)
			pd_queue = 0;
		अगर (q) अणु
			काष्ठा pd_unit *disk = q->queuedata;

			अगर (list_empty(&disk->rq_list))
				जारी;

			pd_req = list_first_entry(&disk->rq_list,
							काष्ठा request,
							queuelist);
			list_del_init(&pd_req->queuelist);
			blk_mq_start_request(pd_req);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pd_queue != old_pos);

	वापस pd_req != शून्य;
पूर्ण

अटल व्योम run_fsm(व्योम)
अणु
	जबतक (1) अणु
		क्रमागत action res;
		पूर्णांक stop = 0;

		अगर (!phase) अणु
			pd_current = pd_req->rq_disk->निजी_data;
			pi_current = pd_current->pi;
			phase = करो_pd_io_start;
		पूर्ण

		चयन (pd_claimed) अणु
			हाल 0:
				pd_claimed = 1;
				अगर (!pi_schedule_claimed(pi_current, run_fsm))
					वापस;
				fallthrough;
			हाल 1:
				pd_claimed = 2;
				pi_current->proto->connect(pi_current);
		पूर्ण

		चयन(res = phase()) अणु
			हाल Ok: हाल Fail: अणु
				blk_status_t err;

				err = res == Ok ? 0 : BLK_STS_IOERR;
				pi_disconnect(pi_current);
				pd_claimed = 0;
				phase = शून्य;
				spin_lock_irq(&pd_lock);
				अगर (!blk_update_request(pd_req, err,
						blk_rq_cur_bytes(pd_req))) अणु
					__blk_mq_end_request(pd_req, err);
					pd_req = शून्य;
					stop = !set_next_request();
				पूर्ण
				spin_unlock_irq(&pd_lock);
				अगर (stop)
					वापस;
				पूर्ण
				fallthrough;
			हाल Hold:
				schedule_fsm();
				वापस;
			हाल Wait:
				pi_disconnect(pi_current);
				pd_claimed = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pd_retries = 0;	/* i/o error retry count */
अटल पूर्णांक pd_block;		/* address of next requested block */
अटल पूर्णांक pd_count;		/* number of blocks still to करो */
अटल पूर्णांक pd_run;		/* sectors in current cluster */
अटल अक्षर *pd_buf;		/* buffer क्रम request in progress */

अटल क्रमागत action करो_pd_io_start(व्योम)
अणु
	चयन (req_op(pd_req)) अणु
	हाल REQ_OP_DRV_IN:
		phase = pd_special;
		वापस pd_special();
	हाल REQ_OP_READ:
	हाल REQ_OP_WRITE:
		pd_block = blk_rq_pos(pd_req);
		pd_count = blk_rq_cur_sectors(pd_req);
		अगर (pd_block + pd_count > get_capacity(pd_req->rq_disk))
			वापस Fail;
		pd_run = blk_rq_sectors(pd_req);
		pd_buf = bio_data(pd_req->bio);
		pd_retries = 0;
		अगर (req_op(pd_req) == REQ_OP_READ)
			वापस करो_pd_पढ़ो_start();
		अन्यथा
			वापस करो_pd_ग_लिखो_start();
	पूर्ण
	वापस Fail;
पूर्ण

अटल क्रमागत action pd_special(व्योम)
अणु
	काष्ठा pd_req *req = blk_mq_rq_to_pdu(pd_req);

	वापस req->func(pd_current);
पूर्ण

अटल पूर्णांक pd_next_buf(व्योम)
अणु
	अचिन्हित दीर्घ saved_flags;

	pd_count--;
	pd_run--;
	pd_buf += 512;
	pd_block++;
	अगर (!pd_run)
		वापस 1;
	अगर (pd_count)
		वापस 0;
	spin_lock_irqsave(&pd_lock, saved_flags);
	अगर (!blk_update_request(pd_req, 0, blk_rq_cur_bytes(pd_req))) अणु
		__blk_mq_end_request(pd_req, 0);
		pd_req = शून्य;
		pd_count = 0;
		pd_buf = शून्य;
	पूर्ण अन्यथा अणु
		pd_count = blk_rq_cur_sectors(pd_req);
		pd_buf = bio_data(pd_req->bio);
	पूर्ण
	spin_unlock_irqrestore(&pd_lock, saved_flags);
	वापस !pd_count;
पूर्ण

अटल अचिन्हित दीर्घ pd_समयout;

अटल क्रमागत action करो_pd_पढ़ो_start(व्योम)
अणु
	अगर (pd_रुको_क्रम(pd_current, STAT_READY, "do_pd_read") & STAT_ERR) अणु
		अगर (pd_retries < PD_MAX_RETRIES) अणु
			pd_retries++;
			वापस Wait;
		पूर्ण
		वापस Fail;
	पूर्ण
	pd_ide_command(pd_current, IDE_READ, pd_block, pd_run);
	phase = करो_pd_पढ़ो_drq;
	pd_समयout = jअगरfies + PD_TMO;
	वापस Hold;
पूर्ण

अटल क्रमागत action करो_pd_ग_लिखो_start(व्योम)
अणु
	अगर (pd_रुको_क्रम(pd_current, STAT_READY, "do_pd_write") & STAT_ERR) अणु
		अगर (pd_retries < PD_MAX_RETRIES) अणु
			pd_retries++;
			वापस Wait;
		पूर्ण
		वापस Fail;
	पूर्ण
	pd_ide_command(pd_current, IDE_WRITE, pd_block, pd_run);
	जबतक (1) अणु
		अगर (pd_रुको_क्रम(pd_current, STAT_DRQ, "do_pd_write_drq") & STAT_ERR) अणु
			अगर (pd_retries < PD_MAX_RETRIES) अणु
				pd_retries++;
				वापस Wait;
			पूर्ण
			वापस Fail;
		पूर्ण
		pi_ग_लिखो_block(pd_current->pi, pd_buf, 512);
		अगर (pd_next_buf())
			अवरोध;
	पूर्ण
	phase = करो_pd_ग_लिखो_करोne;
	pd_समयout = jअगरfies + PD_TMO;
	वापस Hold;
पूर्ण

अटल अंतरभूत पूर्णांक pd_पढ़ोy(व्योम)
अणु
	वापस !(status_reg(pd_current) & STAT_BUSY);
पूर्ण

अटल क्रमागत action करो_pd_पढ़ो_drq(व्योम)
अणु
	अगर (!pd_पढ़ोy() && !समय_after_eq(jअगरfies, pd_समयout))
		वापस Hold;

	जबतक (1) अणु
		अगर (pd_रुको_क्रम(pd_current, STAT_DRQ, "do_pd_read_drq") & STAT_ERR) अणु
			अगर (pd_retries < PD_MAX_RETRIES) अणु
				pd_retries++;
				phase = करो_pd_पढ़ो_start;
				वापस Wait;
			पूर्ण
			वापस Fail;
		पूर्ण
		pi_पढ़ो_block(pd_current->pi, pd_buf, 512);
		अगर (pd_next_buf())
			अवरोध;
	पूर्ण
	वापस Ok;
पूर्ण

अटल क्रमागत action करो_pd_ग_लिखो_करोne(व्योम)
अणु
	अगर (!pd_पढ़ोy() && !समय_after_eq(jअगरfies, pd_समयout))
		वापस Hold;

	अगर (pd_रुको_क्रम(pd_current, STAT_READY, "do_pd_write_done") & STAT_ERR) अणु
		अगर (pd_retries < PD_MAX_RETRIES) अणु
			pd_retries++;
			phase = करो_pd_ग_लिखो_start;
			वापस Wait;
		पूर्ण
		वापस Fail;
	पूर्ण
	वापस Ok;
पूर्ण

/* special io requests */

/* According to the ATA standard, the शेष CHS geometry should be
   available following a reset.  Some Western Digital drives come up
   in a mode where only LBA addresses are accepted until the device
   parameters are initialised.
*/

अटल व्योम pd_init_dev_parms(काष्ठा pd_unit *disk)
अणु
	pd_रुको_क्रम(disk, 0, DBMSG("before init_dev_parms"));
	pd_send_command(disk, disk->sectors, 0, disk->heads - 1, 0, 0,
			IDE_INIT_DEV_PARMS);
	udelay(300);
	pd_रुको_क्रम(disk, 0, "Initialise device parameters");
पूर्ण

अटल क्रमागत action pd_करोor_lock(काष्ठा pd_unit *disk)
अणु
	अगर (!(pd_रुको_क्रम(disk, STAT_READY, "Lock") & STAT_ERR)) अणु
		pd_send_command(disk, 1, 0, 0, 0, 0, IDE_DOORLOCK);
		pd_रुको_क्रम(disk, STAT_READY, "Lock done");
	पूर्ण
	वापस Ok;
पूर्ण

अटल क्रमागत action pd_करोor_unlock(काष्ठा pd_unit *disk)
अणु
	अगर (!(pd_रुको_क्रम(disk, STAT_READY, "Lock") & STAT_ERR)) अणु
		pd_send_command(disk, 1, 0, 0, 0, 0, IDE_DOORUNLOCK);
		pd_रुको_क्रम(disk, STAT_READY, "Lock done");
	पूर्ण
	वापस Ok;
पूर्ण

अटल क्रमागत action pd_eject(काष्ठा pd_unit *disk)
अणु
	pd_रुको_क्रम(disk, 0, DBMSG("before unlock on eject"));
	pd_send_command(disk, 1, 0, 0, 0, 0, IDE_DOORUNLOCK);
	pd_रुको_क्रम(disk, 0, DBMSG("after unlock on eject"));
	pd_रुको_क्रम(disk, 0, DBMSG("before eject"));
	pd_send_command(disk, 0, 0, 0, 0, 0, IDE_EJECT);
	pd_रुको_क्रम(disk, 0, DBMSG("after eject"));
	वापस Ok;
पूर्ण

अटल क्रमागत action pd_media_check(काष्ठा pd_unit *disk)
अणु
	पूर्णांक r = pd_रुको_क्रम(disk, STAT_READY, DBMSG("before media_check"));
	अगर (!(r & STAT_ERR)) अणु
		pd_send_command(disk, 1, 1, 0, 0, 0, IDE_READ_VRFY);
		r = pd_रुको_क्रम(disk, STAT_READY, DBMSG("RDY after READ_VRFY"));
	पूर्ण अन्यथा
		disk->changed = 1;	/* say changed अगर other error */
	अगर (r & ERR_MC) अणु
		disk->changed = 1;
		pd_send_command(disk, 1, 0, 0, 0, 0, IDE_ACKCHANGE);
		pd_रुको_क्रम(disk, STAT_READY, DBMSG("RDY after ACKCHANGE"));
		pd_send_command(disk, 1, 1, 0, 0, 0, IDE_READ_VRFY);
		r = pd_रुको_क्रम(disk, STAT_READY, DBMSG("RDY after VRFY"));
	पूर्ण
	वापस Ok;
पूर्ण

अटल व्योम pd_standby_off(काष्ठा pd_unit *disk)
अणु
	pd_रुको_क्रम(disk, 0, DBMSG("before STANDBY"));
	pd_send_command(disk, 0, 0, 0, 0, 0, IDE_STANDBY);
	pd_रुको_क्रम(disk, 0, DBMSG("after STANDBY"));
पूर्ण

अटल क्रमागत action pd_identअगरy(काष्ठा pd_unit *disk)
अणु
	पूर्णांक j;
	अक्षर id[PD_ID_LEN + 1];

/* WARNING:  here there may be dragons.  reset() applies to both drives,
   but we call it only on probing the MASTER. This should allow most
   common configurations to work, but be warned that a reset can clear
   settings on the SLAVE drive.
*/

	अगर (disk->drive == 0)
		pd_reset(disk);

	ग_लिखो_reg(disk, 6, DRIVE(disk));
	pd_रुको_क्रम(disk, 0, DBMSG("before IDENT"));
	pd_send_command(disk, 1, 0, 0, 0, 0, IDE_IDENTIFY);

	अगर (pd_रुको_क्रम(disk, STAT_DRQ, DBMSG("IDENT DRQ")) & STAT_ERR)
		वापस Fail;
	pi_पढ़ो_block(disk->pi, pd_scratch, 512);
	disk->can_lba = pd_scratch[99] & 2;
	disk->sectors = le16_to_cpu(*(__le16 *) (pd_scratch + 12));
	disk->heads = le16_to_cpu(*(__le16 *) (pd_scratch + 6));
	disk->cylinders = le16_to_cpu(*(__le16 *) (pd_scratch + 2));
	अगर (disk->can_lba)
		disk->capacity = le32_to_cpu(*(__le32 *) (pd_scratch + 120));
	अन्यथा
		disk->capacity = disk->sectors * disk->heads * disk->cylinders;

	क्रम (j = 0; j < PD_ID_LEN; j++)
		id[j ^ 1] = pd_scratch[j + PD_ID_OFF];
	j = PD_ID_LEN - 1;
	जबतक ((j >= 0) && (id[j] <= 0x20))
		j--;
	j++;
	id[j] = 0;

	disk->removable = pd_scratch[0] & 0x80;

	prपूर्णांकk("%s: %s, %s, %d blocks [%dM], (%d/%d/%d), %s media\n",
	       disk->name, id,
	       disk->drive ? "slave" : "master",
	       disk->capacity, disk->capacity / 2048,
	       disk->cylinders, disk->heads, disk->sectors,
	       disk->removable ? "removable" : "fixed");

	अगर (disk->capacity)
		pd_init_dev_parms(disk);
	अगर (!disk->standby)
		pd_standby_off(disk);

	वापस Ok;
पूर्ण

/* end of io request engine */

अटल blk_status_t pd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा pd_unit *disk = hctx->queue->queuedata;

	spin_lock_irq(&pd_lock);
	अगर (!pd_req) अणु
		pd_req = bd->rq;
		blk_mq_start_request(pd_req);
	पूर्ण अन्यथा
		list_add_tail(&bd->rq->queuelist, &disk->rq_list);
	spin_unlock_irq(&pd_lock);

	run_fsm();
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक pd_special_command(काष्ठा pd_unit *disk,
		      क्रमागत action (*func)(काष्ठा pd_unit *disk))
अणु
	काष्ठा request *rq;
	काष्ठा pd_req *req;

	rq = blk_get_request(disk->gd->queue, REQ_OP_DRV_IN, 0);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);
	req = blk_mq_rq_to_pdu(rq);

	req->func = func;
	blk_execute_rq(disk->gd, rq, 0);
	blk_put_request(rq);
	वापस 0;
पूर्ण

/* kernel glue काष्ठाures */

अटल पूर्णांक pd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा pd_unit *disk = bdev->bd_disk->निजी_data;

	mutex_lock(&pd_mutex);
	disk->access++;

	अगर (disk->removable) अणु
		pd_special_command(disk, pd_media_check);
		pd_special_command(disk, pd_करोor_lock);
	पूर्ण
	mutex_unlock(&pd_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा pd_unit *disk = bdev->bd_disk->निजी_data;

	अगर (disk->alt_geom) अणु
		geo->heads = PD_LOG_HEADS;
		geo->sectors = PD_LOG_SECTS;
		geo->cylinders = disk->capacity / (geo->heads * geo->sectors);
	पूर्ण अन्यथा अणु
		geo->heads = disk->heads;
		geo->sectors = disk->sectors;
		geo->cylinders = disk->cylinders;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pd_unit *disk = bdev->bd_disk->निजी_data;

	चयन (cmd) अणु
	हाल CDROMEJECT:
		mutex_lock(&pd_mutex);
		अगर (disk->access == 1)
			pd_special_command(disk, pd_eject);
		mutex_unlock(&pd_mutex);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम pd_release(काष्ठा gendisk *p, भ_शेषe_t mode)
अणु
	काष्ठा pd_unit *disk = p->निजी_data;

	mutex_lock(&pd_mutex);
	अगर (!--disk->access && disk->removable)
		pd_special_command(disk, pd_करोor_unlock);
	mutex_unlock(&pd_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक pd_check_events(काष्ठा gendisk *p, अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा pd_unit *disk = p->निजी_data;
	पूर्णांक r;
	अगर (!disk->removable)
		वापस 0;
	pd_special_command(disk, pd_media_check);
	r = disk->changed;
	disk->changed = 0;
	वापस r ? DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations pd_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= pd_खोलो,
	.release	= pd_release,
	.ioctl		= pd_ioctl,
	.compat_ioctl	= pd_ioctl,
	.getgeo		= pd_getgeo,
	.check_events	= pd_check_events,
पूर्ण;

/* probing */

अटल स्थिर काष्ठा blk_mq_ops pd_mq_ops = अणु
	.queue_rq	= pd_queue_rq,
पूर्ण;

अटल व्योम pd_probe_drive(काष्ठा pd_unit *disk)
अणु
	काष्ठा gendisk *p;

	p = alloc_disk(1 << PD_BITS);
	अगर (!p)
		वापस;

	म_नकल(p->disk_name, disk->name);
	p->fops = &pd_fops;
	p->major = major;
	p->first_minor = (disk - pd) << PD_BITS;
	p->events = DISK_EVENT_MEDIA_CHANGE;
	disk->gd = p;
	p->निजी_data = disk;

	स_रखो(&disk->tag_set, 0, माप(disk->tag_set));
	disk->tag_set.ops = &pd_mq_ops;
	disk->tag_set.cmd_size = माप(काष्ठा pd_req);
	disk->tag_set.nr_hw_queues = 1;
	disk->tag_set.nr_maps = 1;
	disk->tag_set.queue_depth = 2;
	disk->tag_set.numa_node = NUMA_NO_NODE;
	disk->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;

	अगर (blk_mq_alloc_tag_set(&disk->tag_set))
		वापस;

	p->queue = blk_mq_init_queue(&disk->tag_set);
	अगर (IS_ERR(p->queue)) अणु
		blk_mq_मुक्त_tag_set(&disk->tag_set);
		p->queue = शून्य;
		वापस;
	पूर्ण

	p->queue->queuedata = disk;
	blk_queue_max_hw_sectors(p->queue, cluster);
	blk_queue_bounce_limit(p->queue, BLK_BOUNCE_HIGH);

	अगर (disk->drive == -1) अणु
		क्रम (disk->drive = 0; disk->drive <= 1; disk->drive++)
			अगर (pd_special_command(disk, pd_identअगरy) == 0)
				वापस;
	पूर्ण अन्यथा अगर (pd_special_command(disk, pd_identअगरy) == 0)
		वापस;
	disk->gd = शून्य;
	put_disk(p);
पूर्ण

अटल पूर्णांक pd_detect(व्योम)
अणु
	पूर्णांक found = 0, unit, pd_drive_count = 0;
	काष्ठा pd_unit *disk;

	क्रम (unit = 0; unit < PD_UNITS; unit++) अणु
		पूर्णांक *parm = *drives[unit];
		काष्ठा pd_unit *disk = pd + unit;
		disk->pi = &disk->pia;
		disk->access = 0;
		disk->changed = 1;
		disk->capacity = 0;
		disk->drive = parm[D_SLV];
		snम_लिखो(disk->name, PD_NAMELEN, "%s%c", name, 'a'+unit);
		disk->alt_geom = parm[D_GEO];
		disk->standby = parm[D_SBY];
		अगर (parm[D_PRT])
			pd_drive_count++;
		INIT_LIST_HEAD(&disk->rq_list);
	पूर्ण

	par_drv = pi_रेजिस्टर_driver(name);
	अगर (!par_drv) अणु
		pr_err("failed to register %s driver\n", name);
		वापस -1;
	पूर्ण

	अगर (pd_drive_count == 0) अणु /* nothing spec'd - so स्वतःprobe क्रम 1 */
		disk = pd;
		अगर (pi_init(disk->pi, 1, -1, -1, -1, -1, -1, pd_scratch,
			    PI_PD, verbose, disk->name)) अणु
			pd_probe_drive(disk);
			अगर (!disk->gd)
				pi_release(disk->pi);
		पूर्ण

	पूर्ण अन्यथा अणु
		क्रम (unit = 0, disk = pd; unit < PD_UNITS; unit++, disk++) अणु
			पूर्णांक *parm = *drives[unit];
			अगर (!parm[D_PRT])
				जारी;
			अगर (pi_init(disk->pi, 0, parm[D_PRT], parm[D_MOD],
				     parm[D_UNI], parm[D_PRO], parm[D_DLY],
				     pd_scratch, PI_PD, verbose, disk->name)) अणु
				pd_probe_drive(disk);
				अगर (!disk->gd)
					pi_release(disk->pi);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (unit = 0, disk = pd; unit < PD_UNITS; unit++, disk++) अणु
		अगर (disk->gd) अणु
			set_capacity(disk->gd, disk->capacity);
			add_disk(disk->gd);
			found = 1;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		prपूर्णांकk("%s: no valid drive found\n", name);
		pi_unरेजिस्टर_driver(par_drv);
	पूर्ण
	वापस found;
पूर्ण

अटल पूर्णांक __init pd_init(व्योम)
अणु
	अगर (disable)
		जाओ out1;

	अगर (रेजिस्टर_blkdev(major, name))
		जाओ out1;

	prपूर्णांकk("%s: %s version %s, major %d, cluster %d, nice %d\n",
	       name, name, PD_VERSION, major, cluster, nice);
	अगर (!pd_detect())
		जाओ out2;

	वापस 0;

out2:
	unरेजिस्टर_blkdev(major, name);
out1:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास pd_निकास(व्योम)
अणु
	काष्ठा pd_unit *disk;
	पूर्णांक unit;
	unरेजिस्टर_blkdev(major, name);
	क्रम (unit = 0, disk = pd; unit < PD_UNITS; unit++, disk++) अणु
		काष्ठा gendisk *p = disk->gd;
		अगर (p) अणु
			disk->gd = शून्य;
			del_gendisk(p);
			blk_cleanup_queue(p->queue);
			blk_mq_मुक्त_tag_set(&disk->tag_set);
			put_disk(p);
			pi_release(disk->pi);
		पूर्ण
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
module_init(pd_init)
module_निकास(pd_निकास)
