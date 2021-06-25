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

#अगर_अघोषित __SNIC_RES_H
#घोषणा __SNIC_RES_H

#समावेश "snic_io.h"
#समावेश "wq_enet_desc.h"
#समावेश "vnic_wq.h"
#समावेश "snic_fwint.h"
#समावेश "vnic_cq_fw.h"

अटल अंतरभूत व्योम
snic_icmnd_init(काष्ठा snic_host_req *req, u32 cmnd_id, u32 host_id, u64 ctx,
		u16 flags, u64 tgt_id, u8 *lun, u8 *scsi_cdb, u8 cdb_len,
		u32 data_len, u16 sg_cnt, uदीर्घ sgl_addr,
		dma_addr_t sns_addr_pa, u32 sense_len)
अणु
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_ICMND, 0, cmnd_id, host_id, sg_cnt,
			ctx);

	req->u.icmnd.flags = cpu_to_le16(flags);
	req->u.icmnd.tgt_id = cpu_to_le64(tgt_id);
	स_नकल(&req->u.icmnd.lun_id, lun, LUN_ADDR_LEN);
	req->u.icmnd.cdb_len = cdb_len;
	स_रखो(req->u.icmnd.cdb, 0, SNIC_CDB_LEN);
	स_नकल(req->u.icmnd.cdb, scsi_cdb, cdb_len);
	req->u.icmnd.data_len = cpu_to_le32(data_len);
	req->u.icmnd.sg_addr = cpu_to_le64(sgl_addr);
	req->u.icmnd.sense_len = cpu_to_le32(sense_len);
	req->u.icmnd.sense_addr = cpu_to_le64(sns_addr_pa);
पूर्ण

अटल अंतरभूत व्योम
snic_iपंचांगf_init(काष्ठा snic_host_req *req, u32 cmnd_id, u32 host_id, uदीर्घ ctx,
	       u16 flags, u32 req_id, u64 tgt_id, u8 *lun, u8 पंचांग_type)
अणु
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_ITMF, 0, cmnd_id, host_id, 0, ctx);

	req->u.iपंचांगf.पंचांग_type = पंचांग_type;
	req->u.iपंचांगf.flags = cpu_to_le16(flags);
	/* req_id valid only in पात, clear task */
	req->u.iपंचांगf.req_id = cpu_to_le32(req_id);
	req->u.iपंचांगf.tgt_id = cpu_to_le64(tgt_id);
	स_नकल(&req->u.iपंचांगf.lun_id, lun, LUN_ADDR_LEN);
पूर्ण

अटल अंतरभूत व्योम
snic_queue_wq_eth_desc(काष्ठा vnic_wq *wq,
		       व्योम *os_buf,
		       dma_addr_t dma_addr,
		       अचिन्हित पूर्णांक len,
		       पूर्णांक vlan_tag_insert,
		       अचिन्हित पूर्णांक vlan_tag,
		       पूर्णांक cq_entry)
अणु
	काष्ठा wq_enet_desc *desc = svnic_wq_next_desc(wq);

	wq_enet_desc_enc(desc,
			(u64)dma_addr | VNIC_PADDR_TARGET,
			(u16)len,
			0, /* mss_or_csum_offset */
			0, /* fc_eof */
			0, /* offload mode */
			1, /* eop */
			(u8)cq_entry,
			0, /* fcoe_encap */
			(u8)vlan_tag_insert,
			(u16)vlan_tag,
			0 /* loopback */);

	svnic_wq_post(wq, os_buf, dma_addr, len, 1, 1);
पूर्ण

काष्ठा snic;

पूर्णांक snic_get_vnic_config(काष्ठा snic *);
पूर्णांक snic_alloc_vnic_res(काष्ठा snic *);
व्योम snic_मुक्त_vnic_res(काष्ठा snic *);
व्योम snic_get_res_counts(काष्ठा snic *);
व्योम snic_log_q_error(काष्ठा snic *);
पूर्णांक snic_get_vnic_resources_size(काष्ठा snic *);
#पूर्ण_अगर /* __SNIC_RES_H */
