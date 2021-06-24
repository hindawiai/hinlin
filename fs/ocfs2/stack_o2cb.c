<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * stack_o2cb.c
 *
 * Code which पूर्णांकerfaces ocfs2 with the o2cb stack.
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

/* Needed क्रम AOP_TRUNCATED_PAGE in mlog_त्रुटि_सं() */
#समावेश <linux/fs.h>

#समावेश "cluster/masklog.h"
#समावेश "cluster/nodemanager.h"
#समावेश "cluster/heartbeat.h"
#समावेश "cluster/tcp.h"

#समावेश "stackglue.h"

काष्ठा o2dlm_निजी अणु
	काष्ठा dlm_eviction_cb op_eviction_cb;
पूर्ण;

अटल काष्ठा ocfs2_stack_plugin o2cb_stack;

/* These should be identical */
#अगर (DLM_LOCK_IV != LKM_IVMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_NL != LKM_NLMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_CR != LKM_CRMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_CW != LKM_CWMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_PR != LKM_PRMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_PW != LKM_PWMODE)
# error Lock modes करो not match
#पूर्ण_अगर
#अगर (DLM_LOCK_EX != LKM_EXMODE)
# error Lock modes करो not match
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक mode_to_o2dlm(पूर्णांक mode)
अणु
	BUG_ON(mode > LKM_MAXMODE);

	वापस mode;
पूर्ण

अटल पूर्णांक flags_to_o2dlm(u32 flags)
अणु
	पूर्णांक o2dlm_flags = 0;

	अगर (flags & DLM_LKF_NOQUEUE)
		o2dlm_flags |= LKM_NOQUEUE;
	अगर (flags & DLM_LKF_CANCEL)
		o2dlm_flags |= LKM_CANCEL;
	अगर (flags & DLM_LKF_CONVERT)
		o2dlm_flags |= LKM_CONVERT;
	अगर (flags & DLM_LKF_VALBLK)
		o2dlm_flags |= LKM_VALBLK;
	अगर (flags & DLM_LKF_IVVALBLK)
		o2dlm_flags |= LKM_INVVALBLK;
	अगर (flags & DLM_LKF_ORPHAN)
		o2dlm_flags |= LKM_ORPHAN;
	अगर (flags & DLM_LKF_FORCEUNLOCK)
		o2dlm_flags |= LKM_FORCE;
	अगर (flags & DLM_LKF_TIMEOUT)
		o2dlm_flags |= LKM_TIMEOUT;
	अगर (flags & DLM_LKF_LOCAL)
		o2dlm_flags |= LKM_LOCAL;

	वापस o2dlm_flags;
पूर्ण

/*
 * Map an o2dlm status to standard त्रुटि_सं values.
 *
 * o2dlm only uses a handful of these, and वापसs even fewer to the
 * caller. Still, we try to assign sane values to each error.
 *
 * The following value pairs have special meanings to dlmglue, thus
 * the right hand side needs to stay unique - never duplicate the
 * mapping अन्यथाwhere in the table!
 *
 * DLM_NORMAL:		0
 * DLM_NOTQUEUED:	-EAGAIN
 * DLM_CANCELGRANT:	-EBUSY
 * DLM_CANCEL:		-DLM_ECANCEL
 */
