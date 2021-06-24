<शैली गुरु>
/*
 * Linux driver क्रम VMware's para-भवized SCSI HBA.
 *
 * Copyright (C) 2008-2014, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "vmw_pvscsi.h"

#घोषणा PVSCSI_LINUX_DRIVER_DESC "VMware PVSCSI driver"

MODULE_DESCRIPTION(PVSCSI_LINUX_DRIVER_DESC);
MODULE_AUTHOR("VMware, Inc.");
MODULE_LICENSE("GPL");
MODULE_VERSION(PVSCSI_DRIVER_VERSION_STRING);

#घोषणा PVSCSI_DEFAULT_NUM_PAGES_PER_RING	8
#घोषणा PVSCSI_DEFAULT_NUM_PAGES_MSG_RING	1
#घोषणा PVSCSI_DEFAULT_QUEUE_DEPTH		254
#घोषणा SGL_SIZE				PAGE_SIZE

काष्ठा pvscsi_sg_list अणु
	काष्ठा PVSCSISGElement sge[PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT];
पूर्ण;

काष्ठा pvscsi_ctx अणु
	/*
	 * The index of the context in cmd_map serves as the context ID क्रम a
	 * 1-to-1 mapping completions back to requests.
	 */
	काष्ठा scsi_cmnd	*cmd;
	काष्ठा pvscsi_sg_list	*sgl;
	काष्ठा list_head	list;
	dma_addr_t		dataPA;
	dma_addr_t		sensePA;
	dma_addr_t		sglPA;
	काष्ठा completion	*पात_cmp;
पूर्ण;

काष्ठा pvscsi_adapter अणु
	अक्षर				*mmioBase;
	u8				rev;
	bool				use_msg;
	bool				use_req_threshold;

	spinlock_t			hw_lock;

	काष्ठा workqueue_काष्ठा		*workqueue;
	काष्ठा work_काष्ठा		work;

	काष्ठा PVSCSIRingReqDesc	*req_ring;
	अचिन्हित			req_pages;
	अचिन्हित			req_depth;
	dma_addr_t			reqRingPA;

	काष्ठा PVSCSIRingCmpDesc	*cmp_ring;
	अचिन्हित			cmp_pages;
	dma_addr_t			cmpRingPA;

	काष्ठा PVSCSIRingMsgDesc	*msg_ring;
	अचिन्हित			msg_pages;
	dma_addr_t			msgRingPA;

	काष्ठा PVSCSIRingsState		*rings_state;
	dma_addr_t			ringStatePA;

	काष्ठा pci_dev			*dev;
	काष्ठा Scsi_Host		*host;

	काष्ठा list_head		cmd_pool;
	काष्ठा pvscsi_ctx		*cmd_map;
पूर्ण;


/* Command line parameters */
अटल पूर्णांक pvscsi_ring_pages;
अटल पूर्णांक pvscsi_msg_ring_pages = PVSCSI_DEFAULT_NUM_PAGES_MSG_RING;
अटल पूर्णांक pvscsi_cmd_per_lun    = PVSCSI_DEFAULT_QUEUE_DEPTH;
अटल bool pvscsi_disable_msi;
अटल bool pvscsi_disable_msix;
अटल bool pvscsi_use_msg       = true;
अटल bool pvscsi_use_req_threshold = true;

#घोषणा PVSCSI_RW (S_IRUSR | S_IWUSR)

module_param_named(ring_pages, pvscsi_ring_pages, पूर्णांक, PVSCSI_RW);
MODULE_PARM_DESC(ring_pages, "Number of pages per req/cmp ring - (default="
		 __stringअगरy(PVSCSI_DEFAULT_NUM_PAGES_PER_RING)
		 "[up to 16 targets],"
		 __stringअगरy(PVSCSI_SETUP_RINGS_MAX_NUM_PAGES)
		 "[for 16+ targets])");

module_param_named(msg_ring_pages, pvscsi_msg_ring_pages, पूर्णांक, PVSCSI_RW);
MODULE_PARM_DESC(msg_ring_pages, "Number of pages for the msg ring - (default="
		 __stringअगरy(PVSCSI_DEFAULT_NUM_PAGES_MSG_RING) ")");

module_param_named(cmd_per_lun, pvscsi_cmd_per_lun, पूर्णांक, PVSCSI_RW);
MODULE_PARM_DESC(cmd_per_lun, "Maximum commands per lun - (default="
		 __stringअगरy(PVSCSI_DEFAULT_QUEUE_DEPTH) ")");

module_param_named(disable_msi, pvscsi_disable_msi, bool, PVSCSI_RW);
MODULE_PARM_DESC(disable_msi, "Disable MSI use in driver - (default=0)");

module_param_named(disable_msix, pvscsi_disable_msix, bool, PVSCSI_RW);
MODULE_PARM_DESC(disable_msix, "Disable MSI-X use in driver - (default=0)");

module_param_named(use_msg, pvscsi_use_msg, bool, PVSCSI_RW);
MODULE_PARM_DESC(use_msg, "Use msg ring when available - (default=1)");

module_param_named(use_req_threshold, pvscsi_use_req_threshold,
		   bool, PVSCSI_RW);
MODULE_PARM_DESC(use_req_threshold, "Use driver-based request coalescing if configured - (default=1)");

अटल स्थिर काष्ठा pci_device_id pvscsi_pci_tbl[] = अणु
	अणु PCI_VDEVICE(VMWARE, PCI_DEVICE_ID_VMWARE_PVSCSI) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pvscsi_pci_tbl);

