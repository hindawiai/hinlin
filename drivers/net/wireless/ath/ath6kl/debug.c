<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "core.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>

#समावेश "debug.h"
#समावेश "target.h"

काष्ठा ath6kl_fwlog_slot अणु
	__le32 बारtamp;
	__le32 length;

	/* max ATH6KL_FWLOG_PAYLOAD_SIZE bytes */
	u8 payload[];
पूर्ण;

#घोषणा ATH6KL_FWLOG_MAX_ENTRIES 20

#घोषणा ATH6KL_FWLOG_VALID_MASK 0x1ffff

व्योम ath6kl_prपूर्णांकk(स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%sath6kl: %pV", level, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath6kl_prपूर्णांकk);

व्योम ath6kl_info(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	ath6kl_prपूर्णांकk(KERN_INFO, "%pV", &vaf);
	trace_ath6kl_log_info(&vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath6kl_info);

व्योम ath6kl_err(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	ath6kl_prपूर्णांकk(KERN_ERR, "%pV", &vaf);
	trace_ath6kl_log_err(&vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath6kl_err);

व्योम ath6kl_warn(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	ath6kl_prपूर्णांकk(KERN_WARNING, "%pV", &vaf);
	trace_ath6kl_log_warn(&vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath6kl_warn);

पूर्णांक ath6kl_पढ़ो_tgt_stats(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर)
अणु
	दीर्घ left;

	अगर (करोwn_पूर्णांकerruptible(&ar->sem))
		वापस -EBUSY;

	set_bit(STATS_UPDATE_PEND, &vअगर->flags);

	अगर (ath6kl_wmi_get_stats_cmd(ar->wmi, 0)) अणु
		up(&ar->sem);
		वापस -EIO;
	पूर्ण

	left = रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
						!test_bit(STATS_UPDATE_PEND,
						&vअगर->flags), WMI_TIMEOUT);

	up(&ar->sem);

	अगर (left <= 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath6kl_पढ़ो_tgt_stats);

#अगर_घोषित CONFIG_ATH6KL_DEBUG

व्योम ath6kl_dbg(क्रमागत ATH6K_DEBUG_MASK mask, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (debug_mask & mask)
		ath6kl_prपूर्णांकk(KERN_DEBUG, "%pV", &vaf);

	trace_ath6kl_log_dbg(mask, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath6kl_dbg);

व्योम ath6kl_dbg_dump(क्रमागत ATH6K_DEBUG_MASK mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len)
अणु
	अगर (debug_mask & mask) अणु
		अगर (msg)
			ath6kl_dbg(mask, "%s\n", msg);

		prपूर्णांक_hex_dump_bytes(prefix, DUMP_PREFIX_OFFSET, buf, len);
	पूर्ण

	/* tracing code करोesn't like null strings :/ */
	trace_ath6kl_log_dbg_dump(msg ? msg : "", prefix ? prefix : "",
				  buf, len);
पूर्ण
EXPORT_SYMBOL(ath6kl_dbg_dump);

#घोषणा REG_OUTPUT_LEN_PER_LINE	25
#घोषणा REGTYPE_STR_LEN		100

काष्ठा ath6kl_diag_reg_info अणु
	u32 reg_start;
	u32 reg_end;
	स्थिर अक्षर *reg_info;
पूर्ण;

अटल स्थिर काष्ठा ath6kl_diag_reg_info diag_reg[] = अणु
	अणु 0x20000, 0x200fc, "General DMA and Rx registers" पूर्ण,
	अणु 0x28000, 0x28900, "MAC PCU register & keycache" पूर्ण,
	अणु 0x20800, 0x20a40, "QCU" पूर्ण,
	अणु 0x21000, 0x212f0, "DCU" पूर्ण,
	अणु 0x4000,  0x42e4, "RTC" पूर्ण,
	अणु 0x540000, 0x540000 + (256 * 1024), "RAM" पूर्ण,
	अणु 0x29800, 0x2B210, "Base Band" पूर्ण,
	अणु 0x1C000, 0x1C748, "Analog" पूर्ण,
पूर्ण;

व्योम ath6kl_dump_रेजिस्टरs(काष्ठा ath6kl_device *dev,
			   काष्ठा ath6kl_irq_proc_रेजिस्टरs *irq_proc_reg,
			   काष्ठा ath6kl_irq_enable_reg *irq_enable_reg)
अणु
	ath6kl_dbg(ATH6KL_DBG_IRQ, ("<------- Register Table -------->\n"));

	अगर (irq_proc_reg != शून्य) अणु
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Host Int status:           0x%x\n",
			   irq_proc_reg->host_पूर्णांक_status);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "CPU Int status:            0x%x\n",
			   irq_proc_reg->cpu_पूर्णांक_status);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Error Int status:          0x%x\n",
			   irq_proc_reg->error_पूर्णांक_status);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Counter Int status:        0x%x\n",
			   irq_proc_reg->counter_पूर्णांक_status);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Mbox Frame:                0x%x\n",
			   irq_proc_reg->mbox_frame);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Rx Lookahead Valid:        0x%x\n",
			   irq_proc_reg->rx_lkahd_valid);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Rx Lookahead 0:            0x%x\n",
			   irq_proc_reg->rx_lkahd[0]);
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Rx Lookahead 1:            0x%x\n",
			   irq_proc_reg->rx_lkahd[1]);

		अगर (dev->ar->mbox_info.gmbox_addr != 0) अणु
			/*
			 * If the target supports GMBOX hardware, dump some
			 * additional state.
			 */
			ath6kl_dbg(ATH6KL_DBG_IRQ,
				   "GMBOX Host Int status 2:   0x%x\n",
				   irq_proc_reg->host_पूर्णांक_status2);
			ath6kl_dbg(ATH6KL_DBG_IRQ,
				   "GMBOX RX Avail:            0x%x\n",
				   irq_proc_reg->gmbox_rx_avail);
			ath6kl_dbg(ATH6KL_DBG_IRQ,
				   "GMBOX lookahead alias 0:   0x%x\n",
				   irq_proc_reg->rx_gmbox_lkahd_alias[0]);
			ath6kl_dbg(ATH6KL_DBG_IRQ,
				   "GMBOX lookahead alias 1:   0x%x\n",
				   irq_proc_reg->rx_gmbox_lkahd_alias[1]);
		पूर्ण
	पूर्ण

	अगर (irq_enable_reg != शून्य) अणु
		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "Int status Enable:         0x%x\n",
			   irq_enable_reg->पूर्णांक_status_en);
		ath6kl_dbg(ATH6KL_DBG_IRQ, "Counter Int status Enable: 0x%x\n",
			   irq_enable_reg->cntr_पूर्णांक_status_en);
	पूर्ण
	ath6kl_dbg(ATH6KL_DBG_IRQ, "<------------------------------->\n");
