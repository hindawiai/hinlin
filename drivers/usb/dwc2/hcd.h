<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * hcd.h - DesignWare HS OTG Controller host-mode declarations
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_अघोषित __DWC2_HCD_H__
#घोषणा __DWC2_HCD_H__

/*
 * This file contains the काष्ठाures, स्थिरants, and पूर्णांकerfaces क्रम the
 * Host Contoller Driver (HCD)
 *
 * The Host Controller Driver (HCD) is responsible क्रम translating requests
 * from the USB Driver पूर्णांकo the appropriate actions on the DWC_otg controller.
 * It isolates the USBD from the specअगरics of the controller by providing an
 * API to the USBD.
 */

काष्ठा dwc2_qh;

/**
 * काष्ठा dwc2_host_chan - Software host channel descriptor
 *
 * @hc_num:             Host channel number, used क्रम रेजिस्टर address lookup
 * @dev_addr:           Address of the device
 * @ep_num:             Endpoपूर्णांक of the device
 * @ep_is_in:           Endpoपूर्णांक direction
 * @speed:              Device speed. One of the following values:
 *                       - USB_SPEED_LOW
 *                       - USB_SPEED_FULL
 *                       - USB_SPEED_HIGH
 * @ep_type:            Endpoपूर्णांक type. One of the following values:
 *                       - USB_ENDPOINT_XFER_CONTROL: 0
 *                       - USB_ENDPOINT_XFER_ISOC:    1
 *                       - USB_ENDPOINT_XFER_BULK:    2
 *                       - USB_ENDPOINT_XFER_INTR:    3
 * @max_packet:         Max packet size in bytes
 * @data_pid_start:     PID क्रम initial transaction.
 *                       0: DATA0
 *                       1: DATA2
 *                       2: DATA1
 *                       3: MDATA (non-Control EP),
 *                          SETUP (Control EP)
 * @multi_count:        Number of additional periodic transactions per
 *                      (micro)frame
 * @xfer_buf:           Poपूर्णांकer to current transfer buffer position
 * @xfer_dma:           DMA address of xfer_buf
 * @align_buf:          In Buffer DMA mode this will be used अगर xfer_buf is not
 *                      DWORD aligned
 * @xfer_len:           Total number of bytes to transfer
 * @xfer_count:         Number of bytes transferred so far
 * @start_pkt_count:    Packet count at start of transfer
 * @xfer_started:       True अगर the transfer has been started
 * @करो_ping:            True अगर a PING request should be issued on this channel
 * @error_state:        True अगर the error count क्रम this transaction is non-zero
 * @halt_on_queue:      True अगर this channel should be halted the next समय a
 *                      request is queued क्रम the channel. This is necessary in
 *                      slave mode अगर no request queue space is available when
 *                      an attempt is made to halt the channel.
 * @halt_pending:       True अगर the host channel has been halted, but the core
 *                      is not finished flushing queued requests
 * @करो_split:           Enable split क्रम the channel
 * @complete_split:     Enable complete split
 * @hub_addr:           Address of high speed hub क्रम the split
 * @hub_port:           Port of the low/full speed device क्रम the split
 * @xact_pos:           Split transaction position. One of the following values:
 *                       - DWC2_HCSPLT_XACTPOS_MID
 *                       - DWC2_HCSPLT_XACTPOS_BEGIN
 *                       - DWC2_HCSPLT_XACTPOS_END
 *                       - DWC2_HCSPLT_XACTPOS_ALL
 * @requests:           Number of requests issued क्रम this channel since it was
 *                      asचिन्हित to the current transfer (not counting PINGs)
 * @schinfo:            Scheduling micro-frame biपंचांगap
 * @ntd:                Number of transfer descriptors क्रम the transfer
 * @halt_status:        Reason क्रम halting the host channel
 * @hcपूर्णांक:               Contents of the HCINT रेजिस्टर when the पूर्णांकerrupt came
 * @qh:                 QH क्रम the transfer being processed by this channel
 * @hc_list_entry:      For linking to list of host channels
 * @desc_list_addr:     Current QH's descriptor list DMA address
 * @desc_list_sz:       Current QH's descriptor list size
 * @split_order_list_entry: List entry क्रम keeping track of the order of splits
 *
 * This काष्ठाure represents the state of a single host channel when acting in
 * host mode. It contains the data items needed to transfer packets to an
 * endpoपूर्णांक via a host channel.
 */
