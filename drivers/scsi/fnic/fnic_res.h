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
#अगर_अघोषित _FNIC_RES_H_
#घोषणा _FNIC_RES_H_

#समावेश "wq_enet_desc.h"
#समावेश "rq_enet_desc.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_rq.h"
#समावेश "fnic_io.h"
#समावेश "fcpio.h"
#समावेश "vnic_wq_copy.h"
#समावेश "vnic_cq_copy.h"

अटल अंतरभूत व्योम fnic_queue_wq_desc(काष्ठा vnic_wq *wq,
				      व्योम *os_buf, dma_addr_t dma_addr,
				      अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक fc_eof,
				      पूर्णांक vlan_tag_insert,
				      अचिन्हित पूर्णांक vlan_tag,
				      पूर्णांक cq_entry, पूर्णांक sop, पूर्णांक eop)
अणु
	काष्ठा wq_enet_desc *desc = vnic_wq_next_desc(wq);

	wq_enet_desc_enc(desc,
			 (u64)dma_addr | VNIC_PADDR_TARGET,
			 (u16)len,
			 0, /* mss_or_csum_offset */
			 (u16)fc_eof,
			 0, /* offload_mode */
			 (u8)eop, (u8)cq_entry,
			 1, /* fcoe_encap */
			 (u8)vlan_tag_insert,
			 (u16)vlan_tag,
			 0 /* loopback */);

	vnic_wq_post(wq, os_buf, dma_addr, len, sop, eop);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_eth_desc(काष्ठा vnic_wq *wq,
				      व्योम *os_buf, dma_addr_t dma_addr,
				      अचिन्हित पूर्णांक len,
				      पूर्णांक vlan_tag_insert,
				      अचिन्हित पूर्णांक vlan_tag,
				      पूर्णांक cq_entry)
अणु
	काष्ठा wq_enet_desc *desc = vnic_wq_next_desc(wq);

	wq_enet_desc_enc(desc,
			 (u64)dma_addr | VNIC_PADDR_TARGET,
			 (u16)len,
			 0, /* mss_or_csum_offset */
			 0, /* fc_eof */
			 0, /* offload_mode */
			 1, /* eop */
			 (u8)cq_entry,
			 0, /* fcoe_encap */
			 (u8)vlan_tag_insert,
			 (u16)vlan_tag,
			 0 /* loopback */);

	vnic_wq_post(wq, os_buf, dma_addr, len, 1, 1);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_icmnd_16(काष्ठा vnic_wq_copy *wq,
						    u32 req_id,
						    u32 lunmap_id, u8 spl_flags,
						    u32 sgl_cnt, u32 sense_len,
						    u64 sgl_addr, u64 sns_addr,
						    u8 crn, u8 pri_ta,
						    u8 flags, u8 *scsi_cdb,
						    u8 cdb_len,
						    u32 data_len, u8 *lun,
						    u32 d_id, u16 mss,
						    u32 ratov, u32 edtov)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_ICMND_16; /* क्रमागत fcpio_type */
	desc->hdr.status = 0;            /* header status entry */
	desc->hdr._resvd = 0;            /* reserved */
	desc->hdr.tag.u.req_id = req_id; /* id क्रम this request */

	desc->u.icmnd_16.lunmap_id = lunmap_id; /* index पूर्णांकo lunmap table */
	desc->u.icmnd_16.special_req_flags = spl_flags; /* exch req flags */
	desc->u.icmnd_16._resvd0[0] = 0;        /* reserved */
	desc->u.icmnd_16._resvd0[1] = 0;        /* reserved */
	desc->u.icmnd_16._resvd0[2] = 0;        /* reserved */
	desc->u.icmnd_16.sgl_cnt = sgl_cnt;     /* scatter-gather list count */
	desc->u.icmnd_16.sense_len = sense_len; /* sense buffer length */
	desc->u.icmnd_16.sgl_addr = sgl_addr;   /* scatter-gather list addr */
	desc->u.icmnd_16.sense_addr = sns_addr; /* sense buffer address */
	desc->u.icmnd_16.crn = crn;             /* SCSI Command Reference No.*/
	desc->u.icmnd_16.pri_ta = pri_ta; 	/* SCSI Pri & Task attribute */
	desc->u.icmnd_16._resvd1 = 0;           /* reserved: should be 0 */
	desc->u.icmnd_16.flags = flags;         /* command flags */
	स_रखो(desc->u.icmnd_16.scsi_cdb, 0, CDB_16);
	स_नकल(desc->u.icmnd_16.scsi_cdb, scsi_cdb, cdb_len);    /* SCSI CDB */
	desc->u.icmnd_16.data_len = data_len;   /* length of data expected */
	स_नकल(desc->u.icmnd_16.lun, lun, LUN_ADDRESS);  /* LUN address */
	desc->u.icmnd_16._resvd2 = 0;          	/* reserved */
	hton24(desc->u.icmnd_16.d_id, d_id);	/* FC vNIC only: Target D_ID */
	desc->u.icmnd_16.mss = mss;            	/* FC vNIC only: max burst */
	desc->u.icmnd_16.r_a_tov = ratov; /*FC vNIC only: Res. Alloc Timeout */
	desc->u.icmnd_16.e_d_tov = edtov; /*FC vNIC only: Err Detect Timeout */

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_iपंचांगf(काष्ठा vnic_wq_copy *wq,
						u32 req_id, u32 lunmap_id,
						u32 पंचांग_req, u32 पंचांग_id, u8 *lun,
						u32 d_id, u32 r_a_tov,
						u32 e_d_tov)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_ITMF;     /* क्रमागत fcpio_type */
	desc->hdr.status = 0;            /* header status entry */
	desc->hdr._resvd = 0;            /* reserved */
	desc->hdr.tag.u.req_id = req_id; /* id क्रम this request */

	desc->u.iपंचांगf.lunmap_id = lunmap_id; /* index पूर्णांकo lunmap table */
	desc->u.iपंचांगf.पंचांग_req = पंचांग_req;       /* SCSI Task Management request */
	desc->u.iपंचांगf.t_tag = पंचांग_id;         /* tag of fcpio to be पातed */
	desc->u.iपंचांगf._resvd = 0;
	स_नकल(desc->u.iपंचांगf.lun, lun, LUN_ADDRESS);  /* LUN address */
	desc->u.iपंचांगf._resvd1 = 0;
	hton24(desc->u.iपंचांगf.d_id, d_id);    /* FC vNIC only: Target D_ID */
	desc->u.iपंचांगf.r_a_tov = r_a_tov;     /* FC vNIC only: R_A_TOV in msec */
	desc->u.iपंचांगf.e_d_tov = e_d_tov;     /* FC vNIC only: E_D_TOV in msec */

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_flogi_reg(काष्ठा vnic_wq_copy *wq,
						     u32 req_id, u8 क्रमmat,
						     u32 s_id, u8 *gw_mac)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_FLOGI_REG;     /* क्रमागत fcpio_type */
	desc->hdr.status = 0;                 /* header status entry */
	desc->hdr._resvd = 0;                 /* reserved */
	desc->hdr.tag.u.req_id = req_id;      /* id क्रम this request */

	desc->u.flogi_reg.क्रमmat = क्रमmat;
	desc->u.flogi_reg._resvd = 0;
	hton24(desc->u.flogi_reg.s_id, s_id);
	स_नकल(desc->u.flogi_reg.gateway_mac, gw_mac, ETH_ALEN);

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_fip_reg(काष्ठा vnic_wq_copy *wq,
						   u32 req_id, u32 s_id,
						   u8 *fcf_mac, u8 *ha_mac,
						   u32 r_a_tov, u32 e_d_tov)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_FLOGI_FIP_REG; /* क्रमागत fcpio_type */
	desc->hdr.status = 0;                 /* header status entry */
	desc->hdr._resvd = 0;                 /* reserved */
	desc->hdr.tag.u.req_id = req_id;      /* id क्रम this request */

	desc->u.flogi_fip_reg._resvd0 = 0;
	hton24(desc->u.flogi_fip_reg.s_id, s_id);
	स_नकल(desc->u.flogi_fip_reg.fcf_mac, fcf_mac, ETH_ALEN);
	desc->u.flogi_fip_reg._resvd1 = 0;
	desc->u.flogi_fip_reg.r_a_tov = r_a_tov;
	desc->u.flogi_fip_reg.e_d_tov = e_d_tov;
	स_नकल(desc->u.flogi_fip_reg.ha_mac, ha_mac, ETH_ALEN);
	desc->u.flogi_fip_reg._resvd2 = 0;

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_fw_reset(काष्ठा vnic_wq_copy *wq,
						    u32 req_id)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_RESET;     /* क्रमागत fcpio_type */
	desc->hdr.status = 0;             /* header status entry */
	desc->hdr._resvd = 0;             /* reserved */
	desc->hdr.tag.u.req_id = req_id;  /* id क्रम this request */

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_wq_copy_desc_lunmap(काष्ठा vnic_wq_copy *wq,
						  u32 req_id, u64 lunmap_addr,
						  u32 lunmap_len)
