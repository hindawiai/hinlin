<शैली गुरु>
/* Copyright (c) 2013 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoecmd.c
 * Fileप्रणाली request handling methods
 */

#समावेश <linux/ata.h>
#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/genhd.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <net/net_namespace.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uपन.स>
#समावेश "aoe.h"

#घोषणा MAXIOC (8192)	/* शेष meant to aव्योम most soft lockups */

अटल व्योम ktcomplete(काष्ठा frame *, काष्ठा sk_buff *);
अटल पूर्णांक count_tarमाला_लो(काष्ठा aoedev *d, पूर्णांक *untaपूर्णांकed);

अटल काष्ठा buf *nextbuf(काष्ठा aoedev *);

अटल पूर्णांक aoe_deadsecs = 60 * 3;
module_param(aoe_deadsecs, पूर्णांक, 0644);
MODULE_PARM_DESC(aoe_deadsecs, "After aoe_deadsecs seconds, give up and fail dev.");

अटल पूर्णांक aoe_maxout = 64;
module_param(aoe_maxout, पूर्णांक, 0644);
MODULE_PARM_DESC(aoe_maxout,
	"Only aoe_maxout outstanding packets for every MAC on eX.Y.");

/* The number of online cpus during module initialization gives us a
 * convenient heuristic cap on the parallelism used क्रम ktio thपढ़ोs
 * करोing I/O completion.  It is not important that the cap equal the
 * actual number of running CPUs at any given समय, but because of CPU
 * hotplug, we take care to use ncpus instead of using
 * num_online_cpus() after module initialization.
 */
अटल पूर्णांक ncpus;

/* mutex lock used क्रम synchronization जबतक thपढ़ो spawning */
अटल DEFINE_MUTEX(ktio_spawn_lock);

अटल रुको_queue_head_t *ktiowq;
अटल काष्ठा ktstate *kts;

/* io completion queue */
काष्ठा iocq_ktio अणु
	काष्ठा list_head head;
	spinlock_t lock;
पूर्ण;
अटल काष्ठा iocq_ktio *iocq;

अटल काष्ठा page *empty_page;

अटल काष्ठा sk_buff *
new_skb(uदीर्घ len)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len + MAX_HEADER, GFP_ATOMIC);
	अगर (skb) अणु
		skb_reserve(skb, MAX_HEADER);
		skb_reset_mac_header(skb);
		skb_reset_network_header(skb);
		skb->protocol = __स्थिरant_htons(ETH_P_AOE);
		skb_checksum_none_निश्चित(skb);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा frame *
getframe_deferred(काष्ठा aoedev *d, u32 tag)
अणु
	काष्ठा list_head *head, *pos, *nx;
	काष्ठा frame *f;

	head = &d->rexmitq;
	list_क्रम_each_safe(pos, nx, head) अणु
		f = list_entry(pos, काष्ठा frame, head);
		अगर (f->tag == tag) अणु
			list_del(pos);
			वापस f;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा frame *
getframe(काष्ठा aoedev *d, u32 tag)
अणु
	काष्ठा frame *f;
	काष्ठा list_head *head, *pos, *nx;
	u32 n;

	n = tag % NFACTIVE;
	head = &d->factive[n];
	list_क्रम_each_safe(pos, nx, head) अणु
		f = list_entry(pos, काष्ठा frame, head);
		अगर (f->tag == tag) अणु
			list_del(pos);
			वापस f;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Leave the top bit clear so we have tagspace क्रम userland.
 * The bottom 16 bits are the xmit tick क्रम rexmit/rttavg processing.
 * This driver reserves tag -1 to mean "unused frame."
 */
अटल पूर्णांक
newtag(काष्ठा aoedev *d)
अणु
	रेजिस्टर uदीर्घ n;

	n = jअगरfies & 0xffff;
	वापस n |= (++d->lasttag & 0x7fff) << 16;
पूर्ण

अटल u32
aoehdr_atainit(काष्ठा aoedev *d, काष्ठा aoetgt *t, काष्ठा aoe_hdr *h)
अणु
	u32 host_tag = newtag(d);

	स_नकल(h->src, t->अगरp->nd->dev_addr, माप h->src);
	स_नकल(h->dst, t->addr, माप h->dst);
	h->type = __स्थिरant_cpu_to_be16(ETH_P_AOE);
	h->verfl = AOE_HVER;
	h->major = cpu_to_be16(d->aoemajor);
	h->minor = d->aoeminor;
	h->cmd = AOECMD_ATA;
	h->tag = cpu_to_be32(host_tag);

	वापस host_tag;
पूर्ण

अटल अंतरभूत व्योम
put_lba(काष्ठा aoe_atahdr *ah, sector_t lba)
अणु
	ah->lba0 = lba;
	ah->lba1 = lba >>= 8;
	ah->lba2 = lba >>= 8;
	ah->lba3 = lba >>= 8;
	ah->lba4 = lba >>= 8;
	ah->lba5 = lba >>= 8;
पूर्ण

अटल काष्ठा aoeअगर *
अगरrotate(काष्ठा aoetgt *t)
अणु
	काष्ठा aoeअगर *अगरp;

	अगरp = t->अगरp;
	अगरp++;
	अगर (अगरp >= &t->अगरs[NAOEIFS] || अगरp->nd == शून्य)
		अगरp = t->अगरs;
	अगर (अगरp->nd == शून्य)
		वापस शून्य;
	वापस t->अगरp = अगरp;
पूर्ण

अटल व्योम
skb_pool_put(काष्ठा aoedev *d, काष्ठा sk_buff *skb)
अणु
	__skb_queue_tail(&d->skbpool, skb);
पूर्ण

अटल काष्ठा sk_buff *
skb_pool_get(काष्ठा aoedev *d)
अणु
	काष्ठा sk_buff *skb = skb_peek(&d->skbpool);

	अगर (skb && atomic_पढ़ो(&skb_shinfo(skb)->dataref) == 1) अणु
		__skb_unlink(skb, &d->skbpool);
		वापस skb;
	पूर्ण
	अगर (skb_queue_len(&d->skbpool) < NSKBPOOLMAX &&
	    (skb = new_skb(ETH_ZLEN)))
		वापस skb;

	वापस शून्य;
पूर्ण

व्योम
aoe_मुक्तtframe(काष्ठा frame *f)
अणु
	काष्ठा aoetgt *t;

	t = f->t;
	f->buf = शून्य;
	स_रखो(&f->iter, 0, माप(f->iter));
	f->r_skb = शून्य;
	f->flags = 0;
	list_add(&f->head, &t->fमुक्त);
पूर्ण

अटल काष्ठा frame *
newtframe(काष्ठा aoedev *d, काष्ठा aoetgt *t)
अणु
	काष्ठा frame *f;
	काष्ठा sk_buff *skb;
	काष्ठा list_head *pos;

	अगर (list_empty(&t->fमुक्त)) अणु
		अगर (t->falloc >= NSKBPOOLMAX*2)
			वापस शून्य;
		f = kसुस्मृति(1, माप(*f), GFP_ATOMIC);
		अगर (f == शून्य)
			वापस शून्य;
		t->falloc++;
		f->t = t;
	पूर्ण अन्यथा अणु
		pos = t->fमुक्त.next;
		list_del(pos);
		f = list_entry(pos, काष्ठा frame, head);
	पूर्ण

	skb = f->skb;
	अगर (skb == शून्य) अणु
		f->skb = skb = new_skb(ETH_ZLEN);
		अगर (!skb) अणु
