<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Trond Myklebust <Trond.Myklebust@netapp.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nfs

#अगर !defined(_TRACE_NFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NFS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/iversion.h>

TRACE_DEFINE_ENUM(DT_UNKNOWN);
TRACE_DEFINE_ENUM(DT_FIFO);
TRACE_DEFINE_ENUM(DT_CHR);
TRACE_DEFINE_ENUM(DT_सूची);
TRACE_DEFINE_ENUM(DT_BLK);
TRACE_DEFINE_ENUM(DT_REG);
TRACE_DEFINE_ENUM(DT_LNK);
TRACE_DEFINE_ENUM(DT_SOCK);
TRACE_DEFINE_ENUM(DT_WHT);

#घोषणा nfs_show_file_type(ftype) \
	__prपूर्णांक_symbolic(ftype, \
			अणु DT_UNKNOWN, "UNKNOWN" पूर्ण, \
			अणु DT_FIFO, "FIFO" पूर्ण, \
			अणु DT_CHR, "CHR" पूर्ण, \
			अणु DT_सूची, "DIR" पूर्ण, \
			अणु DT_BLK, "BLK" पूर्ण, \
			अणु DT_REG, "REG" पूर्ण, \
			अणु DT_LNK, "LNK" पूर्ण, \
			अणु DT_SOCK, "SOCK" पूर्ण, \
			अणु DT_WHT, "WHT" पूर्ण)

TRACE_DEFINE_ENUM(NFS_INO_INVALID_DATA);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_ATIME);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_ACCESS);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_ACL);
TRACE_DEFINE_ENUM(NFS_INO_REVAL_PAGECACHE);
TRACE_DEFINE_ENUM(NFS_INO_REVAL_FORCED);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_LABEL);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_CHANGE);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_CTIME);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_MTIME);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_SIZE);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_OTHER);
TRACE_DEFINE_ENUM(NFS_INO_DATA_INVAL_DEFER);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_BLOCKS);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_XATTR);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_NLINK);
TRACE_DEFINE_ENUM(NFS_INO_INVALID_MODE);

#घोषणा nfs_show_cache_validity(v) \
	__prपूर्णांक_flags(v, "|", \
			अणु NFS_INO_INVALID_DATA, "INVALID_DATA" पूर्ण, \
			अणु NFS_INO_INVALID_ATIME, "INVALID_ATIME" पूर्ण, \
			अणु NFS_INO_INVALID_ACCESS, "INVALID_ACCESS" पूर्ण, \
			अणु NFS_INO_INVALID_ACL, "INVALID_ACL" पूर्ण, \
			अणु NFS_INO_REVAL_PAGECACHE, "REVAL_PAGECACHE" पूर्ण, \
			अणु NFS_INO_REVAL_FORCED, "REVAL_FORCED" पूर्ण, \
			अणु NFS_INO_INVALID_LABEL, "INVALID_LABEL" पूर्ण, \
			अणु NFS_INO_INVALID_CHANGE, "INVALID_CHANGE" पूर्ण, \
			अणु NFS_INO_INVALID_CTIME, "INVALID_CTIME" पूर्ण, \
			अणु NFS_INO_INVALID_MTIME, "INVALID_MTIME" पूर्ण, \
			अणु NFS_INO_INVALID_SIZE, "INVALID_SIZE" पूर्ण, \
			अणु NFS_INO_INVALID_OTHER, "INVALID_OTHER" पूर्ण, \
			अणु NFS_INO_DATA_INVAL_DEFER, "DATA_INVAL_DEFER" पूर्ण, \
			अणु NFS_INO_INVALID_BLOCKS, "INVALID_BLOCKS" पूर्ण, \
			अणु NFS_INO_INVALID_XATTR, "INVALID_XATTR" पूर्ण, \
			अणु NFS_INO_INVALID_NLINK, "INVALID_NLINK" पूर्ण, \
			अणु NFS_INO_INVALID_MODE, "INVALID_MODE" पूर्ण)

TRACE_DEFINE_ENUM(NFS_INO_ADVISE_RDPLUS);
TRACE_DEFINE_ENUM(NFS_INO_STALE);
TRACE_DEFINE_ENUM(NFS_INO_ACL_LRU_SET);
TRACE_DEFINE_ENUM(NFS_INO_INVALIDATING);
TRACE_DEFINE_ENUM(NFS_INO_FSCACHE);
TRACE_DEFINE_ENUM(NFS_INO_FSCACHE_LOCK);
TRACE_DEFINE_ENUM(NFS_INO_LAYOUTCOMMIT);
TRACE_DEFINE_ENUM(NFS_INO_LAYOUTCOMMITTING);
TRACE_DEFINE_ENUM(NFS_INO_LAYOUTSTATS);
TRACE_DEFINE_ENUM(NFS_INO_OसूचीECT);

