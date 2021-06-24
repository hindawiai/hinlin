<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Adjunct processor matrix VFIO device driver callbacks.
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Tony Krowiak <akrowiak@linux.ibm.com>
 *	      Halil Pasic <pasic@linux.ibm.com>
 *	      Pierre Morel <pmorel@linux.ibm.com>
 */
#समावेश <linux/माला.स>
#समावेश <linux/vfपन.स>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/bitops.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/zcrypt.h>

#समावेश "vfio_ap_private.h"

#घोषणा VFIO_AP_MDEV_TYPE_HWVIRT "passthrough"
#घोषणा VFIO_AP_MDEV_NAME_HWVIRT "VFIO AP Passthrough Device"

अटल पूर्णांक vfio_ap_mdev_reset_queues(काष्ठा mdev_device *mdev);
अटल काष्ठा vfio_ap_queue *vfio_ap_find_queue(पूर्णांक apqn);

अटल पूर्णांक match_apqn(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा vfio_ap_queue *q = dev_get_drvdata(dev);

	वापस (q->apqn == *(पूर्णांक *)(data)) ? 1 : 0;
पूर्ण

/**
 * vfio_ap_get_queue: Retrieve a queue with a specअगरic APQN from a list
 * @matrix_mdev: the associated mediated matrix
 * @apqn: The queue APQN
 *
 * Retrieve a queue with a specअगरic APQN from the list of the
 * devices of the vfio_ap_drv.
 * Verअगरy that the APID and the APQI are set in the matrix.
 *
 * Returns the poपूर्णांकer to the associated vfio_ap_queue
 */
अटल काष्ठा vfio_ap_queue *vfio_ap_get_queue(
					काष्ठा ap_matrix_mdev *matrix_mdev,
					पूर्णांक apqn)
अणु
	काष्ठा vfio_ap_queue *q;

	अगर (!test_bit_inv(AP_QID_CARD(apqn), matrix_mdev->matrix.apm))
		वापस शून्य;
	अगर (!test_bit_inv(AP_QID_QUEUE(apqn), matrix_mdev->matrix.aqm))
		वापस शून्य;

	q = vfio_ap_find_queue(apqn);
	अगर (q)
		q->matrix_mdev = matrix_mdev;

	वापस q;
पूर्ण

/**
 * vfio_ap_रुको_क्रम_irqclear
 * @apqn: The AP Queue number
 *
 * Checks the IRQ bit क्रम the status of this APQN using ap_tapq.
 * Returns अगर the ap_tapq function succeeded and the bit is clear.
 * Returns अगर ap_tapq function failed with invalid, deconfigured or
 * checkstopped AP.
 * Otherwise retries up to 5 बार after रुकोing 20ms.
 *
 */
अटल व्योम vfio_ap_रुको_क्रम_irqclear(पूर्णांक apqn)
अणु
	काष्ठा ap_queue_status status;
	पूर्णांक retry = 5;

	करो अणु
		status = ap_tapq(apqn, शून्य);
		चयन (status.response_code) अणु
		हाल AP_RESPONSE_NORMAL:
		हाल AP_RESPONSE_RESET_IN_PROGRESS:
			अगर (!status.irq_enabled)
				वापस;
			fallthrough;
		हाल AP_RESPONSE_BUSY:
			msleep(20);
			अवरोध;
		हाल AP_RESPONSE_Q_NOT_AVAIL:
		हाल AP_RESPONSE_DECONFIGURED:
		हाल AP_RESPONSE_CHECKSTOPPED:
		शेष:
			WARN_ONCE(1, "%s: tapq rc %02x: %04x\n", __func__,
				  status.response_code, apqn);
			वापस;
		पूर्ण
	पूर्ण जबतक (--retry);

	WARN_ONCE(1, "%s: tapq rc %02x: %04x could not clear IR bit\n",
		  __func__, status.response_code, apqn);
पूर्ण

/**
 * vfio_ap_मुक्त_aqic_resources
 * @q: The vfio_ap_queue
 *
 * Unरेजिस्टरs the ISC in the GIB when the saved ISC not invalid.
 * Unpin the guest's page holding the NIB when it exist.
 * Reset the saved_pfn and saved_isc to invalid values.
 *
 */
अटल व्योम vfio_ap_मुक्त_aqic_resources(काष्ठा vfio_ap_queue *q)
अणु
	अगर (!q)
		वापस;
	अगर (q->saved_isc != VFIO_AP_ISC_INVALID &&
	    !WARN_ON(!(q->matrix_mdev && q->matrix_mdev->kvm))) अणु
		kvm_s390_gisc_unरेजिस्टर(q->matrix_mdev->kvm, q->saved_isc);
		q->saved_isc = VFIO_AP_ISC_INVALID;
	पूर्ण
	अगर (q->saved_pfn && !WARN_ON(!q->matrix_mdev)) अणु
		vfio_unpin_pages(mdev_dev(q->matrix_mdev->mdev),
				 &q->saved_pfn, 1);
		q->saved_pfn = 0;
	पूर्ण
पूर्ण

/**
 * vfio_ap_irq_disable
 * @q: The vfio_ap_queue
 *
 * Uses ap_aqic to disable the पूर्णांकerruption and in हाल of success, reset
 * in progress or IRQ disable command alपढ़ोy proceeded: calls
 * vfio_ap_रुको_क्रम_irqclear() to check क्रम the IRQ bit to be clear
 * and calls vfio_ap_मुक्त_aqic_resources() to मुक्त the resources associated
 * with the AP पूर्णांकerrupt handling.
 *
 * In the हाल the AP is busy, or a reset is in progress,
 * retries after 20ms, up to 5 बार.
 *
 * Returns अगर ap_aqic function failed with invalid, deconfigured or
 * checkstopped AP.
 */
अटल काष्ठा ap_queue_status vfio_ap_irq_disable(काष्ठा vfio_ap_queue *q)
अणु
	काष्ठा ap_qirq_ctrl aqic_gisa = अणुपूर्ण;
	काष्ठा ap_queue_status status;
	पूर्णांक retries = 5;

	करो अणु
		status = ap_aqic(q->apqn, aqic_gisa, शून्य);
		चयन (status.response_code) अणु
		हाल AP_RESPONSE_OTHERWISE_CHANGED:
		हाल AP_RESPONSE_NORMAL:
			vfio_ap_रुको_क्रम_irqclear(q->apqn);
			जाओ end_मुक्त;
		हाल AP_RESPONSE_RESET_IN_PROGRESS:
		हाल AP_RESPONSE_BUSY:
			msleep(20);
			अवरोध;
		हाल AP_RESPONSE_Q_NOT_AVAIL:
		हाल AP_RESPONSE_DECONFIGURED:
		हाल AP_RESPONSE_CHECKSTOPPED:
		हाल AP_RESPONSE_INVALID_ADDRESS:
		शेष:
			/* All हालs in शेष means AP not operational */
			WARN_ONCE(1, "%s: ap_aqic status %d\n", __func__,
				  status.response_code);
			जाओ end_मुक्त;
		पूर्ण
	पूर्ण जबतक (retries--);

	WARN_ONCE(1, "%s: ap_aqic status %d\n", __func__,
		  status.response_code);
end_मुक्त:
	vfio_ap_मुक्त_aqic_resources(q);
	q->matrix_mdev = शून्य;
	वापस status;
पूर्ण

/**
 * vfio_ap_setirq: Enable Interruption क्रम a APQN
 *
 * @dev: the device associated with the ap_queue
 * @q:	 the vfio_ap_queue holding AQIC parameters
 *
 * Pin the NIB saved in *q
 * Register the guest ISC to GIB पूर्णांकerface and retrieve the
 * host ISC to issue the host side PQAP/AQIC
 *
 * Response.status may be set to AP_RESPONSE_INVALID_ADDRESS in हाल the
 * vfio_pin_pages failed.
 *
 * Otherwise वापस the ap_queue_status वापसed by the ap_aqic(),
 * all retry handling will be करोne by the guest.
 */
अटल काष्ठा ap_queue_status vfio_ap_irq_enable(काष्ठा vfio_ap_queue *q,
						 पूर्णांक isc,
						 अचिन्हित दीर्घ nib)
अणु
	काष्ठा ap_qirq_ctrl aqic_gisa = अणुपूर्ण;
	काष्ठा ap_queue_status status = अणुपूर्ण;
	काष्ठा kvm_s390_gisa *gisa;
	काष्ठा kvm *kvm;
	अचिन्हित दीर्घ h_nib, g_pfn, h_pfn;
	पूर्णांक ret;

	g_pfn = nib >> PAGE_SHIFT;
	ret = vfio_pin_pages(mdev_dev(q->matrix_mdev->mdev), &g_pfn, 1,
			     IOMMU_READ | IOMMU_WRITE, &h_pfn);
	चयन (ret) अणु
	हाल 1:
		अवरोध;
	शेष:
		status.response_code = AP_RESPONSE_INVALID_ADDRESS;
		वापस status;
	पूर्ण

	kvm = q->matrix_mdev->kvm;
	gisa = kvm->arch.gisa_पूर्णांक.origin;

	h_nib = (h_pfn << PAGE_SHIFT) | (nib & ~PAGE_MASK);
	aqic_gisa.gisc = isc;
	aqic_gisa.isc = kvm_s390_gisc_रेजिस्टर(kvm, isc);
	aqic_gisa.ir = 1;
	aqic_gisa.gisa = (uपूर्णांक64_t)gisa >> 4;

	status = ap_aqic(q->apqn, aqic_gisa, (व्योम *)h_nib);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		/* See अगर we did clear older IRQ configuration */
		vfio_ap_मुक्त_aqic_resources(q);
		q->saved_pfn = g_pfn;
		q->saved_isc = isc;
		अवरोध;
	हाल AP_RESPONSE_OTHERWISE_CHANGED:
		/* We could not modअगरy IRQ setings: clear new configuration */
		vfio_unpin_pages(mdev_dev(q->matrix_mdev->mdev), &g_pfn, 1);
		kvm_s390_gisc_unरेजिस्टर(kvm, isc);
		अवरोध;
	शेष:
		pr_warn("%s: apqn %04x: response: %02x\n", __func__, q->apqn,
			status.response_code);
		vfio_ap_irq_disable(q);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * handle_pqap: PQAP inकाष्ठाion callback
 *
 * @vcpu: The vcpu on which we received the PQAP inकाष्ठाion
 *
 * Get the general रेजिस्टर contents to initialize पूर्णांकernal variables.
 * REG[0]: APQN
 * REG[1]: IR and ISC
 * REG[2]: NIB
 *
 * Response.status may be set to following Response Code:
 * - AP_RESPONSE_Q_NOT_AVAIL: अगर the queue is not available
 * - AP_RESPONSE_DECONFIGURED: अगर the queue is not configured
 * - AP_RESPONSE_NORMAL (0) : in हाल of successs
 *   Check vfio_ap_setirq() and vfio_ap_clrirq() क्रम other possible RC.
 * We take the matrix_dev lock to ensure serialization on queues and
 * mediated device access.
 *
 * Return 0 अगर we could handle the request inside KVM.
 * otherwise, वापसs -EOPNOTSUPP to let QEMU handle the fault.
 */
अटल पूर्णांक handle_pqap(काष्ठा kvm_vcpu *vcpu)
अणु
	uपूर्णांक64_t status;
	uपूर्णांक16_t apqn;
	काष्ठा vfio_ap_queue *q;
	काष्ठा ap_queue_status qstatus = अणु
			       .response_code = AP_RESPONSE_Q_NOT_AVAIL, पूर्ण;
	काष्ठा ap_matrix_mdev *matrix_mdev;

	/* If we करो not use the AIV facility just go to userland */
	अगर (!(vcpu->arch.sie_block->eca & ECA_AIV))
		वापस -EOPNOTSUPP;

	apqn = vcpu->run->s.regs.gprs[0] & 0xffff;
	mutex_lock(&matrix_dev->lock);

	अगर (!vcpu->kvm->arch.crypto.pqap_hook)
		जाओ out_unlock;
	matrix_mdev = container_of(vcpu->kvm->arch.crypto.pqap_hook,
				   काष्ठा ap_matrix_mdev, pqap_hook);

	/*
	 * If the KVM poपूर्णांकer is in the process of being set, रुको until the
	 * process has completed.
	 */
	रुको_event_cmd(matrix_mdev->रुको_क्रम_kvm,
		       !matrix_mdev->kvm_busy,
		       mutex_unlock(&matrix_dev->lock),
		       mutex_lock(&matrix_dev->lock));

	/* If the there is no guest using the mdev, there is nothing to करो */
	अगर (!matrix_mdev->kvm)
		जाओ out_unlock;

	q = vfio_ap_get_queue(matrix_mdev, apqn);
	अगर (!q)
		जाओ out_unlock;

	status = vcpu->run->s.regs.gprs[1];

	/* If IR bit(16) is set we enable the पूर्णांकerrupt */
	अगर ((status >> (63 - 16)) & 0x01)
		qstatus = vfio_ap_irq_enable(q, status & 0x07,
					     vcpu->run->s.regs.gprs[2]);
	अन्यथा
		qstatus = vfio_ap_irq_disable(q);

out_unlock:
	स_नकल(&vcpu->run->s.regs.gprs[1], &qstatus, माप(qstatus));
	vcpu->run->s.regs.gprs[1] >>= 32;
	mutex_unlock(&matrix_dev->lock);
	वापस 0;
पूर्ण

अटल व्योम vfio_ap_matrix_init(काष्ठा ap_config_info *info,
				काष्ठा ap_matrix *matrix)
अणु
	matrix->apm_max = info->apxa ? info->Na : 63;
	matrix->aqm_max = info->apxa ? info->Nd : 15;
	matrix->adm_max = info->apxa ? info->Nd : 15;
पूर्ण

अटल पूर्णांक vfio_ap_mdev_create(काष्ठा mdev_device *mdev)
अणु
	काष्ठा ap_matrix_mdev *matrix_mdev;

	अगर ((atomic_dec_अगर_positive(&matrix_dev->available_instances) < 0))
		वापस -EPERM;

	matrix_mdev = kzalloc(माप(*matrix_mdev), GFP_KERNEL);
	अगर (!matrix_mdev) अणु
		atomic_inc(&matrix_dev->available_instances);
		वापस -ENOMEM;
	पूर्ण

	matrix_mdev->mdev = mdev;
	vfio_ap_matrix_init(&matrix_dev->info, &matrix_mdev->matrix);
	init_रुकोqueue_head(&matrix_mdev->रुको_क्रम_kvm);
	mdev_set_drvdata(mdev, matrix_mdev);
	matrix_mdev->pqap_hook.hook = handle_pqap;
	matrix_mdev->pqap_hook.owner = THIS_MODULE;
	mutex_lock(&matrix_dev->lock);
	list_add(&matrix_mdev->node, &matrix_dev->mdev_list);
	mutex_unlock(&matrix_dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ap_mdev_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * un-assignment of control करोमुख्य.
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		mutex_unlock(&matrix_dev->lock);
		वापस -EBUSY;
	पूर्ण

	vfio_ap_mdev_reset_queues(mdev);
	list_del(&matrix_mdev->node);
	kमुक्त(matrix_mdev);
	mdev_set_drvdata(mdev, शून्य);
	atomic_inc(&matrix_dev->available_instances);
	mutex_unlock(&matrix_dev->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_AP_MDEV_NAME_HWVIRT);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(name);

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n",
		       atomic_पढ़ो(&matrix_dev->available_instances));
पूर्ण

अटल MDEV_TYPE_ATTR_RO(available_instances);

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_AP_STRING);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(device_api);

