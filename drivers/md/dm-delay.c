<शैली गुरु>
/*
 * Copyright (C) 2005-2007 Red Hat GmbH
 *
 * A target that delays पढ़ोs and/or ग_लिखोs and can send
 * them to dअगरferent devices.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>

#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "delay"

काष्ठा delay_class अणु
	काष्ठा dm_dev *dev;
	sector_t start;
	अचिन्हित delay;
	अचिन्हित ops;
पूर्ण;

काष्ठा delay_c अणु
	काष्ठा समयr_list delay_समयr;
	काष्ठा mutex समयr_lock;
	काष्ठा workqueue_काष्ठा *kdelayd_wq;
	काष्ठा work_काष्ठा flush_expired_bios;
	काष्ठा list_head delayed_bios;
	atomic_t may_delay;

	काष्ठा delay_class पढ़ो;
	काष्ठा delay_class ग_लिखो;
	काष्ठा delay_class flush;

	पूर्णांक argc;
पूर्ण;

काष्ठा dm_delay_info अणु
	काष्ठा delay_c *context;
	काष्ठा delay_class *class;
	काष्ठा list_head list;
	अचिन्हित दीर्घ expires;
पूर्ण;

अटल DEFINE_MUTEX(delayed_bios_lock);

अटल व्योम handle_delayed_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा delay_c *dc = from_समयr(dc, t, delay_समयr);

	queue_work(dc->kdelayd_wq, &dc->flush_expired_bios);
पूर्ण

अटल व्योम queue_समयout(काष्ठा delay_c *dc, अचिन्हित दीर्घ expires)
अणु
	mutex_lock(&dc->समयr_lock);

	अगर (!समयr_pending(&dc->delay_समयr) || expires < dc->delay_समयr.expires)
		mod_समयr(&dc->delay_समयr, expires);

	mutex_unlock(&dc->समयr_lock);
पूर्ण

अटल व्योम flush_bios(काष्ठा bio *bio)
अणु
	काष्ठा bio *n;

	जबतक (bio) अणु
		n = bio->bi_next;
		bio->bi_next = शून्य;
		submit_bio_noacct(bio);
		bio = n;
	पूर्ण
पूर्ण

अटल काष्ठा bio *flush_delayed_bios(काष्ठा delay_c *dc, पूर्णांक flush_all)
अणु
	काष्ठा dm_delay_info *delayed, *next;
	अचिन्हित दीर्घ next_expires = 0;
	अचिन्हित दीर्घ start_समयr = 0;
	काष्ठा bio_list flush_bios = अणु पूर्ण;

	mutex_lock(&delayed_bios_lock);
	list_क्रम_each_entry_safe(delayed, next, &dc->delayed_bios, list) अणु
		अगर (flush_all || समय_after_eq(jअगरfies, delayed->expires)) अणु
			काष्ठा bio *bio = dm_bio_from_per_bio_data(delayed,
						माप(काष्ठा dm_delay_info));
			list_del(&delayed->list);
			bio_list_add(&flush_bios, bio);
			delayed->class->ops--;
			जारी;
		पूर्ण

		अगर (!start_समयr) अणु
			start_समयr = 1;
			next_expires = delayed->expires;
		पूर्ण अन्यथा
			next_expires = min(next_expires, delayed->expires);
	पूर्ण
	mutex_unlock(&delayed_bios_lock);

	अगर (start_समयr)
		queue_समयout(dc, next_expires);

	वापस bio_list_get(&flush_bios);
पूर्ण

अटल व्योम flush_expired_bios(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delay_c *dc;

	dc = container_of(work, काष्ठा delay_c, flush_expired_bios);
	flush_bios(flush_delayed_bios(dc, 0));
पूर्ण

अटल व्योम delay_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा delay_c *dc = ti->निजी;

	अगर (dc->kdelayd_wq)
		destroy_workqueue(dc->kdelayd_wq);

	अगर (dc->पढ़ो.dev)
		dm_put_device(ti, dc->पढ़ो.dev);
	अगर (dc->ग_लिखो.dev)
		dm_put_device(ti, dc->ग_लिखो.dev);
	अगर (dc->flush.dev)
		dm_put_device(ti, dc->flush.dev);

	mutex_destroy(&dc->समयr_lock);

	kमुक्त(dc);
पूर्ण

अटल पूर्णांक delay_class_ctr(काष्ठा dm_target *ti, काष्ठा delay_class *c, अक्षर **argv)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ पंचांगpll;
	अक्षर dummy;

	अगर (माला_पूछो(argv[1], "%llu%c", &पंचांगpll, &dummy) != 1 || पंचांगpll != (sector_t)पंचांगpll) अणु
		ti->error = "Invalid device sector";
		वापस -EINVAL;
	पूर्ण
	c->start = पंचांगpll;

	अगर (माला_पूछो(argv[2], "%u%c", &c->delay, &dummy) != 1) अणु
		ti->error = "Invalid delay";
		वापस -EINVAL;
	पूर्ण

	ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &c->dev);
	अगर (ret) अणु
		ti->error = "Device lookup failed";
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Mapping parameters:
 *    <device> <offset> <delay> [<ग_लिखो_device> <ग_लिखो_offset> <ग_लिखो_delay>]
 *
 * With separate ग_लिखो parameters, the first set is only used क्रम पढ़ोs.
 * Offsets are specअगरied in sectors.
 * Delays are specअगरied in milliseconds.
 */
