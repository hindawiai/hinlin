<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Transport Linux driver
 *
 * Contact Inक्रमmation:
 * Jon Mason <jon.mason@पूर्णांकel.com>
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश "linux/ntb.h"
#समावेश "linux/ntb_transport.h"

#घोषणा NTB_TRANSPORT_VERSION	4
#घोषणा NTB_TRANSPORT_VER	"4"
#घोषणा NTB_TRANSPORT_NAME	"ntb_transport"
#घोषणा NTB_TRANSPORT_DESC	"Software Queue-Pair Transport over NTB"
#घोषणा NTB_TRANSPORT_MIN_SPADS (MW0_SZ_HIGH + 2)

MODULE_DESCRIPTION(NTB_TRANSPORT_DESC);
MODULE_VERSION(NTB_TRANSPORT_VER);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel Corporation");

अटल अचिन्हित दीर्घ max_mw_size;
module_param(max_mw_size, uदीर्घ, 0644);
MODULE_PARM_DESC(max_mw_size, "Limit size of large memory windows");

अटल अचिन्हित पूर्णांक transport_mtu = 0x10000;
module_param(transport_mtu, uपूर्णांक, 0644);
MODULE_PARM_DESC(transport_mtu, "Maximum size of NTB transport packets");

अटल अचिन्हित अक्षर max_num_clients;
module_param(max_num_clients, byte, 0644);
MODULE_PARM_DESC(max_num_clients, "Maximum number of NTB transport clients");

अटल अचिन्हित पूर्णांक copy_bytes = 1024;
module_param(copy_bytes, uपूर्णांक, 0644);
MODULE_PARM_DESC(copy_bytes, "Threshold under which NTB will use the CPU to copy instead of DMA");

अटल bool use_dma;
module_param(use_dma, bool, 0644);
MODULE_PARM_DESC(use_dma, "Use DMA engine to perform large data copy");

अटल bool use_msi;
#अगर_घोषित CONFIG_NTB_MSI
module_param(use_msi, bool, 0644);
MODULE_PARM_DESC(use_msi, "Use MSI interrupts instead of doorbells");
#पूर्ण_अगर

अटल काष्ठा dentry *nt_debugfs_dir;

/* Only two-ports NTB devices are supported */
#घोषणा PIDX		NTB_DEF_PEER_IDX

काष्ठा ntb_queue_entry अणु
	/* ntb_queue list reference */
	काष्ठा list_head entry;
	/* poपूर्णांकers to data to be transferred */
	व्योम *cb_data;
	व्योम *buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक flags;
	पूर्णांक retries;
	पूर्णांक errors;
	अचिन्हित पूर्णांक tx_index;
	अचिन्हित पूर्णांक rx_index;

	काष्ठा ntb_transport_qp *qp;
	जोड़ अणु
		काष्ठा ntb_payload_header __iomem *tx_hdr;
		काष्ठा ntb_payload_header *rx_hdr;
	पूर्ण;
पूर्ण;

काष्ठा ntb_rx_info अणु
	अचिन्हित पूर्णांक entry;
पूर्ण;

काष्ठा ntb_transport_qp अणु
	काष्ठा ntb_transport_ctx *transport;
	काष्ठा ntb_dev *ndev;
	व्योम *cb_data;
	काष्ठा dma_chan *tx_dma_chan;
	काष्ठा dma_chan *rx_dma_chan;

	bool client_पढ़ोy;
	bool link_is_up;
	bool active;

	u8 qp_num;	/* Only 64 QP's are allowed.  0-63 */
	u64 qp_bit;

	काष्ठा ntb_rx_info __iomem *rx_info;
	काष्ठा ntb_rx_info *remote_rx_info;

	व्योम (*tx_handler)(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
			   व्योम *data, पूर्णांक len);
	काष्ठा list_head tx_मुक्त_q;
	spinlock_t ntb_tx_मुक्त_q_lock;
	व्योम __iomem *tx_mw;
	phys_addr_t tx_mw_phys;
	माप_प्रकार tx_mw_size;
	dma_addr_t tx_mw_dma_addr;
	अचिन्हित पूर्णांक tx_index;
	अचिन्हित पूर्णांक tx_max_entry;
	अचिन्हित पूर्णांक tx_max_frame;

	व्योम (*rx_handler)(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
			   व्योम *data, पूर्णांक len);
	काष्ठा list_head rx_post_q;
	काष्ठा list_head rx_pend_q;
	काष्ठा list_head rx_मुक्त_q;
	/* ntb_rx_q_lock: synchronize access to rx_XXXX_q */
	spinlock_t ntb_rx_q_lock;
	व्योम *rx_buff;
	अचिन्हित पूर्णांक rx_index;
	अचिन्हित पूर्णांक rx_max_entry;
	अचिन्हित पूर्णांक rx_max_frame;
	अचिन्हित पूर्णांक rx_alloc_entry;
	dma_cookie_t last_cookie;
	काष्ठा tasklet_काष्ठा rxc_db_work;

	व्योम (*event_handler)(व्योम *data, पूर्णांक status);
	काष्ठा delayed_work link_work;
	काष्ठा work_काष्ठा link_cleanup;

	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_stats;

	/* Stats */
	u64 rx_bytes;
	u64 rx_pkts;
	u64 rx_ring_empty;
	u64 rx_err_no_buf;
	u64 rx_err_oflow;
	u64 rx_err_ver;
	u64 rx_स_नकल;
	u64 rx_async;
	u64 tx_bytes;
	u64 tx_pkts;
	u64 tx_ring_full;
	u64 tx_err_no_buf;
	u64 tx_स_नकल;
	u64 tx_async;

	bool use_msi;
	पूर्णांक msi_irq;
	काष्ठा ntb_msi_desc msi_desc;
	काष्ठा ntb_msi_desc peer_msi_desc;
पूर्ण;

काष्ठा ntb_transport_mw अणु
	phys_addr_t phys_addr;
	resource_माप_प्रकार phys_size;
	व्योम __iomem *vbase;
	माप_प्रकार xlat_size;
	माप_प्रकार buff_size;
	माप_प्रकार alloc_size;
	व्योम *alloc_addr;
	व्योम *virt_addr;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा ntb_transport_client_dev अणु
	काष्ठा list_head entry;
	काष्ठा ntb_transport_ctx *nt;
	काष्ठा device dev;
पूर्ण;

काष्ठा ntb_transport_ctx अणु
	काष्ठा list_head entry;
	काष्ठा list_head client_devs;

	काष्ठा ntb_dev *ndev;

	काष्ठा ntb_transport_mw *mw_vec;
	काष्ठा ntb_transport_qp *qp_vec;
	अचिन्हित पूर्णांक mw_count;
	अचिन्हित पूर्णांक qp_count;
	u64 qp_biपंचांगap;
	u64 qp_biपंचांगap_मुक्त;

	bool use_msi;
	अचिन्हित पूर्णांक msi_spad_offset;
	u64 msi_db_mask;

	bool link_is_up;
	काष्ठा delayed_work link_work;
	काष्ठा work_काष्ठा link_cleanup;

	काष्ठा dentry *debugfs_node_dir;
पूर्ण;

क्रमागत अणु
	DESC_DONE_FLAG = BIT(0),
	LINK_DOWN_FLAG = BIT(1),
पूर्ण;

काष्ठा ntb_payload_header अणु
	अचिन्हित पूर्णांक ver;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक flags;
पूर्ण;

क्रमागत अणु
	VERSION = 0,
	QP_LINKS,
	NUM_QPS,
	NUM_MWS,
	MW0_SZ_HIGH,
	MW0_SZ_LOW,
पूर्ण;

#घोषणा dev_client_dev(__dev) \
	container_of((__dev), काष्ठा ntb_transport_client_dev, dev)

#घोषणा drv_client(__drv) \
	container_of((__drv), काष्ठा ntb_transport_client, driver)

#घोषणा QP_TO_MW(nt, qp)	((qp) % nt->mw_count)
#घोषणा NTB_QP_DEF_NUM_ENTRIES	100
#घोषणा NTB_LINK_DOWN_TIMEOUT	10

अटल व्योम ntb_transport_rxc_db(अचिन्हित दीर्घ data);
अटल स्थिर काष्ठा ntb_ctx_ops ntb_transport_ops;
अटल काष्ठा ntb_client ntb_transport_client;
अटल पूर्णांक ntb_async_tx_submit(काष्ठा ntb_transport_qp *qp,
			       काष्ठा ntb_queue_entry *entry);
अटल व्योम ntb_स_नकल_tx(काष्ठा ntb_queue_entry *entry, व्योम __iomem *offset);
अटल पूर्णांक ntb_async_rx_submit(काष्ठा ntb_queue_entry *entry, व्योम *offset);
अटल व्योम ntb_स_नकल_rx(काष्ठा ntb_queue_entry *entry, व्योम *offset);


अटल पूर्णांक ntb_transport_bus_match(काष्ठा device *dev,
				   काष्ठा device_driver *drv)
अणु
	वापस !म_भेदन(dev_name(dev), drv->name, म_माप(drv->name));
पूर्ण

अटल पूर्णांक ntb_transport_bus_probe(काष्ठा device *dev)
अणु
	स्थिर काष्ठा ntb_transport_client *client;
	पूर्णांक rc;

	get_device(dev);

	client = drv_client(dev->driver);
	rc = client->probe(dev);
	अगर (rc)
		put_device(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक ntb_transport_bus_हटाओ(काष्ठा device *dev)
अणु
	स्थिर काष्ठा ntb_transport_client *client;

	client = drv_client(dev->driver);
	client->हटाओ(dev);

	put_device(dev);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type ntb_transport_bus = अणु
	.name = "ntb_transport",
	.match = ntb_transport_bus_match,
	.probe = ntb_transport_bus_probe,
	.हटाओ = ntb_transport_bus_हटाओ,
पूर्ण;

अटल LIST_HEAD(ntb_transport_list);

अटल पूर्णांक ntb_bus_init(काष्ठा ntb_transport_ctx *nt)
अणु
	list_add_tail(&nt->entry, &ntb_transport_list);
	वापस 0;
पूर्ण

अटल व्योम ntb_bus_हटाओ(काष्ठा ntb_transport_ctx *nt)
अणु
	काष्ठा ntb_transport_client_dev *client_dev, *cd;

	list_क्रम_each_entry_safe(client_dev, cd, &nt->client_devs, entry) अणु
		dev_err(client_dev->dev.parent, "%s still attached to bus, removing\n",
			dev_name(&client_dev->dev));
		list_del(&client_dev->entry);
		device_unरेजिस्टर(&client_dev->dev);
	पूर्ण

	list_del(&nt->entry);
पूर्ण

अटल व्योम ntb_transport_client_release(काष्ठा device *dev)
अणु
	काष्ठा ntb_transport_client_dev *client_dev;

	client_dev = dev_client_dev(dev);
	kमुक्त(client_dev);
पूर्ण

/**
 * ntb_transport_unरेजिस्टर_client_dev - Unरेजिस्टर NTB client device
 * @device_name: Name of NTB client device
 *
 * Unरेजिस्टर an NTB client device with the NTB transport layer
 */
व्योम ntb_transport_unरेजिस्टर_client_dev(अक्षर *device_name)
अणु
	काष्ठा ntb_transport_client_dev *client, *cd;
	काष्ठा ntb_transport_ctx *nt;

	list_क्रम_each_entry(nt, &ntb_transport_list, entry)
		list_क्रम_each_entry_safe(client, cd, &nt->client_devs, entry)
			अगर (!म_भेदन(dev_name(&client->dev), device_name,
				     म_माप(device_name))) अणु
				list_del(&client->entry);
				device_unरेजिस्टर(&client->dev);
			पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_unरेजिस्टर_client_dev);

