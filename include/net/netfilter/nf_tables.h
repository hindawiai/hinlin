<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_NF_TABLES_H
#घोषणा _NET_NF_TABLES_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/list.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netlink.h>
#समावेश <net/flow_offload.h>
#समावेश <net/netns/generic.h>

#घोषणा NFT_MAX_HOOKS	(NF_INET_INGRESS + 1)

काष्ठा module;

#घोषणा NFT_JUMP_STACK_SIZE	16

काष्ठा nft_pktinfo अणु
	काष्ठा sk_buff			*skb;
	bool				tprot_set;
	u8				tprot;
	/* क्रम x_tables compatibility */
	काष्ठा xt_action_param		xt;
पूर्ण;

अटल अंतरभूत काष्ठा net *nft_net(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	वापस pkt->xt.state->net;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nft_hook(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	वापस pkt->xt.state->hook;
पूर्ण

अटल अंतरभूत u8 nft_pf(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	वापस pkt->xt.state->pf;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा net_device *nft_in(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	वापस pkt->xt.state->in;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा net_device *nft_out(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	वापस pkt->xt.state->out;
पूर्ण

अटल अंतरभूत व्योम nft_set_pktinfo(काष्ठा nft_pktinfo *pkt,
				   काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nf_hook_state *state)
अणु
	pkt->skb = skb;
	pkt->xt.state = state;
पूर्ण

अटल अंतरभूत व्योम nft_set_pktinfo_unspec(काष्ठा nft_pktinfo *pkt,
					  काष्ठा sk_buff *skb)
अणु
	pkt->tprot_set = false;
	pkt->tprot = 0;
	pkt->xt.thoff = 0;
	pkt->xt.fragoff = 0;
पूर्ण

/**
 * 	काष्ठा nft_verdict - nf_tables verdict
 *
 * 	@code: nf_tables/netfilter verdict code
 * 	@chain: destination chain क्रम NFT_JUMP/NFT_GOTO
 */
काष्ठा nft_verdict अणु
	u32				code;
	काष्ठा nft_chain		*chain;
पूर्ण;

काष्ठा nft_data अणु
	जोड़ अणु
		u32			data[4];
		काष्ठा nft_verdict	verdict;
	पूर्ण;
पूर्ण __attribute__((aligned(__alignof__(u64))));

/**
 *	काष्ठा nft_regs - nf_tables रेजिस्टर set
 *
 *	@data: data रेजिस्टरs
 *	@verdict: verdict रेजिस्टर
 *
 *	The first four data रेजिस्टरs alias to the verdict रेजिस्टर.
 */
काष्ठा nft_regs अणु
	जोड़ अणु
		u32			data[20];
		काष्ठा nft_verdict	verdict;
	पूर्ण;
पूर्ण;

/* Store/load an u8, u16 or u64 पूर्णांकeger to/from the u32 data रेजिस्टर.
 *
 * Note, when using concatenations, रेजिस्टर allocation happens at 32-bit
 * level. So क्रम store inकाष्ठाion, pad the rest part with zero to aव्योम
 * garbage values.
 */

अटल अंतरभूत व्योम nft_reg_store8(u32 *dreg, u8 val)
अणु
	*dreg = 0;
	*(u8 *)dreg = val;
पूर्ण

अटल अंतरभूत u8 nft_reg_load8(स्थिर u32 *sreg)
अणु
	वापस *(u8 *)sreg;
पूर्ण

अटल अंतरभूत व्योम nft_reg_store16(u32 *dreg, u16 val)
अणु
	*dreg = 0;
	*(u16 *)dreg = val;
पूर्ण

अटल अंतरभूत u16 nft_reg_load16(स्थिर u32 *sreg)
अणु
	वापस *(u16 *)sreg;
पूर्ण

अटल अंतरभूत व्योम nft_reg_store64(u32 *dreg, u64 val)
अणु
	put_unaligned(val, (u64 *)dreg);
पूर्ण

अटल अंतरभूत u64 nft_reg_load64(स्थिर u32 *sreg)
अणु
	वापस get_unaligned((u64 *)sreg);
पूर्ण

अटल अंतरभूत व्योम nft_data_copy(u32 *dst, स्थिर काष्ठा nft_data *src,
				 अचिन्हित पूर्णांक len)
अणु
	अगर (len % NFT_REG32_SIZE)
		dst[len / NFT_REG32_SIZE] = 0;
	स_नकल(dst, src, len);
पूर्ण

/**
 *	काष्ठा nft_ctx - nf_tables rule/set context
 *
 *	@net: net namespace
 * 	@table: the table the chain is contained in
 * 	@chain: the chain the rule is contained in
 *	@nla: netlink attributes
 *	@portid: netlink portID of the original message
 *	@seq: netlink sequence number
 *	@family: protocol family
 *	@level: depth of the chains
 *	@report: notअगरy via unicast netlink message
 */
काष्ठा nft_ctx अणु
	काष्ठा net			*net;
	काष्ठा nft_table		*table;
	काष्ठा nft_chain		*chain;
	स्थिर काष्ठा nlattr * स्थिर 	*nla;
	u32				portid;
	u32				seq;
	u16				flags;
	u8				family;
	u8				level;
	bool				report;
पूर्ण;

काष्ठा nft_data_desc अणु
	क्रमागत nft_data_types		type;
	अचिन्हित पूर्णांक			len;
पूर्ण;

पूर्णांक nft_data_init(स्थिर काष्ठा nft_ctx *ctx,
		  काष्ठा nft_data *data, अचिन्हित पूर्णांक size,
		  काष्ठा nft_data_desc *desc, स्थिर काष्ठा nlattr *nla);
व्योम nft_data_hold(स्थिर काष्ठा nft_data *data, क्रमागत nft_data_types type);
व्योम nft_data_release(स्थिर काष्ठा nft_data *data, क्रमागत nft_data_types type);
पूर्णांक nft_data_dump(काष्ठा sk_buff *skb, पूर्णांक attr, स्थिर काष्ठा nft_data *data,
		  क्रमागत nft_data_types type, अचिन्हित पूर्णांक len);

अटल अंतरभूत क्रमागत nft_data_types nft_dreg_to_type(क्रमागत nft_रेजिस्टरs reg)
अणु
	वापस reg == NFT_REG_VERDICT ? NFT_DATA_VERDICT : NFT_DATA_VALUE;
पूर्ण

अटल अंतरभूत क्रमागत nft_रेजिस्टरs nft_type_to_reg(क्रमागत nft_data_types type)
अणु
	वापस type == NFT_DATA_VERDICT ? NFT_REG_VERDICT : NFT_REG_1 * NFT_REG_SIZE / NFT_REG32_SIZE;
पूर्ण

पूर्णांक nft_parse_u32_check(स्थिर काष्ठा nlattr *attr, पूर्णांक max, u32 *dest);
पूर्णांक nft_dump_रेजिस्टर(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक attr, अचिन्हित पूर्णांक reg);

पूर्णांक nft_parse_रेजिस्टर_load(स्थिर काष्ठा nlattr *attr, u8 *sreg, u32 len);
पूर्णांक nft_parse_रेजिस्टर_store(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nlattr *attr, u8 *dreg,
			     स्थिर काष्ठा nft_data *data,
			     क्रमागत nft_data_types type, अचिन्हित पूर्णांक len);

/**
 *	काष्ठा nft_userdata - user defined data associated with an object
 *
 *	@len: length of the data
 *	@data: content
 *
 *	The presence of user data is indicated in an object specअगरic fashion,
 *	so a length of zero can't occur and the value "len" indicates data
 *	of length len + 1.
 */
काष्ठा nft_userdata अणु
	u8			len;
	अचिन्हित अक्षर		data[];
पूर्ण;

/**
 *	काष्ठा nft_set_elem - generic representation of set elements
 *
 *	@key: element key
 *	@key_end: closing element key
 *	@priv: element निजी data and extensions
 */
काष्ठा nft_set_elem अणु
	जोड़ अणु
		u32		buf[NFT_DATA_VALUE_MAXLEN / माप(u32)];
		काष्ठा nft_data	val;
	पूर्ण key;
	जोड़ अणु
		u32		buf[NFT_DATA_VALUE_MAXLEN / माप(u32)];
		काष्ठा nft_data	val;
	पूर्ण key_end;
	जोड़ अणु
		u32		buf[NFT_DATA_VALUE_MAXLEN / माप(u32)];
		काष्ठा nft_data val;
	पूर्ण data;
	व्योम			*priv;
पूर्ण;

काष्ठा nft_set;
काष्ठा nft_set_iter अणु
	u8		genmask;
	अचिन्हित पूर्णांक	count;
	अचिन्हित पूर्णांक	skip;
	पूर्णांक		err;
	पूर्णांक		(*fn)(स्थिर काष्ठा nft_ctx *ctx,
			      काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_iter *iter,
			      काष्ठा nft_set_elem *elem);
पूर्ण;

/**
 *	काष्ठा nft_set_desc - description of set elements
 *
 *	@klen: key length
 *	@dlen: data length
 *	@size: number of set elements
 *	@field_len: length of each field in concatenation, bytes
 *	@field_count: number of concatenated fields in element
 *	@expr: set must support क्रम expressions
 */
काष्ठा nft_set_desc अणु
	अचिन्हित पूर्णांक		klen;
	अचिन्हित पूर्णांक		dlen;
	अचिन्हित पूर्णांक		size;
	u8			field_len[NFT_REG32_COUNT];
	u8			field_count;
	bool			expr;
पूर्ण;

/**
 *	क्रमागत nft_set_class - perक्रमmance class
 *
 *	@NFT_LOOKUP_O_1: स्थिरant, O(1)
 *	@NFT_LOOKUP_O_LOG_N: logarithmic, O(log N)
 *	@NFT_LOOKUP_O_N: linear, O(N)
 */
क्रमागत nft_set_class अणु
	NFT_SET_CLASS_O_1,
	NFT_SET_CLASS_O_LOG_N,
	NFT_SET_CLASS_O_N,
पूर्ण;

/**
 *	काष्ठा nft_set_estimate - estimation of memory and perक्रमmance
 *				  अक्षरacteristics
 *
 *	@size: required memory
 *	@lookup: lookup perक्रमmance class
 *	@space: memory class
 */
काष्ठा nft_set_estimate अणु
	u64			size;
	क्रमागत nft_set_class	lookup;
	क्रमागत nft_set_class	space;
पूर्ण;

#घोषणा NFT_EXPR_MAXATTR		16
#घोषणा NFT_EXPR_SIZE(size)		(माप(काष्ठा nft_expr) + \
					 ALIGN(size, __alignof__(काष्ठा nft_expr)))

/**
 *	काष्ठा nft_expr - nf_tables expression
 *
 *	@ops: expression ops
 *	@data: expression निजी data
 */
काष्ठा nft_expr अणु
	स्थिर काष्ठा nft_expr_ops	*ops;
	अचिन्हित अक्षर			data[]
		__attribute__((aligned(__alignof__(u64))));
पूर्ण;

अटल अंतरभूत व्योम *nft_expr_priv(स्थिर काष्ठा nft_expr *expr)
अणु
	वापस (व्योम *)expr->data;
पूर्ण

पूर्णांक nft_expr_clone(काष्ठा nft_expr *dst, काष्ठा nft_expr *src);
व्योम nft_expr_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_expr *expr);
पूर्णांक nft_expr_dump(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक attr,
		  स्थिर काष्ठा nft_expr *expr);

काष्ठा nft_set_ext;

/**
 *	काष्ठा nft_set_ops - nf_tables set operations
 *
 *	@lookup: look up an element within the set
 *	@update: update an element अगर exists, add it अगर करोesn't exist
 *	@delete: delete an element
 *	@insert: insert new element पूर्णांकo set
 *	@activate: activate new element in the next generation
 *	@deactivate: lookup क्रम element and deactivate it in the next generation
 *	@flush: deactivate element in the next generation
 *	@हटाओ: हटाओ element from set
 *	@walk: iterate over all set elements
 *	@get: get set elements
 *	@privsize: function to वापस size of set निजी data
 *	@init: initialize निजी data of new set instance
 *	@destroy: destroy निजी data of set instance
 *	@elemsize: element निजी size
 *
 *	Operations lookup, update and delete have simpler पूर्णांकerfaces, are faster
 *	and currently only used in the packet path. All the rest are slower,
 *	control plane functions.
 */
काष्ठा nft_set_ops अणु
	bool				(*lookup)(स्थिर काष्ठा net *net,
						  स्थिर काष्ठा nft_set *set,
						  स्थिर u32 *key,
						  स्थिर काष्ठा nft_set_ext **ext);
	bool				(*update)(काष्ठा nft_set *set,
						  स्थिर u32 *key,
						  व्योम *(*new)(काष्ठा nft_set *,
							       स्थिर काष्ठा nft_expr *,
							       काष्ठा nft_regs *),
						  स्थिर काष्ठा nft_expr *expr,
						  काष्ठा nft_regs *regs,
						  स्थिर काष्ठा nft_set_ext **ext);
	bool				(*delete)(स्थिर काष्ठा nft_set *set,
						  स्थिर u32 *key);

	पूर्णांक				(*insert)(स्थिर काष्ठा net *net,
						  स्थिर काष्ठा nft_set *set,
						  स्थिर काष्ठा nft_set_elem *elem,
						  काष्ठा nft_set_ext **ext);
	व्योम				(*activate)(स्थिर काष्ठा net *net,
						    स्थिर काष्ठा nft_set *set,
						    स्थिर काष्ठा nft_set_elem *elem);
	व्योम *				(*deactivate)(स्थिर काष्ठा net *net,
						      स्थिर काष्ठा nft_set *set,
						      स्थिर काष्ठा nft_set_elem *elem);
	bool				(*flush)(स्थिर काष्ठा net *net,
						 स्थिर काष्ठा nft_set *set,
						 व्योम *priv);
	व्योम				(*हटाओ)(स्थिर काष्ठा net *net,
						  स्थिर काष्ठा nft_set *set,
						  स्थिर काष्ठा nft_set_elem *elem);
	व्योम				(*walk)(स्थिर काष्ठा nft_ctx *ctx,
						काष्ठा nft_set *set,
						काष्ठा nft_set_iter *iter);
	व्योम *				(*get)(स्थिर काष्ठा net *net,
					       स्थिर काष्ठा nft_set *set,
					       स्थिर काष्ठा nft_set_elem *elem,
					       अचिन्हित पूर्णांक flags);

	u64				(*privsize)(स्थिर काष्ठा nlattr * स्थिर nla[],
						    स्थिर काष्ठा nft_set_desc *desc);
	bool				(*estimate)(स्थिर काष्ठा nft_set_desc *desc,
						    u32 features,
						    काष्ठा nft_set_estimate *est);
	पूर्णांक				(*init)(स्थिर काष्ठा nft_set *set,
						स्थिर काष्ठा nft_set_desc *desc,
						स्थिर काष्ठा nlattr * स्थिर nla[]);
	व्योम				(*destroy)(स्थिर काष्ठा nft_set *set);
	व्योम				(*gc_init)(स्थिर काष्ठा nft_set *set);

	अचिन्हित पूर्णांक			elemsize;
पूर्ण;

/**
 *      काष्ठा nft_set_type - nf_tables set type
 *
 *      @ops: set ops क्रम this type
 *      @features: features supported by the implementation
 */
काष्ठा nft_set_type अणु
	स्थिर काष्ठा nft_set_ops	ops;
	u32				features;
पूर्ण;
#घोषणा to_set_type(o) container_of(o, काष्ठा nft_set_type, ops)

काष्ठा nft_set_elem_expr अणु
	u8				size;
	अचिन्हित अक्षर			data[]
		__attribute__((aligned(__alignof__(काष्ठा nft_expr))));
पूर्ण;

#घोषणा nft_setelem_expr_at(__elem_expr, __offset)			\
	((काष्ठा nft_expr *)&__elem_expr->data[__offset])

#घोषणा nft_setelem_expr_क्रमeach(__expr, __elem_expr, __size)		\
	क्रम (__expr = nft_setelem_expr_at(__elem_expr, 0), __size = 0;	\
	     __size < (__elem_expr)->size;				\
	     __size += (__expr)->ops->size, __expr = ((व्योम *)(__expr)) + (__expr)->ops->size)

#घोषणा NFT_SET_EXPR_MAX	2

/**
 * 	काष्ठा nft_set - nf_tables set instance
 *
 *	@list: table set list node
 *	@bindings: list of set bindings
 *	@table: table this set beदीर्घs to
 *	@net: netnamespace this set beदीर्घs to
 * 	@name: name of the set
 *	@handle: unique handle of the set
 * 	@ktype: key type (numeric type defined by userspace, not used in the kernel)
 * 	@dtype: data type (verdict or numeric type defined by userspace)
 * 	@objtype: object type (see NFT_OBJECT_* definitions)
 * 	@size: maximum set size
 *	@field_len: length of each field in concatenation, bytes
 *	@field_count: number of concatenated fields in element
 *	@use: number of rules references to this set
 * 	@nelems: number of elements
 * 	@ndeact: number of deactivated elements queued क्रम removal
 *	@समयout: शेष समयout value in jअगरfies
 * 	@gc_पूर्णांक: garbage collection पूर्णांकerval in msecs
 *	@policy: set parameterization (see क्रमागत nft_set_policies)
 *	@udlen: user data length
 *	@udata: user data
 *	@expr: stateful expression
 * 	@ops: set ops
 * 	@flags: set flags
 *	@genmask: generation mask
 * 	@klen: key length
 * 	@dlen: data length
 * 	@data: निजी set data
 */
काष्ठा nft_set अणु
	काष्ठा list_head		list;
	काष्ठा list_head		bindings;
	काष्ठा nft_table		*table;
	possible_net_t			net;
	अक्षर				*name;
	u64				handle;
	u32				ktype;
	u32				dtype;
	u32				objtype;
	u32				size;
	u8				field_len[NFT_REG32_COUNT];
	u8				field_count;
	u32				use;
	atomic_t			nelems;
	u32				ndeact;
	u64				समयout;
	u32				gc_पूर्णांक;
	u16				policy;
	u16				udlen;
	अचिन्हित अक्षर			*udata;
	/* runसमय data below here */
	स्थिर काष्ठा nft_set_ops	*ops ____cacheline_aligned;
	u16				flags:14,
					genmask:2;
	u8				klen;
	u8				dlen;
	u8				num_exprs;
	काष्ठा nft_expr			*exprs[NFT_SET_EXPR_MAX];
	काष्ठा list_head		catchall_list;
	अचिन्हित अक्षर			data[]
		__attribute__((aligned(__alignof__(u64))));
पूर्ण;

अटल अंतरभूत bool nft_set_is_anonymous(स्थिर काष्ठा nft_set *set)
अणु
	वापस set->flags & NFT_SET_ANONYMOUS;
पूर्ण

अटल अंतरभूत व्योम *nft_set_priv(स्थिर काष्ठा nft_set *set)
अणु
	वापस (व्योम *)set->data;
पूर्ण

अटल अंतरभूत काष्ठा nft_set *nft_set_container_of(स्थिर व्योम *priv)
अणु
	वापस (व्योम *)priv - दुरत्व(काष्ठा nft_set, data);
पूर्ण

काष्ठा nft_set *nft_set_lookup_global(स्थिर काष्ठा net *net,
				      स्थिर काष्ठा nft_table *table,
				      स्थिर काष्ठा nlattr *nla_set_name,
				      स्थिर काष्ठा nlattr *nla_set_id,
				      u8 genmask);

काष्ठा nft_set_ext *nft_set_catchall_lookup(स्थिर काष्ठा net *net,
					    स्थिर काष्ठा nft_set *set);
व्योम *nft_set_catchall_gc(स्थिर काष्ठा nft_set *set);

अटल अंतरभूत अचिन्हित दीर्घ nft_set_gc_पूर्णांकerval(स्थिर काष्ठा nft_set *set)
अणु
	वापस set->gc_पूर्णांक ? msecs_to_jअगरfies(set->gc_पूर्णांक) : HZ;
पूर्ण

/**
 *	काष्ठा nft_set_binding - nf_tables set binding
 *
 *	@list: set bindings list node
 *	@chain: chain containing the rule bound to the set
 *	@flags: set action flags
 *
 *	A set binding contains all inक्रमmation necessary क्रम validation
 *	of new elements added to a bound set.
 */
काष्ठा nft_set_binding अणु
	काष्ठा list_head		list;
	स्थिर काष्ठा nft_chain		*chain;
	u32				flags;
पूर्ण;

क्रमागत nft_trans_phase;
व्योम nf_tables_deactivate_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			      काष्ठा nft_set_binding *binding,
			      क्रमागत nft_trans_phase phase);
पूर्णांक nf_tables_bind_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
		       काष्ठा nft_set_binding *binding);
व्योम nf_tables_destroy_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set);

