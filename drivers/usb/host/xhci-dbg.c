<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#समावेश "xhci.h"

अक्षर *xhci_get_slot_state(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *ctx)
अणु
	काष्ठा xhci_slot_ctx *slot_ctx = xhci_get_slot_ctx(xhci, ctx);
	पूर्णांक state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));

	वापस xhci_slot_state_string(state);
पूर्ण

व्योम xhci_dbg_trace(काष्ठा xhci_hcd *xhci, व्योम (*trace)(काष्ठा va_क्रमmat *),
			स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	xhci_dbg(xhci, "%pV\n", &vaf);
	trace(&vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(xhci_dbg_trace);
