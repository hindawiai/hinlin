<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/aपंचांग/aपंचांगtcp.c - ATM over TCP "device" driver */

/* Written 1997-2000 by Werner Almesberger, EPFL LRC/ICA */


#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग_tcp.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>


बाह्य पूर्णांक aपंचांग_init_aal5(काष्ठा aपंचांग_vcc *vcc); /* "raw" AAL5 transport */


#घोषणा PRIV(dev) ((काष्ठा aपंचांगtcp_dev_data *) ((dev)->dev_data))


काष्ठा aपंचांगtcp_dev_data अणु
	काष्ठा aपंचांग_vcc *vcc;	/* control VCC; शून्य अगर detached */
	पूर्णांक persist;		/* non-zero अगर persistent */
पूर्ण;


#घोषणा DEV_LABEL    "atmtcp"

#घोषणा MAX_VPI_BITS  8	/* simplअगरies lअगरe */
#घोषणा MAX_VCI_BITS 16


/*
 * Hairy code ahead: the control VCC may be बंदd जबतक we're still
 * रुकोing क्रम an answer, so we need to re-validate out_vcc every once
 * in a जबतक.
 */


अटल पूर्णांक aपंचांगtcp_send_control(काष्ठा aपंचांग_vcc *vcc,पूर्णांक type,
    स्थिर काष्ठा aपंचांगtcp_control *msg,पूर्णांक flag)
अणु
	DECLARE_WAITQUEUE(रुको,current);
	काष्ठा aपंचांग_vcc *out_vcc;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांगtcp_control *new_msg;
	पूर्णांक old_test;
	पूर्णांक error = 0;

	out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : शून्य;
	अगर (!out_vcc) वापस -EUNATCH;
	skb = alloc_skb(माप(*msg),GFP_KERNEL);
	अगर (!skb) वापस -ENOMEM;
	mb();
	out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : शून्य;
	अगर (!out_vcc) अणु
		dev_kमुक्त_skb(skb);
		वापस -EUNATCH;
	पूर्ण
	aपंचांग_क्रमce_अक्षरge(out_vcc,skb->truesize);
	new_msg = skb_put(skb, माप(*new_msg));
	*new_msg = *msg;
	new_msg->hdr.length = ATMTCP_HDR_MAGIC;
	new_msg->type = type;
	स_रखो(&new_msg->vcc,0,माप(aपंचांग_kptr_t));
	*(काष्ठा aपंचांग_vcc **) &new_msg->vcc = vcc;
	old_test = test_bit(flag,&vcc->flags);
	out_vcc->push(out_vcc,skb);
	add_रुको_queue(sk_sleep(sk_aपंचांग(vcc)), &रुको);
	जबतक (test_bit(flag,&vcc->flags) == old_test) अणु
		mb();
		out_vcc = PRIV(vcc->dev) ? PRIV(vcc->dev)->vcc : शून्य;
		अगर (!out_vcc) अणु
			error = -EUNATCH;
			अवरोध;
		पूर्ण
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule();
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk_aपंचांग(vcc)), &रुको);
	वापस error;
पूर्ण


अटल पूर्णांक aपंचांगtcp_recv_control(स्थिर काष्ठा aपंचांगtcp_control *msg)
अणु
	काष्ठा aपंचांग_vcc *vcc = *(काष्ठा aपंचांग_vcc **) &msg->vcc;

	vcc->vpi = msg->addr.sap_addr.vpi;
	vcc->vci = msg->addr.sap_addr.vci;
	vcc->qos = msg->qos;
	sk_aपंचांग(vcc)->sk_err = -msg->result;
	चयन (msg->type) अणु
	    हाल ATMTCP_CTRL_OPEN:
		change_bit(ATM_VF_READY,&vcc->flags);
		अवरोध;
	    हाल ATMTCP_CTRL_CLOSE:
		change_bit(ATM_VF_ADDR,&vcc->flags);
		अवरोध;
	    शेष:
		prपूर्णांकk(KERN_ERR "atmtcp_recv_control: unknown type %d\n",
		    msg->type);
		वापस -EINVAL;
	पूर्ण
	wake_up(sk_sleep(sk_aपंचांग(vcc)));
	वापस 0;
