<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/mempool.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "snic.h"
#समावेश "snic_fwint.h"

#घोषणा PCI_DEVICE_ID_CISCO_SNIC	0x0046

/* Supported devices by snic module */
अटल काष्ठा pci_device_id snic_id_table[] = अणु
	अणुPCI_DEVICE(0x1137, PCI_DEVICE_ID_CISCO_SNIC) पूर्ण,
	अणु 0, पूर्ण	/* end of table */
पूर्ण;

अचिन्हित पूर्णांक snic_log_level = 0x0;
module_param(snic_log_level, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(snic_log_level, "bitmask for snic logging levels");

#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
अचिन्हित पूर्णांक snic_trace_max_pages = 16;
module_param(snic_trace_max_pages, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(snic_trace_max_pages,
		"Total allocated memory pages for snic trace buffer");

#पूर्ण_अगर
अचिन्हित पूर्णांक snic_max_qdepth = SNIC_DFLT_QUEUE_DEPTH;
module_param(snic_max_qdepth, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(snic_max_qdepth, "Queue depth to report for each LUN");

/*
 * snic_slave_alloc : callback function to SCSI Mid Layer, called on
 * scsi device initialization.
 */
अटल पूर्णांक
snic_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा snic_tgt *tgt = starget_to_tgt(scsi_target(sdev));

	अगर (!tgt || snic_tgt_chkपढ़ोy(tgt))
		वापस -ENXIO;

	वापस 0;
पूर्ण

/*
 * snic_slave_configure : callback function to SCSI Mid Layer, called on
 * scsi device initialization.
 */
अटल पूर्णांक
snic_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा snic *snic = shost_priv(sdev->host);
	u32 qdepth = 0, max_ios = 0;
	पूर्णांक पंचांगo = SNIC_DFLT_CMD_TIMEOUT * HZ;

	/* Set Queue Depth */
	max_ios = snic_max_qdepth;
	qdepth = min_t(u32, max_ios, SNIC_MAX_QUEUE_DEPTH);
	scsi_change_queue_depth(sdev, qdepth);

	अगर (snic->fwinfo.io_पंचांगo > 1)
		पंचांगo = snic->fwinfo.io_पंचांगo * HZ;

	/* FW requires extended समयouts */
	blk_queue_rq_समयout(sdev->request_queue, पंचांगo);

	वापस 0;
पूर्ण

अटल पूर्णांक
snic_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा snic *snic = shost_priv(sdev->host);
	पूर्णांक qsz = 0;

	qsz = min_t(u32, qdepth, SNIC_MAX_QUEUE_DEPTH);
	अगर (qsz < sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_rampकरोwn);
	अन्यथा अगर (qsz > sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_rampup);

	atomic64_set(&snic->s_stats.misc.last_qsz, sdev->queue_depth);

	scsi_change_queue_depth(sdev, qsz);

	वापस sdev->queue_depth;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा snic_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = SNIC_DRV_NAME,
	.queuecommand = snic_queuecommand,
	.eh_पात_handler = snic_पात_cmd,
	.eh_device_reset_handler = snic_device_reset,
	.eh_host_reset_handler = snic_host_reset,
	.slave_alloc = snic_slave_alloc,
	.slave_configure = snic_slave_configure,
	.change_queue_depth = snic_change_queue_depth,
	.this_id = -1,
	.cmd_per_lun = SNIC_DFLT_QUEUE_DEPTH,
	.can_queue = SNIC_MAX_IO_REQ,
	.sg_tablesize = SNIC_MAX_SG_DESC_CNT,
	.max_sectors = 0x800,
	.shost_attrs = snic_attrs,
	.track_queue_depth = 1,
	.cmd_size = माप(काष्ठा snic_पूर्णांकernal_io_state),
	.proc_name = "snic_scsi",
पूर्ण;

/*
 * snic_handle_link_event : Handles link events such as link up/करोwn/error
 */
व्योम
snic_handle_link_event(काष्ठा snic *snic)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&snic->snic_lock, flags);
	अगर (snic->stop_link_events) अणु
		spin_unlock_irqrestore(&snic->snic_lock, flags);

		वापस;
	पूर्ण
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	queue_work(snic_glob->event_q, &snic->link_work);
पूर्ण /* end of snic_handle_link_event */

/*
 * snic_notअगरy_set : sets notअगरication area
 * This notअगरication area is to receive events from fw
 * Note: snic supports only MSIX पूर्णांकerrupts, in which we can just call
 *  svnic_dev_notअगरy_set directly
 */
अटल पूर्णांक
snic_notअगरy_set(काष्ठा snic *snic)
अणु
	पूर्णांक ret = 0;
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;

	पूर्णांकr_mode = svnic_dev_get_पूर्णांकr_mode(snic->vdev);

	अगर (पूर्णांकr_mode == VNIC_DEV_INTR_MODE_MSIX) अणु
		ret = svnic_dev_notअगरy_set(snic->vdev, SNIC_MSIX_ERR_NOTIFY);
	पूर्ण अन्यथा अणु
		SNIC_HOST_ERR(snic->shost,
			      "Interrupt mode should be setup before devcmd notify set %d\n",
			      पूर्णांकr_mode);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण /* end of snic_notअगरy_set */

/*
 * snic_dev_रुको : polls vnic खोलो status.
 */
अटल पूर्णांक
snic_dev_रुको(काष्ठा vnic_dev *vdev,
		पूर्णांक (*start)(काष्ठा vnic_dev *, पूर्णांक),
		पूर्णांक (*finished)(काष्ठा vnic_dev *, पूर्णांक *),
		पूर्णांक arg)
अणु
	अचिन्हित दीर्घ समय;
	पूर्णांक ret, करोne;
	पूर्णांक retry_cnt = 0;

	ret = start(vdev, arg);
	अगर (ret)
		वापस ret;

	/*
	 * Wait क्रम func to complete...2 seconds max.
	 *
	 * Someबार schedule_समयout_unपूर्णांकerruptible take दीर्घ	समय
	 * to wakeup, which results skipping retry. The retry counter
	 * ensures to retry at least two बार.
	 */
	समय = jअगरfies + (HZ * 2);
	करो अणु
		ret = finished(vdev, &करोne);
		अगर (ret)
			वापस ret;

		अगर (करोne)
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(HZ/10);
		++retry_cnt;
	पूर्ण जबतक (समय_after(समय, jअगरfies) || (retry_cnt < 3));

	वापस -ETIMEDOUT;
पूर्ण /* end of snic_dev_रुको */

/*
 * snic_cleanup: called by snic_हटाओ
 * Stops the snic device, masks all पूर्णांकerrupts, Completed CQ entries are
 * drained. Posted WQ/RQ/Copy-WQ entries are cleanup
 */
अटल पूर्णांक
snic_cleanup(काष्ठा snic *snic)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	svnic_dev_disable(snic->vdev);
	क्रम (i = 0; i < snic->पूर्णांकr_count; i++)
		svnic_पूर्णांकr_mask(&snic->पूर्णांकr[i]);

	क्रम (i = 0; i < snic->wq_count; i++) अणु
		ret = svnic_wq_disable(&snic->wq[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Clean up completed IOs */
	snic_fwcq_cmpl_handler(snic, -1);

	snic_wq_cmpl_handler(snic, -1);

	/* Clean up the IOs that have not completed */
	क्रम (i = 0; i < snic->wq_count; i++)
		svnic_wq_clean(&snic->wq[i], snic_मुक्त_wq_buf);

	क्रम (i = 0; i < snic->cq_count; i++)
		svnic_cq_clean(&snic->cq[i]);

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++)
		svnic_पूर्णांकr_clean(&snic->पूर्णांकr[i]);

	/* Cleanup snic specअगरic requests */
	snic_मुक्त_all_untagged_reqs(snic);

	/* Cleanup Pending SCSI commands */
	snic_shutकरोwn_scsi_cleanup(snic);

	क्रम (i = 0; i < SNIC_REQ_MAX_CACHES; i++)
		mempool_destroy(snic->req_pool[i]);

	वापस 0;
पूर्ण /* end of snic_cleanup */


अटल व्योम
snic_iounmap(काष्ठा snic *snic)
अणु
	अगर (snic->bar0.vaddr)
		iounmap(snic->bar0.vaddr);
पूर्ण

/*
 * snic_vdev_खोलो_करोne : polls क्रम svnic_dev_खोलो cmd completion.
 */
अटल पूर्णांक
snic_vdev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne)
अणु
	काष्ठा snic *snic = svnic_dev_priv(vdev);
	पूर्णांक ret;
	पूर्णांक nretries = 5;

	करो अणु
		ret = svnic_dev_खोलो_करोne(vdev, करोne);
		अगर (ret == 0)
			अवरोध;

		SNIC_HOST_INFO(snic->shost, "VNIC_DEV_OPEN Timedout.\n");
	पूर्ण जबतक (nretries--);

	वापस ret;
पूर्ण /* end of snic_vdev_खोलो_करोne */

/*
 * snic_add_host : रेजिस्टरs scsi host with ML
 */
अटल पूर्णांक
snic_add_host(काष्ठा Scsi_Host *shost, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret = 0;

	ret = scsi_add_host(shost, &pdev->dev);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "snic: scsi_add_host failed. %d\n",
			      ret);

		वापस ret;
	पूर्ण

	SNIC_BUG_ON(shost->work_q != शून्य);
	snम_लिखो(shost->work_q_name, माप(shost->work_q_name), "scsi_wq_%d",
		 shost->host_no);
	shost->work_q = create_singlethपढ़ो_workqueue(shost->work_q_name);
	अगर (!shost->work_q) अणु
		SNIC_HOST_ERR(shost, "Failed to Create ScsiHost wq.\n");

		ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण /* end of snic_add_host */

अटल व्योम
snic_del_host(काष्ठा Scsi_Host *shost)
अणु
	अगर (!shost->work_q)
		वापस;

	destroy_workqueue(shost->work_q);
	shost->work_q = शून्य;
	scsi_हटाओ_host(shost);
पूर्ण

पूर्णांक
snic_get_state(काष्ठा snic *snic)
अणु
	वापस atomic_पढ़ो(&snic->state);
पूर्ण

व्योम
snic_set_state(काष्ठा snic *snic, क्रमागत snic_state state)
अणु
	SNIC_HOST_INFO(snic->shost, "snic state change from %s to %s\n",
		       snic_state_to_str(snic_get_state(snic)),
		       snic_state_to_str(state));

	atomic_set(&snic->state, state);
पूर्ण

/*
 * snic_probe : Initialize the snic पूर्णांकerface.
 */
अटल पूर्णांक
snic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा snic *snic;
	mempool_t *pool;
	अचिन्हित दीर्घ flags;
	u32 max_ios = 0;
	पूर्णांक ret, i;

	/* Device Inक्रमmation */
	SNIC_INFO("snic device %4x:%4x:%4x:%4x: ",
		  pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
		  pdev->subप्रणाली_device);

	SNIC_INFO("snic device bus %x: slot %x: fn %x\n",
		  pdev->bus->number, PCI_SLOT(pdev->devfn),
		  PCI_FUNC(pdev->devfn));

	/*
	 * Allocate SCSI Host and setup association between host, and snic
	 */
	shost = scsi_host_alloc(&snic_host_ढाँचा, माप(काष्ठा snic));
	अगर (!shost) अणु
		SNIC_ERR("Unable to alloc scsi_host\n");
		ret = -ENOMEM;

		जाओ prob_end;
	पूर्ण
	snic = shost_priv(shost);
	snic->shost = shost;

	snम_लिखो(snic->name, माप(snic->name) - 1, "%s%d", SNIC_DRV_NAME,
		 shost->host_no);

	SNIC_HOST_INFO(shost,
		       "snic%d = %p shost = %p device bus %x: slot %x: fn %x\n",
		       shost->host_no, snic, shost, pdev->bus->number,
		       PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));
#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	/* Per snic debugfs init */
	snic_stats_debugfs_init(snic);
#पूर्ण_अगर

	/* Setup PCI Resources */
	pci_set_drvdata(pdev, snic);
	snic->pdev = pdev;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Cannot enable PCI Resources, aborting : %d\n",
			      ret);

		जाओ err_मुक्त_snic;
	पूर्ण

	ret = pci_request_regions(pdev, SNIC_DRV_NAME);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Cannot obtain PCI Resources, aborting : %d\n",
			      ret);

		जाओ err_pci_disable;
	पूर्ण

	pci_set_master(pdev);

	/*
	 * Query PCI Controller on प्रणाली क्रम DMA addressing
	 * limitation क्रम the device. Try 43-bit first, and
	 * fail to 32-bit.
	 */
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(43));
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			SNIC_HOST_ERR(shost,
				      "No Usable DMA Configuration, aborting %d\n",
				      ret);
			जाओ err_rel_regions;
		पूर्ण
	पूर्ण

	/* Map vNIC resources from BAR0 */
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		SNIC_HOST_ERR(shost, "BAR0 not memory mappable aborting.\n");

		ret = -ENODEV;
		जाओ err_rel_regions;
	पूर्ण

	snic->bar0.vaddr = pci_iomap(pdev, 0, 0);
	अगर (!snic->bar0.vaddr) अणु
		SNIC_HOST_ERR(shost,
			      "Cannot memory map BAR0 res hdr aborting.\n");

		ret = -ENODEV;
		जाओ err_rel_regions;
	पूर्ण

	snic->bar0.bus_addr = pci_resource_start(pdev, 0);
	snic->bar0.len = pci_resource_len(pdev, 0);
	SNIC_BUG_ON(snic->bar0.bus_addr == 0);

	/* Devcmd2 Resource Allocation and Initialization */
	snic->vdev = svnic_dev_alloc_discover(शून्य, snic, pdev, &snic->bar0, 1);
	अगर (!snic->vdev) अणु
		SNIC_HOST_ERR(shost, "vNIC Resource Discovery Failed.\n");

		ret = -ENODEV;
		जाओ err_iounmap;
	पूर्ण

	ret = svnic_dev_cmd_init(snic->vdev, 0);
	अगर (ret) अणु
		SNIC_HOST_INFO(shost, "Devcmd2 Init Failed. err = %d\n", ret);

		जाओ err_vnic_unreg;
	पूर्ण

	ret = snic_dev_रुको(snic->vdev, svnic_dev_खोलो, snic_vdev_खोलो_करोne, 0);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "vNIC dev open failed, aborting. %d\n",
			      ret);

		जाओ err_vnic_unreg;
	पूर्ण

	ret = svnic_dev_init(snic->vdev, 0);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "vNIC dev init failed. aborting. %d\n",
			      ret);

		जाओ err_dev_बंद;
	पूर्ण

	/* Get vNIC inक्रमmation */
	ret = snic_get_vnic_config(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Get vNIC configuration failed, aborting. %d\n",
			      ret);

		जाओ err_dev_बंद;
	पूर्ण

	/* Configure Maximum Outstanding IO reqs */
	max_ios = snic->config.io_throttle_count;
	अगर (max_ios != SNIC_UCSM_DFLT_THROTTLE_CNT_BLD)
		shost->can_queue = min_t(u32, SNIC_MAX_IO_REQ,
					 max_t(u32, SNIC_MIN_IO_REQ, max_ios));

	snic->max_tag_id = shost->can_queue;

	shost->max_lun = snic->config.luns_per_tgt;
	shost->max_id = SNIC_MAX_TARGET;

	shost->max_cmd_len = MAX_COMMAND_SIZE; /*defined in scsi_cmnd.h*/

	snic_get_res_counts(snic);

	/*
	 * Assumption: Only MSIx is supported
	 */
	ret = snic_set_पूर्णांकr_mode(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Failed to set intr mode aborting. %d\n",
			      ret);

		जाओ err_dev_बंद;
	पूर्ण

	ret = snic_alloc_vnic_res(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Failed to alloc vNIC resources aborting. %d\n",
			      ret);

		जाओ err_clear_पूर्णांकr;
	पूर्ण

	/* Initialize specअगरic lists */
	INIT_LIST_HEAD(&snic->list);

	/*
	 * spl_cmd_list क्रम मुख्यtaining snic specअगरic cmds
	 * such as EXCH_VER_REQ, REPORT_TARGETS etc
	 */
	INIT_LIST_HEAD(&snic->spl_cmd_list);
	spin_lock_init(&snic->spl_cmd_lock);

	/* initialize all snic locks */
	spin_lock_init(&snic->snic_lock);

	क्रम (i = 0; i < SNIC_WQ_MAX; i++)
		spin_lock_init(&snic->wq_lock[i]);

	क्रम (i = 0; i < SNIC_IO_LOCKS; i++)
		spin_lock_init(&snic->io_req_lock[i]);

	pool = mempool_create_slab_pool(2,
				snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL]);
	अगर (!pool) अणु
		SNIC_HOST_ERR(shost, "dflt sgl pool creation failed\n");

		ret = -ENOMEM;
		जाओ err_मुक्त_res;
	पूर्ण

	snic->req_pool[SNIC_REQ_CACHE_DFLT_SGL] = pool;

	pool = mempool_create_slab_pool(2,
				snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL]);
	अगर (!pool) अणु
		SNIC_HOST_ERR(shost, "max sgl pool creation failed\n");

		ret = -ENOMEM;
		जाओ err_मुक्त_dflt_sgl_pool;
	पूर्ण

	snic->req_pool[SNIC_REQ_CACHE_MAX_SGL] = pool;

	pool = mempool_create_slab_pool(2,
				snic_glob->req_cache[SNIC_REQ_TM_CACHE]);
	अगर (!pool) अणु
		SNIC_HOST_ERR(shost, "snic tmreq info pool creation failed.\n");

		ret = -ENOMEM;
		जाओ err_मुक्त_max_sgl_pool;
	पूर्ण

	snic->req_pool[SNIC_REQ_TM_CACHE] = pool;

	/* Initialize snic state */
	atomic_set(&snic->state, SNIC_INIT);

	atomic_set(&snic->ios_inflight, 0);

	/* Setup notअगरication buffer area */
	ret = snic_notअगरy_set(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Failed to alloc notify buffer aborting. %d\n",
			      ret);

		जाओ err_मुक्त_पंचांगreq_pool;
	पूर्ण

	spin_lock_irqsave(&snic_glob->snic_list_lock, flags);
	list_add_tail(&snic->list, &snic_glob->snic_list);
	spin_unlock_irqrestore(&snic_glob->snic_list_lock, flags);

	snic_disc_init(&snic->disc);
	INIT_WORK(&snic->tgt_work, snic_handle_tgt_disc);
	INIT_WORK(&snic->disc_work, snic_handle_disc);
	INIT_WORK(&snic->link_work, snic_handle_link);

	/* Enable all queues */
	क्रम (i = 0; i < snic->wq_count; i++)
		svnic_wq_enable(&snic->wq[i]);

	ret = svnic_dev_enable_रुको(snic->vdev);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "vNIC dev enable failed w/ error %d\n",
			      ret);

		जाओ err_vdev_enable;
	पूर्ण

	ret = snic_request_पूर्णांकr(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost, "Unable to request irq. %d\n", ret);

		जाओ err_req_पूर्णांकr;
	पूर्ण

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++)
		svnic_पूर्णांकr_unmask(&snic->पूर्णांकr[i]);

	/* Get snic params */
	ret = snic_get_conf(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Failed to get snic io config from FW w err %d\n",
			      ret);

		जाओ err_get_conf;
	पूर्ण

	/*
	 * Initialization करोne with PCI प्रणाली, hardware, firmware.
	 * Add shost to SCSI
	 */
	ret = snic_add_host(shost, pdev);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost,
			      "Adding scsi host Failed ... exiting. %d\n",
			      ret);

		जाओ err_get_conf;
	पूर्ण

	snic_set_state(snic, SNIC_ONLINE);

	ret = snic_disc_start(snic);
	अगर (ret) अणु
		SNIC_HOST_ERR(shost, "snic_probe:Discovery Failed w err = %d\n",
			      ret);

		जाओ err_get_conf;
	पूर्ण

	SNIC_HOST_INFO(shost, "SNIC Device Probe Successful.\n");

	वापस 0;

