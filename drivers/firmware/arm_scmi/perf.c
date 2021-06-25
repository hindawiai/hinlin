<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Perक्रमmance Protocol
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications PERF - " fmt

#समावेश <linux/bits.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/sort.h>

#समावेश "common.h"
#समावेश "notify.h"

क्रमागत scmi_perक्रमmance_protocol_cmd अणु
	PERF_DOMAIN_ATTRIBUTES = 0x3,
	PERF_DESCRIBE_LEVELS = 0x4,
	PERF_LIMITS_SET = 0x5,
	PERF_LIMITS_GET = 0x6,
	PERF_LEVEL_SET = 0x7,
	PERF_LEVEL_GET = 0x8,
	PERF_NOTIFY_LIMITS = 0x9,
	PERF_NOTIFY_LEVEL = 0xa,
	PERF_DESCRIBE_FASTCHANNEL = 0xb,
पूर्ण;

काष्ठा scmi_opp अणु
	u32 perf;
	u32 घातer;
	u32 trans_latency_us;
पूर्ण;

काष्ठा scmi_msg_resp_perf_attributes अणु
	__le16 num_करोमुख्यs;
	__le16 flags;
#घोषणा POWER_SCALE_IN_MILLIWATT(x)	((x) & BIT(0))
	__le32 stats_addr_low;
	__le32 stats_addr_high;
	__le32 stats_size;
पूर्ण;

काष्ठा scmi_msg_resp_perf_करोमुख्य_attributes अणु
	__le32 flags;
#घोषणा SUPPORTS_SET_LIMITS(x)		((x) & BIT(31))
#घोषणा SUPPORTS_SET_PERF_LVL(x)	((x) & BIT(30))
#घोषणा SUPPORTS_PERF_LIMIT_NOTIFY(x)	((x) & BIT(29))
#घोषणा SUPPORTS_PERF_LEVEL_NOTIFY(x)	((x) & BIT(28))
#घोषणा SUPPORTS_PERF_FASTCHANNELS(x)	((x) & BIT(27))
	__le32 rate_limit_us;
	__le32 sustained_freq_khz;
	__le32 sustained_perf_level;
	    u8 name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_msg_perf_describe_levels अणु
	__le32 करोमुख्य;
	__le32 level_index;
पूर्ण;

काष्ठा scmi_perf_set_limits अणु
	__le32 करोमुख्य;
	__le32 max_level;
	__le32 min_level;
पूर्ण;

काष्ठा scmi_perf_get_limits अणु
	__le32 max_level;
	__le32 min_level;
पूर्ण;

काष्ठा scmi_perf_set_level अणु
	__le32 करोमुख्य;
	__le32 level;
पूर्ण;

काष्ठा scmi_perf_notअगरy_level_or_limits अणु
	__le32 करोमुख्य;
	__le32 notअगरy_enable;
पूर्ण;

काष्ठा scmi_perf_limits_notअगरy_payld अणु
	__le32 agent_id;
	__le32 करोमुख्य_id;
	__le32 range_max;
	__le32 range_min;
पूर्ण;

काष्ठा scmi_perf_level_notअगरy_payld अणु
	__le32 agent_id;
	__le32 करोमुख्य_id;
	__le32 perक्रमmance_level;
पूर्ण;

काष्ठा scmi_msg_resp_perf_describe_levels अणु
	__le16 num_वापसed;
	__le16 num_reमुख्यing;
	काष्ठा अणु
		__le32 perf_val;
		__le32 घातer;
		__le16 transition_latency_us;
		__le16 reserved;
	पूर्ण opp[];
पूर्ण;

काष्ठा scmi_perf_get_fc_info अणु
	__le32 करोमुख्य;
	__le32 message_id;
पूर्ण;

काष्ठा scmi_msg_resp_perf_desc_fc अणु
	__le32 attr;
#घोषणा SUPPORTS_DOORBELL(x)		((x) & BIT(0))
#घोषणा DOORBELL_REG_WIDTH(x)		FIELD_GET(GENMASK(2, 1), (x))
	__le32 rate_limit;
	__le32 chan_addr_low;
	__le32 chan_addr_high;
	__le32 chan_size;
	__le32 db_addr_low;
	__le32 db_addr_high;
	__le32 db_set_lmask;
	__le32 db_set_hmask;
	__le32 db_preserve_lmask;
	__le32 db_preserve_hmask;
