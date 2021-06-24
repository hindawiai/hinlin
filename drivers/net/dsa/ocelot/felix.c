<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019-2021 NXP Semiconductors
 *
 * This is an umbrella module क्रम all network चयनes that are
 * रेजिस्टर-compatible with Ocelot and that perक्रमm I/O to their host CPU
 * through an NPI (Node Processor Interface) Ethernet port.
 */
#समावेश <uapi/linux/अगर_bridge.h>
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश <soc/mscc/ocelot_qsys.h>
#समावेश <soc/mscc/ocelot_sys.h>
#समावेश <soc/mscc/ocelot_dev.h>
#समावेश <soc/mscc/ocelot_ana.h>
#समावेश <soc/mscc/ocelot_ptp.h>
#समावेश <soc/mscc/ocelot.h>
#समावेश <linux/dsa/8021q.h>
#समावेश <linux/dsa/ocelot.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/pcs-lynx.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/dsa.h>
#समावेश "felix.h"

अटल पूर्णांक felix_tag_8021q_rxvlan_add(काष्ठा felix *felix, पूर्णांक port, u16 vid,
				      bool pvid, bool untagged)
अणु
	काष्ठा ocelot_vcap_filter *outer_tagging_rule;
	काष्ठा ocelot *ocelot = &felix->ocelot;
	काष्ठा dsa_चयन *ds = felix->ds;
	पूर्णांक key_length, upstream, err;

	/* We करोn't need to install the rxvlan into the other ports' filtering
	 * tables, because we're just pushing the rxvlan when sending towards
	 * the CPU
	 */
	अगर (!pvid)
		वापस 0;

	key_length = ocelot->vcap[VCAP_ES0].keys[VCAP_ES0_IGR_PORT].length;
	upstream = dsa_upstream_port(ds, port);

	outer_tagging_rule = kzalloc(माप(काष्ठा ocelot_vcap_filter),
				     GFP_KERNEL);
	अगर (!outer_tagging_rule)
		वापस -ENOMEM;

	outer_tagging_rule->key_type = OCELOT_VCAP_KEY_ANY;
	outer_tagging_rule->prio = 1;
	outer_tagging_rule->id.cookie = port;
	outer_tagging_rule->id.tc_offload = false;
	outer_tagging_rule->block_id = VCAP_ES0;
	outer_tagging_rule->type = OCELOT_VCAP_FILTER_OFFLOAD;
	outer_tagging_rule->lookup = 0;
	outer_tagging_rule->ingress_port.value = port;
	outer_tagging_rule->ingress_port.mask = GENMASK(key_length - 1, 0);
	outer_tagging_rule->egress_port.value = upstream;
	outer_tagging_rule->egress_port.mask = GENMASK(key_length - 1, 0);
	outer_tagging_rule->action.push_outer_tag = OCELOT_ES0_TAG;
	outer_tagging_rule->action.tag_a_tpid_sel = OCELOT_TAG_TPID_SEL_8021AD;
	outer_tagging_rule->action.tag_a_vid_sel = 1;
	outer_tagging_rule->action.vid_a_val = vid;

	err = ocelot_vcap_filter_add(ocelot, outer_tagging_rule, शून्य);
	अगर (err)
		kमुक्त(outer_tagging_rule);

	वापस err;
पूर्ण

अटल पूर्णांक felix_tag_8021q_txvlan_add(काष्ठा felix *felix, पूर्णांक port, u16 vid,
				      bool pvid, bool untagged)
अणु
	काष्ठा ocelot_vcap_filter *untagging_rule, *redirect_rule;
	काष्ठा ocelot *ocelot = &felix->ocelot;
	काष्ठा dsa_चयन *ds = felix->ds;
	पूर्णांक upstream, err;

	/* tag_8021q.c assumes we are implementing this via port VLAN
	 * membership, which we aren't. So we don't need to add any VCAP filter
	 * क्रम the CPU port.
	 */
	अगर (ocelot->ports[port]->is_dsa_8021q_cpu)
		वापस 0;

	untagging_rule = kzalloc(माप(काष्ठा ocelot_vcap_filter), GFP_KERNEL);
	अगर (!untagging_rule)
		वापस -ENOMEM;

	redirect_rule = kzalloc(माप(काष्ठा ocelot_vcap_filter), GFP_KERNEL);
	अगर (!redirect_rule) अणु
		kमुक्त(untagging_rule);
		वापस -ENOMEM;
	पूर्ण

	upstream = dsa_upstream_port(ds, port);

	untagging_rule->key_type = OCELOT_VCAP_KEY_ANY;
	untagging_rule->ingress_port_mask = BIT(upstream);
	untagging_rule->vlan.vid.value = vid;
	untagging_rule->vlan.vid.mask = VLAN_VID_MASK;
	untagging_rule->prio = 1;
	untagging_rule->id.cookie = port;
	untagging_rule->id.tc_offload = false;
	untagging_rule->block_id = VCAP_IS1;
	untagging_rule->type = OCELOT_VCAP_FILTER_OFFLOAD;
	untagging_rule->lookup = 0;
	untagging_rule->action.vlan_pop_cnt_ena = true;
	untagging_rule->action.vlan_pop_cnt = 1;
	untagging_rule->action.pag_override_mask = 0xff;
	untagging_rule->action.pag_val = port;

	err = ocelot_vcap_filter_add(ocelot, untagging_rule, शून्य);
	अगर (err) अणु
		kमुक्त(untagging_rule);
		kमुक्त(redirect_rule);
		वापस err;
	पूर्ण

	redirect_rule->key_type = OCELOT_VCAP_KEY_ANY;
	redirect_rule->ingress_port_mask = BIT(upstream);
	redirect_rule->pag = port;
	redirect_rule->prio = 1;
	redirect_rule->id.cookie = port;
	redirect_rule->id.tc_offload = false;
	redirect_rule->block_id = VCAP_IS2;
	redirect_rule->type = OCELOT_VCAP_FILTER_OFFLOAD;
	redirect_rule->lookup = 0;
	redirect_rule->action.mask_mode = OCELOT_MASK_MODE_REसूचीECT;
	redirect_rule->action.port_mask = BIT(port);

	err = ocelot_vcap_filter_add(ocelot, redirect_rule, शून्य);
	अगर (err) अणु
		ocelot_vcap_filter_del(ocelot, untagging_rule);
		kमुक्त(redirect_rule);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक felix_tag_8021q_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid,
				    u16 flags)
अणु
	bool untagged = flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा ocelot *ocelot = ds->priv;

	अगर (vid_is_dsa_8021q_rxvlan(vid))
		वापस felix_tag_8021q_rxvlan_add(ocelot_to_felix(ocelot),
						  port, vid, pvid, untagged);

	अगर (vid_is_dsa_8021q_txvlan(vid))
		वापस felix_tag_8021q_txvlan_add(ocelot_to_felix(ocelot),
						  port, vid, pvid, untagged);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_tag_8021q_rxvlan_del(काष्ठा felix *felix, पूर्णांक port, u16 vid)
