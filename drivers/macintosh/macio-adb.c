<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the ADB controller in the Mac I/O (Hydra) chip.
 */
#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/adb.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hydra.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>

काष्ठा preg अणु
	अचिन्हित अक्षर r;
	अक्षर pad[15];
पूर्ण;

काष्ठा adb_regs अणु
	काष्ठा preg पूर्णांकr;
	काष्ठा preg data[9];
	काष्ठा preg पूर्णांकr_enb;
	काष्ठा preg dcount;
	काष्ठा preg error;
	काष्ठा preg ctrl;
	काष्ठा preg स्वतःpoll;
	काष्ठा preg active_hi;
	काष्ठा preg active_lo;
	काष्ठा preg test;
पूर्ण;

/* Bits in पूर्णांकr and पूर्णांकr_enb रेजिस्टरs */
#घोषणा DFB	1		/* data from bus */
#घोषणा TAG	2		/* transfer access grant */

/* Bits in dcount रेजिस्टर */
#घोषणा HMB	0x0f		/* how many bytes */
#घोषणा APD	0x10		/* स्वतः-poll data */

/* Bits in error रेजिस्टर */
#घोषणा NRE	1		/* no response error */
#घोषणा DLE	2		/* data lost error */

/* Bits in ctrl रेजिस्टर */
#घोषणा TAR	1		/* transfer access request */
#घोषणा DTB	2		/* data to bus */
#घोषणा CRE	4		/* command response expected */
#घोषणा ADB_RST	8		/* ADB reset */

/* Bits in स्वतःpoll रेजिस्टर */
#घोषणा APE	1		/* स्वतःpoll enable */

अटल अस्थिर काष्ठा adb_regs __iomem *adb;
अटल काष्ठा adb_request *current_req, *last_req;
अटल DEFINE_SPINLOCK(macio_lock);

अटल पूर्णांक macio_probe(व्योम);
अटल पूर्णांक macio_init(व्योम);
अटल irqवापस_t macio_adb_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg);
अटल पूर्णांक macio_send_request(काष्ठा adb_request *req, पूर्णांक sync);
अटल पूर्णांक macio_adb_स्वतःpoll(पूर्णांक devs);
अटल व्योम macio_adb_poll(व्योम);
अटल पूर्णांक macio_adb_reset_bus(व्योम);

काष्ठा adb_driver macio_adb_driver = अणु
	.name         = "MACIO",
	.probe        = macio_probe,
	.init         = macio_init,
	.send_request = macio_send_request,
	.स्वतःpoll     = macio_adb_स्वतःpoll,
	.poll         = macio_adb_poll,
	.reset_bus    = macio_adb_reset_bus,
पूर्ण;

पूर्णांक macio_probe(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, "adb", "chrp,adb0");
	अगर (np) अणु
		of_node_put(np);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

पूर्णांक macio_init(व्योम)
अणु
	काष्ठा device_node *adbs;
	काष्ठा resource r;
	अचिन्हित पूर्णांक irq;

	adbs = of_find_compatible_node(शून्य, "adb", "chrp,adb0");
	अगर (adbs == 0)
		वापस -ENXIO;

	अगर (of_address_to_resource(adbs, 0, &r)) अणु
		of_node_put(adbs);
		वापस -ENXIO;
	पूर्ण
	adb = ioremap(r.start, माप(काष्ठा adb_regs));

	out_8(&adb->ctrl.r, 0);
	out_8(&adb->पूर्णांकr.r, 0);
	out_8(&adb->error.r, 0);
	out_8(&adb->active_hi.r, 0xff); /* क्रम now, set all devices active */
	out_8(&adb->active_lo.r, 0xff);
	out_8(&adb->स्वतःpoll.r, APE);

	irq = irq_of_parse_and_map(adbs, 0);
	of_node_put(adbs);
	अगर (request_irq(irq, macio_adb_पूर्णांकerrupt, 0, "ADB", (व्योम *)0)) अणु
		prपूर्णांकk(KERN_ERR "ADB: can't get irq %d\n", irq);
		वापस -EAGAIN;
	पूर्ण
	out_8(&adb->पूर्णांकr_enb.r, DFB | TAG);

	prपूर्णांकk("adb: mac-io driver 1.0 for unified ADB\n");

	वापस 0;
पूर्ण

