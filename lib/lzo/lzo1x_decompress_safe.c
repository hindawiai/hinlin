<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LZO1X Decompressor from LZO
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

#अगर_अघोषित STATIC
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#पूर्ण_अगर
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/lzo.h>
#समावेश "lzodefs.h"

#घोषणा HAVE_IP(x)      ((माप_प्रकार)(ip_end - ip) >= (माप_प्रकार)(x))
#घोषणा HAVE_OP(x)      ((माप_प्रकार)(op_end - op) >= (माप_प्रकार)(x))
#घोषणा NEED_IP(x)      अगर (!HAVE_IP(x)) जाओ input_overrun
#घोषणा NEED_OP(x)      अगर (!HAVE_OP(x)) जाओ output_overrun
#घोषणा TEST_LB(m_pos)  अगर ((m_pos) < out) जाओ lookbehind_overrun

/* This MAX_255_COUNT is the maximum number of बार we can add 255 to a base
 * count without overflowing an पूर्णांकeger. The multiply will overflow when
 * multiplying 255 by more than MAXINT/255. The sum will overflow earlier
 * depending on the base count. Since the base count is taken from a u8
 * and a few bits, it is safe to assume that it will always be lower than
 * or equal to 2*255, thus we can always prevent any overflow by accepting
 * two less 255 steps. See Documentation/staging/lzo.rst क्रम more inक्रमmation.
 */
#घोषणा MAX_255_COUNT      ((((माप_प्रकार)~0) / 255) - 2)

पूर्णांक lzo1x_decompress_safe(स्थिर अचिन्हित अक्षर *in, माप_प्रकार in_len,
			  अचिन्हित अक्षर *out, माप_प्रकार *out_len)
अणु
	अचिन्हित अक्षर *op;
	स्थिर अचिन्हित अक्षर *ip;
	माप_प्रकार t, next;
	माप_प्रकार state = 0;
	स्थिर अचिन्हित अक्षर *m_pos;
	स्थिर अचिन्हित अक्षर * स्थिर ip_end = in + in_len;
	अचिन्हित अक्षर * स्थिर op_end = out + *out_len;

	अचिन्हित अक्षर bitstream_version;

	op = out;
	ip = in;

	अगर (unlikely(in_len < 3))
		जाओ input_overrun;

	अगर (likely(in_len >= 5) && likely(*ip == 17)) अणु
		bitstream_version = ip[1];
		ip += 2;
	पूर्ण अन्यथा अणु
		bitstream_version = 0;
	पूर्ण

	अगर (*ip > 17) अणु
		t = *ip++ - 17;
		अगर (t < 4) अणु
			next = t;
			जाओ match_next;
		पूर्ण
		जाओ copy_literal_run;
	पूर्ण

	क्रम (;;) अणु
		t = *ip++;
		अगर (t < 16) अणु
			अगर (likely(state == 0)) अणु
				अगर (unlikely(t == 0)) अणु
					माप_प्रकार offset;
					स्थिर अचिन्हित अक्षर *ip_last = ip;

					जबतक (unlikely(*ip == 0)) अणु
						ip++;
						NEED_IP(1);
					पूर्ण
					offset = ip - ip_last;
					अगर (unlikely(offset > MAX_255_COUNT))
						वापस LZO_E_ERROR;

					offset = (offset << 8) - offset;
					t += offset + 15 + *ip++;
				पूर्ण
				t += 3;
copy_literal_run:
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
				अगर (likely(HAVE_IP(t + 15) && HAVE_OP(t + 15))) अणु
					स्थिर अचिन्हित अक्षर *ie = ip + t;
					अचिन्हित अक्षर *oe = op + t;
					करो अणु
						COPY8(op, ip);
						op += 8;
						ip += 8;
						COPY8(op, ip);
						op += 8;
						ip += 8;
					पूर्ण जबतक (ip < ie);
					ip = ie;
					op = oe;
				पूर्ण अन्यथा
