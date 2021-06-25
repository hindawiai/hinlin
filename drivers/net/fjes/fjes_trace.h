<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015-2016 FUJITSU LIMITED
 */

#अगर !defined(FJES_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा FJES_TRACE_H_

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fjes

/* tracepoपूर्णांकs क्रम fjes_hw.c */

TRACE_EVENT(fjes_hw_issue_request_command,
	TP_PROTO(जोड़ REG_CR *cr, जोड़ REG_CS *cs, पूर्णांक समयout,
		 क्रमागत fjes_dev_command_response_e ret),
	TP_ARGS(cr, cs, समयout, ret),
	TP_STRUCT__entry(
		__field(u16, cr_req)
		__field(u8, cr_error)
		__field(u16, cr_err_info)
		__field(u8, cr_req_start)
		__field(u16, cs_req)
		__field(u8, cs_busy)
		__field(u8, cs_complete)
		__field(पूर्णांक, समयout)
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		__entry->cr_req = cr->bits.req_code;
		__entry->cr_error = cr->bits.error;
		__entry->cr_err_info = cr->bits.err_info;
		__entry->cr_req_start = cr->bits.req_start;
		__entry->cs_req = cs->bits.req_code;
		__entry->cs_busy = cs->bits.busy;
		__entry->cs_complete = cs->bits.complete;
		__entry->समयout = समयout;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("CR=[req=%04x, error=%u, err_info=%04x, req_start=%u], CS=[req=%04x, busy=%u, complete=%u], timeout=%d, ret=%d",
		  __entry->cr_req, __entry->cr_error, __entry->cr_err_info,
		  __entry->cr_req_start, __entry->cs_req, __entry->cs_busy,
		  __entry->cs_complete, __entry->समयout, __entry->ret)
);

TRACE_EVENT(fjes_hw_request_info,
	TP_PROTO(काष्ठा fjes_hw *hw, जोड़ fjes_device_command_res *res_buf),
	TP_ARGS(hw, res_buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, code)
		__dynamic_array(u8, zone, hw->max_epid)
		__dynamic_array(u8, status, hw->max_epid)
	),
	TP_fast_assign(
		पूर्णांक x;

		__entry->length = res_buf->info.length;
		__entry->code = res_buf->info.code;
		क्रम (x = 0; x < hw->max_epid; x++) अणु
			*((u8 *)__get_dynamic_array(zone) + x) =
					res_buf->info.info[x].zone;
			*((u8 *)__get_dynamic_array(status) + x) =
					res_buf->info.info[x].es_status;
		पूर्ण
	),
	TP_prपूर्णांकk("res_buf=[length=%d, code=%d, es_zones=%s, es_status=%s]",
		  __entry->length, __entry->code,
		  __prपूर्णांक_array(__get_dynamic_array(zone),
				__get_dynamic_array_len(zone) / माप(u8),
				माप(u8)),
		  __prपूर्णांक_array(__get_dynamic_array(status),
				__get_dynamic_array_len(status) / माप(u8),
				माप(u8)))
);

TRACE_EVENT(fjes_hw_request_info_err,
	TP_PROTO(अक्षर *err),
	TP_ARGS(err),
	TP_STRUCT__entry(
		__string(err, err)
	),
	TP_fast_assign(
		__assign_str(err, err);
	),
	TP_prपूर्णांकk("%s", __get_str(err))
);

TRACE_EVENT(fjes_hw_रेजिस्टर_buff_addr_req,
	TP_PROTO(जोड़ fjes_device_command_req *req_buf,
		 काष्ठा ep_share_mem_info *buf_pair),
	TP_ARGS(req_buf, buf_pair),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, epid)
		__field(u64, tx)
		__field(माप_प्रकार,	tx_size)
		__field(u64, rx)
		__field(माप_प्रकार,	rx_size)
	),
	TP_fast_assign(
		व्योम *tx, *rx;

		tx = (व्योम *)buf_pair->tx.buffer;
		rx = (व्योम *)buf_pair->rx.buffer;
		__entry->length = req_buf->share_buffer.length;
		__entry->epid = req_buf->share_buffer.epid;
		__entry->tx_size = buf_pair->tx.size;
		__entry->rx_size = buf_pair->rx.size;
		__entry->tx = page_to_phys(vदो_स्मृति_to_page(tx)) +
				offset_in_page(tx);
		__entry->rx = page_to_phys(vदो_स्मृति_to_page(rx)) +
				offset_in_page(rx);
	),
	TP_prपूर्णांकk("req_buf=[length=%d, epid=%d], TX=[phy=0x%016llx, size=%zu], RX=[phy=0x%016llx, size=%zu]",
		  __entry->length, __entry->epid, __entry->tx, __entry->tx_size,
		  __entry->rx, __entry->rx_size)
);

