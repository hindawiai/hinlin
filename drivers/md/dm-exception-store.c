<शैली गुरु>
/*
 * Copyright (C) 2001-2002 Sistina Software (UK) Limited.
 * Copyright (C) 2006-2008 Red Hat GmbH
 *
 * This file is released under the GPL.
 */

#समावेश "dm-exception-store.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा DM_MSG_PREFIX "snapshot exception stores"

अटल LIST_HEAD(_exception_store_types);
अटल DEFINE_SPINLOCK(_lock);

अटल काष्ठा dm_exception_store_type *__find_exception_store_type(स्थिर अक्षर *name)
अणु
	काष्ठा dm_exception_store_type *type;

	list_क्रम_each_entry(type, &_exception_store_types, list)
		अगर (!म_भेद(name, type->name))
			वापस type;

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_exception_store_type *_get_exception_store_type(स्थिर अक्षर *name)
अणु
	काष्ठा dm_exception_store_type *type;

	spin_lock(&_lock);

	type = __find_exception_store_type(name);

	अगर (type && !try_module_get(type->module))
		type = शून्य;

	spin_unlock(&_lock);

	वापस type;
पूर्ण

/*
 * get_type
 * @type_name
 *
 * Attempt to retrieve the dm_exception_store_type by name.  If not alपढ़ोy
 * available, attempt to load the appropriate module.
 *
 * Exstore modules are named "dm-exstore-" followed by the 'type_name'.
 * Modules may contain multiple types.
 * This function will first try the module "dm-exstore-<type_name>",
 * then truncate 'type_name' on the last '-' and try again.
 *
 * For example, अगर type_name was "clustered-shared", it would search
 * 'dm-exstore-clustered-shared' then 'dm-exstore-clustered'.
 *
 * 'dm-exception-store-<type_name>' is too दीर्घ of a name in my
 * opinion, which is why I've chosen to have the files
 * containing exception store implementations be 'dm-exstore-<type_name>'.
 * If you want your module to be स्वतःloaded, you will follow this
 * naming convention.
 *
 * Returns: dm_exception_store_type* on success, शून्य on failure
 */
अटल काष्ठा dm_exception_store_type *get_type(स्थिर अक्षर *type_name)
अणु
	अक्षर *p, *type_name_dup;
	काष्ठा dm_exception_store_type *type;

	type = _get_exception_store_type(type_name);
	अगर (type)
		वापस type;

	type_name_dup = kstrdup(type_name, GFP_KERNEL);
	अगर (!type_name_dup) अणु
		DMERR("No memory left to attempt load for \"%s\"", type_name);
		वापस शून्य;
	पूर्ण

	जबतक (request_module("dm-exstore-%s", type_name_dup) ||
	       !(type = _get_exception_store_type(type_name))) अणु
		p = म_खोजप(type_name_dup, '-');
		अगर (!p)
			अवरोध;
		p[0] = '\0';
	पूर्ण

	अगर (!type)
		DMWARN("Module for exstore type \"%s\" not found.", type_name);

	kमुक्त(type_name_dup);

	वापस type;
पूर्ण

अटल व्योम put_type(काष्ठा dm_exception_store_type *type)
अणु
	spin_lock(&_lock);
	module_put(type->module);
	spin_unlock(&_lock);
पूर्ण

