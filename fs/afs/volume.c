<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS volume management
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

अचिन्हित __पढ़ो_mostly afs_volume_gc_delay = 10;
अचिन्हित __पढ़ो_mostly afs_volume_record_lअगरe = 60 * 60;

/*
 * Insert a volume पूर्णांकo a cell.  If there's an existing volume record, that is
 * वापसed instead with a ref held.
 */
अटल काष्ठा afs_volume *afs_insert_volume_पूर्णांकo_cell(काष्ठा afs_cell *cell,
						      काष्ठा afs_volume *volume)
अणु
	काष्ठा afs_volume *p;
	काष्ठा rb_node *parent = शून्य, **pp;

	ग_लिखो_seqlock(&cell->volume_lock);

	pp = &cell->volumes.rb_node;
	जबतक (*pp) अणु
		parent = *pp;
		p = rb_entry(parent, काष्ठा afs_volume, cell_node);
		अगर (p->vid < volume->vid) अणु
			pp = &(*pp)->rb_left;
		पूर्ण अन्यथा अगर (p->vid > volume->vid) अणु
			pp = &(*pp)->rb_right;
		पूर्ण अन्यथा अणु
			volume = afs_get_volume(p, afs_volume_trace_get_cell_insert);
			जाओ found;
		पूर्ण
	पूर्ण

	rb_link_node_rcu(&volume->cell_node, parent, pp);
	rb_insert_color(&volume->cell_node, &cell->volumes);
	hlist_add_head_rcu(&volume->proc_link, &cell->proc_volumes);

found:
	ग_लिखो_sequnlock(&cell->volume_lock);
	वापस volume;

पूर्ण

अटल व्योम afs_हटाओ_volume_from_cell(काष्ठा afs_volume *volume)
अणु
	काष्ठा afs_cell *cell = volume->cell;

	अगर (!hlist_unhashed(&volume->proc_link)) अणु
		trace_afs_volume(volume->vid, atomic_पढ़ो(&volume->usage),
				 afs_volume_trace_हटाओ);
		ग_लिखो_seqlock(&cell->volume_lock);
		hlist_del_rcu(&volume->proc_link);
		rb_erase(&volume->cell_node, &cell->volumes);
		ग_लिखो_sequnlock(&cell->volume_lock);
	पूर्ण
पूर्ण

/*
 * Allocate a volume record and load it up from a vldb record.
 */
अटल काष्ठा afs_volume *afs_alloc_volume(काष्ठा afs_fs_context *params,
					   काष्ठा afs_vldb_entry *vldb,
					   अचिन्हित दीर्घ type_mask)
अणु
	काष्ठा afs_server_list *slist;
	काष्ठा afs_volume *volume;
	पूर्णांक ret = -ENOMEM, nr_servers = 0, i;

	क्रम (i = 0; i < vldb->nr_servers; i++)
		अगर (vldb->fs_mask[i] & type_mask)
			nr_servers++;

	volume = kzalloc(माप(काष्ठा afs_volume), GFP_KERNEL);
	अगर (!volume)
		जाओ error_0;

	volume->vid		= vldb->vid[params->type];
	volume->update_at	= kसमय_get_real_seconds() + afs_volume_record_lअगरe;
	volume->cell		= afs_get_cell(params->cell, afs_cell_trace_get_vol);
	volume->type		= params->type;
	volume->type_क्रमce	= params->क्रमce;
	volume->name_len	= vldb->name_len;

	atomic_set(&volume->usage, 1);
	INIT_HLIST_NODE(&volume->proc_link);
	rwlock_init(&volume->servers_lock);
	rwlock_init(&volume->cb_v_अवरोध_lock);
	स_नकल(volume->name, vldb->name, vldb->name_len + 1);

	slist = afs_alloc_server_list(params->cell, params->key, vldb, type_mask);
	अगर (IS_ERR(slist)) अणु
		ret = PTR_ERR(slist);
		जाओ error_1;
	पूर्ण

	refcount_set(&slist->usage, 1);
	rcu_assign_poपूर्णांकer(volume->servers, slist);
	trace_afs_volume(volume->vid, 1, afs_volume_trace_alloc);
	वापस volume;

error_1:
	afs_put_cell(volume->cell, afs_cell_trace_put_vol);
	kमुक्त(volume);
error_0:
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Look up or allocate a volume record.
 */
अटल काष्ठा afs_volume *afs_lookup_volume(काष्ठा afs_fs_context *params,
					    काष्ठा afs_vldb_entry *vldb,
					    अचिन्हित दीर्घ type_mask)
अणु
	काष्ठा afs_volume *candidate, *volume;

	candidate = afs_alloc_volume(params, vldb, type_mask);
	अगर (IS_ERR(candidate))
		वापस candidate;

	volume = afs_insert_volume_पूर्णांकo_cell(params->cell, candidate);
	अगर (volume != candidate)
		afs_put_volume(params->net, candidate, afs_volume_trace_put_cell_dup);
	वापस volume;
पूर्ण

/*
 * Look up a VLDB record क्रम a volume.
 */
