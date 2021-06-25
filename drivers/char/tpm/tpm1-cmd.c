<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2014 Intel Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 */

#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "tpm.h"

#घोषणा TPM_MAX_ORDINAL 243

/*
 * Array with one entry per ordinal defining the maximum amount
 * of समय the chip could take to वापस the result.  The ordinal
 * designation of लघु, medium or दीर्घ is defined in a table in
 * TCG Specअगरication TPM Main Part 2 TPM Structures Section 17. The
 * values of the SHORT, MEDIUM, and LONG durations are retrieved
 * from the chip during initialization with a call to tpm_get_समयouts.
 */
अटल स्थिर u8 tpm1_ordinal_duration[TPM_MAX_ORDINAL] = अणु
	TPM_UNDEFINED,		/* 0 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 5 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 10 */
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_LONG,
	TPM_LONG,
	TPM_MEDIUM,		/* 15 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_LONG,
	TPM_SHORT,		/* 20 */
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHORT,		/* 25 */
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_SHORT,
	TPM_SHORT,
	TPM_MEDIUM,		/* 30 */
	TPM_LONG,
	TPM_MEDIUM,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,		/* 35 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 40 */
	TPM_LONG,
	TPM_MEDIUM,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,		/* 45 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_LONG,
	TPM_MEDIUM,		/* 50 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 55 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 60 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHORT,
	TPM_SHORT,
	TPM_MEDIUM,		/* 65 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 70 */
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 75 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_LONG,		/* 80 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
	TPM_LONG,
	TPM_SHORT,
	TPM_UNDEFINED,		/* 85 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 90 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,		/* 95 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 100 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 105 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 110 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,		/* 115 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_LONG,		/* 120 */
	TPM_LONG,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_SHORT,
	TPM_SHORT,		/* 125 */
	TPM_SHORT,
	TPM_LONG,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,		/* 130 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_UNDEFINED,		/* 135 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 140 */
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 145 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 150 */
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,		/* 155 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 160 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 165 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_LONG,		/* 170 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 175 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_MEDIUM,		/* 180 */
	TPM_SHORT,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,		/* 185 */
	TPM_SHORT,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 190 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 195 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 200 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,
	TPM_SHORT,		/* 205 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_MEDIUM,		/* 210 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_MEDIUM,
	TPM_UNDEFINED,		/* 215 */
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,
	TPM_SHORT,		/* 220 */
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_SHORT,
	TPM_UNDEFINED,		/* 225 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 230 */
	TPM_LONG,
	TPM_MEDIUM,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,		/* 235 */
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_UNDEFINED,
	TPM_SHORT,		/* 240 */
	TPM_UNDEFINED,
	TPM_MEDIUM,
पूर्ण;

/**
 * tpm1_calc_ordinal_duration() - calculate the maximum command duration
 * @chip:    TPM chip to use.
 * @ordinal: TPM command ordinal.
 *
 * The function वापसs the maximum amount of समय the chip could take
 * to वापस the result क्रम a particular ordinal in jअगरfies.
 *
 * Return: A maximal duration समय क्रम an ordinal in jअगरfies.
 */
अचिन्हित दीर्घ tpm1_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal)
अणु
	पूर्णांक duration_idx = TPM_UNDEFINED;
	पूर्णांक duration = 0;

	/*
	 * We only have a duration table क्रम रक्षित commands, where the upper
	 * 16 bits are 0. For the few other ordinals the fallback will be used.
	 */
	अगर (ordinal < TPM_MAX_ORDINAL)
		duration_idx = tpm1_ordinal_duration[ordinal];

	अगर (duration_idx != TPM_UNDEFINED)
		duration = chip->duration[duration_idx];
	अगर (duration <= 0)
		वापस 2 * 60 * HZ;
	अन्यथा
		वापस duration;
पूर्ण

#घोषणा TPM_ORD_STARTUP 153
#घोषणा TPM_ST_CLEAR 1

/**
 * tpm_startup() - turn on the TPM
 * @chip: TPM chip to use
 *
 * Normally the firmware should start the TPM. This function is provided as a
 * workaround अगर this करोes not happen. A legal हाल क्रम this could be क्रम
 * example when a TPM emulator is used.
 *
 * Return: same as tpm_transmit_cmd()
 */
