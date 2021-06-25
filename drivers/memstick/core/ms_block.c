<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ms_block.c - Sony MemoryStick (legacy) storage support

 *  Copyright (C) 2013 Maxim Levitsky <maximlevitsky@gmail.com>
 *
 * Minor portions of the driver were copied from mspro_block.c which is
 * Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 */
#घोषणा DRIVER_NAME "ms_block"
#घोषणा pr_fmt(fmt) DRIVER_NAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/memstick.h>
#समावेश <linux/idr.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश "ms_block.h"

अटल पूर्णांक debug;
अटल पूर्णांक cache_flush_समयout = 1000;
अटल bool verअगरy_ग_लिखोs;

/*
 * Copies section of 'sg_from' starting from offset 'offset' and with length
 * 'len' To another scatterlist of to_nents enties
 */
अटल माप_प्रकार msb_sg_copy(काष्ठा scatterlist *sg_from,
	काष्ठा scatterlist *sg_to, पूर्णांक to_nents, माप_प्रकार offset, माप_प्रकार len)
अणु
	माप_प्रकार copied = 0;

	जबतक (offset > 0) अणु
		अगर (offset >= sg_from->length) अणु
			अगर (sg_is_last(sg_from))
				वापस 0;

			offset -= sg_from->length;
			sg_from = sg_next(sg_from);
			जारी;
		पूर्ण

		copied = min(len, sg_from->length - offset);
		sg_set_page(sg_to, sg_page(sg_from),
			copied, sg_from->offset + offset);

		len -= copied;
		offset = 0;

		अगर (sg_is_last(sg_from) || !len)
			जाओ out;

		sg_to = sg_next(sg_to);
		to_nents--;
		sg_from = sg_next(sg_from);
	पूर्ण

	जबतक (len > sg_from->length && to_nents--) अणु
		len -= sg_from->length;
		copied += sg_from->length;

		sg_set_page(sg_to, sg_page(sg_from),
				sg_from->length, sg_from->offset);

		अगर (sg_is_last(sg_from) || !len)
			जाओ out;

		sg_from = sg_next(sg_from);
		sg_to = sg_next(sg_to);
	पूर्ण

	अगर (len && to_nents) अणु
		sg_set_page(sg_to, sg_page(sg_from), len, sg_from->offset);
		copied += len;
	पूर्ण
out:
	sg_mark_end(sg_to);
	वापस copied;
पूर्ण

/*
 * Compares section of 'sg' starting from offset 'offset' and with length 'len'
 * to linear buffer of length 'len' at address 'buffer'
 * Returns 0 अगर equal and  -1 otherwice
 */
अटल पूर्णांक msb_sg_compare_to_buffer(काष्ठा scatterlist *sg,
					माप_प्रकार offset, u8 *buffer, माप_प्रकार len)
अणु
	पूर्णांक retval = 0, cmplen;
	काष्ठा sg_mapping_iter miter;

	sg_miter_start(&miter, sg, sg_nents(sg),
					SG_MITER_ATOMIC | SG_MITER_FROM_SG);

	जबतक (sg_miter_next(&miter) && len > 0) अणु
		अगर (offset >= miter.length) अणु
			offset -= miter.length;
			जारी;
		पूर्ण

		cmplen = min(miter.length - offset, len);
		retval = स_भेद(miter.addr + offset, buffer, cmplen) ? -1 : 0;
		अगर (retval)
			अवरोध;

		buffer += cmplen;
		len -= cmplen;
		offset = 0;
	पूर्ण

	अगर (!retval && len)
		retval = -1;

	sg_miter_stop(&miter);
	वापस retval;
पूर्ण


/* Get zone at which block with logical address 'lba' lives
 * Flash is broken पूर्णांकo zones.
 * Each zone consists of 512 eraseblocks, out of which in first
 * zone 494 are used and 496 are क्रम all following zones.
 * Thereक्रमe zone #0 hosts blocks 0-493, zone #1 blocks 494-988, etc...
*/
अटल पूर्णांक msb_get_zone_from_lba(पूर्णांक lba)
अणु
	अगर (lba < 494)
		वापस 0;
	वापस ((lba - 494) / 496) + 1;
पूर्ण

/* Get zone of physical block. Trivial */
अटल पूर्णांक msb_get_zone_from_pba(पूर्णांक pba)
अणु
	वापस pba / MS_BLOCKS_IN_ZONE;
पूर्ण

/* Debug test to validate मुक्त block counts */
अटल पूर्णांक msb_validate_used_block_biपंचांगap(काष्ठा msb_data *msb)
अणु
	पूर्णांक total_मुक्त_blocks = 0;
	पूर्णांक i;

	अगर (!debug)
		वापस 0;

	क्रम (i = 0; i < msb->zone_count; i++)
		total_मुक्त_blocks += msb->मुक्त_block_count[i];

	अगर (msb->block_count - biपंचांगap_weight(msb->used_blocks_biपंचांगap,
					msb->block_count) == total_मुक्त_blocks)
		वापस 0;

	pr_err("BUG: free block counts don't match the bitmap");
	msb->पढ़ो_only = true;
	वापस -EINVAL;
पूर्ण

/* Mark physical block as used */
अटल व्योम msb_mark_block_used(काष्ठा msb_data *msb, पूर्णांक pba)
अणु
	पूर्णांक zone = msb_get_zone_from_pba(pba);

	अगर (test_bit(pba, msb->used_blocks_biपंचांगap)) अणु
		pr_err(
		"BUG: attempt to mark already used pba %d as used", pba);
		msb->पढ़ो_only = true;
		वापस;
	पूर्ण

	अगर (msb_validate_used_block_biपंचांगap(msb))
		वापस;

	/* No races because all IO is single thपढ़ोed */
	__set_bit(pba, msb->used_blocks_biपंचांगap);
	msb->मुक्त_block_count[zone]--;
पूर्ण

/* Mark physical block as मुक्त */
अटल व्योम msb_mark_block_unused(काष्ठा msb_data *msb, पूर्णांक pba)
अणु
	पूर्णांक zone = msb_get_zone_from_pba(pba);

	अगर (!test_bit(pba, msb->used_blocks_biपंचांगap)) अणु
		pr_err("BUG: attempt to mark already unused pba %d as unused" , pba);
		msb->पढ़ो_only = true;
		वापस;
	पूर्ण

	अगर (msb_validate_used_block_biपंचांगap(msb))
		वापस;

	/* No races because all IO is single thपढ़ोed */
	__clear_bit(pba, msb->used_blocks_biपंचांगap);
	msb->मुक्त_block_count[zone]++;
पूर्ण

/* Invalidate current रेजिस्टर winकरोw */
अटल व्योम msb_invalidate_reg_winकरोw(काष्ठा msb_data *msb)
अणु
	msb->reg_addr.w_offset = दुरत्व(काष्ठा ms_रेजिस्टर, id);
	msb->reg_addr.w_length = माप(काष्ठा ms_id_रेजिस्टर);
	msb->reg_addr.r_offset = दुरत्व(काष्ठा ms_रेजिस्टर, id);
	msb->reg_addr.r_length = माप(काष्ठा ms_id_रेजिस्टर);
	msb->addr_valid = false;
पूर्ण

/* Start a state machine */
अटल पूर्णांक msb_run_state_machine(काष्ठा msb_data *msb, पूर्णांक   (*state_func)
		(काष्ठा memstick_dev *card, काष्ठा memstick_request **req))
अणु
	काष्ठा memstick_dev *card = msb->card;

	WARN_ON(msb->state != -1);
	msb->पूर्णांक_polling = false;
	msb->state = 0;
	msb->निकास_error = 0;

	स_रखो(&card->current_mrq, 0, माप(card->current_mrq));

	card->next_request = state_func;
	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);

	WARN_ON(msb->state != -1);
	वापस msb->निकास_error;
पूर्ण

/* State machines call that to निकास */
अटल पूर्णांक msb_निकास_state_machine(काष्ठा msb_data *msb, पूर्णांक error)
अणु
	WARN_ON(msb->state == -1);

	msb->state = -1;
	msb->निकास_error = error;
	msb->card->next_request = h_msb_शेष_bad;

	/* Invalidate reg winकरोw on errors */
	अगर (error)
		msb_invalidate_reg_winकरोw(msb);

	complete(&msb->card->mrq_complete);
	वापस -ENXIO;
पूर्ण

/* पढ़ो INT रेजिस्टर */
अटल पूर्णांक msb_पढ़ो_पूर्णांक_reg(काष्ठा msb_data *msb, दीर्घ समयout)
अणु
	काष्ठा memstick_request *mrq = &msb->card->current_mrq;

	WARN_ON(msb->state == -1);

	अगर (!msb->पूर्णांक_polling) अणु
		msb->पूर्णांक_समयout = jअगरfies +
			msecs_to_jअगरfies(समयout == -1 ? 500 : समयout);
		msb->पूर्णांक_polling = true;
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, msb->पूर्णांक_समयout)) अणु
		mrq->data[0] = MEMSTICK_INT_CMDNAK;
		वापस 0;
	पूर्ण

	अगर ((msb->caps & MEMSTICK_CAP_AUTO_GET_INT) &&
				mrq->need_card_पूर्णांक && !mrq->error) अणु
		mrq->data[0] = mrq->पूर्णांक_reg;
		mrq->need_card_पूर्णांक = false;
		वापस 0;
	पूर्ण अन्यथा अणु
		memstick_init_req(mrq, MS_TPC_GET_INT, शून्य, 1);
		वापस 1;
	पूर्ण
पूर्ण

/* Read a रेजिस्टर */
अटल पूर्णांक msb_पढ़ो_regs(काष्ठा msb_data *msb, पूर्णांक offset, पूर्णांक len)
अणु
	काष्ठा memstick_request *req = &msb->card->current_mrq;

	अगर (msb->reg_addr.r_offset != offset ||
	    msb->reg_addr.r_length != len || !msb->addr_valid) अणु

		msb->reg_addr.r_offset = offset;
		msb->reg_addr.r_length = len;
		msb->addr_valid = true;

		memstick_init_req(req, MS_TPC_SET_RW_REG_ADRS,
			&msb->reg_addr, माप(msb->reg_addr));
		वापस 0;
	पूर्ण

	memstick_init_req(req, MS_TPC_READ_REG, शून्य, len);
	वापस 1;
