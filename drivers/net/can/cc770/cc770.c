<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the CC770 and AN82527 CAN controllers
 *
 * Copyright (C) 2009, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/platक्रमm/cc770.h>

#समावेश "cc770.h"

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(KBUILD_MODNAME "CAN netdevice driver");

/*
 * The CC770 is a CAN controller from Bosch, which is 100% compatible
 * with the AN82527 from Intel, but with "bugs" being fixed and some
 * additional functionality, मुख्यly:
 *
 * 1. RX and TX error counters are पढ़ोable.
 * 2. Support of silent (listen-only) mode.
 * 3. Message object 15 can receive all types of frames, also RTR and EFF.
 *
 * Details are available from Bosch's "CC770_Product_Info_2007-01.pdf",
 * which explains in detail the compatibility between the CC770 and the
 * 82527. This driver use the additional functionality 3. on real CC770
 * devices. Unक्रमtunately, the CC770 करोes still not store the message
 * identअगरier of received remote transmission request frames and
 * thereक्रमe it's set to 0.
 *
 * The message objects 1..14 can be used क्रम TX and RX जबतक the message
 * objects 15 is optimized क्रम RX. It has a shaकरोw रेजिस्टर क्रम reliable
 * data reception under heavy bus load. Thereक्रमe it makes sense to use
 * this message object क्रम the needed use हाल. The frame type (EFF/SFF)
 * क्रम the message object 15 can be defined via kernel module parameter
 * "msgobj15_eff". If not equal 0, it will receive 29-bit EFF frames,
 * otherwise 11 bit SFF messages.
 */
अटल पूर्णांक msgobj15_eff;
module_param(msgobj15_eff, पूर्णांक, 0444);
MODULE_PARM_DESC(msgobj15_eff, "Extended 29-bit frames for message object 15 "
		 "(default: 11-bit standard frames)");

अटल पूर्णांक i82527_compat;
module_param(i82527_compat, पूर्णांक, 0444);
MODULE_PARM_DESC(i82527_compat, "Strict Intel 82527 compatibility mode "
		 "without using additional functions");

/*
 * This driver uses the last 5 message objects 11..15. The definitions
 * and काष्ठाure below allows to configure and assign them to the real
 * message object.
 */
अटल अचिन्हित अक्षर cc770_obj_flags[CC770_OBJ_MAX] = अणु
	[CC770_OBJ_RX0] = CC770_OBJ_FLAG_RX,
	[CC770_OBJ_RX1] = CC770_OBJ_FLAG_RX | CC770_OBJ_FLAG_EFF,
	[CC770_OBJ_RX_RTR0] = CC770_OBJ_FLAG_RX | CC770_OBJ_FLAG_RTR,
	[CC770_OBJ_RX_RTR1] = CC770_OBJ_FLAG_RX | CC770_OBJ_FLAG_RTR |
			      CC770_OBJ_FLAG_EFF,
	[CC770_OBJ_TX] = 0,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर cc770_bittiming_स्थिर = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

अटल अंतरभूत पूर्णांक पूर्णांकid2obj(अचिन्हित पूर्णांक पूर्णांकid)
अणु
	अगर (पूर्णांकid == 2)
		वापस 0;
	अन्यथा
		वापस MSGOBJ_LAST + 2 - पूर्णांकid;
पूर्ण

