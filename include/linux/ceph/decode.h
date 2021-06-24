<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CEPH_DECODE_H
#घोषणा __CEPH_DECODE_H

#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/ceph/types.h>

/*
 * in all हालs,
 *   व्योम **p     poपूर्णांकer to position poपूर्णांकer
 *   व्योम *end    poपूर्णांकer to end of buffer (last byte + 1)
 */

अटल अंतरभूत u64 ceph_decode_64(व्योम **p)
अणु
	u64 v = get_unaligned_le64(*p);
	*p += माप(u64);
	वापस v;
पूर्ण
अटल अंतरभूत u32 ceph_decode_32(व्योम **p)
अणु
	u32 v = get_unaligned_le32(*p);
	*p += माप(u32);
	वापस v;
पूर्ण
अटल अंतरभूत u16 ceph_decode_16(व्योम **p)
अणु
	u16 v = get_unaligned_le16(*p);
	*p += माप(u16);
	वापस v;
पूर्ण
अटल अंतरभूत u8 ceph_decode_8(व्योम **p)
अणु
	u8 v = *(u8 *)*p;
	(*p)++;
	वापस v;
पूर्ण
अटल अंतरभूत व्योम ceph_decode_copy(व्योम **p, व्योम *pv, माप_प्रकार n)
अणु
	स_नकल(pv, *p, n);
	*p += n;
पूर्ण

/*
 * bounds check input.
 */
अटल अंतरभूत bool ceph_has_room(व्योम **p, व्योम *end, माप_प्रकार n)
अणु
	वापस end >= *p && n <= end - *p;
पूर्ण

#घोषणा ceph_decode_need(p, end, n, bad)			\
	करो अणु							\
		अगर (!likely(ceph_has_room(p, end, n)))		\
			जाओ bad;				\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_64_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_decode_need(p, end, माप(u64), bad);	\
		v = ceph_decode_64(p);				\
	पूर्ण जबतक (0)
#घोषणा ceph_decode_32_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_decode_need(p, end, माप(u32), bad);	\
		v = ceph_decode_32(p);				\
	पूर्ण जबतक (0)
#घोषणा ceph_decode_16_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_decode_need(p, end, माप(u16), bad);	\
		v = ceph_decode_16(p);				\
	पूर्ण जबतक (0)
#घोषणा ceph_decode_8_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_decode_need(p, end, माप(u8), bad);	\
		v = ceph_decode_8(p);				\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_copy_safe(p, end, pv, n, bad)		\
	करो अणु							\
		ceph_decode_need(p, end, n, bad);		\
		ceph_decode_copy(p, pv, n);			\
	पूर्ण जबतक (0)

/*
 * Allocate a buffer big enough to hold the wire-encoded string, and
 * decode the string पूर्णांकo it.  The resulting string will always be
 * terminated with '\0'.  If successful, *p will be advanced
 * past the decoded data.  Also, अगर lenp is not a null poपूर्णांकer, the
 * length (not including the terminating '\0') will be recorded in
 * *lenp.  Note that a zero-length string is a valid वापस value.
 *
 * Returns a poपूर्णांकer to the newly-allocated string buffer, or a
 * poपूर्णांकer-coded त्रुटि_सं अगर an error occurs.  Neither *p nor *lenp
 * will have been updated अगर an error is वापसed.
 *
 * There are two possible failures:
 *   - converting the string would require accessing memory at or
 *     beyond the "end" poपूर्णांकer provided (-दुस्फल)
 *   - memory could not be allocated क्रम the result (-ENOMEM)
 */
अटल अंतरभूत अक्षर *ceph_extract_encoded_string(व्योम **p, व्योम *end,
						माप_प्रकार *lenp, gfp_t gfp)
अणु
	u32 len;
	व्योम *sp = *p;
	अक्षर *buf;

	ceph_decode_32_safe(&sp, end, len, bad);
	अगर (!ceph_has_room(&sp, end, len))
		जाओ bad;

	buf = kदो_स्मृति(len + 1, gfp);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	अगर (len)
		स_नकल(buf, sp, len);
	buf[len] = '\0';

	*p = (अक्षर *) *p + माप (u32) + len;
	अगर (lenp)
		*lenp = (माप_प्रकार) len;

	वापस buf;

bad:
	वापस ERR_PTR(-दुस्फल);
पूर्ण

/*
 * skip helpers
 */
#घोषणा ceph_decode_skip_n(p, end, n, bad)			\
	करो अणु							\
		ceph_decode_need(p, end, n, bad);		\
                *p += n;					\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_skip_64(p, end, bad)			\
ceph_decode_skip_n(p, end, माप(u64), bad)

#घोषणा ceph_decode_skip_32(p, end, bad)			\
ceph_decode_skip_n(p, end, माप(u32), bad)

#घोषणा ceph_decode_skip_16(p, end, bad)			\
ceph_decode_skip_n(p, end, माप(u16), bad)

#घोषणा ceph_decode_skip_8(p, end, bad)				\
ceph_decode_skip_n(p, end, माप(u8), bad)

