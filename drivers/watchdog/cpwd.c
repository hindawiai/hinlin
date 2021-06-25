<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* cpwd.c - driver implementation क्रम hardware watchकरोg
 * समयrs found on Sun Microप्रणालीs CP1400 and CP1500 boards.
 *
 * This device supports both the generic Linux watchकरोg
 * पूर्णांकerface and Solaris-compatible ioctls as best it is
 * able.
 *
 * NOTE:	CP1400 प्रणालीs appear to have a defective पूर्णांकr_mask
 *			रेजिस्टर on the PLD, preventing the disabling of
 *			समयr पूर्णांकerrupts.  We use a समयr to periodically
 *			reset 'stopped' watchकरोgs on affected platक्रमms.
 *
 * Copyright (c) 2000 Eric Brower (ebrower@usa.net)
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/major.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/watchकरोg.h>

#घोषणा DRIVER_NAME	"cpwd"

#घोषणा WD_OBPNAME	"watchdog"
#घोषणा WD_BADMODEL	"SUNW,501-5336"
#घोषणा WD_BTIMEOUT	(jअगरfies + (HZ * 1000))
#घोषणा WD_BLIMIT	0xFFFF

#घोषणा WD0_MINOR	212
#घोषणा WD1_MINOR	213
#घोषणा WD2_MINOR	214

/* Internal driver definitions.  */
#घोषणा WD0_ID			0
#घोषणा WD1_ID			1
#घोषणा WD2_ID			2
#घोषणा WD_NUMDEVS		3

#घोषणा WD_INTR_OFF		0
#घोषणा WD_INTR_ON		1

#घोषणा WD_STAT_INIT	0x01	/* Watchकरोg समयr is initialized	*/
#घोषणा WD_STAT_BSTOP	0x02	/* Watchकरोg समयr is brokenstopped	*/
#घोषणा WD_STAT_SVCD	0x04	/* Watchकरोg पूर्णांकerrupt occurred		*/

/* Register value definitions
 */
#घोषणा WD0_INTR_MASK	0x01	/* Watchकरोg device पूर्णांकerrupt masks	*/
#घोषणा WD1_INTR_MASK	0x02
#घोषणा WD2_INTR_MASK	0x04

#घोषणा WD_S_RUNNING	0x01	/* Watchकरोg device status running	*/
#घोषणा WD_S_EXPIRED	0x02	/* Watchकरोg device status expired	*/

काष्ठा cpwd अणु
	व्योम __iomem	*regs;
	spinlock_t	lock;

	अचिन्हित पूर्णांक	irq;

	अचिन्हित दीर्घ	समयout;
	bool		enabled;
	bool		reboot;
	bool		broken;
	bool		initialized;

	काष्ठा अणु
		काष्ठा miscdevice	misc;
		व्योम __iomem		*regs;
		u8			पूर्णांकr_mask;
		u8			runstatus;
		u16			समयout;
	पूर्ण devs[WD_NUMDEVS];
पूर्ण;

अटल DEFINE_MUTEX(cpwd_mutex);
अटल काष्ठा cpwd *cpwd_device;

/* Sun uses Altera PLD EPF8820ATC144-4
 * providing three hardware watchकरोgs:
 *
 * 1) RIC - sends an पूर्णांकerrupt when triggered
 * 2) XIR - निश्चितs XIR_B_RESET when triggered, resets CPU
 * 3) POR - निश्चितs POR_B_RESET when triggered, resets CPU, backplane, board
 *
 *** Timer रेजिस्टर block definition (काष्ठा wd_समयr_regblk)
 *
 * dcntr and limit रेजिस्टरs (halfword access):
 * -------------------
 * | 15 | ...| 1 | 0 |
 * -------------------
 * |-  counter val  -|
 * -------------------
 * dcntr -	Current 16-bit करोwncounter value.
 *			When करोwncounter reaches '0' watchकरोg expires.
 *			Reading this रेजिस्टर resets करोwncounter with
 *			'limit' value.
 * limit -	16-bit countकरोwn value in 1/10th second increments.
 *			Writing this रेजिस्टर begins countकरोwn with input value.
 *			Reading from this रेजिस्टर करोes not affect counter.
 * NOTES:	After watchकरोg reset, dcntr and limit contain '1'
 *
 * status रेजिस्टर (byte access):
 * ---------------------------
 * | 7 | ... | 2 |  1  |  0  |
 * --------------+------------
 * |-   UNUSED  -| EXP | RUN |
 * ---------------------------
 * status-	Bit 0 - Watchकरोg is running
 *			Bit 1 - Watchकरोg has expired
 *
 *** PLD रेजिस्टर block definition (काष्ठा wd_pld_regblk)
 *
 * पूर्णांकr_mask रेजिस्टर (byte access):
 * ---------------------------------
 * | 7 | ... | 3 |  2  |  1  |  0  |
 * +-------------+------------------
 * |-   UNUSED  -| WD3 | WD2 | WD1 |
 * ---------------------------------
 * WD3 -  1 == Interrupt disabled क्रम watchकरोg 3
 * WD2 -  1 == Interrupt disabled क्रम watchकरोg 2
 * WD1 -  1 == Interrupt disabled क्रम watchकरोg 1
 *
 * pld_status रेजिस्टर (byte access):
 * UNKNOWN, MAGICAL MYSTERY REGISTER
 *
 */