/**
 * ntb_transport_रेजिस्टर_client_dev - Register NTB client device
 * @device_name: Name of NTB client device
 *
 * Register an NTB client device with the NTB transport layer
 */
पूर्णांक ntb_transport_रेजिस्टर_client_dev(अक्षर *device_name)
अणु
	काष्ठा ntb_transport_client_dev *client_dev;
	काष्ठा ntb_transport_ctx *nt;
	पूर्णांक node;
	पूर्णांक rc, i = 0;

	अगर (list_empty(&ntb_transport_list))
		वापस -ENODEV;

	list_क्रम_each_entry(nt, &ntb_transport_list, entry) अणु
		काष्ठा device *dev;

		node = dev_to_node(&nt->ndev->dev);

		client_dev = kzalloc_node(माप(*client_dev),
					  GFP_KERNEL, node);
		अगर (!client_dev) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		dev = &client_dev->dev;

		/* setup and रेजिस्टर client devices */
		dev_set_name(dev, "%s%d", device_name, i);
		dev->bus = &ntb_transport_bus;
		dev->release = ntb_transport_client_release;
		dev->parent = &nt->ndev->dev;

		rc = device_रेजिस्टर(dev);
		अगर (rc) अणु
			kमुक्त(client_dev);
			जाओ err;
		पूर्ण

		list_add_tail(&client_dev->entry, &nt->client_devs);
		i++;
	पूर्ण

	वापस 0;

err:
	ntb_transport_unरेजिस्टर_client_dev(device_name);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_रेजिस्टर_client_dev);

