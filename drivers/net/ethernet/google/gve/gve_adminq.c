<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश "gve.h"
#समावेश "gve_adminq.h"
#समावेश "gve_register.h"

#घोषणा GVE_MAX_ADMINQ_RELEASE_CHECK	500
#घोषणा GVE_ADMINQ_SLEEP_LEN		20
#घोषणा GVE_MAX_ADMINQ_EVENT_COUNTER_CHECK	100

#घोषणा GVE_DEVICE_OPTION_ERROR_FMT "%s option error:\n" \
"Expected: length=%d, feature_mask=%x.\n" \
"Actual: length=%d, feature_mask=%x.\n"

अटल
काष्ठा gve_device_option *gve_get_next_option(काष्ठा gve_device_descriptor *descriptor,
					      काष्ठा gve_device_option *option)
अणु
	व्योम *option_end, *descriptor_end;

	option_end = (व्योम *)(option + 1) + be16_to_cpu(option->option_length);
	descriptor_end = (व्योम *)descriptor + be16_to_cpu(descriptor->total_length);

	वापस option_end > descriptor_end ? शून्य : (काष्ठा gve_device_option *)option_end;
पूर्ण

अटल
व्योम gve_parse_device_option(काष्ठा gve_priv *priv,
			     काष्ठा gve_device_descriptor *device_descriptor,
			     काष्ठा gve_device_option *option)
अणु
	u16 option_length = be16_to_cpu(option->option_length);
	u16 option_id = be16_to_cpu(option->option_id);

	चयन (option_id) अणु
	हाल GVE_DEV_OPT_ID_RAW_ADDRESSING:
		/* If the length or feature mask करोesn't match,
		 * जारी without enabling the feature.
		 */
		अगर (option_length != GVE_DEV_OPT_LEN_RAW_ADDRESSING ||
		    option->feat_mask != cpu_to_be32(GVE_DEV_OPT_FEAT_MASK_RAW_ADDRESSING)) अणु
			dev_warn(&priv->pdev->dev, GVE_DEVICE_OPTION_ERROR_FMT, "Raw Addressing",
				 GVE_DEV_OPT_LEN_RAW_ADDRESSING,
				 cpu_to_be32(GVE_DEV_OPT_FEAT_MASK_RAW_ADDRESSING),
				 option_length, option->feat_mask);
			priv->raw_addressing = 0;
		पूर्ण अन्यथा अणु
			dev_info(&priv->pdev->dev,
				 "Raw addressing device option enabled.\n");
			priv->raw_addressing = 1;
		पूर्ण
		अवरोध;
	शेष:
		/* If we करोn't recognize the option just जारी
		 * without करोing anything.
		 */
		dev_dbg(&priv->pdev->dev, "Unrecognized device option 0x%hx not enabled.\n",
			option_id);
	पूर्ण
पूर्ण

पूर्णांक gve_adminq_alloc(काष्ठा device *dev, काष्ठा gve_priv *priv)
अणु
	priv->adminq = dma_alloc_coherent(dev, PAGE_SIZE,
					  &priv->adminq_bus_addr, GFP_KERNEL);
	अगर (unlikely(!priv->adminq))
		वापस -ENOMEM;

	priv->adminq_mask = (PAGE_SIZE / माप(जोड़ gve_adminq_command)) - 1;
	priv->adminq_prod_cnt = 0;
	priv->adminq_cmd_fail = 0;
	priv->adminq_समयouts = 0;
	priv->adminq_describe_device_cnt = 0;
	priv->adminq_cfg_device_resources_cnt = 0;
	priv->adminq_रेजिस्टर_page_list_cnt = 0;
	priv->adminq_unरेजिस्टर_page_list_cnt = 0;
	priv->adminq_create_tx_queue_cnt = 0;
	priv->adminq_create_rx_queue_cnt = 0;
	priv->adminq_destroy_tx_queue_cnt = 0;
	priv->adminq_destroy_rx_queue_cnt = 0;
	priv->adminq_dcfg_device_resources_cnt = 0;
	priv->adminq_set_driver_parameter_cnt = 0;
	priv->adminq_report_stats_cnt = 0;
	priv->adminq_report_link_speed_cnt = 0;

	/* Setup Admin queue with the device */
	ioग_लिखो32be(priv->adminq_bus_addr / PAGE_SIZE,
		    &priv->reg_bar0->adminq_pfn);

	gve_set_admin_queue_ok(priv);
	वापस 0;
