<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend Operations - respond to PCI requests from Frontend
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <xen/events.h>
#समावेश <linux/sched.h>
#समावेश "pciback.h"

अटल irqवापस_t xen_pcibk_guest_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* Ensure a device is has the fake IRQ handler "turned on/off" and is
 * पढ़ोy to be exported. This MUST be run after xen_pcibk_reset_device
 * which करोes the actual PCI device enable/disable.
 */
अटल व्योम xen_pcibk_control_isr(काष्ठा pci_dev *dev, पूर्णांक reset)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक rc;
	पूर्णांक enable = 0;

	dev_data = pci_get_drvdata(dev);
	अगर (!dev_data)
		वापस;

	/* We करोn't deal with bridges */
	अगर (dev->hdr_type != PCI_HEADER_TYPE_NORMAL)
		वापस;

	अगर (reset) अणु
		dev_data->enable_पूर्णांकx = 0;
		dev_data->ack_पूर्णांकr = 0;
	पूर्ण
	enable =  dev_data->enable_पूर्णांकx;

	/* Asked to disable, but ISR isn't runnig */
	अगर (!enable && !dev_data->isr_on)
		वापस;

	/* Squirrel away the IRQs in the dev_data. We need this
	 * b/c when device transitions to MSI, the dev->irq is
	 * overwritten with the MSI vector.
	 */
	अगर (enable)
		dev_data->irq = dev->irq;

	/*
	 * SR-IOV devices in all use MSI-X and have no legacy
	 * पूर्णांकerrupts, so inhibit creating a fake IRQ handler क्रम them.
	 */
	अगर (dev_data->irq == 0)
		जाओ out;

	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s-> %s\n",
		dev_data->irq_name,
		dev_data->irq,
		pci_is_enabled(dev) ? "on" : "off",
		dev->msi_enabled ? "MSI" : "",
		dev->msix_enabled ? "MSI/X" : "",
		dev_data->isr_on ? "enable" : "disable",
		enable ? "enable" : "disable");

	अगर (enable) अणु
		/*
		 * The MSI or MSI-X should not have an IRQ handler. Otherwise
		 * अगर the guest terminates we BUG_ON in मुक्त_msi_irqs.
		 */
		अगर (dev->msi_enabled || dev->msix_enabled)
			जाओ out;

		rc = request_irq(dev_data->irq,
				xen_pcibk_guest_पूर्णांकerrupt, IRQF_SHARED,
				dev_data->irq_name, dev);
		अगर (rc) अणु
			dev_err(&dev->dev, "%s: failed to install fake IRQ " \
				"handler for IRQ %d! (rc:%d)\n",
				dev_data->irq_name, dev_data->irq, rc);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(dev_data->irq, dev);
		dev_data->irq = 0;
	पूर्ण
	dev_data->isr_on = enable;
	dev_data->ack_पूर्णांकr = enable;
out:
	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s\n",
		dev_data->irq_name,
		dev_data->irq,
		pci_is_enabled(dev) ? "on" : "off",
		dev->msi_enabled ? "MSI" : "",
		dev->msix_enabled ? "MSI/X" : "",
		enable ? (dev_data->isr_on ? "enabled" : "failed to enable") :
			(dev_data->isr_on ? "failed to disable" : "disabled"));
पूर्ण

/* Ensure a device is "turned off" and पढ़ोy to be exported.
 * (Also see xen_pcibk_config_reset to ensure भव configuration space is
 * पढ़ोy to be re-exported)
 */
व्योम xen_pcibk_reset_device(काष्ठा pci_dev *dev)
अणु
	u16 cmd;

	xen_pcibk_control_isr(dev, 1 /* reset device */);

	/* Disable devices (but not bridges) */
	अगर (dev->hdr_type == PCI_HEADER_TYPE_NORMAL) अणु
#अगर_घोषित CONFIG_PCI_MSI
		/* The guest could have been abruptly समाप्तed without
		 * disabling MSI/MSI-X पूर्णांकerrupts.*/
		अगर (dev->msix_enabled)
			pci_disable_msix(dev);
		अगर (dev->msi_enabled)
			pci_disable_msi(dev);
