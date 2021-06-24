<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_init.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)mpt3sas/mpt3sas_trigger_diag.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

अटल bool esas2r_iniपंचांगem_alloc(काष्ठा esas2r_adapter *a,
				 काष्ठा esas2r_mem_desc *mem_desc,
				 u32 align)
अणु
	mem_desc->esas2r_param = mem_desc->size + align;
	mem_desc->virt_addr = शून्य;
	mem_desc->phys_addr = 0;
	mem_desc->esas2r_data = dma_alloc_coherent(&a->pcid->dev,
						   (माप_प्रकार)mem_desc->
						   esas2r_param,
						   (dma_addr_t *)&mem_desc->
						   phys_addr,
						   GFP_KERNEL);

	अगर (mem_desc->esas2r_data == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate %lu bytes of consistent memory!",
			   (दीर्घ
			    अचिन्हित
			    पूर्णांक)mem_desc->esas2r_param);
		वापस false;
	पूर्ण

	mem_desc->virt_addr = PTR_ALIGN(mem_desc->esas2r_data, align);
	mem_desc->phys_addr = ALIGN(mem_desc->phys_addr, align);
	स_रखो(mem_desc->virt_addr, 0, mem_desc->size);
	वापस true;
पूर्ण

अटल व्योम esas2r_iniपंचांगem_मुक्त(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_mem_desc *mem_desc)
अणु
	अगर (mem_desc->virt_addr == शून्य)
		वापस;

	/*
	 * Careful!  phys_addr and virt_addr may have been adjusted from the
	 * original allocation in order to वापस the desired alignment.  That
	 * means we have to use the original address (in esas2r_data) and size
	 * (esas2r_param) and calculate the original physical address based on
	 * the dअगरference between the requested and actual allocation size.
	 */
	अगर (mem_desc->phys_addr) अणु
		पूर्णांक unalign = ((u8 *)mem_desc->virt_addr) -
			      ((u8 *)mem_desc->esas2r_data);

		dma_मुक्त_coherent(&a->pcid->dev,
				  (माप_प्रकार)mem_desc->esas2r_param,
				  mem_desc->esas2r_data,
				  (dma_addr_t)(mem_desc->phys_addr - unalign));
	पूर्ण अन्यथा अणु
		kमुक्त(mem_desc->esas2r_data);
	पूर्ण

	mem_desc->virt_addr = शून्य;
पूर्ण

अटल bool alloc_vda_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq)
अणु
	काष्ठा esas2r_mem_desc *memdesc = kzalloc(
		माप(काष्ठा esas2r_mem_desc), GFP_KERNEL);

	अगर (memdesc == शून्य) अणु
		esas2r_hdebug("could not alloc mem for vda request memdesc\n");
		वापस false;
	पूर्ण

	memdesc->size = माप(जोड़ atto_vda_req) +
			ESAS2R_DATA_BUF_LEN;

	अगर (!esas2r_iniपंचांगem_alloc(a, memdesc, 256)) अणु
		esas2r_hdebug("could not alloc mem for vda request\n");
		kमुक्त(memdesc);
		वापस false;
	पूर्ण

	a->num_vrqs++;
	list_add(&memdesc->next_desc, &a->vrq_mds_head);

	rq->vrq_md = memdesc;
	rq->vrq = (जोड़ atto_vda_req *)memdesc->virt_addr;
	rq->vrq->scsi.handle = a->num_vrqs;

	वापस true;
पूर्ण

अटल व्योम esas2r_unmap_regions(काष्ठा esas2r_adapter *a)
अणु
	अगर (a->regs)
		iounmap((व्योम __iomem *)a->regs);

	a->regs = शून्य;

	pci_release_region(a->pcid, 2);

	अगर (a->data_winकरोw)
		iounmap((व्योम __iomem *)a->data_winकरोw);

	a->data_winकरोw = शून्य;

	pci_release_region(a->pcid, 0);
पूर्ण

अटल पूर्णांक esas2r_map_regions(काष्ठा esas2r_adapter *a)
अणु
	पूर्णांक error;

	a->regs = शून्य;
	a->data_winकरोw = शून्य;

	error = pci_request_region(a->pcid, 2, a->name);
	अगर (error != 0) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "pci_request_region(2) failed, error %d",
			   error);

		वापस error;
	पूर्ण

	a->regs = (व्योम __क्रमce *)ioremap(pci_resource_start(a->pcid, 2),
					  pci_resource_len(a->pcid, 2));
	अगर (a->regs == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "ioremap failed for regs mem region\n");
		pci_release_region(a->pcid, 2);
		वापस -EFAULT;
	पूर्ण

	error = pci_request_region(a->pcid, 0, a->name);
	अगर (error != 0) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "pci_request_region(2) failed, error %d",
			   error);
		esas2r_unmap_regions(a);
		वापस error;
	पूर्ण

	a->data_winकरोw = (व्योम __क्रमce *)ioremap(pci_resource_start(a->pcid,
								    0),
						 pci_resource_len(a->pcid, 0));
	अगर (a->data_winकरोw == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "ioremap failed for data_window mem region\n");
		esas2r_unmap_regions(a);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम esas2r_setup_पूर्णांकerrupts(काष्ठा esas2r_adapter *a, पूर्णांक पूर्णांकr_mode)
अणु
	पूर्णांक i;

	/* Set up पूर्णांकerrupt mode based on the requested value */
	चयन (पूर्णांकr_mode) अणु
	हाल INTR_MODE_LEGACY:
use_legacy_पूर्णांकerrupts:
		a->पूर्णांकr_mode = INTR_MODE_LEGACY;
		अवरोध;

	हाल INTR_MODE_MSI:
		i = pci_enable_msi(a->pcid);
		अगर (i != 0) अणु
			esas2r_log(ESAS2R_LOG_WARN,
				   "failed to enable MSI for adapter %d, "
				   "falling back to legacy interrupts "
				   "(err=%d)", a->index,
				   i);
			जाओ use_legacy_पूर्णांकerrupts;
		पूर्ण
		a->पूर्णांकr_mode = INTR_MODE_MSI;
		set_bit(AF2_MSI_ENABLED, &a->flags2);
		अवरोध;


	शेष:
		esas2r_log(ESAS2R_LOG_WARN,
			   "unknown interrupt_mode %d requested, "
			   "falling back to legacy interrupt",
			   पूर्णांकerrupt_mode);
		जाओ use_legacy_पूर्णांकerrupts;
	पूर्ण
पूर्ण

अटल व्योम esas2r_claim_पूर्णांकerrupts(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags = 0;

	अगर (a->पूर्णांकr_mode == INTR_MODE_LEGACY)
		flags |= IRQF_SHARED;

	esas2r_log(ESAS2R_LOG_INFO,
		   "esas2r_claim_interrupts irq=%d (%p, %s, %lx)",
		   a->pcid->irq, a, a->name, flags);

	अगर (request_irq(a->pcid->irq,
			(a->पूर्णांकr_mode ==
			 INTR_MODE_LEGACY) ? esas2r_पूर्णांकerrupt :
			esas2r_msi_पूर्णांकerrupt,
			flags,
			a->name,
			a)) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "unable to request IRQ %02X",
			   a->pcid->irq);
		वापस;
	पूर्ण

	set_bit(AF2_IRQ_CLAIMED, &a->flags2);
	esas2r_log(ESAS2R_LOG_INFO,
		   "claimed IRQ %d flags: 0x%lx",
		   a->pcid->irq, flags);