अटल काष्ठा attribute *vfio_ap_mdev_type_attrs[] = अणु
	&mdev_type_attr_name.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_available_instances.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group vfio_ap_mdev_hwvirt_type_group = अणु
	.name = VFIO_AP_MDEV_TYPE_HWVIRT,
	.attrs = vfio_ap_mdev_type_attrs,
पूर्ण;

अटल काष्ठा attribute_group *vfio_ap_mdev_type_groups[] = अणु
	&vfio_ap_mdev_hwvirt_type_group,
	शून्य,
पूर्ण;

काष्ठा vfio_ap_queue_reserved अणु
	अचिन्हित दीर्घ *apid;
	अचिन्हित दीर्घ *apqi;
	bool reserved;
पूर्ण;

/**
 * vfio_ap_has_queue
 *
 * @dev: an AP queue device
 * @data: a काष्ठा vfio_ap_queue_reserved reference
 *
 * Flags whether the AP queue device (@dev) has a queue ID containing the APQN,
 * apid or apqi specअगरied in @data:
 *
 * - If @data contains both an apid and apqi value, then @data will be flagged
 *   as reserved अगर the APID and APQI fields क्रम the AP queue device matches
 *
 * - If @data contains only an apid value, @data will be flagged as
 *   reserved अगर the APID field in the AP queue device matches
 *
 * - If @data contains only an apqi value, @data will be flagged as
 *   reserved अगर the APQI field in the AP queue device matches
 *
 * Returns 0 to indicate the input to function succeeded. Returns -EINVAL अगर
 * @data करोes not contain either an apid or apqi.
 */
