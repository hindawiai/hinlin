<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The USB Monitor, inspired by Dave Harding's USBMon.
 *
 * This is a text क्रमmat पढ़ोer.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/uaccess.h>

#समावेश "usb_mon.h"

/*
 * No, we करो not want arbitrarily दीर्घ data strings.
 * Use the binary पूर्णांकerface अगर you want to capture bulk data!
 */
#घोषणा DATA_MAX  32

/*
 * Defined by USB 2.0 clause 9.3, table 9.2.
 */
#घोषणा SETUP_MAX  8

/*
 * This limit exists to prevent OOMs when the user process stops पढ़ोing.
 * If usbmon were available to unprivileged processes, it might be खोलो
 * to a local DoS. But we have to keep to root in order to prevent
 * password snअगरfing from HID devices.
 */
#घोषणा EVENT_MAX  (4*PAGE_SIZE / माप(काष्ठा mon_event_text))

/*
 * Potentially unlimited number; we limit it क्रम similar allocations.
 * The usbfs limits this to 128, but we're not quite as generous.
 */
#घोषणा ISODESC_MAX   5

#घोषणा PRINTF_DFL  250   /* with 5 ISOs segs */

काष्ठा mon_iso_desc अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक length;	/* Unचिन्हित here, चिन्हित in URB. Historic. */
पूर्ण;

काष्ठा mon_event_text अणु
	काष्ठा list_head e_link;
	पूर्णांक type;		/* submit, complete, etc. */
	अचिन्हित दीर्घ id;	/* From poपूर्णांकer, most of the समय */
	अचिन्हित पूर्णांक tstamp;
	पूर्णांक busnum;
	अक्षर devnum;
	अक्षर epnum;
	अक्षर is_in;
	अक्षर xfertype;
	पूर्णांक length;		/* Depends on type: xfer length or act length */
	पूर्णांक status;
	पूर्णांक पूर्णांकerval;
	पूर्णांक start_frame;
	पूर्णांक error_count;
	अक्षर setup_flag;
	अक्षर data_flag;
	पूर्णांक numdesc;		/* Full number */
	काष्ठा mon_iso_desc isodesc[ISODESC_MAX];
	अचिन्हित अक्षर setup[SETUP_MAX];
	अचिन्हित अक्षर data[DATA_MAX];
पूर्ण;

#घोषणा SLAB_NAME_SZ  30
काष्ठा mon_पढ़ोer_text अणु
	काष्ठा kmem_cache *e_slab;
	पूर्णांक nevents;
	काष्ठा list_head e_list;
	काष्ठा mon_पढ़ोer r;	/* In C, parent class can be placed anywhere */

	रुको_queue_head_t रुको;
	पूर्णांक म_लिखो_size;
	माप_प्रकार म_लिखो_offset;
	माप_प्रकार म_लिखो_togo;
	अक्षर *म_लिखो_buf;
	काष्ठा mutex म_लिखो_lock;

	अक्षर slab_name[SLAB_NAME_SZ];
पूर्ण;

अटल काष्ठा dentry *mon_dir;		/* Usually /sys/kernel/debug/usbmon */

अटल व्योम mon_text_ctor(व्योम *);

काष्ठा mon_text_ptr अणु
	पूर्णांक cnt, limit;
	अक्षर *pbuf;
पूर्ण;

अटल काष्ठा mon_event_text *
    mon_text_पढ़ो_रुको(काष्ठा mon_पढ़ोer_text *rp, काष्ठा file *file);