/**
 *	क्रमागत nft_set_extensions - set extension type IDs
 *
 *	@NFT_SET_EXT_KEY: element key
 *	@NFT_SET_EXT_KEY_END: upper bound element key, क्रम ranges
 *	@NFT_SET_EXT_DATA: mapping data
 *	@NFT_SET_EXT_FLAGS: element flags
 *	@NFT_SET_EXT_TIMEOUT: element समयout
 *	@NFT_SET_EXT_EXPIRATION: element expiration समय
 *	@NFT_SET_EXT_USERDATA: user data associated with the element
 *	@NFT_SET_EXT_EXPRESSIONS: expressions assiciated with the element
 *	@NFT_SET_EXT_OBJREF: stateful object reference associated with element
 *	@NFT_SET_EXT_NUM: number of extension types
 */
क्रमागत nft_set_extensions अणु
	NFT_SET_EXT_KEY,
	NFT_SET_EXT_KEY_END,
	NFT_SET_EXT_DATA,
	NFT_SET_EXT_FLAGS,
	NFT_SET_EXT_TIMEOUT,
	NFT_SET_EXT_EXPIRATION,
	NFT_SET_EXT_USERDATA,
	NFT_SET_EXT_EXPRESSIONS,
	NFT_SET_EXT_OBJREF,
	NFT_SET_EXT_NUM