err_get_conf:
	snic_मुक्त_all_untagged_reqs(snic);

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++)
		svnic_पूर्णांकr_mask(&snic->पूर्णांकr[i]);

	snic_मुक्त_पूर्णांकr(snic);

err_req_पूर्णांकr:
	svnic_dev_disable(snic->vdev);

err_vdev_enable:
	svnic_dev_notअगरy_unset(snic->vdev);

	क्रम (i = 0; i < snic->wq_count; i++) अणु
		पूर्णांक rc = 0;

		rc = svnic_wq_disable(&snic->wq[i]);
		अगर (rc) अणु
			SNIC_HOST_ERR(shost,
				      "WQ Disable Failed w/ err = %d\n", rc);

			 अवरोध;
		पूर्ण
	पूर्ण
	snic_del_host(snic->shost);

err_मुक्त_पंचांगreq_pool:
	mempool_destroy(snic->req_pool[SNIC_REQ_TM_CACHE]);

err_मुक्त_max_sgl_pool:
	mempool_destroy(snic->req_pool[SNIC_REQ_CACHE_MAX_SGL]);

err_मुक्त_dflt_sgl_pool:
	mempool_destroy(snic->req_pool[SNIC_REQ_CACHE_DFLT_SGL]);

err_मुक्त_res:
	snic_मुक्त_vnic_res(snic);

