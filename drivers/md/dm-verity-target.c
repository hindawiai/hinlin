<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * Author: Mikulas Patocka <mpatocka@redhat.com>
 *
 * Based on Chromium dm-verity driver (C) 2011 The Chromium OS Authors
 *
 * In the file "/sys/module/dm_verity/parameters/prefetch_cluster" you can set
 * शेष prefetch value. Data are पढ़ो in "prefetch_cluster" chunks from the
 * hash device. Setting this greatly improves perक्रमmance when data and hash
 * are on the same disk on dअगरferent partitions on devices with poor अक्रमom
 * access behavior.
 */

#समावेश "dm-verity.h"
#समावेश "dm-verity-fec.h"
#समावेश "dm-verity-verify-sig.h"
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>

#घोषणा DM_MSG_PREFIX			"verity"

#घोषणा DM_VERITY_ENV_LENGTH		42
#घोषणा DM_VERITY_ENV_VAR_NAME		"DM_VERITY_ERR_BLOCK_NR"

#घोषणा DM_VERITY_DEFAULT_PREFETCH_SIZE	262144

#घोषणा DM_VERITY_MAX_CORRUPTED_ERRS	100

#घोषणा DM_VERITY_OPT_LOGGING		"ignore_corruption"
#घोषणा DM_VERITY_OPT_RESTART		"restart_on_corruption"
#घोषणा DM_VERITY_OPT_PANIC		"panic_on_corruption"
#घोषणा DM_VERITY_OPT_IGN_ZEROES	"ignore_zero_blocks"
#घोषणा DM_VERITY_OPT_AT_MOST_ONCE	"check_at_most_once"

#घोषणा DM_VERITY_OPTS_MAX		(3 + DM_VERITY_OPTS_FEC + \
					 DM_VERITY_ROOT_HASH_VERIFICATION_OPTS)

अटल अचिन्हित dm_verity_prefetch_cluster = DM_VERITY_DEFAULT_PREFETCH_SIZE;

module_param_named(prefetch_cluster, dm_verity_prefetch_cluster, uपूर्णांक, S_IRUGO | S_IWUSR);

काष्ठा dm_verity_prefetch_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा dm_verity *v;
	sector_t block;
	अचिन्हित n_blocks;
पूर्ण;

/*
 * Auxiliary काष्ठाure appended to each dm-bufio buffer. If the value
 * hash_verअगरied is nonzero, hash of the block has been verअगरied.
 *
 * The variable hash_verअगरied is set to 0 when allocating the buffer, then
 * it can be changed to 1 and it is never reset to 0 again.
 *
 * There is no lock around this value, a race condition can at worst cause
 * that multiple processes verअगरy the hash of the same buffer simultaneously
 * and ग_लिखो 1 to hash_verअगरied simultaneously.
 * This condition is harmless, so we करोn't need locking.
 */
काष्ठा buffer_aux अणु
	पूर्णांक hash_verअगरied;
पूर्ण;

/*
 * Initialize काष्ठा buffer_aux क्रम a freshly created buffer.
 */
अटल व्योम dm_bufio_alloc_callback(काष्ठा dm_buffer *buf)
अणु
	काष्ठा buffer_aux *aux = dm_bufio_get_aux_data(buf);

	aux->hash_verअगरied = 0;
पूर्ण

/*
 * Translate input sector number to the sector number on the target device.
 */
अटल sector_t verity_map_sector(काष्ठा dm_verity *v, sector_t bi_sector)
अणु
	वापस v->data_start + dm_target_offset(v->ti, bi_sector);
पूर्ण

/*
 * Return hash position of a specअगरied block at a specअगरied tree level
 * (0 is the lowest level).
 * The lowest "hash_per_block_bits"-bits of the result denote hash position
 * inside a hash block. The reमुख्यing bits denote location of the hash block.
 */
अटल sector_t verity_position_at_level(काष्ठा dm_verity *v, sector_t block,
					 पूर्णांक level)
अणु
	वापस block >> (level * v->hash_per_block_bits);
पूर्ण

अटल पूर्णांक verity_hash_update(काष्ठा dm_verity *v, काष्ठा ahash_request *req,
				स्थिर u8 *data, माप_प्रकार len,
				काष्ठा crypto_रुको *रुको)
अणु
	काष्ठा scatterlist sg;

	अगर (likely(!is_vदो_स्मृति_addr(data))) अणु
		sg_init_one(&sg, data, len);
		ahash_request_set_crypt(req, &sg, शून्य, len);
		वापस crypto_रुको_req(crypto_ahash_update(req), रुको);
	पूर्ण अन्यथा अणु
		करो अणु
			पूर्णांक r;
			माप_प्रकार this_step = min_t(माप_प्रकार, len, PAGE_SIZE - offset_in_page(data));
			flush_kernel_vmap_range((व्योम *)data, this_step);
			sg_init_table(&sg, 1);
			sg_set_page(&sg, vदो_स्मृति_to_page(data), this_step, offset_in_page(data));
			ahash_request_set_crypt(req, &sg, शून्य, this_step);
			r = crypto_रुको_req(crypto_ahash_update(req), रुको);
			अगर (unlikely(r))
				वापस r;
			data += this_step;
			len -= this_step;
		पूर्ण जबतक (len);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Wrapper क्रम crypto_ahash_init, which handles verity salting.
 */
अटल पूर्णांक verity_hash_init(काष्ठा dm_verity *v, काष्ठा ahash_request *req,
				काष्ठा crypto_रुको *रुको)
