<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 842 Software Decompression
 *
 * Copyright (C) 2015 Dan Streeपंचांगan, IBM Corp
 *
 * See 842.h क्रम details of the 842 compressed क्रमmat.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा MODULE_NAME "842_decompress"

#समावेश "842.h"
#समावेश "842_debugfs.h"

/* rolling fअगरo sizes */
#घोषणा I2_FIFO_SIZE	(2 * (1 << I2_BITS))
#घोषणा I4_FIFO_SIZE	(4 * (1 << I4_BITS))
#घोषणा I8_FIFO_SIZE	(8 * (1 << I8_BITS))

अटल u8 decomp_ops[OPS_MAX][4] = अणु
	अणु D8, N0, N0, N0 पूर्ण,
	अणु D4, D2, I2, N0 पूर्ण,
	अणु D4, I2, D2, N0 पूर्ण,
	अणु D4, I2, I2, N0 पूर्ण,
	अणु D4, I4, N0, N0 पूर्ण,
	अणु D2, I2, D4, N0 पूर्ण,
	अणु D2, I2, D2, I2 पूर्ण,
	अणु D2, I2, I2, D2 पूर्ण,
	अणु D2, I2, I2, I2 पूर्ण,
	अणु D2, I2, I4, N0 पूर्ण,
	अणु I2, D2, D4, N0 पूर्ण,
	अणु I2, D4, I2, N0 पूर्ण,
	अणु I2, D2, I2, D2 पूर्ण,
	अणु I2, D2, I2, I2 पूर्ण,
	अणु I2, D2, I4, N0 पूर्ण,
	अणु I2, I2, D4, N0 पूर्ण,
	अणु I2, I2, D2, I2 पूर्ण,
	अणु I2, I2, I2, D2 पूर्ण,
	अणु I2, I2, I2, I2 पूर्ण,
	अणु I2, I2, I4, N0 पूर्ण,
	अणु I4, D4, N0, N0 पूर्ण,
	अणु I4, D2, I2, N0 पूर्ण,
	अणु I4, I2, D2, N0 पूर्ण,
	अणु I4, I2, I2, N0 पूर्ण,
	अणु I4, I4, N0, N0 पूर्ण,
	अणु I8, N0, N0, N0 पूर्ण
पूर्ण;

काष्ठा sw842_param अणु
	u8 *in;
	u8 bit;
	u64 ilen;
	u8 *out;
	u8 *ostart;
	u64 olen;
पूर्ण;

#घोषणा beN_to_cpu(d, s)					\
	((s) == 2 ? be16_to_cpu(get_unaligned((__be16 *)d)) :	\
	 (s) == 4 ? be32_to_cpu(get_unaligned((__be32 *)d)) :	\
	 (s) == 8 ? be64_to_cpu(get_unaligned((__be64 *)d)) :	\
	 0)

अटल पूर्णांक next_bits(काष्ठा sw842_param *p, u64 *d, u8 n);

अटल पूर्णांक __split_next_bits(काष्ठा sw842_param *p, u64 *d, u8 n, u8 s)
अणु
	u64 पंचांगp = 0;
	पूर्णांक ret;

	अगर (n <= s) अणु
		pr_debug("split_next_bits invalid n %u s %u\n", n, s);
		वापस -EINVAL;
	पूर्ण

	ret = next_bits(p, &पंचांगp, n - s);
	अगर (ret)
		वापस ret;
	ret = next_bits(p, d, s);
	अगर (ret)
		वापस ret;
	*d |= पंचांगp << s;
	वापस 0;
पूर्ण

