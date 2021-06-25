<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/smp.h>

#समावेश <linux/blk-mq.h>
#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"

अटल व्योम blk_mq_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा blk_mq_ctxs *ctxs = container_of(kobj, काष्ठा blk_mq_ctxs, kobj);

	मुक्त_percpu(ctxs->queue_ctx);
	kमुक्त(ctxs);
पूर्ण

अटल व्योम blk_mq_ctx_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा blk_mq_ctx *ctx = container_of(kobj, काष्ठा blk_mq_ctx, kobj);

	/* ctx->ctxs won't be released until all ctx are मुक्तd */
	kobject_put(&ctx->ctxs->kobj);
पूर्ण

अटल व्योम blk_mq_hw_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = container_of(kobj, काष्ठा blk_mq_hw_ctx,
						  kobj);

	अगर (hctx->flags & BLK_MQ_F_BLOCKING)
		cleanup_srcu_काष्ठा(hctx->srcu);
	blk_मुक्त_flush_queue(hctx->fq);
	sbiपंचांगap_मुक्त(&hctx->ctx_map);
	मुक्त_cpumask_var(hctx->cpumask);
	kमुक्त(hctx->ctxs);
	kमुक्त(hctx);
पूर्ण

काष्ठा blk_mq_ctx_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा blk_mq_ctx *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा blk_mq_ctx *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

काष्ठा blk_mq_hw_ctx_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा blk_mq_hw_ctx *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा blk_mq_hw_ctx *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार blk_mq_sysfs_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				 अक्षर *page)
अणु
	काष्ठा blk_mq_ctx_sysfs_entry *entry;
	काष्ठा blk_mq_ctx *ctx;
	काष्ठा request_queue *q;
	sमाप_प्रकार res;

	entry = container_of(attr, काष्ठा blk_mq_ctx_sysfs_entry, attr);
	ctx = container_of(kobj, काष्ठा blk_mq_ctx, kobj);
	q = ctx->queue;

	अगर (!entry->show)
		वापस -EIO;

	mutex_lock(&q->sysfs_lock);
	res = entry->show(ctx, page);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार blk_mq_sysfs_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  स्थिर अक्षर *page, माप_प्रकार length)
