<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Christoph Hellwig.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nfsd

#अगर !defined(_NFSD_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _NFSD_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "export.h"
#समावेश "nfsfh.h"

#घोषणा NFSD_TRACE_PROC_ARG_FIELDS \
		__field(अचिन्हित पूर्णांक, netns_ino) \
		__field(u32, xid) \
		__array(अचिन्हित अक्षर, server, माप(काष्ठा sockaddr_in6)) \
		__array(अचिन्हित अक्षर, client, माप(काष्ठा sockaddr_in6))

#घोषणा NFSD_TRACE_PROC_ARG_ASSIGNMENTS \
		करो अणु \
			__entry->netns_ino = SVC_NET(rqstp)->ns.inum; \
			__entry->xid = be32_to_cpu(rqstp->rq_xid); \
			स_नकल(__entry->server, &rqstp->rq_xprt->xpt_local, \
			       rqstp->rq_xprt->xpt_locallen); \
			स_नकल(__entry->client, &rqstp->rq_xprt->xpt_remote, \
			       rqstp->rq_xprt->xpt_remotelen); \
		पूर्ण जबतक (0);

#घोषणा NFSD_TRACE_PROC_RES_FIELDS \
		__field(अचिन्हित पूर्णांक, netns_ino) \
		__field(u32, xid) \
		__field(अचिन्हित दीर्घ, status) \
		__array(अचिन्हित अक्षर, server, माप(काष्ठा sockaddr_in6)) \
		__array(अचिन्हित अक्षर, client, माप(काष्ठा sockaddr_in6))

#घोषणा NFSD_TRACE_PROC_RES_ASSIGNMENTS(error) \
		करो अणु \
			__entry->netns_ino = SVC_NET(rqstp)->ns.inum; \
			__entry->xid = be32_to_cpu(rqstp->rq_xid); \
			__entry->status = be32_to_cpu(error); \
			स_नकल(__entry->server, &rqstp->rq_xprt->xpt_local, \
			       rqstp->rq_xprt->xpt_locallen); \
			स_नकल(__entry->client, &rqstp->rq_xprt->xpt_remote, \
			       rqstp->rq_xprt->xpt_remotelen); \
		पूर्ण जबतक (0);

TRACE_EVENT(nfsd_garbage_args_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqstp
	),
	TP_ARGS(rqstp),
	TP_STRUCT__entry(
		NFSD_TRACE_PROC_ARG_FIELDS

		__field(u32, vers)
		__field(u32, proc)
	),
	TP_fast_assign(
		NFSD_TRACE_PROC_ARG_ASSIGNMENTS

		__entry->vers = rqstp->rq_vers;
		__entry->proc = rqstp->rq_proc;
	),
	TP_prपूर्णांकk("xid=0x%08x vers=%u proc=%u",
		__entry->xid, __entry->vers, __entry->proc
	)
);

TRACE_EVENT(nfsd_cant_encode_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqstp
	),
	TP_ARGS(rqstp),
	TP_STRUCT__entry(
		NFSD_TRACE_PROC_ARG_FIELDS

		__field(u32, vers)
		__field(u32, proc)
	),
	TP_fast_assign(
		NFSD_TRACE_PROC_ARG_ASSIGNMENTS

		__entry->vers = rqstp->rq_vers;
		__entry->proc = rqstp->rq_proc;
	),
	TP_prपूर्णांकk("xid=0x%08x vers=%u proc=%u",
		__entry->xid, __entry->vers, __entry->proc
	)
);

#घोषणा show_nfsd_may_flags(x)						\
	__prपूर्णांक_flags(x, "|",						\
		अणु NFSD_MAY_EXEC,		"EXEC" पूर्ण,		\
		अणु NFSD_MAY_WRITE,		"WRITE" पूर्ण,		\
		अणु NFSD_MAY_READ,		"READ" पूर्ण,		\
		अणु NFSD_MAY_SATTR,		"SATTR" पूर्ण,		\
		अणु NFSD_MAY_TRUNC,		"TRUNC" पूर्ण,		\
		अणु NFSD_MAY_LOCK,		"LOCK" पूर्ण,		\
		अणु NFSD_MAY_OWNER_OVERRIDE,	"OWNER_OVERRIDE" पूर्ण,	\
		अणु NFSD_MAY_LOCAL_ACCESS,	"LOCAL_ACCESS" पूर्ण,	\
		अणु NFSD_MAY_BYPASS_GSS_ON_ROOT,	"BYPASS_GSS_ON_ROOT" पूर्ण,	\
		अणु NFSD_MAY_NOT_BREAK_LEASE,	"NOT_BREAK_LEASE" पूर्ण,	\
		अणु NFSD_MAY_BYPASS_GSS,		"BYPASS_GSS" पूर्ण,		\
		अणु NFSD_MAY_READ_IF_EXEC,	"READ_IF_EXEC" पूर्ण,	\
		अणु NFSD_MAY_64BIT_COOKIE,	"64BIT_COOKIE" पूर्ण)

