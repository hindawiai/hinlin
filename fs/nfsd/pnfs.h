<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_NFSD_PNFS_H
#घोषणा _FS_NFSD_PNFS_H 1

#अगर_घोषित CONFIG_NFSD_V4
#समावेश <linux/exportfs.h>
#समावेश <linux/nfsd/export.h>

#समावेश "state.h"
#समावेश "xdr4.h"

काष्ठा xdr_stream;

काष्ठा nfsd4_deviceid_map अणु
	काष्ठा list_head	hash;
	u64			idx;
	पूर्णांक			fsid_type;
	u32			fsid[];
पूर्ण;

काष्ठा nfsd4_layout_ops अणु
	u32		notअगरy_types;
	bool		disable_recalls;

	__be32 (*proc_getdeviceinfo)(काष्ठा super_block *sb,
			काष्ठा svc_rqst *rqstp,
			काष्ठा nfs4_client *clp,
			काष्ठा nfsd4_getdeviceinfo *gdevp);
	__be32 (*encode_getdeviceinfo)(काष्ठा xdr_stream *xdr,
			काष्ठा nfsd4_getdeviceinfo *gdevp);

	__be32 (*proc_layoutget)(काष्ठा inode *, स्थिर काष्ठा svc_fh *fhp,
			काष्ठा nfsd4_layoutget *lgp);
	__be32 (*encode_layoutget)(काष्ठा xdr_stream *,
			काष्ठा nfsd4_layoutget *lgp);

	__be32 (*proc_layoutcommit)(काष्ठा inode *inode,
			काष्ठा nfsd4_layoutcommit *lcp);

	व्योम (*fence_client)(काष्ठा nfs4_layout_stateid *ls);
पूर्ण;

बाह्य स्थिर काष्ठा nfsd4_layout_ops *nfsd4_layout_ops[];
#अगर_घोषित CONFIG_NFSD_BLOCKLAYOUT
बाह्य स्थिर काष्ठा nfsd4_layout_ops bl_layout_ops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_SCSILAYOUT
बाह्य स्थिर काष्ठा nfsd4_layout_ops scsi_layout_ops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFSD_FLEXखाताLAYOUT
बाह्य स्थिर काष्ठा nfsd4_layout_ops ff_layout_ops;
#पूर्ण_अगर

__be32 nfsd4_preprocess_layout_stateid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, stateid_t *stateid,
		bool create, u32 layout_type, काष्ठा nfs4_layout_stateid **lsp);
__be32 nfsd4_insert_layout(काष्ठा nfsd4_layoutget *lgp,
		काष्ठा nfs4_layout_stateid *ls);
__be32 nfsd4_वापस_file_layouts(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_layoutवापस *lrp);
__be32 nfsd4_वापस_client_layouts(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_layoutवापस *lrp);
पूर्णांक nfsd4_set_deviceid(काष्ठा nfsd4_deviceid *id, स्थिर काष्ठा svc_fh *fhp,
		u32 device_generation);
काष्ठा nfsd4_deviceid_map *nfsd4_find_devid_map(पूर्णांक idx);
#पूर्ण_अगर /* CONFIG_NFSD_V4 */

#अगर_घोषित CONFIG_NFSD_PNFS
व्योम nfsd4_setup_layout_type(काष्ठा svc_export *exp);
व्योम nfsd4_वापस_all_client_layouts(काष्ठा nfs4_client *);
व्योम nfsd4_वापस_all_file_layouts(काष्ठा nfs4_client *clp,
		काष्ठा nfs4_file *fp);
पूर्णांक nfsd4_init_pnfs(व्योम);
व्योम nfsd4_निकास_pnfs(व्योम);
#अन्यथा
काष्ठा nfs4_client;
काष्ठा nfs4_file;

अटल अंतरभूत व्योम nfsd4_setup_layout_type(काष्ठा svc_export *exp)
अणु
पूर्ण

अटल अंतरभूत व्योम nfsd4_वापस_all_client_layouts(काष्ठा nfs4_client *clp)
अणु
पूर्ण
अटल अंतरभूत व्योम nfsd4_वापस_all_file_layouts(काष्ठा nfs4_client *clp,
		काष्ठा nfs4_file *fp)
अणु
पूर्ण
अटल अंतरभूत व्योम nfsd4_निकास_pnfs(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक nfsd4_init_pnfs(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */
#पूर्ण_अगर /* _FS_NFSD_PNFS_H */