पूर्ण;

काष्ठा scmi_fc_db_info अणु
	पूर्णांक width;
	u64 set;
	u64 mask;
	व्योम __iomem *addr;
पूर्ण;

काष्ठा scmi_fc_info अणु
	व्योम __iomem *level_set_addr;
	व्योम __iomem *limit_set_addr;
	व्योम __iomem *level_get_addr;
	व्योम __iomem *limit_get_addr;
	काष्ठा scmi_fc_db_info *level_set_db;
	काष्ठा scmi_fc_db_info *limit_set_db;
पूर्ण;

काष्ठा perf_करोm_info अणु
	bool set_limits;
	bool set_perf;
	bool perf_limit_notअगरy;
	bool perf_level_notअगरy;
	bool perf_fastchannels;
	u32 opp_count;
	u32 sustained_freq_khz;
	u32 sustained_perf_level;
	u32 mult_factor;
	अक्षर name[SCMI_MAX_STR_SIZE];
	काष्ठा scmi_opp opp[MAX_OPPS];
	काष्ठा scmi_fc_info *fc_info;
पूर्ण;

काष्ठा scmi_perf_info अणु
	u32 version;
	पूर्णांक num_करोमुख्यs;
	bool घातer_scale_mw;
	u64 stats_addr;
	u32 stats_size;
	काष्ठा perf_करोm_info *करोm_info;
पूर्ण;

अटल क्रमागत scmi_perक्रमmance_protocol_cmd evt_2_cmd[] = अणु
	PERF_NOTIFY_LIMITS,
	PERF_NOTIFY_LEVEL,
पूर्ण;

अटल पूर्णांक scmi_perf_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				    काष्ठा scmi_perf_info *pi)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_perf_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES, 0,
				      माप(*attr), &t);
	अगर (ret)
		वापस ret;

	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		u16 flags = le16_to_cpu(attr->flags);

		pi->num_करोमुख्यs = le16_to_cpu(attr->num_करोमुख्यs);
		pi->घातer_scale_mw = POWER_SCALE_IN_MILLIWATT(flags);
		pi->stats_addr = le32_to_cpu(attr->stats_addr_low) |
				(u64)le32_to_cpu(attr->stats_addr_high) << 32;
		pi->stats_size = le32_to_cpu(attr->stats_size);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_perf_करोमुख्य_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				u32 करोमुख्य, काष्ठा perf_करोm_info *करोm_info)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_perf_करोमुख्य_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, PERF_DOMAIN_ATTRIBUTES,
				     माप(करोमुख्य), माप(*attr), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य, t->tx.buf);
	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		u32 flags = le32_to_cpu(attr->flags);

		करोm_info->set_limits = SUPPORTS_SET_LIMITS(flags);
		करोm_info->set_perf = SUPPORTS_SET_PERF_LVL(flags);
		करोm_info->perf_limit_notअगरy = SUPPORTS_PERF_LIMIT_NOTIFY(flags);
		करोm_info->perf_level_notअगरy = SUPPORTS_PERF_LEVEL_NOTIFY(flags);
		करोm_info->perf_fastchannels = SUPPORTS_PERF_FASTCHANNELS(flags);
		करोm_info->sustained_freq_khz =
					le32_to_cpu(attr->sustained_freq_khz);
		करोm_info->sustained_perf_level =
					le32_to_cpu(attr->sustained_perf_level);
		अगर (!करोm_info->sustained_freq_khz ||
		    !करोm_info->sustained_perf_level)
			/* CPUFreq converts to kHz, hence शेष 1000 */
			करोm_info->mult_factor =	1000;
		अन्यथा
			करोm_info->mult_factor =
					(करोm_info->sustained_freq_khz * 1000) /
					करोm_info->sustained_perf_level;
		strlcpy(करोm_info->name, attr->name, SCMI_MAX_STR_SIZE);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक opp_cmp_func(स्थिर व्योम *opp1, स्थिर व्योम *opp2)
अणु
	स्थिर काष्ठा scmi_opp *t1 = opp1, *t2 = opp2;

	वापस t1->perf - t2->perf;
पूर्ण

