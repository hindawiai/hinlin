<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

/**
 * DOC: Nitro Enclaves (NE) PCI device driver.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nitro_enclaves.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश "ne_misc_dev.h"
#समावेश "ne_pci_dev.h"

/**
 * NE_DEFAULT_TIMEOUT_MSECS - Default समयout to रुको क्रम a reply from
 *			      the NE PCI device.
 */
#घोषणा NE_DEFAULT_TIMEOUT_MSECS	(120000) /* 120 sec */

अटल स्थिर काष्ठा pci_device_id ne_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON, PCI_DEVICE_ID_NE) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ne_pci_ids);

/**
 * ne_submit_request() - Submit command request to the PCI device based on the
 *			 command type.
 * @pdev:		PCI device to send the command to.
 * @cmd_type:		Command type of the request sent to the PCI device.
 * @cmd_request:	Command request payload.
 * @cmd_request_size:	Size of the command request payload.
 *
 * Context: Process context. This function is called with the ne_pci_dev mutex held.
 */
अटल व्योम ne_submit_request(काष्ठा pci_dev *pdev, क्रमागत ne_pci_dev_cmd_type cmd_type,
			      व्योम *cmd_request, माप_प्रकार cmd_request_size)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	स_नकल_toio(ne_pci_dev->iomem_base + NE_SEND_DATA, cmd_request, cmd_request_size);

	ioग_लिखो32(cmd_type, ne_pci_dev->iomem_base + NE_COMMAND);
पूर्ण

/**
 * ne_retrieve_reply() - Retrieve reply from the PCI device.
 * @pdev:		PCI device to receive the reply from.
 * @cmd_reply:		Command reply payload.
 * @cmd_reply_size:	Size of the command reply payload.
 *
 * Context: Process context. This function is called with the ne_pci_dev mutex held.
 */
अटल व्योम ne_retrieve_reply(काष्ठा pci_dev *pdev, काष्ठा ne_pci_dev_cmd_reply *cmd_reply,
			      माप_प्रकार cmd_reply_size)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	स_नकल_fromio(cmd_reply, ne_pci_dev->iomem_base + NE_RECV_DATA, cmd_reply_size);
पूर्ण

/**
 * ne_रुको_क्रम_reply() - Wait क्रम a reply of a PCI device command.
 * @pdev:	PCI device क्रम which a reply is रुकोed.
 *
 * Context: Process context. This function is called with the ne_pci_dev mutex held.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_रुको_क्रम_reply(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);
	पूर्णांक rc = -EINVAL;

	/*
	 * TODO: Update to _पूर्णांकerruptible and handle पूर्णांकerrupted रुको event
	 * e.g. -ERESTARTSYS, incoming संकेतs + update समयout, अगर needed.
	 */
	rc = रुको_event_समयout(ne_pci_dev->cmd_reply_रुको_q,
				atomic_पढ़ो(&ne_pci_dev->cmd_reply_avail) != 0,
				msecs_to_jअगरfies(NE_DEFAULT_TIMEOUT_MSECS));
	अगर (!rc)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक ne_करो_request(काष्ठा pci_dev *pdev, क्रमागत ne_pci_dev_cmd_type cmd_type,
		  व्योम *cmd_request, माप_प्रकार cmd_request_size,
		  काष्ठा ne_pci_dev_cmd_reply *cmd_reply, माप_प्रकार cmd_reply_size)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);
	पूर्णांक rc = -EINVAL;

	अगर (cmd_type <= INVALID_CMD || cmd_type >= MAX_CMD) अणु
		dev_err_ratelimited(&pdev->dev, "Invalid cmd type=%u\n", cmd_type);

		वापस -EINVAL;
	पूर्ण

	अगर (!cmd_request) अणु
		dev_err_ratelimited(&pdev->dev, "Null cmd request for cmd type=%u\n",
				    cmd_type);

		वापस -EINVAL;
	पूर्ण

	अगर (cmd_request_size > NE_SEND_DATA_SIZE) अणु
		dev_err_ratelimited(&pdev->dev, "Invalid req size=%zu for cmd type=%u\n",
				    cmd_request_size, cmd_type);

		वापस -EINVAL;
	पूर्ण

	अगर (!cmd_reply) अणु
		dev_err_ratelimited(&pdev->dev, "Null cmd reply for cmd type=%u\n",
				    cmd_type);

		वापस -EINVAL;
	पूर्ण

	अगर (cmd_reply_size > NE_RECV_DATA_SIZE) अणु
		dev_err_ratelimited(&pdev->dev, "Invalid reply size=%zu for cmd type=%u\n",
				    cmd_reply_size, cmd_type);

		वापस -EINVAL;
	पूर्ण

	/*
	 * Use this mutex so that the PCI device handles one command request at
	 * a समय.
	 */
	mutex_lock(&ne_pci_dev->pci_dev_mutex);

	atomic_set(&ne_pci_dev->cmd_reply_avail, 0);

	ne_submit_request(pdev, cmd_type, cmd_request, cmd_request_size);

	rc = ne_रुको_क्रम_reply(pdev);
	अगर (rc < 0) अणु
		dev_err_ratelimited(&pdev->dev, "Error in wait for reply for cmd type=%u [rc=%d]\n",
				    cmd_type, rc);

		जाओ unlock_mutex;
	पूर्ण

	ne_retrieve_reply(pdev, cmd_reply, cmd_reply_size);

	atomic_set(&ne_pci_dev->cmd_reply_avail, 0);

	अगर (cmd_reply->rc < 0) अणु
		rc = cmd_reply->rc;

		dev_err_ratelimited(&pdev->dev, "Error in cmd process logic, cmd type=%u [rc=%d]\n",
				    cmd_type, rc);

		जाओ unlock_mutex;
	पूर्ण

	rc = 0;

