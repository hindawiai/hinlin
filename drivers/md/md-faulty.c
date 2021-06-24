<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * faulty.c : Multiple Devices driver क्रम Linux
 *
 * Copyright (C) 2004 Neil Brown
 *
 * fautly-device-simulator personality क्रम md
 */


/*
 * The "faulty" personality causes some requests to fail.
 *
 * Possible failure modes are:
 *   पढ़ोs fail "randomly" but succeed on retry
 *   ग_लिखोs fail "randomly" but succeed on retry
 *   पढ़ोs क्रम some address fail and then persist until a ग_लिखो
 *   पढ़ोs क्रम some address fail and then persist irrespective of ग_लिखो
 *   ग_लिखोs क्रम some address fail and persist
 *   all ग_लिखोs fail
 *
 * Dअगरferent modes can be active at a समय, but only
 * one can be set at array creation.  Others can be added later.
 * A mode can be one-shot or recurrent with the recurrence being
 * once in every N requests.
 * The bottom 5 bits of the "layout" indicate the mode.  The
 * reमुख्यder indicate a period, or 0 क्रम one-shot.
 *
 * There is an implementation limit on the number of concurrently
 * persisting-faulty blocks. When a new fault is requested that would
 * exceed the limit, it is ignored.
 * All current faults can be clear using a layout of "0".
 *
 * Requests are always sent to the device.  If they are to fail,
 * we clone the bio and insert a new b_end_io पूर्णांकo the chain.
 */

#घोषणा	WriteTransient	0
#घोषणा	ReadTransient	1
#घोषणा	WritePersistent	2
#घोषणा	ReadPersistent	3
#घोषणा	WriteAll	4 /* करोesn't go to device */
#घोषणा	ReadFixable	5
#घोषणा	Modes	6

#घोषणा	ClearErrors	31
#घोषणा	ClearFaults	30

#घोषणा AllPersist	100 /* पूर्णांकernal use only */
#घोषणा	NoPersist	101

#घोषणा	ModeMask	0x1f
#घोषणा	ModeShअगरt	5

#घोषणा MaxFault	50
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/raid/md_u.h>
#समावेश <linux/slab.h>
#समावेश "md.h"
#समावेश <linux/seq_file.h>


अटल व्योम faulty_fail(काष्ठा bio *bio)
अणु
	काष्ठा bio *b = bio->bi_निजी;

	b->bi_iter.bi_size = bio->bi_iter.bi_size;
	b->bi_iter.bi_sector = bio->bi_iter.bi_sector;

	bio_put(bio);

	bio_io_error(b);
पूर्ण

काष्ठा faulty_conf अणु
	पूर्णांक period[Modes];
	atomic_t counters[Modes];
	sector_t faults[MaxFault];
	पूर्णांक	modes[MaxFault];
	पूर्णांक nfaults;
	काष्ठा md_rdev *rdev;
पूर्ण;

