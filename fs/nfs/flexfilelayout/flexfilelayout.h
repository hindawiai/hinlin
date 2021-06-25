<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NFSv4 flexfile layout driver data काष्ठाures.
 *
 * Copyright (c) 2014, Primary Data, Inc. All rights reserved.
 *
 * Tao Peng <bergwolf@primarydata.com>
 */

#अगर_अघोषित FS_NFS_NFS4FLEXखाताLAYOUT_H
#घोषणा FS_NFS_NFS4FLEXखाताLAYOUT_H

#घोषणा FF_FLAGS_NO_LAYOUTCOMMIT 1
#घोषणा FF_FLAGS_NO_IO_THRU_MDS  2
#घोषणा FF_FLAGS_NO_READ_IO      4

#समावेश <linux/refcount.h>
#समावेश "../pnfs.h"

/* XXX: Let's filter out insanely large mirror count क्रम now to aव्योम oom
 * due to network error etc. */
#घोषणा NFS4_FLEXखाता_LAYOUT_MAX_MIRROR_CNT 4096

/* LAYOUTSTATS report पूर्णांकerval in ms */
#घोषणा FF_LAYOUTSTATS_REPORT_INTERVAL (60000L)
#घोषणा FF_LAYOUTSTATS_MAXDEV 4

काष्ठा nfs4_ff_ds_version अणु
	u32				version;
	u32				minor_version;
	u32				rsize;
	u32				wsize;
	bool				tightly_coupled;
पूर्ण;

/* chained in global deviceid hlist */
काष्ठा nfs4_ff_layout_ds अणु
	काष्ठा nfs4_deviceid_node	id_node;
	u32				ds_versions_cnt;
	काष्ठा nfs4_ff_ds_version	*ds_versions;
	काष्ठा nfs4_pnfs_ds		*ds;
पूर्ण;

काष्ठा nfs4_ff_layout_ds_err अणु
	काष्ठा list_head		list; /* linked in mirror error_list */
	u64				offset;
	u64				length;
	पूर्णांक				status;
	क्रमागत nfs_opnum4			opnum;
	nfs4_stateid			stateid;
	काष्ठा nfs4_deviceid		deviceid;
पूर्ण;

काष्ठा nfs4_ff_io_stat अणु
	__u64				ops_requested;
	__u64				bytes_requested;
	__u64				ops_completed;
	__u64				bytes_completed;
	__u64				bytes_not_delivered;
	kसमय_प्रकार				total_busy_समय;
	kसमय_प्रकार				aggregate_completion_समय;
पूर्ण;

काष्ठा nfs4_ff_busy_समयr अणु
	kसमय_प्रकार start_समय;
	atomic_t n_ops;
पूर्ण;

काष्ठा nfs4_ff_layoutstat अणु
	काष्ठा nfs4_ff_io_stat io_stat;
	काष्ठा nfs4_ff_busy_समयr busy_समयr;
पूर्ण;

काष्ठा nfs4_ff_layout_mirror अणु
	काष्ठा pnfs_layout_hdr		*layout;
	काष्ठा list_head		mirrors;
	u32				ds_count;
	u32				efficiency;
	काष्ठा nfs4_deviceid		devid;
	काष्ठा nfs4_ff_layout_ds	*mirror_ds;
	u32				fh_versions_cnt;
	काष्ठा nfs_fh			*fh_versions;
	nfs4_stateid			stateid;
	स्थिर काष्ठा cred __rcu		*ro_cred;
	स्थिर काष्ठा cred __rcu		*rw_cred;
	refcount_t			ref;
	spinlock_t			lock;
	अचिन्हित दीर्घ			flags;
	काष्ठा nfs4_ff_layoutstat	पढ़ो_stat;
	काष्ठा nfs4_ff_layoutstat	ग_लिखो_stat;
	kसमय_प्रकार				start_समय;
	u32				report_पूर्णांकerval;
पूर्ण;

#घोषणा NFS4_FF_MIRROR_STAT_AVAIL	(0)

काष्ठा nfs4_ff_layout_segment अणु
	काष्ठा pnfs_layout_segment	generic_hdr;
	u64				stripe_unit;
	u32				flags;
	u32				mirror_array_cnt;
	काष्ठा nfs4_ff_layout_mirror	*mirror_array[];
पूर्ण;

काष्ठा nfs4_flexfile_layout अणु
	काष्ठा pnfs_layout_hdr generic_hdr;
	काष्ठा pnfs_ds_commit_info commit_info;
	काष्ठा list_head	mirrors;
	काष्ठा list_head	error_list; /* nfs4_ff_layout_ds_err */
	kसमय_प्रकार			last_report_समय; /* Layoutstat report बार */
पूर्ण;

