<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * stackglue.h
 *
 * Glue to the underlying cluster stack.
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */


#अगर_अघोषित STACKGLUE_H
#घोषणा STACKGLUE_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/dlmस्थिरants.h>

#समावेश "dlm/dlmapi.h"
#समावेश <linux/dlm.h>

/* Needed क्रम plock-related prototypes */
काष्ठा file;
काष्ठा file_lock;

/*
 * dlmस्थिरants.h करोes not have a LOCAL flag.  We hope to हटाओ it
 * some day, but right now we need it.  Let's fake it.  This value is larger
 * than any flag in dlmस्थिरants.h.
 */
#घोषणा DLM_LKF_LOCAL		0x00100000

/*
 * This shaकरोws DLM_LOCKSPACE_LEN in fs/dlm/dlm_पूर्णांकernal.h.  That probably
 * wants to be in a खुला header.
 */
#घोषणा GROUP_NAME_MAX		64

/* This shaकरोws  OCFS2_CLUSTER_NAME_LEN */
#घोषणा CLUSTER_NAME_MAX	16


/*
 * ocfs2_protocol_version changes when ocfs2 करोes something dअगरferent in
 * its पूर्णांकer-node behavior.  See dlmglue.c क्रम more inक्रमmation.
 */
काष्ठा ocfs2_protocol_version अणु
	u8 pv_major;
	u8 pv_minor;
पूर्ण;

/*
 * The dlm_lockstatus काष्ठा includes lvb space, but the dlm_lksb काष्ठा only
 * has a poपूर्णांकer to separately allocated lvb space.  This काष्ठा exists only to
 * include in the lksb जोड़ to make space क्रम a combined dlm_lksb and lvb.
 */
काष्ठा fsdlm_lksb_plus_lvb अणु
	काष्ठा dlm_lksb lksb;
	अक्षर lvb[DLM_LVB_LEN];
पूर्ण;

/*
 * A जोड़ of all lock status काष्ठाures.  We define it here so that the
 * size of the जोड़ is known.  Lock status काष्ठाures are embedded in
 * ocfs2 inodes.
 */
काष्ठा ocfs2_cluster_connection;
काष्ठा ocfs2_dlm_lksb अणु
	 जोड़ अणु
		 काष्ठा dlm_lockstatus lksb_o2dlm;
		 काष्ठा dlm_lksb lksb_fsdlm;
		 काष्ठा fsdlm_lksb_plus_lvb padding;
	 पूर्ण;
	 काष्ठा ocfs2_cluster_connection *lksb_conn;
पूर्ण;

/*
 * The ocfs2_locking_protocol defines the handlers called on ocfs2's behalf.
 */
काष्ठा ocfs2_locking_protocol अणु
	काष्ठा ocfs2_protocol_version lp_max_version;
	व्योम (*lp_lock_ast)(काष्ठा ocfs2_dlm_lksb *lksb);
	व्योम (*lp_blocking_ast)(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक level);
	व्योम (*lp_unlock_ast)(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक error);
पूर्ण;


/*
 * A cluster connection.  Mostly opaque to ocfs2, the connection holds
 * state क्रम the underlying stack.  ocfs2 करोes use cc_version to determine
 * locking compatibility.
 */
काष्ठा ocfs2_cluster_connection अणु
	अक्षर cc_name[GROUP_NAME_MAX + 1];
	पूर्णांक cc_namelen;
	अक्षर cc_cluster_name[CLUSTER_NAME_MAX + 1];
	पूर्णांक cc_cluster_name_len;
	काष्ठा ocfs2_protocol_version cc_version;
	काष्ठा ocfs2_locking_protocol *cc_proto;
	व्योम (*cc_recovery_handler)(पूर्णांक node_num, व्योम *recovery_data);
	व्योम *cc_recovery_data;
	व्योम *cc_lockspace;
	व्योम *cc_निजी;
पूर्ण;

/*
 * Each cluster stack implements the stack operations काष्ठाure.  Not used
 * in the ocfs2 code, the stackglue code translates generic cluster calls
 * पूर्णांकo stack operations.
 */
