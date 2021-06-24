<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	अक्षरacter device driver क्रम पढ़ोing z/VM प्रणाली service records
 *
 *
 *	Copyright IBM Corp. 2004, 2009
 *	अक्षरacter device driver क्रम पढ़ोing z/VM प्रणाली service records,
 *	Version 1.0
 *	Author(s): Xenia Tkatschow <xenia@us.ibm.com>
 *		   Stefan Weinhuber <wein@de.ibm.com>
 *
 */

#घोषणा KMSG_COMPONENT "vmlogrdr"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <net/iucv/iucv.h>
#समावेश <linux/kmod.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>

MODULE_AUTHOR
	("(C) 2004 IBM Corporation by Xenia Tkatschow (xenia@us.ibm.com)\n"
	 "                            Stefan Weinhuber (wein@de.ibm.com)");
MODULE_DESCRIPTION ("Character device driver for reading z/VM "
		    "system service records.");
MODULE_LICENSE("GPL");


/*
 * The size of the buffer क्रम iucv data transfer is one page,
 * but in addition to the data we पढ़ो from iucv we also
 * place an पूर्णांकeger and some अक्षरacters पूर्णांकo that buffer,
 * so the maximum size क्रम record data is a little less then
 * one page.
 */
#घोषणा NET_BUFFER_SIZE	(PAGE_SIZE - माप(पूर्णांक) - माप(FENCE))

/*
 * The elements that are concurrently accessed by bottom halves are
 * connection_established, iucv_path_severed, local_पूर्णांकerrupt_buffer
 * and receive_पढ़ोy. The first three can be रक्षित by
 * priv_lock.  receive_पढ़ोy is atomic, so it can be incremented and
 * decremented without holding a lock.
 * The variable dev_in_use needs to be रक्षित by the lock, since
 * it's a flag used by खोलो to make sure that the device is खोलोed only
 * by one user at the same समय.
 */
काष्ठा vmlogrdr_priv_t अणु
	अक्षर प्रणाली_service[8];
	अक्षर पूर्णांकernal_name[8];
	अक्षर recording_name[8];
	काष्ठा iucv_path *path;
	पूर्णांक connection_established;
	पूर्णांक iucv_path_severed;
	काष्ठा iucv_message local_पूर्णांकerrupt_buffer;
	atomic_t receive_पढ़ोy;
	पूर्णांक minor_num;
	अक्षर * buffer;
	अक्षर * current_position;
	पूर्णांक reमुख्यing;
	uदीर्घ residual_length;
	पूर्णांक buffer_मुक्त;
	पूर्णांक dev_in_use; /* 1: alपढ़ोy खोलोed, 0: not खोलोed*/
	spinlock_t priv_lock;
	काष्ठा device  *device;
	काष्ठा device  *class_device;
	पूर्णांक स्वतःrecording;
	पूर्णांक स्वतःpurge;
पूर्ण;


/*
 * File operation काष्ठाure क्रम vmlogrdr devices
 */
अटल पूर्णांक vmlogrdr_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक vmlogrdr_release(काष्ठा inode *, काष्ठा file *);
अटल sमाप_प्रकार vmlogrdr_पढ़ो (काष्ठा file *filp, अक्षर __user *data,
			      माप_प्रकार count, loff_t * ppos);

अटल स्थिर काष्ठा file_operations vmlogrdr_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = vmlogrdr_खोलो,
	.release = vmlogrdr_release,
	.पढ़ो    = vmlogrdr_पढ़ो,
	.llseek  = no_llseek,
पूर्ण;


अटल व्योम vmlogrdr_iucv_path_complete(काष्ठा iucv_path *, u8 *ipuser);
अटल व्योम vmlogrdr_iucv_path_severed(काष्ठा iucv_path *, u8 *ipuser);
अटल व्योम vmlogrdr_iucv_message_pending(काष्ठा iucv_path *,
					  काष्ठा iucv_message *);


अटल काष्ठा iucv_handler vmlogrdr_iucv_handler = अणु
	.path_complete	 = vmlogrdr_iucv_path_complete,
	.path_severed	 = vmlogrdr_iucv_path_severed,
	.message_pending = vmlogrdr_iucv_message_pending,
पूर्ण;


अटल DECLARE_WAIT_QUEUE_HEAD(conn_रुको_queue);
अटल DECLARE_WAIT_QUEUE_HEAD(पढ़ो_रुको_queue);

