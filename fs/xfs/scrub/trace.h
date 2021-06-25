<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM xfs_scrub

#अगर !defined(_TRACE_XFS_SCRUB_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_XFS_SCRUB_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "xfs_bit.h"

/*
 * ftrace's __prपूर्णांक_symbolic requires that all क्रमागत values be wrapped in the
 * TRACE_DEFINE_ENUM macro so that the क्रमागत value can be encoded in the ftrace
 * ring buffer.  Somehow this was only worth mentioning in the ftrace sample
 * code.
 */
TRACE_DEFINE_ENUM(XFS_BTNUM_BNOi);
TRACE_DEFINE_ENUM(XFS_BTNUM_CNTi);
TRACE_DEFINE_ENUM(XFS_BTNUM_BMAPi);
TRACE_DEFINE_ENUM(XFS_BTNUM_INOi);
TRACE_DEFINE_ENUM(XFS_BTNUM_FINOi);
TRACE_DEFINE_ENUM(XFS_BTNUM_RMAPi);
TRACE_DEFINE_ENUM(XFS_BTNUM_REFCi);

TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_PROBE);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_SB);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_AGF);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_AGFL);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_AGI);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_BNOBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_CNTBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_INOBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_FINOBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_RMAPBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_REFCNTBT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_INODE);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_BMBTD);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_BMBTA);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_BMBTC);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_सूची);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_XATTR);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_SYMLINK);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_PARENT);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_RTBITMAP);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_RTSUM);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_UQUOTA);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_GQUOTA);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_PQUOTA);
TRACE_DEFINE_ENUM(XFS_SCRUB_TYPE_FSCOUNTERS);

#घोषणा XFS_SCRUB_TYPE_STRINGS \
	अणु XFS_SCRUB_TYPE_PROBE,		"probe" पूर्ण, \
	अणु XFS_SCRUB_TYPE_SB,		"sb" पूर्ण, \
	अणु XFS_SCRUB_TYPE_AGF,		"agf" पूर्ण, \
	अणु XFS_SCRUB_TYPE_AGFL,		"agfl" पूर्ण, \
	अणु XFS_SCRUB_TYPE_AGI,		"agi" पूर्ण, \
	अणु XFS_SCRUB_TYPE_BNOBT,		"bnobt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_CNTBT,		"cntbt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_INOBT,		"inobt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_FINOBT,	"finobt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_RMAPBT,	"rmapbt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_REFCNTBT,	"refcountbt" पूर्ण, \
	अणु XFS_SCRUB_TYPE_INODE,		"inode" पूर्ण, \
	अणु XFS_SCRUB_TYPE_BMBTD,		"bmapbtd" पूर्ण, \
	अणु XFS_SCRUB_TYPE_BMBTA,		"bmapbta" पूर्ण, \
	अणु XFS_SCRUB_TYPE_BMBTC,		"bmapbtc" पूर्ण, \
	अणु XFS_SCRUB_TYPE_सूची,		"directory" पूर्ण, \
	अणु XFS_SCRUB_TYPE_XATTR,		"xattr" पूर्ण, \
	अणु XFS_SCRUB_TYPE_SYMLINK,	"symlink" पूर्ण, \
	अणु XFS_SCRUB_TYPE_PARENT,	"parent" पूर्ण, \
	अणु XFS_SCRUB_TYPE_RTBITMAP,	"rtbitmap" पूर्ण, \
	अणु XFS_SCRUB_TYPE_RTSUM,		"rtsummary" पूर्ण, \
	अणु XFS_SCRUB_TYPE_UQUOTA,	"usrquota" पूर्ण, \
	अणु XFS_SCRUB_TYPE_GQUOTA,	"grpquota" पूर्ण, \
	अणु XFS_SCRUB_TYPE_PQUOTA,	"prjquota" पूर्ण, \
	अणु XFS_SCRUB_TYPE_FSCOUNTERS,	"fscounters" पूर्ण

