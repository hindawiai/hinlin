<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMA traffic test driver
 *
 * Copyright (C) 2020, Intel Corporation
 * Authors: Isaac Hazan <isaac.hazan@पूर्णांकel.com>
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <linux/thunderbolt.h>

#घोषणा DMA_TEST_TX_RING_SIZE		64
#घोषणा DMA_TEST_RX_RING_SIZE		256
#घोषणा DMA_TEST_FRAME_SIZE		SZ_4K
#घोषणा DMA_TEST_DATA_PATTERN		0x0123456789abcdefLL
#घोषणा DMA_TEST_MAX_PACKETS		1000

क्रमागत dma_test_frame_pdf अणु
	DMA_TEST_PDF_FRAME_START = 1,
	DMA_TEST_PDF_FRAME_END,
पूर्ण;

काष्ठा dma_test_frame अणु
	काष्ठा dma_test *dma_test;
	व्योम *data;
	काष्ठा ring_frame frame;
पूर्ण;

क्रमागत dma_test_test_error अणु
	DMA_TEST_NO_ERROR,
	DMA_TEST_INTERRUPTED,
	DMA_TEST_BUFFER_ERROR,
	DMA_TEST_DMA_ERROR,
	DMA_TEST_CONFIG_ERROR,
	DMA_TEST_SPEED_ERROR,
	DMA_TEST_WIDTH_ERROR,
	DMA_TEST_BONDING_ERROR,
	DMA_TEST_PACKET_ERROR,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dma_test_error_names[] = अणु
	[DMA_TEST_NO_ERROR] = "no errors",
	[DMA_TEST_INTERRUPTED] = "interrupted by signal",
	[DMA_TEST_BUFFER_ERROR] = "no memory for packet buffers",
	[DMA_TEST_DMA_ERROR] = "DMA ring setup failed",
	[DMA_TEST_CONFIG_ERROR] = "configuration is not valid",
	[DMA_TEST_SPEED_ERROR] = "unexpected link speed",
	[DMA_TEST_WIDTH_ERROR] = "unexpected link width",
	[DMA_TEST_BONDING_ERROR] = "lane bonding configuration error",
	[DMA_TEST_PACKET_ERROR] = "packet check failed",
पूर्ण;

क्रमागत dma_test_result अणु
	DMA_TEST_NOT_RUN,
	DMA_TEST_SUCCESS,
	DMA_TEST_FAIL,
पूर्ण;

अटल स्थिर अक्षर * स्थिर dma_test_result_names[] = अणु
	[DMA_TEST_NOT_RUN] = "not run",
	[DMA_TEST_SUCCESS] = "success",
	[DMA_TEST_FAIL] = "failed",
पूर्ण;

/**
 * काष्ठा dma_test - DMA test device driver निजी data
 * @svc: XDoमुख्य service the driver is bound to
 * @xd: XDoमुख्य the service beदीर्घs to
 * @rx_ring: Software ring holding RX frames
 * @rx_hopid: HopID used क्रम receiving frames
 * @tx_ring: Software ring holding TX frames
 * @tx_hopid: HopID used क्रम sending fames
 * @packets_to_send: Number of packets to send
 * @packets_to_receive: Number of packets to receive
 * @packets_sent: Actual number of packets sent
 * @packets_received: Actual number of packets received
 * @link_speed: Expected link speed (Gb/s), %0 to use whatever is negotiated
 * @link_width: Expected link width (Gb/s), %0 to use whatever is negotiated
 * @crc_errors: Number of CRC errors during the test run
 * @buffer_overflow_errors: Number of buffer overflow errors during the test
 *			    run
 * @result: Result of the last run
 * @error_code: Error code of the last run
 * @complete: Used to रुको क्रम the Rx to complete
 * @lock: Lock serializing access to this काष्ठाure
 * @debugfs_dir: dentry of this dma_test
 */
