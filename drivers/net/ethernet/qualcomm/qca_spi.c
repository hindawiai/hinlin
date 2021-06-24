<शैली गुरु>
/*
 *   Copyright (c) 2011, 2012, Qualcomm Atheros Communications Inc.
 *   Copyright (c) 2014, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*   This module implements the Qualcomm Atheros SPI protocol क्रम
 *   kernel-based SPI device; it is essentially an Ethernet-to-SPI
 *   serial converter;
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

#समावेश "qca_7k.h"
#समावेश "qca_7k_common.h"
#समावेश "qca_debug.h"
#समावेश "qca_spi.h"

#घोषणा MAX_DMA_BURST_LEN 5000

/*   Modules parameters     */
#घोषणा QCASPI_CLK_SPEED_MIN 1000000
#घोषणा QCASPI_CLK_SPEED_MAX 16000000
#घोषणा QCASPI_CLK_SPEED     8000000
अटल पूर्णांक qcaspi_clkspeed;
module_param(qcaspi_clkspeed, पूर्णांक, 0);
MODULE_PARM_DESC(qcaspi_clkspeed, "SPI bus clock speed (Hz). Use 1000000-16000000.");

#घोषणा QCASPI_BURST_LEN_MIN 1
#घोषणा QCASPI_BURST_LEN_MAX MAX_DMA_BURST_LEN
अटल पूर्णांक qcaspi_burst_len = MAX_DMA_BURST_LEN;
module_param(qcaspi_burst_len, पूर्णांक, 0);
MODULE_PARM_DESC(qcaspi_burst_len, "Number of data bytes per burst. Use 1-5000.");

#घोषणा QCASPI_PLUGGABLE_MIN 0
#घोषणा QCASPI_PLUGGABLE_MAX 1
अटल पूर्णांक qcaspi_pluggable = QCASPI_PLUGGABLE_MIN;
module_param(qcaspi_pluggable, पूर्णांक, 0);
MODULE_PARM_DESC(qcaspi_pluggable, "Pluggable SPI connection (yes/no).");

#घोषणा QCASPI_WRITE_VERIFY_MIN 0
#घोषणा QCASPI_WRITE_VERIFY_MAX 3
अटल पूर्णांक wr_verअगरy = QCASPI_WRITE_VERIFY_MIN;
module_param(wr_verअगरy, पूर्णांक, 0);
MODULE_PARM_DESC(wr_verअगरy, "SPI register write verify trails. Use 0-3.");

#घोषणा QCASPI_TX_TIMEOUT (1 * HZ)
#घोषणा QCASPI_QCA7K_REBOOT_TIME_MS 1000

अटल व्योम
start_spi_पूर्णांकr_handling(काष्ठा qcaspi *qca, u16 *पूर्णांकr_cause)
अणु
	*पूर्णांकr_cause = 0;

	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_INTR_ENABLE, 0, wr_verअगरy);
	qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_INTR_CAUSE, पूर्णांकr_cause);
	netdev_dbg(qca->net_dev, "interrupts: 0x%04x\n", *पूर्णांकr_cause);
पूर्ण

अटल व्योम
end_spi_पूर्णांकr_handling(काष्ठा qcaspi *qca, u16 पूर्णांकr_cause)
अणु
	u16 पूर्णांकr_enable = (SPI_INT_CPU_ON |
			   SPI_INT_PKT_AVLBL |
			   SPI_INT_RDBUF_ERR |
			   SPI_INT_WRBUF_ERR);

	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_INTR_CAUSE, पूर्णांकr_cause, 0);
	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_INTR_ENABLE, पूर्णांकr_enable, wr_verअगरy);
	netdev_dbg(qca->net_dev, "acking int: 0x%04x\n", पूर्णांकr_cause);
पूर्ण

