<शैली गुरु>
/* $Id: capi.c,v 1.1.2.7 2004/04/28 09:48:59 armin Exp $
 *
 * CAPI 2.0 Interface क्रम Linux
 *
 * Copyright 1996 by Carsten Paeth <calle@calle.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/fs.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/tty.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/capi.h>
#समावेश <linux/kernelcapi.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/isdn/capiutil.h>
#समावेश <linux/isdn/capicmd.h>

#समावेश "kcapi.h"

MODULE_DESCRIPTION("CAPI4Linux: kernel CAPI layer and /dev/capi20 interface");
MODULE_AUTHOR("Carsten Paeth");
MODULE_LICENSE("GPL");

/* -------- driver inक्रमmation -------------------------------------- */

अटल DEFINE_MUTEX(capi_mutex);
अटल काष्ठा class *capi_class;
अटल पूर्णांक capi_major = 68;		/* allocated */

module_param_named(major, capi_major, uपूर्णांक, 0);

#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
#घोषणा CAPINC_NR_PORTS		32
#घोषणा CAPINC_MAX_PORTS	256

अटल पूर्णांक capi_ttyminors = CAPINC_NR_PORTS;

module_param_named(ttyminors, capi_ttyminors, uपूर्णांक, 0);
#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */

/* -------- defines ------------------------------------------------- */

#घोषणा CAPINC_MAX_RECVQUEUE	10
#घोषणा CAPINC_MAX_SENDQUEUE	10
#घोषणा CAPI_MAX_BLKSIZE	2048

/* -------- data काष्ठाures ----------------------------------------- */

काष्ठा capidev;
काष्ठा capincci;
काष्ठा capiminor;

काष्ठा ackqueue_entry अणु
	काष्ठा list_head	list;
	u16			datahandle;
पूर्ण;

काष्ठा capiminor अणु
	अचिन्हित पूर्णांक      minor;

	काष्ठा capi20_appl	*ap;
	u32			ncci;
	atomic_t		datahandle;
	atomic_t		msgid;

	काष्ठा tty_port port;
	पूर्णांक                ttyinstop;
	पूर्णांक                ttyoutstop;

	काष्ठा sk_buff_head	inqueue;

	काष्ठा sk_buff_head	outqueue;
	पूर्णांक			outbytes;
	काष्ठा sk_buff		*outskb;
	spinlock_t		outlock;

	/* transmit path */
	काष्ठा list_head ackqueue;
	पूर्णांक nack;
	spinlock_t ackqlock;
पूर्ण;

काष्ठा capincci अणु
	काष्ठा list_head list;
	u32		 ncci;
	काष्ठा capidev	*cdev;
#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
	काष्ठा capiminor *minorp;
#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */
पूर्ण;

काष्ठा capidev अणु
	काष्ठा list_head list;
	काष्ठा capi20_appl ap;
	u16		errcode;
	अचिन्हित        userflags;

	काष्ठा sk_buff_head recvqueue;
	रुको_queue_head_t recvरुको;

	काष्ठा list_head nccis;

	काष्ठा mutex lock;
पूर्ण;

/* -------- global variables ---------------------------------------- */

अटल DEFINE_MUTEX(capidev_list_lock);
अटल LIST_HEAD(capidev_list);

#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE

अटल DEFINE_SPINLOCK(capiminors_lock);
अटल काष्ठा capiminor **capiminors;

अटल काष्ठा tty_driver *capinc_tty_driver;

/* -------- datahandles --------------------------------------------- */

अटल पूर्णांक capiminor_add_ack(काष्ठा capiminor *mp, u16 datahandle)
अणु
	काष्ठा ackqueue_entry *n;

	n = kदो_स्मृति(माप(*n), GFP_ATOMIC);
	अगर (unlikely(!n)) अणु
		prपूर्णांकk(KERN_ERR "capi: alloc datahandle failed\n");
		वापस -1;
	पूर्ण
	n->datahandle = datahandle;
	INIT_LIST_HEAD(&n->list);
	spin_lock_bh(&mp->ackqlock);
	list_add_tail(&n->list, &mp->ackqueue);
	mp->nack++;
	spin_unlock_bh(&mp->ackqlock);
	वापस 0;
पूर्ण

अटल पूर्णांक capiminor_del_ack(काष्ठा capiminor *mp, u16 datahandle)
अणु
	काष्ठा ackqueue_entry *p, *पंचांगp;

	spin_lock_bh(&mp->ackqlock);
	list_क्रम_each_entry_safe(p, पंचांगp, &mp->ackqueue, list) अणु
		अगर (p->datahandle == datahandle) अणु
			list_del(&p->list);
			mp->nack--;
			spin_unlock_bh(&mp->ackqlock);
			kमुक्त(p);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&mp->ackqlock);
	वापस -1;
पूर्ण

अटल व्योम capiminor_del_all_ack(काष्ठा capiminor *mp)
अणु
	काष्ठा ackqueue_entry *p, *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &mp->ackqueue, list) अणु
		list_del(&p->list);
		kमुक्त(p);
		mp->nack--;
	पूर्ण
पूर्ण


/* -------- काष्ठा capiminor ---------------------------------------- */

अटल व्योम capiminor_destroy(काष्ठा tty_port *port)
अणु
	काष्ठा capiminor *mp = container_of(port, काष्ठा capiminor, port);

	kमुक्त_skb(mp->outskb);
	skb_queue_purge(&mp->inqueue);
	skb_queue_purge(&mp->outqueue);
	capiminor_del_all_ack(mp);
	kमुक्त(mp);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations capiminor_port_ops = अणु
	.deकाष्ठा = capiminor_destroy,
