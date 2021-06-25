<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Google, Inc.
 *
 * Author: Sami Tolvanen <samitolvanen@google.com>
 */

#समावेश "dm-verity-fec.h"
#समावेश <linux/math64.h>

#घोषणा DM_MSG_PREFIX	"verity-fec"

/*
 * If error correction has been configured, वापसs true.
 */
bool verity_fec_is_enabled(काष्ठा dm_verity *v)
अणु
	वापस v->fec && v->fec->dev;
पूर्ण

/*
 * Return a poपूर्णांकer to dm_verity_fec_io after dm_verity_io and its variable
 * length fields.
 */
अटल अंतरभूत काष्ठा dm_verity_fec_io *fec_io(काष्ठा dm_verity_io *io)
अणु
	वापस (काष्ठा dm_verity_fec_io *) verity_io_digest_end(io->v, io);
पूर्ण

/*
 * Return an पूर्णांकerleaved offset क्रम a byte in RS block.
 */
अटल अंतरभूत u64 fec_पूर्णांकerleave(काष्ठा dm_verity *v, u64 offset)
अणु
	u32 mod;

	mod = करो_भाग(offset, v->fec->rsn);
	वापस offset + mod * (v->fec->rounds << v->data_dev_block_bits);
पूर्ण

/*
 * Decode an RS block using Reed-Solomon.
 */
अटल पूर्णांक fec_decode_rs8(काष्ठा dm_verity *v, काष्ठा dm_verity_fec_io *fio,
			  u8 *data, u8 *fec, पूर्णांक neras)
अणु
	पूर्णांक i;
	uपूर्णांक16_t par[DM_VERITY_FEC_RSM - DM_VERITY_FEC_MIN_RSN];

	क्रम (i = 0; i < v->fec->roots; i++)
		par[i] = fec[i];

	वापस decode_rs8(fio->rs, data, par, v->fec->rsn, शून्य, neras,
			  fio->erasures, 0, शून्य);
पूर्ण

/*
 * Read error-correcting codes क्रम the requested RS block. Returns a poपूर्णांकer
 * to the data block. Caller is responsible क्रम releasing buf.
 */
अटल u8 *fec_पढ़ो_parity(काष्ठा dm_verity *v, u64 rsb, पूर्णांक index,
			   अचिन्हित *offset, काष्ठा dm_buffer **buf)
अणु
	u64 position, block, rem;
	u8 *res;

	position = (index + rsb) * v->fec->roots;
	block = भाग64_u64_rem(position, v->fec->io_size, &rem);
	*offset = (अचिन्हित)rem;

	res = dm_bufio_पढ़ो(v->fec->bufio, block, buf);
	अगर (IS_ERR(res)) अणु
		DMERR("%s: FEC %llu: parity read failed (block %llu): %ld",
		      v->data_dev->name, (अचिन्हित दीर्घ दीर्घ)rsb,
		      (अचिन्हित दीर्घ दीर्घ)block, PTR_ERR(res));
		*buf = शून्य;
	पूर्ण

	वापस res;
पूर्ण

/* Loop over each pपुनः_स्मृतिated buffer slot. */
#घोषणा fec_क्रम_each_pपुनः_स्मृति_buffer(__i) \
	क्रम (__i = 0; __i < DM_VERITY_FEC_BUF_PREALLOC; __i++)

/* Loop over each extra buffer slot. */
#घोषणा fec_क्रम_each_extra_buffer(io, __i) \
	क्रम (__i = DM_VERITY_FEC_BUF_PREALLOC; __i < DM_VERITY_FEC_BUF_MAX; __i++)

/* Loop over each allocated buffer. */
#घोषणा fec_क्रम_each_buffer(io, __i) \
	क्रम (__i = 0; __i < (io)->nbufs; __i++)

/* Loop over each RS block in each allocated buffer. */
#घोषणा fec_क्रम_each_buffer_rs_block(io, __i, __j) \
	fec_क्रम_each_buffer(io, __i) \
		क्रम (__j = 0; __j < 1 << DM_VERITY_FEC_BUF_RS_BITS; __j++)

