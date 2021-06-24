<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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
#अगर_अघोषित __CHIOCTL_H__
#घोषणा __CHIOCTL_H__

/*
 * Ioctl commands specअगरic to this driver.
 */
क्रमागत अणु
	CHELSIO_GETMTUTAB 		= 1029,
	CHELSIO_SETMTUTAB 		= 1030,
	CHELSIO_SET_PM 			= 1032,
	CHELSIO_GET_PM			= 1033,
	CHELSIO_GET_MEM			= 1038,
	CHELSIO_LOAD_FW			= 1041,
	CHELSIO_SET_TRACE_FILTER	= 1044,
	CHELSIO_SET_QSET_PARAMS		= 1045,
	CHELSIO_GET_QSET_PARAMS		= 1046,
	CHELSIO_SET_QSET_NUM		= 1047,
	CHELSIO_GET_QSET_NUM		= 1048,
पूर्ण;

काष्ठा ch_reg अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t val;
पूर्ण;

काष्ठा ch_cntxt अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t cntxt_type;
	uपूर्णांक32_t cntxt_id;
	uपूर्णांक32_t data[4];
पूर्ण;

/* context types */
क्रमागत अणु CNTXT_TYPE_EGRESS, CNTXT_TYPE_FL, CNTXT_TYPE_RSP, CNTXT_TYPE_CQ पूर्ण;

काष्ठा ch_desc अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t queue_num;
	uपूर्णांक32_t idx;
	uपूर्णांक32_t size;
	uपूर्णांक8_t data[128];
पूर्ण;

काष्ठा ch_mem_range अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t mem_id;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t len;
	uपूर्णांक32_t version;
	uपूर्णांक8_t buf[];
पूर्ण;

काष्ठा ch_qset_params अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t qset_idx;
	पूर्णांक32_t txq_size[3];
	पूर्णांक32_t rspq_size;
	पूर्णांक32_t fl_size[2];
	पूर्णांक32_t पूर्णांकr_lat;
	पूर्णांक32_t polling;
	पूर्णांक32_t lro;
	पूर्णांक32_t cong_thres;
	पूर्णांक32_t  vector;
	पूर्णांक32_t  qnum;
पूर्ण;

काष्ठा ch_pktsched_params अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक8_t sched;
	uपूर्णांक8_t idx;
	uपूर्णांक8_t min;
	uपूर्णांक8_t max;
	uपूर्णांक8_t binding;
पूर्ण;

#अगर_अघोषित TCB_SIZE
# define TCB_SIZE   128
#पूर्ण_अगर

/* TCB size in 32-bit words */
#घोषणा TCB_WORDS (TCB_SIZE / 4)

क्रमागत अणु MEM_CM, MEM_PMRX, MEM_PMTX पूर्ण;	/* ch_mem_range.mem_id values */

काष्ठा ch_mtus अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t nmtus;
	uपूर्णांक16_t mtus[NMTUS];
पूर्ण;

काष्ठा ch_pm अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t tx_pg_sz;
	uपूर्णांक32_t tx_num_pg;
	uपूर्णांक32_t rx_pg_sz;
	uपूर्णांक32_t rx_num_pg;
	uपूर्णांक32_t pm_total;
पूर्ण;

काष्ठा ch_tcam अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t tcam_size;
	uपूर्णांक32_t nservers;
	uपूर्णांक32_t nroutes;
	uपूर्णांक32_t nfilters;
पूर्ण;

काष्ठा ch_tcb अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t tcb_index;
	uपूर्णांक32_t tcb_data[TCB_WORDS];
पूर्ण;

काष्ठा ch_tcam_word अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t buf[3];
पूर्ण;

काष्ठा ch_trace अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t sip;
	uपूर्णांक32_t sip_mask;
	uपूर्णांक32_t dip;
	uपूर्णांक32_t dip_mask;
	uपूर्णांक16_t sport;
	uपूर्णांक16_t sport_mask;
	uपूर्णांक16_t dport;
	uपूर्णांक16_t dport_mask;
	uपूर्णांक32_t vlan:12;
	uपूर्णांक32_t vlan_mask:12;
	uपूर्णांक32_t पूर्णांकf:4;
	uपूर्णांक32_t पूर्णांकf_mask:4;
	uपूर्णांक8_t proto;
	uपूर्णांक8_t proto_mask;
	uपूर्णांक8_t invert_match:1;
	uपूर्णांक8_t config_tx:1;
	uपूर्णांक8_t config_rx:1;
	uपूर्णांक8_t trace_tx:1;
	uपूर्णांक8_t trace_rx:1;
पूर्ण;

#घोषणा SIOCCHIOCTL SIOCDEVPRIVATE

#पूर्ण_अगर
