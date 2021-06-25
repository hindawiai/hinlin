<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Smart reflex Class 3 specअगरic implementations
 *
 * Author: Thara Gopinath       <thara@ti.com>
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 */

#समावेश <linux/घातer/smartreflex.h>
#समावेश "soc.h"
#समावेश "voltage.h"

अटल पूर्णांक sr_class3_enable(काष्ठा omap_sr *sr)
अणु
	अचिन्हित दीर्घ volt = voltdm_get_voltage(sr->voltdm);

	अगर (!volt) अणु
		pr_warn("%s: Curr voltage unknown. Cannot enable %s\n",
			__func__, sr->name);
		वापस -ENODATA;
	पूर्ण

	omap_vp_enable(sr->voltdm);
	वापस sr_enable(sr, volt);
पूर्ण

अटल पूर्णांक sr_class3_disable(काष्ठा omap_sr *sr, पूर्णांक is_volt_reset)
अणु
	sr_disable_errgen(sr);
	omap_vp_disable(sr->voltdm);
	sr_disable(sr);
	अगर (is_volt_reset)
		voltdm_reset(sr->voltdm);

	वापस 0;
पूर्ण

अटल पूर्णांक sr_class3_configure(काष्ठा omap_sr *sr)
अणु
	वापस sr_configure_errgen(sr);
पूर्ण

/* SR class3 काष्ठाure */
अटल काष्ठा omap_sr_class_data class3_data = अणु
	.enable = sr_class3_enable,
	.disable = sr_class3_disable,
	.configure = sr_class3_configure,
	.class_type = SR_CLASS3,
पूर्ण;

/* Smartreflex Class3 init API to be called from board file */
अटल पूर्णांक __init sr_class3_init(व्योम)
अणु
	pr_info("SmartReflex Class3 initialized\n");
	वापस sr_रेजिस्टर_class(&class3_data);
पूर्ण
omap_late_initcall(sr_class3_init);
