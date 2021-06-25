<शैली गुरु>
/*
 * .xz Stream decoder
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#समावेश "xz_private.h"
#समावेश "xz_stream.h"

/* Hash used to validate the Index field */
काष्ठा xz_dec_hash अणु
	vli_type unpadded;
	vli_type uncompressed;
	uपूर्णांक32_t crc32;
पूर्ण;

काष्ठा xz_dec अणु
	/* Position in dec_मुख्य() */
	क्रमागत अणु
		SEQ_STREAM_HEADER,
		SEQ_BLOCK_START,
		SEQ_BLOCK_HEADER,
		SEQ_BLOCK_UNCOMPRESS,
		SEQ_BLOCK_PADDING,
		SEQ_BLOCK_CHECK,
		SEQ_INDEX,
		SEQ_INDEX_PADDING,
		SEQ_INDEX_CRC32,
		SEQ_STREAM_FOOTER
	पूर्ण sequence;

	/* Position in variable-length पूर्णांकegers and Check fields */
	uपूर्णांक32_t pos;

	/* Variable-length पूर्णांकeger decoded by dec_vli() */
	vli_type vli;

	/* Saved in_pos and out_pos */
	माप_प्रकार in_start;
	माप_प्रकार out_start;

	/* CRC32 value in Block or Index */
	uपूर्णांक32_t crc32;

	/* Type of the पूर्णांकegrity check calculated from uncompressed data */
	क्रमागत xz_check check_type;

	/* Operation mode */
	क्रमागत xz_mode mode;

	/*
	 * True अगर the next call to xz_dec_run() is allowed to वापस
	 * XZ_BUF_ERROR.
	 */
	bool allow_buf_error;

	/* Inक्रमmation stored in Block Header */
	काष्ठा अणु
		/*
		 * Value stored in the Compressed Size field, or
		 * VLI_UNKNOWN अगर Compressed Size is not present.
		 */
		vli_type compressed;

		/*
		 * Value stored in the Uncompressed Size field, or
		 * VLI_UNKNOWN अगर Uncompressed Size is not present.
		 */
		vli_type uncompressed;

		/* Size of the Block Header field */
		uपूर्णांक32_t size;
	पूर्ण block_header;

	/* Inक्रमmation collected when decoding Blocks */
	काष्ठा अणु
		/* Observed compressed size of the current Block */
		vli_type compressed;

		/* Observed uncompressed size of the current Block */
		vli_type uncompressed;

		/* Number of Blocks decoded so far */
		vli_type count;

		/*
		 * Hash calculated from the Block sizes. This is used to
		 * validate the Index field.
		 */
		काष्ठा xz_dec_hash hash;
	पूर्ण block;

	/* Variables needed when verअगरying the Index field */
	काष्ठा अणु
		/* Position in dec_index() */
		क्रमागत अणु
			SEQ_INDEX_COUNT,
			SEQ_INDEX_UNPADDED,
			SEQ_INDEX_UNCOMPRESSED
		पूर्ण sequence;

		/* Size of the Index in bytes */
		vli_type size;

		/* Number of Records (matches block.count in valid files) */
		vli_type count;

		/*
		 * Hash calculated from the Records (matches block.hash in
		 * valid files).
		 */
		काष्ठा xz_dec_hash hash;
	पूर्ण index;

	/*
	 * Temporary buffer needed to hold Stream Header, Block Header,
	 * and Stream Footer. The Block Header is the biggest (1 KiB)
	 * so we reserve space according to that. buf[] has to be aligned
	 * to a multiple of four bytes; the माप_प्रकार variables beक्रमe it
	 * should guarantee this.
	 */
	काष्ठा अणु
		माप_प्रकार pos;
		माप_प्रकार size;
		uपूर्णांक8_t buf[1024];
	पूर्ण temp;

	काष्ठा xz_dec_lzma2 *lzma2;

#अगर_घोषित XZ_DEC_BCJ
	काष्ठा xz_dec_bcj *bcj;
	bool bcj_active;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित XZ_DEC_ANY_CHECK