पूर्ण

अटल व्योम dump_cred_dist(काष्ठा htc_endpoपूर्णांक_credit_dist *ep_dist)
अणु
	ath6kl_dbg(ATH6KL_DBG_CREDIT,
		   "--- endpoint: %d  svc_id: 0x%X ---\n",
		   ep_dist->endpoपूर्णांक, ep_dist->svc_id);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " dist_flags     : 0x%X\n",
		   ep_dist->dist_flags);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_norm      : %d\n",
		   ep_dist->cred_norm);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_min       : %d\n",
		   ep_dist->cred_min);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " credits        : %d\n",
		   ep_dist->credits);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_assngd    : %d\n",
		   ep_dist->cred_assngd);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " seek_cred      : %d\n",
		   ep_dist->seek_cred);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_sz        : %d\n",
		   ep_dist->cred_sz);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_per_msg   : %d\n",
		   ep_dist->cred_per_msg);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " cred_to_dist   : %d\n",
		   ep_dist->cred_to_dist);
	ath6kl_dbg(ATH6KL_DBG_CREDIT, " txq_depth      : %d\n",
		   get_queue_depth(&ep_dist->htc_ep->txq));
	ath6kl_dbg(ATH6KL_DBG_CREDIT,
		   "----------------------------------\n");
पूर्ण

/* FIXME: move to htc.c */
व्योम dump_cred_dist_stats(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक_credit_dist *ep_list;

	list_क्रम_each_entry(ep_list, &target->cred_dist_list, list)
		dump_cred_dist(ep_list);

	ath6kl_dbg(ATH6KL_DBG_CREDIT,
		   "credit distribution total %d free %d\n",
		   target->credit_info->total_avail_credits,
		   target->credit_info->cur_मुक्त_credits);
पूर्ण

व्योम ath6kl_debug_war(काष्ठा ath6kl *ar, क्रमागत ath6kl_war war)
अणु
	चयन (war) अणु
	हाल ATH6KL_WAR_INVALID_RATE:
		ar->debug.war_stats.invalid_rate++;
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_war_stats(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, buf_len = 1500;
	sमाप_प्रकार ret_cnt;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "Workaround stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n\n",
			 "=================");
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10u\n",
			 "Invalid rates", ar->debug.war_stats.invalid_rate);

	अगर (WARN_ON(len > buf_len))
		len = buf_len;

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_war_stats = अणु
	.पढ़ो = पढ़ो_file_war_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath6kl_debug_fwlog_event(काष्ठा ath6kl *ar, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ath6kl_fwlog_slot *slot;
	काष्ठा sk_buff *skb;
	माप_प्रकार slot_len;

	अगर (WARN_ON(len > ATH6KL_FWLOG_PAYLOAD_SIZE))
		वापस;

	slot_len = माप(*slot) + ATH6KL_FWLOG_PAYLOAD_SIZE;

	skb = alloc_skb(slot_len, GFP_KERNEL);
	अगर (!skb)
		वापस;

	slot = skb_put(skb, slot_len);
	slot->बारtamp = cpu_to_le32(jअगरfies);
	slot->length = cpu_to_le32(len);
	स_नकल(slot->payload, buf, len);

	/* Need to pad each record to fixed length ATH6KL_FWLOG_PAYLOAD_SIZE */
	स_रखो(slot->payload + len, 0, ATH6KL_FWLOG_PAYLOAD_SIZE - len);

	spin_lock(&ar->debug.fwlog_queue.lock);

	__skb_queue_tail(&ar->debug.fwlog_queue, skb);
	complete(&ar->debug.fwlog_completion);

	/* drop oldest entries */
	जबतक (skb_queue_len(&ar->debug.fwlog_queue) >
	       ATH6KL_FWLOG_MAX_ENTRIES) अणु
		skb = __skb_dequeue(&ar->debug.fwlog_queue);
		kमुक्त_skb(skb);
	पूर्ण

	spin_unlock(&ar->debug.fwlog_queue.lock);

	वापस;
पूर्ण

अटल पूर्णांक ath6kl_fwlog_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath6kl *ar = inode->i_निजी;

	अगर (ar->debug.fwlog_खोलो)
		वापस -EBUSY;

	ar->debug.fwlog_खोलो = true;

	file->निजी_data = inode->i_निजी;
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_fwlog_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath6kl *ar = inode->i_निजी;

	ar->debug.fwlog_खोलो = false;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath6kl_fwlog_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार ret_cnt;
	माप_प्रकार len = 0;
	अक्षर *buf;

	buf = vदो_स्मृति(count);
	अगर (!buf)
		वापस -ENOMEM;

	/* पढ़ो undelivered logs from firmware */
	ath6kl_पढ़ो_fwlogs(ar);

	spin_lock(&ar->debug.fwlog_queue.lock);

	जबतक ((skb = __skb_dequeue(&ar->debug.fwlog_queue))) अणु
		अगर (skb->len > count - len) अणु
			/* not enough space, put skb back and leave */
			__skb_queue_head(&ar->debug.fwlog_queue, skb);
			अवरोध;
		पूर्ण


		स_नकल(buf + len, skb->data, skb->len);
		len += skb->len;

		kमुक्त_skb(skb);
	पूर्ण

	spin_unlock(&ar->debug.fwlog_queue.lock);

	/* FIXME: what to करो अगर len == 0? */

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	vमुक्त(buf);

	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fwlog = अणु
	.खोलो = ath6kl_fwlog_खोलो,
	.release = ath6kl_fwlog_release,
	.पढ़ो = ath6kl_fwlog_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_fwlog_block_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count,
				       loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा sk_buff *skb;
	sमाप_प्रकार ret_cnt;
	माप_प्रकार len = 0, not_copied;
	अक्षर *buf;
	पूर्णांक ret;

	buf = vदो_स्मृति(count);
	अगर (!buf)
		वापस -ENOMEM;

	spin_lock(&ar->debug.fwlog_queue.lock);

	अगर (skb_queue_len(&ar->debug.fwlog_queue) == 0) अणु
		/* we must init under queue lock */
		init_completion(&ar->debug.fwlog_completion);

		spin_unlock(&ar->debug.fwlog_queue.lock);

		ret = रुको_क्रम_completion_पूर्णांकerruptible(
			&ar->debug.fwlog_completion);
		अगर (ret == -ERESTARTSYS) अणु
			vमुक्त(buf);
			वापस ret;
		पूर्ण

		spin_lock(&ar->debug.fwlog_queue.lock);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&ar->debug.fwlog_queue))) अणु
		अगर (skb->len > count - len) अणु
			/* not enough space, put skb back and leave */
			__skb_queue_head(&ar->debug.fwlog_queue, skb);
			अवरोध;
		पूर्ण


		स_नकल(buf + len, skb->data, skb->len);
		len += skb->len;

		kमुक्त_skb(skb);
	पूर्ण

	spin_unlock(&ar->debug.fwlog_queue.lock);

	/* FIXME: what to करो अगर len == 0? */

	not_copied = copy_to_user(user_buf, buf, len);
	अगर (not_copied != 0) अणु
		ret_cnt = -EFAULT;
		जाओ out;
	पूर्ण

	*ppos = *ppos + len;

	ret_cnt = len;