अटल पूर्णांक
scmi_perf_describe_levels_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			      काष्ठा perf_करोm_info *perf_करोm)
अणु
	पूर्णांक ret, cnt;
	u32 tot_opp_cnt = 0;
	u16 num_वापसed, num_reमुख्यing;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_opp *opp;
	काष्ठा scmi_msg_perf_describe_levels *करोm_info;
	काष्ठा scmi_msg_resp_perf_describe_levels *level_info;

	ret = ph->xops->xfer_get_init(ph, PERF_DESCRIBE_LEVELS,
				      माप(*करोm_info), 0, &t);
	अगर (ret)
		वापस ret;

	करोm_info = t->tx.buf;
	level_info = t->rx.buf;

	करो अणु
		करोm_info->करोमुख्य = cpu_to_le32(करोमुख्य);
		/* Set the number of OPPs to be skipped/alपढ़ोy पढ़ो */
		करोm_info->level_index = cpu_to_le32(tot_opp_cnt);

		ret = ph->xops->करो_xfer(ph, t);
		अगर (ret)
			अवरोध;

		num_वापसed = le16_to_cpu(level_info->num_वापसed);
		num_reमुख्यing = le16_to_cpu(level_info->num_reमुख्यing);
		अगर (tot_opp_cnt + num_वापसed > MAX_OPPS) अणु
			dev_err(ph->dev, "No. of OPPs exceeded MAX_OPPS");
			अवरोध;
		पूर्ण

		opp = &perf_करोm->opp[tot_opp_cnt];
		क्रम (cnt = 0; cnt < num_वापसed; cnt++, opp++) अणु
			opp->perf = le32_to_cpu(level_info->opp[cnt].perf_val);
			opp->घातer = le32_to_cpu(level_info->opp[cnt].घातer);
			opp->trans_latency_us = le16_to_cpu
				(level_info->opp[cnt].transition_latency_us);

			dev_dbg(ph->dev, "Level %d Power %d Latency %dus\n",
				opp->perf, opp->घातer, opp->trans_latency_us);
		पूर्ण

		tot_opp_cnt += num_वापसed;

		ph->xops->reset_rx_to_maxsz(ph, t);
		/*
		 * check क्रम both वापसed and reमुख्यing to aव्योम infinite
		 * loop due to buggy firmware
		 */
	पूर्ण जबतक (num_वापसed && num_reमुख्यing);

	perf_करोm->opp_count = tot_opp_cnt;
	ph->xops->xfer_put(ph, t);

	sort(perf_करोm->opp, tot_opp_cnt, माप(*opp), opp_cmp_func, शून्य);
	वापस ret;
पूर्ण

#घोषणा SCMI_PERF_FC_RING_DB(w)				\
करो अणु							\
	u##w val = 0;					\
							\
	अगर (db->mask)					\
		val = ioपढ़ो##w(db->addr) & db->mask;	\
	ioग_लिखो##w((u##w)db->set | val, db->addr);	\
पूर्ण जबतक (0)

अटल व्योम scmi_perf_fc_ring_db(काष्ठा scmi_fc_db_info *db)
अणु
	अगर (!db || !db->addr)
		वापस;

	अगर (db->width == 1)
		SCMI_PERF_FC_RING_DB(8);
	अन्यथा अगर (db->width == 2)
		SCMI_PERF_FC_RING_DB(16);
	अन्यथा अगर (db->width == 4)
		SCMI_PERF_FC_RING_DB(32);
	अन्यथा /* db->width == 8 */
#अगर_घोषित CONFIG_64BIT
		SCMI_PERF_FC_RING_DB(64);
#अन्यथा
	अणु
		u64 val = 0;

		अगर (db->mask)
			val = ioपढ़ो64_hi_lo(db->addr) & db->mask;
		ioग_लिखो64_hi_lo(db->set | val, db->addr);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक scmi_perf_mb_limits_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य, u32 max_perf, u32 min_perf)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_perf_set_limits *limits;

	ret = ph->xops->xfer_get_init(ph, PERF_LIMITS_SET,
				      माप(*limits), 0, &t);
	अगर (ret)
		वापस ret;

	limits = t->tx.buf;
	limits->करोमुख्य = cpu_to_le32(करोमुख्य);
	limits->max_level = cpu_to_le32(max_perf);
	limits->min_level = cpu_to_le32(min_perf);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_perf_limits_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				u32 करोमुख्य, u32 max_perf, u32 min_perf)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	अगर (करोm->fc_info && करोm->fc_info->limit_set_addr) अणु
		ioग_लिखो32(max_perf, करोm->fc_info->limit_set_addr);
		ioग_लिखो32(min_perf, करोm->fc_info->limit_set_addr + 4);
		scmi_perf_fc_ring_db(करोm->fc_info->limit_set_db);
		वापस 0;
	पूर्ण

	वापस scmi_perf_mb_limits_set(ph, करोमुख्य, max_perf, min_perf);