err_clear_पूर्णांकr:
	snic_clear_पूर्णांकr_mode(snic);

err_dev_बंद:
	svnic_dev_बंद(snic->vdev);

err_vnic_unreg:
	svnic_dev_unरेजिस्टर(snic->vdev);

err_iounmap:
	snic_iounmap(snic);

err_rel_regions:
	pci_release_regions(pdev);

err_pci_disable:
	pci_disable_device(pdev);

err_मुक्त_snic:
#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	snic_stats_debugfs_हटाओ(snic);
#पूर्ण_अगर
	scsi_host_put(shost);
	pci_set_drvdata(pdev, शून्य);

prob_end:
	SNIC_INFO("sNIC device : bus %d: slot %d: fn %d Registration Failed.\n",
		  pdev->bus->number, PCI_SLOT(pdev->devfn),
		  PCI_FUNC(pdev->devfn));

	वापस ret;
पूर्ण /* end of snic_probe */


/*
 * snic_हटाओ : invoked on unbinding the पूर्णांकerface to cleanup the
 * resources allocated in snic_probe on initialization.
 */
अटल व्योम
snic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा snic *snic = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	अगर (!snic) अणु
		SNIC_INFO("sNIC dev: bus %d slot %d fn %d snic inst is null.\n",
			  pdev->bus->number, PCI_SLOT(pdev->devfn),
			  PCI_FUNC(pdev->devfn));

		वापस;
	पूर्ण

	/*
	 * Mark state so that the workqueue thपढ़ो stops क्रमwarding
	 * received frames and link events. ISR and other thपढ़ोs
	 * that can queue work items will also stop creating work
	 * items on the snic workqueue
	 */
	snic_set_state(snic, SNIC_OFFLINE);
	spin_lock_irqsave(&snic->snic_lock, flags);
	snic->stop_link_events = 1;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	flush_workqueue(snic_glob->event_q);
	snic_disc_term(snic);

	spin_lock_irqsave(&snic->snic_lock, flags);
	snic->in_हटाओ = 1;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	/*
	 * This stops the snic device, masks all पूर्णांकerrupts, Completed
	 * CQ entries are drained. Posted WQ/RQ/Copy-WQ entries are
	 * cleanup
	 */
	snic_cleanup(snic);

	spin_lock_irqsave(&snic_glob->snic_list_lock, flags);
	list_del(&snic->list);
	spin_unlock_irqrestore(&snic_glob->snic_list_lock, flags);

	snic_tgt_del_all(snic);
