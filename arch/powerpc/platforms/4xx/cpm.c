<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerPC 4xx Clock and Power Management
 *
 * Copyright (C) 2010, Applied Micro Circuits Corporation
 * Victor Gallarकरो (vgallarकरो@apm.com)
 *
 * Based on arch/घातerpc/platक्रमms/44x/idle.c:
 * Jerone Young <jyoung5@us.ibm.com>
 * Copyright 2008 IBM Corp.
 *
 * Based on arch/घातerpc/sysdev/fsl_pmc.c:
 * Anton Vorontsov <avorontsov@ru.mvista.com>
 * Copyright 2009  MontaVista Software, Inc.
 *
 * See file CREDITS क्रम list of people who contributed to this
 * project.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/cpu.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-native.h>
#समावेश <यंत्र/machdep.h>

#घोषणा CPM_ER	0
#घोषणा CPM_FR	1
#घोषणा CPM_SR	2

#घोषणा CPM_IDLE_WAIT	0
#घोषणा CPM_IDLE_DOZE	1

काष्ठा cpm अणु
	dcr_host_t	dcr_host;
	अचिन्हित पूर्णांक	dcr_offset[3];
	अचिन्हित पूर्णांक	घातersave_off;
	अचिन्हित पूर्णांक	unused;
	अचिन्हित पूर्णांक	idle_करोze;
	अचिन्हित पूर्णांक	standby;
	अचिन्हित पूर्णांक	suspend;
पूर्ण;

अटल काष्ठा cpm cpm;

काष्ठा cpm_idle_mode अणु
	अचिन्हित पूर्णांक enabled;
	स्थिर अक्षर  *name;
पूर्ण;

