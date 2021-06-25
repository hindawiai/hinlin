<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_cfg.h"
#समावेश "adf_cfg_strings.h"
#समावेश "adf_cfg_common.h"
#समावेश "adf_transport_access_macros.h"
#समावेश "adf_transport_internal.h"
#समावेश "adf_pf2vf_msg.h"

#घोषणा ADF_VINTSOU_OFFSET	0x204
#घोषणा ADF_VINTSOU_BUN		BIT(0)
#घोषणा ADF_VINTSOU_PF2VF	BIT(1)

अटल काष्ठा workqueue_काष्ठा *adf_vf_stop_wq;

काष्ठा adf_vf_stop_data अणु
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल पूर्णांक adf_enable_msi(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_dev_info = &accel_dev->accel_pci_dev;
	पूर्णांक stat = pci_enable_msi(pci_dev_info->pci_dev);

	अगर (stat) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to enable MSI interrupts\n");
		वापस stat;
	पूर्ण

	accel_dev->vf.irq_name = kzalloc(ADF_MAX_MSIX_VECTOR_NAME, GFP_KERNEL);
	अगर (!accel_dev->vf.irq_name)
		वापस -ENOMEM;

	वापस stat;
पूर्ण

अटल व्योम adf_disable_msi(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);

	kमुक्त(accel_dev->vf.irq_name);
	pci_disable_msi(pdev);
पूर्ण

अटल व्योम adf_dev_stop_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adf_vf_stop_data *stop_data =
		container_of(work, काष्ठा adf_vf_stop_data, work);
	काष्ठा adf_accel_dev *accel_dev = stop_data->accel_dev;

	adf_dev_stop(accel_dev);
	adf_dev_shutकरोwn(accel_dev);

	/* Re-enable PF2VF पूर्णांकerrupts */
	adf_enable_pf2vf_पूर्णांकerrupts(accel_dev);
	kमुक्त(stop_data);
पूर्ण

अटल व्योम adf_pf2vf_bh_handler(व्योम *data)
अणु
	काष्ठा adf_accel_dev *accel_dev = data;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_bar *pmisc =
			&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
	व्योम __iomem *pmisc_bar_addr = pmisc->virt_addr;
	u32 msg;

	/* Read the message from PF */
	msg = ADF_CSR_RD(pmisc_bar_addr, hw_data->get_pf2vf_offset(0));

	अगर (!(msg & ADF_PF2VF_MSGORIGIN_SYSTEM))
		/* Ignore legacy non-प्रणाली (non-kernel) PF2VF messages */
		जाओ err;

	चयन ((msg & ADF_PF2VF_MSGTYPE_MASK) >> ADF_PF2VF_MSGTYPE_SHIFT) अणु
	हाल ADF_PF2VF_MSGTYPE_RESTARTING: अणु
		काष्ठा adf_vf_stop_data *stop_data;

		dev_dbg(&GET_DEV(accel_dev),
			"Restarting msg received from PF 0x%x\n", msg);

		clear_bit(ADF_STATUS_PF_RUNNING, &accel_dev->status);

		stop_data = kzalloc(माप(*stop_data), GFP_ATOMIC);
		अगर (!stop_data) अणु
			dev_err(&GET_DEV(accel_dev),
				"Couldn't schedule stop for vf_%d\n",
				accel_dev->accel_id);
			वापस;
		पूर्ण
		stop_data->accel_dev = accel_dev;
		INIT_WORK(&stop_data->work, adf_dev_stop_async);
		queue_work(adf_vf_stop_wq, &stop_data->work);
		/* To ack, clear the PF2VFINT bit */
		msg &= ~ADF_PF2VF_INT;
		ADF_CSR_WR(pmisc_bar_addr, hw_data->get_pf2vf_offset(0), msg);
		वापस;
	पूर्ण
	हाल ADF_PF2VF_MSGTYPE_VERSION_RESP:
		dev_dbg(&GET_DEV(accel_dev),
			"Version resp received from PF 0x%x\n", msg);
		accel_dev->vf.pf_version =
			(msg & ADF_PF2VF_VERSION_RESP_VERS_MASK) >>
			ADF_PF2VF_VERSION_RESP_VERS_SHIFT;
		accel_dev->vf.compatible =
			(msg & ADF_PF2VF_VERSION_RESP_RESULT_MASK) >>
			ADF_PF2VF_VERSION_RESP_RESULT_SHIFT;
		complete(&accel_dev->vf.iov_msg_completion);
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	/* To ack, clear the PF2VFINT bit */
	msg &= ~ADF_PF2VF_INT;
	ADF_CSR_WR(pmisc_bar_addr, hw_data->get_pf2vf_offset(0), msg);

	/* Re-enable PF2VF पूर्णांकerrupts */
	adf_enable_pf2vf_पूर्णांकerrupts(accel_dev);
	वापस;
err:
	dev_err(&GET_DEV(accel_dev),
		"Unknown message from PF (0x%x); leaving PF2VF ints disabled\n",
		msg);
पूर्ण

अटल पूर्णांक adf_setup_pf2vf_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	tasklet_init(&accel_dev->vf.pf2vf_bh_tasklet,
		     (व्योम *)adf_pf2vf_bh_handler, (अचिन्हित दीर्घ)accel_dev);

	mutex_init(&accel_dev->vf.vf2pf_lock);
	वापस 0;
पूर्ण

अटल व्योम adf_cleanup_pf2vf_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	tasklet_disable(&accel_dev->vf.pf2vf_bh_tasklet);
	tasklet_समाप्त(&accel_dev->vf.pf2vf_bh_tasklet);
	mutex_destroy(&accel_dev->vf.vf2pf_lock);
पूर्ण

अटल irqवापस_t adf_isr(पूर्णांक irq, व्योम *privdata)
अणु
	काष्ठा adf_accel_dev *accel_dev = privdata;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_hw_csr_ops *csr_ops = &hw_data->csr_ops;
	काष्ठा adf_bar *pmisc =
			&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
	व्योम __iomem *pmisc_bar_addr = pmisc->virt_addr;
	u32 v_पूर्णांक;

	/* Read VF INT source CSR to determine the source of VF पूर्णांकerrupt */
	v_पूर्णांक = ADF_CSR_RD(pmisc_bar_addr, ADF_VINTSOU_OFFSET);

	/* Check क्रम PF2VF पूर्णांकerrupt */
	अगर (v_पूर्णांक & ADF_VINTSOU_PF2VF) अणु
		/* Disable PF to VF पूर्णांकerrupt */
		adf_disable_pf2vf_पूर्णांकerrupts(accel_dev);

		/* Schedule tasklet to handle पूर्णांकerrupt BH */
		tasklet_hi_schedule(&accel_dev->vf.pf2vf_bh_tasklet);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Check bundle पूर्णांकerrupt */
	अगर (v_पूर्णांक & ADF_VINTSOU_BUN) अणु
		काष्ठा adf_etr_data *etr_data = accel_dev->transport;
		काष्ठा adf_etr_bank_data *bank = &etr_data->banks[0];

		/* Disable Flag and Coalesce Ring Interrupts */
		csr_ops->ग_लिखो_csr_पूर्णांक_flag_and_col(bank->csr_addr,
						    bank->bank_number, 0);
		tasklet_hi_schedule(&bank->resp_handler);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक adf_request_msi_irq(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	snम_लिखो(accel_dev->vf.irq_name, ADF_MAX_MSIX_VECTOR_NAME,
		 "qat_%02x:%02d.%02d", pdev->bus->number, PCI_SLOT(pdev->devfn),
		 PCI_FUNC(pdev->devfn));
	ret = request_irq(pdev->irq, adf_isr, 0, accel_dev->vf.irq_name,
			  (व्योम *)accel_dev);
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev), "failed to enable irq for %s\n",
			accel_dev->vf.irq_name);
		वापस ret;
	पूर्ण
	cpu = accel_dev->accel_id % num_online_cpus();
	irq_set_affinity_hपूर्णांक(pdev->irq, get_cpu_mask(cpu));

	वापस ret;