#पूर्ण_अगर
				अणु
					NEED_OP(t);
					NEED_IP(t + 3);
					करो अणु
						*op++ = *ip++;
					पूर्ण जबतक (--t > 0);
				पूर्ण
				state = 4;
				जारी;
			पूर्ण अन्यथा अगर (state != 4) अणु
				next = t & 3;
				m_pos = op - 1;
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				TEST_LB(m_pos);
				NEED_OP(2);
				op[0] = m_pos[0];
				op[1] = m_pos[1];
				op += 2;
				जाओ match_next;
			पूर्ण अन्यथा अणु
				next = t & 3;
				m_pos = op - (1 + M2_MAX_OFFSET);
				m_pos -= t >> 2;
				m_pos -= *ip++ << 2;
				t = 3;
			पूर्ण
		पूर्ण अन्यथा अगर (t >= 64) अणु
			next = t & 3;
			m_pos = op - 1;
			m_pos -= (t >> 2) & 7;
			m_pos -= *ip++ << 3;
			t = (t >> 5) - 1 + (3 - 1);
		पूर्ण अन्यथा अगर (t >= 32) अणु
			t = (t & 31) + (3 - 1);
			अगर (unlikely(t == 2)) अणु
				माप_प्रकार offset;
				स्थिर अचिन्हित अक्षर *ip_last = ip;

				जबतक (unlikely(*ip == 0)) अणु
					ip++;
					NEED_IP(1);
				पूर्ण
				offset = ip - ip_last;
				अगर (unlikely(offset > MAX_255_COUNT))
					वापस LZO_E_ERROR;

				offset = (offset << 8) - offset;
				t += offset + 31 + *ip++;
				NEED_IP(2);
			पूर्ण
			m_pos = op - 1;
			next = get_unaligned_le16(ip);
			ip += 2;
			m_pos -= next >> 2;
			next &= 3;
		पूर्ण अन्यथा अणु
			NEED_IP(2);
			next = get_unaligned_le16(ip);
			अगर (((next & 0xfffc) == 0xfffc) &&
			    ((t & 0xf8) == 0x18) &&
			    likely(bitstream_version)) अणु
				NEED_IP(3);
				t &= 7;
				t |= ip[2] << 3;
				t += MIN_ZERO_RUN_LENGTH;
				NEED_OP(t);
				स_रखो(op, 0, t);
				op += t;
				next &= 3;
				ip += 3;
				जाओ match_next;
			पूर्ण अन्यथा अणु
				m_pos = op;
				m_pos -= (t & 8) << 11;
				t = (t & 7) + (3 - 1);
				अगर (unlikely(t == 2)) अणु
					माप_प्रकार offset;
					स्थिर अचिन्हित अक्षर *ip_last = ip;

					जबतक (unlikely(*ip == 0)) अणु
						ip++;
						NEED_IP(1);
					पूर्ण
					offset = ip - ip_last;
					अगर (unlikely(offset > MAX_255_COUNT))
						वापस LZO_E_ERROR;

					offset = (offset << 8) - offset;
					t += offset + 7 + *ip++;
					NEED_IP(2);
					next = get_unaligned_le16(ip);
				पूर्ण
				ip += 2;
				m_pos -= next >> 2;
				next &= 3;
				अगर (m_pos == op)
					जाओ eof_found;
				m_pos -= 0x4000;
			पूर्ण
		पूर्ण
		TEST_LB(m_pos);
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
		अगर (op - m_pos >= 8) अणु
			अचिन्हित अक्षर *oe = op + t;
			अगर (likely(HAVE_OP(t + 15))) अणु
				करो अणु
					COPY8(op, m_pos);
					op += 8;
					m_pos += 8;
					COPY8(op, m_pos);
					op += 8;
					m_pos += 8;
				पूर्ण जबतक (op < oe);
				op = oe;
				अगर (HAVE_IP(6)) अणु
					state = next;
					COPY4(op, ip);
					op += next;
					ip += next;
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				NEED_OP(t);
				करो अणु
					*op++ = *m_pos++;
				पूर्ण जबतक (op < oe);
			पूर्ण
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			अचिन्हित अक्षर *oe = op + t;
			NEED_OP(t);
			op[0] = m_pos[0];
			op[1] = m_pos[1];
			op += 2;
			m_pos += 2;
			करो अणु
				*op++ = *m_pos++;
			पूर्ण जबतक (op < oe);
		पूर्ण
match_next:
		state = next;
		t = next;
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
		अगर (likely(HAVE_IP(6) && HAVE_OP(4))) अणु
			COPY4(op, ip);
			op += t;
			ip += t;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			NEED_IP(t + 3);
			NEED_OP(t);
			जबतक (t > 0) अणु
				*op++ = *ip++;
				t--;
			पूर्ण
		पूर्ण
	पूर्ण

eof_found:
	*out_len = op - out;
	वापस (t != 3       ? LZO_E_ERROR :
		ip == ip_end ? LZO_E_OK :
		ip <  ip_end ? LZO_E_INPUT_NOT_CONSUMED : LZO_E_INPUT_OVERRUN);

input_overrun:
	*out_len = op - out;
	वापस LZO_E_INPUT_OVERRUN;

output_overrun:
	*out_len = op - out;
	वापस LZO_E_OUTPUT_OVERRUN;

lookbehind_overrun:
	*out_len = op - out;
	वापस LZO_E_LOOKBEHIND_OVERRUN;
पूर्ण
#अगर_अघोषित STATIC
EXPORT_SYMBOL_GPL(lzo1x_decompress_safe);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LZO1X Decompressor");

#पूर्ण_अगर
