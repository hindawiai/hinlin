<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 842 Software Compression
 *
 * Copyright (C) 2015 Dan Streeपंचांगan, IBM Corp
 *
 * See 842.h क्रम details of the 842 compressed क्रमmat.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा MODULE_NAME "842_compress"

#समावेश <linux/hashtable.h>

#समावेश "842.h"
#समावेश "842_debugfs.h"

#घोषणा SW842_HASHTABLE8_BITS	(10)
#घोषणा SW842_HASHTABLE4_BITS	(11)
#घोषणा SW842_HASHTABLE2_BITS	(10)

/* By शेष, we allow compressing input buffers of any length, but we must
 * use the non-standard "short data" ढाँचा so the decompressor can correctly
 * reproduce the uncompressed data buffer at the right length.  However the
 * hardware 842 compressor will not recognize the "short data" ढाँचा, and
 * will fail to decompress any compressed buffer containing it (I have no idea
 * why anyone would want to use software to compress and hardware to decompress
 * but that's beside the poपूर्णांक).  This parameter क्रमces the compression
 * function to simply reject any input buffer that isn't a multiple of 8 bytes
 * दीर्घ, instead of using the "short data" ढाँचा, so that all compressed
 * buffers produced by this function will be decompressable by the 842 hardware
 * decompressor.  Unless you have a specअगरic need क्रम that, leave this disabled
 * so that any length buffer can be compressed.
 */
अटल bool sw842_strict;
module_param_named(strict, sw842_strict, bool, 0644);

अटल u8 comp_ops[OPS_MAX][5] = अणु /* params size in bits */
	अणु I8, N0, N0, N0, 0x19 पूर्ण, /* 8 */
	अणु I4, I4, N0, N0, 0x18 पूर्ण, /* 18 */
	अणु I4, I2, I2, N0, 0x17 पूर्ण, /* 25 */
	अणु I2, I2, I4, N0, 0x13 पूर्ण, /* 25 */
	अणु I2, I2, I2, I2, 0x12 पूर्ण, /* 32 */
	अणु I4, I2, D2, N0, 0x16 पूर्ण, /* 33 */
	अणु I4, D2, I2, N0, 0x15 पूर्ण, /* 33 */
	अणु I2, D2, I4, N0, 0x0e पूर्ण, /* 33 */
	अणु D2, I2, I4, N0, 0x09 पूर्ण, /* 33 */
	अणु I2, I2, I2, D2, 0x11 पूर्ण, /* 40 */
	अणु I2, I2, D2, I2, 0x10 पूर्ण, /* 40 */
	अणु I2, D2, I2, I2, 0x0d पूर्ण, /* 40 */
	अणु D2, I2, I2, I2, 0x08 पूर्ण, /* 40 */
	अणु I4, D4, N0, N0, 0x14 पूर्ण, /* 41 */
	अणु D4, I4, N0, N0, 0x04 पूर्ण, /* 41 */
	अणु I2, I2, D4, N0, 0x0f पूर्ण, /* 48 */
	अणु I2, D2, I2, D2, 0x0c पूर्ण, /* 48 */
	अणु I2, D4, I2, N0, 0x0b पूर्ण, /* 48 */
	अणु D2, I2, I2, D2, 0x07 पूर्ण, /* 48 */
	अणु D2, I2, D2, I2, 0x06 पूर्ण, /* 48 */
	अणु D4, I2, I2, N0, 0x03 पूर्ण, /* 48 */
	अणु I2, D2, D4, N0, 0x0a पूर्ण, /* 56 */
	अणु D2, I2, D4, N0, 0x05 पूर्ण, /* 56 */
	अणु D4, I2, D2, N0, 0x02 पूर्ण, /* 56 */
	अणु D4, D2, I2, N0, 0x01 पूर्ण, /* 56 */
	अणु D8, N0, N0, N0, 0x00 पूर्ण, /* 64 */
पूर्ण;

काष्ठा sw842_hlist_node8 अणु
	काष्ठा hlist_node node;
	u64 data;
	u8 index;
पूर्ण;

काष्ठा sw842_hlist_node4 अणु
	काष्ठा hlist_node node;
	u32 data;
	u16 index;
पूर्ण;

काष्ठा sw842_hlist_node2 अणु
	काष्ठा hlist_node node;
	u16 data;
	u8 index;
पूर्ण;

#घोषणा INDEX_NOT_FOUND		(-1)
#घोषणा INDEX_NOT_CHECKED	(-2)

