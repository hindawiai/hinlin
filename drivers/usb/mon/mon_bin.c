<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The USB Monitor, inspired by Dave Harding's USBMon.
 *
 * This is a binary क्रमmat पढ़ोer.
 *
 * Copyright (C) 2006 Paolo Abeni (paolo.abeni@email.it)
 * Copyright (C) 2006,2007 Pete Zaitcev (zaitcev@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/export.h>
#समावेश <linux/usb.h>
#समावेश <linux/poll.h>
#समावेश <linux/compat.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय64.h>

#समावेश <linux/uaccess.h>

#समावेश "usb_mon.h"

/*
 * Defined by USB 2.0 clause 9.3, table 9.2.
 */
#घोषणा SETUP_LEN  8

/* ioctl macros */
#घोषणा MON_IOC_MAGIC 0x92

#घोषणा MON_IOCQ_URB_LEN _IO(MON_IOC_MAGIC, 1)
/* #2 used to be MON_IOCX_URB, हटाओd beक्रमe it got पूर्णांकo Linus tree */
#घोषणा MON_IOCG_STATS _IOR(MON_IOC_MAGIC, 3, काष्ठा mon_bin_stats)
#घोषणा MON_IOCT_RING_SIZE _IO(MON_IOC_MAGIC, 4)
#घोषणा MON_IOCQ_RING_SIZE _IO(MON_IOC_MAGIC, 5)
#घोषणा MON_IOCX_GET   _IOW(MON_IOC_MAGIC, 6, काष्ठा mon_bin_get)
#घोषणा MON_IOCX_MFETCH _IOWR(MON_IOC_MAGIC, 7, काष्ठा mon_bin_mfetch)
#घोषणा MON_IOCH_MFLUSH _IO(MON_IOC_MAGIC, 8)
/* #9 was MON_IOCT_SETAPI */
#घोषणा MON_IOCX_GETX   _IOW(MON_IOC_MAGIC, 10, काष्ठा mon_bin_get)

#अगर_घोषित CONFIG_COMPAT
#घोषणा MON_IOCX_GET32 _IOW(MON_IOC_MAGIC, 6, काष्ठा mon_bin_get32)
#घोषणा MON_IOCX_MFETCH32 _IOWR(MON_IOC_MAGIC, 7, काष्ठा mon_bin_mfetch32)
#घोषणा MON_IOCX_GETX32   _IOW(MON_IOC_MAGIC, 10, काष्ठा mon_bin_get32)
#पूर्ण_अगर

/*
 * Some architectures have enormous basic pages (16KB क्रम ia64, 64KB क्रम ppc).
 * But it's all right. Just use a simple way to make sure the chunk is never
 * smaller than a page.
 *
 * N.B. An application करोes not know our chunk size.
 *
 * Woops, get_zeroed_page() वापसs a single page. I guess we're stuck with
 * page-sized chunks क्रम the समय being.
 */
#घोषणा CHUNK_SIZE   PAGE_SIZE
#घोषणा CHUNK_ALIGN(x)   (((x)+CHUNK_SIZE-1) & ~(CHUNK_SIZE-1))

/*
 * The magic limit was calculated so that it allows the monitoring
 * application to pick data once in two ticks. This way, another application,
 * which presumably drives the bus, माला_लो to hog CPU, yet we collect our data.
 * If HZ is 100, a 480 mbit/s bus drives 614 KB every jअगरfy. USB has an
 * enormous overhead built पूर्णांकo the bus protocol, so we need about 1000 KB.
 *
 * This is still too much क्रम most हालs, where we just snoop a few
 * descriptor fetches क्रम क्रमागतeration. So, the शेष is a "reasonable"
 * amount क्रम प्रणालीs with HZ=250 and incomplete bus saturation.
 *
 * XXX What about multi-megabyte URBs which take minutes to transfer?
 */
#घोषणा BUFF_MAX  CHUNK_ALIGN(1200*1024)
#घोषणा BUFF_DFL   CHUNK_ALIGN(300*1024)
#घोषणा BUFF_MIN     CHUNK_ALIGN(8*1024)

/*
 * The per-event API header (2 per URB).
 *
 * This काष्ठाure is seen in userland as defined by the करोcumentation.
 */
काष्ठा mon_bin_hdr अणु
	u64 id;			/* URB ID - from submission to callback */
	अचिन्हित अक्षर type;	/* Same as in text API; extensible. */
	अचिन्हित अक्षर xfer_type;	/* ISO, Intr, Control, Bulk */
	अचिन्हित अक्षर epnum;	/* Endpoपूर्णांक number and transfer direction */
	अचिन्हित अक्षर devnum;	/* Device address */
	अचिन्हित लघु busnum;	/* Bus number */
	अक्षर flag_setup;
	अक्षर flag_data;
	s64 ts_sec;		/* kसमय_get_real_ts64 */
	s32 ts_usec;		/* kसमय_get_real_ts64 */
	पूर्णांक status;
	अचिन्हित पूर्णांक len_urb;	/* Length of data (submitted or actual) */
	अचिन्हित पूर्णांक len_cap;	/* Delivered length */
	जोड़ अणु
		अचिन्हित अक्षर setup[SETUP_LEN];	/* Only क्रम Control S-type */
		काष्ठा iso_rec अणु
			पूर्णांक error_count;
			पूर्णांक numdesc;
		पूर्ण iso;
	पूर्ण s;
	पूर्णांक पूर्णांकerval;
	पूर्णांक start_frame;
	अचिन्हित पूर्णांक xfer_flags;
	अचिन्हित पूर्णांक ndesc;	/* Actual number of ISO descriptors */
पूर्ण;

/*
 * ISO vector, packed पूर्णांकo the head of data stream.
 * This has to take 16 bytes to make sure that the end of buffer
 * wrap is not happening in the middle of a descriptor.
 */
काष्ठा mon_bin_isodesc अणु
	पूर्णांक          iso_status;
	अचिन्हित पूर्णांक iso_off;
	अचिन्हित पूर्णांक iso_len;
	u32 _pad;
पूर्ण;

/* per file statistic */
काष्ठा mon_bin_stats अणु
	u32 queued;
	u32 dropped;
पूर्ण;

काष्ठा mon_bin_get अणु
	काष्ठा mon_bin_hdr __user *hdr;	/* Can be 48 bytes or 64. */
	व्योम __user *data;
	माप_प्रकार alloc;		/* Length of data (can be zero) */
पूर्ण;

काष्ठा mon_bin_mfetch अणु
	u32 __user *offvec;	/* Vector of events fetched */
	u32 nfetch;		/* Number of events to fetch (out: fetched) */
	u32 nflush;		/* Number of events to flush */
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
काष्ठा mon_bin_get32 अणु
	u32 hdr32;
	u32 data32;
	u32 alloc32;
पूर्ण;

काष्ठा mon_bin_mfetch32 अणु
        u32 offvec32;
        u32 nfetch32;
        u32 nflush32;
पूर्ण;
#पूर्ण_अगर

/* Having these two values same prevents wrapping of the mon_bin_hdr */
#घोषणा PKT_ALIGN   64
#घोषणा PKT_SIZE    64

#घोषणा PKT_SZ_API0 48	/* API 0 (2.6.20) size */
#घोषणा PKT_SZ_API1 64	/* API 1 size: extra fields */

#घोषणा ISODESC_MAX   128	/* Same number as usbfs allows, 2048 bytes. */

/* max number of USB bus supported */
#घोषणा MON_BIN_MAX_MINOR 128

/*
 * The buffer: map of used pages.
 */
काष्ठा mon_pgmap अणु
	काष्ठा page *pg;
	अचिन्हित अक्षर *ptr;	/* XXX just use page_to_virt everywhere? */
पूर्ण;

/*
 * This माला_लो associated with an खोलो file काष्ठा.
 */
काष्ठा mon_पढ़ोer_bin अणु
	/* The buffer: one per खोलो. */
	spinlock_t b_lock;		/* Protect b_cnt, b_in */
	अचिन्हित पूर्णांक b_size;		/* Current size of the buffer - bytes */
	अचिन्हित पूर्णांक b_cnt;		/* Bytes used */
	अचिन्हित पूर्णांक b_in, b_out;	/* Offsets पूर्णांकo buffer - bytes */
	अचिन्हित पूर्णांक b_पढ़ो;		/* Amount of पढ़ो data in curr. pkt. */
	काष्ठा mon_pgmap *b_vec;	/* The map array */
	रुको_queue_head_t b_रुको;	/* Wait क्रम data here */

	काष्ठा mutex fetch_lock;	/* Protect b_पढ़ो, b_out */
	पूर्णांक mmap_active;

	/* A list of these is needed क्रम "bus 0". Some समय later. */
	काष्ठा mon_पढ़ोer r;

	/* Stats */
	अचिन्हित पूर्णांक cnt_lost;
पूर्ण;

अटल अंतरभूत काष्ठा mon_bin_hdr *MON_OFF2HDR(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक offset)
अणु
	वापस (काष्ठा mon_bin_hdr *)
	    (rp->b_vec[offset / CHUNK_SIZE].ptr + offset % CHUNK_SIZE);
पूर्ण

#घोषणा MON_RING_EMPTY(rp)	((rp)->b_cnt == 0)

अटल अचिन्हित अक्षर xfer_to_pipe[4] = अणु
	PIPE_CONTROL, PIPE_ISOCHRONOUS, PIPE_BULK, PIPE_INTERRUPT
पूर्ण;

अटल काष्ठा class *mon_bin_class;
अटल dev_t mon_bin_dev0;
अटल काष्ठा cdev mon_bin_cdev;

अटल व्योम mon_buff_area_fill(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size);
अटल पूर्णांक mon_bin_रुको_event(काष्ठा file *file, काष्ठा mon_पढ़ोer_bin *rp);
अटल पूर्णांक mon_alloc_buff(काष्ठा mon_pgmap *map, पूर्णांक npages);
अटल व्योम mon_मुक्त_buff(काष्ठा mon_pgmap *map, पूर्णांक npages);

/*
 * This is a "chunked memcpy". It करोes not manipulate any counters.
 */
अटल अचिन्हित पूर्णांक mon_copy_to_buff(स्थिर काष्ठा mon_पढ़ोer_bin *this,
    अचिन्हित पूर्णांक off, स्थिर अचिन्हित अक्षर *from, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक step_len;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक in_page;

	जबतक (length) अणु
		/*
		 * Determine step_len.
		 */
		step_len = length;
		in_page = CHUNK_SIZE - (off & (CHUNK_SIZE-1));
		अगर (in_page < step_len)
			step_len = in_page;

		/*
		 * Copy data and advance poपूर्णांकers.
		 */
		buf = this->b_vec[off / CHUNK_SIZE].ptr + off % CHUNK_SIZE;
		स_नकल(buf, from, step_len);
		अगर ((off += step_len) >= this->b_size) off = 0;
		from += step_len;
		length -= step_len;
	पूर्ण
	वापस off;
पूर्ण

/*
 * This is a little worse than the above because it's "chunked copy_to_user".
 * The वापस value is an error code, not an offset.
 */
अटल पूर्णांक copy_from_buf(स्थिर काष्ठा mon_पढ़ोer_bin *this, अचिन्हित पूर्णांक off,
    अक्षर __user *to, पूर्णांक length)
अणु
	अचिन्हित पूर्णांक step_len;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक in_page;

	जबतक (length) अणु
		/*
		 * Determine step_len.
		 */
		step_len = length;
		in_page = CHUNK_SIZE - (off & (CHUNK_SIZE-1));
		अगर (in_page < step_len)
			step_len = in_page;

		/*
		 * Copy data and advance poपूर्णांकers.
		 */
		buf = this->b_vec[off / CHUNK_SIZE].ptr + off % CHUNK_SIZE;
		अगर (copy_to_user(to, buf, step_len))
			वापस -EINVAL;
		अगर ((off += step_len) >= this->b_size) off = 0;
		to += step_len;
		length -= step_len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Allocate an (aligned) area in the buffer.
 * This is called under b_lock.
 * Returns ~0 on failure.
 */
अटल अचिन्हित पूर्णांक mon_buff_area_alloc(काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक offset;

	size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
	अगर (rp->b_cnt + size > rp->b_size)
		वापस ~0;
	offset = rp->b_in;
	rp->b_cnt += size;
	अगर ((rp->b_in += size) >= rp->b_size)
		rp->b_in -= rp->b_size;
	वापस offset;
पूर्ण

/*
 * This is the same thing as mon_buff_area_alloc, only it करोes not allow
 * buffers to wrap. This is needed by applications which pass references
 * पूर्णांकo mmap-ed buffers up their stacks (libpcap can करो that).
 *
 * Currently, we always have the header stuck with the data, although
 * it is not strictly speaking necessary.
 *
 * When a buffer would wrap, we place a filler packet to mark the space.
 */
अटल अचिन्हित पूर्णांक mon_buff_area_alloc_contiguous(काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक fill_size;

	size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
	अगर (rp->b_cnt + size > rp->b_size)
		वापस ~0;
	अगर (rp->b_in + size > rp->b_size) अणु
		/*
		 * This would wrap. Find अगर we still have space after
		 * skipping to the end of the buffer. If we करो, place
		 * a filler packet and allocate a new packet.
		 */
		fill_size = rp->b_size - rp->b_in;
		अगर (rp->b_cnt + size + fill_size > rp->b_size)
			वापस ~0;
		mon_buff_area_fill(rp, rp->b_in, fill_size);

		offset = 0;
		rp->b_in = size;
		rp->b_cnt += size + fill_size;
	पूर्ण अन्यथा अगर (rp->b_in + size == rp->b_size) अणु
		offset = rp->b_in;
		rp->b_in = 0;
		rp->b_cnt += size;
	पूर्ण अन्यथा अणु
		offset = rp->b_in;
		rp->b_in += size;
		rp->b_cnt += size;
	पूर्ण
	वापस offset;
पूर्ण

/*
 * Return a few (kilo-)bytes to the head of the buffer.
 * This is used अगर a data fetch fails.
 */
अटल व्योम mon_buff_area_shrink(काष्ठा mon_पढ़ोer_bin *rp, अचिन्हित पूर्णांक size)
अणु

	/* size &= ~(PKT_ALIGN-1);  -- we're called with aligned size */
	rp->b_cnt -= size;
	अगर (rp->b_in < size)
		rp->b_in += rp->b_size;
	rp->b_in -= size;
पूर्ण

/*
 * This has to be called under both b_lock and fetch_lock, because
 * it accesses both b_cnt and b_out.
 */
अटल व्योम mon_buff_area_मुक्त(काष्ठा mon_पढ़ोer_bin *rp, अचिन्हित पूर्णांक size)
अणु

	size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
	rp->b_cnt -= size;
	अगर ((rp->b_out += size) >= rp->b_size)
		rp->b_out -= rp->b_size;
पूर्ण

अटल व्योम mon_buff_area_fill(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size)
अणु
	काष्ठा mon_bin_hdr *ep;

	ep = MON_OFF2HDR(rp, offset);
	स_रखो(ep, 0, PKT_SIZE);
	ep->type = '@';
	ep->len_cap = size - PKT_SIZE;
पूर्ण

अटल अंतरभूत अक्षर mon_bin_get_setup(अचिन्हित अक्षर *setupb,
    स्थिर काष्ठा urb *urb, अक्षर ev_type)
अणु

	अगर (urb->setup_packet == शून्य)
		वापस 'Z';
	स_नकल(setupb, urb->setup_packet, SETUP_LEN);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mon_bin_get_data(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक offset, काष्ठा urb *urb, अचिन्हित पूर्णांक length,
    अक्षर *flag)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक this_len;

	*flag = 0;
	अगर (urb->num_sgs == 0) अणु
		अगर (urb->transfer_buffer == शून्य) अणु
			*flag = 'Z';
			वापस length;
		पूर्ण
		mon_copy_to_buff(rp, offset, urb->transfer_buffer, length);
		length = 0;

	पूर्ण अन्यथा अणु
		/* If IOMMU coalescing occurred, we cannot trust sg_page */
		अगर (urb->transfer_flags & URB_DMA_SG_COMBINED) अणु
			*flag = 'D';
			वापस length;
		पूर्ण

		/* Copy up to the first non-addressable segment */
		क्रम_each_sg(urb->sg, sg, urb->num_sgs, i) अणु
			अगर (length == 0 || PageHighMem(sg_page(sg)))
				अवरोध;
			this_len = min_t(अचिन्हित पूर्णांक, sg->length, length);
			offset = mon_copy_to_buff(rp, offset, sg_virt(sg),
					this_len);
			length -= this_len;
		पूर्ण
		अगर (i == 0)
			*flag = 'D';
	पूर्ण

	वापस length;
पूर्ण

/*
 * This is the look-ahead pass in हाल of 'C Zi', when actual_length cannot
 * be used to determine the length of the whole contiguous buffer.
 */
अटल अचिन्हित पूर्णांक mon_bin_collate_isodesc(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    काष्ठा urb *urb, अचिन्हित पूर्णांक ndesc)
अणु
	काष्ठा usb_iso_packet_descriptor *fp;
	अचिन्हित पूर्णांक length;

	length = 0;
	fp = urb->iso_frame_desc;
	जबतक (ndesc-- != 0) अणु
		अगर (fp->actual_length != 0) अणु
			अगर (fp->offset + fp->actual_length > length)
				length = fp->offset + fp->actual_length;
		पूर्ण
		fp++;
	पूर्ण
	वापस length;
पूर्ण

अटल व्योम mon_bin_get_isodesc(स्थिर काष्ठा mon_पढ़ोer_bin *rp,
    अचिन्हित पूर्णांक offset, काष्ठा urb *urb, अक्षर ev_type, अचिन्हित पूर्णांक ndesc)
अणु
	काष्ठा mon_bin_isodesc *dp;
	काष्ठा usb_iso_packet_descriptor *fp;

	fp = urb->iso_frame_desc;
	जबतक (ndesc-- != 0) अणु
		dp = (काष्ठा mon_bin_isodesc *)
		    (rp->b_vec[offset / CHUNK_SIZE].ptr + offset % CHUNK_SIZE);
		dp->iso_status = fp->status;
		dp->iso_off = fp->offset;
		dp->iso_len = (ev_type == 'S') ? fp->length : fp->actual_length;
		dp->_pad = 0;
		अगर ((offset += माप(काष्ठा mon_bin_isodesc)) >= rp->b_size)
			offset = 0;
		fp++;
	पूर्ण
पूर्ण

अटल व्योम mon_bin_event(काष्ठा mon_पढ़ोer_bin *rp, काष्ठा urb *urb,
    अक्षर ev_type, पूर्णांक status)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd = &urb->ep->desc;
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक urb_length;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक delta;
	अचिन्हित पूर्णांक ndesc, lendesc;
	अचिन्हित अक्षर dir;
	काष्ठा mon_bin_hdr *ep;
	अक्षर data_tag = 0;

	kसमय_get_real_ts64(&ts);

	spin_lock_irqsave(&rp->b_lock, flags);

	/*
	 * Find the maximum allowable length, then allocate space.
	 */
	urb_length = (ev_type == 'S') ?
	    urb->transfer_buffer_length : urb->actual_length;
	length = urb_length;

	अगर (usb_endpoपूर्णांक_xfer_isoc(epd)) अणु
		अगर (urb->number_of_packets < 0) अणु
			ndesc = 0;
		पूर्ण अन्यथा अगर (urb->number_of_packets >= ISODESC_MAX) अणु
			ndesc = ISODESC_MAX;
		पूर्ण अन्यथा अणु
			ndesc = urb->number_of_packets;
		पूर्ण
		अगर (ev_type == 'C' && usb_urb_dir_in(urb))
			length = mon_bin_collate_isodesc(rp, urb, ndesc);
	पूर्ण अन्यथा अणु
		ndesc = 0;
	पूर्ण
	lendesc = ndesc*माप(काष्ठा mon_bin_isodesc);

	/* not an issue unless there's a subtle bug in a HCD somewhere */
	अगर (length >= urb->transfer_buffer_length)
		length = urb->transfer_buffer_length;

	अगर (length >= rp->b_size/5)
		length = rp->b_size/5;

	अगर (usb_urb_dir_in(urb)) अणु
		अगर (ev_type == 'S') अणु
			length = 0;
			data_tag = '<';
		पूर्ण
		/* Cannot rely on endpoपूर्णांक number in हाल of control ep.0 */
		dir = USB_सूची_IN;
	पूर्ण अन्यथा अणु
		अगर (ev_type == 'C') अणु
			length = 0;
			data_tag = '>';
		पूर्ण
		dir = 0;
	पूर्ण

	अगर (rp->mmap_active) अणु
		offset = mon_buff_area_alloc_contiguous(rp,
						 length + PKT_SIZE + lendesc);
	पूर्ण अन्यथा अणु
		offset = mon_buff_area_alloc(rp, length + PKT_SIZE + lendesc);
	पूर्ण
	अगर (offset == ~0) अणु
		rp->cnt_lost++;
		spin_unlock_irqrestore(&rp->b_lock, flags);
		वापस;
	पूर्ण

	ep = MON_OFF2HDR(rp, offset);
	अगर ((offset += PKT_SIZE) >= rp->b_size) offset = 0;

	/*
	 * Fill the allocated area.
	 */
	स_रखो(ep, 0, PKT_SIZE);
	ep->type = ev_type;
	ep->xfer_type = xfer_to_pipe[usb_endpoपूर्णांक_type(epd)];
	ep->epnum = dir | usb_endpoपूर्णांक_num(epd);
	ep->devnum = urb->dev->devnum;
	ep->busnum = urb->dev->bus->busnum;
	ep->id = (अचिन्हित दीर्घ) urb;
	ep->ts_sec = ts.tv_sec;
	ep->ts_usec = ts.tv_nsec / NSEC_PER_USEC;
	ep->status = status;
	ep->len_urb = urb_length;
	ep->len_cap = length + lendesc;
	ep->xfer_flags = urb->transfer_flags;

	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epd)) अणु
		ep->पूर्णांकerval = urb->पूर्णांकerval;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(epd)) अणु
		ep->पूर्णांकerval = urb->पूर्णांकerval;
		ep->start_frame = urb->start_frame;
		ep->s.iso.error_count = urb->error_count;
		ep->s.iso.numdesc = urb->number_of_packets;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_control(epd) && ev_type == 'S') अणु
		ep->flag_setup = mon_bin_get_setup(ep->s.setup, urb, ev_type);
	पूर्ण अन्यथा अणु
		ep->flag_setup = '-';
	पूर्ण

	अगर (ndesc != 0) अणु
		ep->ndesc = ndesc;
		mon_bin_get_isodesc(rp, offset, urb, ev_type, ndesc);
		अगर ((offset += lendesc) >= rp->b_size)
			offset -= rp->b_size;
	पूर्ण

	अगर (length != 0) अणु
		length = mon_bin_get_data(rp, offset, urb, length,
				&ep->flag_data);
		अगर (length > 0) अणु
			delta = (ep->len_cap + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
			ep->len_cap -= length;
			delta -= (ep->len_cap + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
			mon_buff_area_shrink(rp, delta);
		पूर्ण
	पूर्ण अन्यथा अणु
		ep->flag_data = data_tag;
	पूर्ण

	spin_unlock_irqrestore(&rp->b_lock, flags);

	wake_up(&rp->b_रुको);
पूर्ण

अटल व्योम mon_bin_submit(व्योम *data, काष्ठा urb *urb)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = data;
	mon_bin_event(rp, urb, 'S', -EINPROGRESS);
पूर्ण

अटल व्योम mon_bin_complete(व्योम *data, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = data;
	mon_bin_event(rp, urb, 'C', status);
पूर्ण

अटल व्योम mon_bin_error(व्योम *data, काष्ठा urb *urb, पूर्णांक error)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = data;
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;
	काष्ठा mon_bin_hdr *ep;

	kसमय_get_real_ts64(&ts);

	spin_lock_irqsave(&rp->b_lock, flags);

	offset = mon_buff_area_alloc(rp, PKT_SIZE);
	अगर (offset == ~0) अणु
		/* Not incrementing cnt_lost. Just because. */
		spin_unlock_irqrestore(&rp->b_lock, flags);
		वापस;
	पूर्ण

	ep = MON_OFF2HDR(rp, offset);

	स_रखो(ep, 0, PKT_SIZE);
	ep->type = 'E';
	ep->xfer_type = xfer_to_pipe[usb_endpoपूर्णांक_type(&urb->ep->desc)];
	ep->epnum = usb_urb_dir_in(urb) ? USB_सूची_IN : 0;
	ep->epnum |= usb_endpoपूर्णांक_num(&urb->ep->desc);
	ep->devnum = urb->dev->devnum;
	ep->busnum = urb->dev->bus->busnum;
	ep->id = (अचिन्हित दीर्घ) urb;
	ep->ts_sec = ts.tv_sec;
	ep->ts_usec = ts.tv_nsec / NSEC_PER_USEC;
	ep->status = error;

	ep->flag_setup = '-';
	ep->flag_data = 'E';

	spin_unlock_irqrestore(&rp->b_lock, flags);

	wake_up(&rp->b_रुको);
पूर्ण

अटल पूर्णांक mon_bin_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mon_bus *mbus;
	काष्ठा mon_पढ़ोer_bin *rp;
	माप_प्रकार size;
	पूर्णांक rc;

	mutex_lock(&mon_lock);
	mbus = mon_bus_lookup(iminor(inode));
	अगर (mbus == शून्य) अणु
		mutex_unlock(&mon_lock);
		वापस -ENODEV;
	पूर्ण
	अगर (mbus != &mon_bus0 && mbus->u_bus == शून्य) अणु
		prपूर्णांकk(KERN_ERR TAG ": consistency error on open\n");
		mutex_unlock(&mon_lock);
		वापस -ENODEV;
	पूर्ण

	rp = kzalloc(माप(काष्ठा mon_पढ़ोer_bin), GFP_KERNEL);
	अगर (rp == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	spin_lock_init(&rp->b_lock);
	init_रुकोqueue_head(&rp->b_रुको);
	mutex_init(&rp->fetch_lock);
	rp->b_size = BUFF_DFL;

	size = माप(काष्ठा mon_pgmap) * (rp->b_size/CHUNK_SIZE);
	अगर ((rp->b_vec = kzalloc(size, GFP_KERNEL)) == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_allocvec;
	पूर्ण

	अगर ((rc = mon_alloc_buff(rp->b_vec, rp->b_size/CHUNK_SIZE)) < 0)
		जाओ err_allocbuff;

	rp->r.m_bus = mbus;
	rp->r.r_data = rp;
	rp->r.rnf_submit = mon_bin_submit;
	rp->r.rnf_error = mon_bin_error;
	rp->r.rnf_complete = mon_bin_complete;

	mon_पढ़ोer_add(mbus, &rp->r);

	file->निजी_data = rp;
	mutex_unlock(&mon_lock);
	वापस 0;

err_allocbuff:
	kमुक्त(rp->b_vec);
err_allocvec:
	kमुक्त(rp);
err_alloc:
	mutex_unlock(&mon_lock);
	वापस rc;
पूर्ण

/*
 * Extract an event from buffer and copy it to user space.
 * Wait अगर there is no event पढ़ोy.
 * Returns zero or error.
 */
अटल पूर्णांक mon_bin_get_event(काष्ठा file *file, काष्ठा mon_पढ़ोer_bin *rp,
    काष्ठा mon_bin_hdr __user *hdr, अचिन्हित पूर्णांक hdrbytes,
    व्योम __user *data, अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mon_bin_hdr *ep;
	माप_प्रकार step_len;
	अचिन्हित पूर्णांक offset;
	पूर्णांक rc;

	mutex_lock(&rp->fetch_lock);

	अगर ((rc = mon_bin_रुको_event(file, rp)) < 0) अणु
		mutex_unlock(&rp->fetch_lock);
		वापस rc;
	पूर्ण

	ep = MON_OFF2HDR(rp, rp->b_out);

	अगर (copy_to_user(hdr, ep, hdrbytes)) अणु
		mutex_unlock(&rp->fetch_lock);
		वापस -EFAULT;
	पूर्ण

	step_len = min(ep->len_cap, nbytes);
	अगर ((offset = rp->b_out + PKT_SIZE) >= rp->b_size) offset = 0;

	अगर (copy_from_buf(rp, offset, data, step_len)) अणु
		mutex_unlock(&rp->fetch_lock);
		वापस -EFAULT;
	पूर्ण

	spin_lock_irqsave(&rp->b_lock, flags);
	mon_buff_area_मुक्त(rp, PKT_SIZE + ep->len_cap);
	spin_unlock_irqrestore(&rp->b_lock, flags);
	rp->b_पढ़ो = 0;

	mutex_unlock(&rp->fetch_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mon_bin_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = file->निजी_data;
	काष्ठा mon_bus* mbus = rp->r.m_bus;

	mutex_lock(&mon_lock);

	अगर (mbus->nपढ़ोers <= 0) अणु
		prपूर्णांकk(KERN_ERR TAG ": consistency error on close\n");
		mutex_unlock(&mon_lock);
		वापस 0;
	पूर्ण
	mon_पढ़ोer_del(mbus, &rp->r);

	mon_मुक्त_buff(rp->b_vec, rp->b_size/CHUNK_SIZE);
	kमुक्त(rp->b_vec);
	kमुक्त(rp);

	mutex_unlock(&mon_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mon_bin_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
    माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = file->निजी_data;
	अचिन्हित पूर्णांक hdrbytes = PKT_SZ_API0;
	अचिन्हित दीर्घ flags;
	काष्ठा mon_bin_hdr *ep;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार step_len;
	अक्षर *ptr;
	sमाप_प्रकार करोne = 0;
	पूर्णांक rc;

	mutex_lock(&rp->fetch_lock);

	अगर ((rc = mon_bin_रुको_event(file, rp)) < 0) अणु
		mutex_unlock(&rp->fetch_lock);
		वापस rc;
	पूर्ण

	ep = MON_OFF2HDR(rp, rp->b_out);

	अगर (rp->b_पढ़ो < hdrbytes) अणु
		step_len = min(nbytes, (माप_प्रकार)(hdrbytes - rp->b_पढ़ो));
		ptr = ((अक्षर *)ep) + rp->b_पढ़ो;
		अगर (step_len && copy_to_user(buf, ptr, step_len)) अणु
			mutex_unlock(&rp->fetch_lock);
			वापस -EFAULT;
		पूर्ण
		nbytes -= step_len;
		buf += step_len;
		rp->b_पढ़ो += step_len;
		करोne += step_len;
	पूर्ण

	अगर (rp->b_पढ़ो >= hdrbytes) अणु
		step_len = ep->len_cap;
		step_len -= rp->b_पढ़ो - hdrbytes;
		अगर (step_len > nbytes)
			step_len = nbytes;
		offset = rp->b_out + PKT_SIZE;
		offset += rp->b_पढ़ो - hdrbytes;
		अगर (offset >= rp->b_size)
			offset -= rp->b_size;
		अगर (copy_from_buf(rp, offset, buf, step_len)) अणु
			mutex_unlock(&rp->fetch_lock);
			वापस -EFAULT;
		पूर्ण
		nbytes -= step_len;
		buf += step_len;
		rp->b_पढ़ो += step_len;
		करोne += step_len;
	पूर्ण

	/*
	 * Check अगर whole packet was पढ़ो, and अगर so, jump to the next one.
	 */
	अगर (rp->b_पढ़ो >= hdrbytes + ep->len_cap) अणु
		spin_lock_irqsave(&rp->b_lock, flags);
		mon_buff_area_मुक्त(rp, PKT_SIZE + ep->len_cap);
		spin_unlock_irqrestore(&rp->b_lock, flags);
		rp->b_पढ़ो = 0;
	पूर्ण

	mutex_unlock(&rp->fetch_lock);
	वापस करोne;
पूर्ण

/*
 * Remove at most nevents from chunked buffer.
 * Returns the number of हटाओd events.
 */
अटल पूर्णांक mon_bin_flush(काष्ठा mon_पढ़ोer_bin *rp, अचिन्हित nevents)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mon_bin_hdr *ep;
	पूर्णांक i;

	mutex_lock(&rp->fetch_lock);
	spin_lock_irqsave(&rp->b_lock, flags);
	क्रम (i = 0; i < nevents; ++i) अणु
		अगर (MON_RING_EMPTY(rp))
			अवरोध;

		ep = MON_OFF2HDR(rp, rp->b_out);
		mon_buff_area_मुक्त(rp, PKT_SIZE + ep->len_cap);
	पूर्ण
	spin_unlock_irqrestore(&rp->b_lock, flags);
	rp->b_पढ़ो = 0;
	mutex_unlock(&rp->fetch_lock);
	वापस i;
पूर्ण

/*
 * Fetch at most max event offsets पूर्णांकo the buffer and put them पूर्णांकo vec.
 * The events are usually मुक्तd later with mon_bin_flush.
 * Return the effective number of events fetched.
 */
अटल पूर्णांक mon_bin_fetch(काष्ठा file *file, काष्ठा mon_पढ़ोer_bin *rp,
    u32 __user *vec, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक cur_out;
	अचिन्हित पूर्णांक bytes, avail;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक nevents;
	काष्ठा mon_bin_hdr *ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	mutex_lock(&rp->fetch_lock);

	अगर ((rc = mon_bin_रुको_event(file, rp)) < 0) अणु
		mutex_unlock(&rp->fetch_lock);
		वापस rc;
	पूर्ण

	spin_lock_irqsave(&rp->b_lock, flags);
	avail = rp->b_cnt;
	spin_unlock_irqrestore(&rp->b_lock, flags);

	cur_out = rp->b_out;
	nevents = 0;
	bytes = 0;
	जबतक (bytes < avail) अणु
		अगर (nevents >= max)
			अवरोध;

		ep = MON_OFF2HDR(rp, cur_out);
		अगर (put_user(cur_out, &vec[nevents])) अणु
			mutex_unlock(&rp->fetch_lock);
			वापस -EFAULT;
		पूर्ण

		nevents++;
		size = ep->len_cap + PKT_SIZE;
		size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
		अगर ((cur_out += size) >= rp->b_size)
			cur_out -= rp->b_size;
		bytes += size;
	पूर्ण

	mutex_unlock(&rp->fetch_lock);
	वापस nevents;
पूर्ण

/*
 * Count events. This is almost the same as the above mon_bin_fetch,
 * only we करो not store offsets पूर्णांकo user vector, and we have no limit.
 */
अटल पूर्णांक mon_bin_queued(काष्ठा mon_पढ़ोer_bin *rp)
अणु
	अचिन्हित पूर्णांक cur_out;
	अचिन्हित पूर्णांक bytes, avail;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक nevents;
	काष्ठा mon_bin_hdr *ep;
	अचिन्हित दीर्घ flags;

	mutex_lock(&rp->fetch_lock);

	spin_lock_irqsave(&rp->b_lock, flags);
	avail = rp->b_cnt;
	spin_unlock_irqrestore(&rp->b_lock, flags);

	cur_out = rp->b_out;
	nevents = 0;
	bytes = 0;
	जबतक (bytes < avail) अणु
		ep = MON_OFF2HDR(rp, cur_out);

		nevents++;
		size = ep->len_cap + PKT_SIZE;
		size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
		अगर ((cur_out += size) >= rp->b_size)
			cur_out -= rp->b_size;
		bytes += size;
	पूर्ण

	mutex_unlock(&rp->fetch_lock);
	वापस nevents;
पूर्ण

/*
 */
अटल दीर्घ mon_bin_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = file->निजी_data;
	// काष्ठा mon_bus* mbus = rp->r.m_bus;
	पूर्णांक ret = 0;
	काष्ठा mon_bin_hdr *ep;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु

	हाल MON_IOCQ_URB_LEN:
		/*
		 * N.B. This only वापसs the size of data, without the header.
		 */
		spin_lock_irqsave(&rp->b_lock, flags);
		अगर (!MON_RING_EMPTY(rp)) अणु
			ep = MON_OFF2HDR(rp, rp->b_out);
			ret = ep->len_cap;
		पूर्ण
		spin_unlock_irqrestore(&rp->b_lock, flags);
		अवरोध;

	हाल MON_IOCQ_RING_SIZE:
		mutex_lock(&rp->fetch_lock);
		ret = rp->b_size;
		mutex_unlock(&rp->fetch_lock);
		अवरोध;

	हाल MON_IOCT_RING_SIZE:
		/*
		 * Changing the buffer size will flush it's contents; the new
		 * buffer is allocated beक्रमe releasing the old one to be sure
		 * the device will stay functional also in हाल of memory
		 * pressure.
		 */
		अणु
		पूर्णांक size;
		काष्ठा mon_pgmap *vec;

		अगर (arg < BUFF_MIN || arg > BUFF_MAX)
			वापस -EINVAL;

		size = CHUNK_ALIGN(arg);
		vec = kसुस्मृति(size / CHUNK_SIZE, माप(काष्ठा mon_pgmap),
			      GFP_KERNEL);
		अगर (vec == शून्य) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ret = mon_alloc_buff(vec, size/CHUNK_SIZE);
		अगर (ret < 0) अणु
			kमुक्त(vec);
			अवरोध;
		पूर्ण

		mutex_lock(&rp->fetch_lock);
		spin_lock_irqsave(&rp->b_lock, flags);
		अगर (rp->mmap_active) अणु
			mon_मुक्त_buff(vec, size/CHUNK_SIZE);
			kमुक्त(vec);
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			mon_मुक्त_buff(rp->b_vec, rp->b_size/CHUNK_SIZE);
			kमुक्त(rp->b_vec);
			rp->b_vec  = vec;
			rp->b_size = size;
			rp->b_पढ़ो = rp->b_in = rp->b_out = rp->b_cnt = 0;
			rp->cnt_lost = 0;
		पूर्ण
		spin_unlock_irqrestore(&rp->b_lock, flags);
		mutex_unlock(&rp->fetch_lock);
		पूर्ण
		अवरोध;

	हाल MON_IOCH_MFLUSH:
		ret = mon_bin_flush(rp, arg);
		अवरोध;

	हाल MON_IOCX_GET:
	हाल MON_IOCX_GETX:
		अणु
		काष्ठा mon_bin_get getb;

		अगर (copy_from_user(&getb, (व्योम __user *)arg,
					    माप(काष्ठा mon_bin_get)))
			वापस -EFAULT;

		अगर (getb.alloc > 0x10000000)	/* Want to cast to u32 */
			वापस -EINVAL;
		ret = mon_bin_get_event(file, rp, getb.hdr,
		    (cmd == MON_IOCX_GET)? PKT_SZ_API0: PKT_SZ_API1,
		    getb.data, (अचिन्हित पूर्णांक)getb.alloc);
		पूर्ण
		अवरोध;

	हाल MON_IOCX_MFETCH:
		अणु
		काष्ठा mon_bin_mfetch mfetch;
		काष्ठा mon_bin_mfetch __user *uptr;

		uptr = (काष्ठा mon_bin_mfetch __user *)arg;

		अगर (copy_from_user(&mfetch, uptr, माप(mfetch)))
			वापस -EFAULT;

		अगर (mfetch.nflush) अणु
			ret = mon_bin_flush(rp, mfetch.nflush);
			अगर (ret < 0)
				वापस ret;
			अगर (put_user(ret, &uptr->nflush))
				वापस -EFAULT;
		पूर्ण
		ret = mon_bin_fetch(file, rp, mfetch.offvec, mfetch.nfetch);
		अगर (ret < 0)
			वापस ret;
		अगर (put_user(ret, &uptr->nfetch))
			वापस -EFAULT;
		ret = 0;
		पूर्ण
		अवरोध;

	हाल MON_IOCG_STATS: अणु
		काष्ठा mon_bin_stats __user *sp;
		अचिन्हित पूर्णांक nevents;
		अचिन्हित पूर्णांक ndropped;

		spin_lock_irqsave(&rp->b_lock, flags);
		ndropped = rp->cnt_lost;
		rp->cnt_lost = 0;
		spin_unlock_irqrestore(&rp->b_lock, flags);
		nevents = mon_bin_queued(rp);

		sp = (काष्ठा mon_bin_stats __user *)arg;
		अगर (put_user(ndropped, &sp->dropped))
			वापस -EFAULT;
		अगर (put_user(nevents, &sp->queued))
			वापस -EFAULT;

		पूर्ण
		अवरोध;

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ mon_bin_compat_ioctl(काष्ठा file *file,
    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = file->निजी_data;
	पूर्णांक ret;

	चयन (cmd) अणु

	हाल MON_IOCX_GET32:
	हाल MON_IOCX_GETX32:
		अणु
		काष्ठा mon_bin_get32 getb;

		अगर (copy_from_user(&getb, (व्योम __user *)arg,
					    माप(काष्ठा mon_bin_get32)))
			वापस -EFAULT;

		ret = mon_bin_get_event(file, rp, compat_ptr(getb.hdr32),
		    (cmd == MON_IOCX_GET32)? PKT_SZ_API0: PKT_SZ_API1,
		    compat_ptr(getb.data32), getb.alloc32);
		अगर (ret < 0)
			वापस ret;
		पूर्ण
		वापस 0;

	हाल MON_IOCX_MFETCH32:
		अणु
		काष्ठा mon_bin_mfetch32 mfetch;
		काष्ठा mon_bin_mfetch32 __user *uptr;

		uptr = (काष्ठा mon_bin_mfetch32 __user *) compat_ptr(arg);

		अगर (copy_from_user(&mfetch, uptr, माप(mfetch)))
			वापस -EFAULT;

		अगर (mfetch.nflush32) अणु
			ret = mon_bin_flush(rp, mfetch.nflush32);
			अगर (ret < 0)
				वापस ret;
			अगर (put_user(ret, &uptr->nflush32))
				वापस -EFAULT;
		पूर्ण
		ret = mon_bin_fetch(file, rp, compat_ptr(mfetch.offvec32),
		    mfetch.nfetch32);
		अगर (ret < 0)
			वापस ret;
		अगर (put_user(ret, &uptr->nfetch32))
			वापस -EFAULT;
		पूर्ण
		वापस 0;

	हाल MON_IOCG_STATS:
		वापस mon_bin_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));

	हाल MON_IOCQ_URB_LEN:
	हाल MON_IOCQ_RING_SIZE:
	हाल MON_IOCT_RING_SIZE:
	हाल MON_IOCH_MFLUSH:
		वापस mon_bin_ioctl(file, cmd, arg);

	शेष:
		;
	पूर्ण
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल __poll_t
mon_bin_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = file->निजी_data;
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;

	अगर (file->f_mode & FMODE_READ)
		poll_रुको(file, &rp->b_रुको, रुको);

	spin_lock_irqsave(&rp->b_lock, flags);
	अगर (!MON_RING_EMPTY(rp))
		mask |= EPOLLIN | EPOLLRDNORM;    /* पढ़ोable */
	spin_unlock_irqrestore(&rp->b_lock, flags);
	वापस mask;
पूर्ण

/*
 * खोलो and बंद: just keep track of how many बार the device is
 * mapped, to use the proper memory allocation function.
 */
अटल व्योम mon_bin_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = vma->vm_निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rp->b_lock, flags);
	rp->mmap_active++;
	spin_unlock_irqrestore(&rp->b_lock, flags);
पूर्ण

अटल व्योम mon_bin_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ flags;

	काष्ठा mon_पढ़ोer_bin *rp = vma->vm_निजी_data;
	spin_lock_irqsave(&rp->b_lock, flags);
	rp->mmap_active--;
	spin_unlock_irqrestore(&rp->b_lock, flags);
पूर्ण

/*
 * Map ring pages to user space.
 */
अटल vm_fault_t mon_bin_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा mon_पढ़ोer_bin *rp = vmf->vma->vm_निजी_data;
	अचिन्हित दीर्घ offset, chunk_idx;
	काष्ठा page *pageptr;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= rp->b_size)
		वापस VM_FAULT_SIGBUS;
	chunk_idx = offset / CHUNK_SIZE;
	pageptr = rp->b_vec[chunk_idx].pg;
	get_page(pageptr);
	vmf->page = pageptr;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा mon_bin_vm_ops = अणु
	.खोलो =     mon_bin_vma_खोलो,
	.बंद =    mon_bin_vma_बंद,
	.fault =    mon_bin_vma_fault,
पूर्ण;

अटल पूर्णांक mon_bin_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* करोn't करो anything here: "fault" will set up page table entries */
	vma->vm_ops = &mon_bin_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data = filp->निजी_data;
	mon_bin_vma_खोलो(vma);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mon_fops_binary = अणु
	.owner =	THIS_MODULE,
	.खोलो =		mon_bin_खोलो,
	.llseek =	no_llseek,
	.पढ़ो =		mon_bin_पढ़ो,
	/* .ग_लिखो =	mon_text_ग_लिखो, */
	.poll =		mon_bin_poll,
	.unlocked_ioctl = mon_bin_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	mon_bin_compat_ioctl,
#पूर्ण_अगर
	.release =	mon_bin_release,
	.mmap =		mon_bin_mmap,
पूर्ण;

अटल पूर्णांक mon_bin_रुको_event(काष्ठा file *file, काष्ठा mon_पढ़ोer_bin *rp)
अणु
	DECLARE_WAITQUEUE(रुकोa, current);
	अचिन्हित दीर्घ flags;

	add_रुको_queue(&rp->b_रुको, &रुकोa);
	set_current_state(TASK_INTERRUPTIBLE);

	spin_lock_irqsave(&rp->b_lock, flags);
	जबतक (MON_RING_EMPTY(rp)) अणु
		spin_unlock_irqrestore(&rp->b_lock, flags);

		अगर (file->f_flags & O_NONBLOCK) अणु
			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&rp->b_रुको, &रुकोa);
			वापस -EWOULDBLOCK; /* Same as EAGAIN in Linux */
		पूर्ण
		schedule();
		अगर (संकेत_pending(current)) अणु
			हटाओ_रुको_queue(&rp->b_रुको, &रुकोa);
			वापस -EINTR;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock_irqsave(&rp->b_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rp->b_lock, flags);

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&rp->b_रुको, &रुकोa);
	वापस 0;
पूर्ण

अटल पूर्णांक mon_alloc_buff(काष्ठा mon_pgmap *map, पूर्णांक npages)
अणु
	पूर्णांक n;
	अचिन्हित दीर्घ vaddr;

	क्रम (n = 0; n < npages; n++) अणु
		vaddr = get_zeroed_page(GFP_KERNEL);
		अगर (vaddr == 0) अणु
			जबतक (n-- != 0)
				मुक्त_page((अचिन्हित दीर्घ) map[n].ptr);
			वापस -ENOMEM;
		पूर्ण
		map[n].ptr = (अचिन्हित अक्षर *) vaddr;
		map[n].pg = virt_to_page((व्योम *) vaddr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mon_मुक्त_buff(काष्ठा mon_pgmap *map, पूर्णांक npages)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < npages; n++)
		मुक्त_page((अचिन्हित दीर्घ) map[n].ptr);
पूर्ण

पूर्णांक mon_bin_add(काष्ठा mon_bus *mbus, स्थिर काष्ठा usb_bus *ubus)
अणु
	काष्ठा device *dev;
	अचिन्हित minor = ubus? ubus->busnum: 0;

	अगर (minor >= MON_BIN_MAX_MINOR)
		वापस 0;

	dev = device_create(mon_bin_class, ubus ? ubus->controller : शून्य,
			    MKDEV(MAJOR(mon_bin_dev0), minor), शून्य,
			    "usbmon%d", minor);
	अगर (IS_ERR(dev))
		वापस 0;

	mbus->classdev = dev;
	वापस 1;
पूर्ण

व्योम mon_bin_del(काष्ठा mon_bus *mbus)
अणु
	device_destroy(mon_bin_class, mbus->classdev->devt);
पूर्ण

पूर्णांक __init mon_bin_init(व्योम)
अणु
	पूर्णांक rc;

	mon_bin_class = class_create(THIS_MODULE, "usbmon");
	अगर (IS_ERR(mon_bin_class)) अणु
		rc = PTR_ERR(mon_bin_class);
		जाओ err_class;
	पूर्ण

	rc = alloc_chrdev_region(&mon_bin_dev0, 0, MON_BIN_MAX_MINOR, "usbmon");
	अगर (rc < 0)
		जाओ err_dev;

	cdev_init(&mon_bin_cdev, &mon_fops_binary);
	mon_bin_cdev.owner = THIS_MODULE;

	rc = cdev_add(&mon_bin_cdev, mon_bin_dev0, MON_BIN_MAX_MINOR);
	अगर (rc < 0)
		जाओ err_add;

	वापस 0;

err_add:
	unरेजिस्टर_chrdev_region(mon_bin_dev0, MON_BIN_MAX_MINOR);
err_dev:
	class_destroy(mon_bin_class);
err_class:
	वापस rc;
पूर्ण

व्योम mon_bin_निकास(व्योम)
अणु
	cdev_del(&mon_bin_cdev);
	unरेजिस्टर_chrdev_region(mon_bin_dev0, MON_BIN_MAX_MINOR);
	class_destroy(mon_bin_class);
पूर्ण