/*
 * poपूर्णांकer to प्रणाली service निजी काष्ठाure
 * minor number 0 --> logrec
 * minor number 1 --> account
 * minor number 2 --> symptom
 */

अटल काष्ठा vmlogrdr_priv_t sys_ser[] = अणु
	अणु .प्रणाली_service = "*LOGREC ",
	  .पूर्णांकernal_name  = "logrec",
	  .recording_name = "EREP",
	  .minor_num      = 0,
	  .buffer_मुक्त    = 1,
	  .priv_lock	  = __SPIN_LOCK_UNLOCKED(sys_ser[0].priv_lock),
	  .स्वतःrecording  = 1,
	  .स्वतःpurge      = 1,
	पूर्ण,
	अणु .प्रणाली_service = "*ACCOUNT",
	  .पूर्णांकernal_name  = "account",
	  .recording_name = "ACCOUNT",
	  .minor_num      = 1,
	  .buffer_मुक्त    = 1,
	  .priv_lock	  = __SPIN_LOCK_UNLOCKED(sys_ser[1].priv_lock),
	  .स्वतःrecording  = 1,
	  .स्वतःpurge      = 1,
	पूर्ण,
	अणु .प्रणाली_service = "*SYMPTOM",
	  .पूर्णांकernal_name  = "symptom",
	  .recording_name = "SYMPTOM",
	  .minor_num      = 2,
	  .buffer_मुक्त    = 1,
	  .priv_lock	  = __SPIN_LOCK_UNLOCKED(sys_ser[2].priv_lock),
	  .स्वतःrecording  = 1,
	  .स्वतःpurge      = 1,
	पूर्ण
पूर्ण;

#घोषणा MAXMINOR  ARRAY_SIZE(sys_ser)

अटल अक्षर FENCE[] = अणु"EOR"पूर्ण;
अटल पूर्णांक vmlogrdr_major = 0;
अटल काष्ठा cdev  *vmlogrdr_cdev = शून्य;
अटल पूर्णांक recording_class_AB;


