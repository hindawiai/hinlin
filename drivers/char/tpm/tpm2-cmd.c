<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014, 2015 Intel Corporation
 *
 * Authors:
 * Jarkko Sakkinen <jarkko.sakkinen@linux.पूर्णांकel.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * This file contains TPM2 protocol implementations of the commands
 * used by the kernel पूर्णांकernally.
 */

#समावेश "tpm.h"
#समावेश <crypto/hash_info.h>

अटल काष्ठा tpm2_hash tpm2_hash_map[] = अणु
	अणुHASH_ALGO_SHA1, TPM_ALG_SHA1पूर्ण,
	अणुHASH_ALGO_SHA256, TPM_ALG_SHA256पूर्ण,
	अणुHASH_ALGO_SHA384, TPM_ALG_SHA384पूर्ण,
	अणुHASH_ALGO_SHA512, TPM_ALG_SHA512पूर्ण,
	अणुHASH_ALGO_SM3_256, TPM_ALG_SM3_256पूर्ण,
पूर्ण;

पूर्णांक tpm2_get_समयouts(काष्ठा tpm_chip *chip)
अणु
	/* Fixed समयouts क्रम TPM2 */
	chip->समयout_a = msecs_to_jअगरfies(TPM2_TIMEOUT_A);
	chip->समयout_b = msecs_to_jअगरfies(TPM2_TIMEOUT_B);
	chip->समयout_c = msecs_to_jअगरfies(TPM2_TIMEOUT_C);
	chip->समयout_d = msecs_to_jअगरfies(TPM2_TIMEOUT_D);

	/* PTP spec समयouts */
	chip->duration[TPM_SHORT] = msecs_to_jअगरfies(TPM2_DURATION_SHORT);
	chip->duration[TPM_MEDIUM] = msecs_to_jअगरfies(TPM2_DURATION_MEDIUM);
	chip->duration[TPM_LONG] = msecs_to_jअगरfies(TPM2_DURATION_LONG);

	/* Key creation commands दीर्घ समयouts */
	chip->duration[TPM_LONG_LONG] =
		msecs_to_jअगरfies(TPM2_DURATION_LONG_LONG);

	chip->flags |= TPM_CHIP_FLAG_HAVE_TIMEOUTS;

	वापस 0;
पूर्ण

/**
 * tpm2_ordinal_duration_index() - वापसs an index to the chip duration table
 * @ordinal: TPM command ordinal.
 *
 * The function वापसs an index to the chip duration table
 * (क्रमागत tpm_duration), that describes the maximum amount of
 * समय the chip could take to वापस the result क्रम a  particular ordinal.
 *
 * The values of the MEDIUM, and LONG durations are taken
 * from the PC Client Profile (PTP) specअगरication (750, 2000 msec)
 *
 * LONG_LONG is क्रम commands that generates keys which empirically takes
 * a दीर्घer समय on some प्रणालीs.
 *
 * Return:
 * * TPM_MEDIUM
 * * TPM_LONG
 * * TPM_LONG_LONG
 * * TPM_UNDEFINED
 */
अटल u8 tpm2_ordinal_duration_index(u32 ordinal)
अणु
	चयन (ordinal) अणु
	/* Startup */
	हाल TPM2_CC_STARTUP:                 /* 144 */
		वापस TPM_MEDIUM;

	हाल TPM2_CC_SELF_TEST:               /* 143 */
		वापस TPM_LONG;

	हाल TPM2_CC_GET_RANDOM:              /* 17B */
		वापस TPM_LONG;

	हाल TPM2_CC_SEQUENCE_UPDATE:         /* 15C */
		वापस TPM_MEDIUM;
	हाल TPM2_CC_SEQUENCE_COMPLETE:       /* 13E */
		वापस TPM_MEDIUM;
	हाल TPM2_CC_EVENT_SEQUENCE_COMPLETE: /* 185 */
		वापस TPM_MEDIUM;
	हाल TPM2_CC_HASH_SEQUENCE_START:     /* 186 */
		वापस TPM_MEDIUM;

	हाल TPM2_CC_VERIFY_SIGNATURE:        /* 177 */
		वापस TPM_LONG;

	हाल TPM2_CC_PCR_EXTEND:              /* 182 */
		वापस TPM_MEDIUM;

	हाल TPM2_CC_HIERARCHY_CONTROL:       /* 121 */
		वापस TPM_LONG;
	हाल TPM2_CC_HIERARCHY_CHANGE_AUTH:   /* 129 */
		वापस TPM_LONG;

	हाल TPM2_CC_GET_CAPABILITY:          /* 17A */
		वापस TPM_MEDIUM;

	हाल TPM2_CC_NV_READ:                 /* 14E */
		वापस TPM_LONG;

	हाल TPM2_CC_CREATE_PRIMARY:          /* 131 */
		वापस TPM_LONG_LONG;
	हाल TPM2_CC_CREATE:                  /* 153 */
		वापस TPM_LONG_LONG;
	हाल TPM2_CC_CREATE_LOADED:           /* 191 */
		वापस TPM_LONG_LONG;

	शेष:
		वापस TPM_UNDEFINED;
	पूर्ण