अणु
	काष्ठा fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_LUNMAP_REQ;	/* क्रमागत fcpio_type */
	desc->hdr.status = 0;			/* header status entry */
	desc->hdr._resvd = 0;			/* reserved */
	desc->hdr.tag.u.req_id = req_id;	/* id क्रम this request */

	desc->u.lunmap_req.addr = lunmap_addr;	/* address of the buffer */
	desc->u.lunmap_req.len = lunmap_len;	/* len of the buffer */

	vnic_wq_copy_post(wq);
पूर्ण

अटल अंतरभूत व्योम fnic_queue_rq_desc(काष्ठा vnic_rq *rq,
				      व्योम *os_buf, dma_addr_t dma_addr,
				      u16 len)
अणु
	काष्ठा rq_enet_desc *desc = vnic_rq_next_desc(rq);

	rq_enet_desc_enc(desc,
		(u64)dma_addr | VNIC_PADDR_TARGET,
		RQ_ENET_TYPE_ONLY_SOP,
		(u16)len);

	vnic_rq_post(rq, os_buf, 0, dma_addr, len);
पूर्ण


काष्ठा fnic;

पूर्णांक fnic_get_vnic_config(काष्ठा fnic *);
पूर्णांक fnic_alloc_vnic_resources(काष्ठा fnic *);
व्योम fnic_मुक्त_vnic_resources(काष्ठा fnic *);
व्योम fnic_get_res_counts(काष्ठा fnic *);
पूर्णांक fnic_set_nic_config(काष्ठा fnic *fnic, u8 rss_शेष_cpu,
			u8 rss_hash_type, u8 rss_hash_bits, u8 rss_base_cpu,
			u8 rss_enable, u8 tso_ipid_split_en,
			u8 ig_vlan_strip_en);

#पूर्ण_अगर /* _FNIC_RES_H_ */
