<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* riowd.c - driver क्रम hw watchकरोg inside Super I/O of RIO
 *
 * Copyright (C) 2001, 2008 David S. Miller (davem@davemloft.net)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>


/* RIO uses the NatSemi Super I/O घातer management logical device
 * as its' watchकरोg.
 *
 * When the watchकरोg triggers, it निश्चितs a line to the BBC (Boot Bus
 * Controller) of the machine.  The BBC can only be configured to
 * trigger a घातer-on reset when the संकेत is निश्चितed.  The BBC
 * can be configured to ignore the संकेत entirely as well.
 *
 * The only Super I/O device रेजिस्टर we care about is at index
 * 0x05 (WDTO_INDEX) which is the watchकरोg समय-out in minutes (1-255).
 * If set to zero, this disables the watchकरोg.  When set, the प्रणाली
 * must periodically (beक्रमe watchकरोg expires) clear (set to zero) and
 * re-set the watchकरोg अन्यथा it will trigger.
 *
 * There are two other indexed watchकरोg रेजिस्टरs inside this Super I/O
 * logical device, but they are unused.  The first, at index 0x06 is
 * the watchकरोg control and can be used to make the watchकरोg समयr re-set
 * when the PS/2 mouse or serial lines show activity.  The second, at
 * index 0x07 is merely a sampling of the line from the watchकरोg to the
 * BBC.
 *
 * The watchकरोg device generates no पूर्णांकerrupts.
 */

MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_DESCRIPTION("Hardware watchdog driver for Sun RIO");
MODULE_LICENSE("GPL");

#घोषणा DRIVER_NAME	"riowd"
#घोषणा PFX		DRIVER_NAME ": "

काष्ठा riowd अणु
	व्योम __iomem		*regs;
	spinlock_t		lock;
पूर्ण;

अटल काष्ठा riowd *riowd_device;

#घोषणा WDTO_INDEX	0x05

अटल पूर्णांक riowd_समयout = 1;		/* in minutes */
module_param(riowd_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(riowd_समयout, "Watchdog timeout in minutes");

अटल व्योम riowd_ग_लिखोreg(काष्ठा riowd *p, u8 val, पूर्णांक index)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->lock, flags);
	ग_लिखोb(index, p->regs + 0);
	ग_लिखोb(val, p->regs + 1);
	spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल पूर्णांक riowd_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	stream_खोलो(inode, filp);
	वापस 0;
पूर्ण

अटल पूर्णांक riowd_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ riowd_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अटल स्थिर काष्ठा watchकरोg_info info = अणु
		.options		= WDIOF_SETTIMEOUT,
		.firmware_version	= 1,
		.identity		= DRIVER_NAME,
	पूर्ण;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा riowd *p = riowd_device;
	अचिन्हित पूर्णांक options;
	पूर्णांक new_margin;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &info, माप(info)))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		अगर (put_user(0, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		riowd_ग_लिखोreg(p, riowd_समयout, WDTO_INDEX);
		अवरोध;

	हाल WDIOC_SETOPTIONS:
		अगर (copy_from_user(&options, argp, माप(options)))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD)
			riowd_ग_लिखोreg(p, 0, WDTO_INDEX);
		अन्यथा अगर (options & WDIOS_ENABLECARD)
			riowd_ग_लिखोreg(p, riowd_समयout, WDTO_INDEX);
		अन्यथा
			वापस -EINVAL;

		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_margin, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अगर ((new_margin < 60) || (new_margin > (255 * 60)))
			वापस -EINVAL;
		riowd_समयout = (new_margin + 59) / 60;
		riowd_ग_लिखोreg(p, riowd_समयout, WDTO_INDEX);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(riowd_समयout * 60, (पूर्णांक __user *)argp);

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार riowd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा riowd *p = riowd_device;

	अगर (count) अणु
		riowd_ग_लिखोreg(p, riowd_समयout, WDTO_INDEX);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations riowd_fops = अणु
	.owner =		THIS_MODULE,
	.llseek =		no_llseek,
	.unlocked_ioctl =	riowd_ioctl,
	.compat_ioctl	=	compat_ptr_ioctl,
	.खोलो =			riowd_खोलो,
	.ग_लिखो =		riowd_ग_लिखो,
	.release =		riowd_release,
पूर्ण;

अटल काष्ठा miscdevice riowd_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &riowd_fops
पूर्ण;

अटल पूर्णांक riowd_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा riowd *p;
	पूर्णांक err = -EINVAL;

	अगर (riowd_device)
		जाओ out;

	err = -ENOMEM;
	p = devm_kzalloc(&op->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		जाओ out;

	spin_lock_init(&p->lock);

	p->regs = of_ioremap(&op->resource[0], 0, 2, DRIVER_NAME);
	अगर (!p->regs) अणु
		pr_err("Cannot map registers\n");
		जाओ out;
	पूर्ण
	/* Make miscdev useable right away */
	riowd_device = p;

	err = misc_रेजिस्टर(&riowd_miscdev);
	अगर (err) अणु
		pr_err("Cannot register watchdog misc device\n");
		जाओ out_iounmap;
	पूर्ण

	pr_info("Hardware watchdog [%i minutes], regs at %p\n",
		riowd_समयout, p->regs);

	platक्रमm_set_drvdata(op, p);
	वापस 0;

out_iounmap:
	riowd_device = शून्य;
	of_iounmap(&op->resource[0], p->regs, 2);

out:
	वापस err;
पूर्ण

अटल पूर्णांक riowd_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा riowd *p = platक्रमm_get_drvdata(op);

	misc_deरेजिस्टर(&riowd_miscdev);
	of_iounmap(&op->resource[0], p->regs, 2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id riowd_match[] = अणु
	अणु
		.name = "pmc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, riowd_match);

अटल काष्ठा platक्रमm_driver riowd_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = riowd_match,
	पूर्ण,
	.probe		= riowd_probe,
	.हटाओ		= riowd_हटाओ,
पूर्ण;

module_platक्रमm_driver(riowd_driver);