unlock_mutex:
	mutex_unlock(&ne_pci_dev->pci_dev_mutex);

	वापस rc;
पूर्ण

/**
 * ne_reply_handler() - Interrupt handler क्रम retrieving a reply matching a
 *			request sent to the PCI device क्रम enclave lअगरeसमय
 *			management.
 * @irq:	Received पूर्णांकerrupt क्रम a reply sent by the PCI device.
 * @args:	PCI device निजी data काष्ठाure.
 *
 * Context: Interrupt context.
 * Return:
 * * IRQ_HANDLED on handled पूर्णांकerrupt.
 */
अटल irqवापस_t ne_reply_handler(पूर्णांक irq, व्योम *args)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = (काष्ठा ne_pci_dev *)args;

	atomic_set(&ne_pci_dev->cmd_reply_avail, 1);

	/* TODO: Update to _पूर्णांकerruptible. */
	wake_up(&ne_pci_dev->cmd_reply_रुको_q);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ne_event_work_handler() - Work queue handler क्रम notअगरying enclaves on a
 *			     state change received by the event पूर्णांकerrupt
 *			     handler.
 * @work:	Item containing the NE PCI device क्रम which an out-of-band event
 *		was issued.
 *
 * An out-of-band event is being issued by the Nitro Hypervisor when at least
 * one enclave is changing state without client पूर्णांकeraction.
 *
 * Context: Work queue context.
 */
अटल व्योम ne_event_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ne_pci_dev_cmd_reply cmd_reply = अणुपूर्ण;
	काष्ठा ne_enclave *ne_enclave = शून्य;
	काष्ठा ne_pci_dev *ne_pci_dev =
		container_of(work, काष्ठा ne_pci_dev, notअगरy_work);
	काष्ठा pci_dev *pdev = ne_pci_dev->pdev;
	पूर्णांक rc = -EINVAL;
	काष्ठा slot_info_req slot_info_req = अणुपूर्ण;

	mutex_lock(&ne_pci_dev->enclaves_list_mutex);

	/*
	 * Iterate over all enclaves रेजिस्टरed क्रम the Nitro Enclaves
	 * PCI device and determine क्रम which enclave(s) the out-of-band event
	 * is corresponding to.
	 */
	list_क्रम_each_entry(ne_enclave, &ne_pci_dev->enclaves_list, enclave_list_entry) अणु
		mutex_lock(&ne_enclave->enclave_info_mutex);

		/*
		 * Enclaves that were never started cannot receive out-of-band
		 * events.
		 */
		अगर (ne_enclave->state != NE_STATE_RUNNING)
			जाओ unlock;

		slot_info_req.slot_uid = ne_enclave->slot_uid;

		rc = ne_करो_request(pdev, SLOT_INFO,
				   &slot_info_req, माप(slot_info_req),
				   &cmd_reply, माप(cmd_reply));
		अगर (rc < 0)
			dev_err(&pdev->dev, "Error in slot info [rc=%d]\n", rc);

		/* Notअगरy enclave process that the enclave state changed. */
		अगर (ne_enclave->state != cmd_reply.state) अणु
			ne_enclave->state = cmd_reply.state;

			ne_enclave->has_event = true;

			wake_up_पूर्णांकerruptible(&ne_enclave->eventq);
		पूर्ण

