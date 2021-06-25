<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Intel Corporation
 *
 * Authors:
 *	Chen, Gong <gong.chen@linux.पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/ras.h>
#समावेश <linux/uuid.h>

#घोषणा CREATE_TRACE_POINTS
#घोषणा TRACE_INCLUDE_PATH ../../include/ras
#समावेश <ras/ras_event.h>

व्योम log_non_standard_event(स्थिर guid_t *sec_type, स्थिर guid_t *fru_id,
			    स्थिर अक्षर *fru_text, स्थिर u8 sev, स्थिर u8 *err,
			    स्थिर u32 len)
अणु
	trace_non_standard_event(sec_type, fru_id, fru_text, sev, err, len);
पूर्ण

व्योम log_arm_hw_error(काष्ठा cper_sec_proc_arm *err)
अणु
	trace_arm_event(err);
पूर्ण

अटल पूर्णांक __init ras_init(व्योम)
अणु
	पूर्णांक rc = 0;

	ras_debugfs_init();
	rc = ras_add_daemon_trace();

	वापस rc;
पूर्ण
subsys_initcall(ras_init);

#अगर defined(CONFIG_ACPI_EXTLOG) || defined(CONFIG_ACPI_EXTLOG_MODULE)
EXPORT_TRACEPOINT_SYMBOL_GPL(extlog_mem_event);
#पूर्ण_अगर
EXPORT_TRACEPOINT_SYMBOL_GPL(mc_event);
EXPORT_TRACEPOINT_SYMBOL_GPL(non_standard_event);
EXPORT_TRACEPOINT_SYMBOL_GPL(arm_event);

अटल पूर्णांक __init parse_ras_param(अक्षर *str)
अणु
#अगर_घोषित CONFIG_RAS_CEC
	parse_cec_param(str);
#पूर्ण_अगर

	वापस 1;
पूर्ण
__setup("ras", parse_ras_param);