काष्ठा dma_test अणु
	स्थिर काष्ठा tb_service *svc;
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb_ring *rx_ring;
	पूर्णांक rx_hopid;
	काष्ठा tb_ring *tx_ring;
	पूर्णांक tx_hopid;
	अचिन्हित पूर्णांक packets_to_send;
	अचिन्हित पूर्णांक packets_to_receive;
	अचिन्हित पूर्णांक packets_sent;
	अचिन्हित पूर्णांक packets_received;
	अचिन्हित पूर्णांक link_speed;
	अचिन्हित पूर्णांक link_width;
	अचिन्हित पूर्णांक crc_errors;
	अचिन्हित पूर्णांक buffer_overflow_errors;
	क्रमागत dma_test_result result;
	क्रमागत dma_test_test_error error_code;
	काष्ठा completion complete;
	काष्ठा mutex lock;
	काष्ठा dentry *debugfs_dir;
पूर्ण;

/* DMA test property directory UUID: 3188cd10-6523-4a5a-a682-fdca07a248d8 */
अटल स्थिर uuid_t dma_test_dir_uuid =
	UUID_INIT(0x3188cd10, 0x6523, 0x4a5a,
		  0xa6, 0x82, 0xfd, 0xca, 0x07, 0xa2, 0x48, 0xd8);

अटल काष्ठा tb_property_dir *dma_test_dir;
अटल व्योम *dma_test_pattern;

अटल व्योम dma_test_मुक्त_rings(काष्ठा dma_test *dt)
अणु
	अगर (dt->rx_ring) अणु
		tb_xकरोमुख्य_release_in_hopid(dt->xd, dt->rx_hopid);
		tb_ring_मुक्त(dt->rx_ring);
		dt->rx_ring = शून्य;
	पूर्ण
	अगर (dt->tx_ring) अणु
		tb_xकरोमुख्य_release_out_hopid(dt->xd, dt->tx_hopid);
		tb_ring_मुक्त(dt->tx_ring);
		dt->tx_ring = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक dma_test_start_rings(काष्ठा dma_test *dt)
अणु
	अचिन्हित पूर्णांक flags = RING_FLAG_FRAME;
	काष्ठा tb_xकरोमुख्य *xd = dt->xd;
	पूर्णांक ret, e2e_tx_hop = 0;
	काष्ठा tb_ring *ring;

	/*
	 * If we are both sender and receiver (traffic goes over a
	 * special loopback करोngle) enable E2E flow control. This aव्योमs
	 * losing packets.
	 */
	अगर (dt->packets_to_send && dt->packets_to_receive)
		flags |= RING_FLAG_E2E;

	अगर (dt->packets_to_send) अणु
		ring = tb_ring_alloc_tx(xd->tb->nhi, -1, DMA_TEST_TX_RING_SIZE,
					flags);
		अगर (!ring)
			वापस -ENOMEM;

		dt->tx_ring = ring;
		e2e_tx_hop = ring->hop;

		ret = tb_xकरोमुख्य_alloc_out_hopid(xd, -1);
		अगर (ret < 0) अणु
			dma_test_मुक्त_rings(dt);
			वापस ret;
		पूर्ण

		dt->tx_hopid = ret;
	पूर्ण

	अगर (dt->packets_to_receive) अणु
		u16 sof_mask, eof_mask;

		sof_mask = BIT(DMA_TEST_PDF_FRAME_START);
		eof_mask = BIT(DMA_TEST_PDF_FRAME_END);

		ring = tb_ring_alloc_rx(xd->tb->nhi, -1, DMA_TEST_RX_RING_SIZE,
					flags, e2e_tx_hop, sof_mask, eof_mask,
					शून्य, शून्य);
		अगर (!ring) अणु
			dma_test_मुक्त_rings(dt);
			वापस -ENOMEM;
		पूर्ण

		dt->rx_ring = ring;

		ret = tb_xकरोमुख्य_alloc_in_hopid(xd, -1);
		अगर (ret < 0) अणु
			dma_test_मुक्त_rings(dt);
			वापस ret;
		पूर्ण

		dt->rx_hopid = ret;
	पूर्ण

	ret = tb_xकरोमुख्य_enable_paths(dt->xd, dt->tx_hopid,
				      dt->tx_ring ? dt->tx_ring->hop : 0,
				      dt->rx_hopid,
				      dt->rx_ring ? dt->rx_ring->hop : 0);
	अगर (ret) अणु
		dma_test_मुक्त_rings(dt);
		वापस ret;
	पूर्ण

	अगर (dt->tx_ring)
		tb_ring_start(dt->tx_ring);
	अगर (dt->rx_ring)
		tb_ring_start(dt->rx_ring);

	वापस 0;
