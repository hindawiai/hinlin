<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/debugfs.h>

#समावेश "cipher.h"
#समावेश "util.h"

/* offset of SPU_OFIFO_CTRL रेजिस्टर */
#घोषणा SPU_OFIFO_CTRL      0x40
#घोषणा SPU_FIFO_WATERMARK  0x1FF

/**
 * spu_sg_at_offset() - Find the scatterlist entry at a given distance from the
 * start of a scatterlist.
 * @sg:         [in]  Start of a scatterlist
 * @skip:       [in]  Distance from the start of the scatterlist, in bytes
 * @sge:        [out] Scatterlist entry at skip bytes from start
 * @sge_offset: [out] Number of bytes from start of sge buffer to get to
 *                    requested distance.
 *
 * Return: 0 अगर entry found at requested distance
 *         < 0 otherwise
 */
पूर्णांक spu_sg_at_offset(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक skip,
		     काष्ठा scatterlist **sge, अचिन्हित पूर्णांक *sge_offset)
अणु
	/* byte index from start of sg to the end of the previous entry */
	अचिन्हित पूर्णांक index = 0;
	/* byte index from start of sg to the end of the current entry */
	अचिन्हित पूर्णांक next_index;

	next_index = sg->length;
	जबतक (next_index <= skip) अणु
		sg = sg_next(sg);
		index = next_index;
		अगर (!sg)
			वापस -EINVAL;
		next_index += sg->length;
	पूर्ण

	*sge_offset = skip - index;
	*sge = sg;
	वापस 0;
पूर्ण

/* Copy len bytes of sg data, starting at offset skip, to a dest buffer */
व्योम sg_copy_part_to_buf(काष्ठा scatterlist *src, u8 *dest,
			 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक skip)
अणु
	माप_प्रकार copied;
	अचिन्हित पूर्णांक nents = sg_nents(src);

	copied = sg_pcopy_to_buffer(src, nents, dest, len, skip);
	अगर (copied != len) अणु
		flow_log("%s copied %u bytes of %u requested. ",
			 __func__, (u32)copied, len);
		flow_log("sg with %u entries and skip %u\n", nents, skip);
	पूर्ण
पूर्ण

/*
 * Copy data पूर्णांकo a scatterlist starting at a specअगरied offset in the
 * scatterlist. Specअगरically, copy len bytes of data in the buffer src
 * पूर्णांकo the scatterlist dest, starting skip bytes पूर्णांकo the scatterlist.
 */
व्योम sg_copy_part_from_buf(काष्ठा scatterlist *dest, u8 *src,
			   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक skip)
अणु
	माप_प्रकार copied;
	अचिन्हित पूर्णांक nents = sg_nents(dest);

	copied = sg_pcopy_from_buffer(dest, nents, src, len, skip);
	अगर (copied != len) अणु
		flow_log("%s copied %u bytes of %u requested. ",
			 __func__, (u32)copied, len);
		flow_log("sg with %u entries and skip %u\n", nents, skip);
	पूर्ण
पूर्ण

/**
 * spu_sg_count() - Determine number of elements in scatterlist to provide a
 * specअगरied number of bytes.
 * @sg_list:  scatterlist to examine
 * @skip:     index of starting poपूर्णांक
 * @nbytes:   consider elements of scatterlist until reaching this number of
 *	      bytes
 *
 * Return: the number of sg entries contributing to nbytes of data
 */
पूर्णांक spu_sg_count(काष्ठा scatterlist *sg_list, अचिन्हित पूर्णांक skip, पूर्णांक nbytes)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक sg_nents = 0;
	अचिन्हित पूर्णांक offset;

	अगर (!sg_list)
		वापस 0;

	अगर (spu_sg_at_offset(sg_list, skip, &sg, &offset) < 0)
		वापस 0;

	जबतक (sg && (nbytes > 0)) अणु
		sg_nents++;
		nbytes -= (sg->length - offset);
		offset = 0;
		sg = sg_next(sg);
	पूर्ण
	वापस sg_nents;
