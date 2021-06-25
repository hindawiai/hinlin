<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Driver क्रम Realtek USB card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Roger Tseng <rogerable@realtek.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/rtsx_usb.h>

अटल पूर्णांक polling_pipe = 1;
module_param(polling_pipe, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(polling_pipe, "polling pipe (0: ctl, 1: bulk)");

अटल स्थिर काष्ठा mfd_cell rtsx_usb_cells[] = अणु
	[RTSX_USB_SD_CARD] = अणु
		.name = "rtsx_usb_sdmmc",
		.pdata_size = 0,
	पूर्ण,
	[RTSX_USB_MS_CARD] = अणु
		.name = "rtsx_usb_ms",
		.pdata_size = 0,
	पूर्ण,
पूर्ण;

अटल व्योम rtsx_usb_sg_समयd_out(काष्ठा समयr_list *t)
अणु
	काष्ठा rtsx_ucr *ucr = from_समयr(ucr, t, sg_समयr);

	dev_dbg(&ucr->pusb_पूर्णांकf->dev, "%s: sg transfer timed out", __func__);
	usb_sg_cancel(&ucr->current_sg);
पूर्ण

अटल पूर्णांक rtsx_usb_bulk_transfer_sglist(काष्ठा rtsx_ucr *ucr,
		अचिन्हित पूर्णांक pipe, काष्ठा scatterlist *sg, पूर्णांक num_sg,
		अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक *act_len, पूर्णांक समयout)
अणु
	पूर्णांक ret;

	dev_dbg(&ucr->pusb_पूर्णांकf->dev, "%s: xfer %u bytes, %d entries\n",
			__func__, length, num_sg);
	ret = usb_sg_init(&ucr->current_sg, ucr->pusb_dev, pipe, 0,
			sg, num_sg, length, GFP_NOIO);
	अगर (ret)
		वापस ret;

	ucr->sg_समयr.expires = jअगरfies + msecs_to_jअगरfies(समयout);
	add_समयr(&ucr->sg_समयr);
	usb_sg_रुको(&ucr->current_sg);
	अगर (!del_समयr_sync(&ucr->sg_समयr))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = ucr->current_sg.status;

	अगर (act_len)
		*act_len = ucr->current_sg.bytes;

	वापस ret;
पूर्ण

पूर्णांक rtsx_usb_transfer_data(काष्ठा rtsx_ucr *ucr, अचिन्हित पूर्णांक pipe,
			      व्योम *buf, अचिन्हित पूर्णांक len, पूर्णांक num_sg,
			      अचिन्हित पूर्णांक *act_len, पूर्णांक समयout)
अणु
	अगर (समयout < 600)
		समयout = 600;

	अगर (num_sg)
		वापस rtsx_usb_bulk_transfer_sglist(ucr, pipe,
				(काष्ठा scatterlist *)buf, num_sg, len, act_len,
				समयout);
	अन्यथा
		वापस usb_bulk_msg(ucr->pusb_dev, pipe, buf, len, act_len,
				समयout);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_transfer_data);

अटल अंतरभूत व्योम rtsx_usb_seq_cmd_hdr(काष्ठा rtsx_ucr *ucr,
		u16 addr, u16 len, u8 seq_type)
अणु
	rtsx_usb_cmd_hdr_tag(ucr);

	ucr->cmd_buf[PACKET_TYPE] = seq_type;
	ucr->cmd_buf[5] = (u8)(len >> 8);
	ucr->cmd_buf[6] = (u8)len;
	ucr->cmd_buf[8] = (u8)(addr >> 8);
	ucr->cmd_buf[9] = (u8)addr;

	अगर (seq_type == SEQ_WRITE)
		ucr->cmd_buf[STAGE_FLAG] = 0;
	अन्यथा
		ucr->cmd_buf[STAGE_FLAG] = STAGE_R;
पूर्ण

अटल पूर्णांक rtsx_usb_seq_ग_लिखो_रेजिस्टर(काष्ठा rtsx_ucr *ucr,
		u16 addr, u16 len, u8 *data)
अणु
	u16 cmd_len = ALIGN(SEQ_WRITE_DATA_OFFSET + len, 4);

	अगर (!data)
		वापस -EINVAL;

	अगर (cmd_len > IOBUF_SIZE)
		वापस -EINVAL;

	rtsx_usb_seq_cmd_hdr(ucr, addr, len, SEQ_WRITE);
	स_नकल(ucr->cmd_buf + SEQ_WRITE_DATA_OFFSET, data, len);

	वापस rtsx_usb_transfer_data(ucr,
			usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
			ucr->cmd_buf, cmd_len, 0, शून्य, 100);