अटल व्योम enable_all_objs(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	u8 msgcfg;
	अचिन्हित अक्षर obj_flags;
	अचिन्हित पूर्णांक o, mo;

	क्रम (o = 0; o < ARRAY_SIZE(priv->obj_flags); o++) अणु
		obj_flags = priv->obj_flags[o];
		mo = obj2msgobj(o);

		अगर (obj_flags & CC770_OBJ_FLAG_RX) अणु
			/*
			 * We करोn't need extra objects क्रम RTR and EFF अगर
			 * the additional CC770 functions are enabled.
			 */
			अगर (priv->control_normal_mode & CTRL_EAF) अणु
				अगर (o > 0)
					जारी;
				netdev_dbg(dev, "Message object %d for "
					   "RX data, RTR, SFF and EFF\n", mo);
			पूर्ण अन्यथा अणु
				netdev_dbg(dev,
					   "Message object %d for RX %s %s\n",
					   mo, obj_flags & CC770_OBJ_FLAG_RTR ?
					   "RTR" : "data",
					   obj_flags & CC770_OBJ_FLAG_EFF ?
					   "EFF" : "SFF");
			पूर्ण

			अगर (obj_flags & CC770_OBJ_FLAG_EFF)
				msgcfg = MSGCFG_XTD;
			अन्यथा
				msgcfg = 0;
			अगर (obj_flags & CC770_OBJ_FLAG_RTR)
				msgcfg |= MSGCFG_सूची;

			cc770_ग_लिखो_reg(priv, msgobj[mo].config, msgcfg);
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_SET | TXIE_RES |
					RXIE_SET | INTPND_RES);

			अगर (obj_flags & CC770_OBJ_FLAG_RTR)
				cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
						NEWDAT_RES | CPUUPD_SET |
						TXRQST_RES | RMTPND_RES);
			अन्यथा
				cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
						NEWDAT_RES | MSGLST_RES |
						TXRQST_RES | RMTPND_RES);
		पूर्ण अन्यथा अणु
			netdev_dbg(dev, "Message object %d for "
				   "TX data, RTR, SFF and EFF\n", mo);

			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
					RMTPND_RES | TXRQST_RES |
					CPUUPD_RES | NEWDAT_RES);
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम disable_all_objs(स्थिर काष्ठा cc770_priv *priv)
अणु
	पूर्णांक o, mo;

	क्रम (o = 0; o <  ARRAY_SIZE(priv->obj_flags); o++) अणु
		mo = obj2msgobj(o);

		अगर (priv->obj_flags[o] & CC770_OBJ_FLAG_RX) अणु
			अगर (o > 0 && priv->control_normal_mode & CTRL_EAF)
				जारी;

			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
					NEWDAT_RES | MSGLST_RES |
					TXRQST_RES | RMTPND_RES);
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		पूर्ण अन्यथा अणु
			/* Clear message object क्रम send */
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
					RMTPND_RES | TXRQST_RES |
					CPUUPD_RES | NEWDAT_RES);
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_reset_mode(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);

	/* Enable configuration and माला_दो chip in bus-off, disable पूर्णांकerrupts */
	cc770_ग_लिखो_reg(priv, control, CTRL_CCE | CTRL_INI);

	priv->can.state = CAN_STATE_STOPPED;

	/* Clear पूर्णांकerrupts */
	cc770_पढ़ो_reg(priv, पूर्णांकerrupt);

	/* Clear status रेजिस्टर */
	cc770_ग_लिखो_reg(priv, status, 0);

	/* Disable all used message objects */
	disable_all_objs(priv);
पूर्ण

अटल व्योम set_normal_mode(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);

	/* Clear पूर्णांकerrupts */
	cc770_पढ़ो_reg(priv, पूर्णांकerrupt);

	/* Clear status रेजिस्टर and pre-set last error code */
	cc770_ग_लिखो_reg(priv, status, STAT_LEC_MASK);

	/* Enable all used message objects*/
	enable_all_objs(dev);

	/*
	 * Clear bus-off, पूर्णांकerrupts only क्रम errors,
	 * not क्रम status change
	 */
	cc770_ग_लिखो_reg(priv, control, priv->control_normal_mode);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
पूर्ण

