<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * Note, the TPM chip is not पूर्णांकerrupt driven (only polling)
 * and can have very दीर्घ समयouts (minutes!). Hence the unusual
 * calls to msleep.
 */

#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/suspend.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "tpm.h"

/*
 * Bug workaround - some TPM's don't flush the most
 * recently changed pcr on suspend, so क्रमce the flush
 * with an extend to the selected _unused_ non-अस्थिर pcr.
 */
अटल u32 tpm_suspend_pcr;
module_param_named(suspend_pcr, tpm_suspend_pcr, uपूर्णांक, 0644);
MODULE_PARM_DESC(suspend_pcr,
		 "PCR to use for dummy writes to facilitate flush on suspend.");

/**
 * tpm_calc_ordinal_duration() - calculate the maximum command duration
 * @chip:    TPM chip to use.
 * @ordinal: TPM command ordinal.
 *
 * The function वापसs the maximum amount of समय the chip could take
 * to वापस the result क्रम a particular ordinal in jअगरfies.
 *
 * Return: A maximal duration समय क्रम an ordinal in jअगरfies.
 */
अचिन्हित दीर्घ tpm_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal)
अणु
	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		वापस tpm2_calc_ordinal_duration(chip, ordinal);
	अन्यथा
		वापस tpm1_calc_ordinal_duration(chip, ordinal);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_calc_ordinal_duration);

अटल sमाप_प्रकार tpm_try_transmit(काष्ठा tpm_chip *chip, व्योम *buf, माप_प्रकार bufsiz)
अणु
	काष्ठा tpm_header *header = buf;
	पूर्णांक rc;
	sमाप_प्रकार len = 0;
	u32 count, ordinal;
	अचिन्हित दीर्घ stop;

	अगर (bufsiz < TPM_HEADER_SIZE)
		वापस -EINVAL;

	अगर (bufsiz > TPM_बफ_मानE)
		bufsiz = TPM_बफ_मानE;

	count = be32_to_cpu(header->length);
	ordinal = be32_to_cpu(header->ordinal);
	अगर (count == 0)
		वापस -ENODATA;
	अगर (count > bufsiz) अणु
		dev_err(&chip->dev,
			"invalid count value %x %zx\n", count, bufsiz);
		वापस -E2BIG;
	पूर्ण

	rc = chip->ops->send(chip, buf, count);
	अगर (rc < 0) अणु
		अगर (rc != -EPIPE)
			dev_err(&chip->dev,
				"%s: send(): error %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	/* A sanity check. send() should just वापस zero on success e.g.
	 * not the command length.
	 */
	अगर (rc > 0) अणु
		dev_warn(&chip->dev,
			 "%s: send(): invalid value %d\n", __func__, rc);
		rc = 0;
	पूर्ण

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ)
		जाओ out_recv;

	stop = jअगरfies + tpm_calc_ordinal_duration(chip, ordinal);
	करो अणु
		u8 status = chip->ops->status(chip);
		अगर ((status & chip->ops->req_complete_mask) ==
		    chip->ops->req_complete_val)
			जाओ out_recv;

		अगर (chip->ops->req_canceled(chip, status)) अणु
			dev_err(&chip->dev, "Operation Canceled\n");
			वापस -ECANCELED;
		पूर्ण

		tpm_msleep(TPM_TIMEOUT_POLL);
		rmb();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	chip->ops->cancel(chip);
	dev_err(&chip->dev, "Operation Timed out\n");
	वापस -ETIME;

out_recv:
	len = chip->ops->recv(chip, buf, bufsiz);
	अगर (len < 0) अणु
		rc = len;
		dev_err(&chip->dev, "tpm_transmit: tpm_recv: error %d\n", rc);
	पूर्ण अन्यथा अगर (len < TPM_HEADER_SIZE || len != be32_to_cpu(header->length))
		rc = -EFAULT;

	वापस rc ? rc : len;
पूर्ण