काष्ठा sw842_param अणु
	u8 *in;
	u8 *instart;
	u64 ilen;
	u8 *out;
	u64 olen;
	u8 bit;
	u64 data8[1];
	u32 data4[2];
	u16 data2[4];
	पूर्णांक index8[1];
	पूर्णांक index4[2];
	पूर्णांक index2[4];
	DECLARE_HASHTABLE(htable8, SW842_HASHTABLE8_BITS);
	DECLARE_HASHTABLE(htable4, SW842_HASHTABLE4_BITS);
	DECLARE_HASHTABLE(htable2, SW842_HASHTABLE2_BITS);
	काष्ठा sw842_hlist_node8 node8[1 << I8_BITS];
	काष्ठा sw842_hlist_node4 node4[1 << I4_BITS];
	काष्ठा sw842_hlist_node2 node2[1 << I2_BITS];
पूर्ण;

#घोषणा get_input_data(p, o, b)						\
	be##b##_to_cpu(get_unaligned((__be##b *)((p)->in + (o))))

#घोषणा init_hashtable_nodes(p, b)	करो अणु			\
	पूर्णांक _i;							\
	hash_init((p)->htable##b);				\
	क्रम (_i = 0; _i < ARRAY_SIZE((p)->node##b); _i++) अणु	\
		(p)->node##b[_i].index = _i;			\
		(p)->node##b[_i].data = 0;			\
		INIT_HLIST_NODE(&(p)->node##b[_i].node);	\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा find_index(p, b, n)	(अणु					\
	काष्ठा sw842_hlist_node##b *_n;					\
	p->index##b[n] = INDEX_NOT_FOUND;				\
	hash_क्रम_each_possible(p->htable##b, _n, node, p->data##b[n]) अणु	\
		अगर (p->data##b[n] == _n->data) अणु			\
			p->index##b[n] = _n->index;			\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	p->index##b[n] >= 0;						\
पूर्ण)

#घोषणा check_index(p, b, n)			\
	((p)->index##b[n] == INDEX_NOT_CHECKED	\
	 ? find_index(p, b, n)			\
	 : (p)->index##b[n] >= 0)

#घोषणा replace_hash(p, b, i, d)	करो अणु				\
	काष्ठा sw842_hlist_node##b *_n = &(p)->node##b[(i)+(d)];	\
	hash_del(&_n->node);						\
	_n->data = (p)->data##b[d];					\
	pr_debug("add hash index%x %x pos %x data %lx\n", b,		\
		 (अचिन्हित पूर्णांक)_n->index,				\
		 (अचिन्हित पूर्णांक)((p)->in - (p)->instart),		\
		 (अचिन्हित दीर्घ)_n->data);				\
	hash_add((p)->htable##b, &_n->node, _n->data);			\
पूर्ण जबतक (0)

अटल u8 bmask[8] = अणु 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe पूर्ण;

अटल पूर्णांक add_bits(काष्ठा sw842_param *p, u64 d, u8 n);

अटल पूर्णांक __split_add_bits(काष्ठा sw842_param *p, u64 d, u8 n, u8 s)
अणु
	पूर्णांक ret;

	अगर (n <= s)
		वापस -EINVAL;

	ret = add_bits(p, d >> s, n - s);
	अगर (ret)
		वापस ret;
	वापस add_bits(p, d & GENMASK_ULL(s - 1, 0), s);
पूर्ण

अटल पूर्णांक add_bits(काष्ठा sw842_param *p, u64 d, u8 n)
अणु
	पूर्णांक b = p->bit, bits = b + n, s = round_up(bits, 8) - bits;
	u64 o;
	u8 *out = p->out;

	pr_debug("add %u bits %lx\n", (अचिन्हित अक्षर)n, (अचिन्हित दीर्घ)d);

	अगर (n > 64)
		वापस -EINVAL;

	/* split this up अगर writing to > 8 bytes (i.e. n == 64 && p->bit > 0),
	 * or अगर we're at the end of the output buffer and would ग_लिखो past end
	 */
	अगर (bits > 64)
		वापस __split_add_bits(p, d, n, 32);
	अन्यथा अगर (p->olen < 8 && bits > 32 && bits <= 56)
		वापस __split_add_bits(p, d, n, 16);
	अन्यथा अगर (p->olen < 4 && bits > 16 && bits <= 24)
		वापस __split_add_bits(p, d, n, 8);

	अगर (DIV_ROUND_UP(bits, 8) > p->olen)
		वापस -ENOSPC;

	o = *out & bmask[b];
	d <<= s;

	अगर (bits <= 8)
		*out = o | d;
	अन्यथा अगर (bits <= 16)
		put_unaligned(cpu_to_be16(o << 8 | d), (__be16 *)out);
	अन्यथा अगर (bits <= 24)
		put_unaligned(cpu_to_be32(o << 24 | d << 8), (__be32 *)out);
	अन्यथा अगर (bits <= 32)
		put_unaligned(cpu_to_be32(o << 24 | d), (__be32 *)out);
	अन्यथा अगर (bits <= 40)
		put_unaligned(cpu_to_be64(o << 56 | d << 24), (__be64 *)out);
	अन्यथा अगर (bits <= 48)
		put_unaligned(cpu_to_be64(o << 56 | d << 16), (__be64 *)out);
	अन्यथा अगर (bits <= 56)
		put_unaligned(cpu_to_be64(o << 56 | d << 8), (__be64 *)out);
	अन्यथा
		put_unaligned(cpu_to_be64(o << 56 | d), (__be64 *)out);

	p->bit += n;

	अगर (p->bit > 7) अणु
		p->out += p->bit / 8;
		p->olen -= p->bit / 8;
		p->bit %= 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_ढाँचा(काष्ठा sw842_param *p, u8 c)
अणु
	पूर्णांक ret, i, b = 0;
	u8 *t = comp_ops[c];
	bool inv = false;

	अगर (c >= OPS_MAX)
		वापस -EINVAL;

	pr_debug("template %x\n", t[4]);

	ret = add_bits(p, t[4], OP_BITS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < 4; i++) अणु
		pr_debug("op %x\n", t[i]);

		चयन (t[i] & OP_AMOUNT) अणु
		हाल OP_AMOUNT_8:
			अगर (b)
				inv = true;
			अन्यथा अगर (t[i] & OP_ACTION_INDEX)
				ret = add_bits(p, p->index8[0], I8_BITS);
			अन्यथा अगर (t[i] & OP_ACTION_DATA)
				ret = add_bits(p, p->data8[0], 64);
			अन्यथा
				inv = true;
			अवरोध;
		हाल OP_AMOUNT_4:
			अगर (b == 2 && t[i] & OP_ACTION_DATA)
				ret = add_bits(p, get_input_data(p, 2, 32), 32);
			अन्यथा अगर (b != 0 && b != 4)
				inv = true;
			अन्यथा अगर (t[i] & OP_ACTION_INDEX)
				ret = add_bits(p, p->index4[b >> 2], I4_BITS);
			अन्यथा अगर (t[i] & OP_ACTION_DATA)
				ret = add_bits(p, p->data4[b >> 2], 32);
			अन्यथा
				inv = true;
			अवरोध;
		हाल OP_AMOUNT_2:
			अगर (b != 0 && b != 2 && b != 4 && b != 6)
				inv = true;
			अगर (t[i] & OP_ACTION_INDEX)
				ret = add_bits(p, p->index2[b >> 1], I2_BITS);
			अन्यथा अगर (t[i] & OP_ACTION_DATA)
				ret = add_bits(p, p->data2[b >> 1], 16);
			अन्यथा
				inv = true;
			अवरोध;
		हाल OP_AMOUNT_0:
			inv = (b != 8) || !(t[i] & OP_ACTION_NOOP);
			अवरोध;
		शेष:
			inv = true;
			अवरोध;
		पूर्ण

		अगर (ret)
			वापस ret;

		अगर (inv) अणु
			pr_err("Invalid templ %x op %d : %x %x %x %x\n",
			       c, i, t[0], t[1], t[2], t[3]);
			वापस -EINVAL;
		पूर्ण

		b += t[i] & OP_AMOUNT;
	पूर्ण

	अगर (b != 8) अणु
		pr_err("Invalid template %x len %x : %x %x %x %x\n",
		       c, b, t[0], t[1], t[2], t[3]);
		वापस -EINVAL;
	पूर्ण

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_count[t[4]]);

	वापस 0;
पूर्ण

अटल पूर्णांक add_repeat_ढाँचा(काष्ठा sw842_param *p, u8 r)
अणु
	पूर्णांक ret;

	/* repeat param is 0-based */
	अगर (!r || --r > REPEAT_BITS_MAX)
		वापस -EINVAL;

	ret = add_bits(p, OP_REPEAT, OP_BITS);
	अगर (ret)
		वापस ret;

	ret = add_bits(p, r, REPEAT_BITS);
	अगर (ret)
		वापस ret;

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_repeat_count);

	वापस 0;
पूर्ण

अटल पूर्णांक add_लघु_data_ढाँचा(काष्ठा sw842_param *p, u8 b)
अणु
	पूर्णांक ret, i;

	अगर (!b || b > SHORT_DATA_BITS_MAX)
		वापस -EINVAL;

	ret = add_bits(p, OP_SHORT_DATA, OP_BITS);
	अगर (ret)
		वापस ret;

	ret = add_bits(p, b, SHORT_DATA_BITS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < b; i++) अणु
		ret = add_bits(p, p->in[i], 8);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_लघु_data_count);

	वापस 0;
पूर्ण

अटल पूर्णांक add_zeros_ढाँचा(काष्ठा sw842_param *p)
अणु
	पूर्णांक ret = add_bits(p, OP_ZEROS, OP_BITS);

	अगर (ret)
		वापस ret;

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_zeros_count);

	वापस 0;
पूर्ण

अटल पूर्णांक add_end_ढाँचा(काष्ठा sw842_param *p)
अणु
	पूर्णांक ret = add_bits(p, OP_END, OP_BITS);

	अगर (ret)
		वापस ret;

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_end_count);

	वापस 0;
पूर्ण

अटल bool check_ढाँचा(काष्ठा sw842_param *p, u8 c)
अणु
	u8 *t = comp_ops[c];
	पूर्णांक i, match, b = 0;

	अगर (c >= OPS_MAX)
		वापस false;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (t[i] & OP_ACTION_INDEX) अणु
			अगर (t[i] & OP_AMOUNT_2)
				match = check_index(p, 2, b >> 1);
			अन्यथा अगर (t[i] & OP_AMOUNT_4)
				match = check_index(p, 4, b >> 2);
			अन्यथा अगर (t[i] & OP_AMOUNT_8)
				match = check_index(p, 8, 0);
			अन्यथा
				वापस false;
			अगर (!match)
				वापस false;
		पूर्ण

		b += t[i] & OP_AMOUNT;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम get_next_data(काष्ठा sw842_param *p)
अणु
	p->data8[0] = get_input_data(p, 0, 64);
	p->data4[0] = get_input_data(p, 0, 32);
	p->data4[1] = get_input_data(p, 4, 32);
	p->data2[0] = get_input_data(p, 0, 16);
	p->data2[1] = get_input_data(p, 2, 16);
	p->data2[2] = get_input_data(p, 4, 16);
	p->data2[3] = get_input_data(p, 6, 16);
पूर्ण

/* update the hashtable entries.
 * only call this after finding/adding the current ढाँचा
 * the dataN fields क्रम the current 8 byte block must be alपढ़ोy updated
 */
अटल व्योम update_hashtables(काष्ठा sw842_param *p)
अणु
	u64 pos = p->in - p->instart;
	u64 n8 = (pos >> 3) % (1 << I8_BITS);
	u64 n4 = (pos >> 2) % (1 << I4_BITS);
	u64 n2 = (pos >> 1) % (1 << I2_BITS);

	replace_hash(p, 8, n8, 0);
	replace_hash(p, 4, n4, 0);
	replace_hash(p, 4, n4, 1);
	replace_hash(p, 2, n2, 0);
	replace_hash(p, 2, n2, 1);
	replace_hash(p, 2, n2, 2);
	replace_hash(p, 2, n2, 3);
पूर्ण

/* find the next ढाँचा to use, and add it
 * the p->dataN fields must alपढ़ोy be set क्रम the current 8 byte block
 */
अटल पूर्णांक process_next(काष्ठा sw842_param *p)
अणु
	पूर्णांक ret, i;

	p->index8[0] = INDEX_NOT_CHECKED;
	p->index4[0] = INDEX_NOT_CHECKED;
	p->index4[1] = INDEX_NOT_CHECKED;
	p->index2[0] = INDEX_NOT_CHECKED;
	p->index2[1] = INDEX_NOT_CHECKED;
	p->index2[2] = INDEX_NOT_CHECKED;
	p->index2[3] = INDEX_NOT_CHECKED;

	/* check up to OPS_MAX - 1; last op is our fallback */
	क्रम (i = 0; i < OPS_MAX - 1; i++) अणु
		अगर (check_ढाँचा(p, i))
			अवरोध;
	पूर्ण

	ret = add_ढाँचा(p, i);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * sw842_compress
 *
 * Compress the uncompressed buffer of length @ilen at @in to the output buffer
 * @out, using no more than @olen bytes, using the 842 compression क्रमmat.
 *
 * Returns: 0 on success, error on failure.  The @olen parameter
 * will contain the number of output bytes written on success, or
 * 0 on error.
 */
पूर्णांक sw842_compress(स्थिर u8 *in, अचिन्हित पूर्णांक ilen,
		   u8 *out, अचिन्हित पूर्णांक *olen, व्योम *wmem)
अणु
	काष्ठा sw842_param *p = (काष्ठा sw842_param *)wmem;
	पूर्णांक ret;
	u64 last, next, pad, total;
	u8 repeat_count = 0;
	u32 crc;

	BUILD_BUG_ON(माप(*p) > SW842_MEM_COMPRESS);

	init_hashtable_nodes(p, 8);
	init_hashtable_nodes(p, 4);
	init_hashtable_nodes(p, 2);

	p->in = (u8 *)in;
	p->instart = p->in;
	p->ilen = ilen;
	p->out = out;
	p->olen = *olen;
	p->bit = 0;

	total = p->olen;

	*olen = 0;

	/* अगर using strict mode, we can only compress a multiple of 8 */
	अगर (sw842_strict && (ilen % 8)) अणु
		pr_err("Using strict mode, can't compress len %d\n", ilen);
		वापस -EINVAL;
	पूर्ण

	/* let's compress at least 8 bytes, mkay? */
	अगर (unlikely(ilen < 8))
		जाओ skip_comp;

	/* make initial 'last' different so we don't match the first समय */
	last = ~get_unaligned((u64 *)p->in);

	जबतक (p->ilen > 7) अणु
		next = get_unaligned((u64 *)p->in);

		/* must get the next data, as we need to update the hashtable
		 * entries with the new data every समय
		 */
		get_next_data(p);

		/* we करोn't care about endianness in last or next;
		 * we're just comparing 8 bytes to another 8 bytes,
		 * they're both the same endianness
		 */
		अगर (next == last) अणु
			/* repeat count bits are 0-based, so we stop at +1 */
			अगर (++repeat_count <= REPEAT_BITS_MAX)
				जाओ repeat;
		पूर्ण
		अगर (repeat_count) अणु
			ret = add_repeat_ढाँचा(p, repeat_count);
			repeat_count = 0;
			अगर (next == last) /* reached max repeat bits */
				जाओ repeat;
		पूर्ण

		अगर (next == 0)
			ret = add_zeros_ढाँचा(p);
		अन्यथा
			ret = process_next(p);

		अगर (ret)
			वापस ret;

repeat:
		last = next;
		update_hashtables(p);
		p->in += 8;
		p->ilen -= 8;
	पूर्ण

	अगर (repeat_count) अणु
		ret = add_repeat_ढाँचा(p, repeat_count);
		अगर (ret)
			वापस ret;
	पूर्ण

skip_comp:
	अगर (p->ilen > 0) अणु
		ret = add_लघु_data_ढाँचा(p, p->ilen);
		अगर (ret)
			वापस ret;

		p->in += p->ilen;
		p->ilen = 0;
	पूर्ण

	ret = add_end_ढाँचा(p);
	अगर (ret)
		वापस ret;

	/*
	 * crc(0:31) is appended to target data starting with the next
	 * bit after End of stream ढाँचा.
	 * nx842 calculates CRC क्रम data in big-endian क्रमmat. So करोing
	 * same here so that sw842 decompression can be used क्रम both
	 * compressed data.
	 */
	crc = crc32_be(0, in, ilen);
	ret = add_bits(p, crc, CRC_BITS);
	अगर (ret)
		वापस ret;

	अगर (p->bit) अणु
		p->out++;
		p->olen--;
		p->bit = 0;
	पूर्ण

	/* pad compressed length to multiple of 8 */
	pad = (8 - ((total - p->olen) % 8)) % 8;
	अगर (pad) अणु
		अगर (pad > p->olen) /* we were so बंद! */
			वापस -ENOSPC;
		स_रखो(p->out, 0, pad);
		p->out += pad;
		p->olen -= pad;
	पूर्ण

	अगर (unlikely((total - p->olen) > अच_पूर्णांक_उच्च))
		वापस -ENOSPC;

	*olen = total - p->olen;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sw842_compress);

अटल पूर्णांक __init sw842_init(व्योम)
अणु
	अगर (sw842_ढाँचा_counts)
		sw842_debugfs_create();

	वापस 0;
पूर्ण
module_init(sw842_init);

अटल व्योम __निकास sw842_निकास(व्योम)
अणु
	अगर (sw842_ढाँचा_counts)
		sw842_debugfs_हटाओ();
पूर्ण
module_निकास(sw842_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software 842 Compressor");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
