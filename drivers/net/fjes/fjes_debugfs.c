<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015-2016 FUJITSU LIMITED
 */

/* debugfs support क्रम fjes driver */

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "fjes.h"

अटल काष्ठा dentry *fjes_debug_root;

अटल स्थिर अक्षर * स्थिर ep_status_string[] = अणु
	"unshared",
	"shared",
	"waiting",
	"complete",
पूर्ण;

अटल पूर्णांक fjes_dbg_status_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fjes_adapter *adapter = m->निजी;
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक max_epid = hw->max_epid;
	पूर्णांक my_epid = hw->my_epid;
	पूर्णांक epidx;

	seq_माला_दो(m, "EPID\tSTATUS           SAME_ZONE        CONNECTED\n");
	क्रम (epidx = 0; epidx < max_epid; epidx++) अणु
		अगर (epidx == my_epid) अणु
			seq_म_लिखो(m, "ep%d\t%-16c %-16c %-16c\n",
				   epidx, '-', '-', '-');
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, "ep%d\t%-16s %-16c %-16c\n",
				   epidx,
				   ep_status_string[fjes_hw_get_partner_ep_status(hw, epidx)],
				   fjes_hw_epid_is_same_zone(hw, epidx) ? 'Y' : 'N',
				   fjes_hw_epid_is_shared(hw->hw_info.share, epidx) ? 'Y' : 'N');
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fjes_dbg_status);

व्योम fjes_dbg_adapter_init(काष्ठा fjes_adapter *adapter)
अणु
	स्थिर अक्षर *name = dev_name(&adapter->plat_dev->dev);

	adapter->dbg_adapter = debugfs_create_dir(name, fjes_debug_root);

	debugfs_create_file("status", 0444, adapter->dbg_adapter, adapter,
			    &fjes_dbg_status_fops);
पूर्ण

व्योम fjes_dbg_adapter_निकास(काष्ठा fjes_adapter *adapter)
अणु
	debugfs_हटाओ_recursive(adapter->dbg_adapter);
	adapter->dbg_adapter = शून्य;
पूर्ण

व्योम fjes_dbg_init(व्योम)
अणु
	fjes_debug_root = debugfs_create_dir(fjes_driver_name, शून्य);
पूर्ण

व्योम fjes_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(fjes_debug_root);
	fjes_debug_root = शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
