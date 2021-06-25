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
#अगर_अघोषित _FNIC_IO_H_
#घोषणा _FNIC_IO_H_

#समावेश <scsi/fc/fc_fcp.h>

#घोषणा FNIC_DFLT_SG_DESC_CNT  32
#घोषणा FNIC_MAX_SG_DESC_CNT        256     /* Maximum descriptors per sgl */
#घोषणा FNIC_SG_DESC_ALIGN          16      /* Descriptor address alignment */

काष्ठा host_sg_desc अणु
	__le64 addr;
	__le32 len;
	u32 _resvd;
पूर्ण;

काष्ठा fnic_dflt_sgl_list अणु
	काष्ठा host_sg_desc sg_desc[FNIC_DFLT_SG_DESC_CNT];
पूर्ण;

काष्ठा fnic_sgl_list अणु
	काष्ठा host_sg_desc sg_desc[FNIC_MAX_SG_DESC_CNT];
पूर्ण;

क्रमागत fnic_sgl_list_type अणु
	FNIC_SGL_CACHE_DFLT = 0,  /* cache with शेष size sgl */
	FNIC_SGL_CACHE_MAX,       /* cache with max size sgl */
	FNIC_SGL_NUM_CACHES       /* number of sgl caches */
पूर्ण;

क्रमागत fnic_ioreq_state अणु
	FNIC_IOREQ_NOT_INITED = 0,
	FNIC_IOREQ_CMD_PENDING,
	FNIC_IOREQ_ABTS_PENDING,
	FNIC_IOREQ_ABTS_COMPLETE,
	FNIC_IOREQ_CMD_COMPLETE,
पूर्ण;

काष्ठा fnic_io_req अणु
	काष्ठा host_sg_desc *sgl_list; /* sgl list */
	व्योम *sgl_list_alloc; /* sgl list address used क्रम मुक्त */
	dma_addr_t sense_buf_pa; /* dma address क्रम sense buffer*/
	dma_addr_t sgl_list_pa;	/* dma address क्रम sgl list */
	u16 sgl_cnt;
	u8 sgl_type; /* device DMA descriptor list type */
	u8 io_completed:1; /* set to 1 when fw completes IO */
	u32 port_id; /* remote port DID */
	अचिन्हित दीर्घ start_समय; /* in jअगरfies */
	काष्ठा completion *abts_करोne; /* completion क्रम abts */
	काष्ठा completion *dr_करोne; /* completion क्रम device reset */
पूर्ण;

क्रमागत fnic_port_speeds अणु
	DCEM_PORTSPEED_NONE = 0,
	DCEM_PORTSPEED_1G    = 1000,
	DCEM_PORTSPEED_10G   = 10000,
	DCEM_PORTSPEED_20G   = 20000,
	DCEM_PORTSPEED_25G   = 25000,
	DCEM_PORTSPEED_40G   = 40000,
	DCEM_PORTSPEED_4x10G = 41000,
	DCEM_PORTSPEED_100G  = 100000,
पूर्ण;
#पूर्ण_अगर /* _FNIC_IO_H_ */
