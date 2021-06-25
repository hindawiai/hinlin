<शैली गुरु>
/******************************************************************************
 * mcelog.c
 * Driver क्रम receiving and transferring machine check error infomation
 *
 * Copyright (c) 2012 Intel Corporation
 * Author: Liu, Jinsong <jinsong.liu@पूर्णांकel.com>
 * Author: Jiang, Yunhong <yunhong.jiang@पूर्णांकel.com>
 * Author: Ke, Liping <liping.ke@पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen_mcelog: " fmt

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/capability.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

अटल काष्ठा mc_info g_mi;
अटल काष्ठा mcinfo_logical_cpu *g_physinfo;
अटल uपूर्णांक32_t ncpus;

अटल DEFINE_MUTEX(mcelog_lock);

अटल काष्ठा xen_mce_log xen_mcelog = अणु
	.signature	= XEN_MCE_LOG_SIGNATURE,
	.len		= XEN_MCE_LOG_LEN,
	.recordlen	= माप(काष्ठा xen_mce),
पूर्ण;

अटल DEFINE_SPINLOCK(xen_mce_chrdev_state_lock);
अटल पूर्णांक xen_mce_chrdev_खोलो_count;	/* #बार खोलोed */
अटल पूर्णांक xen_mce_chrdev_खोलो_exclu;	/* alपढ़ोy खोलो exclusive? */

अटल DECLARE_WAIT_QUEUE_HEAD(xen_mce_chrdev_रुको);

अटल पूर्णांक xen_mce_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&xen_mce_chrdev_state_lock);

	अगर (xen_mce_chrdev_खोलो_exclu ||
	    (xen_mce_chrdev_खोलो_count && (file->f_flags & O_EXCL))) अणु
		spin_unlock(&xen_mce_chrdev_state_lock);

		वापस -EBUSY;
	पूर्ण

	अगर (file->f_flags & O_EXCL)
		xen_mce_chrdev_खोलो_exclu = 1;
	xen_mce_chrdev_खोलो_count++;

	spin_unlock(&xen_mce_chrdev_state_lock);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक xen_mce_chrdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&xen_mce_chrdev_state_lock);

	xen_mce_chrdev_खोलो_count--;
	xen_mce_chrdev_खोलो_exclu = 0;

	spin_unlock(&xen_mce_chrdev_state_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार xen_mce_chrdev_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार usize, loff_t *off)
अणु
	अक्षर __user *buf = ubuf;
	अचिन्हित num;
	पूर्णांक i, err;

	mutex_lock(&mcelog_lock);

	num = xen_mcelog.next;

	/* Only supports full पढ़ोs right now */
	err = -EINVAL;
	अगर (*off != 0 || usize < XEN_MCE_LOG_LEN*माप(काष्ठा xen_mce))
		जाओ out;

	err = 0;
	क्रम (i = 0; i < num; i++) अणु
		काष्ठा xen_mce *m = &xen_mcelog.entry[i];

		err |= copy_to_user(buf, m, माप(*m));
		buf += माप(*m);
	पूर्ण

	स_रखो(xen_mcelog.entry, 0, num * माप(काष्ठा xen_mce));
	xen_mcelog.next = 0;

	अगर (err)
		err = -EFAULT;

out:
	mutex_unlock(&mcelog_lock);

	वापस err ? err : buf - ubuf;
पूर्ण

अटल __poll_t xen_mce_chrdev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &xen_mce_chrdev_रुको, रुको);

	अगर (xen_mcelog.next)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल दीर्घ xen_mce_chrdev_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	पूर्णांक __user *p = (पूर्णांक __user *)arg;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल MCE_GET_RECORD_LEN:
		वापस put_user(माप(काष्ठा xen_mce), p);
	हाल MCE_GET_LOG_LEN:
		वापस put_user(XEN_MCE_LOG_LEN, p);
	हाल MCE_GETCLEAR_FLAGS: अणु
		अचिन्हित flags;

		करो अणु
			flags = xen_mcelog.flags;
		पूर्ण जबतक (cmpxchg(&xen_mcelog.flags, flags, 0) != flags);

		वापस put_user(flags, p);
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations xen_mce_chrdev_ops = अणु
	.खोलो			= xen_mce_chrdev_खोलो,
	.release		= xen_mce_chrdev_release,
	.पढ़ो			= xen_mce_chrdev_पढ़ो,
	.poll			= xen_mce_chrdev_poll,
	.unlocked_ioctl		= xen_mce_chrdev_ioctl,
	.llseek			= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice xen_mce_chrdev_device = अणु
	MISC_MCELOG_MINOR,
	"mcelog",
	&xen_mce_chrdev_ops,