पूर्ण

अटल पूर्णांक scmi_perf_mb_limits_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य, u32 *max_perf, u32 *min_perf)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_perf_get_limits *limits;

	ret = ph->xops->xfer_get_init(ph, PERF_LIMITS_GET,
				      माप(__le32), 0, &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(करोमुख्य, t->tx.buf);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		limits = t->rx.buf;

		*max_perf = le32_to_cpu(limits->max_level);
		*min_perf = le32_to_cpu(limits->min_level);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_perf_limits_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				u32 करोमुख्य, u32 *max_perf, u32 *min_perf)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	अगर (करोm->fc_info && करोm->fc_info->limit_get_addr) अणु
		*max_perf = ioपढ़ो32(करोm->fc_info->limit_get_addr);
		*min_perf = ioपढ़ो32(करोm->fc_info->limit_get_addr + 4);
		वापस 0;
	पूर्ण

	वापस scmi_perf_mb_limits_get(ph, करोमुख्य, max_perf, min_perf);
पूर्ण

अटल पूर्णांक scmi_perf_mb_level_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 करोमुख्य, u32 level, bool poll)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_perf_set_level *lvl;

	ret = ph->xops->xfer_get_init(ph, PERF_LEVEL_SET, माप(*lvl), 0, &t);
	अगर (ret)
		वापस ret;

	t->hdr.poll_completion = poll;
	lvl = t->tx.buf;
	lvl->करोमुख्य = cpu_to_le32(करोमुख्य);
	lvl->level = cpu_to_le32(level);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_perf_level_set(स्थिर काष्ठा scmi_protocol_handle *ph,
			       u32 करोमुख्य, u32 level, bool poll)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	अगर (करोm->fc_info && करोm->fc_info->level_set_addr) अणु
		ioग_लिखो32(level, करोm->fc_info->level_set_addr);
		scmi_perf_fc_ring_db(करोm->fc_info->level_set_db);
		वापस 0;
	पूर्ण

	वापस scmi_perf_mb_level_set(ph, करोमुख्य, level, poll);
पूर्ण

अटल पूर्णांक scmi_perf_mb_level_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 करोमुख्य, u32 *level, bool poll)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, PERF_LEVEL_GET,
				     माप(u32), माप(u32), &t);
	अगर (ret)
		वापस ret;

	t->hdr.poll_completion = poll;
	put_unaligned_le32(करोमुख्य, t->tx.buf);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		*level = get_unaligned_le32(t->rx.buf);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_perf_level_get(स्थिर काष्ठा scmi_protocol_handle *ph,
			       u32 करोमुख्य, u32 *level, bool poll)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	अगर (करोm->fc_info && करोm->fc_info->level_get_addr) अणु
		*level = ioपढ़ो32(करोm->fc_info->level_get_addr);
		वापस 0;
	पूर्ण

	वापस scmi_perf_mb_level_get(ph, करोमुख्य, level, poll);
पूर्ण

अटल पूर्णांक scmi_perf_level_limits_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
					 u32 करोमुख्य, पूर्णांक message_id,
					 bool enable)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_perf_notअगरy_level_or_limits *notअगरy;

	ret = ph->xops->xfer_get_init(ph, message_id, माप(*notअगरy), 0, &t);
	अगर (ret)
		वापस ret;

	notअगरy = t->tx.buf;
	notअगरy->करोमुख्य = cpu_to_le32(करोमुख्य);
	notअगरy->notअगरy_enable = enable ? cpu_to_le32(BIT(0)) : 0;

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल bool scmi_perf_fc_size_is_valid(u32 msg, u32 size)
अणु
	अगर ((msg == PERF_LEVEL_GET || msg == PERF_LEVEL_SET) && size == 4)
		वापस true;
	अगर ((msg == PERF_LIMITS_GET || msg == PERF_LIMITS_SET) && size == 8)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम
scmi_perf_करोमुख्य_desc_fc(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			 u32 message_id, व्योम __iomem **p_addr,
			 काष्ठा scmi_fc_db_info **p_db)