अणु
	काष्ठा ocelot_vcap_filter *outer_tagging_rule;
	काष्ठा ocelot_vcap_block *block_vcap_es0;
	काष्ठा ocelot *ocelot = &felix->ocelot;

	block_vcap_es0 = &ocelot->block[VCAP_ES0];

	outer_tagging_rule = ocelot_vcap_block_find_filter_by_id(block_vcap_es0,
								 port, false);
	/* In rxvlan_add, we had the "if (!pvid) return 0" logic to aव्योम
	 * installing outer tagging ES0 rules where they weren't needed.
	 * But in rxvlan_del, the API करोesn't give us the "flags" anymore,
	 * so that क्रमces us to be slightly sloppy here, and just assume that
	 * अगर we didn't find an outer_tagging_rule it means that there was
	 * none in the first place, i.e. rxvlan_del is called on a non-pvid
	 * port. This is most probably true though.
	 */
	अगर (!outer_tagging_rule)
		वापस 0;

	वापस ocelot_vcap_filter_del(ocelot, outer_tagging_rule);
पूर्ण

अटल पूर्णांक felix_tag_8021q_txvlan_del(काष्ठा felix *felix, पूर्णांक port, u16 vid)
अणु
	काष्ठा ocelot_vcap_filter *untagging_rule, *redirect_rule;
	काष्ठा ocelot_vcap_block *block_vcap_is1;
	काष्ठा ocelot_vcap_block *block_vcap_is2;
	काष्ठा ocelot *ocelot = &felix->ocelot;
	पूर्णांक err;

	अगर (ocelot->ports[port]->is_dsa_8021q_cpu)
		वापस 0;

	block_vcap_is1 = &ocelot->block[VCAP_IS1];
	block_vcap_is2 = &ocelot->block[VCAP_IS2];

	untagging_rule = ocelot_vcap_block_find_filter_by_id(block_vcap_is1,
							     port, false);
	अगर (!untagging_rule)
		वापस 0;

	err = ocelot_vcap_filter_del(ocelot, untagging_rule);
	अगर (err)
		वापस err;

	redirect_rule = ocelot_vcap_block_find_filter_by_id(block_vcap_is2,
							    port, false);
	अगर (!redirect_rule)
		वापस 0;

	वापस ocelot_vcap_filter_del(ocelot, redirect_rule);
पूर्ण