TRACE_EVENT(fjes_hw_रेजिस्टर_buff_addr,
	TP_PROTO(जोड़ fjes_device_command_res *res_buf, पूर्णांक समयout),
	TP_ARGS(res_buf, समयout),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, code)
		__field(पूर्णांक, समयout)
	),
	TP_fast_assign(
		__entry->length = res_buf->share_buffer.length;
		__entry->code = res_buf->share_buffer.code;
		__entry->समयout = समयout;
	),
	TP_prपूर्णांकk("res_buf=[length=%d, code=%d], timeout=%d",
		  __entry->length, __entry->code, __entry->समयout)
);

TRACE_EVENT(fjes_hw_रेजिस्टर_buff_addr_err,
	TP_PROTO(अक्षर *err),
	TP_ARGS(err),
	TP_STRUCT__entry(
		__string(err, err)
	),
	TP_fast_assign(
		__assign_str(err, err);
	),
	TP_prपूर्णांकk("%s", __get_str(err))
);

TRACE_EVENT(fjes_hw_unरेजिस्टर_buff_addr_req,
	TP_PROTO(जोड़ fjes_device_command_req *req_buf),
	TP_ARGS(req_buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, epid)
	),
	TP_fast_assign(
		__entry->length = req_buf->unshare_buffer.length;
		__entry->epid = req_buf->unshare_buffer.epid;
	),
	TP_prपूर्णांकk("req_buf=[length=%d, epid=%d]",
		  __entry->length, __entry->epid)
);

TRACE_EVENT(fjes_hw_unरेजिस्टर_buff_addr,
	TP_PROTO(जोड़ fjes_device_command_res *res_buf, पूर्णांक समयout),
	TP_ARGS(res_buf, समयout),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, code)
		__field(पूर्णांक, समयout)
	),
	TP_fast_assign(
		__entry->length = res_buf->unshare_buffer.length;
		__entry->code = res_buf->unshare_buffer.code;
		__entry->समयout = समयout;
	),
	TP_prपूर्णांकk("res_buf=[length=%d, code=%d], timeout=%d",
		  __entry->length, __entry->code, __entry->समयout)
);

TRACE_EVENT(fjes_hw_unरेजिस्टर_buff_addr_err,
	TP_PROTO(अक्षर *err),
	TP_ARGS(err),
	TP_STRUCT__entry(
		__string(err, err)
	),
	TP_fast_assign(
		__assign_str(err, err);
	),
	TP_prपूर्णांकk("%s", __get_str(err))
);

TRACE_EVENT(fjes_hw_start_debug_req,
	TP_PROTO(जोड़ fjes_device_command_req *req_buf),
	TP_ARGS(req_buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, mode)
		__field(phys_addr_t, buffer)
	),
	TP_fast_assign(
		__entry->length = req_buf->start_trace.length;
		__entry->mode = req_buf->start_trace.mode;
		__entry->buffer = req_buf->start_trace.buffer[0];
	),
	TP_prपूर्णांकk("req_buf=[length=%d, mode=%d, buffer=%pap]",
		  __entry->length, __entry->mode, &__entry->buffer)
);

TRACE_EVENT(fjes_hw_start_debug,
	TP_PROTO(जोड़ fjes_device_command_res *res_buf),
	TP_ARGS(res_buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, code)
	),
	TP_fast_assign(
		__entry->length = res_buf->start_trace.length;
		__entry->code = res_buf->start_trace.code;
	),
	TP_prपूर्णांकk("res_buf=[length=%d, code=%d]", __entry->length, __entry->code)
);

TRACE_EVENT(fjes_hw_start_debug_err,
	TP_PROTO(अक्षर *err),
	TP_ARGS(err),
	TP_STRUCT__entry(
		 __string(err, err)
	),
	TP_fast_assign(
		__assign_str(err, err)
	),
	TP_prपूर्णांकk("%s", __get_str(err))
);

TRACE_EVENT(fjes_hw_stop_debug,
	TP_PROTO(जोड़ fjes_device_command_res *res_buf),
	TP_ARGS(res_buf),
	TP_STRUCT__entry(
		__field(पूर्णांक, length)
		__field(पूर्णांक, code)
	),
	TP_fast_assign(
		__entry->length = res_buf->stop_trace.length;
		__entry->code = res_buf->stop_trace.code;
	),
	TP_prपूर्णांकk("res_buf=[length=%d, code=%d]", __entry->length, __entry->code)
);

TRACE_EVENT(fjes_hw_stop_debug_err,
	TP_PROTO(अक्षर *err),
	TP_ARGS(err),
	TP_STRUCT__entry(
		 __string(err, err)
	),
	TP_fast_assign(
		__assign_str(err, err)
	),
	TP_prपूर्णांकk("%s", __get_str(err))
);