अटल पूर्णांक vfio_ap_has_queue(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा vfio_ap_queue_reserved *qres = data;
	काष्ठा ap_queue *ap_queue = to_ap_queue(dev);
	ap_qid_t qid;
	अचिन्हित दीर्घ id;

	अगर (qres->apid && qres->apqi) अणु
		qid = AP_MKQID(*qres->apid, *qres->apqi);
		अगर (qid == ap_queue->qid)
			qres->reserved = true;
	पूर्ण अन्यथा अगर (qres->apid && !qres->apqi) अणु
		id = AP_QID_CARD(ap_queue->qid);
		अगर (id == *qres->apid)
			qres->reserved = true;
	पूर्ण अन्यथा अगर (!qres->apid && qres->apqi) अणु
		id = AP_QID_QUEUE(ap_queue->qid);
		अगर (id == *qres->apqi)
			qres->reserved = true;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vfio_ap_verअगरy_queue_reserved
 *
 * @matrix_dev: a mediated matrix device
 * @apid: an AP adapter ID
 * @apqi: an AP queue index
 *
 * Verअगरies that the AP queue with @apid/@apqi is reserved by the VFIO AP device
 * driver according to the following rules:
 *
 * - If both @apid and @apqi are not शून्य, then there must be an AP queue
 *   device bound to the vfio_ap driver with the APQN identअगरied by @apid and
 *   @apqi
 *
 * - If only @apid is not शून्य, then there must be an AP queue device bound
 *   to the vfio_ap driver with an APQN containing @apid
 *
 * - If only @apqi is not शून्य, then there must be an AP queue device bound
 *   to the vfio_ap driver with an APQN containing @apqi
 *
 * Returns 0 अगर the AP queue is reserved; otherwise, वापसs -EADDRNOTAVAIL.
 */
अटल पूर्णांक vfio_ap_verअगरy_queue_reserved(अचिन्हित दीर्घ *apid,
					 अचिन्हित दीर्घ *apqi)
अणु
	पूर्णांक ret;
	काष्ठा vfio_ap_queue_reserved qres;

	qres.apid = apid;
	qres.apqi = apqi;
	qres.reserved = false;

	ret = driver_क्रम_each_device(&matrix_dev->vfio_ap_drv->driver, शून्य,
				     &qres, vfio_ap_has_queue);
	अगर (ret)
		वापस ret;

	अगर (qres.reserved)
		वापस 0;

	वापस -EADDRNOTAVAIL;
पूर्ण

अटल पूर्णांक
vfio_ap_mdev_verअगरy_queues_reserved_क्रम_apid(काष्ठा ap_matrix_mdev *matrix_mdev,
					     अचिन्हित दीर्घ apid)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apqi;
	अचिन्हित दीर्घ nbits = matrix_mdev->matrix.aqm_max + 1;

	अगर (find_first_bit_inv(matrix_mdev->matrix.aqm, nbits) >= nbits)
		वापस vfio_ap_verअगरy_queue_reserved(&apid, शून्य);

	क्रम_each_set_bit_inv(apqi, matrix_mdev->matrix.aqm, nbits) अणु
		ret = vfio_ap_verअगरy_queue_reserved(&apid, &apqi);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vfio_ap_mdev_verअगरy_no_sharing
 *
 * Verअगरies that the APQNs derived from the cross product of the AP adapter IDs
 * and AP queue indexes comprising the AP matrix are not configured क्रम another
 * mediated device. AP queue sharing is not allowed.
 *
 * @matrix_mdev: the mediated matrix device
 *
 * Returns 0 अगर the APQNs are not shared, otherwise; वापसs -EADDRINUSE.
 */
अटल पूर्णांक vfio_ap_mdev_verअगरy_no_sharing(काष्ठा ap_matrix_mdev *matrix_mdev)
अणु
	काष्ठा ap_matrix_mdev *lstdev;
	DECLARE_BITMAP(apm, AP_DEVICES);
	DECLARE_BITMAP(aqm, AP_DOMAINS);

	list_क्रम_each_entry(lstdev, &matrix_dev->mdev_list, node) अणु
		अगर (matrix_mdev == lstdev)
			जारी;

		स_रखो(apm, 0, माप(apm));
		स_रखो(aqm, 0, माप(aqm));

		/*
		 * We work on full दीर्घs, as we can only exclude the leftover
		 * bits in non-inverse order. The leftover is all zeros.
		 */
		अगर (!biपंचांगap_and(apm, matrix_mdev->matrix.apm,
				lstdev->matrix.apm, AP_DEVICES))
			जारी;

		अगर (!biपंचांगap_and(aqm, matrix_mdev->matrix.aqm,
				lstdev->matrix.aqm, AP_DOMAINS))
			जारी;

		वापस -EADDRINUSE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * assign_adapter_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's assign_adapter attribute
 * @buf:	a buffer containing the AP adapter number (APID) to
 *		be asचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the APID from @buf and sets the corresponding bit in the mediated
 * matrix device's APM.
 *
 * Returns the number of bytes processed अगर the APID is valid; otherwise,
 * वापसs one of the following errors:
 *
 *	1. -EINVAL
 *	   The APID is not a valid number
 *
 *	2. -ENODEV
 *	   The APID exceeds the maximum value configured क्रम the प्रणाली
 *
 *	3. -EADDRNOTAVAIL
 *	   An APQN derived from the cross product of the APID being asचिन्हित
 *	   and the APQIs previously asचिन्हित is not bound to the vfio_ap device
 *	   driver; or, अगर no APQIs have yet been asचिन्हित, the APID is not
 *	   contained in an APQN bound to the vfio_ap device driver.
 *
 *	4. -EADDRINUSE
 *	   An APQN derived from the cross product of the APID being asचिन्हित
 *	   and the APQIs previously asचिन्हित is being used by another mediated
 *	   matrix device
 */
अटल sमाप_प्रकार assign_adapter_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apid;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * un-assignment of adapter
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &apid);
	अगर (ret)
		जाओ करोne;

	अगर (apid > matrix_mdev->matrix.apm_max) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	/*
	 * Set the bit in the AP mask (APM) corresponding to the AP adapter
	 * number (APID). The bits in the mask, from most signअगरicant to least
	 * signअगरicant bit, correspond to APIDs 0-255.
	 */
	ret = vfio_ap_mdev_verअगरy_queues_reserved_क्रम_apid(matrix_mdev, apid);
	अगर (ret)
		जाओ करोne;

	set_bit_inv(apid, matrix_mdev->matrix.apm);

	ret = vfio_ap_mdev_verअगरy_no_sharing(matrix_mdev);
	अगर (ret)
		जाओ share_err;

	ret = count;
	जाओ करोne;