/* Keep in sync with dlmapi.h */
अटल पूर्णांक status_map[] = अणु
	[DLM_NORMAL]			= 0,		/* Success */
	[DLM_GRANTED]			= -EINVAL,
	[DLM_DENIED]			= -EACCES,
	[DLM_DENIED_NOLOCKS]		= -EACCES,
	[DLM_WORKING]			= -EACCES,
	[DLM_BLOCKED]			= -EINVAL,
	[DLM_BLOCKED_ORPHAN]		= -EINVAL,
	[DLM_DENIED_GRACE_PERIOD]	= -EACCES,
	[DLM_SYSERR]			= -ENOMEM,	/* It is what it is */
	[DLM_NOSUPPORT]			= -EPROTO,
	[DLM_CANCELGRANT]		= -EBUSY,	/* Cancel after grant */
	[DLM_IVLOCKID]			= -EINVAL,
	[DLM_SYNC]			= -EINVAL,
	[DLM_BADTYPE]			= -EINVAL,
	[DLM_BADRESOURCE]		= -EINVAL,
	[DLM_MAXHANDLES]		= -ENOMEM,
	[DLM_NOCLINFO]			= -EINVAL,
	[DLM_NOLOCKMGR]			= -EINVAL,
	[DLM_NOPURGED]			= -EINVAL,
	[DLM_BADARGS]			= -EINVAL,
	[DLM_VOID]			= -EINVAL,
	[DLM_NOTQUEUED]			= -EAGAIN,	/* Trylock failed */
	[DLM_IVBUFLEN]			= -EINVAL,
	[DLM_CVTUNGRANT]		= -EPERM,
	[DLM_BADPARAM]			= -EINVAL,
	[DLM_VALNOTVALID]		= -EINVAL,
	[DLM_REJECTED]			= -EPERM,
	[DLM_ABORT]			= -EINVAL,
	[DLM_CANCEL]			= -DLM_ECANCEL,	/* Successful cancel */
	[DLM_IVRESHANDLE]		= -EINVAL,
	[DLM_DEADLOCK]			= -EDEADLK,
	[DLM_DENIED_NOASTS]		= -EINVAL,
	[DLM_FORWARD]			= -EINVAL,
	[DLM_TIMEOUT]			= -ETIMEDOUT,
	[DLM_IVGROUPID]			= -EINVAL,
	[DLM_VERS_CONFLICT]		= -EOPNOTSUPP,
	[DLM_BAD_DEVICE_PATH]		= -ENOENT,
	[DLM_NO_DEVICE_PERMISSION]	= -EPERM,
	[DLM_NO_CONTROL_DEVICE]		= -ENOENT,
	[DLM_RECOVERING]		= -ENOTCONN,
	[DLM_MIGRATING]			= -ERESTART,
	[DLM_MAXSTATS]			= -EINVAL,
पूर्ण;

अटल पूर्णांक dlm_status_to_त्रुटि_सं(क्रमागत dlm_status status)
अणु
	BUG_ON(status < 0 || status >= ARRAY_SIZE(status_map));

	वापस status_map[status];
पूर्ण

अटल व्योम o2dlm_lock_ast_wrapper(व्योम *astarg)
अणु
	काष्ठा ocfs2_dlm_lksb *lksb = astarg;

	lksb->lksb_conn->cc_proto->lp_lock_ast(lksb);
पूर्ण

अटल व्योम o2dlm_blocking_ast_wrapper(व्योम *astarg, पूर्णांक level)
अणु
	काष्ठा ocfs2_dlm_lksb *lksb = astarg;

	lksb->lksb_conn->cc_proto->lp_blocking_ast(lksb, level);
पूर्ण

अटल व्योम o2dlm_unlock_ast_wrapper(व्योम *astarg, क्रमागत dlm_status status)
अणु
	काष्ठा ocfs2_dlm_lksb *lksb = astarg;
	पूर्णांक error = dlm_status_to_त्रुटि_सं(status);

	/*
	 * In o2dlm, you can get both the lock_ast() क्रम the lock being
	 * granted and the unlock_ast() क्रम the CANCEL failing.  A
	 * successful cancel sends DLM_NORMAL here.  If the
	 * lock grant happened beक्रमe the cancel arrived, you get
	 * DLM_CANCELGRANT.
	 *
	 * There's no need क्रम the द्विगुन-ast.  If we see DLM_CANCELGRANT,
	 * we just ignore it.  We expect the lock_ast() to handle the
	 * granted lock.
	 */
	अगर (status == DLM_CANCELGRANT)
		वापस;

	lksb->lksb_conn->cc_proto->lp_unlock_ast(lksb, error);
पूर्ण

अटल पूर्णांक o2cb_dlm_lock(काष्ठा ocfs2_cluster_connection *conn,
			 पूर्णांक mode,
			 काष्ठा ocfs2_dlm_lksb *lksb,
			 u32 flags,
			 व्योम *name,
			 अचिन्हित पूर्णांक namelen)
अणु
	क्रमागत dlm_status status;
	पूर्णांक o2dlm_mode = mode_to_o2dlm(mode);
	पूर्णांक o2dlm_flags = flags_to_o2dlm(flags);
	पूर्णांक ret;

	status = dlmlock(conn->cc_lockspace, o2dlm_mode, &lksb->lksb_o2dlm,
			 o2dlm_flags, name, namelen,
			 o2dlm_lock_ast_wrapper, lksb,
			 o2dlm_blocking_ast_wrapper);
	ret = dlm_status_to_त्रुटि_सं(status);
	वापस ret;