पूर्ण

/**
 * tpm2_calc_ordinal_duration() - calculate the maximum command duration
 * @chip:    TPM chip to use.
 * @ordinal: TPM command ordinal.
 *
 * The function वापसs the maximum amount of समय the chip could take
 * to वापस the result क्रम a particular ordinal in jअगरfies.
 *
 * Return: A maximal duration समय क्रम an ordinal in jअगरfies.
 */
अचिन्हित दीर्घ tpm2_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal)
अणु
	अचिन्हित पूर्णांक index;

	index = tpm2_ordinal_duration_index(ordinal);

	अगर (index != TPM_UNDEFINED)
		वापस chip->duration[index];
	अन्यथा
		वापस msecs_to_jअगरfies(TPM2_DURATION_DEFAULT);
पूर्ण


काष्ठा tpm2_pcr_पढ़ो_out अणु
	__be32	update_cnt;
	__be32	pcr_selects_cnt;
	__be16	hash_alg;
	u8	pcr_select_size;
	u8	pcr_select[TPM2_PCR_SELECT_MIN];
	__be32	digests_cnt;
	__be16	digest_size;
	u8	digest[];
पूर्ण __packed;

/**
 * tpm2_pcr_पढ़ो() - पढ़ो a PCR value
 * @chip:	TPM chip to use.
 * @pcr_idx:	index of the PCR to पढ़ो.
 * @digest:	PCR bank and buffer current PCR value is written to.
 * @digest_size_ptr:	poपूर्णांकer to variable that stores the digest size.
 *
 * Return: Same as with tpm_transmit_cmd.
 */
पूर्णांक tpm2_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx,
		  काष्ठा tpm_digest *digest, u16 *digest_size_ptr)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	काष्ठा tpm_buf buf;
	काष्ठा tpm2_pcr_पढ़ो_out *out;
	u8 pcr_select[TPM2_PCR_SELECT_MIN] = अणु0पूर्ण;
	u16 digest_size;
	u16 expected_digest_size = 0;

	अगर (pcr_idx >= TPM2_PLATFORM_PCR)
		वापस -EINVAL;

	अगर (!digest_size_ptr) अणु
		क्रम (i = 0; i < chip->nr_allocated_banks &&
		     chip->allocated_banks[i].alg_id != digest->alg_id; i++)
			;

		अगर (i == chip->nr_allocated_banks)
			वापस -EINVAL;

		expected_digest_size = chip->allocated_banks[i].digest_size;
	पूर्ण

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_PCR_READ);
	अगर (rc)
		वापस rc;

	pcr_select[pcr_idx >> 3] = 1 << (pcr_idx & 0x7);

	tpm_buf_append_u32(&buf, 1);
	tpm_buf_append_u16(&buf, digest->alg_id);
	tpm_buf_append_u8(&buf, TPM2_PCR_SELECT_MIN);
	tpm_buf_append(&buf, (स्थिर अचिन्हित अक्षर *)pcr_select,
		       माप(pcr_select));

	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to read a pcr value");
	अगर (rc)
		जाओ out;

	out = (काष्ठा tpm2_pcr_पढ़ो_out *)&buf.data[TPM_HEADER_SIZE];
	digest_size = be16_to_cpu(out->digest_size);
	अगर (digest_size > माप(digest->digest) ||
	    (!digest_size_ptr && digest_size != expected_digest_size)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (digest_size_ptr)
		*digest_size_ptr = digest_size;

	स_नकल(digest->digest, out->digest, digest_size);
out:
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

काष्ठा tpm2_null_auth_area अणु
	__be32  handle;
	__be16  nonce_size;
	u8  attributes;
	__be16  auth_size;
पूर्ण __packed;

/**
 * tpm2_pcr_extend() - extend a PCR value
 *
 * @chip:	TPM chip to use.
 * @pcr_idx:	index of the PCR.
 * @digests:	list of pcr banks and corresponding digest values to extend.
 *
 * Return: Same as with tpm_transmit_cmd.
 */
पूर्णांक tpm2_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx,
		    काष्ठा tpm_digest *digests)
