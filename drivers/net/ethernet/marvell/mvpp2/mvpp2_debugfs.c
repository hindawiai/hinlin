<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Marvell PPv2 network controller क्रम Armada 375 SoC.
 *
 * Copyright (C) 2018 Marvell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>

#समावेश "mvpp2.h"
#समावेश "mvpp2_prs.h"
#समावेश "mvpp2_cls.h"

काष्ठा mvpp2_dbgfs_prs_entry अणु
	पूर्णांक tid;
	काष्ठा mvpp2 *priv;
पूर्ण;

काष्ठा mvpp2_dbgfs_c2_entry अणु
	पूर्णांक id;
	काष्ठा mvpp2 *priv;
पूर्ण;

काष्ठा mvpp2_dbgfs_flow_entry अणु
	पूर्णांक flow;
	काष्ठा mvpp2 *priv;
पूर्ण;

काष्ठा mvpp2_dbgfs_flow_tbl_entry अणु
	पूर्णांक id;
	काष्ठा mvpp2 *priv;
पूर्ण;

काष्ठा mvpp2_dbgfs_port_flow_entry अणु
	काष्ठा mvpp2_port *port;
	काष्ठा mvpp2_dbgfs_flow_entry *dbg_fe;
पूर्ण;

काष्ठा mvpp2_dbgfs_entries अणु
	/* Entries क्रम Header Parser debug info */
	काष्ठा mvpp2_dbgfs_prs_entry prs_entries[MVPP2_PRS_TCAM_SRAM_SIZE];

	/* Entries क्रम Classअगरier C2 engine debug info */
	काष्ठा mvpp2_dbgfs_c2_entry c2_entries[MVPP22_CLS_C2_N_ENTRIES];

	/* Entries क्रम Classअगरier Flow Table debug info */
	काष्ठा mvpp2_dbgfs_flow_tbl_entry flt_entries[MVPP2_CLS_FLOWS_TBL_SIZE];

	/* Entries क्रम Classअगरier flows debug info */
	काष्ठा mvpp2_dbgfs_flow_entry flow_entries[MVPP2_N_PRS_FLOWS];

	/* Entries क्रम per-port flows debug info */
	काष्ठा mvpp2_dbgfs_port_flow_entry port_flow_entries[MVPP2_MAX_PORTS];
पूर्ण;

अटल पूर्णांक mvpp2_dbgfs_flow_flt_hits_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_flow_tbl_entry *entry = s->निजी;

	u32 hits = mvpp2_cls_flow_hits(entry->priv, entry->id);

	seq_म_लिखो(s, "%u\n", hits);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_flt_hits);

अटल पूर्णांक mvpp2_dbgfs_flow_dec_hits_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_flow_entry *entry = s->निजी;

	u32 hits = mvpp2_cls_lookup_hits(entry->priv, entry->flow);

	seq_म_लिखो(s, "%u\n", hits);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_dec_hits);

अटल पूर्णांक mvpp2_dbgfs_flow_type_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_flow_entry *entry = s->निजी;
	स्थिर काष्ठा mvpp2_cls_flow *f;
	स्थिर अक्षर *flow_name;

	f = mvpp2_cls_flow_get(entry->flow);
	अगर (!f)
		वापस -EINVAL;

	चयन (f->flow_type) अणु
	हाल IPV4_FLOW:
		flow_name = "ipv4";
		अवरोध;
	हाल IPV6_FLOW:
		flow_name = "ipv6";
		अवरोध;
	हाल TCP_V4_FLOW:
		flow_name = "tcp4";
		अवरोध;
	हाल TCP_V6_FLOW:
		flow_name = "tcp6";
		अवरोध;
	हाल UDP_V4_FLOW:
		flow_name = "udp4";
		अवरोध;
	हाल UDP_V6_FLOW:
		flow_name = "udp6";
		अवरोध;
	शेष:
		flow_name = "other";
	पूर्ण

	seq_म_लिखो(s, "%s\n", flow_name);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_type);

अटल पूर्णांक mvpp2_dbgfs_flow_id_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	स्थिर काष्ठा mvpp2_dbgfs_flow_entry *entry = s->निजी;
	स्थिर काष्ठा mvpp2_cls_flow *f;

	f = mvpp2_cls_flow_get(entry->flow);
	अगर (!f)
		वापस -EINVAL;

	seq_म_लिखो(s, "%d\n", f->flow_id);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_id);

