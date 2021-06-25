<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ocfs2

#अगर !defined(_TRACE_OCFS2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_OCFS2_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(ocfs2__पूर्णांक,
	TP_PROTO(पूर्णांक num),
	TP_ARGS(num),
	TP_STRUCT__entry(
		__field(पूर्णांक, num)
	),
	TP_fast_assign(
		__entry->num = num;
	),
	TP_prपूर्णांकk("%d", __entry->num)
);

#घोषणा DEFINE_OCFS2_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__पूर्णांक, name,	\
	TP_PROTO(पूर्णांक num),	\
	TP_ARGS(num))

DECLARE_EVENT_CLASS(ocfs2__uपूर्णांक,
	TP_PROTO(अचिन्हित पूर्णांक num),
	TP_ARGS(num),
	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	num		)
	),
	TP_fast_assign(
		__entry->num	= 	num;
	),
	TP_prपूर्णांकk("%u", __entry->num)
);

#घोषणा DEFINE_OCFS2_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित पूर्णांक num),	\
	TP_ARGS(num))

DECLARE_EVENT_CLASS(ocfs2__ull,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno),
	TP_ARGS(blkno),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
	),
	TP_fast_assign(
		__entry->blkno = blkno;
	),
	TP_prपूर्णांकk("%llu", __entry->blkno)
);

#घोषणा DEFINE_OCFS2_ULL_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ num),	\
	TP_ARGS(num))

DECLARE_EVENT_CLASS(ocfs2__poपूर्णांकer,
	TP_PROTO(व्योम *poपूर्णांकer),
	TP_ARGS(poपूर्णांकer),
	TP_STRUCT__entry(
		__field(व्योम *, poपूर्णांकer)
	),
	TP_fast_assign(
		__entry->poपूर्णांकer = poपूर्णांकer;
	),
	TP_prपूर्णांकk("%p", __entry->poपूर्णांकer)
);

#घोषणा DEFINE_OCFS2_POINTER_EVENT(name)	\
DEFINE_EVENT(ocfs2__poपूर्णांकer, name,	\
	TP_PROTO(व्योम *poपूर्णांकer),	\
	TP_ARGS(poपूर्णांकer))

DECLARE_EVENT_CLASS(ocfs2__string,
	TP_PROTO(स्थिर अक्षर *name),
	TP_ARGS(name),
	TP_STRUCT__entry(
		__string(name,name)
	),
	TP_fast_assign(
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%s", __get_str(name))
);

#घोषणा DEFINE_OCFS2_STRING_EVENT(name)	\
DEFINE_EVENT(ocfs2__string, name,	\
	TP_PROTO(स्थिर अक्षर *name),	\
	TP_ARGS(name))

DECLARE_EVENT_CLASS(ocfs2__पूर्णांक_पूर्णांक,
	TP_PROTO(पूर्णांक value1, पूर्णांक value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(पूर्णांक, value1)
		__field(पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->value1	= value1;
		__entry->value2	= value2;
	),
	TP_prपूर्णांकk("%d %d", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_INT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__पूर्णांक_पूर्णांक, name,	\
	TP_PROTO(पूर्णांक val1, पूर्णांक val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__uपूर्णांक_पूर्णांक,
	TP_PROTO(अचिन्हित पूर्णांक value1, पूर्णांक value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, value1)
		__field(पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->value1	= value1;
		__entry->value2	= value2;
	),
	TP_prपूर्णांकk("%u %d", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_UINT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uपूर्णांक_पूर्णांक, name,	\
	TP_PROTO(अचिन्हित पूर्णांक val1, पूर्णांक val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__uपूर्णांक_uपूर्णांक,
	TP_PROTO(अचिन्हित पूर्णांक value1, अचिन्हित पूर्णांक value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, value1)
		__field(अचिन्हित पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
	),
	TP_prपूर्णांकk("%u %u", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uपूर्णांक_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित पूर्णांक val1, अचिन्हित पूर्णांक val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__ull_uपूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1, अचिन्हित पूर्णांक value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
	),
	TP_prपूर्णांकk("%llu %u", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_ULL_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ val1, अचिन्हित पूर्णांक val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__ull_पूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1, पूर्णांक value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->value1	= value1;
		__entry->value2	= value2;
	),
	TP_prपूर्णांकk("%llu %d", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_ULL_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_पूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ val1, पूर्णांक val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__ull_ull,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1, अचिन्हित दीर्घ दीर्घ value2),
	TP_ARGS(value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित दीर्घ दीर्घ, value2)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
	),
	TP_prपूर्णांकk("%llu %llu", __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_ULL_ULL_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_ull, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ val1, अचिन्हित दीर्घ दीर्घ val2),	\
	TP_ARGS(val1, val2))

DECLARE_EVENT_CLASS(ocfs2__ull_ull_uपूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1,
		 अचिन्हित दीर्घ दीर्घ value2, अचिन्हित पूर्णांक value3),
	TP_ARGS(value1, value2, value3),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित दीर्घ दीर्घ, value2)
		__field(अचिन्हित पूर्णांक, value3)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
		__entry->value3 = value3;
	),
	TP_prपूर्णांकk("%llu %llu %u",
		  __entry->value1, __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_ULL_ULL_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_ull_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ val1,	\
		 अचिन्हित दीर्घ दीर्घ val2, अचिन्हित पूर्णांक val3),	\
	TP_ARGS(val1, val2, val3))

DECLARE_EVENT_CLASS(ocfs2__ull_uपूर्णांक_uपूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1,
		 अचिन्हित पूर्णांक value2, अचिन्हित पूर्णांक value3),
	TP_ARGS(value1, value2, value3),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित पूर्णांक, value2)
		__field(अचिन्हित पूर्णांक, value3)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
		__entry->value3	= value3;
	),
	TP_prपूर्णांकk("%llu %u %u", __entry->value1,
		  __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_ULL_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_uपूर्णांक_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ val1,	\
		 अचिन्हित पूर्णांक val2, अचिन्हित पूर्णांक val3),	\
	TP_ARGS(val1, val2, val3))

DECLARE_EVENT_CLASS(ocfs2__uपूर्णांक_uपूर्णांक_uपूर्णांक,
	TP_PROTO(अचिन्हित पूर्णांक value1, अचिन्हित पूर्णांक value2,
		 अचिन्हित पूर्णांक value3),
	TP_ARGS(value1, value2, value3),
	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	value1		)
		__field(	अचिन्हित पूर्णांक,	value2		)
		__field(	अचिन्हित पूर्णांक,	value3		)
	),
	TP_fast_assign(
		__entry->value1	= 	value1;
		__entry->value2	= 	value2;
		__entry->value3	= 	value3;
	),
	TP_prपूर्णांकk("%u %u %u", __entry->value1, __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_UINT_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__uपूर्णांक_uपूर्णांक_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित पूर्णांक value1, अचिन्हित पूर्णांक value2,	\
		 अचिन्हित पूर्णांक value3),	\
	TP_ARGS(value1, value2, value3))

DECLARE_EVENT_CLASS(ocfs2__ull_ull_ull,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1,
		 अचिन्हित दीर्घ दीर्घ value2, अचिन्हित दीर्घ दीर्घ value3),
	TP_ARGS(value1, value2, value3),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित दीर्घ दीर्घ, value2)
		__field(अचिन्हित दीर्घ दीर्घ, value3)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
		__entry->value3 = value3;
	),
	TP_prपूर्णांकk("%llu %llu %llu",
		  __entry->value1, __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_ULL_ULL_ULL_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_ull_ull, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1, अचिन्हित दीर्घ दीर्घ value2,	\
		 अचिन्हित दीर्घ दीर्घ value3),	\
	TP_ARGS(value1, value2, value3))

DECLARE_EVENT_CLASS(ocfs2__ull_पूर्णांक_पूर्णांक_पूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ull, पूर्णांक value1, पूर्णांक value2, पूर्णांक value3),
	TP_ARGS(ull, value1, value2, value3),
	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ दीर्घ,	ull	)
		__field(	पूर्णांक,	value1			)
		__field(	पूर्णांक,	value2			)
		__field(	पूर्णांक,	value3			)
	),
	TP_fast_assign(
		__entry->ull		= ull;
		__entry->value1		= value1;
		__entry->value2		= value2;
		__entry->value3		= value3;
	),
	TP_prपूर्णांकk("%llu %d %d %d",
		  __entry->ull, __entry->value1,
		  __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_पूर्णांक_पूर्णांक_पूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ull, पूर्णांक value1,	\
		 पूर्णांक value2, पूर्णांक value3),	\
	TP_ARGS(ull, value1, value2, value3))

DECLARE_EVENT_CLASS(ocfs2__ull_uपूर्णांक_uपूर्णांक_uपूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ull, अचिन्हित पूर्णांक value1,
		 अचिन्हित पूर्णांक value2, अचिन्हित पूर्णांक value3),
	TP_ARGS(ull, value1, value2, value3),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ull)
		__field(अचिन्हित पूर्णांक, value1)
		__field(अचिन्हित पूर्णांक, value2)
		__field(अचिन्हित पूर्णांक, value3)
	),
	TP_fast_assign(
		__entry->ull = ull;
		__entry->value1 = value1;
		__entry->value2	= value2;
		__entry->value3	= value3;
	),
	TP_prपूर्णांकk("%llu %u %u %u",
		  __entry->ull, __entry->value1,
		  __entry->value2, __entry->value3)
);

#घोषणा DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_uपूर्णांक_uपूर्णांक_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ull, अचिन्हित पूर्णांक value1,	\
		 अचिन्हित पूर्णांक value2, अचिन्हित पूर्णांक value3),	\
	TP_ARGS(ull, value1, value2, value3))

DECLARE_EVENT_CLASS(ocfs2__ull_ull_uपूर्णांक_uपूर्णांक,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ value1, अचिन्हित दीर्घ दीर्घ value2,
		 अचिन्हित पूर्णांक value3, अचिन्हित पूर्णांक value4),
	TP_ARGS(value1, value2, value3, value4),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, value1)
		__field(अचिन्हित दीर्घ दीर्घ, value2)
		__field(अचिन्हित पूर्णांक, value3)
		__field(अचिन्हित पूर्णांक, value4)
	),
	TP_fast_assign(
		__entry->value1 = value1;
		__entry->value2 = value2;
		__entry->value3 = value3;
		__entry->value4 = value4;
	),
	TP_prपूर्णांकk("%llu %llu %u %u",
		  __entry->value1, __entry->value2,
		  __entry->value3, __entry->value4)
);

#घोषणा DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(name)	\
DEFINE_EVENT(ocfs2__ull_ull_uपूर्णांक_uपूर्णांक, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ull, अचिन्हित दीर्घ दीर्घ ull1,	\
		 अचिन्हित पूर्णांक value2, अचिन्हित पूर्णांक value3),	\
	TP_ARGS(ull, ull1, value2, value3))

/* Trace events क्रम fs/ocfs2/alloc.c. */
DECLARE_EVENT_CLASS(ocfs2__btree_ops,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner,\
		 अचिन्हित पूर्णांक value1, अचिन्हित पूर्णांक value2),
	TP_ARGS(owner, value1, value2),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, owner)
		__field(अचिन्हित पूर्णांक, value1)
		__field(अचिन्हित पूर्णांक, value2)
	),
	TP_fast_assign(
		__entry->owner = owner;
		__entry->value1 = value1;
		__entry->value2	= value2;
	),
	TP_prपूर्णांकk("%llu %u %u",
		  __entry->owner, __entry->value1, __entry->value2)
);

#घोषणा DEFINE_OCFS2_BTREE_EVENT(name)	\
DEFINE_EVENT(ocfs2__btree_ops, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner,	\
		 अचिन्हित पूर्णांक value1, अचिन्हित पूर्णांक value2),	\
	TP_ARGS(owner, value1, value2))

DEFINE_OCFS2_BTREE_EVENT(ocfs2_adjust_righपंचांगost_branch);

DEFINE_OCFS2_BTREE_EVENT(ocfs2_rotate_tree_right);

