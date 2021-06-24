<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/landisk/gio.c - driver क्रम landisk
 *
 * This driver will also support the I-O DATA Device, Inc. LANDISK Board.
 * LANDISK and USL-5P Button, LED and GIO driver drive function.
 *
 *   Copylight (C) 2006 kogiidena
 *   Copylight (C) 2002 Atom Create Engineering Co., Ltd. *
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <mach-landisk/mach/gपन.स>
#समावेश <mach-landisk/mach/iodata_landisk.h>

#घोषणा DEVCOUNT                4
#घोषणा GIO_MINOR	        2	/* GIO minor no. */

अटल dev_t dev;
अटल काष्ठा cdev *cdev_p;
अटल पूर्णांक खोलोCnt;

अटल पूर्णांक gio_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक minor = iminor(inode);
	पूर्णांक ret = -ENOENT;

	preempt_disable();
	अगर (minor < DEVCOUNT) अणु
		अगर (खोलोCnt > 0) अणु
			ret = -EALREADY;
		पूर्ण अन्यथा अणु
			खोलोCnt++;
			ret = 0;
		पूर्ण
	पूर्ण
	preempt_enable();
	वापस ret;
पूर्ण

अटल पूर्णांक gio_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक minor = iminor(inode);

	अगर (minor < DEVCOUNT) अणु
		खोलोCnt--;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ gio_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक data;
	अटल अचिन्हित पूर्णांक addr = 0;

	अगर (cmd & 0x01) अणु	/* ग_लिखो */
		अगर (copy_from_user(&data, (पूर्णांक *)arg, माप(पूर्णांक))) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल GIODRV_IOCSGIOSETADDR:	/* address set */
		addr = data;
		अवरोध;

	हाल GIODRV_IOCSGIODATA1:	/* ग_लिखो byte */
		__raw_ग_लिखोb((अचिन्हित अक्षर)(0x0ff & data), addr);
		अवरोध;

	हाल GIODRV_IOCSGIODATA2:	/* ग_लिखो word */
		अगर (addr & 0x01) अणु
			वापस -EFAULT;
		पूर्ण
		__raw_ग_लिखोw((अचिन्हित लघु पूर्णांक)(0x0ffff & data), addr);
		अवरोध;

	हाल GIODRV_IOCSGIODATA4:	/* ग_लिखो दीर्घ */
		अगर (addr & 0x03) अणु
			वापस -EFAULT;
		पूर्ण
		__raw_ग_लिखोl(data, addr);
		अवरोध;

	हाल GIODRV_IOCGGIODATA1:	/* पढ़ो byte */
		data = __raw_पढ़ोb(addr);
		अवरोध;

	हाल GIODRV_IOCGGIODATA2:	/* पढ़ो word */
		अगर (addr & 0x01) अणु
			वापस -EFAULT;
		पूर्ण
		data = __raw_पढ़ोw(addr);
		अवरोध;

	हाल GIODRV_IOCGGIODATA4:	/* पढ़ो दीर्घ */
		अगर (addr & 0x03) अणु
			वापस -EFAULT;
		पूर्ण
		data = __raw_पढ़ोl(addr);
		अवरोध;
	शेष:
		वापस -EFAULT;
		अवरोध;
	पूर्ण

	अगर ((cmd & 0x01) == 0) अणु	/* पढ़ो */
		अगर (copy_to_user((पूर्णांक *)arg, &data, माप(पूर्णांक))) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gio_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = gio_खोलो,	/* खोलो */
	.release = gio_बंद,	/* release */
	.unlocked_ioctl = gio_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक __init gio_init(व्योम)
अणु
	पूर्णांक error;

	prपूर्णांकk(KERN_INFO "gio: driver initialized\n");

	खोलोCnt = 0;

	अगर ((error = alloc_chrdev_region(&dev, 0, DEVCOUNT, "gio")) < 0) अणु
		prपूर्णांकk(KERN_ERR
		       "gio: Couldn't alloc_chrdev_region, error=%d\n",
		       error);
		वापस 1;
	पूर्ण

	cdev_p = cdev_alloc();
	cdev_p->ops = &gio_fops;
	error = cdev_add(cdev_p, dev, DEVCOUNT);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
		       "gio: Couldn't cdev_add, error=%d\n", error);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास gio_निकास(व्योम)
अणु
	cdev_del(cdev_p);
	unरेजिस्टर_chrdev_region(dev, DEVCOUNT);
पूर्ण

module_init(gio_init);
module_निकास(gio_निकास);

MODULE_LICENSE("GPL");