#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	snic_stats_debugfs_हटाओ(snic);
#पूर्ण_अगर
	snic_del_host(snic->shost);

	svnic_dev_notअगरy_unset(snic->vdev);
	snic_मुक्त_पूर्णांकr(snic);
	snic_मुक्त_vnic_res(snic);
	snic_clear_पूर्णांकr_mode(snic);
	svnic_dev_बंद(snic->vdev);
	svnic_dev_unरेजिस्टर(snic->vdev);
	snic_iounmap(snic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);

	/* this मुक्तs Scsi_Host and snic memory (continuous chunk) */
	scsi_host_put(snic->shost);
पूर्ण /* end of snic_हटाओ */


काष्ठा snic_global *snic_glob;

/*
 * snic_global_data_init: Initialize SNIC Global Data
 * Notes: All the global lists, variables should be part of global data
 * this helps in debugging.
 */
अटल पूर्णांक
snic_global_data_init(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा kmem_cache *cachep;
	sमाप_प्रकार len = 0;

	snic_glob = kzalloc(माप(*snic_glob), GFP_KERNEL);

	अगर (!snic_glob) अणु
		SNIC_ERR("Failed to allocate Global Context.\n");

		ret = -ENOMEM;
		जाओ gdi_end;
	पूर्ण

#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	/* Debugfs related Initialization */
	/* Create debugfs entries क्रम snic */
	snic_debugfs_init();

	/* Trace related Initialization */
	/* Allocate memory क्रम trace buffer */
	ret = snic_trc_init();
	अगर (ret < 0) अणु
		SNIC_ERR("Trace buffer init failed, SNIC tracing disabled\n");
		snic_trc_मुक्त();
		/* जारी even अगर it fails */
	पूर्ण

#पूर्ण_अगर
	INIT_LIST_HEAD(&snic_glob->snic_list);
	spin_lock_init(&snic_glob->snic_list_lock);

	/* Create a cache क्रम allocation of snic_host_req+शेष size ESGLs */
	len = माप(काष्ठा snic_req_info);
	len += माप(काष्ठा snic_host_req) + माप(काष्ठा snic_dflt_sgl);
	cachep = kmem_cache_create("snic_req_dfltsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!cachep) अणु
		SNIC_ERR("Failed to create snic default sgl slab\n");
		ret = -ENOMEM;

		जाओ err_dflt_req_slab;
	पूर्ण
	snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL] = cachep;

	/* Create a cache क्रम allocation of max size Extended SGLs */
	len = माप(काष्ठा snic_req_info);
	len += माप(काष्ठा snic_host_req) + माप(काष्ठा snic_max_sgl);
	cachep = kmem_cache_create("snic_req_maxsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!cachep) अणु
		SNIC_ERR("Failed to create snic max sgl slab\n");
		ret = -ENOMEM;

		जाओ err_max_req_slab;
	पूर्ण
	snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL] = cachep;

	len = माप(काष्ठा snic_host_req);
	cachep = kmem_cache_create("snic_req_maxsgl", len, SNIC_SG_DESC_ALIGN,
				   SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!cachep) अणु
		SNIC_ERR("Failed to create snic tm req slab\n");
		ret = -ENOMEM;

		जाओ err_पंचांगreq_slab;
	पूर्ण
	snic_glob->req_cache[SNIC_REQ_TM_CACHE] = cachep;

	/* snic_event queue */
	snic_glob->event_q = create_singlethपढ़ो_workqueue("snic_event_wq");
	अगर (!snic_glob->event_q) अणु
		SNIC_ERR("snic event queue create failed\n");
		ret = -ENOMEM;

		जाओ err_eventq;
	पूर्ण

	वापस ret;

err_eventq:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_TM_CACHE]);