TRACE_EVENT(nfsd_compound,
	TP_PROTO(स्थिर काष्ठा svc_rqst *rqst,
		 u32 args_opcnt),
	TP_ARGS(rqst, args_opcnt),
	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, args_opcnt)
	),
	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqst->rq_xid);
		__entry->args_opcnt = args_opcnt;
	),
	TP_prपूर्णांकk("xid=0x%08x opcnt=%u",
		__entry->xid, __entry->args_opcnt)
)

TRACE_EVENT(nfsd_compound_status,
	TP_PROTO(u32 args_opcnt,
		 u32 resp_opcnt,
		 __be32 status,
		 स्थिर अक्षर *name),
	TP_ARGS(args_opcnt, resp_opcnt, status, name),
	TP_STRUCT__entry(
		__field(u32, args_opcnt)
		__field(u32, resp_opcnt)
		__field(पूर्णांक, status)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->args_opcnt = args_opcnt;
		__entry->resp_opcnt = resp_opcnt;
		__entry->status = be32_to_cpu(status);
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("op=%u/%u %s status=%d",
		__entry->resp_opcnt, __entry->args_opcnt,
		__get_str(name), __entry->status)
)

TRACE_EVENT(nfsd_compound_decode_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqstp,
		u32 args_opcnt,
		u32 resp_opcnt,
		u32 opnum,
		__be32 status
	),
	TP_ARGS(rqstp, args_opcnt, resp_opcnt, opnum, status),
	TP_STRUCT__entry(
		NFSD_TRACE_PROC_RES_FIELDS

		__field(u32, args_opcnt)
		__field(u32, resp_opcnt)
		__field(u32, opnum)
	),
	TP_fast_assign(
		NFSD_TRACE_PROC_RES_ASSIGNMENTS(status)

		__entry->args_opcnt = args_opcnt;
		__entry->resp_opcnt = resp_opcnt;
		__entry->opnum = opnum;
	),
	TP_prपूर्णांकk("op=%u/%u opnum=%u status=%lu",
		__entry->resp_opcnt, __entry->args_opcnt,
		__entry->opnum, __entry->status)
);

TRACE_EVENT(nfsd_compound_encode_err,
	TP_PROTO(
		स्थिर काष्ठा svc_rqst *rqstp,
		u32 opnum,
		__be32 status
	),
	TP_ARGS(rqstp, opnum, status),
	TP_STRUCT__entry(
		NFSD_TRACE_PROC_RES_FIELDS

		__field(u32, opnum)
	),
	TP_fast_assign(
		NFSD_TRACE_PROC_RES_ASSIGNMENTS(status)

		__entry->opnum = opnum;
	),
	TP_prपूर्णांकk("opnum=%u status=%lu",
		__entry->opnum, __entry->status)
);


DECLARE_EVENT_CLASS(nfsd_fh_err_class,
	TP_PROTO(काष्ठा svc_rqst *rqstp,
		 काष्ठा svc_fh	*fhp,
		 पूर्णांक		status),
	TP_ARGS(rqstp, fhp, status),
	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, fh_hash)
		__field(पूर्णांक, status)
	),
	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqstp->rq_xid);
		__entry->fh_hash = knfsd_fh_hash(&fhp->fh_handle);
		__entry->status = status;
	),
	TP_prपूर्णांकk("xid=0x%08x fh_hash=0x%08x status=%d",
		  __entry->xid, __entry->fh_hash,
		  __entry->status)
)

#घोषणा DEFINE_NFSD_FH_ERR_EVENT(name)		\
DEFINE_EVENT(nfsd_fh_err_class, nfsd_##name,	\
	TP_PROTO(काष्ठा svc_rqst *rqstp,	\
		 काष्ठा svc_fh	*fhp,		\
		 पूर्णांक		status),	\
	TP_ARGS(rqstp, fhp, status))

DEFINE_NFSD_FH_ERR_EVENT(set_fh_dentry_badexport);
DEFINE_NFSD_FH_ERR_EVENT(set_fh_dentry_badhandle);

TRACE_EVENT(nfsd_exp_find_key,
	TP_PROTO(स्थिर काष्ठा svc_expkey *key,
		 पूर्णांक status),
	TP_ARGS(key, status),
	TP_STRUCT__entry(
		__field(पूर्णांक, fsidtype)
		__array(u32, fsid, 6)
		__string(auth_करोमुख्य, key->ek_client->name)
		__field(पूर्णांक, status)
	),
	TP_fast_assign(
		__entry->fsidtype = key->ek_fsidtype;
		स_नकल(__entry->fsid, key->ek_fsid, 4*6);
		__assign_str(auth_करोमुख्य, key->ek_client->name);
		__entry->status = status;
	),
	TP_prपूर्णांकk("fsid=%x::%s domain=%s status=%d",
		__entry->fsidtype,
		__prपूर्णांक_array(__entry->fsid, 6, 4),
		__get_str(auth_करोमुख्य),
		__entry->status
	)
);

