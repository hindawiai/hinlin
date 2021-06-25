<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ntb.h>
#समावेश <linux/pci.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/workqueue.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("0.1");
MODULE_AUTHOR("Logan Gunthorpe <logang@deltatee.com>");
MODULE_DESCRIPTION("Test for sending MSI interrupts over an NTB memory window");

अटल पूर्णांक num_irqs = 4;
module_param(num_irqs, पूर्णांक, 0644);
MODULE_PARM_DESC(num_irqs, "number of irqs to use");

काष्ठा ntb_msit_ctx अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा dentry *dbgfs_dir;
	काष्ठा work_काष्ठा setup_work;

	काष्ठा ntb_msit_isr_ctx अणु
		पूर्णांक irq_idx;
		पूर्णांक irq_num;
		पूर्णांक occurrences;
		काष्ठा ntb_msit_ctx *nm;
		काष्ठा ntb_msi_desc desc;
	पूर्ण *isr_ctx;

	काष्ठा ntb_msit_peer अणु
		काष्ठा ntb_msit_ctx *nm;
		पूर्णांक pidx;
		पूर्णांक num_irqs;
		काष्ठा completion init_comp;
		काष्ठा ntb_msi_desc *msi_desc;
	पूर्ण peers[];
पूर्ण;

अटल काष्ठा dentry *ntb_msit_dbgfs_topdir;

अटल irqवापस_t ntb_msit_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ntb_msit_isr_ctx *isr_ctx = dev;
	काष्ठा ntb_msit_ctx *nm = isr_ctx->nm;

	dev_dbg(&nm->ntb->dev, "Interrupt Occurred: %d",
		isr_ctx->irq_idx);

	isr_ctx->occurrences++;

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ntb_msit_setup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ntb_msit_ctx *nm = container_of(work, काष्ठा ntb_msit_ctx,
					       setup_work);
	पूर्णांक irq_count = 0;
	पूर्णांक irq;
	पूर्णांक ret;
	uपूर्णांकptr_t i;

	ret = ntb_msi_setup_mws(nm->ntb);
	अगर (ret) अणु
		dev_err(&nm->ntb->dev, "Unable to setup MSI windows: %d\n",
			ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_irqs; i++) अणु
		nm->isr_ctx[i].irq_idx = i;
		nm->isr_ctx[i].nm = nm;

		अगर (!nm->isr_ctx[i].irq_num) अणु
			irq = ntbm_msi_request_irq(nm->ntb, ntb_msit_isr,
						   KBUILD_MODNAME,
						   &nm->isr_ctx[i],
						   &nm->isr_ctx[i].desc);
			अगर (irq < 0)
				अवरोध;

			nm->isr_ctx[i].irq_num = irq;
		पूर्ण

		ret = ntb_spad_ग_लिखो(nm->ntb, 2 * i + 1,
				     nm->isr_ctx[i].desc.addr_offset);
		अगर (ret)
			अवरोध;

		ret = ntb_spad_ग_लिखो(nm->ntb, 2 * i + 2,
				     nm->isr_ctx[i].desc.data);
		अगर (ret)
			अवरोध;

		irq_count++;
	पूर्ण

	ntb_spad_ग_लिखो(nm->ntb, 0, irq_count);
	ntb_peer_db_set(nm->ntb, BIT(ntb_port_number(nm->ntb)));
पूर्ण

अटल व्योम ntb_msit_desc_changed(व्योम *ctx)
अणु
	काष्ठा ntb_msit_ctx *nm = ctx;
	पूर्णांक i;

	dev_dbg(&nm->ntb->dev, "MSI Descriptors Changed\n");

	क्रम (i = 0; i < num_irqs; i++) अणु
		ntb_spad_ग_लिखो(nm->ntb, 2 * i + 1,
			       nm->isr_ctx[i].desc.addr_offset);
		ntb_spad_ग_लिखो(nm->ntb, 2 * i + 2,
			       nm->isr_ctx[i].desc.data);
	पूर्ण

	ntb_peer_db_set(nm->ntb, BIT(ntb_port_number(nm->ntb)));
पूर्ण

अटल व्योम ntb_msit_link_event(व्योम *ctx)
अणु
	काष्ठा ntb_msit_ctx *nm = ctx;

	अगर (!ntb_link_is_up(nm->ntb, शून्य, शून्य))
		वापस;

	schedule_work(&nm->setup_work);
पूर्ण

अटल व्योम ntb_msit_copy_peer_desc(काष्ठा ntb_msit_ctx *nm, पूर्णांक peer)
अणु
	पूर्णांक i;
	काष्ठा ntb_msi_desc *desc = nm->peers[peer].msi_desc;
	पूर्णांक irq_count = nm->peers[peer].num_irqs;

	क्रम (i = 0; i < irq_count; i++) अणु
		desc[i].addr_offset = ntb_peer_spad_पढ़ो(nm->ntb, peer,
							 2 * i + 1);
		desc[i].data = ntb_peer_spad_पढ़ो(nm->ntb, peer, 2 * i + 2);
	पूर्ण

	dev_info(&nm->ntb->dev, "Found %d interrupts on peer %d\n",
		 irq_count, peer);

	complete_all(&nm->peers[peer].init_comp);