पूर्ण

/* Write a card रेजिस्टर */
अटल पूर्णांक msb_ग_लिखो_regs(काष्ठा msb_data *msb, पूर्णांक offset, पूर्णांक len, व्योम *buf)
अणु
	काष्ठा memstick_request *req = &msb->card->current_mrq;

	अगर (msb->reg_addr.w_offset != offset ||
		msb->reg_addr.w_length != len  || !msb->addr_valid) अणु

		msb->reg_addr.w_offset = offset;
		msb->reg_addr.w_length = len;
		msb->addr_valid = true;

		memstick_init_req(req, MS_TPC_SET_RW_REG_ADRS,
			&msb->reg_addr, माप(msb->reg_addr));
		वापस 0;
	पूर्ण

	memstick_init_req(req, MS_TPC_WRITE_REG, buf, len);
	वापस 1;
पूर्ण

/* Handler क्रम असलence of IO */
अटल पूर्णांक h_msb_शेष_bad(काष्ठा memstick_dev *card,
						काष्ठा memstick_request **mrq)
अणु
	वापस -ENXIO;
पूर्ण

/*
 * This function is a handler क्रम पढ़ोs of one page from device.
 * Writes output to msb->current_sg, takes sector address from msb->reg.param
 * Can also be used to पढ़ो extra data only. Set params accordपूर्णांकly.
 */
अटल पूर्णांक h_msb_पढ़ो_page(काष्ठा memstick_dev *card,
					काष्ठा memstick_request **out_mrq)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_request *mrq = *out_mrq = &card->current_mrq;
	काष्ठा scatterlist sg[2];
	u8 command, पूर्णांकreg;

	अगर (mrq->error) अणु
		dbg("read_page, unknown error");
		वापस msb_निकास_state_machine(msb, mrq->error);
	पूर्ण
again:
	चयन (msb->state) अणु
	हाल MSB_RP_SEND_BLOCK_ADDRESS:
		/* msb_ग_लिखो_regs someबार "fails" because it needs to update
			the reg winकरोw, and thus it वापसs request क्रम that.
			Then we stay in this state and retry */
		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, param),
			माप(काष्ठा ms_param_रेजिस्टर),
			(अचिन्हित अक्षर *)&msb->regs.param))
			वापस 0;

		msb->state = MSB_RP_SEND_READ_COMMAND;
		वापस 0;

	हाल MSB_RP_SEND_READ_COMMAND:
		command = MS_CMD_BLOCK_READ;
		memstick_init_req(mrq, MS_TPC_SET_CMD, &command, 1);
		msb->state = MSB_RP_SEND_INT_REQ;
		वापस 0;

	हाल MSB_RP_SEND_INT_REQ:
		msb->state = MSB_RP_RECEIVE_INT_REQ_RESULT;
		/* If करोnt actually need to send the पूर्णांक पढ़ो request (only in
			serial mode), then just fall through */
		अगर (msb_पढ़ो_पूर्णांक_reg(msb, -1))
			वापस 0;
		fallthrough;

	हाल MSB_RP_RECEIVE_INT_REQ_RESULT:
		पूर्णांकreg = mrq->data[0];
		msb->regs.status.पूर्णांकerrupt = पूर्णांकreg;

		अगर (पूर्णांकreg & MEMSTICK_INT_CMDNAK)
			वापस msb_निकास_state_machine(msb, -EIO);

		अगर (!(पूर्णांकreg & MEMSTICK_INT_CED)) अणु
			msb->state = MSB_RP_SEND_INT_REQ;
			जाओ again;
		पूर्ण

		msb->पूर्णांक_polling = false;
		msb->state = (पूर्णांकreg & MEMSTICK_INT_ERR) ?
			MSB_RP_SEND_READ_STATUS_REG : MSB_RP_SEND_OOB_READ;
		जाओ again;

	हाल MSB_RP_SEND_READ_STATUS_REG:
		 /* पढ़ो the status रेजिस्टर to understand source of the INT_ERR */
		अगर (!msb_पढ़ो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, status),
			माप(काष्ठा ms_status_रेजिस्टर)))
			वापस 0;

		msb->state = MSB_RP_RECEIVE_STATUS_REG;
		वापस 0;

	हाल MSB_RP_RECEIVE_STATUS_REG:
		msb->regs.status = *(काष्ठा ms_status_रेजिस्टर *)mrq->data;
		msb->state = MSB_RP_SEND_OOB_READ;
		fallthrough;

	हाल MSB_RP_SEND_OOB_READ:
		अगर (!msb_पढ़ो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, extra_data),
			माप(काष्ठा ms_extra_data_रेजिस्टर)))
			वापस 0;

		msb->state = MSB_RP_RECEIVE_OOB_READ;
		वापस 0;

	हाल MSB_RP_RECEIVE_OOB_READ:
		msb->regs.extra_data =
			*(काष्ठा ms_extra_data_रेजिस्टर *) mrq->data;
		msb->state = MSB_RP_SEND_READ_DATA;
		fallthrough;

	हाल MSB_RP_SEND_READ_DATA:
		/* Skip that state अगर we only पढ़ो the oob */
		अगर (msb->regs.param.cp == MEMSTICK_CP_EXTRA) अणु
			msb->state = MSB_RP_RECEIVE_READ_DATA;
			जाओ again;
		पूर्ण

		sg_init_table(sg, ARRAY_SIZE(sg));
		msb_sg_copy(msb->current_sg, sg, ARRAY_SIZE(sg),
			msb->current_sg_offset,
			msb->page_size);

		memstick_init_req_sg(mrq, MS_TPC_READ_LONG_DATA, sg);
		msb->state = MSB_RP_RECEIVE_READ_DATA;
		वापस 0;

	हाल MSB_RP_RECEIVE_READ_DATA:
		अगर (!(msb->regs.status.पूर्णांकerrupt & MEMSTICK_INT_ERR)) अणु
			msb->current_sg_offset += msb->page_size;
			वापस msb_निकास_state_machine(msb, 0);
		पूर्ण

		अगर (msb->regs.status.status1 & MEMSTICK_UNCORR_ERROR) अणु
			dbg("read_page: uncorrectable error");
			वापस msb_निकास_state_machine(msb, -EBADMSG);
		पूर्ण

		अगर (msb->regs.status.status1 & MEMSTICK_CORR_ERROR) अणु
			dbg("read_page: correctable error");
			msb->current_sg_offset += msb->page_size;
			वापस msb_निकास_state_machine(msb, -EUCLEAN);
		पूर्ण अन्यथा अणु
			dbg("read_page: INT error, but no status error bits");
			वापस msb_निकास_state_machine(msb, -EIO);
		पूर्ण
	पूर्ण

	BUG();
पूर्ण

/*
 * Handler of ग_लिखोs of exactly one block.
 * Takes address from msb->regs.param.
 * Writes same extra data to blocks, also taken
 * from msb->regs.extra
 * Returns -EBADMSG अगर ग_लिखो fails due to uncorrectable error, or -EIO अगर
 * device refuses to take the command or something अन्यथा
 */
अटल पूर्णांक h_msb_ग_लिखो_block(काष्ठा memstick_dev *card,
					काष्ठा memstick_request **out_mrq)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_request *mrq = *out_mrq = &card->current_mrq;
	काष्ठा scatterlist sg[2];
	u8 पूर्णांकreg, command;

	अगर (mrq->error)
		वापस msb_निकास_state_machine(msb, mrq->error);

again:
	चयन (msb->state) अणु

	/* HACK: Jmicon handling of TPCs between 8 and
	 *	माप(memstick_request.data) is broken due to hardware
	 *	bug in PIO mode that is used क्रम these TPCs
	 *	Thereक्रमe split the ग_लिखो
	 */

	हाल MSB_WB_SEND_WRITE_PARAMS:
		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, param),
			माप(काष्ठा ms_param_रेजिस्टर),
			&msb->regs.param))
			वापस 0;

		msb->state = MSB_WB_SEND_WRITE_OOB;
		वापस 0;

	हाल MSB_WB_SEND_WRITE_OOB:
		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, extra_data),
			माप(काष्ठा ms_extra_data_रेजिस्टर),
			&msb->regs.extra_data))
			वापस 0;
		msb->state = MSB_WB_SEND_WRITE_COMMAND;
		वापस 0;


	हाल MSB_WB_SEND_WRITE_COMMAND:
		command = MS_CMD_BLOCK_WRITE;
		memstick_init_req(mrq, MS_TPC_SET_CMD, &command, 1);
		msb->state = MSB_WB_SEND_INT_REQ;
		वापस 0;

	हाल MSB_WB_SEND_INT_REQ:
		msb->state = MSB_WB_RECEIVE_INT_REQ;
		अगर (msb_पढ़ो_पूर्णांक_reg(msb, -1))
			वापस 0;
		fallthrough;

	हाल MSB_WB_RECEIVE_INT_REQ:
		पूर्णांकreg = mrq->data[0];
		msb->regs.status.पूर्णांकerrupt = पूर्णांकreg;

		/* errors mean out of here, and fast... */
		अगर (पूर्णांकreg & (MEMSTICK_INT_CMDNAK))
			वापस msb_निकास_state_machine(msb, -EIO);

		अगर (पूर्णांकreg & MEMSTICK_INT_ERR)
			वापस msb_निकास_state_machine(msb, -EBADMSG);


		/* क्रम last page we need to poll CED */
		अगर (msb->current_page == msb->pages_in_block) अणु
			अगर (पूर्णांकreg & MEMSTICK_INT_CED)
				वापस msb_निकास_state_machine(msb, 0);
			msb->state = MSB_WB_SEND_INT_REQ;
			जाओ again;

		पूर्ण

		/* क्रम non-last page we need BREQ beक्रमe writing next chunk */
		अगर (!(पूर्णांकreg & MEMSTICK_INT_BREQ)) अणु
			msb->state = MSB_WB_SEND_INT_REQ;
			जाओ again;
		पूर्ण

		msb->पूर्णांक_polling = false;
		msb->state = MSB_WB_SEND_WRITE_DATA;
		fallthrough;

	हाल MSB_WB_SEND_WRITE_DATA:
		sg_init_table(sg, ARRAY_SIZE(sg));

		अगर (msb_sg_copy(msb->current_sg, sg, ARRAY_SIZE(sg),
			msb->current_sg_offset,
			msb->page_size) < msb->page_size)
			वापस msb_निकास_state_machine(msb, -EIO);

		memstick_init_req_sg(mrq, MS_TPC_WRITE_LONG_DATA, sg);
		mrq->need_card_पूर्णांक = 1;
		msb->state = MSB_WB_RECEIVE_WRITE_CONFIRMATION;
		वापस 0;

	हाल MSB_WB_RECEIVE_WRITE_CONFIRMATION:
		msb->current_page++;
		msb->current_sg_offset += msb->page_size;
		msb->state = MSB_WB_SEND_INT_REQ;
		जाओ again;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is used to send simple IO requests to device that consist
 * of रेजिस्टर ग_लिखो + command
 */