TRACE_EVENT(nfsd_expkey_update,
	TP_PROTO(स्थिर काष्ठा svc_expkey *key, स्थिर अक्षर *exp_path),
	TP_ARGS(key, exp_path),
	TP_STRUCT__entry(
		__field(पूर्णांक, fsidtype)
		__array(u32, fsid, 6)
		__string(auth_करोमुख्य, key->ek_client->name)
		__string(path, exp_path)
		__field(bool, cache)
	),
	TP_fast_assign(
		__entry->fsidtype = key->ek_fsidtype;
		स_नकल(__entry->fsid, key->ek_fsid, 4*6);
		__assign_str(auth_करोमुख्य, key->ek_client->name);
		__assign_str(path, exp_path);
		__entry->cache = !test_bit(CACHE_NEGATIVE, &key->h.flags);
	),
	TP_prपूर्णांकk("fsid=%x::%s domain=%s path=%s cache=%s",
		__entry->fsidtype,
		__prपूर्णांक_array(__entry->fsid, 6, 4),
		__get_str(auth_करोमुख्य),
		__get_str(path),
		__entry->cache ? "pos" : "neg"
	)
);

TRACE_EVENT(nfsd_exp_get_by_name,
	TP_PROTO(स्थिर काष्ठा svc_export *key,
		 पूर्णांक status),
	TP_ARGS(key, status),
	TP_STRUCT__entry(
		__string(path, key->ex_path.dentry->d_name.name)
		__string(auth_करोमुख्य, key->ex_client->name)
		__field(पूर्णांक, status)
	),
	TP_fast_assign(
		__assign_str(path, key->ex_path.dentry->d_name.name);
		__assign_str(auth_करोमुख्य, key->ex_client->name);
		__entry->status = status;
	),
	TP_prपूर्णांकk("path=%s domain=%s status=%d",
		__get_str(path),
		__get_str(auth_करोमुख्य),
		__entry->status
	)
);

TRACE_EVENT(nfsd_export_update,
	TP_PROTO(स्थिर काष्ठा svc_export *key),
	TP_ARGS(key),
	TP_STRUCT__entry(
		__string(path, key->ex_path.dentry->d_name.name)
		__string(auth_करोमुख्य, key->ex_client->name)
		__field(bool, cache)
	),
	TP_fast_assign(
		__assign_str(path, key->ex_path.dentry->d_name.name);
		__assign_str(auth_करोमुख्य, key->ex_client->name);
		__entry->cache = !test_bit(CACHE_NEGATIVE, &key->h.flags);
	),
	TP_prपूर्णांकk("path=%s domain=%s cache=%s",
		__get_str(path),
		__get_str(auth_करोमुख्य),
		__entry->cache ? "pos" : "neg"
	)
);

DECLARE_EVENT_CLASS(nfsd_io_class,
	TP_PROTO(काष्ठा svc_rqst *rqstp,
		 काष्ठा svc_fh	*fhp,
		 loff_t		offset,
		 अचिन्हित दीर्घ	len),
	TP_ARGS(rqstp, fhp, offset, len),
	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, fh_hash)
		__field(loff_t, offset)
		__field(अचिन्हित दीर्घ, len)
	),
	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqstp->rq_xid);
		__entry->fh_hash = knfsd_fh_hash(&fhp->fh_handle);
		__entry->offset = offset;
		__entry->len = len;
	),
	TP_prपूर्णांकk("xid=0x%08x fh_hash=0x%08x offset=%lld len=%lu",
		  __entry->xid, __entry->fh_hash,
		  __entry->offset, __entry->len)
)

#घोषणा DEFINE_NFSD_IO_EVENT(name)		\
DEFINE_EVENT(nfsd_io_class, nfsd_##name,	\
	TP_PROTO(काष्ठा svc_rqst *rqstp,	\
		 काष्ठा svc_fh	*fhp,		\
		 loff_t		offset,		\
		 अचिन्हित दीर्घ	len),		\
	TP_ARGS(rqstp, fhp, offset, len))

DEFINE_NFSD_IO_EVENT(पढ़ो_start);
DEFINE_NFSD_IO_EVENT(पढ़ो_splice);
DEFINE_NFSD_IO_EVENT(पढ़ो_vector);
DEFINE_NFSD_IO_EVENT(पढ़ो_io_करोne);
DEFINE_NFSD_IO_EVENT(पढ़ो_करोne);
DEFINE_NFSD_IO_EVENT(ग_लिखो_start);
DEFINE_NFSD_IO_EVENT(ग_लिखो_खोलोed);
DEFINE_NFSD_IO_EVENT(ग_लिखो_io_करोne);
DEFINE_NFSD_IO_EVENT(ग_लिखो_करोne);