पूर्ण

अटल व्योम dma_test_stop_rings(काष्ठा dma_test *dt)
अणु
	पूर्णांक ret;

	अगर (dt->rx_ring)
		tb_ring_stop(dt->rx_ring);
	अगर (dt->tx_ring)
		tb_ring_stop(dt->tx_ring);

	ret = tb_xकरोमुख्य_disable_paths(dt->xd, dt->tx_hopid,
				       dt->tx_ring ? dt->tx_ring->hop : 0,
				       dt->rx_hopid,
				       dt->rx_ring ? dt->rx_ring->hop : 0);
	अगर (ret)
		dev_warn(&dt->svc->dev, "failed to disable DMA paths\n");

	dma_test_मुक्त_rings(dt);
पूर्ण

अटल व्योम dma_test_rx_callback(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame,
				 bool canceled)
अणु
	काष्ठा dma_test_frame *tf = container_of(frame, typeof(*tf), frame);
	काष्ठा dma_test *dt = tf->dma_test;
	काष्ठा device *dma_dev = tb_ring_dma_device(dt->rx_ring);

	dma_unmap_single(dma_dev, tf->frame.buffer_phy, DMA_TEST_FRAME_SIZE,
			 DMA_FROM_DEVICE);
	kमुक्त(tf->data);

	अगर (canceled) अणु
		kमुक्त(tf);
		वापस;
	पूर्ण

	dt->packets_received++;
	dev_dbg(&dt->svc->dev, "packet %u/%u received\n", dt->packets_received,
		dt->packets_to_receive);

	अगर (tf->frame.flags & RING_DESC_CRC_ERROR)
		dt->crc_errors++;
	अगर (tf->frame.flags & RING_DESC_BUFFER_OVERRUN)
		dt->buffer_overflow_errors++;

	kमुक्त(tf);

	अगर (dt->packets_received == dt->packets_to_receive)
		complete(&dt->complete);
पूर्ण