पूर्ण

पूर्णांक esas2r_init_adapter(काष्ठा Scsi_Host *host, काष्ठा pci_dev *pcid,
			पूर्णांक index)
अणु
	काष्ठा esas2r_adapter *a;
	u64 bus_addr = 0;
	पूर्णांक i;
	व्योम *next_uncached;
	काष्ठा esas2r_request *first_request, *last_request;
	bool dma64 = false;

	अगर (index >= MAX_ADAPTERS) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "tried to init invalid adapter index %u!",
			   index);
		वापस 0;
	पूर्ण

	अगर (esas2r_adapters[index]) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "tried to init existing adapter index %u!",
			   index);
		वापस 0;
	पूर्ण

	a = (काष्ठा esas2r_adapter *)host->hostdata;
	स_रखो(a, 0, माप(काष्ठा esas2r_adapter));
	a->pcid = pcid;
	a->host = host;

	अगर (माप(dma_addr_t) > 4 &&
	    dma_get_required_mask(&pcid->dev) > DMA_BIT_MASK(32) &&
	    !dma_set_mask_and_coherent(&pcid->dev, DMA_BIT_MASK(64)))
		dma64 = true;

	अगर (!dma64 && dma_set_mask_and_coherent(&pcid->dev, DMA_BIT_MASK(32))) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "failed to set DMA mask");
		esas2r_समाप्त_adapter(index);
		वापस 0;
	पूर्ण

	esas2r_log_dev(ESAS2R_LOG_INFO, &pcid->dev,
		       "%s-bit PCI addressing enabled\n", dma64 ? "64" : "32");

	esas2r_adapters[index] = a;
	प्र_लिखो(a->name, ESAS2R_DRVR_NAME "_%02d", index);
	esas2r_debug("new adapter %p, name %s", a, a->name);
	spin_lock_init(&a->request_lock);
	spin_lock_init(&a->fw_event_lock);
	mutex_init(&a->fm_api_mutex);
	mutex_init(&a->fs_api_mutex);
	sema_init(&a->nvram_semaphore, 1);

	esas2r_fw_event_off(a);
	snम_लिखो(a->fw_event_q_name, ESAS2R_KOBJ_NAME_LEN, "esas2r/%d",
		 a->index);
	a->fw_event_q = create_singlethपढ़ो_workqueue(a->fw_event_q_name);

	init_रुकोqueue_head(&a->buffered_ioctl_रुकोer);
	init_रुकोqueue_head(&a->nvram_रुकोer);
	init_रुकोqueue_head(&a->fm_api_रुकोer);
	init_रुकोqueue_head(&a->fs_api_रुकोer);
	init_रुकोqueue_head(&a->vda_रुकोer);

	INIT_LIST_HEAD(&a->general_req.req_list);
	INIT_LIST_HEAD(&a->active_list);
	INIT_LIST_HEAD(&a->defer_list);
	INIT_LIST_HEAD(&a->मुक्त_sg_list_head);
	INIT_LIST_HEAD(&a->avail_request);
	INIT_LIST_HEAD(&a->vrq_mds_head);
	INIT_LIST_HEAD(&a->fw_event_list);

	first_request = (काष्ठा esas2r_request *)((u8 *)(a + 1));

	क्रम (last_request = first_request, i = 1; i < num_requests;
	     last_request++, i++) अणु
		INIT_LIST_HEAD(&last_request->req_list);
		list_add_tail(&last_request->comp_list, &a->avail_request);
		अगर (!alloc_vda_req(a, last_request)) अणु
			esas2r_log(ESAS2R_LOG_CRIT,
				   "failed to allocate a VDA request!");
			esas2r_समाप्त_adapter(index);
			वापस 0;
		पूर्ण
	पूर्ण

	esas2r_debug("requests: %p to %p (%d, %d)", first_request,
		     last_request,
		     माप(*first_request),
		     num_requests);

	अगर (esas2r_map_regions(a) != 0) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "could not map PCI regions!");
		esas2r_समाप्त_adapter(index);
		वापस 0;
	पूर्ण

	a->index = index;

	/* पूर्णांकerrupts will be disabled until we are करोne with init */
	atomic_inc(&a->dis_पूर्णांकs_cnt);
	atomic_inc(&a->disable_cnt);
	set_bit(AF_CHPRST_PENDING, &a->flags);
	set_bit(AF_DISC_PENDING, &a->flags);
	set_bit(AF_FIRST_INIT, &a->flags);
	set_bit(AF_LEGACY_SGE_MODE, &a->flags);

	a->init_msg = ESAS2R_INIT_MSG_START;
	a->max_vdareq_size = 128;
	a->build_sgl = esas2r_build_sg_list_sge;

	esas2r_setup_पूर्णांकerrupts(a, पूर्णांकerrupt_mode);

	a->uncached_size = esas2r_get_uncached_size(a);
	a->uncached = dma_alloc_coherent(&pcid->dev,
					 (माप_प्रकार)a->uncached_size,
					 (dma_addr_t *)&bus_addr,
					 GFP_KERNEL);
	अगर (a->uncached == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate %d bytes of consistent memory!",
			   a->uncached_size);
		esas2r_समाप्त_adapter(index);
		वापस 0;
	पूर्ण

	a->uncached_phys = bus_addr;

	esas2r_debug("%d bytes uncached memory allocated @ %p (%x:%x)",
		     a->uncached_size,
		     a->uncached,
		     upper_32_bits(bus_addr),
		     lower_32_bits(bus_addr));
	स_रखो(a->uncached, 0, a->uncached_size);
	next_uncached = a->uncached;

	अगर (!esas2r_init_adapter_काष्ठा(a,
					&next_uncached)) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to initialize adapter structure (2)!");
		esas2r_समाप्त_adapter(index);
		वापस 0;
	पूर्ण

	tasklet_init(&a->tasklet,
		     esas2r_adapter_tasklet,
		     (अचिन्हित दीर्घ)a);

	/*
	 * Disable chip पूर्णांकerrupts to prevent spurious पूर्णांकerrupts
	 * until we claim the IRQ.
	 */
	esas2r_disable_chip_पूर्णांकerrupts(a);
	esas2r_check_adapter(a);

	अगर (!esas2r_init_adapter_hw(a, true)) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "failed to initialize hardware!");
	पूर्ण अन्यथा अणु
		esas2r_debug("esas2r_init_adapter ok");
	पूर्ण

	esas2r_claim_पूर्णांकerrupts(a);

	अगर (test_bit(AF2_IRQ_CLAIMED, &a->flags2))
		esas2r_enable_chip_पूर्णांकerrupts(a);

	set_bit(AF2_INIT_DONE, &a->flags2);
	अगर (!test_bit(AF_DEGRADED_MODE, &a->flags))
		esas2r_kickoff_समयr(a);
	esas2r_debug("esas2r_init_adapter done for %p (%d)",
		     a, a->disable_cnt);

	वापस 1;
पूर्ण

अटल व्योम esas2r_adapter_घातer_करोwn(काष्ठा esas2r_adapter *a,
				      पूर्णांक घातer_management)