#घोषणा nfs_show_nfsi_flags(v) \
	__prपूर्णांक_flags(v, "|", \
			अणु BIT(NFS_INO_ADVISE_RDPLUS), "ADVISE_RDPLUS" पूर्ण, \
			अणु BIT(NFS_INO_STALE), "STALE" पूर्ण, \
			अणु BIT(NFS_INO_ACL_LRU_SET), "ACL_LRU_SET" पूर्ण, \
			अणु BIT(NFS_INO_INVALIDATING), "INVALIDATING" पूर्ण, \
			अणु BIT(NFS_INO_FSCACHE), "FSCACHE" पूर्ण, \
			अणु BIT(NFS_INO_FSCACHE_LOCK), "FSCACHE_LOCK" पूर्ण, \
			अणु BIT(NFS_INO_LAYOUTCOMMIT), "NEED_LAYOUTCOMMIT" पूर्ण, \
			अणु BIT(NFS_INO_LAYOUTCOMMITTING), "LAYOUTCOMMIT" पूर्ण, \
			अणु BIT(NFS_INO_LAYOUTSTATS), "LAYOUTSTATS" पूर्ण, \
			अणु BIT(NFS_INO_OसूचीECT), "ODIRECT" पूर्ण)

DECLARE_EVENT_CLASS(nfs_inode_event,
		TP_PROTO(
			स्थिर काष्ठा inode *inode
		),

		TP_ARGS(inode),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(u64, version)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(&nfsi->fh);
			__entry->version = inode_peek_iversion_raw(inode);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x version=%llu ",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(अचिन्हित दीर्घ दीर्घ)__entry->version
		)
);

DECLARE_EVENT_CLASS(nfs_inode_event_करोne,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			पूर्णांक error
		),

		TP_ARGS(inode, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(अचिन्हित अक्षर, type)
			__field(u64, fileid)
			__field(u64, version)
			__field(loff_t, size)
			__field(अचिन्हित दीर्घ, nfsi_flags)
			__field(अचिन्हित दीर्घ, cache_validity)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			__entry->error = error < 0 ? -error : 0;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(&nfsi->fh);
			__entry->type = nfs_umode_to_dtype(inode->i_mode);
			__entry->version = inode_peek_iversion_raw(inode);
			__entry->size = i_size_पढ़ो(inode);
			__entry->nfsi_flags = nfsi->flags;
			__entry->cache_validity = nfsi->cache_validity;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"type=%u (%s) version=%llu size=%lld "
			"cache_validity=0x%lx (%s) nfs_flags=0x%lx (%s)",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->type,
			nfs_show_file_type(__entry->type),
			(अचिन्हित दीर्घ दीर्घ)__entry->version,
			(दीर्घ दीर्घ)__entry->size,
			__entry->cache_validity,
			nfs_show_cache_validity(__entry->cache_validity),
			__entry->nfsi_flags,
			nfs_show_nfsi_flags(__entry->nfsi_flags)
		)
);

#घोषणा DEFINE_NFS_INODE_EVENT(name) \
	DEFINE_EVENT(nfs_inode_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *inode \
			), \
			TP_ARGS(inode))
#घोषणा DEFINE_NFS_INODE_EVENT_DONE(name) \
	DEFINE_EVENT(nfs_inode_event_करोne, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *inode, \
				पूर्णांक error \
			), \
			TP_ARGS(inode, error))
DEFINE_NFS_INODE_EVENT(nfs_set_inode_stale);
DEFINE_NFS_INODE_EVENT(nfs_refresh_inode_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_refresh_inode_निकास);
DEFINE_NFS_INODE_EVENT(nfs_revalidate_inode_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_revalidate_inode_निकास);
DEFINE_NFS_INODE_EVENT(nfs_invalidate_mapping_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_invalidate_mapping_निकास);
DEFINE_NFS_INODE_EVENT(nfs_getattr_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_getattr_निकास);
DEFINE_NFS_INODE_EVENT(nfs_setattr_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_setattr_निकास);
DEFINE_NFS_INODE_EVENT(nfs_ग_लिखोback_page_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_ग_लिखोback_page_निकास);
DEFINE_NFS_INODE_EVENT(nfs_ग_लिखोback_inode_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_ग_लिखोback_inode_निकास);
DEFINE_NFS_INODE_EVENT(nfs_fsync_enter);
DEFINE_NFS_INODE_EVENT_DONE(nfs_fsync_निकास);
DEFINE_NFS_INODE_EVENT(nfs_access_enter);

TRACE_EVENT(nfs_access_निकास,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			अचिन्हित पूर्णांक mask,
			अचिन्हित पूर्णांक permitted,
			पूर्णांक error
		),

		TP_ARGS(inode, mask, permitted, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(अचिन्हित अक्षर, type)
			__field(u64, fileid)
			__field(u64, version)
			__field(loff_t, size)
			__field(अचिन्हित दीर्घ, nfsi_flags)
			__field(अचिन्हित दीर्घ, cache_validity)
			__field(अचिन्हित पूर्णांक, mask)
			__field(अचिन्हित पूर्णांक, permitted)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			__entry->error = error < 0 ? -error : 0;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(&nfsi->fh);
			__entry->type = nfs_umode_to_dtype(inode->i_mode);
			__entry->version = inode_peek_iversion_raw(inode);
			__entry->size = i_size_पढ़ो(inode);
			__entry->nfsi_flags = nfsi->flags;
			__entry->cache_validity = nfsi->cache_validity;
			__entry->mask = mask;
			__entry->permitted = permitted;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"type=%u (%s) version=%llu size=%lld "
			"cache_validity=0x%lx (%s) nfs_flags=0x%lx (%s) "
			"mask=0x%x permitted=0x%x",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->type,
			nfs_show_file_type(__entry->type),
			(अचिन्हित दीर्घ दीर्घ)__entry->version,
			(दीर्घ दीर्घ)__entry->size,
			__entry->cache_validity,
			nfs_show_cache_validity(__entry->cache_validity),
			__entry->nfsi_flags,
			nfs_show_nfsi_flags(__entry->nfsi_flags),
			__entry->mask, __entry->permitted
		)
);

