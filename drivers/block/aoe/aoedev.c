<शैली गुरु>
/* Copyright (c) 2013 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoedev.c
 * AoE device utility functions; मुख्यtains device list.
 */

#समावेश <linux/hdreg.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश "aoe.h"

अटल व्योम मुक्तtgt(काष्ठा aoedev *d, काष्ठा aoetgt *t);
अटल व्योम skbpoolमुक्त(काष्ठा aoedev *d);

अटल पूर्णांक aoe_dyndevs = 1;
module_param(aoe_dyndevs, पूर्णांक, 0644);
MODULE_PARM_DESC(aoe_dyndevs, "Use dynamic minor numbers for devices.");

अटल काष्ठा aoedev *devlist;
अटल DEFINE_SPINLOCK(devlist_lock);

/* Because some प्रणालीs will have one, many, or no
 *   - partitions,
 *   - slots per shelf,
 *   - or shelves,
 * we need some flexibility in the way the minor numbers
 * are allocated.  So they are dynamic.
 */
#घोषणा N_DEVS ((1U<<MINORBITS)/AOE_PARTITIONS)

अटल DEFINE_SPINLOCK(used_minors_lock);
अटल DECLARE_BITMAP(used_minors, N_DEVS);

अटल पूर्णांक
minor_get_dyn(uदीर्घ *sysminor)
अणु
	uदीर्घ flags;
	uदीर्घ n;
	पूर्णांक error = 0;

	spin_lock_irqsave(&used_minors_lock, flags);
	n = find_first_zero_bit(used_minors, N_DEVS);
	अगर (n < N_DEVS)
		set_bit(n, used_minors);
	अन्यथा
		error = -1;
	spin_unlock_irqrestore(&used_minors_lock, flags);

	*sysminor = n * AOE_PARTITIONS;
	वापस error;
पूर्ण

अटल पूर्णांक
minor_get_अटल(uदीर्घ *sysminor, uदीर्घ aoemaj, पूर्णांक aoemin)
अणु
	uदीर्घ flags;
	uदीर्घ n;
	पूर्णांक error = 0;
	क्रमागत अणु
		/* क्रम backwards compatibility when !aoe_dyndevs,
		 * a अटल number of supported slots per shelf */
		NPERSHELF = 16,
	पूर्ण;

	अगर (aoemin >= NPERSHELF) अणु
		pr_err("aoe: %s %d slots per shelf\n",
			"static minor device numbers support only",
			NPERSHELF);
		error = -1;
		जाओ out;
	पूर्ण

	n = aoemaj * NPERSHELF + aoemin;
	अगर (n >= N_DEVS) अणु
		pr_err("aoe: %s with e%ld.%d\n",
			"cannot use static minor device numbers",
			aoemaj, aoemin);
		error = -1;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&used_minors_lock, flags);
	अगर (test_bit(n, used_minors)) अणु
		pr_err("aoe: %s %lu\n",
			"existing device already has static minor number",
			n);
		error = -1;
	पूर्ण अन्यथा
		set_bit(n, used_minors);
	spin_unlock_irqrestore(&used_minors_lock, flags);
	*sysminor = n * AOE_PARTITIONS;
out:
	वापस error;
पूर्ण

अटल पूर्णांक
minor_get(uदीर्घ *sysminor, uदीर्घ aoemaj, पूर्णांक aoemin)
अणु
	अगर (aoe_dyndevs)
		वापस minor_get_dyn(sysminor);
	अन्यथा
		वापस minor_get_अटल(sysminor, aoemaj, aoemin);
पूर्ण

अटल व्योम
minor_मुक्त(uदीर्घ minor)
अणु
	uदीर्घ flags;

	minor /= AOE_PARTITIONS;
	BUG_ON(minor >= N_DEVS);

	spin_lock_irqsave(&used_minors_lock, flags);
	BUG_ON(!test_bit(minor, used_minors));
	clear_bit(minor, used_minors);
	spin_unlock_irqrestore(&used_minors_lock, flags);
पूर्ण

/*
 * Users who grab a poपूर्णांकer to the device with aoedev_by_aoeaddr
 * स्वतःmatically get a reference count and must be responsible
 * क्रम perक्रमming a aoedev_put.  With the addition of async
 * kthपढ़ो processing I'm no दीर्घer confident that we can
 * guarantee consistency in the face of device flushes.
 *
 * For the समय being, we only bother to add extra references क्रम
 * frames sitting on the iocq.  When the kthपढ़ोs finish processing
 * these frames, they will aoedev_put the device.
 */