अटल u32
qcaspi_ग_लिखो_burst(काष्ठा qcaspi *qca, u8 *src, u32 len)
अणु
	__be16 cmd;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer[2];
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));
	spi_message_init(&msg);

	cmd = cpu_to_be16(QCA7K_SPI_WRITE | QCA7K_SPI_EXTERNAL);
	transfer[0].tx_buf = &cmd;
	transfer[0].len = QCASPI_CMD_LEN;
	transfer[1].tx_buf = src;
	transfer[1].len = len;

	spi_message_add_tail(&transfer[0], &msg);
	spi_message_add_tail(&transfer[1], &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (ret || (msg.actual_length != QCASPI_CMD_LEN + len)) अणु
		qcaspi_spi_error(qca);
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

अटल u32
qcaspi_ग_लिखो_legacy(काष्ठा qcaspi *qca, u8 *src, u32 len)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer;
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));
	spi_message_init(&msg);

	transfer.tx_buf = src;
	transfer.len = len;

	spi_message_add_tail(&transfer, &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (ret || (msg.actual_length != len)) अणु
		qcaspi_spi_error(qca);
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

अटल u32
qcaspi_पढ़ो_burst(काष्ठा qcaspi *qca, u8 *dst, u32 len)
अणु
	काष्ठा spi_message msg;
	__be16 cmd;
	काष्ठा spi_transfer transfer[2];
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));
	spi_message_init(&msg);

	cmd = cpu_to_be16(QCA7K_SPI_READ | QCA7K_SPI_EXTERNAL);
	transfer[0].tx_buf = &cmd;
	transfer[0].len = QCASPI_CMD_LEN;
	transfer[1].rx_buf = dst;
	transfer[1].len = len;

	spi_message_add_tail(&transfer[0], &msg);
	spi_message_add_tail(&transfer[1], &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (ret || (msg.actual_length != QCASPI_CMD_LEN + len)) अणु
		qcaspi_spi_error(qca);
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

अटल u32
qcaspi_पढ़ो_legacy(काष्ठा qcaspi *qca, u8 *dst, u32 len)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer;
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));
	spi_message_init(&msg);

	transfer.rx_buf = dst;
	transfer.len = len;

	spi_message_add_tail(&transfer, &msg);
	ret = spi_sync(qca->spi_dev, &msg);

	अगर (ret || (msg.actual_length != len)) अणु
		qcaspi_spi_error(qca);
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक
qcaspi_tx_cmd(काष्ठा qcaspi *qca, u16 cmd)
अणु
	__be16 tx_data;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer;
	पूर्णांक ret;

	स_रखो(&transfer, 0, माप(transfer));

	spi_message_init(&msg);

	tx_data = cpu_to_be16(cmd);
	transfer.len = माप(cmd);
	transfer.tx_buf = &tx_data;
	spi_message_add_tail(&transfer, &msg);

	ret = spi_sync(qca->spi_dev, &msg);

	अगर (!ret)
		ret = msg.status;

	अगर (ret)
		qcaspi_spi_error(qca);

	वापस ret;
पूर्ण

अटल पूर्णांक
qcaspi_tx_frame(काष्ठा qcaspi *qca, काष्ठा sk_buff *skb)
अणु
	u32 count;
	u32 written;
	u32 offset;
	u32 len;

	len = skb->len;

	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_BFR_SIZE, len, wr_verअगरy);
	अगर (qca->legacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_WRITE | QCA7K_SPI_EXTERNAL);

	offset = 0;
	जबतक (len) अणु
		count = len;
		अगर (count > qca->burst_len)
			count = qca->burst_len;

		अगर (qca->legacy_mode) अणु
			written = qcaspi_ग_लिखो_legacy(qca,
						      skb->data + offset,
						      count);
		पूर्ण अन्यथा अणु
			written = qcaspi_ग_लिखो_burst(qca,
						     skb->data + offset,
						     count);
		पूर्ण

		अगर (written != count)
			वापस -1;

		offset += count;
		len -= count;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qcaspi_transmit(काष्ठा qcaspi *qca)