अटल काष्ठा cpm_idle_mode idle_mode[] = अणु
	[CPM_IDLE_WAIT] = अणु 1, "wait" पूर्ण, /* शेष */
	[CPM_IDLE_DOZE] = अणु 0, "doze" पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक cpm_set(अचिन्हित पूर्णांक cpm_reg, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक value;

	/* CPM controller supports 3 dअगरferent types of sleep पूर्णांकerface
	 * known as class 1, 2 and 3. For class 1 units, they are
	 * unconditionally put to sleep when the corresponding CPM bit is
	 * set. For class 2 and 3 units this is not हाल; अगर they can be
	 * put to to sleep, they will. Here we करो not verअगरy, we just
	 * set them and expect them to eventually go off when they can.
	 */
	value = dcr_पढ़ो(cpm.dcr_host, cpm.dcr_offset[cpm_reg]);
	dcr_ग_लिखो(cpm.dcr_host, cpm.dcr_offset[cpm_reg], value | mask);

	/* वापस old state, to restore later अगर needed */
	वापस value;
पूर्ण

अटल व्योम cpm_idle_रुको(व्योम)
अणु
	अचिन्हित दीर्घ msr_save;

	/* save off initial state */
	msr_save = mfmsr();
	/* sync required when CPM0_ER[CPU] is set */
	mb();
	/* set रुको state MSR */
	mपंचांगsr(msr_save|MSR_WE|MSR_EE|MSR_CE|MSR_DE);
	isync();
	/* वापस to initial state */
	mपंचांगsr(msr_save);
	isync();
पूर्ण

अटल व्योम cpm_idle_sleep(अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक er_save;

	/* update CPM_ER state */
	er_save = cpm_set(CPM_ER, mask);

	/* go to रुको state so that CPM0_ER[CPU] can take effect */
	cpm_idle_रुको();

	/* restore CPM_ER state */
	dcr_ग_लिखो(cpm.dcr_host, cpm.dcr_offset[CPM_ER], er_save);
पूर्ण

अटल व्योम cpm_idle_करोze(व्योम)
अणु
	cpm_idle_sleep(cpm.idle_करोze);
पूर्ण

अटल व्योम cpm_idle_config(पूर्णांक mode)
अणु
	पूर्णांक i;

	अगर (idle_mode[mode].enabled)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(idle_mode); i++)
		idle_mode[i].enabled = 0;

	idle_mode[mode].enabled = 1;
पूर्ण

अटल sमाप_प्रकार cpm_idle_show(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *s = buf;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(idle_mode); i++) अणु
		अगर (idle_mode[i].enabled)
			s += प्र_लिखो(s, "[%s] ", idle_mode[i].name);
		अन्यथा
			s += प्र_लिखो(s, "%s ", idle_mode[i].name);
	पूर्ण

	*(s-1) = '\n'; /* convert the last space to a newline */

	वापस s - buf;
पूर्ण

अटल sमाप_प्रकार cpm_idle_store(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *p;
	पूर्णांक len;

	p = स_प्रथम(buf, '\n', n);
	len = p ? p - buf : n;

	क्रम (i = 0; i < ARRAY_SIZE(idle_mode); i++) अणु
		अगर (म_भेदन(buf, idle_mode[i].name, len) == 0) अणु
			cpm_idle_config(i);
			वापस n;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा kobj_attribute cpm_idle_attr =
	__ATTR(idle, 0644, cpm_idle_show, cpm_idle_store);

अटल व्योम cpm_idle_config_sysfs(व्योम)
अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ ret;

	dev = get_cpu_device(0);

	ret = sysfs_create_file(&dev->kobj,
				&cpm_idle_attr.attr);
	अगर (ret)
		prपूर्णांकk(KERN_WARNING
		       "cpm: failed to create idle sysfs entry\n");
पूर्ण

अटल व्योम cpm_idle(व्योम)
अणु
	अगर (idle_mode[CPM_IDLE_DOZE].enabled)
		cpm_idle_करोze();
	अन्यथा
		cpm_idle_रुको();
पूर्ण

अटल पूर्णांक cpm_suspend_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस !!cpm.standby;
	हाल PM_SUSPEND_MEM:
		वापस !!cpm.suspend;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम cpm_suspend_standby(अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित दीर्घ tcr_save;

	/* disable decrement पूर्णांकerrupt */
	tcr_save = mfspr(SPRN_TCR);
	mtspr(SPRN_TCR, tcr_save & ~TCR_DIE);

	/* go to sleep state */
	cpm_idle_sleep(mask);

	/* restore decrement पूर्णांकerrupt */
	mtspr(SPRN_TCR, tcr_save);
पूर्ण

अटल पूर्णांक cpm_suspend_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		cpm_suspend_standby(cpm.standby);
		अवरोध;
	हाल PM_SUSPEND_MEM:
		cpm_suspend_standby(cpm.suspend);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops cpm_suspend_ops = अणु
	.valid		= cpm_suspend_valid,
	.enter		= cpm_suspend_enter,
पूर्ण;

अटल पूर्णांक cpm_get_uपूर्णांक_property(काष्ठा device_node *np,
				 स्थिर अक्षर *name)
अणु
	पूर्णांक len;
	स्थिर अचिन्हित पूर्णांक *prop = of_get_property(np, name, &len);

	अगर (prop == शून्य || len < माप(u32))
		वापस 0;

	वापस *prop;
पूर्ण

अटल पूर्णांक __init cpm_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक dcr_base, dcr_len;
	पूर्णांक ret = 0;

	अगर (!cpm.घातersave_off) अणु
		cpm_idle_config(CPM_IDLE_WAIT);
		ppc_md.घातer_save = &cpm_idle;
	पूर्ण

	np = of_find_compatible_node(शून्य, शून्य, "ibm,cpm");
	अगर (!np) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	dcr_base = dcr_resource_start(np, 0);
	dcr_len = dcr_resource_len(np, 0);

	अगर (dcr_base == 0 || dcr_len == 0) अणु
		prपूर्णांकk(KERN_ERR "cpm: could not parse dcr property for %pOF\n",
		       np);
		ret = -EINVAL;
		जाओ node_put;
	पूर्ण

	cpm.dcr_host = dcr_map(np, dcr_base, dcr_len);

	अगर (!DCR_MAP_OK(cpm.dcr_host)) अणु
		prपूर्णांकk(KERN_ERR "cpm: failed to map dcr property for %pOF\n",
		       np);
		ret = -EINVAL;
		जाओ node_put;
	पूर्ण

	/* All 4xx SoCs with a CPM controller have one of two
	 * dअगरferent order क्रम the CPM रेजिस्टरs. Some have the
	 * CPM रेजिस्टरs in the following order (ER,FR,SR). The
	 * others have them in the following order (SR,ER,FR).
	 */

	अगर (cpm_get_uपूर्णांक_property(np, "er-offset") == 0) अणु
		cpm.dcr_offset[CPM_ER] = 0;
		cpm.dcr_offset[CPM_FR] = 1;
		cpm.dcr_offset[CPM_SR] = 2;
	पूर्ण अन्यथा अणु
		cpm.dcr_offset[CPM_ER] = 1;
		cpm.dcr_offset[CPM_FR] = 2;
		cpm.dcr_offset[CPM_SR] = 0;
	पूर्ण

	/* Now let's see what IPs to turn off क्रम the following modes */

	cpm.unused = cpm_get_uपूर्णांक_property(np, "unused-units");
	cpm.idle_करोze = cpm_get_uपूर्णांक_property(np, "idle-doze");
	cpm.standby = cpm_get_uपूर्णांक_property(np, "standby");
	cpm.suspend = cpm_get_uपूर्णांक_property(np, "suspend");

	/* If some IPs are unused let's turn them off now */

	अगर (cpm.unused) अणु
		cpm_set(CPM_ER, cpm.unused);
		cpm_set(CPM_FR, cpm.unused);
	पूर्ण

	/* Now let's export पूर्णांकerfaces */

	अगर (!cpm.घातersave_off && cpm.idle_करोze)
		cpm_idle_config_sysfs();

	अगर (cpm.standby || cpm.suspend)
		suspend_set_ops(&cpm_suspend_ops);
node_put:
	of_node_put(np);
out:
	वापस ret;
पूर्ण

late_initcall(cpm_init);

अटल पूर्णांक __init cpm_घातersave_off(अक्षर *arg)
अणु
	cpm.घातersave_off = 1;
	वापस 0;
पूर्ण
__setup("powersave=off", cpm_घातersave_off);