अणु
	पूर्णांक ret;
	u32 flags;
	u64 phys_addr;
	u8 size;
	व्योम __iomem *addr;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_fc_db_info *db;
	काष्ठा scmi_perf_get_fc_info *info;
	काष्ठा scmi_msg_resp_perf_desc_fc *resp;

	अगर (!p_addr)
		वापस;

	ret = ph->xops->xfer_get_init(ph, PERF_DESCRIBE_FASTCHANNEL,
				      माप(*info), माप(*resp), &t);
	अगर (ret)
		वापस;

	info = t->tx.buf;
	info->करोमुख्य = cpu_to_le32(करोमुख्य);
	info->message_id = cpu_to_le32(message_id);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (ret)
		जाओ err_xfer;

	resp = t->rx.buf;
	flags = le32_to_cpu(resp->attr);
	size = le32_to_cpu(resp->chan_size);
	अगर (!scmi_perf_fc_size_is_valid(message_id, size))
		जाओ err_xfer;

	phys_addr = le32_to_cpu(resp->chan_addr_low);
	phys_addr |= (u64)le32_to_cpu(resp->chan_addr_high) << 32;
	addr = devm_ioremap(ph->dev, phys_addr, size);
	अगर (!addr)
		जाओ err_xfer;
	*p_addr = addr;

	अगर (p_db && SUPPORTS_DOORBELL(flags)) अणु
		db = devm_kzalloc(ph->dev, माप(*db), GFP_KERNEL);
		अगर (!db)
			जाओ err_xfer;

		size = 1 << DOORBELL_REG_WIDTH(flags);
		phys_addr = le32_to_cpu(resp->db_addr_low);
		phys_addr |= (u64)le32_to_cpu(resp->db_addr_high) << 32;
		addr = devm_ioremap(ph->dev, phys_addr, size);
		अगर (!addr)
			जाओ err_xfer;

		db->addr = addr;
		db->width = size;
		db->set = le32_to_cpu(resp->db_set_lmask);
		db->set |= (u64)le32_to_cpu(resp->db_set_hmask) << 32;
		db->mask = le32_to_cpu(resp->db_preserve_lmask);
		db->mask |= (u64)le32_to_cpu(resp->db_preserve_hmask) << 32;
		*p_db = db;
	पूर्ण
err_xfer:
	ph->xops->xfer_put(ph, t);
पूर्ण

अटल व्योम scmi_perf_करोमुख्य_init_fc(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u32 करोमुख्य, काष्ठा scmi_fc_info **p_fc)
अणु
	काष्ठा scmi_fc_info *fc;

	fc = devm_kzalloc(ph->dev, माप(*fc), GFP_KERNEL);
	अगर (!fc)
		वापस;

	scmi_perf_करोमुख्य_desc_fc(ph, करोमुख्य, PERF_LEVEL_SET,
				 &fc->level_set_addr, &fc->level_set_db);
	scmi_perf_करोमुख्य_desc_fc(ph, करोमुख्य, PERF_LEVEL_GET,
				 &fc->level_get_addr, शून्य);
	scmi_perf_करोमुख्य_desc_fc(ph, करोमुख्य, PERF_LIMITS_SET,
				 &fc->limit_set_addr, &fc->limit_set_db);
	scmi_perf_करोमुख्य_desc_fc(ph, करोमुख्य, PERF_LIMITS_GET,
				 &fc->limit_get_addr, शून्य);
	*p_fc = fc;
पूर्ण

/* Device specअगरic ops */
अटल पूर्णांक scmi_dev_करोमुख्य_id(काष्ठा device *dev)
अणु
	काष्ठा of_phandle_args clkspec;

	अगर (of_parse_phandle_with_args(dev->of_node, "clocks", "#clock-cells",
				       0, &clkspec))
		वापस -EINVAL;

	वापस clkspec.args[0];
पूर्ण

अटल पूर्णांक scmi_dvfs_device_opps_add(स्थिर काष्ठा scmi_protocol_handle *ph,
				     काष्ठा device *dev)