अटल काष्ठा device *
pvscsi_dev(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	वापस &(adapter->dev->dev);
पूर्ण

अटल काष्ठा pvscsi_ctx *
pvscsi_find_context(स्थिर काष्ठा pvscsi_adapter *adapter, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा pvscsi_ctx *ctx, *end;

	end = &adapter->cmd_map[adapter->req_depth];
	क्रम (ctx = adapter->cmd_map; ctx < end; ctx++)
		अगर (ctx->cmd == cmd)
			वापस ctx;

	वापस शून्य;
पूर्ण

अटल काष्ठा pvscsi_ctx *
pvscsi_acquire_context(काष्ठा pvscsi_adapter *adapter, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा pvscsi_ctx *ctx;

	अगर (list_empty(&adapter->cmd_pool))
		वापस शून्य;

	ctx = list_first_entry(&adapter->cmd_pool, काष्ठा pvscsi_ctx, list);
	ctx->cmd = cmd;
	list_del(&ctx->list);

	वापस ctx;
पूर्ण

अटल व्योम pvscsi_release_context(काष्ठा pvscsi_adapter *adapter,
				   काष्ठा pvscsi_ctx *ctx)
अणु
	ctx->cmd = शून्य;
	ctx->पात_cmp = शून्य;
	list_add(&ctx->list, &adapter->cmd_pool);
पूर्ण

/*
 * Map a pvscsi_ctx काष्ठा to a context ID field value; we map to a simple
 * non-zero पूर्णांकeger. ctx always poपूर्णांकs to an entry in cmd_map array, hence
 * the वापस value is always >=1.
 */
अटल u64 pvscsi_map_context(स्थिर काष्ठा pvscsi_adapter *adapter,
			      स्थिर काष्ठा pvscsi_ctx *ctx)
अणु
	वापस ctx - adapter->cmd_map + 1;
पूर्ण

अटल काष्ठा pvscsi_ctx *
pvscsi_get_context(स्थिर काष्ठा pvscsi_adapter *adapter, u64 context)
अणु
	वापस &adapter->cmd_map[context - 1];
पूर्ण

अटल व्योम pvscsi_reg_ग_लिखो(स्थिर काष्ठा pvscsi_adapter *adapter,
			     u32 offset, u32 val)
अणु
	ग_लिखोl(val, adapter->mmioBase + offset);
पूर्ण

अटल u32 pvscsi_reg_पढ़ो(स्थिर काष्ठा pvscsi_adapter *adapter, u32 offset)
अणु
	वापस पढ़ोl(adapter->mmioBase + offset);
पूर्ण

अटल u32 pvscsi_पढ़ो_पूर्णांकr_status(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	वापस pvscsi_reg_पढ़ो(adapter, PVSCSI_REG_OFFSET_INTR_STATUS);
पूर्ण

अटल व्योम pvscsi_ग_लिखो_पूर्णांकr_status(स्थिर काष्ठा pvscsi_adapter *adapter,
				     u32 val)
अणु
	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_INTR_STATUS, val);
पूर्ण

अटल व्योम pvscsi_unmask_पूर्णांकr(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	u32 पूर्णांकr_bits;

	पूर्णांकr_bits = PVSCSI_INTR_CMPL_MASK;
	अगर (adapter->use_msg)
		पूर्णांकr_bits |= PVSCSI_INTR_MSG_MASK;

	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_INTR_MASK, पूर्णांकr_bits);
पूर्ण

अटल व्योम pvscsi_mask_पूर्णांकr(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_INTR_MASK, 0);
पूर्ण

अटल व्योम pvscsi_ग_लिखो_cmd_desc(स्थिर काष्ठा pvscsi_adapter *adapter,
				  u32 cmd, स्थिर व्योम *desc, माप_प्रकार len)
अणु
	स्थिर u32 *ptr = desc;
	माप_प्रकार i;

	len /= माप(*ptr);
	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_COMMAND, cmd);
	क्रम (i = 0; i < len; i++)
		pvscsi_reg_ग_लिखो(adapter,
				 PVSCSI_REG_OFFSET_COMMAND_DATA, ptr[i]);
पूर्ण

अटल व्योम pvscsi_पात_cmd(स्थिर काष्ठा pvscsi_adapter *adapter,
			     स्थिर काष्ठा pvscsi_ctx *ctx)
अणु
	काष्ठा PVSCSICmdDescAbortCmd cmd = अणु 0 पूर्ण;

	cmd.target = ctx->cmd->device->id;
	cmd.context = pvscsi_map_context(adapter, ctx);

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_ABORT_CMD, &cmd, माप(cmd));
पूर्ण

अटल व्योम pvscsi_kick_rw_io(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_KICK_RW_IO, 0);
पूर्ण

अटल व्योम pvscsi_process_request_ring(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_KICK_NON_RW_IO, 0);
पूर्ण

अटल पूर्णांक scsi_is_rw(अचिन्हित अक्षर op)
अणु
	वापस op == READ_6  || op == WRITE_6 ||
	       op == READ_10 || op == WRITE_10 ||
	       op == READ_12 || op == WRITE_12 ||
	       op == READ_16 || op == WRITE_16;
पूर्ण

अटल व्योम pvscsi_kick_io(स्थिर काष्ठा pvscsi_adapter *adapter,
			   अचिन्हित अक्षर op)
अणु
	अगर (scsi_is_rw(op)) अणु
		काष्ठा PVSCSIRingsState *s = adapter->rings_state;

		अगर (!adapter->use_req_threshold ||
		    s->reqProdIdx - s->reqConsIdx >= s->reqCallThreshold)
			pvscsi_kick_rw_io(adapter);
	पूर्ण अन्यथा अणु
		pvscsi_process_request_ring(adapter);
	पूर्ण
पूर्ण

अटल व्योम ll_adapter_reset(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	dev_dbg(pvscsi_dev(adapter), "Adapter Reset on %p\n", adapter);

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_ADAPTER_RESET, शून्य, 0);
पूर्ण

अटल व्योम ll_bus_reset(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	dev_dbg(pvscsi_dev(adapter), "Resetting bus on %p\n", adapter);

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_RESET_BUS, शून्य, 0);
पूर्ण

अटल व्योम ll_device_reset(स्थिर काष्ठा pvscsi_adapter *adapter, u32 target)
अणु
	काष्ठा PVSCSICmdDescResetDevice cmd = अणु 0 पूर्ण;

	dev_dbg(pvscsi_dev(adapter), "Resetting device: target=%u\n", target);

	cmd.target = target;

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_RESET_DEVICE,
			      &cmd, माप(cmd));
पूर्ण

अटल व्योम pvscsi_create_sg(काष्ठा pvscsi_ctx *ctx,
			     काष्ठा scatterlist *sg, अचिन्हित count)
अणु
	अचिन्हित i;
	काष्ठा PVSCSISGElement *sge;

	BUG_ON(count > PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT);

	sge = &ctx->sgl->sge[0];
	क्रम (i = 0; i < count; i++, sg = sg_next(sg)) अणु
		sge[i].addr   = sg_dma_address(sg);
		sge[i].length = sg_dma_len(sg);
		sge[i].flags  = 0;
	पूर्ण
पूर्ण

/*
 * Map all data buffers क्रम a command पूर्णांकo PCI space and
 * setup the scatter/gather list अगर needed.
 */
अटल पूर्णांक pvscsi_map_buffers(काष्ठा pvscsi_adapter *adapter,
			      काष्ठा pvscsi_ctx *ctx, काष्ठा scsi_cmnd *cmd,
			      काष्ठा PVSCSIRingReqDesc *e)
अणु
	अचिन्हित count;
	अचिन्हित bufflen = scsi_bufflen(cmd);
	काष्ठा scatterlist *sg;

	e->dataLen = bufflen;
	e->dataAddr = 0;
	अगर (bufflen == 0)
		वापस 0;

	sg = scsi_sglist(cmd);
	count = scsi_sg_count(cmd);
	अगर (count != 0) अणु
		पूर्णांक segs = scsi_dma_map(cmd);

		अगर (segs == -ENOMEM) अणु
			scmd_prपूर्णांकk(KERN_DEBUG, cmd,
				    "vmw_pvscsi: Failed to map cmd sglist for DMA.\n");
			वापस -ENOMEM;
		पूर्ण अन्यथा अगर (segs > 1) अणु
			pvscsi_create_sg(ctx, sg, segs);

			e->flags |= PVSCSI_FLAG_CMD_WITH_SG_LIST;
			ctx->sglPA = dma_map_single(&adapter->dev->dev,
					ctx->sgl, SGL_SIZE, DMA_TO_DEVICE);
			अगर (dma_mapping_error(&adapter->dev->dev, ctx->sglPA)) अणु
				scmd_prपूर्णांकk(KERN_ERR, cmd,
					    "vmw_pvscsi: Failed to map ctx sglist for DMA.\n");
				scsi_dma_unmap(cmd);
				ctx->sglPA = 0;
				वापस -ENOMEM;
			पूर्ण
			e->dataAddr = ctx->sglPA;
		पूर्ण अन्यथा
			e->dataAddr = sg_dma_address(sg);
	पूर्ण अन्यथा अणु
		/*
		 * In हाल there is no S/G list, scsi_sglist poपूर्णांकs
		 * directly to the buffer.
		 */
		ctx->dataPA = dma_map_single(&adapter->dev->dev, sg, bufflen,
					     cmd->sc_data_direction);
		अगर (dma_mapping_error(&adapter->dev->dev, ctx->dataPA)) अणु
			scmd_prपूर्णांकk(KERN_DEBUG, cmd,
				    "vmw_pvscsi: Failed to map direct data buffer for DMA.\n");
			वापस -ENOMEM;
		पूर्ण
		e->dataAddr = ctx->dataPA;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The device incorrectly करोesn't clear the first byte of the sense
 * buffer in some हालs. We have to करो it ourselves.
 * Otherwise we run पूर्णांकo trouble when SWIOTLB is क्रमced.
 */
