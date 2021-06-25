<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2020, NXP Semiconductors
 */
#समावेश <net/tc_act/tc_gate.h>
#समावेश <linux/dsa/8021q.h>
#समावेश "sja1105_vl.h"

#घोषणा SJA1105_SIZE_VL_STATUS			8

/* Insert पूर्णांकo the global gate list, sorted by gate action समय. */
अटल पूर्णांक sja1105_insert_gate_entry(काष्ठा sja1105_gating_config *gating_cfg,
				     काष्ठा sja1105_rule *rule,
				     u8 gate_state, s64 entry_समय,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_gate_entry *e;
	पूर्णांक rc;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e)
		वापस -ENOMEM;

	e->rule = rule;
	e->gate_state = gate_state;
	e->पूर्णांकerval = entry_समय;

	अगर (list_empty(&gating_cfg->entries)) अणु
		list_add(&e->list, &gating_cfg->entries);
	पूर्ण अन्यथा अणु
		काष्ठा sja1105_gate_entry *p;

		list_क्रम_each_entry(p, &gating_cfg->entries, list) अणु
			अगर (p->पूर्णांकerval == e->पूर्णांकerval) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Gate conflict");
				rc = -EBUSY;
				जाओ err;
			पूर्ण

			अगर (e->पूर्णांकerval < p->पूर्णांकerval)
				अवरोध;
		पूर्ण
		list_add(&e->list, p->list.prev);
	पूर्ण

	gating_cfg->num_entries++;

	वापस 0;
err:
	kमुक्त(e);
	वापस rc;
पूर्ण

/* The gate entries contain असलolute बार in their e->पूर्णांकerval field. Convert
 * that to proper पूर्णांकervals (i.e. "0, 5, 10, 15" to "5, 5, 5, 5").
 */
अटल व्योम
sja1105_gating_cfg_समय_प्रकारo_पूर्णांकerval(काष्ठा sja1105_gating_config *gating_cfg,
				    u64 cycle_समय)
अणु
	काष्ठा sja1105_gate_entry *last_e;
	काष्ठा sja1105_gate_entry *e;
	काष्ठा list_head *prev;

	list_क्रम_each_entry(e, &gating_cfg->entries, list) अणु
		काष्ठा sja1105_gate_entry *p;

		prev = e->list.prev;

		अगर (prev == &gating_cfg->entries)
			जारी;

		p = list_entry(prev, काष्ठा sja1105_gate_entry, list);
		p->पूर्णांकerval = e->पूर्णांकerval - p->पूर्णांकerval;
	पूर्ण
	last_e = list_last_entry(&gating_cfg->entries,
				 काष्ठा sja1105_gate_entry, list);
	last_e->पूर्णांकerval = cycle_समय - last_e->पूर्णांकerval;
पूर्ण

अटल व्योम sja1105_मुक्त_gating_config(काष्ठा sja1105_gating_config *gating_cfg)
अणु
	काष्ठा sja1105_gate_entry *e, *n;

	list_क्रम_each_entry_safe(e, n, &gating_cfg->entries, list) अणु
		list_del(&e->list);
		kमुक्त(e);
	पूर्ण
पूर्ण

