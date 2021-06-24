<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/pci.h>
#समावेश <linux/vgaarb.h>

#समावेश <drm/i915_drm.h>

#समावेश "i915_drv.h"
#समावेश "intel_de.h"
#समावेश "intel_vga.h"

अटल i915_reg_t पूर्णांकel_vga_cntrl_reg(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		वापस VLV_VGACNTRL;
	अन्यथा अगर (DISPLAY_VER(i915) >= 5)
		वापस CPU_VGACNTRL;
	अन्यथा
		वापस VGACNTRL;
पूर्ण

/* Disable the VGA plane that we never use */
व्योम पूर्णांकel_vga_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	i915_reg_t vga_reg = पूर्णांकel_vga_cntrl_reg(dev_priv);
	u8 sr1;

	/* WaEnableVGAAccessThroughIOPort:ctg,elk,ilk,snb,ivb,vlv,hsw */
	vga_get_unपूर्णांकerruptible(pdev, VGA_RSRC_LEGACY_IO);
	outb(SR01, VGA_SR_INDEX);
	sr1 = inb(VGA_SR_DATA);
	outb(sr1 | 1 << 5, VGA_SR_DATA);
	vga_put(pdev, VGA_RSRC_LEGACY_IO);
	udelay(300);

	पूर्णांकel_de_ग_लिखो(dev_priv, vga_reg, VGA_DISP_DISABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, vga_reg);
पूर्ण

व्योम पूर्णांकel_vga_redisable_घातer_on(काष्ठा drm_i915_निजी *dev_priv)
अणु
	i915_reg_t vga_reg = पूर्णांकel_vga_cntrl_reg(dev_priv);

	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, vga_reg) & VGA_DISP_DISABLE)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Something enabled VGA plane, disabling it\n");
		पूर्णांकel_vga_disable(dev_priv);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_vga_redisable(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * This function can be called both from पूर्णांकel_modeset_setup_hw_state or
	 * at a very early poपूर्णांक in our resume sequence, where the घातer well
	 * काष्ठाures are not yet restored. Since this function is at a very
	 * paranoid "someone might have enabled VGA while we were not looking"
	 * level, just check अगर the घातer well is enabled instead of trying to
	 * follow the "don't touch the power well if we don't need it" policy
	 * the rest of the driver uses.
	 */
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(i915, POWER_DOMAIN_VGA);
	अगर (!wakeref)
		वापस;

	पूर्णांकel_vga_redisable_घातer_on(i915);

	पूर्णांकel_display_घातer_put(i915, POWER_DOMAIN_VGA, wakeref);
पूर्ण

व्योम पूर्णांकel_vga_reset_io_mem(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	/*
	 * After we re-enable the घातer well, अगर we touch VGA रेजिस्टर 0x3d5
	 * we'll get unclaimed रेजिस्टर पूर्णांकerrupts. This stops after we ग_लिखो
	 * anything to the VGA MSR रेजिस्टर. The vgacon module uses this
	 * रेजिस्टर all the समय, so अगर we unbind our driver and, as a
	 * consequence, bind vgacon, we'll get stuck in an infinite loop at
	 * console_unlock(). So make here we touch the VGA MSR रेजिस्टर, making
	 * sure vgacon can keep working normally without triggering पूर्णांकerrupts
	 * and error messages.
	 */
	vga_get_unपूर्णांकerruptible(pdev, VGA_RSRC_LEGACY_IO);
	outb(inb(VGA_MSR_READ), VGA_MSR_WRITE);
	vga_put(pdev, VGA_RSRC_LEGACY_IO);
पूर्ण

अटल पूर्णांक
पूर्णांकel_vga_set_state(काष्ठा drm_i915_निजी *i915, bool enable_decode)
अणु
	अचिन्हित पूर्णांक reg = DISPLAY_VER(i915) >= 6 ? SNB_GMCH_CTRL : INTEL_GMCH_CTRL;
	u16 gmch_ctrl;

	अगर (pci_पढ़ो_config_word(i915->bridge_dev, reg, &gmch_ctrl)) अणु
		drm_err(&i915->drm, "failed to read control word\n");
		वापस -EIO;
	पूर्ण

	अगर (!!(gmch_ctrl & INTEL_GMCH_VGA_DISABLE) == !enable_decode)
		वापस 0;

	अगर (enable_decode)
		gmch_ctrl &= ~INTEL_GMCH_VGA_DISABLE;
	अन्यथा
		gmch_ctrl |= INTEL_GMCH_VGA_DISABLE;

	अगर (pci_ग_लिखो_config_word(i915->bridge_dev, reg, gmch_ctrl)) अणु
		drm_err(&i915->drm, "failed to write control word\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
पूर्णांकel_vga_set_decode(व्योम *cookie, bool enable_decode)
अणु
	काष्ठा drm_i915_निजी *i915 = cookie;

	पूर्णांकel_vga_set_state(i915, enable_decode);

	अगर (enable_decode)
		वापस VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
		       VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
	अन्यथा
		वापस VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;
पूर्ण

पूर्णांक पूर्णांकel_vga_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	पूर्णांक ret;

	/*
	 * If we have > 1 VGA cards, then we need to arbitrate access to the
	 * common VGA resources.
	 *
	 * If we are a secondary display controller (!PCI_DISPLAY_CLASS_VGA),
	 * then we करो not take part in VGA arbitration and the
	 * vga_client_रेजिस्टर() fails with -ENODEV.
	 */
	ret = vga_client_रेजिस्टर(pdev, i915, शून्य, पूर्णांकel_vga_set_decode);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_vga_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	vga_client_रेजिस्टर(pdev, शून्य, शून्य, शून्य);
पूर्ण
