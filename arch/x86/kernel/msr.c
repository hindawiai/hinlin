<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2000-2008 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * x86 MSR access device
 *
 * This device is accessed by lseek() to the appropriate रेजिस्टर number
 * and then पढ़ो/ग_लिखो in chunks of 8 bytes.  A larger size means multiple
 * पढ़ोs or ग_लिखोs of the same रेजिस्टर.
 *
 * This driver uses /dev/cpu/%d/msr where %d is the minor number, and on
 * an SMP box will direct the access to CPU %d.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/smp.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/gfp.h>
#समावेश <linux/security.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/msr.h>

अटल काष्ठा class *msr_class;
अटल क्रमागत cpuhp_state cpuhp_msr_state;

क्रमागत allow_ग_लिखो_msrs अणु
	MSR_WRITES_ON,
	MSR_WRITES_OFF,
	MSR_WRITES_DEFAULT,
पूर्ण;

अटल क्रमागत allow_ग_लिखो_msrs allow_ग_लिखोs = MSR_WRITES_DEFAULT;

अटल sमाप_प्रकार msr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	u32 __user *पंचांगp = (u32 __user *) buf;
	u32 data[2];
	u32 reg = *ppos;
	पूर्णांक cpu = iminor(file_inode(file));
	पूर्णांक err = 0;
	sमाप_प्रकार bytes = 0;

	अगर (count % 8)
		वापस -EINVAL;	/* Invalid chunk size */

	क्रम (; count; count -= 8) अणु
		err = rdmsr_safe_on_cpu(cpu, reg, &data[0], &data[1]);
		अगर (err)
			अवरोध;
		अगर (copy_to_user(पंचांगp, &data, 8)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		पंचांगp += 2;
		bytes += 8;
	पूर्ण

	वापस bytes ? bytes : err;
पूर्ण

अटल पूर्णांक filter_ग_लिखो(u32 reg)
अणु
	/*
	 * MSRs ग_लिखोs usually happen all at once, and can easily saturate kmsg.
	 * Only allow one message every 30 seconds.
	 *
	 * It's possible to be smarter here and करो it (क्रम example) per-MSR, but
	 * it would certainly be more complex, and this is enough at least to
	 * aव्योम saturating the ring buffer.
	 */
	अटल DEFINE_RATELIMIT_STATE(fw_rs, 30 * HZ, 1);

	चयन (allow_ग_लिखोs) अणु
	हाल MSR_WRITES_ON:  वापस 0;
	हाल MSR_WRITES_OFF: वापस -EPERM;
	शेष: अवरोध;
	पूर्ण

	अगर (!__ratelimit(&fw_rs))
		वापस 0;

	pr_warn("Write to unrecognized MSR 0x%x by %s (pid: %d).\n",
	        reg, current->comm, current->pid);
	pr_warn("See https://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git/about for details.\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार msr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर u32 __user *पंचांगp = (स्थिर u32 __user *)buf;
	u32 data[2];
	u32 reg = *ppos;
	पूर्णांक cpu = iminor(file_inode(file));
	पूर्णांक err = 0;
	sमाप_प्रकार bytes = 0;

	err = security_locked_करोwn(LOCKDOWN_MSR);
	अगर (err)
		वापस err;

	err = filter_ग_लिखो(reg);
	अगर (err)
		वापस err;

	अगर (count % 8)
		वापस -EINVAL;	/* Invalid chunk size */

	क्रम (; count; count -= 8) अणु
		अगर (copy_from_user(&data, पंचांगp, 8)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);

		err = wrmsr_safe_on_cpu(cpu, reg, data[0], data[1]);
		अगर (err)
			अवरोध;

		पंचांगp += 2;
		bytes += 8;
	पूर्ण

	वापस bytes ? bytes : err;
पूर्ण

अटल दीर्घ msr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ioc, अचिन्हित दीर्घ arg)
अणु
	u32 __user *uregs = (u32 __user *)arg;
	u32 regs[8];
	पूर्णांक cpu = iminor(file_inode(file));
	पूर्णांक err;

	चयन (ioc) अणु
	हाल X86_IOC_RDMSR_REGS:
		अगर (!(file->f_mode & FMODE_READ)) अणु
			err = -EBADF;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&regs, uregs, माप(regs))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = rdmsr_safe_regs_on_cpu(cpu, regs);
		अगर (err)
			अवरोध;
		अगर (copy_to_user(uregs, &regs, माप(regs)))
			err = -EFAULT;
		अवरोध;

	हाल X86_IOC_WRMSR_REGS:
		अगर (!(file->f_mode & FMODE_WRITE)) अणु
			err = -EBADF;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&regs, uregs, माप(regs))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = security_locked_करोwn(LOCKDOWN_MSR);
		अगर (err)
			अवरोध;

		err = filter_ग_लिखो(regs[1]);
		अगर (err)
			वापस err;

		add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);

		err = wrmsr_safe_regs_on_cpu(cpu, regs);
		अगर (err)
			अवरोध;
		अगर (copy_to_user(uregs, &regs, माप(regs)))
			err = -EFAULT;
		अवरोध;

	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक msr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक cpu = iminor(file_inode(file));
	काष्ठा cpuinfo_x86 *c;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	अगर (cpu >= nr_cpu_ids || !cpu_online(cpu))
		वापस -ENXIO;	/* No such CPU */

	c = &cpu_data(cpu);
	अगर (!cpu_has(c, X86_FEATURE_MSR))
		वापस -EIO;	/* MSR not supported */

	वापस 0;