अणु
	काष्ठा net_device_stats *n_stats = &qca->net_dev->stats;
	u16 available = 0;
	u32 pkt_len;
	u16 new_head;
	u16 packets = 0;

	अगर (qca->txr.skb[qca->txr.head] == शून्य)
		वापस 0;

	qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_WRBUF_SPC_AVA, &available);

	अगर (available > QCASPI_HW_BUF_LEN) अणु
		/* This could only happen by पूर्णांकerferences on the SPI line.
		 * So retry later ...
		 */
		qca->stats.buf_avail_err++;
		वापस -1;
	पूर्ण

	जबतक (qca->txr.skb[qca->txr.head]) अणु
		pkt_len = qca->txr.skb[qca->txr.head]->len + QCASPI_HW_PKT_LEN;

		अगर (available < pkt_len) अणु
			अगर (packets == 0)
				qca->stats.ग_लिखो_buf_miss++;
			अवरोध;
		पूर्ण

		अगर (qcaspi_tx_frame(qca, qca->txr.skb[qca->txr.head]) == -1) अणु
			qca->stats.ग_लिखो_err++;
			वापस -1;
		पूर्ण

		packets++;
		n_stats->tx_packets++;
		n_stats->tx_bytes += qca->txr.skb[qca->txr.head]->len;
		available -= pkt_len;

		/* हटाओ the skb from the queue */
		/* XXX After inconsistent lock states netअगर_tx_lock()
		 * has been replaced by netअगर_tx_lock_bh() and so on.
		 */
		netअगर_tx_lock_bh(qca->net_dev);
		dev_kमुक्त_skb(qca->txr.skb[qca->txr.head]);
		qca->txr.skb[qca->txr.head] = शून्य;
		qca->txr.size -= pkt_len;
		new_head = qca->txr.head + 1;
		अगर (new_head >= qca->txr.count)
			new_head = 0;
		qca->txr.head = new_head;
		अगर (netअगर_queue_stopped(qca->net_dev))
			netअगर_wake_queue(qca->net_dev);
		netअगर_tx_unlock_bh(qca->net_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qcaspi_receive(काष्ठा qcaspi *qca)
अणु
	काष्ठा net_device *net_dev = qca->net_dev;
	काष्ठा net_device_stats *n_stats = &net_dev->stats;
	u16 available = 0;
	u32 bytes_पढ़ो;
	u8 *cp;

	/* Allocate rx SKB अगर we करोn't have one available. */
	अगर (!qca->rx_skb) अणु
		qca->rx_skb = netdev_alloc_skb_ip_align(net_dev,
							net_dev->mtu +
							VLAN_ETH_HLEN);
		अगर (!qca->rx_skb) अणु
			netdev_dbg(net_dev, "out of RX resources\n");
			qca->stats.out_of_mem++;
			वापस -1;
		पूर्ण
	पूर्ण

	/* Read the packet size. */
	qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_RDBUF_BYTE_AVA, &available);

	netdev_dbg(net_dev, "qcaspi_receive: SPI_REG_RDBUF_BYTE_AVA: Value: %08x\n",
		   available);

	अगर (available > QCASPI_HW_BUF_LEN + QCASPI_HW_PKT_LEN) अणु
		/* This could only happen by पूर्णांकerferences on the SPI line.
		 * So retry later ...
		 */
		qca->stats.buf_avail_err++;
		वापस -1;
	पूर्ण अन्यथा अगर (available == 0) अणु
		netdev_dbg(net_dev, "qcaspi_receive called without any data being available!\n");
		वापस -1;
	पूर्ण

	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_BFR_SIZE, available, wr_verअगरy);

	अगर (qca->legacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_READ | QCA7K_SPI_EXTERNAL);

	जबतक (available) अणु
		u32 count = available;

		अगर (count > qca->burst_len)
			count = qca->burst_len;

		अगर (qca->legacy_mode) अणु
			bytes_पढ़ो = qcaspi_पढ़ो_legacy(qca, qca->rx_buffer,
							count);
		पूर्ण अन्यथा अणु
			bytes_पढ़ो = qcaspi_पढ़ो_burst(qca, qca->rx_buffer,
						       count);
		पूर्ण

		netdev_dbg(net_dev, "available: %d, byte read: %d\n",
			   available, bytes_पढ़ो);

		अगर (bytes_पढ़ो) अणु
			available -= bytes_पढ़ो;
		पूर्ण अन्यथा अणु
			qca->stats.पढ़ो_err++;
			वापस -1;
		पूर्ण

		cp = qca->rx_buffer;

		जबतक ((bytes_पढ़ो--) && (qca->rx_skb)) अणु
			s32 retcode;

			retcode = qcafrm_fsm_decode(&qca->frm_handle,
						    qca->rx_skb->data,
						    skb_tailroom(qca->rx_skb),
						    *cp);
			cp++;
			चयन (retcode) अणु
			हाल QCAFRM_GATHER:
			हाल QCAFRM_NOHEAD:
				अवरोध;
			हाल QCAFRM_NOTAIL:
				netdev_dbg(net_dev, "no RX tail\n");
				n_stats->rx_errors++;
				n_stats->rx_dropped++;
				अवरोध;
			हाल QCAFRM_INVLEN:
				netdev_dbg(net_dev, "invalid RX length\n");
				n_stats->rx_errors++;
				n_stats->rx_dropped++;
				अवरोध;
			शेष:
				qca->rx_skb->dev = qca->net_dev;
				n_stats->rx_packets++;
				n_stats->rx_bytes += retcode;
				skb_put(qca->rx_skb, retcode);
				qca->rx_skb->protocol = eth_type_trans(
					qca->rx_skb, qca->rx_skb->dev);
				qca->rx_skb->ip_summed = CHECKSUM_UNNECESSARY;
				netअगर_rx_ni(qca->rx_skb);
				qca->rx_skb = netdev_alloc_skb_ip_align(net_dev,
					net_dev->mtu + VLAN_ETH_HLEN);
				अगर (!qca->rx_skb) अणु
					netdev_dbg(net_dev, "out of RX resources\n");
					n_stats->rx_errors++;
					qca->stats.out_of_mem++;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*   Check that tx ring stores only so much bytes
 *   that fit पूर्णांकo the पूर्णांकernal QCA buffer.
 */

