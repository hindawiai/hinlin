<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"
#समावेश "../include/hw_ip/mmu/mmu_general.h"

#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा MMU_ADDR_BUF_SIZE	40
#घोषणा MMU_ASID_BUF_SIZE	10
#घोषणा MMU_KBUF_SIZE		(MMU_ADDR_BUF_SIZE + MMU_ASID_BUF_SIZE)

अटल काष्ठा dentry *hl_debug_root;

अटल पूर्णांक hl_debugfs_i2c_पढ़ो(काष्ठा hl_device *hdev, u8 i2c_bus, u8 i2c_addr,
				u8 i2c_reg, दीर्घ *val)
अणु
	काष्ठा cpucp_packet pkt;
	u64 result;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -EBUSY;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_I2C_RD <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.i2c_bus = i2c_bus;
	pkt.i2c_addr = i2c_addr;
	pkt.i2c_reg = i2c_reg;

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, &result);

	*val = (दीर्घ) result;

	अगर (rc)
		dev_err(hdev->dev, "Failed to read from I2C, error %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_debugfs_i2c_ग_लिखो(काष्ठा hl_device *hdev, u8 i2c_bus, u8 i2c_addr,
				u8 i2c_reg, u32 val)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -EBUSY;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_I2C_WR <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.i2c_bus = i2c_bus;
	pkt.i2c_addr = i2c_addr;
	pkt.i2c_reg = i2c_reg;
	pkt.value = cpu_to_le64(val);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev, "Failed to write to I2C, error %d\n", rc);

	वापस rc;
पूर्ण

अटल व्योम hl_debugfs_led_set(काष्ठा hl_device *hdev, u8 led, u8 state)
अणु
	काष्ठा cpucp_packet pkt;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.ctl = cpu_to_le32(CPUCP_PACKET_LED_SET <<
				CPUCP_PKT_CTL_OPCODE_SHIFT);
	pkt.led_index = cpu_to_le32(led);
	pkt.value = cpu_to_le64(state);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, माप(pkt),
						0, शून्य);

	अगर (rc)
		dev_err(hdev->dev, "Failed to set LED %d, error %d\n", led, rc);
पूर्ण

