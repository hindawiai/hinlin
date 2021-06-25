<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MIPI SyS-T framing protocol क्रम STM devices.
 * Copyright (c) 2018, Intel Corporation.
 */

#समावेश <linux/configfs.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/sपंचांग.h>
#समावेश "stm.h"

क्रमागत sys_t_message_type अणु
	MIPI_SYST_TYPE_BUILD	= 0,
	MIPI_SYST_TYPE_SHORT32,
	MIPI_SYST_TYPE_STRING,
	MIPI_SYST_TYPE_CATALOG,
	MIPI_SYST_TYPE_RAW	= 6,
	MIPI_SYST_TYPE_SHORT64,
	MIPI_SYST_TYPE_CLOCK,
पूर्ण;

क्रमागत sys_t_message_severity अणु
	MIPI_SYST_SEVERITY_MAX	= 0,
	MIPI_SYST_SEVERITY_FATAL,
	MIPI_SYST_SEVERITY_ERROR,
	MIPI_SYST_SEVERITY_WARNING,
	MIPI_SYST_SEVERITY_INFO,
	MIPI_SYST_SEVERITY_USER1,
	MIPI_SYST_SEVERITY_USER2,
	MIPI_SYST_SEVERITY_DEBUG,
पूर्ण;

क्रमागत sys_t_message_build_subtype अणु
	MIPI_SYST_BUILD_ID_COMPACT32 = 0,
	MIPI_SYST_BUILD_ID_COMPACT64,
	MIPI_SYST_BUILD_ID_LONG,
पूर्ण;

क्रमागत sys_t_message_घड़ी_subtype अणु
	MIPI_SYST_CLOCK_TRANSPORT_SYNC = 1,
पूर्ण;

क्रमागत sys_t_message_string_subtype अणु
	MIPI_SYST_STRING_GENERIC	= 1,
	MIPI_SYST_STRING_FUNCTIONENTER,
	MIPI_SYST_STRING_FUNCTIONEXIT,
	MIPI_SYST_STRING_INVALIDPARAM	= 5,
	MIPI_SYST_STRING_ASSERT		= 7,
	MIPI_SYST_STRING_PRINTF_32	= 11,
	MIPI_SYST_STRING_PRINTF_64	= 12,
पूर्ण;

#घोषणा MIPI_SYST_TYPE(t)		((u32)(MIPI_SYST_TYPE_ ## t))
#घोषणा MIPI_SYST_SEVERITY(s)		((u32)(MIPI_SYST_SEVERITY_ ## s) << 4)
#घोषणा MIPI_SYST_OPT_LOC		BIT(8)
#घोषणा MIPI_SYST_OPT_LEN		BIT(9)
#घोषणा MIPI_SYST_OPT_CHK		BIT(10)
#घोषणा MIPI_SYST_OPT_TS		BIT(11)
#घोषणा MIPI_SYST_UNIT(u)		((u32)(u) << 12)
#घोषणा MIPI_SYST_ORIGIN(o)		((u32)(o) << 16)
#घोषणा MIPI_SYST_OPT_GUID		BIT(23)
#घोषणा MIPI_SYST_SUBTYPE(s)		((u32)(MIPI_SYST_ ## s) << 24)
#घोषणा MIPI_SYST_UNITLARGE(u)		(MIPI_SYST_UNIT(u & 0xf) | \
					 MIPI_SYST_ORIGIN(u >> 4))
#घोषणा MIPI_SYST_TYPES(t, s)		(MIPI_SYST_TYPE(t) | \
					 MIPI_SYST_SUBTYPE(t ## _ ## s))

#घोषणा DATA_HEADER	(MIPI_SYST_TYPES(STRING, GENERIC)	| \
			 MIPI_SYST_SEVERITY(INFO)		| \
			 MIPI_SYST_OPT_GUID)

#घोषणा CLOCK_SYNC_HEADER	(MIPI_SYST_TYPES(CLOCK, TRANSPORT_SYNC)	| \
				 MIPI_SYST_SEVERITY(MAX))

काष्ठा sys_t_policy_node अणु
	uuid_t		uuid;
	bool		करो_len;
	अचिन्हित दीर्घ	ts_पूर्णांकerval;
	अचिन्हित दीर्घ	घड़ीsync_पूर्णांकerval;
पूर्ण;

काष्ठा sys_t_output अणु
	काष्ठा sys_t_policy_node	node;
	अचिन्हित दीर्घ	ts_jअगरfies;
	अचिन्हित दीर्घ	घड़ीsync_jअगरfies;
पूर्ण;

अटल व्योम sys_t_policy_node_init(व्योम *priv)
अणु
	काष्ठा sys_t_policy_node *pn = priv;

	uuid_gen(&pn->uuid);
पूर्ण

