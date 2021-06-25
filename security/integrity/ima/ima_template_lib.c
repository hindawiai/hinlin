<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Author: Roberto Sassu <roberto.sassu@polito.it>
 *
 * File: ima_ढाँचा_lib.c
 *      Library of supported ढाँचा fields.
 */

#समावेश "ima_template_lib.h"

अटल bool ima_ढाँचा_hash_algo_allowed(u8 algo)
अणु
	अगर (algo == HASH_ALGO_SHA1 || algo == HASH_ALGO_MD5)
		वापस true;

	वापस false;
पूर्ण

क्रमागत data_क्रमmats अणु
	DATA_FMT_DIGEST = 0,
	DATA_FMT_DIGEST_WITH_ALGO,
	DATA_FMT_STRING,
	DATA_FMT_HEX
पूर्ण;

अटल पूर्णांक ima_ग_लिखो_ढाँचा_field_data(स्थिर व्योम *data, स्थिर u32 datalen,
					 क्रमागत data_क्रमmats datafmt,
					 काष्ठा ima_field_data *field_data)
अणु
	u8 *buf, *buf_ptr;
	u32 buflen = datalen;

	अगर (datafmt == DATA_FMT_STRING)
		buflen = datalen + 1;

	buf = kzalloc(buflen, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_नकल(buf, data, datalen);

	/*
	 * Replace all space अक्षरacters with underscore क्रम event names and
	 * strings. This aव्योम that, during the parsing of a measurements list,
	 * filenames with spaces or that end with the suffix ' (deleted)' are
	 * split पूर्णांकo multiple ढाँचा fields (the space is the delimitator
	 * अक्षरacter क्रम measurements lists in ASCII क्रमmat).
	 */
	अगर (datafmt == DATA_FMT_STRING) अणु
		क्रम (buf_ptr = buf; buf_ptr - buf < datalen; buf_ptr++)
			अगर (*buf_ptr == ' ')
				*buf_ptr = '_';
	पूर्ण

	field_data->data = buf;
	field_data->len = buflen;
	वापस 0;
पूर्ण

अटल व्योम ima_show_ढाँचा_data_ascii(काष्ठा seq_file *m,
					 क्रमागत ima_show_type show,
					 क्रमागत data_क्रमmats datafmt,
					 काष्ठा ima_field_data *field_data)
अणु
	u8 *buf_ptr = field_data->data;
	u32 buflen = field_data->len;

	चयन (datafmt) अणु
	हाल DATA_FMT_DIGEST_WITH_ALGO:
		buf_ptr = strnchr(field_data->data, buflen, ':');
		अगर (buf_ptr != field_data->data)
			seq_म_लिखो(m, "%s", field_data->data);

		/* skip ':' and '\0' */
		buf_ptr += 2;
		buflen -= buf_ptr - field_data->data;
		fallthrough;
	हाल DATA_FMT_DIGEST:
	हाल DATA_FMT_HEX:
		अगर (!buflen)
			अवरोध;
		ima_prपूर्णांक_digest(m, buf_ptr, buflen);
		अवरोध;
	हाल DATA_FMT_STRING:
		seq_म_लिखो(m, "%s", buf_ptr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ima_show_ढाँचा_data_binary(काष्ठा seq_file *m,
					  क्रमागत ima_show_type show,
					  क्रमागत data_क्रमmats datafmt,
					  काष्ठा ima_field_data *field_data)
अणु
	u32 len = (show == IMA_SHOW_BINARY_OLD_STRING_FMT) ?
	    म_माप(field_data->data) : field_data->len;

	अगर (show != IMA_SHOW_BINARY_NO_FIELD_LEN) अणु
		u32 field_len = !ima_canonical_fmt ? len : cpu_to_le32(len);

		ima_अ_दो(m, &field_len, माप(field_len));
	पूर्ण

	अगर (!len)
		वापस;

	ima_अ_दो(m, field_data->data, len);
पूर्ण

अटल व्योम ima_show_ढाँचा_field_data(काष्ठा seq_file *m,
					 क्रमागत ima_show_type show,
					 क्रमागत data_क्रमmats datafmt,
					 काष्ठा ima_field_data *field_data)
अणु
	चयन (show) अणु
	हाल IMA_SHOW_ASCII:
		ima_show_ढाँचा_data_ascii(m, show, datafmt, field_data);
		अवरोध;
	हाल IMA_SHOW_BINARY:
	हाल IMA_SHOW_BINARY_NO_FIELD_LEN:
	हाल IMA_SHOW_BINARY_OLD_STRING_FMT:
		ima_show_ढाँचा_data_binary(m, show, datafmt, field_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ima_show_ढाँचा_digest(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			      काष्ठा ima_field_data *field_data)
अणु
	ima_show_ढाँचा_field_data(m, show, DATA_FMT_DIGEST, field_data);
पूर्ण

व्योम ima_show_ढाँचा_digest_ng(काष्ठा seq_file *m, क्रमागत ima_show_type show,
				 काष्ठा ima_field_data *field_data)
अणु
	ima_show_ढाँचा_field_data(m, show, DATA_FMT_DIGEST_WITH_ALGO,
				     field_data);
पूर्ण

व्योम ima_show_ढाँचा_string(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			      काष्ठा ima_field_data *field_data)
अणु
	ima_show_ढाँचा_field_data(m, show, DATA_FMT_STRING, field_data);
पूर्ण

व्योम ima_show_ढाँचा_sig(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			   काष्ठा ima_field_data *field_data)
अणु
	ima_show_ढाँचा_field_data(m, show, DATA_FMT_HEX, field_data);
पूर्ण

व्योम ima_show_ढाँचा_buf(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			   काष्ठा ima_field_data *field_data)
अणु
	ima_show_ढाँचा_field_data(m, show, DATA_FMT_HEX, field_data);
पूर्ण

/**
 * ima_parse_buf() - Parses lengths and data from an input buffer
 * @bufstartp:       Buffer start address.
 * @bufendp:         Buffer end address.
 * @bufcurp:         Poपूर्णांकer to reमुख्यing (non-parsed) data.
 * @maxfields:       Length of fields array.
 * @fields:          Array containing lengths and poपूर्णांकers of parsed data.
 * @curfields:       Number of array items containing parsed data.
 * @len_mask:        Biपंचांगap (अगर bit is set, data length should not be parsed).
 * @enक्रमce_mask:    Check अगर curfields == maxfields and/or bufcurp == bufendp.
 * @bufname:         String identअगरier of the input buffer.
 *
 * Return: 0 on success, -EINVAL on error.
 */
पूर्णांक ima_parse_buf(व्योम *bufstartp, व्योम *bufendp, व्योम **bufcurp,
		  पूर्णांक maxfields, काष्ठा ima_field_data *fields, पूर्णांक *curfields,
		  अचिन्हित दीर्घ *len_mask, पूर्णांक enक्रमce_mask, अक्षर *bufname)
अणु
	व्योम *bufp = bufstartp;
	पूर्णांक i;

	क्रम (i = 0; i < maxfields; i++) अणु
		अगर (len_mask == शून्य || !test_bit(i, len_mask)) अणु
			अगर (bufp > (bufendp - माप(u32)))
				अवरोध;

			fields[i].len = *(u32 *)bufp;
			अगर (ima_canonical_fmt)
				fields[i].len = le32_to_cpu(fields[i].len);

			bufp += माप(u32);
		पूर्ण

		अगर (bufp > (bufendp - fields[i].len))
			अवरोध;

		fields[i].data = bufp;
		bufp += fields[i].len;
	पूर्ण

	अगर ((enक्रमce_mask & ENFORCE_FIELDS) && i != maxfields) अणु
		pr_err("%s: nr of fields mismatch: expected: %d, current: %d\n",
		       bufname, maxfields, i);
		वापस -EINVAL;
	पूर्ण

	अगर ((enक्रमce_mask & ENFORCE_BUFEND) && bufp != bufendp) अणु
		pr_err("%s: buf end mismatch: expected: %p, current: %p\n",
		       bufname, bufendp, bufp);
		वापस -EINVAL;
	पूर्ण

	अगर (curfields)
		*curfields = i;

	अगर (bufcurp)
		*bufcurp = bufp;

	वापस 0;
पूर्ण

अटल पूर्णांक ima_eventdigest_init_common(स्थिर u8 *digest, u32 digestsize,
				       u8 hash_algo,
				       काष्ठा ima_field_data *field_data)
अणु
	/*
	 * digest क्रमmats:
	 *  - DATA_FMT_DIGEST: digest
	 *  - DATA_FMT_DIGEST_WITH_ALGO: [<hash algo>] + ':' + '\0' + digest,
	 *    where <hash algo> is provided अगर the hash algoriपंचांग is not
	 *    SHA1 or MD5
	 */
	u8 buffer[CRYPTO_MAX_ALG_NAME + 2 + IMA_MAX_DIGEST_SIZE] = अणु 0 पूर्ण;
	क्रमागत data_क्रमmats fmt = DATA_FMT_DIGEST;
	u32 offset = 0;

	अगर (hash_algo < HASH_ALGO__LAST) अणु
		fmt = DATA_FMT_DIGEST_WITH_ALGO;
		offset += snम_लिखो(buffer, CRYPTO_MAX_ALG_NAME + 1, "%s",
				   hash_algo_name[hash_algo]);
		buffer[offset] = ':';
		offset += 2;
	पूर्ण

	अगर (digest)
		स_नकल(buffer + offset, digest, digestsize);
	अन्यथा
		/*
		 * If digest is शून्य, the event being recorded is a violation.
		 * Make room क्रम the digest by increasing the offset of
		 * IMA_DIGEST_SIZE.
		 */
		offset += IMA_DIGEST_SIZE;

	वापस ima_ग_लिखो_ढाँचा_field_data(buffer, offset + digestsize,
					     fmt, field_data);
पूर्ण

/*
 * This function ग_लिखोs the digest of an event (with size limit).
 */
पूर्णांक ima_eventdigest_init(काष्ठा ima_event_data *event_data,
			 काष्ठा ima_field_data *field_data)
अणु
	काष्ठा अणु
		काष्ठा ima_digest_data hdr;
		अक्षर digest[IMA_MAX_DIGEST_SIZE];
	पूर्ण hash;
	u8 *cur_digest = शून्य;
	u32 cur_digestsize = 0;
	काष्ठा inode *inode;
	पूर्णांक result;

	स_रखो(&hash, 0, माप(hash));

	अगर (event_data->violation)	/* recording a violation. */
		जाओ out;

	अगर (ima_ढाँचा_hash_algo_allowed(event_data->iपूर्णांक->ima_hash->algo)) अणु
		cur_digest = event_data->iपूर्णांक->ima_hash->digest;
		cur_digestsize = event_data->iपूर्णांक->ima_hash->length;
		जाओ out;
	पूर्ण

	अगर ((स्थिर अक्षर *)event_data->filename == boot_aggregate_name) अणु
		अगर (ima_tpm_chip) अणु
			hash.hdr.algo = HASH_ALGO_SHA1;
			result = ima_calc_boot_aggregate(&hash.hdr);

			/* algo can change depending on available PCR banks */
			अगर (!result && hash.hdr.algo != HASH_ALGO_SHA1)
				result = -EINVAL;

			अगर (result < 0)
				स_रखो(&hash, 0, माप(hash));
		पूर्ण

		cur_digest = hash.hdr.digest;
		cur_digestsize = hash_digest_size[HASH_ALGO_SHA1];
		जाओ out;
	पूर्ण

	अगर (!event_data->file)	/* missing info to re-calculate the digest */
		वापस -EINVAL;

	inode = file_inode(event_data->file);
	hash.hdr.algo = ima_ढाँचा_hash_algo_allowed(ima_hash_algo) ?
	    ima_hash_algo : HASH_ALGO_SHA1;
	result = ima_calc_file_hash(event_data->file, &hash.hdr);
	अगर (result) अणु
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_DATA, inode,
				    event_data->filename, "collect_data",
				    "failed", result, 0);
		वापस result;
	पूर्ण
	cur_digest = hash.hdr.digest;
	cur_digestsize = hash.hdr.length;
out:
	वापस ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   HASH_ALGO__LAST, field_data);
पूर्ण

/*
 * This function ग_लिखोs the digest of an event (without size limit).
 */
पूर्णांक ima_eventdigest_ng_init(काष्ठा ima_event_data *event_data,
			    काष्ठा ima_field_data *field_data)
अणु
	u8 *cur_digest = शून्य, hash_algo = HASH_ALGO_SHA1;
	u32 cur_digestsize = 0;

	अगर (event_data->violation)	/* recording a violation. */
		जाओ out;

	cur_digest = event_data->iपूर्णांक->ima_hash->digest;
	cur_digestsize = event_data->iपूर्णांक->ima_hash->length;

	hash_algo = event_data->iपूर्णांक->ima_hash->algo;
out:
	वापस ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   hash_algo, field_data);