TRACE_DEFINE_ENUM(LOOKUP_FOLLOW);
TRACE_DEFINE_ENUM(LOOKUP_सूचीECTORY);
TRACE_DEFINE_ENUM(LOOKUP_AUTOMOUNT);
TRACE_DEFINE_ENUM(LOOKUP_PARENT);
TRACE_DEFINE_ENUM(LOOKUP_REVAL);
TRACE_DEFINE_ENUM(LOOKUP_RCU);
TRACE_DEFINE_ENUM(LOOKUP_OPEN);
TRACE_DEFINE_ENUM(LOOKUP_CREATE);
TRACE_DEFINE_ENUM(LOOKUP_EXCL);
TRACE_DEFINE_ENUM(LOOKUP_RENAME_TARGET);
TRACE_DEFINE_ENUM(LOOKUP_JUMPED);
TRACE_DEFINE_ENUM(LOOKUP_ROOT);
TRACE_DEFINE_ENUM(LOOKUP_EMPTY);
TRACE_DEFINE_ENUM(LOOKUP_DOWN);

#घोषणा show_lookup_flags(flags) \
	__prपूर्णांक_flags(flags, "|", \
			अणु LOOKUP_FOLLOW, "FOLLOW" पूर्ण, \
			अणु LOOKUP_सूचीECTORY, "DIRECTORY" पूर्ण, \
			अणु LOOKUP_AUTOMOUNT, "AUTOMOUNT" पूर्ण, \
			अणु LOOKUP_PARENT, "PARENT" पूर्ण, \
			अणु LOOKUP_REVAL, "REVAL" पूर्ण, \
			अणु LOOKUP_RCU, "RCU" पूर्ण, \
			अणु LOOKUP_OPEN, "OPEN" पूर्ण, \
			अणु LOOKUP_CREATE, "CREATE" पूर्ण, \
			अणु LOOKUP_EXCL, "EXCL" पूर्ण, \
			अणु LOOKUP_RENAME_TARGET, "RENAME_TARGET" पूर्ण, \
			अणु LOOKUP_JUMPED, "JUMPED" पूर्ण, \
			अणु LOOKUP_ROOT, "ROOT" पूर्ण, \
			अणु LOOKUP_EMPTY, "EMPTY" पूर्ण, \
			अणु LOOKUP_DOWN, "DOWN" पूर्ण)

DECLARE_EVENT_CLASS(nfs_lookup_event,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			अचिन्हित पूर्णांक flags
		),

		TP_ARGS(dir, dentry, flags),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, flags)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->flags = flags;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"flags=0x%lx (%s) name=%02x:%02x:%llu/%s",
			__entry->flags,
			show_lookup_flags(__entry->flags),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

#घोषणा DEFINE_NFS_LOOKUP_EVENT(name) \
	DEFINE_EVENT(nfs_lookup_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *dir, \
				स्थिर काष्ठा dentry *dentry, \
				अचिन्हित पूर्णांक flags \
			), \
			TP_ARGS(dir, dentry, flags))

DECLARE_EVENT_CLASS(nfs_lookup_event_करोne,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			अचिन्हित पूर्णांक flags,
			पूर्णांक error
		),

		TP_ARGS(dir, dentry, flags, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(अचिन्हित दीर्घ, flags)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->error = error < 0 ? -error : 0;
			__entry->flags = flags;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) flags=0x%lx (%s) name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			__entry->flags,
			show_lookup_flags(__entry->flags),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

#घोषणा DEFINE_NFS_LOOKUP_EVENT_DONE(name) \
	DEFINE_EVENT(nfs_lookup_event_करोne, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *dir, \
				स्थिर काष्ठा dentry *dentry, \
				अचिन्हित पूर्णांक flags, \
				पूर्णांक error \
			), \
			TP_ARGS(dir, dentry, flags, error))

DEFINE_NFS_LOOKUP_EVENT(nfs_lookup_enter);
DEFINE_NFS_LOOKUP_EVENT_DONE(nfs_lookup_निकास);
DEFINE_NFS_LOOKUP_EVENT(nfs_lookup_revalidate_enter);
DEFINE_NFS_LOOKUP_EVENT_DONE(nfs_lookup_revalidate_निकास);

TRACE_DEFINE_ENUM(O_WRONLY);
TRACE_DEFINE_ENUM(O_RDWR);
TRACE_DEFINE_ENUM(O_CREAT);
TRACE_DEFINE_ENUM(O_EXCL);
TRACE_DEFINE_ENUM(O_NOCTTY);
TRACE_DEFINE_ENUM(O_TRUNC);
TRACE_DEFINE_ENUM(O_APPEND);
TRACE_DEFINE_ENUM(O_NONBLOCK);
TRACE_DEFINE_ENUM(O_DSYNC);
TRACE_DEFINE_ENUM(O_सूचीECT);
TRACE_DEFINE_ENUM(O_LARGEखाता);
TRACE_DEFINE_ENUM(O_सूचीECTORY);
TRACE_DEFINE_ENUM(O_NOFOLLOW);
TRACE_DEFINE_ENUM(O_NOATIME);
TRACE_DEFINE_ENUM(O_CLOEXEC);

