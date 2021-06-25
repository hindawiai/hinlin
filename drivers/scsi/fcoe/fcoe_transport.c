<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crc32.h>
#समावेश <scsi/libfcoe.h>

#समावेश "libfcoe.h"

MODULE_AUTHOR("Open-FCoE.org");
MODULE_DESCRIPTION("FIP discovery protocol and FCoE transport for FCoE HBAs");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक fcoe_transport_create(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
अटल पूर्णांक fcoe_transport_destroy(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
अटल पूर्णांक fcoe_transport_show(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
अटल काष्ठा fcoe_transport *fcoe_transport_lookup(काष्ठा net_device *device);
अटल काष्ठा fcoe_transport *fcoe_netdev_map_lookup(काष्ठा net_device *device);
अटल पूर्णांक fcoe_transport_enable(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
अटल पूर्णांक fcoe_transport_disable(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
अटल पूर्णांक libfcoe_device_notअगरication(काष्ठा notअगरier_block *notअगरier,
				    uदीर्घ event, व्योम *ptr);

अटल LIST_HEAD(fcoe_transports);
अटल DEFINE_MUTEX(ft_mutex);
अटल LIST_HEAD(fcoe_netdevs);
अटल DEFINE_MUTEX(fn_mutex);

अचिन्हित पूर्णांक libfcoe_debug_logging;
module_param_named(debug_logging, libfcoe_debug_logging, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug_logging, "a bit mask of logging levels");

module_param_call(show, शून्य, fcoe_transport_show, शून्य, S_IRUSR);
__MODULE_PARM_TYPE(show, "string");
MODULE_PARM_DESC(show, " Show attached FCoE transports");

module_param_call(create, fcoe_transport_create, शून्य,
		  (व्योम *)FIP_MODE_FABRIC, S_IWUSR);
__MODULE_PARM_TYPE(create, "string");
MODULE_PARM_DESC(create, " Creates fcoe instance on an ethernet interface");

module_param_call(create_vn2vn, fcoe_transport_create, शून्य,
		  (व्योम *)FIP_MODE_VN2VN, S_IWUSR);
__MODULE_PARM_TYPE(create_vn2vn, "string");
MODULE_PARM_DESC(create_vn2vn, " Creates a VN_node to VN_node FCoE instance "
		 "on an Ethernet interface");

module_param_call(destroy, fcoe_transport_destroy, शून्य, शून्य, S_IWUSR);
__MODULE_PARM_TYPE(destroy, "string");
MODULE_PARM_DESC(destroy, " Destroys fcoe instance on an ethernet interface");

module_param_call(enable, fcoe_transport_enable, शून्य, शून्य, S_IWUSR);
__MODULE_PARM_TYPE(enable, "string");
MODULE_PARM_DESC(enable, " Enables fcoe on an ethernet interface.");

module_param_call(disable, fcoe_transport_disable, शून्य, शून्य, S_IWUSR);
__MODULE_PARM_TYPE(disable, "string");
MODULE_PARM_DESC(disable, " Disables fcoe on an ethernet interface.");

/* notअगरication function क्रम packets from net device */
अटल काष्ठा notअगरier_block libfcoe_notअगरier = अणु
	.notअगरier_call = libfcoe_device_notअगरication,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u32 fc_port_speed;
#घोषणा SPEED_2000	2000
#घोषणा SPEED_4000	4000
#घोषणा SPEED_8000	8000
#घोषणा SPEED_16000	16000
#घोषणा SPEED_32000	32000
	u32 eth_port_speed;
पूर्ण fcoe_port_speed_mapping[] = अणु
	अणु FC_PORTSPEED_1GBIT,   SPEED_1000   पूर्ण,
	अणु FC_PORTSPEED_2GBIT,   SPEED_2000   पूर्ण,
	अणु FC_PORTSPEED_4GBIT,   SPEED_4000   पूर्ण,
	अणु FC_PORTSPEED_8GBIT,   SPEED_8000   पूर्ण,
	अणु FC_PORTSPEED_10GBIT,  SPEED_10000  पूर्ण,
	अणु FC_PORTSPEED_16GBIT,  SPEED_16000  पूर्ण,
	अणु FC_PORTSPEED_20GBIT,  SPEED_20000  पूर्ण,
	अणु FC_PORTSPEED_25GBIT,  SPEED_25000  पूर्ण,
	अणु FC_PORTSPEED_32GBIT,  SPEED_32000  पूर्ण,
	अणु FC_PORTSPEED_40GBIT,  SPEED_40000  पूर्ण,
	अणु FC_PORTSPEED_50GBIT,  SPEED_50000  पूर्ण,
	अणु FC_PORTSPEED_100GBIT, SPEED_100000 पूर्ण,
पूर्ण;

अटल अंतरभूत u32 eth2fc_speed(u32 eth_port_speed)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fcoe_port_speed_mapping); i++) अणु
		अगर (fcoe_port_speed_mapping[i].eth_port_speed == eth_port_speed)
			वापस fcoe_port_speed_mapping[i].fc_port_speed;
	पूर्ण

	वापस FC_PORTSPEED_UNKNOWN;
पूर्ण

/**
 * fcoe_link_speed_update() - Update the supported and actual link speeds
 * @lport: The local port to update speeds क्रम
 *
 * Returns: 0 अगर the ethtool query was successful
 *          -1 अगर the ethtool query failed
 */
पूर्णांक fcoe_link_speed_update(काष्ठा fc_lport *lport)
अणु
	काष्ठा net_device *netdev = fcoe_get_netdev(lport);
	काष्ठा ethtool_link_ksettings ecmd;

	अगर (!__ethtool_get_link_ksettings(netdev, &ecmd)) अणु
		lport->link_supported_speeds &= ~(FC_PORTSPEED_1GBIT  |
		                                  FC_PORTSPEED_10GBIT |
		                                  FC_PORTSPEED_20GBIT |
		                                  FC_PORTSPEED_40GBIT);

		अगर (ecmd.link_modes.supported[0] & (
			    SUPPORTED_1000baseT_Half |
			    SUPPORTED_1000baseT_Full |
			    SUPPORTED_1000baseKX_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_1GBIT;

		अगर (ecmd.link_modes.supported[0] & (
			    SUPPORTED_10000baseT_Full   |
			    SUPPORTED_10000baseKX4_Full |
			    SUPPORTED_10000baseKR_Full  |
			    SUPPORTED_10000baseR_FEC))
			lport->link_supported_speeds |= FC_PORTSPEED_10GBIT;

		अगर (ecmd.link_modes.supported[0] & (
			    SUPPORTED_20000baseMLD2_Full |
			    SUPPORTED_20000baseKR2_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_20GBIT;

		अगर (ecmd.link_modes.supported[0] & (
			    SUPPORTED_40000baseKR4_Full |
			    SUPPORTED_40000baseCR4_Full |
			    SUPPORTED_40000baseSR4_Full |
			    SUPPORTED_40000baseLR4_Full))
			lport->link_supported_speeds |= FC_PORTSPEED_40GBIT;

		lport->link_speed = eth2fc_speed(ecmd.base.speed);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_link_speed_update);

/**
 * __fcoe_get_lesb() - Get the Link Error Status Block (LESB) क्रम a given lport
 * @lport: The local port to update speeds क्रम
 * @fc_lesb: Poपूर्णांकer to the LESB to be filled up
 * @netdev: Poपूर्णांकer to the netdev that is associated with the lport
 *
 * Note, the Link Error Status Block (LESB) क्रम FCoE is defined in FC-BB-6
 * Clause 7.11 in v1.04.
 */
व्योम __fcoe_get_lesb(काष्ठा fc_lport *lport,
		     काष्ठा fc_els_lesb *fc_lesb,
		     काष्ठा net_device *netdev)
अणु
	अचिन्हित पूर्णांक cpu;
	u32 lfc, vlfc, mdac;
	काष्ठा fc_stats *stats;
	काष्ठा fcoe_fc_els_lesb *lesb;
	काष्ठा rtnl_link_stats64 temp;

	lfc = 0;
	vlfc = 0;
	mdac = 0;
	lesb = (काष्ठा fcoe_fc_els_lesb *)fc_lesb;
	स_रखो(lesb, 0, माप(*lesb));
	क्रम_each_possible_cpu(cpu) अणु
		stats = per_cpu_ptr(lport->stats, cpu);
		lfc += stats->LinkFailureCount;
		vlfc += stats->VLinkFailureCount;
		mdac += stats->MissDiscAdvCount;
	पूर्ण
	lesb->lesb_link_fail = htonl(lfc);
	lesb->lesb_vlink_fail = htonl(vlfc);
	lesb->lesb_miss_fka = htonl(mdac);
	lesb->lesb_fcs_error =
			htonl(dev_get_stats(netdev, &temp)->rx_crc_errors);
पूर्ण
EXPORT_SYMBOL_GPL(__fcoe_get_lesb);

/**
 * fcoe_get_lesb() - Fill the FCoE Link Error Status Block
 * @lport: the local port
 * @fc_lesb: the link error status block
 */
व्योम fcoe_get_lesb(काष्ठा fc_lport *lport,
			 काष्ठा fc_els_lesb *fc_lesb)
अणु
	काष्ठा net_device *netdev = fcoe_get_netdev(lport);

	__fcoe_get_lesb(lport, fc_lesb, netdev);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_get_lesb);

/**
 * fcoe_ctlr_get_lesb() - Get the Link Error Status Block (LESB) क्रम a given
 * fcoe controller device
 * @ctlr_dev: The given fcoe controller device
 *
 */
व्योम fcoe_ctlr_get_lesb(काष्ठा fcoe_ctlr_device *ctlr_dev)
अणु
	काष्ठा fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा net_device *netdev = fcoe_get_netdev(fip->lp);
	काष्ठा fc_els_lesb *fc_lesb;

	fc_lesb = (काष्ठा fc_els_lesb *)(&ctlr_dev->lesb);
	__fcoe_get_lesb(fip->lp, fc_lesb, netdev);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_ctlr_get_lesb);

व्योम fcoe_wwn_to_str(u64 wwn, अक्षर *buf, पूर्णांक len)
अणु
	u8 wwpn[8];

	u64_to_wwn(wwn, wwpn);
	snम_लिखो(buf, len, "%02x%02x%02x%02x%02x%02x%02x%02x",
		 wwpn[0], wwpn[1], wwpn[2], wwpn[3],
		 wwpn[4], wwpn[5], wwpn[6], wwpn[7]);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_wwn_to_str);

/**
 * fcoe_validate_vport_create() - Validate a vport beक्रमe creating it
 * @vport: NPIV port to be created
 *
 * This routine is meant to add validation क्रम a vport beक्रमe creating it
 * via fcoe_vport_create().
 * Current validations are:
 *      - WWPN supplied is unique क्रम given lport
 */
पूर्णांक fcoe_validate_vport_create(काष्ठा fc_vport *vport)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port;
	पूर्णांक rc = 0;
	अक्षर buf[32];

	mutex_lock(&n_port->lp_mutex);

	fcoe_wwn_to_str(vport->port_name, buf, माप(buf));
	/* Check अगर the wwpn is not same as that of the lport */
	अगर (!स_भेद(&n_port->wwpn, &vport->port_name, माप(u64))) अणु
		LIBFCOE_TRANSPORT_DBG("vport WWPN 0x%s is same as that of the "
				      "base port WWPN\n", buf);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Check अगर there is any existing vport with same wwpn */
	list_क्रम_each_entry(vn_port, &n_port->vports, list) अणु
		अगर (!स_भेद(&vn_port->wwpn, &vport->port_name, माप(u64))) अणु
			LIBFCOE_TRANSPORT_DBG("vport with given WWPN 0x%s "
					      "already exists\n", buf);
			rc = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&n_port->lp_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_validate_vport_create);

/**
 * fcoe_get_wwn() - Get the world wide name from LLD अगर it supports it
 * @netdev: the associated net device
 * @wwn: the output WWN
 * @type: the type of WWN (WWPN or WWNN)
 *
 * Returns: 0 क्रम success
 */
पूर्णांक fcoe_get_wwn(काष्ठा net_device *netdev, u64 *wwn, पूर्णांक type)
अणु
	स्थिर काष्ठा net_device_ops *ops = netdev->netdev_ops;

	अगर (ops->nकरो_fcoe_get_wwn)
		वापस ops->nकरो_fcoe_get_wwn(netdev, wwn, type);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_get_wwn);

/**
 * fcoe_fc_crc() - Calculates the CRC क्रम a given frame
 * @fp: The frame to be checksumed
 *
 * This uses crc32() routine to calculate the CRC क्रम a frame
 *
 * Return: The 32 bit CRC value
 */
u32 fcoe_fc_crc(काष्ठा fc_frame *fp)
अणु
	काष्ठा sk_buff *skb = fp_skb(fp);
	skb_frag_t *frag;
	अचिन्हित अक्षर *data;
	अचिन्हित दीर्घ off, len, clen;
	u32 crc;
	अचिन्हित i;

	crc = crc32(~0, skb->data, skb_headlen(skb));

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		off = skb_frag_off(frag);
		len = skb_frag_size(frag);
		जबतक (len > 0) अणु
			clen = min(len, PAGE_SIZE - (off & ~PAGE_MASK));
			data = kmap_atomic(
				skb_frag_page(frag) + (off >> PAGE_SHIFT));
			crc = crc32(crc, data + (off & ~PAGE_MASK), clen);
			kunmap_atomic(data);
			off += clen;
			len -= clen;
		पूर्ण
	पूर्ण
	वापस crc;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_fc_crc);

