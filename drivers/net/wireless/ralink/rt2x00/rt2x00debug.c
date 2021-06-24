<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 debugfs specअगरic routines.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"
#समावेश "rt2x00dump.h"

#घोषणा MAX_LINE_LENGTH 64

काष्ठा rt2x00debug_crypto अणु
	अचिन्हित दीर्घ success;
	अचिन्हित दीर्घ icv_error;
	अचिन्हित दीर्घ mic_error;
	अचिन्हित दीर्घ key_error;
पूर्ण;

काष्ठा rt2x00debug_पूर्णांकf अणु
	/*
	 * Poपूर्णांकer to driver काष्ठाure where
	 * this debugfs entry beदीर्घs to.
	 */
	काष्ठा rt2x00_dev *rt2x00dev;

	/*
	 * Reference to the rt2x00debug काष्ठाure
	 * which can be used to communicate with
	 * the रेजिस्टरs.
	 */
	स्थिर काष्ठा rt2x00debug *debug;

	/*
	 * Debugfs entries क्रम:
	 * - driver folder
	 *   - driver file
	 *   - chipset file
	 *   - device state flags file
	 *   - device capability flags file
	 *   - hardware restart file
	 *   - रेजिस्टर folder
	 *     - csr offset/value files
	 *     - eeprom offset/value files
	 *     - bbp offset/value files
	 *     - rf offset/value files
	 *     - rfcsr offset/value files
	 *   - queue folder
	 *     - frame dump file
	 *     - queue stats file
	 *     - crypto stats file
	 */
	काष्ठा dentry *driver_folder;

	/*
	 * The frame dump file only allows a single पढ़ोer,
	 * so we need to store the current state here.
	 */
	अचिन्हित दीर्घ frame_dump_flags;
#घोषणा FRAME_DUMP_खाता_OPEN	1

	/*
	 * We queue each frame beक्रमe dumping it to the user,
	 * per पढ़ो command we will pass a single skb काष्ठाure
	 * so we should be prepared to queue multiple sk buffers
	 * beक्रमe sending it to userspace.
	 */
	काष्ठा sk_buff_head frame_dump_skbqueue;
	रुको_queue_head_t frame_dump_रुकोqueue;

	/*
	 * HW crypto statistics.
	 * All statistics are stored separately per cipher type.
	 */
	काष्ठा rt2x00debug_crypto crypto_stats[CIPHER_MAX];

	/*
	 * Driver and chipset files will use a data buffer
	 * that has been created in advance. This will simplअगरy
	 * the code since we can use the debugfs functions.
	 */
	काष्ठा debugfs_blob_wrapper driver_blob;
	काष्ठा debugfs_blob_wrapper chipset_blob;

	/*
	 * Requested offset क्रम each रेजिस्टर type.
	 */
	अचिन्हित पूर्णांक offset_csr;
	अचिन्हित पूर्णांक offset_eeprom;
	अचिन्हित पूर्णांक offset_bbp;
	अचिन्हित पूर्णांक offset_rf;
	अचिन्हित पूर्णांक offset_rfcsr;
पूर्ण;

