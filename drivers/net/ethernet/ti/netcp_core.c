<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Keystone NetCP Core driver
 *
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		Sandeep Paulraj <s-paulraj@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 *		Murali Karicheri <m-karicheri2@ti.com>
 *		Wingman Kwok <w-kwok2@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_address.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ti/knav_qmss.h>
#समावेश <linux/soc/ti/knav_dma.h>

#समावेश "netcp.h"

#घोषणा NETCP_SOP_OFFSET	(NET_IP_ALIGN + NET_SKB_PAD)
#घोषणा NETCP_NAPI_WEIGHT	64
#घोषणा NETCP_TX_TIMEOUT	(5 * HZ)
#घोषणा NETCP_PACKET_SIZE	(ETH_FRAME_LEN + ETH_FCS_LEN)
#घोषणा NETCP_MIN_PACKET_SIZE	ETH_ZLEN
#घोषणा NETCP_MAX_MCAST_ADDR	16

#घोषणा NETCP_EFUSE_REG_INDEX	0

#घोषणा NETCP_MOD_PROBE_SKIPPED	1
#घोषणा NETCP_MOD_PROBE_FAILED	2

#घोषणा NETCP_DEBUG (NETIF_MSG_HW	| NETIF_MSG_WOL		|	\
		    NETIF_MSG_DRV	| NETIF_MSG_LINK	|	\
		    NETIF_MSG_IFUP	| NETIF_MSG_INTR	|	\
		    NETIF_MSG_PROBE	| NETIF_MSG_TIMER	|	\
		    NETIF_MSG_IFDOWN	| NETIF_MSG_RX_ERR	|	\
		    NETIF_MSG_TX_ERR	| NETIF_MSG_TX_DONE	|	\
		    NETIF_MSG_PKTDATA	| NETIF_MSG_TX_QUEUED	|	\
		    NETIF_MSG_RX_STATUS)

#घोषणा NETCP_EFUSE_ADDR_SWAP	2

#घोषणा knav_queue_get_id(q)	knav_queue_device_control(q, \
				KNAV_QUEUE_GET_ID, (अचिन्हित दीर्घ)शून्य)

#घोषणा knav_queue_enable_notअगरy(q) knav_queue_device_control(q,	\
					KNAV_QUEUE_ENABLE_NOTIFY,	\
					(अचिन्हित दीर्घ)शून्य)

#घोषणा knav_queue_disable_notअगरy(q) knav_queue_device_control(q,	\
					KNAV_QUEUE_DISABLE_NOTIFY,	\
					(अचिन्हित दीर्घ)शून्य)

#घोषणा knav_queue_get_count(q)	knav_queue_device_control(q, \
				KNAV_QUEUE_GET_COUNT, (अचिन्हित दीर्घ)शून्य)

#घोषणा क्रम_each_netcp_module(module)			\
	list_क्रम_each_entry(module, &netcp_modules, module_list)

#घोषणा क्रम_each_netcp_device_module(netcp_device, inst_modpriv) \
	list_क्रम_each_entry(inst_modpriv, \
		&((netcp_device)->modpriv_head), inst_list)

#घोषणा क्रम_each_module(netcp, पूर्णांकf_modpriv)			\
	list_क्रम_each_entry(पूर्णांकf_modpriv, &netcp->module_head, पूर्णांकf_list)

/* Module management काष्ठाures */
काष्ठा netcp_device अणु
	काष्ठा list_head	device_list;
	काष्ठा list_head	पूर्णांकerface_head;
	काष्ठा list_head	modpriv_head;
	काष्ठा device		*device;
पूर्ण;

काष्ठा netcp_inst_modpriv अणु
	काष्ठा netcp_device	*netcp_device;
	काष्ठा netcp_module	*netcp_module;
	काष्ठा list_head	inst_list;
	व्योम			*module_priv;
पूर्ण;

काष्ठा netcp_पूर्णांकf_modpriv अणु
	काष्ठा netcp_पूर्णांकf	*netcp_priv;
	काष्ठा netcp_module	*netcp_module;
	काष्ठा list_head	पूर्णांकf_list;
	व्योम			*module_priv;
पूर्ण;

काष्ठा netcp_tx_cb अणु
	व्योम	*ts_context;
	व्योम	(*txtstamp)(व्योम *context, काष्ठा sk_buff *skb);
पूर्ण;

अटल LIST_HEAD(netcp_devices);
अटल LIST_HEAD(netcp_modules);
अटल DEFINE_MUTEX(netcp_modules_lock);

अटल पूर्णांक netcp_debug_level = -1;
module_param(netcp_debug_level, पूर्णांक, 0);
MODULE_PARM_DESC(netcp_debug_level, "Netcp debug level (NETIF_MSG bits) (0=none,...,16=all)");

/* Helper functions - Get/Set */
अटल व्योम get_pkt_info(dma_addr_t *buff, u32 *buff_len, dma_addr_t *ndesc,
			 काष्ठा knav_dma_desc *desc)
अणु
	*buff_len = le32_to_cpu(desc->buff_len);
	*buff = le32_to_cpu(desc->buff);
	*ndesc = le32_to_cpu(desc->next_desc);
पूर्ण

अटल व्योम get_desc_info(u32 *desc_info, u32 *pkt_info,
			  काष्ठा knav_dma_desc *desc)
अणु
	*desc_info = le32_to_cpu(desc->desc_info);
	*pkt_info = le32_to_cpu(desc->packet_info);
पूर्ण

अटल u32 get_sw_data(पूर्णांक index, काष्ठा knav_dma_desc *desc)
अणु
	/* No Endian conversion needed as this data is untouched by hw */
	वापस desc->sw_data[index];
पूर्ण

/* use these macros to get sw data */
#घोषणा GET_SW_DATA0(desc) get_sw_data(0, desc)
#घोषणा GET_SW_DATA1(desc) get_sw_data(1, desc)
#घोषणा GET_SW_DATA2(desc) get_sw_data(2, desc)
#घोषणा GET_SW_DATA3(desc) get_sw_data(3, desc)

अटल व्योम get_org_pkt_info(dma_addr_t *buff, u32 *buff_len,
			     काष्ठा knav_dma_desc *desc)
अणु
	*buff = le32_to_cpu(desc->orig_buff);
	*buff_len = le32_to_cpu(desc->orig_len);
पूर्ण

अटल व्योम get_words(dma_addr_t *words, पूर्णांक num_words, __le32 *desc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_words; i++)
		words[i] = le32_to_cpu(desc[i]);
पूर्ण

अटल व्योम set_pkt_info(dma_addr_t buff, u32 buff_len, u32 ndesc,
			 काष्ठा knav_dma_desc *desc)
अणु
	desc->buff_len = cpu_to_le32(buff_len);
	desc->buff = cpu_to_le32(buff);
	desc->next_desc = cpu_to_le32(ndesc);
पूर्ण

अटल व्योम set_desc_info(u32 desc_info, u32 pkt_info,
			  काष्ठा knav_dma_desc *desc)
अणु
	desc->desc_info = cpu_to_le32(desc_info);
	desc->packet_info = cpu_to_le32(pkt_info);
पूर्ण

अटल व्योम set_sw_data(पूर्णांक index, u32 data, काष्ठा knav_dma_desc *desc)
अणु
	/* No Endian conversion needed as this data is untouched by hw */
	desc->sw_data[index] = data;
पूर्ण

/* use these macros to set sw data */
#घोषणा SET_SW_DATA0(data, desc) set_sw_data(0, data, desc)
#घोषणा SET_SW_DATA1(data, desc) set_sw_data(1, data, desc)
#घोषणा SET_SW_DATA2(data, desc) set_sw_data(2, data, desc)
#घोषणा SET_SW_DATA3(data, desc) set_sw_data(3, data, desc)

अटल व्योम set_org_pkt_info(dma_addr_t buff, u32 buff_len,
			     काष्ठा knav_dma_desc *desc)
अणु
	desc->orig_buff = cpu_to_le32(buff);
	desc->orig_len = cpu_to_le32(buff_len);
पूर्ण

अटल व्योम set_words(u32 *words, पूर्णांक num_words, __le32 *desc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_words; i++)
		desc[i] = cpu_to_le32(words[i]);
पूर्ण

/* Read the e-fuse value as 32 bit values to be endian independent */
अटल पूर्णांक emac_arch_get_mac_addr(अक्षर *x, व्योम __iomem *efuse_mac, u32 swap)
अणु
	अचिन्हित पूर्णांक addr0, addr1;

	addr1 = पढ़ोl(efuse_mac + 4);
	addr0 = पढ़ोl(efuse_mac);

	चयन (swap) अणु
	हाल NETCP_EFUSE_ADDR_SWAP:
		addr0 = addr1;
		addr1 = पढ़ोl(efuse_mac);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	x[0] = (addr1 & 0x0000ff00) >> 8;
	x[1] = addr1 & 0x000000ff;
	x[2] = (addr0 & 0xff000000) >> 24;
	x[3] = (addr0 & 0x00ff0000) >> 16;
	x[4] = (addr0 & 0x0000ff00) >> 8;
	x[5] = addr0 & 0x000000ff;

	वापस 0;
पूर्ण