share_err:
	clear_bit_inv(apid, matrix_mdev->matrix.apm);
करोne:
	mutex_unlock(&matrix_dev->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(assign_adapter);

/**
 * unassign_adapter_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's unassign_adapter attribute
 * @buf:	a buffer containing the adapter number (APID) to be unasचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the APID from @buf and clears the corresponding bit in the mediated
 * matrix device's APM.
 *
 * Returns the number of bytes processed अगर the APID is valid; otherwise,
 * वापसs one of the following errors:
 *	-EINVAL अगर the APID is not a number
 *	-ENODEV अगर the APID it exceeds the maximum value configured क्रम the
 *		प्रणाली
 */
अटल sमाप_प्रकार unassign_adapter_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apid;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * un-assignment of adapter
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &apid);
	अगर (ret)
		जाओ करोne;

	अगर (apid > matrix_mdev->matrix.apm_max) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	clear_bit_inv((अचिन्हित दीर्घ)apid, matrix_mdev->matrix.apm);
	ret = count;
करोne:
	mutex_unlock(&matrix_dev->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(unassign_adapter);

अटल पूर्णांक
vfio_ap_mdev_verअगरy_queues_reserved_क्रम_apqi(काष्ठा ap_matrix_mdev *matrix_mdev,
					     अचिन्हित दीर्घ apqi)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apid;
	अचिन्हित दीर्घ nbits = matrix_mdev->matrix.apm_max + 1;

	अगर (find_first_bit_inv(matrix_mdev->matrix.apm, nbits) >= nbits)
		वापस vfio_ap_verअगरy_queue_reserved(शून्य, &apqi);

	क्रम_each_set_bit_inv(apid, matrix_mdev->matrix.apm, nbits) अणु
		ret = vfio_ap_verअगरy_queue_reserved(&apid, &apqi);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * assign_करोमुख्य_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's assign_करोमुख्य attribute
 * @buf:	a buffer containing the AP queue index (APQI) of the करोमुख्य to
 *		be asचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the APQI from @buf and sets the corresponding bit in the mediated
 * matrix device's AQM.
 *
 * Returns the number of bytes processed अगर the APQI is valid; otherwise वापसs
 * one of the following errors:
 *
 *	1. -EINVAL
 *	   The APQI is not a valid number
 *
 *	2. -ENODEV
 *	   The APQI exceeds the maximum value configured क्रम the प्रणाली
 *
 *	3. -EADDRNOTAVAIL
 *	   An APQN derived from the cross product of the APQI being asचिन्हित
 *	   and the APIDs previously asचिन्हित is not bound to the vfio_ap device
 *	   driver; or, अगर no APIDs have yet been asचिन्हित, the APQI is not
 *	   contained in an APQN bound to the vfio_ap device driver.
 *
 *	4. -EADDRINUSE
 *	   An APQN derived from the cross product of the APQI being asचिन्हित
 *	   and the APIDs previously asचिन्हित is being used by another mediated
 *	   matrix device
 */
अटल sमाप_प्रकार assign_करोमुख्य_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apqi;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	अचिन्हित दीर्घ max_apqi = matrix_mdev->matrix.aqm_max;

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * assignment of करोमुख्य
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &apqi);
	अगर (ret)
		जाओ करोne;
	अगर (apqi > max_apqi) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	ret = vfio_ap_mdev_verअगरy_queues_reserved_क्रम_apqi(matrix_mdev, apqi);
	अगर (ret)
		जाओ करोne;

	set_bit_inv(apqi, matrix_mdev->matrix.aqm);

	ret = vfio_ap_mdev_verअगरy_no_sharing(matrix_mdev);
	अगर (ret)
		जाओ share_err;

	ret = count;
	जाओ करोne;