अणु
	काष्ठा tpm_buf buf;
	काष्ठा tpm2_null_auth_area auth_area;
	पूर्णांक rc;
	पूर्णांक i;

	rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_PCR_EXTEND);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, pcr_idx);

	auth_area.handle = cpu_to_be32(TPM2_RS_PW);
	auth_area.nonce_size = 0;
	auth_area.attributes = 0;
	auth_area.auth_size = 0;

	tpm_buf_append_u32(&buf, माप(काष्ठा tpm2_null_auth_area));
	tpm_buf_append(&buf, (स्थिर अचिन्हित अक्षर *)&auth_area,
		       माप(auth_area));
	tpm_buf_append_u32(&buf, chip->nr_allocated_banks);

	क्रम (i = 0; i < chip->nr_allocated_banks; i++) अणु
		tpm_buf_append_u16(&buf, digests[i].alg_id);
		tpm_buf_append(&buf, (स्थिर अचिन्हित अक्षर *)&digests[i].digest,
			       chip->allocated_banks[i].digest_size);
	पूर्ण

	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting extend a PCR value");

	tpm_buf_destroy(&buf);

	वापस rc;
पूर्ण

काष्ठा tpm2_get_अक्रमom_out अणु
	__be16 size;
	u8 buffer[TPM_MAX_RNG_DATA];
पूर्ण __packed;

/**
 * tpm2_get_अक्रमom() - get अक्रमom bytes from the TPM RNG
 *
 * @chip:	a &tpm_chip instance
 * @dest:	destination buffer
 * @max:	the max number of अक्रमom bytes to pull
 *
 * Return:
 *   size of the buffer on success,
 *   -त्रुटि_सं otherwise (positive TPM वापस codes are masked to -EIO)
 */
पूर्णांक tpm2_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *dest, माप_प्रकार max)
अणु
	काष्ठा tpm2_get_अक्रमom_out *out;
	काष्ठा tpm_buf buf;
	u32 recd;
	u32 num_bytes = max;
	पूर्णांक err;
	पूर्णांक total = 0;
	पूर्णांक retries = 5;
	u8 *dest_ptr = dest;

	अगर (!num_bytes || max > TPM_MAX_RNG_DATA)
		वापस -EINVAL;

	err = tpm_buf_init(&buf, 0, 0);
	अगर (err)
		वापस err;

	करो अणु
		tpm_buf_reset(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_RANDOM);
		tpm_buf_append_u16(&buf, num_bytes);
		err = tpm_transmit_cmd(chip, &buf,
				       दुरत्व(काष्ठा tpm2_get_अक्रमom_out,
						buffer),
				       "attempting get random");
		अगर (err) अणु
			अगर (err > 0)
				err = -EIO;
			जाओ out;
		पूर्ण

		out = (काष्ठा tpm2_get_अक्रमom_out *)
			&buf.data[TPM_HEADER_SIZE];
		recd = min_t(u32, be16_to_cpu(out->size), num_bytes);
		अगर (tpm_buf_length(&buf) <
		    TPM_HEADER_SIZE +
		    दुरत्व(काष्ठा tpm2_get_अक्रमom_out, buffer) +
		    recd) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण
		स_नकल(dest_ptr, out->buffer, recd);

		dest_ptr += recd;
		total += recd;
		num_bytes -= recd;
	पूर्ण जबतक (retries-- && total < max);

	tpm_buf_destroy(&buf);
	वापस total ? total : -EIO;
out:
	tpm_buf_destroy(&buf);
	वापस err;
पूर्ण

/**
 * tpm2_flush_context() - execute a TPM2_FlushContext command
 * @chip:	TPM chip to use
 * @handle:	context handle
 */