/* Module management routines */
अटल पूर्णांक netcp_रेजिस्टर_पूर्णांकerface(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_netdev(netcp->ndev);
	अगर (!ret)
		netcp->netdev_रेजिस्टरed = true;
	वापस ret;
पूर्ण

अटल पूर्णांक netcp_module_probe(काष्ठा netcp_device *netcp_device,
			      काष्ठा netcp_module *module)
अणु
	काष्ठा device *dev = netcp_device->device;
	काष्ठा device_node *devices, *पूर्णांकerface, *node = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा netcp_inst_modpriv *inst_modpriv;
	काष्ठा netcp_पूर्णांकf *netcp_पूर्णांकf;
	काष्ठा netcp_module *पंचांगp;
	bool primary_module_रेजिस्टरed = false;
	पूर्णांक ret;

	/* Find this module in the sub-tree क्रम this device */
	devices = of_get_child_by_name(node, "netcp-devices");
	अगर (!devices) अणु
		dev_err(dev, "could not find netcp-devices node\n");
		वापस NETCP_MOD_PROBE_SKIPPED;
	पूर्ण

	क्रम_each_available_child_of_node(devices, child) अणु
		स्थिर अक्षर *name;
		अक्षर node_name[32];

		अगर (of_property_पढ़ो_string(child, "label", &name) < 0) अणु
			snम_लिखो(node_name, माप(node_name), "%pOFn", child);
			name = node_name;
		पूर्ण
		अगर (!strहालcmp(module->name, name))
			अवरोध;
	पूर्ण

	of_node_put(devices);
	/* If module not used क्रम this device, skip it */
	अगर (!child) अणु
		dev_warn(dev, "module(%s) not used for device\n", module->name);
		वापस NETCP_MOD_PROBE_SKIPPED;
	पूर्ण

	inst_modpriv = devm_kzalloc(dev, माप(*inst_modpriv), GFP_KERNEL);
	अगर (!inst_modpriv) अणु
		of_node_put(child);
		वापस -ENOMEM;
	पूर्ण

	inst_modpriv->netcp_device = netcp_device;
	inst_modpriv->netcp_module = module;
	list_add_tail(&inst_modpriv->inst_list, &netcp_device->modpriv_head);

	ret = module->probe(netcp_device, dev, child,
			    &inst_modpriv->module_priv);
	of_node_put(child);
	अगर (ret) अणु
		dev_err(dev, "Probe of module(%s) failed with %d\n",
			module->name, ret);
		list_del(&inst_modpriv->inst_list);
		devm_kमुक्त(dev, inst_modpriv);
		वापस NETCP_MOD_PROBE_FAILED;
	पूर्ण

	/* Attach modules only अगर the primary module is probed */
	क्रम_each_netcp_module(पंचांगp) अणु
		अगर (पंचांगp->primary)
			primary_module_रेजिस्टरed = true;
	पूर्ण

	अगर (!primary_module_रेजिस्टरed)
		वापस 0;

	/* Attach module to पूर्णांकerfaces */
	list_क्रम_each_entry(netcp_पूर्णांकf, &netcp_device->पूर्णांकerface_head,
			    पूर्णांकerface_list) अणु
		काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;

		पूर्णांकf_modpriv = devm_kzalloc(dev, माप(*पूर्णांकf_modpriv),
					    GFP_KERNEL);
		अगर (!पूर्णांकf_modpriv)
			वापस -ENOMEM;

		पूर्णांकerface = of_parse_phandle(netcp_पूर्णांकf->node_पूर्णांकerface,
					     module->name, 0);

		अगर (!पूर्णांकerface) अणु
			devm_kमुक्त(dev, पूर्णांकf_modpriv);
			जारी;
		पूर्ण

		पूर्णांकf_modpriv->netcp_priv = netcp_पूर्णांकf;
		पूर्णांकf_modpriv->netcp_module = module;
		list_add_tail(&पूर्णांकf_modpriv->पूर्णांकf_list,
			      &netcp_पूर्णांकf->module_head);

		ret = module->attach(inst_modpriv->module_priv,
				     netcp_पूर्णांकf->ndev, पूर्णांकerface,
				     &पूर्णांकf_modpriv->module_priv);
		of_node_put(पूर्णांकerface);
		अगर (ret) अणु
			dev_dbg(dev, "Attach of module %s declined with %d\n",
				module->name, ret);
			list_del(&पूर्णांकf_modpriv->पूर्णांकf_list);
			devm_kमुक्त(dev, पूर्णांकf_modpriv);
			जारी;
		पूर्ण
	पूर्ण

	/* Now रेजिस्टर the पूर्णांकerface with netdev */
	list_क्रम_each_entry(netcp_पूर्णांकf,
			    &netcp_device->पूर्णांकerface_head,
			    पूर्णांकerface_list) अणु
		/* If पूर्णांकerface not रेजिस्टरed then रेजिस्टर now */
		अगर (!netcp_पूर्णांकf->netdev_रेजिस्टरed) अणु
			ret = netcp_रेजिस्टर_पूर्णांकerface(netcp_पूर्णांकf);
			अगर (ret)
				वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक netcp_रेजिस्टर_module(काष्ठा netcp_module *module)
अणु
	काष्ठा netcp_device *netcp_device;
	काष्ठा netcp_module *पंचांगp;
	पूर्णांक ret;

	अगर (!module->name) अणु
		WARN(1, "error registering netcp module: no name\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!module->probe) अणु
		WARN(1, "error registering netcp module: no probe\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&netcp_modules_lock);

	क्रम_each_netcp_module(पंचांगp) अणु
		अगर (!strहालcmp(पंचांगp->name, module->name)) अणु
			mutex_unlock(&netcp_modules_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	list_add_tail(&module->module_list, &netcp_modules);

	list_क्रम_each_entry(netcp_device, &netcp_devices, device_list) अणु
		ret = netcp_module_probe(netcp_device, module);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण
	mutex_unlock(&netcp_modules_lock);
	वापस 0;

fail:
	mutex_unlock(&netcp_modules_lock);
	netcp_unरेजिस्टर_module(module);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_रेजिस्टर_module);

अटल व्योम netcp_release_module(काष्ठा netcp_device *netcp_device,
				 काष्ठा netcp_module *module)
अणु
	काष्ठा netcp_inst_modpriv *inst_modpriv, *inst_पंचांगp;
	काष्ठा netcp_पूर्णांकf *netcp_पूर्णांकf, *netcp_पंचांगp;
	काष्ठा device *dev = netcp_device->device;

	/* Release the module from each पूर्णांकerface */
	list_क्रम_each_entry_safe(netcp_पूर्णांकf, netcp_पंचांगp,
				 &netcp_device->पूर्णांकerface_head,
				 पूर्णांकerface_list) अणु
		काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv, *पूर्णांकf_पंचांगp;

		list_क्रम_each_entry_safe(पूर्णांकf_modpriv, पूर्णांकf_पंचांगp,
					 &netcp_पूर्णांकf->module_head,
					 पूर्णांकf_list) अणु
			अगर (पूर्णांकf_modpriv->netcp_module == module) अणु
				module->release(पूर्णांकf_modpriv->module_priv);
				list_del(&पूर्णांकf_modpriv->पूर्णांकf_list);
				devm_kमुक्त(dev, पूर्णांकf_modpriv);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Remove the module from each instance */
	list_क्रम_each_entry_safe(inst_modpriv, inst_पंचांगp,
				 &netcp_device->modpriv_head, inst_list) अणु
		अगर (inst_modpriv->netcp_module == module) अणु
			module->हटाओ(netcp_device,
				       inst_modpriv->module_priv);
			list_del(&inst_modpriv->inst_list);
			devm_kमुक्त(dev, inst_modpriv);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम netcp_unरेजिस्टर_module(काष्ठा netcp_module *module)
अणु
	काष्ठा netcp_device *netcp_device;
	काष्ठा netcp_module *module_पंचांगp;

	mutex_lock(&netcp_modules_lock);

	list_क्रम_each_entry(netcp_device, &netcp_devices, device_list) अणु
		netcp_release_module(netcp_device, module);
	पूर्ण

	/* Remove the module from the module list */
	क्रम_each_netcp_module(module_पंचांगp) अणु
		अगर (module == module_पंचांगp) अणु
			list_del(&module->module_list);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&netcp_modules_lock);
पूर्ण
EXPORT_SYMBOL_GPL(netcp_unरेजिस्टर_module);

व्योम *netcp_module_get_पूर्णांकf_data(काष्ठा netcp_module *module,
				 काष्ठा netcp_पूर्णांकf *पूर्णांकf)
अणु
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;

	list_क्रम_each_entry(पूर्णांकf_modpriv, &पूर्णांकf->module_head, पूर्णांकf_list)
		अगर (पूर्णांकf_modpriv->netcp_module == module)
			वापस पूर्णांकf_modpriv->module_priv;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_module_get_पूर्णांकf_data);

/* Module TX and RX Hook management */
काष्ठा netcp_hook_list अणु
	काष्ठा list_head	 list;
	netcp_hook_rtn		*hook_rtn;
	व्योम			*hook_data;
	पूर्णांक			 order;
पूर्ण;

पूर्णांक netcp_रेजिस्टर_txhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			  netcp_hook_rtn *hook_rtn, व्योम *hook_data)
अणु
	काष्ठा netcp_hook_list *entry;
	काष्ठा netcp_hook_list *next;
	अचिन्हित दीर्घ flags;

	entry = devm_kzalloc(netcp_priv->dev, माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->hook_rtn  = hook_rtn;
	entry->hook_data = hook_data;
	entry->order     = order;

	spin_lock_irqsave(&netcp_priv->lock, flags);
	list_क्रम_each_entry(next, &netcp_priv->txhook_list_head, list) अणु
		अगर (next->order > order)
			अवरोध;
	पूर्ण
	__list_add(&entry->list, next->list.prev, &next->list);
	spin_unlock_irqrestore(&netcp_priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_रेजिस्टर_txhook);

पूर्णांक netcp_unरेजिस्टर_txhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			    netcp_hook_rtn *hook_rtn, व्योम *hook_data)
अणु
	काष्ठा netcp_hook_list *next, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&netcp_priv->lock, flags);
	list_क्रम_each_entry_safe(next, n, &netcp_priv->txhook_list_head, list) अणु
		अगर ((next->order     == order) &&
		    (next->hook_rtn  == hook_rtn) &&
		    (next->hook_data == hook_data)) अणु
			list_del(&next->list);
			spin_unlock_irqrestore(&netcp_priv->lock, flags);
			devm_kमुक्त(netcp_priv->dev, next);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&netcp_priv->lock, flags);
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_unरेजिस्टर_txhook);

पूर्णांक netcp_रेजिस्टर_rxhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			  netcp_hook_rtn *hook_rtn, व्योम *hook_data)
अणु
	काष्ठा netcp_hook_list *entry;
	काष्ठा netcp_hook_list *next;
	अचिन्हित दीर्घ flags;

	entry = devm_kzalloc(netcp_priv->dev, माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->hook_rtn  = hook_rtn;
	entry->hook_data = hook_data;
	entry->order     = order;

	spin_lock_irqsave(&netcp_priv->lock, flags);
	list_क्रम_each_entry(next, &netcp_priv->rxhook_list_head, list) अणु
		अगर (next->order > order)
			अवरोध;
	पूर्ण
	__list_add(&entry->list, next->list.prev, &next->list);
	spin_unlock_irqrestore(&netcp_priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_रेजिस्टर_rxhook);

पूर्णांक netcp_unरेजिस्टर_rxhook(काष्ठा netcp_पूर्णांकf *netcp_priv, पूर्णांक order,
			    netcp_hook_rtn *hook_rtn, व्योम *hook_data)
अणु
	काष्ठा netcp_hook_list *next, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&netcp_priv->lock, flags);
	list_क्रम_each_entry_safe(next, n, &netcp_priv->rxhook_list_head, list) अणु
		अगर ((next->order     == order) &&
		    (next->hook_rtn  == hook_rtn) &&
		    (next->hook_data == hook_data)) अणु
			list_del(&next->list);
			spin_unlock_irqrestore(&netcp_priv->lock, flags);
			devm_kमुक्त(netcp_priv->dev, next);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&netcp_priv->lock, flags);

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_unरेजिस्टर_rxhook);