पूर्ण

व्योम gve_adminq_release(काष्ठा gve_priv *priv)
अणु
	पूर्णांक i = 0;

	/* Tell the device the adminq is leaving */
	ioग_लिखो32be(0x0, &priv->reg_bar0->adminq_pfn);
	जबतक (ioपढ़ो32be(&priv->reg_bar0->adminq_pfn)) अणु
		/* If this is reached the device is unrecoverable and still
		 * holding memory. Continue looping to aव्योम memory corruption,
		 * but WARN so it is visible what is going on.
		 */
		अगर (i == GVE_MAX_ADMINQ_RELEASE_CHECK)
			WARN(1, "Unrecoverable platform error!");
		i++;
		msleep(GVE_ADMINQ_SLEEP_LEN);
	पूर्ण
	gve_clear_device_rings_ok(priv);
	gve_clear_device_resources_ok(priv);
	gve_clear_admin_queue_ok(priv);
पूर्ण

व्योम gve_adminq_मुक्त(काष्ठा device *dev, काष्ठा gve_priv *priv)
अणु
	अगर (!gve_get_admin_queue_ok(priv))
		वापस;
	gve_adminq_release(priv);
	dma_मुक्त_coherent(dev, PAGE_SIZE, priv->adminq, priv->adminq_bus_addr);
	gve_clear_admin_queue_ok(priv);
पूर्ण

अटल व्योम gve_adminq_kick_cmd(काष्ठा gve_priv *priv, u32 prod_cnt)
अणु
	ioग_लिखो32be(prod_cnt, &priv->reg_bar0->adminq_करोorbell);
पूर्ण

अटल bool gve_adminq_रुको_क्रम_cmd(काष्ठा gve_priv *priv, u32 prod_cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GVE_MAX_ADMINQ_EVENT_COUNTER_CHECK; i++) अणु
		अगर (ioपढ़ो32be(&priv->reg_bar0->adminq_event_counter)
		    == prod_cnt)
			वापस true;
		msleep(GVE_ADMINQ_SLEEP_LEN);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक gve_adminq_parse_err(काष्ठा gve_priv *priv, u32 status)
अणु
	अगर (status != GVE_ADMINQ_COMMAND_PASSED &&
	    status != GVE_ADMINQ_COMMAND_UNSET) अणु
		dev_err(&priv->pdev->dev, "AQ command failed with status %d\n", status);
		priv->adminq_cmd_fail++;
	पूर्ण
	चयन (status) अणु
	हाल GVE_ADMINQ_COMMAND_PASSED:
		वापस 0;
	हाल GVE_ADMINQ_COMMAND_UNSET:
		dev_err(&priv->pdev->dev, "parse_aq_err: err and status both unset, this should not be possible.\n");
		वापस -EINVAL;
	हाल GVE_ADMINQ_COMMAND_ERROR_ABORTED:
	हाल GVE_ADMINQ_COMMAND_ERROR_CANCELLED:
	हाल GVE_ADMINQ_COMMAND_ERROR_DATALOSS:
	हाल GVE_ADMINQ_COMMAND_ERROR_FAILED_PRECONDITION:
	हाल GVE_ADMINQ_COMMAND_ERROR_UNAVAILABLE:
		वापस -EAGAIN;
	हाल GVE_ADMINQ_COMMAND_ERROR_ALREADY_EXISTS:
	हाल GVE_ADMINQ_COMMAND_ERROR_INTERNAL_ERROR:
	हाल GVE_ADMINQ_COMMAND_ERROR_INVALID_ARGUMENT:
	हाल GVE_ADMINQ_COMMAND_ERROR_NOT_FOUND:
	हाल GVE_ADMINQ_COMMAND_ERROR_OUT_OF_RANGE:
	हाल GVE_ADMINQ_COMMAND_ERROR_UNKNOWN_ERROR:
		वापस -EINVAL;
	हाल GVE_ADMINQ_COMMAND_ERROR_DEADLINE_EXCEEDED:
		वापस -ETIME;
	हाल GVE_ADMINQ_COMMAND_ERROR_PERMISSION_DENIED:
	हाल GVE_ADMINQ_COMMAND_ERROR_UNAUTHENTICATED:
		वापस -EACCES;
	हाल GVE_ADMINQ_COMMAND_ERROR_RESOURCE_EXHAUSTED:
		वापस -ENOMEM;
	हाल GVE_ADMINQ_COMMAND_ERROR_UNIMPLEMENTED:
		वापस -ENOTSUPP;
	शेष:
		dev_err(&priv->pdev->dev, "parse_aq_err: unknown status code %d\n", status);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Flushes all AQ commands currently queued and रुकोs क्रम them to complete.
 * If there are failures, it will वापस the first error.
 */
