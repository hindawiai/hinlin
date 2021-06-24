<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LZO1X Compressor from LZO
 *
 *  Copyright (C) 1996-2012 Markus F.X.J. Oberhumer <markus@oberhumer.com>
 *
 *  The full LZO package can be found at:
 *  http://www.oberhumer.com/खोलोsource/lzo/
 *
 *  Changed क्रम Linux kernel use by:
 *  Nitin Gupta <nitingupta910@gmail.com>
 *  Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/lzo.h>
#समावेश "lzodefs.h"

अटल noअंतरभूत माप_प्रकार
lzo1x_1_करो_compress(स्थिर अचिन्हित अक्षर *in, माप_प्रकार in_len,
		    अचिन्हित अक्षर *out, माप_प्रकार *out_len,
		    माप_प्रकार ti, व्योम *wrkmem, चिन्हित अक्षर *state_offset,
		    स्थिर अचिन्हित अक्षर bitstream_version)
अणु
	स्थिर अचिन्हित अक्षर *ip;
	अचिन्हित अक्षर *op;
	स्थिर अचिन्हित अक्षर * स्थिर in_end = in + in_len;
	स्थिर अचिन्हित अक्षर * स्थिर ip_end = in + in_len - 20;
	स्थिर अचिन्हित अक्षर *ii;
	lzo_dict_t * स्थिर dict = (lzo_dict_t *) wrkmem;

	op = out;
	ip = in;
	ii = ip;
	ip += ti < 4 ? 4 - ti : 0;

	क्रम (;;) अणु
		स्थिर अचिन्हित अक्षर *m_pos = शून्य;
		माप_प्रकार t, m_len, m_off;
		u32 dv;
		u32 run_length = 0;
literal:
		ip += 1 + ((ip - ii) >> 5);
next:
		अगर (unlikely(ip >= ip_end))
			अवरोध;
		dv = get_unaligned_le32(ip);

		अगर (dv == 0 && bitstream_version) अणु
			स्थिर अचिन्हित अक्षर *ir = ip + 4;
			स्थिर अचिन्हित अक्षर *limit = ip_end
				< (ip + MAX_ZERO_RUN_LENGTH + 1)
				? ip_end : ip + MAX_ZERO_RUN_LENGTH + 1;
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && \
	defined(LZO_FAST_64BIT_MEMORY_ACCESS)
			u64 dv64;

			क्रम (; (ir + 32) <= limit; ir += 32) अणु
				dv64 = get_unaligned((u64 *)ir);
				dv64 |= get_unaligned((u64 *)ir + 1);
				dv64 |= get_unaligned((u64 *)ir + 2);
				dv64 |= get_unaligned((u64 *)ir + 3);
				अगर (dv64)
					अवरोध;
			पूर्ण
			क्रम (; (ir + 8) <= limit; ir += 8) अणु
				dv64 = get_unaligned((u64 *)ir);
				अगर (dv64) अणु
#  अगर defined(__LITTLE_ENDIAN)
					ir += __builtin_ctzll(dv64) >> 3;
#  elअगर defined(__BIG_ENDIAN)
					ir += __builtin_clzll(dv64) >> 3;
#  अन्यथा
#    error "missing endian definition"
#  endअगर
					अवरोध;
				पूर्ण
			पूर्ण
#अन्यथा
			जबतक ((ir < (स्थिर अचिन्हित अक्षर *)
					ALIGN((uपूर्णांकptr_t)ir, 4)) &&
					(ir < limit) && (*ir == 0))
				ir++;
			अगर (IS_ALIGNED((uपूर्णांकptr_t)ir, 4)) अणु
				क्रम (; (ir + 4) <= limit; ir += 4) अणु
					dv = *((u32 *)ir);
					अगर (dv) अणु
#  अगर defined(__LITTLE_ENDIAN)
						ir += __builtin_ctz(dv) >> 3;
#  elअगर defined(__BIG_ENDIAN)
						ir += __builtin_clz(dv) >> 3;
