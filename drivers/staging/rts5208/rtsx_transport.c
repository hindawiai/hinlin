<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>

#समावेश "rtsx.h"

/***********************************************************************
 * Scatter-gather transfer buffer access routines
 ***********************************************************************/

/*
 * Copy a buffer of length buflen to/from the srb's transfer buffer.
 * (Note: क्रम scatter-gather transfers (srb->use_sg > 0), srb->request_buffer
 * poपूर्णांकs to a list of s-g entries and we ignore srb->request_bufflen.
 * For non-scatter-gather transfers, srb->request_buffer poपूर्णांकs to the
 * transfer buffer itself and srb->request_bufflen is the buffer's length.)
 * Update the *index and *offset variables so that the next copy will
 * pick up from where this one left off.
 */

अचिन्हित पूर्णांक rtsx_stor_access_xfer_buf(अचिन्हित अक्षर *buffer,
				       अचिन्हित पूर्णांक buflen,
				       काष्ठा scsi_cmnd *srb,
				       अचिन्हित पूर्णांक *index,
				       अचिन्हित पूर्णांक *offset,
				       क्रमागत xfer_buf_dir dir)
अणु
	अचिन्हित पूर्णांक cnt;

	/* If not using scatter-gather, just transfer the data directly. */
	अगर (scsi_sg_count(srb) == 0) अणु
		अचिन्हित अक्षर *sgbuffer;

		अगर (*offset >= scsi_bufflen(srb))
			वापस 0;
		cnt = min(buflen, scsi_bufflen(srb) - *offset);

		sgbuffer = (अचिन्हित अक्षर *)scsi_sglist(srb) + *offset;

		अगर (dir == TO_XFER_BUF)
			स_नकल(sgbuffer, buffer, cnt);
		अन्यथा
			स_नकल(buffer, sgbuffer, cnt);
		*offset += cnt;

	/*
	 * Using scatter-gather.  We have to go through the list one entry
	 * at a समय.  Each s-g entry contains some number of pages, and
	 * each page has to be kmap()'ed separately.
	 */
	पूर्ण अन्यथा अणु
		काष्ठा scatterlist *sg =
				(काष्ठा scatterlist *)scsi_sglist(srb)
				+ *index;

		/*
		 * This loop handles a single s-g list entry, which may
		 * include multiple pages.  Find the initial page काष्ठाure
		 * and the starting offset within the page, and update
		 * the *offset and *index values क्रम the next loop.
		 */
		cnt = 0;
		जबतक (cnt < buflen && *index < scsi_sg_count(srb)) अणु
			काष्ठा page *page = sg_page(sg) +
					((sg->offset + *offset) >> PAGE_SHIFT);
			अचिन्हित पूर्णांक poff = (sg->offset + *offset) &
					    (PAGE_SIZE - 1);
			अचिन्हित पूर्णांक sglen = sg->length - *offset;

			अगर (sglen > buflen - cnt) अणु
				/* Transfer ends within this s-g entry */
				sglen = buflen - cnt;
				*offset += sglen;
			पूर्ण अन्यथा अणु
				/* Transfer जारीs to next s-g entry */
				*offset = 0;
				++*index;
				++sg;
			पूर्ण

			जबतक (sglen > 0) अणु
				अचिन्हित पूर्णांक plen = min(sglen, (अचिन्हित पूर्णांक)
						PAGE_SIZE - poff);
				अचिन्हित अक्षर *ptr = kmap(page);

				अगर (dir == TO_XFER_BUF)
					स_नकल(ptr + poff, buffer + cnt, plen);
				अन्यथा
					स_नकल(buffer + cnt, ptr + poff, plen);
				kunmap(page);

				/* Start at the beginning of the next page */
				poff = 0;
				++page;
				cnt += plen;
				sglen -= plen;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Return the amount actually transferred */
	वापस cnt;
पूर्ण