out:
	vमुक्त(buf);

	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fwlog_block = अणु
	.खोलो = ath6kl_fwlog_खोलो,
	.release = ath6kl_fwlog_release,
	.पढ़ो = ath6kl_fwlog_block_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_fwlog_mask_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक len;

	len = snम_लिखो(buf, माप(buf), "0x%x\n", ar->debug.fwlog_mask);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath6kl_fwlog_mask_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;

	ret = kstrtou32_from_user(user_buf, count, 0, &ar->debug.fwlog_mask);
	अगर (ret)
		वापस ret;

	ret = ath6kl_wmi_config_debug_module_cmd(ar->wmi,
						 ATH6KL_FWLOG_VALID_MASK,
						 ar->debug.fwlog_mask);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fwlog_mask = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath6kl_fwlog_mask_पढ़ो,
	.ग_लिखो = ath6kl_fwlog_mask_ग_लिखो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_tgt_stats(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	काष्ठा target_stats *tgt_stats;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, buf_len = 1500;
	पूर्णांक i;
	sमाप_प्रकार ret_cnt;
	पूर्णांक rv;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rv = ath6kl_पढ़ो_tgt_stats(ar, vअगर);
	अगर (rv < 0) अणु
		kमुक्त(buf);
		वापस rv;
	पूर्ण

	tgt_stats = &vअगर->target_stats;

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "Target Tx stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n\n",
			 "=================");
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Ucast packets", tgt_stats->tx_ucast_pkt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Bcast packets", tgt_stats->tx_bcast_pkt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Ucast byte", tgt_stats->tx_ucast_byte);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Bcast byte", tgt_stats->tx_bcast_byte);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Rts success cnt", tgt_stats->tx_rts_success_cnt);
	क्रम (i = 0; i < 4; i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				 "%18s %d %10llu\n", "PER on ac",
				 i, tgt_stats->tx_pkt_per_ac[i]);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Error", tgt_stats->tx_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Fail count", tgt_stats->tx_fail_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Retry count", tgt_stats->tx_retry_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Multi retry cnt", tgt_stats->tx_mult_retry_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Rts fail cnt", tgt_stats->tx_rts_fail_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%25s %10llu\n\n",
			 "TKIP counter measure used",
			 tgt_stats->tkip_cnter_measures_invoked);

	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "Target Rx stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "=================");

	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Ucast packets", tgt_stats->rx_ucast_pkt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10d\n",
			 "Ucast Rate", tgt_stats->rx_ucast_rate);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Bcast packets", tgt_stats->rx_bcast_pkt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Ucast byte", tgt_stats->rx_ucast_byte);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Bcast byte", tgt_stats->rx_bcast_byte);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Fragmented pkt", tgt_stats->rx_frgment_pkt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Error", tgt_stats->rx_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "CRC Err", tgt_stats->rx_crc_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Key cache miss", tgt_stats->rx_key_cache_miss);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Decrypt Err", tgt_stats->rx_decrypt_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Duplicate frame", tgt_stats->rx_dupl_frame);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Tkip Mic failure", tgt_stats->tkip_local_mic_fail);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "TKIP format err", tgt_stats->tkip_fmt_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "CCMP format Err", tgt_stats->ccmp_fmt_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n\n",
			 "CCMP Replay Err", tgt_stats->ccmp_replays);

	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "Misc Target stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%25s\n",
			 "=================");
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Beacon Miss count", tgt_stats->cs_bmiss_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Num Connects", tgt_stats->cs_connect_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10llu\n",
			 "Num disconnects", tgt_stats->cs_discon_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10d\n",
			 "Beacon avg rssi", tgt_stats->cs_ave_beacon_rssi);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10d\n",
			 "ARP pkt received", tgt_stats->arp_received);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10d\n",
			 "ARP pkt matched", tgt_stats->arp_matched);
	len += scnम_लिखो(buf + len, buf_len - len, "%20s %10d\n",
			 "ARP pkt replied", tgt_stats->arp_replied);

	अगर (len > buf_len)
		len = buf_len;

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tgt_stats = अणु
	.पढ़ो = पढ़ो_file_tgt_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#घोषणा prपूर्णांक_credit_info(fmt_str, ep_list_field)		\
	(len += scnम_लिखो(buf + len, buf_len - len, fmt_str,	\
			 ep_list->ep_list_field))
