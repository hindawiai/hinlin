<शैली गुरु>
/*
 * Copyright (C) 2001-2002 Sistina Software (UK) Limited.
 * Copyright (C) 2006-2008 Red Hat GmbH
 *
 * This file is released under the GPL.
 */

#समावेश "dm-exception-store.h"

#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/dm-पन.स>

#घोषणा DM_MSG_PREFIX "transient snapshot"

/*-----------------------------------------------------------------
 * Implementation of the store क्रम non-persistent snapshots.
 *---------------------------------------------------------------*/
काष्ठा transient_c अणु
	sector_t next_मुक्त;
पूर्ण;

अटल व्योम transient_dtr(काष्ठा dm_exception_store *store)
अणु
	kमुक्त(store->context);
पूर्ण

अटल पूर्णांक transient_पढ़ो_metadata(काष्ठा dm_exception_store *store,
				   पूर्णांक (*callback)(व्योम *callback_context,
						   chunk_t old, chunk_t new),
				   व्योम *callback_context)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक transient_prepare_exception(काष्ठा dm_exception_store *store,
				       काष्ठा dm_exception *e)
अणु
	काष्ठा transient_c *tc = store->context;
	sector_t size = get_dev_size(dm_snap_cow(store->snap)->bdev);

	अगर (size < (tc->next_मुक्त + store->chunk_size))
		वापस -1;

	e->new_chunk = sector_to_chunk(store, tc->next_मुक्त);
	tc->next_मुक्त += store->chunk_size;

	वापस 0;
पूर्ण

अटल व्योम transient_commit_exception(काष्ठा dm_exception_store *store,
				       काष्ठा dm_exception *e, पूर्णांक valid,
				       व्योम (*callback) (व्योम *, पूर्णांक success),
				       व्योम *callback_context)
अणु
	/* Just succeed */
	callback(callback_context, valid);
पूर्ण

अटल व्योम transient_usage(काष्ठा dm_exception_store *store,
			    sector_t *total_sectors,
			    sector_t *sectors_allocated,
			    sector_t *metadata_sectors)
अणु
	*sectors_allocated = ((काष्ठा transient_c *) store->context)->next_मुक्त;
	*total_sectors = get_dev_size(dm_snap_cow(store->snap)->bdev);
	*metadata_sectors = 0;
पूर्ण

अटल पूर्णांक transient_ctr(काष्ठा dm_exception_store *store, अक्षर *options)
अणु
	काष्ठा transient_c *tc;

	tc = kदो_स्मृति(माप(काष्ठा transient_c), GFP_KERNEL);
	अगर (!tc)
		वापस -ENOMEM;

	tc->next_मुक्त = 0;
	store->context = tc;

	वापस 0;
पूर्ण

अटल अचिन्हित transient_status(काष्ठा dm_exception_store *store,
				 status_type_t status, अक्षर *result,
				 अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;

	चयन (status) अणु
	हाल STATUSTYPE_INFO:
		अवरोध;
	हाल STATUSTYPE_TABLE:
		DMEMIT(" N %llu", (अचिन्हित दीर्घ दीर्घ)store->chunk_size);
	पूर्ण

	वापस sz;
पूर्ण

अटल काष्ठा dm_exception_store_type _transient_type = अणु
	.name = "transient",
	.module = THIS_MODULE,
	.ctr = transient_ctr,
	.dtr = transient_dtr,
	.पढ़ो_metadata = transient_पढ़ो_metadata,
	.prepare_exception = transient_prepare_exception,
	.commit_exception = transient_commit_exception,
	.usage = transient_usage,
	.status = transient_status,
पूर्ण;

अटल काष्ठा dm_exception_store_type _transient_compat_type = अणु
	.name = "N",
	.module = THIS_MODULE,
	.ctr = transient_ctr,
	.dtr = transient_dtr,
	.पढ़ो_metadata = transient_पढ़ो_metadata,
	.prepare_exception = transient_prepare_exception,
	.commit_exception = transient_commit_exception,
	.usage = transient_usage,
	.status = transient_status,
पूर्ण;

पूर्णांक dm_transient_snapshot_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_exception_store_type_रेजिस्टर(&_transient_type);
	अगर (r) अणु
		DMWARN("Unable to register transient exception store type");
		वापस r;
	पूर्ण

	r = dm_exception_store_type_रेजिस्टर(&_transient_compat_type);
	अगर (r) अणु
		DMWARN("Unable to register old-style transient "
		       "exception store type");
		dm_exception_store_type_unरेजिस्टर(&_transient_type);
		वापस r;
	पूर्ण

	वापस r;
पूर्ण

व्योम dm_transient_snapshot_निकास(व्योम)
अणु
	dm_exception_store_type_unरेजिस्टर(&_transient_type);
	dm_exception_store_type_unरेजिस्टर(&_transient_compat_type);
पूर्ण
