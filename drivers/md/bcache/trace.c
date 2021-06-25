<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "bcache.h"
#समावेश "btree.h"

#समावेश <linux/blktrace_api.h>
#समावेश <linux/module.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/bcache.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_request_start);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_request_end);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_bypass_sequential);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_bypass_congested);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_पढ़ो);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_ग_लिखो);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_पढ़ो_retry);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_cache_insert);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_journal_replay_key);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_journal_ग_लिखो);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_journal_full);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_journal_entry_full);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_cache_cannibalize);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_पढ़ो);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_ग_लिखो);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_node_alloc);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_node_alloc_fail);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_node_मुक्त);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_gc_coalesce);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_gc_start);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_gc_end);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_gc_copy);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_gc_copy_collision);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_insert_key);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_node_split);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_node_compact);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_btree_set_root);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_invalidate);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_alloc_fail);

EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_ग_लिखोback);
EXPORT_TRACEPOINT_SYMBOL_GPL(bcache_ग_लिखोback_collision);
