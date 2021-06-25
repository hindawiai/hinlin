<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * System Control and Management Interface (SCMI) Message Protocol
 * notअगरication header file containing some definitions, काष्ठाures
 * and function prototypes related to SCMI Notअगरication handling.
 *
 * Copyright (C) 2020-2021 ARM Ltd.
 */
#अगर_अघोषित _SCMI_NOTIFY_H
#घोषणा _SCMI_NOTIFY_H

#समावेश <linux/device.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/types.h>

#घोषणा SCMI_PROTO_QUEUE_SZ	4096

/**
 * काष्ठा scmi_event  - Describes an event to be supported
 * @id: Event ID
 * @max_payld_sz: Max possible size क्रम the payload of a notअगरication message
 * @max_report_sz: Max possible size क्रम the report of a notअगरication message
 *
 * Each SCMI protocol, during its initialization phase, can describe the events
 * it wishes to support in a few काष्ठा scmi_event and pass them to the core
 * using scmi_रेजिस्टर_protocol_events().
 */
काष्ठा scmi_event अणु
	u8	id;
	माप_प्रकार	max_payld_sz;
	माप_प्रकार	max_report_sz;
पूर्ण;

काष्ठा scmi_protocol_handle;

/**
 * काष्ठा scmi_event_ops  - Protocol helpers called by the notअगरication core.
 * @get_num_sources: Returns the number of possible events' sources क्रम this
 *		     protocol
 * @set_notअगरy_enabled: Enable/disable the required evt_id/src_id notअगरications
 *			using the proper custom protocol commands.
 *			Return 0 on Success
 * @fill_custom_report: fills a custom event report from the provided
 *			event message payld identअगरying the event
 *			specअगरic src_id.
 *			Return शून्य on failure otherwise @report now fully
 *			populated
 *
 * Context: Helpers described in &काष्ठा scmi_event_ops are called only in
 *	    process context.
 */
काष्ठा scmi_event_ops अणु
	पूर्णांक (*get_num_sources)(स्थिर काष्ठा scmi_protocol_handle *ph);
	पूर्णांक (*set_notअगरy_enabled)(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u8 evt_id, u32 src_id, bool enabled);
	व्योम *(*fill_custom_report)(स्थिर काष्ठा scmi_protocol_handle *ph,
				    u8 evt_id, kसमय_प्रकार बारtamp,
				    स्थिर व्योम *payld, माप_प्रकार payld_sz,
				    व्योम *report, u32 *src_id);
पूर्ण;

/**
 * काष्ठा scmi_protocol_events  - Per-protocol description of available events
 * @queue_sz: Size in bytes of the per-protocol queue to use.
 * @ops: Array of protocol-specअगरic events operations.
 * @evts: Array of supported protocol's events.
 * @num_events: Number of supported protocol's events described in @evts.
 * @num_sources: Number of protocol's sources, should be greater than 0; अगर not
 *		 available at compile समय, it will be provided at run-समय via
 *		 @get_num_sources.
 */
काष्ठा scmi_protocol_events अणु
	माप_प्रकार				queue_sz;
	स्थिर काष्ठा scmi_event_ops	*ops;
	स्थिर काष्ठा scmi_event		*evts;
	अचिन्हित पूर्णांक			num_events;
	अचिन्हित पूर्णांक			num_sources;
पूर्ण;

पूर्णांक scmi_notअगरication_init(काष्ठा scmi_handle *handle);
व्योम scmi_notअगरication_निकास(काष्ठा scmi_handle *handle);
पूर्णांक scmi_रेजिस्टर_protocol_events(स्थिर काष्ठा scmi_handle *handle, u8 proto_id,
				  स्थिर काष्ठा scmi_protocol_handle *ph,
				  स्थिर काष्ठा scmi_protocol_events *ee);
व्योम scmi_deरेजिस्टर_protocol_events(स्थिर काष्ठा scmi_handle *handle,
				     u8 proto_id);
पूर्णांक scmi_notअगरy(स्थिर काष्ठा scmi_handle *handle, u8 proto_id, u8 evt_id,
		स्थिर व्योम *buf, माप_प्रकार len, kसमय_प्रकार ts);

#पूर्ण_अगर /* _SCMI_NOTIFY_H */