अटल पूर्णांक felix_tag_8021q_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port, u16 vid)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	अगर (vid_is_dsa_8021q_rxvlan(vid))
		वापस felix_tag_8021q_rxvlan_del(ocelot_to_felix(ocelot),
						  port, vid);

	अगर (vid_is_dsa_8021q_txvlan(vid))
		वापस felix_tag_8021q_txvlan_del(ocelot_to_felix(ocelot),
						  port, vid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_8021q_ops felix_tag_8021q_ops = अणु
	.vlan_add	= felix_tag_8021q_vlan_add,
	.vlan_del	= felix_tag_8021q_vlan_del,
पूर्ण;

/* Alternatively to using the NPI functionality, that same hardware MAC
 * connected पूर्णांकernally to the enetc or fman DSA master can be configured to
 * use the software-defined tag_8021q frame क्रमmat. As far as the hardware is
 * concerned, it thinks it is a "dumb switch" - the queues of the CPU port
 * module are now disconnected from it, but can still be accessed through
 * रेजिस्टर-based MMIO.
 */
अटल व्योम felix_8021q_cpu_port_init(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	ocelot->ports[port]->is_dsa_8021q_cpu = true;
	ocelot->npi = -1;

	/* Overग_लिखो PGID_CPU with the non-tagging port */
	ocelot_ग_लिखो_rix(ocelot, BIT(port), ANA_PGID_PGID, PGID_CPU);

	ocelot_apply_bridge_fwd_mask(ocelot);
पूर्ण

अटल व्योम felix_8021q_cpu_port_deinit(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	ocelot->ports[port]->is_dsa_8021q_cpu = false;

	/* Restore PGID_CPU */
	ocelot_ग_लिखो_rix(ocelot, BIT(ocelot->num_phys_ports), ANA_PGID_PGID,
			 PGID_CPU);

	ocelot_apply_bridge_fwd_mask(ocelot);
पूर्ण

/* Set up a VCAP IS2 rule क्रम delivering PTP frames to the CPU port module.
 * If the quirk_no_xtr_irq is in place, then also copy those PTP frames to the
 * tag_8021q CPU port.
 */
अटल पूर्णांक felix_setup_mmio_filtering(काष्ठा felix *felix)
अणु
	अचिन्हित दीर्घ user_ports = 0, cpu_ports = 0;
	काष्ठा ocelot_vcap_filter *redirect_rule;
	काष्ठा ocelot_vcap_filter *tagging_rule;
	काष्ठा ocelot *ocelot = &felix->ocelot;
	काष्ठा dsa_चयन *ds = felix->ds;
	पूर्णांक port, ret;

	tagging_rule = kzalloc(माप(काष्ठा ocelot_vcap_filter), GFP_KERNEL);
	अगर (!tagging_rule)
		वापस -ENOMEM;

	redirect_rule = kzalloc(माप(काष्ठा ocelot_vcap_filter), GFP_KERNEL);
	अगर (!redirect_rule) अणु
		kमुक्त(tagging_rule);
		वापस -ENOMEM;
	पूर्ण

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		अगर (dsa_is_user_port(ds, port))
			user_ports |= BIT(port);
		अगर (dsa_is_cpu_port(ds, port))
			cpu_ports |= BIT(port);
	पूर्ण

	tagging_rule->key_type = OCELOT_VCAP_KEY_ETYPE;
	*(__be16 *)tagging_rule->key.etype.etype.value = htons(ETH_P_1588);
	*(__be16 *)tagging_rule->key.etype.etype.mask = htons(0xffff);
	tagging_rule->ingress_port_mask = user_ports;
	tagging_rule->prio = 1;
	tagging_rule->id.cookie = ocelot->num_phys_ports;
	tagging_rule->id.tc_offload = false;
	tagging_rule->block_id = VCAP_IS1;
	tagging_rule->type = OCELOT_VCAP_FILTER_OFFLOAD;
	tagging_rule->lookup = 0;
	tagging_rule->action.pag_override_mask = 0xff;
	tagging_rule->action.pag_val = ocelot->num_phys_ports;

	ret = ocelot_vcap_filter_add(ocelot, tagging_rule, शून्य);
	अगर (ret) अणु
		kमुक्त(tagging_rule);
		kमुक्त(redirect_rule);
		वापस ret;
	पूर्ण

	redirect_rule->key_type = OCELOT_VCAP_KEY_ANY;
	redirect_rule->ingress_port_mask = user_ports;
	redirect_rule->pag = ocelot->num_phys_ports;
	redirect_rule->prio = 1;
	redirect_rule->id.cookie = ocelot->num_phys_ports;
	redirect_rule->id.tc_offload = false;
	redirect_rule->block_id = VCAP_IS2;
	redirect_rule->type = OCELOT_VCAP_FILTER_OFFLOAD;
	redirect_rule->lookup = 0;
	redirect_rule->action.cpu_copy_ena = true;
	अगर (felix->info->quirk_no_xtr_irq) अणु
		/* Redirect to the tag_8021q CPU but also copy PTP packets to
		 * the CPU port module
		 */
		redirect_rule->action.mask_mode = OCELOT_MASK_MODE_REसूचीECT;
		redirect_rule->action.port_mask = cpu_ports;
	पूर्ण अन्यथा अणु
		/* Trap PTP packets only to the CPU port module (which is
		 * redirected to the NPI port)
		 */
		redirect_rule->action.mask_mode = OCELOT_MASK_MODE_PERMIT_DENY;
		redirect_rule->action.port_mask = 0;
	पूर्ण

	ret = ocelot_vcap_filter_add(ocelot, redirect_rule, शून्य);
	अगर (ret) अणु
		ocelot_vcap_filter_del(ocelot, tagging_rule);
		kमुक्त(redirect_rule);
		वापस ret;
	पूर्ण

	/* The ownership of the CPU port module's queues might have just been
	 * transferred to the tag_8021q tagger from the NPI-based tagger.
	 * So there might still be all sorts of crap in the queues. On the
	 * other hand, the MMIO-based matching of PTP frames is very brittle,
	 * so we need to be careful that there are no extra frames to be
	 * dequeued over MMIO, since we would never know to discard them.
	 */
	ocelot_drain_cpu_queue(ocelot, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_tearकरोwn_mmio_filtering(काष्ठा felix *felix)
अणु
	काष्ठा ocelot_vcap_filter *tagging_rule, *redirect_rule;
	काष्ठा ocelot_vcap_block *block_vcap_is1;
	काष्ठा ocelot_vcap_block *block_vcap_is2;
	काष्ठा ocelot *ocelot = &felix->ocelot;
	पूर्णांक err;

	block_vcap_is1 = &ocelot->block[VCAP_IS1];
	block_vcap_is2 = &ocelot->block[VCAP_IS2];

	tagging_rule = ocelot_vcap_block_find_filter_by_id(block_vcap_is1,
							   ocelot->num_phys_ports,
							   false);
	अगर (!tagging_rule)
		वापस -ENOENT;

	err = ocelot_vcap_filter_del(ocelot, tagging_rule);
	अगर (err)
		वापस err;

	redirect_rule = ocelot_vcap_block_find_filter_by_id(block_vcap_is2,
							    ocelot->num_phys_ports,
							    false);
	अगर (!redirect_rule)
		वापस -ENOENT;

	वापस ocelot_vcap_filter_del(ocelot, redirect_rule);
पूर्ण

अटल पूर्णांक felix_setup_tag_8021q(काष्ठा dsa_चयन *ds, पूर्णांक cpu)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	अचिन्हित दीर्घ cpu_flood;
	पूर्णांक port, err;

	felix_8021q_cpu_port_init(ocelot, cpu);

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_is_unused_port(ds, port))
			जारी;

		/* This overग_लिखोs ocelot_init():
		 * Do not क्रमward BPDU frames to the CPU port module,
		 * क्रम 2 reasons:
		 * - When these packets are injected from the tag_8021q
		 *   CPU port, we want them to go out, not loop back
		 *   पूर्णांकo the प्रणाली.
		 * - STP traffic ingressing on a user port should go to
		 *   the tag_8021q CPU port, not to the hardware CPU
		 *   port module.
		 */
		ocelot_ग_लिखो_gix(ocelot,
				 ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REसूची_ENA(0),
				 ANA_PORT_CPU_FWD_BPDU_CFG, port);
	पूर्ण

	/* In tag_8021q mode, the CPU port module is unused, except क्रम PTP
	 * frames. So we want to disable flooding of any kind to the CPU port
	 * module, since packets going there will end in a black hole.
	 */
	cpu_flood = ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports));
	ocelot_rmw_rix(ocelot, 0, cpu_flood, ANA_PGID_PGID, PGID_UC);
	ocelot_rmw_rix(ocelot, 0, cpu_flood, ANA_PGID_PGID, PGID_MC);
	ocelot_rmw_rix(ocelot, 0, cpu_flood, ANA_PGID_PGID, PGID_BC);

	felix->dsa_8021q_ctx = kzalloc(माप(*felix->dsa_8021q_ctx),
				       GFP_KERNEL);
	अगर (!felix->dsa_8021q_ctx)
		वापस -ENOMEM;

	felix->dsa_8021q_ctx->ops = &felix_tag_8021q_ops;
	felix->dsa_8021q_ctx->proto = htons(ETH_P_8021AD);
	felix->dsa_8021q_ctx->ds = ds;

	err = dsa_8021q_setup(felix->dsa_8021q_ctx, true);
	अगर (err)
		जाओ out_मुक्त_dsa_8021_ctx;

	err = felix_setup_mmio_filtering(felix);
	अगर (err)
		जाओ out_tearकरोwn_dsa_8021q;

	वापस 0;

out_tearकरोwn_dsa_8021q:
	dsa_8021q_setup(felix->dsa_8021q_ctx, false);
out_मुक्त_dsa_8021_ctx:
	kमुक्त(felix->dsa_8021q_ctx);
	वापस err;
पूर्ण

अटल व्योम felix_tearकरोwn_tag_8021q(काष्ठा dsa_चयन *ds, पूर्णांक cpu)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	पूर्णांक err, port;

	err = felix_tearकरोwn_mmio_filtering(felix);
	अगर (err)
		dev_err(ds->dev, "felix_teardown_mmio_filtering returned %d",
			err);

	err = dsa_8021q_setup(felix->dsa_8021q_ctx, false);
	अगर (err)
		dev_err(ds->dev, "dsa_8021q_setup returned %d", err);

	kमुक्त(felix->dsa_8021q_ctx);

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_is_unused_port(ds, port))
			जारी;

		/* Restore the logic from ocelot_init:
		 * करो not क्रमward BPDU frames to the front ports.
		 */
		ocelot_ग_लिखो_gix(ocelot,
				 ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REसूची_ENA(0xffff),
				 ANA_PORT_CPU_FWD_BPDU_CFG,
				 port);
	पूर्ण

	felix_8021q_cpu_port_deinit(ocelot, cpu);
पूर्ण

/* The CPU port module is connected to the Node Processor Interface (NPI). This
 * is the mode through which frames can be injected from and extracted to an
 * बाह्यal CPU, over Ethernet. In NXP SoCs, the "external CPU" is the ARM CPU
 * running Linux, and this क्रमms a DSA setup together with the enetc or fman
 * DSA master.
 */
अटल व्योम felix_npi_port_init(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	ocelot->npi = port;

	ocelot_ग_लिखो(ocelot, QSYS_EXT_CPU_CFG_EXT_CPUQ_MSK_M |
		     QSYS_EXT_CPU_CFG_EXT_CPU_PORT(port),
		     QSYS_EXT_CPU_CFG);

	/* NPI port Injection/Extraction configuration */
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PORT_MODE_INCL_XTR_HDR,
			    ocelot->npi_xtr_prefix);
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PORT_MODE_INCL_INJ_HDR,
			    ocelot->npi_inj_prefix);

	/* Disable transmission of छोड़ो frames */
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, 0);
पूर्ण

