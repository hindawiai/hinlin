<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The USB Monitor, inspired by Dave Harding's USBMon.
 *
 * This is the 's' or 'stat' पढ़ोer which debugs usbmon itself.
 * Note that this code blows through locks, so make sure that
 * /dbg/usbmon/0s is well रक्षित from non-root users.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/usb.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>

#समावेश "usb_mon.h"

#घोषणा STAT_BUF_SIZE  80

काष्ठा snap अणु
	पूर्णांक slen;
	अक्षर str[STAT_BUF_SIZE];
पूर्ण;

अटल पूर्णांक mon_stat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mon_bus *mbus;
	काष्ठा snap *sp;

	sp = kदो_स्मृति(माप(काष्ठा snap), GFP_KERNEL);
	अगर (sp == शून्य)
		वापस -ENOMEM;

	mbus = inode->i_निजी;

	sp->slen = snम_लिखो(sp->str, STAT_BUF_SIZE,
	    "nreaders %d events %u text_lost %u\n",
	    mbus->nपढ़ोers, mbus->cnt_events, mbus->cnt_text_lost);

	file->निजी_data = sp;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mon_stat_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा snap *sp = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, sp->str, sp->slen);
पूर्ण

अटल पूर्णांक mon_stat_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snap *sp = file->निजी_data;
	file->निजी_data = शून्य;
	kमुक्त(sp);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations mon_fops_stat = अणु
	.owner =	THIS_MODULE,
	.खोलो =		mon_stat_खोलो,
	.llseek =	no_llseek,
	.पढ़ो =		mon_stat_पढ़ो,
	/* .ग_लिखो =	mon_stat_ग_लिखो, */
	/* .poll =		mon_stat_poll, */
	/* .unlocked_ioctl =	mon_stat_ioctl, */
	.release =	mon_stat_release,
पूर्ण;
