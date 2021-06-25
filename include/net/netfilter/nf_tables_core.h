<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_NF_TABLES_CORE_H
#घोषणा _NET_NF_TABLES_CORE_H

#समावेश <net/netfilter/nf_tables.h>

बाह्य काष्ठा nft_expr_type nft_imm_type;
बाह्य काष्ठा nft_expr_type nft_cmp_type;
बाह्य काष्ठा nft_expr_type nft_lookup_type;
बाह्य काष्ठा nft_expr_type nft_bitwise_type;
बाह्य काष्ठा nft_expr_type nft_byteorder_type;
बाह्य काष्ठा nft_expr_type nft_payload_type;
बाह्य काष्ठा nft_expr_type nft_dynset_type;
बाह्य काष्ठा nft_expr_type nft_range_type;
बाह्य काष्ठा nft_expr_type nft_meta_type;
बाह्य काष्ठा nft_expr_type nft_rt_type;
बाह्य काष्ठा nft_expr_type nft_exthdr_type;

#अगर_घोषित CONFIG_NETWORK_SECMARK
बाह्य काष्ठा nft_object_type nft_secmark_obj_type;
#पूर्ण_अगर

पूर्णांक nf_tables_core_module_init(व्योम);
व्योम nf_tables_core_module_निकास(व्योम);

काष्ठा nft_bitwise_fast_expr अणु
	u32			mask;
	u32			xor;
	u8			sreg;
	u8			dreg;
पूर्ण;

काष्ठा nft_cmp_fast_expr अणु
	u32			data;
	u32			mask;
	u8			sreg;
	u8			len;
	bool			inv;
पूर्ण;

काष्ठा nft_immediate_expr अणु
	काष्ठा nft_data		data;
	u8			dreg;
	u8			dlen;
पूर्ण;

/* Calculate the mask क्रम the nft_cmp_fast expression. On big endian the
 * mask needs to include the *upper* bytes when पूर्णांकerpreting that data as
 * something smaller than the full u32, thereक्रमe a cpu_to_le32 is करोne.
 */
अटल अंतरभूत u32 nft_cmp_fast_mask(अचिन्हित पूर्णांक len)
अणु
	वापस cpu_to_le32(~0U >> (माप_field(काष्ठा nft_cmp_fast_expr,
						data) * BITS_PER_BYTE - len));
पूर्ण

बाह्य स्थिर काष्ठा nft_expr_ops nft_cmp_fast_ops;

काष्ठा nft_payload अणु
	क्रमागत nft_payload_bases	base:8;
	u8			offset;
	u8			len;
	u8			dreg;
पूर्ण;

काष्ठा nft_payload_set अणु
	क्रमागत nft_payload_bases	base:8;
	u8			offset;
	u8			len;
	u8			sreg;
	u8			csum_type;
	u8			csum_offset;
	u8			csum_flags;
पूर्ण;

बाह्य स्थिर काष्ठा nft_expr_ops nft_payload_fast_ops;

बाह्य स्थिर काष्ठा nft_expr_ops nft_bitwise_fast_ops;

बाह्य काष्ठा अटल_key_false nft_counters_enabled;
बाह्य काष्ठा अटल_key_false nft_trace_enabled;

बाह्य स्थिर काष्ठा nft_set_type nft_set_rhash_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_hash_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_hash_fast_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_rbtree_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_biपंचांगap_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_pipapo_type;
बाह्य स्थिर काष्ठा nft_set_type nft_set_pipapo_avx2_type;

काष्ठा nft_expr;
काष्ठा nft_regs;
काष्ठा nft_pktinfo;
व्योम nft_meta_get_eval(स्थिर काष्ठा nft_expr *expr,
		       काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_cmp_eval(स्थिर काष्ठा nft_expr *expr,
		  काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_lookup_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_payload_eval(स्थिर काष्ठा nft_expr *expr,
		      काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_immediate_eval(स्थिर काष्ठा nft_expr *expr,
			काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_bitwise_eval(स्थिर काष्ठा nft_expr *expr,
		      काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_range_eval(स्थिर काष्ठा nft_expr *expr,
		    काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_byteorder_eval(स्थिर काष्ठा nft_expr *expr,
			काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_dynset_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_rt_get_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs, स्थिर काष्ठा nft_pktinfo *pkt);
#पूर्ण_अगर /* _NET_NF_TABLES_CORE_H */