#घोषणा show_खोलो_flags(flags) \
	__prपूर्णांक_flags(flags, "|", \
		अणु O_WRONLY, "O_WRONLY" पूर्ण, \
		अणु O_RDWR, "O_RDWR" पूर्ण, \
		अणु O_CREAT, "O_CREAT" पूर्ण, \
		अणु O_EXCL, "O_EXCL" पूर्ण, \
		अणु O_NOCTTY, "O_NOCTTY" पूर्ण, \
		अणु O_TRUNC, "O_TRUNC" पूर्ण, \
		अणु O_APPEND, "O_APPEND" पूर्ण, \
		अणु O_NONBLOCK, "O_NONBLOCK" पूर्ण, \
		अणु O_DSYNC, "O_DSYNC" पूर्ण, \
		अणु O_सूचीECT, "O_DIRECT" पूर्ण, \
		अणु O_LARGEखाता, "O_LARGEFILE" पूर्ण, \
		अणु O_सूचीECTORY, "O_DIRECTORY" पूर्ण, \
		अणु O_NOFOLLOW, "O_NOFOLLOW" पूर्ण, \
		अणु O_NOATIME, "O_NOATIME" पूर्ण, \
		अणु O_CLOEXEC, "O_CLOEXEC" पूर्ण)

#घोषणा show_भ_शेषe_flags(mode) \
	__prपूर्णांक_flags(mode, "|", \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_READ), "READ" पूर्ण, \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_WRITE), "WRITE" पूर्ण, \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_EXEC), "EXEC" पूर्ण)

TRACE_EVENT(nfs_atomic_खोलो_enter,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा nfs_खोलो_context *ctx,
			अचिन्हित पूर्णांक flags
		),

		TP_ARGS(dir, ctx, flags),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, flags)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, ctx->dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->flags = flags;
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)ctx->mode;
			__assign_str(name, ctx->dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"flags=0x%lx (%s) fmode=%s name=%02x:%02x:%llu/%s",
			__entry->flags,
			show_खोलो_flags(__entry->flags),
			show_भ_शेषe_flags(__entry->भ_शेषe),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

TRACE_EVENT(nfs_atomic_खोलो_निकास,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा nfs_खोलो_context *ctx,
			अचिन्हित पूर्णांक flags,
			पूर्णांक error
		),

		TP_ARGS(dir, ctx, flags, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(अचिन्हित दीर्घ, flags)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, ctx->dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->error = -error;
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->flags = flags;
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)ctx->mode;
			__assign_str(name, ctx->dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) flags=0x%lx (%s) fmode=%s "
			"name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			__entry->flags,
			show_खोलो_flags(__entry->flags),
			show_भ_शेषe_flags(__entry->भ_शेषe),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

TRACE_EVENT(nfs_create_enter,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			अचिन्हित पूर्णांक flags
		),

		TP_ARGS(dir, dentry, flags),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, flags)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->flags = flags;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"flags=0x%lx (%s) name=%02x:%02x:%llu/%s",
			__entry->flags,
			show_खोलो_flags(__entry->flags),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

TRACE_EVENT(nfs_create_निकास,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			अचिन्हित पूर्णांक flags,
			पूर्णांक error
		),

		TP_ARGS(dir, dentry, flags, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(अचिन्हित दीर्घ, flags)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->error = -error;
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->flags = flags;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) flags=0x%lx (%s) name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			__entry->flags,
			show_खोलो_flags(__entry->flags),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

DECLARE_EVENT_CLASS(nfs_directory_event,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry
		),

		TP_ARGS(dir, dentry),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"name=%02x:%02x:%llu/%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

#घोषणा DEFINE_NFS_सूचीECTORY_EVENT(name) \
	DEFINE_EVENT(nfs_directory_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *dir, \
				स्थिर काष्ठा dentry *dentry \
			), \
			TP_ARGS(dir, dentry))

DECLARE_EVENT_CLASS(nfs_directory_event_करोne,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			पूर्णांक error
		),

		TP_ARGS(dir, dentry, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->error = error < 0 ? -error : 0;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

#घोषणा DEFINE_NFS_सूचीECTORY_EVENT_DONE(name) \
	DEFINE_EVENT(nfs_directory_event_करोne, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *dir, \
				स्थिर काष्ठा dentry *dentry, \
				पूर्णांक error \
			), \
			TP_ARGS(dir, dentry, error))

DEFINE_NFS_सूचीECTORY_EVENT(nfs_mknod_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_mknod_निकास);
DEFINE_NFS_सूचीECTORY_EVENT(nfs_सूची_गढ़ो_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_सूची_गढ़ो_निकास);
DEFINE_NFS_सूचीECTORY_EVENT(nfs_सूची_हटाओ_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_सूची_हटाओ_निकास);
DEFINE_NFS_सूचीECTORY_EVENT(nfs_हटाओ_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_हटाओ_निकास);
DEFINE_NFS_सूचीECTORY_EVENT(nfs_unlink_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_unlink_निकास);
DEFINE_NFS_सूचीECTORY_EVENT(nfs_symlink_enter);
DEFINE_NFS_सूचीECTORY_EVENT_DONE(nfs_symlink_निकास);