/*
 * Store the contents of buffer पूर्णांकo srb's transfer buffer and set the
 * SCSI residue.
 */
व्योम rtsx_stor_set_xfer_buf(अचिन्हित अक्षर *buffer,
			    अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb)
अणु
	अचिन्हित पूर्णांक index = 0, offset = 0;

	rtsx_stor_access_xfer_buf(buffer, buflen, srb, &index, &offset,
				  TO_XFER_BUF);
	अगर (buflen < scsi_bufflen(srb))
		scsi_set_resid(srb, scsi_bufflen(srb) - buflen);
पूर्ण

व्योम rtsx_stor_get_xfer_buf(अचिन्हित अक्षर *buffer,
			    अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb)
अणु
	अचिन्हित पूर्णांक index = 0, offset = 0;

	rtsx_stor_access_xfer_buf(buffer, buflen, srb, &index, &offset,
				  FROM_XFER_BUF);
	अगर (buflen < scsi_bufflen(srb))
		scsi_set_resid(srb, scsi_bufflen(srb) - buflen);
पूर्ण

/***********************************************************************
 * Transport routines
 ***********************************************************************/

/*
 * Invoke the transport and basic error-handling/recovery methods
 *
 * This is used to send the message to the device and receive the response.
 */
व्योम rtsx_invoke_transport(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक result;

	result = rtsx_scsi_handler(srb, chip);

	/*
	 * अगर the command माला_लो पातed by the higher layers, we need to
	 * लघु-circuit all other processing.
	 */
	अगर (rtsx_chk_stat(chip, RTSX_STAT_ABORT)) अणु
		dev_dbg(rtsx_dev(chip), "-- command was aborted\n");
		srb->result = DID_ABORT << 16;
		जाओ handle_errors;
	पूर्ण

	/* अगर there is a transport error, reset and करोn't स्वतः-sense */
	अगर (result == TRANSPORT_ERROR) अणु
		dev_dbg(rtsx_dev(chip), "-- transport indicates error, resetting\n");
		srb->result = DID_ERROR << 16;
		जाओ handle_errors;
	पूर्ण

	srb->result = SAM_STAT_GOOD;

	/*
	 * If we have a failure, we're going to करो a REQUEST_SENSE
	 * स्वतःmatically.  Note that we dअगरferentiate between a command
	 * "failure" and an "error" in the transport mechanism.
	 */
	अगर (result == TRANSPORT_FAILED) अणु
		/* set the result so the higher layers expect this data */
		srb->result = SAM_STAT_CHECK_CONDITION;
		स_नकल(srb->sense_buffer,
		       (अचिन्हित अक्षर *)&chip->sense_buffer[SCSI_LUN(srb)],
		       माप(काष्ठा sense_data_t));
	पूर्ण

	वापस;

handle_errors:
	वापस;
पूर्ण

व्योम rtsx_add_cmd(काष्ठा rtsx_chip *chip,
		  u8 cmd_type, u16 reg_addr, u8 mask, u8 data)
अणु
	__le32 *cb = (__le32 *)(chip->host_cmds_ptr);
	u32 val = 0;

	val |= (u32)(cmd_type & 0x03) << 30;
	val |= (u32)(reg_addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	spin_lock_irq(&chip->rtsx->reg_lock);
	अगर (chip->ci < (HOST_CMDS_BUF_LEN / 4))
		cb[(chip->ci)++] = cpu_to_le32(val);

	spin_unlock_irq(&chip->rtsx->reg_lock);
पूर्ण

व्योम rtsx_send_cmd_no_रुको(काष्ठा rtsx_chip *chip)
अणु
	u32 val = BIT(31);

	rtsx_ग_लिखोl(chip, RTSX_HCBAR, chip->host_cmds_addr);

	val |= (u32)(chip->ci * 4) & 0x00FFFFFF;
	/* Hardware Auto Response */
	val |= 0x40000000;
	rtsx_ग_लिखोl(chip, RTSX_HCBCTLR, val);
पूर्ण

पूर्णांक rtsx_send_cmd(काष्ठा rtsx_chip *chip, u8 card, पूर्णांक समयout)
अणु
	काष्ठा rtsx_dev *rtsx = chip->rtsx;
	काष्ठा completion trans_करोne;
	u32 val = BIT(31);
	दीर्घ समयleft;
	पूर्णांक err = 0;

	अगर (card == SD_CARD)
		rtsx->check_card_cd = SD_EXIST;
	अन्यथा अगर (card == MS_CARD)
		rtsx->check_card_cd = MS_EXIST;
	अन्यथा अगर (card == XD_CARD)
		rtsx->check_card_cd = XD_EXIST;
	अन्यथा
		rtsx->check_card_cd = 0;

	spin_lock_irq(&rtsx->reg_lock);

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	rtsx->करोne = &trans_करोne;
	rtsx->trans_result = TRANS_NOT_READY;
	init_completion(&trans_करोne);
	rtsx->trans_state = STATE_TRANS_CMD;

	rtsx_ग_लिखोl(chip, RTSX_HCBAR, chip->host_cmds_addr);

	val |= (u32)(chip->ci * 4) & 0x00FFFFFF;
	/* Hardware Auto Response */
	val |= 0x40000000;
	rtsx_ग_लिखोl(chip, RTSX_HCBCTLR, val);

	spin_unlock_irq(&rtsx->reg_lock);

	/* Wait क्रम TRANS_OK_INT */
	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
							     msecs_to_jअगरfies(समयout));
	अगर (समयleft <= 0) अणु
		dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
			chip->पूर्णांक_reg);
		err = -ETIMEDOUT;
		जाओ finish_send_cmd;
	पूर्ण

	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_RESULT_FAIL)
		err = -EIO;
	अन्यथा अगर (rtsx->trans_result == TRANS_RESULT_OK)
		err = 0;

	spin_unlock_irq(&rtsx->reg_lock);