अणु
	पूर्णांक idx, ret, करोमुख्य;
	अचिन्हित दीर्घ freq;
	काष्ठा scmi_opp *opp;
	काष्ठा perf_करोm_info *करोm;
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);

	करोमुख्य = scmi_dev_करोमुख्य_id(dev);
	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	करोm = pi->करोm_info + करोमुख्य;

	क्रम (opp = करोm->opp, idx = 0; idx < करोm->opp_count; idx++, opp++) अणु
		freq = opp->perf * करोm->mult_factor;

		ret = dev_pm_opp_add(dev, freq, 0);
		अगर (ret) अणु
			dev_warn(dev, "failed to add opp %luHz\n", freq);

			जबतक (idx-- > 0) अणु
				freq = (--opp)->perf * करोm->mult_factor;
				dev_pm_opp_हटाओ(dev, freq);
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
scmi_dvfs_transition_latency_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				 काष्ठा device *dev)
अणु
	काष्ठा perf_करोm_info *करोm;
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	पूर्णांक करोमुख्य = scmi_dev_करोमुख्य_id(dev);

	अगर (करोमुख्य < 0)
		वापस करोमुख्य;

	करोm = pi->करोm_info + करोमुख्य;
	/* uS to nS */
	वापस करोm->opp[करोm->opp_count - 1].trans_latency_us * 1000;
पूर्ण

अटल पूर्णांक scmi_dvfs_freq_set(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			      अचिन्हित दीर्घ freq, bool poll)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	वापस scmi_perf_level_set(ph, करोमुख्य, freq / करोm->mult_factor, poll);
पूर्ण

अटल पूर्णांक scmi_dvfs_freq_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 करोमुख्य,
			      अचिन्हित दीर्घ *freq, bool poll)
अणु
	पूर्णांक ret;
	u32 level;
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm = pi->करोm_info + करोमुख्य;

	ret = scmi_perf_level_get(ph, करोमुख्य, &level, poll);
	अगर (!ret)
		*freq = level * करोm->mult_factor;

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_dvfs_est_घातer_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 करोमुख्य, अचिन्हित दीर्घ *freq,
				   अचिन्हित दीर्घ *घातer)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);
	काष्ठा perf_करोm_info *करोm;
	अचिन्हित दीर्घ opp_freq;
	पूर्णांक idx, ret = -EINVAL;
	काष्ठा scmi_opp *opp;

	करोm = pi->करोm_info + करोमुख्य;
	अगर (!करोm)
		वापस -EIO;

	क्रम (opp = करोm->opp, idx = 0; idx < करोm->opp_count; idx++, opp++) अणु
		opp_freq = opp->perf * करोm->mult_factor;
		अगर (opp_freq < *freq)
			जारी;

		*freq = opp_freq;
		*घातer = opp->घातer;
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool scmi_fast_चयन_possible(स्थिर काष्ठा scmi_protocol_handle *ph,
				      काष्ठा device *dev)
अणु
	काष्ठा perf_करोm_info *करोm;
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);

	करोm = pi->करोm_info + scmi_dev_करोमुख्य_id(dev);

	वापस करोm->fc_info && करोm->fc_info->level_set_addr;
पूर्ण

अटल bool scmi_घातer_scale_mw_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);

	वापस pi->घातer_scale_mw;
पूर्ण

अटल स्थिर काष्ठा scmi_perf_proto_ops perf_proto_ops = अणु
	.limits_set = scmi_perf_limits_set,
	.limits_get = scmi_perf_limits_get,
	.level_set = scmi_perf_level_set,
	.level_get = scmi_perf_level_get,
	.device_करोमुख्य_id = scmi_dev_करोमुख्य_id,
	.transition_latency_get = scmi_dvfs_transition_latency_get,
	.device_opps_add = scmi_dvfs_device_opps_add,
	.freq_set = scmi_dvfs_freq_set,
	.freq_get = scmi_dvfs_freq_get,
	.est_घातer_get = scmi_dvfs_est_घातer_get,
	.fast_चयन_possible = scmi_fast_चयन_possible,
	.घातer_scale_mw_get = scmi_घातer_scale_mw_get,
पूर्ण;

अटल पूर्णांक scmi_perf_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret, cmd_id;

	अगर (evt_id >= ARRAY_SIZE(evt_2_cmd))
		वापस -EINVAL;

	cmd_id = evt_2_cmd[evt_id];
	ret = scmi_perf_level_limits_notअगरy(ph, src_id, cmd_id, enable);
	अगर (ret)
		pr_debug("FAIL_ENABLED - evt[%X] dom[%d] - ret:%d\n",
			 evt_id, src_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *scmi_perf_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
					  u8 evt_id, kसमय_प्रकार बारtamp,
					  स्थिर व्योम *payld, माप_प्रकार payld_sz,
					  व्योम *report, u32 *src_id)