अटल व्योम felix_npi_port_deinit(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	/* Restore hardware शेषs */
	पूर्णांक unused_port = ocelot->num_phys_ports + 2;

	ocelot->npi = -1;

	ocelot_ग_लिखो(ocelot, QSYS_EXT_CPU_CFG_EXT_CPU_PORT(unused_port),
		     QSYS_EXT_CPU_CFG);

	ocelot_fields_ग_लिखो(ocelot, port, SYS_PORT_MODE_INCL_XTR_HDR,
			    OCELOT_TAG_PREFIX_DISABLED);
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PORT_MODE_INCL_INJ_HDR,
			    OCELOT_TAG_PREFIX_DISABLED);

	/* Enable transmission of छोड़ो frames */
	ocelot_fields_ग_लिखो(ocelot, port, SYS_PAUSE_CFG_PAUSE_ENA, 1);
पूर्ण

अटल पूर्णांक felix_setup_tag_npi(काष्ठा dsa_चयन *ds, पूर्णांक cpu)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	अचिन्हित दीर्घ cpu_flood;

	felix_npi_port_init(ocelot, cpu);

	/* Include the CPU port module (and indirectly, the NPI port)
	 * in the क्रमwarding mask क्रम unknown unicast - the hardware
	 * शेष value क्रम ANA_FLOODING_FLD_UNICAST excludes
	 * BIT(ocelot->num_phys_ports), and so करोes ocelot_init,
	 * since Ocelot relies on whitelisting MAC addresses towards
	 * PGID_CPU.
	 * We करो this because DSA करोes not yet perक्रमm RX filtering,
	 * and the NPI port करोes not perक्रमm source address learning,
	 * so traffic sent to Linux is effectively unknown from the
	 * चयन's perspective.
	 */
	cpu_flood = ANA_PGID_PGID_PGID(BIT(ocelot->num_phys_ports));
	ocelot_rmw_rix(ocelot, cpu_flood, cpu_flood, ANA_PGID_PGID, PGID_UC);
	ocelot_rmw_rix(ocelot, cpu_flood, cpu_flood, ANA_PGID_PGID, PGID_MC);
	ocelot_rmw_rix(ocelot, cpu_flood, cpu_flood, ANA_PGID_PGID, PGID_BC);

	वापस 0;
पूर्ण

अटल व्योम felix_tearकरोwn_tag_npi(काष्ठा dsa_चयन *ds, पूर्णांक cpu)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	felix_npi_port_deinit(ocelot, cpu);
पूर्ण

अटल पूर्णांक felix_set_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक cpu,
				  क्रमागत dsa_tag_protocol proto)
अणु
	पूर्णांक err;

	चयन (proto) अणु
	हाल DSA_TAG_PROTO_SEVILLE:
	हाल DSA_TAG_PROTO_OCELOT:
		err = felix_setup_tag_npi(ds, cpu);
		अवरोध;
	हाल DSA_TAG_PROTO_OCELOT_8021Q:
		err = felix_setup_tag_8021q(ds, cpu);
		अवरोध;
	शेष:
		err = -EPROTONOSUPPORT;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम felix_del_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक cpu,
				   क्रमागत dsa_tag_protocol proto)
अणु
	चयन (proto) अणु
	हाल DSA_TAG_PROTO_SEVILLE:
	हाल DSA_TAG_PROTO_OCELOT:
		felix_tearकरोwn_tag_npi(ds, cpu);
		अवरोध;
	हाल DSA_TAG_PROTO_OCELOT_8021Q:
		felix_tearकरोwn_tag_8021q(ds, cpu);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* This always leaves the चयन in a consistent state, because although the
 * tag_8021q setup can fail, the NPI setup can't. So either the change is made,
 * or the restoration is guaranteed to work.
 */
अटल पूर्णांक felix_change_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक cpu,
				     क्रमागत dsa_tag_protocol proto)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	क्रमागत dsa_tag_protocol old_proto = felix->tag_proto;
	पूर्णांक err;

	अगर (proto != DSA_TAG_PROTO_SEVILLE &&
	    proto != DSA_TAG_PROTO_OCELOT &&
	    proto != DSA_TAG_PROTO_OCELOT_8021Q)
		वापस -EPROTONOSUPPORT;

	felix_del_tag_protocol(ds, cpu, old_proto);

	err = felix_set_tag_protocol(ds, cpu, proto);
	अगर (err) अणु
		felix_set_tag_protocol(ds, cpu, old_proto);
		वापस err;
	पूर्ण

	felix->tag_proto = proto;

	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol felix_get_tag_protocol(काष्ठा dsa_चयन *ds,
						    पूर्णांक port,
						    क्रमागत dsa_tag_protocol mp)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);

	वापस felix->tag_proto;
पूर्ण

अटल पूर्णांक felix_set_ageing_समय(काष्ठा dsa_चयन *ds,
				 अचिन्हित पूर्णांक ageing_समय)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_set_ageing_समय(ocelot, ageing_समय);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_fdb_dump(ocelot, port, cb, data);
पूर्ण

अटल पूर्णांक felix_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_fdb_add(ocelot, port, addr, vid);
पूर्ण

अटल पूर्णांक felix_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_fdb_del(ocelot, port, addr, vid);
पूर्ण

अटल पूर्णांक felix_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_mdb_add(ocelot, port, mdb);
पूर्ण

अटल पूर्णांक felix_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_mdb_del(ocelot, port, mdb);
पूर्ण

अटल व्योम felix_bridge_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       u8 state)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_bridge_stp_state_set(ocelot, port, state);
पूर्ण

अटल पूर्णांक felix_pre_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा चयनdev_brport_flags val,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_pre_bridge_flags(ocelot, port, val);
पूर्ण

अटल पूर्णांक felix_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा चयनdev_brport_flags val,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_bridge_flags(ocelot, port, val);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा net_device *br)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_bridge_join(ocelot, port, br);

	वापस 0;
पूर्ण

अटल व्योम felix_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा net_device *br)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_bridge_leave(ocelot, port, br);
पूर्ण

अटल पूर्णांक felix_lag_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  काष्ठा net_device *bond,
			  काष्ठा netdev_lag_upper_info *info)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_lag_join(ocelot, port, bond, info);
पूर्ण

