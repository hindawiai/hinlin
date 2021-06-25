<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sma cpu5 watchकरोg driver
 *
 * Copyright (C) 2003 Heiko Ronsकरोrf <hero@ihg.uni-duisburg.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>

/* adjustable parameters */

अटल पूर्णांक verbose;
अटल पूर्णांक port = 0x91;
अटल पूर्णांक ticks = 10000;
अटल DEFINE_SPINLOCK(cpu5wdt_lock);

#घोषणा PFX			"cpu5wdt: "

#घोषणा CPU5WDT_EXTENT          0x0A

#घोषणा CPU5WDT_STATUS_REG      0x00
#घोषणा CPU5WDT_TIME_A_REG      0x02
#घोषणा CPU5WDT_TIME_B_REG      0x03
#घोषणा CPU5WDT_MODE_REG        0x04
#घोषणा CPU5WDT_TRIGGER_REG     0x07
#घोषणा CPU5WDT_ENABLE_REG      0x08
#घोषणा CPU5WDT_RESET_REG       0x09

#घोषणा CPU5WDT_INTERVAL	(HZ/10+1)

/* some device data */

अटल काष्ठा अणु
	काष्ठा completion stop;
	पूर्णांक running;
	काष्ठा समयr_list समयr;
	पूर्णांक queue;
	पूर्णांक शेष_ticks;
	अचिन्हित दीर्घ inuse;
पूर्ण cpu5wdt_device;

/* generic helper functions */

अटल व्योम cpu5wdt_trigger(काष्ठा समयr_list *unused)
अणु
	अगर (verbose > 2)
		pr_debug("trigger at %i ticks\n", ticks);

	अगर (cpu5wdt_device.running)
		ticks--;

	spin_lock(&cpu5wdt_lock);
	/* keep watchकरोg alive */
	outb(1, port + CPU5WDT_TRIGGER_REG);

	/* requeue?? */
	अगर (cpu5wdt_device.queue && ticks)
		mod_समयr(&cpu5wdt_device.समयr, jअगरfies + CPU5WDT_INTERVAL);
	अन्यथा अणु
		/* ticks करोesn't matter anyway */
		complete(&cpu5wdt_device.stop);
	पूर्ण
	spin_unlock(&cpu5wdt_lock);

पूर्ण

अटल व्योम cpu5wdt_reset(व्योम)
अणु
	ticks = cpu5wdt_device.शेष_ticks;

	अगर (verbose)
		pr_debug("reset (%i ticks)\n", (पूर्णांक) ticks);

पूर्ण

अटल व्योम cpu5wdt_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cpu5wdt_lock, flags);
	अगर (!cpu5wdt_device.queue) अणु
		cpu5wdt_device.queue = 1;
		outb(0, port + CPU5WDT_TIME_A_REG);
		outb(0, port + CPU5WDT_TIME_B_REG);
		outb(1, port + CPU5WDT_MODE_REG);
		outb(0, port + CPU5WDT_RESET_REG);
		outb(0, port + CPU5WDT_ENABLE_REG);
		mod_समयr(&cpu5wdt_device.समयr, jअगरfies + CPU5WDT_INTERVAL);
	पूर्ण
	/* अगर process dies, counter is not decremented */
	cpu5wdt_device.running++;
	spin_unlock_irqrestore(&cpu5wdt_lock, flags);
पूर्ण

अटल पूर्णांक cpu5wdt_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cpu5wdt_lock, flags);
	अगर (cpu5wdt_device.running)
		cpu5wdt_device.running = 0;
	ticks = cpu5wdt_device.शेष_ticks;
	spin_unlock_irqrestore(&cpu5wdt_lock, flags);
	अगर (verbose)
		pr_crit("stop not possible\n");
	वापस -EIO;
पूर्ण

/* fileप्रणाली operations */

अटल पूर्णांक cpu5wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &cpu5wdt_device.inuse))
		वापस -EBUSY;
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक cpu5wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	clear_bit(0, &cpu5wdt_device.inuse);
	वापस 0;
पूर्ण

अटल दीर्घ cpu5wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अचिन्हित पूर्णांक value;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_CARDRESET,
		.identity = "CPU5 WDT",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSTATUS:
		value = inb(port + CPU5WDT_STATUS_REG);
		value = (value >> 2) & 1;
		वापस put_user(value, p);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(value, p))
			वापस -EFAULT;
		अगर (value & WDIOS_ENABLECARD)
			cpu5wdt_start();
		अगर (value & WDIOS_DISABLECARD)
			cpu5wdt_stop();
		अवरोध;
	हाल WDIOC_KEEPALIVE:
		cpu5wdt_reset();
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cpu5wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!count)
		वापस -EIO;
	cpu5wdt_reset();
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations cpu5wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= cpu5wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= cpu5wdt_खोलो,
	.ग_लिखो		= cpu5wdt_ग_लिखो,
	.release	= cpu5wdt_release,
पूर्ण;

अटल काष्ठा miscdevice cpu5wdt_misc = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &cpu5wdt_fops,
पूर्ण;

/* init/निकास function */

अटल पूर्णांक cpu5wdt_init(व्योम)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	अगर (verbose)
		pr_debug("port=0x%x, verbose=%i\n", port, verbose);

	init_completion(&cpu5wdt_device.stop);
	cpu5wdt_device.queue = 0;
	समयr_setup(&cpu5wdt_device.समयr, cpu5wdt_trigger, 0);
	cpu5wdt_device.शेष_ticks = ticks;

	अगर (!request_region(port, CPU5WDT_EXTENT, PFX)) अणु
		pr_err("request_region failed\n");
		err = -EBUSY;
		जाओ no_port;
	पूर्ण

	/* watchकरोg reboot? */
	val = inb(port + CPU5WDT_STATUS_REG);
	val = (val >> 2) & 1;
	अगर (!val)
		pr_info("sorry, was my fault\n");

	err = misc_रेजिस्टर(&cpu5wdt_misc);
	अगर (err < 0) अणु
		pr_err("misc_register failed\n");
		जाओ no_misc;
	पूर्ण


	pr_info("init success\n");
	वापस 0;

no_misc:
	release_region(port, CPU5WDT_EXTENT);
no_port:
	वापस err;
पूर्ण

अटल पूर्णांक cpu5wdt_init_module(व्योम)
अणु
	वापस cpu5wdt_init();
पूर्ण

अटल व्योम cpu5wdt_निकास(व्योम)
अणु
	अगर (cpu5wdt_device.queue) अणु
		cpu5wdt_device.queue = 0;
		रुको_क्रम_completion(&cpu5wdt_device.stop);
		del_समयr(&cpu5wdt_device.समयr);
	पूर्ण

	misc_deरेजिस्टर(&cpu5wdt_misc);

	release_region(port, CPU5WDT_EXTENT);

पूर्ण

अटल व्योम cpu5wdt_निकास_module(व्योम)
अणु
	cpu5wdt_निकास();
पूर्ण

/* module entry poपूर्णांकs */

module_init(cpu5wdt_init_module);
module_निकास(cpu5wdt_निकास_module);

MODULE_AUTHOR("Heiko Ronsdorf <hero@ihg.uni-duisburg.de>");
MODULE_DESCRIPTION("sma cpu5 watchdog driver");
MODULE_LICENSE("GPL");

module_param_hw(port, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(port, "base address of watchdog card, default is 0x91");

module_param(verbose, पूर्णांक, 0);
MODULE_PARM_DESC(verbose, "be verbose, default is 0 (no)");

module_param(ticks, पूर्णांक, 0);
MODULE_PARM_DESC(ticks, "count down ticks, default is 10000");