/**
 * tpm_transmit - Internal kernel पूर्णांकerface to transmit TPM commands.
 * @chip:	a TPM chip to use
 * @buf:	a TPM command buffer
 * @bufsiz:	length of the TPM command buffer
 *
 * A wrapper around tpm_try_transmit() that handles TPM2_RC_RETRY वापसs from
 * the TPM and retransmits the command after a delay up to a maximum रुको of
 * TPM2_DURATION_LONG.
 *
 * Note that TPM 1.x never वापसs TPM2_RC_RETRY so the retry logic is TPM 2.0
 * only.
 *
 * Return:
 * * The response length	- OK
 * * -त्रुटि_सं			- A प्रणाली error
 */
sमाप_प्रकार tpm_transmit(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार bufsiz)
अणु
	काष्ठा tpm_header *header = (काष्ठा tpm_header *)buf;
	/* space क्रम header and handles */
	u8 save[TPM_HEADER_SIZE + 3*माप(u32)];
	अचिन्हित पूर्णांक delay_msec = TPM2_DURATION_SHORT;
	u32 rc = 0;
	sमाप_प्रकार ret;
	स्थिर माप_प्रकार save_size = min(माप(save), bufsiz);
	/* the command code is where the वापस code will be */
	u32 cc = be32_to_cpu(header->वापस_code);

	/*
	 * Subtlety here: अगर we have a space, the handles will be
	 * transक्रमmed, so when we restore the header we also have to
	 * restore the handles.
	 */
	स_नकल(save, buf, save_size);

	क्रम (;;) अणु
		ret = tpm_try_transmit(chip, buf, bufsiz);
		अगर (ret < 0)
			अवरोध;
		rc = be32_to_cpu(header->वापस_code);
		अगर (rc != TPM2_RC_RETRY && rc != TPM2_RC_TESTING)
			अवरोध;
		/*
		 * वापस immediately अगर self test वापसs test
		 * still running to लघुen boot समय.
		 */
		अगर (rc == TPM2_RC_TESTING && cc == TPM2_CC_SELF_TEST)
			अवरोध;

		अगर (delay_msec > TPM2_DURATION_LONG) अणु
			अगर (rc == TPM2_RC_RETRY)
				dev_err(&chip->dev, "in retry loop\n");
			अन्यथा
				dev_err(&chip->dev,
					"self test is still running\n");
			अवरोध;
		पूर्ण
		tpm_msleep(delay_msec);
		delay_msec *= 2;
		स_नकल(buf, save, save_size);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * tpm_transmit_cmd - send a tpm command to the device
 * @chip:			a TPM chip to use
 * @buf:			a TPM command buffer
 * @min_rsp_body_length:	minimum expected length of response body
 * @desc:			command description used in the error message
 *
 * Return:
 * * 0		- OK
 * * -त्रुटि_सं	- A प्रणाली error
 * * TPM_RC	- A TPM error
 */
sमाप_प्रकार tpm_transmit_cmd(काष्ठा tpm_chip *chip, काष्ठा tpm_buf *buf,
			 माप_प्रकार min_rsp_body_length, स्थिर अक्षर *desc)
अणु
	स्थिर काष्ठा tpm_header *header = (काष्ठा tpm_header *)buf->data;
	पूर्णांक err;
	sमाप_प्रकार len;

	len = tpm_transmit(chip, buf->data, PAGE_SIZE);
	अगर (len <  0)
		वापस len;

	err = be32_to_cpu(header->वापस_code);
	अगर (err != 0 && err != TPM_ERR_DISABLED && err != TPM_ERR_DEACTIVATED
	    && err != TPM2_RC_TESTING && desc)
		dev_err(&chip->dev, "A TPM error (%d) occurred %s\n", err,
			desc);
	अगर (err)
		वापस err;

	अगर (len < min_rsp_body_length + TPM_HEADER_SIZE)
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_transmit_cmd);

