<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Felix Fietkau <nbd@nbd.name> */

#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश "mtk_eth_soc.h"

काष्ठा mtk_flow_addr_info
अणु
	व्योम *src, *dest;
	u16 *src_port, *dest_port;
	bool ipv6;
पूर्ण;

अटल स्थिर अक्षर *mtk_foe_entry_state_str(पूर्णांक state)
अणु
	अटल स्थिर अक्षर * स्थिर state_str[] = अणु
		[MTK_FOE_STATE_INVALID] = "INV",
		[MTK_FOE_STATE_UNBIND] = "UNB",
		[MTK_FOE_STATE_BIND] = "BND",
		[MTK_FOE_STATE_FIN] = "FIN",
	पूर्ण;

	अगर (state >= ARRAY_SIZE(state_str) || !state_str[state])
		वापस "UNK";

	वापस state_str[state];
पूर्ण

अटल स्थिर अक्षर *mtk_foe_pkt_type_str(पूर्णांक type)
अणु
	अटल स्थिर अक्षर * स्थिर type_str[] = अणु
		[MTK_PPE_PKT_TYPE_IPV4_HNAPT] = "IPv4 5T",
		[MTK_PPE_PKT_TYPE_IPV4_ROUTE] = "IPv4 3T",
		[MTK_PPE_PKT_TYPE_BRIDGE] = "L2",
		[MTK_PPE_PKT_TYPE_IPV4_DSLITE] = "DS-LITE",
		[MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T] = "IPv6 3T",
		[MTK_PPE_PKT_TYPE_IPV6_ROUTE_5T] = "IPv6 5T",
		[MTK_PPE_PKT_TYPE_IPV6_6RD] = "6RD",
	पूर्ण;

	अगर (type >= ARRAY_SIZE(type_str) || !type_str[type])
		वापस "UNKNOWN";

	वापस type_str[type];
पूर्ण

अटल व्योम
mtk_prपूर्णांक_addr(काष्ठा seq_file *m, u32 *addr, bool ipv6)
अणु
	u32 n_addr[4];
	पूर्णांक i;

	अगर (!ipv6) अणु
		seq_म_लिखो(m, "%pI4h", addr);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(n_addr); i++)
		n_addr[i] = htonl(addr[i]);
	seq_म_लिखो(m, "%pI6", n_addr);
पूर्ण

अटल व्योम
mtk_prपूर्णांक_addr_info(काष्ठा seq_file *m, काष्ठा mtk_flow_addr_info *ai)
अणु
	mtk_prपूर्णांक_addr(m, ai->src, ai->ipv6);
	अगर (ai->src_port)
		seq_म_लिखो(m, ":%d", *ai->src_port);
	seq_म_लिखो(m, "->");
	mtk_prपूर्णांक_addr(m, ai->dest, ai->ipv6);
	अगर (ai->dest_port)
		seq_म_लिखो(m, ":%d", *ai->dest_port);
पूर्ण

