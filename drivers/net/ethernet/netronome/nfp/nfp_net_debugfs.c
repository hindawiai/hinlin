<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>

#समावेश "nfp_net.h"

अटल काष्ठा dentry *nfp_dir;

अटल पूर्णांक nfp_rx_q_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा nfp_net_r_vector *r_vec = file->निजी;
	काष्ठा nfp_net_rx_ring *rx_ring;
	पूर्णांक fl_rd_p, fl_wr_p, rxd_cnt;
	काष्ठा nfp_net_rx_desc *rxd;
	काष्ठा nfp_net *nn;
	व्योम *frag;
	पूर्णांक i;

	rtnl_lock();

	अगर (!r_vec->nfp_net || !r_vec->rx_ring)
		जाओ out;
	nn = r_vec->nfp_net;
	rx_ring = r_vec->rx_ring;
	अगर (!nfp_net_running(nn))
		जाओ out;

	rxd_cnt = rx_ring->cnt;

	fl_rd_p = nfp_qcp_rd_ptr_पढ़ो(rx_ring->qcp_fl);
	fl_wr_p = nfp_qcp_wr_ptr_पढ़ो(rx_ring->qcp_fl);

	seq_म_लिखो(file, "RX[%02d,%02d]: cnt=%u dma=%pad host=%p   H_RD=%u H_WR=%u FL_RD=%u FL_WR=%u\n",
		   rx_ring->idx, rx_ring->fl_qcidx,
		   rx_ring->cnt, &rx_ring->dma, rx_ring->rxds,
		   rx_ring->rd_p, rx_ring->wr_p, fl_rd_p, fl_wr_p);

	क्रम (i = 0; i < rxd_cnt; i++) अणु
		rxd = &rx_ring->rxds[i];
		seq_म_लिखो(file, "%04d: 0x%08x 0x%08x", i,
			   rxd->vals[0], rxd->vals[1]);

		frag = READ_ONCE(rx_ring->rxbufs[i].frag);
		अगर (frag)
			seq_म_लिखो(file, " frag=%p", frag);

		अगर (rx_ring->rxbufs[i].dma_addr)
			seq_म_लिखो(file, " dma_addr=%pad",
				   &rx_ring->rxbufs[i].dma_addr);

		अगर (i == rx_ring->rd_p % rxd_cnt)
			seq_माला_दो(file, " H_RD ");
		अगर (i == rx_ring->wr_p % rxd_cnt)
			seq_माला_दो(file, " H_WR ");
		अगर (i == fl_rd_p % rxd_cnt)
			seq_माला_दो(file, " FL_RD");
		अगर (i == fl_wr_p % rxd_cnt)
			seq_माला_दो(file, " FL_WR");

		seq_अ_दो(file, '\n');
	पूर्ण
out:
	rtnl_unlock();
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(nfp_rx_q);

अटल पूर्णांक nfp_tx_q_show(काष्ठा seq_file *file, व्योम *data);
DEFINE_SHOW_ATTRIBUTE(nfp_tx_q);

