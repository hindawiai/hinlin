<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 IT University of Cखोलोhagen. All rights reserved.
 * Initial release: Matias Bjorling <m@bjorling.me>
 */

#घोषणा pr_fmt(fmt) "nvm: " fmt

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/sem.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/lightnvm.h>
#समावेश <linux/sched/sysctl.h>

अटल LIST_HEAD(nvm_tgt_types);
अटल DECLARE_RWSEM(nvm_tgtt_lock);
अटल LIST_HEAD(nvm_devices);
अटल DECLARE_RWSEM(nvm_lock);

/* Map between भव and physical channel and lun */
काष्ठा nvm_ch_map अणु
	पूर्णांक ch_off;
	पूर्णांक num_lun;
	पूर्णांक *lun_offs;
पूर्ण;

काष्ठा nvm_dev_map अणु
	काष्ठा nvm_ch_map *chnls;
	पूर्णांक num_ch;
पूर्ण;

अटल व्योम nvm_मुक्त(काष्ठा kref *ref);

अटल काष्ठा nvm_target *nvm_find_target(काष्ठा nvm_dev *dev, स्थिर अक्षर *name)
अणु
	काष्ठा nvm_target *tgt;

	list_क्रम_each_entry(tgt, &dev->tarमाला_लो, list)
		अगर (!म_भेद(name, tgt->disk->disk_name))
			वापस tgt;

	वापस शून्य;
पूर्ण

अटल bool nvm_target_exists(स्थिर अक्षर *name)
अणु
	काष्ठा nvm_dev *dev;
	काष्ठा nvm_target *tgt;
	bool ret = false;

	करोwn_ग_लिखो(&nvm_lock);
	list_क्रम_each_entry(dev, &nvm_devices, devices) अणु
		mutex_lock(&dev->mlock);
		list_क्रम_each_entry(tgt, &dev->tarमाला_लो, list) अणु
			अगर (!म_भेद(name, tgt->disk->disk_name)) अणु
				ret = true;
				mutex_unlock(&dev->mlock);
				जाओ out;
			पूर्ण
		पूर्ण
		mutex_unlock(&dev->mlock);
	पूर्ण

