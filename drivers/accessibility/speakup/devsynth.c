<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>	/* क्रम misc_रेजिस्टर, and MISC_DYNAMIC_MINOR */
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश "speakup.h"
#समावेश "spk_priv.h"

अटल पूर्णांक misc_रेजिस्टरed;
अटल पूर्णांक dev_खोलोed;

अटल sमाप_प्रकार speakup_file_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *buffer,
				  माप_प्रकार nbytes, loff_t *ppos)
अणु
	माप_प्रकार count = nbytes;
	स्थिर अक्षर __user *ptr = buffer;
	माप_प्रकार bytes;
	अचिन्हित दीर्घ flags;
	u_अक्षर buf[256];

	अगर (!synth)
		वापस -ENODEV;
	जबतक (count > 0) अणु
		bytes = min(count, माप(buf));
		अगर (copy_from_user(buf, ptr, bytes))
			वापस -EFAULT;
		count -= bytes;
		ptr += bytes;
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		synth_ग_लिखो(buf, bytes);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	पूर्ण
	वापस (sमाप_प्रकार)nbytes;
पूर्ण

अटल sमाप_प्रकार speakup_file_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
				 माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक speakup_file_खोलो(काष्ठा inode *ip, काष्ठा file *fp)
अणु
	अगर (!synth)
		वापस -ENODEV;
	अगर (xchg(&dev_खोलोed, 1))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक speakup_file_release(काष्ठा inode *ip, काष्ठा file *fp)
अणु
	dev_खोलोed = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations synth_fops = अणु
	.पढ़ो = speakup_file_पढ़ो,
	.ग_लिखो = speakup_file_ग_लिखो,
	.खोलो = speakup_file_खोलो,
	.release = speakup_file_release,
पूर्ण;

अटल काष्ठा miscdevice synth_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "synth",
	.fops = &synth_fops,
पूर्ण;

व्योम speakup_रेजिस्टर_devsynth(व्योम)
अणु
	अगर (misc_रेजिस्टरed != 0)
		वापस;
/* zero it so अगर रेजिस्टर fails, deरेजिस्टर will not ref invalid ptrs */
	अगर (misc_रेजिस्टर(&synth_device)) अणु
		pr_warn("Couldn't initialize miscdevice /dev/synth.\n");
	पूर्ण अन्यथा अणु
		pr_info("initialized device: /dev/synth, node (MAJOR %d, MINOR %d)\n",
			MISC_MAJOR, synth_device.minor);
		misc_रेजिस्टरed = 1;
	पूर्ण
पूर्ण

व्योम speakup_unरेजिस्टर_devsynth(व्योम)
अणु
	अगर (!misc_रेजिस्टरed)
		वापस;
	pr_info("speakup: unregistering synth device /dev/synth\n");
	misc_deरेजिस्टर(&synth_device);
	misc_रेजिस्टरed = 0;
पूर्ण