पूर्णांक tpm_get_समयouts(काष्ठा tpm_chip *chip)
अणु
	अगर (chip->flags & TPM_CHIP_FLAG_HAVE_TIMEOUTS)
		वापस 0;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		वापस tpm2_get_समयouts(chip);
	अन्यथा
		वापस tpm1_get_समयouts(chip);
पूर्ण
EXPORT_SYMBOL_GPL(tpm_get_समयouts);

/**
 * tpm_is_tpm2 - करो we a have a TPM2 chip?
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 *
 * Return:
 * 1 अगर we have a TPM2 chip.
 * 0 अगर we करोn't have a TPM2 chip.
 * A negative number क्रम प्रणाली errors (त्रुटि_सं).
 */
पूर्णांक tpm_is_tpm2(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	chip = tpm_find_get_ops(chip);
	अगर (!chip)
		वापस -ENODEV;

	rc = (chip->flags & TPM_CHIP_FLAG_TPM2) != 0;

	tpm_put_ops(chip);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_is_tpm2);

/**
 * tpm_pcr_पढ़ो - पढ़ो a PCR value from SHA1 bank
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 * @pcr_idx:	the PCR to be retrieved
 * @digest:	the PCR bank and buffer current PCR value is written to
 *
 * Return: same as with tpm_transmit_cmd()
 */
पूर्णांक tpm_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx,
		 काष्ठा tpm_digest *digest)
अणु
	पूर्णांक rc;

	chip = tpm_find_get_ops(chip);
	अगर (!chip)
		वापस -ENODEV;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_pcr_पढ़ो(chip, pcr_idx, digest, शून्य);
	अन्यथा
		rc = tpm1_pcr_पढ़ो(chip, pcr_idx, digest->digest);

	tpm_put_ops(chip);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_pcr_पढ़ो);

/**
 * tpm_pcr_extend - extend a PCR value in SHA1 bank.
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 * @pcr_idx:	the PCR to be retrieved
 * @digests:	array of tpm_digest काष्ठाures used to extend PCRs
 *
 * Note: callers must pass a digest क्रम every allocated PCR bank, in the same
 * order of the banks in chip->allocated_banks.
 *
 * Return: same as with tpm_transmit_cmd()
 */
पूर्णांक tpm_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx,
		   काष्ठा tpm_digest *digests)
अणु
	पूर्णांक rc;
	पूर्णांक i;

	chip = tpm_find_get_ops(chip);
	अगर (!chip)
		वापस -ENODEV;

	क्रम (i = 0; i < chip->nr_allocated_banks; i++) अणु
		अगर (digests[i].alg_id != chip->allocated_banks[i].alg_id) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		rc = tpm2_pcr_extend(chip, pcr_idx, digests);
		जाओ out;
	पूर्ण

	rc = tpm1_pcr_extend(chip, pcr_idx, digests[0].digest,
			     "attempting extend a PCR value");

out:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_pcr_extend);

/**
 * tpm_send - send a TPM command
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 * @cmd:	a TPM command buffer
 * @buflen:	the length of the TPM command buffer
 *
 * Return: same as with tpm_transmit_cmd()
 */
पूर्णांक tpm_send(काष्ठा tpm_chip *chip, व्योम *cmd, माप_प्रकार buflen)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;

	chip = tpm_find_get_ops(chip);
	अगर (!chip)
		वापस -ENODEV;

	buf.data = cmd;
	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to a send a command");

	tpm_put_ops(chip);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_send);

