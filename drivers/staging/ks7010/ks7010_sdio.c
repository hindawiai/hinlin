<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Driver क्रम KeyStream, KS7010 based SDIO cards.
 *
 *   Copyright (C) 2006-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 *   Copyright (C) 2016 Sang Engineering, Wolfram Sang
 */

#समावेश <linux/atomic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश "ks_wlan.h"
#समावेश "ks_hostif.h"

#घोषणा ROM_खाता "ks7010sd.rom"

/*  SDIO KeyStream venकरोr and device */
#घोषणा SDIO_VENDOR_ID_KS_CODE_A	0x005b
#घोषणा SDIO_VENDOR_ID_KS_CODE_B	0x0023

/* Older sources suggest earlier versions were named 7910 or 79xx */
#घोषणा SDIO_DEVICE_ID_KS_7010		0x7910

/* Read/Write Status Register */
#घोषणा READ_STATUS_REG		0x000000
#घोषणा WRITE_STATUS_REG	0x00000C
क्रमागत reg_status_type अणु
	REG_STATUS_BUSY,
	REG_STATUS_IDLE
पूर्ण;

/* Read Index Register */
#घोषणा READ_INDEX_REG		0x000004

/* Read Data Size Register */
#घोषणा READ_DATA_SIZE_REG	0x000008

/* Write Index Register */
#घोषणा WRITE_INDEX_REG		0x000010

/*
 * Write Status/Read Data Size Register
 * क्रम network packet (less than 2048 bytes data)
 */
#घोषणा WSTATUS_RSIZE_REG	0x000014

/* Write Status Register value */
#घोषणा WSTATUS_MASK		0x80

/* Read Data Size Register value [10:4] */
#घोषणा RSIZE_MASK		0x7F

/* ARM to SD पूर्णांकerrupt Enable */
#घोषणा INT_ENABLE_REG		0x000020
/* ARM to SD पूर्णांकerrupt Pending */
#घोषणा INT_PENDING_REG		0x000024

#घोषणा INT_GCR_B              BIT(7)
#घोषणा INT_GCR_A              BIT(6)
#घोषणा INT_WRITE_STATUS       BIT(5)
#घोषणा INT_WRITE_INDEX        BIT(4)
#घोषणा INT_WRITE_SIZE         BIT(3)
#घोषणा INT_READ_STATUS        BIT(2)
#घोषणा INT_READ_INDEX         BIT(1)
#घोषणा INT_READ_SIZE          BIT(0)

/* General Communication Register A */
#घोषणा GCR_A_REG		0x000028
क्रमागत gen_com_reg_a अणु
	GCR_A_INIT,
	GCR_A_REMAP,
	GCR_A_RUN
पूर्ण;

/* General Communication Register B */
#घोषणा GCR_B_REG		0x00002C
क्रमागत gen_com_reg_b अणु
	GCR_B_ACTIVE,
	GCR_B_DOZE
पूर्ण;

/* Wakeup Register */
#घोषणा WAKEUP_REG		0x008018
#घोषणा WAKEUP_REQ		0x5a

/* AHB Data Winकरोw  0x010000-0x01FFFF */
#घोषणा DATA_WINDOW		0x010000
#घोषणा WINDOW_SIZE		(64 * 1024)

#घोषणा KS7010_IRAM_ADDRESS	0x06000000

#घोषणा KS7010_IO_BLOCK_SIZE 512

/**
 * काष्ठा ks_sdio_card - SDIO device data.
 *
 * Structure is used as the &काष्ठा sdio_func निजी data.
 *
 * @func: Poपूर्णांकer to the SDIO function device.
 * @priv: Poपूर्णांकer to the &काष्ठा net_device निजी data.
 */
काष्ठा ks_sdio_card अणु
	काष्ठा sdio_func *func;
	काष्ठा ks_wlan_निजी *priv;
पूर्ण;

