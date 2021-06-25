<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
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
#समावेश <linux/अगर_ether.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/fc_frame.h>

#समावेश "vnic_dev.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "fnic_io.h"
#समावेश "fnic_fip.h"
#समावेश "fnic.h"

#घोषणा PCI_DEVICE_ID_CISCO_FNIC	0x0045

/* Timer to poll notअगरication area क्रम events. Used क्रम MSI पूर्णांकerrupts */
#घोषणा FNIC_NOTIFY_TIMER_PERIOD	(2 * HZ)

अटल काष्ठा kmem_cache *fnic_sgl_cache[FNIC_SGL_NUM_CACHES];
अटल काष्ठा kmem_cache *fnic_io_req_cache;
अटल LIST_HEAD(fnic_list);
अटल DEFINE_SPINLOCK(fnic_list_lock);

/* Supported devices by fnic module */
अटल काष्ठा pci_device_id fnic_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CISCO, PCI_DEVICE_ID_CISCO_FNIC) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("Abhijeet Joglekar <abjoglek@cisco.com>, "
	      "Joseph R. Eykholt <jeykholt@cisco.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, fnic_id_table);

अचिन्हित पूर्णांक fnic_log_level;
module_param(fnic_log_level, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(fnic_log_level, "bit mask of fnic logging levels");


अचिन्हित पूर्णांक io_completions = FNIC_DFLT_IO_COMPLETIONS;
module_param(io_completions, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(io_completions, "Max CQ entries to process at a time");

अचिन्हित पूर्णांक fnic_trace_max_pages = 16;
module_param(fnic_trace_max_pages, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(fnic_trace_max_pages, "Total allocated memory pages "
					"for fnic trace buffer");

अचिन्हित पूर्णांक fnic_fc_trace_max_pages = 64;
module_param(fnic_fc_trace_max_pages, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(fnic_fc_trace_max_pages,
		 "Total allocated memory pages for fc trace buffer");

अटल अचिन्हित पूर्णांक fnic_max_qdepth = FNIC_DFLT_QUEUE_DEPTH;
module_param(fnic_max_qdepth, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(fnic_max_qdepth, "Queue depth to report for each LUN");

अटल काष्ठा libfc_function_ढाँचा fnic_transport_ढाँचा = अणु
	.frame_send = fnic_send,
	.lport_set_port_id = fnic_set_port_id,
	.fcp_पात_io = fnic_empty_scsi_cleanup,
	.fcp_cleanup = fnic_empty_scsi_cleanup,
	.exch_mgr_reset = fnic_exch_mgr_reset
पूर्ण;

अटल पूर्णांक fnic_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	scsi_change_queue_depth(sdev, fnic_max_qdepth);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा fnic_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = DRV_NAME,
	.queuecommand = fnic_queuecommand,
	.eh_समयd_out = fc_eh_समयd_out,
	.eh_पात_handler = fnic_पात_cmd,
	.eh_device_reset_handler = fnic_device_reset,
	.eh_host_reset_handler = fnic_host_reset,
	.slave_alloc = fnic_slave_alloc,
	.change_queue_depth = scsi_change_queue_depth,
	.this_id = -1,
	.cmd_per_lun = 3,
	.can_queue = FNIC_DFLT_IO_REQ,
	.sg_tablesize = FNIC_MAX_SG_DESC_CNT,
	.max_sectors = 0xffff,
	.shost_attrs = fnic_attrs,
	.track_queue_depth = 1,
पूर्ण;

अटल व्योम
fnic_set_rport_dev_loss_पंचांगo(काष्ठा fc_rport *rport, u32 समयout)
अणु
	अगर (समयout)
		rport->dev_loss_पंचांगo = समयout;
	अन्यथा
		rport->dev_loss_पंचांगo = 1;
पूर्ण

अटल व्योम fnic_get_host_speed(काष्ठा Scsi_Host *shost);
अटल काष्ठा scsi_transport_ढाँचा *fnic_fc_transport;
अटल काष्ठा fc_host_statistics *fnic_get_stats(काष्ठा Scsi_Host *);
अटल व्योम fnic_reset_host_stats(काष्ठा Scsi_Host *);

अटल काष्ठा fc_function_ढाँचा fnic_fc_functions = अणु

	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,
	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fnic_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,
	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.show_rport_dev_loss_पंचांगo = 1,
	.set_rport_dev_loss_पंचांगo = fnic_set_rport_dev_loss_पंचांगo,
	.issue_fc_host_lip = fnic_reset,
	.get_fc_host_stats = fnic_get_stats,
	.reset_fc_host_stats = fnic_reset_host_stats,
	.dd_fcrport_size = माप(काष्ठा fc_rport_libfc_priv),
	.terminate_rport_io = fnic_terminate_rport_io,
	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल व्योम fnic_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lp = shost_priv(shost);
	काष्ठा fnic *fnic = lport_priv(lp);
	u32 port_speed = vnic_dev_port_speed(fnic->vdev);

	/* Add in other values as they get defined in fw */
	चयन (port_speed) अणु
	हाल DCEM_PORTSPEED_10G:
		fc_host_speed(shost) = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_20G:
		fc_host_speed(shost) = FC_PORTSPEED_20GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_25G:
		fc_host_speed(shost) = FC_PORTSPEED_25GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_40G:
	हाल DCEM_PORTSPEED_4x10G:
		fc_host_speed(shost) = FC_PORTSPEED_40GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_100G:
		fc_host_speed(shost) = FC_PORTSPEED_100GBIT;
		अवरोध;
	शेष:
		fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा fc_host_statistics *fnic_get_stats(काष्ठा Scsi_Host *host)
अणु
	पूर्णांक ret;
	काष्ठा fc_lport *lp = shost_priv(host);
	काष्ठा fnic *fnic = lport_priv(lp);
	काष्ठा fc_host_statistics *stats = &lp->host_stats;
	काष्ठा vnic_stats *vs;
	अचिन्हित दीर्घ flags;

	अगर (समय_beक्रमe(jअगरfies, fnic->stats_समय + HZ / FNIC_STATS_RATE_LIMIT))
		वापस stats;
	fnic->stats_समय = jअगरfies;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	ret = vnic_dev_stats_dump(fnic->vdev, &fnic->stats);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	अगर (ret) अणु
		FNIC_MAIN_DBG(KERN_DEBUG, fnic->lport->host,
			      "fnic: Get vnic stats failed"
			      " 0x%x", ret);
		वापस stats;
	पूर्ण
	vs = fnic->stats;
	stats->tx_frames = vs->tx.tx_unicast_frames_ok;
	stats->tx_words  = vs->tx.tx_unicast_bytes_ok / 4;
	stats->rx_frames = vs->rx.rx_unicast_frames_ok;
	stats->rx_words  = vs->rx.rx_unicast_bytes_ok / 4;
	stats->error_frames = vs->tx.tx_errors + vs->rx.rx_errors;
	stats->dumped_frames = vs->tx.tx_drops + vs->rx.rx_drop;
	stats->invalid_crc_count = vs->rx.rx_crc_errors;
	stats->seconds_since_last_reset =
			(jअगरfies - fnic->stats_reset_समय) / HZ;
	stats->fcp_input_megabytes = भाग_u64(fnic->fcp_input_bytes, 1000000);
	stats->fcp_output_megabytes = भाग_u64(fnic->fcp_output_bytes, 1000000);

	वापस stats;
पूर्ण

/*
 * fnic_dump_fchost_stats
 * note : dumps fc_statistics पूर्णांकo प्रणाली logs
 */
व्योम fnic_dump_fchost_stats(काष्ठा Scsi_Host *host,
				काष्ठा fc_host_statistics *stats)
अणु
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: seconds since last reset = %llu\n",
			stats->seconds_since_last_reset);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: tx frames		= %llu\n",
			stats->tx_frames);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: tx words		= %llu\n",
			stats->tx_words);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: rx frames		= %llu\n",
			stats->rx_frames);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: rx words		= %llu\n",
			stats->rx_words);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: lip count		= %llu\n",
			stats->lip_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: nos count		= %llu\n",
			stats->nos_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: error frames		= %llu\n",
			stats->error_frames);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: dumped frames	= %llu\n",
			stats->dumped_frames);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: link failure count	= %llu\n",
			stats->link_failure_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: loss of sync count	= %llu\n",
			stats->loss_of_sync_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: loss of signal count	= %llu\n",
			stats->loss_of_संकेत_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: prim seq protocol err count = %llu\n",
			stats->prim_seq_protocol_err_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: invalid tx word count= %llu\n",
			stats->invalid_tx_word_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: invalid crc count	= %llu\n",
			stats->invalid_crc_count);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: fcp input requests	= %llu\n",
			stats->fcp_input_requests);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: fcp output requests	= %llu\n",
			stats->fcp_output_requests);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: fcp control requests	= %llu\n",
			stats->fcp_control_requests);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: fcp input megabytes	= %llu\n",
			stats->fcp_input_megabytes);
	FNIC_MAIN_NOTE(KERN_NOTICE, host,
			"fnic: fcp output megabytes	= %llu\n",
			stats->fcp_output_megabytes);
	वापस;