पूर्ण

अटल व्योम ntb_msit_db_event(व्योम *ctx, पूर्णांक vec)
अणु
	काष्ठा ntb_msit_ctx *nm = ctx;
	काष्ठा ntb_msi_desc *desc;
	u64 peer_mask = ntb_db_पढ़ो(nm->ntb);
	u32 irq_count;
	पूर्णांक peer;

	ntb_db_clear(nm->ntb, peer_mask);

	क्रम (peer = 0; peer < माप(peer_mask) * 8; peer++) अणु
		अगर (!(peer_mask & BIT(peer)))
			जारी;

		irq_count = ntb_peer_spad_पढ़ो(nm->ntb, peer, 0);
		अगर (irq_count == -1)
			जारी;

		desc = kसुस्मृति(irq_count, माप(*desc), GFP_ATOMIC);
		अगर (!desc)
			जारी;

		kमुक्त(nm->peers[peer].msi_desc);
		nm->peers[peer].msi_desc = desc;
		nm->peers[peer].num_irqs = irq_count;

		ntb_msit_copy_peer_desc(nm, peer);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ntb_ctx_ops ntb_msit_ops = अणु
	.link_event = ntb_msit_link_event,
	.db_event = ntb_msit_db_event,
पूर्ण;

अटल पूर्णांक ntb_msit_dbgfs_trigger(व्योम *data, u64 idx)
अणु
	काष्ठा ntb_msit_peer *peer = data;

	अगर (idx >= peer->num_irqs)
		वापस -EINVAL;

	dev_dbg(&peer->nm->ntb->dev, "trigger irq %llu on peer %u\n",
		idx, peer->pidx);

	वापस ntb_msi_peer_trigger(peer->nm->ntb, peer->pidx,
				    &peer->msi_desc[idx]);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_trigger_fops, शून्य,
			 ntb_msit_dbgfs_trigger, "%llu\n");

अटल पूर्णांक ntb_msit_dbgfs_port_get(व्योम *data, u64 *port)
अणु
	काष्ठा ntb_msit_peer *peer = data;

	*port = ntb_peer_port_number(peer->nm->ntb, peer->pidx);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_port_fops, ntb_msit_dbgfs_port_get,
			 शून्य, "%llu\n");

अटल पूर्णांक ntb_msit_dbgfs_count_get(व्योम *data, u64 *count)
अणु
	काष्ठा ntb_msit_peer *peer = data;

	*count = peer->num_irqs;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_count_fops, ntb_msit_dbgfs_count_get,
			 शून्य, "%llu\n");

अटल पूर्णांक ntb_msit_dbgfs_पढ़ोy_get(व्योम *data, u64 *पढ़ोy)
अणु
	काष्ठा ntb_msit_peer *peer = data;

	*पढ़ोy = try_रुको_क्रम_completion(&peer->init_comp);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_msit_dbgfs_पढ़ोy_set(व्योम *data, u64 पढ़ोy)
अणु
	काष्ठा ntb_msit_peer *peer = data;

	वापस रुको_क्रम_completion_पूर्णांकerruptible(&peer->init_comp);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_पढ़ोy_fops, ntb_msit_dbgfs_पढ़ोy_get,
			 ntb_msit_dbgfs_पढ़ोy_set, "%llu\n");

अटल पूर्णांक ntb_msit_dbgfs_occurrences_get(व्योम *data, u64 *occurrences)
अणु
	काष्ठा ntb_msit_isr_ctx *isr_ctx = data;

	*occurrences = isr_ctx->occurrences;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_occurrences_fops,
			 ntb_msit_dbgfs_occurrences_get,
			 शून्य, "%llu\n");

अटल पूर्णांक ntb_msit_dbgfs_local_port_get(व्योम *data, u64 *port)
अणु
	काष्ठा ntb_msit_ctx *nm = data;

	*port = ntb_port_number(nm->ntb);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ntb_msit_local_port_fops,
			 ntb_msit_dbgfs_local_port_get,
			 शून्य, "%llu\n");

