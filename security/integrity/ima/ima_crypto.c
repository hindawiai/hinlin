<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * File: ima_crypto.c
 *	Calculates md5/sha1 file hash, ढाँचा hash, boot-aggreate hash
 */

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/file.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <crypto/hash.h>

#समावेश "ima.h"

/* minimum file size क्रम ahash use */
अटल अचिन्हित दीर्घ ima_ahash_minsize;
module_param_named(ahash_minsize, ima_ahash_minsize, uदीर्घ, 0644);
MODULE_PARM_DESC(ahash_minsize, "Minimum file size for ahash use");

/* शेष is 0 - 1 page. */
अटल पूर्णांक ima_maxorder;
अटल अचिन्हित पूर्णांक ima_bufsize = PAGE_SIZE;

अटल पूर्णांक param_set_bufsize(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	पूर्णांक order;

	size = memparse(val, शून्य);
	order = get_order(size);
	अगर (order >= MAX_ORDER)
		वापस -EINVAL;
	ima_maxorder = order;
	ima_bufsize = PAGE_SIZE << order;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_bufsize = अणु
	.set = param_set_bufsize,
	.get = param_get_uपूर्णांक,
पूर्ण;
#घोषणा param_check_bufsize(name, p) __param_check(name, p, अचिन्हित पूर्णांक)

module_param_named(ahash_bufsize, ima_bufsize, bufsize, 0644);
MODULE_PARM_DESC(ahash_bufsize, "Maximum ahash buffer size");

अटल काष्ठा crypto_shash *ima_shash_tfm;
अटल काष्ठा crypto_ahash *ima_ahash_tfm;

काष्ठा ima_algo_desc अणु
	काष्ठा crypto_shash *tfm;
	क्रमागत hash_algo algo;
पूर्ण;

पूर्णांक ima_sha1_idx __ro_after_init;
पूर्णांक ima_hash_algo_idx __ro_after_init;
/*
 * Additional number of slots reserved, as needed, क्रम SHA1
 * and IMA शेष algo.
 */
पूर्णांक ima_extra_slots __ro_after_init;

अटल काष्ठा ima_algo_desc *ima_algo_array;

अटल पूर्णांक __init ima_init_ima_crypto(व्योम)
अणु
	दीर्घ rc;

	ima_shash_tfm = crypto_alloc_shash(hash_algo_name[ima_hash_algo], 0, 0);
	अगर (IS_ERR(ima_shash_tfm)) अणु
		rc = PTR_ERR(ima_shash_tfm);
		pr_err("Can not allocate %s (reason: %ld)\n",
		       hash_algo_name[ima_hash_algo], rc);
		वापस rc;
	पूर्ण
	pr_info("Allocated hash algorithm: %s\n",
		hash_algo_name[ima_hash_algo]);
	वापस 0;
पूर्ण

अटल काष्ठा crypto_shash *ima_alloc_tfm(क्रमागत hash_algo algo)
अणु
	काष्ठा crypto_shash *tfm = ima_shash_tfm;
	पूर्णांक rc, i;

	अगर (algo < 0 || algo >= HASH_ALGO__LAST)
		algo = ima_hash_algo;

	अगर (algo == ima_hash_algo)
		वापस tfm;

	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip) + ima_extra_slots; i++)
		अगर (ima_algo_array[i].tfm && ima_algo_array[i].algo == algo)
			वापस ima_algo_array[i].tfm;

	tfm = crypto_alloc_shash(hash_algo_name[algo], 0, 0);
	अगर (IS_ERR(tfm)) अणु
		rc = PTR_ERR(tfm);
		pr_err("Can not allocate %s (reason: %d)\n",
		       hash_algo_name[algo], rc);
	पूर्ण
	वापस tfm;
पूर्ण