अटल पूर्णांक sja1105_compose_gating_subschedule(काष्ठा sja1105_निजी *priv,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_gating_config *gating_cfg = &priv->tas_data.gating_cfg;
	काष्ठा sja1105_rule *rule;
	s64 max_cycle_समय = 0;
	s64 its_base_समय = 0;
	पूर्णांक i, rc = 0;

	sja1105_मुक्त_gating_config(gating_cfg);

	list_क्रम_each_entry(rule, &priv->flow_block.rules, list) अणु
		अगर (rule->type != SJA1105_RULE_VL)
			जारी;
		अगर (rule->vl.type != SJA1105_VL_TIME_TRIGGERED)
			जारी;

		अगर (max_cycle_समय < rule->vl.cycle_समय) अणु
			max_cycle_समय = rule->vl.cycle_समय;
			its_base_समय = rule->vl.base_समय;
		पूर्ण
	पूर्ण

	अगर (!max_cycle_समय)
		वापस 0;

	dev_dbg(priv->ds->dev, "max_cycle_time %lld its_base_time %lld\n",
		max_cycle_समय, its_base_समय);

	gating_cfg->base_समय = its_base_समय;
	gating_cfg->cycle_समय = max_cycle_समय;
	gating_cfg->num_entries = 0;

	list_क्रम_each_entry(rule, &priv->flow_block.rules, list) अणु
		s64 समय;
		s64 rbt;

		अगर (rule->type != SJA1105_RULE_VL)
			जारी;
		अगर (rule->vl.type != SJA1105_VL_TIME_TRIGGERED)
			जारी;

		/* Calculate the dअगरference between this gating schedule's
		 * base समय, and the base समय of the gating schedule with the
		 * दीर्घest cycle समय. We call it the relative base समय (rbt).
		 */
		rbt = future_base_समय(rule->vl.base_समय, rule->vl.cycle_समय,
				       its_base_समय);
		rbt -= its_base_समय;

		समय = rbt;

		क्रम (i = 0; i < rule->vl.num_entries; i++) अणु
			u8 gate_state = rule->vl.entries[i].gate_state;
			s64 entry_समय = समय;

			जबतक (entry_समय < max_cycle_समय) अणु
				rc = sja1105_insert_gate_entry(gating_cfg, rule,
							       gate_state,
							       entry_समय,
							       extack);
				अगर (rc)
					जाओ err;

				entry_समय += rule->vl.cycle_समय;
			पूर्ण
			समय += rule->vl.entries[i].पूर्णांकerval;
		पूर्ण
	पूर्ण

	sja1105_gating_cfg_समय_प्रकारo_पूर्णांकerval(gating_cfg, max_cycle_समय);

	वापस 0;
err:
	sja1105_मुक्त_gating_config(gating_cfg);
	वापस rc;
पूर्ण

/* The चयन flow classअगरication core implements TTEthernet, which 'thinks' in
 * terms of Virtual Links (VL), a concept borrowed from ARINC 664 part 7.
 * However it also has one other operating mode (VLLUPFORMAT=0) where it acts
 * somewhat बंदr to a pre-standard implementation of IEEE 802.1Qci
 * (Per-Stream Filtering and Policing), which is what the driver is going to be
 * implementing.
 *
 *                                 VL Lookup
 *        Key = अणुDMAC && VLANID   +---------+  Key = अणु (DMAC[47:16] & VLMASK ==
 *               && VLAN PCP      |         |                         VLMARKER)
 *               && INGRESS PORTपूर्ण +---------+                      (both fixed)
 *            (exact match,            |             && DMAC[15:0] == VLID
 *         all specअगरied in rule)      |                    (specअगरied in rule)
 *                                     v             && INGRESS PORT पूर्ण
 *                               ------------
 *                    0 (PSFP)  /            \  1 (ARINC664)
 *                 +-----------/  VLLUPFORMAT \----------+
 *                 |           \    (fixed)   /          |
 *                 |            \            /           |
 *  0 (क्रमwarding) v             ------------            |
 *           ------------                                |
 *          /            \  1 (QoS classअगरication)       |
 *     +---/  ISCRITICAL  \-----------+                  |
 *     |   \  (per rule)  /           |                  |
 *     |    \            /   VLID taken from      VLID taken from
 *     v     ------------     index of rule       contents of rule
 *  select                     that matched         that matched
 * DESTPORTS                          |                  |
 *  |                                 +---------+--------+
 *  |                                           |
 *  |                                           v
 *  |                                     VL Forwarding
 *  |                                   (indexed by VLID)
 *  |                                      +---------+
 *  |                       +--------------|         |
 *  |                       |  select TYPE +---------+
 *  |                       v
 *  |   0 (rate      ------------    1 (समय
 *  |  स्थिरrained) /            \   triggered)
 *  |       +------/     TYPE     \------------+
 *  |       |      \  (per VLID)  /            |
 *  |       v       \            /             v
 *  |  VL Policing   ------------         VL Policing
 *  | (indexed by VLID)                (indexed by VLID)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |  select SHARINDX                 select SHARINDX to
 *  |  to rate-limit                 re-enter VL Forwarding
 *  |  groups of VL's               with new VLID क्रम egress
 *  |  to same quota                           |
 *  |       |                                  |
 *  |  select MAXLEN -> exceed => drop    select MAXLEN -> exceed => drop
 *  |       |                                  |
 *  |       v                                  v
 *  |  VL Forwarding                      VL Forwarding
 *  | (indexed by SHARINDX)             (indexed by SHARINDX)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |  select PRIORITY,                 select PRIORITY,
 *  | PARTITION, DESTPORTS            PARTITION, DESTPORTS
 *  |       |                                  |
 *  |       v                                  v
 *  |  VL Policing                        VL Policing
 *  | (indexed by SHARINDX)           (indexed by SHARINDX)
 *  |  +---------+                        +---------+
 *  |  | TYPE=0  |                        | TYPE=1  |
 *  |  +---------+                        +---------+
 *  |       |                                  |
 *  |       v                                  |
 *  |  select BAG, -> exceed => drop           |
 *  |    JITTER                                v
 *  |       |             ----------------------------------------------
 *  |       |            /    Reception Winकरोw is खोलो क्रम this VL      \
 *  |       |           /    (the Schedule Table executes an entry i     \
 *  |       |          /   M <= i < N, क्रम which these conditions hold):  \ no
 *  |       |    +----/                                                    \-+
 *  |       |    |yes \       WINST[M] == 1 && WINSTINDEX[M] == VLID       / |
 *  |       |    |     \     WINEND[N] == 1 && WINSTINDEX[N] == VLID      /  |
 *  |       |    |      \                                                /   |
 *  |       |    |       \ (the VL winकरोw has खोलोed and not yet बंदd)/    |
 *  |       |    |        ----------------------------------------------     |
 *  |       |    v                                                           v
 *  |       |  dispatch to DESTPORTS when the Schedule Table               drop
 *  |       |  executes an entry i with TXEN == 1 && VLINDEX == i
 *  v       v
 * dispatch immediately to DESTPORTS
 *
 * The per-port classअगरication key is always composed of अणुDMAC, VID, PCPपूर्ण and
 * is non-maskable. This 'looks like' the शून्य stream identअगरication function
 * from IEEE 802.1CB clause 6, except क्रम the extra VLAN PCP. When the चयन
 * ports operate as VLAN-unaware, we करो allow the user to not specअगरy the VLAN
 * ID and PCP, and then the port-based शेषs will be used.
 *
 * In TTEthernet, routing is something that needs to be करोne manually क्रम each
 * Virtual Link. So the flow action must always include one of:
 * a. 'redirect', 'trap' or 'drop': select the egress port list
 * Additionally, the following actions may be applied on a Virtual Link,
 * turning it पूर्णांकo 'critical' traffic:
 * b. 'police': turn it पूर्णांकo a rate-स्थिरrained VL, with bandwidth limitation
 *    given by the maximum frame length, bandwidth allocation gap (BAG) and
 *    maximum jitter.
 * c. 'gate': turn it पूर्णांकo a समय-triggered VL, which can be only be received
 *    and क्रमwarded according to a given schedule.
 */

अटल bool sja1105_vl_key_lower(काष्ठा sja1105_vl_lookup_entry *a,
				 काष्ठा sja1105_vl_lookup_entry *b)
अणु
	अगर (a->macaddr < b->macaddr)
		वापस true;
	अगर (a->macaddr > b->macaddr)
		वापस false;
	अगर (a->vlanid < b->vlanid)
		वापस true;
	अगर (a->vlanid > b->vlanid)
		वापस false;
	अगर (a->port < b->port)
		वापस true;
	अगर (a->port > b->port)
		वापस false;
	अगर (a->vlanprior < b->vlanprior)
		वापस true;
	अगर (a->vlanprior > b->vlanprior)
		वापस false;
	/* Keys are equal */
	वापस false;
पूर्ण

अटल पूर्णांक sja1105_init_भव_links(काष्ठा sja1105_निजी *priv,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_vl_policing_entry *vl_policing;
	काष्ठा sja1105_vl_क्रमwarding_entry *vl_fwd;
	काष्ठा sja1105_vl_lookup_entry *vl_lookup;
	bool have_critical_भव_links = false;
	काष्ठा sja1105_table *table;
	काष्ठा sja1105_rule *rule;
	पूर्णांक num_भव_links = 0;
	पूर्णांक max_sharindx = 0;
	पूर्णांक i, j, k;

	/* Figure out the dimensioning of the problem */
	list_क्रम_each_entry(rule, &priv->flow_block.rules, list) अणु
		अगर (rule->type != SJA1105_RULE_VL)
			जारी;
		/* Each VL lookup entry matches on a single ingress port */
		num_भव_links += hweight_दीर्घ(rule->port_mask);

		अगर (rule->vl.type != SJA1105_VL_NONCRITICAL)
			have_critical_भव_links = true;
		अगर (max_sharindx < rule->vl.sharindx)
			max_sharindx = rule->vl.sharindx;
	पूर्ण

	अगर (num_भव_links > SJA1105_MAX_VL_LOOKUP_COUNT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Not enough VL entries available");
		वापस -ENOSPC;
	पूर्ण

	अगर (max_sharindx + 1 > SJA1105_MAX_VL_LOOKUP_COUNT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer index out of range");
		वापस -ENOSPC;
	पूर्ण

	max_sharindx = max_t(पूर्णांक, num_भव_links, max_sharindx) + 1;

	/* Discard previous VL Lookup Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_LOOKUP];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous VL Policing Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_POLICING];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous VL Forwarding Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_FORWARDING];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous VL Forwarding Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_FORWARDING_PARAMS];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Nothing to करो */
	अगर (!num_भव_links)
		वापस 0;

	/* Pre-allocate space in the अटल config tables */

	/* VL Lookup Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_LOOKUP];
	table->entries = kसुस्मृति(num_भव_links,
				 table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = num_भव_links;
	vl_lookup = table->entries;

	k = 0;

	list_क्रम_each_entry(rule, &priv->flow_block.rules, list) अणु
		अचिन्हित दीर्घ port;

		अगर (rule->type != SJA1105_RULE_VL)
			जारी;

		क्रम_each_set_bit(port, &rule->port_mask, SJA1105_NUM_PORTS) अणु
			vl_lookup[k].क्रमmat = SJA1105_VL_FORMAT_PSFP;
			vl_lookup[k].port = port;
			vl_lookup[k].macaddr = rule->key.vl.dmac;
			अगर (rule->key.type == SJA1105_KEY_VLAN_AWARE_VL) अणु
				vl_lookup[k].vlanid = rule->key.vl.vid;
				vl_lookup[k].vlanprior = rule->key.vl.pcp;
			पूर्ण अन्यथा अणु
				u16 vid = dsa_8021q_rx_vid(priv->ds, port);

				vl_lookup[k].vlanid = vid;
				vl_lookup[k].vlanprior = 0;
			पूर्ण
			/* For critical VLs, the DESTPORTS mask is taken from
			 * the VL Forwarding Table, so no poपूर्णांक in putting it
			 * in the VL Lookup Table
			 */
			अगर (rule->vl.type == SJA1105_VL_NONCRITICAL)
				vl_lookup[k].destports = rule->vl.destports;
			अन्यथा
				vl_lookup[k].iscritical = true;
			vl_lookup[k].flow_cookie = rule->cookie;
			k++;
		पूर्ण
	पूर्ण

	/* UM10944.pdf chapter 4.2.3 VL Lookup table:
	 * "the entries in the VL Lookup table must be sorted in ascending
	 * order (i.e. the smallest value must be loaded first) according to
	 * the following sort order: MACADDR, VLANID, PORT, VLANPRIOR."
	 */
	क्रम (i = 0; i < num_भव_links; i++) अणु
		काष्ठा sja1105_vl_lookup_entry *a = &vl_lookup[i];

		क्रम (j = i + 1; j < num_भव_links; j++) अणु
			काष्ठा sja1105_vl_lookup_entry *b = &vl_lookup[j];

			अगर (sja1105_vl_key_lower(b, a)) अणु
				काष्ठा sja1105_vl_lookup_entry पंचांगp = *a;

				*a = *b;
				*b = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!have_critical_भव_links)
		वापस 0;

	/* VL Policing Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_POLICING];
	table->entries = kसुस्मृति(max_sharindx, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = max_sharindx;
	vl_policing = table->entries;

	/* VL Forwarding Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_FORWARDING];
	table->entries = kसुस्मृति(max_sharindx, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = max_sharindx;
	vl_fwd = table->entries;

	/* VL Forwarding Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_VL_FORWARDING_PARAMS];
	table->entries = kसुस्मृति(1, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = 1;

	क्रम (i = 0; i < num_भव_links; i++) अणु
		अचिन्हित दीर्घ cookie = vl_lookup[i].flow_cookie;
		काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cookie);

		अगर (rule->vl.type == SJA1105_VL_NONCRITICAL)
			जारी;
		अगर (rule->vl.type == SJA1105_VL_TIME_TRIGGERED) अणु
			पूर्णांक sharindx = rule->vl.sharindx;

			vl_policing[i].type = 1;
			vl_policing[i].sharindx = sharindx;
			vl_policing[i].maxlen = rule->vl.maxlen;
			vl_policing[sharindx].type = 1;

			vl_fwd[i].type = 1;
			vl_fwd[sharindx].type = 1;
			vl_fwd[sharindx].priority = rule->vl.ipv;
			vl_fwd[sharindx].partition = 0;
			vl_fwd[sharindx].destports = rule->vl.destports;
		पूर्ण
	पूर्ण

	sja1105_frame_memory_partitioning(priv);

	वापस 0;
पूर्ण

पूर्णांक sja1105_vl_redirect(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			काष्ठा netlink_ext_ack *extack, अचिन्हित दीर्घ cookie,
			काष्ठा sja1105_key *key, अचिन्हित दीर्घ destports,
			bool append)
अणु
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cookie);
	पूर्णांक rc;

	अगर (priv->vlan_state == SJA1105_VLAN_UNAWARE &&
	    key->type != SJA1105_KEY_VLAN_UNAWARE_VL) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can only redirect based on DMAC");
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर ((priv->vlan_state == SJA1105_VLAN_BEST_EFFORT ||
		    priv->vlan_state == SJA1105_VLAN_FILTERING_FULL) &&
		   key->type != SJA1105_KEY_VLAN_AWARE_VL) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can only redirect based on {DMAC, VID, PCP}");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!rule) अणु
		rule = kzalloc(माप(*rule), GFP_KERNEL);
		अगर (!rule)
			वापस -ENOMEM;

		rule->cookie = cookie;
		rule->type = SJA1105_RULE_VL;
		rule->key = *key;
		list_add(&rule->list, &priv->flow_block.rules);
	पूर्ण

	rule->port_mask |= BIT(port);
	अगर (append)
		rule->vl.destports |= destports;
	अन्यथा
		rule->vl.destports = destports;

	rc = sja1105_init_भव_links(priv, extack);
	अगर (rc) अणु
		rule->port_mask &= ~BIT(port);
		अगर (!rule->port_mask) अणु
			list_del(&rule->list);
			kमुक्त(rule);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक sja1105_vl_delete(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		      काष्ठा sja1105_rule *rule, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक rc;

	rule->port_mask &= ~BIT(port);
	अगर (!rule->port_mask) अणु
		list_del(&rule->list);
		kमुक्त(rule);
	पूर्ण

	rc = sja1105_compose_gating_subschedule(priv, extack);
	अगर (rc)
		वापस rc;

	rc = sja1105_init_भव_links(priv, extack);
	अगर (rc)
		वापस rc;

	rc = sja1105_init_scheduling(priv);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_config_reload(priv, SJA1105_VIRTUAL_LINKS);
पूर्ण

पूर्णांक sja1105_vl_gate(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		    काष्ठा netlink_ext_ack *extack, अचिन्हित दीर्घ cookie,
		    काष्ठा sja1105_key *key, u32 index, s32 prio,
		    u64 base_समय, u64 cycle_समय, u64 cycle_समय_ext,
		    u32 num_entries, काष्ठा action_gate_entry *entries)
अणु
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cookie);
	पूर्णांक ipv = -1;
	पूर्णांक i, rc;
	s32 rem;

	अगर (cycle_समय_ext) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Cycle time extension not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	भाग_s64_rem(base_समय, sja1105_delta_to_ns(1), &rem);
	अगर (rem) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Base time must be multiple of 200 ns");
		वापस -दुस्फल;
	पूर्ण

	भाग_s64_rem(cycle_समय, sja1105_delta_to_ns(1), &rem);
	अगर (rem) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Cycle time must be multiple of 200 ns");
		वापस -दुस्फल;
	पूर्ण

	अगर (priv->vlan_state == SJA1105_VLAN_UNAWARE &&
	    key->type != SJA1105_KEY_VLAN_UNAWARE_VL) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can only gate based on DMAC");
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर ((priv->vlan_state == SJA1105_VLAN_BEST_EFFORT ||
		    priv->vlan_state == SJA1105_VLAN_FILTERING_FULL) &&
		   key->type != SJA1105_KEY_VLAN_AWARE_VL) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can only gate based on {DMAC, VID, PCP}");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!rule) अणु
		rule = kzalloc(माप(*rule), GFP_KERNEL);
		अगर (!rule)
			वापस -ENOMEM;

		list_add(&rule->list, &priv->flow_block.rules);
		rule->cookie = cookie;
		rule->type = SJA1105_RULE_VL;
		rule->key = *key;
		rule->vl.type = SJA1105_VL_TIME_TRIGGERED;
		rule->vl.sharindx = index;
		rule->vl.base_समय = base_समय;
		rule->vl.cycle_समय = cycle_समय;
		rule->vl.num_entries = num_entries;
		rule->vl.entries = kसुस्मृति(num_entries,
					   माप(काष्ठा action_gate_entry),
					   GFP_KERNEL);
		अगर (!rule->vl.entries) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < num_entries; i++) अणु
			भाग_s64_rem(entries[i].पूर्णांकerval,
				    sja1105_delta_to_ns(1), &rem);
			अगर (rem) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Interval must be multiple of 200 ns");
				rc = -दुस्फल;
				जाओ out;
			पूर्ण

			अगर (!entries[i].पूर्णांकerval) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Interval cannot be zero");
				rc = -दुस्फल;
				जाओ out;
			पूर्ण

			अगर (ns_to_sja1105_delta(entries[i].पूर्णांकerval) >
			    SJA1105_TAS_MAX_DELTA) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Maximum interval is 52 ms");
				rc = -दुस्फल;
				जाओ out;
			पूर्ण

			अगर (entries[i].maxoctets != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Cannot offload IntervalOctetMax");
				rc = -EOPNOTSUPP;
				जाओ out;
			पूर्ण

			अगर (ipv == -1) अणु
				ipv = entries[i].ipv;
			पूर्ण अन्यथा अगर (ipv != entries[i].ipv) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Only support a single IPV per VL");
				rc = -EOPNOTSUPP;
				जाओ out;
			पूर्ण

			rule->vl.entries[i] = entries[i];
		पूर्ण

		अगर (ipv == -1) अणु
			अगर (key->type == SJA1105_KEY_VLAN_AWARE_VL)
				ipv = key->vl.pcp;
			अन्यथा
				ipv = 0;
		पूर्ण

		/* TODO: support per-flow MTU */
		rule->vl.maxlen = VLAN_ETH_FRAME_LEN + ETH_FCS_LEN;
		rule->vl.ipv = ipv;
	पूर्ण

	rule->port_mask |= BIT(port);

	rc = sja1105_compose_gating_subschedule(priv, extack);
	अगर (rc)
		जाओ out;

	rc = sja1105_init_भव_links(priv, extack);
	अगर (rc)
		जाओ out;

	अगर (sja1105_gating_check_conflicts(priv, -1, extack)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Conflict with tc-taprio schedule");
		rc = -दुस्फल;
		जाओ out;
	पूर्ण

out:
	अगर (rc) अणु
		rule->port_mask &= ~BIT(port);
		अगर (!rule->port_mask) अणु
			list_del(&rule->list);
			kमुक्त(rule->vl.entries);
			kमुक्त(rule);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_find_vlid(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			     काष्ठा sja1105_key *key)
अणु
	काष्ठा sja1105_vl_lookup_entry *vl_lookup;
	काष्ठा sja1105_table *table;
	पूर्णांक i;

	अगर (WARN_ON(key->type != SJA1105_KEY_VLAN_AWARE_VL &&
		    key->type != SJA1105_KEY_VLAN_UNAWARE_VL))
		वापस -1;

	table = &priv->अटल_config.tables[BLK_IDX_VL_LOOKUP];
	vl_lookup = table->entries;

	क्रम (i = 0; i < table->entry_count; i++) अणु
		अगर (key->type == SJA1105_KEY_VLAN_AWARE_VL) अणु
			अगर (vl_lookup[i].port == port &&
			    vl_lookup[i].macaddr == key->vl.dmac &&
			    vl_lookup[i].vlanid == key->vl.vid &&
			    vl_lookup[i].vlanprior == key->vl.pcp)
				वापस i;
		पूर्ण अन्यथा अणु
			अगर (vl_lookup[i].port == port &&
			    vl_lookup[i].macaddr == key->vl.dmac)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक sja1105_vl_stats(काष्ठा sja1105_निजी *priv, पूर्णांक port,
		     काष्ठा sja1105_rule *rule, काष्ठा flow_stats *stats,
		     काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 buf[SJA1105_SIZE_VL_STATUS] = अणु0पूर्ण;
	u64 unreleased;
	u64 timingerr;
	u64 lengtherr;
	पूर्णांक vlid, rc;
	u64 pkts;

	अगर (rule->vl.type != SJA1105_VL_TIME_TRIGGERED)
		वापस 0;

	vlid = sja1105_find_vlid(priv, port, &rule->key);
	अगर (vlid < 0)
		वापस 0;

	rc = sja1105_xfer_buf(priv, SPI_READ, regs->vl_status + 2 * vlid, buf,
			      SJA1105_SIZE_VL_STATUS);
	अगर (rc) अणु
		NL_SET_ERR_MSG_MOD(extack, "SPI access failed");
		वापस rc;
	पूर्ण

	sja1105_unpack(buf, &timingerr,  31, 16, SJA1105_SIZE_VL_STATUS);
	sja1105_unpack(buf, &unreleased, 15,  0, SJA1105_SIZE_VL_STATUS);
	sja1105_unpack(buf, &lengtherr,  47, 32, SJA1105_SIZE_VL_STATUS);

	pkts = timingerr + unreleased + lengtherr;

	flow_stats_update(stats, 0, pkts - rule->vl.stats.pkts, 0,
			  jअगरfies - rule->vl.stats.lastused,
			  FLOW_ACTION_HW_STATS_IMMEDIATE);

	rule->vl.stats.pkts = pkts;
	rule->vl.stats.lastused = jअगरfies;

	वापस 0;
पूर्ण
