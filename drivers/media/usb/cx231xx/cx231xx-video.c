<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx-video.c - driver क्रम Conexant Cx23100/101/102
		     USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
	Based on em28xx driver
	Based on cx23885 driver
	Based on cx88 driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/tuner.h>

#समावेश <media/dvb_frontend.h>

#समावेश "cx231xx-vbi.h"

#घोषणा CX231XX_VERSION "0.0.3"

#घोषणा DRIVER_AUTHOR   "Srinivasa Deevi <srinivasa.deevi@conexant.com>"
#घोषणा DRIVER_DESC     "Conexant cx231xx based USB video device driver"

#घोषणा cx231xx_videodbg(fmt, arg...) करो अणु\
	अगर (video_debug) \
		prपूर्णांकk(KERN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##arg); पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक isoc_debug;
module_param(isoc_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(isoc_debug, "enable debug messages [isoc transfers]");

#घोषणा cx231xx_isocdbg(fmt, arg...) \
करो अणु\
	अगर (isoc_debug) अणु \
		prपूर्णांकk(KERN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##arg); \
	पूर्ण \
  पूर्ण जबतक (0)

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(CX231XX_VERSION);

अटल अचिन्हित पूर्णांक card[]     = अणु[0 ... (CX231XX_MAXBOARDS - 1)] = -1U पूर्ण;
अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (CX231XX_MAXBOARDS - 1)] = -1U पूर्ण;
अटल अचिन्हित पूर्णांक vbi_nr[]   = अणु[0 ... (CX231XX_MAXBOARDS - 1)] = -1U पूर्ण;
अटल अचिन्हित पूर्णांक radio_nr[] = अणु[0 ... (CX231XX_MAXBOARDS - 1)] = -1U पूर्ण;

module_param_array(card, पूर्णांक, शून्य, 0444);
module_param_array(video_nr, पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr, पूर्णांक, शून्य, 0444);
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(card, "card type");
MODULE_PARM_DESC(video_nr, "video device numbers");
MODULE_PARM_DESC(vbi_nr, "vbi device numbers");
MODULE_PARM_DESC(radio_nr, "radio device numbers");

अटल अचिन्हित पूर्णांक video_debug;
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug, "enable debug messages [video]");

/* supported video standards */
अटल काष्ठा cx231xx_fmt क्रमmat[] = अणु
	अणु
	 .fourcc = V4L2_PIX_FMT_YUYV,
	 .depth = 16,
	 .reg = 0,
	 पूर्ण,
पूर्ण;


अटल पूर्णांक cx231xx_enable_analog_tuner(काष्ठा cx231xx *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev = dev->media_dev;
	काष्ठा media_entity  *entity, *decoder = शून्य, *source;
	काष्ठा media_link *link, *found_link = शून्य;
	पूर्णांक ret, active_links = 0;

	अगर (!mdev)
		वापस 0;

	/*
	 * This will find the tuner that is connected पूर्णांकo the decoder.
	 * Technically, this is not 100% correct, as the device may be
	 * using an analog input instead of the tuner. However, as we can't
	 * करो DVB streaming जबतक the DMA engine is being used क्रम V4L2,
	 * this should be enough क्रम the actual needs.
	 */
	media_device_क्रम_each_entity(entity, mdev) अणु
		अगर (entity->function == MEDIA_ENT_F_ATV_DECODER) अणु
			decoder = entity;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!decoder)
		वापस 0;

	list_क्रम_each_entry(link, &decoder->links, list) अणु
		अगर (link->sink->entity == decoder) अणु
			found_link = link;
			अगर (link->flags & MEDIA_LNK_FL_ENABLED)
				active_links++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (active_links == 1 || !found_link)
		वापस 0;

	source = found_link->source->entity;
	list_क्रम_each_entry(link, &source->links, list) अणु
		काष्ठा media_entity *sink;
		पूर्णांक flags = 0;

		sink = link->sink->entity;

		अगर (sink == entity)
			flags = MEDIA_LNK_FL_ENABLED;

		ret = media_entity_setup_link(link, flags);
		अगर (ret) अणु
			dev_err(dev->dev,
				"Couldn't change link %s->%s to %s. Error %d\n",
				source->name, sink->name,
				flags ? "enabled" : "disabled",
				ret);
			वापस ret;
		पूर्ण अन्यथा
			dev_dbg(dev->dev,
				"link %s->%s was %s\n",
				source->name, sink->name,
				flags ? "ENABLED" : "disabled");
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
	Video buffer and parser functions
   ------------------------------------------------------------------*/

/*
 * Announces that a buffer were filled and request the next
 */
अटल अंतरभूत व्योम buffer_filled(काष्ठा cx231xx *dev,
				 काष्ठा cx231xx_dmaqueue *dma_q,
				 काष्ठा cx231xx_buffer *buf)
अणु
	/* Advice that buffer was filled */
	cx231xx_isocdbg("[%p/%d] wakeup\n", buf, buf->vb.vb2_buf.index);
	buf->vb.sequence = dma_q->sequence++;
	buf->vb.field = V4L2_FIELD_INTERLACED;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, dev->size);

	अगर (dev->USE_ISO)
		dev->video_mode.isoc_ctl.buf = शून्य;
	अन्यथा
		dev->video_mode.bulk_ctl.buf = शून्य;

	list_del(&buf->list);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा cx231xx *dev, पूर्णांक packet, पूर्णांक status)
अणु
	अक्षर *errmsg = "Unknown";

	चयन (status) अणु
	हाल -ENOENT:
		errmsg = "unlinked synchronously";
		अवरोध;
	हाल -ECONNRESET:
		errmsg = "unlinked asynchronously";
		अवरोध;
	हाल -ENOSR:
		errmsg = "Buffer error (overrun)";
		अवरोध;
	हाल -EPIPE:
		errmsg = "Stalled (device not responding)";
		अवरोध;
	हाल -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		अवरोध;
	हाल -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		अवरोध;
	हाल -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		अवरोध;
	हाल -ETIME:
		errmsg = "Device does not respond";
		अवरोध;
	पूर्ण
	अगर (packet < 0) अणु
		cx231xx_isocdbg("URB status %d [%s].\n", status, errmsg);
	पूर्ण अन्यथा अणु
		cx231xx_isocdbg("URB packet %d, status %d [%s].\n",
				packet, status, errmsg);
	पूर्ण
पूर्ण

/*
 * video-buf generic routine to get the next available buffer
 */
अटल अंतरभूत व्योम get_next_buf(काष्ठा cx231xx_dmaqueue *dma_q,
				काष्ठा cx231xx_buffer **buf)