DEFINE_OCFS2_BTREE_EVENT(ocfs2_append_rec_to_path);

DEFINE_OCFS2_BTREE_EVENT(ocfs2_insert_extent_start);

DEFINE_OCFS2_BTREE_EVENT(ocfs2_add_clusters_in_btree);

DEFINE_OCFS2_INT_EVENT(ocfs2_num_मुक्त_extents);

DEFINE_OCFS2_INT_EVENT(ocfs2_complete_edge_insert);

TRACE_EVENT(ocfs2_grow_tree,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner, पूर्णांक depth),
	TP_ARGS(owner, depth),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, owner)
		__field(पूर्णांक, depth)
	),
	TP_fast_assign(
		__entry->owner = owner;
		__entry->depth = depth;
	),
	TP_prपूर्णांकk("%llu %d", __entry->owner, __entry->depth)
);

TRACE_EVENT(ocfs2_rotate_subtree,
	TP_PROTO(पूर्णांक subtree_root, अचिन्हित दीर्घ दीर्घ blkno,
		 पूर्णांक depth),
	TP_ARGS(subtree_root, blkno, depth),
	TP_STRUCT__entry(
		__field(पूर्णांक, subtree_root)
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
		__field(पूर्णांक, depth)
	),
	TP_fast_assign(
		__entry->subtree_root = subtree_root;
		__entry->blkno = blkno;
		__entry->depth = depth;
	),
	TP_prपूर्णांकk("%d %llu %d", __entry->subtree_root,
		  __entry->blkno, __entry->depth)
);

TRACE_EVENT(ocfs2_insert_extent,
	TP_PROTO(अचिन्हित पूर्णांक ins_appending, अचिन्हित पूर्णांक ins_contig,
		 पूर्णांक ins_contig_index, पूर्णांक मुक्त_records, पूर्णांक ins_tree_depth),
	TP_ARGS(ins_appending, ins_contig, ins_contig_index, मुक्त_records,
		ins_tree_depth),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, ins_appending)
		__field(अचिन्हित पूर्णांक, ins_contig)
		__field(पूर्णांक, ins_contig_index)
		__field(पूर्णांक, मुक्त_records)
		__field(पूर्णांक, ins_tree_depth)
	),
	TP_fast_assign(
		__entry->ins_appending = ins_appending;
		__entry->ins_contig = ins_contig;
		__entry->ins_contig_index = ins_contig_index;
		__entry->मुक्त_records = मुक्त_records;
		__entry->ins_tree_depth = ins_tree_depth;
	),
	TP_prपूर्णांकk("%u %u %d %d %d",
		  __entry->ins_appending, __entry->ins_contig,
		  __entry->ins_contig_index, __entry->मुक्त_records,
		  __entry->ins_tree_depth)
);

TRACE_EVENT(ocfs2_split_extent,
	TP_PROTO(पूर्णांक split_index, अचिन्हित पूर्णांक c_contig_type,
		 अचिन्हित पूर्णांक c_has_empty_extent,
		 अचिन्हित पूर्णांक c_split_covers_rec),
	TP_ARGS(split_index, c_contig_type,
		c_has_empty_extent, c_split_covers_rec),
	TP_STRUCT__entry(
		__field(पूर्णांक, split_index)
		__field(अचिन्हित पूर्णांक, c_contig_type)
		__field(अचिन्हित पूर्णांक, c_has_empty_extent)
		__field(अचिन्हित पूर्णांक, c_split_covers_rec)
	),
	TP_fast_assign(
		__entry->split_index = split_index;
		__entry->c_contig_type = c_contig_type;
		__entry->c_has_empty_extent = c_has_empty_extent;
		__entry->c_split_covers_rec = c_split_covers_rec;
	),
	TP_prपूर्णांकk("%d %u %u %u", __entry->split_index, __entry->c_contig_type,
		  __entry->c_has_empty_extent, __entry->c_split_covers_rec)
);

TRACE_EVENT(ocfs2_हटाओ_extent,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner, अचिन्हित पूर्णांक cpos,
		 अचिन्हित पूर्णांक len, पूर्णांक index,
		 अचिन्हित पूर्णांक e_cpos, अचिन्हित पूर्णांक clusters),
	TP_ARGS(owner, cpos, len, index, e_cpos, clusters),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, owner)
		__field(अचिन्हित पूर्णांक, cpos)
		__field(अचिन्हित पूर्णांक, len)
		__field(पूर्णांक, index)
		__field(अचिन्हित पूर्णांक, e_cpos)
		__field(अचिन्हित पूर्णांक, clusters)
	),
	TP_fast_assign(
		__entry->owner = owner;
		__entry->cpos = cpos;
		__entry->len = len;
		__entry->index = index;
		__entry->e_cpos = e_cpos;
		__entry->clusters = clusters;
	),
	TP_prपूर्णांकk("%llu %u %u %d %u %u",
		  __entry->owner, __entry->cpos, __entry->len, __entry->index,
		  __entry->e_cpos, __entry->clusters)
);

TRACE_EVENT(ocfs2_commit_truncate,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक new_cpos,
		 अचिन्हित पूर्णांक clusters, अचिन्हित पूर्णांक depth),
	TP_ARGS(ino, new_cpos, clusters, depth),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, new_cpos)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित पूर्णांक, depth)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->new_cpos = new_cpos;
		__entry->clusters = clusters;
		__entry->depth = depth;
	),
	TP_prपूर्णांकk("%llu %u %u %u",
		  __entry->ino, __entry->new_cpos,
		  __entry->clusters, __entry->depth)
);

TRACE_EVENT(ocfs2_validate_extent_block,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno),
	TP_ARGS(blkno),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
	),
	TP_fast_assign(
		__entry->blkno = blkno;
	),
	TP_prपूर्णांकk("%llu ", __entry->blkno)
);

TRACE_EVENT(ocfs2_rotate_leaf,
	TP_PROTO(अचिन्हित पूर्णांक insert_cpos, पूर्णांक insert_index,
		 पूर्णांक has_empty, पूर्णांक next_मुक्त,
		 अचिन्हित पूर्णांक l_count),
	TP_ARGS(insert_cpos, insert_index, has_empty,
		next_मुक्त, l_count),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, insert_cpos)
		__field(पूर्णांक, insert_index)
		__field(पूर्णांक, has_empty)
		__field(पूर्णांक, next_मुक्त)
		__field(अचिन्हित पूर्णांक, l_count)
	),
	TP_fast_assign(
		__entry->insert_cpos = insert_cpos;
		__entry->insert_index = insert_index;
		__entry->has_empty = has_empty;
		__entry->next_मुक्त = next_मुक्त;
		__entry->l_count = l_count;
	),
	TP_prपूर्णांकk("%u %d %d %d %u", __entry->insert_cpos,
		  __entry->insert_index, __entry->has_empty,
		  __entry->next_मुक्त, __entry->l_count)
);

TRACE_EVENT(ocfs2_add_clusters_in_btree_ret,
	TP_PROTO(पूर्णांक status, पूर्णांक reason, पूर्णांक err),
	TP_ARGS(status, reason, err),
	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__field(पूर्णांक, reason)
		__field(पूर्णांक, err)
	),
	TP_fast_assign(
		__entry->status = status;
		__entry->reason = reason;
		__entry->err = err;
	),
	TP_prपूर्णांकk("%d %d %d", __entry->status,
		  __entry->reason, __entry->err)
);

TRACE_EVENT(ocfs2_mark_extent_written,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner, अचिन्हित पूर्णांक cpos,
		 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक phys),
	TP_ARGS(owner, cpos, len, phys),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, owner)
		__field(अचिन्हित पूर्णांक, cpos)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, phys)
	),
	TP_fast_assign(
		__entry->owner = owner;
		__entry->cpos = cpos;
		__entry->len = len;
		__entry->phys = phys;
	),
	TP_prपूर्णांकk("%llu %u %u %u",
		  __entry->owner, __entry->cpos,
		  __entry->len, __entry->phys)
);

DECLARE_EVENT_CLASS(ocfs2__truncate_log_ops,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno, पूर्णांक index,
		 अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक num),
	TP_ARGS(blkno, index, start, num),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
		__field(पूर्णांक, index)
		__field(अचिन्हित पूर्णांक, start)
		__field(अचिन्हित पूर्णांक, num)
	),
	TP_fast_assign(
		__entry->blkno = blkno;
		__entry->index = index;
		__entry->start = start;
		__entry->num = num;
	),
	TP_prपूर्णांकk("%llu %d %u %u",
		  __entry->blkno, __entry->index,
		  __entry->start, __entry->num)
);

#घोषणा DEFINE_OCFS2_TRUNCATE_LOG_OPS_EVENT(name)	\
DEFINE_EVENT(ocfs2__truncate_log_ops, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno, पूर्णांक index,	\
		 अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक num),	\
	TP_ARGS(blkno, index, start, num))

DEFINE_OCFS2_TRUNCATE_LOG_OPS_EVENT(ocfs2_truncate_log_append);

DEFINE_OCFS2_TRUNCATE_LOG_OPS_EVENT(ocfs2_replay_truncate_records);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_flush_truncate_log);

DEFINE_OCFS2_INT_EVENT(ocfs2_begin_truncate_log_recovery);

DEFINE_OCFS2_INT_EVENT(ocfs2_truncate_log_recovery_num);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_complete_truncate_log_recovery);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_मुक्त_cached_blocks);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_cache_cluster_dealloc);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_run_deallocs);

TRACE_EVENT(ocfs2_cache_block_dealloc,
	TP_PROTO(पूर्णांक type, पूर्णांक slot, अचिन्हित दीर्घ दीर्घ suballoc,
		 अचिन्हित दीर्घ दीर्घ blkno, अचिन्हित पूर्णांक bit),
	TP_ARGS(type, slot, suballoc, blkno, bit),
	TP_STRUCT__entry(
		__field(पूर्णांक, type)
		__field(पूर्णांक, slot)
		__field(अचिन्हित दीर्घ दीर्घ, suballoc)
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
		__field(अचिन्हित पूर्णांक, bit)
	),
	TP_fast_assign(
		__entry->type = type;
		__entry->slot = slot;
		__entry->suballoc = suballoc;
		__entry->blkno = blkno;
		__entry->bit = bit;
	),
	TP_prपूर्णांकk("%d %d %llu %llu %u",
		  __entry->type, __entry->slot, __entry->suballoc,
		  __entry->blkno, __entry->bit)
);

TRACE_EVENT(ocfs2_trim_extent,
	TP_PROTO(काष्ठा super_block *sb, अचिन्हित दीर्घ दीर्घ blk,
		 अचिन्हित दीर्घ दीर्घ count),
	TP_ARGS(sb, blk, count),
	TP_STRUCT__entry(
		__field(पूर्णांक, dev_major)
		__field(पूर्णांक, dev_minor)
		__field(अचिन्हित दीर्घ दीर्घ, blk)
		__field(__u64,	count)
	),
	TP_fast_assign(
		__entry->dev_major = MAJOR(sb->s_dev);
		__entry->dev_minor = MINOR(sb->s_dev);
		__entry->blk = blk;
		__entry->count = count;
	),
	TP_prपूर्णांकk("%d %d %llu %llu",
		  __entry->dev_major, __entry->dev_minor,
		  __entry->blk, __entry->count)
);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_trim_group);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_trim_मुख्यbm);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_trim_fs);

/* End of trace events क्रम fs/ocfs2/alloc.c. */

/* Trace events क्रम fs/ocfs2/localalloc.c. */

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_la_set_sizes);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_alloc_should_use_local);

DEFINE_OCFS2_INT_EVENT(ocfs2_load_local_alloc);

DEFINE_OCFS2_INT_EVENT(ocfs2_begin_local_alloc_recovery);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_reserve_local_alloc_bits);

DEFINE_OCFS2_UINT_EVENT(ocfs2_local_alloc_count_bits);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_local_alloc_find_clear_bits_search_biपंचांगap);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_local_alloc_find_clear_bits);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_sync_local_to_मुख्य);

