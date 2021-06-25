<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) System Power Protocol
 *
 * Copyright (C) 2020-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications SYSTEM - " fmt

#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"
#समावेश "notify.h"

#घोषणा SCMI_SYSTEM_NUM_SOURCES		1

क्रमागत scmi_प्रणाली_protocol_cmd अणु
	SYSTEM_POWER_STATE_NOTIFY = 0x5,
पूर्ण;

काष्ठा scmi_प्रणाली_घातer_state_notअगरy अणु
	__le32 notअगरy_enable;
पूर्ण;

काष्ठा scmi_प्रणाली_घातer_state_notअगरier_payld अणु
	__le32 agent_id;
	__le32 flags;
	__le32 प्रणाली_state;
पूर्ण;

काष्ठा scmi_प्रणाली_info अणु
	u32 version;
पूर्ण;

अटल पूर्णांक scmi_प्रणाली_request_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
				      bool enable)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_प्रणाली_घातer_state_notअगरy *notअगरy;

	ret = ph->xops->xfer_get_init(ph, SYSTEM_POWER_STATE_NOTIFY,
				      माप(*notअगरy), 0, &t);
	अगर (ret)
		वापस ret;

	notअगरy = t->tx.buf;
	notअगरy->notअगरy_enable = enable ? cpu_to_le32(BIT(0)) : 0;

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_प्रणाली_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					  u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret;

	ret = scmi_प्रणाली_request_notअगरy(ph, enable);
	अगर (ret)
		pr_debug("FAIL_ENABLE - evt[%X] - ret:%d\n", evt_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *
scmi_प्रणाली_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
			       u8 evt_id, kसमय_प्रकार बारtamp,
			       स्थिर व्योम *payld, माप_प्रकार payld_sz,
			       व्योम *report, u32 *src_id)
अणु
	स्थिर काष्ठा scmi_प्रणाली_घातer_state_notअगरier_payld *p = payld;
	काष्ठा scmi_प्रणाली_घातer_state_notअगरier_report *r = report;

	अगर (evt_id != SCMI_EVENT_SYSTEM_POWER_STATE_NOTIFIER ||
	    माप(*p) != payld_sz)
		वापस शून्य;

	r->बारtamp = बारtamp;
	r->agent_id = le32_to_cpu(p->agent_id);
	r->flags = le32_to_cpu(p->flags);
	r->प्रणाली_state = le32_to_cpu(p->प्रणाली_state);
	*src_id = 0;

	वापस r;
पूर्ण

अटल स्थिर काष्ठा scmi_event प्रणाली_events[] = अणु
	अणु
		.id = SCMI_EVENT_SYSTEM_POWER_STATE_NOTIFIER,
		.max_payld_sz =
			माप(काष्ठा scmi_प्रणाली_घातer_state_notअगरier_payld),
		.max_report_sz =
			माप(काष्ठा scmi_प्रणाली_घातer_state_notअगरier_report),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops प्रणाली_event_ops = अणु
	.set_notअगरy_enabled = scmi_प्रणाली_set_notअगरy_enabled,
	.fill_custom_report = scmi_प्रणाली_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events प्रणाली_protocol_events = अणु
	.queue_sz = SCMI_PROTO_QUEUE_SZ,
	.ops = &प्रणाली_event_ops,
	.evts = प्रणाली_events,
	.num_events = ARRAY_SIZE(प्रणाली_events),
	.num_sources = SCMI_SYSTEM_NUM_SOURCES,
पूर्ण;

अटल पूर्णांक scmi_प्रणाली_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	u32 version;
	काष्ठा scmi_प्रणाली_info *pinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "System Power Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	pinfo = devm_kzalloc(ph->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस -ENOMEM;

	pinfo->version = version;
	वापस ph->set_priv(ph, pinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_प्रणाली = अणु
	.id = SCMI_PROTOCOL_SYSTEM,
	.owner = THIS_MODULE,
	.instance_init = &scmi_प्रणाली_protocol_init,
	.ops = शून्य,
	.events = &प्रणाली_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(प्रणाली, scmi_प्रणाली)
