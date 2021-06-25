<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Base Protocol
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications BASE - " fmt

#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"
#समावेश "notify.h"

#घोषणा SCMI_BASE_NUM_SOURCES		1
#घोषणा SCMI_BASE_MAX_CMD_ERR_COUNT	1024

क्रमागत scmi_base_protocol_cmd अणु
	BASE_DISCOVER_VENDOR = 0x3,
	BASE_DISCOVER_SUB_VENDOR = 0x4,
	BASE_DISCOVER_IMPLEMENT_VERSION = 0x5,
	BASE_DISCOVER_LIST_PROTOCOLS = 0x6,
	BASE_DISCOVER_AGENT = 0x7,
	BASE_NOTIFY_ERRORS = 0x8,
	BASE_SET_DEVICE_PERMISSIONS = 0x9,
	BASE_SET_PROTOCOL_PERMISSIONS = 0xa,
	BASE_RESET_AGENT_CONFIGURATION = 0xb,
पूर्ण;

काष्ठा scmi_msg_resp_base_attributes अणु
	u8 num_protocols;
	u8 num_agents;
	__le16 reserved;
पूर्ण;

काष्ठा scmi_msg_base_error_notअगरy अणु
	__le32 event_control;
#घोषणा BASE_TP_NOTIFY_ALL	BIT(0)
पूर्ण;

काष्ठा scmi_base_error_notअगरy_payld अणु
	__le32 agent_id;
	__le32 error_status;
#घोषणा IS_FATAL_ERROR(x)	((x) & BIT(31))
#घोषणा ERROR_CMD_COUNT(x)	FIELD_GET(GENMASK(9, 0), (x))
	__le64 msg_reports[SCMI_BASE_MAX_CMD_ERR_COUNT];
पूर्ण;

/**
 * scmi_base_attributes_get() - माला_लो the implementation details
 *	that are associated with the base protocol.
 *
 * @ph: SCMI protocol handle
 *
 * Return: 0 on success, अन्यथा appropriate SCMI error.
 */
अटल पूर्णांक scmi_base_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_base_attributes *attr_info;
	काष्ठा scmi_revision_info *rev = ph->get_priv(ph);

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES,
				      0, माप(*attr_info), &t);
	अगर (ret)
		वापस ret;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		attr_info = t->rx.buf;
		rev->num_protocols = attr_info->num_protocols;
		rev->num_agents = attr_info->num_agents;
	पूर्ण

	ph->xops->xfer_put(ph, t);

	वापस ret;
पूर्ण

/**
 * scmi_base_venकरोr_id_get() - माला_लो venकरोr/subvenकरोr identअगरier ASCII string.
 *
 * @ph: SCMI protocol handle
 * @sub_venकरोr: specअगरy true अगर sub-venकरोr ID is needed
 *
 * Return: 0 on success, अन्यथा appropriate SCMI error.
 */
अटल पूर्णांक
scmi_base_venकरोr_id_get(स्थिर काष्ठा scmi_protocol_handle *ph, bool sub_venकरोr)
अणु
	u8 cmd;
	पूर्णांक ret, size;
	अक्षर *venकरोr_id;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_revision_info *rev = ph->get_priv(ph);


	अगर (sub_venकरोr) अणु
		cmd = BASE_DISCOVER_SUB_VENDOR;
		venकरोr_id = rev->sub_venकरोr_id;
		size = ARRAY_SIZE(rev->sub_venकरोr_id);
	पूर्ण अन्यथा अणु
		cmd = BASE_DISCOVER_VENDOR;
		venकरोr_id = rev->venकरोr_id;
		size = ARRAY_SIZE(rev->venकरोr_id);
	पूर्ण

	ret = ph->xops->xfer_get_init(ph, cmd, 0, size, &t);
	अगर (ret)
		वापस ret;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		स_नकल(venकरोr_id, t->rx.buf, size);

	ph->xops->xfer_put(ph, t);

	वापस ret;
पूर्ण

/**
 * scmi_base_implementation_version_get() - माला_लो a venकरोr-specअगरic
 *	implementation 32-bit version. The क्रमmat of the version number is
 *	venकरोr-specअगरic
 *
 * @ph: SCMI protocol handle
 *
 * Return: 0 on success, अन्यथा appropriate SCMI error.
 */
