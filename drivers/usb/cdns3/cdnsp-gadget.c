<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/dmi.h>

#समावेश "core.h"
#समावेश "gadget-export.h"
#समावेश "drd.h"
#समावेश "cdnsp-gadget.h"
#समावेश "cdnsp-trace.h"

अचिन्हित पूर्णांक cdnsp_port_speed(अचिन्हित पूर्णांक port_status)
अणु
	/*Detect gadget speed based on PORTSC रेजिस्टर*/
	अगर (DEV_SUPERSPEEDPLUS(port_status))
		वापस USB_SPEED_SUPER_PLUS;
	अन्यथा अगर (DEV_SUPERSPEED(port_status))
		वापस USB_SPEED_SUPER;
	अन्यथा अगर (DEV_HIGHSPEED(port_status))
		वापस USB_SPEED_HIGH;
	अन्यथा अगर (DEV_FULLSPEED(port_status))
		वापस USB_SPEED_FULL;

	/* If device is detached then speed will be USB_SPEED_UNKNOWN.*/
	वापस USB_SPEED_UNKNOWN;
पूर्ण

/*
 * Given a port state, this function वापसs a value that would result in the
 * port being in the same state, अगर the value was written to the port status
 * control रेजिस्टर.
 * Save Read Only (RO) bits and save पढ़ो/ग_लिखो bits where
 * writing a 0 clears the bit and writing a 1 sets the bit (RWS).
 * For all other types (RW1S, RW1CS, RW, and RZ), writing a '0' has no effect.
 */
u32 cdnsp_port_state_to_neutral(u32 state)
अणु
	/* Save पढ़ो-only status and port state. */
	वापस (state & CDNSP_PORT_RO) | (state & CDNSP_PORT_RWS);
पूर्ण

/**
 * Find the offset of the extended capabilities with capability ID id.
 * @base: PCI MMIO रेजिस्टरs base address.
 * @start: Address at which to start looking, (0 or HCC_PARAMS to start at
 *         beginning of list)
 * @id: Extended capability ID to search क्रम.
 *
 * Returns the offset of the next matching extended capability काष्ठाure.
 * Some capabilities can occur several बार,
 * e.g., the EXT_CAPS_PROTOCOL, and this provides a way to find them all.
 */
पूर्णांक cdnsp_find_next_ext_cap(व्योम __iomem *base, u32 start, पूर्णांक id)
अणु
	u32 offset = start;
	u32 next;
	u32 val;

	अगर (!start || start == HCC_PARAMS_OFFSET) अणु
		val = पढ़ोl(base + HCC_PARAMS_OFFSET);
		अगर (val == ~0)
			वापस 0;

		offset = HCC_EXT_CAPS(val) << 2;
		अगर (!offset)
			वापस 0;
	पूर्ण;

	करो अणु
		val = पढ़ोl(base + offset);
		अगर (val == ~0)
			वापस 0;

		अगर (EXT_CAPS_ID(val) == id && offset != start)
			वापस offset;

		next = EXT_CAPS_NEXT(val);
		offset += next << 2;
	पूर्ण जबतक (next);

	वापस 0;
पूर्ण

व्योम cdnsp_set_link_state(काष्ठा cdnsp_device *pdev,
			  __le32 __iomem *port_regs,
			  u32 link_state)
अणु
	पूर्णांक port_num = 0xFF;
	u32 temp;

	temp = पढ़ोl(port_regs);
	temp = cdnsp_port_state_to_neutral(temp);
	temp |= PORT_WKCONN_E | PORT_WKDISC_E;
	ग_लिखोl(temp, port_regs);

	temp &= ~PORT_PLS_MASK;
	temp |= PORT_LINK_STROBE | link_state;

	अगर (pdev->active_port)
		port_num = pdev->active_port->port_num;

	trace_cdnsp_handle_port_status(port_num, पढ़ोl(port_regs));
	ग_लिखोl(temp, port_regs);
	trace_cdnsp_link_state_changed(port_num, पढ़ोl(port_regs));
पूर्ण

अटल व्योम cdnsp_disable_port(काष्ठा cdnsp_device *pdev,
			       __le32 __iomem *port_regs)
अणु
	u32 temp = cdnsp_port_state_to_neutral(पढ़ोl(port_regs));

	ग_लिखोl(temp | PORT_PED, port_regs);
पूर्ण

अटल व्योम cdnsp_clear_port_change_bit(काष्ठा cdnsp_device *pdev,
					__le32 __iomem *port_regs)
अणु
	u32 portsc = पढ़ोl(port_regs);

	ग_लिखोl(cdnsp_port_state_to_neutral(portsc) |
	       (portsc & PORT_CHANGE_BITS), port_regs);
पूर्ण

अटल व्योम cdnsp_set_chicken_bits_2(काष्ठा cdnsp_device *pdev, u32 bit)
अणु
	__le32 __iomem *reg;
	व्योम __iomem *base;
	u32 offset = 0;

	base = &pdev->cap_regs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, offset, D_XEC_PRE_REGS_CAP);
	reg = base + offset + REG_CHICKEN_BITS_2_OFFSET;

	bit = पढ़ोl(reg) | bit;
	ग_लिखोl(bit, reg);
पूर्ण

अटल व्योम cdnsp_clear_chicken_bits_2(काष्ठा cdnsp_device *pdev, u32 bit)
अणु
	__le32 __iomem *reg;
	व्योम __iomem *base;
	u32 offset = 0;

	base = &pdev->cap_regs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, offset, D_XEC_PRE_REGS_CAP);
	reg = base + offset + REG_CHICKEN_BITS_2_OFFSET;

	bit = पढ़ोl(reg) & ~bit;
	ग_लिखोl(bit, reg);
पूर्ण

/*
 * Disable पूर्णांकerrupts and begin the controller halting process.
 */
अटल व्योम cdnsp_quiesce(काष्ठा cdnsp_device *pdev)
अणु
	u32 halted;
	u32 mask;
	u32 cmd;

	mask = ~(u32)(CDNSP_IRQS);

	halted = पढ़ोl(&pdev->op_regs->status) & STS_HALT;
	अगर (!halted)
		mask &= ~(CMD_R_S | CMD_DEVEN);

	cmd = पढ़ोl(&pdev->op_regs->command);
	cmd &= mask;
	ग_लिखोl(cmd, &pdev->op_regs->command);
पूर्ण

/*
 * Force controller पूर्णांकo halt state.
 *
 * Disable any IRQs and clear the run/stop bit.
 * Controller will complete any current and actively pipelined transactions, and
 * should halt within 16 ms of the run/stop bit being cleared.
 * Read controller Halted bit in the status रेजिस्टर to see when the
 * controller is finished.
 */
