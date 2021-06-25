<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

#समावेश "hnae3.h"

अटल LIST_HEAD(hnae3_ae_algo_list);
अटल LIST_HEAD(hnae3_client_list);
अटल LIST_HEAD(hnae3_ae_dev_list);

/* we are keeping things simple and using single lock क्रम all the
 * list. This is a non-critical code so other updations, अगर happen
 * in parallel, can रुको.
 */
अटल DEFINE_MUTEX(hnae3_common_lock);

अटल bool hnae3_client_match(क्रमागत hnae3_client_type client_type)
अणु
	अगर (client_type == HNAE3_CLIENT_KNIC ||
	    client_type == HNAE3_CLIENT_ROCE)
		वापस true;

	वापस false;
पूर्ण

व्योम hnae3_set_client_init_flag(काष्ठा hnae3_client *client,
				काष्ठा hnae3_ae_dev *ae_dev,
				अचिन्हित पूर्णांक inited)
अणु
	अगर (!client || !ae_dev)
		वापस;

	चयन (client->type) अणु
	हाल HNAE3_CLIENT_KNIC:
		hnae3_set_bit(ae_dev->flag, HNAE3_KNIC_CLIENT_INITED_B, inited);
		अवरोध;
	हाल HNAE3_CLIENT_ROCE:
		hnae3_set_bit(ae_dev->flag, HNAE3_ROCE_CLIENT_INITED_B, inited);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(hnae3_set_client_init_flag);

अटल पूर्णांक hnae3_get_client_init_flag(काष्ठा hnae3_client *client,
				      काष्ठा hnae3_ae_dev *ae_dev)
अणु
	पूर्णांक inited = 0;

	चयन (client->type) अणु
	हाल HNAE3_CLIENT_KNIC:
		inited = hnae3_get_bit(ae_dev->flag,
				       HNAE3_KNIC_CLIENT_INITED_B);
		अवरोध;
	हाल HNAE3_CLIENT_ROCE:
		inited = hnae3_get_bit(ae_dev->flag,
				       HNAE3_ROCE_CLIENT_INITED_B);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस inited;
पूर्ण

अटल पूर्णांक hnae3_init_client_instance(काष्ठा hnae3_client *client,
				      काष्ठा hnae3_ae_dev *ae_dev)
अणु
	पूर्णांक ret;

	/* check अगर this client matches the type of ae_dev */
	अगर (!(hnae3_client_match(client->type) &&
	      hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B))) अणु
		वापस 0;
	पूर्ण

	ret = ae_dev->ops->init_client_instance(client, ae_dev);
	अगर (ret)
		dev_err(&ae_dev->pdev->dev,
			"fail to instantiate client, ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hnae3_uninit_client_instance(काष्ठा hnae3_client *client,
					 काष्ठा hnae3_ae_dev *ae_dev)
अणु
	/* check अगर this client matches the type of ae_dev */
	अगर (!(hnae3_client_match(client->type) &&
	      hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B)))
		वापस;

	अगर (hnae3_get_client_init_flag(client, ae_dev)) अणु
		ae_dev->ops->uninit_client_instance(client, ae_dev);

		hnae3_set_client_init_flag(client, ae_dev, 0);
	पूर्ण
पूर्ण

पूर्णांक hnae3_रेजिस्टर_client(काष्ठा hnae3_client *client)
अणु
	काष्ठा hnae3_client *client_पंचांगp;
	काष्ठा hnae3_ae_dev *ae_dev;

	अगर (!client)
		वापस -ENODEV;

	mutex_lock(&hnae3_common_lock);
	/* one प्रणाली should only have one client क्रम every type */
	list_क्रम_each_entry(client_पंचांगp, &hnae3_client_list, node) अणु
		अगर (client_पंचांगp->type == client->type)
			जाओ निकास;
	पूर्ण

	list_add_tail(&client->node, &hnae3_client_list);

	/* initialize the client on every matched port */
	list_क्रम_each_entry(ae_dev, &hnae3_ae_dev_list, node) अणु
		/* अगर the client could not be initialized on current port, क्रम
		 * any error reasons, move on to next available port
		 */
		पूर्णांक ret = hnae3_init_client_instance(client, ae_dev);
		अगर (ret)
			dev_err(&ae_dev->pdev->dev,
				"match and instantiation failed for port, ret = %d\n",
				ret);
	पूर्ण

