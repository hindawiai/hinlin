<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2020 IBM Corporation
 *
 * Author: Ashley Lai <ashleydlai@gmail.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/prom.h>

#समावेश "tpm.h"
#समावेश "tpm_ibmvtpm.h"

अटल स्थिर अक्षर tpm_ibmvtpm_driver_name[] = "tpm_ibmvtpm";

अटल स्थिर काष्ठा vio_device_id tpm_ibmvtpm_device_table[] = अणु
	अणु "IBM,vtpm", "IBM,vtpm"पूर्ण,
	अणु "IBM,vtpm", "IBM,vtpm20"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, tpm_ibmvtpm_device_table);

/**
 * ibmvtpm_send_crq_word() - Send a CRQ request
 * @vdev:	vio device काष्ठा
 * @w1:		pre-स्थिरructed first word of tpm crq (second word is reserved)
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvtpm_send_crq_word(काष्ठा vio_dev *vdev, u64 w1)
अणु
	वापस plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, w1, 0);
पूर्ण

/**
 * ibmvtpm_send_crq() - Send a CRQ request
 *
 * @vdev:	vio device काष्ठा
 * @valid:	Valid field
 * @msg:	Type field
 * @len:	Length field
 * @data:	Data field
 *
 * The ibmvtpm crq is defined as follows:
 *
 * Byte  |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7
 * -----------------------------------------------------------------------
 * Word0 | Valid | Type  |     Length    |              Data
 * -----------------------------------------------------------------------
 * Word1 |                Reserved
 * -----------------------------------------------------------------------
 *
 * Which matches the following काष्ठाure (on bigendian host):
 *
 * काष्ठा ibmvtpm_crq अणु
 *         u8 valid;
 *         u8 msg;
 *         __be16 len;
 *         __be32 data;
 *         __be64 reserved;
 * पूर्ण __attribute__((packed, aligned(8)));
 *
 * However, the value is passed in a रेजिस्टर so just compute the numeric value
 * to load पूर्णांकo the रेजिस्टर aव्योमing byteswap altogether. Endian only affects
 * memory loads and stores - रेजिस्टरs are पूर्णांकernally represented the same.
 *
 * Return:
 *	0 (H_SUCCESS) - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvtpm_send_crq(काष्ठा vio_dev *vdev,
		u8 valid, u8 msg, u16 len, u32 data)
अणु
	u64 w1 = ((u64)valid << 56) | ((u64)msg << 48) | ((u64)len << 32) |
		(u64)data;
	वापस ibmvtpm_send_crq_word(vdev, w1);
पूर्ण

/**
 * tpm_ibmvtpm_recv - Receive data after send
 *
 * @chip:	tpm chip काष्ठा
 * @buf:	buffer to पढ़ो
 * @count:	size of buffer
 *
 * Return:
 *	Number of bytes पढ़ो
 */
अटल पूर्णांक tpm_ibmvtpm_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	u16 len;
	पूर्णांक sig;

	अगर (!ibmvtpm->rtce_buf) अणु
		dev_err(ibmvtpm->dev, "ibmvtpm device is not ready\n");
		वापस 0;
	पूर्ण

	sig = रुको_event_पूर्णांकerruptible(ibmvtpm->wq, !ibmvtpm->tpm_processing_cmd);
	अगर (sig)
		वापस -EINTR;

	len = ibmvtpm->res_len;

	अगर (count < len) अणु
		dev_err(ibmvtpm->dev,
			"Invalid size in recv: count=%zd, crq_size=%d\n",
			count, len);
		वापस -EIO;
	पूर्ण

	spin_lock(&ibmvtpm->rtce_lock);
	स_नकल((व्योम *)buf, (व्योम *)ibmvtpm->rtce_buf, len);
	स_रखो(ibmvtpm->rtce_buf, 0, len);
	ibmvtpm->res_len = 0;
	spin_unlock(&ibmvtpm->rtce_lock);
	वापस len;
पूर्ण