अटल व्योम netcp_frag_मुक्त(bool is_frag, व्योम *ptr)
अणु
	अगर (is_frag)
		skb_मुक्त_frag(ptr);
	अन्यथा
		kमुक्त(ptr);
पूर्ण

अटल व्योम netcp_मुक्त_rx_desc_chain(काष्ठा netcp_पूर्णांकf *netcp,
				     काष्ठा knav_dma_desc *desc)
अणु
	काष्ठा knav_dma_desc *ndesc;
	dma_addr_t dma_desc, dma_buf;
	अचिन्हित पूर्णांक buf_len, dma_sz = माप(*ndesc);
	व्योम *buf_ptr;
	u32 पंचांगp;

	get_words(&dma_desc, 1, &desc->next_desc);

	जबतक (dma_desc) अणु
		ndesc = knav_pool_desc_unmap(netcp->rx_pool, dma_desc, dma_sz);
		अगर (unlikely(!ndesc)) अणु
			dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
			अवरोध;
		पूर्ण
		get_pkt_info(&dma_buf, &पंचांगp, &dma_desc, ndesc);
		/* warning!!!! We are retrieving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		buf_ptr = (व्योम *)GET_SW_DATA0(ndesc);
		buf_len = (पूर्णांक)GET_SW_DATA1(desc);
		dma_unmap_page(netcp->dev, dma_buf, PAGE_SIZE, DMA_FROM_DEVICE);
		__मुक्त_page(buf_ptr);
		knav_pool_desc_put(netcp->rx_pool, desc);
	पूर्ण
	/* warning!!!! We are retrieving the भव ptr in the sw_data
	 * field as a 32bit value. Will not work on 64bit machines
	 */
	buf_ptr = (व्योम *)GET_SW_DATA0(desc);
	buf_len = (पूर्णांक)GET_SW_DATA1(desc);

	अगर (buf_ptr)
		netcp_frag_मुक्त(buf_len <= PAGE_SIZE, buf_ptr);
	knav_pool_desc_put(netcp->rx_pool, desc);
पूर्ण