अटल व्योम pvscsi_patch_sense(काष्ठा scsi_cmnd *cmd)
अणु
	अगर (cmd->sense_buffer)
		cmd->sense_buffer[0] = 0;
पूर्ण

अटल व्योम pvscsi_unmap_buffers(स्थिर काष्ठा pvscsi_adapter *adapter,
				 काष्ठा pvscsi_ctx *ctx)
अणु
	काष्ठा scsi_cmnd *cmd;
	अचिन्हित bufflen;

	cmd = ctx->cmd;
	bufflen = scsi_bufflen(cmd);

	अगर (bufflen != 0) अणु
		अचिन्हित count = scsi_sg_count(cmd);

		अगर (count != 0) अणु
			scsi_dma_unmap(cmd);
			अगर (ctx->sglPA) अणु
				dma_unmap_single(&adapter->dev->dev, ctx->sglPA,
						 SGL_SIZE, DMA_TO_DEVICE);
				ctx->sglPA = 0;
			पूर्ण
		पूर्ण अन्यथा
			dma_unmap_single(&adapter->dev->dev, ctx->dataPA,
					 bufflen, cmd->sc_data_direction);
	पूर्ण
	अगर (cmd->sense_buffer)
		dma_unmap_single(&adapter->dev->dev, ctx->sensePA,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक pvscsi_allocate_rings(काष्ठा pvscsi_adapter *adapter)
अणु
	adapter->rings_state = dma_alloc_coherent(&adapter->dev->dev, PAGE_SIZE,
			&adapter->ringStatePA, GFP_KERNEL);
	अगर (!adapter->rings_state)
		वापस -ENOMEM;

	adapter->req_pages = min(PVSCSI_MAX_NUM_PAGES_REQ_RING,
				 pvscsi_ring_pages);
	adapter->req_depth = adapter->req_pages
					* PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE;
	adapter->req_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->req_pages * PAGE_SIZE, &adapter->reqRingPA,
			GFP_KERNEL);
	अगर (!adapter->req_ring)
		वापस -ENOMEM;

	adapter->cmp_pages = min(PVSCSI_MAX_NUM_PAGES_CMP_RING,
				 pvscsi_ring_pages);
	adapter->cmp_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->cmp_pages * PAGE_SIZE, &adapter->cmpRingPA,
			GFP_KERNEL);
	अगर (!adapter->cmp_ring)
		वापस -ENOMEM;

	BUG_ON(!IS_ALIGNED(adapter->ringStatePA, PAGE_SIZE));
	BUG_ON(!IS_ALIGNED(adapter->reqRingPA, PAGE_SIZE));
	BUG_ON(!IS_ALIGNED(adapter->cmpRingPA, PAGE_SIZE));

	अगर (!adapter->use_msg)
		वापस 0;

	adapter->msg_pages = min(PVSCSI_MAX_NUM_PAGES_MSG_RING,
				 pvscsi_msg_ring_pages);
	adapter->msg_ring = dma_alloc_coherent(&adapter->dev->dev,
			adapter->msg_pages * PAGE_SIZE, &adapter->msgRingPA,
			GFP_KERNEL);
	अगर (!adapter->msg_ring)
		वापस -ENOMEM;
	BUG_ON(!IS_ALIGNED(adapter->msgRingPA, PAGE_SIZE));

	वापस 0;
पूर्ण

अटल व्योम pvscsi_setup_all_rings(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा PVSCSICmdDescSetupRings cmd = अणु 0 पूर्ण;
	dma_addr_t base;
	अचिन्हित i;

	cmd.ringsStatePPN   = adapter->ringStatePA >> PAGE_SHIFT;
	cmd.reqRingNumPages = adapter->req_pages;
	cmd.cmpRingNumPages = adapter->cmp_pages;

	base = adapter->reqRingPA;
	क्रम (i = 0; i < adapter->req_pages; i++) अणु
		cmd.reqRingPPNs[i] = base >> PAGE_SHIFT;
		base += PAGE_SIZE;
	पूर्ण

	base = adapter->cmpRingPA;
	क्रम (i = 0; i < adapter->cmp_pages; i++) अणु
		cmd.cmpRingPPNs[i] = base >> PAGE_SHIFT;
		base += PAGE_SIZE;
	पूर्ण

	स_रखो(adapter->rings_state, 0, PAGE_SIZE);
	स_रखो(adapter->req_ring, 0, adapter->req_pages * PAGE_SIZE);
	स_रखो(adapter->cmp_ring, 0, adapter->cmp_pages * PAGE_SIZE);

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_SETUP_RINGS,
			      &cmd, माप(cmd));

	अगर (adapter->use_msg) अणु
		काष्ठा PVSCSICmdDescSetupMsgRing cmd_msg = अणु 0 पूर्ण;

		cmd_msg.numPages = adapter->msg_pages;

		base = adapter->msgRingPA;
		क्रम (i = 0; i < adapter->msg_pages; i++) अणु
			cmd_msg.ringPPNs[i] = base >> PAGE_SHIFT;
			base += PAGE_SIZE;
		पूर्ण
		स_रखो(adapter->msg_ring, 0, adapter->msg_pages * PAGE_SIZE);

		pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_SETUP_MSG_RING,
				      &cmd_msg, माप(cmd_msg));
	पूर्ण
पूर्ण

अटल पूर्णांक pvscsi_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	अगर (!sdev->tagged_supported)
		qdepth = 1;
	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

/*
 * Pull a completion descriptor off and pass the completion back
 * to the SCSI mid layer.
 */
अटल व्योम pvscsi_complete_request(काष्ठा pvscsi_adapter *adapter,
				    स्थिर काष्ठा PVSCSIRingCmpDesc *e)