अणु
	काष्ठा esas2r_mem_desc *memdesc, *next;

	अगर ((test_bit(AF2_INIT_DONE, &a->flags2))
	    &&  (!test_bit(AF_DEGRADED_MODE, &a->flags))) अणु
		अगर (!घातer_management) अणु
			del_समयr_sync(&a->समयr);
			tasklet_समाप्त(&a->tasklet);
		पूर्ण
		esas2r_घातer_करोwn(a);

		/*
		 * There are versions of firmware that करो not handle the sync
		 * cache command correctly.  Stall here to ensure that the
		 * cache is lazily flushed.
		 */
		mdelay(500);
		esas2r_debug("chip halted");
	पूर्ण

	/* Remove sysfs binary files */
	अगर (a->sysfs_fw_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj, &bin_attr_fw);
		a->sysfs_fw_created = 0;
	पूर्ण

	अगर (a->sysfs_fs_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj, &bin_attr_fs);
		a->sysfs_fs_created = 0;
	पूर्ण

	अगर (a->sysfs_vda_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj, &bin_attr_vda);
		a->sysfs_vda_created = 0;
	पूर्ण

	अगर (a->sysfs_hw_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj, &bin_attr_hw);
		a->sysfs_hw_created = 0;
	पूर्ण

	अगर (a->sysfs_live_nvram_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj,
				      &bin_attr_live_nvram);
		a->sysfs_live_nvram_created = 0;
	पूर्ण

	अगर (a->sysfs_शेष_nvram_created) अणु
		sysfs_हटाओ_bin_file(&a->host->shost_dev.kobj,
				      &bin_attr_शेष_nvram);
		a->sysfs_शेष_nvram_created = 0;
	पूर्ण

	/* Clean up पूर्णांकerrupts */
	अगर (test_bit(AF2_IRQ_CLAIMED, &a->flags2)) अणु
		esas2r_log_dev(ESAS2R_LOG_INFO,
			       &(a->pcid->dev),
			       "free_irq(%d) called", a->pcid->irq);

		मुक्त_irq(a->pcid->irq, a);
		esas2r_debug("IRQ released");
		clear_bit(AF2_IRQ_CLAIMED, &a->flags2);
	पूर्ण

	अगर (test_bit(AF2_MSI_ENABLED, &a->flags2)) अणु
		pci_disable_msi(a->pcid);
		clear_bit(AF2_MSI_ENABLED, &a->flags2);
		esas2r_debug("MSI disabled");
	पूर्ण

	अगर (a->inbound_list_md.virt_addr)
		esas2r_iniपंचांगem_मुक्त(a, &a->inbound_list_md);

	अगर (a->outbound_list_md.virt_addr)
		esas2r_iniपंचांगem_मुक्त(a, &a->outbound_list_md);

	list_क्रम_each_entry_safe(memdesc, next, &a->मुक्त_sg_list_head,
				 next_desc) अणु
		esas2r_iniपंचांगem_मुक्त(a, memdesc);
	पूर्ण

	/* Following मुक्तs everything allocated via alloc_vda_req */
	list_क्रम_each_entry_safe(memdesc, next, &a->vrq_mds_head, next_desc) अणु
		esas2r_iniपंचांगem_मुक्त(a, memdesc);
		list_del(&memdesc->next_desc);
		kमुक्त(memdesc);
	पूर्ण

	kमुक्त(a->first_ae_req);
	a->first_ae_req = शून्य;

	kमुक्त(a->sg_list_mds);
	a->sg_list_mds = शून्य;

	kमुक्त(a->req_table);
	a->req_table = शून्य;

	अगर (a->regs) अणु
		esas2r_unmap_regions(a);
		a->regs = शून्य;
		a->data_winकरोw = शून्य;
		esas2r_debug("regions unmapped");
	पूर्ण
पूर्ण

/* Release/मुक्त allocated resources क्रम specअगरied adapters. */
व्योम esas2r_समाप्त_adapter(पूर्णांक i)
अणु
	काष्ठा esas2r_adapter *a = esas2r_adapters[i];

	अगर (a) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा workqueue_काष्ठा *wq;
		esas2r_debug("killing adapter %p [%d] ", a, i);
		esas2r_fw_event_off(a);
		esas2r_adapter_घातer_करोwn(a, 0);
		अगर (esas2r_buffered_ioctl &&
		    (a->pcid == esas2r_buffered_ioctl_pcid)) अणु
			dma_मुक्त_coherent(&a->pcid->dev,
					  (माप_प्रकार)esas2r_buffered_ioctl_size,
					  esas2r_buffered_ioctl,
					  esas2r_buffered_ioctl_addr);
			esas2r_buffered_ioctl = शून्य;
		पूर्ण

		अगर (a->vda_buffer) अणु
			dma_मुक्त_coherent(&a->pcid->dev,
					  (माप_प्रकार)VDA_MAX_BUFFER_SIZE,
					  a->vda_buffer,
					  (dma_addr_t)a->ppvda_buffer);
			a->vda_buffer = शून्य;
		पूर्ण
		अगर (a->fs_api_buffer) अणु
			dma_मुक्त_coherent(&a->pcid->dev,
					  (माप_प्रकार)a->fs_api_buffer_size,
					  a->fs_api_buffer,
					  (dma_addr_t)a->ppfs_api_buffer);
			a->fs_api_buffer = शून्य;
		पूर्ण

		kमुक्त(a->local_atto_ioctl);
		a->local_atto_ioctl = शून्य;

		spin_lock_irqsave(&a->fw_event_lock, flags);
		wq = a->fw_event_q;
		a->fw_event_q = शून्य;
		spin_unlock_irqrestore(&a->fw_event_lock, flags);
		अगर (wq)
			destroy_workqueue(wq);

		अगर (a->uncached) अणु
			dma_मुक्त_coherent(&a->pcid->dev,
					  (माप_प्रकार)a->uncached_size,
					  a->uncached,
					  (dma_addr_t)a->uncached_phys);
			a->uncached = शून्य;
			esas2r_debug("uncached area freed");
		पूर्ण

		esas2r_log_dev(ESAS2R_LOG_INFO,
			       &(a->pcid->dev),
			       "pci_disable_device() called.  msix_enabled: %d "
			       "msi_enabled: %d irq: %d pin: %d",
			       a->pcid->msix_enabled,
			       a->pcid->msi_enabled,
			       a->pcid->irq,
			       a->pcid->pin);

		esas2r_log_dev(ESAS2R_LOG_INFO,
			       &(a->pcid->dev),
			       "before pci_disable_device() enable_cnt: %d",
			       a->pcid->enable_cnt.counter);

		pci_disable_device(a->pcid);
		esas2r_log_dev(ESAS2R_LOG_INFO,
			       &(a->pcid->dev),
			       "after pci_disable_device() enable_cnt: %d",
			       a->pcid->enable_cnt.counter);

		esas2r_log_dev(ESAS2R_LOG_INFO,
			       &(a->pcid->dev),
			       "pci_set_drv_data(%p, NULL) called",
			       a->pcid);

		pci_set_drvdata(a->pcid, शून्य);
		esas2r_adapters[i] = शून्य;

		अगर (test_bit(AF2_INIT_DONE, &a->flags2)) अणु
			clear_bit(AF2_INIT_DONE, &a->flags2);

			set_bit(AF_DEGRADED_MODE, &a->flags);

			esas2r_log_dev(ESAS2R_LOG_INFO,
				       &(a->host->shost_gendev),
				       "scsi_remove_host() called");

			scsi_हटाओ_host(a->host);

			esas2r_log_dev(ESAS2R_LOG_INFO,
				       &(a->host->shost_gendev),
				       "scsi_host_put() called");

			scsi_host_put(a->host);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused esas2r_suspend(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(dev);
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)host->hostdata;

	esas2r_log_dev(ESAS2R_LOG_INFO, dev, "suspending adapter()");
	अगर (!a)
		वापस -ENODEV;

	esas2r_adapter_घातer_करोwn(a, 1);
	esas2r_log_dev(ESAS2R_LOG_INFO, dev, "esas2r_suspend(): 0");
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused esas2r_resume(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(dev);
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)host->hostdata;
	पूर्णांक rez = 0;

	esas2r_log_dev(ESAS2R_LOG_INFO, dev, "resuming adapter()");

	अगर (!a) अणु
		rez = -ENODEV;
		जाओ error_निकास;
	पूर्ण

	अगर (esas2r_map_regions(a) != 0) अणु
		esas2r_log(ESAS2R_LOG_CRIT, "could not re-map PCI regions!");
		rez = -ENOMEM;
		जाओ error_निकास;
	पूर्ण

	/* Set up पूर्णांकerupt mode */
	esas2r_setup_पूर्णांकerrupts(a, a->पूर्णांकr_mode);

	/*
	 * Disable chip पूर्णांकerrupts to prevent spurious पूर्णांकerrupts until we
	 * claim the IRQ.
	 */
	esas2r_disable_chip_पूर्णांकerrupts(a);
	अगर (!esas2r_घातer_up(a, true)) अणु
		esas2r_debug("yikes, esas2r_power_up failed");
		rez = -ENOMEM;
		जाओ error_निकास;
	पूर्ण

	esas2r_claim_पूर्णांकerrupts(a);

	अगर (test_bit(AF2_IRQ_CLAIMED, &a->flags2)) अणु
		/*
		 * Now that प्रणाली पूर्णांकerrupt(s) are claimed, we can enable
		 * chip पूर्णांकerrupts.
		 */
		esas2r_enable_chip_पूर्णांकerrupts(a);
		esas2r_kickoff_समयr(a);
	पूर्ण अन्यथा अणु
		esas2r_debug("yikes, unable to claim IRQ");
		esas2r_log(ESAS2R_LOG_CRIT, "could not re-claim IRQ!");
		rez = -ENOMEM;
		जाओ error_निकास;
	पूर्ण