पूर्ण;

अटल काष्ठा capiminor *capiminor_alloc(काष्ठा capi20_appl *ap, u32 ncci)
अणु
	काष्ठा capiminor *mp;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक minor;

	mp = kzalloc(माप(*mp), GFP_KERNEL);
	अगर (!mp) अणु
		prपूर्णांकk(KERN_ERR "capi: can't alloc capiminor\n");
		वापस शून्य;
	पूर्ण

	mp->ap = ap;
	mp->ncci = ncci;
	INIT_LIST_HEAD(&mp->ackqueue);
	spin_lock_init(&mp->ackqlock);

	skb_queue_head_init(&mp->inqueue);
	skb_queue_head_init(&mp->outqueue);
	spin_lock_init(&mp->outlock);

	tty_port_init(&mp->port);
	mp->port.ops = &capiminor_port_ops;

	/* Allocate the least unused minor number. */
	spin_lock(&capiminors_lock);
	क्रम (minor = 0; minor < capi_ttyminors; minor++)
		अगर (!capiminors[minor]) अणु
			capiminors[minor] = mp;
			अवरोध;
		पूर्ण
	spin_unlock(&capiminors_lock);

	अगर (minor == capi_ttyminors) अणु
		prपूर्णांकk(KERN_NOTICE "capi: out of minors\n");
		जाओ err_out1;
	पूर्ण

	mp->minor = minor;

	dev = tty_port_रेजिस्टर_device(&mp->port, capinc_tty_driver, minor,
			शून्य);
	अगर (IS_ERR(dev))
		जाओ err_out2;

	वापस mp;

err_out2:
	spin_lock(&capiminors_lock);
	capiminors[minor] = शून्य;
	spin_unlock(&capiminors_lock);

err_out1:
	tty_port_put(&mp->port);
	वापस शून्य;
पूर्ण

अटल काष्ठा capiminor *capiminor_get(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा capiminor *mp;

	spin_lock(&capiminors_lock);
	mp = capiminors[minor];
	अगर (mp)
		tty_port_get(&mp->port);
	spin_unlock(&capiminors_lock);

	वापस mp;
पूर्ण

अटल अंतरभूत व्योम capiminor_put(काष्ठा capiminor *mp)
अणु
	tty_port_put(&mp->port);
पूर्ण

अटल व्योम capiminor_मुक्त(काष्ठा capiminor *mp)
अणु
	tty_unरेजिस्टर_device(capinc_tty_driver, mp->minor);

	spin_lock(&capiminors_lock);
	capiminors[mp->minor] = शून्य;
	spin_unlock(&capiminors_lock);

	capiminor_put(mp);
पूर्ण

/* -------- काष्ठा capincci ----------------------------------------- */

अटल व्योम capincci_alloc_minor(काष्ठा capidev *cdev, काष्ठा capincci *np)
अणु
	अगर (cdev->userflags & CAPIFLAG_HIGHJACKING)
		np->minorp = capiminor_alloc(&cdev->ap, np->ncci);
पूर्ण

अटल व्योम capincci_मुक्त_minor(काष्ठा capincci *np)
अणु
	काष्ठा capiminor *mp = np->minorp;
	काष्ठा tty_काष्ठा *tty;

	अगर (mp) अणु
		tty = tty_port_tty_get(&mp->port);
		अगर (tty) अणु
			tty_vhangup(tty);
			tty_kref_put(tty);
		पूर्ण

		capiminor_मुक्त(mp);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक capincci_minor_खोलोcount(काष्ठा capincci *np)
अणु
	काष्ठा capiminor *mp = np->minorp;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा tty_काष्ठा *tty;

	अगर (mp) अणु
		tty = tty_port_tty_get(&mp->port);
		अगर (tty) अणु
			count = tty->count;
			tty_kref_put(tty);
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

#अन्यथा /* !CONFIG_ISDN_CAPI_MIDDLEWARE */

अटल अंतरभूत व्योम
capincci_alloc_minor(काष्ठा capidev *cdev, काष्ठा capincci *np) अणु पूर्ण
अटल अंतरभूत व्योम capincci_मुक्त_minor(काष्ठा capincci *np) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_ISDN_CAPI_MIDDLEWARE */

अटल काष्ठा capincci *capincci_alloc(काष्ठा capidev *cdev, u32 ncci)
अणु
	काष्ठा capincci *np;

	np = kzalloc(माप(*np), GFP_KERNEL);
	अगर (!np)
		वापस शून्य;
	np->ncci = ncci;
	np->cdev = cdev;

	capincci_alloc_minor(cdev, np);

	list_add_tail(&np->list, &cdev->nccis);

	वापस np;
पूर्ण

अटल व्योम capincci_मुक्त(काष्ठा capidev *cdev, u32 ncci)
अणु
	काष्ठा capincci *np, *पंचांगp;

	list_क्रम_each_entry_safe(np, पंचांगp, &cdev->nccis, list)
		अगर (ncci == 0xffffffff || np->ncci == ncci) अणु
			capincci_मुक्त_minor(np);
			list_del(&np->list);
			kमुक्त(np);
		पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
अटल काष्ठा capincci *capincci_find(काष्ठा capidev *cdev, u32 ncci)
अणु
	काष्ठा capincci *np;

	list_क्रम_each_entry(np, &cdev->nccis, list)
		अगर (np->ncci == ncci)
			वापस np;
	वापस शून्य;
पूर्ण

/* -------- handle data queue --------------------------------------- */

अटल काष्ठा sk_buff *
gen_data_b3_resp_क्रम(काष्ठा capiminor *mp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;
	nskb = alloc_skb(CAPI_DATA_B3_RESP_LEN, GFP_KERNEL);
	अगर (nskb) अणु
		u16 datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4 + 4 + 2);
		अचिन्हित अक्षर *s = skb_put(nskb, CAPI_DATA_B3_RESP_LEN);
		capimsg_setu16(s, 0, CAPI_DATA_B3_RESP_LEN);
		capimsg_setu16(s, 2, mp->ap->applid);
		capimsg_setu8 (s, 4, CAPI_DATA_B3);
		capimsg_setu8 (s, 5, CAPI_RESP);
		capimsg_setu16(s, 6, atomic_inc_वापस(&mp->msgid));
		capimsg_setu32(s, 8, mp->ncci);
		capimsg_setu16(s, 12, datahandle);
	पूर्ण
	वापस nskb;
पूर्ण

अटल पूर्णांक handle_recv_skb(काष्ठा capiminor *mp, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक datalen = skb->len - CAPIMSG_LEN(skb->data);
	काष्ठा tty_काष्ठा *tty;
	काष्ठा sk_buff *nskb;
	u16 errcode, datahandle;
	काष्ठा tty_ldisc *ld;
	पूर्णांक ret = -1;

	tty = tty_port_tty_get(&mp->port);
	अगर (!tty) अणु
		pr_debug("capi: currently no receiver\n");
		वापस -1;
	पूर्ण

	ld = tty_ldisc_ref(tty);
	अगर (!ld) अणु
		/* fatal error, करो not requeue */
		ret = 0;
		kमुक्त_skb(skb);
		जाओ deref_tty;
	पूर्ण

	अगर (ld->ops->receive_buf == शून्य) अणु
		pr_debug("capi: ldisc has no receive_buf function\n");
		/* fatal error, करो not requeue */
		जाओ मुक्त_skb;
	पूर्ण
	अगर (mp->ttyinstop) अणु
		pr_debug("capi: recv tty throttled\n");
		जाओ deref_ldisc;
	पूर्ण

	अगर (tty->receive_room < datalen) अणु
		pr_debug("capi: no room in tty\n");
		जाओ deref_ldisc;
	पूर्ण

	nskb = gen_data_b3_resp_क्रम(mp, skb);
	अगर (!nskb) अणु
		prपूर्णांकk(KERN_ERR "capi: gen_data_b3_resp failed\n");
		जाओ deref_ldisc;
	पूर्ण

	datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4);

	errcode = capi20_put_message(mp->ap, nskb);

	अगर (errcode == CAPI_NOERROR) अणु
		skb_pull(skb, CAPIMSG_LEN(skb->data));
		pr_debug("capi: DATA_B3_RESP %u len=%d => ldisc\n",
			 datahandle, skb->len);
		ld->ops->receive_buf(tty, skb->data, शून्य, skb->len);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "capi: send DATA_B3_RESP failed=%x\n",
		       errcode);
		kमुक्त_skb(nskb);

		अगर (errcode == CAPI_SENDQUEUEFULL)
			जाओ deref_ldisc;
	पूर्ण