अटल पूर्णांक tpm1_startup(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	dev_info(&chip->dev, "starting up the TPM manually\n");

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_STARTUP);
	अगर (rc < 0)
		वापस rc;

	tpm_buf_append_u16(&buf, TPM_ST_CLEAR);

	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to start the TPM");
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

पूर्णांक tpm1_get_समयouts(काष्ठा tpm_chip *chip)
अणु
	cap_t cap;
	अचिन्हित दीर्घ समयout_old[4], समयout_chip[4], समयout_eff[4];
	अचिन्हित दीर्घ durations[3];
	sमाप_प्रकार rc;

	rc = tpm1_अ_लोap(chip, TPM_CAP_PROP_TIS_TIMEOUT, &cap, शून्य,
			 माप(cap.समयout));
	अगर (rc == TPM_ERR_INVALID_POSTINIT) अणु
		अगर (tpm1_startup(chip))
			वापस rc;

		rc = tpm1_अ_लोap(chip, TPM_CAP_PROP_TIS_TIMEOUT, &cap,
				 "attempting to determine the timeouts",
				 माप(cap.समयout));
	पूर्ण

	अगर (rc) अणु
		dev_err(&chip->dev, "A TPM error (%zd) occurred attempting to determine the timeouts\n",
			rc);
		वापस rc;
	पूर्ण

	समयout_old[0] = jअगरfies_to_usecs(chip->समयout_a);
	समयout_old[1] = jअगरfies_to_usecs(chip->समयout_b);
	समयout_old[2] = jअगरfies_to_usecs(chip->समयout_c);
	समयout_old[3] = jअगरfies_to_usecs(chip->समयout_d);
	समयout_chip[0] = be32_to_cpu(cap.समयout.a);
	समयout_chip[1] = be32_to_cpu(cap.समयout.b);
	समयout_chip[2] = be32_to_cpu(cap.समयout.c);
	समयout_chip[3] = be32_to_cpu(cap.समयout.d);
	स_नकल(समयout_eff, समयout_chip, माप(समयout_eff));

	/*
	 * Provide ability क्रम venकरोr overrides of समयout values in हाल
	 * of misreporting.
	 */
	अगर (chip->ops->update_समयouts)
		chip->ops->update_समयouts(chip, समयout_eff);

	अगर (!chip->समयout_adjusted) अणु
		/* Restore शेष अगर chip reported 0 */
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(समयout_eff); i++) अणु
			अगर (समयout_eff[i])
				जारी;

			समयout_eff[i] = समयout_old[i];
			chip->समयout_adjusted = true;
		पूर्ण

		अगर (समयout_eff[0] != 0 && समयout_eff[0] < 1000) अणु
			/* समयouts in msec rather usec */
			क्रम (i = 0; i != ARRAY_SIZE(समयout_eff); i++)
				समयout_eff[i] *= 1000;
			chip->समयout_adjusted = true;
		पूर्ण
	पूर्ण

	/* Report adjusted समयouts */
	अगर (chip->समयout_adjusted) अणु
		dev_info(&chip->dev, HW_ERR "Adjusting reported timeouts: A %lu->%luus B %lu->%luus C %lu->%luus D %lu->%luus\n",
			 समयout_chip[0], समयout_eff[0],
			 समयout_chip[1], समयout_eff[1],
			 समयout_chip[2], समयout_eff[2],
			 समयout_chip[3], समयout_eff[3]);
	पूर्ण

	chip->समयout_a = usecs_to_jअगरfies(समयout_eff[0]);
	chip->समयout_b = usecs_to_jअगरfies(समयout_eff[1]);
	chip->समयout_c = usecs_to_jअगरfies(समयout_eff[2]);
	chip->समयout_d = usecs_to_jअगरfies(समयout_eff[3]);

	rc = tpm1_अ_लोap(chip, TPM_CAP_PROP_TIS_DURATION, &cap,
			 "attempting to determine the durations",
			  माप(cap.duration));
	अगर (rc)
		वापस rc;

	chip->duration[TPM_SHORT] =
		usecs_to_jअगरfies(be32_to_cpu(cap.duration.tpm_लघु));
	chip->duration[TPM_MEDIUM] =
		usecs_to_jअगरfies(be32_to_cpu(cap.duration.tpm_medium));
	chip->duration[TPM_LONG] =
		usecs_to_jअगरfies(be32_to_cpu(cap.duration.tpm_दीर्घ));
	chip->duration[TPM_LONG_LONG] = 0; /* not used under 1.2 */

	/*
	 * Provide the ability क्रम venकरोr overrides of duration values in हाल
	 * of misreporting.
	 */
	अगर (chip->ops->update_durations)
		chip->ops->update_durations(chip, durations);

	अगर (chip->duration_adjusted) अणु
		dev_info(&chip->dev, HW_ERR "Adjusting reported durations.");
		chip->duration[TPM_SHORT] = durations[0];
		chip->duration[TPM_MEDIUM] = durations[1];
		chip->duration[TPM_LONG] = durations[2];
	पूर्ण

	/* The Broadcom BCM0102 chipset in a Dell Latitude D820 माला_लो the above
	 * value wrong and apparently reports msecs rather than usecs. So we
	 * fix up the resulting too-small TPM_SHORT value to make things work.
	 * We also scale the TPM_MEDIUM and -_LONG values by 1000.
	 */
	अगर (chip->duration[TPM_SHORT] < (HZ / 100)) अणु
		chip->duration[TPM_SHORT] = HZ;
		chip->duration[TPM_MEDIUM] *= 1000;
		chip->duration[TPM_LONG] *= 1000;
		chip->duration_adjusted = true;
		dev_info(&chip->dev, "Adjusting TPM timeout parameters.");
	पूर्ण

	chip->flags |= TPM_CHIP_FLAG_HAVE_TIMEOUTS;
	वापस 0;
