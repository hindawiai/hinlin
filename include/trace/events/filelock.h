<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Events क्रम fileप्रणाली locks
 *
 * Copyright 2013 Jeff Layton <jlayton@poochiereds.net>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM filelock

#अगर !defined(_TRACE_खाताLOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_खाताLOCK_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/kdev_t.h>

#घोषणा show_fl_flags(val)						\
	__prपूर्णांक_flags(val, "|", 					\
		अणु FL_POSIX,		"FL_POSIX" पूर्ण,			\
		अणु FL_FLOCK,		"FL_FLOCK" पूर्ण,			\
		अणु FL_DELEG,		"FL_DELEG" पूर्ण,			\
		अणु FL_ACCESS,		"FL_ACCESS" पूर्ण,			\
		अणु FL_EXISTS,		"FL_EXISTS" पूर्ण,			\
		अणु FL_LEASE,		"FL_LEASE" पूर्ण,			\
		अणु FL_CLOSE,		"FL_CLOSE" पूर्ण,			\
		अणु FL_SLEEP,		"FL_SLEEP" पूर्ण,			\
		अणु FL_DOWNGRADE_PENDING,	"FL_DOWNGRADE_PENDING" पूर्ण,	\
		अणु FL_UNLOCK_PENDING,	"FL_UNLOCK_PENDING" पूर्ण,		\
		अणु FL_OFDLCK,		"FL_OFDLCK" पूर्ण)

#घोषणा show_fl_type(val)				\
	__prपूर्णांक_symbolic(val,				\
			अणु F_RDLCK, "F_RDLCK" पूर्ण,		\
			अणु F_WRLCK, "F_WRLCK" पूर्ण,		\
			अणु F_UNLCK, "F_UNLCK" पूर्ण)

TRACE_EVENT(locks_get_lock_context,
	TP_PROTO(काष्ठा inode *inode, पूर्णांक type, काष्ठा file_lock_context *ctx),

	TP_ARGS(inode, type, ctx),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, i_ino)
		__field(dev_t, s_dev)
		__field(अचिन्हित अक्षर, type)
		__field(काष्ठा file_lock_context *, ctx)
	),

	TP_fast_assign(
		__entry->s_dev = inode->i_sb->s_dev;
		__entry->i_ino = inode->i_ino;
		__entry->type = type;
		__entry->ctx = ctx;
	),

	TP_prपूर्णांकk("dev=0x%x:0x%x ino=0x%lx type=%s ctx=%p",
		  MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
		  __entry->i_ino, show_fl_type(__entry->type), __entry->ctx)
);

DECLARE_EVENT_CLASS(filelock_lock,
	TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl, पूर्णांक ret),

	TP_ARGS(inode, fl, ret),

	TP_STRUCT__entry(
		__field(काष्ठा file_lock *, fl)
		__field(अचिन्हित दीर्घ, i_ino)
		__field(dev_t, s_dev)
		__field(काष्ठा file_lock *, fl_blocker)
		__field(fl_owner_t, fl_owner)
		__field(अचिन्हित पूर्णांक, fl_pid)
		__field(अचिन्हित पूर्णांक, fl_flags)
		__field(अचिन्हित अक्षर, fl_type)
		__field(loff_t, fl_start)
		__field(loff_t, fl_end)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->fl = fl ? fl : शून्य;
		__entry->s_dev = inode->i_sb->s_dev;
		__entry->i_ino = inode->i_ino;
		__entry->fl_blocker = fl ? fl->fl_blocker : शून्य;
		__entry->fl_owner = fl ? fl->fl_owner : शून्य;
		__entry->fl_pid = fl ? fl->fl_pid : 0;
		__entry->fl_flags = fl ? fl->fl_flags : 0;
		__entry->fl_type = fl ? fl->fl_type : 0;
		__entry->fl_start = fl ? fl->fl_start : 0;
		__entry->fl_end = fl ? fl->fl_end : 0;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("fl=%p dev=0x%x:0x%x ino=0x%lx fl_blocker=%p fl_owner=%p fl_pid=%u fl_flags=%s fl_type=%s fl_start=%lld fl_end=%lld ret=%d",
		__entry->fl, MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
		__entry->i_ino, __entry->fl_blocker, __entry->fl_owner,
		__entry->fl_pid, show_fl_flags(__entry->fl_flags),
		show_fl_type(__entry->fl_type),
		__entry->fl_start, __entry->fl_end, __entry->ret)
);

DEFINE_EVENT(filelock_lock, posix_lock_inode,
		TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl, पूर्णांक ret),
		TP_ARGS(inode, fl, ret));

DEFINE_EVENT(filelock_lock, fcntl_setlk,
		TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl, पूर्णांक ret),
		TP_ARGS(inode, fl, ret));

DEFINE_EVENT(filelock_lock, locks_हटाओ_posix,
		TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl, पूर्णांक ret),
		TP_ARGS(inode, fl, ret));

DEFINE_EVENT(filelock_lock, flock_lock_inode,
		TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl, पूर्णांक ret),
		TP_ARGS(inode, fl, ret));