#पूर्ण_अगर
		अगर (pci_is_enabled(dev))
			pci_disable_device(dev);

		dev->is_busmaster = 0;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		अगर (cmd & (PCI_COMMAND_INVALIDATE)) अणु
			cmd &= ~(PCI_COMMAND_INVALIDATE);
			pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);

			dev->is_busmaster = 0;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल
पूर्णांक xen_pcibk_enable_msi(काष्ठा xen_pcibk_device *pdev,
			 काष्ठा pci_dev *dev, काष्ठा xen_pci_op *op)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक status;

	अगर (dev->msi_enabled)
		status = -EALREADY;
	अन्यथा अगर (dev->msix_enabled)
		status = -ENXIO;
	अन्यथा
		status = pci_enable_msi(dev);

	अगर (status) अणु
		dev_warn_ratelimited(&dev->dev, "error enabling MSI for guest %u: err %d\n",
				     pdev->xdev->otherend_id, status);
		op->value = 0;
		वापस XEN_PCI_ERR_op_failed;
	पूर्ण

	/* The value the guest needs is actually the IDT vector, not the
	 * the local करोमुख्य's IRQ number. */

	op->value = dev->irq ? xen_pirq_from_irq(dev->irq) : 0;

	dev_dbg(&dev->dev, "MSI: %d\n", op->value);

	dev_data = pci_get_drvdata(dev);
	अगर (dev_data)
		dev_data->ack_पूर्णांकr = 0;

	वापस 0;
पूर्ण

अटल
पूर्णांक xen_pcibk_disable_msi(काष्ठा xen_pcibk_device *pdev,
			  काष्ठा pci_dev *dev, काष्ठा xen_pci_op *op)
अणु
	अगर (dev->msi_enabled) अणु
		काष्ठा xen_pcibk_dev_data *dev_data;

		pci_disable_msi(dev);

		dev_data = pci_get_drvdata(dev);
		अगर (dev_data)
			dev_data->ack_पूर्णांकr = 1;
	पूर्ण
	op->value = dev->irq ? xen_pirq_from_irq(dev->irq) : 0;

	dev_dbg(&dev->dev, "MSI: %d\n", op->value);

	वापस 0;
पूर्ण

अटल
पूर्णांक xen_pcibk_enable_msix(काष्ठा xen_pcibk_device *pdev,
			  काष्ठा pci_dev *dev, काष्ठा xen_pci_op *op)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data;
	पूर्णांक i, result;
	काष्ठा msix_entry *entries;
	u16 cmd;

	dev_dbg(&dev->dev, "enable MSI-X\n");

	अगर (op->value > SH_INFO_MAX_VEC)
		वापस -EINVAL;

	अगर (dev->msix_enabled)
		वापस -EALREADY;

	/*
	 * PCI_COMMAND_MEMORY must be enabled, otherwise we may not be able
	 * to access the BARs where the MSI-X entries reside.
	 * But VF devices are unique in which the PF needs to be checked.
	 */
	pci_पढ़ो_config_word(pci_physfn(dev), PCI_COMMAND, &cmd);
	अगर (dev->msi_enabled || !(cmd & PCI_COMMAND_MEMORY))
		वापस -ENXIO;

	entries = kदो_स्मृति_array(op->value, माप(*entries), GFP_KERNEL);
	अगर (entries == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < op->value; i++) अणु
		entries[i].entry = op->msix_entries[i].entry;
		entries[i].vector = op->msix_entries[i].vector;
	पूर्ण

	result = pci_enable_msix_exact(dev, entries, op->value);
	अगर (result == 0) अणु
		क्रम (i = 0; i < op->value; i++) अणु
			op->msix_entries[i].entry = entries[i].entry;
			अगर (entries[i].vector) अणु
				op->msix_entries[i].vector =
					xen_pirq_from_irq(entries[i].vector);
				dev_dbg(&dev->dev, "MSI-X[%d]: %d\n", i,
					op->msix_entries[i].vector);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		dev_warn_ratelimited(&dev->dev, "error enabling MSI-X for guest %u: err %d!\n",
				     pdev->xdev->otherend_id, result);
	kमुक्त(entries);

	op->value = result;
	dev_data = pci_get_drvdata(dev);
	अगर (dev_data)
		dev_data->ack_पूर्णांकr = 0;

	वापस result > 0 ? 0 : result;
