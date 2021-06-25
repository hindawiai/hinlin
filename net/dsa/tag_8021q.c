<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 *
 * This module is not a complete tagger implementation. It only provides
 * primitives क्रम taggers that rely on 802.1Q VLAN tags to use. The
 * dsa_8021q_netdev_ops is रेजिस्टरed क्रम API compliance and not used
 * directly by callers.
 */
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dsa/8021q.h>

#समावेश "dsa_priv.h"

/* Binary काष्ठाure of the fake 12-bit VID field (when the TPID is
 * ETH_P_DSA_8021Q):
 *
 * | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +-----------+-----+-----------------+-----------+-----------------------+
 * |    सूची    | SVL |    SWITCH_ID    |  SUBVLAN  |          PORT         |
 * +-----------+-----+-----------------+-----------+-----------------------+
 *
 * सूची - VID[11:10]:
 *	Direction flags.
 *	* 1 (0b01) क्रम RX VLAN,
 *	* 2 (0b10) क्रम TX VLAN.
 *	These values make the special VIDs of 0, 1 and 4095 to be left
 *	unused by this coding scheme.
 *
 * SVL/SUBVLAN - अणु VID[9], VID[5:4] पूर्ण:
 *	Sub-VLAN encoding. Valid only when सूची indicates an RX VLAN.
 *	* 0 (0b000): Field करोes not encode a sub-VLAN, either because
 *	received traffic is untagged, PVID-tagged or because a second
 *	VLAN tag is present after this tag and not inside of it.
 *	* 1 (0b001): Received traffic is tagged with a VID value निजी
 *	to the host. This field encodes the index in the host's lookup
 *	table through which the value of the ingress VLAN ID can be
 *	recovered.
 *	* 2 (0b010): Field encodes a sub-VLAN.
 *	...
 *	* 7 (0b111): Field encodes a sub-VLAN.
 *	When सूची indicates a TX VLAN, SUBVLAN must be transmitted as zero
 *	(by the host) and ignored on receive (by the चयन).
 *
 * SWITCH_ID - VID[8:6]:
 *	Index of चयन within DSA tree. Must be between 0 and 7.
 *
 * PORT - VID[3:0]:
 *	Index of चयन port. Must be between 0 and 15.
 */

#घोषणा DSA_8021Q_सूची_SHIFT		10
#घोषणा DSA_8021Q_सूची_MASK		GENMASK(11, 10)
#घोषणा DSA_8021Q_सूची(x)		(((x) << DSA_8021Q_सूची_SHIFT) & \
						 DSA_8021Q_सूची_MASK)
#घोषणा DSA_8021Q_सूची_RX		DSA_8021Q_सूची(1)
#घोषणा DSA_8021Q_सूची_TX		DSA_8021Q_सूची(2)

#घोषणा DSA_8021Q_SWITCH_ID_SHIFT	6
#घोषणा DSA_8021Q_SWITCH_ID_MASK	GENMASK(8, 6)
#घोषणा DSA_8021Q_SWITCH_ID(x)		(((x) << DSA_8021Q_SWITCH_ID_SHIFT) & \
						 DSA_8021Q_SWITCH_ID_MASK)

#घोषणा DSA_8021Q_SUBVLAN_HI_SHIFT	9
#घोषणा DSA_8021Q_SUBVLAN_HI_MASK	GENMASK(9, 9)
#घोषणा DSA_8021Q_SUBVLAN_LO_SHIFT	4
#घोषणा DSA_8021Q_SUBVLAN_LO_MASK	GENMASK(5, 4)
#घोषणा DSA_8021Q_SUBVLAN_HI(x)		(((x) & GENMASK(2, 2)) >> 2)
#घोषणा DSA_8021Q_SUBVLAN_LO(x)		((x) & GENMASK(1, 0))
#घोषणा DSA_8021Q_SUBVLAN(x)		\
		(((DSA_8021Q_SUBVLAN_LO(x) << DSA_8021Q_SUBVLAN_LO_SHIFT) & \
		  DSA_8021Q_SUBVLAN_LO_MASK) | \
		 ((DSA_8021Q_SUBVLAN_HI(x) << DSA_8021Q_SUBVLAN_HI_SHIFT) & \
		  DSA_8021Q_SUBVLAN_HI_MASK))