अटल पूर्णांक nfp_tx_q_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा nfp_net_r_vector *r_vec = file->निजी;
	काष्ठा nfp_net_tx_ring *tx_ring;
	काष्ठा nfp_net_tx_desc *txd;
	पूर्णांक d_rd_p, d_wr_p, txd_cnt;
	काष्ठा nfp_net *nn;
	पूर्णांक i;

	rtnl_lock();

	अगर (debugfs_real_fops(file->file) == &nfp_tx_q_fops)
		tx_ring = r_vec->tx_ring;
	अन्यथा
		tx_ring = r_vec->xdp_ring;
	अगर (!r_vec->nfp_net || !tx_ring)
		जाओ out;
	nn = r_vec->nfp_net;
	अगर (!nfp_net_running(nn))
		जाओ out;

	txd_cnt = tx_ring->cnt;

	d_rd_p = nfp_qcp_rd_ptr_पढ़ो(tx_ring->qcp_q);
	d_wr_p = nfp_qcp_wr_ptr_पढ़ो(tx_ring->qcp_q);

	seq_म_लिखो(file, "TX[%02d,%02d%s]: cnt=%u dma=%pad host=%p   H_RD=%u H_WR=%u D_RD=%u D_WR=%u\n",
		   tx_ring->idx, tx_ring->qcidx,
		   tx_ring == r_vec->tx_ring ? "" : "xdp",
		   tx_ring->cnt, &tx_ring->dma, tx_ring->txds,
		   tx_ring->rd_p, tx_ring->wr_p, d_rd_p, d_wr_p);

	क्रम (i = 0; i < txd_cnt; i++) अणु
		txd = &tx_ring->txds[i];
		seq_म_लिखो(file, "%04d: 0x%08x 0x%08x 0x%08x 0x%08x", i,
			   txd->vals[0], txd->vals[1],
			   txd->vals[2], txd->vals[3]);

		अगर (tx_ring == r_vec->tx_ring) अणु
			काष्ठा sk_buff *skb = READ_ONCE(tx_ring->txbufs[i].skb);

			अगर (skb)
				seq_म_लिखो(file, " skb->head=%p skb->data=%p",
					   skb->head, skb->data);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(file, " frag=%p",
				   READ_ONCE(tx_ring->txbufs[i].frag));
		पूर्ण

		अगर (tx_ring->txbufs[i].dma_addr)
			seq_म_लिखो(file, " dma_addr=%pad",
				   &tx_ring->txbufs[i].dma_addr);

		अगर (i == tx_ring->rd_p % txd_cnt)
			seq_माला_दो(file, " H_RD");
		अगर (i == tx_ring->wr_p % txd_cnt)
			seq_माला_दो(file, " H_WR");
		अगर (i == d_rd_p % txd_cnt)
			seq_माला_दो(file, " D_RD");
		अगर (i == d_wr_p % txd_cnt)
			seq_माला_दो(file, " D_WR");

		seq_अ_दो(file, '\n');
	पूर्ण
out:
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_xdp_q_show(काष्ठा seq_file *file, व्योम *data)
अणु
	वापस nfp_tx_q_show(file, data);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(nfp_xdp_q);

व्योम nfp_net_debugfs_vnic_add(काष्ठा nfp_net *nn, काष्ठा dentry *ddir)
अणु
	काष्ठा dentry *queues, *tx, *rx, *xdp;
	अक्षर name[20];
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(nfp_dir))
		वापस;

	अगर (nfp_net_is_data_vnic(nn))
		प्र_लिखो(name, "vnic%d", nn->id);
	अन्यथा
		म_नकल(name, "ctrl-vnic");
	nn->debugfs_dir = debugfs_create_dir(name, ddir);

	/* Create queue debugging sub-tree */
	queues = debugfs_create_dir("queue", nn->debugfs_dir);

	rx = debugfs_create_dir("rx", queues);
	tx = debugfs_create_dir("tx", queues);
	xdp = debugfs_create_dir("xdp", queues);

	क्रम (i = 0; i < min(nn->max_rx_rings, nn->max_r_vecs); i++) अणु
		प्र_लिखो(name, "%d", i);
		debugfs_create_file(name, 0400, rx,
				    &nn->r_vecs[i], &nfp_rx_q_fops);
		debugfs_create_file(name, 0400, xdp,
				    &nn->r_vecs[i], &nfp_xdp_q_fops);
	पूर्ण

	क्रम (i = 0; i < min(nn->max_tx_rings, nn->max_r_vecs); i++) अणु
		प्र_लिखो(name, "%d", i);
		debugfs_create_file(name, 0400, tx,
				    &nn->r_vecs[i], &nfp_tx_q_fops);
	पूर्ण
पूर्ण

काष्ठा dentry *nfp_net_debugfs_device_add(काष्ठा pci_dev *pdev)
अणु
	वापस debugfs_create_dir(pci_name(pdev), nfp_dir);
पूर्ण

व्योम nfp_net_debugfs_dir_clean(काष्ठा dentry **dir)
अणु
	debugfs_हटाओ_recursive(*dir);
	*dir = शून्य;
पूर्ण

व्योम nfp_net_debugfs_create(व्योम)
अणु
	nfp_dir = debugfs_create_dir("nfp_net", शून्य);
पूर्ण

व्योम nfp_net_debugfs_destroy(व्योम)
अणु
	debugfs_हटाओ_recursive(nfp_dir);
	nfp_dir = शून्य;
पूर्ण