#घोषणा CREDIT_INFO_DISPLAY_STRING_LEN	200
#घोषणा CREDIT_INFO_LEN	128

अटल sमाप_प्रकार पढ़ो_file_credit_dist_stats(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा htc_target *target = ar->htc_target;
	काष्ठा htc_endpoपूर्णांक_credit_dist *ep_list;
	अक्षर *buf;
	अचिन्हित पूर्णांक buf_len, len = 0;
	sमाप_प्रकार ret_cnt;

	buf_len = CREDIT_INFO_DISPLAY_STRING_LEN +
		  get_queue_depth(&target->cred_dist_list) * CREDIT_INFO_LEN;
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, buf_len - len, "%25s%5d\n",
			 "Total Avail Credits: ",
			 target->credit_info->total_avail_credits);
	len += scnम_लिखो(buf + len, buf_len - len, "%25s%5d\n",
			 "Free credits :",
			 target->credit_info->cur_मुक्त_credits);

	len += scnम_लिखो(buf + len, buf_len - len,
			 " Epid  Flags    Cred_norm  Cred_min  Credits  Cred_assngd"
			 "  Seek_cred  Cred_sz  Cred_per_msg  Cred_to_dist"
			 "  qdepth\n");

	list_क्रम_each_entry(ep_list, &target->cred_dist_list, list) अणु
		prपूर्णांक_credit_info("  %2d", endpoपूर्णांक);
		prपूर्णांक_credit_info("%10x", dist_flags);
		prपूर्णांक_credit_info("%8d", cred_norm);
		prपूर्णांक_credit_info("%9d", cred_min);
		prपूर्णांक_credit_info("%9d", credits);
		prपूर्णांक_credit_info("%10d", cred_assngd);
		prपूर्णांक_credit_info("%13d", seek_cred);
		prपूर्णांक_credit_info("%12d", cred_sz);
		prपूर्णांक_credit_info("%9d", cred_per_msg);
		prपूर्णांक_credit_info("%14d", cred_to_dist);
		len += scnम_लिखो(buf + len, buf_len - len, "%12d\n",
				 get_queue_depth(&ep_list->htc_ep->txq));
	पूर्ण

	अगर (len > buf_len)
		len = buf_len;

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_credit_dist_stats = अणु
	.पढ़ो = पढ़ो_file_credit_dist_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल अचिन्हित पूर्णांक prपूर्णांक_endpoपूर्णांक_stat(काष्ठा htc_target *target, अक्षर *buf,
					अचिन्हित पूर्णांक buf_len, अचिन्हित पूर्णांक len,
					पूर्णांक offset, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	काष्ठा htc_endpoपूर्णांक_stats *ep_st;
	u32 *counter;

	len += scnम_लिखो(buf + len, buf_len - len, "%s:", name);
	क्रम (i = 0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		ep_st = &target->endpoपूर्णांक[i].ep_st;
		counter = ((u32 *) ep_st) + (offset / 4);
		len += scnम_लिखो(buf + len, buf_len - len, " %u", *counter);
	पूर्ण
	len += scnम_लिखो(buf + len, buf_len - len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार ath6kl_endpoपूर्णांक_stats_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा htc_target *target = ar->htc_target;
	अक्षर *buf;
	अचिन्हित पूर्णांक buf_len, len = 0;
	sमाप_प्रकार ret_cnt;

	buf_len = माप(काष्ठा htc_endpoपूर्णांक_stats) / माप(u32) *
		(25 + ENDPOपूर्णांक_उच्च * 11);
	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

#घोषणा EPSTAT(name)							\
	करो अणु								\
		len = prपूर्णांक_endpoपूर्णांक_stat(target, buf, buf_len, len,	\
					  दुरत्व(काष्ठा htc_endpoपूर्णांक_stats, \
						   name),		\
					  #name);			\
	पूर्ण जबतक (0)

	EPSTAT(cred_low_indicate);
	EPSTAT(tx_issued);
	EPSTAT(tx_pkt_bundled);
	EPSTAT(tx_bundles);
	EPSTAT(tx_dropped);
	EPSTAT(tx_cred_rpt);
	EPSTAT(cred_rpt_from_rx);
	EPSTAT(cred_rpt_from_other);
	EPSTAT(cred_rpt_ep0);
	EPSTAT(cred_from_rx);
	EPSTAT(cred_from_other);
	EPSTAT(cred_from_ep0);
	EPSTAT(cred_cosumd);
	EPSTAT(cred_retnd);
	EPSTAT(rx_pkts);
	EPSTAT(rx_lkahds);
	EPSTAT(rx_bundl);
	EPSTAT(rx_bundle_lkahd);
	EPSTAT(rx_bundle_from_hdr);
	EPSTAT(rx_alloc_thresh_hit);
	EPSTAT(rxalloc_thresh_byte);
#अघोषित EPSTAT

	अगर (len > buf_len)
		len = buf_len;

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल sमाप_प्रकार ath6kl_endpoपूर्णांक_stats_ग_लिखो(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा htc_target *target = ar->htc_target;
	पूर्णांक ret, i;
	u32 val;
	काष्ठा htc_endpoपूर्णांक_stats *ep_st;

	ret = kstrtou32_from_user(user_buf, count, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (val == 0) अणु
		क्रम (i = 0; i < ENDPOपूर्णांक_उच्च; i++) अणु
			ep_st = &target->endpoपूर्णांक[i].ep_st;
			स_रखो(ep_st, 0, माप(*ep_st));
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_endpoपूर्णांक_stats = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath6kl_endpoपूर्णांक_stats_पढ़ो,
	.ग_लिखो = ath6kl_endpoपूर्णांक_stats_ग_लिखो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल अचिन्हित दीर्घ ath6kl_get_num_reg(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ n_reg = 0;

	क्रम (i = 0; i < ARRAY_SIZE(diag_reg); i++)
		n_reg = n_reg +
		     (diag_reg[i].reg_end - diag_reg[i].reg_start) / 4 + 1;

	वापस n_reg;
पूर्ण

अटल bool ath6kl_dbg_is_diag_reg_valid(u32 reg_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(diag_reg); i++) अणु
		अगर (reg_addr >= diag_reg[i].reg_start &&
		    reg_addr <= diag_reg[i].reg_end)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल sमाप_प्रकार ath6kl_regपढ़ो_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	u8 buf[50];
	अचिन्हित पूर्णांक len = 0;

	अगर (ar->debug.dbgfs_diag_reg)
		len += scnम_लिखो(buf + len, माप(buf) - len, "0x%x\n",
				ar->debug.dbgfs_diag_reg);
	अन्यथा
		len += scnम_लिखो(buf + len, माप(buf) - len,
				 "All diag registers\n");

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath6kl_regपढ़ो_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अचिन्हित दीर्घ reg_addr;

	अगर (kम_से_अदीर्घ_from_user(user_buf, count, 0, &reg_addr))
		वापस -EINVAL;

	अगर ((reg_addr % 4) != 0)
		वापस -EINVAL;

	अगर (reg_addr && !ath6kl_dbg_is_diag_reg_valid(reg_addr))
		वापस -EINVAL;

	ar->debug.dbgfs_diag_reg = reg_addr;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_diag_reg_पढ़ो = अणु
	.पढ़ो = ath6kl_regपढ़ो_पढ़ो,
	.ग_लिखो = ath6kl_regपढ़ो_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath6kl_regdump_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath6kl *ar = inode->i_निजी;
	u8 *buf;
	अचिन्हित दीर्घ पूर्णांक reg_len;
	अचिन्हित पूर्णांक len = 0, n_reg;
	u32 addr;
	__le32 reg_val;
	पूर्णांक i, status;

	/* Dump all the रेजिस्टरs अगर no रेजिस्टर is specअगरied */
	अगर (!ar->debug.dbgfs_diag_reg)
		n_reg = ath6kl_get_num_reg();
	अन्यथा
		n_reg = 1;

	reg_len = n_reg * REG_OUTPUT_LEN_PER_LINE;
	अगर (n_reg > 1)
		reg_len += REGTYPE_STR_LEN;

	buf = vदो_स्मृति(reg_len);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (n_reg == 1) अणु
		addr = ar->debug.dbgfs_diag_reg;

		status = ath6kl_diag_पढ़ो32(ar,
				TARG_VTOP(ar->target_type, addr),
				(u32 *)&reg_val);
		अगर (status)
			जाओ fail_reg_पढ़ो;

		len += scnम_लिखो(buf + len, reg_len - len,
				 "0x%06x 0x%08x\n", addr, le32_to_cpu(reg_val));
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(diag_reg); i++) अणु
		len += scnम_लिखो(buf + len, reg_len - len,
				"%s\n", diag_reg[i].reg_info);
		क्रम (addr = diag_reg[i].reg_start;
		     addr <= diag_reg[i].reg_end; addr += 4) अणु
			status = ath6kl_diag_पढ़ो32(ar,
					TARG_VTOP(ar->target_type, addr),
					(u32 *)&reg_val);
			अगर (status)
				जाओ fail_reg_पढ़ो;

			len += scnम_लिखो(buf + len, reg_len - len,
					"0x%06x 0x%08x\n",
					addr, le32_to_cpu(reg_val));
		पूर्ण
	पूर्ण

करोne:
	file->निजी_data = buf;
	वापस 0;

fail_reg_पढ़ो:
	ath6kl_warn("Unable to read memory:%u\n", addr);
	vमुक्त(buf);
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार ath6kl_regdump_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	u8 *buf = file->निजी_data;
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
पूर्ण

अटल पूर्णांक ath6kl_regdump_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_reg_dump = अणु
	.खोलो = ath6kl_regdump_खोलो,
	.पढ़ो = ath6kl_regdump_पढ़ो,
	.release = ath6kl_regdump_release,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_lrssi_roam_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अचिन्हित दीर्घ lrssi_roam_threshold;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ_from_user(user_buf, count, 0, &lrssi_roam_threshold))
		वापस -EINVAL;

	ar->lrssi_roam_threshold = lrssi_roam_threshold;

	ret = ath6kl_wmi_set_roam_lrssi_cmd(ar->wmi, ar->lrssi_roam_threshold);

	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार ath6kl_lrssi_roam_पढ़ो(काष्ठा file *file,
				      अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = snम_लिखो(buf, माप(buf), "%u\n", ar->lrssi_roam_threshold);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_lrssi_roam_threshold = अणु
	.पढ़ो = ath6kl_lrssi_roam_पढ़ो,
	.ग_लिखो = ath6kl_lrssi_roam_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_regग_लिखो_पढ़ो(काष्ठा file *file,
				    अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	u8 buf[32];
	अचिन्हित पूर्णांक len = 0;

	len = scnम_लिखो(buf, माप(buf), "Addr: 0x%x Val: 0x%x\n",
			ar->debug.diag_reg_addr_wr, ar->debug.diag_reg_val_wr);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath6kl_regग_लिखो_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर buf[32];
	अक्षर *sptr, *token;
	अचिन्हित पूर्णांक len = 0;
	u32 reg_addr, reg_val;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	sptr = buf;

	token = strsep(&sptr, "=");
	अगर (!token)
		वापस -EINVAL;

	अगर (kstrtou32(token, 0, &reg_addr))
		वापस -EINVAL;

	अगर (!ath6kl_dbg_is_diag_reg_valid(reg_addr))
		वापस -EINVAL;

	अगर (kstrtou32(sptr, 0, &reg_val))
		वापस -EINVAL;

	ar->debug.diag_reg_addr_wr = reg_addr;
	ar->debug.diag_reg_val_wr = reg_val;

	अगर (ath6kl_diag_ग_लिखो32(ar, ar->debug.diag_reg_addr_wr,
				cpu_to_le32(ar->debug.diag_reg_val_wr)))
		वापस -EIO;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_diag_reg_ग_लिखो = अणु
	.पढ़ो = ath6kl_regग_लिखो_पढ़ो,
	.ग_लिखो = ath6kl_regग_लिखो_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक ath6kl_debug_roam_tbl_event(काष्ठा ath6kl *ar, स्थिर व्योम *buf,
				माप_प्रकार len)
अणु
	स्थिर काष्ठा wmi_target_roam_tbl *tbl;
	u16 num_entries;

	अगर (len < माप(*tbl))
		वापस -EINVAL;

	tbl = (स्थिर काष्ठा wmi_target_roam_tbl *) buf;
	num_entries = le16_to_cpu(tbl->num_entries);
	अगर (काष्ठा_size(tbl, info, num_entries) > len)
		वापस -EINVAL;

	अगर (ar->debug.roam_tbl == शून्य ||
	    ar->debug.roam_tbl_len < (अचिन्हित पूर्णांक) len) अणु
		kमुक्त(ar->debug.roam_tbl);
		ar->debug.roam_tbl = kदो_स्मृति(len, GFP_ATOMIC);
		अगर (ar->debug.roam_tbl == शून्य)
			वापस -ENOMEM;
	पूर्ण

	स_नकल(ar->debug.roam_tbl, buf, len);
	ar->debug.roam_tbl_len = len;

	अगर (test_bit(ROAM_TBL_PEND, &ar->flag)) अणु
		clear_bit(ROAM_TBL_PEND, &ar->flag);
		wake_up(&ar->event_wq);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath6kl_roam_table_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;
	दीर्घ left;
	काष्ठा wmi_target_roam_tbl *tbl;
	u16 num_entries, i;
	अक्षर *buf;
	अचिन्हित पूर्णांक len, buf_len;
	sमाप_प्रकार ret_cnt;

	अगर (करोwn_पूर्णांकerruptible(&ar->sem))
		वापस -EBUSY;

	set_bit(ROAM_TBL_PEND, &ar->flag);

	ret = ath6kl_wmi_get_roam_tbl_cmd(ar->wmi);
	अगर (ret) अणु
		up(&ar->sem);
		वापस ret;
	पूर्ण

	left = रुको_event_पूर्णांकerruptible_समयout(
		ar->event_wq, !test_bit(ROAM_TBL_PEND, &ar->flag), WMI_TIMEOUT);
	up(&ar->sem);

	अगर (left <= 0)
		वापस -ETIMEDOUT;

	अगर (ar->debug.roam_tbl == शून्य)
		वापस -ENOMEM;

	tbl = (काष्ठा wmi_target_roam_tbl *) ar->debug.roam_tbl;
	num_entries = le16_to_cpu(tbl->num_entries);

	buf_len = 100 + num_entries * 100;
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;
	len = 0;
	len += scnम_लिखो(buf + len, buf_len - len,
			 "roam_mode=%u\n\n"
			 "# roam_util bssid rssi rssidt last_rssi util bias\n",
			 le16_to_cpu(tbl->roam_mode));

	क्रम (i = 0; i < num_entries; i++) अणु
		काष्ठा wmi_bss_roam_info *info = &tbl->info[i];
		len += scnम_लिखो(buf + len, buf_len - len,
				 "%d %pM %d %d %d %d %d\n",
				 a_sle32_to_cpu(info->roam_util), info->bssid,
				 info->rssi, info->rssidt, info->last_rssi,
				 info->util, info->bias);
	पूर्ण

	अगर (len > buf_len)
		len = buf_len;

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_roam_table = अणु
	.पढ़ो = ath6kl_roam_table_पढ़ो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_क्रमce_roam_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;
	अक्षर buf[20];
	माप_प्रकार len;
	u8 bssid[ETH_ALEN];

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;
	buf[len] = '\0';

	अगर (!mac_pton(buf, bssid))
		वापस -EINVAL;

	ret = ath6kl_wmi_क्रमce_roam_cmd(ar->wmi, bssid);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_क्रमce_roam = अणु
	.ग_लिखो = ath6kl_क्रमce_roam_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_roam_mode_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;
	अक्षर buf[20];
	माप_प्रकार len;
	क्रमागत wmi_roam_mode mode;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;
	buf[len] = '\0';
	अगर (len > 0 && buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	अगर (strहालcmp(buf, "default") == 0)
		mode = WMI_DEFAULT_ROAM_MODE;
	अन्यथा अगर (strहालcmp(buf, "bssbias") == 0)
		mode = WMI_HOST_BIAS_ROAM_MODE;
	अन्यथा अगर (strहालcmp(buf, "lock") == 0)
		mode = WMI_LOCK_BSS_MODE;
	अन्यथा
		वापस -EINVAL;

	ret = ath6kl_wmi_set_roam_mode_cmd(ar->wmi, mode);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_roam_mode = अणु
	.ग_लिखो = ath6kl_roam_mode_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath6kl_debug_set_keepalive(काष्ठा ath6kl *ar, u8 keepalive)
अणु
	ar->debug.keepalive = keepalive;
पूर्ण

अटल sमाप_प्रकार ath6kl_keepalive_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक len;

	len = snम_लिखो(buf, माप(buf), "%u\n", ar->debug.keepalive);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath6kl_keepalive_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8_from_user(user_buf, count, 0, &val);
	अगर (ret)
		वापस ret;

	ret = ath6kl_wmi_set_keepalive_cmd(ar->wmi, 0, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_keepalive = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath6kl_keepalive_पढ़ो,
	.ग_लिखो = ath6kl_keepalive_ग_लिखो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath6kl_debug_set_disconnect_समयout(काष्ठा ath6kl *ar, u8 समयout)
अणु
	ar->debug.disc_समयout = समयout;
पूर्ण

अटल sमाप_प्रकार ath6kl_disconnect_समयout_पढ़ो(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक len;

	len = snम_लिखो(buf, माप(buf), "%u\n", ar->debug.disc_समयout);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath6kl_disconnect_समयout_ग_लिखो(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8_from_user(user_buf, count, 0, &val);
	अगर (ret)
		वापस ret;

	ret = ath6kl_wmi_disस_समयout_cmd(ar->wmi, 0, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_disconnect_समयout = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath6kl_disconnect_समयout_पढ़ो,
	.ग_लिखो = ath6kl_disconnect_समयout_ग_लिखो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_create_qos_ग_लिखो(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	अक्षर buf[200];
	sमाप_प्रकार len;
	अक्षर *sptr, *token;
	काष्ठा wmi_create_pstream_cmd pstream;
	u32 val32;
	u16 val16;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;
	buf[len] = '\0';
	sptr = buf;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.user_pri))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.traffic_direc))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.traffic_class))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.traffic_type))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.voice_psc_cap))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.min_service_पूर्णांक = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.max_service_पूर्णांक = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.inactivity_पूर्णांक = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.suspension_पूर्णांक = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.service_start_समय = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &pstream.tsid))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &val16))
		वापस -EINVAL;
	pstream.nominal_msdu = cpu_to_le16(val16);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &val16))
		वापस -EINVAL;
	pstream.max_msdu = cpu_to_le16(val16);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.min_data_rate = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.mean_data_rate = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.peak_data_rate = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.max_burst_size = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.delay_bound = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.min_phy_rate = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.sba = cpu_to_le32(val32);

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou32(token, 0, &val32))
		वापस -EINVAL;
	pstream.medium_समय = cpu_to_le32(val32);

	pstream.nominal_phy = le32_to_cpu(pstream.min_phy_rate) / 1000000;

	ath6kl_wmi_create_pstream_cmd(ar->wmi, vअगर->fw_vअगर_idx, &pstream);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_create_qos = अणु
	.ग_लिखो = ath6kl_create_qos_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_delete_qos_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	अक्षर buf[100];
	sमाप_प्रकार len;
	अक्षर *sptr, *token;
	u8 traffic_class;
	u8 tsid;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;
	buf[len] = '\0';
	sptr = buf;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &traffic_class))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou8(token, 0, &tsid))
		वापस -EINVAL;

	ath6kl_wmi_delete_pstream_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				      traffic_class, tsid);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_delete_qos = अणु
	.ग_लिखो = ath6kl_delete_qos_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_bgscan_पूर्णांक_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	u16 bgscan_पूर्णांक;
	अक्षर buf[32];
	sमाप_प्रकार len;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kstrtou16(buf, 0, &bgscan_पूर्णांक))
		वापस -EINVAL;

	अगर (bgscan_पूर्णांक == 0)
		bgscan_पूर्णांक = 0xffff;

	vअगर->bg_scan_period = bgscan_पूर्णांक;

	ath6kl_wmi_scanparams_cmd(ar->wmi, 0, 0, 0, bgscan_पूर्णांक, 0, 0, 0, 3,
				  0, 0, 0);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_bgscan_पूर्णांक = अणु
	.ग_लिखो = ath6kl_bgscan_पूर्णांक_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_listen_पूर्णांक_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	u16 listen_पूर्णांकerval;
	अक्षर buf[32];
	sमाप_प्रकार len;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kstrtou16(buf, 0, &listen_पूर्णांकerval))
		वापस -EINVAL;

	अगर ((listen_पूर्णांकerval < 15) || (listen_पूर्णांकerval > 3000))
		वापस -EINVAL;

	vअगर->listen_पूर्णांकvl_t = listen_पूर्णांकerval;
	ath6kl_wmi_listenपूर्णांकerval_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				      vअगर->listen_पूर्णांकvl_t, 0);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ath6kl_listen_पूर्णांक_पढ़ो(काष्ठा file *file,
				      अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	काष्ठा ath6kl_vअगर *vअगर;
	अक्षर buf[32];
	पूर्णांक len;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	len = scnम_लिखो(buf, माप(buf), "%u\n", vअगर->listen_पूर्णांकvl_t);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_listen_पूर्णांक = अणु
	.पढ़ो = ath6kl_listen_पूर्णांक_पढ़ो,
	.ग_लिखो = ath6kl_listen_पूर्णांक_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath6kl_घातer_params_ग_लिखो(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath6kl *ar = file->निजी_data;
	u8 buf[100];
	अचिन्हित पूर्णांक len = 0;
	अक्षर *sptr, *token;
	u16 idle_period, ps_poll_num, dtim,
		tx_wakeup, num_tx;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;
	buf[len] = '\0';
	sptr = buf;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &idle_period))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &ps_poll_num))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &dtim))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &tx_wakeup))
		वापस -EINVAL;

	token = strsep(&sptr, " ");
	अगर (!token)
		वापस -EINVAL;
	अगर (kstrtou16(token, 0, &num_tx))
		वापस -EINVAL;

	ath6kl_wmi_pmparams_cmd(ar->wmi, 0, idle_period, ps_poll_num,
				dtim, tx_wakeup, num_tx, 0);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_घातer_params = अणु
	.ग_लिखो = ath6kl_घातer_params_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath6kl_debug_init(काष्ठा ath6kl *ar)
