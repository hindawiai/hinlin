<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies */

#समावेश <linux/mlx5/vport.h>
#समावेश "lib/devcom.h"

अटल LIST_HEAD(devcom_list);

#घोषणा devcom_क्रम_each_component(priv, comp, iter) \
	क्रम (iter = 0; \
	     comp = &(priv)->components[iter], iter < MLX5_DEVCOM_NUM_COMPONENTS; \
	     iter++)

काष्ठा mlx5_devcom_component अणु
	काष्ठा अणु
		व्योम *data;
	पूर्ण device[MLX5_MAX_PORTS];

	mlx5_devcom_event_handler_t handler;
	काष्ठा rw_semaphore sem;
	bool paired;
पूर्ण;

काष्ठा mlx5_devcom_list अणु
	काष्ठा list_head list;

	काष्ठा mlx5_devcom_component components[MLX5_DEVCOM_NUM_COMPONENTS];
	काष्ठा mlx5_core_dev *devs[MLX5_MAX_PORTS];
पूर्ण;

काष्ठा mlx5_devcom अणु
	काष्ठा mlx5_devcom_list *priv;
	पूर्णांक idx;
पूर्ण;

अटल काष्ठा mlx5_devcom_list *mlx5_devcom_list_alloc(व्योम)
अणु
	काष्ठा mlx5_devcom_component *comp;
	काष्ठा mlx5_devcom_list *priv;
	पूर्णांक i;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	devcom_क्रम_each_component(priv, comp, i)
		init_rwsem(&comp->sem);

	वापस priv;
पूर्ण

अटल काष्ठा mlx5_devcom *mlx5_devcom_alloc(काष्ठा mlx5_devcom_list *priv,
					     u8 idx)
अणु
	काष्ठा mlx5_devcom *devcom;

	devcom = kzalloc(माप(*devcom), GFP_KERNEL);
	अगर (!devcom)
		वापस शून्य;

	devcom->priv = priv;
	devcom->idx = idx;
	वापस devcom;
पूर्ण

/* Must be called with पूर्णांकf_mutex held */
काष्ठा mlx5_devcom *mlx5_devcom_रेजिस्टर_device(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_devcom_list *priv = शून्य, *iter;
	काष्ठा mlx5_devcom *devcom = शून्य;
	bool new_priv = false;
	u64 sguid0, sguid1;
	पूर्णांक idx, i;

	अगर (!mlx5_core_is_pf(dev))
		वापस शून्य;

	sguid0 = mlx5_query_nic_प्रणाली_image_guid(dev);
	list_क्रम_each_entry(iter, &devcom_list, list) अणु
		काष्ठा mlx5_core_dev *पंचांगp_dev = शून्य;

		idx = -1;
		क्रम (i = 0; i < MLX5_MAX_PORTS; i++) अणु
			अगर (iter->devs[i])
				पंचांगp_dev = iter->devs[i];
			अन्यथा
				idx = i;
		पूर्ण

		अगर (idx == -1)
			जारी;

		sguid1 = mlx5_query_nic_प्रणाली_image_guid(पंचांगp_dev);
		अगर (sguid0 != sguid1)
			जारी;

		priv = iter;
		अवरोध;
	पूर्ण

	अगर (!priv) अणु
		priv = mlx5_devcom_list_alloc();
		अगर (!priv)
			वापस ERR_PTR(-ENOMEM);

		idx = 0;
		new_priv = true;
	पूर्ण

	priv->devs[idx] = dev;
	devcom = mlx5_devcom_alloc(priv, idx);
	अगर (!devcom) अणु
		kमुक्त(priv);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (new_priv)
		list_add(&priv->list, &devcom_list);

	वापस devcom;
पूर्ण

/* Must be called with पूर्णांकf_mutex held */
व्योम mlx5_devcom_unरेजिस्टर_device(काष्ठा mlx5_devcom *devcom)
अणु
	काष्ठा mlx5_devcom_list *priv;
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(devcom))
		वापस;

	priv = devcom->priv;
	priv->devs[devcom->idx] = शून्य;

	kमुक्त(devcom);

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (priv->devs[i])
			अवरोध;

	अगर (i != MLX5_MAX_PORTS)
		वापस;

	list_del(&priv->list);
	kमुक्त(priv);