अटल पूर्णांक h_msb_send_command(काष्ठा memstick_dev *card,
					काष्ठा memstick_request **out_mrq)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_request *mrq = *out_mrq = &card->current_mrq;
	u8 पूर्णांकreg;

	अगर (mrq->error) अणु
		dbg("send_command: unknown error");
		वापस msb_निकास_state_machine(msb, mrq->error);
	पूर्ण
again:
	चयन (msb->state) अणु

	/* HACK: see h_msb_ग_लिखो_block */
	हाल MSB_SC_SEND_WRITE_PARAMS: /* ग_लिखो param रेजिस्टर*/
		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, param),
			माप(काष्ठा ms_param_रेजिस्टर),
			&msb->regs.param))
			वापस 0;
		msb->state = MSB_SC_SEND_WRITE_OOB;
		वापस 0;

	हाल MSB_SC_SEND_WRITE_OOB:
		अगर (!msb->command_need_oob) अणु
			msb->state = MSB_SC_SEND_COMMAND;
			जाओ again;
		पूर्ण

		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, extra_data),
			माप(काष्ठा ms_extra_data_रेजिस्टर),
			&msb->regs.extra_data))
			वापस 0;

		msb->state = MSB_SC_SEND_COMMAND;
		वापस 0;

	हाल MSB_SC_SEND_COMMAND:
		memstick_init_req(mrq, MS_TPC_SET_CMD, &msb->command_value, 1);
		msb->state = MSB_SC_SEND_INT_REQ;
		वापस 0;

	हाल MSB_SC_SEND_INT_REQ:
		msb->state = MSB_SC_RECEIVE_INT_REQ;
		अगर (msb_पढ़ो_पूर्णांक_reg(msb, -1))
			वापस 0;
		fallthrough;

	हाल MSB_SC_RECEIVE_INT_REQ:
		पूर्णांकreg = mrq->data[0];

		अगर (पूर्णांकreg & MEMSTICK_INT_CMDNAK)
			वापस msb_निकास_state_machine(msb, -EIO);
		अगर (पूर्णांकreg & MEMSTICK_INT_ERR)
			वापस msb_निकास_state_machine(msb, -EBADMSG);

		अगर (!(पूर्णांकreg & MEMSTICK_INT_CED)) अणु
			msb->state = MSB_SC_SEND_INT_REQ;
			जाओ again;
		पूर्ण

		वापस msb_निकास_state_machine(msb, 0);
	पूर्ण

	BUG();
पूर्ण

/* Small handler क्रम card reset */
अटल पूर्णांक h_msb_reset(काष्ठा memstick_dev *card,
					काष्ठा memstick_request **out_mrq)
अणु
	u8 command = MS_CMD_RESET;
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_request *mrq = *out_mrq = &card->current_mrq;

	अगर (mrq->error)
		वापस msb_निकास_state_machine(msb, mrq->error);

	चयन (msb->state) अणु
	हाल MSB_RS_SEND:
		memstick_init_req(mrq, MS_TPC_SET_CMD, &command, 1);
		mrq->need_card_पूर्णांक = 0;
		msb->state = MSB_RS_CONFIRM;
		वापस 0;
	हाल MSB_RS_CONFIRM:
		वापस msb_निकास_state_machine(msb, 0);
	पूर्ण
	BUG();
पूर्ण

/* This handler is used to करो serial->parallel चयन */
अटल पूर्णांक h_msb_parallel_चयन(काष्ठा memstick_dev *card,
					काष्ठा memstick_request **out_mrq)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_request *mrq = *out_mrq = &card->current_mrq;
	काष्ठा memstick_host *host = card->host;

	अगर (mrq->error) अणु
		dbg("parallel_switch: error");
		msb->regs.param.प्रणाली &= ~MEMSTICK_SYS_PAM;
		वापस msb_निकास_state_machine(msb, mrq->error);
	पूर्ण

	चयन (msb->state) अणु
	हाल MSB_PS_SEND_SWITCH_COMMAND:
		/* Set the parallel पूर्णांकerface on memstick side */
		msb->regs.param.प्रणाली |= MEMSTICK_SYS_PAM;

		अगर (!msb_ग_लिखो_regs(msb,
			दुरत्व(काष्ठा ms_रेजिस्टर, param),
			1,
			(अचिन्हित अक्षर *)&msb->regs.param))
			वापस 0;

		msb->state = MSB_PS_SWICH_HOST;
		वापस 0;

	हाल MSB_PS_SWICH_HOST:
		 /* Set parallel पूर्णांकerface on our side + send a dummy request
			to see अगर card responds */
		host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_PAR4);
		memstick_init_req(mrq, MS_TPC_GET_INT, शून्य, 1);
		msb->state = MSB_PS_CONFIRM;
		वापस 0;

	हाल MSB_PS_CONFIRM:
		वापस msb_निकास_state_machine(msb, 0);
	पूर्ण

	BUG();
पूर्ण

अटल पूर्णांक msb_चयन_to_parallel(काष्ठा msb_data *msb);

/* Reset the card, to guard against hw errors beeing treated as bad blocks */
अटल पूर्णांक msb_reset(काष्ठा msb_data *msb, bool full)
अणु

	bool was_parallel = msb->regs.param.प्रणाली & MEMSTICK_SYS_PAM;
	काष्ठा memstick_dev *card = msb->card;
	काष्ठा memstick_host *host = card->host;
	पूर्णांक error;

	/* Reset the card */
	msb->regs.param.प्रणाली = MEMSTICK_SYS_BAMD;

	अगर (full) अणु
		error =  host->set_param(host,
					MEMSTICK_POWER, MEMSTICK_POWER_OFF);
		अगर (error)
			जाओ out_error;

		msb_invalidate_reg_winकरोw(msb);

		error = host->set_param(host,
					MEMSTICK_POWER, MEMSTICK_POWER_ON);
		अगर (error)
			जाओ out_error;

		error = host->set_param(host,
					MEMSTICK_INTERFACE, MEMSTICK_SERIAL);
		अगर (error) अणु
out_error:
			dbg("Failed to reset the host controller");
			msb->पढ़ो_only = true;
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	error = msb_run_state_machine(msb, h_msb_reset);
	अगर (error) अणु
		dbg("Failed to reset the card");
		msb->पढ़ो_only = true;
		वापस -ENODEV;
	पूर्ण

	/* Set parallel mode */
	अगर (was_parallel)
		msb_चयन_to_parallel(msb);
	वापस 0;
पूर्ण

/* Attempts to चयन पूर्णांकerface to parallel mode */
अटल पूर्णांक msb_चयन_to_parallel(काष्ठा msb_data *msb)
अणु
	पूर्णांक error;

	error = msb_run_state_machine(msb, h_msb_parallel_चयन);
	अगर (error) अणु
		pr_err("Switch to parallel failed");
		msb->regs.param.प्रणाली &= ~MEMSTICK_SYS_PAM;
		msb_reset(msb, true);
		वापस -EFAULT;
	पूर्ण

	msb->caps |= MEMSTICK_CAP_AUTO_GET_INT;
	वापस 0;
पूर्ण

/* Changes overग_लिखो flag on a page */
अटल पूर्णांक msb_set_overग_लिखो_flag(काष्ठा msb_data *msb,
						u16 pba, u8 page, u8 flag)
अणु
	अगर (msb->पढ़ो_only)
		वापस -EROFS;

	msb->regs.param.block_address = cpu_to_be16(pba);
	msb->regs.param.page_address = page;
	msb->regs.param.cp = MEMSTICK_CP_OVERWRITE;
	msb->regs.extra_data.overग_लिखो_flag = flag;
	msb->command_value = MS_CMD_BLOCK_WRITE;
	msb->command_need_oob = true;

	dbg_verbose("changing overwrite flag to %02x for sector %d, page %d",
							flag, pba, page);
	वापस msb_run_state_machine(msb, h_msb_send_command);
पूर्ण

अटल पूर्णांक msb_mark_bad(काष्ठा msb_data *msb, पूर्णांक pba)
अणु
	pr_notice("marking pba %d as bad", pba);
	msb_reset(msb, true);
	वापस msb_set_overग_लिखो_flag(
			msb, pba, 0, 0xFF & ~MEMSTICK_OVERWRITE_BKST);
पूर्ण

अटल पूर्णांक msb_mark_page_bad(काष्ठा msb_data *msb, पूर्णांक pba, पूर्णांक page)
अणु
	dbg("marking page %d of pba %d as bad", page, pba);
	msb_reset(msb, true);
	वापस msb_set_overग_लिखो_flag(msb,
		pba, page, ~MEMSTICK_OVERWRITE_PGST0);
पूर्ण

/* Erases one physical block */
अटल पूर्णांक msb_erase_block(काष्ठा msb_data *msb, u16 pba)
अणु
	पूर्णांक error, try;
	अगर (msb->पढ़ो_only)
		वापस -EROFS;

	dbg_verbose("erasing pba %d", pba);

	क्रम (try = 1; try < 3; try++) अणु
		msb->regs.param.block_address = cpu_to_be16(pba);
		msb->regs.param.page_address = 0;
		msb->regs.param.cp = MEMSTICK_CP_BLOCK;
		msb->command_value = MS_CMD_BLOCK_ERASE;
		msb->command_need_oob = false;


		error = msb_run_state_machine(msb, h_msb_send_command);
		अगर (!error || msb_reset(msb, true))
			अवरोध;
	पूर्ण

	अगर (error) अणु
		pr_err("erase failed, marking pba %d as bad", pba);
		msb_mark_bad(msb, pba);
	पूर्ण

	dbg_verbose("erase success, marking pba %d as unused", pba);
	msb_mark_block_unused(msb, pba);
	__set_bit(pba, msb->erased_blocks_biपंचांगap);
	वापस error;
