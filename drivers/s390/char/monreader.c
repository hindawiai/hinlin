<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Character device driver क्रम पढ़ोing z/VM *MONITOR service records.
 *
 * Copyright IBM Corp. 2004, 2009
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "monreader"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/poll.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <net/iucv/iucv.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/exपंचांगem.h>


#घोषणा MON_COLLECT_SAMPLE 0x80
#घोषणा MON_COLLECT_EVENT  0x40
#घोषणा MON_SERVICE	   "*MONITOR"
#घोषणा MON_IN_USE	   0x01
#घोषणा MON_MSGLIM	   255

अटल अक्षर mon_dcss_name[9] = "MONDCSS\0";

काष्ठा mon_msg अणु
	u32 pos;
	u32 mca_offset;
	काष्ठा iucv_message msg;
	अक्षर msglim_reached;
	अक्षर replied_msglim;
पूर्ण;

काष्ठा mon_निजी अणु
	काष्ठा iucv_path *path;
	काष्ठा mon_msg *msg_array[MON_MSGLIM];
	अचिन्हित पूर्णांक   ग_लिखो_index;
	अचिन्हित पूर्णांक   पढ़ो_index;
	atomic_t msglim_count;
	atomic_t पढ़ो_पढ़ोy;
	atomic_t iucv_connected;
	atomic_t iucv_severed;
पूर्ण;

अटल अचिन्हित दीर्घ mon_in_use = 0;

अटल अचिन्हित दीर्घ mon_dcss_start;
अटल अचिन्हित दीर्घ mon_dcss_end;

अटल DECLARE_WAIT_QUEUE_HEAD(mon_पढ़ो_रुको_queue);
अटल DECLARE_WAIT_QUEUE_HEAD(mon_conn_रुको_queue);

अटल u8 user_data_connect[16] = अणु
	/* Version code, must be 0x01 क्रम shared mode */
	0x01,
	/* what to collect */
	MON_COLLECT_SAMPLE | MON_COLLECT_EVENT,
	/* DCSS name in EBCDIC, 8 bytes padded with blanks */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
पूर्ण;

अटल u8 user_data_sever[16] = अणु
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
पूर्ण;

अटल काष्ठा device *monपढ़ोer_device;

/******************************************************************************
 *                             helper functions                               *
 *****************************************************************************/
/*
 * Create the 8 bytes EBCDIC DCSS segment name from
 * an ASCII name, incl. padding
 */
अटल व्योम dcss_mkname(अक्षर *ascii_name, अक्षर *ebcdic_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ascii_name[i] == '\0')
			अवरोध;
		ebcdic_name[i] = बड़े(ascii_name[i]);
	पूर्ण
	क्रम (; i < 8; i++)
		ebcdic_name[i] = ' ';
	ASCEBC(ebcdic_name, 8);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mon_mca_start(काष्ठा mon_msg *monmsg)
अणु
	वापस *(u32 *) &monmsg->msg.rmmsg;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mon_mca_end(काष्ठा mon_msg *monmsg)
अणु
	वापस *(u32 *) &monmsg->msg.rmmsg[4];
पूर्ण

अटल अंतरभूत u8 mon_mca_type(काष्ठा mon_msg *monmsg, u8 index)
अणु
	वापस *((u8 *) mon_mca_start(monmsg) + monmsg->mca_offset + index);
पूर्ण

अटल अंतरभूत u32 mon_mca_size(काष्ठा mon_msg *monmsg)
अणु
	वापस mon_mca_end(monmsg) - mon_mca_start(monmsg) + 1;
पूर्ण

अटल अंतरभूत u32 mon_rec_start(काष्ठा mon_msg *monmsg)
अणु
	वापस *((u32 *) (mon_mca_start(monmsg) + monmsg->mca_offset + 4));
पूर्ण

अटल अंतरभूत u32 mon_rec_end(काष्ठा mon_msg *monmsg)
अणु
	वापस *((u32 *) (mon_mca_start(monmsg) + monmsg->mca_offset + 8));
पूर्ण

