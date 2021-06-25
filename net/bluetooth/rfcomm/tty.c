<शैली गुरु>
/*
   RFCOMM implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>
   Copyright (C) 2002 Marcel Holपंचांगann <marcel@holपंचांगann.org>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/*
 * RFCOMM TTY.
 */

#समावेश <linux/module.h>

#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/rfcomm.h>

#घोषणा RFCOMM_TTY_MAGIC 0x6d02		/* magic number क्रम rfcomm काष्ठा */
#घोषणा RFCOMM_TTY_PORTS RFCOMM_MAX_DEV	/* whole lotta rfcomm devices */
#घोषणा RFCOMM_TTY_MAJOR 216		/* device node major id of the usb/bluetooth.c driver */
#घोषणा RFCOMM_TTY_MINOR 0

अटल DEFINE_MUTEX(rfcomm_ioctl_mutex);
अटल काष्ठा tty_driver *rfcomm_tty_driver;

काष्ठा rfcomm_dev अणु
	काष्ठा tty_port		port;
	काष्ठा list_head	list;

	अक्षर			name[12];
	पूर्णांक			id;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			err;

	अचिन्हित दीर्घ		status;		/* करोn't export to userspace */

	bdaddr_t		src;
	bdaddr_t		dst;
	u8			channel;

	uपूर्णांक			modem_status;

	काष्ठा rfcomm_dlc	*dlc;

	काष्ठा device		*tty_dev;

	atomic_t		wmem_alloc;

	काष्ठा sk_buff_head	pending;
पूर्ण;

अटल LIST_HEAD(rfcomm_dev_list);
अटल DEFINE_MUTEX(rfcomm_dev_lock);

अटल व्योम rfcomm_dev_data_पढ़ोy(काष्ठा rfcomm_dlc *dlc, काष्ठा sk_buff *skb);
अटल व्योम rfcomm_dev_state_change(काष्ठा rfcomm_dlc *dlc, पूर्णांक err);
अटल व्योम rfcomm_dev_modem_status(काष्ठा rfcomm_dlc *dlc, u8 v24_sig);

/* ---- Device functions ---- */

अटल व्योम rfcomm_dev_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा rfcomm_dev *dev = container_of(port, काष्ठा rfcomm_dev, port);
	काष्ठा rfcomm_dlc *dlc = dev->dlc;

	BT_DBG("dev %p dlc %p", dev, dlc);

	rfcomm_dlc_lock(dlc);
	/* Detach DLC अगर it's owned by this dev */
	अगर (dlc->owner == dev)
		dlc->owner = शून्य;
	rfcomm_dlc_unlock(dlc);

	rfcomm_dlc_put(dlc);

	अगर (dev->tty_dev)
		tty_unरेजिस्टर_device(rfcomm_tty_driver, dev->id);

	mutex_lock(&rfcomm_dev_lock);
	list_del(&dev->list);
	mutex_unlock(&rfcomm_dev_lock);

	kमुक्त(dev);

	/* It's safe to call module_put() here because socket still
	   holds reference to this module. */
	module_put(THIS_MODULE);
पूर्ण

/* device-specअगरic initialization: खोलो the dlc */
अटल पूर्णांक rfcomm_dev_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = container_of(port, काष्ठा rfcomm_dev, port);
	पूर्णांक err;

	err = rfcomm_dlc_खोलो(dev->dlc, &dev->src, &dev->dst, dev->channel);
	अगर (err)
		set_bit(TTY_IO_ERROR, &tty->flags);
	वापस err;
पूर्ण

/* we block the खोलो until the dlc->state becomes BT_CONNECTED */
अटल पूर्णांक rfcomm_dev_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा rfcomm_dev *dev = container_of(port, काष्ठा rfcomm_dev, port);

	वापस (dev->dlc->state == BT_CONNECTED);
पूर्ण

/* device-specअगरic cleanup: बंद the dlc */
अटल व्योम rfcomm_dev_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा rfcomm_dev *dev = container_of(port, काष्ठा rfcomm_dev, port);

	अगर (dev->tty_dev->parent)
		device_move(dev->tty_dev, शून्य, DPM_ORDER_DEV_LAST);

	/* बंद the dlc */
	rfcomm_dlc_बंद(dev->dlc, 0);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations rfcomm_port_ops = अणु
	.deकाष्ठा = rfcomm_dev_deकाष्ठा,
	.activate = rfcomm_dev_activate,
	.shutकरोwn = rfcomm_dev_shutकरोwn,
	.carrier_उठाओd = rfcomm_dev_carrier_उठाओd,
पूर्ण;

अटल काष्ठा rfcomm_dev *__rfcomm_dev_lookup(पूर्णांक id)
अणु
	काष्ठा rfcomm_dev *dev;

	list_क्रम_each_entry(dev, &rfcomm_dev_list, list)
		अगर (dev->id == id)
			वापस dev;

	वापस शून्य;