पूर्ण

/* Reads one page from device */
अटल पूर्णांक msb_पढ़ो_page(काष्ठा msb_data *msb,
	u16 pba, u8 page, काष्ठा ms_extra_data_रेजिस्टर *extra,
					काष्ठा scatterlist *sg,  पूर्णांक offset)
अणु
	पूर्णांक try, error;

	अगर (pba == MS_BLOCK_INVALID) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा sg_mapping_iter miter;
		माप_प्रकार len = msb->page_size;

		dbg_verbose("read unmapped sector. returning 0xFF");

		local_irq_save(flags);
		sg_miter_start(&miter, sg, sg_nents(sg),
				SG_MITER_ATOMIC | SG_MITER_TO_SG);

		जबतक (sg_miter_next(&miter) && len > 0) अणु

			पूर्णांक chunklen;

			अगर (offset && offset >= miter.length) अणु
				offset -= miter.length;
				जारी;
			पूर्ण

			chunklen = min(miter.length - offset, len);
			स_रखो(miter.addr + offset, 0xFF, chunklen);
			len -= chunklen;
			offset = 0;
		पूर्ण

		sg_miter_stop(&miter);
		local_irq_restore(flags);

		अगर (offset)
			वापस -EFAULT;

		अगर (extra)
			स_रखो(extra, 0xFF, माप(*extra));
		वापस 0;
	पूर्ण

	अगर (pba >= msb->block_count) अणु
		pr_err("BUG: attempt to read beyond the end of the card at pba %d", pba);
		वापस -EINVAL;
	पूर्ण

	क्रम (try = 1; try < 3; try++) अणु
		msb->regs.param.block_address = cpu_to_be16(pba);
		msb->regs.param.page_address = page;
		msb->regs.param.cp = MEMSTICK_CP_PAGE;

		msb->current_sg = sg;
		msb->current_sg_offset = offset;
		error = msb_run_state_machine(msb, h_msb_पढ़ो_page);


		अगर (error == -EUCLEAN) अणु
			pr_notice("correctable error on pba %d, page %d",
				pba, page);
			error = 0;
		पूर्ण

		अगर (!error && extra)
			*extra = msb->regs.extra_data;

		अगर (!error || msb_reset(msb, true))
			अवरोध;

	पूर्ण

	/* Mark bad pages */
	अगर (error == -EBADMSG) अणु
		pr_err("uncorrectable error on read of pba %d, page %d",
			pba, page);

		अगर (msb->regs.extra_data.overग_लिखो_flag &
					MEMSTICK_OVERWRITE_PGST0)
			msb_mark_page_bad(msb, pba, page);
		वापस -EBADMSG;
	पूर्ण

	अगर (error)
		pr_err("read of pba %d, page %d failed with error %d",
			pba, page, error);
	वापस error;
पूर्ण

/* Reads oob of page only */
अटल पूर्णांक msb_पढ़ो_oob(काष्ठा msb_data *msb, u16 pba, u16 page,
	काष्ठा ms_extra_data_रेजिस्टर *extra)
अणु
	पूर्णांक error;

	BUG_ON(!extra);
	msb->regs.param.block_address = cpu_to_be16(pba);
	msb->regs.param.page_address = page;
	msb->regs.param.cp = MEMSTICK_CP_EXTRA;

	अगर (pba > msb->block_count) अणु
		pr_err("BUG: attempt to read beyond the end of card at pba %d", pba);
		वापस -EINVAL;
	पूर्ण

	error = msb_run_state_machine(msb, h_msb_पढ़ो_page);
	*extra = msb->regs.extra_data;

	अगर (error == -EUCLEAN) अणु
		pr_notice("correctable error on pba %d, page %d",
			pba, page);
		वापस 0;
	पूर्ण

	वापस error;
पूर्ण

/* Reads a block and compares it with data contained in scatterlist orig_sg */
अटल पूर्णांक msb_verअगरy_block(काष्ठा msb_data *msb, u16 pba,
				काष्ठा scatterlist *orig_sg,  पूर्णांक offset)
अणु
	काष्ठा scatterlist sg;
	पूर्णांक page = 0, error;

	sg_init_one(&sg, msb->block_buffer, msb->block_size);

	जबतक (page < msb->pages_in_block) अणु

		error = msb_पढ़ो_page(msb, pba, page,
				शून्य, &sg, page * msb->page_size);
		अगर (error)
			वापस error;
		page++;
	पूर्ण

	अगर (msb_sg_compare_to_buffer(orig_sg, offset,
				msb->block_buffer, msb->block_size))
		वापस -EIO;
	वापस 0;
पूर्ण

/* Writes exectly one block + oob */
अटल पूर्णांक msb_ग_लिखो_block(काष्ठा msb_data *msb,
			u16 pba, u32 lba, काष्ठा scatterlist *sg, पूर्णांक offset)
अणु
	पूर्णांक error, current_try = 1;
	BUG_ON(sg->length < msb->page_size);

	अगर (msb->पढ़ो_only)
		वापस -EROFS;

	अगर (pba == MS_BLOCK_INVALID) अणु
		pr_err(
			"BUG: write: attempt to write MS_BLOCK_INVALID block");
		वापस -EINVAL;
	पूर्ण

	अगर (pba >= msb->block_count || lba >= msb->logical_block_count) अणु
		pr_err(
		"BUG: write: attempt to write beyond the end of device");
		वापस -EINVAL;
	पूर्ण

	अगर (msb_get_zone_from_lba(lba) != msb_get_zone_from_pba(pba)) अणु
		pr_err("BUG: write: lba zone mismatch");
		वापस -EINVAL;
	पूर्ण

	अगर (pba == msb->boot_block_locations[0] ||
		pba == msb->boot_block_locations[1]) अणु
		pr_err("BUG: write: attempt to write to boot blocks!");
		वापस -EINVAL;
	पूर्ण

	जबतक (1) अणु

		अगर (msb->पढ़ो_only)
			वापस -EROFS;

		msb->regs.param.cp = MEMSTICK_CP_BLOCK;
		msb->regs.param.page_address = 0;
		msb->regs.param.block_address = cpu_to_be16(pba);

		msb->regs.extra_data.management_flag = 0xFF;
		msb->regs.extra_data.overग_लिखो_flag = 0xF8;
		msb->regs.extra_data.logical_address = cpu_to_be16(lba);

		msb->current_sg = sg;
		msb->current_sg_offset = offset;
		msb->current_page = 0;

		error = msb_run_state_machine(msb, h_msb_ग_लिखो_block);

		/* Sector we just wrote to is assumed erased since its pba
			was erased. If it wasn't erased, ग_लिखो will succeed
			and will just clear the bits that were set in the block
			thus test that what we have written,
			matches what we expect.
			We करो trust the blocks that we erased */
		अगर (!error && (verअगरy_ग_लिखोs ||
				!test_bit(pba, msb->erased_blocks_biपंचांगap)))
			error = msb_verअगरy_block(msb, pba, sg, offset);

		अगर (!error)
			अवरोध;

		अगर (current_try > 1 || msb_reset(msb, true))
			अवरोध;

		pr_err("write failed, trying to erase the pba %d", pba);
		error = msb_erase_block(msb, pba);
		अगर (error)
			अवरोध;

		current_try++;
	पूर्ण
	वापस error;
पूर्ण

/* Finds a मुक्त block क्रम ग_लिखो replacement */
अटल u16 msb_get_मुक्त_block(काष्ठा msb_data *msb, पूर्णांक zone)
अणु
	u16 pos;
	पूर्णांक pba = zone * MS_BLOCKS_IN_ZONE;
	पूर्णांक i;

	get_अक्रमom_bytes(&pos, माप(pos));

	अगर (!msb->मुक्त_block_count[zone]) अणु
		pr_err("NO free blocks in the zone %d, to use for a write, (media is WORN out) switching to RO mode", zone);
		msb->पढ़ो_only = true;
		वापस MS_BLOCK_INVALID;
	पूर्ण

	pos %= msb->मुक्त_block_count[zone];

	dbg_verbose("have %d choices for a free block, selected randomly: %d",
		msb->मुक्त_block_count[zone], pos);

	pba = find_next_zero_bit(msb->used_blocks_biपंचांगap,
							msb->block_count, pba);
	क्रम (i = 0; i < pos; ++i)
		pba = find_next_zero_bit(msb->used_blocks_biपंचांगap,
						msb->block_count, pba + 1);

	dbg_verbose("result of the free blocks scan: pba %d", pba);

	अगर (pba == msb->block_count || (msb_get_zone_from_pba(pba)) != zone) अणु
		pr_err("BUG: cant get a free block");
		msb->पढ़ो_only = true;
		वापस MS_BLOCK_INVALID;
	पूर्ण

	msb_mark_block_used(msb, pba);
	वापस pba;
पूर्ण

अटल पूर्णांक msb_update_block(काष्ठा msb_data *msb, u16 lba,
	काष्ठा scatterlist *sg, पूर्णांक offset)
अणु
	u16 pba, new_pba;
	पूर्णांक error, try;

	pba = msb->lba_to_pba_table[lba];
	dbg_verbose("start of a block update at lba  %d, pba %d", lba, pba);

	अगर (pba != MS_BLOCK_INVALID) अणु
		dbg_verbose("setting the update flag on the block");
		msb_set_overग_लिखो_flag(msb, pba, 0,
				0xFF & ~MEMSTICK_OVERWRITE_UDST);
	पूर्ण

	क्रम (try = 0; try < 3; try++) अणु
		new_pba = msb_get_मुक्त_block(msb,
			msb_get_zone_from_lba(lba));

		अगर (new_pba == MS_BLOCK_INVALID) अणु
			error = -EIO;
			जाओ out;
		पूर्ण

		dbg_verbose("block update: writing updated block to the pba %d",
								new_pba);
		error = msb_ग_लिखो_block(msb, new_pba, lba, sg, offset);
		अगर (error == -EBADMSG) अणु
			msb_mark_bad(msb, new_pba);
			जारी;
		पूर्ण

		अगर (error)
			जाओ out;

		dbg_verbose("block update: erasing the old block");
		msb_erase_block(msb, pba);
		msb->lba_to_pba_table[lba] = new_pba;
		वापस 0;
	पूर्ण
