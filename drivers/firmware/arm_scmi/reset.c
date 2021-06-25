<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Reset Protocol
 *
 * Copyright (C) 2019-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications RESET - " fmt

#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"
#समावेश "notify.h"

क्रमागत scmi_reset_protocol_cmd अणु
	RESET_DOMAIN_ATTRIBUTES = 0x3,
	RESET = 0x4,
	RESET_NOTIFY = 0x5,
पूर्ण;

#घोषणा NUM_RESET_DOMAIN_MASK	0xffff
#घोषणा RESET_NOTIFY_ENABLE	BIT(0)

काष्ठा scmi_msg_resp_reset_करोमुख्य_attributes अणु
	__le32 attributes;
#घोषणा SUPPORTS_ASYNC_RESET(x)		((x) & BIT(31))
#घोषणा SUPPORTS_NOTIFY_RESET(x)	((x) & BIT(30))
	__le32 latency;
	    u8 name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_msg_reset_करोमुख्य_reset अणु
	__le32 करोमुख्य_id;
	__le32 flags;
#घोषणा AUTONOMOUS_RESET	BIT(0)
#घोषणा EXPLICIT_RESET_ASSERT	BIT(1)
#घोषणा ASYNCHRONOUS_RESET	BIT(2)
	__le32 reset_state;
#घोषणा ARCH_COLD_RESET		0
पूर्ण;

काष्ठा scmi_msg_reset_notअगरy अणु
	__le32 id;
	__le32 event_control;
#घोषणा RESET_TP_NOTIFY_ALL	BIT(0)
पूर्ण;

काष्ठा scmi_reset_issued_notअगरy_payld अणु
	__le32 agent_id;
	__le32 करोमुख्य_id;
	__le32 reset_state;
पूर्ण;

काष्ठा reset_करोm_info अणु
	bool async_reset;
	bool reset_notअगरy;
	u32 latency_us;
	अक्षर name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_reset_info अणु
	u32 version;
	पूर्णांक num_करोमुख्यs;
	काष्ठा reset_करोm_info *करोm_info;
पूर्ण;

अटल पूर्णांक scmi_reset_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				     काष्ठा scmi_reset_info *pi)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	u32 attr;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES,
				      0, माप(attr), &t);
	अगर (ret)
		वापस ret;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		attr = get_unaligned_le32(t->rx.buf);
		pi->num_करोमुख्यs = attr & NUM_RESET_DOMAIN_MASK;
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_reset_करोमुख्य_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				 u32 करोमुख्य, काष्ठा reset_करोm_info *करोm_info)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_reset_करोमुख्य_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, RESET_DOMAIN_ATTRIBUTES,
				      माप(करोमुख्य), माप(*attr), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य, t->tx.buf);
	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		u32 attributes = le32_to_cpu(attr->attributes);

		करोm_info->async_reset = SUPPORTS_ASYNC_RESET(attributes);
		करोm_info->reset_notअगरy = SUPPORTS_NOTIFY_RESET(attributes);
		करोm_info->latency_us = le32_to_cpu(attr->latency);
		अगर (करोm_info->latency_us == U32_MAX)
			करोm_info->latency_us = 0;
		strlcpy(करोm_info->name, attr->name, SCMI_MAX_STR_SIZE);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_reset_num_करोमुख्यs_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_reset_info *pi = ph->get_priv(ph);

	वापस pi->num_करोमुख्यs;
पूर्ण

अटल अक्षर *scmi_reset_name_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				 u32 करोमुख्य)
अणु
	काष्ठा scmi_reset_info *pi = ph->get_priv(ph);

	काष्ठा reset_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	वापस करोm->name;
पूर्ण

अटल पूर्णांक scmi_reset_latency_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 करोमुख्य)
अणु
	काष्ठा scmi_reset_info *pi = ph->get_priv(ph);
	काष्ठा reset_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	वापस करोm->latency_us;
पूर्ण

अटल पूर्णांक scmi_करोमुख्य_reset(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			     u32 flags, u32 state)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_reset_करोमुख्य_reset *करोm;
	काष्ठा scmi_reset_info *pi = ph->get_priv(ph);
	काष्ठा reset_करोm_info *rकरोm = pi->करोm_info + करोमुख्य;

	अगर (rकरोm->async_reset)
		flags |= ASYNCHRONOUS_RESET;

	ret = ph->xops->xfer_get_init(ph, RESET, माप(*करोm), 0, &t);
	अगर (ret)
		वापस ret;

	करोm = t->tx.buf;
	करोm->करोमुख्य_id = cpu_to_le32(करोमुख्य);
	करोm->flags = cpu_to_le32(flags);
	करोm->reset_state = cpu_to_le32(state);

	अगर (rकरोm->async_reset)
		ret = ph->xops->करो_xfer_with_response(ph, t);
	अन्यथा
		ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_reset_करोमुख्य_reset(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य)
अणु
	वापस scmi_करोमुख्य_reset(ph, करोमुख्य, AUTONOMOUS_RESET,
				 ARCH_COLD_RESET);