पूर्ण

/*
 * This function ग_लिखोs the digest of the file which is expected to match the
 * digest contained in the file's appended signature.
 */
पूर्णांक ima_eventdigest_modsig_init(काष्ठा ima_event_data *event_data,
				काष्ठा ima_field_data *field_data)
अणु
	क्रमागत hash_algo hash_algo;
	स्थिर u8 *cur_digest;
	u32 cur_digestsize;

	अगर (!event_data->modsig)
		वापस 0;

	अगर (event_data->violation) अणु
		/* Recording a violation. */
		hash_algo = HASH_ALGO_SHA1;
		cur_digest = शून्य;
		cur_digestsize = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक rc;

		rc = ima_get_modsig_digest(event_data->modsig, &hash_algo,
					   &cur_digest, &cur_digestsize);
		अगर (rc)
			वापस rc;
		अन्यथा अगर (hash_algo == HASH_ALGO__LAST || cur_digestsize == 0)
			/* There was some error collecting the digest. */
			वापस -EINVAL;
	पूर्ण

	वापस ima_eventdigest_init_common(cur_digest, cur_digestsize,
					   hash_algo, field_data);
पूर्ण

अटल पूर्णांक ima_eventname_init_common(काष्ठा ima_event_data *event_data,
				     काष्ठा ima_field_data *field_data,
				     bool size_limit)