अटल व्योम netcp_empty_rx_queue(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा netcp_stats *rx_stats = &netcp->stats;
	काष्ठा knav_dma_desc *desc;
	अचिन्हित पूर्णांक dma_sz;
	dma_addr_t dma;

	क्रम (; ;) अणु
		dma = knav_queue_pop(netcp->rx_queue, &dma_sz);
		अगर (!dma)
			अवरोध;

		desc = knav_pool_desc_unmap(netcp->rx_pool, dma, dma_sz);
		अगर (unlikely(!desc)) अणु
			dev_err(netcp->ndev_dev, "%s: failed to unmap Rx desc\n",
				__func__);
			rx_stats->rx_errors++;
			जारी;
		पूर्ण
		netcp_मुक्त_rx_desc_chain(netcp, desc);
		rx_stats->rx_dropped++;
	पूर्ण
पूर्ण

अटल पूर्णांक netcp_process_one_rx_packet(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा netcp_stats *rx_stats = &netcp->stats;
	अचिन्हित पूर्णांक dma_sz, buf_len, org_buf_len;
	काष्ठा knav_dma_desc *desc, *ndesc;
	अचिन्हित पूर्णांक pkt_sz = 0, accum_sz;
	काष्ठा netcp_hook_list *rx_hook;
	dma_addr_t dma_desc, dma_buff;
	काष्ठा netcp_packet p_info;
	काष्ठा sk_buff *skb;
	व्योम *org_buf_ptr;
	u32 पंचांगp;

	dma_desc = knav_queue_pop(netcp->rx_queue, &dma_sz);
	अगर (!dma_desc)
		वापस -1;

	desc = knav_pool_desc_unmap(netcp->rx_pool, dma_desc, dma_sz);
	अगर (unlikely(!desc)) अणु
		dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
		वापस 0;
	पूर्ण

	get_pkt_info(&dma_buff, &buf_len, &dma_desc, desc);
	/* warning!!!! We are retrieving the भव ptr in the sw_data
	 * field as a 32bit value. Will not work on 64bit machines
	 */
	org_buf_ptr = (व्योम *)GET_SW_DATA0(desc);
	org_buf_len = (पूर्णांक)GET_SW_DATA1(desc);

	अगर (unlikely(!org_buf_ptr)) अणु
		dev_err(netcp->ndev_dev, "NULL bufptr in desc\n");
		जाओ मुक्त_desc;
	पूर्ण

	pkt_sz &= KNAV_DMA_DESC_PKT_LEN_MASK;
	accum_sz = buf_len;
	dma_unmap_single(netcp->dev, dma_buff, buf_len, DMA_FROM_DEVICE);

	/* Build a new sk_buff क्रम the primary buffer */
	skb = build_skb(org_buf_ptr, org_buf_len);
	अगर (unlikely(!skb)) अणु
		dev_err(netcp->ndev_dev, "build_skb() failed\n");
		जाओ मुक्त_desc;
	पूर्ण

	/* update data, tail and len */
	skb_reserve(skb, NETCP_SOP_OFFSET);
	__skb_put(skb, buf_len);

	/* Fill in the page fragment list */
	जबतक (dma_desc) अणु
		काष्ठा page *page;

		ndesc = knav_pool_desc_unmap(netcp->rx_pool, dma_desc, dma_sz);
		अगर (unlikely(!ndesc)) अणु
			dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
			जाओ मुक्त_desc;
		पूर्ण

		get_pkt_info(&dma_buff, &buf_len, &dma_desc, ndesc);
		/* warning!!!! We are retrieving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		page = (काष्ठा page *)GET_SW_DATA0(ndesc);

		अगर (likely(dma_buff && buf_len && page)) अणु
			dma_unmap_page(netcp->dev, dma_buff, PAGE_SIZE,
				       DMA_FROM_DEVICE);
		पूर्ण अन्यथा अणु
			dev_err(netcp->ndev_dev, "Bad Rx desc dma_buff(%pad), len(%d), page(%p)\n",
				&dma_buff, buf_len, page);
			जाओ मुक्त_desc;
		पूर्ण

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
				offset_in_page(dma_buff), buf_len, PAGE_SIZE);
		accum_sz += buf_len;

		/* Free the descriptor */
		knav_pool_desc_put(netcp->rx_pool, ndesc);
	पूर्ण

	/* check क्रम packet len and warn */
	अगर (unlikely(pkt_sz != accum_sz))
		dev_dbg(netcp->ndev_dev, "mismatch in packet size(%d) & sum of fragments(%d)\n",
			pkt_sz, accum_sz);

	/* Newer version of the Ethernet चयन can trim the Ethernet FCS
	 * from the packet and is indicated in hw_cap. So trim it only क्रम
	 * older h/w
	 */
	अगर (!(netcp->hw_cap & ETH_SW_CAN_REMOVE_ETH_FCS))
		__pskb_trim(skb, skb->len - ETH_FCS_LEN);

	/* Call each of the RX hooks */
	p_info.skb = skb;
	skb->dev = netcp->ndev;
	p_info.rxtstamp_complete = false;
	get_desc_info(&पंचांगp, &p_info.eflags, desc);
	p_info.epib = desc->epib;
	p_info.psdata = (u32 __क्रमce *)desc->psdata;
	p_info.eflags = ((p_info.eflags >> KNAV_DMA_DESC_EFLAGS_SHIFT) &
			 KNAV_DMA_DESC_EFLAGS_MASK);
	list_क्रम_each_entry(rx_hook, &netcp->rxhook_list_head, list) अणु
		पूर्णांक ret;

		ret = rx_hook->hook_rtn(rx_hook->order, rx_hook->hook_data,
					&p_info);
		अगर (unlikely(ret)) अणु
			dev_err(netcp->ndev_dev, "RX hook %d failed: %d\n",
				rx_hook->order, ret);
			/* Free the primary descriptor */
			rx_stats->rx_dropped++;
			knav_pool_desc_put(netcp->rx_pool, desc);
			dev_kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण
	/* Free the primary descriptor */
	knav_pool_desc_put(netcp->rx_pool, desc);

	u64_stats_update_begin(&rx_stats->syncp_rx);
	rx_stats->rx_packets++;
	rx_stats->rx_bytes += skb->len;
	u64_stats_update_end(&rx_stats->syncp_rx);

	/* push skb up the stack */
	skb->protocol = eth_type_trans(skb, netcp->ndev);
	netअगर_receive_skb(skb);
	वापस 0;

मुक्त_desc:
	netcp_मुक्त_rx_desc_chain(netcp, desc);
	rx_stats->rx_errors++;
	वापस 0;
पूर्ण

अटल पूर्णांक netcp_process_rx_packets(काष्ठा netcp_पूर्णांकf *netcp,
				    अचिन्हित पूर्णांक budget)
अणु
	पूर्णांक i;

	क्रम (i = 0; (i < budget) && !netcp_process_one_rx_packet(netcp); i++)
		;
	वापस i;
पूर्ण

/* Release descriptors and attached buffers from Rx FDQ */
अटल व्योम netcp_मुक्त_rx_buf(काष्ठा netcp_पूर्णांकf *netcp, पूर्णांक fdq)
अणु
	काष्ठा knav_dma_desc *desc;
	अचिन्हित पूर्णांक buf_len, dma_sz;
	dma_addr_t dma;
	व्योम *buf_ptr;

	/* Allocate descriptor */
	जबतक ((dma = knav_queue_pop(netcp->rx_fdq[fdq], &dma_sz))) अणु
		desc = knav_pool_desc_unmap(netcp->rx_pool, dma, dma_sz);
		अगर (unlikely(!desc)) अणु
			dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
			जारी;
		पूर्ण

		get_org_pkt_info(&dma, &buf_len, desc);
		/* warning!!!! We are retrieving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		buf_ptr = (व्योम *)GET_SW_DATA0(desc);

		अगर (unlikely(!dma)) अणु
			dev_err(netcp->ndev_dev, "NULL orig_buff in desc\n");
			knav_pool_desc_put(netcp->rx_pool, desc);
			जारी;
		पूर्ण

		अगर (unlikely(!buf_ptr)) अणु
			dev_err(netcp->ndev_dev, "NULL bufptr in desc\n");
			knav_pool_desc_put(netcp->rx_pool, desc);
			जारी;
		पूर्ण

		अगर (fdq == 0) अणु
			dma_unmap_single(netcp->dev, dma, buf_len,
					 DMA_FROM_DEVICE);
			netcp_frag_मुक्त((buf_len <= PAGE_SIZE), buf_ptr);
		पूर्ण अन्यथा अणु
			dma_unmap_page(netcp->dev, dma, buf_len,
				       DMA_FROM_DEVICE);
			__मुक्त_page(buf_ptr);
		पूर्ण

		knav_pool_desc_put(netcp->rx_pool, desc);
	पूर्ण
पूर्ण

अटल व्योम netcp_rxpool_मुक्त(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN &&
	     !IS_ERR_OR_शून्य(netcp->rx_fdq[i]); i++)
		netcp_मुक्त_rx_buf(netcp, i);

	अगर (knav_pool_count(netcp->rx_pool) != netcp->rx_pool_size)
		dev_err(netcp->ndev_dev, "Lost Rx (%d) descriptors\n",
			netcp->rx_pool_size - knav_pool_count(netcp->rx_pool));

	knav_pool_destroy(netcp->rx_pool);
	netcp->rx_pool = शून्य;
पूर्ण

अटल पूर्णांक netcp_allocate_rx_buf(काष्ठा netcp_पूर्णांकf *netcp, पूर्णांक fdq)
अणु
	काष्ठा knav_dma_desc *hwdesc;
	अचिन्हित पूर्णांक buf_len, dma_sz;
	u32 desc_info, pkt_info;
	काष्ठा page *page;
	dma_addr_t dma;
	व्योम *bufptr;
	u32 sw_data[2];

	/* Allocate descriptor */
	hwdesc = knav_pool_desc_get(netcp->rx_pool);
	अगर (IS_ERR_OR_शून्य(hwdesc)) अणु
		dev_dbg(netcp->ndev_dev, "out of rx pool desc\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (likely(fdq == 0)) अणु
		अचिन्हित पूर्णांक primary_buf_len;
		/* Allocate a primary receive queue entry */
		buf_len = NETCP_PACKET_SIZE + NETCP_SOP_OFFSET;
		primary_buf_len = SKB_DATA_ALIGN(buf_len) +
				SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

		bufptr = netdev_alloc_frag(primary_buf_len);
		sw_data[1] = primary_buf_len;

		अगर (unlikely(!bufptr)) अणु
			dev_warn_ratelimited(netcp->ndev_dev,
					     "Primary RX buffer alloc failed\n");
			जाओ fail;
		पूर्ण
		dma = dma_map_single(netcp->dev, bufptr, buf_len,
				     DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(netcp->dev, dma)))
			जाओ fail;

		/* warning!!!! We are saving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		sw_data[0] = (u32)bufptr;
	पूर्ण अन्यथा अणु
		/* Allocate a secondary receive queue entry */
		page = alloc_page(GFP_ATOMIC | GFP_DMA);
		अगर (unlikely(!page)) अणु
			dev_warn_ratelimited(netcp->ndev_dev, "Secondary page alloc failed\n");
			जाओ fail;
		पूर्ण
		buf_len = PAGE_SIZE;
		dma = dma_map_page(netcp->dev, page, 0, buf_len, DMA_TO_DEVICE);
		/* warning!!!! We are saving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		sw_data[0] = (u32)page;
		sw_data[1] = 0;
	पूर्ण

	desc_info =  KNAV_DMA_DESC_PS_INFO_IN_DESC;
	desc_info |= buf_len & KNAV_DMA_DESC_PKT_LEN_MASK;
	pkt_info =  KNAV_DMA_DESC_HAS_EPIB;
	pkt_info |= KNAV_DMA_NUM_PS_WORDS << KNAV_DMA_DESC_PSLEN_SHIFT;
	pkt_info |= (netcp->rx_queue_id & KNAV_DMA_DESC_RETQ_MASK) <<
		    KNAV_DMA_DESC_RETQ_SHIFT;
	set_org_pkt_info(dma, buf_len, hwdesc);
	SET_SW_DATA0(sw_data[0], hwdesc);
	SET_SW_DATA1(sw_data[1], hwdesc);
	set_desc_info(desc_info, pkt_info, hwdesc);

	/* Push to FDQs */
	knav_pool_desc_map(netcp->rx_pool, hwdesc, माप(*hwdesc), &dma,
			   &dma_sz);
	knav_queue_push(netcp->rx_fdq[fdq], dma, माप(*hwdesc), 0);
	वापस 0;

fail:
	knav_pool_desc_put(netcp->rx_pool, hwdesc);
	वापस -ENOMEM;
पूर्ण

/* Refill Rx FDQ with descriptors & attached buffers */
अटल व्योम netcp_rxpool_refill(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	u32 fdq_deficit[KNAV_DMA_FDQ_PER_CHAN] = अणु0पूर्ण;
	पूर्णांक i, ret = 0;

	/* Calculate the FDQ deficit and refill */
	क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN && netcp->rx_fdq[i]; i++) अणु
		fdq_deficit[i] = netcp->rx_queue_depths[i] -
				 knav_queue_get_count(netcp->rx_fdq[i]);

		जबतक (fdq_deficit[i]-- && !ret)
			ret = netcp_allocate_rx_buf(netcp, i);
	पूर्ण /* end क्रम fdqs */
पूर्ण

/* NAPI poll */
अटल पूर्णांक netcp_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = container_of(napi, काष्ठा netcp_पूर्णांकf,
						rx_napi);
	अचिन्हित पूर्णांक packets;

	packets = netcp_process_rx_packets(netcp, budget);

	netcp_rxpool_refill(netcp);
	अगर (packets < budget) अणु
		napi_complete_करोne(&netcp->rx_napi, packets);
		knav_queue_enable_notअगरy(netcp->rx_queue);
	पूर्ण

	वापस packets;
पूर्ण

अटल व्योम netcp_rx_notअगरy(व्योम *arg)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = arg;

	knav_queue_disable_notअगरy(netcp->rx_queue);
	napi_schedule(&netcp->rx_napi);
पूर्ण

अटल व्योम netcp_मुक्त_tx_desc_chain(काष्ठा netcp_पूर्णांकf *netcp,
				     काष्ठा knav_dma_desc *desc,
				     अचिन्हित पूर्णांक desc_sz)
अणु
	काष्ठा knav_dma_desc *ndesc = desc;
	dma_addr_t dma_desc, dma_buf;
	अचिन्हित पूर्णांक buf_len;

	जबतक (ndesc) अणु
		get_pkt_info(&dma_buf, &buf_len, &dma_desc, ndesc);

		अगर (dma_buf && buf_len)
			dma_unmap_single(netcp->dev, dma_buf, buf_len,
					 DMA_TO_DEVICE);
		अन्यथा
			dev_warn(netcp->ndev_dev, "bad Tx desc buf(%pad), len(%d)\n",
				 &dma_buf, buf_len);

		knav_pool_desc_put(netcp->tx_pool, ndesc);
		ndesc = शून्य;
		अगर (dma_desc) अणु
			ndesc = knav_pool_desc_unmap(netcp->tx_pool, dma_desc,
						     desc_sz);
			अगर (!ndesc)
				dev_err(netcp->ndev_dev, "failed to unmap Tx desc\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक netcp_process_tx_compl_packets(काष्ठा netcp_पूर्णांकf *netcp,
					  अचिन्हित पूर्णांक budget)
अणु
	काष्ठा netcp_stats *tx_stats = &netcp->stats;
	काष्ठा knav_dma_desc *desc;
	काष्ठा netcp_tx_cb *tx_cb;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक dma_sz;
	dma_addr_t dma;
	पूर्णांक pkts = 0;

	जबतक (budget--) अणु
		dma = knav_queue_pop(netcp->tx_compl_q, &dma_sz);
		अगर (!dma)
			अवरोध;
		desc = knav_pool_desc_unmap(netcp->tx_pool, dma, dma_sz);
		अगर (unlikely(!desc)) अणु
			dev_err(netcp->ndev_dev, "failed to unmap Tx desc\n");
			tx_stats->tx_errors++;
			जारी;
		पूर्ण

		/* warning!!!! We are retrieving the भव ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		skb = (काष्ठा sk_buff *)GET_SW_DATA0(desc);
		netcp_मुक्त_tx_desc_chain(netcp, desc, dma_sz);
		अगर (!skb) अणु
			dev_err(netcp->ndev_dev, "No skb in Tx desc\n");
			tx_stats->tx_errors++;
			जारी;
		पूर्ण

		tx_cb = (काष्ठा netcp_tx_cb *)skb->cb;
		अगर (tx_cb->txtstamp)
			tx_cb->txtstamp(tx_cb->ts_context, skb);

		अगर (netअगर_subqueue_stopped(netcp->ndev, skb) &&
		    netअगर_running(netcp->ndev) &&
		    (knav_pool_count(netcp->tx_pool) >
		    netcp->tx_resume_threshold)) अणु
			u16 subqueue = skb_get_queue_mapping(skb);

			netअगर_wake_subqueue(netcp->ndev, subqueue);
		पूर्ण

		u64_stats_update_begin(&tx_stats->syncp_tx);
		tx_stats->tx_packets++;
		tx_stats->tx_bytes += skb->len;
		u64_stats_update_end(&tx_stats->syncp_tx);
		dev_kमुक्त_skb(skb);
		pkts++;
	पूर्ण
	वापस pkts;
पूर्ण

अटल पूर्णांक netcp_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक packets;
	काष्ठा netcp_पूर्णांकf *netcp = container_of(napi, काष्ठा netcp_पूर्णांकf,
						tx_napi);

	packets = netcp_process_tx_compl_packets(netcp, budget);
	अगर (packets < budget) अणु
		napi_complete(&netcp->tx_napi);
		knav_queue_enable_notअगरy(netcp->tx_compl_q);
	पूर्ण

	वापस packets;
पूर्ण

अटल व्योम netcp_tx_notअगरy(व्योम *arg)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = arg;

	knav_queue_disable_notअगरy(netcp->tx_compl_q);
	napi_schedule(&netcp->tx_napi);
पूर्ण

अटल काष्ठा knav_dma_desc*
netcp_tx_map_skb(काष्ठा sk_buff *skb, काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा knav_dma_desc *desc, *ndesc, *pdesc;
	अचिन्हित पूर्णांक pkt_len = skb_headlen(skb);
	काष्ठा device *dev = netcp->dev;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक dma_sz;
	पूर्णांक i;

	/* Map the linear buffer */
	dma_addr = dma_map_single(dev, skb->data, pkt_len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, dma_addr))) अणु
		dev_err(netcp->ndev_dev, "Failed to map skb buffer\n");
		वापस शून्य;
	पूर्ण

	desc = knav_pool_desc_get(netcp->tx_pool);
	अगर (IS_ERR_OR_शून्य(desc)) अणु
		dev_err(netcp->ndev_dev, "out of TX desc\n");
		dma_unmap_single(dev, dma_addr, pkt_len, DMA_TO_DEVICE);
		वापस शून्य;
	पूर्ण

	set_pkt_info(dma_addr, pkt_len, 0, desc);
	अगर (skb_is_nonlinear(skb)) अणु
		prefetchw(skb_shinfo(skb));
	पूर्ण अन्यथा अणु
		desc->next_desc = 0;
		जाओ upd_pkt_len;
	पूर्ण

	pdesc = desc;

	/* Handle the हाल where skb is fragmented in pages */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		काष्ठा page *page = skb_frag_page(frag);
		u32 page_offset = skb_frag_off(frag);
		u32 buf_len = skb_frag_size(frag);
		dma_addr_t desc_dma;
		u32 desc_dma_32;

		dma_addr = dma_map_page(dev, page, page_offset, buf_len,
					DMA_TO_DEVICE);
		अगर (unlikely(!dma_addr)) अणु
			dev_err(netcp->ndev_dev, "Failed to map skb page\n");
			जाओ मुक्त_descs;
		पूर्ण

		ndesc = knav_pool_desc_get(netcp->tx_pool);
		अगर (IS_ERR_OR_शून्य(ndesc)) अणु
			dev_err(netcp->ndev_dev, "out of TX desc for frags\n");
			dma_unmap_page(dev, dma_addr, buf_len, DMA_TO_DEVICE);
			जाओ मुक्त_descs;
		पूर्ण

		desc_dma = knav_pool_desc_virt_to_dma(netcp->tx_pool, ndesc);
		set_pkt_info(dma_addr, buf_len, 0, ndesc);
		desc_dma_32 = (u32)desc_dma;
		set_words(&desc_dma_32, 1, &pdesc->next_desc);
		pkt_len += buf_len;
		अगर (pdesc != desc)
			knav_pool_desc_map(netcp->tx_pool, pdesc,
					   माप(*pdesc), &desc_dma, &dma_sz);
		pdesc = ndesc;
	पूर्ण
	अगर (pdesc != desc)
		knav_pool_desc_map(netcp->tx_pool, pdesc, माप(*pdesc),
				   &dma_addr, &dma_sz);

	/* frag list based linkage is not supported क्रम now. */
	अगर (skb_shinfo(skb)->frag_list) अणु
		dev_err_ratelimited(netcp->ndev_dev, "NETIF_F_FRAGLIST not supported\n");
		जाओ मुक्त_descs;
	पूर्ण

