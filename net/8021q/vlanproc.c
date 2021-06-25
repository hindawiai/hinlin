<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 * vlanproc.c	VLAN Module. /proc fileप्रणाली पूर्णांकerface.
 *
 *		This module is completely hardware-independent and provides
 *		access to the router using Linux /proc fileप्रणाली.
 *
 * Author:	Ben Greear, <greearb@candelatech.com> coppied from wanproc.c
 *               by: Gene Kozin	<genek@compuserve.com>
 *
 * Copyright:	(c) 1998 Ben Greear
 *
 * ============================================================================
 * Jan 20, 1998        Ben Greear     Initial Version
 *****************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश "vlanproc.h"
#समावेश "vlan.h"

/****** Function Prototypes *************************************************/

/* Methods क्रम preparing data क्रम पढ़ोing proc entries */
अटल पूर्णांक vlan_seq_show(काष्ठा seq_file *seq, व्योम *v);
अटल व्योम *vlan_seq_start(काष्ठा seq_file *seq, loff_t *pos);
अटल व्योम *vlan_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);
अटल व्योम vlan_seq_stop(काष्ठा seq_file *seq, व्योम *);
अटल पूर्णांक vlandev_seq_show(काष्ठा seq_file *seq, व्योम *v);

/*
 *	Global Data
 */


/*
 *	Names of the proc directory entries
 */

अटल स्थिर अक्षर name_root[]	 = "vlan";
अटल स्थिर अक्षर name_conf[]	 = "config";

/*
 *	Structures क्रम पूर्णांकerfacing with the /proc fileप्रणाली.
 *	VLAN creates its own directory /proc/net/vlan with the following
 *	entries:
 *	config		device status/configuration
 *	<device>	entry क्रम each  device
 */

/*
 *	Generic /proc/net/vlan/<file> file and inode operations
 */

अटल स्थिर काष्ठा seq_operations vlan_seq_ops = अणु
	.start = vlan_seq_start,
	.next = vlan_seq_next,
	.stop = vlan_seq_stop,
	.show = vlan_seq_show,
पूर्ण;

/*
 * Proc fileप्रणाली directory entries.
 */

/* Strings */
अटल स्थिर अक्षर *स्थिर vlan_name_type_str[VLAN_NAME_TYPE_HIGHEST] = अणु
    [VLAN_NAME_TYPE_RAW_PLUS_VID]        = "VLAN_NAME_TYPE_RAW_PLUS_VID",
    [VLAN_NAME_TYPE_PLUS_VID_NO_PAD]	 = "VLAN_NAME_TYPE_PLUS_VID_NO_PAD",
    [VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD] = "VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD",
    [VLAN_NAME_TYPE_PLUS_VID]		 = "VLAN_NAME_TYPE_PLUS_VID",
पूर्ण;
/*
 *	Interface functions
 */

/*
 *	Clean up /proc/net/vlan entries
 */

व्योम vlan_proc_cleanup(काष्ठा net *net)
अणु
	काष्ठा vlan_net *vn = net_generic(net, vlan_net_id);

	अगर (vn->proc_vlan_conf)
		हटाओ_proc_entry(name_conf, vn->proc_vlan_dir);

	अगर (vn->proc_vlan_dir)
		हटाओ_proc_entry(name_root, net->proc_net);

	/* Dynamically added entries should be cleaned up as their vlan_device
	 * is हटाओd, so we should not have to take care of it here...
	 */
पूर्ण

/*
 *	Create /proc/net/vlan entries
 */

पूर्णांक __net_init vlan_proc_init(काष्ठा net *net)
अणु
	काष्ठा vlan_net *vn = net_generic(net, vlan_net_id);

	vn->proc_vlan_dir = proc_net_सूची_गढ़ो(net, name_root, net->proc_net);
	अगर (!vn->proc_vlan_dir)
		जाओ err;

	vn->proc_vlan_conf = proc_create_net(name_conf, S_IFREG | 0600,
			vn->proc_vlan_dir, &vlan_seq_ops,
			माप(काष्ठा seq_net_निजी));
	अगर (!vn->proc_vlan_conf)
		जाओ err;
	वापस 0;

err:
	pr_err("can't create entry in proc filesystem!\n");
	vlan_proc_cleanup(net);
	वापस -ENOBUFS;
पूर्ण

/*
 *	Add directory entry क्रम VLAN device.
 */