मुक्त_skb:
	ret = 0;
	kमुक्त_skb(skb);

deref_ldisc:
	tty_ldisc_deref(ld);

deref_tty:
	tty_kref_put(tty);
	वापस ret;
पूर्ण

अटल व्योम handle_minor_recv(काष्ठा capiminor *mp)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&mp->inqueue)) != शून्य)
		अगर (handle_recv_skb(mp, skb) < 0) अणु
			skb_queue_head(&mp->inqueue, skb);
			वापस;
		पूर्ण
पूर्ण

अटल व्योम handle_minor_send(काष्ठा capiminor *mp)
अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा sk_buff *skb;
	u16 len;
	u16 errcode;
	u16 datahandle;

	tty = tty_port_tty_get(&mp->port);
	अगर (!tty)
		वापस;

	अगर (mp->ttyoutstop) अणु
		pr_debug("capi: send: tty stopped\n");
		tty_kref_put(tty);
		वापस;
	पूर्ण

	जबतक (1) अणु
		spin_lock_bh(&mp->outlock);
		skb = __skb_dequeue(&mp->outqueue);
		अगर (!skb) अणु
			spin_unlock_bh(&mp->outlock);
			अवरोध;
		पूर्ण
		len = (u16)skb->len;
		mp->outbytes -= len;
		spin_unlock_bh(&mp->outlock);

		datahandle = atomic_inc_वापस(&mp->datahandle);
		skb_push(skb, CAPI_DATA_B3_REQ_LEN);
		स_रखो(skb->data, 0, CAPI_DATA_B3_REQ_LEN);
		capimsg_setu16(skb->data, 0, CAPI_DATA_B3_REQ_LEN);
		capimsg_setu16(skb->data, 2, mp->ap->applid);
		capimsg_setu8 (skb->data, 4, CAPI_DATA_B3);
		capimsg_setu8 (skb->data, 5, CAPI_REQ);
		capimsg_setu16(skb->data, 6, atomic_inc_वापस(&mp->msgid));
		capimsg_setu32(skb->data, 8, mp->ncci);	/* NCCI */
		capimsg_setu32(skb->data, 12, (u32)(दीर्घ)skb->data);/* Data32 */
		capimsg_setu16(skb->data, 16, len);	/* Data length */
		capimsg_setu16(skb->data, 18, datahandle);
		capimsg_setu16(skb->data, 20, 0);	/* Flags */

		अगर (capiminor_add_ack(mp, datahandle) < 0) अणु
			skb_pull(skb, CAPI_DATA_B3_REQ_LEN);

			spin_lock_bh(&mp->outlock);
			__skb_queue_head(&mp->outqueue, skb);
			mp->outbytes += len;
			spin_unlock_bh(&mp->outlock);

			अवरोध;
		पूर्ण
		errcode = capi20_put_message(mp->ap, skb);
		अगर (errcode == CAPI_NOERROR) अणु
			pr_debug("capi: DATA_B3_REQ %u len=%u\n",
				 datahandle, len);
			जारी;
		पूर्ण
		capiminor_del_ack(mp, datahandle);

		अगर (errcode == CAPI_SENDQUEUEFULL) अणु
			skb_pull(skb, CAPI_DATA_B3_REQ_LEN);

			spin_lock_bh(&mp->outlock);
			__skb_queue_head(&mp->outqueue, skb);
			mp->outbytes += len;
			spin_unlock_bh(&mp->outlock);

			अवरोध;
		पूर्ण

		/* ups, drop packet */
		prपूर्णांकk(KERN_ERR "capi: put_message = %x\n", errcode);
		kमुक्त_skb(skb);
	पूर्ण
	tty_kref_put(tty);