पूर्ण

अटल पूर्णांक adf_setup_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *priv_data = accel_dev->transport;

	tasklet_init(&priv_data->banks[0].resp_handler, adf_response_handler,
		     (अचिन्हित दीर्घ)priv_data->banks);
	वापस 0;
पूर्ण

अटल व्योम adf_cleanup_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *priv_data = accel_dev->transport;

	tasklet_disable(&priv_data->banks[0].resp_handler);
	tasklet_समाप्त(&priv_data->banks[0].resp_handler);
पूर्ण

/**
 * adf_vf_isr_resource_मुक्त() - Free IRQ क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function मुक्तs पूर्णांकerrupts क्रम acceleration device भव function.
 */
व्योम adf_vf_isr_resource_मुक्त(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);

	irq_set_affinity_hपूर्णांक(pdev->irq, शून्य);
	मुक्त_irq(pdev->irq, (व्योम *)accel_dev);
	adf_cleanup_bh(accel_dev);
	adf_cleanup_pf2vf_bh(accel_dev);
	adf_disable_msi(accel_dev);
पूर्ण
EXPORT_SYMBOL_GPL(adf_vf_isr_resource_मुक्त);

/**
 * adf_vf_isr_resource_alloc() - Allocate IRQ क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function allocates पूर्णांकerrupts क्रम acceleration device भव function.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_vf_isr_resource_alloc(काष्ठा adf_accel_dev *accel_dev)
अणु
	अगर (adf_enable_msi(accel_dev))
		जाओ err_out;

	अगर (adf_setup_pf2vf_bh(accel_dev))
		जाओ err_disable_msi;

	अगर (adf_setup_bh(accel_dev))
		जाओ err_cleanup_pf2vf_bh;

	अगर (adf_request_msi_irq(accel_dev))
		जाओ err_cleanup_bh;

	वापस 0;

err_cleanup_bh:
	adf_cleanup_bh(accel_dev);

err_cleanup_pf2vf_bh:
	adf_cleanup_pf2vf_bh(accel_dev);

err_disable_msi:
	adf_disable_msi(accel_dev);

err_out:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL_GPL(adf_vf_isr_resource_alloc);

पूर्णांक __init adf_init_vf_wq(व्योम)
अणु
	adf_vf_stop_wq = alloc_workqueue("adf_vf_stop_wq", WQ_MEM_RECLAIM, 0);

	वापस !adf_vf_stop_wq ? -EFAULT : 0;
पूर्ण

व्योम adf_निकास_vf_wq(व्योम)
अणु
	अगर (adf_vf_stop_wq)
		destroy_workqueue(adf_vf_stop_wq);

	adf_vf_stop_wq = शून्य;
पूर्ण
