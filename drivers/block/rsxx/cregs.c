<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Filename: cregs.c
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#समावेश <linux/completion.h>
#समावेश <linux/slab.h>

#समावेश "rsxx_priv.h"

#घोषणा CREG_TIMEOUT_MSEC	10000

प्रकार व्योम (*creg_cmd_cb)(काष्ठा rsxx_cardinfo *card,
			    काष्ठा creg_cmd *cmd,
			    पूर्णांक st);

काष्ठा creg_cmd अणु
	काष्ठा list_head list;
	creg_cmd_cb cb;
	व्योम *cb_निजी;
	अचिन्हित पूर्णांक op;
	अचिन्हित पूर्णांक addr;
	पूर्णांक cnt8;
	व्योम *buf;
	अचिन्हित पूर्णांक stream;
	अचिन्हित पूर्णांक status;
पूर्ण;

अटल काष्ठा kmem_cache *creg_cmd_pool;


/*------------ Private Functions --------------*/

#अगर defined(__LITTLE_ENDIAN)
#घोषणा LITTLE_ENDIAN 1
#या_अगर defined(__BIG_ENDIAN)
#घोषणा LITTLE_ENDIAN 0
#अन्यथा
#त्रुटि Unknown endianess!!! Aborting...
#पूर्ण_अगर

अटल पूर्णांक copy_to_creg_data(काष्ठा rsxx_cardinfo *card,
			      पूर्णांक cnt8,
			      व्योम *buf,
			      अचिन्हित पूर्णांक stream)
अणु
	पूर्णांक i = 0;
	u32 *data = buf;

	अगर (unlikely(card->eeh_state))
		वापस -EIO;

	क्रम (i = 0; cnt8 > 0; i++, cnt8 -= 4) अणु
		/*
		 * Firmware implementation makes it necessary to byte swap on
		 * little endian processors.
		 */
		अगर (LITTLE_ENDIAN && stream)
			ioग_लिखो32be(data[i], card->regmap + CREG_DATA(i));
		अन्यथा
			ioग_लिखो32(data[i], card->regmap + CREG_DATA(i));
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक copy_from_creg_data(काष्ठा rsxx_cardinfo *card,
				पूर्णांक cnt8,
				व्योम *buf,
				अचिन्हित पूर्णांक stream)
