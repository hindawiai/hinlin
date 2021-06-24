<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*=============================================================================
 *
 * A  PCMCIA client driver क्रम the Raylink wireless LAN card.
 * The starting poपूर्णांक क्रम this module was the skeleton.c in the
 * PCMCIA 2.9.12 package written by David Hinds, dahinds@users.sourceक्रमge.net
 *
 * Copyright (c) 1998  Corey Thomas (corey@world.std.com)
 *
 * Changes:
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - 08/08/2000
 * - reorganize kदो_स्मृतिs in ray_attach, checking all क्रम failure
 *   and releasing the previous allocations अगर one fails
 *
 * Daniele Bellucci <bellucda@tiscali.it> - 07/10/2003
 * - Audit copy_to_user in ioctl(SIOCGIWESSID)
 *
=============================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ieee80211.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

/* Warning : these stuff will slow करोwn the driver... */
#घोषणा WIRELESS_SPY		/* Enable spying addresses */
/* Definitions we need क्रम spy */
प्रकार काष्ठा iw_statistics iw_stats;
प्रकार u_अक्षर mac_addr[ETH_ALEN];	/* Hardware address */

#समावेश "rayctl.h"
#समावेश "ray_cs.h"


/** Prototypes based on PCMCIA skeleton driver *******************************/
अटल पूर्णांक ray_config(काष्ठा pcmcia_device *link);
अटल व्योम ray_release(काष्ठा pcmcia_device *link);
अटल व्योम ray_detach(काष्ठा pcmcia_device *p_dev);

/***** Prototypes indicated by device काष्ठाure ******************************/
अटल पूर्णांक ray_dev_बंद(काष्ठा net_device *dev);
अटल पूर्णांक ray_dev_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल काष्ठा net_device_stats *ray_get_stats(काष्ठा net_device *dev);
अटल पूर्णांक ray_dev_init(काष्ठा net_device *dev);

अटल पूर्णांक ray_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t ray_dev_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल व्योम ray_update_multi_list(काष्ठा net_device *dev, पूर्णांक all);
अटल पूर्णांक translate_frame(ray_dev_t *local, काष्ठा tx_msg __iomem *ptx,
			   अचिन्हित अक्षर *data, पूर्णांक len);
अटल व्योम ray_build_header(ray_dev_t *local, काष्ठा tx_msg __iomem *ptx,
			     UCHAR msg_type, अचिन्हित अक्षर *data);
अटल व्योम untranslate(ray_dev_t *local, काष्ठा sk_buff *skb, पूर्णांक len);
अटल iw_stats *ray_get_wireless_stats(काष्ठा net_device *dev);
अटल स्थिर काष्ठा iw_handler_def ray_handler_def;

/***** Prototypes क्रम raylink functions **************************************/
अटल व्योम authenticate(ray_dev_t *local);
अटल पूर्णांक build_auth_frame(ray_dev_t *local, UCHAR *dest, पूर्णांक auth_type);
अटल व्योम authenticate_समयout(काष्ठा समयr_list *t);
अटल पूर्णांक get_मुक्त_ccs(ray_dev_t *local);
अटल पूर्णांक get_मुक्त_tx_ccs(ray_dev_t *local);
अटल व्योम init_startup_params(ray_dev_t *local);
अटल पूर्णांक parse_addr(अक्षर *in_str, UCHAR *out);
अटल पूर्णांक ray_hw_xmit(अचिन्हित अक्षर *data, पूर्णांक len, काष्ठा net_device *dev, UCHAR type);
अटल पूर्णांक ray_init(काष्ठा net_device *dev);
अटल पूर्णांक पूर्णांकerrupt_ecf(ray_dev_t *local, पूर्णांक ccs);
अटल व्योम ray_reset(काष्ठा net_device *dev);
अटल व्योम ray_update_parm(काष्ठा net_device *dev, UCHAR objid, UCHAR *value, पूर्णांक len);
अटल व्योम verअगरy_dl_startup(काष्ठा समयr_list *t);

/* Prototypes क्रम पूर्णांकerrpt समय functions **********************************/
अटल irqवापस_t ray_पूर्णांकerrupt(पूर्णांक reg, व्योम *dev_id);
अटल व्योम clear_पूर्णांकerrupt(ray_dev_t *local);
अटल व्योम rx_deauthenticate(ray_dev_t *local, काष्ठा rcs __iomem *prcs,
			      अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len);
अटल पूर्णांक copy_from_rx_buff(ray_dev_t *local, UCHAR *dest, पूर्णांक pkt_addr, पूर्णांक len);
अटल व्योम ray_rx(काष्ठा net_device *dev, ray_dev_t *local, काष्ठा rcs __iomem *prcs);
अटल व्योम release_frag_chain(ray_dev_t *local, काष्ठा rcs __iomem *prcs);
अटल व्योम rx_authenticate(ray_dev_t *local, काष्ठा rcs __iomem *prcs,
			    अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len);
अटल व्योम rx_data(काष्ठा net_device *dev, काष्ठा rcs __iomem *prcs,
		    अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len);
अटल व्योम associate(ray_dev_t *local);

/* Card command functions */
अटल पूर्णांक dl_startup_params(काष्ठा net_device *dev);
अटल व्योम join_net(काष्ठा समयr_list *t);
अटल व्योम start_net(काष्ठा समयr_list *t);

/*===========================================================================*/
/* Parameters that can be set with 'insmod' */

/* ADHOC=0, Infraकाष्ठाure=1 */
अटल पूर्णांक net_type = ADHOC;

/* Hop dwell समय in Kus (1024 us units defined by 802.11) */
अटल पूर्णांक hop_dwell = 128;

/* Beacon period in Kus */
अटल पूर्णांक beacon_period = 256;

/* घातer save mode (0 = off, 1 = save घातer) */
अटल पूर्णांक psm;

/* String क्रम network's Extended Service Set ID. 32 Characters max */
अटल अक्षर *essid;

/* Default to encapsulation unless translation requested */
अटल bool translate = true;

अटल पूर्णांक country = USA;

अटल पूर्णांक snअगरfer;

अटल पूर्णांक bc;

/* 48 bit physical card address अगर overriding card's real physical
 * address is required.  Since IEEE 802.11 addresses are 48 bits
 * like ethernet, an पूर्णांक can't be used, so a string is used. To
 * allow use of addresses starting with a decimal digit, the first
 * अक्षरacter must be a letter and will be ignored. This letter is
 * followed by up to 12 hex digits which are the address.  If less
 * than 12 digits are used, the address will be left filled with 0's.
 * Note that bit 0 of the first byte is the broadcast bit, and evil
 * things will happen अगर it is not 0 in a card address.
 */
अटल अक्षर *phy_addr = शून्य;

अटल अचिन्हित पूर्णांक ray_mem_speed = 500;

/* WARNING: THIS DRIVER IS NOT CAPABLE OF HANDLING MULTIPLE DEVICES! */
अटल काष्ठा pcmcia_device *this_device = शून्य;

MODULE_AUTHOR("Corey Thomas <corey@world.std.com>");
MODULE_DESCRIPTION("Raylink/WebGear wireless LAN driver");
MODULE_LICENSE("GPL");

module_param(net_type, पूर्णांक, 0);
module_param(hop_dwell, पूर्णांक, 0);
module_param(beacon_period, पूर्णांक, 0);
module_param(psm, पूर्णांक, 0);
module_param(essid, अक्षरp, 0);
module_param(translate, bool, 0);
module_param(country, पूर्णांक, 0);
module_param(snअगरfer, पूर्णांक, 0);
module_param(bc, पूर्णांक, 0);
module_param(phy_addr, अक्षरp, 0);
module_param(ray_mem_speed, पूर्णांक, 0);

अटल स्थिर UCHAR b5_शेष_startup_parms[] = अणु
	0, 0,			/* Adhoc station */
	'L', 'I', 'N', 'U', 'X', 0, 0, 0,	/* 32 अक्षर ESSID */
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 0,			/* Active scan, CA Mode */
	0, 0, 0, 0, 0, 0,	/* No शेष MAC addr  */
	0x7f, 0xff,		/* Frag threshold */
	0x00, 0x80,		/* Hop समय 128 Kus */
	0x01, 0x00,		/* Beacon period 256 Kus */
	0x01, 0x07, 0xa3,	/* DTIM, retries, ack समयout */
	0x1d, 0x82, 0x4e,	/* SIFS, DIFS, PIFS */
	0x7f, 0xff,		/* RTS threshold */
	0x04, 0xe2, 0x38, 0xA4,	/* scan_dwell, max_scan_dwell */
	0x05,			/* assoc resp समयout thresh */
	0x08, 0x02, 0x08,	/* adhoc, infra, super cycle max */
	0,			/* Promiscuous mode */
	0x0c, 0x0bd,		/* Unique word */
	0x32,			/* Slot समय */
	0xff, 0xff,		/* roam-low snr, low snr count */
	0x05, 0xff,		/* Infra, adhoc missed bcn thresh */
	0x01, 0x0b, 0x4f,	/* USA, hop pattern, hop pat length */
/* b4 - b5 dअगरferences start here */
	0x00, 0x3f,		/* CW max */
	0x00, 0x0f,		/* CW min */
	0x04, 0x08,		/* Noise gain, limit offset */
	0x28, 0x28,		/* det rssi, med busy offsets */
	7,			/* det sync thresh */
	0, 2, 2,		/* test mode, min, max */
	0,			/* allow broadcast SSID probe resp */
	0, 0,			/* privacy must start, can join */
	2, 0, 0, 0, 0, 0, 0, 0	/* basic rate set */
पूर्ण;

अटल स्थिर UCHAR b4_शेष_startup_parms[] = अणु
	0, 0,			/* Adhoc station */
	'L', 'I', 'N', 'U', 'X', 0, 0, 0,	/* 32 अक्षर ESSID */
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 0,			/* Active scan, CA Mode */
	0, 0, 0, 0, 0, 0,	/* No शेष MAC addr  */
	0x7f, 0xff,		/* Frag threshold */
	0x02, 0x00,		/* Hop समय */
	0x00, 0x01,		/* Beacon period */
	0x01, 0x07, 0xa3,	/* DTIM, retries, ack समयout */
	0x1d, 0x82, 0xce,	/* SIFS, DIFS, PIFS */
	0x7f, 0xff,		/* RTS threshold */
	0xfb, 0x1e, 0xc7, 0x5c,	/* scan_dwell, max_scan_dwell */
	0x05,			/* assoc resp समयout thresh */
	0x04, 0x02, 0x4,	/* adhoc, infra, super cycle max */
	0,			/* Promiscuous mode */
	0x0c, 0x0bd,		/* Unique word */
	0x4e,			/* Slot समय (TBD seems wrong) */
	0xff, 0xff,		/* roam-low snr, low snr count */
	0x05, 0xff,		/* Infra, adhoc missed bcn thresh */
	0x01, 0x0b, 0x4e,	/* USA, hop pattern, hop pat length */
/* b4 - b5 dअगरferences start here */
	0x3f, 0x0f,		/* CW max, min */
	0x04, 0x08,		/* Noise gain, limit offset */
	0x28, 0x28,		/* det rssi, med busy offsets */
	7,			/* det sync thresh */
	0, 2, 2,		/* test mode, min, max */
	0,			/* rx/tx delay */
	0, 0, 0, 0, 0, 0,	/* current BSS id */
	0			/* hop set */
पूर्ण;

/*===========================================================================*/
अटल स्थिर u8 eth2_llc[] = अणु 0xaa, 0xaa, 3, 0, 0, 0 पूर्ण;

अटल स्थिर अक्षर hop_pattern_length[] = अणु 1,
	USA_HOP_MOD, EUROPE_HOP_MOD,
	JAPAN_HOP_MOD, KOREA_HOP_MOD,
	SPAIN_HOP_MOD, FRANCE_HOP_MOD,
	ISRAEL_HOP_MOD, AUSTRALIA_HOP_MOD,
	JAPAN_TEST_HOP_MOD
पूर्ण;

अटल स्थिर अक्षर rcsid[] =
    "Raylink/WebGear wireless LAN - Corey <Thomas corey@world.std.com>";

अटल स्थिर काष्ठा net_device_ops ray_netdev_ops = अणु
	.nकरो_init 		= ray_dev_init,
	.nकरो_खोलो 		= ray_खोलो,
	.nकरो_stop 		= ray_dev_बंद,
	.nकरो_start_xmit		= ray_dev_start_xmit,
	.nकरो_set_config		= ray_dev_config,
	.nकरो_get_stats		= ray_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक ray_probe(काष्ठा pcmcia_device *p_dev)
अणु
	ray_dev_t *local;
	काष्ठा net_device *dev;

	dev_dbg(&p_dev->dev, "ray_attach()\n");

	/* Allocate space क्रम निजी device-specअगरic data */
	dev = alloc_etherdev(माप(ray_dev_t));
	अगर (!dev)
		जाओ fail_alloc_dev;

	local = netdev_priv(dev);
	local->finder = p_dev;

	/* The io काष्ठाure describes IO port mapping. None used here */
	p_dev->resource[0]->end = 0;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	/* General socket configuration */
	p_dev->config_flags |= CONF_ENABLE_IRQ;
	p_dev->config_index = 1;

	p_dev->priv = dev;

	local->finder = p_dev;
	local->card_status = CARD_INSERTED;
	local->authentication_state = UNAUTHENTICATED;
	local->num_multi = 0;
	dev_dbg(&p_dev->dev, "ray_attach p_dev = %p,  dev = %p,  local = %p, intr = %p\n",
	      p_dev, dev, local, &ray_पूर्णांकerrupt);

	/* Raylink entries in the device काष्ठाure */
	dev->netdev_ops = &ray_netdev_ops;
	dev->wireless_handlers = &ray_handler_def;