finish_send_cmd:
	rtsx->करोne = शून्य;
	rtsx->trans_state = STATE_TRANS_NONE;

	अगर (err < 0)
		rtsx_stop_cmd(chip, card);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम rtsx_add_sg_tbl(काष्ठा rtsx_chip *chip,
				   u32 addr, u32 len, u8 option)
अणु
	__le64 *sgb = (__le64 *)(chip->host_sg_tbl_ptr);
	u64 val = 0;
	u32 temp_len = 0;
	u8  temp_opt = 0;

	करो अणु
		अगर (len > 0x80000) अणु
			temp_len = 0x80000;
			temp_opt = option & (~RTSX_SG_END);
		पूर्ण अन्यथा अणु
			temp_len = len;
			temp_opt = option;
		पूर्ण
		val = ((u64)addr << 32) | ((u64)temp_len << 12) | temp_opt;

		अगर (chip->sgi < (HOST_SG_TBL_BUF_LEN / 8))
			sgb[(chip->sgi)++] = cpu_to_le64(val);

		len -= temp_len;
		addr += temp_len;
	पूर्ण जबतक (len);
पूर्ण

अटल पूर्णांक rtsx_transfer_sglist_adma_partial(काष्ठा rtsx_chip *chip, u8 card,
					     काष्ठा scatterlist *sg, पूर्णांक num_sg,
					     अचिन्हित पूर्णांक *index,
					     अचिन्हित पूर्णांक *offset, पूर्णांक size,
					     क्रमागत dma_data_direction dma_dir,
					     पूर्णांक समयout)