TRACE_EVENT(ocfs2_sync_local_to_मुख्य_मुक्त,
	TP_PROTO(पूर्णांक count, पूर्णांक bit, अचिन्हित दीर्घ दीर्घ start_blk,
		 अचिन्हित दीर्घ दीर्घ blkno),
	TP_ARGS(count, bit, start_blk, blkno),
	TP_STRUCT__entry(
		__field(पूर्णांक, count)
		__field(पूर्णांक, bit)
		__field(अचिन्हित दीर्घ दीर्घ, start_blk)
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
	),
	TP_fast_assign(
		__entry->count = count;
		__entry->bit = bit;
		__entry->start_blk = start_blk;
		__entry->blkno = blkno;
	),
	TP_prपूर्णांकk("%d %d %llu %llu",
		  __entry->count, __entry->bit, __entry->start_blk,
		  __entry->blkno)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_local_alloc_new_winकरोw);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_local_alloc_new_winकरोw_result);

/* End of trace events क्रम fs/ocfs2/localalloc.c. */

/* Trace events क्रम fs/ocfs2/resize.c. */

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_update_last_group_and_inode);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_group_extend);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_group_add);

/* End of trace events क्रम fs/ocfs2/resize.c. */

/* Trace events क्रम fs/ocfs2/suballoc.c. */

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_group_descriptor);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_block_group_alloc_contig);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_block_group_alloc_discontig);

DEFINE_OCFS2_ULL_EVENT(ocfs2_block_group_alloc);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_reserve_suballoc_bits_nospc);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_reserve_suballoc_bits_no_new_group);

DEFINE_OCFS2_ULL_EVENT(ocfs2_reserve_new_inode_new_group);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_block_group_set_bits);

TRACE_EVENT(ocfs2_relink_block_group,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ i_blkno, अचिन्हित पूर्णांक chain,
		 अचिन्हित दीर्घ दीर्घ bg_blkno,
		 अचिन्हित दीर्घ दीर्घ prev_blkno),
	TP_ARGS(i_blkno, chain, bg_blkno, prev_blkno),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, i_blkno)
		__field(अचिन्हित पूर्णांक, chain)
		__field(अचिन्हित दीर्घ दीर्घ, bg_blkno)
		__field(अचिन्हित दीर्घ दीर्घ, prev_blkno)
	),
	TP_fast_assign(
		__entry->i_blkno = i_blkno;
		__entry->chain = chain;
		__entry->bg_blkno = bg_blkno;
		__entry->prev_blkno = prev_blkno;
	),
	TP_prपूर्णांकk("%llu %u %llu %llu",
		  __entry->i_blkno, __entry->chain, __entry->bg_blkno,
		  __entry->prev_blkno)
);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_cluster_group_search_wrong_max_bits);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_cluster_group_search_max_block);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_block_group_search_max_block);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_search_chain_begin);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_search_chain_succ);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_search_chain_end);

DEFINE_OCFS2_UINT_EVENT(ocfs2_claim_suballoc_bits);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_claim_new_inode_at_loc);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_block_group_clear_bits);

TRACE_EVENT(ocfs2_मुक्त_suballoc_bits,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ inode, अचिन्हित दीर्घ दीर्घ group,
		 अचिन्हित पूर्णांक start_bit, अचिन्हित पूर्णांक count),
	TP_ARGS(inode, group, start_bit, count),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, inode)
		__field(अचिन्हित दीर्घ दीर्घ, group)
		__field(अचिन्हित पूर्णांक, start_bit)
		__field(अचिन्हित पूर्णांक, count)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->group = group;
		__entry->start_bit = start_bit;
		__entry->count = count;
	),
	TP_prपूर्णांकk("%llu %llu %u %u", __entry->inode, __entry->group,
		  __entry->start_bit, __entry->count)
);

TRACE_EVENT(ocfs2_मुक्त_clusters,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ bg_blkno, अचिन्हित दीर्घ दीर्घ start_blk,
		 अचिन्हित पूर्णांक start_bit, अचिन्हित पूर्णांक count),
	TP_ARGS(bg_blkno, start_blk, start_bit, count),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, bg_blkno)
		__field(अचिन्हित दीर्घ दीर्घ, start_blk)
		__field(अचिन्हित पूर्णांक, start_bit)
		__field(अचिन्हित पूर्णांक, count)
	),
	TP_fast_assign(
		__entry->bg_blkno = bg_blkno;
		__entry->start_blk = start_blk;
		__entry->start_bit = start_bit;
		__entry->count = count;
	),
	TP_prपूर्णांकk("%llu %llu %u %u", __entry->bg_blkno, __entry->start_blk,
		  __entry->start_bit, __entry->count)
);

DEFINE_OCFS2_ULL_EVENT(ocfs2_get_suballoc_slot_bit);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_test_suballoc_bit);

DEFINE_OCFS2_ULL_EVENT(ocfs2_test_inode_bit);

/* End of trace events क्रम fs/ocfs2/suballoc.c. */

/* Trace events क्रम fs/ocfs2/refcounttree.c. */

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_refcount_block);

DEFINE_OCFS2_ULL_EVENT(ocfs2_purge_refcount_trees);

DEFINE_OCFS2_ULL_EVENT(ocfs2_create_refcount_tree);

DEFINE_OCFS2_ULL_EVENT(ocfs2_create_refcount_tree_blkno);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_change_refcount_rec);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_expand_अंतरभूत_ref_root);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_भागide_leaf_refcount_block);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_new_leaf_refcount_block);

DECLARE_EVENT_CLASS(ocfs2__refcount_tree_ops,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno, पूर्णांक index,
		 अचिन्हित दीर्घ दीर्घ cpos,
		 अचिन्हित पूर्णांक clusters, अचिन्हित पूर्णांक refcount),
	TP_ARGS(blkno, index, cpos, clusters, refcount),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
		__field(पूर्णांक, index)
		__field(अचिन्हित दीर्घ दीर्घ, cpos)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित पूर्णांक, refcount)
	),
	TP_fast_assign(
		__entry->blkno = blkno;
		__entry->index = index;
		__entry->cpos = cpos;
		__entry->clusters = clusters;
		__entry->refcount = refcount;
	),
	TP_prपूर्णांकk("%llu %d %llu %u %u", __entry->blkno, __entry->index,
		  __entry->cpos, __entry->clusters, __entry->refcount)
);

#घोषणा DEFINE_OCFS2_REFCOUNT_TREE_OPS_EVENT(name)	\
DEFINE_EVENT(ocfs2__refcount_tree_ops, name,		\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno, पूर्णांक index,	\
		 अचिन्हित दीर्घ दीर्घ cpos,		\
		 अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक refcount),	\
	TP_ARGS(blkno, index, cpos, count, refcount))

DEFINE_OCFS2_REFCOUNT_TREE_OPS_EVENT(ocfs2_insert_refcount_rec);

TRACE_EVENT(ocfs2_split_refcount_rec,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ cpos,
		 अचिन्हित पूर्णांक clusters, अचिन्हित पूर्णांक refcount,
		 अचिन्हित दीर्घ दीर्घ split_cpos,
		 अचिन्हित पूर्णांक split_clusters, अचिन्हित पूर्णांक split_refcount),
	TP_ARGS(cpos, clusters, refcount,
		split_cpos, split_clusters, split_refcount),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, cpos)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित पूर्णांक, refcount)
		__field(अचिन्हित दीर्घ दीर्घ, split_cpos)
		__field(अचिन्हित पूर्णांक, split_clusters)
		__field(अचिन्हित पूर्णांक, split_refcount)
	),
	TP_fast_assign(
		__entry->cpos = cpos;
		__entry->clusters = clusters;
		__entry->refcount = refcount;
		__entry->split_cpos = split_cpos;
		__entry->split_clusters = split_clusters;
		__entry->split_refcount	= split_refcount;
	),
	TP_prपूर्णांकk("%llu %u %u %llu %u %u",
		  __entry->cpos, __entry->clusters, __entry->refcount,
		  __entry->split_cpos, __entry->split_clusters,
		  __entry->split_refcount)
);

DEFINE_OCFS2_REFCOUNT_TREE_OPS_EVENT(ocfs2_split_refcount_rec_insert);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_increase_refcount_begin);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_increase_refcount_change);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_increase_refcount_insert);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_increase_refcount_split);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_हटाओ_refcount_extent);

DEFINE_OCFS2_ULL_EVENT(ocfs2_restore_refcount_block);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_decrease_refcount_rec);

TRACE_EVENT(ocfs2_decrease_refcount,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ owner,
		 अचिन्हित दीर्घ दीर्घ cpos,
		 अचिन्हित पूर्णांक len, पूर्णांक delete),
	TP_ARGS(owner, cpos, len, delete),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, owner)
		__field(अचिन्हित दीर्घ दीर्घ, cpos)
		__field(अचिन्हित पूर्णांक, len)
		__field(पूर्णांक, delete)
	),
	TP_fast_assign(
		__entry->owner = owner;
		__entry->cpos = cpos;
		__entry->len = len;
		__entry->delete = delete;
	),
	TP_prपूर्णांकk("%llu %llu %u %d",
		  __entry->owner, __entry->cpos, __entry->len, __entry->delete)
);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_mark_extent_refcounted);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_calc_refcount_meta_credits);

TRACE_EVENT(ocfs2_calc_refcount_meta_credits_iterate,
	TP_PROTO(पूर्णांक recs_add, अचिन्हित दीर्घ दीर्घ cpos,
		 अचिन्हित पूर्णांक clusters, अचिन्हित दीर्घ दीर्घ r_cpos,
		 अचिन्हित पूर्णांक r_clusters, अचिन्हित पूर्णांक refcount, पूर्णांक index),
	TP_ARGS(recs_add, cpos, clusters, r_cpos, r_clusters, refcount, index),
	TP_STRUCT__entry(
		__field(पूर्णांक, recs_add)
		__field(अचिन्हित दीर्घ दीर्घ, cpos)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित दीर्घ दीर्घ, r_cpos)
		__field(अचिन्हित पूर्णांक, r_clusters)
		__field(अचिन्हित पूर्णांक, refcount)
		__field(पूर्णांक, index)
	),
	TP_fast_assign(
		__entry->recs_add = recs_add;
		__entry->cpos = cpos;
		__entry->clusters = clusters;
		__entry->r_cpos = r_cpos;
		__entry->r_clusters = r_clusters;
		__entry->refcount = refcount;
		__entry->index = index;
	),
	TP_prपूर्णांकk("%d %llu %u %llu %u %u %d",
		  __entry->recs_add, __entry->cpos, __entry->clusters,
		  __entry->r_cpos, __entry->r_clusters,
		  __entry->refcount, __entry->index)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_add_refcount_flag);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_prepare_refcount_change_क्रम_del);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_lock_refcount_allocators);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_duplicate_clusters_by_page);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_duplicate_clusters_by_jbd);

TRACE_EVENT(ocfs2_clear_ext_refcount,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक cpos,
		 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक p_cluster,
		 अचिन्हित पूर्णांक ext_flags),
	TP_ARGS(ino, cpos, len, p_cluster, ext_flags),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, cpos)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, p_cluster)
		__field(अचिन्हित पूर्णांक, ext_flags)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->cpos = cpos;
		__entry->len = len;
		__entry->p_cluster = p_cluster;
		__entry->ext_flags = ext_flags;
	),
	TP_prपूर्णांकk("%llu %u %u %u %u",
		  __entry->ino, __entry->cpos, __entry->len,
		  __entry->p_cluster, __entry->ext_flags)
);

TRACE_EVENT(ocfs2_replace_clusters,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक cpos,
		 अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक ext_flags),
	TP_ARGS(ino, cpos, old, new, len, ext_flags),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, cpos)
		__field(अचिन्हित पूर्णांक, old)
		__field(अचिन्हित पूर्णांक, new)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, ext_flags)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->cpos = cpos;
		__entry->old = old;
		__entry->new = new;
		__entry->len = len;
		__entry->ext_flags = ext_flags;
	),
	TP_prपूर्णांकk("%llu %u %u %u %u %u",
		  __entry->ino, __entry->cpos, __entry->old, __entry->new,
		  __entry->len, __entry->ext_flags)
);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_make_clusters_writable);

