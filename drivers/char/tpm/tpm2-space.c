<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Intel Corporation
 *
 * Authors:
 * Jarkko Sakkinen <jarkko.sakkinen@linux.पूर्णांकel.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * This file contains TPM2 protocol implementations of the commands
 * used by the kernel पूर्णांकernally.
 */

#समावेश <linux/gfp.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "tpm.h"

क्रमागत tpm2_handle_types अणु
	TPM2_HT_HMAC_SESSION	= 0x02000000,
	TPM2_HT_POLICY_SESSION	= 0x03000000,
	TPM2_HT_TRANSIENT	= 0x80000000,
पूर्ण;

काष्ठा tpm2_context अणु
	__be64 sequence;
	__be32 saved_handle;
	__be32 hierarchy;
	__be16 blob_size;
पूर्ण __packed;

अटल व्योम tpm2_flush_sessions(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(space->session_tbl); i++) अणु
		अगर (space->session_tbl[i])
			tpm2_flush_context(chip, space->session_tbl[i]);
	पूर्ण
पूर्ण

पूर्णांक tpm2_init_space(काष्ठा tpm_space *space, अचिन्हित पूर्णांक buf_size)
अणु
	space->context_buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!space->context_buf)
		वापस -ENOMEM;

	space->session_buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (space->session_buf == शून्य) अणु
		kमुक्त(space->context_buf);
		/* Prevent caller getting a dangling poपूर्णांकer. */
		space->context_buf = शून्य;
		वापस -ENOMEM;
	पूर्ण

	space->buf_size = buf_size;
	वापस 0;
पूर्ण

व्योम tpm2_del_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space)
अणु
	mutex_lock(&chip->tpm_mutex);
	अगर (!tpm_chip_start(chip)) अणु
		tpm2_flush_sessions(chip, space);
		tpm_chip_stop(chip);
	पूर्ण
	mutex_unlock(&chip->tpm_mutex);
	kमुक्त(space->context_buf);
	kमुक्त(space->session_buf);
पूर्ण

अटल पूर्णांक tpm2_load_context(काष्ठा tpm_chip *chip, u8 *buf,
			     अचिन्हित पूर्णांक *offset, u32 *handle)
अणु
	काष्ठा tpm_buf tbuf;
	काष्ठा tpm2_context *ctx;
	अचिन्हित पूर्णांक body_size;
	पूर्णांक rc;

	rc = tpm_buf_init(&tbuf, TPM2_ST_NO_SESSIONS, TPM2_CC_CONTEXT_LOAD);
	अगर (rc)
		वापस rc;

	ctx = (काष्ठा tpm2_context *)&buf[*offset];
	body_size = माप(*ctx) + be16_to_cpu(ctx->blob_size);
	tpm_buf_append(&tbuf, &buf[*offset], body_size);

	rc = tpm_transmit_cmd(chip, &tbuf, 4, शून्य);
	अगर (rc < 0) अणु
		dev_warn(&chip->dev, "%s: failed with a system error %d\n",
			 __func__, rc);
		tpm_buf_destroy(&tbuf);
		वापस -EFAULT;
	पूर्ण अन्यथा अगर (tpm2_rc_value(rc) == TPM2_RC_HANDLE ||
		   rc == TPM2_RC_REFERENCE_H0) अणु
		/*
		 * TPM_RC_HANDLE means that the session context can't
		 * be loaded because of an पूर्णांकernal counter mismatch
		 * that makes the TPM think there might have been a
		 * replay.  This might happen अगर the context was saved
		 * and loaded outside the space.
		 *
		 * TPM_RC_REFERENCE_H0 means the session has been
		 * flushed outside the space
		 */
		*handle = 0;
		tpm_buf_destroy(&tbuf);
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (rc > 0) अणु
		dev_warn(&chip->dev, "%s: failed with a TPM error 0x%04X\n",
			 __func__, rc);
		tpm_buf_destroy(&tbuf);
		वापस -EFAULT;
	पूर्ण

	*handle = be32_to_cpup((__be32 *)&tbuf.data[TPM_HEADER_SIZE]);
	*offset += body_size;

	tpm_buf_destroy(&tbuf);
	वापस 0;
पूर्ण