/**
 * ntb_transport_रेजिस्टर_client - Register NTB client driver
 * @drv: NTB client driver to be रेजिस्टरed
 *
 * Register an NTB client driver with the NTB transport layer
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक ntb_transport_रेजिस्टर_client(काष्ठा ntb_transport_client *drv)
अणु
	drv->driver.bus = &ntb_transport_bus;

	अगर (list_empty(&ntb_transport_list))
		वापस -ENODEV;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_रेजिस्टर_client);

/**
 * ntb_transport_unरेजिस्टर_client - Unरेजिस्टर NTB client driver
 * @drv: NTB client driver to be unरेजिस्टरed
 *
 * Unरेजिस्टर an NTB client driver with the NTB transport layer
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
व्योम ntb_transport_unरेजिस्टर_client(काष्ठा ntb_transport_client *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_unरेजिस्टर_client);

अटल sमाप_प्रकार debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार count,
			    loff_t *offp)
अणु
	काष्ठा ntb_transport_qp *qp;
	अक्षर *buf;
	sमाप_प्रकार ret, out_offset, out_count;

	qp = filp->निजी_data;

	अगर (!qp || !qp->link_is_up)
		वापस 0;

	out_count = 1000;

	buf = kदो_स्मृति(out_count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	out_offset = 0;
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "\nNTB QP stats:\n\n");
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_bytes - \t%llu\n", qp->rx_bytes);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_pkts - \t%llu\n", qp->rx_pkts);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_memcpy - \t%llu\n", qp->rx_स_नकल);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_async - \t%llu\n", qp->rx_async);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_ring_empty - %llu\n", qp->rx_ring_empty);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_err_no_buf - %llu\n", qp->rx_err_no_buf);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_err_oflow - \t%llu\n", qp->rx_err_oflow);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_err_ver - \t%llu\n", qp->rx_err_ver);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_buff - \t0x%p\n", qp->rx_buff);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_index - \t%u\n", qp->rx_index);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_max_entry - \t%u\n", qp->rx_max_entry);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "rx_alloc_entry - \t%u\n\n", qp->rx_alloc_entry);

	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_bytes - \t%llu\n", qp->tx_bytes);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_pkts - \t%llu\n", qp->tx_pkts);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_memcpy - \t%llu\n", qp->tx_स_नकल);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_async - \t%llu\n", qp->tx_async);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_ring_full - \t%llu\n", qp->tx_ring_full);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_err_no_buf - %llu\n", qp->tx_err_no_buf);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_mw - \t0x%p\n", qp->tx_mw);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_index (H) - \t%u\n", qp->tx_index);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "RRI (T) - \t%u\n",
			       qp->remote_rx_info->entry);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "tx_max_entry - \t%u\n", qp->tx_max_entry);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "free tx - \t%u\n",
			       ntb_transport_tx_मुक्त_entry(qp));

	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "\n");
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Using TX DMA - \t%s\n",
			       qp->tx_dma_chan ? "Yes" : "No");
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Using RX DMA - \t%s\n",
			       qp->rx_dma_chan ? "Yes" : "No");
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "QP Link - \t%s\n",
			       qp->link_is_up ? "Up" : "Down");
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "\n");

	अगर (out_offset > out_count)
		out_offset = out_count;

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, out_offset);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations ntb_qp_debugfs_stats = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = debugfs_पढ़ो,
पूर्ण;

अटल व्योम ntb_list_add(spinlock_t *lock, काष्ठा list_head *entry,
			 काष्ठा list_head *list)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	list_add_tail(entry, list);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल काष्ठा ntb_queue_entry *ntb_list_rm(spinlock_t *lock,
					   काष्ठा list_head *list)
अणु
	काष्ठा ntb_queue_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	अगर (list_empty(list)) अणु
		entry = शून्य;
		जाओ out;
	पूर्ण
	entry = list_first_entry(list, काष्ठा ntb_queue_entry, entry);
	list_del(&entry->entry);

out:
	spin_unlock_irqrestore(lock, flags);

	वापस entry;
पूर्ण

अटल काष्ठा ntb_queue_entry *ntb_list_mv(spinlock_t *lock,
					   काष्ठा list_head *list,
					   काष्ठा list_head *to_list)
अणु
	काष्ठा ntb_queue_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);

	अगर (list_empty(list)) अणु
		entry = शून्य;
	पूर्ण अन्यथा अणु
		entry = list_first_entry(list, काष्ठा ntb_queue_entry, entry);
		list_move_tail(&entry->entry, to_list);
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	वापस entry;
पूर्ण

अटल पूर्णांक ntb_transport_setup_qp_mw(काष्ठा ntb_transport_ctx *nt,
				     अचिन्हित पूर्णांक qp_num)
अणु
	काष्ठा ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	काष्ठा ntb_transport_mw *mw;
	काष्ठा ntb_dev *ndev = nt->ndev;
	काष्ठा ntb_queue_entry *entry;
	अचिन्हित पूर्णांक rx_size, num_qps_mw;
	अचिन्हित पूर्णांक mw_num, mw_count, qp_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक node;

	mw_count = nt->mw_count;
	qp_count = nt->qp_count;

	mw_num = QP_TO_MW(nt, qp_num);
	mw = &nt->mw_vec[mw_num];

	अगर (!mw->virt_addr)
		वापस -ENOMEM;

	अगर (mw_num < qp_count % mw_count)
		num_qps_mw = qp_count / mw_count + 1;
	अन्यथा
		num_qps_mw = qp_count / mw_count;

	rx_size = (अचिन्हित पूर्णांक)mw->xlat_size / num_qps_mw;
	qp->rx_buff = mw->virt_addr + rx_size * (qp_num / mw_count);
	rx_size -= माप(काष्ठा ntb_rx_info);

	qp->remote_rx_info = qp->rx_buff + rx_size;

	/* Due to housekeeping, there must be atleast 2 buffs */
	qp->rx_max_frame = min(transport_mtu, rx_size / 2);
	qp->rx_max_entry = rx_size / qp->rx_max_frame;
	qp->rx_index = 0;

	/*
	 * Checking to see अगर we have more entries than the शेष.
	 * We should add additional entries अगर that is the हाल so we
	 * can be in sync with the transport frames.
	 */
	node = dev_to_node(&ndev->dev);
	क्रम (i = qp->rx_alloc_entry; i < qp->rx_max_entry; i++) अणु
		entry = kzalloc_node(माप(*entry), GFP_KERNEL, node);
		अगर (!entry)
			वापस -ENOMEM;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry,
			     &qp->rx_मुक्त_q);
		qp->rx_alloc_entry++;
	पूर्ण

	qp->remote_rx_info->entry = qp->rx_max_entry - 1;

	/* setup the hdr offsets with 0's */
	क्रम (i = 0; i < qp->rx_max_entry; i++) अणु
		व्योम *offset = (qp->rx_buff + qp->rx_max_frame * (i + 1) -
				माप(काष्ठा ntb_payload_header));
		स_रखो(offset, 0, माप(काष्ठा ntb_payload_header));
	पूर्ण

	qp->rx_pkts = 0;
	qp->tx_pkts = 0;
	qp->tx_index = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t ntb_transport_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ntb_transport_qp *qp = dev;

	tasklet_schedule(&qp->rxc_db_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ntb_transport_setup_qp_peer_msi(काष्ठा ntb_transport_ctx *nt,
					    अचिन्हित पूर्णांक qp_num)
अणु
	काष्ठा ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	पूर्णांक spad = qp_num * 2 + nt->msi_spad_offset;

	अगर (!nt->use_msi)
		वापस;

	अगर (spad >= ntb_spad_count(nt->ndev))
		वापस;

	qp->peer_msi_desc.addr_offset =
		ntb_peer_spad_पढ़ो(qp->ndev, PIDX, spad);
	qp->peer_msi_desc.data =
		ntb_peer_spad_पढ़ो(qp->ndev, PIDX, spad + 1);

	dev_dbg(&qp->ndev->pdev->dev, "QP%d Peer MSI addr=%x data=%x\n",
		qp_num, qp->peer_msi_desc.addr_offset, qp->peer_msi_desc.data);

	अगर (qp->peer_msi_desc.addr_offset) अणु
		qp->use_msi = true;
		dev_info(&qp->ndev->pdev->dev,
			 "Using MSI interrupts for QP%d\n", qp_num);
	पूर्ण
पूर्ण

अटल व्योम ntb_transport_setup_qp_msi(काष्ठा ntb_transport_ctx *nt,
				       अचिन्हित पूर्णांक qp_num)
अणु
	काष्ठा ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	पूर्णांक spad = qp_num * 2 + nt->msi_spad_offset;
	पूर्णांक rc;

	अगर (!nt->use_msi)
		वापस;

	अगर (spad >= ntb_spad_count(nt->ndev)) अणु
		dev_warn_once(&qp->ndev->pdev->dev,
			      "Not enough SPADS to use MSI interrupts\n");
		वापस;
	पूर्ण

	ntb_spad_ग_लिखो(qp->ndev, spad, 0);
	ntb_spad_ग_लिखो(qp->ndev, spad + 1, 0);

	अगर (!qp->msi_irq) अणु
		qp->msi_irq = ntbm_msi_request_irq(qp->ndev, ntb_transport_isr,
						   KBUILD_MODNAME, qp,
						   &qp->msi_desc);
		अगर (qp->msi_irq < 0) अणु
			dev_warn(&qp->ndev->pdev->dev,
				 "Unable to allocate MSI interrupt for qp%d\n",
				 qp_num);
			वापस;
		पूर्ण
	पूर्ण

	rc = ntb_spad_ग_लिखो(qp->ndev, spad, qp->msi_desc.addr_offset);
	अगर (rc)
		जाओ err_मुक्त_पूर्णांकerrupt;

	rc = ntb_spad_ग_लिखो(qp->ndev, spad + 1, qp->msi_desc.data);
	अगर (rc)
		जाओ err_मुक्त_पूर्णांकerrupt;

	dev_dbg(&qp->ndev->pdev->dev, "QP%d MSI %d addr=%x data=%x\n",
		qp_num, qp->msi_irq, qp->msi_desc.addr_offset,
		qp->msi_desc.data);

	वापस;

err_मुक्त_पूर्णांकerrupt:
	devm_मुक्त_irq(&nt->ndev->dev, qp->msi_irq, qp);
पूर्ण

अटल व्योम ntb_transport_msi_peer_desc_changed(काष्ठा ntb_transport_ctx *nt)
अणु
	पूर्णांक i;

	dev_dbg(&nt->ndev->pdev->dev, "Peer MSI descriptors changed");

	क्रम (i = 0; i < nt->qp_count; i++)
		ntb_transport_setup_qp_peer_msi(nt, i);
पूर्ण

अटल व्योम ntb_transport_msi_desc_changed(व्योम *data)
अणु
	काष्ठा ntb_transport_ctx *nt = data;
	पूर्णांक i;

	dev_dbg(&nt->ndev->pdev->dev, "MSI descriptors changed");

	क्रम (i = 0; i < nt->qp_count; i++)
		ntb_transport_setup_qp_msi(nt, i);

	ntb_peer_db_set(nt->ndev, nt->msi_db_mask);
पूर्ण

अटल व्योम ntb_मुक्त_mw(काष्ठा ntb_transport_ctx *nt, पूर्णांक num_mw)
अणु
	काष्ठा ntb_transport_mw *mw = &nt->mw_vec[num_mw];
	काष्ठा pci_dev *pdev = nt->ndev->pdev;

	अगर (!mw->virt_addr)
		वापस;

	ntb_mw_clear_trans(nt->ndev, PIDX, num_mw);
	dma_मुक्त_coherent(&pdev->dev, mw->alloc_size,
			  mw->alloc_addr, mw->dma_addr);
	mw->xlat_size = 0;
	mw->buff_size = 0;
	mw->alloc_size = 0;
	mw->alloc_addr = शून्य;
	mw->virt_addr = शून्य;
पूर्ण

अटल पूर्णांक ntb_alloc_mw_buffer(काष्ठा ntb_transport_mw *mw,
			       काष्ठा device *dma_dev, माप_प्रकार align)
अणु
	dma_addr_t dma_addr;
	व्योम *alloc_addr, *virt_addr;
	पूर्णांक rc;

	alloc_addr = dma_alloc_coherent(dma_dev, mw->alloc_size,
					&dma_addr, GFP_KERNEL);
	अगर (!alloc_addr) अणु
		dev_err(dma_dev, "Unable to alloc MW buff of size %zu\n",
			mw->alloc_size);
		वापस -ENOMEM;
	पूर्ण
	virt_addr = alloc_addr;

	/*
	 * we must ensure that the memory address allocated is BAR size
	 * aligned in order क्रम the XLAT रेजिस्टर to take the value. This
	 * is a requirement of the hardware. It is recommended to setup CMA
	 * क्रम BAR sizes equal or greater than 4MB.
	 */
	अगर (!IS_ALIGNED(dma_addr, align)) अणु
		अगर (mw->alloc_size > mw->buff_size) अणु
			virt_addr = PTR_ALIGN(alloc_addr, align);
			dma_addr = ALIGN(dma_addr, align);
		पूर्ण अन्यथा अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	mw->alloc_addr = alloc_addr;
	mw->virt_addr = virt_addr;
	mw->dma_addr = dma_addr;

	वापस 0;

err:
	dma_मुक्त_coherent(dma_dev, mw->alloc_size, alloc_addr, dma_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक ntb_set_mw(काष्ठा ntb_transport_ctx *nt, पूर्णांक num_mw,
		      resource_माप_प्रकार size)
अणु
	काष्ठा ntb_transport_mw *mw = &nt->mw_vec[num_mw];
	काष्ठा pci_dev *pdev = nt->ndev->pdev;
	माप_प्रकार xlat_size, buff_size;
	resource_माप_प्रकार xlat_align;
	resource_माप_प्रकार xlat_align_size;
	पूर्णांक rc;

	अगर (!size)
		वापस -EINVAL;

	rc = ntb_mw_get_align(nt->ndev, PIDX, num_mw, &xlat_align,
			      &xlat_align_size, शून्य);
	अगर (rc)
		वापस rc;

	xlat_size = round_up(size, xlat_align_size);
	buff_size = round_up(size, xlat_align);

	/* No need to re-setup */
	अगर (mw->xlat_size == xlat_size)
		वापस 0;

	अगर (mw->buff_size)
		ntb_मुक्त_mw(nt, num_mw);

	/* Alloc memory क्रम receiving data.  Must be aligned */
	mw->xlat_size = xlat_size;
	mw->buff_size = buff_size;
	mw->alloc_size = buff_size;

	rc = ntb_alloc_mw_buffer(mw, &pdev->dev, xlat_align);
	अगर (rc) अणु
		mw->alloc_size *= 2;
		rc = ntb_alloc_mw_buffer(mw, &pdev->dev, xlat_align);
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"Unable to alloc aligned MW buff\n");
			mw->xlat_size = 0;
			mw->buff_size = 0;
			mw->alloc_size = 0;
			वापस rc;
		पूर्ण
	पूर्ण

	/* Notअगरy HW the memory location of the receive buffer */
	rc = ntb_mw_set_trans(nt->ndev, PIDX, num_mw, mw->dma_addr,
			      mw->xlat_size);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Unable to set mw%d translation", num_mw);
		ntb_मुक्त_mw(nt, num_mw);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ntb_qp_link_करोwn_reset(काष्ठा ntb_transport_qp *qp)
अणु
	qp->link_is_up = false;
	qp->active = false;

	qp->tx_index = 0;
	qp->rx_index = 0;
	qp->rx_bytes = 0;
	qp->rx_pkts = 0;
	qp->rx_ring_empty = 0;
	qp->rx_err_no_buf = 0;
	qp->rx_err_oflow = 0;
	qp->rx_err_ver = 0;
	qp->rx_स_नकल = 0;
	qp->rx_async = 0;
	qp->tx_bytes = 0;
	qp->tx_pkts = 0;
	qp->tx_ring_full = 0;
	qp->tx_err_no_buf = 0;
	qp->tx_स_नकल = 0;
	qp->tx_async = 0;
पूर्ण

अटल व्योम ntb_qp_link_cleanup(काष्ठा ntb_transport_qp *qp)
अणु
	काष्ठा ntb_transport_ctx *nt = qp->transport;
	काष्ठा pci_dev *pdev = nt->ndev->pdev;

	dev_info(&pdev->dev, "qp %d: Link Cleanup\n", qp->qp_num);

	cancel_delayed_work_sync(&qp->link_work);
	ntb_qp_link_करोwn_reset(qp);

	अगर (qp->event_handler)
		qp->event_handler(qp->cb_data, qp->link_is_up);
पूर्ण

अटल व्योम ntb_qp_link_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ntb_transport_qp *qp = container_of(work,
						   काष्ठा ntb_transport_qp,
						   link_cleanup);
	काष्ठा ntb_transport_ctx *nt = qp->transport;

	ntb_qp_link_cleanup(qp);

	अगर (nt->link_is_up)
		schedule_delayed_work(&qp->link_work,
				      msecs_to_jअगरfies(NTB_LINK_DOWN_TIMEOUT));
पूर्ण

अटल व्योम ntb_qp_link_करोwn(काष्ठा ntb_transport_qp *qp)
अणु
	schedule_work(&qp->link_cleanup);
पूर्ण

अटल व्योम ntb_transport_link_cleanup(काष्ठा ntb_transport_ctx *nt)
अणु
	काष्ठा ntb_transport_qp *qp;
	u64 qp_biपंचांगap_alloc;
	अचिन्हित पूर्णांक i, count;

	qp_biपंचांगap_alloc = nt->qp_biपंचांगap & ~nt->qp_biपंचांगap_मुक्त;

	/* Pass aदीर्घ the info to any clients */
	क्रम (i = 0; i < nt->qp_count; i++)
		अगर (qp_biपंचांगap_alloc & BIT_ULL(i)) अणु
			qp = &nt->qp_vec[i];
			ntb_qp_link_cleanup(qp);
			cancel_work_sync(&qp->link_cleanup);
			cancel_delayed_work_sync(&qp->link_work);
		पूर्ण

	अगर (!nt->link_is_up)
		cancel_delayed_work_sync(&nt->link_work);

	क्रम (i = 0; i < nt->mw_count; i++)
		ntb_मुक्त_mw(nt, i);

	/* The scratchpad रेजिस्टरs keep the values अगर the remote side
	 * goes करोwn, blast them now to give them a sane value the next
	 * समय they are accessed
	 */
	count = ntb_spad_count(nt->ndev);
	क्रम (i = 0; i < count; i++)
		ntb_spad_ग_लिखो(nt->ndev, i, 0);
पूर्ण

अटल व्योम ntb_transport_link_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ntb_transport_ctx *nt =
		container_of(work, काष्ठा ntb_transport_ctx, link_cleanup);

	ntb_transport_link_cleanup(nt);
पूर्ण

अटल व्योम ntb_transport_event_callback(व्योम *data)
अणु
	काष्ठा ntb_transport_ctx *nt = data;

	अगर (ntb_link_is_up(nt->ndev, शून्य, शून्य) == 1)
		schedule_delayed_work(&nt->link_work, 0);
	अन्यथा
		schedule_work(&nt->link_cleanup);
पूर्ण

अटल व्योम ntb_transport_link_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ntb_transport_ctx *nt =
		container_of(work, काष्ठा ntb_transport_ctx, link_work.work);
	काष्ठा ntb_dev *ndev = nt->ndev;
	काष्ठा pci_dev *pdev = ndev->pdev;
	resource_माप_प्रकार size;
	u32 val;
	पूर्णांक rc = 0, i, spad;

	/* send the local info, in the opposite order of the way we पढ़ो it */

	अगर (nt->use_msi) अणु
		rc = ntb_msi_setup_mws(ndev);
		अगर (rc) अणु
			dev_warn(&pdev->dev,
				 "Failed to register MSI memory window: %d\n",
				 rc);
			nt->use_msi = false;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nt->qp_count; i++)
		ntb_transport_setup_qp_msi(nt, i);

	क्रम (i = 0; i < nt->mw_count; i++) अणु
		size = nt->mw_vec[i].phys_size;

		अगर (max_mw_size && size > max_mw_size)
			size = max_mw_size;

		spad = MW0_SZ_HIGH + (i * 2);
		ntb_peer_spad_ग_लिखो(ndev, PIDX, spad, upper_32_bits(size));

		spad = MW0_SZ_LOW + (i * 2);
		ntb_peer_spad_ग_लिखो(ndev, PIDX, spad, lower_32_bits(size));
	पूर्ण

	ntb_peer_spad_ग_लिखो(ndev, PIDX, NUM_MWS, nt->mw_count);

	ntb_peer_spad_ग_लिखो(ndev, PIDX, NUM_QPS, nt->qp_count);

	ntb_peer_spad_ग_लिखो(ndev, PIDX, VERSION, NTB_TRANSPORT_VERSION);

	/* Query the remote side क्रम its info */
	val = ntb_spad_पढ़ो(ndev, VERSION);
	dev_dbg(&pdev->dev, "Remote version = %d\n", val);
	अगर (val != NTB_TRANSPORT_VERSION)
		जाओ out;

	val = ntb_spad_पढ़ो(ndev, NUM_QPS);
	dev_dbg(&pdev->dev, "Remote max number of qps = %d\n", val);
	अगर (val != nt->qp_count)
		जाओ out;

	val = ntb_spad_पढ़ो(ndev, NUM_MWS);
	dev_dbg(&pdev->dev, "Remote number of mws = %d\n", val);
	अगर (val != nt->mw_count)
		जाओ out;

	क्रम (i = 0; i < nt->mw_count; i++) अणु
		u64 val64;

		val = ntb_spad_पढ़ो(ndev, MW0_SZ_HIGH + (i * 2));
		val64 = (u64)val << 32;

		val = ntb_spad_पढ़ो(ndev, MW0_SZ_LOW + (i * 2));
		val64 |= val;

		dev_dbg(&pdev->dev, "Remote MW%d size = %#llx\n", i, val64);

		rc = ntb_set_mw(nt, i, val64);
		अगर (rc)
			जाओ out1;
	पूर्ण

	nt->link_is_up = true;

	क्रम (i = 0; i < nt->qp_count; i++) अणु
		काष्ठा ntb_transport_qp *qp = &nt->qp_vec[i];

		ntb_transport_setup_qp_mw(nt, i);
		ntb_transport_setup_qp_peer_msi(nt, i);

		अगर (qp->client_पढ़ोy)
			schedule_delayed_work(&qp->link_work, 0);
	पूर्ण

	वापस;