पूर्ण

अटल
पूर्णांक xen_pcibk_disable_msix(काष्ठा xen_pcibk_device *pdev,
			   काष्ठा pci_dev *dev, काष्ठा xen_pci_op *op)
अणु
	अगर (dev->msix_enabled) अणु
		काष्ठा xen_pcibk_dev_data *dev_data;

		pci_disable_msix(dev);

		dev_data = pci_get_drvdata(dev);
		अगर (dev_data)
			dev_data->ack_पूर्णांकr = 1;
	पूर्ण
	/*
	 * SR-IOV devices (which करोn't have any legacy IRQ) have
	 * an undefined IRQ value of zero.
	 */
	op->value = dev->irq ? xen_pirq_from_irq(dev->irq) : 0;

	dev_dbg(&dev->dev, "MSI-X: %d\n", op->value);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool xen_pcibk_test_op_pending(काष्ठा xen_pcibk_device *pdev)
अणु
	वापस test_bit(_XEN_PCIF_active,
			(अचिन्हित दीर्घ *)&pdev->sh_info->flags) &&
	       !test_and_set_bit(_PDEVF_op_active, &pdev->flags);
पूर्ण

/*
* Now the same evtchn is used क्रम both pcअगरront conf_पढ़ो_ग_लिखो request
* as well as pcie aer front end ack. We use a new work_queue to schedule
* xen_pcibk conf_पढ़ो_ग_लिखो service क्रम aव्योमing confict with aer_core
* करो_recovery job which also use the प्रणाली शेष work_queue
*/
अटल व्योम xen_pcibk_test_and_schedule_op(काष्ठा xen_pcibk_device *pdev)
अणु
	bool eoi = true;

	/* Check that frontend is requesting an operation and that we are not
	 * alपढ़ोy processing a request */
	अगर (xen_pcibk_test_op_pending(pdev)) अणु
		schedule_work(&pdev->op_work);
		eoi = false;
	पूर्ण
	/*_XEN_PCIB_active should have been cleared by pcअगरront. And also make
	sure xen_pcibk is रुकोing क्रम ack by checking _PCIB_op_pending*/
	अगर (!test_bit(_XEN_PCIB_active, (अचिन्हित दीर्घ *)&pdev->sh_info->flags)
	    && test_bit(_PCIB_op_pending, &pdev->flags)) अणु
		wake_up(&xen_pcibk_aer_रुको_queue);
		eoi = false;
	पूर्ण

	/* EOI अगर there was nothing to करो. */
	अगर (eoi)
		xen_pcibk_lateeoi(pdev, XEN_EOI_FLAG_SPURIOUS);
पूर्ण

/* Perक्रमming the configuration space पढ़ोs/ग_लिखोs must not be करोne in atomic
 * context because some of the pci_* functions can sleep (mostly due to ACPI
 * use of semaphores). This function is पूर्णांकended to be called from a work
 * queue in process context taking a काष्ठा xen_pcibk_device as a parameter */

अटल व्योम xen_pcibk_करो_one_op(काष्ठा xen_pcibk_device *pdev)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा xen_pcibk_dev_data *dev_data = शून्य;
	काष्ठा xen_pci_op *op = &pdev->op;
	पूर्णांक test_पूर्णांकx = 0;
#अगर_घोषित CONFIG_PCI_MSI
	अचिन्हित पूर्णांक nr = 0;