अटल पूर्णांक tpm2_save_context(काष्ठा tpm_chip *chip, u32 handle, u8 *buf,
			     अचिन्हित पूर्णांक buf_size, अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा tpm_buf tbuf;
	अचिन्हित पूर्णांक body_size;
	पूर्णांक rc;

	rc = tpm_buf_init(&tbuf, TPM2_ST_NO_SESSIONS, TPM2_CC_CONTEXT_SAVE);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&tbuf, handle);

	rc = tpm_transmit_cmd(chip, &tbuf, 0, शून्य);
	अगर (rc < 0) अणु
		dev_warn(&chip->dev, "%s: failed with a system error %d\n",
			 __func__, rc);
		tpm_buf_destroy(&tbuf);
		वापस -EFAULT;
	पूर्ण अन्यथा अगर (tpm2_rc_value(rc) == TPM2_RC_REFERENCE_H0) अणु
		tpm_buf_destroy(&tbuf);
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (rc) अणु
		dev_warn(&chip->dev, "%s: failed with a TPM error 0x%04X\n",
			 __func__, rc);
		tpm_buf_destroy(&tbuf);
		वापस -EFAULT;
	पूर्ण

	body_size = tpm_buf_length(&tbuf) - TPM_HEADER_SIZE;
	अगर ((*offset + body_size) > buf_size) अणु
		dev_warn(&chip->dev, "%s: out of backing storage\n", __func__);
		tpm_buf_destroy(&tbuf);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&buf[*offset], &tbuf.data[TPM_HEADER_SIZE], body_size);
	*offset += body_size;
	tpm_buf_destroy(&tbuf);
	वापस 0;
पूर्ण

व्योम tpm2_flush_space(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(space->context_tbl); i++)
		अगर (space->context_tbl[i] && ~space->context_tbl[i])
			tpm2_flush_context(chip, space->context_tbl[i]);

	tpm2_flush_sessions(chip, space);
पूर्ण

अटल पूर्णांक tpm2_load_space(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	अचिन्हित पूर्णांक offset;
	पूर्णांक i;
	पूर्णांक rc;

	क्रम (i = 0, offset = 0; i < ARRAY_SIZE(space->context_tbl); i++) अणु
		अगर (!space->context_tbl[i])
			जारी;

		/* sanity check, should never happen */
		अगर (~space->context_tbl[i]) अणु
			dev_err(&chip->dev, "context table is inconsistent");
			वापस -EFAULT;
		पूर्ण

		rc = tpm2_load_context(chip, space->context_buf, &offset,
				       &space->context_tbl[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	क्रम (i = 0, offset = 0; i < ARRAY_SIZE(space->session_tbl); i++) अणु
		u32 handle;

		अगर (!space->session_tbl[i])
			जारी;

		rc = tpm2_load_context(chip, space->session_buf,
				       &offset, &handle);
		अगर (rc == -ENOENT) अणु
			/* load failed, just क्रमget session */
			space->session_tbl[i] = 0;
		पूर्ण अन्यथा अगर (rc) अणु
			tpm2_flush_space(chip);
			वापस rc;
		पूर्ण
		अगर (handle != space->session_tbl[i]) अणु
			dev_warn(&chip->dev, "session restored to wrong handle\n");
			tpm2_flush_space(chip);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool tpm2_map_to_phandle(काष्ठा tpm_space *space, व्योम *handle)
अणु
	u32 vhandle = be32_to_cpup((__be32 *)handle);
	u32 phandle;
	पूर्णांक i;

	i = 0xFFFFFF - (vhandle & 0xFFFFFF);
	अगर (i >= ARRAY_SIZE(space->context_tbl) || !space->context_tbl[i])
		वापस false;

	phandle = space->context_tbl[i];
	*((__be32 *)handle) = cpu_to_be32(phandle);
	वापस true;
पूर्ण

अटल पूर्णांक tpm2_map_command(काष्ठा tpm_chip *chip, u32 cc, u8 *cmd)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	अचिन्हित पूर्णांक nr_handles;
	u32 attrs;
	__be32 *handle;
	पूर्णांक i;

	i = tpm2_find_cc(chip, cc);
	अगर (i < 0)
		वापस -EINVAL;

	attrs = chip->cc_attrs_tbl[i];
	nr_handles = (attrs >> TPM2_CC_ATTR_CHANDLES) & GENMASK(2, 0);

	handle = (__be32 *)&cmd[TPM_HEADER_SIZE];
	क्रम (i = 0; i < nr_handles; i++, handle++) अणु
		अगर ((be32_to_cpu(*handle) & 0xFF000000) == TPM2_HT_TRANSIENT) अणु
			अगर (!tpm2_map_to_phandle(space, handle))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_find_and_validate_cc(काष्ठा tpm_chip *chip,
				    काष्ठा tpm_space *space,
				    स्थिर व्योम *cmd, माप_प्रकार len)
अणु
	स्थिर काष्ठा tpm_header *header = (स्थिर व्योम *)cmd;
	पूर्णांक i;
	u32 cc;
	u32 attrs;
	अचिन्हित पूर्णांक nr_handles;

	अगर (len < TPM_HEADER_SIZE || !chip->nr_commands)
		वापस -EINVAL;

	cc = be32_to_cpu(header->ordinal);

	i = tpm2_find_cc(chip, cc);
	अगर (i < 0) अणु
		dev_dbg(&chip->dev, "0x%04X is an invalid command\n",
			cc);
		वापस -EOPNOTSUPP;
	पूर्ण

	attrs = chip->cc_attrs_tbl[i];
	nr_handles =
		4 * ((attrs >> TPM2_CC_ATTR_CHANDLES) & GENMASK(2, 0));
	अगर (len < TPM_HEADER_SIZE + 4 * nr_handles)
		जाओ err_len;

	वापस cc;
err_len:
	dev_dbg(&chip->dev, "%s: insufficient command length %zu", __func__,
		len);
	वापस -EINVAL;
पूर्ण

पूर्णांक tpm2_prepare_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space, u8 *cmd,
		       माप_प्रकार cmdsiz)
अणु
	पूर्णांक rc;
	पूर्णांक cc;

	अगर (!space)
		वापस 0;

	cc = tpm_find_and_validate_cc(chip, space, cmd, cmdsiz);
	अगर (cc < 0)
		वापस cc;

	स_नकल(&chip->work_space.context_tbl, &space->context_tbl,
	       माप(space->context_tbl));
	स_नकल(&chip->work_space.session_tbl, &space->session_tbl,
	       माप(space->session_tbl));
	स_नकल(chip->work_space.context_buf, space->context_buf,
	       space->buf_size);
	स_नकल(chip->work_space.session_buf, space->session_buf,
	       space->buf_size);

	rc = tpm2_load_space(chip);
	अगर (rc) अणु
		tpm2_flush_space(chip);
		वापस rc;
	पूर्ण

	rc = tpm2_map_command(chip, cc, cmd);
	अगर (rc) अणु
		tpm2_flush_space(chip);
		वापस rc;
	पूर्ण

	chip->last_cc = cc;
	वापस 0;
पूर्ण

अटल bool tpm2_add_session(काष्ठा tpm_chip *chip, u32 handle)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(space->session_tbl); i++)
		अगर (space->session_tbl[i] == 0)
			अवरोध;

	अगर (i == ARRAY_SIZE(space->session_tbl))
		वापस false;

	space->session_tbl[i] = handle;
	वापस true;
पूर्ण

अटल u32 tpm2_map_to_vhandle(काष्ठा tpm_space *space, u32 phandle, bool alloc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(space->context_tbl); i++) अणु
		अगर (alloc) अणु
			अगर (!space->context_tbl[i]) अणु
				space->context_tbl[i] = phandle;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (space->context_tbl[i] == phandle)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(space->context_tbl))
		वापस 0;

	वापस TPM2_HT_TRANSIENT | (0xFFFFFF - i);