अटल व्योम mon_text_पढ़ो_head_t(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_head_u(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_statset(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_पूर्णांकstat(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_isostat(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_isodesc(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);
अटल व्योम mon_text_पढ़ो_data(काष्ठा mon_पढ़ोer_text *rp,
    काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep);

/*
 * mon_text_submit
 * mon_text_complete
 *
 * May be called from an पूर्णांकerrupt.
 *
 * This is called with the whole mon_bus locked, so no additional lock.
 */

अटल अंतरभूत अक्षर mon_text_get_setup(काष्ठा mon_event_text *ep,
    काष्ठा urb *urb, अक्षर ev_type, काष्ठा mon_bus *mbus)
अणु

	अगर (ep->xfertype != USB_ENDPOINT_XFER_CONTROL || ev_type != 'S')
		वापस '-';

	अगर (urb->setup_packet == शून्य)
		वापस 'Z';	/* '0' would be not as pretty. */

	स_नकल(ep->setup, urb->setup_packet, SETUP_MAX);
	वापस 0;
पूर्ण

अटल अंतरभूत अक्षर mon_text_get_data(काष्ठा mon_event_text *ep, काष्ठा urb *urb,
    पूर्णांक len, अक्षर ev_type, काष्ठा mon_bus *mbus)
अणु
	व्योम *src;

	अगर (len <= 0)
		वापस 'L';
	अगर (len >= DATA_MAX)
		len = DATA_MAX;

	अगर (ep->is_in) अणु
		अगर (ev_type != 'C')
			वापस '<';
	पूर्ण अन्यथा अणु
		अगर (ev_type != 'S')
			वापस '>';
	पूर्ण

	अगर (urb->num_sgs == 0) अणु
		src = urb->transfer_buffer;
		अगर (src == शून्य)
			वापस 'Z';	/* '0' would be not as pretty. */
	पूर्ण अन्यथा अणु
		काष्ठा scatterlist *sg = urb->sg;

		अगर (PageHighMem(sg_page(sg)))
			वापस 'D';

		/* For the text पूर्णांकerface we copy only the first sg buffer */
		len = min_t(पूर्णांक, sg->length, len);
		src = sg_virt(sg);
	पूर्ण

	स_नकल(ep->data, src, len);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mon_get_बारtamp(व्योम)
अणु
	काष्ठा बारpec64 now;
	अचिन्हित पूर्णांक stamp;

	kसमय_get_ts64(&now);
	stamp = now.tv_sec & 0xFFF;  /* 2^32 = 4294967296. Limit to 4096s. */
	stamp = stamp * USEC_PER_SEC + now.tv_nsec / NSEC_PER_USEC;
	वापस stamp;
पूर्ण

अटल व्योम mon_text_event(काष्ठा mon_पढ़ोer_text *rp, काष्ठा urb *urb,
    अक्षर ev_type, पूर्णांक status)
अणु
	काष्ठा mon_event_text *ep;
	अचिन्हित पूर्णांक stamp;
	काष्ठा usb_iso_packet_descriptor *fp;
	काष्ठा mon_iso_desc *dp;
	पूर्णांक i, ndesc;

	stamp = mon_get_बारtamp();

	अगर (rp->nevents >= EVENT_MAX ||
	    (ep = kmem_cache_alloc(rp->e_slab, GFP_ATOMIC)) == शून्य) अणु
		rp->r.m_bus->cnt_text_lost++;
		वापस;
	पूर्ण

	ep->type = ev_type;
	ep->id = (अचिन्हित दीर्घ) urb;
	ep->busnum = urb->dev->bus->busnum;
	ep->devnum = urb->dev->devnum;
	ep->epnum = usb_endpoपूर्णांक_num(&urb->ep->desc);
	ep->xfertype = usb_endpoपूर्णांक_type(&urb->ep->desc);
	ep->is_in = usb_urb_dir_in(urb);
	ep->tstamp = stamp;
	ep->length = (ev_type == 'S') ?
	    urb->transfer_buffer_length : urb->actual_length;
	/* Collecting status makes debugging sense क्रम submits, too */
	ep->status = status;

	अगर (ep->xfertype == USB_ENDPOINT_XFER_INT) अणु
		ep->पूर्णांकerval = urb->पूर्णांकerval;
	पूर्ण अन्यथा अगर (ep->xfertype == USB_ENDPOINT_XFER_ISOC) अणु
		ep->पूर्णांकerval = urb->पूर्णांकerval;
		ep->start_frame = urb->start_frame;
		ep->error_count = urb->error_count;
	पूर्ण
	ep->numdesc = urb->number_of_packets;
	अगर (ep->xfertype == USB_ENDPOINT_XFER_ISOC &&
			urb->number_of_packets > 0) अणु
		अगर ((ndesc = urb->number_of_packets) > ISODESC_MAX)
			ndesc = ISODESC_MAX;
		fp = urb->iso_frame_desc;
		dp = ep->isodesc;
		क्रम (i = 0; i < ndesc; i++) अणु
			dp->status = fp->status;
			dp->offset = fp->offset;
			dp->length = (ev_type == 'S') ?
			    fp->length : fp->actual_length;
			fp++;
			dp++;
		पूर्ण
		/* Wasteful, but simple to understand: ISO 'C' is sparse. */
		अगर (ev_type == 'C')
			ep->length = urb->transfer_buffer_length;
	पूर्ण

	ep->setup_flag = mon_text_get_setup(ep, urb, ev_type, rp->r.m_bus);
	ep->data_flag = mon_text_get_data(ep, urb, ep->length, ev_type,
			rp->r.m_bus);

	rp->nevents++;
	list_add_tail(&ep->e_link, &rp->e_list);
	wake_up(&rp->रुको);
पूर्ण

अटल व्योम mon_text_submit(व्योम *data, काष्ठा urb *urb)
अणु
	काष्ठा mon_पढ़ोer_text *rp = data;
	mon_text_event(rp, urb, 'S', -EINPROGRESS);
पूर्ण

अटल व्योम mon_text_complete(व्योम *data, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा mon_पढ़ोer_text *rp = data;
	mon_text_event(rp, urb, 'C', status);
पूर्ण

अटल व्योम mon_text_error(व्योम *data, काष्ठा urb *urb, पूर्णांक error)
अणु
	काष्ठा mon_पढ़ोer_text *rp = data;
	काष्ठा mon_event_text *ep;

	अगर (rp->nevents >= EVENT_MAX ||
	    (ep = kmem_cache_alloc(rp->e_slab, GFP_ATOMIC)) == शून्य) अणु
		rp->r.m_bus->cnt_text_lost++;
		वापस;
	पूर्ण

	ep->type = 'E';
	ep->id = (अचिन्हित दीर्घ) urb;
	ep->busnum = urb->dev->bus->busnum;
	ep->devnum = urb->dev->devnum;
	ep->epnum = usb_endpoपूर्णांक_num(&urb->ep->desc);
	ep->xfertype = usb_endpoपूर्णांक_type(&urb->ep->desc);
	ep->is_in = usb_urb_dir_in(urb);
	ep->tstamp = mon_get_बारtamp();
	ep->length = 0;
	ep->status = error;

	ep->setup_flag = '-';
	ep->data_flag = 'E';

	rp->nevents++;
	list_add_tail(&ep->e_link, &rp->e_list);
	wake_up(&rp->रुको);
पूर्ण

/*
 * Fetch next event from the circular buffer.
 */
अटल काष्ठा mon_event_text *mon_text_fetch(काष्ठा mon_पढ़ोer_text *rp,
    काष्ठा mon_bus *mbus)
अणु
	काष्ठा list_head *p;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbus->lock, flags);
	अगर (list_empty(&rp->e_list)) अणु
		spin_unlock_irqrestore(&mbus->lock, flags);
		वापस शून्य;
	पूर्ण
	p = rp->e_list.next;
	list_del(p);
	--rp->nevents;
	spin_unlock_irqrestore(&mbus->lock, flags);
	वापस list_entry(p, काष्ठा mon_event_text, e_link);
पूर्ण

/*
 */
अटल पूर्णांक mon_text_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mon_bus *mbus;
	काष्ठा mon_पढ़ोer_text *rp;
	पूर्णांक rc;

	mutex_lock(&mon_lock);
	mbus = inode->i_निजी;

	rp = kzalloc(माप(काष्ठा mon_पढ़ोer_text), GFP_KERNEL);
	अगर (rp == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	INIT_LIST_HEAD(&rp->e_list);
	init_रुकोqueue_head(&rp->रुको);
	mutex_init(&rp->म_लिखो_lock);

	rp->म_लिखो_size = PRINTF_DFL;
	rp->म_लिखो_buf = kदो_स्मृति(rp->म_लिखो_size, GFP_KERNEL);
	अगर (rp->म_लिखो_buf == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_alloc_pr;
	पूर्ण

	rp->r.m_bus = mbus;
	rp->r.r_data = rp;
	rp->r.rnf_submit = mon_text_submit;
	rp->r.rnf_error = mon_text_error;
	rp->r.rnf_complete = mon_text_complete;

	snम_लिखो(rp->slab_name, SLAB_NAME_SZ, "mon_text_%p", rp);
	rp->e_slab = kmem_cache_create(rp->slab_name,
	    माप(काष्ठा mon_event_text), माप(दीर्घ), 0,
	    mon_text_ctor);
	अगर (rp->e_slab == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_slab;
	पूर्ण

	mon_पढ़ोer_add(mbus, &rp->r);

	file->निजी_data = rp;
	mutex_unlock(&mon_lock);
	वापस 0;

// err_busy:
//	kmem_cache_destroy(rp->e_slab);
err_slab:
	kमुक्त(rp->म_लिखो_buf);
err_alloc_pr:
	kमुक्त(rp);
err_alloc:
	mutex_unlock(&mon_lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mon_text_copy_to_user(काष्ठा mon_पढ़ोer_text *rp,
    अक्षर __user * स्थिर buf, स्थिर माप_प्रकार nbytes)
अणु
	स्थिर माप_प्रकार togo = min(nbytes, rp->म_लिखो_togo);

	अगर (copy_to_user(buf, &rp->म_लिखो_buf[rp->म_लिखो_offset], togo))
		वापस -EFAULT;
	rp->म_लिखो_togo -= togo;
	rp->म_लिखो_offset += togo;
	वापस togo;
पूर्ण

/* ppos is not advanced since the llseek operation is not permitted. */
अटल sमाप_प्रकार mon_text_पढ़ो_t(काष्ठा file *file, अक्षर __user *buf,
    माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा mon_पढ़ोer_text *rp = file->निजी_data;
	काष्ठा mon_event_text *ep;
	काष्ठा mon_text_ptr ptr;
	sमाप_प्रकार ret;

	mutex_lock(&rp->म_लिखो_lock);

	अगर (rp->म_लिखो_togo == 0) अणु

		ep = mon_text_पढ़ो_रुको(rp, file);
		अगर (IS_ERR(ep)) अणु
			mutex_unlock(&rp->म_लिखो_lock);
			वापस PTR_ERR(ep);
		पूर्ण
		ptr.cnt = 0;
		ptr.pbuf = rp->म_लिखो_buf;
		ptr.limit = rp->म_लिखो_size;

		mon_text_पढ़ो_head_t(rp, &ptr, ep);
		mon_text_पढ़ो_statset(rp, &ptr, ep);
		ptr.cnt += scnम_लिखो(ptr.pbuf + ptr.cnt, ptr.limit - ptr.cnt,
		    " %d", ep->length);
		mon_text_पढ़ो_data(rp, &ptr, ep);

		rp->म_लिखो_togo = ptr.cnt;
		rp->म_लिखो_offset = 0;

		kmem_cache_मुक्त(rp->e_slab, ep);
	पूर्ण

	ret = mon_text_copy_to_user(rp, buf, nbytes);
	mutex_unlock(&rp->म_लिखो_lock);
	वापस ret;
पूर्ण

/* ppos is not advanced since the llseek operation is not permitted. */
अटल sमाप_प्रकार mon_text_पढ़ो_u(काष्ठा file *file, अक्षर __user *buf,
    माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा mon_पढ़ोer_text *rp = file->निजी_data;
	काष्ठा mon_event_text *ep;
	काष्ठा mon_text_ptr ptr;
	sमाप_प्रकार ret;

	mutex_lock(&rp->म_लिखो_lock);

	अगर (rp->म_लिखो_togo == 0) अणु

		ep = mon_text_पढ़ो_रुको(rp, file);
		अगर (IS_ERR(ep)) अणु
			mutex_unlock(&rp->म_लिखो_lock);
			वापस PTR_ERR(ep);
		पूर्ण
		ptr.cnt = 0;
		ptr.pbuf = rp->म_लिखो_buf;
		ptr.limit = rp->म_लिखो_size;

		mon_text_पढ़ो_head_u(rp, &ptr, ep);
		अगर (ep->type == 'E') अणु
			mon_text_पढ़ो_statset(rp, &ptr, ep);
		पूर्ण अन्यथा अगर (ep->xfertype == USB_ENDPOINT_XFER_ISOC) अणु
			mon_text_पढ़ो_isostat(rp, &ptr, ep);
			mon_text_पढ़ो_isodesc(rp, &ptr, ep);
		पूर्ण अन्यथा अगर (ep->xfertype == USB_ENDPOINT_XFER_INT) अणु
			mon_text_पढ़ो_पूर्णांकstat(rp, &ptr, ep);
		पूर्ण अन्यथा अणु
			mon_text_पढ़ो_statset(rp, &ptr, ep);
		पूर्ण
		ptr.cnt += scnम_लिखो(ptr.pbuf + ptr.cnt, ptr.limit - ptr.cnt,
		    " %d", ep->length);
		mon_text_पढ़ो_data(rp, &ptr, ep);

		rp->म_लिखो_togo = ptr.cnt;
		rp->म_लिखो_offset = 0;

		kmem_cache_मुक्त(rp->e_slab, ep);
	पूर्ण

	ret = mon_text_copy_to_user(rp, buf, nbytes);
	mutex_unlock(&rp->म_लिखो_lock);
	वापस ret;
पूर्ण

अटल काष्ठा mon_event_text *mon_text_पढ़ो_रुको(काष्ठा mon_पढ़ोer_text *rp,
    काष्ठा file *file)
अणु
	काष्ठा mon_bus *mbus = rp->r.m_bus;
	DECLARE_WAITQUEUE(रुकोa, current);
	काष्ठा mon_event_text *ep;

	add_रुको_queue(&rp->रुको, &रुकोa);
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक ((ep = mon_text_fetch(rp, mbus)) == शून्य) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&rp->रुको, &रुकोa);
			वापस ERR_PTR(-EWOULDBLOCK);
		पूर्ण
		/*
		 * We करो not count nरुकोers, because ->release is supposed
		 * to be called when all खोलोers are gone only.
		 */
		schedule();
		अगर (संकेत_pending(current)) अणु
			हटाओ_रुको_queue(&rp->रुको, &रुकोa);
			वापस ERR_PTR(-EINTR);
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&rp->रुको, &रुकोa);
	वापस ep;
पूर्ण

अटल व्योम mon_text_पढ़ो_head_t(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	अक्षर udir, utype;

	udir = (ep->is_in ? 'i' : 'o');
	चयन (ep->xfertype) अणु
	हाल USB_ENDPOINT_XFER_ISOC:	utype = 'Z'; अवरोध;
	हाल USB_ENDPOINT_XFER_INT:	utype = 'I'; अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:	utype = 'C'; अवरोध;
	शेष: /* PIPE_BULK */  utype = 'B';
	पूर्ण
	p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
	    "%lx %u %c %c%c:%03u:%02u",
	    ep->id, ep->tstamp, ep->type,
	    utype, udir, ep->devnum, ep->epnum);
पूर्ण

अटल व्योम mon_text_पढ़ो_head_u(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	अक्षर udir, utype;

	udir = (ep->is_in ? 'i' : 'o');
	चयन (ep->xfertype) अणु
	हाल USB_ENDPOINT_XFER_ISOC:	utype = 'Z'; अवरोध;
	हाल USB_ENDPOINT_XFER_INT:	utype = 'I'; अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:	utype = 'C'; अवरोध;
	शेष: /* PIPE_BULK */  utype = 'B';
	पूर्ण
	p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
	    "%lx %u %c %c%c:%d:%03u:%u",
	    ep->id, ep->tstamp, ep->type,
	    utype, udir, ep->busnum, ep->devnum, ep->epnum);
पूर्ण

अटल व्योम mon_text_पढ़ो_statset(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु

	अगर (ep->setup_flag == 0) अणु   /* Setup packet is present and captured */
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " s %02x %02x %04x %04x %04x",
		    ep->setup[0],
		    ep->setup[1],
		    (ep->setup[3] << 8) | ep->setup[2],
		    (ep->setup[5] << 8) | ep->setup[4],
		    (ep->setup[7] << 8) | ep->setup[6]);
	पूर्ण अन्यथा अगर (ep->setup_flag != '-') अणु /* Unable to capture setup packet */
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %c __ __ ____ ____ ____", ep->setup_flag);
	पूर्ण अन्यथा अणु                     /* No setup क्रम this kind of URB */
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d", ep->status);
	पूर्ण
पूर्ण

अटल व्योम mon_text_पढ़ो_पूर्णांकstat(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
	    " %d:%d", ep->status, ep->पूर्णांकerval);
पूर्ण

अटल व्योम mon_text_पढ़ो_isostat(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	अगर (ep->type == 'S') अणु
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d:%d:%d", ep->status, ep->पूर्णांकerval, ep->start_frame);
	पूर्ण अन्यथा अणु
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d:%d:%d:%d",
		    ep->status, ep->पूर्णांकerval, ep->start_frame, ep->error_count);
	पूर्ण
पूर्ण

अटल व्योम mon_text_पढ़ो_isodesc(काष्ठा mon_पढ़ोer_text *rp,
	काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	पूर्णांक ndesc;	/* Display this many */
	पूर्णांक i;
	स्थिर काष्ठा mon_iso_desc *dp;

	p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
	    " %d", ep->numdesc);
	ndesc = ep->numdesc;
	अगर (ndesc > ISODESC_MAX)
		ndesc = ISODESC_MAX;
	अगर (ndesc < 0)
		ndesc = 0;
	dp = ep->isodesc;
	क्रम (i = 0; i < ndesc; i++) अणु
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d:%u:%u", dp->status, dp->offset, dp->length);
		dp++;
	पूर्ण
पूर्ण

अटल व्योम mon_text_पढ़ो_data(काष्ठा mon_पढ़ोer_text *rp,
    काष्ठा mon_text_ptr *p, स्थिर काष्ठा mon_event_text *ep)
अणु
	पूर्णांक data_len, i;

	अगर ((data_len = ep->length) > 0) अणु
		अगर (ep->data_flag == 0) अणु
			p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
			    " =");
			अगर (data_len >= DATA_MAX)
				data_len = DATA_MAX;
			क्रम (i = 0; i < data_len; i++) अणु
				अगर (i % 4 == 0) अणु
					p->cnt += scnम_लिखो(p->pbuf + p->cnt,
					    p->limit - p->cnt,
					    " ");
				पूर्ण
				p->cnt += scnम_लिखो(p->pbuf + p->cnt,
				    p->limit - p->cnt,
				    "%02x", ep->data[i]);
			पूर्ण
			p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
			    "\n");
		पूर्ण अन्यथा अणु
			p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt,
			    " %c\n", ep->data_flag);
		पूर्ण
	पूर्ण अन्यथा अणु
		p->cnt += scnम_लिखो(p->pbuf + p->cnt, p->limit - p->cnt, "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक mon_text_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mon_पढ़ोer_text *rp = file->निजी_data;
	काष्ठा mon_bus *mbus;
	/* अचिन्हित दीर्घ flags; */
	काष्ठा list_head *p;
	काष्ठा mon_event_text *ep;

	mutex_lock(&mon_lock);
	mbus = inode->i_निजी;

	अगर (mbus->nपढ़ोers <= 0) अणु
		prपूर्णांकk(KERN_ERR TAG ": consistency error on close\n");
		mutex_unlock(&mon_lock);
		वापस 0;
	पूर्ण
	mon_पढ़ोer_del(mbus, &rp->r);

	/*
	 * In theory, e_list is रक्षित by mbus->lock. However,
	 * after mon_पढ़ोer_del has finished, the following is the हाल:
	 *  - we are not on पढ़ोer list anymore, so new events won't be added;
	 *  - whole mbus may be dropped अगर it was orphaned.
	 * So, we better not touch mbus.
	 */
	/* spin_lock_irqsave(&mbus->lock, flags); */
	जबतक (!list_empty(&rp->e_list)) अणु
		p = rp->e_list.next;
		ep = list_entry(p, काष्ठा mon_event_text, e_link);
		list_del(p);
		--rp->nevents;
		kmem_cache_मुक्त(rp->e_slab, ep);
	पूर्ण
	/* spin_unlock_irqrestore(&mbus->lock, flags); */

	kmem_cache_destroy(rp->e_slab);
	kमुक्त(rp->म_लिखो_buf);
	kमुक्त(rp);

	mutex_unlock(&mon_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mon_fops_text_t = अणु
	.owner =	THIS_MODULE,
	.खोलो =		mon_text_खोलो,
	.llseek =	no_llseek,
	.पढ़ो =		mon_text_पढ़ो_t,
	.release =	mon_text_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations mon_fops_text_u = अणु
	.owner =	THIS_MODULE,
	.खोलो =		mon_text_खोलो,
	.llseek =	no_llseek,
	.पढ़ो =		mon_text_पढ़ो_u,
	.release =	mon_text_release,
पूर्ण;

पूर्णांक mon_text_add(काष्ठा mon_bus *mbus, स्थिर काष्ठा usb_bus *ubus)
अणु
	क्रमागत अणु NAMESZ = 10 पूर्ण;
	अक्षर name[NAMESZ];
	पूर्णांक busnum = ubus? ubus->busnum: 0;
	पूर्णांक rc;

	अगर (mon_dir == शून्य)
		वापस 0;

	अगर (ubus != शून्य) अणु
		rc = snम_लिखो(name, NAMESZ, "%dt", busnum);
		अगर (rc <= 0 || rc >= NAMESZ)
			जाओ err_prपूर्णांक_t;
		mbus->dent_t = debugfs_create_file(name, 0600, mon_dir, mbus,
							     &mon_fops_text_t);
	पूर्ण

	rc = snम_लिखो(name, NAMESZ, "%du", busnum);
	अगर (rc <= 0 || rc >= NAMESZ)
		जाओ err_prपूर्णांक_u;
	mbus->dent_u = debugfs_create_file(name, 0600, mon_dir, mbus,
					   &mon_fops_text_u);

	rc = snम_लिखो(name, NAMESZ, "%ds", busnum);
	अगर (rc <= 0 || rc >= NAMESZ)
		जाओ err_prपूर्णांक_s;
	mbus->dent_s = debugfs_create_file(name, 0600, mon_dir, mbus,
					   &mon_fops_stat);

	वापस 1;

err_prपूर्णांक_s:
	debugfs_हटाओ(mbus->dent_u);
	mbus->dent_u = शून्य;
err_prपूर्णांक_u:
	अगर (ubus != शून्य) अणु
		debugfs_हटाओ(mbus->dent_t);
		mbus->dent_t = शून्य;
	पूर्ण
err_prपूर्णांक_t:
	वापस 0;
पूर्ण

व्योम mon_text_del(काष्ठा mon_bus *mbus)
अणु
	debugfs_हटाओ(mbus->dent_u);
	debugfs_हटाओ(mbus->dent_t);
	debugfs_हटाओ(mbus->dent_s);
पूर्ण

/*
 * Slab पूर्णांकerface: स्थिरructor.
 */
अटल व्योम mon_text_ctor(व्योम *mem)
अणु
	/*
	 * Nothing to initialize. No, really!
	 * So, we fill it with garbage to emulate a reused object.
	 */
	स_रखो(mem, 0xe5, माप(काष्ठा mon_event_text));
पूर्ण

पूर्णांक __init mon_text_init(व्योम)
अणु
	mon_dir = debugfs_create_dir("usbmon", usb_debug_root);
	वापस 0;
पूर्ण

व्योम mon_text_निकास(व्योम)
अणु
	debugfs_हटाओ(mon_dir);
पूर्ण