TRACE_EVENT(ocfs2_refcount_cow_hunk,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक cpos,
		 अचिन्हित पूर्णांक ग_लिखो_len, अचिन्हित पूर्णांक max_cpos,
		 अचिन्हित पूर्णांक cow_start, अचिन्हित पूर्णांक cow_len),
	TP_ARGS(ino, cpos, ग_लिखो_len, max_cpos, cow_start, cow_len),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, cpos)
		__field(अचिन्हित पूर्णांक, ग_लिखो_len)
		__field(अचिन्हित पूर्णांक, max_cpos)
		__field(अचिन्हित पूर्णांक, cow_start)
		__field(अचिन्हित पूर्णांक, cow_len)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->cpos = cpos;
		__entry->ग_लिखो_len = ग_लिखो_len;
		__entry->max_cpos = max_cpos;
		__entry->cow_start = cow_start;
		__entry->cow_len = cow_len;
	),
	TP_prपूर्णांकk("%llu %u %u %u %u %u",
		  __entry->ino, __entry->cpos, __entry->ग_लिखो_len,
		  __entry->max_cpos, __entry->cow_start, __entry->cow_len)
);

/* End of trace events क्रम fs/ocfs2/refcounttree.c. */

/* Trace events क्रम fs/ocfs2/aops.c. */

DECLARE_EVENT_CLASS(ocfs2__get_block,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित दीर्घ दीर्घ iblock,
		 व्योम *bh_result, पूर्णांक create),
	TP_ARGS(ino, iblock, bh_result, create),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित दीर्घ दीर्घ, iblock)
		__field(व्योम *, bh_result)
		__field(पूर्णांक, create)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->iblock = iblock;
		__entry->bh_result = bh_result;
		__entry->create = create;
	),
	TP_prपूर्णांकk("%llu %llu %p %d",
		  __entry->ino, __entry->iblock,
		  __entry->bh_result, __entry->create)
);

#घोषणा DEFINE_OCFS2_GET_BLOCK_EVENT(name)	\
DEFINE_EVENT(ocfs2__get_block, name,	\
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित दीर्घ दीर्घ iblock,	\
		 व्योम *bh_result, पूर्णांक create),	\
	TP_ARGS(ino, iblock, bh_result, create))

DEFINE_OCFS2_GET_BLOCK_EVENT(ocfs2_symlink_get_block);

DEFINE_OCFS2_GET_BLOCK_EVENT(ocfs2_get_block);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_get_block_end);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_पढ़ोpage);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_ग_लिखोpage);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_bmap);

TRACE_EVENT(ocfs2_try_to_ग_लिखो_अंतरभूत_data,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक len,
		 अचिन्हित दीर्घ दीर्घ pos, अचिन्हित पूर्णांक flags),
	TP_ARGS(ino, len, pos, flags),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित दीर्घ दीर्घ, pos)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->len = len;
		__entry->pos = pos;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%llu %u %llu 0x%x",
		  __entry->ino, __entry->len, __entry->pos, __entry->flags)
);

TRACE_EVENT(ocfs2_ग_लिखो_begin_nolock,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino,
		 दीर्घ दीर्घ i_size, अचिन्हित पूर्णांक i_clusters,
		 अचिन्हित दीर्घ दीर्घ pos, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक flags, व्योम *page,
		 अचिन्हित पूर्णांक clusters, अचिन्हित पूर्णांक extents_to_split),
	TP_ARGS(ino, i_size, i_clusters, pos, len, flags,
		page, clusters, extents_to_split),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(दीर्घ दीर्घ, i_size)
		__field(अचिन्हित पूर्णांक, i_clusters)
		__field(अचिन्हित दीर्घ दीर्घ, pos)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, flags)
		__field(व्योम *, page)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित पूर्णांक, extents_to_split)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->i_size = i_size;
		__entry->i_clusters = i_clusters;
		__entry->pos = pos;
		__entry->len = len;
		__entry->flags = flags;
		__entry->page = page;
		__entry->clusters = clusters;
		__entry->extents_to_split = extents_to_split;
	),
	TP_prपूर्णांकk("%llu %lld %u %llu %u %u %p %u %u",
		  __entry->ino, __entry->i_size, __entry->i_clusters,
		  __entry->pos, __entry->len,
		  __entry->flags, __entry->page, __entry->clusters,
		  __entry->extents_to_split)
);

TRACE_EVENT(ocfs2_ग_लिखो_end_अंतरभूत,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित दीर्घ दीर्घ pos, अचिन्हित पूर्णांक copied,
		 अचिन्हित पूर्णांक id_count, अचिन्हित पूर्णांक features),
	TP_ARGS(ino, pos, copied, id_count, features),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित दीर्घ दीर्घ, pos)
		__field(अचिन्हित पूर्णांक, copied)
		__field(अचिन्हित पूर्णांक, id_count)
		__field(अचिन्हित पूर्णांक, features)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->pos = pos;
		__entry->copied = copied;
		__entry->id_count = id_count;
		__entry->features = features;
	),
	TP_prपूर्णांकk("%llu %llu %u %u %u",
		  __entry->ino, __entry->pos, __entry->copied,
		  __entry->id_count, __entry->features)
);

/* End of trace events क्रम fs/ocfs2/aops.c. */

/* Trace events क्रम fs/ocfs2/mmap.c. */

TRACE_EVENT(ocfs2_fault,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino,
		 व्योम *area, व्योम *page, अचिन्हित दीर्घ pgoff),
	TP_ARGS(ino, area, page, pgoff),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(व्योम *, area)
		__field(व्योम *, page)
		__field(अचिन्हित दीर्घ, pgoff)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->area = area;
		__entry->page = page;
		__entry->pgoff = pgoff;
	),
	TP_prपूर्णांकk("%llu %p %p %lu",
		  __entry->ino, __entry->area, __entry->page, __entry->pgoff)
);

/* End of trace events क्रम fs/ocfs2/mmap.c. */

/* Trace events क्रम fs/ocfs2/file.c. */

DECLARE_EVENT_CLASS(ocfs2__file_ops,
	TP_PROTO(व्योम *inode, व्योम *file, व्योम *dentry,
		 अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित पूर्णांक d_len, स्थिर अचिन्हित अक्षर *d_name,
		 अचिन्हित दीर्घ दीर्घ para),
	TP_ARGS(inode, file, dentry, ino, d_len, d_name, para),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(व्योम *, file)
		__field(व्योम *, dentry)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, d_len)
		__string(d_name, d_name)
		__field(अचिन्हित दीर्घ दीर्घ, para)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->file = file;
		__entry->dentry = dentry;
		__entry->ino = ino;
		__entry->d_len = d_len;
		__assign_str(d_name, d_name);
		__entry->para = para;
	),
	TP_prपूर्णांकk("%p %p %p %llu %llu %.*s", __entry->inode, __entry->file,
		  __entry->dentry, __entry->ino, __entry->para,
		  __entry->d_len, __get_str(d_name))
);

#घोषणा DEFINE_OCFS2_खाता_OPS(name)				\
DEFINE_EVENT(ocfs2__file_ops, name,				\
TP_PROTO(व्योम *inode, व्योम *file, व्योम *dentry,			\
	 अचिन्हित दीर्घ दीर्घ ino,				\
	 अचिन्हित पूर्णांक d_len, स्थिर अचिन्हित अक्षर *d_name,	\
	 अचिन्हित दीर्घ दीर्घ mode),				\
	TP_ARGS(inode, file, dentry, ino, d_len, d_name, mode))

DEFINE_OCFS2_खाता_OPS(ocfs2_file_खोलो);

DEFINE_OCFS2_खाता_OPS(ocfs2_file_release);

DEFINE_OCFS2_खाता_OPS(ocfs2_sync_file);

DEFINE_OCFS2_खाता_OPS(ocfs2_file_ग_लिखो_iter);

DEFINE_OCFS2_खाता_OPS(ocfs2_file_splice_ग_लिखो);

DEFINE_OCFS2_खाता_OPS(ocfs2_file_पढ़ो_iter);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_truncate_file);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_truncate_file_error);

TRACE_EVENT(ocfs2_extend_allocation,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ip_blkno, अचिन्हित दीर्घ दीर्घ size,
		 अचिन्हित पूर्णांक clusters, अचिन्हित पूर्णांक clusters_to_add,
		 पूर्णांक why, पूर्णांक restart_func),
	TP_ARGS(ip_blkno, size, clusters, clusters_to_add, why, restart_func),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ip_blkno)
		__field(अचिन्हित दीर्घ दीर्घ, size)
		__field(अचिन्हित पूर्णांक, clusters)
		__field(अचिन्हित पूर्णांक, clusters_to_add)
		__field(पूर्णांक, why)
		__field(पूर्णांक, restart_func)
	),
	TP_fast_assign(
		__entry->ip_blkno = ip_blkno;
		__entry->size = size;
		__entry->clusters = clusters;
		__entry->clusters_to_add = clusters_to_add;
		__entry->why = why;
		__entry->restart_func = restart_func;
	),
	TP_prपूर्णांकk("%llu %llu %u %u %d %d",
		  __entry->ip_blkno, __entry->size, __entry->clusters,
		  __entry->clusters_to_add, __entry->why, __entry->restart_func)
);

TRACE_EVENT(ocfs2_extend_allocation_end,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित पूर्णांक di_clusters, अचिन्हित दीर्घ दीर्घ di_size,
		 अचिन्हित पूर्णांक ip_clusters, अचिन्हित दीर्घ दीर्घ i_size),
	TP_ARGS(ino, di_clusters, di_size, ip_clusters, i_size),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, di_clusters)
		__field(अचिन्हित दीर्घ दीर्घ, di_size)
		__field(अचिन्हित पूर्णांक, ip_clusters)
		__field(अचिन्हित दीर्घ दीर्घ, i_size)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->di_clusters = di_clusters;
		__entry->di_size = di_size;
		__entry->ip_clusters = ip_clusters;
		__entry->i_size = i_size;
	),
	TP_prपूर्णांकk("%llu %u %llu %u %llu", __entry->ino, __entry->di_clusters,
		  __entry->di_size, __entry->ip_clusters, __entry->i_size)
);

TRACE_EVENT(ocfs2_ग_लिखो_zero_page,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित दीर्घ दीर्घ असल_from, अचिन्हित दीर्घ दीर्घ असल_to,
		 अचिन्हित दीर्घ index, अचिन्हित पूर्णांक zero_from,
		 अचिन्हित पूर्णांक zero_to),
	TP_ARGS(ino, असल_from, असल_to, index, zero_from, zero_to),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित दीर्घ दीर्घ, असल_from)
		__field(अचिन्हित दीर्घ दीर्घ, असल_to)
		__field(अचिन्हित दीर्घ, index)
		__field(अचिन्हित पूर्णांक, zero_from)
		__field(अचिन्हित पूर्णांक, zero_to)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->असल_from = असल_from;
		__entry->असल_to = असल_to;
		__entry->index = index;
		__entry->zero_from = zero_from;
		__entry->zero_to = zero_to;
	),
	TP_prपूर्णांकk("%llu %llu %llu %lu %u %u", __entry->ino,
		  __entry->असल_from, __entry->असल_to,
		  __entry->index, __entry->zero_from, __entry->zero_to)
);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_zero_extend_range);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_zero_extend);

