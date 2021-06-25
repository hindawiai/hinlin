<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dim2.c - MediaLB DIM2 Hardware Dependent Module
 *
 * Copyright (C) 2015-2016, Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/most.h>
#समावेश "hal.h"
#समावेश "errors.h"
#समावेश "sysfs.h"

#घोषणा DMA_CHANNELS (32 - 1)  /* channel 0 is a प्रणाली channel */

#घोषणा MAX_BUFFERS_PACKET      32
#घोषणा MAX_BUFFERS_STREAMING   32
#घोषणा MAX_BUF_SIZE_PACKET     2048
#घोषणा MAX_BUF_SIZE_STREAMING  (8 * 1024)

/*
 * The parameter representing the number of frames per sub-buffer क्रम
 * synchronous channels.  Valid values: [0 .. 6].
 *
 * The values 0, 1, 2, 3, 4, 5, 6 represent corresponding number of frames per
 * sub-buffer 1, 2, 4, 8, 16, 32, 64.
 */
अटल u8 fcnt = 4;  /* (1 << fcnt) frames per subbuffer */
module_param(fcnt, byte, 0000);
MODULE_PARM_DESC(fcnt, "Num of frames per sub-buffer for sync channels as a power of 2");

अटल DEFINE_SPINLOCK(dim_lock);

अटल व्योम dim2_tasklet_fn(अचिन्हित दीर्घ data);
अटल DECLARE_TASKLET_OLD(dim2_tasklet, dim2_tasklet_fn);

/**
 * काष्ठा hdm_channel - निजी काष्ठाure to keep channel specअगरic data
 * @is_initialized: identअगरier to know whether the channel is initialized
 * @ch: HAL specअगरic channel data
 * @pending_list: list to keep MBO's beक्रमe starting transfer
 * @started_list: list to keep MBO's after starting transfer
 * @direction: channel direction (TX or RX)
 * @data_type: channel data type
 */
काष्ठा hdm_channel अणु
	अक्षर name[माप "caNNN"];
	bool is_initialized;
	काष्ठा dim_channel ch;
	u16 *reset_dbr_size;
	काष्ठा list_head pending_list;	/* beक्रमe dim_enqueue_buffer() */
	काष्ठा list_head started_list;	/* after dim_enqueue_buffer() */
	क्रमागत most_channel_direction direction;
	क्रमागत most_channel_data_type data_type;
पूर्ण;

/**
 * काष्ठा dim2_hdm - निजी काष्ठाure to keep पूर्णांकerface specअगरic data
 * @hch: an array of channel specअगरic data
 * @most_अगरace: most पूर्णांकerface काष्ठाure
 * @capabilities: an array of channel capability data
 * @io_base: I/O रेजिस्टर base address
 * @netinfo_task: thपढ़ो to deliver network status
 * @netinfo_रुकोq: रुकोq क्रम the thपढ़ो to sleep
 * @deliver_netinfo: to identअगरy whether network status received
 * @mac_addrs: INIC mac address
 * @link_state: network link state
 * @atx_idx: index of async tx channel
 */
काष्ठा dim2_hdm अणु
	काष्ठा device dev;
	काष्ठा hdm_channel hch[DMA_CHANNELS];
	काष्ठा most_channel_capability capabilities[DMA_CHANNELS];
	काष्ठा most_पूर्णांकerface most_अगरace;
	अक्षर name[16 + माप "dim2-"];
	व्योम __iomem *io_base;
	u8 clk_speed;
	काष्ठा clk *clk;
	काष्ठा clk *clk_pll;
	काष्ठा task_काष्ठा *netinfo_task;
	रुको_queue_head_t netinfo_रुकोq;
	पूर्णांक deliver_netinfo;
	अचिन्हित अक्षर mac_addrs[6];
	अचिन्हित अक्षर link_state;
	पूर्णांक atx_idx;
	काष्ठा medialb_bus bus;
	व्योम (*on_netinfo)(काष्ठा most_पूर्णांकerface *most_अगरace,
			   अचिन्हित अक्षर link_state, अचिन्हित अक्षर *addrs);
	व्योम (*disable_platक्रमm)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

काष्ठा dim2_platक्रमm_data अणु
	पूर्णांक (*enable)(काष्ठा platक्रमm_device *pdev);
	व्योम (*disable)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

#घोषणा अगरace_to_hdm(अगरace) container_of(अगरace, काष्ठा dim2_hdm, most_अगरace)

/* Macro to identअगरy a network status message */
#घोषणा PACKET_IS_NET_INFO(p)  \
	(((p)[1] == 0x18) && ((p)[2] == 0x05) && ((p)[3] == 0x0C) && \
	 ((p)[13] == 0x3C) && ((p)[14] == 0x00) && ((p)[15] == 0x0A))

bool dim2_sysfs_get_state_cb(व्योम)
अणु
	bool state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dim_lock, flags);
	state = dim_get_lock_state();
	spin_unlock_irqrestore(&dim_lock, flags);

	वापस state;
