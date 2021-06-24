<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Copyright (C) 2018, Microsoft Corporation.
 *
 *   Author(s): Steve French <stfrench@microsoft.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cअगरs

#अगर !defined(_CIFS_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _CIFS_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Please use this 3-part article as a reference क्रम writing new tracepoपूर्णांकs:
 * https://lwn.net/Articles/379903/
 */

/* For logging errors in पढ़ो or ग_लिखो */
DECLARE_EVENT_CLASS(smb3_rw_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u64	offset,
		__u32	len,
		पूर्णांक	rc),
	TP_ARGS(xid, fid, tid, sesid, offset, len, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u64, offset)
		__field(__u32, len)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->offset = offset;
		__entry->len = len;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("\txid=%u sid=0x%llx tid=0x%x fid=0x%llx offset=0x%llx len=0x%x rc=%d",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->offset, __entry->len, __entry->rc)
)

#घोषणा DEFINE_SMB3_RW_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_rw_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	offset,			\
		__u32	len,			\
		पूर्णांक	rc),			\
	TP_ARGS(xid, fid, tid, sesid, offset, len, rc))

DEFINE_SMB3_RW_ERR_EVENT(ग_लिखो_err);
DEFINE_SMB3_RW_ERR_EVENT(पढ़ो_err);
DEFINE_SMB3_RW_ERR_EVENT(query_dir_err);
DEFINE_SMB3_RW_ERR_EVENT(zero_err);
DEFINE_SMB3_RW_ERR_EVENT(falloc_err);


/* For logging successful पढ़ो or ग_लिखो */
DECLARE_EVENT_CLASS(smb3_rw_करोne_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u64	offset,
		__u32	len),
	TP_ARGS(xid, fid, tid, sesid, offset, len),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u64, offset)
		__field(__u32, len)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->offset = offset;
		__entry->len = len;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x fid=0x%llx offset=0x%llx len=0x%x",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->offset, __entry->len)
)

#घोषणा DEFINE_SMB3_RW_DONE_EVENT(name)         \
DEFINE_EVENT(smb3_rw_करोne_class, smb3_##name,   \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	offset,			\
		__u32	len),			\
	TP_ARGS(xid, fid, tid, sesid, offset, len))

DEFINE_SMB3_RW_DONE_EVENT(ग_लिखो_enter);
DEFINE_SMB3_RW_DONE_EVENT(पढ़ो_enter);
DEFINE_SMB3_RW_DONE_EVENT(query_dir_enter);
DEFINE_SMB3_RW_DONE_EVENT(zero_enter);
DEFINE_SMB3_RW_DONE_EVENT(falloc_enter);
DEFINE_SMB3_RW_DONE_EVENT(ग_लिखो_करोne);
DEFINE_SMB3_RW_DONE_EVENT(पढ़ो_करोne);
DEFINE_SMB3_RW_DONE_EVENT(query_dir_करोne);
DEFINE_SMB3_RW_DONE_EVENT(zero_करोne);
DEFINE_SMB3_RW_DONE_EVENT(falloc_करोne);

/*
 * For handle based calls other than पढ़ो and ग_लिखो, and get/set info
 */
DECLARE_EVENT_CLASS(smb3_fd_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid),
	TP_ARGS(xid, fid, tid, sesid),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
	),
	TP_prपूर्णांकk("\txid=%u sid=0x%llx tid=0x%x fid=0x%llx",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid)
)

#घोषणा DEFINE_SMB3_FD_EVENT(name)          \
DEFINE_EVENT(smb3_fd_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid),			\
	TP_ARGS(xid, fid, tid, sesid))

DEFINE_SMB3_FD_EVENT(flush_enter);
DEFINE_SMB3_FD_EVENT(flush_करोne);
DEFINE_SMB3_FD_EVENT(बंद_enter);
DEFINE_SMB3_FD_EVENT(बंद_करोne);

DECLARE_EVENT_CLASS(smb3_fd_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		पूर्णांक	rc),
	TP_ARGS(xid, fid, tid, sesid, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("\txid=%u sid=0x%llx tid=0x%x fid=0x%llx rc=%d",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->rc)
)

#घोषणा DEFINE_SMB3_FD_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_fd_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		पूर्णांक	rc),			\
	TP_ARGS(xid, fid, tid, sesid, rc))