TRACE_EVENT(ocfs2_setattr,
	TP_PROTO(व्योम *inode, व्योम *dentry,
		 अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित पूर्णांक d_len, स्थिर अचिन्हित अक्षर *d_name,
		 अचिन्हित पूर्णांक ia_valid, अचिन्हित पूर्णांक ia_mode,
		 अचिन्हित पूर्णांक ia_uid, अचिन्हित पूर्णांक ia_gid),
	TP_ARGS(inode, dentry, ino, d_len, d_name,
		ia_valid, ia_mode, ia_uid, ia_gid),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(व्योम *, dentry)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, d_len)
		__string(d_name, d_name)
		__field(अचिन्हित पूर्णांक, ia_valid)
		__field(अचिन्हित पूर्णांक, ia_mode)
		__field(अचिन्हित पूर्णांक, ia_uid)
		__field(अचिन्हित पूर्णांक, ia_gid)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->dentry = dentry;
		__entry->ino = ino;
		__entry->d_len = d_len;
		__assign_str(d_name, d_name);
		__entry->ia_valid = ia_valid;
		__entry->ia_mode = ia_mode;
		__entry->ia_uid = ia_uid;
		__entry->ia_gid = ia_gid;
	),
	TP_prपूर्णांकk("%p %p %llu %.*s %u %u %u %u", __entry->inode,
		  __entry->dentry, __entry->ino, __entry->d_len,
		  __get_str(d_name), __entry->ia_valid, __entry->ia_mode,
		  __entry->ia_uid, __entry->ia_gid)
);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_ग_लिखो_हटाओ_suid);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_zero_partial_clusters);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_zero_partial_clusters_range1);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_zero_partial_clusters_range2);

DEFINE_OCFS2_ULL_ULL_ULL_EVENT(ocfs2_हटाओ_inode_range);

TRACE_EVENT(ocfs2_prepare_inode_क्रम_ग_लिखो,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित दीर्घ दीर्घ saved_pos,
		 अचिन्हित दीर्घ count, पूर्णांक रुको),
	TP_ARGS(ino, saved_pos, count, रुको),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित दीर्घ दीर्घ, saved_pos)
		__field(अचिन्हित दीर्घ, count)
		__field(पूर्णांक, रुको)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->saved_pos = saved_pos;
		__entry->count = count;
		__entry->रुको = रुको;
	),
	TP_prपूर्णांकk("%llu %llu %lu %d", __entry->ino,
		  __entry->saved_pos, __entry->count, __entry->रुको)
);

DEFINE_OCFS2_INT_EVENT(generic_file_पढ़ो_iter_ret);

/* End of trace events क्रम fs/ocfs2/file.c. */

/* Trace events क्रम fs/ocfs2/inode.c. */

TRACE_EVENT(ocfs2_iget_begin,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, अचिन्हित पूर्णांक flags, पूर्णांक sysfile_type),
	TP_ARGS(ino, flags, sysfile_type),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, flags)
		__field(पूर्णांक, sysfile_type)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->flags = flags;
		__entry->sysfile_type = sysfile_type;
	),
	TP_prपूर्णांकk("%llu %u %d", __entry->ino,
		  __entry->flags, __entry->sysfile_type)
);

DEFINE_OCFS2_ULL_EVENT(ocfs2_iget5_locked);

TRACE_EVENT(ocfs2_iget_end,
	TP_PROTO(व्योम *inode, अचिन्हित दीर्घ दीर्घ ino),
	TP_ARGS(inode, ino),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->ino = ino;
	),
	TP_prपूर्णांकk("%p %llu", __entry->inode, __entry->ino)
);

TRACE_EVENT(ocfs2_find_actor,
	TP_PROTO(व्योम *inode, अचिन्हित दीर्घ दीर्घ ino,
		 व्योम *args,  अचिन्हित दीर्घ दीर्घ fi_blkno),
	TP_ARGS(inode, ino, args, fi_blkno),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(व्योम *, args)
		__field(अचिन्हित दीर्घ दीर्घ, fi_blkno)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->ino = ino;
		__entry->args = args;
		__entry->fi_blkno = fi_blkno;
	),
	TP_prपूर्णांकk("%p %llu %p %llu", __entry->inode, __entry->ino,
		  __entry->args, __entry->fi_blkno)
);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_populate_inode);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_पढ़ो_locked_inode);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_check_orphan_recovery_state);

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_inode_block);
DEFINE_OCFS2_ULL_EVENT(ocfs2_filecheck_validate_inode_block);
DEFINE_OCFS2_ULL_EVENT(ocfs2_filecheck_repair_inode_block);

TRACE_EVENT(ocfs2_inode_is_valid_to_delete,
	TP_PROTO(व्योम *task, व्योम *dc_task, अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित पूर्णांक flags),
	TP_ARGS(task, dc_task, ino, flags),
	TP_STRUCT__entry(
		__field(व्योम *, task)
		__field(व्योम *, dc_task)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->task = task;
		__entry->dc_task = dc_task;
		__entry->ino = ino;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%p %p %llu %u", __entry->task, __entry->dc_task,
		  __entry->ino, __entry->flags)
);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_query_inode_wipe_begin);

DEFINE_OCFS2_UINT_EVENT(ocfs2_query_inode_wipe_succ);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_query_inode_wipe_end);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_cleanup_delete_inode);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_delete_inode);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_clear_inode);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_drop_inode);

TRACE_EVENT(ocfs2_inode_revalidate,
	TP_PROTO(व्योम *inode, अचिन्हित दीर्घ दीर्घ ino,
		 अचिन्हित पूर्णांक flags),
	TP_ARGS(inode, ino, flags),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(अचिन्हित पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->ino = ino;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%p %llu %u", __entry->inode, __entry->ino, __entry->flags)
);

DEFINE_OCFS2_ULL_EVENT(ocfs2_mark_inode_dirty);

/* End of trace events क्रम fs/ocfs2/inode.c. */

/* Trace events क्रम fs/ocfs2/extent_map.c. */

TRACE_EVENT(ocfs2_पढ़ो_virt_blocks,
	TP_PROTO(व्योम *inode, अचिन्हित दीर्घ दीर्घ vblock, पूर्णांक nr,
		 व्योम *bhs, अचिन्हित पूर्णांक flags, व्योम *validate),
	TP_ARGS(inode, vblock, nr, bhs, flags, validate),
	TP_STRUCT__entry(
		__field(व्योम *, inode)
		__field(अचिन्हित दीर्घ दीर्घ, vblock)
		__field(पूर्णांक, nr)
		__field(व्योम *, bhs)
		__field(अचिन्हित पूर्णांक, flags)
		__field(व्योम *, validate)
	),
	TP_fast_assign(
		__entry->inode = inode;
		__entry->vblock = vblock;
		__entry->nr = nr;
		__entry->bhs = bhs;
		__entry->flags = flags;
		__entry->validate = validate;
	),
	TP_prपूर्णांकk("%p %llu %d %p %x %p", __entry->inode, __entry->vblock,
		  __entry->nr, __entry->bhs, __entry->flags, __entry->validate)
);

/* End of trace events क्रम fs/ocfs2/extent_map.c. */

/* Trace events क्रम fs/ocfs2/slot_map.c. */

DEFINE_OCFS2_UINT_EVENT(ocfs2_refresh_slot_info);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_map_slot_buffers);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_map_slot_buffers_block);

DEFINE_OCFS2_INT_EVENT(ocfs2_find_slot);

/* End of trace events क्रम fs/ocfs2/slot_map.c. */

/* Trace events क्रम fs/ocfs2/heartbeat.c. */

DEFINE_OCFS2_INT_EVENT(ocfs2_करो_node_करोwn);

/* End of trace events क्रम fs/ocfs2/heartbeat.c. */

/* Trace events क्रम fs/ocfs2/super.c. */

TRACE_EVENT(ocfs2_remount,
	TP_PROTO(अचिन्हित दीर्घ s_flags, अचिन्हित दीर्घ osb_flags, पूर्णांक flags),
	TP_ARGS(s_flags, osb_flags, flags),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, s_flags)
		__field(अचिन्हित दीर्घ, osb_flags)
		__field(पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->s_flags = s_flags;
		__entry->osb_flags = osb_flags;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%lu %lu %d", __entry->s_flags,
		  __entry->osb_flags, __entry->flags)
);

TRACE_EVENT(ocfs2_fill_super,
	TP_PROTO(व्योम *sb, व्योम *data, पूर्णांक silent),
	TP_ARGS(sb, data, silent),
	TP_STRUCT__entry(
		__field(व्योम *, sb)
		__field(व्योम *, data)
		__field(पूर्णांक, silent)
	),
	TP_fast_assign(
		__entry->sb = sb;
		__entry->data = data;
		__entry->silent = silent;
	),
	TP_prपूर्णांकk("%p %p %d", __entry->sb,
		  __entry->data, __entry->silent)
);

TRACE_EVENT(ocfs2_parse_options,
	TP_PROTO(पूर्णांक is_remount, अक्षर *options),
	TP_ARGS(is_remount, options),
	TP_STRUCT__entry(
		__field(पूर्णांक, is_remount)
		__string(options, options)
	),
	TP_fast_assign(
		__entry->is_remount = is_remount;
		__assign_str(options, options);
	),
	TP_prपूर्णांकk("%d %s", __entry->is_remount, __get_str(options))
);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_put_super);

TRACE_EVENT(ocfs2_statfs,
	TP_PROTO(व्योम *sb, व्योम *buf),
	TP_ARGS(sb, buf),
	TP_STRUCT__entry(
		__field(व्योम *, sb)
		__field(व्योम *, buf)
	),
	TP_fast_assign(
		__entry->sb = sb;
		__entry->buf = buf;
	),
	TP_prपूर्णांकk("%p %p", __entry->sb, __entry->buf)
);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_dismount_volume);

TRACE_EVENT(ocfs2_initialize_super,
	TP_PROTO(अक्षर *label, अक्षर *uuid_str, अचिन्हित दीर्घ दीर्घ root_dir,
		 अचिन्हित दीर्घ दीर्घ प्रणाली_dir, पूर्णांक cluster_bits),
	TP_ARGS(label, uuid_str, root_dir, प्रणाली_dir, cluster_bits),
	TP_STRUCT__entry(
		__string(label, label)
		__string(uuid_str, uuid_str)
		__field(अचिन्हित दीर्घ दीर्घ, root_dir)
		__field(अचिन्हित दीर्घ दीर्घ, प्रणाली_dir)
		__field(पूर्णांक, cluster_bits)
	),
	TP_fast_assign(
		__assign_str(label, label);
		__assign_str(uuid_str, uuid_str);
		__entry->root_dir = root_dir;
		__entry->प्रणाली_dir = प्रणाली_dir;
		__entry->cluster_bits = cluster_bits;
	),
	TP_prपूर्णांकk("%s %s %llu %llu %d", __get_str(label), __get_str(uuid_str),
		  __entry->root_dir, __entry->प्रणाली_dir, __entry->cluster_bits)
);

/* End of trace events क्रम fs/ocfs2/super.c. */

/* Trace events क्रम fs/ocfs2/xattr.c. */

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_xattr_block);

DEFINE_OCFS2_UINT_EVENT(ocfs2_xattr_extend_allocation);

TRACE_EVENT(ocfs2_init_xattr_set_ctxt,
	TP_PROTO(स्थिर अक्षर *name, पूर्णांक meta, पूर्णांक clusters, पूर्णांक credits),
	TP_ARGS(name, meta, clusters, credits),
	TP_STRUCT__entry(
		__string(name, name)
		__field(पूर्णांक, meta)
		__field(पूर्णांक, clusters)
		__field(पूर्णांक, credits)
	),
	TP_fast_assign(
		__assign_str(name, name);
		__entry->meta = meta;
		__entry->clusters = clusters;
		__entry->credits = credits;
	),
	TP_prपूर्णांकk("%s %d %d %d", __get_str(name), __entry->meta,
		  __entry->clusters, __entry->credits)
);

DECLARE_EVENT_CLASS(ocfs2__xattr_find,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, स्थिर अक्षर *name, पूर्णांक name_index,
		 अचिन्हित पूर्णांक hash, अचिन्हित दीर्घ दीर्घ location,
		 पूर्णांक xe_index),
	TP_ARGS(ino, name, name_index, hash, location, xe_index),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__string(name, name)
		__field(पूर्णांक, name_index)
		__field(अचिन्हित पूर्णांक, hash)
		__field(अचिन्हित दीर्घ दीर्घ, location)
		__field(पूर्णांक, xe_index)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__assign_str(name, name);
		__entry->name_index = name_index;
		__entry->hash = hash;
		__entry->location = location;
		__entry->xe_index = xe_index;
	),
	TP_prपूर्णांकk("%llu %s %d %u %llu %d", __entry->ino, __get_str(name),
		  __entry->name_index, __entry->hash, __entry->location,
		  __entry->xe_index)
);

