<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016-2020 NVIDIA Corporation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/seq_buf.h>
#समावेश <linux/slab.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

#घोषणा TEGRA_BPMP_DUMP_CLOCK_INFO	0

#घोषणा TEGRA_BPMP_CLK_HAS_MUX		BIT(0)
#घोषणा TEGRA_BPMP_CLK_HAS_SET_RATE	BIT(1)
#घोषणा TEGRA_BPMP_CLK_IS_ROOT		BIT(2)

काष्ठा tegra_bpmp_clk_info अणु
	अचिन्हित पूर्णांक id;
	अक्षर name[MRQ_CLK_NAME_MAXLEN];
	अचिन्हित पूर्णांक parents[MRQ_CLK_MAX_PARENTS];
	अचिन्हित पूर्णांक num_parents;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा tegra_bpmp_clk अणु
	काष्ठा clk_hw hw;

	काष्ठा tegra_bpmp *bpmp;
	अचिन्हित पूर्णांक id;

	अचिन्हित पूर्णांक num_parents;
	अचिन्हित पूर्णांक *parents;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_bpmp_clk *to_tegra_bpmp_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा tegra_bpmp_clk, hw);
पूर्ण

काष्ठा tegra_bpmp_clk_message अणु
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक id;

	काष्ठा अणु
		स्थिर व्योम *data;
		माप_प्रकार size;
	पूर्ण tx;

	काष्ठा अणु
		व्योम *data;
		माप_प्रकार size;
		पूर्णांक ret;
	पूर्ण rx;
पूर्ण;

अटल पूर्णांक tegra_bpmp_clk_transfer(काष्ठा tegra_bpmp *bpmp,
				   स्थिर काष्ठा tegra_bpmp_clk_message *clk)
अणु
	काष्ठा mrq_clk_request request;
	काष्ठा tegra_bpmp_message msg;
	व्योम *req = &request;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.cmd_and_id = (clk->cmd << 24) | clk->id;

	/*
	 * The mrq_clk_request काष्ठाure has an anonymous जोड़ at offset 4
	 * that contains all possible sub-command काष्ठाures. Copy the data
	 * to that जोड़. Ideally we'd be able to refer to it by name, but
	 * करोing so would require changing the ABI header and increase the
	 * मुख्यtenance burden.
	 */
	स_नकल(req + 4, clk->tx.data, clk->tx.size);

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_CLK;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = clk->rx.data;
	msg.rx.size = clk->rx.size;

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा tegra_bpmp_clk_message msg;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_ENABLE;
	msg.id = clk->id;

	वापस tegra_bpmp_clk_transfer(clk->bpmp, &msg);
पूर्ण

अटल व्योम tegra_bpmp_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_DISABLE;
	msg.id = clk->id;

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0)
		dev_err(clk->bpmp->dev, "failed to disable clock %s: %d\n",
			clk_hw_get_name(hw), err);
पूर्ण

अटल पूर्णांक tegra_bpmp_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_is_enabled_response response;
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_IS_ENABLED;
	msg.id = clk->id;
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0)
		वापस err;

	वापस response.state;
पूर्ण

अटल अचिन्हित दीर्घ tegra_bpmp_clk_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_get_rate_response response;
	काष्ठा cmd_clk_get_rate_request request;
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_GET_RATE;
	msg.id = clk->id;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0)
		वापस err;

	वापस response.rate;
पूर्ण

अटल दीर्घ tegra_bpmp_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_round_rate_response response;
	काष्ठा cmd_clk_round_rate_request request;
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.rate = min_t(u64, rate, S64_MAX);

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_ROUND_RATE;
	msg.id = clk->id;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0)
		वापस err;

	वापस response.rate;
पूर्ण

अटल पूर्णांक tegra_bpmp_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_set_parent_response response;
	काष्ठा cmd_clk_set_parent_request request;
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.parent_id = clk->parents[index];

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_SET_PARENT;
	msg.id = clk->id;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0)
		वापस err;

	/* XXX check parent ID in response */

	वापस 0;
पूर्ण

