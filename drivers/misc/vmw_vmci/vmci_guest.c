<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "vmci_datagram.h"
#समावेश "vmci_doorbell.h"
#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"

#घोषणा PCI_DEVICE_ID_VMWARE_VMCI	0x0740

#घोषणा VMCI_UTIL_NUM_RESOURCES 1

अटल bool vmci_disable_msi;
module_param_named(disable_msi, vmci_disable_msi, bool, 0);
MODULE_PARM_DESC(disable_msi, "Disable MSI use in driver - (default=0)");

अटल bool vmci_disable_msix;
module_param_named(disable_msix, vmci_disable_msix, bool, 0);
MODULE_PARM_DESC(disable_msix, "Disable MSI-X use in driver - (default=0)");

अटल u32 ctx_update_sub_id = VMCI_INVALID_ID;
अटल u32 vm_context_id = VMCI_INVALID_ID;

काष्ठा vmci_guest_device अणु
	काष्ठा device *dev;	/* PCI device we are attached to */
	व्योम __iomem *iobase;

	bool exclusive_vectors;

	काष्ठा tasklet_काष्ठा datagram_tasklet;
	काष्ठा tasklet_काष्ठा bm_tasklet;

	व्योम *data_buffer;
	व्योम *notअगरication_biपंचांगap;
	dma_addr_t notअगरication_base;
पूर्ण;

अटल bool use_ppn64;

bool vmci_use_ppn64(व्योम)
अणु
	वापस use_ppn64;
पूर्ण

/* vmci_dev singleton device and supporting data*/
काष्ठा pci_dev *vmci_pdev;
अटल काष्ठा vmci_guest_device *vmci_dev_g;
अटल DEFINE_SPINLOCK(vmci_dev_spinlock);

अटल atomic_t vmci_num_guest_devices = ATOMIC_INIT(0);

bool vmci_guest_code_active(व्योम)
अणु
	वापस atomic_पढ़ो(&vmci_num_guest_devices) != 0;
पूर्ण

u32 vmci_get_vm_context_id(व्योम)
अणु
	अगर (vm_context_id == VMCI_INVALID_ID) अणु
		काष्ठा vmci_datagram get_cid_msg;
		get_cid_msg.dst =
		    vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
				     VMCI_GET_CONTEXT_ID);
		get_cid_msg.src = VMCI_ANON_SRC_HANDLE;
		get_cid_msg.payload_size = 0;
		vm_context_id = vmci_send_datagram(&get_cid_msg);
	पूर्ण
	वापस vm_context_id;
पूर्ण

/*
 * VM to hypervisor call mechanism. We use the standard VMware naming
 * convention since shared code is calling this function as well.
 */