out1:
	क्रम (i = 0; i < nt->mw_count; i++)
		ntb_मुक्त_mw(nt, i);

	/* अगर there's an actual failure, we should just bail */
	अगर (rc < 0)
		वापस;

out:
	अगर (ntb_link_is_up(ndev, शून्य, शून्य) == 1)
		schedule_delayed_work(&nt->link_work,
				      msecs_to_jअगरfies(NTB_LINK_DOWN_TIMEOUT));
पूर्ण

अटल व्योम ntb_qp_link_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ntb_transport_qp *qp = container_of(work,
						   काष्ठा ntb_transport_qp,
						   link_work.work);
	काष्ठा pci_dev *pdev = qp->ndev->pdev;
	काष्ठा ntb_transport_ctx *nt = qp->transport;
	पूर्णांक val;

	WARN_ON(!nt->link_is_up);

	val = ntb_spad_पढ़ो(nt->ndev, QP_LINKS);

	ntb_peer_spad_ग_लिखो(nt->ndev, PIDX, QP_LINKS, val | BIT(qp->qp_num));

	/* query remote spad क्रम qp पढ़ोy bits */
	dev_dbg_ratelimited(&pdev->dev, "Remote QP link status = %x\n", val);

	/* See अगर the remote side is up */
	अगर (val & BIT(qp->qp_num)) अणु
		dev_info(&pdev->dev, "qp %d: Link Up\n", qp->qp_num);
		qp->link_is_up = true;
		qp->active = true;

		अगर (qp->event_handler)
			qp->event_handler(qp->cb_data, qp->link_is_up);

		अगर (qp->active)
			tasklet_schedule(&qp->rxc_db_work);
	पूर्ण अन्यथा अगर (nt->link_is_up)
		schedule_delayed_work(&qp->link_work,
				      msecs_to_jअगरfies(NTB_LINK_DOWN_TIMEOUT));
पूर्ण

अटल पूर्णांक ntb_transport_init_queue(काष्ठा ntb_transport_ctx *nt,
				    अचिन्हित पूर्णांक qp_num)
अणु
	काष्ठा ntb_transport_qp *qp;
	phys_addr_t mw_base;
	resource_माप_प्रकार mw_size;
	अचिन्हित पूर्णांक num_qps_mw, tx_size;
	अचिन्हित पूर्णांक mw_num, mw_count, qp_count;
	u64 qp_offset;

	mw_count = nt->mw_count;
	qp_count = nt->qp_count;

	mw_num = QP_TO_MW(nt, qp_num);

	qp = &nt->qp_vec[qp_num];
	qp->qp_num = qp_num;
	qp->transport = nt;
	qp->ndev = nt->ndev;
	qp->client_पढ़ोy = false;
	qp->event_handler = शून्य;
	ntb_qp_link_करोwn_reset(qp);

	अगर (mw_num < qp_count % mw_count)
		num_qps_mw = qp_count / mw_count + 1;
	अन्यथा
		num_qps_mw = qp_count / mw_count;

	mw_base = nt->mw_vec[mw_num].phys_addr;
	mw_size = nt->mw_vec[mw_num].phys_size;

	अगर (max_mw_size && mw_size > max_mw_size)
		mw_size = max_mw_size;

	tx_size = (अचिन्हित पूर्णांक)mw_size / num_qps_mw;
	qp_offset = tx_size * (qp_num / mw_count);

	qp->tx_mw_size = tx_size;
	qp->tx_mw = nt->mw_vec[mw_num].vbase + qp_offset;
	अगर (!qp->tx_mw)
		वापस -EINVAL;

	qp->tx_mw_phys = mw_base + qp_offset;
	अगर (!qp->tx_mw_phys)
		वापस -EINVAL;

	tx_size -= माप(काष्ठा ntb_rx_info);
	qp->rx_info = qp->tx_mw + tx_size;

	/* Due to housekeeping, there must be atleast 2 buffs */
	qp->tx_max_frame = min(transport_mtu, tx_size / 2);
	qp->tx_max_entry = tx_size / qp->tx_max_frame;

	अगर (nt->debugfs_node_dir) अणु
		अक्षर debugfs_name[4];

		snम_लिखो(debugfs_name, 4, "qp%d", qp_num);
		qp->debugfs_dir = debugfs_create_dir(debugfs_name,
						     nt->debugfs_node_dir);

		qp->debugfs_stats = debugfs_create_file("stats", S_IRUSR,
							qp->debugfs_dir, qp,
							&ntb_qp_debugfs_stats);
	पूर्ण अन्यथा अणु
		qp->debugfs_dir = शून्य;
		qp->debugfs_stats = शून्य;
	पूर्ण

	INIT_DELAYED_WORK(&qp->link_work, ntb_qp_link_work);
	INIT_WORK(&qp->link_cleanup, ntb_qp_link_cleanup_work);

	spin_lock_init(&qp->ntb_rx_q_lock);
	spin_lock_init(&qp->ntb_tx_मुक्त_q_lock);

	INIT_LIST_HEAD(&qp->rx_post_q);
	INIT_LIST_HEAD(&qp->rx_pend_q);
	INIT_LIST_HEAD(&qp->rx_मुक्त_q);
	INIT_LIST_HEAD(&qp->tx_मुक्त_q);

	tasklet_init(&qp->rxc_db_work, ntb_transport_rxc_db,
		     (अचिन्हित दीर्घ)qp);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_transport_probe(काष्ठा ntb_client *self, काष्ठा ntb_dev *ndev)