अटल काष्ठा afs_vldb_entry *afs_vl_lookup_vldb(काष्ठा afs_cell *cell,
						 काष्ठा key *key,
						 स्थिर अक्षर *volname,
						 माप_प्रकार volnamesz)
अणु
	काष्ठा afs_vldb_entry *vldb = ERR_PTR(-EDESTADDRREQ);
	काष्ठा afs_vl_cursor vc;
	पूर्णांक ret;

	अगर (!afs_begin_vlserver_operation(&vc, cell, key))
		वापस ERR_PTR(-ERESTARTSYS);

	जबतक (afs_select_vlserver(&vc)) अणु
		vldb = afs_vl_get_entry_by_name_u(&vc, volname, volnamesz);
	पूर्ण

	ret = afs_end_vlserver_operation(&vc);
	वापस ret < 0 ? ERR_PTR(ret) : vldb;
पूर्ण

/*
 * Look up a volume in the VL server and create a candidate volume record क्रम
 * it.
 *
 * The volume name can be one of the following:
 *	"%[cell:]volume[.]"		R/W volume
 *	"#[cell:]volume[.]"		R/O or R/W volume (rwparent=0),
 *					 or R/W (rwparent=1) volume
 *	"%[cell:]volume.readonly"	R/O volume
 *	"#[cell:]volume.readonly"	R/O volume
 *	"%[cell:]volume.backup"		Backup volume
 *	"#[cell:]volume.backup"		Backup volume
 *
 * The cell name is optional, and शेषs to the current cell.
 *
 * See "The Rules of Mount Point Traversal" in Chapter 5 of the AFS SysAdmin
 * Guide
 * - Rule 1: Explicit type suffix क्रमces access of that type or nothing
 *           (no suffix, then use Rule 2 & 3)
 * - Rule 2: If parent volume is R/O, then mount R/O volume by preference, R/W
 *           अगर not available
 * - Rule 3: If parent volume is R/W, then only mount R/W volume unless
 *           explicitly told otherwise
 */
काष्ठा afs_volume *afs_create_volume(काष्ठा afs_fs_context *params)
अणु
	काष्ठा afs_vldb_entry *vldb;
	काष्ठा afs_volume *volume;
	अचिन्हित दीर्घ type_mask = 1UL << params->type;

	vldb = afs_vl_lookup_vldb(params->cell, params->key,
				  params->volname, params->volnamesz);
	अगर (IS_ERR(vldb))
		वापस ERR_CAST(vldb);

	अगर (test_bit(AFS_VLDB_QUERY_ERROR, &vldb->flags)) अणु
		volume = ERR_PTR(vldb->error);
		जाओ error;
	पूर्ण

	/* Make the final decision on the type we want */
	volume = ERR_PTR(-ENOMEDIUM);
	अगर (params->क्रमce) अणु
		अगर (!(vldb->flags & type_mask))
			जाओ error;
	पूर्ण अन्यथा अगर (test_bit(AFS_VLDB_HAS_RO, &vldb->flags)) अणु
		params->type = AFSVL_ROVOL;
	पूर्ण अन्यथा अगर (test_bit(AFS_VLDB_HAS_RW, &vldb->flags)) अणु
		params->type = AFSVL_RWVOL;
	पूर्ण अन्यथा अणु
		जाओ error;
	पूर्ण

	type_mask = 1UL << params->type;
	volume = afs_lookup_volume(params, vldb, type_mask);

error:
	kमुक्त(vldb);
	वापस volume;
पूर्ण

/*
 * Destroy a volume record
 */
अटल व्योम afs_destroy_volume(काष्ठा afs_net *net, काष्ठा afs_volume *volume)
अणु
	_enter("%p", volume);

#अगर_घोषित CONFIG_AFS_FSCACHE
	ASSERTCMP(volume->cache, ==, शून्य);
#पूर्ण_अगर

	afs_हटाओ_volume_from_cell(volume);
	afs_put_serverlist(net, rcu_access_poपूर्णांकer(volume->servers));
	afs_put_cell(volume->cell, afs_cell_trace_put_vol);
	trace_afs_volume(volume->vid, atomic_पढ़ो(&volume->usage),
			 afs_volume_trace_मुक्त);
	kमुक्त_rcu(volume, rcu);

	_leave(" [destroyed]");
पूर्ण

/*
 * Get a reference on a volume record.
 */
काष्ठा afs_volume *afs_get_volume(काष्ठा afs_volume *volume,
				  क्रमागत afs_volume_trace reason)
अणु
	अगर (volume) अणु
		पूर्णांक u = atomic_inc_वापस(&volume->usage);
		trace_afs_volume(volume->vid, u, reason);
	पूर्ण
	वापस volume;
पूर्ण


/*
 * Drop a reference on a volume record.
 */
व्योम afs_put_volume(काष्ठा afs_net *net, काष्ठा afs_volume *volume,
		    क्रमागत afs_volume_trace reason)
अणु
	अगर (volume) अणु
		afs_volid_t vid = volume->vid;
		पूर्णांक u = atomic_dec_वापस(&volume->usage);
		trace_afs_volume(vid, u, reason);
		अगर (u == 0)
			afs_destroy_volume(net, volume);
	पूर्ण