पूर्ण

व्योम mlx5_devcom_रेजिस्टर_component(काष्ठा mlx5_devcom *devcom,
				    क्रमागत mlx5_devcom_components id,
				    mlx5_devcom_event_handler_t handler,
				    व्योम *data)
अणु
	काष्ठा mlx5_devcom_component *comp;

	अगर (IS_ERR_OR_शून्य(devcom))
		वापस;

	WARN_ON(!data);

	comp = &devcom->priv->components[id];
	करोwn_ग_लिखो(&comp->sem);
	comp->handler = handler;
	comp->device[devcom->idx].data = data;
	up_ग_लिखो(&comp->sem);
पूर्ण

व्योम mlx5_devcom_unरेजिस्टर_component(काष्ठा mlx5_devcom *devcom,
				      क्रमागत mlx5_devcom_components id)
अणु
	काष्ठा mlx5_devcom_component *comp;

	अगर (IS_ERR_OR_शून्य(devcom))
		वापस;

	comp = &devcom->priv->components[id];
	करोwn_ग_लिखो(&comp->sem);
	comp->device[devcom->idx].data = शून्य;
	up_ग_लिखो(&comp->sem);
पूर्ण

पूर्णांक mlx5_devcom_send_event(काष्ठा mlx5_devcom *devcom,
			   क्रमागत mlx5_devcom_components id,
			   पूर्णांक event,
			   व्योम *event_data)
अणु
	काष्ठा mlx5_devcom_component *comp;
	पूर्णांक err = -ENODEV, i;

	अगर (IS_ERR_OR_शून्य(devcom))
		वापस err;

	comp = &devcom->priv->components[id];
	करोwn_ग_लिखो(&comp->sem);
	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (i != devcom->idx && comp->device[i].data) अणु
			err = comp->handler(event, comp->device[i].data,
					    event_data);
			अवरोध;
		पूर्ण

	up_ग_लिखो(&comp->sem);
	वापस err;
पूर्ण

व्योम mlx5_devcom_set_paired(काष्ठा mlx5_devcom *devcom,
			    क्रमागत mlx5_devcom_components id,
			    bool paired)
अणु
	काष्ठा mlx5_devcom_component *comp;

	comp = &devcom->priv->components[id];
	WARN_ON(!rwsem_is_locked(&comp->sem));

	comp->paired = paired;
पूर्ण

bool mlx5_devcom_is_paired(काष्ठा mlx5_devcom *devcom,
			   क्रमागत mlx5_devcom_components id)
अणु
	अगर (IS_ERR_OR_शून्य(devcom))
		वापस false;

	वापस devcom->priv->components[id].paired;
पूर्ण

व्योम *mlx5_devcom_get_peer_data(काष्ठा mlx5_devcom *devcom,
				क्रमागत mlx5_devcom_components id)
अणु
	काष्ठा mlx5_devcom_component *comp;
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(devcom))
		वापस शून्य;

	comp = &devcom->priv->components[id];
	करोwn_पढ़ो(&comp->sem);
	अगर (!comp->paired) अणु
		up_पढ़ो(&comp->sem);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (i != devcom->idx)
			अवरोध;

	वापस comp->device[i].data;
पूर्ण

व्योम mlx5_devcom_release_peer_data(काष्ठा mlx5_devcom *devcom,
				   क्रमागत mlx5_devcom_components id)
अणु
	काष्ठा mlx5_devcom_component *comp = &devcom->priv->components[id];

	up_पढ़ो(&comp->sem);
पूर्ण
