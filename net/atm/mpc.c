<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/seq_file.h>

/* We are an ethernet device */
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/sock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/checksum.h>   /* क्रम ip_fast_csum() */
#समावेश <net/arp.h>
#समावेश <net/dst.h>
#समावेश <linux/proc_fs.h>

/* And aपंचांग device */
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगlec.h>
#समावेश <linux/aपंचांगmpc.h>
/* Modular too */
#समावेश <linux/module.h>

#समावेश "lec.h"
#समावेश "mpc.h"
#समावेश "resources.h"

/*
 * mpc.c: Implementation of MPOA client kernel part
 */

#अगर 0
#घोषणा dprपूर्णांकk(क्रमmat, args...) \
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __func__, ##args)
#घोषणा dprपूर्णांकk_cont(क्रमmat, args...) prपूर्णांकk(KERN_CONT क्रमmat, ##args)
#अन्यथा
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __func__, ##args);\
	पूर्ण जबतक (0)
#घोषणा dprपूर्णांकk_cont(क्रमmat, args...)			\
	करो अणु अगर (0) prपूर्णांकk(KERN_CONT क्रमmat, ##args); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर 0
#घोषणा ddprपूर्णांकk(क्रमmat, args...) \
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __func__, ##args)
#घोषणा ddprपूर्णांकk_cont(क्रमmat, args...) prपूर्णांकk(KERN_CONT क्रमmat, ##args)
#अन्यथा
#घोषणा ddprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __func__, ##args);\
	पूर्ण जबतक (0)
#घोषणा ddprपूर्णांकk_cont(क्रमmat, args...)			\
	करो अणु अगर (0) prपूर्णांकk(KERN_CONT क्रमmat, ##args); पूर्ण जबतक (0)
#पूर्ण_अगर

/* mpc_daemon -> kernel */
अटल व्योम MPOA_trigger_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);
अटल व्योम MPOA_res_reply_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);
अटल व्योम ingress_purge_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);
अटल व्योम egress_purge_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);
अटल व्योम mps_death(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);
अटल व्योम clean_up(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc,
		     पूर्णांक action);
अटल व्योम MPOA_cache_impos_rcvd(काष्ठा k_message *msg,
				  काष्ठा mpoa_client *mpc);
अटल व्योम set_mpc_ctrl_addr_rcvd(काष्ठा k_message *mesg,
				   काष्ठा mpoa_client *mpc);
अटल व्योम set_mps_mac_addr_rcvd(काष्ठा k_message *mesg,
				  काष्ठा mpoa_client *mpc);

अटल स्थिर uपूर्णांक8_t *copy_macs(काष्ठा mpoa_client *mpc,
				स्थिर uपूर्णांक8_t *router_mac,
				स्थिर uपूर्णांक8_t *tlvs, uपूर्णांक8_t mps_macs,
				uपूर्णांक8_t device_type);
अटल व्योम purge_egress_लघुcut(काष्ठा aपंचांग_vcc *vcc, eg_cache_entry *entry);

अटल व्योम send_set_mps_ctrl_addr(स्थिर अक्षर *addr, काष्ठा mpoa_client *mpc);
अटल व्योम mpoad_बंद(काष्ठा aपंचांग_vcc *vcc);
अटल पूर्णांक msg_from_mpoad(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);