share_err:
	clear_bit_inv(apqi, matrix_mdev->matrix.aqm);
करोne:
	mutex_unlock(&matrix_dev->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(assign_करोमुख्य);


/**
 * unassign_करोमुख्य_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's unassign_करोमुख्य attribute
 * @buf:	a buffer containing the AP queue index (APQI) of the करोमुख्य to
 *		be unasचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the APQI from @buf and clears the corresponding bit in the
 * mediated matrix device's AQM.
 *
 * Returns the number of bytes processed अगर the APQI is valid; otherwise,
 * वापसs one of the following errors:
 *	-EINVAL अगर the APQI is not a number
 *	-ENODEV अगर the APQI exceeds the maximum value configured क्रम the प्रणाली
 */
अटल sमाप_प्रकार unassign_करोमुख्य_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ apqi;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * un-assignment of करोमुख्य
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &apqi);
	अगर (ret)
		जाओ करोne;

	अगर (apqi > matrix_mdev->matrix.aqm_max) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	clear_bit_inv((अचिन्हित दीर्घ)apqi, matrix_mdev->matrix.aqm);
	ret = count;

करोne:
	mutex_unlock(&matrix_dev->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(unassign_करोमुख्य);

/**
 * assign_control_करोमुख्य_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's assign_control_करोमुख्य attribute
 * @buf:	a buffer containing the करोमुख्य ID to be asचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the करोमुख्य ID from @buf and sets the corresponding bit in the mediated
 * matrix device's ADM.
 *
 * Returns the number of bytes processed अगर the करोमुख्य ID is valid; otherwise,
 * वापसs one of the following errors:
 *	-EINVAL अगर the ID is not a number
 *	-ENODEV अगर the ID exceeds the maximum value configured क्रम the प्रणाली
 */
अटल sमाप_प्रकार assign_control_करोमुख्य_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ id;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * assignment of control करोमुख्य.
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &id);
	अगर (ret)
		जाओ करोne;

	अगर (id > matrix_mdev->matrix.adm_max) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	/* Set the bit in the ADM (biपंचांगask) corresponding to the AP control
	 * करोमुख्य number (id). The bits in the mask, from most signअगरicant to
	 * least signअगरicant, correspond to IDs 0 up to the one less than the
	 * number of control करोमुख्यs that can be asचिन्हित.
	 */
	set_bit_inv(id, matrix_mdev->matrix.adm);
	ret = count;