DEFINE_SMB3_FD_ERR_EVENT(flush_err);
DEFINE_SMB3_FD_ERR_EVENT(lock_err);
DEFINE_SMB3_FD_ERR_EVENT(बंद_err);

/*
 * For handle based query/set info calls
 */
DECLARE_EVENT_CLASS(smb3_inf_enter_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u8	infclass,
		__u32	type),
	TP_ARGS(xid, fid, tid, sesid, infclass, type),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u8, infclass)
		__field(__u32, type)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->infclass = infclass;
		__entry->type = type;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x fid=0x%llx class=%u type=0x%x",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->infclass, __entry->type)
)

#घोषणा DEFINE_SMB3_INF_ENTER_EVENT(name)          \
DEFINE_EVENT(smb3_inf_enter_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u8	infclass,		\
		__u32	type),			\
	TP_ARGS(xid, fid, tid, sesid, infclass, type))

DEFINE_SMB3_INF_ENTER_EVENT(query_info_enter);
DEFINE_SMB3_INF_ENTER_EVENT(query_info_करोne);
DEFINE_SMB3_INF_ENTER_EVENT(notअगरy_enter);
DEFINE_SMB3_INF_ENTER_EVENT(notअगरy_करोne);

DECLARE_EVENT_CLASS(smb3_inf_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		__u8	infclass,
		__u32	type,
		पूर्णांक	rc),
	TP_ARGS(xid, fid, tid, sesid, infclass, type, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u8, infclass)
		__field(__u32, type)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->infclass = infclass;
		__entry->type = type;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x fid=0x%llx class=%u type=0x%x rc=%d",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->infclass, __entry->type, __entry->rc)
)

#घोषणा DEFINE_SMB3_INF_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_inf_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		__u8	infclass,		\
		__u32	type,			\
		पूर्णांक	rc),			\
	TP_ARGS(xid, fid, tid, sesid, infclass, type, rc))

DEFINE_SMB3_INF_ERR_EVENT(query_info_err);
DEFINE_SMB3_INF_ERR_EVENT(set_info_err);
DEFINE_SMB3_INF_ERR_EVENT(notअगरy_err);
DEFINE_SMB3_INF_ERR_EVENT(fsctl_err);

DECLARE_EVENT_CLASS(smb3_inf_compound_enter_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid,
		स्थिर अक्षर *full_path),
	TP_ARGS(xid, tid, sesid, full_path),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__string(path, full_path)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__assign_str(path, full_path);
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x path=%s",
		__entry->xid, __entry->sesid, __entry->tid,
		__get_str(path))
)

#घोषणा DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_enter_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		स्थिर अक्षर *full_path),		\
	TP_ARGS(xid, tid, sesid, full_path))

DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(query_info_compound_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(posix_query_info_compound_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(hardlink_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(नाम_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(सूची_हटाओ_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(set_eof_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(set_info_compound_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(delete_enter);
DEFINE_SMB3_INF_COMPOUND_ENTER_EVENT(सूची_गढ़ो_enter);


DECLARE_EVENT_CLASS(smb3_inf_compound_करोne_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid),
	TP_ARGS(xid, tid, sesid),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x",
		__entry->xid, __entry->sesid, __entry->tid)
)

#घोषणा DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_करोne_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid),			\
	TP_ARGS(xid, tid, sesid))

DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(query_info_compound_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(posix_query_info_compound_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(hardlink_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(नाम_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(सूची_हटाओ_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(set_eof_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(set_info_compound_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(delete_करोne);
DEFINE_SMB3_INF_COMPOUND_DONE_EVENT(सूची_गढ़ो_करोne);


DECLARE_EVENT_CLASS(smb3_inf_compound_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid,
		पूर्णांक	rc),
	TP_ARGS(xid, tid, sesid, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x rc=%d",
		__entry->xid, __entry->sesid, __entry->tid,
		__entry->rc)
)

#घोषणा DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(name)     \
DEFINE_EVENT(smb3_inf_compound_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		पूर्णांक rc),			\
	TP_ARGS(xid, tid, sesid, rc))

DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(query_info_compound_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(posix_query_info_compound_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(hardlink_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(नाम_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(सूची_हटाओ_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(set_eof_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(set_info_compound_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(सूची_गढ़ो_err);
DEFINE_SMB3_INF_COMPOUND_ERR_EVENT(delete_err);

/*
 * For logging SMB3 Status code and Command क्रम responses which वापस errors
 */
DECLARE_EVENT_CLASS(smb3_cmd_err_class,
	TP_PROTO(__u32	tid,
		__u64	sesid,
		__u16	cmd,
		__u64	mid,
		__u32	status,
		पूर्णांक	rc),
	TP_ARGS(tid, sesid, cmd, mid, status, rc),
	TP_STRUCT__entry(
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u16, cmd)
		__field(__u64, mid)
		__field(__u32, status)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->cmd = cmd;
		__entry->mid = mid;
		__entry->status = status;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("\tsid=0x%llx tid=0x%x cmd=%u mid=%llu status=0x%x rc=%d",
		__entry->sesid, __entry->tid, __entry->cmd, __entry->mid,
		__entry->status, __entry->rc)
)

#घोषणा DEFINE_SMB3_CMD_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_cmd_err_class, smb3_##name,    \
	TP_PROTO(__u32	tid,			\
		__u64	sesid,			\
		__u16	cmd,			\
		__u64	mid,			\
		__u32	status,			\
		पूर्णांक	rc),			\
	TP_ARGS(tid, sesid, cmd, mid, status, rc))

DEFINE_SMB3_CMD_ERR_EVENT(cmd_err);

DECLARE_EVENT_CLASS(smb3_cmd_करोne_class,
	TP_PROTO(__u32	tid,
		__u64	sesid,
		__u16	cmd,
		__u64	mid),
	TP_ARGS(tid, sesid, cmd, mid),
	TP_STRUCT__entry(
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u16, cmd)
		__field(__u64, mid)
	),
	TP_fast_assign(
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->cmd = cmd;
		__entry->mid = mid;
	),
	TP_prपूर्णांकk("\tsid=0x%llx tid=0x%x cmd=%u mid=%llu",
		__entry->sesid, __entry->tid,
		__entry->cmd, __entry->mid)
)

#घोषणा DEFINE_SMB3_CMD_DONE_EVENT(name)          \
DEFINE_EVENT(smb3_cmd_करोne_class, smb3_##name,    \
	TP_PROTO(__u32	tid,			\
		__u64	sesid,			\
		__u16	cmd,			\
		__u64	mid),			\
	TP_ARGS(tid, sesid, cmd, mid))

DEFINE_SMB3_CMD_DONE_EVENT(cmd_enter);
DEFINE_SMB3_CMD_DONE_EVENT(cmd_करोne);
DEFINE_SMB3_CMD_DONE_EVENT(ses_expired);

DECLARE_EVENT_CLASS(smb3_mid_class,
	TP_PROTO(__u16	cmd,
		__u64	mid,
		__u32	pid,
		अचिन्हित दीर्घ when_sent,
		अचिन्हित दीर्घ when_received),
	TP_ARGS(cmd, mid, pid, when_sent, when_received),
	TP_STRUCT__entry(
		__field(__u16, cmd)
		__field(__u64, mid)
		__field(__u32, pid)
		__field(अचिन्हित दीर्घ, when_sent)
		__field(अचिन्हित दीर्घ, when_received)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
		__entry->mid = mid;
		__entry->pid = pid;
		__entry->when_sent = when_sent;
		__entry->when_received = when_received;
	),
	TP_prपूर्णांकk("\tcmd=%u mid=%llu pid=%u, when_sent=%lu when_rcv=%lu",
		__entry->cmd, __entry->mid, __entry->pid, __entry->when_sent,
		__entry->when_received)
)

#घोषणा DEFINE_SMB3_MID_EVENT(name)          \
DEFINE_EVENT(smb3_mid_class, smb3_##name,    \
	TP_PROTO(__u16	cmd,			\
		__u64	mid,			\
		__u32	pid,			\
		अचिन्हित दीर्घ when_sent,	\
		अचिन्हित दीर्घ when_received),	\
	TP_ARGS(cmd, mid, pid, when_sent, when_received))

DEFINE_SMB3_MID_EVENT(slow_rsp);

DECLARE_EVENT_CLASS(smb3_निकास_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		स्थिर अक्षर *func_name,
		पूर्णांक	rc),
	TP_ARGS(xid, func_name, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__string(func_name, func_name)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__assign_str(func_name, func_name);
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("\t%s: xid=%u rc=%d",
		__get_str(func_name), __entry->xid, __entry->rc)
)

#घोषणा DEFINE_SMB3_EXIT_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_निकास_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		स्थिर अक्षर *func_name,		\
		पूर्णांक	rc),			\
	TP_ARGS(xid, func_name, rc))

DEFINE_SMB3_EXIT_ERR_EVENT(निकास_err);


DECLARE_EVENT_CLASS(smb3_sync_err_class,
	TP_PROTO(अचिन्हित दीर्घ ino,
		पूर्णांक	rc),
	TP_ARGS(ino, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, ino)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("\tino=%lu rc=%d",
		__entry->ino, __entry->rc)
)

#घोषणा DEFINE_SMB3_SYNC_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_sync_err_class, cअगरs_##name,    \
	TP_PROTO(अचिन्हित दीर्घ ino,		\
		पूर्णांक	rc),			\
	TP_ARGS(ino, rc))

DEFINE_SMB3_SYNC_ERR_EVENT(fsync_err);
DEFINE_SMB3_SYNC_ERR_EVENT(flush_err);


DECLARE_EVENT_CLASS(smb3_enter_निकास_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		स्थिर अक्षर *func_name),
	TP_ARGS(xid, func_name),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__string(func_name, func_name)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__assign_str(func_name, func_name);
	),
	TP_prपूर्णांकk("\t%s: xid=%u",
		__get_str(func_name), __entry->xid)
)

#घोषणा DEFINE_SMB3_ENTER_EXIT_EVENT(name)        \
DEFINE_EVENT(smb3_enter_निकास_class, smb3_##name,  \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		स्थिर अक्षर *func_name),		\
	TP_ARGS(xid, func_name))

DEFINE_SMB3_ENTER_EXIT_EVENT(enter);
DEFINE_SMB3_ENTER_EXIT_EVENT(निकास_करोne);

/*
 * For SMB2/SMB3 tree connect
 */

DECLARE_EVENT_CLASS(smb3_tcon_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid,
		स्थिर अक्षर *unc_name,
		पूर्णांक	rc),
	TP_ARGS(xid, tid, sesid, unc_name, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__string(name, unc_name)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__assign_str(name, unc_name);
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x unc_name=%s rc=%d",
		__entry->xid, __entry->sesid, __entry->tid,
		__get_str(name), __entry->rc)
)

#घोषणा DEFINE_SMB3_TCON_EVENT(name)          \
DEFINE_EVENT(smb3_tcon_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		स्थिर अक्षर *unc_name,		\
		पूर्णांक	rc),			\
	TP_ARGS(xid, tid, sesid, unc_name, rc))

DEFINE_SMB3_TCON_EVENT(tcon);


/*
 * For smb2/smb3 खोलो (including create and सूची_गढ़ो) calls
 */

DECLARE_EVENT_CLASS(smb3_खोलो_enter_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid,
		पूर्णांक	create_options,
		पूर्णांक	desired_access),
	TP_ARGS(xid, tid, sesid, create_options, desired_access),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(पूर्णांक, create_options)
		__field(पूर्णांक, desired_access)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->create_options = create_options;
		__entry->desired_access = desired_access;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x cr_opts=0x%x des_access=0x%x",
		__entry->xid, __entry->sesid, __entry->tid,
		__entry->create_options, __entry->desired_access)
)

#घोषणा DEFINE_SMB3_OPEN_ENTER_EVENT(name)        \
DEFINE_EVENT(smb3_खोलो_enter_class, smb3_##name,  \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		पूर्णांक	create_options,		\
		पूर्णांक	desired_access),	\
	TP_ARGS(xid, tid, sesid, create_options, desired_access))

DEFINE_SMB3_OPEN_ENTER_EVENT(खोलो_enter);
DEFINE_SMB3_OPEN_ENTER_EVENT(posix_सूची_गढ़ो_enter);

DECLARE_EVENT_CLASS(smb3_खोलो_err_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u32	tid,
		__u64	sesid,
		पूर्णांक	create_options,
		पूर्णांक	desired_access,
		पूर्णांक	rc),
	TP_ARGS(xid, tid, sesid, create_options, desired_access, rc),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(पूर्णांक,   create_options)
		__field(पूर्णांक, desired_access)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->create_options = create_options;
		__entry->desired_access = desired_access;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x cr_opts=0x%x des_access=0x%x rc=%d",
		__entry->xid, __entry->sesid, __entry->tid,
		__entry->create_options, __entry->desired_access, __entry->rc)
)

#घोषणा DEFINE_SMB3_OPEN_ERR_EVENT(name)          \
DEFINE_EVENT(smb3_खोलो_err_class, smb3_##name,    \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u32	tid,			\
		__u64	sesid,			\
		पूर्णांक	create_options,		\
		पूर्णांक	desired_access,		\
		पूर्णांक	rc),			\
	TP_ARGS(xid, tid, sesid, create_options, desired_access, rc))

DEFINE_SMB3_OPEN_ERR_EVENT(खोलो_err);
DEFINE_SMB3_OPEN_ERR_EVENT(posix_सूची_गढ़ो_err);

DECLARE_EVENT_CLASS(smb3_खोलो_करोne_class,
	TP_PROTO(अचिन्हित पूर्णांक xid,
		__u64	fid,
		__u32	tid,
		__u64	sesid,
		पूर्णांक	create_options,
		पूर्णांक	desired_access),
	TP_ARGS(xid, fid, tid, sesid, create_options, desired_access),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, xid)
		__field(__u64, fid)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(पूर्णांक, create_options)
		__field(पूर्णांक, desired_access)
	),
	TP_fast_assign(
		__entry->xid = xid;
		__entry->fid = fid;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->create_options = create_options;
		__entry->desired_access = desired_access;
	),
	TP_prपूर्णांकk("xid=%u sid=0x%llx tid=0x%x fid=0x%llx cr_opts=0x%x des_access=0x%x",
		__entry->xid, __entry->sesid, __entry->tid, __entry->fid,
		__entry->create_options, __entry->desired_access)
)