अटल पूर्णांक command_buffers_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_cb *cb;
	bool first = true;

	spin_lock(&dev_entry->cb_spinlock);

	list_क्रम_each_entry(cb, &dev_entry->cb_list, debugfs_list) अणु
		अगर (first) अणु
			first = false;
			seq_माला_दो(s, "\n");
			seq_माला_दो(s, " CB ID   CTX ID   CB size    CB RefCnt    mmap?   CS counter\n");
			seq_माला_दो(s, "---------------------------------------------------------------\n");
		पूर्ण
		seq_म_लिखो(s,
			"   %03llu        %d    0x%08x      %d          %d          %d\n",
			cb->id, cb->ctx->asid, cb->size,
			kref_पढ़ो(&cb->refcount),
			cb->mmap, atomic_पढ़ो(&cb->cs_cnt));
	पूर्ण

	spin_unlock(&dev_entry->cb_spinlock);

	अगर (!first)
		seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक command_submission_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_cs *cs;
	bool first = true;

	spin_lock(&dev_entry->cs_spinlock);

	list_क्रम_each_entry(cs, &dev_entry->cs_list, debugfs_list) अणु
		अगर (first) अणु
			first = false;
			seq_माला_दो(s, "\n");
			seq_माला_दो(s, " CS ID   CTX ASID   CS RefCnt   Submitted    Completed\n");
			seq_माला_दो(s, "------------------------------------------------------\n");
		पूर्ण
		seq_म_लिखो(s,
			"   %llu       %d          %d           %d            %d\n",
			cs->sequence, cs->ctx->asid,
			kref_पढ़ो(&cs->refcount),
			cs->submitted, cs->completed);
	पूर्ण

	spin_unlock(&dev_entry->cs_spinlock);

	अगर (!first)
		seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक command_submission_jobs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_cs_job *job;
	bool first = true;

	spin_lock(&dev_entry->cs_job_spinlock);

	list_क्रम_each_entry(job, &dev_entry->cs_job_list, debugfs_list) अणु
		अगर (first) अणु
			first = false;
			seq_माला_दो(s, "\n");
			seq_माला_दो(s, " JOB ID   CS ID    CTX ASID   JOB RefCnt   H/W Queue\n");
			seq_माला_दो(s, "----------------------------------------------------\n");
		पूर्ण
		अगर (job->cs)
			seq_म_लिखो(s,
				"   %02d      %llu        %d          %d           %d\n",
				job->id, job->cs->sequence, job->cs->ctx->asid,
				kref_पढ़ो(&job->refcount), job->hw_queue_id);
		अन्यथा
			seq_म_लिखो(s,
				"   %02d      0        %d          %d           %d\n",
				job->id, HL_KERNEL_ASID_ID,
				kref_पढ़ो(&job->refcount), job->hw_queue_id);
	पूर्ण

	spin_unlock(&dev_entry->cs_job_spinlock);

	अगर (!first)
		seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक userptr_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_userptr *userptr;
	अक्षर dma_dir[4][30] = अणु"DMA_BIDIRECTIONAL", "DMA_TO_DEVICE",
				"DMA_FROM_DEVICE", "DMA_NONE"पूर्ण;
	bool first = true;

	spin_lock(&dev_entry->userptr_spinlock);

	list_क्रम_each_entry(userptr, &dev_entry->userptr_list, debugfs_list) अणु
		अगर (first) अणु
			first = false;
			seq_माला_दो(s, "\n");
			seq_माला_दो(s, " user virtual address     size             dma dir\n");
			seq_माला_दो(s, "----------------------------------------------------------\n");
		पूर्ण
		seq_म_लिखो(s,
			"    0x%-14llx      %-10u    %-30s\n",
			userptr->addr, userptr->size, dma_dir[userptr->dir]);
	पूर्ण

	spin_unlock(&dev_entry->userptr_spinlock);

	अगर (!first)
		seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vm_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_vm_hw_block_list_node *lnode;
	काष्ठा hl_ctx *ctx;
	काष्ठा hl_vm *vm;
	काष्ठा hl_vm_hash_node *hnode;
	काष्ठा hl_userptr *userptr;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack = शून्य;
	क्रमागत vm_type_t *vm_type;
	bool once = true;
	u64 j;
	पूर्णांक i;

	अगर (!dev_entry->hdev->mmu_enable)
		वापस 0;

	spin_lock(&dev_entry->ctx_mem_hash_spinlock);

	list_क्रम_each_entry(ctx, &dev_entry->ctx_mem_hash_list, debugfs_list) अणु
		once = false;
		seq_माला_दो(s, "\n\n----------------------------------------------------");
		seq_माला_दो(s, "\n----------------------------------------------------\n\n");
		seq_म_लिखो(s, "ctx asid: %u\n", ctx->asid);

		seq_माला_दो(s, "\nmappings:\n\n");
		seq_माला_दो(s, "    virtual address        size          handle\n");
		seq_माला_दो(s, "----------------------------------------------------\n");
		mutex_lock(&ctx->mem_hash_lock);
		hash_क्रम_each(ctx->mem_hash, i, hnode, node) अणु
			vm_type = hnode->ptr;

			अगर (*vm_type == VM_TYPE_USERPTR) अणु
				userptr = hnode->ptr;
				seq_म_लिखो(s,
					"    0x%-14llx      %-10u\n",
					hnode->vaddr, userptr->size);
			पूर्ण अन्यथा अणु
				phys_pg_pack = hnode->ptr;
				seq_म_लिखो(s,
					"    0x%-14llx      %-10llu       %-4u\n",
					hnode->vaddr, phys_pg_pack->total_size,
					phys_pg_pack->handle);
			पूर्ण
		पूर्ण
		mutex_unlock(&ctx->mem_hash_lock);

		अगर (ctx->asid != HL_KERNEL_ASID_ID &&
		    !list_empty(&ctx->hw_block_mem_list)) अणु
			seq_माला_दो(s, "\nhw_block mappings:\n\n");
			seq_माला_दो(s, "    virtual address    size    HW block id\n");
			seq_माला_दो(s, "-------------------------------------------\n");
			mutex_lock(&ctx->hw_block_list_lock);
			list_क्रम_each_entry(lnode, &ctx->hw_block_mem_list,
					    node) अणु
				seq_म_लिखो(s,
					"    0x%-14lx   %-6u      %-9u\n",
					lnode->vaddr, lnode->size, lnode->id);
			पूर्ण
			mutex_unlock(&ctx->hw_block_list_lock);
		पूर्ण

		vm = &ctx->hdev->vm;
		spin_lock(&vm->idr_lock);

		अगर (!idr_is_empty(&vm->phys_pg_pack_handles))
			seq_माला_दो(s, "\n\nallocations:\n");

		idr_क्रम_each_entry(&vm->phys_pg_pack_handles, phys_pg_pack, i) अणु
			अगर (phys_pg_pack->asid != ctx->asid)
				जारी;

			seq_म_लिखो(s, "\nhandle: %u\n", phys_pg_pack->handle);
			seq_म_लिखो(s, "page size: %u\n\n",
						phys_pg_pack->page_size);
			seq_माला_दो(s, "   physical address\n");
			seq_माला_दो(s, "---------------------\n");
			क्रम (j = 0 ; j < phys_pg_pack->npages ; j++) अणु
				seq_म_लिखो(s, "    0x%-14llx\n",
						phys_pg_pack->pages[j]);
			पूर्ण
		पूर्ण
		spin_unlock(&vm->idr_lock);

	पूर्ण

	spin_unlock(&dev_entry->ctx_mem_hash_spinlock);

	अगर (!once)
		seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mmu_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_device *hdev = dev_entry->hdev;
	काष्ठा hl_ctx *ctx;
	काष्ठा hl_mmu_hop_info hops_info = अणु0पूर्ण;
	u64 virt_addr = dev_entry->mmu_addr, phys_addr;
	पूर्णांक i;

	अगर (!hdev->mmu_enable)
		वापस 0;

	अगर (dev_entry->mmu_asid == HL_KERNEL_ASID_ID)
		ctx = hdev->kernel_ctx;
	अन्यथा
		ctx = hdev->compute_ctx;

	अगर (!ctx) अणु
		dev_err(hdev->dev, "no ctx available\n");
		वापस 0;
	पूर्ण

	अगर (hl_mmu_get_tlb_info(ctx, virt_addr, &hops_info)) अणु
		dev_err(hdev->dev, "virt addr 0x%llx is not mapped to phys addr\n",
				virt_addr);
		वापस 0;
	पूर्ण

	phys_addr = hops_info.hop_info[hops_info.used_hops - 1].hop_pte_val;

	अगर (hops_info.scrambled_vaddr &&
		(dev_entry->mmu_addr != hops_info.scrambled_vaddr))
		seq_म_लिखो(s,
			"asid: %u, virt_addr: 0x%llx, scrambled virt_addr: 0x%llx,\nphys_addr: 0x%llx, scrambled_phys_addr: 0x%llx\n",
			dev_entry->mmu_asid, dev_entry->mmu_addr,
			hops_info.scrambled_vaddr,
			hops_info.unscrambled_paddr, phys_addr);
	अन्यथा
		seq_म_लिखो(s,
			"asid: %u, virt_addr: 0x%llx, phys_addr: 0x%llx\n",
			dev_entry->mmu_asid, dev_entry->mmu_addr, phys_addr);

	क्रम (i = 0 ; i < hops_info.used_hops ; i++) अणु
		seq_म_लिखो(s, "hop%d_addr: 0x%llx\n",
				i, hops_info.hop_info[i].hop_addr);
		seq_म_लिखो(s, "hop%d_pte_addr: 0x%llx\n",
				i, hops_info.hop_info[i].hop_pte_addr);
		seq_म_लिखो(s, "hop%d_pte: 0x%llx\n",
				i, hops_info.hop_info[i].hop_pte_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mmu_asid_va_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_device *hdev = dev_entry->hdev;
	अक्षर kbuf[MMU_KBUF_SIZE];
	अक्षर *c;
	sमाप_प्रकार rc;

	अगर (!hdev->mmu_enable)
		वापस count;

	अगर (count > माप(kbuf) - 1)
		जाओ err;
	अगर (copy_from_user(kbuf, buf, count))
		जाओ err;
	kbuf[count] = 0;

	c = म_अक्षर(kbuf, ' ');
	अगर (!c)
		जाओ err;
	*c = '\0';

	rc = kstrtouपूर्णांक(kbuf, 10, &dev_entry->mmu_asid);
	अगर (rc)
		जाओ err;

	अगर (म_भेदन(c+1, "0x", 2))
		जाओ err;
	rc = kम_से_अदीर्घl(c+3, 16, &dev_entry->mmu_addr);
	अगर (rc)
		जाओ err;

	वापस count;

err:
	dev_err(hdev->dev, "usage: echo <asid> <0xaddr> > mmu\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक engines_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hl_debugfs_entry *entry = s->निजी;
	काष्ठा hl_dbg_device_entry *dev_entry = entry->dev_entry;
	काष्ठा hl_device *hdev = dev_entry->hdev;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev,
				"Can't check device idle during reset\n");
		वापस 0;
	पूर्ण

	hdev->asic_funcs->is_device_idle(hdev, शून्य, 0, s);

	वापस 0;
पूर्ण

अटल bool hl_is_device_va(काष्ठा hl_device *hdev, u64 addr)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;

	अगर (!hdev->mmu_enable)
		जाओ out;

	अगर (prop->dram_supports_भव_memory &&
		(addr >= prop->dmmu.start_addr && addr < prop->dmmu.end_addr))
		वापस true;

	अगर (addr >= prop->pmmu.start_addr &&
		addr < prop->pmmu.end_addr)
		वापस true;

	अगर (addr >= prop->pmmu_huge.start_addr &&
		addr < prop->pmmu_huge.end_addr)
		वापस true;
out:
	वापस false;
पूर्ण

अटल bool hl_is_device_पूर्णांकernal_memory_va(काष्ठा hl_device *hdev, u64 addr,
						u32 size)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 dram_start_addr, dram_end_addr;

	अगर (!hdev->mmu_enable)
		वापस false;

	अगर (prop->dram_supports_भव_memory) अणु
		dram_start_addr = prop->dmmu.start_addr;
		dram_end_addr = prop->dmmu.end_addr;
	पूर्ण अन्यथा अणु
		dram_start_addr = prop->dram_base_address;
		dram_end_addr = prop->dram_end_address;
	पूर्ण

	अगर (hl_mem_area_inside_range(addr, size, dram_start_addr,
					dram_end_addr))
		वापस true;

	अगर (hl_mem_area_inside_range(addr, size, prop->sram_base_address,
					prop->sram_end_address))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक device_va_to_pa(काष्ठा hl_device *hdev, u64 virt_addr, u32 size,
			u64 *phys_addr)
अणु
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	काष्ठा hl_ctx *ctx = hdev->compute_ctx;
	काष्ठा hl_vm_hash_node *hnode;
	काष्ठा hl_userptr *userptr;
	क्रमागत vm_type_t *vm_type;
	bool valid = false;
	u64 end_address;
	u32 range_size;
	पूर्णांक i, rc = 0;

	अगर (!ctx) अणु
		dev_err(hdev->dev, "no ctx available\n");
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy address is mapped */
	mutex_lock(&ctx->mem_hash_lock);
	hash_क्रम_each(ctx->mem_hash, i, hnode, node) अणु
		vm_type = hnode->ptr;

		अगर (*vm_type == VM_TYPE_USERPTR) अणु
			userptr = hnode->ptr;
			range_size = userptr->size;
		पूर्ण अन्यथा अणु
			phys_pg_pack = hnode->ptr;
			range_size = phys_pg_pack->total_size;
		पूर्ण

		end_address = virt_addr + size;
		अगर ((virt_addr >= hnode->vaddr) &&
				(end_address <= hnode->vaddr + range_size)) अणु
			valid = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ctx->mem_hash_lock);

	अगर (!valid) अणु
		dev_err(hdev->dev,
			"virt addr 0x%llx is not mapped\n",
			virt_addr);
		वापस -EINVAL;
	पूर्ण

	rc = hl_mmu_va_to_pa(ctx, virt_addr, phys_addr);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"virt addr 0x%llx is not mapped to phys addr\n",
			virt_addr);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल sमाप_प्रकार hl_data_पढ़ो32(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 addr = entry->addr;
	bool user_address;
	अक्षर पंचांगp_buf[32];
	sमाप_प्रकार rc;
	u32 val;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev, "Can't read during reset\n");
		वापस 0;
	पूर्ण

	अगर (*ppos)
		वापस 0;

	user_address = hl_is_device_va(hdev, addr);
	अगर (user_address) अणु
		rc = device_va_to_pa(hdev, addr, माप(val), &addr);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = hdev->asic_funcs->debugfs_पढ़ो32(hdev, addr, user_address, &val);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to read from 0x%010llx\n", addr);
		वापस rc;
	पूर्ण

	प्र_लिखो(पंचांगp_buf, "0x%08x\n", val);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf));
