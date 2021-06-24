<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/nfs_ssc.h
 *
 * Author: Dai Ngo <dai.ngo@oracle.com>
 *
 * Copyright (c) 2020, Oracle and/or its affiliates.
 */

#समावेश <linux/nfs_fs.h>

बाह्य काष्ठा nfs_ssc_client_ops_tbl nfs_ssc_client_tbl;

/*
 * NFS_V4
 */
काष्ठा nfs4_ssc_client_ops अणु
	काष्ठा file *(*sco_खोलो)(काष्ठा vfsmount *ss_mnt,
		काष्ठा nfs_fh *src_fh, nfs4_stateid *stateid);
	व्योम (*sco_बंद)(काष्ठा file *filep);
पूर्ण;

/*
 * NFS_FS
 */
काष्ठा nfs_ssc_client_ops अणु
	व्योम (*sco_sb_deactive)(काष्ठा super_block *sb);
पूर्ण;

काष्ठा nfs_ssc_client_ops_tbl अणु
	स्थिर काष्ठा nfs4_ssc_client_ops *ssc_nfs4_ops;
	स्थिर काष्ठा nfs_ssc_client_ops *ssc_nfs_ops;
पूर्ण;

बाह्य व्योम nfs42_ssc_रेजिस्टर_ops(व्योम);
बाह्य व्योम nfs42_ssc_unरेजिस्टर_ops(व्योम);

बाह्य व्योम nfs42_ssc_रेजिस्टर(स्थिर काष्ठा nfs4_ssc_client_ops *ops);
बाह्य व्योम nfs42_ssc_unरेजिस्टर(स्थिर काष्ठा nfs4_ssc_client_ops *ops);

#अगर_घोषित CONFIG_NFSD_V4_2_INTER_SSC
अटल अंतरभूत काष्ठा file *nfs42_ssc_खोलो(काष्ठा vfsmount *ss_mnt,
		काष्ठा nfs_fh *src_fh, nfs4_stateid *stateid)
अणु
	अगर (nfs_ssc_client_tbl.ssc_nfs4_ops)
		वापस (*nfs_ssc_client_tbl.ssc_nfs4_ops->sco_खोलो)(ss_mnt, src_fh, stateid);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल अंतरभूत व्योम nfs42_ssc_बंद(काष्ठा file *filep)
अणु
	अगर (nfs_ssc_client_tbl.ssc_nfs4_ops)
		(*nfs_ssc_client_tbl.ssc_nfs4_ops->sco_बंद)(filep);
पूर्ण
#पूर्ण_अगर

/*
 * NFS_FS
 */
बाह्य व्योम nfs_ssc_रेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops);
बाह्य व्योम nfs_ssc_unरेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops);

अटल अंतरभूत व्योम nfs_करो_sb_deactive(काष्ठा super_block *sb)
अणु
	अगर (nfs_ssc_client_tbl.ssc_nfs_ops)
		(*nfs_ssc_client_tbl.ssc_nfs_ops->sco_sb_deactive)(sb);
पूर्ण