निकास:
	mutex_unlock(&hnae3_common_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hnae3_रेजिस्टर_client);

व्योम hnae3_unरेजिस्टर_client(काष्ठा hnae3_client *client)
अणु
	काष्ठा hnae3_client *client_पंचांगp;
	काष्ठा hnae3_ae_dev *ae_dev;
	bool existed = false;

	अगर (!client)
		वापस;

	mutex_lock(&hnae3_common_lock);
	/* one प्रणाली should only have one client क्रम every type */
	list_क्रम_each_entry(client_पंचांगp, &hnae3_client_list, node) अणु
		अगर (client_पंचांगp->type == client->type) अणु
			existed = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!existed) अणु
		mutex_unlock(&hnae3_common_lock);
		pr_err("client %s does not exist!\n", client->name);
		वापस;
	पूर्ण

	/* un-initialize the client on every matched port */
	list_क्रम_each_entry(ae_dev, &hnae3_ae_dev_list, node) अणु
		hnae3_uninit_client_instance(client, ae_dev);
	पूर्ण

	list_del(&client->node);
	mutex_unlock(&hnae3_common_lock);
पूर्ण
EXPORT_SYMBOL(hnae3_unरेजिस्टर_client);

/* hnae3_रेजिस्टर_ae_algo - रेजिस्टर a AE algorithm to hnae3 framework
 * @ae_algo: AE algorithm
 * NOTE: the duplicated name will not be checked
 */
व्योम hnae3_रेजिस्टर_ae_algo(काष्ठा hnae3_ae_algo *ae_algo)
अणु
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा hnae3_ae_dev *ae_dev;
	काष्ठा hnae3_client *client;
	पूर्णांक ret;

	अगर (!ae_algo)
		वापस;

	mutex_lock(&hnae3_common_lock);

	list_add_tail(&ae_algo->node, &hnae3_ae_algo_list);

	/* Check अगर this algo/ops matches the list of ae_devs */
	list_क्रम_each_entry(ae_dev, &hnae3_ae_dev_list, node) अणु
		id = pci_match_id(ae_algo->pdev_id_table, ae_dev->pdev);
		अगर (!id)
			जारी;

		अगर (!ae_algo->ops) अणु
			dev_err(&ae_dev->pdev->dev, "ae_algo ops are null\n");
			जारी;
		पूर्ण
		ae_dev->ops = ae_algo->ops;

		ret = ae_algo->ops->init_ae_dev(ae_dev);
		अगर (ret) अणु
			dev_err(&ae_dev->pdev->dev,
				"init ae_dev error, ret = %d\n", ret);
			जारी;
		पूर्ण

		/* ae_dev init should set flag */
		hnae3_set_bit(ae_dev->flag, HNAE3_DEV_INITED_B, 1);

		/* check the client list क्रम the match with this ae_dev type and
		 * initialize the figure out client instance
		 */
		list_क्रम_each_entry(client, &hnae3_client_list, node) अणु
			ret = hnae3_init_client_instance(client, ae_dev);
			अगर (ret)
				dev_err(&ae_dev->pdev->dev,
					"match and instantiation failed, ret = %d\n",
					ret);
		पूर्ण
	पूर्ण

	mutex_unlock(&hnae3_common_lock);
पूर्ण
EXPORT_SYMBOL(hnae3_रेजिस्टर_ae_algo);

/* hnae3_unरेजिस्टर_ae_algo - unरेजिस्टरs a AE algorithm
 * @ae_algo: the AE algorithm to unरेजिस्टर
 */
व्योम hnae3_unरेजिस्टर_ae_algo(काष्ठा hnae3_ae_algo *ae_algo)
अणु
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा hnae3_ae_dev *ae_dev;
	काष्ठा hnae3_client *client;

	अगर (!ae_algo)
		वापस;

	mutex_lock(&hnae3_common_lock);
	/* Check अगर there are matched ae_dev */
	list_क्रम_each_entry(ae_dev, &hnae3_ae_dev_list, node) अणु
		अगर (!hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B))
			जारी;

		id = pci_match_id(ae_algo->pdev_id_table, ae_dev->pdev);
		अगर (!id)
			जारी;

		/* check the client list क्रम the match with this ae_dev type and
		 * un-initialize the figure out client instance
		 */
		list_क्रम_each_entry(client, &hnae3_client_list, node)
			hnae3_uninit_client_instance(client, ae_dev);

		ae_algo->ops->uninit_ae_dev(ae_dev);
		hnae3_set_bit(ae_dev->flag, HNAE3_DEV_INITED_B, 0);
		ae_dev->ops = शून्य;
	पूर्ण

	list_del(&ae_algo->node);
	mutex_unlock(&hnae3_common_lock);