अटल पूर्णांक
qcaspi_tx_ring_has_space(काष्ठा tx_ring *txr)
अणु
	अगर (txr->skb[txr->tail])
		वापस 0;

	वापस (txr->size + QCAFRM_MAX_LEN < QCASPI_HW_BUF_LEN) ? 1 : 0;
पूर्ण

/*   Flush the tx ring. This function is only safe to
 *   call from the qcaspi_spi_thपढ़ो.
 */

अटल व्योम
qcaspi_flush_tx_ring(काष्ठा qcaspi *qca)
अणु
	पूर्णांक i;

	/* XXX After inconsistent lock states netअगर_tx_lock()
	 * has been replaced by netअगर_tx_lock_bh() and so on.
	 */
	netअगर_tx_lock_bh(qca->net_dev);
	क्रम (i = 0; i < TX_RING_MAX_LEN; i++) अणु
		अगर (qca->txr.skb[i]) अणु
			dev_kमुक्त_skb(qca->txr.skb[i]);
			qca->txr.skb[i] = शून्य;
			qca->net_dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण
	qca->txr.tail = 0;
	qca->txr.head = 0;
	qca->txr.size = 0;
	netअगर_tx_unlock_bh(qca->net_dev);
पूर्ण

अटल व्योम
qcaspi_qca7k_sync(काष्ठा qcaspi *qca, पूर्णांक event)
अणु
	u16 signature = 0;
	u16 spi_config;
	u16 wrbuf_space = 0;

	अगर (event == QCASPI_EVENT_CPUON) अणु
		/* Read signature twice, अगर not valid
		 * go back to unknown state.
		 */
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);
		अगर (signature != QCASPI_GOOD_SIGNATURE) अणु
			qca->sync = QCASPI_SYNC_UNKNOWN;
			netdev_dbg(qca->net_dev, "sync: got CPU on, but signature was invalid, restart\n");
		पूर्ण अन्यथा अणु
			/* ensure that the WRBUF is empty */
			qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_WRBUF_SPC_AVA,
					     &wrbuf_space);
			अगर (wrbuf_space != QCASPI_HW_BUF_LEN) अणु
				netdev_dbg(qca->net_dev, "sync: got CPU on, but wrbuf not empty. reset!\n");
				qca->sync = QCASPI_SYNC_UNKNOWN;
			पूर्ण अन्यथा अणु
				netdev_dbg(qca->net_dev, "sync: got CPU on, now in sync\n");
				qca->sync = QCASPI_SYNC_READY;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (qca->sync) अणु
	हाल QCASPI_SYNC_READY:
		/* Read signature, अगर not valid go to unknown state. */
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);
		अगर (signature != QCASPI_GOOD_SIGNATURE) अणु
			qca->sync = QCASPI_SYNC_UNKNOWN;
			netdev_dbg(qca->net_dev, "sync: bad signature, restart\n");
			/* करोn't reset right away */
			वापस;
		पूर्ण
		अवरोध;
	हाल QCASPI_SYNC_UNKNOWN:
		/* Read signature, अगर not valid stay in unknown state */
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);
		अगर (signature != QCASPI_GOOD_SIGNATURE) अणु
			netdev_dbg(qca->net_dev, "sync: could not read signature to reset device, retry.\n");
			वापस;
		पूर्ण

		/* TODO: use GPIO to reset QCA7000 in legacy mode*/
		netdev_dbg(qca->net_dev, "sync: resetting device.\n");
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SPI_CONFIG, &spi_config);
		spi_config |= QCASPI_SLAVE_RESET_BIT;
		qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_SPI_CONFIG, spi_config, 0);

		qca->sync = QCASPI_SYNC_RESET;
		qca->stats.trig_reset++;
		qca->reset_count = 0;
		अवरोध;
	हाल QCASPI_SYNC_RESET:
		qca->reset_count++;
		netdev_dbg(qca->net_dev, "sync: waiting for CPU on, count %u.\n",
			   qca->reset_count);
		अगर (qca->reset_count >= QCASPI_RESET_TIMEOUT) अणु
			/* reset did not seem to take place, try again */
			qca->sync = QCASPI_SYNC_UNKNOWN;
			qca->stats.reset_समयout++;
			netdev_dbg(qca->net_dev, "sync: reset timeout, restarting process.\n");
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
qcaspi_spi_thपढ़ो(व्योम *data)
अणु
	काष्ठा qcaspi *qca = data;
	u16 पूर्णांकr_cause = 0;

	netdev_info(qca->net_dev, "SPI thread created\n");
	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर ((qca->पूर्णांकr_req == qca->पूर्णांकr_svc) &&
		    (qca->txr.skb[qca->txr.head] == शून्य) &&
		    (qca->sync == QCASPI_SYNC_READY))
			schedule();

		set_current_state(TASK_RUNNING);

		netdev_dbg(qca->net_dev, "have work to do. int: %d, tx_skb: %p\n",
			   qca->पूर्णांकr_req - qca->पूर्णांकr_svc,
			   qca->txr.skb[qca->txr.head]);

		qcaspi_qca7k_sync(qca, QCASPI_EVENT_UPDATE);

		अगर (qca->sync != QCASPI_SYNC_READY) अणु
			netdev_dbg(qca->net_dev, "sync: not ready %u, turn off carrier and flush\n",
				   (अचिन्हित पूर्णांक)qca->sync);
			netअगर_stop_queue(qca->net_dev);
			netअगर_carrier_off(qca->net_dev);
			qcaspi_flush_tx_ring(qca);
			msleep(QCASPI_QCA7K_REBOOT_TIME_MS);
		पूर्ण

		अगर (qca->पूर्णांकr_svc != qca->पूर्णांकr_req) अणु
			qca->पूर्णांकr_svc = qca->पूर्णांकr_req;
			start_spi_पूर्णांकr_handling(qca, &पूर्णांकr_cause);

			अगर (पूर्णांकr_cause & SPI_INT_CPU_ON) अणु
				qcaspi_qca7k_sync(qca, QCASPI_EVENT_CPUON);

				/* not synced. */
				अगर (qca->sync != QCASPI_SYNC_READY)
					जारी;

				qca->stats.device_reset++;
				netअगर_wake_queue(qca->net_dev);
				netअगर_carrier_on(qca->net_dev);
			पूर्ण

			अगर (पूर्णांकr_cause & SPI_INT_RDBUF_ERR) अणु
				/* restart sync */
				netdev_dbg(qca->net_dev, "===> rdbuf error!\n");
				qca->stats.पढ़ो_buf_err++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				जारी;
			पूर्ण

			अगर (पूर्णांकr_cause & SPI_INT_WRBUF_ERR) अणु
				/* restart sync */
				netdev_dbg(qca->net_dev, "===> wrbuf error!\n");
				qca->stats.ग_लिखो_buf_err++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				जारी;
			पूर्ण

			/* can only handle other पूर्णांकerrupts
			 * अगर sync has occurred
			 */
			अगर (qca->sync == QCASPI_SYNC_READY) अणु
				अगर (पूर्णांकr_cause & SPI_INT_PKT_AVLBL)
					qcaspi_receive(qca);
			पूर्ण

			end_spi_पूर्णांकr_handling(qca, पूर्णांकr_cause);
		पूर्ण

		अगर (qca->sync == QCASPI_SYNC_READY)
			qcaspi_transmit(qca);
	पूर्ण
	set_current_state(TASK_RUNNING);
	netdev_info(qca->net_dev, "SPI thread exit\n");

	वापस 0;