अणु
	पूर्णांक r;

	ahash_request_set_tfm(req, v->tfm);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
					crypto_req_करोne, (व्योम *)रुको);
	crypto_init_रुको(रुको);

	r = crypto_रुको_req(crypto_ahash_init(req), रुको);

	अगर (unlikely(r < 0)) अणु
		DMERR("crypto_ahash_init failed: %d", r);
		वापस r;
	पूर्ण

	अगर (likely(v->salt_size && (v->version >= 1)))
		r = verity_hash_update(v, req, v->salt, v->salt_size, रुको);

	वापस r;
पूर्ण

अटल पूर्णांक verity_hash_final(काष्ठा dm_verity *v, काष्ठा ahash_request *req,
			     u8 *digest, काष्ठा crypto_रुको *रुको)
अणु
	पूर्णांक r;

	अगर (unlikely(v->salt_size && (!v->version))) अणु
		r = verity_hash_update(v, req, v->salt, v->salt_size, रुको);

		अगर (r < 0) अणु
			DMERR("verity_hash_final failed updating salt: %d", r);
			जाओ out;
		पूर्ण
	पूर्ण

	ahash_request_set_crypt(req, शून्य, digest, 0);
	r = crypto_रुको_req(crypto_ahash_final(req), रुको);
out:
	वापस r;
पूर्ण

पूर्णांक verity_hash(काष्ठा dm_verity *v, काष्ठा ahash_request *req,
		स्थिर u8 *data, माप_प्रकार len, u8 *digest)
अणु
	पूर्णांक r;
	काष्ठा crypto_रुको रुको;

	r = verity_hash_init(v, req, &रुको);
	अगर (unlikely(r < 0))
		जाओ out;

	r = verity_hash_update(v, req, data, len, &रुको);
	अगर (unlikely(r < 0))
		जाओ out;

	r = verity_hash_final(v, req, digest, &रुको);

out:
	वापस r;
पूर्ण

अटल व्योम verity_hash_at_level(काष्ठा dm_verity *v, sector_t block, पूर्णांक level,
				 sector_t *hash_block, अचिन्हित *offset)
अणु
	sector_t position = verity_position_at_level(v, block, level);
	अचिन्हित idx;

	*hash_block = v->hash_level_block[level] + (position >> v->hash_per_block_bits);

	अगर (!offset)
		वापस;

	idx = position & ((1 << v->hash_per_block_bits) - 1);
	अगर (!v->version)
		*offset = idx * v->digest_size;
	अन्यथा
		*offset = idx << (v->hash_dev_block_bits - v->hash_per_block_bits);
पूर्ण

/*
 * Handle verअगरication errors.
 */
अटल पूर्णांक verity_handle_err(काष्ठा dm_verity *v, क्रमागत verity_block_type type,
			     अचिन्हित दीर्घ दीर्घ block)
अणु
	अक्षर verity_env[DM_VERITY_ENV_LENGTH];
	अक्षर *envp[] = अणु verity_env, शून्य पूर्ण;
	स्थिर अक्षर *type_str = "";
	काष्ठा mapped_device *md = dm_table_get_md(v->ti->table);

	/* Corruption should be visible in device status in all modes */
	v->hash_failed = 1;

	अगर (v->corrupted_errs >= DM_VERITY_MAX_CORRUPTED_ERRS)
		जाओ out;

	v->corrupted_errs++;

	चयन (type) अणु
	हाल DM_VERITY_BLOCK_TYPE_DATA:
		type_str = "data";
		अवरोध;
	हाल DM_VERITY_BLOCK_TYPE_METADATA:
		type_str = "metadata";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	DMERR_LIMIT("%s: %s block %llu is corrupted", v->data_dev->name,
		    type_str, block);

	अगर (v->corrupted_errs == DM_VERITY_MAX_CORRUPTED_ERRS)
		DMERR("%s: reached maximum errors", v->data_dev->name);

	snम_लिखो(verity_env, DM_VERITY_ENV_LENGTH, "%s=%d,%llu",
		DM_VERITY_ENV_VAR_NAME, type, block);

	kobject_uevent_env(&disk_to_dev(dm_disk(md))->kobj, KOBJ_CHANGE, envp);

out:
	अगर (v->mode == DM_VERITY_MODE_LOGGING)
		वापस 0;

	अगर (v->mode == DM_VERITY_MODE_RESTART)
		kernel_restart("dm-verity device corrupted");

	अगर (v->mode == DM_VERITY_MODE_PANIC)
		panic("dm-verity device corrupted");

	वापस 1;
पूर्ण

/*
 * Verअगरy hash of a metadata block pertaining to the specअगरied data block
 * ("block" argument) at a specअगरied level ("level" argument).
 *
 * On successful वापस, verity_io_want_digest(v, io) contains the hash value
 * क्रम a lower tree level or क्रम the data block (अगर we're at the lowest level).
 *
 * If "skip_unverified" is true, unverअगरied buffer is skipped and 1 is वापसed.
 * If "skip_unverified" is false, unverअगरied buffer is hashed and verअगरied
 * against current value of verity_io_want_digest(v, io).
 */
अटल पूर्णांक verity_verअगरy_level(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			       sector_t block, पूर्णांक level, bool skip_unverअगरied,
			       u8 *want_digest)