#अगर_घोषित WIRELESS_SPY
	local->wireless_data.spy_data = &local->spy_data;
	dev->wireless_data = &local->wireless_data;
#पूर्ण_अगर /* WIRELESS_SPY */


	dev_dbg(&p_dev->dev, "ray_cs ray_attach calling ether_setup.)\n");
	netअगर_stop_queue(dev);

	समयr_setup(&local->समयr, शून्य, 0);

	this_device = p_dev;
	वापस ray_config(p_dev);

fail_alloc_dev:
	वापस -ENOMEM;
पूर्ण /* ray_attach */

अटल व्योम ray_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev;
	ray_dev_t *local;

	dev_dbg(&link->dev, "ray_detach\n");

	this_device = शून्य;
	dev = link->priv;

	ray_release(link);

	local = netdev_priv(dev);
	del_समयr_sync(&local->समयr);

	अगर (link->priv) अणु
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
	पूर्ण
	dev_dbg(&link->dev, "ray_cs ray_detach ending\n");
पूर्ण /* ray_detach */

#घोषणा MAX_TUPLE_SIZE 128
अटल पूर्णांक ray_config(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा net_device *dev = (काष्ठा net_device *)link->priv;
	ray_dev_t *local = netdev_priv(dev);

	dev_dbg(&link->dev, "ray_config\n");

	/* Determine card type and firmware version */
	prपूर्णांकk(KERN_INFO "ray_cs Detected: %s%s%s%s\n",
	       link->prod_id[0] ? link->prod_id[0] : " ",
	       link->prod_id[1] ? link->prod_id[1] : " ",
	       link->prod_id[2] ? link->prod_id[2] : " ",
	       link->prod_id[3] ? link->prod_id[3] : " ");

	/* Now allocate an पूर्णांकerrupt line.  Note that this करोes not
	   actually assign a handler to the पूर्णांकerrupt.
	 */
	ret = pcmcia_request_irq(link, ray_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;
	dev->irq = link->irq;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

/*** Set up 32k winकरोw क्रम shared memory (transmit and control) ************/
	link->resource[2]->flags |= WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_CM | WIN_ENABLE | WIN_USE_WAIT;
	link->resource[2]->start = 0;
	link->resource[2]->end = 0x8000;
	ret = pcmcia_request_winकरोw(link, link->resource[2], ray_mem_speed);
	अगर (ret)
		जाओ failed;
	ret = pcmcia_map_mem_page(link, link->resource[2], 0);
	अगर (ret)
		जाओ failed;
	local->sram = ioremap(link->resource[2]->start,
			resource_size(link->resource[2]));

/*** Set up 16k winकरोw क्रम shared memory (receive buffer) ***************/
	link->resource[3]->flags |=
	    WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_CM | WIN_ENABLE | WIN_USE_WAIT;
	link->resource[3]->start = 0;
	link->resource[3]->end = 0x4000;
	ret = pcmcia_request_winकरोw(link, link->resource[3], ray_mem_speed);
	अगर (ret)
		जाओ failed;
	ret = pcmcia_map_mem_page(link, link->resource[3], 0x8000);
	अगर (ret)
		जाओ failed;
	local->rmem = ioremap(link->resource[3]->start,
			resource_size(link->resource[3]));

/*** Set up winकरोw क्रम attribute memory ***********************************/
	link->resource[4]->flags |=
	    WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_AM | WIN_ENABLE | WIN_USE_WAIT;
	link->resource[4]->start = 0;
	link->resource[4]->end = 0x1000;
	ret = pcmcia_request_winकरोw(link, link->resource[4], ray_mem_speed);
	अगर (ret)
		जाओ failed;
	ret = pcmcia_map_mem_page(link, link->resource[4], 0);
	अगर (ret)
		जाओ failed;
	local->amem = ioremap(link->resource[4]->start,
			resource_size(link->resource[4]));

	dev_dbg(&link->dev, "ray_config sram=%p\n", local->sram);
	dev_dbg(&link->dev, "ray_config rmem=%p\n", local->rmem);
	dev_dbg(&link->dev, "ray_config amem=%p\n", local->amem);
	अगर (ray_init(dev) < 0) अणु
		ray_release(link);
		वापस -ENODEV;
	पूर्ण

	SET_NETDEV_DEV(dev, &link->dev);
	i = रेजिस्टर_netdev(dev);
	अगर (i != 0) अणु
		prपूर्णांकk("ray_config register_netdev() failed\n");
		ray_release(link);
		वापस i;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: RayLink, irq %d, hw_addr %pM\n",
	       dev->name, dev->irq, dev->dev_addr);

	वापस 0;

failed:
	ray_release(link);
	वापस -ENODEV;
पूर्ण /* ray_config */

अटल अंतरभूत काष्ठा ccs __iomem *ccs_base(ray_dev_t *dev)
अणु
	वापस dev->sram + CCS_BASE;
पूर्ण

अटल अंतरभूत काष्ठा rcs __iomem *rcs_base(ray_dev_t *dev)
अणु
	/*
	 * This looks nonsensical, since there is a separate
	 * RCS_BASE. But the dअगरference between a "struct rcs"
	 * and a "struct ccs" ends up being in the _index_ off
	 * the base, so the base poपूर्णांकer is the same क्रम both
	 * ccs/rcs.
	 */
	वापस dev->sram + CCS_BASE;
पूर्ण

/*===========================================================================*/
अटल पूर्णांक ray_init(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा ccs __iomem *pccs;
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	dev_dbg(&link->dev, "ray_init(0x%p)\n", dev);
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_init - device not present\n");
		वापस -1;
	पूर्ण

	local->net_type = net_type;
	local->sta_type = TYPE_STA;

	/* Copy the startup results to local memory */
	स_नकल_fromio(&local->startup_res, local->sram + ECF_TO_HOST_BASE,
		      माप(काष्ठा startup_res_6));

	/* Check Power up test status and get mac address from card */
	अगर (local->startup_res.startup_word != 0x80) अणु
		prपूर्णांकk(KERN_INFO "ray_init ERROR card status = %2x\n",
		       local->startup_res.startup_word);
		local->card_status = CARD_INIT_ERROR;
		वापस -1;
	पूर्ण

	local->fw_ver = local->startup_res.firmware_version[0];
	local->fw_bld = local->startup_res.firmware_version[1];
	local->fw_var = local->startup_res.firmware_version[2];
	dev_dbg(&link->dev, "ray_init firmware version %d.%d\n", local->fw_ver,
	      local->fw_bld);

	local->tib_length = 0x20;
	अगर ((local->fw_ver == 5) && (local->fw_bld >= 30))
		local->tib_length = local->startup_res.tib_length;
	dev_dbg(&link->dev, "ray_init tib_length = 0x%02x\n", local->tib_length);
	/* Initialize CCS's to buffer मुक्त state */
	pccs = ccs_base(local);
	क्रम (i = 0; i < NUMBER_OF_CCS; i++) अणु
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
	पूर्ण
	init_startup_params(local);

	/* copy mac address to startup parameters */
	अगर (!parse_addr(phy_addr, local->sparm.b4.a_mac_addr)) अणु
		स_नकल(&local->sparm.b4.a_mac_addr,
		       &local->startup_res.station_addr, ADDRLEN);
	पूर्ण

	clear_पूर्णांकerrupt(local);	/* Clear any पूर्णांकerrupt from the card */
	local->card_status = CARD_AWAITING_PARAM;
	dev_dbg(&link->dev, "ray_init ending\n");
	वापस 0;
पूर्ण /* ray_init */

/*===========================================================================*/
/* Download startup parameters to the card and command it to पढ़ो them       */
अटल पूर्णांक dl_startup_params(काष्ठा net_device *dev)
अणु
	पूर्णांक ccsindex;
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा ccs __iomem *pccs;
	काष्ठा pcmcia_device *link = local->finder;

	dev_dbg(&link->dev, "dl_startup_params entered\n");
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs dl_startup_params - device not present\n");
		वापस -1;
	पूर्ण

	/* Copy parameters to host to ECF area */
	अगर (local->fw_ver == 0x55)
		स_नकल_toio(local->sram + HOST_TO_ECF_BASE, &local->sparm.b4,
			    माप(काष्ठा b4_startup_params));
	अन्यथा
		स_नकल_toio(local->sram + HOST_TO_ECF_BASE, &local->sparm.b5,
			    माप(काष्ठा b5_startup_params));

	/* Fill in the CCS fields क्रम the ECF */
	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0)
		वापस -1;
	local->dl_param_ccs = ccsindex;
	pccs = ccs_base(local) + ccsindex;
	ग_लिखोb(CCS_DOWNLOAD_STARTUP_PARAMS, &pccs->cmd);
	dev_dbg(&link->dev, "dl_startup_params start ccsindex = %d\n",
	      local->dl_param_ccs);
	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		prपूर्णांकk(KERN_INFO "ray dl_startup_params failed - "
		       "ECF not ready for intr\n");
		local->card_status = CARD_DL_PARAM_ERROR;
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
		वापस -2;
	पूर्ण
	local->card_status = CARD_DL_PARAM;
	/* Start kernel समयr to रुको क्रम dl startup to complete. */
	local->समयr.expires = jअगरfies + HZ / 2;
	local->समयr.function = verअगरy_dl_startup;
	add_समयr(&local->समयr);
	dev_dbg(&link->dev,
	      "ray_cs dl_startup_params started timer for verify_dl_startup\n");
	वापस 0;
पूर्ण /* dl_startup_params */

/*===========================================================================*/
अटल व्योम init_startup_params(ray_dev_t *local)
अणु
	पूर्णांक i;

	अगर (country > JAPAN_TEST)
		country = USA;
	अन्यथा अगर (country < USA)
		country = USA;
	/* काष्ठाure क्रम hop समय and beacon period is defined here using
	 * New 802.11D6.1 क्रमmat.  Card firmware is still using old क्रमmat
	 * until version 6.
	 *    Beक्रमe                    After
	 *    a_hop_समय ms byte        a_hop_समय ms byte
	 *    a_hop_समय 2s byte        a_hop_समय ls byte
	 *    a_hop_समय ls byte        a_beacon_period ms byte
	 *    a_beacon_period           a_beacon_period ls byte
	 *
	 *    a_hop_समय = uS           a_hop_समय = KuS
	 *    a_beacon_period = hops    a_beacon_period = KuS
	 *//* 64ms = 010000 */
	अगर (local->fw_ver == 0x55) अणु
		स_नकल(&local->sparm.b4, b4_शेष_startup_parms,
		       माप(काष्ठा b4_startup_params));
		/* Translate sane kus input values to old build 4/5 क्रमmat */
		/* i = hop समय in uS truncated to 3 bytes */
		i = (hop_dwell * 1024) & 0xffffff;
		local->sparm.b4.a_hop_समय[0] = (i >> 16) & 0xff;
		local->sparm.b4.a_hop_समय[1] = (i >> 8) & 0xff;
		local->sparm.b4.a_beacon_period[0] = 0;
		local->sparm.b4.a_beacon_period[1] =
		    ((beacon_period / hop_dwell) - 1) & 0xff;
		local->sparm.b4.a_curr_country_code = country;
		local->sparm.b4.a_hop_pattern_length =
		    hop_pattern_length[(पूर्णांक)country] - 1;
		अगर (bc) अणु
			local->sparm.b4.a_ack_समयout = 0x50;
			local->sparm.b4.a_sअगरs = 0x3f;
		पूर्ण
	पूर्ण अन्यथा अणु /* Version 5 uses real kus values */
		स_नकल((UCHAR *) &local->sparm.b5, b5_शेष_startup_parms,
		       माप(काष्ठा b5_startup_params));

		local->sparm.b5.a_hop_समय[0] = (hop_dwell >> 8) & 0xff;
		local->sparm.b5.a_hop_समय[1] = hop_dwell & 0xff;
		local->sparm.b5.a_beacon_period[0] =
		    (beacon_period >> 8) & 0xff;
		local->sparm.b5.a_beacon_period[1] = beacon_period & 0xff;
		अगर (psm)
			local->sparm.b5.a_घातer_mgt_state = 1;
		local->sparm.b5.a_curr_country_code = country;
		local->sparm.b5.a_hop_pattern_length =
		    hop_pattern_length[(पूर्णांक)country];
	पूर्ण

	local->sparm.b4.a_network_type = net_type & 0x01;
	local->sparm.b4.a_acting_as_ap_status = TYPE_STA;

	अगर (essid != शून्य)
		म_नकलन(local->sparm.b4.a_current_ess_id, essid, ESSID_SIZE);
पूर्ण /* init_startup_params */

/*===========================================================================*/
अटल व्योम verअगरy_dl_startup(काष्ठा समयr_list *t)
अणु
	ray_dev_t *local = from_समयr(local, t, समयr);
	काष्ठा ccs __iomem *pccs = ccs_base(local) + local->dl_param_ccs;
	UCHAR status;
	काष्ठा pcmcia_device *link = local->finder;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs verify_dl_startup - device not present\n");
		वापस;
	पूर्ण
#अगर 0
	अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG
		       "verify_dl_startup parameters sent via ccs %d:\n",
		       local->dl_param_ccs);
		क्रम (i = 0; i < माप(काष्ठा b5_startup_params); i++) अणु
			prपूर्णांकk(" %2x",
			       (अचिन्हित पूर्णांक)पढ़ोb(local->sram +
						   HOST_TO_ECF_BASE + i));
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर

	status = पढ़ोb(&pccs->buffer_status);
	अगर (status != CCS_BUFFER_FREE) अणु
		prपूर्णांकk(KERN_INFO
		       "Download startup params failed.  Status = %d\n",
		       status);
		local->card_status = CARD_DL_PARAM_ERROR;
		वापस;
	पूर्ण
	अगर (local->sparm.b4.a_network_type == ADHOC)
		start_net(&local->समयr);
	अन्यथा
		join_net(&local->समयr);