पूर्ण

/**
 * dimcb_on_error - callback from HAL to report miscommunication between
 * HDM and HAL
 * @error_id: Error ID
 * @error_message: Error message. Some text in a मुक्त क्रमmat
 */
व्योम dimcb_on_error(u8 error_id, स्थिर अक्षर *error_message)
अणु
	pr_err("%s: error_id - %d, error_message - %s\n", __func__, error_id,
	       error_message);
पूर्ण

/**
 * try_start_dim_transfer - try to transfer a buffer on a channel
 * @hdm_ch: channel specअगरic data
 *
 * Transfer a buffer from pending_list अगर the channel is पढ़ोy
 */
अटल पूर्णांक try_start_dim_transfer(काष्ठा hdm_channel *hdm_ch)
अणु
	u16 buf_size;
	काष्ठा list_head *head = &hdm_ch->pending_list;
	काष्ठा mbo *mbo;
	अचिन्हित दीर्घ flags;
	काष्ठा dim_ch_state_t st;

	BUG_ON(!hdm_ch);
	BUG_ON(!hdm_ch->is_initialized);

	spin_lock_irqsave(&dim_lock, flags);
	अगर (list_empty(head)) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		वापस -EAGAIN;
	पूर्ण

	अगर (!dim_get_channel_state(&hdm_ch->ch, &st)->पढ़ोy) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		वापस -EAGAIN;
	पूर्ण

	mbo = list_first_entry(head, काष्ठा mbo, list);
	buf_size = mbo->buffer_length;

	अगर (dim_dbr_space(&hdm_ch->ch) < buf_size) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		वापस -EAGAIN;
	पूर्ण

	BUG_ON(mbo->bus_address == 0);
	अगर (!dim_enqueue_buffer(&hdm_ch->ch, mbo->bus_address, buf_size)) अणु
		list_del(head->next);
		spin_unlock_irqrestore(&dim_lock, flags);
		mbo->processed_length = 0;
		mbo->status = MBO_E_INVAL;
		mbo->complete(mbo);
		वापस -EFAULT;
	पूर्ण

	list_move_tail(head->next, &hdm_ch->started_list);
	spin_unlock_irqrestore(&dim_lock, flags);

	वापस 0;
पूर्ण

/**
 * deliver_netinfo_thपढ़ो - thपढ़ो to deliver network status to mostcore
 * @data: निजी data
 *
 * Wait क्रम network status and deliver it to mostcore once it is received
 */
अटल पूर्णांक deliver_netinfo_thपढ़ो(व्योम *data)
अणु
	काष्ठा dim2_hdm *dev = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		रुको_event_पूर्णांकerruptible(dev->netinfo_रुकोq,
					 dev->deliver_netinfo ||
					 kthपढ़ो_should_stop());

		अगर (dev->deliver_netinfo) अणु
			dev->deliver_netinfo--;
			अगर (dev->on_netinfo) अणु
				dev->on_netinfo(&dev->most_अगरace,
						dev->link_state,
						dev->mac_addrs);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * retrieve_netinfo - retrieve network status from received buffer
 * @dev: निजी data
 * @mbo: received MBO
 *
 * Parse the message in buffer and get node address, link state, MAC address.
 * Wake up a thपढ़ो to deliver this status to mostcore
 */
अटल व्योम retrieve_netinfo(काष्ठा dim2_hdm *dev, काष्ठा mbo *mbo)
अणु
	u8 *data = mbo->virt_address;

	pr_info("Node Address: 0x%03x\n", (u16)data[16] << 8 | data[17]);
	dev->link_state = data[18];
	pr_info("NIState: %d\n", dev->link_state);
	स_नकल(dev->mac_addrs, data + 19, 6);
	dev->deliver_netinfo++;
	wake_up_पूर्णांकerruptible(&dev->netinfo_रुकोq);
पूर्ण

/**
 * service_करोne_flag - handle completed buffers
 * @dev: निजी data
 * @ch_idx: channel index
 *
 * Return back the completed buffers to mostcore, using completion callback
 */