अटल काष्ठा sdio_func *ks7010_to_func(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा ks_sdio_card *ks_sdio = priv->अगर_hw;

	वापस ks_sdio->func;
पूर्ण

/* Read single byte from device address पूर्णांकo byte (CMD52) */
अटल पूर्णांक ks7010_sdio_पढ़ोb(काष्ठा ks_wlan_निजी *priv,
			     u32 address, u8 *byte)
अणु
	काष्ठा sdio_func *func = ks7010_to_func(priv);
	पूर्णांक ret;

	*byte = sdio_पढ़ोb(func, address, &ret);

	वापस ret;
पूर्ण

/* Read length bytes from device address पूर्णांकo buffer (CMD53) */
अटल पूर्णांक ks7010_sdio_पढ़ो(काष्ठा ks_wlan_निजी *priv, u32 address,
			    u8 *buffer, अचिन्हित पूर्णांक length)
अणु
	काष्ठा sdio_func *func = ks7010_to_func(priv);

	वापस sdio_स_नकल_fromio(func, buffer, address, length);
पूर्ण

/* Write single byte to device address (CMD52) */
अटल पूर्णांक ks7010_sdio_ग_लिखोb(काष्ठा ks_wlan_निजी *priv,
			      u32 address, u8 byte)
अणु
	काष्ठा sdio_func *func = ks7010_to_func(priv);
	पूर्णांक ret;

	sdio_ग_लिखोb(func, byte, address, &ret);

	वापस ret;
पूर्ण

/* Write length bytes to device address from buffer (CMD53) */
अटल पूर्णांक ks7010_sdio_ग_लिखो(काष्ठा ks_wlan_निजी *priv, u32 address,
			     u8 *buffer, अचिन्हित पूर्णांक length)
अणु
	काष्ठा sdio_func *func = ks7010_to_func(priv);

	वापस sdio_स_नकल_toio(func, address, buffer, length);
पूर्ण

अटल व्योम ks_wlan_hw_sleep_करोze_request(काष्ठा ks_wlan_निजी *priv)
अणु
	पूर्णांक ret;

	/* clear request */
	atomic_set(&priv->sleepstatus.करोze_request, 0);

	अगर (atomic_पढ़ो(&priv->sleepstatus.status) == 0) अणु
		ret = ks7010_sdio_ग_लिखोb(priv, GCR_B_REG, GCR_B_DOZE);
		अगर (ret) अणु
			netdev_err(priv->net_dev, "write GCR_B_REG\n");
			जाओ set_sleep_mode;
		पूर्ण
		atomic_set(&priv->sleepstatus.status, 1);
		priv->last_करोze = jअगरfies;
	पूर्ण

set_sleep_mode:
	priv->sleep_mode = atomic_पढ़ो(&priv->sleepstatus.status);
पूर्ण

अटल व्योम ks_wlan_hw_sleep_wakeup_request(काष्ठा ks_wlan_निजी *priv)
अणु
	पूर्णांक ret;

	/* clear request */
	atomic_set(&priv->sleepstatus.wakeup_request, 0);

	अगर (atomic_पढ़ो(&priv->sleepstatus.status) == 1) अणु
		ret = ks7010_sdio_ग_लिखोb(priv, WAKEUP_REG, WAKEUP_REQ);
		अगर (ret) अणु
			netdev_err(priv->net_dev, "write WAKEUP_REG\n");
			जाओ set_sleep_mode;
		पूर्ण
		atomic_set(&priv->sleepstatus.status, 0);
		priv->last_wakeup = jअगरfies;
		++priv->wakeup_count;
	पूर्ण

set_sleep_mode:
	priv->sleep_mode = atomic_पढ़ो(&priv->sleepstatus.status);
पूर्ण

व्योम ks_wlan_hw_wakeup_request(काष्ठा ks_wlan_निजी *priv)
अणु
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
		ret = ks7010_sdio_ग_लिखोb(priv, WAKEUP_REG, WAKEUP_REQ);
		अगर (ret)
			netdev_err(priv->net_dev, "write WAKEUP_REG\n");

		priv->last_wakeup = jअगरfies;
		++priv->wakeup_count;
	पूर्ण
पूर्ण

अटल व्योम _ks_wlan_hw_घातer_save(काष्ठा ks_wlan_निजी *priv)
अणु
	u8 byte;
	पूर्णांक ret;

	अगर (priv->reg.घातer_mgmt == POWER_MGMT_ACTIVE)
		वापस;

	अगर (priv->reg.operation_mode != MODE_INFRASTRUCTURE)
		वापस;

	अगर (!is_connect_status(priv->connect_status))
		वापस;

	अगर (priv->dev_state != DEVICE_STATE_SLEEP)
		वापस;

	अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE)
		वापस;

	netdev_dbg(priv->net_dev,
		   "STATUS:\n"
		   "- psstatus.status = %d\n"
		   "- psstatus.confirm_wait = %d\n"
		   "- psstatus.snooze_guard = %d\n"
		   "- txq_count = %d\n",
		   atomic_पढ़ो(&priv->psstatus.status),
		   atomic_पढ़ो(&priv->psstatus.confirm_रुको),
		   atomic_पढ़ो(&priv->psstatus.snooze_guard),
		   txq_count(priv));

	अगर (atomic_पढ़ो(&priv->psstatus.confirm_रुको) ||
	    atomic_पढ़ो(&priv->psstatus.snooze_guard) ||
	    txq_has_space(priv)) अणु
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
		वापस;
	पूर्ण

	ret = ks7010_sdio_पढ़ोb(priv, INT_PENDING_REG, &byte);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "read INT_PENDING_REG\n");
		जाओ queue_delayed_work;
	पूर्ण
	अगर (byte)
		जाओ queue_delayed_work;

	ret = ks7010_sdio_ग_लिखोb(priv, GCR_B_REG, GCR_B_DOZE);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "write GCR_B_REG\n");
		जाओ queue_delayed_work;
	पूर्ण
	atomic_set(&priv->psstatus.status, PS_SNOOZE);

	वापस;

queue_delayed_work:
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
पूर्ण