TRACE_EVENT(nfs_link_enter,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry
		),

		TP_ARGS(inode, dir, dentry),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, fileid)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->dir = NFS_खाताID(dir);
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu name=%02x:%02x:%llu/%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			__entry->fileid,
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

TRACE_EVENT(nfs_link_निकास,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा dentry *dentry,
			पूर्णांक error
		),

		TP_ARGS(inode, dir, dentry, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u64, fileid)
			__field(u64, dir)
			__string(name, dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->dir = NFS_खाताID(dir);
			__entry->error = error < 0 ? -error : 0;
			__assign_str(name, dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			__entry->fileid,
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

DECLARE_EVENT_CLASS(nfs_नाम_event,
		TP_PROTO(
			स्थिर काष्ठा inode *old_dir,
			स्थिर काष्ठा dentry *old_dentry,
			स्थिर काष्ठा inode *new_dir,
			स्थिर काष्ठा dentry *new_dentry
		),

		TP_ARGS(old_dir, old_dentry, new_dir, new_dentry),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, old_dir)
			__field(u64, new_dir)
			__string(old_name, old_dentry->d_name.name)
			__string(new_name, new_dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = old_dir->i_sb->s_dev;
			__entry->old_dir = NFS_खाताID(old_dir);
			__entry->new_dir = NFS_खाताID(new_dir);
			__assign_str(old_name, old_dentry->d_name.name);
			__assign_str(new_name, new_dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"old_name=%02x:%02x:%llu/%s new_name=%02x:%02x:%llu/%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->old_dir,
			__get_str(old_name),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->new_dir,
			__get_str(new_name)
		)
);
#घोषणा DEFINE_NFS_RENAME_EVENT(name) \
	DEFINE_EVENT(nfs_नाम_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *old_dir, \
				स्थिर काष्ठा dentry *old_dentry, \
				स्थिर काष्ठा inode *new_dir, \
				स्थिर काष्ठा dentry *new_dentry \
			), \
			TP_ARGS(old_dir, old_dentry, new_dir, new_dentry))

DECLARE_EVENT_CLASS(nfs_नाम_event_करोne,
		TP_PROTO(
			स्थिर काष्ठा inode *old_dir,
			स्थिर काष्ठा dentry *old_dentry,
			स्थिर काष्ठा inode *new_dir,
			स्थिर काष्ठा dentry *new_dentry,
			पूर्णांक error
		),

		TP_ARGS(old_dir, old_dentry, new_dir, new_dentry, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(अचिन्हित दीर्घ, error)
			__field(u64, old_dir)
			__string(old_name, old_dentry->d_name.name)
			__field(u64, new_dir)
			__string(new_name, new_dentry->d_name.name)
		),

		TP_fast_assign(
			__entry->dev = old_dir->i_sb->s_dev;
			__entry->error = -error;
			__entry->old_dir = NFS_खाताID(old_dir);
			__entry->new_dir = NFS_खाताID(new_dir);
			__assign_str(old_name, old_dentry->d_name.name);
			__assign_str(new_name, new_dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) old_name=%02x:%02x:%llu/%s "
			"new_name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->old_dir,
			__get_str(old_name),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->new_dir,
			__get_str(new_name)
		)
);
#घोषणा DEFINE_NFS_RENAME_EVENT_DONE(name) \
	DEFINE_EVENT(nfs_नाम_event_करोne, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *old_dir, \
				स्थिर काष्ठा dentry *old_dentry, \
				स्थिर काष्ठा inode *new_dir, \
				स्थिर काष्ठा dentry *new_dentry, \
				पूर्णांक error \
			), \
			TP_ARGS(old_dir, old_dentry, new_dir, \
				new_dentry, error))

DEFINE_NFS_RENAME_EVENT(nfs_नाम_enter);
DEFINE_NFS_RENAME_EVENT_DONE(nfs_नाम_निकास);

DEFINE_NFS_RENAME_EVENT_DONE(nfs_sillyनाम_नाम);

TRACE_EVENT(nfs_sillyनाम_unlink,
		TP_PROTO(
			स्थिर काष्ठा nfs_unlinkdata *data,
			पूर्णांक error
		),

		TP_ARGS(data, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(अचिन्हित दीर्घ, error)
			__field(u64, dir)
			__dynamic_array(अक्षर, name, data->args.name.len + 1)
		),

		TP_fast_assign(
			काष्ठा inode *dir = d_inode(data->dentry->d_parent);
			माप_प्रकार len = data->args.name.len;
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->error = -error;
			स_नकल(__get_str(name),
				data->args.name.name, len);
			__get_str(name)[len] = 0;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) name=%02x:%02x:%llu/%s",
			-__entry->error, nfs_show_status(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

TRACE_EVENT(nfs_initiate_पढ़ो,
		TP_PROTO(
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(hdr),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, count)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;

			__entry->offset = hdr->args.offset;
			__entry->count = hdr->args.count;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->count
		)
);

TRACE_EVENT(nfs_पढ़ोpage_करोne,
		TP_PROTO(
			स्थिर काष्ठा rpc_task *task,
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(task, hdr),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, arg_count)
			__field(u32, res_count)
			__field(bool, eof)
			__field(पूर्णांक, status)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;

			__entry->status = task->tk_status;
			__entry->offset = hdr->args.offset;
			__entry->arg_count = hdr->args.count;
			__entry->res_count = hdr->res.count;
			__entry->eof = hdr->res.eof;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u res=%u status=%d%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->arg_count,
			__entry->res_count, __entry->status,
			__entry->eof ? " eof" : ""
		)
);

