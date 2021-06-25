<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005, 2006 IBM Corporation
 * Copyright (C) 2014, 2015 Intel Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG TPM Interface Spec version 1.2, revision 1.0.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/acpi.h>
#समावेश <linux/मुक्तzer.h>
#समावेश "tpm.h"
#समावेश "tpm_tis_core.h"

अटल व्योम tpm_tis_clkrun_enable(काष्ठा tpm_chip *chip, bool value);

अटल bool रुको_क्रम_tpm_stat_cond(काष्ठा tpm_chip *chip, u8 mask,
					bool check_cancel, bool *canceled)
अणु
	u8 status = chip->ops->status(chip);

	*canceled = false;
	अगर ((status & mask) == mask)
		वापस true;
	अगर (check_cancel && chip->ops->req_canceled(chip, status)) अणु
		*canceled = true;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_tpm_stat(काष्ठा tpm_chip *chip, u8 mask,
		अचिन्हित दीर्घ समयout, रुको_queue_head_t *queue,
		bool check_cancel)
अणु
	अचिन्हित दीर्घ stop;
	दीर्घ rc;
	u8 status;
	bool canceled = false;

	/* check current status */
	status = chip->ops->status(chip);
	अगर ((status & mask) == mask)
		वापस 0;

	stop = jअगरfies + समयout;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
again:
		समयout = stop - jअगरfies;
		अगर ((दीर्घ)समयout <= 0)
			वापस -ETIME;
		rc = रुको_event_पूर्णांकerruptible_समयout(*queue,
			रुको_क्रम_tpm_stat_cond(chip, mask, check_cancel,
					       &canceled),
			समयout);
		अगर (rc > 0) अणु
			अगर (canceled)
				वापस -ECANCELED;
			वापस 0;
		पूर्ण
		अगर (rc == -ERESTARTSYS && मुक्तzing(current)) अणु
			clear_thपढ़ो_flag(TIF_SIGPENDING);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		करो अणु
			usleep_range(TPM_TIMEOUT_USECS_MIN,
				     TPM_TIMEOUT_USECS_MAX);
			status = chip->ops->status(chip);
			अगर ((status & mask) == mask)
				वापस 0;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	पूर्ण
	वापस -ETIME;
पूर्ण

/* Beक्रमe we attempt to access the TPM we must see that the valid bit is set.
 * The specअगरication says that this bit is 0 at reset and reमुख्यs 0 until the
 * 'TPM has gone through its self test and initialization and has established
 * correct values in the other bits.'
 */
अटल पूर्णांक रुको_startup(काष्ठा tpm_chip *chip, पूर्णांक l)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop = jअगरfies + chip->समयout_a;

	करो अणु
		पूर्णांक rc;
		u8 access;

		rc = tpm_tis_पढ़ो8(priv, TPM_ACCESS(l), &access);
		अगर (rc < 0)
			वापस rc;

		अगर (access & TPM_ACCESS_VALID)
			वापस 0;
		tpm_msleep(TPM_TIMEOUT);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	वापस -1;
पूर्ण