अटल पूर्णांक gve_adminq_kick_and_रुको(काष्ठा gve_priv *priv)
अणु
	u32 tail, head;
	पूर्णांक i;

	tail = ioपढ़ो32be(&priv->reg_bar0->adminq_event_counter);
	head = priv->adminq_prod_cnt;

	gve_adminq_kick_cmd(priv, head);
	अगर (!gve_adminq_रुको_क्रम_cmd(priv, head)) अणु
		dev_err(&priv->pdev->dev, "AQ commands timed out, need to reset AQ\n");
		priv->adminq_समयouts++;
		वापस -ENOTRECOVERABLE;
	पूर्ण

	क्रम (i = tail; i < head; i++) अणु
		जोड़ gve_adminq_command *cmd;
		u32 status, err;

		cmd = &priv->adminq[i & priv->adminq_mask];
		status = be32_to_cpu(READ_ONCE(cmd->status));
		err = gve_adminq_parse_err(priv, status);
		अगर (err)
			// Return the first error अगर we failed.
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* This function is not thपढ़ोsafe - the caller is responsible क्रम any
 * necessary locks.
 */
अटल पूर्णांक gve_adminq_issue_cmd(काष्ठा gve_priv *priv,
				जोड़ gve_adminq_command *cmd_orig)
अणु
	जोड़ gve_adminq_command *cmd;
	u32 opcode;
	u32 tail;

	tail = ioपढ़ो32be(&priv->reg_bar0->adminq_event_counter);

	// Check अगर next command will overflow the buffer.
	अगर (((priv->adminq_prod_cnt + 1) & priv->adminq_mask) == tail) अणु
		पूर्णांक err;

		// Flush existing commands to make room.
		err = gve_adminq_kick_and_रुको(priv);
		अगर (err)
			वापस err;

		// Retry.
		tail = ioपढ़ो32be(&priv->reg_bar0->adminq_event_counter);
		अगर (((priv->adminq_prod_cnt + 1) & priv->adminq_mask) == tail) अणु
			// This should never happen. We just flushed the
			// command queue so there should be enough space.
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cmd = &priv->adminq[priv->adminq_prod_cnt & priv->adminq_mask];
	priv->adminq_prod_cnt++;

	स_नकल(cmd, cmd_orig, माप(*cmd_orig));
	opcode = be32_to_cpu(READ_ONCE(cmd->opcode));

	चयन (opcode) अणु
	हाल GVE_ADMINQ_DESCRIBE_DEVICE:
		priv->adminq_describe_device_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_CONFIGURE_DEVICE_RESOURCES:
		priv->adminq_cfg_device_resources_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_REGISTER_PAGE_LIST:
		priv->adminq_रेजिस्टर_page_list_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_UNREGISTER_PAGE_LIST:
		priv->adminq_unरेजिस्टर_page_list_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_CREATE_TX_QUEUE:
		priv->adminq_create_tx_queue_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_CREATE_RX_QUEUE:
		priv->adminq_create_rx_queue_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_DESTROY_TX_QUEUE:
		priv->adminq_destroy_tx_queue_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_DESTROY_RX_QUEUE:
		priv->adminq_destroy_rx_queue_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_DECONFIGURE_DEVICE_RESOURCES:
		priv->adminq_dcfg_device_resources_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_SET_DRIVER_PARAMETER:
		priv->adminq_set_driver_parameter_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_REPORT_STATS:
		priv->adminq_report_stats_cnt++;
		अवरोध;
	हाल GVE_ADMINQ_REPORT_LINK_SPEED:
		priv->adminq_report_link_speed_cnt++;
		अवरोध;
	शेष:
		dev_err(&priv->pdev->dev, "unknown AQ command opcode %d\n", opcode);
	पूर्ण

	वापस 0;