पूर्ण

#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */
/* -------- function called by lower level -------------------------- */

अटल व्योम capi_recv_message(काष्ठा capi20_appl *ap, काष्ठा sk_buff *skb)
अणु
	काष्ठा capidev *cdev = ap->निजी;
#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
	काष्ठा capiminor *mp;
	u16 datahandle;
	काष्ठा capincci *np;
#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	mutex_lock(&cdev->lock);

	अगर (CAPIMSG_CMD(skb->data) == CAPI_CONNECT_B3_CONF) अणु
		u16 info = CAPIMSG_U16(skb->data, 12); // Info field
		अगर ((info & 0xff00) == 0)
			capincci_alloc(cdev, CAPIMSG_NCCI(skb->data));
	पूर्ण
	अगर (CAPIMSG_CMD(skb->data) == CAPI_CONNECT_B3_IND)
		capincci_alloc(cdev, CAPIMSG_NCCI(skb->data));

	अगर (CAPIMSG_COMMAND(skb->data) != CAPI_DATA_B3) अणु
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_पूर्णांकerruptible(&cdev->recvरुको);
		जाओ unlock_out;
	पूर्ण

#अगर_अघोषित CONFIG_ISDN_CAPI_MIDDLEWARE
	skb_queue_tail(&cdev->recvqueue, skb);
	wake_up_पूर्णांकerruptible(&cdev->recvरुको);

#अन्यथा /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	np = capincci_find(cdev, CAPIMSG_CONTROL(skb->data));
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "BUG: capi_signal: ncci not found\n");
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_पूर्णांकerruptible(&cdev->recvरुको);
		जाओ unlock_out;
	पूर्ण

	mp = np->minorp;
	अगर (!mp) अणु
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_पूर्णांकerruptible(&cdev->recvरुको);
		जाओ unlock_out;
	पूर्ण
	अगर (CAPIMSG_SUBCOMMAND(skb->data) == CAPI_IND) अणु
		datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4 + 4 + 2);
		pr_debug("capi_signal: DATA_B3_IND %u len=%d\n",
			 datahandle, skb->len-CAPIMSG_LEN(skb->data));
		skb_queue_tail(&mp->inqueue, skb);

		handle_minor_recv(mp);

	पूर्ण अन्यथा अगर (CAPIMSG_SUBCOMMAND(skb->data) == CAPI_CONF) अणु

		datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4);
		pr_debug("capi_signal: DATA_B3_CONF %u 0x%x\n",
			 datahandle,
			 CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4 + 2));
		kमुक्त_skb(skb);
		capiminor_del_ack(mp, datahandle);
		tty_port_tty_wakeup(&mp->port);
		handle_minor_send(mp);

	पूर्ण अन्यथा अणु
		/* ups, let capi application handle it :-) */
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_पूर्णांकerruptible(&cdev->recvरुको);
	पूर्ण
#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */

unlock_out:
	mutex_unlock(&cdev->lock);
पूर्ण

/* -------- file_operations क्रम capidev ----------------------------- */

अटल sमाप_प्रकार
capi_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा capidev *cdev = file->निजी_data;
	काष्ठा sk_buff *skb;
	माप_प्रकार copied;
	पूर्णांक err;

	अगर (!cdev->ap.applid)
		वापस -ENODEV;

	skb = skb_dequeue(&cdev->recvqueue);
	अगर (!skb) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		err = रुको_event_पूर्णांकerruptible(cdev->recvरुको,
					       (skb = skb_dequeue(&cdev->recvqueue)));
		अगर (err)
			वापस err;
	पूर्ण
	अगर (skb->len > count) अणु
		skb_queue_head(&cdev->recvqueue, skb);
		वापस -EMSGSIZE;
	पूर्ण
	अगर (copy_to_user(buf, skb->data, skb->len)) अणु
		skb_queue_head(&cdev->recvqueue, skb);
		वापस -EFAULT;
	पूर्ण
	copied = skb->len;

	kमुक्त_skb(skb);

	वापस copied;
पूर्ण