अटल व्योम vmlogrdr_iucv_path_complete(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा vmlogrdr_priv_t * logptr = path->निजी;

	spin_lock(&logptr->priv_lock);
	logptr->connection_established = 1;
	spin_unlock(&logptr->priv_lock);
	wake_up(&conn_रुको_queue);
पूर्ण


अटल व्योम vmlogrdr_iucv_path_severed(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा vmlogrdr_priv_t * logptr = path->निजी;
	u8 reason = (u8) ipuser[8];

	pr_err("vmlogrdr: connection severed with reason %i\n", reason);

	iucv_path_sever(path, शून्य);
	kमुक्त(path);
	logptr->path = शून्य;

	spin_lock(&logptr->priv_lock);
	logptr->connection_established = 0;
	logptr->iucv_path_severed = 1;
	spin_unlock(&logptr->priv_lock);

	wake_up(&conn_रुको_queue);
	/* just in हाल we're sleeping रुकोing क्रम a record */
	wake_up_पूर्णांकerruptible(&पढ़ो_रुको_queue);
पूर्ण


अटल व्योम vmlogrdr_iucv_message_pending(काष्ठा iucv_path *path,
					  काष्ठा iucv_message *msg)
अणु
	काष्ठा vmlogrdr_priv_t * logptr = path->निजी;

	/*
	 * This function is the bottom half so it should be quick.
	 * Copy the बाह्यal पूर्णांकerrupt data पूर्णांकo our local eib and increment
	 * the usage count
	 */
	spin_lock(&logptr->priv_lock);
	स_नकल(&logptr->local_पूर्णांकerrupt_buffer, msg, माप(*msg));
	atomic_inc(&logptr->receive_पढ़ोy);
	spin_unlock(&logptr->priv_lock);
	wake_up_पूर्णांकerruptible(&पढ़ो_रुको_queue);
पूर्ण


अटल पूर्णांक vmlogrdr_get_recording_class_AB(व्योम)
अणु
	अटल स्थिर अक्षर cp_command[] = "QUERY COMMAND RECORDING ";
	अक्षर cp_response[80];
	अक्षर *tail;
	पूर्णांक len,i;

	cpcmd(cp_command, cp_response, माप(cp_response), शून्य);
	len = strnlen(cp_response,माप(cp_response));
	// now the parsing
	tail=strnchr(cp_response,len,'=');
	अगर (!tail)
		वापस 0;
	tail++;
	अगर (!म_भेदन("ANY",tail,3))
		वापस 1;
	अगर (!म_भेदन("NONE",tail,4))
		वापस 0;
	/*
	 * expect comma separated list of classes here, अगर one of them
	 * is A or B वापस 1 otherwise 0
	 */
        क्रम (i=tail-cp_response; i<len; i++)
		अगर ( cp_response[i]=='A' || cp_response[i]=='B' )
			वापस 1;
	वापस 0;
पूर्ण


अटल पूर्णांक vmlogrdr_recording(काष्ठा vmlogrdr_priv_t * logptr,
			      पूर्णांक action, पूर्णांक purge)
अणु

	अक्षर cp_command[80];
	अक्षर cp_response[160];
	अक्षर *onoff, *qid_string;
	पूर्णांक rc;

	onoff = ((action == 1) ? "ON" : "OFF");
	qid_string = ((recording_class_AB == 1) ? " QID * " : "");

	/*
	 * The recording commands needs to be called with option QID
	 * क्रम guests that have previlege classes A or B.
	 * Purging has to be करोne as separate step, because recording
	 * can't be चयनed on as दीर्घ as records are on the queue.
	 * Doing both at the same समय करोesn't work.
	 */
	अगर (purge && (action == 1)) अणु
		स_रखो(cp_command, 0x00, माप(cp_command));
		स_रखो(cp_response, 0x00, माप(cp_response));
		snम_लिखो(cp_command, माप(cp_command),
			 "RECORDING %s PURGE %s",
			 logptr->recording_name,
			 qid_string);
		cpcmd(cp_command, cp_response, माप(cp_response), शून्य);
	पूर्ण

	स_रखो(cp_command, 0x00, माप(cp_command));
	स_रखो(cp_response, 0x00, माप(cp_response));
	snम_लिखो(cp_command, माप(cp_command), "RECORDING %s %s %s",
		logptr->recording_name,
		onoff,
		qid_string);
	cpcmd(cp_command, cp_response, माप(cp_response), शून्य);
	/* The recording command will usually answer with 'Command complete'
	 * on success, but when the specअगरic service was never connected
	 * beक्रमe then there might be an additional inक्रमmational message
	 * 'HCPCRC8072I Recording entry not found' beक्रमe the
	 * 'Command complete'. So I use म_माला rather then the म_भेदन.
	 */
	अगर (म_माला(cp_response,"Command complete"))
		rc = 0;
	अन्यथा
		rc = -EIO;
	/*
	 * If we turn recording off, we have to purge any reमुख्यing records
	 * afterwards, as a large number of queued records may impact z/VM
	 * perक्रमmance.
	 */
	अगर (purge && (action == 0)) अणु
		स_रखो(cp_command, 0x00, माप(cp_command));
		स_रखो(cp_response, 0x00, माप(cp_response));
		snम_लिखो(cp_command, माप(cp_command),
			 "RECORDING %s PURGE %s",
			 logptr->recording_name,
			 qid_string);
		cpcmd(cp_command, cp_response, माप(cp_response), शून्य);
	पूर्ण

	वापस rc;
पूर्ण


अटल पूर्णांक vmlogrdr_खोलो (काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक dev_num = 0;
	काष्ठा vmlogrdr_priv_t * logptr = शून्य;
	पूर्णांक connect_rc = 0;
	पूर्णांक ret;

	dev_num = iminor(inode);
	अगर (dev_num >= MAXMINOR)
		वापस -ENODEV;
	logptr = &sys_ser[dev_num];

	/*
	 * only allow क्रम blocking पढ़ोs to be खोलो
	 */
	अगर (filp->f_flags & O_NONBLOCK)
		वापस -EOPNOTSUPP;

	/* Besure this device hasn't alपढ़ोy been खोलोed */
	spin_lock_bh(&logptr->priv_lock);
	अगर (logptr->dev_in_use)	अणु
		spin_unlock_bh(&logptr->priv_lock);
		वापस -EBUSY;
	पूर्ण
	logptr->dev_in_use = 1;
	logptr->connection_established = 0;
	logptr->iucv_path_severed = 0;
	atomic_set(&logptr->receive_पढ़ोy, 0);
	logptr->buffer_मुक्त = 1;
	spin_unlock_bh(&logptr->priv_lock);

	/* set the file options */
	filp->निजी_data = logptr;

	/* start recording क्रम this service*/
	अगर (logptr->स्वतःrecording) अणु
		ret = vmlogrdr_recording(logptr,1,logptr->स्वतःpurge);
		अगर (ret)
			pr_warn("vmlogrdr: failed to start recording automatically\n");
	पूर्ण

	/* create connection to the प्रणाली service */
	logptr->path = iucv_path_alloc(10, 0, GFP_KERNEL);
	अगर (!logptr->path)
		जाओ out_dev;
	connect_rc = iucv_path_connect(logptr->path, &vmlogrdr_iucv_handler,
				       logptr->प्रणाली_service, शून्य, शून्य,
				       logptr);
	अगर (connect_rc) अणु
		pr_err("vmlogrdr: iucv connection to %s "
		       "failed with rc %i \n",
		       logptr->प्रणाली_service, connect_rc);
		जाओ out_path;
	पूर्ण

	/* We've issued the connect and now we must रुको क्रम a
	 * ConnectionComplete or ConnectinSevered Interrupt
	 * beक्रमe we can जारी to process.
	 */
	रुको_event(conn_रुको_queue, (logptr->connection_established)
		   || (logptr->iucv_path_severed));
	अगर (logptr->iucv_path_severed)
		जाओ out_record;
	nonseekable_खोलो(inode, filp);
	वापस 0;

out_record:
	अगर (logptr->स्वतःrecording)
		vmlogrdr_recording(logptr,0,logptr->स्वतःpurge);
out_path:
	kमुक्त(logptr->path);	/* kमुक्त(शून्य) is ok. */
	logptr->path = शून्य;
out_dev:
	logptr->dev_in_use = 0;
	वापस -EIO;
पूर्ण


अटल पूर्णांक vmlogrdr_release (काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	काष्ठा vmlogrdr_priv_t * logptr = filp->निजी_data;

	iucv_path_sever(logptr->path, शून्य);
	kमुक्त(logptr->path);
	logptr->path = शून्य;
	अगर (logptr->स्वतःrecording) अणु
		ret = vmlogrdr_recording(logptr,0,logptr->स्वतःpurge);
		अगर (ret)
			pr_warn("vmlogrdr: failed to stop recording automatically\n");
	पूर्ण
	logptr->dev_in_use = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक vmlogrdr_receive_data(काष्ठा vmlogrdr_priv_t *priv)
अणु
	पूर्णांक rc, *temp;
	/* we need to keep track of two data sizes here:
	 * The number of bytes we need to receive from iucv and
	 * the total number of bytes we actually ग_लिखो पूर्णांकo the buffer.
	 */
	पूर्णांक user_data_count, iucv_data_count;
	अक्षर * buffer;

	अगर (atomic_पढ़ो(&priv->receive_पढ़ोy)) अणु
		spin_lock_bh(&priv->priv_lock);
		अगर (priv->residual_length)अणु
			/* receive second half of a record */
			iucv_data_count = priv->residual_length;
			user_data_count = 0;
			buffer = priv->buffer;
		पूर्ण अन्यथा अणु
			/* receive a new record:
			 * We need to वापस the total length of the record
                         * + size of FENCE in the first 4 bytes of the buffer.
		         */
			iucv_data_count = priv->local_पूर्णांकerrupt_buffer.length;
			user_data_count = माप(पूर्णांक);
			temp = (पूर्णांक*)priv->buffer;
			*temp= iucv_data_count + माप(FENCE);
			buffer = priv->buffer + माप(पूर्णांक);
		पूर्ण
		/*
		 * If the record is bigger than our buffer, we receive only
		 * a part of it. We can get the rest later.
		 */
		अगर (iucv_data_count > NET_BUFFER_SIZE)
			iucv_data_count = NET_BUFFER_SIZE;
		rc = iucv_message_receive(priv->path,
					  &priv->local_पूर्णांकerrupt_buffer,
					  0, buffer, iucv_data_count,
					  &priv->residual_length);
		spin_unlock_bh(&priv->priv_lock);
		/* An rc of 5 indicates that the record was bigger than
		 * the buffer, which is OK क्रम us. A 9 indicates that the
		 * record was purged beक्रम we could receive it.
		 */
		अगर (rc == 5)
			rc = 0;
		अगर (rc == 9)
			atomic_set(&priv->receive_पढ़ोy, 0);
	पूर्ण अन्यथा अणु
		rc = 1;
	पूर्ण
	अगर (!rc) अणु
		priv->buffer_मुक्त = 0;
 		user_data_count += iucv_data_count;
		priv->current_position = priv->buffer;
		अगर (priv->residual_length == 0)अणु
			/* the whole record has been captured,
			 * now add the fence */
			atomic_dec(&priv->receive_पढ़ोy);
			buffer = priv->buffer + user_data_count;
			स_नकल(buffer, FENCE, माप(FENCE));
			user_data_count += माप(FENCE);
		पूर्ण
		priv->reमुख्यing = user_data_count;
	पूर्ण

	वापस rc;
पूर्ण


अटल sमाप_प्रकार vmlogrdr_पढ़ो(काष्ठा file *filp, अक्षर __user *data,
			     माप_प्रकार count, loff_t * ppos)
अणु
	पूर्णांक rc;
	काष्ठा vmlogrdr_priv_t * priv = filp->निजी_data;

	जबतक (priv->buffer_मुक्त) अणु
		rc = vmlogrdr_receive_data(priv);
		अगर (rc) अणु
			rc = रुको_event_पूर्णांकerruptible(पढ़ो_रुको_queue,
					atomic_पढ़ो(&priv->receive_पढ़ोy));
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	/* copy only up to end of record */
	अगर (count > priv->reमुख्यing)
		count = priv->reमुख्यing;

	अगर (copy_to_user(data, priv->current_position, count))
		वापस -EFAULT;

	*ppos += count;
	priv->current_position += count;
	priv->reमुख्यing -= count;

	/* अगर all data has been transferred, set buffer मुक्त */
	अगर (priv->reमुख्यing == 0)
		priv->buffer_मुक्त = 1;

	वापस count;
पूर्ण

अटल sमाप_प्रकार vmlogrdr_स्वतःpurge_store(काष्ठा device * dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर * buf, माप_प्रकार count)
अणु
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	sमाप_प्रकार ret = count;

	चयन (buf[0]) अणु
	हाल '0':
		priv->स्वतःpurge=0;
		अवरोध;
	हाल '1':
		priv->स्वतःpurge=1;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण


अटल sमाप_प्रकार vmlogrdr_स्वतःpurge_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", priv->स्वतःpurge);
पूर्ण


अटल DEVICE_ATTR(स्वतःpurge, 0644, vmlogrdr_स्वतःpurge_show,
		   vmlogrdr_स्वतःpurge_store);


अटल sमाप_प्रकार vmlogrdr_purge_store(काष्ठा device * dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर * buf, माप_प्रकार count)
अणु

	अक्षर cp_command[80];
	अक्षर cp_response[80];
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);

	अगर (buf[0] != '1')
		वापस -EINVAL;

	स_रखो(cp_command, 0x00, माप(cp_command));
	स_रखो(cp_response, 0x00, माप(cp_response));

        /*
	 * The recording command needs to be called with option QID
	 * क्रम guests that have previlege classes A or B.
	 * Other guests will not recognize the command and we have to
	 * issue the same command without the QID parameter.
	 */

	अगर (recording_class_AB)
		snम_लिखो(cp_command, माप(cp_command),
			 "RECORDING %s PURGE QID * ",
			 priv->recording_name);
	अन्यथा
		snम_लिखो(cp_command, माप(cp_command),
			 "RECORDING %s PURGE ",
			 priv->recording_name);

	cpcmd(cp_command, cp_response, माप(cp_response), शून्य);

	वापस count;
पूर्ण


अटल DEVICE_ATTR(purge, 0200, शून्य, vmlogrdr_purge_store);


अटल sमाप_प्रकार vmlogrdr_स्वतःrecording_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	sमाप_प्रकार ret = count;

	चयन (buf[0]) अणु
	हाल '0':
		priv->स्वतःrecording=0;
		अवरोध;
	हाल '1':
		priv->स्वतःrecording=1;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण


अटल sमाप_प्रकार vmlogrdr_स्वतःrecording_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", priv->स्वतःrecording);
पूर्ण


अटल DEVICE_ATTR(स्वतःrecording, 0644, vmlogrdr_स्वतःrecording_show,
		   vmlogrdr_स्वतःrecording_store);


अटल sमाप_प्रकार vmlogrdr_recording_store(काष्ठा device * dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर * buf, माप_प्रकार count)
अणु
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	sमाप_प्रकार ret;

	चयन (buf[0]) अणु
	हाल '0':
		ret = vmlogrdr_recording(priv,0,0);
		अवरोध;
	हाल '1':
		ret = vmlogrdr_recording(priv,1,0);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		वापस ret;
	अन्यथा
		वापस count;

पूर्ण


अटल DEVICE_ATTR(recording, 0200, शून्य, vmlogrdr_recording_store);


अटल sमाप_प्रकार recording_status_show(काष्ठा device_driver *driver, अक्षर *buf)
अणु
	अटल स्थिर अक्षर cp_command[] = "QUERY RECORDING ";
	पूर्णांक len;

	cpcmd(cp_command, buf, 4096, शून्य);
	len = म_माप(buf);
	वापस len;
पूर्ण
अटल DRIVER_ATTR_RO(recording_status);
अटल काष्ठा attribute *vmlogrdr_drv_attrs[] = अणु
	&driver_attr_recording_status.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group vmlogrdr_drv_attr_group = अणु
	.attrs = vmlogrdr_drv_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *vmlogrdr_drv_attr_groups[] = अणु
	&vmlogrdr_drv_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *vmlogrdr_attrs[] = अणु
	&dev_attr_स्वतःpurge.attr,
	&dev_attr_purge.attr,
	&dev_attr_स्वतःrecording.attr,
	&dev_attr_recording.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group vmlogrdr_attr_group = अणु
	.attrs = vmlogrdr_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *vmlogrdr_attr_groups[] = अणु
	&vmlogrdr_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक vmlogrdr_pm_prepare(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा vmlogrdr_priv_t *priv = dev_get_drvdata(dev);

	rc = 0;
	अगर (priv) अणु
		spin_lock_bh(&priv->priv_lock);
		अगर (priv->dev_in_use)
			rc = -EBUSY;
		spin_unlock_bh(&priv->priv_lock);
	पूर्ण
	अगर (rc)
		pr_err("vmlogrdr: device %s is busy. Refuse to suspend.\n",
		       dev_name(dev));
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा dev_pm_ops vmlogrdr_pm_ops = अणु
	.prepare = vmlogrdr_pm_prepare,
पूर्ण;

अटल काष्ठा class *vmlogrdr_class;
अटल काष्ठा device_driver vmlogrdr_driver = अणु
	.name = "vmlogrdr",
	.bus  = &iucv_bus,
	.pm = &vmlogrdr_pm_ops,
	.groups = vmlogrdr_drv_attr_groups,
पूर्ण;

अटल पूर्णांक vmlogrdr_रेजिस्टर_driver(व्योम)
अणु
	पूर्णांक ret;

	/* Register with iucv driver */
	ret = iucv_रेजिस्टर(&vmlogrdr_iucv_handler, 1);
	अगर (ret)
		जाओ out;

	ret = driver_रेजिस्टर(&vmlogrdr_driver);
	अगर (ret)
		जाओ out_iucv;

	vmlogrdr_class = class_create(THIS_MODULE, "vmlogrdr");
	अगर (IS_ERR(vmlogrdr_class)) अणु
		ret = PTR_ERR(vmlogrdr_class);
		vmlogrdr_class = शून्य;
		जाओ out_driver;
	पूर्ण
	वापस 0;

out_driver:
	driver_unरेजिस्टर(&vmlogrdr_driver);
out_iucv:
	iucv_unरेजिस्टर(&vmlogrdr_iucv_handler, 1);
out:
	वापस ret;
पूर्ण


अटल व्योम vmlogrdr_unरेजिस्टर_driver(व्योम)
अणु
	class_destroy(vmlogrdr_class);
	vmlogrdr_class = शून्य;
	driver_unरेजिस्टर(&vmlogrdr_driver);
	iucv_unरेजिस्टर(&vmlogrdr_iucv_handler, 1);
पूर्ण


अटल पूर्णांक vmlogrdr_रेजिस्टर_device(काष्ठा vmlogrdr_priv_t *priv)
अणु
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (dev) अणु
		dev_set_name(dev, "%s", priv->पूर्णांकernal_name);
		dev->bus = &iucv_bus;
		dev->parent = iucv_root;
		dev->driver = &vmlogrdr_driver;
		dev->groups = vmlogrdr_attr_groups;
		dev_set_drvdata(dev, priv);
		/*
		 * The release function could be called after the
		 * module has been unloaded. It's _only_ task is to
		 * मुक्त the काष्ठा. Thereक्रमe, we specअगरy kमुक्त()
		 * directly here. (Probably a little bit obfuscating
		 * but legiसमय ...).
		 */
		dev->release = (व्योम (*)(काष्ठा device *))kमुक्त;
	पूर्ण अन्यथा
		वापस -ENOMEM;
	ret = device_रेजिस्टर(dev);
	अगर (ret) अणु
		put_device(dev);
		वापस ret;
	पूर्ण

	priv->class_device = device_create(vmlogrdr_class, dev,
					   MKDEV(vmlogrdr_major,
						 priv->minor_num),
					   priv, "%s", dev_name(dev));
	अगर (IS_ERR(priv->class_device)) अणु
		ret = PTR_ERR(priv->class_device);
		priv->class_device=शून्य;
		device_unरेजिस्टर(dev);
		वापस ret;
	पूर्ण
	priv->device = dev;
	वापस 0;
पूर्ण


अटल पूर्णांक vmlogrdr_unरेजिस्टर_device(काष्ठा vmlogrdr_priv_t *priv)
अणु
	device_destroy(vmlogrdr_class, MKDEV(vmlogrdr_major, priv->minor_num));
	अगर (priv->device != शून्य) अणु
		device_unरेजिस्टर(priv->device);
		priv->device=शून्य;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक vmlogrdr_रेजिस्टर_cdev(dev_t dev)
अणु
	पूर्णांक rc = 0;
	vmlogrdr_cdev = cdev_alloc();
	अगर (!vmlogrdr_cdev) अणु
		वापस -ENOMEM;
	पूर्ण
	vmlogrdr_cdev->owner = THIS_MODULE;
	vmlogrdr_cdev->ops = &vmlogrdr_fops;
	rc = cdev_add(vmlogrdr_cdev, dev, MAXMINOR);
	अगर (!rc)
		वापस 0;

	// cleanup: cdev is not fully रेजिस्टरed, no cdev_del here!
	kobject_put(&vmlogrdr_cdev->kobj);
	vmlogrdr_cdev=शून्य;
	वापस rc;
पूर्ण


अटल व्योम vmlogrdr_cleanup(व्योम)
अणु
        पूर्णांक i;

	अगर (vmlogrdr_cdev) अणु
		cdev_del(vmlogrdr_cdev);
		vmlogrdr_cdev=शून्य;
	पूर्ण
	क्रम (i=0; i < MAXMINOR; ++i ) अणु
		vmlogrdr_unरेजिस्टर_device(&sys_ser[i]);
		मुक्त_page((अचिन्हित दीर्घ)sys_ser[i].buffer);
	पूर्ण
	vmlogrdr_unरेजिस्टर_driver();
	अगर (vmlogrdr_major) अणु
		unरेजिस्टर_chrdev_region(MKDEV(vmlogrdr_major, 0), MAXMINOR);
		vmlogrdr_major=0;
	पूर्ण
पूर्ण


अटल पूर्णांक __init vmlogrdr_init(व्योम)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	dev_t dev;

	अगर (! MACHINE_IS_VM) अणु
		pr_err("not running under VM, driver not loaded.\n");
		वापस -ENODEV;
	पूर्ण

        recording_class_AB = vmlogrdr_get_recording_class_AB();

	rc = alloc_chrdev_region(&dev, 0, MAXMINOR, "vmlogrdr");
	अगर (rc)
		वापस rc;
	vmlogrdr_major = MAJOR(dev);

	rc=vmlogrdr_रेजिस्टर_driver();
	अगर (rc)
		जाओ cleanup;

	क्रम (i=0; i < MAXMINOR; ++i ) अणु
		sys_ser[i].buffer = (अक्षर *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
		अगर (!sys_ser[i].buffer) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
		sys_ser[i].current_position = sys_ser[i].buffer;
		rc=vmlogrdr_रेजिस्टर_device(&sys_ser[i]);
		अगर (rc)
			अवरोध;
	पूर्ण
	अगर (rc)
		जाओ cleanup;

	rc = vmlogrdr_रेजिस्टर_cdev(dev);
	अगर (rc)
		जाओ cleanup;
	वापस 0;

cleanup:
	vmlogrdr_cleanup();
	वापस rc;
पूर्ण


अटल व्योम __निकास vmlogrdr_निकास(व्योम)
अणु
	vmlogrdr_cleanup();
	वापस;
पूर्ण


module_init(vmlogrdr_init);
module_निकास(vmlogrdr_निकास);