DECLARE_EVENT_CLASS(filelock_lease,
	TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),

	TP_ARGS(inode, fl),

	TP_STRUCT__entry(
		__field(काष्ठा file_lock *, fl)
		__field(अचिन्हित दीर्घ, i_ino)
		__field(dev_t, s_dev)
		__field(काष्ठा file_lock *, fl_blocker)
		__field(fl_owner_t, fl_owner)
		__field(अचिन्हित पूर्णांक, fl_flags)
		__field(अचिन्हित अक्षर, fl_type)
		__field(अचिन्हित दीर्घ, fl_अवरोध_समय)
		__field(अचिन्हित दीर्घ, fl_करोwngrade_समय)
	),

	TP_fast_assign(
		__entry->fl = fl ? fl : शून्य;
		__entry->s_dev = inode->i_sb->s_dev;
		__entry->i_ino = inode->i_ino;
		__entry->fl_blocker = fl ? fl->fl_blocker : शून्य;
		__entry->fl_owner = fl ? fl->fl_owner : शून्य;
		__entry->fl_flags = fl ? fl->fl_flags : 0;
		__entry->fl_type = fl ? fl->fl_type : 0;
		__entry->fl_अवरोध_समय = fl ? fl->fl_अवरोध_समय : 0;
		__entry->fl_करोwngrade_समय = fl ? fl->fl_करोwngrade_समय : 0;
	),

	TP_prपूर्णांकk("fl=%p dev=0x%x:0x%x ino=0x%lx fl_blocker=%p fl_owner=%p fl_flags=%s fl_type=%s fl_break_time=%lu fl_downgrade_time=%lu",
		__entry->fl, MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
		__entry->i_ino, __entry->fl_blocker, __entry->fl_owner,
		show_fl_flags(__entry->fl_flags),
		show_fl_type(__entry->fl_type),
		__entry->fl_अवरोध_समय, __entry->fl_करोwngrade_समय)
);

DEFINE_EVENT(filelock_lease, अवरोध_lease_noblock, TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),
		TP_ARGS(inode, fl));

DEFINE_EVENT(filelock_lease, अवरोध_lease_block, TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),
		TP_ARGS(inode, fl));

DEFINE_EVENT(filelock_lease, अवरोध_lease_unblock, TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),
		TP_ARGS(inode, fl));

DEFINE_EVENT(filelock_lease, generic_delete_lease, TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),
		TP_ARGS(inode, fl));

DEFINE_EVENT(filelock_lease, समय_out_leases, TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),
		TP_ARGS(inode, fl));

TRACE_EVENT(generic_add_lease,
	TP_PROTO(काष्ठा inode *inode, काष्ठा file_lock *fl),

	TP_ARGS(inode, fl),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, i_ino)
		__field(पूर्णांक, wcount)
		__field(पूर्णांक, rcount)
		__field(पूर्णांक, icount)
		__field(dev_t, s_dev)
		__field(fl_owner_t, fl_owner)
		__field(अचिन्हित पूर्णांक, fl_flags)
		__field(अचिन्हित अक्षर, fl_type)
	),

	TP_fast_assign(
		__entry->s_dev = inode->i_sb->s_dev;
		__entry->i_ino = inode->i_ino;
		__entry->wcount = atomic_पढ़ो(&inode->i_ग_लिखोcount);
		__entry->rcount = atomic_पढ़ो(&inode->i_पढ़ोcount);
		__entry->icount = atomic_पढ़ो(&inode->i_count);
		__entry->fl_owner = fl->fl_owner;
		__entry->fl_flags = fl->fl_flags;
		__entry->fl_type = fl->fl_type;
	),

	TP_prपूर्णांकk("dev=0x%x:0x%x ino=0x%lx wcount=%d rcount=%d icount=%d fl_owner=%p fl_flags=%s fl_type=%s",
		MAJOR(__entry->s_dev), MINOR(__entry->s_dev),
		__entry->i_ino, __entry->wcount, __entry->rcount,
		__entry->icount, __entry->fl_owner,
		show_fl_flags(__entry->fl_flags),
		show_fl_type(__entry->fl_type))
);

TRACE_EVENT(leases_conflict,
	TP_PROTO(bool conflict, काष्ठा file_lock *lease, काष्ठा file_lock *अवरोधer),

	TP_ARGS(conflict, lease, अवरोधer),

	TP_STRUCT__entry(
		__field(व्योम *, lease)
		__field(व्योम *, अवरोधer)
		__field(अचिन्हित पूर्णांक, l_fl_flags)
		__field(अचिन्हित पूर्णांक, b_fl_flags)
		__field(अचिन्हित अक्षर, l_fl_type)
		__field(अचिन्हित अक्षर, b_fl_type)
		__field(bool, conflict)
	),

	TP_fast_assign(
		__entry->lease = lease;
		__entry->l_fl_flags = lease->fl_flags;
		__entry->l_fl_type = lease->fl_type;
		__entry->अवरोधer = अवरोधer;
		__entry->b_fl_flags = अवरोधer->fl_flags;
		__entry->b_fl_type = अवरोधer->fl_type;
		__entry->conflict = conflict;
	),

	TP_prपूर्णांकk("conflict %d: lease=%p fl_flags=%s fl_type=%s; breaker=%p fl_flags=%s fl_type=%s",
		__entry->conflict,
		__entry->lease,
		show_fl_flags(__entry->l_fl_flags),
		show_fl_type(__entry->l_fl_type),
		__entry->अवरोधer,
		show_fl_flags(__entry->b_fl_flags),
		show_fl_type(__entry->b_fl_type))
);

#पूर्ण_अगर /* _TRACE_खाताLOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