अणु
	काष्ठा pvscsi_ctx *ctx;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा completion *पात_cmp;
	u32 btstat = e->hostStatus;
	u32 sdstat = e->scsiStatus;

	ctx = pvscsi_get_context(adapter, e->context);
	cmd = ctx->cmd;
	पात_cmp = ctx->पात_cmp;
	pvscsi_unmap_buffers(adapter, ctx);
	अगर (sdstat != SAM_STAT_CHECK_CONDITION)
		pvscsi_patch_sense(cmd);
	pvscsi_release_context(adapter, ctx);
	अगर (पात_cmp) अणु
		/*
		 * The command was requested to be पातed. Just संकेत that
		 * the request completed and swallow the actual cmd completion
		 * here. The पात handler will post a completion क्रम this
		 * command indicating that it got successfully पातed.
		 */
		complete(पात_cmp);
		वापस;
	पूर्ण

	cmd->result = 0;
	अगर (sdstat != SAM_STAT_GOOD &&
	    (btstat == BTSTAT_SUCCESS ||
	     btstat == BTSTAT_LINKED_COMMAND_COMPLETED ||
	     btstat == BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG)) अणु
		अगर (sdstat == SAM_STAT_COMMAND_TERMINATED) अणु
			cmd->result = (DID_RESET << 16);
		पूर्ण अन्यथा अणु
			cmd->result = (DID_OK << 16) | sdstat;
			अगर (sdstat == SAM_STAT_CHECK_CONDITION &&
			    cmd->sense_buffer)
				cmd->result |= (DRIVER_SENSE << 24);
		पूर्ण
	पूर्ण अन्यथा
		चयन (btstat) अणु
		हाल BTSTAT_SUCCESS:
		हाल BTSTAT_LINKED_COMMAND_COMPLETED:
		हाल BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG:
			/*
			 * Commands like INQUIRY may transfer less data than
			 * requested by the initiator via bufflen. Set residual
			 * count to make upper layer aware of the actual amount
			 * of data वापसed.
			 */
			scsi_set_resid(cmd, scsi_bufflen(cmd) - e->dataLen);
			cmd->result = (DID_OK << 16);
			अवरोध;

		हाल BTSTAT_DATARUN:
		हाल BTSTAT_DATA_UNDERRUN:
			/* Report residual data in underruns */
			scsi_set_resid(cmd, scsi_bufflen(cmd) - e->dataLen);
			cmd->result = (DID_ERROR << 16);
			अवरोध;

		हाल BTSTAT_SELTIMEO:
			/* Our emulation वापसs this क्रम non-connected devs */
			cmd->result = (DID_BAD_TARGET << 16);
			अवरोध;

		हाल BTSTAT_LUNMISMATCH:
		हाल BTSTAT_TAGREJECT:
		हाल BTSTAT_BADMSG:
			cmd->result = (DRIVER_INVALID << 24);
			fallthrough;

		हाल BTSTAT_HAHARDWARE:
		हाल BTSTAT_INVPHASE:
		हाल BTSTAT_HATIMEOUT:
		हाल BTSTAT_NORESPONSE:
		हाल BTSTAT_DISCONNECT:
		हाल BTSTAT_HASOFTWARE:
		हाल BTSTAT_BUSFREE:
		हाल BTSTAT_SENSFAILED:
			cmd->result |= (DID_ERROR << 16);
			अवरोध;

		हाल BTSTAT_SENTRST:
		हाल BTSTAT_RECVRST:
		हाल BTSTAT_BUSRESET:
			cmd->result = (DID_RESET << 16);
			अवरोध;

		हाल BTSTAT_ABORTQUEUE:
			cmd->result = (DID_BUS_BUSY << 16);
			अवरोध;

		हाल BTSTAT_SCSIPARITY:
			cmd->result = (DID_PARITY << 16);
			अवरोध;

		शेष:
			cmd->result = (DID_ERROR << 16);
			scmd_prपूर्णांकk(KERN_DEBUG, cmd,
				    "Unknown completion status: 0x%x\n",
				    btstat);
	पूर्ण

	dev_dbg(&cmd->device->sdev_gendev,
		"cmd=%p %x ctx=%p result=0x%x status=0x%x,%x\n",
		cmd, cmd->cmnd[0], ctx, cmd->result, btstat, sdstat);

	cmd->scsi_करोne(cmd);
पूर्ण

/*
 * barrier usage : Since the PVSCSI device is emulated, there could be हालs
 * where we may want to serialize some accesses between the driver and the
 * emulation layer. We use compiler barriers instead of the more expensive
 * memory barriers because PVSCSI is only supported on X86 which has strong
 * memory access ordering.
 */
अटल व्योम pvscsi_process_completion_ring(काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा PVSCSIRingsState *s = adapter->rings_state;
	काष्ठा PVSCSIRingCmpDesc *ring = adapter->cmp_ring;
	u32 cmp_entries = s->cmpNumEntriesLog2;

	जबतक (s->cmpConsIdx != s->cmpProdIdx) अणु
		काष्ठा PVSCSIRingCmpDesc *e = ring + (s->cmpConsIdx &
						      MASK(cmp_entries));
		/*
		 * This barrier() ensures that *e is not dereferenced जबतक
		 * the device emulation still ग_लिखोs data पूर्णांकo the slot.
		 * Since the device emulation advances s->cmpProdIdx only after
		 * updating the slot we want to check it first.
		 */
		barrier();
		pvscsi_complete_request(adapter, e);
		/*
		 * This barrier() ensures that compiler करोesn't reorder ग_लिखो
		 * to s->cmpConsIdx beक्रमe the पढ़ो of (*e) inside
		 * pvscsi_complete_request. Otherwise, device emulation may
		 * overग_लिखो *e beक्रमe we had a chance to पढ़ो it.
		 */
		barrier();
		s->cmpConsIdx++;
	पूर्ण
पूर्ण

/*
 * Translate a Linux SCSI request पूर्णांकo a request ring entry.
 */
अटल पूर्णांक pvscsi_queue_ring(काष्ठा pvscsi_adapter *adapter,
			     काष्ठा pvscsi_ctx *ctx, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा PVSCSIRingsState *s;
	काष्ठा PVSCSIRingReqDesc *e;
	काष्ठा scsi_device *sdev;
	u32 req_entries;

	s = adapter->rings_state;
	sdev = cmd->device;
	req_entries = s->reqNumEntriesLog2;

	/*
	 * If this condition holds, we might have room on the request ring, but
	 * we might not have room on the completion ring क्रम the response.
	 * However, we have alपढ़ोy ruled out this possibility - we would not
	 * have successfully allocated a context अगर it were true, since we only
	 * have one context per request entry.  Check क्रम it anyway, since it
	 * would be a serious bug.
	 */
	अगर (s->reqProdIdx - s->cmpConsIdx >= 1 << req_entries) अणु
		scmd_prपूर्णांकk(KERN_ERR, cmd, "vmw_pvscsi: "
			    "ring full: reqProdIdx=%d cmpConsIdx=%d\n",
			    s->reqProdIdx, s->cmpConsIdx);
		वापस -1;
	पूर्ण

	e = adapter->req_ring + (s->reqProdIdx & MASK(req_entries));

	e->bus    = sdev->channel;
	e->target = sdev->id;
	स_रखो(e->lun, 0, माप(e->lun));
	e->lun[1] = sdev->lun;

	अगर (cmd->sense_buffer) अणु
		ctx->sensePA = dma_map_single(&adapter->dev->dev,
				cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&adapter->dev->dev, ctx->sensePA)) अणु
			scmd_prपूर्णांकk(KERN_DEBUG, cmd,
				    "vmw_pvscsi: Failed to map sense buffer for DMA.\n");
			ctx->sensePA = 0;
			वापस -ENOMEM;
		पूर्ण
		e->senseAddr = ctx->sensePA;
		e->senseLen = SCSI_SENSE_BUFFERSIZE;
	पूर्ण अन्यथा अणु
		e->senseLen  = 0;
		e->senseAddr = 0;
	पूर्ण
	e->cdbLen   = cmd->cmd_len;
	e->vcpuHपूर्णांक = smp_processor_id();
	स_नकल(e->cdb, cmd->cmnd, e->cdbLen);

	e->tag = SIMPLE_QUEUE_TAG;

	अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
		e->flags = PVSCSI_FLAG_CMD_सूची_TOHOST;
	अन्यथा अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		e->flags = PVSCSI_FLAG_CMD_सूची_TODEVICE;
	अन्यथा अगर (cmd->sc_data_direction == DMA_NONE)
		e->flags = PVSCSI_FLAG_CMD_सूची_NONE;
	अन्यथा
		e->flags = 0;

	अगर (pvscsi_map_buffers(adapter, ctx, cmd, e) != 0) अणु
		अगर (cmd->sense_buffer) अणु
			dma_unmap_single(&adapter->dev->dev, ctx->sensePA,
					 SCSI_SENSE_BUFFERSIZE,
					 DMA_FROM_DEVICE);
			ctx->sensePA = 0;
		पूर्ण
		वापस -ENOMEM;
	पूर्ण

	e->context = pvscsi_map_context(adapter, ctx);

	barrier();

	s->reqProdIdx++;

	वापस 0;
पूर्ण

अटल पूर्णांक pvscsi_queue_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);
	काष्ठा pvscsi_ctx *ctx;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर op;

	spin_lock_irqsave(&adapter->hw_lock, flags);

	ctx = pvscsi_acquire_context(adapter, cmd);
	अगर (!ctx || pvscsi_queue_ring(adapter, ctx, cmd) != 0) अणु
		अगर (ctx)
			pvscsi_release_context(adapter, ctx);
		spin_unlock_irqrestore(&adapter->hw_lock, flags);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	cmd->scsi_करोne = करोne;
	op = cmd->cmnd[0];

	dev_dbg(&cmd->device->sdev_gendev,
		"queued cmd %p, ctx %p, op=%x\n", cmd, ctx, op);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	pvscsi_kick_io(adapter, op);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(pvscsi_queue)

