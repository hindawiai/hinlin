<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 NVIDIA Corporation
 */

#समावेश <linux/reset-controller.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

अटल काष्ठा tegra_bpmp *to_tegra_bpmp(काष्ठा reset_controller_dev *rstc)
अणु
	वापस container_of(rstc, काष्ठा tegra_bpmp, rstc);
पूर्ण

अटल पूर्णांक tegra_bpmp_reset_common(काष्ठा reset_controller_dev *rstc,
				   क्रमागत mrq_reset_commands command,
				   अचिन्हित पूर्णांक id)
अणु
	काष्ठा tegra_bpmp *bpmp = to_tegra_bpmp(rstc);
	काष्ठा mrq_reset_request request;
	काष्ठा tegra_bpmp_message msg;

	स_रखो(&request, 0, माप(request));
	request.cmd = command;
	request.reset_id = id;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_RESET;
	msg.tx.data = &request;
	msg.tx.size = माप(request);

	वापस tegra_bpmp_transfer(bpmp, &msg);
पूर्ण

अटल पूर्णांक tegra_bpmp_reset_module(काष्ठा reset_controller_dev *rstc,
				   अचिन्हित दीर्घ id)
अणु
	वापस tegra_bpmp_reset_common(rstc, CMD_RESET_MODULE, id);
पूर्ण

अटल पूर्णांक tegra_bpmp_reset_निश्चित(काष्ठा reset_controller_dev *rstc,
				   अचिन्हित दीर्घ id)
अणु
	वापस tegra_bpmp_reset_common(rstc, CMD_RESET_ASSERT, id);
पूर्ण

अटल पूर्णांक tegra_bpmp_reset_deनिश्चित(काष्ठा reset_controller_dev *rstc,
				     अचिन्हित दीर्घ id)
अणु
	वापस tegra_bpmp_reset_common(rstc, CMD_RESET_DEASSERT, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops tegra_bpmp_reset_ops = अणु
	.reset = tegra_bpmp_reset_module,
	.निश्चित = tegra_bpmp_reset_निश्चित,
	.deनिश्चित = tegra_bpmp_reset_deनिश्चित,
पूर्ण;

पूर्णांक tegra_bpmp_init_resets(काष्ठा tegra_bpmp *bpmp)
अणु
	bpmp->rstc.ops = &tegra_bpmp_reset_ops;
	bpmp->rstc.owner = THIS_MODULE;
	bpmp->rstc.of_node = bpmp->dev->of_node;
	bpmp->rstc.nr_resets = bpmp->soc->num_resets;

	वापस devm_reset_controller_रेजिस्टर(bpmp->dev, &bpmp->rstc);
पूर्ण