अटल पूर्णांक felix_lag_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा net_device *bond)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_lag_leave(ocelot, port, bond);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_lag_change(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा dsa_port *dp = dsa_to_port(ds, port);
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_lag_change(ocelot, port, dp->lag_tx_enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_vlan_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	u16 flags = vlan->flags;

	/* Ocelot चयनes copy frames as-is to the CPU, so the flags:
	 * egress-untagged or not, pvid or not, make no dअगरference. This
	 * behavior is alपढ़ोy better than what DSA just tries to approximate
	 * when it installs the VLAN with the same flags on the CPU port.
	 * Just accept any configuration, and करोn't let ocelot deny installing
	 * multiple native VLANs on the NPI port, because the चयन करोesn't
	 * look at the port tag settings towards the NPI पूर्णांकerface anyway.
	 */
	अगर (port == ocelot->npi)
		वापस 0;

	वापस ocelot_vlan_prepare(ocelot, port, vlan->vid,
				   flags & BRIDGE_VLAN_INFO_PVID,
				   flags & BRIDGE_VLAN_INFO_UNTAGGED);
पूर्ण

अटल पूर्णांक felix_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool enabled,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_vlan_filtering(ocelot, port, enabled);
पूर्ण

अटल पूर्णांक felix_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	u16 flags = vlan->flags;
	पूर्णांक err;

	err = felix_vlan_prepare(ds, port, vlan);
	अगर (err)
		वापस err;

	वापस ocelot_vlan_add(ocelot, port, vlan->vid,
			       flags & BRIDGE_VLAN_INFO_PVID,
			       flags & BRIDGE_VLAN_INFO_UNTAGGED);
पूर्ण

अटल पूर्णांक felix_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_vlan_del(ocelot, port, vlan->vid);
पूर्ण

अटल पूर्णांक felix_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा phy_device *phy)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_enable(ocelot, port, phy);

	वापस 0;
पूर्ण

अटल व्योम felix_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_port_disable(ocelot, port);
पूर्ण

अटल व्योम felix_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   अचिन्हित दीर्घ *supported,
				   काष्ठा phylink_link_state *state)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);

	अगर (felix->info->phylink_validate)
		felix->info->phylink_validate(ocelot, port, supported, state);
पूर्ण

अटल व्योम felix_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित पूर्णांक link_an_mode,
				     स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	काष्ठा dsa_port *dp = dsa_to_port(ds, port);

	अगर (felix->pcs[port])
		phylink_set_pcs(dp->pl, &felix->pcs[port]->pcs);
पूर्ण

अटल व्योम felix_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
					अचिन्हित पूर्णांक link_an_mode,
					phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	पूर्णांक err;

	ocelot_port_rmwl(ocelot_port, 0, DEV_MAC_ENA_CFG_RX_ENA,
			 DEV_MAC_ENA_CFG);

	ocelot_fields_ग_लिखो(ocelot, port, QSYS_SWITCH_PORT_MODE_PORT_ENA, 0);

	err = ocelot_port_flush(ocelot, port);
	अगर (err)
		dev_err(ocelot->dev, "failed to flush port %d: %d\n",
			port, err);

	/* Put the port in reset. */
	ocelot_port_ग_लिखोl(ocelot_port,
			   DEV_CLOCK_CFG_MAC_TX_RST |
			   DEV_CLOCK_CFG_MAC_RX_RST |
			   DEV_CLOCK_CFG_LINK_SPEED(OCELOT_SPEED_1000),
			   DEV_CLOCK_CFG);
पूर्ण

अटल व्योम felix_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      अचिन्हित पूर्णांक link_an_mode,
				      phy_पूर्णांकerface_t पूर्णांकerface,
				      काष्ठा phy_device *phydev,
				      पूर्णांक speed, पूर्णांक duplex,
				      bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	u32 mac_fc_cfg;

	/* Take port out of reset by clearing the MAC_TX_RST, MAC_RX_RST and
	 * PORT_RST bits in DEV_CLOCK_CFG. Note that the way this प्रणाली is
	 * पूर्णांकegrated is that the MAC speed is fixed and it's the PCS who is
	 * perक्रमming the rate adaptation, so we have to ग_लिखो "1000Mbps" पूर्णांकo
	 * the LINK_SPEED field of DEV_CLOCK_CFG (which is also its शेष
	 * value).
	 */
	ocelot_port_ग_लिखोl(ocelot_port,
			   DEV_CLOCK_CFG_LINK_SPEED(OCELOT_SPEED_1000),
			   DEV_CLOCK_CFG);

	चयन (speed) अणु
	हाल SPEED_10:
		mac_fc_cfg = SYS_MAC_FC_CFG_FC_LINK_SPEED(3);
		अवरोध;
	हाल SPEED_100:
		mac_fc_cfg = SYS_MAC_FC_CFG_FC_LINK_SPEED(2);
		अवरोध;
	हाल SPEED_1000:
	हाल SPEED_2500:
		mac_fc_cfg = SYS_MAC_FC_CFG_FC_LINK_SPEED(1);
		अवरोध;
	शेष:
		dev_err(ocelot->dev, "Unsupported speed on port %d: %d\n",
			port, speed);
		वापस;
	पूर्ण

	/* handle Rx छोड़ो in all हालs, with 2500base-X this is used क्रम rate
	 * adaptation.
	 */
	mac_fc_cfg |= SYS_MAC_FC_CFG_RX_FC_ENA;

	अगर (tx_छोड़ो)
		mac_fc_cfg |= SYS_MAC_FC_CFG_TX_FC_ENA |
			      SYS_MAC_FC_CFG_PAUSE_VAL_CFG(0xffff) |
			      SYS_MAC_FC_CFG_FC_LATENCY_CFG(0x7) |
			      SYS_MAC_FC_CFG_ZERO_PAUSE_ENA;

	/* Flow control. Link speed is only used here to evaluate the समय
	 * specअगरication in incoming छोड़ो frames.
	 */
	ocelot_ग_लिखो_rix(ocelot, mac_fc_cfg, SYS_MAC_FC_CFG, port);

	ocelot_ग_लिखो_rix(ocelot, 0, ANA_POL_FLOWC, port);

	/* Unकरो the effects of felix_phylink_mac_link_करोwn:
	 * enable MAC module
	 */
	ocelot_port_ग_लिखोl(ocelot_port, DEV_MAC_ENA_CFG_RX_ENA |
			   DEV_MAC_ENA_CFG_TX_ENA, DEV_MAC_ENA_CFG);

	/* Enable receiving frames on the port, and activate स्वतः-learning of
	 * MAC addresses.
	 */
	ocelot_ग_लिखो_gix(ocelot, ANA_PORT_PORT_CFG_LEARNAUTO |
			 ANA_PORT_PORT_CFG_RECV_ENA |
			 ANA_PORT_PORT_CFG_PORTID_VAL(port),
			 ANA_PORT_PORT_CFG, port);

	/* Core: Enable port क्रम frame transfer */
	ocelot_fields_ग_लिखो(ocelot, port,
			    QSYS_SWITCH_PORT_MODE_PORT_ENA, 1);

	अगर (felix->info->port_sched_speed_set)
		felix->info->port_sched_speed_set(ocelot, port, speed);
पूर्ण

अटल व्योम felix_port_qos_map_init(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	पूर्णांक i;

	ocelot_rmw_gix(ocelot,
		       ANA_PORT_QOS_CFG_QOS_PCP_ENA,
		       ANA_PORT_QOS_CFG_QOS_PCP_ENA,
		       ANA_PORT_QOS_CFG,
		       port);

	क्रम (i = 0; i < OCELOT_NUM_TC * 2; i++) अणु
		ocelot_rmw_ix(ocelot,
			      (ANA_PORT_PCP_DEI_MAP_DP_PCP_DEI_VAL & i) |
			      ANA_PORT_PCP_DEI_MAP_QOS_PCP_DEI_VAL(i),
			      ANA_PORT_PCP_DEI_MAP_DP_PCP_DEI_VAL |
			      ANA_PORT_PCP_DEI_MAP_QOS_PCP_DEI_VAL_M,
			      ANA_PORT_PCP_DEI_MAP,
			      port, i);
	पूर्ण
पूर्ण

अटल व्योम felix_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      u32 stringset, u8 *data)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_get_strings(ocelot, port, stringset, data);
पूर्ण

