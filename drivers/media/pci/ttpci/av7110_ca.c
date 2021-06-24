<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * av7110_ca.c: CA and CI stuff
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * originally based on code by:
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 *
 * the project's page is at https://linuxtv.org
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/poll.h>
#समावेश <linux/gfp.h>

#समावेश "av7110.h"
#समावेश "av7110_hw.h"
#समावेश "av7110_ca.h"


व्योम CI_handle(काष्ठा av7110 *av7110, u8 *data, u16 len)
अणु
	dprपूर्णांकk(8, "av7110:%p\n",av7110);

	अगर (len < 3)
		वापस;
	चयन (data[0]) अणु
	हाल CI_MSG_CI_INFO:
		अगर (data[2] != 1 && data[2] != 2)
			अवरोध;
		चयन (data[1]) अणु
		हाल 0:
			av7110->ci_slot[data[2] - 1].flags = 0;
			अवरोध;
		हाल 1:
			av7110->ci_slot[data[2] - 1].flags |= CA_CI_MODULE_PRESENT;
			अवरोध;
		हाल 2:
			av7110->ci_slot[data[2] - 1].flags |= CA_CI_MODULE_READY;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CI_SWITCH_PRG_REPLY:
		//av7110->ci_stat=data[1];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण


व्योम ci_get_data(काष्ठा dvb_ringbuffer *cibuf, u8 *data, पूर्णांक len)
अणु
	अगर (dvb_ringbuffer_मुक्त(cibuf) < len + 2)
		वापस;

	DVB_RINGBUFFER_WRITE_BYTE(cibuf, len >> 8);
	DVB_RINGBUFFER_WRITE_BYTE(cibuf, len & 0xff);
	dvb_ringbuffer_ग_लिखो(cibuf, data, len);
	wake_up_पूर्णांकerruptible(&cibuf->queue);
पूर्ण


/******************************************************************************
 * CI link layer file ops
 ******************************************************************************/

अटल पूर्णांक ci_ll_init(काष्ठा dvb_ringbuffer *cirbuf, काष्ठा dvb_ringbuffer *ciwbuf, पूर्णांक size)
अणु
	काष्ठा dvb_ringbuffer *tab[] = अणु cirbuf, ciwbuf, शून्य पूर्ण, **p;
	व्योम *data;

	क्रम (p = tab; *p; p++) अणु
		data = vदो_स्मृति(size);
		अगर (!data) अणु
			जबतक (p-- != tab) अणु
				vमुक्त(p[0]->data);
				p[0]->data = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		dvb_ringbuffer_init(*p, data, size);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ci_ll_flush(काष्ठा dvb_ringbuffer *cirbuf, काष्ठा dvb_ringbuffer *ciwbuf)
अणु
	dvb_ringbuffer_flush_spinlock_wakeup(cirbuf);
	dvb_ringbuffer_flush_spinlock_wakeup(ciwbuf);
पूर्ण

अटल व्योम ci_ll_release(काष्ठा dvb_ringbuffer *cirbuf, काष्ठा dvb_ringbuffer *ciwbuf)
अणु
	vमुक्त(cirbuf->data);
	cirbuf->data = शून्य;
	vमुक्त(ciwbuf->data);
	ciwbuf->data = शून्य;
पूर्ण

