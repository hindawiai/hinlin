<शैली गुरु>
/* Copyright (c) 2012 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoechr.c
 * AoE अक्षरacter device driver
 */

#समावेश <linux/hdreg.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश "aoe.h"

क्रमागत अणु
	//MINOR_STAT = 1, (moved to sysfs)
	MINOR_ERR = 2,
	MINOR_DISCOVER,
	MINOR_INTERFACES,
	MINOR_REVALIDATE,
	MINOR_FLUSH,
	MSGSZ = 2048,
	NMSG = 100,		/* message backlog to retain */
पूर्ण;

काष्ठा aoe_अक्षरdev अणु
	uदीर्घ minor;
	अक्षर name[32];
पूर्ण;

क्रमागत अणु EMFL_VALID = 1 पूर्ण;

काष्ठा ErrMsg अणु
	लघु flags;
	लघु len;
	अक्षर *msg;
पूर्ण;

अटल DEFINE_MUTEX(aoechr_mutex);

/* A ring buffer of error messages, to be पढ़ो through
 * "/dev/etherd/err".  When no messages are present,
 * पढ़ोers will block रुकोing क्रम messages to appear.
 */
अटल काष्ठा ErrMsg emsgs[NMSG];
अटल पूर्णांक emsgs_head_idx, emsgs_tail_idx;
अटल काष्ठा completion emsgs_comp;
अटल spinlock_t emsgs_lock;
अटल पूर्णांक nblocked_emsgs_पढ़ोers;
अटल काष्ठा class *aoe_class;
अटल काष्ठा aoe_अक्षरdev अक्षरdevs[] = अणु
	अणु MINOR_ERR, "err" पूर्ण,
	अणु MINOR_DISCOVER, "discover" पूर्ण,
	अणु MINOR_INTERFACES, "interfaces" पूर्ण,
	अणु MINOR_REVALIDATE, "revalidate" पूर्ण,
	अणु MINOR_FLUSH, "flush" पूर्ण,
पूर्ण;

अटल पूर्णांक
discover(व्योम)
अणु
	aoecmd_cfg(0xffff, 0xff);
	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकerfaces(स्थिर अक्षर __user *str, माप_प्रकार size)
अणु
	अगर (set_aoe_अगरlist(str, size)) अणु
		prपूर्णांकk(KERN_ERR
			"aoe: could not set interface list: too many interfaces\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
revalidate(स्थिर अक्षर __user *str, माप_प्रकार size)
अणु
	पूर्णांक major, minor, n;
	uदीर्घ flags;
	काष्ठा aoedev *d;
	काष्ठा sk_buff *skb;
	अक्षर buf[16];

	अगर (size >= माप buf)
		वापस -EINVAL;
	buf[माप buf - 1] = '\0';
	अगर (copy_from_user(buf, str, size))
		वापस -EFAULT;

	n = माला_पूछो(buf, "e%d.%d", &major, &minor);
	अगर (n != 2) अणु
		pr_err("aoe: invalid device specification %s\n", buf);
		वापस -EINVAL;
	पूर्ण
	d = aoedev_by_aoeaddr(major, minor, 0);
	अगर (!d)
		वापस -EINVAL;
	spin_lock_irqsave(&d->lock, flags);
	aoecmd_cleanslate(d);
	aoecmd_cfg(major, minor);
loop:
	skb = aoecmd_ata_id(d);
	spin_unlock_irqrestore(&d->lock, flags);
	/* try again अगर we are able to sleep a bit,
	 * otherwise give up this revalidation
	 */
	अगर (!skb && !msleep_पूर्णांकerruptible(250)) अणु
		spin_lock_irqsave(&d->lock, flags);
		जाओ loop;
	पूर्ण
	aoedev_put(d);
	अगर (skb) अणु
		काष्ठा sk_buff_head queue;
		__skb_queue_head_init(&queue);
		__skb_queue_tail(&queue, skb);
		aoenet_xmit(&queue);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
aoechr_error(अक्षर *msg)
अणु
	काष्ठा ErrMsg *em;
	अक्षर *mp;
	uदीर्घ flags, n;

	n = म_माप(msg);

	spin_lock_irqsave(&emsgs_lock, flags);

	em = emsgs + emsgs_tail_idx;
	अगर ((em->flags & EMFL_VALID)) अणु
bail:		spin_unlock_irqrestore(&emsgs_lock, flags);
		वापस;
	पूर्ण

	mp = kmemdup(msg, n, GFP_ATOMIC);
	अगर (mp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "aoe: allocation failure, len=%ld\n", n);
		जाओ bail;
	पूर्ण

	em->msg = mp;
	em->flags |= EMFL_VALID;
	em->len = n;

	emsgs_tail_idx++;
	emsgs_tail_idx %= ARRAY_SIZE(emsgs);

	spin_unlock_irqrestore(&emsgs_lock, flags);

	अगर (nblocked_emsgs_पढ़ोers)
		complete(&emsgs_comp);
पूर्ण

अटल sमाप_प्रकार
aoechr_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार cnt, loff_t *offp)
अणु
	पूर्णांक ret = -EINVAL;

	चयन ((अचिन्हित दीर्घ) filp->निजी_data) अणु
	शेष:
		prपूर्णांकk(KERN_INFO "aoe: can't write to that file.\n");
		अवरोध;
	हाल MINOR_DISCOVER:
		ret = discover();
		अवरोध;
	हाल MINOR_INTERFACES:
		ret = पूर्णांकerfaces(buf, cnt);
		अवरोध;
	हाल MINOR_REVALIDATE:
		ret = revalidate(buf, cnt);
		अवरोध;
	हाल MINOR_FLUSH:
		ret = aoedev_flush(buf, cnt);
		अवरोध;
	पूर्ण
	अगर (ret == 0)
		ret = cnt;
	वापस ret;