/* Sizes of the Check field with dअगरferent Check IDs */
अटल स्थिर uपूर्णांक8_t check_sizes[16] = अणु
	0,
	4, 4, 4,
	8, 8, 8,
	16, 16, 16,
	32, 32, 32,
	64, 64, 64
पूर्ण;
#पूर्ण_अगर

/*
 * Fill s->temp by copying data starting from b->in[b->in_pos]. Caller
 * must have set s->temp.pos to indicate how much data we are supposed
 * to copy पूर्णांकo s->temp.buf. Return true once s->temp.pos has reached
 * s->temp.size.
 */
अटल bool fill_temp(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	माप_प्रकार copy_size = min_t(माप_प्रकार,
			b->in_size - b->in_pos, s->temp.size - s->temp.pos);

	स_नकल(s->temp.buf + s->temp.pos, b->in + b->in_pos, copy_size);
	b->in_pos += copy_size;
	s->temp.pos += copy_size;

	अगर (s->temp.pos == s->temp.size) अणु
		s->temp.pos = 0;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Decode a variable-length पूर्णांकeger (little-endian base-128 encoding) */
अटल क्रमागत xz_ret dec_vli(काष्ठा xz_dec *s, स्थिर uपूर्णांक8_t *in,
			   माप_प्रकार *in_pos, माप_प्रकार in_size)
अणु
	uपूर्णांक8_t byte;

	अगर (s->pos == 0)
		s->vli = 0;

	जबतक (*in_pos < in_size) अणु
		byte = in[*in_pos];
		++*in_pos;

		s->vli |= (vli_type)(byte & 0x7F) << s->pos;

		अगर ((byte & 0x80) == 0) अणु
			/* Don't allow non-minimal encodings. */
			अगर (byte == 0 && s->pos != 0)
				वापस XZ_DATA_ERROR;

			s->pos = 0;
			वापस XZ_STREAM_END;
		पूर्ण

		s->pos += 7;
		अगर (s->pos == 7 * VLI_BYTES_MAX)
			वापस XZ_DATA_ERROR;
	पूर्ण

	वापस XZ_OK;
पूर्ण

/*
 * Decode the Compressed Data field from a Block. Update and validate
 * the observed compressed and uncompressed sizes of the Block so that
 * they करोn't exceed the values possibly stored in the Block Header
 * (validation assumes that no पूर्णांकeger overflow occurs, since vli_type
 * is normally uपूर्णांक64_t). Update the CRC32 अगर presence of the CRC32
 * field was indicated in Stream Header.
 *
 * Once the decoding is finished, validate that the observed sizes match
 * the sizes possibly stored in the Block Header. Update the hash and
 * Block count, which are later used to validate the Index field.
 */
अटल क्रमागत xz_ret dec_block(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	क्रमागत xz_ret ret;

	s->in_start = b->in_pos;
	s->out_start = b->out_pos;

#अगर_घोषित XZ_DEC_BCJ
	अगर (s->bcj_active)
		ret = xz_dec_bcj_run(s->bcj, s->lzma2, b);
	अन्यथा
#पूर्ण_अगर
		ret = xz_dec_lzma2_run(s->lzma2, b);

	s->block.compressed += b->in_pos - s->in_start;
	s->block.uncompressed += b->out_pos - s->out_start;

	/*
	 * There is no need to separately check क्रम VLI_UNKNOWN, since
	 * the observed sizes are always smaller than VLI_UNKNOWN.
	 */
	अगर (s->block.compressed > s->block_header.compressed
			|| s->block.uncompressed
				> s->block_header.uncompressed)
		वापस XZ_DATA_ERROR;

	अगर (s->check_type == XZ_CHECK_CRC32)
		s->crc32 = xz_crc32(b->out + s->out_start,
				b->out_pos - s->out_start, s->crc32);

	अगर (ret == XZ_STREAM_END) अणु
		अगर (s->block_header.compressed != VLI_UNKNOWN
				&& s->block_header.compressed
					!= s->block.compressed)
			वापस XZ_DATA_ERROR;

		अगर (s->block_header.uncompressed != VLI_UNKNOWN
				&& s->block_header.uncompressed
					!= s->block.uncompressed)
			वापस XZ_DATA_ERROR;

		s->block.hash.unpadded += s->block_header.size
				+ s->block.compressed;

#अगर_घोषित XZ_DEC_ANY_CHECK
		s->block.hash.unpadded += check_sizes[s->check_type];
#अन्यथा
		अगर (s->check_type == XZ_CHECK_CRC32)
			s->block.hash.unpadded += 4;
#पूर्ण_अगर

		s->block.hash.uncompressed += s->block.uncompressed;
		s->block.hash.crc32 = xz_crc32(
				(स्थिर uपूर्णांक8_t *)&s->block.hash,
				माप(s->block.hash), s->block.hash.crc32);

		++s->block.count;
	पूर्ण

	वापस ret;
पूर्ण

/* Update the Index size and the CRC32 value. */
अटल व्योम index_update(काष्ठा xz_dec *s, स्थिर काष्ठा xz_buf *b)
अणु
	माप_प्रकार in_used = b->in_pos - s->in_start;
	s->index.size += in_used;
	s->crc32 = xz_crc32(b->in + s->in_start, in_used, s->crc32);
पूर्ण

/*
 * Decode the Number of Records, Unpadded Size, and Uncompressed Size
 * fields from the Index field. That is, Index Padding and CRC32 are not
 * decoded by this function.
 *
 * This can वापस XZ_OK (more input needed), XZ_STREAM_END (everything
 * successfully decoded), or XZ_DATA_ERROR (input is corrupt).
 */
अटल क्रमागत xz_ret dec_index(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	क्रमागत xz_ret ret;

	करो अणु
		ret = dec_vli(s, b->in, &b->in_pos, b->in_size);
		अगर (ret != XZ_STREAM_END) अणु
			index_update(s, b);
			वापस ret;
		पूर्ण

		चयन (s->index.sequence) अणु
		हाल SEQ_INDEX_COUNT:
			s->index.count = s->vli;

			/*
			 * Validate that the Number of Records field
			 * indicates the same number of Records as
			 * there were Blocks in the Stream.
			 */
			अगर (s->index.count != s->block.count)
				वापस XZ_DATA_ERROR;

			s->index.sequence = SEQ_INDEX_UNPADDED;
			अवरोध;

		हाल SEQ_INDEX_UNPADDED:
			s->index.hash.unpadded += s->vli;
			s->index.sequence = SEQ_INDEX_UNCOMPRESSED;
			अवरोध;

		हाल SEQ_INDEX_UNCOMPRESSED:
			s->index.hash.uncompressed += s->vli;
			s->index.hash.crc32 = xz_crc32(
					(स्थिर uपूर्णांक8_t *)&s->index.hash,
					माप(s->index.hash),
					s->index.hash.crc32);
			--s->index.count;
			s->index.sequence = SEQ_INDEX_UNPADDED;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (s->index.count > 0);

	वापस XZ_STREAM_END;
पूर्ण

/*
 * Validate that the next four input bytes match the value of s->crc32.
 * s->pos must be zero when starting to validate the first byte.
 */
अटल क्रमागत xz_ret crc32_validate(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	करो अणु
		अगर (b->in_pos == b->in_size)
			वापस XZ_OK;

		अगर (((s->crc32 >> s->pos) & 0xFF) != b->in[b->in_pos++])
			वापस XZ_DATA_ERROR;

		s->pos += 8;

	पूर्ण जबतक (s->pos < 32);

	s->crc32 = 0;
	s->pos = 0;

	वापस XZ_STREAM_END;
पूर्ण

#अगर_घोषित XZ_DEC_ANY_CHECK
/*
 * Skip over the Check field when the Check ID is not supported.
 * Returns true once the whole Check field has been skipped over.
 */
अटल bool check_skip(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	जबतक (s->pos < check_sizes[s->check_type]) अणु
		अगर (b->in_pos == b->in_size)
			वापस false;

		++b->in_pos;
		++s->pos;
	पूर्ण

	s->pos = 0;

	वापस true;
पूर्ण
#पूर्ण_अगर

/* Decode the Stream Header field (the first 12 bytes of the .xz Stream). */
अटल क्रमागत xz_ret dec_stream_header(काष्ठा xz_dec *s)
अणु
	अगर (!memeq(s->temp.buf, HEADER_MAGIC, HEADER_MAGIC_SIZE))
		वापस XZ_FORMAT_ERROR;

	अगर (xz_crc32(s->temp.buf + HEADER_MAGIC_SIZE, 2, 0)
			!= get_le32(s->temp.buf + HEADER_MAGIC_SIZE + 2))
		वापस XZ_DATA_ERROR;

	अगर (s->temp.buf[HEADER_MAGIC_SIZE] != 0)
		वापस XZ_OPTIONS_ERROR;

	/*
	 * Of पूर्णांकegrity checks, we support only none (Check ID = 0) and
	 * CRC32 (Check ID = 1). However, अगर XZ_DEC_ANY_CHECK is defined,
	 * we will accept other check types too, but then the check won't
	 * be verअगरied and a warning (XZ_UNSUPPORTED_CHECK) will be given.
	 */
	s->check_type = s->temp.buf[HEADER_MAGIC_SIZE + 1];

#अगर_घोषित XZ_DEC_ANY_CHECK
	अगर (s->check_type > XZ_CHECK_MAX)
		वापस XZ_OPTIONS_ERROR;

	अगर (s->check_type > XZ_CHECK_CRC32)
		वापस XZ_UNSUPPORTED_CHECK;
#अन्यथा
	अगर (s->check_type > XZ_CHECK_CRC32)
		वापस XZ_OPTIONS_ERROR;
#पूर्ण_अगर

	वापस XZ_OK;
पूर्ण

/* Decode the Stream Footer field (the last 12 bytes of the .xz Stream) */
अटल क्रमागत xz_ret dec_stream_footer(काष्ठा xz_dec *s)
अणु
	अगर (!memeq(s->temp.buf + 10, FOOTER_MAGIC, FOOTER_MAGIC_SIZE))
		वापस XZ_DATA_ERROR;

	अगर (xz_crc32(s->temp.buf + 4, 6, 0) != get_le32(s->temp.buf))
		वापस XZ_DATA_ERROR;

	/*
	 * Validate Backward Size. Note that we never added the size of the
	 * Index CRC32 field to s->index.size, thus we use s->index.size / 4
	 * instead of s->index.size / 4 - 1.
	 */
	अगर ((s->index.size >> 2) != get_le32(s->temp.buf + 4))
		वापस XZ_DATA_ERROR;

	अगर (s->temp.buf[8] != 0 || s->temp.buf[9] != s->check_type)
		वापस XZ_DATA_ERROR;

	/*
	 * Use XZ_STREAM_END instead of XZ_OK to be more convenient
	 * क्रम the caller.
	 */
	वापस XZ_STREAM_END;
पूर्ण

/* Decode the Block Header and initialize the filter chain. */
अटल क्रमागत xz_ret dec_block_header(काष्ठा xz_dec *s)
अणु
	क्रमागत xz_ret ret;

	/*
	 * Validate the CRC32. We know that the temp buffer is at least
	 * eight bytes so this is safe.
	 */
	s->temp.size -= 4;
	अगर (xz_crc32(s->temp.buf, s->temp.size, 0)
			!= get_le32(s->temp.buf + s->temp.size))
		वापस XZ_DATA_ERROR;

	s->temp.pos = 2;

	/*
	 * Catch unsupported Block Flags. We support only one or two filters
	 * in the chain, so we catch that with the same test.
	 */
#अगर_घोषित XZ_DEC_BCJ
	अगर (s->temp.buf[1] & 0x3E)
#अन्यथा
	अगर (s->temp.buf[1] & 0x3F)
#पूर्ण_अगर
		वापस XZ_OPTIONS_ERROR;

	/* Compressed Size */
	अगर (s->temp.buf[1] & 0x40) अणु
		अगर (dec_vli(s, s->temp.buf, &s->temp.pos, s->temp.size)
					!= XZ_STREAM_END)
			वापस XZ_DATA_ERROR;

		s->block_header.compressed = s->vli;
	पूर्ण अन्यथा अणु
		s->block_header.compressed = VLI_UNKNOWN;
	पूर्ण

	/* Uncompressed Size */
	अगर (s->temp.buf[1] & 0x80) अणु
		अगर (dec_vli(s, s->temp.buf, &s->temp.pos, s->temp.size)
				!= XZ_STREAM_END)
			वापस XZ_DATA_ERROR;

		s->block_header.uncompressed = s->vli;
	पूर्ण अन्यथा अणु
		s->block_header.uncompressed = VLI_UNKNOWN;
	पूर्ण

#अगर_घोषित XZ_DEC_BCJ
	/* If there are two filters, the first one must be a BCJ filter. */
	s->bcj_active = s->temp.buf[1] & 0x01;
	अगर (s->bcj_active) अणु
		अगर (s->temp.size - s->temp.pos < 2)
			वापस XZ_OPTIONS_ERROR;

		ret = xz_dec_bcj_reset(s->bcj, s->temp.buf[s->temp.pos++]);
		अगर (ret != XZ_OK)
			वापस ret;

		/*
		 * We करोn't support custom start offset,
		 * so Size of Properties must be zero.
		 */
		अगर (s->temp.buf[s->temp.pos++] != 0x00)
			वापस XZ_OPTIONS_ERROR;
	पूर्ण
#पूर्ण_अगर

	/* Valid Filter Flags always take at least two bytes. */
	अगर (s->temp.size - s->temp.pos < 2)
		वापस XZ_DATA_ERROR;

	/* Filter ID = LZMA2 */
	अगर (s->temp.buf[s->temp.pos++] != 0x21)
		वापस XZ_OPTIONS_ERROR;

	/* Size of Properties = 1-byte Filter Properties */
	अगर (s->temp.buf[s->temp.pos++] != 0x01)
		वापस XZ_OPTIONS_ERROR;

	/* Filter Properties contains LZMA2 dictionary size. */
	अगर (s->temp.size - s->temp.pos < 1)
		वापस XZ_DATA_ERROR;

	ret = xz_dec_lzma2_reset(s->lzma2, s->temp.buf[s->temp.pos++]);
	अगर (ret != XZ_OK)
		वापस ret;

	/* The rest must be Header Padding. */
	जबतक (s->temp.pos < s->temp.size)
		अगर (s->temp.buf[s->temp.pos++] != 0x00)
			वापस XZ_OPTIONS_ERROR;

	s->temp.pos = 0;
	s->block.compressed = 0;
	s->block.uncompressed = 0;

	वापस XZ_OK;
पूर्ण

अटल क्रमागत xz_ret dec_मुख्य(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	क्रमागत xz_ret ret;

	/*
	 * Store the start position क्रम the हाल when we are in the middle
	 * of the Index field.
	 */
	s->in_start = b->in_pos;

	जबतक (true) अणु
		चयन (s->sequence) अणु
		हाल SEQ_STREAM_HEADER:
			/*
			 * Stream Header is copied to s->temp, and then
			 * decoded from there. This way अगर the caller
			 * gives us only little input at a समय, we can
			 * still keep the Stream Header decoding code
			 * simple. Similar approach is used in many places
			 * in this file.
			 */
			अगर (!fill_temp(s, b))
				वापस XZ_OK;

			/*
			 * If dec_stream_header() वापसs
			 * XZ_UNSUPPORTED_CHECK, it is still possible
			 * to जारी decoding अगर working in multi-call
			 * mode. Thus, update s->sequence beक्रमe calling
			 * dec_stream_header().
			 */
			s->sequence = SEQ_BLOCK_START;

			ret = dec_stream_header(s);
			अगर (ret != XZ_OK)
				वापस ret;

			fallthrough;

		हाल SEQ_BLOCK_START:
			/* We need one byte of input to जारी. */
			अगर (b->in_pos == b->in_size)
				वापस XZ_OK;

			/* See अगर this is the beginning of the Index field. */
			अगर (b->in[b->in_pos] == 0) अणु
				s->in_start = b->in_pos++;
				s->sequence = SEQ_INDEX;
				अवरोध;
			पूर्ण

			/*
			 * Calculate the size of the Block Header and
			 * prepare to decode it.
			 */
			s->block_header.size
				= ((uपूर्णांक32_t)b->in[b->in_pos] + 1) * 4;

			s->temp.size = s->block_header.size;
			s->temp.pos = 0;
			s->sequence = SEQ_BLOCK_HEADER;

			fallthrough;

		हाल SEQ_BLOCK_HEADER:
			अगर (!fill_temp(s, b))
				वापस XZ_OK;

			ret = dec_block_header(s);
			अगर (ret != XZ_OK)
				वापस ret;

			s->sequence = SEQ_BLOCK_UNCOMPRESS;

			fallthrough;

		हाल SEQ_BLOCK_UNCOMPRESS:
			ret = dec_block(s, b);
			अगर (ret != XZ_STREAM_END)
				वापस ret;

			s->sequence = SEQ_BLOCK_PADDING;

			fallthrough;

		हाल SEQ_BLOCK_PADDING:
			/*
			 * Size of Compressed Data + Block Padding
			 * must be a multiple of four. We करोn't need
			 * s->block.compressed क्रम anything अन्यथा
			 * anymore, so we use it here to test the size
			 * of the Block Padding field.
			 */
			जबतक (s->block.compressed & 3) अणु
				अगर (b->in_pos == b->in_size)
					वापस XZ_OK;

				अगर (b->in[b->in_pos++] != 0)
					वापस XZ_DATA_ERROR;

				++s->block.compressed;
			पूर्ण

			s->sequence = SEQ_BLOCK_CHECK;

			fallthrough;

		हाल SEQ_BLOCK_CHECK:
			अगर (s->check_type == XZ_CHECK_CRC32) अणु
				ret = crc32_validate(s, b);
				अगर (ret != XZ_STREAM_END)
					वापस ret;
			पूर्ण
#अगर_घोषित XZ_DEC_ANY_CHECK
			अन्यथा अगर (!check_skip(s, b)) अणु
				वापस XZ_OK;
			पूर्ण
#पूर्ण_अगर

			s->sequence = SEQ_BLOCK_START;
			अवरोध;

		हाल SEQ_INDEX:
			ret = dec_index(s, b);
			अगर (ret != XZ_STREAM_END)
				वापस ret;

			s->sequence = SEQ_INDEX_PADDING;

			fallthrough;

		हाल SEQ_INDEX_PADDING:
			जबतक ((s->index.size + (b->in_pos - s->in_start))
					& 3) अणु
				अगर (b->in_pos == b->in_size) अणु
					index_update(s, b);
					वापस XZ_OK;
				पूर्ण

				अगर (b->in[b->in_pos++] != 0)
					वापस XZ_DATA_ERROR;
			पूर्ण

			/* Finish the CRC32 value and Index size. */
			index_update(s, b);

			/* Compare the hashes to validate the Index field. */
			अगर (!memeq(&s->block.hash, &s->index.hash,
					माप(s->block.hash)))
				वापस XZ_DATA_ERROR;

			s->sequence = SEQ_INDEX_CRC32;

			fallthrough;

		हाल SEQ_INDEX_CRC32:
			ret = crc32_validate(s, b);
			अगर (ret != XZ_STREAM_END)
				वापस ret;

			s->temp.size = STREAM_HEADER_SIZE;
			s->sequence = SEQ_STREAM_FOOTER;

			fallthrough;

		हाल SEQ_STREAM_FOOTER:
			अगर (!fill_temp(s, b))
				वापस XZ_OK;

			वापस dec_stream_footer(s);
		पूर्ण
	पूर्ण

	/* Never reached */
पूर्ण

/*
 * xz_dec_run() is a wrapper क्रम dec_मुख्य() to handle some special हालs in
 * multi-call and single-call decoding.
 *
 * In multi-call mode, we must वापस XZ_BUF_ERROR when it seems clear that we
 * are not going to make any progress anymore. This is to prevent the caller
 * from calling us infinitely when the input file is truncated or otherwise
 * corrupt. Since zlib-style API allows that the caller fills the input buffer
 * only when the decoder करोesn't produce any new output, we have to be careful
 * to aव्योम वापसing XZ_BUF_ERROR too easily: XZ_BUF_ERROR is वापसed only
 * after the second consecutive call to xz_dec_run() that makes no progress.
 *
 * In single-call mode, अगर we couldn't decode everything and no error
 * occurred, either the input is truncated or the output buffer is too small.
 * Since we know that the last input byte never produces any output, we know
 * that अगर all the input was consumed and decoding wasn't finished, the file
 * must be corrupt. Otherwise the output buffer has to be too small or the
 * file is corrupt in a way that decoding it produces too big output.
 *
 * If single-call decoding fails, we reset b->in_pos and b->out_pos back to
 * their original values. This is because with some filter chains there won't
 * be any valid uncompressed data in the output buffer unless the decoding
 * actually succeeds (that's the price to pay of using the output buffer as
 * the workspace).
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_run(काष्ठा xz_dec *s, काष्ठा xz_buf *b)
अणु
	माप_प्रकार in_start;
	माप_प्रकार out_start;
	क्रमागत xz_ret ret;

	अगर (DEC_IS_SINGLE(s->mode))
		xz_dec_reset(s);

	in_start = b->in_pos;
	out_start = b->out_pos;
	ret = dec_मुख्य(s, b);

	अगर (DEC_IS_SINGLE(s->mode)) अणु
		अगर (ret == XZ_OK)
			ret = b->in_pos == b->in_size
					? XZ_DATA_ERROR : XZ_BUF_ERROR;

		अगर (ret != XZ_STREAM_END) अणु
			b->in_pos = in_start;
			b->out_pos = out_start;
		पूर्ण

	पूर्ण अन्यथा अगर (ret == XZ_OK && in_start == b->in_pos
			&& out_start == b->out_pos) अणु
		अगर (s->allow_buf_error)
			ret = XZ_BUF_ERROR;

		s->allow_buf_error = true;
	पूर्ण अन्यथा अणु
		s->allow_buf_error = false;
	पूर्ण

	वापस ret;
पूर्ण

XZ_EXTERN काष्ठा xz_dec *xz_dec_init(क्रमागत xz_mode mode, uपूर्णांक32_t dict_max)
अणु
	काष्ठा xz_dec *s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (s == शून्य)
		वापस शून्य;

	s->mode = mode;

#अगर_घोषित XZ_DEC_BCJ
	s->bcj = xz_dec_bcj_create(DEC_IS_SINGLE(mode));
	अगर (s->bcj == शून्य)
		जाओ error_bcj;
#पूर्ण_अगर

	s->lzma2 = xz_dec_lzma2_create(mode, dict_max);
	अगर (s->lzma2 == शून्य)
		जाओ error_lzma2;

	xz_dec_reset(s);
	वापस s;

error_lzma2:
#अगर_घोषित XZ_DEC_BCJ
	xz_dec_bcj_end(s->bcj);
error_bcj:
#पूर्ण_अगर
	kमुक्त(s);
	वापस शून्य;
पूर्ण

XZ_EXTERN व्योम xz_dec_reset(काष्ठा xz_dec *s)
अणु
	s->sequence = SEQ_STREAM_HEADER;
	s->allow_buf_error = false;
	s->pos = 0;
	s->crc32 = 0;
	memzero(&s->block, माप(s->block));
	memzero(&s->index, माप(s->index));
	s->temp.pos = 0;
	s->temp.size = STREAM_HEADER_SIZE;
पूर्ण

XZ_EXTERN व्योम xz_dec_end(काष्ठा xz_dec *s)
अणु
	अगर (s != शून्य) अणु
		xz_dec_lzma2_end(s->lzma2);
#अगर_घोषित XZ_DEC_BCJ
		xz_dec_bcj_end(s->bcj);
#पूर्ण_अगर
		kमुक्त(s);
	पूर्ण
पूर्ण