अणु
	काष्ठा dm_buffer *buf;
	काष्ठा buffer_aux *aux;
	u8 *data;
	पूर्णांक r;
	sector_t hash_block;
	अचिन्हित offset;

	verity_hash_at_level(v, block, level, &hash_block, &offset);

	data = dm_bufio_पढ़ो(v->bufio, hash_block, &buf);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	aux = dm_bufio_get_aux_data(buf);

	अगर (!aux->hash_verअगरied) अणु
		अगर (skip_unverअगरied) अणु
			r = 1;
			जाओ release_ret_r;
		पूर्ण

		r = verity_hash(v, verity_io_hash_req(v, io),
				data, 1 << v->hash_dev_block_bits,
				verity_io_real_digest(v, io));
		अगर (unlikely(r < 0))
			जाओ release_ret_r;

		अगर (likely(स_भेद(verity_io_real_digest(v, io), want_digest,
				  v->digest_size) == 0))
			aux->hash_verअगरied = 1;
		अन्यथा अगर (verity_fec_decode(v, io,
					   DM_VERITY_BLOCK_TYPE_METADATA,
					   hash_block, data, शून्य) == 0)
			aux->hash_verअगरied = 1;
		अन्यथा अगर (verity_handle_err(v,
					   DM_VERITY_BLOCK_TYPE_METADATA,
					   hash_block)) अणु
			r = -EIO;
			जाओ release_ret_r;
		पूर्ण
	पूर्ण

	data += offset;
	स_नकल(want_digest, data, v->digest_size);
	r = 0;

release_ret_r:
	dm_bufio_release(buf);
	वापस r;
पूर्ण

/*
 * Find a hash क्रम a given block, ग_लिखो it to digest and verअगरy the पूर्णांकegrity
 * of the hash tree अगर necessary.
 */
पूर्णांक verity_hash_क्रम_block(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			  sector_t block, u8 *digest, bool *is_zero)
अणु
	पूर्णांक r = 0, i;

	अगर (likely(v->levels)) अणु
		/*
		 * First, we try to get the requested hash क्रम
		 * the current block. If the hash block itself is
		 * verअगरied, zero is वापसed. If it isn't, this
		 * function वापसs 1 and we fall back to whole
		 * chain verअगरication.
		 */
		r = verity_verअगरy_level(v, io, block, 0, true, digest);
		अगर (likely(r <= 0))
			जाओ out;
	पूर्ण

	स_नकल(digest, v->root_digest, v->digest_size);

	क्रम (i = v->levels - 1; i >= 0; i--) अणु
		r = verity_verअगरy_level(v, io, block, i, false, digest);
		अगर (unlikely(r))
			जाओ out;
	पूर्ण
out:
	अगर (!r && v->zero_digest)
		*is_zero = !स_भेद(v->zero_digest, digest, v->digest_size);
	अन्यथा
		*is_zero = false;

	वापस r;
पूर्ण

/*
 * Calculates the digest क्रम the given bio
 */
अटल पूर्णांक verity_क्रम_io_block(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			       काष्ठा bvec_iter *iter, काष्ठा crypto_रुको *रुको)
अणु
	अचिन्हित पूर्णांक toकरो = 1 << v->data_dev_block_bits;
	काष्ठा bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);
	काष्ठा scatterlist sg;
	काष्ठा ahash_request *req = verity_io_hash_req(v, io);

	करो अणु
		पूर्णांक r;
		अचिन्हित पूर्णांक len;
		काष्ठा bio_vec bv = bio_iter_iovec(bio, *iter);

		sg_init_table(&sg, 1);

		len = bv.bv_len;

		अगर (likely(len >= toकरो))
			len = toकरो;
		/*
		 * Operating on a single page at a समय looks suboptimal
		 * until you consider the typical block size is 4,096B.
		 * Going through this loops twice should be very rare.
		 */
		sg_set_page(&sg, bv.bv_page, len, bv.bv_offset);
		ahash_request_set_crypt(req, &sg, शून्य, len);
		r = crypto_रुको_req(crypto_ahash_update(req), रुको);

		अगर (unlikely(r < 0)) अणु
			DMERR("verity_for_io_block crypto op failed: %d", r);
			वापस r;
		पूर्ण

		bio_advance_iter(bio, iter, len);
		toकरो -= len;
	पूर्ण जबतक (toकरो);

	वापस 0;
पूर्ण

/*
 * Calls function process क्रम 1 << v->data_dev_block_bits bytes in the bio_vec
 * starting from iter.
 */
पूर्णांक verity_क्रम_bv_block(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			काष्ठा bvec_iter *iter,
			पूर्णांक (*process)(काष्ठा dm_verity *v,
				       काष्ठा dm_verity_io *io, u8 *data,
				       माप_प्रकार len))
अणु
	अचिन्हित toकरो = 1 << v->data_dev_block_bits;
	काष्ठा bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);

	करो अणु
		पूर्णांक r;
		u8 *page;
		अचिन्हित len;
		काष्ठा bio_vec bv = bio_iter_iovec(bio, *iter);

		page = kmap_atomic(bv.bv_page);
		len = bv.bv_len;

		अगर (likely(len >= toकरो))
			len = toकरो;

		r = process(v, io, page + bv.bv_offset, len);
		kunmap_atomic(page);

		अगर (r < 0)
			वापस r;

		bio_advance_iter(bio, iter, len);
		toकरो -= len;
	पूर्ण जबतक (toकरो);

	वापस 0;
पूर्ण

अटल पूर्णांक verity_bv_zero(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io,
			  u8 *data, माप_प्रकार len)
अणु
	स_रखो(data, 0, len);
	वापस 0;
पूर्ण

/*
 * Moves the bio iter one data block क्रमward.
 */
अटल अंतरभूत व्योम verity_bv_skip_block(काष्ठा dm_verity *v,
					काष्ठा dm_verity_io *io,
					काष्ठा bvec_iter *iter)