पूर्णांक __init ima_init_crypto(व्योम)
अणु
	क्रमागत hash_algo algo;
	दीर्घ rc;
	पूर्णांक i;

	rc = ima_init_ima_crypto();
	अगर (rc)
		वापस rc;

	ima_sha1_idx = -1;
	ima_hash_algo_idx = -1;

	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip); i++) अणु
		algo = ima_tpm_chip->allocated_banks[i].crypto_id;
		अगर (algo == HASH_ALGO_SHA1)
			ima_sha1_idx = i;

		अगर (algo == ima_hash_algo)
			ima_hash_algo_idx = i;
	पूर्ण

	अगर (ima_sha1_idx < 0) अणु
		ima_sha1_idx = NR_BANKS(ima_tpm_chip) + ima_extra_slots++;
		अगर (ima_hash_algo == HASH_ALGO_SHA1)
			ima_hash_algo_idx = ima_sha1_idx;
	पूर्ण

	अगर (ima_hash_algo_idx < 0)
		ima_hash_algo_idx = NR_BANKS(ima_tpm_chip) + ima_extra_slots++;

	ima_algo_array = kसुस्मृति(NR_BANKS(ima_tpm_chip) + ima_extra_slots,
				 माप(*ima_algo_array), GFP_KERNEL);
	अगर (!ima_algo_array) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip); i++) अणु
		algo = ima_tpm_chip->allocated_banks[i].crypto_id;
		ima_algo_array[i].algo = algo;

		/* unknown TPM algorithm */
		अगर (algo == HASH_ALGO__LAST)
			जारी;

		अगर (algo == ima_hash_algo) अणु
			ima_algo_array[i].tfm = ima_shash_tfm;
			जारी;
		पूर्ण

		ima_algo_array[i].tfm = ima_alloc_tfm(algo);
		अगर (IS_ERR(ima_algo_array[i].tfm)) अणु
			अगर (algo == HASH_ALGO_SHA1) अणु
				rc = PTR_ERR(ima_algo_array[i].tfm);
				ima_algo_array[i].tfm = शून्य;
				जाओ out_array;
			पूर्ण

			ima_algo_array[i].tfm = शून्य;
		पूर्ण
	पूर्ण

	अगर (ima_sha1_idx >= NR_BANKS(ima_tpm_chip)) अणु
		अगर (ima_hash_algo == HASH_ALGO_SHA1) अणु
			ima_algo_array[ima_sha1_idx].tfm = ima_shash_tfm;
		पूर्ण अन्यथा अणु
			ima_algo_array[ima_sha1_idx].tfm =
						ima_alloc_tfm(HASH_ALGO_SHA1);
			अगर (IS_ERR(ima_algo_array[ima_sha1_idx].tfm)) अणु
				rc = PTR_ERR(ima_algo_array[ima_sha1_idx].tfm);
				जाओ out_array;
			पूर्ण
		पूर्ण

		ima_algo_array[ima_sha1_idx].algo = HASH_ALGO_SHA1;
	पूर्ण

	अगर (ima_hash_algo_idx >= NR_BANKS(ima_tpm_chip) &&
	    ima_hash_algo_idx != ima_sha1_idx) अणु
		ima_algo_array[ima_hash_algo_idx].tfm = ima_shash_tfm;
		ima_algo_array[ima_hash_algo_idx].algo = ima_hash_algo;
	पूर्ण

	वापस 0;
out_array:
	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip) + ima_extra_slots; i++) अणु
		अगर (!ima_algo_array[i].tfm ||
		    ima_algo_array[i].tfm == ima_shash_tfm)
			जारी;

		crypto_मुक्त_shash(ima_algo_array[i].tfm);
	पूर्ण
out:
	crypto_मुक्त_shash(ima_shash_tfm);
	वापस rc;
पूर्ण

अटल व्योम ima_मुक्त_tfm(काष्ठा crypto_shash *tfm)
अणु
	पूर्णांक i;

	अगर (tfm == ima_shash_tfm)
		वापस;

	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip) + ima_extra_slots; i++)
		अगर (ima_algo_array[i].tfm == tfm)
			वापस;

	crypto_मुक्त_shash(tfm);
