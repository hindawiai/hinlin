<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h> /* bug in tracepoपूर्णांक.h, it should include this */

#अगर_अघोषित __CHECKER__
#घोषणा CREATE_TRACE_POINTS
#समावेश "bus.h"
#समावेश "tracepoint.h"
#समावेश "debug.h"

व्योम __brcmf_err(काष्ठा brcmf_bus *bus, स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	अगर (bus)
		dev_err(bus->dev, "%s: %pV", func, &vaf);
	अन्यथा
		pr_err("%s: %pV", func, &vaf);
	trace_brcmf_err(func, &vaf);
	बहु_पूर्ण(args);
पूर्ण

#पूर्ण_अगर