bail:			aoe_मुक्तtframe(f);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&skb_shinfo(skb)->dataref) != 1) अणु
		skb = skb_pool_get(d);
		अगर (skb == शून्य)
			जाओ bail;
		skb_pool_put(d, f->skb);
		f->skb = skb;
	पूर्ण

	skb->truesize -= skb->data_len;
	skb_shinfo(skb)->nr_frags = skb->data_len = 0;
	skb_trim(skb, 0);
	वापस f;
पूर्ण

अटल काष्ठा frame *
newframe(काष्ठा aoedev *d)
अणु
	काष्ठा frame *f;
	काष्ठा aoetgt *t, **tt;
	पूर्णांक totout = 0;
	पूर्णांक use_taपूर्णांकed;
	पूर्णांक has_untaपूर्णांकed;

	अगर (!d->tarमाला_लो || !d->tarमाला_लो[0]) अणु
		prपूर्णांकk(KERN_ERR "aoe: NULL TARGETS!\n");
		वापस शून्य;
	पूर्ण
	tt = d->tgt;	/* last used target */
	क्रम (use_taपूर्णांकed = 0, has_untaपूर्णांकed = 0;;) अणु
		tt++;
		अगर (tt >= &d->tarमाला_लो[d->ntarमाला_लो] || !*tt)
			tt = d->tarमाला_लो;
		t = *tt;
		अगर (!t->taपूर्णांक) अणु
			has_untaपूर्णांकed = 1;
			totout += t->nout;
		पूर्ण
		अगर (t->nout < t->maxout
		&& (use_taपूर्णांकed || !t->taपूर्णांक)
		&& t->अगरp->nd) अणु
			f = newtframe(d, t);
			अगर (f) अणु
				अगरrotate(t);
				d->tgt = tt;
				वापस f;
			पूर्ण
		पूर्ण
		अगर (tt == d->tgt) अणु	/* we've looped and found nada */
			अगर (!use_taपूर्णांकed && !has_untaपूर्णांकed)
				use_taपूर्णांकed = 1;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (totout == 0) अणु
		d->kicked++;
		d->flags |= DEVFL_KICKME;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
skb_fillup(काष्ठा sk_buff *skb, काष्ठा bio *bio, काष्ठा bvec_iter iter)
अणु
	पूर्णांक frag = 0;
	काष्ठा bio_vec bv;

	__bio_क्रम_each_segment(bv, bio, iter, iter)
		skb_fill_page_desc(skb, frag++, bv.bv_page,
				   bv.bv_offset, bv.bv_len);
पूर्ण

अटल व्योम
fhash(काष्ठा frame *f)
अणु
	काष्ठा aoedev *d = f->t->d;
	u32 n;

	n = f->tag % NFACTIVE;
	list_add_tail(&f->head, &d->factive[n]);
पूर्ण

अटल व्योम
ata_rw_frameinit(काष्ठा frame *f)
अणु
	काष्ठा aoetgt *t;
	काष्ठा aoe_hdr *h;
	काष्ठा aoe_atahdr *ah;
	काष्ठा sk_buff *skb;
	अक्षर ग_लिखोbit, extbit;

	skb = f->skb;
	h = (काष्ठा aoe_hdr *) skb_mac_header(skb);
	ah = (काष्ठा aoe_atahdr *) (h + 1);
	skb_put(skb, माप(*h) + माप(*ah));
	स_रखो(h, 0, skb->len);

	ग_लिखोbit = 0x10;
	extbit = 0x4;

	t = f->t;
	f->tag = aoehdr_atainit(t->d, t, h);
	fhash(f);
	t->nout++;
	f->रुकोed = 0;
	f->रुकोed_total = 0;

	/* set up ata header */
	ah->scnt = f->iter.bi_size >> 9;
	put_lba(ah, f->iter.bi_sector);
	अगर (t->d->flags & DEVFL_EXT) अणु
		ah->aflags |= AOEAFL_EXT;
	पूर्ण अन्यथा अणु
		extbit = 0;
		ah->lba3 &= 0x0f;
		ah->lba3 |= 0xe0;	/* LBA bit + obsolete 0xa0 */
	पूर्ण
	अगर (f->buf && bio_data_dir(f->buf->bio) == WRITE) अणु
		skb_fillup(skb, f->buf->bio, f->iter);
		ah->aflags |= AOEAFL_WRITE;
		skb->len += f->iter.bi_size;
		skb->data_len = f->iter.bi_size;
		skb->truesize += f->iter.bi_size;
		t->wpkts++;
	पूर्ण अन्यथा अणु
		t->rpkts++;
		ग_लिखोbit = 0;
	पूर्ण

	ah->cmdstat = ATA_CMD_PIO_READ | ग_लिखोbit | extbit;
	skb->dev = t->अगरp->nd;
पूर्ण

अटल पूर्णांक
aoecmd_ata_rw(काष्ठा aoedev *d)
अणु
	काष्ठा frame *f;
	काष्ठा buf *buf;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head queue;

	buf = nextbuf(d);
	अगर (buf == शून्य)
		वापस 0;
	f = newframe(d);
	अगर (f == शून्य)
		वापस 0;

	/* initialize the headers & frame */
	f->buf = buf;
	f->iter = buf->iter;
	f->iter.bi_size = min_t(अचिन्हित दीर्घ,
				d->maxbcnt ?: DEFAULTBCNT,
				f->iter.bi_size);
	bio_advance_iter(buf->bio, &buf->iter, f->iter.bi_size);

	अगर (!buf->iter.bi_size)
		d->ip.buf = शून्य;

	/* mark all tracking fields and load out */
	buf->nframesout += 1;

	ata_rw_frameinit(f);

	skb = skb_clone(f->skb, GFP_ATOMIC);
	अगर (skb) अणु
		f->sent = kसमय_get();
		__skb_queue_head_init(&queue);
		__skb_queue_tail(&queue, skb);
		aoenet_xmit(&queue);
	पूर्ण
	वापस 1;
पूर्ण

/* some callers cannot sleep, and they can call this function,
 * transmitting the packets later, when पूर्णांकerrupts are on
 */
अटल व्योम
aoecmd_cfg_pkts(uलघु aoemajor, अचिन्हित अक्षर aoeminor, काष्ठा sk_buff_head *queue)
अणु
	काष्ठा aoe_hdr *h;
	काष्ठा aoe_cfghdr *ch;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *अगरp;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, अगरp) अणु
		dev_hold(अगरp);
		अगर (!is_aoe_netअगर(अगरp))
			जाओ cont;

		skb = new_skb(माप *h + माप *ch);
		अगर (skb == शून्य) अणु
			prपूर्णांकk(KERN_INFO "aoe: skb alloc failure\n");
			जाओ cont;
		पूर्ण
		skb_put(skb, माप *h + माप *ch);
		skb->dev = अगरp;
		__skb_queue_tail(queue, skb);
		h = (काष्ठा aoe_hdr *) skb_mac_header(skb);
		स_रखो(h, 0, माप *h + माप *ch);

		स_रखो(h->dst, 0xff, माप h->dst);
		स_नकल(h->src, अगरp->dev_addr, माप h->src);
		h->type = __स्थिरant_cpu_to_be16(ETH_P_AOE);
		h->verfl = AOE_HVER;
		h->major = cpu_to_be16(aoemajor);
		h->minor = aoeminor;
		h->cmd = AOECMD_CFG;