DECLARE_EVENT_CLASS(nfsd_err_class,
	TP_PROTO(काष्ठा svc_rqst *rqstp,
		 काष्ठा svc_fh	*fhp,
		 loff_t		offset,
		 पूर्णांक		status),
	TP_ARGS(rqstp, fhp, offset, status),
	TP_STRUCT__entry(
		__field(u32, xid)
		__field(u32, fh_hash)
		__field(loff_t, offset)
		__field(पूर्णांक, status)
	),
	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqstp->rq_xid);
		__entry->fh_hash = knfsd_fh_hash(&fhp->fh_handle);
		__entry->offset = offset;
		__entry->status = status;
	),
	TP_prपूर्णांकk("xid=0x%08x fh_hash=0x%08x offset=%lld status=%d",
		  __entry->xid, __entry->fh_hash,
		  __entry->offset, __entry->status)
)

#घोषणा DEFINE_NFSD_ERR_EVENT(name)		\
DEFINE_EVENT(nfsd_err_class, nfsd_##name,	\
	TP_PROTO(काष्ठा svc_rqst *rqstp,	\
		 काष्ठा svc_fh	*fhp,		\
		 loff_t		offset,		\
		 पूर्णांक		len),		\
	TP_ARGS(rqstp, fhp, offset, len))

DEFINE_NFSD_ERR_EVENT(पढ़ो_err);
DEFINE_NFSD_ERR_EVENT(ग_लिखो_err);

TRACE_EVENT(nfsd_dirent,
	TP_PROTO(काष्ठा svc_fh *fhp,
		 u64 ino,
		 स्थिर अक्षर *name,
		 पूर्णांक namlen),
	TP_ARGS(fhp, ino, name, namlen),
	TP_STRUCT__entry(
		__field(u32, fh_hash)
		__field(u64, ino)
		__field(पूर्णांक, len)
		__dynamic_array(अचिन्हित अक्षर, name, namlen)
	),
	TP_fast_assign(
		__entry->fh_hash = fhp ? knfsd_fh_hash(&fhp->fh_handle) : 0;
		__entry->ino = ino;
		__entry->len = namlen;
		स_नकल(__get_str(name), name, namlen);
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("fh_hash=0x%08x ino=%llu name=%.*s",
		__entry->fh_hash, __entry->ino,
		__entry->len, __get_str(name))
)

#समावेश "state.h"
#समावेश "filecache.h"
#समावेश "vfs.h"

DECLARE_EVENT_CLASS(nfsd_stateid_class,
	TP_PROTO(stateid_t *stp),
	TP_ARGS(stp),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__field(u32, si_id)
		__field(u32, si_generation)
	),
	TP_fast_assign(
		__entry->cl_boot = stp->si_opaque.so_clid.cl_boot;
		__entry->cl_id = stp->si_opaque.so_clid.cl_id;
		__entry->si_id = stp->si_opaque.so_id;
		__entry->si_generation = stp->si_generation;
	),
	TP_prपूर्णांकk("client %08x:%08x stateid %08x:%08x",
		__entry->cl_boot,
		__entry->cl_id,
		__entry->si_id,
		__entry->si_generation)
)

#घोषणा DEFINE_STATEID_EVENT(name) \
DEFINE_EVENT(nfsd_stateid_class, nfsd_##name, \
	TP_PROTO(stateid_t *stp), \
	TP_ARGS(stp))

DEFINE_STATEID_EVENT(layoutstate_alloc);
DEFINE_STATEID_EVENT(layoutstate_unhash);
DEFINE_STATEID_EVENT(layoutstate_मुक्त);
DEFINE_STATEID_EVENT(layout_get_lookup_fail);
DEFINE_STATEID_EVENT(layout_commit_lookup_fail);
DEFINE_STATEID_EVENT(layout_वापस_lookup_fail);
DEFINE_STATEID_EVENT(layout_recall);
DEFINE_STATEID_EVENT(layout_recall_करोne);
DEFINE_STATEID_EVENT(layout_recall_fail);
DEFINE_STATEID_EVENT(layout_recall_release);

DEFINE_STATEID_EVENT(खोलो);
DEFINE_STATEID_EVENT(deleg_पढ़ो);
DEFINE_STATEID_EVENT(deleg_अवरोध);
DEFINE_STATEID_EVENT(deleg_recall);