error_निकास:
	esas2r_log_dev(ESAS2R_LOG_CRIT, dev, "esas2r_resume(): %d",
		       rez);
	वापस rez;
पूर्ण

SIMPLE_DEV_PM_OPS(esas2r_pm_ops, esas2r_suspend, esas2r_resume);

bool esas2r_set_degraded_mode(काष्ठा esas2r_adapter *a, अक्षर *error_str)
अणु
	set_bit(AF_DEGRADED_MODE, &a->flags);
	esas2r_log(ESAS2R_LOG_CRIT,
		   "setting adapter to degraded mode: %s\n", error_str);
	वापस false;
पूर्ण

u32 esas2r_get_uncached_size(काष्ठा esas2r_adapter *a)
अणु
	वापस माप(काष्ठा esas2r_sas_nvram)
	       + ALIGN(ESAS2R_DISC_BUF_LEN, 8)
	       + ALIGN(माप(u32), 8) /* outbound list copy poपूर्णांकer */
	       + 8
	       + (num_sg_lists * (u16)sgl_page_size)
	       + ALIGN((num_requests + num_ae_requests + 1 +
			ESAS2R_LIST_EXTRA) *
		       माप(काष्ठा esas2r_inbound_list_source_entry),
		       8)
	       + ALIGN((num_requests + num_ae_requests + 1 +
			ESAS2R_LIST_EXTRA) *
		       माप(काष्ठा atto_vda_ob_rsp), 8)
	       + 256; /* VDA request and buffer align */
पूर्ण

अटल व्योम esas2r_init_pci_cfg_space(काष्ठा esas2r_adapter *a)
अणु
	अगर (pci_is_pcie(a->pcid)) अणु
		u16 devcontrol;

		pcie_capability_पढ़ो_word(a->pcid, PCI_EXP_DEVCTL, &devcontrol);

		अगर ((devcontrol & PCI_EXP_DEVCTL_READRQ) >
		     PCI_EXP_DEVCTL_READRQ_512B) अणु
			esas2r_log(ESAS2R_LOG_INFO,
				   "max read request size > 512B");

			devcontrol &= ~PCI_EXP_DEVCTL_READRQ;
			devcontrol |= PCI_EXP_DEVCTL_READRQ_512B;
			pcie_capability_ग_लिखो_word(a->pcid, PCI_EXP_DEVCTL,
						   devcontrol);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Determine the organization of the uncached data area and
 * finish initializing the adapter काष्ठाure
 */
bool esas2r_init_adapter_काष्ठा(काष्ठा esas2r_adapter *a,
				व्योम **uncached_area)