पूर्ण /* end verअगरy_dl_startup */

/*===========================================================================*/
/* Command card to start a network */
अटल व्योम start_net(काष्ठा समयr_list *t)
अणु
	ray_dev_t *local = from_समयr(local, t, समयr);
	काष्ठा ccs __iomem *pccs;
	पूर्णांक ccsindex;
	काष्ठा pcmcia_device *link = local->finder;
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs start_net - device not present\n");
		वापस;
	पूर्ण
	/* Fill in the CCS fields क्रम the ECF */
	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0)
		वापस;
	pccs = ccs_base(local) + ccsindex;
	ग_लिखोb(CCS_START_NETWORK, &pccs->cmd);
	ग_लिखोb(0, &pccs->var.start_network.update_param);
	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		dev_dbg(&link->dev, "ray start net failed - card not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
		वापस;
	पूर्ण
	local->card_status = CARD_DOING_ACQ;
पूर्ण /* end start_net */

/*===========================================================================*/
/* Command card to join a network */
अटल व्योम join_net(काष्ठा समयr_list *t)
अणु
	ray_dev_t *local = from_समयr(local, t, समयr);

	काष्ठा ccs __iomem *pccs;
	पूर्णांक ccsindex;
	काष्ठा pcmcia_device *link = local->finder;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs join_net - device not present\n");
		वापस;
	पूर्ण
	/* Fill in the CCS fields क्रम the ECF */
	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0)
		वापस;
	pccs = ccs_base(local) + ccsindex;
	ग_लिखोb(CCS_JOIN_NETWORK, &pccs->cmd);
	ग_लिखोb(0, &pccs->var.join_network.update_param);
	ग_लिखोb(0, &pccs->var.join_network.net_initiated);
	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		dev_dbg(&link->dev, "ray join net failed - card not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
		वापस;
	पूर्ण
	local->card_status = CARD_DOING_ACQ;
पूर्ण


अटल व्योम ray_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	ray_dev_t *local = netdev_priv(dev);

	dev_dbg(&link->dev, "ray_release\n");

	del_समयr(&local->समयr);

	iounmap(local->sram);
	iounmap(local->rmem);
	iounmap(local->amem);
	pcmcia_disable_device(link);

	dev_dbg(&link->dev, "ray_release ending\n");
पूर्ण

अटल पूर्णांक ray_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ray_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		ray_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

/*===========================================================================*/
अटल पूर्णांक ray_dev_init(काष्ठा net_device *dev)
अणु
#अगर_घोषित RAY_IMMEDIATE_INIT
	पूर्णांक i;
#पूर्ण_अगर /* RAY_IMMEDIATE_INIT */
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;

	dev_dbg(&link->dev, "ray_dev_init(dev=%p)\n", dev);
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_dev_init - device not present\n");
		वापस -1;
	पूर्ण
#अगर_घोषित RAY_IMMEDIATE_INIT
	/* Download startup parameters */
	अगर ((i = dl_startup_params(dev)) < 0) अणु
		prपूर्णांकk(KERN_INFO "ray_dev_init dl_startup_params failed - "
		       "returns 0x%x\n", i);
		वापस -1;
	पूर्ण
#अन्यथा /* RAY_IMMEDIATE_INIT */
	/* Postpone the card init so that we can still configure the card,
	 * क्रम example using the Wireless Extensions. The init will happen
	 * in ray_खोलो() - Jean II */
	dev_dbg(&link->dev,
	      "ray_dev_init: postponing card init to ray_open() ; Status = %d\n",
	      local->card_status);
#पूर्ण_अगर /* RAY_IMMEDIATE_INIT */

	/* copy mac and broadcast addresses to linux device */
	स_नकल(dev->dev_addr, &local->sparm.b4.a_mac_addr, ADDRLEN);
	eth_broadcast_addr(dev->broadcast);

	dev_dbg(&link->dev, "ray_dev_init ending\n");
	वापस 0;
पूर्ण

/*===========================================================================*/
अटल पूर्णांक ray_dev_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	/* Dummy routine to satisfy device काष्ठाure */
	dev_dbg(&link->dev, "ray_dev_config(dev=%p,ifmap=%p)\n", dev, map);
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_dev_config - device not present\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*===========================================================================*/
अटल netdev_tx_t ray_dev_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	लघु length = skb->len;

	अगर (!pcmcia_dev_present(link)) अणु
		dev_dbg(&link->dev, "ray_dev_start_xmit - device not present\n");
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	dev_dbg(&link->dev, "ray_dev_start_xmit(skb=%p, dev=%p)\n", skb, dev);
	अगर (local->authentication_state == NEED_TO_AUTH) अणु
		dev_dbg(&link->dev, "ray_cs Sending authentication request.\n");
		अगर (!build_auth_frame(local, local->auth_id, OPEN_AUTH_REQUEST)) अणु
			local->authentication_state = AUTHENTICATED;
			netअगर_stop_queue(dev);
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण

	अगर (length < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		length = ETH_ZLEN;
	पूर्ण
	चयन (ray_hw_xmit(skb->data, length, dev, DATA_TYPE)) अणु
	हाल XMIT_NO_CCS:
	हाल XMIT_NEED_AUTH:
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	हाल XMIT_NO_INTR:
	हाल XMIT_MSG_BAD:
	हाल XMIT_OK:
	शेष:
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण /* ray_dev_start_xmit */

/*===========================================================================*/
अटल पूर्णांक ray_hw_xmit(अचिन्हित अक्षर *data, पूर्णांक len, काष्ठा net_device *dev,
		       UCHAR msg_type)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा ccs __iomem *pccs;
	पूर्णांक ccsindex;
	पूर्णांक offset;
	काष्ठा tx_msg __iomem *ptx;	/* Address of xmit buffer in PC space */
	लघु पूर्णांक addr;		/* Address of xmit buffer in card space */

	pr_debug("ray_hw_xmit(data=%p, len=%d, dev=%p)\n", data, len, dev);
	अगर (len + TX_HEADER_LENGTH > TX_BUF_SIZE) अणु
		prपूर्णांकk(KERN_INFO "ray_hw_xmit packet too large: %d bytes\n",
		       len);
		वापस XMIT_MSG_BAD;
	पूर्ण
	चयन (ccsindex = get_मुक्त_tx_ccs(local)) अणु
	हाल ECCSBUSY:
		pr_debug("ray_hw_xmit tx_ccs table busy\n");
		fallthrough;
	हाल ECCSFULL:
		pr_debug("ray_hw_xmit No free tx ccs\n");
		fallthrough;
	हाल ECARDGONE:
		netअगर_stop_queue(dev);
		वापस XMIT_NO_CCS;
	शेष:
		अवरोध;
	पूर्ण
	addr = TX_BUF_BASE + (ccsindex << 11);

	अगर (msg_type == DATA_TYPE) अणु
		local->stats.tx_bytes += len;
		local->stats.tx_packets++;
	पूर्ण

	ptx = local->sram + addr;

	ray_build_header(local, ptx, msg_type, data);
	अगर (translate) अणु
		offset = translate_frame(local, ptx, data, len);
	पूर्ण अन्यथा अणु /* Encapsulate frame */
		/* TBD TIB length will move address of ptx->var */
		स_नकल_toio(&ptx->var, data, len);
		offset = 0;
	पूर्ण

	/* fill in the CCS */
	pccs = ccs_base(local) + ccsindex;
	len += TX_HEADER_LENGTH + offset;
	ग_लिखोb(CCS_TX_REQUEST, &pccs->cmd);
	ग_लिखोb(addr >> 8, &pccs->var.tx_request.tx_data_ptr[0]);
	ग_लिखोb(local->tib_length, &pccs->var.tx_request.tx_data_ptr[1]);
	ग_लिखोb(len >> 8, &pccs->var.tx_request.tx_data_length[0]);
	ग_लिखोb(len & 0xff, &pccs->var.tx_request.tx_data_length[1]);
/* TBD still need psm_cam? */
	ग_लिखोb(PSM_CAM, &pccs->var.tx_request.घात_sav_mode);
	ग_लिखोb(local->net_शेष_tx_rate, &pccs->var.tx_request.tx_rate);
	ग_लिखोb(0, &pccs->var.tx_request.antenna);
	pr_debug("ray_hw_xmit default_tx_rate = 0x%x\n",
	      local->net_शेष_tx_rate);

	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		pr_debug("ray_hw_xmit failed - ECF not ready for intr\n");
/* TBD very inefficient to copy packet to buffer, and then not
   send it, but the alternative is to queue the messages and that
   won't be करोne क्रम a जबतक.  Maybe set tbusy until a CCS is मुक्त?
*/
		ग_लिखोb(CCS_BUFFER_FREE, &pccs->buffer_status);
		वापस XMIT_NO_INTR;
	पूर्ण
	वापस XMIT_OK;
पूर्ण /* end ray_hw_xmit */

/*===========================================================================*/
अटल पूर्णांक translate_frame(ray_dev_t *local, काष्ठा tx_msg __iomem *ptx,
			   अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	__be16 proto = ((काष्ठा ethhdr *)data)->h_proto;
	अगर (ntohs(proto) >= ETH_P_802_3_MIN) अणु /* DIX II ethernet frame */
		pr_debug("ray_cs translate_frame DIX II\n");
		/* Copy LLC header to card buffer */
		स_नकल_toio(&ptx->var, eth2_llc, माप(eth2_llc));
		स_नकल_toio(((व्योम __iomem *)&ptx->var) + माप(eth2_llc),
			    (UCHAR *) &proto, 2);
		अगर (proto == htons(ETH_P_AARP) || proto == htons(ETH_P_IPX)) अणु
			/* This is the selective translation table, only 2 entries */
			ग_लिखोb(0xf8,
			       &((काष्ठा snaphdr_t __iomem *)ptx->var)->org[2]);
		पूर्ण
		/* Copy body of ethernet packet without ethernet header */
		स_नकल_toio((व्योम __iomem *)&ptx->var +
			    माप(काष्ठा snaphdr_t), data + ETH_HLEN,
			    len - ETH_HLEN);
		वापस (पूर्णांक)माप(काष्ठा snaphdr_t) - ETH_HLEN;
	पूर्ण अन्यथा अणु /* alपढ़ोy  802 type, and proto is length */
		pr_debug("ray_cs translate_frame 802\n");
		अगर (proto == htons(0xffff)) अणु /* evil netware IPX 802.3 without LLC */
			pr_debug("ray_cs translate_frame evil IPX\n");
			स_नकल_toio(&ptx->var, data + ETH_HLEN, len - ETH_HLEN);
			वापस 0 - ETH_HLEN;
		पूर्ण
		स_नकल_toio(&ptx->var, data + ETH_HLEN, len - ETH_HLEN);
		वापस 0 - ETH_HLEN;
	पूर्ण
	/* TBD करो other frame types */
पूर्ण /* end translate_frame */

/*===========================================================================*/
अटल व्योम ray_build_header(ray_dev_t *local, काष्ठा tx_msg __iomem *ptx,
			     UCHAR msg_type, अचिन्हित अक्षर *data)
अणु
	ग_लिखोb(PROTOCOL_VER | msg_type, &ptx->mac.frame_ctl_1);
/*** IEEE 802.11 Address field assignments *************
		TODS	FROMDS	addr_1		addr_2		addr_3	addr_4
Adhoc		0	0	dest		src (terminal)	BSSID	N/A
AP to Terminal	0	1	dest		AP(BSSID)	source	N/A
Terminal to AP	1	0	AP(BSSID)	src (terminal)	dest	N/A
AP to AP	1	1	dest AP		src AP		dest	source
*******************************************************/
	अगर (local->net_type == ADHOC) अणु
		ग_लिखोb(0, &ptx->mac.frame_ctl_2);
		स_नकल_toio(ptx->mac.addr_1, ((काष्ठा ethhdr *)data)->h_dest,
			    2 * ADDRLEN);
		स_नकल_toio(ptx->mac.addr_3, local->bss_id, ADDRLEN);
	पूर्ण अन्यथा अणु /* infraकाष्ठाure */

		अगर (local->sparm.b4.a_acting_as_ap_status) अणु
			ग_लिखोb(FC2_FROM_DS, &ptx->mac.frame_ctl_2);
			स_नकल_toio(ptx->mac.addr_1,
				    ((काष्ठा ethhdr *)data)->h_dest, ADDRLEN);
			स_नकल_toio(ptx->mac.addr_2, local->bss_id, 6);
			स_नकल_toio(ptx->mac.addr_3,
				    ((काष्ठा ethhdr *)data)->h_source, ADDRLEN);
		पूर्ण अन्यथा अणु /* Terminal */

			ग_लिखोb(FC2_TO_DS, &ptx->mac.frame_ctl_2);
			स_नकल_toio(ptx->mac.addr_1, local->bss_id, ADDRLEN);
			स_नकल_toio(ptx->mac.addr_2,
				    ((काष्ठा ethhdr *)data)->h_source, ADDRLEN);
			स_नकल_toio(ptx->mac.addr_3,
				    ((काष्ठा ethhdr *)data)->h_dest, ADDRLEN);
		पूर्ण
	पूर्ण
पूर्ण /* end encapsulate_frame */

/*====================================================================*/

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get protocol name
 */
अटल पूर्णांक ray_get_name(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	म_नकल(wrqu->name, "IEEE 802.11-FH");
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set frequency
 */
अटल पूर्णांक ray_set_freq(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);
	पूर्णांक err = -EINPROGRESS;	/* Call commit handler */

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	/* Setting by channel number */
	अगर ((wrqu->freq.m > USA_HOP_MOD) || (wrqu->freq.e > 0))
		err = -EOPNOTSUPP;
	अन्यथा
		local->sparm.b5.a_hop_pattern = wrqu->freq.m;

	वापस err;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get frequency
 */
अटल पूर्णांक ray_get_freq(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	wrqu->freq.m = local->sparm.b5.a_hop_pattern;
	wrqu->freq.e = 0;
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set ESSID
 */
अटल पूर्णांक ray_set_essid(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	/* Check अगर we asked क्रम `any' */
	अगर (wrqu->essid.flags == 0)
		/* Corey : can you करो that ? */
		वापस -EOPNOTSUPP;

	/* Check the size of the string */
	अगर (wrqu->essid.length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;

	/* Set the ESSID in the card */
	स_रखो(local->sparm.b5.a_current_ess_id, 0, IW_ESSID_MAX_SIZE);
	स_नकल(local->sparm.b5.a_current_ess_id, extra, wrqu->essid.length);

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get ESSID
 */
अटल पूर्णांक ray_get_essid(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);
	UCHAR पंचांगp[IW_ESSID_MAX_SIZE + 1];

	/* Get the essid that was set */
	स_नकल(extra, local->sparm.b5.a_current_ess_id, IW_ESSID_MAX_SIZE);
	स_नकल(पंचांगp, local->sparm.b5.a_current_ess_id, IW_ESSID_MAX_SIZE);
	पंचांगp[IW_ESSID_MAX_SIZE] = '\0';

	/* Push it out ! */
	wrqu->essid.length = म_माप(पंचांगp);
	wrqu->essid.flags = 1;	/* active */

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get AP address
 */
अटल पूर्णांक ray_get_wap(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	स_नकल(wrqu->ap_addr.sa_data, local->bss_id, ETH_ALEN);
	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Bit-Rate
 */
अटल पूर्णांक ray_set_rate(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	/* Check अगर rate is in range */
	अगर ((wrqu->bitrate.value != 1000000) && (wrqu->bitrate.value != 2000000))
		वापस -EINVAL;

	/* Hack क्रम 1.5 Mb/s instead of 2 Mb/s */
	अगर ((local->fw_ver == 0x55) &&	/* Please check */
	    (wrqu->bitrate.value == 2000000))
		local->net_शेष_tx_rate = 3;
	अन्यथा
		local->net_शेष_tx_rate = wrqu->bitrate.value / 500000;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Bit-Rate
 */
अटल पूर्णांक ray_get_rate(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	अगर (local->net_शेष_tx_rate == 3)
		wrqu->bitrate.value = 2000000;	/* Hum... */
	अन्यथा
		wrqu->bitrate.value = local->net_शेष_tx_rate * 500000;
	wrqu->bitrate.fixed = 0;	/* We are in स्वतः mode */

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set RTS threshold
 */
अटल पूर्णांक ray_set_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);
	पूर्णांक rthr = wrqu->rts.value;

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	/* अगर(wrq->u.rts.fixed == 0) we should complain */
	अगर (wrqu->rts.disabled)
		rthr = 32767;
	अन्यथा अणु
		अगर ((rthr < 0) || (rthr > 2347))   /* What's the max packet size ??? */
			वापस -EINVAL;
	पूर्ण
	local->sparm.b5.a_rts_threshold[0] = (rthr >> 8) & 0xFF;
	local->sparm.b5.a_rts_threshold[1] = rthr & 0xFF;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get RTS threshold
 */
अटल पूर्णांक ray_get_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	wrqu->rts.value = (local->sparm.b5.a_rts_threshold[0] << 8)
	    + local->sparm.b5.a_rts_threshold[1];
	wrqu->rts.disabled = (wrqu->rts.value == 32767);
	wrqu->rts.fixed = 1;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Fragmentation threshold
 */
अटल पूर्णांक ray_set_frag(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);
	पूर्णांक fthr = wrqu->frag.value;

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	/* अगर(wrq->u.frag.fixed == 0) should complain */
	अगर (wrqu->frag.disabled)
		fthr = 32767;
	अन्यथा अणु
		अगर ((fthr < 256) || (fthr > 2347))	/* To check out ! */
			वापस -EINVAL;
	पूर्ण
	local->sparm.b5.a_frag_threshold[0] = (fthr >> 8) & 0xFF;
	local->sparm.b5.a_frag_threshold[1] = fthr & 0xFF;

	वापस -EINPROGRESS;	/* Call commit handler */
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Fragmentation threshold
 */
अटल पूर्णांक ray_get_frag(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	wrqu->frag.value = (local->sparm.b5.a_frag_threshold[0] << 8)
	    + local->sparm.b5.a_frag_threshold[1];
	wrqu->frag.disabled = (wrqu->frag.value == 32767);
	wrqu->frag.fixed = 1;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : set Mode of Operation
 */
अटल पूर्णांक ray_set_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);
	पूर्णांक err = -EINPROGRESS;	/* Call commit handler */
	अक्षर card_mode = 1;

	/* Reject अगर card is alपढ़ोy initialised */
	अगर (local->card_status != CARD_AWAITING_PARAM)
		वापस -EBUSY;

	चयन (wrqu->mode) अणु
	हाल IW_MODE_ADHOC:
		card_mode = 0;
		fallthrough;
	हाल IW_MODE_INFRA:
		local->sparm.b5.a_network_type = card_mode;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get Mode of Operation
 */
अटल पूर्णांक ray_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	ray_dev_t *local = netdev_priv(dev);

	अगर (local->sparm.b5.a_network_type)
		wrqu->mode = IW_MODE_INFRA;
	अन्यथा
		wrqu->mode = IW_MODE_ADHOC;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Handler : get range info
 */
अटल पूर्णांक ray_get_range(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;

	स_रखो(range, 0, माप(काष्ठा iw_range));

	/* Set the length (very important क्रम backward compatibility) */
	wrqu->data.length = माप(काष्ठा iw_range);

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 9;

	/* Set inक्रमmation in the range काष्ठा */
	range->throughput = 1.1 * 1000 * 1000;	/* Put the right number here */
	range->num_channels = hop_pattern_length[(पूर्णांक)country];
	range->num_frequency = 0;
	range->max_qual.qual = 0;
	range->max_qual.level = 255;	/* What's the correct value ? */
	range->max_qual.noise = 255;	/* Idem */
	range->num_bitrates = 2;
	range->bitrate[0] = 1000000;	/* 1 Mb/s */
	range->bitrate[1] = 2000000;	/* 2 Mb/s */
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Private Handler : set framing mode
 */
अटल पूर्णांक ray_set_framing(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	translate = !!*(extra);	/* Set framing mode */

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Private Handler : get framing mode
 */
अटल पूर्णांक ray_get_framing(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	*(extra) = translate;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Wireless Private Handler : get country
 */
अटल पूर्णांक ray_get_country(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	*(extra) = country;

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Commit handler : called after a bunch of SET operations
 */
अटल पूर्णांक ray_commit(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/
/*
 * Stats handler : वापस Wireless Stats
 */
अटल iw_stats *ray_get_wireless_stats(काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	काष्ठा status __iomem *p = local->sram + STATUS_BASE;

	local->wstats.status = local->card_status;
#अगर_घोषित WIRELESS_SPY
	अगर ((local->spy_data.spy_number > 0)
	    && (local->sparm.b5.a_network_type == 0)) अणु
		/* Get it from the first node in spy list */
		local->wstats.qual.qual = local->spy_data.spy_stat[0].qual;
		local->wstats.qual.level = local->spy_data.spy_stat[0].level;
		local->wstats.qual.noise = local->spy_data.spy_stat[0].noise;
		local->wstats.qual.updated =
		    local->spy_data.spy_stat[0].updated;
	पूर्ण
#पूर्ण_अगर /* WIRELESS_SPY */

	अगर (pcmcia_dev_present(link)) अणु
		local->wstats.qual.noise = पढ़ोb(&p->rxnoise);
		local->wstats.qual.updated |= 4;
	पूर्ण

	वापस &local->wstats;
पूर्ण /* end ray_get_wireless_stats */

/*------------------------------------------------------------------*/
/*
 * Structures to export the Wireless Handlers
 */

अटल स्थिर iw_handler ray_handler[] = अणु
	IW_HANDLER(SIOCSIWCOMMIT, ray_commit),
	IW_HANDLER(SIOCGIWNAME, ray_get_name),
	IW_HANDLER(SIOCSIWFREQ, ray_set_freq),
	IW_HANDLER(SIOCGIWFREQ, ray_get_freq),
	IW_HANDLER(SIOCSIWMODE, ray_set_mode),
	IW_HANDLER(SIOCGIWMODE, ray_get_mode),
	IW_HANDLER(SIOCGIWRANGE, ray_get_range),
#अगर_घोषित WIRELESS_SPY
	IW_HANDLER(SIOCSIWSPY, iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY, iw_handler_get_spy),
	IW_HANDLER(SIOCSIWTHRSPY, iw_handler_set_thrspy),
	IW_HANDLER(SIOCGIWTHRSPY, iw_handler_get_thrspy),
#पूर्ण_अगर /* WIRELESS_SPY */
	IW_HANDLER(SIOCGIWAP, ray_get_wap),
	IW_HANDLER(SIOCSIWESSID, ray_set_essid),
	IW_HANDLER(SIOCGIWESSID, ray_get_essid),
	IW_HANDLER(SIOCSIWRATE, ray_set_rate),
	IW_HANDLER(SIOCGIWRATE, ray_get_rate),
	IW_HANDLER(SIOCSIWRTS, ray_set_rts),
	IW_HANDLER(SIOCGIWRTS, ray_get_rts),
	IW_HANDLER(SIOCSIWFRAG, ray_set_frag),
	IW_HANDLER(SIOCGIWFRAG, ray_get_frag),
पूर्ण;

#घोषणा SIOCSIPFRAMING	SIOCIWFIRSTPRIV	/* Set framing mode */
#घोषणा SIOCGIPFRAMING	SIOCIWFIRSTPRIV + 1	/* Get framing mode */
#घोषणा SIOCGIPCOUNTRY	SIOCIWFIRSTPRIV + 3	/* Get country code */

अटल स्थिर iw_handler ray_निजी_handler[] = अणु
	[0] = ray_set_framing,
	[1] = ray_get_framing,
	[3] = ray_get_country,
पूर्ण;

अटल स्थिर काष्ठा iw_priv_args ray_निजी_args[] = अणु
/* cmd,		set_args,	get_args,	name */
	अणुSIOCSIPFRAMING, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0,
	 "set_framing"पूर्ण,
	अणुSIOCGIPFRAMING, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1,
	 "get_framing"पूर्ण,
	अणुSIOCGIPCOUNTRY, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1,
	 "get_country"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def ray_handler_def = अणु
	.num_standard = ARRAY_SIZE(ray_handler),
	.num_निजी = ARRAY_SIZE(ray_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(ray_निजी_args),
	.standard = ray_handler,
	.निजी = ray_निजी_handler,
	.निजी_args = ray_निजी_args,
	.get_wireless_stats = ray_get_wireless_stats,
पूर्ण;

/*===========================================================================*/
अटल पूर्णांक ray_खोलो(काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link;
	link = local->finder;

	dev_dbg(&link->dev, "ray_open('%s')\n", dev->name);

	अगर (link->खोलो == 0)
		local->num_multi = 0;
	link->खोलो++;

	/* If the card is not started, समय to start it ! - Jean II */
	अगर (local->card_status == CARD_AWAITING_PARAM) अणु
		पूर्णांक i;

		dev_dbg(&link->dev, "ray_open: doing init now !\n");

		/* Download startup parameters */
		अगर ((i = dl_startup_params(dev)) < 0) अणु
			prपूर्णांकk(KERN_INFO
			       "ray_dev_init dl_startup_params failed - "
			       "returns 0x%x\n", i);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (snअगरfer)
		netअगर_stop_queue(dev);
	अन्यथा
		netअगर_start_queue(dev);

	dev_dbg(&link->dev, "ray_open ending\n");
	वापस 0;
पूर्ण /* end ray_खोलो */

/*===========================================================================*/
अटल पूर्णांक ray_dev_बंद(काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link;
	link = local->finder;

	dev_dbg(&link->dev, "ray_dev_close('%s')\n", dev->name);

	link->खोलो--;
	netअगर_stop_queue(dev);

	/* In here, we should stop the hardware (stop card from beeing active)
	 * and set local->card_status to CARD_AWAITING_PARAM, so that जबतक the
	 * card is बंदd we can chage its configuration.
	 * Probably also need a COR reset to get sane state - Jean II */

	वापस 0;
पूर्ण /* end ray_dev_बंद */

/*===========================================================================*/
अटल व्योम ray_reset(काष्ठा net_device *dev)
अणु
	pr_debug("ray_reset entered\n");
पूर्ण

/*===========================================================================*/
/* Cause a firmware पूर्णांकerrupt अगर it is पढ़ोy क्रम one                         */
/* Return nonzero अगर not पढ़ोy                                               */
अटल पूर्णांक पूर्णांकerrupt_ecf(ray_dev_t *local, पूर्णांक ccs)
अणु
	पूर्णांक i = 50;
	काष्ठा pcmcia_device *link = local->finder;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs interrupt_ecf - device not present\n");
		वापस -1;
	पूर्ण
	dev_dbg(&link->dev, "interrupt_ecf(local=%p, ccs = 0x%x\n", local, ccs);

	जबतक (i &&
	       (पढ़ोb(local->amem + CIS_OFFSET + ECF_INTR_OFFSET) &
		ECF_INTR_SET))
		i--;
	अगर (i == 0) अणु
		dev_dbg(&link->dev, "ray_cs interrupt_ecf card not ready for interrupt\n");
		वापस -1;
	पूर्ण
	/* Fill the mailbox, then kick the card */
	ग_लिखोb(ccs, local->sram + SCB_BASE);
	ग_लिखोb(ECF_INTR_SET, local->amem + CIS_OFFSET + ECF_INTR_OFFSET);
	वापस 0;
पूर्ण /* पूर्णांकerrupt_ecf */

/*===========================================================================*/
/* Get next मुक्त transmit CCS                                                */
/* Return - index of current tx ccs                                          */
अटल पूर्णांक get_मुक्त_tx_ccs(ray_dev_t *local)
अणु
	पूर्णांक i;
	काष्ठा ccs __iomem *pccs = ccs_base(local);
	काष्ठा pcmcia_device *link = local->finder;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs get_free_tx_ccs - device not present\n");
		वापस ECARDGONE;
	पूर्ण

	अगर (test_and_set_bit(0, &local->tx_ccs_lock)) अणु
		dev_dbg(&link->dev, "ray_cs tx_ccs_lock busy\n");
		वापस ECCSBUSY;
	पूर्ण

	क्रम (i = 0; i < NUMBER_OF_TX_CCS; i++) अणु
		अगर (पढ़ोb(&(pccs + i)->buffer_status) == CCS_BUFFER_FREE) अणु
			ग_लिखोb(CCS_BUFFER_BUSY, &(pccs + i)->buffer_status);
			ग_लिखोb(CCS_END_LIST, &(pccs + i)->link);
			local->tx_ccs_lock = 0;
			वापस i;
		पूर्ण
	पूर्ण
	local->tx_ccs_lock = 0;
	dev_dbg(&link->dev, "ray_cs ERROR no free tx CCS for raylink card\n");
	वापस ECCSFULL;
पूर्ण /* get_मुक्त_tx_ccs */

/*===========================================================================*/
/* Get next मुक्त CCS                                                         */
/* Return - index of current ccs                                             */
अटल पूर्णांक get_मुक्त_ccs(ray_dev_t *local)
अणु
	पूर्णांक i;
	काष्ठा ccs __iomem *pccs = ccs_base(local);
	काष्ठा pcmcia_device *link = local->finder;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs get_free_ccs - device not present\n");
		वापस ECARDGONE;
	पूर्ण
	अगर (test_and_set_bit(0, &local->ccs_lock)) अणु
		dev_dbg(&link->dev, "ray_cs ccs_lock busy\n");
		वापस ECCSBUSY;
	पूर्ण

	क्रम (i = NUMBER_OF_TX_CCS; i < NUMBER_OF_CCS; i++) अणु
		अगर (पढ़ोb(&(pccs + i)->buffer_status) == CCS_BUFFER_FREE) अणु
			ग_लिखोb(CCS_BUFFER_BUSY, &(pccs + i)->buffer_status);
			ग_लिखोb(CCS_END_LIST, &(pccs + i)->link);
			local->ccs_lock = 0;
			वापस i;
		पूर्ण
	पूर्ण
	local->ccs_lock = 0;
	dev_dbg(&link->dev, "ray_cs ERROR no free CCS for raylink card\n");
	वापस ECCSFULL;
पूर्ण /* get_मुक्त_ccs */

/*===========================================================================*/
अटल व्योम authenticate_समयout(काष्ठा समयr_list *t)
अणु
	ray_dev_t *local = from_समयr(local, t, समयr);
	del_समयr(&local->समयr);
	prपूर्णांकk(KERN_INFO "ray_cs Authentication with access point failed"
	       " - timeout\n");
	join_net(&local->समयr);
पूर्ण

/*===========================================================================*/
अटल पूर्णांक parse_addr(अक्षर *in_str, UCHAR *out)
अणु
	पूर्णांक len;
	पूर्णांक i, j, k;
	पूर्णांक status;

	अगर (in_str == शून्य)
		वापस 0;
	अगर ((len = म_माप(in_str)) < 2)
		वापस 0;
	स_रखो(out, 0, ADDRLEN);

	status = 1;
	j = len - 1;
	अगर (j > 12)
		j = 12;
	i = 5;

	जबतक (j > 0) अणु
		अगर ((k = hex_to_bin(in_str[j--])) != -1)
			out[i] = k;
		अन्यथा
			वापस 0;

		अगर (j == 0)
			अवरोध;
		अगर ((k = hex_to_bin(in_str[j--])) != -1)
			out[i] += k << 4;
		अन्यथा
			वापस 0;
		अगर (!i--)
			अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/*===========================================================================*/
अटल काष्ठा net_device_stats *ray_get_stats(काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	काष्ठा status __iomem *p = local->sram + STATUS_BASE;
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs net_device_stats - device not present\n");
		वापस &local->stats;
	पूर्ण
	अगर (पढ़ोb(&p->mrx_overflow_क्रम_host)) अणु
		local->stats.rx_over_errors += swab16(पढ़ोw(&p->mrx_overflow));
		ग_लिखोb(0, &p->mrx_overflow);
		ग_लिखोb(0, &p->mrx_overflow_क्रम_host);
	पूर्ण
	अगर (पढ़ोb(&p->mrx_checksum_error_क्रम_host)) अणु
		local->stats.rx_crc_errors +=
		    swab16(पढ़ोw(&p->mrx_checksum_error));
		ग_लिखोb(0, &p->mrx_checksum_error);
		ग_लिखोb(0, &p->mrx_checksum_error_क्रम_host);
	पूर्ण
	अगर (पढ़ोb(&p->rx_hec_error_क्रम_host)) अणु
		local->stats.rx_frame_errors += swab16(पढ़ोw(&p->rx_hec_error));
		ग_लिखोb(0, &p->rx_hec_error);
		ग_लिखोb(0, &p->rx_hec_error_क्रम_host);
	पूर्ण
	वापस &local->stats;
पूर्ण

/*===========================================================================*/
अटल व्योम ray_update_parm(काष्ठा net_device *dev, UCHAR objid, UCHAR *value,
			    पूर्णांक len)
अणु
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	पूर्णांक ccsindex;
	पूर्णांक i;
	काष्ठा ccs __iomem *pccs;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_update_parm - device not present\n");
		वापस;
	पूर्ण

	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0) अणु
		dev_dbg(&link->dev, "ray_update_parm - No free ccs\n");
		वापस;
	पूर्ण
	pccs = ccs_base(local) + ccsindex;
	ग_लिखोb(CCS_UPDATE_PARAMS, &pccs->cmd);
	ग_लिखोb(objid, &pccs->var.update_param.object_id);
	ग_लिखोb(1, &pccs->var.update_param.number_objects);
	ग_लिखोb(0, &pccs->var.update_param.failure_cause);
	क्रम (i = 0; i < len; i++) अणु
		ग_लिखोb(value[i], local->sram + HOST_TO_ECF_BASE);
	पूर्ण
	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		dev_dbg(&link->dev, "ray_cs associate failed - ECF not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
	पूर्ण
पूर्ण

/*===========================================================================*/
अटल व्योम ray_update_multi_list(काष्ठा net_device *dev, पूर्णांक all)
अणु
	पूर्णांक ccsindex;
	काष्ठा ccs __iomem *pccs;
	ray_dev_t *local = netdev_priv(dev);
	काष्ठा pcmcia_device *link = local->finder;
	व्योम __iomem *p = local->sram + HOST_TO_ECF_BASE;

	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_update_multi_list - device not present\n");
		वापस;
	पूर्ण अन्यथा
		dev_dbg(&link->dev, "ray_update_multi_list(%p)\n", dev);
	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0) अणु
		dev_dbg(&link->dev, "ray_update_multi - No free ccs\n");
		वापस;
	पूर्ण
	pccs = ccs_base(local) + ccsindex;
	ग_लिखोb(CCS_UPDATE_MULTICAST_LIST, &pccs->cmd);

	अगर (all) अणु
		ग_लिखोb(0xff, &pccs->var);
		local->num_multi = 0xff;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i = 0;

		/* Copy the kernel's list of MC addresses to card */
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			स_नकल_toio(p, ha->addr, ETH_ALEN);
			dev_dbg(&link->dev, "ray_update_multi add addr %pm\n",
				ha->addr);
			p += ETH_ALEN;
			i++;
		पूर्ण
		अगर (i > 256 / ADDRLEN)
			i = 256 / ADDRLEN;
		ग_लिखोb((UCHAR) i, &pccs->var);
		dev_dbg(&link->dev, "ray_cs update_multi %d addresses in list\n", i);
		/* Interrupt the firmware to process the command */
		local->num_multi = i;
	पूर्ण
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		dev_dbg(&link->dev,
		      "ray_cs update_multi failed - ECF not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
	पूर्ण
पूर्ण /* end ray_update_multi_list */

/*===========================================================================*/
अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	ray_dev_t *local = netdev_priv(dev);
	UCHAR promisc;

	pr_debug("ray_cs set_multicast_list(%p)\n", dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		अगर (local->sparm.b5.a_promiscuous_mode == 0) अणु
			pr_debug("ray_cs set_multicast_list promisc on\n");
			local->sparm.b5.a_promiscuous_mode = 1;
			promisc = 1;
			ray_update_parm(dev, OBJID_promiscuous_mode,
					&promisc, माप(promisc));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (local->sparm.b5.a_promiscuous_mode == 1) अणु
			pr_debug("ray_cs set_multicast_list promisc off\n");
			local->sparm.b5.a_promiscuous_mode = 0;
			promisc = 0;
			ray_update_parm(dev, OBJID_promiscuous_mode,
					&promisc, माप(promisc));
		पूर्ण
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI)
		ray_update_multi_list(dev, 1);
	अन्यथा अणु
		अगर (local->num_multi != netdev_mc_count(dev))
			ray_update_multi_list(dev, 0);
	पूर्ण
पूर्ण /* end set_multicast_list */

/*=============================================================================
 * All routines below here are run at पूर्णांकerrupt समय.
=============================================================================*/
अटल irqवापस_t ray_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा pcmcia_device *link;
	ray_dev_t *local;
	काष्ठा ccs __iomem *pccs;
	काष्ठा rcs __iomem *prcs;
	UCHAR rcsindex;
	UCHAR पंचांगp;
	UCHAR cmd;
	UCHAR status;
	UCHAR memपंचांगp[ESSID_SIZE + 1];


	अगर (dev == शून्य)	/* Note that we want पूर्णांकerrupts with dev->start == 0 */
		वापस IRQ_NONE;

	pr_debug("ray_cs: interrupt for *dev=%p\n", dev);

	local = netdev_priv(dev);
	link = local->finder;
	अगर (!pcmcia_dev_present(link)) अणु
		pr_debug(
			"ray_cs interrupt from device not present or suspended.\n");
		वापस IRQ_NONE;
	पूर्ण
	rcsindex = पढ़ोb(&((काष्ठा scb __iomem *)(local->sram))->rcs_index);

	अगर (rcsindex >= (NUMBER_OF_CCS + NUMBER_OF_RCS)) अणु
		dev_dbg(&link->dev, "ray_cs interrupt bad rcsindex = 0x%x\n", rcsindex);
		clear_पूर्णांकerrupt(local);
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (rcsindex < NUMBER_OF_CCS) अणु /* If it's a वापसed CCS */
		pccs = ccs_base(local) + rcsindex;
		cmd = पढ़ोb(&pccs->cmd);
		status = पढ़ोb(&pccs->buffer_status);
		चयन (cmd) अणु
		हाल CCS_DOWNLOAD_STARTUP_PARAMS:	/* Happens in firmware someday */
			del_समयr(&local->समयr);
			अगर (status == CCS_COMMAND_COMPLETE) अणु
				dev_dbg(&link->dev,
				      "ray_cs interrupt download_startup_parameters OK\n");
			पूर्ण अन्यथा अणु
				dev_dbg(&link->dev,
				      "ray_cs interrupt download_startup_parameters fail\n");
			पूर्ण
			अवरोध;
		हाल CCS_UPDATE_PARAMS:
			dev_dbg(&link->dev, "ray_cs interrupt update params done\n");
			अगर (status != CCS_COMMAND_COMPLETE) अणु
				पंचांगp =
				    पढ़ोb(&pccs->var.update_param.
					  failure_cause);
				dev_dbg(&link->dev,
				      "ray_cs interrupt update params failed - reason %d\n",
				      पंचांगp);
			पूर्ण
			अवरोध;
		हाल CCS_REPORT_PARAMS:
			dev_dbg(&link->dev, "ray_cs interrupt report params done\n");
			अवरोध;
		हाल CCS_UPDATE_MULTICAST_LIST:	/* Note that this CCS isn't वापसed */
			dev_dbg(&link->dev,
			      "ray_cs interrupt CCS Update Multicast List done\n");
			अवरोध;
		हाल CCS_UPDATE_POWER_SAVINGS_MODE:
			dev_dbg(&link->dev,
			      "ray_cs interrupt update power save mode done\n");
			अवरोध;
		हाल CCS_START_NETWORK:
		हाल CCS_JOIN_NETWORK:
			स_नकल(memपंचांगp, local->sparm.b4.a_current_ess_id,
								ESSID_SIZE);
			memपंचांगp[ESSID_SIZE] = '\0';

			अगर (status == CCS_COMMAND_COMPLETE) अणु
				अगर (पढ़ोb
				    (&pccs->var.start_network.net_initiated) ==
				    1) अणु
					dev_dbg(&link->dev,
					      "ray_cs interrupt network \"%s\" started\n",
					      memपंचांगp);
				पूर्ण अन्यथा अणु
					dev_dbg(&link->dev,
					      "ray_cs interrupt network \"%s\" joined\n",
					      memपंचांगp);
				पूर्ण
				स_नकल_fromio(&local->bss_id,
					      pccs->var.start_network.bssid,
					      ADDRLEN);

				अगर (local->fw_ver == 0x55)
					local->net_शेष_tx_rate = 3;
				अन्यथा
					local->net_शेष_tx_rate =
					    पढ़ोb(&pccs->var.start_network.
						  net_शेष_tx_rate);
				local->encryption =
				    पढ़ोb(&pccs->var.start_network.encryption);
				अगर (!snअगरfer && (local->net_type == INFRA)
				    && !(local->sparm.b4.a_acting_as_ap_status)) अणु
					authenticate(local);
				पूर्ण
				local->card_status = CARD_ACQ_COMPLETE;
			पूर्ण अन्यथा अणु
				local->card_status = CARD_ACQ_FAILED;

				del_समयr(&local->समयr);
				local->समयr.expires = jअगरfies + HZ * 5;
				अगर (status == CCS_START_NETWORK) अणु
					dev_dbg(&link->dev,
					      "ray_cs interrupt network \"%s\" start failed\n",
					      memपंचांगp);
					local->समयr.function = start_net;
				पूर्ण अन्यथा अणु
					dev_dbg(&link->dev,
					      "ray_cs interrupt network \"%s\" join failed\n",
					      memपंचांगp);
					local->समयr.function = join_net;
				पूर्ण
				add_समयr(&local->समयr);
			पूर्ण
			अवरोध;
		हाल CCS_START_ASSOCIATION:
			अगर (status == CCS_COMMAND_COMPLETE) अणु
				local->card_status = CARD_ASSOC_COMPLETE;
				dev_dbg(&link->dev, "ray_cs association successful\n");
			पूर्ण अन्यथा अणु
				dev_dbg(&link->dev, "ray_cs association failed,\n");
				local->card_status = CARD_ASSOC_FAILED;
				join_net(&local->समयr);
			पूर्ण
			अवरोध;
		हाल CCS_TX_REQUEST:
			अगर (status == CCS_COMMAND_COMPLETE) अणु
				dev_dbg(&link->dev,
				      "ray_cs interrupt tx request complete\n");
			पूर्ण अन्यथा अणु
				dev_dbg(&link->dev,
				      "ray_cs interrupt tx request failed\n");
			पूर्ण
			अगर (!snअगरfer)
				netअगर_start_queue(dev);
			netअगर_wake_queue(dev);
			अवरोध;
		हाल CCS_TEST_MEMORY:
			dev_dbg(&link->dev, "ray_cs interrupt mem test done\n");
			अवरोध;
		हाल CCS_SHUTDOWN:
			dev_dbg(&link->dev,
			      "ray_cs interrupt Unexpected CCS returned - Shutdown\n");
			अवरोध;
		हाल CCS_DUMP_MEMORY:
			dev_dbg(&link->dev, "ray_cs interrupt dump memory done\n");
			अवरोध;
		हाल CCS_START_TIMER:
			dev_dbg(&link->dev,
			      "ray_cs interrupt DING - raylink timer expired\n");
			अवरोध;
		शेष:
			dev_dbg(&link->dev,
			      "ray_cs interrupt Unexpected CCS 0x%x returned 0x%x\n",
			      rcsindex, cmd);
		पूर्ण
		ग_लिखोb(CCS_BUFFER_FREE, &pccs->buffer_status);
	पूर्ण अन्यथा अणु /* It's an RCS */

		prcs = rcs_base(local) + rcsindex;

		चयन (पढ़ोb(&prcs->पूर्णांकerrupt_id)) अणु
		हाल PROCESS_RX_PACKET:
			ray_rx(dev, local, prcs);
			अवरोध;
		हाल REJOIN_NET_COMPLETE:
			dev_dbg(&link->dev, "ray_cs interrupt rejoin net complete\n");
			local->card_status = CARD_ACQ_COMPLETE;
			/* करो we need to clear tx buffers CCS's? */
			अगर (local->sparm.b4.a_network_type == ADHOC) अणु
				अगर (!snअगरfer)
					netअगर_start_queue(dev);
			पूर्ण अन्यथा अणु
				स_नकल_fromio(&local->bss_id,
					      prcs->var.rejoin_net_complete.
					      bssid, ADDRLEN);
				dev_dbg(&link->dev, "ray_cs new BSSID = %pm\n",
					local->bss_id);
				अगर (!snअगरfer)
					authenticate(local);
			पूर्ण
			अवरोध;
		हाल ROAMING_INITIATED:
			dev_dbg(&link->dev, "ray_cs interrupt roaming initiated\n");
			netअगर_stop_queue(dev);
			local->card_status = CARD_DOING_ACQ;
			अवरोध;
		हाल JAPAN_CALL_SIGN_RXD:
			dev_dbg(&link->dev, "ray_cs interrupt japan call sign rx\n");
			अवरोध;
		शेष:
			dev_dbg(&link->dev,
			      "ray_cs Unexpected interrupt for RCS 0x%x cmd = 0x%x\n",
			      rcsindex,
			      (अचिन्हित पूर्णांक)पढ़ोb(&prcs->पूर्णांकerrupt_id));
			अवरोध;
		पूर्ण
		ग_लिखोb(CCS_BUFFER_FREE, &prcs->buffer_status);
	पूर्ण
	clear_पूर्णांकerrupt(local);
	वापस IRQ_HANDLED;
पूर्ण /* ray_पूर्णांकerrupt */

/*===========================================================================*/
अटल व्योम ray_rx(काष्ठा net_device *dev, ray_dev_t *local,
		   काष्ठा rcs __iomem *prcs)
अणु
	पूर्णांक rx_len;
	अचिन्हित पूर्णांक pkt_addr;
	व्योम __iomem *pmsg;
	pr_debug("ray_rx process rx packet\n");

	/* Calculate address of packet within Rx buffer */
	pkt_addr = ((पढ़ोb(&prcs->var.rx_packet.rx_data_ptr[0]) << 8)
		    + पढ़ोb(&prcs->var.rx_packet.rx_data_ptr[1])) & RX_BUFF_END;
	/* Length of first packet fragment */
	rx_len = (पढ़ोb(&prcs->var.rx_packet.rx_data_length[0]) << 8)
	    + पढ़ोb(&prcs->var.rx_packet.rx_data_length[1]);

	local->last_rsl = पढ़ोb(&prcs->var.rx_packet.rx_sig_lev);
	pmsg = local->rmem + pkt_addr;
	चयन (पढ़ोb(pmsg)) अणु
	हाल DATA_TYPE:
		pr_debug("ray_rx data type\n");
		rx_data(dev, prcs, pkt_addr, rx_len);
		अवरोध;
	हाल AUTHENTIC_TYPE:
		pr_debug("ray_rx authentic type\n");
		अगर (snअगरfer)
			rx_data(dev, prcs, pkt_addr, rx_len);
		अन्यथा
			rx_authenticate(local, prcs, pkt_addr, rx_len);
		अवरोध;
	हाल DEAUTHENTIC_TYPE:
		pr_debug("ray_rx deauth type\n");
		अगर (snअगरfer)
			rx_data(dev, prcs, pkt_addr, rx_len);
		अन्यथा
			rx_deauthenticate(local, prcs, pkt_addr, rx_len);
		अवरोध;
	हाल शून्य_MSG_TYPE:
		pr_debug("ray_cs rx NULL msg\n");
		अवरोध;
	हाल BEACON_TYPE:
		pr_debug("ray_rx beacon type\n");
		अगर (snअगरfer)
			rx_data(dev, prcs, pkt_addr, rx_len);

		copy_from_rx_buff(local, (UCHAR *) &local->last_bcn, pkt_addr,
				  rx_len < माप(काष्ठा beacon_rx) ?
				  rx_len : माप(काष्ठा beacon_rx));

		local->beacon_rxed = 1;
		/* Get the statistics so the card counters never overflow */
		ray_get_stats(dev);
		अवरोध;
	शेष:
		pr_debug("ray_cs unknown pkt type %2x\n",
		      (अचिन्हित पूर्णांक)पढ़ोb(pmsg));
		अवरोध;
	पूर्ण

पूर्ण /* end ray_rx */

/*===========================================================================*/
अटल व्योम rx_data(काष्ठा net_device *dev, काष्ठा rcs __iomem *prcs,
		    अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rcs __iomem *prcslink = prcs;
	ray_dev_t *local = netdev_priv(dev);
	UCHAR *rx_ptr;
	पूर्णांक total_len;
	पूर्णांक पंचांगp;
#अगर_घोषित WIRELESS_SPY
	पूर्णांक siglev = local->last_rsl;
	u_अक्षर linksrcaddr[ETH_ALEN];	/* Other end of the wireless link */
#पूर्ण_अगर

	अगर (!snअगरfer) अणु
		अगर (translate) अणु
/* TBD length needs fixing क्रम translated header */
			अगर (rx_len < (ETH_HLEN + RX_MAC_HEADER_LENGTH) ||
			    rx_len >
			    (dev->mtu + RX_MAC_HEADER_LENGTH + ETH_HLEN +
			     FCS_LEN)) अणु
				pr_debug(
				      "ray_cs invalid packet length %d received\n",
				      rx_len);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु /* encapsulated ethernet */

			अगर (rx_len < (ETH_HLEN + RX_MAC_HEADER_LENGTH) ||
			    rx_len >
			    (dev->mtu + RX_MAC_HEADER_LENGTH + ETH_HLEN +
			     FCS_LEN)) अणु
				pr_debug(
				      "ray_cs invalid packet length %d received\n",
				      rx_len);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	pr_debug("ray_cs rx_data packet\n");
	/* If fragmented packet, verअगरy sizes of fragments add up */
	अगर (पढ़ोb(&prcs->var.rx_packet.next_frag_rcs_index) != 0xFF) अणु
		pr_debug("ray_cs rx'ed fragment\n");
		पंचांगp = (पढ़ोb(&prcs->var.rx_packet.totalpacketlength[0]) << 8)
		    + पढ़ोb(&prcs->var.rx_packet.totalpacketlength[1]);
		total_len = पंचांगp;
		prcslink = prcs;
		करो अणु
			पंचांगp -=
			    (पढ़ोb(&prcslink->var.rx_packet.rx_data_length[0])
			     << 8)
			    + पढ़ोb(&prcslink->var.rx_packet.rx_data_length[1]);
			अगर (पढ़ोb(&prcslink->var.rx_packet.next_frag_rcs_index)
			    == 0xFF || पंचांगp < 0)
				अवरोध;
			prcslink = rcs_base(local)
			    + पढ़ोb(&prcslink->link_field);
		पूर्ण जबतक (1);

		अगर (पंचांगp < 0) अणु
			pr_debug(
			      "ray_cs rx_data fragment lengths don't add up\n");
			local->stats.rx_dropped++;
			release_frag_chain(local, prcs);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु /* Single unfragmented packet */
		total_len = rx_len;
	पूर्ण

	skb = dev_alloc_skb(total_len + 5);
	अगर (skb == शून्य) अणु
		pr_debug("ray_cs rx_data could not allocate skb\n");
		local->stats.rx_dropped++;
		अगर (पढ़ोb(&prcs->var.rx_packet.next_frag_rcs_index) != 0xFF)
			release_frag_chain(local, prcs);
		वापस;
	पूर्ण
	skb_reserve(skb, 2);	/* Align IP on 16 byte (TBD check this) */

	pr_debug("ray_cs rx_data total_len = %x, rx_len = %x\n", total_len,
	      rx_len);

/************************/
	/* Reserve enough room क्रम the whole damn packet. */
	rx_ptr = skb_put(skb, total_len);
	/* Copy the whole packet to sk_buff */
	rx_ptr +=
	    copy_from_rx_buff(local, rx_ptr, pkt_addr & RX_BUFF_END, rx_len);
	/* Get source address */
#अगर_घोषित WIRELESS_SPY
	skb_copy_from_linear_data_offset(skb,
					 दुरत्व(काष्ठा mac_header, addr_2),
					 linksrcaddr, ETH_ALEN);
#पूर्ण_अगर
	/* Now, deal with encapsulation/translation/snअगरfer */
	अगर (!snअगरfer) अणु
		अगर (!translate) अणु
			/* Encapsulated ethernet, so just lop off 802.11 MAC header */
/* TBD reserve            skb_reserve( skb, RX_MAC_HEADER_LENGTH); */
			skb_pull(skb, RX_MAC_HEADER_LENGTH);
		पूर्ण अन्यथा अणु
			/* Do translation */
			untranslate(local, skb, total_len);
		पूर्ण
	पूर्ण अन्यथा अणु /* snअगरfer mode, so just pass whole packet */
	पूर्ण

/************************/
	/* Now pick up the rest of the fragments अगर any */
	पंचांगp = 17;
	अगर (पढ़ोb(&prcs->var.rx_packet.next_frag_rcs_index) != 0xFF) अणु
		prcslink = prcs;
		pr_debug("ray_cs rx_data in fragment loop\n");
		करो अणु
			prcslink = rcs_base(local)
			    +
			    पढ़ोb(&prcslink->var.rx_packet.next_frag_rcs_index);
			rx_len =
			    ((पढ़ोb(&prcslink->var.rx_packet.rx_data_length[0])
			      << 8)
			     +
			     पढ़ोb(&prcslink->var.rx_packet.rx_data_length[1]))
			    & RX_BUFF_END;
			pkt_addr =
			    ((पढ़ोb(&prcslink->var.rx_packet.rx_data_ptr[0]) <<
			      8)
			     + पढ़ोb(&prcslink->var.rx_packet.rx_data_ptr[1]))
			    & RX_BUFF_END;

			rx_ptr +=
			    copy_from_rx_buff(local, rx_ptr, pkt_addr, rx_len);

		पूर्ण जबतक (पंचांगp-- &&
			 पढ़ोb(&prcslink->var.rx_packet.next_frag_rcs_index) !=
			 0xFF);
		release_frag_chain(local, prcs);
	पूर्ण

	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx(skb);
	local->stats.rx_packets++;
	local->stats.rx_bytes += total_len;

	/* Gather संकेत strength per address */
#अगर_घोषित WIRELESS_SPY
	/* For the Access Poपूर्णांक or the node having started the ad-hoc net
	 * note : ad-hoc work only in some specअगरic configurations, but we
	 * kludge in ray_get_wireless_stats... */
	अगर (!स_भेद(linksrcaddr, local->bss_id, ETH_ALEN)) अणु
		/* Update statistics */
		/*local->wstats.qual.qual = none ? */
		local->wstats.qual.level = siglev;
		/*local->wstats.qual.noise = none ? */
		local->wstats.qual.updated = 0x2;
	पूर्ण
	/* Now, update the spy stuff */
	अणु
		काष्ठा iw_quality wstats;
		wstats.level = siglev;
		/* wstats.noise = none ? */
		/* wstats.qual = none ? */
		wstats.updated = 0x2;
		/* Update spy records */
		wireless_spy_update(dev, linksrcaddr, &wstats);
	पूर्ण
#पूर्ण_अगर /* WIRELESS_SPY */
पूर्ण /* end rx_data */

/*===========================================================================*/
अटल व्योम untranslate(ray_dev_t *local, काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	snaphdr_t *psnap = (snaphdr_t *) (skb->data + RX_MAC_HEADER_LENGTH);
	काष्ठा ieee80211_hdr *pmac = (काष्ठा ieee80211_hdr *)skb->data;
	__be16 type = *(__be16 *) psnap->ethertype;
	पूर्णांक delta;
	काष्ठा ethhdr *peth;
	UCHAR srcaddr[ADDRLEN];
	UCHAR destaddr[ADDRLEN];
	अटल स्थिर UCHAR org_bridge[3] = अणु 0, 0, 0xf8 पूर्ण;
	अटल स्थिर UCHAR org_1042[3] = अणु 0, 0, 0 पूर्ण;

	स_नकल(destaddr, ieee80211_get_DA(pmac), ADDRLEN);
	स_नकल(srcaddr, ieee80211_get_SA(pmac), ADDRLEN);

#अगर 0
	अगर अणु
		prपूर्णांक_hex_dump(KERN_DEBUG, "skb->data before untranslate: ",
			       DUMP_PREFIX_NONE, 16, 1,
			       skb->data, 64, true);
		prपूर्णांकk(KERN_DEBUG
		       "type = %08x, xsap = %02x%02x%02x, org = %02x02x02x\n",
		       ntohs(type), psnap->dsap, psnap->ssap, psnap->ctrl,
		       psnap->org[0], psnap->org[1], psnap->org[2]);
		prपूर्णांकk(KERN_DEBUG "untranslate skb->data = %p\n", skb->data);
	पूर्ण
#पूर्ण_अगर

	अगर (psnap->dsap != 0xaa || psnap->ssap != 0xaa || psnap->ctrl != 3) अणु
		/* not a snap type so leave it alone */
		pr_debug("ray_cs untranslate NOT SNAP %02x %02x %02x\n",
		      psnap->dsap, psnap->ssap, psnap->ctrl);

		delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
		peth = (काष्ठा ethhdr *)(skb->data + delta);
		peth->h_proto = htons(len - RX_MAC_HEADER_LENGTH);
	पूर्ण अन्यथा अणु /* Its a SNAP */
		अगर (स_भेद(psnap->org, org_bridge, 3) == 0) अणु
		/* EtherII and nuke the LLC */
			pr_debug("ray_cs untranslate Bridge encap\n");
			delta = RX_MAC_HEADER_LENGTH
			    + माप(काष्ठा snaphdr_t) - ETH_HLEN;
			peth = (काष्ठा ethhdr *)(skb->data + delta);
			peth->h_proto = type;
		पूर्ण अन्यथा अगर (स_भेद(psnap->org, org_1042, 3) == 0) अणु
			चयन (ntohs(type)) अणु
			हाल ETH_P_IPX:
			हाल ETH_P_AARP:
				pr_debug("ray_cs untranslate RFC IPX/AARP\n");
				delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
				peth = (काष्ठा ethhdr *)(skb->data + delta);
				peth->h_proto =
				    htons(len - RX_MAC_HEADER_LENGTH);
				अवरोध;
			शेष:
				pr_debug("ray_cs untranslate RFC default\n");
				delta = RX_MAC_HEADER_LENGTH +
				    माप(काष्ठा snaphdr_t) - ETH_HLEN;
				peth = (काष्ठा ethhdr *)(skb->data + delta);
				peth->h_proto = type;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk("ray_cs untranslate very confused by packet\n");
			delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
			peth = (काष्ठा ethhdr *)(skb->data + delta);
			peth->h_proto = type;
		पूर्ण
	पूर्ण
/* TBD reserve  skb_reserve(skb, delta); */
	skb_pull(skb, delta);
	pr_debug("untranslate after skb_pull(%d), skb->data = %p\n", delta,
	      skb->data);
	स_नकल(peth->h_dest, destaddr, ADDRLEN);
	स_नकल(peth->h_source, srcaddr, ADDRLEN);
#अगर 0
	अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "skb->data after untranslate:");
		क्रम (i = 0; i < 64; i++)
			prपूर्णांकk("%02x ", skb->data[i]);
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण /* end untranslate */

/*===========================================================================*/
/* Copy data from circular receive buffer to PC memory.
 * dest     = destination address in PC memory
 * pkt_addr = source address in receive buffer
 * len      = length of packet to copy
 */
अटल पूर्णांक copy_from_rx_buff(ray_dev_t *local, UCHAR *dest, पूर्णांक pkt_addr,
			     पूर्णांक length)
अणु
	पूर्णांक wrap_bytes = (pkt_addr + length) - (RX_BUFF_END + 1);
	अगर (wrap_bytes <= 0) अणु
		स_नकल_fromio(dest, local->rmem + pkt_addr, length);
	पूर्ण अन्यथा अणु /* Packet wrapped in circular buffer */

		स_नकल_fromio(dest, local->rmem + pkt_addr,
			      length - wrap_bytes);
		स_नकल_fromio(dest + length - wrap_bytes, local->rmem,
			      wrap_bytes);
	पूर्ण
	वापस length;
पूर्ण

/*===========================================================================*/
अटल व्योम release_frag_chain(ray_dev_t *local, काष्ठा rcs __iomem *prcs)
अणु
	काष्ठा rcs __iomem *prcslink = prcs;
	पूर्णांक पंचांगp = 17;
	अचिन्हित rcsindex = पढ़ोb(&prcs->var.rx_packet.next_frag_rcs_index);

	जबतक (पंचांगp--) अणु
		ग_लिखोb(CCS_BUFFER_FREE, &prcslink->buffer_status);
		अगर (rcsindex >= (NUMBER_OF_CCS + NUMBER_OF_RCS)) अणु
			pr_debug("ray_cs interrupt bad rcsindex = 0x%x\n",
			      rcsindex);
			अवरोध;
		पूर्ण
		prcslink = rcs_base(local) + rcsindex;
		rcsindex = पढ़ोb(&prcslink->var.rx_packet.next_frag_rcs_index);
	पूर्ण
	ग_लिखोb(CCS_BUFFER_FREE, &prcslink->buffer_status);
पूर्ण

/*===========================================================================*/
अटल व्योम authenticate(ray_dev_t *local)
अणु
	काष्ठा pcmcia_device *link = local->finder;
	dev_dbg(&link->dev, "ray_cs Starting authentication.\n");
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs authenticate - device not present\n");
		वापस;
	पूर्ण

	del_समयr(&local->समयr);
	अगर (build_auth_frame(local, local->bss_id, OPEN_AUTH_REQUEST)) अणु
		local->समयr.function = join_net;
	पूर्ण अन्यथा अणु
		local->समयr.function = authenticate_समयout;
	पूर्ण
	local->समयr.expires = jअगरfies + HZ * 2;
	add_समयr(&local->समयr);
	local->authentication_state = AWAITING_RESPONSE;
पूर्ण /* end authenticate */

/*===========================================================================*/
अटल व्योम rx_authenticate(ray_dev_t *local, काष्ठा rcs __iomem *prcs,
			    अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len)
अणु
	UCHAR buff[256];
	काष्ठा ray_rx_msg *msg = (काष्ठा ray_rx_msg *) buff;

	del_समयr(&local->समयr);

	copy_from_rx_buff(local, buff, pkt_addr, rx_len & 0xff);
	/* अगर we are trying to get authenticated */
	अगर (local->sparm.b4.a_network_type == ADHOC) अणु
		pr_debug("ray_cs rx_auth var= %02x %02x %02x %02x %02x %02x\n",
		      msg->var[0], msg->var[1], msg->var[2], msg->var[3],
		      msg->var[4], msg->var[5]);
		अगर (msg->var[2] == 1) अणु
			pr_debug("ray_cs Sending authentication response.\n");
			अगर (!build_auth_frame
			    (local, msg->mac.addr_2, OPEN_AUTH_RESPONSE)) अणु
				local->authentication_state = NEED_TO_AUTH;
				स_नकल(local->auth_id, msg->mac.addr_2,
				       ADDRLEN);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* Infraकाष्ठाure network */

		अगर (local->authentication_state == AWAITING_RESPONSE) अणु
			/* Verअगरy authentication sequence #2 and success */
			अगर (msg->var[2] == 2) अणु
				अगर ((msg->var[3] | msg->var[4]) == 0) अणु
					pr_debug("Authentication successful\n");
					local->card_status = CARD_AUTH_COMPLETE;
					associate(local);
					local->authentication_state =
					    AUTHENTICATED;
				पूर्ण अन्यथा अणु
					pr_debug("Authentication refused\n");
					local->card_status = CARD_AUTH_REFUSED;
					join_net(&local->समयr);
					local->authentication_state =
					    UNAUTHENTICATED;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण /* end rx_authenticate */

/*===========================================================================*/
अटल व्योम associate(ray_dev_t *local)
अणु
	काष्ठा ccs __iomem *pccs;
	काष्ठा pcmcia_device *link = local->finder;
	काष्ठा net_device *dev = link->priv;
	पूर्णांक ccsindex;
	अगर (!(pcmcia_dev_present(link))) अणु
		dev_dbg(&link->dev, "ray_cs associate - device not present\n");
		वापस;
	पूर्ण
	/* If no tx buffers available, वापस */
	अगर ((ccsindex = get_मुक्त_ccs(local)) < 0) अणु
/* TBD should never be here but... what अगर we are? */
		dev_dbg(&link->dev, "ray_cs associate - No free ccs\n");
		वापस;
	पूर्ण
	dev_dbg(&link->dev, "ray_cs Starting association with access point\n");
	pccs = ccs_base(local) + ccsindex;
	/* fill in the CCS */
	ग_लिखोb(CCS_START_ASSOCIATION, &pccs->cmd);
	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		dev_dbg(&link->dev, "ray_cs associate failed - ECF not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);

		del_समयr(&local->समयr);
		local->समयr.expires = jअगरfies + HZ * 2;
		local->समयr.function = join_net;
		add_समयr(&local->समयr);
		local->card_status = CARD_ASSOC_FAILED;
		वापस;
	पूर्ण
	अगर (!snअगरfer)
		netअगर_start_queue(dev);

पूर्ण /* end associate */

/*===========================================================================*/
अटल व्योम rx_deauthenticate(ray_dev_t *local, काष्ठा rcs __iomem *prcs,
			      अचिन्हित पूर्णांक pkt_addr, पूर्णांक rx_len)
अणु
/*  UCHAR buff[256];
    काष्ठा ray_rx_msg *msg = (काष्ठा ray_rx_msg *) buff;
*/
	pr_debug("Deauthentication frame received\n");
	local->authentication_state = UNAUTHENTICATED;
	/* Need to reauthenticate or rejoin depending on reason code */
/*  copy_from_rx_buff(local, buff, pkt_addr, rx_len & 0xff);
 */
पूर्ण

/*===========================================================================*/
अटल व्योम clear_पूर्णांकerrupt(ray_dev_t *local)
अणु
	ग_लिखोb(0, local->amem + CIS_OFFSET + HCS_INTR_OFFSET);
पूर्ण

/*===========================================================================*/
#अगर_घोषित CONFIG_PROC_FS
#घोषणा MAXDATA (PAGE_SIZE - 80)

अटल स्थिर अक्षर *card_status[] = अणु
	"Card inserted - uninitialized",	/* 0 */
	"Card not downloaded",			/* 1 */
	"Waiting for download parameters",	/* 2 */
	"Card doing acquisition",		/* 3 */
	"Acquisition complete",			/* 4 */
	"Authentication complete",		/* 5 */
	"Association complete",			/* 6 */
	"???", "???", "???", "???",		/* 7 8 9 10 undefined */
	"Card init error",			/* 11 */
	"Download parameters error",		/* 12 */
	"???",					/* 13 */
	"Acquisition failed",			/* 14 */
	"Authentication refused",		/* 15 */
	"Association failed"			/* 16 */
पूर्ण;

अटल स्थिर अक्षर *nettype[] = अणु "Adhoc", "Infra " पूर्ण;
अटल स्थिर अक्षर *framing[] = अणु "Encapsulation", "Translation" पूर्ण

;
/*===========================================================================*/
अटल पूर्णांक ray_cs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
/* Prपूर्णांक current values which are not available via other means
 * eg अगरconfig
 */
	पूर्णांक i;
	काष्ठा pcmcia_device *link;
	काष्ठा net_device *dev;
	ray_dev_t *local;
	UCHAR *p;
	काष्ठा freq_hop_element *pfh;
	UCHAR c[33];

	link = this_device;
	अगर (!link)
		वापस 0;
	dev = (काष्ठा net_device *)link->priv;
	अगर (!dev)
		वापस 0;
	local = netdev_priv(dev);
	अगर (!local)
		वापस 0;

	seq_माला_दो(m, "Raylink Wireless LAN driver status\n");
	seq_म_लिखो(m, "%s\n", rcsid);
	/* build 4 करोes not report version, and field is 0x55 after memtest */
	seq_माला_दो(m, "Firmware version     = ");
	अगर (local->fw_ver == 0x55)
		seq_माला_दो(m, "4 - Use dump_cis for more details\n");
	अन्यथा
		seq_म_लिखो(m, "%2d.%02d.%02d\n",
			   local->fw_ver, local->fw_bld, local->fw_var);

	क्रम (i = 0; i < 32; i++)
		c[i] = local->sparm.b5.a_current_ess_id[i];
	c[32] = 0;
	seq_म_लिखो(m, "%s network ESSID = \"%s\"\n",
		   nettype[local->sparm.b5.a_network_type], c);

	p = local->bss_id;
	seq_म_लिखो(m, "BSSID                = %pM\n", p);

	seq_म_लिखो(m, "Country code         = %d\n",
		   local->sparm.b5.a_curr_country_code);

	i = local->card_status;
	अगर (i < 0)
		i = 10;
	अगर (i > 16)
		i = 10;
	seq_म_लिखो(m, "Card status          = %s\n", card_status[i]);

	seq_म_लिखो(m, "Framing mode         = %s\n", framing[translate]);

	seq_म_लिखो(m, "Last pkt signal lvl  = %d\n", local->last_rsl);

	अगर (local->beacon_rxed) अणु
		/* Pull some fields out of last beacon received */
		seq_म_लिखो(m, "Beacon Interval      = %d Kus\n",
			   local->last_bcn.beacon_पूर्णांकvl[0]
			   + 256 * local->last_bcn.beacon_पूर्णांकvl[1]);

		p = local->last_bcn.elements;
		अगर (p[0] == C_ESSID_ELEMENT_ID)
			p += p[1] + 2;
		अन्यथा अणु
			seq_म_लिखो(m,
				   "Parse beacon failed at essid element id = %d\n",
				   p[0]);
			वापस 0;
		पूर्ण

		अगर (p[0] == C_SUPPORTED_RATES_ELEMENT_ID) अणु
			seq_माला_दो(m, "Supported rate codes = ");
			क्रम (i = 2; i < p[1] + 2; i++)
				seq_म_लिखो(m, "0x%02x ", p[i]);
			seq_अ_दो(m, '\n');
			p += p[1] + 2;
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, "Parse beacon failed at rates element\n");
			वापस 0;
		पूर्ण

		अगर (p[0] == C_FH_PARAM_SET_ELEMENT_ID) अणु
			pfh = (काष्ठा freq_hop_element *)p;
			seq_म_लिखो(m, "Hop dwell            = %d Kus\n",
				   pfh->dwell_समय[0] +
				   256 * pfh->dwell_समय[1]);
			seq_म_लिखो(m, "Hop set              = %d\n",
				   pfh->hop_set);
			seq_म_लिखो(m, "Hop pattern          = %d\n",
				   pfh->hop_pattern);
			seq_म_लिखो(m, "Hop index            = %d\n",
				   pfh->hop_index);
			p += p[1] + 2;
		पूर्ण अन्यथा अणु
			seq_माला_दो(m,
				 "Parse beacon failed at FH param element\n");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "No beacons received\n");
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर
/*===========================================================================*/
अटल पूर्णांक build_auth_frame(ray_dev_t *local, UCHAR *dest, पूर्णांक auth_type)
अणु
	पूर्णांक addr;
	काष्ठा ccs __iomem *pccs;
	काष्ठा tx_msg __iomem *ptx;
	पूर्णांक ccsindex;

	/* If no tx buffers available, वापस */
	अगर ((ccsindex = get_मुक्त_tx_ccs(local)) < 0) अणु
		pr_debug("ray_cs send authenticate - No free tx ccs\n");
		वापस -1;
	पूर्ण

	pccs = ccs_base(local) + ccsindex;

	/* Address in card space */
	addr = TX_BUF_BASE + (ccsindex << 11);
	/* fill in the CCS */
	ग_लिखोb(CCS_TX_REQUEST, &pccs->cmd);
	ग_लिखोb(addr >> 8, pccs->var.tx_request.tx_data_ptr);
	ग_लिखोb(0x20, pccs->var.tx_request.tx_data_ptr + 1);
	ग_लिखोb(TX_AUTHENTICATE_LENGTH_MSB, pccs->var.tx_request.tx_data_length);
	ग_लिखोb(TX_AUTHENTICATE_LENGTH_LSB,
	       pccs->var.tx_request.tx_data_length + 1);
	ग_लिखोb(0, &pccs->var.tx_request.घात_sav_mode);

	ptx = local->sram + addr;
	/* fill in the mac header */
	ग_लिखोb(PROTOCOL_VER | AUTHENTIC_TYPE, &ptx->mac.frame_ctl_1);
	ग_लिखोb(0, &ptx->mac.frame_ctl_2);

	स_नकल_toio(ptx->mac.addr_1, dest, ADDRLEN);
	स_नकल_toio(ptx->mac.addr_2, local->sparm.b4.a_mac_addr, ADDRLEN);
	स_नकल_toio(ptx->mac.addr_3, local->bss_id, ADDRLEN);

	/* Fill in msg body with protocol 00 00, sequence 01 00 ,status 00 00 */
	स_रखो_io(ptx->var, 0, 6);
	ग_लिखोb(auth_type & 0xff, ptx->var + 2);

	/* Interrupt the firmware to process the command */
	अगर (पूर्णांकerrupt_ecf(local, ccsindex)) अणु
		pr_debug(
		      "ray_cs send authentication request failed - ECF not ready for intr\n");
		ग_लिखोb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण /* End build_auth_frame */

/*===========================================================================*/
#अगर_घोषित CONFIG_PROC_FS
अटल sमाप_प्रकार ray_cs_essid_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अटल अक्षर proc_essid[33];
	अचिन्हित पूर्णांक len = count;

	अगर (len > 32)
		len = 32;
	स_रखो(proc_essid, 0, 33);
	अगर (copy_from_user(proc_essid, buffer, len))
		वापस -EFAULT;
	essid = proc_essid;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops ray_cs_essid_proc_ops = अणु
	.proc_ग_लिखो	= ray_cs_essid_proc_ग_लिखो,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल sमाप_प्रकार पूर्णांक_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *pos)
अणु
	अटल अक्षर proc_number[10];
	अक्षर *p;
	पूर्णांक nr, len;

	अगर (!count)
		वापस 0;

	अगर (count > 9)
		वापस -EINVAL;
	अगर (copy_from_user(proc_number, buffer, count))
		वापस -EFAULT;
	p = proc_number;
	nr = 0;
	len = count;
	करो अणु
		अचिन्हित पूर्णांक c = *p - '0';
		अगर (c > 9)
			वापस -EINVAL;
		nr = nr * 10 + c;
		p++;
	पूर्ण जबतक (--len);
	*(पूर्णांक *)PDE_DATA(file_inode(file)) = nr;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops पूर्णांक_proc_ops = अणु
	.proc_ग_लिखो	= पूर्णांक_proc_ग_लिखो,
	.proc_lseek	= noop_llseek,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा pcmcia_device_id ray_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x01a6, 0x0000),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, ray_ids);

अटल काष्ठा pcmcia_driver ray_driver = अणु
	.owner = THIS_MODULE,
	.name = "ray_cs",
	.probe = ray_probe,
	.हटाओ = ray_detach,
	.id_table = ray_ids,
	.suspend = ray_suspend,
	.resume = ray_resume,
पूर्ण;

अटल पूर्णांक __init init_ray_cs(व्योम)
अणु
	पूर्णांक rc;

	pr_debug("%s\n", rcsid);
	rc = pcmcia_रेजिस्टर_driver(&ray_driver);
	pr_debug("raylink init_module register_pcmcia_driver returns 0x%x\n",
	      rc);
	अगर (rc)
		वापस rc;

#अगर_घोषित CONFIG_PROC_FS
	proc_सूची_गढ़ो("driver/ray_cs", शून्य);

	proc_create_single("driver/ray_cs/ray_cs", 0, शून्य, ray_cs_proc_show);
	proc_create("driver/ray_cs/essid", 0200, शून्य, &ray_cs_essid_proc_ops);
	proc_create_data("driver/ray_cs/net_type", 0200, शून्य, &पूर्णांक_proc_ops,
			 &net_type);
	proc_create_data("driver/ray_cs/translate", 0200, शून्य, &पूर्णांक_proc_ops,
			 &translate);
#पूर्ण_अगर
	translate = !!translate;
	वापस 0;
पूर्ण /* init_ray_cs */

/*===========================================================================*/

अटल व्योम __निकास निकास_ray_cs(व्योम)
अणु
	pr_debug("ray_cs: cleanup_module\n");

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_subtree("driver/ray_cs", शून्य);
#पूर्ण_अगर

	pcmcia_unरेजिस्टर_driver(&ray_driver);
पूर्ण /* निकास_ray_cs */

module_init(init_ray_cs);
module_निकास(निकास_ray_cs);

/*===========================================================================*/