/*
 * Return a poपूर्णांकer to the current RS block when called inside
 * fec_क्रम_each_buffer_rs_block.
 */
अटल अंतरभूत u8 *fec_buffer_rs_block(काष्ठा dm_verity *v,
				      काष्ठा dm_verity_fec_io *fio,
				      अचिन्हित i, अचिन्हित j)
अणु
	वापस &fio->bufs[i][j * v->fec->rsn];
पूर्ण

/*
 * Return an index to the current RS block when called inside
 * fec_क्रम_each_buffer_rs_block.
 */
अटल अंतरभूत अचिन्हित fec_buffer_rs_index(अचिन्हित i, अचिन्हित j)
अणु
	वापस (i << DM_VERITY_FEC_BUF_RS_BITS) + j;
पूर्ण

/*
 * Decode all RS blocks from buffers and copy corrected bytes पूर्णांकo fio->output
 * starting from block_offset.
 */
अटल पूर्णांक fec_decode_bufs(काष्ठा dm_verity *v, काष्ठा dm_verity_fec_io *fio,
			   u64 rsb, पूर्णांक byte_index, अचिन्हित block_offset,
			   पूर्णांक neras)
अणु
	पूर्णांक r, corrected = 0, res;
	काष्ठा dm_buffer *buf;
	अचिन्हित n, i, offset;
	u8 *par, *block;

	par = fec_पढ़ो_parity(v, rsb, block_offset, &offset, &buf);
	अगर (IS_ERR(par))
		वापस PTR_ERR(par);

	/*
	 * Decode the RS blocks we have in bufs. Each RS block results in
	 * one corrected target byte and consumes fec->roots parity bytes.
	 */
	fec_क्रम_each_buffer_rs_block(fio, n, i) अणु
		block = fec_buffer_rs_block(v, fio, n, i);
		res = fec_decode_rs8(v, fio, block, &par[offset], neras);
		अगर (res < 0) अणु
			r = res;
			जाओ error;
		पूर्ण

		corrected += res;
		fio->output[block_offset] = block[byte_index];

		block_offset++;
		अगर (block_offset >= 1 << v->data_dev_block_bits)
			जाओ करोne;

		/* पढ़ो the next block when we run out of parity bytes */
		offset += v->fec->roots;
		अगर (offset >= v->fec->io_size) अणु
			dm_bufio_release(buf);

			par = fec_पढ़ो_parity(v, rsb, block_offset, &offset, &buf);
			अगर (IS_ERR(par))
				वापस PTR_ERR(par);
		पूर्ण
	पूर्ण
करोne:
	r = corrected;
error:
	dm_bufio_release(buf);

	अगर (r < 0 && neras)
		DMERR_LIMIT("%s: FEC %llu: failed to correct: %d",
			    v->data_dev->name, (अचिन्हित दीर्घ दीर्घ)rsb, r);
	अन्यथा अगर (r > 0)
		DMWARN_LIMIT("%s: FEC %llu: corrected %d errors",
			     v->data_dev->name, (अचिन्हित दीर्घ दीर्घ)rsb, r);

	वापस r;
पूर्ण

/*
 * Locate data block erasures using verity hashes.
 */
अटल पूर्णांक fec_is_erasure(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			  u8 *want_digest, u8 *data)
अणु
	अगर (unlikely(verity_hash(v, verity_io_hash_req(v, io),
				 data, 1 << v->data_dev_block_bits,
				 verity_io_real_digest(v, io))))
		वापस 0;

	वापस स_भेद(verity_io_real_digest(v, io), want_digest,
		      v->digest_size) != 0;
पूर्ण

/*
 * Read data blocks that are part of the RS block and deपूर्णांकerleave as much as
 * fits पूर्णांकo buffers. Check क्रम erasure locations अगर @neras is non-शून्य.
 */
