<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Clock Protocol
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/sort.h>

#समावेश "common.h"

क्रमागत scmi_घड़ी_protocol_cmd अणु
	CLOCK_ATTRIBUTES = 0x3,
	CLOCK_DESCRIBE_RATES = 0x4,
	CLOCK_RATE_SET = 0x5,
	CLOCK_RATE_GET = 0x6,
	CLOCK_CONFIG_SET = 0x7,
पूर्ण;

काष्ठा scmi_msg_resp_घड़ी_protocol_attributes अणु
	__le16 num_घड़ीs;
	u8 max_async_req;
	u8 reserved;
पूर्ण;

काष्ठा scmi_msg_resp_घड़ी_attributes अणु
	__le32 attributes;
#घोषणा	CLOCK_ENABLE	BIT(0)
	    u8 name[SCMI_MAX_STR_SIZE];
पूर्ण;

काष्ठा scmi_घड़ी_set_config अणु
	__le32 id;
	__le32 attributes;
पूर्ण;

काष्ठा scmi_msg_घड़ी_describe_rates अणु
	__le32 id;
	__le32 rate_index;
पूर्ण;

काष्ठा scmi_msg_resp_घड़ी_describe_rates अणु
	__le32 num_rates_flags;
#घोषणा NUM_RETURNED(x)		((x) & 0xfff)
#घोषणा RATE_DISCRETE(x)	!((x) & BIT(12))
#घोषणा NUM_REMAINING(x)	((x) >> 16)
	काष्ठा अणु
		__le32 value_low;
		__le32 value_high;
	पूर्ण rate[0];
#घोषणा RATE_TO_U64(X)		\
(अणु				\
	typeof(X) x = (X);	\
	le32_to_cpu((x).value_low) | (u64)le32_to_cpu((x).value_high) << 32; \
पूर्ण)
पूर्ण;

काष्ठा scmi_घड़ी_set_rate अणु
	__le32 flags;
#घोषणा CLOCK_SET_ASYNC		BIT(0)
#घोषणा CLOCK_SET_IGNORE_RESP	BIT(1)
#घोषणा CLOCK_SET_ROUND_UP	BIT(2)
#घोषणा CLOCK_SET_ROUND_AUTO	BIT(3)
	__le32 id;
	__le32 value_low;
	__le32 value_high;
पूर्ण;

काष्ठा घड़ी_info अणु
	u32 version;
	पूर्णांक num_घड़ीs;
	पूर्णांक max_async_req;
	atomic_t cur_async_req;
	काष्ठा scmi_घड़ी_info *clk;
पूर्ण;

अटल पूर्णांक
scmi_घड़ी_protocol_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				   काष्ठा घड़ी_info *ci)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_घड़ी_protocol_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES,
				      0, माप(*attr), &t);
	अगर (ret)
		वापस ret;

	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		ci->num_घड़ीs = le16_to_cpu(attr->num_घड़ीs);
		ci->max_async_req = attr->max_async_req;
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घड़ी_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u32 clk_id, काष्ठा scmi_घड़ी_info *clk)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_घड़ी_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, CLOCK_ATTRIBUTES,
				      माप(clk_id), माप(*attr), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(clk_id, t->tx.buf);
	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		strlcpy(clk->name, attr->name, SCMI_MAX_STR_SIZE);
	अन्यथा
		clk->name[0] = '\0';

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक rate_cmp_func(स्थिर व्योम *_r1, स्थिर व्योम *_r2)
अणु
	स्थिर u64 *r1 = _r1, *r2 = _r2;

	अगर (*r1 < *r2)
		वापस -1;
	अन्यथा अगर (*r1 == *r2)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक
scmi_घड़ी_describe_rates_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id,
			      काष्ठा scmi_घड़ी_info *clk)
अणु
	u64 *rate = शून्य;
	पूर्णांक ret, cnt;
	bool rate_discrete = false;
	u32 tot_rate_cnt = 0, rates_flag;
	u16 num_वापसed, num_reमुख्यing;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_घड़ी_describe_rates *clk_desc;
	काष्ठा scmi_msg_resp_घड़ी_describe_rates *rlist;

	ret = ph->xops->xfer_get_init(ph, CLOCK_DESCRIBE_RATES,
				      माप(*clk_desc), 0, &t);
	अगर (ret)
		वापस ret;

	clk_desc = t->tx.buf;
	rlist = t->rx.buf;

	करो अणु
		clk_desc->id = cpu_to_le32(clk_id);
		/* Set the number of rates to be skipped/alपढ़ोy पढ़ो */
		clk_desc->rate_index = cpu_to_le32(tot_rate_cnt);

		ret = ph->xops->करो_xfer(ph, t);
		अगर (ret)
			जाओ err;

		rates_flag = le32_to_cpu(rlist->num_rates_flags);
		num_reमुख्यing = NUM_REMAINING(rates_flag);
		rate_discrete = RATE_DISCRETE(rates_flag);
		num_वापसed = NUM_RETURNED(rates_flag);

		अगर (tot_rate_cnt + num_वापसed > SCMI_MAX_NUM_RATES) अणु
			dev_err(ph->dev, "No. of rates > MAX_NUM_RATES");
			अवरोध;
		पूर्ण

		अगर (!rate_discrete) अणु
			clk->range.min_rate = RATE_TO_U64(rlist->rate[0]);
			clk->range.max_rate = RATE_TO_U64(rlist->rate[1]);
			clk->range.step_size = RATE_TO_U64(rlist->rate[2]);
			dev_dbg(ph->dev, "Min %llu Max %llu Step %llu Hz\n",
				clk->range.min_rate, clk->range.max_rate,
				clk->range.step_size);
			अवरोध;
		पूर्ण

		rate = &clk->list.rates[tot_rate_cnt];
		क्रम (cnt = 0; cnt < num_वापसed; cnt++, rate++) अणु
			*rate = RATE_TO_U64(rlist->rate[cnt]);
			dev_dbg(ph->dev, "Rate %llu Hz\n", *rate);
		पूर्ण

		tot_rate_cnt += num_वापसed;

		ph->xops->reset_rx_to_maxsz(ph, t);
		/*
		 * check क्रम both वापसed and reमुख्यing to aव्योम infinite
		 * loop due to buggy firmware
		 */
	पूर्ण जबतक (num_वापसed && num_reमुख्यing);

	अगर (rate_discrete && rate) अणु
		clk->list.num_rates = tot_rate_cnt;
		sort(rate, tot_rate_cnt, माप(*rate), rate_cmp_func, शून्य);
	पूर्ण

	clk->rate_discrete = rate_discrete;