cont:
		dev_put(अगरp);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
resend(काष्ठा aoedev *d, काष्ठा frame *f)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head queue;
	काष्ठा aoe_hdr *h;
	काष्ठा aoetgt *t;
	अक्षर buf[128];
	u32 n;

	t = f->t;
	n = newtag(d);
	skb = f->skb;
	अगर (अगरrotate(t) == शून्य) अणु
		/* probably can't happen, but set it up to fail anyway */
		pr_info("aoe: resend: no interfaces to rotate to.\n");
		ktcomplete(f, शून्य);
		वापस;
	पूर्ण
	h = (काष्ठा aoe_hdr *) skb_mac_header(skb);

	अगर (!(f->flags & FFL_PROBE)) अणु
		snम_लिखो(buf, माप(buf),
			"%15s e%ld.%d oldtag=%08x@%08lx newtag=%08x s=%pm d=%pm nout=%d\n",
			"retransmit", d->aoemajor, d->aoeminor,
			f->tag, jअगरfies, n,
			h->src, h->dst, t->nout);
		aoechr_error(buf);
	पूर्ण

	f->tag = n;
	fhash(f);
	h->tag = cpu_to_be32(n);
	स_नकल(h->dst, t->addr, माप h->dst);
	स_नकल(h->src, t->अगरp->nd->dev_addr, माप h->src);

	skb->dev = t->अगरp->nd;
	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस;
	f->sent = kसमय_get();
	__skb_queue_head_init(&queue);
	__skb_queue_tail(&queue, skb);
	aoenet_xmit(&queue);
पूर्ण

अटल पूर्णांक
tsince_hr(काष्ठा frame *f)
अणु
	u64 delta = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), f->sent));

	/* delta is normally under 4.2 seconds, aव्योम 64-bit भागision */
	अगर (likely(delta <= अच_पूर्णांक_उच्च))
		वापस (u32)delta / NSEC_PER_USEC;

	/* aव्योम overflow after 71 minutes */
	अगर (delta > ((u64)पूर्णांक_उच्च * NSEC_PER_USEC))
		वापस पूर्णांक_उच्च;

	वापस भाग_u64(delta, NSEC_PER_USEC);
पूर्ण

अटल पूर्णांक
tsince(u32 tag)
अणु
	पूर्णांक n;

	n = jअगरfies & 0xffff;
	n -= tag & 0xffff;
	अगर (n < 0)
		n += 1<<16;
	वापस jअगरfies_to_usecs(n + 1);
पूर्ण

अटल काष्ठा aoeअगर *
getअगर(काष्ठा aoetgt *t, काष्ठा net_device *nd)
अणु
	काष्ठा aoeअगर *p, *e;

	p = t->अगरs;
	e = p + NAOEIFS;
	क्रम (; p < e; p++)
		अगर (p->nd == nd)
			वापस p;
	वापस शून्य;
पूर्ण

अटल व्योम
ejectअगर(काष्ठा aoetgt *t, काष्ठा aoeअगर *अगरp)
अणु
	काष्ठा aoeअगर *e;
	काष्ठा net_device *nd;
	uदीर्घ n;

	nd = अगरp->nd;
	e = t->अगरs + NAOEIFS - 1;
	n = (e - अगरp) * माप *अगरp;
	स_हटाओ(अगरp, अगरp+1, n);
	e->nd = शून्य;
	dev_put(nd);
पूर्ण

अटल काष्ठा frame *
reassign_frame(काष्ठा frame *f)
अणु
	काष्ठा frame *nf;
	काष्ठा sk_buff *skb;

	nf = newframe(f->t->d);
	अगर (!nf)
		वापस शून्य;
	अगर (nf->t == f->t) अणु
		aoe_मुक्तtframe(nf);
		वापस शून्य;
	पूर्ण

	skb = nf->skb;
	nf->skb = f->skb;
	nf->buf = f->buf;
	nf->iter = f->iter;
	nf->रुकोed = 0;
	nf->रुकोed_total = f->रुकोed_total;
	nf->sent = f->sent;
	f->skb = skb;

	वापस nf;
पूर्ण

अटल व्योम
probe(काष्ठा aoetgt *t)
अणु
	काष्ठा aoedev *d;
	काष्ठा frame *f;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head queue;
	माप_प्रकार n, m;
	पूर्णांक frag;

	d = t->d;
	f = newtframe(d, t);
	अगर (!f) अणु
		pr_err("%s %pm for e%ld.%d: %s\n",
			"aoe: cannot probe remote address",
			t->addr,
			(दीर्घ) d->aoemajor, d->aoeminor,
			"no frame available");
		वापस;
	पूर्ण
	f->flags |= FFL_PROBE;
	अगरrotate(t);
	f->iter.bi_size = t->d->maxbcnt ? t->d->maxbcnt : DEFAULTBCNT;
	ata_rw_frameinit(f);
	skb = f->skb;
	क्रम (frag = 0, n = f->iter.bi_size; n > 0; ++frag, n -= m) अणु
		अगर (n < PAGE_SIZE)
			m = n;
		अन्यथा
			m = PAGE_SIZE;
		skb_fill_page_desc(skb, frag, empty_page, 0, m);
	पूर्ण
	skb->len += f->iter.bi_size;
	skb->data_len = f->iter.bi_size;
	skb->truesize += f->iter.bi_size;

	skb = skb_clone(f->skb, GFP_ATOMIC);
	अगर (skb) अणु
		f->sent = kसमय_get();
		__skb_queue_head_init(&queue);
		__skb_queue_tail(&queue, skb);
		aoenet_xmit(&queue);
	पूर्ण
पूर्ण

अटल दीर्घ
rto(काष्ठा aoedev *d)
अणु
	दीर्घ t;

	t = 2 * d->rttavg >> RTTSCALE;
	t += 8 * d->rttdev >> RTTDSCALE;
	अगर (t == 0)
		t = 1;

	वापस t;
पूर्ण

अटल व्योम
rexmit_deferred(काष्ठा aoedev *d)
अणु
	काष्ठा aoetgt *t;
	काष्ठा frame *f;
	काष्ठा frame *nf;
	काष्ठा list_head *pos, *nx, *head;
	पूर्णांक since;
	पूर्णांक untaपूर्णांकed;

	count_tarमाला_लो(d, &untaपूर्णांकed);

	head = &d->rexmitq;
	list_क्रम_each_safe(pos, nx, head) अणु
		f = list_entry(pos, काष्ठा frame, head);
		t = f->t;
		अगर (t->taपूर्णांक) अणु
			अगर (!(f->flags & FFL_PROBE)) अणु
				nf = reassign_frame(f);
				अगर (nf) अणु
					अगर (t->nout_probes == 0
					&& untaपूर्णांकed > 0) अणु
						probe(t);
						t->nout_probes++;
					पूर्ण
					list_replace(&f->head, &nf->head);
					pos = &nf->head;
					aoe_मुक्तtframe(f);
					f = nf;
					t = f->t;
				पूर्ण
			पूर्ण अन्यथा अगर (untaपूर्णांकed < 1) अणु
				/* करोn't probe w/o other untaपूर्णांकed aoetgts */
				जाओ stop_probe;
			पूर्ण अन्यथा अगर (tsince_hr(f) < t->taपूर्णांक * rto(d)) अणु
				/* reprobe slowly when taपूर्णांक is high */
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (f->flags & FFL_PROBE) अणु
stop_probe:		/* करोn't probe untaपूर्णांकed aoetgts */
			list_del(pos);
			aoe_मुक्तtframe(f);
			/* leaving d->kicked, because this is routine */
			f->t->d->flags |= DEVFL_KICKME;
			जारी;
		पूर्ण
		अगर (t->nout >= t->maxout)
			जारी;
		list_del(pos);
		t->nout++;
		अगर (f->flags & FFL_PROBE)
			t->nout_probes++;
		since = tsince_hr(f);
		f->रुकोed += since;
		f->रुकोed_total += since;
		resend(d, f);
	पूर्ण