अटल पूर्णांक pvscsi_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा pvscsi_adapter *adapter = shost_priv(cmd->device->host);
	काष्ठा pvscsi_ctx *ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक result = SUCCESS;
	DECLARE_COMPLETION_ONSTACK(पात_cmp);
	पूर्णांक करोne;

	scmd_prपूर्णांकk(KERN_DEBUG, cmd, "task abort on host %u, %p\n",
		    adapter->host->host_no, cmd);

	spin_lock_irqsave(&adapter->hw_lock, flags);

	/*
	 * Poll the completion ring first - we might be trying to पात
	 * a command that is रुकोing to be dispatched in the completion ring.
	 */
	pvscsi_process_completion_ring(adapter);

	/*
	 * If there is no context क्रम the command, it either alपढ़ोy succeeded
	 * or अन्यथा was never properly issued.  Not our problem.
	 */
	ctx = pvscsi_find_context(adapter, cmd);
	अगर (!ctx) अणु
		scmd_prपूर्णांकk(KERN_DEBUG, cmd, "Failed to abort cmd %p\n", cmd);
		जाओ out;
	पूर्ण

	/*
	 * Mark that the command has been requested to be पातed and issue
	 * the पात.
	 */
	ctx->पात_cmp = &पात_cmp;

	pvscsi_पात_cmd(adapter, ctx);
	spin_unlock_irqrestore(&adapter->hw_lock, flags);
	/* Wait क्रम 2 secs क्रम the completion. */
	करोne = रुको_क्रम_completion_समयout(&पात_cmp, msecs_to_jअगरfies(2000));
	spin_lock_irqsave(&adapter->hw_lock, flags);

	अगर (!करोne) अणु
		/*
		 * Failed to पात the command, unmark the fact that it
		 * was requested to be पातed.
		 */
		ctx->पात_cmp = शून्य;
		result = FAILED;
		scmd_prपूर्णांकk(KERN_DEBUG, cmd,
			    "Failed to get completion for aborted cmd %p\n",
			    cmd);
		जाओ out;
	पूर्ण

	/*
	 * Successfully पातed the command.
	 */
	cmd->result = (DID_ABORT << 16);
	cmd->scsi_करोne(cmd);

out:
	spin_unlock_irqrestore(&adapter->hw_lock, flags);
	वापस result;
पूर्ण

/*
 * Abort all outstanding requests.  This is only safe to use अगर the completion
 * ring will never be walked again or the device has been reset, because it
 * destroys the 1-1 mapping between context field passed to emulation and our
 * request काष्ठाure.
 */
अटल व्योम pvscsi_reset_all(काष्ठा pvscsi_adapter *adapter)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < adapter->req_depth; i++) अणु
		काष्ठा pvscsi_ctx *ctx = &adapter->cmd_map[i];
		काष्ठा scsi_cmnd *cmd = ctx->cmd;
		अगर (cmd) अणु
			scmd_prपूर्णांकk(KERN_ERR, cmd,
				    "Forced reset on cmd %p\n", cmd);
			pvscsi_unmap_buffers(adapter, ctx);
			pvscsi_patch_sense(cmd);
			pvscsi_release_context(adapter, ctx);
			cmd->result = (DID_RESET << 16);
			cmd->scsi_करोne(cmd);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pvscsi_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);
	अचिन्हित दीर्घ flags;
	bool use_msg;

	scmd_prपूर्णांकk(KERN_INFO, cmd, "SCSI Host reset\n");

	spin_lock_irqsave(&adapter->hw_lock, flags);

	use_msg = adapter->use_msg;

	अगर (use_msg) अणु
		adapter->use_msg = false;
		spin_unlock_irqrestore(&adapter->hw_lock, flags);

		/*
		 * Now that we know that the ISR won't add more work on the
		 * workqueue we can safely flush any outstanding work.
		 */
		flush_workqueue(adapter->workqueue);
		spin_lock_irqsave(&adapter->hw_lock, flags);
	पूर्ण

	/*
	 * We're going to tear करोwn the entire ring काष्ठाure and set it back
	 * up, so stalling new requests until all completions are flushed and
	 * the rings are back in place.
	 */

	pvscsi_process_request_ring(adapter);

	ll_adapter_reset(adapter);

	/*
	 * Now process any completions.  Note we करो this AFTER adapter reset,
	 * which is strange, but stops races where completions get posted
	 * between processing the ring and issuing the reset.  The backend will
	 * not touch the ring memory after reset, so the immediately pre-reset
	 * completion ring state is still valid.
	 */
	pvscsi_process_completion_ring(adapter);

	pvscsi_reset_all(adapter);
	adapter->use_msg = use_msg;
	pvscsi_setup_all_rings(adapter);
	pvscsi_unmask_पूर्णांकr(adapter);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक pvscsi_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);
	अचिन्हित दीर्घ flags;

	scmd_prपूर्णांकk(KERN_INFO, cmd, "SCSI Bus reset\n");

	/*
	 * We करोn't want to queue new requests क्रम this bus after
	 * flushing all pending requests to emulation, since new
	 * requests could then sneak in during this bus reset phase,
	 * so take the lock now.
	 */
	spin_lock_irqsave(&adapter->hw_lock, flags);

	pvscsi_process_request_ring(adapter);
	ll_bus_reset(adapter);
	pvscsi_process_completion_ring(adapter);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक pvscsi_device_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);
	अचिन्हित दीर्घ flags;

	scmd_prपूर्णांकk(KERN_INFO, cmd, "SCSI device reset on scsi%u:%u\n",
		    host->host_no, cmd->device->id);

	/*
	 * We करोn't want to queue new requests क्रम this device after flushing
	 * all pending requests to emulation, since new requests could then
	 * sneak in during this device reset phase, so take the lock now.
	 */
	spin_lock_irqsave(&adapter->hw_lock, flags);

	pvscsi_process_request_ring(adapter);
	ll_device_reset(adapter, cmd->device->id);
	pvscsi_process_completion_ring(adapter);

	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	वापस SUCCESS;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pvscsi_ढाँचा;

अटल स्थिर अक्षर *pvscsi_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);
	अटल अक्षर buf[256];

	प्र_लिखो(buf, "VMware PVSCSI storage adapter rev %d, req/cmp/msg rings: "
		"%u/%u/%u pages, cmd_per_lun=%u", adapter->rev,
		adapter->req_pages, adapter->cmp_pages, adapter->msg_pages,
		pvscsi_ढाँचा.cmd_per_lun);

	वापस buf;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pvscsi_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "VMware PVSCSI Host Adapter",
	.proc_name			= "vmw_pvscsi",
	.info				= pvscsi_info,
	.queuecommand			= pvscsi_queue,
	.this_id			= -1,
	.sg_tablesize			= PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT,
	.dma_boundary			= अच_पूर्णांक_उच्च,
	.max_sectors			= 0xffff,
	.change_queue_depth		= pvscsi_change_queue_depth,
	.eh_पात_handler		= pvscsi_पात,
	.eh_device_reset_handler	= pvscsi_device_reset,
	.eh_bus_reset_handler		= pvscsi_bus_reset,
	.eh_host_reset_handler		= pvscsi_host_reset,