अटल पूर्णांक macio_adb_स्वतःpoll(पूर्णांक devs)
अणु
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&macio_lock, flags);
	out_8(&adb->active_hi.r, devs >> 8);
	out_8(&adb->active_lo.r, devs);
	out_8(&adb->स्वतःpoll.r, devs? APE: 0);
	spin_unlock_irqrestore(&macio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_adb_reset_bus(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout = 1000000;

	/* Hrm... we may want to not lock पूर्णांकerrupts क्रम so
	 * दीर्घ ... oh well, who uses that chip anyway ? :)
	 * That function will be selकरोm used during boot
	 * on rare machines, so...
	 */
	spin_lock_irqsave(&macio_lock, flags);
	out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | ADB_RST);
	जबतक ((in_8(&adb->ctrl.r) & ADB_RST) != 0) अणु
		अगर (--समयout == 0) अणु
			out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) & ~ADB_RST);
			spin_unlock_irqrestore(&macio_lock, flags);
			वापस -1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&macio_lock, flags);
	वापस 0;
पूर्ण

/* Send an ADB command */
अटल पूर्णांक macio_send_request(काष्ठा adb_request *req, पूर्णांक sync)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	
	अगर (req->data[0] != ADB_PACKET)
		वापस -EINVAL;
	
	क्रम (i = 0; i < req->nbytes - 1; ++i)
		req->data[i] = req->data[i+1];
	--req->nbytes;
	
	req->next = शून्य;
	req->sent = 0;
	req->complete = 0;
	req->reply_len = 0;

	spin_lock_irqsave(&macio_lock, flags);
	अगर (current_req != 0) अणु
		last_req->next = req;
		last_req = req;
	पूर्ण अन्यथा अणु
		current_req = last_req = req;
		out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
	पूर्ण
	spin_unlock_irqrestore(&macio_lock, flags);
	
	अगर (sync) अणु
		जबतक (!req->complete)
			macio_adb_poll();
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t macio_adb_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	पूर्णांक i, n, err;
	काष्ठा adb_request *req = शून्य;
	अचिन्हित अक्षर ibuf[16];
	पूर्णांक ibuf_len = 0;
	पूर्णांक complete = 0;
	पूर्णांक स्वतःpoll = 0;
	पूर्णांक handled = 0;

	spin_lock(&macio_lock);
	अगर (in_8(&adb->पूर्णांकr.r) & TAG) अणु
		handled = 1;
		अगर ((req = current_req) != 0) अणु
			/* put the current request in */
			क्रम (i = 0; i < req->nbytes; ++i)
				out_8(&adb->data[i].r, req->data[i]);
			out_8(&adb->dcount.r, req->nbytes & HMB);
			req->sent = 1;
			अगर (req->reply_expected) अणु
				out_8(&adb->ctrl.r, DTB + CRE);
			पूर्ण अन्यथा अणु
				out_8(&adb->ctrl.r, DTB);
				current_req = req->next;
				complete = 1;
				अगर (current_req)
					out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
			पूर्ण
		पूर्ण
		out_8(&adb->पूर्णांकr.r, 0);
	पूर्ण

	अगर (in_8(&adb->पूर्णांकr.r) & DFB) अणु
		handled = 1;
		err = in_8(&adb->error.r);
		अगर (current_req && current_req->sent) अणु
			/* this is the response to a command */
			req = current_req;
			अगर (err == 0) अणु
				req->reply_len = in_8(&adb->dcount.r) & HMB;
				क्रम (i = 0; i < req->reply_len; ++i)
					req->reply[i] = in_8(&adb->data[i].r);
			पूर्ण
			current_req = req->next;
			complete = 1;
			अगर (current_req)
				out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
		पूर्ण अन्यथा अगर (err == 0) अणु
			/* स्वतःpoll data */
			n = in_8(&adb->dcount.r) & HMB;
			क्रम (i = 0; i < n; ++i)
				ibuf[i] = in_8(&adb->data[i].r);
			ibuf_len = n;
			स्वतःpoll = (in_8(&adb->dcount.r) & APD) != 0;
		पूर्ण
		out_8(&adb->error.r, 0);
		out_8(&adb->पूर्णांकr.r, 0);
	पूर्ण
	spin_unlock(&macio_lock);
	अगर (complete && req) अणु
	    व्योम (*करोne)(काष्ठा adb_request *) = req->करोne;
	    mb();
	    req->complete = 1;
	    /* Here, we assume that अगर the request has a करोne member, the
    	     * काष्ठा request will survive to setting req->complete to 1
	     */
	    अगर (करोne)
		(*करोne)(req);
	पूर्ण
	अगर (ibuf_len)
		adb_input(ibuf, ibuf_len, स्वतःpoll);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम macio_adb_poll(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (in_8(&adb->पूर्णांकr.r) != 0)
		macio_adb_पूर्णांकerrupt(0, शून्य);
	local_irq_restore(flags);
पूर्ण