अटल व्योम chipset_init(काष्ठा cc770_priv *priv)
अणु
	पूर्णांक mo, id, data;

	/* Enable configuration and put chip in bus-off, disable पूर्णांकerrupts */
	cc770_ग_लिखो_reg(priv, control, (CTRL_CCE | CTRL_INI));

	/* Set CLKOUT भागider and slew rates */
	cc770_ग_लिखो_reg(priv, clkout, priv->clkout);

	/* Configure CPU पूर्णांकerface / CLKOUT enable */
	cc770_ग_लिखो_reg(priv, cpu_पूर्णांकerface, priv->cpu_पूर्णांकerface);

	/* Set bus configuration  */
	cc770_ग_लिखो_reg(priv, bus_config, priv->bus_config);

	/* Clear पूर्णांकerrupts */
	cc770_पढ़ो_reg(priv, पूर्णांकerrupt);

	/* Clear status रेजिस्टर */
	cc770_ग_लिखो_reg(priv, status, 0);

	/* Clear and invalidate message objects */
	क्रम (mo = MSGOBJ_FIRST; mo <= MSGOBJ_LAST; mo++) अणु
		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
				INTPND_UNC | RXIE_RES |
				TXIE_RES | MSGVAL_RES);
		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
				INTPND_RES | RXIE_RES |
				TXIE_RES | MSGVAL_RES);
		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
				NEWDAT_RES | MSGLST_RES |
				TXRQST_RES | RMTPND_RES);
		क्रम (data = 0; data < 8; data++)
			cc770_ग_लिखो_reg(priv, msgobj[mo].data[data], 0);
		क्रम (id = 0; id < 4; id++)
			cc770_ग_लिखो_reg(priv, msgobj[mo].id[id], 0);
		cc770_ग_लिखो_reg(priv, msgobj[mo].config, 0);
	पूर्ण

	/* Set all global ID masks to "don't care" */
	cc770_ग_लिखो_reg(priv, global_mask_std[0], 0);
	cc770_ग_लिखो_reg(priv, global_mask_std[1], 0);
	cc770_ग_लिखो_reg(priv, global_mask_ext[0], 0);
	cc770_ग_लिखो_reg(priv, global_mask_ext[1], 0);
	cc770_ग_लिखो_reg(priv, global_mask_ext[2], 0);
	cc770_ग_लिखो_reg(priv, global_mask_ext[3], 0);

पूर्ण

अटल पूर्णांक cc770_probe_chip(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);

	/* Enable configuration, put chip in bus-off, disable पूर्णांकs */
	cc770_ग_लिखो_reg(priv, control, CTRL_CCE | CTRL_EAF | CTRL_INI);
	/* Configure cpu पूर्णांकerface / CLKOUT disable */
	cc770_ग_लिखो_reg(priv, cpu_पूर्णांकerface, priv->cpu_पूर्णांकerface);

	/*
	 * Check अगर hardware reset is still inactive or maybe there
	 * is no chip in this address space
	 */
	अगर (cc770_पढ़ो_reg(priv, cpu_पूर्णांकerface) & CPUIF_RST) अणु
		netdev_info(dev, "probing @0x%p failed (reset)\n",
			    priv->reg_base);
		वापस -ENODEV;
	पूर्ण

	/* Write and पढ़ो back test pattern (some arbitrary values) */
	cc770_ग_लिखो_reg(priv, msgobj[1].data[1], 0x25);
	cc770_ग_लिखो_reg(priv, msgobj[2].data[3], 0x52);
	cc770_ग_लिखो_reg(priv, msgobj[10].data[6], 0xc3);
	अगर ((cc770_पढ़ो_reg(priv, msgobj[1].data[1]) != 0x25) ||
	    (cc770_पढ़ो_reg(priv, msgobj[2].data[3]) != 0x52) ||
	    (cc770_पढ़ो_reg(priv, msgobj[10].data[6]) != 0xc3)) अणु
		netdev_info(dev, "probing @0x%p failed (pattern)\n",
			    priv->reg_base);
		वापस -ENODEV;
	पूर्ण

	/* Check अगर this chip is a CC770 supporting additional functions */
	अगर (cc770_पढ़ो_reg(priv, control) & CTRL_EAF)
		priv->control_normal_mode |= CTRL_EAF;

	वापस 0;
पूर्ण

अटल व्योम cc770_start(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);

	/* leave reset mode */
	अगर (priv->can.state != CAN_STATE_STOPPED)
		set_reset_mode(dev);

	/* leave reset mode */
	set_normal_mode(dev);
पूर्ण

अटल पूर्णांक cc770_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		cc770_start(dev);
		netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(dev, "setting BTR0=0x%02x BTR1=0x%02x\n", btr0, btr1);

	cc770_ग_लिखो_reg(priv, bit_timing_0, btr0);
	cc770_ग_लिखो_reg(priv, bit_timing_1, btr1);

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_get_berr_counter(स्थिर काष्ठा net_device *dev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);

	bec->txerr = cc770_पढ़ो_reg(priv, tx_error_counter);
	bec->rxerr = cc770_पढ़ो_reg(priv, rx_error_counter);

	वापस 0;