TRACE_EVENT(nfs_पढ़ोpage_लघु,
		TP_PROTO(
			स्थिर काष्ठा rpc_task *task,
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(task, hdr),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, arg_count)
			__field(u32, res_count)
			__field(bool, eof)
			__field(पूर्णांक, status)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;

			__entry->status = task->tk_status;
			__entry->offset = hdr->args.offset;
			__entry->arg_count = hdr->args.count;
			__entry->res_count = hdr->res.count;
			__entry->eof = hdr->res.eof;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u res=%u status=%d%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->arg_count,
			__entry->res_count, __entry->status,
			__entry->eof ? " eof" : ""
		)
);

TRACE_EVENT(nfs_pgio_error,
	TP_PROTO(
		स्थिर काष्ठा nfs_pgio_header *hdr,
		पूर्णांक error,
		loff_t pos
	),

	TP_ARGS(hdr, error, pos),

	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(u32, fhandle)
		__field(u64, fileid)
		__field(loff_t, offset)
		__field(u32, arg_count)
		__field(u32, res_count)
		__field(loff_t, pos)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		स्थिर काष्ठा inode *inode = hdr->inode;
		स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
		स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
					  hdr->args.fh : &nfsi->fh;

		__entry->status = error;
		__entry->offset = hdr->args.offset;
		__entry->arg_count = hdr->args.count;
		__entry->res_count = hdr->res.count;
		__entry->dev = inode->i_sb->s_dev;
		__entry->fileid = nfsi->fileid;
		__entry->fhandle = nfs_fhandle_hash(fh);
	),

	TP_prपूर्णांकk("fileid=%02x:%02x:%llu fhandle=0x%08x "
		  "offset=%lld count=%u res=%u pos=%llu status=%d",
		MAJOR(__entry->dev), MINOR(__entry->dev),
		(अचिन्हित दीर्घ दीर्घ)__entry->fileid, __entry->fhandle,
		(दीर्घ दीर्घ)__entry->offset, __entry->arg_count, __entry->res_count,
		__entry->pos, __entry->status
	)
);

TRACE_DEFINE_ENUM(NFS_UNSTABLE);
TRACE_DEFINE_ENUM(NFS_DATA_SYNC);
TRACE_DEFINE_ENUM(NFS_खाता_SYNC);

#घोषणा nfs_show_stable(stable) \
	__prपूर्णांक_symbolic(stable, \
			अणु NFS_UNSTABLE, "UNSTABLE" पूर्ण, \
			अणु NFS_DATA_SYNC, "DATA_SYNC" पूर्ण, \
			अणु NFS_खाता_SYNC, "FILE_SYNC" पूर्ण)

TRACE_EVENT(nfs_initiate_ग_लिखो,
		TP_PROTO(
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(hdr),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, count)
			__field(क्रमागत nfs3_stable_how, stable)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;

			__entry->offset = hdr->args.offset;
			__entry->count = hdr->args.count;
			__entry->stable = hdr->args.stable;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u stable=%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->count,
			nfs_show_stable(__entry->stable)
		)
);

TRACE_EVENT(nfs_ग_लिखोback_करोne,
		TP_PROTO(
			स्थिर काष्ठा rpc_task *task,
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(task, hdr),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, arg_count)
			__field(u32, res_count)
			__field(पूर्णांक, status)
			__field(क्रमागत nfs3_stable_how, stable)
			__array(अक्षर, verअगरier, NFS4_VERIFIER_SIZE)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;
			स्थिर काष्ठा nfs_ग_लिखोverf *verf = hdr->res.verf;

			__entry->status = task->tk_status;
			__entry->offset = hdr->args.offset;
			__entry->arg_count = hdr->args.count;
			__entry->res_count = hdr->res.count;
			__entry->stable = verf->committed;
			स_नकल(__entry->verअगरier,
				&verf->verअगरier,
				NFS4_VERIFIER_SIZE);
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u res=%u status=%d stable=%s "
			"verifier=%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->arg_count,
			__entry->res_count, __entry->status,
			nfs_show_stable(__entry->stable),
			__prपूर्णांक_hex_str(__entry->verअगरier, NFS4_VERIFIER_SIZE)
		)
);