/**
 * ibmvtpm_crq_send_init - Send a CRQ initialize message
 * @ibmvtpm:	vtpm device काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक ibmvtpm_crq_send_init(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc;

	rc = ibmvtpm_send_crq_word(ibmvtpm->vdev, INIT_CRQ_CMD);
	अगर (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"%s failed rc=%d\n", __func__, rc);

	वापस rc;
पूर्ण

/**
 * tpm_ibmvtpm_resume - Resume from suspend
 *
 * @dev:	device काष्ठा
 *
 * Return: Always 0.
 */
अटल पूर्णांक tpm_ibmvtpm_resume(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	पूर्णांक rc = 0;

	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_ENABLE_CRQ,
					ibmvtpm->vdev->unit_address);
	पूर्ण जबतक (rc == H_IN_PROGRESS || rc == H_BUSY || H_IS_LONG_BUSY(rc));

	अगर (rc) अणु
		dev_err(dev, "Error enabling ibmvtpm rc=%d\n", rc);
		वापस rc;
	पूर्ण

	rc = vio_enable_पूर्णांकerrupts(ibmvtpm->vdev);
	अगर (rc) अणु
		dev_err(dev, "Error vio_enable_interrupts rc=%d\n", rc);
		वापस rc;
	पूर्ण

	rc = ibmvtpm_crq_send_init(ibmvtpm);
	अगर (rc)
		dev_err(dev, "Error send_init rc=%d\n", rc);

	वापस rc;
पूर्ण

/**
 * tpm_ibmvtpm_send() - Send a TPM command
 * @chip:	tpm chip काष्ठा
 * @buf:	buffer contains data to send
 * @count:	size of buffer
 *
 * Return:
 *   0 on success,
 *   -त्रुटि_सं on error
 */
अटल पूर्णांक tpm_ibmvtpm_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	bool retry = true;
	पूर्णांक rc, sig;

	अगर (!ibmvtpm->rtce_buf) अणु
		dev_err(ibmvtpm->dev, "ibmvtpm device is not ready\n");
		वापस 0;
	पूर्ण

	अगर (count > ibmvtpm->rtce_size) अणु
		dev_err(ibmvtpm->dev,
			"Invalid size in send: count=%zd, rtce_size=%d\n",
			count, ibmvtpm->rtce_size);
		वापस -EIO;
	पूर्ण

	अगर (ibmvtpm->tpm_processing_cmd) अणु
		dev_info(ibmvtpm->dev,
		         "Need to wait for TPM to finish\n");
		/* रुको क्रम previous command to finish */
		sig = रुको_event_पूर्णांकerruptible(ibmvtpm->wq, !ibmvtpm->tpm_processing_cmd);
		अगर (sig)
			वापस -EINTR;
	पूर्ण

	spin_lock(&ibmvtpm->rtce_lock);
	ibmvtpm->res_len = 0;
	स_नकल((व्योम *)ibmvtpm->rtce_buf, (व्योम *)buf, count);

	/*
	 * set the processing flag beक्रमe the Hcall, since we may get the
	 * result (पूर्णांकerrupt) beक्रमe even being able to check rc.
	 */
	ibmvtpm->tpm_processing_cmd = true;

again:
	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_TPM_COMMAND,
			count, ibmvtpm->rtce_dma_handle);
	अगर (rc != H_SUCCESS) अणु
		/*
		 * H_CLOSED can be वापसed after LPM resume.  Call
		 * tpm_ibmvtpm_resume() to re-enable the CRQ then retry
		 * ibmvtpm_send_crq() once beक्रमe failing.
		 */
		अगर (rc == H_CLOSED && retry) अणु
			tpm_ibmvtpm_resume(ibmvtpm->dev);
			retry = false;
			जाओ again;
		पूर्ण
		dev_err(ibmvtpm->dev, "tpm_ibmvtpm_send failed rc=%d\n", rc);
		ibmvtpm->tpm_processing_cmd = false;
	पूर्ण

	spin_unlock(&ibmvtpm->rtce_lock);
	वापस 0;
पूर्ण

अटल व्योम tpm_ibmvtpm_cancel(काष्ठा tpm_chip *chip)
अणु
	वापस;