अणु
	पूर्णांक i = 0;
	u32 *data = buf;

	अगर (unlikely(card->eeh_state))
		वापस -EIO;

	क्रम (i = 0; cnt8 > 0; i++, cnt8 -= 4) अणु
		/*
		 * Firmware implementation makes it necessary to byte swap on
		 * little endian processors.
		 */
		अगर (LITTLE_ENDIAN && stream)
			data[i] = ioपढ़ो32be(card->regmap + CREG_DATA(i));
		अन्यथा
			data[i] = ioपढ़ो32(card->regmap + CREG_DATA(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम creg_issue_cmd(काष्ठा rsxx_cardinfo *card, काष्ठा creg_cmd *cmd)
अणु
	पूर्णांक st;

	अगर (unlikely(card->eeh_state))
		वापस;

	ioग_लिखो32(cmd->addr, card->regmap + CREG_ADD);
	ioग_लिखो32(cmd->cnt8, card->regmap + CREG_CNT);

	अगर (cmd->op == CREG_OP_WRITE) अणु
		अगर (cmd->buf) अणु
			st = copy_to_creg_data(card, cmd->cnt8,
					       cmd->buf, cmd->stream);
			अगर (st)
				वापस;
		पूर्ण
	पूर्ण

	अगर (unlikely(card->eeh_state))
		वापस;

	/* Setting the valid bit will kick off the command. */
	ioग_लिखो32(cmd->op, card->regmap + CREG_CMD);
पूर्ण

अटल व्योम creg_kick_queue(काष्ठा rsxx_cardinfo *card)
अणु
	अगर (card->creg_ctrl.active || list_empty(&card->creg_ctrl.queue))
		वापस;

	card->creg_ctrl.active = 1;
	card->creg_ctrl.active_cmd = list_first_entry(&card->creg_ctrl.queue,
						      काष्ठा creg_cmd, list);
	list_del(&card->creg_ctrl.active_cmd->list);
	card->creg_ctrl.q_depth--;

	/*
	 * We have to set the समयr beक्रमe we push the new command. Otherwise,
	 * we could create a race condition that would occur अगर the समयr
	 * was not canceled, and expired after the new command was pushed,
	 * but beक्रमe the command was issued to hardware.
	 */
	mod_समयr(&card->creg_ctrl.cmd_समयr,
				jअगरfies + msecs_to_jअगरfies(CREG_TIMEOUT_MSEC));

	creg_issue_cmd(card, card->creg_ctrl.active_cmd);
पूर्ण

अटल पूर्णांक creg_queue_cmd(काष्ठा rsxx_cardinfo *card,
			  अचिन्हित पूर्णांक op,
			  अचिन्हित पूर्णांक addr,
			  अचिन्हित पूर्णांक cnt8,
			  व्योम *buf,
			  पूर्णांक stream,
			  creg_cmd_cb callback,
			  व्योम *cb_निजी)
अणु
	काष्ठा creg_cmd *cmd;

	/* Don't queue stuff up if we're halted. */
	अगर (unlikely(card->halt))
		वापस -EINVAL;

	अगर (card->creg_ctrl.reset)
		वापस -EAGAIN;

	अगर (cnt8 > MAX_CREG_DATA8)
		वापस -EINVAL;

	cmd = kmem_cache_alloc(creg_cmd_pool, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&cmd->list);

	cmd->op		= op;
	cmd->addr	= addr;
	cmd->cnt8	= cnt8;
	cmd->buf	= buf;
	cmd->stream	= stream;
	cmd->cb		= callback;
	cmd->cb_निजी = cb_निजी;
	cmd->status	= 0;

	spin_lock_bh(&card->creg_ctrl.lock);
	list_add_tail(&cmd->list, &card->creg_ctrl.queue);
	card->creg_ctrl.q_depth++;
	creg_kick_queue(card);
	spin_unlock_bh(&card->creg_ctrl.lock);

	वापस 0;
पूर्ण

अटल व्योम creg_cmd_समयd_out(काष्ठा समयr_list *t)
अणु
	काष्ठा rsxx_cardinfo *card = from_समयr(card, t, creg_ctrl.cmd_समयr);
	काष्ठा creg_cmd *cmd;

	spin_lock(&card->creg_ctrl.lock);
	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = शून्य;
	spin_unlock(&card->creg_ctrl.lock);

	अगर (cmd == शून्य) अणु
		card->creg_ctrl.creg_stats.creg_समयout++;
		dev_warn(CARD_TO_DEV(card),
			"No active command associated with timeout!\n");
		वापस;
	पूर्ण

	अगर (cmd->cb)
		cmd->cb(card, cmd, -ETIMEDOUT);

	kmem_cache_मुक्त(creg_cmd_pool, cmd);


	spin_lock(&card->creg_ctrl.lock);
	card->creg_ctrl.active = 0;
	creg_kick_queue(card);
	spin_unlock(&card->creg_ctrl.lock);
पूर्ण


अटल व्योम creg_cmd_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rsxx_cardinfo *card;
	काष्ठा creg_cmd *cmd;
	पूर्णांक st = 0;

	card = container_of(work, काष्ठा rsxx_cardinfo,
			    creg_ctrl.करोne_work);

	/*
	 * The समयr could not be cancelled क्रम some reason,
	 * race to pop the active command.
	 */
	अगर (del_समयr_sync(&card->creg_ctrl.cmd_समयr) == 0)
		card->creg_ctrl.creg_stats.failed_cancel_समयr++;

	spin_lock_bh(&card->creg_ctrl.lock);
	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = शून्य;
	spin_unlock_bh(&card->creg_ctrl.lock);

	अगर (cmd == शून्य) अणु
		dev_err(CARD_TO_DEV(card),
			"Spurious creg interrupt!\n");
		वापस;
	पूर्ण

	card->creg_ctrl.creg_stats.stat = ioपढ़ो32(card->regmap + CREG_STAT);
	cmd->status = card->creg_ctrl.creg_stats.stat;
	अगर ((cmd->status & CREG_STAT_STATUS_MASK) == 0) अणु
		dev_err(CARD_TO_DEV(card),
			"Invalid status on creg command\n");
		/*
		 * At this poपूर्णांक we're probably reading garbage from HW. Don't
		 * करो anything अन्यथा that could mess up the प्रणाली and let
		 * the sync function वापस an error.
		 */
		st = -EIO;
		जाओ creg_करोne;
	पूर्ण अन्यथा अगर (cmd->status & CREG_STAT_ERROR) अणु
		st = -EIO;
	पूर्ण

	अगर (cmd->op == CREG_OP_READ) अणु
		अचिन्हित पूर्णांक cnt8 = ioपढ़ो32(card->regmap + CREG_CNT);

		/* Paranoid Sanity Checks */
		अगर (!cmd->buf) अणु
			dev_err(CARD_TO_DEV(card),
				"Buffer not given for read.\n");
			st = -EIO;
			जाओ creg_करोne;
		पूर्ण
		अगर (cnt8 != cmd->cnt8) अणु
			dev_err(CARD_TO_DEV(card),
				"count mismatch\n");
			st = -EIO;
			जाओ creg_करोne;
		पूर्ण

		st = copy_from_creg_data(card, cnt8, cmd->buf, cmd->stream);
	पूर्ण

creg_करोne:
	अगर (cmd->cb)
		cmd->cb(card, cmd, st);

	kmem_cache_मुक्त(creg_cmd_pool, cmd);

	spin_lock_bh(&card->creg_ctrl.lock);
	card->creg_ctrl.active = 0;
	creg_kick_queue(card);
	spin_unlock_bh(&card->creg_ctrl.lock);
पूर्ण

अटल व्योम creg_reset(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा creg_cmd *cmd = शून्य;
	काष्ठा creg_cmd *पंचांगp;
	अचिन्हित दीर्घ flags;

	/*
	 * mutex_trylock is used here because अगर reset_lock is taken then a
	 * reset is alपढ़ोy happening. So, we can just go ahead and वापस.
	 */
	अगर (!mutex_trylock(&card->creg_ctrl.reset_lock))
		वापस;

	card->creg_ctrl.reset = 1;
	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_disable_ier_and_isr(card, CR_INTR_CREG | CR_INTR_EVENT);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	dev_warn(CARD_TO_DEV(card),
		"Resetting creg interface for recovery\n");

	/* Cancel outstanding commands */
	spin_lock_bh(&card->creg_ctrl.lock);
	list_क्रम_each_entry_safe(cmd, पंचांगp, &card->creg_ctrl.queue, list) अणु
		list_del(&cmd->list);
		card->creg_ctrl.q_depth--;
		अगर (cmd->cb)
			cmd->cb(card, cmd, -ECANCELED);
		kmem_cache_मुक्त(creg_cmd_pool, cmd);
	पूर्ण

	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = शून्य;
	अगर (cmd) अणु
		अगर (समयr_pending(&card->creg_ctrl.cmd_समयr))
			del_समयr_sync(&card->creg_ctrl.cmd_समयr);

		अगर (cmd->cb)
			cmd->cb(card, cmd, -ECANCELED);
		kmem_cache_मुक्त(creg_cmd_pool, cmd);

		card->creg_ctrl.active = 0;
	पूर्ण
	spin_unlock_bh(&card->creg_ctrl.lock);

	card->creg_ctrl.reset = 0;
	spin_lock_irqsave(&card->irq_lock, flags);
	rsxx_enable_ier_and_isr(card, CR_INTR_CREG | CR_INTR_EVENT);
	spin_unlock_irqrestore(&card->irq_lock, flags);

	mutex_unlock(&card->creg_ctrl.reset_lock);
पूर्ण

/* Used क्रम synchronous accesses */
काष्ठा creg_completion अणु
	काष्ठा completion	*cmd_करोne;
	पूर्णांक			st;
	u32			creg_status;
पूर्ण;

अटल व्योम creg_cmd_करोne_cb(काष्ठा rsxx_cardinfo *card,
			     काष्ठा creg_cmd *cmd,
			     पूर्णांक st)
अणु
	काष्ठा creg_completion *cmd_completion;

	cmd_completion = cmd->cb_निजी;
	BUG_ON(!cmd_completion);

	cmd_completion->st = st;
	cmd_completion->creg_status = cmd->status;
	complete(cmd_completion->cmd_करोne);
पूर्ण

अटल पूर्णांक __issue_creg_rw(काष्ठा rsxx_cardinfo *card,
			   अचिन्हित पूर्णांक op,
			   अचिन्हित पूर्णांक addr,
			   अचिन्हित पूर्णांक cnt8,
			   व्योम *buf,
			   पूर्णांक stream,
			   अचिन्हित पूर्णांक *hw_stat)
अणु
	DECLARE_COMPLETION_ONSTACK(cmd_करोne);
	काष्ठा creg_completion completion;
	अचिन्हित दीर्घ समयout;
	पूर्णांक st;

	completion.cmd_करोne = &cmd_करोne;
	completion.st = 0;
	completion.creg_status = 0;

	st = creg_queue_cmd(card, op, addr, cnt8, buf, stream, creg_cmd_करोne_cb,
			    &completion);
	अगर (st)
		वापस st;

	/*
	 * This समयout is necessary क्रम unresponsive hardware. The additional
	 * 20 seconds to used to guarantee that each cregs requests has समय to
	 * complete.
	 */
	समयout = msecs_to_jअगरfies(CREG_TIMEOUT_MSEC *
				   card->creg_ctrl.q_depth + 20000);

	/*
	 * The creg पूर्णांकerface is guaranteed to complete. It has a समयout
	 * mechanism that will kick in अगर hardware करोes not respond.
	 */
	st = रुको_क्रम_completion_समयout(completion.cmd_करोne, समयout);
	अगर (st == 0) अणु
		/*
		 * This is really bad, because the kernel समयr did not
		 * expire and notअगरy us of a समयout!
		 */
		dev_crit(CARD_TO_DEV(card),
			"cregs timer failed\n");
		creg_reset(card);
		वापस -EIO;
	पूर्ण

	*hw_stat = completion.creg_status;

	अगर (completion.st) अणु
		/*
		* This पढ़ो is needed to verअगरy that there has not been any
		* extreme errors that might have occurred, i.e. EEH. The
		* function ioग_लिखो32 will not detect EEH errors, so it is
		* necessary that we recover अगर such an error is the reason
		* क्रम the समयout. This is a dummy पढ़ो.
		*/
		ioपढ़ो32(card->regmap + SCRATCH);

		dev_warn(CARD_TO_DEV(card),
			"creg command failed(%d x%08x)\n",
			completion.st, addr);
		वापस completion.st;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक issue_creg_rw(काष्ठा rsxx_cardinfo *card,
			 u32 addr,
			 अचिन्हित पूर्णांक size8,
			 व्योम *data,
			 पूर्णांक stream,
			 पूर्णांक पढ़ो)
अणु
	अचिन्हित पूर्णांक hw_stat;
	अचिन्हित पूर्णांक xfer;
	अचिन्हित पूर्णांक op;
	पूर्णांक st;

	op = पढ़ो ? CREG_OP_READ : CREG_OP_WRITE;

	करो अणु
		xfer = min_t(अचिन्हित पूर्णांक, size8, MAX_CREG_DATA8);

		st = __issue_creg_rw(card, op, addr, xfer,
				     data, stream, &hw_stat);
		अगर (st)
			वापस st;

		data   = (अक्षर *)data + xfer;
		addr  += xfer;
		size8 -= xfer;
	पूर्ण जबतक (size8);

	वापस 0;
पूर्ण

/* ---------------------------- Public API ---------------------------------- */
पूर्णांक rsxx_creg_ग_लिखो(काष्ठा rsxx_cardinfo *card,
			u32 addr,
			अचिन्हित पूर्णांक size8,
			व्योम *data,
			पूर्णांक byte_stream)
अणु
	वापस issue_creg_rw(card, addr, size8, data, byte_stream, 0);
पूर्ण

पूर्णांक rsxx_creg_पढ़ो(काष्ठा rsxx_cardinfo *card,
		       u32 addr,
		       अचिन्हित पूर्णांक size8,
		       व्योम *data,
		       पूर्णांक byte_stream)
अणु
	वापस issue_creg_rw(card, addr, size8, data, byte_stream, 1);
पूर्ण

पूर्णांक rsxx_get_card_state(काष्ठा rsxx_cardinfo *card, अचिन्हित पूर्णांक *state)
अणु
	वापस rsxx_creg_पढ़ो(card, CREG_ADD_CARD_STATE,
				  माप(*state), state, 0);
पूर्ण

पूर्णांक rsxx_get_card_size8(काष्ठा rsxx_cardinfo *card, u64 *size8)
अणु
	अचिन्हित पूर्णांक size;
	पूर्णांक st;

	st = rsxx_creg_पढ़ो(card, CREG_ADD_CARD_SIZE,
				माप(size), &size, 0);
	अगर (st)
		वापस st;

	*size8 = (u64)size * RSXX_HW_BLK_SIZE;
	वापस 0;
पूर्ण

पूर्णांक rsxx_get_num_tarमाला_लो(काष्ठा rsxx_cardinfo *card,
			     अचिन्हित पूर्णांक *n_tarमाला_लो)
अणु
	वापस rsxx_creg_पढ़ो(card, CREG_ADD_NUM_TARGETS,
				  माप(*n_tarमाला_लो), n_tarमाला_लो, 0);
पूर्ण

पूर्णांक rsxx_get_card_capabilities(काष्ठा rsxx_cardinfo *card,
				   u32 *capabilities)
अणु
	वापस rsxx_creg_पढ़ो(card, CREG_ADD_CAPABILITIES,
				  माप(*capabilities), capabilities, 0);
पूर्ण

पूर्णांक rsxx_issue_card_cmd(काष्ठा rsxx_cardinfo *card, u32 cmd)
अणु
	वापस rsxx_creg_ग_लिखो(card, CREG_ADD_CARD_CMD,
				   माप(cmd), &cmd, 0);
पूर्ण


/*----------------- HW Log Functions -------------------*/
अटल व्योम hw_log_msg(काष्ठा rsxx_cardinfo *card, स्थिर अक्षर *str, पूर्णांक len)
अणु
	अटल अक्षर level;

	/*
	 * New messages start with "<#>", where # is the log level. Messages
	 * that extend past the log buffer will use the previous level
	 */
	अगर ((len > 3) && (str[0] == '<') && (str[2] == '>')) अणु
		level = str[1];
		str += 3; /* Skip past the log level. */
		len -= 3;
	पूर्ण

	चयन (level) अणु
	हाल '0':
		dev_emerg(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '1':
		dev_alert(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '2':
		dev_crit(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '3':
		dev_err(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '4':
		dev_warn(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '5':
		dev_notice(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '6':
		dev_info(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	हाल '7':
		dev_dbg(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	शेष:
		dev_info(CARD_TO_DEV(card), "HW: %.*s", len, str);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * The subम_नकलन function copies the src string (which includes the
 * terminating '\0' अक्षरacter), up to the count पूर्णांकo the dest poपूर्णांकer.
 * Returns the number of bytes copied to dest.
 */
अटल पूर्णांक subम_नकलन(अक्षर *dest, स्थिर अक्षर *src, पूर्णांक count)
अणु
	पूर्णांक max_cnt = count;

	जबतक (count) अणु
		count--;
		*dest = *src;
		अगर (*dest == '\0')
			अवरोध;
		src++;
		dest++;
	पूर्ण
	वापस max_cnt - count;
पूर्ण


अटल व्योम पढ़ो_hw_log_करोne(काष्ठा rsxx_cardinfo *card,
			     काष्ठा creg_cmd *cmd,
			     पूर्णांक st)
अणु
	अक्षर *buf;
	अक्षर *log_str;
	पूर्णांक cnt;
	पूर्णांक len;
	पूर्णांक off;

	buf = cmd->buf;
	off = 0;

	/* Failed getting the log message */
	अगर (st)
		वापस;

	जबतक (off < cmd->cnt8) अणु
		log_str = &card->log.buf[card->log.buf_len];
		cnt = min(cmd->cnt8 - off, LOG_BUF_SIZE8 - card->log.buf_len);
		len = subम_नकलन(log_str, &buf[off], cnt);

		off += len;
		card->log.buf_len += len;

		/*
		 * Flush the log अगर we've hit the end of a message or if we've
		 * run out of buffer space.
		 */
		अगर ((log_str[len - 1] == '\0')  ||
		    (card->log.buf_len == LOG_BUF_SIZE8)) अणु
			अगर (card->log.buf_len != 1) /* Don't log blank lines. */
				hw_log_msg(card, card->log.buf,
					   card->log.buf_len);
			card->log.buf_len = 0;
		पूर्ण

	पूर्ण

	अगर (cmd->status & CREG_STAT_LOG_PENDING)
		rsxx_पढ़ो_hw_log(card);
पूर्ण

पूर्णांक rsxx_पढ़ो_hw_log(काष्ठा rsxx_cardinfo *card)
अणु
	पूर्णांक st;

	st = creg_queue_cmd(card, CREG_OP_READ, CREG_ADD_LOG,
			    माप(card->log.पंचांगp), card->log.पंचांगp,
			    1, पढ़ो_hw_log_करोne, शून्य);
	अगर (st)
		dev_err(CARD_TO_DEV(card),
			"Failed getting log text\n");

	वापस st;
पूर्ण

/*-------------- IOCTL REG Access ------------------*/
अटल पूर्णांक issue_reg_cmd(काष्ठा rsxx_cardinfo *card,
			 काष्ठा rsxx_reg_access *cmd,
			 पूर्णांक पढ़ो)
अणु
	अचिन्हित पूर्णांक op = पढ़ो ? CREG_OP_READ : CREG_OP_WRITE;

	वापस __issue_creg_rw(card, op, cmd->addr, cmd->cnt, cmd->data,
			       cmd->stream, &cmd->stat);
पूर्ण

पूर्णांक rsxx_reg_access(काष्ठा rsxx_cardinfo *card,
			काष्ठा rsxx_reg_access __user *ucmd,
			पूर्णांक पढ़ो)
अणु
	काष्ठा rsxx_reg_access cmd;
	पूर्णांक st;

	st = copy_from_user(&cmd, ucmd, माप(cmd));
	अगर (st)
		वापस -EFAULT;

	अगर (cmd.cnt > RSXX_MAX_REG_CNT)
		वापस -EFAULT;

	st = issue_reg_cmd(card, &cmd, पढ़ो);
	अगर (st)
		वापस st;

	st = put_user(cmd.stat, &ucmd->stat);
	अगर (st)
		वापस -EFAULT;

	अगर (पढ़ो) अणु
		st = copy_to_user(ucmd->data, cmd.data, cmd.cnt);
		अगर (st)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

व्योम rsxx_eeh_save_issued_creg(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा creg_cmd *cmd = शून्य;

	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = शून्य;

	अगर (cmd) अणु
		del_समयr_sync(&card->creg_ctrl.cmd_समयr);

		spin_lock_bh(&card->creg_ctrl.lock);
		list_add(&cmd->list, &card->creg_ctrl.queue);
		card->creg_ctrl.q_depth++;
		card->creg_ctrl.active = 0;
		spin_unlock_bh(&card->creg_ctrl.lock);
	पूर्ण
पूर्ण

व्योम rsxx_kick_creg_queue(काष्ठा rsxx_cardinfo *card)
अणु
	spin_lock_bh(&card->creg_ctrl.lock);
	अगर (!list_empty(&card->creg_ctrl.queue))
		creg_kick_queue(card);
	spin_unlock_bh(&card->creg_ctrl.lock);
पूर्ण

/*------------ Initialization & Setup --------------*/
पूर्णांक rsxx_creg_setup(काष्ठा rsxx_cardinfo *card)
अणु
	card->creg_ctrl.active_cmd = शून्य;

	card->creg_ctrl.creg_wq =
			create_singlethपढ़ो_workqueue(DRIVER_NAME"_creg");
	अगर (!card->creg_ctrl.creg_wq)
		वापस -ENOMEM;

	INIT_WORK(&card->creg_ctrl.करोne_work, creg_cmd_करोne);
	mutex_init(&card->creg_ctrl.reset_lock);
	INIT_LIST_HEAD(&card->creg_ctrl.queue);
	spin_lock_init(&card->creg_ctrl.lock);
	समयr_setup(&card->creg_ctrl.cmd_समयr, creg_cmd_समयd_out, 0);

	वापस 0;
पूर्ण

व्योम rsxx_creg_destroy(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा creg_cmd *cmd;
	काष्ठा creg_cmd *पंचांगp;
	पूर्णांक cnt = 0;

	/* Cancel outstanding commands */
	spin_lock_bh(&card->creg_ctrl.lock);
	list_क्रम_each_entry_safe(cmd, पंचांगp, &card->creg_ctrl.queue, list) अणु
		list_del(&cmd->list);
		अगर (cmd->cb)
			cmd->cb(card, cmd, -ECANCELED);
		kmem_cache_मुक्त(creg_cmd_pool, cmd);
		cnt++;
	पूर्ण

	अगर (cnt)
		dev_info(CARD_TO_DEV(card),
			"Canceled %d queue creg commands\n", cnt);

	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = शून्य;
	अगर (cmd) अणु
		अगर (समयr_pending(&card->creg_ctrl.cmd_समयr))
			del_समयr_sync(&card->creg_ctrl.cmd_समयr);

		अगर (cmd->cb)
			cmd->cb(card, cmd, -ECANCELED);
		dev_info(CARD_TO_DEV(card),
			"Canceled active creg command\n");
		kmem_cache_मुक्त(creg_cmd_pool, cmd);
	पूर्ण
	spin_unlock_bh(&card->creg_ctrl.lock);

	cancel_work_sync(&card->creg_ctrl.करोne_work);
पूर्ण


पूर्णांक rsxx_creg_init(व्योम)
अणु
	creg_cmd_pool = KMEM_CACHE(creg_cmd, SLAB_HWCACHE_ALIGN);
	अगर (!creg_cmd_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम rsxx_creg_cleanup(व्योम)
अणु
	kmem_cache_destroy(creg_cmd_pool);
पूर्ण