पूर्ण

अटल पूर्णांक o2cb_dlm_unlock(काष्ठा ocfs2_cluster_connection *conn,
			   काष्ठा ocfs2_dlm_lksb *lksb,
			   u32 flags)
अणु
	क्रमागत dlm_status status;
	पूर्णांक o2dlm_flags = flags_to_o2dlm(flags);
	पूर्णांक ret;

	status = dlmunlock(conn->cc_lockspace, &lksb->lksb_o2dlm,
			   o2dlm_flags, o2dlm_unlock_ast_wrapper, lksb);
	ret = dlm_status_to_त्रुटि_सं(status);
	वापस ret;
पूर्ण

अटल पूर्णांक o2cb_dlm_lock_status(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस dlm_status_to_त्रुटि_सं(lksb->lksb_o2dlm.status);
पूर्ण

/*
 * o2dlm aways has a "valid" LVB. If the dlm loses track of the LVB
 * contents, it will zero out the LVB.  Thus the caller can always trust
 * the contents.
 */
अटल पूर्णांक o2cb_dlm_lvb_valid(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस 1;
पूर्ण

अटल व्योम *o2cb_dlm_lvb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस (व्योम *)(lksb->lksb_o2dlm.lvb);
पूर्ण

अटल व्योम o2cb_dump_lksb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	dlm_prपूर्णांक_one_lock(lksb->lksb_o2dlm.lockid);
पूर्ण

/*
 * Check अगर this node is heartbeating and is connected to all other
 * heartbeating nodes.
 */
अटल पूर्णांक o2cb_cluster_check(व्योम)
अणु
	u8 node_num;
	पूर्णांक i;
	अचिन्हित दीर्घ hbmap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ neपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];

	node_num = o2nm_this_node();
	अगर (node_num == O2NM_MAX_NODES) अणु
		prपूर्णांकk(KERN_ERR "o2cb: This node has not been configured.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * o2dlm expects o2net sockets to be created. If not, then
	 * dlm_join_करोमुख्य() fails with a stack of errors which are both cryptic
	 * and incomplete. The idea here is to detect upfront whether we have
	 * managed to connect to all nodes or not. If not, then list the nodes
	 * to allow the user to check the configuration (incorrect IP, firewall,
	 * etc.) Yes, this is racy. But its not the end of the world.
	 */
#घोषणा	O2CB_MAP_STABILIZE_COUNT	60
	क्रम (i = 0; i < O2CB_MAP_STABILIZE_COUNT; ++i) अणु
		o2hb_fill_node_map(hbmap, माप(hbmap));
		अगर (!test_bit(node_num, hbmap)) अणु
			prपूर्णांकk(KERN_ERR "o2cb: %s heartbeat has not been "
			       "started.\n", (o2hb_global_heartbeat_active() ?
					      "Global" : "Local"));
			वापस -EINVAL;
		पूर्ण
		o2net_fill_node_map(neपंचांगap, माप(neपंचांगap));
		/* Force set the current node to allow easy compare */
		set_bit(node_num, neपंचांगap);
		अगर (!स_भेद(hbmap, neपंचांगap, माप(hbmap)))
			वापस 0;
		अगर (i < O2CB_MAP_STABILIZE_COUNT - 1)
			msleep(1000);
	पूर्ण

	prपूर्णांकk(KERN_ERR "o2cb: This node could not connect to nodes:");
	i = -1;
	जबतक ((i = find_next_bit(hbmap, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) अणु
		अगर (!test_bit(i, neपंचांगap))
			prपूर्णांकk(" %u", i);
	पूर्ण
	prपूर्णांकk(".\n");

	वापस -ENOTCONN;
पूर्ण

/*
 * Called from the dlm when it's about to evict a node. This is how the
 * classic stack संकेतs node death.
 */
अटल व्योम o2dlm_eviction_cb(पूर्णांक node_num, व्योम *data)
अणु
	काष्ठा ocfs2_cluster_connection *conn = data;

	prपूर्णांकk(KERN_NOTICE "o2cb: o2dlm has evicted node %d from domain %.*s\n",
	       node_num, conn->cc_namelen, conn->cc_name);

	conn->cc_recovery_handler(node_num, conn->cc_recovery_data);
पूर्ण

अटल पूर्णांक o2cb_cluster_connect(काष्ठा ocfs2_cluster_connection *conn)
अणु
	पूर्णांक rc = 0;
	u32 dlm_key;
	काष्ठा dlm_ctxt *dlm;
	काष्ठा o2dlm_निजी *priv;
	काष्ठा dlm_protocol_version fs_version;

	BUG_ON(conn == शून्य);
	BUG_ON(conn->cc_proto == शून्य);

	/* Ensure cluster stack is up and all nodes are connected */
	rc = o2cb_cluster_check();
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "o2cb: Cluster check failed. Fix errors "
		       "before retrying.\n");
		जाओ out;
	पूर्ण

	priv = kzalloc(माप(काष्ठा o2dlm_निजी), GFP_KERNEL);
	अगर (!priv) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* This just fills the काष्ठाure in.  It is safe to pass conn. */
	dlm_setup_eviction_cb(&priv->op_eviction_cb, o2dlm_eviction_cb,
			      conn);

	conn->cc_निजी = priv;

	/* used by the dlm code to make message headers unique, each
	 * node in this करोमुख्य must agree on this. */
	dlm_key = crc32_le(0, conn->cc_name, conn->cc_namelen);
	fs_version.pv_major = conn->cc_version.pv_major;
	fs_version.pv_minor = conn->cc_version.pv_minor;

	dlm = dlm_रेजिस्टर_करोमुख्य(conn->cc_name, dlm_key, &fs_version);
	अगर (IS_ERR(dlm)) अणु
		rc = PTR_ERR(dlm);
		mlog_त्रुटि_सं(rc);
		जाओ out_मुक्त;
	पूर्ण

	conn->cc_version.pv_major = fs_version.pv_major;
	conn->cc_version.pv_minor = fs_version.pv_minor;
	conn->cc_lockspace = dlm;

	dlm_रेजिस्टर_eviction_cb(dlm, &priv->op_eviction_cb);

out_मुक्त:
	अगर (rc)
		kमुक्त(conn->cc_निजी);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक o2cb_cluster_disconnect(काष्ठा ocfs2_cluster_connection *conn)
अणु
	काष्ठा dlm_ctxt *dlm = conn->cc_lockspace;
	काष्ठा o2dlm_निजी *priv = conn->cc_निजी;

	dlm_unरेजिस्टर_eviction_cb(&priv->op_eviction_cb);
	conn->cc_निजी = शून्य;
	kमुक्त(priv);

	dlm_unरेजिस्टर_करोमुख्य(dlm);
	conn->cc_lockspace = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक o2cb_cluster_this_node(काष्ठा ocfs2_cluster_connection *conn,
				  अचिन्हित पूर्णांक *node)
अणु
	पूर्णांक node_num;

	node_num = o2nm_this_node();
	अगर (node_num == O2NM_INVALID_NODE_NUM)
		वापस -ENOENT;

	अगर (node_num >= O2NM_MAX_NODES)
		वापस -EOVERFLOW;

	*node = node_num;
	वापस 0;
पूर्ण

अटल काष्ठा ocfs2_stack_operations o2cb_stack_ops = अणु
	.connect	= o2cb_cluster_connect,
	.disconnect	= o2cb_cluster_disconnect,
	.this_node	= o2cb_cluster_this_node,
	.dlm_lock	= o2cb_dlm_lock,
	.dlm_unlock	= o2cb_dlm_unlock,
	.lock_status	= o2cb_dlm_lock_status,
	.lvb_valid	= o2cb_dlm_lvb_valid,
	.lock_lvb	= o2cb_dlm_lvb,
	.dump_lksb	= o2cb_dump_lksb,
पूर्ण;

अटल काष्ठा ocfs2_stack_plugin o2cb_stack = अणु
	.sp_name	= "o2cb",
	.sp_ops		= &o2cb_stack_ops,
	.sp_owner	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init o2cb_stack_init(व्योम)
अणु
	वापस ocfs2_stack_glue_रेजिस्टर(&o2cb_stack);
पूर्ण

अटल व्योम __निकास o2cb_stack_निकास(व्योम)
अणु
	ocfs2_stack_glue_unरेजिस्टर(&o2cb_stack);
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_DESCRIPTION("ocfs2 driver for the classic o2cb stack");
MODULE_LICENSE("GPL");
module_init(o2cb_stack_init);
module_निकास(o2cb_stack_निकास);