पूर्ण

अटल u8 tpm_ibmvtpm_status(काष्ठा tpm_chip *chip)
अणु
	वापस 0;
पूर्ण

/**
 * ibmvtpm_crq_get_rtce_size - Send a CRQ request to get rtce size
 *
 * @ibmvtpm:	vtpm device काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक ibmvtpm_crq_get_rtce_size(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc;

	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_GET_RTCE_BUFFER_SIZE, 0, 0);
	अगर (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"ibmvtpm_crq_get_rtce_size failed rc=%d\n", rc);

	वापस rc;
पूर्ण

/**
 * ibmvtpm_crq_get_version - Send a CRQ request to get vtpm version
 *			   - Note that this is vtpm version and not tpm version
 *
 * @ibmvtpm:	vtpm device काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक ibmvtpm_crq_get_version(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc;

	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_GET_VERSION, 0, 0);
	अगर (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"ibmvtpm_crq_get_version failed rc=%d\n", rc);

	वापस rc;
पूर्ण

/**
 * ibmvtpm_crq_send_init_complete - Send a CRQ initialize complete message
 * @ibmvtpm:	vtpm device काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक ibmvtpm_crq_send_init_complete(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc;

	rc = ibmvtpm_send_crq_word(ibmvtpm->vdev, INIT_CRQ_COMP_CMD);
	अगर (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"ibmvtpm_crq_send_init_complete failed rc=%d\n", rc);

	वापस rc;
पूर्ण

/**
 * tpm_ibmvtpm_हटाओ - ibm vtpm हटाओ entry poपूर्णांक
 * @vdev:	vio device काष्ठा
 *
 * Return: Always 0.
 */
अटल व्योम tpm_ibmvtpm_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&vdev->dev);
	काष्ठा ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	पूर्णांक rc = 0;

	tpm_chip_unरेजिस्टर(chip);

	मुक्त_irq(vdev->irq, ibmvtpm);

	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	dma_unmap_single(ibmvtpm->dev, ibmvtpm->crq_dma_handle,
			 CRQ_RES_BUF_SIZE, DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)ibmvtpm->crq_queue.crq_addr);

	अगर (ibmvtpm->rtce_buf) अणु
		dma_unmap_single(ibmvtpm->dev, ibmvtpm->rtce_dma_handle,
				 ibmvtpm->rtce_size, DMA_BIसूचीECTIONAL);
		kमुक्त(ibmvtpm->rtce_buf);
	पूर्ण

	kमुक्त(ibmvtpm);
	/* For tpm_ibmvtpm_get_desired_dma */
	dev_set_drvdata(&vdev->dev, शून्य);
पूर्ण

/**
 * tpm_ibmvtpm_get_desired_dma - Get DMA size needed by this driver
 * @vdev:	vio device काष्ठा
 *
 * Return:
 *	Number of bytes the driver needs to DMA map.
 */
अटल अचिन्हित दीर्घ tpm_ibmvtpm_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(&vdev->dev);
	काष्ठा ibmvtpm_dev *ibmvtpm;

	/*
	 * ibmvtpm initializes at probe समय, so the data we are
	 * asking क्रम may not be set yet. Estimate that 4K required
	 * क्रम TCE-mapped buffer in addition to CRQ.
	 */
	अगर (chip)
		ibmvtpm = dev_get_drvdata(&chip->dev);
	अन्यथा
		वापस CRQ_RES_BUF_SIZE + PAGE_SIZE;

	वापस CRQ_RES_BUF_SIZE + ibmvtpm->rtce_size;
पूर्ण

/**
 * tpm_ibmvtpm_suspend - Suspend
 * @dev:	device काष्ठा
 *
 * Return: Always 0.
 */
अटल पूर्णांक tpm_ibmvtpm_suspend(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	पूर्णांक rc = 0;

	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_PREPARE_TO_SUSPEND, 0, 0);
	अगर (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"tpm_ibmvtpm_suspend failed rc=%d\n", rc);

	वापस rc;
पूर्ण