DECLARE_EVENT_CLASS(nfs_page_error_class,
		TP_PROTO(
			स्थिर काष्ठा nfs_page *req,
			पूर्णांक error
		),

		TP_ARGS(req, error),

		TP_STRUCT__entry(
			__field(स्थिर व्योम *, req)
			__field(pgoff_t, index)
			__field(अचिन्हित पूर्णांक, offset)
			__field(अचिन्हित पूर्णांक, pgbase)
			__field(अचिन्हित पूर्णांक, bytes)
			__field(पूर्णांक, error)
		),

		TP_fast_assign(
			__entry->req = req;
			__entry->index = req->wb_index;
			__entry->offset = req->wb_offset;
			__entry->pgbase = req->wb_pgbase;
			__entry->bytes = req->wb_bytes;
			__entry->error = error;
		),

		TP_prपूर्णांकk(
			"req=%p index=%lu offset=%u pgbase=%u bytes=%u error=%d",
			__entry->req, __entry->index, __entry->offset,
			__entry->pgbase, __entry->bytes, __entry->error
		)
);

#घोषणा DEFINE_NFS_PAGEERR_EVENT(name) \
	DEFINE_EVENT(nfs_page_error_class, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_page *req, \
				पूर्णांक error \
			), \
			TP_ARGS(req, error))

DEFINE_NFS_PAGEERR_EVENT(nfs_ग_लिखो_error);
DEFINE_NFS_PAGEERR_EVENT(nfs_comp_error);
DEFINE_NFS_PAGEERR_EVENT(nfs_commit_error);

TRACE_EVENT(nfs_initiate_commit,
		TP_PROTO(
			स्थिर काष्ठा nfs_commit_data *data
		),

		TP_ARGS(data),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, count)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = data->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = data->args.fh ?
						  data->args.fh : &nfsi->fh;

			__entry->offset = data->args.offset;
			__entry->count = data->args.count;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->count
		)
);

TRACE_EVENT(nfs_commit_करोne,
		TP_PROTO(
			स्थिर काष्ठा rpc_task *task,
			स्थिर काष्ठा nfs_commit_data *data
		),

		TP_ARGS(task, data),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(पूर्णांक, status)
			__field(क्रमागत nfs3_stable_how, stable)
			__array(अक्षर, verअगरier, NFS4_VERIFIER_SIZE)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = data->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = data->args.fh ?
						  data->args.fh : &nfsi->fh;
			स्थिर काष्ठा nfs_ग_लिखोverf *verf = data->res.verf;

			__entry->status = task->tk_status;
			__entry->offset = data->args.offset;
			__entry->stable = verf->committed;
			स_नकल(__entry->verअगरier,
				&verf->verअगरier,
				NFS4_VERIFIER_SIZE);
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld status=%d stable=%s verifier=%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset, __entry->status,
			nfs_show_stable(__entry->stable),
			__prपूर्णांक_hex_str(__entry->verअगरier, NFS4_VERIFIER_SIZE)
		)
);