काष्ठा dwc2_host_chan अणु
	u8 hc_num;

	अचिन्हित dev_addr:7;
	अचिन्हित ep_num:4;
	अचिन्हित ep_is_in:1;
	अचिन्हित speed:4;
	अचिन्हित ep_type:2;
	अचिन्हित max_packet:11;
	अचिन्हित data_pid_start:2;
#घोषणा DWC2_HC_PID_DATA0	TSIZ_SC_MC_PID_DATA0
#घोषणा DWC2_HC_PID_DATA2	TSIZ_SC_MC_PID_DATA2
#घोषणा DWC2_HC_PID_DATA1	TSIZ_SC_MC_PID_DATA1
#घोषणा DWC2_HC_PID_MDATA	TSIZ_SC_MC_PID_MDATA
#घोषणा DWC2_HC_PID_SETUP	TSIZ_SC_MC_PID_SETUP

	अचिन्हित multi_count:2;

	u8 *xfer_buf;
	dma_addr_t xfer_dma;
	dma_addr_t align_buf;
	u32 xfer_len;
	u32 xfer_count;
	u16 start_pkt_count;
	u8 xfer_started;
	u8 करो_ping;
	u8 error_state;
	u8 halt_on_queue;
	u8 halt_pending;
	u8 करो_split;
	u8 complete_split;
	u8 hub_addr;
	u8 hub_port;
	u8 xact_pos;
#घोषणा DWC2_HCSPLT_XACTPOS_MID	HCSPLT_XACTPOS_MID
#घोषणा DWC2_HCSPLT_XACTPOS_END	HCSPLT_XACTPOS_END
#घोषणा DWC2_HCSPLT_XACTPOS_BEGIN HCSPLT_XACTPOS_BEGIN
#घोषणा DWC2_HCSPLT_XACTPOS_ALL	HCSPLT_XACTPOS_ALL

	u8 requests;
	u8 schinfo;
	u16 ntd;
	क्रमागत dwc2_halt_status halt_status;
	u32 hcपूर्णांक;
	काष्ठा dwc2_qh *qh;
	काष्ठा list_head hc_list_entry;
	dma_addr_t desc_list_addr;
	u32 desc_list_sz;
	काष्ठा list_head split_order_list_entry;
पूर्ण;

काष्ठा dwc2_hcd_pipe_info अणु
	u8 dev_addr;
	u8 ep_num;
	u8 pipe_type;
	u8 pipe_dir;
	u16 maxp;
	u16 maxp_mult;
पूर्ण;

काष्ठा dwc2_hcd_iso_packet_desc अणु
	u32 offset;
	u32 length;
	u32 actual_length;
	u32 status;
पूर्ण;

काष्ठा dwc2_qtd;

काष्ठा dwc2_hcd_urb अणु
	व्योम *priv;
	काष्ठा dwc2_qtd *qtd;
	व्योम *buf;
	dma_addr_t dma;
	व्योम *setup_packet;
	dma_addr_t setup_dma;
	u32 length;
	u32 actual_length;
	u32 status;
	u32 error_count;
	u32 packet_count;
	u32 flags;
	u16 पूर्णांकerval;
	काष्ठा dwc2_hcd_pipe_info pipe_info;
	काष्ठा dwc2_hcd_iso_packet_desc iso_descs[];
पूर्ण;

/* Phases क्रम control transfers */
क्रमागत dwc2_control_phase अणु
	DWC2_CONTROL_SETUP,
	DWC2_CONTROL_DATA,
	DWC2_CONTROL_STATUS,
पूर्ण;

/* Transaction types */
क्रमागत dwc2_transaction_type अणु
	DWC2_TRANSACTION_NONE,
	DWC2_TRANSACTION_PERIODIC,
	DWC2_TRANSACTION_NON_PERIODIC,
	DWC2_TRANSACTION_ALL,
पूर्ण;

/* The number of elements per LS biपंचांगap (per port on multi_tt) */
#घोषणा DWC2_ELEMENTS_PER_LS_BITMAP	DIV_ROUND_UP(DWC2_LS_SCHEDULE_SLICES, \
						     BITS_PER_LONG)