अटल पूर्णांक mon_check_mca(काष्ठा mon_msg *monmsg)
अणु
	अगर ((mon_rec_end(monmsg) <= mon_rec_start(monmsg)) ||
	    (mon_rec_start(monmsg) < mon_dcss_start) ||
	    (mon_rec_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_type(monmsg, 0) == 0) ||
	    (mon_mca_size(monmsg) % 12 != 0) ||
	    (mon_mca_end(monmsg) <= mon_mca_start(monmsg)) ||
	    (mon_mca_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_start(monmsg) < mon_dcss_start) ||
	    ((mon_mca_type(monmsg, 1) == 0) && (mon_mca_type(monmsg, 2) == 0)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक mon_send_reply(काष्ठा mon_msg *monmsg,
			  काष्ठा mon_निजी *monpriv)
अणु
	पूर्णांक rc;

	rc = iucv_message_reply(monpriv->path, &monmsg->msg,
				IUCV_IPRMDATA, शून्य, 0);
	atomic_dec(&monpriv->msglim_count);
	अगर (likely(!monmsg->msglim_reached)) अणु
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpriv->पढ़ो_index = (monpriv->पढ़ो_index + 1) %
				      MON_MSGLIM;
		atomic_dec(&monpriv->पढ़ो_पढ़ोy);
	पूर्ण अन्यथा
		monmsg->replied_msglim = 1;
	अगर (rc) अणु
		pr_err("Reading monitor data failed with rc=%i\n", rc);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mon_मुक्त_mem(काष्ठा mon_निजी *monpriv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MON_MSGLIM; i++)
		kमुक्त(monpriv->msg_array[i]);
	kमुक्त(monpriv);
पूर्ण

अटल काष्ठा mon_निजी *mon_alloc_mem(व्योम)
अणु
	पूर्णांक i;
	काष्ठा mon_निजी *monpriv;

	monpriv = kzalloc(माप(काष्ठा mon_निजी), GFP_KERNEL);
	अगर (!monpriv)
		वापस शून्य;
	क्रम (i = 0; i < MON_MSGLIM; i++) अणु
		monpriv->msg_array[i] = kzalloc(माप(काष्ठा mon_msg),
						    GFP_KERNEL);
		अगर (!monpriv->msg_array[i]) अणु
			mon_मुक्त_mem(monpriv);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस monpriv;
पूर्ण

अटल अंतरभूत व्योम mon_next_mca(काष्ठा mon_msg *monmsg)
अणु
	अगर (likely((mon_mca_size(monmsg) - monmsg->mca_offset) == 12))
		वापस;
	monmsg->mca_offset += 12;
	monmsg->pos = 0;
पूर्ण

अटल काष्ठा mon_msg *mon_next_message(काष्ठा mon_निजी *monpriv)
अणु
	काष्ठा mon_msg *monmsg;

	अगर (!atomic_पढ़ो(&monpriv->पढ़ो_पढ़ोy))
		वापस शून्य;
	monmsg = monpriv->msg_array[monpriv->पढ़ो_index];
	अगर (unlikely(monmsg->replied_msglim)) अणु
		monmsg->replied_msglim = 0;
		monmsg->msglim_reached = 0;
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpriv->पढ़ो_index = (monpriv->पढ़ो_index + 1) %
				      MON_MSGLIM;
		atomic_dec(&monpriv->पढ़ो_पढ़ोy);
		वापस ERR_PTR(-EOVERFLOW);
	पूर्ण
	वापस monmsg;
पूर्ण


/******************************************************************************
 *                               IUCV handler                                 *
 *****************************************************************************/
अटल व्योम mon_iucv_path_complete(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा mon_निजी *monpriv = path->निजी;

	atomic_set(&monpriv->iucv_connected, 1);
	wake_up(&mon_conn_रुको_queue);
पूर्ण

अटल व्योम mon_iucv_path_severed(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा mon_निजी *monpriv = path->निजी;

	pr_err("z/VM *MONITOR system service disconnected with rc=%i\n",
	       ipuser[0]);
	iucv_path_sever(path, शून्य);
	atomic_set(&monpriv->iucv_severed, 1);
	wake_up(&mon_conn_रुको_queue);
	wake_up_पूर्णांकerruptible(&mon_पढ़ो_रुको_queue);
पूर्ण

अटल व्योम mon_iucv_message_pending(काष्ठा iucv_path *path,
				     काष्ठा iucv_message *msg)
अणु
	काष्ठा mon_निजी *monpriv = path->निजी;

	स_नकल(&monpriv->msg_array[monpriv->ग_लिखो_index]->msg,
	       msg, माप(*msg));
	अगर (atomic_inc_वापस(&monpriv->msglim_count) == MON_MSGLIM) अणु
		pr_warn("The read queue for monitor data is full\n");
		monpriv->msg_array[monpriv->ग_लिखो_index]->msglim_reached = 1;
	पूर्ण
	monpriv->ग_लिखो_index = (monpriv->ग_लिखो_index + 1) % MON_MSGLIM;
	atomic_inc(&monpriv->पढ़ो_पढ़ोy);
	wake_up_पूर्णांकerruptible(&mon_पढ़ो_रुको_queue);
पूर्ण

अटल काष्ठा iucv_handler monपढ़ोer_iucv_handler = अणु
	.path_complete	 = mon_iucv_path_complete,
	.path_severed	 = mon_iucv_path_severed,
	.message_pending = mon_iucv_message_pending,
पूर्ण;

/******************************************************************************
 *                               file operations                              *
 *****************************************************************************/
अटल पूर्णांक mon_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mon_निजी *monpriv;
	पूर्णांक rc;

	/*
	 * only one user allowed
	 */
	rc = -EBUSY;
	अगर (test_and_set_bit(MON_IN_USE, &mon_in_use))
		जाओ out;

	rc = -ENOMEM;
	monpriv = mon_alloc_mem();
	अगर (!monpriv)
		जाओ out_use;

	/*
	 * Connect to *MONITOR service
	 */
	monpriv->path = iucv_path_alloc(MON_MSGLIM, IUCV_IPRMDATA, GFP_KERNEL);
	अगर (!monpriv->path)
		जाओ out_priv;
	rc = iucv_path_connect(monpriv->path, &monपढ़ोer_iucv_handler,
			       MON_SERVICE, शून्य, user_data_connect, monpriv);
	अगर (rc) अणु
		pr_err("Connecting to the z/VM *MONITOR system service "
		       "failed with rc=%i\n", rc);
		rc = -EIO;
		जाओ out_path;
	पूर्ण
	/*
	 * Wait क्रम connection confirmation
	 */
	रुको_event(mon_conn_रुको_queue,
		   atomic_पढ़ो(&monpriv->iucv_connected) ||
		   atomic_पढ़ो(&monpriv->iucv_severed));
	अगर (atomic_पढ़ो(&monpriv->iucv_severed)) अणु
		atomic_set(&monpriv->iucv_severed, 0);
		atomic_set(&monpriv->iucv_connected, 0);
		rc = -EIO;
		जाओ out_path;
	पूर्ण
	filp->निजी_data = monpriv;
	dev_set_drvdata(monपढ़ोer_device, monpriv);
	वापस nonseekable_खोलो(inode, filp);

out_path:
	iucv_path_मुक्त(monpriv->path);
out_priv:
	mon_मुक्त_mem(monpriv);
out_use:
	clear_bit(MON_IN_USE, &mon_in_use);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक mon_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक rc, i;
	काष्ठा mon_निजी *monpriv = filp->निजी_data;

	/*
	 * Close IUCV connection and unरेजिस्टर
	 */
	अगर (monpriv->path) अणु
		rc = iucv_path_sever(monpriv->path, user_data_sever);
		अगर (rc)
			pr_warn("Disconnecting the z/VM *MONITOR system service failed with rc=%i\n",
				rc);
		iucv_path_मुक्त(monpriv->path);
	पूर्ण

	atomic_set(&monpriv->iucv_severed, 0);
	atomic_set(&monpriv->iucv_connected, 0);
	atomic_set(&monpriv->पढ़ो_पढ़ोy, 0);
	atomic_set(&monpriv->msglim_count, 0);
	monpriv->ग_लिखो_index  = 0;
	monpriv->पढ़ो_index   = 0;
	dev_set_drvdata(monपढ़ोer_device, शून्य);

	क्रम (i = 0; i < MON_MSGLIM; i++)
		kमुक्त(monpriv->msg_array[i]);
	kमुक्त(monpriv);
	clear_bit(MON_IN_USE, &mon_in_use);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mon_पढ़ो(काष्ठा file *filp, अक्षर __user *data,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mon_निजी *monpriv = filp->निजी_data;
	काष्ठा mon_msg *monmsg;
	पूर्णांक ret;
	u32 mce_start;

	monmsg = mon_next_message(monpriv);
	अगर (IS_ERR(monmsg))
		वापस PTR_ERR(monmsg);

	अगर (!monmsg) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		ret = रुको_event_पूर्णांकerruptible(mon_पढ़ो_रुको_queue,
					atomic_पढ़ो(&monpriv->पढ़ो_पढ़ोy) ||
					atomic_पढ़ो(&monpriv->iucv_severed));
		अगर (ret)
			वापस ret;
		अगर (unlikely(atomic_पढ़ो(&monpriv->iucv_severed)))
			वापस -EIO;
		monmsg = monpriv->msg_array[monpriv->पढ़ो_index];
	पूर्ण

	अगर (!monmsg->pos)
		monmsg->pos = mon_mca_start(monmsg) + monmsg->mca_offset;
	अगर (mon_check_mca(monmsg))
		जाओ reply;

	/* पढ़ो monitor control element (12 bytes) first */
	mce_start = mon_mca_start(monmsg) + monmsg->mca_offset;
	अगर ((monmsg->pos >= mce_start) && (monmsg->pos < mce_start + 12)) अणु
		count = min(count, (माप_प्रकार) mce_start + 12 - monmsg->pos);
		ret = copy_to_user(data, (व्योम *) (अचिन्हित दीर्घ) monmsg->pos,
				   count);
		अगर (ret)
			वापस -EFAULT;
		monmsg->pos += count;
		अगर (monmsg->pos == mce_start + 12)
			monmsg->pos = mon_rec_start(monmsg);
		जाओ out_copy;
	पूर्ण

	/* पढ़ो records */
	अगर (monmsg->pos <= mon_rec_end(monmsg)) अणु
		count = min(count, (माप_प्रकार) mon_rec_end(monmsg) - monmsg->pos
					    + 1);
		ret = copy_to_user(data, (व्योम *) (अचिन्हित दीर्घ) monmsg->pos,
				   count);
		अगर (ret)
			वापस -EFAULT;
		monmsg->pos += count;
		अगर (monmsg->pos > mon_rec_end(monmsg))
			mon_next_mca(monmsg);
		जाओ out_copy;
	पूर्ण
reply:
	ret = mon_send_reply(monmsg, monpriv);
	वापस ret;

out_copy:
	*ppos += count;
	वापस count;
पूर्ण

अटल __poll_t mon_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *p)
अणु
	काष्ठा mon_निजी *monpriv = filp->निजी_data;

	poll_रुको(filp, &mon_पढ़ो_रुको_queue, p);
	अगर (unlikely(atomic_पढ़ो(&monpriv->iucv_severed)))
		वापस EPOLLERR;
	अगर (atomic_पढ़ो(&monpriv->पढ़ो_पढ़ोy))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mon_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = &mon_खोलो,
	.release = &mon_बंद,
	.पढ़ो    = &mon_पढ़ो,
	.poll    = &mon_poll,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice mon_dev = अणु
	.name       = "monreader",
	.fops       = &mon_fops,
	.minor      = MISC_DYNAMIC_MINOR,
पूर्ण;


/******************************************************************************
 *				suspend / resume			      *
 *****************************************************************************/
अटल पूर्णांक monपढ़ोer_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा mon_निजी *monpriv = dev_get_drvdata(dev);
	पूर्णांक rc;

	अगर (!monpriv)
		वापस 0;
	अगर (monpriv->path) अणु
		rc = iucv_path_sever(monpriv->path, user_data_sever);
		अगर (rc)
			pr_warn("Disconnecting the z/VM *MONITOR system service failed with rc=%i\n",
				rc);
		iucv_path_मुक्त(monpriv->path);
	पूर्ण
	atomic_set(&monpriv->iucv_severed, 0);
	atomic_set(&monpriv->iucv_connected, 0);
	atomic_set(&monpriv->पढ़ो_पढ़ोy, 0);
	atomic_set(&monpriv->msglim_count, 0);
	monpriv->ग_लिखो_index  = 0;
	monpriv->पढ़ो_index   = 0;
	monpriv->path = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक monपढ़ोer_thaw(काष्ठा device *dev)
अणु
	काष्ठा mon_निजी *monpriv = dev_get_drvdata(dev);
	पूर्णांक rc;

	अगर (!monpriv)
		वापस 0;
	rc = -ENOMEM;
	monpriv->path = iucv_path_alloc(MON_MSGLIM, IUCV_IPRMDATA, GFP_KERNEL);
	अगर (!monpriv->path)
		जाओ out;
	rc = iucv_path_connect(monpriv->path, &monपढ़ोer_iucv_handler,
			       MON_SERVICE, शून्य, user_data_connect, monpriv);
	अगर (rc) अणु
		pr_err("Connecting to the z/VM *MONITOR system service "
		       "failed with rc=%i\n", rc);
		जाओ out_path;
	पूर्ण
	रुको_event(mon_conn_रुको_queue,
		   atomic_पढ़ो(&monpriv->iucv_connected) ||
		   atomic_पढ़ो(&monpriv->iucv_severed));
	अगर (atomic_पढ़ो(&monpriv->iucv_severed))
		जाओ out_path;
	वापस 0;
out_path:
	rc = -EIO;
	iucv_path_मुक्त(monpriv->path);
	monpriv->path = शून्य;
out:
	atomic_set(&monpriv->iucv_severed, 1);
	वापस rc;
पूर्ण

अटल पूर्णांक monपढ़ोer_restore(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	segment_unload(mon_dcss_name);
	rc = segment_load(mon_dcss_name, SEGMENT_SHARED,
			  &mon_dcss_start, &mon_dcss_end);
	अगर (rc < 0) अणु
		segment_warning(rc, mon_dcss_name);
		panic("fatal monreader resume error: no monitor dcss\n");
	पूर्ण
	वापस monपढ़ोer_thaw(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops monपढ़ोer_pm_ops = अणु
	.मुक्तze  = monपढ़ोer_मुक्तze,
	.thaw	 = monपढ़ोer_thaw,
	.restore = monपढ़ोer_restore,
पूर्ण;

अटल काष्ठा device_driver monपढ़ोer_driver = अणु
	.name = "monreader",
	.bus  = &iucv_bus,
	.pm   = &monपढ़ोer_pm_ops,
पूर्ण;


/******************************************************************************
 *                              module init/निकास                              *
 *****************************************************************************/
अटल पूर्णांक __init mon_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM) अणु
		pr_err("The z/VM *MONITOR record device driver cannot be "
		       "loaded without z/VM\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Register with IUCV and connect to *MONITOR service
	 */
	rc = iucv_रेजिस्टर(&monपढ़ोer_iucv_handler, 1);
	अगर (rc) अणु
		pr_err("The z/VM *MONITOR record device driver failed to "
		       "register with IUCV\n");
		वापस rc;
	पूर्ण

	rc = driver_रेजिस्टर(&monपढ़ोer_driver);
	अगर (rc)
		जाओ out_iucv;
	monपढ़ोer_device = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (!monपढ़ोer_device) अणु
		rc = -ENOMEM;
		जाओ out_driver;
	पूर्ण

	dev_set_name(monपढ़ोer_device, "monreader-dev");
	monपढ़ोer_device->bus = &iucv_bus;
	monपढ़ोer_device->parent = iucv_root;
	monपढ़ोer_device->driver = &monपढ़ोer_driver;
	monपढ़ोer_device->release = (व्योम (*)(काष्ठा device *))kमुक्त;
	rc = device_रेजिस्टर(monपढ़ोer_device);
	अगर (rc) अणु
		put_device(monपढ़ोer_device);
		जाओ out_driver;
	पूर्ण

	rc = segment_type(mon_dcss_name);
	अगर (rc < 0) अणु
		segment_warning(rc, mon_dcss_name);
		जाओ out_device;
	पूर्ण
	अगर (rc != SEG_TYPE_SC) अणु
		pr_err("The specified *MONITOR DCSS %s does not have the "
		       "required type SC\n", mon_dcss_name);
		rc = -EINVAL;
		जाओ out_device;
	पूर्ण

	rc = segment_load(mon_dcss_name, SEGMENT_SHARED,
			  &mon_dcss_start, &mon_dcss_end);
	अगर (rc < 0) अणु
		segment_warning(rc, mon_dcss_name);
		rc = -EINVAL;
		जाओ out_device;
	पूर्ण
	dcss_mkname(mon_dcss_name, &user_data_connect[8]);

	/*
	 * misc_रेजिस्टर() has to be the last action in module_init(), because
	 * file operations will be available right after this.
	 */
	rc = misc_रेजिस्टर(&mon_dev);
	अगर (rc < 0 )
		जाओ out;
	वापस 0;

out:
	segment_unload(mon_dcss_name);
out_device:
	device_unरेजिस्टर(monपढ़ोer_device);
out_driver:
	driver_unरेजिस्टर(&monपढ़ोer_driver);
out_iucv:
	iucv_unरेजिस्टर(&monपढ़ोer_iucv_handler, 1);
	वापस rc;
पूर्ण

अटल व्योम __निकास mon_निकास(व्योम)
अणु
	segment_unload(mon_dcss_name);
	misc_deरेजिस्टर(&mon_dev);
	device_unरेजिस्टर(monपढ़ोer_device);
	driver_unरेजिस्टर(&monपढ़ोer_driver);
	iucv_unरेजिस्टर(&monपढ़ोer_iucv_handler, 1);
	वापस;
पूर्ण


module_init(mon_init);
module_निकास(mon_निकास);

module_param_string(mondcss, mon_dcss_name, 9, 0444);
MODULE_PARM_DESC(mondcss, "Name of DCSS segment to be used for *MONITOR "
		 "service, max. 8 chars. Default is MONDCSS");

MODULE_AUTHOR("Gerald Schaefer <geraldsc@de.ibm.com>");
MODULE_DESCRIPTION("Character device driver for reading z/VM "
		   "monitor service records.");
MODULE_LICENSE("GPL");
