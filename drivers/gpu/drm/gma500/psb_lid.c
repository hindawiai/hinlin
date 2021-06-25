<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2007, Intel Corporation.
 *
 * Authors: Thomas Hellstrom <thomas-at-tungstengraphics-करोt-com>
 **************************************************************************/

#समावेश <linux/spinlock.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_reg.h"

अटल व्योम psb_lid_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा drm_psb_निजी *dev_priv = from_समयr(dev_priv, t, lid_समयr);
	काष्ठा drm_device *dev = (काष्ठा drm_device *)dev_priv->dev;
	काष्ठा समयr_list *lid_समयr = &dev_priv->lid_समयr;
	अचिन्हित दीर्घ irq_flags;
	u32 __iomem *lid_state = dev_priv->opregion.lid_state;
	u32 pp_status;

	अगर (पढ़ोl(lid_state) == dev_priv->lid_last_state)
		जाओ lid_समयr_schedule;

	अगर ((पढ़ोl(lid_state)) & 0x01) अणु
		/*lid state is खोलो*/
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) | POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & PP_ON) == 0 &&
			 (pp_status & PP_SEQUENCE_MASK) != 0);

		अगर (REG_READ(PP_STATUS) & PP_ON) अणु
			/*FIXME: should be backlight level beक्रमe*/
			psb_पूर्णांकel_lvds_set_brightness(dev, 100);
		पूर्ण अन्यथा अणु
			DRM_DEBUG("LVDS panel never powered up");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		psb_पूर्णांकel_lvds_set_brightness(dev, 0);

		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) & ~POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & PP_ON) == 0);
	पूर्ण
	dev_priv->lid_last_state =  पढ़ोl(lid_state);

lid_समयr_schedule:
	spin_lock_irqsave(&dev_priv->lid_lock, irq_flags);
	अगर (!समयr_pending(lid_समयr)) अणु
		lid_समयr->expires = jअगरfies + PSB_LID_DELAY;
		add_समयr(lid_समयr);
	पूर्ण
	spin_unlock_irqrestore(&dev_priv->lid_lock, irq_flags);
पूर्ण

व्योम psb_lid_समयr_init(काष्ठा drm_psb_निजी *dev_priv)
अणु
	काष्ठा समयr_list *lid_समयr = &dev_priv->lid_समयr;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_init(&dev_priv->lid_lock);
	spin_lock_irqsave(&dev_priv->lid_lock, irq_flags);

	समयr_setup(lid_समयr, psb_lid_समयr_func, 0);

	lid_समयr->expires = jअगरfies + PSB_LID_DELAY;

	add_समयr(lid_समयr);
	spin_unlock_irqrestore(&dev_priv->lid_lock, irq_flags);
पूर्ण

व्योम psb_lid_समयr_takeकरोwn(काष्ठा drm_psb_निजी *dev_priv)
अणु
	del_समयr_sync(&dev_priv->lid_समयr);
पूर्ण