#घोषणा DSA_8021Q_PORT_SHIFT		0
#घोषणा DSA_8021Q_PORT_MASK		GENMASK(3, 0)
#घोषणा DSA_8021Q_PORT(x)		(((x) << DSA_8021Q_PORT_SHIFT) & \
						 DSA_8021Q_PORT_MASK)

/* Returns the VID to be inserted पूर्णांकo the frame from xmit क्रम चयन steering
 * inकाष्ठाions on egress. Encodes चयन ID and port ID.
 */
u16 dsa_8021q_tx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस DSA_8021Q_सूची_TX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_tx_vid);

/* Returns the VID that will be installed as pvid क्रम this चयन port, sent as
 * tagged egress towards the CPU port and decoded by the rcv function.
 */
u16 dsa_8021q_rx_vid(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस DSA_8021Q_सूची_RX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_rx_vid);

u16 dsa_8021q_rx_vid_subvlan(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 subvlan)
अणु
	वापस DSA_8021Q_सूची_RX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port) | DSA_8021Q_SUBVLAN(subvlan);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_rx_vid_subvlan);

/* Returns the decoded चयन ID from the RX VID. */
पूर्णांक dsa_8021q_rx_चयन_id(u16 vid)
अणु
	वापस (vid & DSA_8021Q_SWITCH_ID_MASK) >> DSA_8021Q_SWITCH_ID_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_rx_चयन_id);

/* Returns the decoded port ID from the RX VID. */
पूर्णांक dsa_8021q_rx_source_port(u16 vid)
अणु
	वापस (vid & DSA_8021Q_PORT_MASK) >> DSA_8021Q_PORT_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_rx_source_port);

/* Returns the decoded subvlan from the RX VID. */
u16 dsa_8021q_rx_subvlan(u16 vid)
अणु
	u16 svl_hi, svl_lo;

	svl_hi = (vid & DSA_8021Q_SUBVLAN_HI_MASK) >>
		 DSA_8021Q_SUBVLAN_HI_SHIFT;
	svl_lo = (vid & DSA_8021Q_SUBVLAN_LO_MASK) >>
		 DSA_8021Q_SUBVLAN_LO_SHIFT;

	वापस (svl_hi << 2) | svl_lo;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_rx_subvlan);

bool vid_is_dsa_8021q_rxvlan(u16 vid)
अणु
	वापस (vid & DSA_8021Q_सूची_MASK) == DSA_8021Q_सूची_RX;
पूर्ण
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q_rxvlan);

bool vid_is_dsa_8021q_txvlan(u16 vid)
अणु
	वापस (vid & DSA_8021Q_सूची_MASK) == DSA_8021Q_सूची_TX;
पूर्ण
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q_txvlan);

bool vid_is_dsa_8021q(u16 vid)
अणु
	वापस vid_is_dsa_8021q_rxvlan(vid) || vid_is_dsa_8021q_txvlan(vid);
पूर्ण
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q);

/* If @enabled is true, installs @vid with @flags पूर्णांकo the चयन port's HW
 * filter.
 * If @enabled is false, deletes @vid (ignores @flags) from the port. Had the
 * user explicitly configured this @vid through the bridge core, then the @vid
 * is installed again, but this समय with the flags from the bridge layer.
 */
अटल पूर्णांक dsa_8021q_vid_apply(काष्ठा dsa_8021q_context *ctx, पूर्णांक port, u16 vid,
			       u16 flags, bool enabled)
अणु
	काष्ठा dsa_port *dp = dsa_to_port(ctx->ds, port);

	अगर (enabled)
		वापस ctx->ops->vlan_add(ctx->ds, dp->index, vid, flags);

	वापस ctx->ops->vlan_del(ctx->ds, dp->index, vid);
पूर्ण