DECLARE_EVENT_CLASS(xchk_class,
	TP_PROTO(काष्ठा xfs_inode *ip, काष्ठा xfs_scrub_metadata *sm,
		 पूर्णांक error),
	TP_ARGS(ip, sm, error),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_agnumber_t, agno)
		__field(xfs_ino_t, inum)
		__field(अचिन्हित पूर्णांक, gen)
		__field(अचिन्हित पूर्णांक, flags)
		__field(पूर्णांक, error)
	),
	TP_fast_assign(
		__entry->dev = ip->i_mount->m_super->s_dev;
		__entry->ino = ip->i_ino;
		__entry->type = sm->sm_type;
		__entry->agno = sm->sm_agno;
		__entry->inum = sm->sm_ino;
		__entry->gen = sm->sm_gen;
		__entry->flags = sm->sm_flags;
		__entry->error = error;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx type %s agno %u inum %llu gen %u flags 0x%x error %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->agno,
		  __entry->inum,
		  __entry->gen,
		  __entry->flags,
		  __entry->error)
)
#घोषणा DEFINE_SCRUB_EVENT(name) \
DEFINE_EVENT(xchk_class, name, \
	TP_PROTO(काष्ठा xfs_inode *ip, काष्ठा xfs_scrub_metadata *sm, \
		 पूर्णांक error), \
	TP_ARGS(ip, sm, error))

DEFINE_SCRUB_EVENT(xchk_start);
DEFINE_SCRUB_EVENT(xchk_करोne);
DEFINE_SCRUB_EVENT(xchk_deadlock_retry);
DEFINE_SCRUB_EVENT(xrep_attempt);
DEFINE_SCRUB_EVENT(xrep_करोne);

TRACE_EVENT(xchk_op_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, xfs_agnumber_t agno,
		 xfs_agblock_t bno, पूर्णांक error, व्योम *ret_ip),
	TP_ARGS(sc, agno, bno, error, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, error)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->agno = agno;
		__entry->bno = bno;
		__entry->error = error;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s agno %u agbno %u error %d ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->agno,
		  __entry->bno,
		  __entry->error,
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_file_op_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		 xfs_fileoff_t offset, पूर्णांक error, व्योम *ret_ip),
	TP_ARGS(sc, whichविभाजन, offset, error, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(पूर्णांक, whichविभाजन)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_fileoff_t, offset)
		__field(पूर्णांक, error)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->ip->i_mount->m_super->s_dev;
		__entry->ino = sc->ip->i_ino;
		__entry->whichविभाजन = whichविभाजन;
		__entry->type = sc->sm->sm_type;
		__entry->offset = offset;
		__entry->error = error;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx fork %d type %s offset %llu error %d ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->whichविभाजन,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->offset,
		  __entry->error,
		  __entry->ret_ip)
);

DECLARE_EVENT_CLASS(xchk_block_error_class,
	TP_PROTO(काष्ठा xfs_scrub *sc, xfs_daddr_t daddr, व्योम *ret_ip),
	TP_ARGS(sc, daddr, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		xfs_fsblock_t	fsbno;
		xfs_agnumber_t	agno;
		xfs_agblock_t	bno;

		fsbno = XFS_DADDR_TO_FSB(sc->mp, daddr);
		agno = XFS_FSB_TO_AGNO(sc->mp, fsbno);
		bno = XFS_FSB_TO_AGBNO(sc->mp, fsbno);

		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->agno = agno;
		__entry->bno = bno;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s agno %u agbno %u ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->agno,
		  __entry->bno,
		  __entry->ret_ip)
)

#घोषणा DEFINE_SCRUB_BLOCK_ERROR_EVENT(name) \
DEFINE_EVENT(xchk_block_error_class, name, \
	TP_PROTO(काष्ठा xfs_scrub *sc, xfs_daddr_t daddr, \
		 व्योम *ret_ip), \
	TP_ARGS(sc, daddr, ret_ip))

DEFINE_SCRUB_BLOCK_ERROR_EVENT(xchk_fs_error);
DEFINE_SCRUB_BLOCK_ERROR_EVENT(xchk_block_error);
DEFINE_SCRUB_BLOCK_ERROR_EVENT(xchk_block_preen);

DECLARE_EVENT_CLASS(xchk_ino_error_class,
	TP_PROTO(काष्ठा xfs_scrub *sc, xfs_ino_t ino, व्योम *ret_ip),
	TP_ARGS(sc, ino, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(अचिन्हित पूर्णांक, type)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->ino = ino;
		__entry->type = sc->sm->sm_type;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx type %s ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->ret_ip)
)