पूर्ण

#घोषणा TPM_ORD_PCR_EXTEND 20
पूर्णांक tpm1_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx, स्थिर u8 *hash,
		    स्थिर अक्षर *log_msg)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_PCR_EXTEND);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, pcr_idx);
	tpm_buf_append(&buf, hash, TPM_DIGEST_SIZE);

	rc = tpm_transmit_cmd(chip, &buf, TPM_DIGEST_SIZE, log_msg);
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

#घोषणा TPM_ORD_GET_CAP 101
sमाप_प्रकार tpm1_अ_लोap(काष्ठा tpm_chip *chip, u32 subcap_id, cap_t *cap,
		    स्थिर अक्षर *desc, माप_प्रकार min_cap_length)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_GET_CAP);
	अगर (rc)
		वापस rc;

	अगर (subcap_id == TPM_CAP_VERSION_1_1 ||
	    subcap_id == TPM_CAP_VERSION_1_2) अणु
		tpm_buf_append_u32(&buf, subcap_id);
		tpm_buf_append_u32(&buf, 0);
	पूर्ण अन्यथा अणु
		अगर (subcap_id == TPM_CAP_FLAG_PERM ||
		    subcap_id == TPM_CAP_FLAG_VOL)
			tpm_buf_append_u32(&buf, TPM_CAP_FLAG);
		अन्यथा
			tpm_buf_append_u32(&buf, TPM_CAP_PROP);

		tpm_buf_append_u32(&buf, 4);
		tpm_buf_append_u32(&buf, subcap_id);
	पूर्ण
	rc = tpm_transmit_cmd(chip, &buf, min_cap_length, desc);
	अगर (!rc)
		*cap = *(cap_t *)&buf.data[TPM_HEADER_SIZE + 4];
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm1_अ_लोap);

#घोषणा TPM_ORD_GET_RANDOM 70
काष्ठा tpm1_get_अक्रमom_out अणु
	__be32 rng_data_len;
	u8 rng_data[TPM_MAX_RNG_DATA];
पूर्ण __packed;

/**
 * tpm1_get_अक्रमom() - get अक्रमom bytes from the TPM's RNG
 * @chip:	a &काष्ठा tpm_chip instance
 * @dest:	destination buffer क्रम the अक्रमom bytes
 * @max:	the maximum number of bytes to ग_लिखो to @dest
 *
 * Return:
 * *  number of bytes पढ़ो
 * * -त्रुटि_सं (positive TPM वापस codes are masked to -EIO)
 */