अटल पूर्णांक dma_test_submit_rx(काष्ठा dma_test *dt, माप_प्रकार npackets)
अणु
	काष्ठा device *dma_dev = tb_ring_dma_device(dt->rx_ring);
	पूर्णांक i;

	क्रम (i = 0; i < npackets; i++) अणु
		काष्ठा dma_test_frame *tf;
		dma_addr_t dma_addr;

		tf = kzalloc(माप(*tf), GFP_KERNEL);
		अगर (!tf)
			वापस -ENOMEM;

		tf->data = kzalloc(DMA_TEST_FRAME_SIZE, GFP_KERNEL);
		अगर (!tf->data) अणु
			kमुक्त(tf);
			वापस -ENOMEM;
		पूर्ण

		dma_addr = dma_map_single(dma_dev, tf->data, DMA_TEST_FRAME_SIZE,
					  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
			kमुक्त(tf->data);
			kमुक्त(tf);
			वापस -ENOMEM;
		पूर्ण

		tf->frame.buffer_phy = dma_addr;
		tf->frame.callback = dma_test_rx_callback;
		tf->dma_test = dt;
		INIT_LIST_HEAD(&tf->frame.list);

		tb_ring_rx(dt->rx_ring, &tf->frame);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dma_test_tx_callback(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame,
				 bool canceled)
अणु
	काष्ठा dma_test_frame *tf = container_of(frame, typeof(*tf), frame);
	काष्ठा dma_test *dt = tf->dma_test;
	काष्ठा device *dma_dev = tb_ring_dma_device(dt->tx_ring);

	dma_unmap_single(dma_dev, tf->frame.buffer_phy, DMA_TEST_FRAME_SIZE,
			 DMA_TO_DEVICE);
	kमुक्त(tf->data);
	kमुक्त(tf);
पूर्ण

अटल पूर्णांक dma_test_submit_tx(काष्ठा dma_test *dt, माप_प्रकार npackets)
अणु
	काष्ठा device *dma_dev = tb_ring_dma_device(dt->tx_ring);
	पूर्णांक i;

	क्रम (i = 0; i < npackets; i++) अणु
		काष्ठा dma_test_frame *tf;
		dma_addr_t dma_addr;

		tf = kzalloc(माप(*tf), GFP_KERNEL);
		अगर (!tf)
			वापस -ENOMEM;

		tf->frame.size = 0; /* means 4096 */
		tf->dma_test = dt;

		tf->data = kmemdup(dma_test_pattern, DMA_TEST_FRAME_SIZE, GFP_KERNEL);
		अगर (!tf->data) अणु
			kमुक्त(tf);
			वापस -ENOMEM;
		पूर्ण

		dma_addr = dma_map_single(dma_dev, tf->data, DMA_TEST_FRAME_SIZE,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
			kमुक्त(tf->data);
			kमुक्त(tf);
			वापस -ENOMEM;
		पूर्ण

		tf->frame.buffer_phy = dma_addr;
		tf->frame.callback = dma_test_tx_callback;
		tf->frame.sof = DMA_TEST_PDF_FRAME_START;
		tf->frame.eof = DMA_TEST_PDF_FRAME_END;
		INIT_LIST_HEAD(&tf->frame.list);

		dt->packets_sent++;
		dev_dbg(&dt->svc->dev, "packet %u/%u sent\n", dt->packets_sent,
			dt->packets_to_send);

		tb_ring_tx(dt->tx_ring, &tf->frame);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DMA_TEST_DEBUGFS_ATTR(__fops, __get, __validate, __set)	\
अटल पूर्णांक __fops ## _show(व्योम *data, u64 *val)		\
अणु								\
	काष्ठा tb_service *svc = data;				\
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);	\
	पूर्णांक ret;						\
								\
	ret = mutex_lock_पूर्णांकerruptible(&dt->lock);		\
	अगर (ret)						\
		वापस ret;					\
	__get(dt, val);						\
	mutex_unlock(&dt->lock);				\
	वापस 0;						\
पूर्ण								\
अटल पूर्णांक __fops ## _store(व्योम *data, u64 val)		\
अणु								\
	काष्ठा tb_service *svc = data;				\
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);	\
	पूर्णांक ret;						\
								\
	ret = __validate(val);					\
	अगर (ret)						\
		वापस ret;					\
	ret = mutex_lock_पूर्णांकerruptible(&dt->lock);		\
	अगर (ret)						\
		वापस ret;					\
	__set(dt, val);						\
	mutex_unlock(&dt->lock);				\
	वापस 0;						\