काष्ठा ocfs2_stack_operations अणु
	/*
	 * The fs code calls ocfs2_cluster_connect() to attach a new
	 * fileप्रणाली to the cluster stack.  The ->connect() op is passed
	 * an ocfs2_cluster_connection with the name and recovery field
	 * filled in.
	 *
	 * The stack must set up any notअगरication mechanisms and create
	 * the fileप्रणाली lockspace in the DLM.  The lockspace should be
	 * stored on cc_lockspace.  Any other inक्रमmation can be stored on
	 * cc_निजी.
	 *
	 * ->connect() must not वापस until it is guaranteed that
	 *
	 *  - Node करोwn notअगरications क्रम the fileप्रणाली will be received
	 *    and passed to conn->cc_recovery_handler().
	 *  - Locking requests क्रम the fileप्रणाली will be processed.
	 */
	पूर्णांक (*connect)(काष्ठा ocfs2_cluster_connection *conn);

	/*
	 * The fs code calls ocfs2_cluster_disconnect() when a fileप्रणाली
	 * no दीर्घer needs cluster services.  All DLM locks have been
	 * dropped, and recovery notअगरication is being ignored by the
	 * fs code.  The stack must disengage from the DLM and disजारी
	 * recovery notअगरication.
	 *
	 * Once ->disconnect() has वापसed, the connection काष्ठाure will
	 * be मुक्तd.  Thus, a stack must not वापस from ->disconnect()
	 * until it will no दीर्घer reference the conn poपूर्णांकer.
	 *
	 * Once this call वापसs, the stack glue will be dropping this
	 * connection's reference on the module.
	 */
	पूर्णांक (*disconnect)(काष्ठा ocfs2_cluster_connection *conn);

	/*
	 * ->this_node() वापसs the cluster's unique identअगरier क्रम the
	 * local node.
	 */
	पूर्णांक (*this_node)(काष्ठा ocfs2_cluster_connection *conn,
			 अचिन्हित पूर्णांक *node);

	/*
	 * Call the underlying dlm lock function.  The ->dlm_lock()
	 * callback should convert the flags and mode as appropriate.
	 *
	 * ast and bast functions are not part of the call because the
	 * stack will likely want to wrap ast and bast calls beक्रमe passing
	 * them to stack->sp_proto.  There is no astarg.  The lksb will
	 * be passed back to the ast and bast functions.  The caller can
	 * use this to find their object.
	 */
	पूर्णांक (*dlm_lock)(काष्ठा ocfs2_cluster_connection *conn,
			पूर्णांक mode,
			काष्ठा ocfs2_dlm_lksb *lksb,
			u32 flags,
			व्योम *name,
			अचिन्हित पूर्णांक namelen);

	/*
	 * Call the underlying dlm unlock function.  The ->dlm_unlock()
	 * function should convert the flags as appropriate.
	 *
	 * The unlock ast is not passed, as the stack will want to wrap
	 * it beक्रमe calling stack->sp_proto->lp_unlock_ast().  There is
	 * no astarg.  The lksb will be passed back to the unlock ast
	 * function.  The caller can use this to find their object.
	 */
	पूर्णांक (*dlm_unlock)(काष्ठा ocfs2_cluster_connection *conn,
			  काष्ठा ocfs2_dlm_lksb *lksb,
			  u32 flags);

	/*
	 * Return the status of the current lock status block.  The fs
	 * code should never dereference the जोड़.  The ->lock_status()
	 * callback pulls out the stack-specअगरic lksb, converts the status
	 * to a proper त्रुटि_सं, and वापसs it.
	 */
	पूर्णांक (*lock_status)(काष्ठा ocfs2_dlm_lksb *lksb);

	/*
	 * Return non-zero अगर the LVB is valid.
	 */
	पूर्णांक (*lvb_valid)(काष्ठा ocfs2_dlm_lksb *lksb);

	/*
	 * Pull the lvb poपूर्णांकer off of the stack-specअगरic lksb.
	 */
	व्योम *(*lock_lvb)(काष्ठा ocfs2_dlm_lksb *lksb);

	/*
	 * Cluster-aware posix locks
	 *
	 * This is शून्य क्रम stacks which करो not support posix locks.
	 */
	पूर्णांक (*plock)(काष्ठा ocfs2_cluster_connection *conn,
		     u64 ino,
		     काष्ठा file *file,
		     पूर्णांक cmd,
		     काष्ठा file_lock *fl);

	/*
	 * This is an optoinal debugging hook.  If provided, the
	 * stack can dump debugging inक्रमmation about this lock.
	 */
	व्योम (*dump_lksb)(काष्ठा ocfs2_dlm_lksb *lksb);
