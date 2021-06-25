<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/vgaarb.h>
#समावेश <linux/nospec.h>
#समावेश <linux/sched/mm.h>

#समावेश "vfio_pci_private.h"

#घोषणा DRIVER_VERSION  "0.2"
#घोषणा DRIVER_AUTHOR   "Alex Williamson <alex.williamson@redhat.com>"
#घोषणा DRIVER_DESC     "VFIO PCI - User Level meta-driver"

अटल अक्षर ids[1024] __initdata;
module_param_string(ids, ids, माप(ids), 0);
MODULE_PARM_DESC(ids, "Initial PCI IDs to add to the vfio driver, format is \"vendor:device[:subvendor[:subdevice[:class[:class_mask]]]]\" and multiple comma separated entries can be specified");

अटल bool noपूर्णांकxmask;
module_param_named(noपूर्णांकxmask, noपूर्णांकxmask, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(noपूर्णांकxmask,
		  "Disable support for PCI 2.3 style INTx masking.  If this resolves problems for specific devices, report lspci -vvvxxx to linux-pci@vger.kernel.org so the device can be fixed automatically via the broken_intx_masking flag.");

#अगर_घोषित CONFIG_VFIO_PCI_VGA
अटल bool disable_vga;
module_param(disable_vga, bool, S_IRUGO);
MODULE_PARM_DESC(disable_vga, "Disable VGA resource access through vfio-pci");
#पूर्ण_अगर

अटल bool disable_idle_d3;
module_param(disable_idle_d3, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(disable_idle_d3,
		 "Disable using the PCI D3 low power state for idle, unused devices");

अटल bool enable_sriov;
#अगर_घोषित CONFIG_PCI_IOV
module_param(enable_sriov, bool, 0644);
MODULE_PARM_DESC(enable_sriov, "Enable support for SR-IOV configuration.  Enabling SR-IOV on a PF typically requires support of the userspace PF driver, enabling VFs without such support may result in non-functional VFs or PF.");
#पूर्ण_अगर

अटल bool disable_denylist;
module_param(disable_denylist, bool, 0444);
MODULE_PARM_DESC(disable_denylist, "Disable use of device denylist. Disabling the denylist allows binding to devices with known errata that may lead to exploitable stability or security issues when accessed by untrusted users.");

अटल अंतरभूत bool vfio_vga_disabled(व्योम)
अणु
#अगर_घोषित CONFIG_VFIO_PCI_VGA
	वापस disable_vga;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल bool vfio_pci_dev_in_denylist(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->venकरोr) अणु
	हाल PCI_VENDOR_ID_INTEL:
		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX:
		हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX_VF:
		हाल PCI_DEVICE_ID_INTEL_QAT_C62X:
		हाल PCI_DEVICE_ID_INTEL_QAT_C62X_VF:
		हाल PCI_DEVICE_ID_INTEL_QAT_DH895XCC:
		हाल PCI_DEVICE_ID_INTEL_QAT_DH895XCC_VF:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool vfio_pci_is_denylisted(काष्ठा pci_dev *pdev)
अणु
	अगर (!vfio_pci_dev_in_denylist(pdev))
		वापस false;

	अगर (disable_denylist) अणु
		pci_warn(pdev,
			 "device denylist disabled - allowing device %04x:%04x.\n",
			 pdev->venकरोr, pdev->device);
		वापस false;
	पूर्ण

	pci_warn(pdev, "%04x:%04x exists in vfio-pci device denylist, driver probing disallowed.\n",
		 pdev->venकरोr, pdev->device);

	वापस true;
पूर्ण

/*
 * Our VGA arbiter participation is limited since we करोn't know anything
 * about the device itself.  However, अगर the device is the only VGA device
 * करोwnstream of a bridge and VFIO VGA support is disabled, then we can
 * safely वापस legacy VGA IO and memory as not decoded since the user
 * has no way to get to it and routing can be disabled बाह्यally at the
 * bridge.
 */
अटल अचिन्हित पूर्णांक vfio_pci_set_vga_decode(व्योम *opaque, bool single_vga)
अणु
	काष्ठा vfio_pci_device *vdev = opaque;
	काष्ठा pci_dev *पंचांगp = शून्य, *pdev = vdev->pdev;
	अचिन्हित अक्षर max_busnr;
	अचिन्हित पूर्णांक decodes;

	अगर (single_vga || !vfio_vga_disabled() || pci_is_root_bus(pdev->bus))
		वापस VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM |
		       VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;

	max_busnr = pci_bus_max_busnr(pdev->bus);
	decodes = VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;

	जबतक ((पंचांगp = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, पंचांगp)) != शून्य) अणु
		अगर (पंचांगp == pdev ||
		    pci_करोमुख्य_nr(पंचांगp->bus) != pci_करोमुख्य_nr(pdev->bus) ||
		    pci_is_root_bus(पंचांगp->bus))
			जारी;

		अगर (पंचांगp->bus->number >= pdev->bus->number &&
		    पंचांगp->bus->number <= max_busnr) अणु
			pci_dev_put(पंचांगp);
			decodes |= VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस decodes;
पूर्ण

अटल अंतरभूत bool vfio_pci_is_vga(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA;
पूर्ण

अटल व्योम vfio_pci_probe_mmaps(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा resource *res;
	पूर्णांक i;
	काष्ठा vfio_pci_dummy_resource *dummy_res;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		पूर्णांक bar = i + PCI_STD_RESOURCES;

		res = &vdev->pdev->resource[bar];

		अगर (!IS_ENABLED(CONFIG_VFIO_PCI_MMAP))
			जाओ no_mmap;

		अगर (!(res->flags & IORESOURCE_MEM))
			जाओ no_mmap;

		/*
		 * The PCI core shouldn't set up a resource with a
		 * type but zero size. But there may be bugs that
		 * cause us to करो that.
		 */
		अगर (!resource_size(res))
			जाओ no_mmap;

		अगर (resource_size(res) >= PAGE_SIZE) अणु
			vdev->bar_mmap_supported[bar] = true;
			जारी;
		पूर्ण

		अगर (!(res->start & ~PAGE_MASK)) अणु
			/*
			 * Add a dummy resource to reserve the reमुख्यder
			 * of the exclusive page in हाल that hot-add
			 * device's bar is asचिन्हित पूर्णांकo it.
			 */
			dummy_res = kzalloc(माप(*dummy_res), GFP_KERNEL);
			अगर (dummy_res == शून्य)
				जाओ no_mmap;

			dummy_res->resource.name = "vfio sub-page reserved";
			dummy_res->resource.start = res->end + 1;
			dummy_res->resource.end = res->start + PAGE_SIZE - 1;
			dummy_res->resource.flags = res->flags;
			अगर (request_resource(res->parent,
						&dummy_res->resource)) अणु
				kमुक्त(dummy_res);
				जाओ no_mmap;
			पूर्ण
			dummy_res->index = bar;
			list_add(&dummy_res->res_next,
					&vdev->dummy_resources_list);
			vdev->bar_mmap_supported[bar] = true;
			जारी;
		पूर्ण
		/*
		 * Here we करोn't handle the हाल when the BAR is not page
		 * aligned because we can't expect the BAR will be
		 * asचिन्हित पूर्णांकo the same location in a page in guest
		 * when we passthrough the BAR. And it's hard to access
		 * this BAR in userspace because we have no way to get
		 * the BAR's location in a page.
		 */
no_mmap:
		vdev->bar_mmap_supported[bar] = false;
	पूर्ण
पूर्ण

अटल व्योम vfio_pci_try_bus_reset(काष्ठा vfio_pci_device *vdev);
अटल व्योम vfio_pci_disable(काष्ठा vfio_pci_device *vdev);
अटल पूर्णांक vfio_pci_try_zap_and_vma_lock_cb(काष्ठा pci_dev *pdev, व्योम *data);

/*
 * INTx masking requires the ability to disable INTx संकेतing via PCI_COMMAND
 * _and_ the ability detect when the device is निश्चितing INTx via PCI_STATUS.
 * If a device implements the क्रमmer but not the latter we would typically
 * expect broken_पूर्णांकx_masking be set and require an exclusive पूर्णांकerrupt.
 * However since we करो have control of the device's ability to निश्चित INTx,
 * we can instead pretend that the device करोes not implement INTx, भवizing
 * the pin रेजिस्टर to report zero and मुख्यtaining DisINTx set on the host.
 */
अटल bool vfio_pci_noपूर्णांकx(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->venकरोr) अणु
	हाल PCI_VENDOR_ID_INTEL:
		चयन (pdev->device) अणु
		/* All i40e (XL710/X710/XXV710) 10/20/25/40GbE NICs */
		हाल 0x1572:
		हाल 0x1574:
		हाल 0x1580 ... 0x1581:
		हाल 0x1583 ... 0x158b:
		हाल 0x37d0 ... 0x37d2:
		/* X550 */
		हाल 0x1563:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम vfio_pci_probe_घातer_state(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u16 pmcsr;

	अगर (!pdev->pm_cap)
		वापस;

	pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &pmcsr);

	vdev->needs_pm_restore = !(pmcsr & PCI_PM_CTRL_NO_SOFT_RESET);
पूर्ण

/*
 * pci_set_घातer_state() wrapper handling devices which perक्रमm a soft reset on
 * D3->D0 transition.  Save state prior to D0/1/2->D3, stash it on the vdev,
 * restore when वापसed to D0.  Saved separately from pci_saved_state क्रम use
 * by PM capability emulation and separately from pci_dev पूर्णांकernal saved state
 * to aव्योम it being overwritten and consumed around other resets.
 */
पूर्णांक vfio_pci_set_घातer_state(काष्ठा vfio_pci_device *vdev, pci_घातer_t state)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	bool needs_restore = false, needs_save = false;
	पूर्णांक ret;

	अगर (vdev->needs_pm_restore) अणु
		अगर (pdev->current_state < PCI_D3hot && state >= PCI_D3hot) अणु
			pci_save_state(pdev);
			needs_save = true;
		पूर्ण

		अगर (pdev->current_state >= PCI_D3hot && state <= PCI_D0)
			needs_restore = true;
	पूर्ण

	ret = pci_set_घातer_state(pdev, state);

	अगर (!ret) अणु
		/* D3 might be unsupported via quirk, skip unless in D3 */
		अगर (needs_save && pdev->current_state >= PCI_D3hot) अणु
			vdev->pm_save = pci_store_saved_state(pdev);
		पूर्ण अन्यथा अगर (needs_restore) अणु
			pci_load_and_मुक्त_saved_state(pdev, &vdev->pm_save);
			pci_restore_state(pdev);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_pci_enable(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक ret;
	u16 cmd;
	u8 msix_pos;

	vfio_pci_set_घातer_state(vdev, PCI_D0);

	/* Don't allow our initial saved state to include busmaster */
	pci_clear_master(pdev);

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	/* If reset fails because of the device lock, fail this path entirely */
	ret = pci_try_reset_function(pdev);
	अगर (ret == -EAGAIN) अणु
		pci_disable_device(pdev);
		वापस ret;
	पूर्ण

	vdev->reset_works = !ret;
	pci_save_state(pdev);
	vdev->pci_saved_state = pci_store_saved_state(pdev);
	अगर (!vdev->pci_saved_state)
		pci_dbg(pdev, "%s: Couldn't store saved state\n", __func__);

	अगर (likely(!noपूर्णांकxmask)) अणु
		अगर (vfio_pci_noपूर्णांकx(pdev)) अणु
			pci_info(pdev, "Masking broken INTx support\n");
			vdev->noपूर्णांकx = true;
			pci_पूर्णांकx(pdev, 0);
		पूर्ण अन्यथा
			vdev->pci_2_3 = pci_पूर्णांकx_mask_supported(pdev);
	पूर्ण

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर (vdev->pci_2_3 && (cmd & PCI_COMMAND_INTX_DISABLE)) अणु
		cmd &= ~PCI_COMMAND_INTX_DISABLE;
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
	पूर्ण

	ret = vfio_config_init(vdev);
	अगर (ret) अणु
		kमुक्त(vdev->pci_saved_state);
		vdev->pci_saved_state = शून्य;
		pci_disable_device(pdev);
		वापस ret;
	पूर्ण

	msix_pos = pdev->msix_cap;
	अगर (msix_pos) अणु
		u16 flags;
		u32 table;

		pci_पढ़ो_config_word(pdev, msix_pos + PCI_MSIX_FLAGS, &flags);
		pci_पढ़ो_config_dword(pdev, msix_pos + PCI_MSIX_TABLE, &table);

		vdev->msix_bar = table & PCI_MSIX_TABLE_BIR;
		vdev->msix_offset = table & PCI_MSIX_TABLE_OFFSET;
		vdev->msix_size = ((flags & PCI_MSIX_FLAGS_QSIZE) + 1) * 16;
	पूर्ण अन्यथा
		vdev->msix_bar = 0xFF;

	अगर (!vfio_vga_disabled() && vfio_pci_is_vga(pdev))
		vdev->has_vga = true;

	अगर (vfio_pci_is_vga(pdev) &&
	    pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    IS_ENABLED(CONFIG_VFIO_PCI_IGD)) अणु
		ret = vfio_pci_igd_init(vdev);
		अगर (ret && ret != -ENODEV) अणु
			pci_warn(pdev, "Failed to setup Intel IGD regions\n");
			जाओ disable_निकास;
		पूर्ण
	पूर्ण

	vfio_pci_probe_mmaps(vdev);

	वापस 0;

disable_निकास:
	vfio_pci_disable(vdev);
	वापस ret;
पूर्ण

अटल व्योम vfio_pci_disable(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	काष्ठा vfio_pci_dummy_resource *dummy_res, *पंचांगp;
	काष्ठा vfio_pci_ioeventfd *ioeventfd, *ioeventfd_पंचांगp;
	पूर्णांक i, bar;

	/* Stop the device from further DMA */
	pci_clear_master(pdev);

	vfio_pci_set_irqs_ioctl(vdev, VFIO_IRQ_SET_DATA_NONE |
				VFIO_IRQ_SET_ACTION_TRIGGER,
				vdev->irq_type, 0, 0, शून्य);

	/* Device बंदd, करोn't need mutex here */
	list_क्रम_each_entry_safe(ioeventfd, ioeventfd_पंचांगp,
				 &vdev->ioeventfds_list, next) अणु
		vfio_virqfd_disable(&ioeventfd->virqfd);
		list_del(&ioeventfd->next);
		kमुक्त(ioeventfd);
	पूर्ण
	vdev->ioeventfds_nr = 0;

	vdev->virq_disabled = false;

	क्रम (i = 0; i < vdev->num_regions; i++)
		vdev->region[i].ops->release(vdev, &vdev->region[i]);

	vdev->num_regions = 0;
	kमुक्त(vdev->region);
	vdev->region = शून्य; /* करोn't kपुनः_स्मृति a मुक्तd poपूर्णांकer */

	vfio_config_मुक्त(vdev);

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		bar = i + PCI_STD_RESOURCES;
		अगर (!vdev->barmap[bar])
			जारी;
		pci_iounmap(pdev, vdev->barmap[bar]);
		pci_release_selected_regions(pdev, 1 << bar);
		vdev->barmap[bar] = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(dummy_res, पंचांगp,
				 &vdev->dummy_resources_list, res_next) अणु
		list_del(&dummy_res->res_next);
		release_resource(&dummy_res->resource);
		kमुक्त(dummy_res);
	पूर्ण

	vdev->needs_reset = true;

	/*
	 * If we have saved state, restore it.  If we can reset the device,
	 * even better.  Resetting with current state seems better than
	 * nothing, but saving and restoring current state without reset
	 * is just busy work.
	 */
	अगर (pci_load_and_मुक्त_saved_state(pdev, &vdev->pci_saved_state)) अणु
		pci_info(pdev, "%s: Couldn't reload saved state\n", __func__);

		अगर (!vdev->reset_works)
			जाओ out;

		pci_save_state(pdev);
	पूर्ण

	/*
	 * Disable INTx and MSI, presumably to aव्योम spurious पूर्णांकerrupts
	 * during reset.  Stolen from pci_reset_function()
	 */
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE);

	/*
	 * Try to get the locks ourselves to prevent a deadlock. The
	 * success of this is dependent on being able to lock the device,
	 * which is not always possible.
	 * We can not use the "try" reset पूर्णांकerface here, which will
	 * overग_लिखो the previously restored configuration inक्रमmation.
	 */
	अगर (vdev->reset_works && pci_cfg_access_trylock(pdev)) अणु
		अगर (device_trylock(&pdev->dev)) अणु
			अगर (!__pci_reset_function_locked(pdev))
				vdev->needs_reset = false;
			device_unlock(&pdev->dev);
		पूर्ण
		pci_cfg_access_unlock(pdev);
	पूर्ण

	pci_restore_state(pdev);
out:
	pci_disable_device(pdev);

	vfio_pci_try_bus_reset(vdev);

	अगर (!disable_idle_d3)
		vfio_pci_set_घातer_state(vdev, PCI_D3hot);
पूर्ण

अटल काष्ठा pci_driver vfio_pci_driver;

अटल काष्ठा vfio_pci_device *get_pf_vdev(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *physfn = pci_physfn(vdev->pdev);
	काष्ठा vfio_device *pf_dev;

	अगर (!vdev->pdev->is_virtfn)
		वापस शून्य;

	pf_dev = vfio_device_get_from_dev(&physfn->dev);
	अगर (!pf_dev)
		वापस शून्य;

	अगर (pci_dev_driver(physfn) != &vfio_pci_driver) अणु
		vfio_device_put(pf_dev);
		वापस शून्य;
	पूर्ण

	वापस container_of(pf_dev, काष्ठा vfio_pci_device, vdev);
पूर्ण

अटल व्योम vfio_pci_vf_token_user_add(काष्ठा vfio_pci_device *vdev, पूर्णांक val)
अणु
	काष्ठा vfio_pci_device *pf_vdev = get_pf_vdev(vdev);

	अगर (!pf_vdev)
		वापस;

	mutex_lock(&pf_vdev->vf_token->lock);
	pf_vdev->vf_token->users += val;
	WARN_ON(pf_vdev->vf_token->users < 0);
	mutex_unlock(&pf_vdev->vf_token->lock);

	vfio_device_put(&pf_vdev->vdev);
पूर्ण

अटल व्योम vfio_pci_release(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);

	mutex_lock(&vdev->reflck->lock);

	अगर (!(--vdev->refcnt)) अणु
		vfio_pci_vf_token_user_add(vdev, -1);
		vfio_spapr_pci_eeh_release(vdev->pdev);
		vfio_pci_disable(vdev);

		mutex_lock(&vdev->igate);
		अगर (vdev->err_trigger) अणु
			eventfd_ctx_put(vdev->err_trigger);
			vdev->err_trigger = शून्य;
		पूर्ण
		अगर (vdev->req_trigger) अणु
			eventfd_ctx_put(vdev->req_trigger);
			vdev->req_trigger = शून्य;
		पूर्ण
		mutex_unlock(&vdev->igate);
	पूर्ण

	mutex_unlock(&vdev->reflck->lock);

	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक vfio_pci_खोलो(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);
	पूर्णांक ret = 0;

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	mutex_lock(&vdev->reflck->lock);

	अगर (!vdev->refcnt) अणु
		ret = vfio_pci_enable(vdev);
		अगर (ret)
			जाओ error;

		vfio_spapr_pci_eeh_खोलो(vdev->pdev);
		vfio_pci_vf_token_user_add(vdev, 1);
	पूर्ण
	vdev->refcnt++;
error:
	mutex_unlock(&vdev->reflck->lock);
	अगर (ret)
		module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_pci_get_irq_count(काष्ठा vfio_pci_device *vdev, पूर्णांक irq_type)
अणु
	अगर (irq_type == VFIO_PCI_INTX_IRQ_INDEX) अणु
		u8 pin;

		अगर (!IS_ENABLED(CONFIG_VFIO_PCI_INTX) ||
		    vdev->noपूर्णांकx || vdev->pdev->is_virtfn)
			वापस 0;

		pci_पढ़ो_config_byte(vdev->pdev, PCI_INTERRUPT_PIN, &pin);

		वापस pin ? 1 : 0;
	पूर्ण अन्यथा अगर (irq_type == VFIO_PCI_MSI_IRQ_INDEX) अणु
		u8 pos;
		u16 flags;

		pos = vdev->pdev->msi_cap;
		अगर (pos) अणु
			pci_पढ़ो_config_word(vdev->pdev,
					     pos + PCI_MSI_FLAGS, &flags);
			वापस 1 << ((flags & PCI_MSI_FLAGS_QMASK) >> 1);
		पूर्ण
	पूर्ण अन्यथा अगर (irq_type == VFIO_PCI_MSIX_IRQ_INDEX) अणु
		u8 pos;
		u16 flags;

		pos = vdev->pdev->msix_cap;
		अगर (pos) अणु
			pci_पढ़ो_config_word(vdev->pdev,
					     pos + PCI_MSIX_FLAGS, &flags);

			वापस (flags & PCI_MSIX_FLAGS_QSIZE) + 1;
		पूर्ण
	पूर्ण अन्यथा अगर (irq_type == VFIO_PCI_ERR_IRQ_INDEX) अणु
		अगर (pci_is_pcie(vdev->pdev))
			वापस 1;
	पूर्ण अन्यथा अगर (irq_type == VFIO_PCI_REQ_IRQ_INDEX) अणु
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_count_devs(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	(*(पूर्णांक *)data)++;
	वापस 0;
पूर्ण

काष्ठा vfio_pci_fill_info अणु
	पूर्णांक max;
	पूर्णांक cur;
	काष्ठा vfio_pci_dependent_device *devices;
पूर्ण;

अटल पूर्णांक vfio_pci_fill_devs(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_pci_fill_info *fill = data;
	काष्ठा iommu_group *iommu_group;

	अगर (fill->cur == fill->max)
		वापस -EAGAIN; /* Something changed, try again */

	iommu_group = iommu_group_get(&pdev->dev);
	अगर (!iommu_group)
		वापस -EPERM; /* Cannot reset non-isolated devices */

	fill->devices[fill->cur].group_id = iommu_group_id(iommu_group);
	fill->devices[fill->cur].segment = pci_करोमुख्य_nr(pdev->bus);
	fill->devices[fill->cur].bus = pdev->bus->number;
	fill->devices[fill->cur].devfn = pdev->devfn;
	fill->cur++;
	iommu_group_put(iommu_group);
	वापस 0;
पूर्ण

काष्ठा vfio_pci_group_entry अणु
	काष्ठा vfio_group *group;
	पूर्णांक id;
पूर्ण;

काष्ठा vfio_pci_group_info अणु
	पूर्णांक count;
	काष्ठा vfio_pci_group_entry *groups;
पूर्ण;

अटल पूर्णांक vfio_pci_validate_devs(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_pci_group_info *info = data;
	काष्ठा iommu_group *group;
	पूर्णांक id, i;

	group = iommu_group_get(&pdev->dev);
	अगर (!group)
		वापस -EPERM;

	id = iommu_group_id(group);

	क्रम (i = 0; i < info->count; i++)
		अगर (info->groups[i].id == id)
			अवरोध;

	iommu_group_put(group);

	वापस (i == info->count) ? -EINVAL : 0;
पूर्ण

अटल bool vfio_pci_dev_below_slot(काष्ठा pci_dev *pdev, काष्ठा pci_slot *slot)
अणु
	क्रम (; pdev; pdev = pdev->bus->self)
		अगर (pdev->bus == slot->bus)
			वापस (pdev->slot == slot);
	वापस false;
पूर्ण

काष्ठा vfio_pci_walk_info अणु
	पूर्णांक (*fn)(काष्ठा pci_dev *, व्योम *data);
	व्योम *data;
	काष्ठा pci_dev *pdev;
	bool slot;
	पूर्णांक ret;
पूर्ण;

अटल पूर्णांक vfio_pci_walk_wrapper(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_pci_walk_info *walk = data;

	अगर (!walk->slot || vfio_pci_dev_below_slot(pdev, walk->pdev->slot))
		walk->ret = walk->fn(pdev, walk->data);

	वापस walk->ret;
पूर्ण

अटल पूर्णांक vfio_pci_क्रम_each_slot_or_bus(काष्ठा pci_dev *pdev,
					 पूर्णांक (*fn)(काष्ठा pci_dev *,
						   व्योम *data), व्योम *data,
					 bool slot)
अणु
	काष्ठा vfio_pci_walk_info walk = अणु
		.fn = fn, .data = data, .pdev = pdev, .slot = slot, .ret = 0,
	पूर्ण;

	pci_walk_bus(pdev->bus, vfio_pci_walk_wrapper, &walk);

	वापस walk.ret;
पूर्ण

अटल पूर्णांक msix_mmappable_cap(काष्ठा vfio_pci_device *vdev,
			      काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_info_cap_header header = अणु
		.id = VFIO_REGION_INFO_CAP_MSIX_MAPPABLE,
		.version = 1
	पूर्ण;

	वापस vfio_info_add_capability(caps, &header, माप(header));
पूर्ण

पूर्णांक vfio_pci_रेजिस्टर_dev_region(काष्ठा vfio_pci_device *vdev,
				 अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक subtype,
				 स्थिर काष्ठा vfio_pci_regops *ops,
				 माप_प्रकार size, u32 flags, व्योम *data)
अणु
	काष्ठा vfio_pci_region *region;

	region = kपुनः_स्मृति(vdev->region,
			  (vdev->num_regions + 1) * माप(*region),
			  GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	vdev->region = region;
	vdev->region[vdev->num_regions].type = type;
	vdev->region[vdev->num_regions].subtype = subtype;
	vdev->region[vdev->num_regions].ops = ops;
	vdev->region[vdev->num_regions].size = size;
	vdev->region[vdev->num_regions].flags = flags;
	vdev->region[vdev->num_regions].data = data;

	vdev->num_regions++;

	वापस 0;
पूर्ण

काष्ठा vfio_devices अणु
	काष्ठा vfio_pci_device **devices;
	पूर्णांक cur_index;
	पूर्णांक max_index;
पूर्ण;

अटल दीर्घ vfio_pci_ioctl(काष्ठा vfio_device *core_vdev,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);
	अचिन्हित दीर्घ minsz;

	अगर (cmd == VFIO_DEVICE_GET_INFO) अणु
		काष्ठा vfio_device_info info;
		काष्ठा vfio_info_cap caps = अणु .buf = शून्य, .size = 0 पूर्ण;
		अचिन्हित दीर्घ capsz;
		पूर्णांक ret;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		/* For backward compatibility, cannot require this */
		capsz = दुरत्वend(काष्ठा vfio_iommu_type1_info, cap_offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (info.argsz >= capsz) अणु
			minsz = capsz;
			info.cap_offset = 0;
		पूर्ण

		info.flags = VFIO_DEVICE_FLAGS_PCI;

		अगर (vdev->reset_works)
			info.flags |= VFIO_DEVICE_FLAGS_RESET;

		info.num_regions = VFIO_PCI_NUM_REGIONS + vdev->num_regions;
		info.num_irqs = VFIO_PCI_NUM_IRQS;

		ret = vfio_pci_info_zdev_add_caps(vdev, &caps);
		अगर (ret && ret != -ENODEV) अणु
			pci_warn(vdev->pdev, "Failed to setup zPCI info capabilities\n");
			वापस ret;
		पूर्ण

		अगर (caps.size) अणु
			info.flags |= VFIO_DEVICE_FLAGS_CAPS;
			अगर (info.argsz < माप(info) + caps.size) अणु
				info.argsz = माप(info) + caps.size;
			पूर्ण अन्यथा अणु
				vfio_info_cap_shअगरt(&caps, माप(info));
				अगर (copy_to_user((व्योम __user *)arg +
						  माप(info), caps.buf,
						  caps.size)) अणु
					kमुक्त(caps.buf);
					वापस -EFAULT;
				पूर्ण
				info.cap_offset = माप(info);
			पूर्ण

			kमुक्त(caps.buf);
		पूर्ण

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_REGION_INFO) अणु
		काष्ठा pci_dev *pdev = vdev->pdev;
		काष्ठा vfio_region_info info;
		काष्ठा vfio_info_cap caps = अणु .buf = शून्य, .size = 0 पूर्ण;
		पूर्णांक i, ret;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		चयन (info.index) अणु
		हाल VFIO_PCI_CONFIG_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = pdev->cfg_size;
			info.flags = VFIO_REGION_INFO_FLAG_READ |
				     VFIO_REGION_INFO_FLAG_WRITE;
			अवरोध;
		हाल VFIO_PCI_BAR0_REGION_INDEX ... VFIO_PCI_BAR5_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = pci_resource_len(pdev, info.index);
			अगर (!info.size) अणु
				info.flags = 0;
				अवरोध;
			पूर्ण

			info.flags = VFIO_REGION_INFO_FLAG_READ |
				     VFIO_REGION_INFO_FLAG_WRITE;
			अगर (vdev->bar_mmap_supported[info.index]) अणु
				info.flags |= VFIO_REGION_INFO_FLAG_MMAP;
				अगर (info.index == vdev->msix_bar) अणु
					ret = msix_mmappable_cap(vdev, &caps);
					अगर (ret)
						वापस ret;
				पूर्ण
			पूर्ण

			अवरोध;
		हाल VFIO_PCI_ROM_REGION_INDEX:
		अणु
			व्योम __iomem *io;
			माप_प्रकार size;
			u16 cmd;

			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.flags = 0;

			/* Report the BAR size, not the ROM size */
			info.size = pci_resource_len(pdev, info.index);
			अगर (!info.size) अणु
				/* Shaकरोw ROMs appear as PCI option ROMs */
				अगर (pdev->resource[PCI_ROM_RESOURCE].flags &
							IORESOURCE_ROM_SHADOW)
					info.size = 0x20000;
				अन्यथा
					अवरोध;
			पूर्ण

			/*
			 * Is it really there?  Enable memory decode क्रम
			 * implicit access in pci_map_rom().
			 */
			cmd = vfio_pci_memory_lock_and_enable(vdev);
			io = pci_map_rom(pdev, &size);
			अगर (io) अणु
				info.flags = VFIO_REGION_INFO_FLAG_READ;
				pci_unmap_rom(pdev, io);
			पूर्ण अन्यथा अणु
				info.size = 0;
			पूर्ण
			vfio_pci_memory_unlock_and_restore(vdev, cmd);

			अवरोध;
		पूर्ण
		हाल VFIO_PCI_VGA_REGION_INDEX:
			अगर (!vdev->has_vga)
				वापस -EINVAL;

			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = 0xc0000;
			info.flags = VFIO_REGION_INFO_FLAG_READ |
				     VFIO_REGION_INFO_FLAG_WRITE;

			अवरोध;
		शेष:
		अणु
			काष्ठा vfio_region_info_cap_type cap_type = अणु
					.header.id = VFIO_REGION_INFO_CAP_TYPE,
					.header.version = 1 पूर्ण;

			अगर (info.index >=
			    VFIO_PCI_NUM_REGIONS + vdev->num_regions)
				वापस -EINVAL;
			info.index = array_index_nospec(info.index,
							VFIO_PCI_NUM_REGIONS +
							vdev->num_regions);

			i = info.index - VFIO_PCI_NUM_REGIONS;

			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = vdev->region[i].size;
			info.flags = vdev->region[i].flags;

			cap_type.type = vdev->region[i].type;
			cap_type.subtype = vdev->region[i].subtype;

			ret = vfio_info_add_capability(&caps, &cap_type.header,
						       माप(cap_type));
			अगर (ret)
				वापस ret;

			अगर (vdev->region[i].ops->add_capability) अणु
				ret = vdev->region[i].ops->add_capability(vdev,
						&vdev->region[i], &caps);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		पूर्ण

		अगर (caps.size) अणु
			info.flags |= VFIO_REGION_INFO_FLAG_CAPS;
			अगर (info.argsz < माप(info) + caps.size) अणु
				info.argsz = माप(info) + caps.size;
				info.cap_offset = 0;
			पूर्ण अन्यथा अणु
				vfio_info_cap_shअगरt(&caps, माप(info));
				अगर (copy_to_user((व्योम __user *)arg +
						  माप(info), caps.buf,
						  caps.size)) अणु
					kमुक्त(caps.buf);
					वापस -EFAULT;
				पूर्ण
				info.cap_offset = माप(info);
			पूर्ण

			kमुक्त(caps.buf);
		पूर्ण

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_IRQ_INFO) अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz || info.index >= VFIO_PCI_NUM_IRQS)
			वापस -EINVAL;

		चयन (info.index) अणु
		हाल VFIO_PCI_INTX_IRQ_INDEX ... VFIO_PCI_MSIX_IRQ_INDEX:
		हाल VFIO_PCI_REQ_IRQ_INDEX:
			अवरोध;
		हाल VFIO_PCI_ERR_IRQ_INDEX:
			अगर (pci_is_pcie(vdev->pdev))
				अवरोध;
			fallthrough;
		शेष:
			वापस -EINVAL;
		पूर्ण

		info.flags = VFIO_IRQ_INFO_EVENTFD;

		info.count = vfio_pci_get_irq_count(vdev, info.index);

		अगर (info.index == VFIO_PCI_INTX_IRQ_INDEX)
			info.flags |= (VFIO_IRQ_INFO_MASKABLE |
				       VFIO_IRQ_INFO_AUTOMASKED);
		अन्यथा
			info.flags |= VFIO_IRQ_INFO_NORESIZE;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_SET_IRQS) अणु
		काष्ठा vfio_irq_set hdr;
		u8 *data = शून्य;
		पूर्णांक max, ret = 0;
		माप_प्रकार data_size = 0;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		max = vfio_pci_get_irq_count(vdev, hdr.index);

		ret = vfio_set_irqs_validate_and_prepare(&hdr, max,
						 VFIO_PCI_NUM_IRQS, &data_size);
		अगर (ret)
			वापस ret;

		अगर (data_size) अणु
			data = memdup_user((व्योम __user *)(arg + minsz),
					    data_size);
			अगर (IS_ERR(data))
				वापस PTR_ERR(data);
		पूर्ण

		mutex_lock(&vdev->igate);

		ret = vfio_pci_set_irqs_ioctl(vdev, hdr.flags, hdr.index,
					      hdr.start, hdr.count, data);

		mutex_unlock(&vdev->igate);
		kमुक्त(data);

		वापस ret;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_RESET) अणु
		पूर्णांक ret;

		अगर (!vdev->reset_works)
			वापस -EINVAL;

		vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(vdev);
		ret = pci_try_reset_function(vdev->pdev);
		up_ग_लिखो(&vdev->memory_lock);

		वापस ret;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_PCI_HOT_RESET_INFO) अणु
		काष्ठा vfio_pci_hot_reset_info hdr;
		काष्ठा vfio_pci_fill_info fill = अणु 0 पूर्ण;
		काष्ठा vfio_pci_dependent_device *devices = शून्य;
		bool slot = false;
		पूर्णांक ret = 0;

		minsz = दुरत्वend(काष्ठा vfio_pci_hot_reset_info, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (hdr.argsz < minsz)
			वापस -EINVAL;

		hdr.flags = 0;

		/* Can we करो a slot or bus reset or neither? */
		अगर (!pci_probe_reset_slot(vdev->pdev->slot))
			slot = true;
		अन्यथा अगर (pci_probe_reset_bus(vdev->pdev->bus))
			वापस -ENODEV;

		/* How many devices are affected? */
		ret = vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
						    vfio_pci_count_devs,
						    &fill.max, slot);
		अगर (ret)
			वापस ret;

		WARN_ON(!fill.max); /* Should always be at least one */

		/*
		 * If there's enough space, fill it now, otherwise वापस
		 * -ENOSPC and the number of devices affected.
		 */
		अगर (hdr.argsz < माप(hdr) + (fill.max * माप(*devices))) अणु
			ret = -ENOSPC;
			hdr.count = fill.max;
			जाओ reset_info_निकास;
		पूर्ण

		devices = kसुस्मृति(fill.max, माप(*devices), GFP_KERNEL);
		अगर (!devices)
			वापस -ENOMEM;

		fill.devices = devices;

		ret = vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
						    vfio_pci_fill_devs,
						    &fill, slot);

		/*
		 * If a device was हटाओd between counting and filling,
		 * we may come up लघु of fill.max.  If a device was
		 * added, we'll have a वापस of -EAGAIN above.
		 */
		अगर (!ret)
			hdr.count = fill.cur;

reset_info_निकास:
		अगर (copy_to_user((व्योम __user *)arg, &hdr, minsz))
			ret = -EFAULT;

		अगर (!ret) अणु
			अगर (copy_to_user((व्योम __user *)(arg + minsz), devices,
					 hdr.count * माप(*devices)))
				ret = -EFAULT;
		पूर्ण

		kमुक्त(devices);
		वापस ret;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_PCI_HOT_RESET) अणु
		काष्ठा vfio_pci_hot_reset hdr;
		पूर्णांक32_t *group_fds;
		काष्ठा vfio_pci_group_entry *groups;
		काष्ठा vfio_pci_group_info info;
		काष्ठा vfio_devices devs = अणु .cur_index = 0 पूर्ण;
		bool slot = false;
		पूर्णांक i, group_idx, mem_idx = 0, count = 0, ret = 0;

		minsz = दुरत्वend(काष्ठा vfio_pci_hot_reset, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (hdr.argsz < minsz || hdr.flags)
			वापस -EINVAL;

		/* Can we करो a slot or bus reset or neither? */
		अगर (!pci_probe_reset_slot(vdev->pdev->slot))
			slot = true;
		अन्यथा अगर (pci_probe_reset_bus(vdev->pdev->bus))
			वापस -ENODEV;

		/*
		 * We can't let userspace give us an arbitrarily large
		 * buffer to copy, so verअगरy how many we think there
		 * could be.  Note groups can have multiple devices so
		 * one group per device is the max.
		 */
		ret = vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
						    vfio_pci_count_devs,
						    &count, slot);
		अगर (ret)
			वापस ret;

		/* Somewhere between 1 and count is OK */
		अगर (!hdr.count || hdr.count > count)
			वापस -EINVAL;

		group_fds = kसुस्मृति(hdr.count, माप(*group_fds), GFP_KERNEL);
		groups = kसुस्मृति(hdr.count, माप(*groups), GFP_KERNEL);
		अगर (!group_fds || !groups) अणु
			kमुक्त(group_fds);
			kमुक्त(groups);
			वापस -ENOMEM;
		पूर्ण

		अगर (copy_from_user(group_fds, (व्योम __user *)(arg + minsz),
				   hdr.count * माप(*group_fds))) अणु
			kमुक्त(group_fds);
			kमुक्त(groups);
			वापस -EFAULT;
		पूर्ण

		/*
		 * For each group_fd, get the group through the vfio बाह्यal
		 * user पूर्णांकerface and store the group and iommu ID.  This
		 * ensures the group is held across the reset.
		 */
		क्रम (group_idx = 0; group_idx < hdr.count; group_idx++) अणु
			काष्ठा vfio_group *group;
			काष्ठा fd f = fdget(group_fds[group_idx]);
			अगर (!f.file) अणु
				ret = -EBADF;
				अवरोध;
			पूर्ण

			group = vfio_group_get_बाह्यal_user(f.file);
			fdput(f);
			अगर (IS_ERR(group)) अणु
				ret = PTR_ERR(group);
				अवरोध;
			पूर्ण

			groups[group_idx].group = group;
			groups[group_idx].id =
					vfio_बाह्यal_user_iommu_id(group);
		पूर्ण

		kमुक्त(group_fds);

		/* release reference to groups on error */
		अगर (ret)
			जाओ hot_reset_release;

		info.count = hdr.count;
		info.groups = groups;

		/*
		 * Test whether all the affected devices are contained
		 * by the set of groups provided by the user.
		 */
		ret = vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
						    vfio_pci_validate_devs,
						    &info, slot);
		अगर (ret)
			जाओ hot_reset_release;

		devs.max_index = count;
		devs.devices = kसुस्मृति(count, माप(काष्ठा vfio_device *),
				       GFP_KERNEL);
		अगर (!devs.devices) अणु
			ret = -ENOMEM;
			जाओ hot_reset_release;
		पूर्ण

		/*
		 * We need to get memory_lock क्रम each device, but devices
		 * can share mmap_lock, thereक्रमe we need to zap and hold
		 * the vma_lock क्रम each device, and only then get each
		 * memory_lock.
		 */
		ret = vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
					    vfio_pci_try_zap_and_vma_lock_cb,
					    &devs, slot);
		अगर (ret)
			जाओ hot_reset_release;

		क्रम (; mem_idx < devs.cur_index; mem_idx++) अणु
			काष्ठा vfio_pci_device *पंचांगp = devs.devices[mem_idx];

			ret = करोwn_ग_लिखो_trylock(&पंचांगp->memory_lock);
			अगर (!ret) अणु
				ret = -EBUSY;
				जाओ hot_reset_release;
			पूर्ण
			mutex_unlock(&पंचांगp->vma_lock);
		पूर्ण

		/* User has access, करो the reset */
		ret = pci_reset_bus(vdev->pdev);

hot_reset_release:
		क्रम (i = 0; i < devs.cur_index; i++) अणु
			काष्ठा vfio_pci_device *पंचांगp = devs.devices[i];

			अगर (i < mem_idx)
				up_ग_लिखो(&पंचांगp->memory_lock);
			अन्यथा
				mutex_unlock(&पंचांगp->vma_lock);
			vfio_device_put(&पंचांगp->vdev);
		पूर्ण
		kमुक्त(devs.devices);

		क्रम (group_idx--; group_idx >= 0; group_idx--)
			vfio_group_put_बाह्यal_user(groups[group_idx].group);

		kमुक्त(groups);
		वापस ret;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_IOEVENTFD) अणु
		काष्ठा vfio_device_ioeventfd ioeventfd;
		पूर्णांक count;

		minsz = दुरत्वend(काष्ठा vfio_device_ioeventfd, fd);

		अगर (copy_from_user(&ioeventfd, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (ioeventfd.argsz < minsz)
			वापस -EINVAL;

		अगर (ioeventfd.flags & ~VFIO_DEVICE_IOEVENTFD_SIZE_MASK)
			वापस -EINVAL;

		count = ioeventfd.flags & VFIO_DEVICE_IOEVENTFD_SIZE_MASK;

		अगर (hweight8(count) != 1 || ioeventfd.fd < -1)
			वापस -EINVAL;

		वापस vfio_pci_ioeventfd(vdev, ioeventfd.offset,
					  ioeventfd.data, count, ioeventfd.fd);
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_FEATURE) अणु
		काष्ठा vfio_device_feature feature;
		uuid_t uuid;

		minsz = दुरत्वend(काष्ठा vfio_device_feature, flags);

		अगर (copy_from_user(&feature, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (feature.argsz < minsz)
			वापस -EINVAL;

		/* Check unknown flags */
		अगर (feature.flags & ~(VFIO_DEVICE_FEATURE_MASK |
				      VFIO_DEVICE_FEATURE_SET |
				      VFIO_DEVICE_FEATURE_GET |
				      VFIO_DEVICE_FEATURE_PROBE))
			वापस -EINVAL;

		/* GET & SET are mutually exclusive except with PROBE */
		अगर (!(feature.flags & VFIO_DEVICE_FEATURE_PROBE) &&
		    (feature.flags & VFIO_DEVICE_FEATURE_SET) &&
		    (feature.flags & VFIO_DEVICE_FEATURE_GET))
			वापस -EINVAL;

		चयन (feature.flags & VFIO_DEVICE_FEATURE_MASK) अणु
		हाल VFIO_DEVICE_FEATURE_PCI_VF_TOKEN:
			अगर (!vdev->vf_token)
				वापस -ENOTTY;

			/*
			 * We करो not support GET of the VF Token UUID as this
			 * could expose the token of the previous device user.
			 */
			अगर (feature.flags & VFIO_DEVICE_FEATURE_GET)
				वापस -EINVAL;

			अगर (feature.flags & VFIO_DEVICE_FEATURE_PROBE)
				वापस 0;

			/* Don't SET unless told to करो so */
			अगर (!(feature.flags & VFIO_DEVICE_FEATURE_SET))
				वापस -EINVAL;

			अगर (feature.argsz < minsz + माप(uuid))
				वापस -EINVAL;

			अगर (copy_from_user(&uuid, (व्योम __user *)(arg + minsz),
					   माप(uuid)))
				वापस -EFAULT;

			mutex_lock(&vdev->vf_token->lock);
			uuid_copy(&vdev->vf_token->uuid, &uuid);
			mutex_unlock(&vdev->vf_token->lock);

			वापस 0;
		शेष:
			वापस -ENOTTY;
		पूर्ण
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार vfio_pci_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	अचिन्हित पूर्णांक index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);

	अगर (index >= VFIO_PCI_NUM_REGIONS + vdev->num_regions)
		वापस -EINVAL;

	चयन (index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:
		वापस vfio_pci_config_rw(vdev, buf, count, ppos, isग_लिखो);

	हाल VFIO_PCI_ROM_REGION_INDEX:
		अगर (isग_लिखो)
			वापस -EINVAL;
		वापस vfio_pci_bar_rw(vdev, buf, count, ppos, false);

	हाल VFIO_PCI_BAR0_REGION_INDEX ... VFIO_PCI_BAR5_REGION_INDEX:
		वापस vfio_pci_bar_rw(vdev, buf, count, ppos, isग_लिखो);

	हाल VFIO_PCI_VGA_REGION_INDEX:
		वापस vfio_pci_vga_rw(vdev, buf, count, ppos, isग_लिखो);
	शेष:
		index -= VFIO_PCI_NUM_REGIONS;
		वापस vdev->region[index].ops->rw(vdev, buf,
						   count, ppos, isग_लिखो);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार vfio_pci_पढ़ो(काष्ठा vfio_device *core_vdev, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);

	अगर (!count)
		वापस 0;

	वापस vfio_pci_rw(vdev, buf, count, ppos, false);
पूर्ण

अटल sमाप_प्रकार vfio_pci_ग_लिखो(काष्ठा vfio_device *core_vdev, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);

	अगर (!count)
		वापस 0;

	वापस vfio_pci_rw(vdev, (अक्षर __user *)buf, count, ppos, true);
पूर्ण

/* Return 1 on zap and vma_lock acquired, 0 on contention (only with @try) */
अटल पूर्णांक vfio_pci_zap_and_vma_lock(काष्ठा vfio_pci_device *vdev, bool try)
अणु
	काष्ठा vfio_pci_mmap_vma *mmap_vma, *पंचांगp;

	/*
	 * Lock ordering:
	 * vma_lock is nested under mmap_lock क्रम vm_ops callback paths.
	 * The memory_lock semaphore is used by both code paths calling
	 * पूर्णांकo this function to zap vmas and the vm_ops.fault callback
	 * to protect the memory enable state of the device.
	 *
	 * When zapping vmas we need to मुख्यtain the mmap_lock => vma_lock
	 * ordering, which requires using vma_lock to walk vma_list to
	 * acquire an mm, then dropping vma_lock to get the mmap_lock and
	 * reacquiring vma_lock.  This logic is derived from similar
	 * requirements in uverbs_user_mmap_disassociate().
	 *
	 * mmap_lock must always be the top-level lock when it is taken.
	 * Thereक्रमe we can only hold the memory_lock ग_लिखो lock when
	 * vma_list is empty, as we'd need to take mmap_lock to clear
	 * entries.  vma_list can only be guaranteed empty when holding
	 * vma_lock, thus memory_lock is nested under vma_lock.
	 *
	 * This enables the vm_ops.fault callback to acquire vma_lock,
	 * followed by memory_lock पढ़ो lock, जबतक alपढ़ोy holding
	 * mmap_lock without risk of deadlock.
	 */
	जबतक (1) अणु
		काष्ठा mm_काष्ठा *mm = शून्य;

		अगर (try) अणु
			अगर (!mutex_trylock(&vdev->vma_lock))
				वापस 0;
		पूर्ण अन्यथा अणु
			mutex_lock(&vdev->vma_lock);
		पूर्ण
		जबतक (!list_empty(&vdev->vma_list)) अणु
			mmap_vma = list_first_entry(&vdev->vma_list,
						    काष्ठा vfio_pci_mmap_vma,
						    vma_next);
			mm = mmap_vma->vma->vm_mm;
			अगर (mmget_not_zero(mm))
				अवरोध;

			list_del(&mmap_vma->vma_next);
			kमुक्त(mmap_vma);
			mm = शून्य;
		पूर्ण
		अगर (!mm)
			वापस 1;
		mutex_unlock(&vdev->vma_lock);

		अगर (try) अणु
			अगर (!mmap_पढ़ो_trylock(mm)) अणु
				mmput(mm);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			mmap_पढ़ो_lock(mm);
		पूर्ण
		अगर (try) अणु
			अगर (!mutex_trylock(&vdev->vma_lock)) अणु
				mmap_पढ़ो_unlock(mm);
				mmput(mm);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			mutex_lock(&vdev->vma_lock);
		पूर्ण
		list_क्रम_each_entry_safe(mmap_vma, पंचांगp,
					 &vdev->vma_list, vma_next) अणु
			काष्ठा vm_area_काष्ठा *vma = mmap_vma->vma;

			अगर (vma->vm_mm != mm)
				जारी;

			list_del(&mmap_vma->vma_next);
			kमुक्त(mmap_vma);

			zap_vma_ptes(vma, vma->vm_start,
				     vma->vm_end - vma->vm_start);
		पूर्ण
		mutex_unlock(&vdev->vma_lock);
		mmap_पढ़ो_unlock(mm);
		mmput(mm);
	पूर्ण
पूर्ण

व्योम vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(काष्ठा vfio_pci_device *vdev)
अणु
	vfio_pci_zap_and_vma_lock(vdev, false);
	करोwn_ग_लिखो(&vdev->memory_lock);
	mutex_unlock(&vdev->vma_lock);
पूर्ण

u16 vfio_pci_memory_lock_and_enable(काष्ठा vfio_pci_device *vdev)
अणु
	u16 cmd;

	करोwn_ग_लिखो(&vdev->memory_lock);
	pci_पढ़ो_config_word(vdev->pdev, PCI_COMMAND, &cmd);
	अगर (!(cmd & PCI_COMMAND_MEMORY))
		pci_ग_लिखो_config_word(vdev->pdev, PCI_COMMAND,
				      cmd | PCI_COMMAND_MEMORY);

	वापस cmd;
पूर्ण

व्योम vfio_pci_memory_unlock_and_restore(काष्ठा vfio_pci_device *vdev, u16 cmd)
अणु
	pci_ग_लिखो_config_word(vdev->pdev, PCI_COMMAND, cmd);
	up_ग_लिखो(&vdev->memory_lock);
पूर्ण

/* Caller holds vma_lock */
अटल पूर्णांक __vfio_pci_add_vma(काष्ठा vfio_pci_device *vdev,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_pci_mmap_vma *mmap_vma;

	mmap_vma = kदो_स्मृति(माप(*mmap_vma), GFP_KERNEL);
	अगर (!mmap_vma)
		वापस -ENOMEM;

	mmap_vma->vma = vma;
	list_add(&mmap_vma->vma_next, &vdev->vma_list);

	वापस 0;
पूर्ण

/*
 * Zap mmaps on खोलो so that we can fault them in on access and thereक्रमe
 * our vma_list only tracks mappings accessed since last zap.
 */
अटल व्योम vfio_pci_mmap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	zap_vma_ptes(vma, vma->vm_start, vma->vm_end - vma->vm_start);
पूर्ण

अटल व्योम vfio_pci_mmap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_pci_device *vdev = vma->vm_निजी_data;
	काष्ठा vfio_pci_mmap_vma *mmap_vma;

	mutex_lock(&vdev->vma_lock);
	list_क्रम_each_entry(mmap_vma, &vdev->vma_list, vma_next) अणु
		अगर (mmap_vma->vma == vma) अणु
			list_del(&mmap_vma->vma_next);
			kमुक्त(mmap_vma);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vdev->vma_lock);
पूर्ण

अटल vm_fault_t vfio_pci_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा vfio_pci_device *vdev = vma->vm_निजी_data;
	vm_fault_t ret = VM_FAULT_NOPAGE;

	mutex_lock(&vdev->vma_lock);
	करोwn_पढ़ो(&vdev->memory_lock);

	अगर (!__vfio_pci_memory_enabled(vdev)) अणु
		ret = VM_FAULT_SIGBUS;
		mutex_unlock(&vdev->vma_lock);
		जाओ up_out;
	पूर्ण

	अगर (__vfio_pci_add_vma(vdev, vma)) अणु
		ret = VM_FAULT_OOM;
		mutex_unlock(&vdev->vma_lock);
		जाओ up_out;
	पूर्ण

	mutex_unlock(&vdev->vma_lock);

	अगर (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot))
		ret = VM_FAULT_SIGBUS;

up_out:
	up_पढ़ो(&vdev->memory_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vfio_pci_mmap_ops = अणु
	.खोलो = vfio_pci_mmap_खोलो,
	.बंद = vfio_pci_mmap_बंद,
	.fault = vfio_pci_mmap_fault,
पूर्ण;

अटल पूर्णांक vfio_pci_mmap(काष्ठा vfio_device *core_vdev, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);
	काष्ठा pci_dev *pdev = vdev->pdev;
	अचिन्हित पूर्णांक index;
	u64 phys_len, req_len, pgoff, req_start;
	पूर्णांक ret;

	index = vma->vm_pgoff >> (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT);

	अगर (index >= VFIO_PCI_NUM_REGIONS + vdev->num_regions)
		वापस -EINVAL;
	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;
	अगर (index >= VFIO_PCI_NUM_REGIONS) अणु
		पूर्णांक regnum = index - VFIO_PCI_NUM_REGIONS;
		काष्ठा vfio_pci_region *region = vdev->region + regnum;

		अगर (region->ops && region->ops->mmap &&
		    (region->flags & VFIO_REGION_INFO_FLAG_MMAP))
			वापस region->ops->mmap(vdev, region, vma);
		वापस -EINVAL;
	पूर्ण
	अगर (index >= VFIO_PCI_ROM_REGION_INDEX)
		वापस -EINVAL;
	अगर (!vdev->bar_mmap_supported[index])
		वापस -EINVAL;

	phys_len = PAGE_ALIGN(pci_resource_len(pdev, index));
	req_len = vma->vm_end - vma->vm_start;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	req_start = pgoff << PAGE_SHIFT;

	अगर (req_start + req_len > phys_len)
		वापस -EINVAL;

	/*
	 * Even though we करोn't make use of the barmap क्रम the mmap,
	 * we need to request the region and the barmap tracks that.
	 */
	अगर (!vdev->barmap[index]) अणु
		ret = pci_request_selected_regions(pdev,
						   1 << index, "vfio-pci");
		अगर (ret)
			वापस ret;

		vdev->barmap[index] = pci_iomap(pdev, index, 0);
		अगर (!vdev->barmap[index]) अणु
			pci_release_selected_regions(pdev, 1 << index);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	vma->vm_निजी_data = vdev;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = (pci_resource_start(pdev, index) >> PAGE_SHIFT) + pgoff;

	/*
	 * See remap_pfn_range(), called from vfio_pci_fault() but we can't
	 * change vm_flags within the fault handler.  Set them now.
	 */
	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &vfio_pci_mmap_ops;

	वापस 0;
पूर्ण

अटल व्योम vfio_pci_request(काष्ठा vfio_device *core_vdev, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);
	काष्ठा pci_dev *pdev = vdev->pdev;

	mutex_lock(&vdev->igate);

	अगर (vdev->req_trigger) अणु
		अगर (!(count % 10))
			pci_notice_ratelimited(pdev,
				"Relaying device request to user (#%u)\n",
				count);
		eventfd_संकेत(vdev->req_trigger, 1);
	पूर्ण अन्यथा अगर (count == 0) अणु
		pci_warn(pdev,
			"No device request channel registered, blocked until released by user\n");
	पूर्ण

	mutex_unlock(&vdev->igate);
पूर्ण

अटल पूर्णांक vfio_pci_validate_vf_token(काष्ठा vfio_pci_device *vdev,
				      bool vf_token, uuid_t *uuid)
अणु
	/*
	 * There's always some degree of trust or collaboration between SR-IOV
	 * PF and VFs, even अगर just that the PF hosts the SR-IOV capability and
	 * can disrupt VFs with a reset, but often the PF has more explicit
	 * access to deny service to the VF or access data passed through the
	 * VF.  We thereक्रमe require an opt-in via a shared VF token (UUID) to
	 * represent this trust.  This both prevents that a VF driver might
	 * assume the PF driver is a trusted, in-kernel driver, and also that
	 * a PF driver might be replaced with a rogue driver, unknown to in-use
	 * VF drivers.
	 *
	 * Thereक्रमe when presented with a VF, अगर the PF is a vfio device and
	 * it is bound to the vfio-pci driver, the user needs to provide a VF
	 * token to access the device, in the क्रमm of appending a vf_token to
	 * the device name, क्रम example:
	 *
	 * "0000:04:10.0 vf_token=bd8d9d2b-5a5f-4f5a-a211-f591514ba1f3"
	 *
	 * When presented with a PF which has VFs in use, the user must also
	 * provide the current VF token to prove collaboration with existing
	 * VF users.  If VFs are not in use, the VF token provided क्रम the PF
	 * device will act to set the VF token.
	 *
	 * If the VF token is provided but unused, an error is generated.
	 */
	अगर (!vdev->pdev->is_virtfn && !vdev->vf_token && !vf_token)
		वापस 0; /* No VF token provided or required */

	अगर (vdev->pdev->is_virtfn) अणु
		काष्ठा vfio_pci_device *pf_vdev = get_pf_vdev(vdev);
		bool match;

		अगर (!pf_vdev) अणु
			अगर (!vf_token)
				वापस 0; /* PF is not vfio-pci, no VF token */

			pci_info_ratelimited(vdev->pdev,
				"VF token incorrectly provided, PF not bound to vfio-pci\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!vf_token) अणु
			vfio_device_put(&pf_vdev->vdev);
			pci_info_ratelimited(vdev->pdev,
				"VF token required to access device\n");
			वापस -EACCES;
		पूर्ण

		mutex_lock(&pf_vdev->vf_token->lock);
		match = uuid_equal(uuid, &pf_vdev->vf_token->uuid);
		mutex_unlock(&pf_vdev->vf_token->lock);

		vfio_device_put(&pf_vdev->vdev);

		अगर (!match) अणु
			pci_info_ratelimited(vdev->pdev,
				"Incorrect VF token provided for device\n");
			वापस -EACCES;
		पूर्ण
	पूर्ण अन्यथा अगर (vdev->vf_token) अणु
		mutex_lock(&vdev->vf_token->lock);
		अगर (vdev->vf_token->users) अणु
			अगर (!vf_token) अणु
				mutex_unlock(&vdev->vf_token->lock);
				pci_info_ratelimited(vdev->pdev,
					"VF token required to access device\n");
				वापस -EACCES;
			पूर्ण

			अगर (!uuid_equal(uuid, &vdev->vf_token->uuid)) अणु
				mutex_unlock(&vdev->vf_token->lock);
				pci_info_ratelimited(vdev->pdev,
					"Incorrect VF token provided for device\n");
				वापस -EACCES;
			पूर्ण
		पूर्ण अन्यथा अगर (vf_token) अणु
			uuid_copy(&vdev->vf_token->uuid, uuid);
		पूर्ण

		mutex_unlock(&vdev->vf_token->lock);
	पूर्ण अन्यथा अगर (vf_token) अणु
		pci_info_ratelimited(vdev->pdev,
			"VF token incorrectly provided, not a PF or VF\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा VF_TOKEN_ARG "vf_token="

अटल पूर्णांक vfio_pci_match(काष्ठा vfio_device *core_vdev, अक्षर *buf)
अणु
	काष्ठा vfio_pci_device *vdev =
		container_of(core_vdev, काष्ठा vfio_pci_device, vdev);
	bool vf_token = false;
	uuid_t uuid;
	पूर्णांक ret;

	अगर (म_भेदन(pci_name(vdev->pdev), buf, म_माप(pci_name(vdev->pdev))))
		वापस 0; /* No match */

	अगर (म_माप(buf) > म_माप(pci_name(vdev->pdev))) अणु
		buf += म_माप(pci_name(vdev->pdev));

		अगर (*buf != ' ')
			वापस 0; /* No match: non-whitespace after name */

		जबतक (*buf) अणु
			अगर (*buf == ' ') अणु
				buf++;
				जारी;
			पूर्ण

			अगर (!vf_token && !म_भेदन(buf, VF_TOKEN_ARG,
						  म_माप(VF_TOKEN_ARG))) अणु
				buf += म_माप(VF_TOKEN_ARG);

				अगर (म_माप(buf) < UUID_STRING_LEN)
					वापस -EINVAL;

				ret = uuid_parse(buf, &uuid);
				अगर (ret)
					वापस ret;

				vf_token = true;
				buf += UUID_STRING_LEN;
			पूर्ण अन्यथा अणु
				/* Unknown/duplicate option */
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = vfio_pci_validate_vf_token(vdev, vf_token, &uuid);
	अगर (ret)
		वापस ret;

	वापस 1; /* Match */
पूर्ण

अटल स्थिर काष्ठा vfio_device_ops vfio_pci_ops = अणु
	.name		= "vfio-pci",
	.खोलो		= vfio_pci_खोलो,
	.release	= vfio_pci_release,
	.ioctl		= vfio_pci_ioctl,
	.पढ़ो		= vfio_pci_पढ़ो,
	.ग_लिखो		= vfio_pci_ग_लिखो,
	.mmap		= vfio_pci_mmap,
	.request	= vfio_pci_request,
	.match		= vfio_pci_match,
पूर्ण;

अटल पूर्णांक vfio_pci_reflck_attach(काष्ठा vfio_pci_device *vdev);
अटल व्योम vfio_pci_reflck_put(काष्ठा vfio_pci_reflck *reflck);

अटल पूर्णांक vfio_pci_bus_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा vfio_pci_device *vdev = container_of(nb,
						    काष्ठा vfio_pci_device, nb);
	काष्ठा device *dev = data;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_dev *physfn = pci_physfn(pdev);

	अगर (action == BUS_NOTIFY_ADD_DEVICE &&
	    pdev->is_virtfn && physfn == vdev->pdev) अणु
		pci_info(vdev->pdev, "Captured SR-IOV VF %s driver_override\n",
			 pci_name(pdev));
		pdev->driver_override = kaप्र_लिखो(GFP_KERNEL, "%s",
						  vfio_pci_ops.name);
	पूर्ण अन्यथा अगर (action == BUS_NOTIFY_BOUND_DRIVER &&
		   pdev->is_virtfn && physfn == vdev->pdev) अणु
		काष्ठा pci_driver *drv = pci_dev_driver(pdev);

		अगर (drv && drv != &vfio_pci_driver)
			pci_warn(vdev->pdev,
				 "VF %s bound to driver %s while PF bound to vfio-pci\n",
				 pci_name(pdev), drv->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_vf_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक ret;

	अगर (!pdev->is_physfn)
		वापस 0;

	vdev->vf_token = kzalloc(माप(*vdev->vf_token), GFP_KERNEL);
	अगर (!vdev->vf_token)
		वापस -ENOMEM;

	mutex_init(&vdev->vf_token->lock);
	uuid_gen(&vdev->vf_token->uuid);

	vdev->nb.notअगरier_call = vfio_pci_bus_notअगरier;
	ret = bus_रेजिस्टर_notअगरier(&pci_bus_type, &vdev->nb);
	अगर (ret) अणु
		kमुक्त(vdev->vf_token);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vfio_pci_vf_uninit(काष्ठा vfio_pci_device *vdev)
अणु
	अगर (!vdev->vf_token)
		वापस;

	bus_unरेजिस्टर_notअगरier(&pci_bus_type, &vdev->nb);
	WARN_ON(vdev->vf_token->users);
	mutex_destroy(&vdev->vf_token->lock);
	kमुक्त(vdev->vf_token);
पूर्ण

अटल पूर्णांक vfio_pci_vga_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक ret;

	अगर (!vfio_pci_is_vga(pdev))
		वापस 0;

	ret = vga_client_रेजिस्टर(pdev, vdev, शून्य, vfio_pci_set_vga_decode);
	अगर (ret)
		वापस ret;
	vga_set_legacy_decoding(pdev, vfio_pci_set_vga_decode(vdev, false));
	वापस 0;
पूर्ण

अटल व्योम vfio_pci_vga_uninit(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;

	अगर (!vfio_pci_is_vga(pdev))
		वापस;
	vga_client_रेजिस्टर(pdev, शून्य, शून्य, शून्य);
	vga_set_legacy_decoding(pdev, VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM |
					      VGA_RSRC_LEGACY_IO |
					      VGA_RSRC_LEGACY_MEM);
पूर्ण

अटल पूर्णांक vfio_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा vfio_pci_device *vdev;
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	अगर (vfio_pci_is_denylisted(pdev))
		वापस -EINVAL;

	अगर (pdev->hdr_type != PCI_HEADER_TYPE_NORMAL)
		वापस -EINVAL;

	/*
	 * Prevent binding to PFs with VFs enabled, the VFs might be in use
	 * by the host or other users.  We cannot capture the VFs अगर they
	 * alपढ़ोy exist, nor can we track VF users.  Disabling SR-IOV here
	 * would initiate removing the VFs, which would unbind the driver,
	 * which is prone to blocking अगर that VF is also in use by vfio-pci.
	 * Just reject these PFs and let the user sort it out.
	 */
	अगर (pci_num_vf(pdev)) अणु
		pci_warn(pdev, "Cannot bind to PF with SR-IOV enabled\n");
		वापस -EBUSY;
	पूर्ण

	group = vfio_iommu_group_get(&pdev->dev);
	अगर (!group)
		वापस -EINVAL;

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev) अणु
		ret = -ENOMEM;
		जाओ out_group_put;
	पूर्ण

	vfio_init_group_dev(&vdev->vdev, &pdev->dev, &vfio_pci_ops);
	vdev->pdev = pdev;
	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	mutex_init(&vdev->igate);
	spin_lock_init(&vdev->irqlock);
	mutex_init(&vdev->ioeventfds_lock);
	INIT_LIST_HEAD(&vdev->dummy_resources_list);
	INIT_LIST_HEAD(&vdev->ioeventfds_list);
	mutex_init(&vdev->vma_lock);
	INIT_LIST_HEAD(&vdev->vma_list);
	init_rwsem(&vdev->memory_lock);

	ret = vfio_pci_reflck_attach(vdev);
	अगर (ret)
		जाओ out_मुक्त;
	ret = vfio_pci_vf_init(vdev);
	अगर (ret)
		जाओ out_reflck;
	ret = vfio_pci_vga_init(vdev);
	अगर (ret)
		जाओ out_vf;

	vfio_pci_probe_घातer_state(vdev);

	अगर (!disable_idle_d3) अणु
		/*
		 * pci-core sets the device घातer state to an unknown value at
		 * bootup and after being हटाओd from a driver.  The only
		 * transition it allows from this unknown state is to D0, which
		 * typically happens when a driver calls pci_enable_device().
		 * We're not पढ़ोy to enable the device yet, but we करो want to
		 * be able to get to D3.  Thereक्रमe first करो a D0 transition
		 * beक्रमe going to D3.
		 */
		vfio_pci_set_घातer_state(vdev, PCI_D0);
		vfio_pci_set_घातer_state(vdev, PCI_D3hot);
	पूर्ण

	ret = vfio_रेजिस्टर_group_dev(&vdev->vdev);
	अगर (ret)
		जाओ out_घातer;
	dev_set_drvdata(&pdev->dev, vdev);
	वापस 0;

out_घातer:
	अगर (!disable_idle_d3)
		vfio_pci_set_घातer_state(vdev, PCI_D0);
out_vf:
	vfio_pci_vf_uninit(vdev);
out_reflck:
	vfio_pci_reflck_put(vdev->reflck);
out_मुक्त:
	kमुक्त(vdev->pm_save);
	kमुक्त(vdev);
out_group_put:
	vfio_iommu_group_put(group, &pdev->dev);
	वापस ret;
पूर्ण

अटल व्योम vfio_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vfio_pci_device *vdev = dev_get_drvdata(&pdev->dev);

	pci_disable_sriov(pdev);

	vfio_unरेजिस्टर_group_dev(&vdev->vdev);

	vfio_pci_vf_uninit(vdev);
	vfio_pci_reflck_put(vdev->reflck);
	vfio_pci_vga_uninit(vdev);

	vfio_iommu_group_put(pdev->dev.iommu_group, &pdev->dev);

	अगर (!disable_idle_d3)
		vfio_pci_set_घातer_state(vdev, PCI_D0);

	mutex_destroy(&vdev->ioeventfds_lock);
	kमुक्त(vdev->region);
	kमुक्त(vdev->pm_save);
	kमुक्त(vdev);
पूर्ण

अटल pci_ers_result_t vfio_pci_aer_err_detected(काष्ठा pci_dev *pdev,
						  pci_channel_state_t state)
अणु
	काष्ठा vfio_pci_device *vdev;
	काष्ठा vfio_device *device;

	device = vfio_device_get_from_dev(&pdev->dev);
	अगर (device == शून्य)
		वापस PCI_ERS_RESULT_DISCONNECT;

	vdev = container_of(device, काष्ठा vfio_pci_device, vdev);

	mutex_lock(&vdev->igate);

	अगर (vdev->err_trigger)
		eventfd_संकेत(vdev->err_trigger, 1);

	mutex_unlock(&vdev->igate);

	vfio_device_put(device);

	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल पूर्णांक vfio_pci_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक nr_virtfn)
अणु
	काष्ठा vfio_device *device;
	पूर्णांक ret = 0;

	might_sleep();

	अगर (!enable_sriov)
		वापस -ENOENT;

	device = vfio_device_get_from_dev(&pdev->dev);
	अगर (!device)
		वापस -ENODEV;

	अगर (nr_virtfn == 0)
		pci_disable_sriov(pdev);
	अन्यथा
		ret = pci_enable_sriov(pdev, nr_virtfn);

	vfio_device_put(device);

	वापस ret < 0 ? ret : nr_virtfn;
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers vfio_err_handlers = अणु
	.error_detected = vfio_pci_aer_err_detected,
पूर्ण;

अटल काष्ठा pci_driver vfio_pci_driver = अणु
	.name			= "vfio-pci",
	.id_table		= शून्य, /* only dynamic ids */
	.probe			= vfio_pci_probe,
	.हटाओ			= vfio_pci_हटाओ,
	.sriov_configure	= vfio_pci_sriov_configure,
	.err_handler		= &vfio_err_handlers,
पूर्ण;

अटल DEFINE_MUTEX(reflck_lock);

अटल काष्ठा vfio_pci_reflck *vfio_pci_reflck_alloc(व्योम)
अणु
	काष्ठा vfio_pci_reflck *reflck;

	reflck = kzalloc(माप(*reflck), GFP_KERNEL);
	अगर (!reflck)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&reflck->kref);
	mutex_init(&reflck->lock);

	वापस reflck;
पूर्ण

अटल व्योम vfio_pci_reflck_get(काष्ठा vfio_pci_reflck *reflck)
अणु
	kref_get(&reflck->kref);
पूर्ण

अटल पूर्णांक vfio_pci_reflck_find(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_pci_reflck **preflck = data;
	काष्ठा vfio_device *device;
	काष्ठा vfio_pci_device *vdev;

	device = vfio_device_get_from_dev(&pdev->dev);
	अगर (!device)
		वापस 0;

	अगर (pci_dev_driver(pdev) != &vfio_pci_driver) अणु
		vfio_device_put(device);
		वापस 0;
	पूर्ण

	vdev = container_of(device, काष्ठा vfio_pci_device, vdev);

	अगर (vdev->reflck) अणु
		vfio_pci_reflck_get(vdev->reflck);
		*preflck = vdev->reflck;
		vfio_device_put(device);
		वापस 1;
	पूर्ण

	vfio_device_put(device);
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_reflck_attach(काष्ठा vfio_pci_device *vdev)
अणु
	bool slot = !pci_probe_reset_slot(vdev->pdev->slot);

	mutex_lock(&reflck_lock);

	अगर (pci_is_root_bus(vdev->pdev->bus) ||
	    vfio_pci_क्रम_each_slot_or_bus(vdev->pdev, vfio_pci_reflck_find,
					  &vdev->reflck, slot) <= 0)
		vdev->reflck = vfio_pci_reflck_alloc();

	mutex_unlock(&reflck_lock);

	वापस PTR_ERR_OR_ZERO(vdev->reflck);
पूर्ण

अटल व्योम vfio_pci_reflck_release(काष्ठा kref *kref)
अणु
	काष्ठा vfio_pci_reflck *reflck = container_of(kref,
						      काष्ठा vfio_pci_reflck,
						      kref);

	kमुक्त(reflck);
	mutex_unlock(&reflck_lock);
पूर्ण

अटल व्योम vfio_pci_reflck_put(काष्ठा vfio_pci_reflck *reflck)
अणु
	kref_put_mutex(&reflck->kref, vfio_pci_reflck_release, &reflck_lock);
पूर्ण

अटल पूर्णांक vfio_pci_get_unused_devs(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_devices *devs = data;
	काष्ठा vfio_device *device;
	काष्ठा vfio_pci_device *vdev;

	अगर (devs->cur_index == devs->max_index)
		वापस -ENOSPC;

	device = vfio_device_get_from_dev(&pdev->dev);
	अगर (!device)
		वापस -EINVAL;

	अगर (pci_dev_driver(pdev) != &vfio_pci_driver) अणु
		vfio_device_put(device);
		वापस -EBUSY;
	पूर्ण

	vdev = container_of(device, काष्ठा vfio_pci_device, vdev);

	/* Fault अगर the device is not unused */
	अगर (vdev->refcnt) अणु
		vfio_device_put(device);
		वापस -EBUSY;
	पूर्ण

	devs->devices[devs->cur_index++] = vdev;
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pci_try_zap_and_vma_lock_cb(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	काष्ठा vfio_devices *devs = data;
	काष्ठा vfio_device *device;
	काष्ठा vfio_pci_device *vdev;

	अगर (devs->cur_index == devs->max_index)
		वापस -ENOSPC;

	device = vfio_device_get_from_dev(&pdev->dev);
	अगर (!device)
		वापस -EINVAL;

	अगर (pci_dev_driver(pdev) != &vfio_pci_driver) अणु
		vfio_device_put(device);
		वापस -EBUSY;
	पूर्ण

	vdev = container_of(device, काष्ठा vfio_pci_device, vdev);

	/*
	 * Locking multiple devices is prone to deadlock, runaway and
	 * unwind अगर we hit contention.
	 */
	अगर (!vfio_pci_zap_and_vma_lock(vdev, true)) अणु
		vfio_device_put(device);
		वापस -EBUSY;
	पूर्ण

	devs->devices[devs->cur_index++] = vdev;
	वापस 0;
पूर्ण

/*
 * If a bus or slot reset is available क्रम the provided device and:
 *  - All of the devices affected by that bus or slot reset are unused
 *    (!refcnt)
 *  - At least one of the affected devices is marked dirty via
 *    needs_reset (such as by lack of FLR support)
 * Then attempt to perक्रमm that bus or slot reset.  Callers are required
 * to hold vdev->reflck->lock, protecting the bus/slot reset group from
 * concurrent खोलोs.  A vfio_device reference is acquired क्रम each device
 * to prevent unbinds during the reset operation.
 *
 * NB: vfio-core considers a group to be viable even अगर some devices are
 * bound to drivers like pci-stub or pcieport.  Here we require all devices
 * to be bound to vfio_pci since that's the only way we can be sure they
 * stay put.
 */
अटल व्योम vfio_pci_try_bus_reset(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा vfio_devices devs = अणु .cur_index = 0 पूर्ण;
	पूर्णांक i = 0, ret = -EINVAL;
	bool slot = false;
	काष्ठा vfio_pci_device *पंचांगp;

	अगर (!pci_probe_reset_slot(vdev->pdev->slot))
		slot = true;
	अन्यथा अगर (pci_probe_reset_bus(vdev->pdev->bus))
		वापस;

	अगर (vfio_pci_क्रम_each_slot_or_bus(vdev->pdev, vfio_pci_count_devs,
					  &i, slot) || !i)
		वापस;

	devs.max_index = i;
	devs.devices = kसुस्मृति(i, माप(काष्ठा vfio_device *), GFP_KERNEL);
	अगर (!devs.devices)
		वापस;

	अगर (vfio_pci_क्रम_each_slot_or_bus(vdev->pdev,
					  vfio_pci_get_unused_devs,
					  &devs, slot))
		जाओ put_devs;

	/* Does at least one need a reset? */
	क्रम (i = 0; i < devs.cur_index; i++) अणु
		पंचांगp = devs.devices[i];
		अगर (पंचांगp->needs_reset) अणु
			ret = pci_reset_bus(vdev->pdev);
			अवरोध;
		पूर्ण
	पूर्ण

put_devs:
	क्रम (i = 0; i < devs.cur_index; i++) अणु
		पंचांगp = devs.devices[i];

		/*
		 * If reset was successful, affected devices no दीर्घer need
		 * a reset and we should वापस all the collateral devices
		 * to low घातer.  If not successful, we either didn't reset
		 * the bus or समयd out रुकोing क्रम it, so let's not touch
		 * the घातer state.
		 */
		अगर (!ret) अणु
			पंचांगp->needs_reset = false;

			अगर (पंचांगp != vdev && !disable_idle_d3)
				vfio_pci_set_घातer_state(पंचांगp, PCI_D3hot);
		पूर्ण

		vfio_device_put(&पंचांगp->vdev);
	पूर्ण

	kमुक्त(devs.devices);
पूर्ण

अटल व्योम __निकास vfio_pci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vfio_pci_driver);
	vfio_pci_uninit_perm_bits();
पूर्ण

अटल व्योम __init vfio_pci_fill_ids(व्योम)
अणु
	अक्षर *p, *id;
	पूर्णांक rc;

	/* no ids passed actually */
	अगर (ids[0] == '\0')
		वापस;

	/* add ids specअगरied in the module parameter */
	p = ids;
	जबतक ((id = strsep(&p, ","))) अणु
		अचिन्हित पूर्णांक venकरोr, device, subvenकरोr = PCI_ANY_ID,
			subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
		पूर्णांक fields;

		अगर (!म_माप(id))
			जारी;

		fields = माला_पूछो(id, "%x:%x:%x:%x:%x:%x",
				&venकरोr, &device, &subvenकरोr, &subdevice,
				&class, &class_mask);

		अगर (fields < 2) अणु
			pr_warn("invalid id string \"%s\"\n", id);
			जारी;
		पूर्ण

		rc = pci_add_dynid(&vfio_pci_driver, venकरोr, device,
				   subvenकरोr, subdevice, class, class_mask, 0);
		अगर (rc)
			pr_warn("failed to add dynamic id [%04x:%04x[%04x:%04x]] class %#08x/%08x (%d)\n",
				venकरोr, device, subvenकरोr, subdevice,
				class, class_mask, rc);
		अन्यथा
			pr_info("add [%04x:%04x[%04x:%04x]] class %#08x/%08x\n",
				venकरोr, device, subvenकरोr, subdevice,
				class, class_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक __init vfio_pci_init(व्योम)
अणु
	पूर्णांक ret;

	/* Allocate shared config space permission data used by all devices */
	ret = vfio_pci_init_perm_bits();
	अगर (ret)
		वापस ret;

	/* Register and scan क्रम devices */
	ret = pci_रेजिस्टर_driver(&vfio_pci_driver);
	अगर (ret)
		जाओ out_driver;

	vfio_pci_fill_ids();

	अगर (disable_denylist)
		pr_warn("device denylist disabled.\n");

	वापस 0;

out_driver:
	vfio_pci_uninit_perm_bits();
	वापस ret;
पूर्ण

module_init(vfio_pci_init);
module_निकास(vfio_pci_cleanup);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