अटल bool check_locality(काष्ठा tpm_chip *chip, पूर्णांक l)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc;
	u8 access;

	rc = tpm_tis_पढ़ो8(priv, TPM_ACCESS(l), &access);
	अगर (rc < 0)
		वापस false;

	अगर ((access & (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID
		       | TPM_ACCESS_REQUEST_USE)) ==
	    (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) अणु
		priv->locality = l;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक release_locality(काष्ठा tpm_chip *chip, पूर्णांक l)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	tpm_tis_ग_लिखो8(priv, TPM_ACCESS(l), TPM_ACCESS_ACTIVE_LOCALITY);

	वापस 0;
पूर्ण

अटल पूर्णांक request_locality(काष्ठा tpm_chip *chip, पूर्णांक l)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop, समयout;
	दीर्घ rc;

	अगर (check_locality(chip, l))
		वापस l;

	rc = tpm_tis_ग_लिखो8(priv, TPM_ACCESS(l), TPM_ACCESS_REQUEST_USE);
	अगर (rc < 0)
		वापस rc;

	stop = jअगरfies + chip->समयout_a;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
again:
		समयout = stop - jअगरfies;
		अगर ((दीर्घ)समयout <= 0)
			वापस -1;
		rc = रुको_event_पूर्णांकerruptible_समयout(priv->पूर्णांक_queue,
						      (check_locality
						       (chip, l)),
						      समयout);
		अगर (rc > 0)
			वापस l;
		अगर (rc == -ERESTARTSYS && मुक्तzing(current)) अणु
			clear_thपढ़ो_flag(TIF_SIGPENDING);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* रुको क्रम burstcount */
		करो अणु
			अगर (check_locality(chip, l))
				वापस l;
			tpm_msleep(TPM_TIMEOUT);
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	पूर्ण
	वापस -1;
पूर्ण

अटल u8 tpm_tis_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc;
	u8 status;

	rc = tpm_tis_पढ़ो8(priv, TPM_STS(priv->locality), &status);
	अगर (rc < 0)
		वापस 0;

	अगर (unlikely((status & TPM_STS_READ_ZERO) != 0)) अणु
		/*
		 * If this trips, the chances are the पढ़ो is
		 * वापसing 0xff because the locality hasn't been
		 * acquired.  Usually because tpm_try_get_ops() hasn't
		 * been called beक्रमe करोing a TPM operation.
		 */
		WARN_ONCE(1, "TPM returned invalid status\n");
		वापस 0;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम tpm_tis_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	/* this causes the current command to be पातed */
	tpm_tis_ग_लिखो8(priv, TPM_STS(priv->locality), TPM_STS_COMMAND_READY);
पूर्ण

अटल पूर्णांक get_burstcount(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop;
	पूर्णांक burstcnt, rc;
	u32 value;

	/* रुको क्रम burstcount */
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		stop = jअगरfies + chip->समयout_a;
	अन्यथा
		stop = jअगरfies + chip->समयout_d;
	करो अणु
		rc = tpm_tis_पढ़ो32(priv, TPM_STS(priv->locality), &value);
		अगर (rc < 0)
			वापस rc;

		burstcnt = (value >> 8) & 0xFFFF;
		अगर (burstcnt)
			वापस burstcnt;
		usleep_range(TPM_TIMEOUT_USECS_MIN, TPM_TIMEOUT_USECS_MAX);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक recv_data(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक size = 0, burstcnt, rc;

	जबतक (size < count) अणु
		rc = रुको_क्रम_tpm_stat(chip,
				 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
				 chip->समयout_c,
				 &priv->पढ़ो_queue, true);
		अगर (rc < 0)
			वापस rc;
		burstcnt = get_burstcount(chip);
		अगर (burstcnt < 0) अणु
			dev_err(&chip->dev, "Unable to read burstcount\n");
			वापस burstcnt;
		पूर्ण
		burstcnt = min_t(पूर्णांक, burstcnt, count - size);

		rc = tpm_tis_पढ़ो_bytes(priv, TPM_DATA_FIFO(priv->locality),
					burstcnt, buf + size);
		अगर (rc < 0)
			वापस rc;

		size += burstcnt;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक tpm_tis_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक size = 0;
	पूर्णांक status;
	u32 expected;

	अगर (count < TPM_HEADER_SIZE) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	/* पढ़ो first 10 bytes, including tag, paramsize, and result */
	अगर (size < TPM_HEADER_SIZE) अणु
		dev_err(&chip->dev, "Unable to read header\n");
		जाओ out;
	पूर्ण

	expected = be32_to_cpu(*(__be32 *) (buf + 2));
	अगर (expected > count || expected < TPM_HEADER_SIZE) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			  expected - TPM_HEADER_SIZE);
	अगर (size < expected) अणु
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
		जाओ out;
	पूर्ण

	अगर (रुको_क्रम_tpm_stat(chip, TPM_STS_VALID, chip->समयout_c,
				&priv->पूर्णांक_queue, false) < 0) अणु
		size = -ETIME;
		जाओ out;
	पूर्ण
	status = tpm_tis_status(chip);
	अगर (status & TPM_STS_DATA_AVAIL) अणु	/* retry? */
		dev_err(&chip->dev, "Error left over data\n");
		size = -EIO;
		जाओ out;
	पूर्ण

out:
	tpm_tis_पढ़ोy(chip);
	वापस size;
पूर्ण

/*
 * If पूर्णांकerrupts are used (संकेतed by an irq set in the venकरोr काष्ठाure)
 * tpm.c can skip polling क्रम the data to be available as the पूर्णांकerrupt is
 * रुकोed क्रम here
 */
अटल पूर्णांक tpm_tis_send_data(काष्ठा tpm_chip *chip, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc, status, burstcnt;
	माप_प्रकार count = 0;
	bool itpm = priv->flags & TPM_TIS_ITPM_WORKAROUND;

	status = tpm_tis_status(chip);
	अगर ((status & TPM_STS_COMMAND_READY) == 0) अणु
		tpm_tis_पढ़ोy(chip);
		अगर (रुको_क्रम_tpm_stat
		    (chip, TPM_STS_COMMAND_READY, chip->समयout_b,
		     &priv->पूर्णांक_queue, false) < 0) अणु
			rc = -ETIME;
			जाओ out_err;
		पूर्ण
	पूर्ण

	जबतक (count < len - 1) अणु
		burstcnt = get_burstcount(chip);
		अगर (burstcnt < 0) अणु
			dev_err(&chip->dev, "Unable to read burstcount\n");
			rc = burstcnt;
			जाओ out_err;
		पूर्ण
		burstcnt = min_t(पूर्णांक, burstcnt, len - count - 1);
		rc = tpm_tis_ग_लिखो_bytes(priv, TPM_DATA_FIFO(priv->locality),
					 burstcnt, buf + count);
		अगर (rc < 0)
			जाओ out_err;

		count += burstcnt;

		अगर (रुको_क्रम_tpm_stat(chip, TPM_STS_VALID, chip->समयout_c,
					&priv->पूर्णांक_queue, false) < 0) अणु
			rc = -ETIME;
			जाओ out_err;
		पूर्ण
		status = tpm_tis_status(chip);
		अगर (!itpm && (status & TPM_STS_DATA_EXPECT) == 0) अणु
			rc = -EIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* ग_लिखो last byte */
	rc = tpm_tis_ग_लिखो8(priv, TPM_DATA_FIFO(priv->locality), buf[count]);
	अगर (rc < 0)
		जाओ out_err;

	अगर (रुको_क्रम_tpm_stat(chip, TPM_STS_VALID, chip->समयout_c,
				&priv->पूर्णांक_queue, false) < 0) अणु
		rc = -ETIME;
		जाओ out_err;
	पूर्ण
	status = tpm_tis_status(chip);
	अगर (!itpm && (status & TPM_STS_DATA_EXPECT) != 0) अणु
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	tpm_tis_पढ़ोy(chip);
	वापस rc;
पूर्ण

अटल व्योम disable_पूर्णांकerrupts(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 पूर्णांकmask;
	पूर्णांक rc;

	अगर (priv->irq == 0)
		वापस;

	rc = tpm_tis_पढ़ो32(priv, TPM_INT_ENABLE(priv->locality), &पूर्णांकmask);
	अगर (rc < 0)
		पूर्णांकmask = 0;

	पूर्णांकmask &= ~TPM_GLOBAL_INT_ENABLE;
	rc = tpm_tis_ग_लिखो32(priv, TPM_INT_ENABLE(priv->locality), पूर्णांकmask);

	devm_मुक्त_irq(chip->dev.parent, priv->irq, chip);
	priv->irq = 0;
	chip->flags &= ~TPM_CHIP_FLAG_IRQ;
पूर्ण

/*
 * If पूर्णांकerrupts are used (संकेतed by an irq set in the venकरोr काष्ठाure)
 * tpm.c can skip polling क्रम the data to be available as the पूर्णांकerrupt is
 * रुकोed क्रम here
 */
अटल पूर्णांक tpm_tis_send_मुख्य(काष्ठा tpm_chip *chip, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc;
	u32 ordinal;
	अचिन्हित दीर्घ dur;

	rc = tpm_tis_send_data(chip, buf, len);
	अगर (rc < 0)
		वापस rc;

	/* go and करो it */
	rc = tpm_tis_ग_लिखो8(priv, TPM_STS(priv->locality), TPM_STS_GO);
	अगर (rc < 0)
		जाओ out_err;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
		ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));

		dur = tpm_calc_ordinal_duration(chip, ordinal);
		अगर (रुको_क्रम_tpm_stat
		    (chip, TPM_STS_DATA_AVAIL | TPM_STS_VALID, dur,
		     &priv->पढ़ो_queue, false) < 0) अणु
			rc = -ETIME;
			जाओ out_err;
		पूर्ण
	पूर्ण
	वापस 0;
out_err:
	tpm_tis_पढ़ोy(chip);
	वापस rc;
पूर्ण

अटल पूर्णांक tpm_tis_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक rc, irq;
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	अगर (!(chip->flags & TPM_CHIP_FLAG_IRQ) || priv->irq_tested)
		वापस tpm_tis_send_मुख्य(chip, buf, len);

	/* Verअगरy receipt of the expected IRQ */
	irq = priv->irq;
	priv->irq = 0;
	chip->flags &= ~TPM_CHIP_FLAG_IRQ;
	rc = tpm_tis_send_मुख्य(chip, buf, len);
	priv->irq = irq;
	chip->flags |= TPM_CHIP_FLAG_IRQ;
	अगर (!priv->irq_tested)
		tpm_msleep(1);
	अगर (!priv->irq_tested)
		disable_पूर्णांकerrupts(chip);
	priv->irq_tested = true;
	वापस rc;
पूर्ण

काष्ठा tis_venकरोr_durations_override अणु
	u32 did_vid;
	काष्ठा tpm1_version version;
	अचिन्हित दीर्घ durations[3];
पूर्ण;

अटल स्थिर काष्ठा  tis_venकरोr_durations_override venकरोr_dur_overrides[] = अणु
	/* STMicroelectronics 0x104a */
	अणु 0x0000104a,
	  अणु 1, 2, 8, 28 पूर्ण,
	  अणु (2 * 60 * HZ), (2 * 60 * HZ), (2 * 60 * HZ) पूर्ण पूर्ण,
पूर्ण;

अटल व्योम tpm_tis_update_durations(काष्ठा tpm_chip *chip,
				     अचिन्हित दीर्घ *duration_cap)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा tpm1_version *version;
	u32 did_vid;
	पूर्णांक i, rc;
	cap_t cap;

	chip->duration_adjusted = false;

	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, true);

	rc = tpm_tis_पढ़ो32(priv, TPM_DID_VID(0), &did_vid);
	अगर (rc < 0) अणु
		dev_warn(&chip->dev, "%s: failed to read did_vid. %d\n",
			 __func__, rc);
		जाओ out;
	पूर्ण

	/* Try to get a TPM version 1.2 or 1.1 TPM_CAP_VERSION_INFO */
	rc = tpm1_अ_लोap(chip, TPM_CAP_VERSION_1_2, &cap,
			 "attempting to determine the 1.2 version",
			 माप(cap.version2));
	अगर (!rc) अणु
		version = &cap.version2.version;
	पूर्ण अन्यथा अणु
		rc = tpm1_अ_लोap(chip, TPM_CAP_VERSION_1_1, &cap,
				 "attempting to determine the 1.1 version",
				 माप(cap.version1));

		अगर (rc)
			जाओ out;

		version = &cap.version1;
	पूर्ण

	क्रम (i = 0; i != ARRAY_SIZE(venकरोr_dur_overrides); i++) अणु
		अगर (venकरोr_dur_overrides[i].did_vid != did_vid)
			जारी;

		अगर ((version->major ==
		     venकरोr_dur_overrides[i].version.major) &&
		    (version->minor ==
		     venकरोr_dur_overrides[i].version.minor) &&
		    (version->rev_major ==
		     venकरोr_dur_overrides[i].version.rev_major) &&
		    (version->rev_minor ==
		     venकरोr_dur_overrides[i].version.rev_minor)) अणु

			स_नकल(duration_cap,
			       venकरोr_dur_overrides[i].durations,
			       माप(venकरोr_dur_overrides[i].durations));

			chip->duration_adjusted = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, false);
पूर्ण

काष्ठा tis_venकरोr_समयout_override अणु
	u32 did_vid;
	अचिन्हित दीर्घ समयout_us[4];
पूर्ण;

अटल स्थिर काष्ठा tis_venकरोr_समयout_override venकरोr_समयout_overrides[] = अणु
	/* Aपंचांगel 3204 */
	अणु 0x32041114, अणु (TIS_SHORT_TIMEOUT*1000), (TIS_LONG_TIMEOUT*1000),
			(TIS_SHORT_TIMEOUT*1000), (TIS_SHORT_TIMEOUT*1000) पूर्ण पूर्ण,
पूर्ण;

अटल व्योम tpm_tis_update_समयouts(काष्ठा tpm_chip *chip,
				    अचिन्हित दीर्घ *समयout_cap)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक i, rc;
	u32 did_vid;

	chip->समयout_adjusted = false;

	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, true);

	rc = tpm_tis_पढ़ो32(priv, TPM_DID_VID(0), &did_vid);
	अगर (rc < 0) अणु
		dev_warn(&chip->dev, "%s: failed to read did_vid: %d\n",
			 __func__, rc);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i != ARRAY_SIZE(venकरोr_समयout_overrides); i++) अणु
		अगर (venकरोr_समयout_overrides[i].did_vid != did_vid)
			जारी;
		स_नकल(समयout_cap, venकरोr_समयout_overrides[i].समयout_us,
		       माप(venकरोr_समयout_overrides[i].समयout_us));
		chip->समयout_adjusted = true;
	पूर्ण