अटल पूर्णांक next_bits(काष्ठा sw842_param *p, u64 *d, u8 n)
अणु
	u8 *in = p->in, b = p->bit, bits = b + n;

	अगर (n > 64) अणु
		pr_debug("next_bits invalid n %u\n", n);
		वापस -EINVAL;
	पूर्ण

	/* split this up अगर पढ़ोing > 8 bytes, or अगर we're at the end of
	 * the input buffer and would पढ़ो past the end
	 */
	अगर (bits > 64)
		वापस __split_next_bits(p, d, n, 32);
	अन्यथा अगर (p->ilen < 8 && bits > 32 && bits <= 56)
		वापस __split_next_bits(p, d, n, 16);
	अन्यथा अगर (p->ilen < 4 && bits > 16 && bits <= 24)
		वापस __split_next_bits(p, d, n, 8);

	अगर (DIV_ROUND_UP(bits, 8) > p->ilen)
		वापस -EOVERFLOW;

	अगर (bits <= 8)
		*d = *in >> (8 - bits);
	अन्यथा अगर (bits <= 16)
		*d = be16_to_cpu(get_unaligned((__be16 *)in)) >> (16 - bits);
	अन्यथा अगर (bits <= 32)
		*d = be32_to_cpu(get_unaligned((__be32 *)in)) >> (32 - bits);
	अन्यथा
		*d = be64_to_cpu(get_unaligned((__be64 *)in)) >> (64 - bits);

	*d &= GENMASK_ULL(n - 1, 0);

	p->bit += n;

	अगर (p->bit > 7) अणु
		p->in += p->bit / 8;
		p->ilen -= p->bit / 8;
		p->bit %= 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_data(काष्ठा sw842_param *p, u8 n)
अणु
	u64 v;
	पूर्णांक ret;

	अगर (n > p->olen)
		वापस -ENOSPC;

	ret = next_bits(p, &v, n * 8);
	अगर (ret)
		वापस ret;

	चयन (n) अणु
	हाल 2:
		put_unaligned(cpu_to_be16((u16)v), (__be16 *)p->out);
		अवरोध;
	हाल 4:
		put_unaligned(cpu_to_be32((u32)v), (__be32 *)p->out);
		अवरोध;
	हाल 8:
		put_unaligned(cpu_to_be64((u64)v), (__be64 *)p->out);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	p->out += n;
	p->olen -= n;

	वापस 0;
पूर्ण

अटल पूर्णांक __करो_index(काष्ठा sw842_param *p, u8 size, u8 bits, u64 fsize)
अणु
	u64 index, offset, total = round_करोwn(p->out - p->ostart, 8);
	पूर्णांक ret;

	ret = next_bits(p, &index, bits);
	अगर (ret)
		वापस ret;

	offset = index * size;

	/* a ring buffer of fsize is used; correct the offset */
	अगर (total > fsize) अणु
		/* this is where the current fअगरo is */
		u64 section = round_करोwn(total, fsize);
		/* the current pos in the fअगरo */
		u64 pos = total - section;

		/* अगर the offset is past/at the pos, we need to
		 * go back to the last fअगरo section
		 */
		अगर (offset >= pos)
			section -= fsize;

		offset += section;
	पूर्ण

	अगर (offset + size > total) अणु
		pr_debug("index%x %lx points past end %lx\n", size,
			 (अचिन्हित दीर्घ)offset, (अचिन्हित दीर्घ)total);
		वापस -EINVAL;
	पूर्ण

	अगर (size != 2 && size != 4 && size != 8)
		WARN(1, "__do_index invalid size %x\n", size);
	अन्यथा
		pr_debug("index%x to %lx off %lx adjoff %lx tot %lx data %lx\n",
			 size, (अचिन्हित दीर्घ)index,
			 (अचिन्हित दीर्घ)(index * size), (अचिन्हित दीर्घ)offset,
			 (अचिन्हित दीर्घ)total,
			 (अचिन्हित दीर्घ)beN_to_cpu(&p->ostart[offset], size));

	स_नकल(p->out, &p->ostart[offset], size);
	p->out += size;
	p->olen -= size;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_index(काष्ठा sw842_param *p, u8 n)
अणु
	चयन (n) अणु
	हाल 2:
		वापस __करो_index(p, 2, I2_BITS, I2_FIFO_SIZE);
	हाल 4:
		वापस __करो_index(p, 4, I4_BITS, I4_FIFO_SIZE);
	हाल 8:
		वापस __करो_index(p, 8, I8_BITS, I8_FIFO_SIZE);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_op(काष्ठा sw842_param *p, u8 o)
अणु
	पूर्णांक i, ret = 0;

	अगर (o >= OPS_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < 4; i++) अणु
		u8 op = decomp_ops[o][i];

		pr_debug("op is %x\n", op);

		चयन (op & OP_ACTION) अणु
		हाल OP_ACTION_DATA:
			ret = करो_data(p, op & OP_AMOUNT);
			अवरोध;
		हाल OP_ACTION_INDEX:
			ret = करो_index(p, op & OP_AMOUNT);
			अवरोध;
		हाल OP_ACTION_NOOP:
			अवरोध;
		शेष:
			pr_err("Internal error, invalid op %x\n", op);
			वापस -EINVAL;
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sw842_ढाँचा_counts)
		atomic_inc(&ढाँचा_count[o]);

	वापस 0;