पूर्ण

अटल irqवापस_t
qcaspi_पूर्णांकr_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcaspi *qca = data;

	qca->पूर्णांकr_req++;
	अगर (qca->spi_thपढ़ो &&
	    qca->spi_thपढ़ो->state != TASK_RUNNING)
		wake_up_process(qca->spi_thपढ़ो);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
qcaspi_netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!qca)
		वापस -EINVAL;

	qca->पूर्णांकr_req = 1;
	qca->पूर्णांकr_svc = 0;
	qca->sync = QCASPI_SYNC_UNKNOWN;
	qcafrm_fsm_init_spi(&qca->frm_handle);

	qca->spi_thपढ़ो = kthपढ़ो_run((व्योम *)qcaspi_spi_thपढ़ो,
				      qca, "%s", dev->name);

	अगर (IS_ERR(qca->spi_thपढ़ो)) अणु
		netdev_err(dev, "%s: unable to start kernel thread.\n",
			   QCASPI_DRV_NAME);
		वापस PTR_ERR(qca->spi_thपढ़ो);
	पूर्ण

	ret = request_irq(qca->spi_dev->irq, qcaspi_पूर्णांकr_handler, 0,
			  dev->name, qca);
	अगर (ret) अणु
		netdev_err(dev, "%s: unable to get IRQ %d (irqval=%d).\n",
			   QCASPI_DRV_NAME, qca->spi_dev->irq, ret);
		kthपढ़ो_stop(qca->spi_thपढ़ो);
		वापस ret;
	पूर्ण

	/* SPI thपढ़ो takes care of TX queue */

	वापस 0;
