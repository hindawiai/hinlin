<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Power Protocol
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications POWER - " fmt

#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"
#समावेश "notify.h"

क्रमागत scmi_घातer_protocol_cmd अणु
	POWER_DOMAIN_ATTRIBUTES = 0x3,
	POWER_STATE_SET = 0x4,
	POWER_STATE_GET = 0x5,
	POWER_STATE_NOTIFY = 0x6,
पूर्ण;

काष्ठा scmi_msg_resp_घातer_attributes अणु
	__le16 num_करोमुख्यs;
	__le16 reserved;
	__le32 stats_addr_low;
	__le32 stats_addr_high;
	__le32 stats_size;
पूर्ण;

काष्ठा scmi_msg_resp_घातer_करोमुख्य_attributes अणु
	__le32 flags;
#घोषणा SUPPORTS_STATE_SET_NOTIFY(x)	((x) & BIT(31))
#घोषणा SUPPORTS_STATE_SET_ASYNC(x)	((x) & BIT(30))
#घोषणा SUPPORTS_STATE_SET_SYNC(x)	((x) & BIT(29))
	    u8 name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_घातer_set_state अणु
	__le32 flags;
#घोषणा STATE_SET_ASYNC		BIT(0)
	__le32 करोमुख्य;
	__le32 state;
पूर्ण;

काष्ठा scmi_घातer_state_notअगरy अणु
	__le32 करोमुख्य;
	__le32 notअगरy_enable;
पूर्ण;

काष्ठा scmi_घातer_state_notअगरy_payld अणु
	__le32 agent_id;
	__le32 करोमुख्य_id;
	__le32 घातer_state;
पूर्ण;

काष्ठा घातer_करोm_info अणु
	bool state_set_sync;
	bool state_set_async;
	bool state_set_notअगरy;
	अक्षर name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_घातer_info अणु
	u32 version;
	पूर्णांक num_करोमुख्यs;
	u64 stats_addr;
	u32 stats_size;
	काष्ठा घातer_करोm_info *करोm_info;
पूर्ण;

अटल पूर्णांक scmi_घातer_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				     काष्ठा scmi_घातer_info *pi)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_घातer_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES,
				      0, माप(*attr), &t);
	अगर (ret)
		वापस ret;

	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		pi->num_करोमुख्यs = le16_to_cpu(attr->num_करोमुख्यs);
		pi->stats_addr = le32_to_cpu(attr->stats_addr_low) |
				(u64)le32_to_cpu(attr->stats_addr_high) << 32;
		pi->stats_size = le32_to_cpu(attr->stats_size);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_घातer_करोमुख्य_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				 u32 करोमुख्य, काष्ठा घातer_करोm_info *करोm_info)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_घातer_करोमुख्य_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, POWER_DOMAIN_ATTRIBUTES,
				      माप(करोमुख्य), माप(*attr), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य, t->tx.buf);
	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		u32 flags = le32_to_cpu(attr->flags);

		करोm_info->state_set_notअगरy = SUPPORTS_STATE_SET_NOTIFY(flags);
		करोm_info->state_set_async = SUPPORTS_STATE_SET_ASYNC(flags);
		करोm_info->state_set_sync = SUPPORTS_STATE_SET_SYNC(flags);
		strlcpy(करोm_info->name, attr->name, SCMI_MAX_STR_SIZE);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घातer_state_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				u32 करोमुख्य, u32 state)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_घातer_set_state *st;

	ret = ph->xops->xfer_get_init(ph, POWER_STATE_SET, माप(*st), 0, &t);
	अगर (ret)
		वापस ret;

	st = t->tx.buf;
	st->flags = cpu_to_le32(0);
	st->करोमुख्य = cpu_to_le32(करोमुख्य);
	st->state = cpu_to_le32(state);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घातer_state_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				u32 करोमुख्य, u32 *state)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, POWER_STATE_GET, माप(u32), माप(u32), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य, t->tx.buf);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		*state = get_unaligned_le32(t->rx.buf);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घातer_num_करोमुख्यs_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_घातer_info *pi = ph->get_priv(ph);

	वापस pi->num_करोमुख्यs;
पूर्ण

अटल अक्षर *scmi_घातer_name_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				 u32 करोमुख्य)
अणु
	काष्ठा scmi_घातer_info *pi = ph->get_priv(ph);
	काष्ठा घातer_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	वापस करोm->name;
पूर्ण