अटल पूर्णांक mvpp2_dbgfs_port_flow_hash_opt_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_port_flow_entry *entry = s->निजी;
	काष्ठा mvpp2_port *port = entry->port;
	काष्ठा mvpp2_cls_flow_entry fe;
	स्थिर काष्ठा mvpp2_cls_flow *f;
	पूर्णांक flow_index;
	u16 hash_opts;

	f = mvpp2_cls_flow_get(entry->dbg_fe->flow);
	अगर (!f)
		वापस -EINVAL;

	flow_index = MVPP2_CLS_FLT_HASH_ENTRY(entry->port->id, f->flow_id);

	mvpp2_cls_flow_पढ़ो(port->priv, flow_index, &fe);

	hash_opts = mvpp2_flow_get_hek_fields(&fe);

	seq_म_लिखो(s, "0x%04x\n", hash_opts);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_port_flow_hash_opt);

अटल पूर्णांक mvpp2_dbgfs_port_flow_engine_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_port_flow_entry *entry = s->निजी;
	काष्ठा mvpp2_port *port = entry->port;
	काष्ठा mvpp2_cls_flow_entry fe;
	स्थिर काष्ठा mvpp2_cls_flow *f;
	पूर्णांक flow_index, engine;

	f = mvpp2_cls_flow_get(entry->dbg_fe->flow);
	अगर (!f)
		वापस -EINVAL;

	flow_index = MVPP2_CLS_FLT_HASH_ENTRY(entry->port->id, f->flow_id);

	mvpp2_cls_flow_पढ़ो(port->priv, flow_index, &fe);

	engine = mvpp2_cls_flow_eng_get(&fe);

	seq_म_लिखो(s, "%d\n", engine);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_port_flow_engine);

अटल पूर्णांक mvpp2_dbgfs_flow_c2_hits_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_c2_entry *entry = s->निजी;
	u32 hits;

	hits = mvpp2_cls_c2_hit_count(entry->priv, entry->id);

	seq_म_लिखो(s, "%u\n", hits);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_c2_hits);

अटल पूर्णांक mvpp2_dbgfs_flow_c2_rxq_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_c2_entry *entry = s->निजी;
	काष्ठा mvpp2_cls_c2_entry c2;
	u8 qh, ql;

	mvpp2_cls_c2_पढ़ो(entry->priv, entry->id, &c2);

	qh = (c2.attr[0] >> MVPP22_CLS_C2_ATTR0_QHIGH_OFFS) &
	     MVPP22_CLS_C2_ATTR0_QHIGH_MASK;

	ql = (c2.attr[0] >> MVPP22_CLS_C2_ATTR0_QLOW_OFFS) &
	     MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	seq_म_लिखो(s, "%d\n", (qh << 3 | ql));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_c2_rxq);

अटल पूर्णांक mvpp2_dbgfs_flow_c2_enable_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_c2_entry *entry = s->निजी;
	काष्ठा mvpp2_cls_c2_entry c2;
	पूर्णांक enabled;

	mvpp2_cls_c2_पढ़ो(entry->priv, entry->id, &c2);

	enabled = !!(c2.attr[2] & MVPP22_CLS_C2_ATTR2_RSS_EN);

	seq_म_लिखो(s, "%d\n", enabled);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_flow_c2_enable);

अटल पूर्णांक mvpp2_dbgfs_port_vid_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_port *port = s->निजी;
	अचिन्हित अक्षर byte[2], enable[2];
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित दीर्घ pmap;
	u16 rvid;
	पूर्णांक tid;

	क्रम (tid = MVPP2_PRS_VID_PORT_FIRST(port->id);
	     tid <= MVPP2_PRS_VID_PORT_LAST(port->id); tid++) अणु
		mvpp2_prs_init_from_hw(priv, &pe, tid);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);

		अगर (!priv->prs_shaकरोw[tid].valid)
			जारी;

		अगर (!test_bit(port->id, &pmap))
			जारी;

		mvpp2_prs_tcam_data_byte_get(&pe, 2, &byte[0], &enable[0]);
		mvpp2_prs_tcam_data_byte_get(&pe, 3, &byte[1], &enable[1]);

		rvid = ((byte[0] & 0xf) << 8) + byte[1];

		seq_म_लिखो(s, "%u\n", rvid);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_port_vid);

अटल पूर्णांक mvpp2_dbgfs_port_parser_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_port *port = s->निजी;
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित दीर्घ pmap;
	पूर्णांक i;

	क्रम (i = 0; i < MVPP2_PRS_TCAM_SRAM_SIZE; i++) अणु
		mvpp2_prs_init_from_hw(port->priv, &pe, i);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);
		अगर (priv->prs_shaकरोw[i].valid && test_bit(port->id, &pmap))
			seq_म_लिखो(s, "%03d\n", i);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_port_parser);