पूर्ण;

/**
 *	काष्ठा nft_set_ext_type - set extension type
 *
 * 	@len: fixed part length of the extension
 * 	@align: alignment requirements of the extension
 */
काष्ठा nft_set_ext_type अणु
	u8	len;
	u8	align;
पूर्ण;

बाह्य स्थिर काष्ठा nft_set_ext_type nft_set_ext_types[];

/**
 *	काष्ठा nft_set_ext_पंचांगpl - set extension ढाँचा
 *
 *	@len: length of extension area
 *	@offset: offsets of inभागidual extension types
 */
काष्ठा nft_set_ext_पंचांगpl अणु
	u16	len;
	u8	offset[NFT_SET_EXT_NUM];
पूर्ण;

/**
 *	काष्ठा nft_set_ext - set extensions
 *
 *	@genmask: generation mask
 *	@offset: offsets of inभागidual extension types
 *	@data: beginning of extension data
 */
काष्ठा nft_set_ext अणु
	u8	genmask;
	u8	offset[NFT_SET_EXT_NUM];
	अक्षर	data[];
पूर्ण;

अटल अंतरभूत व्योम nft_set_ext_prepare(काष्ठा nft_set_ext_पंचांगpl *पंचांगpl)
अणु
	स_रखो(पंचांगpl, 0, माप(*पंचांगpl));
	पंचांगpl->len = माप(काष्ठा nft_set_ext);
