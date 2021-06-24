<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_msi.c: Sparc64 MSI support common layer.
 *
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश "pci_impl.h"

अटल irqवापस_t sparc64_msiq_पूर्णांकerrupt(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा sparc64_msiq_cookie *msiq_cookie = cookie;
	काष्ठा pci_pbm_info *pbm = msiq_cookie->pbm;
	अचिन्हित दीर्घ msiqid = msiq_cookie->msiqid;
	स्थिर काष्ठा sparc64_msiq_ops *ops;
	अचिन्हित दीर्घ orig_head, head;
	पूर्णांक err;

	ops = pbm->msi_ops;

	err = ops->get_head(pbm, msiqid, &head);
	अगर (unlikely(err < 0))
		जाओ err_get_head;

	orig_head = head;
	क्रम (;;) अणु
		अचिन्हित दीर्घ msi;

		err = ops->dequeue_msi(pbm, msiqid, &head, &msi);
		अगर (likely(err > 0)) अणु
			अचिन्हित पूर्णांक irq;

			irq = pbm->msi_irq_table[msi - pbm->msi_first];
			generic_handle_irq(irq);
		पूर्ण

		अगर (unlikely(err < 0))
			जाओ err_dequeue;

		अगर (err == 0)
			अवरोध;
	पूर्ण
	अगर (likely(head != orig_head)) अणु
		err = ops->set_head(pbm, msiqid, head);
		अगर (unlikely(err < 0))
			जाओ err_set_head;
	पूर्ण
	वापस IRQ_HANDLED;

err_get_head:
	prपूर्णांकk(KERN_EMERG "MSI: Get head on msiqid[%lu] gives error %d\n",
	       msiqid, err);
	जाओ err_out;

err_dequeue:
	prपूर्णांकk(KERN_EMERG "MSI: Dequeue head[%lu] from msiqid[%lu] "
	       "gives error %d\n",
	       head, msiqid, err);
	जाओ err_out;

err_set_head:
	prपूर्णांकk(KERN_EMERG "MSI: Set head[%lu] on msiqid[%lu] "
	       "gives error %d\n",
	       head, msiqid, err);
	जाओ err_out;

err_out:
	वापस IRQ_NONE;
पूर्ण

अटल u32 pick_msiq(काष्ठा pci_pbm_info *pbm)
अणु
	अटल DEFINE_SPINLOCK(rotor_lock);
	अचिन्हित दीर्घ flags;
	u32 ret, rotor;

	spin_lock_irqsave(&rotor_lock, flags);

	rotor = pbm->msiq_rotor;
	ret = pbm->msiq_first + rotor;

	अगर (++rotor >= pbm->msiq_num)
		rotor = 0;
	pbm->msiq_rotor = rotor;

	spin_unlock_irqrestore(&rotor_lock, flags);

	वापस ret;
पूर्ण


अटल पूर्णांक alloc_msi(काष्ठा pci_pbm_info *pbm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pbm->msi_num; i++) अणु
		अगर (!test_and_set_bit(i, pbm->msi_biपंचांगap))
			वापस i + pbm->msi_first;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल व्योम मुक्त_msi(काष्ठा pci_pbm_info *pbm, पूर्णांक msi_num)
अणु
	msi_num -= pbm->msi_first;
	clear_bit(msi_num, pbm->msi_biपंचांगap);
पूर्ण

अटल काष्ठा irq_chip msi_irq = अणु
	.name		= "PCI-MSI",
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
	.irq_enable	= pci_msi_unmask_irq,
	.irq_disable	= pci_msi_mask_irq,
	/* XXX affinity XXX */
पूर्ण;

अटल पूर्णांक sparc64_setup_msi_irq(अचिन्हित पूर्णांक *irq_p,
				 काष्ठा pci_dev *pdev,
				 काष्ठा msi_desc *entry)
अणु
	काष्ठा pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	स्थिर काष्ठा sparc64_msiq_ops *ops = pbm->msi_ops;
	काष्ठा msi_msg msg;
	पूर्णांक msi, err;
	u32 msiqid;

	*irq_p = irq_alloc(0, 0);
	err = -ENOMEM;
	अगर (!*irq_p)
		जाओ out_err;

	irq_set_chip_and_handler_name(*irq_p, &msi_irq, handle_simple_irq,
				      "MSI");

	err = alloc_msi(pbm);
	अगर (unlikely(err < 0))
		जाओ out_irq_मुक्त;

	msi = err;

	msiqid = pick_msiq(pbm);

	err = ops->msi_setup(pbm, msiqid, msi,
			     (entry->msi_attrib.is_64 ? 1 : 0));
	अगर (err)
		जाओ out_msi_मुक्त;

	pbm->msi_irq_table[msi - pbm->msi_first] = *irq_p;

	अगर (entry->msi_attrib.is_64) अणु
		msg.address_hi = pbm->msi64_start >> 32;
		msg.address_lo = pbm->msi64_start & 0xffffffff;
	पूर्ण अन्यथा अणु
		msg.address_hi = 0;
		msg.address_lo = pbm->msi32_start;
	पूर्ण
	msg.data = msi;

	irq_set_msi_desc(*irq_p, entry);
	pci_ग_लिखो_msi_msg(*irq_p, &msg);

	वापस 0;

out_msi_मुक्त:
	मुक्त_msi(pbm, msi);

out_irq_मुक्त:
	irq_set_chip(*irq_p, शून्य);
	irq_मुक्त(*irq_p);
	*irq_p = 0;

out_err:
	वापस err;
पूर्ण

अटल व्योम sparc64_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq,
				     काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	स्थिर काष्ठा sparc64_msiq_ops *ops = pbm->msi_ops;
	अचिन्हित पूर्णांक msi_num;
	पूर्णांक i, err;

	क्रम (i = 0; i < pbm->msi_num; i++) अणु
		अगर (pbm->msi_irq_table[i] == irq)
			अवरोध;
	पूर्ण
	अगर (i >= pbm->msi_num) अणु
		pci_err(pdev, "%s: teardown: No MSI for irq %u\n", pbm->name,
			irq);
		वापस;
	पूर्ण

	msi_num = pbm->msi_first + i;
	pbm->msi_irq_table[i] = ~0U;

	err = ops->msi_tearकरोwn(pbm, msi_num);
	अगर (err) अणु
		pci_err(pdev, "%s: teardown: ops->teardown() on MSI %u, "
			"irq %u, gives error %d\n", pbm->name, msi_num, irq,
			err);
		वापस;
	पूर्ण

	मुक्त_msi(pbm, msi_num);

	irq_set_chip(irq, शून्य);
	irq_मुक्त(irq);
पूर्ण

अटल पूर्णांक msi_biपंचांगap_alloc(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ size, bits_per_uदीर्घ;

	bits_per_uदीर्घ = माप(अचिन्हित दीर्घ) * 8;
	size = (pbm->msi_num + (bits_per_uदीर्घ - 1)) & ~(bits_per_uदीर्घ - 1);
	size /= 8;
	BUG_ON(size % माप(अचिन्हित दीर्घ));

	pbm->msi_biपंचांगap = kzalloc(size, GFP_KERNEL);
	अगर (!pbm->msi_biपंचांगap)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम msi_biपंचांगap_मुक्त(काष्ठा pci_pbm_info *pbm)
अणु
	kमुक्त(pbm->msi_biपंचांगap);
	pbm->msi_biपंचांगap = शून्य;
पूर्ण

अटल पूर्णांक msi_table_alloc(काष्ठा pci_pbm_info *pbm)
अणु
	पूर्णांक size, i;

	size = pbm->msiq_num * माप(काष्ठा sparc64_msiq_cookie);
	pbm->msiq_irq_cookies = kzalloc(size, GFP_KERNEL);
	अगर (!pbm->msiq_irq_cookies)
		वापस -ENOMEM;

	क्रम (i = 0; i < pbm->msiq_num; i++) अणु
		काष्ठा sparc64_msiq_cookie *p;

		p = &pbm->msiq_irq_cookies[i];
		p->pbm = pbm;
		p->msiqid = pbm->msiq_first + i;
	पूर्ण

	size = pbm->msi_num * माप(अचिन्हित पूर्णांक);
	pbm->msi_irq_table = kzalloc(size, GFP_KERNEL);
	अगर (!pbm->msi_irq_table) अणु
		kमुक्त(pbm->msiq_irq_cookies);
		pbm->msiq_irq_cookies = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम msi_table_मुक्त(काष्ठा pci_pbm_info *pbm)
अणु
	kमुक्त(pbm->msiq_irq_cookies);
	pbm->msiq_irq_cookies = शून्य;

	kमुक्त(pbm->msi_irq_table);
	pbm->msi_irq_table = शून्य;
पूर्ण

अटल पूर्णांक bringup_one_msi_queue(काष्ठा pci_pbm_info *pbm,
				 स्थिर काष्ठा sparc64_msiq_ops *ops,
				 अचिन्हित दीर्घ msiqid,
				 अचिन्हित दीर्घ devino)
अणु
	पूर्णांक irq = ops->msiq_build_irq(pbm, msiqid, devino);
	पूर्णांक err, nid;

	अगर (irq < 0)
		वापस irq;

	nid = pbm->numa_node;
	अगर (nid != -1) अणु
		cpumask_t numa_mask;

		cpumask_copy(&numa_mask, cpumask_of_node(nid));
		irq_set_affinity(irq, &numa_mask);
	पूर्ण
	err = request_irq(irq, sparc64_msiq_पूर्णांकerrupt, 0,
			  "MSIQ",
			  &pbm->msiq_irq_cookies[msiqid - pbm->msiq_first]);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक sparc64_bringup_msi_queues(काष्ठा pci_pbm_info *pbm,
				      स्थिर काष्ठा sparc64_msiq_ops *ops)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pbm->msiq_num; i++) अणु
		अचिन्हित दीर्घ msiqid = i + pbm->msiq_first;
		अचिन्हित दीर्घ devino = i + pbm->msiq_first_devino;
		पूर्णांक err;

		err = bringup_one_msi_queue(pbm, ops, msiqid, devino);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sparc64_pbm_msi_init(काष्ठा pci_pbm_info *pbm,
			  स्थिर काष्ठा sparc64_msiq_ops *ops)
अणु
	स्थिर u32 *val;
	पूर्णांक len;

	val = of_get_property(pbm->op->dev.of_node, "#msi-eqs", &len);
	अगर (!val || len != 4)
		जाओ no_msi;
	pbm->msiq_num = *val;
	अगर (pbm->msiq_num) अणु
		स्थिर काष्ठा msiq_prop अणु
			u32 first_msiq;
			u32 num_msiq;
			u32 first_devino;
		पूर्ण *mqp;
		स्थिर काष्ठा msi_range_prop अणु
			u32 first_msi;
			u32 num_msi;
		पूर्ण *mrng;
		स्थिर काष्ठा addr_range_prop अणु
			u32 msi32_high;
			u32 msi32_low;
			u32 msi32_len;
			u32 msi64_high;
			u32 msi64_low;
			u32 msi64_len;
		पूर्ण *arng;

		val = of_get_property(pbm->op->dev.of_node, "msi-eq-size", &len);
		अगर (!val || len != 4)
			जाओ no_msi;

		pbm->msiq_ent_count = *val;

		mqp = of_get_property(pbm->op->dev.of_node,
				      "msi-eq-to-devino", &len);
		अगर (!mqp)
			mqp = of_get_property(pbm->op->dev.of_node,
					      "msi-eq-devino", &len);
		अगर (!mqp || len != माप(काष्ठा msiq_prop))
			जाओ no_msi;

		pbm->msiq_first = mqp->first_msiq;
		pbm->msiq_first_devino = mqp->first_devino;

		val = of_get_property(pbm->op->dev.of_node, "#msi", &len);
		अगर (!val || len != 4)
			जाओ no_msi;
		pbm->msi_num = *val;

		mrng = of_get_property(pbm->op->dev.of_node, "msi-ranges", &len);
		अगर (!mrng || len != माप(काष्ठा msi_range_prop))
			जाओ no_msi;
		pbm->msi_first = mrng->first_msi;

		val = of_get_property(pbm->op->dev.of_node, "msi-data-mask", &len);
		अगर (!val || len != 4)
			जाओ no_msi;
		pbm->msi_data_mask = *val;

		val = of_get_property(pbm->op->dev.of_node, "msix-data-width", &len);
		अगर (!val || len != 4)
			जाओ no_msi;
		pbm->msix_data_width = *val;

		arng = of_get_property(pbm->op->dev.of_node, "msi-address-ranges",
				       &len);
		अगर (!arng || len != माप(काष्ठा addr_range_prop))
			जाओ no_msi;
		pbm->msi32_start = ((u64)arng->msi32_high << 32) |
			(u64) arng->msi32_low;
		pbm->msi64_start = ((u64)arng->msi64_high << 32) |
			(u64) arng->msi64_low;
		pbm->msi32_len = arng->msi32_len;
		pbm->msi64_len = arng->msi64_len;

		अगर (msi_biपंचांगap_alloc(pbm))
			जाओ no_msi;

		अगर (msi_table_alloc(pbm)) अणु
			msi_biपंचांगap_मुक्त(pbm);
			जाओ no_msi;
		पूर्ण

		अगर (ops->msiq_alloc(pbm)) अणु
			msi_table_मुक्त(pbm);
			msi_biपंचांगap_मुक्त(pbm);
			जाओ no_msi;
		पूर्ण

		अगर (sparc64_bringup_msi_queues(pbm, ops)) अणु
			ops->msiq_मुक्त(pbm);
			msi_table_मुक्त(pbm);
			msi_biपंचांगap_मुक्त(pbm);
			जाओ no_msi;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s: MSI Queue first[%u] num[%u] count[%u] "
		       "devino[0x%x]\n",
		       pbm->name,
		       pbm->msiq_first, pbm->msiq_num,
		       pbm->msiq_ent_count,
		       pbm->msiq_first_devino);
		prपूर्णांकk(KERN_INFO "%s: MSI first[%u] num[%u] mask[0x%x] "
		       "width[%u]\n",
		       pbm->name,
		       pbm->msi_first, pbm->msi_num, pbm->msi_data_mask,
		       pbm->msix_data_width);
		prपूर्णांकk(KERN_INFO "%s: MSI addr32[0x%llx:0x%x] "
		       "addr64[0x%llx:0x%x]\n",
		       pbm->name,
		       pbm->msi32_start, pbm->msi32_len,
		       pbm->msi64_start, pbm->msi64_len);
		prपूर्णांकk(KERN_INFO "%s: MSI queues at RA [%016lx]\n",
		       pbm->name,
		       __pa(pbm->msi_queues));

		pbm->msi_ops = ops;
		pbm->setup_msi_irq = sparc64_setup_msi_irq;
		pbm->tearकरोwn_msi_irq = sparc64_tearकरोwn_msi_irq;
	पूर्ण
	वापस;

no_msi:
	pbm->msiq_num = 0;
	prपूर्णांकk(KERN_INFO "%s: No MSI support.\n", pbm->name);
पूर्ण
