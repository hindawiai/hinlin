<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 MOSER-BAER AG
//

#घोषणा pr_fmt(fmt) "InES_PTP: " fmt

#समावेश <linux/ethtool.h>
#समावेश <linux/export.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mii_बारtamper.h>
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/मानकघोष.स>

MODULE_DESCRIPTION("Driver for the ZHAW InES PTP time stamping IP core");
MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");

/* GLOBAL रेजिस्टर */
#घोषणा MCAST_MAC_SELECT_SHIFT	2
#घोषणा MCAST_MAC_SELECT_MASK	0x3
#घोषणा IO_RESET		BIT(1)
#घोषणा PTP_RESET		BIT(0)

/* VERSION रेजिस्टर */
#घोषणा IF_MAJOR_VER_SHIFT	12
#घोषणा IF_MAJOR_VER_MASK	0xf
#घोषणा IF_MINOR_VER_SHIFT	8
#घोषणा IF_MINOR_VER_MASK	0xf
#घोषणा FPGA_MAJOR_VER_SHIFT	4
#घोषणा FPGA_MAJOR_VER_MASK	0xf
#घोषणा FPGA_MINOR_VER_SHIFT	0
#घोषणा FPGA_MINOR_VER_MASK	0xf

/* INT_STAT रेजिस्टर */
#घोषणा RX_INTR_STATUS_3	BIT(5)
#घोषणा RX_INTR_STATUS_2	BIT(4)
#घोषणा RX_INTR_STATUS_1	BIT(3)
#घोषणा TX_INTR_STATUS_3	BIT(2)
#घोषणा TX_INTR_STATUS_2	BIT(1)
#घोषणा TX_INTR_STATUS_1	BIT(0)

/* INT_MSK रेजिस्टर */
#घोषणा RX_INTR_MASK_3		BIT(5)
#घोषणा RX_INTR_MASK_2		BIT(4)
#घोषणा RX_INTR_MASK_1		BIT(3)
#घोषणा TX_INTR_MASK_3		BIT(2)
#घोषणा TX_INTR_MASK_2		BIT(1)
#घोषणा TX_INTR_MASK_1		BIT(0)

/* BUF_STAT रेजिस्टर */
#घोषणा RX_FIFO_NE_3		BIT(5)
#घोषणा RX_FIFO_NE_2		BIT(4)
#घोषणा RX_FIFO_NE_1		BIT(3)
#घोषणा TX_FIFO_NE_3		BIT(2)
#घोषणा TX_FIFO_NE_2		BIT(1)
#घोषणा TX_FIFO_NE_1		BIT(0)

/* PORT_CONF रेजिस्टर */
#घोषणा CM_ONE_STEP		BIT(6)
#घोषणा PHY_SPEED_SHIFT		4
#घोषणा PHY_SPEED_MASK		0x3
#घोषणा P2P_DELAY_WR_POS_SHIFT	2
#घोषणा P2P_DELAY_WR_POS_MASK	0x3
#घोषणा PTP_MODE_SHIFT		0
#घोषणा PTP_MODE_MASK		0x3

/* TS_STAT_TX रेजिस्टर */
#घोषणा TS_ENABLE		BIT(15)
#घोषणा DATA_READ_POS_SHIFT	8
#घोषणा DATA_READ_POS_MASK	0x1f
#घोषणा DISCARDED_EVENTS_SHIFT	4
#घोषणा DISCARDED_EVENTS_MASK	0xf

#घोषणा INES_N_PORTS		3
#घोषणा INES_REGISTER_SIZE	0x80
#घोषणा INES_PORT_OFFSET	0x20
#घोषणा INES_PORT_SIZE		0x20
#घोषणा INES_FIFO_DEPTH		90
#घोषणा INES_MAX_EVENTS		100

#घोषणा BC_PTP_V1		0
#घोषणा BC_PTP_V2		1
#घोषणा TC_E2E_PTP_V2		2
#घोषणा TC_P2P_PTP_V2		3