व्योम
aoedev_put(काष्ठा aoedev *d)
अणु
	uदीर्घ flags;

	spin_lock_irqsave(&devlist_lock, flags);
	d->ref--;
	spin_unlock_irqrestore(&devlist_lock, flags);
पूर्ण

अटल व्योम
dummy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा aoedev *d;

	d = from_समयr(d, t, समयr);
	अगर (d->flags & DEVFL_TKILL)
		वापस;
	d->समयr.expires = jअगरfies + HZ;
	add_समयr(&d->समयr);
पूर्ण

अटल व्योम
aoe_failip(काष्ठा aoedev *d)
अणु
	काष्ठा request *rq;
	काष्ठा aoe_req *req;
	काष्ठा bio *bio;

	aoe_failbuf(d, d->ip.buf);
	rq = d->ip.rq;
	अगर (rq == शून्य)
		वापस;

	req = blk_mq_rq_to_pdu(rq);
	जबतक ((bio = d->ip.nxbio)) अणु
		bio->bi_status = BLK_STS_IOERR;
		d->ip.nxbio = bio->bi_next;
		req->nr_bios--;
	पूर्ण

	अगर (!req->nr_bios)
		aoe_end_request(d, rq, 0);
पूर्ण

अटल व्योम
करोwndev_frame(काष्ठा list_head *pos)
अणु
	काष्ठा frame *f;

	f = list_entry(pos, काष्ठा frame, head);
	list_del(pos);
	अगर (f->buf) अणु
		f->buf->nframesout--;
		aoe_failbuf(f->t->d, f->buf);
	पूर्ण
	aoe_मुक्तtframe(f);
पूर्ण

व्योम
aoedev_करोwndev(काष्ठा aoedev *d)
अणु
	काष्ठा aoetgt *t, **tt, **te;
	काष्ठा list_head *head, *pos, *nx;
	पूर्णांक i;

	d->flags &= ~DEVFL_UP;

	/* clean out active and to-be-retransmitted buffers */
	क्रम (i = 0; i < NFACTIVE; i++) अणु
		head = &d->factive[i];
		list_क्रम_each_safe(pos, nx, head)
			करोwndev_frame(pos);
	पूर्ण
	head = &d->rexmitq;
	list_क्रम_each_safe(pos, nx, head)
		करोwndev_frame(pos);

	/* reset winकरोw dressings */
	tt = d->tarमाला_लो;
	te = tt + d->ntarमाला_लो;
	क्रम (; tt < te && (t = *tt); tt++) अणु
		aoecmd_wreset(t);
		t->nout = 0;
	पूर्ण

	/* clean out the in-process request (अगर any) */
	aoe_failip(d);

	/* fast fail all pending I/O */
	अगर (d->blkq) अणु
		/* UP is cleared, मुक्तze+quiesce to insure all are errored */
		blk_mq_मुक्तze_queue(d->blkq);
		blk_mq_quiesce_queue(d->blkq);
		blk_mq_unquiesce_queue(d->blkq);
		blk_mq_unमुक्तze_queue(d->blkq);
	पूर्ण

	अगर (d->gd)
		set_capacity(d->gd, 0);
पूर्ण

/* वापस whether the user asked क्रम this particular
 * device to be flushed
 */
अटल पूर्णांक
user_req(अक्षर *s, माप_प्रकार slen, काष्ठा aoedev *d)
अणु
	स्थिर अक्षर *p;
	माप_प्रकार lim;

	अगर (!d->gd)
		वापस 0;
	p = kbasename(d->gd->disk_name);
	lim = माप(d->gd->disk_name);
	lim -= p - d->gd->disk_name;
	अगर (slen < lim)
		lim = slen;

	वापस !म_भेदन(s, p, lim);
पूर्ण

अटल व्योम
मुक्तdev(काष्ठा aoedev *d)
अणु
	काष्ठा aoetgt **t, **e;
	पूर्णांक मुक्तing = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->lock, flags);
	अगर (d->flags & DEVFL_TKILL
	&& !(d->flags & DEVFL_FREEING)) अणु
		d->flags |= DEVFL_FREEING;
		मुक्तing = 1;
	पूर्ण
	spin_unlock_irqrestore(&d->lock, flags);
	अगर (!मुक्तing)
		वापस;

	del_समयr_sync(&d->समयr);
	अगर (d->gd) अणु
		aoedisk_rm_debugfs(d);
		del_gendisk(d->gd);
		put_disk(d->gd);
		blk_mq_मुक्त_tag_set(&d->tag_set);
		blk_cleanup_queue(d->blkq);
	पूर्ण
	t = d->tarमाला_लो;
	e = t + d->ntarमाला_लो;
	क्रम (; t < e && *t; t++)
		मुक्तtgt(d, *t);

	mempool_destroy(d->bufpool);
	skbpoolमुक्त(d);
	minor_मुक्त(d->sysminor);

	spin_lock_irqsave(&d->lock, flags);
	d->flags |= DEVFL_FREED;
	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

