<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>

#समावेश <net/bonding.h>
#समावेश <net/bond_alb.h>

#अगर defined(CONFIG_DEBUG_FS) && !defined(CONFIG_NET_NS)

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल काष्ठा dentry *bonding_debug_root;

/* Show RLB hash table */
अटल पूर्णांक bond_debug_rlb_hash_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा bonding *bond = m->निजी;
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *client_info;
	u32 hash_index;

	अगर (BOND_MODE(bond) != BOND_MODE_ALB)
		वापस 0;

	seq_म_लिखो(m, "SourceIP        DestinationIP   "
			"Destination MAC   DEV\n");

	spin_lock_bh(&bond->mode_lock);

	hash_index = bond_info->rx_hashtbl_used_head;
	क्रम (; hash_index != RLB_शून्य_INDEX;
	     hash_index = client_info->used_next) अणु
		client_info = &(bond_info->rx_hashtbl[hash_index]);
		seq_म_लिखो(m, "%-15pI4 %-15pI4 %-17pM %s\n",
			&client_info->ip_src,
			&client_info->ip_dst,
			&client_info->mac_dst,
			client_info->slave->dev->name);
	पूर्ण

	spin_unlock_bh(&bond->mode_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(bond_debug_rlb_hash);

व्योम bond_debug_रेजिस्टर(काष्ठा bonding *bond)
अणु
	अगर (!bonding_debug_root)
		वापस;

	bond->debug_dir =
		debugfs_create_dir(bond->dev->name, bonding_debug_root);

	debugfs_create_file("rlb_hash_table", 0400, bond->debug_dir,
				bond, &bond_debug_rlb_hash_fops);
पूर्ण

व्योम bond_debug_unरेजिस्टर(काष्ठा bonding *bond)
अणु
	अगर (!bonding_debug_root)
		वापस;

	debugfs_हटाओ_recursive(bond->debug_dir);
पूर्ण

व्योम bond_debug_reरेजिस्टर(काष्ठा bonding *bond)
अणु
	काष्ठा dentry *d;

	अगर (!bonding_debug_root)
		वापस;

	d = debugfs_नाम(bonding_debug_root, bond->debug_dir,
			   bonding_debug_root, bond->dev->name);
	अगर (d) अणु
		bond->debug_dir = d;
	पूर्ण अन्यथा अणु
		netdev_warn(bond->dev, "failed to reregister, so just unregister old one\n");
		bond_debug_unरेजिस्टर(bond);
	पूर्ण
पूर्ण

व्योम bond_create_debugfs(व्योम)
अणु
	bonding_debug_root = debugfs_create_dir("bonding", शून्य);

	अगर (!bonding_debug_root) अणु
		pr_warn("Warning: Cannot create bonding directory in debugfs\n");
	पूर्ण
पूर्ण

व्योम bond_destroy_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(bonding_debug_root);
	bonding_debug_root = शून्य;
पूर्ण


#अन्यथा /* !CONFIG_DEBUG_FS */

व्योम bond_debug_रेजिस्टर(काष्ठा bonding *bond)
अणु
पूर्ण

व्योम bond_debug_unरेजिस्टर(काष्ठा bonding *bond)
अणु
पूर्ण

व्योम bond_debug_reरेजिस्टर(काष्ठा bonding *bond)
अणु
पूर्ण

व्योम bond_create_debugfs(व्योम)
अणु
पूर्ण

व्योम bond_destroy_debugfs(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