करोne:
	mutex_unlock(&matrix_dev->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(assign_control_करोमुख्य);

/**
 * unassign_control_करोमुख्य_store
 *
 * @dev:	the matrix device
 * @attr:	the mediated matrix device's unassign_control_करोमुख्य attribute
 * @buf:	a buffer containing the करोमुख्य ID to be unasचिन्हित
 * @count:	the number of bytes in @buf
 *
 * Parses the करोमुख्य ID from @buf and clears the corresponding bit in the
 * mediated matrix device's ADM.
 *
 * Returns the number of bytes processed अगर the करोमुख्य ID is valid; otherwise,
 * वापसs one of the following errors:
 *	-EINVAL अगर the ID is not a number
 *	-ENODEV अगर the ID exceeds the maximum value configured क्रम the प्रणाली
 */
अटल sमाप_प्रकार unassign_control_करोमुख्य_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ करोmid;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	अचिन्हित दीर्घ max_करोmid =  matrix_mdev->matrix.adm_max;

	mutex_lock(&matrix_dev->lock);

	/*
	 * If the KVM poपूर्णांकer is in flux or the guest is running, disallow
	 * un-assignment of control करोमुख्य.
	 */
	अगर (matrix_mdev->kvm_busy || matrix_mdev->kvm) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &करोmid);
	अगर (ret)
		जाओ करोne;
	अगर (करोmid > max_करोmid) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	clear_bit_inv(करोmid, matrix_mdev->matrix.adm);
	ret = count;