अणु
	काष्ठा rtsx_dev *rtsx = chip->rtsx;
	काष्ठा completion trans_करोne;
	u8 dir;
	पूर्णांक sg_cnt, i, resid;
	पूर्णांक err = 0;
	दीर्घ समयleft;
	काष्ठा scatterlist *sg_ptr;
	u32 val = TRIG_DMA;

	अगर (!sg || (num_sg <= 0) || !offset || !index)
		वापस -EIO;

	अगर (dma_dir == DMA_TO_DEVICE)
		dir = HOST_TO_DEVICE;
	अन्यथा अगर (dma_dir == DMA_FROM_DEVICE)
		dir = DEVICE_TO_HOST;
	अन्यथा
		वापस -ENXIO;

	अगर (card == SD_CARD)
		rtsx->check_card_cd = SD_EXIST;
	अन्यथा अगर (card == MS_CARD)
		rtsx->check_card_cd = MS_EXIST;
	अन्यथा अगर (card == XD_CARD)
		rtsx->check_card_cd = XD_EXIST;
	अन्यथा
		rtsx->check_card_cd = 0;

	spin_lock_irq(&rtsx->reg_lock);

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	rtsx->करोne = &trans_करोne;

	rtsx->trans_state = STATE_TRANS_SG;
	rtsx->trans_result = TRANS_NOT_READY;

	spin_unlock_irq(&rtsx->reg_lock);

	sg_cnt = dma_map_sg(&rtsx->pci->dev, sg, num_sg, dma_dir);

	resid = size;
	sg_ptr = sg;
	chip->sgi = 0;
	/*
	 * Usually the next entry will be @sg@ + 1, but अगर this sg element
	 * is part of a chained scatterlist, it could jump to the start of
	 * a new scatterlist array. So here we use sg_next to move to
	 * the proper sg.
	 */
	क्रम (i = 0; i < *index; i++)
		sg_ptr = sg_next(sg_ptr);
	क्रम (i = *index; i < sg_cnt; i++) अणु
		dma_addr_t addr;
		अचिन्हित पूर्णांक len;
		u8 option;

		addr = sg_dma_address(sg_ptr);
		len = sg_dma_len(sg_ptr);

		dev_dbg(rtsx_dev(chip), "DMA addr: 0x%x, Len: 0x%x\n",
			(अचिन्हित पूर्णांक)addr, len);
		dev_dbg(rtsx_dev(chip), "*index = %d, *offset = %d\n",
			*index, *offset);

		addr += *offset;

		अगर ((len - *offset) > resid) अणु
			*offset += resid;
			len = resid;
			resid = 0;
		पूर्ण अन्यथा अणु
			resid -= (len - *offset);
			len -= *offset;
			*offset = 0;
			*index = *index + 1;
		पूर्ण
		option = RTSX_SG_VALID | RTSX_SG_TRANS_DATA;
		अगर ((i == sg_cnt - 1) || !resid)
			option |= RTSX_SG_END;

		rtsx_add_sg_tbl(chip, (u32)addr, (u32)len, option);

		अगर (!resid)
			अवरोध;

		sg_ptr = sg_next(sg_ptr);
	पूर्ण

	dev_dbg(rtsx_dev(chip), "SG table count = %d\n", chip->sgi);

	val |= (u32)(dir & 0x01) << 29;
	val |= ADMA_MODE;

	spin_lock_irq(&rtsx->reg_lock);

	init_completion(&trans_करोne);

	rtsx_ग_लिखोl(chip, RTSX_HDBAR, chip->host_sg_tbl_addr);
	rtsx_ग_लिखोl(chip, RTSX_HDBCTLR, val);

	spin_unlock_irq(&rtsx->reg_lock);

	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
							     msecs_to_jअगरfies(समयout));
	अगर (समयleft <= 0) अणु
		dev_dbg(rtsx_dev(chip), "Timeout (%s %d)\n",
			__func__, __LINE__);
		dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
			chip->पूर्णांक_reg);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_RESULT_FAIL) अणु
		err = -EIO;
		spin_unlock_irq(&rtsx->reg_lock);
		जाओ out;
	पूर्ण
	spin_unlock_irq(&rtsx->reg_lock);

	/* Wait क्रम TRANS_OK_INT */
	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_NOT_READY) अणु
		init_completion(&trans_करोne);
		spin_unlock_irq(&rtsx->reg_lock);
		समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
								     msecs_to_jअगरfies(समयout));
		अगर (समयleft <= 0) अणु
			dev_dbg(rtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __LINE__);
			dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
				chip->पूर्णांक_reg);
			err = -ETIMEDOUT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&rtsx->reg_lock);
	पूर्ण

	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_RESULT_FAIL)
		err = -EIO;
	अन्यथा अगर (rtsx->trans_result == TRANS_RESULT_OK)
		err = 0;

	spin_unlock_irq(&rtsx->reg_lock);