पूर्ण


अटल व्योम aपंचांगtcp_v_dev_बंद(काष्ठा aपंचांग_dev *dev)
अणु
	/* Nothing.... Isn't this simple :-)  -- REW */
पूर्ण


अटल पूर्णांक aपंचांगtcp_v_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांगtcp_control msg;
	पूर्णांक error;
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;

	स_रखो(&msg,0,माप(msg));
	msg.addr.sap_family = AF_ATMPVC;
	msg.hdr.vpi = htons(vpi);
	msg.addr.sap_addr.vpi = vpi;
	msg.hdr.vci = htons(vci);
	msg.addr.sap_addr.vci = vci;
	अगर (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC) वापस 0;
	msg.type = ATMTCP_CTRL_OPEN;
	msg.qos = vcc->qos;
	set_bit(ATM_VF_ADDR,&vcc->flags);
	clear_bit(ATM_VF_READY,&vcc->flags); /* just in हाल ... */
	error = aपंचांगtcp_send_control(vcc,ATMTCP_CTRL_OPEN,&msg,ATM_VF_READY);
	अगर (error) वापस error;
	वापस -sk_aपंचांग(vcc)->sk_err;
पूर्ण


अटल व्योम aपंचांगtcp_v_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांगtcp_control msg;

	स_रखो(&msg,0,माप(msg));
	msg.addr.sap_family = AF_ATMPVC;
	msg.addr.sap_addr.vpi = vcc->vpi;
	msg.addr.sap_addr.vci = vcc->vci;
	clear_bit(ATM_VF_READY,&vcc->flags);
	(व्योम) aपंचांगtcp_send_control(vcc,ATMTCP_CTRL_CLOSE,&msg,ATM_VF_ADDR);
पूर्ण


