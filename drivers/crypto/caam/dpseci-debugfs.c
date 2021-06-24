<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश "dpseci-debugfs.h"

अटल पूर्णांक dpseci_dbg_fqs_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा dpaa2_caam_priv *priv = (काष्ठा dpaa2_caam_priv *)file->निजी;
	u32 fqid, fcnt, bcnt;
	पूर्णांक i, err;

	seq_म_लिखो(file, "FQ stats for %s:\n", dev_name(priv->dev));
	seq_म_लिखो(file, "%s%16s%16s\n",
		   "Rx-VFQID",
		   "Pending frames",
		   "Pending bytes");

	क्रम (i = 0; i <  priv->num_pairs; i++) अणु
		fqid = priv->rx_queue_attr[i].fqid;
		err = dpaa2_io_query_fq_count(शून्य, fqid, &fcnt, &bcnt);
		अगर (err)
			जारी;

		seq_म_लिखो(file, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	पूर्ण

	seq_म_लिखो(file, "%s%16s%16s\n",
		   "Tx-VFQID",
		   "Pending frames",
		   "Pending bytes");

	क्रम (i = 0; i <  priv->num_pairs; i++) अणु
		fqid = priv->tx_queue_attr[i].fqid;
		err = dpaa2_io_query_fq_count(शून्य, fqid, &fcnt, &bcnt);
		अगर (err)
			जारी;

		seq_म_लिखो(file, "%5d%16u%16u\n", fqid, fcnt, bcnt);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dpseci_dbg_fqs);

व्योम dpaa2_dpseci_debugfs_init(काष्ठा dpaa2_caam_priv *priv)
अणु
	priv->dfs_root = debugfs_create_dir(dev_name(priv->dev), शून्य);

	debugfs_create_file("fq_stats", 0444, priv->dfs_root, priv,
			    &dpseci_dbg_fqs_fops);
पूर्ण

व्योम dpaa2_dpseci_debugfs_निकास(काष्ठा dpaa2_caam_priv *priv)
अणु
	debugfs_हटाओ_recursive(priv->dfs_root);
पूर्ण