#घोषणा ceph_decode_skip_string(p, end, bad)			\
	करो अणु							\
		u32 len;					\
								\
		ceph_decode_32_safe(p, end, len, bad);		\
		ceph_decode_skip_n(p, end, len, bad);		\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_skip_set(p, end, type, bad)			\
	करो अणु							\
		u32 len;					\
								\
		ceph_decode_32_safe(p, end, len, bad);		\
		जबतक (len--)					\
			ceph_decode_skip_##type(p, end, bad);	\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_skip_map(p, end, ktype, vtype, bad)		\
	करो अणु							\
		u32 len;					\
								\
		ceph_decode_32_safe(p, end, len, bad);		\
		जबतक (len--) अणु					\
			ceph_decode_skip_##ktype(p, end, bad);	\
			ceph_decode_skip_##vtype(p, end, bad);	\
		पूर्ण						\
	पूर्ण जबतक (0)

#घोषणा ceph_decode_skip_map_of_map(p, end, ktype1, ktype2, vtype2, bad) \
	करो अणु							\
		u32 len;					\
								\
		ceph_decode_32_safe(p, end, len, bad);		\
		जबतक (len--) अणु					\
			ceph_decode_skip_##ktype1(p, end, bad);	\
			ceph_decode_skip_map(p, end, ktype2, vtype2, bad); \
		पूर्ण						\
	पूर्ण जबतक (0)

/*
 * काष्ठा ceph_बारpec <-> काष्ठा बारpec64
 */
अटल अंतरभूत व्योम ceph_decode_बारpec64(काष्ठा बारpec64 *ts,
					  स्थिर काष्ठा ceph_बारpec *tv)
अणु
	/*
	 * This will still overflow in year 2106.  We could extend
	 * the protocol to steal two more bits from tv_nsec to
	 * add three more 136 year epochs after that the way ext4
	 * करोes अगर necessary.
	 */
	ts->tv_sec = (समय64_t)le32_to_cpu(tv->tv_sec);
	ts->tv_nsec = (दीर्घ)le32_to_cpu(tv->tv_nsec);
पूर्ण
अटल अंतरभूत व्योम ceph_encode_बारpec64(काष्ठा ceph_बारpec *tv,
					  स्थिर काष्ठा बारpec64 *ts)
अणु
	tv->tv_sec = cpu_to_le32((u32)ts->tv_sec);
	tv->tv_nsec = cpu_to_le32((u32)ts->tv_nsec);
पूर्ण

/*
 * sockaddr_storage <-> ceph_sockaddr
 */
#घोषणा CEPH_ENTITY_ADDR_TYPE_NONE	0
#घोषणा CEPH_ENTITY_ADDR_TYPE_LEGACY	__cpu_to_le32(1)
#घोषणा CEPH_ENTITY_ADDR_TYPE_MSGR2	__cpu_to_le32(2)
#घोषणा CEPH_ENTITY_ADDR_TYPE_ANY	__cpu_to_le32(3)

अटल अंतरभूत व्योम ceph_encode_banner_addr(काष्ठा ceph_entity_addr *a)
अणु
	__be16 ss_family = htons(a->in_addr.ss_family);
	a->in_addr.ss_family = *(__u16 *)&ss_family;

	/* Banner addresses require TYPE_NONE */
	a->type = CEPH_ENTITY_ADDR_TYPE_NONE;
पूर्ण
अटल अंतरभूत व्योम ceph_decode_banner_addr(काष्ठा ceph_entity_addr *a)
अणु
	__be16 ss_family = *(__be16 *)&a->in_addr.ss_family;
	a->in_addr.ss_family = ntohs(ss_family);
	WARN_ON(a->in_addr.ss_family == 512);
	a->type = CEPH_ENTITY_ADDR_TYPE_LEGACY;
पूर्ण

बाह्य पूर्णांक ceph_decode_entity_addr(व्योम **p, व्योम *end,
				   काष्ठा ceph_entity_addr *addr);
पूर्णांक ceph_decode_entity_addrvec(व्योम **p, व्योम *end, bool msgr2,
			       काष्ठा ceph_entity_addr *addr);

पूर्णांक ceph_entity_addr_encoding_len(स्थिर काष्ठा ceph_entity_addr *addr);
व्योम ceph_encode_entity_addr(व्योम **p, स्थिर काष्ठा ceph_entity_addr *addr);

/*
 * encoders
 */
अटल अंतरभूत व्योम ceph_encode_64(व्योम **p, u64 v)
अणु
	put_unaligned_le64(v, (__le64 *)*p);
	*p += माप(u64);
पूर्ण
अटल अंतरभूत व्योम ceph_encode_32(व्योम **p, u32 v)
अणु
	put_unaligned_le32(v, (__le32 *)*p);
	*p += माप(u32);
पूर्ण
अटल अंतरभूत व्योम ceph_encode_16(व्योम **p, u16 v)
अणु
	put_unaligned_le16(v, (__le16 *)*p);
	*p += माप(u16);