पूर्ण

/**
 * ima_alloc_pages() - Allocate contiguous pages.
 * @max_size:       Maximum amount of memory to allocate.
 * @allocated_size: Returned size of actual allocation.
 * @last_warn:      Should the min_size allocation warn or not.
 *
 * Tries to करो opportunistic allocation क्रम memory first trying to allocate
 * max_size amount of memory and then splitting that until zero order is
 * reached. Allocation is tried without generating allocation warnings unless
 * last_warn is set. Last_warn set affects only last allocation of zero order.
 *
 * By शेष, ima_maxorder is 0 and it is equivalent to kदो_स्मृति(GFP_KERNEL)
 *
 * Return poपूर्णांकer to allocated memory, or शून्य on failure.
 */
अटल व्योम *ima_alloc_pages(loff_t max_size, माप_प्रकार *allocated_size,
			     पूर्णांक last_warn)
अणु
	व्योम *ptr;
	पूर्णांक order = ima_maxorder;
	gfp_t gfp_mask = __GFP_RECLAIM | __GFP_NOWARN | __GFP_NORETRY;

	अगर (order)
		order = min(get_order(max_size), order);

	क्रम (; order; order--) अणु
		ptr = (व्योम *)__get_मुक्त_pages(gfp_mask, order);
		अगर (ptr) अणु
			*allocated_size = PAGE_SIZE << order;
			वापस ptr;
		पूर्ण
	पूर्ण

	/* order is zero - one page */

	gfp_mask = GFP_KERNEL;

	अगर (!last_warn)
		gfp_mask |= __GFP_NOWARN;

	ptr = (व्योम *)__get_मुक्त_pages(gfp_mask, 0);
	अगर (ptr) अणु
		*allocated_size = PAGE_SIZE;
		वापस ptr;
	पूर्ण

	*allocated_size = 0;
	वापस शून्य;
पूर्ण

/**
 * ima_मुक्त_pages() - Free pages allocated by ima_alloc_pages().
 * @ptr:  Poपूर्णांकer to allocated pages.
 * @size: Size of allocated buffer.
 */
अटल व्योम ima_मुक्त_pages(व्योम *ptr, माप_प्रकार size)
अणु
	अगर (!ptr)
		वापस;
	मुक्त_pages((अचिन्हित दीर्घ)ptr, get_order(size));
पूर्ण

अटल काष्ठा crypto_ahash *ima_alloc_atfm(क्रमागत hash_algo algo)
अणु
	काष्ठा crypto_ahash *tfm = ima_ahash_tfm;
	पूर्णांक rc;

	अगर (algo < 0 || algo >= HASH_ALGO__LAST)
		algo = ima_hash_algo;

	अगर (algo != ima_hash_algo || !tfm) अणु
		tfm = crypto_alloc_ahash(hash_algo_name[algo], 0, 0);
		अगर (!IS_ERR(tfm)) अणु
			अगर (algo == ima_hash_algo)
				ima_ahash_tfm = tfm;
		पूर्ण अन्यथा अणु
			rc = PTR_ERR(tfm);
			pr_err("Can not allocate %s (reason: %d)\n",
			       hash_algo_name[algo], rc);
		पूर्ण
	पूर्ण
	वापस tfm;
पूर्ण

अटल व्योम ima_मुक्त_atfm(काष्ठा crypto_ahash *tfm)
अणु
	अगर (tfm != ima_ahash_tfm)
		crypto_मुक्त_ahash(tfm);
पूर्ण

अटल अंतरभूत पूर्णांक ahash_रुको(पूर्णांक err, काष्ठा crypto_रुको *रुको)
अणु

	err = crypto_रुको_req(err, रुको);

	अगर (err)
		pr_crit_ratelimited("ahash calculation failed: err: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक ima_calc_file_hash_atfm(काष्ठा file *file,
				   काष्ठा ima_digest_data *hash,
				   काष्ठा crypto_ahash *tfm)
