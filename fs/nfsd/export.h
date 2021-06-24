<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 */
#अगर_अघोषित NFSD_EXPORT_H
#घोषणा NFSD_EXPORT_H

#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/percpu_counter.h>
#समावेश <uapi/linux/nfsd/export.h>
#समावेश <linux/nfs4.h>

काष्ठा knfsd_fh;
काष्ठा svc_fh;
काष्ठा svc_rqst;

/*
 * FS Locations
 */

#घोषणा MAX_FS_LOCATIONS	128

काष्ठा nfsd4_fs_location अणु
	अक्षर *hosts; /* colon separated list of hosts */
	अक्षर *path;  /* slash separated list of path components */
पूर्ण;

काष्ठा nfsd4_fs_locations अणु
	uपूर्णांक32_t locations_count;
	काष्ठा nfsd4_fs_location *locations;
/* If we're not actually serving this data ourselves (only providing a
 * list of replicas that करो serve it) then we set "migrated": */
	पूर्णांक migrated;
पूर्ण;

/*
 * We keep an array of pseuकरोflavors with the export, in order from most
 * to least preferred.  For the क्रमeseeable future, we करोn't expect more
 * than the eight pseuकरोflavors null, unix, krb5, krb5i, krb5p, skpm3,
 * spkm3i, and spkm3p (and using all 8 at once should be rare).
 */
#घोषणा MAX_SECINFO_LIST	8
#घोषणा EX_UUID_LEN		16

काष्ठा exp_flavor_info अणु
	u32	pseuकरोflavor;
	u32	flags;
पूर्ण;

/* Per-export stats */
क्रमागत अणु
	EXP_STATS_FH_STALE,
	EXP_STATS_IO_READ,
	EXP_STATS_IO_WRITE,
	EXP_STATS_COUNTERS_NUM
पूर्ण;

काष्ठा export_stats अणु
	समय64_t		start_समय;
	काष्ठा percpu_counter	counter[EXP_STATS_COUNTERS_NUM];
पूर्ण;

काष्ठा svc_export अणु
	काष्ठा cache_head	h;
	काष्ठा auth_करोमुख्य *	ex_client;
	पूर्णांक			ex_flags;
	काष्ठा path		ex_path;
	kuid_t			ex_anon_uid;
	kgid_t			ex_anon_gid;
	पूर्णांक			ex_fsid;
	अचिन्हित अक्षर *		ex_uuid; /* 16 byte fsid */
	काष्ठा nfsd4_fs_locations ex_fslocs;
	uपूर्णांक32_t		ex_nflavors;
	काष्ठा exp_flavor_info	ex_flavors[MAX_SECINFO_LIST];
	u32			ex_layout_types;
	काष्ठा nfsd4_deviceid_map *ex_devid_map;
	काष्ठा cache_detail	*cd;
	काष्ठा rcu_head		ex_rcu;
	काष्ठा export_stats	ex_stats;
पूर्ण;

/* an "export key" (expkey) maps a filehandlefragement to an
 * svc_export क्रम a given client.  There can be several per export,
 * क्रम the dअगरferent fsid types.
 */
काष्ठा svc_expkey अणु
	काष्ठा cache_head	h;

	काष्ठा auth_करोमुख्य *	ek_client;
	पूर्णांक			ek_fsidtype;
	u32			ek_fsid[6];

	काष्ठा path		ek_path;
	काष्ठा rcu_head		ek_rcu;
पूर्ण;

#घोषणा EX_ISSYNC(exp)		(!((exp)->ex_flags & NFSEXP_ASYNC))
#घोषणा EX_NOHIDE(exp)		((exp)->ex_flags & NFSEXP_NOHIDE)
#घोषणा EX_WGATHER(exp)		((exp)->ex_flags & NFSEXP_GATHERED_WRITES)

पूर्णांक nfsexp_flags(काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp);
__be32 check_nfsd_access(काष्ठा svc_export *exp, काष्ठा svc_rqst *rqstp);

/*
 * Function declarations
 */
पूर्णांक			nfsd_export_init(काष्ठा net *);
व्योम			nfsd_export_shutकरोwn(काष्ठा net *);
व्योम			nfsd_export_flush(काष्ठा net *);
काष्ठा svc_export *	rqst_exp_get_by_name(काष्ठा svc_rqst *,
					     काष्ठा path *);
काष्ठा svc_export *	rqst_exp_parent(काष्ठा svc_rqst *,
					काष्ठा path *);
काष्ठा svc_export *	rqst_find_fsidzero_export(काष्ठा svc_rqst *);
पूर्णांक			exp_rootfh(काष्ठा net *, काष्ठा auth_करोमुख्य *,
					अक्षर *path, काष्ठा knfsd_fh *, पूर्णांक maxsize);
__be32			exp_pseuकरोroot(काष्ठा svc_rqst *, काष्ठा svc_fh *);
__be32			nfsत्रुटि_सं(पूर्णांक त्रुटि_सं);

अटल अंतरभूत व्योम exp_put(काष्ठा svc_export *exp)
अणु
	cache_put(&exp->h, exp->cd);
पूर्ण

अटल अंतरभूत काष्ठा svc_export *exp_get(काष्ठा svc_export *exp)
अणु
	cache_get(&exp->h);
	वापस exp;
पूर्ण
काष्ठा svc_export * rqst_exp_find(काष्ठा svc_rqst *, पूर्णांक, u32 *);

#पूर्ण_अगर /* NFSD_EXPORT_H */