out:
	अगर (error) अणु
		pr_err("block update error after %d tries,  switching to r/o mode", try);
		msb->पढ़ो_only = true;
	पूर्ण
	वापस error;
पूर्ण

/* Converts endiannes in the boot block क्रम easy use */
अटल व्योम msb_fix_boot_page_endianness(काष्ठा ms_boot_page *p)
अणु
	p->header.block_id = be16_to_cpu(p->header.block_id);
	p->header.क्रमmat_reserved = be16_to_cpu(p->header.क्रमmat_reserved);
	p->entry.disabled_block.start_addr
		= be32_to_cpu(p->entry.disabled_block.start_addr);
	p->entry.disabled_block.data_size
		= be32_to_cpu(p->entry.disabled_block.data_size);
	p->entry.cis_idi.start_addr
		= be32_to_cpu(p->entry.cis_idi.start_addr);
	p->entry.cis_idi.data_size
		= be32_to_cpu(p->entry.cis_idi.data_size);
	p->attr.block_size = be16_to_cpu(p->attr.block_size);
	p->attr.number_of_blocks = be16_to_cpu(p->attr.number_of_blocks);
	p->attr.number_of_effective_blocks
		= be16_to_cpu(p->attr.number_of_effective_blocks);
	p->attr.page_size = be16_to_cpu(p->attr.page_size);
	p->attr.memory_manufacturer_code
		= be16_to_cpu(p->attr.memory_manufacturer_code);
	p->attr.memory_device_code = be16_to_cpu(p->attr.memory_device_code);
	p->attr.implemented_capacity
		= be16_to_cpu(p->attr.implemented_capacity);
	p->attr.controller_number = be16_to_cpu(p->attr.controller_number);
	p->attr.controller_function = be16_to_cpu(p->attr.controller_function);
पूर्ण

अटल पूर्णांक msb_पढ़ो_boot_blocks(काष्ठा msb_data *msb)
अणु
	पूर्णांक pba = 0;
	काष्ठा scatterlist sg;
	काष्ठा ms_extra_data_रेजिस्टर extra;
	काष्ठा ms_boot_page *page;

	msb->boot_block_locations[0] = MS_BLOCK_INVALID;
	msb->boot_block_locations[1] = MS_BLOCK_INVALID;
	msb->boot_block_count = 0;

	dbg_verbose("Start of a scan for the boot blocks");

	अगर (!msb->boot_page) अणु
		page = kदो_स्मृति_array(2, माप(काष्ठा ms_boot_page),
				     GFP_KERNEL);
		अगर (!page)
			वापस -ENOMEM;

		msb->boot_page = page;
	पूर्ण अन्यथा
		page = msb->boot_page;

	msb->block_count = MS_BLOCK_MAX_BOOT_ADDR;

	क्रम (pba = 0; pba < MS_BLOCK_MAX_BOOT_ADDR; pba++) अणु

		sg_init_one(&sg, page, माप(*page));
		अगर (msb_पढ़ो_page(msb, pba, 0, &extra, &sg, 0)) अणु
			dbg("boot scan: can't read pba %d", pba);
			जारी;
		पूर्ण

		अगर (extra.management_flag & MEMSTICK_MANAGEMENT_SYSFLG) अणु
			dbg("management flag doesn't indicate boot block %d",
									pba);
			जारी;
		पूर्ण

		अगर (be16_to_cpu(page->header.block_id) != MS_BLOCK_BOOT_ID) अणु
			dbg("the pba at %d doesn't contain boot block ID", pba);
			जारी;
		पूर्ण

		msb_fix_boot_page_endianness(page);
		msb->boot_block_locations[msb->boot_block_count] = pba;

		page++;
		msb->boot_block_count++;

		अगर (msb->boot_block_count == 2)
			अवरोध;
	पूर्ण

	अगर (!msb->boot_block_count) अणु
		pr_err("media doesn't contain master page, aborting");
		वापस -EIO;
	पूर्ण

	dbg_verbose("End of scan for boot blocks");
	वापस 0;
पूर्ण

अटल पूर्णांक msb_पढ़ो_bad_block_table(काष्ठा msb_data *msb, पूर्णांक block_nr)
अणु
	काष्ठा ms_boot_page *boot_block;
	काष्ठा scatterlist sg;
	u16 *buffer = शून्य;
	पूर्णांक offset = 0;
	पूर्णांक i, error = 0;
	पूर्णांक data_size, data_offset, page, page_offset, माप_प्रकारo_पढ़ो;
	u16 pba;

	BUG_ON(block_nr > 1);
	boot_block = &msb->boot_page[block_nr];
	pba = msb->boot_block_locations[block_nr];

	अगर (msb->boot_block_locations[block_nr] == MS_BLOCK_INVALID)
		वापस -EINVAL;

	data_size = boot_block->entry.disabled_block.data_size;
	data_offset = माप(काष्ठा ms_boot_page) +
			boot_block->entry.disabled_block.start_addr;
	अगर (!data_size)
		वापस 0;

	page = data_offset / msb->page_size;
	page_offset = data_offset % msb->page_size;
	माप_प्रकारo_पढ़ो =
		DIV_ROUND_UP(data_size + page_offset, msb->page_size) *
			msb->page_size;

	dbg("reading bad block of boot block at pba %d, offset %d len %d",
		pba, data_offset, data_size);

	buffer = kzalloc(माप_प्रकारo_पढ़ो, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* Read the buffer */
	sg_init_one(&sg, buffer, माप_प्रकारo_पढ़ो);

	जबतक (offset < माप_प्रकारo_पढ़ो) अणु
		error = msb_पढ़ो_page(msb, pba, page, शून्य, &sg, offset);
		अगर (error)
			जाओ out;

		page++;
		offset += msb->page_size;

		अगर (page == msb->pages_in_block) अणु
			pr_err(
			"bad block table extends beyond the boot block");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Process the bad block table */
	क्रम (i = page_offset; i < data_size / माप(u16); i++) अणु

		u16 bad_block = be16_to_cpu(buffer[i]);

		अगर (bad_block >= msb->block_count) अणु
			dbg("bad block table contains invalid block %d",
								bad_block);
			जारी;
		पूर्ण

		अगर (test_bit(bad_block, msb->used_blocks_biपंचांगap))  अणु
			dbg("duplicate bad block %d in the table",
				bad_block);
			जारी;
		पूर्ण

		dbg("block %d is marked as factory bad", bad_block);
		msb_mark_block_used(msb, bad_block);
	पूर्ण
out:
	kमुक्त(buffer);
	वापस error;
पूर्ण

अटल पूर्णांक msb_ftl_initialize(काष्ठा msb_data *msb)
अणु
	पूर्णांक i;

	अगर (msb->ftl_initialized)
		वापस 0;

	msb->zone_count = msb->block_count / MS_BLOCKS_IN_ZONE;
	msb->logical_block_count = msb->zone_count * 496 - 2;

	msb->used_blocks_biपंचांगap = kzalloc(msb->block_count / 8, GFP_KERNEL);
	msb->erased_blocks_biपंचांगap = kzalloc(msb->block_count / 8, GFP_KERNEL);
	msb->lba_to_pba_table =
		kदो_स्मृति_array(msb->logical_block_count, माप(u16),
			      GFP_KERNEL);

	अगर (!msb->used_blocks_biपंचांगap || !msb->lba_to_pba_table ||
						!msb->erased_blocks_biपंचांगap) अणु
		kमुक्त(msb->used_blocks_biपंचांगap);
		kमुक्त(msb->lba_to_pba_table);
		kमुक्त(msb->erased_blocks_biपंचांगap);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < msb->zone_count; i++)
		msb->मुक्त_block_count[i] = MS_BLOCKS_IN_ZONE;

	स_रखो(msb->lba_to_pba_table, MS_BLOCK_INVALID,
			msb->logical_block_count * माप(u16));

	dbg("initial FTL tables created. Zone count = %d, Logical block count = %d",
		msb->zone_count, msb->logical_block_count);

	msb->ftl_initialized = true;
	वापस 0;
पूर्ण