पूर्ण								\
DEFINE_DEBUGFS_ATTRIBUTE(__fops ## _fops, __fops ## _show,	\
			 __fops ## _store, "%llu\n")

अटल व्योम lanes_get(स्थिर काष्ठा dma_test *dt, u64 *val)
अणु
	*val = dt->link_width;
पूर्ण

अटल पूर्णांक lanes_validate(u64 val)
अणु
	वापस val > 2 ? -EINVAL : 0;
पूर्ण

अटल व्योम lanes_set(काष्ठा dma_test *dt, u64 val)
अणु
	dt->link_width = val;
पूर्ण
DMA_TEST_DEBUGFS_ATTR(lanes, lanes_get, lanes_validate, lanes_set);

अटल व्योम speed_get(स्थिर काष्ठा dma_test *dt, u64 *val)
अणु
	*val = dt->link_speed;
पूर्ण

अटल पूर्णांक speed_validate(u64 val)
अणु
	चयन (val) अणु
	हाल 20:
	हाल 10:
	हाल 0:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम speed_set(काष्ठा dma_test *dt, u64 val)
अणु
	dt->link_speed = val;
पूर्ण
DMA_TEST_DEBUGFS_ATTR(speed, speed_get, speed_validate, speed_set);

अटल व्योम packets_to_receive_get(स्थिर काष्ठा dma_test *dt, u64 *val)
अणु
	*val = dt->packets_to_receive;
पूर्ण

अटल पूर्णांक packets_to_receive_validate(u64 val)
अणु
	वापस val > DMA_TEST_MAX_PACKETS ? -EINVAL : 0;
पूर्ण

अटल व्योम packets_to_receive_set(काष्ठा dma_test *dt, u64 val)
अणु
	dt->packets_to_receive = val;
पूर्ण
DMA_TEST_DEBUGFS_ATTR(packets_to_receive, packets_to_receive_get,
		      packets_to_receive_validate, packets_to_receive_set);

अटल व्योम packets_to_send_get(स्थिर काष्ठा dma_test *dt, u64 *val)
अणु
	*val = dt->packets_to_send;
पूर्ण

अटल पूर्णांक packets_to_send_validate(u64 val)
अणु
	वापस val > DMA_TEST_MAX_PACKETS ? -EINVAL : 0;
पूर्ण

अटल व्योम packets_to_send_set(काष्ठा dma_test *dt, u64 val)
अणु
	dt->packets_to_send = val;
पूर्ण
DMA_TEST_DEBUGFS_ATTR(packets_to_send, packets_to_send_get,
		      packets_to_send_validate, packets_to_send_set);

अटल पूर्णांक dma_test_set_bonding(काष्ठा dma_test *dt)
अणु
	चयन (dt->link_width) अणु
	हाल 2:
		वापस tb_xकरोमुख्य_lane_bonding_enable(dt->xd);
	हाल 1:
		tb_xकरोमुख्य_lane_bonding_disable(dt->xd);
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool dma_test_validate_config(काष्ठा dma_test *dt)
अणु
	अगर (!dt->packets_to_send && !dt->packets_to_receive)
		वापस false;
	अगर (dt->packets_to_send && dt->packets_to_receive &&
	    dt->packets_to_send != dt->packets_to_receive)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम dma_test_check_errors(काष्ठा dma_test *dt, पूर्णांक ret)
अणु
	अगर (!dt->error_code) अणु
		अगर (dt->link_speed && dt->xd->link_speed != dt->link_speed) अणु
			dt->error_code = DMA_TEST_SPEED_ERROR;
		पूर्ण अन्यथा अगर (dt->link_width &&
			   dt->xd->link_width != dt->link_width) अणु
			dt->error_code = DMA_TEST_WIDTH_ERROR;
		पूर्ण अन्यथा अगर (dt->packets_to_send != dt->packets_sent ||
			 dt->packets_to_receive != dt->packets_received ||
			 dt->crc_errors || dt->buffer_overflow_errors) अणु
			dt->error_code = DMA_TEST_PACKET_ERROR;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण

	dt->result = DMA_TEST_FAIL;
पूर्ण

अटल पूर्णांक test_store(व्योम *data, u64 val)
अणु
	काष्ठा tb_service *svc = data;
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);
	पूर्णांक ret;

	अगर (val != 1)
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&dt->lock);
	अगर (ret)
		वापस ret;

	dt->packets_sent = 0;
	dt->packets_received = 0;
	dt->crc_errors = 0;
	dt->buffer_overflow_errors = 0;
	dt->result = DMA_TEST_SUCCESS;
	dt->error_code = DMA_TEST_NO_ERROR;

	dev_dbg(&svc->dev, "DMA test starting\n");
	अगर (dt->link_speed)
		dev_dbg(&svc->dev, "link_speed: %u Gb/s\n", dt->link_speed);
	अगर (dt->link_width)
		dev_dbg(&svc->dev, "link_width: %u\n", dt->link_width);
	dev_dbg(&svc->dev, "packets_to_send: %u\n", dt->packets_to_send);
	dev_dbg(&svc->dev, "packets_to_receive: %u\n", dt->packets_to_receive);

	अगर (!dma_test_validate_config(dt)) अणु
		dev_err(&svc->dev, "invalid test configuration\n");
		dt->error_code = DMA_TEST_CONFIG_ERROR;
		जाओ out_unlock;
	पूर्ण

	ret = dma_test_set_bonding(dt);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to set lanes\n");
		dt->error_code = DMA_TEST_BONDING_ERROR;
		जाओ out_unlock;
	पूर्ण

	ret = dma_test_start_rings(dt);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to enable DMA rings\n");
		dt->error_code = DMA_TEST_DMA_ERROR;
		जाओ out_unlock;
	पूर्ण

	अगर (dt->packets_to_receive) अणु
		reinit_completion(&dt->complete);
		ret = dma_test_submit_rx(dt, dt->packets_to_receive);
		अगर (ret) अणु
			dev_err(&svc->dev, "failed to submit receive buffers\n");
			dt->error_code = DMA_TEST_BUFFER_ERROR;
			जाओ out_stop;
		पूर्ण
	पूर्ण

	अगर (dt->packets_to_send) अणु
		ret = dma_test_submit_tx(dt, dt->packets_to_send);
		अगर (ret) अणु
			dev_err(&svc->dev, "failed to submit transmit buffers\n");
			dt->error_code = DMA_TEST_BUFFER_ERROR;
			जाओ out_stop;
		पूर्ण
	पूर्ण

	अगर (dt->packets_to_receive) अणु
		ret = रुको_क्रम_completion_पूर्णांकerruptible(&dt->complete);
		अगर (ret) अणु
			dt->error_code = DMA_TEST_INTERRUPTED;
			जाओ out_stop;
		पूर्ण
	पूर्ण