अणु
	व्योम *rep = शून्य;

	चयन (evt_id) अणु
	हाल SCMI_EVENT_PERFORMANCE_LIMITS_CHANGED:
	अणु
		स्थिर काष्ठा scmi_perf_limits_notअगरy_payld *p = payld;
		काष्ठा scmi_perf_limits_report *r = report;

		अगर (माप(*p) != payld_sz)
			अवरोध;

		r->बारtamp = बारtamp;
		r->agent_id = le32_to_cpu(p->agent_id);
		r->करोमुख्य_id = le32_to_cpu(p->करोमुख्य_id);
		r->range_max = le32_to_cpu(p->range_max);
		r->range_min = le32_to_cpu(p->range_min);
		*src_id = r->करोमुख्य_id;
		rep = r;
		अवरोध;
	पूर्ण
	हाल SCMI_EVENT_PERFORMANCE_LEVEL_CHANGED:
	अणु
		स्थिर काष्ठा scmi_perf_level_notअगरy_payld *p = payld;
		काष्ठा scmi_perf_level_report *r = report;

		अगर (माप(*p) != payld_sz)
			अवरोध;

		r->बारtamp = बारtamp;
		r->agent_id = le32_to_cpu(p->agent_id);
		r->करोमुख्य_id = le32_to_cpu(p->करोमुख्य_id);
		r->perक्रमmance_level = le32_to_cpu(p->perक्रमmance_level);
		*src_id = r->करोमुख्य_id;
		rep = r;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस rep;
पूर्ण

अटल पूर्णांक scmi_perf_get_num_sources(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा scmi_perf_info *pi = ph->get_priv(ph);

	अगर (!pi)
		वापस -EINVAL;

	वापस pi->num_करोमुख्यs;
पूर्ण

अटल स्थिर काष्ठा scmi_event perf_events[] = अणु
	अणु
		.id = SCMI_EVENT_PERFORMANCE_LIMITS_CHANGED,
		.max_payld_sz = माप(काष्ठा scmi_perf_limits_notअगरy_payld),
		.max_report_sz = माप(काष्ठा scmi_perf_limits_report),
	पूर्ण,
	अणु
		.id = SCMI_EVENT_PERFORMANCE_LEVEL_CHANGED,
		.max_payld_sz = माप(काष्ठा scmi_perf_level_notअगरy_payld),
		.max_report_sz = माप(काष्ठा scmi_perf_level_report),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops perf_event_ops = अणु
	.get_num_sources = scmi_perf_get_num_sources,
	.set_notअगरy_enabled = scmi_perf_set_notअगरy_enabled,
	.fill_custom_report = scmi_perf_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events perf_protocol_events = अणु
	.queue_sz = SCMI_PROTO_QUEUE_SZ,
	.ops = &perf_event_ops,
	.evts = perf_events,
	.num_events = ARRAY_SIZE(perf_events),
पूर्ण;

अटल पूर्णांक scmi_perf_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	पूर्णांक करोमुख्य;
	u32 version;
	काष्ठा scmi_perf_info *pinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "Performance Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	pinfo = devm_kzalloc(ph->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस -ENOMEM;

	scmi_perf_attributes_get(ph, pinfo);

	pinfo->करोm_info = devm_kसुस्मृति(ph->dev, pinfo->num_करोमुख्यs,
				       माप(*pinfo->करोm_info), GFP_KERNEL);
	अगर (!pinfo->करोm_info)
		वापस -ENOMEM;

	क्रम (करोमुख्य = 0; करोमुख्य < pinfo->num_करोमुख्यs; करोमुख्य++) अणु
		काष्ठा perf_करोm_info *करोm = pinfo->करोm_info + करोमुख्य;

		scmi_perf_करोमुख्य_attributes_get(ph, करोमुख्य, करोm);
		scmi_perf_describe_levels_get(ph, करोमुख्य, करोm);

		अगर (करोm->perf_fastchannels)
			scmi_perf_करोमुख्य_init_fc(ph, करोमुख्य, &करोm->fc_info);
	पूर्ण

	pinfo->version = version;

	वापस ph->set_priv(ph, pinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_perf = अणु
	.id = SCMI_PROTOCOL_PERF,
	.owner = THIS_MODULE,
	.instance_init = &scmi_perf_protocol_init,
	.ops = &perf_proto_ops,
	.events = &perf_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(perf, scmi_perf)