अटल u8 tegra_bpmp_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_get_parent_response response;
	काष्ठा tegra_bpmp_clk_message msg;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_GET_PARENT;
	msg.id = clk->id;
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(clk->bpmp, &msg);
	अगर (err < 0) अणु
		dev_err(clk->bpmp->dev, "failed to get parent for %s: %d\n",
			clk_hw_get_name(hw), err);
		वापस U8_MAX;
	पूर्ण

	क्रम (i = 0; i < clk->num_parents; i++)
		अगर (clk->parents[i] == response.parent_id)
			वापस i;

	वापस U8_MAX;
पूर्ण

अटल पूर्णांक tegra_bpmp_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_bpmp_clk *clk = to_tegra_bpmp_clk(hw);
	काष्ठा cmd_clk_set_rate_response response;
	काष्ठा cmd_clk_set_rate_request request;
	काष्ठा tegra_bpmp_clk_message msg;

	स_रखो(&request, 0, माप(request));
	request.rate = min_t(u64, rate, S64_MAX);

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_SET_RATE;
	msg.id = clk->id;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	वापस tegra_bpmp_clk_transfer(clk->bpmp, &msg);
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_bpmp_clk_gate_ops = अणु
	.prepare = tegra_bpmp_clk_prepare,
	.unprepare = tegra_bpmp_clk_unprepare,
	.is_prepared = tegra_bpmp_clk_is_prepared,
	.recalc_rate = tegra_bpmp_clk_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_bpmp_clk_mux_ops = अणु
	.prepare = tegra_bpmp_clk_prepare,
	.unprepare = tegra_bpmp_clk_unprepare,
	.is_prepared = tegra_bpmp_clk_is_prepared,
	.recalc_rate = tegra_bpmp_clk_recalc_rate,
	.set_parent = tegra_bpmp_clk_set_parent,
	.get_parent = tegra_bpmp_clk_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_bpmp_clk_rate_ops = अणु
	.prepare = tegra_bpmp_clk_prepare,
	.unprepare = tegra_bpmp_clk_unprepare,
	.is_prepared = tegra_bpmp_clk_is_prepared,
	.recalc_rate = tegra_bpmp_clk_recalc_rate,
	.round_rate = tegra_bpmp_clk_round_rate,
	.set_rate = tegra_bpmp_clk_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_bpmp_clk_mux_rate_ops = अणु
	.prepare = tegra_bpmp_clk_prepare,
	.unprepare = tegra_bpmp_clk_unprepare,
	.is_prepared = tegra_bpmp_clk_is_prepared,
	.recalc_rate = tegra_bpmp_clk_recalc_rate,
	.round_rate = tegra_bpmp_clk_round_rate,
	.set_parent = tegra_bpmp_clk_set_parent,
	.get_parent = tegra_bpmp_clk_get_parent,
	.set_rate = tegra_bpmp_clk_set_rate,
पूर्ण;

