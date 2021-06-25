<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_devपूर्णांकf.c
 *
 * Linux device पूर्णांकerface क्रम the IPMI message handler.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/compat.h>

काष्ठा ipmi_file_निजी
अणु
	काष्ठा ipmi_user     *user;
	spinlock_t           recv_msg_lock;
	काष्ठा list_head     recv_msgs;
	काष्ठा fasync_काष्ठा *fasync_queue;
	रुको_queue_head_t    रुको;
	काष्ठा mutex	     recv_mutex;
	पूर्णांक                  शेष_retries;
	अचिन्हित पूर्णांक         शेष_retry_समय_ms;
पूर्ण;

अटल व्योम file_receive_handler(काष्ठा ipmi_recv_msg *msg,
				 व्योम                 *handler_data)
अणु
	काष्ठा ipmi_file_निजी *priv = handler_data;
	पूर्णांक                      was_empty;
	अचिन्हित दीर्घ            flags;

	spin_lock_irqsave(&priv->recv_msg_lock, flags);
	was_empty = list_empty(&priv->recv_msgs);
	list_add_tail(&msg->link, &priv->recv_msgs);
	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);

	अगर (was_empty) अणु
		wake_up_पूर्णांकerruptible(&priv->रुको);
		समाप्त_fasync(&priv->fasync_queue, SIGIO, POLL_IN);
	पूर्ण
पूर्ण

अटल __poll_t ipmi_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा ipmi_file_निजी *priv = file->निजी_data;
	__poll_t             mask = 0;
	अचिन्हित दीर्घ            flags;

	poll_रुको(file, &priv->रुको, रुको);

	spin_lock_irqsave(&priv->recv_msg_lock, flags);

	अगर (!list_empty(&priv->recv_msgs))
		mask |= (EPOLLIN | EPOLLRDNORM);

	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);

	वापस mask;
पूर्ण

अटल पूर्णांक ipmi_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा ipmi_file_निजी *priv = file->निजी_data;

	वापस fasync_helper(fd, file, on, &priv->fasync_queue);
पूर्ण

अटल स्थिर काष्ठा ipmi_user_hndl ipmi_hndlrs =
अणु
	.ipmi_recv_hndl	= file_receive_handler,
पूर्ण;

अटल पूर्णांक ipmi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक                      अगर_num = iminor(inode);
	पूर्णांक                      rv;
	काष्ठा ipmi_file_निजी *priv;

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	rv = ipmi_create_user(अगर_num,
			      &ipmi_hndlrs,
			      priv,
			      &priv->user);
	अगर (rv) अणु
		kमुक्त(priv);
		जाओ out;
	पूर्ण

	file->निजी_data = priv;

	spin_lock_init(&priv->recv_msg_lock);
	INIT_LIST_HEAD(&priv->recv_msgs);
	init_रुकोqueue_head(&priv->रुको);
	priv->fasync_queue = शून्य;
	mutex_init(&priv->recv_mutex);

	/* Use the low-level शेषs. */
	priv->शेष_retries = -1;
	priv->शेष_retry_समय_ms = 0;

out:
	वापस rv;
पूर्ण

अटल पूर्णांक ipmi_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ipmi_file_निजी *priv = file->निजी_data;
	पूर्णांक                      rv;
	काष्ठा ipmi_recv_msg *msg, *next;

	rv = ipmi_destroy_user(priv->user);
	अगर (rv)
		वापस rv;

	list_क्रम_each_entry_safe(msg, next, &priv->recv_msgs, link)
		ipmi_मुक्त_recv_msg(msg);

	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक handle_send_req(काष्ठा ipmi_user *user,
			   काष्ठा ipmi_req *req,
			   पूर्णांक             retries,
			   अचिन्हित पूर्णांक    retry_समय_ms)