काष्ठा nfs4_flexfile_layoutवापस_args अणु
	काष्ठा list_head errors;
	काष्ठा nfs42_layoutstat_devinfo devinfo[FF_LAYOUTSTATS_MAXDEV];
	अचिन्हित पूर्णांक num_errors;
	अचिन्हित पूर्णांक num_dev;
	काष्ठा page *pages[1];
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_flexfile_layout *
FF_LAYOUT_FROM_HDR(काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस container_of(lo, काष्ठा nfs4_flexfile_layout, generic_hdr);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_ff_layout_segment *
FF_LAYOUT_LSEG(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस container_of(lseg,
			    काष्ठा nfs4_ff_layout_segment,
			    generic_hdr);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_ff_layout_ds *
FF_LAYOUT_MIRROR_DS(काष्ठा nfs4_deviceid_node *node)
अणु
	वापस container_of(node, काष्ठा nfs4_ff_layout_ds, id_node);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_ff_layout_mirror *
FF_LAYOUT_COMP(काष्ठा pnfs_layout_segment *lseg, u32 idx)
अणु
	काष्ठा nfs4_ff_layout_segment *fls = FF_LAYOUT_LSEG(lseg);

	अगर (idx < fls->mirror_array_cnt)
		वापस fls->mirror_array[idx];
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा nfs4_deviceid_node *
FF_LAYOUT_DEVID_NODE(काष्ठा pnfs_layout_segment *lseg, u32 idx)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror = FF_LAYOUT_COMP(lseg, idx);

	अगर (mirror != शून्य) अणु
		काष्ठा nfs4_ff_layout_ds *mirror_ds = mirror->mirror_ds;

		अगर (!IS_ERR_OR_शून्य(mirror_ds))
			वापस &mirror_ds->id_node;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत u32
FF_LAYOUT_MIRROR_COUNT(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस FF_LAYOUT_LSEG(lseg)->mirror_array_cnt;
पूर्ण

अटल अंतरभूत bool
ff_layout_no_fallback_to_mds(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस FF_LAYOUT_LSEG(lseg)->flags & FF_FLAGS_NO_IO_THRU_MDS;
पूर्ण

अटल अंतरभूत bool
ff_layout_no_पढ़ो_on_rw(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस FF_LAYOUT_LSEG(lseg)->flags & FF_FLAGS_NO_READ_IO;
पूर्ण

अटल अंतरभूत पूर्णांक
nfs4_ff_layout_ds_version(स्थिर काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	वापस mirror->mirror_ds->ds_versions[0].version;
पूर्ण

काष्ठा nfs4_ff_layout_ds *
nfs4_ff_alloc_deviceid_node(काष्ठा nfs_server *server, काष्ठा pnfs_device *pdev,
			    gfp_t gfp_flags);
व्योम nfs4_ff_layout_put_deviceid(काष्ठा nfs4_ff_layout_ds *mirror_ds);
व्योम nfs4_ff_layout_मुक्त_deviceid(काष्ठा nfs4_ff_layout_ds *mirror_ds);
पूर्णांक ff_layout_track_ds_error(काष्ठा nfs4_flexfile_layout *flo,
			     काष्ठा nfs4_ff_layout_mirror *mirror, u64 offset,
			     u64 length, पूर्णांक status, क्रमागत nfs_opnum4 opnum,
			     gfp_t gfp_flags);
व्योम ff_layout_send_layouterror(काष्ठा pnfs_layout_segment *lseg);
पूर्णांक ff_layout_encode_ds_ioerr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा list_head *head);
व्योम ff_layout_मुक्त_ds_ioerr(काष्ठा list_head *head);
अचिन्हित पूर्णांक ff_layout_fetch_ds_ioerr(काष्ठा pnfs_layout_hdr *lo,
		स्थिर काष्ठा pnfs_layout_range *range,
		काष्ठा list_head *head,
		अचिन्हित पूर्णांक maxnum);
काष्ठा nfs_fh *
nfs4_ff_layout_select_ds_fh(काष्ठा nfs4_ff_layout_mirror *mirror);
व्योम
nfs4_ff_layout_select_ds_stateid(स्थिर काष्ठा nfs4_ff_layout_mirror *mirror,
		nfs4_stateid *stateid);

काष्ठा nfs4_pnfs_ds *
nfs4_ff_layout_prepare_ds(काष्ठा pnfs_layout_segment *lseg,
			  काष्ठा nfs4_ff_layout_mirror *mirror,
			  bool fail_वापस);

काष्ठा rpc_clnt *
nfs4_ff_find_or_create_ds_client(काष्ठा nfs4_ff_layout_mirror *mirror,
				 काष्ठा nfs_client *ds_clp,
				 काष्ठा inode *inode);
स्थिर काष्ठा cred *ff_layout_get_ds_cred(काष्ठा nfs4_ff_layout_mirror *mirror,
					 स्थिर काष्ठा pnfs_layout_range *range,
					 स्थिर काष्ठा cred *mdscred);
bool ff_layout_aव्योम_mds_available_ds(काष्ठा pnfs_layout_segment *lseg);
bool ff_layout_aव्योम_पढ़ो_on_rw(काष्ठा pnfs_layout_segment *lseg);

#पूर्ण_अगर /* FS_NFS_NFS4FLEXखाताLAYOUT_H */