/**
 * ibmvtpm_reset_crq - Reset CRQ
 *
 * @ibmvtpm:	ibm vtpm काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक ibmvtpm_reset_crq(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc = 0;

	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ,
					ibmvtpm->vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	स_रखो(ibmvtpm->crq_queue.crq_addr, 0, CRQ_RES_BUF_SIZE);
	ibmvtpm->crq_queue.index = 0;

	वापस plpar_hcall_norets(H_REG_CRQ, ibmvtpm->vdev->unit_address,
				  ibmvtpm->crq_dma_handle, CRQ_RES_BUF_SIZE);
पूर्ण

अटल bool tpm_ibmvtpm_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == 0);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_ibmvtpm = अणु
	.recv = tpm_ibmvtpm_recv,
	.send = tpm_ibmvtpm_send,
	.cancel = tpm_ibmvtpm_cancel,
	.status = tpm_ibmvtpm_status,
	.req_complete_mask = 0,
	.req_complete_val = 0,
	.req_canceled = tpm_ibmvtpm_req_canceled,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops tpm_ibmvtpm_pm_ops = अणु
	.suspend = tpm_ibmvtpm_suspend,
	.resume = tpm_ibmvtpm_resume,
पूर्ण;

/**
 * ibmvtpm_crq_get_next - Get next responded crq
 *
 * @ibmvtpm:	vtpm device काष्ठा
 *
 * Return: vtpm crq poपूर्णांकer or शून्य.
 */