अटल पूर्णांक check_mode(काष्ठा faulty_conf *conf, पूर्णांक mode)
अणु
	अगर (conf->period[mode] == 0 &&
	    atomic_पढ़ो(&conf->counters[mode]) <= 0)
		वापस 0; /* no failure, no decrement */


	अगर (atomic_dec_and_test(&conf->counters[mode])) अणु
		अगर (conf->period[mode])
			atomic_set(&conf->counters[mode], conf->period[mode]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_sector(काष्ठा faulty_conf *conf, sector_t start, sector_t end, पूर्णांक dir)
अणु
	/* If we find a ReadFixable sector, we fix it ... */
	पूर्णांक i;
	क्रम (i=0; i<conf->nfaults; i++)
		अगर (conf->faults[i] >= start &&
		    conf->faults[i] < end) अणु
			/* found it ... */
			चयन (conf->modes[i] * 2 + dir) अणु
			हाल WritePersistent*2+WRITE: वापस 1;
			हाल ReadPersistent*2+READ: वापस 1;
			हाल ReadFixable*2+READ: वापस 1;
			हाल ReadFixable*2+WRITE:
				conf->modes[i] = NoPersist;
				वापस 0;
			हाल AllPersist*2+READ:
			हाल AllPersist*2+WRITE: वापस 1;
			शेष:
				वापस 0;
			पूर्ण
		पूर्ण
	वापस 0;
पूर्ण

अटल व्योम add_sector(काष्ठा faulty_conf *conf, sector_t start, पूर्णांक mode)
अणु
	पूर्णांक i;
	पूर्णांक n = conf->nfaults;
	क्रम (i=0; i<conf->nfaults; i++)
		अगर (conf->faults[i] == start) अणु
			चयन(mode) अणु
			हाल NoPersist: conf->modes[i] = mode; वापस;
			हाल WritePersistent:
				अगर (conf->modes[i] == ReadPersistent ||
				    conf->modes[i] == ReadFixable)
					conf->modes[i] = AllPersist;
				अन्यथा
					conf->modes[i] = WritePersistent;
				वापस;
			हाल ReadPersistent:
				अगर (conf->modes[i] == WritePersistent)
					conf->modes[i] = AllPersist;
				अन्यथा
					conf->modes[i] = ReadPersistent;
				वापस;
			हाल ReadFixable:
				अगर (conf->modes[i] == WritePersistent ||
				    conf->modes[i] == ReadPersistent)
					conf->modes[i] = AllPersist;
				अन्यथा
					conf->modes[i] = ReadFixable;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (conf->modes[i] == NoPersist)
			n = i;

	अगर (n >= MaxFault)
		वापस;
	conf->faults[n] = start;
	conf->modes[n] = mode;
	अगर (conf->nfaults == n)
		conf->nfaults = n+1;
पूर्ण

अटल bool faulty_make_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा faulty_conf *conf = mddev->निजी;
	पूर्णांक failit = 0;

	अगर (bio_data_dir(bio) == WRITE) अणु
		/* ग_लिखो request */
		अगर (atomic_पढ़ो(&conf->counters[WriteAll])) अणु
			/* special हाल - करोn't decrement, don't submit_bio_noacct,
			 * just fail immediately
			 */
			bio_io_error(bio);
			वापस true;
		पूर्ण

		अगर (check_sector(conf, bio->bi_iter.bi_sector,
				 bio_end_sector(bio), WRITE))
			failit = 1;
		अगर (check_mode(conf, WritePersistent)) अणु
			add_sector(conf, bio->bi_iter.bi_sector,
				   WritePersistent);
			failit = 1;
		पूर्ण
		अगर (check_mode(conf, WriteTransient))
			failit = 1;
	पूर्ण अन्यथा अणु
		/* पढ़ो request */
		अगर (check_sector(conf, bio->bi_iter.bi_sector,
				 bio_end_sector(bio), READ))
			failit = 1;
		अगर (check_mode(conf, ReadTransient))
			failit = 1;
		अगर (check_mode(conf, ReadPersistent)) अणु
			add_sector(conf, bio->bi_iter.bi_sector,
				   ReadPersistent);
			failit = 1;
		पूर्ण
		अगर (check_mode(conf, ReadFixable)) अणु
			add_sector(conf, bio->bi_iter.bi_sector,
				   ReadFixable);
			failit = 1;
		पूर्ण
	पूर्ण
	अगर (failit) अणु
		काष्ठा bio *b = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);

		bio_set_dev(b, conf->rdev->bdev);
		b->bi_निजी = bio;
		b->bi_end_io = faulty_fail;
		bio = b;
	पूर्ण अन्यथा
		bio_set_dev(bio, conf->rdev->bdev);

	submit_bio_noacct(bio);
	वापस true;
पूर्ण