अणु
	काष्ठा cx231xx_video_mode *vmode =
	    container_of(dma_q, काष्ठा cx231xx_video_mode, vidq);
	काष्ठा cx231xx *dev = container_of(vmode, काष्ठा cx231xx, video_mode);

	अक्षर *outp;

	अगर (list_empty(&dma_q->active)) अणु
		cx231xx_isocdbg("No active queue to serve\n");
		अगर (dev->USE_ISO)
			dev->video_mode.isoc_ctl.buf = शून्य;
		अन्यथा
			dev->video_mode.bulk_ctl.buf = शून्य;
		*buf = शून्य;
		वापस;
	पूर्ण

	/* Get the next buffer */
	*buf = list_entry(dma_q->active.next, काष्ठा cx231xx_buffer, list);

	/* Cleans up buffer - Useful क्रम testing क्रम frame/URB loss */
	outp = vb2_plane_vaddr(&(*buf)->vb.vb2_buf, 0);
	स_रखो(outp, 0, dev->size);

	अगर (dev->USE_ISO)
		dev->video_mode.isoc_ctl.buf = *buf;
	अन्यथा
		dev->video_mode.bulk_ctl.buf = *buf;

	वापस;
पूर्ण

/*
 * Controls the isoc copy of each urb packet
 */
अटल अंतरभूत पूर्णांक cx231xx_isoc_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	पूर्णांक i;
	अचिन्हित अक्षर *p_buffer;
	u32 bytes_parsed = 0, buffer_size = 0;
	u8 sav_eav = 0;

	अगर (!dev)
		वापस 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		पूर्णांक status = urb->iso_frame_desc[i].status;

		अगर (status < 0) अणु
			prपूर्णांक_err_status(dev, i, status);
			अगर (urb->iso_frame_desc[i].status != -EPROTO)
				जारी;
		पूर्ण

		अगर (urb->iso_frame_desc[i].actual_length <= 0) अणु
			/* cx231xx_isocdbg("packet %d is empty",i); - spammy */
			जारी;
		पूर्ण
		अगर (urb->iso_frame_desc[i].actual_length >
		    dev->video_mode.max_pkt_size) अणु
			cx231xx_isocdbg("packet bigger than packet size");
			जारी;
		पूर्ण

		/*  get buffer poपूर्णांकer and length */
		p_buffer = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		buffer_size = urb->iso_frame_desc[i].actual_length;
		bytes_parsed = 0;

		अगर (dma_q->is_partial_line) अणु
			/* Handle the हाल of a partial line */
			sav_eav = dma_q->last_sav;
		पूर्ण अन्यथा अणु
			/* Check क्रम a SAV/EAV overlapping
				the buffer boundary */
			sav_eav =
			    cx231xx_find_boundary_SAV_EAV(p_buffer,
							  dma_q->partial_buf,
							  &bytes_parsed);
		पूर्ण

		sav_eav &= 0xF0;
		/* Get the first line अगर we have some portion of an SAV/EAV from
		   the last buffer or a partial line  */
		अगर (sav_eav) अणु
			bytes_parsed += cx231xx_get_video_line(dev, dma_q,
				sav_eav,	/* SAV/EAV */
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed);/* buf size */
		पूर्ण

		/* Now parse data that is completely in this buffer */
		/* dma_q->is_partial_line = 0;  */

		जबतक (bytes_parsed < buffer_size) अणु
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed,	/* buf size */
				&bytes_used);/* bytes used to get SAV/EAV */

			bytes_parsed += bytes_used;

			sav_eav &= 0xF0;
			अगर (sav_eav && (bytes_parsed < buffer_size)) अणु
				bytes_parsed += cx231xx_get_video_line(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffer + bytes_parsed,/* p_buffer */
					buffer_size - bytes_parsed);/*buf size*/
			पूर्ण
		पूर्ण

		/* Save the last four bytes of the buffer so we can check the
		   buffer boundary condition next समय */
		स_नकल(dma_q->partial_buf, p_buffer + buffer_size - 4, 4);
		bytes_parsed = 0;

	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक cx231xx_bulk_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	अचिन्हित अक्षर *p_buffer;
	u32 bytes_parsed = 0, buffer_size = 0;
	u8 sav_eav = 0;

	अगर (!dev)
		वापस 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस 0;

	अगर (urb->status < 0) अणु
		prपूर्णांक_err_status(dev, -1, urb->status);
		अगर (urb->status == -ENOENT)
			वापस 0;
	पूर्ण

	अगर (1) अणु

		/*  get buffer poपूर्णांकer and length */
		p_buffer = urb->transfer_buffer;
		buffer_size = urb->actual_length;
		bytes_parsed = 0;

		अगर (dma_q->is_partial_line) अणु
			/* Handle the हाल of a partial line */
			sav_eav = dma_q->last_sav;
		पूर्ण अन्यथा अणु
			/* Check क्रम a SAV/EAV overlapping
				the buffer boundary */
			sav_eav =
			    cx231xx_find_boundary_SAV_EAV(p_buffer,
							  dma_q->partial_buf,
							  &bytes_parsed);
		पूर्ण

		sav_eav &= 0xF0;
		/* Get the first line अगर we have some portion of an SAV/EAV from
		   the last buffer or a partial line  */
		अगर (sav_eav) अणु
			bytes_parsed += cx231xx_get_video_line(dev, dma_q,
				sav_eav,	/* SAV/EAV */
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed);/* buf size */
		पूर्ण

		/* Now parse data that is completely in this buffer */
		/* dma_q->is_partial_line = 0;  */

		जबतक (bytes_parsed < buffer_size) अणु
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed,	/* buf size */
				&bytes_used);/* bytes used to get SAV/EAV */

			bytes_parsed += bytes_used;

			sav_eav &= 0xF0;
			अगर (sav_eav && (bytes_parsed < buffer_size)) अणु
				bytes_parsed += cx231xx_get_video_line(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffer + bytes_parsed,/* p_buffer */
					buffer_size - bytes_parsed);/*buf size*/
			पूर्ण
		पूर्ण

		/* Save the last four bytes of the buffer so we can check the
		   buffer boundary condition next समय */
		स_नकल(dma_q->partial_buf, p_buffer + buffer_size - 4, 4);
		bytes_parsed = 0;

	पूर्ण
	वापस 1;
पूर्ण


u8 cx231xx_find_boundary_SAV_EAV(u8 *p_buffer, u8 *partial_buf,
				 u32 *p_bytes_used)
अणु
	u32 bytes_used;
	u8 boundary_bytes[8];
	u8 sav_eav = 0;

	*p_bytes_used = 0;

	/* Create an array of the last 4 bytes of the last buffer and the first
	   4 bytes of the current buffer. */

	स_नकल(boundary_bytes, partial_buf, 4);
	स_नकल(boundary_bytes + 4, p_buffer, 4);

	/* Check क्रम the SAV/EAV in the boundary buffer */
	sav_eav = cx231xx_find_next_SAV_EAV((u8 *)&boundary_bytes, 8,
					    &bytes_used);

	अगर (sav_eav) अणु
		/* found a boundary SAV/EAV.  Updates the bytes used to reflect
		   only those used in the new buffer */
		*p_bytes_used = bytes_used - 4;
	पूर्ण

	वापस sav_eav;
पूर्ण