अटल काष्ठा ibmvtpm_crq *ibmvtpm_crq_get_next(काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	काष्ठा ibmvtpm_crq_queue *crq_q = &ibmvtpm->crq_queue;
	काष्ठा ibmvtpm_crq *crq = &crq_q->crq_addr[crq_q->index];

	अगर (crq->valid & VTPM_MSG_RES) अणु
		अगर (++crq_q->index == crq_q->num_entry)
			crq_q->index = 0;
		smp_rmb();
	पूर्ण अन्यथा
		crq = शून्य;
	वापस crq;
पूर्ण

/**
 * ibmvtpm_crq_process - Process responded crq
 *
 * @crq:	crq to be processed
 * @ibmvtpm:	vtpm device काष्ठा
 *
 */
अटल व्योम ibmvtpm_crq_process(काष्ठा ibmvtpm_crq *crq,
				काष्ठा ibmvtpm_dev *ibmvtpm)
अणु
	पूर्णांक rc = 0;

	चयन (crq->valid) अणु
	हाल VALID_INIT_CRQ:
		चयन (crq->msg) अणु
		हाल INIT_CRQ_RES:
			dev_info(ibmvtpm->dev, "CRQ initialized\n");
			rc = ibmvtpm_crq_send_init_complete(ibmvtpm);
			अगर (rc)
				dev_err(ibmvtpm->dev, "Unable to send CRQ init complete rc=%d\n", rc);
			वापस;
		हाल INIT_CRQ_COMP_RES:
			dev_info(ibmvtpm->dev,
				 "CRQ initialization completed\n");
			वापस;
		शेष:
			dev_err(ibmvtpm->dev, "Unknown crq message type: %d\n", crq->msg);
			वापस;
		पूर्ण
	हाल IBMVTPM_VALID_CMD:
		चयन (crq->msg) अणु
		हाल VTPM_GET_RTCE_BUFFER_SIZE_RES:
			अगर (be16_to_cpu(crq->len) <= 0) अणु
				dev_err(ibmvtpm->dev, "Invalid rtce size\n");
				वापस;
			पूर्ण
			ibmvtpm->rtce_size = be16_to_cpu(crq->len);
			ibmvtpm->rtce_buf = kदो_स्मृति(ibmvtpm->rtce_size,
						    GFP_ATOMIC);
			अगर (!ibmvtpm->rtce_buf) अणु
				dev_err(ibmvtpm->dev, "Failed to allocate memory for rtce buffer\n");
				वापस;
			पूर्ण

			ibmvtpm->rtce_dma_handle = dma_map_single(ibmvtpm->dev,
				ibmvtpm->rtce_buf, ibmvtpm->rtce_size,
				DMA_BIसूचीECTIONAL);

			अगर (dma_mapping_error(ibmvtpm->dev,
					      ibmvtpm->rtce_dma_handle)) अणु
				kमुक्त(ibmvtpm->rtce_buf);
				ibmvtpm->rtce_buf = शून्य;
				dev_err(ibmvtpm->dev, "Failed to dma map rtce buffer\n");
			पूर्ण

			वापस;
		हाल VTPM_GET_VERSION_RES:
			ibmvtpm->vtpm_version = be32_to_cpu(crq->data);
			वापस;
		हाल VTPM_TPM_COMMAND_RES:
			/* len of the data in rtce buffer */
			ibmvtpm->res_len = be16_to_cpu(crq->len);
			ibmvtpm->tpm_processing_cmd = false;
			wake_up_पूर्णांकerruptible(&ibmvtpm->wq);
			वापस;
		शेष:
			वापस;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

/**
 * ibmvtpm_पूर्णांकerrupt -	Interrupt handler
 *
 * @irq:		irq number to handle
 * @vtpm_instance:	vtpm that received पूर्णांकerrupt
 *
 * Returns:
 *	IRQ_HANDLED
 **/
अटल irqवापस_t ibmvtpm_पूर्णांकerrupt(पूर्णांक irq, व्योम *vtpm_instance)
अणु
	काष्ठा ibmvtpm_dev *ibmvtpm = (काष्ठा ibmvtpm_dev *) vtpm_instance;
	काष्ठा ibmvtpm_crq *crq;

	/* जबतक loop is needed क्रम initial setup (get version and
	 * get rtce_size). There should be only one tpm request at any
	 * given समय.
	 */
	जबतक ((crq = ibmvtpm_crq_get_next(ibmvtpm)) != शून्य) अणु
		ibmvtpm_crq_process(crq, ibmvtpm);
		wake_up_पूर्णांकerruptible(&ibmvtpm->crq_queue.wq);
		crq->valid = 0;
		smp_wmb();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * tpm_ibmvtpm_probe - ibm vtpm initialize entry poपूर्णांक
 *
 * @vio_dev:	vio device काष्ठा
 * @id:		vio device id काष्ठा
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक tpm_ibmvtpm_probe(काष्ठा vio_dev *vio_dev,
				   स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा ibmvtpm_dev *ibmvtpm;
	काष्ठा device *dev = &vio_dev->dev;
	काष्ठा ibmvtpm_crq_queue *crq_q;
	काष्ठा tpm_chip *chip;
	पूर्णांक rc = -ENOMEM, rc1;

	chip = tpmm_chip_alloc(dev, &tpm_ibmvtpm);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	ibmvtpm = kzalloc(माप(काष्ठा ibmvtpm_dev), GFP_KERNEL);
	अगर (!ibmvtpm) अणु
		dev_err(dev, "kzalloc for ibmvtpm failed\n");
		जाओ cleanup;
	पूर्ण

	ibmvtpm->dev = dev;
	ibmvtpm->vdev = vio_dev;

	crq_q = &ibmvtpm->crq_queue;
	crq_q->crq_addr = (काष्ठा ibmvtpm_crq *)get_zeroed_page(GFP_KERNEL);
	अगर (!crq_q->crq_addr) अणु
		dev_err(dev, "Unable to allocate memory for crq_addr\n");
		जाओ cleanup;
	पूर्ण

	crq_q->num_entry = CRQ_RES_BUF_SIZE / माप(*crq_q->crq_addr);
	init_रुकोqueue_head(&crq_q->wq);
	ibmvtpm->crq_dma_handle = dma_map_single(dev, crq_q->crq_addr,
						 CRQ_RES_BUF_SIZE,
						 DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(dev, ibmvtpm->crq_dma_handle)) अणु
		dev_err(dev, "dma mapping failed\n");
		जाओ cleanup;
	पूर्ण

	rc = plpar_hcall_norets(H_REG_CRQ, vio_dev->unit_address,
				ibmvtpm->crq_dma_handle, CRQ_RES_BUF_SIZE);
	अगर (rc == H_RESOURCE)
		rc = ibmvtpm_reset_crq(ibmvtpm);

	अगर (rc) अणु
		dev_err(dev, "Unable to register CRQ rc=%d\n", rc);
		जाओ reg_crq_cleanup;
	पूर्ण

	rc = request_irq(vio_dev->irq, ibmvtpm_पूर्णांकerrupt, 0,
			 tpm_ibmvtpm_driver_name, ibmvtpm);
	अगर (rc) अणु
		dev_err(dev, "Error %d register irq 0x%x\n", rc, vio_dev->irq);
		जाओ init_irq_cleanup;
	पूर्ण

	rc = vio_enable_पूर्णांकerrupts(vio_dev);
	अगर (rc) अणु
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		जाओ init_irq_cleanup;
	पूर्ण

	init_रुकोqueue_head(&ibmvtpm->wq);

	crq_q->index = 0;

	dev_set_drvdata(&chip->dev, ibmvtpm);

	spin_lock_init(&ibmvtpm->rtce_lock);

	rc = ibmvtpm_crq_send_init(ibmvtpm);
	अगर (rc)
		जाओ init_irq_cleanup;

	rc = ibmvtpm_crq_get_version(ibmvtpm);
	अगर (rc)
		जाओ init_irq_cleanup;

	rc = ibmvtpm_crq_get_rtce_size(ibmvtpm);
	अगर (rc)
		जाओ init_irq_cleanup;

	अगर (!रुको_event_समयout(ibmvtpm->crq_queue.wq,
				ibmvtpm->rtce_buf != शून्य,
				HZ)) अणु
		dev_err(dev, "CRQ response timed out\n");
		जाओ init_irq_cleanup;
	पूर्ण

	अगर (!म_भेद(id->compat, "IBM,vtpm20")) अणु
		chip->flags |= TPM_CHIP_FLAG_TPM2;
		rc = tpm2_get_cc_attrs_tbl(chip);
		अगर (rc)
			जाओ init_irq_cleanup;
	पूर्ण

	वापस tpm_chip_रेजिस्टर(chip);
init_irq_cleanup:
	करो अणु
		rc1 = plpar_hcall_norets(H_FREE_CRQ, vio_dev->unit_address);
	पूर्ण जबतक (rc1 == H_BUSY || H_IS_LONG_BUSY(rc1));
reg_crq_cleanup:
	dma_unmap_single(dev, ibmvtpm->crq_dma_handle, CRQ_RES_BUF_SIZE,
			 DMA_BIसूचीECTIONAL);
cleanup:
	अगर (ibmvtpm) अणु
		अगर (crq_q->crq_addr)
			मुक्त_page((अचिन्हित दीर्घ)crq_q->crq_addr);
		kमुक्त(ibmvtpm);
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा vio_driver ibmvtpm_driver = अणु
	.id_table	 = tpm_ibmvtpm_device_table,
	.probe		 = tpm_ibmvtpm_probe,
	.हटाओ		 = tpm_ibmvtpm_हटाओ,
	.get_desired_dma = tpm_ibmvtpm_get_desired_dma,
	.name		 = tpm_ibmvtpm_driver_name,
	.pm		 = &tpm_ibmvtpm_pm_ops,
पूर्ण;

/**
 * ibmvtpm_module_init - Initialize ibm vtpm module.
 *
 *
 * Return:
 *	0 on success.
 *	Non-zero on failure.
 */
अटल पूर्णांक __init ibmvtpm_module_init(व्योम)
अणु
	वापस vio_रेजिस्टर_driver(&ibmvtpm_driver);
पूर्ण

/**
 * ibmvtpm_module_निकास - Tear करोwn ibm vtpm module.
 */
अटल व्योम __निकास ibmvtpm_module_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&ibmvtpm_driver);
पूर्ण

module_init(ibmvtpm_module_init);
module_निकास(ibmvtpm_module_निकास);

MODULE_AUTHOR("adlai@us.ibm.com");
MODULE_DESCRIPTION("IBM vTPM Driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