पूर्ण

अटल व्योम cc770_tx(काष्ठा net_device *dev, पूर्णांक mo)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)priv->tx_skb->data;
	u8 dlc, rtr;
	u32 id;
	पूर्णांक i;

	dlc = cf->len;
	id = cf->can_id;
	rtr = cf->can_id & CAN_RTR_FLAG ? 0 : MSGCFG_सूची;

	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_RES | TXIE_RES | RXIE_RES | INTPND_RES);
	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
			RMTPND_RES | TXRQST_RES | CPUUPD_SET | NEWDAT_RES);

	अगर (id & CAN_EFF_FLAG) अणु
		id &= CAN_EFF_MASK;
		cc770_ग_लिखो_reg(priv, msgobj[mo].config,
				(dlc << 4) | rtr | MSGCFG_XTD);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[3], id << 3);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[2], id >> 5);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[1], id >> 13);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[0], id >> 21);
	पूर्ण अन्यथा अणु
		id &= CAN_SFF_MASK;
		cc770_ग_लिखो_reg(priv, msgobj[mo].config, (dlc << 4) | rtr);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[0], id >> 3);
		cc770_ग_लिखो_reg(priv, msgobj[mo].id[1], id << 5);
	पूर्ण

	क्रम (i = 0; i < dlc; i++)
		cc770_ग_लिखो_reg(priv, msgobj[mo].data[i], cf->data[i]);

	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
			RMTPND_UNC | TXRQST_SET | CPUUPD_RES | NEWDAT_UNC);
	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_SET | TXIE_SET | RXIE_SET | INTPND_UNC);
पूर्ण