अटल व्योम felix_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, u64 *data)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_get_ethtool_stats(ocelot, port, data);
पूर्ण

अटल पूर्णांक felix_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_get_sset_count(ocelot, port, sset);
पूर्ण

अटल पूर्णांक felix_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_get_ts_info(ocelot, port, info);
पूर्ण

अटल पूर्णांक felix_parse_ports_node(काष्ठा felix *felix,
				  काष्ठा device_node *ports_node,
				  phy_पूर्णांकerface_t *port_phy_modes)
अणु
	काष्ठा ocelot *ocelot = &felix->ocelot;
	काष्ठा device *dev = felix->ocelot.dev;
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(ports_node, child) अणु
		phy_पूर्णांकerface_t phy_mode;
		u32 port;
		पूर्णांक err;

		/* Get चयन port number from DT */
		अगर (of_property_पढ़ो_u32(child, "reg", &port) < 0) अणु
			dev_err(dev, "Port number not defined in device tree "
				"(property \"reg\")\n");
			of_node_put(child);
			वापस -ENODEV;
		पूर्ण

		/* Get PHY mode from DT */
		err = of_get_phy_mode(child, &phy_mode);
		अगर (err) अणु
			dev_err(dev, "Failed to read phy-mode or "
				"phy-interface-type property for port %d\n",
				port);
			of_node_put(child);
			वापस -ENODEV;
		पूर्ण

		err = felix->info->prevalidate_phy_mode(ocelot, port, phy_mode);
		अगर (err < 0) अणु
			dev_err(dev, "Unsupported PHY mode %s on port %d\n",
				phy_modes(phy_mode), port);
			of_node_put(child);
			वापस err;
		पूर्ण

		port_phy_modes[port] = phy_mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक felix_parse_dt(काष्ठा felix *felix, phy_पूर्णांकerface_t *port_phy_modes)
अणु
	काष्ठा device *dev = felix->ocelot.dev;
	काष्ठा device_node *चयन_node;
	काष्ठा device_node *ports_node;
	पूर्णांक err;

	चयन_node = dev->of_node;

	ports_node = of_get_child_by_name(चयन_node, "ports");
	अगर (!ports_node) अणु
		dev_err(dev, "Incorrect bindings: absent \"ports\" node\n");
		वापस -ENODEV;
	पूर्ण

	err = felix_parse_ports_node(felix, ports_node, port_phy_modes);
	of_node_put(ports_node);

	वापस err;
पूर्ण

अटल पूर्णांक felix_init_काष्ठाs(काष्ठा felix *felix, पूर्णांक num_phys_ports)
अणु
	काष्ठा ocelot *ocelot = &felix->ocelot;
	phy_पूर्णांकerface_t *port_phy_modes;
	काष्ठा resource res;
	पूर्णांक port, i, err;

	ocelot->num_phys_ports = num_phys_ports;
	ocelot->ports = devm_kसुस्मृति(ocelot->dev, num_phys_ports,
				     माप(काष्ठा ocelot_port *), GFP_KERNEL);
	अगर (!ocelot->ports)
		वापस -ENOMEM;

	ocelot->map		= felix->info->map;
	ocelot->stats_layout	= felix->info->stats_layout;
	ocelot->num_stats	= felix->info->num_stats;
	ocelot->num_mact_rows	= felix->info->num_mact_rows;
	ocelot->vcap		= felix->info->vcap;
	ocelot->ops		= felix->info->ops;
	ocelot->npi_inj_prefix	= OCELOT_TAG_PREFIX_SHORT;
	ocelot->npi_xtr_prefix	= OCELOT_TAG_PREFIX_SHORT;
	ocelot->devlink		= felix->ds->devlink;

	port_phy_modes = kसुस्मृति(num_phys_ports, माप(phy_पूर्णांकerface_t),
				 GFP_KERNEL);
	अगर (!port_phy_modes)
		वापस -ENOMEM;

	err = felix_parse_dt(felix, port_phy_modes);
	अगर (err) अणु
		kमुक्त(port_phy_modes);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < TARGET_MAX; i++) अणु
		काष्ठा regmap *target;

		अगर (!felix->info->target_io_res[i].name)
			जारी;

		स_नकल(&res, &felix->info->target_io_res[i], माप(res));
		res.flags = IORESOURCE_MEM;
		res.start += felix->चयन_base;
		res.end += felix->चयन_base;

		target = ocelot_regmap_init(ocelot, &res);
		अगर (IS_ERR(target)) अणु
			dev_err(ocelot->dev,
				"Failed to map device memory space\n");
			kमुक्त(port_phy_modes);
			वापस PTR_ERR(target);
		पूर्ण

		ocelot->tarमाला_लो[i] = target;
	पूर्ण

	err = ocelot_regfields_init(ocelot, felix->info->regfields);
	अगर (err) अणु
		dev_err(ocelot->dev, "failed to init reg fields map\n");
		kमुक्त(port_phy_modes);
		वापस err;
	पूर्ण

	क्रम (port = 0; port < num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port;
		काष्ठा regmap *target;

		ocelot_port = devm_kzalloc(ocelot->dev,
					   माप(काष्ठा ocelot_port),
					   GFP_KERNEL);
		अगर (!ocelot_port) अणु
			dev_err(ocelot->dev,
				"failed to allocate port memory\n");
			kमुक्त(port_phy_modes);
			वापस -ENOMEM;
		पूर्ण

		स_नकल(&res, &felix->info->port_io_res[port], माप(res));
		res.flags = IORESOURCE_MEM;
		res.start += felix->चयन_base;
		res.end += felix->चयन_base;

		target = ocelot_regmap_init(ocelot, &res);
		अगर (IS_ERR(target)) अणु
			dev_err(ocelot->dev,
				"Failed to map memory space for port %d\n",
				port);
			kमुक्त(port_phy_modes);
			वापस PTR_ERR(target);
		पूर्ण

		ocelot_port->phy_mode = port_phy_modes[port];
		ocelot_port->ocelot = ocelot;
		ocelot_port->target = target;
		ocelot->ports[port] = ocelot_port;
	पूर्ण

	kमुक्त(port_phy_modes);

	अगर (felix->info->mdio_bus_alloc) अणु
		err = felix->info->mdio_bus_alloc(ocelot);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Hardware initialization करोne here so that we can allocate काष्ठाures with
 * devm without fear of dsa_रेजिस्टर_चयन वापसing -EPROBE_DEFER and causing
 * us to allocate काष्ठाures twice (leak memory) and map PCI memory twice
 * (which will not work).
 */
अटल पूर्णांक felix_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	पूर्णांक port, err;

	err = felix_init_काष्ठाs(felix, ds->num_ports);
	अगर (err)
		वापस err;

	err = ocelot_init(ocelot);
	अगर (err)
		जाओ out_mdiobus_मुक्त;

	अगर (ocelot->ptp) अणु
		err = ocelot_init_बारtamp(ocelot, felix->info->ptp_caps);
		अगर (err) अणु
			dev_err(ocelot->dev,
				"Timestamp initialization failed\n");
			ocelot->ptp = 0;
		पूर्ण
	पूर्ण

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_is_unused_port(ds, port))
			जारी;

		ocelot_init_port(ocelot, port);

		/* Set the शेष QoS Classअगरication based on PCP and DEI
		 * bits of vlan tag.
		 */
		felix_port_qos_map_init(ocelot, port);
	पूर्ण

	err = ocelot_devlink_sb_रेजिस्टर(ocelot);
	अगर (err)
		जाओ out_deinit_ports;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_cpu_port(ds, port))
			जारी;

		/* The initial tag protocol is NPI which always वापसs 0, so
		 * there's no real poपूर्णांक in checking क्रम errors.
		 */
		felix_set_tag_protocol(ds, port, felix->tag_proto);
	पूर्ण

	ds->mtu_enक्रमcement_ingress = true;
	ds->assisted_learning_on_cpu_port = true;

	वापस 0;