पूर्ण

/**
 * spu_msg_sg_add() - Copy scatterlist entries from one sg to another, up to a
 * given length.
 * @to_sg:       scatterlist to copy to
 * @from_sg:     scatterlist to copy from
 * @from_skip:   number of bytes to skip in from_sg. Non-zero when previous
 *		 request included part of the buffer in entry in from_sg.
 *		 Assumes from_skip < from_sg->length.
 * @from_nents:  number of entries in from_sg
 * @length:      number of bytes to copy. may reach this limit beक्रमe exhausting
 *		 from_sg.
 *
 * Copies the entries themselves, not the data in the entries. Assumes to_sg has
 * enough entries. Does not limit the size of an inभागidual buffer in to_sg.
 *
 * to_sg, from_sg, skip are all updated to end of copy
 *
 * Return: Number of bytes copied
 */
u32 spu_msg_sg_add(काष्ठा scatterlist **to_sg,
		   काष्ठा scatterlist **from_sg, u32 *from_skip,
		   u8 from_nents, u32 length)
अणु
	काष्ठा scatterlist *sg;	/* an entry in from_sg */
	काष्ठा scatterlist *to = *to_sg;
	काष्ठा scatterlist *from = *from_sg;
	u32 skip = *from_skip;
	u32 offset;
	पूर्णांक i;
	u32 entry_len = 0;
	u32 frag_len = 0;	/* length of entry added to to_sg */
	u32 copied = 0;		/* number of bytes copied so far */

	अगर (length == 0)
		वापस 0;

	क्रम_each_sg(from, sg, from_nents, i) अणु
		/* number of bytes in this from entry not yet used */
		entry_len = sg->length - skip;
		frag_len = min(entry_len, length - copied);
		offset = sg->offset + skip;
		अगर (frag_len)
			sg_set_page(to++, sg_page(sg), frag_len, offset);
		copied += frag_len;
		अगर (copied == entry_len) अणु
			/* used up all of from entry */
			skip = 0;	/* start at beginning of next entry */
		पूर्ण
		अगर (copied == length)
			अवरोध;
	पूर्ण
	*to_sg = to;
	*from_sg = sg;
	अगर (frag_len < entry_len)
		*from_skip = skip + frag_len;
	अन्यथा
		*from_skip = 0;

	वापस copied;
पूर्ण

व्योम add_to_ctr(u8 *ctr_pos, अचिन्हित पूर्णांक increment)
अणु
	__be64 *high_be = (__be64 *)ctr_pos;
	__be64 *low_be = high_be + 1;
	u64 orig_low = __be64_to_cpu(*low_be);
	u64 new_low = orig_low + (u64)increment;

	*low_be = __cpu_to_be64(new_low);
	अगर (new_low < orig_low)
		/* there was a carry from the low 8 bytes */
		*high_be = __cpu_to_be64(__be64_to_cpu(*high_be) + 1);
पूर्ण

काष्ठा sdesc अणु
	काष्ठा shash_desc shash;
	अक्षर ctx[];
पूर्ण;

/**
 * करो_shash() - Do a synchronous hash operation in software
 * @name:       The name of the hash algorithm
 * @result:     Buffer where digest is to be written
 * @data1:      First part of data to hash. May be शून्य.
 * @data1_len:  Length of data1, in bytes
 * @data2:      Second part of data to hash. May be शून्य.
 * @data2_len:  Length of data2, in bytes
 * @key:	Key (अगर keyed hash)
 * @key_len:	Length of key, in bytes (or 0 अगर non-keyed hash)
 *
 * Note that the crypto API will not select this driver's own transक्रमm because
 * this driver only रेजिस्टरs asynchronous algos.
 *
 * Return: 0 अगर hash successfully stored in result
 *         < 0 otherwise
 */