अटल पूर्णांक msb_ftl_scan(काष्ठा msb_data *msb)
अणु
	u16 pba, lba, other_block;
	u8 overग_लिखो_flag, management_flag, other_overग_लिखो_flag;
	पूर्णांक error;
	काष्ठा ms_extra_data_रेजिस्टर extra;
	u8 *overग_लिखो_flags = kzalloc(msb->block_count, GFP_KERNEL);

	अगर (!overग_लिखो_flags)
		वापस -ENOMEM;

	dbg("Start of media scanning");
	क्रम (pba = 0; pba < msb->block_count; pba++) अणु

		अगर (pba == msb->boot_block_locations[0] ||
			pba == msb->boot_block_locations[1]) अणु
			dbg_verbose("pba %05d -> [boot block]", pba);
			msb_mark_block_used(msb, pba);
			जारी;
		पूर्ण

		अगर (test_bit(pba, msb->used_blocks_biपंचांगap)) अणु
			dbg_verbose("pba %05d -> [factory bad]", pba);
			जारी;
		पूर्ण

		स_रखो(&extra, 0, माप(extra));
		error = msb_पढ़ो_oob(msb, pba, 0, &extra);

		/* can't trust the page if we can't पढ़ो the oob */
		अगर (error == -EBADMSG) अणु
			pr_notice(
			"oob of pba %d damaged, will try to erase it", pba);
			msb_mark_block_used(msb, pba);
			msb_erase_block(msb, pba);
			जारी;
		पूर्ण अन्यथा अगर (error) अणु
			pr_err("unknown error %d on read of oob of pba %d - aborting",
				error, pba);

			kमुक्त(overग_लिखो_flags);
			वापस error;
		पूर्ण

		lba = be16_to_cpu(extra.logical_address);
		management_flag = extra.management_flag;
		overग_लिखो_flag = extra.overग_लिखो_flag;
		overग_लिखो_flags[pba] = overग_लिखो_flag;

		/* Skip bad blocks */
		अगर (!(overग_लिखो_flag & MEMSTICK_OVERWRITE_BKST)) अणु
			dbg("pba %05d -> [BAD]", pba);
			msb_mark_block_used(msb, pba);
			जारी;
		पूर्ण

		/* Skip प्रणाली/drm blocks */
		अगर ((management_flag & MEMSTICK_MANAGEMENT_FLAG_NORMAL) !=
			MEMSTICK_MANAGEMENT_FLAG_NORMAL) अणु
			dbg("pba %05d -> [reserved management flag %02x]",
							pba, management_flag);
			msb_mark_block_used(msb, pba);
			जारी;
		पूर्ण

		/* Erase temporary tables */
		अगर (!(management_flag & MEMSTICK_MANAGEMENT_ATFLG)) अणु
			dbg("pba %05d -> [temp table] - will erase", pba);

			msb_mark_block_used(msb, pba);
			msb_erase_block(msb, pba);
			जारी;
		पूर्ण

		अगर (lba == MS_BLOCK_INVALID) अणु
			dbg_verbose("pba %05d -> [free]", pba);
			जारी;
		पूर्ण

		msb_mark_block_used(msb, pba);

		/* Block has LBA not according to zoning*/
		अगर (msb_get_zone_from_lba(lba) != msb_get_zone_from_pba(pba)) अणु
			pr_notice("pba %05d -> [bad lba %05d] - will erase",
								pba, lba);
			msb_erase_block(msb, pba);
			जारी;
		पूर्ण

		/* No collisions - great */
		अगर (msb->lba_to_pba_table[lba] == MS_BLOCK_INVALID) अणु
			dbg_verbose("pba %05d -> [lba %05d]", pba, lba);
			msb->lba_to_pba_table[lba] = pba;
			जारी;
		पूर्ण

		other_block = msb->lba_to_pba_table[lba];
		other_overग_लिखो_flag = overग_लिखो_flags[other_block];

		pr_notice("Collision between pba %d and pba %d",
			pba, other_block);

		अगर (!(overग_लिखो_flag & MEMSTICK_OVERWRITE_UDST)) अणु
			pr_notice("pba %d is marked as stable, use it", pba);
			msb_erase_block(msb, other_block);
			msb->lba_to_pba_table[lba] = pba;
			जारी;
		पूर्ण

		अगर (!(other_overग_लिखो_flag & MEMSTICK_OVERWRITE_UDST)) अणु
			pr_notice("pba %d is marked as stable, use it",
								other_block);
			msb_erase_block(msb, pba);
			जारी;
		पूर्ण

		pr_notice("collision between blocks %d and %d, without stable flag set on both, erasing pba %d",
				pba, other_block, other_block);

		msb_erase_block(msb, other_block);
		msb->lba_to_pba_table[lba] = pba;
	पूर्ण

	dbg("End of media scanning");
	kमुक्त(overग_लिखो_flags);
	वापस 0;
पूर्ण

अटल व्योम msb_cache_flush_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा msb_data *msb = from_समयr(msb, t, cache_flush_समयr);
	msb->need_flush_cache = true;
	queue_work(msb->io_queue, &msb->io_work);
पूर्ण


अटल व्योम msb_cache_discard(काष्ठा msb_data *msb)
अणु
	अगर (msb->cache_block_lba == MS_BLOCK_INVALID)
		वापस;

	del_समयr_sync(&msb->cache_flush_समयr);

	dbg_verbose("Discarding the write cache");
	msb->cache_block_lba = MS_BLOCK_INVALID;
	biपंचांगap_zero(&msb->valid_cache_biपंचांगap, msb->pages_in_block);
पूर्ण

अटल पूर्णांक msb_cache_init(काष्ठा msb_data *msb)
अणु
	समयr_setup(&msb->cache_flush_समयr, msb_cache_flush_समयr, 0);

	अगर (!msb->cache)
		msb->cache = kzalloc(msb->block_size, GFP_KERNEL);
	अगर (!msb->cache)
		वापस -ENOMEM;

	msb_cache_discard(msb);
	वापस 0;
पूर्ण

अटल पूर्णांक msb_cache_flush(काष्ठा msb_data *msb)
अणु
	काष्ठा scatterlist sg;
	काष्ठा ms_extra_data_रेजिस्टर extra;
	पूर्णांक page, offset, error;
	u16 pba, lba;

	अगर (msb->पढ़ो_only)
		वापस -EROFS;

	अगर (msb->cache_block_lba == MS_BLOCK_INVALID)
		वापस 0;

	lba = msb->cache_block_lba;
	pba = msb->lba_to_pba_table[lba];

	dbg_verbose("Flushing the write cache of pba %d (LBA %d)",
						pba, msb->cache_block_lba);

	sg_init_one(&sg, msb->cache , msb->block_size);

	/* Read all missing pages in cache */
	क्रम (page = 0; page < msb->pages_in_block; page++) अणु

		अगर (test_bit(page, &msb->valid_cache_biपंचांगap))
			जारी;

		offset = page * msb->page_size;

		dbg_verbose("reading non-present sector %d of cache block %d",
			page, lba);
		error = msb_पढ़ो_page(msb, pba, page, &extra, &sg, offset);

		/* Bad pages are copied with 00 page status */
		अगर (error == -EBADMSG) अणु
			pr_err("read error on sector %d, contents probably damaged", page);
			जारी;
		पूर्ण

		अगर (error)
			वापस error;

		अगर ((extra.overग_लिखो_flag & MEMSTICK_OV_PG_NORMAL) !=
							MEMSTICK_OV_PG_NORMAL) अणु
			dbg("page %d is marked as bad", page);
			जारी;
		पूर्ण

		set_bit(page, &msb->valid_cache_biपंचांगap);
	पूर्ण

	/* Write the cache now */
	error = msb_update_block(msb, msb->cache_block_lba, &sg, 0);
	pba = msb->lba_to_pba_table[msb->cache_block_lba];

	/* Mark invalid pages */
	अगर (!error) अणु
		क्रम (page = 0; page < msb->pages_in_block; page++) अणु

			अगर (test_bit(page, &msb->valid_cache_biपंचांगap))
				जारी;

			dbg("marking page %d as containing damaged data",
				page);
			msb_set_overग_लिखो_flag(msb,
				pba , page, 0xFF & ~MEMSTICK_OV_PG_NORMAL);
		पूर्ण
	पूर्ण

	msb_cache_discard(msb);
	वापस error;
पूर्ण

अटल पूर्णांक msb_cache_ग_लिखो(काष्ठा msb_data *msb, पूर्णांक lba,
	पूर्णांक page, bool add_to_cache_only, काष्ठा scatterlist *sg, पूर्णांक offset)
अणु
	पूर्णांक error;
	काष्ठा scatterlist sg_पंचांगp[10];

	अगर (msb->पढ़ो_only)
		वापस -EROFS;

	अगर (msb->cache_block_lba == MS_BLOCK_INVALID ||
						lba != msb->cache_block_lba)
		अगर (add_to_cache_only)
			वापस 0;

	/* If we need to ग_लिखो dअगरferent block */
	अगर (msb->cache_block_lba != MS_BLOCK_INVALID &&
						lba != msb->cache_block_lba) अणु
		dbg_verbose("first flush the cache");
		error = msb_cache_flush(msb);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (msb->cache_block_lba  == MS_BLOCK_INVALID) अणु
		msb->cache_block_lba  = lba;
		mod_समयr(&msb->cache_flush_समयr,
			jअगरfies + msecs_to_jअगरfies(cache_flush_समयout));
	पूर्ण

	dbg_verbose("Write of LBA %d page %d to cache ", lba, page);

	sg_init_table(sg_पंचांगp, ARRAY_SIZE(sg_पंचांगp));
	msb_sg_copy(sg, sg_पंचांगp, ARRAY_SIZE(sg_पंचांगp), offset, msb->page_size);

	sg_copy_to_buffer(sg_पंचांगp, sg_nents(sg_पंचांगp),
		msb->cache + page * msb->page_size, msb->page_size);

	set_bit(page, &msb->valid_cache_biपंचांगap);
	वापस 0;
पूर्ण

अटल पूर्णांक msb_cache_पढ़ो(काष्ठा msb_data *msb, पूर्णांक lba,
				पूर्णांक page, काष्ठा scatterlist *sg, पूर्णांक offset)
अणु
	पूर्णांक pba = msb->lba_to_pba_table[lba];
	काष्ठा scatterlist sg_पंचांगp[10];
	पूर्णांक error = 0;

	अगर (lba == msb->cache_block_lba &&
			test_bit(page, &msb->valid_cache_biपंचांगap)) अणु

		dbg_verbose("Read of LBA %d (pba %d) sector %d from cache",
							lba, pba, page);

		sg_init_table(sg_पंचांगp, ARRAY_SIZE(sg_पंचांगp));
		msb_sg_copy(sg, sg_पंचांगp, ARRAY_SIZE(sg_पंचांगp),
			offset, msb->page_size);
		sg_copy_from_buffer(sg_पंचांगp, sg_nents(sg_पंचांगp),
			msb->cache + msb->page_size * page,
							msb->page_size);
	पूर्ण अन्यथा अणु
		dbg_verbose("Read of LBA %d (pba %d) sector %d from device",
							lba, pba, page);

		error = msb_पढ़ो_page(msb, pba, page, शून्य, sg, offset);
		अगर (error)
			वापस error;

		msb_cache_ग_लिखो(msb, lba, page, true, sg, offset);
	पूर्ण
	वापस error;
पूर्ण

/* Emulated geometry table
 * This table content isn't that importaपूर्णांक,
 * One could put here dअगरferent values, providing that they still
 * cover whole disk.
 * 64 MB entry is what winकरोws reports क्रम my 64M memstick */

अटल स्थिर काष्ठा chs_entry chs_table[] = अणु
/*        size sectors cylynders  heads */
	अणु 4,    16,    247,       2  पूर्ण,
	अणु 8,    16,    495,       2  पूर्ण,
	अणु 16,   16,    495,       4  पूर्ण,
	अणु 32,   16,    991,       4  पूर्ण,
	अणु 64,   16,    991,       8  पूर्ण,
	अणु128,   16,    991,       16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* Load inक्रमmation about the card */