पूर्ण;

/*
 * Each stack plugin must describe itself by रेजिस्टरing a
 * ocfs2_stack_plugin काष्ठाure.  This is only seen by stackglue and the
 * stack driver.
 */
काष्ठा ocfs2_stack_plugin अणु
	अक्षर *sp_name;
	काष्ठा ocfs2_stack_operations *sp_ops;
	काष्ठा module *sp_owner;

	/* These are managed by the stackglue code. */
	काष्ठा list_head sp_list;
	अचिन्हित पूर्णांक sp_count;
	काष्ठा ocfs2_protocol_version sp_max_proto;
पूर्ण;


/* Used by the fileप्रणाली */
पूर्णांक ocfs2_cluster_connect(स्थिर अक्षर *stack_name,
			  स्थिर अक्षर *cluster_name,
			  पूर्णांक cluster_name_len,
			  स्थिर अक्षर *group,
			  पूर्णांक grouplen,
			  काष्ठा ocfs2_locking_protocol *lproto,
			  व्योम (*recovery_handler)(पूर्णांक node_num,
						   व्योम *recovery_data),
			  व्योम *recovery_data,
			  काष्ठा ocfs2_cluster_connection **conn);
/*
 * Used by callers that करोn't store their stack name.  They must ensure
 * all nodes have the same stack.
 */
पूर्णांक ocfs2_cluster_connect_agnostic(स्थिर अक्षर *group,
				   पूर्णांक grouplen,
				   काष्ठा ocfs2_locking_protocol *lproto,
				   व्योम (*recovery_handler)(पूर्णांक node_num,
							    व्योम *recovery_data),
				   व्योम *recovery_data,
				   काष्ठा ocfs2_cluster_connection **conn);
पूर्णांक ocfs2_cluster_disconnect(काष्ठा ocfs2_cluster_connection *conn,
			     पूर्णांक hangup_pending);
व्योम ocfs2_cluster_hangup(स्थिर अक्षर *group, पूर्णांक grouplen);
पूर्णांक ocfs2_cluster_this_node(काष्ठा ocfs2_cluster_connection *conn,
			    अचिन्हित पूर्णांक *node);

काष्ठा ocfs2_lock_res;
पूर्णांक ocfs2_dlm_lock(काष्ठा ocfs2_cluster_connection *conn,
		   पूर्णांक mode,
		   काष्ठा ocfs2_dlm_lksb *lksb,
		   u32 flags,
		   व्योम *name,
		   अचिन्हित पूर्णांक namelen);
पूर्णांक ocfs2_dlm_unlock(काष्ठा ocfs2_cluster_connection *conn,
		     काष्ठा ocfs2_dlm_lksb *lksb,
		     u32 flags);

पूर्णांक ocfs2_dlm_lock_status(काष्ठा ocfs2_dlm_lksb *lksb);
पूर्णांक ocfs2_dlm_lvb_valid(काष्ठा ocfs2_dlm_lksb *lksb);
व्योम *ocfs2_dlm_lvb(काष्ठा ocfs2_dlm_lksb *lksb);
व्योम ocfs2_dlm_dump_lksb(काष्ठा ocfs2_dlm_lksb *lksb);

पूर्णांक ocfs2_stack_supports_plocks(व्योम);
पूर्णांक ocfs2_plock(काष्ठा ocfs2_cluster_connection *conn, u64 ino,
		काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl);

व्योम ocfs2_stack_glue_set_max_proto_version(काष्ठा ocfs2_protocol_version *max_proto);


/* Used by stack plugins */
पूर्णांक ocfs2_stack_glue_रेजिस्टर(काष्ठा ocfs2_stack_plugin *plugin);
व्योम ocfs2_stack_glue_unरेजिस्टर(काष्ठा ocfs2_stack_plugin *plugin);

बाह्य काष्ठा kset *ocfs2_kset;

#पूर्ण_अगर  /* STACKGLUE_H */
