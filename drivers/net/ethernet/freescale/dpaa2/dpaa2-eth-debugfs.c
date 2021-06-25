<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2015 Freescale Semiconductor Inc.
 * Copyright 2018-2019 NXP
 */
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश "dpaa2-eth.h"
#समावेश "dpaa2-eth-debugfs.h"

#घोषणा DPAA2_ETH_DBG_ROOT "dpaa2-eth"

अटल काष्ठा dentry *dpaa2_dbg_root;

अटल पूर्णांक dpaa2_dbg_cpu_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा dpaa2_eth_priv *priv = (काष्ठा dpaa2_eth_priv *)file->निजी;
	काष्ठा rtnl_link_stats64 *stats;
	काष्ठा dpaa2_eth_drv_stats *extras;
	पूर्णांक i;

	seq_म_लिखो(file, "Per-CPU stats for %s\n", priv->net_dev->name);
	seq_म_लिखो(file, "%s%16s%16s%16s%16s%16s%16s%16s%16s%16s\n",
		   "CPU", "Rx", "Rx Err", "Rx SG", "Tx", "Tx Err", "Tx conf",
		   "Tx SG", "Tx converted to SG", "Enq busy");

	क्रम_each_online_cpu(i) अणु
		stats = per_cpu_ptr(priv->percpu_stats, i);
		extras = per_cpu_ptr(priv->percpu_extras, i);
		seq_म_लिखो(file, "%3d%16llu%16llu%16llu%16llu%16llu%16llu%16llu%16llu%16llu\n",
			   i,
			   stats->rx_packets,
			   stats->rx_errors,
			   extras->rx_sg_frames,
			   stats->tx_packets,
			   stats->tx_errors,
			   extras->tx_conf_frames,
			   extras->tx_sg_frames,
			   extras->tx_converted_sg_frames,
			   extras->tx_portal_busy);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dpaa2_dbg_cpu);

अटल अक्षर *fq_type_to_str(काष्ठा dpaa2_eth_fq *fq)
अणु
	चयन (fq->type) अणु
	हाल DPAA2_RX_FQ:
		वापस "Rx";
	हाल DPAA2_TX_CONF_FQ:
		वापस "Tx conf";
	शेष:
		वापस "N/A";
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_dbg_fqs_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा dpaa2_eth_priv *priv = (काष्ठा dpaa2_eth_priv *)file->निजी;
	काष्ठा dpaa2_eth_fq *fq;
	u32 fcnt, bcnt;
	पूर्णांक i, err;

	seq_म_लिखो(file, "FQ stats for %s:\n", priv->net_dev->name);
	seq_म_लिखो(file, "%s%16s%16s%16s%16s%16s\n",
		   "VFQID", "CPU", "TC", "Type", "Frames", "Pending frames");

	क्रम (i = 0; i <  priv->num_fqs; i++) अणु
		fq = &priv->fq[i];
		err = dpaa2_io_query_fq_count(शून्य, fq->fqid, &fcnt, &bcnt);
		अगर (err)
			fcnt = 0;

		/* Skip FQs with no traffic */
		अगर (!fq->stats.frames && !fcnt)
			जारी;

		seq_म_लिखो(file, "%5d%16d%16d%16s%16llu%16u\n",
			   fq->fqid,
			   fq->target_cpu,
			   fq->tc,
			   fq_type_to_str(fq),
			   fq->stats.frames,
			   fcnt);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dpaa2_dbg_fqs);

अटल पूर्णांक dpaa2_dbg_ch_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा dpaa2_eth_priv *priv = (काष्ठा dpaa2_eth_priv *)file->निजी;
	काष्ठा dpaa2_eth_channel *ch;
	पूर्णांक i;

	seq_म_लिखो(file, "Channel stats for %s:\n", priv->net_dev->name);
	seq_म_लिखो(file, "%s%16s%16s%16s%16s%16s%16s\n",
		   "CHID", "CPU", "Deq busy", "Frames", "CDANs",
		   "Avg Frm/CDAN", "Buf count");

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		seq_म_लिखो(file, "%4d%16d%16llu%16llu%16llu%16llu%16d\n",
			   ch->ch_id,
			   ch->nctx.desired_cpu,
			   ch->stats.dequeue_portal_busy,
			   ch->stats.frames,
			   ch->stats.cdan,
			   भाग64_u64(ch->stats.frames, ch->stats.cdan),
			   ch->buf_count);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dpaa2_dbg_ch);

व्योम dpaa2_dbg_add(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dentry *dir;

	/* Create a directory क्रम the पूर्णांकerface */
	dir = debugfs_create_dir(priv->net_dev->name, dpaa2_dbg_root);
	priv->dbg.dir = dir;

	/* per-cpu stats file */
	debugfs_create_file("cpu_stats", 0444, dir, priv, &dpaa2_dbg_cpu_fops);

	/* per-fq stats file */
	debugfs_create_file("fq_stats", 0444, dir, priv, &dpaa2_dbg_fqs_fops);

	/* per-fq stats file */
	debugfs_create_file("ch_stats", 0444, dir, priv, &dpaa2_dbg_ch_fops);
पूर्ण

व्योम dpaa2_dbg_हटाओ(काष्ठा dpaa2_eth_priv *priv)
अणु
	debugfs_हटाओ_recursive(priv->dbg.dir);
पूर्ण

व्योम dpaa2_eth_dbg_init(व्योम)
अणु
	dpaa2_dbg_root = debugfs_create_dir(DPAA2_ETH_DBG_ROOT, शून्य);
	pr_debug("DPAA2-ETH: debugfs created\n");
पूर्ण

व्योम dpaa2_eth_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ(dpaa2_dbg_root);
पूर्ण
