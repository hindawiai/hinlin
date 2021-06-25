<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell UMI driver
 *
 * Copyright 2011 Marvell. <jyli@marvell.com>
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/पन.स>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "mvumi.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jyli@marvell.com");
MODULE_DESCRIPTION("Marvell UMI Driver");

अटल स्थिर काष्ठा pci_device_id mvumi_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, PCI_DEVICE_ID_MARVELL_MV9143) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, PCI_DEVICE_ID_MARVELL_MV9580) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mvumi_pci_table);

अटल व्योम tag_init(काष्ठा mvumi_tag *st, अचिन्हित लघु size)
अणु
	अचिन्हित लघु i;
	BUG_ON(size != st->size);
	st->top = size;
	क्रम (i = 0; i < size; i++)
		st->stack[i] = size - 1 - i;
पूर्ण

अटल अचिन्हित लघु tag_get_one(काष्ठा mvumi_hba *mhba, काष्ठा mvumi_tag *st)
अणु
	BUG_ON(st->top <= 0);
	वापस st->stack[--st->top];
पूर्ण

अटल व्योम tag_release_one(काष्ठा mvumi_hba *mhba, काष्ठा mvumi_tag *st,
							अचिन्हित लघु tag)
अणु
	BUG_ON(st->top >= st->size);
	st->stack[st->top++] = tag;
पूर्ण

अटल bool tag_is_empty(काष्ठा mvumi_tag *st)
अणु
	अगर (st->top == 0)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम mvumi_unmap_pci_addr(काष्ठा pci_dev *dev, व्योम **addr_array)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BASE_ADDRESS; i++)
		अगर ((pci_resource_flags(dev, i) & IORESOURCE_MEM) &&
								addr_array[i])
			pci_iounmap(dev, addr_array[i]);
पूर्ण

