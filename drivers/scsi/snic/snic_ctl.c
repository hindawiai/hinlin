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
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mempool.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <linux/प्रकार.स>

#समावेश "snic_io.h"
#समावेश "snic.h"
#समावेश "cq_enet_desc.h"
#समावेश "snic_fwint.h"

/*
 * snic_handle_link : Handles link flaps.
 */
व्योम
snic_handle_link(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snic *snic = container_of(work, काष्ठा snic, link_work);

	अगर (snic->config.xpt_type == SNIC_DAS)
		वापस;

	snic->link_status = svnic_dev_link_status(snic->vdev);
	snic->link_करोwn_cnt = svnic_dev_link_करोwn_cnt(snic->vdev);
	SNIC_HOST_INFO(snic->shost, "Link Event: Link %s.\n",
		       ((snic->link_status) ? "Up" : "Down"));

	SNIC_ASSERT_NOT_IMPL(1);
पूर्ण


/*
 * snic_ver_enc : Encodes version str to पूर्णांक
 * version string is similar to neपंचांगask string
 */
अटल पूर्णांक
snic_ver_enc(स्थिर अक्षर *s)
अणु
	पूर्णांक v[4] = अणु0पूर्ण;
	पूर्णांक  i = 0, x = 0;
	अक्षर c;
	स्थिर अक्षर *p = s;

	/* validate version string */
	अगर ((म_माप(s) > 15) || (म_माप(s) < 7))
		जाओ end;

	जबतक ((c = *p++)) अणु
		अगर (c == '.') अणु
			i++;
			जारी;
		पूर्ण

		अगर (i > 3 || !है_अंक(c))
			जाओ end;

		v[i] = v[i] * 10 + (c - '0');
	पूर्ण

	/* validate sub version numbers */
	क्रम (i = 3; i >= 0; i--)
		अगर (v[i] > 0xff)
			जाओ end;

	x |= (v[0] << 24) | v[1] << 16 | v[2] << 8 | v[3];

end:
	अगर (x == 0) अणु
		SNIC_ERR("Invalid version string [%s].\n", s);

		वापस -1;
	पूर्ण

	वापस x;
पूर्ण /* end of snic_ver_enc */

/*
 * snic_qeueue_exch_ver_req :
 *
 * Queues Exchange Version Request, to communicate host inक्रमmation
 * in वापस, it माला_लो firmware version details
 */
पूर्णांक
snic_queue_exch_ver_req(काष्ठा snic *snic)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_host_req *req = शून्य;
	u32 ver = 0;
	पूर्णांक ret = 0;

	SNIC_HOST_INFO(snic->shost, "Exch Ver Req Preparing...\n");

	rqi = snic_req_init(snic, 0);
	अगर (!rqi) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Queuing Exch Ver Req failed, err = %d\n",
			      ret);

		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	req = rqi_to_req(rqi);

	/* Initialize snic_host_req */
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_EXCH_VER, 0, SCSI_NO_TAG,
			snic->config.hid, 0, (uदीर्घ)rqi);
	ver = snic_ver_enc(SNIC_DRV_VERSION);
	req->u.exch_ver.drvr_ver = cpu_to_le32(ver);
	req->u.exch_ver.os_type = cpu_to_le32(SNIC_OS_LINUX);

	snic_handle_untagged_req(snic, rqi);

	ret = snic_queue_wq_desc(snic, req, माप(*req));
	अगर (ret) अणु
		snic_release_untagged_req(snic, rqi);
		SNIC_HOST_ERR(snic->shost,
			      "Queuing Exch Ver Req failed, err = %d\n",
			      ret);
		जाओ error;
	पूर्ण

	SNIC_HOST_INFO(snic->shost, "Exch Ver Req is issued. ret = %d\n", ret);

error:
	वापस ret;
पूर्ण /* end of snic_queue_exch_ver_req */

/*
 * snic_io_exch_ver_cmpl_handler
 */