पूर्ण

अटल पूर्णांक tpm2_map_response_header(काष्ठा tpm_chip *chip, u32 cc, u8 *rsp,
				    माप_प्रकार len)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	काष्ठा tpm_header *header = (काष्ठा tpm_header *)rsp;
	u32 phandle;
	u32 phandle_type;
	u32 vhandle;
	u32 attrs;
	पूर्णांक i;

	अगर (be32_to_cpu(header->वापस_code) != TPM2_RC_SUCCESS)
		वापस 0;

	i = tpm2_find_cc(chip, cc);
	/* sanity check, should never happen */
	अगर (i < 0)
		वापस -EFAULT;

	attrs = chip->cc_attrs_tbl[i];
	अगर (!((attrs >> TPM2_CC_ATTR_RHANDLE) & 1))
		वापस 0;

	phandle = be32_to_cpup((__be32 *)&rsp[TPM_HEADER_SIZE]);
	phandle_type = phandle & 0xFF000000;

	चयन (phandle_type) अणु
	हाल TPM2_HT_TRANSIENT:
		vhandle = tpm2_map_to_vhandle(space, phandle, true);
		अगर (!vhandle)
			जाओ out_no_slots;

		*(__be32 *)&rsp[TPM_HEADER_SIZE] = cpu_to_be32(vhandle);
		अवरोध;
	हाल TPM2_HT_HMAC_SESSION:
	हाल TPM2_HT_POLICY_SESSION:
		अगर (!tpm2_add_session(chip, phandle))
			जाओ out_no_slots;
		अवरोध;
	शेष:
		dev_err(&chip->dev, "%s: unknown handle 0x%08X\n",
			__func__, phandle);
		अवरोध;
	पूर्ण

	वापस 0;
out_no_slots:
	tpm2_flush_context(chip, phandle);
	dev_warn(&chip->dev, "%s: out of slots for 0x%08X\n", __func__,
		 phandle);
	वापस -ENOMEM;
पूर्ण

काष्ठा tpm2_cap_handles अणु
	u8 more_data;
	__be32 capability;
	__be32 count;
	__be32 handles[];