अटल पूर्णांक
mtk_ppe_debugfs_foe_show(काष्ठा seq_file *m, व्योम *निजी, bool bind)
अणु
	काष्ठा mtk_ppe *ppe = m->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_PPE_ENTRIES; i++) अणु
		काष्ठा mtk_foe_entry *entry = &ppe->foe_table[i];
		काष्ठा mtk_foe_mac_info *l2;
		काष्ठा mtk_flow_addr_info ai = अणुपूर्ण;
		अचिन्हित अक्षर h_source[ETH_ALEN];
		अचिन्हित अक्षर h_dest[ETH_ALEN];
		पूर्णांक type, state;
		u32 ib2;


		state = FIELD_GET(MTK_FOE_IB1_STATE, entry->ib1);
		अगर (!state)
			जारी;

		अगर (bind && state != MTK_FOE_STATE_BIND)
			जारी;

		type = FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, entry->ib1);
		seq_म_लिखो(m, "%05x %s %7s", i,
			   mtk_foe_entry_state_str(state),
			   mtk_foe_pkt_type_str(type));

		चयन (type) अणु
		हाल MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		हाल MTK_PPE_PKT_TYPE_IPV4_DSLITE:
			ai.src_port = &entry->ipv4.orig.src_port;
			ai.dest_port = &entry->ipv4.orig.dest_port;
			fallthrough;
		हाल MTK_PPE_PKT_TYPE_IPV4_ROUTE:
			ai.src = &entry->ipv4.orig.src_ip;
			ai.dest = &entry->ipv4.orig.dest_ip;
			अवरोध;
		हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_5T:
			ai.src_port = &entry->ipv6.src_port;
			ai.dest_port = &entry->ipv6.dest_port;
			fallthrough;
		हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T:
		हाल MTK_PPE_PKT_TYPE_IPV6_6RD:
			ai.src = &entry->ipv6.src_ip;
			ai.dest = &entry->ipv6.dest_ip;
			ai.ipv6 = true;
			अवरोध;
		पूर्ण

		seq_म_लिखो(m, " orig=");
		mtk_prपूर्णांक_addr_info(m, &ai);

		चयन (type) अणु
		हाल MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		हाल MTK_PPE_PKT_TYPE_IPV4_DSLITE:
			ai.src_port = &entry->ipv4.new.src_port;
			ai.dest_port = &entry->ipv4.new.dest_port;
			fallthrough;
		हाल MTK_PPE_PKT_TYPE_IPV4_ROUTE:
			ai.src = &entry->ipv4.new.src_ip;
			ai.dest = &entry->ipv4.new.dest_ip;
			seq_म_लिखो(m, " new=");
			mtk_prपूर्णांक_addr_info(m, &ai);
			अवरोध;
		पूर्ण

		अगर (type >= MTK_PPE_PKT_TYPE_IPV4_DSLITE) अणु
			l2 = &entry->ipv6.l2;
			ib2 = entry->ipv6.ib2;
		पूर्ण अन्यथा अणु
			l2 = &entry->ipv4.l2;
			ib2 = entry->ipv4.ib2;
		पूर्ण

		*((__be32 *)h_source) = htonl(l2->src_mac_hi);
		*((__be16 *)&h_source[4]) = htons(l2->src_mac_lo);
		*((__be32 *)h_dest) = htonl(l2->dest_mac_hi);
		*((__be16 *)&h_dest[4]) = htons(l2->dest_mac_lo);

		seq_म_लिखो(m, " eth=%pM->%pM etype=%04x"
			      " vlan=%d,%d ib1=%08x ib2=%08x\n",
			   h_source, h_dest, ntohs(l2->etype),
			   l2->vlan1, l2->vlan2, entry->ib1, ib2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_ppe_debugfs_foe_show_all(काष्ठा seq_file *m, व्योम *निजी)
अणु
	वापस mtk_ppe_debugfs_foe_show(m, निजी, false);
पूर्ण

अटल पूर्णांक
mtk_ppe_debugfs_foe_show_bind(काष्ठा seq_file *m, व्योम *निजी)
अणु
	वापस mtk_ppe_debugfs_foe_show(m, निजी, true);
पूर्ण

अटल पूर्णांक
mtk_ppe_debugfs_foe_खोलो_all(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mtk_ppe_debugfs_foe_show_all,
			   inode->i_निजी);
पूर्ण

अटल पूर्णांक
mtk_ppe_debugfs_foe_खोलो_bind(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mtk_ppe_debugfs_foe_show_bind,
			   inode->i_निजी);
पूर्ण

पूर्णांक mtk_ppe_debugfs_init(काष्ठा mtk_ppe *ppe)
अणु
	अटल स्थिर काष्ठा file_operations fops_all = अणु
		.खोलो = mtk_ppe_debugfs_foe_खोलो_all,
		.पढ़ो = seq_पढ़ो,
		.llseek = seq_lseek,
		.release = single_release,
	पूर्ण;

	अटल स्थिर काष्ठा file_operations fops_bind = अणु
		.खोलो = mtk_ppe_debugfs_foe_खोलो_bind,
		.पढ़ो = seq_पढ़ो,
		.llseek = seq_lseek,
		.release = single_release,
	पूर्ण;

	काष्ठा dentry *root;

	root = debugfs_create_dir("mtk_ppe", शून्य);
	अगर (!root)
		वापस -ENOMEM;

	debugfs_create_file("entries", S_IRUGO, root, ppe, &fops_all);
	debugfs_create_file("bind", S_IRUGO, root, ppe, &fops_bind);

	वापस 0;
पूर्ण
