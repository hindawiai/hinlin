<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * /dev/lcd driver क्रम Apple Network Servers.
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>

#समावेश "ans-lcd.h"

#घोषणा ANSLCD_ADDR		0xf301c000
#घोषणा ANSLCD_CTRL_IX 0x00
#घोषणा ANSLCD_DATA_IX 0x10

अटल अचिन्हित दीर्घ anslcd_लघु_delay = 80;
अटल अचिन्हित दीर्घ anslcd_दीर्घ_delay = 3280;
अटल अस्थिर अचिन्हित अक्षर __iomem *anslcd_ptr;
अटल DEFINE_MUTEX(anslcd_mutex);

#अघोषित DEBUG

अटल व्योम
anslcd_ग_लिखो_byte_ctrl ( अचिन्हित अक्षर c )
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "LCD: CTRL byte: %02x\n",c);
#पूर्ण_अगर
	out_8(anslcd_ptr + ANSLCD_CTRL_IX, c);
	चयन(c) अणु
		हाल 1:
		हाल 2:
		हाल 3:
			udelay(anslcd_दीर्घ_delay); अवरोध;
		शेष: udelay(anslcd_लघु_delay);
	पूर्ण
पूर्ण

अटल व्योम
anslcd_ग_लिखो_byte_data ( अचिन्हित अक्षर c )
अणु
	out_8(anslcd_ptr + ANSLCD_DATA_IX, c);
	udelay(anslcd_लघु_delay);
पूर्ण

अटल sमाप_प्रकार
anslcd_ग_लिखो( काष्ठा file * file, स्थिर अक्षर __user * buf, 
				माप_प्रकार count, loff_t *ppos )
अणु
	स्थिर अक्षर __user *p = buf;
	पूर्णांक i;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "LCD: write\n");
#पूर्ण_अगर

	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	mutex_lock(&anslcd_mutex);
	क्रम ( i = *ppos; count > 0; ++i, ++p, --count ) 
	अणु
		अक्षर c;
		__get_user(c, p);
		anslcd_ग_लिखो_byte_data( c );
	पूर्ण
	mutex_unlock(&anslcd_mutex);
	*ppos = i;
	वापस p - buf;
पूर्ण

अटल दीर्घ
anslcd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अक्षर ch, __user *temp;
	दीर्घ ret = 0;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "LCD: ioctl(%d,%d)\n",cmd,arg);
#पूर्ण_अगर

	mutex_lock(&anslcd_mutex);

	चयन ( cmd )
	अणु
	हाल ANSLCD_CLEAR:
		anslcd_ग_लिखो_byte_ctrl ( 0x38 );
		anslcd_ग_लिखो_byte_ctrl ( 0x0f );
		anslcd_ग_लिखो_byte_ctrl ( 0x06 );
		anslcd_ग_लिखो_byte_ctrl ( 0x01 );
		anslcd_ग_लिखो_byte_ctrl ( 0x02 );
		अवरोध;
	हाल ANSLCD_SENDCTRL:
		temp = (अक्षर __user *) arg;
		__get_user(ch, temp);
		क्रम (; ch; temp++) अणु /* FIXME: This is ugly, but should work, as a \0 byte is not a valid command code */
			anslcd_ग_लिखो_byte_ctrl ( ch );
			__get_user(ch, temp);
		पूर्ण
		अवरोध;
	हाल ANSLCD_SETSHORTDELAY:
		अगर (!capable(CAP_SYS_ADMIN))
			ret =-EACCES;
		अन्यथा
			anslcd_लघु_delay=arg;
		अवरोध;
	हाल ANSLCD_SETLONGDELAY:
		अगर (!capable(CAP_SYS_ADMIN))
			ret = -EACCES;
		अन्यथा
			anslcd_दीर्घ_delay=arg;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&anslcd_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
anslcd_खोलो( काष्ठा inode * inode, काष्ठा file * file )
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations anslcd_fops = अणु
	.ग_लिखो		= anslcd_ग_लिखो,
	.unlocked_ioctl	= anslcd_ioctl,
	.खोलो		= anslcd_खोलो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा miscdevice anslcd_dev = अणु
	LCD_MINOR,
	"anslcd",
	&anslcd_fops
पूर्ण;

अटल स्थिर अक्षर anslcd_logo[] __initस्थिर =
				"********************"  /* Line #1 */
				"*      LINUX!      *"  /* Line #3 */
				"*    Welcome to    *"  /* Line #2 */
				"********************"; /* Line #4 */

अटल पूर्णांक __init
anslcd_init(व्योम)
अणु
	पूर्णांक a;
	पूर्णांक retval;
	काष्ठा device_node* node;

	node = of_find_node_by_name(शून्य, "lcd");
	अगर (!node || !of_node_name_eq(node->parent, "gc")) अणु
		of_node_put(node);
		वापस -ENODEV;
	पूर्ण
	of_node_put(node);

	anslcd_ptr = ioremap(ANSLCD_ADDR, 0x20);
	
	retval = misc_रेजिस्टर(&anslcd_dev);
	अगर(retval < 0)अणु
		prपूर्णांकk(KERN_INFO "LCD: misc_register failed\n");
		iounmap(anslcd_ptr);
		वापस retval;
	पूर्ण

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "LCD: init\n");
#पूर्ण_अगर

	mutex_lock(&anslcd_mutex);
	anslcd_ग_लिखो_byte_ctrl ( 0x38 );
	anslcd_ग_लिखो_byte_ctrl ( 0x0c );
	anslcd_ग_लिखो_byte_ctrl ( 0x06 );
	anslcd_ग_लिखो_byte_ctrl ( 0x01 );
	anslcd_ग_लिखो_byte_ctrl ( 0x02 );
	क्रम(a=0;a<80;a++) अणु
		anslcd_ग_लिखो_byte_data(anslcd_logo[a]);
	पूर्ण
	mutex_unlock(&anslcd_mutex);
	वापस 0;
पूर्ण

अटल व्योम __निकास
anslcd_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&anslcd_dev);
	iounmap(anslcd_ptr);
पूर्ण

module_init(anslcd_init);
module_निकास(anslcd_निकास);
MODULE_LICENSE("GPL v2");