#घोषणा DEFINE_SMB3_OPEN_DONE_EVENT(name)        \
DEFINE_EVENT(smb3_खोलो_करोne_class, smb3_##name,  \
	TP_PROTO(अचिन्हित पूर्णांक xid,		\
		__u64	fid,			\
		__u32	tid,			\
		__u64	sesid,			\
		पूर्णांक	create_options,		\
		पूर्णांक	desired_access),	\
	TP_ARGS(xid, fid, tid, sesid, create_options, desired_access))

DEFINE_SMB3_OPEN_DONE_EVENT(खोलो_करोne);
DEFINE_SMB3_OPEN_DONE_EVENT(posix_सूची_गढ़ो_करोne);


DECLARE_EVENT_CLASS(smb3_lease_करोne_class,
	TP_PROTO(__u32	lease_state,
		__u32	tid,
		__u64	sesid,
		__u64	lease_key_low,
		__u64	lease_key_high),
	TP_ARGS(lease_state, tid, sesid, lease_key_low, lease_key_high),
	TP_STRUCT__entry(
		__field(__u32, lease_state)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u64, lease_key_low)
		__field(__u64, lease_key_high)
	),
	TP_fast_assign(
		__entry->lease_state = lease_state;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->lease_key_low = lease_key_low;
		__entry->lease_key_high = lease_key_high;
	),
	TP_prपूर्णांकk("sid=0x%llx tid=0x%x lease_key=0x%llx%llx lease_state=0x%x",
		__entry->sesid, __entry->tid, __entry->lease_key_high,
		__entry->lease_key_low, __entry->lease_state)
)