पूर्णांक करो_shash(अचिन्हित अक्षर *name, अचिन्हित अक्षर *result,
	     स्थिर u8 *data1, अचिन्हित पूर्णांक data1_len,
	     स्थिर u8 *data2, अचिन्हित पूर्णांक data2_len,
	     स्थिर u8 *key, अचिन्हित पूर्णांक key_len)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक size;
	काष्ठा crypto_shash *hash;
	काष्ठा sdesc *sdesc;

	hash = crypto_alloc_shash(name, 0, 0);
	अगर (IS_ERR(hash)) अणु
		rc = PTR_ERR(hash);
		pr_err("%s: Crypto %s allocation error %d\n", __func__, name, rc);
		वापस rc;
	पूर्ण

	size = माप(काष्ठा shash_desc) + crypto_shash_descsize(hash);
	sdesc = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!sdesc) अणु
		rc = -ENOMEM;
		जाओ करो_shash_err;
	पूर्ण
	sdesc->shash.tfm = hash;

	अगर (key_len > 0) अणु
		rc = crypto_shash_setkey(hash, key, key_len);
		अगर (rc) अणु
			pr_err("%s: Could not setkey %s shash\n", __func__, name);
			जाओ करो_shash_err;
		पूर्ण
	पूर्ण

	rc = crypto_shash_init(&sdesc->shash);
	अगर (rc) अणु
		pr_err("%s: Could not init %s shash\n", __func__, name);
		जाओ करो_shash_err;
	पूर्ण
	rc = crypto_shash_update(&sdesc->shash, data1, data1_len);
	अगर (rc) अणु
		pr_err("%s: Could not update1\n", __func__);
		जाओ करो_shash_err;
	पूर्ण
	अगर (data2 && data2_len) अणु
		rc = crypto_shash_update(&sdesc->shash, data2, data2_len);
		अगर (rc) अणु
			pr_err("%s: Could not update2\n", __func__);
			जाओ करो_shash_err;
		पूर्ण
	पूर्ण
	rc = crypto_shash_final(&sdesc->shash, result);
	अगर (rc)
		pr_err("%s: Could not generate %s hash\n", __func__, name);

करो_shash_err:
	crypto_मुक्त_shash(hash);
	kमुक्त(sdesc);

	वापस rc;
पूर्ण

#अगर_घोषित DEBUG
/* Dump len bytes of a scatterlist starting at skip bytes पूर्णांकo the sg */
व्योम __dump_sg(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक skip, अचिन्हित पूर्णांक len)
अणु
	u8 dbuf[16];
	अचिन्हित पूर्णांक idx = skip;
	अचिन्हित पूर्णांक num_out = 0;	/* number of bytes dumped so far */
	अचिन्हित पूर्णांक count;

	अगर (packet_debug_logging) अणु
		जबतक (num_out < len) अणु
			count = (len - num_out > 16) ? 16 : len - num_out;
			sg_copy_part_to_buf(sg, dbuf, count, idx);
			num_out += count;
			prपूर्णांक_hex_dump(KERN_ALERT, "  sg: ", DUMP_PREFIX_NONE,
				       4, 1, dbuf, count, false);
			idx += 16;
		पूर्ण
	पूर्ण
	अगर (debug_logging_sleep)
		msleep(debug_logging_sleep);
पूर्ण
#पूर्ण_अगर