अटल व्योम faulty_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	काष्ठा faulty_conf *conf = mddev->निजी;
	पूर्णांक n;

	अगर ((n=atomic_पढ़ो(&conf->counters[WriteTransient])) != 0)
		seq_म_लिखो(seq, " WriteTransient=%d(%d)",
			   n, conf->period[WriteTransient]);

	अगर ((n=atomic_पढ़ो(&conf->counters[ReadTransient])) != 0)
		seq_म_लिखो(seq, " ReadTransient=%d(%d)",
			   n, conf->period[ReadTransient]);

	अगर ((n=atomic_पढ़ो(&conf->counters[WritePersistent])) != 0)
		seq_म_लिखो(seq, " WritePersistent=%d(%d)",
			   n, conf->period[WritePersistent]);

	अगर ((n=atomic_पढ़ो(&conf->counters[ReadPersistent])) != 0)
		seq_म_लिखो(seq, " ReadPersistent=%d(%d)",
			   n, conf->period[ReadPersistent]);


	अगर ((n=atomic_पढ़ो(&conf->counters[ReadFixable])) != 0)
		seq_म_लिखो(seq, " ReadFixable=%d(%d)",
			   n, conf->period[ReadFixable]);

	अगर ((n=atomic_पढ़ो(&conf->counters[WriteAll])) != 0)
		seq_म_लिखो(seq, " WriteAll");

	seq_म_लिखो(seq, " nfaults=%d", conf->nfaults);
पूर्ण


अटल पूर्णांक faulty_reshape(काष्ठा mddev *mddev)
अणु
	पूर्णांक mode = mddev->new_layout & ModeMask;
	पूर्णांक count = mddev->new_layout >> ModeShअगरt;
	काष्ठा faulty_conf *conf = mddev->निजी;

	अगर (mddev->new_layout < 0)
		वापस 0;

	/* new layout */
	अगर (mode == ClearFaults)
		conf->nfaults = 0;
	अन्यथा अगर (mode == ClearErrors) अणु
		पूर्णांक i;
		क्रम (i=0 ; i < Modes ; i++) अणु
			conf->period[i] = 0;
			atomic_set(&conf->counters[i], 0);
		पूर्ण
	पूर्ण अन्यथा अगर (mode < Modes) अणु
		conf->period[mode] = count;
		अगर (!count) count++;
		atomic_set(&conf->counters[mode], count);
	पूर्ण अन्यथा
		वापस -EINVAL;
	mddev->new_layout = -1;
	mddev->layout = -1; /* makes sure further changes come through */
	वापस 0;
पूर्ण

अटल sector_t faulty_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	WARN_ONCE(raid_disks,
		  "%s does not support generic reshape\n", __func__);

	अगर (sectors == 0)
		वापस mddev->dev_sectors;

	वापस sectors;
पूर्ण

अटल पूर्णांक faulty_run(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक i;
	काष्ठा faulty_conf *conf;

	अगर (md_check_no_biपंचांगap(mddev))
		वापस -EINVAL;

	conf = kदो_स्मृति(माप(*conf), GFP_KERNEL);
	अगर (!conf)
		वापस -ENOMEM;

	क्रम (i=0; i<Modes; i++) अणु
		atomic_set(&conf->counters[i], 0);
		conf->period[i] = 0;
	पूर्ण
	conf->nfaults = 0;

	rdev_क्रम_each(rdev, mddev) अणु
		conf->rdev = rdev;
		disk_stack_limits(mddev->gendisk, rdev->bdev,
				  rdev->data_offset << 9);
	पूर्ण

	md_set_array_sectors(mddev, faulty_size(mddev, 0, 0));
	mddev->निजी = conf;

	faulty_reshape(mddev);

	वापस 0;
पूर्ण

अटल व्योम faulty_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा faulty_conf *conf = priv;

	kमुक्त(conf);
पूर्ण

अटल काष्ठा md_personality faulty_personality =
अणु
	.name		= "faulty",
	.level		= LEVEL_FAULTY,
	.owner		= THIS_MODULE,
	.make_request	= faulty_make_request,
	.run		= faulty_run,
	.मुक्त		= faulty_मुक्त,
	.status		= faulty_status,
	.check_reshape	= faulty_reshape,
	.size		= faulty_size,
पूर्ण;

अटल पूर्णांक __init raid_init(व्योम)
अणु
	वापस रेजिस्टर_md_personality(&faulty_personality);
पूर्ण

अटल व्योम raid_निकास(व्योम)
अणु
	unरेजिस्टर_md_personality(&faulty_personality);
पूर्ण

module_init(raid_init);
module_निकास(raid_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fault injection personality for MD");
MODULE_ALIAS("md-personality-10"); /* faulty */
MODULE_ALIAS("md-faulty");
MODULE_ALIAS("md-level--5");