पूर्ण

/* An aoetgt accumulates demerits quickly, and successful
 * probing redeems the aoetgt slowly.
 */
अटल व्योम
scorn(काष्ठा aoetgt *t)
अणु
	पूर्णांक n;

	n = t->taपूर्णांक++;
	t->taपूर्णांक += t->taपूर्णांक * 2;
	अगर (n > t->taपूर्णांक)
		t->taपूर्णांक = n;
	अगर (t->taपूर्णांक > MAX_TAINT)
		t->taपूर्णांक = MAX_TAINT;
पूर्ण

अटल पूर्णांक
count_tarमाला_लो(काष्ठा aoedev *d, पूर्णांक *untaपूर्णांकed)
अणु
	पूर्णांक i, good;

	क्रम (i = good = 0; i < d->ntarमाला_लो && d->tarमाला_लो[i]; ++i)
		अगर (d->tarमाला_लो[i]->taपूर्णांक == 0)
			good++;

	अगर (untaपूर्णांकed)
		*untaपूर्णांकed = good;
	वापस i;
पूर्ण

अटल व्योम
rexmit_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा aoedev *d;
	काष्ठा aoetgt *t;
	काष्ठा aoeअगर *अगरp;
	काष्ठा frame *f;
	काष्ठा list_head *head, *pos, *nx;
	LIST_HEAD(flist);
	रेजिस्टर दीर्घ समयout;
	uदीर्घ flags, n;
	पूर्णांक i;
	पूर्णांक utgts;	/* number of aoetgt descriptors (not slots) */
	पूर्णांक since;

	d = from_समयr(d, समयr, समयr);

	spin_lock_irqsave(&d->lock, flags);

	/* समयout based on observed timings and variations */
	समयout = rto(d);

	utgts = count_tarमाला_लो(d, शून्य);

	अगर (d->flags & DEVFL_TKILL) अणु
		spin_unlock_irqrestore(&d->lock, flags);
		वापस;
	पूर्ण

	/* collect all frames to rexmit पूर्णांकo flist */
	क्रम (i = 0; i < NFACTIVE; i++) अणु
		head = &d->factive[i];
		list_क्रम_each_safe(pos, nx, head) अणु
			f = list_entry(pos, काष्ठा frame, head);
			अगर (tsince_hr(f) < समयout)
				अवरोध;	/* end of expired frames */
			/* move to flist क्रम later processing */
			list_move_tail(pos, &flist);
		पूर्ण
	पूर्ण

	/* process expired frames */
	जबतक (!list_empty(&flist)) अणु
		pos = flist.next;
		f = list_entry(pos, काष्ठा frame, head);
		since = tsince_hr(f);
		n = f->रुकोed_total + since;
		n /= USEC_PER_SEC;
		अगर (aoe_deadsecs
		&& n > aoe_deadsecs
		&& !(f->flags & FFL_PROBE)) अणु
			/* Waited too दीर्घ.  Device failure.
			 * Hang all frames on first hash bucket क्रम करोwndev
			 * to clean up.
			 */
			list_splice(&flist, &d->factive[0]);
			aoedev_करोwndev(d);
			जाओ out;
		पूर्ण

		t = f->t;
		n = f->रुकोed + since;
		n /= USEC_PER_SEC;
		अगर (aoe_deadsecs && utgts > 0
		&& (n > aoe_deadsecs / utgts || n > HARD_SCORN_SECS))
			scorn(t); /* aव्योम this target */

		अगर (t->maxout != 1) अणु
			t->ssthresh = t->maxout / 2;
			t->maxout = 1;
		पूर्ण

		अगर (f->flags & FFL_PROBE) अणु
			t->nout_probes--;
		पूर्ण अन्यथा अणु
			अगरp = getअगर(t, f->skb->dev);
			अगर (अगरp && ++अगरp->lost > (t->nframes << 1)
			&& (अगरp != t->अगरs || t->अगरs[1].nd)) अणु
				ejectअगर(t, अगरp);
				अगरp = शून्य;
			पूर्ण
		पूर्ण
		list_move_tail(pos, &d->rexmitq);
		t->nout--;
	पूर्ण
	rexmit_deferred(d);

out:
	अगर ((d->flags & DEVFL_KICKME) && d->blkq) अणु
		d->flags &= ~DEVFL_KICKME;
		blk_mq_run_hw_queues(d->blkq, true);
	पूर्ण

	d->समयr.expires = jअगरfies + TIMERTICK;
	add_समयr(&d->समयr);

	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

अटल व्योम
bufinit(काष्ठा buf *buf, काष्ठा request *rq, काष्ठा bio *bio)
अणु
	स_रखो(buf, 0, माप(*buf));
	buf->rq = rq;
	buf->bio = bio;
	buf->iter = bio->bi_iter;
पूर्ण

अटल काष्ठा buf *
nextbuf(काष्ठा aoedev *d)
अणु
	काष्ठा request *rq;
	काष्ठा request_queue *q;
	काष्ठा aoe_req *req;
	काष्ठा buf *buf;
	काष्ठा bio *bio;

	q = d->blkq;
	अगर (q == शून्य)
		वापस शून्य;	/* initializing */
	अगर (d->ip.buf)
		वापस d->ip.buf;
	rq = d->ip.rq;
	अगर (rq == शून्य) अणु
		rq = list_first_entry_or_null(&d->rq_list, काष्ठा request,
						queuelist);
		अगर (rq == शून्य)
			वापस शून्य;
		list_del_init(&rq->queuelist);
		blk_mq_start_request(rq);
		d->ip.rq = rq;
		d->ip.nxbio = rq->bio;

		req = blk_mq_rq_to_pdu(rq);
		req->nr_bios = 0;
		__rq_क्रम_each_bio(bio, rq)
			req->nr_bios++;
	पूर्ण
	buf = mempool_alloc(d->bufpool, GFP_ATOMIC);
	अगर (buf == शून्य) अणु
		pr_err("aoe: nextbuf: unable to mempool_alloc!\n");
		वापस शून्य;
	पूर्ण
	bio = d->ip.nxbio;
	bufinit(buf, rq, bio);
	bio = bio->bi_next;
	d->ip.nxbio = bio;
	अगर (bio == शून्य)
		d->ip.rq = शून्य;
	वापस d->ip.buf = buf;
पूर्ण

/* enters with d->lock held */
व्योम
aoecmd_work(काष्ठा aoedev *d)
अणु
	rexmit_deferred(d);
	जबतक (aoecmd_ata_rw(d))
		;
पूर्ण

/* this function perक्रमms work that has been deferred until sleeping is OK
 */
व्योम
aoecmd_sleepwork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aoedev *d = container_of(work, काष्ठा aoedev, work);

	अगर (d->flags & DEVFL_GDALLOC)
		aoeblk_gdalloc(d);

	अगर (d->flags & DEVFL_NEWSIZE) अणु
		set_capacity_and_notअगरy(d->gd, d->ssize);

		spin_lock_irq(&d->lock);
		d->flags |= DEVFL_UP;
		d->flags &= ~DEVFL_NEWSIZE;
		spin_unlock_irq(&d->lock);
	पूर्ण