out:
	rtsx->करोne = शून्य;
	rtsx->trans_state = STATE_TRANS_NONE;
	dma_unmap_sg(&rtsx->pci->dev, sg, num_sg, dma_dir);

	अगर (err < 0)
		rtsx_stop_cmd(chip, card);

	वापस err;
पूर्ण

अटल पूर्णांक rtsx_transfer_sglist_adma(काष्ठा rtsx_chip *chip, u8 card,
				     काष्ठा scatterlist *sg, पूर्णांक num_sg,
				     क्रमागत dma_data_direction dma_dir,
				     पूर्णांक समयout)
अणु
	काष्ठा rtsx_dev *rtsx = chip->rtsx;
	काष्ठा completion trans_करोne;
	u8 dir;
	पूर्णांक buf_cnt, i;
	पूर्णांक err = 0;
	दीर्घ समयleft;
	काष्ठा scatterlist *sg_ptr;

	अगर (!sg || (num_sg <= 0))
		वापस -EIO;

	अगर (dma_dir == DMA_TO_DEVICE)
		dir = HOST_TO_DEVICE;
	अन्यथा अगर (dma_dir == DMA_FROM_DEVICE)
		dir = DEVICE_TO_HOST;
	अन्यथा
		वापस -ENXIO;

	अगर (card == SD_CARD)
		rtsx->check_card_cd = SD_EXIST;
	अन्यथा अगर (card == MS_CARD)
		rtsx->check_card_cd = MS_EXIST;
	अन्यथा अगर (card == XD_CARD)
		rtsx->check_card_cd = XD_EXIST;
	अन्यथा
		rtsx->check_card_cd = 0;

	spin_lock_irq(&rtsx->reg_lock);

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	rtsx->करोne = &trans_करोne;

	rtsx->trans_state = STATE_TRANS_SG;
	rtsx->trans_result = TRANS_NOT_READY;

	spin_unlock_irq(&rtsx->reg_lock);

	buf_cnt = dma_map_sg(&rtsx->pci->dev, sg, num_sg, dma_dir);

	sg_ptr = sg;

	क्रम (i = 0; i <= buf_cnt / (HOST_SG_TBL_BUF_LEN / 8); i++) अणु
		u32 val = TRIG_DMA;
		पूर्णांक sg_cnt, j;

		अगर (i == buf_cnt / (HOST_SG_TBL_BUF_LEN / 8))
			sg_cnt = buf_cnt % (HOST_SG_TBL_BUF_LEN / 8);
		अन्यथा
			sg_cnt = HOST_SG_TBL_BUF_LEN / 8;

		chip->sgi = 0;
		क्रम (j = 0; j < sg_cnt; j++) अणु
			dma_addr_t addr = sg_dma_address(sg_ptr);
			अचिन्हित पूर्णांक len = sg_dma_len(sg_ptr);
			u8 option;

			dev_dbg(rtsx_dev(chip), "DMA addr: 0x%x, Len: 0x%x\n",
				(अचिन्हित पूर्णांक)addr, len);

			option = RTSX_SG_VALID | RTSX_SG_TRANS_DATA;
			अगर (j == (sg_cnt - 1))
				option |= RTSX_SG_END;

			rtsx_add_sg_tbl(chip, (u32)addr, (u32)len, option);

			sg_ptr = sg_next(sg_ptr);
		पूर्ण

		dev_dbg(rtsx_dev(chip), "SG table count = %d\n", chip->sgi);

		val |= (u32)(dir & 0x01) << 29;
		val |= ADMA_MODE;

		spin_lock_irq(&rtsx->reg_lock);

		init_completion(&trans_करोne);

		rtsx_ग_लिखोl(chip, RTSX_HDBAR, chip->host_sg_tbl_addr);
		rtsx_ग_लिखोl(chip, RTSX_HDBCTLR, val);

		spin_unlock_irq(&rtsx->reg_lock);

		समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
								     msecs_to_jअगरfies(समयout));
		अगर (समयleft <= 0) अणु
			dev_dbg(rtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __LINE__);
			dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
				chip->पूर्णांक_reg);
			err = -ETIMEDOUT;
			जाओ out;
		पूर्ण

		spin_lock_irq(&rtsx->reg_lock);
		अगर (rtsx->trans_result == TRANS_RESULT_FAIL) अणु
			err = -EIO;
			spin_unlock_irq(&rtsx->reg_lock);
			जाओ out;
		पूर्ण
		spin_unlock_irq(&rtsx->reg_lock);

		sg_ptr += sg_cnt;
	पूर्ण

	/* Wait क्रम TRANS_OK_INT */
	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_NOT_READY) अणु
		init_completion(&trans_करोne);
		spin_unlock_irq(&rtsx->reg_lock);
		समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
								     msecs_to_jअगरfies(समयout));
		अगर (समयleft <= 0) अणु
			dev_dbg(rtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __LINE__);
			dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
				chip->पूर्णांक_reg);
			err = -ETIMEDOUT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&rtsx->reg_lock);
	पूर्ण

	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_RESULT_FAIL)
		err = -EIO;
	अन्यथा अगर (rtsx->trans_result == TRANS_RESULT_OK)
		err = 0;

	spin_unlock_irq(&rtsx->reg_lock);

