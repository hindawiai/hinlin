<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "fm10k.h"

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल काष्ठा dentry *dbg_root;

/* Descriptor Seq Functions */

अटल व्योम *fm10k_dbg_desc_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा fm10k_ring *ring = s->निजी;

	वापस (*pos < ring->count) ? pos : शून्य;
पूर्ण

अटल व्योम *fm10k_dbg_desc_seq_next(काष्ठा seq_file *s,
				     व्योम __always_unused *v,
				     loff_t *pos)
अणु
	काष्ठा fm10k_ring *ring = s->निजी;

	वापस (++(*pos) < ring->count) ? pos : शून्य;
पूर्ण

अटल व्योम fm10k_dbg_desc_seq_stop(काष्ठा seq_file __always_unused *s,
				    व्योम __always_unused *v)
अणु
	/* Do nothing. */
पूर्ण

अटल व्योम fm10k_dbg_desc_अवरोध(काष्ठा seq_file *s, पूर्णांक i)
अणु
	जबतक (i--)
		seq_अ_दो(s, '-');

	seq_अ_दो(s, '\n');
पूर्ण

अटल पूर्णांक fm10k_dbg_tx_desc_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा fm10k_ring *ring = s->निजी;
	पूर्णांक i = *(loff_t *)v;
	अटल स्थिर अक्षर tx_desc_hdr[] =
		"DES BUFFER_ADDRESS     LENGTH VLAN   MSS    HDRLEN FLAGS\n";

	/* Generate header */
	अगर (!i) अणु
		seq_म_लिखो(s, tx_desc_hdr);
		fm10k_dbg_desc_अवरोध(s, माप(tx_desc_hdr) - 1);
	पूर्ण

	/* Validate descriptor allocation */
	अगर (!ring->desc) अणु
		seq_म_लिखो(s, "%03X Descriptor ring not allocated.\n", i);
	पूर्ण अन्यथा अणु
		काष्ठा fm10k_tx_desc *txd = FM10K_TX_DESC(ring, i);

		seq_म_लिखो(s, "%03X %#018llx %#06x %#06x %#06x %#06x %#04x\n",
			   i, txd->buffer_addr, txd->buflen, txd->vlan,
			   txd->mss, txd->hdrlen, txd->flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_dbg_rx_desc_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा fm10k_ring *ring = s->निजी;
	पूर्णांक i = *(loff_t *)v;
	अटल स्थिर अक्षर rx_desc_hdr[] =
	"DES DATA       RSS        STATERR    LENGTH VLAN   DGLORT SGLORT TIMESTAMP\n";

	/* Generate header */
	अगर (!i) अणु
		seq_म_लिखो(s, rx_desc_hdr);
		fm10k_dbg_desc_अवरोध(s, माप(rx_desc_hdr) - 1);
	पूर्ण

	/* Validate descriptor allocation */
	अगर (!ring->desc) अणु
		seq_म_लिखो(s, "%03X Descriptor ring not allocated.\n", i);
	पूर्ण अन्यथा अणु
		जोड़ fm10k_rx_desc *rxd = FM10K_RX_DESC(ring, i);

		seq_म_लिखो(s,
			   "%03X %#010x %#010x %#010x %#06x %#06x %#06x %#06x %#018llx\n",
			   i, rxd->d.data, rxd->d.rss, rxd->d.staterr,
			   rxd->w.length, rxd->w.vlan, rxd->w.dglort,
			   rxd->w.sglort, rxd->q.बारtamp);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fm10k_dbg_tx_desc_seq_ops = अणु
	.start = fm10k_dbg_desc_seq_start,
	.next  = fm10k_dbg_desc_seq_next,
	.stop  = fm10k_dbg_desc_seq_stop,
	.show  = fm10k_dbg_tx_desc_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations fm10k_dbg_rx_desc_seq_ops = अणु
	.start = fm10k_dbg_desc_seq_start,
	.next  = fm10k_dbg_desc_seq_next,
	.stop  = fm10k_dbg_desc_seq_stop,
	.show  = fm10k_dbg_rx_desc_seq_show,
पूर्ण;

अटल पूर्णांक fm10k_dbg_desc_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा fm10k_ring *ring = inode->i_निजी;
	काष्ठा fm10k_q_vector *q_vector = ring->q_vector;
	स्थिर काष्ठा seq_operations *desc_seq_ops;
	पूर्णांक err;

	अगर (ring < q_vector->rx.ring)
		desc_seq_ops = &fm10k_dbg_tx_desc_seq_ops;
	अन्यथा
		desc_seq_ops = &fm10k_dbg_rx_desc_seq_ops;

	err = seq_खोलो(filep, desc_seq_ops);
	अगर (err)
		वापस err;

	((काष्ठा seq_file *)filep->निजी_data)->निजी = ring;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fm10k_dbg_desc_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = fm10k_dbg_desc_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;

/**
 * fm10k_dbg_q_vector_init - setup debugfs क्रम the q_vectors
 * @q_vector: q_vector to allocate directories क्रम
 *
 * A folder is created क्रम each q_vector found. In each q_vector
 * folder, a debugfs file is created क्रम each tx and rx ring
 * allocated to the q_vector.
 **/
व्योम fm10k_dbg_q_vector_init(काष्ठा fm10k_q_vector *q_vector)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = q_vector->पूर्णांकerface;
	अक्षर name[16];
	पूर्णांक i;

	अगर (!पूर्णांकerface->dbg_पूर्णांकfc)
		वापस;

	/* Generate a folder क्रम each q_vector */
	snम_लिखो(name, माप(name), "q_vector.%03d", q_vector->v_idx);

	q_vector->dbg_q_vector = debugfs_create_dir(name, पूर्णांकerface->dbg_पूर्णांकfc);

	/* Generate a file क्रम each rx ring in the q_vector */
	क्रम (i = 0; i < q_vector->tx.count; i++) अणु
		काष्ठा fm10k_ring *ring = &q_vector->tx.ring[i];

		snम_लिखो(name, माप(name), "tx_ring.%03d", ring->queue_index);

		debugfs_create_file(name, 0600,
				    q_vector->dbg_q_vector, ring,
				    &fm10k_dbg_desc_fops);
	पूर्ण

	/* Generate a file क्रम each rx ring in the q_vector */
	क्रम (i = 0; i < q_vector->rx.count; i++) अणु
		काष्ठा fm10k_ring *ring = &q_vector->rx.ring[i];

		snम_लिखो(name, माप(name), "rx_ring.%03d", ring->queue_index);

		debugfs_create_file(name, 0600,
				    q_vector->dbg_q_vector, ring,
				    &fm10k_dbg_desc_fops);
	पूर्ण
पूर्ण

/**
 * fm10k_dbg_q_vector_निकास - setup debugfs क्रम the q_vectors
 * @q_vector: q_vector to allocate directories क्रम
 **/
व्योम fm10k_dbg_q_vector_निकास(काष्ठा fm10k_q_vector *q_vector)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = q_vector->पूर्णांकerface;

	अगर (पूर्णांकerface->dbg_पूर्णांकfc)
		debugfs_हटाओ_recursive(q_vector->dbg_q_vector);
	q_vector->dbg_q_vector = शून्य;
पूर्ण

/**
 * fm10k_dbg_पूर्णांकfc_init - setup the debugfs directory क्रम the पूर्णांकferface
 * @पूर्णांकerface: the पूर्णांकerface that is starting up
 **/

व्योम fm10k_dbg_पूर्णांकfc_init(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	स्थिर अक्षर *name = pci_name(पूर्णांकerface->pdev);

	अगर (dbg_root)
		पूर्णांकerface->dbg_पूर्णांकfc = debugfs_create_dir(name, dbg_root);
पूर्ण

/**
 * fm10k_dbg_पूर्णांकfc_निकास - clean out the पूर्णांकerface's debugfs entries
 * @पूर्णांकerface: the पूर्णांकerface that is stopping
 **/
व्योम fm10k_dbg_पूर्णांकfc_निकास(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	अगर (dbg_root)
		debugfs_हटाओ_recursive(पूर्णांकerface->dbg_पूर्णांकfc);
	पूर्णांकerface->dbg_पूर्णांकfc = शून्य;
पूर्ण

/**
 * fm10k_dbg_init - start up debugfs क्रम the driver
 **/
व्योम fm10k_dbg_init(व्योम)
अणु
	dbg_root = debugfs_create_dir(fm10k_driver_name, शून्य);
पूर्ण

/**
 * fm10k_dbg_निकास - clean out the driver's debugfs entries
 **/
व्योम fm10k_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(dbg_root);
	dbg_root = शून्य;
पूर्ण