पूर्ण

अटल पूर्णांक rtsx_usb_seq_पढ़ो_रेजिस्टर(काष्ठा rtsx_ucr *ucr,
		u16 addr, u16 len, u8 *data)
अणु
	पूर्णांक i, ret;
	u16 rsp_len = round_करोwn(len, 4);
	u16 res_len = len - rsp_len;

	अगर (!data)
		वापस -EINVAL;

	/* 4-byte aligned part */
	अगर (rsp_len) अणु
		rtsx_usb_seq_cmd_hdr(ucr, addr, len, SEQ_READ);
		ret = rtsx_usb_transfer_data(ucr,
				usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
				ucr->cmd_buf, 12, 0, शून्य, 100);
		अगर (ret)
			वापस ret;

		ret = rtsx_usb_transfer_data(ucr,
				usb_rcvbulkpipe(ucr->pusb_dev, EP_BULK_IN),
				data, rsp_len, 0, शून्य, 100);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* unaligned part */
	क्रम (i = 0; i < res_len; i++) अणु
		ret = rtsx_usb_पढ़ो_रेजिस्टर(ucr, addr + rsp_len + i,
				data + rsp_len + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rtsx_usb_पढ़ो_ppbuf(काष्ठा rtsx_ucr *ucr, u8 *buf, पूर्णांक buf_len)
अणु
	वापस rtsx_usb_seq_पढ़ो_रेजिस्टर(ucr, PPBUF_BASE2, (u16)buf_len, buf);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_पढ़ो_ppbuf);

पूर्णांक rtsx_usb_ग_लिखो_ppbuf(काष्ठा rtsx_ucr *ucr, u8 *buf, पूर्णांक buf_len)
अणु
	वापस rtsx_usb_seq_ग_लिखो_रेजिस्टर(ucr, PPBUF_BASE2, (u16)buf_len, buf);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_ग_लिखो_ppbuf);

पूर्णांक rtsx_usb_ep0_ग_लिखो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr,
		u8 mask, u8 data)
अणु
	u16 value, index;

	addr |= EP0_WRITE_REG_CMD << EP0_OP_SHIFT;
	value = swab16(addr);
	index = mask | data << 8;

	वापस usb_control_msg(ucr->pusb_dev,
			usb_sndctrlpipe(ucr->pusb_dev, 0), RTSX_USB_REQ_REG_OP,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0, 100);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_ep0_ग_लिखो_रेजिस्टर);

पूर्णांक rtsx_usb_ep0_पढ़ो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 *data)
अणु
	u16 value;
	u8 *buf;
	पूर्णांक ret;

	अगर (!data)
		वापस -EINVAL;

	buf = kzalloc(माप(u8), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	addr |= EP0_READ_REG_CMD << EP0_OP_SHIFT;
	value = swab16(addr);

	ret = usb_control_msg(ucr->pusb_dev,
			usb_rcvctrlpipe(ucr->pusb_dev, 0), RTSX_USB_REQ_REG_OP,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, 0, buf, 1, 100);
	*data = *buf;

	kमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_ep0_पढ़ो_रेजिस्टर);

व्योम rtsx_usb_add_cmd(काष्ठा rtsx_ucr *ucr, u8 cmd_type, u16 reg_addr,
		u8 mask, u8 data)
अणु
	पूर्णांक i;

	अगर (ucr->cmd_idx < (IOBUF_SIZE - CMD_OFFSET) / 4) अणु
		i = CMD_OFFSET + ucr->cmd_idx * 4;

		ucr->cmd_buf[i++] = ((cmd_type & 0x03) << 6) |
			(u8)((reg_addr >> 8) & 0x3F);
		ucr->cmd_buf[i++] = (u8)reg_addr;
		ucr->cmd_buf[i++] = mask;
		ucr->cmd_buf[i++] = data;

		ucr->cmd_idx++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_add_cmd);

पूर्णांक rtsx_usb_send_cmd(काष्ठा rtsx_ucr *ucr, u8 flag, पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ucr->cmd_buf[CNT_H] = (u8)(ucr->cmd_idx >> 8);
	ucr->cmd_buf[CNT_L] = (u8)(ucr->cmd_idx);
	ucr->cmd_buf[STAGE_FLAG] = flag;

	ret = rtsx_usb_transfer_data(ucr,
			usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
			ucr->cmd_buf, ucr->cmd_idx * 4 + CMD_OFFSET,
			0, शून्य, समयout);
	अगर (ret) अणु
		rtsx_usb_clear_fsm_err(ucr);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_send_cmd);