#घोषणा DEFINE_SMB3_LEASE_DONE_EVENT(name)        \
DEFINE_EVENT(smb3_lease_करोne_class, smb3_##name,  \
	TP_PROTO(__u32	lease_state,		\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	lease_key_low,		\
		__u64	lease_key_high),	\
	TP_ARGS(lease_state, tid, sesid, lease_key_low, lease_key_high))

DEFINE_SMB3_LEASE_DONE_EVENT(lease_करोne);

DECLARE_EVENT_CLASS(smb3_lease_err_class,
	TP_PROTO(__u32	lease_state,
		__u32	tid,
		__u64	sesid,
		__u64	lease_key_low,
		__u64	lease_key_high,
		पूर्णांक	rc),
	TP_ARGS(lease_state, tid, sesid, lease_key_low, lease_key_high, rc),
	TP_STRUCT__entry(
		__field(__u32, lease_state)
		__field(__u32, tid)
		__field(__u64, sesid)
		__field(__u64, lease_key_low)
		__field(__u64, lease_key_high)
		__field(पूर्णांक, rc)
	),
	TP_fast_assign(
		__entry->lease_state = lease_state;
		__entry->tid = tid;
		__entry->sesid = sesid;
		__entry->lease_key_low = lease_key_low;
		__entry->lease_key_high = lease_key_high;
		__entry->rc = rc;
	),
	TP_prपूर्णांकk("sid=0x%llx tid=0x%x lease_key=0x%llx%llx lease_state=0x%x rc=%d",
		__entry->sesid, __entry->tid, __entry->lease_key_high,
		__entry->lease_key_low, __entry->lease_state, __entry->rc)
)

