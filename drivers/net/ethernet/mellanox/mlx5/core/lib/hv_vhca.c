<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2018 Mellanox Technologies

#समावेश <linux/hyperv.h>
#समावेश "mlx5_core.h"
#समावेश "lib/hv.h"
#समावेश "lib/hv_vhca.h"

काष्ठा mlx5_hv_vhca अणु
	काष्ठा mlx5_core_dev       *dev;
	काष्ठा workqueue_काष्ठा    *work_queue;
	काष्ठा mlx5_hv_vhca_agent  *agents[MLX5_HV_VHCA_AGENT_MAX];
	काष्ठा mutex                agents_lock; /* Protect agents array */
पूर्ण;

काष्ठा mlx5_hv_vhca_work अणु
	काष्ठा work_काष्ठा     invalidate_work;
	काष्ठा mlx5_hv_vhca   *hv_vhca;
	u64                    block_mask;
पूर्ण;

काष्ठा mlx5_hv_vhca_data_block अणु
	u16     sequence;
	u16     offset;
	u8      reserved[4];
	u64     data[15];
पूर्ण;

काष्ठा mlx5_hv_vhca_agent अणु
	क्रमागत mlx5_hv_vhca_agent_type	 type;
	काष्ठा mlx5_hv_vhca		*hv_vhca;
	व्योम				*priv;
	u16                              seq;
	व्योम (*control)(काष्ठा mlx5_hv_vhca_agent *agent,
			काष्ठा mlx5_hv_vhca_control_block *block);
	व्योम (*invalidate)(काष्ठा mlx5_hv_vhca_agent *agent,
			   u64 block_mask);
	व्योम (*cleanup)(काष्ठा mlx5_hv_vhca_agent *agent);
पूर्ण;

काष्ठा mlx5_hv_vhca *mlx5_hv_vhca_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_hv_vhca *hv_vhca = शून्य;

	hv_vhca = kzalloc(माप(*hv_vhca), GFP_KERNEL);
	अगर (!hv_vhca)
		वापस ERR_PTR(-ENOMEM);

	hv_vhca->work_queue = create_singlethपढ़ो_workqueue("mlx5_hv_vhca");
	अगर (!hv_vhca->work_queue) अणु
		kमुक्त(hv_vhca);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	hv_vhca->dev = dev;
	mutex_init(&hv_vhca->agents_lock);

	वापस hv_vhca;
पूर्ण

व्योम mlx5_hv_vhca_destroy(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	अगर (IS_ERR_OR_शून्य(hv_vhca))
		वापस;

	destroy_workqueue(hv_vhca->work_queue);
	kमुक्त(hv_vhca);
पूर्ण

अटल व्योम mlx5_hv_vhca_invalidate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_hv_vhca_work *hwork;
	काष्ठा mlx5_hv_vhca *hv_vhca;
	पूर्णांक i;

	hwork = container_of(work, काष्ठा mlx5_hv_vhca_work, invalidate_work);
	hv_vhca = hwork->hv_vhca;

	mutex_lock(&hv_vhca->agents_lock);
	क्रम (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++) अणु
		काष्ठा mlx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		अगर (!agent || !agent->invalidate)
			जारी;

		अगर (!(BIT(agent->type) & hwork->block_mask))
			जारी;

		agent->invalidate(agent, hwork->block_mask);
	पूर्ण
	mutex_unlock(&hv_vhca->agents_lock);

	kमुक्त(hwork);
पूर्ण

व्योम mlx5_hv_vhca_invalidate(व्योम *context, u64 block_mask)
अणु
	काष्ठा mlx5_hv_vhca *hv_vhca = (काष्ठा mlx5_hv_vhca *)context;
	काष्ठा mlx5_hv_vhca_work *work;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस;

	INIT_WORK(&work->invalidate_work, mlx5_hv_vhca_invalidate_work);
	work->hv_vhca    = hv_vhca;
	work->block_mask = block_mask;

	queue_work(hv_vhca->work_queue, &work->invalidate_work);
पूर्ण

#घोषणा AGENT_MASK(type) (type ? BIT(type - 1) : 0 /* control */)

अटल व्योम mlx5_hv_vhca_agents_control(काष्ठा mlx5_hv_vhca *hv_vhca,
					काष्ठा mlx5_hv_vhca_control_block *block)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++) अणु
		काष्ठा mlx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		अगर (!agent || !agent->control)
			जारी;

		अगर (!(AGENT_MASK(agent->type) & block->control))
			जारी;

		agent->control(agent, block);
	पूर्ण