पूर्ण

/*
 * Activate a volume.
 */
व्योम afs_activate_volume(काष्ठा afs_volume *volume)
अणु
#अगर_घोषित CONFIG_AFS_FSCACHE
	volume->cache = fscache_acquire_cookie(volume->cell->cache,
					       &afs_volume_cache_index_def,
					       &volume->vid, माप(volume->vid),
					       शून्य, 0,
					       volume, 0, true);
#पूर्ण_अगर
पूर्ण

/*
 * Deactivate a volume.
 */
व्योम afs_deactivate_volume(काष्ठा afs_volume *volume)
अणु
	_enter("%s", volume->name);

#अगर_घोषित CONFIG_AFS_FSCACHE
	fscache_relinquish_cookie(volume->cache, शून्य,
				  test_bit(AFS_VOLUME_DELETED, &volume->flags));
	volume->cache = शून्य;
#पूर्ण_अगर

	_leave("");
पूर्ण

/*
 * Query the VL service to update the volume status.
 */
अटल पूर्णांक afs_update_volume_status(काष्ठा afs_volume *volume, काष्ठा key *key)
अणु
	काष्ठा afs_server_list *new, *old, *discard;
	काष्ठा afs_vldb_entry *vldb;
	अक्षर idbuf[16];
	पूर्णांक ret, idsz;

	_enter("");

	/* We look up an ID by passing it as a decimal string in the
	 * operation's name parameter.
	 */
	idsz = प्र_लिखो(idbuf, "%llu", volume->vid);

	vldb = afs_vl_lookup_vldb(volume->cell, key, idbuf, idsz);
	अगर (IS_ERR(vldb)) अणु
		ret = PTR_ERR(vldb);
		जाओ error;
	पूर्ण

	/* See अगर the volume got नामd. */
	अगर (vldb->name_len != volume->name_len ||
	    स_भेद(vldb->name, volume->name, vldb->name_len) != 0) अणु
		/* TODO: Use RCU'd string. */
		स_नकल(volume->name, vldb->name, AFS_MAXVOLNAME);
		volume->name_len = vldb->name_len;
	पूर्ण

	/* See अगर the volume's server list got updated. */
	new = afs_alloc_server_list(volume->cell, key,
				    vldb, (1 << volume->type));
	अगर (IS_ERR(new)) अणु
		ret = PTR_ERR(new);
		जाओ error_vldb;
	पूर्ण

	ग_लिखो_lock(&volume->servers_lock);

	discard = new;
	old = rcu_dereference_रक्षित(volume->servers,
					lockdep_is_held(&volume->servers_lock));
	अगर (afs_annotate_server_list(new, old)) अणु
		new->seq = volume->servers_seq + 1;
		rcu_assign_poपूर्णांकer(volume->servers, new);
		smp_wmb();
		volume->servers_seq++;
		discard = old;
	पूर्ण

	volume->update_at = kसमय_get_real_seconds() + afs_volume_record_lअगरe;
	ग_लिखो_unlock(&volume->servers_lock);
	ret = 0;

	afs_put_serverlist(volume->cell->net, discard);
error_vldb:
	kमुक्त(vldb);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Make sure the volume record is up to date.
 */
पूर्णांक afs_check_volume_status(काष्ठा afs_volume *volume, काष्ठा afs_operation *op)
अणु
	पूर्णांक ret, retries = 0;

	_enter("");

retry:
	अगर (test_bit(AFS_VOLUME_WAIT, &volume->flags))
		जाओ रुको;
	अगर (volume->update_at <= kसमय_get_real_seconds() ||
	    test_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags))
		जाओ update;
	_leave(" = 0");
	वापस 0;

update:
	अगर (!test_and_set_bit_lock(AFS_VOLUME_UPDATING, &volume->flags)) अणु
		clear_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags);
		ret = afs_update_volume_status(volume, op->key);
		अगर (ret < 0)
			set_bit(AFS_VOLUME_NEEDS_UPDATE, &volume->flags);
		clear_bit_unlock(AFS_VOLUME_WAIT, &volume->flags);
		clear_bit_unlock(AFS_VOLUME_UPDATING, &volume->flags);
		wake_up_bit(&volume->flags, AFS_VOLUME_WAIT);
		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

रुको:
	अगर (!test_bit(AFS_VOLUME_WAIT, &volume->flags)) अणु
		_leave(" = 0 [no wait]");
		वापस 0;
	पूर्ण

	ret = रुको_on_bit(&volume->flags, AFS_VOLUME_WAIT,
			  (op->flags & AFS_OPERATION_UNINTR) ?
			  TASK_UNINTERRUPTIBLE : TASK_INTERRUPTIBLE);
	अगर (ret == -ERESTARTSYS) अणु
		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

	retries++;
	अगर (retries == 4) अणु
		_leave(" = -ESTALE");
		वापस -ESTALE;
	पूर्ण
	जाओ retry;
पूर्ण