करोne:
	mutex_unlock(&matrix_dev->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(unassign_control_करोमुख्य);

अटल sमाप_प्रकार control_करोमुख्यs_show(काष्ठा device *dev,
				    काष्ठा device_attribute *dev_attr,
				    अक्षर *buf)
अणु
	अचिन्हित दीर्घ id;
	पूर्णांक nअक्षरs = 0;
	पूर्णांक n;
	अक्षर *bufpos = buf;
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	अचिन्हित दीर्घ max_करोmid = matrix_mdev->matrix.adm_max;

	mutex_lock(&matrix_dev->lock);
	क्रम_each_set_bit_inv(id, matrix_mdev->matrix.adm, max_करोmid + 1) अणु
		n = प्र_लिखो(bufpos, "%04lx\n", id);
		bufpos += n;
		nअक्षरs += n;
	पूर्ण
	mutex_unlock(&matrix_dev->lock);

	वापस nअक्षरs;
पूर्ण
अटल DEVICE_ATTR_RO(control_करोमुख्यs);

अटल sमाप_प्रकार matrix_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	अक्षर *bufpos = buf;
	अचिन्हित दीर्घ apid;
	अचिन्हित दीर्घ apqi;
	अचिन्हित दीर्घ apid1;
	अचिन्हित दीर्घ apqi1;
	अचिन्हित दीर्घ napm_bits = matrix_mdev->matrix.apm_max + 1;
	अचिन्हित दीर्घ naqm_bits = matrix_mdev->matrix.aqm_max + 1;
	पूर्णांक nअक्षरs = 0;
	पूर्णांक n;

	apid1 = find_first_bit_inv(matrix_mdev->matrix.apm, napm_bits);
	apqi1 = find_first_bit_inv(matrix_mdev->matrix.aqm, naqm_bits);

	mutex_lock(&matrix_dev->lock);

	अगर ((apid1 < napm_bits) && (apqi1 < naqm_bits)) अणु
		क्रम_each_set_bit_inv(apid, matrix_mdev->matrix.apm, napm_bits) अणु
			क्रम_each_set_bit_inv(apqi, matrix_mdev->matrix.aqm,
					     naqm_bits) अणु
				n = प्र_लिखो(bufpos, "%02lx.%04lx\n", apid,
					    apqi);
				bufpos += n;
				nअक्षरs += n;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (apid1 < napm_bits) अणु
		क्रम_each_set_bit_inv(apid, matrix_mdev->matrix.apm, napm_bits) अणु
			n = प्र_लिखो(bufpos, "%02lx.\n", apid);
			bufpos += n;
			nअक्षरs += n;
		पूर्ण
	पूर्ण अन्यथा अगर (apqi1 < naqm_bits) अणु
		क्रम_each_set_bit_inv(apqi, matrix_mdev->matrix.aqm, naqm_bits) अणु
			n = प्र_लिखो(bufpos, ".%04lx\n", apqi);
			bufpos += n;
			nअक्षरs += n;
		पूर्ण
	पूर्ण

	mutex_unlock(&matrix_dev->lock);

	वापस nअक्षरs;
पूर्ण
अटल DEVICE_ATTR_RO(matrix);

अटल काष्ठा attribute *vfio_ap_mdev_attrs[] = अणु
	&dev_attr_assign_adapter.attr,
	&dev_attr_unassign_adapter.attr,
	&dev_attr_assign_करोमुख्य.attr,
	&dev_attr_unassign_करोमुख्य.attr,
	&dev_attr_assign_control_करोमुख्य.attr,
	&dev_attr_unassign_control_करोमुख्य.attr,
	&dev_attr_control_करोमुख्यs.attr,
	&dev_attr_matrix.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group vfio_ap_mdev_attr_group = अणु
	.attrs = vfio_ap_mdev_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *vfio_ap_mdev_attr_groups[] = अणु
	&vfio_ap_mdev_attr_group,
	शून्य
पूर्ण;

/**
 * vfio_ap_mdev_set_kvm
 *
 * @matrix_mdev: a mediated matrix device
 * @kvm: reference to KVM instance
 *
 * Sets all data क्रम @matrix_mdev that are needed to manage AP resources
 * क्रम the guest whose state is represented by @kvm.
 *
 * Note: The matrix_dev->lock must be taken prior to calling
 * this function; however, the lock will be temporarily released जबतक the
 * guest's AP configuration is set to aव्योम a potential lockdep splat.
 * The kvm->lock is taken to set the guest's AP configuration which, under
 * certain circumstances, will result in a circular lock dependency अगर this is
 * करोne under the @matrix_mdev->lock.
 *
 * Return 0 अगर no other mediated matrix device has a reference to @kvm;
 * otherwise, वापसs an -EPERM.
 */
अटल पूर्णांक vfio_ap_mdev_set_kvm(काष्ठा ap_matrix_mdev *matrix_mdev,
				काष्ठा kvm *kvm)
अणु
	काष्ठा ap_matrix_mdev *m;

	अगर (kvm->arch.crypto.crycbd) अणु
		list_क्रम_each_entry(m, &matrix_dev->mdev_list, node) अणु
			अगर (m != matrix_mdev && m->kvm == kvm)
				वापस -EPERM;
		पूर्ण

		kvm_get_kvm(kvm);
		matrix_mdev->kvm_busy = true;
		mutex_unlock(&matrix_dev->lock);
		kvm_arch_crypto_set_masks(kvm,
					  matrix_mdev->matrix.apm,
					  matrix_mdev->matrix.aqm,
					  matrix_mdev->matrix.adm);
		mutex_lock(&matrix_dev->lock);
		kvm->arch.crypto.pqap_hook = &matrix_mdev->pqap_hook;
		matrix_mdev->kvm = kvm;
		matrix_mdev->kvm_busy = false;
		wake_up_all(&matrix_mdev->रुको_क्रम_kvm);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vfio_ap_mdev_iommu_notअगरier: IOMMU notअगरier callback
 *
 * @nb: The notअगरier block
 * @action: Action to be taken
 * @data: data associated with the request
 *
 * For an UNMAP request, unpin the guest IOVA (the NIB guest address we
 * pinned beक्रमe). Other requests are ignored.
 *
 */
अटल पूर्णांक vfio_ap_mdev_iommu_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा ap_matrix_mdev *matrix_mdev;

	matrix_mdev = container_of(nb, काष्ठा ap_matrix_mdev, iommu_notअगरier);

	अगर (action == VFIO_IOMMU_NOTIFY_DMA_UNMAP) अणु
		काष्ठा vfio_iommu_type1_dma_unmap *unmap = data;
		अचिन्हित दीर्घ g_pfn = unmap->iova >> PAGE_SHIFT;

		vfio_unpin_pages(mdev_dev(matrix_mdev->mdev), &g_pfn, 1);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * vfio_ap_mdev_unset_kvm
 *
 * @matrix_mdev: a matrix mediated device
 *
 * Perक्रमms clean-up of resources no दीर्घer needed by @matrix_mdev.
 *
 * Note: The matrix_dev->lock must be taken prior to calling
 * this function; however, the lock will be temporarily released जबतक the
 * guest's AP configuration is cleared to aव्योम a potential lockdep splat.
 * The kvm->lock is taken to clear the guest's AP configuration which, under
 * certain circumstances, will result in a circular lock dependency अगर this is
 * करोne under the @matrix_mdev->lock.
 *
 */
अटल व्योम vfio_ap_mdev_unset_kvm(काष्ठा ap_matrix_mdev *matrix_mdev)
अणु
	/*
	 * If the KVM poपूर्णांकer is in the process of being set, रुको until the
	 * process has completed.
	 */
	रुको_event_cmd(matrix_mdev->रुको_क्रम_kvm,
		       !matrix_mdev->kvm_busy,
		       mutex_unlock(&matrix_dev->lock),
		       mutex_lock(&matrix_dev->lock));

	अगर (matrix_mdev->kvm) अणु
		matrix_mdev->kvm_busy = true;
		mutex_unlock(&matrix_dev->lock);
		kvm_arch_crypto_clear_masks(matrix_mdev->kvm);
		mutex_lock(&matrix_dev->lock);
		vfio_ap_mdev_reset_queues(matrix_mdev->mdev);
		matrix_mdev->kvm->arch.crypto.pqap_hook = शून्य;
		kvm_put_kvm(matrix_mdev->kvm);
		matrix_mdev->kvm = शून्य;
		matrix_mdev->kvm_busy = false;
		wake_up_all(&matrix_mdev->रुको_क्रम_kvm);
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_ap_mdev_group_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक notअगरy_rc = NOTIFY_OK;
	काष्ठा ap_matrix_mdev *matrix_mdev;

	अगर (action != VFIO_GROUP_NOTIFY_SET_KVM)
		वापस NOTIFY_OK;

	mutex_lock(&matrix_dev->lock);
	matrix_mdev = container_of(nb, काष्ठा ap_matrix_mdev, group_notअगरier);

	अगर (!data)
		vfio_ap_mdev_unset_kvm(matrix_mdev);
	अन्यथा अगर (vfio_ap_mdev_set_kvm(matrix_mdev, data))
		notअगरy_rc = NOTIFY_DONE;

	mutex_unlock(&matrix_dev->lock);

	वापस notअगरy_rc;
पूर्ण

अटल काष्ठा vfio_ap_queue *vfio_ap_find_queue(पूर्णांक apqn)
अणु
	काष्ठा device *dev;
	काष्ठा vfio_ap_queue *q = शून्य;

	dev = driver_find_device(&matrix_dev->vfio_ap_drv->driver, शून्य,
				 &apqn, match_apqn);
	अगर (dev) अणु
		q = dev_get_drvdata(dev);
		put_device(dev);
	पूर्ण

	वापस q;
पूर्ण

पूर्णांक vfio_ap_mdev_reset_queue(काष्ठा vfio_ap_queue *q,
			     अचिन्हित पूर्णांक retry)
अणु
	काष्ठा ap_queue_status status;
	पूर्णांक ret;
	पूर्णांक retry2 = 2;

	अगर (!q)
		वापस 0;

retry_zapq:
	status = ap_zapq(q->apqn);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
		ret = 0;
		अवरोध;
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
		अगर (retry--) अणु
			msleep(20);
			जाओ retry_zapq;
		पूर्ण
		ret = -EBUSY;
		अवरोध;
	हाल AP_RESPONSE_Q_NOT_AVAIL:
	हाल AP_RESPONSE_DECONFIGURED:
	हाल AP_RESPONSE_CHECKSTOPPED:
		WARN_ON_ONCE(status.irq_enabled);
		ret = -EBUSY;
		जाओ मुक्त_resources;
	शेष:
		/* things are really broken, give up */
		WARN(true, "PQAP/ZAPQ completed with invalid rc (%x)\n",
		     status.response_code);
		वापस -EIO;
	पूर्ण

	/* रुको क्रम the reset to take effect */
	जबतक (retry2--) अणु
		अगर (status.queue_empty && !status.irq_enabled)
			अवरोध;
		msleep(20);
		status = ap_tapq(q->apqn, शून्य);
	पूर्ण
	WARN_ON_ONCE(retry2 <= 0);

मुक्त_resources:
	vfio_ap_मुक्त_aqic_resources(q);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_ap_mdev_reset_queues(काष्ठा mdev_device *mdev)
अणु
	पूर्णांक ret;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ apid, apqi;
	काष्ठा vfio_ap_queue *q;
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	क्रम_each_set_bit_inv(apid, matrix_mdev->matrix.apm,
			     matrix_mdev->matrix.apm_max + 1) अणु
		क्रम_each_set_bit_inv(apqi, matrix_mdev->matrix.aqm,
				     matrix_mdev->matrix.aqm_max + 1) अणु
			q = vfio_ap_find_queue(AP_MKQID(apid, apqi));
			ret = vfio_ap_mdev_reset_queue(q, 1);
			/*
			 * Regardless whether a queue turns out to be busy, or
			 * is not operational, we need to जारी resetting
			 * the reमुख्यing queues.
			 */
			अगर (ret)
				rc = ret;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक vfio_ap_mdev_खोलो(काष्ठा mdev_device *mdev)
अणु
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	अचिन्हित दीर्घ events;
	पूर्णांक ret;


	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	matrix_mdev->group_notअगरier.notअगरier_call = vfio_ap_mdev_group_notअगरier;
	events = VFIO_GROUP_NOTIFY_SET_KVM;

	ret = vfio_रेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				     &events, &matrix_mdev->group_notअगरier);
	अगर (ret) अणु
		module_put(THIS_MODULE);
		वापस ret;
	पूर्ण

	matrix_mdev->iommu_notअगरier.notअगरier_call = vfio_ap_mdev_iommu_notअगरier;
	events = VFIO_IOMMU_NOTIFY_DMA_UNMAP;
	ret = vfio_रेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				     &events, &matrix_mdev->iommu_notअगरier);
	अगर (!ret)
		वापस ret;

	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				 &matrix_mdev->group_notअगरier);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल व्योम vfio_ap_mdev_release(काष्ठा mdev_device *mdev)