#घोषणा DEFINE_SCRUB_INO_ERROR_EVENT(name) \
DEFINE_EVENT(xchk_ino_error_class, name, \
	TP_PROTO(काष्ठा xfs_scrub *sc, xfs_ino_t ino, \
		 व्योम *ret_ip), \
	TP_ARGS(sc, ino, ret_ip))

DEFINE_SCRUB_INO_ERROR_EVENT(xchk_ino_error);
DEFINE_SCRUB_INO_ERROR_EVENT(xchk_ino_preen);
DEFINE_SCRUB_INO_ERROR_EVENT(xchk_ino_warning);

DECLARE_EVENT_CLASS(xchk_fblock_error_class,
	TP_PROTO(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		 xfs_fileoff_t offset, व्योम *ret_ip),
	TP_ARGS(sc, whichविभाजन, offset, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(पूर्णांक, whichविभाजन)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_fileoff_t, offset)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->ip->i_mount->m_super->s_dev;
		__entry->ino = sc->ip->i_ino;
		__entry->whichविभाजन = whichविभाजन;
		__entry->type = sc->sm->sm_type;
		__entry->offset = offset;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx fork %d type %s offset %llu ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->whichविभाजन,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->offset,
		  __entry->ret_ip)
);

#घोषणा DEFINE_SCRUB_FBLOCK_ERROR_EVENT(name) \
DEFINE_EVENT(xchk_fblock_error_class, name, \
	TP_PROTO(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन, \
		 xfs_fileoff_t offset, व्योम *ret_ip), \
	TP_ARGS(sc, whichविभाजन, offset, ret_ip))

DEFINE_SCRUB_FBLOCK_ERROR_EVENT(xchk_fblock_error);
DEFINE_SCRUB_FBLOCK_ERROR_EVENT(xchk_fblock_warning);

TRACE_EVENT(xchk_incomplete,
	TP_PROTO(काष्ठा xfs_scrub *sc, व्योम *ret_ip),
	TP_ARGS(sc, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, type)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_btree_op_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		 पूर्णांक level, पूर्णांक error, व्योम *ret_ip),
	TP_ARGS(sc, cur, level, error, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_btnum_t, btnum)
		__field(पूर्णांक, level)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, ptr)
		__field(पूर्णांक, error)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		xfs_fsblock_t fsbno = xchk_btree_cur_fsbno(cur, level);

		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->btnum = cur->bc_btnum;
		__entry->level = level;
		__entry->agno = XFS_FSB_TO_AGNO(cur->bc_mp, fsbno);
		__entry->bno = XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno);
		__entry->ptr = cur->bc_ptrs[level];
		__entry->error = error;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s btree %s level %d ptr %d agno %u agbno %u error %d ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS),
		  __entry->level,
		  __entry->ptr,
		  __entry->agno,
		  __entry->bno,
		  __entry->error,
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_अगरork_btree_op_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		 पूर्णांक level, पूर्णांक error, व्योम *ret_ip),
	TP_ARGS(sc, cur, level, error, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(पूर्णांक, whichविभाजन)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_btnum_t, btnum)
		__field(पूर्णांक, level)
		__field(पूर्णांक, ptr)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, error)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		xfs_fsblock_t fsbno = xchk_btree_cur_fsbno(cur, level);
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->ino = sc->ip->i_ino;
		__entry->whichविभाजन = cur->bc_ino.whichविभाजन;
		__entry->type = sc->sm->sm_type;
		__entry->btnum = cur->bc_btnum;
		__entry->level = level;
		__entry->ptr = cur->bc_ptrs[level];
		__entry->agno = XFS_FSB_TO_AGNO(cur->bc_mp, fsbno);
		__entry->bno = XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno);
		__entry->error = error;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx fork %d type %s btree %s level %d ptr %d agno %u agbno %u error %d ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->whichविभाजन,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS),
		  __entry->level,
		  __entry->ptr,
		  __entry->agno,
		  __entry->bno,
		  __entry->error,
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_btree_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		 पूर्णांक level, व्योम *ret_ip),
	TP_ARGS(sc, cur, level, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_btnum_t, btnum)
		__field(पूर्णांक, level)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, ptr)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		xfs_fsblock_t fsbno = xchk_btree_cur_fsbno(cur, level);
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->btnum = cur->bc_btnum;
		__entry->level = level;
		__entry->agno = XFS_FSB_TO_AGNO(cur->bc_mp, fsbno);
		__entry->bno = XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno);
		__entry->ptr = cur->bc_ptrs[level];
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s btree %s level %d ptr %d agno %u agbno %u ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS),
		  __entry->level,
		  __entry->ptr,
		  __entry->agno,
		  __entry->bno,
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_अगरork_btree_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		 पूर्णांक level, व्योम *ret_ip),
	TP_ARGS(sc, cur, level, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_ino_t, ino)
		__field(पूर्णांक, whichविभाजन)
		__field(अचिन्हित पूर्णांक, type)
		__field(xfs_btnum_t, btnum)
		__field(पूर्णांक, level)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, ptr)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		xfs_fsblock_t fsbno = xchk_btree_cur_fsbno(cur, level);
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->ino = sc->ip->i_ino;
		__entry->whichविभाजन = cur->bc_ino.whichविभाजन;
		__entry->type = sc->sm->sm_type;
		__entry->btnum = cur->bc_btnum;
		__entry->level = level;
		__entry->agno = XFS_FSB_TO_AGNO(cur->bc_mp, fsbno);
		__entry->bno = XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno);
		__entry->ptr = cur->bc_ptrs[level];
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d ino 0x%llx fork %d type %s btree %s level %d ptr %d agno %u agbno %u ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->ino,
		  __entry->whichविभाजन,
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS),
		  __entry->level,
		  __entry->ptr,
		  __entry->agno,
		  __entry->bno,
		  __entry->ret_ip)
);