अटल sमाप_प्रकार
capi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा capidev *cdev = file->निजी_data;
	काष्ठा sk_buff *skb;
	u16 mlen;

	अगर (!cdev->ap.applid)
		वापस -ENODEV;

	अगर (count < CAPIMSG_BASELEN)
		वापस -EINVAL;

	skb = alloc_skb(count, GFP_USER);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (copy_from_user(skb_put(skb, count), buf, count)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण
	mlen = CAPIMSG_LEN(skb->data);
	अगर (CAPIMSG_CMD(skb->data) == CAPI_DATA_B3_REQ) अणु
		अगर (count < CAPI_DATA_B3_REQ_LEN ||
		    (माप_प्रकार)(mlen + CAPIMSG_DATALEN(skb->data)) != count) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mlen != count) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	CAPIMSG_SETAPPID(skb->data, cdev->ap.applid);

	अगर (CAPIMSG_CMD(skb->data) == CAPI_DISCONNECT_B3_RESP) अणु
		अगर (count < CAPI_DISCONNECT_B3_RESP_LEN) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		mutex_lock(&cdev->lock);
		capincci_मुक्त(cdev, CAPIMSG_NCCI(skb->data));
		mutex_unlock(&cdev->lock);
	पूर्ण

	cdev->errcode = capi20_put_message(&cdev->ap, skb);

	अगर (cdev->errcode) अणु
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण
	वापस count;
पूर्ण

अटल __poll_t
capi_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा capidev *cdev = file->निजी_data;
	__poll_t mask = 0;

	अगर (!cdev->ap.applid)
		वापस EPOLLERR;

	poll_रुको(file, &(cdev->recvरुको), रुको);
	mask = EPOLLOUT | EPOLLWRNORM;
	अगर (!skb_queue_empty_lockless(&cdev->recvqueue))
		mask |= EPOLLIN | EPOLLRDNORM;
	वापस mask;
पूर्ण

अटल पूर्णांक
capi_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा capidev *cdev = file->निजी_data;
	capi_ioctl_काष्ठा data;
	पूर्णांक retval = -EINVAL;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल CAPI_REGISTER:
		mutex_lock(&cdev->lock);

		अगर (cdev->ap.applid) अणु
			retval = -EEXIST;
			जाओ रेजिस्टर_out;
		पूर्ण
		अगर (copy_from_user(&cdev->ap.rparam, argp,
				   माप(काष्ठा capi_रेजिस्टर_params))) अणु
			retval = -EFAULT;
			जाओ रेजिस्टर_out;
		पूर्ण
		cdev->ap.निजी = cdev;
		cdev->ap.recv_message = capi_recv_message;
		cdev->errcode = capi20_रेजिस्टर(&cdev->ap);
		retval = (पूर्णांक)cdev->ap.applid;
		अगर (cdev->errcode) अणु
			cdev->ap.applid = 0;
			retval = -EIO;
		पूर्ण

रेजिस्टर_out:
		mutex_unlock(&cdev->lock);
		वापस retval;

	हाल CAPI_GET_VERSION:
		अगर (copy_from_user(&data.contr, argp,
				   माप(data.contr)))
			वापस -EFAULT;
		cdev->errcode = capi20_get_version(data.contr, &data.version);
		अगर (cdev->errcode)
			वापस -EIO;
		अगर (copy_to_user(argp, &data.version,
				 माप(data.version)))
			वापस -EFAULT;
		वापस 0;

	हाल CAPI_GET_SERIAL:
		अगर (copy_from_user(&data.contr, argp,
				   माप(data.contr)))
			वापस -EFAULT;
		cdev->errcode = capi20_get_serial(data.contr, data.serial);
		अगर (cdev->errcode)
			वापस -EIO;
		अगर (copy_to_user(argp, data.serial,
				 माप(data.serial)))
			वापस -EFAULT;
		वापस 0;

	हाल CAPI_GET_PROखाता:
		अगर (copy_from_user(&data.contr, argp,
				   माप(data.contr)))
			वापस -EFAULT;

		अगर (data.contr == 0) अणु
			cdev->errcode = capi20_get_profile(data.contr, &data.profile);
			अगर (cdev->errcode)
				वापस -EIO;

			retval = copy_to_user(argp,
					      &data.profile.ncontroller,
					      माप(data.profile.ncontroller));

		पूर्ण अन्यथा अणु
			cdev->errcode = capi20_get_profile(data.contr, &data.profile);
			अगर (cdev->errcode)
				वापस -EIO;

			retval = copy_to_user(argp, &data.profile,
					      माप(data.profile));
		पूर्ण
		अगर (retval)
			वापस -EFAULT;
		वापस 0;

	हाल CAPI_GET_MANUFACTURER:
		अगर (copy_from_user(&data.contr, argp,
				   माप(data.contr)))
			वापस -EFAULT;
		cdev->errcode = capi20_get_manufacturer(data.contr, data.manufacturer);
		अगर (cdev->errcode)
			वापस -EIO;

		अगर (copy_to_user(argp, data.manufacturer,
				 माप(data.manufacturer)))
			वापस -EFAULT;

		वापस 0;

	हाल CAPI_GET_ERRCODE:
		data.errcode = cdev->errcode;
		cdev->errcode = CAPI_NOERROR;
		अगर (arg) अणु
			अगर (copy_to_user(argp, &data.errcode,
					 माप(data.errcode)))
				वापस -EFAULT;
		पूर्ण
		वापस data.errcode;

	हाल CAPI_INSTALLED:
		अगर (capi20_isinstalled() == CAPI_NOERROR)
			वापस 0;
		वापस -ENXIO;

	हाल CAPI_MANUFACTURER_CMD: अणु
		काष्ठा capi_manufacturer_cmd mcmd;
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&mcmd, argp, माप(mcmd)))
			वापस -EFAULT;
		वापस capi20_manufacturer(mcmd.cmd, mcmd.data);
	पूर्ण
	हाल CAPI_SET_FLAGS:
	हाल CAPI_CLR_FLAGS: अणु
		अचिन्हित userflags;

		अगर (copy_from_user(&userflags, argp, माप(userflags)))
			वापस -EFAULT;

		mutex_lock(&cdev->lock);
		अगर (cmd == CAPI_SET_FLAGS)
			cdev->userflags |= userflags;
		अन्यथा
			cdev->userflags &= ~userflags;
		mutex_unlock(&cdev->lock);
		वापस 0;
	पूर्ण
	हाल CAPI_GET_FLAGS:
		अगर (copy_to_user(argp, &cdev->userflags,
				 माप(cdev->userflags)))
			वापस -EFAULT;
		वापस 0;