/**
 * काष्ठा dwc2_tt - dwc2 data associated with a usb_tt
 *
 * @refcount:           Number of Queue Heads (QHs) holding a reference.
 * @usb_tt:             Poपूर्णांकer back to the official usb_tt.
 * @periodic_biपंचांगaps:   Biपंचांगap क्रम which parts of the 1ms frame are accounted
 *                      क्रम alपढ़ोy.  Each is DWC2_ELEMENTS_PER_LS_BITMAP
 *			elements (so माप(दीर्घ) बार that in bytes).
 *
 * This काष्ठाure is stored in the hcpriv of the official usb_tt.
 */
काष्ठा dwc2_tt अणु
	पूर्णांक refcount;
	काष्ठा usb_tt *usb_tt;
	अचिन्हित दीर्घ periodic_biपंचांगaps[];
पूर्ण;

/**
 * काष्ठा dwc2_hs_transfer_समय - Info about a transfer on the high speed bus.
 *
 * @start_schedule_us:  The start समय on the मुख्य bus schedule.  Note that
 *                         the मुख्य bus schedule is tightly packed and this
 *			   समय should be पूर्णांकerpreted as tightly packed (so
 *			   uFrame 0 starts at 0 us, uFrame 1 starts at 100 us
 *			   instead of 125 us).
 * @duration_us:           How दीर्घ this transfer goes.
 */

काष्ठा dwc2_hs_transfer_समय अणु
	u32 start_schedule_us;
	u16 duration_us;
पूर्ण;

/**
 * काष्ठा dwc2_qh - Software queue head काष्ठाure
 *
 * @hsotg:              The HCD state काष्ठाure क्रम the DWC OTG controller
 * @ep_type:            Endpoपूर्णांक type. One of the following values:
 *                       - USB_ENDPOINT_XFER_CONTROL
 *                       - USB_ENDPOINT_XFER_BULK
 *                       - USB_ENDPOINT_XFER_INT
 *                       - USB_ENDPOINT_XFER_ISOC
 * @ep_is_in:           Endpoपूर्णांक direction
 * @maxp:               Value from wMaxPacketSize field of Endpoपूर्णांक Descriptor
 * @maxp_mult:          Multiplier क्रम maxp
 * @dev_speed:          Device speed. One of the following values:
 *                       - USB_SPEED_LOW
 *                       - USB_SPEED_FULL
 *                       - USB_SPEED_HIGH
 * @data_toggle:        Determines the PID of the next data packet क्रम
 *                      non-controltransfers. Ignored क्रम control transfers.
 *                      One of the following values:
 *                       - DWC2_HC_PID_DATA0
 *                       - DWC2_HC_PID_DATA1
 * @ping_state:         Ping state
 * @करो_split:           Full/low speed endpoपूर्णांक on high-speed hub requires split
 * @td_first:           Index of first activated isochronous transfer descriptor
 * @td_last:            Index of last activated isochronous transfer descriptor
 * @host_us:            Bandwidth in microseconds per transfer as seen by host
 * @device_us:          Bandwidth in microseconds per transfer as seen by device
 * @host_पूर्णांकerval:      Interval between transfers as seen by the host.  If
 *                      the host is high speed and the device is low speed this
 *                      will be 8 बार device पूर्णांकerval.
 * @device_पूर्णांकerval:    Interval between transfers as seen by the device.
 *                      पूर्णांकerval.
 * @next_active_frame:  (Micro)frame _beक्रमe_ we next need to put something on
 *                      the bus.  We'll move the qh to active here.  If the
 *                      host is in high speed mode this will be a uframe.  If
 *                      the host is in low speed mode this will be a full frame.
 * @start_active_frame: If we are partway through a split transfer, this will be
 *			what next_active_frame was when we started.  Otherwise
 *			it should always be the same as next_active_frame.
 * @num_hs_transfers:   Number of transfers in hs_transfers.
 *                      Normally this is 1 but can be more than one क्रम splits.
 *                      Always >= 1 unless the host is in low/full speed mode.
 * @hs_transfers:       Transfers that are scheduled as seen by the high speed
 *                      bus.  Not used अगर host is in low or full speed mode (but
 *                      note that it IS USED अगर the device is low or full speed
 *                      as दीर्घ as the HOST is in high speed mode).
 * @ls_start_schedule_slice: Start समय (in slices) on the low speed bus
 *                           schedule that's being used by this device.  This
 *			     will be on the periodic_biपंचांगap in a
 *                           "struct dwc2_tt".  Not used अगर this device is high
 *                           speed.  Note that this is in "schedule slice" which
 *                           is tightly packed.
 * @ntd:                Actual number of transfer descriptors in a list
 * @dw_align_buf:       Used instead of original buffer अगर its physical address
 *                      is not dword-aligned
 * @dw_align_buf_dma:   DMA address क्रम dw_align_buf
 * @qtd_list:           List of QTDs क्रम this QH
 * @channel:            Host channel currently processing transfers क्रम this QH
 * @qh_list_entry:      Entry क्रम QH in either the periodic or non-periodic
 *                      schedule
 * @desc_list:          List of transfer descriptors
 * @desc_list_dma:      Physical address of desc_list
 * @desc_list_sz:       Size of descriptors list
 * @n_bytes:            Xfer Bytes array. Each element corresponds to a transfer
 *                      descriptor and indicates original XferSize value क्रम the
 *                      descriptor
 * @unreserve_समयr:    Timer क्रम releasing periodic reservation.
 * @रुको_समयr:         Timer used to रुको beक्रमe re-queuing.
 * @dwc_tt:            Poपूर्णांकer to our tt info (or शून्य अगर no tt).
 * @ttport:             Port number within our tt.
 * @tt_buffer_dirty     True अगर clear_tt_buffer_complete is pending
 * @unreserve_pending:  True अगर we planned to unreserve but haven't yet.
 * @schedule_low_speed: True अगर we have a low/full speed component (either the
 *			host is in low/full speed mode or करो_split).
 * @want_रुको:          We should रुको beक्रमe re-queuing; only matters क्रम non-
 *                      periodic transfers and is ignored क्रम periodic ones.
 * @रुको_समयr_cancel:  Set to true to cancel the रुको_समयr.
 *
 * @tt_buffer_dirty:	True अगर EP's TT buffer is not clean.
 * A Queue Head (QH) holds the अटल अक्षरacteristics of an endpoपूर्णांक and
 * मुख्यtains a list of transfers (QTDs) क्रम that endpoपूर्णांक. A QH काष्ठाure may
 * be entered in either the non-periodic or periodic schedule.
 */