पूर्ण

/* This function is not thपढ़ोsafe - the caller is responsible क्रम any
 * necessary locks.
 * The caller is also responsible क्रम making sure there are no commands
 * रुकोing to be executed.
 */
अटल पूर्णांक gve_adminq_execute_cmd(काष्ठा gve_priv *priv, जोड़ gve_adminq_command *cmd_orig)
अणु
	u32 tail, head;
	पूर्णांक err;

	tail = ioपढ़ो32be(&priv->reg_bar0->adminq_event_counter);
	head = priv->adminq_prod_cnt;
	अगर (tail != head)
		// This is not a valid path
		वापस -EINVAL;

	err = gve_adminq_issue_cmd(priv, cmd_orig);
	अगर (err)
		वापस err;

	वापस gve_adminq_kick_and_रुको(priv);
पूर्ण

/* The device specअगरies that the management vector can either be the first irq
 * or the last irq. ntfy_blk_msix_base_idx indicates the first irq asचिन्हित to
 * the ntfy blks. It अगर is 0 then the management vector is last, अगर it is 1 then
 * the management vector is first.
 *
 * gve arranges the msix vectors so that the management vector is last.
 */
#घोषणा GVE_NTFY_BLK_BASE_MSIX_IDX	0
पूर्णांक gve_adminq_configure_device_resources(काष्ठा gve_priv *priv,
					  dma_addr_t counter_array_bus_addr,
					  u32 num_counters,
					  dma_addr_t db_array_bus_addr,
					  u32 num_ntfy_blks)
अणु
	जोड़ gve_adminq_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_CONFIGURE_DEVICE_RESOURCES);
	cmd.configure_device_resources =
		(काष्ठा gve_adminq_configure_device_resources) अणु
		.counter_array = cpu_to_be64(counter_array_bus_addr),
		.num_counters = cpu_to_be32(num_counters),
		.irq_db_addr = cpu_to_be64(db_array_bus_addr),
		.num_irq_dbs = cpu_to_be32(num_ntfy_blks),
		.irq_db_stride = cpu_to_be32(माप(priv->ntfy_blocks[0])),
		.ntfy_blk_msix_base_idx =
					cpu_to_be32(GVE_NTFY_BLK_BASE_MSIX_IDX),
	पूर्ण;

	वापस gve_adminq_execute_cmd(priv, &cmd);
पूर्ण

पूर्णांक gve_adminq_deconfigure_device_resources(काष्ठा gve_priv *priv)
अणु
	जोड़ gve_adminq_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_DECONFIGURE_DEVICE_RESOURCES);

	वापस gve_adminq_execute_cmd(priv, &cmd);
पूर्ण