अणु
	skb_queue_head_init(&ar->debug.fwlog_queue);
	init_completion(&ar->debug.fwlog_completion);

	/*
	 * Actually we are lying here but करोn't know how to पढ़ो the mask
	 * value from the firmware.
	 */
	ar->debug.fwlog_mask = 0;
पूर्ण

/*
 * Initialisation needs to happen in two stages as fwlog events can come
 * beक्रमe cfg80211 is initialised, and debugfs depends on cfg80211
 * initialisation.
 */
पूर्णांक ath6kl_debug_init_fs(काष्ठा ath6kl *ar)
अणु
	ar->debugfs_phy = debugfs_create_dir("ath6kl",
					     ar->wiphy->debugfsdir);
	अगर (!ar->debugfs_phy)
		वापस -ENOMEM;

	debugfs_create_file("tgt_stats", 0400, ar->debugfs_phy, ar,
			    &fops_tgt_stats);

	अगर (ar->hअगर_type == ATH6KL_HIF_TYPE_SDIO)
		debugfs_create_file("credit_dist_stats", 0400,
				    ar->debugfs_phy, ar,
				    &fops_credit_dist_stats);

	debugfs_create_file("endpoint_stats", 0600,
			    ar->debugfs_phy, ar, &fops_endpoपूर्णांक_stats);

	debugfs_create_file("fwlog", 0400, ar->debugfs_phy, ar, &fops_fwlog);

	debugfs_create_file("fwlog_block", 0400, ar->debugfs_phy, ar,
			    &fops_fwlog_block);

	debugfs_create_file("fwlog_mask", 0600, ar->debugfs_phy,
			    ar, &fops_fwlog_mask);

	debugfs_create_file("reg_addr", 0600, ar->debugfs_phy, ar,
			    &fops_diag_reg_पढ़ो);

	debugfs_create_file("reg_dump", 0400, ar->debugfs_phy, ar,
			    &fops_reg_dump);

	debugfs_create_file("lrssi_roam_threshold", 0600,
			    ar->debugfs_phy, ar, &fops_lrssi_roam_threshold);

	debugfs_create_file("reg_write", 0600,
			    ar->debugfs_phy, ar, &fops_diag_reg_ग_लिखो);

	debugfs_create_file("war_stats", 0400, ar->debugfs_phy, ar,
			    &fops_war_stats);

	debugfs_create_file("roam_table", 0400, ar->debugfs_phy, ar,
			    &fops_roam_table);

	debugfs_create_file("force_roam", 0200, ar->debugfs_phy, ar,
			    &fops_क्रमce_roam);

	debugfs_create_file("roam_mode", 0200, ar->debugfs_phy, ar,
			    &fops_roam_mode);

	debugfs_create_file("keepalive", 0600, ar->debugfs_phy, ar,
			    &fops_keepalive);

	debugfs_create_file("disconnect_timeout", 0600,
			    ar->debugfs_phy, ar, &fops_disconnect_समयout);

	debugfs_create_file("create_qos", 0200, ar->debugfs_phy, ar,
			    &fops_create_qos);

	debugfs_create_file("delete_qos", 0200, ar->debugfs_phy, ar,
			    &fops_delete_qos);

	debugfs_create_file("bgscan_interval", 0200,
			    ar->debugfs_phy, ar, &fops_bgscan_पूर्णांक);

	debugfs_create_file("listen_interval", 0600,
			    ar->debugfs_phy, ar, &fops_listen_पूर्णांक);

	debugfs_create_file("power_params", 0200, ar->debugfs_phy, ar,
			    &fops_घातer_params);

	वापस 0;
पूर्ण

व्योम ath6kl_debug_cleanup(काष्ठा ath6kl *ar)
अणु
	skb_queue_purge(&ar->debug.fwlog_queue);
	complete(&ar->debug.fwlog_completion);
	kमुक्त(ar->debug.roam_tbl);
पूर्ण

#पूर्ण_अगर