अणु
	काष्ठा bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);

	bio_advance_iter(bio, iter, 1 << v->data_dev_block_bits);
पूर्ण

/*
 * Verअगरy one "dm_verity_io" काष्ठाure.
 */
अटल पूर्णांक verity_verअगरy_io(काष्ठा dm_verity_io *io)
अणु
	bool is_zero;
	काष्ठा dm_verity *v = io->v;
	काष्ठा bvec_iter start;
	अचिन्हित b;
	काष्ठा crypto_रुको रुको;

	क्रम (b = 0; b < io->n_blocks; b++) अणु
		पूर्णांक r;
		sector_t cur_block = io->block + b;
		काष्ठा ahash_request *req = verity_io_hash_req(v, io);

		अगर (v->validated_blocks &&
		    likely(test_bit(cur_block, v->validated_blocks))) अणु
			verity_bv_skip_block(v, io, &io->iter);
			जारी;
		पूर्ण

		r = verity_hash_क्रम_block(v, io, cur_block,
					  verity_io_want_digest(v, io),
					  &is_zero);
		अगर (unlikely(r < 0))
			वापस r;

		अगर (is_zero) अणु
			/*
			 * If we expect a zero block, करोn't validate, just
			 * वापस zeros.
			 */
			r = verity_क्रम_bv_block(v, io, &io->iter,
						verity_bv_zero);
			अगर (unlikely(r < 0))
				वापस r;

			जारी;
		पूर्ण

		r = verity_hash_init(v, req, &रुको);
		अगर (unlikely(r < 0))
			वापस r;

		start = io->iter;
		r = verity_क्रम_io_block(v, io, &io->iter, &रुको);
		अगर (unlikely(r < 0))
			वापस r;

		r = verity_hash_final(v, req, verity_io_real_digest(v, io),
					&रुको);
		अगर (unlikely(r < 0))
			वापस r;

		अगर (likely(स_भेद(verity_io_real_digest(v, io),
				  verity_io_want_digest(v, io), v->digest_size) == 0)) अणु
			अगर (v->validated_blocks)
				set_bit(cur_block, v->validated_blocks);
			जारी;
		पूर्ण
		अन्यथा अगर (verity_fec_decode(v, io, DM_VERITY_BLOCK_TYPE_DATA,
					   cur_block, शून्य, &start) == 0)
			जारी;
		अन्यथा अगर (verity_handle_err(v, DM_VERITY_BLOCK_TYPE_DATA,
					   cur_block))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Skip verity work in response to I/O error when प्रणाली is shutting करोwn.
 */
अटल अंतरभूत bool verity_is_प्रणाली_shutting_करोwn(व्योम)
अणु
	वापस प्रणाली_state == SYSTEM_HALT || प्रणाली_state == SYSTEM_POWER_OFF
		|| प्रणाली_state == SYSTEM_RESTART;
पूर्ण

/*
 * End one "io" काष्ठाure with a given error.
 */
अटल व्योम verity_finish_io(काष्ठा dm_verity_io *io, blk_status_t status)
अणु
	काष्ठा dm_verity *v = io->v;
	काष्ठा bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);

	bio->bi_end_io = io->orig_bi_end_io;
	bio->bi_status = status;

	verity_fec_finish_io(io);

	bio_endio(bio);
पूर्ण

अटल व्योम verity_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_verity_io *io = container_of(w, काष्ठा dm_verity_io, work);

	verity_finish_io(io, त्रुटि_सं_to_blk_status(verity_verअगरy_io(io)));
पूर्ण

अटल व्योम verity_end_io(काष्ठा bio *bio)
अणु
	काष्ठा dm_verity_io *io = bio->bi_निजी;

	अगर (bio->bi_status &&
	    (!verity_fec_is_enabled(io->v) || verity_is_प्रणाली_shutting_करोwn())) अणु
		verity_finish_io(io, bio->bi_status);
		वापस;
	पूर्ण

	INIT_WORK(&io->work, verity_work);
	queue_work(io->v->verअगरy_wq, &io->work);
पूर्ण

/*
 * Prefetch buffers क्रम the specअगरied io.
 * The root buffer is not prefetched, it is assumed that it will be cached
 * all the समय.
 */