#घोषणा DEFINE_OCFS2_XATTR_FIND_EVENT(name)					\
DEFINE_EVENT(ocfs2__xattr_find, name,					\
TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, स्थिर अक्षर *name, पूर्णांक name_index,	\
	 अचिन्हित पूर्णांक hash, अचिन्हित दीर्घ दीर्घ bucket,			\
	 पूर्णांक xe_index),							\
	TP_ARGS(ino, name, name_index, hash, bucket, xe_index))

DEFINE_OCFS2_XATTR_FIND_EVENT(ocfs2_xattr_bucket_find);

DEFINE_OCFS2_XATTR_FIND_EVENT(ocfs2_xattr_index_block_find);

DEFINE_OCFS2_XATTR_FIND_EVENT(ocfs2_xattr_index_block_find_rec);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_iterate_xattr_buckets);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_iterate_xattr_bucket);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_cp_xattr_block_to_bucket_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_cp_xattr_block_to_bucket_end);

DEFINE_OCFS2_ULL_EVENT(ocfs2_xattr_create_index_block_begin);

DEFINE_OCFS2_ULL_EVENT(ocfs2_xattr_create_index_block);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_defrag_xattr_bucket);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_mv_xattr_bucket_cross_cluster);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_भागide_xattr_bucket_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_भागide_xattr_bucket_move);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_cp_xattr_bucket);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_mv_xattr_buckets);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_adjust_xattr_cross_cluster);

DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(ocfs2_add_new_xattr_cluster_begin);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_add_new_xattr_cluster);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_add_new_xattr_cluster_insert);

DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(ocfs2_extend_xattr_bucket);

DEFINE_OCFS2_ULL_EVENT(ocfs2_add_new_xattr_bucket);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_xattr_bucket_value_truncate);

DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(ocfs2_rm_xattr_cluster);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_reflink_xattr_header);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_create_empty_xattr_block);

DEFINE_OCFS2_STRING_EVENT(ocfs2_xattr_set_entry_bucket);

DEFINE_OCFS2_STRING_EVENT(ocfs2_xattr_set_entry_index_block);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_xattr_bucket_value_refcount);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_reflink_xattr_buckets);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_reflink_xattr_rec);

/* End of trace events क्रम fs/ocfs2/xattr.c. */

/* Trace events क्रम fs/ocfs2/reservations.c. */

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_resv_insert);

DEFINE_OCFS2_ULL_UINT_UINT_UINT_EVENT(ocfs2_resmap_find_मुक्त_bits_begin);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_resmap_find_मुक्त_bits_end);

TRACE_EVENT(ocfs2_resv_find_winकरोw_begin,
	TP_PROTO(अचिन्हित पूर्णांक r_start, अचिन्हित पूर्णांक r_end, अचिन्हित पूर्णांक goal,
		 अचिन्हित पूर्णांक wanted, पूर्णांक empty_root),
	TP_ARGS(r_start, r_end, goal, wanted, empty_root),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, r_start)
		__field(अचिन्हित पूर्णांक, r_end)
		__field(अचिन्हित पूर्णांक, goal)
		__field(अचिन्हित पूर्णांक, wanted)
		__field(पूर्णांक, empty_root)
	),
	TP_fast_assign(
		__entry->r_start = r_start;
		__entry->r_end = r_end;
		__entry->goal = goal;
		__entry->wanted = wanted;
		__entry->empty_root = empty_root;
	),
	TP_prपूर्णांकk("%u %u %u %u %d", __entry->r_start, __entry->r_end,
		  __entry->goal, __entry->wanted, __entry->empty_root)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_resv_find_winकरोw_prev);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_resv_find_winकरोw_next);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_cannibalize_resv_begin);

TRACE_EVENT(ocfs2_cannibalize_resv_end,
	TP_PROTO(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक last_start, अचिन्हित पूर्णांक last_len),
	TP_ARGS(start, end, len, last_start, last_len),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, start)
		__field(अचिन्हित पूर्णांक, end)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, last_start)
		__field(अचिन्हित पूर्णांक, last_len)
	),
	TP_fast_assign(
		__entry->start = start;
		__entry->end = end;
		__entry->len = len;
		__entry->last_start = last_start;
		__entry->last_len = last_len;
	),
	TP_prपूर्णांकk("%u %u %u %u %u", __entry->start, __entry->end,
		  __entry->len, __entry->last_start, __entry->last_len)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_resmap_resv_bits);

TRACE_EVENT(ocfs2_resmap_claimed_bits_begin,
	TP_PROTO(अचिन्हित पूर्णांक cstart, अचिन्हित पूर्णांक cend, अचिन्हित पूर्णांक clen,
		 अचिन्हित पूर्णांक r_start, अचिन्हित पूर्णांक r_end, अचिन्हित पूर्णांक r_len,
		 अचिन्हित पूर्णांक last_start, अचिन्हित पूर्णांक last_len),
	TP_ARGS(cstart, cend, clen, r_start, r_end,
		r_len, last_start, last_len),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, cstart)
		__field(अचिन्हित पूर्णांक, cend)
		__field(अचिन्हित पूर्णांक, clen)
		__field(अचिन्हित पूर्णांक, r_start)
		__field(अचिन्हित पूर्णांक, r_end)
		__field(अचिन्हित पूर्णांक, r_len)
		__field(अचिन्हित पूर्णांक, last_start)
		__field(अचिन्हित पूर्णांक, last_len)
	),
	TP_fast_assign(
		__entry->cstart = cstart;
		__entry->cend = cend;
		__entry->clen = clen;
		__entry->r_start = r_start;
		__entry->r_end = r_end;
		__entry->r_len = r_len;
		__entry->last_start = last_start;
		__entry->last_len = last_len;
	),
	TP_prपूर्णांकk("%u %u %u %u %u %u %u %u",
		  __entry->cstart, __entry->cend, __entry->clen,
		  __entry->r_start, __entry->r_end, __entry->r_len,
		  __entry->last_start, __entry->last_len)
);

TRACE_EVENT(ocfs2_resmap_claimed_bits_end,
	TP_PROTO(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक last_start, अचिन्हित पूर्णांक last_len),
	TP_ARGS(start, end, len, last_start, last_len),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, start)
		__field(अचिन्हित पूर्णांक, end)
		__field(अचिन्हित पूर्णांक, len)
		__field(अचिन्हित पूर्णांक, last_start)
		__field(अचिन्हित पूर्णांक, last_len)
	),
	TP_fast_assign(
		__entry->start = start;
		__entry->end = end;
		__entry->len = len;
		__entry->last_start = last_start;
		__entry->last_len = last_len;
	),
	TP_prपूर्णांकk("%u %u %u %u %u", __entry->start, __entry->end,
		  __entry->len, __entry->last_start, __entry->last_len)
);

/* End of trace events क्रम fs/ocfs2/reservations.c. */

/* Trace events क्रम fs/ocfs2/quota_local.c. */

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_recover_local_quota_file);

DEFINE_OCFS2_INT_EVENT(ocfs2_finish_quota_recovery);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(olq_set_dquot);

/* End of trace events क्रम fs/ocfs2/quota_local.c. */

/* Trace events क्रम fs/ocfs2/quota_global.c. */

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_quota_block);

TRACE_EVENT(ocfs2_sync_dquot,
	TP_PROTO(अचिन्हित पूर्णांक dq_id, दीर्घ दीर्घ dqb_curspace,
		 दीर्घ दीर्घ spacechange, दीर्घ दीर्घ curinodes,
		 दीर्घ दीर्घ inodechange),
	TP_ARGS(dq_id, dqb_curspace, spacechange, curinodes, inodechange),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, dq_id)
		__field(दीर्घ दीर्घ, dqb_curspace)
		__field(दीर्घ दीर्घ, spacechange)
		__field(दीर्घ दीर्घ, curinodes)
		__field(दीर्घ दीर्घ, inodechange)
	),
	TP_fast_assign(
		__entry->dq_id = dq_id;
		__entry->dqb_curspace = dqb_curspace;
		__entry->spacechange = spacechange;
		__entry->curinodes = curinodes;
		__entry->inodechange = inodechange;
	),
	TP_prपूर्णांकk("%u %lld %lld %lld %lld", __entry->dq_id,
		  __entry->dqb_curspace, __entry->spacechange,
		  __entry->curinodes, __entry->inodechange)
);

TRACE_EVENT(ocfs2_sync_dquot_helper,
	TP_PROTO(अचिन्हित पूर्णांक dq_id, अचिन्हित पूर्णांक dq_type, अचिन्हित दीर्घ type,
		 स्थिर अक्षर *s_id),
	TP_ARGS(dq_id, dq_type, type, s_id),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, dq_id)
		__field(अचिन्हित पूर्णांक, dq_type)
		__field(अचिन्हित दीर्घ, type)
		__string(s_id, s_id)
	),
	TP_fast_assign(
		__entry->dq_id = dq_id;
		__entry->dq_type = dq_type;
		__entry->type = type;
		__assign_str(s_id, s_id);
	),
	TP_prपूर्णांकk("%u %u %lu %s", __entry->dq_id, __entry->dq_type,
		  __entry->type, __get_str(s_id))
);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_ग_लिखो_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_release_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_acquire_dquot);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_get_next_id);

DEFINE_OCFS2_UINT_INT_EVENT(ocfs2_mark_dquot_dirty);

/* End of trace events क्रम fs/ocfs2/quota_global.c. */

/* Trace events क्रम fs/ocfs2/dir.c. */
DEFINE_OCFS2_INT_EVENT(ocfs2_search_dirblock);

DEFINE_OCFS2_ULL_EVENT(ocfs2_validate_dir_block);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_find_entry_el);

TRACE_EVENT(ocfs2_dx_dir_search,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, पूर्णांक namelen, स्थिर अक्षर *name,
		 अचिन्हित पूर्णांक major_hash, अचिन्हित पूर्णांक minor_hash,
		 अचिन्हित दीर्घ दीर्घ blkno),
	TP_ARGS(ino, namelen, name, major_hash, minor_hash, blkno),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(पूर्णांक, namelen)
		__string(name, name)
		__field(अचिन्हित पूर्णांक, major_hash)
		__field(अचिन्हित पूर्णांक,minor_hash)
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->namelen = namelen;
		__assign_str(name, name);
		__entry->major_hash = major_hash;
		__entry->minor_hash = minor_hash;
		__entry->blkno = blkno;
	),
	TP_prपूर्णांकk("%llu %.*s %u %u %llu", __entry->ino,
		   __entry->namelen, __get_str(name),
		  __entry->major_hash, __entry->minor_hash, __entry->blkno)
);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_dx_dir_search_leaf_info);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_delete_entry_dx);

DEFINE_OCFS2_ULL_EVENT(ocfs2_सूची_पढ़ो);

TRACE_EVENT(ocfs2_find_files_on_disk,
	TP_PROTO(पूर्णांक namelen, स्थिर अक्षर *name, व्योम *blkno,
		 अचिन्हित दीर्घ दीर्घ dir),
	TP_ARGS(namelen, name, blkno, dir),
	TP_STRUCT__entry(
		__field(पूर्णांक, namelen)
		__string(name, name)
		__field(व्योम *, blkno)
		__field(अचिन्हित दीर्घ दीर्घ, dir)
	),
	TP_fast_assign(
		__entry->namelen = namelen;
		__assign_str(name, name);
		__entry->blkno = blkno;
		__entry->dir = dir;
	),
	TP_prपूर्णांकk("%.*s %p %llu", __entry->namelen, __get_str(name),
		  __entry->blkno, __entry->dir)
);

