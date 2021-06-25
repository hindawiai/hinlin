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

/*   This file contains debugging routines क्रम use in the QCA7K driver.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>

#समावेश "qca_7k.h"
#समावेश "qca_debug.h"

#घोषणा QCASPI_MAX_REGS 0x20

अटल स्थिर u16 qcaspi_spi_regs[] = अणु
	SPI_REG_BFR_SIZE,
	SPI_REG_WRBUF_SPC_AVA,
	SPI_REG_RDBUF_BYTE_AVA,
	SPI_REG_SPI_CONFIG,
	SPI_REG_SPI_STATUS,
	SPI_REG_INTR_CAUSE,
	SPI_REG_INTR_ENABLE,
	SPI_REG_RDBUF_WATERMARK,
	SPI_REG_WRBUF_WATERMARK,
	SPI_REG_SIGNATURE,
	SPI_REG_ACTION_CTRL
पूर्ण;

/* The order of these strings must match the order of the fields in
 * काष्ठा qcaspi_stats
 * See qca_spi.h
 */
अटल स्थिर अक्षर qcaspi_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"Triggered resets",
	"Device resets",
	"Reset timeouts",
	"Read errors",
	"Write errors",
	"Read buffer errors",
	"Write buffer errors",
	"Out of memory",
	"Write buffer misses",
	"Transmit ring full",
	"SPI errors",
	"Write verify errors",
	"Buffer available errors",
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक
qcaspi_info_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा qcaspi *qca = s->निजी;

	seq_म_लिखो(s, "RX buffer size   : %lu\n",
		   (अचिन्हित दीर्घ)qca->buffer_size);

	seq_माला_दो(s, "TX ring state    : ");

	अगर (qca->txr.skb[qca->txr.head] == शून्य)
		seq_माला_दो(s, "empty");
	अन्यथा अगर (qca->txr.skb[qca->txr.tail])
		seq_माला_दो(s, "full");
	अन्यथा
		seq_माला_दो(s, "in use");

	seq_माला_दो(s, "\n");

	seq_म_लिखो(s, "TX ring size     : %u\n",
		   qca->txr.size);

	seq_म_लिखो(s, "Sync state       : %u (",
		   (अचिन्हित पूर्णांक)qca->sync);
	चयन (qca->sync) अणु
	हाल QCASPI_SYNC_UNKNOWN:
		seq_माला_दो(s, "QCASPI_SYNC_UNKNOWN");
		अवरोध;
	हाल QCASPI_SYNC_RESET:
		seq_माला_दो(s, "QCASPI_SYNC_RESET");
		अवरोध;
	हाल QCASPI_SYNC_READY:
		seq_माला_दो(s, "QCASPI_SYNC_READY");
		अवरोध;
	शेष:
		seq_माला_दो(s, "INVALID");
		अवरोध;
	पूर्ण
	seq_माला_दो(s, ")\n");

	seq_म_लिखो(s, "IRQ              : %d\n",
		   qca->spi_dev->irq);
	seq_म_लिखो(s, "INTR REQ         : %u\n",
		   qca->पूर्णांकr_req);
	seq_म_लिखो(s, "INTR SVC         : %u\n",
		   qca->पूर्णांकr_svc);

	seq_म_लिखो(s, "SPI max speed    : %lu\n",
		   (अचिन्हित दीर्घ)qca->spi_dev->max_speed_hz);
	seq_म_लिखो(s, "SPI mode         : %x\n",
		   qca->spi_dev->mode);
	seq_म_लिखो(s, "SPI chip select  : %u\n",
		   (अचिन्हित पूर्णांक)qca->spi_dev->chip_select);
	seq_म_लिखो(s, "SPI legacy mode  : %u\n",
		   (अचिन्हित पूर्णांक)qca->legacy_mode);
	seq_म_लिखो(s, "SPI burst length : %u\n",
		   (अचिन्हित पूर्णांक)qca->burst_len);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(qcaspi_info);

व्योम
qcaspi_init_device_debugfs(काष्ठा qcaspi *qca)
अणु
	qca->device_root = debugfs_create_dir(dev_name(&qca->net_dev->dev),
					      शून्य);

	debugfs_create_file("info", S_IFREG | 0444, qca->device_root, qca,
			    &qcaspi_info_fops);
