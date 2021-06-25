<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <dt-bindings/memory/tegra20-mc.h>

#समावेश "mc.h"

#घोषणा MC_STAT_CONTROL				0x90
#घोषणा MC_STAT_EMC_CLOCK_LIMIT			0xa0
#घोषणा MC_STAT_EMC_CLOCKS			0xa4
#घोषणा MC_STAT_EMC_CONTROL_0			0xa8
#घोषणा MC_STAT_EMC_CONTROL_1			0xac
#घोषणा MC_STAT_EMC_COUNT_0			0xb8
#घोषणा MC_STAT_EMC_COUNT_1			0xbc

#घोषणा MC_STAT_CONTROL_CLIENT_ID		GENMASK(13,  8)
#घोषणा MC_STAT_CONTROL_EVENT			GENMASK(23, 16)
#घोषणा MC_STAT_CONTROL_PRI_EVENT		GENMASK(25, 24)
#घोषणा MC_STAT_CONTROL_FILTER_CLIENT_ENABLE	GENMASK(26, 26)
#घोषणा MC_STAT_CONTROL_FILTER_PRI		GENMASK(29, 28)

#घोषणा MC_STAT_CONTROL_PRI_EVENT_HP		0
#घोषणा MC_STAT_CONTROL_PRI_EVENT_TM		1
#घोषणा MC_STAT_CONTROL_PRI_EVENT_BW		2

#घोषणा MC_STAT_CONTROL_FILTER_PRI_DISABLE	0
#घोषणा MC_STAT_CONTROL_FILTER_PRI_NO		1
#घोषणा MC_STAT_CONTROL_FILTER_PRI_YES		2

#घोषणा MC_STAT_CONTROL_EVENT_QUALIFIED		0
#घोषणा MC_STAT_CONTROL_EVENT_ANY_READ		1
#घोषणा MC_STAT_CONTROL_EVENT_ANY_WRITE		2
#घोषणा MC_STAT_CONTROL_EVENT_RD_WR_CHANGE	3
#घोषणा MC_STAT_CONTROL_EVENT_SUCCESSIVE	4
#घोषणा MC_STAT_CONTROL_EVENT_ARB_BANK_AA	5
#घोषणा MC_STAT_CONTROL_EVENT_ARB_BANK_BB	6
#घोषणा MC_STAT_CONTROL_EVENT_PAGE_MISS		7
#घोषणा MC_STAT_CONTROL_EVENT_AUTO_PRECHARGE	8

#घोषणा EMC_GATHER_RST				(0 << 8)
#घोषणा EMC_GATHER_CLEAR			(1 << 8)
#घोषणा EMC_GATHER_DISABLE			(2 << 8)
#घोषणा EMC_GATHER_ENABLE			(3 << 8)

#घोषणा MC_STAT_SAMPLE_TIME_USEC		16000

/* we store collected statistics as a fixed poपूर्णांक values */
#घोषणा MC_FX_FRAC_SCALE			100

अटल DEFINE_MUTEX(tegra20_mc_stat_lock);

काष्ठा tegra20_mc_stat_gather अणु
	अचिन्हित पूर्णांक pri_filter;
	अचिन्हित पूर्णांक pri_event;
	अचिन्हित पूर्णांक result;
	अचिन्हित पूर्णांक client;
	अचिन्हित पूर्णांक event;
	bool client_enb;
पूर्ण;

काष्ठा tegra20_mc_stat अणु
	काष्ठा tegra20_mc_stat_gather gather0;
	काष्ठा tegra20_mc_stat_gather gather1;
	अचिन्हित पूर्णांक sample_समय_usec;
	स्थिर काष्ठा tegra_mc *mc;
पूर्ण;

काष्ठा tegra20_mc_client_stat अणु
	अचिन्हित पूर्णांक events;
	अचिन्हित पूर्णांक arb_high_prio;
	अचिन्हित पूर्णांक arb_समयout;
	अचिन्हित पूर्णांक arb_bandwidth;
	अचिन्हित पूर्णांक rd_wr_change;
	अचिन्हित पूर्णांक successive;
	अचिन्हित पूर्णांक page_miss;
	अचिन्हित पूर्णांक स्वतः_preअक्षरge;
	अचिन्हित पूर्णांक arb_bank_aa;
	अचिन्हित पूर्णांक arb_bank_bb;