पूर्ण

अटल काष्ठा rfcomm_dev *rfcomm_dev_get(पूर्णांक id)
अणु
	काष्ठा rfcomm_dev *dev;

	mutex_lock(&rfcomm_dev_lock);

	dev = __rfcomm_dev_lookup(id);

	अगर (dev && !tty_port_get(&dev->port))
		dev = शून्य;

	mutex_unlock(&rfcomm_dev_lock);

	वापस dev;
पूर्ण

अटल व्योम rfcomm_reparent_device(काष्ठा rfcomm_dev *dev)
अणु
	काष्ठा hci_dev *hdev;
	काष्ठा hci_conn *conn;

	hdev = hci_get_route(&dev->dst, &dev->src, BDADDR_BREDR);
	अगर (!hdev)
		वापस;

	/* The lookup results are unsafe to access without the
	 * hci device lock (FIXME: why is this not करोcumented?)
	 */
	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &dev->dst);

	/* Just because the acl link is in the hash table is no
	 * guarantee the sysfs device has been added ...
	 */
	अगर (conn && device_is_रेजिस्टरed(&conn->dev))
		device_move(dev->tty_dev, &conn->dev, DPM_ORDER_DEV_AFTER_PARENT);

	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
पूर्ण

अटल sमाप_प्रकार show_address(काष्ठा device *tty_dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rfcomm_dev *dev = dev_get_drvdata(tty_dev);
	वापस प्र_लिखो(buf, "%pMR\n", &dev->dst);
पूर्ण

अटल sमाप_प्रकार show_channel(काष्ठा device *tty_dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rfcomm_dev *dev = dev_get_drvdata(tty_dev);
	वापस प्र_लिखो(buf, "%d\n", dev->channel);
पूर्ण

अटल DEVICE_ATTR(address, 0444, show_address, शून्य);
अटल DEVICE_ATTR(channel, 0444, show_channel, शून्य);

अटल काष्ठा rfcomm_dev *__rfcomm_dev_add(काष्ठा rfcomm_dev_req *req,
					   काष्ठा rfcomm_dlc *dlc)
अणु
	काष्ठा rfcomm_dev *dev, *entry;
	काष्ठा list_head *head = &rfcomm_dev_list;
	पूर्णांक err = 0;

	dev = kzalloc(माप(काष्ठा rfcomm_dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&rfcomm_dev_lock);

	अगर (req->dev_id < 0) अणु
		dev->id = 0;

		list_क्रम_each_entry(entry, &rfcomm_dev_list, list) अणु
			अगर (entry->id != dev->id)
				अवरोध;

			dev->id++;
			head = &entry->list;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->id = req->dev_id;

		list_क्रम_each_entry(entry, &rfcomm_dev_list, list) अणु
			अगर (entry->id == dev->id) अणु
				err = -EADDRINUSE;
				जाओ out;
			पूर्ण

			अगर (entry->id > dev->id - 1)
				अवरोध;

			head = &entry->list;
		पूर्ण
	पूर्ण

	अगर ((dev->id < 0) || (dev->id > RFCOMM_MAX_DEV - 1)) अणु
		err = -ENखाता;
		जाओ out;
	पूर्ण

	प्र_लिखो(dev->name, "rfcomm%d", dev->id);

	list_add(&dev->list, head);

	bacpy(&dev->src, &req->src);
	bacpy(&dev->dst, &req->dst);
	dev->channel = req->channel;

	dev->flags = req->flags &
		((1 << RFCOMM_RELEASE_ONHUP) | (1 << RFCOMM_REUSE_DLC));

	tty_port_init(&dev->port);
	dev->port.ops = &rfcomm_port_ops;

	skb_queue_head_init(&dev->pending);

	rfcomm_dlc_lock(dlc);

	अगर (req->flags & (1 << RFCOMM_REUSE_DLC)) अणु
		काष्ठा sock *sk = dlc->owner;
		काष्ठा sk_buff *skb;

		BUG_ON(!sk);

		rfcomm_dlc_throttle(dlc);

		जबतक ((skb = skb_dequeue(&sk->sk_receive_queue))) अणु
			skb_orphan(skb);
			skb_queue_tail(&dev->pending, skb);
			atomic_sub(skb->len, &sk->sk_rmem_alloc);
		पूर्ण
	पूर्ण

	dlc->data_पढ़ोy   = rfcomm_dev_data_पढ़ोy;
	dlc->state_change = rfcomm_dev_state_change;
	dlc->modem_status = rfcomm_dev_modem_status;

	dlc->owner = dev;
	dev->dlc   = dlc;

	rfcomm_dev_modem_status(dlc, dlc->remote_v24_sig);

	rfcomm_dlc_unlock(dlc);

	/* It's safe to call __module_get() here because socket alपढ़ोy
	   holds reference to this module. */
	__module_get(THIS_MODULE);

	mutex_unlock(&rfcomm_dev_lock);
	वापस dev;

out:
	mutex_unlock(&rfcomm_dev_lock);
	kमुक्त(dev);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक rfcomm_dev_add(काष्ठा rfcomm_dev_req *req, काष्ठा rfcomm_dlc *dlc)
अणु
	काष्ठा rfcomm_dev *dev;
	काष्ठा device *tty;

	BT_DBG("id %d channel %d", req->dev_id, req->channel);

	dev = __rfcomm_dev_add(req, dlc);
	अगर (IS_ERR(dev)) अणु
		rfcomm_dlc_put(dlc);
		वापस PTR_ERR(dev);
	पूर्ण

	tty = tty_port_रेजिस्टर_device(&dev->port, rfcomm_tty_driver,
			dev->id, शून्य);
	अगर (IS_ERR(tty)) अणु
		tty_port_put(&dev->port);
		वापस PTR_ERR(tty);
	पूर्ण

	dev->tty_dev = tty;
	rfcomm_reparent_device(dev);
	dev_set_drvdata(dev->tty_dev, dev);

	अगर (device_create_file(dev->tty_dev, &dev_attr_address) < 0)
		BT_ERR("Failed to create address attribute");

	अगर (device_create_file(dev->tty_dev, &dev_attr_channel) < 0)
		BT_ERR("Failed to create channel attribute");

	वापस dev->id;
पूर्ण

/* ---- Send buffer ---- */
अटल अंतरभूत अचिन्हित पूर्णांक rfcomm_room(काष्ठा rfcomm_dev *dev)
अणु
	काष्ठा rfcomm_dlc *dlc = dev->dlc;

	/* Limit the outstanding number of packets not yet sent to 40 */
	पूर्णांक pending = 40 - atomic_पढ़ो(&dev->wmem_alloc);

	वापस max(0, pending) * dlc->mtu;
पूर्ण

अटल व्योम rfcomm_wमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_dev *dev = (व्योम *) skb->sk;
	atomic_dec(&dev->wmem_alloc);
	अगर (test_bit(RFCOMM_TTY_ATTACHED, &dev->flags))
		tty_port_tty_wakeup(&dev->port);
	tty_port_put(&dev->port);
पूर्ण

अटल व्योम rfcomm_set_owner_w(काष्ठा sk_buff *skb, काष्ठा rfcomm_dev *dev)
अणु
	tty_port_get(&dev->port);
	atomic_inc(&dev->wmem_alloc);
	skb->sk = (व्योम *) dev;
	skb->deकाष्ठाor = rfcomm_wमुक्त;
पूर्ण

अटल काष्ठा sk_buff *rfcomm_wदो_स्मृति(काष्ठा rfcomm_dev *dev, अचिन्हित दीर्घ size, gfp_t priority)
अणु
	काष्ठा sk_buff *skb = alloc_skb(size, priority);
	अगर (skb)
		rfcomm_set_owner_w(skb, dev);
	वापस skb;
पूर्ण

/* ---- Device IOCTLs ---- */

#घोषणा NOCAP_FLAGS ((1 << RFCOMM_REUSE_DLC) | (1 << RFCOMM_RELEASE_ONHUP))

अटल पूर्णांक __rfcomm_create_dev(काष्ठा sock *sk, व्योम __user *arg)
अणु
	काष्ठा rfcomm_dev_req req;
	काष्ठा rfcomm_dlc *dlc;
	पूर्णांक id;

	अगर (copy_from_user(&req, arg, माप(req)))
		वापस -EFAULT;

	BT_DBG("sk %p dev_id %d flags 0x%x", sk, req.dev_id, req.flags);

	अगर (req.flags != NOCAP_FLAGS && !capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (req.flags & (1 << RFCOMM_REUSE_DLC)) अणु
		/* Socket must be connected */
		अगर (sk->sk_state != BT_CONNECTED)
			वापस -EBADFD;

		dlc = rfcomm_pi(sk)->dlc;
		rfcomm_dlc_hold(dlc);
	पूर्ण अन्यथा अणु
		/* Validate the channel is unused */
		dlc = rfcomm_dlc_exists(&req.src, &req.dst, req.channel);
		अगर (IS_ERR(dlc))
			वापस PTR_ERR(dlc);
		अगर (dlc)
			वापस -EBUSY;
		dlc = rfcomm_dlc_alloc(GFP_KERNEL);
		अगर (!dlc)
			वापस -ENOMEM;
	पूर्ण

	id = rfcomm_dev_add(&req, dlc);
	अगर (id < 0)
		वापस id;

	अगर (req.flags & (1 << RFCOMM_REUSE_DLC)) अणु
		/* DLC is now used by device.
		 * Socket must be disconnected */
		sk->sk_state = BT_CLOSED;
	पूर्ण

	वापस id;
पूर्ण

अटल पूर्णांक __rfcomm_release_dev(व्योम __user *arg)
अणु
	काष्ठा rfcomm_dev_req req;
	काष्ठा rfcomm_dev *dev;
	काष्ठा tty_काष्ठा *tty;

	अगर (copy_from_user(&req, arg, माप(req)))
		वापस -EFAULT;

	BT_DBG("dev_id %d flags 0x%x", req.dev_id, req.flags);

	dev = rfcomm_dev_get(req.dev_id);
	अगर (!dev)
		वापस -ENODEV;

	अगर (dev->flags != NOCAP_FLAGS && !capable(CAP_NET_ADMIN)) अणु
		tty_port_put(&dev->port);
		वापस -EPERM;
	पूर्ण

	/* only release once */
	अगर (test_and_set_bit(RFCOMM_DEV_RELEASED, &dev->status)) अणु
		tty_port_put(&dev->port);
		वापस -EALREADY;
	पूर्ण

	अगर (req.flags & (1 << RFCOMM_HANGUP_NOW))
		rfcomm_dlc_बंद(dev->dlc, 0);

	/* Shut करोwn TTY synchronously beक्रमe मुक्तing rfcomm_dev */
	tty = tty_port_tty_get(&dev->port);
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण

	अगर (!test_bit(RFCOMM_TTY_OWNED, &dev->status))
		tty_port_put(&dev->port);

	tty_port_put(&dev->port);
	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_create_dev(काष्ठा sock *sk, व्योम __user *arg)
अणु
	पूर्णांक ret;

	mutex_lock(&rfcomm_ioctl_mutex);
	ret = __rfcomm_create_dev(sk, arg);
	mutex_unlock(&rfcomm_ioctl_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rfcomm_release_dev(व्योम __user *arg)
अणु
	पूर्णांक ret;

	mutex_lock(&rfcomm_ioctl_mutex);
	ret = __rfcomm_release_dev(arg);
	mutex_unlock(&rfcomm_ioctl_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rfcomm_get_dev_list(व्योम __user *arg)
अणु
	काष्ठा rfcomm_dev *dev;
	काष्ठा rfcomm_dev_list_req *dl;
	काष्ठा rfcomm_dev_info *di;
	पूर्णांक n = 0, size, err;
	u16 dev_num;

	BT_DBG("");

	अगर (get_user(dev_num, (u16 __user *) arg))
		वापस -EFAULT;

	अगर (!dev_num || dev_num > (PAGE_SIZE * 4) / माप(*di))
		वापस -EINVAL;

	size = माप(*dl) + dev_num * माप(*di);

	dl = kzalloc(size, GFP_KERNEL);
	अगर (!dl)
		वापस -ENOMEM;

	di = dl->dev_info;

	mutex_lock(&rfcomm_dev_lock);

	list_क्रम_each_entry(dev, &rfcomm_dev_list, list) अणु
		अगर (!tty_port_get(&dev->port))
			जारी;
		(di + n)->id      = dev->id;
		(di + n)->flags   = dev->flags;
		(di + n)->state   = dev->dlc->state;
		(di + n)->channel = dev->channel;
		bacpy(&(di + n)->src, &dev->src);
		bacpy(&(di + n)->dst, &dev->dst);
		tty_port_put(&dev->port);
		अगर (++n >= dev_num)
			अवरोध;
	पूर्ण

	mutex_unlock(&rfcomm_dev_lock);

	dl->dev_num = n;
	size = माप(*dl) + n * माप(*di);

	err = copy_to_user(arg, dl, size);
	kमुक्त(dl);

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक rfcomm_get_dev_info(व्योम __user *arg)
अणु
	काष्ठा rfcomm_dev *dev;
	काष्ठा rfcomm_dev_info di;
	पूर्णांक err = 0;

	BT_DBG("");

	अगर (copy_from_user(&di, arg, माप(di)))
		वापस -EFAULT;

	dev = rfcomm_dev_get(di.id);
	अगर (!dev)
		वापस -ENODEV;

	di.flags   = dev->flags;
	di.channel = dev->channel;
	di.state   = dev->dlc->state;
	bacpy(&di.src, &dev->src);
	bacpy(&di.dst, &dev->dst);

	अगर (copy_to_user(arg, &di, माप(di)))
		err = -EFAULT;

	tty_port_put(&dev->port);
	वापस err;
पूर्ण

पूर्णांक rfcomm_dev_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	BT_DBG("cmd %d arg %p", cmd, arg);

	चयन (cmd) अणु
	हाल RFCOMMCREATEDEV:
		वापस rfcomm_create_dev(sk, arg);

	हाल RFCOMMRELEASEDEV:
		वापस rfcomm_release_dev(arg);

	हाल RFCOMMGETDEVLIST:
		वापस rfcomm_get_dev_list(arg);

	हाल RFCOMMGETDEVINFO:
		वापस rfcomm_get_dev_info(arg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* ---- DLC callbacks ---- */
अटल व्योम rfcomm_dev_data_पढ़ोy(काष्ठा rfcomm_dlc *dlc, काष्ठा sk_buff *skb)
अणु
	काष्ठा rfcomm_dev *dev = dlc->owner;

	अगर (!dev) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (!skb_queue_empty(&dev->pending)) अणु
		skb_queue_tail(&dev->pending, skb);
		वापस;
	पूर्ण

	BT_DBG("dlc %p len %d", dlc, skb->len);

	tty_insert_flip_string(&dev->port, skb->data, skb->len);
	tty_flip_buffer_push(&dev->port);

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम rfcomm_dev_state_change(काष्ठा rfcomm_dlc *dlc, पूर्णांक err)
अणु
	काष्ठा rfcomm_dev *dev = dlc->owner;
	अगर (!dev)
		वापस;

	BT_DBG("dlc %p dev %p err %d", dlc, dev, err);

	dev->err = err;
	अगर (dlc->state == BT_CONNECTED) अणु
		rfcomm_reparent_device(dev);

		wake_up_पूर्णांकerruptible(&dev->port.खोलो_रुको);
	पूर्ण अन्यथा अगर (dlc->state == BT_CLOSED)
		tty_port_tty_hangup(&dev->port, false);
पूर्ण

अटल व्योम rfcomm_dev_modem_status(काष्ठा rfcomm_dlc *dlc, u8 v24_sig)
अणु
	काष्ठा rfcomm_dev *dev = dlc->owner;
	अगर (!dev)
		वापस;

	BT_DBG("dlc %p dev %p v24_sig 0x%02x", dlc, dev, v24_sig);

	अगर ((dev->modem_status & TIOCM_CD) && !(v24_sig & RFCOMM_V24_DV))
		tty_port_tty_hangup(&dev->port, true);

	dev->modem_status =
		((v24_sig & RFCOMM_V24_RTC) ? (TIOCM_DSR | TIOCM_DTR) : 0) |
		((v24_sig & RFCOMM_V24_RTR) ? (TIOCM_RTS | TIOCM_CTS) : 0) |
		((v24_sig & RFCOMM_V24_IC)  ? TIOCM_RI : 0) |
		((v24_sig & RFCOMM_V24_DV)  ? TIOCM_CD : 0);
पूर्ण

/* ---- TTY functions ---- */
अटल व्योम rfcomm_tty_copy_pending(काष्ठा rfcomm_dev *dev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक inserted = 0;

	BT_DBG("dev %p", dev);

	rfcomm_dlc_lock(dev->dlc);

	जबतक ((skb = skb_dequeue(&dev->pending))) अणु
		inserted += tty_insert_flip_string(&dev->port, skb->data,
				skb->len);
		kमुक्त_skb(skb);
	पूर्ण

	rfcomm_dlc_unlock(dev->dlc);

	अगर (inserted > 0)
		tty_flip_buffer_push(&dev->port);
पूर्ण

/* करो the reverse of install, clearing the tty fields and releasing the
 * reference to tty_port
 */
अटल व्योम rfcomm_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = tty->driver_data;

	clear_bit(RFCOMM_TTY_ATTACHED, &dev->flags);

	rfcomm_dlc_lock(dev->dlc);
	tty->driver_data = शून्य;
	rfcomm_dlc_unlock(dev->dlc);

	/*
	 * purge the dlc->tx_queue to aव्योम circular dependencies
	 * between dev and dlc
	 */
	skb_queue_purge(&dev->dlc->tx_queue);

	tty_port_put(&dev->port);
पूर्ण

/* we acquire the tty_port reference since it's here the tty is first used
 * by setting the termios. We also populate the driver_data field and install
 * the tty port
 */
अटल पूर्णांक rfcomm_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev;
	काष्ठा rfcomm_dlc *dlc;
	पूर्णांक err;

	dev = rfcomm_dev_get(tty->index);
	अगर (!dev)
		वापस -ENODEV;

	dlc = dev->dlc;

	/* Attach TTY and खोलो DLC */
	rfcomm_dlc_lock(dlc);
	tty->driver_data = dev;
	rfcomm_dlc_unlock(dlc);
	set_bit(RFCOMM_TTY_ATTACHED, &dev->flags);

	/* install the tty_port */
	err = tty_port_install(&dev->port, driver, tty);
	अगर (err) अणु
		rfcomm_tty_cleanup(tty);
		वापस err;
	पूर्ण

	/* take over the tty_port reference अगर the port was created with the
	 * flag RFCOMM_RELEASE_ONHUP. This will क्रमce the release of the port
	 * when the last process बंदs the tty. The behaviour is expected by
	 * userspace.
	 */
	अगर (test_bit(RFCOMM_RELEASE_ONHUP, &dev->flags)) अणु
		set_bit(RFCOMM_TTY_OWNED, &dev->status);
		tty_port_put(&dev->port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा rfcomm_dev *dev = tty->driver_data;
	पूर्णांक err;

	BT_DBG("tty %p id %d", tty, tty->index);

	BT_DBG("dev %p dst %pMR channel %d opened %d", dev, &dev->dst,
	       dev->channel, dev->port.count);

	err = tty_port_खोलो(&dev->port, tty, filp);
	अगर (err)
		वापस err;

	/*
	 * FIXME: rfcomm should use proper flow control क्रम
	 * received data. This hack will be unnecessary and can
	 * be हटाओd when that's implemented
	 */
	rfcomm_tty_copy_pending(dev);

	rfcomm_dlc_unthrottle(dev->dlc);

	वापस 0;
पूर्ण

अटल व्योम rfcomm_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p dlc %p opened %d", tty, dev, dev->dlc,
						dev->port.count);

	tty_port_बंद(&dev->port, tty, filp);
पूर्ण

अटल पूर्णांक rfcomm_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;
	काष्ठा rfcomm_dlc *dlc = dev->dlc;
	काष्ठा sk_buff *skb;
	पूर्णांक sent = 0, size;

	BT_DBG("tty %p count %d", tty, count);

	जबतक (count) अणु
		size = min_t(uपूर्णांक, count, dlc->mtu);

		skb = rfcomm_wदो_स्मृति(dev, size + RFCOMM_SKB_RESERVE, GFP_ATOMIC);
		अगर (!skb)
			अवरोध;

		skb_reserve(skb, RFCOMM_SKB_HEAD_RESERVE);

		skb_put_data(skb, buf + sent, size);

		rfcomm_dlc_send_noerror(dlc, skb);

		sent  += size;
		count -= size;
	पूर्ण

	वापस sent;
पूर्ण

अटल पूर्णांक rfcomm_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;
	पूर्णांक room = 0;

	अगर (dev && dev->dlc)
		room = rfcomm_room(dev);

	BT_DBG("tty %p room %d", tty, room);

	वापस room;
पूर्ण

अटल पूर्णांक rfcomm_tty_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	BT_DBG("tty %p cmd 0x%02x", tty, cmd);

	चयन (cmd) अणु
	हाल TCGETS:
		BT_DBG("TCGETS is not supported");
		वापस -ENOIOCTLCMD;

	हाल TCSETS:
		BT_DBG("TCSETS is not supported");
		वापस -ENOIOCTLCMD;

	हाल TIOCMIWAIT:
		BT_DBG("TIOCMIWAIT");
		अवरोध;

	हाल TIOCSERGETLSR:
		BT_ERR("TIOCSERGETLSR is not supported");
		वापस -ENOIOCTLCMD;

	हाल TIOCSERCONFIG:
		BT_ERR("TIOCSERCONFIG is not supported");
		वापस -ENOIOCTLCMD;

	शेष:
		वापस -ENOIOCTLCMD;	/* ioctls which we must ignore */

	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल व्योम rfcomm_tty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा ktermios *new = &tty->termios;
	पूर्णांक old_baud_rate = tty_termios_baud_rate(old);
	पूर्णांक new_baud_rate = tty_termios_baud_rate(new);

	u8 baud, data_bits, stop_bits, parity, x_on, x_off;
	u16 changes = 0;

	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p termios %p", tty, old);

	अगर (!dev || !dev->dlc || !dev->dlc->session)
		वापस;

	/* Handle turning off CRTSCTS */
	अगर ((old->c_cflag & CRTSCTS) && !(new->c_cflag & CRTSCTS))
		BT_DBG("Turning off CRTSCTS unsupported");

	/* Parity on/off and when on, odd/even */
	अगर (((old->c_cflag & PARENB) != (new->c_cflag & PARENB)) ||
			((old->c_cflag & PARODD) != (new->c_cflag & PARODD))) अणु
		changes |= RFCOMM_RPN_PM_PARITY;
		BT_DBG("Parity change detected.");
	पूर्ण

	/* Mark and space parity are not supported! */
	अगर (new->c_cflag & PARENB) अणु
		अगर (new->c_cflag & PARODD) अणु
			BT_DBG("Parity is ODD");
			parity = RFCOMM_RPN_PARITY_ODD;
		पूर्ण अन्यथा अणु
			BT_DBG("Parity is EVEN");
			parity = RFCOMM_RPN_PARITY_EVEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_DBG("Parity is OFF");
		parity = RFCOMM_RPN_PARITY_NONE;
	पूर्ण

	/* Setting the x_on / x_off अक्षरacters */
	अगर (old->c_cc[VSTOP] != new->c_cc[VSTOP]) अणु
		BT_DBG("XOFF custom");
		x_on = new->c_cc[VSTOP];
		changes |= RFCOMM_RPN_PM_XON;
	पूर्ण अन्यथा अणु
		BT_DBG("XOFF default");
		x_on = RFCOMM_RPN_XON_CHAR;
	पूर्ण

	अगर (old->c_cc[VSTART] != new->c_cc[VSTART]) अणु
		BT_DBG("XON custom");
		x_off = new->c_cc[VSTART];
		changes |= RFCOMM_RPN_PM_XOFF;
	पूर्ण अन्यथा अणु
		BT_DBG("XON default");
		x_off = RFCOMM_RPN_XOFF_CHAR;
	पूर्ण

	/* Handle setting of stop bits */
	अगर ((old->c_cflag & CSTOPB) != (new->c_cflag & CSTOPB))
		changes |= RFCOMM_RPN_PM_STOP;

	/* POSIX करोes not support 1.5 stop bits and RFCOMM करोes not
	 * support 2 stop bits. So a request क्रम 2 stop bits माला_लो
	 * translated to 1.5 stop bits */
	अगर (new->c_cflag & CSTOPB)
		stop_bits = RFCOMM_RPN_STOP_15;
	अन्यथा
		stop_bits = RFCOMM_RPN_STOP_1;

	/* Handle number of data bits [5-8] */
	अगर ((old->c_cflag & CSIZE) != (new->c_cflag & CSIZE))
		changes |= RFCOMM_RPN_PM_DATA;

	चयन (new->c_cflag & CSIZE) अणु
	हाल CS5:
		data_bits = RFCOMM_RPN_DATA_5;
		अवरोध;
	हाल CS6:
		data_bits = RFCOMM_RPN_DATA_6;
		अवरोध;
	हाल CS7:
		data_bits = RFCOMM_RPN_DATA_7;
		अवरोध;
	हाल CS8:
		data_bits = RFCOMM_RPN_DATA_8;
		अवरोध;
	शेष:
		data_bits = RFCOMM_RPN_DATA_8;
		अवरोध;
	पूर्ण

	/* Handle baudrate settings */
	अगर (old_baud_rate != new_baud_rate)
		changes |= RFCOMM_RPN_PM_BITRATE;

	चयन (new_baud_rate) अणु
	हाल 2400:
		baud = RFCOMM_RPN_BR_2400;
		अवरोध;
	हाल 4800:
		baud = RFCOMM_RPN_BR_4800;
		अवरोध;
	हाल 7200:
		baud = RFCOMM_RPN_BR_7200;
		अवरोध;
	हाल 9600:
		baud = RFCOMM_RPN_BR_9600;
		अवरोध;
	हाल 19200:
		baud = RFCOMM_RPN_BR_19200;
		अवरोध;
	हाल 38400:
		baud = RFCOMM_RPN_BR_38400;
		अवरोध;
	हाल 57600:
		baud = RFCOMM_RPN_BR_57600;
		अवरोध;
	हाल 115200:
		baud = RFCOMM_RPN_BR_115200;
		अवरोध;
	हाल 230400:
		baud = RFCOMM_RPN_BR_230400;
		अवरोध;
	शेष:
		/* 9600 is standard accordinag to the RFCOMM specअगरication */
		baud = RFCOMM_RPN_BR_9600;
		अवरोध;

	पूर्ण

	अगर (changes)
		rfcomm_send_rpn(dev->dlc->session, 1, dev->dlc->dlci, baud,
				data_bits, stop_bits, parity,
				RFCOMM_RPN_FLOW_NONE, x_on, x_off, changes);
पूर्ण

अटल व्योम rfcomm_tty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	rfcomm_dlc_throttle(dev->dlc);
पूर्ण

अटल व्योम rfcomm_tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	rfcomm_dlc_unthrottle(dev->dlc);
पूर्ण

अटल पूर्णांक rfcomm_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	अगर (!dev || !dev->dlc)
		वापस 0;

	अगर (!skb_queue_empty(&dev->dlc->tx_queue))
		वापस dev->dlc->mtu;

	वापस 0;
पूर्ण

अटल व्योम rfcomm_tty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	अगर (!dev || !dev->dlc)
		वापस;

	skb_queue_purge(&dev->dlc->tx_queue);
	tty_wakeup(tty);
पूर्ण

अटल व्योम rfcomm_tty_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	BT_DBG("tty %p ch %c", tty, ch);
पूर्ण

अटल व्योम rfcomm_tty_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	BT_DBG("tty %p timeout %d", tty, समयout);
पूर्ण

अटल व्योम rfcomm_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	tty_port_hangup(&dev->port);
पूर्ण

अटल पूर्णांक rfcomm_tty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	वापस dev->modem_status;
पूर्ण

अटल पूर्णांक rfcomm_tty_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा rfcomm_dev *dev = (काष्ठा rfcomm_dev *) tty->driver_data;
	काष्ठा rfcomm_dlc *dlc = dev->dlc;
	u8 v24_sig;

	BT_DBG("tty %p dev %p set 0x%02x clear 0x%02x", tty, dev, set, clear);

	rfcomm_dlc_get_modem_status(dlc, &v24_sig);

	अगर (set & TIOCM_DSR || set & TIOCM_DTR)
		v24_sig |= RFCOMM_V24_RTC;
	अगर (set & TIOCM_RTS || set & TIOCM_CTS)
		v24_sig |= RFCOMM_V24_RTR;
	अगर (set & TIOCM_RI)
		v24_sig |= RFCOMM_V24_IC;
	अगर (set & TIOCM_CD)
		v24_sig |= RFCOMM_V24_DV;

	अगर (clear & TIOCM_DSR || clear & TIOCM_DTR)
		v24_sig &= ~RFCOMM_V24_RTC;
	अगर (clear & TIOCM_RTS || clear & TIOCM_CTS)
		v24_sig &= ~RFCOMM_V24_RTR;
	अगर (clear & TIOCM_RI)
		v24_sig &= ~RFCOMM_V24_IC;
	अगर (clear & TIOCM_CD)
		v24_sig &= ~RFCOMM_V24_DV;

	rfcomm_dlc_set_modem_status(dlc, v24_sig);

	वापस 0;
पूर्ण

/* ---- TTY काष्ठाure ---- */

अटल स्थिर काष्ठा tty_operations rfcomm_ops = अणु
	.खोलो			= rfcomm_tty_खोलो,
	.बंद			= rfcomm_tty_बंद,
	.ग_लिखो			= rfcomm_tty_ग_लिखो,
	.ग_लिखो_room		= rfcomm_tty_ग_लिखो_room,
	.अक्षरs_in_buffer	= rfcomm_tty_अक्षरs_in_buffer,
	.flush_buffer		= rfcomm_tty_flush_buffer,
	.ioctl			= rfcomm_tty_ioctl,
	.throttle		= rfcomm_tty_throttle,
	.unthrottle		= rfcomm_tty_unthrottle,
	.set_termios		= rfcomm_tty_set_termios,
	.send_xअक्षर		= rfcomm_tty_send_xअक्षर,
	.hangup			= rfcomm_tty_hangup,
	.रुको_until_sent	= rfcomm_tty_रुको_until_sent,
	.tiocmget		= rfcomm_tty_tiocmget,
	.tiocmset		= rfcomm_tty_tiocmset,
	.install                = rfcomm_tty_install,
	.cleanup                = rfcomm_tty_cleanup,
पूर्ण;

पूर्णांक __init rfcomm_init_ttys(व्योम)
अणु
	पूर्णांक error;

	rfcomm_tty_driver = alloc_tty_driver(RFCOMM_TTY_PORTS);
	अगर (!rfcomm_tty_driver)
		वापस -ENOMEM;

	rfcomm_tty_driver->driver_name	= "rfcomm";
	rfcomm_tty_driver->name		= "rfcomm";
	rfcomm_tty_driver->major	= RFCOMM_TTY_MAJOR;
	rfcomm_tty_driver->minor_start	= RFCOMM_TTY_MINOR;
	rfcomm_tty_driver->type		= TTY_DRIVER_TYPE_SERIAL;
	rfcomm_tty_driver->subtype	= SERIAL_TYPE_NORMAL;
	rfcomm_tty_driver->flags	= TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	rfcomm_tty_driver->init_termios	= tty_std_termios;
	rfcomm_tty_driver->init_termios.c_cflag	= B9600 | CS8 | CREAD | HUPCL;
	rfcomm_tty_driver->init_termios.c_lflag &= ~ICANON;
	tty_set_operations(rfcomm_tty_driver, &rfcomm_ops);

	error = tty_रेजिस्टर_driver(rfcomm_tty_driver);
	अगर (error) अणु
		BT_ERR("Can't register RFCOMM TTY driver");
		put_tty_driver(rfcomm_tty_driver);
		वापस error;
	पूर्ण

	BT_INFO("RFCOMM TTY layer initialized");

	वापस 0;
पूर्ण

व्योम rfcomm_cleanup_ttys(व्योम)
अणु
	tty_unरेजिस्टर_driver(rfcomm_tty_driver);
	put_tty_driver(rfcomm_tty_driver);
पूर्ण