अटल व्योम service_करोne_flag(काष्ठा dim2_hdm *dev, पूर्णांक ch_idx)
अणु
	काष्ठा hdm_channel *hdm_ch = dev->hch + ch_idx;
	काष्ठा dim_ch_state_t st;
	काष्ठा list_head *head;
	काष्ठा mbo *mbo;
	पूर्णांक करोne_buffers;
	अचिन्हित दीर्घ flags;
	u8 *data;

	BUG_ON(!hdm_ch);
	BUG_ON(!hdm_ch->is_initialized);

	spin_lock_irqsave(&dim_lock, flags);

	करोne_buffers = dim_get_channel_state(&hdm_ch->ch, &st)->करोne_buffers;
	अगर (!करोne_buffers) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		वापस;
	पूर्ण

	अगर (!dim_detach_buffers(&hdm_ch->ch, करोne_buffers)) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dim_lock, flags);

	head = &hdm_ch->started_list;

	जबतक (करोne_buffers) अणु
		spin_lock_irqsave(&dim_lock, flags);
		अगर (list_empty(head)) अणु
			spin_unlock_irqrestore(&dim_lock, flags);
			pr_crit("hard error: started_mbo list is empty whereas DIM2 has sent buffers\n");
			अवरोध;
		पूर्ण

		mbo = list_first_entry(head, काष्ठा mbo, list);
		list_del(head->next);
		spin_unlock_irqrestore(&dim_lock, flags);

		data = mbo->virt_address;

		अगर (hdm_ch->data_type == MOST_CH_ASYNC &&
		    hdm_ch->direction == MOST_CH_RX &&
		    PACKET_IS_NET_INFO(data)) अणु
			retrieve_netinfo(dev, mbo);

			spin_lock_irqsave(&dim_lock, flags);
			list_add_tail(&mbo->list, &hdm_ch->pending_list);
			spin_unlock_irqrestore(&dim_lock, flags);
		पूर्ण अन्यथा अणु
			अगर (hdm_ch->data_type == MOST_CH_CONTROL ||
			    hdm_ch->data_type == MOST_CH_ASYNC) अणु
				u32 स्थिर data_size =
					(u32)data[0] * 256 + data[1] + 2;

				mbo->processed_length =
					min_t(u32, data_size,
					      mbo->buffer_length);
			पूर्ण अन्यथा अणु
				mbo->processed_length = mbo->buffer_length;
			पूर्ण
			mbo->status = MBO_SUCCESS;
			mbo->complete(mbo);
		पूर्ण

		करोne_buffers--;
	पूर्ण
पूर्ण

अटल काष्ठा dim_channel **get_active_channels(काष्ठा dim2_hdm *dev,
						काष्ठा dim_channel **buffer)
अणु
	पूर्णांक idx = 0;
	पूर्णांक ch_idx;

	क्रम (ch_idx = 0; ch_idx < DMA_CHANNELS; ch_idx++) अणु
		अगर (dev->hch[ch_idx].is_initialized)
			buffer[idx++] = &dev->hch[ch_idx].ch;
	पूर्ण
	buffer[idx++] = शून्य;

	वापस buffer;
पूर्ण

अटल irqवापस_t dim2_mlb_isr(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा dim2_hdm *dev = _dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dim_lock, flags);
	dim_service_mlb_पूर्णांक_irq();
	spin_unlock_irqrestore(&dim_lock, flags);

	अगर (dev->atx_idx >= 0 && dev->hch[dev->atx_idx].is_initialized)
		जबतक (!try_start_dim_transfer(dev->hch + dev->atx_idx))
			जारी;

	वापस IRQ_HANDLED;
पूर्ण

/**
 * dim2_tasklet_fn - tasklet function
 * @data: निजी data
 *
 * Service each initialized channel, अगर needed
 */
अटल व्योम dim2_tasklet_fn(अचिन्हित दीर्घ data)
अणु
	काष्ठा dim2_hdm *dev = (काष्ठा dim2_hdm *)data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ch_idx;

	क्रम (ch_idx = 0; ch_idx < DMA_CHANNELS; ch_idx++) अणु
		अगर (!dev->hch[ch_idx].is_initialized)
			जारी;

		spin_lock_irqsave(&dim_lock, flags);
		dim_service_channel(&dev->hch[ch_idx].ch);
		spin_unlock_irqrestore(&dim_lock, flags);

		service_करोne_flag(dev, ch_idx);
		जबतक (!try_start_dim_transfer(dev->hch + ch_idx))
			जारी;
	पूर्ण
पूर्ण

/**
 * dim2_ahb_isr - पूर्णांकerrupt service routine
 * @irq: irq number
 * @_dev: निजी data
 *
 * Acknowledge the पूर्णांकerrupt and schedule a tasklet to service channels.
 * Return IRQ_HANDLED.
 */