पूर्ण __packed;

अटल पूर्णांक tpm2_map_response_body(काष्ठा tpm_chip *chip, u32 cc, u8 *rsp,
				  माप_प्रकार len)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	काष्ठा tpm_header *header = (काष्ठा tpm_header *)rsp;
	काष्ठा tpm2_cap_handles *data;
	u32 phandle;
	u32 phandle_type;
	u32 vhandle;
	पूर्णांक i;
	पूर्णांक j;

	अगर (cc != TPM2_CC_GET_CAPABILITY ||
	    be32_to_cpu(header->वापस_code) != TPM2_RC_SUCCESS) अणु
		वापस 0;
	पूर्ण

	अगर (len < TPM_HEADER_SIZE + 9)
		वापस -EFAULT;

	data = (व्योम *)&rsp[TPM_HEADER_SIZE];
	अगर (be32_to_cpu(data->capability) != TPM2_CAP_HANDLES)
		वापस 0;

	अगर (len != TPM_HEADER_SIZE + 9 + 4 * be32_to_cpu(data->count))
		वापस -EFAULT;

	क्रम (i = 0, j = 0; i < be32_to_cpu(data->count); i++) अणु
		phandle = be32_to_cpup((__be32 *)&data->handles[i]);
		phandle_type = phandle & 0xFF000000;

		चयन (phandle_type) अणु
		हाल TPM2_HT_TRANSIENT:
			vhandle = tpm2_map_to_vhandle(space, phandle, false);
			अगर (!vhandle)
				अवरोध;

			data->handles[j] = cpu_to_be32(vhandle);
			j++;
			अवरोध;

		शेष:
			data->handles[j] = cpu_to_be32(phandle);
			j++;
			अवरोध;
		पूर्ण

	पूर्ण

	header->length = cpu_to_be32(TPM_HEADER_SIZE + 9 + 4 * j);
	data->count = cpu_to_be32(j);
	वापस 0;
पूर्ण

अटल पूर्णांक tpm2_save_space(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_space *space = &chip->work_space;
	अचिन्हित पूर्णांक offset;
	पूर्णांक i;
	पूर्णांक rc;

	क्रम (i = 0, offset = 0; i < ARRAY_SIZE(space->context_tbl); i++) अणु
		अगर (!(space->context_tbl[i] && ~space->context_tbl[i]))
			जारी;

		rc = tpm2_save_context(chip, space->context_tbl[i],
				       space->context_buf, space->buf_size,
				       &offset);
		अगर (rc == -ENOENT) अणु
			space->context_tbl[i] = 0;
			जारी;
		पूर्ण अन्यथा अगर (rc)
			वापस rc;

		tpm2_flush_context(chip, space->context_tbl[i]);
		space->context_tbl[i] = ~0;
	पूर्ण

	क्रम (i = 0, offset = 0; i < ARRAY_SIZE(space->session_tbl); i++) अणु
		अगर (!space->session_tbl[i])
			जारी;

		rc = tpm2_save_context(chip, space->session_tbl[i],
				       space->session_buf, space->buf_size,
				       &offset);
		अगर (rc == -ENOENT) अणु
			/* handle error saving session, just क्रमget it */
			space->session_tbl[i] = 0;
		पूर्ण अन्यथा अगर (rc < 0) अणु
			tpm2_flush_space(chip);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tpm2_commit_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space,
		      व्योम *buf, माप_प्रकार *bufsiz)
अणु
	काष्ठा tpm_header *header = buf;
	पूर्णांक rc;

	अगर (!space)
		वापस 0;

	rc = tpm2_map_response_header(chip, chip->last_cc, buf, *bufsiz);
	अगर (rc) अणु
		tpm2_flush_space(chip);
		जाओ out;
	पूर्ण

	rc = tpm2_map_response_body(chip, chip->last_cc, buf, *bufsiz);
	अगर (rc) अणु
		tpm2_flush_space(chip);
		जाओ out;
	पूर्ण

	rc = tpm2_save_space(chip);
	अगर (rc) अणु
		tpm2_flush_space(chip);
		जाओ out;
	पूर्ण

	*bufsiz = be32_to_cpu(header->length);

	स_नकल(&space->context_tbl, &chip->work_space.context_tbl,
	       माप(space->context_tbl));
	स_नकल(&space->session_tbl, &chip->work_space.session_tbl,
	       माप(space->session_tbl));
	स_नकल(space->context_buf, chip->work_space.context_buf,
	       space->buf_size);
	स_नकल(space->session_buf, chip->work_space.session_buf,
	       space->buf_size);

	वापस 0;
out:
	dev_err(&chip->dev, "%s: error %d\n", __func__, rc);
	वापस rc;
पूर्ण