अटल व्योम verity_prefetch_io(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_verity_prefetch_work *pw =
		container_of(work, काष्ठा dm_verity_prefetch_work, work);
	काष्ठा dm_verity *v = pw->v;
	पूर्णांक i;

	क्रम (i = v->levels - 2; i >= 0; i--) अणु
		sector_t hash_block_start;
		sector_t hash_block_end;
		verity_hash_at_level(v, pw->block, i, &hash_block_start, शून्य);
		verity_hash_at_level(v, pw->block + pw->n_blocks - 1, i, &hash_block_end, शून्य);
		अगर (!i) अणु
			अचिन्हित cluster = READ_ONCE(dm_verity_prefetch_cluster);

			cluster >>= v->data_dev_block_bits;
			अगर (unlikely(!cluster))
				जाओ no_prefetch_cluster;

			अगर (unlikely(cluster & (cluster - 1)))
				cluster = 1 << __fls(cluster);

			hash_block_start &= ~(sector_t)(cluster - 1);
			hash_block_end |= cluster - 1;
			अगर (unlikely(hash_block_end >= v->hash_blocks))
				hash_block_end = v->hash_blocks - 1;
		पूर्ण
no_prefetch_cluster:
		dm_bufio_prefetch(v->bufio, hash_block_start,
				  hash_block_end - hash_block_start + 1);
	पूर्ण

	kमुक्त(pw);
पूर्ण

अटल व्योम verity_submit_prefetch(काष्ठा dm_verity *v, काष्ठा dm_verity_io *io)
अणु
	sector_t block = io->block;
	अचिन्हित पूर्णांक n_blocks = io->n_blocks;
	काष्ठा dm_verity_prefetch_work *pw;

	अगर (v->validated_blocks) अणु
		जबतक (n_blocks && test_bit(block, v->validated_blocks)) अणु
			block++;
			n_blocks--;
		पूर्ण
		जबतक (n_blocks && test_bit(block + n_blocks - 1,
					    v->validated_blocks))
			n_blocks--;
		अगर (!n_blocks)
			वापस;
	पूर्ण

	pw = kदो_स्मृति(माप(काष्ठा dm_verity_prefetch_work),
		GFP_NOIO | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);

	अगर (!pw)
		वापस;

	INIT_WORK(&pw->work, verity_prefetch_io);
	pw->v = v;
	pw->block = block;
	pw->n_blocks = n_blocks;
	queue_work(v->verअगरy_wq, &pw->work);
पूर्ण

/*
 * Bio map function. It allocates dm_verity_io काष्ठाure and bio vector and
 * fills them. Then it issues prefetches and the I/O.
 */
अटल पूर्णांक verity_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_verity *v = ti->निजी;
	काष्ठा dm_verity_io *io;

	bio_set_dev(bio, v->data_dev->bdev);
	bio->bi_iter.bi_sector = verity_map_sector(v, bio->bi_iter.bi_sector);

	अगर (((अचिन्हित)bio->bi_iter.bi_sector | bio_sectors(bio)) &
	    ((1 << (v->data_dev_block_bits - SECTOR_SHIFT)) - 1)) अणु
		DMERR_LIMIT("unaligned io");
		वापस DM_MAPIO_KILL;
	पूर्ण

	अगर (bio_end_sector(bio) >>
	    (v->data_dev_block_bits - SECTOR_SHIFT) > v->data_blocks) अणु
		DMERR_LIMIT("io out of range");
		वापस DM_MAPIO_KILL;
	पूर्ण

	अगर (bio_data_dir(bio) == WRITE)
		वापस DM_MAPIO_KILL;

	io = dm_per_bio_data(bio, ti->per_io_data_size);
	io->v = v;
	io->orig_bi_end_io = bio->bi_end_io;
	io->block = bio->bi_iter.bi_sector >> (v->data_dev_block_bits - SECTOR_SHIFT);
	io->n_blocks = bio->bi_iter.bi_size >> v->data_dev_block_bits;

	bio->bi_end_io = verity_end_io;
	bio->bi_निजी = io;
	io->iter = bio->bi_iter;

	verity_fec_init_io(io);

	verity_submit_prefetch(v, io);

	submit_bio_noacct(bio);

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

/*
 * Status: V (valid) or C (corruption found)
 */
अटल व्योम verity_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा dm_verity *v = ti->निजी;
	अचिन्हित args = 0;
	अचिन्हित sz = 0;
	अचिन्हित x;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%c", v->hash_failed ? 'C' : 'V');
		अवरोध;
	हाल STATUSTYPE_TABLE:
		DMEMIT("%u %s %s %u %u %llu %llu %s ",
			v->version,
			v->data_dev->name,
			v->hash_dev->name,
			1 << v->data_dev_block_bits,
			1 << v->hash_dev_block_bits,
			(अचिन्हित दीर्घ दीर्घ)v->data_blocks,
			(अचिन्हित दीर्घ दीर्घ)v->hash_start,
			v->alg_name
			);
		क्रम (x = 0; x < v->digest_size; x++)
			DMEMIT("%02x", v->root_digest[x]);
		DMEMIT(" ");
		अगर (!v->salt_size)
			DMEMIT("-");
		अन्यथा
			क्रम (x = 0; x < v->salt_size; x++)
				DMEMIT("%02x", v->salt[x]);
		अगर (v->mode != DM_VERITY_MODE_EIO)
			args++;
		अगर (verity_fec_is_enabled(v))
			args += DM_VERITY_OPTS_FEC;
		अगर (v->zero_digest)
			args++;
		अगर (v->validated_blocks)
			args++;
		अगर (v->signature_key_desc)
			args += DM_VERITY_ROOT_HASH_VERIFICATION_OPTS;
		अगर (!args)
			वापस;
		DMEMIT(" %u", args);
		अगर (v->mode != DM_VERITY_MODE_EIO) अणु
			DMEMIT(" ");
			चयन (v->mode) अणु
			हाल DM_VERITY_MODE_LOGGING:
				DMEMIT(DM_VERITY_OPT_LOGGING);
				अवरोध;
			हाल DM_VERITY_MODE_RESTART:
				DMEMIT(DM_VERITY_OPT_RESTART);
				अवरोध;
			हाल DM_VERITY_MODE_PANIC:
				DMEMIT(DM_VERITY_OPT_PANIC);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
		पूर्ण
		अगर (v->zero_digest)
			DMEMIT(" " DM_VERITY_OPT_IGN_ZEROES);
		अगर (v->validated_blocks)
			DMEMIT(" " DM_VERITY_OPT_AT_MOST_ONCE);
		sz = verity_fec_status_table(v, sz, result, maxlen);
		अगर (v->signature_key_desc)
			DMEMIT(" " DM_VERITY_ROOT_HASH_VERIFICATION_OPT_SIG_KEY
				" %s", v->signature_key_desc);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक verity_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा dm_verity *v = ti->निजी;

	*bdev = v->data_dev->bdev;

	अगर (v->data_start ||
	    ti->len != i_size_पढ़ो(v->data_dev->bdev->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक verity_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dm_verity *v = ti->निजी;

	वापस fn(ti, v->data_dev, v->data_start, ti->len, data);
पूर्ण

अटल व्योम verity_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_verity *v = ti->निजी;

	अगर (limits->logical_block_size < 1 << v->data_dev_block_bits)
		limits->logical_block_size = 1 << v->data_dev_block_bits;

	अगर (limits->physical_block_size < 1 << v->data_dev_block_bits)
		limits->physical_block_size = 1 << v->data_dev_block_bits;

	blk_limits_io_min(limits, limits->logical_block_size);
पूर्ण

अटल व्योम verity_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_verity *v = ti->निजी;

	अगर (v->verअगरy_wq)
		destroy_workqueue(v->verअगरy_wq);

	अगर (v->bufio)
		dm_bufio_client_destroy(v->bufio);

	kvमुक्त(v->validated_blocks);
	kमुक्त(v->salt);
	kमुक्त(v->root_digest);
	kमुक्त(v->zero_digest);

	अगर (v->tfm)
		crypto_मुक्त_ahash(v->tfm);

	kमुक्त(v->alg_name);

	अगर (v->hash_dev)
		dm_put_device(ti, v->hash_dev);

	अगर (v->data_dev)
		dm_put_device(ti, v->data_dev);

	verity_fec_dtr(v);

	kमुक्त(v->signature_key_desc);

	kमुक्त(v);
पूर्ण

अटल पूर्णांक verity_alloc_most_once(काष्ठा dm_verity *v)
अणु
	काष्ठा dm_target *ti = v->ti;

	/* the bitset can only handle पूर्णांक_उच्च blocks */
	अगर (v->data_blocks > पूर्णांक_उच्च) अणु
		ti->error = "device too large to use check_at_most_once";
		वापस -E2BIG;
	पूर्ण

	v->validated_blocks = kvसुस्मृति(BITS_TO_LONGS(v->data_blocks),
				       माप(अचिन्हित दीर्घ),
				       GFP_KERNEL);
	अगर (!v->validated_blocks) अणु
		ti->error = "failed to allocate bitset for check_at_most_once";
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक verity_alloc_zero_digest(काष्ठा dm_verity *v)
अणु
	पूर्णांक r = -ENOMEM;
	काष्ठा ahash_request *req;
	u8 *zero_data;

	v->zero_digest = kदो_स्मृति(v->digest_size, GFP_KERNEL);

	अगर (!v->zero_digest)
		वापस r;

	req = kदो_स्मृति(v->ahash_reqsize, GFP_KERNEL);

	अगर (!req)
		वापस r; /* verity_dtr will मुक्त zero_digest */

	zero_data = kzalloc(1 << v->data_dev_block_bits, GFP_KERNEL);

	अगर (!zero_data)
		जाओ out;

	r = verity_hash(v, req, zero_data, 1 << v->data_dev_block_bits,
			v->zero_digest);

out:
	kमुक्त(req);
	kमुक्त(zero_data);

	वापस r;
पूर्ण

अटल अंतरभूत bool verity_is_verity_mode(स्थिर अक्षर *arg_name)
अणु
	वापस (!strहालcmp(arg_name, DM_VERITY_OPT_LOGGING) ||
		!strहालcmp(arg_name, DM_VERITY_OPT_RESTART) ||
		!strहालcmp(arg_name, DM_VERITY_OPT_PANIC));
पूर्ण

अटल पूर्णांक verity_parse_verity_mode(काष्ठा dm_verity *v, स्थिर अक्षर *arg_name)
अणु
	अगर (v->mode)
		वापस -EINVAL;

	अगर (!strहालcmp(arg_name, DM_VERITY_OPT_LOGGING))
		v->mode = DM_VERITY_MODE_LOGGING;
	अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_RESTART))
		v->mode = DM_VERITY_MODE_RESTART;
	अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_PANIC))
		v->mode = DM_VERITY_MODE_PANIC;

	वापस 0;
