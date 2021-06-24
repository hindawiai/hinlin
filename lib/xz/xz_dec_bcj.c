<शैली गुरु>
/*
 * Branch/Call/Jump (BCJ) filter decoders
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <https://7-zip.org/>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#समावेश "xz_private.h"

/*
 * The rest of the file is inside this अगरdef. It makes things a little more
 * convenient when building without support क्रम any BCJ filters.
 */
#अगर_घोषित XZ_DEC_BCJ

काष्ठा xz_dec_bcj अणु
	/* Type of the BCJ filter being used */
	क्रमागत अणु
		BCJ_X86 = 4,        /* x86 or x86-64 */
		BCJ_POWERPC = 5,    /* Big endian only */
		BCJ_IA64 = 6,       /* Big or little endian */
		BCJ_ARM = 7,        /* Little endian only */
		BCJ_ARMTHUMB = 8,   /* Little endian only */
		BCJ_SPARC = 9       /* Big or little endian */
	पूर्ण type;

	/*
	 * Return value of the next filter in the chain. We need to preserve
	 * this inक्रमmation across calls, because we must not call the next
	 * filter anymore once it has वापसed XZ_STREAM_END.
	 */
	क्रमागत xz_ret ret;

	/* True अगर we are operating in single-call mode. */
	bool single_call;

	/*
	 * Absolute position relative to the beginning of the uncompressed
	 * data (in a single .xz Block). We care only about the lowest 32
	 * bits so this करोesn't need to be uपूर्णांक64_t even with big files.
	 */
	uपूर्णांक32_t pos;

	/* x86 filter state */
	uपूर्णांक32_t x86_prev_mask;

	/* Temporary space to hold the variables from काष्ठा xz_buf */
	uपूर्णांक8_t *out;
	माप_प्रकार out_pos;
	माप_प्रकार out_size;

	काष्ठा अणु
		/* Amount of alपढ़ोy filtered data in the beginning of buf */
		माप_प्रकार filtered;

		/* Total amount of data currently stored in buf  */
		माप_प्रकार size;

		/*
		 * Buffer to hold a mix of filtered and unfiltered data. This
		 * needs to be big enough to hold Alignment + 2 * Look-ahead:
		 *
		 * Type         Alignment   Look-ahead
		 * x86              1           4
		 * PowerPC          4           0
		 * IA-64           16           0
		 * ARM              4           0
		 * ARM-Thumb        2           2
		 * SPARC            4           0
		 */
		uपूर्णांक8_t buf[16];
	पूर्ण temp;
पूर्ण;

#अगर_घोषित XZ_DEC_X86
/*
 * This is used to test the most signअगरicant byte of a memory address
 * in an x86 inकाष्ठाion.
 */
अटल अंतरभूत पूर्णांक bcj_x86_test_msbyte(uपूर्णांक8_t b)
अणु
	वापस b == 0x00 || b == 0xFF;
पूर्ण