पूर्णांक cdnsp_halt(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक ret;
	u32 val;

	cdnsp_quiesce(pdev);

	ret = पढ़ोl_poll_समयout_atomic(&pdev->op_regs->status, val,
					val & STS_HALT, 1,
					CDNSP_MAX_HALT_USEC);
	अगर (ret) अणु
		dev_err(pdev->dev, "ERROR: Device halt failed\n");
		वापस ret;
	पूर्ण

	pdev->cdnsp_state |= CDNSP_STATE_HALTED;

	वापस 0;
पूर्ण

/*
 * device controller died, रेजिस्टर पढ़ो वापसs 0xffffffff, or command never
 * ends.
 */
व्योम cdnsp_died(काष्ठा cdnsp_device *pdev)
अणु
	dev_err(pdev->dev, "ERROR: CDNSP controller not responding\n");
	pdev->cdnsp_state |= CDNSP_STATE_DYING;
	cdnsp_halt(pdev);
पूर्ण

/*
 * Set the run bit and रुको क्रम the device to be running.
 */
अटल पूर्णांक cdnsp_start(काष्ठा cdnsp_device *pdev)
अणु
	u32 temp;
	पूर्णांक ret;

	temp = पढ़ोl(&pdev->op_regs->command);
	temp |= (CMD_R_S | CMD_DEVEN);
	ग_लिखोl(temp, &pdev->op_regs->command);

	pdev->cdnsp_state = 0;

	/*
	 * Wait क्रम the STS_HALT Status bit to be 0 to indicate the device is
	 * running.
	 */
	ret = पढ़ोl_poll_समयout_atomic(&pdev->op_regs->status, temp,
					!(temp & STS_HALT), 1,
					CDNSP_MAX_HALT_USEC);
	अगर (ret) अणु
		pdev->cdnsp_state = CDNSP_STATE_DYING;
		dev_err(pdev->dev, "ERROR: Controller run failed\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Reset a halted controller.
 *
 * This resets pipelines, समयrs, counters, state machines, etc.
 * Transactions will be terminated immediately, and operational रेजिस्टरs
 * will be set to their शेषs.
 */
पूर्णांक cdnsp_reset(काष्ठा cdnsp_device *pdev)
अणु
	u32 command;
	u32 temp;
	पूर्णांक ret;

	temp = पढ़ोl(&pdev->op_regs->status);

	अगर (temp == ~(u32)0) अणु
		dev_err(pdev->dev, "Device not accessible, reset failed.\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((temp & STS_HALT) == 0) अणु
		dev_err(pdev->dev, "Controller not halted, aborting reset.\n");
		वापस -EINVAL;
	पूर्ण

	command = पढ़ोl(&pdev->op_regs->command);
	command |= CMD_RESET;
	ग_लिखोl(command, &pdev->op_regs->command);

	ret = पढ़ोl_poll_समयout_atomic(&pdev->op_regs->command, temp,
					!(temp & CMD_RESET), 1,
					10 * 1000);
	अगर (ret) अणु
		dev_err(pdev->dev, "ERROR: Controller reset failed\n");
		वापस ret;
	पूर्ण

	/*
	 * CDNSP cannot ग_लिखो any करोorbells or operational रेजिस्टरs other
	 * than status until the "Controller Not Ready" flag is cleared.
	 */
	ret = पढ़ोl_poll_समयout_atomic(&pdev->op_regs->status, temp,
					!(temp & STS_CNR), 1,
					10 * 1000);

	अगर (ret) अणु
		dev_err(pdev->dev, "ERROR: Controller not ready to work\n");
		वापस ret;
	पूर्ण

	dev_dbg(pdev->dev, "Controller ready to work");

	वापस ret;
पूर्ण

/*
 * cdnsp_get_endpoपूर्णांक_index - Find the index क्रम an endpoपूर्णांक given its
 * descriptor.Use the वापस value to right shअगरt 1 क्रम the biपंचांगask.
 *
 * Index = (epnum * 2) + direction - 1,
 * where direction = 0 क्रम OUT, 1 क्रम IN.
 * For control endpoपूर्णांकs, the IN index is used (OUT index is unused), so
 * index = (epnum * 2) + direction - 1 = (epnum * 2) + 1 - 1 = (epnum * 2)
 */
अटल अचिन्हित पूर्णांक
	cdnsp_get_endpoपूर्णांक_index(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित पूर्णांक index = (अचिन्हित पूर्णांक)usb_endpoपूर्णांक_num(desc);

	अगर (usb_endpoपूर्णांक_xfer_control(desc))
		वापस index * 2;

	वापस (index * 2) + (usb_endpoपूर्णांक_dir_in(desc) ? 1 : 0) - 1;
पूर्ण

/*
 * Find the flag क्रम this endpoपूर्णांक (क्रम use in the control context). Use the
 * endpoपूर्णांक index to create a biपंचांगask. The slot context is bit 0, endpoपूर्णांक 0 is
 * bit 1, etc.
 */
अटल अचिन्हित पूर्णांक
	cdnsp_get_endpoपूर्णांक_flag(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस 1 << (cdnsp_get_endpoपूर्णांक_index(desc) + 1);
पूर्ण

पूर्णांक cdnsp_ep_enqueue(काष्ठा cdnsp_ep *pep, काष्ठा cdnsp_request *preq)
अणु
	काष्ठा cdnsp_device *pdev = pep->pdev;
	काष्ठा usb_request *request;
	पूर्णांक ret;

	अगर (preq->epnum == 0 && !list_empty(&pep->pending_list)) अणु
		trace_cdnsp_request_enqueue_busy(preq);
		वापस -EBUSY;
	पूर्ण

	request = &preq->request;
	request->actual = 0;
	request->status = -EINPROGRESS;
	preq->direction = pep->direction;
	preq->epnum = pep->number;
	preq->td.drbl = 0;

	ret = usb_gadget_map_request_by_dev(pdev->dev, request, pep->direction);
	अगर (ret) अणु
		trace_cdnsp_request_enqueue_error(preq);
		वापस ret;
	पूर्ण

	list_add_tail(&preq->list, &pep->pending_list);

	trace_cdnsp_request_enqueue(preq);

	चयन (usb_endpoपूर्णांक_type(pep->endpoपूर्णांक.desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		ret = cdnsp_queue_ctrl_tx(pdev, preq);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		ret = cdnsp_queue_bulk_tx(pdev, preq);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		ret = cdnsp_queue_isoc_tx_prepare(pdev, preq);
	पूर्ण

	अगर (ret)
		जाओ unmap;

	वापस 0;

unmap:
	usb_gadget_unmap_request_by_dev(pdev->dev, &preq->request,
					pep->direction);
	list_del(&preq->list);
	trace_cdnsp_request_enqueue_error(preq);

	वापस ret;
पूर्ण

/*
 * Remove the request's TD from the endpoपूर्णांक ring. This may cause the
 * controller to stop USB transfers, potentially stopping in the middle of a
 * TRB buffer. The controller should pick up where it left off in the TD,
 * unless a Set Transfer Ring Dequeue Poपूर्णांकer is issued.
 *
 * The TRBs that make up the buffers क्रम the canceled request will be "removed"
 * from the ring. Since the ring is a contiguous काष्ठाure, they can't be
 * physically हटाओd. Instead, there are two options:
 *
 *  1) If the controller is in the middle of processing the request to be
 *     canceled, we simply move the ring's dequeue poपूर्णांकer past those TRBs
 *     using the Set Transfer Ring Dequeue Poपूर्णांकer command. This will be
 *     the common हाल, when drivers समयout on the last submitted request
 *     and attempt to cancel.
 *
 *  2) If the controller is in the middle of a dअगरferent TD, we turn the TRBs
 *     पूर्णांकo a series of 1-TRB transfer no-op TDs. No-ops shouldn't be chained.
 *     The controller will need to invalidate the any TRBs it has cached after
 *     the stop endpoपूर्णांक command.
 *
 *  3) The TD may have completed by the समय the Stop Endpoपूर्णांक Command
 *     completes, so software needs to handle that हाल too.
 *
 */
पूर्णांक cdnsp_ep_dequeue(काष्ठा cdnsp_ep *pep, काष्ठा cdnsp_request *preq)
अणु
	काष्ठा cdnsp_device *pdev = pep->pdev;
	पूर्णांक ret_stop = 0;
	पूर्णांक ret_rem;

	trace_cdnsp_request_dequeue(preq);

	अगर (GET_EP_CTX_STATE(pep->out_ctx) == EP_STATE_RUNNING)
		ret_stop = cdnsp_cmd_stop_ep(pdev, pep);

	ret_rem = cdnsp_हटाओ_request(pdev, preq, pep);

	वापस ret_rem ? ret_rem : ret_stop;
पूर्ण

अटल व्योम cdnsp_zero_in_ctx(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_input_control_ctx *ctrl_ctx;
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	काष्ठा cdnsp_ep_ctx *ep_ctx;
	पूर्णांक i;

	ctrl_ctx = cdnsp_get_input_control_ctx(&pdev->in_ctx);

	/*
	 * When a device's add flag and drop flag are zero, any subsequent
	 * configure endpoपूर्णांक command will leave that endpoपूर्णांक's state
	 * untouched. Make sure we करोn't leave any old state in the input
	 * endpoपूर्णांक contexts.
	 */
	ctrl_ctx->drop_flags = 0;
	ctrl_ctx->add_flags = 0;
	slot_ctx = cdnsp_get_slot_ctx(&pdev->in_ctx);
	slot_ctx->dev_info &= cpu_to_le32(~LAST_CTX_MASK);

	/* Endpoपूर्णांक 0 is always valid */
	slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(1));
	क्रम (i = 1; i < CDNSP_ENDPOINTS_NUM; ++i) अणु
		ep_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, i);
		ep_ctx->ep_info = 0;
		ep_ctx->ep_info2 = 0;
		ep_ctx->deq = 0;
		ep_ctx->tx_info = 0;
	पूर्ण
पूर्ण

/* Issue a configure endpoपूर्णांक command and रुको क्रम it to finish. */
अटल पूर्णांक cdnsp_configure_endpoपूर्णांक(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक ret;

	cdnsp_queue_configure_endpoपूर्णांक(pdev, pdev->cmd.in_ctx->dma);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);
	अगर (ret) अणु
		dev_err(pdev->dev,
			"ERR: unexpected command completion code 0x%x.\n", ret);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cdnsp_invalidate_ep_events(काष्ठा cdnsp_device *pdev,
				       काष्ठा cdnsp_ep *pep)
अणु
	काष्ठा cdnsp_segment *segment;
	जोड़ cdnsp_trb *event;
	u32 cycle_state;
	u32  data;

	event = pdev->event_ring->dequeue;
	segment = pdev->event_ring->deq_seg;
	cycle_state = pdev->event_ring->cycle_state;

	जबतक (1) अणु
		data = le32_to_cpu(event->trans_event.flags);

		/* Check the owner of the TRB. */
		अगर ((data & TRB_CYCLE) != cycle_state)
			अवरोध;

		अगर (TRB_FIELD_TO_TYPE(data) == TRB_TRANSFER &&
		    TRB_TO_EP_ID(data) == (pep->idx + 1)) अणु
			data |= TRB_EVENT_INVALIDATE;
			event->trans_event.flags = cpu_to_le32(data);
		पूर्ण

		अगर (cdnsp_last_trb_on_seg(segment, event)) अणु
			cycle_state ^= 1;
			segment = pdev->event_ring->deq_seg->next;
			event = segment->trbs;
		पूर्ण अन्यथा अणु
			event++;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cdnsp_रुको_क्रम_cmd_compl(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_segment *event_deq_seg;
	जोड़ cdnsp_trb *cmd_trb;
	dma_addr_t cmd_deq_dma;
	जोड़ cdnsp_trb *event;
	u32 cycle_state;
	पूर्णांक ret, val;
	u64 cmd_dma;
	u32  flags;

	cmd_trb = pdev->cmd.command_trb;
	pdev->cmd.status = 0;

	trace_cdnsp_cmd_रुको_क्रम_compl(pdev->cmd_ring, &cmd_trb->generic);

	ret = पढ़ोl_poll_समयout_atomic(&pdev->op_regs->cmd_ring, val,
					!CMD_RING_BUSY(val), 1,
					CDNSP_CMD_TIMEOUT);
	अगर (ret) अणु
		dev_err(pdev->dev, "ERR: Timeout while waiting for command\n");
		trace_cdnsp_cmd_समयout(pdev->cmd_ring, &cmd_trb->generic);
		pdev->cdnsp_state = CDNSP_STATE_DYING;
		वापस -ETIMEDOUT;
	पूर्ण

	event = pdev->event_ring->dequeue;
	event_deq_seg = pdev->event_ring->deq_seg;
	cycle_state = pdev->event_ring->cycle_state;

	cmd_deq_dma = cdnsp_trb_virt_to_dma(pdev->cmd_ring->deq_seg, cmd_trb);
	अगर (!cmd_deq_dma)
		वापस -EINVAL;

	जबतक (1) अणु
		flags = le32_to_cpu(event->event_cmd.flags);

		/* Check the owner of the TRB. */
		अगर ((flags & TRB_CYCLE) != cycle_state)
			वापस -EINVAL;

		cmd_dma = le64_to_cpu(event->event_cmd.cmd_trb);

		/*
		 * Check whether the completion event is क्रम last queued
		 * command.
		 */
		अगर (TRB_FIELD_TO_TYPE(flags) != TRB_COMPLETION ||
		    cmd_dma != (u64)cmd_deq_dma) अणु
			अगर (!cdnsp_last_trb_on_seg(event_deq_seg, event)) अणु
				event++;
				जारी;
			पूर्ण

			अगर (cdnsp_last_trb_on_ring(pdev->event_ring,
						   event_deq_seg, event))
				cycle_state ^= 1;

			event_deq_seg = event_deq_seg->next;
			event = event_deq_seg->trbs;
			जारी;
		पूर्ण

		trace_cdnsp_handle_command(pdev->cmd_ring, &cmd_trb->generic);

		pdev->cmd.status = GET_COMP_CODE(le32_to_cpu(event->event_cmd.status));
		अगर (pdev->cmd.status == COMP_SUCCESS)
			वापस 0;

		वापस -pdev->cmd.status;
	पूर्ण
पूर्ण

पूर्णांक cdnsp_halt_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
			काष्ठा cdnsp_ep *pep,
			पूर्णांक value)
अणु
	पूर्णांक ret;

	trace_cdnsp_ep_halt(value ? "Set" : "Clear");

	अगर (value) अणु
		ret = cdnsp_cmd_stop_ep(pdev, pep);
		अगर (ret)
			वापस ret;

		अगर (GET_EP_CTX_STATE(pep->out_ctx) == EP_STATE_STOPPED) अणु
			cdnsp_queue_halt_endpoपूर्णांक(pdev, pep->idx);
			cdnsp_ring_cmd_db(pdev);
			ret = cdnsp_रुको_क्रम_cmd_compl(pdev);
		पूर्ण

		pep->ep_state |= EP_HALTED;
	पूर्ण अन्यथा अणु
		/*
		 * In device mode driver can call reset endpoपूर्णांक command
		 * from any endpoपूर्णांक state.
		 */
		cdnsp_queue_reset_ep(pdev, pep->idx);
		cdnsp_ring_cmd_db(pdev);
		ret = cdnsp_रुको_क्रम_cmd_compl(pdev);
		trace_cdnsp_handle_cmd_reset_ep(pep->out_ctx);

		अगर (ret)
			वापस ret;

		pep->ep_state &= ~EP_HALTED;

		अगर (pep->idx != 0 && !(pep->ep_state & EP_WEDGE))
			cdnsp_ring_करोorbell_क्रम_active_rings(pdev, pep);

		pep->ep_state &= ~EP_WEDGE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_update_eps_configuration(काष्ठा cdnsp_device *pdev,
					  काष्ठा cdnsp_ep *pep)
अणु
	काष्ठा cdnsp_input_control_ctx *ctrl_ctx;
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	पूर्णांक ret = 0;
	u32 ep_sts;
	पूर्णांक i;

	ctrl_ctx = cdnsp_get_input_control_ctx(&pdev->in_ctx);

	/* Don't issue the command if there's no endpoपूर्णांकs to update. */
	अगर (ctrl_ctx->add_flags == 0 && ctrl_ctx->drop_flags == 0)
		वापस 0;

	ctrl_ctx->add_flags |= cpu_to_le32(SLOT_FLAG);
	ctrl_ctx->add_flags &= cpu_to_le32(~EP0_FLAG);
	ctrl_ctx->drop_flags &= cpu_to_le32(~(SLOT_FLAG | EP0_FLAG));

	/* Fix up Context Entries field. Minimum value is EP0 == BIT(1). */
	slot_ctx = cdnsp_get_slot_ctx(&pdev->in_ctx);
	क्रम (i = CDNSP_ENDPOINTS_NUM; i >= 1; i--) अणु
		__le32 le32 = cpu_to_le32(BIT(i));

		अगर ((pdev->eps[i - 1].ring && !(ctrl_ctx->drop_flags & le32)) ||
		    (ctrl_ctx->add_flags & le32) || i == 1) अणु
			slot_ctx->dev_info &= cpu_to_le32(~LAST_CTX_MASK);
			slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(i));
			अवरोध;
		पूर्ण
	पूर्ण

	ep_sts = GET_EP_CTX_STATE(pep->out_ctx);

	अगर ((ctrl_ctx->add_flags != cpu_to_le32(SLOT_FLAG) &&
	     ep_sts == EP_STATE_DISABLED) ||
	    (ep_sts != EP_STATE_DISABLED && ctrl_ctx->drop_flags))
		ret = cdnsp_configure_endpoपूर्णांक(pdev);

	trace_cdnsp_configure_endpoपूर्णांक(cdnsp_get_slot_ctx(&pdev->out_ctx));
	trace_cdnsp_handle_cmd_config_ep(pep->out_ctx);

	cdnsp_zero_in_ctx(pdev);

	वापस ret;
पूर्ण

/*
 * This submits a Reset Device Command, which will set the device state to 0,
 * set the device address to 0, and disable all the endpoपूर्णांकs except the शेष
 * control endpoपूर्णांक. The USB core should come back and call
 * cdnsp_setup_device(), and then re-set up the configuration.
 */
पूर्णांक cdnsp_reset_device(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	पूर्णांक slot_state;
	पूर्णांक ret, i;

	slot_ctx = cdnsp_get_slot_ctx(&pdev->in_ctx);
	slot_ctx->dev_info = 0;
	pdev->device_address = 0;

	/* If device is not setup, there is no poपूर्णांक in resetting it. */
	slot_ctx = cdnsp_get_slot_ctx(&pdev->out_ctx);
	slot_state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));
	trace_cdnsp_reset_device(slot_ctx);

	अगर (slot_state <= SLOT_STATE_DEFAULT &&
	    pdev->eps[0].ep_state & EP_HALTED) अणु
		cdnsp_halt_endpoपूर्णांक(pdev, &pdev->eps[0], 0);
	पूर्ण

	/*
	 * During Reset Device command controller shall transition the
	 * endpoपूर्णांक ep0 to the Running State.
	 */
	pdev->eps[0].ep_state &= ~(EP_STOPPED | EP_HALTED);
	pdev->eps[0].ep_state |= EP_ENABLED;

	अगर (slot_state <= SLOT_STATE_DEFAULT)
		वापस 0;

	cdnsp_queue_reset_device(pdev);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	/*
	 * After Reset Device command all not शेष endpoपूर्णांकs
	 * are in Disabled state.
	 */
	क्रम (i = 1; i < CDNSP_ENDPOINTS_NUM; ++i)
		pdev->eps[i].ep_state |= EP_STOPPED | EP_UNCONFIGURED;

	trace_cdnsp_handle_cmd_reset_dev(slot_ctx);

	अगर (ret)
		dev_err(pdev->dev, "Reset device failed with error code %d",
			ret);

	वापस ret;
पूर्ण

/*
 * Sets the MaxPStreams field and the Linear Stream Array field.
 * Sets the dequeue poपूर्णांकer to the stream context array.
 */
अटल व्योम cdnsp_setup_streams_ep_input_ctx(काष्ठा cdnsp_device *pdev,
					     काष्ठा cdnsp_ep_ctx *ep_ctx,
					     काष्ठा cdnsp_stream_info *stream_info)
अणु
	u32 max_primary_streams;

	/* MaxPStreams is the number of stream context array entries, not the
	 * number we're actually using. Must be in 2^(MaxPstreams + 1) क्रमmat.
	 * fls(0) = 0, fls(0x1) = 1, fls(0x10) = 2, fls(0x100) = 3, etc.
	 */
	max_primary_streams = fls(stream_info->num_stream_ctxs) - 2;
	ep_ctx->ep_info &= cpu_to_le32(~EP_MAXPSTREAMS_MASK);
	ep_ctx->ep_info |= cpu_to_le32(EP_MAXPSTREAMS(max_primary_streams)
				       | EP_HAS_LSA);
	ep_ctx->deq  = cpu_to_le64(stream_info->ctx_array_dma);
पूर्ण

/*
 * The drivers use this function to prepare a bulk endpoपूर्णांकs to use streams.
 *
 * Don't allow the call to succeed अगर endpoपूर्णांक only supports one stream
 * (which means it करोesn't support streams at all).
 */
पूर्णांक cdnsp_alloc_streams(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	अचिन्हित पूर्णांक num_streams = usb_ss_max_streams(pep->endpoपूर्णांक.comp_desc);
	अचिन्हित पूर्णांक num_stream_ctxs;
	पूर्णांक ret;

	अगर (num_streams ==  0)
		वापस 0;

	अगर (num_streams > STREAM_NUM_STREAMS)
		वापस -EINVAL;

	/*
	 * Add two to the number of streams requested to account क्रम
	 * stream 0 that is reserved क्रम controller usage and one additional
	 * क्रम TASK SET FULL response.
	 */
	num_streams += 2;

	/* The stream context array size must be a घातer of two */
	num_stream_ctxs = roundup_घात_of_two(num_streams);

	trace_cdnsp_stream_number(pep, num_stream_ctxs, num_streams);

	ret = cdnsp_alloc_stream_info(pdev, pep, num_stream_ctxs, num_streams);
	अगर (ret)
		वापस ret;

	cdnsp_setup_streams_ep_input_ctx(pdev, pep->in_ctx, &pep->stream_info);

	pep->ep_state |= EP_HAS_STREAMS;
	pep->stream_info.td_count = 0;
	pep->stream_info.first_prime_det = 0;

	/* Subtract 1 क्रम stream 0, which drivers can't use. */
	वापस num_streams - 1;
पूर्ण

पूर्णांक cdnsp_disable_slot(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक ret;

	cdnsp_queue_slot_control(pdev, TRB_DISABLE_SLOT);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	pdev->slot_id = 0;
	pdev->active_port = शून्य;

	trace_cdnsp_handle_cmd_disable_slot(cdnsp_get_slot_ctx(&pdev->out_ctx));

	स_रखो(pdev->in_ctx.bytes, 0, CDNSP_CTX_SIZE);
	स_रखो(pdev->out_ctx.bytes, 0, CDNSP_CTX_SIZE);

	वापस ret;
पूर्ण

पूर्णांक cdnsp_enable_slot(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	पूर्णांक slot_state;
	पूर्णांक ret;

	/* If device is not setup, there is no poपूर्णांक in resetting it */
	slot_ctx = cdnsp_get_slot_ctx(&pdev->out_ctx);
	slot_state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));

	अगर (slot_state != SLOT_STATE_DISABLED)
		वापस 0;

	cdnsp_queue_slot_control(pdev, TRB_ENABLE_SLOT);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);
	अगर (ret)
		जाओ show_trace;

	pdev->slot_id = 1;

show_trace:
	trace_cdnsp_handle_cmd_enable_slot(cdnsp_get_slot_ctx(&pdev->out_ctx));

	वापस ret;
पूर्ण

/*
 * Issue an Address Device command with BSR=0 अगर setup is SETUP_CONTEXT_ONLY
 * or with BSR = 1 अगर set_address is SETUP_CONTEXT_ADDRESS.
 */
पूर्णांक cdnsp_setup_device(काष्ठा cdnsp_device *pdev, क्रमागत cdnsp_setup_dev setup)
अणु
	काष्ठा cdnsp_input_control_ctx *ctrl_ctx;
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	पूर्णांक dev_state = 0;
	पूर्णांक ret;

	अगर (!pdev->slot_id) अणु
		trace_cdnsp_slot_id("incorrect");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdev->active_port->port_num)
		वापस -EINVAL;

	slot_ctx = cdnsp_get_slot_ctx(&pdev->out_ctx);
	dev_state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));

	अगर (setup == SETUP_CONTEXT_ONLY && dev_state == SLOT_STATE_DEFAULT) अणु
		trace_cdnsp_slot_alपढ़ोy_in_शेष(slot_ctx);
		वापस 0;
	पूर्ण

	slot_ctx = cdnsp_get_slot_ctx(&pdev->in_ctx);
	ctrl_ctx = cdnsp_get_input_control_ctx(&pdev->in_ctx);

	अगर (!slot_ctx->dev_info || dev_state == SLOT_STATE_DEFAULT) अणु
		ret = cdnsp_setup_addressable_priv_dev(pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	cdnsp_copy_ep0_dequeue_पूर्णांकo_input_ctx(pdev);

	ctrl_ctx->add_flags = cpu_to_le32(SLOT_FLAG | EP0_FLAG);
	ctrl_ctx->drop_flags = 0;

	trace_cdnsp_setup_device_slot(slot_ctx);

	cdnsp_queue_address_device(pdev, pdev->in_ctx.dma, setup);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	trace_cdnsp_handle_cmd_addr_dev(cdnsp_get_slot_ctx(&pdev->out_ctx));

	/* Zero the input context control क्रम later use. */
	ctrl_ctx->add_flags = 0;
	ctrl_ctx->drop_flags = 0;

	वापस ret;
पूर्ण

व्योम cdnsp_set_usb2_hardware_lpm(काष्ठा cdnsp_device *pdev,
				 काष्ठा usb_request *req,
				 पूर्णांक enable)
अणु
	अगर (pdev->active_port != &pdev->usb2_port || !pdev->gadget.lpm_capable)
		वापस;

	trace_cdnsp_lpm(enable);

	अगर (enable)
		ग_लिखोl(PORT_BESL(CDNSP_DEFAULT_BESL) | PORT_L1S_NYET | PORT_HLE,
		       &pdev->active_port->regs->portpmsc);
	अन्यथा
		ग_लिखोl(PORT_L1S_NYET, &pdev->active_port->regs->portpmsc);
पूर्ण

अटल पूर्णांक cdnsp_get_frame(काष्ठा cdnsp_device *pdev)
अणु
	वापस पढ़ोl(&pdev->run_regs->microframe_index) >> 3;
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_enable(काष्ठा usb_ep *ep,
				  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा cdnsp_input_control_ctx *ctrl_ctx;
	काष्ठा cdnsp_device *pdev;
	काष्ठा cdnsp_ep *pep;
	अचिन्हित दीर्घ flags;
	u32 added_ctxs;
	पूर्णांक ret;

	अगर (!ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT ||
	    !desc->wMaxPacketSize)
		वापस -EINVAL;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;
	pep->ep_state &= ~EP_UNCONFIGURED;

	अगर (dev_WARN_ONCE(pdev->dev, pep->ep_state & EP_ENABLED,
			  "%s is already enabled\n", pep->name))
		वापस 0;

	spin_lock_irqsave(&pdev->lock, flags);

	added_ctxs = cdnsp_get_endpoपूर्णांक_flag(desc);
	अगर (added_ctxs == SLOT_FLAG || added_ctxs == EP0_FLAG) अणु
		dev_err(pdev->dev, "ERROR: Bad endpoint number\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	pep->पूर्णांकerval = desc->bInterval ? BIT(desc->bInterval - 1) : 0;

	अगर (pdev->gadget.speed == USB_SPEED_FULL) अणु
		अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_INT)
			pep->पूर्णांकerval = desc->bInterval << 3;
		अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_ISOC)
			pep->पूर्णांकerval = BIT(desc->bInterval - 1) << 3;
	पूर्ण

	अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_ISOC) अणु
		अगर (pep->पूर्णांकerval > BIT(12)) अणु
			dev_err(pdev->dev, "bInterval %d not supported\n",
				desc->bInterval);
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
		cdnsp_set_chicken_bits_2(pdev, CHICKEN_XDMA_2_TP_CACHE_DIS);
	पूर्ण

	ret = cdnsp_endpoपूर्णांक_init(pdev, pep, GFP_ATOMIC);
	अगर (ret)
		जाओ unlock;

	ctrl_ctx = cdnsp_get_input_control_ctx(&pdev->in_ctx);
	ctrl_ctx->add_flags = cpu_to_le32(added_ctxs);
	ctrl_ctx->drop_flags = 0;

	ret = cdnsp_update_eps_configuration(pdev, pep);
	अगर (ret) अणु
		cdnsp_मुक्त_endpoपूर्णांक_rings(pdev, pep);
		जाओ unlock;
	पूर्ण

	pep->ep_state |= EP_ENABLED;
	pep->ep_state &= ~EP_STOPPED;

unlock:
	trace_cdnsp_ep_enable_end(pep, 0);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा cdnsp_input_control_ctx *ctrl_ctx;
	काष्ठा cdnsp_request *preq;
	काष्ठा cdnsp_device *pdev;
	काष्ठा cdnsp_ep *pep;
	अचिन्हित दीर्घ flags;
	u32 drop_flag;
	पूर्णांक ret = 0;

	अगर (!ep)
		वापस -EINVAL;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;

	spin_lock_irqsave(&pdev->lock, flags);

	अगर (!(pep->ep_state & EP_ENABLED)) अणु
		dev_err(pdev->dev, "%s is already disabled\n", pep->name);
		ret = -EINVAL;
		जाओ finish;
	पूर्ण

	pep->ep_state |= EP_DIS_IN_RROGRESS;

	/* Endpoपूर्णांक was unconfigured by Reset Device command. */
	अगर (!(pep->ep_state & EP_UNCONFIGURED)) अणु
		cdnsp_cmd_stop_ep(pdev, pep);
		cdnsp_cmd_flush_ep(pdev, pep);
	पूर्ण

	/* Remove all queued USB requests. */
	जबतक (!list_empty(&pep->pending_list)) अणु
		preq = next_request(&pep->pending_list);
		cdnsp_ep_dequeue(pep, preq);
	पूर्ण

	cdnsp_invalidate_ep_events(pdev, pep);

	pep->ep_state &= ~EP_DIS_IN_RROGRESS;
	drop_flag = cdnsp_get_endpoपूर्णांक_flag(pep->endpoपूर्णांक.desc);
	ctrl_ctx = cdnsp_get_input_control_ctx(&pdev->in_ctx);
	ctrl_ctx->drop_flags = cpu_to_le32(drop_flag);
	ctrl_ctx->add_flags = 0;

	cdnsp_endpoपूर्णांक_zero(pdev, pep);

	अगर (!(pep->ep_state & EP_UNCONFIGURED))
		ret = cdnsp_update_eps_configuration(pdev, pep);

	cdnsp_मुक्त_endpoपूर्णांक_rings(pdev, pep);

	pep->ep_state &= ~(EP_ENABLED | EP_UNCONFIGURED);
	pep->ep_state |= EP_STOPPED;

finish:
	trace_cdnsp_ep_disable_end(pep, 0);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा usb_request *cdnsp_gadget_ep_alloc_request(काष्ठा usb_ep *ep,
							 gfp_t gfp_flags)
अणु
	काष्ठा cdnsp_ep *pep = to_cdnsp_ep(ep);
	काष्ठा cdnsp_request *preq;

	preq = kzalloc(माप(*preq), gfp_flags);
	अगर (!preq)
		वापस शून्य;

	preq->epnum = pep->number;
	preq->pep = pep;

	trace_cdnsp_alloc_request(preq);

	वापस &preq->request;
पूर्ण

अटल व्योम cdnsp_gadget_ep_मुक्त_request(काष्ठा usb_ep *ep,
					 काष्ठा usb_request *request)
अणु
	काष्ठा cdnsp_request *preq = to_cdnsp_request(request);

	trace_cdnsp_मुक्त_request(preq);
	kमुक्त(preq);
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_queue(काष्ठा usb_ep *ep,
				 काष्ठा usb_request *request,
				 gfp_t gfp_flags)
अणु
	काष्ठा cdnsp_request *preq;
	काष्ठा cdnsp_device *pdev;
	काष्ठा cdnsp_ep *pep;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!request || !ep)
		वापस -EINVAL;

	pep = to_cdnsp_ep(ep);
	pdev = pep->pdev;

	अगर (!(pep->ep_state & EP_ENABLED)) अणु
		dev_err(pdev->dev, "%s: can't queue to disabled endpoint\n",
			pep->name);
		वापस -EINVAL;
	पूर्ण

	preq = to_cdnsp_request(request);
	spin_lock_irqsave(&pdev->lock, flags);
	ret = cdnsp_ep_enqueue(pep, preq);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_dequeue(काष्ठा usb_ep *ep,
				   काष्ठा usb_request *request)