अटल व्योम ntb_msit_create_dbgfs(काष्ठा ntb_msit_ctx *nm)
अणु
	काष्ठा pci_dev *pdev = nm->ntb->pdev;
	अक्षर buf[32];
	पूर्णांक i;
	काष्ठा dentry *peer_dir;

	nm->dbgfs_dir = debugfs_create_dir(pci_name(pdev),
					   ntb_msit_dbgfs_topdir);
	debugfs_create_file("port", 0400, nm->dbgfs_dir, nm,
			    &ntb_msit_local_port_fops);

	क्रम (i = 0; i < ntb_peer_port_count(nm->ntb); i++) अणु
		nm->peers[i].pidx = i;
		nm->peers[i].nm = nm;
		init_completion(&nm->peers[i].init_comp);

		snम_लिखो(buf, माप(buf), "peer%d", i);
		peer_dir = debugfs_create_dir(buf, nm->dbgfs_dir);

		debugfs_create_file_unsafe("trigger", 0200, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_trigger_fops);

		debugfs_create_file_unsafe("port", 0400, peer_dir,
					   &nm->peers[i], &ntb_msit_port_fops);

		debugfs_create_file_unsafe("count", 0400, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_count_fops);

		debugfs_create_file_unsafe("ready", 0600, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_पढ़ोy_fops);
	पूर्ण

	क्रम (i = 0; i < num_irqs; i++) अणु
		snम_लिखो(buf, माप(buf), "irq%d_occurrences", i);
		debugfs_create_file_unsafe(buf, 0400, nm->dbgfs_dir,
					   &nm->isr_ctx[i],
					   &ntb_msit_occurrences_fops);
	पूर्ण
पूर्ण

अटल व्योम ntb_msit_हटाओ_dbgfs(काष्ठा ntb_msit_ctx *nm)
अणु
	debugfs_हटाओ_recursive(nm->dbgfs_dir);
पूर्ण

अटल पूर्णांक ntb_msit_probe(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा ntb_msit_ctx *nm;
	पूर्णांक peers;
	पूर्णांक ret;

	peers = ntb_peer_port_count(ntb);
	अगर (peers <= 0)
		वापस -EINVAL;

	अगर (ntb_spad_is_unsafe(ntb) || ntb_spad_count(ntb) < 2 * num_irqs + 1) अणु
		dev_err(&ntb->dev, "NTB MSI test requires at least %d spads for %d irqs\n",
			2 * num_irqs + 1, num_irqs);
		वापस -EFAULT;
	पूर्ण

	ret = ntb_spad_ग_लिखो(ntb, 0, -1);
	अगर (ret) अणु
		dev_err(&ntb->dev, "Unable to write spads: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ntb_db_clear_mask(ntb, GENMASK(peers - 1, 0));
	अगर (ret) अणु
		dev_err(&ntb->dev, "Unable to clear doorbell mask: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ntb_msi_init(ntb, ntb_msit_desc_changed);
	अगर (ret) अणु
		dev_err(&ntb->dev, "Unable to initialize MSI library: %d\n",
			ret);
		वापस ret;
	पूर्ण

	nm = devm_kzalloc(&ntb->dev, काष्ठा_size(nm, peers, peers), GFP_KERNEL);
	अगर (!nm)
		वापस -ENOMEM;

	nm->isr_ctx = devm_kसुस्मृति(&ntb->dev, num_irqs, माप(*nm->isr_ctx),
				   GFP_KERNEL);
	अगर (!nm->isr_ctx)
		वापस -ENOMEM;

	INIT_WORK(&nm->setup_work, ntb_msit_setup_work);
	nm->ntb = ntb;

	ntb_msit_create_dbgfs(nm);

	ret = ntb_set_ctx(ntb, nm, &ntb_msit_ops);
	अगर (ret)
		जाओ हटाओ_dbgfs;

	अगर (!nm->isr_ctx)
		जाओ हटाओ_dbgfs;

	ntb_link_enable(ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);

	वापस 0;

हटाओ_dbgfs:
	ntb_msit_हटाओ_dbgfs(nm);
	devm_kमुक्त(&ntb->dev, nm->isr_ctx);
	devm_kमुक्त(&ntb->dev, nm);
	वापस ret;
पूर्ण

अटल व्योम ntb_msit_हटाओ(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा ntb_msit_ctx *nm = ntb->ctx;
	पूर्णांक i;

	ntb_link_disable(ntb);
	ntb_db_set_mask(ntb, ntb_db_valid_mask(ntb));
	ntb_msi_clear_mws(ntb);

	क्रम (i = 0; i < ntb_peer_port_count(ntb); i++)
		kमुक्त(nm->peers[i].msi_desc);

	ntb_clear_ctx(ntb);
	ntb_msit_हटाओ_dbgfs(nm);
पूर्ण

अटल काष्ठा ntb_client ntb_msit_client = अणु
	.ops = अणु
		.probe = ntb_msit_probe,
		.हटाओ = ntb_msit_हटाओ
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ntb_msit_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (debugfs_initialized())
		ntb_msit_dbgfs_topdir = debugfs_create_dir(KBUILD_MODNAME,
							   शून्य);

	ret = ntb_रेजिस्टर_client(&ntb_msit_client);
	अगर (ret)
		debugfs_हटाओ_recursive(ntb_msit_dbgfs_topdir);

	वापस ret;
पूर्ण
module_init(ntb_msit_init);

अटल व्योम __निकास ntb_msit_निकास(व्योम)
अणु
	ntb_unरेजिस्टर_client(&ntb_msit_client);
	debugfs_हटाओ_recursive(ntb_msit_dbgfs_topdir);
पूर्ण
module_निकास(ntb_msit_निकास);