out_stop:
	dma_test_stop_rings(dt);
out_unlock:
	dma_test_check_errors(dt, ret);
	mutex_unlock(&dt->lock);

	dev_dbg(&svc->dev, "DMA test %s\n", dma_test_result_names[dt->result]);
	वापस ret;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(test_fops, शून्य, test_store, "%llu\n");

अटल पूर्णांक status_show(काष्ठा seq_file *s, व्योम *not_used)
अणु
	काष्ठा tb_service *svc = s->निजी;
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&dt->lock);
	अगर (ret)
		वापस ret;

	seq_म_लिखो(s, "result: %s\n", dma_test_result_names[dt->result]);
	अगर (dt->result == DMA_TEST_NOT_RUN)
		जाओ out_unlock;

	seq_म_लिखो(s, "packets received: %u\n", dt->packets_received);
	seq_म_लिखो(s, "packets sent: %u\n", dt->packets_sent);
	seq_म_लिखो(s, "CRC errors: %u\n", dt->crc_errors);
	seq_म_लिखो(s, "buffer overflow errors: %u\n",
		   dt->buffer_overflow_errors);
	seq_म_लिखो(s, "error: %s\n", dma_test_error_names[dt->error_code]);

out_unlock:
	mutex_unlock(&dt->lock);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(status);

अटल व्योम dma_test_debugfs_init(काष्ठा tb_service *svc)
अणु
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);

	dt->debugfs_dir = debugfs_create_dir("dma_test", svc->debugfs_dir);

	debugfs_create_file("lanes", 0600, dt->debugfs_dir, svc, &lanes_fops);
	debugfs_create_file("speed", 0600, dt->debugfs_dir, svc, &speed_fops);
	debugfs_create_file("packets_to_receive", 0600, dt->debugfs_dir, svc,
			    &packets_to_receive_fops);
	debugfs_create_file("packets_to_send", 0600, dt->debugfs_dir, svc,
			    &packets_to_send_fops);
	debugfs_create_file("status", 0400, dt->debugfs_dir, svc, &status_fops);
	debugfs_create_file("test", 0200, dt->debugfs_dir, svc, &test_fops);
पूर्ण