अटल स्थिर काष्ठा scmi_घातer_proto_ops घातer_proto_ops = अणु
	.num_करोमुख्यs_get = scmi_घातer_num_करोमुख्यs_get,
	.name_get = scmi_घातer_name_get,
	.state_set = scmi_घातer_state_set,
	.state_get = scmi_घातer_state_get,
पूर्ण;

अटल पूर्णांक scmi_घातer_request_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u32 करोमुख्य, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_घातer_state_notअगरy *notअगरy;

	ret = ph->xops->xfer_get_init(ph, POWER_STATE_NOTIFY,
				      माप(*notअगरy), 0, &t);
	अगर (ret)
		वापस ret;

	notअगरy = t->tx.buf;
	notअगरy->करोमुख्य = cpu_to_le32(करोमुख्य);
	notअगरy->notअगरy_enable = enable ? cpu_to_le32(BIT(0)) : 0;

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घातer_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					 u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret;

	ret = scmi_घातer_request_notअगरy(ph, src_id, enable);
	अगर (ret)
		pr_debug("FAIL_ENABLE - evt[%X] dom[%d] - ret:%d\n",
			 evt_id, src_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *
scmi_घातer_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
			      u8 evt_id, kसमय_प्रकार बारtamp,
			      स्थिर व्योम *payld, माप_प्रकार payld_sz,
			      व्योम *report, u32 *src_id)
अणु
	स्थिर काष्ठा scmi_घातer_state_notअगरy_payld *p = payld;
	काष्ठा scmi_घातer_state_changed_report *r = report;

	अगर (evt_id != SCMI_EVENT_POWER_STATE_CHANGED || माप(*p) != payld_sz)
		वापस शून्य;

	r->बारtamp = बारtamp;
	r->agent_id = le32_to_cpu(p->agent_id);
	r->करोमुख्य_id = le32_to_cpu(p->करोमुख्य_id);
	r->घातer_state = le32_to_cpu(p->घातer_state);
	*src_id = r->करोमुख्य_id;

	वापस r;
पूर्ण

अटल पूर्णांक scmi_घातer_get_num_sources(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_घातer_info *pinfo = ph->get_priv(ph);

	अगर (!pinfo)
		वापस -EINVAL;

	वापस pinfo->num_करोमुख्यs;
पूर्ण

अटल स्थिर काष्ठा scmi_event घातer_events[] = अणु
	अणु
		.id = SCMI_EVENT_POWER_STATE_CHANGED,
		.max_payld_sz = माप(काष्ठा scmi_घातer_state_notअगरy_payld),
		.max_report_sz =
			माप(काष्ठा scmi_घातer_state_changed_report),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops घातer_event_ops = अणु
	.get_num_sources = scmi_घातer_get_num_sources,
	.set_notअगरy_enabled = scmi_घातer_set_notअगरy_enabled,
	.fill_custom_report = scmi_घातer_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events घातer_protocol_events = अणु
	.queue_sz = SCMI_PROTO_QUEUE_SZ,
	.ops = &घातer_event_ops,
	.evts = घातer_events,
	.num_events = ARRAY_SIZE(घातer_events),
पूर्ण;

अटल पूर्णांक scmi_घातer_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक करोमुख्य;
	u32 version;
	काष्ठा scmi_घातer_info *pinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "Power Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	pinfo = devm_kzalloc(ph->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस -ENOMEM;

	scmi_घातer_attributes_get(ph, pinfo);

	pinfo->करोm_info = devm_kसुस्मृति(ph->dev, pinfo->num_करोमुख्यs,
				       माप(*pinfo->करोm_info), GFP_KERNEL);
	अगर (!pinfo->करोm_info)
		वापस -ENOMEM;

	क्रम (करोमुख्य = 0; करोमुख्य < pinfo->num_करोमुख्यs; करोमुख्य++) अणु
		काष्ठा घातer_करोm_info *करोm = pinfo->करोm_info + करोमुख्य;

		scmi_घातer_करोमुख्य_attributes_get(ph, करोमुख्य, करोm);
	पूर्ण

	pinfo->version = version;

	वापस ph->set_priv(ph, pinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_घातer = अणु
	.id = SCMI_PROTOCOL_POWER,
	.owner = THIS_MODULE,
	.instance_init = &scmi_घातer_protocol_init,
	.ops = &घातer_proto_ops,
	.events = &घातer_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(घातer, scmi_घातer)