पूर्ण

अटल व्योम mlx5_hv_vhca_capabilities(काष्ठा mlx5_hv_vhca *hv_vhca,
				      u32 *capabilities)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++) अणु
		काष्ठा mlx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		अगर (agent)
			*capabilities |= AGENT_MASK(agent->type);
	पूर्ण
पूर्ण

अटल व्योम
mlx5_hv_vhca_control_agent_invalidate(काष्ठा mlx5_hv_vhca_agent *agent,
				      u64 block_mask)
अणु
	काष्ठा mlx5_hv_vhca *hv_vhca = agent->hv_vhca;
	काष्ठा mlx5_core_dev *dev = hv_vhca->dev;
	काष्ठा mlx5_hv_vhca_control_block *block;
	u32 capabilities = 0;
	पूर्णांक err;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		वापस;

	err = mlx5_hv_पढ़ो_config(dev, block, माप(*block), 0);
	अगर (err)
		जाओ मुक्त_block;

	mlx5_hv_vhca_capabilities(hv_vhca, &capabilities);

	/* In हाल no capabilities, send empty block in वापस */
	अगर (!capabilities) अणु
		स_रखो(block, 0, माप(*block));
		जाओ ग_लिखो;
	पूर्ण

	अगर (block->capabilities != capabilities)
		block->capabilities = capabilities;

	अगर (block->control & ~capabilities)
		जाओ मुक्त_block;

	mlx5_hv_vhca_agents_control(hv_vhca, block);
	block->command_ack = block->command;

ग_लिखो:
	mlx5_hv_ग_लिखो_config(dev, block, माप(*block), 0);

मुक्त_block:
	kमुक्त(block);
पूर्ण