अणु
	काष्ठा ntb_transport_ctx *nt;
	काष्ठा ntb_transport_mw *mw;
	अचिन्हित पूर्णांक mw_count, qp_count, spad_count, max_mw_count_क्रम_spads;
	u64 qp_biपंचांगap;
	पूर्णांक node;
	पूर्णांक rc, i;

	mw_count = ntb_peer_mw_count(ndev);

	अगर (!ndev->ops->mw_set_trans) अणु
		dev_err(&ndev->dev, "Inbound MW based NTB API is required\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ntb_db_is_unsafe(ndev))
		dev_dbg(&ndev->dev,
			"doorbell is unsafe, proceed anyway...\n");
	अगर (ntb_spad_is_unsafe(ndev))
		dev_dbg(&ndev->dev,
			"scratchpad is unsafe, proceed anyway...\n");

	अगर (ntb_peer_port_count(ndev) != NTB_DEF_PEER_CNT)
		dev_warn(&ndev->dev, "Multi-port NTB devices unsupported\n");

	node = dev_to_node(&ndev->dev);

	nt = kzalloc_node(माप(*nt), GFP_KERNEL, node);
	अगर (!nt)
		वापस -ENOMEM;

	nt->ndev = ndev;

	/*
	 * If we are using MSI, and have at least one extra memory winकरोw,
	 * we will reserve the last MW क्रम the MSI winकरोw.
	 */
	अगर (use_msi && mw_count > 1) अणु
		rc = ntb_msi_init(ndev, ntb_transport_msi_desc_changed);
		अगर (!rc) अणु
			mw_count -= 1;
			nt->use_msi = true;
		पूर्ण
	पूर्ण

	spad_count = ntb_spad_count(ndev);

	/* Limit the MW's based on the availability of scratchpads */

	अगर (spad_count < NTB_TRANSPORT_MIN_SPADS) अणु
		nt->mw_count = 0;
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	max_mw_count_क्रम_spads = (spad_count - MW0_SZ_HIGH) / 2;
	nt->mw_count = min(mw_count, max_mw_count_क्रम_spads);

	nt->msi_spad_offset = nt->mw_count * 2 + MW0_SZ_HIGH;

	nt->mw_vec = kसुस्मृति_node(mw_count, माप(*nt->mw_vec),
				  GFP_KERNEL, node);
	अगर (!nt->mw_vec) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < mw_count; i++) अणु
		mw = &nt->mw_vec[i];

		rc = ntb_peer_mw_get_addr(ndev, i, &mw->phys_addr,
					  &mw->phys_size);
		अगर (rc)
			जाओ err1;

		mw->vbase = ioremap_wc(mw->phys_addr, mw->phys_size);
		अगर (!mw->vbase) अणु
			rc = -ENOMEM;
			जाओ err1;
		पूर्ण

		mw->buff_size = 0;
		mw->xlat_size = 0;
		mw->virt_addr = शून्य;
		mw->dma_addr = 0;
	पूर्ण

	qp_biपंचांगap = ntb_db_valid_mask(ndev);

	qp_count = ilog2(qp_biपंचांगap);
	अगर (nt->use_msi) अणु
		qp_count -= 1;
		nt->msi_db_mask = 1 << qp_count;
		ntb_db_clear_mask(ndev, nt->msi_db_mask);
	पूर्ण

	अगर (max_num_clients && max_num_clients < qp_count)
		qp_count = max_num_clients;
	अन्यथा अगर (nt->mw_count < qp_count)
		qp_count = nt->mw_count;

	qp_biपंचांगap &= BIT_ULL(qp_count) - 1;

	nt->qp_count = qp_count;
	nt->qp_biपंचांगap = qp_biपंचांगap;
	nt->qp_biपंचांगap_मुक्त = qp_biपंचांगap;

	nt->qp_vec = kसुस्मृति_node(qp_count, माप(*nt->qp_vec),
				  GFP_KERNEL, node);
	अगर (!nt->qp_vec) अणु
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (nt_debugfs_dir) अणु
		nt->debugfs_node_dir =
			debugfs_create_dir(pci_name(ndev->pdev),
					   nt_debugfs_dir);
	पूर्ण

	क्रम (i = 0; i < qp_count; i++) अणु
		rc = ntb_transport_init_queue(nt, i);
		अगर (rc)
			जाओ err2;
	पूर्ण

	INIT_DELAYED_WORK(&nt->link_work, ntb_transport_link_work);
	INIT_WORK(&nt->link_cleanup, ntb_transport_link_cleanup_work);

	rc = ntb_set_ctx(ndev, nt, &ntb_transport_ops);
	अगर (rc)
		जाओ err2;

	INIT_LIST_HEAD(&nt->client_devs);
	rc = ntb_bus_init(nt);
	अगर (rc)
		जाओ err3;

	nt->link_is_up = false;
	ntb_link_enable(ndev, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	ntb_link_event(ndev);

	वापस 0;

err3:
	ntb_clear_ctx(ndev);
err2:
	kमुक्त(nt->qp_vec);
err1:
	जबतक (i--) अणु
		mw = &nt->mw_vec[i];
		iounmap(mw->vbase);
	पूर्ण
	kमुक्त(nt->mw_vec);
err:
	kमुक्त(nt);
	वापस rc;
पूर्ण

अटल व्योम ntb_transport_मुक्त(काष्ठा ntb_client *self, काष्ठा ntb_dev *ndev)
अणु
	काष्ठा ntb_transport_ctx *nt = ndev->ctx;
	काष्ठा ntb_transport_qp *qp;
	u64 qp_biपंचांगap_alloc;
	पूर्णांक i;

	ntb_transport_link_cleanup(nt);
	cancel_work_sync(&nt->link_cleanup);
	cancel_delayed_work_sync(&nt->link_work);

	qp_biपंचांगap_alloc = nt->qp_biपंचांगap & ~nt->qp_biपंचांगap_मुक्त;

	/* verअगरy that all the qp's are मुक्तd */
	क्रम (i = 0; i < nt->qp_count; i++) अणु
		qp = &nt->qp_vec[i];
		अगर (qp_biपंचांगap_alloc & BIT_ULL(i))
			ntb_transport_मुक्त_queue(qp);
		debugfs_हटाओ_recursive(qp->debugfs_dir);
	पूर्ण

	ntb_link_disable(ndev);
	ntb_clear_ctx(ndev);

	ntb_bus_हटाओ(nt);

	क्रम (i = nt->mw_count; i--; ) अणु
		ntb_मुक्त_mw(nt, i);
		iounmap(nt->mw_vec[i].vbase);
	पूर्ण

	kमुक्त(nt->qp_vec);
	kमुक्त(nt->mw_vec);
	kमुक्त(nt);
पूर्ण

अटल व्योम ntb_complete_rxc(काष्ठा ntb_transport_qp *qp)
अणु
	काष्ठा ntb_queue_entry *entry;
	व्योम *cb_data;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&qp->ntb_rx_q_lock, irqflags);

	जबतक (!list_empty(&qp->rx_post_q)) अणु
		entry = list_first_entry(&qp->rx_post_q,
					 काष्ठा ntb_queue_entry, entry);
		अगर (!(entry->flags & DESC_DONE_FLAG))
			अवरोध;

		entry->rx_hdr->flags = 0;
		ioग_लिखो32(entry->rx_index, &qp->rx_info->entry);

		cb_data = entry->cb_data;
		len = entry->len;

		list_move_tail(&entry->entry, &qp->rx_मुक्त_q);

		spin_unlock_irqrestore(&qp->ntb_rx_q_lock, irqflags);

		अगर (qp->rx_handler && qp->client_पढ़ोy)
			qp->rx_handler(qp, qp->cb_data, cb_data, len);

		spin_lock_irqsave(&qp->ntb_rx_q_lock, irqflags);
	पूर्ण

	spin_unlock_irqrestore(&qp->ntb_rx_q_lock, irqflags);
पूर्ण

अटल व्योम ntb_rx_copy_callback(व्योम *data,
				 स्थिर काष्ठा dmaengine_result *res)
अणु
	काष्ठा ntb_queue_entry *entry = data;

	/* we need to check DMA results अगर we are using DMA */
	अगर (res) अणु
		क्रमागत dmaengine_tx_result dma_err = res->result;

		चयन (dma_err) अणु
		हाल DMA_TRANS_READ_FAILED:
		हाल DMA_TRANS_WRITE_FAILED:
			entry->errors++;
			fallthrough;
		हाल DMA_TRANS_ABORTED:
		अणु
			काष्ठा ntb_transport_qp *qp = entry->qp;
			व्योम *offset = qp->rx_buff + qp->rx_max_frame *
					qp->rx_index;

			ntb_स_नकल_rx(entry, offset);
			qp->rx_स_नकल++;
			वापस;
		पूर्ण

		हाल DMA_TRANS_NOERROR:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	entry->flags |= DESC_DONE_FLAG;

	ntb_complete_rxc(entry->qp);
पूर्ण

अटल व्योम ntb_स_नकल_rx(काष्ठा ntb_queue_entry *entry, व्योम *offset)
अणु
	व्योम *buf = entry->buf;
	माप_प्रकार len = entry->len;

	स_नकल(buf, offset, len);

	/* Ensure that the data is fully copied out beक्रमe clearing the flag */
	wmb();

	ntb_rx_copy_callback(entry, शून्य);
पूर्ण

अटल पूर्णांक ntb_async_rx_submit(काष्ठा ntb_queue_entry *entry, व्योम *offset)
अणु
	काष्ठा dma_async_tx_descriptor *txd;
	काष्ठा ntb_transport_qp *qp = entry->qp;
	काष्ठा dma_chan *chan = qp->rx_dma_chan;
	काष्ठा dma_device *device;
	माप_प्रकार pay_off, buff_off, len;
	काष्ठा dmaengine_unmap_data *unmap;
	dma_cookie_t cookie;
	व्योम *buf = entry->buf;

	len = entry->len;
	device = chan->device;
	pay_off = (माप_प्रकार)offset & ~PAGE_MASK;
	buff_off = (माप_प्रकार)buf & ~PAGE_MASK;

	अगर (!is_dma_copy_aligned(device, pay_off, buff_off, len))
		जाओ err;

	unmap = dmaengine_get_unmap_data(device->dev, 2, GFP_NOWAIT);
	अगर (!unmap)
		जाओ err;

	unmap->len = len;
	unmap->addr[0] = dma_map_page(device->dev, virt_to_page(offset),
				      pay_off, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(device->dev, unmap->addr[0]))
		जाओ err_get_unmap;

	unmap->to_cnt = 1;

	unmap->addr[1] = dma_map_page(device->dev, virt_to_page(buf),
				      buff_off, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(device->dev, unmap->addr[1]))
		जाओ err_get_unmap;

	unmap->from_cnt = 1;

	txd = device->device_prep_dma_स_नकल(chan, unmap->addr[1],
					     unmap->addr[0], len,
					     DMA_PREP_INTERRUPT);
	अगर (!txd)
		जाओ err_get_unmap;

	txd->callback_result = ntb_rx_copy_callback;
	txd->callback_param = entry;
	dma_set_unmap(txd, unmap);

	cookie = dmaengine_submit(txd);
	अगर (dma_submit_error(cookie))
		जाओ err_set_unmap;

	dmaengine_unmap_put(unmap);

	qp->last_cookie = cookie;

	qp->rx_async++;

	वापस 0;

err_set_unmap:
	dmaengine_unmap_put(unmap);
