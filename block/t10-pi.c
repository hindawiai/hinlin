<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * t10_pi.c - Functions क्रम generating and verअगरying T10 Protection
 *	      Inक्रमmation.
 */

#समावेश <linux/t10-pi.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/module.h>
#समावेश <net/checksum.h>

प्रकार __be16 (csum_fn) (व्योम *, अचिन्हित पूर्णांक);

अटल __be16 t10_pi_crc_fn(व्योम *data, अचिन्हित पूर्णांक len)
अणु
	वापस cpu_to_be16(crc_t10dअगर(data, len));
पूर्ण

अटल __be16 t10_pi_ip_fn(व्योम *data, अचिन्हित पूर्णांक len)
अणु
	वापस (__क्रमce __be16)ip_compute_csum(data, len);
पूर्ण

/*
 * Type 1 and Type 2 protection use the same क्रमmat: 16 bit guard tag,
 * 16 bit app tag, 32 bit reference tag. Type 3 करोes not define the ref
 * tag.
 */
अटल blk_status_t t10_pi_generate(काष्ठा blk_पूर्णांकegrity_iter *iter,
		csum_fn *fn, क्रमागत t10_dअगर_type type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0 ; i < iter->data_size ; i += iter->पूर्णांकerval) अणु
		काष्ठा t10_pi_tuple *pi = iter->prot_buf;

		pi->guard_tag = fn(iter->data_buf, iter->पूर्णांकerval);
		pi->app_tag = 0;

		अगर (type == T10_PI_TYPE1_PROTECTION)
			pi->ref_tag = cpu_to_be32(lower_32_bits(iter->seed));
		अन्यथा
			pi->ref_tag = 0;

		iter->data_buf += iter->पूर्णांकerval;
		iter->prot_buf += माप(काष्ठा t10_pi_tuple);
		iter->seed++;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t t10_pi_verअगरy(काष्ठा blk_पूर्णांकegrity_iter *iter,
		csum_fn *fn, क्रमागत t10_dअगर_type type)
अणु
	अचिन्हित पूर्णांक i;

	BUG_ON(type == T10_PI_TYPE0_PROTECTION);

	क्रम (i = 0 ; i < iter->data_size ; i += iter->पूर्णांकerval) अणु
		काष्ठा t10_pi_tuple *pi = iter->prot_buf;
		__be16 csum;

		अगर (type == T10_PI_TYPE1_PROTECTION ||
		    type == T10_PI_TYPE2_PROTECTION) अणु
			अगर (pi->app_tag == T10_PI_APP_ESCAPE)
				जाओ next;

			अगर (be32_to_cpu(pi->ref_tag) !=
			    lower_32_bits(iter->seed)) अणु
				pr_err("%s: ref tag error at location %llu " \
				       "(rcvd %u)\n", iter->disk_name,
				       (अचिन्हित दीर्घ दीर्घ)
				       iter->seed, be32_to_cpu(pi->ref_tag));
				वापस BLK_STS_PROTECTION;
			पूर्ण
		पूर्ण अन्यथा अगर (type == T10_PI_TYPE3_PROTECTION) अणु
			अगर (pi->app_tag == T10_PI_APP_ESCAPE &&
			    pi->ref_tag == T10_PI_REF_ESCAPE)
				जाओ next;
		पूर्ण

		csum = fn(iter->data_buf, iter->पूर्णांकerval);

		अगर (pi->guard_tag != csum) अणु
			pr_err("%s: guard tag error at sector %llu " \
			       "(rcvd %04x, want %04x)\n", iter->disk_name,
			       (अचिन्हित दीर्घ दीर्घ)iter->seed,
			       be16_to_cpu(pi->guard_tag), be16_to_cpu(csum));
			वापस BLK_STS_PROTECTION;
		पूर्ण