पूर्णांक vmci_send_datagram(काष्ठा vmci_datagram *dg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	/* Check args. */
	अगर (dg == शून्य)
		वापस VMCI_ERROR_INVALID_ARGS;

	/*
	 * Need to acquire spinlock on the device because the datagram
	 * data may be spपढ़ो over multiple pages and the monitor may
	 * पूर्णांकerleave device user rpc calls from multiple
	 * VCPUs. Acquiring the spinlock precludes that
	 * possibility. Disabling पूर्णांकerrupts to aव्योम incoming
	 * datagrams during a "rep out" and possibly landing up in
	 * this function.
	 */
	spin_lock_irqsave(&vmci_dev_spinlock, flags);

	अगर (vmci_dev_g) अणु
		ioग_लिखो8_rep(vmci_dev_g->iobase + VMCI_DATA_OUT_ADDR,
			     dg, VMCI_DG_SIZE(dg));
		result = ioपढ़ो32(vmci_dev_g->iobase + VMCI_RESULT_LOW_ADDR);
	पूर्ण अन्यथा अणु
		result = VMCI_ERROR_UNAVAILABLE;
	पूर्ण

	spin_unlock_irqrestore(&vmci_dev_spinlock, flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_send_datagram);

/*
 * Gets called with the new context id अगर updated or resumed.
 * Context id.
 */
अटल व्योम vmci_guest_cid_update(u32 sub_id,
				  स्थिर काष्ठा vmci_event_data *event_data,
				  व्योम *client_data)
अणु
	स्थिर काष्ठा vmci_event_payld_ctx *ev_payload =
				vmci_event_data_स्थिर_payload(event_data);

	अगर (sub_id != ctx_update_sub_id) अणु
		pr_devel("Invalid subscriber (ID=0x%x)\n", sub_id);
		वापस;
	पूर्ण

	अगर (!event_data || ev_payload->context_id == VMCI_INVALID_ID) अणु
		pr_devel("Invalid event data\n");
		वापस;
	पूर्ण

	pr_devel("Updating context from (ID=0x%x) to (ID=0x%x) on event (type=%d)\n",
		 vm_context_id, ev_payload->context_id, event_data->event);

	vm_context_id = ev_payload->context_id;
पूर्ण

/*
 * Verअगरy that the host supports the hypercalls we need. If it करोes not,
 * try to find fallback hypercalls and use those instead.  Returns
 * true अगर required hypercalls (or fallback hypercalls) are
 * supported by the host, false otherwise.
 */
अटल पूर्णांक vmci_check_host_caps(काष्ठा pci_dev *pdev)
अणु
	bool result;
	काष्ठा vmci_resource_query_msg *msg;
	u32 msg_size = माप(काष्ठा vmci_resource_query_hdr) +
				VMCI_UTIL_NUM_RESOURCES * माप(u32);
	काष्ठा vmci_datagram *check_msg;

	check_msg = kzalloc(msg_size, GFP_KERNEL);
	अगर (!check_msg) अणु
		dev_err(&pdev->dev, "%s: Insufficient memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	check_msg->dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					  VMCI_RESOURCES_QUERY);
	check_msg->src = VMCI_ANON_SRC_HANDLE;
	check_msg->payload_size = msg_size - VMCI_DG_HEADERSIZE;
	msg = (काष्ठा vmci_resource_query_msg *)VMCI_DG_PAYLOAD(check_msg);

	msg->num_resources = VMCI_UTIL_NUM_RESOURCES;
	msg->resources[0] = VMCI_GET_CONTEXT_ID;

	/* Checks that hyper calls are supported */
	result = vmci_send_datagram(check_msg) == 0x01;
	kमुक्त(check_msg);

	dev_dbg(&pdev->dev, "%s: Host capability check: %s\n",
		__func__, result ? "PASSED" : "FAILED");

	/* We need the vector. There are no fallbacks. */
	वापस result ? 0 : -ENXIO;
पूर्ण

/*
 * Reads datagrams from the data in port and dispatches them. We
 * always start पढ़ोing datagrams पूर्णांकo only the first page of the
 * datagram buffer. If the datagrams करोn't fit पूर्णांकo one page, we
 * use the maximum datagram buffer size क्रम the reमुख्यder of the
 * invocation. This is a simple heuristic क्रम not penalizing
 * small datagrams.
 *
 * This function assumes that it has exclusive access to the data
 * in port क्रम the duration of the call.
 */
अटल व्योम vmci_dispatch_dgs(अचिन्हित दीर्घ data)
अणु
	काष्ठा vmci_guest_device *vmci_dev = (काष्ठा vmci_guest_device *)data;
	u8 *dg_in_buffer = vmci_dev->data_buffer;
	काष्ठा vmci_datagram *dg;
	माप_प्रकार dg_in_buffer_size = VMCI_MAX_DG_SIZE;
	माप_प्रकार current_dg_in_buffer_size = PAGE_SIZE;
	माप_प्रकार reमुख्यing_bytes;

	BUILD_BUG_ON(VMCI_MAX_DG_SIZE < PAGE_SIZE);

	ioपढ़ो8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
		    vmci_dev->data_buffer, current_dg_in_buffer_size);
	dg = (काष्ठा vmci_datagram *)dg_in_buffer;
	reमुख्यing_bytes = current_dg_in_buffer_size;

	जबतक (dg->dst.resource != VMCI_INVALID_ID ||
	       reमुख्यing_bytes > PAGE_SIZE) अणु
		अचिन्हित dg_in_size;

		/*
		 * When the input buffer spans multiple pages, a datagram can
		 * start on any page boundary in the buffer.
		 */
		अगर (dg->dst.resource == VMCI_INVALID_ID) अणु
			dg = (काष्ठा vmci_datagram *)roundup(
				(uपूर्णांकptr_t)dg + 1, PAGE_SIZE);
			reमुख्यing_bytes =
				(माप_प्रकार)(dg_in_buffer +
					 current_dg_in_buffer_size -
					 (u8 *)dg);
			जारी;
		पूर्ण

		dg_in_size = VMCI_DG_SIZE_ALIGNED(dg);

		अगर (dg_in_size <= dg_in_buffer_size) अणु
			पूर्णांक result;

			/*
			 * If the reमुख्यing bytes in the datagram
			 * buffer करोesn't contain the complete
			 * datagram, we first make sure we have enough
			 * room क्रम it and then we पढ़ो the reminder
			 * of the datagram and possibly any following
			 * datagrams.
			 */
			अगर (dg_in_size > reमुख्यing_bytes) अणु
				अगर (reमुख्यing_bytes !=
				    current_dg_in_buffer_size) अणु

					/*
					 * We move the partial
					 * datagram to the front and
					 * पढ़ो the reminder of the
					 * datagram and possibly
					 * following calls पूर्णांकo the
					 * following bytes.
					 */
					स_हटाओ(dg_in_buffer, dg_in_buffer +
						current_dg_in_buffer_size -
						reमुख्यing_bytes,
						reमुख्यing_bytes);
					dg = (काष्ठा vmci_datagram *)
					    dg_in_buffer;
				पूर्ण

				अगर (current_dg_in_buffer_size !=
				    dg_in_buffer_size)
					current_dg_in_buffer_size =
					    dg_in_buffer_size;

				ioपढ़ो8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer +
						reमुख्यing_bytes,
					current_dg_in_buffer_size -
						reमुख्यing_bytes);
			पूर्ण

			/*
			 * We special हाल event datagrams from the
			 * hypervisor.
			 */
			अगर (dg->src.context == VMCI_HYPERVISOR_CONTEXT_ID &&
			    dg->dst.resource == VMCI_EVENT_HANDLER) अणु
				result = vmci_event_dispatch(dg);
			पूर्ण अन्यथा अणु
				result = vmci_datagram_invoke_guest_handler(dg);
			पूर्ण
			अगर (result < VMCI_SUCCESS)
				dev_dbg(vmci_dev->dev,
					"Datagram with resource (ID=0x%x) failed (err=%d)\n",
					 dg->dst.resource, result);

			/* On to the next datagram. */
			dg = (काष्ठा vmci_datagram *)((u8 *)dg +
						      dg_in_size);
		पूर्ण अन्यथा अणु
			माप_प्रकार bytes_to_skip;

			/*
			 * Datagram करोesn't fit in datagram buffer of maximal
			 * size. We drop it.
			 */
			dev_dbg(vmci_dev->dev,
				"Failed to receive datagram (size=%u bytes)\n",
				 dg_in_size);

			bytes_to_skip = dg_in_size - reमुख्यing_bytes;
			अगर (current_dg_in_buffer_size != dg_in_buffer_size)
				current_dg_in_buffer_size = dg_in_buffer_size;

			क्रम (;;) अणु
				ioपढ़ो8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer,
					current_dg_in_buffer_size);
				अगर (bytes_to_skip <= current_dg_in_buffer_size)
					अवरोध;

				bytes_to_skip -= current_dg_in_buffer_size;
			पूर्ण
			dg = (काष्ठा vmci_datagram *)(dg_in_buffer +
						      bytes_to_skip);
		पूर्ण

		reमुख्यing_bytes =
		    (माप_प्रकार) (dg_in_buffer + current_dg_in_buffer_size -
			      (u8 *)dg);

		अगर (reमुख्यing_bytes < VMCI_DG_HEADERSIZE) अणु
			/* Get the next batch of datagrams. */

			ioपढ़ो8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
				    vmci_dev->data_buffer,
				    current_dg_in_buffer_size);
			dg = (काष्ठा vmci_datagram *)dg_in_buffer;
			reमुख्यing_bytes = current_dg_in_buffer_size;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Scans the notअगरication biपंचांगap क्रम उठाओd flags, clears them
 * and handles the notअगरications.
 */
