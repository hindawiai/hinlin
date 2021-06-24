<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* display7seg.c - Driver implementation क्रम the 7-segment display
 *                 present on Sun Microप्रणालीs CP1400 and CP1500
 *
 * Copyright (c) 2000 Eric Brower (ebrower@usa.net)
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/major.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ioport.h>		/* request_region */
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>		/* put_/get_user			*/
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/display7seg.h>

#घोषणा DRIVER_NAME	"d7s"
#घोषणा PFX		DRIVER_NAME ": "

अटल DEFINE_MUTEX(d7s_mutex);
अटल पूर्णांक sol_compat = 0;		/* Solaris compatibility mode	*/

/* Solaris compatibility flag -
 * The Solaris implementation omits support क्रम several
 * करोcumented driver features (ref Sun करोc 806-0180-03).  
 * By शेष, this module supports the करोcumented driver 
 * abilities, rather than the Solaris implementation:
 *
 * 	1) Device ALWAYS reverts to OBP-specअगरied FLIPPED mode
 * 	   upon closure of device or module unload.
 * 	2) Device ioctls D7SIOCRD/D7SIOCWR honor toggling of
 * 	   FLIP bit
 *
 * If you wish the device to operate as under Solaris,
 * omitting above features, set this parameter to non-zero.
 */
module_param(sol_compat, पूर्णांक, 0);
MODULE_PARM_DESC(sol_compat, 
		 "Disables documented functionality omitted from Solaris driver");

MODULE_AUTHOR("Eric Brower <ebrower@usa.net>");
MODULE_DESCRIPTION("7-Segment Display driver for Sun Microsystems CP1400/1500");
MODULE_LICENSE("GPL");

काष्ठा d7s अणु
	व्योम __iomem	*regs;
	bool		flipped;
पूर्ण;
काष्ठा d7s *d7s_device;

/*
 * Register block address- see header क्रम details
 * -----------------------------------------
 * | DP | ALARM | FLIP | 4 | 3 | 2 | 1 | 0 |
 * -----------------------------------------
 *
 * DP 		- Toggles decimal poपूर्णांक on/off 
 * ALARM	- Toggles "Alarm" LED green/red
 * FLIP		- Inverts display क्रम upside-करोwn mounted board
 * bits 0-4	- 7-segment display contents
 */
अटल atomic_t d7s_users = ATOMIC_INIT(0);

अटल पूर्णांक d7s_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	अगर (D7S_MINOR != iminor(inode))
		वापस -ENODEV;
	atomic_inc(&d7s_users);
	वापस 0;
पूर्ण