अणु
	loff_t i_size, offset;
	अक्षर *rbuf[2] = अणु शून्य, पूर्ण;
	पूर्णांक rc, rbuf_len, active = 0, ahash_rc = 0;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist sg[1];
	काष्ठा crypto_रुको रुको;
	माप_प्रकार rbuf_size[2];

	hash->length = crypto_ahash_digestsize(tfm);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	crypto_init_रुको(&रुको);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				   CRYPTO_TFM_REQ_MAY_SLEEP,
				   crypto_req_करोne, &रुको);

	rc = ahash_रुको(crypto_ahash_init(req), &रुको);
	अगर (rc)
		जाओ out1;

	i_size = i_size_पढ़ो(file_inode(file));

	अगर (i_size == 0)
		जाओ out2;

	/*
	 * Try to allocate maximum size of memory.
	 * Fail अगर even a single page cannot be allocated.
	 */
	rbuf[0] = ima_alloc_pages(i_size, &rbuf_size[0], 1);
	अगर (!rbuf[0]) अणु
		rc = -ENOMEM;
		जाओ out1;
	पूर्ण

	/* Only allocate one buffer अगर that is enough. */
	अगर (i_size > rbuf_size[0]) अणु
		/*
		 * Try to allocate secondary buffer. If that fails fallback to
		 * using single buffering. Use previous memory allocation size
		 * as baseline क्रम possible allocation size.
		 */
		rbuf[1] = ima_alloc_pages(i_size - rbuf_size[0],
					  &rbuf_size[1], 0);
	पूर्ण

	क्रम (offset = 0; offset < i_size; offset += rbuf_len) अणु
		अगर (!rbuf[1] && offset) अणु
			/* Not using two buffers, and it is not the first
			 * पढ़ो/request, रुको क्रम the completion of the
			 * previous ahash_update() request.
			 */
			rc = ahash_रुको(ahash_rc, &रुको);
			अगर (rc)
				जाओ out3;
		पूर्ण
		/* पढ़ो buffer */
		rbuf_len = min_t(loff_t, i_size - offset, rbuf_size[active]);
		rc = पूर्णांकegrity_kernel_पढ़ो(file, offset, rbuf[active],
					   rbuf_len);
		अगर (rc != rbuf_len) अणु
			अगर (rc >= 0)
				rc = -EINVAL;
			/*
			 * Forward current rc, करो not overग_लिखो with वापस value
			 * from ahash_रुको()
			 */
			ahash_रुको(ahash_rc, &रुको);
			जाओ out3;
		पूर्ण

		अगर (rbuf[1] && offset) अणु
			/* Using two buffers, and it is not the first
			 * पढ़ो/request, रुको क्रम the completion of the
			 * previous ahash_update() request.
			 */
			rc = ahash_रुको(ahash_rc, &रुको);
			अगर (rc)
				जाओ out3;
		पूर्ण

		sg_init_one(&sg[0], rbuf[active], rbuf_len);
		ahash_request_set_crypt(req, sg, शून्य, rbuf_len);

		ahash_rc = crypto_ahash_update(req);

		अगर (rbuf[1])
			active = !active; /* swap buffers, अगर we use two */
	पूर्ण
	/* रुको क्रम the last update request to complete */
	rc = ahash_रुको(ahash_rc, &रुको);
out3:
	ima_मुक्त_pages(rbuf[0], rbuf_size[0]);
	ima_मुक्त_pages(rbuf[1], rbuf_size[1]);
out2:
	अगर (!rc) अणु
		ahash_request_set_crypt(req, शून्य, hash->digest, 0);
		rc = ahash_रुको(crypto_ahash_final(req), &रुको);
	पूर्ण