पूर्ण

/*
 * fnic_reset_host_stats : clears host stats
 * note : called when reset_statistics set under sysfs dir
 */
अटल व्योम fnic_reset_host_stats(काष्ठा Scsi_Host *host)
अणु
	पूर्णांक ret;
	काष्ठा fc_lport *lp = shost_priv(host);
	काष्ठा fnic *fnic = lport_priv(lp);
	काष्ठा fc_host_statistics *stats;
	अचिन्हित दीर्घ flags;

	/* dump current stats, beक्रमe clearing them */
	stats = fnic_get_stats(host);
	fnic_dump_fchost_stats(host, stats);

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	ret = vnic_dev_stats_clear(fnic->vdev);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	अगर (ret) अणु
		FNIC_MAIN_DBG(KERN_DEBUG, fnic->lport->host,
				"fnic: Reset vnic stats failed"
				" 0x%x", ret);
		वापस;
	पूर्ण
	fnic->stats_reset_समय = jअगरfies;
	स_रखो(stats, 0, माप(*stats));

	वापस;
पूर्ण

व्योम fnic_log_q_error(काष्ठा fnic *fnic)
अणु
	अचिन्हित पूर्णांक i;
	u32 error_status;

	क्रम (i = 0; i < fnic->raw_wq_count; i++) अणु
		error_status = ioपढ़ो32(&fnic->wq[i].ctrl->error_status);
		अगर (error_status)
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "WQ[%d] error_status"
				     " %d\n", i, error_status);
	पूर्ण

	क्रम (i = 0; i < fnic->rq_count; i++) अणु
		error_status = ioपढ़ो32(&fnic->rq[i].ctrl->error_status);
		अगर (error_status)
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "RQ[%d] error_status"
				     " %d\n", i, error_status);
	पूर्ण

	क्रम (i = 0; i < fnic->wq_copy_count; i++) अणु
		error_status = ioपढ़ो32(&fnic->wq_copy[i].ctrl->error_status);
		अगर (error_status)
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "CWQ[%d] error_status"
				     " %d\n", i, error_status);
	पूर्ण