#पूर्ण_अगर

	*op = pdev->sh_info->op;
	barrier();
	dev = xen_pcibk_get_pci_dev(pdev, op->करोमुख्य, op->bus, op->devfn);

	अगर (dev == शून्य)
		op->err = XEN_PCI_ERR_dev_not_found;
	अन्यथा अणु
		dev_data = pci_get_drvdata(dev);
		अगर (dev_data)
			test_पूर्णांकx = dev_data->enable_पूर्णांकx;
		चयन (op->cmd) अणु
		हाल XEN_PCI_OP_conf_पढ़ो:
			op->err = xen_pcibk_config_पढ़ो(dev,
				  op->offset, op->size, &op->value);
			अवरोध;
		हाल XEN_PCI_OP_conf_ग_लिखो:
			op->err = xen_pcibk_config_ग_लिखो(dev,
				  op->offset, op->size,	op->value);
			अवरोध;
#अगर_घोषित CONFIG_PCI_MSI
		हाल XEN_PCI_OP_enable_msi:
			op->err = xen_pcibk_enable_msi(pdev, dev, op);
			अवरोध;
		हाल XEN_PCI_OP_disable_msi:
			op->err = xen_pcibk_disable_msi(pdev, dev, op);
			अवरोध;
		हाल XEN_PCI_OP_enable_msix:
			nr = op->value;
			op->err = xen_pcibk_enable_msix(pdev, dev, op);
			अवरोध;
		हाल XEN_PCI_OP_disable_msix:
			op->err = xen_pcibk_disable_msix(pdev, dev, op);
			अवरोध;
#पूर्ण_अगर
		शेष:
			op->err = XEN_PCI_ERR_not_implemented;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!op->err && dev && dev_data) अणु
		/* Transition detected */
		अगर ((dev_data->enable_पूर्णांकx != test_पूर्णांकx))
			xen_pcibk_control_isr(dev, 0 /* no reset */);
	पूर्ण
	pdev->sh_info->op.err = op->err;
	pdev->sh_info->op.value = op->value;
#अगर_घोषित CONFIG_PCI_MSI
	अगर (op->cmd == XEN_PCI_OP_enable_msix && op->err == 0) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < nr; i++)
			pdev->sh_info->op.msix_entries[i].vector =
				op->msix_entries[i].vector;
	पूर्ण
#पूर्ण_अगर
	/* Tell the driver करोमुख्य that we're करोne. */
	wmb();
	clear_bit(_XEN_PCIF_active, (अचिन्हित दीर्घ *)&pdev->sh_info->flags);
	notअगरy_remote_via_irq(pdev->evtchn_irq);

	/* Mark that we're करोne. */
	smp_mb__beक्रमe_atomic(); /* /after/ clearing PCIF_active */
	clear_bit(_PDEVF_op_active, &pdev->flags);
	smp_mb__after_atomic(); /* /beक्रमe/ final check क्रम work */
पूर्ण

व्योम xen_pcibk_करो_op(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा xen_pcibk_device *pdev =
		container_of(data, काष्ठा xen_pcibk_device, op_work);

	करो अणु
		xen_pcibk_करो_one_op(pdev);
	पूर्ण जबतक (xen_pcibk_test_op_pending(pdev));

	xen_pcibk_lateeoi(pdev, 0);
पूर्ण

irqवापस_t xen_pcibk_handle_event(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xen_pcibk_device *pdev = dev_id;
	bool eoi;

	/* IRQs might come in beक्रमe pdev->evtchn_irq is written. */
	अगर (unlikely(pdev->evtchn_irq != irq))
		pdev->evtchn_irq = irq;

	eoi = test_and_set_bit(_EOI_pending, &pdev->flags);
	WARN(eoi, "IRQ while EOI pending\n");

	xen_pcibk_test_and_schedule_op(pdev);

	वापस IRQ_HANDLED;
पूर्ण
अटल irqवापस_t xen_pcibk_guest_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_dev *dev = (काष्ठा pci_dev *)dev_id;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	अगर (dev_data->isr_on && dev_data->ack_पूर्णांकr) अणु
		dev_data->handled++;
		अगर ((dev_data->handled % 1000) == 0) अणु
			अगर (xen_test_irq_shared(irq)) अणु
				dev_info(&dev->dev, "%s IRQ line is not shared "
					"with other domains. Turning ISR off\n",
					 dev_data->irq_name);
				dev_data->ack_पूर्णांकr = 0;
			पूर्ण
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण
