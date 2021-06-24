<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/******************************************************************************
 *  usbaपंचांग.c - Generic USB xDSL driver core
 *
 *  Copyright (C) 2001, Alcatel
 *  Copyright (C) 2003, Duncan Sands, SolNegro, Josep Comas
 *  Copyright (C) 2004, David Woodhouse, Roman Kagan
 ******************************************************************************/

/*
 *  Written by Johan Verrept, Duncan Sands (duncan.sands@मुक्त.fr) and David Woodhouse
 *
 *  1.7+:	- See the check-in logs
 *
 *  1.6:	- No दीर्घer खोलोs a connection अगर the firmware is not loaded
 *  		- Added support क्रम the speedtouch 330
 *  		- Removed the limit on the number of devices
 *  		- Module now स्वतःloads on device plugin
 *  		- Merged relevant parts of sarlib
 *  		- Replaced the kernel thपढ़ो with a tasklet
 *  		- New packet transmission code
 *  		- Changed proc file contents
 *  		- Fixed all known SMP races
 *  		- Many fixes and cleanups
 *  		- Various fixes by Oliver Neukum (oliver@neukum.name)
 *
 *  1.5A:	- Version क्रम inclusion in 2.5 series kernel
 *		- Modअगरications by Riअक्षरd Purdie (rpurdie@rpsys.net)
 *		- made compatible with kernel 2.5.6 onwards by changing
 *		usbaपंचांग_usb_send_data_context->urb to a poपूर्णांकer and adding code
 *		to alloc and मुक्त it
 *		- हटाओ_रुको_queue() added to usbaपंचांग_aपंचांग_processqueue_thपढ़ो()
 *
 *  1.5:	- fixed memory leak when aपंचांगsar_decode_aal5 वापसed शून्य.
 *		(reported by stephen.robinson@zen.co.uk)
 *
 *  1.4:	- changed the spin_lock() under पूर्णांकerrupt to spin_lock_irqsave()
 *		- unlink all active send urbs of a vcc that is being बंदd.
 *
 *  1.3.1:	- added the version number
 *
 *  1.3:	- Added multiple send urb support
 *		- fixed memory leak and vcc->tx_inuse starvation bug
 *		  when not enough memory left in vcc.
 *
 *  1.2:	- Fixed race condition in usbaपंचांग_usb_send_data()
 *  1.1:	- Turned off packet debugging
 *
 */

#समावेश "usbatm.h"

#समावेश <linux/uaccess.h>
#समावेश <linux/crc32.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/ratelimit.h>

#अगर_घोषित VERBOSE_DEBUG
अटल पूर्णांक usbaपंचांग_prपूर्णांक_packet(काष्ठा usbaपंचांग_data *instance, स्थिर अचिन्हित अक्षर *data, पूर्णांक len);
#घोषणा PACKETDEBUG(arg...)	usbaपंचांग_prपूर्णांक_packet(arg)
#घोषणा vdbg(arg...)		dev_dbg(arg)
#अन्यथा
#घोषणा PACKETDEBUG(arg...)
#घोषणा vdbg(arg...)
#पूर्ण_अगर

#घोषणा DRIVER_AUTHOR	"Johan Verrept, Duncan Sands <duncan.sands@free.fr>"
#घोषणा DRIVER_DESC	"Generic USB ATM/DSL I/O"

अटल स्थिर अक्षर usbaपंचांग_driver_name[] = "usbatm";

#घोषणा UDSL_MAX_RCV_URBS		16
#घोषणा UDSL_MAX_SND_URBS		16
#घोषणा UDSL_MAX_BUF_SIZE		65536
#घोषणा UDSL_DEFAULT_RCV_URBS		4
#घोषणा UDSL_DEFAULT_SND_URBS		4
#घोषणा UDSL_DEFAULT_RCV_BUF_SIZE	3392	/* 64 * ATM_CELL_SIZE */
#घोषणा UDSL_DEFAULT_SND_BUF_SIZE	3392	/* 64 * ATM_CELL_SIZE */

#घोषणा ATM_CELL_HEADER			(ATM_CELL_SIZE - ATM_CELL_PAYLOAD)

#घोषणा THROTTLE_MSECS			100	/* delay to recover processing after urb submission fails */

अटल अचिन्हित पूर्णांक num_rcv_urbs = UDSL_DEFAULT_RCV_URBS;
अटल अचिन्हित पूर्णांक num_snd_urbs = UDSL_DEFAULT_SND_URBS;
अटल अचिन्हित पूर्णांक rcv_buf_bytes = UDSL_DEFAULT_RCV_BUF_SIZE;
अटल अचिन्हित पूर्णांक snd_buf_bytes = UDSL_DEFAULT_SND_BUF_SIZE;

module_param(num_rcv_urbs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num_rcv_urbs,
		 "Number of urbs used for reception (range: 0-"
		 __MODULE_STRING(UDSL_MAX_RCV_URBS) ", default: "
		 __MODULE_STRING(UDSL_DEFAULT_RCV_URBS) ")");

module_param(num_snd_urbs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num_snd_urbs,
		 "Number of urbs used for transmission (range: 0-"
		 __MODULE_STRING(UDSL_MAX_SND_URBS) ", default: "
		 __MODULE_STRING(UDSL_DEFAULT_SND_URBS) ")");

module_param(rcv_buf_bytes, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcv_buf_bytes,
		 "Size of the buffers used for reception, in bytes (range: 1-"
		 __MODULE_STRING(UDSL_MAX_BUF_SIZE) ", default: "
		 __MODULE_STRING(UDSL_DEFAULT_RCV_BUF_SIZE) ")");