अटल पूर्णांक fec_पढ़ो_bufs(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			 u64 rsb, u64 target, अचिन्हित block_offset,
			 पूर्णांक *neras)
अणु
	bool is_zero;
	पूर्णांक i, j, target_index = -1;
	काष्ठा dm_buffer *buf;
	काष्ठा dm_bufio_client *bufio;
	काष्ठा dm_verity_fec_io *fio = fec_io(io);
	u64 block, ileaved;
	u8 *bbuf, *rs_block;
	u8 want_digest[HASH_MAX_DIGESTSIZE];
	अचिन्हित n, k;

	अगर (neras)
		*neras = 0;

	अगर (WARN_ON(v->digest_size > माप(want_digest)))
		वापस -EINVAL;

	/*
	 * पढ़ो each of the rsn data blocks that are part of the RS block, and
	 * पूर्णांकerleave contents to available bufs
	 */
	क्रम (i = 0; i < v->fec->rsn; i++) अणु
		ileaved = fec_पूर्णांकerleave(v, rsb * v->fec->rsn + i);

		/*
		 * target is the data block we want to correct, target_index is
		 * the index of this block within the rsn RS blocks
		 */
		अगर (ileaved == target)
			target_index = i;

		block = ileaved >> v->data_dev_block_bits;
		bufio = v->fec->data_bufio;

		अगर (block >= v->data_blocks) अणु
			block -= v->data_blocks;

			/*
			 * blocks outside the area were assumed to contain
			 * zeros when encoding data was generated
			 */
			अगर (unlikely(block >= v->fec->hash_blocks))
				जारी;

			block += v->hash_start;
			bufio = v->bufio;
		पूर्ण

		bbuf = dm_bufio_पढ़ो(bufio, block, &buf);
		अगर (IS_ERR(bbuf)) अणु
			DMWARN_LIMIT("%s: FEC %llu: read failed (%llu): %ld",
				     v->data_dev->name,
				     (अचिन्हित दीर्घ दीर्घ)rsb,
				     (अचिन्हित दीर्घ दीर्घ)block, PTR_ERR(bbuf));

			/* assume the block is corrupted */
			अगर (neras && *neras <= v->fec->roots)
				fio->erasures[(*neras)++] = i;

			जारी;
		पूर्ण

		/* locate erasures अगर the block is on the data device */
		अगर (bufio == v->fec->data_bufio &&
		    verity_hash_क्रम_block(v, io, block, want_digest,
					  &is_zero) == 0) अणु
			/* skip known zero blocks entirely */
			अगर (is_zero)
				जाओ करोne;

			/*
			 * skip अगर we have alपढ़ोy found the theoretical
			 * maximum number (i.e. fec->roots) of erasures
			 */
			अगर (neras && *neras <= v->fec->roots &&
			    fec_is_erasure(v, io, want_digest, bbuf))
				fio->erasures[(*neras)++] = i;
		पूर्ण

		/*
		 * deपूर्णांकerleave and copy the bytes that fit पूर्णांकo bufs,
		 * starting from block_offset
		 */
		fec_क्रम_each_buffer_rs_block(fio, n, j) अणु
			k = fec_buffer_rs_index(n, j) + block_offset;

			अगर (k >= 1 << v->data_dev_block_bits)
				जाओ करोne;

			rs_block = fec_buffer_rs_block(v, fio, n, j);
			rs_block[i] = bbuf[k];
		पूर्ण
करोne:
		dm_bufio_release(buf);
	पूर्ण

	वापस target_index;
पूर्ण

/*
 * Allocate RS control काष्ठाure and FEC buffers from pपुनः_स्मृतिated mempools,
 * and attempt to allocate as many extra buffers as available.
 */