out1:
	ahash_request_मुक्त(req);
	वापस rc;
पूर्ण

अटल पूर्णांक ima_calc_file_ahash(काष्ठा file *file, काष्ठा ima_digest_data *hash)
अणु
	काष्ठा crypto_ahash *tfm;
	पूर्णांक rc;

	tfm = ima_alloc_atfm(hash->algo);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	rc = ima_calc_file_hash_atfm(file, hash, tfm);

	ima_मुक्त_atfm(tfm);

	वापस rc;
पूर्ण

अटल पूर्णांक ima_calc_file_hash_tfm(काष्ठा file *file,
				  काष्ठा ima_digest_data *hash,
				  काष्ठा crypto_shash *tfm)
अणु
	loff_t i_size, offset = 0;
	अक्षर *rbuf;
	पूर्णांक rc;
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;

	hash->length = crypto_shash_digestsize(tfm);

	rc = crypto_shash_init(shash);
	अगर (rc != 0)
		वापस rc;

	i_size = i_size_पढ़ो(file_inode(file));

	अगर (i_size == 0)
		जाओ out;

	rbuf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!rbuf)
		वापस -ENOMEM;

	जबतक (offset < i_size) अणु
		पूर्णांक rbuf_len;

		rbuf_len = पूर्णांकegrity_kernel_पढ़ो(file, offset, rbuf, PAGE_SIZE);
		अगर (rbuf_len < 0) अणु
			rc = rbuf_len;
			अवरोध;
		पूर्ण
		अगर (rbuf_len == 0) अणु	/* unexpected खातापूर्ण */
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		offset += rbuf_len;

		rc = crypto_shash_update(shash, rbuf, rbuf_len);
		अगर (rc)
			अवरोध;
	पूर्ण
	kमुक्त(rbuf);
out:
	अगर (!rc)
		rc = crypto_shash_final(shash, hash->digest);
	वापस rc;
पूर्ण

अटल पूर्णांक ima_calc_file_shash(काष्ठा file *file, काष्ठा ima_digest_data *hash)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक rc;

	tfm = ima_alloc_tfm(hash->algo);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	rc = ima_calc_file_hash_tfm(file, hash, tfm);

	ima_मुक्त_tfm(tfm);

	वापस rc;
पूर्ण

/*
 * ima_calc_file_hash - calculate file hash
 *
 * Asynchronous hash (ahash) allows using HW acceleration क्रम calculating
 * a hash. ahash perक्रमmance varies क्रम dअगरferent data sizes on dअगरferent
 * crypto accelerators. shash perक्रमmance might be better क्रम smaller files.
 * The 'ima.ahash_minsize' module parameter allows specअगरying the best
 * minimum file size क्रम using ahash on the प्रणाली.
 *
 * If the ima.ahash_minsize parameter is not specअगरied, this function uses
 * shash क्रम the hash calculation.  If ahash fails, it falls back to using
 * shash.
 */
पूर्णांक ima_calc_file_hash(काष्ठा file *file, काष्ठा ima_digest_data *hash)
अणु
	loff_t i_size;
	पूर्णांक rc;
	काष्ठा file *f = file;
	bool new_file_instance = false;

	/*
	 * For consistency, fail file's खोलोed with the O_सूचीECT flag on
	 * fileप्रणालीs mounted with/without DAX option.
	 */
	अगर (file->f_flags & O_सूचीECT) अणु
		hash->length = hash_digest_size[ima_hash_algo];
		hash->algo = ima_hash_algo;
		वापस -EINVAL;
	पूर्ण

	/* Open a new file instance in O_RDONLY अगर we cannot पढ़ो */
	अगर (!(file->f_mode & FMODE_READ)) अणु
		पूर्णांक flags = file->f_flags & ~(O_WRONLY | O_APPEND |
				O_TRUNC | O_CREAT | O_NOCTTY | O_EXCL);
		flags |= O_RDONLY;
		f = dentry_खोलो(&file->f_path, flags, file->f_cred);
		अगर (IS_ERR(f))
			वापस PTR_ERR(f);

		new_file_instance = true;
	पूर्ण

	i_size = i_size_पढ़ो(file_inode(f));

	अगर (ima_ahash_minsize && i_size >= ima_ahash_minsize) अणु
		rc = ima_calc_file_ahash(f, hash);
		अगर (!rc)
			जाओ out;
	पूर्ण

	rc = ima_calc_file_shash(f, hash);