पूर्ण

अटल अंतरभूत व्योम nft_set_ext_add_length(काष्ठा nft_set_ext_पंचांगpl *पंचांगpl, u8 id,
					  अचिन्हित पूर्णांक len)
अणु
	पंचांगpl->len	 = ALIGN(पंचांगpl->len, nft_set_ext_types[id].align);
	BUG_ON(पंचांगpl->len > U8_MAX);
	पंचांगpl->offset[id] = पंचांगpl->len;
	पंचांगpl->len	+= nft_set_ext_types[id].len + len;
पूर्ण

अटल अंतरभूत व्योम nft_set_ext_add(काष्ठा nft_set_ext_पंचांगpl *पंचांगpl, u8 id)
अणु
	nft_set_ext_add_length(पंचांगpl, id, 0);
पूर्ण

अटल अंतरभूत व्योम nft_set_ext_init(काष्ठा nft_set_ext *ext,
				    स्थिर काष्ठा nft_set_ext_पंचांगpl *पंचांगpl)
अणु
	स_नकल(ext->offset, पंचांगpl->offset, माप(ext->offset));
पूर्ण

अटल अंतरभूत bool __nft_set_ext_exists(स्थिर काष्ठा nft_set_ext *ext, u8 id)
अणु
	वापस !!ext->offset[id];
पूर्ण

अटल अंतरभूत bool nft_set_ext_exists(स्थिर काष्ठा nft_set_ext *ext, u8 id)
अणु
	वापस ext && __nft_set_ext_exists(ext, id);
पूर्ण

अटल अंतरभूत व्योम *nft_set_ext(स्थिर काष्ठा nft_set_ext *ext, u8 id)
अणु
	वापस (व्योम *)ext + ext->offset[id];
पूर्ण

अटल अंतरभूत काष्ठा nft_data *nft_set_ext_key(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_KEY);
पूर्ण

अटल अंतरभूत काष्ठा nft_data *nft_set_ext_key_end(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_KEY_END);
पूर्ण

अटल अंतरभूत काष्ठा nft_data *nft_set_ext_data(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_DATA);
पूर्ण

अटल अंतरभूत u8 *nft_set_ext_flags(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_FLAGS);
पूर्ण

अटल अंतरभूत u64 *nft_set_ext_समयout(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_TIMEOUT);
पूर्ण

अटल अंतरभूत u64 *nft_set_ext_expiration(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_EXPIRATION);
पूर्ण

अटल अंतरभूत काष्ठा nft_userdata *nft_set_ext_userdata(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_USERDATA);
पूर्ण

अटल अंतरभूत काष्ठा nft_set_elem_expr *nft_set_ext_expr(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_EXPRESSIONS);
पूर्ण

अटल अंतरभूत bool nft_set_elem_expired(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext_exists(ext, NFT_SET_EXT_EXPIRATION) &&
	       समय_is_beक्रमe_eq_jअगरfies64(*nft_set_ext_expiration(ext));
पूर्ण

अटल अंतरभूत काष्ठा nft_set_ext *nft_set_elem_ext(स्थिर काष्ठा nft_set *set,
						   व्योम *elem)
अणु
	वापस elem + set->ops->elemsize;
पूर्ण

अटल अंतरभूत काष्ठा nft_object **nft_set_ext_obj(स्थिर काष्ठा nft_set_ext *ext)
अणु
	वापस nft_set_ext(ext, NFT_SET_EXT_OBJREF);
पूर्ण

काष्ठा nft_expr *nft_set_elem_expr_alloc(स्थिर काष्ठा nft_ctx *ctx,
					 स्थिर काष्ठा nft_set *set,
					 स्थिर काष्ठा nlattr *attr);

व्योम *nft_set_elem_init(स्थिर काष्ठा nft_set *set,
			स्थिर काष्ठा nft_set_ext_पंचांगpl *पंचांगpl,
			स्थिर u32 *key, स्थिर u32 *key_end, स्थिर u32 *data,
			u64 समयout, u64 expiration, gfp_t gfp);
पूर्णांक nft_set_elem_expr_clone(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			    काष्ठा nft_expr *expr_array[]);
व्योम nft_set_elem_destroy(स्थिर काष्ठा nft_set *set, व्योम *elem,
			  bool destroy_expr);

/**
 *	काष्ठा nft_set_gc_batch_head - nf_tables set garbage collection batch
 *
 *	@rcu: rcu head
 *	@set: set the elements beदीर्घ to
 *	@cnt: count of elements
 */
काष्ठा nft_set_gc_batch_head अणु
	काष्ठा rcu_head			rcu;
	स्थिर काष्ठा nft_set		*set;
	अचिन्हित पूर्णांक			cnt;
पूर्ण;

#घोषणा NFT_SET_GC_BATCH_SIZE	((PAGE_SIZE -				  \
				  माप(काष्ठा nft_set_gc_batch_head)) / \
				 माप(व्योम *))

/**
 *	काष्ठा nft_set_gc_batch - nf_tables set garbage collection batch
 *
 * 	@head: GC batch head
 * 	@elems: garbage collection elements
 */
काष्ठा nft_set_gc_batch अणु
	काष्ठा nft_set_gc_batch_head	head;
	व्योम				*elems[NFT_SET_GC_BATCH_SIZE];
पूर्ण;

काष्ठा nft_set_gc_batch *nft_set_gc_batch_alloc(स्थिर काष्ठा nft_set *set,
						gfp_t gfp);
व्योम nft_set_gc_batch_release(काष्ठा rcu_head *rcu);

अटल अंतरभूत व्योम nft_set_gc_batch_complete(काष्ठा nft_set_gc_batch *gcb)
अणु
	अगर (gcb != शून्य)
		call_rcu(&gcb->head.rcu, nft_set_gc_batch_release);
पूर्ण

अटल अंतरभूत काष्ठा nft_set_gc_batch *
nft_set_gc_batch_check(स्थिर काष्ठा nft_set *set, काष्ठा nft_set_gc_batch *gcb,
		       gfp_t gfp)
अणु
	अगर (gcb != शून्य) अणु
		अगर (gcb->head.cnt + 1 < ARRAY_SIZE(gcb->elems))
			वापस gcb;
		nft_set_gc_batch_complete(gcb);
	पूर्ण
	वापस nft_set_gc_batch_alloc(set, gfp);
पूर्ण

अटल अंतरभूत व्योम nft_set_gc_batch_add(काष्ठा nft_set_gc_batch *gcb,
					व्योम *elem)
अणु
	gcb->elems[gcb->head.cnt++] = elem;
पूर्ण

काष्ठा nft_expr_ops;
/**
 *	काष्ठा nft_expr_type - nf_tables expression type
 *
 *	@select_ops: function to select nft_expr_ops
 *	@release_ops: release nft_expr_ops
 *	@ops: शेष ops, used when no select_ops functions is present
 *	@list: used पूर्णांकernally
 *	@name: Identअगरier
 *	@owner: module reference
 *	@policy: netlink attribute policy
 *	@maxattr: highest netlink attribute number
 *	@family: address family क्रम AF-specअगरic types
 *	@flags: expression type flags
 */
काष्ठा nft_expr_type अणु
	स्थिर काष्ठा nft_expr_ops	*(*select_ops)(स्थिर काष्ठा nft_ctx *,
						       स्थिर काष्ठा nlattr * स्थिर tb[]);
	व्योम				(*release_ops)(स्थिर काष्ठा nft_expr_ops *ops);
	स्थिर काष्ठा nft_expr_ops	*ops;
	काष्ठा list_head		list;
	स्थिर अक्षर			*name;
	काष्ठा module			*owner;
	स्थिर काष्ठा nla_policy		*policy;
	अचिन्हित पूर्णांक			maxattr;
	u8				family;
	u8				flags;