पूर्ण;

अटल स्थिर काष्ठा tegra_mc_client tegra20_mc_clients[] = अणु
	अणु
		.id = 0x00,
		.name = "display0a",
	पूर्ण, अणु
		.id = 0x01,
		.name = "display0ab",
	पूर्ण, अणु
		.id = 0x02,
		.name = "display0b",
	पूर्ण, अणु
		.id = 0x03,
		.name = "display0bb",
	पूर्ण, अणु
		.id = 0x04,
		.name = "display0c",
	पूर्ण, अणु
		.id = 0x05,
		.name = "display0cb",
	पूर्ण, अणु
		.id = 0x06,
		.name = "display1b",
	पूर्ण, अणु
		.id = 0x07,
		.name = "display1bb",
	पूर्ण, अणु
		.id = 0x08,
		.name = "eppup",
	पूर्ण, अणु
		.id = 0x09,
		.name = "g2pr",
	पूर्ण, अणु
		.id = 0x0a,
		.name = "g2sr",
	पूर्ण, अणु
		.id = 0x0b,
		.name = "mpeunifbr",
	पूर्ण, अणु
		.id = 0x0c,
		.name = "viruv",
	पूर्ण, अणु
		.id = 0x0d,
		.name = "avpcarm7r",
	पूर्ण, अणु
		.id = 0x0e,
		.name = "displayhc",
	पूर्ण, अणु
		.id = 0x0f,
		.name = "displayhcb",
	पूर्ण, अणु
		.id = 0x10,
		.name = "fdcdrd",
	पूर्ण, अणु
		.id = 0x11,
		.name = "g2dr",
	पूर्ण, अणु
		.id = 0x12,
		.name = "host1xdmar",
	पूर्ण, अणु
		.id = 0x13,
		.name = "host1xr",
	पूर्ण, अणु
		.id = 0x14,
		.name = "idxsrd",
	पूर्ण, अणु
		.id = 0x15,
		.name = "mpcorer",
	पूर्ण, अणु
		.id = 0x16,
		.name = "mpe_ipred",
	पूर्ण, अणु
		.id = 0x17,
		.name = "mpeamemrd",
	पूर्ण, अणु
		.id = 0x18,
		.name = "mpecsrd",
	पूर्ण, अणु
		.id = 0x19,
		.name = "ppcsahbdmar",
	पूर्ण, अणु
		.id = 0x1a,
		.name = "ppcsahbslvr",
	पूर्ण, अणु
		.id = 0x1b,
		.name = "texsrd",
	पूर्ण, अणु
		.id = 0x1c,
		.name = "vdebsevr",
	पूर्ण, अणु
		.id = 0x1d,
		.name = "vdember",
	पूर्ण, अणु
		.id = 0x1e,
		.name = "vdemcer",
	पूर्ण, अणु
		.id = 0x1f,
		.name = "vdetper",
	पूर्ण, अणु
		.id = 0x20,
		.name = "eppu",
	पूर्ण, अणु
		.id = 0x21,
		.name = "eppv",
	पूर्ण, अणु
		.id = 0x22,
		.name = "eppy",
	पूर्ण, अणु
		.id = 0x23,
		.name = "mpeunifbw",
	पूर्ण, अणु
		.id = 0x24,
		.name = "viwsb",
	पूर्ण, अणु
		.id = 0x25,
		.name = "viwu",
	पूर्ण, अणु
		.id = 0x26,
		.name = "viwv",
	पूर्ण, अणु
		.id = 0x27,
		.name = "viwy",
	पूर्ण, अणु
		.id = 0x28,
		.name = "g2dw",
	पूर्ण, अणु
		.id = 0x29,
		.name = "avpcarm7w",
	पूर्ण, अणु
		.id = 0x2a,
		.name = "fdcdwr",
	पूर्ण, अणु
		.id = 0x2b,
		.name = "host1xw",
	पूर्ण, अणु
		.id = 0x2c,
		.name = "ispw",
	पूर्ण, अणु
		.id = 0x2d,
		.name = "mpcorew",
	पूर्ण, अणु
		.id = 0x2e,
		.name = "mpecswr",
	पूर्ण, अणु
		.id = 0x2f,
		.name = "ppcsahbdmaw",
	पूर्ण, अणु
		.id = 0x30,
		.name = "ppcsahbslvw",
	पूर्ण, अणु
		.id = 0x31,
		.name = "vdebsevw",
	पूर्ण, अणु
		.id = 0x32,
		.name = "vdembew",
	पूर्ण, अणु
		.id = 0x33,
		.name = "vdetpmw",
	पूर्ण,