TRACE_EVENT(ocfs2_check_dir_क्रम_entry,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ dir, पूर्णांक namelen, स्थिर अक्षर *name),
	TP_ARGS(dir, namelen, name),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, dir)
		__field(पूर्णांक, namelen)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__entry->namelen = namelen;
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%llu %.*s", __entry->dir,
		  __entry->namelen, __get_str(name))
);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_dx_dir_attach_index);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_dx_dir_क्रमmat_cluster);

TRACE_EVENT(ocfs2_dx_dir_index_root_block,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ dir,
		 अचिन्हित पूर्णांक major_hash, अचिन्हित पूर्णांक minor_hash,
		 पूर्णांक namelen, स्थिर अक्षर *name, अचिन्हित पूर्णांक num_used),
	TP_ARGS(dir, major_hash, minor_hash, namelen, name, num_used),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, dir)
		__field(अचिन्हित पूर्णांक, major_hash)
		__field(अचिन्हित पूर्णांक, minor_hash)
		__field(पूर्णांक, namelen)
		__string(name, name)
		__field(अचिन्हित पूर्णांक, num_used)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__entry->major_hash = major_hash;
		__entry->minor_hash = minor_hash;
		__entry->namelen = namelen;
		__assign_str(name, name);
		__entry->num_used = num_used;
	),
	TP_prपूर्णांकk("%llu %x %x %.*s %u", __entry->dir,
		  __entry->major_hash, __entry->minor_hash,
		   __entry->namelen, __get_str(name), __entry->num_used)
);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_extend_dir);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_dx_dir_rebalance);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_dx_dir_rebalance_split);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_prepare_dir_क्रम_insert);

/* End of trace events क्रम fs/ocfs2/dir.c. */

/* Trace events क्रम fs/ocfs2/namei.c. */

DECLARE_EVENT_CLASS(ocfs2__dentry_ops,
	TP_PROTO(व्योम *dir, व्योम *dentry, पूर्णांक name_len, स्थिर अक्षर *name,
		 अचिन्हित दीर्घ दीर्घ dir_blkno, अचिन्हित दीर्घ दीर्घ extra),
	TP_ARGS(dir, dentry, name_len, name, dir_blkno, extra),
	TP_STRUCT__entry(
		__field(व्योम *, dir)
		__field(व्योम *, dentry)
		__field(पूर्णांक, name_len)
		__string(name, name)
		__field(अचिन्हित दीर्घ दीर्घ, dir_blkno)
		__field(अचिन्हित दीर्घ दीर्घ, extra)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__entry->dentry = dentry;
		__entry->name_len = name_len;
		__assign_str(name, name);
		__entry->dir_blkno = dir_blkno;
		__entry->extra = extra;
	),
	TP_prपूर्णांकk("%p %p %.*s %llu %llu", __entry->dir, __entry->dentry,
		  __entry->name_len, __get_str(name),
		  __entry->dir_blkno, __entry->extra)
);

#घोषणा DEFINE_OCFS2_DENTRY_OPS(name)					\
DEFINE_EVENT(ocfs2__dentry_ops, name,					\
TP_PROTO(व्योम *dir, व्योम *dentry, पूर्णांक name_len, स्थिर अक्षर *name,	\
	 अचिन्हित दीर्घ दीर्घ dir_blkno, अचिन्हित दीर्घ दीर्घ extra),	\
	TP_ARGS(dir, dentry, name_len, name, dir_blkno, extra))

DEFINE_OCFS2_DENTRY_OPS(ocfs2_lookup);

DEFINE_OCFS2_DENTRY_OPS(ocfs2_सूची_गढ़ो);

DEFINE_OCFS2_DENTRY_OPS(ocfs2_create);

DEFINE_OCFS2_DENTRY_OPS(ocfs2_unlink);

DEFINE_OCFS2_DENTRY_OPS(ocfs2_symlink_create);

DEFINE_OCFS2_DENTRY_OPS(ocfs2_mv_orphaned_inode_to_new);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_lookup_ret);

TRACE_EVENT(ocfs2_mknod,
	TP_PROTO(व्योम *dir, व्योम *dentry, पूर्णांक name_len, स्थिर अक्षर *name,
		 अचिन्हित दीर्घ दीर्घ dir_blkno, अचिन्हित दीर्घ dev, पूर्णांक mode),
	TP_ARGS(dir, dentry, name_len, name, dir_blkno, dev, mode),
	TP_STRUCT__entry(
		__field(व्योम *, dir)
		__field(व्योम *, dentry)
		__field(पूर्णांक, name_len)
		__string(name, name)
		__field(अचिन्हित दीर्घ दीर्घ, dir_blkno)
		__field(अचिन्हित दीर्घ, dev)
		__field(पूर्णांक, mode)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__entry->dentry = dentry;
		__entry->name_len = name_len;
		__assign_str(name, name);
		__entry->dir_blkno = dir_blkno;
		__entry->dev = dev;
		__entry->mode = mode;
	),
	TP_prपूर्णांकk("%p %p %.*s %llu %lu %d", __entry->dir, __entry->dentry,
		  __entry->name_len, __get_str(name),
		  __entry->dir_blkno, __entry->dev, __entry->mode)
);

TRACE_EVENT(ocfs2_link,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ ino, पूर्णांक old_len, स्थिर अक्षर *old_name,
		 पूर्णांक name_len, स्थिर अक्षर *name),
	TP_ARGS(ino, old_len, old_name, name_len, name),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, ino)
		__field(पूर्णांक, old_len)
		__string(old_name, old_name)
		__field(पूर्णांक, name_len)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->ino = ino;
		__entry->old_len = old_len;
		__assign_str(old_name, old_name);
		__entry->name_len = name_len;
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%llu %.*s %.*s", __entry->ino,
		  __entry->old_len, __get_str(old_name),
		  __entry->name_len, __get_str(name))
);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_unlink_noent);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_द्विगुन_lock);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_द्विगुन_lock_end);

TRACE_EVENT(ocfs2_नाम,
	TP_PROTO(व्योम *old_dir, व्योम *old_dentry,
		 व्योम *new_dir, व्योम *new_dentry,
		 पूर्णांक old_len, स्थिर अक्षर *old_name,
		 पूर्णांक new_len, स्थिर अक्षर *new_name),
	TP_ARGS(old_dir, old_dentry, new_dir, new_dentry,
		old_len, old_name, new_len, new_name),
	TP_STRUCT__entry(
		__field(व्योम *, old_dir)
		__field(व्योम *, old_dentry)
		__field(व्योम *, new_dir)
		__field(व्योम *, new_dentry)
		__field(पूर्णांक, old_len)
		__string(old_name, old_name)
		__field(पूर्णांक, new_len)
		__string(new_name, new_name)
	),
	TP_fast_assign(
		__entry->old_dir = old_dir;
		__entry->old_dentry = old_dentry;
		__entry->new_dir = new_dir;
		__entry->new_dentry = new_dentry;
		__entry->old_len = old_len;
		__assign_str(old_name, old_name);
		__entry->new_len = new_len;
		__assign_str(new_name, new_name);
	),
	TP_prपूर्णांकk("%p %p %p %p %.*s %.*s",
		  __entry->old_dir, __entry->old_dentry,
		  __entry->new_dir, __entry->new_dentry,
		  __entry->old_len, __get_str(old_name),
		  __entry->new_len, __get_str(new_name))
);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_नाम_not_permitted);

TRACE_EVENT(ocfs2_नाम_target_exists,
	TP_PROTO(पूर्णांक new_len, स्थिर अक्षर *new_name),
	TP_ARGS(new_len, new_name),
	TP_STRUCT__entry(
		__field(पूर्णांक, new_len)
		__string(new_name, new_name)
	),
	TP_fast_assign(
		__entry->new_len = new_len;
		__assign_str(new_name, new_name);
	),
	TP_prपूर्णांकk("%.*s", __entry->new_len, __get_str(new_name))
);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_नाम_disagree);

TRACE_EVENT(ocfs2_नाम_over_existing,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ new_blkno, व्योम *new_bh,
		 अचिन्हित दीर्घ दीर्घ newdi_blkno),
	TP_ARGS(new_blkno, new_bh, newdi_blkno),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, new_blkno)
		__field(व्योम *, new_bh)
		__field(अचिन्हित दीर्घ दीर्घ, newdi_blkno)
	),
	TP_fast_assign(
		__entry->new_blkno = new_blkno;
		__entry->new_bh = new_bh;
		__entry->newdi_blkno = newdi_blkno;
	),
	TP_prपूर्णांकk("%llu %p %llu", __entry->new_blkno, __entry->new_bh,
		  __entry->newdi_blkno)
);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_create_symlink_data);

TRACE_EVENT(ocfs2_symlink_begin,
	TP_PROTO(व्योम *dir, व्योम *dentry, स्थिर अक्षर *symname,
		 पूर्णांक len, स्थिर अक्षर *name),
	TP_ARGS(dir, dentry, symname, len, name),
	TP_STRUCT__entry(
		__field(व्योम *, dir)
		__field(व्योम *, dentry)
		__field(स्थिर अक्षर *, symname)
		__field(पूर्णांक, len)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__entry->dentry = dentry;
		__entry->symname = symname;
		__entry->len = len;
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%p %p %s %.*s", __entry->dir, __entry->dentry,
		  __entry->symname, __entry->len, __get_str(name))
);

TRACE_EVENT(ocfs2_blkno_stringअगरy,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ blkno, स्थिर अक्षर *name, पूर्णांक namelen),
	TP_ARGS(blkno, name, namelen),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
		__string(name, name)
		__field(पूर्णांक, namelen)
	),
	TP_fast_assign(
		__entry->blkno = blkno;
		__assign_str(name, name);
		__entry->namelen = namelen;
	),
	TP_prपूर्णांकk("%llu %s %d", __entry->blkno, __get_str(name),
		  __entry->namelen)
);

DEFINE_OCFS2_ULL_EVENT(ocfs2_orphan_add_begin);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_orphan_add_end);

TRACE_EVENT(ocfs2_orphan_del,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ dir, स्थिर अक्षर *name, पूर्णांक namelen),
	TP_ARGS(dir, name, namelen),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, dir)
		__string(name, name)
		__field(पूर्णांक, namelen)
	),
	TP_fast_assign(
		__entry->dir = dir;
		__assign_str(name, name);
		__entry->namelen = namelen;
	),
	TP_prपूर्णांकk("%llu %s %d", __entry->dir, __get_str(name),
		  __entry->namelen)
);

/* End of trace events क्रम fs/ocfs2/namei.c. */

/* Trace events क्रम fs/ocfs2/dcache.c. */