पूर्ण

अटल sमाप_प्रकार hl_data_ग_लिखो32(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 addr = entry->addr;
	bool user_address;
	u32 value;
	sमाप_प्रकार rc;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev, "Can't write during reset\n");
		वापस 0;
	पूर्ण

	rc = kstrtouपूर्णांक_from_user(buf, count, 16, &value);
	अगर (rc)
		वापस rc;

	user_address = hl_is_device_va(hdev, addr);
	अगर (user_address) अणु
		rc = device_va_to_pa(hdev, addr, माप(value), &addr);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = hdev->asic_funcs->debugfs_ग_लिखो32(hdev, addr, user_address, value);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to write 0x%08x to 0x%010llx\n",
			value, addr);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_data_पढ़ो64(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 addr = entry->addr;
	bool user_address;
	अक्षर पंचांगp_buf[32];
	sमाप_प्रकार rc;
	u64 val;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev, "Can't read during reset\n");
		वापस 0;
	पूर्ण

	अगर (*ppos)
		वापस 0;

	user_address = hl_is_device_va(hdev, addr);
	अगर (user_address) अणु
		rc = device_va_to_pa(hdev, addr, माप(val), &addr);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = hdev->asic_funcs->debugfs_पढ़ो64(hdev, addr, user_address, &val);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to read from 0x%010llx\n", addr);
		वापस rc;
	पूर्ण

	प्र_लिखो(पंचांगp_buf, "0x%016llx\n", val);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf));