upd_pkt_len:
	WARN_ON(pkt_len != skb->len);

	pkt_len &= KNAV_DMA_DESC_PKT_LEN_MASK;
	set_words(&pkt_len, 1, &desc->desc_info);
	वापस desc;

मुक्त_descs:
	netcp_मुक्त_tx_desc_chain(netcp, desc, माप(*desc));
	वापस शून्य;
पूर्ण

अटल पूर्णांक netcp_tx_submit_skb(काष्ठा netcp_पूर्णांकf *netcp,
			       काष्ठा sk_buff *skb,
			       काष्ठा knav_dma_desc *desc)
अणु
	काष्ठा netcp_tx_pipe *tx_pipe = शून्य;
	काष्ठा netcp_hook_list *tx_hook;
	काष्ठा netcp_packet p_info;
	काष्ठा netcp_tx_cb *tx_cb;
	अचिन्हित पूर्णांक dma_sz;
	dma_addr_t dma;
	u32 पंचांगp = 0;
	पूर्णांक ret = 0;

	p_info.netcp = netcp;
	p_info.skb = skb;
	p_info.tx_pipe = शून्य;
	p_info.psdata_len = 0;
	p_info.ts_context = शून्य;
	p_info.txtstamp = शून्य;
	p_info.epib = desc->epib;
	p_info.psdata = (u32 __क्रमce *)desc->psdata;
	स_रखो(p_info.epib, 0, KNAV_DMA_NUM_EPIB_WORDS * माप(__le32));

	/* Find out where to inject the packet क्रम transmission */
	list_क्रम_each_entry(tx_hook, &netcp->txhook_list_head, list) अणु
		ret = tx_hook->hook_rtn(tx_hook->order, tx_hook->hook_data,
					&p_info);
		अगर (unlikely(ret != 0)) अणु
			dev_err(netcp->ndev_dev, "TX hook %d rejected the packet with reason(%d)\n",
				tx_hook->order, ret);
			ret = (ret < 0) ? ret : NETDEV_TX_OK;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Make sure some TX hook claimed the packet */
	tx_pipe = p_info.tx_pipe;
	अगर (!tx_pipe) अणु
		dev_err(netcp->ndev_dev, "No TX hook claimed the packet!\n");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	tx_cb = (काष्ठा netcp_tx_cb *)skb->cb;
	tx_cb->ts_context = p_info.ts_context;
	tx_cb->txtstamp = p_info.txtstamp;

	/* update descriptor */
	अगर (p_info.psdata_len) अणु
		/* psdata poपूर्णांकs to both native-endian and device-endian data */
		__le32 *psdata = (व्योम __क्रमce *)p_info.psdata;

		set_words((u32 *)psdata +
			  (KNAV_DMA_NUM_PS_WORDS - p_info.psdata_len),
			  p_info.psdata_len, psdata);
		पंचांगp |= (p_info.psdata_len & KNAV_DMA_DESC_PSLEN_MASK) <<
			KNAV_DMA_DESC_PSLEN_SHIFT;
	पूर्ण

	पंचांगp |= KNAV_DMA_DESC_HAS_EPIB |
		((netcp->tx_compl_qid & KNAV_DMA_DESC_RETQ_MASK) <<
		KNAV_DMA_DESC_RETQ_SHIFT);

	अगर (!(tx_pipe->flags & SWITCH_TO_PORT_IN_TAGINFO)) अणु
		पंचांगp |= ((tx_pipe->चयन_to_port & KNAV_DMA_DESC_PSFLAG_MASK) <<
			KNAV_DMA_DESC_PSFLAG_SHIFT);
	पूर्ण

	set_words(&पंचांगp, 1, &desc->packet_info);
	/* warning!!!! We are saving the भव ptr in the sw_data
	 * field as a 32bit value. Will not work on 64bit machines
	 */
	SET_SW_DATA0((u32)skb, desc);

	अगर (tx_pipe->flags & SWITCH_TO_PORT_IN_TAGINFO) अणु
		पंचांगp = tx_pipe->चयन_to_port;
		set_words(&पंचांगp, 1, &desc->tag_info);
	पूर्ण

	/* submit packet descriptor */
	ret = knav_pool_desc_map(netcp->tx_pool, desc, माप(*desc), &dma,
				 &dma_sz);
	अगर (unlikely(ret)) अणु
		dev_err(netcp->ndev_dev, "%s() failed to map desc\n", __func__);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	skb_tx_बारtamp(skb);
	knav_queue_push(tx_pipe->dma_queue, dma, dma_sz, 0);

out:
	वापस ret;
पूर्ण

/* Submit the packet */
अटल पूर्णांक netcp_nकरो_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_stats *tx_stats = &netcp->stats;
	पूर्णांक subqueue = skb_get_queue_mapping(skb);
	काष्ठा knav_dma_desc *desc;
	पूर्णांक desc_count, ret = 0;

	अगर (unlikely(skb->len <= 0)) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(skb->len < NETCP_MIN_PACKET_SIZE)) अणु
		ret = skb_padto(skb, NETCP_MIN_PACKET_SIZE);
		अगर (ret < 0) अणु
			/* If we get here, the skb has alपढ़ोy been dropped */
			dev_warn(netcp->ndev_dev, "padding failed (%d), packet dropped\n",
				 ret);
			tx_stats->tx_dropped++;
			वापस ret;
		पूर्ण
		skb->len = NETCP_MIN_PACKET_SIZE;
	पूर्ण

	desc = netcp_tx_map_skb(skb, netcp);
	अगर (unlikely(!desc)) अणु
		netअगर_stop_subqueue(ndev, subqueue);
		ret = -ENOBUFS;
		जाओ drop;
	पूर्ण

	ret = netcp_tx_submit_skb(netcp, skb, desc);
	अगर (ret)
		जाओ drop;

	/* Check Tx pool count & stop subqueue अगर needed */
	desc_count = knav_pool_count(netcp->tx_pool);
	अगर (desc_count < netcp->tx_छोड़ो_threshold) अणु
		dev_dbg(netcp->ndev_dev, "pausing tx, count(%d)\n", desc_count);
		netअगर_stop_subqueue(ndev, subqueue);
	पूर्ण
	वापस NETDEV_TX_OK;

drop:
	tx_stats->tx_dropped++;
	अगर (desc)
		netcp_मुक्त_tx_desc_chain(netcp, desc, माप(*desc));
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक netcp_txpipe_बंद(काष्ठा netcp_tx_pipe *tx_pipe)
अणु
	अगर (tx_pipe->dma_channel) अणु
		knav_dma_बंद_channel(tx_pipe->dma_channel);
		tx_pipe->dma_channel = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_txpipe_बंद);

पूर्णांक netcp_txpipe_खोलो(काष्ठा netcp_tx_pipe *tx_pipe)
अणु
	काष्ठा device *dev = tx_pipe->netcp_device->device;
	काष्ठा knav_dma_cfg config;
	पूर्णांक ret = 0;
	u8 name[16];

	स_रखो(&config, 0, माप(config));
	config.direction = DMA_MEM_TO_DEV;
	config.u.tx.filt_einfo = false;
	config.u.tx.filt_pswords = false;
	config.u.tx.priority = DMA_PRIO_MED_L;

	tx_pipe->dma_channel = knav_dma_खोलो_channel(dev,
				tx_pipe->dma_chan_name, &config);
	अगर (IS_ERR(tx_pipe->dma_channel)) अणु
		dev_err(dev, "failed opening tx chan(%s)\n",
			tx_pipe->dma_chan_name);
		ret = PTR_ERR(tx_pipe->dma_channel);
		जाओ err;
	पूर्ण

	snम_लिखो(name, माप(name), "tx-pipe-%s", dev_name(dev));
	tx_pipe->dma_queue = knav_queue_खोलो(name, tx_pipe->dma_queue_id,
					     KNAV_QUEUE_SHARED);
	अगर (IS_ERR(tx_pipe->dma_queue)) अणु
		dev_err(dev, "Could not open DMA queue for channel \"%s\": %pe\n",
			name, tx_pipe->dma_queue);
		ret = PTR_ERR(tx_pipe->dma_queue);
		जाओ err;
	पूर्ण

	dev_dbg(dev, "opened tx pipe %s\n", name);
	वापस 0;

err:
	अगर (!IS_ERR_OR_शून्य(tx_pipe->dma_channel))
		knav_dma_बंद_channel(tx_pipe->dma_channel);
	tx_pipe->dma_channel = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_txpipe_खोलो);

पूर्णांक netcp_txpipe_init(काष्ठा netcp_tx_pipe *tx_pipe,
		      काष्ठा netcp_device *netcp_device,
		      स्थिर अक्षर *dma_chan_name, अचिन्हित पूर्णांक dma_queue_id)