पूर्ण;

#घोषणा TEGRA20_MC_RESET(_name, _control, _status, _reset, _bit)	\
	अणु								\
		.name = #_name,						\
		.id = TEGRA20_MC_RESET_##_name,				\
		.control = _control,					\
		.status = _status,					\
		.reset = _reset,					\
		.bit = _bit,						\
	पूर्ण

अटल स्थिर काष्ठा tegra_mc_reset tegra20_mc_resets[] = अणु
	TEGRA20_MC_RESET(AVPC,   0x100, 0x140, 0x104,  0),
	TEGRA20_MC_RESET(DC,     0x100, 0x144, 0x104,  1),
	TEGRA20_MC_RESET(DCB,    0x100, 0x148, 0x104,  2),
	TEGRA20_MC_RESET(EPP,    0x100, 0x14c, 0x104,  3),
	TEGRA20_MC_RESET(2D,     0x100, 0x150, 0x104,  4),
	TEGRA20_MC_RESET(HC,     0x100, 0x154, 0x104,  5),
	TEGRA20_MC_RESET(ISP,    0x100, 0x158, 0x104,  6),
	TEGRA20_MC_RESET(MPCORE, 0x100, 0x15c, 0x104,  7),
	TEGRA20_MC_RESET(MPEA,   0x100, 0x160, 0x104,  8),
	TEGRA20_MC_RESET(MPEB,   0x100, 0x164, 0x104,  9),
	TEGRA20_MC_RESET(MPEC,   0x100, 0x168, 0x104, 10),
	TEGRA20_MC_RESET(3D,     0x100, 0x16c, 0x104, 11),
	TEGRA20_MC_RESET(PPCS,   0x100, 0x170, 0x104, 12),
	TEGRA20_MC_RESET(VDE,    0x100, 0x174, 0x104, 13),
	TEGRA20_MC_RESET(VI,     0x100, 0x178, 0x104, 14),
पूर्ण;