पूर्ण

अटल sमाप_प्रकार hl_data_ग_लिखो64(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 addr = entry->addr;
	bool user_address;
	u64 value;
	sमाप_प्रकार rc;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev, "Can't write during reset\n");
		वापस 0;
	पूर्ण

	rc = kम_से_अदीर्घl_from_user(buf, count, 16, &value);
	अगर (rc)
		वापस rc;

	user_address = hl_is_device_va(hdev, addr);
	अगर (user_address) अणु
		rc = device_va_to_pa(hdev, addr, माप(value), &addr);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = hdev->asic_funcs->debugfs_ग_लिखो64(hdev, addr, user_address, value);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to write 0x%016llx to 0x%010llx\n",
			value, addr);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_dma_size_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 addr = entry->addr;
	sमाप_प्रकार rc;
	u32 size;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev, "Can't DMA during reset\n");
		वापस 0;
	पूर्ण
	rc = kstrtouपूर्णांक_from_user(buf, count, 16, &size);
	अगर (rc)
		वापस rc;

	अगर (!size) अणु
		dev_err(hdev->dev, "DMA read failed. size can't be 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (size > SZ_128M) अणु
		dev_err(hdev->dev,
			"DMA read failed. size can't be larger than 128MB\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!hl_is_device_पूर्णांकernal_memory_va(hdev, addr, size)) अणु
		dev_err(hdev->dev,
			"DMA read failed. Invalid 0x%010llx + 0x%08x\n",
			addr, size);
		वापस -EINVAL;
	पूर्ण

	/* Free the previous allocation, अगर there was any */
	entry->blob_desc.size = 0;
	vमुक्त(entry->blob_desc.data);

	entry->blob_desc.data = vदो_स्मृति(size);
	अगर (!entry->blob_desc.data)
		वापस -ENOMEM;

	rc = hdev->asic_funcs->debugfs_पढ़ो_dma(hdev, addr, size,
						entry->blob_desc.data);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to DMA from 0x%010llx\n", addr);
		vमुक्त(entry->blob_desc.data);
		entry->blob_desc.data = शून्य;
		वापस -EIO;
	पूर्ण

	entry->blob_desc.size = size;

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_get_घातer_state(काष्ठा file *f, अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	अक्षर पंचांगp_buf[200];
	पूर्णांक i;

	अगर (*ppos)
		वापस 0;

	अगर (hdev->pdev->current_state == PCI_D0)
		i = 1;
	अन्यथा अगर (hdev->pdev->current_state == PCI_D3hot)
		i = 2;
	अन्यथा
		i = 3;

	प्र_लिखो(पंचांगp_buf,
		"current power state: %d\n1 - D0\n2 - D3hot\n3 - Unknown\n", i);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf));
पूर्ण

अटल sमाप_प्रकार hl_set_घातer_state(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	rc = kstrtouपूर्णांक_from_user(buf, count, 10, &value);
	अगर (rc)
		वापस rc;

	अगर (value == 1) अणु
		pci_set_घातer_state(hdev->pdev, PCI_D0);
		pci_restore_state(hdev->pdev);
		rc = pci_enable_device(hdev->pdev);
	पूर्ण अन्यथा अगर (value == 2) अणु
		pci_save_state(hdev->pdev);
		pci_disable_device(hdev->pdev);
		pci_set_घातer_state(hdev->pdev, PCI_D3hot);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "invalid power state value %u\n", value);
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_i2c_data_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	अक्षर पंचांगp_buf[32];
	दीर्घ val;
	sमाप_प्रकार rc;

	अगर (*ppos)
		वापस 0;

	rc = hl_debugfs_i2c_पढ़ो(hdev, entry->i2c_bus, entry->i2c_addr,
			entry->i2c_reg, &val);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to read from I2C bus %d, addr %d, reg %d\n",
			entry->i2c_bus, entry->i2c_addr, entry->i2c_reg);
		वापस rc;
	पूर्ण

	प्र_लिखो(पंचांगp_buf, "0x%02lx\n", val);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf));

	वापस rc;
