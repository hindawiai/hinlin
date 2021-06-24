<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* apc - Driver implementation क्रम घातer management functions
 * of Aurora Personality Chip (APC) on SPARCstation-4/5 and
 * derivatives.
 *
 * Copyright (c) 2002 Eric Brower (ebrower@usa.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/apc.h>
#समावेश <यंत्र/processor.h>

/* Debugging
 * 
 * #घोषणा APC_DEBUG_LED
 */

#घोषणा APC_MINOR	MISC_DYNAMIC_MINOR
#घोषणा APC_OBPNAME	"power-management"
#घोषणा APC_DEVNAME "apc"

अटल u8 __iomem *regs;
अटल पूर्णांक apc_no_idle = 0;

#घोषणा apc_पढ़ोb(offs)		(sbus_पढ़ोb(regs+offs))
#घोषणा apc_ग_लिखोb(val, offs) 	(sbus_ग_लिखोb(val, regs+offs))

/* Specअगरy "apc=noidle" on the kernel command line to 
 * disable APC CPU standby support.  Certain prototype
 * प्रणालीs (SPARCstation-Fox) करो not play well with APC
 * CPU idle, so disable this अगर your प्रणाली has APC and 
 * crashes अक्रमomly.
 */
अटल पूर्णांक __init apc_setup(अक्षर *str) 
अणु
	अगर(!म_भेदन(str, "noidle", म_माप("noidle"))) अणु
		apc_no_idle = 1;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
__setup("apc=", apc_setup);

/* 
 * CPU idle callback function
 * See .../arch/sparc/kernel/process.c
 */
अटल व्योम apc_swअगरt_idle(व्योम)
अणु
#अगर_घोषित APC_DEBUG_LED
	set_auxio(0x00, AUXIO_LED); 
#पूर्ण_अगर

	apc_ग_लिखोb(apc_पढ़ोb(APC_IDLE_REG) | APC_IDLE_ON, APC_IDLE_REG);

#अगर_घोषित APC_DEBUG_LED
	set_auxio(AUXIO_LED, 0x00); 
#पूर्ण_अगर
पूर्ण 

अटल अंतरभूत व्योम apc_मुक्त(काष्ठा platक्रमm_device *op)
अणु
	of_iounmap(&op->resource[0], regs, resource_size(&op->resource[0]));
पूर्ण

अटल पूर्णांक apc_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक apc_release(काष्ठा inode *inode, काष्ठा file *f)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ apc_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ __arg)
अणु
	__u8 inarg, __user *arg = (__u8 __user *) __arg;

	चयन (cmd) अणु
	हाल APCIOCGFANCTL:
		अगर (put_user(apc_पढ़ोb(APC_FANCTL_REG) & APC_REGMASK, arg))
			वापस -EFAULT;
		अवरोध;

	हाल APCIOCGCPWR:
		अगर (put_user(apc_पढ़ोb(APC_CPOWER_REG) & APC_REGMASK, arg))
			वापस -EFAULT;
		अवरोध;

	हाल APCIOCGBPORT:
		अगर (put_user(apc_पढ़ोb(APC_BPORT_REG) & APC_BPMASK, arg))
			वापस -EFAULT;
		अवरोध;

	हाल APCIOCSFANCTL:
		अगर (get_user(inarg, arg))
			वापस -EFAULT;
		apc_ग_लिखोb(inarg & APC_REGMASK, APC_FANCTL_REG);
		अवरोध;

	हाल APCIOCSCPWR:
		अगर (get_user(inarg, arg))
			वापस -EFAULT;
		apc_ग_लिखोb(inarg & APC_REGMASK, APC_CPOWER_REG);
		अवरोध;

	हाल APCIOCSBPORT:
		अगर (get_user(inarg, arg))
			वापस -EFAULT;
		apc_ग_लिखोb(inarg & APC_BPMASK, APC_BPORT_REG);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations apc_fops = अणु
	.unlocked_ioctl =	apc_ioctl,
	.खोलो =			apc_खोलो,
	.release =		apc_release,
	.llseek =		noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice apc_miscdev = अणु APC_MINOR, APC_DEVNAME, &apc_fops पूर्ण;

अटल पूर्णांक apc_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक err;

	regs = of_ioremap(&op->resource[0], 0,
			  resource_size(&op->resource[0]), APC_OBPNAME);
	अगर (!regs) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to map registers\n", APC_DEVNAME);
		वापस -ENODEV;
	पूर्ण

	err = misc_रेजिस्टर(&apc_miscdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to register device\n", APC_DEVNAME);
		apc_मुक्त(op);
		वापस -ENODEV;
	पूर्ण

	/* Assign घातer management IDLE handler */
	अगर (!apc_no_idle)
		sparc_idle = apc_swअगरt_idle;

	prपूर्णांकk(KERN_INFO "%s: power management initialized%s\n", 
	       APC_DEVNAME, apc_no_idle ? " (CPU idle disabled)" : "");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id apc_match[] = अणु
	अणु
		.name = APC_OBPNAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, apc_match);

अटल काष्ठा platक्रमm_driver apc_driver = अणु
	.driver = अणु
		.name = "apc",
		.of_match_table = apc_match,
	पूर्ण,
	.probe		= apc_probe,
पूर्ण;

अटल पूर्णांक __init apc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&apc_driver);
पूर्ण

/* This driver is not critical to the boot process
 * and is easiest to ioremap when SBus is alपढ़ोy
 * initialized, so we install ourselves thusly:
 */
__initcall(apc_init);