/**
 * fcoe_start_io() - Start FCoE I/O
 * @skb: The packet to be transmitted
 *
 * This routine is called from the net device to start transmitting
 * FCoE packets.
 *
 * Returns: 0 क्रम success
 */
पूर्णांक fcoe_start_io(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;
	पूर्णांक rc;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		वापस -ENOMEM;
	rc = dev_queue_xmit(nskb);
	अगर (rc != 0)
		वापस rc;
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_start_io);


/**
 * fcoe_clean_pending_queue() - Dequeue a skb and मुक्त it
 * @lport: The local port to dequeue a skb on
 */
व्योम fcoe_clean_pending_queue(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port  *port = lport_priv(lport);
	काष्ठा sk_buff *skb;

	spin_lock_bh(&port->fcoe_pending_queue.lock);
	जबतक ((skb = __skb_dequeue(&port->fcoe_pending_queue)) != शून्य) अणु
		spin_unlock_bh(&port->fcoe_pending_queue.lock);
		kमुक्त_skb(skb);
		spin_lock_bh(&port->fcoe_pending_queue.lock);
	पूर्ण
	spin_unlock_bh(&port->fcoe_pending_queue.lock);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_clean_pending_queue);

/**
 * fcoe_check_रुको_queue() - Attempt to clear the transmit backlog
 * @lport: The local port whose backlog is to be cleared
 * @skb: The received FIP packet
 *
 * This empties the रुको_queue, dequeues the head of the रुको_queue queue
 * and calls fcoe_start_io() क्रम each packet. If all skb have been
 * transmitted it वापसs the qlen. If an error occurs it restores
 * रुको_queue (to try again later) and वापसs -1.
 *
 * The रुको_queue is used when the skb transmit fails. The failed skb
 * will go in the रुको_queue which will be emptied by the समयr function or
 * by the next skb transmit.
 */