पूर्ण;

#घोषणा NFT_EXPR_STATEFUL		0x1
#घोषणा NFT_EXPR_GC			0x2

क्रमागत nft_trans_phase अणु
	NFT_TRANS_PREPARE,
	NFT_TRANS_ABORT,
	NFT_TRANS_COMMIT,
	NFT_TRANS_RELEASE
पूर्ण;

काष्ठा nft_flow_rule;
काष्ठा nft_offload_ctx;

/**
 *	काष्ठा nft_expr_ops - nf_tables expression operations
 *
 *	@eval: Expression evaluation function
 *	@size: full expression size, including निजी data size
 *	@init: initialization function
 *	@activate: activate expression in the next generation
 *	@deactivate: deactivate expression in next generation
 *	@destroy: deकाष्ठाion function, called after synchronize_rcu
 *	@dump: function to dump parameters
 *	@type: expression type
 *	@validate: validate expression, called during loop detection
 *	@data: extra data to attach to this expression operation
 */
काष्ठा nft_expr_ops अणु
	व्योम				(*eval)(स्थिर काष्ठा nft_expr *expr,
						काष्ठा nft_regs *regs,
						स्थिर काष्ठा nft_pktinfo *pkt);
	पूर्णांक				(*clone)(काष्ठा nft_expr *dst,
						 स्थिर काष्ठा nft_expr *src);
	अचिन्हित पूर्णांक			size;

	पूर्णांक				(*init)(स्थिर काष्ठा nft_ctx *ctx,
						स्थिर काष्ठा nft_expr *expr,
						स्थिर काष्ठा nlattr * स्थिर tb[]);
	व्योम				(*activate)(स्थिर काष्ठा nft_ctx *ctx,
						    स्थिर काष्ठा nft_expr *expr);
	व्योम				(*deactivate)(स्थिर काष्ठा nft_ctx *ctx,
						      स्थिर काष्ठा nft_expr *expr,
						      क्रमागत nft_trans_phase phase);
	व्योम				(*destroy)(स्थिर काष्ठा nft_ctx *ctx,
						   स्थिर काष्ठा nft_expr *expr);
	व्योम				(*destroy_clone)(स्थिर काष्ठा nft_ctx *ctx,
							 स्थिर काष्ठा nft_expr *expr);
	पूर्णांक				(*dump)(काष्ठा sk_buff *skb,
						स्थिर काष्ठा nft_expr *expr);
	पूर्णांक				(*validate)(स्थिर काष्ठा nft_ctx *ctx,
						    स्थिर काष्ठा nft_expr *expr,
						    स्थिर काष्ठा nft_data **data);
	bool				(*gc)(काष्ठा net *net,
					      स्थिर काष्ठा nft_expr *expr);
	पूर्णांक				(*offload)(काष्ठा nft_offload_ctx *ctx,
						   काष्ठा nft_flow_rule *flow,
						   स्थिर काष्ठा nft_expr *expr);
	व्योम				(*offload_stats)(काष्ठा nft_expr *expr,
							 स्थिर काष्ठा flow_stats *stats);
	u32				offload_flags;
	स्थिर काष्ठा nft_expr_type	*type;
	व्योम				*data;
पूर्ण;

/**
 *	काष्ठा nft_rule - nf_tables rule
 *
 *	@list: used पूर्णांकernally
 *	@handle: rule handle
 *	@genmask: generation mask
 *	@dlen: length of expression data
 *	@udata: user data is appended to the rule
 *	@data: expression data
 */
काष्ठा nft_rule अणु
	काष्ठा list_head		list;
	u64				handle:42,
					genmask:2,
					dlen:12,
					udata:1;
	अचिन्हित अक्षर			data[]
		__attribute__((aligned(__alignof__(काष्ठा nft_expr))));
पूर्ण;

अटल अंतरभूत काष्ठा nft_expr *nft_expr_first(स्थिर काष्ठा nft_rule *rule)
अणु
	वापस (काष्ठा nft_expr *)&rule->data[0];
पूर्ण

अटल अंतरभूत काष्ठा nft_expr *nft_expr_next(स्थिर काष्ठा nft_expr *expr)
अणु
	वापस ((व्योम *)expr) + expr->ops->size;
पूर्ण

अटल अंतरभूत काष्ठा nft_expr *nft_expr_last(स्थिर काष्ठा nft_rule *rule)
अणु
	वापस (काष्ठा nft_expr *)&rule->data[rule->dlen];
पूर्ण

अटल अंतरभूत bool nft_expr_more(स्थिर काष्ठा nft_rule *rule,
				 स्थिर काष्ठा nft_expr *expr)
अणु
	वापस expr != nft_expr_last(rule) && expr->ops;
पूर्ण

अटल अंतरभूत काष्ठा nft_userdata *nft_userdata(स्थिर काष्ठा nft_rule *rule)
अणु
	वापस (व्योम *)&rule->data[rule->dlen];
पूर्ण

व्योम nf_tables_rule_release(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_rule *rule);

अटल अंतरभूत व्योम nft_set_elem_update_expr(स्थिर काष्ठा nft_set_ext *ext,
					    काष्ठा nft_regs *regs,
					    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_set_elem_expr *elem_expr;
	काष्ठा nft_expr *expr;
	u32 size;

	अगर (__nft_set_ext_exists(ext, NFT_SET_EXT_EXPRESSIONS)) अणु
		elem_expr = nft_set_ext_expr(ext);
		nft_setelem_expr_क्रमeach(expr, elem_expr, size) अणु
			expr->ops->eval(expr, regs, pkt);
			अगर (regs->verdict.code == NFT_BREAK)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The last poपूर्णांकer isn't really necessary, but the compiler isn't able to
 * determine that the result of nft_expr_last() is always the same since it
 * can't assume that the dlen value wasn't changed within calls in the loop.
 */
#घोषणा nft_rule_क्रम_each_expr(expr, last, rule) \
	क्रम ((expr) = nft_expr_first(rule), (last) = nft_expr_last(rule); \
	     (expr) != (last); \
	     (expr) = nft_expr_next(expr))

#घोषणा NFT_CHAIN_POLICY_UNSET		U8_MAX

/**
 *	काष्ठा nft_chain - nf_tables chain
 *
 *	@rules: list of rules in the chain
 *	@list: used पूर्णांकernally
 *	@rhlhead: used पूर्णांकernally
 *	@table: table that this chain beदीर्घs to
 *	@handle: chain handle
 *	@use: number of jump references to this chain
 *	@flags: biपंचांगask of क्रमागत nft_chain_flags
 *	@name: name of the chain
 */
काष्ठा nft_chain अणु
	काष्ठा nft_rule			*__rcu *rules_gen_0;
	काष्ठा nft_rule			*__rcu *rules_gen_1;
	काष्ठा list_head		rules;
	काष्ठा list_head		list;
	काष्ठा rhlist_head		rhlhead;
	काष्ठा nft_table		*table;
	u64				handle;
	u32				use;
	u8				flags:5,
					bound:1,
					genmask:2;
	अक्षर				*name;
	u16				udlen;
	u8				*udata;

	/* Only used during control plane commit phase: */
	काष्ठा nft_rule			**rules_next;
पूर्ण;

पूर्णांक nft_chain_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_chain *chain);

क्रमागत nft_chain_types अणु
	NFT_CHAIN_T_DEFAULT = 0,
	NFT_CHAIN_T_ROUTE,
	NFT_CHAIN_T_NAT,
	NFT_CHAIN_T_MAX
पूर्ण;