अटल माप_प्रकार bcj_x86(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	अटल स्थिर bool mask_to_allowed_status[8]
		= अणु true, true, true, false, true, false, false, false पूर्ण;

	अटल स्थिर uपूर्णांक8_t mask_to_bit_num[8] = अणु 0, 1, 2, 2, 3, 3, 3, 3 पूर्ण;

	माप_प्रकार i;
	माप_प्रकार prev_pos = (माप_प्रकार)-1;
	uपूर्णांक32_t prev_mask = s->x86_prev_mask;
	uपूर्णांक32_t src;
	uपूर्णांक32_t dest;
	uपूर्णांक32_t j;
	uपूर्णांक8_t b;

	अगर (size <= 4)
		वापस 0;

	size -= 4;
	क्रम (i = 0; i < size; ++i) अणु
		अगर ((buf[i] & 0xFE) != 0xE8)
			जारी;

		prev_pos = i - prev_pos;
		अगर (prev_pos > 3) अणु
			prev_mask = 0;
		पूर्ण अन्यथा अणु
			prev_mask = (prev_mask << (prev_pos - 1)) & 7;
			अगर (prev_mask != 0) अणु
				b = buf[i + 4 - mask_to_bit_num[prev_mask]];
				अगर (!mask_to_allowed_status[prev_mask]
						|| bcj_x86_test_msbyte(b)) अणु
					prev_pos = i;
					prev_mask = (prev_mask << 1) | 1;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		prev_pos = i;

		अगर (bcj_x86_test_msbyte(buf[i + 4])) अणु
			src = get_unaligned_le32(buf + i + 1);
			जबतक (true) अणु
				dest = src - (s->pos + (uपूर्णांक32_t)i + 5);
				अगर (prev_mask == 0)
					अवरोध;

				j = mask_to_bit_num[prev_mask] * 8;
				b = (uपूर्णांक8_t)(dest >> (24 - j));
				अगर (!bcj_x86_test_msbyte(b))
					अवरोध;

				src = dest ^ (((uपूर्णांक32_t)1 << (32 - j)) - 1);
			पूर्ण

			dest &= 0x01FFFFFF;
			dest |= (uपूर्णांक32_t)0 - (dest & 0x01000000);
			put_unaligned_le32(dest, buf + i + 1);
			i += 4;
		पूर्ण अन्यथा अणु
			prev_mask = (prev_mask << 1) | 1;
		पूर्ण
	पूर्ण

	prev_pos = i - prev_pos;
	s->x86_prev_mask = prev_pos > 3 ? 0 : prev_mask << (prev_pos - 1);
	वापस i;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_POWERPC
अटल माप_प्रकार bcj_घातerpc(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	माप_प्रकार i;
	uपूर्णांक32_t instr;

	क्रम (i = 0; i + 4 <= size; i += 4) अणु
		instr = get_unaligned_be32(buf + i);
		अगर ((instr & 0xFC000003) == 0x48000001) अणु
			instr &= 0x03FFFFFC;
			instr -= s->pos + (uपूर्णांक32_t)i;
			instr &= 0x03FFFFFC;
			instr |= 0x48000001;
			put_unaligned_be32(instr, buf + i);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_IA64
अटल माप_प्रकार bcj_ia64(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	अटल स्थिर uपूर्णांक8_t branch_table[32] = अणु
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		4, 4, 6, 6, 0, 0, 7, 7,
		4, 4, 0, 0, 4, 4, 0, 0
	पूर्ण;

	/*
	 * The local variables take a little bit stack space, but it's less
	 * than what LZMA2 decoder takes, so it करोesn't make sense to reduce
	 * stack usage here without करोing that क्रम the LZMA2 decoder too.
	 */

	/* Loop counters */
	माप_प्रकार i;
	माप_प्रकार j;

	/* Inकाष्ठाion slot (0, 1, or 2) in the 128-bit inकाष्ठाion word */
	uपूर्णांक32_t slot;

	/* Bitwise offset of the inकाष्ठाion indicated by slot */
	uपूर्णांक32_t bit_pos;

	/* bit_pos split पूर्णांकo byte and bit parts */
	uपूर्णांक32_t byte_pos;
	uपूर्णांक32_t bit_res;

	/* Address part of an inकाष्ठाion */
	uपूर्णांक32_t addr;

	/* Mask used to detect which inकाष्ठाions to convert */
	uपूर्णांक32_t mask;

	/* 41-bit inकाष्ठाion stored somewhere in the lowest 48 bits */
	uपूर्णांक64_t instr;

	/* Inकाष्ठाion normalized with bit_res क्रम easier manipulation */
	uपूर्णांक64_t norm;

	क्रम (i = 0; i + 16 <= size; i += 16) अणु
		mask = branch_table[buf[i] & 0x1F];
		क्रम (slot = 0, bit_pos = 5; slot < 3; ++slot, bit_pos += 41) अणु
			अगर (((mask >> slot) & 1) == 0)
				जारी;

			byte_pos = bit_pos >> 3;
			bit_res = bit_pos & 7;
			instr = 0;
			क्रम (j = 0; j < 6; ++j)
				instr |= (uपूर्णांक64_t)(buf[i + j + byte_pos])
						<< (8 * j);

			norm = instr >> bit_res;

			अगर (((norm >> 37) & 0x0F) == 0x05
					&& ((norm >> 9) & 0x07) == 0) अणु
				addr = (norm >> 13) & 0x0FFFFF;
				addr |= ((uपूर्णांक32_t)(norm >> 36) & 1) << 20;
				addr <<= 4;
				addr -= s->pos + (uपूर्णांक32_t)i;
				addr >>= 4;

				norm &= ~((uपूर्णांक64_t)0x8FFFFF << 13);
				norm |= (uपूर्णांक64_t)(addr & 0x0FFFFF) << 13;
				norm |= (uपूर्णांक64_t)(addr & 0x100000)
						<< (36 - 20);

				instr &= (1 << bit_res) - 1;
				instr |= norm << bit_res;

				क्रम (j = 0; j < 6; j++)
					buf[i + j + byte_pos]
						= (uपूर्णांक8_t)(instr >> (8 * j));
			पूर्ण
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_ARM
अटल माप_प्रकार bcj_arm(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	माप_प्रकार i;
	uपूर्णांक32_t addr;

	क्रम (i = 0; i + 4 <= size; i += 4) अणु
		अगर (buf[i + 3] == 0xEB) अणु
			addr = (uपूर्णांक32_t)buf[i] | ((uपूर्णांक32_t)buf[i + 1] << 8)
					| ((uपूर्णांक32_t)buf[i + 2] << 16);
			addr <<= 2;
			addr -= s->pos + (uपूर्णांक32_t)i + 8;
			addr >>= 2;
			buf[i] = (uपूर्णांक8_t)addr;
			buf[i + 1] = (uपूर्णांक8_t)(addr >> 8);
			buf[i + 2] = (uपूर्णांक8_t)(addr >> 16);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_ARMTHUMB
अटल माप_प्रकार bcj_armthumb(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	माप_प्रकार i;
	uपूर्णांक32_t addr;

	क्रम (i = 0; i + 4 <= size; i += 2) अणु
		अगर ((buf[i + 1] & 0xF8) == 0xF0
				&& (buf[i + 3] & 0xF8) == 0xF8) अणु
			addr = (((uपूर्णांक32_t)buf[i + 1] & 0x07) << 19)
					| ((uपूर्णांक32_t)buf[i] << 11)
					| (((uपूर्णांक32_t)buf[i + 3] & 0x07) << 8)
					| (uपूर्णांक32_t)buf[i + 2];
			addr <<= 1;
			addr -= s->pos + (uपूर्णांक32_t)i + 4;
			addr >>= 1;
			buf[i + 1] = (uपूर्णांक8_t)(0xF0 | ((addr >> 19) & 0x07));
			buf[i] = (uपूर्णांक8_t)(addr >> 11);
			buf[i + 3] = (uपूर्णांक8_t)(0xF8 | ((addr >> 8) & 0x07));
			buf[i + 2] = (uपूर्णांक8_t)addr;
			i += 2;
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_SPARC
अटल माप_प्रकार bcj_sparc(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	माप_प्रकार i;
	uपूर्णांक32_t instr;

	क्रम (i = 0; i + 4 <= size; i += 4) अणु
		instr = get_unaligned_be32(buf + i);
		अगर ((instr >> 22) == 0x100 || (instr >> 22) == 0x1FF) अणु
			instr <<= 2;
			instr -= s->pos + (uपूर्णांक32_t)i;
			instr >>= 2;
			instr = ((uपूर्णांक32_t)0x40000000 - (instr & 0x400000))
					| 0x40000000 | (instr & 0x3FFFFF);
			put_unaligned_be32(instr, buf + i);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

/*
 * Apply the selected BCJ filter. Update *pos and s->pos to match the amount
 * of data that got filtered.
 *
 * NOTE: This is implemented as a चयन statement to aव्योम using function
 * poपूर्णांकers, which could be problematic in the kernel boot code, which must
 * aव्योम poपूर्णांकers to अटल data (at least on x86).
 */
अटल व्योम bcj_apply(काष्ठा xz_dec_bcj *s,
		      uपूर्णांक8_t *buf, माप_प्रकार *pos, माप_प्रकार size)
अणु
	माप_प्रकार filtered;

	buf += *pos;
	size -= *pos;

	चयन (s->type) अणु
#अगर_घोषित XZ_DEC_X86
	हाल BCJ_X86:
		filtered = bcj_x86(s, buf, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_POWERPC
	हाल BCJ_POWERPC:
		filtered = bcj_घातerpc(s, buf, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_IA64
	हाल BCJ_IA64:
		filtered = bcj_ia64(s, buf, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_ARM
	हाल BCJ_ARM:
		filtered = bcj_arm(s, buf, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_ARMTHUMB
	हाल BCJ_ARMTHUMB:
		filtered = bcj_armthumb(s, buf, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_SPARC
	हाल BCJ_SPARC:
		filtered = bcj_sparc(s, buf, size);
		अवरोध;
#पूर्ण_अगर
	शेष:
		/* Never reached but silence compiler warnings. */
		filtered = 0;
		अवरोध;
	पूर्ण

	*pos += filtered;
	s->pos += filtered;
पूर्ण

/*
 * Flush pending filtered data from temp to the output buffer.
 * Move the reमुख्यing mixture of possibly filtered and unfiltered
 * data to the beginning of temp.
 */
अटल व्योम bcj_flush(काष्ठा xz_dec_bcj *s, काष्ठा xz_buf *b)
अणु
	माप_प्रकार copy_size;

	copy_size = min_t(माप_प्रकार, s->temp.filtered, b->out_size - b->out_pos);
	स_नकल(b->out + b->out_pos, s->temp.buf, copy_size);
	b->out_pos += copy_size;

	s->temp.filtered -= copy_size;
	s->temp.size -= copy_size;
	स_हटाओ(s->temp.buf, s->temp.buf + copy_size, s->temp.size);
पूर्ण

/*
 * The BCJ filter functions are primitive in sense that they process the
 * data in chunks of 1-16 bytes. To hide this issue, this function करोes
 * some buffering.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_bcj_run(काष्ठा xz_dec_bcj *s,
				     काष्ठा xz_dec_lzma2 *lzma2,
				     काष्ठा xz_buf *b)
अणु
	माप_प्रकार out_start;

	/*
	 * Flush pending alपढ़ोy filtered data to the output buffer. Return
	 * immediatelly अगर we couldn't flush everything, or अगर the next
	 * filter in the chain had alपढ़ोy वापसed XZ_STREAM_END.
	 */
	अगर (s->temp.filtered > 0) अणु
		bcj_flush(s, b);
		अगर (s->temp.filtered > 0)
			वापस XZ_OK;

		अगर (s->ret == XZ_STREAM_END)
			वापस XZ_STREAM_END;
	पूर्ण

	/*
	 * If we have more output space than what is currently pending in
	 * temp, copy the unfiltered data from temp to the output buffer
	 * and try to fill the output buffer by decoding more data from the
	 * next filter in the chain. Apply the BCJ filter on the new data
	 * in the output buffer. If everything cannot be filtered, copy it
	 * to temp and शुरुआत the output buffer position accordingly.
	 *
	 * This needs to be always run when temp.size == 0 to handle a special
	 * हाल where the output buffer is full and the next filter has no
	 * more output coming but hasn't वापसed XZ_STREAM_END yet.
	 */
	अगर (s->temp.size < b->out_size - b->out_pos || s->temp.size == 0) अणु
		out_start = b->out_pos;
		स_नकल(b->out + b->out_pos, s->temp.buf, s->temp.size);
		b->out_pos += s->temp.size;

		s->ret = xz_dec_lzma2_run(lzma2, b);
		अगर (s->ret != XZ_STREAM_END
				&& (s->ret != XZ_OK || s->single_call))
			वापस s->ret;

		bcj_apply(s, b->out, &out_start, b->out_pos);

		/*
		 * As an exception, अगर the next filter वापसed XZ_STREAM_END,
		 * we can करो that too, since the last few bytes that reमुख्य
		 * unfiltered are meant to reमुख्य unfiltered.
		 */
		अगर (s->ret == XZ_STREAM_END)
			वापस XZ_STREAM_END;

		s->temp.size = b->out_pos - out_start;
		b->out_pos -= s->temp.size;
		स_नकल(s->temp.buf, b->out + b->out_pos, s->temp.size);

		/*
		 * If there wasn't enough input to the next filter to fill
		 * the output buffer with unfiltered data, there's no poपूर्णांक
		 * to try decoding more data to temp.
		 */
		अगर (b->out_pos + s->temp.size < b->out_size)
			वापस XZ_OK;
	पूर्ण

	/*
	 * We have unfiltered data in temp. If the output buffer isn't full
	 * yet, try to fill the temp buffer by decoding more data from the
	 * next filter. Apply the BCJ filter on temp. Then we hopefully can
	 * fill the actual output buffer by copying filtered data from temp.
	 * A mix of filtered and unfiltered data may be left in temp; it will
	 * be taken care on the next call to this function.
	 */
	अगर (b->out_pos < b->out_size) अणु
		/* Make b->outअणु,_pos,_sizeपूर्ण temporarily poपूर्णांक to s->temp. */
		s->out = b->out;
		s->out_pos = b->out_pos;
		s->out_size = b->out_size;
		b->out = s->temp.buf;
		b->out_pos = s->temp.size;
		b->out_size = माप(s->temp.buf);

		s->ret = xz_dec_lzma2_run(lzma2, b);

		s->temp.size = b->out_pos;
		b->out = s->out;
		b->out_pos = s->out_pos;
		b->out_size = s->out_size;

		अगर (s->ret != XZ_OK && s->ret != XZ_STREAM_END)
			वापस s->ret;

		bcj_apply(s, s->temp.buf, &s->temp.filtered, s->temp.size);

		/*
		 * If the next filter वापसed XZ_STREAM_END, we mark that
		 * everything is filtered, since the last unfiltered bytes
		 * of the stream are meant to be left as is.
		 */
		अगर (s->ret == XZ_STREAM_END)
			s->temp.filtered = s->temp.size;

		bcj_flush(s, b);
		अगर (s->temp.filtered > 0)
			वापस XZ_OK;
	पूर्ण

	वापस s->ret;
पूर्ण

XZ_EXTERN काष्ठा xz_dec_bcj *xz_dec_bcj_create(bool single_call)
अणु
	काष्ठा xz_dec_bcj *s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (s != शून्य)
		s->single_call = single_call;

	वापस s;
पूर्ण

XZ_EXTERN क्रमागत xz_ret xz_dec_bcj_reset(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t id)
अणु
	चयन (id) अणु
#अगर_घोषित XZ_DEC_X86
	हाल BCJ_X86:
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_POWERPC
	हाल BCJ_POWERPC:
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_IA64
	हाल BCJ_IA64:
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_ARM
	हाल BCJ_ARM:
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_ARMTHUMB
	हाल BCJ_ARMTHUMB:
#पूर्ण_अगर
#अगर_घोषित XZ_DEC_SPARC
	हाल BCJ_SPARC:
#पूर्ण_अगर
		अवरोध;

	शेष:
		/* Unsupported Filter ID */
		वापस XZ_OPTIONS_ERROR;
	पूर्ण

	s->type = id;
	s->ret = XZ_OK;
	s->pos = 0;
	s->x86_prev_mask = 0;
	s->temp.filtered = 0;
	s->temp.size = 0;

	वापस XZ_OK;
पूर्ण

#पूर्ण_अगर