#घोषणा WD_TIMER_REGSZ	16
#घोषणा WD0_OFF		0
#घोषणा WD1_OFF		(WD_TIMER_REGSZ * 1)
#घोषणा WD2_OFF		(WD_TIMER_REGSZ * 2)
#घोषणा PLD_OFF		(WD_TIMER_REGSZ * 3)

#घोषणा WD_DCNTR	0x00
#घोषणा WD_LIMIT	0x04
#घोषणा WD_STATUS	0x08

#घोषणा PLD_IMASK	(PLD_OFF + 0x00)
#घोषणा PLD_STATUS	(PLD_OFF + 0x04)

अटल काष्ठा समयr_list cpwd_समयr;

अटल पूर्णांक wd0_समयout;
अटल पूर्णांक wd1_समयout;
अटल पूर्णांक wd2_समयout;

module_param(wd0_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(wd0_समयout, "Default watchdog0 timeout in 1/10secs");
module_param(wd1_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(wd1_समयout, "Default watchdog1 timeout in 1/10secs");
module_param(wd2_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(wd2_समयout, "Default watchdog2 timeout in 1/10secs");

MODULE_AUTHOR("Eric Brower <ebrower@usa.net>");
MODULE_DESCRIPTION("Hardware watchdog driver for Sun Microsystems CP1400/1500");
MODULE_LICENSE("GPL");

अटल व्योम cpwd_ग_लिखोw(u16 val, व्योम __iomem *addr)
अणु
	ग_लिखोw(cpu_to_le16(val), addr);
पूर्ण
अटल u16 cpwd_पढ़ोw(व्योम __iomem *addr)
अणु
	u16 val = पढ़ोw(addr);

	वापस le16_to_cpu(val);
पूर्ण

अटल व्योम cpwd_ग_लिखोb(u8 val, व्योम __iomem *addr)
अणु
	ग_लिखोb(val, addr);
पूर्ण

अटल u8 cpwd_पढ़ोb(व्योम __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण

/* Enable or disable watchकरोg पूर्णांकerrupts
 * Because of the CP1400 defect this should only be
 * called during initialzation or by wd_[start|stop]समयr()
 *
 * index	- sub-device index, or -1 क्रम 'all'
 * enable	- non-zero to enable पूर्णांकerrupts, zero to disable
 */
अटल व्योम cpwd_toggleपूर्णांकr(काष्ठा cpwd *p, पूर्णांक index, पूर्णांक enable)
अणु
	अचिन्हित अक्षर curregs = cpwd_पढ़ोb(p->regs + PLD_IMASK);
	अचिन्हित अक्षर setregs =
		(index == -1) ?
		(WD0_INTR_MASK | WD1_INTR_MASK | WD2_INTR_MASK) :
		(p->devs[index].पूर्णांकr_mask);

	अगर (enable == WD_INTR_ON)
		curregs &= ~setregs;
	अन्यथा
		curregs |= setregs;

	cpwd_ग_लिखोb(curregs, p->regs + PLD_IMASK);
पूर्ण

/* Restarts समयr with maximum limit value and
 * करोes not unset 'brokenstop' value.
 */
अटल व्योम cpwd_resetbrokenसमयr(काष्ठा cpwd *p, पूर्णांक index)
अणु
	cpwd_toggleपूर्णांकr(p, index, WD_INTR_ON);
	cpwd_ग_लिखोw(WD_BLIMIT, p->devs[index].regs + WD_LIMIT);
पूर्ण

/* Timer method called to reset stopped watchकरोgs--
 * because of the PLD bug on CP1400, we cannot mask
 * पूर्णांकerrupts within the PLD so me must continually
 * reset the समयrs ad infinitum.
 */
अटल व्योम cpwd_brokenसमयr(काष्ठा समयr_list *unused)
अणु
	काष्ठा cpwd *p = cpwd_device;
	पूर्णांक id, tripped = 0;

	/* समाप्त a running समयr instance, in हाल we
	 * were called directly instead of by kernel समयr
	 */
	अगर (समयr_pending(&cpwd_समयr))
		del_समयr(&cpwd_समयr);

	क्रम (id = 0; id < WD_NUMDEVS; id++) अणु
		अगर (p->devs[id].runstatus & WD_STAT_BSTOP) अणु
			++tripped;
			cpwd_resetbrokenसमयr(p, id);
		पूर्ण
	पूर्ण

	अगर (tripped) अणु
		/* there is at least one समयr brokenstopped-- reschedule */
		cpwd_समयr.expires = WD_BTIMEOUT;
		add_समयr(&cpwd_समयr);
	पूर्ण
पूर्ण

/* Reset countकरोwn समयr with 'limit' value and जारी countकरोwn.
 * This will not start a stopped समयr.
 */
अटल व्योम cpwd_pingसमयr(काष्ठा cpwd *p, पूर्णांक index)
अणु
	अगर (cpwd_पढ़ोb(p->devs[index].regs + WD_STATUS) & WD_S_RUNNING)
		cpwd_पढ़ोw(p->devs[index].regs + WD_DCNTR);
पूर्ण

/* Stop a running watchकरोg समयr-- the समयr actually keeps
 * running, but the पूर्णांकerrupt is masked so that no action is
 * taken upon expiration.
 */
अटल व्योम cpwd_stopसमयr(काष्ठा cpwd *p, पूर्णांक index)
अणु
	अगर (cpwd_पढ़ोb(p->devs[index].regs + WD_STATUS) & WD_S_RUNNING) अणु
		cpwd_toggleपूर्णांकr(p, index, WD_INTR_OFF);

		अगर (p->broken) अणु
			p->devs[index].runstatus |= WD_STAT_BSTOP;
			cpwd_brokenसमयr(शून्य);
		पूर्ण
	पूर्ण
पूर्ण

/* Start a watchकरोg समयr with the specअगरied limit value
 * If the watchकरोg is running, it will be restarted with
 * the provided limit value.
 *
 * This function will enable पूर्णांकerrupts on the specअगरied
 * watchकरोg.
 */
अटल व्योम cpwd_startसमयr(काष्ठा cpwd *p, पूर्णांक index)
अणु
	अगर (p->broken)
		p->devs[index].runstatus &= ~WD_STAT_BSTOP;

	p->devs[index].runstatus &= ~WD_STAT_SVCD;

	cpwd_ग_लिखोw(p->devs[index].समयout, p->devs[index].regs + WD_LIMIT);
	cpwd_toggleपूर्णांकr(p, index, WD_INTR_ON);
पूर्ण

अटल पूर्णांक cpwd_माला_लोtatus(काष्ठा cpwd *p, पूर्णांक index)
अणु
	अचिन्हित अक्षर stat = cpwd_पढ़ोb(p->devs[index].regs + WD_STATUS);
	अचिन्हित अक्षर पूर्णांकr = cpwd_पढ़ोb(p->devs[index].regs + PLD_IMASK);
	अचिन्हित अक्षर ret  = WD_STOPPED;

	/* determine STOPPED */
	अगर (!stat)
		वापस ret;

	/* determine EXPIRED vs FREERUN vs RUNNING */
	अन्यथा अगर (WD_S_EXPIRED & stat) अणु
		ret = WD_EXPIRED;
	पूर्ण अन्यथा अगर (WD_S_RUNNING & stat) अणु
		अगर (पूर्णांकr & p->devs[index].पूर्णांकr_mask) अणु
			ret = WD_FREERUN;
		पूर्ण अन्यथा अणु
			/* Fudge WD_EXPIRED status क्रम defective CP1400--
			 * IF समयr is running
			 *	AND brokenstop is set
			 *	AND an पूर्णांकerrupt has been serviced
			 * we are WD_EXPIRED.
			 *
			 * IF समयr is running
			 *	AND brokenstop is set
			 *	AND no पूर्णांकerrupt has been serviced
			 * we are WD_FREERUN.
			 */
			अगर (p->broken &&
			    (p->devs[index].runstatus & WD_STAT_BSTOP)) अणु
				अगर (p->devs[index].runstatus & WD_STAT_SVCD) अणु
					ret = WD_EXPIRED;
				पूर्ण अन्यथा अणु
					/* we could as well pretend
					 * we are expired */
					ret = WD_FREERUN;
				पूर्ण
			पूर्ण अन्यथा अणु
				ret = WD_RUNNING;
			पूर्ण
		पूर्ण
	पूर्ण

	/* determine SERVICED */
	अगर (p->devs[index].runstatus & WD_STAT_SVCD)
		ret |= WD_SERVICED;

	वापस ret;
पूर्ण

अटल irqवापस_t cpwd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cpwd *p = dev_id;

	/* Only WD0 will पूर्णांकerrupt-- others are NMI and we won't
	 * see them here....
	 */
	spin_lock_irq(&p->lock);

	cpwd_stopसमयr(p, WD0_ID);
	p->devs[WD0_ID].runstatus |=  WD_STAT_SVCD;

	spin_unlock_irq(&p->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpwd_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा cpwd *p = cpwd_device;

	mutex_lock(&cpwd_mutex);
	चयन (iminor(inode)) अणु
	हाल WD0_MINOR:
	हाल WD1_MINOR:
	हाल WD2_MINOR:
		अवरोध;

	शेष:
		mutex_unlock(&cpwd_mutex);
		वापस -ENODEV;
	पूर्ण

	/* Register IRQ on first खोलो of device */
	अगर (!p->initialized) अणु
		अगर (request_irq(p->irq, &cpwd_पूर्णांकerrupt,
				IRQF_SHARED, DRIVER_NAME, p)) अणु
			pr_err("Cannot register IRQ %d\n", p->irq);
			mutex_unlock(&cpwd_mutex);
			वापस -EBUSY;
		पूर्ण
		p->initialized = true;
	पूर्ण

	mutex_unlock(&cpwd_mutex);

	वापस stream_खोलो(inode, f);
पूर्ण

अटल पूर्णांक cpwd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ cpwd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अटल स्थिर काष्ठा watchकरोg_info info = अणु
		.options		= WDIOF_SETTIMEOUT,
		.firmware_version	= 1,
		.identity		= DRIVER_NAME,
	पूर्ण;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक index = iminor(inode) - WD0_MINOR;
	काष्ठा cpwd *p = cpwd_device;
	पूर्णांक setopt = 0;

	चयन (cmd) अणु
	/* Generic Linux IOCTLs */
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &info, माप(काष्ठा watchकरोg_info)))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		अगर (put_user(0, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		cpwd_pingसमयr(p, index);
		अवरोध;

	हाल WDIOC_SETOPTIONS:
		अगर (copy_from_user(&setopt, argp, माप(अचिन्हित पूर्णांक)))
			वापस -EFAULT;

		अगर (setopt & WDIOS_DISABLECARD) अणु
			अगर (p->enabled)
				वापस -EINVAL;
			cpwd_stopसमयr(p, index);
		पूर्ण अन्यथा अगर (setopt & WDIOS_ENABLECARD) अणु
			cpwd_startसमयr(p, index);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	/* Solaris-compatible IOCTLs */
	हाल WIOCGSTAT:
		setopt = cpwd_माला_लोtatus(p, index);
		अगर (copy_to_user(argp, &setopt, माप(अचिन्हित पूर्णांक)))
			वापस -EFAULT;
		अवरोध;

	हाल WIOCSTART:
		cpwd_startसमयr(p, index);
		अवरोध;

	हाल WIOCSTOP:
		अगर (p->enabled)
			वापस -EINVAL;

		cpwd_stopसमयr(p, index);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ cpwd_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस cpwd_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण

अटल sमाप_प्रकार cpwd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा cpwd *p = cpwd_device;
	पूर्णांक index = iminor(inode);

	अगर (count) अणु
		cpwd_pingसमयr(p, index);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cpwd_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations cpwd_fops = अणु
	.owner =		THIS_MODULE,
	.unlocked_ioctl =	cpwd_ioctl,
	.compat_ioctl =		cpwd_compat_ioctl,
	.खोलो =			cpwd_खोलो,
	.ग_लिखो =		cpwd_ग_लिखो,
	.पढ़ो =			cpwd_पढ़ो,
	.release =		cpwd_release,
	.llseek =		no_llseek,
पूर्ण;

अटल पूर्णांक cpwd_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *options;
	स्थिर अक्षर *str_prop;
	स्थिर व्योम *prop_val;
	पूर्णांक i, err = -EINVAL;
	काष्ठा cpwd *p;

	अगर (cpwd_device)
		वापस -EINVAL;

	p = devm_kzalloc(&op->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->irq = op->archdata.irqs[0];

	spin_lock_init(&p->lock);

	p->regs = of_ioremap(&op->resource[0], 0,
			     4 * WD_TIMER_REGSZ, DRIVER_NAME);
	अगर (!p->regs) अणु
		pr_err("Unable to map registers\n");
		वापस -ENOMEM;
	पूर्ण

	options = of_find_node_by_path("/options");
	अगर (!options) अणु
		err = -ENODEV;
		pr_err("Unable to find /options node\n");
		जाओ out_iounmap;
	पूर्ण

	prop_val = of_get_property(options, "watchdog-enable?", शून्य);
	p->enabled = (prop_val ? true : false);

	prop_val = of_get_property(options, "watchdog-reboot?", शून्य);
	p->reboot = (prop_val ? true : false);

	str_prop = of_get_property(options, "watchdog-timeout", शून्य);
	अगर (str_prop)
		p->समयout = simple_म_से_अदीर्घ(str_prop, शून्य, 10);

	of_node_put(options);

	/* CP1400s seem to have broken PLD implementations-- the
	 * पूर्णांकerrupt_mask रेजिस्टर cannot be written, so no समयr
	 * पूर्णांकerrupts can be masked within the PLD.
	 */
	str_prop = of_get_property(op->dev.of_node, "model", शून्य);
	p->broken = (str_prop && !म_भेद(str_prop, WD_BADMODEL));

	अगर (!p->enabled)
		cpwd_toggleपूर्णांकr(p, -1, WD_INTR_OFF);

	क्रम (i = 0; i < WD_NUMDEVS; i++) अणु
		अटल स्थिर अक्षर *cpwd_names[] = अणु "RIC", "XIR", "POR" पूर्ण;
		अटल पूर्णांक *parms[] = अणु &wd0_समयout,
					&wd1_समयout,
					&wd2_समयout पूर्ण;
		काष्ठा miscdevice *mp = &p->devs[i].misc;

		mp->minor = WD0_MINOR + i;
		mp->name = cpwd_names[i];
		mp->fops = &cpwd_fops;

		p->devs[i].regs = p->regs + (i * WD_TIMER_REGSZ);
		p->devs[i].पूर्णांकr_mask = (WD0_INTR_MASK << i);
		p->devs[i].runstatus &= ~WD_STAT_BSTOP;
		p->devs[i].runstatus |= WD_STAT_INIT;
		p->devs[i].समयout = p->समयout;
		अगर (*parms[i])
			p->devs[i].समयout = *parms[i];

		err = misc_रेजिस्टर(&p->devs[i].misc);
		अगर (err) अणु
			pr_err("Could not register misc device for dev %d\n",
			       i);
			जाओ out_unरेजिस्टर;
		पूर्ण
	पूर्ण

	अगर (p->broken) अणु
		समयr_setup(&cpwd_समयr, cpwd_brokenसमयr, 0);
		cpwd_समयr.expires	= WD_BTIMEOUT;

		pr_info("PLD defect workaround enabled for model %s\n",
			WD_BADMODEL);
	पूर्ण

	platक्रमm_set_drvdata(op, p);
	cpwd_device = p;
	वापस 0;

out_unरेजिस्टर:
	क्रम (i--; i >= 0; i--)
		misc_deरेजिस्टर(&p->devs[i].misc);

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, 4 * WD_TIMER_REGSZ);

	वापस err;
पूर्ण

अटल पूर्णांक cpwd_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा cpwd *p = platक्रमm_get_drvdata(op);
	पूर्णांक i;

	क्रम (i = 0; i < WD_NUMDEVS; i++) अणु
		misc_deरेजिस्टर(&p->devs[i].misc);

		अगर (!p->enabled) अणु
			cpwd_stopसमयr(p, i);
			अगर (p->devs[i].runstatus & WD_STAT_BSTOP)
				cpwd_resetbrokenसमयr(p, i);
		पूर्ण
	पूर्ण

	अगर (p->broken)
		del_समयr_sync(&cpwd_समयr);

	अगर (p->initialized)
		मुक्त_irq(p->irq, p);

	of_iounmap(&op->resource[0], p->regs, 4 * WD_TIMER_REGSZ);

	cpwd_device = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpwd_match[] = अणु
	अणु
		.name = "watchdog",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpwd_match);

अटल काष्ठा platक्रमm_driver cpwd_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = cpwd_match,
	पूर्ण,
	.probe		= cpwd_probe,
	.हटाओ		= cpwd_हटाओ,
पूर्ण;

module_platक्रमm_driver(cpwd_driver);