DECLARE_EVENT_CLASS(xchk_sbtree_class,
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		 पूर्णांक level),
	TP_ARGS(sc, cur, level),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(पूर्णांक, type)
		__field(xfs_btnum_t, btnum)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bno)
		__field(पूर्णांक, level)
		__field(पूर्णांक, nlevels)
		__field(पूर्णांक, ptr)
	),
	TP_fast_assign(
		xfs_fsblock_t fsbno = xchk_btree_cur_fsbno(cur, level);

		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->btnum = cur->bc_btnum;
		__entry->agno = XFS_FSB_TO_AGNO(cur->bc_mp, fsbno);
		__entry->bno = XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno);
		__entry->level = level;
		__entry->nlevels = cur->bc_nlevels;
		__entry->ptr = cur->bc_ptrs[level];
	),
	TP_prपूर्णांकk("dev %d:%d type %s btree %s agno %u agbno %u level %d nlevels %d ptr %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS),
		  __entry->agno,
		  __entry->bno,
		  __entry->level,
		  __entry->nlevels,
		  __entry->ptr)
)
#घोषणा DEFINE_SCRUB_SBTREE_EVENT(name) \
DEFINE_EVENT(xchk_sbtree_class, name, \
	TP_PROTO(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur, \
		 पूर्णांक level), \
	TP_ARGS(sc, cur, level))

DEFINE_SCRUB_SBTREE_EVENT(xchk_btree_rec);
DEFINE_SCRUB_SBTREE_EVENT(xchk_btree_key);

TRACE_EVENT(xchk_xref_error,
	TP_PROTO(काष्ठा xfs_scrub *sc, पूर्णांक error, व्योम *ret_ip),
	TP_ARGS(sc, error, ret_ip),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(पूर्णांक, type)
		__field(पूर्णांक, error)
		__field(व्योम *, ret_ip)
	),
	TP_fast_assign(
		__entry->dev = sc->mp->m_super->s_dev;
		__entry->type = sc->sm->sm_type;
		__entry->error = error;
		__entry->ret_ip = ret_ip;
	),
	TP_prपूर्णांकk("dev %d:%d type %s xref error %d ret_ip %pS",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __prपूर्णांक_symbolic(__entry->type, XFS_SCRUB_TYPE_STRINGS),
		  __entry->error,
		  __entry->ret_ip)
);