अणु
	पूर्णांक              rv;
	काष्ठा ipmi_addr addr;
	काष्ठा kernel_ipmi_msg msg;

	अगर (req->addr_len > माप(काष्ठा ipmi_addr))
		वापस -EINVAL;

	अगर (copy_from_user(&addr, req->addr, req->addr_len))
		वापस -EFAULT;

	msg.netfn = req->msg.netfn;
	msg.cmd = req->msg.cmd;
	msg.data_len = req->msg.data_len;
	msg.data = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!msg.data)
		वापस -ENOMEM;

	/* From here out we cannot वापस, we must jump to "out" क्रम
	   error निकासs to मुक्त msgdata. */

	rv = ipmi_validate_addr(&addr, req->addr_len);
	अगर (rv)
		जाओ out;

	अगर (req->msg.data != शून्य) अणु
		अगर (req->msg.data_len > IPMI_MAX_MSG_LENGTH) अणु
			rv = -EMSGSIZE;
			जाओ out;
		पूर्ण

		अगर (copy_from_user(msg.data,
				   req->msg.data,
				   req->msg.data_len)) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg.data_len = 0;
	पूर्ण

	rv = ipmi_request_समय_रखो(user,
				  &addr,
				  req->msgid,
				  &msg,
				  शून्य,
				  0,
				  retries,
				  retry_समय_ms);
 out:
	kमुक्त(msg.data);
	वापस rv;
पूर्ण

अटल पूर्णांक handle_recv(काष्ठा ipmi_file_निजी *priv,
			bool trunc, काष्ठा ipmi_recv *rsp,
			पूर्णांक (*copyout)(काष्ठा ipmi_recv *, व्योम __user *),
			व्योम __user *to)
अणु
	पूर्णांक              addr_len;
	काष्ठा list_head *entry;
	काष्ठा ipmi_recv_msg  *msg;
	अचिन्हित दीर्घ    flags;
	पूर्णांक rv = 0, rv2 = 0;

	/* We claim a mutex because we करोn't want two
	   users getting something from the queue at a समय.
	   Since we have to release the spinlock beक्रमe we can
	   copy the data to the user, it's possible another
	   user will grab something from the queue, too.  Then
	   the messages might get out of order अगर something
	   fails and the message माला_लो put back onto the
	   queue.  This mutex prevents that problem. */
	mutex_lock(&priv->recv_mutex);

	/* Grab the message off the list. */
	spin_lock_irqsave(&priv->recv_msg_lock, flags);
	अगर (list_empty(&(priv->recv_msgs))) अणु
		spin_unlock_irqrestore(&priv->recv_msg_lock, flags);
		rv = -EAGAIN;
		जाओ recv_err;
	पूर्ण
	entry = priv->recv_msgs.next;
	msg = list_entry(entry, काष्ठा ipmi_recv_msg, link);
	list_del(entry);
	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);

	addr_len = ipmi_addr_length(msg->addr.addr_type);
	अगर (rsp->addr_len < addr_len) अणु
		rv = -EINVAL;
		जाओ recv_putback_on_err;
	पूर्ण

	अगर (copy_to_user(rsp->addr, &msg->addr, addr_len)) अणु
		rv = -EFAULT;
		जाओ recv_putback_on_err;
	पूर्ण
	rsp->addr_len = addr_len;

	rsp->recv_type = msg->recv_type;
	rsp->msgid = msg->msgid;
	rsp->msg.netfn = msg->msg.netfn;
	rsp->msg.cmd = msg->msg.cmd;

	अगर (msg->msg.data_len > 0) अणु
		अगर (rsp->msg.data_len < msg->msg.data_len) अणु
			rv2 = -EMSGSIZE;
			अगर (trunc)
				msg->msg.data_len = rsp->msg.data_len;
			अन्यथा
				जाओ recv_putback_on_err;
		पूर्ण

		अगर (copy_to_user(rsp->msg.data,
				 msg->msg.data,
				 msg->msg.data_len)) अणु
			rv = -EFAULT;
			जाओ recv_putback_on_err;
		पूर्ण
		rsp->msg.data_len = msg->msg.data_len;
	पूर्ण अन्यथा अणु
		rsp->msg.data_len = 0;
	पूर्ण

	rv = copyout(rsp, to);
	अगर (rv)
		जाओ recv_putback_on_err;

	mutex_unlock(&priv->recv_mutex);
	ipmi_मुक्त_recv_msg(msg);
	वापस rv2;

