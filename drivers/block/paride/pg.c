<शैली गुरु>
/* 
	pg.c    (c) 1998  Grant R. Guenther <grant@torque.net>
			  Under the terms of the GNU General Public License.

	The pg driver provides a simple अक्षरacter device पूर्णांकerface क्रम
	sending ATAPI commands to a device.  With the exception of the
	ATAPI reset operation, all operations are perक्रमmed by a pair
	of पढ़ो and ग_लिखो operations to the appropriate /dev/pgN device.
	A ग_लिखो operation delivers a command and any outbound data in
	a single buffer.  Normally, the ग_लिखो will succeed unless the
	device is offline or malfunctioning, or there is alपढ़ोy another
	command pending.  If the ग_लिखो succeeds, it should be followed
	immediately by a पढ़ो operation, to obtain any वापसed data and
	status inक्रमmation.  A पढ़ो will fail अगर there is no operation
	in progress.

	As a special हाल, the device can be reset with a ग_लिखो operation,
	and in this हाल, no following पढ़ो is expected, or permitted.

	There are no ioctl() operations.  Any single operation
	may transfer at most PG_MAX_DATA bytes.  Note that the driver must
	copy the data through an पूर्णांकernal buffer.  In keeping with all
	current ATAPI devices, command packets are assumed to be exactly
	12 bytes in length.

	To permit future changes to this पूर्णांकerface, the headers in the
	पढ़ो and ग_लिखो buffers contain a single अक्षरacter "magic" flag.
	Currently this flag must be the अक्षरacter "P".

	By शेष, the driver will स्वतःprobe क्रम a single parallel
	port ATAPI device, but अगर their inभागidual parameters are
	specअगरied, the driver can handle up to 4 devices.

	To use this device, you must have the following device 
	special files defined:

		/dev/pg0 c 97 0
		/dev/pg1 c 97 1
		/dev/pg2 c 97 2
		/dev/pg3 c 97 3

	(You'll need to change the 97 to something अन्यथा अगर you use
	the 'major' parameter to install the driver on a dअगरferent
	major number.)

	The behaviour of the pg driver can be altered by setting
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
			शेष major number (97) that this driver
			will use.  Be sure to change the device
			name as well.

	    name	This parameter is a अक्षरacter string that
			contains the name the kernel will use क्रम this
			device (in /proc output, क्रम instance).
			(शेष "pg").

	    verbose     This parameter controls the amount of logging
			that is करोne by the driver.  Set it to 0 क्रम 
			quiet operation, to 1 to enable progress
			messages जबतक the driver probes क्रम devices,
			or to 2 क्रम full debug logging.  (शेष 0)

	If this driver is built पूर्णांकo the kernel, you can use 
	the following command line parameters, with the same values
	as the corresponding module parameters listed above:

	    pg.drive0
	    pg.drive1
	    pg.drive2
	    pg.drive3

	In addition, you can use the parameter pg.disable to disable
	the driver entirely.

*/

/* Changes:

	1.01	GRG 1998.06.16	Bug fixes
	1.02    GRG 1998.09.24  Added jumbo support

*/

#घोषणा PG_VERSION      "1.02"
#घोषणा PG_MAJOR	97
#घोषणा PG_NAME		"pg"
#घोषणा PG_UNITS	4

#अगर_अघोषित PI_PG
#घोषणा PI_PG	4
#पूर्ण_अगर

#समावेश <linux/types.h>
/* Here are things one can override from the insmod command.
   Most are स्वतःprobed by paride unless set here.  Verbose is 0
   by शेष.

*/

अटल पूर्णांक verbose;
अटल पूर्णांक major = PG_MAJOR;
अटल अक्षर *name = PG_NAME;
अटल पूर्णांक disable = 0;