पूर्णांक rtsx_usb_get_rsp(काष्ठा rtsx_ucr *ucr, पूर्णांक rsp_len, पूर्णांक समयout)
अणु
	अगर (rsp_len <= 0)
		वापस -EINVAL;

	rsp_len = ALIGN(rsp_len, 4);

	वापस rtsx_usb_transfer_data(ucr,
			usb_rcvbulkpipe(ucr->pusb_dev, EP_BULK_IN),
			ucr->rsp_buf, rsp_len, 0, शून्य, समयout);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_get_rsp);

अटल पूर्णांक rtsx_usb_get_status_with_bulk(काष्ठा rtsx_ucr *ucr, u16 *status)
अणु
	पूर्णांक ret;

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, CARD_EXIST, 0x00, 0x00);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, OCPSTAT, 0x00, 0x00);
	ret = rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	अगर (ret)
		वापस ret;

	ret = rtsx_usb_get_rsp(ucr, 2, 100);
	अगर (ret)
		वापस ret;

	*status = ((ucr->rsp_buf[0] >> 2) & 0x0f) |
		  ((ucr->rsp_buf[1] & 0x03) << 4);

	वापस 0;
पूर्ण

पूर्णांक rtsx_usb_get_card_status(काष्ठा rtsx_ucr *ucr, u16 *status)
अणु
	पूर्णांक ret;
	u16 *buf;

	अगर (!status)
		वापस -EINVAL;

	अगर (polling_pipe == 0) अणु
		buf = kzalloc(माप(u16), GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		ret = usb_control_msg(ucr->pusb_dev,
				usb_rcvctrlpipe(ucr->pusb_dev, 0),
				RTSX_USB_REQ_POLL,
				USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, 0, buf, 2, 100);
		*status = *buf;

		kमुक्त(buf);
	पूर्ण अन्यथा अणु
		ret = rtsx_usb_get_status_with_bulk(ucr, status);
	पूर्ण

	/* usb_control_msg may वापस positive when success */
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_get_card_status);

अटल पूर्णांक rtsx_usb_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u8 addr, u8 val)
अणु
	dev_dbg(&ucr->pusb_पूर्णांकf->dev, "Write 0x%x to phy register 0x%x\n",
			val, addr);

	rtsx_usb_init_cmd(ucr);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VSTAIN, 0xFF, val);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VCONTROL, 0xFF, addr & 0x0F);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x00);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x00);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x01);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VCONTROL,
			0xFF, (addr >> 4) & 0x0F);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x00);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x00);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, HS_VLOADM, 0xFF, 0x01);

	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण

पूर्णांक rtsx_usb_ग_लिखो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 mask, u8 data)
अणु
	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, addr, mask, data);
	वापस rtsx_usb_send_cmd(ucr, MODE_C, 100);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_ग_लिखो_रेजिस्टर);

पूर्णांक rtsx_usb_पढ़ो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 *data)
अणु
	पूर्णांक ret;

	अगर (data != शून्य)
		*data = 0;

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, READ_REG_CMD, addr, 0, 0);
	ret = rtsx_usb_send_cmd(ucr, MODE_CR, 100);
	अगर (ret)
		वापस ret;

	ret = rtsx_usb_get_rsp(ucr, 1, 100);
	अगर (ret)
		वापस ret;

	अगर (data != शून्य)
		*data = ucr->rsp_buf[0];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_पढ़ो_रेजिस्टर);

अटल अंतरभूत u8 द्विगुन_ssc_depth(u8 depth)
अणु
	वापस (depth > 1) ? (depth - 1) : depth;
पूर्ण

अटल u8 revise_ssc_depth(u8 ssc_depth, u8 भाग)
अणु
	अगर (भाग > CLK_DIV_1) अणु
		अगर (ssc_depth > भाग - 1)
			ssc_depth -= (भाग - 1);
		अन्यथा
			ssc_depth = SSC_DEPTH_2M;
	पूर्ण

	वापस ssc_depth;
पूर्ण