/* RX VLAN tagging (left) and TX VLAN tagging (right) setup shown क्रम a single
 * front-panel चयन port (here swp0).
 *
 * Port identअगरication through VLAN (802.1Q) tags has dअगरferent requirements
 * क्रम it to work effectively:
 *  - On RX (ingress from network): each front-panel port must have a pvid
 *    that uniquely identअगरies it, and the egress of this pvid must be tagged
 *    towards the CPU port, so that software can recover the source port based
 *    on the VID in the frame. But this would only work क्रम standalone ports;
 *    अगर bridged, this VLAN setup would अवरोध स्वतःnomous क्रमwarding and would
 *    क्रमce all चयनed traffic to pass through the CPU. So we must also make
 *    the other front-panel ports members of this VID we're adding, albeit
 *    we're not making it their PVID (they'll still have their own).
 *    By the way - just because we're installing the same VID in multiple
 *    चयन ports करोesn't mean that they'll start to talk to one another, even
 *    जबतक not bridged: the final क्रमwarding decision is still an AND between
 *    the L2 क्रमwarding inक्रमmation (which is limiting क्रमwarding in this हाल)
 *    and the VLAN-based restrictions (of which there are none in this हाल,
 *    since all ports are members).
 *  - On TX (ingress from CPU and towards network) we are faced with a problem.
 *    If we were to tag traffic (from within DSA) with the port's pvid, all
 *    would be well, assuming the चयन ports were standalone. Frames would
 *    have no choice but to be directed towards the correct front-panel port.
 *    But because we also want the RX VLAN to not अवरोध bridging, then
 *    inevitably that means that we have to give them a choice (of what
 *    front-panel port to go out on), and thereक्रमe we cannot steer traffic
 *    based on the RX VID. So what we करो is simply install one more VID on the
 *    front-panel and CPU ports, and profit off of the fact that steering will
 *    work just by virtue of the fact that there is only one other port that's
 *    a member of the VID we're tagging the traffic with - the desired one.
 *
 * So at the end, each front-panel port will have one RX VID (also the PVID),
 * the RX VID of all other front-panel ports, and one TX VID. Whereas the CPU
 * port will have the RX and TX VIDs of all front-panel ports, and on top of
 * that, is also tagged-input and tagged-output (VLAN trunk).
 *
 *               CPU port                               CPU port
 * +-------------+-----+-------------+    +-------------+-----+-------------+
 * |  RX VID     |     |             |    |  TX VID     |     |             |
 * |  of swp0    |     |             |    |  of swp0    |     |             |
 * |             +-----+             |    |             +-----+             |
 * |                ^ T              |    |                | Tagged         |
 * |                |                |    |                | ingress        |
 * |    +-------+---+---+-------+    |    |    +-----------+                |
 * |    |       |       |       |    |    |    | Untagged                   |
 * |    |     U v     U v     U v    |    |    v egress                     |
 * | +-----+ +-----+ +-----+ +-----+ |    | +-----+ +-----+ +-----+ +-----+ |
 * | |     | |     | |     | |     | |    | |     | |     | |     | |     | |
 * | |PVID | |     | |     | |     | |    | |     | |     | |     | |     | |
 * +-+-----+-+-----+-+-----+-+-----+-+    +-+-----+-+-----+-+-----+-+-----+-+
 *   swp0    swp1    swp2    swp3           swp0    swp1    swp2    swp3
 */
