<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <linux/vgaarb.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_acpi.h"
#समावेश "nouveau_fbcon.h"
#समावेश "nouveau_vga.h"

अटल अचिन्हित पूर्णांक
nouveau_vga_set_decode(व्योम *priv, bool state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(priv);
	काष्ठा nvअगर_object *device = &drm->client.device.object;

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE &&
	    drm->client.device.info.chipset >= 0x4c)
		nvअगर_wr32(device, 0x088060, state);
	अन्यथा
	अगर (drm->client.device.info.chipset >= 0x40)
		nvअगर_wr32(device, 0x088054, state);
	अन्यथा
		nvअगर_wr32(device, 0x001854, state);

	अगर (state)
		वापस VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
		       VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
	अन्यथा
		वापस VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
पूर्ण

अटल व्योम
nouveau_चयनeroo_set_state(काष्ठा pci_dev *pdev,
			     क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	अगर ((nouveau_is_optimus() || nouveau_is_v1_dsm()) && state == VGA_SWITCHEROO_OFF)
		वापस;

	अगर (state == VGA_SWITCHEROO_ON) अणु
		pr_err("VGA switcheroo: switched nouveau on\n");
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		nouveau_pmops_resume(&pdev->dev);
		dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;
	पूर्ण अन्यथा अणु
		pr_err("VGA switcheroo: switched nouveau off\n");
		dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		nouveau_चयनeroo_optimus_dsm();
		nouveau_pmops_suspend(&pdev->dev);
		dev->चयन_घातer_state = DRM_SWITCH_POWER_OFF;
	पूर्ण
पूर्ण

अटल व्योम
nouveau_चयनeroo_reprobe(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	drm_fb_helper_output_poll_changed(dev);
पूर्ण

अटल bool
nouveau_चयनeroo_can_चयन(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	/*
	 * FIXME: खोलो_count is रक्षित by drm_global_mutex but that would lead to
	 * locking inversion with the driver load path. And the access here is
	 * completely racy anyway. So करोn't bother with locking क्रम now.
	 */
	वापस atomic_पढ़ो(&dev->खोलो_count) == 0;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_client_ops
nouveau_चयनeroo_ops = अणु
	.set_gpu_state = nouveau_चयनeroo_set_state,
	.reprobe = nouveau_चयनeroo_reprobe,
	.can_चयन = nouveau_चयनeroo_can_चयन,
पूर्ण;

व्योम
nouveau_vga_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा drm_device *dev = drm->dev;
	bool runसमय = nouveau_pmops_runसमय();
	काष्ठा pci_dev *pdev;

	/* only relevant क्रम PCI devices */
	अगर (!dev_is_pci(dev->dev))
		वापस;
	pdev = to_pci_dev(dev->dev);

	vga_client_रेजिस्टर(pdev, dev, शून्य, nouveau_vga_set_decode);

	/* करोn't रेजिस्टर Thunderbolt eGPU with vga_चयनeroo */
	अगर (pci_is_thunderbolt_attached(pdev))
		वापस;

	vga_चयनeroo_रेजिस्टर_client(pdev, &nouveau_चयनeroo_ops, runसमय);

	अगर (runसमय && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_चयनeroo_init_करोमुख्य_pm_ops(drm->dev->dev, &drm->vga_pm_करोमुख्य);
पूर्ण

व्योम
nouveau_vga_fini(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा drm_device *dev = drm->dev;
	bool runसमय = nouveau_pmops_runसमय();
	काष्ठा pci_dev *pdev;

	/* only relevant क्रम PCI devices */
	अगर (!dev_is_pci(dev->dev))
		वापस;
	pdev = to_pci_dev(dev->dev);

	vga_client_रेजिस्टर(pdev, शून्य, शून्य, शून्य);

	अगर (pci_is_thunderbolt_attached(pdev))
		वापस;

	vga_चयनeroo_unरेजिस्टर_client(pdev);
	अगर (runसमय && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_चयनeroo_fini_करोमुख्य_pm_ops(drm->dev->dev);
पूर्ण


व्योम
nouveau_vga_lastबंद(काष्ठा drm_device *dev)
अणु
	vga_चयनeroo_process_delayed_चयन();
पूर्ण
