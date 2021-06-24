<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2011 Intel Corporation
 */
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश "iwl-drv.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-devtrace.h"

#घोषणा __iwl_fn(fn)						\
व्योम __iwl_ ##fn(काष्ठा device *dev, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat vaf = अणु				\
		.fmt = fmt,					\
	पूर्ण;							\
	बहु_सूची args;						\
								\
	बहु_शुरू(args, fmt);					\
	vaf.va = &args;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	trace_iwlwअगरi_ ##fn(&vaf);				\
	बहु_पूर्ण(args);						\
पूर्ण

__iwl_fn(warn)
IWL_EXPORT_SYMBOL(__iwl_warn);
__iwl_fn(info)
IWL_EXPORT_SYMBOL(__iwl_info);
__iwl_fn(crit)
IWL_EXPORT_SYMBOL(__iwl_crit);

व्योम __iwl_err(काष्ठा device *dev, bool rfसमाप्त_prefix, bool trace_only,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	अगर (!trace_only) अणु
		अगर (rfसमाप्त_prefix)
			dev_err(dev, "(RFKILL) %pV", &vaf);
		अन्यथा
			dev_err(dev, "%pV", &vaf);
	पूर्ण
	trace_iwlwअगरi_err(&vaf);
	बहु_पूर्ण(args);
पूर्ण
IWL_EXPORT_SYMBOL(__iwl_err);

#अगर defined(CONFIG_IWLWIFI_DEBUG) || defined(CONFIG_IWLWIFI_DEVICE_TRACING)
व्योम __iwl_dbg(काष्ठा device *dev,
	       u32 level, bool limit, स्थिर अक्षर *function,
	       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	अगर (iwl_have_debug_level(level) &&
	    (!limit || net_ratelimit()))
		dev_prपूर्णांकk(KERN_DEBUG, dev, "%s %pV", function, &vaf);
#पूर्ण_अगर
	trace_iwlwअगरi_dbg(level, function, &vaf);
	बहु_पूर्ण(args);
पूर्ण
IWL_EXPORT_SYMBOL(__iwl_dbg);
#पूर्ण_अगर