अणु
	स्थिर अक्षर *cur_filename = शून्य;
	u32 cur_filename_len = 0;

	BUG_ON(event_data->filename == शून्य && event_data->file == शून्य);

	अगर (event_data->filename) अणु
		cur_filename = event_data->filename;
		cur_filename_len = म_माप(event_data->filename);

		अगर (!size_limit || cur_filename_len <= IMA_EVENT_NAME_LEN_MAX)
			जाओ out;
	पूर्ण

	अगर (event_data->file) अणु
		cur_filename = event_data->file->f_path.dentry->d_name.name;
		cur_filename_len = म_माप(cur_filename);
	पूर्ण अन्यथा
		/*
		 * Truncate filename अगर the latter is too दीर्घ and
		 * the file descriptor is not available.
		 */
		cur_filename_len = IMA_EVENT_NAME_LEN_MAX;
out:
	वापस ima_ग_लिखो_ढाँचा_field_data(cur_filename, cur_filename_len,
					     DATA_FMT_STRING, field_data);
पूर्ण

/*
 * This function ग_लिखोs the name of an event (with size limit).
 */
पूर्णांक ima_eventname_init(काष्ठा ima_event_data *event_data,
		       काष्ठा ima_field_data *field_data)
अणु
	वापस ima_eventname_init_common(event_data, field_data, true);