क्रमागत flush_parms अणु
	NOT_EXITING = 0,
	EXITING = 1,
पूर्ण;

अटल पूर्णांक
flush(स्थिर अक्षर __user *str, माप_प्रकार cnt, पूर्णांक निकासing)
अणु
	uदीर्घ flags;
	काष्ठा aoedev *d, **dd;
	अक्षर buf[16];
	पूर्णांक all = 0;
	पूर्णांक specअगरied = 0;	/* flush a specअगरic device */
	अचिन्हित पूर्णांक skipflags;

	skipflags = DEVFL_GDALLOC | DEVFL_NEWSIZE | DEVFL_TKILL;

	अगर (!निकासing && cnt >= 3) अणु
		अगर (cnt > माप buf)
			cnt = माप buf;
		अगर (copy_from_user(buf, str, cnt))
			वापस -EFAULT;
		all = !म_भेदन(buf, "all", 3);
		अगर (!all)
			specअगरied = 1;
	पूर्ण

	flush_scheduled_work();
	/* pass one: करो aoedev_करोwndev, which might sleep */
restart1:
	spin_lock_irqsave(&devlist_lock, flags);
	क्रम (d = devlist; d; d = d->next) अणु
		spin_lock(&d->lock);
		अगर (d->flags & DEVFL_TKILL)
			जाओ cont;

		अगर (निकासing) अणु
			/* unconditionally take each device करोwn */
		पूर्ण अन्यथा अगर (specअगरied) अणु
			अगर (!user_req(buf, cnt, d))
				जाओ cont;
		पूर्ण अन्यथा अगर ((!all && (d->flags & DEVFL_UP))
		|| d->flags & skipflags
		|| d->nखोलो
		|| d->ref)
			जाओ cont;

		spin_unlock(&d->lock);
		spin_unlock_irqrestore(&devlist_lock, flags);
		aoedev_करोwndev(d);
		d->flags |= DEVFL_TKILL;
		जाओ restart1;
cont:
		spin_unlock(&d->lock);
	पूर्ण
	spin_unlock_irqrestore(&devlist_lock, flags);

	/* pass two: call मुक्तdev, which might sleep,
	 * क्रम aoedevs marked with DEVFL_TKILL
	 */