next:
		iter->data_buf += iter->पूर्णांकerval;
		iter->prot_buf += माप(काष्ठा t10_pi_tuple);
		iter->seed++;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t t10_pi_type1_generate_crc(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_generate(iter, t10_pi_crc_fn, T10_PI_TYPE1_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type1_generate_ip(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_generate(iter, t10_pi_ip_fn, T10_PI_TYPE1_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type1_verअगरy_crc(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_verअगरy(iter, t10_pi_crc_fn, T10_PI_TYPE1_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type1_verअगरy_ip(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_verअगरy(iter, t10_pi_ip_fn, T10_PI_TYPE1_PROTECTION);
पूर्ण

/**
 * t10_pi_type1_prepare - prepare PI prior submitting request to device
 * @rq:              request with PI that should be prepared
 *
 * For Type 1/Type 2, the भव start sector is the one that was
 * originally submitted by the block layer क्रम the ref_tag usage. Due to
 * partitioning, MD/DM cloning, etc. the actual physical start sector is
 * likely to be dअगरferent. Remap protection inक्रमmation to match the
 * physical LBA.
 */
अटल व्योम t10_pi_type1_prepare(काष्ठा request *rq)
अणु
	स्थिर पूर्णांक tuple_sz = rq->q->पूर्णांकegrity.tuple_size;
	u32 ref_tag = t10_pi_ref_tag(rq);
	काष्ठा bio *bio;

	__rq_क्रम_each_bio(bio, rq) अणु
		काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
		u32 virt = bip_get_seed(bip) & 0xffffffff;
		काष्ठा bio_vec iv;
		काष्ठा bvec_iter iter;

		/* Alपढ़ोy remapped? */
		अगर (bip->bip_flags & BIP_MAPPED_INTEGRITY)
			अवरोध;

		bip_क्रम_each_vec(iv, bip, iter) अणु
			व्योम *p, *pmap;
			अचिन्हित पूर्णांक j;

			pmap = kmap_atomic(iv.bv_page);
			p = pmap + iv.bv_offset;
			क्रम (j = 0; j < iv.bv_len; j += tuple_sz) अणु
				काष्ठा t10_pi_tuple *pi = p;

				अगर (be32_to_cpu(pi->ref_tag) == virt)
					pi->ref_tag = cpu_to_be32(ref_tag);
				virt++;
				ref_tag++;
				p += tuple_sz;
			पूर्ण

			kunmap_atomic(pmap);
		पूर्ण

		bip->bip_flags |= BIP_MAPPED_INTEGRITY;
	पूर्ण
पूर्ण

/**
 * t10_pi_type1_complete - prepare PI prior वापसing request to the blk layer
 * @rq:              request with PI that should be prepared
 * @nr_bytes:        total bytes to prepare
 *
 * For Type 1/Type 2, the भव start sector is the one that was
 * originally submitted by the block layer क्रम the ref_tag usage. Due to
 * partitioning, MD/DM cloning, etc. the actual physical start sector is
 * likely to be dअगरferent. Since the physical start sector was submitted
 * to the device, we should remap it back to भव values expected by the
 * block layer.
 */
अटल व्योम t10_pi_type1_complete(काष्ठा request *rq, अचिन्हित पूर्णांक nr_bytes)
अणु
	अचिन्हित पूर्णांकervals = nr_bytes >> rq->q->पूर्णांकegrity.पूर्णांकerval_exp;
	स्थिर पूर्णांक tuple_sz = rq->q->पूर्णांकegrity.tuple_size;
	u32 ref_tag = t10_pi_ref_tag(rq);
	काष्ठा bio *bio;

	__rq_क्रम_each_bio(bio, rq) अणु
		काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
		u32 virt = bip_get_seed(bip) & 0xffffffff;
		काष्ठा bio_vec iv;
		काष्ठा bvec_iter iter;

		bip_क्रम_each_vec(iv, bip, iter) अणु
			व्योम *p, *pmap;
			अचिन्हित पूर्णांक j;

			pmap = kmap_atomic(iv.bv_page);
			p = pmap + iv.bv_offset;
			क्रम (j = 0; j < iv.bv_len && पूर्णांकervals; j += tuple_sz) अणु
				काष्ठा t10_pi_tuple *pi = p;

				अगर (be32_to_cpu(pi->ref_tag) == ref_tag)
					pi->ref_tag = cpu_to_be32(virt);
				virt++;
				ref_tag++;
				पूर्णांकervals--;
				p += tuple_sz;
			पूर्ण

			kunmap_atomic(pmap);
		पूर्ण
	पूर्ण
पूर्ण

अटल blk_status_t t10_pi_type3_generate_crc(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_generate(iter, t10_pi_crc_fn, T10_PI_TYPE3_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type3_generate_ip(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_generate(iter, t10_pi_ip_fn, T10_PI_TYPE3_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type3_verअगरy_crc(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_verअगरy(iter, t10_pi_crc_fn, T10_PI_TYPE3_PROTECTION);
पूर्ण

अटल blk_status_t t10_pi_type3_verअगरy_ip(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस t10_pi_verअगरy(iter, t10_pi_ip_fn, T10_PI_TYPE3_PROTECTION);
पूर्ण

/* Type 3 करोes not have a reference tag so no remapping is required. */
अटल व्योम t10_pi_type3_prepare(काष्ठा request *rq)
अणु
पूर्ण

/* Type 3 करोes not have a reference tag so no remapping is required. */
अटल व्योम t10_pi_type3_complete(काष्ठा request *rq, अचिन्हित पूर्णांक nr_bytes)
अणु
पूर्ण

स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type1_crc = अणु
	.name			= "T10-DIF-TYPE1-CRC",
	.generate_fn		= t10_pi_type1_generate_crc,
	.verअगरy_fn		= t10_pi_type1_verअगरy_crc,
	.prepare_fn		= t10_pi_type1_prepare,
	.complete_fn		= t10_pi_type1_complete,
पूर्ण;
EXPORT_SYMBOL(t10_pi_type1_crc);

स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type1_ip = अणु
	.name			= "T10-DIF-TYPE1-IP",
	.generate_fn		= t10_pi_type1_generate_ip,
	.verअगरy_fn		= t10_pi_type1_verअगरy_ip,
	.prepare_fn		= t10_pi_type1_prepare,
	.complete_fn		= t10_pi_type1_complete,
पूर्ण;
EXPORT_SYMBOL(t10_pi_type1_ip);

स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type3_crc = अणु
	.name			= "T10-DIF-TYPE3-CRC",
	.generate_fn		= t10_pi_type3_generate_crc,
	.verअगरy_fn		= t10_pi_type3_verअगरy_crc,
	.prepare_fn		= t10_pi_type3_prepare,
	.complete_fn		= t10_pi_type3_complete,
पूर्ण;
EXPORT_SYMBOL(t10_pi_type3_crc);

स्थिर काष्ठा blk_पूर्णांकegrity_profile t10_pi_type3_ip = अणु
	.name			= "T10-DIF-TYPE3-IP",
	.generate_fn		= t10_pi_type3_generate_ip,
	.verअगरy_fn		= t10_pi_type3_verअगरy_ip,
	.prepare_fn		= t10_pi_type3_prepare,
	.complete_fn		= t10_pi_type3_complete,
पूर्ण;
EXPORT_SYMBOL(t10_pi_type3_ip);

MODULE_LICENSE("GPL");