व्योम tpm2_flush_context(काष्ठा tpm_chip *chip, u32 handle)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_FLUSH_CONTEXT);
	अगर (rc) अणु
		dev_warn(&chip->dev, "0x%08x was not flushed, out of memory\n",
			 handle);
		वापस;
	पूर्ण

	tpm_buf_append_u32(&buf, handle);

	tpm_transmit_cmd(chip, &buf, 0, "flushing context");
	tpm_buf_destroy(&buf);
पूर्ण
EXPORT_SYMBOL_GPL(tpm2_flush_context);

काष्ठा tpm2_get_cap_out अणु
	u8 more_data;
	__be32 subcap_id;
	__be32 property_cnt;
	__be32 property_id;
	__be32 value;
पूर्ण __packed;

/**
 * tpm2_get_tpm_pt() - get value of a TPM_CAP_TPM_PROPERTIES type property
 * @chip:		a &tpm_chip instance
 * @property_id:	property ID.
 * @value:		output variable.
 * @desc:		passed to tpm_transmit_cmd()
 *
 * Return:
 *   0 on success,
 *   -त्रुटि_सं or a TPM वापस code otherwise
 */
sमाप_प्रकार tpm2_get_tpm_pt(काष्ठा tpm_chip *chip, u32 property_id,  u32 *value,
			स्थिर अक्षर *desc)
अणु
	काष्ठा tpm2_get_cap_out *out;
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	अगर (rc)
		वापस rc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PROPERTIES);
	tpm_buf_append_u32(&buf, property_id);
	tpm_buf_append_u32(&buf, 1);
	rc = tpm_transmit_cmd(chip, &buf, 0, शून्य);
	अगर (!rc) अणु
		out = (काष्ठा tpm2_get_cap_out *)
			&buf.data[TPM_HEADER_SIZE];
		*value = be32_to_cpu(out->value);
	पूर्ण
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm2_get_tpm_pt);

/**
 * tpm2_shutकरोwn() - send a TPM shutकरोwn command
 *
 * Sends a TPM shutकरोwn command. The shutकरोwn command is used in call
 * sites where the प्रणाली is going करोwn. If it fails, there is not much
 * that can be करोne except prपूर्णांक an error message.
 *
 * @chip:		a &tpm_chip instance
 * @shutकरोwn_type:	TPM_SU_CLEAR or TPM_SU_STATE.
 */
व्योम tpm2_shutकरोwn(काष्ठा tpm_chip *chip, u16 shutकरोwn_type)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_SHUTDOWN);
	अगर (rc)
		वापस;
	tpm_buf_append_u16(&buf, shutकरोwn_type);
	tpm_transmit_cmd(chip, &buf, 0, "stopping the TPM");
	tpm_buf_destroy(&buf);
पूर्ण

/**
 * tpm2_करो_selftest() - ensure that all self tests have passed
 *
 * @chip: TPM chip to use
 *
 * Return: Same as with tpm_transmit_cmd.
 *
 * The TPM can either run all self tests synchronously and then वापस
 * RC_SUCCESS once all tests were successful. Or it can choose to run the tests
 * asynchronously and वापस RC_TESTING immediately जबतक the self tests still
 * execute in the background. This function handles both हालs and रुकोs until
 * all tests have completed.
 */
अटल पूर्णांक tpm2_करो_selftest(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक full;
	पूर्णांक rc;

	क्रम (full = 0; full < 2; full++) अणु
		rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_SELF_TEST);
		अगर (rc)
			वापस rc;

		tpm_buf_append_u8(&buf, full);
		rc = tpm_transmit_cmd(chip, &buf, 0,
				      "attempting the self test");
		tpm_buf_destroy(&buf);

		अगर (rc == TPM2_RC_TESTING)
			rc = TPM2_RC_SUCCESS;
		अगर (rc == TPM2_RC_INITIALIZE || rc == TPM2_RC_SUCCESS)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * tpm2_probe() - probe क्रम the TPM 2.0 protocol
 * @chip:	a &tpm_chip instance
 *
 * Send an idempotent TPM 2.0 command and see whether there is TPM2 chip in the
 * other end based on the response tag. The flag TPM_CHIP_FLAG_TPM2 is set by
 * this function अगर this is the हाल.
 *
 * Return:
 *   0 on success,
 *   -त्रुटि_सं otherwise
 */