अणु
	u32 i;
	u8 *high;
	काष्ठा esas2r_inbound_list_source_entry *element;
	काष्ठा esas2r_request *rq;
	काष्ठा esas2r_mem_desc *sgl;

	spin_lock_init(&a->sg_list_lock);
	spin_lock_init(&a->mem_lock);
	spin_lock_init(&a->queue_lock);

	a->targetdb_end = &a->targetdb[ESAS2R_MAX_TARGETS];

	अगर (!alloc_vda_req(a, &a->general_req)) अणु
		esas2r_hdebug(
			"failed to allocate a VDA request for the general req!");
		वापस false;
	पूर्ण

	/* allocate requests क्रम asynchronous events */
	a->first_ae_req =
		kसुस्मृति(num_ae_requests, माप(काष्ठा esas2r_request),
			GFP_KERNEL);

	अगर (a->first_ae_req == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate memory for asynchronous events");
		वापस false;
	पूर्ण

	/* allocate the S/G list memory descriptors */
	a->sg_list_mds = kसुस्मृति(num_sg_lists, माप(काष्ठा esas2r_mem_desc),
				 GFP_KERNEL);

	अगर (a->sg_list_mds == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate memory for s/g list descriptors");
		वापस false;
	पूर्ण

	/* allocate the request table */
	a->req_table =
		kसुस्मृति(num_requests + num_ae_requests + 1,
			माप(काष्ठा esas2r_request *),
			GFP_KERNEL);

	अगर (a->req_table == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate memory for the request table");
		वापस false;
	पूर्ण

	/* initialize PCI configuration space */
	esas2r_init_pci_cfg_space(a);

	/*
	 * the thunder_stream boards all have a serial flash part that has a
	 * dअगरferent base address on the AHB bus.
	 */
	अगर ((a->pcid->subप्रणाली_venकरोr == ATTO_VENDOR_ID)
	    && (a->pcid->subप्रणाली_device & ATTO_SSDID_TBT))
		a->flags2 |= AF2_THUNDERBOLT;

	अगर (test_bit(AF2_THUNDERBOLT, &a->flags2))
		a->flags2 |= AF2_SERIAL_FLASH;

	अगर (a->pcid->subप्रणाली_device == ATTO_TLSH_1068)
		a->flags2 |= AF2_THUNDERLINK;

	/* Uncached Area */
	high = (u8 *)*uncached_area;

	/* initialize the scatter/gather table pages */

	क्रम (i = 0, sgl = a->sg_list_mds; i < num_sg_lists; i++, sgl++) अणु
		sgl->size = sgl_page_size;

		list_add_tail(&sgl->next_desc, &a->मुक्त_sg_list_head);

		अगर (!esas2r_iniपंचांगem_alloc(a, sgl, ESAS2R_SGL_ALIGN)) अणु
			/* Allow the driver to load अगर the minimum count met. */
			अगर (i < NUM_SGL_MIN)
				वापस false;
			अवरोध;
		पूर्ण
	पूर्ण

	/* compute the size of the lists */
	a->list_size = num_requests + ESAS2R_LIST_EXTRA;

	/* allocate the inbound list */
	a->inbound_list_md.size = a->list_size *
				  माप(काष्ठा
					 esas2r_inbound_list_source_entry);

	अगर (!esas2r_iniपंचांगem_alloc(a, &a->inbound_list_md, ESAS2R_LIST_ALIGN)) अणु
		esas2r_hdebug("failed to allocate IB list");
		वापस false;
	पूर्ण

	/* allocate the outbound list */
	a->outbound_list_md.size = a->list_size *
				   माप(काष्ठा atto_vda_ob_rsp);

	अगर (!esas2r_iniपंचांगem_alloc(a, &a->outbound_list_md,
				  ESAS2R_LIST_ALIGN)) अणु
		esas2r_hdebug("failed to allocate IB list");
		वापस false;
	पूर्ण

	/* allocate the NVRAM काष्ठाure */
	a->nvram = (काष्ठा esas2r_sas_nvram *)high;
	high += माप(काष्ठा esas2r_sas_nvram);

	/* allocate the discovery buffer */
	a->disc_buffer = high;
	high += ESAS2R_DISC_BUF_LEN;
	high = PTR_ALIGN(high, 8);

	/* allocate the outbound list copy poपूर्णांकer */
	a->outbound_copy = (u32 अस्थिर *)high;
	high += माप(u32);

	अगर (!test_bit(AF_NVR_VALID, &a->flags))
		esas2r_nvram_set_शेषs(a);

	/* update the caller's uncached memory area poपूर्णांकer */
	*uncached_area = (व्योम *)high;

	/* initialize the allocated memory */
	अगर (test_bit(AF_FIRST_INIT, &a->flags)) अणु
		esas2r_targ_db_initialize(a);

		/* prime parts of the inbound list */
		element =
			(काष्ठा esas2r_inbound_list_source_entry *)a->
			inbound_list_md.
			virt_addr;

		क्रम (i = 0; i < a->list_size; i++) अणु
			element->address = 0;
			element->reserved = 0;
			element->length = cpu_to_le32(HWILSE_INTERFACE_F0
						      | (माप(जोड़
								atto_vda_req)
							 /
							 माप(u32)));
			element++;
		पूर्ण

		/* init the AE requests */
		क्रम (rq = a->first_ae_req, i = 0; i < num_ae_requests; rq++,
		     i++) अणु
			INIT_LIST_HEAD(&rq->req_list);
			अगर (!alloc_vda_req(a, rq)) अणु
				esas2r_hdebug(
					"failed to allocate a VDA request!");
				वापस false;
			पूर्ण

			esas2r_rq_init_request(rq, a);

			/* override the completion function */
			rq->comp_cb = esas2r_ae_complete;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/* This code will verअगरy that the chip is operational. */
bool esas2r_check_adapter(काष्ठा esas2r_adapter *a)
अणु
	u32 startसमय;
	u32 करोorbell;
	u64 ppaddr;
	u32 dw;

	/*
	 * अगर the chip reset detected flag is set, we can bypass a bunch of
	 * stuff.
	 */
	अगर (test_bit(AF_CHPRST_DETECTED, &a->flags))
		जाओ skip_chip_reset;

	/*
	 * BEFORE WE DO ANYTHING, disable the chip पूर्णांकerrupts!  the boot driver
	 * may have left them enabled or we may be recovering from a fault.
	 */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_INT_MASK_OUT, ESAS2R_INT_DIS_MASK);
	esas2r_flush_रेजिस्टर_dword(a, MU_INT_MASK_OUT);

	/*
	 * रुको क्रम the firmware to become पढ़ोy by क्रमcing an पूर्णांकerrupt and
	 * रुकोing क्रम a response.
	 */
	startसमय = jअगरfies_to_msecs(jअगरfies);

	जबतक (true) अणु
		esas2r_क्रमce_पूर्णांकerrupt(a);
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell == 0xFFFFFFFF) अणु
			/*
			 * Give the firmware up to two seconds to enable
			 * रेजिस्टर access after a reset.
			 */
			अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 2000)
				वापस esas2r_set_degraded_mode(a,
								"unable to access registers");
		पूर्ण अन्यथा अगर (करोorbell & DRBL_FORCE_INT) अणु
			u32 ver = (करोorbell & DRBL_FW_VER_MSK);

			/*
			 * This driver supports version 0 and version 1 of
			 * the API
			 */
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);

			अगर (ver == DRBL_FW_VER_0) अणु
				set_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 128;
				a->build_sgl = esas2r_build_sg_list_sge;
			पूर्ण अन्यथा अगर (ver == DRBL_FW_VER_1) अणु
				clear_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 1024;
				a->build_sgl = esas2r_build_sg_list_prd;
			पूर्ण अन्यथा अणु
				वापस esas2r_set_degraded_mode(a,
								"unknown firmware version");
			पूर्ण
			अवरोध;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 180000) अणु
			esas2r_hdebug("FW ready TMO");
			esas2r_bugon();

			वापस esas2r_set_degraded_mode(a,
							"firmware start has timed out");
		पूर्ण
	पूर्ण

	/* purge any asynchronous events since we will repost them later */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN, DRBL_MSG_IFC_DOWN);
	startसमय = jअगरfies_to_msecs(jअगरfies);

	जबतक (true) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell & DRBL_MSG_IFC_DOWN) अणु
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);
			अवरोध;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(50));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 3000) अणु
			esas2r_hdebug("timeout waiting for interface down");
			अवरोध;
		पूर्ण
	पूर्ण