u8 cx231xx_find_next_SAV_EAV(u8 *p_buffer, u32 buffer_size, u32 *p_bytes_used)
अणु
	u32 i;
	u8 sav_eav = 0;

	/*
	 * Don't search अगर the buffer size is less than 4.  It causes a page
	 * fault since buffer_size - 4 evaluates to a large number in that
	 * हाल.
	 */
	अगर (buffer_size < 4) अणु
		*p_bytes_used = buffer_size;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < (buffer_size - 3); i++) अणु

		अगर ((p_buffer[i] == 0xFF) &&
		    (p_buffer[i + 1] == 0x00) && (p_buffer[i + 2] == 0x00)) अणु

			*p_bytes_used = i + 4;
			sav_eav = p_buffer[i + 3];
			वापस sav_eav;
		पूर्ण
	पूर्ण

	*p_bytes_used = buffer_size;
	वापस 0;
पूर्ण

u32 cx231xx_get_video_line(काष्ठा cx231xx *dev,
			   काष्ठा cx231xx_dmaqueue *dma_q, u8 sav_eav,
			   u8 *p_buffer, u32 buffer_size)
अणु
	u32 bytes_copied = 0;
	पूर्णांक current_field = -1;

	चयन (sav_eav) अणु
	हाल SAV_ACTIVE_VIDEO_FIELD1:
		/* looking क्रम skipped line which occurred in PAL 720x480 mode.
		   In this हाल, there will be no active data contained
		   between the SAV and EAV */
		अगर ((buffer_size > 3) && (p_buffer[0] == 0xFF) &&
		    (p_buffer[1] == 0x00) && (p_buffer[2] == 0x00) &&
		    ((p_buffer[3] == EAV_ACTIVE_VIDEO_FIELD1) ||
		     (p_buffer[3] == EAV_ACTIVE_VIDEO_FIELD2) ||
		     (p_buffer[3] == EAV_VBLANK_FIELD1) ||
		     (p_buffer[3] == EAV_VBLANK_FIELD2)))
			वापस bytes_copied;
		current_field = 1;
		अवरोध;

	हाल SAV_ACTIVE_VIDEO_FIELD2:
		/* looking क्रम skipped line which occurred in PAL 720x480 mode.
		   In this हाल, there will be no active data contained between
		   the SAV and EAV */
		अगर ((buffer_size > 3) && (p_buffer[0] == 0xFF) &&
		    (p_buffer[1] == 0x00) && (p_buffer[2] == 0x00) &&
		    ((p_buffer[3] == EAV_ACTIVE_VIDEO_FIELD1) ||
		     (p_buffer[3] == EAV_ACTIVE_VIDEO_FIELD2) ||
		     (p_buffer[3] == EAV_VBLANK_FIELD1)       ||
		     (p_buffer[3] == EAV_VBLANK_FIELD2)))
			वापस bytes_copied;
		current_field = 2;
		अवरोध;
	पूर्ण

	dma_q->last_sav = sav_eav;

	bytes_copied = cx231xx_copy_video_line(dev, dma_q, p_buffer,
					       buffer_size, current_field);

	वापस bytes_copied;
पूर्ण

u32 cx231xx_copy_video_line(काष्ठा cx231xx *dev,
			    काष्ठा cx231xx_dmaqueue *dma_q, u8 *p_line,
			    u32 length, पूर्णांक field_number)
अणु
	u32 bytes_to_copy;
	काष्ठा cx231xx_buffer *buf;
	u32 _line_size = dev->width * 2;

	अगर (dma_q->current_field != field_number)
		cx231xx_reset_video_buffer(dev, dma_q);

	/* get the buffer poपूर्णांकer */
	अगर (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctl.buf;
	अन्यथा
		buf = dev->video_mode.bulk_ctl.buf;

	/* Remember the field number क्रम next समय */
	dma_q->current_field = field_number;

	bytes_to_copy = dma_q->bytes_left_in_line;
	अगर (bytes_to_copy > length)
		bytes_to_copy = length;

	अगर (dma_q->lines_completed >= dma_q->lines_per_field) अणु
		dma_q->bytes_left_in_line -= bytes_to_copy;
		dma_q->is_partial_line = (dma_q->bytes_left_in_line == 0) ?
					  0 : 1;
		वापस 0;
	पूर्ण

	dma_q->is_partial_line = 1;

	/* If we करोn't have a buffer, just वापस the number of bytes we would
	   have copied अगर we had a buffer. */
	अगर (!buf) अणु
		dma_q->bytes_left_in_line -= bytes_to_copy;
		dma_q->is_partial_line = (dma_q->bytes_left_in_line == 0)
					 ? 0 : 1;
		वापस bytes_to_copy;
	पूर्ण

	/* copy the data to video buffer */
	cx231xx_करो_copy(dev, dma_q, p_line, bytes_to_copy);

	dma_q->pos += bytes_to_copy;
	dma_q->bytes_left_in_line -= bytes_to_copy;

	अगर (dma_q->bytes_left_in_line == 0) अणु
		dma_q->bytes_left_in_line = _line_size;
		dma_q->lines_completed++;
		dma_q->is_partial_line = 0;

		अगर (cx231xx_is_buffer_करोne(dev, dma_q) && buf) अणु
			buffer_filled(dev, dma_q, buf);

			dma_q->pos = 0;
			buf = शून्य;
			dma_q->lines_completed = 0;
		पूर्ण
	पूर्ण

	वापस bytes_to_copy;
पूर्ण

व्योम cx231xx_reset_video_buffer(काष्ठा cx231xx *dev,
				काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	काष्ठा cx231xx_buffer *buf;

	/* handle the चयन from field 1 to field 2 */
	अगर (dma_q->current_field == 1) अणु
		अगर (dma_q->lines_completed >= dma_q->lines_per_field)
			dma_q->field1_करोne = 1;
		अन्यथा
			dma_q->field1_करोne = 0;
	पूर्ण

	अगर (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctl.buf;
	अन्यथा
		buf = dev->video_mode.bulk_ctl.buf;

	अगर (buf == शून्य) अणु
		/* first try to get the buffer */
		get_next_buf(dma_q, &buf);

		dma_q->pos = 0;
		dma_q->field1_करोne = 0;
		dma_q->current_field = -1;
	पूर्ण

	/* reset the counters */
	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_completed = 0;
पूर्ण

पूर्णांक cx231xx_करो_copy(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
		    u8 *p_buffer, u32 bytes_to_copy)
अणु
	u8 *p_out_buffer = शून्य;
	u32 current_line_bytes_copied = 0;
	काष्ठा cx231xx_buffer *buf;
	u32 _line_size = dev->width << 1;
	व्योम *startग_लिखो;
	पूर्णांक offset, lencopy;

	अगर (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctl.buf;
	अन्यथा
		buf = dev->video_mode.bulk_ctl.buf;

	अगर (buf == शून्य)
		वापस -1;

	p_out_buffer = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	current_line_bytes_copied = _line_size - dma_q->bytes_left_in_line;

	/* Offset field 2 one line from the top of the buffer */
	offset = (dma_q->current_field == 1) ? 0 : _line_size;

	/* Offset क्रम field 2 */
	startग_लिखो = p_out_buffer + offset;

	/* lines alपढ़ोy completed in the current field */
	startग_लिखो += (dma_q->lines_completed * _line_size * 2);

	/* bytes alपढ़ोy completed in the current line */
	startग_लिखो += current_line_bytes_copied;

	lencopy = dma_q->bytes_left_in_line > bytes_to_copy ?
		  bytes_to_copy : dma_q->bytes_left_in_line;

	अगर ((u8 *)(startग_लिखो + lencopy) > (u8 *)(p_out_buffer + dev->size))
		वापस 0;

	/* The below copies the UYVY data straight पूर्णांकo video buffer */
	cx231xx_swab((u16 *) p_buffer, (u16 *) startग_लिखो, (u16) lencopy);

	वापस 0;
पूर्ण

व्योम cx231xx_swab(u16 *from, u16 *to, u16 len)
अणु
	u16 i;

	अगर (len <= 0)
		वापस;

	क्रम (i = 0; i < len / 2; i++)
		to[i] = (from[i] << 8) | (from[i] >> 8);
पूर्ण

u8 cx231xx_is_buffer_करोne(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	u8 buffer_complete = 0;

	/* Dual field stream */
	buffer_complete = ((dma_q->current_field == 2) &&
			   (dma_q->lines_completed >= dma_q->lines_per_field) &&
			    dma_q->field1_करोne);

	वापस buffer_complete;
पूर्ण

/* ------------------------------------------------------------------
	Videobuf operations
   ------------------------------------------------------------------*/

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);

	dev->size = (dev->width * dev->height * dev->क्रमmat->depth + 7) >> 3;

	अगर (vq->num_buffers + *nbuffers < CX231XX_MIN_BUF)
		*nbuffers = CX231XX_MIN_BUF - vq->num_buffers;

	अगर (*nplanes)
		वापस sizes[0] < dev->size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = dev->size;

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cx231xx_buffer *buf =
	    container_of(vb, काष्ठा cx231xx_buffer, vb.vb2_buf);
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा cx231xx *dev,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	काष्ठा cx231xx_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	अगर (dev->USE_ISO)
		dev->video_mode.isoc_ctl.buf = शून्य;
	अन्यथा
		dev->video_mode.bulk_ctl.buf = शून्य;
	list_क्रम_each_entry_safe(buf, node, &vidq->active, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	पूर्णांक ret = 0;

	vidq->sequence = 0;
	dev->mode_tv = 0;

	cx231xx_enable_analog_tuner(dev);
	अगर (dev->USE_ISO)
		ret = cx231xx_init_isoc(dev, CX231XX_NUM_PACKETS,
					CX231XX_NUM_BUFS,
					dev->video_mode.max_pkt_size,
					cx231xx_isoc_copy);
	अन्यथा
		ret = cx231xx_init_bulk(dev, CX231XX_NUM_PACKETS,
					CX231XX_NUM_BUFS,
					dev->video_mode.max_pkt_size,
					cx231xx_bulk_copy);
	अगर (ret)
		वापस_all_buffers(dev, VB2_BUF_STATE_QUEUED);
	call_all(dev, video, s_stream, 1);
	वापस ret;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);

	call_all(dev, video, s_stream, 0);
	वापस_all_buffers(dev, VB2_BUF_STATE_ERROR);
पूर्ण

अटल काष्ठा vb2_ops cx231xx_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/*********************  v4l2 पूर्णांकerface  **************************************/

व्योम video_mux(काष्ठा cx231xx *dev, पूर्णांक index)
अणु
	dev->video_input = index;
	dev->ctl_ainput = INPUT(index)->amux;

	cx231xx_set_video_input_mux(dev, index);

	cx25840_call(dev, video, s_routing, INPUT(index)->vmux, 0, 0);

	cx231xx_set_audio_input(dev, dev->ctl_ainput);

	dev_dbg(dev->dev, "video_mux : %d\n", index);

	/* करो mode control overrides अगर required */
	cx231xx_करो_mode_ctrl_overrides(dev);
पूर्ण

/* ------------------------------------------------------------------
	IOCTL vidioc handling
   ------------------------------------------------------------------*/

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.pixelक्रमmat = dev->क्रमmat->fourcc;
	f->fmt.pix.bytesperline = (dev->width * dev->क्रमmat->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * dev->height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	f->fmt.pix.field = V4L2_FIELD_INTERLACED;

	वापस 0;
पूर्ण

अटल काष्ठा cx231xx_fmt *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmat); i++)
		अगर (क्रमmat[i].fourcc == fourcc)
			वापस &क्रमmat[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	अचिन्हित पूर्णांक width = f->fmt.pix.width;
	अचिन्हित पूर्णांक height = f->fmt.pix.height;
	अचिन्हित पूर्णांक maxw = norm_maxw(dev);
	अचिन्हित पूर्णांक maxh = norm_maxh(dev);
	काष्ठा cx231xx_fmt *fmt;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		cx231xx_videodbg("Fourcc format (%08x) invalid.\n",
				 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* width must even because of the YUYV क्रमmat
	   height must be even because of पूर्णांकerlacing */
	v4l_bound_align_image(&width, 48, maxw, 1, &height, 32, maxh, 1, 0);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	f->fmt.pix.bytesperline = (width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक rc;

	rc = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (rc)
		वापस rc;

	अगर (vb2_is_busy(&dev->vidq)) अणु
		dev_err(dev->dev, "%s: queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/* set new image size */
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->क्रमmat = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	call_all(dev, pad, set_fmt, शून्य, &क्रमmat);
	v4l2_fill_pix_क्रमmat(&f->fmt.pix, &क्रमmat.क्रमmat);

	वापस rc;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	*id = dev->norm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	अगर (dev->norm == norm)
		वापस 0;

	अगर (vb2_is_busy(&dev->vidq))
		वापस -EBUSY;

	dev->norm = norm;

	/* Adjusts width/height, अगर needed */
	dev->width = 720;
	dev->height = (dev->norm & V4L2_STD_625_50) ? 576 : 480;

	call_all(dev, video, s_std, dev->norm);

	/* We need to reset basic properties in the decoder related to
	   resolution (since a standard change effects things like the number
	   of lines in VACT, etc) */
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	क्रमmat.क्रमmat.width = dev->width;
	क्रमmat.क्रमmat.height = dev->height;
	call_all(dev, pad, set_fmt, शून्य, &क्रमmat);

	/* करो mode control overrides */
	cx231xx_करो_mode_ctrl_overrides(dev);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *iname[] = अणु
	[CX231XX_VMUX_COMPOSITE1] = "Composite1",
	[CX231XX_VMUX_SVIDEO]     = "S-Video",
	[CX231XX_VMUX_TELEVISION] = "Television",
	[CX231XX_VMUX_CABLE]      = "Cable TV",
	[CX231XX_VMUX_DVB]        = "DVB",
पूर्ण;

व्योम cx231xx_v4l2_create_entities(काष्ठा cx231xx *dev)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	पूर्णांक ret, i;

	/* Create entities क्रम each input connector */
	क्रम (i = 0; i < MAX_CX231XX_INPUT; i++) अणु
		काष्ठा media_entity *ent = &dev->input_ent[i];

		अगर (!INPUT(i)->type)
			अवरोध;

		ent->name = iname[INPUT(i)->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		चयन (INPUT(i)->type) अणु
		हाल CX231XX_VMUX_COMPOSITE1:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			अवरोध;
		हाल CX231XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			अवरोध;
		हाल CX231XX_VMUX_TELEVISION:
		हाल CX231XX_VMUX_CABLE:
		हाल CX231XX_VMUX_DVB:
			/* The DVB core will handle it */
			अगर (dev->tuner_type == TUNER_ABSENT)
				जारी;
			fallthrough;
		शेष: /* just to shut up a gcc warning */
			ent->function = MEDIA_ENT_F_CONN_RF;
			अवरोध;
		पूर्ण

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		अगर (ret < 0)
			pr_err("failed to initialize input pad[%d]!\n", i);

		ret = media_device_रेजिस्टर_entity(dev->media_dev, ent);
		अगर (ret < 0)
			pr_err("failed to register input entity %d!\n", i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक cx231xx_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	u32 gen_stat;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	n = i->index;
	अगर (n >= MAX_CX231XX_INPUT)
		वापस -EINVAL;
	अगर (0 == INPUT(n)->type)
		वापस -EINVAL;

	i->index = n;
	i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[INPUT(n)->type], माप(i->name));

	अगर ((CX231XX_VMUX_TELEVISION == INPUT(n)->type) ||
	    (CX231XX_VMUX_CABLE == INPUT(n)->type))
		i->type = V4L2_INPUT_TYPE_TUNER;

	i->std = dev->vdev.tvnorms;

	/* If they are asking about the active input, पढ़ो संकेत status */
	अगर (n == dev->video_input) अणु
		ret = cx231xx_पढ़ो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					    GEN_STAT, 2, &gen_stat, 4);
		अगर (ret > 0) अणु
			अगर ((gen_stat & FLD_VPRES) == 0x00)
				i->status |= V4L2_IN_ST_NO_SIGNAL;
			अगर ((gen_stat & FLD_HLOCK) == 0x00)
				i->status |= V4L2_IN_ST_NO_H_LOCK;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cx231xx_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	*i = dev->video_input;

	वापस 0;
पूर्ण

पूर्णांक cx231xx_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	dev->mode_tv = 0;

	अगर (i >= MAX_CX231XX_INPUT)
		वापस -EINVAL;
	अगर (0 == INPUT(i)->type)
		वापस -EINVAL;

	video_mux(dev, i);

	अगर (INPUT(i)->type == CX231XX_VMUX_TELEVISION ||
	    INPUT(i)->type == CX231XX_VMUX_CABLE) अणु
		/* There's a tuner, so reset the standard and put it on the
		   last known frequency (since it was probably घातered करोwn
		   until now */
		call_all(dev, video, s_std, dev->norm);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cx231xx_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (0 != t->index)
		वापस -EINVAL;

	strscpy(t->name, "Tuner", माप(t->name));

	t->type = V4L2_TUNER_ANALOG_TV;
	t->capability = V4L2_TUNER_CAP_NORM;
	t->rangehigh = 0xffffffffUL;
	t->संकेत = 0xffff;	/* LOCKED */
	call_all(dev, tuner, g_tuner, t);

	वापस 0;
पूर्ण

पूर्णांक cx231xx_s_tuner(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_tuner *t)
अणु
	अगर (0 != t->index)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक cx231xx_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;

	f->frequency = dev->ctl_freq;

	वापस 0;
पूर्ण

पूर्णांक cx231xx_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	काष्ठा v4l2_frequency new_freq = *f;
	पूर्णांक rc, need_अगर_freq = 0;
	u32 अगर_frequency = 5400000;

	dev_dbg(dev->dev,
		"Enter vidioc_s_frequency()f->frequency=%d;f->type=%d\n",
		f->frequency, f->type);

	अगर (0 != f->tuner)
		वापस -EINVAL;

	/* set pre channel change settings in DIF first */
	rc = cx231xx_tuner_pre_channel_change(dev);

	चयन (dev->model) अणु /* i2c device tuners */
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	हाल CX231XX_BOARD_HAUPPAUGE_975:
	हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
		अगर (dev->cx231xx_set_analog_freq)
			dev->cx231xx_set_analog_freq(dev, f->frequency);
		dev->ctl_freq = f->frequency;
		need_अगर_freq = 1;
		अवरोध;
	शेष:
		call_all(dev, tuner, s_frequency, f);
		call_all(dev, tuner, g_frequency, &new_freq);
		dev->ctl_freq = new_freq.frequency;
		अवरोध;
	पूर्ण

	pr_debug("%s() %u  :  %u\n", __func__, f->frequency, dev->ctl_freq);

	/* set post channel change settings in DIF first */
	rc = cx231xx_tuner_post_channel_change(dev);

	अगर (need_अगर_freq || dev->tuner_type == TUNER_NXP_TDA18271) अणु
		अगर (dev->norm & (V4L2_STD_MN | V4L2_STD_NTSC_443))
			अगर_frequency = 5400000;  /*5.4MHz	*/
		अन्यथा अगर (dev->norm & V4L2_STD_B)
			अगर_frequency = 6000000;  /*6.0MHz	*/
		अन्यथा अगर (dev->norm & (V4L2_STD_PAL_DK | V4L2_STD_SECAM_DK))
			अगर_frequency = 6900000;  /*6.9MHz	*/
		अन्यथा अगर (dev->norm & V4L2_STD_GH)
			अगर_frequency = 7100000;  /*7.1MHz	*/
		अन्यथा अगर (dev->norm & V4L2_STD_PAL_I)
			अगर_frequency = 7250000;  /*7.25MHz	*/
		अन्यथा अगर (dev->norm & V4L2_STD_SECAM_L)
			अगर_frequency = 6900000;  /*6.9MHz	*/
		अन्यथा अगर (dev->norm & V4L2_STD_SECAM_LC)
			अगर_frequency = 1250000;  /*1.25MHz	*/

		dev_dbg(dev->dev,
			"if_frequency is set to %d\n", अगर_frequency);
		cx231xx_set_Colibri_For_LowIF(dev, अगर_frequency, 1, 1);

		update_HH_रेजिस्टर_after_set_DIF(dev);
	पूर्ण

	dev_dbg(dev->dev, "Set New FREQUENCY to %d\n", f->frequency);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG

पूर्णांक cx231xx_g_chip_info(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_dbg_chip_info *chip)
अणु
	चयन (chip->match.addr) अणु
	हाल 0:	/* Cx231xx - पूर्णांकernal रेजिस्टरs */
		वापस 0;
	हाल 1:	/* AFE - पढ़ो byte */
		strscpy(chip->name, "AFE (byte)", माप(chip->name));
		वापस 0;
	हाल 2:	/* Video Block - पढ़ो byte */
		strscpy(chip->name, "Video (byte)", माप(chip->name));
		वापस 0;
	हाल 3:	/* I2S block - पढ़ो byte */
		strscpy(chip->name, "I2S (byte)", माप(chip->name));
		वापस 0;
	हाल 4: /* AFE - पढ़ो dword */
		strscpy(chip->name, "AFE (dword)", माप(chip->name));
		वापस 0;
	हाल 5: /* Video Block - पढ़ो dword */
		strscpy(chip->name, "Video (dword)", माप(chip->name));
		वापस 0;
	हाल 6: /* I2S Block - पढ़ो dword */
		strscpy(chip->name, "I2S (dword)", माप(chip->name));
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक cx231xx_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	पूर्णांक ret;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 data = 0;

	चयन (reg->match.addr) अणु
	हाल 0:	/* Cx231xx - पूर्णांकernal रेजिस्टरs */
		ret = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER,
				(u16)reg->reg, value, 4);
		reg->val = value[0] | value[1] << 8 |
			value[2] << 16 | (u32)value[3] << 24;
		reg->size = 4;
		अवरोध;
	हाल 1:	/* AFE - पढ़ो byte */
		ret = cx231xx_पढ़ो_i2c_data(dev, AFE_DEVICE_ADDRESS,
				(u16)reg->reg, 2, &data, 1);
		reg->val = data;
		reg->size = 1;
		अवरोध;
	हाल 2:	/* Video Block - पढ़ो byte */
		ret = cx231xx_पढ़ो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
				(u16)reg->reg, 2, &data, 1);
		reg->val = data;
		reg->size = 1;
		अवरोध;
	हाल 3:	/* I2S block - पढ़ो byte */
		ret = cx231xx_पढ़ो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				(u16)reg->reg, 1, &data, 1);
		reg->val = data;
		reg->size = 1;
		अवरोध;
	हाल 4: /* AFE - पढ़ो dword */
		ret = cx231xx_पढ़ो_i2c_data(dev, AFE_DEVICE_ADDRESS,
				(u16)reg->reg, 2, &data, 4);
		reg->val = data;
		reg->size = 4;
		अवरोध;
	हाल 5: /* Video Block - पढ़ो dword */
		ret = cx231xx_पढ़ो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
				(u16)reg->reg, 2, &data, 4);
		reg->val = data;
		reg->size = 4;
		अवरोध;
	हाल 6: /* I2S Block - पढ़ो dword */
		ret = cx231xx_पढ़ो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				(u16)reg->reg, 1, &data, 4);
		reg->val = data;
		reg->size = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret < 0 ? ret : 0;
पूर्ण

पूर्णांक cx231xx_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	पूर्णांक ret;
	u8 data[4] = अणु 0, 0, 0, 0 पूर्ण;

	चयन (reg->match.addr) अणु
	हाल 0:	/* cx231xx पूर्णांकernal रेजिस्टरs */
		data[0] = (u8) reg->val;
		data[1] = (u8) (reg->val >> 8);
		data[2] = (u8) (reg->val >> 16);
		data[3] = (u8) (reg->val >> 24);
		ret = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
				(u16)reg->reg, data, 4);
		अवरोध;
	हाल 1:	/* AFE - ग_लिखो byte */
		ret = cx231xx_ग_लिखो_i2c_data(dev, AFE_DEVICE_ADDRESS,
				(u16)reg->reg, 2, reg->val, 1);
		अवरोध;
	हाल 2:	/* Video Block - ग_लिखो byte */
		ret = cx231xx_ग_लिखो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
				(u16)reg->reg, 2, reg->val, 1);
		अवरोध;
	हाल 3:	/* I2S block - ग_लिखो byte */
		ret = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				(u16)reg->reg, 1, reg->val, 1);
		अवरोध;
	हाल 4: /* AFE - ग_लिखो dword */
		ret = cx231xx_ग_लिखो_i2c_data(dev, AFE_DEVICE_ADDRESS,
				(u16)reg->reg, 2, reg->val, 4);
		अवरोध;
	हाल 5: /* Video Block - ग_लिखो dword */
		ret = cx231xx_ग_लिखो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
				(u16)reg->reg, 2, reg->val, 4);
		अवरोध;
	हाल 6: /* I2S block - ग_लिखो dword */
		ret = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				(u16)reg->reg, 1, reg->val, 4);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret < 0 ? ret : 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vidioc_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	bool is_50hz = dev->norm & V4L2_STD_625_50;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f->numerator = is_50hz ? 54 : 11;
	f->denominator = is_50hz ? 59 : 10;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = dev->width;
		s->r.height = dev->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cx231xx_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	strscpy(cap->driver, "cx231xx", माप(cap->driver));
	strscpy(cap->card, cx231xx_boards[dev->model].name, माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	cap->capabilities = V4L2_CAP_READWRITE |
		V4L2_CAP_VBI_CAPTURE | V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_STREAMING | V4L2_CAP_DEVICE_CAPS;
	अगर (video_is_रेजिस्टरed(&dev->radio_dev))
		cap->capabilities |= V4L2_CAP_RADIO;

	चयन (dev->model) अणु
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	हाल CX231XX_BOARD_HAUPPAUGE_975:
	हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
		cap->capabilities |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			cap->capabilities |= V4L2_CAP_TUNER;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (unlikely(f->index >= ARRAY_SIZE(क्रमmat)))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmat[f->index].fourcc;

	वापस 0;
पूर्ण

/* RAW VBI ioctls */

अटल पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	f->fmt.vbi.sampling_rate = 6750000 * 4;
	f->fmt.vbi.samples_per_line = VBI_LINE_LENGTH;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.start[0] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_START_LINE : NTSC_VBI_START_LINE;
	f->fmt.vbi.count[0] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_LINES : NTSC_VBI_LINES;
	f->fmt.vbi.start[1] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_START_LINE + 312 : NTSC_VBI_START_LINE + 263;
	f->fmt.vbi.count[1] = f->fmt.vbi.count[0];
	स_रखो(f->fmt.vbi.reserved, 0, माप(f->fmt.vbi.reserved));

	वापस 0;

पूर्ण

अटल पूर्णांक vidioc_try_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	f->fmt.vbi.sampling_rate = 6750000 * 4;
	f->fmt.vbi.samples_per_line = VBI_LINE_LENGTH;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.flags = 0;
	f->fmt.vbi.start[0] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_START_LINE : NTSC_VBI_START_LINE;
	f->fmt.vbi.count[0] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_LINES : NTSC_VBI_LINES;
	f->fmt.vbi.start[1] = (dev->norm & V4L2_STD_625_50) ?
	    PAL_VBI_START_LINE + 312 : NTSC_VBI_START_LINE + 263;
	f->fmt.vbi.count[1] = f->fmt.vbi.count[0];
	स_रखो(f->fmt.vbi.reserved, 0, माप(f->fmt.vbi.reserved));

	वापस 0;

पूर्ण

अटल पूर्णांक vidioc_s_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_try_fmt_vbi_cap(file, priv, f);
पूर्ण

/* ----------------------------------------------------------- */
/* RADIO ESPECIFIC IOCTLS                                      */
/* ----------------------------------------------------------- */

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (t->index)
		वापस -EINVAL;

	strscpy(t->name, "Radio", माप(t->name));

	call_all(dev, tuner, g_tuner, t);

	वापस 0;
पूर्ण
अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (t->index)
		वापस -EINVAL;

	call_all(dev, tuner, s_tuner, t);

	वापस 0;
पूर्ण

/*
 * cx231xx_v4l2_खोलो()
 * inits the device and starts isoc transfer
 */
अटल पूर्णांक cx231xx_v4l2_खोलो(काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा cx231xx *dev = video_drvdata(filp);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(filp);
	अगर (ret) अणु
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	अगर (dev->users++ == 0) अणु
		/* Power up in Analog TV mode */
		अगर (dev->board.बाह्यal_av)
			cx231xx_set_घातer_mode(dev,
				 POLARIS_AVMODE_ENXTERNAL_AV);
		अन्यथा
			cx231xx_set_घातer_mode(dev, POLARIS_AVMODE_ANALOGT_TV);

		/* set video alternate setting */
		cx231xx_set_video_alternate(dev);

		/* Needed, since GPIO might have disabled घातer of
		   some i2c device */
		cx231xx_config_i2c(dev);

		/* device needs to be initialized beक्रमe isoc transfer */
		dev->video_input = dev->video_input > 2 ? 2 : dev->video_input;
	पूर्ण

	अगर (vdev->vfl_type == VFL_TYPE_RADIO) अणु
		cx231xx_videodbg("video_open: setting radio device\n");

		/* cx231xx_start_radio(dev); */

		call_all(dev, tuner, s_radio);
	पूर्ण
	अगर (vdev->vfl_type == VFL_TYPE_VBI) अणु
		/* Set the required alternate setting  VBI पूर्णांकerface works in
		   Bulk mode only */
		cx231xx_set_alt_setting(dev, INDEX_VANC, 0);
	पूर्ण
	mutex_unlock(&dev->lock);
	वापस 0;
पूर्ण

/*
 * cx231xx_realease_resources()
 * unरेजिस्टरs the v4l2,i2c and usb devices
 * called when the device माला_लो disconnected or at module unload
*/
व्योम cx231xx_release_analog_resources(काष्ठा cx231xx *dev)
अणु

	/*FIXME: I2C IR should be disconnected */

	अगर (video_is_रेजिस्टरed(&dev->radio_dev))
		video_unरेजिस्टर_device(&dev->radio_dev);
	अगर (video_is_रेजिस्टरed(&dev->vbi_dev)) अणु
		dev_info(dev->dev, "V4L2 device %s deregistered\n",
			video_device_node_name(&dev->vbi_dev));
		video_unरेजिस्टर_device(&dev->vbi_dev);
	पूर्ण
	अगर (video_is_रेजिस्टरed(&dev->vdev)) अणु
		dev_info(dev->dev, "V4L2 device %s deregistered\n",
			video_device_node_name(&dev->vdev));

		अगर (dev->board.has_417)
			cx231xx_417_unरेजिस्टर(dev);

		video_unरेजिस्टर_device(&dev->vdev);
	पूर्ण
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_ctrl_handler_मुक्त(&dev->radio_ctrl_handler);
पूर्ण

/*
 * cx231xx_बंद()
 * stops streaming and deallocates all resources allocated by the v4l2
 * calls and ioctls
 */
अटल पूर्णांक cx231xx_बंद(काष्ठा file *filp)
अणु
	काष्ठा cx231xx *dev = video_drvdata(filp);
	काष्ठा video_device *vdev = video_devdata(filp);

	_vb2_fop_release(filp, शून्य);

	अगर (--dev->users == 0) अणु
		/* Save some घातer by putting tuner to sleep */
		call_all(dev, tuner, standby);

		/* करो this beक्रमe setting alternate! */
		अगर (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		अन्यथा
			cx231xx_uninit_bulk(dev);
		cx231xx_set_mode(dev, CX231XX_SUSPEND);
	पूर्ण

	/*
	 * To workaround error number=-71 on EP0 क्रम VideoGrabber,
	 *	 need exclude following.
	 * FIXME: It is probably safe to हटाओ most of these, as we're
	 * now aव्योमing the alternate setting क्रम INDEX_VANC
	 */
	अगर (!dev->board.no_alt_vanc && vdev->vfl_type == VFL_TYPE_VBI) अणु
		/* करो this beक्रमe setting alternate! */
		cx231xx_uninit_vbi_isoc(dev);

		/* set alternate 0 */
		अगर (!dev->vbi_or_sliced_cc_mode)
			cx231xx_set_alt_setting(dev, INDEX_VANC, 0);
		अन्यथा
			cx231xx_set_alt_setting(dev, INDEX_HANC, 0);

		wake_up_पूर्णांकerruptible_nr(&dev->खोलो, 1);
		वापस 0;
	पूर्ण

	अगर (dev->users == 0) अणु
		/* set alternate 0 */
		cx231xx_set_alt_setting(dev, INDEX_VIDEO, 0);
	पूर्ण

	wake_up_पूर्णांकerruptible(&dev->खोलो);
	वापस 0;
पूर्ण

अटल पूर्णांक cx231xx_v4l2_बंद(काष्ठा file *filp)
अणु
	काष्ठा cx231xx *dev = video_drvdata(filp);
	पूर्णांक rc;

	mutex_lock(&dev->lock);
	rc = cx231xx_बंद(filp);
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations cx231xx_v4l_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cx231xx_v4l2_खोलो,
	.release = cx231xx_v4l2_बंद,
	.पढ़ो    = vb2_fop_पढ़ो,
	.poll    = vb2_fop_poll,
	.mmap    = vb2_fop_mmap,
	.unlocked_ioctl   = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap               = cx231xx_querycap,
	.vidioc_क्रमागत_fmt_vid_cap       = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap          = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap        = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap          = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap          = vidioc_g_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap        = vidioc_try_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap          = vidioc_s_fmt_vbi_cap,
	.vidioc_g_pixelaspect          = vidioc_g_pixelaspect,
	.vidioc_g_selection            = vidioc_g_selection,
	.vidioc_reqbufs                = vb2_ioctl_reqbufs,
	.vidioc_querybuf               = vb2_ioctl_querybuf,
	.vidioc_qbuf                   = vb2_ioctl_qbuf,
	.vidioc_dqbuf                  = vb2_ioctl_dqbuf,
	.vidioc_s_std                  = vidioc_s_std,
	.vidioc_g_std                  = vidioc_g_std,
	.vidioc_क्रमागत_input             = cx231xx_क्रमागत_input,
	.vidioc_g_input                = cx231xx_g_input,
	.vidioc_s_input                = cx231xx_s_input,
	.vidioc_streamon               = vb2_ioctl_streamon,
	.vidioc_streamoff              = vb2_ioctl_streamoff,
	.vidioc_g_tuner                = cx231xx_g_tuner,
	.vidioc_s_tuner                = cx231xx_s_tuner,
	.vidioc_g_frequency            = cx231xx_g_frequency,
	.vidioc_s_frequency            = cx231xx_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info            = cx231xx_g_chip_info,
	.vidioc_g_रेजिस्टर             = cx231xx_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर             = cx231xx_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device cx231xx_vbi_ढाँचा;

अटल स्थिर काष्ठा video_device cx231xx_video_ढाँचा = अणु
	.fops         = &cx231xx_v4l_fops,
	.release      = video_device_release_empty,
	.ioctl_ops    = &video_ioctl_ops,
	.tvnorms      = V4L2_STD_ALL,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो   = cx231xx_v4l2_खोलो,
	.release = cx231xx_v4l2_बंद,
	.poll = v4l2_ctrl_poll,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap    = cx231xx_querycap,
	.vidioc_g_tuner     = radio_g_tuner,
	.vidioc_s_tuner     = radio_s_tuner,
	.vidioc_g_frequency = cx231xx_g_frequency,
	.vidioc_s_frequency = cx231xx_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info = cx231xx_g_chip_info,
	.vidioc_g_रेजिस्टर  = cx231xx_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर  = cx231xx_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device cx231xx_radio_ढाँचा = अणु
	.name      = "cx231xx-radio",
	.fops      = &radio_fops,
	.ioctl_ops = &radio_ioctl_ops,
पूर्ण;

/******************************** usb पूर्णांकerface ******************************/

अटल व्योम cx231xx_vdev_init(काष्ठा cx231xx *dev,
		काष्ठा video_device *vfd,
		स्थिर काष्ठा video_device *ढाँचा,
		स्थिर अक्षर *type_name)
अणु
	*vfd = *ढाँचा;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &dev->lock;

	snम_लिखो(vfd->name, माप(vfd->name), "%s %s", dev->name, type_name);

	video_set_drvdata(vfd, dev);
	अगर (dev->tuner_type == TUNER_ABSENT) अणु
		चयन (dev->model) अणु
		हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
		हाल CX231XX_BOARD_HAUPPAUGE_935C:
		हाल CX231XX_BOARD_HAUPPAUGE_955Q:
		हाल CX231XX_BOARD_HAUPPAUGE_975:
		हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
			अवरोध;
		शेष:
			v4l2_disable_ioctl(vfd, VIDIOC_G_FREQUENCY);
			v4l2_disable_ioctl(vfd, VIDIOC_S_FREQUENCY);
			v4l2_disable_ioctl(vfd, VIDIOC_G_TUNER);
			v4l2_disable_ioctl(vfd, VIDIOC_S_TUNER);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cx231xx_रेजिस्टर_analog_devices(काष्ठा cx231xx *dev)
अणु
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	dev_info(dev->dev, "v4l2 driver version %s\n", CX231XX_VERSION);

	/* set शेष norm */
	dev->norm = V4L2_STD_PAL;
	dev->width = norm_maxw(dev);
	dev->height = norm_maxh(dev);
	dev->पूर्णांकerlaced = 0;

	/* Analog specअगरic initialization */
	dev->क्रमmat = &क्रमmat[0];

	/* Set the initial input */
	video_mux(dev, dev->video_input);

	call_all(dev, video, s_std, dev->norm);

	v4l2_ctrl_handler_init(&dev->ctrl_handler, 10);
	v4l2_ctrl_handler_init(&dev->radio_ctrl_handler, 5);

	अगर (dev->sd_cx25840) अणु
		v4l2_ctrl_add_handler(&dev->ctrl_handler,
				dev->sd_cx25840->ctrl_handler, शून्य, true);
		v4l2_ctrl_add_handler(&dev->radio_ctrl_handler,
				dev->sd_cx25840->ctrl_handler,
				v4l2_ctrl_radio_filter, true);
	पूर्ण

	अगर (dev->ctrl_handler.error)
		वापस dev->ctrl_handler.error;
	अगर (dev->radio_ctrl_handler.error)
		वापस dev->radio_ctrl_handler.error;

	/* enable vbi capturing */
	/* ग_लिखो code here...  */

	/* allocate and fill video video_device काष्ठा */
	cx231xx_vdev_init(dev, &dev->vdev, &cx231xx_video_ढाँचा, "video");
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	dev->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	अगर (ret < 0)
		dev_err(dev->dev, "failed to initialize video media entity!\n");
#पूर्ण_अगर
	dev->vdev.ctrl_handler = &dev->ctrl_handler;

	q = &dev->vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_USERPTR | VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx231xx_buffer);
	q->ops = &cx231xx_video_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 1;
	q->lock = &dev->lock;
	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;
	dev->vdev.queue = q;
	dev->vdev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				V4L2_CAP_VIDEO_CAPTURE;

	चयन (dev->model) अणु /* i2c device tuners */
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	हाल CX231XX_BOARD_HAUPPAUGE_975:
	हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
		dev->vdev.device_caps |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			dev->vdev.device_caps |= V4L2_CAP_TUNER;
		अवरोध;
	पूर्ण

	/* रेजिस्टर v4l2 video video_device */
	ret = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_VIDEO,
				    video_nr[dev->devno]);
	अगर (ret) अणु
		dev_err(dev->dev,
			"unable to register video device (error=%i).\n",
			ret);
		वापस ret;
	पूर्ण

	dev_info(dev->dev, "Registered video device %s [v4l2]\n",
		video_device_node_name(&dev->vdev));

	/* Initialize VBI ढाँचा */
	cx231xx_vbi_ढाँचा = cx231xx_video_ढाँचा;
	strscpy(cx231xx_vbi_ढाँचा.name, "cx231xx-vbi",
		माप(cx231xx_vbi_ढाँचा.name));

	/* Allocate and fill vbi video_device काष्ठा */
	cx231xx_vdev_init(dev, &dev->vbi_dev, &cx231xx_vbi_ढाँचा, "vbi");

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	dev->vbi_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	अगर (ret < 0)
		dev_err(dev->dev, "failed to initialize vbi media entity!\n");
#पूर्ण_अगर
	dev->vbi_dev.ctrl_handler = &dev->ctrl_handler;

	q = &dev->vbiq;
	q->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	q->io_modes = VB2_USERPTR | VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx231xx_buffer);
	q->ops = &cx231xx_vbi_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 1;
	q->lock = &dev->lock;
	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;
	dev->vbi_dev.queue = q;
	dev->vbi_dev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				   V4L2_CAP_VBI_CAPTURE;
	चयन (dev->model) अणु /* i2c device tuners */
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	हाल CX231XX_BOARD_HAUPPAUGE_935C:
	हाल CX231XX_BOARD_HAUPPAUGE_955Q:
	हाल CX231XX_BOARD_HAUPPAUGE_975:
	हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
		dev->vbi_dev.device_caps |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			dev->vbi_dev.device_caps |= V4L2_CAP_TUNER;
	पूर्ण

	/* रेजिस्टर v4l2 vbi video_device */
	ret = video_रेजिस्टर_device(&dev->vbi_dev, VFL_TYPE_VBI,
				    vbi_nr[dev->devno]);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "unable to register vbi device\n");
		वापस ret;
	पूर्ण

	dev_info(dev->dev, "Registered VBI device %s\n",
		video_device_node_name(&dev->vbi_dev));

	अगर (cx231xx_boards[dev->model].radio.type == CX231XX_RADIO) अणु
		cx231xx_vdev_init(dev, &dev->radio_dev,
				&cx231xx_radio_ढाँचा, "radio");
		dev->radio_dev.ctrl_handler = &dev->radio_ctrl_handler;
		dev->radio_dev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		ret = video_रेजिस्टर_device(&dev->radio_dev, VFL_TYPE_RADIO,
					    radio_nr[dev->devno]);
		अगर (ret < 0) अणु
			dev_err(dev->dev,
				"can't register radio device\n");
			वापस ret;
		पूर्ण
		dev_info(dev->dev, "Registered radio device as %s\n",
			video_device_node_name(&dev->radio_dev));
	पूर्ण

	वापस 0;
पूर्ण