व्योम
snic_io_exch_ver_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq)
अणु
	काष्ठा snic_req_info *rqi = शून्य;
	काष्ठा snic_exch_ver_rsp *exv_cmpl = &fwreq->u.exch_ver_cmpl;
	u8 typ, hdr_stat;
	u32 cmnd_id, hid, max_sgs;
	uदीर्घ ctx = 0;
	अचिन्हित दीर्घ flags;

	SNIC_HOST_INFO(snic->shost, "Exch Ver Compl Received.\n");
	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	SNIC_BUG_ON(snic->config.hid != hid);
	rqi = (काष्ठा snic_req_info *) ctx;

	अगर (hdr_stat) अणु
		SNIC_HOST_ERR(snic->shost,
			      "Exch Ver Completed w/ err status %d\n",
			      hdr_stat);

		जाओ exch_cmpl_end;
	पूर्ण

	spin_lock_irqsave(&snic->snic_lock, flags);
	snic->fwinfo.fw_ver = le32_to_cpu(exv_cmpl->version);
	snic->fwinfo.hid = le32_to_cpu(exv_cmpl->hid);
	snic->fwinfo.max_concur_ios = le32_to_cpu(exv_cmpl->max_concur_ios);
	snic->fwinfo.max_sgs_per_cmd = le32_to_cpu(exv_cmpl->max_sgs_per_cmd);
	snic->fwinfo.max_io_sz = le32_to_cpu(exv_cmpl->max_io_sz);
	snic->fwinfo.max_tgts = le32_to_cpu(exv_cmpl->max_tgts);
	snic->fwinfo.io_पंचांगo = le16_to_cpu(exv_cmpl->io_समयout);

	SNIC_HOST_INFO(snic->shost,
		       "vers %u hid %u max_concur_ios %u max_sgs_per_cmd %u max_io_sz %u max_tgts %u fw tmo %u\n",
		       snic->fwinfo.fw_ver,
		       snic->fwinfo.hid,
		       snic->fwinfo.max_concur_ios,
		       snic->fwinfo.max_sgs_per_cmd,
		       snic->fwinfo.max_io_sz,
		       snic->fwinfo.max_tgts,
		       snic->fwinfo.io_पंचांगo);

	SNIC_HOST_INFO(snic->shost,
		       "HBA Capabilities = 0x%x\n",
		       le32_to_cpu(exv_cmpl->hba_cap));

	/* Updating SGList size */
	max_sgs = snic->fwinfo.max_sgs_per_cmd;
	अगर (max_sgs && max_sgs < SNIC_MAX_SG_DESC_CNT) अणु
		snic->shost->sg_tablesize = max_sgs;
		SNIC_HOST_INFO(snic->shost, "Max SGs set to %d\n",
			       snic->shost->sg_tablesize);
	पूर्ण अन्यथा अगर (max_sgs > snic->shost->sg_tablesize) अणु
		SNIC_HOST_INFO(snic->shost,
			       "Target type %d Supports Larger Max SGList %d than driver's Max SG List %d.\n",
			       snic->config.xpt_type, max_sgs,
			       snic->shost->sg_tablesize);
	पूर्ण

	अगर (snic->shost->can_queue > snic->fwinfo.max_concur_ios)
		snic->shost->can_queue = snic->fwinfo.max_concur_ios;

	snic->shost->max_sectors = snic->fwinfo.max_io_sz >> 9;
	अगर (snic->fwinfo.रुको)
		complete(snic->fwinfo.रुको);

	spin_unlock_irqrestore(&snic->snic_lock, flags);

exch_cmpl_end:
	snic_release_untagged_req(snic, rqi);

	SNIC_HOST_INFO(snic->shost, "Exch_cmpl Done, hdr_stat %d.\n", hdr_stat);
पूर्ण /* end of snic_io_exch_ver_cmpl_handler */

/*
 * snic_get_conf
 *
 * Synchronous call, and Retrieves snic params.
 */
पूर्णांक
snic_get_conf(काष्ठा snic *snic)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	पूर्णांक nr_retries = 3;

	SNIC_HOST_INFO(snic->shost, "Retrieving snic params.\n");
	spin_lock_irqsave(&snic->snic_lock, flags);
	स_रखो(&snic->fwinfo, 0, माप(snic->fwinfo));
	snic->fwinfo.रुको = &रुको;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	/* Additional delay to handle HW Resource initialization. */
	msleep(50);

	/*
	 * Exch ver req can be ignored by FW, अगर HW Resource initialization
	 * is in progress, Hence retry.
	 */
	करो अणु
		ret = snic_queue_exch_ver_req(snic);
		अगर (ret)
			वापस ret;

		रुको_क्रम_completion_समयout(&रुको, msecs_to_jअगरfies(2000));
		spin_lock_irqsave(&snic->snic_lock, flags);
		ret = (snic->fwinfo.fw_ver != 0) ? 0 : -ETIMEDOUT;
		अगर (ret)
			SNIC_HOST_ERR(snic->shost,
				      "Failed to retrieve snic params,\n");

		/* Unset fwinfo.रुको, on success or on last retry */
		अगर (ret == 0 || nr_retries == 1)
			snic->fwinfo.रुको = शून्य;

		spin_unlock_irqrestore(&snic->snic_lock, flags);
	पूर्ण जबतक (ret && --nr_retries);

	वापस ret;
पूर्ण /* end of snic_get_info */