पूर्णांक ks_wlan_hw_घातer_save(काष्ठा ks_wlan_निजी *priv)
अणु
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक enqueue_txdev(काष्ठा ks_wlan_निजी *priv, अचिन्हित अक्षर *p,
			 अचिन्हित दीर्घ size,
			 व्योम (*complete_handler)(काष्ठा ks_wlan_निजी *priv,
						  काष्ठा sk_buff *skb),
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा tx_device_buffer *sp;
	पूर्णांक ret;

	अगर (priv->dev_state < DEVICE_STATE_BOOT) अणु
		ret = -EPERM;
		जाओ err_complete;
	पूर्ण

	अगर ((TX_DEVICE_BUFF_SIZE - 1) <= txq_count(priv)) अणु
		netdev_err(priv->net_dev, "tx buffer overflow\n");
		ret = -EOVERFLOW;
		जाओ err_complete;
	पूर्ण

	sp = &priv->tx_dev.tx_dev_buff[priv->tx_dev.qtail];
	sp->sendp = p;
	sp->size = size;
	sp->complete_handler = complete_handler;
	sp->skb = skb;
	inc_txqtail(priv);

	वापस 0;

err_complete:
	kमुक्त(p);
	अगर (complete_handler)
		(*complete_handler)(priv, skb);

	वापस ret;
पूर्ण

/* ग_लिखो data */
अटल पूर्णांक ग_लिखो_to_device(काष्ठा ks_wlan_निजी *priv, u8 *buffer,
			   अचिन्हित दीर्घ size)
अणु
	काष्ठा hostअगर_hdr *hdr;
	पूर्णांक ret;

	hdr = (काष्ठा hostअगर_hdr *)buffer;

	अगर (le16_to_cpu(hdr->event) < HIF_DATA_REQ ||
	    le16_to_cpu(hdr->event) > HIF_REQ_MAX) अणु
		netdev_err(priv->net_dev, "unknown event=%04X\n", hdr->event);
		वापस 0;
	पूर्ण

	ret = ks7010_sdio_ग_लिखो(priv, DATA_WINDOW, buffer, size);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "write DATA_WINDOW\n");
		वापस ret;
	पूर्ण

	ret = ks7010_sdio_ग_लिखोb(priv, WRITE_STATUS_REG, REG_STATUS_BUSY);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "write WRITE_STATUS_REG\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tx_device_task(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा tx_device_buffer *sp;
	पूर्णांक ret;

	अगर (!txq_has_space(priv) ||
	    atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE)
		वापस;

	sp = &priv->tx_dev.tx_dev_buff[priv->tx_dev.qhead];
	अगर (priv->dev_state >= DEVICE_STATE_BOOT) अणु
		ret = ग_लिखो_to_device(priv, sp->sendp, sp->size);
		अगर (ret) अणु
			netdev_err(priv->net_dev,
				   "write_to_device error !!(%d)\n", ret);
			queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
			वापस;
		पूर्ण
	पूर्ण
	kमुक्त(sp->sendp);
	अगर (sp->complete_handler)	/* TX Complete */
		(*sp->complete_handler)(priv, sp->skb);
	inc_txqhead(priv);

	अगर (txq_has_space(priv))
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
पूर्ण

पूर्णांक ks_wlan_hw_tx(काष्ठा ks_wlan_निजी *priv, व्योम *p, अचिन्हित दीर्घ size,
		  व्योम (*complete_handler)(काष्ठा ks_wlan_निजी *priv,
					   काष्ठा sk_buff *skb),
		  काष्ठा sk_buff *skb)
अणु
	पूर्णांक result;
	काष्ठा hostअगर_hdr *hdr;

	hdr = (काष्ठा hostअगर_hdr *)p;

	अगर (le16_to_cpu(hdr->event) < HIF_DATA_REQ ||
	    le16_to_cpu(hdr->event) > HIF_REQ_MAX) अणु
		netdev_err(priv->net_dev, "unknown event=%04X\n", hdr->event);
		वापस 0;
	पूर्ण

	/* add event to hostt buffer */
	priv->hostt.buff[priv->hostt.qtail] = le16_to_cpu(hdr->event);
	priv->hostt.qtail = (priv->hostt.qtail + 1) % SME_EVENT_BUFF_SIZE;

	spin_lock(&priv->tx_dev.tx_dev_lock);
	result = enqueue_txdev(priv, p, size, complete_handler, skb);
	spin_unlock(&priv->tx_dev.tx_dev_lock);

	अगर (txq_has_space(priv))
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);

	वापस result;
पूर्ण

अटल व्योम rx_event_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ks_wlan_निजी *priv = from_tasklet(priv, t, rx_bh_task);
	काष्ठा rx_device_buffer *rp;

	अगर (rxq_has_space(priv) && priv->dev_state >= DEVICE_STATE_BOOT) अणु
		rp = &priv->rx_dev.rx_dev_buff[priv->rx_dev.qhead];
		hostअगर_receive(priv, rp->data, rp->size);
		inc_rxqhead(priv);

		अगर (rxq_has_space(priv))
			tasklet_schedule(&priv->rx_bh_task);
	पूर्ण
पूर्ण