अटल पूर्णांक fec_alloc_bufs(काष्ठा dm_verity *v, काष्ठा dm_verity_fec_io *fio)
अणु
	अचिन्हित n;

	अगर (!fio->rs)
		fio->rs = mempool_alloc(&v->fec->rs_pool, GFP_NOIO);

	fec_क्रम_each_pपुनः_स्मृति_buffer(n) अणु
		अगर (fio->bufs[n])
			जारी;

		fio->bufs[n] = mempool_alloc(&v->fec->pपुनः_स्मृति_pool, GFP_NOWAIT);
		अगर (unlikely(!fio->bufs[n])) अणु
			DMERR("failed to allocate FEC buffer");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* try to allocate the maximum number of buffers */
	fec_क्रम_each_extra_buffer(fio, n) अणु
		अगर (fio->bufs[n])
			जारी;

		fio->bufs[n] = mempool_alloc(&v->fec->extra_pool, GFP_NOWAIT);
		/* we can manage with even one buffer अगर necessary */
		अगर (unlikely(!fio->bufs[n]))
			अवरोध;
	पूर्ण
	fio->nbufs = n;

	अगर (!fio->output)
		fio->output = mempool_alloc(&v->fec->output_pool, GFP_NOIO);

	वापस 0;
पूर्ण

/*
 * Initialize buffers and clear erasures. fec_पढ़ो_bufs() assumes buffers are
 * zeroed beक्रमe deपूर्णांकerleaving.
 */
अटल व्योम fec_init_bufs(काष्ठा dm_verity *v, काष्ठा dm_verity_fec_io *fio)
अणु
	अचिन्हित n;

	fec_क्रम_each_buffer(fio, n)
		स_रखो(fio->bufs[n], 0, v->fec->rsn << DM_VERITY_FEC_BUF_RS_BITS);

	स_रखो(fio->erasures, 0, माप(fio->erasures));
पूर्ण

/*
 * Decode all RS blocks in a single data block and वापस the target block
 * (indicated by @offset) in fio->output. If @use_erasures is non-zero, uses
 * hashes to locate erasures.
 */
अटल पूर्णांक fec_decode_rsb(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			  काष्ठा dm_verity_fec_io *fio, u64 rsb, u64 offset,
			  bool use_erasures)
अणु
	पूर्णांक r, neras = 0;
	अचिन्हित pos;

	r = fec_alloc_bufs(v, fio);
	अगर (unlikely(r < 0))
		वापस r;

	क्रम (pos = 0; pos < 1 << v->data_dev_block_bits; ) अणु
		fec_init_bufs(v, fio);

		r = fec_पढ़ो_bufs(v, io, rsb, offset, pos,
				  use_erasures ? &neras : शून्य);
		अगर (unlikely(r < 0))
			वापस r;

		r = fec_decode_bufs(v, fio, rsb, r, pos, neras);
		अगर (r < 0)
			वापस r;

		pos += fio->nbufs << DM_VERITY_FEC_BUF_RS_BITS;
	पूर्ण

	/* Always re-validate the corrected block against the expected hash */
	r = verity_hash(v, verity_io_hash_req(v, io), fio->output,
			1 << v->data_dev_block_bits,
			verity_io_real_digest(v, io));
	अगर (unlikely(r < 0))
		वापस r;

	अगर (स_भेद(verity_io_real_digest(v, io), verity_io_want_digest(v, io),
		   v->digest_size)) अणु
		DMERR_LIMIT("%s: FEC %llu: failed to correct (%d erasures)",
			    v->data_dev->name, (अचिन्हित दीर्घ दीर्घ)rsb, neras);
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fec_bv_copy(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io, u8 *data,
		       माप_प्रकार len)
अणु
	काष्ठा dm_verity_fec_io *fio = fec_io(io);

	स_नकल(data, &fio->output[fio->output_pos], len);
	fio->output_pos += len;

	वापस 0;
पूर्ण

/*
 * Correct errors in a block. Copies corrected block to dest अगर non-शून्य,
 * otherwise to a bio_vec starting from iter.
 */
पूर्णांक verity_fec_decode(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
		      क्रमागत verity_block_type type, sector_t block, u8 *dest,
		      काष्ठा bvec_iter *iter)