err_पंचांगreq_slab:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL]);

err_max_req_slab:
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL]);

err_dflt_req_slab:
#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	snic_trc_मुक्त();
	snic_debugfs_term();
#पूर्ण_अगर
	kमुक्त(snic_glob);
	snic_glob = शून्य;

gdi_end:
	वापस ret;
पूर्ण /* end of snic_glob_init */

/*
 * snic_global_data_cleanup : Frees SNIC Global Data
 */
अटल व्योम
snic_global_data_cleanup(व्योम)
अणु
	SNIC_BUG_ON(snic_glob == शून्य);

	destroy_workqueue(snic_glob->event_q);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_TM_CACHE]);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_MAX_SGL]);
	kmem_cache_destroy(snic_glob->req_cache[SNIC_REQ_CACHE_DFLT_SGL]);

#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	/* Freeing Trace Resources */
	snic_trc_मुक्त();

	/* Freeing Debugfs Resources */
	snic_debugfs_term();
#पूर्ण_अगर
	kमुक्त(snic_glob);
	snic_glob = शून्य;
पूर्ण /* end of snic_glob_cleanup */

अटल काष्ठा pci_driver snic_driver = अणु
	.name = SNIC_DRV_NAME,
	.id_table = snic_id_table,
	.probe = snic_probe,
	.हटाओ = snic_हटाओ,