अणु
	काष्ठा ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);
	vfio_ap_mdev_unset_kvm(matrix_mdev);
	mutex_unlock(&matrix_dev->lock);

	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &matrix_mdev->iommu_notअगरier);
	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				 &matrix_mdev->group_notअगरier);
	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक vfio_ap_mdev_get_device_info(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ minsz;
	काष्ठा vfio_device_info info;

	minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

	अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
		वापस -EFAULT;

	अगर (info.argsz < minsz)
		वापस -EINVAL;

	info.flags = VFIO_DEVICE_FLAGS_AP | VFIO_DEVICE_FLAGS_RESET;
	info.num_regions = 0;
	info.num_irqs = 0;

	वापस copy_to_user((व्योम __user *)arg, &info, minsz) ? -EFAULT : 0;
पूर्ण

अटल sमाप_प्रकार vfio_ap_mdev_ioctl(काष्ठा mdev_device *mdev,
				    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा ap_matrix_mdev *matrix_mdev;

	mutex_lock(&matrix_dev->lock);
	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
		ret = vfio_ap_mdev_get_device_info(arg);
		अवरोध;
	हाल VFIO_DEVICE_RESET:
		matrix_mdev = mdev_get_drvdata(mdev);
		अगर (WARN(!matrix_mdev, "Driver data missing from mdev!!")) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * If the KVM poपूर्णांकer is in the process of being set, रुको until
		 * the process has completed.
		 */
		रुको_event_cmd(matrix_mdev->रुको_क्रम_kvm,
			       !matrix_mdev->kvm_busy,
			       mutex_unlock(&matrix_dev->lock),
			       mutex_lock(&matrix_dev->lock));

		ret = vfio_ap_mdev_reset_queues(mdev);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&matrix_dev->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mdev_parent_ops vfio_ap_matrix_ops = अणु
	.owner			= THIS_MODULE,
	.supported_type_groups	= vfio_ap_mdev_type_groups,
	.mdev_attr_groups	= vfio_ap_mdev_attr_groups,
	.create			= vfio_ap_mdev_create,
	.हटाओ			= vfio_ap_mdev_हटाओ,
	.खोलो			= vfio_ap_mdev_खोलो,
	.release		= vfio_ap_mdev_release,
	.ioctl			= vfio_ap_mdev_ioctl,
पूर्ण;

पूर्णांक vfio_ap_mdev_रेजिस्टर(व्योम)
अणु
	atomic_set(&matrix_dev->available_instances, MAX_ZDEV_ENTRIES_EXT);

	वापस mdev_रेजिस्टर_device(&matrix_dev->device, &vfio_ap_matrix_ops);
पूर्ण

व्योम vfio_ap_mdev_unरेजिस्टर(व्योम)
अणु
	mdev_unरेजिस्टर_device(&matrix_dev->device);
पूर्ण