unlock:
		 mutex_unlock(&ne_enclave->enclave_info_mutex);
	पूर्ण

	mutex_unlock(&ne_pci_dev->enclaves_list_mutex);
पूर्ण

/**
 * ne_event_handler() - Interrupt handler क्रम PCI device out-of-band events.
 *			This पूर्णांकerrupt करोes not supply any data in the MMIO
 *			region. It notअगरies a change in the state of any of
 *			the launched enclaves.
 * @irq:	Received पूर्णांकerrupt क्रम an out-of-band event.
 * @args:	PCI device निजी data काष्ठाure.
 *
 * Context: Interrupt context.
 * Return:
 * * IRQ_HANDLED on handled पूर्णांकerrupt.
 */
अटल irqवापस_t ne_event_handler(पूर्णांक irq, व्योम *args)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = (काष्ठा ne_pci_dev *)args;

	queue_work(ne_pci_dev->event_wq, &ne_pci_dev->notअगरy_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ne_setup_msix() - Setup MSI-X vectors क्रम the PCI device.
 * @pdev:	PCI device to setup the MSI-X क्रम.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_setup_msix(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);
	पूर्णांक nr_vecs = 0;
	पूर्णांक rc = -EINVAL;

	nr_vecs = pci_msix_vec_count(pdev);
	अगर (nr_vecs < 0) अणु
		rc = nr_vecs;

		dev_err(&pdev->dev, "Error in getting vec count [rc=%d]\n", rc);

		वापस rc;
	पूर्ण

	rc = pci_alloc_irq_vectors(pdev, nr_vecs, nr_vecs, PCI_IRQ_MSIX);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in alloc MSI-X vecs [rc=%d]\n", rc);

		वापस rc;
	पूर्ण

	/*
	 * This IRQ माला_लो triggered every समय the PCI device responds to a
	 * command request. The reply is then retrieved, पढ़ोing from the MMIO
	 * space of the PCI device.
	 */
	rc = request_irq(pci_irq_vector(pdev, NE_VEC_REPLY), ne_reply_handler,
			 0, "enclave_cmd", ne_pci_dev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in request irq reply [rc=%d]\n", rc);

		जाओ मुक्त_irq_vectors;
	पूर्ण

	ne_pci_dev->event_wq = create_singlethपढ़ो_workqueue("ne_pci_dev_wq");
	अगर (!ne_pci_dev->event_wq) अणु
		rc = -ENOMEM;

		dev_err(&pdev->dev, "Cannot get wq for dev events [rc=%d]\n", rc);

		जाओ मुक्त_reply_irq_vec;
	पूर्ण

	INIT_WORK(&ne_pci_dev->notअगरy_work, ne_event_work_handler);

	/*
	 * This IRQ माला_लो triggered every समय any enclave's state changes. Its
	 * handler then scans क्रम the changes and propagates them to the user
	 * space.
	 */
	rc = request_irq(pci_irq_vector(pdev, NE_VEC_EVENT), ne_event_handler,
			 0, "enclave_evt", ne_pci_dev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in request irq event [rc=%d]\n", rc);

		जाओ destroy_wq;
	पूर्ण

	वापस 0;

destroy_wq:
	destroy_workqueue(ne_pci_dev->event_wq);
मुक्त_reply_irq_vec:
	मुक्त_irq(pci_irq_vector(pdev, NE_VEC_REPLY), ne_pci_dev);
मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);

	वापस rc;
पूर्ण

/**
 * ne_tearकरोwn_msix() - Tearकरोwn MSI-X vectors क्रम the PCI device.
 * @pdev:	PCI device to tearकरोwn the MSI-X क्रम.
 *
 * Context: Process context.
 */
अटल व्योम ne_tearकरोwn_msix(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	मुक्त_irq(pci_irq_vector(pdev, NE_VEC_EVENT), ne_pci_dev);

	flush_work(&ne_pci_dev->notअगरy_work);
	flush_workqueue(ne_pci_dev->event_wq);
	destroy_workqueue(ne_pci_dev->event_wq);

	मुक्त_irq(pci_irq_vector(pdev, NE_VEC_REPLY), ne_pci_dev);

	pci_मुक्त_irq_vectors(pdev);
पूर्ण

/**
 * ne_pci_dev_enable() - Select the PCI device version and enable it.
 * @pdev:	PCI device to select version क्रम and then enable.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_pci_dev_enable(काष्ठा pci_dev *pdev)
अणु
	u8 dev_enable_reply = 0;
	u16 dev_version_reply = 0;
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	ioग_लिखो16(NE_VERSION_MAX, ne_pci_dev->iomem_base + NE_VERSION);

	dev_version_reply = ioपढ़ो16(ne_pci_dev->iomem_base + NE_VERSION);
	अगर (dev_version_reply != NE_VERSION_MAX) अणु
		dev_err(&pdev->dev, "Error in pci dev version cmd\n");

		वापस -EIO;
	पूर्ण

	ioग_लिखो8(NE_ENABLE_ON, ne_pci_dev->iomem_base + NE_ENABLE);

	dev_enable_reply = ioपढ़ो8(ne_pci_dev->iomem_base + NE_ENABLE);
	अगर (dev_enable_reply != NE_ENABLE_ON) अणु
		dev_err(&pdev->dev, "Error in pci dev enable cmd\n");

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ne_pci_dev_disable() - Disable the PCI device.
 * @pdev:	PCI device to disable.
 *
 * Context: Process context.
 */
अटल व्योम ne_pci_dev_disable(काष्ठा pci_dev *pdev)
अणु
	u8 dev_disable_reply = 0;
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);
	स्थिर अचिन्हित पूर्णांक sleep_समय = 10; /* 10 ms */
	अचिन्हित पूर्णांक sleep_समय_count = 0;

	ioग_लिखो8(NE_ENABLE_OFF, ne_pci_dev->iomem_base + NE_ENABLE);

	/*
	 * Check क्रम NE_ENABLE_OFF in a loop, to handle हालs when the device
	 * state is not immediately set to disabled and going through a
	 * transitory state of disabling.
	 */
	जबतक (sleep_समय_count < NE_DEFAULT_TIMEOUT_MSECS) अणु
		dev_disable_reply = ioपढ़ो8(ne_pci_dev->iomem_base + NE_ENABLE);
		अगर (dev_disable_reply == NE_ENABLE_OFF)
			वापस;

		msleep_पूर्णांकerruptible(sleep_समय);
		sleep_समय_count += sleep_समय;
	पूर्ण

	dev_disable_reply = ioपढ़ो8(ne_pci_dev->iomem_base + NE_ENABLE);
	अगर (dev_disable_reply != NE_ENABLE_OFF)
		dev_err(&pdev->dev, "Error in pci dev disable cmd\n");
पूर्ण

/**
 * ne_pci_probe() - Probe function क्रम the NE PCI device.
 * @pdev:	PCI device to match with the NE PCI driver.
 * @id :	PCI device id table associated with the NE PCI driver.
 *
 * Context: Process context.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
अटल पूर्णांक ne_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = शून्य;
	पूर्णांक rc = -EINVAL;

	ne_pci_dev = kzalloc(माप(*ne_pci_dev), GFP_KERNEL);
	अगर (!ne_pci_dev)
		वापस -ENOMEM;

	rc = pci_enable_device(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in pci dev enable [rc=%d]\n", rc);

		जाओ मुक्त_ne_pci_dev;
	पूर्ण

	rc = pci_request_regions_exclusive(pdev, "nitro_enclaves");
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in pci request regions [rc=%d]\n", rc);

		जाओ disable_pci_dev;
	पूर्ण

	ne_pci_dev->iomem_base = pci_iomap(pdev, PCI_BAR_NE, 0);
	अगर (!ne_pci_dev->iomem_base) अणु
		rc = -ENOMEM;

		dev_err(&pdev->dev, "Error in pci iomap [rc=%d]\n", rc);

		जाओ release_pci_regions;
	पूर्ण

	pci_set_drvdata(pdev, ne_pci_dev);

	rc = ne_setup_msix(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in pci dev msix setup [rc=%d]\n", rc);

		जाओ iounmap_pci_bar;
	पूर्ण

	ne_pci_dev_disable(pdev);

	rc = ne_pci_dev_enable(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in ne_pci_dev enable [rc=%d]\n", rc);

		जाओ tearकरोwn_msix;
	पूर्ण

	atomic_set(&ne_pci_dev->cmd_reply_avail, 0);
	init_रुकोqueue_head(&ne_pci_dev->cmd_reply_रुको_q);
	INIT_LIST_HEAD(&ne_pci_dev->enclaves_list);
	mutex_init(&ne_pci_dev->enclaves_list_mutex);
	mutex_init(&ne_pci_dev->pci_dev_mutex);
	ne_pci_dev->pdev = pdev;

	ne_devs.ne_pci_dev = ne_pci_dev;

	rc = misc_रेजिस्टर(ne_devs.ne_misc_dev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Error in misc dev register [rc=%d]\n", rc);

		जाओ disable_ne_pci_dev;
	पूर्ण

	वापस 0;

disable_ne_pci_dev:
	ne_devs.ne_pci_dev = शून्य;
	ne_pci_dev_disable(pdev);
tearकरोwn_msix:
	ne_tearकरोwn_msix(pdev);
iounmap_pci_bar:
	pci_set_drvdata(pdev, शून्य);
	pci_iounmap(pdev, ne_pci_dev->iomem_base);
release_pci_regions:
	pci_release_regions(pdev);
disable_pci_dev:
	pci_disable_device(pdev);
मुक्त_ne_pci_dev:
	kमुक्त(ne_pci_dev);

	वापस rc;
पूर्ण

/**
 * ne_pci_हटाओ() - Remove function क्रम the NE PCI device.
 * @pdev:	PCI device associated with the NE PCI driver.
 *
 * Context: Process context.
 */
अटल व्योम ne_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	misc_deरेजिस्टर(ne_devs.ne_misc_dev);

	ne_devs.ne_pci_dev = शून्य;

	ne_pci_dev_disable(pdev);

	ne_tearकरोwn_msix(pdev);

	pci_set_drvdata(pdev, शून्य);

	pci_iounmap(pdev, ne_pci_dev->iomem_base);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	kमुक्त(ne_pci_dev);
पूर्ण

/**
 * ne_pci_shutकरोwn() - Shutकरोwn function क्रम the NE PCI device.
 * @pdev:	PCI device associated with the NE PCI driver.
 *
 * Context: Process context.
 */
अटल व्योम ne_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);

	अगर (!ne_pci_dev)
		वापस;

	misc_deरेजिस्टर(ne_devs.ne_misc_dev);

	ne_devs.ne_pci_dev = शून्य;

	ne_pci_dev_disable(pdev);

	ne_tearकरोwn_msix(pdev);

	pci_set_drvdata(pdev, शून्य);

	pci_iounmap(pdev, ne_pci_dev->iomem_base);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	kमुक्त(ne_pci_dev);
पूर्ण

/*
 * TODO: Add suspend / resume functions क्रम घातer management w/ CONFIG_PM, अगर
 * needed.
 */
/* NE PCI device driver. */
काष्ठा pci_driver ne_pci_driver = अणु
	.name		= "nitro_enclaves",
	.id_table	= ne_pci_ids,
	.probe		= ne_pci_probe,
	.हटाओ		= ne_pci_हटाओ,
	.shutकरोwn	= ne_pci_shutकरोwn,
पूर्ण;