अणु
	पूर्णांक r;
	काष्ठा dm_verity_fec_io *fio = fec_io(io);
	u64 offset, res, rsb;

	अगर (!verity_fec_is_enabled(v))
		वापस -EOPNOTSUPP;

	अगर (fio->level >= DM_VERITY_FEC_MAX_RECURSION) अणु
		DMWARN_LIMIT("%s: FEC: recursion too deep", v->data_dev->name);
		वापस -EIO;
	पूर्ण

	fio->level++;

	अगर (type == DM_VERITY_BLOCK_TYPE_METADATA)
		block = block - v->hash_start + v->data_blocks;

	/*
	 * For RS(M, N), the continuous FEC data is भागided पूर्णांकo blocks of N
	 * bytes. Since block size may not be भागisible by N, the last block
	 * is zero padded when decoding.
	 *
	 * Each byte of the block is covered by a dअगरferent RS(M, N) code,
	 * and each code is पूर्णांकerleaved over N blocks to make it less likely
	 * that bursty corruption will leave us in unrecoverable state.
	 */

	offset = block << v->data_dev_block_bits;
	res = भाग64_u64(offset, v->fec->rounds << v->data_dev_block_bits);

	/*
	 * The base RS block we can feed to the पूर्णांकerleaver to find out all
	 * blocks required क्रम decoding.
	 */
	rsb = offset - res * (v->fec->rounds << v->data_dev_block_bits);

	/*
	 * Locating erasures is slow, so attempt to recover the block without
	 * them first. Do a second attempt with erasures अगर the corruption is
	 * bad enough.
	 */
	r = fec_decode_rsb(v, io, fio, rsb, offset, false);
	अगर (r < 0) अणु
		r = fec_decode_rsb(v, io, fio, rsb, offset, true);
		अगर (r < 0)
			जाओ करोne;
	पूर्ण

	अगर (dest)
		स_नकल(dest, fio->output, 1 << v->data_dev_block_bits);
	अन्यथा अगर (iter) अणु
		fio->output_pos = 0;
		r = verity_क्रम_bv_block(v, io, iter, fec_bv_copy);
	पूर्ण

करोne:
	fio->level--;
	वापस r;
पूर्ण

/*
 * Clean up per-bio data.
 */
व्योम verity_fec_finish_io(काष्ठा dm_verity_io *io)
अणु
	अचिन्हित n;
	काष्ठा dm_verity_fec *f = io->v->fec;
	काष्ठा dm_verity_fec_io *fio = fec_io(io);

	अगर (!verity_fec_is_enabled(io->v))
		वापस;

	mempool_मुक्त(fio->rs, &f->rs_pool);

	fec_क्रम_each_pपुनः_स्मृति_buffer(n)
		mempool_मुक्त(fio->bufs[n], &f->pपुनः_स्मृति_pool);

	fec_क्रम_each_extra_buffer(fio, n)
		mempool_मुक्त(fio->bufs[n], &f->extra_pool);

	mempool_मुक्त(fio->output, &f->output_pool);
पूर्ण

/*
 * Initialize per-bio data.
 */
व्योम verity_fec_init_io(काष्ठा dm_verity_io *io)
अणु
	काष्ठा dm_verity_fec_io *fio = fec_io(io);

	अगर (!verity_fec_is_enabled(io->v))
		वापस;

	fio->rs = शून्य;
	स_रखो(fio->bufs, 0, माप(fio->bufs));
	fio->nbufs = 0;
	fio->output = शून्य;
	fio->level = 0;
पूर्ण

/*
 * Append feature arguments and values to the status table.
 */
अचिन्हित verity_fec_status_table(काष्ठा dm_verity *v, अचिन्हित sz,
				 अक्षर *result, अचिन्हित maxlen)
