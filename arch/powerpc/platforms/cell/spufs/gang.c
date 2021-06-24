<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU file प्रणाली
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "spufs.h"

काष्ठा spu_gang *alloc_spu_gang(व्योम)
अणु
	काष्ठा spu_gang *gang;

	gang = kzalloc(माप *gang, GFP_KERNEL);
	अगर (!gang)
		जाओ out;

	kref_init(&gang->kref);
	mutex_init(&gang->mutex);
	mutex_init(&gang->aff_mutex);
	INIT_LIST_HEAD(&gang->list);
	INIT_LIST_HEAD(&gang->aff_list_head);

out:
	वापस gang;
पूर्ण

अटल व्योम destroy_spu_gang(काष्ठा kref *kref)
अणु
	काष्ठा spu_gang *gang;
	gang = container_of(kref, काष्ठा spu_gang, kref);
	WARN_ON(gang->contexts || !list_empty(&gang->list));
	kमुक्त(gang);
पूर्ण

काष्ठा spu_gang *get_spu_gang(काष्ठा spu_gang *gang)
अणु
	kref_get(&gang->kref);
	वापस gang;
पूर्ण

पूर्णांक put_spu_gang(काष्ठा spu_gang *gang)
अणु
	वापस kref_put(&gang->kref, &destroy_spu_gang);
पूर्ण

व्योम spu_gang_add_ctx(काष्ठा spu_gang *gang, काष्ठा spu_context *ctx)
अणु
	mutex_lock(&gang->mutex);
	ctx->gang = get_spu_gang(gang);
	list_add(&ctx->gang_list, &gang->list);
	gang->contexts++;
	mutex_unlock(&gang->mutex);
पूर्ण

व्योम spu_gang_हटाओ_ctx(काष्ठा spu_gang *gang, काष्ठा spu_context *ctx)
अणु
	mutex_lock(&gang->mutex);
	WARN_ON(ctx->gang != gang);
	अगर (!list_empty(&ctx->aff_list)) अणु
		list_del_init(&ctx->aff_list);
		gang->aff_flags &= ~AFF_OFFSETS_SET;
	पूर्ण
	list_del_init(&ctx->gang_list);
	gang->contexts--;
	mutex_unlock(&gang->mutex);

	put_spu_gang(gang);
पूर्ण