अटल पूर्णांक tegra20_mc_hotreset_निश्चित(काष्ठा tegra_mc *mc,
				      स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->reset);
	mc_ग_लिखोl(mc, value & ~BIT(rst->bit), rst->reset);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_mc_hotreset_deनिश्चित(काष्ठा tegra_mc *mc,
					स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->reset);
	mc_ग_लिखोl(mc, value | BIT(rst->bit), rst->reset);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_mc_block_dma(काष्ठा tegra_mc *mc,
				स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->control) & ~BIT(rst->bit);
	mc_ग_लिखोl(mc, value, rst->control);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल bool tegra20_mc_dma_idling(काष्ठा tegra_mc *mc,
				  स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	वापस mc_पढ़ोl(mc, rst->status) == 0;
पूर्ण

अटल पूर्णांक tegra20_mc_reset_status(काष्ठा tegra_mc *mc,
				   स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	वापस (mc_पढ़ोl(mc, rst->reset) & BIT(rst->bit)) == 0;
पूर्ण

अटल पूर्णांक tegra20_mc_unblock_dma(काष्ठा tegra_mc *mc,
				  स्थिर काष्ठा tegra_mc_reset *rst)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&mc->lock, flags);

	value = mc_पढ़ोl(mc, rst->control) | BIT(rst->bit);
	mc_ग_लिखोl(mc, value, rst->control);

	spin_unlock_irqrestore(&mc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_mc_reset_ops tegra20_mc_reset_ops = अणु
	.hotreset_निश्चित = tegra20_mc_hotreset_निश्चित,
	.hotreset_deनिश्चित = tegra20_mc_hotreset_deनिश्चित,
	.block_dma = tegra20_mc_block_dma,
	.dma_idling = tegra20_mc_dma_idling,
	.unblock_dma = tegra20_mc_unblock_dma,
	.reset_status = tegra20_mc_reset_status,
पूर्ण;

अटल पूर्णांक tegra20_mc_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	/*
	 * It should be possible to tune arbitration knobs here, but the
	 * शेष values are known to work well on all devices. Hence
	 * nothing to करो here so far.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_mc_icc_aggreate(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
				   u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
अणु
	/*
	 * ISO clients need to reserve extra bandwidth up-front because
	 * there could be high bandwidth pressure during initial filling
	 * of the client's FIFO buffers.  Secondly, we need to take पूर्णांकo
	 * account impurities of the memory subप्रणाली.
	 */
	अगर (tag & TEGRA_MC_ICC_TAG_ISO)
		peak_bw = tegra_mc_scale_percents(peak_bw, 300);

	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	वापस 0;
पूर्ण

अटल काष्ठा icc_node_data *
tegra20_mc_of_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा tegra_mc *mc = icc_provider_to_tegra_mc(data);
	अचिन्हित पूर्णांक i, idx = spec->args[0];
	काष्ठा icc_node_data *ndata;
	काष्ठा icc_node *node;

	list_क्रम_each_entry(node, &mc->provider.nodes, node_list) अणु
		अगर (node->id != idx)
			जारी;

		ndata = kzalloc(माप(*ndata), GFP_KERNEL);
		अगर (!ndata)
			वापस ERR_PTR(-ENOMEM);

		ndata->node = node;

		/* these clients are isochronous by शेष */
		अगर (strstarts(node->name, "display") ||
		    strstarts(node->name, "vi"))
			ndata->tag = TEGRA_MC_ICC_TAG_ISO;
		अन्यथा
			ndata->tag = TEGRA_MC_ICC_TAG_DEFAULT;

		वापस ndata;
	पूर्ण

	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		अगर (mc->soc->clients[i].id == idx)
			वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	dev_err(mc->dev, "invalid ICC client ID %u\n", idx);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा tegra_mc_icc_ops tegra20_mc_icc_ops = अणु
	.xlate_extended = tegra20_mc_of_icc_xlate_extended,
	.aggregate = tegra20_mc_icc_aggreate,
	.set = tegra20_mc_icc_set,
पूर्ण;

अटल u32 tegra20_mc_stat_gather_control(स्थिर काष्ठा tegra20_mc_stat_gather *g)
अणु
	u32 control;

	control  = FIELD_PREP(MC_STAT_CONTROL_EVENT, g->event);
	control |= FIELD_PREP(MC_STAT_CONTROL_CLIENT_ID, g->client);
	control |= FIELD_PREP(MC_STAT_CONTROL_PRI_EVENT, g->pri_event);
	control |= FIELD_PREP(MC_STAT_CONTROL_FILTER_PRI, g->pri_filter);
	control |= FIELD_PREP(MC_STAT_CONTROL_FILTER_CLIENT_ENABLE, g->client_enb);

	वापस control;
पूर्ण

अटल व्योम tegra20_mc_stat_gather(काष्ठा tegra20_mc_stat *stat)
अणु
	u32 घड़ीs, count0, count1, control_0, control_1;
	स्थिर काष्ठा tegra_mc *mc = stat->mc;

	control_0 = tegra20_mc_stat_gather_control(&stat->gather0);
	control_1 = tegra20_mc_stat_gather_control(&stat->gather1);

	/*
	 * Reset statistic gathers state, select statistics collection mode
	 * and set घड़ीs counter saturation limit to maximum.
	 */
	mc_ग_लिखोl(mc, 0x00000000, MC_STAT_CONTROL);
	mc_ग_लिखोl(mc,  control_0, MC_STAT_EMC_CONTROL_0);
	mc_ग_लिखोl(mc,  control_1, MC_STAT_EMC_CONTROL_1);
	mc_ग_लिखोl(mc, 0xffffffff, MC_STAT_EMC_CLOCK_LIMIT);

	mc_ग_लिखोl(mc, EMC_GATHER_ENABLE, MC_STAT_CONTROL);
	fsleep(stat->sample_समय_usec);
	mc_ग_लिखोl(mc, EMC_GATHER_DISABLE, MC_STAT_CONTROL);

	count0 = mc_पढ़ोl(mc, MC_STAT_EMC_COUNT_0);
	count1 = mc_पढ़ोl(mc, MC_STAT_EMC_COUNT_1);
	घड़ीs = mc_पढ़ोl(mc, MC_STAT_EMC_CLOCKS);
	घड़ीs = max(घड़ीs / 100 / MC_FX_FRAC_SCALE, 1u);

	stat->gather0.result = DIV_ROUND_UP(count0, घड़ीs);
	stat->gather1.result = DIV_ROUND_UP(count1, घड़ीs);
पूर्ण

अटल व्योम tegra20_mc_stat_events(स्थिर काष्ठा tegra_mc *mc,
				   स्थिर काष्ठा tegra_mc_client *client0,
				   स्थिर काष्ठा tegra_mc_client *client1,
				   अचिन्हित पूर्णांक pri_filter,
				   अचिन्हित पूर्णांक pri_event,
				   अचिन्हित पूर्णांक event,
				   अचिन्हित पूर्णांक *result0,
				   अचिन्हित पूर्णांक *result1)
अणु
	काष्ठा tegra20_mc_stat stat = अणुपूर्ण;

	stat.gather0.client = client0 ? client0->id : 0;
	stat.gather0.pri_filter = pri_filter;
	stat.gather0.client_enb = !!client0;
	stat.gather0.pri_event = pri_event;
	stat.gather0.event = event;

	stat.gather1.client = client1 ? client1->id : 0;
	stat.gather1.pri_filter = pri_filter;
	stat.gather1.client_enb = !!client1;
	stat.gather1.pri_event = pri_event;
	stat.gather1.event = event;

	stat.sample_समय_usec = MC_STAT_SAMPLE_TIME_USEC;
	stat.mc = mc;

	tegra20_mc_stat_gather(&stat);

	*result0 = stat.gather0.result;
	*result1 = stat.gather1.result;
पूर्ण

अटल व्योम tegra20_mc_collect_stats(स्थिर काष्ठा tegra_mc *mc,
				     काष्ठा tegra20_mc_client_stat *stats)
अणु
	स्थिर काष्ठा tegra_mc_client *client0, *client1;
	अचिन्हित पूर्णांक i;

	/* collect memory controller utilization percent क्रम each client */
	क्रम (i = 0; i < mc->soc->num_clients; i += 2) अणु
		client0 = &mc->soc->clients[i];
		client1 = &mc->soc->clients[i + 1];

		अगर (i + 1 == mc->soc->num_clients)
			client1 = शून्य;

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_DISABLE,
				       MC_STAT_CONTROL_PRI_EVENT_HP,
				       MC_STAT_CONTROL_EVENT_QUALIFIED,
				       &stats[i + 0].events,
				       &stats[i + 1].events);
	पूर्ण

	/* collect more info from active clients */
	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		अचिन्हित पूर्णांक clienta, clientb = mc->soc->num_clients;

		क्रम (client0 = शून्य; i < mc->soc->num_clients; i++) अणु
			अगर (stats[i].events) अणु
				client0 = &mc->soc->clients[i];
				clienta = i++;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (client1 = शून्य; i < mc->soc->num_clients; i++) अणु
			अगर (stats[i].events) अणु
				client1 = &mc->soc->clients[i];
				clientb = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!client0 && !client1)
			अवरोध;

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_YES,
				       MC_STAT_CONTROL_PRI_EVENT_HP,
				       MC_STAT_CONTROL_EVENT_QUALIFIED,
				       &stats[clienta].arb_high_prio,
				       &stats[clientb].arb_high_prio);

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_YES,
				       MC_STAT_CONTROL_PRI_EVENT_TM,
				       MC_STAT_CONTROL_EVENT_QUALIFIED,
				       &stats[clienta].arb_समयout,
				       &stats[clientb].arb_समयout);

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_YES,
				       MC_STAT_CONTROL_PRI_EVENT_BW,
				       MC_STAT_CONTROL_EVENT_QUALIFIED,
				       &stats[clienta].arb_bandwidth,
				       &stats[clientb].arb_bandwidth);

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_DISABLE,
				       MC_STAT_CONTROL_PRI_EVENT_HP,
				       MC_STAT_CONTROL_EVENT_RD_WR_CHANGE,
				       &stats[clienta].rd_wr_change,
				       &stats[clientb].rd_wr_change);

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_DISABLE,
				       MC_STAT_CONTROL_PRI_EVENT_HP,
				       MC_STAT_CONTROL_EVENT_SUCCESSIVE,
				       &stats[clienta].successive,
				       &stats[clientb].successive);

		tegra20_mc_stat_events(mc, client0, client1,
				       MC_STAT_CONTROL_FILTER_PRI_DISABLE,
				       MC_STAT_CONTROL_PRI_EVENT_HP,
				       MC_STAT_CONTROL_EVENT_PAGE_MISS,
				       &stats[clienta].page_miss,
				       &stats[clientb].page_miss);
	पूर्ण
