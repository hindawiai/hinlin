<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache statistics
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL THREAD
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "internal.h"

/*
 * operation counters
 */
atomic_t fscache_n_op_pend;
atomic_t fscache_n_op_run;
atomic_t fscache_n_op_enqueue;
atomic_t fscache_n_op_deferred_release;
atomic_t fscache_n_op_initialised;
atomic_t fscache_n_op_release;
atomic_t fscache_n_op_gc;
atomic_t fscache_n_op_cancelled;
atomic_t fscache_n_op_rejected;

atomic_t fscache_n_attr_changed;
atomic_t fscache_n_attr_changed_ok;
atomic_t fscache_n_attr_changed_nobufs;
atomic_t fscache_n_attr_changed_nomem;
atomic_t fscache_n_attr_changed_calls;

atomic_t fscache_n_allocs;
atomic_t fscache_n_allocs_ok;
atomic_t fscache_n_allocs_रुको;
atomic_t fscache_n_allocs_nobufs;
atomic_t fscache_n_allocs_पूर्णांकr;
atomic_t fscache_n_allocs_object_dead;
atomic_t fscache_n_alloc_ops;
atomic_t fscache_n_alloc_op_रुकोs;

atomic_t fscache_n_retrievals;
atomic_t fscache_n_retrievals_ok;
atomic_t fscache_n_retrievals_रुको;
atomic_t fscache_n_retrievals_nodata;
atomic_t fscache_n_retrievals_nobufs;
atomic_t fscache_n_retrievals_पूर्णांकr;
atomic_t fscache_n_retrievals_nomem;
atomic_t fscache_n_retrievals_object_dead;
atomic_t fscache_n_retrieval_ops;
atomic_t fscache_n_retrieval_op_रुकोs;

atomic_t fscache_n_stores;
atomic_t fscache_n_stores_ok;
atomic_t fscache_n_stores_again;
atomic_t fscache_n_stores_nobufs;
atomic_t fscache_n_stores_oom;
atomic_t fscache_n_store_ops;
atomic_t fscache_n_store_calls;
atomic_t fscache_n_store_pages;
atomic_t fscache_n_store_radix_deletes;
atomic_t fscache_n_store_pages_over_limit;

atomic_t fscache_n_store_vmscan_not_storing;
atomic_t fscache_n_store_vmscan_gone;
atomic_t fscache_n_store_vmscan_busy;
atomic_t fscache_n_store_vmscan_cancelled;
atomic_t fscache_n_store_vmscan_रुको;

atomic_t fscache_n_marks;
atomic_t fscache_n_uncaches;

atomic_t fscache_n_acquires;
atomic_t fscache_n_acquires_null;
atomic_t fscache_n_acquires_no_cache;
atomic_t fscache_n_acquires_ok;
atomic_t fscache_n_acquires_nobufs;
atomic_t fscache_n_acquires_oom;

atomic_t fscache_n_invalidates;
atomic_t fscache_n_invalidates_run;

atomic_t fscache_n_updates;
atomic_t fscache_n_updates_null;
atomic_t fscache_n_updates_run;

atomic_t fscache_n_relinquishes;
atomic_t fscache_n_relinquishes_null;
atomic_t fscache_n_relinquishes_रुकोcrt;
atomic_t fscache_n_relinquishes_retire;

atomic_t fscache_n_cookie_index;
atomic_t fscache_n_cookie_data;
atomic_t fscache_n_cookie_special;

atomic_t fscache_n_object_alloc;
atomic_t fscache_n_object_no_alloc;
atomic_t fscache_n_object_lookups;
atomic_t fscache_n_object_lookups_negative;
atomic_t fscache_n_object_lookups_positive;
atomic_t fscache_n_object_lookups_समयd_out;
atomic_t fscache_n_object_created;
atomic_t fscache_n_object_avail;
atomic_t fscache_n_object_dead;

atomic_t fscache_n_checkaux_none;
atomic_t fscache_n_checkaux_okay;
atomic_t fscache_n_checkaux_update;
atomic_t fscache_n_checkaux_obsolete;

atomic_t fscache_n_cop_alloc_object;
atomic_t fscache_n_cop_lookup_object;
atomic_t fscache_n_cop_lookup_complete;
atomic_t fscache_n_cop_grab_object;
atomic_t fscache_n_cop_invalidate_object;
atomic_t fscache_n_cop_update_object;
atomic_t fscache_n_cop_drop_object;
atomic_t fscache_n_cop_put_object;
atomic_t fscache_n_cop_sync_cache;
atomic_t fscache_n_cop_attr_changed;
atomic_t fscache_n_cop_पढ़ो_or_alloc_page;
atomic_t fscache_n_cop_पढ़ो_or_alloc_pages;
atomic_t fscache_n_cop_allocate_page;
atomic_t fscache_n_cop_allocate_pages;
atomic_t fscache_n_cop_ग_लिखो_page;
atomic_t fscache_n_cop_uncache_page;
atomic_t fscache_n_cop_dissociate_pages;

atomic_t fscache_n_cache_no_space_reject;
atomic_t fscache_n_cache_stale_objects;
atomic_t fscache_n_cache_retired_objects;
atomic_t fscache_n_cache_culled_objects;