पूर्ण;

/*
 * Caller should hold the mcelog_lock
 */
अटल व्योम xen_mce_log(काष्ठा xen_mce *mce)
अणु
	अचिन्हित entry;

	entry = xen_mcelog.next;

	/*
	 * When the buffer fills up discard new entries.
	 * Assume that the earlier errors are the more
	 * पूर्णांकeresting ones:
	 */
	अगर (entry >= XEN_MCE_LOG_LEN) अणु
		set_bit(XEN_MCE_OVERFLOW,
			(अचिन्हित दीर्घ *)&xen_mcelog.flags);
		वापस;
	पूर्ण

	स_नकल(xen_mcelog.entry + entry, mce, माप(काष्ठा xen_mce));

	xen_mcelog.next++;
पूर्ण

अटल पूर्णांक convert_log(काष्ठा mc_info *mi)
अणु
	काष्ठा mcinfo_common *mic;
	काष्ठा mcinfo_global *mc_global;
	काष्ठा mcinfo_bank *mc_bank;
	काष्ठा xen_mce m;
	अचिन्हित पूर्णांक i, j;

	mic = शून्य;
	x86_mcinfo_lookup(&mic, mi, MC_TYPE_GLOBAL);
	अगर (unlikely(!mic)) अणु
		pr_warn("Failed to find global error info\n");
		वापस -ENODEV;
	पूर्ण

	स_रखो(&m, 0, माप(काष्ठा xen_mce));

	mc_global = (काष्ठा mcinfo_global *)mic;
	m.mcgstatus = mc_global->mc_gstatus;
	m.apicid = mc_global->mc_apicid;

	क्रम (i = 0; i < ncpus; i++)
		अगर (g_physinfo[i].mc_apicid == m.apicid)
			अवरोध;
	अगर (unlikely(i == ncpus)) अणु
		pr_warn("Failed to match cpu with apicid %d\n", m.apicid);
		वापस -ENODEV;
	पूर्ण

	m.socketid = g_physinfo[i].mc_chipid;
	m.cpu = m.extcpu = g_physinfo[i].mc_cpunr;
	m.cpuvenकरोr = (__u8)g_physinfo[i].mc_venकरोr;
	क्रम (j = 0; j < g_physinfo[i].mc_nmsrvals; ++j)
		चयन (g_physinfo[i].mc_msrvalues[j].reg) अणु
		हाल MSR_IA32_MCG_CAP:
			m.mcgcap = g_physinfo[i].mc_msrvalues[j].value;
			अवरोध;

		हाल MSR_PPIN:
		हाल MSR_AMD_PPIN:
			m.ppin = g_physinfo[i].mc_msrvalues[j].value;
			अवरोध;
		पूर्ण

	mic = शून्य;
	x86_mcinfo_lookup(&mic, mi, MC_TYPE_BANK);
	अगर (unlikely(!mic)) अणु
		pr_warn("Fail to find bank error info\n");
		वापस -ENODEV;
	पूर्ण

	करो अणु
		अगर ((!mic) || (mic->size == 0) ||
		    (mic->type != MC_TYPE_GLOBAL   &&
		     mic->type != MC_TYPE_BANK     &&
		     mic->type != MC_TYPE_EXTENDED &&
		     mic->type != MC_TYPE_RECOVERY))
			अवरोध;

		अगर (mic->type == MC_TYPE_BANK) अणु
			mc_bank = (काष्ठा mcinfo_bank *)mic;
			m.misc = mc_bank->mc_misc;
			m.status = mc_bank->mc_status;
			m.addr = mc_bank->mc_addr;
			m.tsc = mc_bank->mc_tsc;
			m.bank = mc_bank->mc_bank;
			m.finished = 1;
			/*log this record*/
			xen_mce_log(&m);
		पूर्ण
		mic = x86_mcinfo_next(mic);
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक mc_queue_handle(uपूर्णांक32_t flags)
अणु
	काष्ठा xen_mc mc_op;
	पूर्णांक ret = 0;

	mc_op.cmd = XEN_MC_fetch;
	set_xen_guest_handle(mc_op.u.mc_fetch.data, &g_mi);
	करो अणु
		mc_op.u.mc_fetch.flags = flags;
		ret = HYPERVISOR_mca(&mc_op);
		अगर (ret) अणु
			pr_err("Failed to fetch %surgent error log\n",
			       flags == XEN_MC_URGENT ? "" : "non");
			अवरोध;
		पूर्ण

		अगर (mc_op.u.mc_fetch.flags & XEN_MC_NODATA ||
		    mc_op.u.mc_fetch.flags & XEN_MC_FETCHFAILED)
			अवरोध;
		अन्यथा अणु
			ret = convert_log(&g_mi);
			अगर (ret)
				pr_warn("Failed to convert this error log, continue acking it anyway\n");

			mc_op.u.mc_fetch.flags = flags | XEN_MC_ACK;
			ret = HYPERVISOR_mca(&mc_op);
			अगर (ret) अणु
				pr_err("Failed to ack previous error log\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (1);

	वापस ret;
पूर्ण

/* virq handler क्रम machine check error info*/
अटल व्योम xen_mce_work_fn(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;

	mutex_lock(&mcelog_lock);

	/* urgent mc_info */
	err = mc_queue_handle(XEN_MC_URGENT);
	अगर (err)
		pr_err("Failed to handle urgent mc_info queue, continue handling nonurgent mc_info queue anyway\n");

	/* nonurgent mc_info */
	err = mc_queue_handle(XEN_MC_NONURGENT);
	अगर (err)
		pr_err("Failed to handle nonurgent mc_info queue\n");

	/* wake processes polling /dev/mcelog */
	wake_up_पूर्णांकerruptible(&xen_mce_chrdev_रुको);

	mutex_unlock(&mcelog_lock);
पूर्ण
अटल DECLARE_WORK(xen_mce_work, xen_mce_work_fn);

अटल irqवापस_t xen_mce_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	schedule_work(&xen_mce_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bind_virq_क्रम_mce(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा xen_mc mc_op;

	स_रखो(&mc_op, 0, माप(काष्ठा xen_mc));

	/* Fetch physical CPU Numbers */
	mc_op.cmd = XEN_MC_physcpuinfo;
	set_xen_guest_handle(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	ret = HYPERVISOR_mca(&mc_op);
	अगर (ret) अणु
		pr_err("Failed to get CPU numbers\n");
		वापस ret;
	पूर्ण

	/* Fetch each CPU Physical Info क्रम later reference*/
	ncpus = mc_op.u.mc_physcpuinfo.ncpus;
	g_physinfo = kसुस्मृति(ncpus, माप(काष्ठा mcinfo_logical_cpu),
			     GFP_KERNEL);
	अगर (!g_physinfo)
		वापस -ENOMEM;
	set_xen_guest_handle(mc_op.u.mc_physcpuinfo.info, g_physinfo);
	ret = HYPERVISOR_mca(&mc_op);
	अगर (ret) अणु
		pr_err("Failed to get CPU info\n");
		kमुक्त(g_physinfo);
		वापस ret;
	पूर्ण

	ret  = bind_virq_to_irqhandler(VIRQ_MCA, 0,
				       xen_mce_पूर्णांकerrupt, 0, "mce", शून्य);
	अगर (ret < 0) अणु
		pr_err("Failed to bind virq\n");
		kमुक्त(g_physinfo);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init xen_late_init_mcelog(व्योम)
अणु
	पूर्णांक ret;

	/* Only DOM0 is responsible क्रम MCE logging */
	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	/* रेजिस्टर अक्षरacter device /dev/mcelog क्रम xen mcelog */
	ret = misc_रेजिस्टर(&xen_mce_chrdev_device);
	अगर (ret)
		वापस ret;

	ret = bind_virq_क्रम_mce();
	अगर (ret)
		जाओ deरेजिस्टर;

	pr_info("/dev/mcelog registered by Xen\n");

	वापस 0;

deरेजिस्टर:
	misc_deरेजिस्टर(&xen_mce_chrdev_device);
	वापस ret;
पूर्ण
device_initcall(xen_late_init_mcelog);