अटल पूर्णांक ci_ll_reset(काष्ठा dvb_ringbuffer *cibuf, काष्ठा file *file,
		       पूर्णांक slots, काष्ठा ca_slot_info *slot)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;
	u8 msg[8] = अणु 0x00, 0x06, 0x00, 0x00, 0xff, 0x02, 0x00, 0x00 पूर्ण;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (slots & (1 << i))
			len += 8;
	पूर्ण

	अगर (dvb_ringbuffer_मुक्त(cibuf) < len)
		वापस -EBUSY;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (slots & (1 << i)) अणु
			msg[2] = i;
			dvb_ringbuffer_ग_लिखो(cibuf, msg, 8);
			slot[i].flags = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ci_ll_ग_लिखो(काष्ठा dvb_ringbuffer *cibuf, काष्ठा file *file,
			   स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक मुक्त;
	पूर्णांक non_blocking = file->f_flags & O_NONBLOCK;
	u8 *page = (u8 *)__get_मुक्त_page(GFP_USER);
	पूर्णांक res;

	अगर (!page)
		वापस -ENOMEM;

	res = -EINVAL;
	अगर (count > 2048)
		जाओ out;

	res = -EFAULT;
	अगर (copy_from_user(page, buf, count))
		जाओ out;

	मुक्त = dvb_ringbuffer_मुक्त(cibuf);
	अगर (count + 2 > मुक्त) अणु
		res = -EWOULDBLOCK;
		अगर (non_blocking)
			जाओ out;
		res = -ERESTARTSYS;
		अगर (रुको_event_पूर्णांकerruptible(cibuf->queue,
					     (dvb_ringbuffer_मुक्त(cibuf) >= count + 2)))
			जाओ out;
	पूर्ण

	DVB_RINGBUFFER_WRITE_BYTE(cibuf, count >> 8);
	DVB_RINGBUFFER_WRITE_BYTE(cibuf, count & 0xff);

	res = dvb_ringbuffer_ग_लिखो(cibuf, page, count);
out:
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस res;
पूर्ण

अटल sमाप_प्रकार ci_ll_पढ़ो(काष्ठा dvb_ringbuffer *cibuf, काष्ठा file *file,
			  अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक avail;
	पूर्णांक non_blocking = file->f_flags & O_NONBLOCK;
	sमाप_प्रकार len;

	अगर (!cibuf->data || !count)
		वापस 0;
	अगर (non_blocking && (dvb_ringbuffer_empty(cibuf)))
		वापस -EWOULDBLOCK;
	अगर (रुको_event_पूर्णांकerruptible(cibuf->queue,
				     !dvb_ringbuffer_empty(cibuf)))
		वापस -ERESTARTSYS;
	avail = dvb_ringbuffer_avail(cibuf);
	अगर (avail < 4)
		वापस 0;
	len = DVB_RINGBUFFER_PEEK(cibuf, 0) << 8;
	len |= DVB_RINGBUFFER_PEEK(cibuf, 1);
	अगर (avail < len + 2 || count < len)
		वापस -EINVAL;
	DVB_RINGBUFFER_SKIP(cibuf, 2);

	वापस dvb_ringbuffer_पढ़ो_user(cibuf, buf, len);
पूर्ण

अटल पूर्णांक dvb_ca_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	पूर्णांक err = dvb_generic_खोलो(inode, file);

	dprपूर्णांकk(8, "av7110:%p\n",av7110);

	अगर (err < 0)
		वापस err;
	ci_ll_flush(&av7110->ci_rbuffer, &av7110->ci_wbuffer);
	वापस 0;
पूर्ण

अटल __poll_t dvb_ca_poll (काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	काष्ठा dvb_ringbuffer *rbuf = &av7110->ci_rbuffer;
	काष्ठा dvb_ringbuffer *wbuf = &av7110->ci_wbuffer;
	__poll_t mask = 0;

	dprपूर्णांकk(8, "av7110:%p\n",av7110);

	poll_रुको(file, &rbuf->queue, रुको);
	poll_रुको(file, &wbuf->queue, रुको);

	अगर (!dvb_ringbuffer_empty(rbuf))
		mask |= (EPOLLIN | EPOLLRDNORM);

	अगर (dvb_ringbuffer_मुक्त(wbuf) > 1024)
		mask |= (EPOLLOUT | EPOLLWRNORM);

	वापस mask;
पूर्ण

अटल पूर्णांक dvb_ca_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	अचिन्हित दीर्घ arg = (अचिन्हित दीर्घ) parg;
	पूर्णांक ret = 0;

	dprपूर्णांकk(8, "av7110:%p\n",av7110);

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->ioctl_mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल CA_RESET:
		ret = ci_ll_reset(&av7110->ci_wbuffer, file, arg,
				  &av7110->ci_slot[0]);
		अवरोध;
	हाल CA_GET_CAP:
	अणु
		काष्ठा ca_caps cap;

		cap.slot_num = 2;
		cap.slot_type = (FW_CI_LL_SUPPORT(av7110->arm_app) ?
				 CA_CI_LINK : CA_CI) | CA_DESCR;
		cap.descr_num = 16;
		cap.descr_type = CA_ECD;
		स_नकल(parg, &cap, माप(cap));
		अवरोध;
	पूर्ण

	हाल CA_GET_SLOT_INFO:
	अणु
		काष्ठा ca_slot_info *info=(काष्ठा ca_slot_info *)parg;

		अगर (info->num < 0 || info->num > 1) अणु
			mutex_unlock(&av7110->ioctl_mutex);
			वापस -EINVAL;
		पूर्ण
		av7110->ci_slot[info->num].num = info->num;
		av7110->ci_slot[info->num].type = FW_CI_LL_SUPPORT(av7110->arm_app) ?
							CA_CI_LINK : CA_CI;
		स_नकल(info, &av7110->ci_slot[info->num], माप(काष्ठा ca_slot_info));
		अवरोध;
	पूर्ण

	हाल CA_GET_MSG:
		अवरोध;

	हाल CA_SEND_MSG:
		अवरोध;

	हाल CA_GET_DESCR_INFO:
	अणु
		काष्ठा ca_descr_info info;

		info.num = 16;
		info.type = CA_ECD;
		स_नकल(parg, &info, माप (info));
		अवरोध;
	पूर्ण

	हाल CA_SET_DESCR:
	अणु
		काष्ठा ca_descr *descr = (काष्ठा ca_descr*) parg;

		अगर (descr->index >= 16 || descr->parity > 1) अणु
			mutex_unlock(&av7110->ioctl_mutex);
			वापस -EINVAL;
		पूर्ण
		av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, SetDescr, 5,
			      (descr->index<<8)|descr->parity,
			      (descr->cw[0]<<8)|descr->cw[1],
			      (descr->cw[2]<<8)|descr->cw[3],
			      (descr->cw[4]<<8)|descr->cw[5],
			      (descr->cw[6]<<8)|descr->cw[7]);
		अवरोध;
	पूर्ण

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&av7110->ioctl_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार dvb_ca_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;

	dprपूर्णांकk(8, "av7110:%p\n",av7110);
	वापस ci_ll_ग_लिखो(&av7110->ci_wbuffer, file, buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार dvb_ca_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;

	dprपूर्णांकk(8, "av7110:%p\n",av7110);
	वापस ci_ll_पढ़ो(&av7110->ci_rbuffer, file, buf, count, ppos);
पूर्ण

अटल स्थिर काष्ठा file_operations dvb_ca_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= dvb_ca_पढ़ो,
	.ग_लिखो		= dvb_ca_ग_लिखो,
	.unlocked_ioctl	= dvb_generic_ioctl,
	.खोलो		= dvb_ca_खोलो,
	.release	= dvb_generic_release,
	.poll		= dvb_ca_poll,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_ca = अणु
	.priv		= शून्य,
	.users		= 1,
	.ग_लिखोrs	= 1,
	.fops		= &dvb_ca_fops,
	.kernel_ioctl	= dvb_ca_ioctl,
पूर्ण;


पूर्णांक av7110_ca_रेजिस्टर(काष्ठा av7110 *av7110)
अणु
	वापस dvb_रेजिस्टर_device(&av7110->dvb_adapter, &av7110->ca_dev,
				   &dvbdev_ca, av7110, DVB_DEVICE_CA, 0);
पूर्ण

व्योम av7110_ca_unरेजिस्टर(काष्ठा av7110 *av7110)
अणु
	dvb_unरेजिस्टर_device(av7110->ca_dev);
पूर्ण

पूर्णांक av7110_ca_init(काष्ठा av7110* av7110)
अणु
	वापस ci_ll_init(&av7110->ci_rbuffer, &av7110->ci_wbuffer, 8192);
पूर्ण

व्योम av7110_ca_निकास(काष्ठा av7110* av7110)
अणु
	ci_ll_release(&av7110->ci_rbuffer, &av7110->ci_wbuffer);
पूर्ण