#अगर_अघोषित CONFIG_ISDN_CAPI_MIDDLEWARE
	हाल CAPI_NCCI_OPENCOUNT:
		वापस 0;

#अन्यथा /* CONFIG_ISDN_CAPI_MIDDLEWARE */
	हाल CAPI_NCCI_OPENCOUNT: अणु
		काष्ठा capincci *nccip;
		अचिन्हित ncci;
		पूर्णांक count = 0;

		अगर (copy_from_user(&ncci, argp, माप(ncci)))
			वापस -EFAULT;

		mutex_lock(&cdev->lock);
		nccip = capincci_find(cdev, (u32)ncci);
		अगर (nccip)
			count = capincci_minor_खोलोcount(nccip);
		mutex_unlock(&cdev->lock);
		वापस count;
	पूर्ण

	हाल CAPI_NCCI_GETUNIT: अणु
		काष्ठा capincci *nccip;
		काष्ठा capiminor *mp;
		अचिन्हित ncci;
		पूर्णांक unit = -ESRCH;

		अगर (copy_from_user(&ncci, argp, माप(ncci)))
			वापस -EFAULT;

		mutex_lock(&cdev->lock);
		nccip = capincci_find(cdev, (u32)ncci);
		अगर (nccip) अणु
			mp = nccip->minorp;
			अगर (mp)
				unit = mp->minor;
		पूर्ण
		mutex_unlock(&cdev->lock);
		वापस unit;
	पूर्ण
#पूर्ण_अगर /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ
capi_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&capi_mutex);
	ret = capi_ioctl(file, cmd, arg);
	mutex_unlock(&capi_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
capi_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	अगर (cmd == CAPI_MANUFACTURER_CMD) अणु
		काष्ठा अणु
			compat_uदीर्घ_t cmd;
			compat_uptr_t data;
		पूर्ण mcmd32;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&mcmd32, compat_ptr(arg), माप(mcmd32)))
			वापस -EFAULT;

		mutex_lock(&capi_mutex);
		ret = capi20_manufacturer(mcmd32.cmd, compat_ptr(mcmd32.data));
		mutex_unlock(&capi_mutex);

		वापस ret;
	पूर्ण

	वापस capi_unlocked_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक capi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा capidev *cdev;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	mutex_init(&cdev->lock);
	skb_queue_head_init(&cdev->recvqueue);
	init_रुकोqueue_head(&cdev->recvरुको);
	INIT_LIST_HEAD(&cdev->nccis);
	file->निजी_data = cdev;

	mutex_lock(&capidev_list_lock);
	list_add_tail(&cdev->list, &capidev_list);
	mutex_unlock(&capidev_list_lock);

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक capi_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा capidev *cdev = file->निजी_data;

	mutex_lock(&capidev_list_lock);
	list_del(&cdev->list);
	mutex_unlock(&capidev_list_lock);

	अगर (cdev->ap.applid)
		capi20_release(&cdev->ap);
	skb_queue_purge(&cdev->recvqueue);
	capincci_मुक्त(cdev, 0xffffffff);

	kमुक्त(cdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations capi_fops =
अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= capi_पढ़ो,
	.ग_लिखो		= capi_ग_लिखो,
	.poll		= capi_poll,
	.unlocked_ioctl	= capi_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= capi_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= capi_खोलो,
	.release	= capi_release,
पूर्ण;

#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
/* -------- tty_operations क्रम capincci ----------------------------- */

अटल पूर्णांक
capinc_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = capiminor_get(tty->index);
	पूर्णांक ret = tty_standard_install(driver, tty);

	अगर (ret == 0)
		tty->driver_data = mp;
	अन्यथा
		capiminor_put(mp);
	वापस ret;
पूर्ण

अटल व्योम capinc_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	tty->driver_data = शून्य;
	capiminor_put(mp);
पूर्ण

अटल पूर्णांक capinc_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	पूर्णांक err;

	err = tty_port_खोलो(&mp->port, tty, filp);
	अगर (err)
		वापस err;

	handle_minor_recv(mp);
	वापस 0;
पूर्ण

अटल व्योम capinc_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	tty_port_बंद(&mp->port, tty, filp);
पूर्ण

अटल पूर्णांक capinc_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty,
			    स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	काष्ठा sk_buff *skb;

	pr_debug("capinc_tty_write(count=%d)\n", count);

	spin_lock_bh(&mp->outlock);
	skb = mp->outskb;
	अगर (skb) अणु
		mp->outskb = शून्य;
		__skb_queue_tail(&mp->outqueue, skb);
		mp->outbytes += skb->len;
	पूर्ण

	skb = alloc_skb(CAPI_DATA_B3_REQ_LEN + count, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "capinc_tty_write: alloc_skb failed\n");
		spin_unlock_bh(&mp->outlock);
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, CAPI_DATA_B3_REQ_LEN);
	skb_put_data(skb, buf, count);

	__skb_queue_tail(&mp->outqueue, skb);
	mp->outbytes += skb->len;
	spin_unlock_bh(&mp->outlock);

	handle_minor_send(mp);

	वापस count;
पूर्ण