अटल पूर्णांक sys_t_output_खोलो(व्योम *priv, काष्ठा sपंचांग_output *output)
अणु
	काष्ठा sys_t_policy_node *pn = priv;
	काष्ठा sys_t_output *opriv;

	opriv = kzalloc(माप(*opriv), GFP_ATOMIC);
	अगर (!opriv)
		वापस -ENOMEM;

	स_नकल(&opriv->node, pn, माप(opriv->node));
	output->pdrv_निजी = opriv;

	वापस 0;
पूर्ण

अटल व्योम sys_t_output_बंद(काष्ठा sपंचांग_output *output)
अणु
	kमुक्त(output->pdrv_निजी);
पूर्ण

अटल sमाप_प्रकार sys_t_policy_uuid_show(काष्ठा config_item *item,
				      अक्षर *page)
अणु
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);

	वापस प्र_लिखो(page, "%pU\n", &pn->uuid);
पूर्ण

अटल sमाप_प्रकार
sys_t_policy_uuid_store(काष्ठा config_item *item, स्थिर अक्षर *page,
			माप_प्रकार count)
अणु
	काष्ठा mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);
	पूर्णांक ret;

	mutex_lock(mutexp);
	ret = uuid_parse(page, &pn->uuid);
	mutex_unlock(mutexp);

	वापस ret < 0 ? ret : count;
पूर्ण

CONFIGFS_ATTR(sys_t_policy_, uuid);

अटल sमाप_प्रकार sys_t_policy_करो_len_show(काष्ठा config_item *item,
				      अक्षर *page)
अणु
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);

	वापस प्र_लिखो(page, "%d\n", pn->करो_len);
पूर्ण

अटल sमाप_प्रकार
sys_t_policy_करो_len_store(काष्ठा config_item *item, स्थिर अक्षर *page,
			माप_प्रकार count)
अणु
	काष्ठा mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);
	पूर्णांक ret;

	mutex_lock(mutexp);
	ret = kstrtobool(page, &pn->करो_len);
	mutex_unlock(mutexp);

	वापस ret ? ret : count;
पूर्ण

CONFIGFS_ATTR(sys_t_policy_, करो_len);

अटल sमाप_प्रकार sys_t_policy_ts_पूर्णांकerval_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);

	वापस प्र_लिखो(page, "%u\n", jअगरfies_to_msecs(pn->ts_पूर्णांकerval));
पूर्ण

अटल sमाप_प्रकार
sys_t_policy_ts_पूर्णांकerval_store(काष्ठा config_item *item, स्थिर अक्षर *page,
			       माप_प्रकार count)
अणु
	काष्ठा mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);
	अचिन्हित पूर्णांक ms;
	पूर्णांक ret;

	mutex_lock(mutexp);
	ret = kstrtouपूर्णांक(page, 10, &ms);
	mutex_unlock(mutexp);

	अगर (!ret) अणु
		pn->ts_पूर्णांकerval = msecs_to_jअगरfies(ms);
		वापस count;
	पूर्ण

	वापस ret;
पूर्ण

CONFIGFS_ATTR(sys_t_policy_, ts_पूर्णांकerval);

अटल sमाप_प्रकार sys_t_policy_घड़ीsync_पूर्णांकerval_show(काष्ठा config_item *item,
						    अक्षर *page)
अणु
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);

	वापस प्र_लिखो(page, "%u\n", jअगरfies_to_msecs(pn->घड़ीsync_पूर्णांकerval));
पूर्ण

अटल sमाप_प्रकार
sys_t_policy_घड़ीsync_पूर्णांकerval_store(काष्ठा config_item *item,
				      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा mutex *mutexp = &item->ci_group->cg_subsys->su_mutex;
	काष्ठा sys_t_policy_node *pn = to_pdrv_policy_node(item);
	अचिन्हित पूर्णांक ms;
	पूर्णांक ret;

	mutex_lock(mutexp);
	ret = kstrtouपूर्णांक(page, 10, &ms);
	mutex_unlock(mutexp);

	अगर (!ret) अणु
		pn->घड़ीsync_पूर्णांकerval = msecs_to_jअगरfies(ms);
		वापस count;
	पूर्ण

	वापस ret;
पूर्ण

CONFIGFS_ATTR(sys_t_policy_, घड़ीsync_पूर्णांकerval);

अटल काष्ठा configfs_attribute *sys_t_policy_attrs[] = अणु
	&sys_t_policy_attr_uuid,
	&sys_t_policy_attr_करो_len,
	&sys_t_policy_attr_ts_पूर्णांकerval,
	&sys_t_policy_attr_घड़ीsync_पूर्णांकerval,
	शून्य,
पूर्ण;

अटल अंतरभूत bool sys_t_need_ts(काष्ठा sys_t_output *op)
अणु
	अगर (op->node.ts_पूर्णांकerval &&
	    समय_after(jअगरfies, op->ts_jअगरfies + op->node.ts_पूर्णांकerval)) अणु
		op->ts_jअगरfies = jअगरfies;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sys_t_need_घड़ी_sync(काष्ठा sys_t_output *op)
अणु
	अगर (op->node.घड़ीsync_पूर्णांकerval &&
	    समय_after(jअगरfies,
		       op->घड़ीsync_jअगरfies + op->node.घड़ीsync_पूर्णांकerval)) अणु
		op->घड़ीsync_jअगरfies = jअगरfies;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल sमाप_प्रकार
sys_t_घड़ी_sync(काष्ठा sपंचांग_data *data, अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक c)
अणु
	u32 header = CLOCK_SYNC_HEADER;
	स्थिर अचिन्हित अक्षर nil = 0;
	u64 payload[2]; /* Clock value and frequency */
	sमाप_प्रकार sz;

	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&header);
	अगर (sz <= 0)
		वापस sz;

	payload[0] = kसमय_get_real_ns();
	payload[1] = NSEC_PER_SEC;
	sz = sपंचांग_data_ग_लिखो(data, m, c, false, &payload, माप(payload));
	अगर (sz <= 0)
		वापस sz;

	data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	वापस माप(header) + माप(payload);