पूर्ण;

अटल व्योम pvscsi_process_msg(स्थिर काष्ठा pvscsi_adapter *adapter,
			       स्थिर काष्ठा PVSCSIRingMsgDesc *e)
अणु
	काष्ठा PVSCSIRingsState *s = adapter->rings_state;
	काष्ठा Scsi_Host *host = adapter->host;
	काष्ठा scsi_device *sdev;

	prपूर्णांकk(KERN_INFO "vmw_pvscsi: msg type: 0x%x - MSG RING: %u/%u (%u) \n",
	       e->type, s->msgProdIdx, s->msgConsIdx, s->msgNumEntriesLog2);

	BUILD_BUG_ON(PVSCSI_MSG_LAST != 2);

	अगर (e->type == PVSCSI_MSG_DEV_ADDED) अणु
		काष्ठा PVSCSIMsgDescDevStatusChanged *desc;
		desc = (काष्ठा PVSCSIMsgDescDevStatusChanged *)e;

		prपूर्णांकk(KERN_INFO
		       "vmw_pvscsi: msg: device added at scsi%u:%u:%u\n",
		       desc->bus, desc->target, desc->lun[1]);

		अगर (!scsi_host_get(host))
			वापस;

		sdev = scsi_device_lookup(host, desc->bus, desc->target,
					  desc->lun[1]);
		अगर (sdev) अणु
			prपूर्णांकk(KERN_INFO "vmw_pvscsi: device already exists\n");
			scsi_device_put(sdev);
		पूर्ण अन्यथा
			scsi_add_device(adapter->host, desc->bus,
					desc->target, desc->lun[1]);

		scsi_host_put(host);
	पूर्ण अन्यथा अगर (e->type == PVSCSI_MSG_DEV_REMOVED) अणु
		काष्ठा PVSCSIMsgDescDevStatusChanged *desc;
		desc = (काष्ठा PVSCSIMsgDescDevStatusChanged *)e;

		prपूर्णांकk(KERN_INFO
		       "vmw_pvscsi: msg: device removed at scsi%u:%u:%u\n",
		       desc->bus, desc->target, desc->lun[1]);

		अगर (!scsi_host_get(host))
			वापस;

		sdev = scsi_device_lookup(host, desc->bus, desc->target,
					  desc->lun[1]);
		अगर (sdev) अणु
			scsi_हटाओ_device(sdev);
			scsi_device_put(sdev);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO
			       "vmw_pvscsi: failed to lookup scsi%u:%u:%u\n",
			       desc->bus, desc->target, desc->lun[1]);

		scsi_host_put(host);
	पूर्ण
पूर्ण