अटल पूर्णांक gve_adminq_create_tx_queue(काष्ठा gve_priv *priv, u32 queue_index)
अणु
	काष्ठा gve_tx_ring *tx = &priv->tx[queue_index];
	जोड़ gve_adminq_command cmd;
	u32 qpl_id;
	पूर्णांक err;

	qpl_id = priv->raw_addressing ? GVE_RAW_ADDRESSING_QPL_ID : tx->tx_fअगरo.qpl->id;
	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_CREATE_TX_QUEUE);
	cmd.create_tx_queue = (काष्ठा gve_adminq_create_tx_queue) अणु
		.queue_id = cpu_to_be32(queue_index),
		.reserved = 0,
		.queue_resources_addr =
			cpu_to_be64(tx->q_resources_bus),
		.tx_ring_addr = cpu_to_be64(tx->bus),
		.queue_page_list_id = cpu_to_be32(qpl_id),
		.ntfy_id = cpu_to_be32(tx->ntfy_id),
	पूर्ण;

	err = gve_adminq_issue_cmd(priv, &cmd);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक gve_adminq_create_tx_queues(काष्ठा gve_priv *priv, u32 num_queues)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_queues; i++) अणु
		err = gve_adminq_create_tx_queue(priv, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस gve_adminq_kick_and_रुको(priv);
पूर्ण

अटल पूर्णांक gve_adminq_create_rx_queue(काष्ठा gve_priv *priv, u32 queue_index)
अणु
	काष्ठा gve_rx_ring *rx = &priv->rx[queue_index];
	जोड़ gve_adminq_command cmd;
	u32 qpl_id;
	पूर्णांक err;

	qpl_id = priv->raw_addressing ? GVE_RAW_ADDRESSING_QPL_ID : rx->data.qpl->id;
	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_CREATE_RX_QUEUE);
	cmd.create_rx_queue = (काष्ठा gve_adminq_create_rx_queue) अणु
		.queue_id = cpu_to_be32(queue_index),
		.index = cpu_to_be32(queue_index),
		.reserved = 0,
		.ntfy_id = cpu_to_be32(rx->ntfy_id),
		.queue_resources_addr = cpu_to_be64(rx->q_resources_bus),
		.rx_desc_ring_addr = cpu_to_be64(rx->desc.bus),
		.rx_data_ring_addr = cpu_to_be64(rx->data.data_bus),
		.queue_page_list_id = cpu_to_be32(qpl_id),
	पूर्ण;

	err = gve_adminq_issue_cmd(priv, &cmd);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक gve_adminq_create_rx_queues(काष्ठा gve_priv *priv, u32 num_queues)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_queues; i++) अणु
		err = gve_adminq_create_rx_queue(priv, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस gve_adminq_kick_and_रुको(priv);
पूर्ण

अटल पूर्णांक gve_adminq_destroy_tx_queue(काष्ठा gve_priv *priv, u32 queue_index)
अणु
	जोड़ gve_adminq_command cmd;
	पूर्णांक err;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_DESTROY_TX_QUEUE);
	cmd.destroy_tx_queue = (काष्ठा gve_adminq_destroy_tx_queue) अणु
		.queue_id = cpu_to_be32(queue_index),
	पूर्ण;

	err = gve_adminq_issue_cmd(priv, &cmd);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक gve_adminq_destroy_tx_queues(काष्ठा gve_priv *priv, u32 num_queues)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_queues; i++) अणु
		err = gve_adminq_destroy_tx_queue(priv, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस gve_adminq_kick_and_रुको(priv);
पूर्ण

अटल पूर्णांक gve_adminq_destroy_rx_queue(काष्ठा gve_priv *priv, u32 queue_index)
अणु
	जोड़ gve_adminq_command cmd;
	पूर्णांक err;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_DESTROY_RX_QUEUE);
	cmd.destroy_rx_queue = (काष्ठा gve_adminq_destroy_rx_queue) अणु
		.queue_id = cpu_to_be32(queue_index),
	पूर्ण;

	err = gve_adminq_issue_cmd(priv, &cmd);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक gve_adminq_destroy_rx_queues(काष्ठा gve_priv *priv, u32 num_queues)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < num_queues; i++) अणु
		err = gve_adminq_destroy_rx_queue(priv, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस gve_adminq_kick_and_रुको(priv);
पूर्ण

पूर्णांक gve_adminq_describe_device(काष्ठा gve_priv *priv)
अणु
	काष्ठा gve_device_descriptor *descriptor;
	काष्ठा gve_device_option *dev_opt;
	जोड़ gve_adminq_command cmd;
	dma_addr_t descriptor_bus;
	u16 num_options;
	पूर्णांक err = 0;
	u8 *mac;
	u16 mtu;
	पूर्णांक i;

	स_रखो(&cmd, 0, माप(cmd));
	descriptor = dma_alloc_coherent(&priv->pdev->dev, PAGE_SIZE,
					&descriptor_bus, GFP_KERNEL);
	अगर (!descriptor)
		वापस -ENOMEM;
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_DESCRIBE_DEVICE);
	cmd.describe_device.device_descriptor_addr =
						cpu_to_be64(descriptor_bus);
	cmd.describe_device.device_descriptor_version =
			cpu_to_be32(GVE_ADMINQ_DEVICE_DESCRIPTOR_VERSION);
	cmd.describe_device.available_length = cpu_to_be32(PAGE_SIZE);

	err = gve_adminq_execute_cmd(priv, &cmd);
	अगर (err)
		जाओ मुक्त_device_descriptor;

	priv->tx_desc_cnt = be16_to_cpu(descriptor->tx_queue_entries);
	अगर (priv->tx_desc_cnt * माप(priv->tx->desc[0]) < PAGE_SIZE) अणु
		dev_err(&priv->pdev->dev, "Tx desc count %d too low\n", priv->tx_desc_cnt);
		err = -EINVAL;
		जाओ मुक्त_device_descriptor;
	पूर्ण
	priv->rx_desc_cnt = be16_to_cpu(descriptor->rx_queue_entries);
	अगर (priv->rx_desc_cnt * माप(priv->rx->desc.desc_ring[0])
	    < PAGE_SIZE ||
	    priv->rx_desc_cnt * माप(priv->rx->data.data_ring[0])
	    < PAGE_SIZE) अणु
		dev_err(&priv->pdev->dev, "Rx desc count %d too low\n", priv->rx_desc_cnt);
		err = -EINVAL;
		जाओ मुक्त_device_descriptor;
	पूर्ण
	priv->max_रेजिस्टरed_pages =
				be64_to_cpu(descriptor->max_रेजिस्टरed_pages);
	mtu = be16_to_cpu(descriptor->mtu);
	अगर (mtu < ETH_MIN_MTU) अणु
		dev_err(&priv->pdev->dev, "MTU %d below minimum MTU\n", mtu);
		err = -EINVAL;
		जाओ मुक्त_device_descriptor;
	पूर्ण
	priv->dev->max_mtu = mtu;
	priv->num_event_counters = be16_to_cpu(descriptor->counters);
	ether_addr_copy(priv->dev->dev_addr, descriptor->mac);
	mac = descriptor->mac;
	dev_info(&priv->pdev->dev, "MAC addr: %pM\n", mac);
	priv->tx_pages_per_qpl = be16_to_cpu(descriptor->tx_pages_per_qpl);
	priv->rx_data_slot_cnt = be16_to_cpu(descriptor->rx_pages_per_qpl);
	अगर (priv->rx_data_slot_cnt < priv->rx_desc_cnt) अणु
		dev_err(&priv->pdev->dev, "rx_data_slot_cnt cannot be smaller than rx_desc_cnt, setting rx_desc_cnt down to %d.\n",
			priv->rx_data_slot_cnt);
		priv->rx_desc_cnt = priv->rx_data_slot_cnt;
	पूर्ण
	priv->शेष_num_queues = be16_to_cpu(descriptor->शेष_num_queues);
	dev_opt = (व्योम *)(descriptor + 1);

	num_options = be16_to_cpu(descriptor->num_device_options);
	क्रम (i = 0; i < num_options; i++) अणु
		काष्ठा gve_device_option *next_opt;

		next_opt = gve_get_next_option(descriptor, dev_opt);
		अगर (!next_opt) अणु
			dev_err(&priv->dev->dev,
				"options exceed device_descriptor's total length.\n");
			err = -EINVAL;
			जाओ मुक्त_device_descriptor;
		पूर्ण

		gve_parse_device_option(priv, descriptor, dev_opt);
		dev_opt = next_opt;
	पूर्ण