err_get_unmap:
	dmaengine_unmap_put(unmap);
err:
	वापस -ENXIO;
पूर्ण

अटल व्योम ntb_async_rx(काष्ठा ntb_queue_entry *entry, व्योम *offset)
अणु
	काष्ठा ntb_transport_qp *qp = entry->qp;
	काष्ठा dma_chan *chan = qp->rx_dma_chan;
	पूर्णांक res;

	अगर (!chan)
		जाओ err;

	अगर (entry->len < copy_bytes)
		जाओ err;

	res = ntb_async_rx_submit(entry, offset);
	अगर (res < 0)
		जाओ err;

	अगर (!entry->retries)
		qp->rx_async++;

	वापस;

err:
	ntb_स_नकल_rx(entry, offset);
	qp->rx_स_नकल++;
पूर्ण

अटल पूर्णांक ntb_process_rxc(काष्ठा ntb_transport_qp *qp)
अणु
	काष्ठा ntb_payload_header *hdr;
	काष्ठा ntb_queue_entry *entry;
	व्योम *offset;

	offset = qp->rx_buff + qp->rx_max_frame * qp->rx_index;
	hdr = offset + qp->rx_max_frame - माप(काष्ठा ntb_payload_header);

	dev_dbg(&qp->ndev->pdev->dev, "qp %d: RX ver %u len %d flags %x\n",
		qp->qp_num, hdr->ver, hdr->len, hdr->flags);

	अगर (!(hdr->flags & DESC_DONE_FLAG)) अणु
		dev_dbg(&qp->ndev->pdev->dev, "done flag not set\n");
		qp->rx_ring_empty++;
		वापस -EAGAIN;
	पूर्ण

	अगर (hdr->flags & LINK_DOWN_FLAG) अणु
		dev_dbg(&qp->ndev->pdev->dev, "link down flag set\n");
		ntb_qp_link_करोwn(qp);
		hdr->flags = 0;
		वापस -EAGAIN;
	पूर्ण

	अगर (hdr->ver != (u32)qp->rx_pkts) अणु
		dev_dbg(&qp->ndev->pdev->dev,
			"version mismatch, expected %llu - got %u\n",
			qp->rx_pkts, hdr->ver);
		qp->rx_err_ver++;
		वापस -EIO;
	पूर्ण

	entry = ntb_list_mv(&qp->ntb_rx_q_lock, &qp->rx_pend_q, &qp->rx_post_q);
	अगर (!entry) अणु
		dev_dbg(&qp->ndev->pdev->dev, "no receive buffer\n");
		qp->rx_err_no_buf++;
		वापस -EAGAIN;
	पूर्ण

	entry->rx_hdr = hdr;
	entry->rx_index = qp->rx_index;

	अगर (hdr->len > entry->len) अणु
		dev_dbg(&qp->ndev->pdev->dev,
			"receive buffer overflow! Wanted %d got %d\n",
			hdr->len, entry->len);
		qp->rx_err_oflow++;

		entry->len = -EIO;
		entry->flags |= DESC_DONE_FLAG;

		ntb_complete_rxc(qp);
	पूर्ण अन्यथा अणु
		dev_dbg(&qp->ndev->pdev->dev,
			"RX OK index %u ver %u size %d into buf size %d\n",
			qp->rx_index, hdr->ver, hdr->len, entry->len);

		qp->rx_bytes += hdr->len;
		qp->rx_pkts++;

		entry->len = hdr->len;

		ntb_async_rx(entry, offset);
	पूर्ण

	qp->rx_index++;
	qp->rx_index %= qp->rx_max_entry;

	वापस 0;
पूर्ण

अटल व्योम ntb_transport_rxc_db(अचिन्हित दीर्घ data)
अणु
	काष्ठा ntb_transport_qp *qp = (व्योम *)data;
	पूर्णांक rc, i;

	dev_dbg(&qp->ndev->pdev->dev, "%s: doorbell %d received\n",
		__func__, qp->qp_num);

	/* Limit the number of packets processed in a single पूर्णांकerrupt to
	 * provide fairness to others
	 */
	क्रम (i = 0; i < qp->rx_max_entry; i++) अणु
		rc = ntb_process_rxc(qp);
		अगर (rc)
			अवरोध;
	पूर्ण

	अगर (i && qp->rx_dma_chan)
		dma_async_issue_pending(qp->rx_dma_chan);

	अगर (i == qp->rx_max_entry) अणु
		/* there is more work to करो */
		अगर (qp->active)
			tasklet_schedule(&qp->rxc_db_work);
	पूर्ण अन्यथा अगर (ntb_db_पढ़ो(qp->ndev) & BIT_ULL(qp->qp_num)) अणु
		/* the करोorbell bit is set: clear it */
		ntb_db_clear(qp->ndev, BIT_ULL(qp->qp_num));
		/* ntb_db_पढ़ो ensures ntb_db_clear ग_लिखो is committed */
		ntb_db_पढ़ो(qp->ndev);

		/* an पूर्णांकerrupt may have arrived between finishing
		 * ntb_process_rxc and clearing the करोorbell bit:
		 * there might be some more work to करो.
		 */
		अगर (qp->active)
			tasklet_schedule(&qp->rxc_db_work);
	पूर्ण
पूर्ण

अटल व्योम ntb_tx_copy_callback(व्योम *data,
				 स्थिर काष्ठा dmaengine_result *res)
अणु
	काष्ठा ntb_queue_entry *entry = data;
	काष्ठा ntb_transport_qp *qp = entry->qp;
	काष्ठा ntb_payload_header __iomem *hdr = entry->tx_hdr;

	/* we need to check DMA results अगर we are using DMA */
	अगर (res) अणु
		क्रमागत dmaengine_tx_result dma_err = res->result;

		चयन (dma_err) अणु
		हाल DMA_TRANS_READ_FAILED:
		हाल DMA_TRANS_WRITE_FAILED:
			entry->errors++;
			fallthrough;
		हाल DMA_TRANS_ABORTED:
		अणु
			व्योम __iomem *offset =
				qp->tx_mw + qp->tx_max_frame *
				entry->tx_index;

			/* resubmit via CPU */
			ntb_स_नकल_tx(entry, offset);
			qp->tx_स_नकल++;
			वापस;
		पूर्ण

		हाल DMA_TRANS_NOERROR:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ioग_लिखो32(entry->flags | DESC_DONE_FLAG, &hdr->flags);

	अगर (qp->use_msi)
		ntb_msi_peer_trigger(qp->ndev, PIDX, &qp->peer_msi_desc);
	अन्यथा
		ntb_peer_db_set(qp->ndev, BIT_ULL(qp->qp_num));

	/* The entry length can only be zero अगर the packet is पूर्णांकended to be a
	 * "link down" or similar.  Since no payload is being sent in these
	 * हालs, there is nothing to add to the completion queue.
	 */
	अगर (entry->len > 0) अणु
		qp->tx_bytes += entry->len;

		अगर (qp->tx_handler)
			qp->tx_handler(qp, qp->cb_data, entry->cb_data,
				       entry->len);
	पूर्ण

	ntb_list_add(&qp->ntb_tx_मुक्त_q_lock, &entry->entry, &qp->tx_मुक्त_q);
पूर्ण

अटल व्योम ntb_स_नकल_tx(काष्ठा ntb_queue_entry *entry, व्योम __iomem *offset)
अणु
#अगर_घोषित ARCH_HAS_NOCACHE_UACCESS
	/*
	 * Using non-temporal mov to improve perक्रमmance on non-cached
	 * ग_लिखोs, even though we aren't actually copying from user space.
	 */
	__copy_from_user_inatomic_nocache(offset, entry->buf, entry->len);
#अन्यथा
	स_नकल_toio(offset, entry->buf, entry->len);
#पूर्ण_अगर

	/* Ensure that the data is fully copied out beक्रमe setting the flags */
	wmb();

	ntb_tx_copy_callback(entry, शून्य);
पूर्ण

अटल पूर्णांक ntb_async_tx_submit(काष्ठा ntb_transport_qp *qp,
			       काष्ठा ntb_queue_entry *entry)
अणु
	काष्ठा dma_async_tx_descriptor *txd;
	काष्ठा dma_chan *chan = qp->tx_dma_chan;
	काष्ठा dma_device *device;
	माप_प्रकार len = entry->len;
	व्योम *buf = entry->buf;
	माप_प्रकार dest_off, buff_off;
	काष्ठा dmaengine_unmap_data *unmap;
	dma_addr_t dest;
	dma_cookie_t cookie;

	device = chan->device;
	dest = qp->tx_mw_dma_addr + qp->tx_max_frame * entry->tx_index;
	buff_off = (माप_प्रकार)buf & ~PAGE_MASK;
	dest_off = (माप_प्रकार)dest & ~PAGE_MASK;

	अगर (!is_dma_copy_aligned(device, buff_off, dest_off, len))
		जाओ err;

	unmap = dmaengine_get_unmap_data(device->dev, 1, GFP_NOWAIT);
	अगर (!unmap)
		जाओ err;

	unmap->len = len;
	unmap->addr[0] = dma_map_page(device->dev, virt_to_page(buf),
				      buff_off, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(device->dev, unmap->addr[0]))
		जाओ err_get_unmap;

	unmap->to_cnt = 1;

	txd = device->device_prep_dma_स_नकल(chan, dest, unmap->addr[0], len,
					     DMA_PREP_INTERRUPT);
	अगर (!txd)
		जाओ err_get_unmap;

	txd->callback_result = ntb_tx_copy_callback;
	txd->callback_param = entry;
	dma_set_unmap(txd, unmap);

	cookie = dmaengine_submit(txd);
	अगर (dma_submit_error(cookie))
		जाओ err_set_unmap;

	dmaengine_unmap_put(unmap);

	dma_async_issue_pending(chan);

	वापस 0;
err_set_unmap:
	dmaengine_unmap_put(unmap);
err_get_unmap:
	dmaengine_unmap_put(unmap);
err:
	वापस -ENXIO;
पूर्ण

अटल व्योम ntb_async_tx(काष्ठा ntb_transport_qp *qp,
			 काष्ठा ntb_queue_entry *entry)
अणु
	काष्ठा ntb_payload_header __iomem *hdr;
	काष्ठा dma_chan *chan = qp->tx_dma_chan;
	व्योम __iomem *offset;
	पूर्णांक res;

	entry->tx_index = qp->tx_index;
	offset = qp->tx_mw + qp->tx_max_frame * entry->tx_index;
	hdr = offset + qp->tx_max_frame - माप(काष्ठा ntb_payload_header);
	entry->tx_hdr = hdr;

	ioग_लिखो32(entry->len, &hdr->len);
	ioग_लिखो32((u32)qp->tx_pkts, &hdr->ver);

	अगर (!chan)
		जाओ err;

	अगर (entry->len < copy_bytes)
		जाओ err;

	res = ntb_async_tx_submit(qp, entry);
	अगर (res < 0)
		जाओ err;

	अगर (!entry->retries)
		qp->tx_async++;

	वापस;

