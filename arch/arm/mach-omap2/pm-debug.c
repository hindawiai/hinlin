<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP Power Management debug routines
 *
 * Copyright (C) 2005 Texas Instruments, Inc.
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Written by:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Tony Lindgren
 * Juha Yrjola
 * Amit Kucheria <amit.kucheria@nokia.com>
 * Igor Stoppa <igor.stoppa@nokia.com>
 * Jouni Hogander
 *
 * Based on pm.c क्रम omap2
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "clock.h"
#समावेश "powerdomain.h"
#समावेश "clockdomain.h"

#समावेश "soc.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "pm.h"

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक pm_dbg_init_करोne;

अटल पूर्णांक pm_dbg_init(व्योम);

अटल स्थिर अक्षर pwrdm_state_names[][PWRDM_MAX_PWRSTS] = अणु
	"OFF",
	"RET",
	"INA",
	"ON"
पूर्ण;

व्योम pm_dbg_update_समय(काष्ठा घातerकरोमुख्य *pwrdm, पूर्णांक prev)
अणु
	s64 t;

	अगर (!pm_dbg_init_करोne)
		वापस ;

	/* Update समयr क्रम previous state */
	t = sched_घड़ी();

	pwrdm->state_समयr[prev] += t - pwrdm->समयr;

	pwrdm->समयr = t;
पूर्ण

अटल पूर्णांक clkdm_dbg_show_counter(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *user)
अणु
	काष्ठा seq_file *s = (काष्ठा seq_file *)user;

	अगर (म_भेद(clkdm->name, "emu_clkdm") == 0 ||
		म_भेद(clkdm->name, "wkup_clkdm") == 0 ||
		म_भेदन(clkdm->name, "dpll", 4) == 0)
		वापस 0;

	seq_म_लिखो(s, "%s->%s (%d)\n", clkdm->name, clkdm->pwrdm.ptr->name,
		   clkdm->usecount);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrdm_dbg_show_counter(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *user)
अणु
	काष्ठा seq_file *s = (काष्ठा seq_file *)user;
	पूर्णांक i;

	अगर (म_भेद(pwrdm->name, "emu_pwrdm") == 0 ||
		म_भेद(pwrdm->name, "wkup_pwrdm") == 0 ||
		म_भेदन(pwrdm->name, "dpll", 4) == 0)
		वापस 0;

	अगर (pwrdm->state != pwrdm_पढ़ो_pwrst(pwrdm))
		prपूर्णांकk(KERN_ERR "pwrdm state mismatch(%s) %d != %d\n",
			pwrdm->name, pwrdm->state, pwrdm_पढ़ो_pwrst(pwrdm));

	seq_म_लिखो(s, "%s (%s)", pwrdm->name,
			pwrdm_state_names[pwrdm->state]);
	क्रम (i = 0; i < PWRDM_MAX_PWRSTS; i++)
		seq_म_लिखो(s, ",%s:%d", pwrdm_state_names[i],
			pwrdm->state_counter[i]);

	seq_म_लिखो(s, ",RET-LOGIC-OFF:%d", pwrdm->ret_logic_off_counter);
	क्रम (i = 0; i < pwrdm->banks; i++)
		seq_म_लिखो(s, ",RET-MEMBANK%d-OFF:%d", i + 1,
				pwrdm->ret_mem_off_counter[i]);

	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक pwrdm_dbg_show_समयr(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *user)
अणु
	काष्ठा seq_file *s = (काष्ठा seq_file *)user;
	पूर्णांक i;

	अगर (म_भेद(pwrdm->name, "emu_pwrdm") == 0 ||
		म_भेद(pwrdm->name, "wkup_pwrdm") == 0 ||
		म_भेदन(pwrdm->name, "dpll", 4) == 0)
		वापस 0;

	pwrdm_state_चयन(pwrdm);

	seq_म_लिखो(s, "%s (%s)", pwrdm->name,
		pwrdm_state_names[pwrdm->state]);

	क्रम (i = 0; i < 4; i++)
		seq_म_लिखो(s, ",%s:%lld", pwrdm_state_names[i],
			pwrdm->state_समयr[i]);

	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक pm_dbg_counters_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	pwrdm_क्रम_each(pwrdm_dbg_show_counter, s);
	clkdm_क्रम_each(clkdm_dbg_show_counter, s);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pm_dbg_counters);

अटल पूर्णांक pm_dbg_समयrs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	pwrdm_क्रम_each(pwrdm_dbg_show_समयr, s);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pm_dbg_समयrs);

अटल पूर्णांक pwrdm_suspend_get(व्योम *data, u64 *val)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (cpu_is_omap34xx())
		ret = omap3_pm_get_suspend_state((काष्ठा घातerकरोमुख्य *)data);
	*val = ret;

	अगर (ret >= 0)
		वापस 0;
	वापस *val;
पूर्ण

अटल पूर्णांक pwrdm_suspend_set(व्योम *data, u64 val)
अणु
	अगर (cpu_is_omap34xx())
		वापस omap3_pm_set_suspend_state(
			(काष्ठा घातerकरोमुख्य *)data, (पूर्णांक)val);
	वापस -EINVAL;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(pwrdm_suspend_fops, pwrdm_suspend_get,
			  pwrdm_suspend_set, "%llu\n");

अटल पूर्णांक __init pwrdms_setup(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *dir)
अणु
	पूर्णांक i;
	s64 t;
	काष्ठा dentry *d;

	t = sched_घड़ी();

	क्रम (i = 0; i < 4; i++)
		pwrdm->state_समयr[i] = 0;

	pwrdm->समयr = t;

	अगर (म_भेदन(pwrdm->name, "dpll", 4) == 0)
		वापस 0;

	d = debugfs_create_dir(pwrdm->name, (काष्ठा dentry *)dir);
	debugfs_create_file("suspend", S_IRUGO|S_IWUSR, d, pwrdm,
			    &pwrdm_suspend_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक option_get(व्योम *data, u64 *val)
अणु
	u32 *option = data;

	*val = *option;

	वापस 0;
पूर्ण

अटल पूर्णांक option_set(व्योम *data, u64 val)
अणु
	u32 *option = data;

	*option = val;

	अगर (option == &enable_off_mode) अणु
		अगर (cpu_is_omap34xx())
			omap3_pm_off_mode_enable(val);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(pm_dbg_option_fops, option_get, option_set, "%llu\n");

अटल पूर्णांक __init pm_dbg_init(व्योम)
अणु
	काष्ठा dentry *d;

	अगर (pm_dbg_init_करोne)
		वापस 0;

	d = debugfs_create_dir("pm_debug", शून्य);

	debugfs_create_file("count", 0444, d, शून्य, &pm_dbg_counters_fops);
	debugfs_create_file("time", 0444, d, शून्य, &pm_dbg_समयrs_fops);

	pwrdm_क्रम_each(pwrdms_setup, (व्योम *)d);

	debugfs_create_file("enable_off_mode", S_IRUGO | S_IWUSR, d,
			    &enable_off_mode, &pm_dbg_option_fops);
	pm_dbg_init_करोne = 1;

	वापस 0;
पूर्ण
omap_arch_initcall(pm_dbg_init);

#पूर्ण_अगर
