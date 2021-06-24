<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश "nitrox_csr.h"
#समावेश "nitrox_debugfs.h"
#समावेश "nitrox_dev.h"

अटल पूर्णांक firmware_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nitrox_device *ndev = s->निजी;

	seq_म_लिखो(s, "Version: %s\n", ndev->hw.fw_name[0]);
	seq_म_लिखो(s, "Version: %s\n", ndev->hw.fw_name[1]);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(firmware);

अटल पूर्णांक device_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nitrox_device *ndev = s->निजी;

	seq_म_लिखो(s, "NITROX [%d]\n", ndev->idx);
	seq_म_लिखो(s, "  Part Name: %s\n", ndev->hw.partname);
	seq_म_लिखो(s, "  Frequency: %d MHz\n", ndev->hw.freq);
	seq_म_लिखो(s, "  Device ID: 0x%0x\n", ndev->hw.device_id);
	seq_म_लिखो(s, "  Revision ID: 0x%0x\n", ndev->hw.revision_id);
	seq_म_लिखो(s, "  Cores: [AE=%u  SE=%u  ZIP=%u]\n",
		   ndev->hw.ae_cores, ndev->hw.se_cores, ndev->hw.zip_cores);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(device);

अटल पूर्णांक stats_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nitrox_device *ndev = s->निजी;

	seq_म_लिखो(s, "NITROX [%d] Request Statistics\n", ndev->idx);
	seq_म_लिखो(s, "  Posted: %llu\n",
		   (u64)atomic64_पढ़ो(&ndev->stats.posted));
	seq_म_लिखो(s, "  Completed: %llu\n",
		   (u64)atomic64_पढ़ो(&ndev->stats.completed));
	seq_म_लिखो(s, "  Dropped: %llu\n",
		   (u64)atomic64_पढ़ो(&ndev->stats.dropped));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(stats);

व्योम nitrox_debugfs_निकास(काष्ठा nitrox_device *ndev)
अणु
	debugfs_हटाओ_recursive(ndev->debugfs_dir);
	ndev->debugfs_dir = शून्य;
पूर्ण

व्योम nitrox_debugfs_init(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ndev->debugfs_dir = dir;
	debugfs_create_file("firmware", 0400, dir, ndev, &firmware_fops);
	debugfs_create_file("device", 0400, dir, ndev, &device_fops);
	debugfs_create_file("stats", 0400, dir, ndev, &stats_fops);
पूर्ण