अटल पूर्णांक tegra_bpmp_clk_get_max_id(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा cmd_clk_get_max_clk_id_response response;
	काष्ठा tegra_bpmp_clk_message msg;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_GET_MAX_CLK_ID;
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;

	अगर (response.max_id > पूर्णांक_उच्च)
		वापस -E2BIG;

	वापस response.max_id;
पूर्ण

अटल पूर्णांक tegra_bpmp_clk_get_info(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक id,
				   काष्ठा tegra_bpmp_clk_info *info)
अणु
	काष्ठा cmd_clk_get_all_info_response response;
	काष्ठा tegra_bpmp_clk_message msg;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	स_रखो(&msg, 0, माप(msg));
	msg.cmd = CMD_CLK_GET_ALL_INFO;
	msg.id = id;
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_clk_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;

	strlcpy(info->name, response.name, MRQ_CLK_NAME_MAXLEN);
	info->num_parents = response.num_parents;

	क्रम (i = 0; i < info->num_parents; i++)
		info->parents[i] = response.parents[i];

	info->flags = response.flags;

	वापस 0;
पूर्ण

अटल व्योम tegra_bpmp_clk_info_dump(काष्ठा tegra_bpmp *bpmp,
				     स्थिर अक्षर *level,
				     स्थिर काष्ठा tegra_bpmp_clk_info *info)
अणु
	स्थिर अक्षर *prefix = "";
	काष्ठा seq_buf buf;
	अचिन्हित पूर्णांक i;
	अक्षर flags[64];

	seq_buf_init(&buf, flags, माप(flags));

	अगर (info->flags)
		seq_buf_म_लिखो(&buf, "(");

	अगर (info->flags & TEGRA_BPMP_CLK_HAS_MUX) अणु
		seq_buf_म_लिखो(&buf, "%smux", prefix);
		prefix = ", ";
	पूर्ण

	अगर ((info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE) == 0) अणु
		seq_buf_म_लिखो(&buf, "%sfixed", prefix);
		prefix = ", ";
	पूर्ण

	अगर (info->flags & TEGRA_BPMP_CLK_IS_ROOT) अणु
		seq_buf_म_लिखो(&buf, "%sroot", prefix);
		prefix = ", ";
	पूर्ण

	अगर (info->flags)
		seq_buf_म_लिखो(&buf, ")");

	dev_prपूर्णांकk(level, bpmp->dev, "%03u: %s\n", info->id, info->name);
	dev_prपूर्णांकk(level, bpmp->dev, "  flags: %lx %s\n", info->flags, flags);
	dev_prपूर्णांकk(level, bpmp->dev, "  parents: %u\n", info->num_parents);

	क्रम (i = 0; i < info->num_parents; i++)
		dev_prपूर्णांकk(level, bpmp->dev, "    %03u\n", info->parents[i]);
पूर्ण

अटल पूर्णांक tegra_bpmp_probe_घड़ीs(काष्ठा tegra_bpmp *bpmp,
				   काष्ठा tegra_bpmp_clk_info **घड़ीsp)
अणु
	काष्ठा tegra_bpmp_clk_info *घड़ीs;
	अचिन्हित पूर्णांक max_id, id, count = 0;
	अचिन्हित पूर्णांक holes = 0;
	पूर्णांक err;

	err = tegra_bpmp_clk_get_max_id(bpmp);
	अगर (err < 0)
		वापस err;

	max_id = err;

	dev_dbg(bpmp->dev, "maximum clock ID: %u\n", max_id);

	घड़ीs = kसुस्मृति(max_id + 1, माप(*घड़ीs), GFP_KERNEL);
	अगर (!घड़ीs)
		वापस -ENOMEM;

	क्रम (id = 0; id <= max_id; id++) अणु
		काष्ठा tegra_bpmp_clk_info *info = &घड़ीs[count];

		err = tegra_bpmp_clk_get_info(bpmp, id, info);
		अगर (err < 0)
			जारी;

		अगर (info->num_parents >= U8_MAX) अणु
			dev_err(bpmp->dev,
				"clock %u has too many parents (%u, max: %u)\n",
				id, info->num_parents, U8_MAX);
			जारी;
		पूर्ण

		/* घड़ी not exposed by BPMP */
		अगर (info->name[0] == '\0') अणु
			holes++;
			जारी;
		पूर्ण

		info->id = id;
		count++;

		अगर (TEGRA_BPMP_DUMP_CLOCK_INFO)
			tegra_bpmp_clk_info_dump(bpmp, KERN_DEBUG, info);
	पूर्ण

	dev_dbg(bpmp->dev, "holes: %u\n", holes);
	*घड़ीsp = घड़ीs;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा tegra_bpmp_clk_info *
tegra_bpmp_clk_find(स्थिर काष्ठा tegra_bpmp_clk_info *घड़ीs,
		    अचिन्हित पूर्णांक num_घड़ीs, अचिन्हित पूर्णांक id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_घड़ीs; i++)
		अगर (घड़ीs[i].id == id)
			वापस &घड़ीs[i];

	वापस शून्य;
पूर्ण

अटल काष्ठा tegra_bpmp_clk *
tegra_bpmp_clk_रेजिस्टर(काष्ठा tegra_bpmp *bpmp,
			स्थिर काष्ठा tegra_bpmp_clk_info *info,
			स्थिर काष्ठा tegra_bpmp_clk_info *घड़ीs,
			अचिन्हित पूर्णांक num_घड़ीs)
अणु
	काष्ठा tegra_bpmp_clk *clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर **parents;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	clk = devm_kzalloc(bpmp->dev, माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->id = info->id;
	clk->bpmp = bpmp;

	clk->parents = devm_kसुस्मृति(bpmp->dev, info->num_parents,
				    माप(*clk->parents), GFP_KERNEL);
	अगर (!clk->parents)
		वापस ERR_PTR(-ENOMEM);

	clk->num_parents = info->num_parents;

	/* hardware घड़ी initialization */
	स_रखो(&init, 0, माप(init));
	init.name = info->name;
	clk->hw.init = &init;

	अगर (info->flags & TEGRA_BPMP_CLK_HAS_MUX) अणु
		अगर (info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE)
			init.ops = &tegra_bpmp_clk_mux_rate_ops;
		अन्यथा
			init.ops = &tegra_bpmp_clk_mux_ops;
	पूर्ण अन्यथा अणु
		अगर (info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE)
			init.ops = &tegra_bpmp_clk_rate_ops;
		अन्यथा
			init.ops = &tegra_bpmp_clk_gate_ops;
	पूर्ण

	init.num_parents = info->num_parents;

	parents = kसुस्मृति(info->num_parents, माप(*parents), GFP_KERNEL);
	अगर (!parents)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < info->num_parents; i++) अणु
		स्थिर काष्ठा tegra_bpmp_clk_info *parent;

		/* keep a निजी copy of the ID to parent index map */
		clk->parents[i] = info->parents[i];

		parent = tegra_bpmp_clk_find(घड़ीs, num_घड़ीs,
					     info->parents[i]);
		अगर (!parent) अणु
			dev_err(bpmp->dev, "no parent %u found for %u\n",
				info->parents[i], info->id);
			जारी;
		पूर्ण

		parents[i] = parent->name;
	पूर्ण

	init.parent_names = parents;

	err = devm_clk_hw_रेजिस्टर(bpmp->dev, &clk->hw);

	kमुक्त(parents);

	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस clk;
पूर्ण

अटल पूर्णांक tegra_bpmp_रेजिस्टर_घड़ीs(काष्ठा tegra_bpmp *bpmp,
				      काष्ठा tegra_bpmp_clk_info *infos,
				      अचिन्हित पूर्णांक count)
अणु
	काष्ठा tegra_bpmp_clk *clk;
	अचिन्हित पूर्णांक i;

	bpmp->num_घड़ीs = count;

	bpmp->घड़ीs = devm_kसुस्मृति(bpmp->dev, count, माप(clk), GFP_KERNEL);
	अगर (!bpmp->घड़ीs)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा tegra_bpmp_clk_info *info = &infos[i];

		clk = tegra_bpmp_clk_रेजिस्टर(bpmp, info, infos, count);
		अगर (IS_ERR(clk)) अणु
			dev_err(bpmp->dev,
				"failed to register clock %u (%s): %ld\n",
				info->id, info->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		bpmp->घड़ीs[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_bpmp_unरेजिस्टर_घड़ीs(काष्ठा tegra_bpmp *bpmp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < bpmp->num_घड़ीs; i++)
		clk_hw_unरेजिस्टर(&bpmp->घड़ीs[i]->hw);
पूर्ण

अटल काष्ठा clk_hw *tegra_bpmp_clk_of_xlate(काष्ठा of_phandle_args *clkspec,
					      व्योम *data)
अणु
	अचिन्हित पूर्णांक id = clkspec->args[0], i;
	काष्ठा tegra_bpmp *bpmp = data;

	क्रम (i = 0; i < bpmp->num_घड़ीs; i++) अणु
		काष्ठा tegra_bpmp_clk *clk = bpmp->घड़ीs[i];

		अगर (!clk)
			जारी;

		अगर (clk->id == id)
			वापस &clk->hw;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक tegra_bpmp_init_घड़ीs(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra_bpmp_clk_info *घड़ीs;
	अचिन्हित पूर्णांक count;
	पूर्णांक err;

	err = tegra_bpmp_probe_घड़ीs(bpmp, &घड़ीs);
	अगर (err < 0)
		वापस err;

	count = err;

	dev_dbg(bpmp->dev, "%u clocks probed\n", count);

	err = tegra_bpmp_रेजिस्टर_घड़ीs(bpmp, घड़ीs, count);
	अगर (err < 0)
		जाओ मुक्त;

	err = of_clk_add_hw_provider(bpmp->dev->of_node,
				     tegra_bpmp_clk_of_xlate,
				     bpmp);
	अगर (err < 0) अणु
		tegra_bpmp_unरेजिस्टर_घड़ीs(bpmp);
		जाओ मुक्त;
	पूर्ण

मुक्त:
	kमुक्त(घड़ीs);
	वापस err;
पूर्ण