अणु
	स_रखो(tx_pipe, 0, माप(*tx_pipe));
	tx_pipe->netcp_device = netcp_device;
	tx_pipe->dma_chan_name = dma_chan_name;
	tx_pipe->dma_queue_id = dma_queue_id;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netcp_txpipe_init);

अटल काष्ठा netcp_addr *netcp_addr_find(काष्ठा netcp_पूर्णांकf *netcp,
					  स्थिर u8 *addr,
					  क्रमागत netcp_addr_type type)
अणु
	काष्ठा netcp_addr *naddr;

	list_क्रम_each_entry(naddr, &netcp->addr_list, node) अणु
		अगर (naddr->type != type)
			जारी;
		अगर (addr && स_भेद(addr, naddr->addr, ETH_ALEN))
			जारी;
		वापस naddr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा netcp_addr *netcp_addr_add(काष्ठा netcp_पूर्णांकf *netcp,
					 स्थिर u8 *addr,
					 क्रमागत netcp_addr_type type)
अणु
	काष्ठा netcp_addr *naddr;

	naddr = devm_kदो_स्मृति(netcp->dev, माप(*naddr), GFP_ATOMIC);
	अगर (!naddr)
		वापस शून्य;

	naddr->type = type;
	naddr->flags = 0;
	naddr->netcp = netcp;
	अगर (addr)
		ether_addr_copy(naddr->addr, addr);
	अन्यथा
		eth_zero_addr(naddr->addr);
	list_add_tail(&naddr->node, &netcp->addr_list);

	वापस naddr;
पूर्ण

अटल व्योम netcp_addr_del(काष्ठा netcp_पूर्णांकf *netcp, काष्ठा netcp_addr *naddr)
अणु
	list_del(&naddr->node);
	devm_kमुक्त(netcp->dev, naddr);
पूर्ण

अटल व्योम netcp_addr_clear_mark(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा netcp_addr *naddr;

	list_क्रम_each_entry(naddr, &netcp->addr_list, node)
		naddr->flags = 0;
पूर्ण

अटल व्योम netcp_addr_add_mark(काष्ठा netcp_पूर्णांकf *netcp, स्थिर u8 *addr,
				क्रमागत netcp_addr_type type)
अणु
	काष्ठा netcp_addr *naddr;

	naddr = netcp_addr_find(netcp, addr, type);
	अगर (naddr) अणु
		naddr->flags |= ADDR_VALID;
		वापस;
	पूर्ण

	naddr = netcp_addr_add(netcp, addr, type);
	अगर (!WARN_ON(!naddr))
		naddr->flags |= ADDR_NEW;
पूर्ण

अटल व्योम netcp_addr_sweep_del(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा netcp_addr *naddr, *पंचांगp;
	काष्ठा netcp_पूर्णांकf_modpriv *priv;
	काष्ठा netcp_module *module;
	पूर्णांक error;

	list_क्रम_each_entry_safe(naddr, पंचांगp, &netcp->addr_list, node) अणु
		अगर (naddr->flags & (ADDR_VALID | ADDR_NEW))
			जारी;
		dev_dbg(netcp->ndev_dev, "deleting address %pM, type %x\n",
			naddr->addr, naddr->type);
		क्रम_each_module(netcp, priv) अणु
			module = priv->netcp_module;
			अगर (!module->del_addr)
				जारी;
			error = module->del_addr(priv->module_priv,
						 naddr);
			WARN_ON(error);
		पूर्ण
		netcp_addr_del(netcp, naddr);
	पूर्ण
पूर्ण

अटल व्योम netcp_addr_sweep_add(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा netcp_addr *naddr, *पंचांगp;
	काष्ठा netcp_पूर्णांकf_modpriv *priv;
	काष्ठा netcp_module *module;
	पूर्णांक error;

	list_क्रम_each_entry_safe(naddr, पंचांगp, &netcp->addr_list, node) अणु
		अगर (!(naddr->flags & ADDR_NEW))
			जारी;
		dev_dbg(netcp->ndev_dev, "adding address %pM, type %x\n",
			naddr->addr, naddr->type);

		क्रम_each_module(netcp, priv) अणु
			module = priv->netcp_module;
			अगर (!module->add_addr)
				जारी;
			error = module->add_addr(priv->module_priv, naddr);
			WARN_ON(error);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक netcp_set_promiscuous(काष्ठा netcp_पूर्णांकf *netcp, bool promisc)
अणु
	काष्ठा netcp_पूर्णांकf_modpriv *priv;
	काष्ठा netcp_module *module;
	पूर्णांक error;

	क्रम_each_module(netcp, priv) अणु
		module = priv->netcp_module;
		अगर (!module->set_rx_mode)
			जारी;

		error = module->set_rx_mode(priv->module_priv, promisc);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम netcp_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netdev_hw_addr *ndev_addr;
	bool promisc;

	promisc = (ndev->flags & IFF_PROMISC ||
		   ndev->flags & IFF_ALLMULTI ||
		   netdev_mc_count(ndev) > NETCP_MAX_MCAST_ADDR);

	spin_lock(&netcp->lock);
	/* first clear all marks */
	netcp_addr_clear_mark(netcp);

	/* next add new entries, mark existing ones */
	netcp_addr_add_mark(netcp, ndev->broadcast, ADDR_BCAST);
	क्रम_each_dev_addr(ndev, ndev_addr)
		netcp_addr_add_mark(netcp, ndev_addr->addr, ADDR_DEV);
	netdev_क्रम_each_uc_addr(ndev_addr, ndev)
		netcp_addr_add_mark(netcp, ndev_addr->addr, ADDR_UCAST);
	netdev_क्रम_each_mc_addr(ndev_addr, ndev)
		netcp_addr_add_mark(netcp, ndev_addr->addr, ADDR_MCAST);

	अगर (promisc)
		netcp_addr_add_mark(netcp, शून्य, ADDR_ANY);

	/* finally sweep and callout पूर्णांकo modules */
	netcp_addr_sweep_del(netcp);
	netcp_addr_sweep_add(netcp);
	netcp_set_promiscuous(netcp, promisc);
	spin_unlock(&netcp->lock);
पूर्ण

अटल व्योम netcp_मुक्त_navigator_resources(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	पूर्णांक i;

	अगर (netcp->rx_channel) अणु
		knav_dma_बंद_channel(netcp->rx_channel);
		netcp->rx_channel = शून्य;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(netcp->rx_pool))
		netcp_rxpool_मुक्त(netcp);

	अगर (!IS_ERR_OR_शून्य(netcp->rx_queue)) अणु
		knav_queue_बंद(netcp->rx_queue);
		netcp->rx_queue = शून्य;
	पूर्ण

	क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN &&
	     !IS_ERR_OR_शून्य(netcp->rx_fdq[i]) ; ++i) अणु
		knav_queue_बंद(netcp->rx_fdq[i]);
		netcp->rx_fdq[i] = शून्य;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(netcp->tx_compl_q)) अणु
		knav_queue_बंद(netcp->tx_compl_q);
		netcp->tx_compl_q = शून्य;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(netcp->tx_pool)) अणु
		knav_pool_destroy(netcp->tx_pool);
		netcp->tx_pool = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक netcp_setup_navigator_resources(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा knav_queue_notअगरy_config notअगरy_cfg;
	काष्ठा knav_dma_cfg config;
	u32 last_fdq = 0;
	u8 name[16];
	पूर्णांक ret;
	पूर्णांक i;

	/* Create Rx/Tx descriptor pools */
	snम_लिखो(name, माप(name), "rx-pool-%s", ndev->name);
	netcp->rx_pool = knav_pool_create(name, netcp->rx_pool_size,
						netcp->rx_pool_region_id);
	अगर (IS_ERR_OR_शून्य(netcp->rx_pool)) अणु
		dev_err(netcp->ndev_dev, "Couldn't create rx pool\n");
		ret = PTR_ERR(netcp->rx_pool);
		जाओ fail;
	पूर्ण

	snम_लिखो(name, माप(name), "tx-pool-%s", ndev->name);
	netcp->tx_pool = knav_pool_create(name, netcp->tx_pool_size,
						netcp->tx_pool_region_id);
	अगर (IS_ERR_OR_शून्य(netcp->tx_pool)) अणु
		dev_err(netcp->ndev_dev, "Couldn't create tx pool\n");
		ret = PTR_ERR(netcp->tx_pool);
		जाओ fail;
	पूर्ण

	/* खोलो Tx completion queue */
	snम_लिखो(name, माप(name), "tx-compl-%s", ndev->name);
	netcp->tx_compl_q = knav_queue_खोलो(name, netcp->tx_compl_qid, 0);
	अगर (IS_ERR(netcp->tx_compl_q)) अणु
		ret = PTR_ERR(netcp->tx_compl_q);
		जाओ fail;
	पूर्ण
	netcp->tx_compl_qid = knav_queue_get_id(netcp->tx_compl_q);

	/* Set notअगरication क्रम Tx completion */
	notअगरy_cfg.fn = netcp_tx_notअगरy;
	notअगरy_cfg.fn_arg = netcp;
	ret = knav_queue_device_control(netcp->tx_compl_q,
					KNAV_QUEUE_SET_NOTIFIER,
					(अचिन्हित दीर्घ)&notअगरy_cfg);
	अगर (ret)
		जाओ fail;

	knav_queue_disable_notअगरy(netcp->tx_compl_q);

	/* खोलो Rx completion queue */
	snम_लिखो(name, माप(name), "rx-compl-%s", ndev->name);
	netcp->rx_queue = knav_queue_खोलो(name, netcp->rx_queue_id, 0);
	अगर (IS_ERR(netcp->rx_queue)) अणु
		ret = PTR_ERR(netcp->rx_queue);
		जाओ fail;
	पूर्ण
	netcp->rx_queue_id = knav_queue_get_id(netcp->rx_queue);

	/* Set notअगरication क्रम Rx completion */
	notअगरy_cfg.fn = netcp_rx_notअगरy;
	notअगरy_cfg.fn_arg = netcp;
	ret = knav_queue_device_control(netcp->rx_queue,
					KNAV_QUEUE_SET_NOTIFIER,
					(अचिन्हित दीर्घ)&notअगरy_cfg);
	अगर (ret)
		जाओ fail;

	knav_queue_disable_notअगरy(netcp->rx_queue);

	/* खोलो Rx FDQs */
	क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN && netcp->rx_queue_depths[i];
	     ++i) अणु
		snम_लिखो(name, माप(name), "rx-fdq-%s-%d", ndev->name, i);
		netcp->rx_fdq[i] = knav_queue_खोलो(name, KNAV_QUEUE_GP, 0);
		अगर (IS_ERR(netcp->rx_fdq[i])) अणु
			ret = PTR_ERR(netcp->rx_fdq[i]);
			जाओ fail;
		पूर्ण
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.direction		= DMA_DEV_TO_MEM;
	config.u.rx.einfo_present	= true;
	config.u.rx.psinfo_present	= true;
	config.u.rx.err_mode		= DMA_DROP;
	config.u.rx.desc_type		= DMA_DESC_HOST;
	config.u.rx.psinfo_at_sop	= false;
	config.u.rx.sop_offset		= NETCP_SOP_OFFSET;
	config.u.rx.dst_q		= netcp->rx_queue_id;
	config.u.rx.thresh		= DMA_THRESH_NONE;

	क्रम (i = 0; i < KNAV_DMA_FDQ_PER_CHAN; ++i) अणु
		अगर (netcp->rx_fdq[i])
			last_fdq = knav_queue_get_id(netcp->rx_fdq[i]);
		config.u.rx.fdq[i] = last_fdq;
	पूर्ण

	netcp->rx_channel = knav_dma_खोलो_channel(netcp->netcp_device->device,
					netcp->dma_chan_name, &config);
	अगर (IS_ERR(netcp->rx_channel)) अणु
		dev_err(netcp->ndev_dev, "failed opening rx chan(%s\n",
			netcp->dma_chan_name);
		ret = PTR_ERR(netcp->rx_channel);
		जाओ fail;
	पूर्ण

	dev_dbg(netcp->ndev_dev, "opened RX channel: %p\n", netcp->rx_channel);
	वापस 0;