पूर्ण

अटल sमाप_प्रकार hl_i2c_data_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	rc = kstrtouपूर्णांक_from_user(buf, count, 16, &value);
	अगर (rc)
		वापस rc;

	rc = hl_debugfs_i2c_ग_लिखो(hdev, entry->i2c_bus, entry->i2c_addr,
			entry->i2c_reg, value);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to write 0x%02x to I2C bus %d, addr %d, reg %d\n",
			value, entry->i2c_bus, entry->i2c_addr, entry->i2c_reg);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_led0_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	rc = kstrtouपूर्णांक_from_user(buf, count, 10, &value);
	अगर (rc)
		वापस rc;

	value = value ? 1 : 0;

	hl_debugfs_led_set(hdev, 0, value);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_led1_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	rc = kstrtouपूर्णांक_from_user(buf, count, 10, &value);
	अगर (rc)
		वापस rc;

	value = value ? 1 : 0;

	hl_debugfs_led_set(hdev, 1, value);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_led2_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	rc = kstrtouपूर्णांक_from_user(buf, count, 10, &value);
	अगर (rc)
		वापस rc;

	value = value ? 1 : 0;

	hl_debugfs_led_set(hdev, 2, value);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_device_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	अटल स्थिर अक्षर *help =
		"Valid values: disable, enable, suspend, resume, cpu_timeout\n";
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, help, म_माप(help));
पूर्ण