out:
	rtsx->करोne = शून्य;
	rtsx->trans_state = STATE_TRANS_NONE;
	dma_unmap_sg(&rtsx->pci->dev, sg, num_sg, dma_dir);

	अगर (err < 0)
		rtsx_stop_cmd(chip, card);

	वापस err;
पूर्ण

अटल पूर्णांक rtsx_transfer_buf(काष्ठा rtsx_chip *chip, u8 card, व्योम *buf,
			     माप_प्रकार len, क्रमागत dma_data_direction dma_dir,
			     पूर्णांक समयout)
अणु
	काष्ठा rtsx_dev *rtsx = chip->rtsx;
	काष्ठा completion trans_करोne;
	dma_addr_t addr;
	u8 dir;
	पूर्णांक err = 0;
	u32 val = BIT(31);
	दीर्घ समयleft;

	अगर (!buf || (len <= 0))
		वापस -EIO;

	अगर (dma_dir == DMA_TO_DEVICE)
		dir = HOST_TO_DEVICE;
	अन्यथा अगर (dma_dir == DMA_FROM_DEVICE)
		dir = DEVICE_TO_HOST;
	अन्यथा
		वापस -ENXIO;

	addr = dma_map_single(&rtsx->pci->dev, buf, len, dma_dir);
	अगर (dma_mapping_error(&rtsx->pci->dev, addr))
		वापस -ENOMEM;

	अगर (card == SD_CARD)
		rtsx->check_card_cd = SD_EXIST;
	अन्यथा अगर (card == MS_CARD)
		rtsx->check_card_cd = MS_EXIST;
	अन्यथा अगर (card == XD_CARD)
		rtsx->check_card_cd = XD_EXIST;
	अन्यथा
		rtsx->check_card_cd = 0;

	val |= (u32)(dir & 0x01) << 29;
	val |= (u32)(len & 0x00FFFFFF);

	spin_lock_irq(&rtsx->reg_lock);

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	rtsx->करोne = &trans_करोne;

	init_completion(&trans_करोne);

	rtsx->trans_state = STATE_TRANS_BUF;
	rtsx->trans_result = TRANS_NOT_READY;

	rtsx_ग_लिखोl(chip, RTSX_HDBAR, addr);
	rtsx_ग_लिखोl(chip, RTSX_HDBCTLR, val);

	spin_unlock_irq(&rtsx->reg_lock);

	/* Wait क्रम TRANS_OK_INT */
	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&trans_करोne,
							     msecs_to_jअगरfies(समयout));
	अगर (समयleft <= 0) अणु
		dev_dbg(rtsx_dev(chip), "Timeout (%s %d)\n",
			__func__, __LINE__);
		dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
			chip->पूर्णांक_reg);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	spin_lock_irq(&rtsx->reg_lock);
	अगर (rtsx->trans_result == TRANS_RESULT_FAIL)
		err = -EIO;
	अन्यथा अगर (rtsx->trans_result == TRANS_RESULT_OK)
		err = 0;

	spin_unlock_irq(&rtsx->reg_lock);