अटल पूर्णांक capinc_tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	bool invoke_send = false;
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 1;

	pr_debug("capinc_put_char(%u)\n", ch);

	spin_lock_bh(&mp->outlock);
	skb = mp->outskb;
	अगर (skb) अणु
		अगर (skb_tailroom(skb) > 0) अणु
			skb_put_u8(skb, ch);
			जाओ unlock_out;
		पूर्ण
		mp->outskb = शून्य;
		__skb_queue_tail(&mp->outqueue, skb);
		mp->outbytes += skb->len;
		invoke_send = true;
	पूर्ण

	skb = alloc_skb(CAPI_DATA_B3_REQ_LEN + CAPI_MAX_BLKSIZE, GFP_ATOMIC);
	अगर (skb) अणु
		skb_reserve(skb, CAPI_DATA_B3_REQ_LEN);
		skb_put_u8(skb, ch);
		mp->outskb = skb;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "capinc_put_char: char %u lost\n", ch);
		ret = 0;
	पूर्ण

unlock_out:
	spin_unlock_bh(&mp->outlock);

	अगर (invoke_send)
		handle_minor_send(mp);

	वापस ret;
पूर्ण

अटल व्योम capinc_tty_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	काष्ठा sk_buff *skb;

	pr_debug("capinc_tty_flush_chars\n");

	spin_lock_bh(&mp->outlock);
	skb = mp->outskb;
	अगर (skb) अणु
		mp->outskb = शून्य;
		__skb_queue_tail(&mp->outqueue, skb);
		mp->outbytes += skb->len;
		spin_unlock_bh(&mp->outlock);

		handle_minor_send(mp);
	पूर्ण अन्यथा
		spin_unlock_bh(&mp->outlock);

	handle_minor_recv(mp);
पूर्ण

अटल पूर्णांक capinc_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	पूर्णांक room;

	room = CAPINC_MAX_SENDQUEUE-skb_queue_len(&mp->outqueue);
	room *= CAPI_MAX_BLKSIZE;
	pr_debug("capinc_tty_write_room = %d\n", room);
	वापस room;
पूर्ण

अटल पूर्णांक capinc_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_chars_in_buffer = %d nack=%d sq=%d rq=%d\n",
		 mp->outbytes, mp->nack,
		 skb_queue_len(&mp->outqueue),
		 skb_queue_len(&mp->inqueue));
	वापस mp->outbytes;
पूर्ण

अटल व्योम capinc_tty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	pr_debug("capinc_tty_set_termios\n");
पूर्ण

अटल व्योम capinc_tty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;
	pr_debug("capinc_tty_throttle\n");
	mp->ttyinstop = 1;
पूर्ण

अटल व्योम capinc_tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_unthrottle\n");
	mp->ttyinstop = 0;
	handle_minor_recv(mp);
पूर्ण

अटल व्योम capinc_tty_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_stop\n");
	mp->ttyoutstop = 1;
पूर्ण

अटल व्योम capinc_tty_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_start\n");
	mp->ttyoutstop = 0;
	handle_minor_send(mp);
पूर्ण

अटल व्योम capinc_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा capiminor *mp = tty->driver_data;

	pr_debug("capinc_tty_hangup\n");
	tty_port_hangup(&mp->port);
पूर्ण

अटल पूर्णांक capinc_tty_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	pr_debug("capinc_tty_break_ctl(%d)\n", state);
	वापस 0;
पूर्ण

अटल व्योम capinc_tty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	pr_debug("capinc_tty_flush_buffer\n");
पूर्ण

अटल व्योम capinc_tty_set_ldisc(काष्ठा tty_काष्ठा *tty)
अणु
	pr_debug("capinc_tty_set_ldisc\n");
पूर्ण

अटल व्योम capinc_tty_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	pr_debug("capinc_tty_send_xchar(%d)\n", ch);
पूर्ण

अटल स्थिर काष्ठा tty_operations capinc_ops = अणु
	.खोलो = capinc_tty_खोलो,
	.बंद = capinc_tty_बंद,
	.ग_लिखो = capinc_tty_ग_लिखो,
	.put_अक्षर = capinc_tty_put_अक्षर,
	.flush_अक्षरs = capinc_tty_flush_अक्षरs,
	.ग_लिखो_room = capinc_tty_ग_लिखो_room,
	.अक्षरs_in_buffer = capinc_tty_अक्षरs_in_buffer,
	.set_termios = capinc_tty_set_termios,
	.throttle = capinc_tty_throttle,
	.unthrottle = capinc_tty_unthrottle,
	.stop = capinc_tty_stop,
	.start = capinc_tty_start,
	.hangup = capinc_tty_hangup,
	.अवरोध_ctl = capinc_tty_अवरोध_ctl,
	.flush_buffer = capinc_tty_flush_buffer,
	.set_ldisc = capinc_tty_set_ldisc,
	.send_xअक्षर = capinc_tty_send_xअक्षर,
	.install = capinc_tty_install,
	.cleanup = capinc_tty_cleanup,
पूर्ण;