अटल व्योम mpc_push(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल netdev_tx_t mpc_send_packet(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev);
अटल पूर्णांक mpoa_event_listener(काष्ठा notअगरier_block *mpoa_notअगरier,
			       अचिन्हित दीर्घ event, व्योम *dev);
अटल व्योम mpc_समयr_refresh(व्योम);
अटल व्योम mpc_cache_check(काष्ठा समयr_list *unused);

अटल काष्ठा llc_snap_hdr llc_snap_mpoa_ctrl = अणु
	0xaa, 0xaa, 0x03,
	अणु0x00, 0x00, 0x5eपूर्ण,
	अणु0x00, 0x03पूर्ण         /* For MPOA control PDUs */
पूर्ण;
अटल काष्ठा llc_snap_hdr llc_snap_mpoa_data = अणु
	0xaa, 0xaa, 0x03,
	अणु0x00, 0x00, 0x00पूर्ण,
	अणु0x08, 0x00पूर्ण         /* This is क्रम IP PDUs only */
पूर्ण;
अटल काष्ठा llc_snap_hdr llc_snap_mpoa_data_tagged = अणु
	0xaa, 0xaa, 0x03,
	अणु0x00, 0x00, 0x00पूर्ण,
	अणु0x88, 0x4cपूर्ण         /* This is क्रम tagged data PDUs */
पूर्ण;

अटल काष्ठा notअगरier_block mpoa_notअगरier = अणु
	mpoa_event_listener,
	शून्य,
	0
पूर्ण;

काष्ठा mpoa_client *mpcs = शून्य; /* FIXME */
अटल काष्ठा aपंचांग_mpoa_qos *qos_head = शून्य;
अटल DEFINE_TIMER(mpc_समयr, mpc_cache_check);


अटल काष्ठा mpoa_client *find_mpc_by_itfnum(पूर्णांक itf)
अणु
	काष्ठा mpoa_client *mpc;

	mpc = mpcs;  /* our global linked list */
	जबतक (mpc != शून्य) अणु
		अगर (mpc->dev_num == itf)
			वापस mpc;
		mpc = mpc->next;
	पूर्ण

	वापस शून्य;   /* not found */
पूर्ण

अटल काष्ठा mpoa_client *find_mpc_by_vcc(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा mpoa_client *mpc;

	mpc = mpcs;  /* our global linked list */
	जबतक (mpc != शून्य) अणु
		अगर (mpc->mpoad_vcc == vcc)
			वापस mpc;
		mpc = mpc->next;
	पूर्ण

	वापस शून्य;   /* not found */
पूर्ण

अटल काष्ठा mpoa_client *find_mpc_by_lec(काष्ठा net_device *dev)
अणु
	काष्ठा mpoa_client *mpc;

	mpc = mpcs;  /* our global linked list */
	जबतक (mpc != शून्य) अणु
		अगर (mpc->dev == dev)
			वापस mpc;
		mpc = mpc->next;
	पूर्ण

	वापस शून्य;   /* not found */
पूर्ण

/*
 * Functions क्रम managing QoS list
 */

/*
 * Overग_लिखोs the old entry or makes a new one.
 */
काष्ठा aपंचांग_mpoa_qos *aपंचांग_mpoa_add_qos(__be32 dst_ip, काष्ठा aपंचांग_qos *qos)
अणु
	काष्ठा aपंचांग_mpoa_qos *entry;

	entry = aपंचांग_mpoa_search_qos(dst_ip);
	अगर (entry != शून्य) अणु
		entry->qos = *qos;
		वापस entry;
	पूर्ण

	entry = kदो_स्मृति(माप(काष्ठा aपंचांग_mpoa_qos), GFP_KERNEL);
	अगर (entry == शून्य) अणु
		pr_info("mpoa: out of memory\n");
		वापस entry;
	पूर्ण

	entry->ipaddr = dst_ip;
	entry->qos = *qos;

	entry->next = qos_head;
	qos_head = entry;

	वापस entry;
पूर्ण

काष्ठा aपंचांग_mpoa_qos *aपंचांग_mpoa_search_qos(__be32 dst_ip)
अणु
	काष्ठा aपंचांग_mpoa_qos *qos;

	qos = qos_head;
	जबतक (qos) अणु
		अगर (qos->ipaddr == dst_ip)
			अवरोध;
		qos = qos->next;
	पूर्ण

	वापस qos;
पूर्ण

/*
 * Returns 0 क्रम failure
 */
पूर्णांक aपंचांग_mpoa_delete_qos(काष्ठा aपंचांग_mpoa_qos *entry)
अणु
	काष्ठा aपंचांग_mpoa_qos *curr;

	अगर (entry == शून्य)
		वापस 0;
	अगर (entry == qos_head) अणु
		qos_head = qos_head->next;
		kमुक्त(entry);
		वापस 1;
	पूर्ण

	curr = qos_head;
	जबतक (curr != शून्य) अणु
		अगर (curr->next == entry) अणु
			curr->next = entry->next;
			kमुक्त(entry);
			वापस 1;
		पूर्ण
		curr = curr->next;
	पूर्ण

	वापस 0;
पूर्ण

/* this is buggered - we need locking क्रम qos_head */
व्योम aपंचांग_mpoa_disp_qos(काष्ठा seq_file *m)
अणु
	काष्ठा aपंचांग_mpoa_qos *qos;

	qos = qos_head;
	seq_म_लिखो(m, "QoS entries for shortcuts:\n");
	seq_म_लिखो(m, "IP address\n  TX:max_pcr pcr     min_pcr max_cdv max_sdu\n  RX:max_pcr pcr     min_pcr max_cdv max_sdu\n");

	जबतक (qos != शून्य) अणु
		seq_म_लिखो(m, "%pI4\n     %-7d %-7d %-7d %-7d %-7d\n     %-7d %-7d %-7d %-7d %-7d\n",
			   &qos->ipaddr,
			   qos->qos.txtp.max_pcr,
			   qos->qos.txtp.pcr,
			   qos->qos.txtp.min_pcr,
			   qos->qos.txtp.max_cdv,
			   qos->qos.txtp.max_sdu,
			   qos->qos.rxtp.max_pcr,
			   qos->qos.rxtp.pcr,
			   qos->qos.rxtp.min_pcr,
			   qos->qos.rxtp.max_cdv,
			   qos->qos.rxtp.max_sdu);
		qos = qos->next;
	पूर्ण
पूर्ण

अटल काष्ठा net_device *find_lec_by_itfnum(पूर्णांक itf)
अणु
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];

	प्र_लिखो(name, "lec%d", itf);
	dev = dev_get_by_name(&init_net, name);

	वापस dev;
पूर्ण

अटल काष्ठा mpoa_client *alloc_mpc(व्योम)
अणु
	काष्ठा mpoa_client *mpc;

	mpc = kzalloc(माप(काष्ठा mpoa_client), GFP_KERNEL);
	अगर (mpc == शून्य)
		वापस शून्य;
	rwlock_init(&mpc->ingress_lock);
	rwlock_init(&mpc->egress_lock);
	mpc->next = mpcs;
	aपंचांग_mpoa_init_cache(mpc);

	mpc->parameters.mpc_p1 = MPC_P1;
	mpc->parameters.mpc_p2 = MPC_P2;
	स_रखो(mpc->parameters.mpc_p3, 0, माप(mpc->parameters.mpc_p3));
	mpc->parameters.mpc_p4 = MPC_P4;
	mpc->parameters.mpc_p5 = MPC_P5;
	mpc->parameters.mpc_p6 = MPC_P6;

	mpcs = mpc;

	वापस mpc;
पूर्ण

/*
 *
 * start_mpc() माला_दो the MPC on line. All the packets destined
 * to the lec underneath us are now being monitored and
 * लघुcuts will be established.
 *
 */
अटल व्योम start_mpc(काष्ठा mpoa_client *mpc, काष्ठा net_device *dev)
अणु

	dprपूर्णांकk("(%s)\n", mpc->dev->name);
	अगर (!dev->netdev_ops)
		pr_info("(%s) not starting\n", dev->name);
	अन्यथा अणु
		mpc->old_ops = dev->netdev_ops;
		mpc->new_ops = *mpc->old_ops;
		mpc->new_ops.nकरो_start_xmit = mpc_send_packet;
		dev->netdev_ops = &mpc->new_ops;
	पूर्ण
पूर्ण

अटल व्योम stop_mpc(काष्ठा mpoa_client *mpc)
अणु
	काष्ठा net_device *dev = mpc->dev;
	dprपूर्णांकk("(%s)", mpc->dev->name);

	/* Lets not nullअगरy lec device's dev->hard_start_xmit */
	अगर (dev->netdev_ops != &mpc->new_ops) अणु
		dprपूर्णांकk_cont(" mpc already stopped, not fatal\n");
		वापस;
	पूर्ण
	dprपूर्णांकk_cont("\n");

	dev->netdev_ops = mpc->old_ops;
	mpc->old_ops = शून्य;

	/* बंद_लघुcuts(mpc);    ??? FIXME */
पूर्ण

अटल स्थिर अक्षर *mpoa_device_type_string(अक्षर type) __attribute__ ((unused));

अटल स्थिर अक्षर *mpoa_device_type_string(अक्षर type)
अणु
	चयन (type) अणु
	हाल NON_MPOA:
		वापस "non-MPOA device";
	हाल MPS:
		वापस "MPS";
	हाल MPC:
		वापस "MPC";
	हाल MPS_AND_MPC:
		वापस "both MPS and MPC";
	पूर्ण

	वापस "unspecified (non-MPOA) device";
पूर्ण

/*
 * lec device calls this via its netdev_priv(dev)->lane2_ops
 * ->associate_indicator() when it sees a TLV in LE_ARP packet.
 * We fill in the poपूर्णांकer above when we see a LANE2 lec initializing
 * See LANE2 spec 3.1.5
 *
 * Quite a big and ugly function but when you look at it
 * all it करोes is to try to locate and parse MPOA Device
 * Type TLV.
 * We give our lec a poपूर्णांकer to this function and when the
 * lec sees a TLV it uses the poपूर्णांकer to call this function.
 *
 */
अटल व्योम lane2_assoc_ind(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			    स्थिर u8 *tlvs, u32 मापtlvs)
अणु
	uपूर्णांक32_t type;
	uपूर्णांक8_t length, mpoa_device_type, number_of_mps_macs;
	स्थिर uपूर्णांक8_t *end_of_tlvs;
	काष्ठा mpoa_client *mpc;

	mpoa_device_type = number_of_mps_macs = 0; /* silence gcc */
	dprपूर्णांकk("(%s) received TLV(s), ", dev->name);
	dprपूर्णांकk("total length of all TLVs %d\n", मापtlvs);
	mpc = find_mpc_by_lec(dev); /* Sampo-Fix: moved here from below */
	अगर (mpc == शून्य) अणु
		pr_info("(%s) no mpc\n", dev->name);
		वापस;
	पूर्ण
	end_of_tlvs = tlvs + मापtlvs;
	जबतक (end_of_tlvs - tlvs >= 5) अणु
		type = ((tlvs[0] << 24) | (tlvs[1] << 16) |
			(tlvs[2] << 8) | tlvs[3]);
		length = tlvs[4];
		tlvs += 5;
		dprपूर्णांकk("    type 0x%x length %02x\n", type, length);
		अगर (tlvs + length > end_of_tlvs) अणु
			pr_info("TLV value extends past its buffer, aborting parse\n");
			वापस;
		पूर्ण

		अगर (type == 0) अणु
			pr_info("mpoa: (%s) TLV type was 0, returning\n",
				dev->name);
			वापस;
		पूर्ण

		अगर (type != TLV_MPOA_DEVICE_TYPE) अणु
			tlvs += length;
			जारी;  /* skip other TLVs */
		पूर्ण
		mpoa_device_type = *tlvs++;
		number_of_mps_macs = *tlvs++;
		dprपूर्णांकk("(%s) MPOA device type '%s', ",
			dev->name, mpoa_device_type_string(mpoa_device_type));
		अगर (mpoa_device_type == MPS_AND_MPC &&
		    length < (42 + number_of_mps_macs*ETH_ALEN)) अणु /* :) */
			pr_info("(%s) short MPOA Device Type TLV\n",
				dev->name);
			जारी;
		पूर्ण
		अगर ((mpoa_device_type == MPS || mpoa_device_type == MPC) &&
		    length < 22 + number_of_mps_macs*ETH_ALEN) अणु
			pr_info("(%s) short MPOA Device Type TLV\n", dev->name);
			जारी;
		पूर्ण
		अगर (mpoa_device_type != MPS &&
		    mpoa_device_type != MPS_AND_MPC) अणु
			dprपूर्णांकk("ignoring non-MPS device ");
			अगर (mpoa_device_type == MPC)
				tlvs += 20;
			जारी;  /* we are only पूर्णांकerested in MPSs */
		पूर्ण
		अगर (number_of_mps_macs == 0 &&
		    mpoa_device_type == MPS_AND_MPC) अणु
			pr_info("(%s) MPS_AND_MPC has zero MACs\n", dev->name);
			जारी;  /* someone should पढ़ो the spec */
		पूर्ण
		dprपूर्णांकk_cont("this MPS has %d MAC addresses\n",
			     number_of_mps_macs);

		/*
		 * ok, now we can go and tell our daemon
		 * the control address of MPS
		 */
		send_set_mps_ctrl_addr(tlvs, mpc);

		tlvs = copy_macs(mpc, mac_addr, tlvs,
				 number_of_mps_macs, mpoa_device_type);
		अगर (tlvs == शून्य)
			वापस;
	पूर्ण
	अगर (end_of_tlvs - tlvs != 0)
		pr_info("(%s) ignoring %zd bytes of trailing TLV garbage\n",
			dev->name, end_of_tlvs - tlvs);
पूर्ण

/*
 * Store at least advertizing router's MAC address
 * plus the possible MAC address(es) to mpc->mps_macs.
 * For a freshly allocated MPOA client mpc->mps_macs == 0.
 */
अटल स्थिर uपूर्णांक8_t *copy_macs(काष्ठा mpoa_client *mpc,
				स्थिर uपूर्णांक8_t *router_mac,
				स्थिर uपूर्णांक8_t *tlvs, uपूर्णांक8_t mps_macs,
				uपूर्णांक8_t device_type)
अणु
	पूर्णांक num_macs;
	num_macs = (mps_macs > 1) ? mps_macs : 1;

	अगर (mpc->number_of_mps_macs != num_macs) अणु /* need to पुनः_स्मृतिate? */
		अगर (mpc->number_of_mps_macs != 0)
			kमुक्त(mpc->mps_macs);
		mpc->number_of_mps_macs = 0;
		mpc->mps_macs = kदो_स्मृति_array(ETH_ALEN, num_macs, GFP_KERNEL);
		अगर (mpc->mps_macs == शून्य) अणु
			pr_info("(%s) out of mem\n", mpc->dev->name);
			वापस शून्य;
		पूर्ण
	पूर्ण
	ether_addr_copy(mpc->mps_macs, router_mac);
	tlvs += 20; अगर (device_type == MPS_AND_MPC) tlvs += 20;
	अगर (mps_macs > 0)
		स_नकल(mpc->mps_macs, tlvs, mps_macs*ETH_ALEN);
	tlvs += mps_macs*ETH_ALEN;
	mpc->number_of_mps_macs = num_macs;

	वापस tlvs;
पूर्ण

अटल पूर्णांक send_via_लघुcut(काष्ठा sk_buff *skb, काष्ठा mpoa_client *mpc)
अणु
	in_cache_entry *entry;
	काष्ठा iphdr *iph;
	अक्षर *buff;
	__be32 ipaddr = 0;

	अटल काष्ठा अणु
		काष्ठा llc_snap_hdr hdr;
		__be32 tag;
	पूर्ण tagged_llc_snap_hdr = अणु
		अणु0xaa, 0xaa, 0x03, अणु0x00, 0x00, 0x00पूर्ण, अणु0x88, 0x4cपूर्णपूर्ण,
		0
	पूर्ण;

	buff = skb->data + mpc->dev->hard_header_len;
	iph = (काष्ठा iphdr *)buff;
	ipaddr = iph->daddr;

	ddprपूर्णांकk("(%s) ipaddr 0x%x\n",
		 mpc->dev->name, ipaddr);

	entry = mpc->in_ops->get(ipaddr, mpc);
	अगर (entry == शून्य) अणु
		entry = mpc->in_ops->add_entry(ipaddr, mpc);
		अगर (entry != शून्य)
			mpc->in_ops->put(entry);
		वापस 1;
	पूर्ण
	/* threshold not exceeded or VCC not पढ़ोy */
	अगर (mpc->in_ops->cache_hit(entry, mpc) != OPEN) अणु
		ddprपूर्णांकk("(%s) cache_hit: returns != OPEN\n",
			 mpc->dev->name);
		mpc->in_ops->put(entry);
		वापस 1;
	पूर्ण

	ddprपूर्णांकk("(%s) using shortcut\n",
		 mpc->dev->name);
	/* MPOA spec A.1.4, MPOA client must decrement IP ttl at least by one */
	अगर (iph->ttl <= 1) अणु
		ddprपूर्णांकk("(%s) IP ttl = %u, using LANE\n",
			 mpc->dev->name, iph->ttl);
		mpc->in_ops->put(entry);
		वापस 1;
	पूर्ण
	iph->ttl--;
	iph->check = 0;
	iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);

	अगर (entry->ctrl_info.tag != 0) अणु
		ddprपूर्णांकk("(%s) adding tag 0x%x\n",
			 mpc->dev->name, entry->ctrl_info.tag);
		tagged_llc_snap_hdr.tag = entry->ctrl_info.tag;
		skb_pull(skb, ETH_HLEN);	/* get rid of Eth header */
		skb_push(skb, माप(tagged_llc_snap_hdr));
						/* add LLC/SNAP header   */
		skb_copy_to_linear_data(skb, &tagged_llc_snap_hdr,
					माप(tagged_llc_snap_hdr));
	पूर्ण अन्यथा अणु
		skb_pull(skb, ETH_HLEN);	/* get rid of Eth header */
		skb_push(skb, माप(काष्ठा llc_snap_hdr));
						/* add LLC/SNAP header + tag  */
		skb_copy_to_linear_data(skb, &llc_snap_mpoa_data,
					माप(काष्ठा llc_snap_hdr));
	पूर्ण

	aपंचांग_account_tx(entry->लघुcut, skb);
	entry->लघुcut->send(entry->लघुcut, skb);
	entry->packets_fwded++;
	mpc->in_ops->put(entry);

	वापस 0;
