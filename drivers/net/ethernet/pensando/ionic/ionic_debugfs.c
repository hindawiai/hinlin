<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_debugfs.h"

#अगर_घोषित CONFIG_DEBUG_FS

अटल काष्ठा dentry *ionic_dir;

व्योम ionic_debugfs_create(व्योम)
अणु
	ionic_dir = debugfs_create_dir(IONIC_DRV_NAME, शून्य);
पूर्ण

व्योम ionic_debugfs_destroy(व्योम)
अणु
	debugfs_हटाओ_recursive(ionic_dir);
पूर्ण

व्योम ionic_debugfs_add_dev(काष्ठा ionic *ionic)
अणु
	ionic->dentry = debugfs_create_dir(ionic_bus_info(ionic), ionic_dir);
पूर्ण

व्योम ionic_debugfs_del_dev(काष्ठा ionic *ionic)
अणु
	debugfs_हटाओ_recursive(ionic->dentry);
	ionic->dentry = शून्य;
पूर्ण

अटल पूर्णांक identity_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ionic *ionic = seq->निजी;
	काष्ठा ionic_identity *ident;

	ident = &ionic->ident;

	seq_म_लिखो(seq, "nlifs:            %d\n", ident->dev.nlअगरs);
	seq_म_लिखो(seq, "nintrs:           %d\n", ident->dev.nपूर्णांकrs);
	seq_म_लिखो(seq, "ndbpgs_per_lif:   %d\n", ident->dev.ndbpgs_per_lअगर);
	seq_म_लिखो(seq, "intr_coal_mult:   %d\n", ident->dev.पूर्णांकr_coal_mult);
	seq_म_लिखो(seq, "intr_coal_div:    %d\n", ident->dev.पूर्णांकr_coal_भाग);

	seq_म_लिखो(seq, "max_ucast_filters:  %d\n", ident->lअगर.eth.max_ucast_filters);
	seq_म_लिखो(seq, "max_mcast_filters:  %d\n", ident->lअगर.eth.max_mcast_filters);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(identity);

व्योम ionic_debugfs_add_ident(काष्ठा ionic *ionic)
अणु
	debugfs_create_file("identity", 0400, ionic->dentry,
			    ionic, &identity_fops);
पूर्ण

व्योम ionic_debugfs_add_sizes(काष्ठा ionic *ionic)
अणु
	debugfs_create_u32("nlifs", 0400, ionic->dentry,
			   (u32 *)&ionic->ident.dev.nlअगरs);
	debugfs_create_u32("nintrs", 0400, ionic->dentry, &ionic->nपूर्णांकrs);

	debugfs_create_u32("ntxqs_per_lif", 0400, ionic->dentry,
			   (u32 *)&ionic->ident.lअगर.eth.config.queue_count[IONIC_QTYPE_TXQ]);
	debugfs_create_u32("nrxqs_per_lif", 0400, ionic->dentry,
			   (u32 *)&ionic->ident.lअगर.eth.config.queue_count[IONIC_QTYPE_RXQ]);
पूर्ण

अटल पूर्णांक q_tail_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ionic_queue *q = seq->निजी;

	seq_म_लिखो(seq, "%d\n", q->tail_idx);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(q_tail);

अटल पूर्णांक q_head_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ionic_queue *q = seq->निजी;

	seq_म_लिखो(seq, "%d\n", q->head_idx);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(q_head);

अटल पूर्णांक cq_tail_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ionic_cq *cq = seq->निजी;

	seq_म_लिखो(seq, "%d\n", cq->tail_idx);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cq_tail);

अटल स्थिर काष्ठा debugfs_reg32 पूर्णांकr_ctrl_regs[] = अणु
	अणु .name = "coal_init", .offset = 0, पूर्ण,
	अणु .name = "mask", .offset = 4, पूर्ण,
	अणु .name = "credits", .offset = 8, पूर्ण,
	अणु .name = "mask_on_assert", .offset = 12, पूर्ण,
	अणु .name = "coal_timer", .offset = 16, पूर्ण,
पूर्ण;