module_param(snd_buf_bytes, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(snd_buf_bytes,
		 "Size of the buffers used for transmission, in bytes (range: 1-"
		 __MODULE_STRING(UDSL_MAX_BUF_SIZE) ", default: "
		 __MODULE_STRING(UDSL_DEFAULT_SND_BUF_SIZE) ")");


/* receive */

काष्ठा usbaपंचांग_vcc_data अणु
	/* vpi/vci lookup */
	काष्ठा list_head list;
	लघु vpi;
	पूर्णांक vci;
	काष्ठा aपंचांग_vcc *vcc;

	/* raw cell reassembly */
	काष्ठा sk_buff *sarb;
पूर्ण;


/* send */

काष्ठा usbaपंचांग_control अणु
	काष्ठा aपंचांग_skb_data aपंचांग;
	u32 len;
	u32 crc;
पूर्ण;

#घोषणा UDSL_SKB(x)		((काष्ठा usbaपंचांग_control *)(x)->cb)


/* ATM */

अटल व्योम usbaपंचांग_aपंचांग_dev_बंद(काष्ठा aपंचांग_dev *aपंचांग_dev);
अटल पूर्णांक usbaपंचांग_aपंचांग_खोलो(काष्ठा aपंचांग_vcc *vcc);
अटल व्योम usbaपंचांग_aपंचांग_बंद(काष्ठा aपंचांग_vcc *vcc);
अटल पूर्णांक usbaपंचांग_aपंचांग_ioctl(काष्ठा aपंचांग_dev *aपंचांग_dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
अटल पूर्णांक usbaपंचांग_aपंचांग_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल पूर्णांक usbaपंचांग_aपंचांग_proc_पढ़ो(काष्ठा aपंचांग_dev *aपंचांग_dev, loff_t *pos, अक्षर *page);

अटल स्थिर काष्ठा aपंचांगdev_ops usbaपंचांग_aपंचांग_devops = अणु
	.dev_बंद	= usbaपंचांग_aपंचांग_dev_बंद,
	.खोलो		= usbaपंचांग_aपंचांग_खोलो,
	.बंद		= usbaपंचांग_aपंचांग_बंद,
	.ioctl		= usbaपंचांग_aपंचांग_ioctl,
	.send		= usbaपंचांग_aपंचांग_send,
	.proc_पढ़ो	= usbaपंचांग_aपंचांग_proc_पढ़ो,
	.owner		= THIS_MODULE,
पूर्ण;


/***********
**  misc  **
***********/

अटल अंतरभूत अचिन्हित पूर्णांक usbaपंचांग_pdu_length(अचिन्हित पूर्णांक length)
अणु
	length += ATM_CELL_PAYLOAD - 1 + ATM_AAL5_TRAILER;
	वापस length - length % ATM_CELL_PAYLOAD;
पूर्ण

अटल अंतरभूत व्योम usbaपंचांग_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अगर (vcc->pop)
		vcc->pop(vcc, skb);
	अन्यथा
		dev_kमुक्त_skb_any(skb);
पूर्ण


/***********
**  urbs  **
************/

अटल काष्ठा urb *usbaपंचांग_pop_urb(काष्ठा usbaपंचांग_channel *channel)
अणु
	काष्ठा urb *urb;

	spin_lock_irq(&channel->lock);
	अगर (list_empty(&channel->list)) अणु
		spin_unlock_irq(&channel->lock);
		वापस शून्य;
	पूर्ण

	urb = list_entry(channel->list.next, काष्ठा urb, urb_list);
	list_del(&urb->urb_list);
	spin_unlock_irq(&channel->lock);

	वापस urb;
पूर्ण

अटल पूर्णांक usbaपंचांग_submit_urb(काष्ठा urb *urb)
अणु
	काष्ठा usbaपंचांग_channel *channel = urb->context;
	पूर्णांक ret;

	/* vdbg("%s: submitting urb 0x%p, size %u",
	     __func__, urb, urb->transfer_buffer_length); */

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		अगर (prपूर्णांकk_ratelimit())
			aपंचांग_warn(channel->usbaपंचांग, "%s: urb 0x%p submission failed (%d)!\n",
				__func__, urb, ret);

		/* consider all errors transient and वापस the buffer back to the queue */
		urb->status = -EAGAIN;
		spin_lock_irq(&channel->lock);

		/* must add to the front when sending; करोesn't matter when receiving */
		list_add(&urb->urb_list, &channel->list);

		spin_unlock_irq(&channel->lock);

		/* make sure the channel करोesn't stall */
		mod_समयr(&channel->delay, jअगरfies + msecs_to_jअगरfies(THROTTLE_MSECS));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम usbaपंचांग_complete(काष्ठा urb *urb)
अणु
	काष्ठा usbaपंचांग_channel *channel = urb->context;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	/* vdbg("%s: urb 0x%p, status %d, actual_length %d",
	     __func__, urb, status, urb->actual_length); */

	/* Can be invoked from task context, protect against पूर्णांकerrupts */
	spin_lock_irqsave(&channel->lock, flags);

	/* must add to the back when receiving; करोesn't matter when sending */
	list_add_tail(&urb->urb_list, &channel->list);

	spin_unlock_irqrestore(&channel->lock, flags);

	अगर (unlikely(status) &&
			(!(channel->usbaपंचांग->flags & UDSL_IGNORE_EILSEQ) ||
			 status != -EILSEQ)) अणु
		अगर (status == -ESHUTDOWN)
			वापस;

		अगर (prपूर्णांकk_ratelimit())
			aपंचांग_warn(channel->usbaपंचांग, "%s: urb 0x%p failed (%d)!\n",
				__func__, urb, status);
		/* throttle processing in हाल of an error */
		mod_समयr(&channel->delay, jअगरfies + msecs_to_jअगरfies(THROTTLE_MSECS));
	पूर्ण अन्यथा
		tasklet_schedule(&channel->tasklet);
पूर्ण


/*************
**  decode  **
*************/

अटल अंतरभूत काष्ठा usbaपंचांग_vcc_data *usbaपंचांग_find_vcc(काष्ठा usbaपंचांग_data *instance,
						  लघु vpi, पूर्णांक vci)
अणु
	काष्ठा usbaपंचांग_vcc_data *vcc_data;

	list_क्रम_each_entry(vcc_data, &instance->vcc_list, list)
		अगर ((vcc_data->vci == vci) && (vcc_data->vpi == vpi))
			वापस vcc_data;
	वापस शून्य;
पूर्ण

अटल व्योम usbaपंचांग_extract_one_cell(काष्ठा usbaपंचांग_data *instance, अचिन्हित अक्षर *source)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *sarb;
	लघु vpi = ((source[0] & 0x0f) << 4)  | (source[1] >> 4);
	पूर्णांक vci = ((source[1] & 0x0f) << 12) | (source[2] << 4) | (source[3] >> 4);
	u8 pti = ((source[3] & 0xe) >> 1);

	अगर ((vci != instance->cached_vci) || (vpi != instance->cached_vpi)) अणु
		instance->cached_vpi = vpi;
		instance->cached_vci = vci;

		instance->cached_vcc = usbaपंचांग_find_vcc(instance, vpi, vci);

		अगर (!instance->cached_vcc)
			aपंचांग_rldbg(instance, "%s: unknown vpi/vci (%hd/%d)!\n", __func__, vpi, vci);
	पूर्ण

	अगर (!instance->cached_vcc)
		वापस;

	vcc = instance->cached_vcc->vcc;

	/* OAM F5 end-to-end */
	अगर (pti == ATM_PTI_E2EF5) अणु
		अगर (prपूर्णांकk_ratelimit())
			aपंचांग_warn(instance, "%s: OAM not supported (vpi %d, vci %d)!\n",
				__func__, vpi, vci);
		atomic_inc(&vcc->stats->rx_err);
		वापस;
	पूर्ण

	sarb = instance->cached_vcc->sarb;

	अगर (sarb->tail + ATM_CELL_PAYLOAD > sarb->end) अणु
		aपंचांग_rldbg(instance, "%s: buffer overrun (sarb->len %u, vcc: 0x%p)!\n",
				__func__, sarb->len, vcc);
		/* discard cells alपढ़ोy received */
		skb_trim(sarb, 0);
	पूर्ण

	स_नकल(skb_tail_poपूर्णांकer(sarb), source + ATM_CELL_HEADER, ATM_CELL_PAYLOAD);
	__skb_put(sarb, ATM_CELL_PAYLOAD);

	अगर (pti & 1) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक length;
		अचिन्हित पूर्णांक pdu_length;

		length = (source[ATM_CELL_SIZE - 6] << 8) + source[ATM_CELL_SIZE - 5];

		/* guard against overflow */
		अगर (length > ATM_MAX_AAL5_PDU) अणु
			aपंचांग_rldbg(instance, "%s: bogus length %u (vcc: 0x%p)!\n",
				  __func__, length, vcc);
			atomic_inc(&vcc->stats->rx_err);
			जाओ out;
		पूर्ण

		pdu_length = usbaपंचांग_pdu_length(length);

		अगर (sarb->len < pdu_length) अणु
			aपंचांग_rldbg(instance, "%s: bogus pdu_length %u (sarb->len: %u, vcc: 0x%p)!\n",
				  __func__, pdu_length, sarb->len, vcc);
			atomic_inc(&vcc->stats->rx_err);
			जाओ out;
		पूर्ण

		अगर (crc32_be(~0, skb_tail_poपूर्णांकer(sarb) - pdu_length, pdu_length) != 0xc704dd7b) अणु
			aपंचांग_rldbg(instance, "%s: packet failed crc check (vcc: 0x%p)!\n",
				  __func__, vcc);
			atomic_inc(&vcc->stats->rx_err);
			जाओ out;
		पूर्ण

		vdbg(&instance->usb_पूर्णांकf->dev,
		     "%s: got packet (length: %u, pdu_length: %u, vcc: 0x%p)",
		     __func__, length, pdu_length, vcc);

		skb = dev_alloc_skb(length);
		अगर (!skb) अणु
			अगर (prपूर्णांकk_ratelimit())
				aपंचांग_err(instance, "%s: no memory for skb (length: %u)!\n",
					__func__, length);
			atomic_inc(&vcc->stats->rx_drop);
			जाओ out;
		पूर्ण

		vdbg(&instance->usb_पूर्णांकf->dev,
		     "%s: allocated new sk_buff (skb: 0x%p, skb->truesize: %u)",
		     __func__, skb, skb->truesize);

		अगर (!aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
			aपंचांग_rldbg(instance, "%s: failed atm_charge (skb->truesize: %u)!\n",
				  __func__, skb->truesize);
			dev_kमुक्त_skb_any(skb);
			जाओ out;	/* aपंचांग_अक्षरge increments rx_drop */
		पूर्ण

		skb_copy_to_linear_data(skb,
					skb_tail_poपूर्णांकer(sarb) - pdu_length,
					length);
		__skb_put(skb, length);

		vdbg(&instance->usb_पूर्णांकf->dev,
		     "%s: sending skb 0x%p, skb->len %u, skb->truesize %u",
		     __func__, skb, skb->len, skb->truesize);

		PACKETDEBUG(instance, skb->data, skb->len);

		vcc->push(vcc, skb);

		atomic_inc(&vcc->stats->rx);
	out:
		skb_trim(sarb, 0);
	पूर्ण
पूर्ण

अटल व्योम usbaपंचांग_extract_cells(काष्ठा usbaपंचांग_data *instance,
		अचिन्हित अक्षर *source, अचिन्हित पूर्णांक avail_data)
अणु
	अचिन्हित पूर्णांक stride = instance->rx_channel.stride;
	अचिन्हित पूर्णांक buf_usage = instance->buf_usage;

	/* extract cells from incoming data, taking पूर्णांकo account that
	 * the length of avail data may not be a multiple of stride */

	अगर (buf_usage > 0) अणु
		/* we have a partially received aपंचांग cell */
		अचिन्हित अक्षर *cell_buf = instance->cell_buf;
		अचिन्हित पूर्णांक space_left = stride - buf_usage;

		अगर (avail_data >= space_left) अणु
			/* add new data and process cell */
			स_नकल(cell_buf + buf_usage, source, space_left);
			source += space_left;
			avail_data -= space_left;
			usbaपंचांग_extract_one_cell(instance, cell_buf);
			instance->buf_usage = 0;
		पूर्ण अन्यथा अणु
			/* not enough data to fill the cell */
			स_नकल(cell_buf + buf_usage, source, avail_data);
			instance->buf_usage = buf_usage + avail_data;
			वापस;
		पूर्ण
	पूर्ण

	क्रम (; avail_data >= stride; avail_data -= stride, source += stride)
		usbaपंचांग_extract_one_cell(instance, source);

	अगर (avail_data > 0) अणु
		/* length was not a multiple of stride -
		 * save reमुख्यing data क्रम next call */
		स_नकल(instance->cell_buf, source, avail_data);
		instance->buf_usage = avail_data;
	पूर्ण
पूर्ण


/*************
**  encode  **
*************/

अटल अचिन्हित पूर्णांक usbaपंचांग_ग_लिखो_cells(काष्ठा usbaपंचांग_data *instance,
				       काष्ठा sk_buff *skb,
				       u8 *target, अचिन्हित पूर्णांक avail_space)
अणु
	काष्ठा usbaपंचांग_control *ctrl = UDSL_SKB(skb);
	काष्ठा aपंचांग_vcc *vcc = ctrl->aपंचांग.vcc;
	अचिन्हित पूर्णांक bytes_written;
	अचिन्हित पूर्णांक stride = instance->tx_channel.stride;

	क्रम (bytes_written = 0; bytes_written < avail_space && ctrl->len;
	     bytes_written += stride, target += stride) अणु
		अचिन्हित पूर्णांक data_len = min_t(अचिन्हित पूर्णांक, skb->len, ATM_CELL_PAYLOAD);
		अचिन्हित पूर्णांक left = ATM_CELL_PAYLOAD - data_len;
		u8 *ptr = target;

		ptr[0] = vcc->vpi >> 4;
		ptr[1] = (vcc->vpi << 4) | (vcc->vci >> 12);
		ptr[2] = vcc->vci >> 4;
		ptr[3] = vcc->vci << 4;
		ptr[4] = 0xec;
		ptr += ATM_CELL_HEADER;

		skb_copy_from_linear_data(skb, ptr, data_len);
		ptr += data_len;
		__skb_pull(skb, data_len);

		अगर (!left)
			जारी;

		स_रखो(ptr, 0, left);

		अगर (left >= ATM_AAL5_TRAILER) अणु	/* trailer will go in this cell */
			u8 *trailer = target + ATM_CELL_SIZE - ATM_AAL5_TRAILER;
			/* trailer[0] = 0;		UU = 0 */
			/* trailer[1] = 0;		CPI = 0 */
			trailer[2] = ctrl->len >> 8;
			trailer[3] = ctrl->len;

			ctrl->crc = ~crc32_be(ctrl->crc, ptr, left - 4);

			trailer[4] = ctrl->crc >> 24;
			trailer[5] = ctrl->crc >> 16;
			trailer[6] = ctrl->crc >> 8;
			trailer[7] = ctrl->crc;

			target[3] |= 0x2;	/* adjust PTI */

			ctrl->len = 0;		/* tag this skb finished */
		पूर्ण अन्यथा
			ctrl->crc = crc32_be(ctrl->crc, ptr, left);
	पूर्ण

	वापस bytes_written;
पूर्ण


/**************
**  receive  **
**************/

अटल व्योम usbaपंचांग_rx_process(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा usbaपंचांग_data *instance = from_tasklet(instance, t,
						    rx_channel.tasklet);
	काष्ठा urb *urb;

	जबतक ((urb = usbaपंचांग_pop_urb(&instance->rx_channel))) अणु
		vdbg(&instance->usb_पूर्णांकf->dev,
		     "%s: processing urb 0x%p", __func__, urb);

		अगर (usb_pipeisoc(urb->pipe)) अणु
			अचिन्हित अक्षर *merge_start = शून्य;
			अचिन्हित पूर्णांक merge_length = 0;
			स्थिर अचिन्हित पूर्णांक packet_size = instance->rx_channel.packet_size;
			पूर्णांक i;

			क्रम (i = 0; i < urb->number_of_packets; i++) अणु
				अगर (!urb->iso_frame_desc[i].status) अणु
					अचिन्हित पूर्णांक actual_length = urb->iso_frame_desc[i].actual_length;

					अगर (!merge_length)
						merge_start = (अचिन्हित अक्षर *)urb->transfer_buffer + urb->iso_frame_desc[i].offset;
					merge_length += actual_length;
					अगर (merge_length && (actual_length < packet_size)) अणु
						usbaपंचांग_extract_cells(instance, merge_start, merge_length);
						merge_length = 0;
					पूर्ण
				पूर्ण अन्यथा अणु
					aपंचांग_rldbg(instance, "%s: status %d in frame %d!\n", __func__, urb->status, i);
					अगर (merge_length)
						usbaपंचांग_extract_cells(instance, merge_start, merge_length);
					merge_length = 0;
					instance->buf_usage = 0;
				पूर्ण
			पूर्ण

			अगर (merge_length)
				usbaपंचांग_extract_cells(instance, merge_start, merge_length);
		पूर्ण अन्यथा
			अगर (!urb->status)
				usbaपंचांग_extract_cells(instance, urb->transfer_buffer, urb->actual_length);
			अन्यथा
				instance->buf_usage = 0;

		अगर (usbaपंचांग_submit_urb(urb))
			वापस;
	पूर्ण
पूर्ण


/***********
**  send  **
***********/

अटल व्योम usbaपंचांग_tx_process(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा usbaपंचांग_data *instance = from_tasklet(instance, t,
						    tx_channel.tasklet);
	काष्ठा sk_buff *skb = instance->current_skb;
	काष्ठा urb *urb = शून्य;
	स्थिर अचिन्हित पूर्णांक buf_size = instance->tx_channel.buf_size;
	अचिन्हित पूर्णांक bytes_written = 0;
	u8 *buffer = शून्य;

	अगर (!skb)
		skb = skb_dequeue(&instance->sndqueue);

	जबतक (skb) अणु
		अगर (!urb) अणु
			urb = usbaपंचांग_pop_urb(&instance->tx_channel);
			अगर (!urb)
				अवरोध;		/* no more senders */
			buffer = urb->transfer_buffer;
			bytes_written = (urb->status == -EAGAIN) ?
				urb->transfer_buffer_length : 0;
		पूर्ण

		bytes_written += usbaपंचांग_ग_लिखो_cells(instance, skb,
						  buffer + bytes_written,
						  buf_size - bytes_written);

		vdbg(&instance->usb_पूर्णांकf->dev,
		     "%s: wrote %u bytes from skb 0x%p to urb 0x%p",
		     __func__, bytes_written, skb, urb);

		अगर (!UDSL_SKB(skb)->len) अणु
			काष्ठा aपंचांग_vcc *vcc = UDSL_SKB(skb)->aपंचांग.vcc;

			usbaपंचांग_pop(vcc, skb);
			atomic_inc(&vcc->stats->tx);

			skb = skb_dequeue(&instance->sndqueue);
		पूर्ण

		अगर (bytes_written == buf_size || (!skb && bytes_written)) अणु
			urb->transfer_buffer_length = bytes_written;

			अगर (usbaपंचांग_submit_urb(urb))
				अवरोध;
			urb = शून्य;
		पूर्ण
	पूर्ण

	instance->current_skb = skb;
पूर्ण

अटल व्योम usbaपंचांग_cancel_send(काष्ठा usbaपंचांग_data *instance,
			       काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा sk_buff *skb, *n;

	spin_lock_irq(&instance->sndqueue.lock);
	skb_queue_walk_safe(&instance->sndqueue, skb, n) अणु
		अगर (UDSL_SKB(skb)->aपंचांग.vcc == vcc) अणु
			aपंचांग_dbg(instance, "%s: popping skb 0x%p\n", __func__, skb);
			__skb_unlink(skb, &instance->sndqueue);
			usbaपंचांग_pop(vcc, skb);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&instance->sndqueue.lock);

	tasklet_disable(&instance->tx_channel.tasklet);
	अगर ((skb = instance->current_skb) && (UDSL_SKB(skb)->aपंचांग.vcc == vcc)) अणु
		aपंचांग_dbg(instance, "%s: popping current skb (0x%p)\n", __func__, skb);
		instance->current_skb = शून्य;
		usbaपंचांग_pop(vcc, skb);
	पूर्ण
	tasklet_enable(&instance->tx_channel.tasklet);
पूर्ण

अटल पूर्णांक usbaपंचांग_aपंचांग_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा usbaपंचांग_data *instance = vcc->dev->dev_data;
	काष्ठा usbaपंचांग_control *ctrl = UDSL_SKB(skb);
	पूर्णांक err;

	/* racy disconnection check - fine */
	अगर (!instance || instance->disconnected) अणु
#अगर_घोषित VERBOSE_DEBUG
		prपूर्णांकk_ratelimited(KERN_DEBUG "%s: %s!\n", __func__, instance ? "disconnected" : "NULL instance");
#पूर्ण_अगर
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (vcc->qos.aal != ATM_AAL5) अणु
		aपंचांग_rldbg(instance, "%s: unsupported ATM type %d!\n", __func__, vcc->qos.aal);
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (skb->len > ATM_MAX_AAL5_PDU) अणु
		aपंचांग_rldbg(instance, "%s: packet too long (%d vs %d)!\n",
				__func__, skb->len, ATM_MAX_AAL5_PDU);
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	PACKETDEBUG(instance, skb->data, skb->len);

	/* initialize the control block */
	ctrl->aपंचांग.vcc = vcc;
	ctrl->len = skb->len;
	ctrl->crc = crc32_be(~0, skb->data, skb->len);

	skb_queue_tail(&instance->sndqueue, skb);
	tasklet_schedule(&instance->tx_channel.tasklet);

	वापस 0;

 fail:
	usbaपंचांग_pop(vcc, skb);
	वापस err;
पूर्ण


/********************
**  bean counting  **
********************/

अटल व्योम usbaपंचांग_destroy_instance(काष्ठा kref *kref)
अणु
	काष्ठा usbaपंचांग_data *instance = container_of(kref, काष्ठा usbaपंचांग_data, refcount);

	tasklet_समाप्त(&instance->rx_channel.tasklet);
	tasklet_समाप्त(&instance->tx_channel.tasklet);
	usb_put_dev(instance->usb_dev);
	kमुक्त(instance);
पूर्ण

अटल व्योम usbaपंचांग_get_instance(काष्ठा usbaपंचांग_data *instance)
अणु
	kref_get(&instance->refcount);
पूर्ण

अटल व्योम usbaपंचांग_put_instance(काष्ठा usbaपंचांग_data *instance)
अणु
	kref_put(&instance->refcount, usbaपंचांग_destroy_instance);
पूर्ण


/**********
**  ATM  **
**********/

अटल व्योम usbaपंचांग_aपंचांग_dev_बंद(काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	काष्ठा usbaपंचांग_data *instance = aपंचांग_dev->dev_data;

	अगर (!instance)
		वापस;

	aपंचांग_dev->dev_data = शून्य; /* catch bugs */
	usbaपंचांग_put_instance(instance);	/* taken in usbaपंचांग_aपंचांग_init */
पूर्ण

अटल पूर्णांक usbaपंचांग_aपंचांग_proc_पढ़ो(काष्ठा aपंचांग_dev *aपंचांग_dev, loff_t *pos, अक्षर *page)
अणु
	काष्ठा usbaपंचांग_data *instance = aपंचांग_dev->dev_data;
	पूर्णांक left = *pos;

	अगर (!instance)
		वापस -ENODEV;

	अगर (!left--)
		वापस प्र_लिखो(page, "%s\n", instance->description);

	अगर (!left--)
		वापस प्र_लिखो(page, "MAC: %pM\n", aपंचांग_dev->esi);

	अगर (!left--)
		वापस प्र_लिखो(page,
			       "AAL5: tx %d ( %d err ), rx %d ( %d err, %d drop )\n",
			       atomic_पढ़ो(&aपंचांग_dev->stats.aal5.tx),
			       atomic_पढ़ो(&aपंचांग_dev->stats.aal5.tx_err),
			       atomic_पढ़ो(&aपंचांग_dev->stats.aal5.rx),
			       atomic_पढ़ो(&aपंचांग_dev->stats.aal5.rx_err),
			       atomic_पढ़ो(&aपंचांग_dev->stats.aal5.rx_drop));

	अगर (!left--) अणु
		अगर (instance->disconnected)
			वापस प्र_लिखो(page, "Disconnected\n");
		अन्यथा
			चयन (aपंचांग_dev->संकेत) अणु
			हाल ATM_PHY_SIG_FOUND:
				वापस प्र_लिखो(page, "Line up\n");
			हाल ATM_PHY_SIG_LOST:
				वापस प्र_लिखो(page, "Line down\n");
			शेष:
				वापस प्र_लिखो(page, "Line state unknown\n");
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbaपंचांग_aपंचांग_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा usbaपंचांग_data *instance = vcc->dev->dev_data;
	काष्ठा usbaपंचांग_vcc_data *new = शून्य;
	पूर्णांक ret;
	पूर्णांक vci = vcc->vci;
	लघु vpi = vcc->vpi;

	अगर (!instance)
		वापस -ENODEV;

	/* only support AAL5 */
	अगर ((vcc->qos.aal != ATM_AAL5)) अणु
		aपंचांग_warn(instance, "%s: unsupported ATM type %d!\n", __func__, vcc->qos.aal);
		वापस -EINVAL;
	पूर्ण

	/* sanity checks */
	अगर ((vcc->qos.rxtp.max_sdu < 0) || (vcc->qos.rxtp.max_sdu > ATM_MAX_AAL5_PDU)) अणु
		aपंचांग_dbg(instance, "%s: max_sdu %d out of range!\n", __func__, vcc->qos.rxtp.max_sdu);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&instance->serialize);	/* vs self, usbaपंचांग_aपंचांग_बंद, usbaपंचांग_usb_disconnect */

	अगर (instance->disconnected) अणु
		aपंचांग_dbg(instance, "%s: disconnected!\n", __func__);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (usbaपंचांग_find_vcc(instance, vpi, vci)) अणु
		aपंचांग_dbg(instance, "%s: %hd/%d already in use!\n", __func__, vpi, vci);
		ret = -EADDRINUSE;
		जाओ fail;
	पूर्ण

	new = kzalloc(माप(काष्ठा usbaपंचांग_vcc_data), GFP_KERNEL);
	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	new->vcc = vcc;
	new->vpi = vpi;
	new->vci = vci;

	new->sarb = alloc_skb(usbaपंचांग_pdu_length(vcc->qos.rxtp.max_sdu), GFP_KERNEL);
	अगर (!new->sarb) अणु
		aपंचांग_err(instance, "%s: no memory for SAR buffer!\n", __func__);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	vcc->dev_data = new;

	tasklet_disable(&instance->rx_channel.tasklet);
	instance->cached_vcc = new;
	instance->cached_vpi = vpi;
	instance->cached_vci = vci;
	list_add(&new->list, &instance->vcc_list);
	tasklet_enable(&instance->rx_channel.tasklet);

	set_bit(ATM_VF_ADDR, &vcc->flags);
	set_bit(ATM_VF_PARTIAL, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	mutex_unlock(&instance->serialize);

	aपंचांग_dbg(instance, "%s: allocated vcc data 0x%p\n", __func__, new);

	वापस 0;

fail:
	kमुक्त(new);
	mutex_unlock(&instance->serialize);
	वापस ret;
पूर्ण

अटल व्योम usbaपंचांग_aपंचांग_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा usbaपंचांग_data *instance = vcc->dev->dev_data;
	काष्ठा usbaपंचांग_vcc_data *vcc_data = vcc->dev_data;

	अगर (!instance || !vcc_data)
		वापस;

	usbaपंचांग_cancel_send(instance, vcc);

	mutex_lock(&instance->serialize);	/* vs self, usbaपंचांग_aपंचांग_खोलो, usbaपंचांग_usb_disconnect */

	tasklet_disable(&instance->rx_channel.tasklet);
	अगर (instance->cached_vcc == vcc_data) अणु
		instance->cached_vcc = शून्य;
		instance->cached_vpi = ATM_VPI_UNSPEC;
		instance->cached_vci = ATM_VCI_UNSPEC;
	पूर्ण
	list_del(&vcc_data->list);
	tasklet_enable(&instance->rx_channel.tasklet);

	kमुक्त_skb(vcc_data->sarb);
	vcc_data->sarb = शून्य;

	kमुक्त(vcc_data);
	vcc->dev_data = शून्य;

	vcc->vpi = ATM_VPI_UNSPEC;
	vcc->vci = ATM_VCI_UNSPEC;
	clear_bit(ATM_VF_READY, &vcc->flags);
	clear_bit(ATM_VF_PARTIAL, &vcc->flags);
	clear_bit(ATM_VF_ADDR, &vcc->flags);

	mutex_unlock(&instance->serialize);
पूर्ण

अटल पूर्णांक usbaपंचांग_aपंचांग_ioctl(काष्ठा aपंचांग_dev *aपंचांग_dev, अचिन्हित पूर्णांक cmd,
			  व्योम __user *arg)
अणु
	काष्ठा usbaपंचांग_data *instance = aपंचांग_dev->dev_data;

	अगर (!instance || instance->disconnected)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल ATM_QUERYLOOP:
		वापस put_user(ATM_LM_NONE, (पूर्णांक __user *)arg) ? -EFAULT : 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक usbaपंचांग_aपंचांग_init(काष्ठा usbaपंचांग_data *instance)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	पूर्णांक ret, i;

	/* ATM init.  The ATM initialization scheme suffers from an पूर्णांकrinsic race
	 * condition: callbacks we रेजिस्टर can be executed at once, beक्रमe we have
	 * initialized the काष्ठा aपंचांग_dev.  To protect against this, all callbacks
	 * पात अगर aपंचांग_dev->dev_data is शून्य. */
	aपंचांग_dev = aपंचांग_dev_रेजिस्टर(instance->driver_name,
				   &instance->usb_पूर्णांकf->dev, &usbaपंचांग_aपंचांग_devops,
				   -1, शून्य);
	अगर (!aपंचांग_dev) अणु
		usb_err(instance, "%s: failed to register ATM device!\n", __func__);
		वापस -1;
	पूर्ण

	instance->aपंचांग_dev = aपंचांग_dev;

	aपंचांग_dev->ci_range.vpi_bits = ATM_CI_MAX;
	aपंचांग_dev->ci_range.vci_bits = ATM_CI_MAX;
	aपंचांग_dev->संकेत = ATM_PHY_SIG_UNKNOWN;

	/* temp init ATM device, set to 128kbit */
	aपंचांग_dev->link_rate = 128 * 1000 / 424;

	अगर (instance->driver->aपंचांग_start && ((ret = instance->driver->aपंचांग_start(instance, aपंचांग_dev)) < 0)) अणु
		aपंचांग_err(instance, "%s: atm_start failed: %d!\n", __func__, ret);
		जाओ fail;
	पूर्ण

	usbaपंचांग_get_instance(instance);	/* dropped in usbaपंचांग_aपंचांग_dev_बंद */

	/* पढ़ोy क्रम ATM callbacks */
	mb();
	aपंचांग_dev->dev_data = instance;

	/* submit all rx URBs */
	क्रम (i = 0; i < num_rcv_urbs; i++)
		usbaपंचांग_submit_urb(instance->urbs[i]);

	वापस 0;

 fail:
	instance->aपंचांग_dev = शून्य;
	aपंचांग_dev_deरेजिस्टर(aपंचांग_dev); /* usbaपंचांग_aपंचांग_dev_बंद will eventually be called */
	वापस ret;
पूर्ण


/**********
**  USB  **
**********/

अटल पूर्णांक usbaपंचांग_करो_heavy_init(व्योम *arg)
अणु
	काष्ठा usbaपंचांग_data *instance = arg;
	पूर्णांक ret;

	allow_संकेत(संक_इति);
	complete(&instance->thपढ़ो_started);

	ret = instance->driver->heavy_init(instance, instance->usb_पूर्णांकf);

	अगर (!ret)
		ret = usbaपंचांग_aपंचांग_init(instance);

	mutex_lock(&instance->serialize);
	instance->thपढ़ो = शून्य;
	mutex_unlock(&instance->serialize);

	complete_and_निकास(&instance->thपढ़ो_निकासed, ret);
पूर्ण

अटल पूर्णांक usbaपंचांग_heavy_init(काष्ठा usbaपंचांग_data *instance)
अणु
	काष्ठा task_काष्ठा *t;

	t = kthपढ़ो_create(usbaपंचांग_करो_heavy_init, instance, "%s",
			instance->driver->driver_name);
	अगर (IS_ERR(t)) अणु
		usb_err(instance, "%s: failed to create kernel_thread (%ld)!\n",
				__func__, PTR_ERR(t));
		वापस PTR_ERR(t);
	पूर्ण

	instance->thपढ़ो = t;
	wake_up_process(t);
	रुको_क्रम_completion(&instance->thपढ़ो_started);

	वापस 0;
पूर्ण

अटल व्योम usbaपंचांग_tasklet_schedule(काष्ठा समयr_list *t)
अणु
	काष्ठा usbaपंचांग_channel *channel = from_समयr(channel, t, delay);

	tasklet_schedule(&channel->tasklet);
पूर्ण

अटल व्योम usbaपंचांग_init_channel(काष्ठा usbaपंचांग_channel *channel)
अणु
	spin_lock_init(&channel->lock);
	INIT_LIST_HEAD(&channel->list);
	समयr_setup(&channel->delay, usbaपंचांग_tasklet_schedule, 0);
पूर्ण

पूर्णांक usbaपंचांग_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id,
		     काष्ठा usbaपंचांग_driver *driver)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usbaपंचांग_data *instance;
	अक्षर *buf;
	पूर्णांक error = -ENOMEM;
	पूर्णांक i, length;
	अचिन्हित पूर्णांक maxpacket, num_packets;

	/* instance init */
	instance = kzalloc(माप(*instance) + माप(काष्ठा urb *) * (num_rcv_urbs + num_snd_urbs), GFP_KERNEL);
	अगर (!instance)
		वापस -ENOMEM;

	/* खुला fields */

	instance->driver = driver;
	strlcpy(instance->driver_name, driver->driver_name,
		माप(instance->driver_name));

	instance->usb_dev = usb_dev;
	instance->usb_पूर्णांकf = पूर्णांकf;

	buf = instance->description;
	length = माप(instance->description);

	अगर ((i = usb_string(usb_dev, usb_dev->descriptor.iProduct, buf, length)) < 0)
		जाओ bind;

	buf += i;
	length -= i;

	i = scnम_लिखो(buf, length, " (");
	buf += i;
	length -= i;

	अगर (length <= 0 || (i = usb_make_path(usb_dev, buf, length)) < 0)
		जाओ bind;

	buf += i;
	length -= i;

	snम_लिखो(buf, length, ")");

 bind:
	अगर (driver->bind && (error = driver->bind(instance, पूर्णांकf, id)) < 0) अणु
			dev_err(dev, "%s: bind failed: %d!\n", __func__, error);
			जाओ fail_मुक्त;
	पूर्ण

	/* निजी fields */

	kref_init(&instance->refcount);		/* dropped in usbaपंचांग_usb_disconnect */
	mutex_init(&instance->serialize);

	instance->thपढ़ो = शून्य;
	init_completion(&instance->thपढ़ो_started);
	init_completion(&instance->thपढ़ो_निकासed);

	INIT_LIST_HEAD(&instance->vcc_list);
	skb_queue_head_init(&instance->sndqueue);

	usbaपंचांग_init_channel(&instance->rx_channel);
	usbaपंचांग_init_channel(&instance->tx_channel);
	tasklet_setup(&instance->rx_channel.tasklet, usbaपंचांग_rx_process);
	tasklet_setup(&instance->tx_channel.tasklet, usbaपंचांग_tx_process);
	instance->rx_channel.stride = ATM_CELL_SIZE + driver->rx_padding;
	instance->tx_channel.stride = ATM_CELL_SIZE + driver->tx_padding;
	instance->rx_channel.usbaपंचांग = instance->tx_channel.usbaपंचांग = instance;

	अगर ((instance->flags & UDSL_USE_ISOC) && driver->isoc_in)
		instance->rx_channel.endpoपूर्णांक = usb_rcvisocpipe(usb_dev, driver->isoc_in);
	अन्यथा
		instance->rx_channel.endpoपूर्णांक = usb_rcvbulkpipe(usb_dev, driver->bulk_in);

	instance->tx_channel.endpoपूर्णांक = usb_sndbulkpipe(usb_dev, driver->bulk_out);

	/* tx buffer size must be a positive multiple of the stride */
	instance->tx_channel.buf_size = max(instance->tx_channel.stride,
			snd_buf_bytes - (snd_buf_bytes % instance->tx_channel.stride));

	/* rx buffer size must be a positive multiple of the endpoपूर्णांक maxpacket */
	maxpacket = usb_maxpacket(usb_dev, instance->rx_channel.endpoपूर्णांक, 0);

	अगर ((maxpacket < 1) || (maxpacket > UDSL_MAX_BUF_SIZE)) अणु
		dev_err(dev, "%s: invalid endpoint %02x!\n", __func__,
				usb_pipeendpoपूर्णांक(instance->rx_channel.endpoपूर्णांक));
		error = -EINVAL;
		जाओ fail_unbind;
	पूर्ण

	num_packets = max(1U, (rcv_buf_bytes + maxpacket / 2) / maxpacket); /* round */

	अगर (num_packets * maxpacket > UDSL_MAX_BUF_SIZE)
		num_packets--;

	instance->rx_channel.buf_size = num_packets * maxpacket;
	instance->rx_channel.packet_size = maxpacket;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा usbaपंचांग_channel *channel = i ?
			&instance->tx_channel : &instance->rx_channel;

		dev_dbg(dev, "%s: using %d byte buffer for %s channel 0x%p\n",
			__func__, channel->buf_size, i ? "tx" : "rx", channel);
	पूर्ण

	/* initialize urbs */

	क्रम (i = 0; i < num_rcv_urbs + num_snd_urbs; i++) अणु
		u8 *buffer;
		काष्ठा usbaपंचांग_channel *channel = i < num_rcv_urbs ?
			&instance->rx_channel : &instance->tx_channel;
		काष्ठा urb *urb;
		अचिन्हित पूर्णांक iso_packets = usb_pipeisoc(channel->endpoपूर्णांक) ? channel->buf_size / channel->packet_size : 0;

		urb = usb_alloc_urb(iso_packets, GFP_KERNEL);
		अगर (!urb) अणु
			error = -ENOMEM;
			जाओ fail_unbind;
		पूर्ण

		instance->urbs[i] = urb;

		/* zero the tx padding to aव्योम leaking inक्रमmation */
		buffer = kzalloc(channel->buf_size, GFP_KERNEL);
		अगर (!buffer) अणु
			error = -ENOMEM;
			जाओ fail_unbind;
		पूर्ण

		usb_fill_bulk_urb(urb, instance->usb_dev, channel->endpoपूर्णांक,
				  buffer, channel->buf_size, usbaपंचांग_complete, channel);
		अगर (iso_packets) अणु
			पूर्णांक j;
			urb->पूर्णांकerval = 1;
			urb->transfer_flags = URB_ISO_ASAP;
			urb->number_of_packets = iso_packets;
			क्रम (j = 0; j < iso_packets; j++) अणु
				urb->iso_frame_desc[j].offset = channel->packet_size * j;
				urb->iso_frame_desc[j].length = channel->packet_size;
			पूर्ण
		पूर्ण

		/* put all tx URBs on the list of spares */
		अगर (i >= num_rcv_urbs)
			list_add_tail(&urb->urb_list, &channel->list);

		vdbg(&पूर्णांकf->dev, "%s: alloced buffer 0x%p buf size %u urb 0x%p",
		     __func__, urb->transfer_buffer, urb->transfer_buffer_length, urb);
	पूर्ण

	instance->cached_vpi = ATM_VPI_UNSPEC;
	instance->cached_vci = ATM_VCI_UNSPEC;
	instance->cell_buf = kदो_स्मृति(instance->rx_channel.stride, GFP_KERNEL);

	अगर (!instance->cell_buf) अणु
		error = -ENOMEM;
		जाओ fail_unbind;
	पूर्ण

	अगर (!(instance->flags & UDSL_SKIP_HEAVY_INIT) && driver->heavy_init) अणु
		error = usbaपंचांग_heavy_init(instance);
	पूर्ण अन्यथा अणु
		complete(&instance->thपढ़ो_निकासed);	/* pretend that heavy_init was run */
		error = usbaपंचांग_aपंचांग_init(instance);
	पूर्ण

	अगर (error < 0)
		जाओ fail_unbind;

	usb_get_dev(usb_dev);
	usb_set_पूर्णांकfdata(पूर्णांकf, instance);

	वापस 0;

 fail_unbind:
	अगर (instance->driver->unbind)
		instance->driver->unbind(instance, पूर्णांकf);
 fail_मुक्त:
	kमुक्त(instance->cell_buf);

	क्रम (i = 0; i < num_rcv_urbs + num_snd_urbs; i++) अणु
		अगर (instance->urbs[i])
			kमुक्त(instance->urbs[i]->transfer_buffer);
		usb_मुक्त_urb(instance->urbs[i]);
	पूर्ण

	kमुक्त(instance);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(usbaपंचांग_usb_probe);

व्योम usbaपंचांग_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usbaपंचांग_data *instance = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbaपंचांग_vcc_data *vcc_data;
	पूर्णांक i;

	अगर (!instance) अणु
		dev_dbg(dev, "%s: NULL instance!\n", __func__);
		वापस;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	mutex_lock(&instance->serialize);
	instance->disconnected = 1;
	अगर (instance->thपढ़ो != शून्य)
		send_sig(संक_इति, instance->thपढ़ो, 1);
	mutex_unlock(&instance->serialize);

	रुको_क्रम_completion(&instance->thपढ़ो_निकासed);

	mutex_lock(&instance->serialize);
	list_क्रम_each_entry(vcc_data, &instance->vcc_list, list)
		vcc_release_async(vcc_data->vcc, -EPIPE);
	mutex_unlock(&instance->serialize);

	tasklet_disable(&instance->rx_channel.tasklet);
	tasklet_disable(&instance->tx_channel.tasklet);

	क्रम (i = 0; i < num_rcv_urbs + num_snd_urbs; i++)
		usb_समाप्त_urb(instance->urbs[i]);

	del_समयr_sync(&instance->rx_channel.delay);
	del_समयr_sync(&instance->tx_channel.delay);

	/* turn usbaपंचांग_[rt]x_process पूर्णांकo something बंद to a no-op */
	/* no need to take the spinlock */
	INIT_LIST_HEAD(&instance->rx_channel.list);
	INIT_LIST_HEAD(&instance->tx_channel.list);

	tasklet_enable(&instance->rx_channel.tasklet);
	tasklet_enable(&instance->tx_channel.tasklet);

	अगर (instance->aपंचांग_dev && instance->driver->aपंचांग_stop)
		instance->driver->aपंचांग_stop(instance, instance->aपंचांग_dev);

	अगर (instance->driver->unbind)
		instance->driver->unbind(instance, पूर्णांकf);

	instance->driver_data = शून्य;

	क्रम (i = 0; i < num_rcv_urbs + num_snd_urbs; i++) अणु
		kमुक्त(instance->urbs[i]->transfer_buffer);
		usb_मुक्त_urb(instance->urbs[i]);
	पूर्ण

	kमुक्त(instance->cell_buf);

	/* ATM finalize */
	अगर (instance->aपंचांग_dev) अणु
		aपंचांग_dev_deरेजिस्टर(instance->aपंचांग_dev);
		instance->aपंचांग_dev = शून्य;
	पूर्ण

	usbaपंचांग_put_instance(instance);	/* taken in usbaपंचांग_usb_probe */
पूर्ण
EXPORT_SYMBOL_GPL(usbaपंचांग_usb_disconnect);


/***********
**  init  **
***********/

अटल पूर्णांक __init usbaपंचांग_usb_init(व्योम)
अणु
	अगर (माप(काष्ठा usbaपंचांग_control) > माप_field(काष्ठा sk_buff, cb)) अणु
		pr_err("%s unusable with this kernel!\n", usbaपंचांग_driver_name);
		वापस -EIO;
	पूर्ण

	अगर ((num_rcv_urbs > UDSL_MAX_RCV_URBS)
	    || (num_snd_urbs > UDSL_MAX_SND_URBS)
	    || (rcv_buf_bytes < 1)
	    || (rcv_buf_bytes > UDSL_MAX_BUF_SIZE)
	    || (snd_buf_bytes < 1)
	    || (snd_buf_bytes > UDSL_MAX_BUF_SIZE))
		वापस -EINVAL;

	वापस 0;
पूर्ण
module_init(usbaपंचांग_usb_init);

अटल व्योम __निकास usbaपंचांग_usb_निकास(व्योम)
अणु
पूर्ण
module_निकास(usbaपंचांग_usb_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/************
**  debug  **
************/

#अगर_घोषित VERBOSE_DEBUG
अटल पूर्णांक usbaपंचांग_prपूर्णांक_packet(काष्ठा usbaपंचांग_data *instance,
			       स्थिर अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	अचिन्हित अक्षर buffer[256];
	पूर्णांक i = 0, j = 0;

	क्रम (i = 0; i < len;) अणु
		buffer[0] = '\0';
		प्र_लिखो(buffer, "%.3d :", i);
		क्रम (j = 0; (j < 16) && (i < len); j++, i++)
			प्र_लिखो(buffer, "%s %2.2x", buffer, data[i]);
		dev_dbg(&instance->usb_पूर्णांकf->dev, "%s", buffer);
	पूर्ण
	वापस i;
पूर्ण
#पूर्ण_अगर