अटल पूर्णांक
scmi_base_implementation_version_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक ret;
	__le32 *impl_ver;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_revision_info *rev = ph->get_priv(ph);

	ret = ph->xops->xfer_get_init(ph, BASE_DISCOVER_IMPLEMENT_VERSION,
				      0, माप(*impl_ver), &t);
	अगर (ret)
		वापस ret;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		impl_ver = t->rx.buf;
		rev->impl_ver = le32_to_cpu(*impl_ver);
	पूर्ण

	ph->xops->xfer_put(ph, t);

	वापस ret;
पूर्ण

/**
 * scmi_base_implementation_list_get() - माला_लो the list of protocols it is
 *	OSPM is allowed to access
 *
 * @ph: SCMI protocol handle
 * @protocols_imp: poपूर्णांकer to hold the list of protocol identअगरiers
 *
 * Return: 0 on success, अन्यथा appropriate SCMI error.
 */
अटल पूर्णांक
scmi_base_implementation_list_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u8 *protocols_imp)
अणु
	u8 *list;
	पूर्णांक ret, loop;
	काष्ठा scmi_xfer *t;
	__le32 *num_skip, *num_ret;
	u32 tot_num_ret = 0, loop_num_ret;
	काष्ठा device *dev = ph->dev;

	ret = ph->xops->xfer_get_init(ph, BASE_DISCOVER_LIST_PROTOCOLS,
				      माप(*num_skip), 0, &t);
	अगर (ret)
		वापस ret;

	num_skip = t->tx.buf;
	num_ret = t->rx.buf;
	list = t->rx.buf + माप(*num_ret);

	करो अणु
		/* Set the number of protocols to be skipped/alपढ़ोy पढ़ो */
		*num_skip = cpu_to_le32(tot_num_ret);

		ret = ph->xops->करो_xfer(ph, t);
		अगर (ret)
			अवरोध;

		loop_num_ret = le32_to_cpu(*num_ret);
		अगर (tot_num_ret + loop_num_ret > MAX_PROTOCOLS_IMP) अणु
			dev_err(dev, "No. of Protocol > MAX_PROTOCOLS_IMP");
			अवरोध;
		पूर्ण

		क्रम (loop = 0; loop < loop_num_ret; loop++)
			protocols_imp[tot_num_ret + loop] = *(list + loop);

		tot_num_ret += loop_num_ret;

		ph->xops->reset_rx_to_maxsz(ph, t);
	पूर्ण जबतक (loop_num_ret);

	ph->xops->xfer_put(ph, t);

	वापस ret;
पूर्ण

/**
 * scmi_base_discover_agent_get() - discover the name of an agent
 *
 * @ph: SCMI protocol handle
 * @id: Agent identअगरier
 * @name: Agent identअगरier ASCII string
 *
 * An agent id of 0 is reserved to identअगरy the platक्रमm itself.
 * Generally operating प्रणाली is represented as "OSPM"
 *
 * Return: 0 on success, अन्यथा appropriate SCMI error.
 */
अटल पूर्णांक scmi_base_discover_agent_get(स्थिर काष्ठा scmi_protocol_handle *ph,
					पूर्णांक id, अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, BASE_DISCOVER_AGENT,
				      माप(__le32), SCMI_MAX_STR_SIZE, &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(id, t->tx.buf);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		strlcpy(name, t->rx.buf, SCMI_MAX_STR_SIZE);

	ph->xops->xfer_put(ph, t);

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_base_error_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
				  bool enable)
अणु
	पूर्णांक ret;
	u32 evt_cntl = enable ? BASE_TP_NOTIFY_ALL : 0;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_base_error_notअगरy *cfg;

	ret = ph->xops->xfer_get_init(ph, BASE_NOTIFY_ERRORS,
				      माप(*cfg), 0, &t);
	अगर (ret)
		वापस ret;

	cfg = t->tx.buf;
	cfg->event_control = cpu_to_le32(evt_cntl);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_base_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret;

	ret = scmi_base_error_notअगरy(ph, enable);
	अगर (ret)
		pr_debug("FAIL_ENABLED - evt[%X] ret:%d\n", evt_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *scmi_base_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
					  u8 evt_id, kसमय_प्रकार बारtamp,
					  स्थिर व्योम *payld, माप_प्रकार payld_sz,
					  व्योम *report, u32 *src_id)
