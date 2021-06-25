<शैली गुरु>
/*
 * debugfs code क्रम HSR & PRP
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Author(s):
 *	Murali Karicheri <m-karicheri2@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/debugfs.h>
#समावेश "hsr_main.h"
#समावेश "hsr_framereg.h"

अटल काष्ठा dentry *hsr_debugfs_root_dir;

/* hsr_node_table_show - Formats and prपूर्णांकs node_table entries */
अटल पूर्णांक
hsr_node_table_show(काष्ठा seq_file *sfp, व्योम *data)
अणु
	काष्ठा hsr_priv *priv = (काष्ठा hsr_priv *)sfp->निजी;
	काष्ठा hsr_node *node;

	seq_म_लिखो(sfp, "Node Table entries for (%s) device\n",
		   (priv->prot_version == PRP_V1 ? "PRP" : "HSR"));
	seq_माला_दो(sfp, "MAC-Address-A,    MAC-Address-B,    time_in[A], ");
	seq_माला_दो(sfp, "time_in[B], Address-B port, ");
	अगर (priv->prot_version == PRP_V1)
		seq_माला_दो(sfp, "SAN-A, SAN-B, DAN-P\n");
	अन्यथा
		seq_माला_दो(sfp, "DAN-H\n");

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(node, &priv->node_db, mac_list) अणु
		/* skip self node */
		अगर (hsr_addr_is_self(priv, node->macaddress_A))
			जारी;
		seq_म_लिखो(sfp, "%pM ", &node->macaddress_A[0]);
		seq_म_लिखो(sfp, "%pM ", &node->macaddress_B[0]);
		seq_म_लिखो(sfp, "%10lx, ", node->समय_in[HSR_PT_SLAVE_A]);
		seq_म_लिखो(sfp, "%10lx, ", node->समय_in[HSR_PT_SLAVE_B]);
		seq_म_लिखो(sfp, "%14x, ", node->addr_B_port);

		अगर (priv->prot_version == PRP_V1)
			seq_म_लिखो(sfp, "%5x, %5x, %5x\n",
				   node->san_a, node->san_b,
				   (node->san_a == 0 && node->san_b == 0));
		अन्यथा
			seq_म_लिखो(sfp, "%5x\n", 1);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(hsr_node_table);

व्योम hsr_debugfs_नाम(काष्ठा net_device *dev)
अणु
	काष्ठा hsr_priv *priv = netdev_priv(dev);
	काष्ठा dentry *d;

	d = debugfs_नाम(hsr_debugfs_root_dir, priv->node_tbl_root,
			   hsr_debugfs_root_dir, dev->name);
	अगर (IS_ERR(d))
		netdev_warn(dev, "failed to rename\n");
	अन्यथा
		priv->node_tbl_root = d;
पूर्ण

/* hsr_debugfs_init - create hsr node_table file क्रम dumping
 * the node table
 *
 * Description:
 * When debugfs is configured this routine sets up the node_table file per
 * hsr device क्रम dumping the node_table entries
 */
व्योम hsr_debugfs_init(काष्ठा hsr_priv *priv, काष्ठा net_device *hsr_dev)
अणु
	काष्ठा dentry *de = शून्य;

	de = debugfs_create_dir(hsr_dev->name, hsr_debugfs_root_dir);
	अगर (IS_ERR(de)) अणु
		pr_err("Cannot create hsr debugfs directory\n");
		वापस;
	पूर्ण

	priv->node_tbl_root = de;

	de = debugfs_create_file("node_table", S_IFREG | 0444,
				 priv->node_tbl_root, priv,
				 &hsr_node_table_fops);
	अगर (IS_ERR(de)) अणु
		pr_err("Cannot create hsr node_table file\n");
		debugfs_हटाओ(priv->node_tbl_root);
		priv->node_tbl_root = शून्य;
		वापस;
	पूर्ण
पूर्ण

/* hsr_debugfs_term - Tear करोwn debugfs पूर्णांकraकाष्ठाure
 *
 * Description:
 * When Debugfs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to hsr
 */
व्योम
hsr_debugfs_term(काष्ठा hsr_priv *priv)
अणु
	debugfs_हटाओ_recursive(priv->node_tbl_root);
	priv->node_tbl_root = शून्य;
पूर्ण

व्योम hsr_debugfs_create_root(व्योम)
अणु
	hsr_debugfs_root_dir = debugfs_create_dir("hsr", शून्य);
	अगर (IS_ERR(hsr_debugfs_root_dir)) अणु
		pr_err("Cannot create hsr debugfs root directory\n");
		hsr_debugfs_root_dir = शून्य;
	पूर्ण
पूर्ण

व्योम hsr_debugfs_हटाओ_root(व्योम)
अणु
	/* debugfs_हटाओ() पूर्णांकernally checks शून्य and ERROR */
	debugfs_हटाओ(hsr_debugfs_root_dir);
पूर्ण