व्योम fcoe_check_रुको_queue(काष्ठा fc_lport *lport, काष्ठा sk_buff *skb)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	पूर्णांक rc;

	spin_lock_bh(&port->fcoe_pending_queue.lock);

	अगर (skb)
		__skb_queue_tail(&port->fcoe_pending_queue, skb);

	अगर (port->fcoe_pending_queue_active)
		जाओ out;
	port->fcoe_pending_queue_active = 1;

	जबतक (port->fcoe_pending_queue.qlen) अणु
		/* keep qlen > 0 until fcoe_start_io succeeds */
		port->fcoe_pending_queue.qlen++;
		skb = __skb_dequeue(&port->fcoe_pending_queue);

		spin_unlock_bh(&port->fcoe_pending_queue.lock);
		rc = fcoe_start_io(skb);
		spin_lock_bh(&port->fcoe_pending_queue.lock);

		अगर (rc) अणु
			__skb_queue_head(&port->fcoe_pending_queue, skb);
			/* unकरो temporary increment above */
			port->fcoe_pending_queue.qlen--;
			अवरोध;
		पूर्ण
		/* unकरो temporary increment above */
		port->fcoe_pending_queue.qlen--;
	पूर्ण

	अगर (port->fcoe_pending_queue.qlen < port->min_queue_depth)
		lport->qfull = 0;
	अगर (port->fcoe_pending_queue.qlen && !समयr_pending(&port->समयr))
		mod_समयr(&port->समयr, jअगरfies + 2);
	port->fcoe_pending_queue_active = 0;
