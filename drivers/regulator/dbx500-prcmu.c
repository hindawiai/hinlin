<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Authors: Sundar Iyer <sundar.iyer@stericsson.com> क्रम ST-Ericsson
 *          Bengt Jonsson <bengt.g.jonsson@stericsson.com> क्रम ST-Ericsson
 *
 * UX500 common part of Power करोमुख्य regulators
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "dbx500-prcmu.h"

/*
 * घातer state reference count
 */
अटल पूर्णांक घातer_state_active_cnt; /* will initialize to zero */
अटल DEFINE_SPINLOCK(घातer_state_active_lock);

व्योम घातer_state_active_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घातer_state_active_lock, flags);
	घातer_state_active_cnt++;
	spin_unlock_irqrestore(&घातer_state_active_lock, flags);
पूर्ण

पूर्णांक घातer_state_active_disable(व्योम)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घातer_state_active_lock, flags);
	अगर (घातer_state_active_cnt <= 0) अणु
		pr_err("power state: unbalanced enable/disable calls\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	घातer_state_active_cnt--;
out:
	spin_unlock_irqrestore(&घातer_state_active_lock, flags);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_REGULATOR_DEBUG

अटल पूर्णांक घातer_state_active_get(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cnt;

	spin_lock_irqsave(&घातer_state_active_lock, flags);
	cnt = घातer_state_active_cnt;
	spin_unlock_irqrestore(&घातer_state_active_lock, flags);

	वापस cnt;
पूर्ण

अटल काष्ठा ux500_regulator_debug अणु
	काष्ठा dentry *dir;
	काष्ठा dbx500_regulator_info *regulator_array;
	पूर्णांक num_regulators;
	u8 *state_beक्रमe_suspend;
	u8 *state_after_suspend;
पूर्ण rdebug;

अटल पूर्णांक ux500_regulator_घातer_state_cnt_show(काष्ठा seq_file *s, व्योम *p)
अणु
	/* prपूर्णांक घातer state count */
	seq_म_लिखो(s, "ux500-regulator power state count: %i\n",
		   घातer_state_active_get());

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ux500_regulator_घातer_state_cnt);

अटल पूर्णांक ux500_regulator_status_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक i;

	/* prपूर्णांक dump header */
	seq_माला_दो(s, "ux500-regulator status:\n");
	seq_म_लिखो(s, "%31s : %8s : %8s\n", "current", "before", "after");

	क्रम (i = 0; i < rdebug.num_regulators; i++) अणु
		काष्ठा dbx500_regulator_info *info;
		/* Access per-regulator data */
		info = &rdebug.regulator_array[i];

		/* prपूर्णांक status */
		seq_म_लिखो(s, "%20s : %8s : %8s : %8s\n",
			   info->desc.name,
			   info->is_enabled ? "enabled" : "disabled",
			   rdebug.state_beक्रमe_suspend[i] ? "enabled" : "disabled",
			   rdebug.state_after_suspend[i] ? "enabled" : "disabled");
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ux500_regulator_status);

पूर्णांक
ux500_regulator_debug_init(काष्ठा platक्रमm_device *pdev,
	काष्ठा dbx500_regulator_info *regulator_info,
	पूर्णांक num_regulators)
अणु
	/* create directory */
	rdebug.dir = debugfs_create_dir("ux500-regulator", शून्य);

	/* create "status" file */
	debugfs_create_file("status", S_IRUGO, rdebug.dir, &pdev->dev,
			    &ux500_regulator_status_fops);

	/* create "power-state-count" file */
	debugfs_create_file("power-state-count", S_IRUGO, rdebug.dir,
			    &pdev->dev, &ux500_regulator_घातer_state_cnt_fops);

	rdebug.regulator_array = regulator_info;
	rdebug.num_regulators = num_regulators;

	rdebug.state_beक्रमe_suspend = kzalloc(num_regulators, GFP_KERNEL);
	अगर (!rdebug.state_beक्रमe_suspend)
		जाओ निकास_destroy_घातer_state;

	rdebug.state_after_suspend = kzalloc(num_regulators, GFP_KERNEL);
	अगर (!rdebug.state_after_suspend)
		जाओ निकास_मुक्त;

	वापस 0;

निकास_मुक्त:
	kमुक्त(rdebug.state_beक्रमe_suspend);
निकास_destroy_घातer_state:
	debugfs_हटाओ_recursive(rdebug.dir);
	वापस -ENOMEM;
पूर्ण

पूर्णांक ux500_regulator_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(rdebug.dir);
	kमुक्त(rdebug.state_after_suspend);
	kमुक्त(rdebug.state_beक्रमe_suspend);

	वापस 0;
पूर्ण
#पूर्ण_अगर