#घोषणा DEFINE_SMB3_LEASE_ERR_EVENT(name)        \
DEFINE_EVENT(smb3_lease_err_class, smb3_##name,  \
	TP_PROTO(__u32	lease_state,		\
		__u32	tid,			\
		__u64	sesid,			\
		__u64	lease_key_low,		\
		__u64	lease_key_high,		\
		पूर्णांक	rc),			\
	TP_ARGS(lease_state, tid, sesid, lease_key_low, lease_key_high, rc))

DEFINE_SMB3_LEASE_ERR_EVENT(lease_err);

DECLARE_EVENT_CLASS(smb3_reconnect_class,
	TP_PROTO(__u64	currmid,
		__u64 conn_id,
		अक्षर *hostname),
	TP_ARGS(currmid, conn_id, hostname),
	TP_STRUCT__entry(
		__field(__u64, currmid)
		__field(__u64, conn_id)
		__string(hostname, hostname)
	),
	TP_fast_assign(
		__entry->currmid = currmid;
		__entry->conn_id = conn_id;
		__assign_str(hostname, hostname);
	),
	TP_prपूर्णांकk("conn_id=0x%llx server=%s current_mid=%llu",
		__entry->conn_id,
		__get_str(hostname),
		__entry->currmid)
)

#घोषणा DEFINE_SMB3_RECONNECT_EVENT(name)        \
DEFINE_EVENT(smb3_reconnect_class, smb3_##name,  \
	TP_PROTO(__u64	currmid,		\
		__u64 conn_id,			\
		अक्षर *hostname),				\
	TP_ARGS(currmid, conn_id, hostname))

DEFINE_SMB3_RECONNECT_EVENT(reconnect);
DEFINE_SMB3_RECONNECT_EVENT(partial_send_reconnect);

DECLARE_EVENT_CLASS(smb3_credit_class,
	TP_PROTO(__u64	currmid,
		__u64 conn_id,
		अक्षर *hostname,
		पूर्णांक credits,
		पूर्णांक credits_to_add,
		पूर्णांक in_flight),
	TP_ARGS(currmid, conn_id, hostname, credits, credits_to_add, in_flight),
	TP_STRUCT__entry(
		__field(__u64, currmid)
		__field(__u64, conn_id)
		__string(hostname, hostname)
		__field(पूर्णांक, credits)
		__field(पूर्णांक, credits_to_add)
		__field(पूर्णांक, in_flight)
	),
	TP_fast_assign(
		__entry->currmid = currmid;
		__entry->conn_id = conn_id;
		__assign_str(hostname, hostname);
		__entry->credits = credits;
		__entry->credits_to_add = credits_to_add;
		__entry->in_flight = in_flight;
	),
	TP_prपूर्णांकk("conn_id=0x%llx server=%s current_mid=%llu "
			"credits=%d credit_change=%d in_flight=%d",
		__entry->conn_id,
		__get_str(hostname),
		__entry->currmid,
		__entry->credits,
		__entry->credits_to_add,
		__entry->in_flight)
)

#घोषणा DEFINE_SMB3_CREDIT_EVENT(name)        \
DEFINE_EVENT(smb3_credit_class, smb3_##name,  \
	TP_PROTO(__u64	currmid,		\
		__u64 conn_id,			\
		अक्षर *hostname,			\
		पूर्णांक  credits,			\
		पूर्णांक  credits_to_add,	\
		पूर्णांक in_flight),			\
	TP_ARGS(currmid, conn_id, hostname, credits, credits_to_add, in_flight))

DEFINE_SMB3_CREDIT_EVENT(reconnect_with_invalid_credits);
DEFINE_SMB3_CREDIT_EVENT(reconnect_detected);
DEFINE_SMB3_CREDIT_EVENT(credit_समयout);
DEFINE_SMB3_CREDIT_EVENT(insufficient_credits);
DEFINE_SMB3_CREDIT_EVENT(too_many_credits);
DEFINE_SMB3_CREDIT_EVENT(add_credits);
DEFINE_SMB3_CREDIT_EVENT(set_credits);

#पूर्ण_अगर /* _CIFS_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