/*
 * display the general statistics
 */
पूर्णांक fscache_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "FS-Cache statistics\n");

	seq_म_लिखो(m, "Cookies: idx=%u dat=%u spc=%u\n",
		   atomic_पढ़ो(&fscache_n_cookie_index),
		   atomic_पढ़ो(&fscache_n_cookie_data),
		   atomic_पढ़ो(&fscache_n_cookie_special));

	seq_म_लिखो(m, "Objects: alc=%u nal=%u avl=%u ded=%u\n",
		   atomic_पढ़ो(&fscache_n_object_alloc),
		   atomic_पढ़ो(&fscache_n_object_no_alloc),
		   atomic_पढ़ो(&fscache_n_object_avail),
		   atomic_पढ़ो(&fscache_n_object_dead));
	seq_म_लिखो(m, "ChkAux : non=%u ok=%u upd=%u obs=%u\n",
		   atomic_पढ़ो(&fscache_n_checkaux_none),
		   atomic_पढ़ो(&fscache_n_checkaux_okay),
		   atomic_पढ़ो(&fscache_n_checkaux_update),
		   atomic_पढ़ो(&fscache_n_checkaux_obsolete));

	seq_म_लिखो(m, "Pages  : mrk=%u unc=%u\n",
		   atomic_पढ़ो(&fscache_n_marks),
		   atomic_पढ़ो(&fscache_n_uncaches));

	seq_म_लिखो(m, "Acquire: n=%u nul=%u noc=%u ok=%u nbf=%u"
		   " oom=%u\n",
		   atomic_पढ़ो(&fscache_n_acquires),
		   atomic_पढ़ो(&fscache_n_acquires_null),
		   atomic_पढ़ो(&fscache_n_acquires_no_cache),
		   atomic_पढ़ो(&fscache_n_acquires_ok),
		   atomic_पढ़ो(&fscache_n_acquires_nobufs),
		   atomic_पढ़ो(&fscache_n_acquires_oom));

	seq_म_लिखो(m, "Lookups: n=%u neg=%u pos=%u crt=%u tmo=%u\n",
		   atomic_पढ़ो(&fscache_n_object_lookups),
		   atomic_पढ़ो(&fscache_n_object_lookups_negative),
		   atomic_पढ़ो(&fscache_n_object_lookups_positive),
		   atomic_पढ़ो(&fscache_n_object_created),
		   atomic_पढ़ो(&fscache_n_object_lookups_समयd_out));

	seq_म_लिखो(m, "Invals : n=%u run=%u\n",
		   atomic_पढ़ो(&fscache_n_invalidates),
		   atomic_पढ़ो(&fscache_n_invalidates_run));

	seq_म_लिखो(m, "Updates: n=%u nul=%u run=%u\n",
		   atomic_पढ़ो(&fscache_n_updates),
		   atomic_पढ़ो(&fscache_n_updates_null),
		   atomic_पढ़ो(&fscache_n_updates_run));

	seq_म_लिखो(m, "Relinqs: n=%u nul=%u wcr=%u rtr=%u\n",
		   atomic_पढ़ो(&fscache_n_relinquishes),
		   atomic_पढ़ो(&fscache_n_relinquishes_null),
		   atomic_पढ़ो(&fscache_n_relinquishes_रुकोcrt),
		   atomic_पढ़ो(&fscache_n_relinquishes_retire));

	seq_म_लिखो(m, "AttrChg: n=%u ok=%u nbf=%u oom=%u run=%u\n",
		   atomic_पढ़ो(&fscache_n_attr_changed),
		   atomic_पढ़ो(&fscache_n_attr_changed_ok),
		   atomic_पढ़ो(&fscache_n_attr_changed_nobufs),
		   atomic_पढ़ो(&fscache_n_attr_changed_nomem),
		   atomic_पढ़ो(&fscache_n_attr_changed_calls));

	seq_म_लिखो(m, "Allocs : n=%u ok=%u wt=%u nbf=%u int=%u\n",
		   atomic_पढ़ो(&fscache_n_allocs),
		   atomic_पढ़ो(&fscache_n_allocs_ok),
		   atomic_पढ़ो(&fscache_n_allocs_रुको),
		   atomic_पढ़ो(&fscache_n_allocs_nobufs),
		   atomic_पढ़ो(&fscache_n_allocs_पूर्णांकr));
	seq_म_लिखो(m, "Allocs : ops=%u owt=%u abt=%u\n",
		   atomic_पढ़ो(&fscache_n_alloc_ops),
		   atomic_पढ़ो(&fscache_n_alloc_op_रुकोs),
		   atomic_पढ़ो(&fscache_n_allocs_object_dead));

	seq_म_लिखो(m, "Retrvls: n=%u ok=%u wt=%u nod=%u nbf=%u"
		   " int=%u oom=%u\n",
		   atomic_पढ़ो(&fscache_n_retrievals),
		   atomic_पढ़ो(&fscache_n_retrievals_ok),
		   atomic_पढ़ो(&fscache_n_retrievals_रुको),
		   atomic_पढ़ो(&fscache_n_retrievals_nodata),
		   atomic_पढ़ो(&fscache_n_retrievals_nobufs),
		   atomic_पढ़ो(&fscache_n_retrievals_पूर्णांकr),
		   atomic_पढ़ो(&fscache_n_retrievals_nomem));
	seq_म_लिखो(m, "Retrvls: ops=%u owt=%u abt=%u\n",
		   atomic_पढ़ो(&fscache_n_retrieval_ops),
		   atomic_पढ़ो(&fscache_n_retrieval_op_रुकोs),
		   atomic_पढ़ो(&fscache_n_retrievals_object_dead));

	seq_म_लिखो(m, "Stores : n=%u ok=%u agn=%u nbf=%u oom=%u\n",
		   atomic_पढ़ो(&fscache_n_stores),
		   atomic_पढ़ो(&fscache_n_stores_ok),
		   atomic_पढ़ो(&fscache_n_stores_again),
		   atomic_पढ़ो(&fscache_n_stores_nobufs),
		   atomic_पढ़ो(&fscache_n_stores_oom));
	seq_म_लिखो(m, "Stores : ops=%u run=%u pgs=%u rxd=%u olm=%u\n",
		   atomic_पढ़ो(&fscache_n_store_ops),
		   atomic_पढ़ो(&fscache_n_store_calls),
		   atomic_पढ़ो(&fscache_n_store_pages),
		   atomic_पढ़ो(&fscache_n_store_radix_deletes),
		   atomic_पढ़ो(&fscache_n_store_pages_over_limit));

	seq_म_लिखो(m, "VmScan : nos=%u gon=%u bsy=%u can=%u wt=%u\n",
		   atomic_पढ़ो(&fscache_n_store_vmscan_not_storing),
		   atomic_पढ़ो(&fscache_n_store_vmscan_gone),
		   atomic_पढ़ो(&fscache_n_store_vmscan_busy),
		   atomic_पढ़ो(&fscache_n_store_vmscan_cancelled),
		   atomic_पढ़ो(&fscache_n_store_vmscan_रुको));

	seq_म_लिखो(m, "Ops    : pend=%u run=%u enq=%u can=%u rej=%u\n",
		   atomic_पढ़ो(&fscache_n_op_pend),
		   atomic_पढ़ो(&fscache_n_op_run),
		   atomic_पढ़ो(&fscache_n_op_enqueue),
		   atomic_पढ़ो(&fscache_n_op_cancelled),
		   atomic_पढ़ो(&fscache_n_op_rejected));
	seq_म_लिखो(m, "Ops    : ini=%u dfr=%u rel=%u gc=%u\n",
		   atomic_पढ़ो(&fscache_n_op_initialised),
		   atomic_पढ़ो(&fscache_n_op_deferred_release),
		   atomic_पढ़ो(&fscache_n_op_release),
		   atomic_पढ़ो(&fscache_n_op_gc));

	seq_म_लिखो(m, "CacheOp: alo=%d luo=%d luc=%d gro=%d\n",
		   atomic_पढ़ो(&fscache_n_cop_alloc_object),
		   atomic_पढ़ो(&fscache_n_cop_lookup_object),
		   atomic_पढ़ो(&fscache_n_cop_lookup_complete),
		   atomic_पढ़ो(&fscache_n_cop_grab_object));
	seq_म_लिखो(m, "CacheOp: inv=%d upo=%d dro=%d pto=%d atc=%d syn=%d\n",
		   atomic_पढ़ो(&fscache_n_cop_invalidate_object),
		   atomic_पढ़ो(&fscache_n_cop_update_object),
		   atomic_पढ़ो(&fscache_n_cop_drop_object),
		   atomic_पढ़ो(&fscache_n_cop_put_object),
		   atomic_पढ़ो(&fscache_n_cop_attr_changed),
		   atomic_पढ़ो(&fscache_n_cop_sync_cache));
	seq_म_लिखो(m, "CacheOp: rap=%d ras=%d alp=%d als=%d wrp=%d ucp=%d dsp=%d\n",
		   atomic_पढ़ो(&fscache_n_cop_पढ़ो_or_alloc_page),
		   atomic_पढ़ो(&fscache_n_cop_पढ़ो_or_alloc_pages),
		   atomic_पढ़ो(&fscache_n_cop_allocate_page),
		   atomic_पढ़ो(&fscache_n_cop_allocate_pages),
		   atomic_पढ़ो(&fscache_n_cop_ग_लिखो_page),
		   atomic_पढ़ो(&fscache_n_cop_uncache_page),
		   atomic_पढ़ो(&fscache_n_cop_dissociate_pages));
	seq_म_लिखो(m, "CacheEv: nsp=%d stl=%d rtr=%d cul=%d\n",
		   atomic_पढ़ो(&fscache_n_cache_no_space_reject),
		   atomic_पढ़ो(&fscache_n_cache_stale_objects),
		   atomic_पढ़ो(&fscache_n_cache_retired_objects),
		   atomic_पढ़ो(&fscache_n_cache_culled_objects));
	netfs_stats_show(m);
	वापस 0;
पूर्ण