अणु
	अगर (!verity_fec_is_enabled(v))
		वापस sz;

	DMEMIT(" " DM_VERITY_OPT_FEC_DEV " %s "
	       DM_VERITY_OPT_FEC_BLOCKS " %llu "
	       DM_VERITY_OPT_FEC_START " %llu "
	       DM_VERITY_OPT_FEC_ROOTS " %d",
	       v->fec->dev->name,
	       (अचिन्हित दीर्घ दीर्घ)v->fec->blocks,
	       (अचिन्हित दीर्घ दीर्घ)v->fec->start,
	       v->fec->roots);

	वापस sz;
पूर्ण

व्योम verity_fec_dtr(काष्ठा dm_verity *v)
अणु
	काष्ठा dm_verity_fec *f = v->fec;

	अगर (!verity_fec_is_enabled(v))
		जाओ out;

	mempool_निकास(&f->rs_pool);
	mempool_निकास(&f->pपुनः_स्मृति_pool);
	mempool_निकास(&f->extra_pool);
	mempool_निकास(&f->output_pool);
	kmem_cache_destroy(f->cache);

	अगर (f->data_bufio)
		dm_bufio_client_destroy(f->data_bufio);
	अगर (f->bufio)
		dm_bufio_client_destroy(f->bufio);

	अगर (f->dev)
		dm_put_device(v->ti, f->dev);
out:
	kमुक्त(f);
	v->fec = शून्य;
पूर्ण

अटल व्योम *fec_rs_alloc(gfp_t gfp_mask, व्योम *pool_data)
अणु
	काष्ठा dm_verity *v = (काष्ठा dm_verity *)pool_data;

	वापस init_rs_gfp(8, 0x11d, 0, 1, v->fec->roots, gfp_mask);
पूर्ण

अटल व्योम fec_rs_मुक्त(व्योम *element, व्योम *pool_data)
अणु
	काष्ठा rs_control *rs = (काष्ठा rs_control *)element;

	अगर (rs)
		मुक्त_rs(rs);
पूर्ण

bool verity_is_fec_opt_arg(स्थिर अक्षर *arg_name)
अणु
	वापस (!strहालcmp(arg_name, DM_VERITY_OPT_FEC_DEV) ||
		!strहालcmp(arg_name, DM_VERITY_OPT_FEC_BLOCKS) ||
		!strहालcmp(arg_name, DM_VERITY_OPT_FEC_START) ||
		!strहालcmp(arg_name, DM_VERITY_OPT_FEC_ROOTS));
पूर्ण

पूर्णांक verity_fec_parse_opt_args(काष्ठा dm_arg_set *as, काष्ठा dm_verity *v,
			      अचिन्हित *argc, स्थिर अक्षर *arg_name)
अणु
	पूर्णांक r;
	काष्ठा dm_target *ti = v->ti;
	स्थिर अक्षर *arg_value;
	अचिन्हित दीर्घ दीर्घ num_ll;
	अचिन्हित अक्षर num_c;
	अक्षर dummy;

	अगर (!*argc) अणु
		ti->error = "FEC feature arguments require a value";
		वापस -EINVAL;
	पूर्ण

	arg_value = dm_shअगरt_arg(as);
	(*argc)--;

	अगर (!strहालcmp(arg_name, DM_VERITY_OPT_FEC_DEV)) अणु
		r = dm_get_device(ti, arg_value, FMODE_READ, &v->fec->dev);
		अगर (r) अणु
			ti->error = "FEC device lookup failed";
			वापस r;
		पूर्ण

	पूर्ण अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_FEC_BLOCKS)) अणु
		अगर (माला_पूछो(arg_value, "%llu%c", &num_ll, &dummy) != 1 ||
		    ((sector_t)(num_ll << (v->data_dev_block_bits - SECTOR_SHIFT))
		     >> (v->data_dev_block_bits - SECTOR_SHIFT) != num_ll)) अणु
			ti->error = "Invalid " DM_VERITY_OPT_FEC_BLOCKS;
			वापस -EINVAL;
		पूर्ण
		v->fec->blocks = num_ll;

	पूर्ण अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_FEC_START)) अणु
		अगर (माला_पूछो(arg_value, "%llu%c", &num_ll, &dummy) != 1 ||
		    ((sector_t)(num_ll << (v->data_dev_block_bits - SECTOR_SHIFT)) >>
		     (v->data_dev_block_bits - SECTOR_SHIFT) != num_ll)) अणु
			ti->error = "Invalid " DM_VERITY_OPT_FEC_START;
			वापस -EINVAL;
		पूर्ण
		v->fec->start = num_ll;

	पूर्ण अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_FEC_ROOTS)) अणु
		अगर (माला_पूछो(arg_value, "%hhu%c", &num_c, &dummy) != 1 || !num_c ||
		    num_c < (DM_VERITY_FEC_RSM - DM_VERITY_FEC_MAX_RSN) ||
		    num_c > (DM_VERITY_FEC_RSM - DM_VERITY_FEC_MIN_RSN)) अणु
			ti->error = "Invalid " DM_VERITY_OPT_FEC_ROOTS;
			वापस -EINVAL;
		पूर्ण
		v->fec->roots = num_c;

	पूर्ण अन्यथा अणु
		ti->error = "Unrecognized verity FEC feature request";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Allocate dm_verity_fec क्रम v->fec. Must be called beक्रमe verity_fec_ctr.
 */