पूर्ण

व्योम fnic_handle_link_event(काष्ठा fnic *fnic)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (fnic->stop_rx_link_events) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	queue_work(fnic_event_queue, &fnic->link_work);

पूर्ण

अटल पूर्णांक fnic_notअगरy_set(काष्ठा fnic *fnic)
अणु
	पूर्णांक err;

	चयन (vnic_dev_get_पूर्णांकr_mode(fnic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_INTX:
		err = vnic_dev_notअगरy_set(fnic->vdev, FNIC_INTX_NOTIFY);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSI:
		err = vnic_dev_notअगरy_set(fnic->vdev, -1);
		अवरोध;
	हाल VNIC_DEV_INTR_MODE_MSIX:
		err = vnic_dev_notअगरy_set(fnic->vdev, FNIC_MSIX_ERR_NOTIFY);
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Interrupt mode should be set up"
			     " before devcmd notify set %d\n",
			     vnic_dev_get_पूर्णांकr_mode(fnic->vdev));
		err = -1;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम fnic_notअगरy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fnic *fnic = from_समयr(fnic, t, notअगरy_समयr);

	fnic_handle_link_event(fnic);
	mod_समयr(&fnic->notअगरy_समयr,
		  round_jअगरfies(jअगरfies + FNIC_NOTIFY_TIMER_PERIOD));
पूर्ण

अटल व्योम fnic_fip_notअगरy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fnic *fnic = from_समयr(fnic, t, fip_समयr);

	fnic_handle_fip_समयr(fnic);
पूर्ण

अटल व्योम fnic_notअगरy_समयr_start(काष्ठा fnic *fnic)
अणु
	चयन (vnic_dev_get_पूर्णांकr_mode(fnic->vdev)) अणु
	हाल VNIC_DEV_INTR_MODE_MSI:
		/*
		 * Schedule first समयout immediately. The driver is
		 * initiatialized and पढ़ोy to look क्रम link up notअगरication
		 */
		mod_समयr(&fnic->notअगरy_समयr, jअगरfies);
		अवरोध;
	शेष:
		/* Using पूर्णांकr क्रम notअगरication क्रम INTx/MSI-X */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fnic_dev_रुको(काष्ठा vnic_dev *vdev,
			 पूर्णांक (*start)(काष्ठा vnic_dev *, पूर्णांक),
			 पूर्णांक (*finished)(काष्ठा vnic_dev *, पूर्णांक *),
			 पूर्णांक arg)
अणु
	अचिन्हित दीर्घ समय;
	पूर्णांक करोne;
	पूर्णांक err;
	पूर्णांक count;

	count = 0;

	err = start(vdev, arg);
	अगर (err)
		वापस err;

	/* Wait क्रम func to complete.
	* Someसमय schedule_समयout_unपूर्णांकerruptible take दीर्घ समय
	* to wake up so we करो not retry as we are only रुकोing क्रम
	* 2 seconds in जबतक loop. By adding count, we make sure
	* we try atleast three बार beक्रमe वापसing -ETIMEDOUT
	*/
	समय = jअगरfies + (HZ * 2);
	करो अणु
		err = finished(vdev, &करोne);
		count++;
		अगर (err)
			वापस err;
		अगर (करोne)
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(HZ / 10);
	पूर्ण जबतक (समय_after(समय, jअगरfies) || (count < 3));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक fnic_cleanup(काष्ठा fnic *fnic)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	vnic_dev_disable(fnic->vdev);
	क्रम (i = 0; i < fnic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_mask(&fnic->पूर्णांकr[i]);

	क्रम (i = 0; i < fnic->rq_count; i++) अणु
		err = vnic_rq_disable(&fnic->rq[i]);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < fnic->raw_wq_count; i++) अणु
		err = vnic_wq_disable(&fnic->wq[i]);
		अगर (err)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < fnic->wq_copy_count; i++) अणु
		err = vnic_wq_copy_disable(&fnic->wq_copy[i]);
		अगर (err)
			वापस err;
	पूर्ण

	/* Clean up completed IOs and FCS frames */
	fnic_wq_copy_cmpl_handler(fnic, io_completions);
	fnic_wq_cmpl_handler(fnic, -1);
	fnic_rq_cmpl_handler(fnic, -1);

	/* Clean up the IOs and FCS frames that have not completed */
	क्रम (i = 0; i < fnic->raw_wq_count; i++)
		vnic_wq_clean(&fnic->wq[i], fnic_मुक्त_wq_buf);
	क्रम (i = 0; i < fnic->rq_count; i++)
		vnic_rq_clean(&fnic->rq[i], fnic_मुक्त_rq_buf);
	क्रम (i = 0; i < fnic->wq_copy_count; i++)
		vnic_wq_copy_clean(&fnic->wq_copy[i],
				   fnic_wq_copy_cleanup_handler);

	क्रम (i = 0; i < fnic->cq_count; i++)
		vnic_cq_clean(&fnic->cq[i]);
	क्रम (i = 0; i < fnic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_clean(&fnic->पूर्णांकr[i]);

	mempool_destroy(fnic->io_req_pool);
	क्रम (i = 0; i < FNIC_SGL_NUM_CACHES; i++)
		mempool_destroy(fnic->io_sgl_pool[i]);

	वापस 0;
पूर्ण

अटल व्योम fnic_iounmap(काष्ठा fnic *fnic)
अणु
	अगर (fnic->bar0.vaddr)
		iounmap(fnic->bar0.vaddr);
पूर्ण

/**
 * fnic_get_mac() - get asचिन्हित data MAC address क्रम FIP code.
 * @lport: 	local port.
 */
अटल u8 *fnic_get_mac(काष्ठा fc_lport *lport)
अणु
	काष्ठा fnic *fnic = lport_priv(lport);

	वापस fnic->data_src_addr;
पूर्ण

अटल व्योम fnic_set_vlan(काष्ठा fnic *fnic, u16 vlan_id)
अणु
	vnic_dev_set_शेष_vlan(fnic->vdev, vlan_id);
पूर्ण

अटल पूर्णांक fnic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा fc_lport *lp;
	काष्ठा fnic *fnic;
	mempool_t *pool;
	पूर्णांक err;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/*
	 * Allocate SCSI Host and set up association between host,
	 * local port, and fnic
	 */
	lp = libfc_host_alloc(&fnic_host_ढाँचा, माप(काष्ठा fnic));
	अगर (!lp) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to alloc libfc local port\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	host = lp->host;
	fnic = lport_priv(lp);
	fnic->lport = lp;
	fnic->ctlr.lp = lp;

	fnic->link_events = 0;

	snम_लिखो(fnic->name, माप(fnic->name) - 1, "%s%d", DRV_NAME,
		 host->host_no);

	host->transportt = fnic_fc_transport;

	fnic_stats_debugfs_init(fnic);

	/* Setup PCI resources */
	pci_set_drvdata(pdev, fnic);

	fnic->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Cannot enable PCI device, aborting.\n");
		जाओ err_out_मुक्त_hba;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Cannot enable PCI resources, aborting\n");
		जाओ err_out_disable_device;
	पूर्ण

	pci_set_master(pdev);

	/* Query PCI controller on प्रणाली क्रम DMA addressing
	 * limitation क्रम the device.  Try 64-bit first, and
	 * fail to 32-bit.
	 */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "No usable DMA configuration "
				     "aborting\n");
			जाओ err_out_release_regions;
		पूर्ण
	पूर्ण

	/* Map vNIC resources from BAR0 */
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "BAR0 not memory-map'able, aborting.\n");
		err = -ENODEV;
		जाओ err_out_release_regions;
	पूर्ण

	fnic->bar0.vaddr = pci_iomap(pdev, 0, 0);
	fnic->bar0.bus_addr = pci_resource_start(pdev, 0);
	fnic->bar0.len = pci_resource_len(pdev, 0);

	अगर (!fnic->bar0.vaddr) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Cannot memory-map BAR0 res hdr, "
			     "aborting.\n");
		err = -ENODEV;
		जाओ err_out_release_regions;
	पूर्ण

	fnic->vdev = vnic_dev_रेजिस्टर(शून्य, fnic, pdev, &fnic->bar0);
	अगर (!fnic->vdev) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "vNIC registration failed, "
			     "aborting.\n");
		err = -ENODEV;
		जाओ err_out_iounmap;
	पूर्ण

	err = vnic_dev_cmd_init(fnic->vdev);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				"vnic_dev_cmd_init() returns %d, aborting\n",
				err);
		जाओ err_out_vnic_unरेजिस्टर;
	पूर्ण

	err = fnic_dev_रुको(fnic->vdev, vnic_dev_खोलो,
			    vnic_dev_खोलो_करोne, CMD_OPENF_RQ_ENABLE_THEN_POST);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "vNIC dev open failed, aborting.\n");
		जाओ err_out_dev_cmd_deinit;
	पूर्ण

	err = vnic_dev_init(fnic->vdev, 0);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "vNIC dev init failed, aborting.\n");
		जाओ err_out_dev_बंद;
	पूर्ण

	err = vnic_dev_mac_addr(fnic->vdev, fnic->ctlr.ctl_src_addr);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "vNIC get MAC addr failed \n");
		जाओ err_out_dev_बंद;
	पूर्ण
	/* set data_src क्रम poपूर्णांक-to-poपूर्णांक mode and to keep it non-zero */
	स_नकल(fnic->data_src_addr, fnic->ctlr.ctl_src_addr, ETH_ALEN);

	/* Get vNIC configuration */
	err = fnic_get_vnic_config(fnic);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Get vNIC configuration failed, "
			     "aborting.\n");
		जाओ err_out_dev_बंद;
	पूर्ण

	/* Configure Maximum Outstanding IO reqs*/
	अगर (fnic->config.io_throttle_count != FNIC_UCSM_DFLT_THROTTLE_CNT_BLD) अणु
		host->can_queue = min_t(u32, FNIC_MAX_IO_REQ,
					max_t(u32, FNIC_MIN_IO_REQ,
					fnic->config.io_throttle_count));
	पूर्ण
	fnic->fnic_max_tag_id = host->can_queue;

	host->max_lun = fnic->config.luns_per_tgt;
	host->max_id = FNIC_MAX_FCP_TARGET;
	host->max_cmd_len = FCOE_MAX_CMD_LEN;

	fnic_get_res_counts(fnic);

	err = fnic_set_पूर्णांकr_mode(fnic);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Failed to set intr mode, "
			     "aborting.\n");
		जाओ err_out_dev_बंद;
	पूर्ण

	err = fnic_alloc_vnic_resources(fnic);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Failed to alloc vNIC resources, "
			     "aborting.\n");
		जाओ err_out_clear_पूर्णांकr;
	पूर्ण


	/* initialize all fnic locks */
	spin_lock_init(&fnic->fnic_lock);

	क्रम (i = 0; i < FNIC_WQ_MAX; i++)
		spin_lock_init(&fnic->wq_lock[i]);

	क्रम (i = 0; i < FNIC_WQ_COPY_MAX; i++) अणु
		spin_lock_init(&fnic->wq_copy_lock[i]);
		fnic->wq_copy_desc_low[i] = DESC_CLEAN_LOW_WATERMARK;
		fnic->fw_ack_recd[i] = 0;
		fnic->fw_ack_index[i] = -1;
	पूर्ण

	क्रम (i = 0; i < FNIC_IO_LOCKS; i++)
		spin_lock_init(&fnic->io_req_lock[i]);

	err = -ENOMEM;
	fnic->io_req_pool = mempool_create_slab_pool(2, fnic_io_req_cache);
	अगर (!fnic->io_req_pool)
		जाओ err_out_मुक्त_resources;

	pool = mempool_create_slab_pool(2, fnic_sgl_cache[FNIC_SGL_CACHE_DFLT]);
	अगर (!pool)
		जाओ err_out_मुक्त_ioreq_pool;
	fnic->io_sgl_pool[FNIC_SGL_CACHE_DFLT] = pool;

	pool = mempool_create_slab_pool(2, fnic_sgl_cache[FNIC_SGL_CACHE_MAX]);
	अगर (!pool)
		जाओ err_out_मुक्त_dflt_pool;
	fnic->io_sgl_pool[FNIC_SGL_CACHE_MAX] = pool;

	/* setup vlan config, hw inserts vlan header */
	fnic->vlan_hw_insert = 1;
	fnic->vlan_id = 0;

	/* Initialize the FIP fcoe_ctrl काष्ठा */
	fnic->ctlr.send = fnic_eth_send;
	fnic->ctlr.update_mac = fnic_update_mac;
	fnic->ctlr.get_src_addr = fnic_get_mac;
	अगर (fnic->config.flags & VFCF_FIP_CAPABLE) अणु
		shost_prपूर्णांकk(KERN_INFO, fnic->lport->host,
			     "firmware supports FIP\n");
		/* enable directed and multicast */
		vnic_dev_packet_filter(fnic->vdev, 1, 1, 0, 0, 0);
		vnic_dev_add_addr(fnic->vdev, FIP_ALL_ENODE_MACS);
		vnic_dev_add_addr(fnic->vdev, fnic->ctlr.ctl_src_addr);
		fnic->set_vlan = fnic_set_vlan;
		fcoe_ctlr_init(&fnic->ctlr, FIP_MODE_AUTO);
		समयr_setup(&fnic->fip_समयr, fnic_fip_notअगरy_समयr, 0);
		spin_lock_init(&fnic->vlans_lock);
		INIT_WORK(&fnic->fip_frame_work, fnic_handle_fip_frame);
		INIT_WORK(&fnic->event_work, fnic_handle_event);
		skb_queue_head_init(&fnic->fip_frame_queue);
		INIT_LIST_HEAD(&fnic->evlist);
		INIT_LIST_HEAD(&fnic->vlans);
	पूर्ण अन्यथा अणु
		shost_prपूर्णांकk(KERN_INFO, fnic->lport->host,
			     "firmware uses non-FIP mode\n");
		fcoe_ctlr_init(&fnic->ctlr, FIP_MODE_NON_FIP);
		fnic->ctlr.state = FIP_ST_NON_FIP;
	पूर्ण
	fnic->state = FNIC_IN_FC_MODE;

	atomic_set(&fnic->in_flight, 0);
	fnic->state_flags = FNIC_FLAGS_NONE;

	/* Enable hardware stripping of vlan header on ingress */
	fnic_set_nic_config(fnic, 0, 0, 0, 0, 0, 0, 1);

	/* Setup notअगरication buffer area */
	err = fnic_notअगरy_set(fnic);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Failed to alloc notify buffer, aborting.\n");
		जाओ err_out_मुक्त_max_pool;
	पूर्ण

	/* Setup notअगरy समयr when using MSI पूर्णांकerrupts */
	अगर (vnic_dev_get_पूर्णांकr_mode(fnic->vdev) == VNIC_DEV_INTR_MODE_MSI)
		समयr_setup(&fnic->notअगरy_समयr, fnic_notअगरy_समयr, 0);

	/* allocate RQ buffers and post them to RQ*/
	क्रम (i = 0; i < fnic->rq_count; i++) अणु
		vnic_rq_enable(&fnic->rq[i]);
		err = vnic_rq_fill(&fnic->rq[i], fnic_alloc_rq_frame);
		अगर (err) अणु
			shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
				     "fnic_alloc_rq_frame can't alloc "
				     "frame\n");
			जाओ err_out_मुक्त_rq_buf;
		पूर्ण
	पूर्ण

	/*
	 * Initialization करोne with PCI प्रणाली, hardware, firmware.
	 * Add host to SCSI
	 */
	err = scsi_add_host(lp->host, &pdev->dev);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "fnic: scsi_add_host failed...exiting\n");
		जाओ err_out_मुक्त_rq_buf;
	पूर्ण

	/* Start local port initiatialization */

	lp->link_up = 0;

	lp->max_retry_count = fnic->config.flogi_retries;
	lp->max_rport_retry_count = fnic->config.plogi_retries;
	lp->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
			      FCP_SPPF_CONF_COMPL);
	अगर (fnic->config.flags & VFCF_FCP_SEQ_LVL_ERR)
		lp->service_params |= FCP_SPPF_RETRY;

	lp->boot_समय = jअगरfies;
	lp->e_d_tov = fnic->config.ed_tov;
	lp->r_a_tov = fnic->config.ra_tov;
	lp->link_supported_speeds = FC_PORTSPEED_10GBIT;
	fc_set_wwnn(lp, fnic->config.node_wwn);
	fc_set_wwpn(lp, fnic->config.port_wwn);

	fcoe_libfc_config(lp, &fnic->ctlr, &fnic_transport_ढाँचा, 0);

	अगर (!fc_exch_mgr_alloc(lp, FC_CLASS_3, FCPIO_HOST_EXCH_RANGE_START,
			       FCPIO_HOST_EXCH_RANGE_END, शून्य)) अणु
		err = -ENOMEM;
		जाओ err_out_हटाओ_scsi_host;
	पूर्ण

	fc_lport_init_stats(lp);
	fnic->stats_reset_समय = jअगरfies;

	fc_lport_config(lp);

	अगर (fc_set_mfs(lp, fnic->config.maxdatafieldsize +
		       माप(काष्ठा fc_frame_header))) अणु
		err = -EINVAL;
		जाओ err_out_मुक्त_exch_mgr;
	पूर्ण
	fc_host_maxframe_size(lp->host) = lp->mfs;
	fc_host_dev_loss_पंचांगo(lp->host) = fnic->config.port_करोwn_समयout / 1000;

	प्र_लिखो(fc_host_symbolic_name(lp->host),
		DRV_NAME " v" DRV_VERSION " over %s", fnic->name);

	spin_lock_irqsave(&fnic_list_lock, flags);
	list_add_tail(&fnic->list, &fnic_list);
	spin_unlock_irqrestore(&fnic_list_lock, flags);

	INIT_WORK(&fnic->link_work, fnic_handle_link);
	INIT_WORK(&fnic->frame_work, fnic_handle_frame);
	skb_queue_head_init(&fnic->frame_queue);
	skb_queue_head_init(&fnic->tx_queue);

	/* Enable all queues */
	क्रम (i = 0; i < fnic->raw_wq_count; i++)
		vnic_wq_enable(&fnic->wq[i]);
	क्रम (i = 0; i < fnic->wq_copy_count; i++)
		vnic_wq_copy_enable(&fnic->wq_copy[i]);

	fc_fabric_login(lp);

	err = fnic_request_पूर्णांकr(fnic);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "Unable to request irq.\n");
		जाओ err_out_मुक्त_exch_mgr;
	पूर्ण

	vnic_dev_enable(fnic->vdev);

	क्रम (i = 0; i < fnic->पूर्णांकr_count; i++)
		vnic_पूर्णांकr_unmask(&fnic->पूर्णांकr[i]);

	fnic_notअगरy_समयr_start(fnic);

	वापस 0;