व्योम rt2x00debug_update_crypto(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = rt2x00dev->debugfs_पूर्णांकf;
	क्रमागत cipher cipher = rxdesc->cipher;
	क्रमागत rx_crypto status = rxdesc->cipher_status;

	अगर (cipher == CIPHER_TKIP_NO_MIC)
		cipher = CIPHER_TKIP;
	अगर (cipher == CIPHER_NONE || cipher >= CIPHER_MAX)
		वापस;

	/* Remove CIPHER_NONE index */
	cipher--;

	पूर्णांकf->crypto_stats[cipher].success += (status == RX_CRYPTO_SUCCESS);
	पूर्णांकf->crypto_stats[cipher].icv_error += (status == RX_CRYPTO_FAIL_ICV);
	पूर्णांकf->crypto_stats[cipher].mic_error += (status == RX_CRYPTO_FAIL_MIC);
	पूर्णांकf->crypto_stats[cipher].key_error += (status == RX_CRYPTO_FAIL_KEY);
पूर्ण

व्योम rt2x00debug_dump_frame(काष्ठा rt2x00_dev *rt2x00dev,
			    क्रमागत rt2x00_dump_type type, काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = rt2x00dev->debugfs_पूर्णांकf;
	काष्ठा sk_buff *skb = entry->skb;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(skb);
	काष्ठा sk_buff *skbcopy;
	काष्ठा rt2x00dump_hdr *dump_hdr;
	काष्ठा बारpec64 बारtamp;
	u32 data_len;

	अगर (likely(!test_bit(FRAME_DUMP_खाता_OPEN, &पूर्णांकf->frame_dump_flags)))
		वापस;

	kसमय_get_ts64(&बारtamp);

	अगर (skb_queue_len(&पूर्णांकf->frame_dump_skbqueue) > 20) अणु
		rt2x00_dbg(rt2x00dev, "txrx dump queue length exceeded\n");
		वापस;
	पूर्ण

	data_len = skb->len;
	अगर (skbdesc->flags & SKBDESC_DESC_IN_SKB)
		data_len -= skbdesc->desc_len;

	skbcopy = alloc_skb(माप(*dump_hdr) + skbdesc->desc_len + data_len,
			    GFP_ATOMIC);
	अगर (!skbcopy) अणु
		rt2x00_dbg(rt2x00dev, "Failed to copy skb for dump\n");
		वापस;
	पूर्ण

	dump_hdr = skb_put(skbcopy, माप(*dump_hdr));
	dump_hdr->version = cpu_to_le32(DUMP_HEADER_VERSION);
	dump_hdr->header_length = cpu_to_le32(माप(*dump_hdr));
	dump_hdr->desc_length = cpu_to_le32(skbdesc->desc_len);
	dump_hdr->data_length = cpu_to_le32(data_len);
	dump_hdr->chip_rt = cpu_to_le16(rt2x00dev->chip.rt);
	dump_hdr->chip_rf = cpu_to_le16(rt2x00dev->chip.rf);
	dump_hdr->chip_rev = cpu_to_le16(rt2x00dev->chip.rev);
	dump_hdr->type = cpu_to_le16(type);
	dump_hdr->queue_index = entry->queue->qid;
	dump_hdr->entry_index = entry->entry_idx;
	dump_hdr->बारtamp_sec = cpu_to_le32(बारtamp.tv_sec);
	dump_hdr->बारtamp_usec = cpu_to_le32(बारtamp.tv_nsec /
					       NSEC_PER_USEC);

	अगर (!(skbdesc->flags & SKBDESC_DESC_IN_SKB))
		skb_put_data(skbcopy, skbdesc->desc, skbdesc->desc_len);
	skb_put_data(skbcopy, skb->data, skb->len);

	skb_queue_tail(&पूर्णांकf->frame_dump_skbqueue, skbcopy);
	wake_up_पूर्णांकerruptible(&पूर्णांकf->frame_dump_रुकोqueue);

	/*
	 * Verअगरy that the file has not been बंदd जबतक we were working.
	 */
	अगर (!test_bit(FRAME_DUMP_खाता_OPEN, &पूर्णांकf->frame_dump_flags))
		skb_queue_purge(&पूर्णांकf->frame_dump_skbqueue);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00debug_dump_frame);

अटल पूर्णांक rt2x00debug_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = inode->i_निजी;

	file->निजी_data = inode->i_निजी;

	अगर (!try_module_get(पूर्णांकf->debug->owner))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक rt2x00debug_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;

	module_put(पूर्णांकf->debug->owner);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2x00debug_खोलो_queue_dump(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = inode->i_निजी;
	पूर्णांक retval;

	retval = rt2x00debug_file_खोलो(inode, file);
	अगर (retval)
		वापस retval;

	अगर (test_and_set_bit(FRAME_DUMP_खाता_OPEN, &पूर्णांकf->frame_dump_flags)) अणु
		rt2x00debug_file_release(inode, file);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2x00debug_release_queue_dump(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = inode->i_निजी;

	skb_queue_purge(&पूर्णांकf->frame_dump_skbqueue);

	clear_bit(FRAME_DUMP_खाता_OPEN, &पूर्णांकf->frame_dump_flags);

	वापस rt2x00debug_file_release(inode, file);
पूर्ण

अटल sमाप_प्रकार rt2x00debug_पढ़ो_queue_dump(काष्ठा file *file,
					   अक्षर __user *buf,
					   माप_प्रकार length,
					   loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;
	काष्ठा sk_buff *skb;
	माप_प्रकार status;
	पूर्णांक retval;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EAGAIN;

	retval =
	    रुको_event_पूर्णांकerruptible(पूर्णांकf->frame_dump_रुकोqueue,
				     (skb =
				     skb_dequeue(&पूर्णांकf->frame_dump_skbqueue)));
	अगर (retval)
		वापस retval;

	status = min_t(माप_प्रकार, skb->len, length);
	अगर (copy_to_user(buf, skb->data, status)) अणु
		status = -EFAULT;
		जाओ निकास;
	पूर्ण

	*offset += status;

निकास:
	kमुक्त_skb(skb);

	वापस status;
पूर्ण

अटल __poll_t rt2x00debug_poll_queue_dump(काष्ठा file *file,
						poll_table *रुको)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;

	poll_रुको(file, &पूर्णांकf->frame_dump_रुकोqueue, रुको);

	अगर (!skb_queue_empty(&पूर्णांकf->frame_dump_skbqueue))
		वापस EPOLLOUT | EPOLLWRNORM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_fop_queue_dump = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rt2x00debug_पढ़ो_queue_dump,
	.poll		= rt2x00debug_poll_queue_dump,
	.खोलो		= rt2x00debug_खोलो_queue_dump,
	.release	= rt2x00debug_release_queue_dump,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rt2x00debug_पढ़ो_queue_stats(काष्ठा file *file,
					    अक्षर __user *buf,
					    माप_प्रकार length,
					    loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;
	काष्ठा data_queue *queue;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक lines = 1 + पूर्णांकf->rt2x00dev->data_queues;
	माप_प्रकार size;
	अक्षर *data;
	अक्षर *temp;

	अगर (*offset)
		वापस 0;

	data = kसुस्मृति(lines, MAX_LINE_LENGTH, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	temp = data +
	    प्र_लिखो(data, "qid\tflags\t\tcount\tlimit\tlength\tindex\tdma done\tdone\n");

	queue_क्रम_each(पूर्णांकf->rt2x00dev, queue) अणु
		spin_lock_irqsave(&queue->index_lock, irqflags);

		temp += प्र_लिखो(temp, "%d\t0x%.8x\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
				queue->qid, (अचिन्हित पूर्णांक)queue->flags,
				queue->count, queue->limit, queue->length,
				queue->index[Q_INDEX],
				queue->index[Q_INDEX_DMA_DONE],
				queue->index[Q_INDEX_DONE]);

		spin_unlock_irqrestore(&queue->index_lock, irqflags);
	पूर्ण

	size = म_माप(data);
	size = min(size, length);

	अगर (copy_to_user(buf, data, size)) अणु
		kमुक्त(data);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(data);

	*offset += size;
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_fop_queue_stats = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rt2x00debug_पढ़ो_queue_stats,
	.खोलो		= rt2x00debug_file_खोलो,
	.release	= rt2x00debug_file_release,
	.llseek		= शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_RT2X00_LIB_CRYPTO
अटल sमाप_प्रकार rt2x00debug_पढ़ो_crypto_stats(काष्ठा file *file,
					     अक्षर __user *buf,
					     माप_प्रकार length,
					     loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;
	अटल स्थिर अक्षर * स्थिर name[] = अणु "WEP64", "WEP128", "TKIP", "AES" पूर्ण;
	अक्षर *data;
	अक्षर *temp;
	माप_प्रकार size;
	अचिन्हित पूर्णांक i;

	अगर (*offset)
		वापस 0;

	data = kसुस्मृति(1 + CIPHER_MAX, MAX_LINE_LENGTH, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	temp = data;
	temp += प्र_लिखो(data, "cipher\tsuccess\ticv err\tmic err\tkey err\n");

	क्रम (i = 0; i < CIPHER_MAX; i++) अणु
		temp += प्र_लिखो(temp, "%s\t%lu\t%lu\t%lu\t%lu\n", name[i],
				पूर्णांकf->crypto_stats[i].success,
				पूर्णांकf->crypto_stats[i].icv_error,
				पूर्णांकf->crypto_stats[i].mic_error,
				पूर्णांकf->crypto_stats[i].key_error);
	पूर्ण

	size = म_माप(data);
	size = min(size, length);

	अगर (copy_to_user(buf, data, size)) अणु
		kमुक्त(data);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(data);

	*offset += size;
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_fop_crypto_stats = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rt2x00debug_पढ़ो_crypto_stats,
	.खोलो		= rt2x00debug_file_खोलो,
	.release	= rt2x00debug_file_release,
	.llseek		= शेष_llseek,
पूर्ण;
#पूर्ण_अगर

#घोषणा RT2X00DEBUGFS_OPS_READ(__name, __क्रमmat, __type)	\
अटल sमाप_प्रकार rt2x00debug_पढ़ो_##__name(काष्ठा file *file,	\
					 अक्षर __user *buf,	\
					 माप_प्रकार length,		\
					 loff_t *offset)	\
अणु								\
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;	\
	स्थिर काष्ठा rt2x00debug *debug = पूर्णांकf->debug;		\
	अक्षर line[16];						\
	माप_प्रकार size;						\
	अचिन्हित पूर्णांक index = पूर्णांकf->offset_##__name;		\
	__type value;						\
								\
	अगर (*offset)						\
		वापस 0;					\
								\
	अगर (index >= debug->__name.word_count)			\
		वापस -EINVAL;					\
								\
	index += (debug->__name.word_base /			\
		  debug->__name.word_size);			\
								\
	अगर (debug->__name.flags & RT2X00DEBUGFS_OFFSET)		\
		index *= debug->__name.word_size;		\
								\
	value = debug->__name.पढ़ो(पूर्णांकf->rt2x00dev, index);	\
								\
	size = प्र_लिखो(line, __क्रमmat, value);			\
								\
	वापस simple_पढ़ो_from_buffer(buf, length, offset, line, size); \
पूर्ण

#घोषणा RT2X00DEBUGFS_OPS_WRITE(__name, __type)			\
अटल sमाप_प्रकार rt2x00debug_ग_लिखो_##__name(काष्ठा file *file,	\
					  स्थिर अक्षर __user *buf,\
					  माप_प्रकार length,	\
					  loff_t *offset)	\
अणु								\
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = file->निजी_data;	\
	स्थिर काष्ठा rt2x00debug *debug = पूर्णांकf->debug;		\
	अक्षर line[17];						\
	माप_प्रकार size;						\
	अचिन्हित पूर्णांक index = पूर्णांकf->offset_##__name;		\
	__type value;						\
								\
	अगर (*offset)						\
		वापस 0;					\
								\
	अगर (index >= debug->__name.word_count)			\
		वापस -EINVAL;					\
								\
	अगर (length > माप(line))				\
		वापस -EINVAL;					\
								\
	अगर (copy_from_user(line, buf, length))			\
		वापस -EFAULT;					\
	line[16] = 0;						\
						\
	size = म_माप(line);					\
	value = simple_म_से_अदीर्घ(line, शून्य, 0);			\
								\
	index += (debug->__name.word_base /			\
		  debug->__name.word_size);			\
								\
	अगर (debug->__name.flags & RT2X00DEBUGFS_OFFSET)		\
		index *= debug->__name.word_size;		\
								\
	debug->__name.ग_लिखो(पूर्णांकf->rt2x00dev, index, value);	\
								\
	*offset += size;					\
	वापस size;						\
पूर्ण

#घोषणा RT2X00DEBUGFS_OPS(__name, __क्रमmat, __type)		\
RT2X00DEBUGFS_OPS_READ(__name, __क्रमmat, __type);		\
RT2X00DEBUGFS_OPS_WRITE(__name, __type);			\
								\
अटल स्थिर काष्ठा file_operations rt2x00debug_fop_##__name = अणु\
	.owner		= THIS_MODULE,				\
	.पढ़ो		= rt2x00debug_पढ़ो_##__name,		\
	.ग_लिखो		= rt2x00debug_ग_लिखो_##__name,		\
	.खोलो		= rt2x00debug_file_खोलो,		\
	.release	= rt2x00debug_file_release,		\
	.llseek		= generic_file_llseek,			\
पूर्ण;

RT2X00DEBUGFS_OPS(csr, "0x%.8x\n", u32);
RT2X00DEBUGFS_OPS(eeprom, "0x%.4x\n", u16);
RT2X00DEBUGFS_OPS(bbp, "0x%.2x\n", u8);
RT2X00DEBUGFS_OPS(rf, "0x%.8x\n", u32);
RT2X00DEBUGFS_OPS(rfcsr, "0x%.2x\n", u8);

अटल sमाप_प्रकार rt2x00debug_पढ़ो_dev_flags(काष्ठा file *file,
					  अक्षर __user *buf,
					  माप_प्रकार length,
					  loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf =	file->निजी_data;
	अक्षर line[16];
	माप_प्रकार size;

	अगर (*offset)
		वापस 0;

	size = प्र_लिखो(line, "0x%.8x\n", (अचिन्हित पूर्णांक)पूर्णांकf->rt2x00dev->flags);

	वापस simple_पढ़ो_from_buffer(buf, length, offset, line, size);
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_fop_dev_flags = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rt2x00debug_पढ़ो_dev_flags,
	.खोलो		= rt2x00debug_file_खोलो,
	.release	= rt2x00debug_file_release,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rt2x00debug_पढ़ो_cap_flags(काष्ठा file *file,
					  अक्षर __user *buf,
					  माप_प्रकार length,
					  loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf =	file->निजी_data;
	अक्षर line[16];
	माप_प्रकार size;

	अगर (*offset)
		वापस 0;

	size = प्र_लिखो(line, "0x%.8x\n", (अचिन्हित पूर्णांक)पूर्णांकf->rt2x00dev->cap_flags);

	वापस simple_पढ़ो_from_buffer(buf, length, offset, line, size);
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_fop_cap_flags = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= rt2x00debug_पढ़ो_cap_flags,
	.खोलो		= rt2x00debug_file_खोलो,
	.release	= rt2x00debug_file_release,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rt2x00debug_ग_लिखो_restart_hw(काष्ठा file *file,
					    स्थिर अक्षर __user *buf,
					    माप_प्रकार length,
					    loff_t *offset)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf =	file->निजी_data;
	काष्ठा rt2x00_dev *rt2x00dev = पूर्णांकf->rt2x00dev;
	अटल अचिन्हित दीर्घ last_reset = INITIAL_JIFFIES;

	अगर (!rt2x00_has_cap_restart_hw(rt2x00dev))
		वापस -EOPNOTSUPP;

	अगर (समय_beक्रमe(jअगरfies, last_reset + msecs_to_jअगरfies(2000)))
		वापस -EBUSY;

	last_reset = jअगरfies;

	ieee80211_restart_hw(rt2x00dev->hw);
	वापस length;
पूर्ण

अटल स्थिर काष्ठा file_operations rt2x00debug_restart_hw = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = rt2x00debug_ग_लिखो_restart_hw,
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम rt2x00debug_create_file_driver(स्थिर अक्षर *name,
					   काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf,
					   काष्ठा debugfs_blob_wrapper *blob)
अणु
	अक्षर *data;

	data = kzalloc(3 * MAX_LINE_LENGTH, GFP_KERNEL);
	अगर (!data)
		वापस;

	blob->data = data;
	data += प्र_लिखो(data, "driver:\t%s\n", पूर्णांकf->rt2x00dev->ops->name);
	data += प्र_लिखो(data, "version:\t%s\n", DRV_VERSION);
	blob->size = म_माप(blob->data);

	debugfs_create_blob(name, 0400, पूर्णांकf->driver_folder, blob);
पूर्ण

अटल व्योम rt2x00debug_create_file_chipset(स्थिर अक्षर *name,
					    काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf,
					    काष्ठा debugfs_blob_wrapper *blob)
अणु
	स्थिर काष्ठा rt2x00debug *debug = पूर्णांकf->debug;
	अक्षर *data;

	data = kzalloc(9 * MAX_LINE_LENGTH, GFP_KERNEL);
	अगर (!data)
		वापस;

	blob->data = data;
	data += प्र_लिखो(data, "rt chip:\t%04x\n", पूर्णांकf->rt2x00dev->chip.rt);
	data += प्र_लिखो(data, "rf chip:\t%04x\n", पूर्णांकf->rt2x00dev->chip.rf);
	data += प्र_लिखो(data, "revision:\t%04x\n", पूर्णांकf->rt2x00dev->chip.rev);
	data += प्र_लिखो(data, "\n");
	data += प्र_लिखो(data, "register\tbase\twords\twordsize\n");
#घोषणा RT2X00DEBUGFS_SPRINTF_REGISTER(__name)			\
अणु								\
	अगर (debug->__name.पढ़ो)					\
		data += प्र_लिखो(data, __stringअगरy(__name)	\
				"\t%d\t%d\t%d\n",		\
				debug->__name.word_base,	\
				debug->__name.word_count,	\
				debug->__name.word_size);	\
पूर्ण
	RT2X00DEBUGFS_SPRINTF_REGISTER(csr);
	RT2X00DEBUGFS_SPRINTF_REGISTER(eeprom);
	RT2X00DEBUGFS_SPRINTF_REGISTER(bbp);
	RT2X00DEBUGFS_SPRINTF_REGISTER(rf);
	RT2X00DEBUGFS_SPRINTF_REGISTER(rfcsr);
#अघोषित RT2X00DEBUGFS_SPRINTF_REGISTER

	blob->size = म_माप(blob->data);

	debugfs_create_blob(name, 0400, पूर्णांकf->driver_folder, blob);
पूर्ण

व्योम rt2x00debug_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	स्थिर काष्ठा rt2x00debug *debug = rt2x00dev->ops->debugfs;
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf;
	काष्ठा dentry *queue_folder;
	काष्ठा dentry *रेजिस्टर_folder;

	पूर्णांकf = kzalloc(माप(काष्ठा rt2x00debug_पूर्णांकf), GFP_KERNEL);
	अगर (!पूर्णांकf) अणु
		rt2x00_err(rt2x00dev, "Failed to allocate debug handler\n");
		वापस;
	पूर्ण

	पूर्णांकf->debug = debug;
	पूर्णांकf->rt2x00dev = rt2x00dev;
	rt2x00dev->debugfs_पूर्णांकf = पूर्णांकf;

	पूर्णांकf->driver_folder =
	    debugfs_create_dir(पूर्णांकf->rt2x00dev->ops->name,
			       rt2x00dev->hw->wiphy->debugfsdir);

	rt2x00debug_create_file_driver("driver", पूर्णांकf, &पूर्णांकf->driver_blob);
	rt2x00debug_create_file_chipset("chipset", पूर्णांकf, &पूर्णांकf->chipset_blob);
	debugfs_create_file("dev_flags", 0400, पूर्णांकf->driver_folder, पूर्णांकf,
			    &rt2x00debug_fop_dev_flags);
	debugfs_create_file("cap_flags", 0400, पूर्णांकf->driver_folder, पूर्णांकf,
			    &rt2x00debug_fop_cap_flags);
	debugfs_create_file("restart_hw", 0200, पूर्णांकf->driver_folder, पूर्णांकf,
			    &rt2x00debug_restart_hw);

	रेजिस्टर_folder = debugfs_create_dir("register", पूर्णांकf->driver_folder);

#घोषणा RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(__पूर्णांकf, __name)		\
(अणु									\
	अगर (debug->__name.पढ़ो) अणु					\
		debugfs_create_u32(__stringअगरy(__name) "_offset", 0600,	\
				   रेजिस्टर_folder,			\
				   &(__पूर्णांकf)->offset_##__name);		\
									\
		debugfs_create_file(__stringअगरy(__name) "_value", 0600,	\
				    रेजिस्टर_folder, (__पूर्णांकf),		\
				    &rt2x00debug_fop_##__name);		\
	पूर्ण								\
पूर्ण)

	RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(पूर्णांकf, csr);
	RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(पूर्णांकf, eeprom);
	RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(पूर्णांकf, bbp);
	RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(पूर्णांकf, rf);
	RT2X00DEBUGFS_CREATE_REGISTER_ENTRY(पूर्णांकf, rfcsr);

#अघोषित RT2X00DEBUGFS_CREATE_REGISTER_ENTRY

	queue_folder = debugfs_create_dir("queue", पूर्णांकf->driver_folder);

	debugfs_create_file("dump", 0400, queue_folder, पूर्णांकf,
			    &rt2x00debug_fop_queue_dump);

	skb_queue_head_init(&पूर्णांकf->frame_dump_skbqueue);
	init_रुकोqueue_head(&पूर्णांकf->frame_dump_रुकोqueue);

	debugfs_create_file("queue", 0400, queue_folder, पूर्णांकf,
			    &rt2x00debug_fop_queue_stats);

#अगर_घोषित CONFIG_RT2X00_LIB_CRYPTO
	अगर (rt2x00_has_cap_hw_crypto(rt2x00dev))
		debugfs_create_file("crypto", 0444, queue_folder, पूर्णांकf,
				    &rt2x00debug_fop_crypto_stats);
#पूर्ण_अगर

	वापस;
पूर्ण

व्योम rt2x00debug_deरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2x00debug_पूर्णांकf *पूर्णांकf = rt2x00dev->debugfs_पूर्णांकf;

	अगर (unlikely(!पूर्णांकf))
		वापस;

	skb_queue_purge(&पूर्णांकf->frame_dump_skbqueue);

	debugfs_हटाओ_recursive(पूर्णांकf->driver_folder);
	kमुक्त(पूर्णांकf->chipset_blob.data);
	kमुक्त(पूर्णांकf->driver_blob.data);
	kमुक्त(पूर्णांकf);

	rt2x00dev->debugfs_पूर्णांकf = शून्य;
पूर्ण