पूर्णांक tpm1_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *dest, माप_प्रकार max)
अणु
	काष्ठा tpm1_get_अक्रमom_out *out;
	u32 num_bytes =  min_t(u32, max, TPM_MAX_RNG_DATA);
	काष्ठा tpm_buf buf;
	u32 total = 0;
	पूर्णांक retries = 5;
	u32 recd;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_GET_RANDOM);
	अगर (rc)
		वापस rc;

	करो अणु
		tpm_buf_append_u32(&buf, num_bytes);

		rc = tpm_transmit_cmd(chip, &buf, माप(out->rng_data_len),
				      "attempting get random");
		अगर (rc) अणु
			अगर (rc > 0)
				rc = -EIO;
			जाओ out;
		पूर्ण

		out = (काष्ठा tpm1_get_अक्रमom_out *)&buf.data[TPM_HEADER_SIZE];

		recd = be32_to_cpu(out->rng_data_len);
		अगर (recd > num_bytes) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (tpm_buf_length(&buf) < TPM_HEADER_SIZE +
					   माप(out->rng_data_len) + recd) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		स_नकल(dest, out->rng_data, recd);

		dest += recd;
		total += recd;
		num_bytes -= recd;

		tpm_buf_reset(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_GET_RANDOM);
	पूर्ण जबतक (retries-- && total < max);

	rc = total ? (पूर्णांक)total : -EIO;
out:
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

#घोषणा TPM_ORD_PCRREAD 21
पूर्णांक tpm1_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx, u8 *res_buf)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_PCRREAD);
	अगर (rc)
		वापस rc;

	tpm_buf_append_u32(&buf, pcr_idx);

	rc = tpm_transmit_cmd(chip, &buf, TPM_DIGEST_SIZE,
			      "attempting to read a pcr value");
	अगर (rc)
		जाओ out;

	अगर (tpm_buf_length(&buf) < TPM_DIGEST_SIZE) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	स_नकल(res_buf, &buf.data[TPM_HEADER_SIZE], TPM_DIGEST_SIZE);

out:
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

#घोषणा TPM_ORD_CONTINUE_SELFTEST 83
/**
 * tpm_जारी_selftest() - run TPM's selftest
 * @chip: TPM chip to use
 *
 * Returns 0 on success, < 0 in हाल of fatal error or a value > 0 representing
 * a TPM error code.
 */
अटल पूर्णांक tpm1_जारी_selftest(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_CONTINUE_SELFTEST);
	अगर (rc)
		वापस rc;

	rc = tpm_transmit_cmd(chip, &buf, 0, "continue selftest");
	tpm_buf_destroy(&buf);
	वापस rc;
पूर्ण

/**
 * tpm1_करो_selftest - have the TPM जारी its selftest and रुको until it
 *                   can receive further commands
 * @chip: TPM chip to use
 *
 * Returns 0 on success, < 0 in हाल of fatal error or a value > 0 representing
 * a TPM error code.
 */
पूर्णांक tpm1_करो_selftest(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक loops;
	अचिन्हित पूर्णांक delay_msec = 100;
	अचिन्हित दीर्घ duration;
	u8 dummy[TPM_DIGEST_SIZE];

	duration = tpm1_calc_ordinal_duration(chip, TPM_ORD_CONTINUE_SELFTEST);

	loops = jअगरfies_to_msecs(duration) / delay_msec;

	rc = tpm1_जारी_selftest(chip);
	अगर (rc == TPM_ERR_INVALID_POSTINIT) अणु
		chip->flags |= TPM_CHIP_FLAG_ALWAYS_POWERED;
		dev_info(&chip->dev, "TPM not ready (%d)\n", rc);
	पूर्ण
	/* This may fail अगर there was no TPM driver during a suspend/resume
	 * cycle; some may वापस 10 (BAD_ORDINAL), others 28 (FAILEDSELFTEST)
	 */
	अगर (rc)
		वापस rc;

	करो अणु
		/* Attempt to पढ़ो a PCR value */
		rc = tpm1_pcr_पढ़ो(chip, 0, dummy);

		/* Some buggy TPMs will not respond to tpm_tis_पढ़ोy() क्रम
		 * around 300ms जबतक the self test is ongoing, keep trying
		 * until the self test duration expires.
		 */
		अगर (rc == -ETIME) अणु
			dev_info(&chip->dev, HW_ERR "TPM command timed out during continue self test");
			tpm_msleep(delay_msec);
			जारी;
		पूर्ण

		अगर (rc == TPM_ERR_DISABLED || rc == TPM_ERR_DEACTIVATED) अणु
			dev_info(&chip->dev, "TPM is disabled/deactivated (0x%X)\n",
				 rc);
			/* TPM is disabled and/or deactivated; driver can
			 * proceed and TPM करोes handle commands क्रम
			 * suspend/resume correctly
			 */
			वापस 0;
		पूर्ण
		अगर (rc != TPM_WARN_DOING_SELFTEST)
			वापस rc;
		tpm_msleep(delay_msec);
	पूर्ण जबतक (--loops > 0);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm1_करो_selftest);