पूर्ण

/*
 * Probably needs some error checks and locking, not sure...
 */
अटल netdev_tx_t mpc_send_packet(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा mpoa_client *mpc;
	काष्ठा ethhdr *eth;
	पूर्णांक i = 0;

	mpc = find_mpc_by_lec(dev); /* this should NEVER fail */
	अगर (mpc == शून्य) अणु
		pr_info("(%s) no MPC found\n", dev->name);
		जाओ non_ip;
	पूर्ण

	eth = (काष्ठा ethhdr *)skb->data;
	अगर (eth->h_proto != htons(ETH_P_IP))
		जाओ non_ip; /* Multi-Protocol Over ATM :-) */

	/* Weed out funny packets (e.g., AF_PACKET or raw). */
	अगर (skb->len < ETH_HLEN + माप(काष्ठा iphdr))
		जाओ non_ip;
	skb_set_network_header(skb, ETH_HLEN);
	अगर (skb->len < ETH_HLEN + ip_hdr(skb)->ihl * 4 || ip_hdr(skb)->ihl < 5)
		जाओ non_ip;

	जबतक (i < mpc->number_of_mps_macs) अणु
		अगर (ether_addr_equal(eth->h_dest, mpc->mps_macs + i * ETH_ALEN))
			अगर (send_via_लघुcut(skb, mpc) == 0) /* try लघुcut */
				वापस NETDEV_TX_OK;
		i++;
	पूर्ण

non_ip:
	वापस __netdev_start_xmit(mpc->old_ops, skb, dev, false);
पूर्ण

अटल पूर्णांक aपंचांग_mpoa_vcc_attach(काष्ठा aपंचांग_vcc *vcc, व्योम __user *arg)
अणु
	पूर्णांक bytes_left;
	काष्ठा mpoa_client *mpc;
	काष्ठा aपंचांगmpc_ioc ioc_data;
	in_cache_entry *in_entry;
	__be32  ipaddr;

	bytes_left = copy_from_user(&ioc_data, arg, माप(काष्ठा aपंचांगmpc_ioc));
	अगर (bytes_left != 0) अणु
		pr_info("mpoa:Short read (missed %d bytes) from userland\n",
			bytes_left);
		वापस -EFAULT;
	पूर्ण
	ipaddr = ioc_data.ipaddr;
	अगर (ioc_data.dev_num < 0 || ioc_data.dev_num >= MAX_LEC_ITF)
		वापस -EINVAL;

	mpc = find_mpc_by_itfnum(ioc_data.dev_num);
	अगर (mpc == शून्य)
		वापस -EINVAL;

	अगर (ioc_data.type == MPC_SOCKET_INGRESS) अणु
		in_entry = mpc->in_ops->get(ipaddr, mpc);
		अगर (in_entry == शून्य ||
		    in_entry->entry_state < INGRESS_RESOLVED) अणु
			pr_info("(%s) did not find RESOLVED entry from ingress cache\n",
				mpc->dev->name);
			अगर (in_entry != शून्य)
				mpc->in_ops->put(in_entry);
			वापस -EINVAL;
		पूर्ण
		pr_info("(%s) attaching ingress SVC, entry = %pI4\n",
			mpc->dev->name, &in_entry->ctrl_info.in_dst_ip);
		in_entry->लघुcut = vcc;
		mpc->in_ops->put(in_entry);
	पूर्ण अन्यथा अणु
		pr_info("(%s) attaching egress SVC\n", mpc->dev->name);
	पूर्ण

	vcc->proto_data = mpc->dev;
	vcc->push = mpc_push;

	वापस 0;
पूर्ण

/*
 *
 */
अटल व्योम mpc_vcc_बंद(काष्ठा aपंचांग_vcc *vcc, काष्ठा net_device *dev)
अणु
	काष्ठा mpoa_client *mpc;
	in_cache_entry *in_entry;
	eg_cache_entry *eg_entry;

	mpc = find_mpc_by_lec(dev);
	अगर (mpc == शून्य) अणु
		pr_info("(%s) close for unknown MPC\n", dev->name);
		वापस;
	पूर्ण

	dprपूर्णांकk("(%s)\n", dev->name);
	in_entry = mpc->in_ops->get_by_vcc(vcc, mpc);
	अगर (in_entry) अणु
		dprपूर्णांकk("(%s) ingress SVC closed ip = %pI4\n",
			mpc->dev->name, &in_entry->ctrl_info.in_dst_ip);
		in_entry->लघुcut = शून्य;
		mpc->in_ops->put(in_entry);
	पूर्ण
	eg_entry = mpc->eg_ops->get_by_vcc(vcc, mpc);
	अगर (eg_entry) अणु
		dprपूर्णांकk("(%s) egress SVC closed\n", mpc->dev->name);
		eg_entry->लघुcut = शून्य;
		mpc->eg_ops->put(eg_entry);
	पूर्ण

	अगर (in_entry == शून्य && eg_entry == शून्य)
		dprपूर्णांकk("(%s) unused vcc closed\n", dev->name);
पूर्ण

अटल व्योम mpc_push(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)vcc->proto_data;
	काष्ठा sk_buff *new_skb;
	eg_cache_entry *eg;
	काष्ठा mpoa_client *mpc;
	__be32 tag;
	अक्षर *पंचांगp;

	ddprपूर्णांकk("(%s)\n", dev->name);
	अगर (skb == शून्य) अणु
		dprपूर्णांकk("(%s) null skb, closing VCC\n", dev->name);
		mpc_vcc_बंद(vcc, dev);
		वापस;
	पूर्ण

	skb->dev = dev;
	अगर (स_भेद(skb->data, &llc_snap_mpoa_ctrl,
		   माप(काष्ठा llc_snap_hdr)) == 0) अणु
		काष्ठा sock *sk = sk_aपंचांग(vcc);

		dprपूर्णांकk("(%s) control packet arrived\n", dev->name);
		/* Pass control packets to daemon */
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_पढ़ोy(sk);
		वापस;
	पूर्ण

	/* data coming over the लघुcut */
	aपंचांग_वापस(vcc, skb->truesize);

	mpc = find_mpc_by_lec(dev);
	अगर (mpc == शून्य) अणु
		pr_info("(%s) unknown MPC\n", dev->name);
		वापस;
	पूर्ण

	अगर (स_भेद(skb->data, &llc_snap_mpoa_data_tagged,
		   माप(काष्ठा llc_snap_hdr)) == 0) अणु /* MPOA tagged data */
		ddprपूर्णांकk("(%s) tagged data packet arrived\n", dev->name);

	पूर्ण अन्यथा अगर (स_भेद(skb->data, &llc_snap_mpoa_data,
			  माप(काष्ठा llc_snap_hdr)) == 0) अणु /* MPOA data */
		pr_info("(%s) Unsupported non-tagged data packet arrived.  Purging\n",
			dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण अन्यथा अणु
		pr_info("(%s) garbage arrived, purging\n", dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	पंचांगp = skb->data + माप(काष्ठा llc_snap_hdr);
	tag = *(__be32 *)पंचांगp;

	eg = mpc->eg_ops->get_by_tag(tag, mpc);
	अगर (eg == शून्य) अणु
		pr_info("mpoa: (%s) Didn't find egress cache entry, tag = %u\n",
			dev->name, tag);
		purge_egress_लघुcut(vcc, शून्य);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	/*
	 * See अगर ingress MPC is using लघुcut we खोलोed as a वापस channel.
	 * This means we have a bi-directional vcc खोलोed by us.
	 */
	अगर (eg->लघुcut == शून्य) अणु
		eg->लघुcut = vcc;
		pr_info("(%s) egress SVC in use\n", dev->name);
	पूर्ण

	skb_pull(skb, माप(काष्ठा llc_snap_hdr) + माप(tag));
					/* get rid of LLC/SNAP header */
	new_skb = skb_पुनः_स्मृति_headroom(skb, eg->ctrl_info.DH_length);
					/* LLC/SNAP is लघुer than MAC header :( */
	dev_kमुक्त_skb_any(skb);
	अगर (new_skb == शून्य) अणु
		mpc->eg_ops->put(eg);
		वापस;
	पूर्ण
	skb_push(new_skb, eg->ctrl_info.DH_length);     /* add MAC header */
	skb_copy_to_linear_data(new_skb, eg->ctrl_info.DLL_header,
				eg->ctrl_info.DH_length);
	new_skb->protocol = eth_type_trans(new_skb, dev);
	skb_reset_network_header(new_skb);

	eg->latest_ip_addr = ip_hdr(new_skb)->saddr;
	eg->packets_rcvd++;
	mpc->eg_ops->put(eg);

	स_रखो(ATM_SKB(new_skb), 0, माप(काष्ठा aपंचांग_skb_data));
	netअगर_rx(new_skb);
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops mpc_ops = अणु /* only send is required */
	.बंद	= mpoad_बंद,
	.send	= msg_from_mpoad
पूर्ण;

अटल काष्ठा aपंचांग_dev mpc_dev = अणु
	.ops	= &mpc_ops,
	.type	= "mpc",
	.number	= 42,
	.lock	= __SPIN_LOCK_UNLOCKED(mpc_dev.lock)
	/* members not explicitly initialised will be 0 */
पूर्ण;

अटल पूर्णांक aपंचांग_mpoa_mpoad_attach(काष्ठा aपंचांग_vcc *vcc, पूर्णांक arg)
अणु
	काष्ठा mpoa_client *mpc;
	काष्ठा lec_priv *priv;
	पूर्णांक err;

	अगर (mpcs == शून्य) अणु
		mpc_समयr_refresh();

		/* This lets us now how our LECs are करोing */
		err = रेजिस्टर_netdevice_notअगरier(&mpoa_notअगरier);
		अगर (err < 0) अणु
			del_समयr(&mpc_समयr);
			वापस err;
		पूर्ण
	पूर्ण

	mpc = find_mpc_by_itfnum(arg);
	अगर (mpc == शून्य) अणु
		dprपूर्णांकk("allocating new mpc for itf %d\n", arg);
		mpc = alloc_mpc();
		अगर (mpc == शून्य)
			वापस -ENOMEM;
		mpc->dev_num = arg;
		mpc->dev = find_lec_by_itfnum(arg);
					/* शून्य अगर there was no lec */
	पूर्ण
	अगर (mpc->mpoad_vcc) अणु
		pr_info("mpoad is already present for itf %d\n", arg);
		वापस -EADDRINUSE;
	पूर्ण

	अगर (mpc->dev) अणु /* check अगर the lec is LANE2 capable */
		priv = netdev_priv(mpc->dev);
		अगर (priv->lane_version < 2) अणु
			dev_put(mpc->dev);
			mpc->dev = शून्य;
		पूर्ण अन्यथा
			priv->lane2_ops->associate_indicator = lane2_assoc_ind;
	पूर्ण

	mpc->mpoad_vcc = vcc;
	vcc->dev = &mpc_dev;
	vcc_insert_socket(sk_aपंचांग(vcc));
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	अगर (mpc->dev) अणु
		अक्षर empty[ATM_ESA_LEN];
		स_रखो(empty, 0, ATM_ESA_LEN);

		start_mpc(mpc, mpc->dev);
		/* set address अगर mpcd e.g. माला_लो समाप्तed and restarted.
		 * If we करो not करो it now we have to रुको क्रम the next LE_ARP
		 */
		अगर (स_भेद(mpc->mps_ctrl_addr, empty, ATM_ESA_LEN) != 0)
			send_set_mps_ctrl_addr(mpc->mps_ctrl_addr, mpc);
	पूर्ण

	__module_get(THIS_MODULE);
	वापस arg;
पूर्ण

अटल व्योम send_set_mps_ctrl_addr(स्थिर अक्षर *addr, काष्ठा mpoa_client *mpc)
अणु
	काष्ठा k_message mesg;

	स_नकल(mpc->mps_ctrl_addr, addr, ATM_ESA_LEN);

	mesg.type = SET_MPS_CTRL_ADDR;
	स_नकल(mesg.MPS_ctrl, addr, ATM_ESA_LEN);
	msg_to_mpoad(&mesg, mpc);
पूर्ण

अटल व्योम mpoad_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा mpoa_client *mpc;
	काष्ठा sk_buff *skb;

	mpc = find_mpc_by_vcc(vcc);
	अगर (mpc == शून्य) अणु
		pr_info("did not find MPC\n");
		वापस;
	पूर्ण
	अगर (!mpc->mpoad_vcc) अणु
		pr_info("close for non-present mpoad\n");
		वापस;
	पूर्ण

	mpc->mpoad_vcc = शून्य;
	अगर (mpc->dev) अणु
		काष्ठा lec_priv *priv = netdev_priv(mpc->dev);
		priv->lane2_ops->associate_indicator = शून्य;
		stop_mpc(mpc);
		dev_put(mpc->dev);
	पूर्ण

	mpc->in_ops->destroy_cache(mpc);
	mpc->eg_ops->destroy_cache(mpc);

	जबतक ((skb = skb_dequeue(&sk_aपंचांग(vcc)->sk_receive_queue))) अणु
		aपंचांग_वापस(vcc, skb->truesize);
		kमुक्त_skb(skb);
	पूर्ण

	pr_info("(%s) going down\n",
		(mpc->dev) ? mpc->dev->name : "<unknown>");
	module_put(THIS_MODULE);
पूर्ण

/*
 *
 */
अटल पूर्णांक msg_from_mpoad(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु

	काष्ठा mpoa_client *mpc = find_mpc_by_vcc(vcc);
	काष्ठा k_message *mesg = (काष्ठा k_message *)skb->data;
	WARN_ON(refcount_sub_and_test(skb->truesize, &sk_aपंचांग(vcc)->sk_wmem_alloc));

	अगर (mpc == शून्य) अणु
		pr_info("no mpc found\n");
		वापस 0;
	पूर्ण
	dprपूर्णांकk("(%s)", mpc->dev ? mpc->dev->name : "<unknown>");
	चयन (mesg->type) अणु
	हाल MPOA_RES_REPLY_RCVD:
		dprपूर्णांकk_cont("mpoa_res_reply_rcvd\n");
		MPOA_res_reply_rcvd(mesg, mpc);
		अवरोध;
	हाल MPOA_TRIGGER_RCVD:
		dprपूर्णांकk_cont("mpoa_trigger_rcvd\n");
		MPOA_trigger_rcvd(mesg, mpc);
		अवरोध;
	हाल INGRESS_PURGE_RCVD:
		dprपूर्णांकk_cont("nhrp_purge_rcvd\n");
		ingress_purge_rcvd(mesg, mpc);
		अवरोध;
	हाल EGRESS_PURGE_RCVD:
		dprपूर्णांकk_cont("egress_purge_reply_rcvd\n");
		egress_purge_rcvd(mesg, mpc);
		अवरोध;
	हाल MPS_DEATH:
		dprपूर्णांकk_cont("mps_death\n");
		mps_death(mesg, mpc);
		अवरोध;
	हाल CACHE_IMPOS_RCVD:
		dprपूर्णांकk_cont("cache_impos_rcvd\n");
		MPOA_cache_impos_rcvd(mesg, mpc);
		अवरोध;
	हाल SET_MPC_CTRL_ADDR:
		dprपूर्णांकk_cont("set_mpc_ctrl_addr\n");
		set_mpc_ctrl_addr_rcvd(mesg, mpc);
		अवरोध;
	हाल SET_MPS_MAC_ADDR:
		dprपूर्णांकk_cont("set_mps_mac_addr\n");
		set_mps_mac_addr_rcvd(mesg, mpc);
		अवरोध;
	हाल CLEAN_UP_AND_EXIT:
		dprपूर्णांकk_cont("clean_up_and_exit\n");
		clean_up(mesg, mpc, DIE);
		अवरोध;
	हाल RELOAD:
		dprपूर्णांकk_cont("reload\n");
		clean_up(mesg, mpc, RELOAD);
		अवरोध;
	हाल SET_MPC_PARAMS:
		dprपूर्णांकk_cont("set_mpc_params\n");
		mpc->parameters = mesg->content.params;
		अवरोध;
	शेष:
		dprपूर्णांकk_cont("unknown message %d\n", mesg->type);
		अवरोध;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

/* Remember that this function may not करो things that sleep */
पूर्णांक msg_to_mpoad(काष्ठा k_message *mesg, काष्ठा mpoa_client *mpc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;

	अगर (mpc == शून्य || !mpc->mpoad_vcc) अणु
		pr_info("mesg %d to a non-existent mpoad\n", mesg->type);
		वापस -ENXIO;
	पूर्ण

	skb = alloc_skb(माप(काष्ठा k_message), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;
	skb_put(skb, माप(काष्ठा k_message));
	skb_copy_to_linear_data(skb, mesg, माप(*mesg));
	aपंचांग_क्रमce_अक्षरge(mpc->mpoad_vcc, skb->truesize);

	sk = sk_aपंचांग(mpc->mpoad_vcc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक mpoa_event_listener(काष्ठा notअगरier_block *mpoa_notअगरier,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा mpoa_client *mpc;
	काष्ठा lec_priv *priv;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (म_भेदन(dev->name, "lec", 3))
		वापस NOTIFY_DONE; /* we are only पूर्णांकerested in lec:s */

	चयन (event) अणु
	हाल NETDEV_REGISTER:       /* a new lec device was allocated */
		priv = netdev_priv(dev);
		अगर (priv->lane_version < 2)
			अवरोध;
		priv->lane2_ops->associate_indicator = lane2_assoc_ind;
		mpc = find_mpc_by_itfnum(priv->itfnum);
		अगर (mpc == शून्य) अणु
			dprपूर्णांकk("allocating new mpc for %s\n", dev->name);
			mpc = alloc_mpc();
			अगर (mpc == शून्य) अणु
				pr_info("no new mpc");
				अवरोध;
			पूर्ण
		पूर्ण
		mpc->dev_num = priv->itfnum;
		mpc->dev = dev;
		dev_hold(dev);
		dprपूर्णांकk("(%s) was initialized\n", dev->name);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* the lec device was deallocated */
		mpc = find_mpc_by_lec(dev);
		अगर (mpc == शून्य)
			अवरोध;
		dprपूर्णांकk("device (%s) was deallocated\n", dev->name);
		stop_mpc(mpc);
		dev_put(mpc->dev);
		mpc->dev = शून्य;
		अवरोध;
	हाल NETDEV_UP:
		/* the dev was अगरconfig'ed up */
		mpc = find_mpc_by_lec(dev);
		अगर (mpc == शून्य)
			अवरोध;
		अगर (mpc->mpoad_vcc != शून्य)
			start_mpc(mpc, dev);
		अवरोध;
	हाल NETDEV_DOWN:
		/* the dev was अगरconfig'ed करोwn */
		/* this means that the flow of packets from the
		 * upper layer stops
		 */
		mpc = find_mpc_by_lec(dev);
		अगर (mpc == शून्य)
			अवरोध;
		अगर (mpc->mpoad_vcc != शून्य)
			stop_mpc(mpc);
		अवरोध;
	हाल NETDEV_REBOOT:
	हाल NETDEV_CHANGE:
	हाल NETDEV_CHANGEMTU:
	हाल NETDEV_CHANGEADDR:
	हाल NETDEV_GOING_DOWN:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 * Functions which are called after a message is received from mpcd.
 * Msg is reused on purpose.
 */


अटल व्योम MPOA_trigger_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc)
अणु
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	in_cache_entry *entry;

	entry = mpc->in_ops->get(dst_ip, mpc);
	अगर (entry == शून्य) अणु
		entry = mpc->in_ops->add_entry(dst_ip, mpc);
		entry->entry_state = INGRESS_RESOLVING;
		msg->type = SND_MPOA_RES_RQST;
		msg->content.in_info = entry->ctrl_info;
		msg_to_mpoad(msg, mpc);
		entry->reply_रुको = kसमय_get_seconds();
		mpc->in_ops->put(entry);
		वापस;
	पूर्ण

	अगर (entry->entry_state == INGRESS_INVALID) अणु
		entry->entry_state = INGRESS_RESOLVING;
		msg->type = SND_MPOA_RES_RQST;
		msg->content.in_info = entry->ctrl_info;
		msg_to_mpoad(msg, mpc);
		entry->reply_रुको = kसमय_get_seconds();
		mpc->in_ops->put(entry);
		वापस;
	पूर्ण

	pr_info("(%s) entry already in resolving state\n",
		(mpc->dev) ? mpc->dev->name : "<unknown>");
	mpc->in_ops->put(entry);
पूर्ण

/*
 * Things get complicated because we have to check अगर there's an egress
 * लघुcut with suitable traffic parameters we could use.
 */
अटल व्योम check_qos_and_खोलो_लघुcut(काष्ठा k_message *msg,
					काष्ठा mpoa_client *client,
					in_cache_entry *entry)
अणु
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	काष्ठा aपंचांग_mpoa_qos *qos = aपंचांग_mpoa_search_qos(dst_ip);
	eg_cache_entry *eg_entry = client->eg_ops->get_by_src_ip(dst_ip, client);

	अगर (eg_entry && eg_entry->लघुcut) अणु
		अगर (eg_entry->लघुcut->qos.txtp.traffic_class &
		    msg->qos.txtp.traffic_class &
		    (qos ? qos->qos.txtp.traffic_class : ATM_UBR | ATM_CBR)) अणु
			अगर (eg_entry->लघुcut->qos.txtp.traffic_class == ATM_UBR)
				entry->लघुcut = eg_entry->लघुcut;
			अन्यथा अगर (eg_entry->लघुcut->qos.txtp.max_pcr > 0)
				entry->लघुcut = eg_entry->लघुcut;
		पूर्ण
		अगर (entry->लघुcut) अणु
			dprपूर्णांकk("(%s) using egress SVC to reach %pI4\n",
				client->dev->name, &dst_ip);
			client->eg_ops->put(eg_entry);
			वापस;
		पूर्ण
	पूर्ण
	अगर (eg_entry != शून्य)
		client->eg_ops->put(eg_entry);

	/* No luck in the egress cache we must खोलो an ingress SVC */
	msg->type = OPEN_INGRESS_SVC;
	अगर (qos &&
	    (qos->qos.txtp.traffic_class == msg->qos.txtp.traffic_class)) अणु
		msg->qos = qos->qos;
		pr_info("(%s) trying to get a CBR shortcut\n",
			client->dev->name);
	पूर्ण अन्यथा
		स_रखो(&msg->qos, 0, माप(काष्ठा aपंचांग_qos));
	msg_to_mpoad(msg, client);
पूर्ण

अटल व्योम MPOA_res_reply_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc)
अणु
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	in_cache_entry *entry = mpc->in_ops->get(dst_ip, mpc);

	dprपूर्णांकk("(%s) ip %pI4\n",
		mpc->dev->name, &dst_ip);
	ddprपूर्णांकk("(%s) entry = %p",
		 mpc->dev->name, entry);
	अगर (entry == शून्य) अणु
		pr_info("(%s) ARGH, received res. reply for an entry that doesn't exist.\n",
			mpc->dev->name);
		वापस;
	पूर्ण
	ddprपूर्णांकk_cont(" entry_state = %d ", entry->entry_state);

	अगर (entry->entry_state == INGRESS_RESOLVED) अणु
		pr_info("(%s) RESOLVED entry!\n", mpc->dev->name);
		mpc->in_ops->put(entry);
		वापस;
	पूर्ण

	entry->ctrl_info = msg->content.in_info;
	entry->समय = kसमय_get_seconds();
	/* Used in refreshing func from now on */
	entry->reply_रुको = kसमय_get_seconds();
	entry->refresh_समय = 0;
	ddprपूर्णांकk_cont("entry->shortcut = %p\n", entry->लघुcut);

	अगर (entry->entry_state == INGRESS_RESOLVING &&
	    entry->लघुcut != शून्य) अणु
		entry->entry_state = INGRESS_RESOLVED;
		mpc->in_ops->put(entry);
		वापस; /* Shortcut alपढ़ोy खोलो... */
	पूर्ण

	अगर (entry->लघुcut != शून्य) अणु
		pr_info("(%s) entry->shortcut != NULL, impossible!\n",
			mpc->dev->name);
		mpc->in_ops->put(entry);
		वापस;
	पूर्ण

	check_qos_and_खोलो_लघुcut(msg, mpc, entry);
	entry->entry_state = INGRESS_RESOLVED;
	mpc->in_ops->put(entry);

	वापस;

पूर्ण

अटल व्योम ingress_purge_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc)
अणु
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	__be32 mask = msg->ip_mask;
	in_cache_entry *entry = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);

	अगर (entry == शून्य) अणु
		pr_info("(%s) purge for a non-existing entry, ip = %pI4\n",
			mpc->dev->name, &dst_ip);
		वापस;
	पूर्ण

	करो अणु
		dprपूर्णांकk("(%s) removing an ingress entry, ip = %pI4\n",
			mpc->dev->name, &dst_ip);
		ग_लिखो_lock_bh(&mpc->ingress_lock);
		mpc->in_ops->हटाओ_entry(entry, mpc);
		ग_लिखो_unlock_bh(&mpc->ingress_lock);
		mpc->in_ops->put(entry);
		entry = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);
	पूर्ण जबतक (entry != शून्य);
पूर्ण

अटल व्योम egress_purge_rcvd(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc)
अणु
	__be32 cache_id = msg->content.eg_info.cache_id;
	eg_cache_entry *entry = mpc->eg_ops->get_by_cache_id(cache_id, mpc);

	अगर (entry == शून्य) अणु
		dprपूर्णांकk("(%s) purge for a non-existing entry\n",
			mpc->dev->name);
		वापस;
	पूर्ण

	ग_लिखो_lock_irq(&mpc->egress_lock);
	mpc->eg_ops->हटाओ_entry(entry, mpc);
	ग_लिखो_unlock_irq(&mpc->egress_lock);

	mpc->eg_ops->put(entry);
पूर्ण

अटल व्योम purge_egress_लघुcut(काष्ठा aपंचांग_vcc *vcc, eg_cache_entry *entry)
अणु
	काष्ठा sock *sk;
	काष्ठा k_message *purge_msg;
	काष्ठा sk_buff *skb;

	dprपूर्णांकk("entering\n");
	अगर (vcc == शून्य) अणु
		pr_info("vcc == NULL\n");
		वापस;
	पूर्ण

	skb = alloc_skb(माप(काष्ठा k_message), GFP_ATOMIC);
	अगर (skb == शून्य) अणु
		pr_info("out of memory\n");
		वापस;
	पूर्ण

	skb_put(skb, माप(काष्ठा k_message));
	स_रखो(skb->data, 0, माप(काष्ठा k_message));
	purge_msg = (काष्ठा k_message *)skb->data;
	purge_msg->type = DATA_PLANE_PURGE;
	अगर (entry != शून्य)
		purge_msg->content.eg_info = entry->ctrl_info;

	aपंचांग_क्रमce_अक्षरge(vcc, skb->truesize);

	sk = sk_aपंचांग(vcc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);
	dprपूर्णांकk("exiting\n");
पूर्ण

/*
 * Our MPS died. Tell our daemon to send NHRP data plane purge to each
 * of the egress लघुcuts we have.
 */
अटल व्योम mps_death(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc)
अणु
	eg_cache_entry *entry;

	dprपूर्णांकk("(%s)\n", mpc->dev->name);

	अगर (स_भेद(msg->MPS_ctrl, mpc->mps_ctrl_addr, ATM_ESA_LEN)) अणु
		pr_info("(%s) wrong MPS\n", mpc->dev->name);
		वापस;
	पूर्ण

	/* FIXME: This knows too much of the cache काष्ठाure */
	पढ़ो_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		purge_egress_लघुcut(entry->लघुcut, entry);
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irq(&mpc->egress_lock);

	mpc->in_ops->destroy_cache(mpc);
	mpc->eg_ops->destroy_cache(mpc);
पूर्ण

अटल व्योम MPOA_cache_impos_rcvd(काष्ठा k_message *msg,
				  काष्ठा mpoa_client *mpc)
अणु
	uपूर्णांक16_t holding_समय;
	eg_cache_entry *entry = mpc->eg_ops->get_by_cache_id(msg->content.eg_info.cache_id, mpc);

	holding_समय = msg->content.eg_info.holding_समय;
	dprपूर्णांकk("(%s) entry = %p, holding_time = %u\n",
		mpc->dev->name, entry, holding_समय);
	अगर (entry == शून्य && holding_समय) अणु
		entry = mpc->eg_ops->add_entry(msg, mpc);
		mpc->eg_ops->put(entry);
		वापस;
	पूर्ण
	अगर (holding_समय) अणु
		mpc->eg_ops->update(entry, holding_समय);
		वापस;
	पूर्ण

	ग_लिखो_lock_irq(&mpc->egress_lock);
	mpc->eg_ops->हटाओ_entry(entry, mpc);
	ग_लिखो_unlock_irq(&mpc->egress_lock);

	mpc->eg_ops->put(entry);
पूर्ण

अटल व्योम set_mpc_ctrl_addr_rcvd(काष्ठा k_message *mesg,
				   काष्ठा mpoa_client *mpc)
अणु
	काष्ठा lec_priv *priv;
	पूर्णांक i, retval ;

	uपूर्णांक8_t tlv[4 + 1 + 1 + 1 + ATM_ESA_LEN];

	tlv[0] = 00; tlv[1] = 0xa0; tlv[2] = 0x3e; tlv[3] = 0x2a; /* type  */
	tlv[4] = 1 + 1 + ATM_ESA_LEN;  /* length                           */
	tlv[5] = 0x02;                 /* MPOA client                      */
	tlv[6] = 0x00;                 /* number of MPS MAC addresses      */

	स_नकल(&tlv[7], mesg->MPS_ctrl, ATM_ESA_LEN); /* MPC ctrl ATM addr */
	स_नकल(mpc->our_ctrl_addr, mesg->MPS_ctrl, ATM_ESA_LEN);

	dprपूर्णांकk("(%s) setting MPC ctrl ATM address to",
		mpc->dev ? mpc->dev->name : "<unknown>");
	क्रम (i = 7; i < माप(tlv); i++)
		dprपूर्णांकk_cont(" %02x", tlv[i]);
	dprपूर्णांकk_cont("\n");

	अगर (mpc->dev) अणु
		priv = netdev_priv(mpc->dev);
		retval = priv->lane2_ops->associate_req(mpc->dev,
							mpc->dev->dev_addr,
							tlv, माप(tlv));
		अगर (retval == 0)
			pr_info("(%s) MPOA device type TLV association failed\n",
				mpc->dev->name);
		retval = priv->lane2_ops->resolve(mpc->dev, शून्य, 1, शून्य, शून्य);
		अगर (retval < 0)
			pr_info("(%s) targetless LE_ARP request failed\n",
				mpc->dev->name);
	पूर्ण
पूर्ण

अटल व्योम set_mps_mac_addr_rcvd(काष्ठा k_message *msg,
				  काष्ठा mpoa_client *client)
अणु

	अगर (client->number_of_mps_macs)
		kमुक्त(client->mps_macs);
	client->number_of_mps_macs = 0;
	client->mps_macs = kmemdup(msg->MPS_ctrl, ETH_ALEN, GFP_KERNEL);
	अगर (client->mps_macs == शून्य) अणु
		pr_info("out of memory\n");
		वापस;
	पूर्ण
	client->number_of_mps_macs = 1;
पूर्ण

/*
 * purge egress cache and tell daemon to 'action' (DIE, RELOAD)
 */
अटल व्योम clean_up(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc, पूर्णांक action)
अणु

	eg_cache_entry *entry;
	msg->type = SND_EGRESS_PURGE;


	/* FIXME: This knows too much of the cache काष्ठाure */
	पढ़ो_lock_irq(&mpc->egress_lock);
	entry = mpc->eg_cache;
	जबतक (entry != शून्य) अणु
		msg->content.eg_info = entry->ctrl_info;
		dprपूर्णांकk("cache_id %u\n", entry->ctrl_info.cache_id);
		msg_to_mpoad(msg, mpc);
		entry = entry->next;
	पूर्ण
	पढ़ो_unlock_irq(&mpc->egress_lock);

	msg->type = action;
	msg_to_mpoad(msg, mpc);
पूर्ण

अटल अचिन्हित दीर्घ checking_समय;

अटल व्योम mpc_समयr_refresh(व्योम)
अणु
	mpc_समयr.expires = jअगरfies + (MPC_P2 * HZ);
	checking_समय = mpc_समयr.expires;
	add_समयr(&mpc_समयr);
पूर्ण

अटल व्योम mpc_cache_check(काष्ठा समयr_list *unused)
अणु
	काष्ठा mpoa_client *mpc = mpcs;
	अटल अचिन्हित दीर्घ previous_resolving_check_समय;
	अटल अचिन्हित दीर्घ previous_refresh_समय;

	जबतक (mpc != शून्य) अणु
		mpc->in_ops->clear_count(mpc);
		mpc->eg_ops->clear_expired(mpc);
		अगर (checking_समय - previous_resolving_check_समय >
		    mpc->parameters.mpc_p4 * HZ) अणु
			mpc->in_ops->check_resolving(mpc);
			previous_resolving_check_समय = checking_समय;
		पूर्ण
		अगर (checking_समय - previous_refresh_समय >
		    mpc->parameters.mpc_p5 * HZ) अणु
			mpc->in_ops->refresh(mpc);
			previous_refresh_समय = checking_समय;
		पूर्ण
		mpc = mpc->next;
	पूर्ण
	mpc_समयr_refresh();
पूर्ण

अटल पूर्णांक aपंचांग_mpoa_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);

	अगर (cmd != ATMMPC_CTRL && cmd != ATMMPC_DATA)
		वापस -ENOIOCTLCMD;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल ATMMPC_CTRL:
		err = aपंचांग_mpoa_mpoad_attach(vcc, (पूर्णांक)arg);
		अगर (err >= 0)
			sock->state = SS_CONNECTED;
		अवरोध;
	हाल ATMMPC_DATA:
		err = aपंचांग_mpoa_vcc_attach(vcc, (व्योम __user *)arg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा aपंचांग_ioctl aपंचांग_ioctl_ops = अणु
	.owner	= THIS_MODULE,
	.ioctl	= aपंचांग_mpoa_ioctl,
पूर्ण;

अटल __init पूर्णांक aपंचांग_mpoa_init(व्योम)
अणु
	रेजिस्टर_aपंचांग_ioctl(&aपंचांग_ioctl_ops);

	अगर (mpc_proc_init() != 0)
		pr_info("failed to initialize /proc/mpoa\n");

	pr_info("mpc.c: initialized\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास aपंचांग_mpoa_cleanup(व्योम)
अणु
	काष्ठा mpoa_client *mpc, *पंचांगp;
	काष्ठा aपंचांग_mpoa_qos *qos, *nextqos;
	काष्ठा lec_priv *priv;

	mpc_proc_clean();

	del_समयr_sync(&mpc_समयr);
	unरेजिस्टर_netdevice_notअगरier(&mpoa_notअगरier);
	deरेजिस्टर_aपंचांग_ioctl(&aपंचांग_ioctl_ops);

	mpc = mpcs;
	mpcs = शून्य;
	जबतक (mpc != शून्य) अणु
		पंचांगp = mpc->next;
		अगर (mpc->dev != शून्य) अणु
			stop_mpc(mpc);
			priv = netdev_priv(mpc->dev);
			अगर (priv->lane2_ops != शून्य)
				priv->lane2_ops->associate_indicator = शून्य;
		पूर्ण
		ddprपूर्णांकk("about to clear caches\n");
		mpc->in_ops->destroy_cache(mpc);
		mpc->eg_ops->destroy_cache(mpc);
		ddprपूर्णांकk("caches cleared\n");
		kमुक्त(mpc->mps_macs);
		स_रखो(mpc, 0, माप(काष्ठा mpoa_client));
		ddprपूर्णांकk("about to kfree %p\n", mpc);
		kमुक्त(mpc);
		ddprपूर्णांकk("next mpc is at %p\n", पंचांगp);
		mpc = पंचांगp;
	पूर्ण

	qos = qos_head;
	qos_head = शून्य;
	जबतक (qos != शून्य) अणु
		nextqos = qos->next;
		dprपूर्णांकk("freeing qos entry %p\n", qos);
		kमुक्त(qos);
		qos = nextqos;
	पूर्ण
पूर्ण

module_init(aपंचांग_mpoa_init);
module_निकास(aपंचांग_mpoa_cleanup);

MODULE_LICENSE("GPL");