restart2:
	spin_lock_irqsave(&devlist_lock, flags);
	क्रम (d = devlist; d; d = d->next) अणु
		spin_lock(&d->lock);
		अगर (d->flags & DEVFL_TKILL
		&& !(d->flags & DEVFL_FREEING)) अणु
			spin_unlock(&d->lock);
			spin_unlock_irqrestore(&devlist_lock, flags);
			मुक्तdev(d);
			जाओ restart2;
		पूर्ण
		spin_unlock(&d->lock);
	पूर्ण

	/* pass three: हटाओ aoedevs marked with DEVFL_FREED */
	क्रम (dd = &devlist, d = *dd; d; d = *dd) अणु
		काष्ठा aoedev *करोomed = शून्य;

		spin_lock(&d->lock);
		अगर (d->flags & DEVFL_FREED) अणु
			*dd = d->next;
			करोomed = d;
		पूर्ण अन्यथा अणु
			dd = &d->next;
		पूर्ण
		spin_unlock(&d->lock);
		अगर (करोomed)
			kमुक्त(करोomed->tarमाला_लो);
		kमुक्त(करोomed);
	पूर्ण
	spin_unlock_irqrestore(&devlist_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक
aoedev_flush(स्थिर अक्षर __user *str, माप_प्रकार cnt)
अणु
	वापस flush(str, cnt, NOT_EXITING);
पूर्ण

/* This has been confirmed to occur once with Tms=3*1000 due to the
 * driver changing link and not processing its transmit ring.  The
 * problem is hard enough to solve by वापसing an error that I'm
 * still punting on "solving" this.
 */
अटल व्योम
skbमुक्त(काष्ठा sk_buff *skb)
अणु
	क्रमागत अणु Sms = 250, Tms = 30 * 1000पूर्ण;
	पूर्णांक i = Tms / Sms;

	अगर (skb == शून्य)
		वापस;
	जबतक (atomic_पढ़ो(&skb_shinfo(skb)->dataref) != 1 && i-- > 0)
		msleep(Sms);
	अगर (i < 0) अणु
		prपूर्णांकk(KERN_ERR
			"aoe: %s holds ref: %s\n",
			skb->dev ? skb->dev->name : "netif",
			"cannot free skb -- memory leaked.");
		वापस;
	पूर्ण
	skb->truesize -= skb->data_len;
	skb_shinfo(skb)->nr_frags = skb->data_len = 0;
	skb_trim(skb, 0);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
skbpoolमुक्त(काष्ठा aoedev *d)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(&d->skbpool, skb, पंचांगp)
		skbमुक्त(skb);

	__skb_queue_head_init(&d->skbpool);
पूर्ण

/* find it or allocate it */
काष्ठा aoedev *
aoedev_by_aoeaddr(uदीर्घ maj, पूर्णांक min, पूर्णांक करो_alloc)
अणु
	काष्ठा aoedev *d;
	पूर्णांक i;
	uदीर्घ flags;
	uदीर्घ sysminor = 0;

	spin_lock_irqsave(&devlist_lock, flags);

	क्रम (d=devlist; d; d=d->next)
		अगर (d->aoemajor == maj && d->aoeminor == min) अणु
			spin_lock(&d->lock);
			अगर (d->flags & DEVFL_TKILL) अणु
				spin_unlock(&d->lock);
				d = शून्य;
				जाओ out;
			पूर्ण
			d->ref++;
			spin_unlock(&d->lock);
			अवरोध;
		पूर्ण
	अगर (d || !करो_alloc || minor_get(&sysminor, maj, min) < 0)
		जाओ out;
	d = kसुस्मृति(1, माप *d, GFP_ATOMIC);
	अगर (!d)
		जाओ out;
	d->tarमाला_लो = kसुस्मृति(NTARGETS, माप(*d->tarमाला_लो), GFP_ATOMIC);
	अगर (!d->tarमाला_लो) अणु
		kमुक्त(d);
		d = शून्य;
		जाओ out;
	पूर्ण
	d->ntarमाला_लो = NTARGETS;
	INIT_WORK(&d->work, aoecmd_sleepwork);
	spin_lock_init(&d->lock);
	INIT_LIST_HEAD(&d->rq_list);
	skb_queue_head_init(&d->skbpool);
	समयr_setup(&d->समयr, dummy_समयr, 0);
	d->समयr.expires = jअगरfies + HZ;
	add_समयr(&d->समयr);
	d->bufpool = शून्य;	/* defer to aoeblk_gdalloc */
	d->tgt = d->tarमाला_लो;
	d->ref = 1;
	क्रम (i = 0; i < NFACTIVE; i++)
		INIT_LIST_HEAD(&d->factive[i]);
	INIT_LIST_HEAD(&d->rexmitq);
	d->sysminor = sysminor;
	d->aoemajor = maj;
	d->aoeminor = min;
	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->next = devlist;
	devlist = d;
 out:
	spin_unlock_irqrestore(&devlist_lock, flags);
	वापस d;
पूर्ण

अटल व्योम
मुक्तtgt(काष्ठा aoedev *d, काष्ठा aoetgt *t)
अणु
	काष्ठा frame *f;
	काष्ठा list_head *pos, *nx, *head;
	काष्ठा aoeअगर *अगरp;

	क्रम (अगरp = t->अगरs; अगरp < &t->अगरs[NAOEIFS]; ++अगरp) अणु
		अगर (!अगरp->nd)
			अवरोध;
		dev_put(अगरp->nd);
	पूर्ण

	head = &t->fमुक्त;
	list_क्रम_each_safe(pos, nx, head) अणु
		list_del(pos);
		f = list_entry(pos, काष्ठा frame, head);
		skbमुक्त(f->skb);
		kमुक्त(f);
	पूर्ण
	kमुक्त(t);
पूर्ण

व्योम
aoedev_निकास(व्योम)
अणु
	flush_scheduled_work();
	flush(शून्य, 0, EXITING);
पूर्ण

पूर्णांक __init
aoedev_init(व्योम)
अणु
	वापस 0;
पूर्ण