अटल पूर्णांक delay_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा delay_c *dc;
	पूर्णांक ret;

	अगर (argc != 3 && argc != 6 && argc != 9) अणु
		ti->error = "Requires exactly 3, 6 or 9 arguments";
		वापस -EINVAL;
	पूर्ण

	dc = kzalloc(माप(*dc), GFP_KERNEL);
	अगर (!dc) अणु
		ti->error = "Cannot allocate context";
		वापस -ENOMEM;
	पूर्ण

	ti->निजी = dc;
	समयr_setup(&dc->delay_समयr, handle_delayed_समयr, 0);
	INIT_WORK(&dc->flush_expired_bios, flush_expired_bios);
	INIT_LIST_HEAD(&dc->delayed_bios);
	mutex_init(&dc->समयr_lock);
	atomic_set(&dc->may_delay, 1);
	dc->argc = argc;

	ret = delay_class_ctr(ti, &dc->पढ़ो, argv);
	अगर (ret)
		जाओ bad;

	अगर (argc == 3) अणु
		ret = delay_class_ctr(ti, &dc->ग_लिखो, argv);
		अगर (ret)
			जाओ bad;
		ret = delay_class_ctr(ti, &dc->flush, argv);
		अगर (ret)
			जाओ bad;
		जाओ out;
	पूर्ण

	ret = delay_class_ctr(ti, &dc->ग_लिखो, argv + 3);
	अगर (ret)
		जाओ bad;
	अगर (argc == 6) अणु
		ret = delay_class_ctr(ti, &dc->flush, argv + 3);
		अगर (ret)
			जाओ bad;
		जाओ out;
	पूर्ण

	ret = delay_class_ctr(ti, &dc->flush, argv + 6);
	अगर (ret)
		जाओ bad;

out:
	dc->kdelayd_wq = alloc_workqueue("kdelayd", WQ_MEM_RECLAIM, 0);
	अगर (!dc->kdelayd_wq) अणु
		ret = -EINVAL;
		DMERR("Couldn't start kdelayd");
		जाओ bad;
	पूर्ण

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->per_io_data_size = माप(काष्ठा dm_delay_info);
	वापस 0;

bad:
	delay_dtr(ti);
	वापस ret;
पूर्ण

अटल पूर्णांक delay_bio(काष्ठा delay_c *dc, काष्ठा delay_class *c, काष्ठा bio *bio)
अणु
	काष्ठा dm_delay_info *delayed;
	अचिन्हित दीर्घ expires = 0;

	अगर (!c->delay || !atomic_पढ़ो(&dc->may_delay))
		वापस DM_MAPIO_REMAPPED;

	delayed = dm_per_bio_data(bio, माप(काष्ठा dm_delay_info));

	delayed->context = dc;
	delayed->expires = expires = jअगरfies + msecs_to_jअगरfies(c->delay);

	mutex_lock(&delayed_bios_lock);
	c->ops++;
	list_add_tail(&delayed->list, &dc->delayed_bios);
	mutex_unlock(&delayed_bios_lock);

	queue_समयout(dc, expires);

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल व्योम delay_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा delay_c *dc = ti->निजी;

	atomic_set(&dc->may_delay, 0);
	del_समयr_sync(&dc->delay_समयr);
	flush_bios(flush_delayed_bios(dc, 1));