अटल netdev_tx_t cc770_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक mo = obj2msgobj(CC770_OBJ_TX);

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(dev);

	अगर ((cc770_पढ़ो_reg(priv,
			    msgobj[mo].ctrl1) & TXRQST_UNC) == TXRQST_SET) अणु
		netdev_err(dev, "TX register is still occupied!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	priv->tx_skb = skb;
	cc770_tx(dev, mo);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम cc770_rx(काष्ठा net_device *dev, अचिन्हित पूर्णांक mo, u8 ctrl1)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u8 config;
	u32 id;
	पूर्णांक i;

	skb = alloc_can_skb(dev, &cf);
	अगर (!skb)
		वापस;

	config = cc770_पढ़ो_reg(priv, msgobj[mo].config);

	अगर (ctrl1 & RMTPND_SET) अणु
		/*
		 * Unक्रमtunately, the chip करोes not store the real message
		 * identअगरier of the received remote transmission request
		 * frame. Thereक्रमe we set it to 0.
		 */
		cf->can_id = CAN_RTR_FLAG;
		अगर (config & MSGCFG_XTD)
			cf->can_id |= CAN_EFF_FLAG;
		cf->len = 0;
	पूर्ण अन्यथा अणु
		अगर (config & MSGCFG_XTD) अणु
			id = cc770_पढ़ो_reg(priv, msgobj[mo].id[3]);
			id |= cc770_पढ़ो_reg(priv, msgobj[mo].id[2]) << 8;
			id |= cc770_पढ़ो_reg(priv, msgobj[mo].id[1]) << 16;
			id |= cc770_पढ़ो_reg(priv, msgobj[mo].id[0]) << 24;
			id >>= 3;
			id |= CAN_EFF_FLAG;
		पूर्ण अन्यथा अणु
			id = cc770_पढ़ो_reg(priv, msgobj[mo].id[1]);
			id |= cc770_पढ़ो_reg(priv, msgobj[mo].id[0]) << 8;
			id >>= 5;
		पूर्ण

		cf->can_id = id;
		cf->len = can_cc_dlc2len((config & 0xf0) >> 4);
		क्रम (i = 0; i < cf->len; i++)
			cf->data[i] = cc770_पढ़ो_reg(priv, msgobj[mo].data[i]);
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल पूर्णांक cc770_err(काष्ठा net_device *dev, u8 status)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u8 lec;

	netdev_dbg(dev, "status interrupt (%#x)\n", status);

	skb = alloc_can_err_skb(dev, &cf);
	अगर (!skb)
		वापस -ENOMEM;

	/* Use extended functions of the CC770 */
	अगर (priv->control_normal_mode & CTRL_EAF) अणु
		cf->data[6] = cc770_पढ़ो_reg(priv, tx_error_counter);
		cf->data[7] = cc770_पढ़ो_reg(priv, rx_error_counter);
	पूर्ण

	अगर (status & STAT_BOFF) अणु
		/* Disable पूर्णांकerrupts */
		cc770_ग_लिखो_reg(priv, control, CTRL_INI);
		cf->can_id |= CAN_ERR_BUSOFF;
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(dev);
	पूर्ण अन्यथा अगर (status & STAT_WARN) अणु
		cf->can_id |= CAN_ERR_CRTL;
		/* Only the CC770 करोes show error passive */
		अगर (cf->data[7] > 127) अणु
			cf->data[1] = CAN_ERR_CRTL_RX_PASSIVE |
				CAN_ERR_CRTL_TX_PASSIVE;
			priv->can.state = CAN_STATE_ERROR_PASSIVE;
			priv->can.can_stats.error_passive++;
		पूर्ण अन्यथा अणु
			cf->data[1] = CAN_ERR_CRTL_RX_WARNING |
				CAN_ERR_CRTL_TX_WARNING;
			priv->can.state = CAN_STATE_ERROR_WARNING;
			priv->can.can_stats.error_warning++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Back to error active */
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
	पूर्ण

	lec = status & STAT_LEC_MASK;
	अगर (lec < 7 && lec > 0) अणु
		अगर (lec == STAT_LEC_ACK) अणु
			cf->can_id |= CAN_ERR_ACK;
		पूर्ण अन्यथा अणु
			cf->can_id |= CAN_ERR_PROT;
			चयन (lec) अणु
			हाल STAT_LEC_STUFF:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				अवरोध;
			हाल STAT_LEC_FORM:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				अवरोध;
			हाल STAT_LEC_BIT1:
				cf->data[2] |= CAN_ERR_PROT_BIT1;
				अवरोध;
			हाल STAT_LEC_BIT0:
				cf->data[2] |= CAN_ERR_PROT_BIT0;
				अवरोध;
			हाल STAT_LEC_CRC:
				cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण


	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_status_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	u8 status;

	status = cc770_पढ़ो_reg(priv, status);
	/* Reset the status रेजिस्टर including RXOK and TXOK */
	cc770_ग_लिखो_reg(priv, status, STAT_LEC_MASK);

	अगर (status & (STAT_WARN | STAT_BOFF) ||
	    (status & STAT_LEC_MASK) != STAT_LEC_MASK) अणु
		cc770_err(dev, status);
		वापस status & STAT_BOFF;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cc770_rx_पूर्णांकerrupt(काष्ठा net_device *dev, अचिन्हित पूर्णांक o)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित पूर्णांक mo = obj2msgobj(o);
	u8 ctrl1;
	पूर्णांक n = CC770_MAX_MSG;

	जबतक (n--) अणु
		ctrl1 = cc770_पढ़ो_reg(priv, msgobj[mo].ctrl1);

		अगर (!(ctrl1 & NEWDAT_SET))  अणु
			/* Check क्रम RTR अगर additional functions are enabled */
			अगर (priv->control_normal_mode & CTRL_EAF) अणु
				अगर (!(cc770_पढ़ो_reg(priv, msgobj[mo].ctrl0) &
				      INTPND_SET))
					अवरोध;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ctrl1 & MSGLST_SET) अणु
			stats->rx_over_errors++;
			stats->rx_errors++;
		पूर्ण
		अगर (mo < MSGOBJ_LAST)
			cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
					NEWDAT_RES | MSGLST_RES |
					TXRQST_UNC | RMTPND_UNC);
		cc770_rx(dev, mo, ctrl1);

		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
				MSGVAL_SET | TXIE_RES |
				RXIE_SET | INTPND_RES);
		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
				NEWDAT_RES | MSGLST_RES |
				TXRQST_RES | RMTPND_RES);
	पूर्ण