skip_chip_reset:
	/*
	 * first things first, beक्रमe we go changing any of these रेजिस्टरs
	 * disable the communication lists.
	 */
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_IN_LIST_CONFIG);
	dw &= ~MU_ILC_ENABLE;
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_CONFIG, dw);
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_OUT_LIST_CONFIG);
	dw &= ~MU_OLC_ENABLE;
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_CONFIG, dw);

	/* configure the communication list addresses */
	ppaddr = a->inbound_list_md.phys_addr;
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_ADDR_LO,
				    lower_32_bits(ppaddr));
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_ADDR_HI,
				    upper_32_bits(ppaddr));
	ppaddr = a->outbound_list_md.phys_addr;
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_ADDR_LO,
				    lower_32_bits(ppaddr));
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_ADDR_HI,
				    upper_32_bits(ppaddr));
	ppaddr = a->uncached_phys +
		 ((u8 *)a->outbound_copy - a->uncached);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_COPY_PTR_LO,
				    lower_32_bits(ppaddr));
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_COPY_PTR_HI,
				    upper_32_bits(ppaddr));

	/* reset the पढ़ो and ग_लिखो poपूर्णांकers */
	*a->outbound_copy =
		a->last_ग_लिखो =
			a->last_पढ़ो = a->list_size - 1;
	set_bit(AF_COMM_LIST_TOGGLE, &a->flags);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_WRITE, MU_ILW_TOGGLE |
				    a->last_ग_लिखो);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_COPY, MU_OLC_TOGGLE |
				    a->last_ग_लिखो);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_READ, MU_ILR_TOGGLE |
				    a->last_ग_लिखो);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_WRITE,
				    MU_OLW_TOGGLE | a->last_ग_लिखो);

	/* configure the पूर्णांकerface select fields */
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_IN_LIST_IFC_CONFIG);
	dw &= ~(MU_ILIC_LIST | MU_ILIC_DEST);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_IFC_CONFIG,
				    (dw | MU_ILIC_LIST_F0 | MU_ILIC_DEST_DDR));
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_OUT_LIST_IFC_CONFIG);
	dw &= ~(MU_OLIC_LIST | MU_OLIC_SOURCE);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_IFC_CONFIG,
				    (dw | MU_OLIC_LIST_F0 |
				     MU_OLIC_SOURCE_DDR));

	/* finish configuring the communication lists */
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_IN_LIST_CONFIG);
	dw &= ~(MU_ILC_ENTRY_MASK | MU_ILC_NUMBER_MASK);
	dw |= MU_ILC_ENTRY_4_DW | MU_ILC_DYNAMIC_SRC
	      | (a->list_size << MU_ILC_NUMBER_SHIFT);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_IN_LIST_CONFIG, dw);
	dw = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_OUT_LIST_CONFIG);
	dw &= ~(MU_OLC_ENTRY_MASK | MU_OLC_NUMBER_MASK);
	dw |= MU_OLC_ENTRY_4_DW | (a->list_size << MU_OLC_NUMBER_SHIFT);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_CONFIG, dw);

	/*
	 * notअगरy the firmware that we're करोne setting up the communication
	 * list रेजिस्टरs.  रुको here until the firmware is करोne configuring
	 * its lists.  it will संकेत that it is करोne by enabling the lists.
	 */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN, DRBL_MSG_IFC_INIT);
	startसमय = jअगरfies_to_msecs(jअगरfies);

	जबतक (true) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell & DRBL_MSG_IFC_INIT) अणु
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);
			अवरोध;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 3000) अणु
			esas2r_hdebug(
				"timeout waiting for communication list init");
			esas2r_bugon();
			वापस esas2r_set_degraded_mode(a,
							"timeout waiting for communication list init");
		पूर्ण
	पूर्ण

	/*
	 * flag whether the firmware supports the घातer करोwn करोorbell.  we
	 * determine this by पढ़ोing the inbound करोorbell enable mask.
	 */
	करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_IN_ENB);
	अगर (करोorbell & DRBL_POWER_DOWN)
		set_bit(AF2_VDA_POWER_DOWN, &a->flags2);
	अन्यथा
		clear_bit(AF2_VDA_POWER_DOWN, &a->flags2);

	/*
	 * enable निश्चितion of outbound queue and करोorbell पूर्णांकerrupts in the
	 * मुख्य पूर्णांकerrupt cause रेजिस्टर.
	 */
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_OUT_LIST_INT_MASK, MU_OLIS_MASK);
	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT_ENB, DRBL_ENB_MASK);
	वापस true;
पूर्ण

/* Process the initialization message just completed and क्रमmat the next one. */
अटल bool esas2r_क्रमmat_init_msg(काष्ठा esas2r_adapter *a,
				   काष्ठा esas2r_request *rq)
अणु
	u32 msg = a->init_msg;
	काष्ठा atto_vda_cfg_init *ci;

	a->init_msg = 0;

	चयन (msg) अणु
	हाल ESAS2R_INIT_MSG_START:
	हाल ESAS2R_INIT_MSG_REINIT:
	अणु
		esas2r_hdebug("CFG init");
		esas2r_build_cfg_req(a,
				     rq,
				     VDA_CFG_INIT,
				     0,
				     शून्य);
		ci = (काष्ठा atto_vda_cfg_init *)&rq->vrq->cfg.data.init;
		ci->sgl_page_size = cpu_to_le32(sgl_page_size);
		/* firmware पूर्णांकerface overflows in y2106 */
		ci->epoch_समय = cpu_to_le32(kसमय_get_real_seconds());
		rq->flags |= RF_FAILURE_OK;
		a->init_msg = ESAS2R_INIT_MSG_INIT;
		अवरोध;
	पूर्ण

	हाल ESAS2R_INIT_MSG_INIT:
		अगर (rq->req_stat == RS_SUCCESS) अणु
			u32 major;
			u32 minor;
			u16 fw_release;

			a->fw_version = le16_to_cpu(
				rq->func_rsp.cfg_rsp.vda_version);
			a->fw_build = rq->func_rsp.cfg_rsp.fw_build;
			fw_release = le16_to_cpu(
				rq->func_rsp.cfg_rsp.fw_release);
			major = LOBYTE(fw_release);
			minor = HIBYTE(fw_release);
			a->fw_version += (major << 16) + (minor << 24);
		पूर्ण अन्यथा अणु
			esas2r_hdebug("FAILED");
		पूर्ण

		/*
		 * the 2.71 and earlier releases of R6xx firmware did not error
		 * unsupported config requests correctly.
		 */

		अगर ((test_bit(AF2_THUNDERBOLT, &a->flags2))
		    || (be32_to_cpu(a->fw_version) > 0x00524702)) अणु
			esas2r_hdebug("CFG get init");
			esas2r_build_cfg_req(a,
					     rq,
					     VDA_CFG_GET_INIT2,
					     माप(काष्ठा atto_vda_cfg_init),
					     शून्य);

			rq->vrq->cfg.sg_list_offset = दुरत्व(
				काष्ठा atto_vda_cfg_req,
				data.sge);
			rq->vrq->cfg.data.prde.ctl_len =
				cpu_to_le32(माप(काष्ठा atto_vda_cfg_init));
			rq->vrq->cfg.data.prde.address = cpu_to_le64(
				rq->vrq_md->phys_addr +
				माप(जोड़ atto_vda_req));
			rq->flags |= RF_FAILURE_OK;
			a->init_msg = ESAS2R_INIT_MSG_GET_INIT;
			अवरोध;
		पूर्ण
		fallthrough;

	हाल ESAS2R_INIT_MSG_GET_INIT:
		अगर (msg == ESAS2R_INIT_MSG_GET_INIT) अणु
			ci = (काष्ठा atto_vda_cfg_init *)rq->data_buf;
			अगर (rq->req_stat == RS_SUCCESS) अणु
				a->num_tarमाला_लो_backend =
					le32_to_cpu(ci->num_tarमाला_लो_backend);
				a->ioctl_tunnel =
					le32_to_cpu(ci->ioctl_tunnel);
			पूर्ण अन्यथा अणु
				esas2r_hdebug("FAILED");
			पूर्ण
		पूर्ण
		fallthrough;

	शेष:
		rq->req_stat = RS_SUCCESS;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Perक्रमm initialization messages via the request queue.  Messages are
 * perक्रमmed with पूर्णांकerrupts disabled.
 */
bool esas2r_init_msgs(काष्ठा esas2r_adapter *a)
अणु
	bool success = true;
	काष्ठा esas2r_request *rq = &a->general_req;

	esas2r_rq_init_request(rq, a);
	rq->comp_cb = esas2r_dummy_complete;

	अगर (a->init_msg == 0)
		a->init_msg = ESAS2R_INIT_MSG_REINIT;

	जबतक (a->init_msg) अणु
		अगर (esas2r_क्रमmat_init_msg(a, rq)) अणु
			अचिन्हित दीर्घ flags;
			जबतक (true) अणु
				spin_lock_irqsave(&a->queue_lock, flags);
				esas2r_start_vda_request(a, rq);
				spin_unlock_irqrestore(&a->queue_lock, flags);
				esas2r_रुको_request(a, rq);
				अगर (rq->req_stat != RS_PENDING)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (rq->req_stat == RS_SUCCESS
		    || ((rq->flags & RF_FAILURE_OK)
			&& rq->req_stat != RS_TIMEOUT))
			जारी;

		esas2r_log(ESAS2R_LOG_CRIT, "init message %x failed (%x, %x)",
			   a->init_msg, rq->req_stat, rq->flags);
		a->init_msg = ESAS2R_INIT_MSG_START;
		success = false;
		अवरोध;
	पूर्ण

	esas2r_rq_destroy_request(rq, a);
	वापस success;