अटल व्योम ks_wlan_hw_rx(काष्ठा ks_wlan_निजी *priv, माप_प्रकार size)
अणु
	पूर्णांक ret;
	काष्ठा rx_device_buffer *rx_buffer;
	काष्ठा hostअगर_hdr *hdr;
	u16 event = 0;

	/* receive data */
	अगर (rxq_count(priv) >= (RX_DEVICE_BUFF_SIZE - 1)) अणु
		netdev_err(priv->net_dev, "rx buffer overflow\n");
		वापस;
	पूर्ण
	rx_buffer = &priv->rx_dev.rx_dev_buff[priv->rx_dev.qtail];

	ret = ks7010_sdio_पढ़ो(priv, DATA_WINDOW, &rx_buffer->data[0],
			       hअगर_align_size(size));
	अगर (ret)
		वापस;

	/* length check */
	अगर (size > 2046 || size == 0) अणु
#अगर_घोषित DEBUG
		prपूर्णांक_hex_dump_bytes("INVALID DATA dump: ",
				     DUMP_PREFIX_OFFSET,
				     rx_buffer->data, 32);
#पूर्ण_अगर
		ret = ks7010_sdio_ग_लिखोb(priv, READ_STATUS_REG,
					 REG_STATUS_IDLE);
		अगर (ret)
			netdev_err(priv->net_dev, "write READ_STATUS_REG\n");

		/* length check fail */
		वापस;
	पूर्ण

	hdr = (काष्ठा hostअगर_hdr *)&rx_buffer->data[0];
	rx_buffer->size = le16_to_cpu(hdr->size) + माप(hdr->size);
	event = le16_to_cpu(hdr->event);
	inc_rxqtail(priv);

	ret = ks7010_sdio_ग_लिखोb(priv, READ_STATUS_REG, REG_STATUS_IDLE);
	अगर (ret)
		netdev_err(priv->net_dev, "write READ_STATUS_REG\n");

	अगर (atomic_पढ़ो(&priv->psstatus.confirm_रुको) && is_hअगर_conf(event)) अणु
		netdev_dbg(priv->net_dev, "IS_HIF_CONF true !!\n");
		atomic_dec(&priv->psstatus.confirm_रुको);
	पूर्ण

	tasklet_schedule(&priv->rx_bh_task);
पूर्ण

अटल व्योम ks7010_rw_function(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ks_wlan_निजी *priv = container_of(work,
						    काष्ठा ks_wlan_निजी,
						    rw_dwork.work);
	काष्ठा sdio_func *func = ks7010_to_func(priv);
	u8 byte;
	पूर्णांक ret;

	/* रुको after DOZE */
	अगर (समय_after(priv->last_करोze + msecs_to_jअगरfies(30), jअगरfies)) अणु
		netdev_dbg(priv->net_dev, "wait after DOZE\n");
		queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
		वापस;
	पूर्ण

	/* रुको after WAKEUP */
	जबतक (समय_after(priv->last_wakeup + msecs_to_jअगरfies(30), jअगरfies)) अणु
		netdev_dbg(priv->net_dev, "wait after WAKEUP\n");
		dev_info(&func->dev, "wake: %lu %lu\n",
			 priv->last_wakeup + msecs_to_jअगरfies(30), jअगरfies);
		msleep(30);
	पूर्ण

	sdio_claim_host(func);

	/* घातer save wakeup */
	अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
		अगर (txq_has_space(priv)) अणु
			ks_wlan_hw_wakeup_request(priv);
			queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
		पूर्ण
		जाओ release_host;
	पूर्ण

	/* sleep mode करोze */
	अगर (atomic_पढ़ो(&priv->sleepstatus.करोze_request) == 1) अणु
		ks_wlan_hw_sleep_करोze_request(priv);
		जाओ release_host;
	पूर्ण
	/* sleep mode wakeup */
	अगर (atomic_पढ़ो(&priv->sleepstatus.wakeup_request) == 1) अणु
		ks_wlan_hw_sleep_wakeup_request(priv);
		जाओ release_host;
	पूर्ण

	/* पढ़ो (WriteStatus/ReadDataSize FN1:00_0014) */
	ret = ks7010_sdio_पढ़ोb(priv, WSTATUS_RSIZE_REG, &byte);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "read WSTATUS_RSIZE_REG psstatus=%d\n",
			   atomic_पढ़ो(&priv->psstatus.status));
		जाओ release_host;
	पूर्ण

	अगर (byte & RSIZE_MASK) अणु	/* Read schedule */
		ks_wlan_hw_rx(priv, (माप_प्रकार)((byte & RSIZE_MASK) << 4));
	पूर्ण
	अगर ((byte & WSTATUS_MASK))
		tx_device_task(priv);

	_ks_wlan_hw_घातer_save(priv);

release_host:
	sdio_release_host(func);
पूर्ण