पूर्णांक vlan_proc_add_dev(काष्ठा net_device *vlandev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(vlandev);
	काष्ठा vlan_net *vn = net_generic(dev_net(vlandev), vlan_net_id);

	अगर (!म_भेद(vlandev->name, name_conf))
		वापस -EINVAL;
	vlan->dent = proc_create_single_data(vlandev->name, S_IFREG | 0600,
			vn->proc_vlan_dir, vlandev_seq_show, vlandev);
	अगर (!vlan->dent)
		वापस -ENOBUFS;
	वापस 0;
पूर्ण

/*
 *	Delete directory entry क्रम VLAN device.
 */
व्योम vlan_proc_rem_dev(काष्ठा net_device *vlandev)
अणु
	/** NOTE:  This will consume the memory poपूर्णांकed to by dent, it seems. */
	proc_हटाओ(vlan_dev_priv(vlandev)->dent);
	vlan_dev_priv(vlandev)->dent = शून्य;
पूर्ण

/****** Proc fileप्रणाली entry poपूर्णांकs ****************************************/

/*
 * The following few functions build the content of /proc/net/vlan/config
 */

/* start पढ़ो of /proc/net/vlan/config */
अटल व्योम *vlan_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	काष्ठा net_device *dev;
	काष्ठा net *net = seq_file_net(seq);
	loff_t i = 1;

	rcu_पढ़ो_lock();
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम_each_netdev_rcu(net, dev) अणु
		अगर (!is_vlan_dev(dev))
			जारी;

		अगर (i++ == *pos)
			वापस dev;
	पूर्ण

	वापस  शून्य;
पूर्ण

अटल व्योम *vlan_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा net_device *dev;
	काष्ठा net *net = seq_file_net(seq);

	++*pos;

	dev = v;
	अगर (v == SEQ_START_TOKEN)
		dev = net_device_entry(&net->dev_base_head);

	क्रम_each_netdev_जारी_rcu(net, dev) अणु
		अगर (!is_vlan_dev(dev))
			जारी;

		वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम vlan_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक vlan_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा vlan_net *vn = net_generic(net, vlan_net_id);

	अगर (v == SEQ_START_TOKEN) अणु
		स्थिर अक्षर *nmtype = शून्य;

		seq_माला_दो(seq, "VLAN Dev name	 | VLAN ID\n");

		अगर (vn->name_type < ARRAY_SIZE(vlan_name_type_str))
		    nmtype =  vlan_name_type_str[vn->name_type];

		seq_म_लिखो(seq, "Name-Type: %s\n",
			   nmtype ? nmtype :  "UNKNOWN");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा net_device *vlandev = v;
		स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(vlandev);

		seq_म_लिखो(seq, "%-15s| %d  | %s\n",  vlandev->name,
			   vlan->vlan_id,    vlan->real_dev->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vlandev_seq_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	काष्ठा net_device *vlandev = (काष्ठा net_device *) seq->निजी;
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(vlandev);
	काष्ठा rtnl_link_stats64 temp;
	स्थिर काष्ठा rtnl_link_stats64 *stats;
	अटल स्थिर अक्षर fmt64[] = "%30s %12llu\n";
	पूर्णांक i;

	अगर (!is_vlan_dev(vlandev))
		वापस 0;

	stats = dev_get_stats(vlandev, &temp);
	seq_म_लिखो(seq,
		   "%s  VID: %d	 REORDER_HDR: %i  dev->priv_flags: %hx\n",
		   vlandev->name, vlan->vlan_id,
		   (पूर्णांक)(vlan->flags & 1), vlandev->priv_flags);

	seq_म_लिखो(seq, fmt64, "total frames received", stats->rx_packets);
	seq_म_लिखो(seq, fmt64, "total bytes received", stats->rx_bytes);
	seq_म_लिखो(seq, fmt64, "Broadcast/Multicast Rcvd", stats->multicast);
	seq_माला_दो(seq, "\n");
	seq_म_लिखो(seq, fmt64, "total frames transmitted", stats->tx_packets);
	seq_म_लिखो(seq, fmt64, "total bytes transmitted", stats->tx_bytes);
	seq_म_लिखो(seq, "Device: %s", vlan->real_dev->name);
	/* now show all PRIORITY mappings relating to this VLAN */
	seq_म_लिखो(seq, "\nINGRESS priority mappings: "
			"0:%u  1:%u  2:%u  3:%u  4:%u  5:%u  6:%u 7:%u\n",
		   vlan->ingress_priority_map[0],
		   vlan->ingress_priority_map[1],
		   vlan->ingress_priority_map[2],
		   vlan->ingress_priority_map[3],
		   vlan->ingress_priority_map[4],
		   vlan->ingress_priority_map[5],
		   vlan->ingress_priority_map[6],
		   vlan->ingress_priority_map[7]);

	seq_म_लिखो(seq, " EGRESS priority mappings: ");
	क्रम (i = 0; i < 16; i++) अणु
		स्थिर काष्ठा vlan_priority_tci_mapping *mp
			= vlan->egress_priority_map[i];
		जबतक (mp) अणु
			seq_म_लिखो(seq, "%u:%hu ",
				   mp->priority, ((mp->vlan_qos >> 13) & 0x7));
			mp = mp->next;
		पूर्ण
	पूर्ण
	seq_माला_दो(seq, "\n");

	वापस 0;
पूर्ण