पूर्ण

/* Initialize the adapter chip */
bool esas2r_init_adapter_hw(काष्ठा esas2r_adapter *a, bool init_poll)
अणु
	bool rslt = false;
	काष्ठा esas2r_request *rq;
	u32 i;

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		जाओ निकास;

	अगर (!test_bit(AF_NVR_VALID, &a->flags)) अणु
		अगर (!esas2r_nvram_पढ़ो_direct(a))
			esas2r_log(ESAS2R_LOG_WARN,
				   "invalid/missing NVRAM parameters");
	पूर्ण

	अगर (!esas2r_init_msgs(a)) अणु
		esas2r_set_degraded_mode(a, "init messages failed");
		जाओ निकास;
	पूर्ण

	/* The firmware is पढ़ोy. */
	clear_bit(AF_DEGRADED_MODE, &a->flags);
	clear_bit(AF_CHPRST_PENDING, &a->flags);

	/* Post all the async event requests */
	क्रम (i = 0, rq = a->first_ae_req; i < num_ae_requests; i++, rq++)
		esas2r_start_ae_request(a, rq);

	अगर (!a->flash_rev[0])
		esas2r_पढ़ो_flash_rev(a);

	अगर (!a->image_type[0])
		esas2r_पढ़ो_image_type(a);

	अगर (a->fw_version == 0)
		a->fw_rev[0] = 0;
	अन्यथा
		प्र_लिखो(a->fw_rev, "%1d.%02d",
			(पूर्णांक)LOBYTE(HIWORD(a->fw_version)),
			(पूर्णांक)HIBYTE(HIWORD(a->fw_version)));

	esas2r_hdebug("firmware revision: %s", a->fw_rev);

	अगर (test_bit(AF_CHPRST_DETECTED, &a->flags)
	    && (test_bit(AF_FIRST_INIT, &a->flags))) अणु
		esas2r_enable_chip_पूर्णांकerrupts(a);
		वापस true;
	पूर्ण

	/* initialize discovery */
	esas2r_disc_initialize(a);

	/*
	 * रुको क्रम the device रुको समय to expire here अगर requested.  this is
	 * usually requested during initial driver load and possibly when
	 * resuming from a low घातer state.  deferred device रुकोing will use
	 * पूर्णांकerrupts.  chip reset recovery always defers device रुकोing to
	 * aव्योम being in a TASKLET too दीर्घ.
	 */
	अगर (init_poll) अणु
		u32 currसमय = a->disc_start_समय;
		u32 nexttick = 100;
		u32 deltaसमय;

		/*
		 * Block Tasklets from getting scheduled and indicate this is
		 * polled discovery.
		 */
		set_bit(AF_TASKLET_SCHEDULED, &a->flags);
		set_bit(AF_DISC_POLLED, &a->flags);

		/*
		 * Temporarily bring the disable count to zero to enable
		 * deferred processing.  Note that the count is alपढ़ोy zero
		 * after the first initialization.
		 */
		अगर (test_bit(AF_FIRST_INIT, &a->flags))
			atomic_dec(&a->disable_cnt);

		जबतक (test_bit(AF_DISC_PENDING, &a->flags)) अणु
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

			/*
			 * Determine the need क्रम a समयr tick based on the
			 * delta समय between this and the last iteration of
			 * this loop.  We करोn't use the असलolute समय because
			 * then we would have to worry about when nexttick
			 * wraps and currसमय hasn't yet.
			 */
			deltaसमय = jअगरfies_to_msecs(jअगरfies) - currसमय;
			currसमय += deltaसमय;

			/*
			 * Process any रुकोing discovery as दीर्घ as the chip is
			 * up.  If a chip reset happens during initial polling,
			 * we have to make sure the समयr tick processes the
			 * करोorbell indicating the firmware is पढ़ोy.
			 */
			अगर (!test_bit(AF_CHPRST_PENDING, &a->flags))
				esas2r_disc_check_क्रम_work(a);

			/* Simulate a समयr tick. */
			अगर (nexttick <= deltaसमय) अणु

				/* Time क्रम a समयr tick */
				nexttick += 100;
				esas2r_समयr_tick(a);
			पूर्ण

			अगर (nexttick > deltaसमय)
				nexttick -= deltaसमय;

			/* Do any deferred processing */
			अगर (esas2r_is_tasklet_pending(a))
				esas2r_करो_tasklet_tasks(a);

		पूर्ण

		अगर (test_bit(AF_FIRST_INIT, &a->flags))
			atomic_inc(&a->disable_cnt);

		clear_bit(AF_DISC_POLLED, &a->flags);
		clear_bit(AF_TASKLET_SCHEDULED, &a->flags);
	पूर्ण


	esas2r_targ_db_report_changes(a);

	/*
	 * For हालs where (a) the initialization messages processing may
	 * handle an पूर्णांकerrupt क्रम a port event and a discovery is रुकोing, but
	 * we are not रुकोing क्रम devices, or (b) the device रुको समय has been
	 * exhausted but there is still discovery pending, start any leftover
	 * discovery in पूर्णांकerrupt driven mode.
	 */
	esas2r_disc_start_रुकोing(a);

	/* Enable chip पूर्णांकerrupts */
	a->पूर्णांक_mask = ESAS2R_INT_STS_MASK;
	esas2r_enable_chip_पूर्णांकerrupts(a);
	esas2r_enable_heartbeat(a);
	rslt = true;

निकास:
	/*
	 * Regardless of whether initialization was successful, certain things
	 * need to get करोne beक्रमe we निकास.
	 */

	अगर (test_bit(AF_CHPRST_DETECTED, &a->flags) &&
	    test_bit(AF_FIRST_INIT, &a->flags)) अणु
		/*
		 * Reinitialization was perक्रमmed during the first
		 * initialization.  Only clear the chip reset flag so the
		 * original device polling is not cancelled.
		 */
		अगर (!rslt)
			clear_bit(AF_CHPRST_PENDING, &a->flags);
	पूर्ण अन्यथा अणु
		/* First initialization or a subsequent re-init is complete. */
		अगर (!rslt) अणु
			clear_bit(AF_CHPRST_PENDING, &a->flags);
			clear_bit(AF_DISC_PENDING, &a->flags);
		पूर्ण


		/* Enable deferred processing after the first initialization. */
		अगर (test_bit(AF_FIRST_INIT, &a->flags)) अणु
			clear_bit(AF_FIRST_INIT, &a->flags);

			अगर (atomic_dec_वापस(&a->disable_cnt) == 0)
				esas2r_करो_deferred_processes(a);
		पूर्ण
	पूर्ण

	वापस rslt;
पूर्ण

व्योम esas2r_reset_adapter(काष्ठा esas2r_adapter *a)
अणु
	set_bit(AF_OS_RESET, &a->flags);
	esas2r_local_reset_adapter(a);
	esas2r_schedule_tasklet(a);
पूर्ण