out:
	up_ग_लिखो(&nvm_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक nvm_reserve_luns(काष्ठा nvm_dev *dev, पूर्णांक lun_begin, पूर्णांक lun_end)
अणु
	पूर्णांक i;

	क्रम (i = lun_begin; i <= lun_end; i++) अणु
		अगर (test_and_set_bit(i, dev->lun_map)) अणु
			pr_err("lun %d already allocated\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	जबतक (--i >= lun_begin)
		clear_bit(i, dev->lun_map);

	वापस -EBUSY;
पूर्ण

अटल व्योम nvm_release_luns_err(काष्ठा nvm_dev *dev, पूर्णांक lun_begin,
				 पूर्णांक lun_end)
अणु
	पूर्णांक i;

	क्रम (i = lun_begin; i <= lun_end; i++)
		WARN_ON(!test_and_clear_bit(i, dev->lun_map));
पूर्ण

अटल व्योम nvm_हटाओ_tgt_dev(काष्ठा nvm_tgt_dev *tgt_dev, पूर्णांक clear)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	काष्ठा nvm_dev_map *dev_map = tgt_dev->map;
	पूर्णांक i, j;

	क्रम (i = 0; i < dev_map->num_ch; i++) अणु
		काष्ठा nvm_ch_map *ch_map = &dev_map->chnls[i];
		पूर्णांक *lun_offs = ch_map->lun_offs;
		पूर्णांक ch = i + ch_map->ch_off;

		अगर (clear) अणु
			क्रम (j = 0; j < ch_map->num_lun; j++) अणु
				पूर्णांक lun = j + lun_offs[j];
				पूर्णांक lunid = (ch * dev->geo.num_lun) + lun;

				WARN_ON(!test_and_clear_bit(lunid,
							dev->lun_map));
			पूर्ण
		पूर्ण

		kमुक्त(ch_map->lun_offs);
	पूर्ण

	kमुक्त(dev_map->chnls);
	kमुक्त(dev_map);

	kमुक्त(tgt_dev->luns);
	kमुक्त(tgt_dev);
पूर्ण

अटल काष्ठा nvm_tgt_dev *nvm_create_tgt_dev(काष्ठा nvm_dev *dev,
					      u16 lun_begin, u16 lun_end,
					      u16 op)
अणु
	काष्ठा nvm_tgt_dev *tgt_dev = शून्य;
	काष्ठा nvm_dev_map *dev_rmap = dev->rmap;
	काष्ठा nvm_dev_map *dev_map;
	काष्ठा ppa_addr *luns;
	पूर्णांक num_lun = lun_end - lun_begin + 1;
	पूर्णांक luns_left = num_lun;
	पूर्णांक num_ch = num_lun / dev->geo.num_lun;
	पूर्णांक num_ch_mod = num_lun % dev->geo.num_lun;
	पूर्णांक bch = lun_begin / dev->geo.num_lun;
	पूर्णांक blun = lun_begin % dev->geo.num_lun;
	पूर्णांक lunid = 0;
	पूर्णांक lun_balanced = 1;
	पूर्णांक sec_per_lun, prev_num_lun;
	पूर्णांक i, j;

	num_ch = (num_ch_mod == 0) ? num_ch : num_ch + 1;

	dev_map = kदो_स्मृति(माप(काष्ठा nvm_dev_map), GFP_KERNEL);
	अगर (!dev_map)
		जाओ err_dev;

	dev_map->chnls = kसुस्मृति(num_ch, माप(काष्ठा nvm_ch_map), GFP_KERNEL);
	अगर (!dev_map->chnls)
		जाओ err_chnls;

	luns = kसुस्मृति(num_lun, माप(काष्ठा ppa_addr), GFP_KERNEL);
	अगर (!luns)
		जाओ err_luns;

	prev_num_lun = (luns_left > dev->geo.num_lun) ?
					dev->geo.num_lun : luns_left;
	क्रम (i = 0; i < num_ch; i++) अणु
		काष्ठा nvm_ch_map *ch_rmap = &dev_rmap->chnls[i + bch];
		पूर्णांक *lun_roffs = ch_rmap->lun_offs;
		काष्ठा nvm_ch_map *ch_map = &dev_map->chnls[i];
		पूर्णांक *lun_offs;
		पूर्णांक luns_in_chnl = (luns_left > dev->geo.num_lun) ?
					dev->geo.num_lun : luns_left;

		अगर (lun_balanced && prev_num_lun != luns_in_chnl)
			lun_balanced = 0;

		ch_map->ch_off = ch_rmap->ch_off = bch;
		ch_map->num_lun = luns_in_chnl;

		lun_offs = kसुस्मृति(luns_in_chnl, माप(पूर्णांक), GFP_KERNEL);
		अगर (!lun_offs)
			जाओ err_ch;

		क्रम (j = 0; j < luns_in_chnl; j++) अणु
			luns[lunid].ppa = 0;
			luns[lunid].a.ch = i;
			luns[lunid++].a.lun = j;

			lun_offs[j] = blun;
			lun_roffs[j + blun] = blun;
		पूर्ण

		ch_map->lun_offs = lun_offs;

		/* when starting a new channel, lun offset is reset */
		blun = 0;
		luns_left -= luns_in_chnl;
	पूर्ण

	dev_map->num_ch = num_ch;

	tgt_dev = kदो_स्मृति(माप(काष्ठा nvm_tgt_dev), GFP_KERNEL);
	अगर (!tgt_dev)
		जाओ err_ch;

	/* Inherit device geometry from parent */
	स_नकल(&tgt_dev->geo, &dev->geo, माप(काष्ठा nvm_geo));

	/* Target device only owns a portion of the physical device */
	tgt_dev->geo.num_ch = num_ch;
	tgt_dev->geo.num_lun = (lun_balanced) ? prev_num_lun : -1;
	tgt_dev->geo.all_luns = num_lun;
	tgt_dev->geo.all_chunks = num_lun * dev->geo.num_chk;

	tgt_dev->geo.op = op;

	sec_per_lun = dev->geo.clba * dev->geo.num_chk;
	tgt_dev->geo.total_secs = num_lun * sec_per_lun;

	tgt_dev->q = dev->q;
	tgt_dev->map = dev_map;
	tgt_dev->luns = luns;
	tgt_dev->parent = dev;

	वापस tgt_dev;
err_ch:
	जबतक (--i >= 0)
		kमुक्त(dev_map->chnls[i].lun_offs);
	kमुक्त(luns);
err_luns:
	kमुक्त(dev_map->chnls);
err_chnls:
	kमुक्त(dev_map);
err_dev:
	वापस tgt_dev;
पूर्ण

अटल काष्ठा nvm_tgt_type *__nvm_find_target_type(स्थिर अक्षर *name)
अणु
	काष्ठा nvm_tgt_type *tt;

	list_क्रम_each_entry(tt, &nvm_tgt_types, list)
		अगर (!म_भेद(name, tt->name))
			वापस tt;

	वापस शून्य;
पूर्ण

अटल काष्ठा nvm_tgt_type *nvm_find_target_type(स्थिर अक्षर *name)
अणु
	काष्ठा nvm_tgt_type *tt;

	करोwn_ग_लिखो(&nvm_tgtt_lock);
	tt = __nvm_find_target_type(name);
	up_ग_लिखो(&nvm_tgtt_lock);

	वापस tt;
पूर्ण

अटल पूर्णांक nvm_config_check_luns(काष्ठा nvm_geo *geo, पूर्णांक lun_begin,
				 पूर्णांक lun_end)
अणु
	अगर (lun_begin > lun_end || lun_end >= geo->all_luns) अणु
		pr_err("lun out of bound (%u:%u > %u)\n",
			lun_begin, lun_end, geo->all_luns - 1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __nvm_config_simple(काष्ठा nvm_dev *dev,
			       काष्ठा nvm_ioctl_create_simple *s)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;

	अगर (s->lun_begin == -1 && s->lun_end == -1) अणु
		s->lun_begin = 0;
		s->lun_end = geo->all_luns - 1;
	पूर्ण

	वापस nvm_config_check_luns(geo, s->lun_begin, s->lun_end);
पूर्ण

अटल पूर्णांक __nvm_config_extended(काष्ठा nvm_dev *dev,
				 काष्ठा nvm_ioctl_create_extended *e)
अणु
	अगर (e->lun_begin == 0xFFFF && e->lun_end == 0xFFFF) अणु
		e->lun_begin = 0;
		e->lun_end = dev->geo.all_luns - 1;
	पूर्ण

	/* op not set falls पूर्णांकo target's शेष */
	अगर (e->op == 0xFFFF) अणु
		e->op = NVM_TARGET_DEFAULT_OP;
	पूर्ण अन्यथा अगर (e->op < NVM_TARGET_MIN_OP || e->op > NVM_TARGET_MAX_OP) अणु
		pr_err("invalid over provisioning value\n");
		वापस -EINVAL;
	पूर्ण

	वापस nvm_config_check_luns(&dev->geo, e->lun_begin, e->lun_end);
पूर्ण

अटल पूर्णांक nvm_create_tgt(काष्ठा nvm_dev *dev, काष्ठा nvm_ioctl_create *create)
अणु
	काष्ठा nvm_ioctl_create_extended e;
	काष्ठा request_queue *tqueue;
	काष्ठा gendisk *tdisk;
	काष्ठा nvm_tgt_type *tt;
	काष्ठा nvm_target *t;
	काष्ठा nvm_tgt_dev *tgt_dev;
	व्योम *targetdata;
	अचिन्हित पूर्णांक mdts;
	पूर्णांक ret;

	चयन (create->conf.type) अणु
	हाल NVM_CONFIG_TYPE_SIMPLE:
		ret = __nvm_config_simple(dev, &create->conf.s);
		अगर (ret)
			वापस ret;

		e.lun_begin = create->conf.s.lun_begin;
		e.lun_end = create->conf.s.lun_end;
		e.op = NVM_TARGET_DEFAULT_OP;
		अवरोध;
	हाल NVM_CONFIG_TYPE_EXTENDED:
		ret = __nvm_config_extended(dev, &create->conf.e);
		अगर (ret)
			वापस ret;

		e = create->conf.e;
		अवरोध;
	शेष:
		pr_err("config type not valid\n");
		वापस -EINVAL;
	पूर्ण

	tt = nvm_find_target_type(create->tgttype);
	अगर (!tt) अणु
		pr_err("target type %s not found\n", create->tgttype);
		वापस -EINVAL;
	पूर्ण

	अगर ((tt->flags & NVM_TGT_F_HOST_L2P) != (dev->geo.करोm & NVM_RSP_L2P)) अणु
		pr_err("device is incompatible with target L2P type.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nvm_target_exists(create->tgtname)) अणु
		pr_err("target name already exists (%s)\n",
							create->tgtname);
		वापस -EINVAL;
	पूर्ण

	ret = nvm_reserve_luns(dev, e.lun_begin, e.lun_end);
	अगर (ret)
		वापस ret;

	t = kदो_स्मृति(माप(काष्ठा nvm_target), GFP_KERNEL);
	अगर (!t) अणु
		ret = -ENOMEM;
		जाओ err_reserve;
	पूर्ण

	tgt_dev = nvm_create_tgt_dev(dev, e.lun_begin, e.lun_end, e.op);
	अगर (!tgt_dev) अणु
		pr_err("could not create target device\n");
		ret = -ENOMEM;
		जाओ err_t;
	पूर्ण

	tdisk = alloc_disk(0);
	अगर (!tdisk) अणु
		ret = -ENOMEM;
		जाओ err_dev;
	पूर्ण

	tqueue = blk_alloc_queue(dev->q->node);
	अगर (!tqueue) अणु
		ret = -ENOMEM;
		जाओ err_disk;
	पूर्ण

	strlcpy(tdisk->disk_name, create->tgtname, माप(tdisk->disk_name));
	tdisk->flags = GENHD_FL_EXT_DEVT;
	tdisk->major = 0;
	tdisk->first_minor = 0;
	tdisk->fops = tt->bops;
	tdisk->queue = tqueue;

	targetdata = tt->init(tgt_dev, tdisk, create->flags);
	अगर (IS_ERR(targetdata)) अणु
		ret = PTR_ERR(targetdata);
		जाओ err_init;
	पूर्ण

	tdisk->निजी_data = targetdata;
	tqueue->queuedata = targetdata;

	mdts = (dev->geo.csecs >> 9) * NVM_MAX_VLBA;
	अगर (dev->geo.mdts) अणु
		mdts = min_t(u32, dev->geo.mdts,
				(dev->geo.csecs >> 9) * NVM_MAX_VLBA);
	पूर्ण
	blk_queue_max_hw_sectors(tqueue, mdts);

	set_capacity(tdisk, tt->capacity(targetdata));
	add_disk(tdisk);

	अगर (tt->sysfs_init && tt->sysfs_init(tdisk)) अणु
		ret = -ENOMEM;
		जाओ err_sysfs;
	पूर्ण

	t->type = tt;
	t->disk = tdisk;
	t->dev = tgt_dev;

	mutex_lock(&dev->mlock);
	list_add_tail(&t->list, &dev->tarमाला_लो);
	mutex_unlock(&dev->mlock);

	__module_get(tt->owner);

	वापस 0;
err_sysfs:
	अगर (tt->निकास)
		tt->निकास(targetdata, true);
err_init:
	blk_cleanup_queue(tqueue);
	tdisk->queue = शून्य;
err_disk:
	put_disk(tdisk);
err_dev:
	nvm_हटाओ_tgt_dev(tgt_dev, 0);
err_t:
	kमुक्त(t);
err_reserve:
	nvm_release_luns_err(dev, e.lun_begin, e.lun_end);
	वापस ret;
पूर्ण

अटल व्योम __nvm_हटाओ_target(काष्ठा nvm_target *t, bool graceful)
अणु
	काष्ठा nvm_tgt_type *tt = t->type;
	काष्ठा gendisk *tdisk = t->disk;
	काष्ठा request_queue *q = tdisk->queue;

	del_gendisk(tdisk);
	blk_cleanup_queue(q);

	अगर (tt->sysfs_निकास)
		tt->sysfs_निकास(tdisk);

	अगर (tt->निकास)
		tt->निकास(tdisk->निजी_data, graceful);

	nvm_हटाओ_tgt_dev(t->dev, 1);
	put_disk(tdisk);
	module_put(t->type->owner);

	list_del(&t->list);
	kमुक्त(t);
पूर्ण

/**
 * nvm_हटाओ_tgt - Removes a target from the media manager
 * @हटाओ:	ioctl काष्ठाure with target name to हटाओ.
 *
 * Returns:
 * 0: on success
 * 1: on not found
 * <0: on error
 */
अटल पूर्णांक nvm_हटाओ_tgt(काष्ठा nvm_ioctl_हटाओ *हटाओ)
अणु
	काष्ठा nvm_target *t = शून्य;
	काष्ठा nvm_dev *dev;

	करोwn_पढ़ो(&nvm_lock);
	list_क्रम_each_entry(dev, &nvm_devices, devices) अणु
		mutex_lock(&dev->mlock);
		t = nvm_find_target(dev, हटाओ->tgtname);
		अगर (t) अणु
			mutex_unlock(&dev->mlock);
			अवरोध;
		पूर्ण
		mutex_unlock(&dev->mlock);
	पूर्ण
	up_पढ़ो(&nvm_lock);

	अगर (!t) अणु
		pr_err("failed to remove target %s\n",
				हटाओ->tgtname);
		वापस 1;
	पूर्ण

	__nvm_हटाओ_target(t, true);
	kref_put(&dev->ref, nvm_मुक्त);

	वापस 0;
पूर्ण

अटल पूर्णांक nvm_रेजिस्टर_map(काष्ठा nvm_dev *dev)
अणु
	काष्ठा nvm_dev_map *rmap;
	पूर्णांक i, j;

	rmap = kदो_स्मृति(माप(काष्ठा nvm_dev_map), GFP_KERNEL);
	अगर (!rmap)
		जाओ err_rmap;

	rmap->chnls = kसुस्मृति(dev->geo.num_ch, माप(काष्ठा nvm_ch_map),
								GFP_KERNEL);
	अगर (!rmap->chnls)
		जाओ err_chnls;

	क्रम (i = 0; i < dev->geo.num_ch; i++) अणु
		काष्ठा nvm_ch_map *ch_rmap;
		पूर्णांक *lun_roffs;
		पूर्णांक luns_in_chnl = dev->geo.num_lun;

		ch_rmap = &rmap->chnls[i];

		ch_rmap->ch_off = -1;
		ch_rmap->num_lun = luns_in_chnl;

		lun_roffs = kसुस्मृति(luns_in_chnl, माप(पूर्णांक), GFP_KERNEL);
		अगर (!lun_roffs)
			जाओ err_ch;

		क्रम (j = 0; j < luns_in_chnl; j++)
			lun_roffs[j] = -1;

		ch_rmap->lun_offs = lun_roffs;
	पूर्ण

	dev->rmap = rmap;

	वापस 0;
err_ch:
	जबतक (--i >= 0)
		kमुक्त(rmap->chnls[i].lun_offs);
err_chnls:
	kमुक्त(rmap);
err_rmap:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvm_unरेजिस्टर_map(काष्ठा nvm_dev *dev)
अणु
	काष्ठा nvm_dev_map *rmap = dev->rmap;
	पूर्णांक i;

	क्रम (i = 0; i < dev->geo.num_ch; i++)
		kमुक्त(rmap->chnls[i].lun_offs);

	kमुक्त(rmap->chnls);
	kमुक्त(rmap);
पूर्ण

अटल व्योम nvm_map_to_dev(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा ppa_addr *p)
अणु
	काष्ठा nvm_dev_map *dev_map = tgt_dev->map;
	काष्ठा nvm_ch_map *ch_map = &dev_map->chnls[p->a.ch];
	पूर्णांक lun_off = ch_map->lun_offs[p->a.lun];

	p->a.ch += ch_map->ch_off;
	p->a.lun += lun_off;
पूर्ण

अटल व्योम nvm_map_to_tgt(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा ppa_addr *p)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	काष्ठा nvm_dev_map *dev_rmap = dev->rmap;
	काष्ठा nvm_ch_map *ch_rmap = &dev_rmap->chnls[p->a.ch];
	पूर्णांक lun_roff = ch_rmap->lun_offs[p->a.lun];

	p->a.ch -= ch_rmap->ch_off;
	p->a.lun -= lun_roff;
पूर्ण

अटल व्योम nvm_ppa_tgt_to_dev(काष्ठा nvm_tgt_dev *tgt_dev,
				काष्ठा ppa_addr *ppa_list, पूर्णांक nr_ppas)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_ppas; i++) अणु
		nvm_map_to_dev(tgt_dev, &ppa_list[i]);
		ppa_list[i] = generic_to_dev_addr(tgt_dev->parent, ppa_list[i]);
	पूर्ण
पूर्ण

अटल व्योम nvm_ppa_dev_to_tgt(काष्ठा nvm_tgt_dev *tgt_dev,
				काष्ठा ppa_addr *ppa_list, पूर्णांक nr_ppas)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_ppas; i++) अणु
		ppa_list[i] = dev_to_generic_addr(tgt_dev->parent, ppa_list[i]);
		nvm_map_to_tgt(tgt_dev, &ppa_list[i]);
	पूर्ण
पूर्ण

अटल व्योम nvm_rq_tgt_to_dev(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

	nvm_ppa_tgt_to_dev(tgt_dev, ppa_list, rqd->nr_ppas);
पूर्ण

अटल व्योम nvm_rq_dev_to_tgt(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

	nvm_ppa_dev_to_tgt(tgt_dev, ppa_list, rqd->nr_ppas);
पूर्ण

पूर्णांक nvm_रेजिस्टर_tgt_type(काष्ठा nvm_tgt_type *tt)
अणु
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&nvm_tgtt_lock);
	अगर (__nvm_find_target_type(tt->name))
		ret = -EEXIST;
	अन्यथा
		list_add(&tt->list, &nvm_tgt_types);
	up_ग_लिखो(&nvm_tgtt_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nvm_रेजिस्टर_tgt_type);

व्योम nvm_unरेजिस्टर_tgt_type(काष्ठा nvm_tgt_type *tt)
अणु
	अगर (!tt)
		वापस;

	करोwn_ग_लिखो(&nvm_tgtt_lock);
	list_del(&tt->list);
	up_ग_लिखो(&nvm_tgtt_lock);
पूर्ण
EXPORT_SYMBOL(nvm_unरेजिस्टर_tgt_type);

व्योम *nvm_dev_dma_alloc(काष्ठा nvm_dev *dev, gfp_t mem_flags,
							dma_addr_t *dma_handler)
अणु
	वापस dev->ops->dev_dma_alloc(dev, dev->dma_pool, mem_flags,
								dma_handler);
पूर्ण
EXPORT_SYMBOL(nvm_dev_dma_alloc);

व्योम nvm_dev_dma_मुक्त(काष्ठा nvm_dev *dev, व्योम *addr, dma_addr_t dma_handler)
अणु
	dev->ops->dev_dma_मुक्त(dev->dma_pool, addr, dma_handler);
पूर्ण
EXPORT_SYMBOL(nvm_dev_dma_मुक्त);

अटल काष्ठा nvm_dev *nvm_find_nvm_dev(स्थिर अक्षर *name)
अणु
	काष्ठा nvm_dev *dev;

	list_क्रम_each_entry(dev, &nvm_devices, devices)
		अगर (!म_भेद(name, dev->name))
			वापस dev;

	वापस शून्य;
पूर्ण

अटल पूर्णांक nvm_set_rqd_ppalist(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा nvm_rq *rqd,
			स्थिर काष्ठा ppa_addr *ppas, पूर्णांक nr_ppas)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	काष्ठा nvm_geo *geo = &tgt_dev->geo;
	पूर्णांक i, plane_cnt, pl_idx;
	काष्ठा ppa_addr ppa;

	अगर (geo->pln_mode == NVM_PLANE_SINGLE && nr_ppas == 1) अणु
		rqd->nr_ppas = nr_ppas;
		rqd->ppa_addr = ppas[0];

		वापस 0;
	पूर्ण

	rqd->nr_ppas = nr_ppas;
	rqd->ppa_list = nvm_dev_dma_alloc(dev, GFP_KERNEL, &rqd->dma_ppa_list);
	अगर (!rqd->ppa_list) अणु
		pr_err("failed to allocate dma memory\n");
		वापस -ENOMEM;
	पूर्ण

	plane_cnt = geo->pln_mode;
	rqd->nr_ppas *= plane_cnt;

	क्रम (i = 0; i < nr_ppas; i++) अणु
		क्रम (pl_idx = 0; pl_idx < plane_cnt; pl_idx++) अणु
			ppa = ppas[i];
			ppa.g.pl = pl_idx;
			rqd->ppa_list[(pl_idx * nr_ppas) + i] = ppa;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvm_मुक्त_rqd_ppalist(काष्ठा nvm_tgt_dev *tgt_dev,
			काष्ठा nvm_rq *rqd)
अणु
	अगर (!rqd->ppa_list)
		वापस;

	nvm_dev_dma_मुक्त(tgt_dev->parent, rqd->ppa_list, rqd->dma_ppa_list);
पूर्ण

अटल पूर्णांक nvm_set_flags(काष्ठा nvm_geo *geo, काष्ठा nvm_rq *rqd)
अणु
	पूर्णांक flags = 0;

	अगर (geo->version == NVM_OCSSD_SPEC_20)
		वापस 0;

	अगर (rqd->is_seq)
		flags |= geo->pln_mode >> 1;

	अगर (rqd->opcode == NVM_OP_PREAD)
		flags |= (NVM_IO_SCRAMBLE_ENABLE | NVM_IO_SUSPEND);
	अन्यथा अगर (rqd->opcode == NVM_OP_PWRITE)
		flags |= NVM_IO_SCRAMBLE_ENABLE;

	वापस flags;
पूर्ण

पूर्णांक nvm_submit_io(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा nvm_rq *rqd, व्योम *buf)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	पूर्णांक ret;

	अगर (!dev->ops->submit_io)
		वापस -ENODEV;

	nvm_rq_tgt_to_dev(tgt_dev, rqd);

	rqd->dev = tgt_dev;
	rqd->flags = nvm_set_flags(&tgt_dev->geo, rqd);

	/* In हाल of error, fail with right address क्रमmat */
	ret = dev->ops->submit_io(dev, rqd, buf);
	अगर (ret)
		nvm_rq_dev_to_tgt(tgt_dev, rqd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nvm_submit_io);

अटल व्योम nvm_sync_end_io(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा completion *रुकोing = rqd->निजी;

	complete(रुकोing);
पूर्ण

अटल पूर्णांक nvm_submit_io_रुको(काष्ठा nvm_dev *dev, काष्ठा nvm_rq *rqd,
			      व्योम *buf)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);
	पूर्णांक ret = 0;

	rqd->end_io = nvm_sync_end_io;
	rqd->निजी = &रुको;

	ret = dev->ops->submit_io(dev, rqd, buf);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion_io(&रुको);

	वापस 0;
पूर्ण

पूर्णांक nvm_submit_io_sync(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा nvm_rq *rqd,
		       व्योम *buf)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	पूर्णांक ret;

	अगर (!dev->ops->submit_io)
		वापस -ENODEV;

	nvm_rq_tgt_to_dev(tgt_dev, rqd);

	rqd->dev = tgt_dev;
	rqd->flags = nvm_set_flags(&tgt_dev->geo, rqd);

	ret = nvm_submit_io_रुको(dev, rqd, buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nvm_submit_io_sync);

व्योम nvm_end_io(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा nvm_tgt_dev *tgt_dev = rqd->dev;

	/* Convert address space */
	अगर (tgt_dev)
		nvm_rq_dev_to_tgt(tgt_dev, rqd);

	अगर (rqd->end_io)
		rqd->end_io(rqd);
पूर्ण
EXPORT_SYMBOL(nvm_end_io);

अटल पूर्णांक nvm_submit_io_sync_raw(काष्ठा nvm_dev *dev, काष्ठा nvm_rq *rqd)
अणु
	अगर (!dev->ops->submit_io)
		वापस -ENODEV;

	rqd->dev = शून्य;
	rqd->flags = nvm_set_flags(&dev->geo, rqd);

	वापस nvm_submit_io_रुको(dev, rqd, शून्य);
पूर्ण

अटल पूर्णांक nvm_bb_chunk_sense(काष्ठा nvm_dev *dev, काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_rq rqd = अणु शून्य पूर्ण;
	काष्ठा bio bio;
	काष्ठा bio_vec bio_vec;
	काष्ठा page *page;
	पूर्णांक ret;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	bio_init(&bio, &bio_vec, 1);
	bio_add_page(&bio, page, PAGE_SIZE, 0);
	bio_set_op_attrs(&bio, REQ_OP_READ, 0);

	rqd.bio = &bio;
	rqd.opcode = NVM_OP_PREAD;
	rqd.is_seq = 1;
	rqd.nr_ppas = 1;
	rqd.ppa_addr = generic_to_dev_addr(dev, ppa);

	ret = nvm_submit_io_sync_raw(dev, &rqd);
	__मुक्त_page(page);
	अगर (ret)
		वापस ret;

	वापस rqd.error;
पूर्ण

/*
 * Scans a 1.2 chunk first and last page to determine अगर its state.
 * If the chunk is found to be खोलो, also scan it to update the ग_लिखो
 * poपूर्णांकer.
 */
अटल पूर्णांक nvm_bb_chunk_scan(काष्ठा nvm_dev *dev, काष्ठा ppa_addr ppa,
			     काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ret, pg, pl;

	/* sense first page */
	ret = nvm_bb_chunk_sense(dev, ppa);
	अगर (ret < 0) /* io error */
		वापस ret;
	अन्यथा अगर (ret == 0) /* valid data */
		meta->state = NVM_CHK_ST_OPEN;
	अन्यथा अगर (ret > 0) अणु
		/*
		 * If empty page, the chunk is मुक्त, अन्यथा it is an
		 * actual io error. In that हाल, mark it offline.
		 */
		चयन (ret) अणु
		हाल NVM_RSP_ERR_EMPTYPAGE:
			meta->state = NVM_CHK_ST_FREE;
			वापस 0;
		हाल NVM_RSP_ERR_FAILCRC:
		हाल NVM_RSP_ERR_FAILECC:
		हाल NVM_RSP_WARN_HIGHECC:
			meta->state = NVM_CHK_ST_OPEN;
			जाओ scan;
		शेष:
			वापस -ret; /* other io error */
		पूर्ण
	पूर्ण

	/* sense last page */
	ppa.g.pg = geo->num_pg - 1;
	ppa.g.pl = geo->num_pln - 1;

	ret = nvm_bb_chunk_sense(dev, ppa);
	अगर (ret < 0) /* io error */
		वापस ret;
	अन्यथा अगर (ret == 0) अणु /* Chunk fully written */
		meta->state = NVM_CHK_ST_CLOSED;
		meta->wp = geo->clba;
		वापस 0;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		चयन (ret) अणु
		हाल NVM_RSP_ERR_EMPTYPAGE:
		हाल NVM_RSP_ERR_FAILCRC:
		हाल NVM_RSP_ERR_FAILECC:
		हाल NVM_RSP_WARN_HIGHECC:
			meta->state = NVM_CHK_ST_OPEN;
			अवरोध;
		शेष:
			वापस -ret; /* other io error */
		पूर्ण
	पूर्ण

scan:
	/*
	 * chunk is खोलो, we scan sequentially to update the ग_लिखो poपूर्णांकer.
	 * We make the assumption that tarमाला_लो ग_लिखो data across all planes
	 * beक्रमe moving to the next page.
	 */
	क्रम (pg = 0; pg < geo->num_pg; pg++) अणु
		क्रम (pl = 0; pl < geo->num_pln; pl++) अणु
			ppa.g.pg = pg;
			ppa.g.pl = pl;

			ret = nvm_bb_chunk_sense(dev, ppa);
			अगर (ret < 0) /* io error */
				वापस ret;
			अन्यथा अगर (ret == 0) अणु
				meta->wp += geo->ws_min;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				चयन (ret) अणु
				हाल NVM_RSP_ERR_EMPTYPAGE:
					वापस 0;
				हाल NVM_RSP_ERR_FAILCRC:
				हाल NVM_RSP_ERR_FAILECC:
				हाल NVM_RSP_WARN_HIGHECC:
					meta->wp += geo->ws_min;
					अवरोध;
				शेष:
					वापस -ret; /* other io error */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * folds a bad block list from its plane representation to its
 * chunk representation.
 *
 * If any of the planes status are bad or grown bad, the chunk is marked
 * offline. If not bad, the first plane state acts as the chunk state.
 */
अटल पूर्णांक nvm_bb_to_chunk(काष्ठा nvm_dev *dev, काष्ठा ppa_addr ppa,
			   u8 *blks, पूर्णांक nr_blks, काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ret, blk, pl, offset, blktype;

	क्रम (blk = 0; blk < geo->num_chk; blk++) अणु
		offset = blk * geo->pln_mode;
		blktype = blks[offset];

		क्रम (pl = 0; pl < geo->pln_mode; pl++) अणु
			अगर (blks[offset + pl] &
					(NVM_BLK_T_BAD|NVM_BLK_T_GRWN_BAD)) अणु
				blktype = blks[offset + pl];
				अवरोध;
			पूर्ण
		पूर्ण

		ppa.g.blk = blk;

		meta->wp = 0;
		meta->type = NVM_CHK_TP_W_SEQ;
		meta->wi = 0;
		meta->slba = generic_to_dev_addr(dev, ppa).ppa;
		meta->cnlb = dev->geo.clba;

		अगर (blktype == NVM_BLK_T_FREE) अणु
			ret = nvm_bb_chunk_scan(dev, ppa, meta);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			meta->state = NVM_CHK_ST_OFFLINE;
		पूर्ण

		meta++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvm_get_bb_meta(काष्ठा nvm_dev *dev, sector_t slba,
			   पूर्णांक nchks, काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr ppa;
	u8 *blks;
	पूर्णांक ch, lun, nr_blks;
	पूर्णांक ret = 0;

	ppa.ppa = slba;
	ppa = dev_to_generic_addr(dev, ppa);

	अगर (ppa.g.blk != 0)
		वापस -EINVAL;

	अगर ((nchks % geo->num_chk) != 0)
		वापस -EINVAL;

	nr_blks = geo->num_chk * geo->pln_mode;

	blks = kदो_स्मृति(nr_blks, GFP_KERNEL);
	अगर (!blks)
		वापस -ENOMEM;

	क्रम (ch = ppa.g.ch; ch < geo->num_ch; ch++) अणु
		क्रम (lun = ppa.g.lun; lun < geo->num_lun; lun++) अणु
			काष्ठा ppa_addr ppa_gen, ppa_dev;

			अगर (!nchks)
				जाओ करोne;

			ppa_gen.ppa = 0;
			ppa_gen.g.ch = ch;
			ppa_gen.g.lun = lun;
			ppa_dev = generic_to_dev_addr(dev, ppa_gen);

			ret = dev->ops->get_bb_tbl(dev, ppa_dev, blks);
			अगर (ret)
				जाओ करोne;

			ret = nvm_bb_to_chunk(dev, ppa_gen, blks, nr_blks,
									meta);
			अगर (ret)
				जाओ करोne;

			meta += geo->num_chk;
			nchks -= geo->num_chk;
		पूर्ण
	पूर्ण
करोne:
	kमुक्त(blks);
	वापस ret;
पूर्ण

पूर्णांक nvm_get_chunk_meta(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा ppa_addr ppa,
		       पूर्णांक nchks, काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;

	nvm_ppa_tgt_to_dev(tgt_dev, &ppa, 1);

	अगर (dev->geo.version == NVM_OCSSD_SPEC_12)
		वापस nvm_get_bb_meta(dev, (sector_t)ppa.ppa, nchks, meta);

	वापस dev->ops->get_chk_meta(dev, (sector_t)ppa.ppa, nchks, meta);
पूर्ण
EXPORT_SYMBOL_GPL(nvm_get_chunk_meta);

पूर्णांक nvm_set_chunk_meta(काष्ठा nvm_tgt_dev *tgt_dev, काष्ठा ppa_addr *ppas,
		       पूर्णांक nr_ppas, पूर्णांक type)
अणु
	काष्ठा nvm_dev *dev = tgt_dev->parent;
	काष्ठा nvm_rq rqd;
	पूर्णांक ret;

	अगर (dev->geo.version == NVM_OCSSD_SPEC_20)
		वापस 0;

	अगर (nr_ppas > NVM_MAX_VLBA) अणु
		pr_err("unable to update all blocks atomically\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&rqd, 0, माप(काष्ठा nvm_rq));

	nvm_set_rqd_ppalist(tgt_dev, &rqd, ppas, nr_ppas);
	nvm_rq_tgt_to_dev(tgt_dev, &rqd);

	ret = dev->ops->set_bb_tbl(dev, &rqd.ppa_addr, rqd.nr_ppas, type);
	nvm_मुक्त_rqd_ppalist(tgt_dev, &rqd);
	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvm_set_chunk_meta);

अटल पूर्णांक nvm_core_init(काष्ठा nvm_dev *dev)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ret;

	dev->lun_map = kसुस्मृति(BITS_TO_LONGS(geo->all_luns),
					माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!dev->lun_map)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dev->area_list);
	INIT_LIST_HEAD(&dev->tarमाला_लो);
	mutex_init(&dev->mlock);
	spin_lock_init(&dev->lock);

	ret = nvm_रेजिस्टर_map(dev);
	अगर (ret)
		जाओ err_fmtype;

	वापस 0;
err_fmtype:
	kमुक्त(dev->lun_map);
	वापस ret;
पूर्ण

अटल व्योम nvm_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvm_dev *dev = container_of(ref, काष्ठा nvm_dev, ref);

	अगर (dev->dma_pool)
		dev->ops->destroy_dma_pool(dev->dma_pool);

	अगर (dev->rmap)
		nvm_unरेजिस्टर_map(dev);

	kमुक्त(dev->lun_map);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक nvm_init(काष्ठा nvm_dev *dev)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ret = -EINVAL;

	अगर (dev->ops->identity(dev)) अणु
		pr_err("device could not be identified\n");
		जाओ err;
	पूर्ण

	pr_debug("ver:%u.%u nvm_vendor:%x\n", geo->major_ver_id,
			geo->minor_ver_id, geo->vmnt);

	ret = nvm_core_init(dev);
	अगर (ret) अणु
		pr_err("could not initialize core structures.\n");
		जाओ err;
	पूर्ण

	pr_info("registered %s [%u/%u/%u/%u/%u]\n",
			dev->name, dev->geo.ws_min, dev->geo.ws_opt,
			dev->geo.num_chk, dev->geo.all_luns,
			dev->geo.num_ch);
	वापस 0;
err:
	pr_err("failed to initialize nvm\n");
	वापस ret;
पूर्ण

काष्ठा nvm_dev *nvm_alloc_dev(पूर्णांक node)
अणु
	काष्ठा nvm_dev *dev;

	dev = kzalloc_node(माप(काष्ठा nvm_dev), GFP_KERNEL, node);
	अगर (dev)
		kref_init(&dev->ref);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(nvm_alloc_dev);

पूर्णांक nvm_रेजिस्टर(काष्ठा nvm_dev *dev)
अणु
	पूर्णांक ret, exp_pool_size;

	pr_warn_once("lightnvm support is deprecated and will be removed in Linux 5.15.\n");

	अगर (!dev->q || !dev->ops) अणु
		kref_put(&dev->ref, nvm_मुक्त);
		वापस -EINVAL;
	पूर्ण

	ret = nvm_init(dev);
	अगर (ret) अणु
		kref_put(&dev->ref, nvm_मुक्त);
		वापस ret;
	पूर्ण

	exp_pool_size = max_t(पूर्णांक, PAGE_SIZE,
			      (NVM_MAX_VLBA * (माप(u64) + dev->geo.sos)));
	exp_pool_size = round_up(exp_pool_size, PAGE_SIZE);

	dev->dma_pool = dev->ops->create_dma_pool(dev, "ppalist",
						  exp_pool_size);
	अगर (!dev->dma_pool) अणु
		pr_err("could not create dma pool\n");
		kref_put(&dev->ref, nvm_मुक्त);
		वापस -ENOMEM;
	पूर्ण

	/* रेजिस्टर device with a supported media manager */
	करोwn_ग_लिखो(&nvm_lock);
	list_add(&dev->devices, &nvm_devices);
	up_ग_लिखो(&nvm_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvm_रेजिस्टर);

व्योम nvm_unरेजिस्टर(काष्ठा nvm_dev *dev)
अणु
	काष्ठा nvm_target *t, *पंचांगp;

	mutex_lock(&dev->mlock);
	list_क्रम_each_entry_safe(t, पंचांगp, &dev->tarमाला_लो, list) अणु
		अगर (t->dev->parent != dev)
			जारी;
		__nvm_हटाओ_target(t, false);
		kref_put(&dev->ref, nvm_मुक्त);
	पूर्ण
	mutex_unlock(&dev->mlock);

	करोwn_ग_लिखो(&nvm_lock);
	list_del(&dev->devices);
	up_ग_लिखो(&nvm_lock);

	kref_put(&dev->ref, nvm_मुक्त);
पूर्ण
EXPORT_SYMBOL(nvm_unरेजिस्टर);

अटल पूर्णांक __nvm_configure_create(काष्ठा nvm_ioctl_create *create)
अणु
	काष्ठा nvm_dev *dev;
	पूर्णांक ret;

	करोwn_ग_लिखो(&nvm_lock);
	dev = nvm_find_nvm_dev(create->dev);
	up_ग_लिखो(&nvm_lock);

	अगर (!dev) अणु
		pr_err("device not found\n");
		वापस -EINVAL;
	पूर्ण

	kref_get(&dev->ref);
	ret = nvm_create_tgt(dev, create);
	अगर (ret)
		kref_put(&dev->ref, nvm_मुक्त);

	वापस ret;
पूर्ण

अटल दीर्घ nvm_ioctl_info(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_info *info;
	काष्ठा nvm_tgt_type *tt;
	पूर्णांक tgt_iter = 0;

	info = memdup_user(arg, माप(काष्ठा nvm_ioctl_info));
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	info->version[0] = NVM_VERSION_MAJOR;
	info->version[1] = NVM_VERSION_MINOR;
	info->version[2] = NVM_VERSION_PATCH;

	करोwn_ग_लिखो(&nvm_tgtt_lock);
	list_क्रम_each_entry(tt, &nvm_tgt_types, list) अणु
		काष्ठा nvm_ioctl_info_tgt *tgt = &info->tgts[tgt_iter];

		tgt->version[0] = tt->version[0];
		tgt->version[1] = tt->version[1];
		tgt->version[2] = tt->version[2];
		म_नकलन(tgt->tgtname, tt->name, NVM_TTYPE_NAME_MAX);

		tgt_iter++;
	पूर्ण

	info->tgtsize = tgt_iter;
	up_ग_लिखो(&nvm_tgtt_lock);

	अगर (copy_to_user(arg, info, माप(काष्ठा nvm_ioctl_info))) अणु
		kमुक्त(info);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(info);
	वापस 0;
पूर्ण

अटल दीर्घ nvm_ioctl_get_devices(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_get_devices *devices;
	काष्ठा nvm_dev *dev;
	पूर्णांक i = 0;

	devices = kzalloc(माप(काष्ठा nvm_ioctl_get_devices), GFP_KERNEL);
	अगर (!devices)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&nvm_lock);
	list_क्रम_each_entry(dev, &nvm_devices, devices) अणु
		काष्ठा nvm_ioctl_device_info *info = &devices->info[i];

		strlcpy(info->devname, dev->name, माप(info->devname));

		/* kept क्रम compatibility */
		info->bmversion[0] = 1;
		info->bmversion[1] = 0;
		info->bmversion[2] = 0;
		strlcpy(info->bmname, "gennvm", माप(info->bmname));
		i++;

		अगर (i >= ARRAY_SIZE(devices->info)) अणु
			pr_err("max %zd devices can be reported.\n",
			       ARRAY_SIZE(devices->info));
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&nvm_lock);

	devices->nr_devices = i;

	अगर (copy_to_user(arg, devices,
			 माप(काष्ठा nvm_ioctl_get_devices))) अणु
		kमुक्त(devices);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(devices);
	वापस 0;
पूर्ण

अटल दीर्घ nvm_ioctl_dev_create(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_create create;

	अगर (copy_from_user(&create, arg, माप(काष्ठा nvm_ioctl_create)))
		वापस -EFAULT;

	अगर (create.conf.type == NVM_CONFIG_TYPE_EXTENDED &&
	    create.conf.e.rsv != 0) अणु
		pr_err("reserved config field in use\n");
		वापस -EINVAL;
	पूर्ण

	create.dev[DISK_NAME_LEN - 1] = '\0';
	create.tgttype[NVM_TTYPE_NAME_MAX - 1] = '\0';
	create.tgtname[DISK_NAME_LEN - 1] = '\0';

	अगर (create.flags != 0) अणु
		__u32 flags = create.flags;

		/* Check क्रम valid flags */
		अगर (flags & NVM_TARGET_FACTORY)
			flags &= ~NVM_TARGET_FACTORY;

		अगर (flags) अणु
			pr_err("flag not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस __nvm_configure_create(&create);
पूर्ण

अटल दीर्घ nvm_ioctl_dev_हटाओ(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_हटाओ हटाओ;

	अगर (copy_from_user(&हटाओ, arg, माप(काष्ठा nvm_ioctl_हटाओ)))
		वापस -EFAULT;

	हटाओ.tgtname[DISK_NAME_LEN - 1] = '\0';

	अगर (हटाओ.flags != 0) अणु
		pr_err("no flags supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस nvm_हटाओ_tgt(&हटाओ);
पूर्ण

/* kept क्रम compatibility reasons */
अटल दीर्घ nvm_ioctl_dev_init(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_dev_init init;

	अगर (copy_from_user(&init, arg, माप(काष्ठा nvm_ioctl_dev_init)))
		वापस -EFAULT;

	अगर (init.flags != 0) अणु
		pr_err("no flags supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Kept क्रम compatibility reasons */
अटल दीर्घ nvm_ioctl_dev_factory(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा nvm_ioctl_dev_factory fact;

	अगर (copy_from_user(&fact, arg, माप(काष्ठा nvm_ioctl_dev_factory)))
		वापस -EFAULT;

	fact.dev[DISK_NAME_LEN - 1] = '\0';

	अगर (fact.flags & ~(NVM_FACTORY_NR_BITS - 1))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल दीर्घ nvm_ctl_ioctl(काष्ठा file *file, uपूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल NVM_INFO:
		वापस nvm_ioctl_info(file, argp);
	हाल NVM_GET_DEVICES:
		वापस nvm_ioctl_get_devices(file, argp);
	हाल NVM_DEV_CREATE:
		वापस nvm_ioctl_dev_create(file, argp);
	हाल NVM_DEV_REMOVE:
		वापस nvm_ioctl_dev_हटाओ(file, argp);
	हाल NVM_DEV_INIT:
		वापस nvm_ioctl_dev_init(file, argp);
	हाल NVM_DEV_FACTORY:
		वापस nvm_ioctl_dev_factory(file, argp);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations _ctl_fops = अणु
	.खोलो = nonseekable_खोलो,
	.unlocked_ioctl = nvm_ctl_ioctl,
	.owner = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice _nvm_misc = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "lightnvm",
	.nodename	= "lightnvm/control",
	.fops		= &_ctl_fops,
पूर्ण;
builtin_misc_device(_nvm_misc);