out:
	rtsx->करोne = शून्य;
	rtsx->trans_state = STATE_TRANS_NONE;
	dma_unmap_single(&rtsx->pci->dev, addr, len, dma_dir);

	अगर (err < 0)
		rtsx_stop_cmd(chip, card);

	वापस err;
पूर्ण

पूर्णांक rtsx_transfer_data_partial(काष्ठा rtsx_chip *chip, u8 card,
			       व्योम *buf, माप_प्रकार len, पूर्णांक use_sg,
			       अचिन्हित पूर्णांक *index, अचिन्हित पूर्णांक *offset,
			       क्रमागत dma_data_direction dma_dir, पूर्णांक समयout)
अणु
	पूर्णांक err = 0;

	/* करोn't transfer data during पात processing */
	अगर (rtsx_chk_stat(chip, RTSX_STAT_ABORT))
		वापस -EIO;

	अगर (use_sg) अणु
		काष्ठा scatterlist *sg = buf;

		err = rtsx_transfer_sglist_adma_partial(chip, card, sg, use_sg,
							index, offset, (पूर्णांक)len,
							dma_dir, समयout);
	पूर्ण अन्यथा अणु
		err = rtsx_transfer_buf(chip, card,
					buf, len, dma_dir, समयout);
	पूर्ण
	अगर (err < 0) अणु
		अगर (RTSX_TST_DELINK(chip)) अणु
			RTSX_CLR_DELINK(chip);
			chip->need_reinit = SD_CARD | MS_CARD | XD_CARD;
			rtsx_reinit_cards(chip, 1);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक rtsx_transfer_data(काष्ठा rtsx_chip *chip, u8 card, व्योम *buf, माप_प्रकार len,
		       पूर्णांक use_sg, क्रमागत dma_data_direction dma_dir, पूर्णांक समयout)
अणु
	पूर्णांक err = 0;

	dev_dbg(rtsx_dev(chip), "use_sg = %d\n", use_sg);

	/* करोn't transfer data during पात processing */
	अगर (rtsx_chk_stat(chip, RTSX_STAT_ABORT))
		वापस -EIO;

	अगर (use_sg) अणु
		err = rtsx_transfer_sglist_adma(chip, card, buf,
						use_sg, dma_dir, समयout);
	पूर्ण अन्यथा अणु
		err = rtsx_transfer_buf(chip, card, buf, len, dma_dir, समयout);
	पूर्ण

	अगर (err < 0) अणु
		अगर (RTSX_TST_DELINK(chip)) अणु
			RTSX_CLR_DELINK(chip);
			chip->need_reinit = SD_CARD | MS_CARD | XD_CARD;
			rtsx_reinit_cards(chip, 1);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