अटल irqवापस_t dim2_ahb_isr(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा dim2_hdm *dev = _dev;
	काष्ठा dim_channel *buffer[DMA_CHANNELS + 1];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dim_lock, flags);
	dim_service_ahb_पूर्णांक_irq(get_active_channels(dev, buffer));
	spin_unlock_irqrestore(&dim_lock, flags);

	dim2_tasklet.data = (अचिन्हित दीर्घ)dev;
	tasklet_schedule(&dim2_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * complete_all_mbos - complete MBO's in a list
 * @head: list head
 *
 * Delete all the entries in list and वापस back MBO's to mostcore using
 * completion call back.
 */
अटल व्योम complete_all_mbos(काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mbo *mbo;

	क्रम (;;) अणु
		spin_lock_irqsave(&dim_lock, flags);
		अगर (list_empty(head)) अणु
			spin_unlock_irqrestore(&dim_lock, flags);
			अवरोध;
		पूर्ण

		mbo = list_first_entry(head, काष्ठा mbo, list);
		list_del(head->next);
		spin_unlock_irqrestore(&dim_lock, flags);

		mbo->processed_length = 0;
		mbo->status = MBO_E_CLOSE;
		mbo->complete(mbo);
	पूर्ण
पूर्ण

/**
 * configure_channel - initialize a channel
 * @अगरace: पूर्णांकerface the channel beदीर्घs to
 * @channel: channel to be configured
 * @channel_config: काष्ठाure that holds the configuration inक्रमmation
 *
 * Receives configuration inक्रमmation from mostcore and initialize
 * the corresponding channel. Return 0 on success, negative on failure.
 */
अटल पूर्णांक configure_channel(काष्ठा most_पूर्णांकerface *most_अगरace, पूर्णांक ch_idx,
			     काष्ठा most_channel_config *ccfg)
अणु
	काष्ठा dim2_hdm *dev = अगरace_to_hdm(most_अगरace);
	bool स्थिर is_tx = ccfg->direction == MOST_CH_TX;
	u16 स्थिर sub_size = ccfg->subbuffer_size;
	u16 स्थिर buf_size = ccfg->buffer_size;
	u16 new_size;
	अचिन्हित दीर्घ flags;
	u8 hal_ret;
	पूर्णांक स्थिर ch_addr = ch_idx * 2 + 2;
	काष्ठा hdm_channel *स्थिर hdm_ch = dev->hch + ch_idx;

	BUG_ON(ch_idx < 0 || ch_idx >= DMA_CHANNELS);

	अगर (hdm_ch->is_initialized)
		वापस -EPERM;

	/* करो not reset अगर the property was set by user, see poison_channel */
	hdm_ch->reset_dbr_size = ccfg->dbr_size ? शून्य : &ccfg->dbr_size;

	/* zero value is शेष dbr_size, see dim2 hal */
	hdm_ch->ch.dbr_size = ccfg->dbr_size;

	चयन (ccfg->data_type) अणु
	हाल MOST_CH_CONTROL:
		new_size = dim_norm_ctrl_async_buffer_size(buf_size);
		अगर (new_size == 0) अणु
			pr_err("%s: too small buffer size\n", hdm_ch->name);
			वापस -EINVAL;
		पूर्ण
		ccfg->buffer_size = new_size;
		अगर (new_size != buf_size)
			pr_warn("%s: fixed buffer size (%d -> %d)\n",
				hdm_ch->name, buf_size, new_size);
		spin_lock_irqsave(&dim_lock, flags);
		hal_ret = dim_init_control(&hdm_ch->ch, is_tx, ch_addr,
					   is_tx ? new_size * 2 : new_size);
		अवरोध;
	हाल MOST_CH_ASYNC:
		new_size = dim_norm_ctrl_async_buffer_size(buf_size);
		अगर (new_size == 0) अणु
			pr_err("%s: too small buffer size\n", hdm_ch->name);
			वापस -EINVAL;
		पूर्ण
		ccfg->buffer_size = new_size;
		अगर (new_size != buf_size)
			pr_warn("%s: fixed buffer size (%d -> %d)\n",
				hdm_ch->name, buf_size, new_size);
		spin_lock_irqsave(&dim_lock, flags);
		hal_ret = dim_init_async(&hdm_ch->ch, is_tx, ch_addr,
					 is_tx ? new_size * 2 : new_size);
		अवरोध;
	हाल MOST_CH_ISOC:
		new_size = dim_norm_isoc_buffer_size(buf_size, sub_size);
		अगर (new_size == 0) अणु
			pr_err("%s: invalid sub-buffer size or too small buffer size\n",
			       hdm_ch->name);
			वापस -EINVAL;
		पूर्ण
		ccfg->buffer_size = new_size;
		अगर (new_size != buf_size)
			pr_warn("%s: fixed buffer size (%d -> %d)\n",
				hdm_ch->name, buf_size, new_size);
		spin_lock_irqsave(&dim_lock, flags);
		hal_ret = dim_init_isoc(&hdm_ch->ch, is_tx, ch_addr, sub_size);
		अवरोध;
	हाल MOST_CH_SYNC:
		new_size = dim_norm_sync_buffer_size(buf_size, sub_size);
		अगर (new_size == 0) अणु
			pr_err("%s: invalid sub-buffer size or too small buffer size\n",
			       hdm_ch->name);
			वापस -EINVAL;
		पूर्ण
		ccfg->buffer_size = new_size;
		अगर (new_size != buf_size)
			pr_warn("%s: fixed buffer size (%d -> %d)\n",
				hdm_ch->name, buf_size, new_size);
		spin_lock_irqsave(&dim_lock, flags);
		hal_ret = dim_init_sync(&hdm_ch->ch, is_tx, ch_addr, sub_size);
		अवरोध;
	शेष:
		pr_err("%s: configure failed, bad channel type: %d\n",
		       hdm_ch->name, ccfg->data_type);
		वापस -EINVAL;
	पूर्ण

	अगर (hal_ret != DIM_NO_ERROR) अणु
		spin_unlock_irqrestore(&dim_lock, flags);
		pr_err("%s: configure failed (%d), type: %d, is_tx: %d\n",
		       hdm_ch->name, hal_ret, ccfg->data_type, (पूर्णांक)is_tx);
		वापस -ENODEV;
	पूर्ण

	hdm_ch->data_type = ccfg->data_type;
	hdm_ch->direction = ccfg->direction;
	hdm_ch->is_initialized = true;

	अगर (hdm_ch->data_type == MOST_CH_ASYNC &&
	    hdm_ch->direction == MOST_CH_TX &&
	    dev->atx_idx < 0)
		dev->atx_idx = ch_idx;

	spin_unlock_irqrestore(&dim_lock, flags);
	ccfg->dbr_size = hdm_ch->ch.dbr_size;

	वापस 0;
पूर्ण

/**
 * enqueue - enqueue a buffer क्रम data transfer
 * @अगरace: पूर्णांकended पूर्णांकerface
 * @channel: ID of the channel the buffer is पूर्णांकended क्रम
 * @mbo: poपूर्णांकer to the buffer object
 *
 * Push the buffer पूर्णांकo pending_list and try to transfer one buffer from
 * pending_list. Return 0 on success, negative on failure.
 */
अटल पूर्णांक enqueue(काष्ठा most_पूर्णांकerface *most_अगरace, पूर्णांक ch_idx,
		   काष्ठा mbo *mbo)
अणु
	काष्ठा dim2_hdm *dev = अगरace_to_hdm(most_अगरace);
	काष्ठा hdm_channel *hdm_ch = dev->hch + ch_idx;
	अचिन्हित दीर्घ flags;

	BUG_ON(ch_idx < 0 || ch_idx >= DMA_CHANNELS);

	अगर (!hdm_ch->is_initialized)
		वापस -EPERM;

	अगर (mbo->bus_address == 0)
		वापस -EFAULT;

	spin_lock_irqsave(&dim_lock, flags);
	list_add_tail(&mbo->list, &hdm_ch->pending_list);
	spin_unlock_irqrestore(&dim_lock, flags);

	(व्योम)try_start_dim_transfer(hdm_ch);

	वापस 0;
पूर्ण

/**
 * request_netinfo - triggers retrieving of network info
 * @अगरace: poपूर्णांकer to the पूर्णांकerface
 * @channel_id: corresponding channel ID
 *
 * Send a command to INIC which triggers retrieving of network info by means of
 * "Message exchange over MDP/MEP". Return 0 on success, negative on failure.
 */
अटल व्योम request_netinfo(काष्ठा most_पूर्णांकerface *most_अगरace, पूर्णांक ch_idx,
			    व्योम (*on_netinfo)(काष्ठा most_पूर्णांकerface *,
					       अचिन्हित अक्षर, अचिन्हित अक्षर *))
अणु
	काष्ठा dim2_hdm *dev = अगरace_to_hdm(most_अगरace);
	काष्ठा mbo *mbo;
	u8 *data;

	dev->on_netinfo = on_netinfo;
	अगर (!on_netinfo)
		वापस;

	अगर (dev->atx_idx < 0) अणु
		pr_err("Async Tx Not initialized\n");
		वापस;
	पूर्ण

	mbo = most_get_mbo(&dev->most_अगरace, dev->atx_idx, शून्य);
	अगर (!mbo)
		वापस;

	mbo->buffer_length = 5;

	data = mbo->virt_address;

	data[0] = 0x00; /* PML High byte */
	data[1] = 0x03; /* PML Low byte */
	data[2] = 0x02; /* PMHL */
	data[3] = 0x08; /* FPH */
	data[4] = 0x40; /* FMF (FIFO cmd msg - Triggers NAOverMDP) */

	most_submit_mbo(mbo);
पूर्ण

/**
 * poison_channel - poison buffers of a channel
 * @अगरace: poपूर्णांकer to the पूर्णांकerface the channel to be poisoned beदीर्घs to
 * @channel_id: corresponding channel ID
 *
 * Destroy a channel and complete all the buffers in both started_list &
 * pending_list. Return 0 on success, negative on failure.
 */
अटल पूर्णांक poison_channel(काष्ठा most_पूर्णांकerface *most_अगरace, पूर्णांक ch_idx)
अणु
	काष्ठा dim2_hdm *dev = अगरace_to_hdm(most_अगरace);
	काष्ठा hdm_channel *hdm_ch = dev->hch + ch_idx;
	अचिन्हित दीर्घ flags;
	u8 hal_ret;
	पूर्णांक ret = 0;

	BUG_ON(ch_idx < 0 || ch_idx >= DMA_CHANNELS);

	अगर (!hdm_ch->is_initialized)
		वापस -EPERM;

	tasklet_disable(&dim2_tasklet);
	spin_lock_irqsave(&dim_lock, flags);
	hal_ret = dim_destroy_channel(&hdm_ch->ch);
	hdm_ch->is_initialized = false;
	अगर (ch_idx == dev->atx_idx)
		dev->atx_idx = -1;
	spin_unlock_irqrestore(&dim_lock, flags);
	tasklet_enable(&dim2_tasklet);
	अगर (hal_ret != DIM_NO_ERROR) अणु
		pr_err("HAL Failed to close channel %s\n", hdm_ch->name);
		ret = -EFAULT;
	पूर्ण

	complete_all_mbos(&hdm_ch->started_list);
	complete_all_mbos(&hdm_ch->pending_list);
	अगर (hdm_ch->reset_dbr_size)
		*hdm_ch->reset_dbr_size = 0;

	वापस ret;
पूर्ण

अटल व्योम *dma_alloc(काष्ठा mbo *mbo, u32 size)
अणु
	काष्ठा device *dev = mbo->अगरp->driver_dev;

	वापस dma_alloc_coherent(dev, size, &mbo->bus_address, GFP_KERNEL);
पूर्ण

अटल व्योम dma_मुक्त(काष्ठा mbo *mbo, u32 size)
अणु
	काष्ठा device *dev = mbo->अगरp->driver_dev;

	dma_मुक्त_coherent(dev, size, mbo->virt_address, mbo->bus_address);
पूर्ण

अटल स्थिर काष्ठा of_device_id dim2_of_match[];

अटल काष्ठा अणु
	स्थिर अक्षर *घड़ी_speed;
	u8 clk_speed;
पूर्ण clk_mt[] = अणु
	अणु "256fs", CLK_256FS पूर्ण,
	अणु "512fs", CLK_512FS पूर्ण,
	अणु "1024fs", CLK_1024FS पूर्ण,
	अणु "2048fs", CLK_2048FS पूर्ण,
	अणु "3072fs", CLK_3072FS पूर्ण,
	अणु "4096fs", CLK_4096FS पूर्ण,
	अणु "6144fs", CLK_6144FS पूर्ण,
	अणु "8192fs", CLK_8192FS पूर्ण,
पूर्ण;

/**
 * get_dim2_clk_speed - converts string to DIM2 घड़ी speed value
 *
 * @घड़ी_speed: string in the क्रमmat "{NUMBER}fs"
 * @val: poपूर्णांकer to get one of the CLK_अणुNUMBERपूर्णFS values
 *
 * By success stores one of the CLK_अणुNUMBERपूर्णFS in the *val and वापसs 0,
 * otherwise वापसs -EINVAL.
 */
अटल पूर्णांक get_dim2_clk_speed(स्थिर अक्षर *घड़ी_speed, u8 *val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clk_mt); i++) अणु
		अगर (!म_भेद(घड़ी_speed, clk_mt[i].घड़ी_speed)) अणु
			*val = clk_mt[i].clk_speed;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * dim2_probe - dim2 probe handler
 * @pdev: platक्रमm device काष्ठाure
 *
 * Register the dim2 पूर्णांकerface with mostcore and initialize it.
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक dim2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dim2_platक्रमm_data *pdata;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर अक्षर *घड़ी_speed;
	काष्ठा dim2_hdm *dev;
	काष्ठा resource *res;
	पूर्णांक ret, i;
	u8 hal_ret;
	पूर्णांक irq;

	क्रमागत अणु MLB_INT_IDX, AHB0_INT_IDX पूर्ण;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->atx_idx = -1;

	platक्रमm_set_drvdata(pdev, dev);

	ret = of_property_पढ़ो_string(pdev->dev.of_node,
				      "microchip,clock-speed", &घड़ी_speed);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing dt property clock-speed\n");
		वापस ret;
	पूर्ण

	ret = get_dim2_clk_speed(घड़ी_speed, &dev->clk_speed);
	अगर (ret) अणु
		dev_err(&pdev->dev, "bad dt property clock-speed\n");
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->io_base))
		वापस PTR_ERR(dev->io_base);

	of_id = of_match_node(dim2_of_match, pdev->dev.of_node);
	pdata = of_id->data;
	ret = pdata && pdata->enable ? pdata->enable(pdev) : 0;
	अगर (ret)
		वापस ret;

	dev->disable_platक्रमm = pdata ? pdata->disable : शून्य;

	dev_info(&pdev->dev, "sync: num of frames per sub-buffer: %u\n", fcnt);
	hal_ret = dim_startup(dev->io_base, dev->clk_speed, fcnt);
	अगर (hal_ret != DIM_NO_ERROR) अणु
		dev_err(&pdev->dev, "dim_startup failed: %d\n", hal_ret);
		ret = -ENODEV;
		जाओ err_disable_platक्रमm;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, AHB0_INT_IDX);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_shutकरोwn_dim;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, dim2_ahb_isr, 0,
			       "dim2_ahb0_int", dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request ahb0_int irq %d\n", irq);
		जाओ err_shutकरोwn_dim;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, MLB_INT_IDX);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_shutकरोwn_dim;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, dim2_mlb_isr, 0,
			       "dim2_mlb_int", dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request mlb_int irq %d\n", irq);
		जाओ err_shutकरोwn_dim;
	पूर्ण

	init_रुकोqueue_head(&dev->netinfo_रुकोq);
	dev->deliver_netinfo = 0;
	dev->netinfo_task = kthपढ़ो_run(&deliver_netinfo_thपढ़ो, dev,
					"dim2_netinfo");
	अगर (IS_ERR(dev->netinfo_task)) अणु
		ret = PTR_ERR(dev->netinfo_task);
		जाओ err_shutकरोwn_dim;
	पूर्ण

	क्रम (i = 0; i < DMA_CHANNELS; i++) अणु
		काष्ठा most_channel_capability *cap = dev->capabilities + i;
		काष्ठा hdm_channel *hdm_ch = dev->hch + i;

		INIT_LIST_HEAD(&hdm_ch->pending_list);
		INIT_LIST_HEAD(&hdm_ch->started_list);
		hdm_ch->is_initialized = false;
		snम_लिखो(hdm_ch->name, माप(hdm_ch->name), "ca%d", i * 2 + 2);

		cap->name_suffix = hdm_ch->name;
		cap->direction = MOST_CH_RX | MOST_CH_TX;
		cap->data_type = MOST_CH_CONTROL | MOST_CH_ASYNC |
				 MOST_CH_ISOC | MOST_CH_SYNC;
		cap->num_buffers_packet = MAX_BUFFERS_PACKET;
		cap->buffer_size_packet = MAX_BUF_SIZE_PACKET;
		cap->num_buffers_streaming = MAX_BUFFERS_STREAMING;
		cap->buffer_size_streaming = MAX_BUF_SIZE_STREAMING;
	पूर्ण

	अणु
		स्थिर अक्षर *fmt;

		अगर (माप(res->start) == माप(दीर्घ दीर्घ))
			fmt = "dim2-%016llx";
		अन्यथा अगर (माप(res->start) == माप(दीर्घ))
			fmt = "dim2-%016lx";
		अन्यथा
			fmt = "dim2-%016x";

		snम_लिखो(dev->name, माप(dev->name), fmt, res->start);
	पूर्ण

	dev->most_अगरace.पूर्णांकerface = ITYPE_MEDIALB_DIM2;
	dev->most_अगरace.description = dev->name;
	dev->most_अगरace.num_channels = DMA_CHANNELS;
	dev->most_अगरace.channel_vector = dev->capabilities;
	dev->most_अगरace.configure = configure_channel;
	dev->most_अगरace.enqueue = enqueue;
	dev->most_अगरace.dma_alloc = dma_alloc;
	dev->most_अगरace.dma_मुक्त = dma_मुक्त;
	dev->most_अगरace.poison_channel = poison_channel;
	dev->most_अगरace.request_netinfo = request_netinfo;
	dev->most_अगरace.driver_dev = &pdev->dev;
	dev->most_अगरace.dev = &dev->dev;
	dev->dev.init_name = "dim2_state";
	dev->dev.parent = &pdev->dev;

	ret = most_रेजिस्टर_पूर्णांकerface(&dev->most_अगरace);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register MOST interface\n");
		जाओ err_stop_thपढ़ो;
	पूर्ण

	ret = dim2_sysfs_probe(&dev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to create sysfs attribute\n");
		जाओ err_unreg_अगरace;
	पूर्ण

	वापस 0;

err_unreg_अगरace:
	most_deरेजिस्टर_पूर्णांकerface(&dev->most_अगरace);
err_stop_thपढ़ो:
	kthपढ़ो_stop(dev->netinfo_task);
err_shutकरोwn_dim:
	dim_shutकरोwn();
err_disable_platक्रमm:
	अगर (dev->disable_platक्रमm)
		dev->disable_platक्रमm(pdev);

	वापस ret;
पूर्ण

/**
 * dim2_हटाओ - dim2 हटाओ handler
 * @pdev: platक्रमm device काष्ठाure
 *
 * Unरेजिस्टर the पूर्णांकerface from mostcore
 */
अटल पूर्णांक dim2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	dim2_sysfs_destroy(&dev->dev);
	most_deरेजिस्टर_पूर्णांकerface(&dev->most_अगरace);
	kthपढ़ो_stop(dev->netinfo_task);

	spin_lock_irqsave(&dim_lock, flags);
	dim_shutकरोwn();
	spin_unlock_irqrestore(&dim_lock, flags);

	अगर (dev->disable_platक्रमm)
		dev->disable_platक्रमm(pdev);

	वापस 0;
पूर्ण

/* platक्रमm specअगरic functions [[ */

अटल पूर्णांक fsl_mx6_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	dev->clk = devm_clk_get(&pdev->dev, "mlb");
	अगर (IS_ERR_OR_शून्य(dev->clk)) अणु
		dev_err(&pdev->dev, "unable to get mlb clock\n");
		वापस -EFAULT;
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s\n", "clk_prepare_enable failed");
		वापस ret;
	पूर्ण

	अगर (dev->clk_speed >= CLK_2048FS) अणु
		/* enable pll */
		dev->clk_pll = devm_clk_get(&pdev->dev, "pll8_mlb");
		अगर (IS_ERR_OR_शून्य(dev->clk_pll)) अणु
			dev_err(&pdev->dev, "unable to get mlb pll clock\n");
			clk_disable_unprepare(dev->clk);
			वापस -EFAULT;
		पूर्ण

		ग_लिखोl(0x888, dev->io_base + 0x38);
		clk_prepare_enable(dev->clk_pll);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_mx6_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);

	अगर (dev->clk_speed >= CLK_2048FS)
		clk_disable_unprepare(dev->clk_pll);

	clk_disable_unprepare(dev->clk);