अणु
	काष्ठा cdnsp_ep *pep = to_cdnsp_ep(ep);
	काष्ठा cdnsp_device *pdev = pep->pdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!pep->endpoपूर्णांक.desc) अणु
		dev_err(pdev->dev,
			"%s: can't dequeue to disabled endpoint\n",
			pep->name);
		वापस -ESHUTDOWN;
	पूर्ण

	/* Requests has been dequeued during disabling endpoपूर्णांक. */
	अगर (!(pep->ep_state & EP_ENABLED))
		वापस 0;

	spin_lock_irqsave(&pdev->lock, flags);
	ret = cdnsp_ep_dequeue(pep, to_cdnsp_request(request));
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा cdnsp_ep *pep = to_cdnsp_ep(ep);
	काष्ठा cdnsp_device *pdev = pep->pdev;
	काष्ठा cdnsp_request *preq;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	spin_lock_irqsave(&pdev->lock, flags);

	preq = next_request(&pep->pending_list);
	अगर (value) अणु
		अगर (preq) अणु
			trace_cdnsp_ep_busy_try_halt_again(pep, 0);
			ret = -EAGAIN;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = cdnsp_halt_endpoपूर्णांक(pdev, pep, value);

करोne:
	spin_unlock_irqrestore(&pdev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_gadget_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा cdnsp_ep *pep = to_cdnsp_ep(ep);
	काष्ठा cdnsp_device *pdev = pep->pdev;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	spin_lock_irqsave(&pdev->lock, flags);
	pep->ep_state |= EP_WEDGE;
	ret = cdnsp_halt_endpoपूर्णांक(pdev, pep, 1);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops cdnsp_gadget_ep0_ops = अणु
	.enable		= cdnsp_gadget_ep_enable,
	.disable	= cdnsp_gadget_ep_disable,
	.alloc_request	= cdnsp_gadget_ep_alloc_request,
	.मुक्त_request	= cdnsp_gadget_ep_मुक्त_request,
	.queue		= cdnsp_gadget_ep_queue,
	.dequeue	= cdnsp_gadget_ep_dequeue,
	.set_halt	= cdnsp_gadget_ep_set_halt,
	.set_wedge	= cdnsp_gadget_ep_set_wedge,
पूर्ण;

अटल स्थिर काष्ठा usb_ep_ops cdnsp_gadget_ep_ops = अणु
	.enable		= cdnsp_gadget_ep_enable,
	.disable	= cdnsp_gadget_ep_disable,
	.alloc_request	= cdnsp_gadget_ep_alloc_request,
	.मुक्त_request	= cdnsp_gadget_ep_मुक्त_request,
	.queue		= cdnsp_gadget_ep_queue,
	.dequeue	= cdnsp_gadget_ep_dequeue,
	.set_halt	= cdnsp_gadget_ep_set_halt,
	.set_wedge	= cdnsp_gadget_ep_set_wedge,
पूर्ण;

व्योम cdnsp_gadget_giveback(काष्ठा cdnsp_ep *pep,
			   काष्ठा cdnsp_request *preq,
			   पूर्णांक status)
अणु
	काष्ठा cdnsp_device *pdev = pep->pdev;

	list_del(&preq->list);

	अगर (preq->request.status == -EINPROGRESS)
		preq->request.status = status;

	usb_gadget_unmap_request_by_dev(pdev->dev, &preq->request,
					preq->direction);

	trace_cdnsp_request_giveback(preq);

	अगर (preq != &pdev->ep0_preq) अणु
		spin_unlock(&pdev->lock);
		usb_gadget_giveback_request(&pep->endpoपूर्णांक, &preq->request);
		spin_lock(&pdev->lock);
	पूर्ण
पूर्ण

अटल काष्ठा usb_endpoपूर्णांक_descriptor cdnsp_gadget_ep0_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_CONTROL,
पूर्ण;

अटल पूर्णांक cdnsp_run(काष्ठा cdnsp_device *pdev,
		     क्रमागत usb_device_speed speed)
अणु
	u32 fs_speed = 0;
	u64 temp_64;
	u32 temp;
	पूर्णांक ret;

	temp_64 = cdnsp_पढ़ो_64(&pdev->ir_set->erst_dequeue);
	temp_64 &= ~ERST_PTR_MASK;
	temp = पढ़ोl(&pdev->ir_set->irq_control);
	temp &= ~IMOD_INTERVAL_MASK;
	temp |= ((IMOD_DEFAULT_INTERVAL / 250) & IMOD_INTERVAL_MASK);
	ग_लिखोl(temp, &pdev->ir_set->irq_control);

	temp = पढ़ोl(&pdev->port3x_regs->mode_addr);

	चयन (speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
		temp |= CFG_3XPORT_SSP_SUPPORT;
		अवरोध;
	हाल USB_SPEED_SUPER:
		temp &= ~CFG_3XPORT_SSP_SUPPORT;
		अवरोध;
	हाल USB_SPEED_HIGH:
		अवरोध;
	हाल USB_SPEED_FULL:
		fs_speed = PORT_REG6_FORCE_FS;
		अवरोध;
	शेष:
		dev_err(pdev->dev, "invalid maximum_speed parameter %d\n",
			speed);
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		/* Default to superspeed. */
		speed = USB_SPEED_SUPER;
		अवरोध;
	पूर्ण

	अगर (speed >= USB_SPEED_SUPER) अणु
		ग_लिखोl(temp, &pdev->port3x_regs->mode_addr);
		cdnsp_set_link_state(pdev, &pdev->usb3_port.regs->portsc,
				     XDEV_RXDETECT);
	पूर्ण अन्यथा अणु
		cdnsp_disable_port(pdev, &pdev->usb3_port.regs->portsc);
	पूर्ण

	cdnsp_set_link_state(pdev, &pdev->usb2_port.regs->portsc,
			     XDEV_RXDETECT);

	cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);

	ग_लिखोl(PORT_REG6_L1_L0_HW_EN | fs_speed, &pdev->port20_regs->port_reg6);

	ret = cdnsp_start(pdev);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	temp = पढ़ोl(&pdev->op_regs->command);
	temp |= (CMD_INTE);
	ग_लिखोl(temp, &pdev->op_regs->command);

	temp = पढ़ोl(&pdev->ir_set->irq_pending);
	ग_लिखोl(IMAN_IE_SET(temp), &pdev->ir_set->irq_pending);

	trace_cdnsp_init("Controller ready to work");
	वापस 0;
err:
	cdnsp_halt(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_gadget_udc_start(काष्ठा usb_gadget *g,
				  काष्ठा usb_gadget_driver *driver)
अणु
	क्रमागत usb_device_speed max_speed = driver->max_speed;
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(g);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&pdev->lock, flags);
	pdev->gadget_driver = driver;

	/* limit speed अगर necessary */
	max_speed = min(driver->max_speed, g->max_speed);
	ret = cdnsp_run(pdev, max_speed);

	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

/*
 * Update Event Ring Dequeue Poपूर्णांकer:
 * - When all events have finished
 * - To aव्योम "Event Ring Full Error" condition
 */
व्योम cdnsp_update_erst_dequeue(काष्ठा cdnsp_device *pdev,
			       जोड़ cdnsp_trb *event_ring_deq,
			       u8 clear_ehb)
अणु
	u64 temp_64;
	dma_addr_t deq;

	temp_64 = cdnsp_पढ़ो_64(&pdev->ir_set->erst_dequeue);

	/* If necessary, update the HW's version of the event ring deq ptr. */
	अगर (event_ring_deq != pdev->event_ring->dequeue) अणु
		deq = cdnsp_trb_virt_to_dma(pdev->event_ring->deq_seg,
					    pdev->event_ring->dequeue);
		temp_64 &= ERST_PTR_MASK;
		temp_64 |= ((u64)deq & (u64)~ERST_PTR_MASK);
	पूर्ण

	/* Clear the event handler busy flag (RW1C). */
	अगर (clear_ehb)
		temp_64 |= ERST_EHB;
	अन्यथा
		temp_64 &= ~ERST_EHB;

	cdnsp_ग_लिखो_64(temp_64, &pdev->ir_set->erst_dequeue);
पूर्ण

अटल व्योम cdnsp_clear_cmd_ring(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_segment *seg;
	u64 val_64;
	पूर्णांक i;

	cdnsp_initialize_ring_info(pdev->cmd_ring);

	seg = pdev->cmd_ring->first_seg;
	क्रम (i = 0; i < pdev->cmd_ring->num_segs; i++) अणु
		स_रखो(seg->trbs, 0,
		       माप(जोड़ cdnsp_trb) * (TRBS_PER_SEGMENT - 1));
		seg = seg->next;
	पूर्ण

	/* Set the address in the Command Ring Control रेजिस्टर. */
	val_64 = cdnsp_पढ़ो_64(&pdev->op_regs->cmd_ring);
	val_64 = (val_64 & (u64)CMD_RING_RSVD_BITS) |
		 (pdev->cmd_ring->first_seg->dma & (u64)~CMD_RING_RSVD_BITS) |
		 pdev->cmd_ring->cycle_state;
	cdnsp_ग_लिखो_64(val_64, &pdev->op_regs->cmd_ring);
पूर्ण

अटल व्योम cdnsp_consume_all_events(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_segment *event_deq_seg;
	जोड़ cdnsp_trb *event_ring_deq;
	जोड़ cdnsp_trb *event;
	u32 cycle_bit;

	event_ring_deq = pdev->event_ring->dequeue;
	event_deq_seg = pdev->event_ring->deq_seg;
	event = pdev->event_ring->dequeue;

	/* Update ring dequeue poपूर्णांकer. */
	जबतक (1) अणु
		cycle_bit = (le32_to_cpu(event->event_cmd.flags) & TRB_CYCLE);

		/* Does the controller or driver own the TRB? */
		अगर (cycle_bit != pdev->event_ring->cycle_state)
			अवरोध;

		cdnsp_inc_deq(pdev, pdev->event_ring);

		अगर (!cdnsp_last_trb_on_seg(event_deq_seg, event)) अणु
			event++;
			जारी;
		पूर्ण

		अगर (cdnsp_last_trb_on_ring(pdev->event_ring, event_deq_seg,
					   event))
			cycle_bit ^= 1;

		event_deq_seg = event_deq_seg->next;
		event = event_deq_seg->trbs;
	पूर्ण

	cdnsp_update_erst_dequeue(pdev,  event_ring_deq, 1);
पूर्ण

अटल व्योम cdnsp_stop(काष्ठा cdnsp_device *pdev)
अणु
	u32 temp;

	cdnsp_cmd_flush_ep(pdev, &pdev->eps[0]);

	/* Remove पूर्णांकernally queued request क्रम ep0. */
	अगर (!list_empty(&pdev->eps[0].pending_list)) अणु
		काष्ठा cdnsp_request *req;

		req = next_request(&pdev->eps[0].pending_list);
		अगर (req == &pdev->ep0_preq)
			cdnsp_ep_dequeue(&pdev->eps[0], req);
	पूर्ण

	cdnsp_disable_port(pdev, &pdev->usb2_port.regs->portsc);
	cdnsp_disable_port(pdev, &pdev->usb3_port.regs->portsc);
	cdnsp_disable_slot(pdev);
	cdnsp_halt(pdev);

	temp = पढ़ोl(&pdev->op_regs->status);
	ग_लिखोl((temp & ~0x1fff) | STS_EINT, &pdev->op_regs->status);
	temp = पढ़ोl(&pdev->ir_set->irq_pending);
	ग_लिखोl(IMAN_IE_CLEAR(temp), &pdev->ir_set->irq_pending);

	cdnsp_clear_port_change_bit(pdev, &pdev->usb2_port.regs->portsc);
	cdnsp_clear_port_change_bit(pdev, &pdev->usb3_port.regs->portsc);

	/* Clear पूर्णांकerrupt line */
	temp = पढ़ोl(&pdev->ir_set->irq_pending);
	temp |= IMAN_IP;
	ग_लिखोl(temp, &pdev->ir_set->irq_pending);

	cdnsp_consume_all_events(pdev);
	cdnsp_clear_cmd_ring(pdev);

	trace_cdnsp_निकास("Controller stopped.");
पूर्ण

/*
 * Stop controller.
 * This function is called by the gadget core when the driver is हटाओd.
 * Disable slot, disable IRQs, and quiesce the controller.
 */
अटल पूर्णांक cdnsp_gadget_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(g);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdev->lock, flags);
	cdnsp_stop(pdev);
	pdev->gadget_driver = शून्य;
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_gadget_get_frame(काष्ठा usb_gadget *g)
अणु
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(g);

	वापस cdnsp_get_frame(pdev);
पूर्ण

अटल व्योम __cdnsp_gadget_wakeup(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_port_regs __iomem *port_regs;
	u32 portpm, portsc;

	port_regs = pdev->active_port->regs;
	portsc = पढ़ोl(&port_regs->portsc) & PORT_PLS_MASK;

	/* Remote wakeup feature is not enabled by host. */
	अगर (pdev->gadget.speed < USB_SPEED_SUPER && portsc == XDEV_U2) अणु
		portpm = पढ़ोl(&port_regs->portpmsc);

		अगर (!(portpm & PORT_RWE))
			वापस;
	पूर्ण

	अगर (portsc == XDEV_U3 && !pdev->may_wakeup)
		वापस;

	cdnsp_set_link_state(pdev, &port_regs->portsc, XDEV_U0);

	pdev->cdnsp_state |= CDNSP_WAKEUP_PENDING;
पूर्ण

अटल पूर्णांक cdnsp_gadget_wakeup(काष्ठा usb_gadget *g)
अणु
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(g);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdev->lock, flags);
	__cdnsp_gadget_wakeup(pdev);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_gadget_set_selfघातered(काष्ठा usb_gadget *g,
					पूर्णांक is_selfघातered)
अणु
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(g);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdev->lock, flags);
	g->is_selfघातered = !!is_selfघातered;
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_gadget_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा cdnsp_device *pdev = gadget_to_cdnsp(gadget);
	काष्ठा cdns *cdns = dev_get_drvdata(pdev->dev);

	trace_cdnsp_pullup(is_on);

	अगर (!is_on) अणु
		cdnsp_reset_device(pdev);
		cdns_clear_vbus(cdns);
	पूर्ण अन्यथा अणु
		cdns_set_vbus(cdns);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops cdnsp_gadget_ops = अणु
	.get_frame		= cdnsp_gadget_get_frame,
	.wakeup			= cdnsp_gadget_wakeup,
	.set_selfघातered	= cdnsp_gadget_set_selfघातered,
	.pullup			= cdnsp_gadget_pullup,
	.udc_start		= cdnsp_gadget_udc_start,
	.udc_stop		= cdnsp_gadget_udc_stop,
पूर्ण;

अटल व्योम cdnsp_get_ep_buffering(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep)
अणु
	व्योम __iomem *reg = &pdev->cap_regs->hc_capbase;
	पूर्णांक endpoपूर्णांकs;

	reg += cdnsp_find_next_ext_cap(reg, 0, XBUF_CAP_ID);

	अगर (!pep->direction) अणु
		pep->buffering = पढ़ोl(reg + XBUF_RX_TAG_MASK_0_OFFSET);
		pep->buffering_period = पढ़ोl(reg + XBUF_RX_TAG_MASK_1_OFFSET);
		pep->buffering = (pep->buffering + 1) / 2;
		pep->buffering_period = (pep->buffering_period + 1) / 2;
		वापस;
	पूर्ण

	endpoपूर्णांकs = HCS_ENDPOINTS(pdev->hcs_params1) / 2;

	/* Set to XBUF_TX_TAG_MASK_0 रेजिस्टर. */
	reg += XBUF_TX_CMD_OFFSET + (endpoपूर्णांकs * 2 + 2) * माप(u32);
	/* Set reg to XBUF_TX_TAG_MASK_N related with this endpoपूर्णांक. */
	reg += pep->number * माप(u32) * 2;

	pep->buffering = (पढ़ोl(reg) + 1) / 2;
	pep->buffering_period = pep->buffering;
पूर्ण

अटल पूर्णांक cdnsp_gadget_init_endpoपूर्णांकs(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक max_streams = HCC_MAX_PSA(pdev->hcc_params);
	काष्ठा cdnsp_ep *pep;
	पूर्णांक i;

	INIT_LIST_HEAD(&pdev->gadget.ep_list);

	अगर (max_streams < STREAM_LOG_STREAMS) अणु
		dev_err(pdev->dev, "Stream size %d not supported\n",
			max_streams);
		वापस -EINVAL;
	पूर्ण

	max_streams = STREAM_LOG_STREAMS;

	क्रम (i = 0; i < CDNSP_ENDPOINTS_NUM; i++) अणु
		bool direction = !(i & 1); /* Start from OUT endpoपूर्णांक. */
		u8 epnum = ((i + 1) >> 1);

		अगर (!CDNSP_IF_EP_EXIST(pdev, epnum, direction))
			जारी;

		pep = &pdev->eps[i];
		pep->pdev = pdev;
		pep->number = epnum;
		pep->direction = direction; /* 0 क्रम OUT, 1 क्रम IN. */

		/*
		 * Ep0 is bidirectional, so ep0in and ep0out are represented by
		 * pdev->eps[0]
		 */
		अगर (epnum == 0) अणु
			snम_लिखो(pep->name, माप(pep->name), "ep%d%s",
				 epnum, "BiDir");

			pep->idx = 0;
			usb_ep_set_maxpacket_limit(&pep->endpoपूर्णांक, 512);
			pep->endpoपूर्णांक.maxburst = 1;
			pep->endpoपूर्णांक.ops = &cdnsp_gadget_ep0_ops;
			pep->endpoपूर्णांक.desc = &cdnsp_gadget_ep0_desc;
			pep->endpoपूर्णांक.comp_desc = शून्य;
			pep->endpoपूर्णांक.caps.type_control = true;
			pep->endpoपूर्णांक.caps.dir_in = true;
			pep->endpoपूर्णांक.caps.dir_out = true;

			pdev->ep0_preq.epnum = pep->number;
			pdev->ep0_preq.pep = pep;
			pdev->gadget.ep0 = &pep->endpoपूर्णांक;
		पूर्ण अन्यथा अणु
			snम_लिखो(pep->name, माप(pep->name), "ep%d%s",
				 epnum, (pep->direction) ? "in" : "out");

			pep->idx =  (epnum * 2 + (direction ? 1 : 0)) - 1;
			usb_ep_set_maxpacket_limit(&pep->endpoपूर्णांक, 1024);

			pep->endpoपूर्णांक.max_streams = max_streams;
			pep->endpoपूर्णांक.ops = &cdnsp_gadget_ep_ops;
			list_add_tail(&pep->endpoपूर्णांक.ep_list,
				      &pdev->gadget.ep_list);

			pep->endpoपूर्णांक.caps.type_iso = true;
			pep->endpoपूर्णांक.caps.type_bulk = true;
			pep->endpoपूर्णांक.caps.type_पूर्णांक = true;

			pep->endpoपूर्णांक.caps.dir_in = direction;
			pep->endpoपूर्णांक.caps.dir_out = !direction;
		पूर्ण

		pep->endpoपूर्णांक.name = pep->name;
		pep->in_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, pep->idx);
		pep->out_ctx = cdnsp_get_ep_ctx(&pdev->out_ctx, pep->idx);
		cdnsp_get_ep_buffering(pdev, pep);

		dev_dbg(pdev->dev, "Init %s, MPS: %04x SupType: "
			"CTRL: %s, INT: %s, BULK: %s, ISOC %s, "
			"SupDir IN: %s, OUT: %s\n",
			pep->name, 1024,
			(pep->endpoपूर्णांक.caps.type_control) ? "yes" : "no",
			(pep->endpoपूर्णांक.caps.type_पूर्णांक) ? "yes" : "no",
			(pep->endpoपूर्णांक.caps.type_bulk) ? "yes" : "no",
			(pep->endpoपूर्णांक.caps.type_iso) ? "yes" : "no",
			(pep->endpoपूर्णांक.caps.dir_in) ? "yes" : "no",
			(pep->endpoपूर्णांक.caps.dir_out) ? "yes" : "no");

		INIT_LIST_HEAD(&pep->pending_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdnsp_gadget_मुक्त_endpoपूर्णांकs(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_ep *pep;
	पूर्णांक i;

	क्रम (i = 0; i < CDNSP_ENDPOINTS_NUM; i++) अणु
		pep = &pdev->eps[i];
		अगर (pep->number != 0 && pep->out_ctx)
			list_del(&pep->endpoपूर्णांक.ep_list);
	पूर्ण
पूर्ण

व्योम cdnsp_disconnect_gadget(काष्ठा cdnsp_device *pdev)
अणु
	pdev->cdnsp_state |= CDNSP_STATE_DISCONNECT_PENDING;

	अगर (pdev->gadget_driver && pdev->gadget_driver->disconnect) अणु
		spin_unlock(&pdev->lock);
		pdev->gadget_driver->disconnect(&pdev->gadget);
		spin_lock(&pdev->lock);
	पूर्ण

	pdev->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&pdev->gadget, USB_STATE_NOTATTACHED);

	pdev->cdnsp_state &= ~CDNSP_STATE_DISCONNECT_PENDING;
पूर्ण

व्योम cdnsp_suspend_gadget(काष्ठा cdnsp_device *pdev)
अणु
	अगर (pdev->gadget_driver && pdev->gadget_driver->suspend) अणु
		spin_unlock(&pdev->lock);
		pdev->gadget_driver->suspend(&pdev->gadget);
		spin_lock(&pdev->lock);
	पूर्ण
पूर्ण

व्योम cdnsp_resume_gadget(काष्ठा cdnsp_device *pdev)
अणु
	अगर (pdev->gadget_driver && pdev->gadget_driver->resume) अणु
		spin_unlock(&pdev->lock);
		pdev->gadget_driver->resume(&pdev->gadget);
		spin_lock(&pdev->lock);
	पूर्ण
पूर्ण

व्योम cdnsp_irq_reset(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_port_regs __iomem *port_regs;

	cdnsp_reset_device(pdev);

	port_regs = pdev->active_port->regs;
	pdev->gadget.speed = cdnsp_port_speed(पढ़ोl(port_regs));

	spin_unlock(&pdev->lock);
	usb_gadget_udc_reset(&pdev->gadget, pdev->gadget_driver);
	spin_lock(&pdev->lock);

	चयन (pdev->gadget.speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_SUPER:
		cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);
		pdev->gadget.ep0->maxpacket = 512;
		अवरोध;
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_FULL:
		cdnsp_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		pdev->gadget.ep0->maxpacket = 64;
		अवरोध;
	शेष:
		/* Low speed is not supported. */
		dev_err(pdev->dev, "Unknown device speed\n");
		अवरोध;
	पूर्ण

	cdnsp_clear_chicken_bits_2(pdev, CHICKEN_XDMA_2_TP_CACHE_DIS);
	cdnsp_setup_device(pdev, SETUP_CONTEXT_ONLY);
	usb_gadget_set_state(&pdev->gadget, USB_STATE_DEFAULT);
पूर्ण

अटल व्योम cdnsp_get_rev_cap(काष्ठा cdnsp_device *pdev)
अणु
	व्योम __iomem *reg = &pdev->cap_regs->hc_capbase;

	reg += cdnsp_find_next_ext_cap(reg, 0, RTL_REV_CAP);
	pdev->rev_cap  = reg;

	dev_info(pdev->dev, "Rev: %08x/%08x, eps: %08x, buff: %08x/%08x\n",
		 पढ़ोl(&pdev->rev_cap->ctrl_revision),
		 पढ़ोl(&pdev->rev_cap->rtl_revision),
		 पढ़ोl(&pdev->rev_cap->ep_supported),
		 पढ़ोl(&pdev->rev_cap->rx_buff_size),
		 पढ़ोl(&pdev->rev_cap->tx_buff_size));
पूर्ण

अटल पूर्णांक cdnsp_gen_setup(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक ret;
	u32 reg;

	pdev->cap_regs = pdev->regs;
	pdev->op_regs = pdev->regs +
		HC_LENGTH(पढ़ोl(&pdev->cap_regs->hc_capbase));
	pdev->run_regs = pdev->regs +
		(पढ़ोl(&pdev->cap_regs->run_regs_off) & RTSOFF_MASK);

	/* Cache पढ़ो-only capability रेजिस्टरs */
	pdev->hcs_params1 = पढ़ोl(&pdev->cap_regs->hcs_params1);
	pdev->hcc_params = पढ़ोl(&pdev->cap_regs->hc_capbase);
	pdev->hci_version = HC_VERSION(pdev->hcc_params);
	pdev->hcc_params = पढ़ोl(&pdev->cap_regs->hcc_params);

	cdnsp_get_rev_cap(pdev);

	/* Make sure the Device Controller is halted. */
	ret = cdnsp_halt(pdev);
	अगर (ret)
		वापस ret;

	/* Reset the पूर्णांकernal controller memory state and रेजिस्टरs. */
	ret = cdnsp_reset(pdev);
	अगर (ret)
		वापस ret;

	/*
	 * Set dma_mask and coherent_dma_mask to 64-bits,
	 * अगर controller supports 64-bit addressing.
	 */
	अगर (HCC_64BIT_ADDR(pdev->hcc_params) &&
	    !dma_set_mask(pdev->dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(pdev->dev, "Enabling 64-bit DMA addresses.\n");
		dma_set_coherent_mask(pdev->dev, DMA_BIT_MASK(64));
	पूर्ण अन्यथा अणु
		/*
		 * This is to aव्योम error in हालs where a 32-bit USB
		 * controller is used on a 64-bit capable प्रणाली.
		 */
		ret = dma_set_mask(pdev->dev, DMA_BIT_MASK(32));
		अगर (ret)
			वापस ret;

		dev_dbg(pdev->dev, "Enabling 32-bit DMA addresses.\n");
		dma_set_coherent_mask(pdev->dev, DMA_BIT_MASK(32));
	पूर्ण

	spin_lock_init(&pdev->lock);

	ret = cdnsp_mem_init(pdev);
	अगर (ret)
		वापस ret;

	/*
	 * Software workaround क्रम U1: after transition
	 * to U1 the controller starts gating घड़ी, and in some हालs,
	 * it causes that controller stack.
	 */
	reg = पढ़ोl(&pdev->port3x_regs->mode_2);
	reg &= ~CFG_3XPORT_U1_PIPE_CLK_GATE_EN;
	ग_लिखोl(reg, &pdev->port3x_regs->mode_2);

	वापस 0;
पूर्ण

अटल पूर्णांक __cdnsp_gadget_init(काष्ठा cdns *cdns)
अणु
	काष्ठा cdnsp_device *pdev;
	u32 max_speed;
	पूर्णांक ret = -ENOMEM;

	cdns_drd_gadget_on(cdns);

	pdev = kzalloc(माप(*pdev), GFP_KERNEL);
	अगर (!pdev)
		वापस -ENOMEM;

	pm_runसमय_get_sync(cdns->dev);

	cdns->gadget_dev = pdev;
	pdev->dev = cdns->dev;
	pdev->regs = cdns->dev_regs;
	max_speed = usb_get_maximum_speed(cdns->dev);

	चयन (max_speed) अणु
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		अवरोध;
	शेष:
		dev_err(cdns->dev, "invalid speed parameter %d\n", max_speed);
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		/* Default to SSP */
		max_speed = USB_SPEED_SUPER_PLUS;
		अवरोध;
	पूर्ण

	pdev->gadget.ops = &cdnsp_gadget_ops;
	pdev->gadget.name = "cdnsp-gadget";
	pdev->gadget.speed = USB_SPEED_UNKNOWN;
	pdev->gadget.sg_supported = 1;
	pdev->gadget.max_speed = USB_SPEED_SUPER_PLUS;
	pdev->gadget.lpm_capable = 1;

	pdev->setup_buf = kzalloc(CDNSP_EP0_SETUP_SIZE, GFP_KERNEL);
	अगर (!pdev->setup_buf)
		जाओ मुक्त_pdev;

	/*
	 * Controller supports not aligned buffer but it should improve
	 * perक्रमmance.
	 */
	pdev->gadget.quirk_ep_out_aligned_size = true;

	ret = cdnsp_gen_setup(pdev);
	अगर (ret) अणु
		dev_err(pdev->dev, "Generic initialization failed %d\n", ret);
		जाओ मुक्त_setup;
	पूर्ण

	ret = cdnsp_gadget_init_endpoपूर्णांकs(pdev);
	अगर (ret) अणु
		dev_err(pdev->dev, "failed to initialize endpoints\n");
		जाओ halt_pdev;
	पूर्ण

	ret = usb_add_gadget_udc(pdev->dev, &pdev->gadget);
	अगर (ret) अणु
		dev_err(pdev->dev, "failed to register udc\n");
		जाओ मुक्त_endpoपूर्णांकs;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(pdev->dev, cdns->dev_irq,
					cdnsp_irq_handler,
					cdnsp_thपढ़ो_irq_handler, IRQF_SHARED,
					dev_name(pdev->dev), pdev);
	अगर (ret)
		जाओ del_gadget;

	वापस 0;

del_gadget:
	usb_del_gadget_udc(&pdev->gadget);
मुक्त_endpoपूर्णांकs:
	cdnsp_gadget_मुक्त_endpoपूर्णांकs(pdev);
halt_pdev:
	cdnsp_halt(pdev);
	cdnsp_reset(pdev);
	cdnsp_mem_cleanup(pdev);
मुक्त_setup:
	kमुक्त(pdev->setup_buf);
मुक्त_pdev:
	kमुक्त(pdev);

	वापस ret;
पूर्ण

अटल व्योम cdnsp_gadget_निकास(काष्ठा cdns *cdns)
अणु
	काष्ठा cdnsp_device *pdev = cdns->gadget_dev;

	devm_मुक्त_irq(pdev->dev, cdns->dev_irq, pdev);
	pm_runसमय_mark_last_busy(cdns->dev);
	pm_runसमय_put_स्वतःsuspend(cdns->dev);
	usb_del_gadget_udc(&pdev->gadget);
	cdnsp_gadget_मुक्त_endpoपूर्णांकs(pdev);
	cdnsp_mem_cleanup(pdev);
	kमुक्त(pdev);
	cdns->gadget_dev = शून्य;
	cdns_drd_gadget_off(cdns);
पूर्ण

अटल पूर्णांक cdnsp_gadget_suspend(काष्ठा cdns *cdns, bool करो_wakeup)
अणु
	काष्ठा cdnsp_device *pdev = cdns->gadget_dev;
	अचिन्हित दीर्घ flags;

	अगर (pdev->link_state == XDEV_U3)
		वापस 0;

	spin_lock_irqsave(&pdev->lock, flags);
	cdnsp_disconnect_gadget(pdev);
	cdnsp_stop(pdev);
	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_gadget_resume(काष्ठा cdns *cdns, bool hibernated)
अणु
	काष्ठा cdnsp_device *pdev = cdns->gadget_dev;
	क्रमागत usb_device_speed max_speed;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!pdev->gadget_driver)
		वापस 0;

	spin_lock_irqsave(&pdev->lock, flags);
	max_speed = pdev->gadget_driver->max_speed;

	/* Limit speed अगर necessary. */
	max_speed = min(max_speed, pdev->gadget.max_speed);

	ret = cdnsp_run(pdev, max_speed);

	अगर (pdev->link_state == XDEV_U3)
		__cdnsp_gadget_wakeup(pdev);

	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस ret;
पूर्ण

/**
 * cdnsp_gadget_init - initialize device काष्ठाure
 * @cdns: cdnsp instance
 *
 * This function initializes the gadget.
 */
पूर्णांक cdnsp_gadget_init(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, माप(*rdrv), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start	= __cdnsp_gadget_init;
	rdrv->stop	= cdnsp_gadget_निकास;
	rdrv->suspend	= cdnsp_gadget_suspend;
	rdrv->resume	= cdnsp_gadget_resume;
	rdrv->state	= CDNS_ROLE_STATE_INACTIVE;
	rdrv->name	= "gadget";
	cdns->roles[USB_ROLE_DEVICE] = rdrv;

	वापस 0;
पूर्ण