#घोषणा PHY_SPEED_10		0
#घोषणा PHY_SPEED_100		1
#घोषणा PHY_SPEED_1000		2

#घोषणा PORT_CONF \
	((PHY_SPEED_1000 << PHY_SPEED_SHIFT) | (BC_PTP_V2 << PTP_MODE_SHIFT))

#घोषणा ines_पढ़ो32(s, r)	__raw_पढ़ोl((व्योम __iomem *)&s->regs->r)
#घोषणा ines_ग_लिखो32(s, v, r)	__raw_ग_लिखोl(v, (व्योम __iomem *)&s->regs->r)

#घोषणा MESSAGE_TYPE_SYNC		1
#घोषणा MESSAGE_TYPE_P_DELAY_REQ	2
#घोषणा MESSAGE_TYPE_P_DELAY_RESP	3
#घोषणा MESSAGE_TYPE_DELAY_REQ		4

अटल LIST_HEAD(ines_घड़ीs);
अटल DEFINE_MUTEX(ines_घड़ीs_lock);

काष्ठा ines_global_regs अणु
	u32 id;
	u32 test;
	u32 global;
	u32 version;
	u32 test2;
	u32 पूर्णांक_stat;
	u32 पूर्णांक_msk;
	u32 buf_stat;
पूर्ण;

काष्ठा ines_port_रेजिस्टरs अणु
	u32 port_conf;
	u32 p_delay;
	u32 ts_stat_tx;
	u32 ts_stat_rx;
	u32 ts_tx;
	u32 ts_rx;
पूर्ण;

काष्ठा ines_बारtamp अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ	पंचांगo;
	u16		tag;
	u64		sec;
	u64		nsec;
	u64		clkid;
	u16		portnum;
	u16		seqid;
पूर्ण;

काष्ठा ines_port अणु
	काष्ठा ines_port_रेजिस्टरs	*regs;
	काष्ठा mii_बारtamper		mii_ts;
	काष्ठा ines_घड़ी		*घड़ी;
	bool				rxts_enabled;
	bool				txts_enabled;
	अचिन्हित पूर्णांक			index;
	काष्ठा delayed_work		ts_work;
	/* lock protects event list and tx_skb */
	spinlock_t			lock;
	काष्ठा sk_buff			*tx_skb;
	काष्ठा list_head		events;
	काष्ठा list_head		pool;
	काष्ठा ines_बारtamp		pool_data[INES_MAX_EVENTS];
पूर्ण;

काष्ठा ines_घड़ी अणु
	काष्ठा ines_port		port[INES_N_PORTS];
	काष्ठा ines_global_regs __iomem	*regs;
	व्योम __iomem			*base;
	काष्ठा device_node		*node;
	काष्ठा device			*dev;
	काष्ठा list_head		list;
पूर्ण;

अटल bool ines_match(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ptp_class,
		       काष्ठा ines_बारtamp *ts, काष्ठा device *dev);
अटल पूर्णांक ines_rxfअगरo_पढ़ो(काष्ठा ines_port *port);
अटल u64 ines_rxts64(काष्ठा ines_port *port, अचिन्हित पूर्णांक words);
अटल bool ines_बारtamp_expired(काष्ठा ines_बारtamp *ts);
अटल u64 ines_txts64(काष्ठा ines_port *port, अचिन्हित पूर्णांक words);
अटल व्योम ines_txtstamp_work(काष्ठा work_काष्ठा *work);
अटल bool is_sync_pdelay_resp(काष्ठा sk_buff *skb, पूर्णांक type);
अटल u8 tag_to_msgtype(u8 tag);

अटल व्योम ines_घड़ी_cleanup(काष्ठा ines_घड़ी *घड़ी)
अणु
	काष्ठा ines_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < INES_N_PORTS; i++) अणु
		port = &घड़ी->port[i];
		cancel_delayed_work_sync(&port->ts_work);
	पूर्ण
