<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bdc_cmd.c - BRCM BDC USB3.0 device controller
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश "bdc.h"
#समावेश "bdc_cmd.h"
#समावेश "bdc_dbg.h"

/* Issues a cmd to cmd processor and रुकोs क्रम cmd completion */
अटल पूर्णांक bdc_issue_cmd(काष्ठा bdc *bdc, u32 cmd_sc, u32 param0,
							u32 param1, u32 param2)
अणु
	u32 समयout = BDC_CMD_TIMEOUT;
	u32 cmd_status;
	u32 temp;

	bdc_ग_लिखोl(bdc->regs, BDC_CMDPAR0, param0);
	bdc_ग_लिखोl(bdc->regs, BDC_CMDPAR1, param1);
	bdc_ग_लिखोl(bdc->regs, BDC_CMDPAR2, param2);

	/* Issue the cmd */
	/* Make sure the cmd params are written beक्रमe asking HW to exec cmd */
	wmb();
	bdc_ग_लिखोl(bdc->regs, BDC_CMDSC, cmd_sc | BDC_CMD_CWS | BDC_CMD_SRD);
	करो अणु
		temp = bdc_पढ़ोl(bdc->regs, BDC_CMDSC);
		dev_dbg_ratelimited(bdc->dev, "cmdsc=%x", temp);
		cmd_status =  BDC_CMD_CST(temp);
		अगर (cmd_status != BDC_CMDS_BUSY)  अणु
			dev_dbg(bdc->dev,
				"command completed cmd_sts:%x\n", cmd_status);
			वापस cmd_status;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (समयout--);

	dev_err(bdc->dev,
		"command operation timedout cmd_status=%d\n", cmd_status);

	वापस cmd_status;
पूर्ण

/* Submits cmd and analyze the वापस value of bdc_issue_cmd */
अटल पूर्णांक bdc_submit_cmd(काष्ठा bdc *bdc, u32 cmd_sc,
					u32 param0, u32 param1,	u32 param2)