काष्ठा dwc2_qh अणु
	काष्ठा dwc2_hsotg *hsotg;
	u8 ep_type;
	u8 ep_is_in;
	u16 maxp;
	u16 maxp_mult;
	u8 dev_speed;
	u8 data_toggle;
	u8 ping_state;
	u8 करो_split;
	u8 td_first;
	u8 td_last;
	u16 host_us;
	u16 device_us;
	u16 host_पूर्णांकerval;
	u16 device_पूर्णांकerval;
	u16 next_active_frame;
	u16 start_active_frame;
	s16 num_hs_transfers;
	काष्ठा dwc2_hs_transfer_समय hs_transfers[DWC2_HS_SCHEDULE_UFRAMES];
	u32 ls_start_schedule_slice;
	u16 ntd;
	u8 *dw_align_buf;
	dma_addr_t dw_align_buf_dma;
	काष्ठा list_head qtd_list;
	काष्ठा dwc2_host_chan *channel;
	काष्ठा list_head qh_list_entry;
	काष्ठा dwc2_dma_desc *desc_list;
	dma_addr_t desc_list_dma;
	u32 desc_list_sz;
	u32 *n_bytes;
	काष्ठा समयr_list unreserve_समयr;
	काष्ठा hrसमयr रुको_समयr;
	काष्ठा dwc2_tt *dwc_tt;
	पूर्णांक ttport;
	अचिन्हित tt_buffer_dirty:1;
	अचिन्हित unreserve_pending:1;
	अचिन्हित schedule_low_speed:1;
	अचिन्हित want_रुको:1;
	अचिन्हित रुको_समयr_cancel:1;
पूर्ण;