पूर्णांक rtsx_usb_चयन_घड़ी(काष्ठा rtsx_ucr *ucr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk)
अणु
	पूर्णांक ret;
	u8 n, clk_भागider, mcu_cnt, भाग;

	अगर (!card_घड़ी) अणु
		ucr->cur_clk = 0;
		वापस 0;
	पूर्ण

	अगर (initial_mode) अणु
		/* We use 250k(around) here, in initial stage */
		clk_भागider = SD_CLK_DIVIDE_128;
		card_घड़ी = 30000000;
	पूर्ण अन्यथा अणु
		clk_भागider = SD_CLK_DIVIDE_0;
	पूर्ण

	ret = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, clk_भागider);
	अगर (ret < 0)
		वापस ret;

	card_घड़ी /= 1000000;
	dev_dbg(&ucr->pusb_पूर्णांकf->dev,
			"Switch card clock to %dMHz\n", card_घड़ी);

	अगर (!initial_mode && द्विगुन_clk)
		card_घड़ी *= 2;
	dev_dbg(&ucr->pusb_पूर्णांकf->dev,
			"Internal SSC clock: %dMHz (cur_clk = %d)\n",
			card_घड़ी, ucr->cur_clk);

	अगर (card_घड़ी == ucr->cur_clk)
		वापस 0;

	/* Converting घड़ी value पूर्णांकo पूर्णांकernal settings: n and भाग */
	n = card_घड़ी - 2;
	अगर ((card_घड़ी <= 2) || (n > MAX_DIV_N))
		वापस -EINVAL;

	mcu_cnt = 60/card_घड़ी + 3;
	अगर (mcu_cnt > 15)
		mcu_cnt = 15;

	/* Make sure that the SSC घड़ी भाग_n is not less than MIN_DIV_N */

	भाग = CLK_DIV_1;
	जबतक (n < MIN_DIV_N && भाग < CLK_DIV_4) अणु
		n = (n + 2) * 2 - 2;
		भाग++;
	पूर्ण
	dev_dbg(&ucr->pusb_पूर्णांकf->dev, "n = %d, div = %d\n", n, भाग);

	अगर (द्विगुन_clk)
		ssc_depth = द्विगुन_ssc_depth(ssc_depth);

	ssc_depth = revise_ssc_depth(ssc_depth, भाग);
	dev_dbg(&ucr->pusb_पूर्णांकf->dev, "ssc_depth = %d\n", ssc_depth);

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV, CLK_CHANGE, CLK_CHANGE);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV,
			0x3F, (भाग << 4) | mcu_cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL2,
			SSC_DEPTH_MASK, ssc_depth);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	अगर (vpclk) अणु
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, 0);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, PHASE_NOT_RESET);
	पूर्ण

	ret = rtsx_usb_send_cmd(ucr, MODE_C, 2000);
	अगर (ret < 0)
		वापस ret;

	ret = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, SSC_CTL1, 0xff,
			SSC_RSTB | SSC_8X_EN | SSC_SEL_4M);
	अगर (ret < 0)
		वापस ret;

	/* Wait SSC घड़ी stable */
	usleep_range(100, 1000);

	ret = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, CLK_DIV, CLK_CHANGE, 0);
	अगर (ret < 0)
		वापस ret;

	ucr->cur_clk = card_घड़ी;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_चयन_घड़ी);

पूर्णांक rtsx_usb_card_exclusive_check(काष्ठा rtsx_ucr *ucr, पूर्णांक card)
अणु
	पूर्णांक ret;
	u16 val;
	u16 cd_mask[] = अणु
		[RTSX_USB_SD_CARD] = (CD_MASK & ~SD_CD),
		[RTSX_USB_MS_CARD] = (CD_MASK & ~MS_CD)
	पूर्ण;

	ret = rtsx_usb_get_card_status(ucr, &val);
	/*
	 * If get status fails, वापस 0 (ok) क्रम the exclusive check
	 * and let the flow fail at somewhere अन्यथा.
	 */
	अगर (ret)
		वापस 0;

	अगर (val & cd_mask[card])
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_usb_card_exclusive_check);