व्योम ionic_debugfs_add_qcq(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा dentry *qcq_dentry, *q_dentry, *cq_dentry;
	काष्ठा dentry *पूर्णांकr_dentry, *stats_dentry;
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा debugfs_regset32 *पूर्णांकr_ctrl_regset;
	काष्ठा ionic_पूर्णांकr_info *पूर्णांकr = &qcq->पूर्णांकr;
	काष्ठा debugfs_blob_wrapper *desc_blob;
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_queue *q = &qcq->q;
	काष्ठा ionic_cq *cq = &qcq->cq;

	qcq_dentry = debugfs_create_dir(q->name, lअगर->dentry);
	अगर (IS_ERR_OR_शून्य(qcq_dentry))
		वापस;
	qcq->dentry = qcq_dentry;

	debugfs_create_x64("q_base_pa", 0400, qcq_dentry, &qcq->q_base_pa);
	debugfs_create_x32("q_size", 0400, qcq_dentry, &qcq->q_size);
	debugfs_create_x64("cq_base_pa", 0400, qcq_dentry, &qcq->cq_base_pa);
	debugfs_create_x32("cq_size", 0400, qcq_dentry, &qcq->cq_size);
	debugfs_create_x64("sg_base_pa", 0400, qcq_dentry, &qcq->sg_base_pa);
	debugfs_create_x32("sg_size", 0400, qcq_dentry, &qcq->sg_size);

	q_dentry = debugfs_create_dir("q", qcq->dentry);

	debugfs_create_u32("index", 0400, q_dentry, &q->index);
	debugfs_create_u32("num_descs", 0400, q_dentry, &q->num_descs);
	debugfs_create_u32("desc_size", 0400, q_dentry, &q->desc_size);
	debugfs_create_u32("pid", 0400, q_dentry, &q->pid);
	debugfs_create_u32("qid", 0400, q_dentry, &q->hw_index);
	debugfs_create_u32("qtype", 0400, q_dentry, &q->hw_type);
	debugfs_create_u64("drop", 0400, q_dentry, &q->drop);
	debugfs_create_u64("stop", 0400, q_dentry, &q->stop);
	debugfs_create_u64("wake", 0400, q_dentry, &q->wake);

	debugfs_create_file("tail", 0400, q_dentry, q, &q_tail_fops);
	debugfs_create_file("head", 0400, q_dentry, q, &q_head_fops);

	desc_blob = devm_kzalloc(dev, माप(*desc_blob), GFP_KERNEL);
	अगर (!desc_blob)
		वापस;
	desc_blob->data = q->base;
	desc_blob->size = (अचिन्हित दीर्घ)q->num_descs * q->desc_size;
	debugfs_create_blob("desc_blob", 0400, q_dentry, desc_blob);

	अगर (qcq->flags & IONIC_QCQ_F_SG) अणु
		desc_blob = devm_kzalloc(dev, माप(*desc_blob), GFP_KERNEL);
		अगर (!desc_blob)
			वापस;
		desc_blob->data = q->sg_base;
		desc_blob->size = (अचिन्हित दीर्घ)q->num_descs * q->sg_desc_size;
		debugfs_create_blob("sg_desc_blob", 0400, q_dentry,
				    desc_blob);
	पूर्ण

	cq_dentry = debugfs_create_dir("cq", qcq->dentry);

	debugfs_create_x64("base_pa", 0400, cq_dentry, &cq->base_pa);
	debugfs_create_u32("num_descs", 0400, cq_dentry, &cq->num_descs);
	debugfs_create_u32("desc_size", 0400, cq_dentry, &cq->desc_size);
	debugfs_create_bool("done_color", 0400, cq_dentry, &cq->करोne_color);

	debugfs_create_file("tail", 0400, cq_dentry, cq, &cq_tail_fops);

	desc_blob = devm_kzalloc(dev, माप(*desc_blob), GFP_KERNEL);
	अगर (!desc_blob)
		वापस;
	desc_blob->data = cq->base;
	desc_blob->size = (अचिन्हित दीर्घ)cq->num_descs * cq->desc_size;
	debugfs_create_blob("desc_blob", 0400, cq_dentry, desc_blob);

	अगर (qcq->flags & IONIC_QCQ_F_INTR) अणु
		पूर्णांकr_dentry = debugfs_create_dir("intr", qcq->dentry);

		debugfs_create_u32("index", 0400, पूर्णांकr_dentry,
				   &पूर्णांकr->index);
		debugfs_create_u32("vector", 0400, पूर्णांकr_dentry,
				   &पूर्णांकr->vector);
		debugfs_create_u32("dim_coal_hw", 0400, पूर्णांकr_dentry,
				   &पूर्णांकr->dim_coal_hw);

		पूर्णांकr_ctrl_regset = devm_kzalloc(dev, माप(*पूर्णांकr_ctrl_regset),
						GFP_KERNEL);
		अगर (!पूर्णांकr_ctrl_regset)
			वापस;
		पूर्णांकr_ctrl_regset->regs = पूर्णांकr_ctrl_regs;
		पूर्णांकr_ctrl_regset->nregs = ARRAY_SIZE(पूर्णांकr_ctrl_regs);
		पूर्णांकr_ctrl_regset->base = &idev->पूर्णांकr_ctrl[पूर्णांकr->index];

		debugfs_create_regset32("intr_ctrl", 0400, पूर्णांकr_dentry,
					पूर्णांकr_ctrl_regset);
	पूर्ण

	अगर (qcq->flags & IONIC_QCQ_F_NOTIFYQ) अणु
		stats_dentry = debugfs_create_dir("notifyblock", qcq->dentry);

		debugfs_create_u64("eid", 0400, stats_dentry,
				   (u64 *)&lअगर->info->status.eid);
		debugfs_create_u16("link_status", 0400, stats_dentry,
				   (u16 *)&lअगर->info->status.link_status);
		debugfs_create_u32("link_speed", 0400, stats_dentry,
				   (u32 *)&lअगर->info->status.link_speed);
		debugfs_create_u16("link_down_count", 0400, stats_dentry,
				   (u16 *)&lअगर->info->status.link_करोwn_count);
	पूर्ण
पूर्ण

अटल पूर्णांक netdev_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *netdev = seq->निजी;

	seq_म_लिखो(seq, "%s\n", netdev->name);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(netdev);

व्योम ionic_debugfs_add_lअगर(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा dentry *lअगर_dentry;

	lअगर_dentry = debugfs_create_dir(lअगर->name, lअगर->ionic->dentry);
	अगर (IS_ERR_OR_शून्य(lअगर_dentry))
		वापस;
	lअगर->dentry = lअगर_dentry;

	debugfs_create_file("netdev", 0400, lअगर->dentry,
			    lअगर->netdev, &netdev_fops);
पूर्ण

व्योम ionic_debugfs_del_lअगर(काष्ठा ionic_lअगर *lअगर)
अणु
	debugfs_हटाओ_recursive(lअगर->dentry);
	lअगर->dentry = शून्य;
पूर्ण

व्योम ionic_debugfs_del_qcq(काष्ठा ionic_qcq *qcq)
अणु
	debugfs_हटाओ_recursive(qcq->dentry);
	qcq->dentry = शून्य;
पूर्ण

#पूर्ण_अगर