पूर्ण

अटल व्योम cc770_rtr_पूर्णांकerrupt(काष्ठा net_device *dev, अचिन्हित पूर्णांक o)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक mo = obj2msgobj(o);
	u8 ctrl0, ctrl1;
	पूर्णांक n = CC770_MAX_MSG;

	जबतक (n--) अणु
		ctrl0 = cc770_पढ़ो_reg(priv, msgobj[mo].ctrl0);
		अगर (!(ctrl0 & INTPND_SET))
			अवरोध;

		ctrl1 = cc770_पढ़ो_reg(priv, msgobj[mo].ctrl1);
		cc770_rx(dev, mo, ctrl1);

		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
				MSGVAL_SET | TXIE_RES |
				RXIE_SET | INTPND_RES);
		cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
				NEWDAT_RES | CPUUPD_SET |
				TXRQST_RES | RMTPND_RES);
	पूर्ण
पूर्ण

अटल व्योम cc770_tx_पूर्णांकerrupt(काष्ठा net_device *dev, अचिन्हित पूर्णांक o)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित पूर्णांक mo = obj2msgobj(o);
	काष्ठा can_frame *cf;
	u8 ctrl1;

	ctrl1 = cc770_पढ़ो_reg(priv, msgobj[mo].ctrl1);

	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_RES | TXIE_RES | RXIE_RES | INTPND_RES);
	cc770_ग_लिखो_reg(priv, msgobj[mo].ctrl1,
			RMTPND_RES | TXRQST_RES | MSGLST_RES | NEWDAT_RES);

	अगर (unlikely(!priv->tx_skb)) अणु
		netdev_err(dev, "missing tx skb in tx interrupt\n");
		वापस;
	पूर्ण

	अगर (unlikely(ctrl1 & MSGLST_SET)) अणु
		stats->rx_over_errors++;
		stats->rx_errors++;
	पूर्ण

	/* When the CC770 is sending an RTR message and it receives a regular
	 * message that matches the id of the RTR message, it will overग_लिखो the
	 * outgoing message in the TX रेजिस्टर. When this happens we must
	 * process the received message and try to transmit the outgoing skb
	 * again.
	 */
	अगर (unlikely(ctrl1 & NEWDAT_SET)) अणु
		cc770_rx(dev, mo, ctrl1);
		cc770_tx(dev, mo);
		वापस;
	पूर्ण

	cf = (काष्ठा can_frame *)priv->tx_skb->data;
	stats->tx_bytes += cf->len;
	stats->tx_packets++;

	can_put_echo_skb(priv->tx_skb, dev, 0, 0);
	can_get_echo_skb(dev, 0, शून्य);
	priv->tx_skb = शून्य;

	netअगर_wake_queue(dev);
पूर्ण

