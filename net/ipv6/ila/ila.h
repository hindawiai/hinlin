<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Tom Herbert <tom@herbertland.com>
 */

#अगर_अघोषित __ILA_H
#घोषणा __ILA_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/genetlink.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <uapi/linux/ila.h>

काष्ठा ila_locator अणु
	जोड़ अणु
		__u8            v8[8];
		__be16          v16[4];
		__be32          v32[2];
		__be64		v64;
	पूर्ण;
पूर्ण;

काष्ठा ila_identअगरier अणु
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			u8 __space:4;
			u8 csum_neutral:1;
			u8 type:3;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
			u8 type:3;
			u8 csum_neutral:1;
			u8 __space:4;
#अन्यथा
#त्रुटि  "Adjust your <asm/byteorder.h> defines"
#पूर्ण_अगर
			u8 __space2[7];
		पूर्ण;
		__u8            v8[8];
		__be16          v16[4];
		__be32          v32[2];
		__be64		v64;
	पूर्ण;
पूर्ण;

#घोषणा CSUM_NEUTRAL_FLAG	htonl(0x10000000)

काष्ठा ila_addr अणु
	जोड़ अणु
		काष्ठा in6_addr addr;
		काष्ठा अणु
			काष्ठा ila_locator loc;
			काष्ठा ila_identअगरier ident;
		पूर्ण;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा ila_addr *ila_a2i(काष्ठा in6_addr *addr)
अणु
	वापस (काष्ठा ila_addr *)addr;
पूर्ण

काष्ठा ila_params अणु
	काष्ठा ila_locator locator;
	काष्ठा ila_locator locator_match;
	__wsum csum_dअगरf;
	u8 csum_mode;
	u8 ident_type;
पूर्ण;

अटल अंतरभूत __wsum compute_csum_dअगरf8(स्थिर __be32 *from, स्थिर __be32 *to)
अणु
	__be32 dअगरf[] = अणु
		~from[0], ~from[1], to[0], to[1],
	पूर्ण;

	वापस csum_partial(dअगरf, माप(dअगरf), 0);
पूर्ण

अटल अंतरभूत bool ila_csum_neutral_set(काष्ठा ila_identअगरier ident)
अणु
	वापस !!(ident.csum_neutral);
पूर्ण

व्योम ila_update_ipv6_locator(काष्ठा sk_buff *skb, काष्ठा ila_params *p,
			     bool set_csum_neutral);

व्योम ila_init_saved_csum(काष्ठा ila_params *p);

काष्ठा ila_net अणु
	काष्ठा अणु
		काष्ठा rhashtable rhash_table;
		spinlock_t *locks; /* Bucket locks क्रम entry manipulation */
		अचिन्हित पूर्णांक locks_mask;
		bool hooks_रेजिस्टरed;
	पूर्ण xlat;
पूर्ण;

पूर्णांक ila_lwt_init(व्योम);
व्योम ila_lwt_fini(व्योम);

पूर्णांक ila_xlat_init_net(काष्ठा net *net);
व्योम ila_xlat_निकास_net(काष्ठा net *net);

पूर्णांक ila_xlat_nl_cmd_add_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ila_xlat_nl_cmd_del_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ila_xlat_nl_cmd_get_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ila_xlat_nl_cmd_flush(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ila_xlat_nl_dump_start(काष्ठा netlink_callback *cb);
पूर्णांक ila_xlat_nl_dump_करोne(काष्ठा netlink_callback *cb);
पूर्णांक ila_xlat_nl_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

बाह्य अचिन्हित पूर्णांक ila_net_id;

बाह्य काष्ठा genl_family ila_nl_family;

#पूर्ण_अगर /* __ILA_H */