TRACE_EVENT(ocfs2_dentry_revalidate,
	TP_PROTO(व्योम *dentry, पूर्णांक len, स्थिर अक्षर *name),
	TP_ARGS(dentry, len, name),
	TP_STRUCT__entry(
		__field(व्योम *, dentry)
		__field(पूर्णांक, len)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->dentry = dentry;
		__entry->len = len;
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%p %.*s", __entry->dentry, __entry->len, __get_str(name))
);

TRACE_EVENT(ocfs2_dentry_revalidate_negative,
	TP_PROTO(पूर्णांक len, स्थिर अक्षर *name, अचिन्हित दीर्घ pgen,
		 अचिन्हित दीर्घ gen),
	TP_ARGS(len, name, pgen, gen),
	TP_STRUCT__entry(
		__field(पूर्णांक, len)
		__string(name, name)
		__field(अचिन्हित दीर्घ, pgen)
		__field(अचिन्हित दीर्घ, gen)
	),
	TP_fast_assign(
		__entry->len = len;
		__assign_str(name, name);
		__entry->pgen = pgen;
		__entry->gen = gen;
	),
	TP_prपूर्णांकk("%.*s %lu %lu", __entry->len, __get_str(name),
		  __entry->pgen, __entry->gen)
);

DEFINE_OCFS2_ULL_EVENT(ocfs2_dentry_revalidate_delete);

DEFINE_OCFS2_ULL_INT_EVENT(ocfs2_dentry_revalidate_orphaned);

DEFINE_OCFS2_ULL_EVENT(ocfs2_dentry_revalidate_nofsdata);

DEFINE_OCFS2_INT_EVENT(ocfs2_dentry_revalidate_ret);

TRACE_EVENT(ocfs2_find_local_alias,
	TP_PROTO(पूर्णांक len, स्थिर अक्षर *name),
	TP_ARGS(len, name),
	TP_STRUCT__entry(
		__field(पूर्णांक, len)
		__string(name, name)
	),
	TP_fast_assign(
		__entry->len = len;
		__assign_str(name, name);
	),
	TP_prपूर्णांकk("%.*s", __entry->len, __get_str(name))
);

TRACE_EVENT(ocfs2_dentry_attach_lock,
	TP_PROTO(पूर्णांक len, स्थिर अक्षर *name,
		 अचिन्हित दीर्घ दीर्घ parent, व्योम *fsdata),
	TP_ARGS(len, name, parent, fsdata),
	TP_STRUCT__entry(
		__field(पूर्णांक, len)
		__string(name, name)
		__field(अचिन्हित दीर्घ दीर्घ, parent)
		__field(व्योम *, fsdata)
	),
	TP_fast_assign(
		__entry->len = len;
		__assign_str(name, name);
		__entry->parent = parent;
		__entry->fsdata = fsdata;
	),
	TP_prपूर्णांकk("%.*s %llu %p", __entry->len, __get_str(name),
		  __entry->parent, __entry->fsdata)
);

TRACE_EVENT(ocfs2_dentry_attach_lock_found,
	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ दीर्घ parent,
		 अचिन्हित दीर्घ दीर्घ ino),
	TP_ARGS(name, parent, ino),
	TP_STRUCT__entry(
		__string(name, name)
		__field(अचिन्हित दीर्घ दीर्घ, parent)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
	),
	TP_fast_assign(
		__assign_str(name, name);
		__entry->parent = parent;
		__entry->ino = ino;
	),
	TP_prपूर्णांकk("%s %llu %llu", __get_str(name), __entry->parent, __entry->ino)
);
/* End of trace events क्रम fs/ocfs2/dcache.c. */

/* Trace events क्रम fs/ocfs2/export.c. */

TRACE_EVENT(ocfs2_get_dentry_begin,
	TP_PROTO(व्योम *sb, व्योम *handle, अचिन्हित दीर्घ दीर्घ blkno),
	TP_ARGS(sb, handle, blkno),
	TP_STRUCT__entry(
		__field(व्योम *, sb)
		__field(व्योम *, handle)
		__field(अचिन्हित दीर्घ दीर्घ, blkno)
	),
	TP_fast_assign(
		__entry->sb = sb;
		__entry->handle = handle;
		__entry->blkno = blkno;
	),
	TP_prपूर्णांकk("%p %p %llu", __entry->sb, __entry->handle, __entry->blkno)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_get_dentry_test_bit);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_get_dentry_stale);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_get_dentry_generation);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_get_dentry_end);

TRACE_EVENT(ocfs2_get_parent,
	TP_PROTO(व्योम *child, पूर्णांक len, स्थिर अक्षर *name,
		 अचिन्हित दीर्घ दीर्घ ino),
	TP_ARGS(child, len, name, ino),
	TP_STRUCT__entry(
		__field(व्योम *,	child)
		__field(पूर्णांक, len)
		__string(name, name)
		__field(अचिन्हित दीर्घ दीर्घ, ino)
	),
	TP_fast_assign(
		__entry->child = child;
		__entry->len = len;
		__assign_str(name, name);
		__entry->ino = ino;
	),
	TP_prपूर्णांकk("%p %.*s %llu", __entry->child, __entry->len,
		  __get_str(name), __entry->ino)
);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_get_parent_end);

TRACE_EVENT(ocfs2_encode_fh_begin,
	TP_PROTO(व्योम *dentry, पूर्णांक name_len, स्थिर अक्षर *name,
		 व्योम *fh, पूर्णांक len, पूर्णांक connectable),
	TP_ARGS(dentry, name_len, name, fh, len, connectable),
	TP_STRUCT__entry(
		__field(व्योम *, dentry)
		__field(पूर्णांक, name_len)
		__string(name, name)
		__field(व्योम *, fh)
		__field(पूर्णांक, len)
		__field(पूर्णांक, connectable)
	),
	TP_fast_assign(
		__entry->dentry = dentry;
		__entry->name_len = name_len;
		__assign_str(name, name);
		__entry->fh = fh;
		__entry->len = len;
		__entry->connectable = connectable;
	),
	TP_prपूर्णांकk("%p %.*s %p %d %d", __entry->dentry, __entry->name_len,
		  __get_str(name), __entry->fh, __entry->len,
		  __entry->connectable)
);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_encode_fh_self);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_encode_fh_parent);

DEFINE_OCFS2_INT_EVENT(ocfs2_encode_fh_type);

/* End of trace events क्रम fs/ocfs2/export.c. */

/* Trace events क्रम fs/ocfs2/journal.c. */

DEFINE_OCFS2_UINT_EVENT(ocfs2_commit_cache_begin);

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_commit_cache_end);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_extend_trans);

DEFINE_OCFS2_INT_EVENT(ocfs2_extend_trans_restart);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_allocate_extend_trans);

DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(ocfs2_journal_access);

DEFINE_OCFS2_ULL_EVENT(ocfs2_journal_dirty);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_journal_init);

DEFINE_OCFS2_UINT_EVENT(ocfs2_journal_init_maxlen);

DEFINE_OCFS2_INT_EVENT(ocfs2_journal_shutकरोwn);

DEFINE_OCFS2_POINTER_EVENT(ocfs2_journal_shutकरोwn_रुको);

DEFINE_OCFS2_ULL_EVENT(ocfs2_complete_recovery);

DEFINE_OCFS2_INT_EVENT(ocfs2_complete_recovery_end);

TRACE_EVENT(ocfs2_complete_recovery_slot,
	TP_PROTO(पूर्णांक slot, अचिन्हित दीर्घ दीर्घ la_ino,
		 अचिन्हित दीर्घ दीर्घ tl_ino, व्योम *qrec),
	TP_ARGS(slot, la_ino, tl_ino, qrec),
	TP_STRUCT__entry(
		__field(पूर्णांक, slot)
		__field(अचिन्हित दीर्घ दीर्घ, la_ino)
		__field(अचिन्हित दीर्घ दीर्घ, tl_ino)
		__field(व्योम *, qrec)
	),
	TP_fast_assign(
		__entry->slot = slot;
		__entry->la_ino = la_ino;
		__entry->tl_ino = tl_ino;
		__entry->qrec = qrec;
	),
	TP_prपूर्णांकk("%d %llu %llu %p", __entry->slot, __entry->la_ino,
		  __entry->tl_ino, __entry->qrec)
);

DEFINE_OCFS2_INT_INT_EVENT(ocfs2_recovery_thपढ़ो_node);

DEFINE_OCFS2_INT_EVENT(ocfs2_recovery_thपढ़ो_end);

TRACE_EVENT(ocfs2_recovery_thपढ़ो,
	TP_PROTO(पूर्णांक node_num, पूर्णांक osb_node_num, पूर्णांक disable,
		 व्योम *recovery_thपढ़ो, पूर्णांक map_set),
	TP_ARGS(node_num, osb_node_num, disable, recovery_thपढ़ो, map_set),
	TP_STRUCT__entry(
		__field(पूर्णांक, node_num)
		__field(पूर्णांक, osb_node_num)
		__field(पूर्णांक,disable)
		__field(व्योम *, recovery_thपढ़ो)
		__field(पूर्णांक,map_set)
	),
	TP_fast_assign(
		__entry->node_num = node_num;
		__entry->osb_node_num = osb_node_num;
		__entry->disable = disable;
		__entry->recovery_thपढ़ो = recovery_thपढ़ो;
		__entry->map_set = map_set;
	),
	TP_prपूर्णांकk("%d %d %d %p %d", __entry->node_num,
		   __entry->osb_node_num, __entry->disable,
		   __entry->recovery_thपढ़ो, __entry->map_set)
);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_replay_journal_recovered);

DEFINE_OCFS2_INT_EVENT(ocfs2_replay_journal_lock_err);

DEFINE_OCFS2_INT_EVENT(ocfs2_replay_journal_skip);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_recover_node);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_recover_node_skip);

DEFINE_OCFS2_UINT_UINT_EVENT(ocfs2_mark_dead_nodes);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_queue_orphan_scan_begin);

DEFINE_OCFS2_UINT_UINT_UINT_EVENT(ocfs2_queue_orphan_scan_end);

DEFINE_OCFS2_ULL_EVENT(ocfs2_orphan_filldir);

DEFINE_OCFS2_INT_EVENT(ocfs2_recover_orphans);

DEFINE_OCFS2_ULL_EVENT(ocfs2_recover_orphans_iput);

DEFINE_OCFS2_INT_EVENT(ocfs2_रुको_on_mount);

/* End of trace events क्रम fs/ocfs2/journal.c. */

/* Trace events क्रम fs/ocfs2/buffer_head_io.c. */

DEFINE_OCFS2_ULL_UINT_EVENT(ocfs2_पढ़ो_blocks_sync);

DEFINE_OCFS2_ULL_EVENT(ocfs2_पढ़ो_blocks_sync_jbd);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_पढ़ो_blocks_from_disk);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_पढ़ो_blocks_bh);

DEFINE_OCFS2_ULL_INT_INT_INT_EVENT(ocfs2_पढ़ो_blocks_end);

TRACE_EVENT(ocfs2_ग_लिखो_block,
	TP_PROTO(अचिन्हित दीर्घ दीर्घ block, व्योम *ci),
	TP_ARGS(block, ci),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ दीर्घ, block)
		__field(व्योम *, ci)
	),
	TP_fast_assign(
		__entry->block = block;
		__entry->ci = ci;
	),
	TP_prपूर्णांकk("%llu %p", __entry->block, __entry->ci)
);

TRACE_EVENT(ocfs2_पढ़ो_blocks_begin,
	TP_PROTO(व्योम *ci, अचिन्हित दीर्घ दीर्घ block,
		 अचिन्हित पूर्णांक nr, पूर्णांक flags),
	TP_ARGS(ci, block, nr, flags),
	TP_STRUCT__entry(
		__field(व्योम *, ci)
		__field(अचिन्हित दीर्घ दीर्घ, block)
		__field(अचिन्हित पूर्णांक, nr)
		__field(पूर्णांक, flags)
	),
	TP_fast_assign(
		__entry->ci = ci;
		__entry->block = block;
		__entry->nr = nr;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%p %llu %u %d", __entry->ci, __entry->block,
		  __entry->nr, __entry->flags)
);

/* End of trace events क्रम fs/ocfs2/buffer_head_io.c. */

/* Trace events क्रम fs/ocfs2/uptodate.c. */

DEFINE_OCFS2_ULL_EVENT(ocfs2_purge_copied_metadata_tree);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_metadata_cache_purge);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_buffer_cached_begin);

TRACE_EVENT(ocfs2_buffer_cached_end,
	TP_PROTO(पूर्णांक index, व्योम *item),
	TP_ARGS(index, item),
	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__field(व्योम *, item)
	),
	TP_fast_assign(
		__entry->index = index;
		__entry->item = item;
	),
	TP_prपूर्णांकk("%d %p", __entry->index, __entry->item)
);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_append_cache_array);

DEFINE_OCFS2_ULL_ULL_UINT_EVENT(ocfs2_insert_cache_tree);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_expand_cache);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_set_buffer_uptodate);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_set_buffer_uptodate_begin);

DEFINE_OCFS2_ULL_UINT_UINT_EVENT(ocfs2_हटाओ_metadata_array);

DEFINE_OCFS2_ULL_ULL_EVENT(ocfs2_हटाओ_metadata_tree);

DEFINE_OCFS2_ULL_ULL_UINT_UINT_EVENT(ocfs2_हटाओ_block_from_cache);

/* End of trace events क्रम fs/ocfs2/uptodate.c. */
#पूर्ण_अगर /* _TRACE_OCFS2_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता ocfs2_trace
#समावेश <trace/define_trace.h>