DECLARE_EVENT_CLASS(nfsd_stateseqid_class,
	TP_PROTO(u32 seqid, स्थिर stateid_t *stp),
	TP_ARGS(seqid, stp),
	TP_STRUCT__entry(
		__field(u32, seqid)
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__field(u32, si_id)
		__field(u32, si_generation)
	),
	TP_fast_assign(
		__entry->seqid = seqid;
		__entry->cl_boot = stp->si_opaque.so_clid.cl_boot;
		__entry->cl_id = stp->si_opaque.so_clid.cl_id;
		__entry->si_id = stp->si_opaque.so_id;
		__entry->si_generation = stp->si_generation;
	),
	TP_prपूर्णांकk("seqid=%u client %08x:%08x stateid %08x:%08x",
		__entry->seqid, __entry->cl_boot, __entry->cl_id,
		__entry->si_id, __entry->si_generation)
)

#घोषणा DEFINE_STATESEQID_EVENT(name) \
DEFINE_EVENT(nfsd_stateseqid_class, nfsd_##name, \
	TP_PROTO(u32 seqid, स्थिर stateid_t *stp), \
	TP_ARGS(seqid, stp))

DEFINE_STATESEQID_EVENT(preprocess);
DEFINE_STATESEQID_EVENT(खोलो_confirm);

DECLARE_EVENT_CLASS(nfsd_clientid_class,
	TP_PROTO(स्थिर clientid_t *clid),
	TP_ARGS(clid),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
	),
	TP_fast_assign(
		__entry->cl_boot = clid->cl_boot;
		__entry->cl_id = clid->cl_id;
	),
	TP_prपूर्णांकk("client %08x:%08x", __entry->cl_boot, __entry->cl_id)
)

#घोषणा DEFINE_CLIENTID_EVENT(name) \
DEFINE_EVENT(nfsd_clientid_class, nfsd_clid_##name, \
	TP_PROTO(स्थिर clientid_t *clid), \
	TP_ARGS(clid))

DEFINE_CLIENTID_EVENT(expired);
DEFINE_CLIENTID_EVENT(purged);
DEFINE_CLIENTID_EVENT(renew);
DEFINE_CLIENTID_EVENT(stale);

DECLARE_EVENT_CLASS(nfsd_net_class,
	TP_PROTO(स्थिर काष्ठा nfsd_net *nn),
	TP_ARGS(nn),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, boot_समय)
	),
	TP_fast_assign(
		__entry->boot_समय = nn->boot_समय;
	),
	TP_prपूर्णांकk("boot_time=%16llx", __entry->boot_समय)
)

#घोषणा DEFINE_NET_EVENT(name) \
DEFINE_EVENT(nfsd_net_class, nfsd_##name, \
	TP_PROTO(स्थिर काष्ठा nfsd_net *nn), \
	TP_ARGS(nn))

DEFINE_NET_EVENT(grace_start);
DEFINE_NET_EVENT(grace_complete);

DECLARE_EVENT_CLASS(nfsd_clid_class,
	TP_PROTO(स्थिर काष्ठा nfsd_net *nn,
		 अचिन्हित पूर्णांक namelen,
		 स्थिर अचिन्हित अक्षर *namedata),
	TP_ARGS(nn, namelen, namedata),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, boot_समय)
		__field(अचिन्हित पूर्णांक, namelen)
		__dynamic_array(अचिन्हित अक्षर,  name, namelen)
	),
	TP_fast_assign(
		__entry->boot_समय = nn->boot_समय;
		__entry->namelen = namelen;
		स_नकल(__get_dynamic_array(name), namedata, namelen);
	),
	TP_prपूर्णांकk("boot_time=%16llx nfs4_clientid=%.*s",
		__entry->boot_समय, __entry->namelen, __get_str(name))
)

#घोषणा DEFINE_CLID_EVENT(name) \
DEFINE_EVENT(nfsd_clid_class, nfsd_clid_##name, \
	TP_PROTO(स्थिर काष्ठा nfsd_net *nn, \
		 अचिन्हित पूर्णांक namelen, \
		 स्थिर अचिन्हित अक्षर *namedata), \
	TP_ARGS(nn, namelen, namedata))

DEFINE_CLID_EVENT(find);
DEFINE_CLID_EVENT(reclaim);

TRACE_EVENT(nfsd_clid_inuse_err,
	TP_PROTO(स्थिर काष्ठा nfs4_client *clp),
	TP_ARGS(clp),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
		__field(अचिन्हित पूर्णांक, namelen)
		__dynamic_array(अचिन्हित अक्षर, name, clp->cl_name.len)
	),
	TP_fast_assign(
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		स_नकल(__entry->addr, &clp->cl_addr,
			माप(काष्ठा sockaddr_in6));
		__entry->namelen = clp->cl_name.len;
		स_नकल(__get_dynamic_array(name), clp->cl_name.data,
			clp->cl_name.len);
	),
	TP_prपूर्णांकk("nfs4_clientid %.*s already in use by %pISpc, client %08x:%08x",
		__entry->namelen, __get_str(name), __entry->addr,
		__entry->cl_boot, __entry->cl_id)
)

