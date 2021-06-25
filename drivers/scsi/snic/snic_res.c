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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>

#समावेश "wq_enet_desc.h"
#समावेश "cq_enet_desc.h"
#समावेश "vnic_resource.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_cq.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "snic.h"

पूर्णांक
snic_get_vnic_config(काष्ठा snic *snic)
अणु
	काष्ठा vnic_snic_config *c = &snic->config;
	पूर्णांक ret;

#घोषणा GET_CONFIG(m) \
	करो अणु \
		ret = svnic_dev_spec(snic->vdev, \
				     दुरत्व(काष्ठा vnic_snic_config, m), \
				     माप(c->m), \
				     &c->m); \
		अगर (ret) अणु \
			SNIC_HOST_ERR(snic->shost, \
				      "Error getting %s, %d\n", #m, ret); \
			वापस ret; \
		पूर्ण \
	पूर्ण जबतक (0)

	GET_CONFIG(wq_enet_desc_count);
	GET_CONFIG(maxdatafieldsize);
	GET_CONFIG(पूर्णांकr_समयr);
	GET_CONFIG(पूर्णांकr_समयr_type);
	GET_CONFIG(flags);
	GET_CONFIG(io_throttle_count);
	GET_CONFIG(port_करोwn_समयout);
	GET_CONFIG(port_करोwn_io_retries);
	GET_CONFIG(luns_per_tgt);
	GET_CONFIG(xpt_type);
	GET_CONFIG(hid);

	c->wq_enet_desc_count = min_t(u32,
				      VNIC_SNIC_WQ_DESCS_MAX,
				      max_t(u32,
					    VNIC_SNIC_WQ_DESCS_MIN,
					    c->wq_enet_desc_count));

	c->wq_enet_desc_count = ALIGN(c->wq_enet_desc_count, 16);

	c->maxdatafieldsize = min_t(u32,
				    VNIC_SNIC_MAXDATAFIELDSIZE_MAX,
				    max_t(u32,
					  VNIC_SNIC_MAXDATAFIELDSIZE_MIN,
					  c->maxdatafieldsize));

	c->io_throttle_count = min_t(u32,
				     VNIC_SNIC_IO_THROTTLE_COUNT_MAX,
				     max_t(u32,
					   VNIC_SNIC_IO_THROTTLE_COUNT_MIN,
					   c->io_throttle_count));

	c->port_करोwn_समयout = min_t(u32,
				     VNIC_SNIC_PORT_DOWN_TIMEOUT_MAX,
				     c->port_करोwn_समयout);

	c->port_करोwn_io_retries = min_t(u32,
				     VNIC_SNIC_PORT_DOWN_IO_RETRIES_MAX,
				     c->port_करोwn_io_retries);

	c->luns_per_tgt = min_t(u32,
				VNIC_SNIC_LUNS_PER_TARGET_MAX,
				max_t(u32,
				      VNIC_SNIC_LUNS_PER_TARGET_MIN,
				      c->luns_per_tgt));

	c->पूर्णांकr_समयr = min_t(u32, VNIC_INTR_TIMER_MAX, c->पूर्णांकr_समयr);

	SNIC_INFO("vNIC resources wq %d\n", c->wq_enet_desc_count);
	SNIC_INFO("vNIC mtu %d intr timer %d\n",
		  c->maxdatafieldsize,
		  c->पूर्णांकr_समयr);

	SNIC_INFO("vNIC flags 0x%x luns per tgt %d\n",
		  c->flags,
		  c->luns_per_tgt);

	SNIC_INFO("vNIC io throttle count %d\n", c->io_throttle_count);
	SNIC_INFO("vNIC port down timeout %d port down io retries %d\n",
		  c->port_करोwn_समयout,
		  c->port_करोwn_io_retries);

	SNIC_INFO("vNIC back end type = %d\n", c->xpt_type);
	SNIC_INFO("vNIC hid = %d\n", c->hid);

	वापस 0;
पूर्ण

व्योम
snic_get_res_counts(काष्ठा snic *snic)
अणु
	snic->wq_count = svnic_dev_get_res_count(snic->vdev, RES_TYPE_WQ);
	SNIC_BUG_ON(snic->wq_count == 0);
	snic->cq_count = svnic_dev_get_res_count(snic->vdev, RES_TYPE_CQ);
	SNIC_BUG_ON(snic->cq_count == 0);
	snic->पूर्णांकr_count = svnic_dev_get_res_count(snic->vdev,
						  RES_TYPE_INTR_CTRL);
	SNIC_BUG_ON(snic->पूर्णांकr_count == 0);
पूर्ण

व्योम
snic_मुक्त_vnic_res(काष्ठा snic *snic)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < snic->wq_count; i++)
		svnic_wq_मुक्त(&snic->wq[i]);

	क्रम (i = 0; i < snic->cq_count; i++)
		svnic_cq_मुक्त(&snic->cq[i]);

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++)
		svnic_पूर्णांकr_मुक्त(&snic->पूर्णांकr[i]);
पूर्ण

