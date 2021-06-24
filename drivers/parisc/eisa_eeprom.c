<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 *    EISA "eeprom" support routines
 *
 *    Copyright (C) 2001 Thomas Bogenकरोerfer <tsbogend at parisc-linux.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/eisa_eeprom.h>

#घोषणा 	EISA_EEPROM_MINOR 241

अटल loff_t eisa_eeprom_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	वापस fixed_size_llseek(file, offset, origin, HPEE_MAX_LENGTH);
पूर्ण

अटल sमाप_प्रकार eisa_eeprom_पढ़ो(काष्ठा file * file,
			      अक्षर __user *buf, माप_प्रकार count, loff_t *ppos )
अणु
	अचिन्हित अक्षर *पंचांगp;
	sमाप_प्रकार ret;
	पूर्णांक i;
	
	अगर (*ppos < 0 || *ppos >= HPEE_MAX_LENGTH)
		वापस 0;
	
	count = *ppos + count < HPEE_MAX_LENGTH ? count : HPEE_MAX_LENGTH - *ppos;
	पंचांगp = kदो_स्मृति(count, GFP_KERNEL);
	अगर (पंचांगp) अणु
		क्रम (i = 0; i < count; i++)
			पंचांगp[i] = पढ़ोb(eisa_eeprom_addr+(*ppos)++);

		अगर (copy_to_user (buf, पंचांगp, count))
			ret = -EFAULT;
		अन्यथा
			ret = count;
		kमुक्त (पंचांगp);
	पूर्ण अन्यथा
		ret = -ENOMEM;
	
	वापस ret;
पूर्ण

अटल पूर्णांक eisa_eeprom_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (file->f_mode & FMODE_WRITE)
		वापस -EINVAL;
   
	वापस 0;
पूर्ण

अटल पूर्णांक eisa_eeprom_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 *	The various file operations we support.
 */
अटल स्थिर काष्ठा file_operations eisa_eeprom_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	eisa_eeprom_llseek,
	.पढ़ो =		eisa_eeprom_पढ़ो,
	.खोलो =		eisa_eeprom_खोलो,
	.release =	eisa_eeprom_release,
पूर्ण;

अटल काष्ठा miscdevice eisa_eeprom_dev = अणु
	EISA_EEPROM_MINOR,
	"eisa_eeprom",
	&eisa_eeprom_fops
पूर्ण;

अटल पूर्णांक __init eisa_eeprom_init(व्योम)
अणु
	पूर्णांक retval;

	अगर (!eisa_eeprom_addr)
		वापस -ENODEV;

	retval = misc_रेजिस्टर(&eisa_eeprom_dev);
	अगर (retval < 0) अणु
		prपूर्णांकk(KERN_ERR "EISA EEPROM: cannot register misc device.\n");
		वापस retval;
	पूर्ण

	prपूर्णांकk(KERN_INFO "EISA EEPROM at 0x%px\n", eisa_eeprom_addr);
	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");

module_init(eisa_eeprom_init);