पूर्ण

अटल पूर्णांक verity_parse_opt_args(काष्ठा dm_arg_set *as, काष्ठा dm_verity *v,
				 काष्ठा dm_verity_sig_opts *verअगरy_args)
अणु
	पूर्णांक r;
	अचिन्हित argc;
	काष्ठा dm_target *ti = v->ti;
	स्थिर अक्षर *arg_name;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, DM_VERITY_OPTS_MAX, "Invalid number of feature args"पूर्ण,
	पूर्ण;

	r = dm_पढ़ो_arg_group(_args, as, &argc, &ti->error);
	अगर (r)
		वापस -EINVAL;

	अगर (!argc)
		वापस 0;

	करो अणु
		arg_name = dm_shअगरt_arg(as);
		argc--;

		अगर (verity_is_verity_mode(arg_name)) अणु
			r = verity_parse_verity_mode(v, arg_name);
			अगर (r) अणु
				ti->error = "Conflicting error handling parameters";
				वापस r;
			पूर्ण
			जारी;

		पूर्ण अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_IGN_ZEROES)) अणु
			r = verity_alloc_zero_digest(v);
			अगर (r) अणु
				ti->error = "Cannot allocate zero digest";
				वापस r;
			पूर्ण
			जारी;

		पूर्ण अन्यथा अगर (!strहालcmp(arg_name, DM_VERITY_OPT_AT_MOST_ONCE)) अणु
			r = verity_alloc_most_once(v);
			अगर (r)
				वापस r;
			जारी;

		पूर्ण अन्यथा अगर (verity_is_fec_opt_arg(arg_name)) अणु
			r = verity_fec_parse_opt_args(as, v, &argc, arg_name);
			अगर (r)
				वापस r;
			जारी;
		पूर्ण अन्यथा अगर (verity_verअगरy_is_sig_opt_arg(arg_name)) अणु
			r = verity_verअगरy_sig_parse_opt_args(as, v,
							     verअगरy_args,
							     &argc, arg_name);
			अगर (r)
				वापस r;
			जारी;

		पूर्ण

		ti->error = "Unrecognized verity feature request";
		वापस -EINVAL;
	पूर्ण जबतक (argc && !r);

	वापस r;
