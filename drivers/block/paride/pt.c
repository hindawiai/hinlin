<शैली गुरु>
/* 
        pt.c    (c) 1998  Grant R. Guenther <grant@torque.net>
                          Under the terms of the GNU General Public License.

        This is the high-level driver क्रम parallel port ATAPI tape
        drives based on chips supported by the paride module.

	The driver implements both शुरुआतing and non-शुरुआतing
	devices, filemarks, and the शुरुआत ioctl.  It allocates
	a small पूर्णांकernal "bounce buffer" क्रम each खोलो device, but
        otherwise expects buffering and blocking to be करोne at the
        user level.  As with most block-काष्ठाured tapes, लघु
	ग_लिखोs are padded to full tape blocks, so पढ़ोing back a file
        may वापस more data than was actually written.

        By शेष, the driver will स्वतःprobe क्रम a single parallel
        port ATAPI tape drive, but अगर their inभागidual parameters are
        specअगरied, the driver can handle up to 4 drives.

	The शुरुआतing devices are named /dev/pt0, /dev/pt1, ...
	जबतक the non-शुरुआतing devices are /dev/npt0, /dev/npt1, etc.

        The behaviour of the pt driver can be altered by setting
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

                <slv>   ATAPI devices can be jumpered to master or slave.
                        Set this to 0 to choose the master drive, 1 to
                        choose the slave, -1 (the शेष) to choose the
                        first drive found.

                <dly>   some parallel ports require the driver to 
                        go more slowly.  -1 sets a शेष value that
                        should work with the chosen protocol.  Otherwise,
                        set this to a small पूर्णांकeger, the larger it is
                        the slower the port i/o.  In some हालs, setting
                        this to zero will speed up the device. (शेष -1)

	    major	You may use this parameter to override the
			शेष major number (96) that this driver
			will use.  Be sure to change the device
			name as well.

	    name	This parameter is a अक्षरacter string that
			contains the name the kernel will use क्रम this
			device (in /proc output, क्रम instance).
			(शेष "pt").

            verbose     This parameter controls the amount of logging
                        that the driver will करो.  Set it to 0 क्रम
                        normal operation, 1 to see स्वतःprobe progress
                        messages, or 2 to see additional debugging
                        output.  (शेष 0)
 
        If this driver is built पूर्णांकo the kernel, you can use 
        the following command line parameters, with the same values
        as the corresponding module parameters listed above:

            pt.drive0
            pt.drive1
            pt.drive2
            pt.drive3

        In addition, you can use the parameter pt.disable to disable
        the driver entirely.

*/

/*   Changes:

	1.01	GRG 1998.05.06	Round up transfer size, fix पढ़ोy_रुको,
			        loosed पूर्णांकerpretation of ATAPI standard
				क्रम clearing error status.
				Eliminate sti();
	1.02    GRG 1998.06.16  Eliminate an Ugh.
	1.03    GRG 1998.08.15  Adjusted PT_TMO, use HZ in loop timing,
				extra debugging
	1.04    GRG 1998.09.24  Repair minor coding error, added jumbo support
	
*/

#घोषणा PT_VERSION      "1.04"
#घोषणा PT_MAJOR	96
#घोषणा PT_NAME		"pt"
#घोषणा PT_UNITS	4

#समावेश <linux/types.h>

/* Here are things one can override from the insmod command.
   Most are स्वतःprobed by paride unless set here.  Verbose is on
   by शेष.

*/

अटल पूर्णांक verbose = 0;
अटल पूर्णांक major = PT_MAJOR;
अटल अक्षर *name = PT_NAME;
अटल पूर्णांक disable = 0;