/**
 * काष्ठा dwc2_qtd - Software queue transfer descriptor (QTD)
 *
 * @control_phase:      Current phase क्रम control transfers (Setup, Data, or
 *                      Status)
 * @in_process:         Indicates अगर this QTD is currently processed by HW
 * @data_toggle:        Determines the PID of the next data packet क्रम the
 *                      data phase of control transfers. Ignored क्रम other
 *                      transfer types. One of the following values:
 *                       - DWC2_HC_PID_DATA0
 *                       - DWC2_HC_PID_DATA1
 * @complete_split:     Keeps track of the current split type क्रम FS/LS
 *                      endpoपूर्णांकs on a HS Hub
 * @isoc_split_pos:     Position of the ISOC split in full/low speed
 * @isoc_frame_index:   Index of the next frame descriptor क्रम an isochronous
 *                      transfer. A frame descriptor describes the buffer
 *                      position and length of the data to be transferred in the
 *                      next scheduled (micro)frame of an isochronous transfer.
 *                      It also holds status क्रम that transaction. The frame
 *                      index starts at 0.
 * @isoc_split_offset:  Position of the ISOC split in the buffer क्रम the
 *                      current frame
 * @ssplit_out_xfer_count: How many bytes transferred during SSPLIT OUT
 * @error_count:        Holds the number of bus errors that have occurred क्रम
 *                      a transaction within this transfer
 * @n_desc:             Number of DMA descriptors क्रम this QTD
 * @isoc_frame_index_last: Last activated frame (packet) index, used in
 *                      descriptor DMA mode only
 * @num_naks:           Number of NAKs received on this QTD.
 * @urb:                URB क्रम this transfer
 * @qh:                 Queue head क्रम this QTD
 * @qtd_list_entry:     For linking to the QH's list of QTDs
 * @isoc_td_first:	Index of first activated isochronous transfer
 *			descriptor in Descriptor DMA mode
 * @isoc_td_last:	Index of last activated isochronous transfer
 *			descriptor in Descriptor DMA mode
 *
 * A Queue Transfer Descriptor (QTD) holds the state of a bulk, control,
 * पूर्णांकerrupt, or isochronous transfer. A single QTD is created क्रम each URB
 * (of one of these types) submitted to the HCD. The transfer associated with
 * a QTD may require one or multiple transactions.
 *
 * A QTD is linked to a Queue Head, which is entered in either the
 * non-periodic or periodic schedule क्रम execution. When a QTD is chosen क्रम
 * execution, some or all of its transactions may be executed. After
 * execution, the state of the QTD is updated. The QTD may be retired अगर all
 * its transactions are complete or अगर an error occurred. Otherwise, it
 * reमुख्यs in the schedule so more transactions can be executed later.
 */
काष्ठा dwc2_qtd अणु
	क्रमागत dwc2_control_phase control_phase;
	u8 in_process;
	u8 data_toggle;
	u8 complete_split;
	u8 isoc_split_pos;
	u16 isoc_frame_index;
	u16 isoc_split_offset;
	u16 isoc_td_last;
	u16 isoc_td_first;
	u32 ssplit_out_xfer_count;
	u8 error_count;
	u8 n_desc;
	u16 isoc_frame_index_last;
	u16 num_naks;
	काष्ठा dwc2_hcd_urb *urb;
	काष्ठा dwc2_qh *qh;
	काष्ठा list_head qtd_list_entry;
पूर्ण;

#अगर_घोषित DEBUG
काष्ठा hc_xfer_info अणु
	काष्ठा dwc2_hsotg *hsotg;
	काष्ठा dwc2_host_chan *chan;
पूर्ण;
#पूर्ण_अगर

u32 dwc2_calc_frame_पूर्णांकerval(काष्ठा dwc2_hsotg *hsotg);