err:
	ntb_स_नकल_tx(entry, offset);
	qp->tx_स_नकल++;
पूर्ण

अटल पूर्णांक ntb_process_tx(काष्ठा ntb_transport_qp *qp,
			  काष्ठा ntb_queue_entry *entry)
अणु
	अगर (qp->tx_index == qp->remote_rx_info->entry) अणु
		qp->tx_ring_full++;
		वापस -EAGAIN;
	पूर्ण

	अगर (entry->len > qp->tx_max_frame - माप(काष्ठा ntb_payload_header)) अणु
		अगर (qp->tx_handler)
			qp->tx_handler(qp, qp->cb_data, शून्य, -EIO);

		ntb_list_add(&qp->ntb_tx_मुक्त_q_lock, &entry->entry,
			     &qp->tx_मुक्त_q);
		वापस 0;
	पूर्ण

	ntb_async_tx(qp, entry);

	qp->tx_index++;
	qp->tx_index %= qp->tx_max_entry;

	qp->tx_pkts++;

	वापस 0;
पूर्ण

अटल व्योम ntb_send_link_करोwn(काष्ठा ntb_transport_qp *qp)
अणु
	काष्ठा pci_dev *pdev = qp->ndev->pdev;
	काष्ठा ntb_queue_entry *entry;
	पूर्णांक i, rc;

	अगर (!qp->link_is_up)
		वापस;

	dev_info(&pdev->dev, "qp %d: Send Link Down\n", qp->qp_num);

	क्रम (i = 0; i < NTB_LINK_DOWN_TIMEOUT; i++) अणु
		entry = ntb_list_rm(&qp->ntb_tx_मुक्त_q_lock, &qp->tx_मुक्त_q);
		अगर (entry)
			अवरोध;
		msleep(100);
	पूर्ण

	अगर (!entry)
		वापस;

	entry->cb_data = शून्य;
	entry->buf = शून्य;
	entry->len = 0;
	entry->flags = LINK_DOWN_FLAG;

	rc = ntb_process_tx(qp, entry);
	अगर (rc)
		dev_err(&pdev->dev, "ntb: QP%d unable to send linkdown msg\n",
			qp->qp_num);

	ntb_qp_link_करोwn_reset(qp);
पूर्ण

अटल bool ntb_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *node)
अणु
	वापस dev_to_node(&chan->dev->device) == (पूर्णांक)(अचिन्हित दीर्घ)node;
पूर्ण

/**
 * ntb_transport_create_queue - Create a new NTB transport layer queue
 * @rx_handler: receive callback function
 * @tx_handler: transmit callback function
 * @event_handler: event callback function
 *
 * Create a new NTB transport layer queue and provide the queue with a callback
 * routine क्रम both transmit and receive.  The receive callback routine will be
 * used to pass up data when the transport has received it on the queue.   The
 * transmit callback routine will be called when the transport has completed the
 * transmission of the data on the queue and the data is पढ़ोy to be मुक्तd.
 *
 * RETURNS: poपूर्णांकer to newly created ntb_queue, शून्य on error.
 */
काष्ठा ntb_transport_qp *
ntb_transport_create_queue(व्योम *data, काष्ठा device *client_dev,
			   स्थिर काष्ठा ntb_queue_handlers *handlers)
अणु
	काष्ठा ntb_dev *ndev;
	काष्ठा pci_dev *pdev;
	काष्ठा ntb_transport_ctx *nt;
	काष्ठा ntb_queue_entry *entry;
	काष्ठा ntb_transport_qp *qp;
	u64 qp_bit;
	अचिन्हित पूर्णांक मुक्त_queue;
	dma_cap_mask_t dma_mask;
	पूर्णांक node;
	पूर्णांक i;

	ndev = dev_ntb(client_dev->parent);
	pdev = ndev->pdev;
	nt = ndev->ctx;

	node = dev_to_node(&ndev->dev);

	मुक्त_queue = ffs(nt->qp_biपंचांगap_मुक्त);
	अगर (!मुक्त_queue)
		जाओ err;

	/* decrement मुक्त_queue to make it zero based */
	मुक्त_queue--;

	qp = &nt->qp_vec[मुक्त_queue];
	qp_bit = BIT_ULL(qp->qp_num);

	nt->qp_biपंचांगap_मुक्त &= ~qp_bit;

	qp->cb_data = data;
	qp->rx_handler = handlers->rx_handler;
	qp->tx_handler = handlers->tx_handler;
	qp->event_handler = handlers->event_handler;

	dma_cap_zero(dma_mask);
	dma_cap_set(DMA_MEMCPY, dma_mask);

	अगर (use_dma) अणु
		qp->tx_dma_chan =
			dma_request_channel(dma_mask, ntb_dma_filter_fn,
					    (व्योम *)(अचिन्हित दीर्घ)node);
		अगर (!qp->tx_dma_chan)
			dev_info(&pdev->dev, "Unable to allocate TX DMA channel\n");

		qp->rx_dma_chan =
			dma_request_channel(dma_mask, ntb_dma_filter_fn,
					    (व्योम *)(अचिन्हित दीर्घ)node);
		अगर (!qp->rx_dma_chan)
			dev_info(&pdev->dev, "Unable to allocate RX DMA channel\n");
	पूर्ण अन्यथा अणु
		qp->tx_dma_chan = शून्य;
		qp->rx_dma_chan = शून्य;
	पूर्ण

	qp->tx_mw_dma_addr = 0;
	अगर (qp->tx_dma_chan) अणु
		qp->tx_mw_dma_addr =
			dma_map_resource(qp->tx_dma_chan->device->dev,
					 qp->tx_mw_phys, qp->tx_mw_size,
					 DMA_FROM_DEVICE, 0);
		अगर (dma_mapping_error(qp->tx_dma_chan->device->dev,
				      qp->tx_mw_dma_addr)) अणु
			qp->tx_mw_dma_addr = 0;
			जाओ err1;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "Using %s memcpy for TX\n",
		qp->tx_dma_chan ? "DMA" : "CPU");

	dev_dbg(&pdev->dev, "Using %s memcpy for RX\n",
		qp->rx_dma_chan ? "DMA" : "CPU");

	क्रम (i = 0; i < NTB_QP_DEF_NUM_ENTRIES; i++) अणु
		entry = kzalloc_node(माप(*entry), GFP_KERNEL, node);
		अगर (!entry)
			जाओ err1;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry,
			     &qp->rx_मुक्त_q);
	पूर्ण
	qp->rx_alloc_entry = NTB_QP_DEF_NUM_ENTRIES;

	क्रम (i = 0; i < qp->tx_max_entry; i++) अणु
		entry = kzalloc_node(माप(*entry), GFP_KERNEL, node);
		अगर (!entry)
			जाओ err2;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_tx_मुक्त_q_lock, &entry->entry,
			     &qp->tx_मुक्त_q);
	पूर्ण

	ntb_db_clear(qp->ndev, qp_bit);
	ntb_db_clear_mask(qp->ndev, qp_bit);

	dev_info(&pdev->dev, "NTB Transport QP %d created\n", qp->qp_num);

	वापस qp;

err2:
	जबतक ((entry = ntb_list_rm(&qp->ntb_tx_मुक्त_q_lock, &qp->tx_मुक्त_q)))
		kमुक्त(entry);
err1:
	qp->rx_alloc_entry = 0;
	जबतक ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_मुक्त_q)))
		kमुक्त(entry);
	अगर (qp->tx_mw_dma_addr)
		dma_unmap_resource(qp->tx_dma_chan->device->dev,
				   qp->tx_mw_dma_addr, qp->tx_mw_size,
				   DMA_FROM_DEVICE, 0);
	अगर (qp->tx_dma_chan)
		dma_release_channel(qp->tx_dma_chan);
	अगर (qp->rx_dma_chan)
		dma_release_channel(qp->rx_dma_chan);
	nt->qp_biपंचांगap_मुक्त |= qp_bit;
err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_create_queue);

/**
 * ntb_transport_मुक्त_queue - Frees NTB transport queue
 * @qp: NTB queue to be मुक्तd
 *
 * Frees NTB transport queue
 */
व्योम ntb_transport_मुक्त_queue(काष्ठा ntb_transport_qp *qp)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा ntb_queue_entry *entry;
	u64 qp_bit;

	अगर (!qp)
		वापस;

	pdev = qp->ndev->pdev;

	qp->active = false;

	अगर (qp->tx_dma_chan) अणु
		काष्ठा dma_chan *chan = qp->tx_dma_chan;
		/* Putting the dma_chan to शून्य will क्रमce any new traffic to be
		 * processed by the CPU instead of the DAM engine
		 */
		qp->tx_dma_chan = शून्य;

		/* Try to be nice and रुको क्रम any queued DMA engine
		 * transactions to process beक्रमe smashing it with a rock
		 */
		dma_sync_रुको(chan, qp->last_cookie);
		dmaengine_terminate_all(chan);

		dma_unmap_resource(chan->device->dev,
				   qp->tx_mw_dma_addr, qp->tx_mw_size,
				   DMA_FROM_DEVICE, 0);

		dma_release_channel(chan);
	पूर्ण

	अगर (qp->rx_dma_chan) अणु
		काष्ठा dma_chan *chan = qp->rx_dma_chan;
		/* Putting the dma_chan to शून्य will क्रमce any new traffic to be
		 * processed by the CPU instead of the DAM engine
		 */
		qp->rx_dma_chan = शून्य;

		/* Try to be nice and रुको क्रम any queued DMA engine
		 * transactions to process beक्रमe smashing it with a rock
		 */
		dma_sync_रुको(chan, qp->last_cookie);
		dmaengine_terminate_all(chan);
		dma_release_channel(chan);
	पूर्ण

	qp_bit = BIT_ULL(qp->qp_num);

	ntb_db_set_mask(qp->ndev, qp_bit);
	tasklet_समाप्त(&qp->rxc_db_work);

	cancel_delayed_work_sync(&qp->link_work);

	qp->cb_data = शून्य;
	qp->rx_handler = शून्य;
	qp->tx_handler = शून्य;
	qp->event_handler = शून्य;

	जबतक ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_मुक्त_q)))
		kमुक्त(entry);

	जबतक ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_pend_q))) अणु
		dev_warn(&pdev->dev, "Freeing item from non-empty rx_pend_q\n");
		kमुक्त(entry);
	पूर्ण

	जबतक ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_post_q))) अणु
		dev_warn(&pdev->dev, "Freeing item from non-empty rx_post_q\n");
		kमुक्त(entry);
	पूर्ण

	जबतक ((entry = ntb_list_rm(&qp->ntb_tx_मुक्त_q_lock, &qp->tx_मुक्त_q)))
		kमुक्त(entry);

	qp->transport->qp_biपंचांगap_मुक्त |= qp_bit;

	dev_info(&pdev->dev, "NTB Transport QP %d freed\n", qp->qp_num);
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_मुक्त_queue);