अटल पूर्णांक drive0[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive1[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive2[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive3[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;

अटल पूर्णांक (*drives[4])[6] = अणु&drive0, &drive1, &drive2, &drive3पूर्ण;

#घोषणा D_PRT   0
#घोषणा D_PRO   1
#घोषणा D_UNI   2
#घोषणा D_MOD   3
#घोषणा D_SLV   4
#घोषणा D_DLY   5

#घोषणा DU              (*drives[unit])

/* end of parameters */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtपन.स>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>	/* current, TASK_*, schedule_समयout() */
#समावेश <linux/mutex.h>

#समावेश <linux/uaccess.h>

module_param(verbose, पूर्णांक, 0);
module_param(major, पूर्णांक, 0);
module_param(name, अक्षरp, 0);
module_param_array(drive0, पूर्णांक, शून्य, 0);
module_param_array(drive1, पूर्णांक, शून्य, 0);
module_param_array(drive2, पूर्णांक, शून्य, 0);
module_param_array(drive3, पूर्णांक, शून्य, 0);

#समावेश "paride.h"

#घोषणा PT_MAX_RETRIES  5
#घोषणा PT_TMO          3000	/* पूर्णांकerrupt समयout in jअगरfies */
#घोषणा PT_SPIN_DEL     50	/* spin delay in micro-seconds  */
#घोषणा PT_RESET_TMO    30	/* 30 seconds */
#घोषणा PT_READY_TMO	60	/* 60 seconds */
#घोषणा PT_REWIND_TMO	1200	/* 20 minutes */

#घोषणा PT_SPIN         ((1000000/(HZ*PT_SPIN_DEL))*PT_TMO)

#घोषणा STAT_ERR        0x00001
#घोषणा STAT_INDEX      0x00002
#घोषणा STAT_ECC        0x00004
#घोषणा STAT_DRQ        0x00008
#घोषणा STAT_SEEK       0x00010
#घोषणा STAT_WRERR      0x00020
#घोषणा STAT_READY      0x00040
#घोषणा STAT_BUSY       0x00080
#घोषणा STAT_SENSE	0x1f000

#घोषणा ATAPI_TEST_READY	0x00
#घोषणा ATAPI_REWIND		0x01
#घोषणा ATAPI_REQ_SENSE		0x03
#घोषणा ATAPI_READ_6		0x08
#घोषणा ATAPI_WRITE_6		0x0a
#घोषणा ATAPI_WFM		0x10
#घोषणा ATAPI_IDENTIFY		0x12
#घोषणा ATAPI_MODE_SENSE	0x1a
#घोषणा ATAPI_LOG_SENSE		0x4d

अटल DEFINE_MUTEX(pt_mutex);
अटल पूर्णांक pt_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल दीर्घ pt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक pt_release(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार pt_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
		       माप_प्रकार count, loff_t * ppos);
अटल sमाप_प्रकार pt_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t * ppos);
अटल पूर्णांक pt_detect(व्योम);

/* bits in tape->flags */

#घोषणा PT_MEDIA	1
#घोषणा PT_WRITE_OK	2
#घोषणा PT_REWIND	4
#घोषणा PT_WRITING      8
#घोषणा PT_READING     16
#घोषणा PT_खातापूर्ण	       32

#घोषणा PT_NAMELEN      8
#घोषणा PT_बफ_मानE  16384

काष्ठा pt_unit अणु
	काष्ठा pi_adapter pia;	/* पूर्णांकerface to paride layer */
	काष्ठा pi_adapter *pi;
	पूर्णांक flags;		/* various state flags */
	पूर्णांक last_sense;		/* result of last request sense */
	पूर्णांक drive;		/* drive */
	atomic_t available;	/* 1 अगर access is available 0 otherwise */
	पूर्णांक bs;			/* block size */
	पूर्णांक capacity;		/* Size of tape in KB */
	पूर्णांक present;		/* device present ? */
	अक्षर *bufptr;
	अक्षर name[PT_NAMELEN];	/* pf0, pf1, ... */
पूर्ण;

अटल पूर्णांक pt_identअगरy(काष्ठा pt_unit *tape);

अटल काष्ठा pt_unit pt[PT_UNITS];

अटल अक्षर pt_scratch[512];	/* scratch block buffer */
अटल व्योम *par_drv;		/* reference of parport driver */

/* kernel glue काष्ठाures */

अटल स्थिर काष्ठा file_operations pt_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = pt_पढ़ो,
	.ग_लिखो = pt_ग_लिखो,
	.unlocked_ioctl = pt_ioctl,
	.खोलो = pt_खोलो,
	.release = pt_release,
	.llseek = noop_llseek,
पूर्ण;

/* sysfs class support */
अटल काष्ठा class *pt_class;

अटल अंतरभूत पूर्णांक status_reg(काष्ठा pi_adapter *pi)
अणु
	वापस pi_पढ़ो_regr(pi, 1, 6);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_reg(काष्ठा pi_adapter *pi, पूर्णांक reg)
अणु
	वापस pi_पढ़ो_regr(pi, 0, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा pi_adapter *pi, पूर्णांक reg, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(pi, 0, reg, val);
पूर्ण

अटल अंतरभूत u8 DRIVE(काष्ठा pt_unit *tape)
अणु
	वापस 0xa0+0x10*tape->drive;
पूर्ण

अटल पूर्णांक pt_रुको(काष्ठा pt_unit *tape, पूर्णांक go, पूर्णांक stop, अक्षर *fun, अक्षर *msg)
अणु
	पूर्णांक j, r, e, s, p;
	काष्ठा pi_adapter *pi = tape->pi;

	j = 0;
	जबतक ((((r = status_reg(pi)) & go) || (stop && (!(r & stop))))
	       && (j++ < PT_SPIN))
		udelay(PT_SPIN_DEL);

	अगर ((r & (STAT_ERR & stop)) || (j > PT_SPIN)) अणु
		s = पढ़ो_reg(pi, 7);
		e = पढ़ो_reg(pi, 1);
		p = पढ़ो_reg(pi, 2);
		अगर (j > PT_SPIN)
			e |= 0x100;
		अगर (fun)
			prपूर्णांकk("%s: %s %s: alt=0x%x stat=0x%x err=0x%x"
			       " loop=%d phase=%d\n",
			       tape->name, fun, msg, r, s, e, j, p);
		वापस (e << 8) + s;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pt_command(काष्ठा pt_unit *tape, अक्षर *cmd, पूर्णांक dlen, अक्षर *fun)
अणु
	काष्ठा pi_adapter *pi = tape->pi;
	pi_connect(pi);

	ग_लिखो_reg(pi, 6, DRIVE(tape));

	अगर (pt_रुको(tape, STAT_BUSY | STAT_DRQ, 0, fun, "before command")) अणु
		pi_disconnect(pi);
		वापस -1;
	पूर्ण

	ग_लिखो_reg(pi, 4, dlen % 256);
	ग_लिखो_reg(pi, 5, dlen / 256);
	ग_लिखो_reg(pi, 7, 0xa0);	/* ATAPI packet command */

	अगर (pt_रुको(tape, STAT_BUSY, STAT_DRQ, fun, "command DRQ")) अणु
		pi_disconnect(pi);
		वापस -1;
	पूर्ण

	अगर (पढ़ो_reg(pi, 2) != 1) अणु
		prपूर्णांकk("%s: %s: command phase error\n", tape->name, fun);
		pi_disconnect(pi);
		वापस -1;
	पूर्ण

	pi_ग_लिखो_block(pi, cmd, 12);

	वापस 0;
पूर्ण

अटल पूर्णांक pt_completion(काष्ठा pt_unit *tape, अक्षर *buf, अक्षर *fun)
अणु
	काष्ठा pi_adapter *pi = tape->pi;
	पूर्णांक r, s, n, p;

	r = pt_रुको(tape, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
		    fun, "completion");

	अगर (पढ़ो_reg(pi, 7) & STAT_DRQ) अणु
		n = (((पढ़ो_reg(pi, 4) + 256 * पढ़ो_reg(pi, 5)) +
		      3) & 0xfffc);
		p = पढ़ो_reg(pi, 2) & 3;
		अगर (p == 0)
			pi_ग_लिखो_block(pi, buf, n);
		अगर (p == 2)
			pi_पढ़ो_block(pi, buf, n);
	पूर्ण

	s = pt_रुको(tape, STAT_BUSY, STAT_READY | STAT_ERR, fun, "data done");

	pi_disconnect(pi);

	वापस (r ? r : s);
पूर्ण

अटल व्योम pt_req_sense(काष्ठा pt_unit *tape, पूर्णांक quiet)
अणु
	अक्षर rs_cmd[12] = अणु ATAPI_REQ_SENSE, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[16];
	पूर्णांक r;

	r = pt_command(tape, rs_cmd, 16, "Request sense");
	mdelay(1);
	अगर (!r)
		pt_completion(tape, buf, "Request sense");

	tape->last_sense = -1;
	अगर (!r) अणु
		अगर (!quiet)
			prपूर्णांकk("%s: Sense key: %x, ASC: %x, ASQ: %x\n",
			       tape->name, buf[2] & 0xf, buf[12], buf[13]);
		tape->last_sense = (buf[2] & 0xf) | ((buf[12] & 0xff) << 8)
		    | ((buf[13] & 0xff) << 16);
	पूर्ण
पूर्ण

अटल पूर्णांक pt_atapi(काष्ठा pt_unit *tape, अक्षर *cmd, पूर्णांक dlen, अक्षर *buf, अक्षर *fun)
अणु
	पूर्णांक r;

	r = pt_command(tape, cmd, dlen, fun);
	mdelay(1);
	अगर (!r)
		r = pt_completion(tape, buf, fun);
	अगर (r)
		pt_req_sense(tape, !fun);

	वापस r;
पूर्ण

अटल व्योम pt_sleep(पूर्णांक cs)
अणु
	schedule_समयout_पूर्णांकerruptible(cs);
पूर्ण

अटल पूर्णांक pt_poll_dsc(काष्ठा pt_unit *tape, पूर्णांक छोड़ो, पूर्णांक पंचांगo, अक्षर *msg)
अणु
	काष्ठा pi_adapter *pi = tape->pi;
	पूर्णांक k, e, s;

	k = 0;
	e = 0;
	s = 0;
	जबतक (k < पंचांगo) अणु
		pt_sleep(छोड़ो);
		k++;
		pi_connect(pi);
		ग_लिखो_reg(pi, 6, DRIVE(tape));
		s = पढ़ो_reg(pi, 7);
		e = पढ़ो_reg(pi, 1);
		pi_disconnect(pi);
		अगर (s & (STAT_ERR | STAT_SEEK))
			अवरोध;
	पूर्ण
	अगर ((k >= पंचांगo) || (s & STAT_ERR)) अणु
		अगर (k >= पंचांगo)
			prपूर्णांकk("%s: %s DSC timeout\n", tape->name, msg);
		अन्यथा
			prपूर्णांकk("%s: %s stat=0x%x err=0x%x\n", tape->name, msg, s,
			       e);
		pt_req_sense(tape, 0);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम pt_media_access_cmd(काष्ठा pt_unit *tape, पूर्णांक पंचांगo, अक्षर *cmd, अक्षर *fun)
अणु
	अगर (pt_command(tape, cmd, 0, fun)) अणु
		pt_req_sense(tape, 0);
		वापस;
	पूर्ण
	pi_disconnect(tape->pi);
	pt_poll_dsc(tape, HZ, पंचांगo, fun);
पूर्ण

अटल व्योम pt_शुरुआत(काष्ठा pt_unit *tape)
अणु
	अक्षर rw_cmd[12] = अणु ATAPI_REWIND, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	pt_media_access_cmd(tape, PT_REWIND_TMO, rw_cmd, "rewind");
पूर्ण

अटल व्योम pt_ग_लिखो_fm(काष्ठा pt_unit *tape)
अणु
	अक्षर wm_cmd[12] = अणु ATAPI_WFM, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	pt_media_access_cmd(tape, PT_TMO, wm_cmd, "write filemark");
पूर्ण

#घोषणा DBMSG(msg)      ((verbose>1)?(msg):शून्य)

अटल पूर्णांक pt_reset(काष्ठा pt_unit *tape)
अणु
	काष्ठा pi_adapter *pi = tape->pi;
	पूर्णांक i, k, flg;
	पूर्णांक expect[5] = अणु 1, 1, 1, 0x14, 0xeb पूर्ण;

	pi_connect(pi);
	ग_लिखो_reg(pi, 6, DRIVE(tape));
	ग_लिखो_reg(pi, 7, 8);

	pt_sleep(20 * HZ / 1000);

	k = 0;
	जबतक ((k++ < PT_RESET_TMO) && (status_reg(pi) & STAT_BUSY))
		pt_sleep(HZ / 10);

	flg = 1;
	क्रम (i = 0; i < 5; i++)
		flg &= (पढ़ो_reg(pi, i + 1) == expect[i]);

	अगर (verbose) अणु
		prपूर्णांकk("%s: Reset (%d) signature = ", tape->name, k);
		क्रम (i = 0; i < 5; i++)
			prपूर्णांकk("%3x", पढ़ो_reg(pi, i + 1));
		अगर (!flg)
			prपूर्णांकk(" (incorrect)");
		prपूर्णांकk("\n");
	पूर्ण

	pi_disconnect(pi);
	वापस flg - 1;
पूर्ण

अटल पूर्णांक pt_पढ़ोy_रुको(काष्ठा pt_unit *tape, पूर्णांक पंचांगo)
अणु
	अक्षर tr_cmd[12] = अणु ATAPI_TEST_READY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक k, p;

	k = 0;
	जबतक (k < पंचांगo) अणु
		tape->last_sense = 0;
		pt_atapi(tape, tr_cmd, 0, शून्य, DBMSG("test unit ready"));
		p = tape->last_sense;
		अगर (!p)
			वापस 0;
		अगर (!(((p & 0xffff) == 0x0402) || ((p & 0xff) == 6)))
			वापस p;
		k++;
		pt_sleep(HZ);
	पूर्ण
	वापस 0x000020;	/* समयout */
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

अटल पूर्णांक xn(अक्षर *buf, पूर्णांक offs, पूर्णांक size)
अणु
	पूर्णांक v, k;

	v = 0;
	क्रम (k = 0; k < size; k++)
		v = v * 256 + (buf[k + offs] & 0xff);
	वापस v;
पूर्ण

अटल पूर्णांक pt_identअगरy(काष्ठा pt_unit *tape)
अणु
	पूर्णांक dt, s;
	अक्षर *ms[2] = अणु "master", "slave" पूर्ण;
	अक्षर mf[10], id[18];
	अक्षर id_cmd[12] = अणु ATAPI_IDENTIFY, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर ms_cmd[12] =
	    अणु ATAPI_MODE_SENSE, 0, 0x2a, 0, 36, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर ls_cmd[12] =
	    अणु ATAPI_LOG_SENSE, 0, 0x71, 0, 0, 0, 0, 0, 36, 0, 0, 0 पूर्ण;
	अक्षर buf[36];

	s = pt_atapi(tape, id_cmd, 36, buf, "identify");
	अगर (s)
		वापस -1;

	dt = buf[0] & 0x1f;
	अगर (dt != 1) अणु
		अगर (verbose)
			prपूर्णांकk("%s: Drive %d, unsupported type %d\n",
			       tape->name, tape->drive, dt);
		वापस -1;
	पूर्ण

	xs(buf, mf, 8, 8);
	xs(buf, id, 16, 16);

	tape->flags = 0;
	tape->capacity = 0;
	tape->bs = 0;

	अगर (!pt_पढ़ोy_रुको(tape, PT_READY_TMO))
		tape->flags |= PT_MEDIA;

	अगर (!pt_atapi(tape, ms_cmd, 36, buf, "mode sense")) अणु
		अगर (!(buf[2] & 0x80))
			tape->flags |= PT_WRITE_OK;
		tape->bs = xn(buf, 10, 2);
	पूर्ण

	अगर (!pt_atapi(tape, ls_cmd, 36, buf, "log sense"))
		tape->capacity = xn(buf, 24, 4);

	prपूर्णांकk("%s: %s %s, %s", tape->name, mf, id, ms[tape->drive]);
	अगर (!(tape->flags & PT_MEDIA))
		prपूर्णांकk(", no media\n");
	अन्यथा अणु
		अगर (!(tape->flags & PT_WRITE_OK))
			prपूर्णांकk(", RO");
		prपूर्णांकk(", blocksize %d, %d MB\n", tape->bs, tape->capacity / 1024);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * वापसs  0, with id set अगर drive is detected
 *	   -1, अगर drive detection failed
 */
अटल पूर्णांक pt_probe(काष्ठा pt_unit *tape)
अणु
	अगर (tape->drive == -1) अणु
		क्रम (tape->drive = 0; tape->drive <= 1; tape->drive++)
			अगर (!pt_reset(tape))
				वापस pt_identअगरy(tape);
	पूर्ण अन्यथा अणु
		अगर (!pt_reset(tape))
			वापस pt_identअगरy(tape);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक pt_detect(व्योम)
अणु
	काष्ठा pt_unit *tape;
	पूर्णांक specअगरied = 0, found = 0;
	पूर्णांक unit;

	prपूर्णांकk("%s: %s version %s, major %d\n", name, name, PT_VERSION, major);

	par_drv = pi_रेजिस्टर_driver(name);
	अगर (!par_drv) अणु
		pr_err("failed to register %s driver\n", name);
		वापस -1;
	पूर्ण

	specअगरied = 0;
	क्रम (unit = 0; unit < PT_UNITS; unit++) अणु
		काष्ठा pt_unit *tape = &pt[unit];
		tape->pi = &tape->pia;
		atomic_set(&tape->available, 1);
		tape->flags = 0;
		tape->last_sense = 0;
		tape->present = 0;
		tape->bufptr = शून्य;
		tape->drive = DU[D_SLV];
		snम_लिखो(tape->name, PT_NAMELEN, "%s%d", name, unit);
		अगर (!DU[D_PRT])
			जारी;
		specअगरied++;
		अगर (pi_init(tape->pi, 0, DU[D_PRT], DU[D_MOD], DU[D_UNI],
		     DU[D_PRO], DU[D_DLY], pt_scratch, PI_PT,
		     verbose, tape->name)) अणु
			अगर (!pt_probe(tape)) अणु
				tape->present = 1;
				found++;
			पूर्ण अन्यथा
				pi_release(tape->pi);
		पूर्ण
	पूर्ण
	अगर (specअगरied == 0) अणु
		tape = pt;
		अगर (pi_init(tape->pi, 1, -1, -1, -1, -1, -1, pt_scratch,
			    PI_PT, verbose, tape->name)) अणु
			अगर (!pt_probe(tape)) अणु
				tape->present = 1;
				found++;
			पूर्ण अन्यथा
				pi_release(tape->pi);
		पूर्ण

	पूर्ण
	अगर (found)
		वापस 0;

	pi_unरेजिस्टर_driver(par_drv);
	prपूर्णांकk("%s: No ATAPI tape drive detected\n", name);
	वापस -1;
पूर्ण

अटल पूर्णांक pt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक unit = iminor(inode) & 0x7F;
	काष्ठा pt_unit *tape = pt + unit;
	पूर्णांक err;

	mutex_lock(&pt_mutex);
	अगर (unit >= PT_UNITS || (!tape->present)) अणु
		mutex_unlock(&pt_mutex);
		वापस -ENODEV;
	पूर्ण

	err = -EBUSY;
	अगर (!atomic_dec_and_test(&tape->available))
		जाओ out;

	pt_identअगरy(tape);

	err = -ENODEV;
	अगर (!(tape->flags & PT_MEDIA))
		जाओ out;

	err = -EROFS;
	अगर ((!(tape->flags & PT_WRITE_OK)) && (file->f_mode & FMODE_WRITE))
		जाओ out;

	अगर (!(iminor(inode) & 128))
		tape->flags |= PT_REWIND;

	err = -ENOMEM;
	tape->bufptr = kदो_स्मृति(PT_बफ_मानE, GFP_KERNEL);
	अगर (tape->bufptr == शून्य) अणु
		prपूर्णांकk("%s: buffer allocation failed\n", tape->name);
		जाओ out;
	पूर्ण

	file->निजी_data = tape;
	mutex_unlock(&pt_mutex);
	वापस 0;

out:
	atomic_inc(&tape->available);
	mutex_unlock(&pt_mutex);
	वापस err;
पूर्ण

अटल दीर्घ pt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pt_unit *tape = file->निजी_data;
	काष्ठा mtop __user *p = (व्योम __user *)arg;
	काष्ठा mtop mtop;

	चयन (cmd) अणु
	हाल MTIOCTOP:
		अगर (copy_from_user(&mtop, p, माप(काष्ठा mtop)))
			वापस -EFAULT;

		चयन (mtop.mt_op) अणु

		हाल MTREW:
			mutex_lock(&pt_mutex);
			pt_शुरुआत(tape);
			mutex_unlock(&pt_mutex);
			वापस 0;

		हाल MTWखातापूर्ण:
			mutex_lock(&pt_mutex);
			pt_ग_लिखो_fm(tape);
			mutex_unlock(&pt_mutex);
			वापस 0;

		शेष:
			/* FIXME: rate limit ?? */
			prपूर्णांकk(KERN_DEBUG "%s: Unimplemented mt_op %d\n", tape->name,
			       mtop.mt_op);
			वापस -EINVAL;
		पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक
pt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pt_unit *tape = file->निजी_data;

	अगर (atomic_पढ़ो(&tape->available) > 1)
		वापस -EINVAL;

	अगर (tape->flags & PT_WRITING)
		pt_ग_लिखो_fm(tape);

	अगर (tape->flags & PT_REWIND)
		pt_शुरुआत(tape);

	kमुक्त(tape->bufptr);
	tape->bufptr = शून्य;

	atomic_inc(&tape->available);

	वापस 0;

पूर्ण

अटल sमाप_प्रकार pt_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	काष्ठा pt_unit *tape = filp->निजी_data;
	काष्ठा pi_adapter *pi = tape->pi;
	अक्षर rd_cmd[12] = अणु ATAPI_READ_6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक k, n, r, p, s, t, b;

	अगर (!(tape->flags & (PT_READING | PT_WRITING))) अणु
		tape->flags |= PT_READING;
		अगर (pt_atapi(tape, rd_cmd, 0, शून्य, "start read-ahead"))
			वापस -EIO;
	पूर्ण अन्यथा अगर (tape->flags & PT_WRITING)
		वापस -EIO;

	अगर (tape->flags & PT_खातापूर्ण)
		वापस 0;

	t = 0;

	जबतक (count > 0) अणु

		अगर (!pt_poll_dsc(tape, HZ / 100, PT_TMO, "read"))
			वापस -EIO;

		n = count;
		अगर (n > 32768)
			n = 32768;	/* max per command */
		b = (n - 1 + tape->bs) / tape->bs;
		n = b * tape->bs;	/* rounded up to even block */

		rd_cmd[4] = b;

		r = pt_command(tape, rd_cmd, n, "read");

		mdelay(1);

		अगर (r) अणु
			pt_req_sense(tape, 0);
			वापस -EIO;
		पूर्ण

		जबतक (1) अणु

			r = pt_रुको(tape, STAT_BUSY,
				    STAT_DRQ | STAT_ERR | STAT_READY,
				    DBMSG("read DRQ"), "");

			अगर (r & STAT_SENSE) अणु
				pi_disconnect(pi);
				pt_req_sense(tape, 0);
				वापस -EIO;
			पूर्ण

			अगर (r)
				tape->flags |= PT_खातापूर्ण;

			s = पढ़ो_reg(pi, 7);

			अगर (!(s & STAT_DRQ))
				अवरोध;

			n = (पढ़ो_reg(pi, 4) + 256 * पढ़ो_reg(pi, 5));
			p = (पढ़ो_reg(pi, 2) & 3);
			अगर (p != 2) अणु
				pi_disconnect(pi);
				prपूर्णांकk("%s: Phase error on read: %d\n", tape->name,
				       p);
				वापस -EIO;
			पूर्ण

			जबतक (n > 0) अणु
				k = n;
				अगर (k > PT_बफ_मानE)
					k = PT_बफ_मानE;
				pi_पढ़ो_block(pi, tape->bufptr, k);
				n -= k;
				b = k;
				अगर (b > count)
					b = count;
				अगर (copy_to_user(buf + t, tape->bufptr, b)) अणु
					pi_disconnect(pi);
					वापस -EFAULT;
				पूर्ण
				t += b;
				count -= b;
			पूर्ण

		पूर्ण
		pi_disconnect(pi);
		अगर (tape->flags & PT_खातापूर्ण)
			अवरोध;
	पूर्ण

	वापस t;

पूर्ण

अटल sमाप_प्रकार pt_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	काष्ठा pt_unit *tape = filp->निजी_data;
	काष्ठा pi_adapter *pi = tape->pi;
	अक्षर wr_cmd[12] = अणु ATAPI_WRITE_6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक k, n, r, p, s, t, b;

	अगर (!(tape->flags & PT_WRITE_OK))
		वापस -EROFS;

	अगर (!(tape->flags & (PT_READING | PT_WRITING))) अणु
		tape->flags |= PT_WRITING;
		अगर (pt_atapi
		    (tape, wr_cmd, 0, शून्य, "start buffer-available mode"))
			वापस -EIO;
	पूर्ण अन्यथा अगर (tape->flags & PT_READING)
		वापस -EIO;

	अगर (tape->flags & PT_खातापूर्ण)
		वापस -ENOSPC;

	t = 0;

	जबतक (count > 0) अणु

		अगर (!pt_poll_dsc(tape, HZ / 100, PT_TMO, "write"))
			वापस -EIO;

		n = count;
		अगर (n > 32768)
			n = 32768;	/* max per command */
		b = (n - 1 + tape->bs) / tape->bs;
		n = b * tape->bs;	/* rounded up to even block */

		wr_cmd[4] = b;

		r = pt_command(tape, wr_cmd, n, "write");

		mdelay(1);

		अगर (r) अणु	/* error delivering command only */
			pt_req_sense(tape, 0);
			वापस -EIO;
		पूर्ण

		जबतक (1) अणु

			r = pt_रुको(tape, STAT_BUSY,
				    STAT_DRQ | STAT_ERR | STAT_READY,
				    DBMSG("write DRQ"), शून्य);

			अगर (r & STAT_SENSE) अणु
				pi_disconnect(pi);
				pt_req_sense(tape, 0);
				वापस -EIO;
			पूर्ण

			अगर (r)
				tape->flags |= PT_खातापूर्ण;

			s = पढ़ो_reg(pi, 7);

			अगर (!(s & STAT_DRQ))
				अवरोध;

			n = (पढ़ो_reg(pi, 4) + 256 * पढ़ो_reg(pi, 5));
			p = (पढ़ो_reg(pi, 2) & 3);
			अगर (p != 0) अणु
				pi_disconnect(pi);
				prपूर्णांकk("%s: Phase error on write: %d \n",
				       tape->name, p);
				वापस -EIO;
			पूर्ण

			जबतक (n > 0) अणु
				k = n;
				अगर (k > PT_बफ_मानE)
					k = PT_बफ_मानE;
				b = k;
				अगर (b > count)
					b = count;
				अगर (copy_from_user(tape->bufptr, buf + t, b)) अणु
					pi_disconnect(pi);
					वापस -EFAULT;
				पूर्ण
				pi_ग_लिखो_block(pi, tape->bufptr, k);
				t += b;
				count -= b;
				n -= k;
			पूर्ण

		पूर्ण
		pi_disconnect(pi);
		अगर (tape->flags & PT_खातापूर्ण)
			अवरोध;
	पूर्ण

	वापस t;
पूर्ण

अटल पूर्णांक __init pt_init(व्योम)
अणु
	पूर्णांक unit;
	पूर्णांक err;

	अगर (disable) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (pt_detect()) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = रेजिस्टर_chrdev(major, name, &pt_fops);
	अगर (err < 0) अणु
		prपूर्णांकk("pt_init: unable to get major number %d\n", major);
		क्रम (unit = 0; unit < PT_UNITS; unit++)
			अगर (pt[unit].present)
				pi_release(pt[unit].pi);
		जाओ out;
	पूर्ण
	major = err;
	pt_class = class_create(THIS_MODULE, "pt");
	अगर (IS_ERR(pt_class)) अणु
		err = PTR_ERR(pt_class);
		जाओ out_chrdev;
	पूर्ण

	क्रम (unit = 0; unit < PT_UNITS; unit++)
		अगर (pt[unit].present) अणु
			device_create(pt_class, शून्य, MKDEV(major, unit), शून्य,
				      "pt%d", unit);
			device_create(pt_class, शून्य, MKDEV(major, unit + 128),
				      शून्य, "pt%dn", unit);
		पूर्ण
	जाओ out;

out_chrdev:
	unरेजिस्टर_chrdev(major, "pt");
out:
	वापस err;
पूर्ण

अटल व्योम __निकास pt_निकास(व्योम)
अणु
	पूर्णांक unit;
	क्रम (unit = 0; unit < PT_UNITS; unit++)
		अगर (pt[unit].present) अणु
			device_destroy(pt_class, MKDEV(major, unit));
			device_destroy(pt_class, MKDEV(major, unit + 128));
		पूर्ण
	class_destroy(pt_class);
	unरेजिस्टर_chrdev(major, name);
	क्रम (unit = 0; unit < PT_UNITS; unit++)
		अगर (pt[unit].present)
			pi_release(pt[unit].pi);
पूर्ण

MODULE_LICENSE("GPL");
module_init(pt_init)
module_निकास(pt_निकास)