/* Gets the काष्ठा usb_hcd that contains a काष्ठा dwc2_hsotg */
अटल अंतरभूत काष्ठा usb_hcd *dwc2_hsotg_to_hcd(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (काष्ठा usb_hcd *)hsotg->priv;
पूर्ण

/*
 * Inline used to disable one channel पूर्णांकerrupt. Channel पूर्णांकerrupts are
 * disabled when the channel is halted or released by the पूर्णांकerrupt handler.
 * There is no need to handle further पूर्णांकerrupts of that type until the
 * channel is re-asचिन्हित. In fact, subsequent handling may cause crashes
 * because the channel काष्ठाures are cleaned up when the channel is released.
 */
अटल अंतरभूत व्योम disable_hc_पूर्णांक(काष्ठा dwc2_hsotg *hsotg, पूर्णांक chnum, u32 पूर्णांकr)
अणु
	u32 mask = dwc2_पढ़ोl(hsotg, HCINTMSK(chnum));

	mask &= ~पूर्णांकr;
	dwc2_ग_लिखोl(hsotg, mask, HCINTMSK(chnum));
पूर्ण

व्योम dwc2_hc_cleanup(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan);
व्योम dwc2_hc_halt(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_host_chan *chan,
		  क्रमागत dwc2_halt_status halt_status);
व्योम dwc2_hc_start_transfer_ddma(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan);

/*
 * Reads HPRT0 in preparation to modअगरy. It keeps the WC bits 0 so that अगर they
 * are पढ़ो as 1, they won't clear when written back.
 */
अटल अंतरभूत u32 dwc2_पढ़ो_hprt0(काष्ठा dwc2_hsotg *hsotg)
अणु
	u32 hprt0 = dwc2_पढ़ोl(hsotg, HPRT0);

	hprt0 &= ~(HPRT0_ENA | HPRT0_CONNDET | HPRT0_ENACHG | HPRT0_OVRCURRCHG);
	वापस hprt0;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_get_ep_num(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->ep_num;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_get_pipe_type(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_type;
पूर्ण

अटल अंतरभूत u16 dwc2_hcd_get_maxp(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->maxp;
पूर्ण

अटल अंतरभूत u16 dwc2_hcd_get_maxp_mult(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->maxp_mult;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_get_dev_addr(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->dev_addr;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_isoc(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_type == USB_ENDPOINT_XFER_ISOC;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_पूर्णांक(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_type == USB_ENDPOINT_XFER_INT;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_bulk(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_type == USB_ENDPOINT_XFER_BULK;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_control(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_type == USB_ENDPOINT_XFER_CONTROL;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_in(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस pipe->pipe_dir == USB_सूची_IN;
पूर्ण

अटल अंतरभूत u8 dwc2_hcd_is_pipe_out(काष्ठा dwc2_hcd_pipe_info *pipe)
अणु
	वापस !dwc2_hcd_is_pipe_in(pipe);
पूर्ण

पूर्णांक dwc2_hcd_init(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hcd_हटाओ(काष्ठा dwc2_hsotg *hsotg);

/* Transaction Execution Functions */
क्रमागत dwc2_transaction_type dwc2_hcd_select_transactions(
						काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hcd_queue_transactions(काष्ठा dwc2_hsotg *hsotg,
				 क्रमागत dwc2_transaction_type tr_type);

/* Schedule Queue Functions */
/* Implemented in hcd_queue.c */
काष्ठा dwc2_qh *dwc2_hcd_qh_create(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_hcd_urb *urb,
					  gfp_t mem_flags);
व्योम dwc2_hcd_qh_मुक्त(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh);
पूर्णांक dwc2_hcd_qh_add(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh);
व्योम dwc2_hcd_qh_unlink(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh);
व्योम dwc2_hcd_qh_deactivate(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			    पूर्णांक sched_csplit);

व्योम dwc2_hcd_qtd_init(काष्ठा dwc2_qtd *qtd, काष्ठा dwc2_hcd_urb *urb);
पूर्णांक dwc2_hcd_qtd_add(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qtd *qtd,
		     काष्ठा dwc2_qh *qh);

/* Unlinks and मुक्तs a QTD */
अटल अंतरभूत व्योम dwc2_hcd_qtd_unlink_and_मुक्त(काष्ठा dwc2_hsotg *hsotg,
						काष्ठा dwc2_qtd *qtd,
						काष्ठा dwc2_qh *qh)
अणु
	list_del(&qtd->qtd_list_entry);
	kमुक्त(qtd);
पूर्ण

/* Descriptor DMA support functions */
व्योम dwc2_hcd_start_xfer_ddma(काष्ठा dwc2_hsotg *hsotg,
			      काष्ठा dwc2_qh *qh);
व्योम dwc2_hcd_complete_xfer_ddma(काष्ठा dwc2_hsotg *hsotg,
				 काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
					क्रमागत dwc2_halt_status halt_status);

पूर्णांक dwc2_hcd_qh_init_ddma(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			  gfp_t mem_flags);
व्योम dwc2_hcd_qh_मुक्त_ddma(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh);

/* Check अगर QH is non-periodic */
#घोषणा dwc2_qh_is_non_per(_qh_ptr_) \
	((_qh_ptr_)->ep_type == USB_ENDPOINT_XFER_BULK || \
	 (_qh_ptr_)->ep_type == USB_ENDPOINT_XFER_CONTROL)

#अगर_घोषित CONFIG_USB_DWC2_DEBUG_PERIODIC
अटल अंतरभूत bool dbg_hc(काष्ठा dwc2_host_chan *hc) अणु वापस true; पूर्ण
अटल अंतरभूत bool dbg_qh(काष्ठा dwc2_qh *qh) अणु वापस true; पूर्ण
अटल अंतरभूत bool dbg_urb(काष्ठा urb *urb) अणु वापस true; पूर्ण
अटल अंतरभूत bool dbg_perio(व्योम) अणु वापस true; पूर्ण
#अन्यथा /* !CONFIG_USB_DWC2_DEBUG_PERIODIC */
अटल अंतरभूत bool dbg_hc(काष्ठा dwc2_host_chan *hc)
अणु
	वापस hc->ep_type == USB_ENDPOINT_XFER_BULK ||
	       hc->ep_type == USB_ENDPOINT_XFER_CONTROL;
पूर्ण

अटल अंतरभूत bool dbg_qh(काष्ठा dwc2_qh *qh)
अणु
	वापस qh->ep_type == USB_ENDPOINT_XFER_BULK ||
	       qh->ep_type == USB_ENDPOINT_XFER_CONTROL;
पूर्ण

अटल अंतरभूत bool dbg_urb(काष्ठा urb *urb)
अणु
	वापस usb_pipetype(urb->pipe) == PIPE_BULK ||
	       usb_pipetype(urb->pipe) == PIPE_CONTROL;
पूर्ण

अटल अंतरभूत bool dbg_perio(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

/*
 * Returns true अगर frame1 index is greater than frame2 index. The comparison
 * is करोne modulo FRLISTEN_64_SIZE. This accounts क्रम the rollover of the
 * frame number when the max index frame number is reached.
 */
अटल अंतरभूत bool dwc2_frame_idx_num_gt(u16 fr_idx1, u16 fr_idx2)
अणु
	u16 dअगरf = fr_idx1 - fr_idx2;
	u16 sign = dअगरf & (FRLISTEN_64_SIZE >> 1);

	वापस dअगरf && !sign;
पूर्ण

/*
 * Returns true अगर frame1 is less than or equal to frame2. The comparison is
 * करोne modulo HFNUM_MAX_FRNUM. This accounts क्रम the rollover of the
 * frame number when the max frame number is reached.
 */
अटल अंतरभूत पूर्णांक dwc2_frame_num_le(u16 frame1, u16 frame2)
अणु
	वापस ((frame2 - frame1) & HFNUM_MAX_FRNUM) <= (HFNUM_MAX_FRNUM >> 1);
पूर्ण

/*
 * Returns true अगर frame1 is greater than frame2. The comparison is करोne
 * modulo HFNUM_MAX_FRNUM. This accounts क्रम the rollover of the frame
 * number when the max frame number is reached.
 */
अटल अंतरभूत पूर्णांक dwc2_frame_num_gt(u16 frame1, u16 frame2)
अणु
	वापस (frame1 != frame2) &&
	       ((frame1 - frame2) & HFNUM_MAX_FRNUM) < (HFNUM_MAX_FRNUM >> 1);
पूर्ण

/*
 * Increments frame by the amount specअगरied by inc. The addition is करोne
 * modulo HFNUM_MAX_FRNUM. Returns the incremented value.
 */
अटल अंतरभूत u16 dwc2_frame_num_inc(u16 frame, u16 inc)
अणु
	वापस (frame + inc) & HFNUM_MAX_FRNUM;
पूर्ण

अटल अंतरभूत u16 dwc2_frame_num_dec(u16 frame, u16 dec)
अणु
	वापस (frame + HFNUM_MAX_FRNUM + 1 - dec) & HFNUM_MAX_FRNUM;
पूर्ण

अटल अंतरभूत u16 dwc2_full_frame_num(u16 frame)
अणु
	वापस (frame & HFNUM_MAX_FRNUM) >> 3;
पूर्ण

अटल अंतरभूत u16 dwc2_micro_frame_num(u16 frame)
अणु
	वापस frame & 0x7;
पूर्ण

/*
 * Returns the Core Interrupt Status रेजिस्टर contents, ANDed with the Core
 * Interrupt Mask रेजिस्टर contents
 */
अटल अंतरभूत u32 dwc2_पढ़ो_core_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस dwc2_पढ़ोl(hsotg, GINTSTS) &
	       dwc2_पढ़ोl(hsotg, GINTMSK);
पूर्ण

अटल अंतरभूत u32 dwc2_hcd_urb_get_status(काष्ठा dwc2_hcd_urb *dwc2_urb)
अणु
	वापस dwc2_urb->status;
पूर्ण

अटल अंतरभूत u32 dwc2_hcd_urb_get_actual_length(
		काष्ठा dwc2_hcd_urb *dwc2_urb)
अणु
	वापस dwc2_urb->actual_length;
पूर्ण

अटल अंतरभूत u32 dwc2_hcd_urb_get_error_count(काष्ठा dwc2_hcd_urb *dwc2_urb)
अणु
	वापस dwc2_urb->error_count;
पूर्ण

अटल अंतरभूत व्योम dwc2_hcd_urb_set_iso_desc_params(
		काष्ठा dwc2_hcd_urb *dwc2_urb, पूर्णांक desc_num, u32 offset,
		u32 length)
अणु
	dwc2_urb->iso_descs[desc_num].offset = offset;
	dwc2_urb->iso_descs[desc_num].length = length;
पूर्ण

अटल अंतरभूत u32 dwc2_hcd_urb_get_iso_desc_status(
		काष्ठा dwc2_hcd_urb *dwc2_urb, पूर्णांक desc_num)
अणु
	वापस dwc2_urb->iso_descs[desc_num].status;
पूर्ण

अटल अंतरभूत u32 dwc2_hcd_urb_get_iso_desc_actual_length(
		काष्ठा dwc2_hcd_urb *dwc2_urb, पूर्णांक desc_num)
अणु
	वापस dwc2_urb->iso_descs[desc_num].actual_length;
पूर्ण

अटल अंतरभूत पूर्णांक dwc2_hcd_is_bandwidth_allocated(काष्ठा dwc2_hsotg *hsotg,
						  काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_qh *qh = ep->hcpriv;

	अगर (qh && !list_empty(&qh->qh_list_entry))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत u16 dwc2_hcd_get_ep_bandwidth(काष्ठा dwc2_hsotg *hsotg,
					    काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा dwc2_qh *qh = ep->hcpriv;

	अगर (!qh) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	वापस qh->host_us;
पूर्ण

व्योम dwc2_hcd_save_data_toggle(काष्ठा dwc2_hsotg *hsotg,
			       काष्ठा dwc2_host_chan *chan, पूर्णांक chnum,
				      काष्ठा dwc2_qtd *qtd);

/* HCD Core API */

/**
 * dwc2_handle_hcd_पूर्णांकr() - Called on every hardware पूर्णांकerrupt
 *
 * @hsotg: The DWC2 HCD
 *
 * Returns IRQ_HANDLED अगर पूर्णांकerrupt is handled
 * Return IRQ_NONE अगर पूर्णांकerrupt is not handled
 */
irqवापस_t dwc2_handle_hcd_पूर्णांकr(काष्ठा dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_stop() - Halts the DWC_otg host mode operation
 *
 * @hsotg: The DWC2 HCD
 */
व्योम dwc2_hcd_stop(काष्ठा dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_is_b_host() - Returns 1 अगर core currently is acting as B host,
 * and 0 otherwise
 *
 * @hsotg: The DWC2 HCD
 */
पूर्णांक dwc2_hcd_is_b_host(काष्ठा dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_dump_state() - Dumps hsotg state
 *
 * @hsotg: The DWC2 HCD
 *
 * NOTE: This function will be हटाओd once the peripheral controller code
 * is पूर्णांकegrated and the driver is stable
 */
व्योम dwc2_hcd_dump_state(काष्ठा dwc2_hsotg *hsotg);

/* URB पूर्णांकerface */

/* Transfer flags */
#घोषणा URB_GIVEBACK_ASAP	0x1
#घोषणा URB_SEND_ZERO_PACKET	0x2

/* Host driver callbacks */
काष्ठा dwc2_tt *dwc2_host_get_tt_info(काष्ठा dwc2_hsotg *hsotg,
				      व्योम *context, gfp_t mem_flags,
				      पूर्णांक *ttport);

व्योम dwc2_host_put_tt_info(काष्ठा dwc2_hsotg *hsotg,
			   काष्ठा dwc2_tt *dwc_tt);
पूर्णांक dwc2_host_get_speed(काष्ठा dwc2_hsotg *hsotg, व्योम *context);
व्योम dwc2_host_complete(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qtd *qtd,
			पूर्णांक status);

#पूर्ण_अगर /* __DWC2_HCD_H__ */