अटल पूर्णांक pvscsi_msg_pending(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा PVSCSIRingsState *s = adapter->rings_state;

	वापस s->msgProdIdx != s->msgConsIdx;
पूर्ण

अटल व्योम pvscsi_process_msg_ring(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा PVSCSIRingsState *s = adapter->rings_state;
	काष्ठा PVSCSIRingMsgDesc *ring = adapter->msg_ring;
	u32 msg_entries = s->msgNumEntriesLog2;

	जबतक (pvscsi_msg_pending(adapter)) अणु
		काष्ठा PVSCSIRingMsgDesc *e = ring + (s->msgConsIdx &
						      MASK(msg_entries));

		barrier();
		pvscsi_process_msg(adapter, e);
		barrier();
		s->msgConsIdx++;
	पूर्ण
पूर्ण

अटल व्योम pvscsi_msg_workqueue_handler(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा pvscsi_adapter *adapter;

	adapter = container_of(data, काष्ठा pvscsi_adapter, work);

	pvscsi_process_msg_ring(adapter);
पूर्ण

अटल पूर्णांक pvscsi_setup_msg_workqueue(काष्ठा pvscsi_adapter *adapter)
अणु
	अक्षर name[32];

	अगर (!pvscsi_use_msg)
		वापस 0;

	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_COMMAND,
			 PVSCSI_CMD_SETUP_MSG_RING);

	अगर (pvscsi_reg_पढ़ो(adapter, PVSCSI_REG_OFFSET_COMMAND_STATUS) == -1)
		वापस 0;

	snम_लिखो(name, माप(name),
		 "vmw_pvscsi_wq_%u", adapter->host->host_no);

	adapter->workqueue = create_singlethपढ़ो_workqueue(name);
	अगर (!adapter->workqueue) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: failed to create work queue\n");
		वापस 0;
	पूर्ण
	INIT_WORK(&adapter->work, pvscsi_msg_workqueue_handler);

	वापस 1;
पूर्ण

अटल bool pvscsi_setup_req_threshold(काष्ठा pvscsi_adapter *adapter,
				      bool enable)
अणु
	u32 val;

	अगर (!pvscsi_use_req_threshold)
		वापस false;

	pvscsi_reg_ग_लिखो(adapter, PVSCSI_REG_OFFSET_COMMAND,
			 PVSCSI_CMD_SETUP_REQCALLTHRESHOLD);
	val = pvscsi_reg_पढ़ो(adapter, PVSCSI_REG_OFFSET_COMMAND_STATUS);
	अगर (val == -1) अणु
		prपूर्णांकk(KERN_INFO "vmw_pvscsi: device does not support req_threshold\n");
		वापस false;
	पूर्ण अन्यथा अणु
		काष्ठा PVSCSICmdDescSetupReqCall cmd_msg = अणु 0 पूर्ण;
		cmd_msg.enable = enable;
		prपूर्णांकk(KERN_INFO
		       "vmw_pvscsi: %sabling reqCallThreshold\n",
			enable ? "en" : "dis");
		pvscsi_ग_लिखो_cmd_desc(adapter,
				      PVSCSI_CMD_SETUP_REQCALLTHRESHOLD,
				      &cmd_msg, माप(cmd_msg));
		वापस pvscsi_reg_पढ़ो(adapter,
				       PVSCSI_REG_OFFSET_COMMAND_STATUS) != 0;
	पूर्ण
पूर्ण

अटल irqवापस_t pvscsi_isr(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा pvscsi_adapter *adapter = devp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);
	pvscsi_process_completion_ring(adapter);
	अगर (adapter->use_msg && pvscsi_msg_pending(adapter))
		queue_work(adapter->workqueue, &adapter->work);
	spin_unlock_irqrestore(&adapter->hw_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pvscsi_shared_isr(पूर्णांक irq, व्योम *devp)
अणु
	काष्ठा pvscsi_adapter *adapter = devp;
	u32 val = pvscsi_पढ़ो_पूर्णांकr_status(adapter);

	अगर (!(val & PVSCSI_INTR_ALL_SUPPORTED))
		वापस IRQ_NONE;
	pvscsi_ग_लिखो_पूर्णांकr_status(devp, val);
	वापस pvscsi_isr(irq, devp);
पूर्ण

अटल व्योम pvscsi_मुक्त_sgls(स्थिर काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा pvscsi_ctx *ctx = adapter->cmd_map;
	अचिन्हित i;

	क्रम (i = 0; i < adapter->req_depth; ++i, ++ctx)
		मुक्त_pages((अचिन्हित दीर्घ)ctx->sgl, get_order(SGL_SIZE));
पूर्ण

अटल व्योम pvscsi_shutकरोwn_पूर्णांकr(काष्ठा pvscsi_adapter *adapter)
अणु
	मुक्त_irq(pci_irq_vector(adapter->dev, 0), adapter);
	pci_मुक्त_irq_vectors(adapter->dev);
पूर्ण

अटल व्योम pvscsi_release_resources(काष्ठा pvscsi_adapter *adapter)
अणु
	अगर (adapter->workqueue)
		destroy_workqueue(adapter->workqueue);

	अगर (adapter->mmioBase)
		pci_iounmap(adapter->dev, adapter->mmioBase);

	pci_release_regions(adapter->dev);

	अगर (adapter->cmd_map) अणु
		pvscsi_मुक्त_sgls(adapter);
		kमुक्त(adapter->cmd_map);
	पूर्ण

	अगर (adapter->rings_state)
		dma_मुक्त_coherent(&adapter->dev->dev, PAGE_SIZE,
				    adapter->rings_state, adapter->ringStatePA);

	अगर (adapter->req_ring)
		dma_मुक्त_coherent(&adapter->dev->dev,
				    adapter->req_pages * PAGE_SIZE,
				    adapter->req_ring, adapter->reqRingPA);

	अगर (adapter->cmp_ring)
		dma_मुक्त_coherent(&adapter->dev->dev,
				    adapter->cmp_pages * PAGE_SIZE,
				    adapter->cmp_ring, adapter->cmpRingPA);

	अगर (adapter->msg_ring)
		dma_मुक्त_coherent(&adapter->dev->dev,
				    adapter->msg_pages * PAGE_SIZE,
				    adapter->msg_ring, adapter->msgRingPA);
पूर्ण

/*
 * Allocate scatter gather lists.
 *
 * These are अटलally allocated.  Trying to be clever was not worth it.
 *
 * Dynamic allocation can fail, and we can't go deep पूर्णांकo the memory
 * allocator, since we're a SCSI driver, and trying too hard to allocate
 * memory might generate disk I/O.  We also करोn't want to fail disk I/O
 * in that हाल because we can't get an allocation - the I/O could be
 * trying to swap out data to मुक्त memory.  Since that is pathological,
 * just use a अटलally allocated scatter list.
 *
 */
अटल पूर्णांक pvscsi_allocate_sg(काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा pvscsi_ctx *ctx;
	पूर्णांक i;

	ctx = adapter->cmd_map;
	BUILD_BUG_ON(माप(काष्ठा pvscsi_sg_list) > SGL_SIZE);

	क्रम (i = 0; i < adapter->req_depth; ++i, ++ctx) अणु
		ctx->sgl = (व्योम *)__get_मुक्त_pages(GFP_KERNEL,
						    get_order(SGL_SIZE));
		ctx->sglPA = 0;
		BUG_ON(!IS_ALIGNED(((अचिन्हित दीर्घ)ctx->sgl), PAGE_SIZE));
		अगर (!ctx->sgl) अणु
			क्रम (; i >= 0; --i, --ctx) अणु
				मुक्त_pages((अचिन्हित दीर्घ)ctx->sgl,
					   get_order(SGL_SIZE));
				ctx->sgl = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Query the device, fetch the config info and वापस the
 * maximum number of tarमाला_लो on the adapter. In हाल of
 * failure due to any reason वापस शेष i.e. 16.
 */
अटल u32 pvscsi_get_max_tarमाला_लो(काष्ठा pvscsi_adapter *adapter)
अणु
	काष्ठा PVSCSICmdDescConfigCmd cmd;
	काष्ठा PVSCSIConfigPageHeader *header;
	काष्ठा device *dev;
	dma_addr_t configPagePA;
	व्योम *config_page;
	u32 numPhys = 16;

	dev = pvscsi_dev(adapter);
	config_page = dma_alloc_coherent(&adapter->dev->dev, PAGE_SIZE,
			&configPagePA, GFP_KERNEL);
	अगर (!config_page) अणु
		dev_warn(dev, "vmw_pvscsi: failed to allocate memory for config page\n");
		जाओ निकास;
	पूर्ण
	BUG_ON(configPagePA & ~PAGE_MASK);

	/* Fetch config info from the device. */
	cmd.configPageAddress = ((u64)PVSCSI_CONFIG_CONTROLLER_ADDRESS) << 32;
	cmd.configPageNum = PVSCSI_CONFIG_PAGE_CONTROLLER;
	cmd.cmpAddr = configPagePA;
	cmd._pad = 0;

	/*
	 * Mark the completion page header with error values. If the device
	 * completes the command successfully, it sets the status values to
	 * indicate success.
	 */
	header = config_page;
	स_रखो(header, 0, माप *header);
	header->hostStatus = BTSTAT_INVPARAM;
	header->scsiStatus = SDSTAT_CHECK;

	pvscsi_ग_लिखो_cmd_desc(adapter, PVSCSI_CMD_CONFIG, &cmd, माप cmd);

	अगर (header->hostStatus == BTSTAT_SUCCESS &&
	    header->scsiStatus == SDSTAT_GOOD) अणु
		काष्ठा PVSCSIConfigPageController *config;

		config = config_page;
		numPhys = config->numPhys;
	पूर्ण अन्यथा
		dev_warn(dev, "vmw_pvscsi: PVSCSI_CMD_CONFIG failed. hostStatus = 0x%x, scsiStatus = 0x%x\n",
			 header->hostStatus, header->scsiStatus);
	dma_मुक्त_coherent(&adapter->dev->dev, PAGE_SIZE, config_page,
			  configPagePA);
निकास:
	वापस numPhys;
पूर्ण

अटल पूर्णांक pvscsi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित पूर्णांक irq_flag = PCI_IRQ_MSIX | PCI_IRQ_MSI | PCI_IRQ_LEGACY;
	काष्ठा pvscsi_adapter *adapter;
	काष्ठा pvscsi_adapter adapter_temp;
	काष्ठा Scsi_Host *host = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;
	u32 max_id;

	error = -ENODEV;

	अगर (pci_enable_device(pdev))
		वापस error;

	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		prपूर्णांकk(KERN_INFO "vmw_pvscsi: using 64bit dma\n");
	पूर्ण अन्यथा अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_INFO "vmw_pvscsi: using 32bit dma\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: failed to set DMA mask\n");
		जाओ out_disable_device;
	पूर्ण

	/*
	 * Let's use a temp pvscsi_adapter काष्ठा until we find the number of
	 * tarमाला_लो on the adapter, after that we will चयन to the real
	 * allocated काष्ठा.
	 */
	adapter = &adapter_temp;
	स_रखो(adapter, 0, माप(*adapter));
	adapter->dev  = pdev;
	adapter->rev = pdev->revision;

	अगर (pci_request_regions(pdev, "vmw_pvscsi")) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: pci memory selection failed\n");
		जाओ out_disable_device;
	पूर्ण

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		अगर ((pci_resource_flags(pdev, i) & PCI_BASE_ADDRESS_SPACE_IO))
			जारी;

		अगर (pci_resource_len(pdev, i) < PVSCSI_MEM_SPACE_SIZE)
			जारी;

		अवरोध;
	पूर्ण

	अगर (i == DEVICE_COUNT_RESOURCE) अणु
		prपूर्णांकk(KERN_ERR
		       "vmw_pvscsi: adapter has no suitable MMIO region\n");
		जाओ out_release_resources_and_disable;
	पूर्ण

	adapter->mmioBase = pci_iomap(pdev, i, PVSCSI_MEM_SPACE_SIZE);

	अगर (!adapter->mmioBase) अणु
		prपूर्णांकk(KERN_ERR
		       "vmw_pvscsi: can't iomap for BAR %d memsize %lu\n",
		       i, PVSCSI_MEM_SPACE_SIZE);
		जाओ out_release_resources_and_disable;
	पूर्ण

	pci_set_master(pdev);

	/*
	 * Ask the device क्रम max number of tarमाला_लो beक्रमe deciding the
	 * शेष pvscsi_ring_pages value.
	 */
	max_id = pvscsi_get_max_tarमाला_लो(adapter);
	prपूर्णांकk(KERN_INFO "vmw_pvscsi: max_id: %u\n", max_id);

	अगर (pvscsi_ring_pages == 0)
		/*
		 * Set the right शेष value. Up to 16 it is 8, above it is
		 * max.
		 */
		pvscsi_ring_pages = (max_id > 16) ?
			PVSCSI_SETUP_RINGS_MAX_NUM_PAGES :
			PVSCSI_DEFAULT_NUM_PAGES_PER_RING;
	prपूर्णांकk(KERN_INFO
	       "vmw_pvscsi: setting ring_pages to %d\n",
	       pvscsi_ring_pages);

	pvscsi_ढाँचा.can_queue =
		min(PVSCSI_MAX_NUM_PAGES_REQ_RING, pvscsi_ring_pages) *
		PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE;
	pvscsi_ढाँचा.cmd_per_lun =
		min(pvscsi_ढाँचा.can_queue, pvscsi_cmd_per_lun);
	host = scsi_host_alloc(&pvscsi_ढाँचा, माप(काष्ठा pvscsi_adapter));
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: failed to allocate host\n");
		जाओ out_release_resources_and_disable;
	पूर्ण

	/*
	 * Let's use the real pvscsi_adapter काष्ठा here onwards.
	 */
	adapter = shost_priv(host);
	स_रखो(adapter, 0, माप(*adapter));
	adapter->dev  = pdev;
	adapter->host = host;
	/*
	 * Copy back what we alपढ़ोy have to the allocated adapter काष्ठा.
	 */
	adapter->rev = adapter_temp.rev;
	adapter->mmioBase = adapter_temp.mmioBase;

	spin_lock_init(&adapter->hw_lock);
	host->max_channel = 0;
	host->max_lun     = 1;
	host->max_cmd_len = 16;
	host->max_id      = max_id;

	pci_set_drvdata(pdev, host);

	ll_adapter_reset(adapter);

	adapter->use_msg = pvscsi_setup_msg_workqueue(adapter);

	error = pvscsi_allocate_rings(adapter);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: unable to allocate ring memory\n");
		जाओ out_release_resources;
	पूर्ण

	/*
	 * From this poपूर्णांक on we should reset the adapter अगर anything goes
	 * wrong.
	 */
	pvscsi_setup_all_rings(adapter);

	adapter->cmd_map = kसुस्मृति(adapter->req_depth,
				   माप(काष्ठा pvscsi_ctx), GFP_KERNEL);
	अगर (!adapter->cmd_map) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: failed to allocate memory.\n");
		error = -ENOMEM;
		जाओ out_reset_adapter;
	पूर्ण

	INIT_LIST_HEAD(&adapter->cmd_pool);
	क्रम (i = 0; i < adapter->req_depth; i++) अणु
		काष्ठा pvscsi_ctx *ctx = adapter->cmd_map + i;
		list_add(&ctx->list, &adapter->cmd_pool);
	पूर्ण

	error = pvscsi_allocate_sg(adapter);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "vmw_pvscsi: unable to allocate s/g table\n");
		जाओ out_reset_adapter;
	पूर्ण

	अगर (pvscsi_disable_msix)
		irq_flag &= ~PCI_IRQ_MSIX;
	अगर (pvscsi_disable_msi)
		irq_flag &= ~PCI_IRQ_MSI;

	error = pci_alloc_irq_vectors(adapter->dev, 1, 1, irq_flag);
	अगर (error < 0)
		जाओ out_reset_adapter;

	adapter->use_req_threshold = pvscsi_setup_req_threshold(adapter, true);
	prपूर्णांकk(KERN_DEBUG "vmw_pvscsi: driver-based request coalescing %sabled\n",
	       adapter->use_req_threshold ? "en" : "dis");

	अगर (adapter->dev->msix_enabled || adapter->dev->msi_enabled) अणु
		prपूर्णांकk(KERN_INFO "vmw_pvscsi: using MSI%s\n",
			adapter->dev->msix_enabled ? "-X" : "");
		error = request_irq(pci_irq_vector(pdev, 0), pvscsi_isr,
				0, "vmw_pvscsi", adapter);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "vmw_pvscsi: using INTx\n");
		error = request_irq(pci_irq_vector(pdev, 0), pvscsi_shared_isr,
				IRQF_SHARED, "vmw_pvscsi", adapter);
	पूर्ण

	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
		       "vmw_pvscsi: unable to request IRQ: %d\n", error);
		जाओ out_reset_adapter;
	पूर्ण

	error = scsi_add_host(host, &pdev->dev);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
		       "vmw_pvscsi: scsi_add_host failed: %d\n", error);
		जाओ out_reset_adapter;
	पूर्ण

	dev_info(&pdev->dev, "VMware PVSCSI rev %d host #%u\n",
		 adapter->rev, host->host_no);

	pvscsi_unmask_पूर्णांकr(adapter);

	scsi_scan_host(host);

	वापस 0;

