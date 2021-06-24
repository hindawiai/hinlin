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
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_cfg.h"
#समावेश "adf_cfg_strings.h"
#समावेश "adf_cfg_common.h"
#समावेश "adf_transport_access_macros.h"
#समावेश "adf_transport_internal.h"

अटल पूर्णांक adf_enable_msix(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_dev_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 msix_num_entries = 1;

	अगर (hw_data->set_msix_rttable)
		hw_data->set_msix_rttable(accel_dev);

	/* If SR-IOV is disabled, add entries क्रम each bank */
	अगर (!accel_dev->pf.vf_info) अणु
		पूर्णांक i;

		msix_num_entries += hw_data->num_banks;
		क्रम (i = 0; i < msix_num_entries; i++)
			pci_dev_info->msix_entries.entries[i].entry = i;
	पूर्ण अन्यथा अणु
		pci_dev_info->msix_entries.entries[0].entry =
			hw_data->num_banks;
	पूर्ण

	अगर (pci_enable_msix_exact(pci_dev_info->pci_dev,
				  pci_dev_info->msix_entries.entries,
				  msix_num_entries)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to enable MSI-X IRQ(s)\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adf_disable_msix(काष्ठा adf_accel_pci *pci_dev_info)
अणु
	pci_disable_msix(pci_dev_info->pci_dev);
पूर्ण

अटल irqवापस_t adf_msix_isr_bundle(पूर्णांक irq, व्योम *bank_ptr)
अणु
	काष्ठा adf_etr_bank_data *bank = bank_ptr;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	csr_ops->ग_लिखो_csr_पूर्णांक_flag_and_col(bank->csr_addr, bank->bank_number,
					    0);
	tasklet_hi_schedule(&bank->resp_handler);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t adf_msix_isr_ae(पूर्णांक irq, व्योम *dev_ptr)
अणु
	काष्ठा adf_accel_dev *accel_dev = dev_ptr;

#अगर_घोषित CONFIG_PCI_IOV
	/* If SR-IOV is enabled (vf_info is non-शून्य), check क्रम VF->PF पूर्णांकs */
	अगर (accel_dev->pf.vf_info) अणु
		काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
		काष्ठा adf_bar *pmisc =
			&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
		व्योम __iomem *pmisc_bar_addr = pmisc->virt_addr;
		u32 vf_mask;

		/* Get the पूर्णांकerrupt sources triggered by VFs */
		vf_mask = ((ADF_CSR_RD(pmisc_bar_addr, ADF_ERRSOU5) &
			    0x0000FFFF) << 16) |
			  ((ADF_CSR_RD(pmisc_bar_addr, ADF_ERRSOU3) &
			    0x01FFFE00) >> 9);

		अगर (vf_mask) अणु
			काष्ठा adf_accel_vf_info *vf_info;
			bool irq_handled = false;
			पूर्णांक i;

			/* Disable VF2PF पूर्णांकerrupts क्रम VFs with pending पूर्णांकs */
			adf_disable_vf2pf_पूर्णांकerrupts(accel_dev, vf_mask);

			/*
			 * Schedule tasklets to handle VF2PF पूर्णांकerrupt BHs
			 * unless the VF is malicious and is attempting to
			 * flood the host OS with VF2PF पूर्णांकerrupts.
			 */
			क्रम_each_set_bit(i, (स्थिर अचिन्हित दीर्घ *)&vf_mask,
					 (माप(vf_mask) * BITS_PER_BYTE)) अणु
				vf_info = accel_dev->pf.vf_info + i;

				अगर (!__ratelimit(&vf_info->vf2pf_ratelimit)) अणु
					dev_info(&GET_DEV(accel_dev),
						 "Too many ints from VF%d\n",
						  vf_info->vf_nr + 1);
					जारी;
				पूर्ण

				/* Tasklet will re-enable पूर्णांकs from this VF */
				tasklet_hi_schedule(&vf_info->vf2pf_bh_tasklet);
				irq_handled = true;
			पूर्ण

			अगर (irq_handled)
				वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	dev_dbg(&GET_DEV(accel_dev), "qat_dev%d spurious AE interrupt\n",
		accel_dev->accel_id);

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक adf_request_irqs(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_dev_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा msix_entry *msixe = pci_dev_info->msix_entries.entries;
	काष्ठा adf_etr_data *etr_data = accel_dev->transport;
	पूर्णांक ret, i = 0;
	अक्षर *name;

	/* Request msix irq क्रम all banks unless SR-IOV enabled */
	अगर (!accel_dev->pf.vf_info) अणु
		क्रम (i = 0; i < hw_data->num_banks; i++) अणु
			काष्ठा adf_etr_bank_data *bank = &etr_data->banks[i];
			अचिन्हित पूर्णांक cpu, cpus = num_online_cpus();

			name = *(pci_dev_info->msix_entries.names + i);
			snम_लिखो(name, ADF_MAX_MSIX_VECTOR_NAME,
				 "qat%d-bundle%d", accel_dev->accel_id, i);
			ret = request_irq(msixe[i].vector,
					  adf_msix_isr_bundle, 0, name, bank);
			अगर (ret) अणु
				dev_err(&GET_DEV(accel_dev),
					"failed to enable irq %d for %s\n",
					msixe[i].vector, name);
				वापस ret;
			पूर्ण

			cpu = ((accel_dev->accel_id * hw_data->num_banks) +
			       i) % cpus;
			irq_set_affinity_hपूर्णांक(msixe[i].vector,
					      get_cpu_mask(cpu));
		पूर्ण
	पूर्ण

	/* Request msix irq क्रम AE */
	name = *(pci_dev_info->msix_entries.names + i);
	snम_लिखो(name, ADF_MAX_MSIX_VECTOR_NAME,
		 "qat%d-ae-cluster", accel_dev->accel_id);
	ret = request_irq(msixe[i].vector, adf_msix_isr_ae, 0, name, accel_dev);
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev),
			"failed to enable irq %d, for %s\n",
			msixe[i].vector, name);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम adf_मुक्त_irqs(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_dev_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा msix_entry *msixe = pci_dev_info->msix_entries.entries;
	काष्ठा adf_etr_data *etr_data = accel_dev->transport;
	पूर्णांक i = 0;

	अगर (pci_dev_info->msix_entries.num_entries > 1) अणु
		क्रम (i = 0; i < hw_data->num_banks; i++) अणु
			irq_set_affinity_hपूर्णांक(msixe[i].vector, शून्य);
			मुक्त_irq(msixe[i].vector, &etr_data->banks[i]);
		पूर्ण
	पूर्ण
	irq_set_affinity_hपूर्णांक(msixe[i].vector, शून्य);
	मुक्त_irq(msixe[i].vector, accel_dev);
पूर्ण

अटल पूर्णांक adf_isr_alloc_msix_entry_table(काष्ठा adf_accel_dev *accel_dev)
अणु
	पूर्णांक i;
	अक्षर **names;
	काष्ठा msix_entry *entries;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 msix_num_entries = 1;

	/* If SR-IOV is disabled (vf_info is शून्य), add entries क्रम each bank */
	अगर (!accel_dev->pf.vf_info)
		msix_num_entries += hw_data->num_banks;

	entries = kसुस्मृति_node(msix_num_entries, माप(*entries),
			       GFP_KERNEL, dev_to_node(&GET_DEV(accel_dev)));
	अगर (!entries)
		वापस -ENOMEM;

	names = kसुस्मृति(msix_num_entries, माप(अक्षर *), GFP_KERNEL);
	अगर (!names) अणु
		kमुक्त(entries);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < msix_num_entries; i++) अणु
		*(names + i) = kzalloc(ADF_MAX_MSIX_VECTOR_NAME, GFP_KERNEL);
		अगर (!(*(names + i)))
			जाओ err;
	पूर्ण
	accel_dev->accel_pci_dev.msix_entries.num_entries = msix_num_entries;
	accel_dev->accel_pci_dev.msix_entries.entries = entries;
	accel_dev->accel_pci_dev.msix_entries.names = names;
	वापस 0;
err:
	क्रम (i = 0; i < msix_num_entries; i++)
		kमुक्त(*(names + i));
	kमुक्त(entries);
	kमुक्त(names);
	वापस -ENOMEM;
पूर्ण

अटल व्योम adf_isr_मुक्त_msix_entry_table(काष्ठा adf_accel_dev *accel_dev)
अणु
	अक्षर **names = accel_dev->accel_pci_dev.msix_entries.names;
	पूर्णांक i;

	kमुक्त(accel_dev->accel_pci_dev.msix_entries.entries);
	क्रम (i = 0; i < accel_dev->accel_pci_dev.msix_entries.num_entries; i++)
		kमुक्त(*(names + i));
	kमुक्त(names);
पूर्ण

अटल पूर्णांक adf_setup_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *priv_data = accel_dev->transport;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	पूर्णांक i;

	क्रम (i = 0; i < hw_data->num_banks; i++)
		tasklet_init(&priv_data->banks[i].resp_handler,
			     adf_response_handler,
			     (अचिन्हित दीर्घ)&priv_data->banks[i]);
	वापस 0;
पूर्ण

अटल व्योम adf_cleanup_bh(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *priv_data = accel_dev->transport;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	पूर्णांक i;

	क्रम (i = 0; i < hw_data->num_banks; i++) अणु
		tasklet_disable(&priv_data->banks[i].resp_handler);
		tasklet_समाप्त(&priv_data->banks[i].resp_handler);
	पूर्ण
पूर्ण

/**
 * adf_isr_resource_मुक्त() - Free IRQ क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function मुक्तs पूर्णांकerrupts क्रम acceleration device.
 */
व्योम adf_isr_resource_मुक्त(काष्ठा adf_accel_dev *accel_dev)
अणु
	adf_मुक्त_irqs(accel_dev);
	adf_cleanup_bh(accel_dev);
	adf_disable_msix(&accel_dev->accel_pci_dev);
	adf_isr_मुक्त_msix_entry_table(accel_dev);
पूर्ण
EXPORT_SYMBOL_GPL(adf_isr_resource_मुक्त);

/**
 * adf_isr_resource_alloc() - Allocate IRQ क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function allocates पूर्णांकerrupts क्रम acceleration device.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_isr_resource_alloc(काष्ठा adf_accel_dev *accel_dev)
अणु
	पूर्णांक ret;

	ret = adf_isr_alloc_msix_entry_table(accel_dev);
	अगर (ret)
		जाओ err_out;

	ret = adf_enable_msix(accel_dev);
	अगर (ret)
		जाओ err_मुक्त_msix_table;

	ret = adf_setup_bh(accel_dev);
	अगर (ret)
		जाओ err_disable_msix;

	ret = adf_request_irqs(accel_dev);
	अगर (ret)
		जाओ err_cleanup_bh;

	वापस 0;

err_cleanup_bh:
	adf_cleanup_bh(accel_dev);

err_disable_msix:
	adf_disable_msix(&accel_dev->accel_pci_dev);

err_मुक्त_msix_table:
	adf_isr_मुक्त_msix_entry_table(accel_dev);

err_out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adf_isr_resource_alloc);
