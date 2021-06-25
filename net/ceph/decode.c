<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/inet.h>

#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/messenger.h>  /* क्रम ceph_pr_addr() */

अटल पूर्णांक
ceph_decode_entity_addr_versioned(व्योम **p, व्योम *end,
				  काष्ठा ceph_entity_addr *addr)
अणु
	पूर्णांक ret;
	u8 काष्ठा_v;
	u32 काष्ठा_len, addr_len;
	व्योम *काष्ठा_end;

	ret = ceph_start_decoding(p, end, 1, "entity_addr_t", &काष्ठा_v,
				  &काष्ठा_len);
	अगर (ret)
		जाओ bad;

	ret = -EINVAL;
	काष्ठा_end = *p + काष्ठा_len;

	ceph_decode_copy_safe(p, end, &addr->type, माप(addr->type), bad);

	ceph_decode_copy_safe(p, end, &addr->nonce, माप(addr->nonce), bad);

	ceph_decode_32_safe(p, end, addr_len, bad);
	अगर (addr_len > माप(addr->in_addr))
		जाओ bad;

	स_रखो(&addr->in_addr, 0, माप(addr->in_addr));
	अगर (addr_len) अणु
		ceph_decode_copy_safe(p, end, &addr->in_addr, addr_len, bad);

		addr->in_addr.ss_family =
			le16_to_cpu((__क्रमce __le16)addr->in_addr.ss_family);
	पूर्ण

	/* Advance past anything the client करोesn't yet understand */
	*p = काष्ठा_end;
	ret = 0;
bad:
	वापस ret;
पूर्ण

अटल पूर्णांक
ceph_decode_entity_addr_legacy(व्योम **p, व्योम *end,
			       काष्ठा ceph_entity_addr *addr)
अणु
	पूर्णांक ret = -EINVAL;

	/* Skip rest of type field */
	ceph_decode_skip_n(p, end, 3, bad);

	/*
	 * Clients that करोn't support ADDR2 always send TYPE_NONE, change it
	 * to TYPE_LEGACY क्रम क्रमward compatibility.
	 */
	addr->type = CEPH_ENTITY_ADDR_TYPE_LEGACY;
	ceph_decode_copy_safe(p, end, &addr->nonce, माप(addr->nonce), bad);
	स_रखो(&addr->in_addr, 0, माप(addr->in_addr));
	ceph_decode_copy_safe(p, end, &addr->in_addr,
			      माप(addr->in_addr), bad);
	addr->in_addr.ss_family =
			be16_to_cpu((__क्रमce __be16)addr->in_addr.ss_family);
	ret = 0;
bad:
	वापस ret;
पूर्ण

पूर्णांक
ceph_decode_entity_addr(व्योम **p, व्योम *end, काष्ठा ceph_entity_addr *addr)
अणु
	u8 marker;

	ceph_decode_8_safe(p, end, marker, bad);
	अगर (marker == 1)
		वापस ceph_decode_entity_addr_versioned(p, end, addr);
	अन्यथा अगर (marker == 0)
		वापस ceph_decode_entity_addr_legacy(p, end, addr);
bad:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ceph_decode_entity_addr);

/*
 * Return addr of desired type (MSGR2 or LEGACY) or error.
 * Make sure there is only one match.
 *
 * Assume encoding with MSG_ADDR2.
 */
पूर्णांक ceph_decode_entity_addrvec(व्योम **p, व्योम *end, bool msgr2,
			       काष्ठा ceph_entity_addr *addr)
अणु
	__le32 my_type = msgr2 ? CEPH_ENTITY_ADDR_TYPE_MSGR2 :
				 CEPH_ENTITY_ADDR_TYPE_LEGACY;
	काष्ठा ceph_entity_addr पंचांगp_addr;
	पूर्णांक addr_cnt;
	bool found;
	u8 marker;
	पूर्णांक ret;
	पूर्णांक i;

	ceph_decode_8_safe(p, end, marker, e_inval);
	अगर (marker != 2) अणु
		pr_err("bad addrvec marker %d\n", marker);
		वापस -EINVAL;
	पूर्ण

	ceph_decode_32_safe(p, end, addr_cnt, e_inval);
	करोut("%s addr_cnt %d\n", __func__, addr_cnt);

	found = false;
	क्रम (i = 0; i < addr_cnt; i++) अणु
		ret = ceph_decode_entity_addr(p, end, &पंचांगp_addr);
		अगर (ret)
			वापस ret;

		करोut("%s i %d addr %s\n", __func__, i, ceph_pr_addr(&पंचांगp_addr));
		अगर (पंचांगp_addr.type == my_type) अणु
			अगर (found) अणु
				pr_err("another match of type %d in addrvec\n",
				       le32_to_cpu(my_type));
				वापस -EINVAL;
			पूर्ण

			स_नकल(addr, &पंचांगp_addr, माप(*addr));
			found = true;
		पूर्ण
	पूर्ण

	अगर (found)
		वापस 0;

	अगर (!addr_cnt)
		वापस 0;  /* normal -- e.g. unused OSD id/slot */

	अगर (addr_cnt == 1 && !स_प्रथम_inv(&पंचांगp_addr, 0, माप(पंचांगp_addr)))
		वापस 0;  /* weird but effectively the same as !addr_cnt */

	pr_err("no match of type %d in addrvec\n", le32_to_cpu(my_type));
	वापस -ENOENT;

e_inval:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ceph_decode_entity_addrvec);

अटल पूर्णांक get_sockaddr_encoding_len(sa_family_t family)
अणु
	जोड़ अणु
		काष्ठा sockaddr sa;
		काष्ठा sockaddr_in sin;
		काष्ठा sockaddr_in6 sin6;
	पूर्ण u;

	चयन (family) अणु
	हाल AF_INET:
		वापस माप(u.sin);
	हाल AF_INET6:
		वापस माप(u.sin6);
	शेष:
		वापस माप(u);
	पूर्ण
पूर्ण

पूर्णांक ceph_entity_addr_encoding_len(स्थिर काष्ठा ceph_entity_addr *addr)
अणु
	sa_family_t family = get_unaligned(&addr->in_addr.ss_family);
	पूर्णांक addr_len = get_sockaddr_encoding_len(family);

	वापस 1 + CEPH_ENCODING_START_BLK_LEN + 4 + 4 + 4 + addr_len;
पूर्ण

व्योम ceph_encode_entity_addr(व्योम **p, स्थिर काष्ठा ceph_entity_addr *addr)
अणु
	sa_family_t family = get_unaligned(&addr->in_addr.ss_family);
	पूर्णांक addr_len = get_sockaddr_encoding_len(family);

	ceph_encode_8(p, 1);  /* marker */
	ceph_start_encoding(p, 1, 1, माप(addr->type) +
				     माप(addr->nonce) +
				     माप(u32) + addr_len);
	ceph_encode_copy(p, &addr->type, माप(addr->type));
	ceph_encode_copy(p, &addr->nonce, माप(addr->nonce));

	ceph_encode_32(p, addr_len);
	ceph_encode_16(p, family);
	ceph_encode_copy(p, addr->in_addr.__data, addr_len - माप(family));
पूर्ण