पूर्ण

अटल पूर्णांक
aoechr_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक n, i;

	mutex_lock(&aoechr_mutex);
	n = iminor(inode);
	filp->निजी_data = (व्योम *) (अचिन्हित दीर्घ) n;

	क्रम (i = 0; i < ARRAY_SIZE(अक्षरdevs); ++i)
		अगर (अक्षरdevs[i].minor == n) अणु
			mutex_unlock(&aoechr_mutex);
			वापस 0;
		पूर्ण
	mutex_unlock(&aoechr_mutex);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
aoechr_rel(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
aoechr_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार cnt, loff_t *off)
अणु
	अचिन्हित दीर्घ n;
	अक्षर *mp;
	काष्ठा ErrMsg *em;
	sमाप_प्रकार len;
	uदीर्घ flags;

	n = (अचिन्हित दीर्घ) filp->निजी_data;
	अगर (n != MINOR_ERR)
		वापस -EFAULT;

	spin_lock_irqsave(&emsgs_lock, flags);

	क्रम (;;) अणु
		em = emsgs + emsgs_head_idx;
		अगर ((em->flags & EMFL_VALID) != 0)
			अवरोध;
		अगर (filp->f_flags & O_NDELAY) अणु
			spin_unlock_irqrestore(&emsgs_lock, flags);
			वापस -EAGAIN;
		पूर्ण
		nblocked_emsgs_पढ़ोers++;

		spin_unlock_irqrestore(&emsgs_lock, flags);

		n = रुको_क्रम_completion_पूर्णांकerruptible(&emsgs_comp);

		spin_lock_irqsave(&emsgs_lock, flags);

		nblocked_emsgs_पढ़ोers--;

		अगर (n) अणु
			spin_unlock_irqrestore(&emsgs_lock, flags);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
	अगर (em->len > cnt) अणु
		spin_unlock_irqrestore(&emsgs_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	mp = em->msg;
	len = em->len;
	em->msg = शून्य;
	em->flags &= ~EMFL_VALID;

	emsgs_head_idx++;
	emsgs_head_idx %= ARRAY_SIZE(emsgs);

	spin_unlock_irqrestore(&emsgs_lock, flags);

	n = copy_to_user(buf, mp, len);
	kमुक्त(mp);
	वापस n == 0 ? len : -EFAULT;
पूर्ण

अटल स्थिर काष्ठा file_operations aoe_fops = अणु
	.ग_लिखो = aoechr_ग_लिखो,
	.पढ़ो = aoechr_पढ़ो,
	.खोलो = aoechr_खोलो,
	.release = aoechr_rel,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल अक्षर *aoe_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "etherd/%s", dev_name(dev));
पूर्ण

पूर्णांक __init
aoechr_init(व्योम)
अणु
	पूर्णांक n, i;

	n = रेजिस्टर_chrdev(AOE_MAJOR, "aoechr", &aoe_fops);
	अगर (n < 0) अणु
		prपूर्णांकk(KERN_ERR "aoe: can't register char device\n");
		वापस n;
	पूर्ण
	init_completion(&emsgs_comp);
	spin_lock_init(&emsgs_lock);
	aoe_class = class_create(THIS_MODULE, "aoe");
	अगर (IS_ERR(aoe_class)) अणु
		unरेजिस्टर_chrdev(AOE_MAJOR, "aoechr");
		वापस PTR_ERR(aoe_class);
	पूर्ण
	aoe_class->devnode = aoe_devnode;

	क्रम (i = 0; i < ARRAY_SIZE(अक्षरdevs); ++i)
		device_create(aoe_class, शून्य,
			      MKDEV(AOE_MAJOR, अक्षरdevs[i].minor), शून्य,
			      अक्षरdevs[i].name);

	वापस 0;
पूर्ण

व्योम
aoechr_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(अक्षरdevs); ++i)
		device_destroy(aoe_class, MKDEV(AOE_MAJOR, अक्षरdevs[i].minor));
	class_destroy(aoe_class);
	unरेजिस्टर_chrdev(AOE_MAJOR, "aoechr");
पूर्ण