TRACE_EVENT(nfs_fh_to_dentry,
		TP_PROTO(
			स्थिर काष्ठा super_block *sb,
			स्थिर काष्ठा nfs_fh *fh,
			u64 fileid,
			पूर्णांक error
		),

		TP_ARGS(sb, fh, fileid, error),

		TP_STRUCT__entry(
			__field(पूर्णांक, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
		),

		TP_fast_assign(
			__entry->error = error;
			__entry->dev = sb->s_dev;
			__entry->fileid = fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
		),

		TP_prपूर्णांकk(
			"error=%d fileid=%02x:%02x:%llu fhandle=0x%08x ",
			__entry->error,
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle
		)
);

TRACE_DEFINE_ENUM(NFS_OK);
TRACE_DEFINE_ENUM(NFSERR_PERM);
TRACE_DEFINE_ENUM(NFSERR_NOENT);
TRACE_DEFINE_ENUM(NFSERR_IO);
TRACE_DEFINE_ENUM(NFSERR_NXIO);
TRACE_DEFINE_ENUM(ECHILD);
TRACE_DEFINE_ENUM(NFSERR_EAGAIN);
TRACE_DEFINE_ENUM(NFSERR_ACCES);
TRACE_DEFINE_ENUM(NFSERR_EXIST);
TRACE_DEFINE_ENUM(NFSERR_XDEV);
TRACE_DEFINE_ENUM(NFSERR_NODEV);
TRACE_DEFINE_ENUM(NFSERR_NOTसूची);
TRACE_DEFINE_ENUM(NFSERR_ISसूची);
TRACE_DEFINE_ENUM(NFSERR_INVAL);
TRACE_DEFINE_ENUM(NFSERR_FBIG);
TRACE_DEFINE_ENUM(NFSERR_NOSPC);
TRACE_DEFINE_ENUM(NFSERR_ROFS);
TRACE_DEFINE_ENUM(NFSERR_MLINK);
TRACE_DEFINE_ENUM(NFSERR_OPNOTSUPP);
TRACE_DEFINE_ENUM(NFSERR_NAMETOOLONG);
TRACE_DEFINE_ENUM(NFSERR_NOTEMPTY);
TRACE_DEFINE_ENUM(NFSERR_DQUOT);
TRACE_DEFINE_ENUM(NFSERR_STALE);
TRACE_DEFINE_ENUM(NFSERR_REMOTE);
TRACE_DEFINE_ENUM(NFSERR_WFLUSH);
TRACE_DEFINE_ENUM(NFSERR_BADHANDLE);
TRACE_DEFINE_ENUM(NFSERR_NOT_SYNC);
TRACE_DEFINE_ENUM(NFSERR_BAD_COOKIE);
TRACE_DEFINE_ENUM(NFSERR_NOTSUPP);
TRACE_DEFINE_ENUM(NFSERR_TOOSMALL);
TRACE_DEFINE_ENUM(NFSERR_SERVERFAULT);
TRACE_DEFINE_ENUM(NFSERR_BADTYPE);
TRACE_DEFINE_ENUM(NFSERR_JUKEBOX);

#घोषणा nfs_show_status(x) \
	__prपूर्णांक_symbolic(x, \
			अणु NFS_OK, "OK" पूर्ण, \
			अणु NFSERR_PERM, "PERM" पूर्ण, \
			अणु NFSERR_NOENT, "NOENT" पूर्ण, \
			अणु NFSERR_IO, "IO" पूर्ण, \
			अणु NFSERR_NXIO, "NXIO" पूर्ण, \
			अणु ECHILD, "CHILD" पूर्ण, \
			अणु NFSERR_EAGAIN, "AGAIN" पूर्ण, \
			अणु NFSERR_ACCES, "ACCES" पूर्ण, \
			अणु NFSERR_EXIST, "EXIST" पूर्ण, \
			अणु NFSERR_XDEV, "XDEV" पूर्ण, \
			अणु NFSERR_NODEV, "NODEV" पूर्ण, \
			अणु NFSERR_NOTसूची, "NOTDIR" पूर्ण, \
			अणु NFSERR_ISसूची, "ISDIR" पूर्ण, \
			अणु NFSERR_INVAL, "INVAL" पूर्ण, \
			अणु NFSERR_FBIG, "FBIG" पूर्ण, \
			अणु NFSERR_NOSPC, "NOSPC" पूर्ण, \
			अणु NFSERR_ROFS, "ROFS" पूर्ण, \
			अणु NFSERR_MLINK, "MLINK" पूर्ण, \
			अणु NFSERR_OPNOTSUPP, "OPNOTSUPP" पूर्ण, \
			अणु NFSERR_NAMETOOLONG, "NAMETOOLONG" पूर्ण, \
			अणु NFSERR_NOTEMPTY, "NOTEMPTY" पूर्ण, \
			अणु NFSERR_DQUOT, "DQUOT" पूर्ण, \
			अणु NFSERR_STALE, "STALE" पूर्ण, \
			अणु NFSERR_REMOTE, "REMOTE" पूर्ण, \
			अणु NFSERR_WFLUSH, "WFLUSH" पूर्ण, \
			अणु NFSERR_BADHANDLE, "BADHANDLE" पूर्ण, \
			अणु NFSERR_NOT_SYNC, "NOTSYNC" पूर्ण, \
			अणु NFSERR_BAD_COOKIE, "BADCOOKIE" पूर्ण, \
			अणु NFSERR_NOTSUPP, "NOTSUPP" पूर्ण, \
			अणु NFSERR_TOOSMALL, "TOOSMALL" पूर्ण, \
			अणु NFSERR_SERVERFAULT, "REMOTEIO" पूर्ण, \
			अणु NFSERR_BADTYPE, "BADTYPE" पूर्ण, \
			अणु NFSERR_JUKEBOX, "JUKEBOX" पूर्ण)

DECLARE_EVENT_CLASS(nfs_xdr_event,
		TP_PROTO(
			स्थिर काष्ठा xdr_stream *xdr,
			पूर्णांक error
		),

		TP_ARGS(xdr, error),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, task_id)
			__field(अचिन्हित पूर्णांक, client_id)
			__field(u32, xid)
			__field(पूर्णांक, version)
			__field(अचिन्हित दीर्घ, error)
			__string(program,
				 xdr->rqst->rq_task->tk_client->cl_program->name)
			__string(procedure,
				 xdr->rqst->rq_task->tk_msg.rpc_proc->p_name)
		),

		TP_fast_assign(
			स्थिर काष्ठा rpc_rqst *rqstp = xdr->rqst;
			स्थिर काष्ठा rpc_task *task = rqstp->rq_task;

			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client->cl_clid;
			__entry->xid = be32_to_cpu(rqstp->rq_xid);
			__entry->version = task->tk_client->cl_vers;
			__entry->error = error;
			__assign_str(program,
				     task->tk_client->cl_program->name)
			__assign_str(procedure, task->tk_msg.rpc_proc->p_name)
		),

		TP_prपूर्णांकk(
			"task:%u@%d xid=0x%08x %sv%d %s error=%ld (%s)",
			__entry->task_id, __entry->client_id, __entry->xid,
			__get_str(program), __entry->version,
			__get_str(procedure), -__entry->error,
			nfs_show_status(__entry->error)
		)
);
#घोषणा DEFINE_NFS_XDR_EVENT(name) \
	DEFINE_EVENT(nfs_xdr_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा xdr_stream *xdr, \
				पूर्णांक error \
			), \
			TP_ARGS(xdr, error))
DEFINE_NFS_XDR_EVENT(nfs_xdr_status);
DEFINE_NFS_XDR_EVENT(nfs_xdr_bad_filehandle);

#पूर्ण_अगर /* _TRACE_NFS_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता nfstrace
/* This part must be outside protection */
#समावेश <trace/define_trace.h>