/**
 * 	काष्ठा nft_chain_type - nf_tables chain type info
 *
 * 	@name: name of the type
 * 	@type: numeric identअगरier
 * 	@family: address family
 * 	@owner: module owner
 * 	@hook_mask: mask of valid hooks
 * 	@hooks: array of hook functions
 *	@ops_रेजिस्टर: base chain रेजिस्टर function
 *	@ops_unरेजिस्टर: base chain unरेजिस्टर function
 */
काष्ठा nft_chain_type अणु
	स्थिर अक्षर			*name;
	क्रमागत nft_chain_types		type;
	पूर्णांक				family;
	काष्ठा module			*owner;
	अचिन्हित पूर्णांक			hook_mask;
	nf_hookfn			*hooks[NFT_MAX_HOOKS];
	पूर्णांक				(*ops_रेजिस्टर)(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
	व्योम				(*ops_unरेजिस्टर)(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
पूर्ण;

पूर्णांक nft_chain_validate_dependency(स्थिर काष्ठा nft_chain *chain,
				  क्रमागत nft_chain_types type);
पूर्णांक nft_chain_validate_hooks(स्थिर काष्ठा nft_chain *chain,
                             अचिन्हित पूर्णांक hook_flags);

अटल अंतरभूत bool nft_chain_is_bound(काष्ठा nft_chain *chain)
अणु
	वापस (chain->flags & NFT_CHAIN_BINDING) && chain->bound;
पूर्ण

व्योम nft_chain_del(काष्ठा nft_chain *chain);
व्योम nf_tables_chain_destroy(काष्ठा nft_ctx *ctx);

काष्ठा nft_stats अणु
	u64			bytes;
	u64			pkts;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

काष्ठा nft_hook अणु
	काष्ठा list_head	list;
	bool			inactive;
	काष्ठा nf_hook_ops	ops;
	काष्ठा rcu_head		rcu;
पूर्ण;

/**
 *	काष्ठा nft_base_chain - nf_tables base chain
 *
 *	@ops: netfilter hook ops
 *	@hook_list: list of netfilter hooks (क्रम NFPROTO_NETDEV family)
 *	@type: chain type
 *	@policy: शेष policy
 *	@stats: per-cpu chain stats
 *	@chain: the chain
 *	@flow_block: flow block (क्रम hardware offload)
 */
काष्ठा nft_base_chain अणु
	काष्ठा nf_hook_ops		ops;
	काष्ठा list_head		hook_list;
	स्थिर काष्ठा nft_chain_type	*type;
	u8				policy;
	u8				flags;
	काष्ठा nft_stats __percpu	*stats;
	काष्ठा nft_chain		chain;
	काष्ठा flow_block		flow_block;
पूर्ण;

अटल अंतरभूत काष्ठा nft_base_chain *nft_base_chain(स्थिर काष्ठा nft_chain *chain)
अणु
	वापस container_of(chain, काष्ठा nft_base_chain, chain);
पूर्ण

अटल अंतरभूत bool nft_is_base_chain(स्थिर काष्ठा nft_chain *chain)
अणु
	वापस chain->flags & NFT_CHAIN_BASE;
पूर्ण

पूर्णांक __nft_release_basechain(काष्ठा nft_ctx *ctx);

अचिन्हित पूर्णांक nft_करो_chain(काष्ठा nft_pktinfo *pkt, व्योम *priv);

/**
 *	काष्ठा nft_table - nf_tables table
 *
 *	@list: used पूर्णांकernally
 *	@chains_ht: chains in the table
 *	@chains: same, क्रम stable walks
 *	@sets: sets in the table
 *	@objects: stateful objects in the table
 *	@flowtables: flow tables in the table
 *	@hgenerator: handle generator state
 *	@handle: table handle
 *	@use: number of chain references to this table
 *	@flags: table flag (see क्रमागत nft_table_flags)
 *	@genmask: generation mask
 *	@afinfo: address family info
 *	@name: name of the table
 */
काष्ठा nft_table अणु
	काष्ठा list_head		list;
	काष्ठा rhltable			chains_ht;
	काष्ठा list_head		chains;
	काष्ठा list_head		sets;
	काष्ठा list_head		objects;
	काष्ठा list_head		flowtables;
	u64				hgenerator;
	u64				handle;
	u32				use;
	u16				family:6,
					flags:8,
					genmask:2;
	u32				nlpid;
	अक्षर				*name;
	u16				udlen;
	u8				*udata;
पूर्ण;

अटल अंतरभूत bool nft_table_has_owner(स्थिर काष्ठा nft_table *table)
अणु
	वापस table->flags & NFT_TABLE_F_OWNER;
पूर्ण

अटल अंतरभूत bool nft_base_chain_netdev(पूर्णांक family, u32 hooknum)
अणु
	वापस family == NFPROTO_NETDEV ||
	       (family == NFPROTO_INET && hooknum == NF_INET_INGRESS);
पूर्ण

व्योम nft_रेजिस्टर_chain_type(स्थिर काष्ठा nft_chain_type *);
व्योम nft_unरेजिस्टर_chain_type(स्थिर काष्ठा nft_chain_type *);

पूर्णांक nft_रेजिस्टर_expr(काष्ठा nft_expr_type *);
व्योम nft_unरेजिस्टर_expr(काष्ठा nft_expr_type *);

पूर्णांक nft_verdict_dump(काष्ठा sk_buff *skb, पूर्णांक type,
		     स्थिर काष्ठा nft_verdict *v);

/**
 *	काष्ठा nft_object_hash_key - key to lookup nft_object
 *
 *	@name: name of the stateful object to look up
 *	@table: table the object beदीर्घs to
 */
काष्ठा nft_object_hash_key अणु
	स्थिर अक्षर                      *name;
	स्थिर काष्ठा nft_table          *table;
पूर्ण;

/**
 *	काष्ठा nft_object - nf_tables stateful object
 *
 *	@list: table stateful object list node
 *	@key:  keys that identअगरy this object
 *	@rhlhead: nft_objname_ht node
 *	@genmask: generation mask
 *	@use: number of references to this stateful object
 *	@handle: unique object handle
 *	@ops: object operations
 *	@data: object data, layout depends on type
 */
काष्ठा nft_object अणु
	काष्ठा list_head		list;
	काष्ठा rhlist_head		rhlhead;
	काष्ठा nft_object_hash_key	key;
	u32				genmask:2,
					use:30;
	u64				handle;
	u16				udlen;
	u8				*udata;
	/* runसमय data below here */
	स्थिर काष्ठा nft_object_ops	*ops ____cacheline_aligned;
	अचिन्हित अक्षर			data[]
		__attribute__((aligned(__alignof__(u64))));
पूर्ण;

अटल अंतरभूत व्योम *nft_obj_data(स्थिर काष्ठा nft_object *obj)
अणु
	वापस (व्योम *)obj->data;
पूर्ण

#घोषणा nft_expr_obj(expr)	*((काष्ठा nft_object **)nft_expr_priv(expr))

काष्ठा nft_object *nft_obj_lookup(स्थिर काष्ठा net *net,
				  स्थिर काष्ठा nft_table *table,
				  स्थिर काष्ठा nlattr *nla, u32 objtype,
				  u8 genmask);

व्योम nft_obj_notअगरy(काष्ठा net *net, स्थिर काष्ठा nft_table *table,
		    काष्ठा nft_object *obj, u32 portid, u32 seq,
		    पूर्णांक event, पूर्णांक family, पूर्णांक report, gfp_t gfp);

/**
 *	काष्ठा nft_object_type - stateful object type
 *
 *	@select_ops: function to select nft_object_ops
 *	@ops: शेष ops, used when no select_ops functions is present
 *	@list: list node in list of object types
 *	@type: stateful object numeric type
 *	@owner: module owner
 *	@maxattr: maximum netlink attribute
 *	@policy: netlink attribute policy
 */
काष्ठा nft_object_type अणु
	स्थिर काष्ठा nft_object_ops	*(*select_ops)(स्थिर काष्ठा nft_ctx *,
						       स्थिर काष्ठा nlattr * स्थिर tb[]);
	स्थिर काष्ठा nft_object_ops	*ops;
	काष्ठा list_head		list;
	u32				type;
	अचिन्हित पूर्णांक                    maxattr;
	काष्ठा module			*owner;
	स्थिर काष्ठा nla_policy		*policy;
पूर्ण;

/**
 *	काष्ठा nft_object_ops - stateful object operations
 *
 *	@eval: stateful object evaluation function
 *	@size: stateful object size
 *	@init: initialize object from netlink attributes
 *	@destroy: release existing stateful object
 *	@dump: netlink dump stateful object
 *	@update: update stateful object
 */
काष्ठा nft_object_ops अणु
	व्योम				(*eval)(काष्ठा nft_object *obj,
						काष्ठा nft_regs *regs,
						स्थिर काष्ठा nft_pktinfo *pkt);
	अचिन्हित पूर्णांक			size;
	पूर्णांक				(*init)(स्थिर काष्ठा nft_ctx *ctx,
						स्थिर काष्ठा nlattr *स्थिर tb[],
						काष्ठा nft_object *obj);
	व्योम				(*destroy)(स्थिर काष्ठा nft_ctx *ctx,
						   काष्ठा nft_object *obj);
	पूर्णांक				(*dump)(काष्ठा sk_buff *skb,
						काष्ठा nft_object *obj,
						bool reset);
	व्योम				(*update)(काष्ठा nft_object *obj,
						  काष्ठा nft_object *newobj);
	स्थिर काष्ठा nft_object_type	*type;
पूर्ण;

पूर्णांक nft_रेजिस्टर_obj(काष्ठा nft_object_type *obj_type);
व्योम nft_unरेजिस्टर_obj(काष्ठा nft_object_type *obj_type);

#घोषणा NFT_NETDEVICE_MAX	256

/**
 *	काष्ठा nft_flowtable - nf_tables flow table
 *
 *	@list: flow table list node in table list
 * 	@table: the table the flow table is contained in
 *	@name: name of this flow table
 *	@hooknum: hook number
 *	@ops_len: number of hooks in array
 *	@genmask: generation mask
 *	@use: number of references to this flow table
 * 	@handle: unique object handle
 *	@dev_name: array of device names
 *	@data: rhashtable and garbage collector
 * 	@ops: array of hooks
 */
काष्ठा nft_flowtable अणु
	काष्ठा list_head		list;
	काष्ठा nft_table		*table;
	अक्षर				*name;
	पूर्णांक				hooknum;
	पूर्णांक				ops_len;
	u32				genmask:2,
					use:30;
	u64				handle;
	/* runसमय data below here */
	काष्ठा list_head		hook_list ____cacheline_aligned;
	काष्ठा nf_flowtable		data;
पूर्ण;

काष्ठा nft_flowtable *nft_flowtable_lookup(स्थिर काष्ठा nft_table *table,
					   स्थिर काष्ठा nlattr *nla,
					   u8 genmask);

व्योम nf_tables_deactivate_flowtable(स्थिर काष्ठा nft_ctx *ctx,
				    काष्ठा nft_flowtable *flowtable,
				    क्रमागत nft_trans_phase phase);

व्योम nft_रेजिस्टर_flowtable_type(काष्ठा nf_flowtable_type *type);
व्योम nft_unरेजिस्टर_flowtable_type(काष्ठा nf_flowtable_type *type);

/**
 *	काष्ठा nft_traceinfo - nft tracing inक्रमmation and state
 *
 *	@pkt: pktinfo currently processed
 *	@basechain: base chain currently processed
 *	@chain: chain currently processed
 *	@rule:  rule that was evaluated
 *	@verdict: verdict given by rule
 *	@type: event type (क्रमागत nft_trace_types)
 *	@packet_dumped: packet headers sent in a previous traceinfo message
 *	@trace: other काष्ठा members are initialised
 */
काष्ठा nft_traceinfo अणु
	स्थिर काष्ठा nft_pktinfo	*pkt;
	स्थिर काष्ठा nft_base_chain	*basechain;
	स्थिर काष्ठा nft_chain		*chain;
	स्थिर काष्ठा nft_rule		*rule;
	स्थिर काष्ठा nft_verdict	*verdict;
	क्रमागत nft_trace_types		type;
	bool				packet_dumped;
	bool				trace;
पूर्ण;

व्योम nft_trace_init(काष्ठा nft_traceinfo *info, स्थिर काष्ठा nft_pktinfo *pkt,
		    स्थिर काष्ठा nft_verdict *verdict,
		    स्थिर काष्ठा nft_chain *basechain);

व्योम nft_trace_notअगरy(काष्ठा nft_traceinfo *info);

#घोषणा MODULE_ALIAS_NFT_CHAIN(family, name) \
	MODULE_ALIAS("nft-chain-" __stringअगरy(family) "-" name)

#घोषणा MODULE_ALIAS_NFT_AF_EXPR(family, name) \
	MODULE_ALIAS("nft-expr-" __stringअगरy(family) "-" name)

#घोषणा MODULE_ALIAS_NFT_EXPR(name) \
	MODULE_ALIAS("nft-expr-" name)

#घोषणा MODULE_ALIAS_NFT_OBJ(type) \
	MODULE_ALIAS("nft-obj-" __stringअगरy(type))

#अगर IS_ENABLED(CONFIG_NF_TABLES)

/*
 * The gencursor defines two generations, the currently active and the
 * next one. Objects contain a biपंचांगask of 2 bits specअगरying the generations
 * they're active in. A set bit means they're inactive in the generation
 * represented by that bit.
 *
 * New objects start out as inactive in the current and active in the
 * next generation. When committing the ruleset the biपंचांगask is cleared,
 * meaning they're active in all generations. When removing an object,
 * it is set inactive in the next generation. After committing the ruleset,
 * the objects are हटाओd.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nft_gencursor_next(स्थिर काष्ठा net *net)
अणु
	वापस net->nft.gencursor + 1 == 1 ? 1 : 0;
पूर्ण

अटल अंतरभूत u8 nft_genmask_next(स्थिर काष्ठा net *net)
अणु
	वापस 1 << nft_gencursor_next(net);
पूर्ण

अटल अंतरभूत u8 nft_genmask_cur(स्थिर काष्ठा net *net)
अणु
	/* Use READ_ONCE() to prevent refetching the value क्रम atomicity */
	वापस 1 << READ_ONCE(net->nft.gencursor);
पूर्ण

#घोषणा NFT_GENMASK_ANY		((1 << 0) | (1 << 1))

/*
 * Generic transaction helpers
 */

/* Check अगर this object is currently active. */
#घोषणा nft_is_active(__net, __obj)				\
	(((__obj)->genmask & nft_genmask_cur(__net)) == 0)

/* Check अगर this object is active in the next generation. */
#घोषणा nft_is_active_next(__net, __obj)			\
	(((__obj)->genmask & nft_genmask_next(__net)) == 0)

/* This object becomes active in the next generation. */
#घोषणा nft_activate_next(__net, __obj)				\
	(__obj)->genmask = nft_genmask_cur(__net)

/* This object becomes inactive in the next generation. */
#घोषणा nft_deactivate_next(__net, __obj)			\
        (__obj)->genmask = nft_genmask_next(__net)

/* After committing the ruleset, clear the stale generation bit. */
#घोषणा nft_clear(__net, __obj)					\
	(__obj)->genmask &= ~nft_genmask_next(__net)
#घोषणा nft_active_genmask(__obj, __genmask)			\
	!((__obj)->genmask & __genmask)

/*
 * Set element transaction helpers
 */

अटल अंतरभूत bool nft_set_elem_active(स्थिर काष्ठा nft_set_ext *ext,
				       u8 genmask)
अणु
	वापस !(ext->genmask & genmask);
पूर्ण

अटल अंतरभूत व्योम nft_set_elem_change_active(स्थिर काष्ठा net *net,
					      स्थिर काष्ठा nft_set *set,
					      काष्ठा nft_set_ext *ext)
अणु
	ext->genmask ^= nft_genmask_next(net);
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_NF_TABLES) */

/*
 * We use a मुक्त bit in the genmask field to indicate the element
 * is busy, meaning it is currently being processed either by
 * the netlink API or GC.
 *
 * Even though the genmask is only a single byte wide, this works
 * because the extension काष्ठाure अगर fully स्थिरant once initialized,
 * so there are no non-atomic ग_लिखो accesses unless it is alपढ़ोy
 * marked busy.
 */
#घोषणा NFT_SET_ELEM_BUSY_MASK	(1 << 2)

#अगर defined(__LITTLE_ENDIAN_BITFIELD)
#घोषणा NFT_SET_ELEM_BUSY_BIT	2
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
#घोषणा NFT_SET_ELEM_BUSY_BIT	(BITS_PER_LONG - BITS_PER_BYTE + 2)
#अन्यथा
#त्रुटि
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक nft_set_elem_mark_busy(काष्ठा nft_set_ext *ext)
अणु
	अचिन्हित दीर्घ *word = (अचिन्हित दीर्घ *)ext;

	BUILD_BUG_ON(दुरत्व(काष्ठा nft_set_ext, genmask) != 0);
	वापस test_and_set_bit(NFT_SET_ELEM_BUSY_BIT, word);
पूर्ण

अटल अंतरभूत व्योम nft_set_elem_clear_busy(काष्ठा nft_set_ext *ext)
अणु
	अचिन्हित दीर्घ *word = (अचिन्हित दीर्घ *)ext;

	clear_bit(NFT_SET_ELEM_BUSY_BIT, word);
पूर्ण

/**
 *	काष्ठा nft_trans - nf_tables object update in transaction
 *
 *	@list: used पूर्णांकernally
 *	@msg_type: message type
 *	@put_net: ctx->net needs to be put
 *	@ctx: transaction context
 *	@data: पूर्णांकernal inक्रमmation related to the transaction
 */
काष्ठा nft_trans अणु
	काष्ठा list_head		list;
	पूर्णांक				msg_type;
	bool				put_net;
	काष्ठा nft_ctx			ctx;
	अक्षर				data[];
पूर्ण;

काष्ठा nft_trans_rule अणु
	काष्ठा nft_rule			*rule;
	काष्ठा nft_flow_rule		*flow;
	u32				rule_id;
पूर्ण;

#घोषणा nft_trans_rule(trans)	\
	(((काष्ठा nft_trans_rule *)trans->data)->rule)
#घोषणा nft_trans_flow_rule(trans)	\
	(((काष्ठा nft_trans_rule *)trans->data)->flow)
#घोषणा nft_trans_rule_id(trans)	\
	(((काष्ठा nft_trans_rule *)trans->data)->rule_id)

काष्ठा nft_trans_set अणु
	काष्ठा nft_set			*set;
	u32				set_id;
	bool				bound;
पूर्ण;

#घोषणा nft_trans_set(trans)	\
	(((काष्ठा nft_trans_set *)trans->data)->set)
#घोषणा nft_trans_set_id(trans)	\
	(((काष्ठा nft_trans_set *)trans->data)->set_id)
#घोषणा nft_trans_set_bound(trans)	\
	(((काष्ठा nft_trans_set *)trans->data)->bound)

काष्ठा nft_trans_chain अणु
	bool				update;
	अक्षर				*name;
	काष्ठा nft_stats __percpu	*stats;
	u8				policy;
	u32				chain_id;
पूर्ण;

#घोषणा nft_trans_chain_update(trans)	\
	(((काष्ठा nft_trans_chain *)trans->data)->update)
#घोषणा nft_trans_chain_name(trans)	\
	(((काष्ठा nft_trans_chain *)trans->data)->name)
#घोषणा nft_trans_chain_stats(trans)	\
	(((काष्ठा nft_trans_chain *)trans->data)->stats)
#घोषणा nft_trans_chain_policy(trans)	\
	(((काष्ठा nft_trans_chain *)trans->data)->policy)
#घोषणा nft_trans_chain_id(trans)	\
	(((काष्ठा nft_trans_chain *)trans->data)->chain_id)

काष्ठा nft_trans_table अणु
	bool				update;
पूर्ण;

#घोषणा nft_trans_table_update(trans)	\
	(((काष्ठा nft_trans_table *)trans->data)->update)

काष्ठा nft_trans_elem अणु
	काष्ठा nft_set			*set;
	काष्ठा nft_set_elem		elem;
	bool				bound;
पूर्ण;

#घोषणा nft_trans_elem_set(trans)	\
	(((काष्ठा nft_trans_elem *)trans->data)->set)
#घोषणा nft_trans_elem(trans)	\
	(((काष्ठा nft_trans_elem *)trans->data)->elem)
#घोषणा nft_trans_elem_set_bound(trans)	\
	(((काष्ठा nft_trans_elem *)trans->data)->bound)

काष्ठा nft_trans_obj अणु
	काष्ठा nft_object		*obj;
	काष्ठा nft_object		*newobj;
	bool				update;
पूर्ण;

#घोषणा nft_trans_obj(trans)	\
	(((काष्ठा nft_trans_obj *)trans->data)->obj)
#घोषणा nft_trans_obj_newobj(trans) \
	(((काष्ठा nft_trans_obj *)trans->data)->newobj)
#घोषणा nft_trans_obj_update(trans)	\
	(((काष्ठा nft_trans_obj *)trans->data)->update)

काष्ठा nft_trans_flowtable अणु
	काष्ठा nft_flowtable		*flowtable;
	bool				update;
	काष्ठा list_head		hook_list;
	u32				flags;
पूर्ण;

#घोषणा nft_trans_flowtable(trans)	\
	(((काष्ठा nft_trans_flowtable *)trans->data)->flowtable)
#घोषणा nft_trans_flowtable_update(trans)	\
	(((काष्ठा nft_trans_flowtable *)trans->data)->update)
#घोषणा nft_trans_flowtable_hooks(trans)	\
	(((काष्ठा nft_trans_flowtable *)trans->data)->hook_list)
#घोषणा nft_trans_flowtable_flags(trans)	\
	(((काष्ठा nft_trans_flowtable *)trans->data)->flags)

पूर्णांक __init nft_chain_filter_init(व्योम);
व्योम nft_chain_filter_fini(व्योम);

व्योम __init nft_chain_route_init(व्योम);
व्योम nft_chain_route_fini(व्योम);

व्योम nf_tables_trans_destroy_flush_work(व्योम);

पूर्णांक nf_msecs_to_jअगरfies64(स्थिर काष्ठा nlattr *nla, u64 *result);
__be64 nf_jअगरfies64_to_msecs(u64 input);

#अगर_घोषित CONFIG_MODULES
__म_लिखो(2, 3) पूर्णांक nft_request_module(काष्ठा net *net, स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत पूर्णांक nft_request_module(काष्ठा net *net, स्थिर अक्षर *fmt, ...) अणु वापस -ENOENT; पूर्ण
#पूर्ण_अगर

काष्ठा nftables_pernet अणु
	काष्ठा list_head	tables;
	काष्ठा list_head	commit_list;
	काष्ठा list_head	module_list;
	काष्ठा list_head	notअगरy_list;
	काष्ठा mutex		commit_mutex;
	अचिन्हित पूर्णांक		base_seq;
	u8			validate_state;
पूर्ण;

बाह्य अचिन्हित पूर्णांक nf_tables_net_id;

अटल अंतरभूत काष्ठा nftables_pernet *nft_pernet(स्थिर काष्ठा net *net)
अणु
	वापस net_generic(net, nf_tables_net_id);
पूर्ण

#पूर्ण_अगर /* _NET_NF_TABLES_H */