पूर्ण
EXPORT_SYMBOL(hnae3_unरेजिस्टर_ae_algo);

/* hnae3_रेजिस्टर_ae_dev - रेजिस्टरs a AE device to hnae3 framework
 * @ae_dev: the AE device
 * NOTE: the duplicated name will not be checked
 */
पूर्णांक hnae3_रेजिस्टर_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा hnae3_ae_algo *ae_algo;
	काष्ठा hnae3_client *client;
	पूर्णांक ret;

	अगर (!ae_dev)
		वापस -ENODEV;

	mutex_lock(&hnae3_common_lock);

	list_add_tail(&ae_dev->node, &hnae3_ae_dev_list);

	/* Check अगर there are matched ae_algo */
	list_क्रम_each_entry(ae_algo, &hnae3_ae_algo_list, node) अणु
		id = pci_match_id(ae_algo->pdev_id_table, ae_dev->pdev);
		अगर (!id)
			जारी;

		अगर (!ae_algo->ops) अणु
			dev_err(&ae_dev->pdev->dev, "ae_algo ops are null\n");
			ret = -EOPNOTSUPP;
			जाओ out_err;
		पूर्ण
		ae_dev->ops = ae_algo->ops;

		ret = ae_dev->ops->init_ae_dev(ae_dev);
		अगर (ret) अणु
			dev_err(&ae_dev->pdev->dev,
				"init ae_dev error, ret = %d\n", ret);
			जाओ out_err;
		पूर्ण

		/* ae_dev init should set flag */
		hnae3_set_bit(ae_dev->flag, HNAE3_DEV_INITED_B, 1);
		अवरोध;
	पूर्ण

	/* check the client list क्रम the match with this ae_dev type and
	 * initialize the figure out client instance
	 */
	list_क्रम_each_entry(client, &hnae3_client_list, node) अणु
		ret = hnae3_init_client_instance(client, ae_dev);
		अगर (ret)
			dev_err(&ae_dev->pdev->dev,
				"match and instantiation failed, ret = %d\n",
				ret);
	पूर्ण

	mutex_unlock(&hnae3_common_lock);

	वापस 0;

out_err:
	list_del(&ae_dev->node);
	mutex_unlock(&hnae3_common_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(hnae3_रेजिस्टर_ae_dev);

/* hnae3_unरेजिस्टर_ae_dev - unरेजिस्टरs a AE device
 * @ae_dev: the AE device to unरेजिस्टर
 */
व्योम hnae3_unरेजिस्टर_ae_dev(काष्ठा hnae3_ae_dev *ae_dev)
अणु
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा hnae3_ae_algo *ae_algo;
	काष्ठा hnae3_client *client;

	अगर (!ae_dev)
		वापस;

	mutex_lock(&hnae3_common_lock);
	/* Check अगर there are matched ae_algo */
	list_क्रम_each_entry(ae_algo, &hnae3_ae_algo_list, node) अणु
		अगर (!hnae3_get_bit(ae_dev->flag, HNAE3_DEV_INITED_B))
			जारी;

		id = pci_match_id(ae_algo->pdev_id_table, ae_dev->pdev);
		अगर (!id)
			जारी;

		list_क्रम_each_entry(client, &hnae3_client_list, node)
			hnae3_uninit_client_instance(client, ae_dev);

		ae_algo->ops->uninit_ae_dev(ae_dev);
		hnae3_set_bit(ae_dev->flag, HNAE3_DEV_INITED_B, 0);
		ae_dev->ops = शून्य;
	पूर्ण

	list_del(&ae_dev->node);
	mutex_unlock(&hnae3_common_lock);
पूर्ण
EXPORT_SYMBOL(hnae3_unरेजिस्टर_ae_dev);

MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HNAE3(Hisilicon Network Acceleration Engine) Framework");
MODULE_VERSION(HNAE3_MOD_VERSION);