#  अन्यथा
#    error "missing endian definition"
#  endअगर
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			जबतक (likely(ir < limit) && unlikely(*ir == 0))
				ir++;
			run_length = ir - ip;
			अगर (run_length > MAX_ZERO_RUN_LENGTH)
				run_length = MAX_ZERO_RUN_LENGTH;
		पूर्ण अन्यथा अणु
			t = ((dv * 0x1824429d) >> (32 - D_BITS)) & D_MASK;
			m_pos = in + dict[t];
			dict[t] = (lzo_dict_t) (ip - in);
			अगर (unlikely(dv != get_unaligned_le32(m_pos)))
				जाओ literal;
		पूर्ण

		ii -= ti;
		ti = 0;
		t = ip - ii;
		अगर (t != 0) अणु
			अगर (t <= 3) अणु
				op[*state_offset] |= t;
				COPY4(op, ii);
				op += t;
			पूर्ण अन्यथा अगर (t <= 16) अणु
				*op++ = (t - 3);
				COPY8(op, ii);
				COPY8(op + 8, ii + 8);
				op += t;
			पूर्ण अन्यथा अणु
				अगर (t <= 18) अणु
					*op++ = (t - 3);
				पूर्ण अन्यथा अणु
					माप_प्रकार tt = t - 18;
					*op++ = 0;
					जबतक (unlikely(tt > 255)) अणु
						tt -= 255;
						*op++ = 0;
					पूर्ण
					*op++ = tt;
				पूर्ण
				करो अणु
					COPY8(op, ii);
					COPY8(op + 8, ii + 8);
					op += 16;
					ii += 16;
					t -= 16;
				पूर्ण जबतक (t >= 16);
				अगर (t > 0) करो अणु
					*op++ = *ii++;
				पूर्ण जबतक (--t > 0);
			पूर्ण
		पूर्ण

		अगर (unlikely(run_length)) अणु
			ip += run_length;
			run_length -= MIN_ZERO_RUN_LENGTH;
			put_unaligned_le32((run_length << 21) | 0xfffc18
					   | (run_length & 0x7), op);
			op += 4;
			run_length = 0;
			*state_offset = -3;
			जाओ finished_writing_inकाष्ठाion;
		पूर्ण

		m_len = 4;
		अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && defined(LZO_USE_CTZ64)
		u64 v;
		v = get_unaligned((स्थिर u64 *) (ip + m_len)) ^
		    get_unaligned((स्थिर u64 *) (m_pos + m_len));
		अगर (unlikely(v == 0)) अणु
			करो अणु
				m_len += 8;
				v = get_unaligned((स्थिर u64 *) (ip + m_len)) ^
				    get_unaligned((स्थिर u64 *) (m_pos + m_len));
				अगर (unlikely(ip + m_len >= ip_end))
					जाओ m_len_करोne;
			पूर्ण जबतक (v == 0);
		पूर्ण
#  अगर defined(__LITTLE_ENDIAN)
		m_len += (अचिन्हित) __builtin_ctzll(v) / 8;
#  elअगर defined(__BIG_ENDIAN)
		m_len += (अचिन्हित) __builtin_clzll(v) / 8;
#  अन्यथा
#    error "missing endian definition"
#  endअगर
#या_अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && defined(LZO_USE_CTZ32)
		u32 v;
		v = get_unaligned((स्थिर u32 *) (ip + m_len)) ^
		    get_unaligned((स्थिर u32 *) (m_pos + m_len));
		अगर (unlikely(v == 0)) अणु
			करो अणु
				m_len += 4;
				v = get_unaligned((स्थिर u32 *) (ip + m_len)) ^
				    get_unaligned((स्थिर u32 *) (m_pos + m_len));
				अगर (v != 0)
					अवरोध;
				m_len += 4;
				v = get_unaligned((स्थिर u32 *) (ip + m_len)) ^
				    get_unaligned((स्थिर u32 *) (m_pos + m_len));
				अगर (unlikely(ip + m_len >= ip_end))
					जाओ m_len_करोne;
			पूर्ण जबतक (v == 0);
		पूर्ण
#  अगर defined(__LITTLE_ENDIAN)
		m_len += (अचिन्हित) __builtin_ctz(v) / 8;
#  elअगर defined(__BIG_ENDIAN)
		m_len += (अचिन्हित) __builtin_clz(v) / 8;
#  अन्यथा
#    error "missing endian definition"
#  endअगर
#अन्यथा
		अगर (unlikely(ip[m_len] == m_pos[m_len])) अणु
			करो अणु
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (ip[m_len] != m_pos[m_len])
					अवरोध;
				m_len += 1;
				अगर (unlikely(ip + m_len >= ip_end))
					जाओ m_len_करोne;
			पूर्ण जबतक (ip[m_len] == m_pos[m_len]);
		पूर्ण
#पूर्ण_अगर
		पूर्ण
m_len_करोne:

		m_off = ip - m_pos;
		ip += m_len;
		अगर (m_len <= M2_MAX_LEN && m_off <= M2_MAX_OFFSET) अणु
			m_off -= 1;
			*op++ = (((m_len - 1) << 5) | ((m_off & 7) << 2));
			*op++ = (m_off >> 3);
		पूर्ण अन्यथा अगर (m_off <= M3_MAX_OFFSET) अणु
			m_off -= 1;
			अगर (m_len <= M3_MAX_LEN)
				*op++ = (M3_MARKER | (m_len - 2));
			अन्यथा अणु
				m_len -= M3_MAX_LEN;
				*op++ = M3_MARKER | 0;
				जबतक (unlikely(m_len > 255)) अणु
					m_len -= 255;
					*op++ = 0;
				पूर्ण
				*op++ = (m_len);
			पूर्ण
			*op++ = (m_off << 2);
			*op++ = (m_off >> 6);
		पूर्ण अन्यथा अणु
			m_off -= 0x4000;
			अगर (m_len <= M4_MAX_LEN)
				*op++ = (M4_MARKER | ((m_off >> 11) & 8)
						| (m_len - 2));
			अन्यथा अणु
				अगर (unlikely(((m_off & 0x403f) == 0x403f)
						&& (m_len >= 261)
						&& (m_len <= 264))
						&& likely(bitstream_version)) अणु
					// Under lzo-rle, block copies
					// क्रम 261 <= length <= 264 and
					// (distance & 0x80f3) == 0x80f3
					// can result in ambiguous
					// output. Adjust length
					// to 260 to prevent ambiguity.
					ip -= m_len - 260;
					m_len = 260;
				पूर्ण
				m_len -= M4_MAX_LEN;
				*op++ = (M4_MARKER | ((m_off >> 11) & 8));
				जबतक (unlikely(m_len > 255)) अणु
					m_len -= 255;
					*op++ = 0;
				पूर्ण
				*op++ = (m_len);
			पूर्ण
			*op++ = (m_off << 2);
			*op++ = (m_off >> 6);
		पूर्ण
		*state_offset = -2;