/*
 * from fs/nfsd/filecache.h
 */
TRACE_DEFINE_ENUM(NFSD_खाता_HASHED);
TRACE_DEFINE_ENUM(NFSD_खाता_PENDING);
TRACE_DEFINE_ENUM(NFSD_खाता_BREAK_READ);
TRACE_DEFINE_ENUM(NFSD_खाता_BREAK_WRITE);
TRACE_DEFINE_ENUM(NFSD_खाता_REFERENCED);

#घोषणा show_nf_flags(val)						\
	__prपूर्णांक_flags(val, "|",						\
		अणु 1 << NFSD_खाता_HASHED,	"HASHED" पूर्ण,		\
		अणु 1 << NFSD_खाता_PENDING,	"PENDING" पूर्ण,		\
		अणु 1 << NFSD_खाता_BREAK_READ,	"BREAK_READ" पूर्ण,		\
		अणु 1 << NFSD_खाता_BREAK_WRITE,	"BREAK_WRITE" पूर्ण,	\
		अणु 1 << NFSD_खाता_REFERENCED,	"REFERENCED"पूर्ण)

DECLARE_EVENT_CLASS(nfsd_file_class,
	TP_PROTO(काष्ठा nfsd_file *nf),
	TP_ARGS(nf),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, nf_hashval)
		__field(व्योम *, nf_inode)
		__field(पूर्णांक, nf_ref)
		__field(अचिन्हित दीर्घ, nf_flags)
		__field(अचिन्हित अक्षर, nf_may)
		__field(काष्ठा file *, nf_file)
	),
	TP_fast_assign(
		__entry->nf_hashval = nf->nf_hashval;
		__entry->nf_inode = nf->nf_inode;
		__entry->nf_ref = refcount_पढ़ो(&nf->nf_ref);
		__entry->nf_flags = nf->nf_flags;
		__entry->nf_may = nf->nf_may;
		__entry->nf_file = nf->nf_file;
	),
	TP_prपूर्णांकk("hash=0x%x inode=%p ref=%d flags=%s may=%s file=%p",
		__entry->nf_hashval,
		__entry->nf_inode,
		__entry->nf_ref,
		show_nf_flags(__entry->nf_flags),
		show_nfsd_may_flags(__entry->nf_may),
		__entry->nf_file)
)

#घोषणा DEFINE_NFSD_खाता_EVENT(name) \
DEFINE_EVENT(nfsd_file_class, name, \
	TP_PROTO(काष्ठा nfsd_file *nf), \
	TP_ARGS(nf))

DEFINE_NFSD_खाता_EVENT(nfsd_file_alloc);
DEFINE_NFSD_खाता_EVENT(nfsd_file_put_final);
DEFINE_NFSD_खाता_EVENT(nfsd_file_unhash);
DEFINE_NFSD_खाता_EVENT(nfsd_file_put);
DEFINE_NFSD_खाता_EVENT(nfsd_file_unhash_and_release_locked);

TRACE_EVENT(nfsd_file_acquire,
	TP_PROTO(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक hash,
		 काष्ठा inode *inode, अचिन्हित पूर्णांक may_flags,
		 काष्ठा nfsd_file *nf, __be32 status),

	TP_ARGS(rqstp, hash, inode, may_flags, nf, status),

	TP_STRUCT__entry(
		__field(u32, xid)
		__field(अचिन्हित पूर्णांक, hash)
		__field(व्योम *, inode)
		__field(अचिन्हित दीर्घ, may_flags)
		__field(पूर्णांक, nf_ref)
		__field(अचिन्हित दीर्घ, nf_flags)
		__field(अचिन्हित दीर्घ, nf_may)
		__field(काष्ठा file *, nf_file)
		__field(u32, status)
	),

	TP_fast_assign(
		__entry->xid = be32_to_cpu(rqstp->rq_xid);
		__entry->hash = hash;
		__entry->inode = inode;
		__entry->may_flags = may_flags;
		__entry->nf_ref = nf ? refcount_पढ़ो(&nf->nf_ref) : 0;
		__entry->nf_flags = nf ? nf->nf_flags : 0;
		__entry->nf_may = nf ? nf->nf_may : 0;
		__entry->nf_file = nf ? nf->nf_file : शून्य;
		__entry->status = be32_to_cpu(status);
	),

	TP_prपूर्णांकk("xid=0x%x hash=0x%x inode=%p may_flags=%s ref=%d nf_flags=%s nf_may=%s nf_file=%p status=%u",
			__entry->xid, __entry->hash, __entry->inode,
			show_nfsd_may_flags(__entry->may_flags),
			__entry->nf_ref, show_nf_flags(__entry->nf_flags),
			show_nfsd_may_flags(__entry->nf_may),
			__entry->nf_file, __entry->status)
);