अटल व्योम ks_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	काष्ठा ks_sdio_card *card;
	काष्ठा ks_wlan_निजी *priv;
	u8 status, rsize, byte;

	card = sdio_get_drvdata(func);
	priv = card->priv;

	अगर (priv->dev_state < DEVICE_STATE_BOOT)
		जाओ queue_delayed_work;

	ret = ks7010_sdio_पढ़ोb(priv, INT_PENDING_REG, &status);
	अगर (ret) अणु
		netdev_err(priv->net_dev, "read INT_PENDING_REG\n");
		जाओ queue_delayed_work;
	पूर्ण

	/* schedule task क्रम पूर्णांकerrupt status */
	/* bit7 -> Write General Communication B रेजिस्टर */
	/* पढ़ो (General Communication B रेजिस्टर) */
	/* bit5 -> Write Status Idle */
	/* bit2 -> Read Status Busy  */
	अगर (status & INT_GCR_B ||
	    atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
		ret = ks7010_sdio_पढ़ोb(priv, GCR_B_REG, &byte);
		अगर (ret) अणु
			netdev_err(priv->net_dev, "read GCR_B_REG\n");
			जाओ queue_delayed_work;
		पूर्ण
		अगर (byte == GCR_B_ACTIVE) अणु
			अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
				atomic_set(&priv->psstatus.status, PS_WAKEUP);
				priv->wakeup_count = 0;
			पूर्ण
			complete(&priv->psstatus.wakeup_रुको);
		पूर्ण
	पूर्ण

	करो अणु
		/* पढ़ो (WriteStatus/ReadDataSize FN1:00_0014) */
		ret = ks7010_sdio_पढ़ोb(priv, WSTATUS_RSIZE_REG, &byte);
		अगर (ret) अणु
			netdev_err(priv->net_dev, "read WSTATUS_RSIZE_REG\n");
			जाओ queue_delayed_work;
		पूर्ण
		rsize = byte & RSIZE_MASK;
		अगर (rsize != 0)		/* Read schedule */
			ks_wlan_hw_rx(priv, (माप_प्रकार)(rsize << 4));

		अगर (byte & WSTATUS_MASK) अणु
			अगर (atomic_पढ़ो(&priv->psstatus.status) == PS_SNOOZE) अणु
				अगर (txq_has_space(priv)) अणु
					ks_wlan_hw_wakeup_request(priv);
					queue_delayed_work(priv->wq,
							   &priv->rw_dwork, 1);
					वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				tx_device_task(priv);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (rsize);

queue_delayed_work:
	queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
पूर्ण

अटल पूर्णांक trx_device_init(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->tx_dev.qhead = 0;
	priv->tx_dev.qtail = 0;

	priv->rx_dev.qhead = 0;
	priv->rx_dev.qtail = 0;

	spin_lock_init(&priv->tx_dev.tx_dev_lock);
	spin_lock_init(&priv->rx_dev.rx_dev_lock);

	tasklet_setup(&priv->rx_bh_task, rx_event_task);

	वापस 0;
पूर्ण

अटल व्योम trx_device_निकास(काष्ठा ks_wlan_निजी *priv)
अणु
	काष्ठा tx_device_buffer *sp;

	/* tx buffer clear */
	जबतक (txq_has_space(priv)) अणु
		sp = &priv->tx_dev.tx_dev_buff[priv->tx_dev.qhead];
		kमुक्त(sp->sendp);
		अगर (sp->complete_handler)	/* TX Complete */
			(*sp->complete_handler)(priv, sp->skb);
		inc_txqhead(priv);
	पूर्ण

	tasklet_समाप्त(&priv->rx_bh_task);
पूर्ण

अटल पूर्णांक ks7010_sdio_update_index(काष्ठा ks_wlan_निजी *priv, u32 index)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर *data_buf;

	data_buf = kmemdup(&index, माप(u32), GFP_KERNEL);
	अगर (!data_buf)
		वापस -ENOMEM;

	ret = ks7010_sdio_ग_लिखो(priv, WRITE_INDEX_REG, data_buf, माप(index));
	अगर (ret)
		जाओ err_मुक्त_data_buf;

	ret = ks7010_sdio_ग_लिखो(priv, READ_INDEX_REG, data_buf, माप(index));
	अगर (ret)
		जाओ err_मुक्त_data_buf;

	वापस 0;

err_मुक्त_data_buf:
	kमुक्त(data_buf);

	वापस ret;
पूर्ण

#घोषणा ROM_BUFF_SIZE (64 * 1024)
अटल पूर्णांक ks7010_sdio_data_compare(काष्ठा ks_wlan_निजी *priv, u32 address,
				    u8 *data, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;
	u8 *पढ़ो_buf;

	पढ़ो_buf = kदो_स्मृति(ROM_BUFF_SIZE, GFP_KERNEL);
	अगर (!पढ़ो_buf)
		वापस -ENOMEM;

	ret = ks7010_sdio_पढ़ो(priv, address, पढ़ो_buf, size);
	अगर (ret)
		जाओ err_मुक्त_पढ़ो_buf;

	अगर (स_भेद(data, पढ़ो_buf, size) != 0) अणु
		ret = -EIO;
		netdev_err(priv->net_dev, "data compare error (%d)\n", ret);
		जाओ err_मुक्त_पढ़ो_buf;
	पूर्ण

	वापस 0;

err_मुक्त_पढ़ो_buf:
	kमुक्त(पढ़ो_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक ks7010_copy_firmware(काष्ठा ks_wlan_निजी *priv,
				स्थिर काष्ठा firmware *fw_entry)
अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक n = 0;
	u8 *rom_buf;
	पूर्णांक ret;

	rom_buf = kदो_स्मृति(ROM_BUFF_SIZE, GFP_KERNEL);
	अगर (!rom_buf)
		वापस -ENOMEM;

	length = fw_entry->size;

	करो अणु
		अगर (length >= ROM_BUFF_SIZE) अणु
			size = ROM_BUFF_SIZE;
			length = length - ROM_BUFF_SIZE;
		पूर्ण अन्यथा अणु
			size = length;
			length = 0;
		पूर्ण
		अगर (size == 0)
			अवरोध;

		स_नकल(rom_buf, fw_entry->data + n, size);

		offset = n;
		ret = ks7010_sdio_update_index(priv,
					       KS7010_IRAM_ADDRESS + offset);
		अगर (ret)
			जाओ मुक्त_rom_buf;

		ret = ks7010_sdio_ग_लिखो(priv, DATA_WINDOW, rom_buf, size);
		अगर (ret)
			जाओ मुक्त_rom_buf;

		ret = ks7010_sdio_data_compare(priv,
					       DATA_WINDOW, rom_buf, size);
		अगर (ret)
			जाओ मुक्त_rom_buf;

		n += size;

	पूर्ण जबतक (size);

	ret = ks7010_sdio_ग_लिखोb(priv, GCR_A_REG, GCR_A_REMAP);

मुक्त_rom_buf:
	kमुक्त(rom_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ks7010_upload_firmware(काष्ठा ks_sdio_card *card)
अणु
	काष्ठा ks_wlan_निजी *priv = card->priv;
	काष्ठा sdio_func *func = ks7010_to_func(priv);
	अचिन्हित पूर्णांक n;
	u8 byte = 0;
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw_entry = शून्य;

	sdio_claim_host(func);

	/* Firmware running ? */
	ret = ks7010_sdio_पढ़ोb(priv, GCR_A_REG, &byte);
	अगर (ret)
		जाओ release_host;
	अगर (byte == GCR_A_RUN) अणु
		netdev_dbg(priv->net_dev, "MAC firmware running ...\n");
		ret = -EBUSY;
		जाओ release_host;
	पूर्ण

	ret = request_firmware(&fw_entry, ROM_खाता,
			       &func->dev);
	अगर (ret)
		जाओ release_host;

	ret = ks7010_copy_firmware(priv, fw_entry);
	अगर (ret)
		जाओ release_firmware;

	/* Firmware running check */
	क्रम (n = 0; n < 50; ++n) अणु
		usleep_range(10000, 11000);	/* रुको_ms(10); */
		ret = ks7010_sdio_पढ़ोb(priv, GCR_A_REG, &byte);
		अगर (ret)
			जाओ release_firmware;

		अगर (byte == GCR_A_RUN)
			अवरोध;
	पूर्ण
	अगर ((50) <= n) अणु
		netdev_err(priv->net_dev, "firmware can't start\n");
		ret = -EIO;
		जाओ release_firmware;
	पूर्ण

	ret = 0;

 release_firmware:
	release_firmware(fw_entry);
 release_host:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल व्योम ks7010_sme_enqueue_events(काष्ठा ks_wlan_निजी *priv)
अणु
	अटल स्थिर u16 init_events[] = अणु
		SME_GET_EEPROM_CKSUM, SME_STOP_REQUEST,
		SME_RTS_THRESHOLD_REQUEST, SME_FRAGMENTATION_THRESHOLD_REQUEST,
		SME_WEP_INDEX_REQUEST, SME_WEP_KEY1_REQUEST,
		SME_WEP_KEY2_REQUEST, SME_WEP_KEY3_REQUEST,
		SME_WEP_KEY4_REQUEST, SME_WEP_FLAG_REQUEST,
		SME_RSN_ENABLED_REQUEST, SME_MODE_SET_REQUEST,
		SME_START_REQUEST
	पूर्ण;
	पूर्णांक ev;

	क्रम (ev = 0; ev < ARRAY_SIZE(init_events); ev++)
		hostअगर_sme_enqueue(priv, init_events[ev]);
पूर्ण

अटल व्योम ks7010_card_init(काष्ठा ks_wlan_निजी *priv)
अणु
	init_completion(&priv->confirm_रुको);

	/* get mac address & firmware version */
	hostअगर_sme_enqueue(priv, SME_START);

	अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout
	    (&priv->confirm_रुको, 5 * HZ)) अणु
		netdev_dbg(priv->net_dev, "wait time out!! SME_START\n");
	पूर्ण

	अगर (priv->mac_address_valid && priv->version_size != 0)
		priv->dev_state = DEVICE_STATE_PREINIT;

	ks7010_sme_enqueue_events(priv);

	अगर (!रुको_क्रम_completion_पूर्णांकerruptible_समयout
	    (&priv->confirm_रुको, 5 * HZ)) अणु
		netdev_dbg(priv->net_dev, "wait time out!! wireless parameter set\n");
	पूर्ण

	अगर (priv->dev_state >= DEVICE_STATE_PREINIT) अणु
		netdev_dbg(priv->net_dev, "DEVICE READY!!\n");
		priv->dev_state = DEVICE_STATE_READY;
	पूर्ण
पूर्ण

अटल व्योम ks7010_init_शेषs(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->reg.tx_rate = TX_RATE_AUTO;
	priv->reg.preamble = LONG_PREAMBLE;
	priv->reg.घातer_mgmt = POWER_MGMT_ACTIVE;
	priv->reg.scan_type = ACTIVE_SCAN;
	priv->reg.beacon_lost_count = 20;
	priv->reg.rts = 2347UL;
	priv->reg.fragment = 2346UL;
	priv->reg.phy_type = D_11BG_COMPATIBLE_MODE;
	priv->reg.cts_mode = CTS_MODE_FALSE;
	priv->reg.rate_set.body[11] = TX_RATE_54M;
	priv->reg.rate_set.body[10] = TX_RATE_48M;
	priv->reg.rate_set.body[9] = TX_RATE_36M;
	priv->reg.rate_set.body[8] = TX_RATE_18M;
	priv->reg.rate_set.body[7] = TX_RATE_9M;
	priv->reg.rate_set.body[6] = TX_RATE_24M | BASIC_RATE;
	priv->reg.rate_set.body[5] = TX_RATE_12M | BASIC_RATE;
	priv->reg.rate_set.body[4] = TX_RATE_6M | BASIC_RATE;
	priv->reg.rate_set.body[3] = TX_RATE_11M | BASIC_RATE;
	priv->reg.rate_set.body[2] = TX_RATE_5M | BASIC_RATE;
	priv->reg.rate_set.body[1] = TX_RATE_2M | BASIC_RATE;
	priv->reg.rate_set.body[0] = TX_RATE_1M | BASIC_RATE;
	priv->reg.tx_rate = TX_RATE_FULL_AUTO;
	priv->reg.rate_set.size = 12;
पूर्ण

अटल पूर्णांक ks7010_sdio_setup_irqs(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;

	/* पूर्णांकerrupt disable */
	sdio_ग_लिखोb(func, 0, INT_ENABLE_REG, &ret);
	अगर (ret)
		जाओ irq_error;

	sdio_ग_लिखोb(func, 0xff, INT_PENDING_REG, &ret);
	अगर (ret)
		जाओ irq_error;

	/* setup पूर्णांकerrupt handler */
	ret = sdio_claim_irq(func, ks_sdio_पूर्णांकerrupt);

irq_error:
	वापस ret;
पूर्ण

अटल व्योम ks7010_sdio_init_irqs(काष्ठा sdio_func *func,
				  काष्ठा ks_wlan_निजी *priv)
अणु
	u8 byte;
	पूर्णांक ret;

	/*
	 * पूर्णांकerrupt setting
	 * clear Interrupt status ग_लिखो
	 * (ARMtoSD_InterruptPending FN1:00_0024)
	 */
	sdio_claim_host(func);
	ret = ks7010_sdio_ग_लिखोb(priv, INT_PENDING_REG, 0xff);
	sdio_release_host(func);
	अगर (ret)
		netdev_err(priv->net_dev, "write INT_PENDING_REG\n");

	/* enable ks7010sdio पूर्णांकerrupt */
	byte = (INT_GCR_B | INT_READ_STATUS | INT_WRITE_STATUS);
	sdio_claim_host(func);
	ret = ks7010_sdio_ग_लिखोb(priv, INT_ENABLE_REG, byte);
	sdio_release_host(func);
	अगर (ret)
		netdev_err(priv->net_dev, "write INT_ENABLE_REG\n");
पूर्ण

अटल व्योम ks7010_निजी_init(काष्ठा ks_wlan_निजी *priv,
				काष्ठा ks_sdio_card *card,
				काष्ठा net_device *netdev)
अणु
	/* निजी memory initialize */
	priv->अगर_hw = card;

	priv->dev_state = DEVICE_STATE_PREBOOT;
	priv->net_dev = netdev;
	priv->firmware_version[0] = '\0';
	priv->version_size = 0;
	priv->last_करोze = jअगरfies;
	priv->last_wakeup = jअगरfies;
	स_रखो(&priv->nstats, 0, माप(priv->nstats));
	स_रखो(&priv->wstats, 0, माप(priv->wstats));

	/* sleep mode */
	atomic_set(&priv->sleepstatus.करोze_request, 0);
	atomic_set(&priv->sleepstatus.wakeup_request, 0);
	atomic_set(&priv->sleepstatus.wakeup_request, 0);

	trx_device_init(priv);
	hostअगर_init(priv);
	ks_wlan_net_start(netdev);
	ks7010_init_शेषs(priv);
पूर्ण

अटल पूर्णांक ks7010_sdio_probe(काष्ठा sdio_func *func,
			     स्थिर काष्ठा sdio_device_id *device)
अणु
	काष्ठा ks_wlan_निजी *priv = शून्य;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा ks_sdio_card *card;
	पूर्णांक ret;

	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->func = func;

	sdio_claim_host(func);

	ret = sdio_set_block_size(func, KS7010_IO_BLOCK_SIZE);
	अगर (ret)
		जाओ err_मुक्त_card;

	dev_dbg(&card->func->dev, "multi_block=%d sdio_set_block_size()=%d %d\n",
		func->card->cccr.multi_block, func->cur_blksize, ret);

	ret = sdio_enable_func(func);
	अगर (ret)
		जाओ err_मुक्त_card;

	ret = ks7010_sdio_setup_irqs(func);
	अगर (ret)
		जाओ err_disable_func;

	sdio_release_host(func);

	sdio_set_drvdata(func, card);

	dev_dbg(&card->func->dev, "class = 0x%X, vendor = 0x%X, device = 0x%X\n",
		func->class, func->venकरोr, func->device);

	/* निजी memory allocate */
	netdev = alloc_etherdev(माप(*priv));
	अगर (!netdev) अणु
		dev_err(&card->func->dev, "Unable to alloc new net device\n");
		जाओ err_release_irq;
	पूर्ण

	ret = dev_alloc_name(netdev, "wlan%d");
	अगर (ret < 0) अणु
		dev_err(&card->func->dev, "Couldn't get name!\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	priv = netdev_priv(netdev);

	card->priv = priv;
	SET_NETDEV_DEV(netdev, &card->func->dev);

	ks7010_निजी_init(priv, card, netdev);

	ret = ks7010_upload_firmware(card);
	अगर (ret) अणु
		netdev_err(priv->net_dev,
			   "firmware load failed !! ret = %d\n", ret);
		जाओ err_मुक्त_netdev;
	पूर्ण

	ks7010_sdio_init_irqs(func, priv);

	priv->dev_state = DEVICE_STATE_BOOT;

	priv->wq = alloc_workqueue("wq", WQ_MEM_RECLAIM, 1);
	अगर (!priv->wq) अणु
		netdev_err(priv->net_dev, "create_workqueue failed !!\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	INIT_DELAYED_WORK(&priv->rw_dwork, ks7010_rw_function);
	ks7010_card_init(priv);

	ret = रेजिस्टर_netdev(priv->net_dev);
	अगर (ret)
		जाओ err_destroy_wq;

	वापस 0;

 err_destroy_wq:
	destroy_workqueue(priv->wq);
 err_मुक्त_netdev:
	मुक्त_netdev(netdev);
 err_release_irq:
	sdio_claim_host(func);
	sdio_release_irq(func);
 err_disable_func:
	sdio_disable_func(func);
 err_मुक्त_card:
	sdio_release_host(func);
	sdio_set_drvdata(func, शून्य);
	kमुक्त(card);

	वापस -ENODEV;
पूर्ण

/* send stop request to MAC */
अटल पूर्णांक send_stop_request(काष्ठा sdio_func *func)
अणु
	काष्ठा hostअगर_stop_request *pp;
	काष्ठा ks_sdio_card *card;
	माप_प्रकार size;

	card = sdio_get_drvdata(func);

	pp = kzalloc(hअगर_align_size(माप(*pp)), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	size = माप(*pp) - माप(pp->header.size);
	pp->header.size = cpu_to_le16(size);
	pp->header.event = cpu_to_le16(HIF_STOP_REQ);

	sdio_claim_host(func);
	ग_लिखो_to_device(card->priv, (u8 *)pp, hअगर_align_size(माप(*pp)));
	sdio_release_host(func);

	kमुक्त(pp);
	वापस 0;
पूर्ण

अटल व्योम ks7010_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	काष्ठा ks_sdio_card *card;
	काष्ठा ks_wlan_निजी *priv;

	card = sdio_get_drvdata(func);

	अगर (!card)
		वापस;

	priv = card->priv;
	अगर (!priv)
		जाओ err_मुक्त_card;

	ks_wlan_net_stop(priv->net_dev);

	/* पूर्णांकerrupt disable */
	sdio_claim_host(func);
	sdio_ग_लिखोb(func, 0, INT_ENABLE_REG, &ret);
	sdio_ग_लिखोb(func, 0xff, INT_PENDING_REG, &ret);
	sdio_release_host(func);

	ret = send_stop_request(func);
	अगर (ret)	/* memory allocation failure */
		जाओ err_मुक्त_card;

	अगर (priv->wq) अणु
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
	पूर्ण

	hostअगर_निकास(priv);

	unरेजिस्टर_netdev(priv->net_dev);

	trx_device_निकास(priv);
	मुक्त_netdev(priv->net_dev);
	card->priv = शून्य;

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);
err_मुक्त_card:
	sdio_set_drvdata(func, शून्य);
	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id ks7010_sdio_ids[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_KS_CODE_A, SDIO_DEVICE_ID_KS_7010)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_KS_CODE_B, SDIO_DEVICE_ID_KS_7010)पूर्ण,
	अणु /* all zero */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(sdio, ks7010_sdio_ids);

अटल काष्ठा sdio_driver ks7010_sdio_driver = अणु
	.name = "ks7010_sdio",
	.id_table = ks7010_sdio_ids,
	.probe = ks7010_sdio_probe,
	.हटाओ = ks7010_sdio_हटाओ,
पूर्ण;

module_driver(ks7010_sdio_driver, sdio_रेजिस्टर_driver, sdio_unरेजिस्टर_driver);
MODULE_AUTHOR("Sang Engineering, Qi-Hardware, KeyStream");
MODULE_DESCRIPTION("Driver for KeyStream KS7010 based SDIO cards");
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(ROM_खाता);