पूर्णांक tpm2_probe(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_header *out;
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	अगर (rc)
		वापस rc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PROPERTIES);
	tpm_buf_append_u32(&buf, TPM_PT_TOTAL_COMMANDS);
	tpm_buf_append_u32(&buf, 1);
	rc = tpm_transmit_cmd(chip, &buf, 0, शून्य);
	/* We ignore TPM वापस codes on purpose. */
	अगर (rc >=  0) अणु
		out = (काष्ठा tpm_header *)buf.data;
		अगर (be16_to_cpu(out->tag) == TPM2_ST_NO_SESSIONS)
			chip->flags |= TPM_CHIP_FLAG_TPM2;
	पूर्ण
	tpm_buf_destroy(&buf);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpm2_probe);

अटल पूर्णांक tpm2_init_bank_info(काष्ठा tpm_chip *chip, u32 bank_index)
अणु
	काष्ठा tpm_bank_info *bank = chip->allocated_banks + bank_index;
	काष्ठा tpm_digest digest = अणु .alg_id = bank->alg_id पूर्ण;
	पूर्णांक i;

	/*
	 * Aव्योम unnecessary PCR पढ़ो operations to reduce overhead
	 * and obtain identअगरiers of the crypto subप्रणाली.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(tpm2_hash_map); i++) अणु
		क्रमागत hash_algo crypto_algo = tpm2_hash_map[i].crypto_id;

		अगर (bank->alg_id != tpm2_hash_map[i].tpm_id)
			जारी;

		bank->digest_size = hash_digest_size[crypto_algo];
		bank->crypto_id = crypto_algo;
		वापस 0;
	पूर्ण

	bank->crypto_id = HASH_ALGO__LAST;

	वापस tpm2_pcr_पढ़ो(chip, 0, &digest, &bank->digest_size);
पूर्ण

काष्ठा tpm2_pcr_selection अणु
	__be16  hash_alg;
	u8  size_of_select;
	u8  pcr_select[3];
पूर्ण __packed;

sमाप_प्रकार tpm2_get_pcr_allocation(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm2_pcr_selection pcr_selection;
	काष्ठा tpm_buf buf;
	व्योम *marker;
	व्योम *end;
	व्योम *pcr_select_offset;
	u32 माप_pcr_selection;
	u32 nr_possible_banks;
	u32 nr_alloc_banks = 0;
	u16 hash_alg;
	u32 rsp_len;
	पूर्णांक rc;
	पूर्णांक i = 0;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, TPM2_CAP_PCRS);
	tpm_buf_append_u32(&buf, 0);
	tpm_buf_append_u32(&buf, 1);

	rc = tpm_transmit_cmd(chip, &buf, 9, "get tpm pcr allocation");
	अगर (rc)
		जाओ out;

	nr_possible_banks = be32_to_cpup(
		(__be32 *)&buf.data[TPM_HEADER_SIZE + 5]);

	chip->allocated_banks = kसुस्मृति(nr_possible_banks,
					माप(*chip->allocated_banks),
					GFP_KERNEL);
	अगर (!chip->allocated_banks) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	marker = &buf.data[TPM_HEADER_SIZE + 9];

	rsp_len = be32_to_cpup((__be32 *)&buf.data[2]);
	end = &buf.data[rsp_len];

	क्रम (i = 0; i < nr_possible_banks; i++) अणु
		pcr_select_offset = marker +
			दुरत्व(काष्ठा tpm2_pcr_selection, size_of_select);
		अगर (pcr_select_offset >= end) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण

		स_नकल(&pcr_selection, marker, माप(pcr_selection));
		hash_alg = be16_to_cpu(pcr_selection.hash_alg);

		pcr_select_offset = स_प्रथम_inv(pcr_selection.pcr_select, 0,
					       pcr_selection.size_of_select);
		अगर (pcr_select_offset) अणु
			chip->allocated_banks[nr_alloc_banks].alg_id = hash_alg;

			rc = tpm2_init_bank_info(chip, nr_alloc_banks);
			अगर (rc < 0)
				अवरोध;

			nr_alloc_banks++;
		पूर्ण

		माप_pcr_selection = माप(pcr_selection.hash_alg) +
			माप(pcr_selection.size_of_select) +
			pcr_selection.size_of_select;
		marker = marker + माप_pcr_selection;
	पूर्ण

	chip->nr_allocated_banks = nr_alloc_banks;
out:
	tpm_buf_destroy(&buf);

	वापस rc;
पूर्ण

पूर्णांक tpm2_get_cc_attrs_tbl(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_buf buf;
	u32 nr_commands;
	__be32 *attrs;
	u32 cc;
	पूर्णांक i;
	पूर्णांक rc;

	rc = tpm2_get_tpm_pt(chip, TPM_PT_TOTAL_COMMANDS, &nr_commands, शून्य);
	अगर (rc)
		जाओ out;

	अगर (nr_commands > 0xFFFFF) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	chip->cc_attrs_tbl = devm_kसुस्मृति(&chip->dev, 4, nr_commands,
					  GFP_KERNEL);
	अगर (!chip->cc_attrs_tbl) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	अगर (rc)
		जाओ out;

	tpm_buf_append_u32(&buf, TPM2_CAP_COMMANDS);
	tpm_buf_append_u32(&buf, TPM2_CC_FIRST);
	tpm_buf_append_u32(&buf, nr_commands);

	rc = tpm_transmit_cmd(chip, &buf, 9 + 4 * nr_commands, शून्य);
	अगर (rc) अणु
		tpm_buf_destroy(&buf);
		जाओ out;
	पूर्ण

	अगर (nr_commands !=
	    be32_to_cpup((__be32 *)&buf.data[TPM_HEADER_SIZE + 5])) अणु
		rc = -EFAULT;
		tpm_buf_destroy(&buf);
		जाओ out;
	पूर्ण

	chip->nr_commands = nr_commands;

	attrs = (__be32 *)&buf.data[TPM_HEADER_SIZE + 9];
	क्रम (i = 0; i < nr_commands; i++, attrs++) अणु
		chip->cc_attrs_tbl[i] = be32_to_cpup(attrs);
		cc = chip->cc_attrs_tbl[i] & 0xFFFF;

		अगर (cc == TPM2_CC_CONTEXT_SAVE || cc == TPM2_CC_FLUSH_CONTEXT) अणु
			chip->cc_attrs_tbl[i] &=
				~(GENMASK(2, 0) << TPM2_CC_ATTR_CHANDLES);
			chip->cc_attrs_tbl[i] |= 1 << TPM2_CC_ATTR_CHANDLES;
		पूर्ण
	पूर्ण

	tpm_buf_destroy(&buf);

out:
	अगर (rc > 0)
		rc = -ENODEV;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm2_get_cc_attrs_tbl);

/**
 * tpm2_startup - turn on the TPM
 * @chip: TPM chip to use
 *
 * Normally the firmware should start the TPM. This function is provided as a
 * workaround अगर this करोes not happen. A legal हाल क्रम this could be क्रम
 * example when a TPM emulator is used.
 *
 * Return: same as tpm_transmit_cmd()
 */