पूर्ण

अटल पूर्णांक
qcaspi_netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	netअगर_stop_queue(dev);

	qcaspi_ग_लिखो_रेजिस्टर(qca, SPI_REG_INTR_ENABLE, 0, wr_verअगरy);
	मुक्त_irq(qca->spi_dev->irq, qca);

	kthपढ़ो_stop(qca->spi_thपढ़ो);
	qca->spi_thपढ़ो = शून्य;
	qcaspi_flush_tx_ring(qca);

	वापस 0;
पूर्ण

अटल netdev_tx_t
qcaspi_netdev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	u32 frame_len;
	u8 *pपंचांगp;
	काष्ठा qcaspi *qca = netdev_priv(dev);
	u16 new_tail;
	काष्ठा sk_buff *tskb;
	u8 pad_len = 0;

	अगर (skb->len < QCAFRM_MIN_LEN)
		pad_len = QCAFRM_MIN_LEN - skb->len;

	अगर (qca->txr.skb[qca->txr.tail]) अणु
		netdev_warn(qca->net_dev, "queue was unexpectedly full!\n");
		netअगर_stop_queue(qca->net_dev);
		qca->stats.ring_full++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर ((skb_headroom(skb) < QCAFRM_HEADER_LEN) ||
	    (skb_tailroom(skb) < QCAFRM_FOOTER_LEN + pad_len)) अणु
		tskb = skb_copy_expand(skb, QCAFRM_HEADER_LEN,
				       QCAFRM_FOOTER_LEN + pad_len, GFP_ATOMIC);
		अगर (!tskb) अणु
			qca->stats.out_of_mem++;
			वापस NETDEV_TX_BUSY;
		पूर्ण
		dev_kमुक्त_skb(skb);
		skb = tskb;
	पूर्ण

	frame_len = skb->len + pad_len;

	pपंचांगp = skb_push(skb, QCAFRM_HEADER_LEN);
	qcafrm_create_header(pपंचांगp, frame_len);

	अगर (pad_len) अणु
		pपंचांगp = skb_put_zero(skb, pad_len);
	पूर्ण

	pपंचांगp = skb_put(skb, QCAFRM_FOOTER_LEN);
	qcafrm_create_footer(pपंचांगp);

	netdev_dbg(qca->net_dev, "Tx-ing packet: Size: 0x%08x\n",
		   skb->len);

	qca->txr.size += skb->len + QCASPI_HW_PKT_LEN;

	new_tail = qca->txr.tail + 1;
	अगर (new_tail >= qca->txr.count)
		new_tail = 0;

	qca->txr.skb[qca->txr.tail] = skb;
	qca->txr.tail = new_tail;

	अगर (!qcaspi_tx_ring_has_space(&qca->txr)) अणु
		netअगर_stop_queue(qca->net_dev);
		qca->stats.ring_full++;
	पूर्ण

	netअगर_trans_update(dev);

	अगर (qca->spi_thपढ़ो &&
	    qca->spi_thपढ़ो->state != TASK_RUNNING)
		wake_up_process(qca->spi_thपढ़ो);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
qcaspi_netdev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	netdev_info(qca->net_dev, "Transmit timeout at %ld, latency %ld\n",
		    jअगरfies, jअगरfies - dev_trans_start(dev));
	qca->net_dev->stats.tx_errors++;
	/* Trigger tx queue flush and QCA7000 reset */
	qca->sync = QCASPI_SYNC_UNKNOWN;

	अगर (qca->spi_thपढ़ो)
		wake_up_process(qca->spi_thपढ़ो);