out:
	अगर (port->fcoe_pending_queue.qlen > port->max_queue_depth)
		lport->qfull = 1;
	spin_unlock_bh(&port->fcoe_pending_queue.lock);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_check_रुको_queue);

/**
 * fcoe_queue_समयr() - The fcoe queue समयr
 * @t: Timer context use to obtain the FCoE port
 *
 * Calls fcoe_check_रुको_queue on समयout
 */
व्योम fcoe_queue_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fcoe_port *port = from_समयr(port, t, समयr);

	fcoe_check_रुको_queue(port->lport, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_queue_समयr);

/**
 * fcoe_get_paged_crc_eof() - Allocate a page to be used क्रम the trailer CRC
 * @skb:  The packet to be transmitted
 * @tlen: The total length of the trailer
 * @fps:  The fcoe context
 *
 * This routine allocates a page क्रम frame trailers. The page is re-used अगर
 * there is enough room left on it क्रम the current trailer. If there isn't
 * enough buffer left a new page is allocated क्रम the trailer. Reference to
 * the page from this function as well as the skbs using the page fragments
 * ensure that the page is मुक्तd at the appropriate समय.
 *
 * Returns: 0 क्रम success
 */
पूर्णांक fcoe_get_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen,
			   काष्ठा fcoe_percpu_s *fps)