अटल पूर्णांक tpm2_startup(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	dev_info(&chip->dev, "starting up the TPM manually\n");

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_STARTUP);
	अगर (rc < 0)
		वापस rc;

	tpm_buf_append_u16(&buf, TPM2_SU_CLEAR);
	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to start the TPM");
	tpm_buf_destroy(&buf);

	वापस rc;
पूर्ण

/**
 * tpm2_स्वतः_startup - Perक्रमm the standard स्वतःmatic TPM initialization
 *                     sequence
 * @chip: TPM chip to use
 *
 * Returns 0 on success, < 0 in हाल of fatal error.
 */
पूर्णांक tpm2_स्वतः_startup(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	rc = tpm2_get_समयouts(chip);
	अगर (rc)
		जाओ out;

	rc = tpm2_करो_selftest(chip);
	अगर (rc && rc != TPM2_RC_INITIALIZE)
		जाओ out;

	अगर (rc == TPM2_RC_INITIALIZE) अणु
		rc = tpm2_startup(chip);
		अगर (rc)
			जाओ out;

		rc = tpm2_करो_selftest(chip);
		अगर (rc)
			जाओ out;
	पूर्ण

	rc = tpm2_get_cc_attrs_tbl(chip);

out:
	अगर (rc > 0)
		rc = -ENODEV;
	वापस rc;
पूर्ण

पूर्णांक tpm2_find_cc(काष्ठा tpm_chip *chip, u32 cc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chip->nr_commands; i++)
		अगर (cc == (chip->cc_attrs_tbl[i] & GENMASK(15, 0)))
			वापस i;

	वापस -1;
पूर्ण