/**
 * tpm1_स्वतः_startup - Perक्रमm the standard स्वतःmatic TPM initialization
 *                     sequence
 * @chip: TPM chip to use
 *
 * Returns 0 on success, < 0 in हाल of fatal error.
 */
पूर्णांक tpm1_स्वतः_startup(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	rc = tpm1_get_समयouts(chip);
	अगर (rc)
		जाओ out;
	rc = tpm1_करो_selftest(chip);
	अगर (rc) अणु
		dev_err(&chip->dev, "TPM self test failed\n");
		जाओ out;
	पूर्ण

	वापस rc;
out:
	अगर (rc > 0)
		rc = -ENODEV;
	वापस rc;
पूर्ण

#घोषणा TPM_ORD_SAVESTATE 152

/**
 * tpm1_pm_suspend() - pm suspend handler
 * @chip: TPM chip to use.
 * @tpm_suspend_pcr: flush pcr क्रम buggy TPM chips.
 *
 * The functions saves the TPM state to be restored on resume.
 *
 * Return:
 * * 0 on success,
 * * < 0 on error.
 */
पूर्णांक tpm1_pm_suspend(काष्ठा tpm_chip *chip, u32 tpm_suspend_pcr)
अणु
	u8 dummy_hash[TPM_DIGEST_SIZE] = अणु 0 पूर्ण;
	काष्ठा tpm_buf buf;
	अचिन्हित पूर्णांक try;
	पूर्णांक rc;


	/* क्रम buggy tpm, flush pcrs with extend to selected dummy */
	अगर (tpm_suspend_pcr)
		rc = tpm1_pcr_extend(chip, tpm_suspend_pcr, dummy_hash,
				     "extending dummy pcr before suspend");

	rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_SAVESTATE);
	अगर (rc)
		वापस rc;
	/* now करो the actual savestate */
	क्रम (try = 0; try < TPM_RETRY; try++) अणु
		rc = tpm_transmit_cmd(chip, &buf, 0, शून्य);
		/*
		 * If the TPM indicates that it is too busy to respond to
		 * this command then retry beक्रमe giving up.  It can take
		 * several seconds क्रम this TPM to be पढ़ोy.
		 *
		 * This can happen अगर the TPM has alपढ़ोy been sent the
		 * SaveState command beक्रमe the driver has loaded.  TCG 1.2
		 * specअगरication states that any communication after SaveState
		 * may cause the TPM to invalidate previously saved state.
		 */
		अगर (rc != TPM_WARN_RETRY)
			अवरोध;
		tpm_msleep(TPM_TIMEOUT_RETRY);

		tpm_buf_reset(&buf, TPM_TAG_RQU_COMMAND, TPM_ORD_SAVESTATE);
	पूर्ण

	अगर (rc)
		dev_err(&chip->dev, "Error (%d) sending savestate before suspend\n",
			rc);
	अन्यथा अगर (try > 0)
		dev_warn(&chip->dev, "TPM savestate took %dms\n",
			 try * TPM_TIMEOUT_RETRY);

	tpm_buf_destroy(&buf);

	वापस rc;
पूर्ण

/**
 * tpm1_get_pcr_allocation() - initialize the allocated bank
 * @chip: TPM chip to use.
 *
 * The function initializes the SHA1 allocated bank to extend PCR
 *
 * Return:
 * * 0 on success,
 * * < 0 on error.
 */
पूर्णांक tpm1_get_pcr_allocation(काष्ठा tpm_chip *chip)
अणु
	chip->allocated_banks = kसुस्मृति(1, माप(*chip->allocated_banks),
					GFP_KERNEL);
	अगर (!chip->allocated_banks)
		वापस -ENOMEM;

	chip->allocated_banks[0].alg_id = TPM_ALG_SHA1;
	chip->allocated_banks[0].digest_size = hash_digest_size[HASH_ALGO_SHA1];
	chip->allocated_banks[0].crypto_id = HASH_ALGO_SHA1;
	chip->nr_allocated_banks = 1;

	वापस 0;
पूर्ण