DECLARE_EVENT_CLASS(nfsd_file_search_class,
	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक hash, पूर्णांक found),
	TP_ARGS(inode, hash, found),
	TP_STRUCT__entry(
		__field(काष्ठा inode *, inode)
		__field(अचिन्हित पूर्णांक, hash)
		__field(पूर्णांक, found)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->hash = hash;
		__entry->found = found;
	),
	TP_prपूर्णांकk("hash=0x%x inode=%p found=%d", __entry->hash,
			__entry->inode, __entry->found)
);

#घोषणा DEFINE_NFSD_खाता_SEARCH_EVENT(name)				\
DEFINE_EVENT(nfsd_file_search_class, name,				\
	TP_PROTO(काष्ठा inode *inode, अचिन्हित पूर्णांक hash, पूर्णांक found),	\
	TP_ARGS(inode, hash, found))

DEFINE_NFSD_खाता_SEARCH_EVENT(nfsd_file_बंद_inode_sync);
DEFINE_NFSD_खाता_SEARCH_EVENT(nfsd_file_बंद_inode);
DEFINE_NFSD_खाता_SEARCH_EVENT(nfsd_file_is_cached);

TRACE_EVENT(nfsd_file_fsnotअगरy_handle_event,
	TP_PROTO(काष्ठा inode *inode, u32 mask),
	TP_ARGS(inode, mask),
	TP_STRUCT__entry(
		__field(काष्ठा inode *, inode)
		__field(अचिन्हित पूर्णांक, nlink)
		__field(umode_t, mode)
		__field(u32, mask)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->nlink = inode->i_nlink;
		__entry->mode = inode->i_mode;
		__entry->mask = mask;
	),
	TP_prपूर्णांकk("inode=%p nlink=%u mode=0%ho mask=0x%x", __entry->inode,
			__entry->nlink, __entry->mode, __entry->mask)
);

#समावेश "cache.h"

TRACE_DEFINE_ENUM(RC_DROPIT);
TRACE_DEFINE_ENUM(RC_REPLY);
TRACE_DEFINE_ENUM(RC_DOIT);

#घोषणा show_drc_retval(x)						\
	__prपूर्णांक_symbolic(x,						\
		अणु RC_DROPIT, "DROPIT" पूर्ण,				\
		अणु RC_REPLY, "REPLY" पूर्ण,					\
		अणु RC_DOIT, "DOIT" पूर्ण)

TRACE_EVENT(nfsd_drc_found,
	TP_PROTO(
		स्थिर काष्ठा nfsd_net *nn,
		स्थिर काष्ठा svc_rqst *rqstp,
		पूर्णांक result
	),
	TP_ARGS(nn, rqstp, result),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, boot_समय)
		__field(अचिन्हित दीर्घ, result)
		__field(u32, xid)
	),
	TP_fast_assign(
		__entry->boot_समय = nn->boot_समय;
		__entry->result = result;
		__entry->xid = be32_to_cpu(rqstp->rq_xid);
	),
	TP_prपूर्णांकk("boot_time=%16llx xid=0x%08x result=%s",
		__entry->boot_समय, __entry->xid,
		show_drc_retval(__entry->result))

);

TRACE_EVENT(nfsd_drc_mismatch,
	TP_PROTO(
		स्थिर काष्ठा nfsd_net *nn,
		स्थिर काष्ठा svc_cacherep *key,
		स्थिर काष्ठा svc_cacherep *rp
	),
	TP_ARGS(nn, key, rp),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, boot_समय)
		__field(u32, xid)
		__field(u32, cached)
		__field(u32, ingress)
	),
	TP_fast_assign(
		__entry->boot_समय = nn->boot_समय;
		__entry->xid = be32_to_cpu(key->c_key.k_xid);
		__entry->cached = (__क्रमce u32)key->c_key.k_csum;
		__entry->ingress = (__क्रमce u32)rp->c_key.k_csum;
	),
	TP_prपूर्णांकk("boot_time=%16llx xid=0x%08x cached-csum=0x%08x ingress-csum=0x%08x",
		__entry->boot_समय, __entry->xid, __entry->cached,
		__entry->ingress)
);

TRACE_EVENT(nfsd_cb_args,
	TP_PROTO(
		स्थिर काष्ठा nfs4_client *clp,
		स्थिर काष्ठा nfs4_cb_conn *conn
	),
	TP_ARGS(clp, conn),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__field(u32, prog)
		__field(u32, ident)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),
	TP_fast_assign(
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		__entry->prog = conn->cb_prog;
		__entry->ident = conn->cb_ident;
		स_नकल(__entry->addr, &conn->cb_addr,
			माप(काष्ठा sockaddr_in6));
	),
	TP_prपूर्णांकk("client %08x:%08x callback addr=%pISpc prog=%u ident=%u",
		__entry->cl_boot, __entry->cl_id,
		__entry->addr, __entry->prog, __entry->ident)
);