अणु
	काष्ठा page *page;

	page = fps->crc_eof_page;
	अगर (!page) अणु
		page = alloc_page(GFP_ATOMIC);
		अगर (!page)
			वापस -ENOMEM;

		fps->crc_eof_page = page;
		fps->crc_eof_offset = 0;
	पूर्ण

	get_page(page);
	skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags, page,
			   fps->crc_eof_offset, tlen);
	skb->len += tlen;
	skb->data_len += tlen;
	skb->truesize += tlen;
	fps->crc_eof_offset += माप(काष्ठा fcoe_crc_eof);

	अगर (fps->crc_eof_offset >= PAGE_SIZE) अणु
		fps->crc_eof_page = शून्य;
		fps->crc_eof_offset = 0;
		put_page(page);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_get_paged_crc_eof);

/**
 * fcoe_transport_lookup - find an fcoe transport that matches a netdev
 * @netdev: The netdev to look क्रम from all attached transports
 *
 * Returns : ptr to the fcoe transport that supports this netdev or शून्य
 * अगर not found.
 *
 * The ft_mutex should be held when this is called
 */
अटल काष्ठा fcoe_transport *fcoe_transport_lookup(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_transport *ft = शून्य;

	list_क्रम_each_entry(ft, &fcoe_transports, list)
		अगर (ft->match && ft->match(netdev))
			वापस ft;
	वापस शून्य;
पूर्ण

/**
 * fcoe_transport_attach - Attaches an FCoE transport
 * @ft: The fcoe transport to be attached
 *
 * Returns : 0 क्रम success
 */
पूर्णांक fcoe_transport_attach(काष्ठा fcoe_transport *ft)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&ft_mutex);
	अगर (ft->attached) अणु
		LIBFCOE_TRANSPORT_DBG("transport %s already attached\n",
				       ft->name);
		rc = -EEXIST;
		जाओ out_attach;
	पूर्ण

	/* Add शेष transport to the tail */
	अगर (म_भेद(ft->name, FCOE_TRANSPORT_DEFAULT))
		list_add(&ft->list, &fcoe_transports);
	अन्यथा
		list_add_tail(&ft->list, &fcoe_transports);

	ft->attached = true;
	LIBFCOE_TRANSPORT_DBG("attaching transport %s\n", ft->name);

out_attach:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fcoe_transport_attach);

/**
 * fcoe_transport_detach - Detaches an FCoE transport
 * @ft: The fcoe transport to be attached
 *
 * Returns : 0 क्रम success
 */