पूर्ण

अटल व्योम delay_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा delay_c *dc = ti->निजी;

	atomic_set(&dc->may_delay, 1);
पूर्ण

अटल पूर्णांक delay_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा delay_c *dc = ti->निजी;
	काष्ठा delay_class *c;
	काष्ठा dm_delay_info *delayed = dm_per_bio_data(bio, माप(काष्ठा dm_delay_info));

	अगर (bio_data_dir(bio) == WRITE) अणु
		अगर (unlikely(bio->bi_opf & REQ_PREFLUSH))
			c = &dc->flush;
		अन्यथा
			c = &dc->ग_लिखो;
	पूर्ण अन्यथा अणु
		c = &dc->पढ़ो;
	पूर्ण
	delayed->class = c;
	bio_set_dev(bio, c->dev->bdev);
	अगर (bio_sectors(bio))
		bio->bi_iter.bi_sector = c->start + dm_target_offset(ti, bio->bi_iter.bi_sector);

	वापस delay_bio(dc, c, bio);
पूर्ण

#घोषणा DMEMIT_DELAY_CLASS(c) \
	DMEMIT("%s %llu %u", (c)->dev->name, (अचिन्हित दीर्घ दीर्घ)(c)->start, (c)->delay)

अटल व्योम delay_status(काष्ठा dm_target *ti, status_type_t type,
			 अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा delay_c *dc = ti->निजी;
	पूर्णांक sz = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%u %u %u", dc->पढ़ो.ops, dc->ग_लिखो.ops, dc->flush.ops);
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT_DELAY_CLASS(&dc->पढ़ो);
		अगर (dc->argc >= 6) अणु
			DMEMIT(" ");
			DMEMIT_DELAY_CLASS(&dc->ग_लिखो);
		पूर्ण
		अगर (dc->argc >= 9) अणु
			DMEMIT(" ");
			DMEMIT_DELAY_CLASS(&dc->flush);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक delay_iterate_devices(काष्ठा dm_target *ti,
				 iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा delay_c *dc = ti->निजी;
	पूर्णांक ret = 0;

	ret = fn(ti, dc->पढ़ो.dev, dc->पढ़ो.start, ti->len, data);
	अगर (ret)
		जाओ out;
	ret = fn(ti, dc->ग_लिखो.dev, dc->ग_लिखो.start, ti->len, data);
	अगर (ret)
		जाओ out;
	ret = fn(ti, dc->flush.dev, dc->flush.start, ti->len, data);
	अगर (ret)
		जाओ out;

out:
	वापस ret;
पूर्ण

अटल काष्ठा target_type delay_target = अणु
	.name	     = "delay",
	.version     = अणु1, 2, 1पूर्ण,
	.features    = DM_TARGET_PASSES_INTEGRITY,
	.module      = THIS_MODULE,
	.ctr	     = delay_ctr,
	.dtr	     = delay_dtr,
	.map	     = delay_map,
	.presuspend  = delay_presuspend,
	.resume	     = delay_resume,
	.status	     = delay_status,
	.iterate_devices = delay_iterate_devices,
पूर्ण;

अटल पूर्णांक __init dm_delay_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&delay_target);
	अगर (r < 0) अणु
		DMERR("register failed %d", r);
		जाओ bad_रेजिस्टर;
	पूर्ण

	वापस 0;

bad_रेजिस्टर:
	वापस r;
पूर्ण

अटल व्योम __निकास dm_delay_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&delay_target);
पूर्ण

/* Module hooks */
module_init(dm_delay_init);
module_निकास(dm_delay_निकास);

MODULE_DESCRIPTION(DM_NAME " delay target");
MODULE_AUTHOR("Heinz Mauelshagen <mauelshagen@redhat.com>");
MODULE_LICENSE("GPL");
