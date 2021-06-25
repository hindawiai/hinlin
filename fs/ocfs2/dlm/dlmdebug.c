<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmdebug.c
 *
 * debug functionality क्रम the dlm
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>

#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"
#समावेश "dlmdomain.h"
#समावेश "dlmdebug.h"

#घोषणा MLOG_MASK_PREFIX ML_DLM
#समावेश "../cluster/masklog.h"

अटल पूर्णांक stringअगरy_lockname(स्थिर अक्षर *lockname, पूर्णांक locklen, अक्षर *buf,
			      पूर्णांक len);

व्योम dlm_prपूर्णांक_one_lock_resource(काष्ठा dlm_lock_resource *res)
अणु
	spin_lock(&res->spinlock);
	__dlm_prपूर्णांक_one_lock_resource(res);
	spin_unlock(&res->spinlock);
पूर्ण

अटल व्योम dlm_prपूर्णांक_lockres_refmap(काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक bit;
	निश्चित_spin_locked(&res->spinlock);

	prपूर्णांकk("  refmap nodes: [ ");
	bit = 0;
	जबतक (1) अणु
		bit = find_next_bit(res->refmap, O2NM_MAX_NODES, bit);
		अगर (bit >= O2NM_MAX_NODES)
			अवरोध;
		prपूर्णांकk("%u ", bit);
		bit++;
	पूर्ण
	prपूर्णांकk("], inflight=%u\n", res->inflight_locks);
पूर्ण

अटल व्योम __dlm_prपूर्णांक_lock(काष्ठा dlm_lock *lock)
अणु
	spin_lock(&lock->spinlock);

	prपूर्णांकk("    type=%d, conv=%d, node=%u, cookie=%u:%llu, "
	       "ref=%u, ast=(empty=%c,pend=%c), bast=(empty=%c,pend=%c), "
	       "pending=(conv=%c,lock=%c,cancel=%c,unlock=%c)\n",
	       lock->ml.type, lock->ml.convert_type, lock->ml.node,
	       dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	       dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
	       kref_पढ़ो(&lock->lock_refs),
	       (list_empty(&lock->ast_list) ? 'y' : 'n'),
	       (lock->ast_pending ? 'y' : 'n'),
	       (list_empty(&lock->bast_list) ? 'y' : 'n'),
	       (lock->bast_pending ? 'y' : 'n'),
	       (lock->convert_pending ? 'y' : 'n'),
	       (lock->lock_pending ? 'y' : 'n'),
	       (lock->cancel_pending ? 'y' : 'n'),
	       (lock->unlock_pending ? 'y' : 'n'));

	spin_unlock(&lock->spinlock);
पूर्ण

व्योम __dlm_prपूर्णांक_one_lock_resource(काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा dlm_lock *lock;
	अक्षर buf[DLM_LOCKID_NAME_MAX];

	निश्चित_spin_locked(&res->spinlock);

	stringअगरy_lockname(res->lockname.name, res->lockname.len,
			   buf, माप(buf));
	prपूर्णांकk("lockres: %s, owner=%u, state=%u\n",
	       buf, res->owner, res->state);
	prपूर्णांकk("  last used: %lu, refcnt: %u, on purge list: %s\n",
	       res->last_used, kref_पढ़ो(&res->refs),
	       list_empty(&res->purge) ? "no" : "yes");
	prपूर्णांकk("  on dirty list: %s, on reco list: %s, "
	       "migrating pending: %s\n",
	       list_empty(&res->dirty) ? "no" : "yes",
	       list_empty(&res->recovering) ? "no" : "yes",
	       res->migration_pending ? "yes" : "no");
	prपूर्णांकk("  inflight locks: %d, asts reserved: %d\n",
	       res->inflight_locks, atomic_पढ़ो(&res->asts_reserved));
	dlm_prपूर्णांक_lockres_refmap(res);
	prपूर्णांकk("  granted queue:\n");
	list_क्रम_each_entry(lock, &res->granted, list) अणु
		__dlm_prपूर्णांक_lock(lock);
	पूर्ण
	prपूर्णांकk("  converting queue:\n");
	list_क्रम_each_entry(lock, &res->converting, list) अणु
		__dlm_prपूर्णांक_lock(lock);
	पूर्ण
	prपूर्णांकk("  blocked queue:\n");
	list_क्रम_each_entry(lock, &res->blocked, list) अणु
		__dlm_prपूर्णांक_lock(lock);
	पूर्ण
पूर्ण

व्योम dlm_prपूर्णांक_one_lock(काष्ठा dlm_lock *lockid)
अणु
	dlm_prपूर्णांक_one_lock_resource(lockid->lockres);
पूर्ण
EXPORT_SYMBOL_GPL(dlm_prपूर्णांक_one_lock);

अटल स्थिर अक्षर *dlm_errnames[] = अणु
	[DLM_NORMAL] =			"DLM_NORMAL",
	[DLM_GRANTED] =			"DLM_GRANTED",
	[DLM_DENIED] =			"DLM_DENIED",
	[DLM_DENIED_NOLOCKS] =		"DLM_DENIED_NOLOCKS",
	[DLM_WORKING] =			"DLM_WORKING",
	[DLM_BLOCKED] =			"DLM_BLOCKED",
	[DLM_BLOCKED_ORPHAN] =		"DLM_BLOCKED_ORPHAN",
	[DLM_DENIED_GRACE_PERIOD] =	"DLM_DENIED_GRACE_PERIOD",
	[DLM_SYSERR] =			"DLM_SYSERR",
	[DLM_NOSUPPORT] =		"DLM_NOSUPPORT",
	[DLM_CANCELGRANT] =		"DLM_CANCELGRANT",
	[DLM_IVLOCKID] =		"DLM_IVLOCKID",
	[DLM_SYNC] =			"DLM_SYNC",
	[DLM_BADTYPE] =			"DLM_BADTYPE",
	[DLM_BADRESOURCE] =		"DLM_BADRESOURCE",
	[DLM_MAXHANDLES] =		"DLM_MAXHANDLES",
	[DLM_NOCLINFO] =		"DLM_NOCLINFO",
	[DLM_NOLOCKMGR] =		"DLM_NOLOCKMGR",
	[DLM_NOPURGED] =		"DLM_NOPURGED",
	[DLM_BADARGS] =			"DLM_BADARGS",
	[DLM_VOID] =			"DLM_VOID",
	[DLM_NOTQUEUED] =		"DLM_NOTQUEUED",
	[DLM_IVBUFLEN] =		"DLM_IVBUFLEN",
	[DLM_CVTUNGRANT] =		"DLM_CVTUNGRANT",
	[DLM_BADPARAM] =		"DLM_BADPARAM",
	[DLM_VALNOTVALID] =		"DLM_VALNOTVALID",
	[DLM_REJECTED] =		"DLM_REJECTED",
	[DLM_ABORT] =			"DLM_ABORT",
	[DLM_CANCEL] =			"DLM_CANCEL",
	[DLM_IVRESHANDLE] =		"DLM_IVRESHANDLE",
	[DLM_DEADLOCK] =		"DLM_DEADLOCK",
	[DLM_DENIED_NOASTS] =		"DLM_DENIED_NOASTS",
	[DLM_FORWARD] =			"DLM_FORWARD",
	[DLM_TIMEOUT] =			"DLM_TIMEOUT",
	[DLM_IVGROUPID] =		"DLM_IVGROUPID",
	[DLM_VERS_CONFLICT] =		"DLM_VERS_CONFLICT",
	[DLM_BAD_DEVICE_PATH] =		"DLM_BAD_DEVICE_PATH",
	[DLM_NO_DEVICE_PERMISSION] =	"DLM_NO_DEVICE_PERMISSION",
	[DLM_NO_CONTROL_DEVICE ] =	"DLM_NO_CONTROL_DEVICE ",
	[DLM_RECOVERING] =		"DLM_RECOVERING",
	[DLM_MIGRATING] =		"DLM_MIGRATING",
	[DLM_MAXSTATS] =		"DLM_MAXSTATS",
पूर्ण;

अटल स्थिर अक्षर *dlm_errmsgs[] = अणु
	[DLM_NORMAL] = 			"request in progress",
	[DLM_GRANTED] = 		"request granted",
	[DLM_DENIED] = 			"request denied",
	[DLM_DENIED_NOLOCKS] = 		"request denied, out of system resources",
	[DLM_WORKING] = 		"async request in progress",
	[DLM_BLOCKED] = 		"lock request blocked",
	[DLM_BLOCKED_ORPHAN] = 		"lock request blocked by a orphan lock",
	[DLM_DENIED_GRACE_PERIOD] = 	"topological change in progress",
	[DLM_SYSERR] = 			"system error",
	[DLM_NOSUPPORT] = 		"unsupported",
	[DLM_CANCELGRANT] = 		"can't cancel convert: already granted",
	[DLM_IVLOCKID] = 		"bad lockid",
	[DLM_SYNC] = 			"synchronous request granted",
	[DLM_BADTYPE] = 		"bad resource type",
	[DLM_BADRESOURCE] = 		"bad resource handle",
	[DLM_MAXHANDLES] = 		"no more resource handles",
	[DLM_NOCLINFO] = 		"can't contact cluster manager",
	[DLM_NOLOCKMGR] = 		"can't contact lock manager",
	[DLM_NOPURGED] = 		"can't contact purge daemon",
	[DLM_BADARGS] = 		"bad api args",
	[DLM_VOID] = 			"no status",
	[DLM_NOTQUEUED] = 		"NOQUEUE was specified and request failed",
	[DLM_IVBUFLEN] = 		"invalid resource name length",
	[DLM_CVTUNGRANT] = 		"attempted to convert ungranted lock",
	[DLM_BADPARAM] = 		"invalid lock mode specified",
	[DLM_VALNOTVALID] = 		"value block has been invalidated",
	[DLM_REJECTED] = 		"request rejected, unrecognized client",
	[DLM_ABORT] = 			"blocked lock request cancelled",
	[DLM_CANCEL] = 			"conversion request cancelled",
	[DLM_IVRESHANDLE] = 		"invalid resource handle",
	[DLM_DEADLOCK] = 		"deadlock recovery refused this request",
	[DLM_DENIED_NOASTS] = 		"failed to allocate AST",
	[DLM_FORWARD] = 		"request must wait for primary's response",
	[DLM_TIMEOUT] = 		"timeout value for lock has expired",
	[DLM_IVGROUPID] = 		"invalid group specification",
	[DLM_VERS_CONFLICT] = 		"version conflicts prevent request handling",
	[DLM_BAD_DEVICE_PATH] = 	"Locks device does not exist or path wrong",
	[DLM_NO_DEVICE_PERMISSION] = 	"Client has insufficient perms for device",
	[DLM_NO_CONTROL_DEVICE] = 	"Cannot set options on opened device ",
	[DLM_RECOVERING] = 		"lock resource being recovered",
	[DLM_MIGRATING] = 		"lock resource being migrated",
	[DLM_MAXSTATS] = 		"invalid error number",
पूर्ण;

स्थिर अक्षर *dlm_errmsg(क्रमागत dlm_status err)
अणु
	अगर (err >= DLM_MAXSTATS || err < 0)
		वापस dlm_errmsgs[DLM_MAXSTATS];
	वापस dlm_errmsgs[err];
पूर्ण
EXPORT_SYMBOL_GPL(dlm_errmsg);

स्थिर अक्षर *dlm_errname(क्रमागत dlm_status err)
अणु
	अगर (err >= DLM_MAXSTATS || err < 0)
		वापस dlm_errnames[DLM_MAXSTATS];
	वापस dlm_errnames[err];
पूर्ण
EXPORT_SYMBOL_GPL(dlm_errname);

/* NOTE: This function converts a lockname पूर्णांकo a string. It uses knowledge
 * of the क्रमmat of the lockname that should be outside the purview of the dlm.
 * We are adding only to make dlm debugging slightly easier.
 *
 * For more on lockname क्रमmats, please refer to dlmglue.c and ocfs2_lockid.h.
 */
अटल पूर्णांक stringअगरy_lockname(स्थिर अक्षर *lockname, पूर्णांक locklen, अक्षर *buf,
			      पूर्णांक len)
अणु
	पूर्णांक out = 0;
	__be64 inode_blkno_be;

#घोषणा OCFS2_DENTRY_LOCK_INO_START	18
	अगर (*lockname == 'N') अणु
		स_नकल((__be64 *)&inode_blkno_be,
		       (अक्षर *)&lockname[OCFS2_DENTRY_LOCK_INO_START],
		       माप(__be64));
		out += scnम_लिखो(buf + out, len - out, "%.*s%08x",
				OCFS2_DENTRY_LOCK_INO_START - 1, lockname,
				(अचिन्हित पूर्णांक)be64_to_cpu(inode_blkno_be));
	पूर्ण अन्यथा
		out += scnम_लिखो(buf + out, len - out, "%.*s",
				locklen, lockname);
	वापस out;
पूर्ण

अटल पूर्णांक stringअगरy_nodemap(अचिन्हित दीर्घ *nodemap, पूर्णांक maxnodes,
			     अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक out = 0;
	पूर्णांक i = -1;

	जबतक ((i = find_next_bit(nodemap, maxnodes, i + 1)) < maxnodes)
		out += scnम_लिखो(buf + out, len - out, "%d ", i);

	वापस out;
पूर्ण

अटल पूर्णांक dump_mle(काष्ठा dlm_master_list_entry *mle, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक out = 0;
	अक्षर *mle_type;

	अगर (mle->type == DLM_MLE_BLOCK)
		mle_type = "BLK";
	अन्यथा अगर (mle->type == DLM_MLE_MASTER)
		mle_type = "MAS";
	अन्यथा
		mle_type = "MIG";

	out += stringअगरy_lockname(mle->mname, mle->mnamelen, buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out,
			"\t%3s\tmas=%3u\tnew=%3u\tevt=%1d\tuse=%1d\tref=%3d\n",
			mle_type, mle->master, mle->new_master,
			!list_empty(&mle->hb_events),
			!!mle->inuse,
			kref_पढ़ो(&mle->mle_refs));

	out += scnम_लिखो(buf + out, len - out, "Maybe=");
	out += stringअगरy_nodemap(mle->maybe_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	out += scnम_लिखो(buf + out, len - out, "Vote=");
	out += stringअगरy_nodemap(mle->vote_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	out += scnम_लिखो(buf + out, len - out, "Response=");
	out += stringअगरy_nodemap(mle->response_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	out += scnम_लिखो(buf + out, len - out, "Node=");
	out += stringअगरy_nodemap(mle->node_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	out += scnम_लिखो(buf + out, len - out, "\n");

	वापस out;
पूर्ण

व्योम dlm_prपूर्णांक_one_mle(काष्ठा dlm_master_list_entry *mle)
अणु
	अक्षर *buf;

	buf = (अक्षर *) get_zeroed_page(GFP_ATOMIC);
	अगर (buf) अणु
		dump_mle(mle, buf, PAGE_SIZE - 1);
		मुक्त_page((अचिन्हित दीर्घ)buf);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल काष्ठा dentry *dlm_debugfs_root;

#घोषणा DLM_DEBUGFS_सूची				"o2dlm"
#घोषणा DLM_DEBUGFS_DLM_STATE			"dlm_state"
#घोषणा DLM_DEBUGFS_LOCKING_STATE		"locking_state"
#घोषणा DLM_DEBUGFS_MLE_STATE			"mle_state"
#घोषणा DLM_DEBUGFS_PURGE_LIST			"purge_list"

/* begin - utils funcs */
अटल पूर्णांक debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	मुक्त_page((अचिन्हित दीर्घ)file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, file->निजी_data,
				       i_size_पढ़ो(file->f_mapping->host));
पूर्ण
/* end - util funcs */

/* begin - purge list funcs */
अटल पूर्णांक debug_purgelist_prपूर्णांक(काष्ठा dlm_ctxt *dlm, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dlm_lock_resource *res;
	पूर्णांक out = 0;
	अचिन्हित दीर्घ total = 0;

	out += scnम_लिखो(buf + out, len - out,
			"Dumping Purgelist for Domain: %s\n", dlm->name);

	spin_lock(&dlm->spinlock);
	list_क्रम_each_entry(res, &dlm->purge_list, purge) अणु
		++total;
		अगर (len - out < 100)
			जारी;
		spin_lock(&res->spinlock);
		out += stringअगरy_lockname(res->lockname.name,
					  res->lockname.len,
					  buf + out, len - out);
		out += scnम_लिखो(buf + out, len - out, "\t%ld\n",
				(jअगरfies - res->last_used)/HZ);
		spin_unlock(&res->spinlock);
	पूर्ण
	spin_unlock(&dlm->spinlock);

	out += scnम_लिखो(buf + out, len - out, "Total on list: %lu\n", total);

	वापस out;
पूर्ण

अटल पूर्णांक debug_purgelist_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_ctxt *dlm = inode->i_निजी;
	अक्षर *buf = शून्य;

	buf = (अक्षर *) get_zeroed_page(GFP_NOFS);
	अगर (!buf)
		जाओ bail;

	i_size_ग_लिखो(inode, debug_purgelist_prपूर्णांक(dlm, buf, PAGE_SIZE - 1));

	file->निजी_data = buf;

	वापस 0;
bail:
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_purgelist_fops = अणु
	.खोलो =		debug_purgelist_खोलो,
	.release =	debug_release,
	.पढ़ो =		debug_पढ़ो,
	.llseek =	generic_file_llseek,
पूर्ण;
/* end - purge list funcs */

/* begin - debug mle funcs */
अटल पूर्णांक debug_mle_prपूर्णांक(काष्ठा dlm_ctxt *dlm, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dlm_master_list_entry *mle;
	काष्ठा hlist_head *bucket;
	पूर्णांक i, out = 0;
	अचिन्हित दीर्घ total = 0, दीर्घest = 0, bucket_count = 0;

	out += scnम_लिखो(buf + out, len - out,
			"Dumping MLEs for Domain: %s\n", dlm->name);

	spin_lock(&dlm->master_lock);
	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
		bucket = dlm_master_hash(dlm, i);
		hlist_क्रम_each_entry(mle, bucket, master_hash_node) अणु
			++total;
			++bucket_count;
			अगर (len - out < 200)
				जारी;
			out += dump_mle(mle, buf + out, len - out);
		पूर्ण
		दीर्घest = max(दीर्घest, bucket_count);
		bucket_count = 0;
	पूर्ण
	spin_unlock(&dlm->master_lock);

	out += scnम_लिखो(buf + out, len - out,
			"Total: %lu, Longest: %lu\n", total, दीर्घest);
	वापस out;
पूर्ण

अटल पूर्णांक debug_mle_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_ctxt *dlm = inode->i_निजी;
	अक्षर *buf = शून्य;

	buf = (अक्षर *) get_zeroed_page(GFP_NOFS);
	अगर (!buf)
		जाओ bail;

	i_size_ग_लिखो(inode, debug_mle_prपूर्णांक(dlm, buf, PAGE_SIZE - 1));

	file->निजी_data = buf;

	वापस 0;
bail:
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_mle_fops = अणु
	.खोलो =		debug_mle_खोलो,
	.release =	debug_release,
	.पढ़ो =		debug_पढ़ो,
	.llseek =	generic_file_llseek,
पूर्ण;

/* end - debug mle funcs */

/* begin - debug lockres funcs */
अटल पूर्णांक dump_lock(काष्ठा dlm_lock *lock, पूर्णांक list_type, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक out;

#घोषणा DEBUG_LOCK_VERSION	1
	spin_lock(&lock->spinlock);
	out = scnम_लिखो(buf, len, "LOCK:%d,%d,%d,%d,%d,%d:%lld,%d,%d,%d,%d,%d,"
		       "%d,%d,%d,%d\n",
		       DEBUG_LOCK_VERSION,
		       list_type, lock->ml.type, lock->ml.convert_type,
		       lock->ml.node,
		       dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		       dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		       !list_empty(&lock->ast_list),
		       !list_empty(&lock->bast_list),
		       lock->ast_pending, lock->bast_pending,
		       lock->convert_pending, lock->lock_pending,
		       lock->cancel_pending, lock->unlock_pending,
		       kref_पढ़ो(&lock->lock_refs));
	spin_unlock(&lock->spinlock);

	वापस out;
पूर्ण

अटल पूर्णांक dump_lockres(काष्ठा dlm_lock_resource *res, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dlm_lock *lock;
	पूर्णांक i;
	पूर्णांक out = 0;

	out += scnम_लिखो(buf + out, len - out, "NAME:");
	out += stringअगरy_lockname(res->lockname.name, res->lockname.len,
				  buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

#घोषणा DEBUG_LRES_VERSION	1
	out += scnम_लिखो(buf + out, len - out,
			"LRES:%d,%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d\n",
			DEBUG_LRES_VERSION,
			res->owner, res->state, res->last_used,
			!list_empty(&res->purge),
			!list_empty(&res->dirty),
			!list_empty(&res->recovering),
			res->inflight_locks, res->migration_pending,
			atomic_पढ़ो(&res->asts_reserved),
			kref_पढ़ो(&res->refs));

	/* refmap */
	out += scnम_लिखो(buf + out, len - out, "RMAP:");
	out += stringअगरy_nodemap(res->refmap, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* lvb */
	out += scnम_लिखो(buf + out, len - out, "LVBX:");
	क्रम (i = 0; i < DLM_LVB_LEN; i++)
		out += scnम_लिखो(buf + out, len - out,
					"%02x", (अचिन्हित अक्षर)res->lvb[i]);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* granted */
	list_क्रम_each_entry(lock, &res->granted, list)
		out += dump_lock(lock, 0, buf + out, len - out);

	/* converting */
	list_क्रम_each_entry(lock, &res->converting, list)
		out += dump_lock(lock, 1, buf + out, len - out);

	/* blocked */
	list_क्रम_each_entry(lock, &res->blocked, list)
		out += dump_lock(lock, 2, buf + out, len - out);

	out += scnम_लिखो(buf + out, len - out, "\n");

	वापस out;
पूर्ण

अटल व्योम *lockres_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा debug_lockres *dl = m->निजी;
	काष्ठा dlm_ctxt *dlm = dl->dl_ctxt;
	काष्ठा dlm_lock_resource *oldres = dl->dl_res;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा list_head *track_list;

	spin_lock(&dlm->track_lock);
	अगर (oldres)
		track_list = &oldres->tracking;
	अन्यथा अणु
		track_list = &dlm->tracking_list;
		अगर (list_empty(track_list)) अणु
			dl = शून्य;
			spin_unlock(&dlm->track_lock);
			जाओ bail;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(res, track_list, tracking) अणु
		अगर (&res->tracking == &dlm->tracking_list)
			res = शून्य;
		अन्यथा
			dlm_lockres_get(res);
		अवरोध;
	पूर्ण
	spin_unlock(&dlm->track_lock);

	अगर (oldres)
		dlm_lockres_put(oldres);

	dl->dl_res = res;

	अगर (res) अणु
		spin_lock(&res->spinlock);
		dump_lockres(res, dl->dl_buf, dl->dl_len - 1);
		spin_unlock(&res->spinlock);
	पूर्ण अन्यथा
		dl = शून्य;

bail:
	/* passed to seq_show */
	वापस dl;
पूर्ण

अटल व्योम lockres_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल व्योम *lockres_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक lockres_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा debug_lockres *dl = (काष्ठा debug_lockres *)v;

	seq_म_लिखो(s, "%s", dl->dl_buf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations debug_lockres_ops = अणु
	.start =	lockres_seq_start,
	.stop =		lockres_seq_stop,
	.next =		lockres_seq_next,
	.show =		lockres_seq_show,
पूर्ण;

अटल पूर्णांक debug_lockres_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_ctxt *dlm = inode->i_निजी;
	काष्ठा debug_lockres *dl;
	व्योम *buf;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		जाओ bail;

	dl = __seq_खोलो_निजी(file, &debug_lockres_ops, माप(*dl));
	अगर (!dl)
		जाओ bailमुक्त;

	dl->dl_len = PAGE_SIZE;
	dl->dl_buf = buf;

	dlm_grab(dlm);
	dl->dl_ctxt = dlm;

	वापस 0;

bailमुक्त:
	kमुक्त(buf);
bail:
	mlog_त्रुटि_सं(-ENOMEM);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक debug_lockres_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा debug_lockres *dl = (काष्ठा debug_lockres *)seq->निजी;

	अगर (dl->dl_res)
		dlm_lockres_put(dl->dl_res);
	dlm_put(dl->dl_ctxt);
	kमुक्त(dl->dl_buf);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations debug_lockres_fops = अणु
	.खोलो =		debug_lockres_खोलो,
	.release =	debug_lockres_release,
	.पढ़ो =		seq_पढ़ो,
	.llseek =	seq_lseek,
पूर्ण;
/* end - debug lockres funcs */

/* begin - debug state funcs */
अटल पूर्णांक debug_state_prपूर्णांक(काष्ठा dlm_ctxt *dlm, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक out = 0;
	काष्ठा dlm_reco_node_data *node;
	अक्षर *state;
	पूर्णांक cur_mles = 0, tot_mles = 0;
	पूर्णांक i;

	spin_lock(&dlm->spinlock);

	चयन (dlm->dlm_state) अणु
	हाल DLM_CTXT_NEW:
		state = "NEW"; अवरोध;
	हाल DLM_CTXT_JOINED:
		state = "JOINED"; अवरोध;
	हाल DLM_CTXT_IN_SHUTDOWN:
		state = "SHUTDOWN"; अवरोध;
	हाल DLM_CTXT_LEAVING:
		state = "LEAVING"; अवरोध;
	शेष:
		state = "UNKNOWN"; अवरोध;
	पूर्ण

	/* Doमुख्य: xxxxxxxxxx  Key: 0xdfbac769 */
	out += scnम_लिखो(buf + out, len - out,
			"Domain: %s  Key: 0x%08x  Protocol: %d.%d\n",
			dlm->name, dlm->key, dlm->dlm_locking_proto.pv_major,
			dlm->dlm_locking_proto.pv_minor);

	/* Thपढ़ो Pid: xxx  Node: xxx  State: xxxxx */
	out += scnम_लिखो(buf + out, len - out,
			"Thread Pid: %d  Node: %d  State: %s\n",
			task_pid_nr(dlm->dlm_thपढ़ो_task), dlm->node_num, state);

	/* Number of Joins: xxx  Joining Node: xxx */
	out += scnम_लिखो(buf + out, len - out,
			"Number of Joins: %d  Joining Node: %d\n",
			dlm->num_joins, dlm->joining_node);

	/* Doमुख्य Map: xx xx xx */
	out += scnम_लिखो(buf + out, len - out, "Domain Map: ");
	out += stringअगरy_nodemap(dlm->करोमुख्य_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* Exit Doमुख्य Map: xx xx xx */
	out += scnम_लिखो(buf + out, len - out, "Exit Domain Map: ");
	out += stringअगरy_nodemap(dlm->निकास_करोमुख्य_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* Live Map: xx xx xx */
	out += scnम_लिखो(buf + out, len - out, "Live Map: ");
	out += stringअगरy_nodemap(dlm->live_nodes_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* Lock Resources: xxx (xxx) */
	out += scnम_लिखो(buf + out, len - out,
			"Lock Resources: %d (%d)\n",
			atomic_पढ़ो(&dlm->res_cur_count),
			atomic_पढ़ो(&dlm->res_tot_count));

	क्रम (i = 0; i < DLM_MLE_NUM_TYPES; ++i)
		tot_mles += atomic_पढ़ो(&dlm->mle_tot_count[i]);

	क्रम (i = 0; i < DLM_MLE_NUM_TYPES; ++i)
		cur_mles += atomic_पढ़ो(&dlm->mle_cur_count[i]);

	/* MLEs: xxx (xxx) */
	out += scnम_लिखो(buf + out, len - out,
			"MLEs: %d (%d)\n", cur_mles, tot_mles);

	/*  Blocking: xxx (xxx) */
	out += scnम_लिखो(buf + out, len - out,
			"  Blocking: %d (%d)\n",
			atomic_पढ़ो(&dlm->mle_cur_count[DLM_MLE_BLOCK]),
			atomic_पढ़ो(&dlm->mle_tot_count[DLM_MLE_BLOCK]));

	/*  Mastery: xxx (xxx) */
	out += scnम_लिखो(buf + out, len - out,
			"  Mastery: %d (%d)\n",
			atomic_पढ़ो(&dlm->mle_cur_count[DLM_MLE_MASTER]),
			atomic_पढ़ो(&dlm->mle_tot_count[DLM_MLE_MASTER]));

	/*  Migration: xxx (xxx) */
	out += scnम_लिखो(buf + out, len - out,
			"  Migration: %d (%d)\n",
			atomic_पढ़ो(&dlm->mle_cur_count[DLM_MLE_MIGRATION]),
			atomic_पढ़ो(&dlm->mle_tot_count[DLM_MLE_MIGRATION]));

	/* Lists: Dirty=Empty  Purge=InUse  PendingASTs=Empty  ... */
	out += scnम_लिखो(buf + out, len - out,
			"Lists: Dirty=%s  Purge=%s  PendingASTs=%s  "
			"PendingBASTs=%s\n",
			(list_empty(&dlm->dirty_list) ? "Empty" : "InUse"),
			(list_empty(&dlm->purge_list) ? "Empty" : "InUse"),
			(list_empty(&dlm->pending_asts) ? "Empty" : "InUse"),
			(list_empty(&dlm->pending_basts) ? "Empty" : "InUse"));

	/* Purge Count: xxx  Refs: xxx */
	out += scnम_लिखो(buf + out, len - out,
			"Purge Count: %d  Refs: %d\n", dlm->purge_count,
			kref_पढ़ो(&dlm->dlm_refs));

	/* Dead Node: xxx */
	out += scnम_लिखो(buf + out, len - out,
			"Dead Node: %d\n", dlm->reco.dead_node);

	/* What about DLM_RECO_STATE_FINALIZE? */
	अगर (dlm->reco.state == DLM_RECO_STATE_ACTIVE)
		state = "ACTIVE";
	अन्यथा
		state = "INACTIVE";

	/* Recovery Pid: xxxx  Master: xxx  State: xxxx */
	out += scnम_लिखो(buf + out, len - out,
			"Recovery Pid: %d  Master: %d  State: %s\n",
			task_pid_nr(dlm->dlm_reco_thपढ़ो_task),
			dlm->reco.new_master, state);

	/* Recovery Map: xx xx */
	out += scnम_लिखो(buf + out, len - out, "Recovery Map: ");
	out += stringअगरy_nodemap(dlm->recovery_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += scnम_लिखो(buf + out, len - out, "\n");

	/* Recovery Node State: */
	out += scnम_लिखो(buf + out, len - out, "Recovery Node State:\n");
	list_क्रम_each_entry(node, &dlm->reco.node_data, list) अणु
		चयन (node->state) अणु
		हाल DLM_RECO_NODE_DATA_INIT:
			state = "INIT";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_REQUESTING:
			state = "REQUESTING";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_DEAD:
			state = "DEAD";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_RECEIVING:
			state = "RECEIVING";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_REQUESTED:
			state = "REQUESTED";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_DONE:
			state = "DONE";
			अवरोध;
		हाल DLM_RECO_NODE_DATA_FINALIZE_SENT:
			state = "FINALIZE-SENT";
			अवरोध;
		शेष:
			state = "BAD";
			अवरोध;
		पूर्ण
		out += scnम_लिखो(buf + out, len - out, "\t%u - %s\n",
				node->node_num, state);
	पूर्ण

	spin_unlock(&dlm->spinlock);

	वापस out;
पूर्ण

अटल पूर्णांक debug_state_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_ctxt *dlm = inode->i_निजी;
	अक्षर *buf = शून्य;

	buf = (अक्षर *) get_zeroed_page(GFP_NOFS);
	अगर (!buf)
		जाओ bail;

	i_size_ग_लिखो(inode, debug_state_prपूर्णांक(dlm, buf, PAGE_SIZE - 1));

	file->निजी_data = buf;

	वापस 0;
bail:
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_state_fops = अणु
	.खोलो =		debug_state_खोलो,
	.release =	debug_release,
	.पढ़ो =		debug_पढ़ो,
	.llseek =	generic_file_llseek,
पूर्ण;
/* end  - debug state funcs */

/* files in subroot */
व्योम dlm_debug_init(काष्ठा dlm_ctxt *dlm)
अणु
	/* क्रम dumping dlm_ctxt */
	debugfs_create_file(DLM_DEBUGFS_DLM_STATE, S_IFREG|S_IRUSR,
			    dlm->dlm_debugfs_subroot, dlm, &debug_state_fops);

	/* क्रम dumping lockres */
	debugfs_create_file(DLM_DEBUGFS_LOCKING_STATE, S_IFREG|S_IRUSR,
			    dlm->dlm_debugfs_subroot, dlm, &debug_lockres_fops);

	/* क्रम dumping mles */
	debugfs_create_file(DLM_DEBUGFS_MLE_STATE, S_IFREG|S_IRUSR,
			    dlm->dlm_debugfs_subroot, dlm, &debug_mle_fops);

	/* क्रम dumping lockres on the purge list */
	debugfs_create_file(DLM_DEBUGFS_PURGE_LIST, S_IFREG|S_IRUSR,
			    dlm->dlm_debugfs_subroot, dlm,
			    &debug_purgelist_fops);
पूर्ण

/* subroot - करोमुख्य dir */
व्योम dlm_create_debugfs_subroot(काष्ठा dlm_ctxt *dlm)
अणु
	dlm->dlm_debugfs_subroot = debugfs_create_dir(dlm->name,
						      dlm_debugfs_root);
पूर्ण

व्योम dlm_destroy_debugfs_subroot(काष्ठा dlm_ctxt *dlm)
अणु
	debugfs_हटाओ_recursive(dlm->dlm_debugfs_subroot);
पूर्ण

/* debugfs root */
व्योम dlm_create_debugfs_root(व्योम)
अणु
	dlm_debugfs_root = debugfs_create_dir(DLM_DEBUGFS_सूची, शून्य);
पूर्ण

व्योम dlm_destroy_debugfs_root(व्योम)
अणु
	debugfs_हटाओ(dlm_debugfs_root);
पूर्ण
#पूर्ण_अगर	/* CONFIG_DEBUG_FS */
