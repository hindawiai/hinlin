<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor auditing function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_AUDIT_H
#घोषणा __AA_AUDIT_H

#समावेश <linux/audit.h>
#समावेश <linux/fs.h>
#समावेश <linux/lsm_audit.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "file.h"
#समावेश "label.h"

बाह्य स्थिर अक्षर *स्थिर audit_mode_names[];
#घोषणा AUDIT_MAX_INDEX 5
क्रमागत audit_mode अणु
	AUDIT_NORMAL,		/* follow normal auditing of accesses */
	AUDIT_QUIET_DENIED,	/* quiet all denied access messages */
	AUDIT_QUIET,		/* quiet all messages */
	AUDIT_NOQUIET,		/* करो not quiet audit messages */
	AUDIT_ALL		/* audit all accesses */
पूर्ण;

क्रमागत audit_type अणु
	AUDIT_APPARMOR_AUDIT,
	AUDIT_APPARMOR_ALLOWED,
	AUDIT_APPARMOR_DENIED,
	AUDIT_APPARMOR_HINT,
	AUDIT_APPARMOR_STATUS,
	AUDIT_APPARMOR_ERROR,
	AUDIT_APPARMOR_KILL,
	AUDIT_APPARMOR_AUTO
पूर्ण;

#घोषणा OP_शून्य शून्य

#घोषणा OP_SYSCTL "sysctl"
#घोषणा OP_CAPABLE "capable"

#घोषणा OP_UNLINK "unlink"
#घोषणा OP_MKसूची "mkdir"
#घोषणा OP_RMसूची "rmdir"
#घोषणा OP_MKNOD "mknod"
#घोषणा OP_TRUNC "truncate"
#घोषणा OP_LINK "link"
#घोषणा OP_SYMLINK "symlink"
#घोषणा OP_RENAME_SRC "rename_src"
#घोषणा OP_RENAME_DEST "rename_dest"
#घोषणा OP_CHMOD "chmod"
#घोषणा OP_CHOWN "chown"
#घोषणा OP_GETATTR "getattr"
#घोषणा OP_OPEN "open"

#घोषणा OP_FRECEIVE "file_receive"
#घोषणा OP_FPERM "file_perm"
#घोषणा OP_FLOCK "file_lock"
#घोषणा OP_FMMAP "file_mmap"
#घोषणा OP_FMPROT "file_mprotect"
#घोषणा OP_INHERIT "file_inherit"

#घोषणा OP_PIVOTROOT "pivotroot"
#घोषणा OP_MOUNT "mount"
#घोषणा OP_UMOUNT "umount"

#घोषणा OP_CREATE "create"
#घोषणा OP_POST_CREATE "post_create"
#घोषणा OP_BIND "bind"
#घोषणा OP_CONNECT "connect"
#घोषणा OP_LISTEN "listen"
#घोषणा OP_ACCEPT "accept"
#घोषणा OP_SENDMSG "sendmsg"
#घोषणा OP_RECVMSG "recvmsg"
#घोषणा OP_GETSOCKNAME "getsockname"
#घोषणा OP_GETPEERNAME "getpeername"
#घोषणा OP_GETSOCKOPT "getsockopt"
#घोषणा OP_SETSOCKOPT "setsockopt"
#घोषणा OP_SHUTDOWN "socket_shutdown"

#घोषणा OP_PTRACE "ptrace"
#घोषणा OP_SIGNAL "signal"

#घोषणा OP_EXEC "exec"

#घोषणा OP_CHANGE_HAT "change_hat"
#घोषणा OP_CHANGE_PROखाता "change_profile"
#घोषणा OP_CHANGE_ONEXEC "change_onexec"
#घोषणा OP_STACK "stack"
#घोषणा OP_STACK_ONEXEC "stack_onexec"

#घोषणा OP_SETPROCATTR "setprocattr"
#घोषणा OP_SETRLIMIT "setrlimit"

#घोषणा OP_PROF_REPL "profile_replace"
#घोषणा OP_PROF_LOAD "profile_load"
#घोषणा OP_PROF_RM "profile_remove"


काष्ठा apparmor_audit_data अणु
	पूर्णांक error;
	पूर्णांक type;
	स्थिर अक्षर *op;
	काष्ठा aa_label *label;
	स्थिर अक्षर *name;
	स्थिर अक्षर *info;
	u32 request;
	u32 denied;
	जोड़ अणु
		/* these entries require a custom callback fn */
		काष्ठा अणु
			काष्ठा aa_label *peer;
			जोड़ अणु
				काष्ठा अणु
					स्थिर अक्षर *target;
					kuid_t ouid;
				पूर्ण fs;
				काष्ठा अणु
					पूर्णांक rlim;
					अचिन्हित दीर्घ max;
				पूर्ण rlim;
				काष्ठा अणु
					पूर्णांक संकेत;
					पूर्णांक unmappedsig;
				पूर्ण;
				काष्ठा अणु
					पूर्णांक type, protocol;
					काष्ठा sock *peer_sk;
					व्योम *addr;
					पूर्णांक addrlen;
				पूर्ण net;
			पूर्ण;
		पूर्ण;
		काष्ठा अणु
			काष्ठा aa_profile *profile;
			स्थिर अक्षर *ns;
			दीर्घ pos;
		पूर्ण अगरace;
		काष्ठा अणु
			स्थिर अक्षर *src_name;
			स्थिर अक्षर *type;
			स्थिर अक्षर *trans;
			स्थिर अक्षर *data;
			अचिन्हित दीर्घ flags;
		पूर्ण mnt;
	पूर्ण;
पूर्ण;

/* macros क्रम dealing with  apparmor_audit_data काष्ठाure */
#घोषणा aad(SA) ((SA)->apparmor_audit_data)
#घोषणा DEFINE_AUDIT_DATA(NAME, T, X)					\
	/* TODO: cleanup audit init so we करोn't need _aad = अणु0,पूर्ण */	\
	काष्ठा apparmor_audit_data NAME ## _aad = अणु .op = (X), पूर्ण;	\
	काष्ठा common_audit_data NAME =					\
	अणु								\
	.type = (T),							\
	.u.tsk = शून्य,							\
	पूर्ण;								\
	NAME.apparmor_audit_data = &(NAME ## _aad)

व्योम aa_audit_msg(पूर्णांक type, काष्ठा common_audit_data *sa,
		  व्योम (*cb) (काष्ठा audit_buffer *, व्योम *));
पूर्णांक aa_audit(पूर्णांक type, काष्ठा aa_profile *profile, काष्ठा common_audit_data *sa,
	     व्योम (*cb) (काष्ठा audit_buffer *, व्योम *));

#घोषणा aa_audit_error(ERROR, SA, CB)				\
(अणु								\
	aad((SA))->error = (ERROR);				\
	aa_audit_msg(AUDIT_APPARMOR_ERROR, (SA), (CB));		\
	aad((SA))->error;					\
पूर्ण)


अटल अंतरभूत पूर्णांक complain_error(पूर्णांक error)
अणु
	अगर (error == -EPERM || error == -EACCES)
		वापस 0;
	वापस error;
पूर्ण

व्योम aa_audit_rule_मुक्त(व्योम *vrule);
पूर्णांक aa_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **vrule);
पूर्णांक aa_audit_rule_known(काष्ठा audit_krule *rule);
पूर्णांक aa_audit_rule_match(u32 sid, u32 field, u32 op, व्योम *vrule);

#पूर्ण_अगर /* __AA_AUDIT_H */