err_out_मुक्त_exch_mgr:
	fc_exch_mgr_मुक्त(lp);
err_out_हटाओ_scsi_host:
	fc_हटाओ_host(lp->host);
	scsi_हटाओ_host(lp->host);
err_out_मुक्त_rq_buf:
	क्रम (i = 0; i < fnic->rq_count; i++)
		vnic_rq_clean(&fnic->rq[i], fnic_मुक्त_rq_buf);
	vnic_dev_notअगरy_unset(fnic->vdev);
err_out_मुक्त_max_pool:
	mempool_destroy(fnic->io_sgl_pool[FNIC_SGL_CACHE_MAX]);
err_out_मुक्त_dflt_pool:
	mempool_destroy(fnic->io_sgl_pool[FNIC_SGL_CACHE_DFLT]);
err_out_मुक्त_ioreq_pool:
	mempool_destroy(fnic->io_req_pool);
err_out_मुक्त_resources:
	fnic_मुक्त_vnic_resources(fnic);
err_out_clear_पूर्णांकr:
	fnic_clear_पूर्णांकr_mode(fnic);
err_out_dev_बंद:
	vnic_dev_बंद(fnic->vdev);
err_out_dev_cmd_deinit:
err_out_vnic_unरेजिस्टर:
	vnic_dev_unरेजिस्टर(fnic->vdev);