/* tracepoपूर्णांकs क्रम fjes_मुख्य.c */

TRACE_EVENT(fjes_txrx_stop_req_irq_pre,
	TP_PROTO(काष्ठा fjes_hw *hw, पूर्णांक src_epid,
		 क्रमागत ep_partner_status status),
	TP_ARGS(hw, src_epid, status),
	TP_STRUCT__entry(
		__field(पूर्णांक, src_epid)
		__field(क्रमागत ep_partner_status, status)
		__field(u8, ep_status)
		__field(अचिन्हित दीर्घ, txrx_stop_req_bit)
		__field(u16, rx_status)
	),
	TP_fast_assign(
		__entry->src_epid = src_epid;
		__entry->status = status;
		__entry->ep_status = hw->hw_info.share->ep_status[src_epid];
		__entry->txrx_stop_req_bit = hw->txrx_stop_req_bit;
		__entry->rx_status =
			hw->ep_shm_info[src_epid].tx.info->v1i.rx_status;
	),
	TP_prपूर्णांकk("epid=%d, partner_status=%d, ep_status=%x, txrx_stop_req_bit=%016lx, tx.rx_status=%08x",
		  __entry->src_epid, __entry->status, __entry->ep_status,
		  __entry->txrx_stop_req_bit, __entry->rx_status)
);

TRACE_EVENT(fjes_txrx_stop_req_irq_post,
	TP_PROTO(काष्ठा fjes_hw *hw, पूर्णांक src_epid),
	TP_ARGS(hw, src_epid),
	TP_STRUCT__entry(
		__field(पूर्णांक, src_epid)
		__field(u8, ep_status)
		__field(अचिन्हित दीर्घ, txrx_stop_req_bit)
		__field(u16, rx_status)
	),
	TP_fast_assign(
		__entry->src_epid = src_epid;
		__entry->ep_status = hw->hw_info.share->ep_status[src_epid];
		__entry->txrx_stop_req_bit = hw->txrx_stop_req_bit;
		__entry->rx_status = hw->ep_shm_info[src_epid].tx.info->v1i.rx_status;
	),
	TP_prपूर्णांकk("epid=%d, ep_status=%x, txrx_stop_req_bit=%016lx, tx.rx_status=%08x",
		  __entry->src_epid, __entry->ep_status,
		  __entry->txrx_stop_req_bit, __entry->rx_status)
);

TRACE_EVENT(fjes_stop_req_irq_pre,
	TP_PROTO(काष्ठा fjes_hw *hw, पूर्णांक src_epid,
		 क्रमागत ep_partner_status status),
	TP_ARGS(hw, src_epid, status),
	TP_STRUCT__entry(
		__field(पूर्णांक, src_epid)
		__field(क्रमागत ep_partner_status, status)
		__field(u8, ep_status)
		__field(अचिन्हित दीर्घ, txrx_stop_req_bit)
		__field(u16, rx_status)
	),
	TP_fast_assign(
		__entry->src_epid = src_epid;
		__entry->status = status;
		__entry->ep_status = hw->hw_info.share->ep_status[src_epid];
		__entry->txrx_stop_req_bit = hw->txrx_stop_req_bit;
		__entry->rx_status =
			hw->ep_shm_info[src_epid].tx.info->v1i.rx_status;
	),
	TP_prपूर्णांकk("epid=%d, partner_status=%d, ep_status=%x, txrx_stop_req_bit=%016lx, tx.rx_status=%08x",
		  __entry->src_epid, __entry->status, __entry->ep_status,
		  __entry->txrx_stop_req_bit, __entry->rx_status)
);

TRACE_EVENT(fjes_stop_req_irq_post,
	TP_PROTO(काष्ठा fjes_hw *hw, पूर्णांक src_epid),
	TP_ARGS(hw, src_epid),
	TP_STRUCT__entry(
		__field(पूर्णांक, src_epid)
		__field(u8, ep_status)
		__field(अचिन्हित दीर्घ, txrx_stop_req_bit)
		__field(u16, rx_status)
	),
	TP_fast_assign(
		__entry->src_epid = src_epid;
		__entry->ep_status = hw->hw_info.share->ep_status[src_epid];
		__entry->txrx_stop_req_bit = hw->txrx_stop_req_bit;
		__entry->rx_status =
			hw->ep_shm_info[src_epid].tx.info->v1i.rx_status;
	),
	TP_prपूर्णांकk("epid=%d, ep_status=%x, txrx_stop_req_bit=%016lx, tx.rx_status=%08x",
		  __entry->src_epid, __entry->ep_status,
		  __entry->txrx_stop_req_bit, __entry->rx_status)
);

#पूर्ण_अगर /* FJES_TRACE_H_ */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH ../../../drivers/net/fjes
#घोषणा TRACE_INCLUDE_खाता fjes_trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
