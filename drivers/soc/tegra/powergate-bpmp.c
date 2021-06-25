<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved
 */

#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/version.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

काष्ठा tegra_घातergate_info अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
पूर्ण;

काष्ठा tegra_घातergate अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा tegra_bpmp *bpmp;
	अचिन्हित पूर्णांक id;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_घातergate *
to_tegra_घातergate(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस container_of(genpd, काष्ठा tegra_घातergate, genpd);
पूर्ण

अटल पूर्णांक tegra_bpmp_घातergate_set_state(काष्ठा tegra_bpmp *bpmp,
					  अचिन्हित पूर्णांक id, u32 state)
अणु
	काष्ठा mrq_pg_request request;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.cmd = CMD_PG_SET_STATE;
	request.id = id;
	request.set_state.state = state;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_PG;
	msg.tx.data = &request;
	msg.tx.size = माप(request);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_घातergate_get_state(काष्ठा tegra_bpmp *bpmp,
					  अचिन्हित पूर्णांक id)
अणु
	काष्ठा mrq_pg_response response;
	काष्ठा mrq_pg_request request;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.cmd = CMD_PG_GET_STATE;
	request.id = id;

	स_रखो(&response, 0, माप(response));

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_PG;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस PG_STATE_OFF;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	वापस response.get_state.state;
पूर्ण

अटल पूर्णांक tegra_bpmp_घातergate_get_max_id(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा mrq_pg_response response;
	काष्ठा mrq_pg_request request;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.cmd = CMD_PG_GET_MAX_ID;

	स_रखो(&response, 0, माप(response));

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_PG;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	वापस response.get_max_id.max_id;
पूर्ण

अटल अक्षर *tegra_bpmp_घातergate_get_name(काष्ठा tegra_bpmp *bpmp,
					   अचिन्हित पूर्णांक id)
अणु
	काष्ठा mrq_pg_response response;
	काष्ठा mrq_pg_request request;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.cmd = CMD_PG_GET_NAME;
	request.id = id;

	स_रखो(&response, 0, माप(response));

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_PG;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0 || msg.rx.ret < 0)
		वापस शून्य;

	वापस kstrdup(response.get_name.name, GFP_KERNEL);
पूर्ण

अटल अंतरभूत bool tegra_bpmp_घातergate_is_घातered(काष्ठा tegra_bpmp *bpmp,
						   अचिन्हित पूर्णांक id)
अणु
	वापस tegra_bpmp_घातergate_get_state(bpmp, id) != PG_STATE_OFF;
पूर्ण

अटल पूर्णांक tegra_घातergate_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा tegra_घातergate *घातergate = to_tegra_घातergate(करोमुख्य);
	काष्ठा tegra_bpmp *bpmp = घातergate->bpmp;

	वापस tegra_bpmp_घातergate_set_state(bpmp, घातergate->id,
					      PG_STATE_ON);
पूर्ण

अटल पूर्णांक tegra_घातergate_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा tegra_घातergate *घातergate = to_tegra_घातergate(करोमुख्य);
	काष्ठा tegra_bpmp *bpmp = घातergate->bpmp;

	वापस tegra_bpmp_घातergate_set_state(bpmp, घातergate->id,
					      PG_STATE_OFF);
पूर्ण

अटल काष्ठा tegra_घातergate *
tegra_घातergate_add(काष्ठा tegra_bpmp *bpmp,
		    स्थिर काष्ठा tegra_घातergate_info *info)
अणु
	काष्ठा tegra_घातergate *घातergate;
	bool off;
	पूर्णांक err;

	off = !tegra_bpmp_घातergate_is_घातered(bpmp, info->id);

	घातergate = devm_kzalloc(bpmp->dev, माप(*घातergate), GFP_KERNEL);
	अगर (!घातergate)
		वापस ERR_PTR(-ENOMEM);

	घातergate->id = info->id;
	घातergate->bpmp = bpmp;

	घातergate->genpd.name = kstrdup(info->name, GFP_KERNEL);
	घातergate->genpd.घातer_on = tegra_घातergate_घातer_on;
	घातergate->genpd.घातer_off = tegra_घातergate_घातer_off;

	err = pm_genpd_init(&घातergate->genpd, शून्य, off);
	अगर (err < 0) अणु
		kमुक्त(घातergate->genpd.name);
		वापस ERR_PTR(err);
	पूर्ण

	वापस घातergate;
पूर्ण

अटल व्योम tegra_घातergate_हटाओ(काष्ठा tegra_घातergate *घातergate)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = &घातergate->genpd;
	काष्ठा tegra_bpmp *bpmp = घातergate->bpmp;
	पूर्णांक err;

	err = pm_genpd_हटाओ(genpd);
	अगर (err < 0)
		dev_err(bpmp->dev, "failed to remove power domain %s: %d\n",
			genpd->name, err);

	kमुक्त(genpd->name);
पूर्ण

अटल पूर्णांक
tegra_bpmp_probe_घातergates(काष्ठा tegra_bpmp *bpmp,
			    काष्ठा tegra_घातergate_info **घातergatesp)
अणु
	काष्ठा tegra_घातergate_info *घातergates;
	अचिन्हित पूर्णांक max_id, id, count = 0;
	अचिन्हित पूर्णांक num_holes = 0;
	पूर्णांक err;

	err = tegra_bpmp_घातergate_get_max_id(bpmp);
	अगर (err < 0)
		वापस err;

	max_id = err;

	dev_dbg(bpmp->dev, "maximum powergate ID: %u\n", max_id);

	घातergates = kसुस्मृति(max_id + 1, माप(*घातergates), GFP_KERNEL);
	अगर (!घातergates)
		वापस -ENOMEM;

	क्रम (id = 0; id <= max_id; id++) अणु
		काष्ठा tegra_घातergate_info *info = &घातergates[count];

		info->name = tegra_bpmp_घातergate_get_name(bpmp, id);
		अगर (!info->name || info->name[0] == '\0') अणु
			num_holes++;
			जारी;
		पूर्ण

		info->id = id;
		count++;
	पूर्ण

	dev_dbg(bpmp->dev, "holes: %u\n", num_holes);

	*घातergatesp = घातergates;

	वापस count;
पूर्ण

अटल पूर्णांक tegra_bpmp_add_घातergates(काष्ठा tegra_bpmp *bpmp,
				     काष्ठा tegra_घातergate_info *घातergates,
				     अचिन्हित पूर्णांक count)
अणु
	काष्ठा genpd_onecell_data *genpd = &bpmp->genpd;
	काष्ठा generic_pm_करोमुख्य **करोमुख्यs;
	काष्ठा tegra_घातergate *घातergate;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	करोमुख्यs = kसुस्मृति(count, माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		घातergate = tegra_घातergate_add(bpmp, &घातergates[i]);
		अगर (IS_ERR(घातergate)) अणु
			err = PTR_ERR(घातergate);
			जाओ हटाओ;
		पूर्ण

		dev_dbg(bpmp->dev, "added power domain %s\n",
			घातergate->genpd.name);
		करोमुख्यs[i] = &घातergate->genpd;
	पूर्ण

	genpd->num_करोमुख्यs = count;
	genpd->करोमुख्यs = करोमुख्यs;

	वापस 0;

हटाओ:
	जबतक (i--) अणु
		घातergate = to_tegra_घातergate(करोमुख्यs[i]);
		tegra_घातergate_हटाओ(घातergate);
	पूर्ण

	kमुक्त(genpd->करोमुख्यs);
	वापस err;
पूर्ण

अटल व्योम tegra_bpmp_हटाओ_घातergates(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा genpd_onecell_data *genpd = &bpmp->genpd;
	अचिन्हित पूर्णांक i = genpd->num_करोमुख्यs;
	काष्ठा tegra_घातergate *घातergate;

	जबतक (i--) अणु
		dev_dbg(bpmp->dev, "removing power domain %s\n",
			genpd->करोमुख्यs[i]->name);
		घातergate = to_tegra_घातergate(genpd->करोमुख्यs[i]);
		tegra_घातergate_हटाओ(घातergate);
	पूर्ण
पूर्ण

अटल काष्ठा generic_pm_करोमुख्य *
tegra_घातergate_xlate(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा generic_pm_करोमुख्य *करोमुख्य = ERR_PTR(-ENOENT);
	काष्ठा genpd_onecell_data *genpd = data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < genpd->num_करोमुख्यs; i++) अणु
		काष्ठा tegra_घातergate *घातergate;

		घातergate = to_tegra_घातergate(genpd->करोमुख्यs[i]);
		अगर (घातergate->id == spec->args[0]) अणु
			करोमुख्य = &घातergate->genpd;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस करोमुख्य;
पूर्ण

पूर्णांक tegra_bpmp_init_घातergates(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा device_node *np = bpmp->dev->of_node;
	काष्ठा tegra_घातergate_info *घातergates;
	काष्ठा device *dev = bpmp->dev;
	अचिन्हित पूर्णांक count, i;
	पूर्णांक err;

	err = tegra_bpmp_probe_घातergates(bpmp, &घातergates);
	अगर (err < 0)
		वापस err;

	count = err;

	dev_dbg(dev, "%u power domains probed\n", count);

	err = tegra_bpmp_add_घातergates(bpmp, घातergates, count);
	अगर (err < 0)
		जाओ मुक्त;

	bpmp->genpd.xlate = tegra_घातergate_xlate;

	err = of_genpd_add_provider_onecell(np, &bpmp->genpd);
	अगर (err < 0) अणु
		dev_err(dev, "failed to add power domain provider: %d\n", err);
		tegra_bpmp_हटाओ_घातergates(bpmp);
	पूर्ण

मुक्त:
	क्रम (i = 0; i < count; i++)
		kमुक्त(घातergates[i].name);

	kमुक्त(घातergates);
	वापस err;
पूर्ण