पूर्ण

अटल पूर्णांक
scmi_reset_करोमुख्य_निश्चित(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य)
अणु
	वापस scmi_करोमुख्य_reset(ph, करोमुख्य, EXPLICIT_RESET_ASSERT,
				 ARCH_COLD_RESET);
पूर्ण

अटल पूर्णांक
scmi_reset_करोमुख्य_deनिश्चित(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य)
अणु
	वापस scmi_करोमुख्य_reset(ph, करोमुख्य, 0, ARCH_COLD_RESET);
पूर्ण

अटल स्थिर काष्ठा scmi_reset_proto_ops reset_proto_ops = अणु
	.num_करोमुख्यs_get = scmi_reset_num_करोमुख्यs_get,
	.name_get = scmi_reset_name_get,
	.latency_get = scmi_reset_latency_get,
	.reset = scmi_reset_करोमुख्य_reset,
	.निश्चित = scmi_reset_करोमुख्य_निश्चित,
	.deनिश्चित = scmi_reset_करोमुख्य_deनिश्चित,
पूर्ण;

अटल पूर्णांक scmi_reset_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
			     u32 करोमुख्य_id, bool enable)
अणु
	पूर्णांक ret;
	u32 evt_cntl = enable ? RESET_TP_NOTIFY_ALL : 0;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_reset_notअगरy *cfg;

	ret = ph->xops->xfer_get_init(ph, RESET_NOTIFY, माप(*cfg), 0, &t);
	अगर (ret)
		वापस ret;

	cfg = t->tx.buf;
	cfg->id = cpu_to_le32(करोमुख्य_id);
	cfg->event_control = cpu_to_le32(evt_cntl);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_reset_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					 u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret;

	ret = scmi_reset_notअगरy(ph, src_id, enable);
	अगर (ret)
		pr_debug("FAIL_ENABLED - evt[%X] dom[%d] - ret:%d\n",
			 evt_id, src_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *
scmi_reset_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
			      u8 evt_id, kसमय_प्रकार बारtamp,
			      स्थिर व्योम *payld, माप_प्रकार payld_sz,
			      व्योम *report, u32 *src_id)
अणु
	स्थिर काष्ठा scmi_reset_issued_notअगरy_payld *p = payld;
	काष्ठा scmi_reset_issued_report *r = report;

	अगर (evt_id != SCMI_EVENT_RESET_ISSUED || माप(*p) != payld_sz)
		वापस शून्य;

	r->बारtamp = बारtamp;
	r->agent_id = le32_to_cpu(p->agent_id);
	r->करोमुख्य_id = le32_to_cpu(p->करोमुख्य_id);
	r->reset_state = le32_to_cpu(p->reset_state);
	*src_id = r->करोमुख्य_id;

	वापस r;
पूर्ण

अटल पूर्णांक scmi_reset_get_num_sources(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_reset_info *pinfo = ph->get_priv(ph);

	अगर (!pinfo)
		वापस -EINVAL;

	वापस pinfo->num_करोमुख्यs;
पूर्ण

अटल स्थिर काष्ठा scmi_event reset_events[] = अणु
	अणु
		.id = SCMI_EVENT_RESET_ISSUED,
		.max_payld_sz = माप(काष्ठा scmi_reset_issued_notअगरy_payld),
		.max_report_sz = माप(काष्ठा scmi_reset_issued_report),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops reset_event_ops = अणु
	.get_num_sources = scmi_reset_get_num_sources,
	.set_notअगरy_enabled = scmi_reset_set_notअगरy_enabled,
	.fill_custom_report = scmi_reset_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events reset_protocol_events = अणु
	.queue_sz = SCMI_PROTO_QUEUE_SZ,
	.ops = &reset_event_ops,
	.evts = reset_events,
	.num_events = ARRAY_SIZE(reset_events),
पूर्ण;

अटल पूर्णांक scmi_reset_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक करोमुख्य;
	u32 version;
	काष्ठा scmi_reset_info *pinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "Reset Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	pinfo = devm_kzalloc(ph->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस -ENOMEM;

	scmi_reset_attributes_get(ph, pinfo);

	pinfo->करोm_info = devm_kसुस्मृति(ph->dev, pinfo->num_करोमुख्यs,
				       माप(*pinfo->करोm_info), GFP_KERNEL);
	अगर (!pinfo->करोm_info)
		वापस -ENOMEM;

	क्रम (करोमुख्य = 0; करोमुख्य < pinfo->num_करोमुख्यs; करोमुख्य++) अणु
		काष्ठा reset_करोm_info *करोm = pinfo->करोm_info + करोमुख्य;

		scmi_reset_करोमुख्य_attributes_get(ph, करोमुख्य, करोm);
	पूर्ण

	pinfo->version = version;
	वापस ph->set_priv(ph, pinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_reset = अणु
	.id = SCMI_PROTOCOL_RESET,
	.owner = THIS_MODULE,
	.instance_init = &scmi_reset_protocol_init,
	.ops = &reset_proto_ops,
	.events = &reset_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(reset, scmi_reset)