पूर्ण

अटल पूर्णांक ines_घड़ी_init(काष्ठा ines_घड़ी *घड़ी, काष्ठा device *device,
			   व्योम __iomem *addr)
अणु
	काष्ठा device_node *node = device->of_node;
	अचिन्हित दीर्घ port_addr;
	काष्ठा ines_port *port;
	पूर्णांक i, j;

	INIT_LIST_HEAD(&घड़ी->list);
	घड़ी->node = node;
	घड़ी->dev  = device;
	घड़ी->base = addr;
	घड़ी->regs = घड़ी->base;

	क्रम (i = 0; i < INES_N_PORTS; i++) अणु
		port = &घड़ी->port[i];
		port_addr = (अचिन्हित दीर्घ) घड़ी->base +
			INES_PORT_OFFSET + i * INES_PORT_SIZE;
		port->regs = (काष्ठा ines_port_रेजिस्टरs *) port_addr;
		port->घड़ी = घड़ी;
		port->index = i;
		INIT_DELAYED_WORK(&port->ts_work, ines_txtstamp_work);
		spin_lock_init(&port->lock);
		INIT_LIST_HEAD(&port->events);
		INIT_LIST_HEAD(&port->pool);
		क्रम (j = 0; j < INES_MAX_EVENTS; j++)
			list_add(&port->pool_data[j].list, &port->pool);
	पूर्ण

	ines_ग_लिखो32(घड़ी, 0xBEEF, test);
	ines_ग_लिखो32(घड़ी, 0xBEEF, test2);

	dev_dbg(device, "ID      0x%x\n", ines_पढ़ो32(घड़ी, id));
	dev_dbg(device, "TEST    0x%x\n", ines_पढ़ो32(घड़ी, test));
	dev_dbg(device, "VERSION 0x%x\n", ines_पढ़ो32(घड़ी, version));
	dev_dbg(device, "TEST2   0x%x\n", ines_पढ़ो32(घड़ी, test2));

	क्रम (i = 0; i < INES_N_PORTS; i++) अणु
		port = &घड़ी->port[i];
		ines_ग_लिखो32(port, PORT_CONF, port_conf);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ines_port *ines_find_port(काष्ठा device_node *node, u32 index)
अणु
	काष्ठा ines_port *port = शून्य;
	काष्ठा ines_घड़ी *घड़ी;
	काष्ठा list_head *this;

	mutex_lock(&ines_घड़ीs_lock);
	list_क्रम_each(this, &ines_घड़ीs) अणु
		घड़ी = list_entry(this, काष्ठा ines_घड़ी, list);
		अगर (घड़ी->node == node) अणु
			port = &घड़ी->port[index];
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ines_घड़ीs_lock);
	वापस port;
पूर्ण

अटल u64 ines_find_rxts(काष्ठा ines_port *port, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा ines_बारtamp *ts;
	अचिन्हित दीर्घ flags;
	u64 ns = 0;

	अगर (type == PTP_CLASS_NONE)
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	ines_rxfअगरo_पढ़ो(port);
	list_क्रम_each_safe(this, next, &port->events) अणु
		ts = list_entry(this, काष्ठा ines_बारtamp, list);
		अगर (ines_बारtamp_expired(ts)) अणु
			list_del_init(&ts->list);
			list_add(&ts->list, &port->pool);
			जारी;
		पूर्ण
		अगर (ines_match(skb, type, ts, port->घड़ी->dev)) अणु
			ns = ts->sec * 1000000000ULL + ts->nsec;
			list_del_init(&ts->list);
			list_add(&ts->list, &port->pool);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);

	वापस ns;
पूर्ण