fail:
	netcp_मुक्त_navigator_resources(netcp);
	वापस ret;
पूर्ण

/* Open the device */
अटल पूर्णांक netcp_nकरो_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;
	काष्ठा netcp_module *module;
	पूर्णांक ret;

	netअगर_carrier_off(ndev);
	ret = netcp_setup_navigator_resources(ndev);
	अगर (ret) अणु
		dev_err(netcp->ndev_dev, "Failed to setup navigator resources\n");
		जाओ fail;
	पूर्ण

	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर (module->खोलो) अणु
			ret = module->खोलो(पूर्णांकf_modpriv->module_priv, ndev);
			अगर (ret != 0) अणु
				dev_err(netcp->ndev_dev, "module open failed\n");
				जाओ fail_खोलो;
			पूर्ण
		पूर्ण
	पूर्ण

	napi_enable(&netcp->rx_napi);
	napi_enable(&netcp->tx_napi);
	knav_queue_enable_notअगरy(netcp->tx_compl_q);
	knav_queue_enable_notअगरy(netcp->rx_queue);
	netcp_rxpool_refill(netcp);
	netअगर_tx_wake_all_queues(ndev);
	dev_dbg(netcp->ndev_dev, "netcp device %s opened\n", ndev->name);
	वापस 0;

fail_खोलो:
	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर (module->बंद)
			module->बंद(पूर्णांकf_modpriv->module_priv, ndev);
	पूर्ण

fail:
	netcp_मुक्त_navigator_resources(netcp);
	वापस ret;
पूर्ण

/* Close the device */
अटल पूर्णांक netcp_nकरो_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;
	काष्ठा netcp_module *module;
	पूर्णांक err = 0;

	netअगर_tx_stop_all_queues(ndev);
	netअगर_carrier_off(ndev);
	netcp_addr_clear_mark(netcp);
	netcp_addr_sweep_del(netcp);
	knav_queue_disable_notअगरy(netcp->rx_queue);
	knav_queue_disable_notअगरy(netcp->tx_compl_q);
	napi_disable(&netcp->rx_napi);
	napi_disable(&netcp->tx_napi);

	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर (module->बंद) अणु
			err = module->बंद(पूर्णांकf_modpriv->module_priv, ndev);
			अगर (err != 0)
				dev_err(netcp->ndev_dev, "Close failed\n");
		पूर्ण
	पूर्ण

	/* Recycle Rx descriptors from completion queue */
	netcp_empty_rx_queue(netcp);

	/* Recycle Tx descriptors from completion queue */
	netcp_process_tx_compl_packets(netcp, netcp->tx_pool_size);

	अगर (knav_pool_count(netcp->tx_pool) != netcp->tx_pool_size)
		dev_err(netcp->ndev_dev, "Lost (%d) Tx descs\n",
			netcp->tx_pool_size - knav_pool_count(netcp->tx_pool));

	netcp_मुक्त_navigator_resources(netcp);
	dev_dbg(netcp->ndev_dev, "netcp device %s stopped\n", ndev->name);
	वापस 0;
पूर्ण

अटल पूर्णांक netcp_nकरो_ioctl(काष्ठा net_device *ndev,
			   काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;
	काष्ठा netcp_module *module;
	पूर्णांक ret = -1, err = -EOPNOTSUPP;

	अगर (!netअगर_running(ndev))
		वापस -EINVAL;

	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर (!module->ioctl)
			जारी;

		err = module->ioctl(पूर्णांकf_modpriv->module_priv, req, cmd);
		अगर ((err < 0) && (err != -EOPNOTSUPP)) अणु
			ret = err;
			जाओ out;
		पूर्ण
		अगर (err == 0)
			ret = err;
	पूर्ण

out:
	वापस (ret == 0) ? 0 : err;
पूर्ण

अटल व्योम netcp_nकरो_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	अचिन्हित पूर्णांक descs = knav_pool_count(netcp->tx_pool);

	dev_err(netcp->ndev_dev, "transmit timed out tx descs(%d)\n", descs);
	netcp_process_tx_compl_packets(netcp, netcp->tx_pool_size);
	netअगर_trans_update(ndev);
	netअगर_tx_wake_all_queues(ndev);
पूर्ण

अटल पूर्णांक netcp_rx_add_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;
	काष्ठा netcp_module *module;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	dev_dbg(netcp->ndev_dev, "adding rx vlan id: %d\n", vid);

	spin_lock_irqsave(&netcp->lock, flags);
	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर ((module->add_vid) && (vid != 0)) अणु
			err = module->add_vid(पूर्णांकf_modpriv->module_priv, vid);
			अगर (err != 0) अणु
				dev_err(netcp->ndev_dev, "Could not add vlan id = %d\n",
					vid);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&netcp->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक netcp_rx_समाप्त_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv;
	काष्ठा netcp_module *module;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	dev_dbg(netcp->ndev_dev, "removing rx vlan id: %d\n", vid);

	spin_lock_irqsave(&netcp->lock, flags);
	क्रम_each_module(netcp, पूर्णांकf_modpriv) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		अगर (module->del_vid) अणु
			err = module->del_vid(पूर्णांकf_modpriv->module_priv, vid);
			अगर (err != 0) अणु
				dev_err(netcp->ndev_dev, "Could not delete vlan id = %d\n",
					vid);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&netcp->lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक netcp_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			  व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	u8 num_tc;
	पूर्णांक i;

	/* setup tc must be called under rtnl lock */
	ASSERT_RTNL();

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_tc = mqprio->num_tc;

	/* Sanity-check the number of traffic classes requested */
	अगर ((dev->real_num_tx_queues <= 1) ||
	    (dev->real_num_tx_queues < num_tc))
		वापस -EINVAL;

	/* Configure traffic class to queue mappings */
	अगर (num_tc) अणु
		netdev_set_num_tc(dev, num_tc);
		क्रम (i = 0; i < num_tc; i++)
			netdev_set_tc_queue(dev, i, 1, i);
	पूर्ण अन्यथा अणु
		netdev_reset_tc(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
netcp_get_stats(काष्ठा net_device *ndev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_stats *p = &netcp->stats;
	u64 rxpackets, rxbytes, txpackets, txbytes;
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(&p->syncp_rx);
		rxpackets       = p->rx_packets;
		rxbytes         = p->rx_bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp_rx, start));

	करो अणु
		start = u64_stats_fetch_begin_irq(&p->syncp_tx);
		txpackets       = p->tx_packets;
		txbytes         = p->tx_bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp_tx, start));

	stats->rx_packets = rxpackets;
	stats->rx_bytes = rxbytes;
	stats->tx_packets = txpackets;
	stats->tx_bytes = txbytes;

	/* The following are stored as 32 bit */
	stats->rx_errors = p->rx_errors;
	stats->rx_dropped = p->rx_dropped;
	stats->tx_dropped = p->tx_dropped;
पूर्ण

अटल स्थिर काष्ठा net_device_ops netcp_netdev_ops = अणु
	.nकरो_खोलो		= netcp_nकरो_खोलो,
	.nकरो_stop		= netcp_nकरो_stop,
	.nकरो_start_xmit		= netcp_nकरो_start_xmit,
	.nकरो_set_rx_mode	= netcp_set_rx_mode,
	.nकरो_करो_ioctl           = netcp_nकरो_ioctl,
	.nकरो_get_stats64        = netcp_get_stats,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= netcp_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= netcp_rx_समाप्त_vid,
	.nकरो_tx_समयout		= netcp_nकरो_tx_समयout,
	.nकरो_select_queue	= dev_pick_tx_zero,
	.nकरो_setup_tc		= netcp_setup_tc,
पूर्ण;

अटल पूर्णांक netcp_create_पूर्णांकerface(काष्ठा netcp_device *netcp_device,
				  काष्ठा device_node *node_पूर्णांकerface)
