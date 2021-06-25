<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_device headers
 *
 * Copyright (C) 2009 Nokia Corporation
 * Paul Walmsley
 *
 * Developed in collaboration with (alphabetical order): Benoit
 * Cousson, Kevin Hilman, Tony Lindgren, Rajendra Nayak, Vikram
 * Pandita, Sakari Poussa, Anand Sawant, Santosh Shilimkar, Riअक्षरd
 * Woodruff
 *
 * This type of functionality should be implemented as a proper
 * omap_bus/omap_device in Linux.
 *
 * omap_device dअगरfers from omap_hwmod in that it includes बाह्यal
 * (e.g., board- and प्रणाली-level) पूर्णांकegration details.  omap_hwmod
 * stores hardware data that is invariant क्रम a given OMAP chip.
 */
#अगर_अघोषित __ARCH_ARM_PLAT_OMAP_INCLUDE_MACH_OMAP_DEVICE_H
#घोषणा __ARCH_ARM_PLAT_OMAP_INCLUDE_MACH_OMAP_DEVICE_H

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "omap_hwmod.h"

बाह्य काष्ठा dev_pm_करोमुख्य omap_device_pm_करोमुख्य;
बाह्य काष्ठा dev_pm_करोमुख्य omap_device_fail_pm_करोमुख्य;

/* omap_device._state values */
#घोषणा OMAP_DEVICE_STATE_UNKNOWN	0
#घोषणा OMAP_DEVICE_STATE_ENABLED	1
#घोषणा OMAP_DEVICE_STATE_IDLE		2
#घोषणा OMAP_DEVICE_STATE_SHUTDOWN	3

/* omap_device.flags values */
#घोषणा OMAP_DEVICE_SUSPENDED		BIT(0)

/**
 * काष्ठा omap_device - omap_device wrapper क्रम platक्रमm_devices
 * @pdev: platक्रमm_device
 * @hwmods: (one .. many per omap_device)
 * @hwmods_cnt: ARRAY_SIZE() of @hwmods
 * @_state: one of OMAP_DEVICE_STATE_* (see above)
 * @flags: device flags
 * @_driver_status: one of BUS_NOTIFY_*_DRIVER from <linux/device.h>
 *
 * Integrates omap_hwmod data पूर्णांकo Linux platक्रमm_device.
 *
 * Field names beginning with underscores are क्रम the पूर्णांकernal use of
 * the omap_device code.
 *
 */
काष्ठा omap_device अणु
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा omap_hwmod		**hwmods;
	अचिन्हित दीर्घ			_driver_status;
	u8				hwmods_cnt;
	u8				_state;
	u8                              flags;
पूर्ण;

/* Device driver पूर्णांकerface (call via platक्रमm_data fn ptrs) */

पूर्णांक omap_device_enable(काष्ठा platक्रमm_device *pdev);
पूर्णांक omap_device_idle(काष्ठा platक्रमm_device *pdev);

/* Core code पूर्णांकerface */

काष्ठा omap_device *omap_device_alloc(काष्ठा platक्रमm_device *pdev,
				      काष्ठा omap_hwmod **ohs, पूर्णांक oh_cnt);
व्योम omap_device_delete(काष्ठा omap_device *od);
पूर्णांक omap_device_रेजिस्टर(काष्ठा platक्रमm_device *pdev);

काष्ठा device *omap_device_get_by_hwmod_name(स्थिर अक्षर *oh_name);

/* OMAP PM पूर्णांकerface */
पूर्णांक omap_device_get_context_loss_count(काष्ठा platक्रमm_device *pdev);

/* Other */

पूर्णांक omap_device_निश्चित_hardreset(काष्ठा platक्रमm_device *pdev,
				 स्थिर अक्षर *name);
पूर्णांक omap_device_deनिश्चित_hardreset(काष्ठा platक्रमm_device *pdev,
				 स्थिर अक्षर *name);

/* Get omap_device poपूर्णांकer from platक्रमm_device poपूर्णांकer */
अटल अंतरभूत काष्ठा omap_device *to_omap_device(काष्ठा platक्रमm_device *pdev)
अणु
	वापस pdev ? pdev->archdata.od : शून्य;
पूर्ण
#पूर्ण_अगर