पूर्ण

/**
 * sw842_decompress
 *
 * Decompress the 842-compressed buffer of length @ilen at @in
 * to the output buffer @out, using no more than @olen bytes.
 *
 * The compressed buffer must be only a single 842-compressed buffer,
 * with the standard क्रमmat described in the comments in 842.h
 * Processing will stop when the 842 "END" ढाँचा is detected,
 * not the end of the buffer.
 *
 * Returns: 0 on success, error on failure.  The @olen parameter
 * will contain the number of output bytes written on success, or
 * 0 on error.
 */
पूर्णांक sw842_decompress(स्थिर u8 *in, अचिन्हित पूर्णांक ilen,
		     u8 *out, अचिन्हित पूर्णांक *olen)
अणु
	काष्ठा sw842_param p;
	पूर्णांक ret;
	u64 op, rep, पंचांगp, bytes, total;
	u64 crc;

	p.in = (u8 *)in;
	p.bit = 0;
	p.ilen = ilen;
	p.out = out;
	p.ostart = out;
	p.olen = *olen;

	total = p.olen;

	*olen = 0;

	करो अणु
		ret = next_bits(&p, &op, OP_BITS);
		अगर (ret)
			वापस ret;

		pr_debug("template is %lx\n", (अचिन्हित दीर्घ)op);

		चयन (op) अणु
		हाल OP_REPEAT:
			ret = next_bits(&p, &rep, REPEAT_BITS);
			अगर (ret)
				वापस ret;

			अगर (p.out == out) /* no previous bytes */
				वापस -EINVAL;

			/* copy rep + 1 */
			rep++;

			अगर (rep * 8 > p.olen)
				वापस -ENOSPC;

			जबतक (rep-- > 0) अणु
				स_नकल(p.out, p.out - 8, 8);
				p.out += 8;
				p.olen -= 8;
			पूर्ण

			अगर (sw842_ढाँचा_counts)
				atomic_inc(&ढाँचा_repeat_count);

			अवरोध;
		हाल OP_ZEROS:
			अगर (8 > p.olen)
				वापस -ENOSPC;

			स_रखो(p.out, 0, 8);
			p.out += 8;
			p.olen -= 8;

			अगर (sw842_ढाँचा_counts)
				atomic_inc(&ढाँचा_zeros_count);

			अवरोध;
		हाल OP_SHORT_DATA:
			ret = next_bits(&p, &bytes, SHORT_DATA_BITS);
			अगर (ret)
				वापस ret;

			अगर (!bytes || bytes > SHORT_DATA_BITS_MAX)
				वापस -EINVAL;

			जबतक (bytes-- > 0) अणु
				ret = next_bits(&p, &पंचांगp, 8);
				अगर (ret)
					वापस ret;
				*p.out = (u8)पंचांगp;
				p.out++;
				p.olen--;
			पूर्ण

			अगर (sw842_ढाँचा_counts)
				atomic_inc(&ढाँचा_लघु_data_count);

			अवरोध;
		हाल OP_END:
			अगर (sw842_ढाँचा_counts)
				atomic_inc(&ढाँचा_end_count);

			अवरोध;
		शेष: /* use ढाँचा */
			ret = करो_op(&p, op);
			अगर (ret)
				वापस ret;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (op != OP_END);

	/*
	 * crc(0:31) is saved in compressed data starting with the
	 * next bit after End of stream ढाँचा.
	 */
	ret = next_bits(&p, &crc, CRC_BITS);
	अगर (ret)
		वापस ret;

	/*
	 * Validate CRC saved in compressed data.
	 */
	अगर (crc != (u64)crc32_be(0, out, total - p.olen)) अणु
		pr_debug("CRC mismatch for decompression\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely((total - p.olen) > अच_पूर्णांक_उच्च))
		वापस -ENOSPC;

	*olen = total - p.olen;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sw842_decompress);

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
MODULE_DESCRIPTION("Software 842 Decompressor");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