पूर्ण

अटल पूर्णांक rcar_h2_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(dev->clk);
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s\n", "clk_prepare_enable failed");
		वापस ret;
	पूर्ण

	अगर (dev->clk_speed >= CLK_2048FS) अणु
		/* enable MLP pll and LVDS drivers */
		ग_लिखोl(0x03, dev->io_base + 0x600);
		/* set bias */
		ग_लिखोl(0x888, dev->io_base + 0x38);
	पूर्ण अन्यथा अणु
		/* PLL */
		ग_लिखोl(0x04, dev->io_base + 0x600);
	पूर्ण


	/* BBCR = 0b11 */
	ग_लिखोl(0x03, dev->io_base + 0x500);
	ग_लिखोl(0x0002FF02, dev->io_base + 0x508);

	वापस 0;
पूर्ण

अटल व्योम rcar_h2_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(dev->clk);

	/* disable PLLs and LVDS drivers */
	ग_लिखोl(0x0, dev->io_base + 0x600);
पूर्ण

अटल पूर्णांक rcar_m3_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);
	u32 enable_512fs = dev->clk_speed == CLK_512FS;
	पूर्णांक ret;

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(dev->clk);
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s\n", "clk_prepare_enable failed");
		वापस ret;
	पूर्ण

	/* PLL */
	ग_लिखोl(0x04, dev->io_base + 0x600);

	ग_लिखोl(enable_512fs, dev->io_base + 0x604);

	/* BBCR = 0b11 */
	ग_लिखोl(0x03, dev->io_base + 0x500);
	ग_लिखोl(0x0002FF02, dev->io_base + 0x508);

	वापस 0;