/* Returns the name क्रम a given cipher alg/mode */
अक्षर *spu_alg_name(क्रमागत spu_cipher_alg alg, क्रमागत spu_cipher_mode mode)
अणु
	चयन (alg) अणु
	हाल CIPHER_ALG_RC4:
		वापस "rc4";
	हाल CIPHER_ALG_AES:
		चयन (mode) अणु
		हाल CIPHER_MODE_CBC:
			वापस "cbc(aes)";
		हाल CIPHER_MODE_ECB:
			वापस "ecb(aes)";
		हाल CIPHER_MODE_OFB:
			वापस "ofb(aes)";
		हाल CIPHER_MODE_CFB:
			वापस "cfb(aes)";
		हाल CIPHER_MODE_CTR:
			वापस "ctr(aes)";
		हाल CIPHER_MODE_XTS:
			वापस "xts(aes)";
		हाल CIPHER_MODE_GCM:
			वापस "gcm(aes)";
		शेष:
			वापस "aes";
		पूर्ण
		अवरोध;
	हाल CIPHER_ALG_DES:
		चयन (mode) अणु
		हाल CIPHER_MODE_CBC:
			वापस "cbc(des)";
		हाल CIPHER_MODE_ECB:
			वापस "ecb(des)";
		हाल CIPHER_MODE_CTR:
			वापस "ctr(des)";
		शेष:
			वापस "des";
		पूर्ण
		अवरोध;
	हाल CIPHER_ALG_3DES:
		चयन (mode) अणु
		हाल CIPHER_MODE_CBC:
			वापस "cbc(des3_ede)";
		हाल CIPHER_MODE_ECB:
			वापस "ecb(des3_ede)";
		हाल CIPHER_MODE_CTR:
			वापस "ctr(des3_ede)";
		शेष:
			वापस "3des";
		पूर्ण
		अवरोध;
	शेष:
		वापस "other";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार spu_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा bcm_device_निजी *ipriv;
	अक्षर *buf;
	sमाप_प्रकार ret, out_offset, out_count;
	पूर्णांक i;
	u32 fअगरo_len;
	u32 spu_ofअगरo_ctrl;
	u32 alg;
	u32 mode;
	u32 op_cnt;

	out_count = 2048;

	buf = kदो_स्मृति(out_count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ipriv = filp->निजी_data;
	out_offset = 0;
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Number of SPUs.........%u\n",
			       ipriv->spu.num_spu);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Current sessions.......%u\n",
			       atomic_पढ़ो(&ipriv->session_count));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Session count..........%u\n",
			       atomic_पढ़ो(&ipriv->stream_count));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Cipher setkey..........%u\n",
			       atomic_पढ़ो(&ipriv->setkey_cnt[SPU_OP_CIPHER]));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Cipher Ops.............%u\n",
			       atomic_पढ़ो(&ipriv->op_counts[SPU_OP_CIPHER]));
	क्रम (alg = 0; alg < CIPHER_ALG_LAST; alg++) अणु
		क्रम (mode = 0; mode < CIPHER_MODE_LAST; mode++) अणु
			op_cnt = atomic_पढ़ो(&ipriv->cipher_cnt[alg][mode]);
			अगर (op_cnt) अणु
				out_offset += scnम_लिखो(buf + out_offset,
						       out_count - out_offset,
			       "  %-13s%11u\n",
			       spu_alg_name(alg, mode), op_cnt);
			पूर्ण
		पूर्ण
	पूर्ण
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Hash Ops...............%u\n",
			       atomic_पढ़ो(&ipriv->op_counts[SPU_OP_HASH]));
	क्रम (alg = 0; alg < HASH_ALG_LAST; alg++) अणु
		op_cnt = atomic_पढ़ो(&ipriv->hash_cnt[alg]);
		अगर (op_cnt) अणु
			out_offset += scnम_लिखो(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       hash_alg_name[alg], op_cnt);
		पूर्ण
	पूर्ण
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "HMAC setkey............%u\n",
			       atomic_पढ़ो(&ipriv->setkey_cnt[SPU_OP_HMAC]));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "HMAC Ops...............%u\n",
			       atomic_पढ़ो(&ipriv->op_counts[SPU_OP_HMAC]));
	क्रम (alg = 0; alg < HASH_ALG_LAST; alg++) अणु
		op_cnt = atomic_पढ़ो(&ipriv->hmac_cnt[alg]);
		अगर (op_cnt) अणु
			out_offset += scnम_लिखो(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       hash_alg_name[alg], op_cnt);
		पूर्ण
	पूर्ण
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "AEAD setkey............%u\n",
			       atomic_पढ़ो(&ipriv->setkey_cnt[SPU_OP_AEAD]));

	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "AEAD Ops...............%u\n",
			       atomic_पढ़ो(&ipriv->op_counts[SPU_OP_AEAD]));
	क्रम (alg = 0; alg < AEAD_TYPE_LAST; alg++) अणु
		op_cnt = atomic_पढ़ो(&ipriv->aead_cnt[alg]);
		अगर (op_cnt) अणु
			out_offset += scnम_लिखो(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       aead_alg_name[alg], op_cnt);
		पूर्ण
	पूर्ण
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Bytes of req data......%llu\n",
			       (u64)atomic64_पढ़ो(&ipriv->bytes_out));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Bytes of resp data.....%llu\n",
			       (u64)atomic64_पढ़ो(&ipriv->bytes_in));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Mailbox full...........%u\n",
			       atomic_पढ़ो(&ipriv->mb_no_spc));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Mailbox send failures..%u\n",
			       atomic_पढ़ो(&ipriv->mb_send_fail));
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Check ICV errors.......%u\n",
			       atomic_पढ़ो(&ipriv->bad_icv));
	अगर (ipriv->spu.spu_type == SPU_TYPE_SPUM)
		क्रम (i = 0; i < ipriv->spu.num_spu; i++) अणु
			spu_ofअगरo_ctrl = ioपढ़ो32(ipriv->spu.reg_vbase[i] +
						  SPU_OFIFO_CTRL);
			fअगरo_len = spu_ofअगरo_ctrl & SPU_FIFO_WATERMARK;
			out_offset += scnम_लिखो(buf + out_offset,
					       out_count - out_offset,
				       "SPU %d output FIFO high water.....%u\n",
				       i, fअगरo_len);
		पूर्ण

	अगर (out_offset > out_count)
		out_offset = out_count;

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, out_offset);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations spu_debugfs_stats = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = spu_debugfs_पढ़ो,
पूर्ण;