मुक्त_device_descriptor:
	dma_मुक्त_coherent(&priv->pdev->dev, माप(*descriptor), descriptor,
			  descriptor_bus);
	वापस err;
पूर्ण

पूर्णांक gve_adminq_रेजिस्टर_page_list(काष्ठा gve_priv *priv,
				  काष्ठा gve_queue_page_list *qpl)
अणु
	काष्ठा device *hdev = &priv->pdev->dev;
	u32 num_entries = qpl->num_entries;
	u32 size = num_entries * माप(qpl->page_buses[0]);
	जोड़ gve_adminq_command cmd;
	dma_addr_t page_list_bus;
	__be64 *page_list;
	पूर्णांक err;
	पूर्णांक i;

	स_रखो(&cmd, 0, माप(cmd));
	page_list = dma_alloc_coherent(hdev, size, &page_list_bus, GFP_KERNEL);
	अगर (!page_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_entries; i++)
		page_list[i] = cpu_to_be64(qpl->page_buses[i]);

	cmd.opcode = cpu_to_be32(GVE_ADMINQ_REGISTER_PAGE_LIST);
	cmd.reg_page_list = (काष्ठा gve_adminq_रेजिस्टर_page_list) अणु
		.page_list_id = cpu_to_be32(qpl->id),
		.num_pages = cpu_to_be32(num_entries),
		.page_address_list_addr = cpu_to_be64(page_list_bus),
	पूर्ण;

	err = gve_adminq_execute_cmd(priv, &cmd);
	dma_मुक्त_coherent(hdev, size, page_list, page_list_bus);
	वापस err;