out_deinit_ports:
	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		अगर (dsa_is_unused_port(ds, port))
			जारी;

		ocelot_deinit_port(ocelot, port);
	पूर्ण

	ocelot_deinit_बारtamp(ocelot);
	ocelot_deinit(ocelot);

out_mdiobus_मुक्त:
	अगर (felix->info->mdio_bus_मुक्त)
		felix->info->mdio_bus_मुक्त(ocelot);

	वापस err;
पूर्ण

अटल व्योम felix_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	पूर्णांक port;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_cpu_port(ds, port))
			जारी;

		felix_del_tag_protocol(ds, port, felix->tag_proto);
	पूर्ण

	ocelot_devlink_sb_unरेजिस्टर(ocelot);
	ocelot_deinit_बारtamp(ocelot);
	ocelot_deinit(ocelot);

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		अगर (dsa_is_unused_port(ds, port))
			जारी;

		ocelot_deinit_port(ocelot, port);
	पूर्ण

	अगर (felix->info->mdio_bus_मुक्त)
		felix->info->mdio_bus_मुक्त(ocelot);
पूर्ण

अटल पूर्णांक felix_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_hwstamp_get(ocelot, port, अगरr);
पूर्ण

अटल पूर्णांक felix_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_hwstamp_set(ocelot, port, अगरr);
पूर्ण

अटल bool felix_check_xtr_pkt(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक ptp_type)
अणु
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	पूर्णांक err, grp = 0;

	अगर (felix->tag_proto != DSA_TAG_PROTO_OCELOT_8021Q)
		वापस false;

	अगर (!felix->info->quirk_no_xtr_irq)
		वापस false;

	अगर (ptp_type == PTP_CLASS_NONE)
		वापस false;

	जबतक (ocelot_पढ़ो(ocelot, QS_XTR_DATA_PRESENT) & BIT(grp)) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक type;

		err = ocelot_xtr_poll_frame(ocelot, grp, &skb);
		अगर (err)
			जाओ out;

		/* We trap to the CPU port module all PTP frames, but
		 * felix_rxtstamp() only माला_लो called क्रम event frames.
		 * So we need to aव्योम sending duplicate general
		 * message frames by running a second BPF classअगरier
		 * here and dropping those.
		 */
		__skb_push(skb, ETH_HLEN);

		type = ptp_classअगरy_raw(skb);

		__skb_pull(skb, ETH_HLEN);

		अगर (type == PTP_CLASS_NONE) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		netअगर_rx(skb);
	पूर्ण

out:
	अगर (err < 0)
		ocelot_drain_cpu_queue(ocelot, 0);

	वापस true;
पूर्ण

अटल bool felix_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type)
अणु
	u8 *extraction = skb->data - ETH_HLEN - OCELOT_TAG_LEN;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा ocelot *ocelot = ds->priv;
	u32 tstamp_lo, tstamp_hi;
	काष्ठा बारpec64 ts;
	u64 tstamp, val;

	/* If the "no XTR IRQ" workaround is in use, tell DSA to defer this skb
	 * क्रम RX बारtamping. Then मुक्त it, and poll क्रम its copy through
	 * MMIO in the CPU port module, and inject that पूर्णांकo the stack from
	 * ocelot_xtr_poll().
	 */
	अगर (felix_check_xtr_pkt(ocelot, type)) अणु
		kमुक्त_skb(skb);
		वापस true;
	पूर्ण

	ocelot_ptp_समय_लो64(&ocelot->ptp_info, &ts);
	tstamp = kसमय_set(ts.tv_sec, ts.tv_nsec);

	ocelot_xfh_get_rew_val(extraction, &val);
	tstamp_lo = (u32)val;

	tstamp_hi = tstamp >> 32;
	अगर ((tstamp & 0xffffffff) < tstamp_lo)
		tstamp_hi--;

	tstamp = ((u64)tstamp_hi << 32) | tstamp_lo;

	shhwtstamps = skb_hwtstamps(skb);
	स_रखो(shhwtstamps, 0, माप(काष्ठा skb_shared_hwtstamps));
	shhwtstamps->hwtstamp = tstamp;
	वापस false;
पूर्ण

अटल व्योम felix_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा sk_buff *clone = शून्य;

	अगर (!ocelot->ptp)
		वापस;

	अगर (ocelot_port_txtstamp_request(ocelot, port, skb, &clone))
		वापस;

	अगर (clone)
		OCELOT_SKB_CB(skb)->clone = clone;
पूर्ण

अटल पूर्णांक felix_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_set_maxlen(ocelot, port, new_mtu);

	वापस 0;
पूर्ण

अटल पूर्णांक felix_get_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_get_max_mtu(ocelot, port);
पूर्ण

अटल पूर्णांक felix_cls_flower_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_cls_flower_replace(ocelot, port, cls, ingress);
पूर्ण

अटल पूर्णांक felix_cls_flower_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_cls_flower_destroy(ocelot, port, cls, ingress);
पूर्ण

अटल पूर्णांक felix_cls_flower_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_cls_flower_stats(ocelot, port, cls, ingress);
पूर्ण

अटल पूर्णांक felix_port_policer_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा dsa_mall_policer_tc_entry *policer)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा ocelot_policer pol = अणु
		.rate = भाग_u64(policer->rate_bytes_per_sec, 1000) * 8,
		.burst = policer->burst,
	पूर्ण;

	वापस ocelot_port_policer_add(ocelot, port, &pol);
पूर्ण