पूर्ण

अटल व्योम
ata_ident_fixstring(u16 *id, पूर्णांक ns)
अणु
	u16 s;

	जबतक (ns-- > 0) अणु
		s = *id;
		*id++ = s >> 8 | s << 8;
	पूर्ण
पूर्ण

अटल व्योम
ataid_complete(काष्ठा aoedev *d, काष्ठा aoetgt *t, अचिन्हित अक्षर *id)
अणु
	u64 ssize;
	u16 n;

	/* word 83: command set supported */
	n = get_unaligned_le16(&id[83 << 1]);

	/* word 86: command set/feature enabled */
	n |= get_unaligned_le16(&id[86 << 1]);

	अगर (n & (1<<10)) अणु	/* bit 10: LBA 48 */
		d->flags |= DEVFL_EXT;

		/* word 100: number lba48 sectors */
		ssize = get_unaligned_le64(&id[100 << 1]);

		/* set as in ide-disk.c:init_idedisk_capacity */
		d->geo.cylinders = ssize;
		d->geo.cylinders /= (255 * 63);
		d->geo.heads = 255;
		d->geo.sectors = 63;
	पूर्ण अन्यथा अणु
		d->flags &= ~DEVFL_EXT;

		/* number lba28 sectors */
		ssize = get_unaligned_le32(&id[60 << 1]);

		/* NOTE: obsolete in ATA 6 */
		d->geo.cylinders = get_unaligned_le16(&id[54 << 1]);
		d->geo.heads = get_unaligned_le16(&id[55 << 1]);
		d->geo.sectors = get_unaligned_le16(&id[56 << 1]);
	पूर्ण

	ata_ident_fixstring((u16 *) &id[10<<1], 10);	/* serial */
	ata_ident_fixstring((u16 *) &id[23<<1], 4);	/* firmware */
	ata_ident_fixstring((u16 *) &id[27<<1], 20);	/* model */
	स_नकल(d->ident, id, माप(d->ident));

	अगर (d->ssize != ssize)
		prपूर्णांकk(KERN_INFO
			"aoe: %pm e%ld.%d v%04x has %llu sectors\n",
			t->addr,
			d->aoemajor, d->aoeminor,
			d->fw_ver, (दीर्घ दीर्घ)ssize);
	d->ssize = ssize;
	d->geo.start = 0;
	अगर (d->flags & (DEVFL_GDALLOC|DEVFL_NEWSIZE))
		वापस;
	अगर (d->gd != शून्य)
		d->flags |= DEVFL_NEWSIZE;
	अन्यथा
		d->flags |= DEVFL_GDALLOC;
	schedule_work(&d->work);
पूर्ण

अटल व्योम
calc_rttavg(काष्ठा aoedev *d, काष्ठा aoetgt *t, पूर्णांक rtt)
अणु
	रेजिस्टर दीर्घ n;

	n = rtt;

	/* cf. Congestion Aव्योमance and Control, Jacobson & Karels, 1988 */
	n -= d->rttavg >> RTTSCALE;
	d->rttavg += n;
	अगर (n < 0)
		n = -n;
	n -= d->rttdev >> RTTDSCALE;
	d->rttdev += n;

	अगर (!t || t->maxout >= t->nframes)
		वापस;
	अगर (t->maxout < t->ssthresh)
		t->maxout += 1;
	अन्यथा अगर (t->nout == t->maxout && t->next_cwnd-- == 0) अणु
		t->maxout += 1;
		t->next_cwnd = t->maxout;
	पूर्ण
पूर्ण

अटल काष्ठा aoetgt *
gettgt(काष्ठा aoedev *d, अक्षर *addr)
अणु
	काष्ठा aoetgt **t, **e;

	t = d->tarमाला_लो;
	e = t + d->ntarमाला_लो;
	क्रम (; t < e && *t; t++)
		अगर (स_भेद((*t)->addr, addr, माप((*t)->addr)) == 0)
			वापस *t;
	वापस शून्य;
पूर्ण

अटल व्योम
bvcpy(काष्ठा sk_buff *skb, काष्ठा bio *bio, काष्ठा bvec_iter iter, दीर्घ cnt)
अणु
	पूर्णांक soff = 0;
	काष्ठा bio_vec bv;

	iter.bi_size = cnt;

	__bio_क्रम_each_segment(bv, bio, iter, iter) अणु
		अक्षर *p = kmap_atomic(bv.bv_page) + bv.bv_offset;
		skb_copy_bits(skb, soff, p, bv.bv_len);
		kunmap_atomic(p);
		soff += bv.bv_len;
	पूर्ण
पूर्ण

व्योम
aoe_end_request(काष्ठा aoedev *d, काष्ठा request *rq, पूर्णांक fastfail)
अणु
	काष्ठा bio *bio;
	पूर्णांक bok;
	काष्ठा request_queue *q;
	blk_status_t err = BLK_STS_OK;

	q = d->blkq;
	अगर (rq == d->ip.rq)
		d->ip.rq = शून्य;
	करो अणु
		bio = rq->bio;
		bok = !fastfail && !bio->bi_status;
		अगर (!bok)
			err = BLK_STS_IOERR;
	पूर्ण जबतक (blk_update_request(rq, bok ? BLK_STS_OK : BLK_STS_IOERR, bio->bi_iter.bi_size));

	__blk_mq_end_request(rq, err);

	/* cf. https://lore.kernel.org/lkml/20061031071040.GS14055@kernel.dk/ */
	अगर (!fastfail)
		blk_mq_run_hw_queues(q, true);
पूर्ण

अटल व्योम
aoe_end_buf(काष्ठा aoedev *d, काष्ठा buf *buf)
अणु
	काष्ठा request *rq = buf->rq;
	काष्ठा aoe_req *req = blk_mq_rq_to_pdu(rq);

	अगर (buf == d->ip.buf)
		d->ip.buf = शून्य;
	mempool_मुक्त(buf, d->bufpool);
	अगर (--req->nr_bios == 0)
		aoe_end_request(d, rq, 0);
पूर्ण

अटल व्योम
ktiocomplete(काष्ठा frame *f)
अणु
	काष्ठा aoe_hdr *hin, *hout;
	काष्ठा aoe_atahdr *ahin, *ahout;
	काष्ठा buf *buf;
	काष्ठा sk_buff *skb;
	काष्ठा aoetgt *t;
	काष्ठा aoeअगर *अगरp;
	काष्ठा aoedev *d;
	दीर्घ n;
	पूर्णांक untaपूर्णांकed;

	अगर (f == शून्य)
		वापस;

	t = f->t;
	d = t->d;
	skb = f->r_skb;
	buf = f->buf;
	अगर (f->flags & FFL_PROBE)
		जाओ out;
	अगर (!skb)		/* just fail the buf. */
		जाओ noskb;

	hout = (काष्ठा aoe_hdr *) skb_mac_header(f->skb);
	ahout = (काष्ठा aoe_atahdr *) (hout+1);

	hin = (काष्ठा aoe_hdr *) skb->data;
	skb_pull(skb, माप(*hin));
	ahin = (काष्ठा aoe_atahdr *) skb->data;
	skb_pull(skb, माप(*ahin));
	अगर (ahin->cmdstat & 0xa9) अणु	/* these bits cleared on success */
		pr_err("aoe: ata error cmd=%2.2Xh stat=%2.2Xh from e%ld.%d\n",
			ahout->cmdstat, ahin->cmdstat,
			d->aoemajor, d->aoeminor);