अटल irqवापस_t cc770_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	u8 पूर्णांकid;
	पूर्णांक o, n = 0;

	/* Shared पूर्णांकerrupts and IRQ off? */
	अगर (priv->can.state == CAN_STATE_STOPPED)
		वापस IRQ_NONE;

	अगर (priv->pre_irq)
		priv->pre_irq(priv);

	जबतक (n < CC770_MAX_IRQ) अणु
		/* Read the highest pending पूर्णांकerrupt request */
		पूर्णांकid = cc770_पढ़ो_reg(priv, पूर्णांकerrupt);
		अगर (!पूर्णांकid)
			अवरोध;
		n++;

		अगर (पूर्णांकid == 1) अणु
			/* Exit in हाल of bus-off */
			अगर (cc770_status_पूर्णांकerrupt(dev))
				अवरोध;
		पूर्ण अन्यथा अणु
			o = पूर्णांकid2obj(पूर्णांकid);

			अगर (o >= CC770_OBJ_MAX) अणु
				netdev_err(dev, "Unexpected interrupt id %d\n",
					   पूर्णांकid);
				जारी;
			पूर्ण

			अगर (priv->obj_flags[o] & CC770_OBJ_FLAG_RTR)
				cc770_rtr_पूर्णांकerrupt(dev, o);
			अन्यथा अगर (priv->obj_flags[o] & CC770_OBJ_FLAG_RX)
				cc770_rx_पूर्णांकerrupt(dev, o);
			अन्यथा
				cc770_tx_पूर्णांकerrupt(dev, o);
		पूर्ण
	पूर्ण

	अगर (priv->post_irq)
		priv->post_irq(priv);

	अगर (n >= CC770_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	वापस (n) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक cc770_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	/* set chip पूर्णांकo reset mode */
	set_reset_mode(dev);

	/* common खोलो */
	err = खोलो_candev(dev);
	अगर (err)
		वापस err;

	err = request_irq(dev->irq, &cc770_पूर्णांकerrupt, priv->irq_flags,
			  dev->name, dev);
	अगर (err) अणु
		बंद_candev(dev);
		वापस -EAGAIN;
	पूर्ण

	/* init and start chip */
	cc770_start(dev);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	set_reset_mode(dev);

	मुक्त_irq(dev->irq, dev);
	बंद_candev(dev);

	वापस 0;
पूर्ण

काष्ठा net_device *alloc_cc770dev(पूर्णांक माप_priv)
अणु
	काष्ठा net_device *dev;
	काष्ठा cc770_priv *priv;

	dev = alloc_candev(माप(काष्ठा cc770_priv) + माप_priv,
			   CC770_ECHO_SKB_MAX);
	अगर (!dev)
		वापस शून्य;

	priv = netdev_priv(dev);

	priv->dev = dev;
	priv->can.bittiming_स्थिर = &cc770_bittiming_स्थिर;
	priv->can.करो_set_bittiming = cc770_set_bittiming;
	priv->can.करो_set_mode = cc770_set_mode;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;
	priv->tx_skb = शून्य;

	स_नकल(priv->obj_flags, cc770_obj_flags, माप(cc770_obj_flags));

	अगर (माप_priv)
		priv->priv = (व्योम *)priv + माप(काष्ठा cc770_priv);

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_cc770dev);

व्योम मुक्त_cc770dev(काष्ठा net_device *dev)
अणु
	मुक्त_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_cc770dev);

अटल स्थिर काष्ठा net_device_ops cc770_netdev_ops = अणु
	.nकरो_खोलो = cc770_खोलो,
	.nकरो_stop = cc770_बंद,
	.nकरो_start_xmit = cc770_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

पूर्णांक रेजिस्टर_cc770dev(काष्ठा net_device *dev)
अणु
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = cc770_probe_chip(dev);
	अगर (err)
		वापस err;

	dev->netdev_ops = &cc770_netdev_ops;

	dev->flags |= IFF_ECHO;	/* we support local echo */

	/* Should we use additional functions? */
	अगर (!i82527_compat && priv->control_normal_mode & CTRL_EAF) अणु
		priv->can.करो_get_berr_counter = cc770_get_berr_counter;
		priv->control_normal_mode = CTRL_IE | CTRL_EAF | CTRL_EIE;
		netdev_dbg(dev, "i82527 mode with additional functions\n");
	पूर्ण अन्यथा अणु
		priv->control_normal_mode = CTRL_IE | CTRL_EIE;
		netdev_dbg(dev, "strict i82527 compatibility mode\n");
	पूर्ण

	chipset_init(priv);
	set_reset_mode(dev);

	वापस रेजिस्टर_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_cc770dev);

व्योम unरेजिस्टर_cc770dev(काष्ठा net_device *dev)
अणु
	set_reset_mode(dev);
	unरेजिस्टर_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_cc770dev);

अटल __init पूर्णांक cc770_init(व्योम)
अणु
	अगर (msgobj15_eff) अणु
		cc770_obj_flags[CC770_OBJ_RX0] |= CC770_OBJ_FLAG_EFF;
		cc770_obj_flags[CC770_OBJ_RX1] &= ~CC770_OBJ_FLAG_EFF;
	पूर्ण

	pr_info("CAN netdevice driver\n");

	वापस 0;
पूर्ण
module_init(cc770_init);

अटल __निकास व्योम cc770_निकास(व्योम)
अणु
	pr_info("driver removed\n");
पूर्ण
module_निकास(cc770_निकास);
