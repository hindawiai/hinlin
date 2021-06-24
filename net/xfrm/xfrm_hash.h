<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XFRM_HASH_H
#घोषणा _XFRM_HASH_H

#समावेश <linux/xfrm.h>
#समावेश <linux/socket.h>
#समावेश <linux/jhash.h>

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm4_addr_hash(स्थिर xfrm_address_t *addr)
अणु
	वापस ntohl(addr->a4);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm6_addr_hash(स्थिर xfrm_address_t *addr)
अणु
	वापस jhash2((__क्रमce u32 *)addr->a6, 4, 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm4_daddr_saddr_hash(स्थिर xfrm_address_t *daddr,
						    स्थिर xfrm_address_t *saddr)
अणु
	u32 sum = (__क्रमce u32)daddr->a4 + (__क्रमce u32)saddr->a4;
	वापस ntohl((__क्रमce __be32)sum);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm6_daddr_saddr_hash(स्थिर xfrm_address_t *daddr,
						    स्थिर xfrm_address_t *saddr)
अणु
	वापस __xfrm6_addr_hash(daddr) ^ __xfrm6_addr_hash(saddr);
पूर्ण

अटल अंतरभूत u32 __bits2mask32(__u8 bits)
अणु
	u32 mask32 = 0xffffffff;

	अगर (bits == 0)
		mask32 = 0;
	अन्यथा अगर (bits < 32)
		mask32 <<= (32 - bits);

	वापस mask32;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm4_dpref_spref_hash(स्थिर xfrm_address_t *daddr,
						    स्थिर xfrm_address_t *saddr,
						    __u8 dbits,
						    __u8 sbits)
अणु
	वापस jhash_2words(ntohl(daddr->a4) & __bits2mask32(dbits),
			    ntohl(saddr->a4) & __bits2mask32(sbits),
			    0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm6_pref_hash(स्थिर xfrm_address_t *addr,
					     __u8 prefixlen)
अणु
	अचिन्हित पूर्णांक pdw;
	अचिन्हित पूर्णांक pbi;
	u32 initval = 0;

	pdw = prefixlen >> 5;     /* num of whole u32 in prefix */
	pbi = prefixlen &  0x1f;  /* num of bits in incomplete u32 in prefix */

	अगर (pbi) अणु
		__be32 mask;

		mask = htonl((0xffffffff) << (32 - pbi));

		initval = (__क्रमce u32)(addr->a6[pdw] & mask);
	पूर्ण

	वापस jhash2((__क्रमce u32 *)addr->a6, pdw, initval);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm6_dpref_spref_hash(स्थिर xfrm_address_t *daddr,
						    स्थिर xfrm_address_t *saddr,
						    __u8 dbits,
						    __u8 sbits)
अणु
	वापस __xfrm6_pref_hash(daddr, dbits) ^
	       __xfrm6_pref_hash(saddr, sbits);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm_dst_hash(स्थिर xfrm_address_t *daddr,
					   स्थिर xfrm_address_t *saddr,
					   u32 reqid, अचिन्हित लघु family,
					   अचिन्हित पूर्णांक hmask)
अणु
	अचिन्हित पूर्णांक h = family ^ reqid;
	चयन (family) अणु
	हाल AF_INET:
		h ^= __xfrm4_daddr_saddr_hash(daddr, saddr);
		अवरोध;
	हाल AF_INET6:
		h ^= __xfrm6_daddr_saddr_hash(daddr, saddr);
		अवरोध;
	पूर्ण
	वापस (h ^ (h >> 16)) & hmask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __xfrm_src_hash(स्थिर xfrm_address_t *daddr,
					   स्थिर xfrm_address_t *saddr,
					   अचिन्हित लघु family,
					   अचिन्हित पूर्णांक hmask)
अणु
	अचिन्हित पूर्णांक h = family;
	चयन (family) अणु
	हाल AF_INET:
		h ^= __xfrm4_daddr_saddr_hash(daddr, saddr);
		अवरोध;
	हाल AF_INET6:
		h ^= __xfrm6_daddr_saddr_hash(daddr, saddr);
		अवरोध;
	पूर्ण
	वापस (h ^ (h >> 16)) & hmask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
__xfrm_spi_hash(स्थिर xfrm_address_t *daddr, __be32 spi, u8 proto,
		अचिन्हित लघु family, अचिन्हित पूर्णांक hmask)
अणु
	अचिन्हित पूर्णांक h = (__क्रमce u32)spi ^ proto;
	चयन (family) अणु
	हाल AF_INET:
		h ^= __xfrm4_addr_hash(daddr);
		अवरोध;
	हाल AF_INET6:
		h ^= __xfrm6_addr_hash(daddr);
		अवरोध;
	पूर्ण
	वापस (h ^ (h >> 10) ^ (h >> 20)) & hmask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __idx_hash(u32 index, अचिन्हित पूर्णांक hmask)
अणु
	वापस (index ^ (index >> 8)) & hmask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __sel_hash(स्थिर काष्ठा xfrm_selector *sel,
				      अचिन्हित लघु family, अचिन्हित पूर्णांक hmask,
				      u8 dbits, u8 sbits)
अणु
	स्थिर xfrm_address_t *daddr = &sel->daddr;
	स्थिर xfrm_address_t *saddr = &sel->saddr;
	अचिन्हित पूर्णांक h = 0;

	चयन (family) अणु
	हाल AF_INET:
		अगर (sel->prefixlen_d < dbits ||
		    sel->prefixlen_s < sbits)
			वापस hmask + 1;

		h = __xfrm4_dpref_spref_hash(daddr, saddr, dbits, sbits);
		अवरोध;

	हाल AF_INET6:
		अगर (sel->prefixlen_d < dbits ||
		    sel->prefixlen_s < sbits)
			वापस hmask + 1;

		h = __xfrm6_dpref_spref_hash(daddr, saddr, dbits, sbits);
		अवरोध;
	पूर्ण
	h ^= (h >> 16);
	वापस h & hmask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __addr_hash(स्थिर xfrm_address_t *daddr,
				       स्थिर xfrm_address_t *saddr,
				       अचिन्हित लघु family,
				       अचिन्हित पूर्णांक hmask,
				       u8 dbits, u8 sbits)
अणु
	अचिन्हित पूर्णांक h = 0;

	चयन (family) अणु
	हाल AF_INET:
		h = __xfrm4_dpref_spref_hash(daddr, saddr, dbits, sbits);
		अवरोध;

	हाल AF_INET6:
		h = __xfrm6_dpref_spref_hash(daddr, saddr, dbits, sbits);
		अवरोध;
	पूर्ण
	h ^= (h >> 16);
	वापस h & hmask;
पूर्ण

काष्ठा hlist_head *xfrm_hash_alloc(अचिन्हित पूर्णांक sz);
व्योम xfrm_hash_मुक्त(काष्ठा hlist_head *n, अचिन्हित पूर्णांक sz);

#पूर्ण_अगर /* _XFRM_HASH_H */