out:
	अगर (new_file_instance)
		fput(f);
	वापस rc;
पूर्ण

/*
 * Calculate the hash of ढाँचा data
 */
अटल पूर्णांक ima_calc_field_array_hash_tfm(काष्ठा ima_field_data *field_data,
					 काष्ठा ima_ढाँचा_entry *entry,
					 पूर्णांक tfm_idx)
अणु
	SHASH_DESC_ON_STACK(shash, ima_algo_array[tfm_idx].tfm);
	काष्ठा ima_ढाँचा_desc *td = entry->ढाँचा_desc;
	पूर्णांक num_fields = entry->ढाँचा_desc->num_fields;
	पूर्णांक rc, i;

	shash->tfm = ima_algo_array[tfm_idx].tfm;

	rc = crypto_shash_init(shash);
	अगर (rc != 0)
		वापस rc;

	क्रम (i = 0; i < num_fields; i++) अणु
		u8 buffer[IMA_EVENT_NAME_LEN_MAX + 1] = अणु 0 पूर्ण;
		u8 *data_to_hash = field_data[i].data;
		u32 datalen = field_data[i].len;
		u32 datalen_to_hash =
		    !ima_canonical_fmt ? datalen : cpu_to_le32(datalen);

		अगर (म_भेद(td->name, IMA_TEMPLATE_IMA_NAME) != 0) अणु
			rc = crypto_shash_update(shash,
						(स्थिर u8 *) &datalen_to_hash,
						माप(datalen_to_hash));
			अगर (rc)
				अवरोध;
		पूर्ण अन्यथा अगर (म_भेद(td->fields[i]->field_id, "n") == 0) अणु
			स_नकल(buffer, data_to_hash, datalen);
			data_to_hash = buffer;
			datalen = IMA_EVENT_NAME_LEN_MAX + 1;
		पूर्ण
		rc = crypto_shash_update(shash, data_to_hash, datalen);
		अगर (rc)
			अवरोध;
	पूर्ण

	अगर (!rc)
		rc = crypto_shash_final(shash, entry->digests[tfm_idx].digest);

	वापस rc;
पूर्ण

पूर्णांक ima_calc_field_array_hash(काष्ठा ima_field_data *field_data,
			      काष्ठा ima_ढाँचा_entry *entry)
अणु
	u16 alg_id;
	पूर्णांक rc, i;

	rc = ima_calc_field_array_hash_tfm(field_data, entry, ima_sha1_idx);
	अगर (rc)
		वापस rc;

	entry->digests[ima_sha1_idx].alg_id = TPM_ALG_SHA1;

	क्रम (i = 0; i < NR_BANKS(ima_tpm_chip) + ima_extra_slots; i++) अणु
		अगर (i == ima_sha1_idx)
			जारी;

		अगर (i < NR_BANKS(ima_tpm_chip)) अणु
			alg_id = ima_tpm_chip->allocated_banks[i].alg_id;
			entry->digests[i].alg_id = alg_id;
		पूर्ण

		/* क्रम unmapped TPM algorithms digest is still a padded SHA1 */
		अगर (!ima_algo_array[i].tfm) अणु
			स_नकल(entry->digests[i].digest,
			       entry->digests[ima_sha1_idx].digest,
			       TPM_DIGEST_SIZE);
			जारी;
		पूर्ण

		rc = ima_calc_field_array_hash_tfm(field_data, entry, i);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक calc_buffer_ahash_atfm(स्थिर व्योम *buf, loff_t len,
				  काष्ठा ima_digest_data *hash,
				  काष्ठा crypto_ahash *tfm)