अटल u64 ines_find_txts(काष्ठा ines_port *port, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक class = ptp_classअगरy_raw(skb), i;
	u32 data_rd_pos, buf_stat, mask, ts_stat_tx;
	काष्ठा ines_बारtamp ts;
	अचिन्हित दीर्घ flags;
	u64 ns = 0;

	mask = TX_FIFO_NE_1 << port->index;

	spin_lock_irqsave(&port->lock, flags);

	क्रम (i = 0; i < INES_FIFO_DEPTH; i++) अणु

		buf_stat = ines_पढ़ो32(port->घड़ी, buf_stat);
		अगर (!(buf_stat & mask)) अणु
			dev_dbg(port->घड़ी->dev,
				  "Tx timestamp FIFO unexpectedly empty\n");
			अवरोध;
		पूर्ण
		ts_stat_tx = ines_पढ़ो32(port, ts_stat_tx);
		data_rd_pos = (ts_stat_tx >> DATA_READ_POS_SHIFT) &
			DATA_READ_POS_MASK;
		अगर (data_rd_pos) अणु
			dev_err(port->घड़ी->dev,
				"unexpected Tx read pos %u\n", data_rd_pos);
			अवरोध;
		पूर्ण

		ts.tag     = ines_पढ़ो32(port, ts_tx);
		ts.sec     = ines_txts64(port, 3);
		ts.nsec    = ines_txts64(port, 2);
		ts.clkid   = ines_txts64(port, 4);
		ts.portnum = ines_पढ़ो32(port, ts_tx);
		ts.seqid   = ines_पढ़ो32(port, ts_tx);

		अगर (ines_match(skb, class, &ts, port->घड़ी->dev)) अणु
			ns = ts.sec * 1000000000ULL + ts.nsec;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
	वापस ns;
पूर्ण

अटल पूर्णांक ines_hwtstamp(काष्ठा mii_बारtamper *mii_ts, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ines_port *port = container_of(mii_ts, काष्ठा ines_port, mii_ts);
	u32 cm_one_step = 0, port_conf, ts_stat_rx, ts_stat_tx;
	काष्ठा hwtstamp_config cfg;
	अचिन्हित दीर्घ flags;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (cfg.flags)
		वापस -EINVAL;

	चयन (cfg.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		ts_stat_tx = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		ts_stat_tx = TS_ENABLE;
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		ts_stat_tx = TS_ENABLE;
		cm_one_step = CM_ONE_STEP;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		ts_stat_rx = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		वापस -दुस्फल;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		ts_stat_rx = TS_ENABLE;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	port_conf = ines_पढ़ो32(port, port_conf);
	port_conf &= ~CM_ONE_STEP;
	port_conf |= cm_one_step;

	ines_ग_लिखो32(port, port_conf, port_conf);
	ines_ग_लिखो32(port, ts_stat_rx, ts_stat_rx);
	ines_ग_लिखो32(port, ts_stat_tx, ts_stat_tx);

	port->rxts_enabled = ts_stat_rx == TS_ENABLE;
	port->txts_enabled = ts_stat_tx == TS_ENABLE;

	spin_unlock_irqrestore(&port->lock, flags);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल व्योम ines_link_state(काष्ठा mii_बारtamper *mii_ts,
			    काष्ठा phy_device *phydev)
अणु
	काष्ठा ines_port *port = container_of(mii_ts, काष्ठा ines_port, mii_ts);
	u32 port_conf, speed_conf;
	अचिन्हित दीर्घ flags;

	चयन (phydev->speed) अणु
	हाल SPEED_10:
		speed_conf = PHY_SPEED_10 << PHY_SPEED_SHIFT;
		अवरोध;
	हाल SPEED_100:
		speed_conf = PHY_SPEED_100 << PHY_SPEED_SHIFT;
		अवरोध;
	हाल SPEED_1000:
		speed_conf = PHY_SPEED_1000 << PHY_SPEED_SHIFT;
		अवरोध;
	शेष:
		dev_err(port->घड़ी->dev, "bad speed: %d\n", phydev->speed);
		वापस;
	पूर्ण
	spin_lock_irqsave(&port->lock, flags);

	port_conf = ines_पढ़ो32(port, port_conf);
	port_conf &= ~(0x3 << PHY_SPEED_SHIFT);
	port_conf |= speed_conf;

	ines_ग_लिखो32(port, port_conf, port_conf);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल bool ines_match(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ptp_class,
		       काष्ठा ines_बारtamp *ts, काष्ठा device *dev)
अणु
	काष्ठा ptp_header *hdr;
	u16 portn, seqid;
	u8 msgtype;
	u64 clkid;

	अगर (unlikely(ptp_class & PTP_CLASS_V1))
		वापस false;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस false;

	msgtype = ptp_get_msgtype(hdr, ptp_class);
	clkid = be64_to_cpup((__be64 *)&hdr->source_port_identity.घड़ी_identity.id[0]);
	portn = be16_to_cpu(hdr->source_port_identity.port_number);
	seqid = be16_to_cpu(hdr->sequence_id);

	अगर (tag_to_msgtype(ts->tag & 0x7) != msgtype) अणु
		dev_dbg(dev, "msgtype mismatch ts %hhu != skb %hhu\n",
			tag_to_msgtype(ts->tag & 0x7), msgtype);
		वापस false;
	पूर्ण
	अगर (ts->clkid != clkid) अणु
		dev_dbg(dev, "clkid mismatch ts %llx != skb %llx\n",
			ts->clkid, clkid);
		वापस false;
	पूर्ण
	अगर (ts->portnum != portn) अणु
		dev_dbg(dev, "portn mismatch ts %hu != skb %hu\n",
			ts->portnum, portn);
		वापस false;
	पूर्ण
	अगर (ts->seqid != seqid) अणु
		dev_dbg(dev, "seqid mismatch ts %hu != skb %hu\n",
			ts->seqid, seqid);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ines_rxtstamp(काष्ठा mii_बारtamper *mii_ts,
			  काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा ines_port *port = container_of(mii_ts, काष्ठा ines_port, mii_ts);
	काष्ठा skb_shared_hwtstamps *ssh;
	u64 ns;

	अगर (!port->rxts_enabled)
		वापस false;

	ns = ines_find_rxts(port, skb, type);
	अगर (!ns)
		वापस false;

	ssh = skb_hwtstamps(skb);
	ssh->hwtstamp = ns_to_kसमय(ns);
	netअगर_rx(skb);

	वापस true;
पूर्ण

अटल पूर्णांक ines_rxfअगरo_पढ़ो(काष्ठा ines_port *port)
अणु
	u32 data_rd_pos, buf_stat, mask, ts_stat_rx;
	काष्ठा ines_बारtamp *ts;
	अचिन्हित पूर्णांक i;

	mask = RX_FIFO_NE_1 << port->index;

	क्रम (i = 0; i < INES_FIFO_DEPTH; i++) अणु
		अगर (list_empty(&port->pool)) अणु
			dev_err(port->घड़ी->dev, "event pool is empty\n");
			वापस -1;
		पूर्ण
		buf_stat = ines_पढ़ो32(port->घड़ी, buf_stat);
		अगर (!(buf_stat & mask))
			अवरोध;

		ts_stat_rx = ines_पढ़ो32(port, ts_stat_rx);
		data_rd_pos = (ts_stat_rx >> DATA_READ_POS_SHIFT) &
			DATA_READ_POS_MASK;
		अगर (data_rd_pos) अणु
			dev_err(port->घड़ी->dev, "unexpected Rx read pos %u\n",
				data_rd_pos);
			अवरोध;
		पूर्ण

		ts = list_first_entry(&port->pool, काष्ठा ines_बारtamp, list);
		ts->पंचांगo     = jअगरfies + HZ;
		ts->tag     = ines_पढ़ो32(port, ts_rx);
		ts->sec     = ines_rxts64(port, 3);
		ts->nsec    = ines_rxts64(port, 2);
		ts->clkid   = ines_rxts64(port, 4);
		ts->portnum = ines_पढ़ो32(port, ts_rx);
		ts->seqid   = ines_पढ़ो32(port, ts_rx);

		list_del_init(&ts->list);
		list_add_tail(&ts->list, &port->events);
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 ines_rxts64(काष्ठा ines_port *port, अचिन्हित पूर्णांक words)
अणु
	अचिन्हित पूर्णांक i;
	u64 result;
	u16 word;

	word = ines_पढ़ो32(port, ts_rx);
	result = word;
	words--;
	क्रम (i = 0; i < words; i++) अणु
		word = ines_पढ़ो32(port, ts_rx);
		result <<= 16;
		result |= word;
	पूर्ण
	वापस result;
पूर्ण

अटल bool ines_बारtamp_expired(काष्ठा ines_बारtamp *ts)
अणु
	वापस समय_after(jअगरfies, ts->पंचांगo);
पूर्ण

अटल पूर्णांक ines_ts_info(काष्ठा mii_बारtamper *mii_ts,
			काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;

	info->phc_index = -1;

	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_P2P);

	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);

	वापस 0;
पूर्ण

अटल u64 ines_txts64(काष्ठा ines_port *port, अचिन्हित पूर्णांक words)
अणु
	अचिन्हित पूर्णांक i;
	u64 result;
	u16 word;

	word = ines_पढ़ो32(port, ts_tx);
	result = word;
	words--;
	क्रम (i = 0; i < words; i++) अणु
		word = ines_पढ़ो32(port, ts_tx);
		result <<= 16;
		result |= word;
	पूर्ण
	वापस result;
पूर्ण

अटल bool ines_txts_onestep(काष्ठा ines_port *port, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	अचिन्हित दीर्घ flags;
	u32 port_conf;

	spin_lock_irqsave(&port->lock, flags);
	port_conf = ines_पढ़ो32(port, port_conf);
	spin_unlock_irqrestore(&port->lock, flags);

	अगर (port_conf & CM_ONE_STEP)
		वापस is_sync_pdelay_resp(skb, type);

	वापस false;
पूर्ण

अटल व्योम ines_txtstamp(काष्ठा mii_बारtamper *mii_ts,
			  काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा ines_port *port = container_of(mii_ts, काष्ठा ines_port, mii_ts);
	काष्ठा sk_buff *old_skb = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (!port->txts_enabled || ines_txts_onestep(port, skb, type)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	अगर (port->tx_skb)
		old_skb = port->tx_skb;

	port->tx_skb = skb;

	spin_unlock_irqrestore(&port->lock, flags);

	kमुक्त_skb(old_skb);

	schedule_delayed_work(&port->ts_work, 1);
पूर्ण

अटल व्योम ines_txtstamp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ines_port *port =
		container_of(work, काष्ठा ines_port, ts_work.work);
	काष्ठा skb_shared_hwtstamps ssh;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	u64 ns;

	spin_lock_irqsave(&port->lock, flags);
	skb = port->tx_skb;
	port->tx_skb = शून्य;
	spin_unlock_irqrestore(&port->lock, flags);

	ns = ines_find_txts(port, skb);
	अगर (!ns) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	ssh.hwtstamp = ns_to_kसमय(ns);
	skb_complete_tx_बारtamp(skb, &ssh);
पूर्ण

अटल bool is_sync_pdelay_resp(काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा ptp_header *hdr;
	u8 msgtype;

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस false;

	msgtype = ptp_get_msgtype(hdr, type);

	चयन (msgtype) अणु
	हाल PTP_MSGTYPE_SYNC:
	हाल PTP_MSGTYPE_PDELAY_RESP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u8 tag_to_msgtype(u8 tag)
अणु
	चयन (tag) अणु
	हाल MESSAGE_TYPE_SYNC:
		वापस PTP_MSGTYPE_SYNC;
	हाल MESSAGE_TYPE_P_DELAY_REQ:
		वापस PTP_MSGTYPE_PDELAY_REQ;
	हाल MESSAGE_TYPE_P_DELAY_RESP:
		वापस PTP_MSGTYPE_PDELAY_RESP;
	हाल MESSAGE_TYPE_DELAY_REQ:
		वापस PTP_MSGTYPE_DELAY_REQ;
	पूर्ण
	वापस 0xf;
पूर्ण

अटल काष्ठा mii_बारtamper *ines_ptp_probe_channel(काष्ठा device *device,
						      अचिन्हित पूर्णांक index)
अणु
	काष्ठा device_node *node = device->of_node;
	काष्ठा ines_port *port;

	अगर (index > INES_N_PORTS - 1) अणु
		dev_err(device, "bad port index %u\n", index);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	port = ines_find_port(node, index);
	अगर (!port) अणु
		dev_err(device, "missing port index %u\n", index);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	port->mii_ts.rxtstamp = ines_rxtstamp;
	port->mii_ts.txtstamp = ines_txtstamp;
	port->mii_ts.hwtstamp = ines_hwtstamp;
	port->mii_ts.link_state = ines_link_state;
	port->mii_ts.ts_info = ines_ts_info;

	वापस &port->mii_ts;
पूर्ण

अटल व्योम ines_ptp_release_channel(काष्ठा device *device,
				     काष्ठा mii_बारtamper *mii_ts)
अणु
पूर्ण

अटल काष्ठा mii_बारtamping_ctrl ines_ctrl = अणु
	.probe_channel = ines_ptp_probe_channel,
	.release_channel = ines_ptp_release_channel,
पूर्ण;

अटल पूर्णांक ines_ptp_ctrl_probe(काष्ठा platक्रमm_device *pld)
अणु
	काष्ठा ines_घड़ी *घड़ी;
	व्योम __iomem *addr;
	पूर्णांक err = 0;

	addr = devm_platक्रमm_ioremap_resource(pld, 0);
	अगर (IS_ERR(addr)) अणु
		err = PTR_ERR(addr);
		जाओ out;
	पूर्ण
	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (ines_घड़ी_init(घड़ी, &pld->dev, addr)) अणु
		kमुक्त(घड़ी);
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	err = रेजिस्टर_mii_tstamp_controller(&pld->dev, &ines_ctrl);
	अगर (err) अणु
		kमुक्त(घड़ी);
		जाओ out;
	पूर्ण
	mutex_lock(&ines_घड़ीs_lock);
	list_add_tail(&ines_घड़ीs, &घड़ी->list);
	mutex_unlock(&ines_घड़ीs_lock);

	dev_set_drvdata(&pld->dev, घड़ी);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ines_ptp_ctrl_हटाओ(काष्ठा platक्रमm_device *pld)
अणु
	काष्ठा ines_घड़ी *घड़ी = dev_get_drvdata(&pld->dev);

	unरेजिस्टर_mii_tstamp_controller(&pld->dev);
	mutex_lock(&ines_घड़ीs_lock);
	list_del(&घड़ी->list);
	mutex_unlock(&ines_घड़ीs_lock);
	ines_घड़ी_cleanup(घड़ी);
	kमुक्त(घड़ी);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ines_ptp_ctrl_of_match[] = अणु
	अणु .compatible = "ines,ptp-ctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ines_ptp_ctrl_of_match);

अटल काष्ठा platक्रमm_driver ines_ptp_ctrl_driver = अणु
	.probe  = ines_ptp_ctrl_probe,
	.हटाओ = ines_ptp_ctrl_हटाओ,
	.driver = अणु
		.name = "ines_ptp_ctrl",
		.of_match_table = of_match_ptr(ines_ptp_ctrl_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ines_ptp_ctrl_driver);