पूर्ण

अटल पूर्णांक
qcaspi_netdev_init(काष्ठा net_device *dev)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	dev->mtu = QCAFRM_MAX_MTU;
	dev->type = ARPHRD_ETHER;
	qca->clkspeed = qcaspi_clkspeed;
	qca->burst_len = qcaspi_burst_len;
	qca->spi_thपढ़ो = शून्य;
	qca->buffer_size = (dev->mtu + VLAN_ETH_HLEN + QCAFRM_HEADER_LEN +
		QCAFRM_FOOTER_LEN + 4) * 4;

	स_रखो(&qca->stats, 0, माप(काष्ठा qcaspi_stats));

	qca->rx_buffer = kदो_स्मृति(qca->buffer_size, GFP_KERNEL);
	अगर (!qca->rx_buffer)
		वापस -ENOBUFS;

	qca->rx_skb = netdev_alloc_skb_ip_align(dev, qca->net_dev->mtu +
						VLAN_ETH_HLEN);
	अगर (!qca->rx_skb) अणु
		kमुक्त(qca->rx_buffer);
		netdev_info(qca->net_dev, "Failed to allocate RX sk_buff.\n");
		वापस -ENOBUFS;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
qcaspi_netdev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	kमुक्त(qca->rx_buffer);
	qca->buffer_size = 0;
	dev_kमुक्त_skb(qca->rx_skb);
पूर्ण

अटल स्थिर काष्ठा net_device_ops qcaspi_netdev_ops = अणु
	.nकरो_init = qcaspi_netdev_init,
	.nकरो_uninit = qcaspi_netdev_uninit,
	.nकरो_खोलो = qcaspi_netdev_खोलो,
	.nकरो_stop = qcaspi_netdev_बंद,
	.nकरो_start_xmit = qcaspi_netdev_xmit,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_tx_समयout = qcaspi_netdev_tx_समयout,
	.nकरो_validate_addr = eth_validate_addr,
पूर्ण;

अटल व्योम
qcaspi_netdev_setup(काष्ठा net_device *dev)
अणु
	काष्ठा qcaspi *qca = शून्य;

	dev->netdev_ops = &qcaspi_netdev_ops;
	qcaspi_set_ethtool_ops(dev);
	dev->watchकरोg_समयo = QCASPI_TX_TIMEOUT;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->tx_queue_len = 100;

	/* MTU range: 46 - 1500 */
	dev->min_mtu = QCAFRM_MIN_MTU;
	dev->max_mtu = QCAFRM_MAX_MTU;

	qca = netdev_priv(dev);
	स_रखो(qca, 0, माप(काष्ठा qcaspi));

	स_रखो(&qca->txr, 0, माप(qca->txr));
	qca->txr.count = TX_RING_MAX_LEN;
पूर्ण

अटल स्थिर काष्ठा of_device_id qca_spi_of_match[] = अणु
	अणु .compatible = "qca,qca7000" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qca_spi_of_match);