finished_writing_inकाष्ठाion:
		ii = ip;
		जाओ next;
	पूर्ण
	*out_len = op - out;
	वापस in_end - (ii - ti);
पूर्ण

अटल पूर्णांक lzogeneric1x_1_compress(स्थिर अचिन्हित अक्षर *in, माप_प्रकार in_len,
		     अचिन्हित अक्षर *out, माप_प्रकार *out_len,
		     व्योम *wrkmem, स्थिर अचिन्हित अक्षर bitstream_version)
अणु
	स्थिर अचिन्हित अक्षर *ip = in;
	अचिन्हित अक्षर *op = out;
	अचिन्हित अक्षर *data_start;
	माप_प्रकार l = in_len;
	माप_प्रकार t = 0;
	चिन्हित अक्षर state_offset = -2;
	अचिन्हित पूर्णांक m4_max_offset;

	// LZO v0 will never ग_लिखो 17 as first byte (except क्रम zero-length
	// input), so this is used to version the bitstream
	अगर (bitstream_version > 0) अणु
		*op++ = 17;
		*op++ = bitstream_version;
		m4_max_offset = M4_MAX_OFFSET_V1;
	पूर्ण अन्यथा अणु
		m4_max_offset = M4_MAX_OFFSET_V0;
	पूर्ण

	data_start = op;

	जबतक (l > 20) अणु
		माप_प्रकार ll = l <= (m4_max_offset + 1) ? l : (m4_max_offset + 1);
		uपूर्णांकptr_t ll_end = (uपूर्णांकptr_t) ip + ll;
		अगर ((ll_end + ((t + ll) >> 5)) <= ll_end)
			अवरोध;
		BUILD_BUG_ON(D_SIZE * माप(lzo_dict_t) > LZO1X_1_MEM_COMPRESS);
		स_रखो(wrkmem, 0, D_SIZE * माप(lzo_dict_t));
		t = lzo1x_1_करो_compress(ip, ll, op, out_len, t, wrkmem,
					&state_offset, bitstream_version);
		ip += ll;
		op += *out_len;
		l  -= ll;
	पूर्ण
	t += l;

	अगर (t > 0) अणु
		स्थिर अचिन्हित अक्षर *ii = in + in_len - t;

		अगर (op == data_start && t <= 238) अणु
			*op++ = (17 + t);
		पूर्ण अन्यथा अगर (t <= 3) अणु
			op[state_offset] |= t;
		पूर्ण अन्यथा अगर (t <= 18) अणु
			*op++ = (t - 3);
		पूर्ण अन्यथा अणु
			माप_प्रकार tt = t - 18;
			*op++ = 0;
			जबतक (tt > 255) अणु
				tt -= 255;
				*op++ = 0;
			पूर्ण
			*op++ = tt;
		पूर्ण
		अगर (t >= 16) करो अणु
			COPY8(op, ii);
			COPY8(op + 8, ii + 8);
			op += 16;
			ii += 16;
			t -= 16;
		पूर्ण जबतक (t >= 16);
		अगर (t > 0) करो अणु
			*op++ = *ii++;
		पूर्ण जबतक (--t > 0);
	पूर्ण

	*op++ = M4_MARKER | 1;
	*op++ = 0;
	*op++ = 0;

	*out_len = op - out;
	वापस LZO_E_OK;
पूर्ण

पूर्णांक lzo1x_1_compress(स्थिर अचिन्हित अक्षर *in, माप_प्रकार in_len,
		     अचिन्हित अक्षर *out, माप_प्रकार *out_len,
		     व्योम *wrkmem)
अणु
	वापस lzogeneric1x_1_compress(in, in_len, out, out_len, wrkmem, 0);
पूर्ण

पूर्णांक lzorle1x_1_compress(स्थिर अचिन्हित अक्षर *in, माप_प्रकार in_len,
		     अचिन्हित अक्षर *out, माप_प्रकार *out_len,
		     व्योम *wrkmem)
अणु
	वापस lzogeneric1x_1_compress(in, in_len, out, out_len,
				       wrkmem, LZO_VERSION);
पूर्ण

EXPORT_SYMBOL_GPL(lzo1x_1_compress);
EXPORT_SYMBOL_GPL(lzorle1x_1_compress);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LZO1X-1 Compressor");