पूर्णांक fcoe_transport_detach(काष्ठा fcoe_transport *ft)
अणु
	पूर्णांक rc = 0;
	काष्ठा fcoe_netdev_mapping *nm = शून्य, *पंचांगp;

	mutex_lock(&ft_mutex);
	अगर (!ft->attached) अणु
		LIBFCOE_TRANSPORT_DBG("transport %s already detached\n",
			ft->name);
		rc = -ENODEV;
		जाओ out_attach;
	पूर्ण

	/* हटाओ netdev mapping क्रम this transport as it is going away */
	mutex_lock(&fn_mutex);
	list_क्रम_each_entry_safe(nm, पंचांगp, &fcoe_netdevs, list) अणु
		अगर (nm->ft == ft) अणु
			LIBFCOE_TRANSPORT_DBG("transport %s going away, "
				"remove its netdev mapping for %s\n",
				ft->name, nm->netdev->name);
			list_del(&nm->list);
			kमुक्त(nm);
		पूर्ण
	पूर्ण
	mutex_unlock(&fn_mutex);

	list_del(&ft->list);
	ft->attached = false;
	LIBFCOE_TRANSPORT_DBG("detaching transport %s\n", ft->name);

out_attach:
	mutex_unlock(&ft_mutex);
	वापस rc;

पूर्ण
EXPORT_SYMBOL(fcoe_transport_detach);