पूर्ण

पूर्णांक gve_adminq_unरेजिस्टर_page_list(काष्ठा gve_priv *priv, u32 page_list_id)
अणु
	जोड़ gve_adminq_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_UNREGISTER_PAGE_LIST);
	cmd.unreg_page_list = (काष्ठा gve_adminq_unरेजिस्टर_page_list) अणु
		.page_list_id = cpu_to_be32(page_list_id),
	पूर्ण;

	वापस gve_adminq_execute_cmd(priv, &cmd);
पूर्ण

पूर्णांक gve_adminq_set_mtu(काष्ठा gve_priv *priv, u64 mtu)
अणु
	जोड़ gve_adminq_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_SET_DRIVER_PARAMETER);
	cmd.set_driver_param = (काष्ठा gve_adminq_set_driver_parameter) अणु
		.parameter_type = cpu_to_be32(GVE_SET_PARAM_MTU),
		.parameter_value = cpu_to_be64(mtu),
	पूर्ण;

	वापस gve_adminq_execute_cmd(priv, &cmd);
पूर्ण

पूर्णांक gve_adminq_report_stats(काष्ठा gve_priv *priv, u64 stats_report_len,
			    dma_addr_t stats_report_addr, u64 पूर्णांकerval)
अणु
	जोड़ gve_adminq_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_REPORT_STATS);
	cmd.report_stats = (काष्ठा gve_adminq_report_stats) अणु
		.stats_report_len = cpu_to_be64(stats_report_len),
		.stats_report_addr = cpu_to_be64(stats_report_addr),
		.पूर्णांकerval = cpu_to_be64(पूर्णांकerval),
	पूर्ण;

	वापस gve_adminq_execute_cmd(priv, &cmd);
पूर्ण

पूर्णांक gve_adminq_report_link_speed(काष्ठा gve_priv *priv)
अणु
	जोड़ gve_adminq_command gvnic_cmd;
	dma_addr_t link_speed_region_bus;
	__be64 *link_speed_region;
	पूर्णांक err;

	link_speed_region =
		dma_alloc_coherent(&priv->pdev->dev, माप(*link_speed_region),
				   &link_speed_region_bus, GFP_KERNEL);

	अगर (!link_speed_region)
		वापस -ENOMEM;

	स_रखो(&gvnic_cmd, 0, माप(gvnic_cmd));
	gvnic_cmd.opcode = cpu_to_be32(GVE_ADMINQ_REPORT_LINK_SPEED);
	gvnic_cmd.report_link_speed.link_speed_address =
		cpu_to_be64(link_speed_region_bus);

	err = gve_adminq_execute_cmd(priv, &gvnic_cmd);

	priv->link_speed = be64_to_cpu(*link_speed_region);
	dma_मुक्त_coherent(&priv->pdev->dev, माप(*link_speed_region), link_speed_region,
			  link_speed_region_bus);
	वापस err;
पूर्ण