पूर्णांक
snic_alloc_vnic_res(काष्ठा snic *snic)
अणु
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;
	अचिन्हित पूर्णांक mask_on_निश्चितion;
	अचिन्हित पूर्णांक पूर्णांकr_offset;
	अचिन्हित पूर्णांक err_पूर्णांकr_enable;
	अचिन्हित पूर्णांक err_पूर्णांकr_offset;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	पूर्णांकr_mode = svnic_dev_get_पूर्णांकr_mode(snic->vdev);

	SNIC_INFO("vNIC interrupt mode: %s\n",
		  ((पूर्णांकr_mode == VNIC_DEV_INTR_MODE_INTX) ?
		   "Legacy PCI INTx" :
		   ((पूर्णांकr_mode == VNIC_DEV_INTR_MODE_MSI) ?
		    "MSI" :
		    ((पूर्णांकr_mode == VNIC_DEV_INTR_MODE_MSIX) ?
		     "MSI-X" : "Unknown"))));

	/* only MSI-X is supported */
	SNIC_BUG_ON(पूर्णांकr_mode != VNIC_DEV_INTR_MODE_MSIX);

	SNIC_INFO("wq %d cq %d intr %d\n", snic->wq_count,
		  snic->cq_count,
		  snic->पूर्णांकr_count);


	/* Allocate WQs used क्रम SCSI IOs */
	क्रम (i = 0; i < snic->wq_count; i++) अणु
		ret = svnic_wq_alloc(snic->vdev,
				     &snic->wq[i],
				     i,
				     snic->config.wq_enet_desc_count,
				     माप(काष्ठा wq_enet_desc));
		अगर (ret)
			जाओ error_cleanup;
	पूर्ण

	/* CQ क्रम each WQ */
	क्रम (i = 0; i < snic->wq_count; i++) अणु
		ret = svnic_cq_alloc(snic->vdev,
				     &snic->cq[i],
				     i,
				     snic->config.wq_enet_desc_count,
				     माप(काष्ठा cq_enet_wq_desc));
		अगर (ret)
			जाओ error_cleanup;
	पूर्ण

	SNIC_BUG_ON(snic->cq_count != 2 * snic->wq_count);
	/* CQ क्रम FW TO host */
	क्रम (i = snic->wq_count; i < snic->cq_count; i++) अणु
		ret = svnic_cq_alloc(snic->vdev,
				     &snic->cq[i],
				     i,
				     (snic->config.wq_enet_desc_count * 3),
				     माप(काष्ठा snic_fw_req));
		अगर (ret)
			जाओ error_cleanup;
	पूर्ण

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++) अणु
		ret = svnic_पूर्णांकr_alloc(snic->vdev, &snic->पूर्णांकr[i], i);
		अगर (ret)
			जाओ error_cleanup;
	पूर्ण

	/*
	 * Init WQ Resources.
	 * WQ[0 to n] poपूर्णांकs to CQ[0 to n-1]
	 * firmware to host comm poपूर्णांकs to CQ[n to m+1]
	 */
	err_पूर्णांकr_enable = 1;
	err_पूर्णांकr_offset = snic->err_पूर्णांकr_offset;

	क्रम (i = 0; i < snic->wq_count; i++) अणु
		svnic_wq_init(&snic->wq[i],
			      i,
			      err_पूर्णांकr_enable,
			      err_पूर्णांकr_offset);
	पूर्ण

	क्रम (i = 0; i < snic->cq_count; i++) अणु
		पूर्णांकr_offset = i;

		svnic_cq_init(&snic->cq[i],
			      0 /* flow_control_enable */,
			      1 /* color_enable */,
			      0 /* cq_head */,
			      0 /* cq_tail */,
			      1 /* cq_tail_color */,
			      1 /* पूर्णांकerrupt_enable */,
			      1 /* cq_entry_enable */,
			      0 /* cq_message_enable */,
			      पूर्णांकr_offset,
			      0 /* cq_message_addr */);
	पूर्ण

	/*
	 * Init INTR resources
	 * Assumption : snic is always in MSI-X mode
	 */
	SNIC_BUG_ON(पूर्णांकr_mode != VNIC_DEV_INTR_MODE_MSIX);
	mask_on_निश्चितion = 1;

	क्रम (i = 0; i < snic->पूर्णांकr_count; i++) अणु
		svnic_पूर्णांकr_init(&snic->पूर्णांकr[i],
				snic->config.पूर्णांकr_समयr,
				snic->config.पूर्णांकr_समयr_type,
				mask_on_निश्चितion);
	पूर्ण

	/* init the stats memory by making the first call here */
	ret = svnic_dev_stats_dump(snic->vdev, &snic->stats);
	अगर (ret) अणु
		SNIC_HOST_ERR(snic->shost,
			      "svnic_dev_stats_dump failed - x%x\n",
			      ret);
		जाओ error_cleanup;
	पूर्ण

	/* Clear LIF stats */
	svnic_dev_stats_clear(snic->vdev);
	ret = 0;

	वापस ret;

error_cleanup:
	snic_मुक्त_vnic_res(snic);

	वापस ret;
पूर्ण

व्योम
snic_log_q_error(काष्ठा snic *snic)
अणु
	अचिन्हित पूर्णांक i;
	u32 err_status;

	क्रम (i = 0; i < snic->wq_count; i++) अणु
		err_status = ioपढ़ो32(&snic->wq[i].ctrl->error_status);
		अगर (err_status)
			SNIC_HOST_ERR(snic->shost,
				      "WQ[%d] error status %d\n",
				      i,
				      err_status);
	पूर्ण
पूर्ण /* end of snic_log_q_error */