अणु
	काष्ठा blk_mq_ctx_sysfs_entry *entry;
	काष्ठा blk_mq_ctx *ctx;
	काष्ठा request_queue *q;
	sमाप_प्रकार res;

	entry = container_of(attr, काष्ठा blk_mq_ctx_sysfs_entry, attr);
	ctx = container_of(kobj, काष्ठा blk_mq_ctx, kobj);
	q = ctx->queue;

	अगर (!entry->store)
		वापस -EIO;

	mutex_lock(&q->sysfs_lock);
	res = entry->store(ctx, page, length);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार blk_mq_hw_sysfs_show(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा blk_mq_hw_ctx_sysfs_entry *entry;
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा request_queue *q;
	sमाप_प्रकार res;

	entry = container_of(attr, काष्ठा blk_mq_hw_ctx_sysfs_entry, attr);
	hctx = container_of(kobj, काष्ठा blk_mq_hw_ctx, kobj);
	q = hctx->queue;

	अगर (!entry->show)
		वापस -EIO;

	mutex_lock(&q->sysfs_lock);
	res = entry->show(hctx, page);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार blk_mq_hw_sysfs_store(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, स्थिर अक्षर *page,
				     माप_प्रकार length)
अणु
	काष्ठा blk_mq_hw_ctx_sysfs_entry *entry;
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा request_queue *q;
	sमाप_प्रकार res;

	entry = container_of(attr, काष्ठा blk_mq_hw_ctx_sysfs_entry, attr);
	hctx = container_of(kobj, काष्ठा blk_mq_hw_ctx, kobj);
	q = hctx->queue;

	अगर (!entry->store)
		वापस -EIO;

	mutex_lock(&q->sysfs_lock);
	res = entry->store(hctx, page, length);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार blk_mq_hw_sysfs_nr_tags_show(काष्ठा blk_mq_hw_ctx *hctx,
					    अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", hctx->tags->nr_tags);
पूर्ण

अटल sमाप_प्रकार blk_mq_hw_sysfs_nr_reserved_tags_show(काष्ठा blk_mq_hw_ctx *hctx,
						     अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", hctx->tags->nr_reserved_tags);
पूर्ण

अटल sमाप_प्रकार blk_mq_hw_sysfs_cpus_show(काष्ठा blk_mq_hw_ctx *hctx, अक्षर *page)
अणु
	स्थिर माप_प्रकार size = PAGE_SIZE - 1;
	अचिन्हित पूर्णांक i, first = 1;
	पूर्णांक ret = 0, pos = 0;

	क्रम_each_cpu(i, hctx->cpumask) अणु
		अगर (first)
			ret = snम_लिखो(pos + page, size - pos, "%u", i);
		अन्यथा
			ret = snम_लिखो(pos + page, size - pos, ", %u", i);

		अगर (ret >= size - pos)
			अवरोध;

		first = 0;
		pos += ret;
	पूर्ण

	ret = snम_लिखो(pos + page, size + 1 - pos, "\n");
	वापस pos + ret;
पूर्ण

अटल काष्ठा blk_mq_hw_ctx_sysfs_entry blk_mq_hw_sysfs_nr_tags = अणु
	.attr = अणु.name = "nr_tags", .mode = 0444 पूर्ण,
	.show = blk_mq_hw_sysfs_nr_tags_show,
पूर्ण;
अटल काष्ठा blk_mq_hw_ctx_sysfs_entry blk_mq_hw_sysfs_nr_reserved_tags = अणु
	.attr = अणु.name = "nr_reserved_tags", .mode = 0444 पूर्ण,
	.show = blk_mq_hw_sysfs_nr_reserved_tags_show,
पूर्ण;
अटल काष्ठा blk_mq_hw_ctx_sysfs_entry blk_mq_hw_sysfs_cpus = अणु
	.attr = अणु.name = "cpu_list", .mode = 0444 पूर्ण,
	.show = blk_mq_hw_sysfs_cpus_show,
पूर्ण;

अटल काष्ठा attribute *शेष_hw_ctx_attrs[] = अणु
	&blk_mq_hw_sysfs_nr_tags.attr,
	&blk_mq_hw_sysfs_nr_reserved_tags.attr,
	&blk_mq_hw_sysfs_cpus.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(शेष_hw_ctx);

अटल स्थिर काष्ठा sysfs_ops blk_mq_sysfs_ops = अणु
	.show	= blk_mq_sysfs_show,
	.store	= blk_mq_sysfs_store,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops blk_mq_hw_sysfs_ops = अणु
	.show	= blk_mq_hw_sysfs_show,
	.store	= blk_mq_hw_sysfs_store,
पूर्ण;

अटल काष्ठा kobj_type blk_mq_ktype = अणु
	.sysfs_ops	= &blk_mq_sysfs_ops,
	.release	= blk_mq_sysfs_release,
पूर्ण;

अटल काष्ठा kobj_type blk_mq_ctx_ktype = अणु
	.sysfs_ops	= &blk_mq_sysfs_ops,
	.release	= blk_mq_ctx_sysfs_release,
पूर्ण;

अटल काष्ठा kobj_type blk_mq_hw_ktype = अणु
	.sysfs_ops	= &blk_mq_hw_sysfs_ops,
	.शेष_groups = शेष_hw_ctx_groups,
	.release	= blk_mq_hw_sysfs_release,
पूर्ण;

अटल व्योम blk_mq_unरेजिस्टर_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा blk_mq_ctx *ctx;
	पूर्णांक i;

	अगर (!hctx->nr_ctx)
		वापस;

	hctx_क्रम_each_ctx(hctx, ctx, i)
		kobject_del(&ctx->kobj);

	kobject_del(&hctx->kobj);
पूर्ण

अटल पूर्णांक blk_mq_रेजिस्टर_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा blk_mq_ctx *ctx;
	पूर्णांक i, ret;

	अगर (!hctx->nr_ctx)
		वापस 0;

	ret = kobject_add(&hctx->kobj, q->mq_kobj, "%u", hctx->queue_num);
	अगर (ret)
		वापस ret;

	hctx_क्रम_each_ctx(hctx, ctx, i) अणु
		ret = kobject_add(&ctx->kobj, &hctx->kobj, "cpu%u", ctx->cpu);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम blk_mq_unरेजिस्टर_dev(काष्ठा device *dev, काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	lockdep_निश्चित_held(&q->sysfs_dir_lock);

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_unरेजिस्टर_hctx(hctx);

	kobject_uevent(q->mq_kobj, KOBJ_REMOVE);
	kobject_del(q->mq_kobj);
	kobject_put(&dev->kobj);

	q->mq_sysfs_init_करोne = false;
पूर्ण

व्योम blk_mq_hctx_kobj_init(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	kobject_init(&hctx->kobj, &blk_mq_hw_ktype);
पूर्ण

व्योम blk_mq_sysfs_deinit(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_ctx *ctx;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		ctx = per_cpu_ptr(q->queue_ctx, cpu);
		kobject_put(&ctx->kobj);
	पूर्ण
	kobject_put(q->mq_kobj);
पूर्ण

व्योम blk_mq_sysfs_init(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_ctx *ctx;
	पूर्णांक cpu;

	kobject_init(q->mq_kobj, &blk_mq_ktype);

	क्रम_each_possible_cpu(cpu) अणु
		ctx = per_cpu_ptr(q->queue_ctx, cpu);

		kobject_get(q->mq_kobj);
		kobject_init(&ctx->kobj, &blk_mq_ctx_ktype);
	पूर्ण
पूर्ण

पूर्णांक __blk_mq_रेजिस्टर_dev(काष्ठा device *dev, काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक ret, i;

	WARN_ON_ONCE(!q->kobj.parent);
	lockdep_निश्चित_held(&q->sysfs_dir_lock);

	ret = kobject_add(q->mq_kobj, kobject_get(&dev->kobj), "%s", "mq");
	अगर (ret < 0)
		जाओ out;

	kobject_uevent(q->mq_kobj, KOBJ_ADD);

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		ret = blk_mq_रेजिस्टर_hctx(hctx);
		अगर (ret)
			जाओ unreg;
	पूर्ण

	q->mq_sysfs_init_करोne = true;

out:
	वापस ret;

unreg:
	जबतक (--i >= 0)
		blk_mq_unरेजिस्टर_hctx(q->queue_hw_ctx[i]);

	kobject_uevent(q->mq_kobj, KOBJ_REMOVE);
	kobject_del(q->mq_kobj);
	kobject_put(&dev->kobj);
	वापस ret;
पूर्ण

व्योम blk_mq_sysfs_unरेजिस्टर(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	mutex_lock(&q->sysfs_dir_lock);
	अगर (!q->mq_sysfs_init_करोne)
		जाओ unlock;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_unरेजिस्टर_hctx(hctx);

unlock:
	mutex_unlock(&q->sysfs_dir_lock);
पूर्ण

पूर्णांक blk_mq_sysfs_रेजिस्टर(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i, ret = 0;

	mutex_lock(&q->sysfs_dir_lock);
	अगर (!q->mq_sysfs_init_करोne)
		जाओ unlock;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		ret = blk_mq_रेजिस्टर_hctx(hctx);
		अगर (ret)
			अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&q->sysfs_dir_lock);

	वापस ret;
पूर्ण