err_out_iounmap:
	fnic_iounmap(fnic);
err_out_release_regions:
	pci_release_regions(pdev);
err_out_disable_device:
	pci_disable_device(pdev);
err_out_मुक्त_hba:
	fnic_stats_debugfs_हटाओ(fnic);
	scsi_host_put(lp->host);
err_out:
	वापस err;
पूर्ण

अटल व्योम fnic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fnic *fnic = pci_get_drvdata(pdev);
	काष्ठा fc_lport *lp = fnic->lport;
	अचिन्हित दीर्घ flags;

	/*
	 * Mark state so that the workqueue thपढ़ो stops क्रमwarding
	 * received frames and link events to the local port. ISR and
	 * other thपढ़ोs that can queue work items will also stop
	 * creating work items on the fnic workqueue
	 */
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->stop_rx_link_events = 1;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	अगर (vnic_dev_get_पूर्णांकr_mode(fnic->vdev) == VNIC_DEV_INTR_MODE_MSI)
		del_समयr_sync(&fnic->notअगरy_समयr);

	/*
	 * Flush the fnic event queue. After this call, there should
	 * be no event queued क्रम this fnic device in the workqueue
	 */
	flush_workqueue(fnic_event_queue);
	skb_queue_purge(&fnic->frame_queue);
	skb_queue_purge(&fnic->tx_queue);

	अगर (fnic->config.flags & VFCF_FIP_CAPABLE) अणु
		del_समयr_sync(&fnic->fip_समयr);
		skb_queue_purge(&fnic->fip_frame_queue);
		fnic_fcoe_reset_vlans(fnic);
		fnic_fcoe_evlist_मुक्त(fnic);
	पूर्ण

	/*
	 * Log off the fabric. This stops all remote ports, dns port,
	 * logs off the fabric. This flushes all rport, disc, lport work
	 * beक्रमe वापसing
	 */
	fc_fabric_logoff(fnic->lport);

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->in_हटाओ = 1;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	fcoe_ctlr_destroy(&fnic->ctlr);
	fc_lport_destroy(lp);
	fnic_stats_debugfs_हटाओ(fnic);

	/*
	 * This stops the fnic device, masks all पूर्णांकerrupts. Completed
	 * CQ entries are drained. Posted WQ/RQ/Copy-WQ entries are
	 * cleaned up
	 */
	fnic_cleanup(fnic);

	BUG_ON(!skb_queue_empty(&fnic->frame_queue));
	BUG_ON(!skb_queue_empty(&fnic->tx_queue));

	spin_lock_irqsave(&fnic_list_lock, flags);
	list_del(&fnic->list);
	spin_unlock_irqrestore(&fnic_list_lock, flags);

	fc_हटाओ_host(fnic->lport->host);
	scsi_हटाओ_host(fnic->lport->host);
	fc_exch_mgr_मुक्त(fnic->lport);
	vnic_dev_notअगरy_unset(fnic->vdev);
	fnic_मुक्त_पूर्णांकr(fnic);
	fnic_मुक्त_vnic_resources(fnic);
	fnic_clear_पूर्णांकr_mode(fnic);
	vnic_dev_बंद(fnic->vdev);
	vnic_dev_unरेजिस्टर(fnic->vdev);
	fnic_iounmap(fnic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	scsi_host_put(lp->host);
पूर्ण

अटल काष्ठा pci_driver fnic_driver = अणु
	.name = DRV_NAME,
	.id_table = fnic_id_table,
	.probe = fnic_probe,
	.हटाओ = fnic_हटाओ,
पूर्ण;

अटल पूर्णांक __init fnic_init_module(व्योम)
अणु
	माप_प्रकार len;
	पूर्णांक err = 0;

	prपूर्णांकk(KERN_INFO PFX "%s, ver %s\n", DRV_DESCRIPTION, DRV_VERSION);

	/* Create debugfs entries क्रम fnic */
	err = fnic_debugfs_init();
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to create fnic directory "
				"for tracing and stats logging\n");
		fnic_debugfs_terminate();
	पूर्ण

	/* Allocate memory क्रम trace buffer */
	err = fnic_trace_buf_init();
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX
		       "Trace buffer initialization Failed. "
		       "Fnic Tracing utility is disabled\n");
		fnic_trace_मुक्त();
	पूर्ण

    /* Allocate memory क्रम fc trace buffer */
	err = fnic_fc_trace_init();
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "FC trace buffer initialization Failed "
		       "FC frame tracing utility is disabled\n");
		fnic_fc_trace_मुक्त();
	पूर्ण

	/* Create a cache क्रम allocation of शेष size sgls */
	len = माप(काष्ठा fnic_dflt_sgl_list);
	fnic_sgl_cache[FNIC_SGL_CACHE_DFLT] = kmem_cache_create
		("fnic_sgl_dflt", len + FNIC_SG_DESC_ALIGN, FNIC_SG_DESC_ALIGN,
		 SLAB_HWCACHE_ALIGN,
		 शून्य);
	अगर (!fnic_sgl_cache[FNIC_SGL_CACHE_DFLT]) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create fnic dflt sgl slab\n");
		err = -ENOMEM;
		जाओ err_create_fnic_sgl_slab_dflt;
	पूर्ण

	/* Create a cache क्रम allocation of max size sgls*/
	len = माप(काष्ठा fnic_sgl_list);
	fnic_sgl_cache[FNIC_SGL_CACHE_MAX] = kmem_cache_create
		("fnic_sgl_max", len + FNIC_SG_DESC_ALIGN, FNIC_SG_DESC_ALIGN,
		  SLAB_HWCACHE_ALIGN,
		  शून्य);
	अगर (!fnic_sgl_cache[FNIC_SGL_CACHE_MAX]) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create fnic max sgl slab\n");
		err = -ENOMEM;
		जाओ err_create_fnic_sgl_slab_max;
	पूर्ण

	/* Create a cache of io_req काष्ठाs क्रम use via mempool */
	fnic_io_req_cache = kmem_cache_create("fnic_io_req",
					      माप(काष्ठा fnic_io_req),
					      0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!fnic_io_req_cache) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create fnic io_req slab\n");
		err = -ENOMEM;
		जाओ err_create_fnic_ioreq_slab;
	पूर्ण

	fnic_event_queue = create_singlethपढ़ो_workqueue("fnic_event_wq");
	अगर (!fnic_event_queue) अणु
		prपूर्णांकk(KERN_ERR PFX "fnic work queue create failed\n");
		err = -ENOMEM;
		जाओ err_create_fnic_workq;
	पूर्ण

	fnic_fip_queue = create_singlethपढ़ो_workqueue("fnic_fip_q");
	अगर (!fnic_fip_queue) अणु
		prपूर्णांकk(KERN_ERR PFX "fnic FIP work queue create failed\n");
		err = -ENOMEM;
		जाओ err_create_fip_workq;
	पूर्ण

	fnic_fc_transport = fc_attach_transport(&fnic_fc_functions);
	अगर (!fnic_fc_transport) अणु
		prपूर्णांकk(KERN_ERR PFX "fc_attach_transport error\n");
		err = -ENOMEM;
		जाओ err_fc_transport;
	पूर्ण

	/* रेजिस्टर the driver with PCI प्रणाली */
	err = pci_रेजिस्टर_driver(&fnic_driver);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "pci register error\n");
		जाओ err_pci_रेजिस्टर;
	पूर्ण
	वापस err;