पूर्णांक verity_fec_ctr_alloc(काष्ठा dm_verity *v)
अणु
	काष्ठा dm_verity_fec *f;

	f = kzalloc(माप(काष्ठा dm_verity_fec), GFP_KERNEL);
	अगर (!f) अणु
		v->ti->error = "Cannot allocate FEC structure";
		वापस -ENOMEM;
	पूर्ण
	v->fec = f;

	वापस 0;
पूर्ण

/*
 * Validate arguments and pपुनः_स्मृतिate memory. Must be called after arguments
 * have been parsed using verity_fec_parse_opt_args.
 */
पूर्णांक verity_fec_ctr(काष्ठा dm_verity *v)
अणु
	काष्ठा dm_verity_fec *f = v->fec;
	काष्ठा dm_target *ti = v->ti;
	u64 hash_blocks, fec_blocks;
	पूर्णांक ret;

	अगर (!verity_fec_is_enabled(v)) अणु
		verity_fec_dtr(v);
		वापस 0;
	पूर्ण

	/*
	 * FEC is computed over data blocks, possible metadata, and
	 * hash blocks. In other words, FEC covers total of fec_blocks
	 * blocks consisting of the following:
	 *
	 *  data blocks | hash blocks | metadata (optional)
	 *
	 * We allow metadata after hash blocks to support a use हाल
	 * where all data is stored on the same device and FEC covers
	 * the entire area.
	 *
	 * If metadata is included, we require it to be available on the
	 * hash device after the hash blocks.
	 */

	hash_blocks = v->hash_blocks - v->hash_start;

	/*
	 * Require matching block sizes क्रम data and hash devices क्रम
	 * simplicity.
	 */
	अगर (v->data_dev_block_bits != v->hash_dev_block_bits) अणु
		ti->error = "Block sizes must match to use FEC";
		वापस -EINVAL;
	पूर्ण

	अगर (!f->roots) अणु
		ti->error = "Missing " DM_VERITY_OPT_FEC_ROOTS;
		वापस -EINVAL;
	पूर्ण
	f->rsn = DM_VERITY_FEC_RSM - f->roots;

	अगर (!f->blocks) अणु
		ti->error = "Missing " DM_VERITY_OPT_FEC_BLOCKS;
		वापस -EINVAL;
	पूर्ण

	f->rounds = f->blocks;
	अगर (sector_भाग(f->rounds, f->rsn))
		f->rounds++;

	/*
	 * Due to optional metadata, f->blocks can be larger than
	 * data_blocks and hash_blocks combined.
	 */
	अगर (f->blocks < v->data_blocks + hash_blocks || !f->rounds) अणु
		ti->error = "Invalid " DM_VERITY_OPT_FEC_BLOCKS;
		वापस -EINVAL;
	पूर्ण

	/*
	 * Metadata is accessed through the hash device, so we require
	 * it to be large enough.
	 */
	f->hash_blocks = f->blocks - v->data_blocks;
	अगर (dm_bufio_get_device_size(v->bufio) < f->hash_blocks) अणु
		ti->error = "Hash device is too small for "
			DM_VERITY_OPT_FEC_BLOCKS;
		वापस -E2BIG;
	पूर्ण

	अगर ((f->roots << SECTOR_SHIFT) & ((1 << v->data_dev_block_bits) - 1))
		f->io_size = 1 << v->data_dev_block_bits;
	अन्यथा
		f->io_size = v->fec->roots << SECTOR_SHIFT;

	f->bufio = dm_bufio_client_create(f->dev->bdev,
					  f->io_size,
					  1, 0, शून्य, शून्य);
	अगर (IS_ERR(f->bufio)) अणु
		ti->error = "Cannot initialize FEC bufio client";
		वापस PTR_ERR(f->bufio);
	पूर्ण

	dm_bufio_set_sector_offset(f->bufio, f->start << (v->data_dev_block_bits - SECTOR_SHIFT));

	fec_blocks = भाग64_u64(f->rounds * f->roots, v->fec->roots << SECTOR_SHIFT);
	अगर (dm_bufio_get_device_size(f->bufio) < fec_blocks) अणु
		ti->error = "FEC device is too small";
		वापस -E2BIG;
	पूर्ण

	f->data_bufio = dm_bufio_client_create(v->data_dev->bdev,
					       1 << v->data_dev_block_bits,
					       1, 0, शून्य, शून्य);
	अगर (IS_ERR(f->data_bufio)) अणु
		ti->error = "Cannot initialize FEC data bufio client";
		वापस PTR_ERR(f->data_bufio);
	पूर्ण

	अगर (dm_bufio_get_device_size(f->data_bufio) < v->data_blocks) अणु
		ti->error = "Data device is too small";
		वापस -E2BIG;
	पूर्ण

	/* Pपुनः_स्मृतिate an rs_control काष्ठाure क्रम each worker thपढ़ो */
	ret = mempool_init(&f->rs_pool, num_online_cpus(), fec_rs_alloc,
			   fec_rs_मुक्त, (व्योम *) v);
	अगर (ret) अणु
		ti->error = "Cannot allocate RS pool";
		वापस ret;
	पूर्ण

	f->cache = kmem_cache_create("dm_verity_fec_buffers",
				     f->rsn << DM_VERITY_FEC_BUF_RS_BITS,
				     0, 0, शून्य);
	अगर (!f->cache) अणु
		ti->error = "Cannot create FEC buffer cache";
		वापस -ENOMEM;
	पूर्ण

	/* Pपुनः_स्मृतिate DM_VERITY_FEC_BUF_PREALLOC buffers क्रम each thपढ़ो */
	ret = mempool_init_slab_pool(&f->pपुनः_स्मृति_pool, num_online_cpus() *
				     DM_VERITY_FEC_BUF_PREALLOC,
				     f->cache);
	अगर (ret) अणु
		ti->error = "Cannot allocate FEC buffer prealloc pool";
		वापस ret;
	पूर्ण

	ret = mempool_init_slab_pool(&f->extra_pool, 0, f->cache);
	अगर (ret) अणु
		ti->error = "Cannot allocate FEC buffer extra pool";
		वापस ret;
	पूर्ण

	/* Pपुनः_स्मृतिate an output buffer क्रम each thपढ़ो */
	ret = mempool_init_kदो_स्मृति_pool(&f->output_pool, num_online_cpus(),
					1 << v->data_dev_block_bits);
	अगर (ret) अणु
		ti->error = "Cannot allocate FEC output pool";
		वापस ret;
	पूर्ण

	/* Reserve space क्रम our per-bio data */
	ti->per_io_data_size += माप(काष्ठा dm_verity_fec_io);

	वापस 0;
पूर्ण