अटल पूर्णांक msb_init_card(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_host *host = card->host;
	काष्ठा ms_boot_page *boot_block;
	पूर्णांक error = 0, i, raw_size_in_megs;

	msb->caps = 0;

	अगर (card->id.class >= MEMSTICK_CLASS_ROM &&
				card->id.class <= MEMSTICK_CLASS_ROM)
		msb->पढ़ो_only = true;

	msb->state = -1;
	error = msb_reset(msb, false);
	अगर (error)
		वापस error;

	/* Due to a bug in Jmicron driver written by Alex Dubov,
	 its serial mode barely works,
	 so we चयन to parallel mode right away */
	अगर (host->caps & MEMSTICK_CAP_PAR4)
		msb_चयन_to_parallel(msb);

	msb->page_size = माप(काष्ठा ms_boot_page);

	/* Read the boot page */
	error = msb_पढ़ो_boot_blocks(msb);
	अगर (error)
		वापस -EIO;

	boot_block = &msb->boot_page[0];

	/* Save पूर्णांकersting attributes from boot page */
	msb->block_count = boot_block->attr.number_of_blocks;
	msb->page_size = boot_block->attr.page_size;

	msb->pages_in_block = boot_block->attr.block_size * 2;
	msb->block_size = msb->page_size * msb->pages_in_block;

	अगर (msb->page_size > PAGE_SIZE) अणु
		/* this isn't supported by linux at all, anyway*/
		dbg("device page %d size isn't supported", msb->page_size);
		वापस -EINVAL;
	पूर्ण

	msb->block_buffer = kzalloc(msb->block_size, GFP_KERNEL);
	अगर (!msb->block_buffer)
		वापस -ENOMEM;

	raw_size_in_megs = (msb->block_size * msb->block_count) >> 20;

	क्रम (i = 0; chs_table[i].size; i++) अणु

		अगर (chs_table[i].size != raw_size_in_megs)
			जारी;

		msb->geometry.cylinders = chs_table[i].cyl;
		msb->geometry.heads = chs_table[i].head;
		msb->geometry.sectors = chs_table[i].sec;
		अवरोध;
	पूर्ण

	अगर (boot_block->attr.transfer_supporting == 1)
		msb->caps |= MEMSTICK_CAP_PAR4;

	अगर (boot_block->attr.device_type & 0x03)
		msb->पढ़ो_only = true;

	dbg("Total block count = %d", msb->block_count);
	dbg("Each block consists of %d pages", msb->pages_in_block);
	dbg("Page size = %d bytes", msb->page_size);
	dbg("Parallel mode supported: %d", !!(msb->caps & MEMSTICK_CAP_PAR4));
	dbg("Read only: %d", msb->पढ़ो_only);

#अगर 0
	/* Now we can चयन the पूर्णांकerface */
	अगर (host->caps & msb->caps & MEMSTICK_CAP_PAR4)
		msb_चयन_to_parallel(msb);
#पूर्ण_अगर

	error = msb_cache_init(msb);
	अगर (error)
		वापस error;

	error = msb_ftl_initialize(msb);
	अगर (error)
		वापस error;


	/* Read the bad block table */
	error = msb_पढ़ो_bad_block_table(msb, 0);

	अगर (error && error != -ENOMEM) अणु
		dbg("failed to read bad block table from primary boot block, trying from backup");
		error = msb_पढ़ो_bad_block_table(msb, 1);
	पूर्ण

	अगर (error)
		वापस error;

	/* *drum roll* Scan the media */
	error = msb_ftl_scan(msb);
	अगर (error) अणु
		pr_err("Scan of media failed");
		वापस error;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक msb_करो_ग_लिखो_request(काष्ठा msb_data *msb, पूर्णांक lba,
	पूर्णांक page, काष्ठा scatterlist *sg, माप_प्रकार len, पूर्णांक *sucessfuly_written)
अणु
	पूर्णांक error = 0;
	off_t offset = 0;
	*sucessfuly_written = 0;

	जबतक (offset < len) अणु
		अगर (page == 0 && len - offset >= msb->block_size) अणु

			अगर (msb->cache_block_lba == lba)
				msb_cache_discard(msb);

			dbg_verbose("Writing whole lba %d", lba);
			error = msb_update_block(msb, lba, sg, offset);
			अगर (error)
				वापस error;

			offset += msb->block_size;
			*sucessfuly_written += msb->block_size;
			lba++;
			जारी;
		पूर्ण

		error = msb_cache_ग_लिखो(msb, lba, page, false, sg, offset);
		अगर (error)
			वापस error;

		offset += msb->page_size;
		*sucessfuly_written += msb->page_size;

		page++;
		अगर (page == msb->pages_in_block) अणु
			page = 0;
			lba++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msb_करो_पढ़ो_request(काष्ठा msb_data *msb, पूर्णांक lba,
		पूर्णांक page, काष्ठा scatterlist *sg, पूर्णांक len, पूर्णांक *sucessfuly_पढ़ो)
अणु
	पूर्णांक error = 0;
	पूर्णांक offset = 0;
	*sucessfuly_पढ़ो = 0;

	जबतक (offset < len) अणु

		error = msb_cache_पढ़ो(msb, lba, page, sg, offset);
		अगर (error)
			वापस error;

		offset += msb->page_size;
		*sucessfuly_पढ़ो += msb->page_size;

		page++;
		अगर (page == msb->pages_in_block) अणु
			page = 0;
			lba++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम msb_io_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msb_data *msb = container_of(work, काष्ठा msb_data, io_work);
	पूर्णांक page, error, len;
	sector_t lba;
	काष्ठा scatterlist *sg = msb->pपुनः_स्मृति_sg;
	काष्ठा request *req;

	dbg_verbose("IO: work started");

	जबतक (1) अणु
		spin_lock_irq(&msb->q_lock);

		अगर (msb->need_flush_cache) अणु
			msb->need_flush_cache = false;
			spin_unlock_irq(&msb->q_lock);
			msb_cache_flush(msb);
			जारी;
		पूर्ण

		req = msb->req;
		अगर (!req) अणु
			dbg_verbose("IO: no more requests exiting");
			spin_unlock_irq(&msb->q_lock);
			वापस;
		पूर्ण

		spin_unlock_irq(&msb->q_lock);

		/* process the request */
		dbg_verbose("IO: processing new request");
		blk_rq_map_sg(msb->queue, req, sg);

		lba = blk_rq_pos(req);

		sector_भाग(lba, msb->page_size / 512);
		page = sector_भाग(lba, msb->pages_in_block);

		अगर (rq_data_dir(msb->req) == READ)
			error = msb_करो_पढ़ो_request(msb, lba, page, sg,
				blk_rq_bytes(req), &len);
		अन्यथा
			error = msb_करो_ग_लिखो_request(msb, lba, page, sg,
				blk_rq_bytes(req), &len);

		अगर (len && !blk_update_request(req, BLK_STS_OK, len)) अणु
			__blk_mq_end_request(req, BLK_STS_OK);
			spin_lock_irq(&msb->q_lock);
			msb->req = शून्य;
			spin_unlock_irq(&msb->q_lock);
		पूर्ण

		अगर (error && msb->req) अणु
			blk_status_t ret = त्रुटि_सं_to_blk_status(error);

			dbg_verbose("IO: ending one sector of the request with error");
			blk_mq_end_request(req, ret);
			spin_lock_irq(&msb->q_lock);
			msb->req = शून्य;
			spin_unlock_irq(&msb->q_lock);
		पूर्ण

		अगर (msb->req)
			dbg_verbose("IO: request still pending");
	पूर्ण
पूर्ण

अटल DEFINE_IDR(msb_disk_idr); /*set of used disk numbers */
अटल DEFINE_MUTEX(msb_disk_lock); /* protects against races in खोलो/release */

अटल पूर्णांक msb_bd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा msb_data *msb = disk->निजी_data;

	dbg_verbose("block device open");

	mutex_lock(&msb_disk_lock);

	अगर (msb && msb->card)
		msb->usage_count++;

	mutex_unlock(&msb_disk_lock);
	वापस 0;
पूर्ण

अटल व्योम msb_data_clear(काष्ठा msb_data *msb)
अणु
	kमुक्त(msb->boot_page);
	kमुक्त(msb->used_blocks_biपंचांगap);
	kमुक्त(msb->lba_to_pba_table);
	kमुक्त(msb->cache);
	msb->card = शून्य;
पूर्ण

अटल पूर्णांक msb_disk_release(काष्ठा gendisk *disk)
अणु
	काष्ठा msb_data *msb = disk->निजी_data;

	dbg_verbose("block device release");
	mutex_lock(&msb_disk_lock);

	अगर (msb) अणु
		अगर (msb->usage_count)
			msb->usage_count--;

		अगर (!msb->usage_count) अणु
			disk->निजी_data = शून्य;
			idr_हटाओ(&msb_disk_idr, msb->disk_id);
			put_disk(disk);
			kमुक्त(msb);
		पूर्ण
	पूर्ण
	mutex_unlock(&msb_disk_lock);
	वापस 0;
पूर्ण

अटल व्योम msb_bd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	msb_disk_release(disk);
पूर्ण

अटल पूर्णांक msb_bd_getgeo(काष्ठा block_device *bdev,
				 काष्ठा hd_geometry *geo)
अणु
	काष्ठा msb_data *msb = bdev->bd_disk->निजी_data;
	*geo = msb->geometry;
	वापस 0;
पूर्ण

अटल blk_status_t msb_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा memstick_dev *card = hctx->queue->queuedata;
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा request *req = bd->rq;

	dbg_verbose("Submit request");

	spin_lock_irq(&msb->q_lock);

	अगर (msb->card_dead) अणु
		dbg("Refusing requests on removed card");

		WARN_ON(!msb->io_queue_stopped);

		spin_unlock_irq(&msb->q_lock);
		blk_mq_start_request(req);
		वापस BLK_STS_IOERR;
	पूर्ण

	अगर (msb->req) अणु
		spin_unlock_irq(&msb->q_lock);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण

	blk_mq_start_request(req);
	msb->req = req;

	अगर (!msb->io_queue_stopped)
		queue_work(msb->io_queue, &msb->io_work);

	spin_unlock_irq(&msb->q_lock);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक msb_check_card(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	वापस (msb->card_dead == 0);
पूर्ण

अटल व्योम msb_stop(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	अचिन्हित दीर्घ flags;

	dbg("Stopping all msblock IO");

	blk_mq_stop_hw_queues(msb->queue);
	spin_lock_irqsave(&msb->q_lock, flags);
	msb->io_queue_stopped = true;
	spin_unlock_irqrestore(&msb->q_lock, flags);

	del_समयr_sync(&msb->cache_flush_समयr);
	flush_workqueue(msb->io_queue);

	spin_lock_irqsave(&msb->q_lock, flags);
	अगर (msb->req) अणु
		blk_mq_requeue_request(msb->req, false);
		msb->req = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&msb->q_lock, flags);
पूर्ण

अटल व्योम msb_start(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	अचिन्हित दीर्घ flags;

	dbg("Resuming IO from msblock");

	msb_invalidate_reg_winकरोw(msb);

	spin_lock_irqsave(&msb->q_lock, flags);
	अगर (!msb->io_queue_stopped || msb->card_dead) अणु
		spin_unlock_irqrestore(&msb->q_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&msb->q_lock, flags);

	/* Kick cache flush anyway, its harmless */
	msb->need_flush_cache = true;
	msb->io_queue_stopped = false;

	blk_mq_start_hw_queues(msb->queue);

	queue_work(msb->io_queue, &msb->io_work);

पूर्ण

अटल स्थिर काष्ठा block_device_operations msb_bकरोps = अणु
	.खोलो    = msb_bd_खोलो,
	.release = msb_bd_release,
	.getgeo  = msb_bd_getgeo,
	.owner   = THIS_MODULE
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops msb_mq_ops = अणु
	.queue_rq	= msb_queue_rq,
पूर्ण;

/* Registers the block device */
अटल पूर्णांक msb_init_disk(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	पूर्णांक rc;
	अचिन्हित दीर्घ capacity;

	mutex_lock(&msb_disk_lock);
	msb->disk_id = idr_alloc(&msb_disk_idr, card, 0, 256, GFP_KERNEL);
	mutex_unlock(&msb_disk_lock);

	अगर (msb->disk_id  < 0)
		वापस msb->disk_id;

	msb->disk = alloc_disk(0);
	अगर (!msb->disk) अणु
		rc = -ENOMEM;
		जाओ out_release_id;
	पूर्ण

	msb->queue = blk_mq_init_sq_queue(&msb->tag_set, &msb_mq_ops, 2,
						BLK_MQ_F_SHOULD_MERGE);
	अगर (IS_ERR(msb->queue)) अणु
		rc = PTR_ERR(msb->queue);
		msb->queue = शून्य;
		जाओ out_put_disk;
	पूर्ण

	msb->queue->queuedata = card;

	blk_queue_max_hw_sectors(msb->queue, MS_BLOCK_MAX_PAGES);
	blk_queue_max_segments(msb->queue, MS_BLOCK_MAX_SEGS);
	blk_queue_max_segment_size(msb->queue,
				   MS_BLOCK_MAX_PAGES * msb->page_size);
	blk_queue_logical_block_size(msb->queue, msb->page_size);

	प्र_लिखो(msb->disk->disk_name, "msblk%d", msb->disk_id);
	msb->disk->fops = &msb_bकरोps;
	msb->disk->निजी_data = msb;
	msb->disk->queue = msb->queue;
	msb->disk->flags |= GENHD_FL_EXT_DEVT;

	capacity = msb->pages_in_block * msb->logical_block_count;
	capacity *= (msb->page_size / 512);
	set_capacity(msb->disk, capacity);
	dbg("Set total disk size to %lu sectors", capacity);

	msb->usage_count = 1;
	msb->io_queue = alloc_ordered_workqueue("ms_block", WQ_MEM_RECLAIM);
	INIT_WORK(&msb->io_work, msb_io_work);
	sg_init_table(msb->pपुनः_स्मृति_sg, MS_BLOCK_MAX_SEGS+1);

	अगर (msb->पढ़ो_only)
		set_disk_ro(msb->disk, 1);

	msb_start(card);
	device_add_disk(&card->dev, msb->disk, शून्य);
	dbg("Disk added");
	वापस 0;

out_put_disk:
	put_disk(msb->disk);
out_release_id:
	mutex_lock(&msb_disk_lock);
	idr_हटाओ(&msb_disk_idr, msb->disk_id);
	mutex_unlock(&msb_disk_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक msb_probe(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb;
	पूर्णांक rc = 0;

	msb = kzalloc(माप(काष्ठा msb_data), GFP_KERNEL);
	अगर (!msb)
		वापस -ENOMEM;
	memstick_set_drvdata(card, msb);
	msb->card = card;
	spin_lock_init(&msb->q_lock);

	rc = msb_init_card(card);
	अगर (rc)
		जाओ out_मुक्त;

	rc = msb_init_disk(card);
	अगर (!rc) अणु
		card->check = msb_check_card;
		card->stop = msb_stop;
		card->start = msb_start;
		वापस 0;
	पूर्ण
out_मुक्त:
	memstick_set_drvdata(card, शून्य);
	msb_data_clear(msb);
	kमुक्त(msb);
	वापस rc;
पूर्ण

अटल व्योम msb_हटाओ(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	अचिन्हित दीर्घ flags;

	अगर (!msb->io_queue_stopped)
		msb_stop(card);

	dbg("Removing the disk device");

	/* Take care of unhandled + new requests from now on */
	spin_lock_irqsave(&msb->q_lock, flags);
	msb->card_dead = true;
	spin_unlock_irqrestore(&msb->q_lock, flags);
	blk_mq_start_hw_queues(msb->queue);

	/* Remove the disk */
	del_gendisk(msb->disk);
	blk_cleanup_queue(msb->queue);
	blk_mq_मुक्त_tag_set(&msb->tag_set);
	msb->queue = शून्य;

	mutex_lock(&msb_disk_lock);
	msb_data_clear(msb);
	mutex_unlock(&msb_disk_lock);

	msb_disk_release(msb->disk);
	memstick_set_drvdata(card, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक msb_suspend(काष्ठा memstick_dev *card, pm_message_t state)
अणु
	msb_stop(card);
	वापस 0;
पूर्ण

अटल पूर्णांक msb_resume(काष्ठा memstick_dev *card)
अणु
	काष्ठा msb_data *msb = memstick_get_drvdata(card);
	काष्ठा msb_data *new_msb = शून्य;
	bool card_dead = true;

#अगर_अघोषित CONFIG_MEMSTICK_UNSAFE_RESUME
	msb->card_dead = true;
	वापस 0;
#पूर्ण_अगर
	mutex_lock(&card->host->lock);

	new_msb = kzalloc(माप(काष्ठा msb_data), GFP_KERNEL);
	अगर (!new_msb)
		जाओ out;

	new_msb->card = card;
	memstick_set_drvdata(card, new_msb);
	spin_lock_init(&new_msb->q_lock);
	sg_init_table(msb->pपुनः_स्मृति_sg, MS_BLOCK_MAX_SEGS+1);

	अगर (msb_init_card(card))
		जाओ out;

	अगर (msb->block_size != new_msb->block_size)
		जाओ out;

	अगर (स_भेद(msb->boot_page, new_msb->boot_page,
					माप(काष्ठा ms_boot_page)))
		जाओ out;

	अगर (msb->logical_block_count != new_msb->logical_block_count ||
		स_भेद(msb->lba_to_pba_table, new_msb->lba_to_pba_table,
						msb->logical_block_count))
		जाओ out;

	अगर (msb->block_count != new_msb->block_count ||
		स_भेद(msb->used_blocks_biपंचांगap, new_msb->used_blocks_biपंचांगap,
							msb->block_count / 8))
		जाओ out;

	card_dead = false;
out:
	अगर (card_dead)
		dbg("Card was removed/replaced during suspend");

	msb->card_dead = card_dead;
	memstick_set_drvdata(card, msb);

	अगर (new_msb) अणु
		msb_data_clear(new_msb);
		kमुक्त(new_msb);
	पूर्ण

	msb_start(card);
	mutex_unlock(&card->host->lock);
	वापस 0;
पूर्ण
#अन्यथा

#घोषणा msb_suspend शून्य
#घोषणा msb_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा memstick_device_id msb_id_tbl[] = अणु
	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_LEGACY, MEMSTICK_CATEGORY_STORAGE,
	 MEMSTICK_CLASS_FLASHपूर्ण,

	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_LEGACY, MEMSTICK_CATEGORY_STORAGE,
	 MEMSTICK_CLASS_ROMपूर्ण,

	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_LEGACY, MEMSTICK_CATEGORY_STORAGE,
	 MEMSTICK_CLASS_ROपूर्ण,

	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_LEGACY, MEMSTICK_CATEGORY_STORAGE,
	 MEMSTICK_CLASS_WPपूर्ण,

	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_DUO, MEMSTICK_CATEGORY_STORAGE_DUO,
	 MEMSTICK_CLASS_DUOपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(memstick, msb_id_tbl);


अटल काष्ठा memstick_driver msb_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
		.owner = THIS_MODULE
	पूर्ण,
	.id_table = msb_id_tbl,
	.probe    = msb_probe,
	.हटाओ   = msb_हटाओ,
	.suspend  = msb_suspend,
	.resume   = msb_resume
पूर्ण;

अटल पूर्णांक __init msb_init(व्योम)
अणु
	पूर्णांक rc = memstick_रेजिस्टर_driver(&msb_driver);
	अगर (rc)
		pr_err("failed to register memstick driver (error %d)\n", rc);

	वापस rc;
पूर्ण

अटल व्योम __निकास msb_निकास(व्योम)
अणु
	memstick_unरेजिस्टर_driver(&msb_driver);
	idr_destroy(&msb_disk_idr);
पूर्ण

module_init(msb_init);
module_निकास(msb_निकास);

module_param(cache_flush_समयout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cache_flush_समयout,
				"Cache flush timeout in msec (1000 default)");
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

module_param(verअगरy_ग_लिखोs, bool, S_IRUGO);
MODULE_PARM_DESC(verअगरy_ग_लिखोs, "Read back and check all data that is written");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Levitsky");
MODULE_DESCRIPTION("Sony MemoryStick block device driver");