err:
	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_घड़ी_rate_get(स्थिर काष्ठा scmi_protocol_handle *ph,
		    u32 clk_id, u64 *value)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, CLOCK_RATE_GET,
				      माप(__le32), माप(u64), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(clk_id, t->tx.buf);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret)
		*value = get_unaligned_le64(t->rx.buf);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घड़ी_rate_set(स्थिर काष्ठा scmi_protocol_handle *ph,
			       u32 clk_id, u64 rate)
अणु
	पूर्णांक ret;
	u32 flags = 0;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_घड़ी_set_rate *cfg;
	काष्ठा घड़ी_info *ci = ph->get_priv(ph);

	ret = ph->xops->xfer_get_init(ph, CLOCK_RATE_SET, माप(*cfg), 0, &t);
	अगर (ret)
		वापस ret;

	अगर (ci->max_async_req &&
	    atomic_inc_वापस(&ci->cur_async_req) < ci->max_async_req)
		flags |= CLOCK_SET_ASYNC;

	cfg = t->tx.buf;
	cfg->flags = cpu_to_le32(flags);
	cfg->id = cpu_to_le32(clk_id);
	cfg->value_low = cpu_to_le32(rate & 0xffffffff);
	cfg->value_high = cpu_to_le32(rate >> 32);

	अगर (flags & CLOCK_SET_ASYNC)
		ret = ph->xops->करो_xfer_with_response(ph, t);
	अन्यथा
		ret = ph->xops->करो_xfer(ph, t);

	अगर (ci->max_async_req)
		atomic_dec(&ci->cur_async_req);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_घड़ी_config_set(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id,
		      u32 config)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_घड़ी_set_config *cfg;

	ret = ph->xops->xfer_get_init(ph, CLOCK_CONFIG_SET,
				      माप(*cfg), 0, &t);
	अगर (ret)
		वापस ret;

	cfg = t->tx.buf;
	cfg->id = cpu_to_le32(clk_id);
	cfg->attributes = cpu_to_le32(config);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घड़ी_enable(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id)
अणु
	वापस scmi_घड़ी_config_set(ph, clk_id, CLOCK_ENABLE);
पूर्ण

अटल पूर्णांक scmi_घड़ी_disable(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id)
अणु
	वापस scmi_घड़ी_config_set(ph, clk_id, 0);
पूर्ण

अटल पूर्णांक scmi_घड़ी_count_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा घड़ी_info *ci = ph->get_priv(ph);

	वापस ci->num_घड़ीs;
पूर्ण

अटल स्थिर काष्ठा scmi_घड़ी_info *
scmi_घड़ी_info_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 clk_id)
अणु
	काष्ठा घड़ी_info *ci = ph->get_priv(ph);
	काष्ठा scmi_घड़ी_info *clk = ci->clk + clk_id;

	अगर (!clk->name[0])
		वापस शून्य;

	वापस clk;
पूर्ण

अटल स्थिर काष्ठा scmi_clk_proto_ops clk_proto_ops = अणु
	.count_get = scmi_घड़ी_count_get,
	.info_get = scmi_घड़ी_info_get,
	.rate_get = scmi_घड़ी_rate_get,
	.rate_set = scmi_घड़ी_rate_set,
	.enable = scmi_घड़ी_enable,
	.disable = scmi_घड़ी_disable,
पूर्ण;

अटल पूर्णांक scmi_घड़ी_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	u32 version;
	पूर्णांक clkid, ret;
	काष्ठा घड़ी_info *cinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "Clock Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	cinfo = devm_kzalloc(ph->dev, माप(*cinfo), GFP_KERNEL);
	अगर (!cinfo)
		वापस -ENOMEM;

	scmi_घड़ी_protocol_attributes_get(ph, cinfo);

	cinfo->clk = devm_kसुस्मृति(ph->dev, cinfo->num_घड़ीs,
				  माप(*cinfo->clk), GFP_KERNEL);
	अगर (!cinfo->clk)
		वापस -ENOMEM;

	क्रम (clkid = 0; clkid < cinfo->num_घड़ीs; clkid++) अणु
		काष्ठा scmi_घड़ी_info *clk = cinfo->clk + clkid;

		ret = scmi_घड़ी_attributes_get(ph, clkid, clk);
		अगर (!ret)
			scmi_घड़ी_describe_rates_get(ph, clkid, clk);
	पूर्ण

	cinfo->version = version;
	वापस ph->set_priv(ph, cinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_घड़ी = अणु
	.id = SCMI_PROTOCOL_CLOCK,
	.owner = THIS_MODULE,
	.instance_init = &scmi_घड़ी_protocol_init,
	.ops = &clk_proto_ops,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(घड़ी, scmi_घड़ी)