/**
 * ntb_transport_rx_हटाओ - Dequeues enqueued rx packet
 * @qp: NTB queue to be मुक्तd
 * @len: poपूर्णांकer to variable to ग_लिखो enqueued buffers length
 *
 * Dequeues unused buffers from receive queue.  Should only be used during
 * shutकरोwn of qp.
 *
 * RETURNS: शून्य error value on error, or व्योम* क्रम success.
 */
व्योम *ntb_transport_rx_हटाओ(काष्ठा ntb_transport_qp *qp, अचिन्हित पूर्णांक *len)
अणु
	काष्ठा ntb_queue_entry *entry;
	व्योम *buf;

	अगर (!qp || qp->client_पढ़ोy)
		वापस शून्य;

	entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_pend_q);
	अगर (!entry)
		वापस शून्य;

	buf = entry->cb_data;
	*len = entry->len;

	ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry, &qp->rx_मुक्त_q);

	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_rx_हटाओ);

/**
 * ntb_transport_rx_enqueue - Enqueue a new NTB queue entry
 * @qp: NTB transport layer queue the entry is to be enqueued on
 * @cb: per buffer poपूर्णांकer क्रम callback function to use
 * @data: poपूर्णांकer to data buffer that incoming packets will be copied पूर्णांकo
 * @len: length of the data buffer
 *
 * Enqueue a new receive buffer onto the transport queue पूर्णांकo which a NTB
 * payload can be received पूर्णांकo.
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक ntb_transport_rx_enqueue(काष्ठा ntb_transport_qp *qp, व्योम *cb, व्योम *data,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा ntb_queue_entry *entry;

	अगर (!qp)
		वापस -EINVAL;

	entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_मुक्त_q);
	अगर (!entry)
		वापस -ENOMEM;

	entry->cb_data = cb;
	entry->buf = data;
	entry->len = len;
	entry->flags = 0;
	entry->retries = 0;
	entry->errors = 0;
	entry->rx_index = 0;

	ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry, &qp->rx_pend_q);

	अगर (qp->active)
		tasklet_schedule(&qp->rxc_db_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_rx_enqueue);

/**
 * ntb_transport_tx_enqueue - Enqueue a new NTB queue entry
 * @qp: NTB transport layer queue the entry is to be enqueued on
 * @cb: per buffer poपूर्णांकer क्रम callback function to use
 * @data: poपूर्णांकer to data buffer that will be sent
 * @len: length of the data buffer
 *
 * Enqueue a new transmit buffer onto the transport queue from which a NTB
 * payload will be transmitted.  This assumes that a lock is being held to
 * serialize access to the qp.
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक ntb_transport_tx_enqueue(काष्ठा ntb_transport_qp *qp, व्योम *cb, व्योम *data,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा ntb_queue_entry *entry;
	पूर्णांक rc;

	अगर (!qp || !qp->link_is_up || !len)
		वापस -EINVAL;

	entry = ntb_list_rm(&qp->ntb_tx_मुक्त_q_lock, &qp->tx_मुक्त_q);
	अगर (!entry) अणु
		qp->tx_err_no_buf++;
		वापस -EBUSY;
	पूर्ण

	entry->cb_data = cb;
	entry->buf = data;
	entry->len = len;
	entry->flags = 0;
	entry->errors = 0;
	entry->retries = 0;
	entry->tx_index = 0;

	rc = ntb_process_tx(qp, entry);
	अगर (rc)
		ntb_list_add(&qp->ntb_tx_मुक्त_q_lock, &entry->entry,
			     &qp->tx_मुक्त_q);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_tx_enqueue);

/**
 * ntb_transport_link_up - Notअगरy NTB transport of client पढ़ोiness to use queue
 * @qp: NTB transport layer queue to be enabled
 *
 * Notअगरy NTB transport layer of client पढ़ोiness to use queue
 */
व्योम ntb_transport_link_up(काष्ठा ntb_transport_qp *qp)
अणु
	अगर (!qp)
		वापस;

	qp->client_पढ़ोy = true;

	अगर (qp->transport->link_is_up)
		schedule_delayed_work(&qp->link_work, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_link_up);

/**
 * ntb_transport_link_करोwn - Notअगरy NTB transport to no दीर्घer enqueue data
 * @qp: NTB transport layer queue to be disabled
 *
 * Notअगरy NTB transport layer of client's desire to no दीर्घer receive data on
 * transport queue specअगरied.  It is the client's responsibility to ensure all
 * entries on queue are purged or otherwise handled appropriately.
 */
व्योम ntb_transport_link_करोwn(काष्ठा ntb_transport_qp *qp)
अणु
	पूर्णांक val;

	अगर (!qp)
		वापस;

	qp->client_पढ़ोy = false;

	val = ntb_spad_पढ़ो(qp->ndev, QP_LINKS);

	ntb_peer_spad_ग_लिखो(qp->ndev, PIDX, QP_LINKS, val & ~BIT(qp->qp_num));

	अगर (qp->link_is_up)
		ntb_send_link_करोwn(qp);
	अन्यथा
		cancel_delayed_work_sync(&qp->link_work);
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_link_करोwn);

/**
 * ntb_transport_link_query - Query transport link state
 * @qp: NTB transport layer queue to be queried
 *
 * Query connectivity to the remote प्रणाली of the NTB transport queue
 *
 * RETURNS: true क्रम link up or false क्रम link करोwn
 */
bool ntb_transport_link_query(काष्ठा ntb_transport_qp *qp)
अणु
	अगर (!qp)
		वापस false;

	वापस qp->link_is_up;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_link_query);

/**
 * ntb_transport_qp_num - Query the qp number
 * @qp: NTB transport layer queue to be queried
 *
 * Query qp number of the NTB transport queue
 *
 * RETURNS: a zero based number specअगरying the qp number
 */
अचिन्हित अक्षर ntb_transport_qp_num(काष्ठा ntb_transport_qp *qp)
अणु
	अगर (!qp)
		वापस 0;

	वापस qp->qp_num;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_qp_num);

/**
 * ntb_transport_max_size - Query the max payload size of a qp
 * @qp: NTB transport layer queue to be queried
 *
 * Query the maximum payload size permissible on the given qp
 *
 * RETURNS: the max payload size of a qp
 */
अचिन्हित पूर्णांक ntb_transport_max_size(काष्ठा ntb_transport_qp *qp)
अणु
	अचिन्हित पूर्णांक max_size;
	अचिन्हित पूर्णांक copy_align;
	काष्ठा dma_chan *rx_chan, *tx_chan;

	अगर (!qp)
		वापस 0;

	rx_chan = qp->rx_dma_chan;
	tx_chan = qp->tx_dma_chan;

	copy_align = max(rx_chan ? rx_chan->device->copy_align : 0,
			 tx_chan ? tx_chan->device->copy_align : 0);

	/* If DMA engine usage is possible, try to find the max size क्रम that */
	max_size = qp->tx_max_frame - माप(काष्ठा ntb_payload_header);
	max_size = round_करोwn(max_size, 1 << copy_align);

	वापस max_size;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_max_size);

अचिन्हित पूर्णांक ntb_transport_tx_मुक्त_entry(काष्ठा ntb_transport_qp *qp)
अणु
	अचिन्हित पूर्णांक head = qp->tx_index;
	अचिन्हित पूर्णांक tail = qp->remote_rx_info->entry;

	वापस tail > head ? tail - head : qp->tx_max_entry + tail - head;
पूर्ण
EXPORT_SYMBOL_GPL(ntb_transport_tx_मुक्त_entry);

अटल व्योम ntb_transport_करोorbell_callback(व्योम *data, पूर्णांक vector)
अणु
	काष्ठा ntb_transport_ctx *nt = data;
	काष्ठा ntb_transport_qp *qp;
	u64 db_bits;
	अचिन्हित पूर्णांक qp_num;

	अगर (ntb_db_पढ़ो(nt->ndev) & nt->msi_db_mask) अणु
		ntb_transport_msi_peer_desc_changed(nt);
		ntb_db_clear(nt->ndev, nt->msi_db_mask);
	पूर्ण

	db_bits = (nt->qp_biपंचांगap & ~nt->qp_biपंचांगap_मुक्त &
		   ntb_db_vector_mask(nt->ndev, vector));

	जबतक (db_bits) अणु
		qp_num = __ffs(db_bits);
		qp = &nt->qp_vec[qp_num];

		अगर (qp->active)
			tasklet_schedule(&qp->rxc_db_work);

		db_bits &= ~BIT_ULL(qp_num);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ntb_ctx_ops ntb_transport_ops = अणु
	.link_event = ntb_transport_event_callback,
	.db_event = ntb_transport_करोorbell_callback,
पूर्ण;

अटल काष्ठा ntb_client ntb_transport_client = अणु
	.ops = अणु
		.probe = ntb_transport_probe,
		.हटाओ = ntb_transport_मुक्त,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ntb_transport_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info("%s, version %s\n", NTB_TRANSPORT_DESC, NTB_TRANSPORT_VER);

	अगर (debugfs_initialized())
		nt_debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	rc = bus_रेजिस्टर(&ntb_transport_bus);
	अगर (rc)
		जाओ err_bus;

	rc = ntb_रेजिस्टर_client(&ntb_transport_client);
	अगर (rc)
		जाओ err_client;

	वापस 0;

err_client:
	bus_unरेजिस्टर(&ntb_transport_bus);
err_bus:
	debugfs_हटाओ_recursive(nt_debugfs_dir);
	वापस rc;
पूर्ण
module_init(ntb_transport_init);

अटल व्योम __निकास ntb_transport_निकास(व्योम)
अणु
	ntb_unरेजिस्टर_client(&ntb_transport_client);
	bus_unरेजिस्टर(&ntb_transport_bus);
	debugfs_हटाओ_recursive(nt_debugfs_dir);
पूर्ण
module_निकास(ntb_transport_निकास);
