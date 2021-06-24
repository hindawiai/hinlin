<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/vga_चयनeroo.h>

#समावेश "i915_drv.h"
#समावेश "i915_switcheroo.h"

अटल व्योम i915_चयनeroo_set_state(काष्ठा pci_dev *pdev,
				      क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा drm_i915_निजी *i915 = pdev_to_i915(pdev);
	pm_message_t pmm = अणु .event = PM_EVENT_SUSPEND पूर्ण;

	अगर (!i915) अणु
		dev_err(&pdev->dev, "DRM not initialized, aborting switch.\n");
		वापस;
	पूर्ण

	अगर (state == VGA_SWITCHEROO_ON) अणु
		drm_info(&i915->drm, "switched on\n");
		i915->drm.चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		/* i915 resume handler करोesn't set to D0 */
		pci_set_घातer_state(pdev, PCI_D0);
		i915_resume_चयनeroo(i915);
		i915->drm.चयन_घातer_state = DRM_SWITCH_POWER_ON;
	पूर्ण अन्यथा अणु
		drm_info(&i915->drm, "switched off\n");
		i915->drm.चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
		i915_suspend_चयनeroo(i915, pmm);
		i915->drm.चयन_घातer_state = DRM_SWITCH_POWER_OFF;
	पूर्ण
पूर्ण

अटल bool i915_चयनeroo_can_चयन(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_i915_निजी *i915 = pdev_to_i915(pdev);

	/*
	 * FIXME: खोलो_count is रक्षित by drm_global_mutex but that would lead to
	 * locking inversion with the driver load path. And the access here is
	 * completely racy anyway. So करोn't bother with locking क्रम now.
	 */
	वापस i915 && atomic_पढ़ो(&i915->drm.खोलो_count) == 0;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_client_ops i915_चयनeroo_ops = अणु
	.set_gpu_state = i915_चयनeroo_set_state,
	.reprobe = शून्य,
	.can_चयन = i915_चयनeroo_can_चयन,
पूर्ण;

पूर्णांक i915_चयनeroo_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	वापस vga_चयनeroo_रेजिस्टर_client(pdev, &i915_चयनeroo_ops, false);
पूर्ण

व्योम i915_चयनeroo_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	vga_चयनeroo_unरेजिस्टर_client(pdev);
पूर्ण