अटल पूर्णांक rtsx_usb_reset_chip(काष्ठा rtsx_ucr *ucr)
अणु
	पूर्णांक ret;
	u8 val;

	rtsx_usb_init_cmd(ucr);

	अगर (CHECK_PKG(ucr, LQFP48)) अणु
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
				LDO3318_PWR_MASK, LDO_SUSPEND);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PWR_CTL,
				FORCE_LDO_POWERB, FORCE_LDO_POWERB);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL1,
				0x30, 0x10);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL5,
				0x03, 0x01);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_PULL_CTL6,
				0x0C, 0x04);
	पूर्ण

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SYS_DUMMY0, NYET_MSAK, NYET_EN);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CD_DEGLITCH_WIDTH, 0xFF, 0x08);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
			CD_DEGLITCH_EN, XD_CD_DEGLITCH_EN, 0x0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD30_DRIVE_SEL,
			SD30_DRIVE_MASK, DRIVER_TYPE_D);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
			CARD_DRIVE_SEL, SD20_DRIVE_MASK, 0x0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, LDO_POWER_CFG, 0xE0, 0x0);

	अगर (ucr->is_rts5179)
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD,
				CARD_PULL_CTL5, 0x03, 0x01);

	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_DMA1_CTL,
		       EXTEND_DMA1_ASYNC_SIGNAL, EXTEND_DMA1_ASYNC_SIGNAL);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CARD_INT_PEND,
			XD_INT | MS_INT | SD_INT,
			XD_INT | MS_INT | SD_INT);

	ret = rtsx_usb_send_cmd(ucr, MODE_C, 100);
	अगर (ret)
		वापस ret;

	/* config non-crystal mode */
	rtsx_usb_पढ़ो_रेजिस्टर(ucr, CFG_MODE, &val);
	अगर ((val & XTAL_FREE) || ((val & CLK_MODE_MASK) == CLK_MODE_NON_XTAL)) अणु
		ret = rtsx_usb_ग_लिखो_phy_रेजिस्टर(ucr, 0xC2, 0x7C);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_init_chip(काष्ठा rtsx_ucr *ucr)
अणु
	पूर्णांक ret;
	u8 val;

	rtsx_usb_clear_fsm_err(ucr);

	/* घातer on SSC */
	ret = rtsx_usb_ग_लिखो_रेजिस्टर(ucr,
			FPDCTL, SSC_POWER_MASK, SSC_POWER_ON);
	अगर (ret)
		वापस ret;

	usleep_range(100, 1000);
	ret = rtsx_usb_ग_लिखो_रेजिस्टर(ucr, CLK_DIV, CLK_CHANGE, 0x00);
	अगर (ret)
		वापस ret;

	/* determine IC version */
	ret = rtsx_usb_पढ़ो_रेजिस्टर(ucr, HW_VERSION, &val);
	अगर (ret)
		वापस ret;

	ucr->ic_version = val & HW_VER_MASK;

	/* determine package */
	ret = rtsx_usb_पढ़ो_रेजिस्टर(ucr, CARD_SHARE_MODE, &val);
	अगर (ret)
		वापस ret;

	अगर (val & CARD_SHARE_LQFP_SEL) अणु
		ucr->package = LQFP48;
		dev_dbg(&ucr->pusb_पूर्णांकf->dev, "Package: LQFP48\n");
	पूर्ण अन्यथा अणु
		ucr->package = QFN24;
		dev_dbg(&ucr->pusb_पूर्णांकf->dev, "Package: QFN24\n");
	पूर्ण

	/* determine IC variations */
	rtsx_usb_पढ़ो_रेजिस्टर(ucr, CFG_MODE_1, &val);
	अगर (val & RTS5179) अणु
		ucr->is_rts5179 = true;
		dev_dbg(&ucr->pusb_पूर्णांकf->dev, "Device is rts5179\n");
	पूर्ण अन्यथा अणु
		ucr->is_rts5179 = false;
	पूर्ण

	वापस rtsx_usb_reset_chip(ucr);
पूर्ण

अटल पूर्णांक rtsx_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा rtsx_ucr *ucr;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev,
		": Realtek USB Card Reader found at bus %03d address %03d\n",
		 usb_dev->bus->busnum, usb_dev->devnum);

	ucr = devm_kzalloc(&पूर्णांकf->dev, माप(*ucr), GFP_KERNEL);
	अगर (!ucr)
		वापस -ENOMEM;

	ucr->pusb_dev = usb_dev;

	ucr->iobuf = usb_alloc_coherent(ucr->pusb_dev, IOBUF_SIZE,
			GFP_KERNEL, &ucr->iobuf_dma);
	अगर (!ucr->iobuf)
		वापस -ENOMEM;

	usb_set_पूर्णांकfdata(पूर्णांकf, ucr);

	ucr->venकरोr_id = id->idVenकरोr;
	ucr->product_id = id->idProduct;
	ucr->cmd_buf = ucr->rsp_buf = ucr->iobuf;

	mutex_init(&ucr->dev_mutex);

	ucr->pusb_पूर्णांकf = पूर्णांकf;

	/* initialize */
	ret = rtsx_usb_init_chip(ucr);
	अगर (ret)
		जाओ out_init_fail;

	/* initialize USB SG transfer समयr */
	समयr_setup(&ucr->sg_समयr, rtsx_usb_sg_समयd_out, 0);

	ret = mfd_add_hotplug_devices(&पूर्णांकf->dev, rtsx_usb_cells,
				      ARRAY_SIZE(rtsx_usb_cells));
	अगर (ret)
		जाओ out_init_fail;