व्योम esas2r_reset_chip(काष्ठा esas2r_adapter *a)
अणु
	अगर (!esas2r_is_adapter_present(a))
		वापस;

	/*
	 * Beक्रमe we reset the chip, save off the VDA core dump.  The VDA core
	 * dump is located in the upper 512KB of the onchip SRAM.  Make sure
	 * to not overग_लिखो a previous crash that was saved.
	 */
	अगर (test_bit(AF2_COREDUMP_AVAIL, &a->flags2) &&
	    !test_bit(AF2_COREDUMP_SAVED, &a->flags2)) अणु
		esas2r_पढ़ो_mem_block(a,
				      a->fw_coredump_buff,
				      MW_DATA_ADDR_SRAM + 0x80000,
				      ESAS2R_FWCOREDUMP_SZ);

		set_bit(AF2_COREDUMP_SAVED, &a->flags2);
	पूर्ण

	clear_bit(AF2_COREDUMP_AVAIL, &a->flags2);

	/* Reset the chip */
	अगर (a->pcid->revision == MVR_FREY_B2)
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_CTL_STATUS_IN_B2,
					    MU_CTL_IN_FULL_RST2);
	अन्यथा
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_CTL_STATUS_IN,
					    MU_CTL_IN_FULL_RST);


	/* Stall a little जबतक to let the reset condition clear */
	mdelay(10);
पूर्ण

अटल व्योम esas2r_घातer_करोwn_notअगरy_firmware(काष्ठा esas2r_adapter *a)
अणु
	u32 startसमय;
	u32 करोorbell;

	esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN, DRBL_POWER_DOWN);
	startसमय = jअगरfies_to_msecs(jअगरfies);

	जबतक (true) अणु
		करोorbell = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
		अगर (करोorbell & DRBL_POWER_DOWN) अणु
			esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
						    करोorbell);
			अवरोध;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

		अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 30000) अणु
			esas2r_hdebug("Timeout waiting for power down");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Perक्रमm घातer management processing including managing device states, adapter
 * states, पूर्णांकerrupts, and I/O.
 */
व्योम esas2r_घातer_करोwn(काष्ठा esas2r_adapter *a)
अणु
	set_bit(AF_POWER_MGT, &a->flags);
	set_bit(AF_POWER_DOWN, &a->flags);

	अगर (!test_bit(AF_DEGRADED_MODE, &a->flags)) अणु
		u32 startसमय;
		u32 करोorbell;

		/*
		 * We are currently running OK and will be reinitializing later.
		 * increment the disable count to coordinate with
		 * esas2r_init_adapter.  We करोn't have to करो this in degraded
		 * mode since we never enabled पूर्णांकerrupts in the first place.
		 */
		esas2r_disable_chip_पूर्णांकerrupts(a);
		esas2r_disable_heartbeat(a);

		/* रुको क्रम any VDA activity to clear beक्रमe continuing */
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_IN,
					    DRBL_MSG_IFC_DOWN);
		startसमय = jअगरfies_to_msecs(jअगरfies);

		जबतक (true) अणु
			करोorbell =
				esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT);
			अगर (करोorbell & DRBL_MSG_IFC_DOWN) अणु
				esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_DOORBELL_OUT,
							    करोorbell);
				अवरोध;
			पूर्ण

			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

			अगर ((jअगरfies_to_msecs(jअगरfies) - startसमय) > 3000) अणु
				esas2r_hdebug(
					"timeout waiting for interface down");
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * For versions of firmware that support it tell them the driver
		 * is घातering करोwn.
		 */
		अगर (test_bit(AF2_VDA_POWER_DOWN, &a->flags2))
			esas2r_घातer_करोwn_notअगरy_firmware(a);
	पूर्ण

	/* Suspend I/O processing. */
	set_bit(AF_OS_RESET, &a->flags);
	set_bit(AF_DISC_PENDING, &a->flags);
	set_bit(AF_CHPRST_PENDING, &a->flags);

	esas2r_process_adapter_reset(a);

	/* Remove devices now that I/O is cleaned up. */
	a->prev_dev_cnt = esas2r_targ_db_get_tgt_cnt(a);
	esas2r_targ_db_हटाओ_all(a, false);
पूर्ण

/*
 * Perक्रमm घातer management processing including managing device states, adapter
 * states, पूर्णांकerrupts, and I/O.
 */
bool esas2r_घातer_up(काष्ठा esas2r_adapter *a, bool init_poll)
अणु
	bool ret;

	clear_bit(AF_POWER_DOWN, &a->flags);
	esas2r_init_pci_cfg_space(a);
	set_bit(AF_FIRST_INIT, &a->flags);
	atomic_inc(&a->disable_cnt);

	/* reinitialize the adapter */
	ret = esas2r_check_adapter(a);
	अगर (!esas2r_init_adapter_hw(a, init_poll))
		ret = false;

	/* send the reset asynchronous event */
	esas2r_send_reset_ae(a, true);

	/* clear this flag after initialization. */
	clear_bit(AF_POWER_MGT, &a->flags);
	वापस ret;
पूर्ण

bool esas2r_is_adapter_present(काष्ठा esas2r_adapter *a)
अणु
	अगर (test_bit(AF_NOT_PRESENT, &a->flags))
		वापस false;

	अगर (esas2r_पढ़ो_रेजिस्टर_dword(a, MU_DOORBELL_OUT) == 0xFFFFFFFF) अणु
		set_bit(AF_NOT_PRESENT, &a->flags);

		वापस false;
	पूर्ण
	वापस true;
पूर्ण

स्थिर अक्षर *esas2r_get_model_name(काष्ठा esas2r_adapter *a)
अणु
	चयन (a->pcid->subप्रणाली_device) अणु
	हाल ATTO_ESAS_R680:
		वापस "ATTO ExpressSAS R680";

	हाल ATTO_ESAS_R608:
		वापस "ATTO ExpressSAS R608";

	हाल ATTO_ESAS_R60F:
		वापस "ATTO ExpressSAS R60F";

	हाल ATTO_ESAS_R6F0:
		वापस "ATTO ExpressSAS R6F0";

	हाल ATTO_ESAS_R644:
		वापस "ATTO ExpressSAS R644";

	हाल ATTO_ESAS_R648:
		वापस "ATTO ExpressSAS R648";

	हाल ATTO_TSSC_3808:
		वापस "ATTO ThunderStream SC 3808D";

	हाल ATTO_TSSC_3808E:
		वापस "ATTO ThunderStream SC 3808E";

	हाल ATTO_TLSH_1068:
		वापस "ATTO ThunderLink SH 1068";
	पूर्ण

	वापस "ATTO SAS Controller";
पूर्ण

स्थिर अक्षर *esas2r_get_model_name_लघु(काष्ठा esas2r_adapter *a)
अणु
	चयन (a->pcid->subप्रणाली_device) अणु
	हाल ATTO_ESAS_R680:
		वापस "R680";

	हाल ATTO_ESAS_R608:
		वापस "R608";

	हाल ATTO_ESAS_R60F:
		वापस "R60F";

	हाल ATTO_ESAS_R6F0:
		वापस "R6F0";

	हाल ATTO_ESAS_R644:
		वापस "R644";

	हाल ATTO_ESAS_R648:
		वापस "R648";

	हाल ATTO_TSSC_3808:
		वापस "SC 3808D";

	हाल ATTO_TSSC_3808E:
		वापस "SC 3808E";

	हाल ATTO_TLSH_1068:
		वापस "SH 1068";
	पूर्ण

	वापस "unknown";
पूर्ण
