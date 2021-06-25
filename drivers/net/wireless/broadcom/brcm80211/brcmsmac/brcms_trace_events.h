<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __BRCMS_TRACE_EVENTS_H
#घोषणा __BRCMS_TRACE_EVENTS_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mac80211_if.h"

#अगर_अघोषित CONFIG_BRCM_TRACING
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर

#समावेश "brcms_trace_brcmsmac.h"
#समावेश "brcms_trace_brcmsmac_tx.h"
#समावेश "brcms_trace_brcmsmac_msg.h"

#पूर्ण_अगर /* __TRACE_BRCMSMAC_H */