अणु
	u32 temp, cmd_status;
	पूर्णांक ret;

	temp = bdc_पढ़ोl(bdc->regs, BDC_CMDSC);
	dev_dbg(bdc->dev,
		"%s:CMDSC:%08x cmdsc:%08x param0=%08x param1=%08x param2=%08x\n",
		 __func__, temp, cmd_sc, param0, param1, param2);

	cmd_status = BDC_CMD_CST(temp);
	अगर (cmd_status  ==  BDC_CMDS_BUSY) अणु
		dev_err(bdc->dev, "command processor busy: %x\n", cmd_status);
		वापस -EBUSY;
	पूर्ण
	ret = bdc_issue_cmd(bdc, cmd_sc, param0, param1, param2);
	चयन (ret) अणु
	हाल BDC_CMDS_SUCC:
		dev_dbg(bdc->dev, "command completed successfully\n");
		ret = 0;
		अवरोध;

	हाल BDC_CMDS_PARA:
		dev_err(bdc->dev, "command parameter error\n");
		ret = -EINVAL;
		अवरोध;

	हाल BDC_CMDS_STAT:
		dev_err(bdc->dev, "Invalid device/ep state\n");
		ret = -EINVAL;
		अवरोध;

	हाल BDC_CMDS_FAIL:
		dev_err(bdc->dev, "Command failed?\n");
		ret = -EAGAIN;
		अवरोध;

	हाल BDC_CMDS_INTL:
		dev_err(bdc->dev, "BDC Internal error\n");
		ret = -ECONNRESET;
		अवरोध;

	हाल BDC_CMDS_BUSY:
		dev_err(bdc->dev,
			"command timedout waited for %dusec\n",
			BDC_CMD_TIMEOUT);
		ret = -ECONNRESET;
		अवरोध;
	शेष:
		dev_dbg(bdc->dev, "Unknown command completion code:%x\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

/* Deconfigure the endpoपूर्णांक from HW */
पूर्णांक bdc_dconfig_ep(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep)
अणु
	u32 cmd_sc;

	cmd_sc = BDC_SUB_CMD_DRP_EP|BDC_CMD_EPN(ep->ep_num)|BDC_CMD_EPC;
	dev_dbg(bdc->dev, "%s ep->ep_num =%d cmd_sc=%x\n", __func__,
							ep->ep_num, cmd_sc);

	वापस bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
पूर्ण

/* Reinitalize the bdlist after config ep command */
अटल व्योम ep_bd_list_reinit(काष्ठा bdc_ep *ep)
अणु
	काष्ठा bdc *bdc = ep->bdc;
	काष्ठा bdc_bd *bd;

	ep->bd_list.eqp_bdi = 0;
	ep->bd_list.hwd_bdi = 0;
	bd = ep->bd_list.bd_table_array[0]->start_bd;
	dev_dbg(bdc->dev, "%s ep:%p bd:%p\n", __func__, ep, bd);
	स_रखो(bd, 0, माप(काष्ठा bdc_bd));
	bd->offset[3] |= cpu_to_le32(BD_SBF);
पूर्ण

/* Configure an endpoपूर्णांक */
पूर्णांक bdc_config_ep(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep)
अणु
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
	u32 param0, param1, param2, cmd_sc;
	u32 mps, mbs, mul, si;
	पूर्णांक ret;

	desc = ep->desc;
	comp_desc = ep->comp_desc;
	cmd_sc = mul = mbs = param2 = 0;
	param0 = lower_32_bits(ep->bd_list.bd_table_array[0]->dma);
	param1 = upper_32_bits(ep->bd_list.bd_table_array[0]->dma);
	cpu_to_le32s(&param0);
	cpu_to_le32s(&param1);

	dev_dbg(bdc->dev, "%s: param0=%08x param1=%08x",
						__func__, param0, param1);
	si = desc->bInterval;
	si = clamp_val(si, 1, 16) - 1;

	mps = usb_endpoपूर्णांक_maxp(desc);
	mps &= 0x7ff;
	param2 |= mps << MP_SHIFT;
	param2 |= usb_endpoपूर्णांक_type(desc) << EPT_SHIFT;

	चयन (bdc->gadget.speed) अणु
	हाल USB_SPEED_SUPER:
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) ||
					usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
			param2 |= si;
			अगर (usb_endpoपूर्णांक_xfer_isoc(desc) && comp_desc)
				mul = comp_desc->bmAttributes;

		पूर्ण
		param2 |= mul << EPM_SHIFT;
		अगर (comp_desc)
			mbs = comp_desc->bMaxBurst;
		param2 |= mbs << MB_SHIFT;
		अवरोध;

	हाल USB_SPEED_HIGH:
		अगर (usb_endpoपूर्णांक_xfer_isoc(desc) ||
					usb_endpoपूर्णांक_xfer_पूर्णांक(desc)) अणु
			param2 |= si;

			mbs = usb_endpoपूर्णांक_maxp_mult(desc);
			param2 |= mbs << MB_SHIFT;
		पूर्ण
		अवरोध;

	हाल USB_SPEED_FULL:
	हाल USB_SPEED_LOW:
		/* the hardware accepts SI in 125usec range */
		अगर (usb_endpoपूर्णांक_xfer_isoc(desc))
			si += 3;

		/*
		 * FS Int endpoपूर्णांकs can have si of 1-255ms but the controller
		 * accepts 2^bInterval*125usec, so convert ms to nearest घातer
		 * of 2
		 */
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc))
			si = fls(desc->bInterval * 8) - 1;

		param2 |= si;
		अवरोध;
	शेष:
		dev_err(bdc->dev, "UNKNOWN speed ERR\n");
		वापस -EINVAL;
	पूर्ण

	cmd_sc |= BDC_CMD_EPC|BDC_CMD_EPN(ep->ep_num)|BDC_SUB_CMD_ADD_EP;

	dev_dbg(bdc->dev, "cmd_sc=%x param2=%08x\n", cmd_sc, param2);
	ret = bdc_submit_cmd(bdc, cmd_sc, param0, param1, param2);
	अगर (ret) अणु
		dev_err(bdc->dev, "command failed :%x\n", ret);
		वापस ret;
	पूर्ण
	ep_bd_list_reinit(ep);

	वापस ret;
पूर्ण

/*
 * Change the HW deq poपूर्णांकer, अगर this command is successful, HW will start
 * fetching the next bd from address dma_addr.
 */
पूर्णांक bdc_ep_bla(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep, dma_addr_t dma_addr)
अणु
	u32 param0, param1;
	u32 cmd_sc = 0;

	dev_dbg(bdc->dev, "%s: add=%08llx\n", __func__,
				(अचिन्हित दीर्घ दीर्घ)(dma_addr));
	param0 = lower_32_bits(dma_addr);
	param1 = upper_32_bits(dma_addr);
	cpu_to_le32s(&param0);
	cpu_to_le32s(&param1);

	cmd_sc |= BDC_CMD_EPN(ep->ep_num)|BDC_CMD_BLA;
	dev_dbg(bdc->dev, "cmd_sc=%x\n", cmd_sc);

	वापस bdc_submit_cmd(bdc, cmd_sc, param0, param1, 0);
पूर्ण

/* Set the address sent bu Host in SET_ADD request */
पूर्णांक bdc_address_device(काष्ठा bdc *bdc, u32 add)
अणु
	u32 cmd_sc = 0;
	u32 param2;

	dev_dbg(bdc->dev, "%s: add=%d\n", __func__, add);
	cmd_sc |=  BDC_SUB_CMD_ADD|BDC_CMD_DVC;
	param2 = add & 0x7f;

	वापस bdc_submit_cmd(bdc, cmd_sc, 0, 0, param2);