पूर्णांक dm_exception_store_type_रेजिस्टर(काष्ठा dm_exception_store_type *type)
अणु
	पूर्णांक r = 0;

	spin_lock(&_lock);
	अगर (!__find_exception_store_type(type->name))
		list_add(&type->list, &_exception_store_types);
	अन्यथा
		r = -EEXIST;
	spin_unlock(&_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL(dm_exception_store_type_रेजिस्टर);

पूर्णांक dm_exception_store_type_unरेजिस्टर(काष्ठा dm_exception_store_type *type)
अणु
	spin_lock(&_lock);

	अगर (!__find_exception_store_type(type->name)) अणु
		spin_unlock(&_lock);
		वापस -EINVAL;
	पूर्ण

	list_del(&type->list);

	spin_unlock(&_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dm_exception_store_type_unरेजिस्टर);

अटल पूर्णांक set_chunk_size(काष्ठा dm_exception_store *store,
			  स्थिर अक्षर *chunk_size_arg, अक्षर **error)
अणु
	अचिन्हित chunk_size;

	अगर (kstrtouपूर्णांक(chunk_size_arg, 10, &chunk_size)) अणु
		*error = "Invalid chunk size";
		वापस -EINVAL;
	पूर्ण

	अगर (!chunk_size) अणु
		store->chunk_size = store->chunk_mask = store->chunk_shअगरt = 0;
		वापस 0;
	पूर्ण

	वापस dm_exception_store_set_chunk_size(store, chunk_size, error);
पूर्ण

पूर्णांक dm_exception_store_set_chunk_size(काष्ठा dm_exception_store *store,
				      अचिन्हित chunk_size,
				      अक्षर **error)
अणु
	/* Check chunk_size is a घातer of 2 */
	अगर (!is_घातer_of_2(chunk_size)) अणु
		*error = "Chunk size is not a power of 2";
		वापस -EINVAL;
	पूर्ण

	/* Validate the chunk size against the device block size */
	अगर (chunk_size %
	    (bdev_logical_block_size(dm_snap_cow(store->snap)->bdev) >> 9) ||
	    chunk_size %
	    (bdev_logical_block_size(dm_snap_origin(store->snap)->bdev) >> 9)) अणु
		*error = "Chunk size is not a multiple of device blocksize";
		वापस -EINVAL;
	पूर्ण

	अगर (chunk_size > पूर्णांक_उच्च >> SECTOR_SHIFT) अणु
		*error = "Chunk size is too high";
		वापस -EINVAL;
	पूर्ण

	store->chunk_size = chunk_size;
	store->chunk_mask = chunk_size - 1;
	store->chunk_shअगरt = __ffs(chunk_size);

	वापस 0;
पूर्ण

पूर्णांक dm_exception_store_create(काष्ठा dm_target *ti, पूर्णांक argc, अक्षर **argv,
			      काष्ठा dm_snapshot *snap,
			      अचिन्हित *args_used,
			      काष्ठा dm_exception_store **store)
अणु
	पूर्णांक r = 0;
	काष्ठा dm_exception_store_type *type = शून्य;
	काष्ठा dm_exception_store *पंचांगp_store;
	अक्षर persistent;

	अगर (argc < 2) अणु
		ti->error = "Insufficient exception store arguments";
		वापस -EINVAL;
	पूर्ण

	पंचांगp_store = kzalloc(माप(*पंचांगp_store), GFP_KERNEL);
	अगर (!पंचांगp_store) अणु
		ti->error = "Exception store allocation failed";
		वापस -ENOMEM;
	पूर्ण

	persistent = बड़े(*argv[0]);
	अगर (persistent == 'P')
		type = get_type("P");
	अन्यथा अगर (persistent == 'N')
		type = get_type("N");
	अन्यथा अणु
		ti->error = "Exception store type is not P or N";
		r = -EINVAL;
		जाओ bad_type;
	पूर्ण

	अगर (!type) अणु
		ti->error = "Exception store type not recognised";
		r = -EINVAL;
		जाओ bad_type;
	पूर्ण

	पंचांगp_store->type = type;
	पंचांगp_store->snap = snap;

	r = set_chunk_size(पंचांगp_store, argv[1], &ti->error);
	अगर (r)
		जाओ bad;

	r = type->ctr(पंचांगp_store, (म_माप(argv[0]) > 1 ? &argv[0][1] : शून्य));
	अगर (r) अणु
		ti->error = "Exception store type constructor failed";
		जाओ bad;
	पूर्ण

	*args_used = 2;
	*store = पंचांगp_store;
	वापस 0;

bad:
	put_type(type);
bad_type:
	kमुक्त(पंचांगp_store);
	वापस r;
पूर्ण
EXPORT_SYMBOL(dm_exception_store_create);

व्योम dm_exception_store_destroy(काष्ठा dm_exception_store *store)
अणु
	store->type->dtr(store);
	put_type(store->type);
	kमुक्त(store);
पूर्ण
EXPORT_SYMBOL(dm_exception_store_destroy);

पूर्णांक dm_exception_store_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_transient_snapshot_init();
	अगर (r) अणु
		DMERR("Unable to register transient exception store type.");
		जाओ transient_fail;
	पूर्ण

	r = dm_persistent_snapshot_init();
	अगर (r) अणु
		DMERR("Unable to register persistent exception store type");
		जाओ persistent_fail;
	पूर्ण

	वापस 0;

persistent_fail:
	dm_transient_snapshot_निकास();
transient_fail:
	वापस r;
पूर्ण

व्योम dm_exception_store_निकास(व्योम)
अणु
	dm_persistent_snapshot_निकास();
	dm_transient_snapshot_निकास();
पूर्ण
