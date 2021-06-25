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

#अगर_अघोषित _SNIC_IO_H
#घोषणा _SNIC_IO_H

#घोषणा SNIC_DFLT_SG_DESC_CNT	32	/* Default descriptors क्रम sgl */
#घोषणा SNIC_MAX_SG_DESC_CNT	60	/* Max descriptor क्रम sgl */
#घोषणा SNIC_SG_DESC_ALIGN	16	/* Descriptor address alignment */

/* SG descriptor क्रम snic */
काष्ठा snic_sg_desc अणु
	__le64 addr;
	__le32 len;
	u32 _resvd;
पूर्ण;

काष्ठा snic_dflt_sgl अणु
	काष्ठा snic_sg_desc sg_desc[SNIC_DFLT_SG_DESC_CNT];
पूर्ण;

काष्ठा snic_max_sgl अणु
	काष्ठा snic_sg_desc sg_desc[SNIC_MAX_SG_DESC_CNT];
पूर्ण;

क्रमागत snic_req_cache_type अणु
	SNIC_REQ_CACHE_DFLT_SGL = 0,	/* cache with शेष size sgl */
	SNIC_REQ_CACHE_MAX_SGL,		/* cache with max size sgl */
	SNIC_REQ_TM_CACHE,		/* cache क्रम task mgmt reqs contains
					   snic_host_req objects only*/
	SNIC_REQ_MAX_CACHES		/* number of sgl caches */
पूर्ण;

/* Per IO पूर्णांकernal state */
काष्ठा snic_पूर्णांकernal_io_state अणु
	अक्षर	*rqi;
	u64	flags;
	u32	state;
	u32	abts_status;	/* Abort completion status */
	u32	lr_status;	/* device reset completion status */
पूर्ण;

/* IO state machine */
क्रमागत snic_ioreq_state अणु
	SNIC_IOREQ_NOT_INITED = 0,
	SNIC_IOREQ_PENDING,
	SNIC_IOREQ_ABTS_PENDING,
	SNIC_IOREQ_ABTS_COMPLETE,
	SNIC_IOREQ_LR_PENDING,
	SNIC_IOREQ_LR_COMPLETE,
	SNIC_IOREQ_COMPLETE,
पूर्ण;

काष्ठा snic;
काष्ठा snic_host_req;

/*
 * snic_req_info : Contains info about IO, one per scsi command.
 * Notes: Make sure that the काष्ठाure is aligned to 16 B
 * this helps in easy access to snic_req_info from snic_host_req
 */
काष्ठा snic_req_info अणु
	काष्ठा list_head list;
	काष्ठा snic_host_req *req;
	u64	start_समय;		/* start समय in jअगरfies */
	u16	rq_pool_type;		/* noticion of request pool type */
	u16	req_len;		/* buf len passing to fw (req + sgl)*/
	u32	tgt_id;

	u32	पंचांग_tag;
	u8	io_cmpl:1;		/* sets to 1 when fw completes IO */
	u8	resvd[3];
	काष्ठा scsi_cmnd *sc;		/* Associated scsi cmd */
	काष्ठा snic	*snic;		/* Associated snic */
	uदीर्घ	sge_va;			/* Poपूर्णांकer to Resp Buffer */
	u64	snsbuf_va;

	काष्ठा snic_host_req *पात_req;
	काष्ठा completion *abts_करोne;

	काष्ठा snic_host_req *dr_req;
	काष्ठा completion *dr_करोne;
पूर्ण;


#घोषणा rqi_to_req(rqi)	\
	((काष्ठा snic_host_req *) (((काष्ठा snic_req_info *)rqi)->req))

#घोषणा req_to_rqi(req)	\
	((काष्ठा snic_req_info *) (((काष्ठा snic_host_req *)req)->hdr.init_ctx))

#घोषणा req_to_sgl(req)	\
	((काष्ठा snic_sg_desc *) (((काष्ठा snic_host_req *)req)+1))

काष्ठा snic_req_info *
snic_req_init(काष्ठा snic *, पूर्णांक sg_cnt);
व्योम snic_req_मुक्त(काष्ठा snic *, काष्ठा snic_req_info *);
व्योम snic_calc_io_process_समय(काष्ठा snic *, काष्ठा snic_req_info *);
व्योम snic_pci_unmap_rsp_buf(काष्ठा snic *, काष्ठा snic_req_info *);
काष्ठा snic_host_req *
snic_पात_req_init(काष्ठा snic *, काष्ठा snic_req_info *);
काष्ठा snic_host_req *
snic_dr_req_init(काष्ठा snic *, काष्ठा snic_req_info *);
#पूर्ण_अगर /* _SNIC_IO_H */