अटल पूर्णांक dma_test_probe(काष्ठा tb_service *svc, स्थिर काष्ठा tb_service_id *id)
अणु
	काष्ठा tb_xकरोमुख्य *xd = tb_service_parent(svc);
	काष्ठा dma_test *dt;

	dt = devm_kzalloc(&svc->dev, माप(*dt), GFP_KERNEL);
	अगर (!dt)
		वापस -ENOMEM;

	dt->svc = svc;
	dt->xd = xd;
	mutex_init(&dt->lock);
	init_completion(&dt->complete);

	tb_service_set_drvdata(svc, dt);
	dma_test_debugfs_init(svc);

	वापस 0;
पूर्ण

अटल व्योम dma_test_हटाओ(काष्ठा tb_service *svc)
अणु
	काष्ठा dma_test *dt = tb_service_get_drvdata(svc);

	mutex_lock(&dt->lock);
	debugfs_हटाओ_recursive(dt->debugfs_dir);
	mutex_unlock(&dt->lock);
पूर्ण

अटल पूर्णांक __maybe_unused dma_test_suspend(काष्ठा device *dev)
अणु
	/*
	 * No need to करो anything special here. If userspace is writing
	 * to the test attribute when suspend started, it comes out from
	 * रुको_क्रम_completion_पूर्णांकerruptible() with -ERESTARTSYS and the
	 * DMA test fails tearing करोwn the rings. Once userspace is
	 * thawed the kernel restarts the ग_लिखो syscall effectively
	 * re-running the test.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dma_test_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dma_test_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dma_test_suspend, dma_test_resume)
पूर्ण;

अटल स्थिर काष्ठा tb_service_id dma_test_ids[] = अणु
	अणु TB_SERVICE("dma_test", 1) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(tbsvc, dma_test_ids);

अटल काष्ठा tb_service_driver dma_test_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "thunderbolt_dma_test",
		.pm = &dma_test_pm_ops,
	पूर्ण,
	.probe = dma_test_probe,
	.हटाओ = dma_test_हटाओ,
	.id_table = dma_test_ids,
पूर्ण;

अटल पूर्णांक __init dma_test_init(व्योम)
अणु
	u64 data_value = DMA_TEST_DATA_PATTERN;
	पूर्णांक i, ret;

	dma_test_pattern = kदो_स्मृति(DMA_TEST_FRAME_SIZE, GFP_KERNEL);
	अगर (!dma_test_pattern)
		वापस -ENOMEM;

	क्रम (i = 0; i <	DMA_TEST_FRAME_SIZE / माप(data_value); i++)
		((u32 *)dma_test_pattern)[i] = data_value++;

	dma_test_dir = tb_property_create_dir(&dma_test_dir_uuid);
	अगर (!dma_test_dir) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_pattern;
	पूर्ण

	tb_property_add_immediate(dma_test_dir, "prtcid", 1);
	tb_property_add_immediate(dma_test_dir, "prtcvers", 1);
	tb_property_add_immediate(dma_test_dir, "prtcrevs", 0);
	tb_property_add_immediate(dma_test_dir, "prtcstns", 0);

	ret = tb_रेजिस्टर_property_dir("dma_test", dma_test_dir);
	अगर (ret)
		जाओ err_मुक्त_dir;

	ret = tb_रेजिस्टर_service_driver(&dma_test_driver);
	अगर (ret)
		जाओ err_unरेजिस्टर_dir;

	वापस 0;

err_unरेजिस्टर_dir:
	tb_unरेजिस्टर_property_dir("dma_test", dma_test_dir);
err_मुक्त_dir:
	tb_property_मुक्त_dir(dma_test_dir);
err_मुक्त_pattern:
	kमुक्त(dma_test_pattern);

	वापस ret;
पूर्ण
module_init(dma_test_init);

अटल व्योम __निकास dma_test_निकास(व्योम)
अणु
	tb_unरेजिस्टर_service_driver(&dma_test_driver);
	tb_unरेजिस्टर_property_dir("dma_test", dma_test_dir);
	tb_property_मुक्त_dir(dma_test_dir);
	kमुक्त(dma_test_pattern);
पूर्ण
module_निकास(dma_test_निकास);

MODULE_AUTHOR("Isaac Hazan <isaac.hazan@intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("DMA traffic test driver");
MODULE_LICENSE("GPL v2");