पूर्णांक tpm_स्वतः_startup(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	अगर (!(chip->ops->flags & TPM_OPS_AUTO_STARTUP))
		वापस 0;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_स्वतः_startup(chip);
	अन्यथा
		rc = tpm1_स्वतः_startup(chip);

	वापस rc;
पूर्ण

/*
 * We are about to suspend. Save the TPM state
 * so that it can be restored.
 */
पूर्णांक tpm_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	पूर्णांक rc = 0;

	अगर (!chip)
		वापस -ENODEV;

	अगर (chip->flags & TPM_CHIP_FLAG_ALWAYS_POWERED)
		जाओ suspended;

	अगर ((chip->flags & TPM_CHIP_FLAG_FIRMWARE_POWER_MANAGED) &&
	    !pm_suspend_via_firmware())
		जाओ suspended;

	अगर (!tpm_chip_start(chip)) अणु
		अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
			tpm2_shutकरोwn(chip, TPM2_SU_STATE);
		अन्यथा
			rc = tpm1_pm_suspend(chip, tpm_suspend_pcr);

		tpm_chip_stop(chip);
	पूर्ण

suspended:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_pm_suspend);

/*
 * Resume from a घातer safe. The BIOS alपढ़ोy restored
 * the TPM state.
 */
पूर्णांक tpm_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);

	अगर (chip == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_pm_resume);

/**
 * tpm_get_अक्रमom() - get अक्रमom bytes from the TPM's RNG
 * @chip:	a &काष्ठा tpm_chip instance, %शून्य क्रम the शेष chip
 * @out:	destination buffer क्रम the अक्रमom bytes
 * @max:	the max number of bytes to ग_लिखो to @out
 *
 * Return: number of अक्रमom bytes पढ़ो or a negative error value.
 */
पूर्णांक tpm_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *out, माप_प्रकार max)
अणु
	पूर्णांक rc;

	अगर (!out || max > TPM_MAX_RNG_DATA)
		वापस -EINVAL;

	chip = tpm_find_get_ops(chip);
	अगर (!chip)
		वापस -ENODEV;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_get_अक्रमom(chip, out, max);
	अन्यथा
		rc = tpm1_get_अक्रमom(chip, out, max);

	tpm_put_ops(chip);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tpm_get_अक्रमom);

अटल पूर्णांक __init tpm_init(व्योम)
अणु
	पूर्णांक rc;

	tpm_class = class_create(THIS_MODULE, "tpm");
	अगर (IS_ERR(tpm_class)) अणु
		pr_err("couldn't create tpm class\n");
		वापस PTR_ERR(tpm_class);
	पूर्ण

	tpmrm_class = class_create(THIS_MODULE, "tpmrm");
	अगर (IS_ERR(tpmrm_class)) अणु
		pr_err("couldn't create tpmrm class\n");
		rc = PTR_ERR(tpmrm_class);
		जाओ out_destroy_tpm_class;
	पूर्ण

	rc = alloc_chrdev_region(&tpm_devt, 0, 2*TPM_NUM_DEVICES, "tpm");
	अगर (rc < 0) अणु
		pr_err("tpm: failed to allocate char dev region\n");
		जाओ out_destroy_tpmrm_class;
	पूर्ण

	rc = tpm_dev_common_init();
	अगर (rc) अणु
		pr_err("tpm: failed to allocate char dev region\n");
		जाओ out_unreg_chrdev;
	पूर्ण

	वापस 0;

out_unreg_chrdev:
	unरेजिस्टर_chrdev_region(tpm_devt, 2 * TPM_NUM_DEVICES);
out_destroy_tpmrm_class:
	class_destroy(tpmrm_class);
out_destroy_tpm_class:
	class_destroy(tpm_class);

	वापस rc;
पूर्ण

अटल व्योम __निकास tpm_निकास(व्योम)
अणु
	idr_destroy(&dev_nums_idr);
	class_destroy(tpm_class);
	class_destroy(tpmrm_class);
	unरेजिस्टर_chrdev_region(tpm_devt, 2*TPM_NUM_DEVICES);
	tpm_dev_common_निकास();
पूर्ण

subsys_initcall(tpm_init);
module_निकास(tpm_निकास);

MODULE_AUTHOR("Leendert van Doorn (leendert@watson.ibm.com)");
MODULE_DESCRIPTION("TPM Driver");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