अटल पूर्णांक __init capinc_tty_init(व्योम)
अणु
	काष्ठा tty_driver *drv;
	पूर्णांक err;

	अगर (capi_ttyminors > CAPINC_MAX_PORTS)
		capi_ttyminors = CAPINC_MAX_PORTS;
	अगर (capi_ttyminors <= 0)
		capi_ttyminors = CAPINC_NR_PORTS;

	capiminors = kसुस्मृति(capi_ttyminors, माप(काष्ठा capiminor *),
			     GFP_KERNEL);
	अगर (!capiminors)
		वापस -ENOMEM;

	drv = alloc_tty_driver(capi_ttyminors);
	अगर (!drv) अणु
		kमुक्त(capiminors);
		वापस -ENOMEM;
	पूर्ण
	drv->driver_name = "capi_nc";
	drv->name = "capi!";
	drv->major = 0;
	drv->minor_start = 0;
	drv->type = TTY_DRIVER_TYPE_SERIAL;
	drv->subtype = SERIAL_TYPE_NORMAL;
	drv->init_termios = tty_std_termios;
	drv->init_termios.c_अगरlag = ICRNL;
	drv->init_termios.c_oflag = OPOST | ONLCR;
	drv->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	drv->init_termios.c_lflag = 0;
	drv->flags =
		TTY_DRIVER_REAL_RAW | TTY_DRIVER_RESET_TERMIOS |
		TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(drv, &capinc_ops);

	err = tty_रेजिस्टर_driver(drv);
	अगर (err) अणु
		put_tty_driver(drv);
		kमुक्त(capiminors);
		prपूर्णांकk(KERN_ERR "Couldn't register capi_nc driver\n");
		वापस err;
	पूर्ण
	capinc_tty_driver = drv;
	वापस 0;
पूर्ण

अटल व्योम __निकास capinc_tty_निकास(व्योम)
अणु
	tty_unरेजिस्टर_driver(capinc_tty_driver);
	put_tty_driver(capinc_tty_driver);
	kमुक्त(capiminors);
पूर्ण

#अन्यथा /* !CONFIG_ISDN_CAPI_MIDDLEWARE */

अटल अंतरभूत पूर्णांक capinc_tty_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम capinc_tty_निकास(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_ISDN_CAPI_MIDDLEWARE */

/* -------- /proc functions ----------------------------------------- */

/*
 * /proc/capi/capi20:
 *  minor applid nrecvctlpkt nrecvdatapkt nsendctlpkt nsenddatapkt
 */
अटल पूर्णांक __maybe_unused capi20_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा capidev *cdev;
	काष्ठा list_head *l;

	mutex_lock(&capidev_list_lock);
	list_क्रम_each(l, &capidev_list) अणु
		cdev = list_entry(l, काष्ठा capidev, list);
		seq_म_लिखो(m, "0 %d %lu %lu %lu %lu\n",
			   cdev->ap.applid,
			   cdev->ap.nrecvctlpkt,
			   cdev->ap.nrecvdatapkt,
			   cdev->ap.nsentctlpkt,
			   cdev->ap.nsentdatapkt);
	पूर्ण
	mutex_unlock(&capidev_list_lock);
	वापस 0;
पूर्ण

/*
 * /proc/capi/capi20ncci:
 *  applid ncci
 */
अटल पूर्णांक __maybe_unused capi20ncci_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा capidev *cdev;
	काष्ठा capincci *np;

	mutex_lock(&capidev_list_lock);
	list_क्रम_each_entry(cdev, &capidev_list, list) अणु
		mutex_lock(&cdev->lock);
		list_क्रम_each_entry(np, &cdev->nccis, list)
			seq_म_लिखो(m, "%d 0x%x\n", cdev->ap.applid, np->ncci);
		mutex_unlock(&cdev->lock);
	पूर्ण
	mutex_unlock(&capidev_list_lock);
	वापस 0;
पूर्ण

अटल व्योम __init proc_init(व्योम)
अणु
	proc_create_single("capi/capi20", 0, शून्य, capi20_proc_show);
	proc_create_single("capi/capi20ncci", 0, शून्य, capi20ncci_proc_show);
पूर्ण

अटल व्योम __निकास proc_निकास(व्योम)
अणु
	हटाओ_proc_entry("capi/capi20", शून्य);
	हटाओ_proc_entry("capi/capi20ncci", शून्य);
पूर्ण

/* -------- init function and module पूर्णांकerface ---------------------- */


अटल पूर्णांक __init capi_init(व्योम)
अणु
	स्थिर अक्षर *compileinfo;
	पूर्णांक major_ret;
	पूर्णांक ret;

	ret = kcapi_init();
	अगर (ret)
		वापस ret;

	major_ret = रेजिस्टर_chrdev(capi_major, "capi20", &capi_fops);
	अगर (major_ret < 0) अणु
		prपूर्णांकk(KERN_ERR "capi20: unable to get major %d\n", capi_major);
		kcapi_निकास();
		वापस major_ret;
	पूर्ण
	capi_class = class_create(THIS_MODULE, "capi");
	अगर (IS_ERR(capi_class)) अणु
		unरेजिस्टर_chrdev(capi_major, "capi20");
		kcapi_निकास();
		वापस PTR_ERR(capi_class);
	पूर्ण

	device_create(capi_class, शून्य, MKDEV(capi_major, 0), शून्य, "capi20");

	अगर (capinc_tty_init() < 0) अणु
		device_destroy(capi_class, MKDEV(capi_major, 0));
		class_destroy(capi_class);
		unरेजिस्टर_chrdev(capi_major, "capi20");
		kcapi_निकास();
		वापस -ENOMEM;
	पूर्ण

	proc_init();

#अगर_घोषित CONFIG_ISDN_CAPI_MIDDLEWARE
	compileinfo = " (middleware)";
#अन्यथा
	compileinfo = " (no middleware)";
#पूर्ण_अगर
	prपूर्णांकk(KERN_NOTICE "CAPI 2.0 started up with major %d%s\n",
	       capi_major, compileinfo);

	वापस 0;
पूर्ण

अटल व्योम __निकास capi_निकास(व्योम)
अणु
	proc_निकास();

	device_destroy(capi_class, MKDEV(capi_major, 0));
	class_destroy(capi_class);
	unरेजिस्टर_chrdev(capi_major, "capi20");

	capinc_tty_निकास();

	kcapi_निकास();
पूर्ण

module_init(capi_init);
module_निकास(capi_निकास);