अटल पूर्णांक fcoe_transport_show(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, j;
	काष्ठा fcoe_transport *ft = शून्य;

	i = j = प्र_लिखो(buffer, "Attached FCoE transports:");
	mutex_lock(&ft_mutex);
	list_क्रम_each_entry(ft, &fcoe_transports, list) अणु
		अगर (i >= PAGE_SIZE - IFNAMSIZ)
			अवरोध;
		i += snम_लिखो(&buffer[i], IFNAMSIZ, "%s ", ft->name);
	पूर्ण
	mutex_unlock(&ft_mutex);
	अगर (i == j)
		i += snम_लिखो(&buffer[i], IFNAMSIZ, "none");
	वापस i;
पूर्ण

अटल पूर्णांक __init fcoe_transport_init(व्योम)
अणु
	रेजिस्टर_netdevice_notअगरier(&libfcoe_notअगरier);
	वापस 0;
पूर्ण

अटल पूर्णांक fcoe_transport_निकास(व्योम)
अणु
	काष्ठा fcoe_transport *ft;

	unरेजिस्टर_netdevice_notअगरier(&libfcoe_notअगरier);
	mutex_lock(&ft_mutex);
	list_क्रम_each_entry(ft, &fcoe_transports, list)
		prपूर्णांकk(KERN_ERR "FCoE transport %s is still attached!\n",
		      ft->name);
	mutex_unlock(&ft_mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक fcoe_add_netdev_mapping(काष्ठा net_device *netdev,
					काष्ठा fcoe_transport *ft)
अणु
	काष्ठा fcoe_netdev_mapping *nm;

	nm = kदो_स्मृति(माप(*nm), GFP_KERNEL);
	अगर (!nm) अणु
		prपूर्णांकk(KERN_ERR "Unable to allocate netdev_mapping");
		वापस -ENOMEM;
	पूर्ण

	nm->netdev = netdev;
	nm->ft = ft;

	mutex_lock(&fn_mutex);
	list_add(&nm->list, &fcoe_netdevs);
	mutex_unlock(&fn_mutex);
	वापस 0;
पूर्ण


अटल व्योम fcoe_del_netdev_mapping(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_netdev_mapping *nm = शून्य, *पंचांगp;

	mutex_lock(&fn_mutex);
	list_क्रम_each_entry_safe(nm, पंचांगp, &fcoe_netdevs, list) अणु
		अगर (nm->netdev == netdev) अणु
			list_del(&nm->list);
			kमुक्त(nm);
			mutex_unlock(&fn_mutex);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&fn_mutex);
पूर्ण


/**
 * fcoe_netdev_map_lookup - find the fcoe transport that matches the netdev on which
 * it was created
 * @netdev: The net device that the FCoE पूर्णांकerface is on
 *
 * Returns : ptr to the fcoe transport that supports this netdev or शून्य
 * अगर not found.
 *
 * The ft_mutex should be held when this is called
 */
अटल काष्ठा fcoe_transport *fcoe_netdev_map_lookup(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_transport *ft = शून्य;
	काष्ठा fcoe_netdev_mapping *nm;

	mutex_lock(&fn_mutex);
	list_क्रम_each_entry(nm, &fcoe_netdevs, list) अणु
		अगर (netdev == nm->netdev) अणु
			ft = nm->ft;
			mutex_unlock(&fn_mutex);
			वापस ft;
		पूर्ण
	पूर्ण

	mutex_unlock(&fn_mutex);
	वापस शून्य;
पूर्ण

/**
 * fcoe_अगर_to_netdev() - Parse a name buffer to get a net device
 * @buffer: The name of the net device
 *
 * Returns: शून्य or a ptr to net_device
 */
अटल काष्ठा net_device *fcoe_अगर_to_netdev(स्थिर अक्षर *buffer)
अणु
	अक्षर *cp;
	अक्षर अगरname[IFNAMSIZ + 2];

	अगर (buffer) अणु
		strlcpy(अगरname, buffer, IFNAMSIZ);
		cp = अगरname + म_माप(अगरname);
		जबतक (--cp >= अगरname && *cp == '\n')
			*cp = '\0';
		वापस dev_get_by_name(&init_net, अगरname);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * libfcoe_device_notअगरication() - Handler क्रम net device events
 * @notअगरier: The context of the notअगरication
 * @event:    The type of event
 * @ptr:      The net device that the event was on
 *
 * This function is called by the Ethernet driver in हाल of link change event.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक libfcoe_device_notअगरication(काष्ठा notअगरier_block *notअगरier,
				    uदीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		LIBFCOE_TRANSPORT_DBG("NETDEV_UNREGISTER %s\n",
				      netdev->name);
		fcoe_del_netdev_mapping(netdev);
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

sमाप_प्रकार fcoe_ctlr_create_store(काष्ठा bus_type *bus,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक err;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buf);
	अगर (!netdev) अणु
		LIBFCOE_TRANSPORT_DBG("Invalid device %s.\n", buf);
		rc = -ENODEV;
		जाओ out_nodev;
	पूर्ण

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (ft) अणु
		LIBFCOE_TRANSPORT_DBG("transport %s already has existing "
				      "FCoE instance on %s.\n",
				      ft->name, netdev->name);
		rc = -EEXIST;
		जाओ out_putdev;
	पूर्ण

	ft = fcoe_transport_lookup(netdev);
	अगर (!ft) अणु
		LIBFCOE_TRANSPORT_DBG("no FCoE transport found for %s.\n",
				      netdev->name);
		rc = -ENODEV;
		जाओ out_putdev;
	पूर्ण

	/* pass to transport create */
	err = ft->alloc ? ft->alloc(netdev) : -ENODEV;
	अगर (err) अणु
		fcoe_del_netdev_mapping(netdev);
		rc = -ENOMEM;
		जाओ out_putdev;
	पूर्ण

	err = fcoe_add_netdev_mapping(netdev, ft);
	अगर (err) अणु
		LIBFCOE_TRANSPORT_DBG("failed to add new netdev mapping "
				      "for FCoE transport %s for %s.\n",
				      ft->name, netdev->name);
		rc = -ENODEV;
		जाओ out_putdev;
	पूर्ण

	LIBFCOE_TRANSPORT_DBG("transport %s succeeded to create fcoe on %s.\n",
			      ft->name, netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण

sमाप_प्रकार fcoe_ctlr_destroy_store(काष्ठा bus_type *bus,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buf);
	अगर (!netdev) अणु
		LIBFCOE_TRANSPORT_DBG("invalid device %s.\n", buf);
		जाओ out_nodev;
	पूर्ण

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (!ft) अणु
		LIBFCOE_TRANSPORT_DBG("no FCoE transport found for %s.\n",
				      netdev->name);
		जाओ out_putdev;
	पूर्ण

	/* pass to transport destroy */
	rc = ft->destroy(netdev);
	अगर (rc)
		जाओ out_putdev;

	fcoe_del_netdev_mapping(netdev);
	LIBFCOE_TRANSPORT_DBG("transport %s %s to destroy fcoe on %s.\n",
			      ft->name, (rc) ? "failed" : "succeeded",
			      netdev->name);
	rc = count; /* required क्रम successful वापस */
out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_transport_create() - Create a fcoe पूर्णांकerface
 * @buffer: The name of the Ethernet पूर्णांकerface to create on
 * @kp:	    The associated kernel param
 *
 * Called from sysfs. This holds the ft_mutex जबतक calling the
 * रेजिस्टरed fcoe transport's create function.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_transport_create(स्थिर अक्षर *buffer,
				 स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;
	क्रमागत fip_mode fip_mode = (क्रमागत fip_mode)(uपूर्णांकptr_t)kp->arg;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buffer);
	अगर (!netdev) अणु
		LIBFCOE_TRANSPORT_DBG("Invalid device %s.\n", buffer);
		जाओ out_nodev;
	पूर्ण

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (ft) अणु
		LIBFCOE_TRANSPORT_DBG("transport %s already has existing "
				      "FCoE instance on %s.\n",
				      ft->name, netdev->name);
		rc = -EEXIST;
		जाओ out_putdev;
	पूर्ण

	ft = fcoe_transport_lookup(netdev);
	अगर (!ft) अणु
		LIBFCOE_TRANSPORT_DBG("no FCoE transport found for %s.\n",
				      netdev->name);
		जाओ out_putdev;
	पूर्ण

	rc = fcoe_add_netdev_mapping(netdev, ft);
	अगर (rc) अणु
		LIBFCOE_TRANSPORT_DBG("failed to add new netdev mapping "
				      "for FCoE transport %s for %s.\n",
				      ft->name, netdev->name);
		जाओ out_putdev;
	पूर्ण

	/* pass to transport create */
	rc = ft->create ? ft->create(netdev, fip_mode) : -ENODEV;
	अगर (rc)
		fcoe_del_netdev_mapping(netdev);

	LIBFCOE_TRANSPORT_DBG("transport %s %s to create fcoe on %s.\n",
			      ft->name, (rc) ? "failed" : "succeeded",
			      netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_transport_destroy() - Destroy a FCoE पूर्णांकerface
 * @buffer: The name of the Ethernet पूर्णांकerface to be destroyed
 * @kp:	    The associated kernel parameter
 *
 * Called from sysfs. This holds the ft_mutex जबतक calling the
 * रेजिस्टरed fcoe transport's destroy function.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_transport_destroy(स्थिर अक्षर *buffer,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buffer);
	अगर (!netdev) अणु
		LIBFCOE_TRANSPORT_DBG("invalid device %s.\n", buffer);
		जाओ out_nodev;
	पूर्ण

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (!ft) अणु
		LIBFCOE_TRANSPORT_DBG("no FCoE transport found for %s.\n",
				      netdev->name);
		जाओ out_putdev;
	पूर्ण

	/* pass to transport destroy */
	rc = ft->destroy ? ft->destroy(netdev) : -ENODEV;
	fcoe_del_netdev_mapping(netdev);
	LIBFCOE_TRANSPORT_DBG("transport %s %s to destroy fcoe on %s.\n",
			      ft->name, (rc) ? "failed" : "succeeded",
			      netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_transport_disable() - Disables a FCoE पूर्णांकerface
 * @buffer: The name of the Ethernet पूर्णांकerface to be disabled
 * @kp:	    The associated kernel parameter
 *
 * Called from sysfs.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_transport_disable(स्थिर अक्षर *buffer,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buffer);
	अगर (!netdev)
		जाओ out_nodev;

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (!ft)
		जाओ out_putdev;

	rc = ft->disable ? ft->disable(netdev) : -ENODEV;

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_transport_enable() - Enables a FCoE पूर्णांकerface
 * @buffer: The name of the Ethernet पूर्णांकerface to be enabled
 * @kp:     The associated kernel parameter
 *
 * Called from sysfs.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_transport_enable(स्थिर अक्षर *buffer,
				 स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा fcoe_transport *ft = शून्य;

	mutex_lock(&ft_mutex);

	netdev = fcoe_अगर_to_netdev(buffer);
	अगर (!netdev)
		जाओ out_nodev;

	ft = fcoe_netdev_map_lookup(netdev);
	अगर (!ft)
		जाओ out_putdev;

	rc = ft->enable ? ft->enable(netdev) : -ENODEV;

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unlock(&ft_mutex);
	वापस rc;
पूर्ण

/**
 * libfcoe_init() - Initialization routine क्रम libfcoe.ko
 */
अटल पूर्णांक __init libfcoe_init(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = fcoe_transport_init();
	अगर (rc)
		वापस rc;

	rc = fcoe_sysfs_setup();
	अगर (rc)
		fcoe_transport_निकास();

	वापस rc;
पूर्ण
module_init(libfcoe_init);

/**
 * libfcoe_निकास() - Tear करोwn libfcoe.ko
 */
अटल व्योम __निकास libfcoe_निकास(व्योम)
अणु
	fcoe_sysfs_tearकरोwn();
	fcoe_transport_निकास();
पूर्ण
module_निकास(libfcoe_निकास);