अटल पूर्णांक d7s_release(काष्ठा inode *inode, काष्ठा file *f)
अणु
	/* Reset flipped state to OBP शेष only अगर
	 * no other users have the device खोलो and we
	 * are not operating in solaris-compat mode
	 */
	अगर (atomic_dec_and_test(&d7s_users) && !sol_compat) अणु
		काष्ठा d7s *p = d7s_device;
		u8 regval = 0;

		regval = पढ़ोb(p->regs);
		अगर (p->flipped)
			regval |= D7S_FLIP;
		अन्यथा
			regval &= ~D7S_FLIP;
		ग_लिखोb(regval, p->regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ d7s_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा d7s *p = d7s_device;
	u8 regs = पढ़ोb(p->regs);
	पूर्णांक error = 0;
	u8 ireg = 0;

	अगर (D7S_MINOR != iminor(file_inode(file)))
		वापस -ENODEV;

	mutex_lock(&d7s_mutex);
	चयन (cmd) अणु
	हाल D7SIOCWR:
		/* assign device रेजिस्टर values we mask-out D7S_FLIP
		 * अगर in sol_compat mode
		 */
		अगर (get_user(ireg, (पूर्णांक __user *) arg)) अणु
			error = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (sol_compat) अणु
			अगर (regs & D7S_FLIP)
				ireg |= D7S_FLIP;
			अन्यथा
				ireg &= ~D7S_FLIP;
		पूर्ण
		ग_लिखोb(ireg, p->regs);
		अवरोध;

	हाल D7SIOCRD:
		/* retrieve device रेजिस्टर values
		 * NOTE: Solaris implementation वापसs D7S_FLIP bit
		 * as toggled by user, even though it करोes not honor it.
		 * This driver will not misinक्रमm you about the state
		 * of your hardware जबतक in sol_compat mode
		 */
		अगर (put_user(regs, (पूर्णांक __user *) arg)) अणु
			error = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल D7SIOCTM:
		/* toggle device mode-- flip display orientation */
		regs ^= D7S_FLIP;
		ग_लिखोb(regs, p->regs);
		अवरोध;
	पूर्ण
	mutex_unlock(&d7s_mutex);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations d7s_fops = अणु
	.owner =		THIS_MODULE,
	.unlocked_ioctl =	d7s_ioctl,
	.compat_ioctl =		compat_ptr_ioctl,
	.खोलो =			d7s_खोलो,
	.release =		d7s_release,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice d7s_miscdev = अणु
	.minor		= D7S_MINOR,
	.name		= DRIVER_NAME,
	.fops		= &d7s_fops
पूर्ण;

अटल पूर्णांक d7s_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *opts;
	पूर्णांक err = -EINVAL;
	काष्ठा d7s *p;
	u8 regs;

	अगर (d7s_device)
		जाओ out;

	p = devm_kzalloc(&op->dev, माप(*p), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!p)
		जाओ out;

	p->regs = of_ioremap(&op->resource[0], 0, माप(u8), "d7s");
	अगर (!p->regs) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map chip registers\n");
		जाओ out;
	पूर्ण

	err = misc_रेजिस्टर(&d7s_miscdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to acquire miscdevice minor %i\n",
		       D7S_MINOR);
		जाओ out_iounmap;
	पूर्ण

	/* OBP option "d7s-flipped?" is honored as शेष क्रम the
	 * device, and reset शेष when detached
	 */
	regs = पढ़ोb(p->regs);
	opts = of_find_node_by_path("/options");
	अगर (opts &&
	    of_get_property(opts, "d7s-flipped?", शून्य))
		p->flipped = true;

	अगर (p->flipped)
		regs |= D7S_FLIP;
	अन्यथा
		regs &= ~D7S_FLIP;

	ग_लिखोb(regs,  p->regs);

	prपूर्णांकk(KERN_INFO PFX "7-Segment Display%pOF at [%s:0x%llx] %s\n",
	       op->dev.of_node,
	       (regs & D7S_FLIP) ? " (FLIPPED)" : "",
	       op->resource[0].start,
	       sol_compat ? "in sol_compat mode" : "");

	dev_set_drvdata(&op->dev, p);
	d7s_device = p;
	err = 0;
	of_node_put(opts);

out:
	वापस err;

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, माप(u8));
	जाओ out;
पूर्ण

अटल पूर्णांक d7s_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा d7s *p = dev_get_drvdata(&op->dev);
	u8 regs = पढ़ोb(p->regs);

	/* Honor OBP d7s-flipped? unless operating in solaris-compat mode */
	अगर (sol_compat) अणु
		अगर (p->flipped)
			regs |= D7S_FLIP;
		अन्यथा
			regs &= ~D7S_FLIP;
		ग_लिखोb(regs, p->regs);
	पूर्ण

	misc_deरेजिस्टर(&d7s_miscdev);
	of_iounmap(&op->resource[0], p->regs, माप(u8));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id d7s_match[] = अणु
	अणु
		.name = "display7seg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, d7s_match);

अटल काष्ठा platक्रमm_driver d7s_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = d7s_match,
	पूर्ण,
	.probe		= d7s_probe,
	.हटाओ		= d7s_हटाओ,
पूर्ण;

module_platक्रमm_driver(d7s_driver);