पूर्ण

/*
 * This function ग_लिखोs the name of an event (without size limit).
 */
पूर्णांक ima_eventname_ng_init(काष्ठा ima_event_data *event_data,
			  काष्ठा ima_field_data *field_data)
अणु
	वापस ima_eventname_init_common(event_data, field_data, false);
पूर्ण

/*
 *  ima_eventsig_init - include the file signature as part of the ढाँचा data
 */
पूर्णांक ima_eventsig_init(काष्ठा ima_event_data *event_data,
		      काष्ठा ima_field_data *field_data)
अणु
	काष्ठा evm_ima_xattr_data *xattr_value = event_data->xattr_value;

	अगर ((!xattr_value) || (xattr_value->type != EVM_IMA_XATTR_DIGSIG))
		वापस 0;

	वापस ima_ग_लिखो_ढाँचा_field_data(xattr_value, event_data->xattr_len,
					     DATA_FMT_HEX, field_data);
पूर्ण

/*
 *  ima_eventbuf_init - include the buffer(kexec-cmldine) as part of the
 *  ढाँचा data.
 */
पूर्णांक ima_eventbuf_init(काष्ठा ima_event_data *event_data,
		      काष्ठा ima_field_data *field_data)
अणु
	अगर ((!event_data->buf) || (event_data->buf_len == 0))
		वापस 0;

	वापस ima_ग_लिखो_ढाँचा_field_data(event_data->buf,
					     event_data->buf_len, DATA_FMT_HEX,
					     field_data);
पूर्ण

/*
 *  ima_evenपंचांगodsig_init - include the appended file signature as part of the
 *  ढाँचा data
 */
पूर्णांक ima_evenपंचांगodsig_init(काष्ठा ima_event_data *event_data,
			 काष्ठा ima_field_data *field_data)
अणु
	स्थिर व्योम *data;
	u32 data_len;
	पूर्णांक rc;

	अगर (!event_data->modsig)
		वापस 0;

	/*
	 * modsig is a runसमय काष्ठाure containing poपूर्णांकers. Get its raw data
	 * instead.
	 */
	rc = ima_get_raw_modsig(event_data->modsig, &data, &data_len);
	अगर (rc)
		वापस rc;

	वापस ima_ग_लिखो_ढाँचा_field_data(data, data_len, DATA_FMT_HEX,
					     field_data);
पूर्ण