/*
 * Create the debug FS directories. If the top-level directory has not yet
 * been created, create it now. Create a stats file in this directory क्रम
 * a SPU.
 */
व्योम spu_setup_debugfs(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस;

	अगर (!iproc_priv.debugfs_dir)
		iproc_priv.debugfs_dir = debugfs_create_dir(KBUILD_MODNAME,
							    शून्य);

	अगर (!iproc_priv.debugfs_stats)
		/* Create file with permissions S_IRUSR */
		debugfs_create_file("stats", 0400, iproc_priv.debugfs_dir,
				    &iproc_priv, &spu_debugfs_stats);
पूर्ण

व्योम spu_मुक्त_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(iproc_priv.debugfs_dir);
	iproc_priv.debugfs_dir = शून्य;
पूर्ण

/**
 * क्रमmat_value_ccm() - Format a value पूर्णांकo a buffer, using a specअगरied number
 *			of bytes (i.e. maybe writing value X पूर्णांकo a 4 byte
 *			buffer, or maybe पूर्णांकo a 12 byte buffer), as per the
 *			SPU CCM spec.
 *
 * @val:		value to ग_लिखो (up to max of अचिन्हित पूर्णांक)
 * @buf:		(poपूर्णांकer to) buffer to ग_लिखो the value
 * @len:		number of bytes to use (0 to 255)
 *
 */
व्योम क्रमmat_value_ccm(अचिन्हित पूर्णांक val, u8 *buf, u8 len)
अणु
	पूर्णांक i;

	/* First clear full output buffer */
	स_रखो(buf, 0, len);

	/* Then, starting from right side, fill in with data */
	क्रम (i = 0; i < len; i++) अणु
		buf[len - i - 1] = (val >> (8 * i)) & 0xff;
		अगर (i >= 3)
			अवरोध;  /* Only handle up to 32 bits of 'val' */
	पूर्ण
पूर्ण