अटल पूर्णांक
qca_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा qcaspi *qca = शून्य;
	काष्ठा net_device *qcaspi_devs = शून्य;
	u8 legacy_mode = 0;
	u16 signature;
	पूर्णांक ret;

	अगर (!spi->dev.of_node) अणु
		dev_err(&spi->dev, "Missing device tree\n");
		वापस -EINVAL;
	पूर्ण

	legacy_mode = of_property_पढ़ो_bool(spi->dev.of_node,
					    "qca,legacy-mode");

	अगर (qcaspi_clkspeed == 0) अणु
		अगर (spi->max_speed_hz)
			qcaspi_clkspeed = spi->max_speed_hz;
		अन्यथा
			qcaspi_clkspeed = QCASPI_CLK_SPEED;
	पूर्ण

	अगर ((qcaspi_clkspeed < QCASPI_CLK_SPEED_MIN) ||
	    (qcaspi_clkspeed > QCASPI_CLK_SPEED_MAX)) अणु
		dev_err(&spi->dev, "Invalid clkspeed: %d\n",
			qcaspi_clkspeed);
		वापस -EINVAL;
	पूर्ण

	अगर ((qcaspi_burst_len < QCASPI_BURST_LEN_MIN) ||
	    (qcaspi_burst_len > QCASPI_BURST_LEN_MAX)) अणु
		dev_err(&spi->dev, "Invalid burst len: %d\n",
			qcaspi_burst_len);
		वापस -EINVAL;
	पूर्ण

	अगर ((qcaspi_pluggable < QCASPI_PLUGGABLE_MIN) ||
	    (qcaspi_pluggable > QCASPI_PLUGGABLE_MAX)) अणु
		dev_err(&spi->dev, "Invalid pluggable: %d\n",
			qcaspi_pluggable);
		वापस -EINVAL;
	पूर्ण

	अगर (wr_verअगरy < QCASPI_WRITE_VERIFY_MIN ||
	    wr_verअगरy > QCASPI_WRITE_VERIFY_MAX) अणु
		dev_err(&spi->dev, "Invalid write verify: %d\n",
			wr_verअगरy);
		वापस -EINVAL;
	पूर्ण

	dev_info(&spi->dev, "ver=%s, clkspeed=%d, burst_len=%d, pluggable=%d\n",
		 QCASPI_DRV_VERSION,
		 qcaspi_clkspeed,
		 qcaspi_burst_len,
		 qcaspi_pluggable);

	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = qcaspi_clkspeed;
	अगर (spi_setup(spi) < 0) अणु
		dev_err(&spi->dev, "Unable to setup SPI device\n");
		वापस -EFAULT;
	पूर्ण

	qcaspi_devs = alloc_etherdev(माप(काष्ठा qcaspi));
	अगर (!qcaspi_devs)
		वापस -ENOMEM;

	qcaspi_netdev_setup(qcaspi_devs);
	SET_NETDEV_DEV(qcaspi_devs, &spi->dev);

	qca = netdev_priv(qcaspi_devs);
	अगर (!qca) अणु
		मुक्त_netdev(qcaspi_devs);
		dev_err(&spi->dev, "Fail to retrieve private structure\n");
		वापस -ENOMEM;
	पूर्ण
	qca->net_dev = qcaspi_devs;
	qca->spi_dev = spi;
	qca->legacy_mode = legacy_mode;

	spi_set_drvdata(spi, qcaspi_devs);

	ret = of_get_mac_address(spi->dev.of_node, qca->net_dev->dev_addr);
	अगर (ret) अणु
		eth_hw_addr_अक्रमom(qca->net_dev);
		dev_info(&spi->dev, "Using random MAC address: %pM\n",
			 qca->net_dev->dev_addr);
	पूर्ण

	netअगर_carrier_off(qca->net_dev);

	अगर (!qcaspi_pluggable) अणु
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);
		qcaspi_पढ़ो_रेजिस्टर(qca, SPI_REG_SIGNATURE, &signature);

		अगर (signature != QCASPI_GOOD_SIGNATURE) अणु
			dev_err(&spi->dev, "Invalid signature (0x%04X)\n",
				signature);
			मुक्त_netdev(qcaspi_devs);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (रेजिस्टर_netdev(qcaspi_devs)) अणु
		dev_err(&spi->dev, "Unable to register net device %s\n",
			qcaspi_devs->name);
		मुक्त_netdev(qcaspi_devs);
		वापस -EFAULT;
	पूर्ण

	qcaspi_init_device_debugfs(qca);

	वापस 0;
पूर्ण

अटल पूर्णांक
qca_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा net_device *qcaspi_devs = spi_get_drvdata(spi);
	काष्ठा qcaspi *qca = netdev_priv(qcaspi_devs);

	qcaspi_हटाओ_device_debugfs(qca);

	unरेजिस्टर_netdev(qcaspi_devs);
	मुक्त_netdev(qcaspi_devs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id qca_spi_id[] = अणु
	अणु "qca7000", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, qca_spi_id);

अटल काष्ठा spi_driver qca_spi_driver = अणु
	.driver	= अणु
		.name	= QCASPI_DRV_NAME,
		.of_match_table = qca_spi_of_match,
	पूर्ण,
	.id_table = qca_spi_id,
	.probe    = qca_spi_probe,
	.हटाओ   = qca_spi_हटाओ,
पूर्ण;
module_spi_driver(qca_spi_driver);

MODULE_DESCRIPTION("Qualcomm Atheros QCA7000 SPI Driver");
MODULE_AUTHOR("Qualcomm Atheros Communications");
MODULE_AUTHOR("Stefan Wahren <stefan.wahren@i2se.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(QCASPI_DRV_VERSION);