अटल sमाप_प्रकार hl_device_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	अक्षर data[30] = अणु0पूर्ण;

	/* करोn't allow partial ग_लिखोs */
	अगर (*ppos != 0)
		वापस 0;

	simple_ग_लिखो_to_buffer(data, 29, ppos, buf, count);

	अगर (म_भेदन("disable", data, म_माप("disable")) == 0) अणु
		hdev->disabled = true;
	पूर्ण अन्यथा अगर (म_भेदन("enable", data, म_माप("enable")) == 0) अणु
		hdev->disabled = false;
	पूर्ण अन्यथा अगर (म_भेदन("suspend", data, म_माप("suspend")) == 0) अणु
		hdev->asic_funcs->suspend(hdev);
	पूर्ण अन्यथा अगर (म_भेदन("resume", data, म_माप("resume")) == 0) अणु
		hdev->asic_funcs->resume(hdev);
	पूर्ण अन्यथा अगर (म_भेदन("cpu_timeout", data, म_माप("cpu_timeout")) == 0) अणु
		hdev->device_cpu_disabled = true;
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev,
			"Valid values: disable, enable, suspend, resume, cpu_timeout\n");
		count = -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_clk_gate_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	अक्षर पंचांगp_buf[200];
	sमाप_प्रकार rc;

	अगर (*ppos)
		वापस 0;

	प्र_लिखो(पंचांगp_buf, "0x%llx\n", hdev->घड़ी_gating_mask);
	rc = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf) + 1);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार hl_clk_gate_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u64 value;
	sमाप_प्रकार rc;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev,
				"Can't change clock gating during reset\n");
		वापस 0;
	पूर्ण

	rc = kम_से_अदीर्घl_from_user(buf, count, 16, &value);
	अगर (rc)
		वापस rc;

	hdev->घड़ी_gating_mask = value;
	hdev->asic_funcs->set_घड़ी_gating(hdev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_stop_on_err_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	अक्षर पंचांगp_buf[200];
	sमाप_प्रकार rc;

	अगर (*ppos)
		वापस 0;

	प्र_लिखो(पंचांगp_buf, "%d\n", hdev->stop_on_err);
	rc = simple_पढ़ो_from_buffer(buf, म_माप(पंचांगp_buf) + 1, ppos, पंचांगp_buf,
			म_माप(पंचांगp_buf) + 1);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार hl_stop_on_err_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;
	u32 value;
	sमाप_प्रकार rc;

	अगर (atomic_पढ़ो(&hdev->in_reset)) अणु
		dev_warn_ratelimited(hdev->dev,
				"Can't change stop on error during reset\n");
		वापस 0;
	पूर्ण

	rc = kstrtouपूर्णांक_from_user(buf, count, 10, &value);
	अगर (rc)
		वापस rc;

	hdev->stop_on_err = value ? 1 : 0;

	hl_device_reset(hdev, 0);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hl_security_violations_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hl_dbg_device_entry *entry = file_inode(f)->i_निजी;
	काष्ठा hl_device *hdev = entry->hdev;

	hdev->asic_funcs->ack_protection_bits_errors(hdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations hl_data32b_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_data_पढ़ो32,
	.ग_लिखो = hl_data_ग_लिखो32
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_data64b_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_data_पढ़ो64,
	.ग_लिखो = hl_data_ग_लिखो64
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_dma_size_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = hl_dma_size_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_i2c_data_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_i2c_data_पढ़ो,
	.ग_लिखो = hl_i2c_data_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_घातer_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_get_घातer_state,
	.ग_लिखो = hl_set_घातer_state
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_led0_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = hl_led0_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_led1_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = hl_led1_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_led2_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = hl_led2_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_device_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_device_पढ़ो,
	.ग_लिखो = hl_device_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_clk_gate_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_clk_gate_पढ़ो,
	.ग_लिखो = hl_clk_gate_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_stop_on_err_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_stop_on_err_पढ़ो,
	.ग_लिखो = hl_stop_on_err_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations hl_security_violations_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = hl_security_violations_पढ़ो
पूर्ण;

अटल स्थिर काष्ठा hl_info_list hl_debugfs_list[] = अणु
	अणु"command_buffers", command_buffers_show, शून्यपूर्ण,
	अणु"command_submission", command_submission_show, शून्यपूर्ण,
	अणु"command_submission_jobs", command_submission_jobs_show, शून्यपूर्ण,
	अणु"userptr", userptr_show, शून्यपूर्ण,
	अणु"vm", vm_show, शून्यपूर्ण,
	अणु"mmu", mmu_show, mmu_asid_va_ग_लिखोपूर्ण,
	अणु"engines", engines_show, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक hl_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hl_debugfs_entry *node = inode->i_निजी;

	वापस single_खोलो(file, node->info_ent->show, node);
पूर्ण

अटल sमाप_प्रकार hl_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा hl_debugfs_entry *node = file->f_inode->i_निजी;

	अगर (node->info_ent->ग_लिखो)
		वापस node->info_ent->ग_लिखो(file, buf, count, f_pos);
	अन्यथा
		वापस -EINVAL;

पूर्ण

अटल स्थिर काष्ठा file_operations hl_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = hl_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = hl_debugfs_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम hl_debugfs_add_device(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;
	पूर्णांक count = ARRAY_SIZE(hl_debugfs_list);
	काष्ठा hl_debugfs_entry *entry;
	पूर्णांक i;

	dev_entry->hdev = hdev;
	dev_entry->entry_arr = kदो_स्मृति_array(count,
					माप(काष्ठा hl_debugfs_entry),
					GFP_KERNEL);
	अगर (!dev_entry->entry_arr)
		वापस;

	dev_entry->blob_desc.size = 0;
	dev_entry->blob_desc.data = शून्य;

	INIT_LIST_HEAD(&dev_entry->file_list);
	INIT_LIST_HEAD(&dev_entry->cb_list);
	INIT_LIST_HEAD(&dev_entry->cs_list);
	INIT_LIST_HEAD(&dev_entry->cs_job_list);
	INIT_LIST_HEAD(&dev_entry->userptr_list);
	INIT_LIST_HEAD(&dev_entry->ctx_mem_hash_list);
	mutex_init(&dev_entry->file_mutex);
	spin_lock_init(&dev_entry->cb_spinlock);
	spin_lock_init(&dev_entry->cs_spinlock);
	spin_lock_init(&dev_entry->cs_job_spinlock);
	spin_lock_init(&dev_entry->userptr_spinlock);
	spin_lock_init(&dev_entry->ctx_mem_hash_spinlock);

	dev_entry->root = debugfs_create_dir(dev_name(hdev->dev),
						hl_debug_root);

	debugfs_create_x64("addr",
				0644,
				dev_entry->root,
				&dev_entry->addr);

	debugfs_create_file("data32",
				0644,
				dev_entry->root,
				dev_entry,
				&hl_data32b_fops);

	debugfs_create_file("data64",
				0644,
				dev_entry->root,
				dev_entry,
				&hl_data64b_fops);

	debugfs_create_file("set_power_state",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_घातer_fops);

	debugfs_create_u8("i2c_bus",
				0644,
				dev_entry->root,
				&dev_entry->i2c_bus);

	debugfs_create_u8("i2c_addr",
				0644,
				dev_entry->root,
				&dev_entry->i2c_addr);

	debugfs_create_u8("i2c_reg",
				0644,
				dev_entry->root,
				&dev_entry->i2c_reg);

	debugfs_create_file("i2c_data",
				0644,
				dev_entry->root,
				dev_entry,
				&hl_i2c_data_fops);

	debugfs_create_file("led0",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_led0_fops);

	debugfs_create_file("led1",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_led1_fops);

	debugfs_create_file("led2",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_led2_fops);

	debugfs_create_file("device",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_device_fops);

	debugfs_create_file("clk_gate",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_clk_gate_fops);

	debugfs_create_file("stop_on_err",
				0644,
				dev_entry->root,
				dev_entry,
				&hl_stop_on_err_fops);

	debugfs_create_file("dump_security_violations",
				0644,
				dev_entry->root,
				dev_entry,
				&hl_security_violations_fops);

	debugfs_create_file("dma_size",
				0200,
				dev_entry->root,
				dev_entry,
				&hl_dma_size_fops);

	debugfs_create_blob("data_dma",
				0400,
				dev_entry->root,
				&dev_entry->blob_desc);

	क्रम (i = 0, entry = dev_entry->entry_arr ; i < count ; i++, entry++) अणु
		debugfs_create_file(hl_debugfs_list[i].name,
					0444,
					dev_entry->root,
					entry,
					&hl_debugfs_fops);
		entry->info_ent = &hl_debugfs_list[i];
		entry->dev_entry = dev_entry;
	पूर्ण
पूर्ण

व्योम hl_debugfs_हटाओ_device(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_dbg_device_entry *entry = &hdev->hl_debugfs;

	debugfs_हटाओ_recursive(entry->root);

	mutex_destroy(&entry->file_mutex);

	vमुक्त(entry->blob_desc.data);

	kमुक्त(entry->entry_arr);
पूर्ण

व्योम hl_debugfs_add_file(काष्ठा hl_fpriv *hpriv)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hpriv->hdev->hl_debugfs;

	mutex_lock(&dev_entry->file_mutex);
	list_add(&hpriv->debugfs_list, &dev_entry->file_list);
	mutex_unlock(&dev_entry->file_mutex);
पूर्ण

व्योम hl_debugfs_हटाओ_file(काष्ठा hl_fpriv *hpriv)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hpriv->hdev->hl_debugfs;

	mutex_lock(&dev_entry->file_mutex);
	list_del(&hpriv->debugfs_list);
	mutex_unlock(&dev_entry->file_mutex);
पूर्ण

व्योम hl_debugfs_add_cb(काष्ठा hl_cb *cb)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &cb->hdev->hl_debugfs;

	spin_lock(&dev_entry->cb_spinlock);
	list_add(&cb->debugfs_list, &dev_entry->cb_list);
	spin_unlock(&dev_entry->cb_spinlock);
पूर्ण

व्योम hl_debugfs_हटाओ_cb(काष्ठा hl_cb *cb)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &cb->hdev->hl_debugfs;

	spin_lock(&dev_entry->cb_spinlock);
	list_del(&cb->debugfs_list);
	spin_unlock(&dev_entry->cb_spinlock);
पूर्ण

व्योम hl_debugfs_add_cs(काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &cs->ctx->hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_spinlock);
	list_add(&cs->debugfs_list, &dev_entry->cs_list);
	spin_unlock(&dev_entry->cs_spinlock);
पूर्ण

व्योम hl_debugfs_हटाओ_cs(काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &cs->ctx->hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_spinlock);
	list_del(&cs->debugfs_list);
	spin_unlock(&dev_entry->cs_spinlock);
पूर्ण

व्योम hl_debugfs_add_job(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_job_spinlock);
	list_add(&job->debugfs_list, &dev_entry->cs_job_list);
	spin_unlock(&dev_entry->cs_job_spinlock);
पूर्ण

व्योम hl_debugfs_हटाओ_job(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_job_spinlock);
	list_del(&job->debugfs_list);
	spin_unlock(&dev_entry->cs_job_spinlock);
पूर्ण

व्योम hl_debugfs_add_userptr(काष्ठा hl_device *hdev, काष्ठा hl_userptr *userptr)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->userptr_spinlock);
	list_add(&userptr->debugfs_list, &dev_entry->userptr_list);
	spin_unlock(&dev_entry->userptr_spinlock);
पूर्ण

व्योम hl_debugfs_हटाओ_userptr(काष्ठा hl_device *hdev,
				काष्ठा hl_userptr *userptr)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->userptr_spinlock);
	list_del(&userptr->debugfs_list);
	spin_unlock(&dev_entry->userptr_spinlock);
पूर्ण

व्योम hl_debugfs_add_ctx_mem_hash(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->ctx_mem_hash_spinlock);
	list_add(&ctx->debugfs_list, &dev_entry->ctx_mem_hash_list);
	spin_unlock(&dev_entry->ctx_mem_hash_spinlock);
पूर्ण

व्योम hl_debugfs_हटाओ_ctx_mem_hash(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_dbg_device_entry *dev_entry = &hdev->hl_debugfs;

	spin_lock(&dev_entry->ctx_mem_hash_spinlock);
	list_del(&ctx->debugfs_list);
	spin_unlock(&dev_entry->ctx_mem_hash_spinlock);
पूर्ण

व्योम __init hl_debugfs_init(व्योम)
अणु
	hl_debug_root = debugfs_create_dir("habanalabs", शून्य);
पूर्ण

व्योम hl_debugfs_fini(व्योम)
अणु
	debugfs_हटाओ_recursive(hl_debug_root);
पूर्ण