पूर्ण

अटल sमाप_प्रकार sys_t_ग_लिखो(काष्ठा sपंचांग_data *data, काष्ठा sपंचांग_output *output,
			   अचिन्हित पूर्णांक chan, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sys_t_output *op = output->pdrv_निजी;
	अचिन्हित पूर्णांक c = output->channel + chan;
	अचिन्हित पूर्णांक m = output->master;
	स्थिर अचिन्हित अक्षर nil = 0;
	u32 header = DATA_HEADER;
	u8 uuid[UUID_SIZE];
	sमाप_प्रकार sz;

	/* We require an existing policy node to proceed */
	अगर (!op)
		वापस -EINVAL;

	अगर (sys_t_need_घड़ी_sync(op)) अणु
		sz = sys_t_घड़ी_sync(data, m, c);
		अगर (sz <= 0)
			वापस sz;
	पूर्ण

	अगर (op->node.करो_len)
		header |= MIPI_SYST_OPT_LEN;
	अगर (sys_t_need_ts(op))
		header |= MIPI_SYST_OPT_TS;

	/*
	 * STP framing rules क्रम SyS-T frames:
	 *   * the first packet of the SyS-T frame is बारtamped;
	 *   * the last packet is a FLAG.
	 */
	/* Message layout: HEADER / GUID / [LENGTH /][TIMESTAMP /] DATA */
	/* HEADER */
	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&header);
	अगर (sz <= 0)
		वापस sz;

	/* GUID */
	export_uuid(uuid, &op->node.uuid);
	sz = sपंचांग_data_ग_लिखो(data, m, c, false, uuid, माप(op->node.uuid));
	अगर (sz <= 0)
		वापस sz;

	/* [LENGTH] */
	अगर (op->node.करो_len) अणु
		u16 length = count;

		sz = data->packet(data, m, c, STP_PACKET_DATA, 0, 2,
				  (u8 *)&length);
		अगर (sz <= 0)
			वापस sz;
	पूर्ण

	/* [TIMESTAMP] */
	अगर (header & MIPI_SYST_OPT_TS) अणु
		u64 ts = kसमय_get_real_ns();

		sz = sपंचांग_data_ग_लिखो(data, m, c, false, &ts, माप(ts));
		अगर (sz <= 0)
			वापस sz;
	पूर्ण

	/* DATA */
	sz = sपंचांग_data_ग_लिखो(data, m, c, false, buf, count);
	अगर (sz > 0)
		data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	वापस sz;
पूर्ण

अटल स्थिर काष्ठा sपंचांग_protocol_driver sys_t_pdrv = अणु
	.owner			= THIS_MODULE,
	.name			= "p_sys-t",
	.priv_sz		= माप(काष्ठा sys_t_policy_node),
	.ग_लिखो			= sys_t_ग_लिखो,
	.policy_attr		= sys_t_policy_attrs,
	.policy_node_init	= sys_t_policy_node_init,
	.output_खोलो		= sys_t_output_खोलो,
	.output_बंद		= sys_t_output_बंद,
पूर्ण;

अटल पूर्णांक sys_t_sपंचांग_init(व्योम)
अणु
	वापस sपंचांग_रेजिस्टर_protocol(&sys_t_pdrv);
पूर्ण

अटल व्योम sys_t_sपंचांग_निकास(व्योम)
अणु
	sपंचांग_unरेजिस्टर_protocol(&sys_t_pdrv);
पूर्ण

module_init(sys_t_sपंचांग_init);
module_निकास(sys_t_sपंचांग_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MIPI SyS-T STM framing protocol driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