TRACE_EVENT(xchk_iallocbt_check_cluster,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agino_t startino, xfs_daddr_t map_daddr,
		 अचिन्हित लघु map_len, अचिन्हित पूर्णांक chunk_ino,
		 अचिन्हित पूर्णांक nr_inodes, uपूर्णांक16_t cluster_mask,
		 uपूर्णांक16_t holemask, अचिन्हित पूर्णांक cluster_ino),
	TP_ARGS(mp, agno, startino, map_daddr, map_len, chunk_ino, nr_inodes,
		cluster_mask, holemask, cluster_ino),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agino_t, startino)
		__field(xfs_daddr_t, map_daddr)
		__field(अचिन्हित लघु, map_len)
		__field(अचिन्हित पूर्णांक, chunk_ino)
		__field(अचिन्हित पूर्णांक, nr_inodes)
		__field(अचिन्हित पूर्णांक, cluster_ino)
		__field(uपूर्णांक16_t, cluster_mask)
		__field(uपूर्णांक16_t, holemask)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->startino = startino;
		__entry->map_daddr = map_daddr;
		__entry->map_len = map_len;
		__entry->chunk_ino = chunk_ino;
		__entry->nr_inodes = nr_inodes;
		__entry->cluster_mask = cluster_mask;
		__entry->holemask = holemask;
		__entry->cluster_ino = cluster_ino;
	),
	TP_prपूर्णांकk("dev %d:%d agno %d startino %u daddr 0x%llx len %d chunkino %u nr_inodes %u cluster_mask 0x%x holemask 0x%x cluster_ino %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->startino,
		  __entry->map_daddr,
		  __entry->map_len,
		  __entry->chunk_ino,
		  __entry->nr_inodes,
		  __entry->cluster_mask,
		  __entry->holemask,
		  __entry->cluster_ino)
)

TRACE_EVENT(xchk_fscounters_calc,
	TP_PROTO(काष्ठा xfs_mount *mp, uपूर्णांक64_t icount, uपूर्णांक64_t अगरree,
		 uपूर्णांक64_t fdblocks, uपूर्णांक64_t delalloc),
	TP_ARGS(mp, icount, अगरree, fdblocks, delalloc),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(पूर्णांक64_t, icount_sb)
		__field(uपूर्णांक64_t, icount_calculated)
		__field(पूर्णांक64_t, अगरree_sb)
		__field(uपूर्णांक64_t, अगरree_calculated)
		__field(पूर्णांक64_t, fdblocks_sb)
		__field(uपूर्णांक64_t, fdblocks_calculated)
		__field(uपूर्णांक64_t, delalloc)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->icount_sb = mp->m_sb.sb_icount;
		__entry->icount_calculated = icount;
		__entry->अगरree_sb = mp->m_sb.sb_अगरree;
		__entry->अगरree_calculated = अगरree;
		__entry->fdblocks_sb = mp->m_sb.sb_fdblocks;
		__entry->fdblocks_calculated = fdblocks;
		__entry->delalloc = delalloc;
	),
	TP_prपूर्णांकk("dev %d:%d icount %lld:%llu ifree %lld::%llu fdblocks %lld::%llu delalloc %llu",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->icount_sb,
		  __entry->icount_calculated,
		  __entry->अगरree_sb,
		  __entry->अगरree_calculated,
		  __entry->fdblocks_sb,
		  __entry->fdblocks_calculated,
		  __entry->delalloc)
)

TRACE_EVENT(xchk_fscounters_within_range,
	TP_PROTO(काष्ठा xfs_mount *mp, uपूर्णांक64_t expected, पूर्णांक64_t curr_value,
		 पूर्णांक64_t old_value),
	TP_ARGS(mp, expected, curr_value, old_value),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(uपूर्णांक64_t, expected)
		__field(पूर्णांक64_t, curr_value)
		__field(पूर्णांक64_t, old_value)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->expected = expected;
		__entry->curr_value = curr_value;
		__entry->old_value = old_value;
	),
	TP_prपूर्णांकk("dev %d:%d expected %llu curr_value %lld old_value %lld",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->expected,
		  __entry->curr_value,
		  __entry->old_value)
)