पूर्ण

अटल व्योम rcar_m3_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dim2_hdm *dev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(dev->clk);

	/* disable PLLs and LVDS drivers */
	ग_लिखोl(0x0, dev->io_base + 0x600);
पूर्ण

/* ]] platक्रमm specअगरic functions */

क्रमागत dim2_platक्रमms अणु FSL_MX6, RCAR_H2, RCAR_M3 पूर्ण;

अटल काष्ठा dim2_platक्रमm_data plat_data[] = अणु
	[FSL_MX6] = अणु .enable = fsl_mx6_enable, .disable = fsl_mx6_disable पूर्ण,
	[RCAR_H2] = अणु .enable = rcar_h2_enable, .disable = rcar_h2_disable पूर्ण,
	[RCAR_M3] = अणु .enable = rcar_m3_enable, .disable = rcar_m3_disable पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dim2_of_match[] = अणु
	अणु
		.compatible = "fsl,imx6q-mlb150",
		.data = plat_data + FSL_MX6
	पूर्ण,
	अणु
		.compatible = "renesas,mlp",
		.data = plat_data + RCAR_H2
	पूर्ण,
	अणु
		.compatible = "rcar,medialb-dim2",
		.data = plat_data + RCAR_M3
	पूर्ण,
	अणु
		.compatible = "xlnx,axi4-os62420_3pin-1.00.a",
	पूर्ण,
	अणु
		.compatible = "xlnx,axi4-os62420_6pin-1.00.a",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dim2_of_match);

अटल काष्ठा platक्रमm_driver dim2_driver = अणु
	.probe = dim2_probe,
	.हटाओ = dim2_हटाओ,
	.driver = अणु
		.name = "hdm_dim2",
		.of_match_table = dim2_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dim2_driver);

MODULE_AUTHOR("Andrey Shvetsov <andrey.shvetsov@k2l.de>");
MODULE_DESCRIPTION("MediaLB DIM2 Hardware Dependent Module");
MODULE_LICENSE("GPL");
