<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  RPL implementation
 *
 *  Author:
 *  (C) 2020 Alexander Aring <alex.aring@gmail.com>
 */

#अगर_अघोषित _NET_RPL_H
#घोषणा _NET_RPL_H

#समावेश <linux/rpl.h>

#अगर IS_ENABLED(CONFIG_IPV6_RPL_LWTUNNEL)
बाह्य पूर्णांक rpl_init(व्योम);
बाह्य व्योम rpl_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक rpl_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rpl_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* Worst decompression memory usage ipv6 address (16) + pad 7 */
#घोषणा IPV6_RPL_SRH_WORST_SWAP_SIZE (माप(काष्ठा in6_addr) + 7)

माप_प्रकार ipv6_rpl_srh_size(अचिन्हित अक्षर n, अचिन्हित अक्षर cmpri,
			 अचिन्हित अक्षर cmpre);

व्योम ipv6_rpl_srh_decompress(काष्ठा ipv6_rpl_sr_hdr *outhdr,
			     स्थिर काष्ठा ipv6_rpl_sr_hdr *inhdr,
			     स्थिर काष्ठा in6_addr *daddr, अचिन्हित अक्षर n);

व्योम ipv6_rpl_srh_compress(काष्ठा ipv6_rpl_sr_hdr *outhdr,
			   स्थिर काष्ठा ipv6_rpl_sr_hdr *inhdr,
			   स्थिर काष्ठा in6_addr *daddr, अचिन्हित अक्षर n);

#पूर्ण_अगर /* _NET_RPL_H */