noskb:		अगर (buf)
			buf->bio->bi_status = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	n = ahout->scnt << 9;
	चयन (ahout->cmdstat) अणु
	हाल ATA_CMD_PIO_READ:
	हाल ATA_CMD_PIO_READ_EXT:
		अगर (skb->len < n) अणु
			pr_err("%s e%ld.%d.  skb->len=%d need=%ld\n",
				"aoe: runt data size in read from",
				(दीर्घ) d->aoemajor, d->aoeminor,
			       skb->len, n);
			buf->bio->bi_status = BLK_STS_IOERR;
			अवरोध;
		पूर्ण
		अगर (n > f->iter.bi_size) अणु
			pr_err_ratelimited("%s e%ld.%d.  bytes=%ld need=%u\n",
				"aoe: too-large data size in read from",
				(दीर्घ) d->aoemajor, d->aoeminor,
				n, f->iter.bi_size);
			buf->bio->bi_status = BLK_STS_IOERR;
			अवरोध;
		पूर्ण
		bvcpy(skb, f->buf->bio, f->iter, n);
		fallthrough;
	हाल ATA_CMD_PIO_WRITE:
	हाल ATA_CMD_PIO_WRITE_EXT:
		spin_lock_irq(&d->lock);
		अगरp = getअगर(t, skb->dev);
		अगर (अगरp)
			अगरp->lost = 0;
		spin_unlock_irq(&d->lock);
		अवरोध;
	हाल ATA_CMD_ID_ATA:
		अगर (skb->len < 512) अणु
			pr_info("%s e%ld.%d.  skb->len=%d need=512\n",
				"aoe: runt data size in ataid from",
				(दीर्घ) d->aoemajor, d->aoeminor,
				skb->len);
			अवरोध;
		पूर्ण
		अगर (skb_linearize(skb))
			अवरोध;
		spin_lock_irq(&d->lock);
		ataid_complete(d, t, skb->data);
		spin_unlock_irq(&d->lock);
		अवरोध;
	शेष:
		pr_info("aoe: unrecognized ata command %2.2Xh for %d.%d\n",
			ahout->cmdstat,
			be16_to_cpu(get_unaligned(&hin->major)),
			hin->minor);
	पूर्ण
out:
	spin_lock_irq(&d->lock);
	अगर (t->taपूर्णांक > 0
	&& --t->taपूर्णांक > 0
	&& t->nout_probes == 0) अणु
		count_tarमाला_लो(d, &untaपूर्णांकed);
		अगर (untaपूर्णांकed > 0) अणु
			probe(t);
			t->nout_probes++;
		पूर्ण
	पूर्ण

	aoe_मुक्तtframe(f);

	अगर (buf && --buf->nframesout == 0 && buf->iter.bi_size == 0)
		aoe_end_buf(d, buf);

	spin_unlock_irq(&d->lock);
	aoedev_put(d);
	dev_kमुक्त_skb(skb);
पूर्ण

/* Enters with iocq.lock held.
 * Returns true अगरf responses needing processing reमुख्य.
 */
अटल पूर्णांक
ktio(पूर्णांक id)
अणु
	काष्ठा frame *f;
	काष्ठा list_head *pos;
	पूर्णांक i;
	पूर्णांक actual_id;

	क्रम (i = 0; ; ++i) अणु
		अगर (i == MAXIOC)
			वापस 1;
		अगर (list_empty(&iocq[id].head))
			वापस 0;
		pos = iocq[id].head.next;
		list_del(pos);
		f = list_entry(pos, काष्ठा frame, head);
		spin_unlock_irq(&iocq[id].lock);
		ktiocomplete(f);

		/* Figure out अगर extra thपढ़ोs are required. */
		actual_id = f->t->d->aoeminor % ncpus;

		अगर (!kts[actual_id].active) अणु
			BUG_ON(id != 0);
			mutex_lock(&ktio_spawn_lock);
			अगर (!kts[actual_id].active
				&& aoe_ktstart(&kts[actual_id]) == 0)
				kts[actual_id].active = 1;
			mutex_unlock(&ktio_spawn_lock);
		पूर्ण
		spin_lock_irq(&iocq[id].lock);
	पूर्ण
पूर्ण

अटल पूर्णांक
kthपढ़ो(व्योम *vp)
अणु
	काष्ठा ktstate *k;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक more;

	k = vp;
	current->flags |= PF_NOFREEZE;
	set_user_nice(current, -10);
	complete(&k->rendez);	/* tell spawner we're running */
	करो अणु
		spin_lock_irq(k->lock);
		more = k->fn(k->id);
		अगर (!more) अणु
			add_रुको_queue(k->रुकोq, &रुको);
			__set_current_state(TASK_INTERRUPTIBLE);
		पूर्ण
		spin_unlock_irq(k->lock);
		अगर (!more) अणु
			schedule();
			हटाओ_रुको_queue(k->रुकोq, &रुको);
		पूर्ण अन्यथा
			cond_resched();
	पूर्ण जबतक (!kthपढ़ो_should_stop());
	complete(&k->rendez);	/* tell spawner we're stopping */
	वापस 0;
पूर्ण

व्योम
aoe_ktstop(काष्ठा ktstate *k)
अणु
	kthपढ़ो_stop(k->task);
	रुको_क्रम_completion(&k->rendez);
पूर्ण

पूर्णांक
aoe_ktstart(काष्ठा ktstate *k)
अणु
	काष्ठा task_काष्ठा *task;

	init_completion(&k->rendez);
	task = kthपढ़ो_run(kthपढ़ो, k, "%s", k->name);
	अगर (task == शून्य || IS_ERR(task))
		वापस -ENOMEM;
	k->task = task;
	रुको_क्रम_completion(&k->rendez); /* allow kthपढ़ो to start */
	init_completion(&k->rendez);	/* क्रम रुकोing क्रम निकास later */
	वापस 0;
पूर्ण

/* pass it off to kthपढ़ोs क्रम processing */
अटल व्योम
ktcomplete(काष्ठा frame *f, काष्ठा sk_buff *skb)
अणु
	पूर्णांक id;
	uदीर्घ flags;

	f->r_skb = skb;
	id = f->t->d->aoeminor % ncpus;
	spin_lock_irqsave(&iocq[id].lock, flags);
	अगर (!kts[id].active) अणु
		spin_unlock_irqrestore(&iocq[id].lock, flags);
		/* The thपढ़ो with id has not been spawned yet,
		 * so delegate the work to the मुख्य thपढ़ो and
		 * try spawning a new thपढ़ो.
		 */
		id = 0;
		spin_lock_irqsave(&iocq[id].lock, flags);
	पूर्ण
	list_add_tail(&f->head, &iocq[id].head);
	spin_unlock_irqrestore(&iocq[id].lock, flags);
	wake_up(&ktiowq[id]);
पूर्ण