पूर्ण

अटल व्योम tegra20_mc_म_लिखो_percents(काष्ठा seq_file *s,
				       स्थिर अक्षर *fmt,
				       अचिन्हित पूर्णांक percents_fx)
अणु
	अक्षर percents_str[8];

	snम_लिखो(percents_str, ARRAY_SIZE(percents_str), "%3u.%02u%%",
		 percents_fx / MC_FX_FRAC_SCALE, percents_fx % MC_FX_FRAC_SCALE);

	seq_म_लिखो(s, fmt, percents_str);
पूर्ण

अटल पूर्णांक tegra20_mc_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	स्थिर काष्ठा tegra_mc *mc = dev_get_drvdata(s->निजी);
	काष्ठा tegra20_mc_client_stat *stats;
	अचिन्हित पूर्णांक i;

	stats = kसुस्मृति(mc->soc->num_clients + 1, माप(*stats), GFP_KERNEL);
	अगर (!stats)
		वापस -ENOMEM;

	mutex_lock(&tegra20_mc_stat_lock);

	tegra20_mc_collect_stats(mc, stats);

	mutex_unlock(&tegra20_mc_stat_lock);

	seq_माला_दो(s, "Memory client   Events   Timeout   High priority   Bandwidth ARB   RW change   Successive   Page miss\n");
	seq_माला_दो(s, "-----------------------------------------------------------------------------------------------------\n");

	क्रम (i = 0; i < mc->soc->num_clients; i++) अणु
		seq_म_लिखो(s, "%-14s  ", mc->soc->clients[i].name);

		/* An event is generated when client perक्रमms R/W request. */
		tegra20_mc_म_लिखो_percents(s,  "%-9s", stats[i].events);

		/*
		 * An event is generated based on the समयout (TM) संकेत
		 * accompanying a request क्रम arbitration.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-10s", stats[i].arb_समयout);

		/*
		 * An event is generated based on the high-priority (HP) संकेत
		 * accompanying a request क्रम arbitration.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-16s", stats[i].arb_high_prio);

		/*
		 * An event is generated based on the bandwidth (BW) संकेत
		 * accompanying a request क्रम arbitration.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-16s", stats[i].arb_bandwidth);

		/*
		 * An event is generated when the memory controller चयनes
		 * between making a पढ़ो request to making a ग_लिखो request.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-12s", stats[i].rd_wr_change);

		/*
		 * An even generated when the chosen client has wins arbitration
		 * when it was also the winner at the previous request.  If a
		 * client makes N requests in a row that are honored, SUCCESSIVE
		 * will be counted (N-1) बार.  Large values क्रम this event
		 * imply that अगर we were patient enough, all of those requests
		 * could have been coalesced.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-13s", stats[i].successive);

		/*
		 * An event is generated when the memory controller detects a
		 * page miss क्रम the current request.
		 */
		tegra20_mc_म_लिखो_percents(s, "%-12s\n", stats[i].page_miss);
	पूर्ण

	kमुक्त(stats);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_mc_init(काष्ठा tegra_mc *mc)
अणु
	debugfs_create_devm_seqfile(mc->dev, "stats", mc->debugfs.root,
				    tegra20_mc_stats_show);

	वापस 0;
पूर्ण

स्थिर काष्ठा tegra_mc_soc tegra20_mc_soc = अणु
	.clients = tegra20_mc_clients,
	.num_clients = ARRAY_SIZE(tegra20_mc_clients),
	.num_address_bits = 32,
	.client_id_mask = 0x3f,
	.पूर्णांकmask = MC_INT_SECURITY_VIOLATION | MC_INT_INVALID_GART_PAGE |
		   MC_INT_DECERR_EMEM,
	.reset_ops = &tegra20_mc_reset_ops,
	.resets = tegra20_mc_resets,
	.num_resets = ARRAY_SIZE(tegra20_mc_resets),
	.icc_ops = &tegra20_mc_icc_ops,
	.init = tegra20_mc_init,
पूर्ण;