अणु
	पूर्णांक i;
	स्थिर काष्ठा scmi_base_error_notअगरy_payld *p = payld;
	काष्ठा scmi_base_error_report *r = report;

	/*
	 * BaseError notअगरication payload is variable in size but
	 * up to a maximum length determined by the काष्ठा ponted by p.
	 * Instead payld_sz is the effective length of this notअगरication
	 * payload so cannot be greater of the maximum allowed size as
	 * poपूर्णांकed by p.
	 */
	अगर (evt_id != SCMI_EVENT_BASE_ERROR_EVENT || माप(*p) < payld_sz)
		वापस शून्य;

	r->बारtamp = बारtamp;
	r->agent_id = le32_to_cpu(p->agent_id);
	r->fatal = IS_FATAL_ERROR(le32_to_cpu(p->error_status));
	r->cmd_count = ERROR_CMD_COUNT(le32_to_cpu(p->error_status));
	क्रम (i = 0; i < r->cmd_count; i++)
		r->reports[i] = le64_to_cpu(p->msg_reports[i]);
	*src_id = 0;

	वापस r;
पूर्ण

अटल स्थिर काष्ठा scmi_event base_events[] = अणु
	अणु
		.id = SCMI_EVENT_BASE_ERROR_EVENT,
		.max_payld_sz = माप(काष्ठा scmi_base_error_notअगरy_payld),
		.max_report_sz = माप(काष्ठा scmi_base_error_report) +
				  SCMI_BASE_MAX_CMD_ERR_COUNT * माप(u64),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops base_event_ops = अणु
	.set_notअगरy_enabled = scmi_base_set_notअगरy_enabled,
	.fill_custom_report = scmi_base_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events base_protocol_events = अणु
	.queue_sz = 4 * SCMI_PROTO_QUEUE_SZ,
	.ops = &base_event_ops,
	.evts = base_events,
	.num_events = ARRAY_SIZE(base_events),
	.num_sources = SCMI_BASE_NUM_SOURCES,
पूर्ण;

अटल पूर्णांक scmi_base_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक id, ret;
	u8 *prot_imp;
	u32 version;
	अक्षर name[SCMI_MAX_STR_SIZE];
	काष्ठा device *dev = ph->dev;
	काष्ठा scmi_revision_info *rev = scmi_revision_area_get(ph);

	ret = ph->xops->version_get(ph, &version);
	अगर (ret)
		वापस ret;

	prot_imp = devm_kसुस्मृति(dev, MAX_PROTOCOLS_IMP, माप(u8), GFP_KERNEL);
	अगर (!prot_imp)
		वापस -ENOMEM;

	rev->major_ver = PROTOCOL_REV_MAJOR(version),
	rev->minor_ver = PROTOCOL_REV_MINOR(version);
	ph->set_priv(ph, rev);

	scmi_base_attributes_get(ph);
	scmi_base_venकरोr_id_get(ph, false);
	scmi_base_venकरोr_id_get(ph, true);
	scmi_base_implementation_version_get(ph);
	scmi_base_implementation_list_get(ph, prot_imp);

	scmi_setup_protocol_implemented(ph, prot_imp);

	dev_info(dev, "SCMI Protocol v%d.%d '%s:%s' Firmware version 0x%x\n",
		 rev->major_ver, rev->minor_ver, rev->venकरोr_id,
		 rev->sub_venकरोr_id, rev->impl_ver);
	dev_dbg(dev, "Found %d protocol(s) %d agent(s)\n", rev->num_protocols,
		rev->num_agents);

	क्रम (id = 0; id < rev->num_agents; id++) अणु
		scmi_base_discover_agent_get(ph, id, name);
		dev_dbg(dev, "Agent %d: %s\n", id, name);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_base = अणु
	.id = SCMI_PROTOCOL_BASE,
	.owner = शून्य,
	.instance_init = &scmi_base_protocol_init,
	.ops = शून्य,
	.events = &base_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(base, scmi_base)