पूर्ण

/*
 * File operations we support
 */
अटल स्थिर काष्ठा file_operations msr_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_seek_end_llseek,
	.पढ़ो = msr_पढ़ो,
	.ग_लिखो = msr_ग_लिखो,
	.खोलो = msr_खोलो,
	.unlocked_ioctl = msr_ioctl,
	.compat_ioctl = msr_ioctl,
पूर्ण;

अटल पूर्णांक msr_device_create(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev;

	dev = device_create(msr_class, शून्य, MKDEV(MSR_MAJOR, cpu), शून्य,
			    "msr%d", cpu);
	वापस PTR_ERR_OR_ZERO(dev);
पूर्ण

अटल पूर्णांक msr_device_destroy(अचिन्हित पूर्णांक cpu)
अणु
	device_destroy(msr_class, MKDEV(MSR_MAJOR, cpu));
	वापस 0;
पूर्ण

अटल अक्षर *msr_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "cpu/%u/msr", MINOR(dev->devt));
पूर्ण

अटल पूर्णांक __init msr_init(व्योम)
अणु
	पूर्णांक err;

	अगर (__रेजिस्टर_chrdev(MSR_MAJOR, 0, NR_CPUS, "cpu/msr", &msr_fops)) अणु
		pr_err("unable to get major %d for msr\n", MSR_MAJOR);
		वापस -EBUSY;
	पूर्ण
	msr_class = class_create(THIS_MODULE, "msr");
	अगर (IS_ERR(msr_class)) अणु
		err = PTR_ERR(msr_class);
		जाओ out_chrdev;
	पूर्ण
	msr_class->devnode = msr_devnode;

	err  = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "x86/msr:online",
				 msr_device_create, msr_device_destroy);
	अगर (err < 0)
		जाओ out_class;
	cpuhp_msr_state = err;
	वापस 0;

out_class:
	class_destroy(msr_class);
out_chrdev:
	__unरेजिस्टर_chrdev(MSR_MAJOR, 0, NR_CPUS, "cpu/msr");
	वापस err;
पूर्ण
module_init(msr_init);

अटल व्योम __निकास msr_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(cpuhp_msr_state);
	class_destroy(msr_class);
	__unरेजिस्टर_chrdev(MSR_MAJOR, 0, NR_CPUS, "cpu/msr");
पूर्ण
module_निकास(msr_निकास)

अटल पूर्णांक set_allow_ग_लिखोs(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *cp)
अणु
	/* val is NUL-terminated, see kernfs_fop_ग_लिखो() */
	अक्षर *s = म_मालाip((अक्षर *)val);

	अगर (!म_भेद(s, "on"))
		allow_ग_लिखोs = MSR_WRITES_ON;
	अन्यथा अगर (!म_भेद(s, "off"))
		allow_ग_लिखोs = MSR_WRITES_OFF;
	अन्यथा
		allow_ग_लिखोs = MSR_WRITES_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_allow_ग_लिखोs(अक्षर *buf, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर अक्षर *res;

	चयन (allow_ग_लिखोs) अणु
	हाल MSR_WRITES_ON:  res = "on"; अवरोध;
	हाल MSR_WRITES_OFF: res = "off"; अवरोध;
	शेष: res = "default"; अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", res);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops allow_ग_लिखोs_ops = अणु
	.set = set_allow_ग_लिखोs,
	.get = get_allow_ग_लिखोs
पूर्ण;

module_param_cb(allow_ग_लिखोs, &allow_ग_लिखोs_ops, शून्य, 0600);

MODULE_AUTHOR("H. Peter Anvin <hpa@zytor.com>");
MODULE_DESCRIPTION("x86 generic MSR driver");
MODULE_LICENSE("GPL");