काष्ठा sk_buff *
aoecmd_ata_rsp(काष्ठा sk_buff *skb)
अणु
	काष्ठा aoedev *d;
	काष्ठा aoe_hdr *h;
	काष्ठा frame *f;
	u32 n;
	uदीर्घ flags;
	अक्षर ebuf[128];
	u16 aoemajor;

	h = (काष्ठा aoe_hdr *) skb->data;
	aoemajor = be16_to_cpu(get_unaligned(&h->major));
	d = aoedev_by_aoeaddr(aoemajor, h->minor, 0);
	अगर (d == शून्य) अणु
		snम_लिखो(ebuf, माप ebuf, "aoecmd_ata_rsp: ata response "
			"for unknown device %d.%d\n",
			aoemajor, h->minor);
		aoechr_error(ebuf);
		वापस skb;
	पूर्ण

	spin_lock_irqsave(&d->lock, flags);

	n = be32_to_cpu(get_unaligned(&h->tag));
	f = getframe(d, n);
	अगर (f) अणु
		calc_rttavg(d, f->t, tsince_hr(f));
		f->t->nout--;
		अगर (f->flags & FFL_PROBE)
			f->t->nout_probes--;
	पूर्ण अन्यथा अणु
		f = getframe_deferred(d, n);
		अगर (f) अणु
			calc_rttavg(d, शून्य, tsince_hr(f));
		पूर्ण अन्यथा अणु
			calc_rttavg(d, शून्य, tsince(n));
			spin_unlock_irqrestore(&d->lock, flags);
			aoedev_put(d);
			snम_लिखो(ebuf, माप(ebuf),
				 "%15s e%d.%d    tag=%08x@%08lx s=%pm d=%pm\n",
				 "unexpected rsp",
				 get_unaligned_be16(&h->major),
				 h->minor,
				 get_unaligned_be32(&h->tag),
				 jअगरfies,
				 h->src,
				 h->dst);
			aoechr_error(ebuf);
			वापस skb;
		पूर्ण
	पूर्ण
	aoecmd_work(d);

	spin_unlock_irqrestore(&d->lock, flags);

	ktcomplete(f, skb);

	/*
	 * Note here that we करो not perक्रमm an aoedev_put, as we are
	 * leaving this reference क्रम the ktio to release.
	 */
	वापस शून्य;
पूर्ण

व्योम
aoecmd_cfg(uलघु aoemajor, अचिन्हित अक्षर aoeminor)
अणु
	काष्ठा sk_buff_head queue;

	__skb_queue_head_init(&queue);
	aoecmd_cfg_pkts(aoemajor, aoeminor, &queue);
	aoenet_xmit(&queue);
पूर्ण

काष्ठा sk_buff *
aoecmd_ata_id(काष्ठा aoedev *d)
अणु
	काष्ठा aoe_hdr *h;
	काष्ठा aoe_atahdr *ah;
	काष्ठा frame *f;
	काष्ठा sk_buff *skb;
	काष्ठा aoetgt *t;

	f = newframe(d);
	अगर (f == शून्य)
		वापस शून्य;

	t = *d->tgt;

	/* initialize the headers & frame */
	skb = f->skb;
	h = (काष्ठा aoe_hdr *) skb_mac_header(skb);
	ah = (काष्ठा aoe_atahdr *) (h+1);
	skb_put(skb, माप *h + माप *ah);
	स_रखो(h, 0, skb->len);
	f->tag = aoehdr_atainit(d, t, h);
	fhash(f);
	t->nout++;
	f->रुकोed = 0;
	f->रुकोed_total = 0;

	/* set up ata header */
	ah->scnt = 1;
	ah->cmdstat = ATA_CMD_ID_ATA;
	ah->lba3 = 0xa0;

	skb->dev = t->अगरp->nd;

	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->समयr.function = rexmit_समयr;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (skb)
		f->sent = kसमय_get();

	वापस skb;
पूर्ण

अटल काष्ठा aoetgt **
grow_tarमाला_लो(काष्ठा aoedev *d)
अणु
	uदीर्घ oldn, newn;
	काष्ठा aoetgt **tt;

	oldn = d->ntarमाला_लो;
	newn = oldn * 2;
	tt = kसुस्मृति(newn, माप(*d->tarमाला_लो), GFP_ATOMIC);
	अगर (!tt)
		वापस शून्य;
	स_हटाओ(tt, d->tarमाला_लो, माप(*d->tarमाला_लो) * oldn);
	d->tgt = tt + (d->tgt - d->tarमाला_लो);
	kमुक्त(d->tarमाला_लो);
	d->tarमाला_लो = tt;
	d->ntarमाला_लो = newn;

	वापस &d->tarमाला_लो[oldn];
पूर्ण

अटल काष्ठा aoetgt *
addtgt(काष्ठा aoedev *d, अक्षर *addr, uदीर्घ nframes)
अणु
	काष्ठा aoetgt *t, **tt, **te;

	tt = d->tarमाला_लो;
	te = tt + d->ntarमाला_लो;
	क्रम (; tt < te && *tt; tt++)
		;

	अगर (tt == te) अणु
		tt = grow_tarमाला_लो(d);
		अगर (!tt)
			जाओ nomem;
	पूर्ण
	t = kzalloc(माप(*t), GFP_ATOMIC);
	अगर (!t)
		जाओ nomem;
	t->nframes = nframes;
	t->d = d;
	स_नकल(t->addr, addr, माप t->addr);
	t->अगरp = t->अगरs;
	aoecmd_wreset(t);
	t->maxout = t->nframes / 2;
	INIT_LIST_HEAD(&t->fमुक्त);
	वापस *tt = t;

 nomem:
	pr_info("aoe: cannot allocate memory to add target\n");
	वापस शून्य;
पूर्ण

अटल व्योम
setdbcnt(काष्ठा aoedev *d)
अणु
	काष्ठा aoetgt **t, **e;
	पूर्णांक bcnt = 0;

	t = d->tarमाला_लो;
	e = t + d->ntarमाला_लो;
	क्रम (; t < e && *t; t++)
		अगर (bcnt == 0 || bcnt > (*t)->minbcnt)
			bcnt = (*t)->minbcnt;
	अगर (bcnt != d->maxbcnt) अणु
		d->maxbcnt = bcnt;
		pr_info("aoe: e%ld.%d: setting %d byte data frames\n",
			d->aoemajor, d->aoeminor, bcnt);
	पूर्ण
पूर्ण

अटल व्योम
setअगरbcnt(काष्ठा aoetgt *t, काष्ठा net_device *nd, पूर्णांक bcnt)
अणु
	काष्ठा aoedev *d;
	काष्ठा aoeअगर *p, *e;
	पूर्णांक minbcnt;

	d = t->d;
	minbcnt = bcnt;
	p = t->अगरs;
	e = p + NAOEIFS;
	क्रम (; p < e; p++) अणु
		अगर (p->nd == शून्य)
			अवरोध;		/* end of the valid पूर्णांकerfaces */
		अगर (p->nd == nd) अणु
			p->bcnt = bcnt;	/* we're updating */
			nd = शून्य;
		पूर्ण अन्यथा अगर (minbcnt > p->bcnt)
			minbcnt = p->bcnt; /* find the min पूर्णांकerface */
	पूर्ण
	अगर (nd) अणु
		अगर (p == e) अणु
			pr_err("aoe: device setifbcnt failure; too many interfaces.\n");
			वापस;
		पूर्ण
		dev_hold(nd);
		p->nd = nd;
		p->bcnt = bcnt;
	पूर्ण
	t->minbcnt = minbcnt;
	setdbcnt(d);
पूर्ण