अटल पूर्णांक aपंचांगtcp_v_ioctl(काष्ठा aपंचांग_dev *dev,अचिन्हित पूर्णांक cmd,व्योम __user *arg)
अणु
	काष्ठा aपंचांग_cirange ci;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sock *s;
	पूर्णांक i;

	अगर (cmd != ATM_SETCIRANGE) वापस -ENOIOCTLCMD;
	अगर (copy_from_user(&ci, arg,माप(ci))) वापस -EFAULT;
	अगर (ci.vpi_bits == ATM_CI_MAX) ci.vpi_bits = MAX_VPI_BITS;
	अगर (ci.vci_bits == ATM_CI_MAX) ci.vci_bits = MAX_VCI_BITS;
	अगर (ci.vpi_bits > MAX_VPI_BITS || ci.vpi_bits < 0 ||
	    ci.vci_bits > MAX_VCI_BITS || ci.vci_bits < 0) वापस -EINVAL;
	पढ़ो_lock(&vcc_sklist_lock);
	क्रम(i = 0; i < VCC_HTABLE_SIZE; ++i) अणु
		काष्ठा hlist_head *head = &vcc_hash[i];

		sk_क्रम_each(s, head) अणु
			vcc = aपंचांग_sk(s);
			अगर (vcc->dev != dev)
				जारी;
			अगर ((vcc->vpi >> ci.vpi_bits) ||
			    (vcc->vci >> ci.vci_bits)) अणु
				पढ़ो_unlock(&vcc_sklist_lock);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&vcc_sklist_lock);
	dev->ci_range = ci;
	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगtcp_v_send(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांगtcp_dev_data *dev_data;
	काष्ठा aपंचांग_vcc *out_vcc=शून्य; /* Initializer quietens GCC warning */
	काष्ठा sk_buff *new_skb;
	काष्ठा aपंचांगtcp_hdr *hdr;
	पूर्णांक size;

	अगर (vcc->qos.txtp.traffic_class == ATM_NONE) अणु
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	dev_data = PRIV(vcc->dev);
	अगर (dev_data) out_vcc = dev_data->vcc;
	अगर (!dev_data || !out_vcc) अणु
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb(skb);
		अगर (dev_data) वापस 0;
		atomic_inc(&vcc->stats->tx_err);
		वापस -ENOLINK;
	पूर्ण
	size = skb->len+माप(काष्ठा aपंचांगtcp_hdr);
	new_skb = aपंचांग_alloc_अक्षरge(out_vcc,size,GFP_ATOMIC);
	अगर (!new_skb) अणु
		अगर (vcc->pop) vcc->pop(vcc,skb);
		अन्यथा dev_kमुक्त_skb(skb);
		atomic_inc(&vcc->stats->tx_err);
		वापस -ENOBUFS;
	पूर्ण
	hdr = skb_put(new_skb, माप(काष्ठा aपंचांगtcp_hdr));
	hdr->vpi = htons(vcc->vpi);
	hdr->vci = htons(vcc->vci);
	hdr->length = htonl(skb->len);
	skb_copy_from_linear_data(skb, skb_put(new_skb, skb->len), skb->len);
	अगर (vcc->pop) vcc->pop(vcc,skb);
	अन्यथा dev_kमुक्त_skb(skb);
	out_vcc->push(out_vcc,new_skb);
	atomic_inc(&vcc->stats->tx);
	atomic_inc(&out_vcc->stats->rx);
	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगtcp_v_proc(काष्ठा aपंचांग_dev *dev,loff_t *pos,अक्षर *page)
अणु
	काष्ठा aपंचांगtcp_dev_data *dev_data = PRIV(dev);

	अगर (*pos) वापस 0;
	अगर (!dev_data->persist) वापस प्र_लिखो(page,"ephemeral\n");
	वापस प्र_लिखो(page,"persistent, %sconnected\n",
	    dev_data->vcc ? "" : "dis");
पूर्ण


अटल व्योम aपंचांगtcp_c_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांग_dev *aपंचांगtcp_dev;
	काष्ठा aपंचांगtcp_dev_data *dev_data;

	aपंचांगtcp_dev = (काष्ठा aपंचांग_dev *) vcc->dev_data;
	dev_data = PRIV(aपंचांगtcp_dev);
	dev_data->vcc = शून्य;
	अगर (dev_data->persist) वापस;
	aपंचांगtcp_dev->dev_data = शून्य;
	kमुक्त(dev_data);
	aपंचांग_dev_deरेजिस्टर(aपंचांगtcp_dev);
	vcc->dev_data = शून्य;
	module_put(THIS_MODULE);
पूर्ण


अटल काष्ठा aपंचांग_vcc *find_vcc(काष्ठा aपंचांग_dev *dev, लघु vpi, पूर्णांक vci)
अणु
        काष्ठा hlist_head *head;
        काष्ठा aपंचांग_vcc *vcc;
        काष्ठा sock *s;

        head = &vcc_hash[vci & (VCC_HTABLE_SIZE -1)];

	sk_क्रम_each(s, head) अणु
                vcc = aपंचांग_sk(s);
                अगर (vcc->dev == dev &&
                    vcc->vci == vci && vcc->vpi == vpi &&
                    vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
                                वापस vcc;
                पूर्ण
        पूर्ण
        वापस शून्य;
पूर्ण


अटल पूर्णांक aपंचांगtcp_c_send(काष्ठा aपंचांग_vcc *vcc,काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा aपंचांगtcp_hdr *hdr;
	काष्ठा aपंचांग_vcc *out_vcc;
	काष्ठा sk_buff *new_skb;
	पूर्णांक result = 0;

	अगर (!skb->len) वापस 0;
	dev = vcc->dev_data;
	hdr = (काष्ठा aपंचांगtcp_hdr *) skb->data;
	अगर (hdr->length == ATMTCP_HDR_MAGIC) अणु
		result = aपंचांगtcp_recv_control(
		    (काष्ठा aपंचांगtcp_control *) skb->data);
		जाओ करोne;
	पूर्ण
	पढ़ो_lock(&vcc_sklist_lock);
	out_vcc = find_vcc(dev, ntohs(hdr->vpi), ntohs(hdr->vci));
	पढ़ो_unlock(&vcc_sklist_lock);
	अगर (!out_vcc) अणु
		result = -EUNATCH;
		atomic_inc(&vcc->stats->tx_err);
		जाओ करोne;
	पूर्ण
	skb_pull(skb,माप(काष्ठा aपंचांगtcp_hdr));
	new_skb = aपंचांग_alloc_अक्षरge(out_vcc,skb->len,GFP_KERNEL);
	अगर (!new_skb) अणु
		result = -ENOBUFS;
		जाओ करोne;
	पूर्ण
	__net_बारtamp(new_skb);
	skb_copy_from_linear_data(skb, skb_put(new_skb, skb->len), skb->len);
	out_vcc->push(out_vcc,new_skb);
	atomic_inc(&vcc->stats->tx);
	atomic_inc(&out_vcc->stats->rx);
करोne:
	अगर (vcc->pop) vcc->pop(vcc,skb);
	अन्यथा dev_kमुक्त_skb(skb);
	वापस result;
पूर्ण


/*
 * Device operations क्रम the भव ATM devices created by ATMTCP.
 */


अटल स्थिर काष्ठा aपंचांगdev_ops aपंचांगtcp_v_dev_ops = अणु
	.dev_बंद	= aपंचांगtcp_v_dev_बंद,
	.खोलो		= aपंचांगtcp_v_खोलो,
	.बंद		= aपंचांगtcp_v_बंद,
	.ioctl		= aपंचांगtcp_v_ioctl,
	.send		= aपंचांगtcp_v_send,
	.proc_पढ़ो	= aपंचांगtcp_v_proc,
	.owner		= THIS_MODULE
पूर्ण;


/*
 * Device operations क्रम the ATMTCP control device.
 */


अटल स्थिर काष्ठा aपंचांगdev_ops aपंचांगtcp_c_dev_ops = अणु
	.बंद		= aपंचांगtcp_c_बंद,
	.send		= aपंचांगtcp_c_send
पूर्ण;


अटल काष्ठा aपंचांग_dev aपंचांगtcp_control_dev = अणु
	.ops		= &aपंचांगtcp_c_dev_ops,
	.type		= "atmtcp",
	.number		= 999,
	.lock		= __SPIN_LOCK_UNLOCKED(aपंचांगtcp_control_dev.lock)
पूर्ण;


अटल पूर्णांक aपंचांगtcp_create(पूर्णांक itf,पूर्णांक persist,काष्ठा aपंचांग_dev **result)
अणु
	काष्ठा aपंचांगtcp_dev_data *dev_data;
	काष्ठा aपंचांग_dev *dev;

	dev_data = kदो_स्मृति(माप(*dev_data),GFP_KERNEL);
	अगर (!dev_data)
		वापस -ENOMEM;

	dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL,शून्य,&aपंचांगtcp_v_dev_ops,itf,शून्य);
	अगर (!dev) अणु
		kमुक्त(dev_data);
		वापस itf == -1 ? -ENOMEM : -EBUSY;
	पूर्ण
	dev->ci_range.vpi_bits = MAX_VPI_BITS;
	dev->ci_range.vci_bits = MAX_VCI_BITS;
	dev->dev_data = dev_data;
	PRIV(dev)->vcc = शून्य;
	PRIV(dev)->persist = persist;
	अगर (result) *result = dev;
	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगtcp_attach(काष्ठा aपंचांग_vcc *vcc,पूर्णांक itf)
अणु
	काष्ठा aपंचांग_dev *dev;

	dev = शून्य;
	अगर (itf != -1) dev = aपंचांग_dev_lookup(itf);
	अगर (dev) अणु
		अगर (dev->ops != &aपंचांगtcp_v_dev_ops) अणु
			aपंचांग_dev_put(dev);
			वापस -EMEDIUMTYPE;
		पूर्ण
		अगर (PRIV(dev)->vcc) अणु
			aपंचांग_dev_put(dev);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		पूर्णांक error;

		error = aपंचांगtcp_create(itf,0,&dev);
		अगर (error) वापस error;
	पूर्ण
	PRIV(dev)->vcc = vcc;
	vcc->dev = &aपंचांगtcp_control_dev;
	vcc_insert_socket(sk_aपंचांग(vcc));
	set_bit(ATM_VF_META,&vcc->flags);
	set_bit(ATM_VF_READY,&vcc->flags);
	vcc->dev_data = dev;
	(व्योम) aपंचांग_init_aal5(vcc); /* @@@ losing AAL in transit ... */
	vcc->stats = &aपंचांगtcp_control_dev.stats.aal5;
	वापस dev->number;
पूर्ण


अटल पूर्णांक aपंचांगtcp_create_persistent(पूर्णांक itf)
अणु
	वापस aपंचांगtcp_create(itf,1,शून्य);
पूर्ण


अटल पूर्णांक aपंचांगtcp_हटाओ_persistent(पूर्णांक itf)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा aपंचांगtcp_dev_data *dev_data;

	dev = aपंचांग_dev_lookup(itf);
	अगर (!dev) वापस -ENODEV;
	अगर (dev->ops != &aपंचांगtcp_v_dev_ops) अणु
		aपंचांग_dev_put(dev);
		वापस -EMEDIUMTYPE;
	पूर्ण
	dev_data = PRIV(dev);
	अगर (!dev_data->persist) अणु
		aपंचांग_dev_put(dev);
		वापस 0;
	पूर्ण
	dev_data->persist = 0;
	अगर (PRIV(dev)->vcc) अणु
		aपंचांग_dev_put(dev);
		वापस 0;
	पूर्ण
	kमुक्त(dev_data);
	aपंचांग_dev_put(dev);
	aपंचांग_dev_deरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगtcp_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);

	अगर (cmd != SIOCSIFATMTCP && cmd != ATMTCP_CREATE && cmd != ATMTCP_REMOVE)
		वापस -ENOIOCTLCMD;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
		हाल SIOCSIFATMTCP:
			err = aपंचांगtcp_attach(vcc, (पूर्णांक) arg);
			अगर (err >= 0) अणु
				sock->state = SS_CONNECTED;
				__module_get(THIS_MODULE);
			पूर्ण
			अवरोध;
		हाल ATMTCP_CREATE:
			err = aपंचांगtcp_create_persistent((पूर्णांक) arg);
			अवरोध;
		हाल ATMTCP_REMOVE:
			err = aपंचांगtcp_हटाओ_persistent((पूर्णांक) arg);
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा aपंचांग_ioctl aपंचांगtcp_ioctl_ops = अणु
	.owner 	= THIS_MODULE,
	.ioctl	= aपंचांगtcp_ioctl,
पूर्ण;

अटल __init पूर्णांक aपंचांगtcp_init(व्योम)
अणु
	रेजिस्टर_aपंचांग_ioctl(&aपंचांगtcp_ioctl_ops);
	वापस 0;
पूर्ण


अटल व्योम __निकास aपंचांगtcp_निकास(व्योम)
अणु
	deरेजिस्टर_aपंचांग_ioctl(&aपंचांगtcp_ioctl_ops);
पूर्ण

MODULE_LICENSE("GPL");
module_init(aपंचांगtcp_init);
module_निकास(aपंचांगtcp_निकास);