/* repair tracepoपूर्णांकs */
#अगर IS_ENABLED(CONFIG_XFS_ONLINE_REPAIR)

DECLARE_EVENT_CLASS(xrep_extent_class,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agblock_t agbno, xfs_extlen_t len),
	TP_ARGS(mp, agno, agbno, len),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, agbno)
		__field(xfs_extlen_t, len)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->agbno = agbno;
		__entry->len = len;
	),
	TP_prपूर्णांकk("dev %d:%d agno %u agbno %u len %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->agbno,
		  __entry->len)
);
#घोषणा DEFINE_REPAIR_EXTENT_EVENT(name) \
DEFINE_EVENT(xrep_extent_class, name, \
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno, \
		 xfs_agblock_t agbno, xfs_extlen_t len), \
	TP_ARGS(mp, agno, agbno, len))
DEFINE_REPAIR_EXTENT_EVENT(xrep_dispose_btree_extent);
DEFINE_REPAIR_EXTENT_EVENT(xrep_agfl_insert);

DECLARE_EVENT_CLASS(xrep_rmap_class,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agblock_t agbno, xfs_extlen_t len,
		 uपूर्णांक64_t owner, uपूर्णांक64_t offset, अचिन्हित पूर्णांक flags),
	TP_ARGS(mp, agno, agbno, len, owner, offset, flags),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, agbno)
		__field(xfs_extlen_t, len)
		__field(uपूर्णांक64_t, owner)
		__field(uपूर्णांक64_t, offset)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->agbno = agbno;
		__entry->len = len;
		__entry->owner = owner;
		__entry->offset = offset;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("dev %d:%d agno %u agbno %u len %u owner %lld offset %llu flags 0x%x",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->agbno,
		  __entry->len,
		  __entry->owner,
		  __entry->offset,
		  __entry->flags)
);
#घोषणा DEFINE_REPAIR_RMAP_EVENT(name) \
DEFINE_EVENT(xrep_rmap_class, name, \
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno, \
		 xfs_agblock_t agbno, xfs_extlen_t len, \
		 uपूर्णांक64_t owner, uपूर्णांक64_t offset, अचिन्हित पूर्णांक flags), \
	TP_ARGS(mp, agno, agbno, len, owner, offset, flags))
DEFINE_REPAIR_RMAP_EVENT(xrep_alloc_extent_fn);
DEFINE_REPAIR_RMAP_EVENT(xrep_ialloc_extent_fn);
DEFINE_REPAIR_RMAP_EVENT(xrep_rmap_extent_fn);
DEFINE_REPAIR_RMAP_EVENT(xrep_bmap_extent_fn);

TRACE_EVENT(xrep_refcount_extent_fn,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 काष्ठा xfs_refcount_irec *irec),
	TP_ARGS(mp, agno, irec),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, startblock)
		__field(xfs_extlen_t, blockcount)
		__field(xfs_nlink_t, refcount)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->startblock = irec->rc_startblock;
		__entry->blockcount = irec->rc_blockcount;
		__entry->refcount = irec->rc_refcount;
	),
	TP_prपूर्णांकk("dev %d:%d agno %u agbno %u len %u refcount %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->startblock,
		  __entry->blockcount,
		  __entry->refcount)
)