अटल काष्ठा mlx5_hv_vhca_agent *
mlx5_hv_vhca_control_agent_create(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	वापस mlx5_hv_vhca_agent_create(hv_vhca, MLX5_HV_VHCA_AGENT_CONTROL,
					 शून्य,
					 mlx5_hv_vhca_control_agent_invalidate,
					 शून्य, शून्य);
पूर्ण

अटल व्योम mlx5_hv_vhca_control_agent_destroy(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
	mlx5_hv_vhca_agent_destroy(agent);
पूर्ण

पूर्णांक mlx5_hv_vhca_init(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	काष्ठा mlx5_hv_vhca_agent *agent;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(hv_vhca))
		वापस IS_ERR_OR_शून्य(hv_vhca);

	err = mlx5_hv_रेजिस्टर_invalidate(hv_vhca->dev, hv_vhca,
					  mlx5_hv_vhca_invalidate);
	अगर (err)
		वापस err;

	agent = mlx5_hv_vhca_control_agent_create(hv_vhca);
	अगर (IS_ERR_OR_शून्य(agent)) अणु
		mlx5_hv_unरेजिस्टर_invalidate(hv_vhca->dev);
		वापस IS_ERR_OR_शून्य(agent);
	पूर्ण

	hv_vhca->agents[MLX5_HV_VHCA_AGENT_CONTROL] = agent;

	वापस 0;
पूर्ण

व्योम mlx5_hv_vhca_cleanup(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	काष्ठा mlx5_hv_vhca_agent *agent;
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(hv_vhca))
		वापस;

	agent = hv_vhca->agents[MLX5_HV_VHCA_AGENT_CONTROL];
	अगर (agent)
		mlx5_hv_vhca_control_agent_destroy(agent);

	mutex_lock(&hv_vhca->agents_lock);
	क्रम (i = 0; i < MLX5_HV_VHCA_AGENT_MAX; i++)
		WARN_ON(hv_vhca->agents[i]);

	mutex_unlock(&hv_vhca->agents_lock);

	mlx5_hv_unरेजिस्टर_invalidate(hv_vhca->dev);
पूर्ण

अटल व्योम mlx5_hv_vhca_agents_update(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	mlx5_hv_vhca_invalidate(hv_vhca, BIT(MLX5_HV_VHCA_AGENT_CONTROL));
पूर्ण

काष्ठा mlx5_hv_vhca_agent *
mlx5_hv_vhca_agent_create(काष्ठा mlx5_hv_vhca *hv_vhca,
			  क्रमागत mlx5_hv_vhca_agent_type type,
			  व्योम (*control)(काष्ठा mlx5_hv_vhca_agent*,
					  काष्ठा mlx5_hv_vhca_control_block *block),
			  व्योम (*invalidate)(काष्ठा mlx5_hv_vhca_agent*,
					     u64 block_mask),
			  व्योम (*cleaup)(काष्ठा mlx5_hv_vhca_agent *agent),
			  व्योम *priv)
अणु
	काष्ठा mlx5_hv_vhca_agent *agent;

	अगर (IS_ERR_OR_शून्य(hv_vhca))
		वापस ERR_PTR(-ENOMEM);

	अगर (type >= MLX5_HV_VHCA_AGENT_MAX)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&hv_vhca->agents_lock);
	अगर (hv_vhca->agents[type]) अणु
		mutex_unlock(&hv_vhca->agents_lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	mutex_unlock(&hv_vhca->agents_lock);

	agent = kzalloc(माप(*agent), GFP_KERNEL);
	अगर (!agent)
		वापस ERR_PTR(-ENOMEM);

	agent->type      = type;
	agent->hv_vhca   = hv_vhca;
	agent->priv      = priv;
	agent->control   = control;
	agent->invalidate = invalidate;
	agent->cleanup   = cleaup;

	mutex_lock(&hv_vhca->agents_lock);
	hv_vhca->agents[type] = agent;
	mutex_unlock(&hv_vhca->agents_lock);

	mlx5_hv_vhca_agents_update(hv_vhca);

	वापस agent;
पूर्ण

व्योम mlx5_hv_vhca_agent_destroy(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
	काष्ठा mlx5_hv_vhca *hv_vhca = agent->hv_vhca;

	mutex_lock(&hv_vhca->agents_lock);

	अगर (WARN_ON(agent != hv_vhca->agents[agent->type])) अणु
		mutex_unlock(&hv_vhca->agents_lock);
		वापस;
	पूर्ण

	hv_vhca->agents[agent->type] = शून्य;
	mutex_unlock(&hv_vhca->agents_lock);

	अगर (agent->cleanup)
		agent->cleanup(agent);

	kमुक्त(agent);

	mlx5_hv_vhca_agents_update(hv_vhca);
पूर्ण

अटल पूर्णांक mlx5_hv_vhca_data_block_prepare(काष्ठा mlx5_hv_vhca_agent *agent,
					   काष्ठा mlx5_hv_vhca_data_block *data_block,
					   व्योम *src, पूर्णांक len, पूर्णांक *offset)
अणु
	पूर्णांक bytes = min_t(पूर्णांक, (पूर्णांक)माप(data_block->data), len);

	data_block->sequence = agent->seq;
	data_block->offset   = (*offset)++;
	स_नकल(data_block->data, src, bytes);

	वापस bytes;
पूर्ण

अटल व्योम mlx5_hv_vhca_agent_seq_update(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
	agent->seq++;
पूर्ण

पूर्णांक mlx5_hv_vhca_agent_ग_लिखो(काष्ठा mlx5_hv_vhca_agent *agent,
			     व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक offset = agent->type * HV_CONFIG_BLOCK_SIZE_MAX;
	पूर्णांक block_offset = 0;
	पूर्णांक total = 0;
	पूर्णांक err;

	जबतक (len) अणु
		काष्ठा mlx5_hv_vhca_data_block data_block = अणु0पूर्ण;
		पूर्णांक bytes;

		bytes = mlx5_hv_vhca_data_block_prepare(agent, &data_block,
							buf + total,
							len, &block_offset);
		अगर (!bytes)
			वापस -ENOMEM;

		err = mlx5_hv_ग_लिखो_config(agent->hv_vhca->dev, &data_block,
					   माप(data_block), offset);
		अगर (err)
			वापस err;

		total += bytes;
		len   -= bytes;
	पूर्ण

	mlx5_hv_vhca_agent_seq_update(agent);

	वापस 0;
पूर्ण

व्योम *mlx5_hv_vhca_agent_priv(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
	वापस agent->priv;
पूर्ण