पूर्ण
अटल अंतरभूत व्योम ceph_encode_8(व्योम **p, u8 v)
अणु
	*(u8 *)*p = v;
	(*p)++;
पूर्ण
अटल अंतरभूत व्योम ceph_encode_copy(व्योम **p, स्थिर व्योम *s, पूर्णांक len)
अणु
	स_नकल(*p, s, len);
	*p += len;
पूर्ण

/*
 * filepath, string encoders
 */
अटल अंतरभूत व्योम ceph_encode_filepath(व्योम **p, व्योम *end,
					u64 ino, स्थिर अक्षर *path)
अणु
	u32 len = path ? म_माप(path) : 0;
	BUG_ON(*p + 1 + माप(ino) + माप(len) + len > end);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, ino);
	ceph_encode_32(p, len);
	अगर (len)
		स_नकल(*p, path, len);
	*p += len;
पूर्ण

अटल अंतरभूत व्योम ceph_encode_string(व्योम **p, व्योम *end,
				      स्थिर अक्षर *s, u32 len)
अणु
	BUG_ON(*p + माप(len) + len > end);
	ceph_encode_32(p, len);
	अगर (len)
		स_नकल(*p, s, len);
	*p += len;
पूर्ण

/*
 * version and length starting block encoders/decoders
 */

/* current code version (u8) + compat code version (u8) + len of काष्ठा (u32) */
#घोषणा CEPH_ENCODING_START_BLK_LEN 6

/**
 * ceph_start_encoding - start encoding block
 * @काष्ठा_v: current (code) version of the encoding
 * @काष्ठा_compat: oldest code version that can decode it
 * @काष्ठा_len: length of काष्ठा encoding
 */
अटल अंतरभूत व्योम ceph_start_encoding(व्योम **p, u8 काष्ठा_v, u8 काष्ठा_compat,
				       u32 काष्ठा_len)
अणु
	ceph_encode_8(p, काष्ठा_v);
	ceph_encode_8(p, काष्ठा_compat);
	ceph_encode_32(p, काष्ठा_len);
पूर्ण

/**
 * ceph_start_decoding - start decoding block
 * @v: current version of the encoding that the code supports
 * @name: name of the काष्ठा (मुक्त-क्रमm)
 * @काष्ठा_v: out param क्रम the encoding version
 * @काष्ठा_len: out param क्रम the length of काष्ठा encoding
 *
 * Validates the length of काष्ठा encoding, so unsafe ceph_decode_*
 * variants can be used क्रम decoding.
 */
अटल अंतरभूत पूर्णांक ceph_start_decoding(व्योम **p, व्योम *end, u8 v,
				      स्थिर अक्षर *name, u8 *काष्ठा_v,
				      u32 *काष्ठा_len)
अणु
	u8 काष्ठा_compat;

	ceph_decode_need(p, end, CEPH_ENCODING_START_BLK_LEN, bad);
	*काष्ठा_v = ceph_decode_8(p);
	काष्ठा_compat = ceph_decode_8(p);
	अगर (v < काष्ठा_compat) अणु
		pr_warn("got struct_v %d struct_compat %d > %d of %s\n",
			*काष्ठा_v, काष्ठा_compat, v, name);
		वापस -EINVAL;
	पूर्ण

	*काष्ठा_len = ceph_decode_32(p);
	ceph_decode_need(p, end, *काष्ठा_len, bad);
	वापस 0;

bad:
	वापस -दुस्फल;
पूर्ण

#घोषणा ceph_encode_need(p, end, n, bad)			\
	करो अणु							\
		अगर (!likely(ceph_has_room(p, end, n)))		\
			जाओ bad;				\
	पूर्ण जबतक (0)

#घोषणा ceph_encode_64_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_encode_need(p, end, माप(u64), bad);	\
		ceph_encode_64(p, v);				\
	पूर्ण जबतक (0)
#घोषणा ceph_encode_32_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_encode_need(p, end, माप(u32), bad);	\
		ceph_encode_32(p, v);				\
	पूर्ण जबतक (0)
#घोषणा ceph_encode_16_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_encode_need(p, end, माप(u16), bad);	\
		ceph_encode_16(p, v);				\
	पूर्ण जबतक (0)
#घोषणा ceph_encode_8_safe(p, end, v, bad)			\
	करो अणु							\
		ceph_encode_need(p, end, माप(u8), bad);	\
		ceph_encode_8(p, v);				\
	पूर्ण जबतक (0)

#घोषणा ceph_encode_copy_safe(p, end, pv, n, bad)		\
	करो अणु							\
		ceph_encode_need(p, end, n, bad);		\
		ceph_encode_copy(p, pv, n);			\
	पूर्ण जबतक (0)
#घोषणा ceph_encode_string_safe(p, end, s, n, bad)		\
	करो अणु							\
		ceph_encode_need(p, end, n, bad);		\
		ceph_encode_string(p, end, s, n);		\
	पूर्ण जबतक (0)


#पूर्ण_अगर
