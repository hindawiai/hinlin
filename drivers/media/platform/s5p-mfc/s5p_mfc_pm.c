<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_pm.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_pm.h"

अटल काष्ठा s5p_mfc_pm *pm;
अटल काष्ठा s5p_mfc_dev *p_dev;
अटल atomic_t clk_ref;

पूर्णांक s5p_mfc_init_pm(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक i;

	pm = &dev->pm;
	p_dev = dev;

	pm->num_घड़ीs = dev->variant->num_घड़ीs;
	pm->clk_names = dev->variant->clk_names;
	pm->device = &dev->plat_dev->dev;
	pm->घड़ी_gate = शून्य;

	/* घड़ी control */
	क्रम (i = 0; i < pm->num_घड़ीs; i++) अणु
		pm->घड़ीs[i] = devm_clk_get(pm->device, pm->clk_names[i]);
		अगर (IS_ERR(pm->घड़ीs[i])) अणु
			/* additional घड़ीs are optional */
			अगर (i && PTR_ERR(pm->घड़ीs[i]) == -ENOENT) अणु
				pm->घड़ीs[i] = शून्य;
				जारी;
			पूर्ण
			mfc_err("Failed to get clock: %s\n",
				pm->clk_names[i]);
			वापस PTR_ERR(pm->घड़ीs[i]);
		पूर्ण
	पूर्ण

	अगर (dev->variant->use_घड़ी_gating)
		pm->घड़ी_gate = pm->घड़ीs[0];

	pm_runसमय_enable(pm->device);
	atomic_set(&clk_ref, 0);
	वापस 0;
पूर्ण

व्योम s5p_mfc_final_pm(काष्ठा s5p_mfc_dev *dev)
अणु
	pm_runसमय_disable(pm->device);
पूर्ण

पूर्णांक s5p_mfc_घड़ी_on(व्योम)
अणु
	atomic_inc(&clk_ref);
	mfc_debug(3, "+ %d\n", atomic_पढ़ो(&clk_ref));

	वापस clk_enable(pm->घड़ी_gate);
पूर्ण

व्योम s5p_mfc_घड़ी_off(व्योम)
अणु
	atomic_dec(&clk_ref);
	mfc_debug(3, "- %d\n", atomic_पढ़ो(&clk_ref));

	clk_disable(pm->घड़ी_gate);
पूर्ण

पूर्णांक s5p_mfc_घातer_on(व्योम)
अणु
	पूर्णांक i, ret = 0;

	ret = pm_runसमय_get_sync(pm->device);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(pm->device);
		वापस ret;
	पूर्ण

	/* घड़ी control */
	क्रम (i = 0; i < pm->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(pm->घड़ीs[i]);
		अगर (ret < 0) अणु
			mfc_err("clock prepare failed for clock: %s\n",
				pm->clk_names[i]);
			i++;
			जाओ err;
		पूर्ण
	पूर्ण

	/* prepare क्रम software घड़ी gating */
	clk_disable(pm->घड़ी_gate);

	वापस 0;
err:
	जबतक (--i > 0)
		clk_disable_unprepare(pm->घड़ीs[i]);
	pm_runसमय_put(pm->device);
	वापस ret;
पूर्ण

पूर्णांक s5p_mfc_घातer_off(व्योम)
अणु
	पूर्णांक i;

	/* finish software घड़ी gating */
	clk_enable(pm->घड़ी_gate);

	क्रम (i = 0; i < pm->num_घड़ीs; i++)
		clk_disable_unprepare(pm->घड़ीs[i]);

	वापस pm_runसमय_put_sync(pm->device);
पूर्ण

