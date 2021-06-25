<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2000-2008 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * x86 CPUID access device
 *
 * This device is accessed by lseek() to the appropriate CPUID level
 * and then पढ़ो in chunks of 16 bytes.  A larger size means multiple
 * पढ़ोs of consecutive levels.
 *
 * The lower 32 bits of the file position is used as the incoming %eax,
 * and the upper 32 bits of the file position as the incoming %ecx,
 * the latter पूर्णांकended क्रम "counting" eax levels like eax=4.
 *
 * This driver uses /dev/cpu/%d/cpuid where %d is the minor number, and on
 * an SMP box will direct the access to CPU %d.
 */

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
#समावेश <linux/completion.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/msr.h>

अटल काष्ठा class *cpuid_class;
अटल क्रमागत cpuhp_state cpuhp_cpuid_state;

काष्ठा cpuid_regs_करोne अणु
	काष्ठा cpuid_regs regs;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम cpuid_smp_cpuid(व्योम *cmd_block)
अणु
	काष्ठा cpuid_regs_करोne *cmd = cmd_block;

	cpuid_count(cmd->regs.eax, cmd->regs.ecx,
		    &cmd->regs.eax, &cmd->regs.ebx,
		    &cmd->regs.ecx, &cmd->regs.edx);

	complete(&cmd->करोne);
पूर्ण

अटल sमाप_प्रकार cpuid_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर __user *पंचांगp = buf;
	काष्ठा cpuid_regs_करोne cmd;
	पूर्णांक cpu = iminor(file_inode(file));
	u64 pos = *ppos;
	sमाप_प्रकार bytes = 0;
	पूर्णांक err = 0;

	अगर (count % 16)
		वापस -EINVAL;	/* Invalid chunk size */

	init_completion(&cmd.करोne);
	क्रम (; count; count -= 16) अणु
		call_single_data_t csd;

		INIT_CSD(&csd, cpuid_smp_cpuid, &cmd);

		cmd.regs.eax = pos;
		cmd.regs.ecx = pos >> 32;

		err = smp_call_function_single_async(cpu, &csd);
		अगर (err)
			अवरोध;
		रुको_क्रम_completion(&cmd.करोne);
		अगर (copy_to_user(पंचांगp, &cmd.regs, 16)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		पंचांगp += 16;
		bytes += 16;
		*ppos = ++pos;
		reinit_completion(&cmd.करोne);
	पूर्ण

	वापस bytes ? bytes : err;
पूर्ण

अटल पूर्णांक cpuid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा cpuinfo_x86 *c;

	cpu = iminor(file_inode(file));
	अगर (cpu >= nr_cpu_ids || !cpu_online(cpu))
		वापस -ENXIO;	/* No such CPU */

	c = &cpu_data(cpu);
	अगर (c->cpuid_level < 0)
		वापस -EIO;	/* CPUID not supported */

	वापस 0;
पूर्ण

/*
 * File operations we support
 */
अटल स्थिर काष्ठा file_operations cpuid_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_seek_end_llseek,
	.पढ़ो = cpuid_पढ़ो,
	.खोलो = cpuid_खोलो,
पूर्ण;

अटल पूर्णांक cpuid_device_create(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev;

	dev = device_create(cpuid_class, शून्य, MKDEV(CPUID_MAJOR, cpu), शून्य,
			    "cpu%d", cpu);
	वापस PTR_ERR_OR_ZERO(dev);
पूर्ण

अटल पूर्णांक cpuid_device_destroy(अचिन्हित पूर्णांक cpu)
अणु
	device_destroy(cpuid_class, MKDEV(CPUID_MAJOR, cpu));
	वापस 0;
पूर्ण

अटल अक्षर *cpuid_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "cpu/%u/cpuid", MINOR(dev->devt));
पूर्ण

अटल पूर्णांक __init cpuid_init(व्योम)
अणु
	पूर्णांक err;

	अगर (__रेजिस्टर_chrdev(CPUID_MAJOR, 0, NR_CPUS,
			      "cpu/cpuid", &cpuid_fops)) अणु
		prपूर्णांकk(KERN_ERR "cpuid: unable to get major %d for cpuid\n",
		       CPUID_MAJOR);
		वापस -EBUSY;
	पूर्ण
	cpuid_class = class_create(THIS_MODULE, "cpuid");
	अगर (IS_ERR(cpuid_class)) अणु
		err = PTR_ERR(cpuid_class);
		जाओ out_chrdev;
	पूर्ण
	cpuid_class->devnode = cpuid_devnode;

	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "x86/cpuid:online",
				cpuid_device_create, cpuid_device_destroy);
	अगर (err < 0)
		जाओ out_class;

	cpuhp_cpuid_state = err;
	वापस 0;

out_class:
	class_destroy(cpuid_class);
out_chrdev:
	__unरेजिस्टर_chrdev(CPUID_MAJOR, 0, NR_CPUS, "cpu/cpuid");
	वापस err;
पूर्ण
module_init(cpuid_init);

अटल व्योम __निकास cpuid_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(cpuhp_cpuid_state);
	class_destroy(cpuid_class);
	__unरेजिस्टर_chrdev(CPUID_MAJOR, 0, NR_CPUS, "cpu/cpuid");
पूर्ण
module_निकास(cpuid_निकास);

MODULE_AUTHOR("H. Peter Anvin <hpa@zytor.com>");
MODULE_DESCRIPTION("x86 generic CPUID driver");
MODULE_LICENSE("GPL");