अटल पूर्णांक drive0[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive1[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive2[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;
अटल पूर्णांक drive3[6] = अणु 0, 0, 0, -1, -1, -1 पूर्ण;

अटल पूर्णांक (*drives[4])[6] = अणु&drive0, &drive1, &drive2, &drive3पूर्ण;
अटल पूर्णांक pg_drive_count;

क्रमागत अणुD_PRT, D_PRO, D_UNI, D_MOD, D_SLV, D_DLYपूर्ण;

/* end of parameters */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtपन.स>
#समावेश <linux/pg.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>	/* current, TASK_* */
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/uaccess.h>

module_param(verbose, पूर्णांक, 0644);
module_param(major, पूर्णांक, 0);
module_param(name, अक्षरp, 0);
module_param_array(drive0, पूर्णांक, शून्य, 0);
module_param_array(drive1, पूर्णांक, शून्य, 0);
module_param_array(drive2, पूर्णांक, शून्य, 0);
module_param_array(drive3, पूर्णांक, शून्य, 0);

#समावेश "paride.h"

#घोषणा PG_SPIN_DEL     50	/* spin delay in micro-seconds  */
#घोषणा PG_SPIN         200
#घोषणा PG_TMO		HZ
#घोषणा PG_RESET_TMO	10*HZ

#घोषणा STAT_ERR        0x01
#घोषणा STAT_INDEX      0x02
#घोषणा STAT_ECC        0x04
#घोषणा STAT_DRQ        0x08
#घोषणा STAT_SEEK       0x10
#घोषणा STAT_WRERR      0x20
#घोषणा STAT_READY      0x40
#घोषणा STAT_BUSY       0x80

#घोषणा ATAPI_IDENTIFY		0x12

अटल DEFINE_MUTEX(pg_mutex);
अटल पूर्णांक pg_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक pg_release(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार pg_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
		       माप_प्रकार count, loff_t * ppos);
अटल sमाप_प्रकार pg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t * ppos);
अटल पूर्णांक pg_detect(व्योम);

#घोषणा PG_NAMELEN      8

काष्ठा pg अणु
	काष्ठा pi_adapter pia;	/* पूर्णांकerface to paride layer */
	काष्ठा pi_adapter *pi;
	पूर्णांक busy;		/* ग_लिखो करोne, पढ़ो expected */
	पूर्णांक start;		/* jअगरfies at command start */
	पूर्णांक dlen;		/* transfer size requested */
	अचिन्हित दीर्घ समयout;	/* समयout requested */
	पूर्णांक status;		/* last sense key */
	पूर्णांक drive;		/* drive */
	अचिन्हित दीर्घ access;	/* count of active खोलोs ... */
	पूर्णांक present;		/* device present ? */
	अक्षर *bufptr;
	अक्षर name[PG_NAMELEN];	/* pg0, pg1, ... */
पूर्ण;

अटल काष्ठा pg devices[PG_UNITS];

अटल पूर्णांक pg_identअगरy(काष्ठा pg *dev, पूर्णांक log);

अटल अक्षर pg_scratch[512];	/* scratch block buffer */

अटल काष्ठा class *pg_class;
अटल व्योम *par_drv;		/* reference of parport driver */

/* kernel glue काष्ठाures */

अटल स्थिर काष्ठा file_operations pg_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = pg_पढ़ो,
	.ग_लिखो = pg_ग_लिखो,
	.खोलो = pg_खोलो,
	.release = pg_release,
	.llseek = noop_llseek,
पूर्ण;

अटल व्योम pg_init_units(व्योम)
अणु
	पूर्णांक unit;

	pg_drive_count = 0;
	क्रम (unit = 0; unit < PG_UNITS; unit++) अणु
		पूर्णांक *parm = *drives[unit];
		काष्ठा pg *dev = &devices[unit];
		dev->pi = &dev->pia;
		clear_bit(0, &dev->access);
		dev->busy = 0;
		dev->present = 0;
		dev->bufptr = शून्य;
		dev->drive = parm[D_SLV];
		snम_लिखो(dev->name, PG_NAMELEN, "%s%c", name, 'a'+unit);
		अगर (parm[D_PRT])
			pg_drive_count++;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक status_reg(काष्ठा pg *dev)
अणु
	वापस pi_पढ़ो_regr(dev->pi, 1, 6);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_reg(काष्ठा pg *dev, पूर्णांक reg)
अणु
	वापस pi_पढ़ो_regr(dev->pi, 0, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा pg *dev, पूर्णांक reg, पूर्णांक val)
अणु
	pi_ग_लिखो_regr(dev->pi, 0, reg, val);
पूर्ण

अटल अंतरभूत u8 DRIVE(काष्ठा pg *dev)
अणु
	वापस 0xa0+0x10*dev->drive;
पूर्ण

अटल व्योम pg_sleep(पूर्णांक cs)
अणु
	schedule_समयout_पूर्णांकerruptible(cs);
पूर्ण

अटल पूर्णांक pg_रुको(काष्ठा pg *dev, पूर्णांक go, पूर्णांक stop, अचिन्हित दीर्घ पंचांगo, अक्षर *msg)
अणु
	पूर्णांक j, r, e, s, p, to;

	dev->status = 0;

	j = 0;
	जबतक ((((r = status_reg(dev)) & go) || (stop && (!(r & stop))))
	       && समय_beक्रमe(jअगरfies, पंचांगo)) अणु
		अगर (j++ < PG_SPIN)
			udelay(PG_SPIN_DEL);
		अन्यथा
			pg_sleep(1);
	पूर्ण

	to = समय_after_eq(jअगरfies, पंचांगo);

	अगर ((r & (STAT_ERR & stop)) || to) अणु
		s = पढ़ो_reg(dev, 7);
		e = पढ़ो_reg(dev, 1);
		p = पढ़ो_reg(dev, 2);
		अगर (verbose > 1)
			prपूर्णांकk("%s: %s: stat=0x%x err=0x%x phase=%d%s\n",
			       dev->name, msg, s, e, p, to ? " timeout" : "");
		अगर (to)
			e |= 0x100;
		dev->status = (e >> 4) & 0xff;
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pg_command(काष्ठा pg *dev, अक्षर *cmd, पूर्णांक dlen, अचिन्हित दीर्घ पंचांगo)
अणु
	पूर्णांक k;

	pi_connect(dev->pi);

	ग_लिखो_reg(dev, 6, DRIVE(dev));

	अगर (pg_रुको(dev, STAT_BUSY | STAT_DRQ, 0, पंचांगo, "before command"))
		जाओ fail;

	ग_लिखो_reg(dev, 4, dlen % 256);
	ग_लिखो_reg(dev, 5, dlen / 256);
	ग_लिखो_reg(dev, 7, 0xa0);	/* ATAPI packet command */

	अगर (pg_रुको(dev, STAT_BUSY, STAT_DRQ, पंचांगo, "command DRQ"))
		जाओ fail;

	अगर (पढ़ो_reg(dev, 2) != 1) अणु
		prपूर्णांकk("%s: command phase error\n", dev->name);
		जाओ fail;
	पूर्ण

	pi_ग_लिखो_block(dev->pi, cmd, 12);

	अगर (verbose > 1) अणु
		prपूर्णांकk("%s: Command sent, dlen=%d packet= ", dev->name, dlen);
		क्रम (k = 0; k < 12; k++)
			prपूर्णांकk("%02x ", cmd[k] & 0xff);
		prपूर्णांकk("\n");
	पूर्ण
	वापस 0;
fail:
	pi_disconnect(dev->pi);
	वापस -1;
पूर्ण

अटल पूर्णांक pg_completion(काष्ठा pg *dev, अक्षर *buf, अचिन्हित दीर्घ पंचांगo)
अणु
	पूर्णांक r, d, n, p;

	r = pg_रुको(dev, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
		    पंचांगo, "completion");

	dev->dlen = 0;

	जबतक (पढ़ो_reg(dev, 7) & STAT_DRQ) अणु
		d = (पढ़ो_reg(dev, 4) + 256 * पढ़ो_reg(dev, 5));
		n = ((d + 3) & 0xfffc);
		p = पढ़ो_reg(dev, 2) & 3;
		अगर (p == 0)
			pi_ग_लिखो_block(dev->pi, buf, n);
		अगर (p == 2)
			pi_पढ़ो_block(dev->pi, buf, n);
		अगर (verbose > 1)
			prपूर्णांकk("%s: %s %d bytes\n", dev->name,
			       p ? "Read" : "Write", n);
		dev->dlen += (1 - p) * d;
		buf += d;
		r = pg_रुको(dev, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
			    पंचांगo, "completion");
	पूर्ण

	pi_disconnect(dev->pi);

	वापस r;
पूर्ण

अटल पूर्णांक pg_reset(काष्ठा pg *dev)
अणु
	पूर्णांक i, k, err;
	पूर्णांक expect[5] = अणु 1, 1, 1, 0x14, 0xeb पूर्ण;
	पूर्णांक got[5];

	pi_connect(dev->pi);
	ग_लिखो_reg(dev, 6, DRIVE(dev));
	ग_लिखो_reg(dev, 7, 8);

	pg_sleep(20 * HZ / 1000);

	k = 0;
	जबतक ((k++ < PG_RESET_TMO) && (status_reg(dev) & STAT_BUSY))
		pg_sleep(1);

	क्रम (i = 0; i < 5; i++)
		got[i] = पढ़ो_reg(dev, i + 1);

	err = स_भेद(expect, got, माप(got)) ? -1 : 0;

	अगर (verbose) अणु
		prपूर्णांकk("%s: Reset (%d) signature = ", dev->name, k);
		क्रम (i = 0; i < 5; i++)
			prपूर्णांकk("%3x", got[i]);
		अगर (err)
			prपूर्णांकk(" (incorrect)");
		prपूर्णांकk("\n");
	पूर्ण

	pi_disconnect(dev->pi);
	वापस err;
पूर्ण

अटल व्योम xs(अक्षर *buf, अक्षर *targ, पूर्णांक len)
अणु
	अक्षर l = '\0';
	पूर्णांक k;

	क्रम (k = 0; k < len; k++) अणु
		अक्षर c = *buf++;
		अगर (c != ' ' && c != l)
			l = *targ++ = c;
	पूर्ण
	अगर (l == ' ')
		targ--;
	*targ = '\0';
पूर्ण

अटल पूर्णांक pg_identअगरy(काष्ठा pg *dev, पूर्णांक log)
अणु
	पूर्णांक s;
	अक्षर *ms[2] = अणु "master", "slave" पूर्ण;
	अक्षर mf[10], id[18];
	अक्षर id_cmd[12] = अणु ATAPI_IDENTIFY, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	अक्षर buf[36];

	s = pg_command(dev, id_cmd, 36, jअगरfies + PG_TMO);
	अगर (s)
		वापस -1;
	s = pg_completion(dev, buf, jअगरfies + PG_TMO);
	अगर (s)
		वापस -1;

	अगर (log) अणु
		xs(buf + 8, mf, 8);
		xs(buf + 16, id, 16);
		prपूर्णांकk("%s: %s %s, %s\n", dev->name, mf, id, ms[dev->drive]);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापसs  0, with id set अगर drive is detected
 *	   -1, अगर drive detection failed
 */
अटल पूर्णांक pg_probe(काष्ठा pg *dev)
अणु
	अगर (dev->drive == -1) अणु
		क्रम (dev->drive = 0; dev->drive <= 1; dev->drive++)
			अगर (!pg_reset(dev))
				वापस pg_identअगरy(dev, 1);
	पूर्ण अन्यथा अणु
		अगर (!pg_reset(dev))
			वापस pg_identअगरy(dev, 1);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक pg_detect(व्योम)
अणु
	काष्ठा pg *dev = &devices[0];
	पूर्णांक k, unit;

	prपूर्णांकk("%s: %s version %s, major %d\n", name, name, PG_VERSION, major);

	par_drv = pi_रेजिस्टर_driver(name);
	अगर (!par_drv) अणु
		pr_err("failed to register %s driver\n", name);
		वापस -1;
	पूर्ण

	k = 0;
	अगर (pg_drive_count == 0) अणु
		अगर (pi_init(dev->pi, 1, -1, -1, -1, -1, -1, pg_scratch,
			    PI_PG, verbose, dev->name)) अणु
			अगर (!pg_probe(dev)) अणु
				dev->present = 1;
				k++;
			पूर्ण अन्यथा
				pi_release(dev->pi);
		पूर्ण

	पूर्ण अन्यथा
		क्रम (unit = 0; unit < PG_UNITS; unit++, dev++) अणु
			पूर्णांक *parm = *drives[unit];
			अगर (!parm[D_PRT])
				जारी;
			अगर (pi_init(dev->pi, 0, parm[D_PRT], parm[D_MOD],
				    parm[D_UNI], parm[D_PRO], parm[D_DLY],
				    pg_scratch, PI_PG, verbose, dev->name)) अणु
				अगर (!pg_probe(dev)) अणु
					dev->present = 1;
					k++;
				पूर्ण अन्यथा
					pi_release(dev->pi);
			पूर्ण
		पूर्ण

	अगर (k)
		वापस 0;

	pi_unरेजिस्टर_driver(par_drv);
	prपूर्णांकk("%s: No ATAPI device detected\n", name);
	वापस -1;
पूर्ण

अटल पूर्णांक pg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक unit = iminor(inode) & 0x7f;
	काष्ठा pg *dev = &devices[unit];
	पूर्णांक ret = 0;

	mutex_lock(&pg_mutex);
	अगर ((unit >= PG_UNITS) || (!dev->present)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (test_and_set_bit(0, &dev->access)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (dev->busy) अणु
		pg_reset(dev);
		dev->busy = 0;
	पूर्ण

	pg_identअगरy(dev, (verbose > 1));

	dev->bufptr = kदो_स्मृति(PG_MAX_DATA, GFP_KERNEL);
	अगर (dev->bufptr == शून्य) अणु
		clear_bit(0, &dev->access);
		prपूर्णांकk("%s: buffer allocation failed\n", dev->name);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	file->निजी_data = dev;

out:
	mutex_unlock(&pg_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक pg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pg *dev = file->निजी_data;

	kमुक्त(dev->bufptr);
	dev->bufptr = शून्य;
	clear_bit(0, &dev->access);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pg *dev = filp->निजी_data;
	काष्ठा pg_ग_लिखो_hdr hdr;
	पूर्णांक hs = माप (hdr);

	अगर (dev->busy)
		वापस -EBUSY;
	अगर (count < hs)
		वापस -EINVAL;

	अगर (copy_from_user(&hdr, buf, hs))
		वापस -EFAULT;

	अगर (hdr.magic != PG_MAGIC)
		वापस -EINVAL;
	अगर (hdr.dlen < 0 || hdr.dlen > PG_MAX_DATA)
		वापस -EINVAL;
	अगर ((count - hs) > PG_MAX_DATA)
		वापस -EINVAL;

	अगर (hdr.func == PG_RESET) अणु
		अगर (count != hs)
			वापस -EINVAL;
		अगर (pg_reset(dev))
			वापस -EIO;
		वापस count;
	पूर्ण

	अगर (hdr.func != PG_COMMAND)
		वापस -EINVAL;

	dev->start = jअगरfies;
	dev->समयout = hdr.समयout * HZ + HZ / 2 + jअगरfies;

	अगर (pg_command(dev, hdr.packet, hdr.dlen, jअगरfies + PG_TMO)) अणु
		अगर (dev->status & 0x10)
			वापस -ETIME;
		वापस -EIO;
	पूर्ण

	dev->busy = 1;

	अगर (copy_from_user(dev->bufptr, buf + hs, count - hs))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल sमाप_प्रकार pg_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pg *dev = filp->निजी_data;
	काष्ठा pg_पढ़ो_hdr hdr;
	पूर्णांक hs = माप (hdr);
	पूर्णांक copy;

	अगर (!dev->busy)
		वापस -EINVAL;
	अगर (count < hs)
		वापस -EINVAL;

	dev->busy = 0;

	अगर (pg_completion(dev, dev->bufptr, dev->समयout))
		अगर (dev->status & 0x10)
			वापस -ETIME;

	स_रखो(&hdr, 0, माप(hdr));
	hdr.magic = PG_MAGIC;
	hdr.dlen = dev->dlen;
	copy = 0;

	अगर (hdr.dlen < 0) अणु
		hdr.dlen = -1 * hdr.dlen;
		copy = hdr.dlen;
		अगर (copy > (count - hs))
			copy = count - hs;
	पूर्ण

	hdr.duration = (jअगरfies - dev->start + HZ / 2) / HZ;
	hdr.scsi = dev->status & 0x0f;

	अगर (copy_to_user(buf, &hdr, hs))
		वापस -EFAULT;
	अगर (copy > 0)
		अगर (copy_to_user(buf + hs, dev->bufptr, copy))
			वापस -EFAULT;
	वापस copy + hs;
पूर्ण

अटल पूर्णांक __init pg_init(व्योम)
अणु
	पूर्णांक unit;
	पूर्णांक err;

	अगर (disable)अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	pg_init_units();

	अगर (pg_detect()) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = रेजिस्टर_chrdev(major, name, &pg_fops);
	अगर (err < 0) अणु
		prपूर्णांकk("pg_init: unable to get major number %d\n", major);
		क्रम (unit = 0; unit < PG_UNITS; unit++) अणु
			काष्ठा pg *dev = &devices[unit];
			अगर (dev->present)
				pi_release(dev->pi);
		पूर्ण
		जाओ out;
	पूर्ण
	major = err;	/* In हाल the user specअगरied `major=0' (dynamic) */
	pg_class = class_create(THIS_MODULE, "pg");
	अगर (IS_ERR(pg_class)) अणु
		err = PTR_ERR(pg_class);
		जाओ out_chrdev;
	पूर्ण
	क्रम (unit = 0; unit < PG_UNITS; unit++) अणु
		काष्ठा pg *dev = &devices[unit];
		अगर (dev->present)
			device_create(pg_class, शून्य, MKDEV(major, unit), शून्य,
				      "pg%u", unit);
	पूर्ण
	err = 0;
	जाओ out;

out_chrdev:
	unरेजिस्टर_chrdev(major, "pg");
out:
	वापस err;
पूर्ण

अटल व्योम __निकास pg_निकास(व्योम)
अणु
	पूर्णांक unit;

	क्रम (unit = 0; unit < PG_UNITS; unit++) अणु
		काष्ठा pg *dev = &devices[unit];
		अगर (dev->present)
			device_destroy(pg_class, MKDEV(major, unit));
	पूर्ण
	class_destroy(pg_class);
	unरेजिस्टर_chrdev(major, name);

	क्रम (unit = 0; unit < PG_UNITS; unit++) अणु
		काष्ठा pg *dev = &devices[unit];
		अगर (dev->present)
			pi_release(dev->pi);
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
module_init(pg_init)
module_निकास(pg_निकास)