पूर्ण;

अटल पूर्णांक __init
snic_init_module(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_अघोषित __x86_64__
	SNIC_INFO("SNIC Driver is supported only for x86_64 platforms!\n");
	add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);
#पूर्ण_अगर

	SNIC_INFO("%s, ver %s\n", SNIC_DRV_DESCRIPTION, SNIC_DRV_VERSION);

	ret = snic_global_data_init();
	अगर (ret) अणु
		SNIC_ERR("Failed to Initialize Global Data.\n");

		वापस ret;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&snic_driver);
	अगर (ret < 0) अणु
		SNIC_ERR("PCI driver register error\n");

		जाओ err_pci_reg;
	पूर्ण

	वापस ret;

err_pci_reg:
	snic_global_data_cleanup();

	वापस ret;
पूर्ण

अटल व्योम __निकास
snic_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&snic_driver);
	snic_global_data_cleanup();
पूर्ण

module_init(snic_init_module);
module_निकास(snic_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(SNIC_DRV_DESCRIPTION);
MODULE_VERSION(SNIC_DRV_VERSION);
MODULE_DEVICE_TABLE(pci, snic_id_table);
MODULE_AUTHOR("Narsimhulu Musini <nmusini@cisco.com>, "
	      "Sesidhar Baddela <sebaddel@cisco.com>");
