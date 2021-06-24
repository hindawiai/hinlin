<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/अक्षर/nsc_gpio.c

   National Semiconductor common GPIO device-file/VFS methods.
   Allows a user space process to control the GPIO pins.

   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>
   Copyright (c) 2005      Jim Cromie <jim.cromie@gmail.com>
*/

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/nsc_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#घोषणा NAME "nsc_gpio"

व्योम nsc_gpio_dump(काष्ठा nsc_gpio_ops *amp, अचिन्हित index)
अणु
	/* retrieve current config w/o changing it */
	u32 config = amp->gpio_config(index, ~0, 0);

	/* user requested via 'v' command, so its INFO */
	dev_info(amp->dev, "io%02u: 0x%04x %s %s %s %s %s %s %s\tio:%d/%d\n",
		 index, config,
		 (config & 1) ? "OE" : "TS",      /* output-enabled/tristate */
		 (config & 2) ? "PP" : "OD",      /* push pull / खोलो drain */
		 (config & 4) ? "PUE" : "PUD",    /* pull up enabled/disabled */
		 (config & 8) ? "LOCKED" : "",    /* locked / unlocked */
		 (config & 16) ? "LEVEL" : "EDGE",/* level/edge input */
		 (config & 32) ? "HI" : "LO",     /* trigger on rise/fall edge */
		 (config & 64) ? "DEBOUNCE" : "", /* debounce */

		 amp->gpio_get(index), amp->gpio_current(index));
पूर्ण

sमाप_प्रकार nsc_gpio_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
		       माप_प्रकार len, loff_t *ppos)
अणु
	अचिन्हित m = iminor(file_inode(file));
	काष्ठा nsc_gpio_ops *amp = file->निजी_data;
	काष्ठा device *dev = amp->dev;
	माप_प्रकार i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < len; ++i) अणु
		अक्षर c;
		अगर (get_user(c, data + i))
			वापस -EFAULT;
		चयन (c) अणु
		हाल '0':
			amp->gpio_set(m, 0);
			अवरोध;
		हाल '1':
			amp->gpio_set(m, 1);
			अवरोध;
		हाल 'O':
			dev_dbg(dev, "GPIO%d output enabled\n", m);
			amp->gpio_config(m, ~1, 1);
			अवरोध;
		हाल 'o':
			dev_dbg(dev, "GPIO%d output disabled\n", m);
			amp->gpio_config(m, ~1, 0);
			अवरोध;
		हाल 'T':
			dev_dbg(dev, "GPIO%d output is push pull\n", m);
			amp->gpio_config(m, ~2, 2);
			अवरोध;
		हाल 't':
			dev_dbg(dev, "GPIO%d output is open drain\n", m);
			amp->gpio_config(m, ~2, 0);
			अवरोध;
		हाल 'P':
			dev_dbg(dev, "GPIO%d pull up enabled\n", m);
			amp->gpio_config(m, ~4, 4);
			अवरोध;
		हाल 'p':
			dev_dbg(dev, "GPIO%d pull up disabled\n", m);
			amp->gpio_config(m, ~4, 0);
			अवरोध;
		हाल 'v':
			/* View Current pin settings */
			amp->gpio_dump(amp, m);
			अवरोध;
		हाल '\n':
			/* end of settings string, करो nothing */
			अवरोध;
		शेष:
			dev_err(dev, "io%2d bad setting: chr<0x%2x>\n",
				m, (पूर्णांक)c);
			err++;
		पूर्ण
	पूर्ण
	अगर (err)
		वापस -EINVAL;	/* full string handled, report error */

	वापस len;
पूर्ण

sमाप_प्रकार nsc_gpio_पढ़ो(काष्ठा file *file, अक्षर __user * buf,
		      माप_प्रकार len, loff_t * ppos)
अणु
	अचिन्हित m = iminor(file_inode(file));
	पूर्णांक value;
	काष्ठा nsc_gpio_ops *amp = file->निजी_data;

	value = amp->gpio_get(m);
	अगर (put_user(value ? '1' : '0', buf))
		वापस -EFAULT;

	वापस 1;
पूर्ण

/* common file-ops routines क्रम both scx200_gpio and pc87360_gpio */
EXPORT_SYMBOL(nsc_gpio_ग_लिखो);
EXPORT_SYMBOL(nsc_gpio_पढ़ो);
EXPORT_SYMBOL(nsc_gpio_dump);

अटल पूर्णांक __init nsc_gpio_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG NAME " initializing\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास nsc_gpio_cleanup(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG NAME " cleanup\n");
पूर्ण

module_init(nsc_gpio_init);
module_निकास(nsc_gpio_cleanup);

MODULE_AUTHOR("Jim Cromie <jim.cromie@gmail.com>");
MODULE_DESCRIPTION("NatSemi GPIO Common Methods");
MODULE_LICENSE("GPL");