अणु
	काष्ठा ahash_request *req;
	काष्ठा scatterlist sg;
	काष्ठा crypto_रुको रुको;
	पूर्णांक rc, ahash_rc = 0;

	hash->length = crypto_ahash_digestsize(tfm);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	crypto_init_रुको(&रुको);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG |
				   CRYPTO_TFM_REQ_MAY_SLEEP,
				   crypto_req_करोne, &रुको);

	rc = ahash_रुको(crypto_ahash_init(req), &रुको);
	अगर (rc)
		जाओ out;

	sg_init_one(&sg, buf, len);
	ahash_request_set_crypt(req, &sg, शून्य, len);

	ahash_rc = crypto_ahash_update(req);

	/* रुको क्रम the update request to complete */
	rc = ahash_रुको(ahash_rc, &रुको);
	अगर (!rc) अणु
		ahash_request_set_crypt(req, शून्य, hash->digest, 0);
		rc = ahash_रुको(crypto_ahash_final(req), &रुको);
	पूर्ण
out:
	ahash_request_मुक्त(req);
	वापस rc;
पूर्ण

अटल पूर्णांक calc_buffer_ahash(स्थिर व्योम *buf, loff_t len,
			     काष्ठा ima_digest_data *hash)
अणु
	काष्ठा crypto_ahash *tfm;
	पूर्णांक rc;

	tfm = ima_alloc_atfm(hash->algo);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	rc = calc_buffer_ahash_atfm(buf, len, hash, tfm);

	ima_मुक्त_atfm(tfm);

	वापस rc;
पूर्ण

अटल पूर्णांक calc_buffer_shash_tfm(स्थिर व्योम *buf, loff_t size,
				काष्ठा ima_digest_data *hash,
				काष्ठा crypto_shash *tfm)
अणु
	SHASH_DESC_ON_STACK(shash, tfm);
	अचिन्हित पूर्णांक len;
	पूर्णांक rc;

	shash->tfm = tfm;

	hash->length = crypto_shash_digestsize(tfm);

	rc = crypto_shash_init(shash);
	अगर (rc != 0)
		वापस rc;

	जबतक (size) अणु
		len = size < PAGE_SIZE ? size : PAGE_SIZE;
		rc = crypto_shash_update(shash, buf, len);
		अगर (rc)
			अवरोध;
		buf += len;
		size -= len;
	पूर्ण

	अगर (!rc)
		rc = crypto_shash_final(shash, hash->digest);
	वापस rc;
पूर्ण

अटल पूर्णांक calc_buffer_shash(स्थिर व्योम *buf, loff_t len,
			     काष्ठा ima_digest_data *hash)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक rc;

	tfm = ima_alloc_tfm(hash->algo);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	rc = calc_buffer_shash_tfm(buf, len, hash, tfm);

	ima_मुक्त_tfm(tfm);
	वापस rc;
पूर्ण

पूर्णांक ima_calc_buffer_hash(स्थिर व्योम *buf, loff_t len,
			 काष्ठा ima_digest_data *hash)
अणु
	पूर्णांक rc;

	अगर (ima_ahash_minsize && len >= ima_ahash_minsize) अणु
		rc = calc_buffer_ahash(buf, len, hash);
		अगर (!rc)
			वापस 0;
	पूर्ण

	वापस calc_buffer_shash(buf, len, hash);
पूर्ण

अटल व्योम ima_pcrपढ़ो(u32 idx, काष्ठा tpm_digest *d)
अणु
	अगर (!ima_tpm_chip)
		वापस;

	अगर (tpm_pcr_पढ़ो(ima_tpm_chip, idx, d) != 0)
		pr_err("Error Communicating to TPM chip\n");