TRACE_EVENT(nfsd_cb_nodelegs,
	TP_PROTO(स्थिर काष्ठा nfs4_client *clp),
	TP_ARGS(clp),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
	),
	TP_fast_assign(
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
	),
	TP_prपूर्णांकk("client %08x:%08x", __entry->cl_boot, __entry->cl_id)
)

TRACE_DEFINE_ENUM(NFSD4_CB_UP);
TRACE_DEFINE_ENUM(NFSD4_CB_UNKNOWN);
TRACE_DEFINE_ENUM(NFSD4_CB_DOWN);
TRACE_DEFINE_ENUM(NFSD4_CB_FAULT);

#घोषणा show_cb_state(val)						\
	__prपूर्णांक_symbolic(val,						\
		अणु NFSD4_CB_UP,		"UP" पूर्ण,				\
		अणु NFSD4_CB_UNKNOWN,	"UNKNOWN" पूर्ण,			\
		अणु NFSD4_CB_DOWN,	"DOWN" पूर्ण,			\
		अणु NFSD4_CB_FAULT,	"FAULT"पूर्ण)

DECLARE_EVENT_CLASS(nfsd_cb_class,
	TP_PROTO(स्थिर काष्ठा nfs4_client *clp),
	TP_ARGS(clp),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),
	TP_fast_assign(
		__entry->state = clp->cl_cb_state;
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		स_नकल(__entry->addr, &clp->cl_cb_conn.cb_addr,
			माप(काष्ठा sockaddr_in6));
	),
	TP_prपूर्णांकk("addr=%pISpc client %08x:%08x state=%s",
		__entry->addr, __entry->cl_boot, __entry->cl_id,
		show_cb_state(__entry->state))
);

#घोषणा DEFINE_NFSD_CB_EVENT(name)			\
DEFINE_EVENT(nfsd_cb_class, nfsd_cb_##name,		\
	TP_PROTO(स्थिर काष्ठा nfs4_client *clp),	\
	TP_ARGS(clp))

DEFINE_NFSD_CB_EVENT(setup);
DEFINE_NFSD_CB_EVENT(state);
DEFINE_NFSD_CB_EVENT(shutकरोwn);

TRACE_EVENT(nfsd_cb_setup_err,
	TP_PROTO(
		स्थिर काष्ठा nfs4_client *clp,
		दीर्घ error
	),
	TP_ARGS(clp, error),
	TP_STRUCT__entry(
		__field(दीर्घ, error)
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),
	TP_fast_assign(
		__entry->error = error;
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		स_नकल(__entry->addr, &clp->cl_cb_conn.cb_addr,
			माप(काष्ठा sockaddr_in6));
	),
	TP_prपूर्णांकk("addr=%pISpc client %08x:%08x error=%ld",
		__entry->addr, __entry->cl_boot, __entry->cl_id, __entry->error)
);

TRACE_EVENT(nfsd_cb_work,
	TP_PROTO(
		स्थिर काष्ठा nfs4_client *clp,
		स्थिर अक्षर *procedure
	),
	TP_ARGS(clp, procedure),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__string(procedure, procedure)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),
	TP_fast_assign(
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		__assign_str(procedure, procedure)
		स_नकल(__entry->addr, &clp->cl_cb_conn.cb_addr,
			माप(काष्ठा sockaddr_in6));
	),
	TP_prपूर्णांकk("addr=%pISpc client %08x:%08x procedure=%s",
		__entry->addr, __entry->cl_boot, __entry->cl_id,
		__get_str(procedure))
);

TRACE_EVENT(nfsd_cb_करोne,
	TP_PROTO(
		स्थिर काष्ठा nfs4_client *clp,
		पूर्णांक status
	),
	TP_ARGS(clp, status),
	TP_STRUCT__entry(
		__field(u32, cl_boot)
		__field(u32, cl_id)
		__field(पूर्णांक, status)
		__array(अचिन्हित अक्षर, addr, माप(काष्ठा sockaddr_in6))
	),
	TP_fast_assign(
		__entry->cl_boot = clp->cl_clientid.cl_boot;
		__entry->cl_id = clp->cl_clientid.cl_id;
		__entry->status = status;
		स_नकल(__entry->addr, &clp->cl_cb_conn.cb_addr,
			माप(काष्ठा sockaddr_in6));
	),
	TP_prपूर्णांकk("addr=%pISpc client %08x:%08x status=%d",
		__entry->addr, __entry->cl_boot, __entry->cl_id,
		__entry->status)
);

#पूर्ण_अगर /* _NFSD_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