TRACE_EVENT(xrep_init_btblock,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno, xfs_agblock_t agbno,
		 xfs_btnum_t btnum),
	TP_ARGS(mp, agno, agbno, btnum),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, agbno)
		__field(uपूर्णांक32_t, btnum)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->agbno = agbno;
		__entry->btnum = btnum;
	),
	TP_prपूर्णांकk("dev %d:%d agno %u agbno %u btree %s",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->agbno,
		  __prपूर्णांक_symbolic(__entry->btnum, XFS_BTNUM_STRINGS))
)
TRACE_EVENT(xrep_findroot_block,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno, xfs_agblock_t agbno,
		 uपूर्णांक32_t magic, uपूर्णांक16_t level),
	TP_ARGS(mp, agno, agbno, magic, level),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, agbno)
		__field(uपूर्णांक32_t, magic)
		__field(uपूर्णांक16_t, level)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->agbno = agbno;
		__entry->magic = magic;
		__entry->level = level;
	),
	TP_prपूर्णांकk("dev %d:%d agno %u agbno %u magic 0x%x level %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->agbno,
		  __entry->magic,
		  __entry->level)
)
TRACE_EVENT(xrep_calc_ag_resblks,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agino_t icount, xfs_agblock_t aglen, xfs_agblock_t मुक्तlen,
		 xfs_agblock_t usedlen),
	TP_ARGS(mp, agno, icount, aglen, मुक्तlen, usedlen),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agino_t, icount)
		__field(xfs_agblock_t, aglen)
		__field(xfs_agblock_t, मुक्तlen)
		__field(xfs_agblock_t, usedlen)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->icount = icount;
		__entry->aglen = aglen;
		__entry->मुक्तlen = मुक्तlen;
		__entry->usedlen = usedlen;
	),
	TP_prपूर्णांकk("dev %d:%d agno %d icount %u aglen %u freelen %u usedlen %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->icount,
		  __entry->aglen,
		  __entry->मुक्तlen,
		  __entry->usedlen)
)
TRACE_EVENT(xrep_calc_ag_resblks_btsize,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agblock_t bnobt_sz, xfs_agblock_t inobt_sz,
		 xfs_agblock_t rmapbt_sz, xfs_agblock_t refcbt_sz),
	TP_ARGS(mp, agno, bnobt_sz, inobt_sz, rmapbt_sz, refcbt_sz),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agblock_t, bnobt_sz)
		__field(xfs_agblock_t, inobt_sz)
		__field(xfs_agblock_t, rmapbt_sz)
		__field(xfs_agblock_t, refcbt_sz)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->bnobt_sz = bnobt_sz;
		__entry->inobt_sz = inobt_sz;
		__entry->rmapbt_sz = rmapbt_sz;
		__entry->refcbt_sz = refcbt_sz;
	),
	TP_prपूर्णांकk("dev %d:%d agno %d bno %u ino %u rmap %u refcount %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->bnobt_sz,
		  __entry->inobt_sz,
		  __entry->rmapbt_sz,
		  __entry->refcbt_sz)
)
TRACE_EVENT(xrep_reset_counters,
	TP_PROTO(काष्ठा xfs_mount *mp),
	TP_ARGS(mp),
	TP_STRUCT__entry(
		__field(dev_t, dev)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
	),
	TP_prपूर्णांकk("dev %d:%d",
		  MAJOR(__entry->dev), MINOR(__entry->dev))
)

TRACE_EVENT(xrep_ialloc_insert,
	TP_PROTO(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		 xfs_agino_t startino, uपूर्णांक16_t holemask, uपूर्णांक8_t count,
		 uपूर्णांक8_t मुक्तcount, uपूर्णांक64_t मुक्तmask),
	TP_ARGS(mp, agno, startino, holemask, count, मुक्तcount, मुक्तmask),
	TP_STRUCT__entry(
		__field(dev_t, dev)
		__field(xfs_agnumber_t, agno)
		__field(xfs_agino_t, startino)
		__field(uपूर्णांक16_t, holemask)
		__field(uपूर्णांक8_t, count)
		__field(uपूर्णांक8_t, मुक्तcount)
		__field(uपूर्णांक64_t, मुक्तmask)
	),
	TP_fast_assign(
		__entry->dev = mp->m_super->s_dev;
		__entry->agno = agno;
		__entry->startino = startino;
		__entry->holemask = holemask;
		__entry->count = count;
		__entry->मुक्तcount = मुक्तcount;
		__entry->मुक्तmask = मुक्तmask;
	),
	TP_prपूर्णांकk("dev %d:%d agno %d startino %u holemask 0x%x count %u freecount %u freemask 0x%llx",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->agno,
		  __entry->startino,
		  __entry->holemask,
		  __entry->count,
		  __entry->मुक्तcount,
		  __entry->मुक्तmask)
)

#पूर्ण_अगर /* IS_ENABLED(CONFIG_XFS_ONLINE_REPAIR) */

#पूर्ण_अगर /* _TRACE_XFS_SCRUB_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता scrub/trace
#समावेश <trace/define_trace.h>