अटल व्योम vmci_process_biपंचांगap(अचिन्हित दीर्घ data)
अणु
	काष्ठा vmci_guest_device *dev = (काष्ठा vmci_guest_device *)data;

	अगर (!dev->notअगरication_biपंचांगap) अणु
		dev_dbg(dev->dev, "No bitmap present in %s\n", __func__);
		वापस;
	पूर्ण

	vmci_dbell_scan_notअगरication_entries(dev->notअगरication_biपंचांगap);
पूर्ण

/*
 * Interrupt handler क्रम legacy or MSI पूर्णांकerrupt, or क्रम first MSI-X
 * पूर्णांकerrupt (vector VMCI_INTR_DATAGRAM).
 */
अटल irqवापस_t vmci_पूर्णांकerrupt(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा vmci_guest_device *dev = _dev;

	/*
	 * If we are using MSI-X with exclusive vectors then we simply schedule
	 * the datagram tasklet, since we know the पूर्णांकerrupt was meant क्रम us.
	 * Otherwise we must पढ़ो the ICR to determine what to करो.
	 */

	अगर (dev->exclusive_vectors) अणु
		tasklet_schedule(&dev->datagram_tasklet);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक icr;

		/* Acknowledge पूर्णांकerrupt and determine what needs करोing. */
		icr = ioपढ़ो32(dev->iobase + VMCI_ICR_ADDR);
		अगर (icr == 0 || icr == ~0)
			वापस IRQ_NONE;

		अगर (icr & VMCI_ICR_DATAGRAM) अणु
			tasklet_schedule(&dev->datagram_tasklet);
			icr &= ~VMCI_ICR_DATAGRAM;
		पूर्ण

		अगर (icr & VMCI_ICR_NOTIFICATION) अणु
			tasklet_schedule(&dev->bm_tasklet);
			icr &= ~VMCI_ICR_NOTIFICATION;
		पूर्ण

		अगर (icr != 0)
			dev_warn(dev->dev,
				 "Ignoring unknown interrupt cause (%d)\n",
				 icr);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Interrupt handler क्रम MSI-X पूर्णांकerrupt vector VMCI_INTR_NOTIFICATION,
 * which is क्रम the notअगरication biपंचांगap.  Will only get called अगर we are
 * using MSI-X with exclusive vectors.
 */
अटल irqवापस_t vmci_पूर्णांकerrupt_bm(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा vmci_guest_device *dev = _dev;

	/* For MSI-X we can just assume it was meant क्रम us. */
	tasklet_schedule(&dev->bm_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Most of the initialization at module load समय is करोne here.
 */
अटल पूर्णांक vmci_guest_probe_device(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा vmci_guest_device *vmci_dev;
	व्योम __iomem *iobase;
	अचिन्हित पूर्णांक capabilities;
	अचिन्हित पूर्णांक caps_in_use;
	अचिन्हित दीर्घ cmd;
	पूर्णांक vmci_err;
	पूर्णांक error;

	dev_dbg(&pdev->dev, "Probing for vmci/PCI guest device\n");

	error = pcim_enable_device(pdev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to enable VMCI device: %d\n", error);
		वापस error;
	पूर्ण

	error = pcim_iomap_regions(pdev, 1 << 0, KBUILD_MODNAME);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to reserve/map IO regions\n");
		वापस error;
	पूर्ण

	iobase = pcim_iomap_table(pdev)[0];

	dev_info(&pdev->dev, "Found VMCI PCI device at %#lx, irq %u\n",
		 (अचिन्हित दीर्घ)iobase, pdev->irq);

	vmci_dev = devm_kzalloc(&pdev->dev, माप(*vmci_dev), GFP_KERNEL);
	अगर (!vmci_dev) अणु
		dev_err(&pdev->dev,
			"Can't allocate memory for VMCI device\n");
		वापस -ENOMEM;
	पूर्ण

	vmci_dev->dev = &pdev->dev;
	vmci_dev->exclusive_vectors = false;
	vmci_dev->iobase = iobase;

	tasklet_init(&vmci_dev->datagram_tasklet,
		     vmci_dispatch_dgs, (अचिन्हित दीर्घ)vmci_dev);
	tasklet_init(&vmci_dev->bm_tasklet,
		     vmci_process_biपंचांगap, (अचिन्हित दीर्घ)vmci_dev);

	vmci_dev->data_buffer = vदो_स्मृति(VMCI_MAX_DG_SIZE);
	अगर (!vmci_dev->data_buffer) अणु
		dev_err(&pdev->dev,
			"Can't allocate memory for datagram buffer\n");
		वापस -ENOMEM;
	पूर्ण

	pci_set_master(pdev);	/* To enable queue_pair functionality. */

	/*
	 * Verअगरy that the VMCI Device supports the capabilities that
	 * we need. If the device is missing capabilities that we would
	 * like to use, check क्रम fallback capabilities and use those
	 * instead (so we can run a new VM on old hosts). Fail the load अगर
	 * a required capability is missing and there is no fallback.
	 *
	 * Right now, we need datagrams. There are no fallbacks.
	 */
	capabilities = ioपढ़ो32(vmci_dev->iobase + VMCI_CAPS_ADDR);
	अगर (!(capabilities & VMCI_CAPS_DATAGRAM)) अणु
		dev_err(&pdev->dev, "Device does not support datagrams\n");
		error = -ENXIO;
		जाओ err_मुक्त_data_buffer;
	पूर्ण
	caps_in_use = VMCI_CAPS_DATAGRAM;

	/*
	 * Use 64-bit PPNs अगर the device supports.
	 *
	 * There is no check क्रम the वापस value of dma_set_mask_and_coherent
	 * since this driver can handle the शेष mask values अगर
	 * dma_set_mask_and_coherent fails.
	 */
	अगर (capabilities & VMCI_CAPS_PPN64) अणु
		dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
		use_ppn64 = true;
		caps_in_use |= VMCI_CAPS_PPN64;
	पूर्ण अन्यथा अणु
		dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(44));
		use_ppn64 = false;
	पूर्ण

	/*
	 * If the hardware supports notअगरications, we will use that as
	 * well.
	 */
	अगर (capabilities & VMCI_CAPS_NOTIFICATIONS) अणु
		vmci_dev->notअगरication_biपंचांगap = dma_alloc_coherent(
			&pdev->dev, PAGE_SIZE, &vmci_dev->notअगरication_base,
			GFP_KERNEL);
		अगर (!vmci_dev->notअगरication_biपंचांगap) अणु
			dev_warn(&pdev->dev,
				 "Unable to allocate notification bitmap\n");
		पूर्ण अन्यथा अणु
			स_रखो(vmci_dev->notअगरication_biपंचांगap, 0, PAGE_SIZE);
			caps_in_use |= VMCI_CAPS_NOTIFICATIONS;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "Using capabilities 0x%x\n", caps_in_use);

	/* Let the host know which capabilities we पूर्णांकend to use. */
	ioग_लिखो32(caps_in_use, vmci_dev->iobase + VMCI_CAPS_ADDR);

	/* Set up global device so that we can start sending datagrams */
	spin_lock_irq(&vmci_dev_spinlock);
	vmci_dev_g = vmci_dev;
	vmci_pdev = pdev;
	spin_unlock_irq(&vmci_dev_spinlock);

	/*
	 * Register notअगरication biपंचांगap with device अगर that capability is
	 * used.
	 */
	अगर (caps_in_use & VMCI_CAPS_NOTIFICATIONS) अणु
		अचिन्हित दीर्घ biपंचांगap_ppn =
			vmci_dev->notअगरication_base >> PAGE_SHIFT;
		अगर (!vmci_dbell_रेजिस्टर_notअगरication_biपंचांगap(biपंचांगap_ppn)) अणु
			dev_warn(&pdev->dev,
				 "VMCI device unable to register notification bitmap with PPN 0x%lx\n",
				 biपंचांगap_ppn);
			error = -ENXIO;
			जाओ err_हटाओ_vmci_dev_g;
		पूर्ण
	पूर्ण

	/* Check host capabilities. */
	error = vmci_check_host_caps(pdev);
	अगर (error)
		जाओ err_हटाओ_biपंचांगap;

	/* Enable device. */

	/*
	 * We subscribe to the VMCI_EVENT_CTX_ID_UPDATE here so we can
	 * update the पूर्णांकernal context id when needed.
	 */
	vmci_err = vmci_event_subscribe(VMCI_EVENT_CTX_ID_UPDATE,
					vmci_guest_cid_update, शून्य,
					&ctx_update_sub_id);
	अगर (vmci_err < VMCI_SUCCESS)
		dev_warn(&pdev->dev,
			 "Failed to subscribe to event (type=%d): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, vmci_err);

	/*
	 * Enable पूर्णांकerrupts.  Try MSI-X first, then MSI, and then fallback on
	 * legacy पूर्णांकerrupts.
	 */
	error = pci_alloc_irq_vectors(pdev, VMCI_MAX_INTRS, VMCI_MAX_INTRS,
			PCI_IRQ_MSIX);
	अगर (error < 0) अणु
		error = pci_alloc_irq_vectors(pdev, 1, 1,
				PCI_IRQ_MSIX | PCI_IRQ_MSI | PCI_IRQ_LEGACY);
		अगर (error < 0)
			जाओ err_हटाओ_biपंचांगap;
	पूर्ण अन्यथा अणु
		vmci_dev->exclusive_vectors = true;
	पूर्ण

	/*
	 * Request IRQ क्रम legacy or MSI पूर्णांकerrupts, or क्रम first
	 * MSI-X vector.
	 */
	error = request_irq(pci_irq_vector(pdev, 0), vmci_पूर्णांकerrupt,
			    IRQF_SHARED, KBUILD_MODNAME, vmci_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "Irq %u in use: %d\n",
			pci_irq_vector(pdev, 0), error);
		जाओ err_disable_msi;
	पूर्ण

	/*
	 * For MSI-X with exclusive vectors we need to request an
	 * पूर्णांकerrupt क्रम each vector so that we get a separate
	 * पूर्णांकerrupt handler routine.  This allows us to distinguish
	 * between the vectors.
	 */
	अगर (vmci_dev->exclusive_vectors) अणु
		error = request_irq(pci_irq_vector(pdev, 1),
				    vmci_पूर्णांकerrupt_bm, 0, KBUILD_MODNAME,
				    vmci_dev);
		अगर (error) अणु
			dev_err(&pdev->dev,
				"Failed to allocate irq %u: %d\n",
				pci_irq_vector(pdev, 1), error);
			जाओ err_मुक्त_irq;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "Registered device\n");

	atomic_inc(&vmci_num_guest_devices);

	/* Enable specअगरic पूर्णांकerrupt bits. */
	cmd = VMCI_IMR_DATAGRAM;
	अगर (caps_in_use & VMCI_CAPS_NOTIFICATIONS)
		cmd |= VMCI_IMR_NOTIFICATION;
	ioग_लिखो32(cmd, vmci_dev->iobase + VMCI_IMR_ADDR);

	/* Enable पूर्णांकerrupts. */
	ioग_लिखो32(VMCI_CONTROL_INT_ENABLE,
		  vmci_dev->iobase + VMCI_CONTROL_ADDR);

	pci_set_drvdata(pdev, vmci_dev);

	vmci_call_vsock_callback(false);
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(pci_irq_vector(pdev, 0), vmci_dev);
	tasklet_समाप्त(&vmci_dev->datagram_tasklet);
	tasklet_समाप्त(&vmci_dev->bm_tasklet);

err_disable_msi:
	pci_मुक्त_irq_vectors(pdev);

	vmci_err = vmci_event_unsubscribe(ctx_update_sub_id);
	अगर (vmci_err < VMCI_SUCCESS)
		dev_warn(&pdev->dev,
			 "Failed to unsubscribe from event (type=%d) with subscriber (ID=0x%x): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, ctx_update_sub_id, vmci_err);

err_हटाओ_biपंचांगap:
	अगर (vmci_dev->notअगरication_biपंचांगap) अणु
		ioग_लिखो32(VMCI_CONTROL_RESET,
			  vmci_dev->iobase + VMCI_CONTROL_ADDR);
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE,
				  vmci_dev->notअगरication_biपंचांगap,
				  vmci_dev->notअगरication_base);
	पूर्ण

err_हटाओ_vmci_dev_g:
	spin_lock_irq(&vmci_dev_spinlock);
	vmci_pdev = शून्य;
	vmci_dev_g = शून्य;
	spin_unlock_irq(&vmci_dev_spinlock);

err_मुक्त_data_buffer:
	vमुक्त(vmci_dev->data_buffer);

	/* The rest are managed resources and will be मुक्तd by PCI core */
	वापस error;
पूर्ण

अटल व्योम vmci_guest_हटाओ_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vmci_guest_device *vmci_dev = pci_get_drvdata(pdev);
	पूर्णांक vmci_err;

	dev_dbg(&pdev->dev, "Removing device\n");

	atomic_dec(&vmci_num_guest_devices);

	vmci_qp_guest_endpoपूर्णांकs_निकास();

	vmci_err = vmci_event_unsubscribe(ctx_update_sub_id);
	अगर (vmci_err < VMCI_SUCCESS)
		dev_warn(&pdev->dev,
			 "Failed to unsubscribe from event (type=%d) with subscriber (ID=0x%x): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, ctx_update_sub_id, vmci_err);

	spin_lock_irq(&vmci_dev_spinlock);
	vmci_dev_g = शून्य;
	vmci_pdev = शून्य;
	spin_unlock_irq(&vmci_dev_spinlock);

	dev_dbg(&pdev->dev, "Resetting vmci device\n");
	ioग_लिखो32(VMCI_CONTROL_RESET, vmci_dev->iobase + VMCI_CONTROL_ADDR);

	/*
	 * Free IRQ and then disable MSI/MSI-X as appropriate.  For
	 * MSI-X, we might have multiple vectors, each with their own
	 * IRQ, which we must मुक्त too.
	 */
	अगर (vmci_dev->exclusive_vectors)
		मुक्त_irq(pci_irq_vector(pdev, 1), vmci_dev);
	मुक्त_irq(pci_irq_vector(pdev, 0), vmci_dev);
	pci_मुक्त_irq_vectors(pdev);

	tasklet_समाप्त(&vmci_dev->datagram_tasklet);
	tasklet_समाप्त(&vmci_dev->bm_tasklet);

	अगर (vmci_dev->notअगरication_biपंचांगap) अणु
		/*
		 * The device reset above cleared the biपंचांगap state of the
		 * device, so we can safely मुक्त it here.
		 */

		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE,
				  vmci_dev->notअगरication_biपंचांगap,
				  vmci_dev->notअगरication_base);
	पूर्ण

	vमुक्त(vmci_dev->data_buffer);

	/* The rest are managed resources and will be मुक्तd by PCI core */
पूर्ण

अटल स्थिर काष्ठा pci_device_id vmci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VMWARE, PCI_DEVICE_ID_VMWARE_VMCI), पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, vmci_ids);

अटल काष्ठा pci_driver vmci_guest_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= vmci_ids,
	.probe		= vmci_guest_probe_device,
	.हटाओ		= vmci_guest_हटाओ_device,
पूर्ण;

पूर्णांक __init vmci_guest_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&vmci_guest_driver);
पूर्ण

व्योम __निकास vmci_guest_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vmci_guest_driver);
पूर्ण