पूर्ण

/*
 * Target parameters:
 *	<version>	The current क्रमmat is version 1.
 *			Vsn 0 is compatible with original Chromium OS releases.
 *	<data device>
 *	<hash device>
 *	<data block size>
 *	<hash block size>
 *	<the number of data blocks>
 *	<hash start block>
 *	<algorithm>
 *	<digest>
 *	<salt>		Hex string or "-" अगर no salt.
 */
अटल पूर्णांक verity_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा dm_verity *v;
	काष्ठा dm_verity_sig_opts verअगरy_args = अणु0पूर्ण;
	काष्ठा dm_arg_set as;
	अचिन्हित पूर्णांक num;
	अचिन्हित दीर्घ दीर्घ num_ll;
	पूर्णांक r;
	पूर्णांक i;
	sector_t hash_position;
	अक्षर dummy;
	अक्षर *root_hash_digest_to_validate;

	v = kzalloc(माप(काष्ठा dm_verity), GFP_KERNEL);
	अगर (!v) अणु
		ti->error = "Cannot allocate verity structure";
		वापस -ENOMEM;
	पूर्ण
	ti->निजी = v;
	v->ti = ti;

	r = verity_fec_ctr_alloc(v);
	अगर (r)
		जाओ bad;

	अगर ((dm_table_get_mode(ti->table) & ~FMODE_READ)) अणु
		ti->error = "Device must be readonly";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (argc < 10) अणु
		ti->error = "Not enough arguments";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (माला_पूछो(argv[0], "%u%c", &num, &dummy) != 1 ||
	    num > 1) अणु
		ti->error = "Invalid version";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->version = num;

	r = dm_get_device(ti, argv[1], FMODE_READ, &v->data_dev);
	अगर (r) अणु
		ti->error = "Data device lookup failed";
		जाओ bad;
	पूर्ण

	r = dm_get_device(ti, argv[2], FMODE_READ, &v->hash_dev);
	अगर (r) अणु
		ti->error = "Hash device lookup failed";
		जाओ bad;
	पूर्ण

	अगर (माला_पूछो(argv[3], "%u%c", &num, &dummy) != 1 ||
	    !num || (num & (num - 1)) ||
	    num < bdev_logical_block_size(v->data_dev->bdev) ||
	    num > PAGE_SIZE) अणु
		ti->error = "Invalid data device block size";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->data_dev_block_bits = __ffs(num);

	अगर (माला_पूछो(argv[4], "%u%c", &num, &dummy) != 1 ||
	    !num || (num & (num - 1)) ||
	    num < bdev_logical_block_size(v->hash_dev->bdev) ||
	    num > पूर्णांक_उच्च) अणु
		ti->error = "Invalid hash device block size";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->hash_dev_block_bits = __ffs(num);

	अगर (माला_पूछो(argv[5], "%llu%c", &num_ll, &dummy) != 1 ||
	    (sector_t)(num_ll << (v->data_dev_block_bits - SECTOR_SHIFT))
	    >> (v->data_dev_block_bits - SECTOR_SHIFT) != num_ll) अणु
		ti->error = "Invalid data blocks";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->data_blocks = num_ll;

	अगर (ti->len > (v->data_blocks << (v->data_dev_block_bits - SECTOR_SHIFT))) अणु
		ti->error = "Data device is too small";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (माला_पूछो(argv[6], "%llu%c", &num_ll, &dummy) != 1 ||
	    (sector_t)(num_ll << (v->hash_dev_block_bits - SECTOR_SHIFT))
	    >> (v->hash_dev_block_bits - SECTOR_SHIFT) != num_ll) अणु
		ti->error = "Invalid hash start";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->hash_start = num_ll;

	v->alg_name = kstrdup(argv[7], GFP_KERNEL);
	अगर (!v->alg_name) अणु
		ti->error = "Cannot allocate algorithm name";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	v->tfm = crypto_alloc_ahash(v->alg_name, 0, 0);
	अगर (IS_ERR(v->tfm)) अणु
		ti->error = "Cannot initialize hash function";
		r = PTR_ERR(v->tfm);
		v->tfm = शून्य;
		जाओ bad;
	पूर्ण

	/*
	 * dm-verity perक्रमmance can vary greatly depending on which hash
	 * algorithm implementation is used.  Help people debug perक्रमmance
	 * problems by logging the ->cra_driver_name.
	 */
	DMINFO("%s using implementation \"%s\"", v->alg_name,
	       crypto_hash_alg_common(v->tfm)->base.cra_driver_name);

	v->digest_size = crypto_ahash_digestsize(v->tfm);
	अगर ((1 << v->hash_dev_block_bits) < v->digest_size * 2) अणु
		ti->error = "Digest size too big";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	v->ahash_reqsize = माप(काष्ठा ahash_request) +
		crypto_ahash_reqsize(v->tfm);

	v->root_digest = kदो_स्मृति(v->digest_size, GFP_KERNEL);
	अगर (!v->root_digest) अणु
		ti->error = "Cannot allocate root digest";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	अगर (म_माप(argv[8]) != v->digest_size * 2 ||
	    hex2bin(v->root_digest, argv[8], v->digest_size)) अणु
		ti->error = "Invalid root digest";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	root_hash_digest_to_validate = argv[8];

	अगर (म_भेद(argv[9], "-")) अणु
		v->salt_size = म_माप(argv[9]) / 2;
		v->salt = kदो_स्मृति(v->salt_size, GFP_KERNEL);
		अगर (!v->salt) अणु
			ti->error = "Cannot allocate salt";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		अगर (म_माप(argv[9]) != v->salt_size * 2 ||
		    hex2bin(v->salt, argv[9], v->salt_size)) अणु
			ti->error = "Invalid salt";
			r = -EINVAL;
			जाओ bad;
		पूर्ण
	पूर्ण

	argv += 10;
	argc -= 10;

	/* Optional parameters */
	अगर (argc) अणु
		as.argc = argc;
		as.argv = argv;

		r = verity_parse_opt_args(&as, v, &verअगरy_args);
		अगर (r < 0)
			जाओ bad;
	पूर्ण

	/* Root hash signature is  a optional parameter*/
	r = verity_verअगरy_root_hash(root_hash_digest_to_validate,
				    म_माप(root_hash_digest_to_validate),
				    verअगरy_args.sig,
				    verअगरy_args.sig_size);
	अगर (r < 0) अणु
		ti->error = "Root hash verification failed";
		जाओ bad;
	पूर्ण
	v->hash_per_block_bits =
		__fls((1 << v->hash_dev_block_bits) / v->digest_size);

	v->levels = 0;
	अगर (v->data_blocks)
		जबतक (v->hash_per_block_bits * v->levels < 64 &&
		       (अचिन्हित दीर्घ दीर्घ)(v->data_blocks - 1) >>
		       (v->hash_per_block_bits * v->levels))
			v->levels++;

	अगर (v->levels > DM_VERITY_MAX_LEVELS) अणु
		ti->error = "Too many tree levels";
		r = -E2BIG;
		जाओ bad;
	पूर्ण

	hash_position = v->hash_start;
	क्रम (i = v->levels - 1; i >= 0; i--) अणु
		sector_t s;
		v->hash_level_block[i] = hash_position;
		s = (v->data_blocks + ((sector_t)1 << ((i + 1) * v->hash_per_block_bits)) - 1)
					>> ((i + 1) * v->hash_per_block_bits);
		अगर (hash_position + s < hash_position) अणु
			ti->error = "Hash device offset overflow";
			r = -E2BIG;
			जाओ bad;
		पूर्ण
		hash_position += s;
	पूर्ण
	v->hash_blocks = hash_position;

	v->bufio = dm_bufio_client_create(v->hash_dev->bdev,
		1 << v->hash_dev_block_bits, 1, माप(काष्ठा buffer_aux),
		dm_bufio_alloc_callback, शून्य);
	अगर (IS_ERR(v->bufio)) अणु
		ti->error = "Cannot initialize dm-bufio";
		r = PTR_ERR(v->bufio);
		v->bufio = शून्य;
		जाओ bad;
	पूर्ण

	अगर (dm_bufio_get_device_size(v->bufio) < v->hash_blocks) अणु
		ti->error = "Hash device is too small";
		r = -E2BIG;
		जाओ bad;
	पूर्ण

	/* WQ_UNBOUND greatly improves perक्रमmance when running on ramdisk */
	v->verअगरy_wq = alloc_workqueue("kverityd", WQ_CPU_INTENSIVE | WQ_MEM_RECLAIM | WQ_UNBOUND, num_online_cpus());
	अगर (!v->verअगरy_wq) अणु
		ti->error = "Cannot allocate workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	ti->per_io_data_size = माप(काष्ठा dm_verity_io) +
				v->ahash_reqsize + v->digest_size * 2;

	r = verity_fec_ctr(v);
	अगर (r)
		जाओ bad;

	ti->per_io_data_size = roundup(ti->per_io_data_size,
				       __alignof__(काष्ठा dm_verity_io));

	verity_verअगरy_sig_opts_cleanup(&verअगरy_args);

	वापस 0;

bad:

	verity_verअगरy_sig_opts_cleanup(&verअगरy_args);
	verity_dtr(ti);

	वापस r;
पूर्ण

अटल काष्ठा target_type verity_target = अणु
	.name		= "verity",
	.version	= अणु1, 8, 0पूर्ण,
	.module		= THIS_MODULE,
	.ctr		= verity_ctr,
	.dtr		= verity_dtr,
	.map		= verity_map,
	.status		= verity_status,
	.prepare_ioctl	= verity_prepare_ioctl,
	.iterate_devices = verity_iterate_devices,
	.io_hपूर्णांकs	= verity_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_verity_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&verity_target);
	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_verity_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&verity_target);
पूर्ण

module_init(dm_verity_init);
module_निकास(dm_verity_निकास);

MODULE_AUTHOR("Mikulas Patocka <mpatocka@redhat.com>");
MODULE_AUTHOR("Mandeep Baines <msb@chromium.org>");
MODULE_AUTHOR("Will Drewry <wad@chromium.org>");
MODULE_DESCRIPTION(DM_NAME " target for transparent disk integrity checking");
MODULE_LICENSE("GPL");