err_pci_रेजिस्टर:
	fc_release_transport(fnic_fc_transport);
err_fc_transport:
	destroy_workqueue(fnic_fip_queue);
err_create_fip_workq:
	destroy_workqueue(fnic_event_queue);
err_create_fnic_workq:
	kmem_cache_destroy(fnic_io_req_cache);
err_create_fnic_ioreq_slab:
	kmem_cache_destroy(fnic_sgl_cache[FNIC_SGL_CACHE_MAX]);
err_create_fnic_sgl_slab_max:
	kmem_cache_destroy(fnic_sgl_cache[FNIC_SGL_CACHE_DFLT]);
err_create_fnic_sgl_slab_dflt:
	fnic_trace_मुक्त();
	fnic_fc_trace_मुक्त();
	fnic_debugfs_terminate();
	वापस err;
पूर्ण

अटल व्योम __निकास fnic_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&fnic_driver);
	destroy_workqueue(fnic_event_queue);
	अगर (fnic_fip_queue) अणु
		flush_workqueue(fnic_fip_queue);
		destroy_workqueue(fnic_fip_queue);
	पूर्ण
	kmem_cache_destroy(fnic_sgl_cache[FNIC_SGL_CACHE_MAX]);
	kmem_cache_destroy(fnic_sgl_cache[FNIC_SGL_CACHE_DFLT]);
	kmem_cache_destroy(fnic_io_req_cache);
	fc_release_transport(fnic_fc_transport);
	fnic_trace_मुक्त();
	fnic_fc_trace_मुक्त();
	fnic_debugfs_terminate();
पूर्ण

module_init(fnic_init_module);
module_निकास(fnic_cleanup_module);