out:
	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, false);

	वापस;
पूर्ण

/*
 * Early probing क्रम iTPM with STS_DATA_EXPECT flaw.
 * Try sending command without itpm flag set and अगर that
 * fails, repeat with itpm flag set.
 */
अटल पूर्णांक probe_itpm(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc = 0;
	अटल स्थिर u8 cmd_getticks[] = अणु
		0x00, 0xc1, 0x00, 0x00, 0x00, 0x0a,
		0x00, 0x00, 0x00, 0xf1
	पूर्ण;
	माप_प्रकार len = माप(cmd_getticks);
	u16 venकरोr;

	अगर (priv->flags & TPM_TIS_ITPM_WORKAROUND)
		वापस 0;

	rc = tpm_tis_पढ़ो16(priv, TPM_DID_VID(0), &venकरोr);
	अगर (rc < 0)
		वापस rc;

	/* probe only iTPMS */
	अगर (venकरोr != TPM_VID_INTEL)
		वापस 0;

	अगर (request_locality(chip, 0) != 0)
		वापस -EBUSY;

	rc = tpm_tis_send_data(chip, cmd_getticks, len);
	अगर (rc == 0)
		जाओ out;

	tpm_tis_पढ़ोy(chip);

	priv->flags |= TPM_TIS_ITPM_WORKAROUND;

	rc = tpm_tis_send_data(chip, cmd_getticks, len);
	अगर (rc == 0)
		dev_info(&chip->dev, "Detected an iTPM.\n");
	अन्यथा अणु
		priv->flags &= ~TPM_TIS_ITPM_WORKAROUND;
		rc = -EFAULT;
	पूर्ण

out:
	tpm_tis_पढ़ोy(chip);
	release_locality(chip, priv->locality);

	वापस rc;
पूर्ण

अटल bool tpm_tis_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	चयन (priv->manufacturer_id) अणु
	हाल TPM_VID_WINBOND:
		वापस ((status == TPM_STS_VALID) ||
			(status == (TPM_STS_VALID | TPM_STS_COMMAND_READY)));
	हाल TPM_VID_STM:
		वापस (status == (TPM_STS_VALID | TPM_STS_COMMAND_READY));
	शेष:
		वापस (status == TPM_STS_COMMAND_READY);
	पूर्ण
पूर्ण

अटल irqवापस_t tis_पूर्णांक_handler(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा tpm_chip *chip = dev_id;
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 पूर्णांकerrupt;
	पूर्णांक i, rc;

	rc = tpm_tis_पढ़ो32(priv, TPM_INT_STATUS(priv->locality), &पूर्णांकerrupt);
	अगर (rc < 0)
		वापस IRQ_NONE;

	अगर (पूर्णांकerrupt == 0)
		वापस IRQ_NONE;

	priv->irq_tested = true;
	अगर (पूर्णांकerrupt & TPM_INTF_DATA_AVAIL_INT)
		wake_up_पूर्णांकerruptible(&priv->पढ़ो_queue);
	अगर (पूर्णांकerrupt & TPM_INTF_LOCALITY_CHANGE_INT)
		क्रम (i = 0; i < 5; i++)
			अगर (check_locality(chip, i))
				अवरोध;
	अगर (पूर्णांकerrupt &
	    (TPM_INTF_LOCALITY_CHANGE_INT | TPM_INTF_STS_VALID_INT |
	     TPM_INTF_CMD_READY_INT))
		wake_up_पूर्णांकerruptible(&priv->पूर्णांक_queue);

	/* Clear पूर्णांकerrupts handled with TPM_EOI */
	rc = tpm_tis_ग_लिखो32(priv, TPM_INT_STATUS(priv->locality), पूर्णांकerrupt);
	अगर (rc < 0)
		वापस IRQ_NONE;

	tpm_tis_पढ़ो32(priv, TPM_INT_STATUS(priv->locality), &पूर्णांकerrupt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tpm_tis_gen_पूर्णांकerrupt(काष्ठा tpm_chip *chip)
अणु
	स्थिर अक्षर *desc = "attempting to generate an interrupt";
	u32 cap2;
	cap_t cap;
	पूर्णांक ret;

	ret = request_locality(chip, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		ret = tpm2_get_tpm_pt(chip, 0x100, &cap2, desc);
	अन्यथा
		ret = tpm1_अ_लोap(chip, TPM_CAP_PROP_TIS_TIMEOUT, &cap, desc, 0);

	release_locality(chip, 0);

	वापस ret;
पूर्ण

/* Register the IRQ and issue a command that will cause an पूर्णांकerrupt. If an
 * irq is seen then leave the chip setup क्रम IRQ operation, otherwise reverse
 * everything and leave in polling mode. Returns 0 on success.
 */
अटल पूर्णांक tpm_tis_probe_irq_single(काष्ठा tpm_chip *chip, u32 पूर्णांकmask,
				    पूर्णांक flags, पूर्णांक irq)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u8 original_पूर्णांक_vec;
	पूर्णांक rc;
	u32 पूर्णांक_status;

	अगर (devm_request_irq(chip->dev.parent, irq, tis_पूर्णांक_handler, flags,
			     dev_name(&chip->dev), chip) != 0) अणु
		dev_info(&chip->dev, "Unable to request irq: %d for probe\n",
			 irq);
		वापस -1;
	पूर्ण
	priv->irq = irq;

	rc = tpm_tis_पढ़ो8(priv, TPM_INT_VECTOR(priv->locality),
			   &original_पूर्णांक_vec);
	अगर (rc < 0)
		वापस rc;

	rc = tpm_tis_ग_लिखो8(priv, TPM_INT_VECTOR(priv->locality), irq);
	अगर (rc < 0)
		वापस rc;

	rc = tpm_tis_पढ़ो32(priv, TPM_INT_STATUS(priv->locality), &पूर्णांक_status);
	अगर (rc < 0)
		वापस rc;

	/* Clear all existing */
	rc = tpm_tis_ग_लिखो32(priv, TPM_INT_STATUS(priv->locality), पूर्णांक_status);
	अगर (rc < 0)
		वापस rc;

	/* Turn on */
	rc = tpm_tis_ग_लिखो32(priv, TPM_INT_ENABLE(priv->locality),
			     पूर्णांकmask | TPM_GLOBAL_INT_ENABLE);
	अगर (rc < 0)
		वापस rc;

	priv->irq_tested = false;

	/* Generate an पूर्णांकerrupt by having the core call through to
	 * tpm_tis_send
	 */
	rc = tpm_tis_gen_पूर्णांकerrupt(chip);
	अगर (rc < 0)
		वापस rc;

	/* tpm_tis_send will either confirm the पूर्णांकerrupt is working or it
	 * will call disable_irq which unकरोes all of the above.
	 */
	अगर (!(chip->flags & TPM_CHIP_FLAG_IRQ)) अणु
		rc = tpm_tis_ग_लिखो8(priv, original_पूर्णांक_vec,
				TPM_INT_VECTOR(priv->locality));
		अगर (rc < 0)
			वापस rc;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Try to find the IRQ the TPM is using. This is क्रम legacy x86 प्रणालीs that
 * करो not have ACPI/etc. We typically expect the पूर्णांकerrupt to be declared अगर
 * present.
 */
अटल व्योम tpm_tis_probe_irq(काष्ठा tpm_chip *chip, u32 पूर्णांकmask)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u8 original_पूर्णांक_vec;
	पूर्णांक i, rc;

	rc = tpm_tis_पढ़ो8(priv, TPM_INT_VECTOR(priv->locality),
			   &original_पूर्णांक_vec);
	अगर (rc < 0)
		वापस;

	अगर (!original_पूर्णांक_vec) अणु
		अगर (IS_ENABLED(CONFIG_X86))
			क्रम (i = 3; i <= 15; i++)
				अगर (!tpm_tis_probe_irq_single(chip, पूर्णांकmask, 0,
							      i))
					वापस;
	पूर्ण अन्यथा अगर (!tpm_tis_probe_irq_single(chip, पूर्णांकmask, 0,
					     original_पूर्णांक_vec))
		वापस;
पूर्ण

व्योम tpm_tis_हटाओ(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 reg = TPM_INT_ENABLE(priv->locality);
	u32 पूर्णांकerrupt;
	पूर्णांक rc;

	tpm_tis_clkrun_enable(chip, true);

	rc = tpm_tis_पढ़ो32(priv, reg, &पूर्णांकerrupt);
	अगर (rc < 0)
		पूर्णांकerrupt = 0;

	tpm_tis_ग_लिखो32(priv, reg, ~TPM_GLOBAL_INT_ENABLE & पूर्णांकerrupt);

	tpm_tis_clkrun_enable(chip, false);

	अगर (priv->ilb_base_addr)
		iounmap(priv->ilb_base_addr);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_tis_हटाओ);

/**
 * tpm_tis_clkrun_enable() - Keep clkrun protocol disabled क्रम entire duration
 *                           of a single TPM command
 * @chip:	TPM chip to use
 * @value:	1 - Disable CLKRUN protocol, so that घड़ीs are मुक्त running
 *		0 - Enable CLKRUN protocol
 * Call this function directly in tpm_tis_हटाओ() in error or driver removal
 * path, since the chip->ops is set to शून्य in tpm_chip_unरेजिस्टर().
 */
अटल व्योम tpm_tis_clkrun_enable(काष्ठा tpm_chip *chip, bool value)
अणु
	काष्ठा tpm_tis_data *data = dev_get_drvdata(&chip->dev);
	u32 clkrun_val;

	अगर (!IS_ENABLED(CONFIG_X86) || !is_bsw() ||
	    !data->ilb_base_addr)
		वापस;

	अगर (value) अणु
		data->clkrun_enabled++;
		अगर (data->clkrun_enabled > 1)
			वापस;
		clkrun_val = ioपढ़ो32(data->ilb_base_addr + LPC_CNTRL_OFFSET);

		/* Disable LPC CLKRUN# */
		clkrun_val &= ~LPC_CLKRUN_EN;
		ioग_लिखो32(clkrun_val, data->ilb_base_addr + LPC_CNTRL_OFFSET);

		/*
		 * Write any अक्रमom value on port 0x80 which is on LPC, to make
		 * sure LPC घड़ी is running beक्रमe sending any TPM command.
		 */
		outb(0xCC, 0x80);
	पूर्ण अन्यथा अणु
		data->clkrun_enabled--;
		अगर (data->clkrun_enabled)
			वापस;

		clkrun_val = ioपढ़ो32(data->ilb_base_addr + LPC_CNTRL_OFFSET);

		/* Enable LPC CLKRUN# */
		clkrun_val |= LPC_CLKRUN_EN;
		ioग_लिखो32(clkrun_val, data->ilb_base_addr + LPC_CNTRL_OFFSET);

		/*
		 * Write any अक्रमom value on port 0x80 which is on LPC, to make
		 * sure LPC घड़ी is running beक्रमe sending any TPM command.
		 */
		outb(0xCC, 0x80);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_tis = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = tpm_tis_status,
	.recv = tpm_tis_recv,
	.send = tpm_tis_send,
	.cancel = tpm_tis_पढ़ोy,
	.update_समयouts = tpm_tis_update_समयouts,
	.update_durations = tpm_tis_update_durations,
	.req_complete_mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_complete_val = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_canceled = tpm_tis_req_canceled,
	.request_locality = request_locality,
	.relinquish_locality = release_locality,
	.clk_enable = tpm_tis_clkrun_enable,
पूर्ण;

पूर्णांक tpm_tis_core_init(काष्ठा device *dev, काष्ठा tpm_tis_data *priv, पूर्णांक irq,
		      स्थिर काष्ठा tpm_tis_phy_ops *phy_ops,
		      acpi_handle acpi_dev_handle)
अणु
	u32 venकरोr;
	u32 पूर्णांकfcaps;
	u32 पूर्णांकmask;
	u32 clkrun_val;
	u8 rid;
	पूर्णांक rc, probe;
	काष्ठा tpm_chip *chip;

	chip = tpmm_chip_alloc(dev, &tpm_tis);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

#अगर_घोषित CONFIG_ACPI
	chip->acpi_dev_handle = acpi_dev_handle;
#पूर्ण_अगर

	chip->hwrng.quality = priv->rng_quality;

	/* Maximum समयouts */
	chip->समयout_a = msecs_to_jअगरfies(TIS_TIMEOUT_A_MAX);
	chip->समयout_b = msecs_to_jअगरfies(TIS_TIMEOUT_B_MAX);
	chip->समयout_c = msecs_to_jअगरfies(TIS_TIMEOUT_C_MAX);
	chip->समयout_d = msecs_to_jअगरfies(TIS_TIMEOUT_D_MAX);
	priv->phy_ops = phy_ops;
	dev_set_drvdata(&chip->dev, priv);

	अगर (is_bsw()) अणु
		priv->ilb_base_addr = ioremap(INTEL_LEGACY_BLK_BASE_ADDR,
					ILB_REMAP_SIZE);
		अगर (!priv->ilb_base_addr)
			वापस -ENOMEM;

		clkrun_val = ioपढ़ो32(priv->ilb_base_addr + LPC_CNTRL_OFFSET);
		/* Check अगर CLKRUN# is alपढ़ोy not enabled in the LPC bus */
		अगर (!(clkrun_val & LPC_CLKRUN_EN)) अणु
			iounmap(priv->ilb_base_addr);
			priv->ilb_base_addr = शून्य;
		पूर्ण
	पूर्ण

	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, true);

	अगर (रुको_startup(chip, 0) != 0) अणु
		rc = -ENODEV;
		जाओ out_err;
	पूर्ण

	/* Take control of the TPM's पूर्णांकerrupt hardware and shut it off */
	rc = tpm_tis_पढ़ो32(priv, TPM_INT_ENABLE(priv->locality), &पूर्णांकmask);
	अगर (rc < 0)
		जाओ out_err;

	पूर्णांकmask |= TPM_INTF_CMD_READY_INT | TPM_INTF_LOCALITY_CHANGE_INT |
		   TPM_INTF_DATA_AVAIL_INT | TPM_INTF_STS_VALID_INT;
	पूर्णांकmask &= ~TPM_GLOBAL_INT_ENABLE;
	tpm_tis_ग_लिखो32(priv, TPM_INT_ENABLE(priv->locality), पूर्णांकmask);

	rc = tpm_chip_start(chip);
	अगर (rc)
		जाओ out_err;
	rc = tpm2_probe(chip);
	tpm_chip_stop(chip);
	अगर (rc)
		जाओ out_err;

	rc = tpm_tis_पढ़ो32(priv, TPM_DID_VID(0), &venकरोr);
	अगर (rc < 0)
		जाओ out_err;

	priv->manufacturer_id = venकरोr;

	rc = tpm_tis_पढ़ो8(priv, TPM_RID(0), &rid);
	अगर (rc < 0)
		जाओ out_err;

	dev_info(dev, "%s TPM (device-id 0x%X, rev-id %d)\n",
		 (chip->flags & TPM_CHIP_FLAG_TPM2) ? "2.0" : "1.2",
		 venकरोr >> 16, rid);

	probe = probe_itpm(chip);
	अगर (probe < 0) अणु
		rc = -ENODEV;
		जाओ out_err;
	पूर्ण

	/* Figure out the capabilities */
	rc = tpm_tis_पढ़ो32(priv, TPM_INTF_CAPS(priv->locality), &पूर्णांकfcaps);
	अगर (rc < 0)
		जाओ out_err;

	dev_dbg(dev, "TPM interface capabilities (0x%x):\n",
		पूर्णांकfcaps);
	अगर (पूर्णांकfcaps & TPM_INTF_BURST_COUNT_STATIC)
		dev_dbg(dev, "\tBurst Count Static\n");
	अगर (पूर्णांकfcaps & TPM_INTF_CMD_READY_INT)
		dev_dbg(dev, "\tCommand Ready Int Support\n");
	अगर (पूर्णांकfcaps & TPM_INTF_INT_EDGE_FALLING)
		dev_dbg(dev, "\tInterrupt Edge Falling\n");
	अगर (पूर्णांकfcaps & TPM_INTF_INT_EDGE_RISING)
		dev_dbg(dev, "\tInterrupt Edge Rising\n");
	अगर (पूर्णांकfcaps & TPM_INTF_INT_LEVEL_LOW)
		dev_dbg(dev, "\tInterrupt Level Low\n");
	अगर (पूर्णांकfcaps & TPM_INTF_INT_LEVEL_HIGH)
		dev_dbg(dev, "\tInterrupt Level High\n");
	अगर (पूर्णांकfcaps & TPM_INTF_LOCALITY_CHANGE_INT)
		dev_dbg(dev, "\tLocality Change Int Support\n");
	अगर (पूर्णांकfcaps & TPM_INTF_STS_VALID_INT)
		dev_dbg(dev, "\tSts Valid Int Support\n");
	अगर (पूर्णांकfcaps & TPM_INTF_DATA_AVAIL_INT)
		dev_dbg(dev, "\tData Avail Int Support\n");

	/* INTERRUPT Setup */
	init_रुकोqueue_head(&priv->पढ़ो_queue);
	init_रुकोqueue_head(&priv->पूर्णांक_queue);
	अगर (irq != -1) अणु
		/*
		 * Beक्रमe करोing irq testing issue a command to the TPM in polling mode
		 * to make sure it works. May as well use that command to set the
		 * proper समयouts क्रम the driver.
		 */

		rc = request_locality(chip, 0);
		अगर (rc < 0)
			जाओ out_err;

		rc = tpm_get_समयouts(chip);

		release_locality(chip, 0);

		अगर (rc) अणु
			dev_err(dev, "Could not get TPM timeouts and durations\n");
			rc = -ENODEV;
			जाओ out_err;
		पूर्ण

		अगर (irq) अणु
			tpm_tis_probe_irq_single(chip, पूर्णांकmask, IRQF_SHARED,
						 irq);
			अगर (!(chip->flags & TPM_CHIP_FLAG_IRQ)) अणु
				dev_err(&chip->dev, FW_BUG
					"TPM interrupt not working, polling instead\n");

				disable_पूर्णांकerrupts(chip);
			पूर्ण
		पूर्ण अन्यथा अणु
			tpm_tis_probe_irq(chip, पूर्णांकmask);
		पूर्ण
	पूर्ण

	rc = tpm_chip_रेजिस्टर(chip);
	अगर (rc)
		जाओ out_err;

	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, false);

	वापस 0;
out_err:
	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, false);

	tpm_tis_हटाओ(chip);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_tis_core_init);

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम tpm_tis_reenable_पूर्णांकerrupts(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 पूर्णांकmask;
	पूर्णांक rc;

	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, true);

	/* reenable पूर्णांकerrupts that device may have lost or
	 * BIOS/firmware may have disabled
	 */
	rc = tpm_tis_ग_लिखो8(priv, TPM_INT_VECTOR(priv->locality), priv->irq);
	अगर (rc < 0)
		जाओ out;

	rc = tpm_tis_पढ़ो32(priv, TPM_INT_ENABLE(priv->locality), &पूर्णांकmask);
	अगर (rc < 0)
		जाओ out;

	पूर्णांकmask |= TPM_INTF_CMD_READY_INT
	    | TPM_INTF_LOCALITY_CHANGE_INT | TPM_INTF_DATA_AVAIL_INT
	    | TPM_INTF_STS_VALID_INT | TPM_GLOBAL_INT_ENABLE;

	tpm_tis_ग_लिखो32(priv, TPM_INT_ENABLE(priv->locality), पूर्णांकmask);

out:
	अगर (chip->ops->clk_enable != शून्य)
		chip->ops->clk_enable(chip, false);

	वापस;
पूर्ण

पूर्णांक tpm_tis_resume(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ)
		tpm_tis_reenable_पूर्णांकerrupts(chip);

	ret = tpm_pm_resume(dev);
	अगर (ret)
		वापस ret;

	/*
	 * TPM 1.2 requires self-test on resume. This function actually वापसs
	 * an error code but क्रम unknown reason it isn't handled.
	 */
	अगर (!(chip->flags & TPM_CHIP_FLAG_TPM2)) अणु
		ret = request_locality(chip, 0);
		अगर (ret < 0)
			वापस ret;

		tpm1_करो_selftest(chip);

		release_locality(chip, 0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_tis_resume);
#पूर्ण_अगर

MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
