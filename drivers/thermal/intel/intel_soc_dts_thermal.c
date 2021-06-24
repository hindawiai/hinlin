<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_soc_dts_thermal.c
 * Copyright (c) 2014, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "intel_soc_dts_iosf.h"

#घोषणा CRITICAL_OFFSET_FROM_TJ_MAX	5000

अटल पूर्णांक crit_offset = CRITICAL_OFFSET_FROM_TJ_MAX;
module_param(crit_offset, पूर्णांक, 0644);
MODULE_PARM_DESC(crit_offset,
	"Critical Temperature offset from tj max in millidegree Celsius.");

/* IRQ 86 is a fixed APIC पूर्णांकerrupt क्रम BYT DTS Aux threshold notअगरications */
#घोषणा BYT_SOC_DTS_APIC_IRQ	86

अटल पूर्णांक soc_dts_thres_gsi;
अटल पूर्णांक soc_dts_thres_irq;
अटल काष्ठा पूर्णांकel_soc_dts_sensors *soc_dts;

अटल irqवापस_t soc_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_data)
अणु
	pr_debug("proc_thermal_interrupt\n");
	पूर्णांकel_soc_dts_iosf_पूर्णांकerrupt_handler(soc_dts);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id soc_thermal_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT, BYT_SOC_DTS_APIC_IRQ),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, soc_thermal_ids);

अटल पूर्णांक __init पूर्णांकel_soc_thermal_init(व्योम)
अणु
	पूर्णांक err = 0;
	स्थिर काष्ठा x86_cpu_id *match_cpu;

	match_cpu = x86_match_cpu(soc_thermal_ids);
	अगर (!match_cpu)
		वापस -ENODEV;

	/* Create a zone with 2 trips with marked as पढ़ो only */
	soc_dts = पूर्णांकel_soc_dts_iosf_init(INTEL_SOC_DTS_INTERRUPT_APIC, 2, 1);
	अगर (IS_ERR(soc_dts)) अणु
		err = PTR_ERR(soc_dts);
		वापस err;
	पूर्ण

	soc_dts_thres_gsi = (पूर्णांक)match_cpu->driver_data;
	अगर (soc_dts_thres_gsi) अणु
		/*
		 * Note the flags here MUST match the firmware शेषs, rather
		 * then the request_irq flags, otherwise we get an EBUSY error.
		 */
		soc_dts_thres_irq = acpi_रेजिस्टर_gsi(शून्य, soc_dts_thres_gsi,
						      ACPI_LEVEL_SENSITIVE,
						      ACPI_ACTIVE_LOW);
		अगर (soc_dts_thres_irq < 0) अणु
			pr_warn("intel_soc_dts: Could not get IRQ for GSI %d, err %d\n",
				soc_dts_thres_gsi, soc_dts_thres_irq);
			soc_dts_thres_irq = 0;
		पूर्ण
	पूर्ण

	अगर (soc_dts_thres_irq) अणु
		err = request_thपढ़ोed_irq(soc_dts_thres_irq, शून्य,
					   soc_irq_thपढ़ो_fn,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "soc_dts", soc_dts);
		अगर (err) अणु
			/*
			 * Do not just error out because the user space thermal
			 * daemon such as DPTF may use polling instead of being
			 * पूर्णांकerrupt driven.
			 */
			pr_warn("request_threaded_irq ret %d\n", err);
		पूर्ण
	पूर्ण

	err = पूर्णांकel_soc_dts_iosf_add_पढ़ो_only_critical_trip(soc_dts,
							     crit_offset);
	अगर (err)
		जाओ error_trips;

	वापस 0;

error_trips:
	अगर (soc_dts_thres_irq) अणु
		मुक्त_irq(soc_dts_thres_irq, soc_dts);
		acpi_unरेजिस्टर_gsi(soc_dts_thres_gsi);
	पूर्ण
	पूर्णांकel_soc_dts_iosf_निकास(soc_dts);

	वापस err;
पूर्ण

अटल व्योम __निकास पूर्णांकel_soc_thermal_निकास(व्योम)
अणु
	अगर (soc_dts_thres_irq) अणु
		मुक्त_irq(soc_dts_thres_irq, soc_dts);
		acpi_unरेजिस्टर_gsi(soc_dts_thres_gsi);
	पूर्ण
	पूर्णांकel_soc_dts_iosf_निकास(soc_dts);
पूर्ण

module_init(पूर्णांकel_soc_thermal_init)
module_निकास(पूर्णांकel_soc_thermal_निकास)

MODULE_DESCRIPTION("Intel SoC DTS Thermal Driver");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