अटल पूर्णांक dsa_8021q_setup_port(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				bool enabled)
अणु
	पूर्णांक upstream = dsa_upstream_port(ctx->ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ctx->ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ctx->ds, port);
	काष्ठा net_device *master;
	पूर्णांक i, err, subvlan;

	/* The CPU port is implicitly configured by
	 * configuring the front-panel ports
	 */
	अगर (!dsa_is_user_port(ctx->ds, port))
		वापस 0;

	master = dsa_to_port(ctx->ds, port)->cpu_dp->master;

	/* Add this user port's RX VID to the membership list of all others
	 * (including itself). This is so that bridging will not be hindered.
	 * L2 क्रमwarding rules still take precedence when there are no VLAN
	 * restrictions, so there are no concerns about leaking traffic.
	 */
	क्रम (i = 0; i < ctx->ds->num_ports; i++) अणु
		u16 flags;

		अगर (i == upstream)
			जारी;
		अन्यथा अगर (i == port)
			/* The RX VID is pvid on this port */
			flags = BRIDGE_VLAN_INFO_UNTAGGED |
				BRIDGE_VLAN_INFO_PVID;
		अन्यथा
			/* The RX VID is a regular VLAN on all others */
			flags = BRIDGE_VLAN_INFO_UNTAGGED;

		err = dsa_8021q_vid_apply(ctx, i, rx_vid, flags, enabled);
		अगर (err) अणु
			dev_err(ctx->ds->dev,
				"Failed to apply RX VID %d to port %d: %d\n",
				rx_vid, port, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* CPU port needs to see this port's RX VID
	 * as tagged egress.
	 */
	err = dsa_8021q_vid_apply(ctx, upstream, rx_vid, 0, enabled);
	अगर (err) अणु
		dev_err(ctx->ds->dev,
			"Failed to apply RX VID %d to port %d: %d\n",
			rx_vid, port, err);
		वापस err;
	पूर्ण

	/* Add to the master's RX filter not only @rx_vid, but in fact
	 * the entire subvlan range, just in हाल this DSA चयन might
	 * want to use sub-VLANs.
	 */
	क्रम (subvlan = 0; subvlan < DSA_8021Q_N_SUBVLAN; subvlan++) अणु
		u16 vid = dsa_8021q_rx_vid_subvlan(ctx->ds, port, subvlan);

		अगर (enabled)
			vlan_vid_add(master, ctx->proto, vid);
		अन्यथा
			vlan_vid_del(master, ctx->proto, vid);
	पूर्ण

	/* Finally apply the TX VID on this port and on the CPU port */
	err = dsa_8021q_vid_apply(ctx, port, tx_vid, BRIDGE_VLAN_INFO_UNTAGGED,
				  enabled);
	अगर (err) अणु
		dev_err(ctx->ds->dev,
			"Failed to apply TX VID %d on port %d: %d\n",
			tx_vid, port, err);
		वापस err;
	पूर्ण
	err = dsa_8021q_vid_apply(ctx, upstream, tx_vid, 0, enabled);
	अगर (err) अणु
		dev_err(ctx->ds->dev,
			"Failed to apply TX VID %d on port %d: %d\n",
			tx_vid, upstream, err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dsa_8021q_setup(काष्ठा dsa_8021q_context *ctx, bool enabled)
अणु
	पूर्णांक rc, port;

	ASSERT_RTNL();

	क्रम (port = 0; port < ctx->ds->num_ports; port++) अणु
		rc = dsa_8021q_setup_port(ctx, port, enabled);
		अगर (rc < 0) अणु
			dev_err(ctx->ds->dev,
				"Failed to setup VLAN tagging for port %d: %d\n",
				port, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_setup);

अटल पूर्णांक dsa_8021q_crosschip_link_apply(काष्ठा dsa_8021q_context *ctx,
					  पूर्णांक port,
					  काष्ठा dsa_8021q_context *other_ctx,
					  पूर्णांक other_port, bool enabled)
अणु
	u16 rx_vid = dsa_8021q_rx_vid(ctx->ds, port);

	/* @rx_vid of local @ds port @port goes to @other_port of
	 * @other_ds
	 */
	वापस dsa_8021q_vid_apply(other_ctx, other_port, rx_vid,
				   BRIDGE_VLAN_INFO_UNTAGGED, enabled);
पूर्ण

अटल पूर्णांक dsa_8021q_crosschip_link_add(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
					काष्ठा dsa_8021q_context *other_ctx,
					पूर्णांक other_port)
अणु
	काष्ठा dsa_8021q_crosschip_link *c;

	list_क्रम_each_entry(c, &ctx->crosschip_links, list) अणु
		अगर (c->port == port && c->other_ctx == other_ctx &&
		    c->other_port == other_port) अणु
			refcount_inc(&c->refcount);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_dbg(ctx->ds->dev,
		"adding crosschip link from port %d to %s port %d\n",
		port, dev_name(other_ctx->ds->dev), other_port);

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;

	c->port = port;
	c->other_ctx = other_ctx;
	c->other_port = other_port;
	refcount_set(&c->refcount, 1);

	list_add(&c->list, &ctx->crosschip_links);

	वापस 0;
पूर्ण

अटल व्योम dsa_8021q_crosschip_link_del(काष्ठा dsa_8021q_context *ctx,
					 काष्ठा dsa_8021q_crosschip_link *c,
					 bool *keep)
अणु
	*keep = !refcount_dec_and_test(&c->refcount);

	अगर (*keep)
		वापस;

	dev_dbg(ctx->ds->dev,
		"deleting crosschip link from port %d to %s port %d\n",
		c->port, dev_name(c->other_ctx->ds->dev), c->other_port);

	list_del(&c->list);
	kमुक्त(c);
पूर्ण

/* Make traffic from local port @port be received by remote port @other_port.
 * This means that our @rx_vid needs to be installed on @other_ds's upstream
 * and user ports. The user ports should be egress-untagged so that they can
 * pop the dsa_8021q VLAN. But the @other_upstream can be either egress-tagged
 * or untagged: it करोesn't matter, since it should never egress a frame having
 * our @rx_vid.
 */
पूर्णांक dsa_8021q_crosschip_bridge_join(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				    काष्ठा dsa_8021q_context *other_ctx,
				    पूर्णांक other_port)
अणु
	/* @other_upstream is how @other_ds reaches us. If we are part
	 * of disjoपूर्णांक trees, then we are probably connected through
	 * our CPU ports. If we're part of the same tree though, we should
	 * probably use dsa_towards_port.
	 */
	पूर्णांक other_upstream = dsa_upstream_port(other_ctx->ds, other_port);
	पूर्णांक rc;

	rc = dsa_8021q_crosschip_link_add(ctx, port, other_ctx, other_port);
	अगर (rc)
		वापस rc;

	rc = dsa_8021q_crosschip_link_apply(ctx, port, other_ctx,
					    other_port, true);
	अगर (rc)
		वापस rc;

	rc = dsa_8021q_crosschip_link_add(ctx, port, other_ctx, other_upstream);
	अगर (rc)
		वापस rc;

	वापस dsa_8021q_crosschip_link_apply(ctx, port, other_ctx,
					      other_upstream, true);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_crosschip_bridge_join);

पूर्णांक dsa_8021q_crosschip_bridge_leave(काष्ठा dsa_8021q_context *ctx, पूर्णांक port,
				     काष्ठा dsa_8021q_context *other_ctx,
				     पूर्णांक other_port)
अणु
	पूर्णांक other_upstream = dsa_upstream_port(other_ctx->ds, other_port);
	काष्ठा dsa_8021q_crosschip_link *c, *n;

	list_क्रम_each_entry_safe(c, n, &ctx->crosschip_links, list) अणु
		अगर (c->port == port && c->other_ctx == other_ctx &&
		    (c->other_port == other_port ||
		     c->other_port == other_upstream)) अणु
			काष्ठा dsa_8021q_context *other_ctx = c->other_ctx;
			पूर्णांक other_port = c->other_port;
			bool keep;
			पूर्णांक rc;

			dsa_8021q_crosschip_link_del(ctx, c, &keep);
			अगर (keep)
				जारी;

			rc = dsa_8021q_crosschip_link_apply(ctx, port,
							    other_ctx,
							    other_port,
							    false);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_crosschip_bridge_leave);

काष्ठा sk_buff *dsa_8021q_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			       u16 tpid, u16 tci)
अणु
	/* skb->data poपूर्णांकs at skb_mac_header, which
	 * is fine क्रम vlan_insert_tag.
	 */
	वापस vlan_insert_tag(skb, htons(tpid), tci);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_8021q_xmit);

MODULE_LICENSE("GPL v2");
