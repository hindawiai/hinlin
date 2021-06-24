<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cec-api.c - HDMI Consumer Electronics Control framework - API
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/version.h>

#समावेश <media/cec-pin.h>
#समावेश "cec-priv.h"
#समावेश "cec-pin-priv.h"

अटल अंतरभूत काष्ठा cec_devnode *cec_devnode_data(काष्ठा file *filp)
अणु
	काष्ठा cec_fh *fh = filp->निजी_data;

	वापस &fh->adap->devnode;
पूर्ण

/* CEC file operations */

अटल __poll_t cec_poll(काष्ठा file *filp,
			     काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा cec_fh *fh = filp->निजी_data;
	काष्ठा cec_adapter *adap = fh->adap;
	__poll_t res = 0;

	poll_रुको(filp, &fh->रुको, poll);
	अगर (!cec_is_रेजिस्टरed(adap))
		वापस EPOLLERR | EPOLLHUP | EPOLLPRI;
	mutex_lock(&adap->lock);
	अगर (adap->is_configured &&
	    adap->transmit_queue_sz < CEC_MAX_MSG_TX_QUEUE_SZ)
		res |= EPOLLOUT | EPOLLWRNORM;
	अगर (fh->queued_msgs)
		res |= EPOLLIN | EPOLLRDNORM;
	अगर (fh->total_queued_events)
		res |= EPOLLPRI;
	mutex_unlock(&adap->lock);
	वापस res;
पूर्ण

अटल bool cec_is_busy(स्थिर काष्ठा cec_adapter *adap,
			स्थिर काष्ठा cec_fh *fh)
अणु
	bool valid_initiator = adap->cec_initiator && adap->cec_initiator == fh;
	bool valid_follower = adap->cec_follower && adap->cec_follower == fh;

	/*
	 * Exclusive initiators and followers can always access the CEC adapter
	 */
	अगर (valid_initiator || valid_follower)
		वापस false;
	/*
	 * All others can only access the CEC adapter अगर there is no
	 * exclusive initiator and they are in INITIATOR mode.
	 */
	वापस adap->cec_initiator ||
	       fh->mode_initiator == CEC_MODE_NO_INITIATOR;
पूर्ण

अटल दीर्घ cec_adap_g_caps(काष्ठा cec_adapter *adap,
			    काष्ठा cec_caps __user *parg)
अणु
	काष्ठा cec_caps caps = अणुपूर्ण;

	strscpy(caps.driver, adap->devnode.dev.parent->driver->name,
		माप(caps.driver));
	strscpy(caps.name, adap->name, माप(caps.name));
	caps.available_log_addrs = adap->available_log_addrs;
	caps.capabilities = adap->capabilities;
	caps.version = LINUX_VERSION_CODE;
	अगर (copy_to_user(parg, &caps, माप(caps)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ cec_adap_g_phys_addr(काष्ठा cec_adapter *adap,
				 __u16 __user *parg)
अणु
	u16 phys_addr;

	mutex_lock(&adap->lock);
	phys_addr = adap->phys_addr;
	mutex_unlock(&adap->lock);
	अगर (copy_to_user(parg, &phys_addr, माप(phys_addr)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक cec_validate_phys_addr(u16 phys_addr)
अणु
	पूर्णांक i;

	अगर (phys_addr == CEC_PHYS_ADDR_INVALID)
		वापस 0;
	क्रम (i = 0; i < 16; i += 4)
		अगर (phys_addr & (0xf << i))
			अवरोध;
	अगर (i == 16)
		वापस 0;
	क्रम (i += 4; i < 16; i += 4)
		अगर ((phys_addr & (0xf << i)) == 0)
			वापस -EINVAL;
	वापस 0;
पूर्ण

अटल दीर्घ cec_adap_s_phys_addr(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
				 bool block, __u16 __user *parg)
अणु
	u16 phys_addr;
	दीर्घ err;

	अगर (!(adap->capabilities & CEC_CAP_PHYS_ADDR))
		वापस -ENOTTY;
	अगर (copy_from_user(&phys_addr, parg, माप(phys_addr)))
		वापस -EFAULT;

	err = cec_validate_phys_addr(phys_addr);
	अगर (err)
		वापस err;
	mutex_lock(&adap->lock);
	अगर (cec_is_busy(adap, fh))
		err = -EBUSY;
	अन्यथा
		__cec_s_phys_addr(adap, phys_addr, block);
	mutex_unlock(&adap->lock);
	वापस err;
पूर्ण

अटल दीर्घ cec_adap_g_log_addrs(काष्ठा cec_adapter *adap,
				 काष्ठा cec_log_addrs __user *parg)
अणु
	काष्ठा cec_log_addrs log_addrs;

	mutex_lock(&adap->lock);
	/*
	 * We use स_नकल here instead of assignment since there is a
	 * hole at the end of काष्ठा cec_log_addrs that an assignment
	 * might ignore. So when we करो copy_to_user() we could leak
	 * one byte of memory.
	 */
	स_नकल(&log_addrs, &adap->log_addrs, माप(log_addrs));
	अगर (!adap->is_configured)
		स_रखो(log_addrs.log_addr, CEC_LOG_ADDR_INVALID,
		       माप(log_addrs.log_addr));
	mutex_unlock(&adap->lock);

	अगर (copy_to_user(parg, &log_addrs, माप(log_addrs)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ cec_adap_s_log_addrs(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
				 bool block, काष्ठा cec_log_addrs __user *parg)
अणु
	काष्ठा cec_log_addrs log_addrs;
	दीर्घ err = -EBUSY;

	अगर (!(adap->capabilities & CEC_CAP_LOG_ADDRS))
		वापस -ENOTTY;
	अगर (copy_from_user(&log_addrs, parg, माप(log_addrs)))
		वापस -EFAULT;
	log_addrs.flags &= CEC_LOG_ADDRS_FL_ALLOW_UNREG_FALLBACK |
			   CEC_LOG_ADDRS_FL_ALLOW_RC_PASSTHRU |
			   CEC_LOG_ADDRS_FL_CDC_ONLY;
	mutex_lock(&adap->lock);
	अगर (!adap->is_configuring &&
	    (!log_addrs.num_log_addrs || !adap->is_configured) &&
	    !cec_is_busy(adap, fh)) अणु
		err = __cec_s_log_addrs(adap, &log_addrs, block);
		अगर (!err)
			log_addrs = adap->log_addrs;
	पूर्ण
	mutex_unlock(&adap->lock);
	अगर (err)
		वापस err;
	अगर (copy_to_user(parg, &log_addrs, माप(log_addrs)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ cec_adap_g_connector_info(काष्ठा cec_adapter *adap,
				      काष्ठा cec_log_addrs __user *parg)
अणु
	पूर्णांक ret = 0;

	अगर (!(adap->capabilities & CEC_CAP_CONNECTOR_INFO))
		वापस -ENOTTY;

	mutex_lock(&adap->lock);
	अगर (copy_to_user(parg, &adap->conn_info, माप(adap->conn_info)))
		ret = -EFAULT;
	mutex_unlock(&adap->lock);
	वापस ret;
पूर्ण

अटल दीर्घ cec_transmit(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
			 bool block, काष्ठा cec_msg __user *parg)
अणु
	काष्ठा cec_msg msg = अणुपूर्ण;
	दीर्घ err = 0;

	अगर (!(adap->capabilities & CEC_CAP_TRANSMIT))
		वापस -ENOTTY;
	अगर (copy_from_user(&msg, parg, माप(msg)))
		वापस -EFAULT;

	mutex_lock(&adap->lock);
	अगर (adap->log_addrs.num_log_addrs == 0)
		err = -EPERM;
	अन्यथा अगर (adap->is_configuring)
		err = -ENONET;
	अन्यथा अगर (cec_is_busy(adap, fh))
		err = -EBUSY;
	अन्यथा
		err = cec_transmit_msg_fh(adap, &msg, fh, block);
	mutex_unlock(&adap->lock);
	अगर (err)
		वापस err;
	अगर (copy_to_user(parg, &msg, माप(msg)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* Called by CEC_RECEIVE: रुको क्रम a message to arrive */
अटल पूर्णांक cec_receive_msg(काष्ठा cec_fh *fh, काष्ठा cec_msg *msg, bool block)
अणु
	u32 समयout = msg->समयout;
	पूर्णांक res;

	करो अणु
		mutex_lock(&fh->lock);
		/* Are there received messages queued up? */
		अगर (fh->queued_msgs) अणु
			/* Yes, वापस the first one */
			काष्ठा cec_msg_entry *entry =
				list_first_entry(&fh->msgs,
						 काष्ठा cec_msg_entry, list);

			list_del(&entry->list);
			*msg = entry->msg;
			kमुक्त(entry);
			fh->queued_msgs--;
			mutex_unlock(&fh->lock);
			/* restore original समयout value */
			msg->समयout = समयout;
			वापस 0;
		पूर्ण

		/* No, वापस EAGAIN in non-blocking mode or रुको */
		mutex_unlock(&fh->lock);

		/* Return when in non-blocking mode */
		अगर (!block)
			वापस -EAGAIN;

		अगर (msg->समयout) अणु
			/* The user specअगरied a समयout */
			res = रुको_event_पूर्णांकerruptible_समयout(fh->रुको,
							       fh->queued_msgs,
				msecs_to_jअगरfies(msg->समयout));
			अगर (res == 0)
				res = -ETIMEDOUT;
			अन्यथा अगर (res > 0)
				res = 0;
		पूर्ण अन्यथा अणु
			/* Wait indefinitely */
			res = रुको_event_पूर्णांकerruptible(fh->रुको,
						       fh->queued_msgs);
		पूर्ण
		/* Exit on error, otherwise loop to get the new message */
	पूर्ण जबतक (!res);
	वापस res;
पूर्ण

अटल दीर्घ cec_receive(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
			bool block, काष्ठा cec_msg __user *parg)
अणु
	काष्ठा cec_msg msg = अणुपूर्ण;
	दीर्घ err;

	अगर (copy_from_user(&msg, parg, माप(msg)))
		वापस -EFAULT;

	err = cec_receive_msg(fh, &msg, block);
	अगर (err)
		वापस err;
	msg.flags = 0;
	अगर (copy_to_user(parg, &msg, माप(msg)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ cec_dqevent(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
			bool block, काष्ठा cec_event __user *parg)
अणु
	काष्ठा cec_event_entry *ev = शून्य;
	u64 ts = ~0ULL;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक ev_idx;
	दीर्घ err = 0;

	mutex_lock(&fh->lock);
	जबतक (!fh->total_queued_events && block) अणु
		mutex_unlock(&fh->lock);
		err = रुको_event_पूर्णांकerruptible(fh->रुको,
					       fh->total_queued_events);
		अगर (err)
			वापस err;
		mutex_lock(&fh->lock);
	पूर्ण

	/* Find the oldest event */
	क्रम (i = 0; i < CEC_NUM_EVENTS; i++) अणु
		काष्ठा cec_event_entry *entry =
			list_first_entry_or_null(&fh->events[i],
						 काष्ठा cec_event_entry, list);

		अगर (entry && entry->ev.ts <= ts) अणु
			ev = entry;
			ev_idx = i;
			ts = ev->ev.ts;
		पूर्ण
	पूर्ण

	अगर (!ev) अणु
		err = -EAGAIN;
		जाओ unlock;
	पूर्ण
	list_del(&ev->list);

	अगर (copy_to_user(parg, &ev->ev, माप(ev->ev)))
		err = -EFAULT;
	अगर (ev_idx >= CEC_NUM_CORE_EVENTS)
		kमुक्त(ev);
	fh->queued_events[ev_idx]--;
	fh->total_queued_events--;

unlock:
	mutex_unlock(&fh->lock);
	वापस err;
पूर्ण

अटल दीर्घ cec_g_mode(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
		       u32 __user *parg)
अणु
	u32 mode = fh->mode_initiator | fh->mode_follower;

	अगर (copy_to_user(parg, &mode, माप(mode)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ cec_s_mode(काष्ठा cec_adapter *adap, काष्ठा cec_fh *fh,
		       u32 __user *parg)
अणु
	u32 mode;
	u8 mode_initiator;
	u8 mode_follower;
	bool send_pin_event = false;
	दीर्घ err = 0;

	अगर (copy_from_user(&mode, parg, माप(mode)))
		वापस -EFAULT;
	अगर (mode & ~(CEC_MODE_INITIATOR_MSK | CEC_MODE_FOLLOWER_MSK)) अणु
		dprपूर्णांकk(1, "%s: invalid mode bits set\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mode_initiator = mode & CEC_MODE_INITIATOR_MSK;
	mode_follower = mode & CEC_MODE_FOLLOWER_MSK;

	अगर (mode_initiator > CEC_MODE_EXCL_INITIATOR ||
	    mode_follower > CEC_MODE_MONITOR_ALL) अणु
		dprपूर्णांकk(1, "%s: unknown mode\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (mode_follower == CEC_MODE_MONITOR_ALL &&
	    !(adap->capabilities & CEC_CAP_MONITOR_ALL)) अणु
		dprपूर्णांकk(1, "%s: MONITOR_ALL not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (mode_follower == CEC_MODE_MONITOR_PIN &&
	    !(adap->capabilities & CEC_CAP_MONITOR_PIN)) अणु
		dprपूर्णांकk(1, "%s: MONITOR_PIN not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Follower modes should always be able to send CEC messages */
	अगर ((mode_initiator == CEC_MODE_NO_INITIATOR ||
	     !(adap->capabilities & CEC_CAP_TRANSMIT)) &&
	    mode_follower >= CEC_MODE_FOLLOWER &&
	    mode_follower <= CEC_MODE_EXCL_FOLLOWER_PASSTHRU) अणु
		dprपूर्णांकk(1, "%s: cannot transmit\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Monitor modes require CEC_MODE_NO_INITIATOR */
	अगर (mode_initiator && mode_follower >= CEC_MODE_MONITOR_PIN) अणु
		dprपूर्णांकk(1, "%s: monitor modes require NO_INITIATOR\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Monitor modes require CAP_NET_ADMIN */
	अगर (mode_follower >= CEC_MODE_MONITOR_PIN && !capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mutex_lock(&adap->lock);
	/*
	 * You can't become exclusive follower अगर someone अन्यथा alपढ़ोy
	 * has that job.
	 */
	अगर ((mode_follower == CEC_MODE_EXCL_FOLLOWER ||
	     mode_follower == CEC_MODE_EXCL_FOLLOWER_PASSTHRU) &&
	    adap->cec_follower && adap->cec_follower != fh)
		err = -EBUSY;
	/*
	 * You can't become exclusive initiator अगर someone अन्यथा alपढ़ोy
	 * has that job.
	 */
	अगर (mode_initiator == CEC_MODE_EXCL_INITIATOR &&
	    adap->cec_initiator && adap->cec_initiator != fh)
		err = -EBUSY;

	अगर (!err) अणु
		bool old_mon_all = fh->mode_follower == CEC_MODE_MONITOR_ALL;
		bool new_mon_all = mode_follower == CEC_MODE_MONITOR_ALL;

		अगर (old_mon_all != new_mon_all) अणु
			अगर (new_mon_all)
				err = cec_monitor_all_cnt_inc(adap);
			अन्यथा
				cec_monitor_all_cnt_dec(adap);
		पूर्ण
	पूर्ण

	अगर (!err) अणु
		bool old_mon_pin = fh->mode_follower == CEC_MODE_MONITOR_PIN;
		bool new_mon_pin = mode_follower == CEC_MODE_MONITOR_PIN;

		अगर (old_mon_pin != new_mon_pin) अणु
			send_pin_event = new_mon_pin;
			अगर (new_mon_pin)
				err = cec_monitor_pin_cnt_inc(adap);
			अन्यथा
				cec_monitor_pin_cnt_dec(adap);
		पूर्ण
	पूर्ण

	अगर (err) अणु
		mutex_unlock(&adap->lock);
		वापस err;
	पूर्ण

	अगर (fh->mode_follower == CEC_MODE_FOLLOWER)
		adap->follower_cnt--;
	अगर (mode_follower == CEC_MODE_FOLLOWER)
		adap->follower_cnt++;
	अगर (send_pin_event) अणु
		काष्ठा cec_event ev = अणु
			.flags = CEC_EVENT_FL_INITIAL_STATE,
		पूर्ण;

		ev.event = adap->cec_pin_is_high ? CEC_EVENT_PIN_CEC_HIGH :
						   CEC_EVENT_PIN_CEC_LOW;
		cec_queue_event_fh(fh, &ev, 0);
	पूर्ण
	अगर (mode_follower == CEC_MODE_EXCL_FOLLOWER ||
	    mode_follower == CEC_MODE_EXCL_FOLLOWER_PASSTHRU) अणु
		adap->passthrough =
			mode_follower == CEC_MODE_EXCL_FOLLOWER_PASSTHRU;
		adap->cec_follower = fh;
	पूर्ण अन्यथा अगर (adap->cec_follower == fh) अणु
		adap->passthrough = false;
		adap->cec_follower = शून्य;
	पूर्ण
	अगर (mode_initiator == CEC_MODE_EXCL_INITIATOR)
		adap->cec_initiator = fh;
	अन्यथा अगर (adap->cec_initiator == fh)
		adap->cec_initiator = शून्य;
	fh->mode_initiator = mode_initiator;
	fh->mode_follower = mode_follower;
	mutex_unlock(&adap->lock);
	वापस 0;
पूर्ण

अटल दीर्घ cec_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cec_fh *fh = filp->निजी_data;
	काष्ठा cec_adapter *adap = fh->adap;
	bool block = !(filp->f_flags & O_NONBLOCK);
	व्योम __user *parg = (व्योम __user *)arg;

	अगर (!cec_is_रेजिस्टरed(adap))
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल CEC_ADAP_G_CAPS:
		वापस cec_adap_g_caps(adap, parg);

	हाल CEC_ADAP_G_PHYS_ADDR:
		वापस cec_adap_g_phys_addr(adap, parg);

	हाल CEC_ADAP_S_PHYS_ADDR:
		वापस cec_adap_s_phys_addr(adap, fh, block, parg);

	हाल CEC_ADAP_G_LOG_ADDRS:
		वापस cec_adap_g_log_addrs(adap, parg);

	हाल CEC_ADAP_S_LOG_ADDRS:
		वापस cec_adap_s_log_addrs(adap, fh, block, parg);

	हाल CEC_ADAP_G_CONNECTOR_INFO:
		वापस cec_adap_g_connector_info(adap, parg);

	हाल CEC_TRANSMIT:
		वापस cec_transmit(adap, fh, block, parg);

	हाल CEC_RECEIVE:
		वापस cec_receive(adap, fh, block, parg);

	हाल CEC_DQEVENT:
		वापस cec_dqevent(adap, fh, block, parg);

	हाल CEC_G_MODE:
		वापस cec_g_mode(adap, fh, parg);

	हाल CEC_S_MODE:
		वापस cec_s_mode(adap, fh, parg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक cec_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cec_devnode *devnode =
		container_of(inode->i_cdev, काष्ठा cec_devnode, cdev);
	काष्ठा cec_adapter *adap = to_cec_adapter(devnode);
	काष्ठा cec_fh *fh = kzalloc(माप(*fh), GFP_KERNEL);
	/*
	 * Initial events that are स्वतःmatically sent when the cec device is
	 * खोलोed.
	 */
	काष्ठा cec_event ev = अणु
		.event = CEC_EVENT_STATE_CHANGE,
		.flags = CEC_EVENT_FL_INITIAL_STATE,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!fh)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&fh->msgs);
	INIT_LIST_HEAD(&fh->xfer_list);
	क्रम (i = 0; i < CEC_NUM_EVENTS; i++)
		INIT_LIST_HEAD(&fh->events[i]);
	mutex_init(&fh->lock);
	init_रुकोqueue_head(&fh->रुको);

	fh->mode_initiator = CEC_MODE_INITIATOR;
	fh->adap = adap;

	err = cec_get_device(devnode);
	अगर (err) अणु
		kमुक्त(fh);
		वापस err;
	पूर्ण

	mutex_lock(&devnode->lock);
	अगर (list_empty(&devnode->fhs) &&
	    !adap->needs_hpd &&
	    adap->phys_addr == CEC_PHYS_ADDR_INVALID) अणु
		err = adap->ops->adap_enable(adap, true);
		अगर (err) अणु
			mutex_unlock(&devnode->lock);
			kमुक्त(fh);
			वापस err;
		पूर्ण
	पूर्ण
	filp->निजी_data = fh;

	/* Queue up initial state events */
	ev.state_change.phys_addr = adap->phys_addr;
	ev.state_change.log_addr_mask = adap->log_addrs.log_addr_mask;
	ev.state_change.have_conn_info =
		adap->conn_info.type != CEC_CONNECTOR_TYPE_NO_CONNECTOR;
	cec_queue_event_fh(fh, &ev, 0);
#अगर_घोषित CONFIG_CEC_PIN
	अगर (adap->pin && adap->pin->ops->पढ़ो_hpd) अणु
		err = adap->pin->ops->पढ़ो_hpd(adap);
		अगर (err >= 0) अणु
			ev.event = err ? CEC_EVENT_PIN_HPD_HIGH :
					 CEC_EVENT_PIN_HPD_LOW;
			cec_queue_event_fh(fh, &ev, 0);
		पूर्ण
	पूर्ण
	अगर (adap->pin && adap->pin->ops->पढ़ो_5v) अणु
		err = adap->pin->ops->पढ़ो_5v(adap);
		अगर (err >= 0) अणु
			ev.event = err ? CEC_EVENT_PIN_5V_HIGH :
					 CEC_EVENT_PIN_5V_LOW;
			cec_queue_event_fh(fh, &ev, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	list_add(&fh->list, &devnode->fhs);
	mutex_unlock(&devnode->lock);

	वापस 0;
पूर्ण

/* Override क्रम the release function */
अटल पूर्णांक cec_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cec_devnode *devnode = cec_devnode_data(filp);
	काष्ठा cec_adapter *adap = to_cec_adapter(devnode);
	काष्ठा cec_fh *fh = filp->निजी_data;
	अचिन्हित पूर्णांक i;

	mutex_lock(&adap->lock);
	अगर (adap->cec_initiator == fh)
		adap->cec_initiator = शून्य;
	अगर (adap->cec_follower == fh) अणु
		adap->cec_follower = शून्य;
		adap->passthrough = false;
	पूर्ण
	अगर (fh->mode_follower == CEC_MODE_FOLLOWER)
		adap->follower_cnt--;
	अगर (fh->mode_follower == CEC_MODE_MONITOR_PIN)
		cec_monitor_pin_cnt_dec(adap);
	अगर (fh->mode_follower == CEC_MODE_MONITOR_ALL)
		cec_monitor_all_cnt_dec(adap);
	mutex_unlock(&adap->lock);

	mutex_lock(&devnode->lock);
	list_del(&fh->list);
	अगर (cec_is_रेजिस्टरed(adap) && list_empty(&devnode->fhs) &&
	    !adap->needs_hpd && adap->phys_addr == CEC_PHYS_ADDR_INVALID) अणु
		WARN_ON(adap->ops->adap_enable(adap, false));
	पूर्ण
	mutex_unlock(&devnode->lock);

	/* Unhook pending transmits from this filehandle. */
	mutex_lock(&adap->lock);
	जबतक (!list_empty(&fh->xfer_list)) अणु
		काष्ठा cec_data *data =
			list_first_entry(&fh->xfer_list, काष्ठा cec_data, xfer_list);

		data->blocking = false;
		data->fh = शून्य;
		list_del(&data->xfer_list);
	पूर्ण
	mutex_unlock(&adap->lock);
	जबतक (!list_empty(&fh->msgs)) अणु
		काष्ठा cec_msg_entry *entry =
			list_first_entry(&fh->msgs, काष्ठा cec_msg_entry, list);

		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	क्रम (i = CEC_NUM_CORE_EVENTS; i < CEC_NUM_EVENTS; i++) अणु
		जबतक (!list_empty(&fh->events[i])) अणु
			काष्ठा cec_event_entry *entry =
				list_first_entry(&fh->events[i],
						 काष्ठा cec_event_entry, list);

			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण
	kमुक्त(fh);

	cec_put_device(devnode);
	filp->निजी_data = शून्य;
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations cec_devnode_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = cec_खोलो,
	.unlocked_ioctl = cec_ioctl,
	.compat_ioctl = cec_ioctl,
	.release = cec_release,
	.poll = cec_poll,
	.llseek = no_llseek,
पूर्ण;