अणु
	काष्ठा device *dev = netcp_device->device;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा netcp_पूर्णांकf *netcp;
	काष्ठा net_device *ndev;
	resource_माप_प्रकार size;
	काष्ठा resource res;
	व्योम __iomem *efuse = शून्य;
	u32 efuse_mac = 0;
	u8 efuse_mac_addr[6];
	u32 temp[2];
	पूर्णांक ret = 0;

	ndev = alloc_etherdev_mqs(माप(*netcp), 1, 1);
	अगर (!ndev) अणु
		dev_err(dev, "Error allocating netdev\n");
		वापस -ENOMEM;
	पूर्ण

	ndev->features |= NETIF_F_SG;
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	ndev->hw_features = ndev->features;
	ndev->vlan_features |=  NETIF_F_SG;

	/* MTU range: 68 - 9486 */
	ndev->min_mtu = ETH_MIN_MTU;
	ndev->max_mtu = NETCP_MAX_FRAME_SIZE - (ETH_HLEN + ETH_FCS_LEN);

	netcp = netdev_priv(ndev);
	spin_lock_init(&netcp->lock);
	INIT_LIST_HEAD(&netcp->module_head);
	INIT_LIST_HEAD(&netcp->txhook_list_head);
	INIT_LIST_HEAD(&netcp->rxhook_list_head);
	INIT_LIST_HEAD(&netcp->addr_list);
	u64_stats_init(&netcp->stats.syncp_rx);
	u64_stats_init(&netcp->stats.syncp_tx);
	netcp->netcp_device = netcp_device;
	netcp->dev = netcp_device->device;
	netcp->ndev = ndev;
	netcp->ndev_dev  = &ndev->dev;
	netcp->msg_enable = netअगर_msg_init(netcp_debug_level, NETCP_DEBUG);
	netcp->tx_छोड़ो_threshold = MAX_SKB_FRAGS;
	netcp->tx_resume_threshold = netcp->tx_छोड़ो_threshold;
	netcp->node_पूर्णांकerface = node_पूर्णांकerface;

	ret = of_property_पढ़ो_u32(node_पूर्णांकerface, "efuse-mac", &efuse_mac);
	अगर (efuse_mac) अणु
		अगर (of_address_to_resource(node, NETCP_EFUSE_REG_INDEX, &res)) अणु
			dev_err(dev, "could not find efuse-mac reg resource\n");
			ret = -ENODEV;
			जाओ quit;
		पूर्ण
		size = resource_size(&res);

		अगर (!devm_request_mem_region(dev, res.start, size,
					     dev_name(dev))) अणु
			dev_err(dev, "could not reserve resource\n");
			ret = -ENOMEM;
			जाओ quit;
		पूर्ण

		efuse = devm_ioremap(dev, res.start, size);
		अगर (!efuse) अणु
			dev_err(dev, "could not map resource\n");
			devm_release_mem_region(dev, res.start, size);
			ret = -ENOMEM;
			जाओ quit;
		पूर्ण

		emac_arch_get_mac_addr(efuse_mac_addr, efuse, efuse_mac);
		अगर (is_valid_ether_addr(efuse_mac_addr))
			ether_addr_copy(ndev->dev_addr, efuse_mac_addr);
		अन्यथा
			eth_अक्रमom_addr(ndev->dev_addr);

		devm_iounmap(dev, efuse);
		devm_release_mem_region(dev, res.start, size);
	पूर्ण अन्यथा अणु
		ret = of_get_mac_address(node_पूर्णांकerface, ndev->dev_addr);
		अगर (ret)
			eth_अक्रमom_addr(ndev->dev_addr);
	पूर्ण

	ret = of_property_पढ़ो_string(node_पूर्णांकerface, "rx-channel",
				      &netcp->dma_chan_name);
	अगर (ret < 0) अणु
		dev_err(dev, "missing \"rx-channel\" parameter\n");
		ret = -ENODEV;
		जाओ quit;
	पूर्ण

	ret = of_property_पढ़ो_u32(node_पूर्णांकerface, "rx-queue",
				   &netcp->rx_queue_id);
	अगर (ret < 0) अणु
		dev_warn(dev, "missing \"rx-queue\" parameter\n");
		netcp->rx_queue_id = KNAV_QUEUE_QPEND;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(node_पूर्णांकerface, "rx-queue-depth",
					 netcp->rx_queue_depths,
					 KNAV_DMA_FDQ_PER_CHAN);
	अगर (ret < 0) अणु
		dev_err(dev, "missing \"rx-queue-depth\" parameter\n");
		netcp->rx_queue_depths[0] = 128;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(node_पूर्णांकerface, "rx-pool", temp, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "missing \"rx-pool\" parameter\n");
		ret = -ENODEV;
		जाओ quit;
	पूर्ण
	netcp->rx_pool_size = temp[0];
	netcp->rx_pool_region_id = temp[1];

	ret = of_property_पढ़ो_u32_array(node_पूर्णांकerface, "tx-pool", temp, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "missing \"tx-pool\" parameter\n");
		ret = -ENODEV;
		जाओ quit;
	पूर्ण
	netcp->tx_pool_size = temp[0];
	netcp->tx_pool_region_id = temp[1];

	अगर (netcp->tx_pool_size < MAX_SKB_FRAGS) अणु
		dev_err(dev, "tx-pool size too small, must be atleast(%ld)\n",
			MAX_SKB_FRAGS);
		ret = -ENODEV;
		जाओ quit;
	पूर्ण

	ret = of_property_पढ़ो_u32(node_पूर्णांकerface, "tx-completion-queue",
				   &netcp->tx_compl_qid);
	अगर (ret < 0) अणु
		dev_warn(dev, "missing \"tx-completion-queue\" parameter\n");
		netcp->tx_compl_qid = KNAV_QUEUE_QPEND;
	पूर्ण

	/* NAPI रेजिस्टर */
	netअगर_napi_add(ndev, &netcp->rx_napi, netcp_rx_poll, NETCP_NAPI_WEIGHT);
	netअगर_tx_napi_add(ndev, &netcp->tx_napi, netcp_tx_poll, NETCP_NAPI_WEIGHT);

	/* Register the network device */
	ndev->dev_id		= 0;
	ndev->watchकरोg_समयo	= NETCP_TX_TIMEOUT;
	ndev->netdev_ops	= &netcp_netdev_ops;
	SET_NETDEV_DEV(ndev, dev);

	list_add_tail(&netcp->पूर्णांकerface_list, &netcp_device->पूर्णांकerface_head);
	वापस 0;

quit:
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

अटल व्योम netcp_delete_पूर्णांकerface(काष्ठा netcp_device *netcp_device,
				   काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf_modpriv *पूर्णांकf_modpriv, *पंचांगp;
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा netcp_module *module;

	dev_dbg(netcp_device->device, "Removing interface \"%s\"\n",
		ndev->name);

	/* Notअगरy each of the modules that the पूर्णांकerface is going away */
	list_क्रम_each_entry_safe(पूर्णांकf_modpriv, पंचांगp, &netcp->module_head,
				 पूर्णांकf_list) अणु
		module = पूर्णांकf_modpriv->netcp_module;
		dev_dbg(netcp_device->device, "Releasing module \"%s\"\n",
			module->name);
		अगर (module->release)
			module->release(पूर्णांकf_modpriv->module_priv);
		list_del(&पूर्णांकf_modpriv->पूर्णांकf_list);
	पूर्ण
	WARN(!list_empty(&netcp->module_head), "%s interface module list is not empty!\n",
	     ndev->name);

	list_del(&netcp->पूर्णांकerface_list);

	of_node_put(netcp->node_पूर्णांकerface);
	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);
पूर्ण

अटल पूर्णांक netcp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा netcp_पूर्णांकf *netcp_पूर्णांकf, *netcp_पंचांगp;
	काष्ठा device_node *child, *पूर्णांकerfaces;
	काष्ठा netcp_device *netcp_device;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा netcp_module *module;
	पूर्णांक ret;

	अगर (!knav_dma_device_पढ़ोy() ||
	    !knav_qmss_device_पढ़ोy())
		वापस -EPROBE_DEFER;

	अगर (!node) अणु
		dev_err(dev, "could not find device info\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate a new NETCP device instance */
	netcp_device = devm_kzalloc(dev, माप(*netcp_device), GFP_KERNEL);
	अगर (!netcp_device)
		वापस -ENOMEM;

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable NETCP power-domain\n");
		pm_runसमय_disable(&pdev->dev);
		वापस ret;
	पूर्ण

	/* Initialize the NETCP device instance */
	INIT_LIST_HEAD(&netcp_device->पूर्णांकerface_head);
	INIT_LIST_HEAD(&netcp_device->modpriv_head);
	netcp_device->device = dev;
	platक्रमm_set_drvdata(pdev, netcp_device);

	/* create पूर्णांकerfaces */
	पूर्णांकerfaces = of_get_child_by_name(node, "netcp-interfaces");
	अगर (!पूर्णांकerfaces) अणु
		dev_err(dev, "could not find netcp-interfaces node\n");
		ret = -ENODEV;
		जाओ probe_quit;
	पूर्ण

	क्रम_each_available_child_of_node(पूर्णांकerfaces, child) अणु
		ret = netcp_create_पूर्णांकerface(netcp_device, child);
		अगर (ret) अणु
			dev_err(dev, "could not create interface(%pOFn)\n",
				child);
			जाओ probe_quit_पूर्णांकerface;
		पूर्ण
	पूर्ण

	of_node_put(पूर्णांकerfaces);

	/* Add the device instance to the list */
	list_add_tail(&netcp_device->device_list, &netcp_devices);

	/* Probe & attach any modules alपढ़ोy रेजिस्टरed */
	mutex_lock(&netcp_modules_lock);
	क्रम_each_netcp_module(module) अणु
		ret = netcp_module_probe(netcp_device, module);
		अगर (ret < 0)
			dev_err(dev, "module(%s) probe failed\n", module->name);
	पूर्ण
	mutex_unlock(&netcp_modules_lock);
	वापस 0;

probe_quit_पूर्णांकerface:
	list_क्रम_each_entry_safe(netcp_पूर्णांकf, netcp_पंचांगp,
				 &netcp_device->पूर्णांकerface_head,
				 पूर्णांकerface_list) अणु
		netcp_delete_पूर्णांकerface(netcp_device, netcp_पूर्णांकf->ndev);
	पूर्ण

	of_node_put(पूर्णांकerfaces);

probe_quit:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	platक्रमm_set_drvdata(pdev, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक netcp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा netcp_device *netcp_device = platक्रमm_get_drvdata(pdev);
	काष्ठा netcp_पूर्णांकf *netcp_पूर्णांकf, *netcp_पंचांगp;
	काष्ठा netcp_inst_modpriv *inst_modpriv, *पंचांगp;
	काष्ठा netcp_module *module;

	list_क्रम_each_entry_safe(inst_modpriv, पंचांगp, &netcp_device->modpriv_head,
				 inst_list) अणु
		module = inst_modpriv->netcp_module;
		dev_dbg(&pdev->dev, "Removing module \"%s\"\n", module->name);
		module->हटाओ(netcp_device, inst_modpriv->module_priv);
		list_del(&inst_modpriv->inst_list);
	पूर्ण

	/* now that all modules are हटाओd, clean up the पूर्णांकerfaces */
	list_क्रम_each_entry_safe(netcp_पूर्णांकf, netcp_पंचांगp,
				 &netcp_device->पूर्णांकerface_head,
				 पूर्णांकerface_list) अणु
		netcp_delete_पूर्णांकerface(netcp_device, netcp_पूर्णांकf->ndev);
	पूर्ण

	WARN(!list_empty(&netcp_device->पूर्णांकerface_head),
	     "%s interface list not empty!\n", pdev->name);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	platक्रमm_set_drvdata(pdev, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "ti,netcp-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_match);

अटल काष्ठा platक्रमm_driver netcp_driver = अणु
	.driver = अणु
		.name		= "netcp-1.0",
		.of_match_table	= of_match,
	पूर्ण,
	.probe = netcp_probe,
	.हटाओ = netcp_हटाओ,
पूर्ण;
module_platक्रमm_driver(netcp_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI NETCP driver for Keystone SOCs");
MODULE_AUTHOR("Sandeep Nair <sandeep_n@ti.com");