अटल पूर्णांक mvumi_map_pci_addr(काष्ठा pci_dev *dev, व्योम **addr_array)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BASE_ADDRESS; i++) अणु
		अगर (pci_resource_flags(dev, i) & IORESOURCE_MEM) अणु
			addr_array[i] = pci_iomap(dev, i, 0);
			अगर (!addr_array[i]) अणु
				dev_err(&dev->dev, "failed to map Bar[%d]\n",
									i);
				mvumi_unmap_pci_addr(dev, addr_array);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा
			addr_array[i] = शून्य;

		dev_dbg(&dev->dev, "Bar %d : %p.\n", i, addr_array[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mvumi_res *mvumi_alloc_mem_resource(काष्ठा mvumi_hba *mhba,
				क्रमागत resource_type type, अचिन्हित पूर्णांक size)
अणु
	काष्ठा mvumi_res *res = kzalloc(माप(*res), GFP_ATOMIC);

	अगर (!res) अणु
		dev_err(&mhba->pdev->dev,
			"Failed to allocate memory for resource manager.\n");
		वापस शून्य;
	पूर्ण

	चयन (type) अणु
	हाल RESOURCE_CACHED_MEMORY:
		res->virt_addr = kzalloc(size, GFP_ATOMIC);
		अगर (!res->virt_addr) अणु
			dev_err(&mhba->pdev->dev,
				"unable to allocate memory,size = %d.\n", size);
			kमुक्त(res);
			वापस शून्य;
		पूर्ण
		अवरोध;

	हाल RESOURCE_UNCACHED_MEMORY:
		size = round_up(size, 8);
		res->virt_addr = dma_alloc_coherent(&mhba->pdev->dev, size,
						    &res->bus_addr,
						    GFP_KERNEL);
		अगर (!res->virt_addr) अणु
			dev_err(&mhba->pdev->dev,
					"unable to allocate consistent mem,"
							"size = %d.\n", size);
			kमुक्त(res);
			वापस शून्य;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(&mhba->pdev->dev, "unknown resource type %d.\n", type);
		kमुक्त(res);
		वापस शून्य;
	पूर्ण

	res->type = type;
	res->size = size;
	INIT_LIST_HEAD(&res->entry);
	list_add_tail(&res->entry, &mhba->res_list);

	वापस res;
पूर्ण

अटल व्योम mvumi_release_mem_resource(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, &mhba->res_list, entry) अणु
		चयन (res->type) अणु
		हाल RESOURCE_UNCACHED_MEMORY:
			dma_मुक्त_coherent(&mhba->pdev->dev, res->size,
						res->virt_addr, res->bus_addr);
			अवरोध;
		हाल RESOURCE_CACHED_MEMORY:
			kमुक्त(res->virt_addr);
			अवरोध;
		शेष:
			dev_err(&mhba->pdev->dev,
				"unknown resource type %d\n", res->type);
			अवरोध;
		पूर्ण
		list_del(&res->entry);
		kमुक्त(res);
	पूर्ण
	mhba->fw_flag &= ~MVUMI_FW_ALLOC;
पूर्ण

/**
 * mvumi_make_sgl -	Prepares  SGL
 * @mhba:		Adapter soft state
 * @scmd:		SCSI command from the mid-layer
 * @sgl_p:		SGL to be filled in
 * @sg_count:		वापस the number of SG elements
 *
 * If successful, this function वापसs 0. otherwise, it वापसs -1.
 */
अटल पूर्णांक mvumi_make_sgl(काष्ठा mvumi_hba *mhba, काष्ठा scsi_cmnd *scmd,
					व्योम *sgl_p, अचिन्हित अक्षर *sg_count)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा mvumi_sgl *m_sg = (काष्ठा mvumi_sgl *) sgl_p;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक sgnum = scsi_sg_count(scmd);
	dma_addr_t busaddr;

	*sg_count = dma_map_sg(&mhba->pdev->dev, scsi_sglist(scmd), sgnum,
			       scmd->sc_data_direction);
	अगर (*sg_count > mhba->max_sge) अणु
		dev_err(&mhba->pdev->dev,
			"sg count[0x%x] is bigger than max sg[0x%x].\n",
			*sg_count, mhba->max_sge);
		dma_unmap_sg(&mhba->pdev->dev, scsi_sglist(scmd), sgnum,
			     scmd->sc_data_direction);
		वापस -1;
	पूर्ण
	scsi_क्रम_each_sg(scmd, sg, *sg_count, i) अणु
		busaddr = sg_dma_address(sg);
		m_sg->baseaddr_l = cpu_to_le32(lower_32_bits(busaddr));
		m_sg->baseaddr_h = cpu_to_le32(upper_32_bits(busaddr));
		m_sg->flags = 0;
		sgd_setsz(mhba, m_sg, cpu_to_le32(sg_dma_len(sg)));
		अगर ((i + 1) == *sg_count)
			m_sg->flags |= 1U << mhba->eot_flag;

		sgd_inc(mhba, m_sg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvumi_पूर्णांकernal_cmd_sgl(काष्ठा mvumi_hba *mhba, काष्ठा mvumi_cmd *cmd,
							अचिन्हित पूर्णांक size)
अणु
	काष्ठा mvumi_sgl *m_sg;
	व्योम *virt_addr;
	dma_addr_t phy_addr;

	अगर (size == 0)
		वापस 0;

	virt_addr = dma_alloc_coherent(&mhba->pdev->dev, size, &phy_addr,
				       GFP_KERNEL);
	अगर (!virt_addr)
		वापस -1;

	m_sg = (काष्ठा mvumi_sgl *) &cmd->frame->payload[0];
	cmd->frame->sg_counts = 1;
	cmd->data_buf = virt_addr;

	m_sg->baseaddr_l = cpu_to_le32(lower_32_bits(phy_addr));
	m_sg->baseaddr_h = cpu_to_le32(upper_32_bits(phy_addr));
	m_sg->flags = 1U << mhba->eot_flag;
	sgd_setsz(mhba, m_sg, cpu_to_le32(size));

	वापस 0;
पूर्ण

अटल काष्ठा mvumi_cmd *mvumi_create_पूर्णांकernal_cmd(काष्ठा mvumi_hba *mhba,
				अचिन्हित पूर्णांक buf_size)
अणु
	काष्ठा mvumi_cmd *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		dev_err(&mhba->pdev->dev, "failed to create a internal cmd\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&cmd->queue_poपूर्णांकer);

	cmd->frame = dma_alloc_coherent(&mhba->pdev->dev, mhba->ib_max_size,
			&cmd->frame_phys, GFP_KERNEL);
	अगर (!cmd->frame) अणु
		dev_err(&mhba->pdev->dev, "failed to allocate memory for FW"
			" frame,size = %d.\n", mhba->ib_max_size);
		kमुक्त(cmd);
		वापस शून्य;
	पूर्ण

	अगर (buf_size) अणु
		अगर (mvumi_पूर्णांकernal_cmd_sgl(mhba, cmd, buf_size)) अणु
			dev_err(&mhba->pdev->dev, "failed to allocate memory"
						" for internal frame\n");
			dma_मुक्त_coherent(&mhba->pdev->dev, mhba->ib_max_size,
					cmd->frame, cmd->frame_phys);
			kमुक्त(cmd);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा
		cmd->frame->sg_counts = 0;

	वापस cmd;
पूर्ण

अटल व्योम mvumi_delete_पूर्णांकernal_cmd(काष्ठा mvumi_hba *mhba,
						काष्ठा mvumi_cmd *cmd)
अणु
	काष्ठा mvumi_sgl *m_sg;
	अचिन्हित पूर्णांक size;
	dma_addr_t phy_addr;

	अगर (cmd && cmd->frame) अणु
		अगर (cmd->frame->sg_counts) अणु
			m_sg = (काष्ठा mvumi_sgl *) &cmd->frame->payload[0];
			sgd_माला_लोz(mhba, m_sg, size);

			phy_addr = (dma_addr_t) m_sg->baseaddr_l |
				(dma_addr_t) ((m_sg->baseaddr_h << 16) << 16);

			dma_मुक्त_coherent(&mhba->pdev->dev, size, cmd->data_buf,
								phy_addr);
		पूर्ण
		dma_मुक्त_coherent(&mhba->pdev->dev, mhba->ib_max_size,
				cmd->frame, cmd->frame_phys);
		kमुक्त(cmd);
	पूर्ण
पूर्ण

/**
 * mvumi_get_cmd -	Get a command from the मुक्त pool
 * @mhba:		Adapter soft state
 *
 * Returns a मुक्त command from the pool
 */
अटल काष्ठा mvumi_cmd *mvumi_get_cmd(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_cmd *cmd = शून्य;

	अगर (likely(!list_empty(&mhba->cmd_pool))) अणु
		cmd = list_entry((&mhba->cmd_pool)->next,
				काष्ठा mvumi_cmd, queue_poपूर्णांकer);
		list_del_init(&cmd->queue_poपूर्णांकer);
	पूर्ण अन्यथा
		dev_warn(&mhba->pdev->dev, "command pool is empty!\n");

	वापस cmd;
पूर्ण

/**
 * mvumi_वापस_cmd -	Return a cmd to मुक्त command pool
 * @mhba:		Adapter soft state
 * @cmd:		Command packet to be वापसed to मुक्त command pool
 */
अटल अंतरभूत व्योम mvumi_वापस_cmd(काष्ठा mvumi_hba *mhba,
						काष्ठा mvumi_cmd *cmd)
अणु
	cmd->scmd = शून्य;
	list_add_tail(&cmd->queue_poपूर्णांकer, &mhba->cmd_pool);
पूर्ण

/**
 * mvumi_मुक्त_cmds -	Free all the cmds in the मुक्त cmd pool
 * @mhba:		Adapter soft state
 */
अटल व्योम mvumi_मुक्त_cmds(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_cmd *cmd;

	जबतक (!list_empty(&mhba->cmd_pool)) अणु
		cmd = list_first_entry(&mhba->cmd_pool, काष्ठा mvumi_cmd,
							queue_poपूर्णांकer);
		list_del(&cmd->queue_poपूर्णांकer);
		अगर (!(mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC))
			kमुक्त(cmd->frame);
		kमुक्त(cmd);
	पूर्ण
पूर्ण

/**
 * mvumi_alloc_cmds -	Allocates the command packets
 * @mhba:		Adapter soft state
 *
 */
अटल पूर्णांक mvumi_alloc_cmds(काष्ठा mvumi_hba *mhba)
अणु
	पूर्णांक i;
	काष्ठा mvumi_cmd *cmd;

	क्रम (i = 0; i < mhba->max_io; i++) अणु
		cmd = kzalloc(माप(*cmd), GFP_KERNEL);
		अगर (!cmd)
			जाओ err_निकास;

		INIT_LIST_HEAD(&cmd->queue_poपूर्णांकer);
		list_add_tail(&cmd->queue_poपूर्णांकer, &mhba->cmd_pool);
		अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) अणु
			cmd->frame = mhba->ib_frame + i * mhba->ib_max_size;
			cmd->frame_phys = mhba->ib_frame_phys
						+ i * mhba->ib_max_size;
		पूर्ण अन्यथा
			cmd->frame = kzalloc(mhba->ib_max_size, GFP_KERNEL);
		अगर (!cmd->frame)
			जाओ err_निकास;
	पूर्ण
	वापस 0;

err_निकास:
	dev_err(&mhba->pdev->dev,
			"failed to allocate memory for cmd[0x%x].\n", i);
	जबतक (!list_empty(&mhba->cmd_pool)) अणु
		cmd = list_first_entry(&mhba->cmd_pool, काष्ठा mvumi_cmd,
						queue_poपूर्णांकer);
		list_del(&cmd->queue_poपूर्णांकer);
		अगर (!(mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC))
			kमुक्त(cmd->frame);
		kमुक्त(cmd);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित पूर्णांक mvumi_check_ib_list_9143(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक ib_rp_reg;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	ib_rp_reg = ioपढ़ो32(mhba->regs->inb_पढ़ो_poपूर्णांकer);

	अगर (unlikely(((ib_rp_reg & regs->cl_slot_num_mask) ==
			(mhba->ib_cur_slot & regs->cl_slot_num_mask)) &&
			((ib_rp_reg & regs->cl_poपूर्णांकer_toggle)
			 != (mhba->ib_cur_slot & regs->cl_poपूर्णांकer_toggle)))) अणु
		dev_warn(&mhba->pdev->dev, "no free slot to use.\n");
		वापस 0;
	पूर्ण
	अगर (atomic_पढ़ो(&mhba->fw_outstanding) >= mhba->max_io) अणु
		dev_warn(&mhba->pdev->dev, "firmware io overflow.\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस mhba->max_io - atomic_पढ़ो(&mhba->fw_outstanding);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक mvumi_check_ib_list_9580(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक count;
	अगर (atomic_पढ़ो(&mhba->fw_outstanding) >= (mhba->max_io - 1))
		वापस 0;
	count = ioपढ़ो32(mhba->ib_shaकरोw);
	अगर (count == 0xffff)
		वापस 0;
	वापस count;
पूर्ण

अटल व्योम mvumi_get_ib_list_entry(काष्ठा mvumi_hba *mhba, व्योम **ib_entry)
अणु
	अचिन्हित पूर्णांक cur_ib_entry;

	cur_ib_entry = mhba->ib_cur_slot & mhba->regs->cl_slot_num_mask;
	cur_ib_entry++;
	अगर (cur_ib_entry >= mhba->list_num_io) अणु
		cur_ib_entry -= mhba->list_num_io;
		mhba->ib_cur_slot ^= mhba->regs->cl_poपूर्णांकer_toggle;
	पूर्ण
	mhba->ib_cur_slot &= ~mhba->regs->cl_slot_num_mask;
	mhba->ib_cur_slot |= (cur_ib_entry & mhba->regs->cl_slot_num_mask);
	अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) अणु
		*ib_entry = mhba->ib_list + cur_ib_entry *
				माप(काष्ठा mvumi_dyn_list_entry);
	पूर्ण अन्यथा अणु
		*ib_entry = mhba->ib_list + cur_ib_entry * mhba->ib_max_size;
	पूर्ण
	atomic_inc(&mhba->fw_outstanding);
पूर्ण

अटल व्योम mvumi_send_ib_list_entry(काष्ठा mvumi_hba *mhba)
अणु
	ioग_लिखो32(0xffff, mhba->ib_shaकरोw);
	ioग_लिखो32(mhba->ib_cur_slot, mhba->regs->inb_ग_लिखो_poपूर्णांकer);
पूर्ण

अटल अक्षर mvumi_check_ob_frame(काष्ठा mvumi_hba *mhba,
		अचिन्हित पूर्णांक cur_obf, काष्ठा mvumi_rsp_frame *p_outb_frame)
अणु
	अचिन्हित लघु tag, request_id;

	udelay(1);
	p_outb_frame = mhba->ob_list + cur_obf * mhba->ob_max_size;
	request_id = p_outb_frame->request_id;
	tag = p_outb_frame->tag;
	अगर (tag > mhba->tag_pool.size) अणु
		dev_err(&mhba->pdev->dev, "ob frame data error\n");
		वापस -1;
	पूर्ण
	अगर (mhba->tag_cmd[tag] == शून्य) अणु
		dev_err(&mhba->pdev->dev, "tag[0x%x] with NO command\n", tag);
		वापस -1;
	पूर्ण अन्यथा अगर (mhba->tag_cmd[tag]->request_id != request_id &&
						mhba->request_id_enabled) अणु
			dev_err(&mhba->pdev->dev, "request ID from FW:0x%x,"
					"cmd request ID:0x%x\n", request_id,
					mhba->tag_cmd[tag]->request_id);
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvumi_check_ob_list_9143(काष्ठा mvumi_hba *mhba,
			अचिन्हित पूर्णांक *cur_obf, अचिन्हित पूर्णांक *assign_obf_end)
अणु
	अचिन्हित पूर्णांक ob_ग_लिखो, ob_ग_लिखो_shaकरोw;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	करो अणु
		ob_ग_लिखो = ioपढ़ो32(regs->outb_copy_poपूर्णांकer);
		ob_ग_लिखो_shaकरोw = ioपढ़ो32(mhba->ob_shaकरोw);
	पूर्ण जबतक ((ob_ग_लिखो & regs->cl_slot_num_mask) != ob_ग_लिखो_shaकरोw);

	*cur_obf = mhba->ob_cur_slot & mhba->regs->cl_slot_num_mask;
	*assign_obf_end = ob_ग_लिखो & mhba->regs->cl_slot_num_mask;

	अगर ((ob_ग_लिखो & regs->cl_poपूर्णांकer_toggle) !=
			(mhba->ob_cur_slot & regs->cl_poपूर्णांकer_toggle)) अणु
		*assign_obf_end += mhba->list_num_io;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mvumi_check_ob_list_9580(काष्ठा mvumi_hba *mhba,
			अचिन्हित पूर्णांक *cur_obf, अचिन्हित पूर्णांक *assign_obf_end)
अणु
	अचिन्हित पूर्णांक ob_ग_लिखो;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	ob_ग_लिखो = ioपढ़ो32(regs->outb_पढ़ो_poपूर्णांकer);
	ob_ग_लिखो = ioपढ़ो32(regs->outb_copy_poपूर्णांकer);
	*cur_obf = mhba->ob_cur_slot & mhba->regs->cl_slot_num_mask;
	*assign_obf_end = ob_ग_लिखो & mhba->regs->cl_slot_num_mask;
	अगर (*assign_obf_end < *cur_obf)
		*assign_obf_end += mhba->list_num_io;
	अन्यथा अगर (*assign_obf_end == *cur_obf)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम mvumi_receive_ob_list_entry(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक cur_obf, assign_obf_end, i;
	काष्ठा mvumi_ob_data *ob_data;
	काष्ठा mvumi_rsp_frame *p_outb_frame;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	अगर (mhba->instancet->check_ob_list(mhba, &cur_obf, &assign_obf_end))
		वापस;

	क्रम (i = (assign_obf_end - cur_obf); i != 0; i--) अणु
		cur_obf++;
		अगर (cur_obf >= mhba->list_num_io) अणु
			cur_obf -= mhba->list_num_io;
			mhba->ob_cur_slot ^= regs->cl_poपूर्णांकer_toggle;
		पूर्ण

		p_outb_frame = mhba->ob_list + cur_obf * mhba->ob_max_size;

		/* Copy poपूर्णांकer may poपूर्णांक to entry in outbound list
		*  beक्रमe entry has valid data
		*/
		अगर (unlikely(p_outb_frame->tag > mhba->tag_pool.size ||
			mhba->tag_cmd[p_outb_frame->tag] == शून्य ||
			p_outb_frame->request_id !=
				mhba->tag_cmd[p_outb_frame->tag]->request_id))
			अगर (mvumi_check_ob_frame(mhba, cur_obf, p_outb_frame))
				जारी;

		अगर (!list_empty(&mhba->ob_data_list)) अणु
			ob_data = (काष्ठा mvumi_ob_data *)
				list_first_entry(&mhba->ob_data_list,
					काष्ठा mvumi_ob_data, list);
			list_del_init(&ob_data->list);
		पूर्ण अन्यथा अणु
			ob_data = शून्य;
			अगर (cur_obf == 0) अणु
				cur_obf = mhba->list_num_io - 1;
				mhba->ob_cur_slot ^= regs->cl_poपूर्णांकer_toggle;
			पूर्ण अन्यथा
				cur_obf -= 1;
			अवरोध;
		पूर्ण

		स_नकल(ob_data->data, p_outb_frame, mhba->ob_max_size);
		p_outb_frame->tag = 0xff;

		list_add_tail(&ob_data->list, &mhba->मुक्त_ob_list);
	पूर्ण
	mhba->ob_cur_slot &= ~regs->cl_slot_num_mask;
	mhba->ob_cur_slot |= (cur_obf & regs->cl_slot_num_mask);
	ioग_लिखो32(mhba->ob_cur_slot, regs->outb_पढ़ो_poपूर्णांकer);
पूर्ण

अटल व्योम mvumi_reset(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	ioग_लिखो32(0, regs->enpoपूर्णांकa_mask_reg);
	अगर (ioपढ़ो32(regs->arm_to_pciea_msg1) != HANDSHAKE_DONESTATE)
		वापस;

	ioग_लिखो32(DRBL_SOFT_RESET, regs->pciea_to_arm_drbl_reg);
पूर्ण

अटल अचिन्हित अक्षर mvumi_start(काष्ठा mvumi_hba *mhba);

अटल पूर्णांक mvumi_रुको_क्रम_outstanding(काष्ठा mvumi_hba *mhba)
अणु
	mhba->fw_state = FW_STATE_ABORT;
	mvumi_reset(mhba);

	अगर (mvumi_start(mhba))
		वापस FAILED;
	अन्यथा
		वापस SUCCESS;
पूर्ण

अटल पूर्णांक mvumi_रुको_क्रम_fw(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_hw_regs *regs = mhba->regs;
	u32 पंचांगp;
	अचिन्हित दीर्घ beक्रमe;
	beक्रमe = jअगरfies;

	ioग_लिखो32(0, regs->enpoपूर्णांकa_mask_reg);
	पंचांगp = ioपढ़ो32(regs->arm_to_pciea_msg1);
	जबतक (पंचांगp != HANDSHAKE_READYSTATE) अणु
		ioग_लिखो32(DRBL_MU_RESET, regs->pciea_to_arm_drbl_reg);
		अगर (समय_after(jअगरfies, beक्रमe + FW_MAX_DELAY * HZ)) अणु
			dev_err(&mhba->pdev->dev,
				"FW reset failed [0x%x].\n", पंचांगp);
			वापस FAILED;
		पूर्ण

		msleep(500);
		rmb();
		पंचांगp = ioपढ़ो32(regs->arm_to_pciea_msg1);
	पूर्ण

	वापस SUCCESS;
पूर्ण

अटल व्योम mvumi_backup_bar_addr(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित अक्षर i;

	क्रम (i = 0; i < MAX_BASE_ADDRESS; i++) अणु
		pci_पढ़ो_config_dword(mhba->pdev, 0x10 + i * 4,
						&mhba->pci_base[i]);
	पूर्ण
पूर्ण

अटल व्योम mvumi_restore_bar_addr(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित अक्षर i;

	क्रम (i = 0; i < MAX_BASE_ADDRESS; i++) अणु
		अगर (mhba->pci_base[i])
			pci_ग_लिखो_config_dword(mhba->pdev, 0x10 + i * 4,
						mhba->pci_base[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक mvumi_pci_set_master(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret = 0;

	pci_set_master(pdev);

	अगर (IS_DMA64) अणु
		अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))
			ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	पूर्ण अन्यथा
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));

	वापस ret;
पूर्ण

अटल पूर्णांक mvumi_reset_host_9580(काष्ठा mvumi_hba *mhba)
अणु
	mhba->fw_state = FW_STATE_ABORT;

	ioग_लिखो32(0, mhba->regs->reset_enable);
	ioग_लिखो32(0xf, mhba->regs->reset_request);

	ioग_लिखो32(0x10, mhba->regs->reset_enable);
	ioग_लिखो32(0x10, mhba->regs->reset_request);
	msleep(100);
	pci_disable_device(mhba->pdev);

	अगर (pci_enable_device(mhba->pdev)) अणु
		dev_err(&mhba->pdev->dev, "enable device failed\n");
		वापस FAILED;
	पूर्ण
	अगर (mvumi_pci_set_master(mhba->pdev)) अणु
		dev_err(&mhba->pdev->dev, "set master failed\n");
		वापस FAILED;
	पूर्ण
	mvumi_restore_bar_addr(mhba);
	अगर (mvumi_रुको_क्रम_fw(mhba) == FAILED)
		वापस FAILED;

	वापस mvumi_रुको_क्रम_outstanding(mhba);
पूर्ण

अटल पूर्णांक mvumi_reset_host_9143(काष्ठा mvumi_hba *mhba)
अणु
	वापस mvumi_रुको_क्रम_outstanding(mhba);
पूर्ण

अटल पूर्णांक mvumi_host_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा mvumi_hba *mhba;

	mhba = (काष्ठा mvumi_hba *) scmd->device->host->hostdata;

	scmd_prपूर्णांकk(KERN_NOTICE, scmd, "RESET -%u cmd=%x retries=%x\n",
			scmd->request->tag, scmd->cmnd[0], scmd->retries);

	वापस mhba->instancet->reset_host(mhba);
पूर्ण

अटल पूर्णांक mvumi_issue_blocked_cmd(काष्ठा mvumi_hba *mhba,
						काष्ठा mvumi_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	cmd->cmd_status = REQ_STATUS_PENDING;

	अगर (atomic_पढ़ो(&cmd->sync_cmd)) अणु
		dev_err(&mhba->pdev->dev,
			"last blocked cmd not finished, sync_cmd = %d\n",
						atomic_पढ़ो(&cmd->sync_cmd));
		BUG_ON(1);
		वापस -1;
	पूर्ण
	atomic_inc(&cmd->sync_cmd);
	spin_lock_irqsave(mhba->shost->host_lock, flags);
	mhba->instancet->fire_cmd(mhba, cmd);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);

	रुको_event_समयout(mhba->पूर्णांक_cmd_रुको_q,
		(cmd->cmd_status != REQ_STATUS_PENDING),
		MVUMI_INTERNAL_CMD_WAIT_TIME * HZ);

	/* command समयout */
	अगर (atomic_पढ़ो(&cmd->sync_cmd)) अणु
		spin_lock_irqsave(mhba->shost->host_lock, flags);
		atomic_dec(&cmd->sync_cmd);
		अगर (mhba->tag_cmd[cmd->frame->tag]) अणु
			mhba->tag_cmd[cmd->frame->tag] = शून्य;
			dev_warn(&mhba->pdev->dev, "TIMEOUT:release tag [%d]\n",
							cmd->frame->tag);
			tag_release_one(mhba, &mhba->tag_pool, cmd->frame->tag);
		पूर्ण
		अगर (!list_empty(&cmd->queue_poपूर्णांकer)) अणु
			dev_warn(&mhba->pdev->dev,
				"TIMEOUT:A internal command doesn't send!\n");
			list_del_init(&cmd->queue_poपूर्णांकer);
		पूर्ण अन्यथा
			atomic_dec(&mhba->fw_outstanding);

		spin_unlock_irqrestore(mhba->shost->host_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mvumi_release_fw(काष्ठा mvumi_hba *mhba)
अणु
	mvumi_मुक्त_cmds(mhba);
	mvumi_release_mem_resource(mhba);
	mvumi_unmap_pci_addr(mhba->pdev, mhba->base_addr);
	dma_मुक्त_coherent(&mhba->pdev->dev, HSP_MAX_SIZE,
		mhba->handshake_page, mhba->handshake_page_phys);
	kमुक्त(mhba->regs);
	pci_release_regions(mhba->pdev);
पूर्ण

अटल अचिन्हित अक्षर mvumi_flush_cache(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_cmd *cmd;
	काष्ठा mvumi_msg_frame *frame;
	अचिन्हित अक्षर device_id, retry = 0;
	अचिन्हित अक्षर bitcount = माप(अचिन्हित अक्षर) * 8;

	क्रम (device_id = 0; device_id < mhba->max_target_id; device_id++) अणु
		अगर (!(mhba->target_map[device_id / bitcount] &
				(1 << (device_id % bitcount))))
			जारी;
get_cmd:	cmd = mvumi_create_पूर्णांकernal_cmd(mhba, 0);
		अगर (!cmd) अणु
			अगर (retry++ >= 5) अणु
				dev_err(&mhba->pdev->dev, "failed to get memory"
					" for internal flush cache cmd for "
					"device %d", device_id);
				retry = 0;
				जारी;
			पूर्ण अन्यथा
				जाओ get_cmd;
		पूर्ण
		cmd->scmd = शून्य;
		cmd->cmd_status = REQ_STATUS_PENDING;
		atomic_set(&cmd->sync_cmd, 0);
		frame = cmd->frame;
		frame->req_function = CL_FUN_SCSI_CMD;
		frame->device_id = device_id;
		frame->cmd_flag = CMD_FLAG_NON_DATA;
		frame->data_transfer_length = 0;
		frame->cdb_length = MAX_COMMAND_SIZE;
		स_रखो(frame->cdb, 0, MAX_COMMAND_SIZE);
		frame->cdb[0] = SCSI_CMD_MARVELL_SPECIFIC;
		frame->cdb[1] = CDB_CORE_MODULE;
		frame->cdb[2] = CDB_CORE_SHUTDOWN;

		mvumi_issue_blocked_cmd(mhba, cmd);
		अगर (cmd->cmd_status != SAM_STAT_GOOD) अणु
			dev_err(&mhba->pdev->dev,
				"device %d flush cache failed, status=0x%x.\n",
				device_id, cmd->cmd_status);
		पूर्ण

		mvumi_delete_पूर्णांकernal_cmd(mhba, cmd);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर
mvumi_calculate_checksum(काष्ठा mvumi_hs_header *p_header,
							अचिन्हित लघु len)
अणु
	अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर ret = 0, i;

	ptr = (अचिन्हित अक्षर *) p_header->frame_content;
	क्रम (i = 0; i < len; i++) अणु
		ret ^= *ptr;
		ptr++;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mvumi_hs_build_page(काष्ठा mvumi_hba *mhba,
				काष्ठा mvumi_hs_header *hs_header)
अणु
	काष्ठा mvumi_hs_page2 *hs_page2;
	काष्ठा mvumi_hs_page4 *hs_page4;
	काष्ठा mvumi_hs_page3 *hs_page3;
	u64 समय;
	u64 local_समय;

	चयन (hs_header->page_code) अणु
	हाल HS_PAGE_HOST_INFO:
		hs_page2 = (काष्ठा mvumi_hs_page2 *) hs_header;
		hs_header->frame_length = माप(*hs_page2) - 4;
		स_रखो(hs_header->frame_content, 0, hs_header->frame_length);
		hs_page2->host_type = 3; /* 3 mean linux*/
		अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC)
			hs_page2->host_cap = 0x08;/* host dynamic source mode */
		hs_page2->host_ver.ver_major = VER_MAJOR;
		hs_page2->host_ver.ver_minor = VER_MINOR;
		hs_page2->host_ver.ver_oem = VER_OEM;
		hs_page2->host_ver.ver_build = VER_BUILD;
		hs_page2->प्रणाली_io_bus = 0;
		hs_page2->slot_number = 0;
		hs_page2->पूर्णांकr_level = 0;
		hs_page2->पूर्णांकr_vector = 0;
		समय = kसमय_get_real_seconds();
		local_समय = (समय - (sys_tz.tz_minuteswest * 60));
		hs_page2->seconds_since1970 = local_समय;
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		अवरोध;

	हाल HS_PAGE_FIRM_CTL:
		hs_page3 = (काष्ठा mvumi_hs_page3 *) hs_header;
		hs_header->frame_length = माप(*hs_page3) - 4;
		स_रखो(hs_header->frame_content, 0, hs_header->frame_length);
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		अवरोध;

	हाल HS_PAGE_CL_INFO:
		hs_page4 = (काष्ठा mvumi_hs_page4 *) hs_header;
		hs_header->frame_length = माप(*hs_page4) - 4;
		स_रखो(hs_header->frame_content, 0, hs_header->frame_length);
		hs_page4->ib_baseaddr_l = lower_32_bits(mhba->ib_list_phys);
		hs_page4->ib_baseaddr_h = upper_32_bits(mhba->ib_list_phys);

		hs_page4->ob_baseaddr_l = lower_32_bits(mhba->ob_list_phys);
		hs_page4->ob_baseaddr_h = upper_32_bits(mhba->ob_list_phys);
		hs_page4->ib_entry_size = mhba->ib_max_size_setting;
		hs_page4->ob_entry_size = mhba->ob_max_size_setting;
		अगर (mhba->hba_capability
			& HS_CAPABILITY_NEW_PAGE_IO_DEPTH_DEF) अणु
			hs_page4->ob_depth = find_first_bit((अचिन्हित दीर्घ *)
							    &mhba->list_num_io,
							    BITS_PER_LONG);
			hs_page4->ib_depth = find_first_bit((अचिन्हित दीर्घ *)
							    &mhba->list_num_io,
							    BITS_PER_LONG);
		पूर्ण अन्यथा अणु
			hs_page4->ob_depth = (u8) mhba->list_num_io;
			hs_page4->ib_depth = (u8) mhba->list_num_io;
		पूर्ण
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		अवरोध;

	शेष:
		dev_err(&mhba->pdev->dev, "cannot build page, code[0x%x]\n",
			hs_header->page_code);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * mvumi_init_data -	Initialize requested date क्रम FW
 * @mhba:			Adapter soft state
 */
अटल पूर्णांक mvumi_init_data(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_ob_data *ob_pool;
	काष्ठा mvumi_res *res_mgnt;
	अचिन्हित पूर्णांक पंचांगp_size, offset, i;
	व्योम *virmem, *v;
	dma_addr_t p;

	अगर (mhba->fw_flag & MVUMI_FW_ALLOC)
		वापस 0;

	पंचांगp_size = mhba->ib_max_size * mhba->max_io;
	अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC)
		पंचांगp_size += माप(काष्ठा mvumi_dyn_list_entry) * mhba->max_io;

	पंचांगp_size += 128 + mhba->ob_max_size * mhba->max_io;
	पंचांगp_size += 8 + माप(u32)*2 + 16;

	res_mgnt = mvumi_alloc_mem_resource(mhba,
					RESOURCE_UNCACHED_MEMORY, पंचांगp_size);
	अगर (!res_mgnt) अणु
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for inbound list\n");
		जाओ fail_alloc_dma_buf;
	पूर्ण

	p = res_mgnt->bus_addr;
	v = res_mgnt->virt_addr;
	/* ib_list */
	offset = round_up(p, 128) - p;
	p += offset;
	v += offset;
	mhba->ib_list = v;
	mhba->ib_list_phys = p;
	अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) अणु
		v += माप(काष्ठा mvumi_dyn_list_entry) * mhba->max_io;
		p += माप(काष्ठा mvumi_dyn_list_entry) * mhba->max_io;
		mhba->ib_frame = v;
		mhba->ib_frame_phys = p;
	पूर्ण
	v += mhba->ib_max_size * mhba->max_io;
	p += mhba->ib_max_size * mhba->max_io;

	/* ib shaकरोw */
	offset = round_up(p, 8) - p;
	p += offset;
	v += offset;
	mhba->ib_shaकरोw = v;
	mhba->ib_shaकरोw_phys = p;
	p += माप(u32)*2;
	v += माप(u32)*2;
	/* ob shaकरोw */
	अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580) अणु
		offset = round_up(p, 8) - p;
		p += offset;
		v += offset;
		mhba->ob_shaकरोw = v;
		mhba->ob_shaकरोw_phys = p;
		p += 8;
		v += 8;
	पूर्ण अन्यथा अणु
		offset = round_up(p, 4) - p;
		p += offset;
		v += offset;
		mhba->ob_shaकरोw = v;
		mhba->ob_shaकरोw_phys = p;
		p += 4;
		v += 4;
	पूर्ण

	/* ob list */
	offset = round_up(p, 128) - p;
	p += offset;
	v += offset;

	mhba->ob_list = v;
	mhba->ob_list_phys = p;

	/* ob data pool */
	पंचांगp_size = mhba->max_io * (mhba->ob_max_size + माप(*ob_pool));
	पंचांगp_size = round_up(पंचांगp_size, 8);

	res_mgnt = mvumi_alloc_mem_resource(mhba,
				RESOURCE_CACHED_MEMORY, पंचांगp_size);
	अगर (!res_mgnt) अणु
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for outbound data buffer\n");
		जाओ fail_alloc_dma_buf;
	पूर्ण
	virmem = res_mgnt->virt_addr;

	क्रम (i = mhba->max_io; i != 0; i--) अणु
		ob_pool = (काष्ठा mvumi_ob_data *) virmem;
		list_add_tail(&ob_pool->list, &mhba->ob_data_list);
		virmem += mhba->ob_max_size + माप(*ob_pool);
	पूर्ण

	पंचांगp_size = माप(अचिन्हित लघु) * mhba->max_io +
				माप(काष्ठा mvumi_cmd *) * mhba->max_io;
	पंचांगp_size += round_up(mhba->max_target_id, माप(अचिन्हित अक्षर) * 8) /
						(माप(अचिन्हित अक्षर) * 8);

	res_mgnt = mvumi_alloc_mem_resource(mhba,
				RESOURCE_CACHED_MEMORY, पंचांगp_size);
	अगर (!res_mgnt) अणु
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for tag and target map\n");
		जाओ fail_alloc_dma_buf;
	पूर्ण

	virmem = res_mgnt->virt_addr;
	mhba->tag_pool.stack = virmem;
	mhba->tag_pool.size = mhba->max_io;
	tag_init(&mhba->tag_pool, mhba->max_io);
	virmem += माप(अचिन्हित लघु) * mhba->max_io;

	mhba->tag_cmd = virmem;
	virmem += माप(काष्ठा mvumi_cmd *) * mhba->max_io;

	mhba->target_map = virmem;

	mhba->fw_flag |= MVUMI_FW_ALLOC;
	वापस 0;

fail_alloc_dma_buf:
	mvumi_release_mem_resource(mhba);
	वापस -1;
पूर्ण

अटल पूर्णांक mvumi_hs_process_page(काष्ठा mvumi_hba *mhba,
				काष्ठा mvumi_hs_header *hs_header)
अणु
	काष्ठा mvumi_hs_page1 *hs_page1;
	अचिन्हित अक्षर page_checksum;

	page_checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
	अगर (page_checksum != hs_header->checksum) अणु
		dev_err(&mhba->pdev->dev, "checksum error\n");
		वापस -1;
	पूर्ण

	चयन (hs_header->page_code) अणु
	हाल HS_PAGE_FIRM_CAP:
		hs_page1 = (काष्ठा mvumi_hs_page1 *) hs_header;

		mhba->max_io = hs_page1->max_io_support;
		mhba->list_num_io = hs_page1->cl_inout_list_depth;
		mhba->max_transfer_size = hs_page1->max_transfer_size;
		mhba->max_target_id = hs_page1->max_devices_support;
		mhba->hba_capability = hs_page1->capability;
		mhba->ib_max_size_setting = hs_page1->cl_in_max_entry_size;
		mhba->ib_max_size = (1 << hs_page1->cl_in_max_entry_size) << 2;

		mhba->ob_max_size_setting = hs_page1->cl_out_max_entry_size;
		mhba->ob_max_size = (1 << hs_page1->cl_out_max_entry_size) << 2;

		dev_dbg(&mhba->pdev->dev, "FW version:%d\n",
						hs_page1->fw_ver.ver_build);

		अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_COMPACT_SG)
			mhba->eot_flag = 22;
		अन्यथा
			mhba->eot_flag = 27;
		अगर (mhba->hba_capability & HS_CAPABILITY_NEW_PAGE_IO_DEPTH_DEF)
			mhba->list_num_io = 1 << hs_page1->cl_inout_list_depth;
		अवरोध;
	शेष:
		dev_err(&mhba->pdev->dev, "handshake: page code error\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mvumi_handshake -	Move the FW to READY state
 * @mhba:				Adapter soft state
 *
 * During the initialization, FW passes can potentially be in any one of
 * several possible states. If the FW in operational, रुकोing-क्रम-handshake
 * states, driver must take steps to bring it to पढ़ोy state. Otherwise, it
 * has to रुको क्रम the पढ़ोy state.
 */
अटल पूर्णांक mvumi_handshake(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक hs_state, पंचांगp, hs_fun;
	काष्ठा mvumi_hs_header *hs_header;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	अगर (mhba->fw_state == FW_STATE_STARTING)
		hs_state = HS_S_START;
	अन्यथा अणु
		पंचांगp = ioपढ़ो32(regs->arm_to_pciea_msg0);
		hs_state = HS_GET_STATE(पंचांगp);
		dev_dbg(&mhba->pdev->dev, "handshake state[0x%x].\n", hs_state);
		अगर (HS_GET_STATUS(पंचांगp) != HS_STATUS_OK) अणु
			mhba->fw_state = FW_STATE_STARTING;
			वापस -1;
		पूर्ण
	पूर्ण

	hs_fun = 0;
	चयन (hs_state) अणु
	हाल HS_S_START:
		mhba->fw_state = FW_STATE_HANDSHAKING;
		HS_SET_STATUS(hs_fun, HS_STATUS_OK);
		HS_SET_STATE(hs_fun, HS_S_RESET);
		ioग_लिखो32(HANDSHAKE_SIGNATURE, regs->pciea_to_arm_msg1);
		ioग_लिखो32(hs_fun, regs->pciea_to_arm_msg0);
		ioग_लिखो32(DRBL_HANDSHAKE, regs->pciea_to_arm_drbl_reg);
		अवरोध;

	हाल HS_S_RESET:
		ioग_लिखो32(lower_32_bits(mhba->handshake_page_phys),
					regs->pciea_to_arm_msg1);
		ioग_लिखो32(upper_32_bits(mhba->handshake_page_phys),
					regs->arm_to_pciea_msg1);
		HS_SET_STATUS(hs_fun, HS_STATUS_OK);
		HS_SET_STATE(hs_fun, HS_S_PAGE_ADDR);
		ioग_लिखो32(hs_fun, regs->pciea_to_arm_msg0);
		ioग_लिखो32(DRBL_HANDSHAKE, regs->pciea_to_arm_drbl_reg);
		अवरोध;

	हाल HS_S_PAGE_ADDR:
	हाल HS_S_QUERY_PAGE:
	हाल HS_S_SEND_PAGE:
		hs_header = (काष्ठा mvumi_hs_header *) mhba->handshake_page;
		अगर (hs_header->page_code == HS_PAGE_FIRM_CAP) अणु
			mhba->hba_total_pages =
			((काष्ठा mvumi_hs_page1 *) hs_header)->total_pages;

			अगर (mhba->hba_total_pages == 0)
				mhba->hba_total_pages = HS_PAGE_TOTAL-1;
		पूर्ण

		अगर (hs_state == HS_S_QUERY_PAGE) अणु
			अगर (mvumi_hs_process_page(mhba, hs_header)) अणु
				HS_SET_STATE(hs_fun, HS_S_ABORT);
				वापस -1;
			पूर्ण
			अगर (mvumi_init_data(mhba)) अणु
				HS_SET_STATE(hs_fun, HS_S_ABORT);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (hs_state == HS_S_PAGE_ADDR) अणु
			hs_header->page_code = 0;
			mhba->hba_total_pages = HS_PAGE_TOTAL-1;
		पूर्ण

		अगर ((hs_header->page_code + 1) <= mhba->hba_total_pages) अणु
			hs_header->page_code++;
			अगर (hs_header->page_code != HS_PAGE_FIRM_CAP) अणु
				mvumi_hs_build_page(mhba, hs_header);
				HS_SET_STATE(hs_fun, HS_S_SEND_PAGE);
			पूर्ण अन्यथा
				HS_SET_STATE(hs_fun, HS_S_QUERY_PAGE);
		पूर्ण अन्यथा
			HS_SET_STATE(hs_fun, HS_S_END);

		HS_SET_STATUS(hs_fun, HS_STATUS_OK);
		ioग_लिखो32(hs_fun, regs->pciea_to_arm_msg0);
		ioग_लिखो32(DRBL_HANDSHAKE, regs->pciea_to_arm_drbl_reg);
		अवरोध;

	हाल HS_S_END:
		/* Set communication list ISR */
		पंचांगp = ioपढ़ो32(regs->enpoपूर्णांकa_mask_reg);
		पंचांगp |= regs->पूर्णांक_comaout | regs->पूर्णांक_comaerr;
		ioग_लिखो32(पंचांगp, regs->enpoपूर्णांकa_mask_reg);
		ioग_लिखो32(mhba->list_num_io, mhba->ib_shaकरोw);
		/* Set InBound List Available count shaकरोw */
		ioग_लिखो32(lower_32_bits(mhba->ib_shaकरोw_phys),
					regs->inb_aval_count_basel);
		ioग_लिखो32(upper_32_bits(mhba->ib_shaकरोw_phys),
					regs->inb_aval_count_baseh);

		अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9143) अणु
			/* Set OutBound List Available count shaकरोw */
			ioग_लिखो32((mhba->list_num_io-1) |
							regs->cl_poपूर्णांकer_toggle,
							mhba->ob_shaकरोw);
			ioग_लिखो32(lower_32_bits(mhba->ob_shaकरोw_phys),
							regs->outb_copy_basel);
			ioग_लिखो32(upper_32_bits(mhba->ob_shaकरोw_phys),
							regs->outb_copy_baseh);
		पूर्ण

		mhba->ib_cur_slot = (mhba->list_num_io - 1) |
							regs->cl_poपूर्णांकer_toggle;
		mhba->ob_cur_slot = (mhba->list_num_io - 1) |
							regs->cl_poपूर्णांकer_toggle;
		mhba->fw_state = FW_STATE_STARTED;

		अवरोध;
	शेष:
		dev_err(&mhba->pdev->dev, "unknown handshake state [0x%x].\n",
								hs_state);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर mvumi_handshake_event(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक isr_status;
	अचिन्हित दीर्घ beक्रमe;

	beक्रमe = jअगरfies;
	mvumi_handshake(mhba);
	करो अणु
		isr_status = mhba->instancet->पढ़ो_fw_status_reg(mhba);

		अगर (mhba->fw_state == FW_STATE_STARTED)
			वापस 0;
		अगर (समय_after(jअगरfies, beक्रमe + FW_MAX_DELAY * HZ)) अणु
			dev_err(&mhba->pdev->dev,
				"no handshake response at state 0x%x.\n",
				  mhba->fw_state);
			dev_err(&mhba->pdev->dev,
				"isr : global=0x%x,status=0x%x.\n",
					mhba->global_isr, isr_status);
			वापस -1;
		पूर्ण
		rmb();
		usleep_range(1000, 2000);
	पूर्ण जबतक (!(isr_status & DRBL_HANDSHAKE_ISR));

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर mvumi_check_handshake(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ beक्रमe;

	beक्रमe = jअगरfies;
	पंचांगp = ioपढ़ो32(mhba->regs->arm_to_pciea_msg1);
	जबतक ((पंचांगp != HANDSHAKE_READYSTATE) && (पंचांगp != HANDSHAKE_DONESTATE)) अणु
		अगर (पंचांगp != HANDSHAKE_READYSTATE)
			ioग_लिखो32(DRBL_MU_RESET,
					mhba->regs->pciea_to_arm_drbl_reg);
		अगर (समय_after(jअगरfies, beक्रमe + FW_MAX_DELAY * HZ)) अणु
			dev_err(&mhba->pdev->dev,
				"invalid signature [0x%x].\n", पंचांगp);
			वापस -1;
		पूर्ण
		usleep_range(1000, 2000);
		rmb();
		पंचांगp = ioपढ़ो32(mhba->regs->arm_to_pciea_msg1);
	पूर्ण

	mhba->fw_state = FW_STATE_STARTING;
	dev_dbg(&mhba->pdev->dev, "start firmware handshake...\n");
	करो अणु
		अगर (mvumi_handshake_event(mhba)) अणु
			dev_err(&mhba->pdev->dev,
					"handshake failed at state 0x%x.\n",
						mhba->fw_state);
			वापस -1;
		पूर्ण
	पूर्ण जबतक (mhba->fw_state != FW_STATE_STARTED);

	dev_dbg(&mhba->pdev->dev, "firmware handshake done\n");

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर mvumi_start(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	/* clear Door bell */
	पंचांगp = ioपढ़ो32(regs->arm_to_pciea_drbl_reg);
	ioग_लिखो32(पंचांगp, regs->arm_to_pciea_drbl_reg);

	ioग_लिखो32(regs->पूर्णांक_drbl_पूर्णांक_mask, regs->arm_to_pciea_mask_reg);
	पंचांगp = ioपढ़ो32(regs->enpoपूर्णांकa_mask_reg) | regs->पूर्णांक_dl_cpu2pciea;
	ioग_लिखो32(पंचांगp, regs->enpoपूर्णांकa_mask_reg);
	msleep(100);
	अगर (mvumi_check_handshake(mhba))
		वापस -1;

	वापस 0;
पूर्ण

/**
 * mvumi_complete_cmd -	Completes a command
 * @mhba:			Adapter soft state
 * @cmd:			Command to be completed
 * @ob_frame:			Command response
 */
अटल व्योम mvumi_complete_cmd(काष्ठा mvumi_hba *mhba, काष्ठा mvumi_cmd *cmd,
					काष्ठा mvumi_rsp_frame *ob_frame)
अणु
	काष्ठा scsi_cmnd *scmd = cmd->scmd;

	cmd->scmd->SCp.ptr = शून्य;
	scmd->result = ob_frame->req_status;

	चयन (ob_frame->req_status) अणु
	हाल SAM_STAT_GOOD:
		scmd->result |= DID_OK << 16;
		अवरोध;
	हाल SAM_STAT_BUSY:
		scmd->result |= DID_BUS_BUSY << 16;
		अवरोध;
	हाल SAM_STAT_CHECK_CONDITION:
		scmd->result |= (DID_OK << 16);
		अगर (ob_frame->rsp_flag & CL_RSP_FLAG_SENSEDATA) अणु
			स_नकल(cmd->scmd->sense_buffer, ob_frame->payload,
				माप(काष्ठा mvumi_sense_data));
			scmd->result |=  (DRIVER_SENSE << 24);
		पूर्ण
		अवरोध;
	शेष:
		scmd->result |= (DRIVER_INVALID << 24) | (DID_ABORT << 16);
		अवरोध;
	पूर्ण

	अगर (scsi_bufflen(scmd))
		dma_unmap_sg(&mhba->pdev->dev, scsi_sglist(scmd),
			     scsi_sg_count(scmd),
			     scmd->sc_data_direction);
	cmd->scmd->scsi_करोne(scmd);
	mvumi_वापस_cmd(mhba, cmd);
पूर्ण

अटल व्योम mvumi_complete_पूर्णांकernal_cmd(काष्ठा mvumi_hba *mhba,
						काष्ठा mvumi_cmd *cmd,
					काष्ठा mvumi_rsp_frame *ob_frame)
अणु
	अगर (atomic_पढ़ो(&cmd->sync_cmd)) अणु
		cmd->cmd_status = ob_frame->req_status;

		अगर ((ob_frame->req_status == SAM_STAT_CHECK_CONDITION) &&
				(ob_frame->rsp_flag & CL_RSP_FLAG_SENSEDATA) &&
				cmd->data_buf) अणु
			स_नकल(cmd->data_buf, ob_frame->payload,
					माप(काष्ठा mvumi_sense_data));
		पूर्ण
		atomic_dec(&cmd->sync_cmd);
		wake_up(&mhba->पूर्णांक_cmd_रुको_q);
	पूर्ण
पूर्ण

अटल व्योम mvumi_show_event(काष्ठा mvumi_hba *mhba,
			काष्ठा mvumi_driver_event *ptr)
अणु
	अचिन्हित पूर्णांक i;

	dev_warn(&mhba->pdev->dev,
		"Event[0x%x] id[0x%x] severity[0x%x] device id[0x%x]\n",
		ptr->sequence_no, ptr->event_id, ptr->severity, ptr->device_id);
	अगर (ptr->param_count) अणु
		prपूर्णांकk(KERN_WARNING "Event param(len 0x%x): ",
						ptr->param_count);
		क्रम (i = 0; i < ptr->param_count; i++)
			prपूर्णांकk(KERN_WARNING "0x%x ", ptr->params[i]);

		prपूर्णांकk(KERN_WARNING "\n");
	पूर्ण

	अगर (ptr->sense_data_length) अणु
		prपूर्णांकk(KERN_WARNING "Event sense data(len 0x%x): ",
						ptr->sense_data_length);
		क्रम (i = 0; i < ptr->sense_data_length; i++)
			prपूर्णांकk(KERN_WARNING "0x%x ", ptr->sense_data[i]);
		prपूर्णांकk(KERN_WARNING "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक mvumi_handle_hotplug(काष्ठा mvumi_hba *mhba, u16 devid, पूर्णांक status)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक ret = -1;

	अगर (status == DEVICE_OFFLINE) अणु
		sdev = scsi_device_lookup(mhba->shost, 0, devid, 0);
		अगर (sdev) अणु
			dev_dbg(&mhba->pdev->dev, "remove disk %d-%d-%d.\n", 0,
								sdev->id, 0);
			scsi_हटाओ_device(sdev);
			scsi_device_put(sdev);
			ret = 0;
		पूर्ण अन्यथा
			dev_err(&mhba->pdev->dev, " no disk[%d] to remove\n",
									devid);
	पूर्ण अन्यथा अगर (status == DEVICE_ONLINE) अणु
		sdev = scsi_device_lookup(mhba->shost, 0, devid, 0);
		अगर (!sdev) अणु
			scsi_add_device(mhba->shost, 0, devid, 0);
			dev_dbg(&mhba->pdev->dev, " add disk %d-%d-%d.\n", 0,
								devid, 0);
			ret = 0;
		पूर्ण अन्यथा अणु
			dev_err(&mhba->pdev->dev, " don't add disk %d-%d-%d.\n",
								0, devid, 0);
			scsi_device_put(sdev);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल u64 mvumi_inquiry(काष्ठा mvumi_hba *mhba,
	अचिन्हित पूर्णांक id, काष्ठा mvumi_cmd *cmd)
अणु
	काष्ठा mvumi_msg_frame *frame;
	u64 wwid = 0;
	पूर्णांक cmd_alloc = 0;
	पूर्णांक data_buf_len = 64;

	अगर (!cmd) अणु
		cmd = mvumi_create_पूर्णांकernal_cmd(mhba, data_buf_len);
		अगर (cmd)
			cmd_alloc = 1;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		स_रखो(cmd->data_buf, 0, data_buf_len);
	पूर्ण
	cmd->scmd = शून्य;
	cmd->cmd_status = REQ_STATUS_PENDING;
	atomic_set(&cmd->sync_cmd, 0);
	frame = cmd->frame;
	frame->device_id = (u16) id;
	frame->cmd_flag = CMD_FLAG_DATA_IN;
	frame->req_function = CL_FUN_SCSI_CMD;
	frame->cdb_length = 6;
	frame->data_transfer_length = MVUMI_INQUIRY_LENGTH;
	स_रखो(frame->cdb, 0, frame->cdb_length);
	frame->cdb[0] = INQUIRY;
	frame->cdb[4] = frame->data_transfer_length;

	mvumi_issue_blocked_cmd(mhba, cmd);

	अगर (cmd->cmd_status == SAM_STAT_GOOD) अणु
		अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9143)
			wwid = id + 1;
		अन्यथा
			स_नकल((व्योम *)&wwid,
			       (cmd->data_buf + MVUMI_INQUIRY_UUID_OFF),
			       MVUMI_INQUIRY_UUID_LEN);
		dev_dbg(&mhba->pdev->dev,
			"inquiry device(0:%d:0) wwid(%llx)\n", id, wwid);
	पूर्ण अन्यथा अणु
		wwid = 0;
	पूर्ण
	अगर (cmd_alloc)
		mvumi_delete_पूर्णांकernal_cmd(mhba, cmd);

	वापस wwid;
पूर्ण

अटल व्योम mvumi_detach_devices(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_device *mv_dev = शून्य , *dev_next;
	काष्ठा scsi_device *sdev = शून्य;

	mutex_lock(&mhba->device_lock);

	/* detach Hard Disk */
	list_क्रम_each_entry_safe(mv_dev, dev_next,
		&mhba->shost_dev_list, list) अणु
		mvumi_handle_hotplug(mhba, mv_dev->id, DEVICE_OFFLINE);
		list_del_init(&mv_dev->list);
		dev_dbg(&mhba->pdev->dev, "release device(0:%d:0) wwid(%llx)\n",
			mv_dev->id, mv_dev->wwid);
		kमुक्त(mv_dev);
	पूर्ण
	list_क्रम_each_entry_safe(mv_dev, dev_next, &mhba->mhba_dev_list, list) अणु
		list_del_init(&mv_dev->list);
		dev_dbg(&mhba->pdev->dev, "release device(0:%d:0) wwid(%llx)\n",
			mv_dev->id, mv_dev->wwid);
		kमुक्त(mv_dev);
	पूर्ण

	/* detach भव device */
	अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580)
		sdev = scsi_device_lookup(mhba->shost, 0,
						mhba->max_target_id - 1, 0);

	अगर (sdev) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
	पूर्ण

	mutex_unlock(&mhba->device_lock);
पूर्ण

अटल व्योम mvumi_rescan_devices(काष्ठा mvumi_hba *mhba, पूर्णांक id)
अणु
	काष्ठा scsi_device *sdev;

	sdev = scsi_device_lookup(mhba->shost, 0, id, 0);
	अगर (sdev) अणु
		scsi_rescan_device(&sdev->sdev_gendev);
		scsi_device_put(sdev);
	पूर्ण
पूर्ण

अटल पूर्णांक mvumi_match_devices(काष्ठा mvumi_hba *mhba, पूर्णांक id, u64 wwid)
अणु
	काष्ठा mvumi_device *mv_dev = शून्य;

	list_क्रम_each_entry(mv_dev, &mhba->shost_dev_list, list) अणु
		अगर (mv_dev->wwid == wwid) अणु
			अगर (mv_dev->id != id) अणु
				dev_err(&mhba->pdev->dev,
					"%s has same wwid[%llx] ,"
					" but different id[%d %d]\n",
					__func__, mv_dev->wwid, mv_dev->id, id);
				वापस -1;
			पूर्ण अन्यथा अणु
				अगर (mhba->pdev->device ==
						PCI_DEVICE_ID_MARVELL_MV9143)
					mvumi_rescan_devices(mhba, id);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mvumi_हटाओ_devices(काष्ठा mvumi_hba *mhba, पूर्णांक id)
अणु
	काष्ठा mvumi_device *mv_dev = शून्य, *dev_next;

	list_क्रम_each_entry_safe(mv_dev, dev_next,
				&mhba->shost_dev_list, list) अणु
		अगर (mv_dev->id == id) अणु
			dev_dbg(&mhba->pdev->dev,
				"detach device(0:%d:0) wwid(%llx) from HOST\n",
				mv_dev->id, mv_dev->wwid);
			mvumi_handle_hotplug(mhba, mv_dev->id, DEVICE_OFFLINE);
			list_del_init(&mv_dev->list);
			kमुक्त(mv_dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mvumi_probe_devices(काष्ठा mvumi_hba *mhba)
अणु
	पूर्णांक id, maxid;
	u64 wwid = 0;
	काष्ठा mvumi_device *mv_dev = शून्य;
	काष्ठा mvumi_cmd *cmd = शून्य;
	पूर्णांक found = 0;

	cmd = mvumi_create_पूर्णांकernal_cmd(mhba, 64);
	अगर (!cmd)
		वापस -1;

	अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9143)
		maxid = mhba->max_target_id;
	अन्यथा
		maxid = mhba->max_target_id - 1;

	क्रम (id = 0; id < maxid; id++) अणु
		wwid = mvumi_inquiry(mhba, id, cmd);
		अगर (!wwid) अणु
			/* device no response, हटाओ it */
			mvumi_हटाओ_devices(mhba, id);
		पूर्ण अन्यथा अणु
			/* device response, add it */
			found = mvumi_match_devices(mhba, id, wwid);
			अगर (!found) अणु
				mvumi_हटाओ_devices(mhba, id);
				mv_dev = kzalloc(माप(काष्ठा mvumi_device),
								GFP_KERNEL);
				अगर (!mv_dev) अणु
					dev_err(&mhba->pdev->dev,
						"%s alloc mv_dev failed\n",
						__func__);
					जारी;
				पूर्ण
				mv_dev->id = id;
				mv_dev->wwid = wwid;
				mv_dev->sdev = शून्य;
				INIT_LIST_HEAD(&mv_dev->list);
				list_add_tail(&mv_dev->list,
					      &mhba->mhba_dev_list);
				dev_dbg(&mhba->pdev->dev,
					"probe a new device(0:%d:0)"
					" wwid(%llx)\n", id, mv_dev->wwid);
			पूर्ण अन्यथा अगर (found == -1)
				वापस -1;
			अन्यथा
				जारी;
		पूर्ण
	पूर्ण

	अगर (cmd)
		mvumi_delete_पूर्णांकernal_cmd(mhba, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक mvumi_rescan_bus(व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा mvumi_hba *mhba = (काष्ठा mvumi_hba *) data;
	काष्ठा mvumi_device *mv_dev = शून्य , *dev_next;

	जबतक (!kthपढ़ो_should_stop()) अणु

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!atomic_पढ़ो(&mhba->pnp_count))
			schedule();
		msleep(1000);
		atomic_set(&mhba->pnp_count, 0);
		__set_current_state(TASK_RUNNING);

		mutex_lock(&mhba->device_lock);
		ret = mvumi_probe_devices(mhba);
		अगर (!ret) अणु
			list_क्रम_each_entry_safe(mv_dev, dev_next,
						 &mhba->mhba_dev_list, list) अणु
				अगर (mvumi_handle_hotplug(mhba, mv_dev->id,
							 DEVICE_ONLINE)) अणु
					dev_err(&mhba->pdev->dev,
						"%s add device(0:%d:0) failed"
						"wwid(%llx) has exist\n",
						__func__,
						mv_dev->id, mv_dev->wwid);
					list_del_init(&mv_dev->list);
					kमुक्त(mv_dev);
				पूर्ण अन्यथा अणु
					list_move_tail(&mv_dev->list,
						       &mhba->shost_dev_list);
				पूर्ण
			पूर्ण
		पूर्ण
		mutex_unlock(&mhba->device_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mvumi_proc_msg(काष्ठा mvumi_hba *mhba,
					काष्ठा mvumi_hotplug_event *param)
अणु
	u16 size = param->size;
	स्थिर अचिन्हित दीर्घ *ar_biपंचांगap;
	स्थिर अचिन्हित दीर्घ *re_biपंचांगap;
	पूर्णांक index;

	अगर (mhba->fw_flag & MVUMI_FW_ATTACH) अणु
		index = -1;
		ar_biपंचांगap = (स्थिर अचिन्हित दीर्घ *) param->biपंचांगap;
		re_biपंचांगap = (स्थिर अचिन्हित दीर्घ *) &param->biपंचांगap[size >> 3];

		mutex_lock(&mhba->sas_discovery_mutex);
		करो अणु
			index = find_next_zero_bit(ar_biपंचांगap, size, index + 1);
			अगर (index >= size)
				अवरोध;
			mvumi_handle_hotplug(mhba, index, DEVICE_ONLINE);
		पूर्ण जबतक (1);

		index = -1;
		करो अणु
			index = find_next_zero_bit(re_biपंचांगap, size, index + 1);
			अगर (index >= size)
				अवरोध;
			mvumi_handle_hotplug(mhba, index, DEVICE_OFFLINE);
		पूर्ण जबतक (1);
		mutex_unlock(&mhba->sas_discovery_mutex);
	पूर्ण
पूर्ण

अटल व्योम mvumi_notअगरication(काष्ठा mvumi_hba *mhba, u8 msg, व्योम *buffer)
अणु
	अगर (msg == APICDB1_EVENT_GETEVENT) अणु
		पूर्णांक i, count;
		काष्ठा mvumi_driver_event *param = शून्य;
		काष्ठा mvumi_event_req *er = buffer;
		count = er->count;
		अगर (count > MAX_EVENTS_RETURNED) अणु
			dev_err(&mhba->pdev->dev, "event count[0x%x] is bigger"
					" than max event count[0x%x].\n",
					count, MAX_EVENTS_RETURNED);
			वापस;
		पूर्ण
		क्रम (i = 0; i < count; i++) अणु
			param = &er->events[i];
			mvumi_show_event(mhba, param);
		पूर्ण
	पूर्ण अन्यथा अगर (msg == APICDB1_HOST_GETEVENT) अणु
		mvumi_proc_msg(mhba, buffer);
	पूर्ण
पूर्ण

अटल पूर्णांक mvumi_get_event(काष्ठा mvumi_hba *mhba, अचिन्हित अक्षर msg)
अणु
	काष्ठा mvumi_cmd *cmd;
	काष्ठा mvumi_msg_frame *frame;

	cmd = mvumi_create_पूर्णांकernal_cmd(mhba, 512);
	अगर (!cmd)
		वापस -1;
	cmd->scmd = शून्य;
	cmd->cmd_status = REQ_STATUS_PENDING;
	atomic_set(&cmd->sync_cmd, 0);
	frame = cmd->frame;
	frame->device_id = 0;
	frame->cmd_flag = CMD_FLAG_DATA_IN;
	frame->req_function = CL_FUN_SCSI_CMD;
	frame->cdb_length = MAX_COMMAND_SIZE;
	frame->data_transfer_length = माप(काष्ठा mvumi_event_req);
	स_रखो(frame->cdb, 0, MAX_COMMAND_SIZE);
	frame->cdb[0] = APICDB0_EVENT;
	frame->cdb[1] = msg;
	mvumi_issue_blocked_cmd(mhba, cmd);

	अगर (cmd->cmd_status != SAM_STAT_GOOD)
		dev_err(&mhba->pdev->dev, "get event failed, status=0x%x.\n",
							cmd->cmd_status);
	अन्यथा
		mvumi_notअगरication(mhba, cmd->frame->cdb[1], cmd->data_buf);

	mvumi_delete_पूर्णांकernal_cmd(mhba, cmd);
	वापस 0;
पूर्ण

अटल व्योम mvumi_scan_events(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mvumi_events_wq *mu_ev =
		container_of(work, काष्ठा mvumi_events_wq, work_q);

	mvumi_get_event(mu_ev->mhba, mu_ev->event);
	kमुक्त(mu_ev);
पूर्ण

अटल व्योम mvumi_launch_events(काष्ठा mvumi_hba *mhba, u32 isr_status)
अणु
	काष्ठा mvumi_events_wq *mu_ev;

	जबतक (isr_status & (DRBL_BUS_CHANGE | DRBL_EVENT_NOTIFY)) अणु
		अगर (isr_status & DRBL_BUS_CHANGE) अणु
			atomic_inc(&mhba->pnp_count);
			wake_up_process(mhba->dm_thपढ़ो);
			isr_status &= ~(DRBL_BUS_CHANGE);
			जारी;
		पूर्ण

		mu_ev = kzalloc(माप(*mu_ev), GFP_ATOMIC);
		अगर (mu_ev) अणु
			INIT_WORK(&mu_ev->work_q, mvumi_scan_events);
			mu_ev->mhba = mhba;
			mu_ev->event = APICDB1_EVENT_GETEVENT;
			isr_status &= ~(DRBL_EVENT_NOTIFY);
			mu_ev->param = शून्य;
			schedule_work(&mu_ev->work_q);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvumi_handle_clob(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा mvumi_rsp_frame *ob_frame;
	काष्ठा mvumi_cmd *cmd;
	काष्ठा mvumi_ob_data *pool;

	जबतक (!list_empty(&mhba->मुक्त_ob_list)) अणु
		pool = list_first_entry(&mhba->मुक्त_ob_list,
						काष्ठा mvumi_ob_data, list);
		list_del_init(&pool->list);
		list_add_tail(&pool->list, &mhba->ob_data_list);

		ob_frame = (काष्ठा mvumi_rsp_frame *) &pool->data[0];
		cmd = mhba->tag_cmd[ob_frame->tag];

		atomic_dec(&mhba->fw_outstanding);
		mhba->tag_cmd[ob_frame->tag] = शून्य;
		tag_release_one(mhba, &mhba->tag_pool, ob_frame->tag);
		अगर (cmd->scmd)
			mvumi_complete_cmd(mhba, cmd, ob_frame);
		अन्यथा
			mvumi_complete_पूर्णांकernal_cmd(mhba, cmd, ob_frame);
	पूर्ण
	mhba->instancet->fire_cmd(mhba, शून्य);
पूर्ण

अटल irqवापस_t mvumi_isr_handler(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा mvumi_hba *mhba = (काष्ठा mvumi_hba *) devp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(mhba->shost->host_lock, flags);
	अगर (unlikely(mhba->instancet->clear_पूर्णांकr(mhba) || !mhba->global_isr)) अणु
		spin_unlock_irqrestore(mhba->shost->host_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (mhba->global_isr & mhba->regs->पूर्णांक_dl_cpu2pciea) अणु
		अगर (mhba->isr_status & (DRBL_BUS_CHANGE | DRBL_EVENT_NOTIFY))
			mvumi_launch_events(mhba, mhba->isr_status);
		अगर (mhba->isr_status & DRBL_HANDSHAKE_ISR) अणु
			dev_warn(&mhba->pdev->dev, "enter handshake again!\n");
			mvumi_handshake(mhba);
		पूर्ण

	पूर्ण

	अगर (mhba->global_isr & mhba->regs->पूर्णांक_comaout)
		mvumi_receive_ob_list_entry(mhba);

	mhba->global_isr = 0;
	mhba->isr_status = 0;
	अगर (mhba->fw_state == FW_STATE_STARTED)
		mvumi_handle_clob(mhba);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत mvumi_qc_result mvumi_send_command(काष्ठा mvumi_hba *mhba,
						काष्ठा mvumi_cmd *cmd)
अणु
	व्योम *ib_entry;
	काष्ठा mvumi_msg_frame *ib_frame;
	अचिन्हित पूर्णांक frame_len;

	ib_frame = cmd->frame;
	अगर (unlikely(mhba->fw_state != FW_STATE_STARTED)) अणु
		dev_dbg(&mhba->pdev->dev, "firmware not ready.\n");
		वापस MV_QUEUE_COMMAND_RESULT_NO_RESOURCE;
	पूर्ण
	अगर (tag_is_empty(&mhba->tag_pool)) अणु
		dev_dbg(&mhba->pdev->dev, "no free tag.\n");
		वापस MV_QUEUE_COMMAND_RESULT_NO_RESOURCE;
	पूर्ण
	mvumi_get_ib_list_entry(mhba, &ib_entry);

	cmd->frame->tag = tag_get_one(mhba, &mhba->tag_pool);
	cmd->frame->request_id = mhba->io_seq++;
	cmd->request_id = cmd->frame->request_id;
	mhba->tag_cmd[cmd->frame->tag] = cmd;
	frame_len = माप(*ib_frame) - 4 +
				ib_frame->sg_counts * माप(काष्ठा mvumi_sgl);
	अगर (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) अणु
		काष्ठा mvumi_dyn_list_entry *dle;
		dle = ib_entry;
		dle->src_low_addr =
			cpu_to_le32(lower_32_bits(cmd->frame_phys));
		dle->src_high_addr =
			cpu_to_le32(upper_32_bits(cmd->frame_phys));
		dle->अगर_length = (frame_len >> 2) & 0xFFF;
	पूर्ण अन्यथा अणु
		स_नकल(ib_entry, ib_frame, frame_len);
	पूर्ण
	वापस MV_QUEUE_COMMAND_RESULT_SENT;
पूर्ण

अटल व्योम mvumi_fire_cmd(काष्ठा mvumi_hba *mhba, काष्ठा mvumi_cmd *cmd)
अणु
	अचिन्हित लघु num_of_cl_sent = 0;
	अचिन्हित पूर्णांक count;
	क्रमागत mvumi_qc_result result;

	अगर (cmd)
		list_add_tail(&cmd->queue_poपूर्णांकer, &mhba->रुकोing_req_list);
	count = mhba->instancet->check_ib_list(mhba);
	अगर (list_empty(&mhba->रुकोing_req_list) || !count)
		वापस;

	करो अणु
		cmd = list_first_entry(&mhba->रुकोing_req_list,
				       काष्ठा mvumi_cmd, queue_poपूर्णांकer);
		list_del_init(&cmd->queue_poपूर्णांकer);
		result = mvumi_send_command(mhba, cmd);
		चयन (result) अणु
		हाल MV_QUEUE_COMMAND_RESULT_SENT:
			num_of_cl_sent++;
			अवरोध;
		हाल MV_QUEUE_COMMAND_RESULT_NO_RESOURCE:
			list_add(&cmd->queue_poपूर्णांकer, &mhba->रुकोing_req_list);
			अगर (num_of_cl_sent > 0)
				mvumi_send_ib_list_entry(mhba);

			वापस;
		पूर्ण
	पूर्ण जबतक (!list_empty(&mhba->रुकोing_req_list) && count--);

	अगर (num_of_cl_sent > 0)
		mvumi_send_ib_list_entry(mhba);
पूर्ण

/**
 * mvumi_enable_पूर्णांकr -	Enables पूर्णांकerrupts
 * @mhba:		Adapter soft state
 */
अटल व्योम mvumi_enable_पूर्णांकr(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	ioग_लिखो32(regs->पूर्णांक_drbl_पूर्णांक_mask, regs->arm_to_pciea_mask_reg);
	mask = ioपढ़ो32(regs->enpoपूर्णांकa_mask_reg);
	mask |= regs->पूर्णांक_dl_cpu2pciea | regs->पूर्णांक_comaout | regs->पूर्णांक_comaerr;
	ioग_लिखो32(mask, regs->enpoपूर्णांकa_mask_reg);
पूर्ण

/**
 * mvumi_disable_पूर्णांकr -Disables पूर्णांकerrupt
 * @mhba:		Adapter soft state
 */
अटल व्योम mvumi_disable_पूर्णांकr(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	ioग_लिखो32(0, regs->arm_to_pciea_mask_reg);
	mask = ioपढ़ो32(regs->enpoपूर्णांकa_mask_reg);
	mask &= ~(regs->पूर्णांक_dl_cpu2pciea | regs->पूर्णांक_comaout |
							regs->पूर्णांक_comaerr);
	ioग_लिखो32(mask, regs->enpoपूर्णांकa_mask_reg);
पूर्ण

अटल पूर्णांक mvumi_clear_पूर्णांकr(व्योम *extend)
अणु
	काष्ठा mvumi_hba *mhba = (काष्ठा mvumi_hba *) extend;
	अचिन्हित पूर्णांक status, isr_status = 0, पंचांगp = 0;
	काष्ठा mvumi_hw_regs *regs = mhba->regs;

	status = ioपढ़ो32(regs->मुख्य_पूर्णांक_cause_reg);
	अगर (!(status & regs->पूर्णांक_mu) || status == 0xFFFFFFFF)
		वापस 1;
	अगर (unlikely(status & regs->पूर्णांक_comaerr)) अणु
		पंचांगp = ioपढ़ो32(regs->outb_isr_cause);
		अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580) अणु
			अगर (पंचांगp & regs->clic_out_err) अणु
				ioग_लिखो32(पंचांगp & regs->clic_out_err,
							regs->outb_isr_cause);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (पंचांगp & (regs->clic_in_err | regs->clic_out_err))
				ioग_लिखो32(पंचांगp & (regs->clic_in_err |
						regs->clic_out_err),
						regs->outb_isr_cause);
		पूर्ण
		status ^= mhba->regs->पूर्णांक_comaerr;
		/* inbound or outbound parity error, command will समयout */
	पूर्ण
	अगर (status & regs->पूर्णांक_comaout) अणु
		पंचांगp = ioपढ़ो32(regs->outb_isr_cause);
		अगर (पंचांगp & regs->clic_irq)
			ioग_लिखो32(पंचांगp & regs->clic_irq, regs->outb_isr_cause);
	पूर्ण
	अगर (status & regs->पूर्णांक_dl_cpu2pciea) अणु
		isr_status = ioपढ़ो32(regs->arm_to_pciea_drbl_reg);
		अगर (isr_status)
			ioग_लिखो32(isr_status, regs->arm_to_pciea_drbl_reg);
	पूर्ण

	mhba->global_isr = status;
	mhba->isr_status = isr_status;

	वापस 0;
पूर्ण

/**
 * mvumi_पढ़ो_fw_status_reg - वापसs the current FW status value
 * @mhba:		Adapter soft state
 */
अटल अचिन्हित पूर्णांक mvumi_पढ़ो_fw_status_reg(काष्ठा mvumi_hba *mhba)
अणु
	अचिन्हित पूर्णांक status;

	status = ioपढ़ो32(mhba->regs->arm_to_pciea_drbl_reg);
	अगर (status)
		ioग_लिखो32(status, mhba->regs->arm_to_pciea_drbl_reg);
	वापस status;
पूर्ण

अटल काष्ठा mvumi_instance_ढाँचा mvumi_instance_9143 = अणु
	.fire_cmd = mvumi_fire_cmd,
	.enable_पूर्णांकr = mvumi_enable_पूर्णांकr,
	.disable_पूर्णांकr = mvumi_disable_पूर्णांकr,
	.clear_पूर्णांकr = mvumi_clear_पूर्णांकr,
	.पढ़ो_fw_status_reg = mvumi_पढ़ो_fw_status_reg,
	.check_ib_list = mvumi_check_ib_list_9143,
	.check_ob_list = mvumi_check_ob_list_9143,
	.reset_host = mvumi_reset_host_9143,
पूर्ण;

अटल काष्ठा mvumi_instance_ढाँचा mvumi_instance_9580 = अणु
	.fire_cmd = mvumi_fire_cmd,
	.enable_पूर्णांकr = mvumi_enable_पूर्णांकr,
	.disable_पूर्णांकr = mvumi_disable_पूर्णांकr,
	.clear_पूर्णांकr = mvumi_clear_पूर्णांकr,
	.पढ़ो_fw_status_reg = mvumi_पढ़ो_fw_status_reg,
	.check_ib_list = mvumi_check_ib_list_9580,
	.check_ob_list = mvumi_check_ob_list_9580,
	.reset_host = mvumi_reset_host_9580,
पूर्ण;

अटल पूर्णांक mvumi_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा mvumi_hba *mhba;
	अचिन्हित अक्षर bitcount = माप(अचिन्हित अक्षर) * 8;

	mhba = (काष्ठा mvumi_hba *) sdev->host->hostdata;
	अगर (sdev->id >= mhba->max_target_id)
		वापस -EINVAL;

	mhba->target_map[sdev->id / bitcount] |= (1 << (sdev->id % bitcount));
	वापस 0;
पूर्ण

/**
 * mvumi_build_frame -	Prepares a direct cdb (DCDB) command
 * @mhba:		Adapter soft state
 * @scmd:		SCSI command
 * @cmd:		Command to be prepared in
 *
 * This function prepares CDB commands. These are typcially pass-through
 * commands to the devices.
 */
अटल अचिन्हित अक्षर mvumi_build_frame(काष्ठा mvumi_hba *mhba,
				काष्ठा scsi_cmnd *scmd, काष्ठा mvumi_cmd *cmd)
अणु
	काष्ठा mvumi_msg_frame *pframe;

	cmd->scmd = scmd;
	cmd->cmd_status = REQ_STATUS_PENDING;
	pframe = cmd->frame;
	pframe->device_id = ((अचिन्हित लघु) scmd->device->id) |
				(((अचिन्हित लघु) scmd->device->lun) << 8);
	pframe->cmd_flag = 0;

	चयन (scmd->sc_data_direction) अणु
	हाल DMA_NONE:
		pframe->cmd_flag |= CMD_FLAG_NON_DATA;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		pframe->cmd_flag |= CMD_FLAG_DATA_IN;
		अवरोध;
	हाल DMA_TO_DEVICE:
		pframe->cmd_flag |= CMD_FLAG_DATA_OUT;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
	शेष:
		dev_warn(&mhba->pdev->dev, "unexpected data direction[%d] "
			"cmd[0x%x]\n", scmd->sc_data_direction, scmd->cmnd[0]);
		जाओ error;
	पूर्ण

	pframe->cdb_length = scmd->cmd_len;
	स_नकल(pframe->cdb, scmd->cmnd, pframe->cdb_length);
	pframe->req_function = CL_FUN_SCSI_CMD;
	अगर (scsi_bufflen(scmd)) अणु
		अगर (mvumi_make_sgl(mhba, scmd, &pframe->payload[0],
			&pframe->sg_counts))
			जाओ error;

		pframe->data_transfer_length = scsi_bufflen(scmd);
	पूर्ण अन्यथा अणु
		pframe->sg_counts = 0;
		pframe->data_transfer_length = 0;
	पूर्ण
	वापस 0;

error:
	scmd->result = (DID_OK << 16) | (DRIVER_SENSE << 24) |
		SAM_STAT_CHECK_CONDITION;
	scsi_build_sense_buffer(0, scmd->sense_buffer, ILLEGAL_REQUEST, 0x24,
									0);
	वापस -1;
पूर्ण

/**
 * mvumi_queue_command -	Queue entry poपूर्णांक
 * @shost:			Scsi host to queue command on
 * @scmd:			SCSI command to be queued
 */
अटल पूर्णांक mvumi_queue_command(काष्ठा Scsi_Host *shost,
					काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा mvumi_cmd *cmd;
	काष्ठा mvumi_hba *mhba;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(shost->host_lock, irq_flags);

	mhba = (काष्ठा mvumi_hba *) shost->hostdata;
	scmd->result = 0;
	cmd = mvumi_get_cmd(mhba);
	अगर (unlikely(!cmd)) अणु
		spin_unlock_irqrestore(shost->host_lock, irq_flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	अगर (unlikely(mvumi_build_frame(mhba, scmd, cmd)))
		जाओ out_वापस_cmd;

	cmd->scmd = scmd;
	scmd->SCp.ptr = (अक्षर *) cmd;
	mhba->instancet->fire_cmd(mhba, cmd);
	spin_unlock_irqrestore(shost->host_lock, irq_flags);
	वापस 0;

out_वापस_cmd:
	mvumi_वापस_cmd(mhba, cmd);
	scmd->scsi_करोne(scmd);
	spin_unlock_irqrestore(shost->host_lock, irq_flags);
	वापस 0;
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस mvumi_समयd_out(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा mvumi_cmd *cmd = (काष्ठा mvumi_cmd *) scmd->SCp.ptr;
	काष्ठा Scsi_Host *host = scmd->device->host;
	काष्ठा mvumi_hba *mhba = shost_priv(host);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(mhba->shost->host_lock, flags);

	अगर (mhba->tag_cmd[cmd->frame->tag]) अणु
		mhba->tag_cmd[cmd->frame->tag] = शून्य;
		tag_release_one(mhba, &mhba->tag_pool, cmd->frame->tag);
	पूर्ण
	अगर (!list_empty(&cmd->queue_poपूर्णांकer))
		list_del_init(&cmd->queue_poपूर्णांकer);
	अन्यथा
		atomic_dec(&mhba->fw_outstanding);

	scmd->result = (DRIVER_INVALID << 24) | (DID_ABORT << 16);
	scmd->SCp.ptr = शून्य;
	अगर (scsi_bufflen(scmd)) अणु
		dma_unmap_sg(&mhba->pdev->dev, scsi_sglist(scmd),
			     scsi_sg_count(scmd),
			     scmd->sc_data_direction);
	पूर्ण
	mvumi_वापस_cmd(mhba, cmd);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);

	वापस BLK_EH_DONE;
पूर्ण

अटल पूर्णांक
mvumi_bios_param(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
			sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads, sectors;
	sector_t cylinders;
	अचिन्हित दीर्घ पंचांगp;

	heads = 64;
	sectors = 32;
	पंचांगp = heads * sectors;
	cylinders = capacity;
	sector_भाग(cylinders, पंचांगp);

	अगर (capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		पंचांगp = heads * sectors;
		cylinders = capacity;
		sector_भाग(cylinders, पंचांगp);
	पूर्ण
	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mvumi_ढाँचा = अणु

	.module = THIS_MODULE,
	.name = "Marvell Storage Controller",
	.slave_configure = mvumi_slave_configure,
	.queuecommand = mvumi_queue_command,
	.eh_समयd_out = mvumi_समयd_out,
	.eh_host_reset_handler = mvumi_host_reset,
	.bios_param = mvumi_bios_param,
	.dma_boundary = PAGE_SIZE - 1,
	.this_id = -1,
पूर्ण;

अटल पूर्णांक mvumi_cfg_hw_reg(काष्ठा mvumi_hba *mhba)
अणु
	व्योम *base = शून्य;
	काष्ठा mvumi_hw_regs *regs;

	चयन (mhba->pdev->device) अणु
	हाल PCI_DEVICE_ID_MARVELL_MV9143:
		mhba->mmio = mhba->base_addr[0];
		base = mhba->mmio;
		अगर (!mhba->regs) अणु
			mhba->regs = kzalloc(माप(*regs), GFP_KERNEL);
			अगर (mhba->regs == शून्य)
				वापस -ENOMEM;
		पूर्ण
		regs = mhba->regs;

		/* For Arm */
		regs->ctrl_sts_reg          = base + 0x20104;
		regs->rstoutn_mask_reg      = base + 0x20108;
		regs->sys_soft_rst_reg      = base + 0x2010C;
		regs->मुख्य_पूर्णांक_cause_reg    = base + 0x20200;
		regs->enpoपूर्णांकa_mask_reg     = base + 0x2020C;
		regs->rstoutn_en_reg        = base + 0xF1400;
		/* For Doorbell */
		regs->pciea_to_arm_drbl_reg = base + 0x20400;
		regs->arm_to_pciea_drbl_reg = base + 0x20408;
		regs->arm_to_pciea_mask_reg = base + 0x2040C;
		regs->pciea_to_arm_msg0     = base + 0x20430;
		regs->pciea_to_arm_msg1     = base + 0x20434;
		regs->arm_to_pciea_msg0     = base + 0x20438;
		regs->arm_to_pciea_msg1     = base + 0x2043C;

		/* For Message Unit */

		regs->inb_aval_count_basel  = base + 0x508;
		regs->inb_aval_count_baseh  = base + 0x50C;
		regs->inb_ग_लिखो_poपूर्णांकer     = base + 0x518;
		regs->inb_पढ़ो_poपूर्णांकer      = base + 0x51C;
		regs->outb_coal_cfg         = base + 0x568;
		regs->outb_copy_basel       = base + 0x5B0;
		regs->outb_copy_baseh       = base + 0x5B4;
		regs->outb_copy_poपूर्णांकer     = base + 0x544;
		regs->outb_पढ़ो_poपूर्णांकer     = base + 0x548;
		regs->outb_isr_cause        = base + 0x560;
		regs->outb_coal_cfg         = base + 0x568;
		/* Bit setting क्रम HW */
		regs->पूर्णांक_comaout           = 1 << 8;
		regs->पूर्णांक_comaerr           = 1 << 6;
		regs->पूर्णांक_dl_cpu2pciea      = 1 << 1;
		regs->cl_poपूर्णांकer_toggle     = 1 << 12;
		regs->clic_irq              = 1 << 1;
		regs->clic_in_err           = 1 << 8;
		regs->clic_out_err          = 1 << 12;
		regs->cl_slot_num_mask      = 0xFFF;
		regs->पूर्णांक_drbl_पूर्णांक_mask     = 0x3FFFFFFF;
		regs->पूर्णांक_mu = regs->पूर्णांक_dl_cpu2pciea | regs->पूर्णांक_comaout |
							regs->पूर्णांक_comaerr;
		अवरोध;
	हाल PCI_DEVICE_ID_MARVELL_MV9580:
		mhba->mmio = mhba->base_addr[2];
		base = mhba->mmio;
		अगर (!mhba->regs) अणु
			mhba->regs = kzalloc(माप(*regs), GFP_KERNEL);
			अगर (mhba->regs == शून्य)
				वापस -ENOMEM;
		पूर्ण
		regs = mhba->regs;
		/* For Arm */
		regs->ctrl_sts_reg          = base + 0x20104;
		regs->rstoutn_mask_reg      = base + 0x1010C;
		regs->sys_soft_rst_reg      = base + 0x10108;
		regs->मुख्य_पूर्णांक_cause_reg    = base + 0x10200;
		regs->enpoपूर्णांकa_mask_reg     = base + 0x1020C;
		regs->rstoutn_en_reg        = base + 0xF1400;

		/* For Doorbell */
		regs->pciea_to_arm_drbl_reg = base + 0x10460;
		regs->arm_to_pciea_drbl_reg = base + 0x10480;
		regs->arm_to_pciea_mask_reg = base + 0x10484;
		regs->pciea_to_arm_msg0     = base + 0x10400;
		regs->pciea_to_arm_msg1     = base + 0x10404;
		regs->arm_to_pciea_msg0     = base + 0x10420;
		regs->arm_to_pciea_msg1     = base + 0x10424;

		/* For reset*/
		regs->reset_request         = base + 0x10108;
		regs->reset_enable          = base + 0x1010c;

		/* For Message Unit */
		regs->inb_aval_count_basel  = base + 0x4008;
		regs->inb_aval_count_baseh  = base + 0x400C;
		regs->inb_ग_लिखो_poपूर्णांकer     = base + 0x4018;
		regs->inb_पढ़ो_poपूर्णांकer      = base + 0x401C;
		regs->outb_copy_basel       = base + 0x4058;
		regs->outb_copy_baseh       = base + 0x405C;
		regs->outb_copy_poपूर्णांकer     = base + 0x406C;
		regs->outb_पढ़ो_poपूर्णांकer     = base + 0x4070;
		regs->outb_coal_cfg         = base + 0x4080;
		regs->outb_isr_cause        = base + 0x4088;
		/* Bit setting क्रम HW */
		regs->पूर्णांक_comaout           = 1 << 4;
		regs->पूर्णांक_dl_cpu2pciea      = 1 << 12;
		regs->पूर्णांक_comaerr           = 1 << 29;
		regs->cl_poपूर्णांकer_toggle     = 1 << 14;
		regs->cl_slot_num_mask      = 0x3FFF;
		regs->clic_irq              = 1 << 0;
		regs->clic_out_err          = 1 << 1;
		regs->पूर्णांक_drbl_पूर्णांक_mask     = 0x3FFFFFFF;
		regs->पूर्णांक_mu = regs->पूर्णांक_dl_cpu2pciea | regs->पूर्णांक_comaout;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mvumi_init_fw -	Initializes the FW
 * @mhba:		Adapter soft state
 *
 * This is the मुख्य function क्रम initializing firmware.
 */
अटल पूर्णांक mvumi_init_fw(काष्ठा mvumi_hba *mhba)
अणु
	पूर्णांक ret = 0;

	अगर (pci_request_regions(mhba->pdev, MV_DRIVER_NAME)) अणु
		dev_err(&mhba->pdev->dev, "IO memory region busy!\n");
		वापस -EBUSY;
	पूर्ण
	ret = mvumi_map_pci_addr(mhba->pdev, mhba->base_addr);
	अगर (ret)
		जाओ fail_ioremap;

	चयन (mhba->pdev->device) अणु
	हाल PCI_DEVICE_ID_MARVELL_MV9143:
		mhba->instancet = &mvumi_instance_9143;
		mhba->io_seq = 0;
		mhba->max_sge = MVUMI_MAX_SG_ENTRY;
		mhba->request_id_enabled = 1;
		अवरोध;
	हाल PCI_DEVICE_ID_MARVELL_MV9580:
		mhba->instancet = &mvumi_instance_9580;
		mhba->io_seq = 0;
		mhba->max_sge = MVUMI_MAX_SG_ENTRY;
		अवरोध;
	शेष:
		dev_err(&mhba->pdev->dev, "device 0x%x not supported!\n",
							mhba->pdev->device);
		mhba->instancet = शून्य;
		ret = -EINVAL;
		जाओ fail_alloc_mem;
	पूर्ण
	dev_dbg(&mhba->pdev->dev, "device id : %04X is found.\n",
							mhba->pdev->device);
	ret = mvumi_cfg_hw_reg(mhba);
	अगर (ret) अणु
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for reg\n");
		ret = -ENOMEM;
		जाओ fail_alloc_mem;
	पूर्ण
	mhba->handshake_page = dma_alloc_coherent(&mhba->pdev->dev,
			HSP_MAX_SIZE, &mhba->handshake_page_phys, GFP_KERNEL);
	अगर (!mhba->handshake_page) अणु
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for handshake\n");
		ret = -ENOMEM;
		जाओ fail_alloc_page;
	पूर्ण

	अगर (mvumi_start(mhba)) अणु
		ret = -EINVAL;
		जाओ fail_पढ़ोy_state;
	पूर्ण
	ret = mvumi_alloc_cmds(mhba);
	अगर (ret)
		जाओ fail_पढ़ोy_state;

	वापस 0;

fail_पढ़ोy_state:
	mvumi_release_mem_resource(mhba);
	dma_मुक्त_coherent(&mhba->pdev->dev, HSP_MAX_SIZE,
		mhba->handshake_page, mhba->handshake_page_phys);
fail_alloc_page:
	kमुक्त(mhba->regs);
fail_alloc_mem:
	mvumi_unmap_pci_addr(mhba->pdev, mhba->base_addr);
fail_ioremap:
	pci_release_regions(mhba->pdev);

	वापस ret;
पूर्ण

/**
 * mvumi_io_attach -	Attaches this driver to SCSI mid-layer
 * @mhba:		Adapter soft state
 */
अटल पूर्णांक mvumi_io_attach(काष्ठा mvumi_hba *mhba)
अणु
	काष्ठा Scsi_Host *host = mhba->shost;
	काष्ठा scsi_device *sdev = शून्य;
	पूर्णांक ret;
	अचिन्हित पूर्णांक max_sg = (mhba->ib_max_size + 4 -
		माप(काष्ठा mvumi_msg_frame)) / माप(काष्ठा mvumi_sgl);

	host->irq = mhba->pdev->irq;
	host->unique_id = mhba->unique_id;
	host->can_queue = (mhba->max_io - 1) ? (mhba->max_io - 1) : 1;
	host->sg_tablesize = mhba->max_sge > max_sg ? max_sg : mhba->max_sge;
	host->max_sectors = mhba->max_transfer_size / 512;
	host->cmd_per_lun = (mhba->max_io - 1) ? (mhba->max_io - 1) : 1;
	host->max_id = mhba->max_target_id;
	host->max_cmd_len = MAX_COMMAND_SIZE;

	ret = scsi_add_host(host, &mhba->pdev->dev);
	अगर (ret) अणु
		dev_err(&mhba->pdev->dev, "scsi_add_host failed\n");
		वापस ret;
	पूर्ण
	mhba->fw_flag |= MVUMI_FW_ATTACH;

	mutex_lock(&mhba->sas_discovery_mutex);
	अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580)
		ret = scsi_add_device(host, 0, mhba->max_target_id - 1, 0);
	अन्यथा
		ret = 0;
	अगर (ret) अणु
		dev_err(&mhba->pdev->dev, "add virtual device failed\n");
		mutex_unlock(&mhba->sas_discovery_mutex);
		जाओ fail_add_device;
	पूर्ण

	mhba->dm_thपढ़ो = kthपढ़ो_create(mvumi_rescan_bus,
						mhba, "mvumi_scanthread");
	अगर (IS_ERR(mhba->dm_thपढ़ो)) अणु
		dev_err(&mhba->pdev->dev,
			"failed to create device scan thread\n");
		ret = PTR_ERR(mhba->dm_thपढ़ो);
		mutex_unlock(&mhba->sas_discovery_mutex);
		जाओ fail_create_thपढ़ो;
	पूर्ण
	atomic_set(&mhba->pnp_count, 1);
	wake_up_process(mhba->dm_thपढ़ो);

	mutex_unlock(&mhba->sas_discovery_mutex);
	वापस 0;

fail_create_thपढ़ो:
	अगर (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580)
		sdev = scsi_device_lookup(mhba->shost, 0,
						mhba->max_target_id - 1, 0);
	अगर (sdev) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
	पूर्ण
fail_add_device:
	scsi_हटाओ_host(mhba->shost);
	वापस ret;
पूर्ण

/**
 * mvumi_probe_one -	PCI hotplug entry poपूर्णांक
 * @pdev:		PCI device काष्ठाure
 * @id:			PCI ids of supported hotplugged adapter
 */
अटल पूर्णांक mvumi_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा mvumi_hba *mhba;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, " %#4.04x:%#4.04x:%#4.04x:%#4.04x: ",
			pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
			pdev->subप्रणाली_device);

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = mvumi_pci_set_master(pdev);
	अगर (ret)
		जाओ fail_set_dma_mask;

	host = scsi_host_alloc(&mvumi_ढाँचा, माप(*mhba));
	अगर (!host) अणु
		dev_err(&pdev->dev, "scsi_host_alloc failed\n");
		ret = -ENOMEM;
		जाओ fail_alloc_instance;
	पूर्ण
	mhba = shost_priv(host);

	INIT_LIST_HEAD(&mhba->cmd_pool);
	INIT_LIST_HEAD(&mhba->ob_data_list);
	INIT_LIST_HEAD(&mhba->मुक्त_ob_list);
	INIT_LIST_HEAD(&mhba->res_list);
	INIT_LIST_HEAD(&mhba->रुकोing_req_list);
	mutex_init(&mhba->device_lock);
	INIT_LIST_HEAD(&mhba->mhba_dev_list);
	INIT_LIST_HEAD(&mhba->shost_dev_list);
	atomic_set(&mhba->fw_outstanding, 0);
	init_रुकोqueue_head(&mhba->पूर्णांक_cmd_रुको_q);
	mutex_init(&mhba->sas_discovery_mutex);

	mhba->pdev = pdev;
	mhba->shost = host;
	mhba->unique_id = pdev->bus->number << 8 | pdev->devfn;

	ret = mvumi_init_fw(mhba);
	अगर (ret)
		जाओ fail_init_fw;

	ret = request_irq(mhba->pdev->irq, mvumi_isr_handler, IRQF_SHARED,
				"mvumi", mhba);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register IRQ\n");
		जाओ fail_init_irq;
	पूर्ण

	mhba->instancet->enable_पूर्णांकr(mhba);
	pci_set_drvdata(pdev, mhba);

	ret = mvumi_io_attach(mhba);
	अगर (ret)
		जाओ fail_io_attach;

	mvumi_backup_bar_addr(mhba);
	dev_dbg(&pdev->dev, "probe mvumi driver successfully.\n");

	वापस 0;

fail_io_attach:
	mhba->instancet->disable_पूर्णांकr(mhba);
	मुक्त_irq(mhba->pdev->irq, mhba);
fail_init_irq:
	mvumi_release_fw(mhba);
fail_init_fw:
	scsi_host_put(host);

fail_alloc_instance:
fail_set_dma_mask:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

अटल व्योम mvumi_detach_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा mvumi_hba *mhba;

	mhba = pci_get_drvdata(pdev);
	अगर (mhba->dm_thपढ़ो) अणु
		kthपढ़ो_stop(mhba->dm_thपढ़ो);
		mhba->dm_thपढ़ो = शून्य;
	पूर्ण

	mvumi_detach_devices(mhba);
	host = mhba->shost;
	scsi_हटाओ_host(mhba->shost);
	mvumi_flush_cache(mhba);

	mhba->instancet->disable_पूर्णांकr(mhba);
	मुक्त_irq(mhba->pdev->irq, mhba);
	mvumi_release_fw(mhba);
	scsi_host_put(host);
	pci_disable_device(pdev);
	dev_dbg(&pdev->dev, "driver is removed!\n");
पूर्ण

/**
 * mvumi_shutकरोwn -	Shutकरोwn entry poपूर्णांक
 * @pdev:		PCI device काष्ठाure
 */
अटल व्योम mvumi_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mvumi_hba *mhba = pci_get_drvdata(pdev);

	mvumi_flush_cache(mhba);
पूर्ण

अटल पूर्णांक __maybe_unused mvumi_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा mvumi_hba *mhba = pci_get_drvdata(pdev);

	mvumi_flush_cache(mhba);

	mhba->instancet->disable_पूर्णांकr(mhba);
	mvumi_unmap_pci_addr(pdev, mhba->base_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mvumi_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा mvumi_hba *mhba = pci_get_drvdata(pdev);

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ fail;
	ret = mvumi_map_pci_addr(mhba->pdev, mhba->base_addr);
	अगर (ret)
		जाओ release_regions;

	अगर (mvumi_cfg_hw_reg(mhba)) अणु
		ret = -EINVAL;
		जाओ unmap_pci_addr;
	पूर्ण

	mhba->mmio = mhba->base_addr[0];
	mvumi_reset(mhba);

	अगर (mvumi_start(mhba)) अणु
		ret = -EINVAL;
		जाओ unmap_pci_addr;
	पूर्ण

	mhba->instancet->enable_पूर्णांकr(mhba);

	वापस 0;

unmap_pci_addr:
	mvumi_unmap_pci_addr(pdev, mhba->base_addr);
release_regions:
	pci_release_regions(pdev);
fail:

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mvumi_pm_ops, mvumi_suspend, mvumi_resume);

अटल काष्ठा pci_driver mvumi_pci_driver = अणु

	.name = MV_DRIVER_NAME,
	.id_table = mvumi_pci_table,
	.probe = mvumi_probe_one,
	.हटाओ = mvumi_detach_one,
	.shutकरोwn = mvumi_shutकरोwn,
	.driver.pm = &mvumi_pm_ops,
पूर्ण;

module_pci_driver(mvumi_pci_driver);