पूर्ण

/* Send a Function Wake notअगरication packet using FH command */
पूर्णांक bdc_function_wake_fh(काष्ठा bdc *bdc, u8 पूर्णांकf)
अणु
	u32 param0, param1;
	u32 cmd_sc = 0;

	param0 = param1 = 0;
	dev_dbg(bdc->dev, "%s intf=%d\n", __func__, पूर्णांकf);
	cmd_sc  |=  BDC_CMD_FH;
	param0 |= TRA_PACKET;
	param0 |= (bdc->dev_addr << 25);
	param1 |= DEV_NOTF_TYPE;
	param1 |= (FWK_SUBTYPE<<4);
	dev_dbg(bdc->dev, "param0=%08x param1=%08x\n", param0, param1);

	वापस bdc_submit_cmd(bdc, cmd_sc, param0, param1, 0);
पूर्ण

/* Send a Function Wake notअगरication packet using DNC command */
पूर्णांक bdc_function_wake(काष्ठा bdc *bdc, u8 पूर्णांकf)
अणु
	u32 cmd_sc = 0;
	u32 param2 = 0;

	dev_dbg(bdc->dev, "%s intf=%d", __func__, पूर्णांकf);
	param2 |= पूर्णांकf;
	cmd_sc |= BDC_SUB_CMD_FWK|BDC_CMD_DNC;

	वापस bdc_submit_cmd(bdc, cmd_sc, 0, 0, param2);
पूर्ण

/* Stall the endpoपूर्णांक */
पूर्णांक bdc_ep_set_stall(काष्ठा bdc *bdc, पूर्णांक epnum)
अणु
	u32 cmd_sc = 0;

	dev_dbg(bdc->dev, "%s epnum=%d\n", __func__, epnum);
	/* issue a stall endpoपूर्णांक command */
	cmd_sc |=  BDC_SUB_CMD_EP_STL | BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	वापस bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
पूर्ण

/* resets the endpoपूर्णांक, called when host sends CLEAR_FEATURE(HALT) */
पूर्णांक bdc_ep_clear_stall(काष्ठा bdc *bdc, पूर्णांक epnum)
अणु
	काष्ठा bdc_ep *ep;
	u32 cmd_sc = 0;
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s: epnum=%d\n", __func__, epnum);
	ep = bdc->bdc_ep_array[epnum];
	/*
	 * If we are not in stalled then stall Endpoपूर्णांक and issue clear stall,
	 * his will reset the seq number क्रम non EP0.
	 */
	अगर (epnum != 1) अणु
		/* अगर the endpoपूर्णांक it not stallled */
		अगर (!(ep->flags & BDC_EP_STALL)) अणु
			ret = bdc_ep_set_stall(bdc, epnum);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	/* Preserve the seq number क्रम ep0 only */
	अगर (epnum != 1)
		cmd_sc |= BDC_CMD_EPO_RST_SN;

	/* issue a reset endpoपूर्णांक command */
	cmd_sc |=  BDC_SUB_CMD_EP_RST | BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	ret = bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
	अगर (ret) अणु
		dev_err(bdc->dev, "command failed:%x\n", ret);
		वापस ret;
	पूर्ण
	bdc_notअगरy_xfr(bdc, epnum);

	वापस ret;
पूर्ण

/* Stop the endpoपूर्णांक, called when software wants to dequeue some request */
पूर्णांक bdc_stop_ep(काष्ठा bdc *bdc, पूर्णांक epnum)
अणु
	काष्ठा bdc_ep *ep;
	u32 cmd_sc = 0;
	पूर्णांक ret;

	ep = bdc->bdc_ep_array[epnum];
	dev_dbg(bdc->dev, "%s: ep:%s ep->flags:%08x\n", __func__,
						ep->name, ep->flags);
	/* Endpoपूर्णांक has to be in running state to execute stop ep command */
	अगर (!(ep->flags & BDC_EP_ENABLED)) अणु
		dev_err(bdc->dev, "stop endpoint called for disabled ep\n");
		वापस   -EINVAL;
	पूर्ण
	अगर ((ep->flags & BDC_EP_STALL) || (ep->flags & BDC_EP_STOP))
		वापस 0;

	/* issue a stop endpoपूर्णांक command */
	cmd_sc |= BDC_CMD_EP0_XSD | BDC_SUB_CMD_EP_STP
				| BDC_CMD_EPN(epnum) | BDC_CMD_EPO;

	ret = bdc_submit_cmd(bdc, cmd_sc, 0, 0, 0);
	अगर (ret) अणु
		dev_err(bdc->dev,
			"stop endpoint command didn't complete:%d ep:%s\n",
			ret, ep->name);
		वापस ret;
	पूर्ण
	ep->flags |= BDC_EP_STOP;
	bdc_dump_epsts(bdc);

	वापस ret;
पूर्ण