व्योम
aoecmd_cfg_rsp(काष्ठा sk_buff *skb)
अणु
	काष्ठा aoedev *d;
	काष्ठा aoe_hdr *h;
	काष्ठा aoe_cfghdr *ch;
	काष्ठा aoetgt *t;
	uदीर्घ flags, aoemajor;
	काष्ठा sk_buff *sl;
	काष्ठा sk_buff_head queue;
	u16 n;

	sl = शून्य;
	h = (काष्ठा aoe_hdr *) skb_mac_header(skb);
	ch = (काष्ठा aoe_cfghdr *) (h+1);

	/*
	 * Enough people have their dip चयनes set backwards to
	 * warrant a loud message क्रम this special हाल.
	 */
	aoemajor = get_unaligned_be16(&h->major);
	अगर (aoemajor == 0xfff) अणु
		prपूर्णांकk(KERN_ERR "aoe: Warning: shelf address is all ones.  "
			"Check shelf dip switches.\n");
		वापस;
	पूर्ण
	अगर (aoemajor == 0xffff) अणु
		pr_info("aoe: e%ld.%d: broadcast shelf number invalid\n",
			aoemajor, (पूर्णांक) h->minor);
		वापस;
	पूर्ण
	अगर (h->minor == 0xff) अणु
		pr_info("aoe: e%ld.%d: broadcast slot number invalid\n",
			aoemajor, (पूर्णांक) h->minor);
		वापस;
	पूर्ण

	n = be16_to_cpu(ch->bufcnt);
	अगर (n > aoe_maxout)	/* keep it reasonable */
		n = aoe_maxout;

	d = aoedev_by_aoeaddr(aoemajor, h->minor, 1);
	अगर (d == शून्य) अणु
		pr_info("aoe: device allocation failure\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&d->lock, flags);

	t = gettgt(d, h->src);
	अगर (t) अणु
		t->nframes = n;
		अगर (n < t->maxout)
			aoecmd_wreset(t);
	पूर्ण अन्यथा अणु
		t = addtgt(d, h->src, n);
		अगर (!t)
			जाओ bail;
	पूर्ण
	n = skb->dev->mtu;
	n -= माप(काष्ठा aoe_hdr) + माप(काष्ठा aoe_atahdr);
	n /= 512;
	अगर (n > ch->scnt)
		n = ch->scnt;
	n = n ? n * 512 : DEFAULTBCNT;
	setअगरbcnt(t, skb->dev, n);

	/* करोn't change users' perspective */
	अगर (d->nखोलो == 0) अणु
		d->fw_ver = be16_to_cpu(ch->fwver);
		sl = aoecmd_ata_id(d);
	पूर्ण
bail:
	spin_unlock_irqrestore(&d->lock, flags);
	aoedev_put(d);
	अगर (sl) अणु
		__skb_queue_head_init(&queue);
		__skb_queue_tail(&queue, sl);
		aoenet_xmit(&queue);
	पूर्ण
पूर्ण

व्योम
aoecmd_wreset(काष्ठा aoetgt *t)
अणु
	t->maxout = 1;
	t->ssthresh = t->nframes / 2;
	t->next_cwnd = t->nframes;
पूर्ण

व्योम
aoecmd_cleanslate(काष्ठा aoedev *d)
अणु
	काष्ठा aoetgt **t, **te;

	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->maxbcnt = 0;

	t = d->tarमाला_लो;
	te = t + d->ntarमाला_लो;
	क्रम (; t < te && *t; t++)
		aoecmd_wreset(*t);
पूर्ण

व्योम
aoe_failbuf(काष्ठा aoedev *d, काष्ठा buf *buf)
अणु
	अगर (buf == शून्य)
		वापस;
	buf->iter.bi_size = 0;
	buf->bio->bi_status = BLK_STS_IOERR;
	अगर (buf->nframesout == 0)
		aoe_end_buf(d, buf);
पूर्ण

व्योम
aoe_flush_iocq(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ncpus; i++) अणु
		अगर (kts[i].active)
			aoe_flush_iocq_by_index(i);
	पूर्ण
पूर्ण

व्योम
aoe_flush_iocq_by_index(पूर्णांक id)
अणु
	काष्ठा frame *f;
	काष्ठा aoedev *d;
	LIST_HEAD(flist);
	काष्ठा list_head *pos;
	काष्ठा sk_buff *skb;
	uदीर्घ flags;

	spin_lock_irqsave(&iocq[id].lock, flags);
	list_splice_init(&iocq[id].head, &flist);
	spin_unlock_irqrestore(&iocq[id].lock, flags);
	जबतक (!list_empty(&flist)) अणु
		pos = flist.next;
		list_del(pos);
		f = list_entry(pos, काष्ठा frame, head);
		d = f->t->d;
		skb = f->r_skb;
		spin_lock_irqsave(&d->lock, flags);
		अगर (f->buf) अणु
			f->buf->nframesout--;
			aoe_failbuf(d, f->buf);
		पूर्ण
		aoe_मुक्तtframe(f);
		spin_unlock_irqrestore(&d->lock, flags);
		dev_kमुक्त_skb(skb);
		aoedev_put(d);
	पूर्ण
पूर्ण

पूर्णांक __init
aoecmd_init(व्योम)
अणु
	व्योम *p;
	पूर्णांक i;
	पूर्णांक ret;

	/* get_zeroed_page वापसs page with ref count 1 */
	p = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	empty_page = virt_to_page(p);

	ncpus = num_online_cpus();

	iocq = kसुस्मृति(ncpus, माप(काष्ठा iocq_ktio), GFP_KERNEL);
	अगर (!iocq)
		वापस -ENOMEM;

	kts = kसुस्मृति(ncpus, माप(काष्ठा ktstate), GFP_KERNEL);
	अगर (!kts) अणु
		ret = -ENOMEM;
		जाओ kts_fail;
	पूर्ण

	ktiowq = kसुस्मृति(ncpus, माप(रुको_queue_head_t), GFP_KERNEL);
	अगर (!ktiowq) अणु
		ret = -ENOMEM;
		जाओ ktiowq_fail;
	पूर्ण

	mutex_init(&ktio_spawn_lock);

	क्रम (i = 0; i < ncpus; i++) अणु
		INIT_LIST_HEAD(&iocq[i].head);
		spin_lock_init(&iocq[i].lock);
		init_रुकोqueue_head(&ktiowq[i]);
		snम_लिखो(kts[i].name, माप(kts[i].name), "aoe_ktio%d", i);
		kts[i].fn = ktio;
		kts[i].रुकोq = &ktiowq[i];
		kts[i].lock = &iocq[i].lock;
		kts[i].id = i;
		kts[i].active = 0;
	पूर्ण
	kts[0].active = 1;
	अगर (aoe_ktstart(&kts[0])) अणु
		ret = -ENOMEM;
		जाओ ktstart_fail;
	पूर्ण
	वापस 0;

ktstart_fail:
	kमुक्त(ktiowq);
ktiowq_fail:
	kमुक्त(kts);
kts_fail:
	kमुक्त(iocq);

	वापस ret;
पूर्ण

व्योम
aoecmd_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ncpus; i++)
		अगर (kts[i].active)
			aoe_ktstop(&kts[i]);

	aoe_flush_iocq();

	/* Free up the iocq and thपढ़ो speicअगरic configuration
	* allocated during startup.
	*/
	kमुक्त(iocq);
	kमुक्त(kts);
	kमुक्त(ktiowq);

	मुक्त_page((अचिन्हित दीर्घ) page_address(empty_page));
	empty_page = शून्य;
पूर्ण