अटल पूर्णांक mvpp2_dbgfs_filter_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_port *port = s->निजी;
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित दीर्घ pmap;
	पूर्णांक index, tid;

	क्रम (tid = MVPP2_PE_MAC_RANGE_START;
	     tid <= MVPP2_PE_MAC_RANGE_END; tid++) अणु
		अचिन्हित अक्षर da[ETH_ALEN], da_mask[ETH_ALEN];

		अगर (!priv->prs_shaकरोw[tid].valid ||
		    priv->prs_shaकरोw[tid].lu != MVPP2_PRS_LU_MAC ||
		    priv->prs_shaकरोw[tid].udf != MVPP2_PRS_UDF_MAC_DEF)
			जारी;

		mvpp2_prs_init_from_hw(priv, &pe, tid);

		pmap = mvpp2_prs_tcam_port_map_get(&pe);

		/* We only want entries active on this port */
		अगर (!test_bit(port->id, &pmap))
			जारी;

		/* Read mac addr from entry */
		क्रम (index = 0; index < ETH_ALEN; index++)
			mvpp2_prs_tcam_data_byte_get(&pe, index, &da[index],
						     &da_mask[index]);

		seq_म_लिखो(s, "%pM\n", da);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_filter);

अटल पूर्णांक mvpp2_dbgfs_prs_lu_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2 *priv = entry->priv;

	seq_म_लिखो(s, "%x\n", priv->prs_shaकरोw[entry->tid].lu);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_lu);

अटल पूर्णांक mvpp2_dbgfs_prs_pmap_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित पूर्णांक pmap;

	mvpp2_prs_init_from_hw(entry->priv, &pe, entry->tid);

	pmap = mvpp2_prs_tcam_port_map_get(&pe);
	pmap &= MVPP2_PRS_PORT_MASK;

	seq_म_लिखो(s, "%02x\n", pmap);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_pmap);

अटल पूर्णांक mvpp2_dbgfs_prs_ai_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित अक्षर ai, ai_mask;

	mvpp2_prs_init_from_hw(entry->priv, &pe, entry->tid);

	ai = pe.tcam[MVPP2_PRS_TCAM_AI_WORD] & MVPP2_PRS_AI_MASK;
	ai_mask = (pe.tcam[MVPP2_PRS_TCAM_AI_WORD] >> 16) & MVPP2_PRS_AI_MASK;

	seq_म_लिखो(s, "%02x %02x\n", ai, ai_mask);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_ai);

अटल पूर्णांक mvpp2_dbgfs_prs_hdata_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2_prs_entry pe;
	अचिन्हित अक्षर data[8], mask[8];
	पूर्णांक i;

	mvpp2_prs_init_from_hw(entry->priv, &pe, entry->tid);

	क्रम (i = 0; i < 8; i++)
		mvpp2_prs_tcam_data_byte_get(&pe, i, &data[i], &mask[i]);

	seq_म_लिखो(s, "%*phN %*phN\n", 8, data, 8, mask);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_hdata);

अटल पूर्णांक mvpp2_dbgfs_prs_sram_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2_prs_entry pe;

	mvpp2_prs_init_from_hw(entry->priv, &pe, entry->tid);

	seq_म_लिखो(s, "%*phN\n", 14, pe.sram);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_sram);

अटल पूर्णांक mvpp2_dbgfs_prs_hits_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	पूर्णांक val;

	val = mvpp2_prs_hits(entry->priv, entry->tid);
	अगर (val < 0)
		वापस val;

	seq_म_लिखो(s, "%d\n", val);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_hits);

अटल पूर्णांक mvpp2_dbgfs_prs_valid_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry = s->निजी;
	काष्ठा mvpp2 *priv = entry->priv;
	पूर्णांक tid = entry->tid;

	seq_म_लिखो(s, "%d\n", priv->prs_shaकरोw[tid].valid ? 1 : 0);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mvpp2_dbgfs_prs_valid);

अटल पूर्णांक mvpp2_dbgfs_flow_port_init(काष्ठा dentry *parent,
				      काष्ठा mvpp2_port *port,
				      काष्ठा mvpp2_dbgfs_flow_entry *entry)