#अगर_घोषित CONFIG_PM
	पूर्णांकf->needs_remote_wakeup = 1;
	usb_enable_स्वतःsuspend(usb_dev);
#पूर्ण_अगर

	वापस 0;

out_init_fail:
	usb_मुक्त_coherent(ucr->pusb_dev, IOBUF_SIZE, ucr->iobuf,
			ucr->iobuf_dma);
	वापस ret;
पूर्ण

अटल व्योम rtsx_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rtsx_ucr *ucr = (काष्ठा rtsx_ucr *)usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&पूर्णांकf->dev, "%s called\n", __func__);

	mfd_हटाओ_devices(&पूर्णांकf->dev);

	usb_set_पूर्णांकfdata(ucr->pusb_पूर्णांकf, शून्य);
	usb_मुक्त_coherent(ucr->pusb_dev, IOBUF_SIZE, ucr->iobuf,
			ucr->iobuf_dma);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rtsx_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा rtsx_ucr *ucr =
		(काष्ठा rtsx_ucr *)usb_get_पूर्णांकfdata(पूर्णांकf);
	u16 val = 0;

	dev_dbg(&पूर्णांकf->dev, "%s called with pm message 0x%04x\n",
			__func__, message.event);

	अगर (PMSG_IS_AUTO(message)) अणु
		अगर (mutex_trylock(&ucr->dev_mutex)) अणु
			rtsx_usb_get_card_status(ucr, &val);
			mutex_unlock(&ucr->dev_mutex);

			/* Defer the स्वतःsuspend अगर card exists */
			अगर (val & (SD_CD | MS_CD))
				वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			/* There is an ongoing operation*/
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_resume_child(काष्ठा device *dev, व्योम *data)
अणु
	pm_request_resume(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	device_क्रम_each_child(&पूर्णांकf->dev, शून्य, rtsx_usb_resume_child);
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rtsx_ucr *ucr =
		(काष्ठा rtsx_ucr *)usb_get_पूर्णांकfdata(पूर्णांकf);

	rtsx_usb_reset_chip(ucr);
	device_क्रम_each_child(&पूर्णांकf->dev, शून्य, rtsx_usb_resume_child);
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_PM */

#घोषणा rtsx_usb_suspend शून्य
#घोषणा rtsx_usb_resume शून्य
#घोषणा rtsx_usb_reset_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */


अटल पूर्णांक rtsx_usb_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rtsx_ucr *ucr = (काष्ठा rtsx_ucr *)usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&ucr->dev_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_usb_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rtsx_ucr *ucr = (काष्ठा rtsx_ucr *)usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_unlock(&ucr->dev_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_device_id rtsx_usb_usb_ids[] = अणु
	अणु USB_DEVICE(0x0BDA, 0x0129) पूर्ण,
	अणु USB_DEVICE(0x0BDA, 0x0139) पूर्ण,
	अणु USB_DEVICE(0x0BDA, 0x0140) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, rtsx_usb_usb_ids);

अटल काष्ठा usb_driver rtsx_usb_driver = अणु
	.name			= "rtsx_usb",
	.probe			= rtsx_usb_probe,
	.disconnect		= rtsx_usb_disconnect,
	.suspend		= rtsx_usb_suspend,
	.resume			= rtsx_usb_resume,
	.reset_resume		= rtsx_usb_reset_resume,
	.pre_reset		= rtsx_usb_pre_reset,
	.post_reset		= rtsx_usb_post_reset,
	.id_table		= rtsx_usb_usb_ids,
	.supports_स्वतःsuspend	= 1,
	.soft_unbind		= 1,
पूर्ण;

module_usb_driver(rtsx_usb_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Roger Tseng <rogerable@realtek.com>");
MODULE_DESCRIPTION("Realtek USB Card Reader Driver");