अटल व्योम felix_port_policer_del(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	ocelot_port_policer_del(ocelot, port);
पूर्ण

अटल पूर्णांक felix_port_setup_tc(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       क्रमागत tc_setup_type type,
			       व्योम *type_data)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	काष्ठा felix *felix = ocelot_to_felix(ocelot);

	अगर (felix->info->port_setup_tc)
		वापस felix->info->port_setup_tc(ds, port, type, type_data);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक felix_sb_pool_get(काष्ठा dsa_चयन *ds, अचिन्हित पूर्णांक sb_index,
			     u16 pool_index,
			     काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_pool_get(ocelot, sb_index, pool_index, pool_info);
पूर्ण

अटल पूर्णांक felix_sb_pool_set(काष्ठा dsa_चयन *ds, अचिन्हित पूर्णांक sb_index,
			     u16 pool_index, u32 size,
			     क्रमागत devlink_sb_threshold_type threshold_type,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_pool_set(ocelot, sb_index, pool_index, size,
				  threshold_type, extack);
पूर्ण

अटल पूर्णांक felix_sb_port_pool_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित पूर्णांक sb_index, u16 pool_index,
				  u32 *p_threshold)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_port_pool_get(ocelot, port, sb_index, pool_index,
				       p_threshold);
पूर्ण

अटल पूर्णांक felix_sb_port_pool_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित पूर्णांक sb_index, u16 pool_index,
				  u32 threshold, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_port_pool_set(ocelot, port, sb_index, pool_index,
				       threshold, extack);
पूर्ण

अटल पूर्णांक felix_sb_tc_pool_bind_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित पूर्णांक sb_index, u16 tc_index,
				     क्रमागत devlink_sb_pool_type pool_type,
				     u16 *p_pool_index, u32 *p_threshold)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_tc_pool_bind_get(ocelot, port, sb_index, tc_index,
					  pool_type, p_pool_index,
					  p_threshold);
पूर्ण

अटल पूर्णांक felix_sb_tc_pool_bind_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित पूर्णांक sb_index, u16 tc_index,
				     क्रमागत devlink_sb_pool_type pool_type,
				     u16 pool_index, u32 threshold,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_tc_pool_bind_set(ocelot, port, sb_index, tc_index,
					  pool_type, pool_index, threshold,
					  extack);
पूर्ण

अटल पूर्णांक felix_sb_occ_snapshot(काष्ठा dsa_चयन *ds,
				 अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_occ_snapshot(ocelot, sb_index);
पूर्ण

अटल पूर्णांक felix_sb_occ_max_clear(काष्ठा dsa_चयन *ds,
				  अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_occ_max_clear(ocelot, sb_index);
पूर्ण

अटल पूर्णांक felix_sb_occ_port_pool_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      अचिन्हित पूर्णांक sb_index, u16 pool_index,
				      u32 *p_cur, u32 *p_max)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_occ_port_pool_get(ocelot, port, sb_index, pool_index,
					   p_cur, p_max);
पूर्ण

अटल पूर्णांक felix_sb_occ_tc_port_bind_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 अचिन्हित पूर्णांक sb_index, u16 tc_index,
					 क्रमागत devlink_sb_pool_type pool_type,
					 u32 *p_cur, u32 *p_max)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_sb_occ_tc_port_bind_get(ocelot, port, sb_index, tc_index,
					      pool_type, p_cur, p_max);
पूर्ण

अटल पूर्णांक felix_mrp_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_mrp_add(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक felix_mrp_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_mrp_add(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक
felix_mrp_add_ring_role(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_mrp_add_ring_role(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक
felix_mrp_del_ring_role(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	वापस ocelot_mrp_del_ring_role(ocelot, port, mrp);
पूर्ण

स्थिर काष्ठा dsa_चयन_ops felix_चयन_ops = अणु
	.get_tag_protocol		= felix_get_tag_protocol,
	.change_tag_protocol		= felix_change_tag_protocol,
	.setup				= felix_setup,
	.tearकरोwn			= felix_tearकरोwn,
	.set_ageing_समय		= felix_set_ageing_समय,
	.get_strings			= felix_get_strings,
	.get_ethtool_stats		= felix_get_ethtool_stats,
	.get_sset_count			= felix_get_sset_count,
	.get_ts_info			= felix_get_ts_info,
	.phylink_validate		= felix_phylink_validate,
	.phylink_mac_config		= felix_phylink_mac_config,
	.phylink_mac_link_करोwn		= felix_phylink_mac_link_करोwn,
	.phylink_mac_link_up		= felix_phylink_mac_link_up,
	.port_enable			= felix_port_enable,
	.port_disable			= felix_port_disable,
	.port_fdb_dump			= felix_fdb_dump,
	.port_fdb_add			= felix_fdb_add,
	.port_fdb_del			= felix_fdb_del,
	.port_mdb_add			= felix_mdb_add,
	.port_mdb_del			= felix_mdb_del,
	.port_pre_bridge_flags		= felix_pre_bridge_flags,
	.port_bridge_flags		= felix_bridge_flags,
	.port_bridge_join		= felix_bridge_join,
	.port_bridge_leave		= felix_bridge_leave,
	.port_lag_join			= felix_lag_join,
	.port_lag_leave			= felix_lag_leave,
	.port_lag_change		= felix_lag_change,
	.port_stp_state_set		= felix_bridge_stp_state_set,
	.port_vlan_filtering		= felix_vlan_filtering,
	.port_vlan_add			= felix_vlan_add,
	.port_vlan_del			= felix_vlan_del,
	.port_hwtstamp_get		= felix_hwtstamp_get,
	.port_hwtstamp_set		= felix_hwtstamp_set,
	.port_rxtstamp			= felix_rxtstamp,
	.port_txtstamp			= felix_txtstamp,
	.port_change_mtu		= felix_change_mtu,
	.port_max_mtu			= felix_get_max_mtu,
	.port_policer_add		= felix_port_policer_add,
	.port_policer_del		= felix_port_policer_del,
	.cls_flower_add			= felix_cls_flower_add,
	.cls_flower_del			= felix_cls_flower_del,
	.cls_flower_stats		= felix_cls_flower_stats,
	.port_setup_tc			= felix_port_setup_tc,
	.devlink_sb_pool_get		= felix_sb_pool_get,
	.devlink_sb_pool_set		= felix_sb_pool_set,
	.devlink_sb_port_pool_get	= felix_sb_port_pool_get,
	.devlink_sb_port_pool_set	= felix_sb_port_pool_set,
	.devlink_sb_tc_pool_bind_get	= felix_sb_tc_pool_bind_get,
	.devlink_sb_tc_pool_bind_set	= felix_sb_tc_pool_bind_set,
	.devlink_sb_occ_snapshot	= felix_sb_occ_snapshot,
	.devlink_sb_occ_max_clear	= felix_sb_occ_max_clear,
	.devlink_sb_occ_port_pool_get	= felix_sb_occ_port_pool_get,
	.devlink_sb_occ_tc_port_bind_get= felix_sb_occ_tc_port_bind_get,
	.port_mrp_add			= felix_mrp_add,
	.port_mrp_del			= felix_mrp_del,
	.port_mrp_add_ring_role		= felix_mrp_add_ring_role,
	.port_mrp_del_ring_role		= felix_mrp_del_ring_role,
पूर्ण;

काष्ठा net_device *felix_port_to_netdev(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	काष्ठा dsa_चयन *ds = felix->ds;

	अगर (!dsa_is_user_port(ds, port))
		वापस शून्य;

	वापस dsa_to_port(ds, port)->slave;
पूर्ण

पूर्णांक felix_netdev_to_port(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp;

	dp = dsa_port_from_netdev(dev);
	अगर (IS_ERR(dp))
		वापस -EINVAL;

	वापस dp->index;
पूर्ण