अणु
	काष्ठा mvpp2_dbgfs_port_flow_entry *port_entry;
	काष्ठा dentry *port_dir;

	port_dir = debugfs_create_dir(port->dev->name, parent);

	port_entry = &port->priv->dbgfs_entries->port_flow_entries[port->id];

	port_entry->port = port;
	port_entry->dbg_fe = entry;

	debugfs_create_file("hash_opts", 0444, port_dir, port_entry,
			    &mvpp2_dbgfs_port_flow_hash_opt_fops);

	debugfs_create_file("engine", 0444, port_dir, port_entry,
			    &mvpp2_dbgfs_port_flow_engine_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_flow_entry_init(काष्ठा dentry *parent,
				       काष्ठा mvpp2 *priv, पूर्णांक flow)
अणु
	काष्ठा mvpp2_dbgfs_flow_entry *entry;
	काष्ठा dentry *flow_entry_dir;
	अक्षर flow_entry_name[10];
	पूर्णांक i, ret;

	प्र_लिखो(flow_entry_name, "%02d", flow);

	flow_entry_dir = debugfs_create_dir(flow_entry_name, parent);

	entry = &priv->dbgfs_entries->flow_entries[flow];

	entry->flow = flow;
	entry->priv = priv;

	debugfs_create_file("dec_hits", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_dec_hits_fops);

	debugfs_create_file("type", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_type_fops);

	debugfs_create_file("id", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_id_fops);

	/* Create entry क्रम each port */
	क्रम (i = 0; i < priv->port_count; i++) अणु
		ret = mvpp2_dbgfs_flow_port_init(flow_entry_dir,
						 priv->port_list[i], entry);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_flow_init(काष्ठा dentry *parent, काष्ठा mvpp2 *priv)
अणु
	काष्ठा dentry *flow_dir;
	पूर्णांक i, ret;

	flow_dir = debugfs_create_dir("flows", parent);

	क्रम (i = 0; i < MVPP2_N_PRS_FLOWS; i++) अणु
		ret = mvpp2_dbgfs_flow_entry_init(flow_dir, priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_prs_entry_init(काष्ठा dentry *parent,
				      काष्ठा mvpp2 *priv, पूर्णांक tid)
अणु
	काष्ठा mvpp2_dbgfs_prs_entry *entry;
	काष्ठा dentry *prs_entry_dir;
	अक्षर prs_entry_name[10];

	अगर (tid >= MVPP2_PRS_TCAM_SRAM_SIZE)
		वापस -EINVAL;

	प्र_लिखो(prs_entry_name, "%03d", tid);

	prs_entry_dir = debugfs_create_dir(prs_entry_name, parent);

	entry = &priv->dbgfs_entries->prs_entries[tid];

	entry->tid = tid;
	entry->priv = priv;

	/* Create each attr */
	debugfs_create_file("sram", 0444, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_sram_fops);

	debugfs_create_file("valid", 0644, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_valid_fops);

	debugfs_create_file("lookup_id", 0644, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_lu_fops);

	debugfs_create_file("ai", 0644, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_ai_fops);

	debugfs_create_file("header_data", 0644, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_hdata_fops);

	debugfs_create_file("hits", 0444, prs_entry_dir, entry,
			    &mvpp2_dbgfs_prs_hits_fops);

	debugfs_create_file("pmap", 0444, prs_entry_dir, entry,
			     &mvpp2_dbgfs_prs_pmap_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_prs_init(काष्ठा dentry *parent, काष्ठा mvpp2 *priv)
अणु
	काष्ठा dentry *prs_dir;
	पूर्णांक i, ret;

	prs_dir = debugfs_create_dir("parser", parent);

	क्रम (i = 0; i < MVPP2_PRS_TCAM_SRAM_SIZE; i++) अणु
		ret = mvpp2_dbgfs_prs_entry_init(prs_dir, priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_c2_entry_init(काष्ठा dentry *parent,
				     काष्ठा mvpp2 *priv, पूर्णांक id)
अणु
	काष्ठा mvpp2_dbgfs_c2_entry *entry;
	काष्ठा dentry *c2_entry_dir;
	अक्षर c2_entry_name[10];

	अगर (id >= MVPP22_CLS_C2_N_ENTRIES)
		वापस -EINVAL;

	प्र_लिखो(c2_entry_name, "%03d", id);

	c2_entry_dir = debugfs_create_dir(c2_entry_name, parent);
	अगर (!c2_entry_dir)
		वापस -ENOMEM;

	entry = &priv->dbgfs_entries->c2_entries[id];

	entry->id = id;
	entry->priv = priv;

	debugfs_create_file("hits", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_hits_fops);

	debugfs_create_file("default_rxq", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_rxq_fops);

	debugfs_create_file("rss_enable", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_enable_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_flow_tbl_entry_init(काष्ठा dentry *parent,
					   काष्ठा mvpp2 *priv, पूर्णांक id)
अणु
	काष्ठा mvpp2_dbgfs_flow_tbl_entry *entry;
	काष्ठा dentry *flow_tbl_entry_dir;
	अक्षर flow_tbl_entry_name[10];

	अगर (id >= MVPP2_CLS_FLOWS_TBL_SIZE)
		वापस -EINVAL;

	प्र_लिखो(flow_tbl_entry_name, "%03d", id);

	flow_tbl_entry_dir = debugfs_create_dir(flow_tbl_entry_name, parent);
	अगर (!flow_tbl_entry_dir)
		वापस -ENOMEM;

	entry = &priv->dbgfs_entries->flt_entries[id];

	entry->id = id;
	entry->priv = priv;

	debugfs_create_file("hits", 0444, flow_tbl_entry_dir, entry,
			    &mvpp2_dbgfs_flow_flt_hits_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_cls_init(काष्ठा dentry *parent, काष्ठा mvpp2 *priv)
अणु
	काष्ठा dentry *cls_dir, *c2_dir, *flow_tbl_dir;
	पूर्णांक i, ret;

	cls_dir = debugfs_create_dir("classifier", parent);
	अगर (!cls_dir)
		वापस -ENOMEM;

	c2_dir = debugfs_create_dir("c2", cls_dir);
	अगर (!c2_dir)
		वापस -ENOMEM;

	क्रम (i = 0; i < MVPP22_CLS_C2_N_ENTRIES; i++) अणु
		ret = mvpp2_dbgfs_c2_entry_init(c2_dir, priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	flow_tbl_dir = debugfs_create_dir("flow_table", cls_dir);
	अगर (!flow_tbl_dir)
		वापस -ENOMEM;

	क्रम (i = 0; i < MVPP2_CLS_FLOWS_TBL_SIZE; i++) अणु
		ret = mvpp2_dbgfs_flow_tbl_entry_init(flow_tbl_dir, priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_dbgfs_port_init(काष्ठा dentry *parent,
				 काष्ठा mvpp2_port *port)
अणु
	काष्ठा dentry *port_dir;

	port_dir = debugfs_create_dir(port->dev->name, parent);

	debugfs_create_file("parser_entries", 0444, port_dir, port,
			    &mvpp2_dbgfs_port_parser_fops);

	debugfs_create_file("mac_filter", 0444, port_dir, port,
			    &mvpp2_dbgfs_filter_fops);

	debugfs_create_file("vid_filter", 0444, port_dir, port,
			    &mvpp2_dbgfs_port_vid_fops);

	वापस 0;
पूर्ण

व्योम mvpp2_dbgfs_cleanup(काष्ठा mvpp2 *priv)
अणु
	debugfs_हटाओ_recursive(priv->dbgfs_dir);

	kमुक्त(priv->dbgfs_entries);
पूर्ण

व्योम mvpp2_dbgfs_init(काष्ठा mvpp2 *priv, स्थिर अक्षर *name)
अणु
	काष्ठा dentry *mvpp2_dir, *mvpp2_root;
	पूर्णांक ret, i;

	mvpp2_root = debugfs_lookup(MVPP2_DRIVER_NAME, शून्य);
	अगर (!mvpp2_root)
		mvpp2_root = debugfs_create_dir(MVPP2_DRIVER_NAME, शून्य);

	mvpp2_dir = debugfs_create_dir(name, mvpp2_root);

	priv->dbgfs_dir = mvpp2_dir;
	priv->dbgfs_entries = kzalloc(माप(*priv->dbgfs_entries), GFP_KERNEL);
	अगर (!priv->dbgfs_entries)
		जाओ err;

	ret = mvpp2_dbgfs_prs_init(mvpp2_dir, priv);
	अगर (ret)
		जाओ err;

	ret = mvpp2_dbgfs_cls_init(mvpp2_dir, priv);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < priv->port_count; i++) अणु
		ret = mvpp2_dbgfs_port_init(mvpp2_dir, priv->port_list[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = mvpp2_dbgfs_flow_init(mvpp2_dir, priv);
	अगर (ret)
		जाओ err;

	वापस;
err:
	mvpp2_dbgfs_cleanup(priv);
पूर्ण