पूर्ण

/*
 * The boot_aggregate is a cumulative hash over TPM रेजिस्टरs 0 - 7.  With
 * TPM 1.2 the boot_aggregate was based on पढ़ोing the SHA1 PCRs, but with
 * TPM 2.0 hash agility, TPM chips could support multiple TPM PCR banks,
 * allowing firmware to configure and enable dअगरferent banks.
 *
 * Knowing which TPM bank is पढ़ो to calculate the boot_aggregate digest
 * needs to be conveyed to a verअगरier.  For this reason, use the same
 * hash algorithm क्रम पढ़ोing the TPM PCRs as क्रम calculating the boot
 * aggregate digest as stored in the measurement list.
 */
अटल पूर्णांक ima_calc_boot_aggregate_tfm(अक्षर *digest, u16 alg_id,
				       काष्ठा crypto_shash *tfm)
अणु
	काष्ठा tpm_digest d = अणु .alg_id = alg_id, .digest = अणु0पूर्ण पूर्ण;
	पूर्णांक rc;
	u32 i;
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;

	pr_devel("calculating the boot-aggregate based on TPM bank: %04x\n",
		 d.alg_id);

	rc = crypto_shash_init(shash);
	अगर (rc != 0)
		वापस rc;

	/* cumulative digest over TPM रेजिस्टरs 0-7 */
	क्रम (i = TPM_PCR0; i < TPM_PCR8; i++) अणु
		ima_pcrपढ़ो(i, &d);
		/* now accumulate with current aggregate */
		rc = crypto_shash_update(shash, d.digest,
					 crypto_shash_digestsize(tfm));
		अगर (rc != 0)
			वापस rc;
	पूर्ण
	/*
	 * Extend cumulative digest over TPM रेजिस्टरs 8-9, which contain
	 * measurement क्रम the kernel command line (reg. 8) and image (reg. 9)
	 * in a typical PCR allocation. Registers 8-9 are only included in
	 * non-SHA1 boot_aggregate digests to aव्योम ambiguity.
	 */
	अगर (alg_id != TPM_ALG_SHA1) अणु
		क्रम (i = TPM_PCR8; i < TPM_PCR10; i++) अणु
			ima_pcrपढ़ो(i, &d);
			rc = crypto_shash_update(shash, d.digest,
						crypto_shash_digestsize(tfm));
		पूर्ण
	पूर्ण
	अगर (!rc)
		crypto_shash_final(shash, digest);
	वापस rc;
पूर्ण

पूर्णांक ima_calc_boot_aggregate(काष्ठा ima_digest_data *hash)
अणु
	काष्ठा crypto_shash *tfm;
	u16 crypto_id, alg_id;
	पूर्णांक rc, i, bank_idx = -1;

	क्रम (i = 0; i < ima_tpm_chip->nr_allocated_banks; i++) अणु
		crypto_id = ima_tpm_chip->allocated_banks[i].crypto_id;
		अगर (crypto_id == hash->algo) अणु
			bank_idx = i;
			अवरोध;
		पूर्ण

		अगर (crypto_id == HASH_ALGO_SHA256)
			bank_idx = i;

		अगर (bank_idx == -1 && crypto_id == HASH_ALGO_SHA1)
			bank_idx = i;
	पूर्ण

	अगर (bank_idx == -1) अणु
		pr_err("No suitable TPM algorithm for boot aggregate\n");
		वापस 0;
	पूर्ण

	hash->algo = ima_tpm_chip->allocated_banks[bank_idx].crypto_id;

	tfm = ima_alloc_tfm(hash->algo);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	hash->length = crypto_shash_digestsize(tfm);
	alg_id = ima_tpm_chip->allocated_banks[bank_idx].alg_id;
	rc = ima_calc_boot_aggregate_tfm(hash->digest, alg_id, tfm);

	ima_मुक्त_tfm(tfm);

	वापस rc;
पूर्ण