recv_putback_on_err:
	/* If we got an error, put the message back onto
	   the head of the queue. */
	spin_lock_irqsave(&priv->recv_msg_lock, flags);
	list_add(entry, &priv->recv_msgs);
	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);
recv_err:
	mutex_unlock(&priv->recv_mutex);
	वापस rv;
पूर्ण

अटल पूर्णांक copyout_recv(काष्ठा ipmi_recv *rsp, व्योम __user *to)
अणु
	वापस copy_to_user(to, rsp, माप(काष्ठा ipmi_recv)) ? -EFAULT : 0;
पूर्ण

अटल दीर्घ ipmi_ioctl(काष्ठा file   *file,
		       अचिन्हित पूर्णांक  cmd,
		       अचिन्हित दीर्घ data)
अणु
	पूर्णांक                      rv = -EINVAL;
	काष्ठा ipmi_file_निजी *priv = file->निजी_data;
	व्योम __user *arg = (व्योम __user *)data;

	चयन (cmd) 
	अणु
	हाल IPMICTL_SEND_COMMAND:
	अणु
		काष्ठा ipmi_req req;
		पूर्णांक retries;
		अचिन्हित पूर्णांक retry_समय_ms;

		अगर (copy_from_user(&req, arg, माप(req))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		mutex_lock(&priv->recv_mutex);
		retries = priv->शेष_retries;
		retry_समय_ms = priv->शेष_retry_समय_ms;
		mutex_unlock(&priv->recv_mutex);

		rv = handle_send_req(priv->user, &req, retries, retry_समय_ms);
		अवरोध;
	पूर्ण

	हाल IPMICTL_SEND_COMMAND_SETTIME:
	अणु
		काष्ठा ipmi_req_समय_रखो req;

		अगर (copy_from_user(&req, arg, माप(req))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = handle_send_req(priv->user,
				     &req.req,
				     req.retries,
				     req.retry_समय_ms);
		अवरोध;
	पूर्ण

	हाल IPMICTL_RECEIVE_MSG:
	हाल IPMICTL_RECEIVE_MSG_TRUNC:
	अणु
		काष्ठा ipmi_recv      rsp;

		अगर (copy_from_user(&rsp, arg, माप(rsp)))
			rv = -EFAULT;
		अन्यथा
			rv = handle_recv(priv, cmd == IPMICTL_RECEIVE_MSG_TRUNC,
					 &rsp, copyout_recv, arg);
		अवरोध;
	पूर्ण

	हाल IPMICTL_REGISTER_FOR_CMD:
	अणु
		काष्ठा ipmi_cmdspec val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_रेजिस्टर_क्रम_cmd(priv->user, val.netfn, val.cmd,
					   IPMI_CHAN_ALL);
		अवरोध;
	पूर्ण

	हाल IPMICTL_UNREGISTER_FOR_CMD:
	अणु
		काष्ठा ipmi_cmdspec   val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_unरेजिस्टर_क्रम_cmd(priv->user, val.netfn, val.cmd,
					     IPMI_CHAN_ALL);
		अवरोध;
	पूर्ण

	हाल IPMICTL_REGISTER_FOR_CMD_CHANS:
	अणु
		काष्ठा ipmi_cmdspec_chans val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_रेजिस्टर_क्रम_cmd(priv->user, val.netfn, val.cmd,
					   val.chans);
		अवरोध;
	पूर्ण

	हाल IPMICTL_UNREGISTER_FOR_CMD_CHANS:
	अणु
		काष्ठा ipmi_cmdspec_chans val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_unरेजिस्टर_क्रम_cmd(priv->user, val.netfn, val.cmd,
					     val.chans);
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_GETS_EVENTS_CMD:
	अणु
		पूर्णांक val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_set_माला_लो_events(priv->user, val);
		अवरोध;
	पूर्ण

	/* The next four are legacy, not per-channel. */
	हाल IPMICTL_SET_MY_ADDRESS_CMD:
	अणु
		अचिन्हित पूर्णांक val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_set_my_address(priv->user, 0, val);
		अवरोध;
	पूर्ण

	हाल IPMICTL_GET_MY_ADDRESS_CMD:
	अणु
		अचिन्हित पूर्णांक  val;
		अचिन्हित अक्षर rval;

		rv = ipmi_get_my_address(priv->user, 0, &rval);
		अगर (rv)
			अवरोध;

		val = rval;

		अगर (copy_to_user(arg, &val, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_MY_LUN_CMD:
	अणु
		अचिन्हित पूर्णांक val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_set_my_LUN(priv->user, 0, val);
		अवरोध;
	पूर्ण

	हाल IPMICTL_GET_MY_LUN_CMD:
	अणु
		अचिन्हित पूर्णांक  val;
		अचिन्हित अक्षर rval;

		rv = ipmi_get_my_LUN(priv->user, 0, &rval);
		अगर (rv)
			अवरोध;

		val = rval;

		अगर (copy_to_user(arg, &val, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_MY_CHANNEL_ADDRESS_CMD:
	अणु
		काष्ठा ipmi_channel_lun_address_set val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		वापस ipmi_set_my_address(priv->user, val.channel, val.value);
	पूर्ण

	हाल IPMICTL_GET_MY_CHANNEL_ADDRESS_CMD:
	अणु
		काष्ठा ipmi_channel_lun_address_set val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_get_my_address(priv->user, val.channel, &val.value);
		अगर (rv)
			अवरोध;

		अगर (copy_to_user(arg, &val, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_MY_CHANNEL_LUN_CMD:
	अणु
		काष्ठा ipmi_channel_lun_address_set val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_set_my_LUN(priv->user, val.channel, val.value);
		अवरोध;
	पूर्ण

	हाल IPMICTL_GET_MY_CHANNEL_LUN_CMD:
	अणु
		काष्ठा ipmi_channel_lun_address_set val;

		अगर (copy_from_user(&val, arg, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = ipmi_get_my_LUN(priv->user, val.channel, &val.value);
		अगर (rv)
			अवरोध;

		अगर (copy_to_user(arg, &val, माप(val))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_TIMING_PARMS_CMD:
	अणु
		काष्ठा ipmi_timing_parms parms;

		अगर (copy_from_user(&parms, arg, माप(parms))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		mutex_lock(&priv->recv_mutex);
		priv->शेष_retries = parms.retries;
		priv->शेष_retry_समय_ms = parms.retry_समय_ms;
		mutex_unlock(&priv->recv_mutex);
		rv = 0;
		अवरोध;
	पूर्ण

	हाल IPMICTL_GET_TIMING_PARMS_CMD:
	अणु
		काष्ठा ipmi_timing_parms parms;

		mutex_lock(&priv->recv_mutex);
		parms.retries = priv->शेष_retries;
		parms.retry_समय_ms = priv->शेष_retry_समय_ms;
		mutex_unlock(&priv->recv_mutex);

		अगर (copy_to_user(arg, &parms, माप(parms))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण

		rv = 0;
		अवरोध;
	पूर्ण

	हाल IPMICTL_GET_MAINTEन_अंकCE_MODE_CMD:
	अणु
		पूर्णांक mode;

		mode = ipmi_get_मुख्यtenance_mode(priv->user);
		अगर (copy_to_user(arg, &mode, माप(mode))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		rv = 0;
		अवरोध;
	पूर्ण

	हाल IPMICTL_SET_MAINTEन_अंकCE_MODE_CMD:
	अणु
		पूर्णांक mode;

		अगर (copy_from_user(&mode, arg, माप(mode))) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		rv = ipmi_set_मुख्यtenance_mode(priv->user, mode);
		अवरोध;
	पूर्ण

	शेष:
		rv = -ENOTTY;
		अवरोध;
	पूर्ण
  
	वापस rv;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * The following code contains code क्रम supporting 32-bit compatible
 * ioctls on 64-bit kernels.  This allows running 32-bit apps on the
 * 64-bit kernel
 */
#घोषणा COMPAT_IPMICTL_SEND_COMMAND	\
	_IOR(IPMI_IOC_MAGIC, 13, काष्ठा compat_ipmi_req)
#घोषणा COMPAT_IPMICTL_SEND_COMMAND_SETTIME	\
	_IOR(IPMI_IOC_MAGIC, 21, काष्ठा compat_ipmi_req_समय_रखो)
#घोषणा COMPAT_IPMICTL_RECEIVE_MSG	\
	_IOWR(IPMI_IOC_MAGIC, 12, काष्ठा compat_ipmi_recv)
#घोषणा COMPAT_IPMICTL_RECEIVE_MSG_TRUNC	\
	_IOWR(IPMI_IOC_MAGIC, 11, काष्ठा compat_ipmi_recv)

काष्ठा compat_ipmi_msg अणु
	u8		netfn;
	u8		cmd;
	u16		data_len;
	compat_uptr_t	data;
पूर्ण;

काष्ठा compat_ipmi_req अणु
	compat_uptr_t		addr;
	compat_uपूर्णांक_t		addr_len;
	compat_दीर्घ_t		msgid;
	काष्ठा compat_ipmi_msg	msg;
पूर्ण;

काष्ठा compat_ipmi_recv अणु
	compat_पूर्णांक_t		recv_type;
	compat_uptr_t		addr;
	compat_uपूर्णांक_t		addr_len;
	compat_दीर्घ_t		msgid;
	काष्ठा compat_ipmi_msg	msg;
पूर्ण;

काष्ठा compat_ipmi_req_समय_रखो अणु
	काष्ठा compat_ipmi_req	req;
	compat_पूर्णांक_t		retries;
	compat_uपूर्णांक_t		retry_समय_ms;
पूर्ण;

/*
 * Define some helper functions क्रम copying IPMI data
 */
अटल व्योम get_compat_ipmi_msg(काष्ठा ipmi_msg *p64,
				काष्ठा compat_ipmi_msg *p32)
अणु
	p64->netfn = p32->netfn;
	p64->cmd = p32->cmd;
	p64->data_len = p32->data_len;
	p64->data = compat_ptr(p32->data);
पूर्ण

अटल व्योम get_compat_ipmi_req(काष्ठा ipmi_req *p64,
				काष्ठा compat_ipmi_req *p32)
अणु
	p64->addr = compat_ptr(p32->addr);
	p64->addr_len = p32->addr_len;
	p64->msgid = p32->msgid;
	get_compat_ipmi_msg(&p64->msg, &p32->msg);
पूर्ण

अटल व्योम get_compat_ipmi_req_समय_रखो(काष्ठा ipmi_req_समय_रखो *p64,
		काष्ठा compat_ipmi_req_समय_रखो *p32)
अणु
	get_compat_ipmi_req(&p64->req, &p32->req);
	p64->retries = p32->retries;
	p64->retry_समय_ms = p32->retry_समय_ms;
पूर्ण

अटल व्योम get_compat_ipmi_recv(काष्ठा ipmi_recv *p64,
				 काष्ठा compat_ipmi_recv *p32)
अणु
	स_रखो(p64, 0, माप(काष्ठा ipmi_recv));
	p64->recv_type = p32->recv_type;
	p64->addr = compat_ptr(p32->addr);
	p64->addr_len = p32->addr_len;
	p64->msgid = p32->msgid;
	get_compat_ipmi_msg(&p64->msg, &p32->msg);
पूर्ण

अटल पूर्णांक copyout_recv32(काष्ठा ipmi_recv *p64, व्योम __user *to)
अणु
	काष्ठा compat_ipmi_recv v32;
	स_रखो(&v32, 0, माप(काष्ठा compat_ipmi_recv));
	v32.recv_type = p64->recv_type;
	v32.addr = ptr_to_compat(p64->addr);
	v32.addr_len = p64->addr_len;
	v32.msgid = p64->msgid;
	v32.msg.netfn = p64->msg.netfn;
	v32.msg.cmd = p64->msg.cmd;
	v32.msg.data_len = p64->msg.data_len;
	v32.msg.data = ptr_to_compat(p64->msg.data);
	वापस copy_to_user(to, &v32, माप(v32)) ? -EFAULT : 0;
पूर्ण

/*
 * Handle compatibility ioctls
 */
अटल दीर्घ compat_ipmi_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	काष्ठा ipmi_file_निजी *priv = filep->निजी_data;

	चयन(cmd) अणु
	हाल COMPAT_IPMICTL_SEND_COMMAND:
	अणु
		काष्ठा ipmi_req	rp;
		काष्ठा compat_ipmi_req r32;
		पूर्णांक retries;
		अचिन्हित पूर्णांक retry_समय_ms;

		अगर (copy_from_user(&r32, compat_ptr(arg), माप(r32)))
			वापस -EFAULT;

		get_compat_ipmi_req(&rp, &r32);

		mutex_lock(&priv->recv_mutex);
		retries = priv->शेष_retries;
		retry_समय_ms = priv->शेष_retry_समय_ms;
		mutex_unlock(&priv->recv_mutex);

		वापस handle_send_req(priv->user, &rp,
				       retries, retry_समय_ms);
	पूर्ण
	हाल COMPAT_IPMICTL_SEND_COMMAND_SETTIME:
	अणु
		काष्ठा ipmi_req_समय_रखो	sp;
		काष्ठा compat_ipmi_req_समय_रखो sp32;

		अगर (copy_from_user(&sp32, compat_ptr(arg), माप(sp32)))
			वापस -EFAULT;

		get_compat_ipmi_req_समय_रखो(&sp, &sp32);

		वापस handle_send_req(priv->user, &sp.req,
				sp.retries, sp.retry_समय_ms);
	पूर्ण
	हाल COMPAT_IPMICTL_RECEIVE_MSG:
	हाल COMPAT_IPMICTL_RECEIVE_MSG_TRUNC:
	अणु
		काष्ठा ipmi_recv   recv64;
		काष्ठा compat_ipmi_recv recv32;

		अगर (copy_from_user(&recv32, compat_ptr(arg), माप(recv32)))
			वापस -EFAULT;

		get_compat_ipmi_recv(&recv64, &recv32);

		वापस handle_recv(priv,
				 cmd == COMPAT_IPMICTL_RECEIVE_MSG_TRUNC,
				 &recv64, copyout_recv32, compat_ptr(arg));
	पूर्ण
	शेष:
		वापस ipmi_ioctl(filep, cmd, arg);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations ipmi_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= ipmi_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = compat_ipmi_ioctl,
#पूर्ण_अगर
	.खोलो		= ipmi_खोलो,
	.release	= ipmi_release,
	.fasync		= ipmi_fasync,
	.poll		= ipmi_poll,
	.llseek		= noop_llseek,
पूर्ण;

#घोषणा DEVICE_NAME     "ipmidev"

अटल पूर्णांक ipmi_major;
module_param(ipmi_major, पूर्णांक, 0);
MODULE_PARM_DESC(ipmi_major, "Sets the major number of the IPMI device.  By"
		 " default, or if you set it to zero, it will choose the next"
		 " available device.  Setting it to -1 will disable the"
		 " interface.  Other values will set the major device number"
		 " to that value.");

/* Keep track of the devices that are रेजिस्टरed. */
काष्ठा ipmi_reg_list अणु
	dev_t            dev;
	काष्ठा list_head link;
पूर्ण;
अटल LIST_HEAD(reg_list);
अटल DEFINE_MUTEX(reg_list_mutex);

अटल काष्ठा class *ipmi_class;

अटल व्योम ipmi_new_smi(पूर्णांक अगर_num, काष्ठा device *device)
अणु
	dev_t dev = MKDEV(ipmi_major, अगर_num);
	काष्ठा ipmi_reg_list *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		pr_err("ipmi_devintf: Unable to create the ipmi class device link\n");
		वापस;
	पूर्ण
	entry->dev = dev;

	mutex_lock(&reg_list_mutex);
	device_create(ipmi_class, device, dev, शून्य, "ipmi%d", अगर_num);
	list_add(&entry->link, &reg_list);
	mutex_unlock(&reg_list_mutex);
पूर्ण

अटल व्योम ipmi_smi_gone(पूर्णांक अगर_num)
अणु
	dev_t dev = MKDEV(ipmi_major, अगर_num);
	काष्ठा ipmi_reg_list *entry;

	mutex_lock(&reg_list_mutex);
	list_क्रम_each_entry(entry, &reg_list, link) अणु
		अगर (entry->dev == dev) अणु
			list_del(&entry->link);
			kमुक्त(entry);
			अवरोध;
		पूर्ण
	पूर्ण
	device_destroy(ipmi_class, dev);
	mutex_unlock(&reg_list_mutex);
पूर्ण

अटल काष्ठा ipmi_smi_watcher smi_watcher =
अणु
	.owner    = THIS_MODULE,
	.new_smi  = ipmi_new_smi,
	.smi_gone = ipmi_smi_gone,
पूर्ण;

अटल पूर्णांक __init init_ipmi_devपूर्णांकf(व्योम)
अणु
	पूर्णांक rv;

	अगर (ipmi_major < 0)
		वापस -EINVAL;

	pr_info("ipmi device interface\n");

	ipmi_class = class_create(THIS_MODULE, "ipmi");
	अगर (IS_ERR(ipmi_class)) अणु
		pr_err("ipmi: can't register device class\n");
		वापस PTR_ERR(ipmi_class);
	पूर्ण

	rv = रेजिस्टर_chrdev(ipmi_major, DEVICE_NAME, &ipmi_fops);
	अगर (rv < 0) अणु
		class_destroy(ipmi_class);
		pr_err("ipmi: can't get major %d\n", ipmi_major);
		वापस rv;
	पूर्ण

	अगर (ipmi_major == 0) अणु
		ipmi_major = rv;
	पूर्ण

	rv = ipmi_smi_watcher_रेजिस्टर(&smi_watcher);
	अगर (rv) अणु
		unरेजिस्टर_chrdev(ipmi_major, DEVICE_NAME);
		class_destroy(ipmi_class);
		pr_warn("ipmi: can't register smi watcher\n");
		वापस rv;
	पूर्ण

	वापस 0;
पूर्ण
module_init(init_ipmi_devपूर्णांकf);

अटल व्योम __निकास cleanup_ipmi(व्योम)
अणु
	काष्ठा ipmi_reg_list *entry, *entry2;
	mutex_lock(&reg_list_mutex);
	list_क्रम_each_entry_safe(entry, entry2, &reg_list, link) अणु
		list_del(&entry->link);
		device_destroy(ipmi_class, entry->dev);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&reg_list_mutex);
	class_destroy(ipmi_class);
	ipmi_smi_watcher_unरेजिस्टर(&smi_watcher);
	unरेजिस्टर_chrdev(ipmi_major, DEVICE_NAME);
पूर्ण
module_निकास(cleanup_ipmi);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corey Minyard <minyard@mvista.com>");
MODULE_DESCRIPTION("Linux device interface for the IPMI message handler.");