पूर्ण

व्योम
qcaspi_हटाओ_device_debugfs(काष्ठा qcaspi *qca)
अणु
	debugfs_हटाओ_recursive(qca->device_root);
पूर्ण

#अन्यथा /* CONFIG_DEBUG_FS */

व्योम
qcaspi_init_device_debugfs(काष्ठा qcaspi *qca)
अणु
पूर्ण

व्योम
qcaspi_हटाओ_device_debugfs(काष्ठा qcaspi *qca)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम
qcaspi_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *p)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	strlcpy(p->driver, QCASPI_DRV_NAME, माप(p->driver));
	strlcpy(p->version, QCASPI_DRV_VERSION, माप(p->version));
	strlcpy(p->fw_version, "QCA7000", माप(p->fw_version));
	strlcpy(p->bus_info, dev_name(&qca->spi_dev->dev),
		माप(p->bus_info));
पूर्ण

अटल पूर्णांक
qcaspi_get_link_ksettings(काष्ठा net_device *dev,
			  काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Half);

	cmd->base.speed = SPEED_10;
	cmd->base.duplex = DUPLEX_HALF;
	cmd->base.port = PORT_OTHER;
	cmd->base.स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल व्योम
qcaspi_get_ethtool_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *estats, u64 *data)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);
	काष्ठा qcaspi_stats *st = &qca->stats;

	स_नकल(data, st, ARRAY_SIZE(qcaspi_gstrings_stats) * माप(u64));
पूर्ण

अटल व्योम
qcaspi_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &qcaspi_gstrings_stats,
		       माप(qcaspi_gstrings_stats));
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
qcaspi_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(qcaspi_gstrings_stats);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
qcaspi_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(u32) * QCASPI_MAX_REGS;
पूर्ण

अटल व्योम
qcaspi_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);
	u32 *regs_buff = p;
	अचिन्हित पूर्णांक i;

	regs->version = 1;
	स_रखो(regs_buff, 0, माप(u32) * QCASPI_MAX_REGS);

	क्रम (i = 0; i < ARRAY_SIZE(qcaspi_spi_regs); i++) अणु
		u16 offset, value;

		qcaspi_पढ़ो_रेजिस्टर(qca, qcaspi_spi_regs[i], &value);
		offset = qcaspi_spi_regs[i] >> 8;
		regs_buff[offset] = value;
	पूर्ण
पूर्ण

अटल व्योम
qcaspi_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा qcaspi *qca = netdev_priv(dev);

	ring->rx_max_pending = 4;
	ring->tx_max_pending = TX_RING_MAX_LEN;
	ring->rx_pending = 4;
	ring->tx_pending = qca->txr.count;
पूर्ण

अटल पूर्णांक
qcaspi_set_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ring)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा qcaspi *qca = netdev_priv(dev);

	अगर ((ring->rx_pending) ||
	    (ring->rx_mini_pending) ||
	    (ring->rx_jumbo_pending))
		वापस -EINVAL;

	अगर (netअगर_running(dev))
		ops->nकरो_stop(dev);

	qca->txr.count = max_t(u32, ring->tx_pending, TX_RING_MIN_LEN);
	qca->txr.count = min_t(u16, qca->txr.count, TX_RING_MAX_LEN);

	अगर (netअगर_running(dev))
		ops->nकरो_खोलो(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops qcaspi_ethtool_ops = अणु
	.get_drvinfo = qcaspi_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_ethtool_stats = qcaspi_get_ethtool_stats,
	.get_strings = qcaspi_get_strings,
	.get_sset_count = qcaspi_get_sset_count,
	.get_regs_len = qcaspi_get_regs_len,
	.get_regs = qcaspi_get_regs,
	.get_ringparam = qcaspi_get_ringparam,
	.set_ringparam = qcaspi_set_ringparam,
	.get_link_ksettings = qcaspi_get_link_ksettings,
पूर्ण;

व्योम qcaspi_set_ethtool_ops(काष्ठा net_device *dev)
अणु
	dev->ethtool_ops = &qcaspi_ethtool_ops;
पूर्ण