out_reset_adapter:
	ll_adapter_reset(adapter);
out_release_resources:
	pvscsi_shutकरोwn_पूर्णांकr(adapter);
	pvscsi_release_resources(adapter);
	scsi_host_put(host);
out_disable_device:
	pci_disable_device(pdev);

	वापस error;

out_release_resources_and_disable:
	pvscsi_shutकरोwn_पूर्णांकr(adapter);
	pvscsi_release_resources(adapter);
	जाओ out_disable_device;
पूर्ण

अटल व्योम __pvscsi_shutकरोwn(काष्ठा pvscsi_adapter *adapter)
अणु
	pvscsi_mask_पूर्णांकr(adapter);

	अगर (adapter->workqueue)
		flush_workqueue(adapter->workqueue);

	pvscsi_shutकरोwn_पूर्णांकr(adapter);

	pvscsi_process_request_ring(adapter);
	pvscsi_process_completion_ring(adapter);
	ll_adapter_reset(adapter);
पूर्ण

अटल व्योम pvscsi_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(dev);
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);

	__pvscsi_shutकरोwn(adapter);
पूर्ण

अटल व्योम pvscsi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	काष्ठा pvscsi_adapter *adapter = shost_priv(host);

	scsi_हटाओ_host(host);

	__pvscsi_shutकरोwn(adapter);
	pvscsi_release_resources(adapter);

	scsi_host_put(host);

	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver pvscsi_pci_driver = अणु
	.name		= "vmw_pvscsi",
	.id_table	= pvscsi_pci_tbl,
	.probe		= pvscsi_probe,
	.हटाओ		= pvscsi_हटाओ,
	.shutकरोwn       = pvscsi_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init pvscsi_init(व्योम)
अणु
	pr_info("%s - version %s\n",
		PVSCSI_LINUX_DRIVER_DESC, PVSCSI_DRIVER_VERSION_STRING);
	वापस pci_रेजिस्टर_driver(&pvscsi_pci_driver);
पूर्ण

अटल व्योम __निकास pvscsi_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pvscsi_pci_driver);
पूर्ण

module_init(pvscsi_init);
module_निकास(pvscsi_निकास);
