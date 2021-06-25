<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * xen console driver पूर्णांकerface to hvc_console.c
 *
 * (c) 2007 Gerd Hoffmann <kraxel@suse.de>
 */

#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/serial_core.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/hvm.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/page.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/io/console.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/hvc-console.h>
#समावेश <xen/xenbus.h>

#समावेश "hvc_console.h"

#घोषणा HVC_COOKIE   0x58656e /* "Xen" in hex */

काष्ठा xencons_info अणु
	काष्ठा list_head list;
	काष्ठा xenbus_device *xbdev;
	काष्ठा xencons_पूर्णांकerface *पूर्णांकf;
	अचिन्हित पूर्णांक evtchn;
	काष्ठा hvc_काष्ठा *hvc;
	पूर्णांक irq;
	पूर्णांक vtermno;
	grant_ref_t gntref;
पूर्ण;

अटल LIST_HEAD(xenconsoles);
अटल DEFINE_SPINLOCK(xencons_lock);

/* ------------------------------------------------------------------ */

अटल काष्ठा xencons_info *vtermno_to_xencons(पूर्णांक vtermno)
अणु
	काष्ठा xencons_info *entry, *n, *ret = शून्य;

	अगर (list_empty(&xenconsoles))
			वापस शून्य;

	list_क्रम_each_entry_safe(entry, n, &xenconsoles, list) अणु
		अगर (entry->vtermno == vtermno) अणु
			ret  = entry;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xenbus_devid_to_vtermno(पूर्णांक devid)
अणु
	वापस devid + HVC_COOKIE;
पूर्ण

अटल अंतरभूत व्योम notअगरy_daemon(काष्ठा xencons_info *cons)
अणु
	/* Use evtchn: this is called early, beक्रमe irq is set up. */
	notअगरy_remote_via_evtchn(cons->evtchn);
पूर्ण

अटल पूर्णांक __ग_लिखो_console(काष्ठा xencons_info *xencons,
		स्थिर अक्षर *data, पूर्णांक len)
अणु
	XENCONS_RING_IDX cons, prod;
	काष्ठा xencons_पूर्णांकerface *पूर्णांकf = xencons->पूर्णांकf;
	पूर्णांक sent = 0;

	cons = पूर्णांकf->out_cons;
	prod = पूर्णांकf->out_prod;
	mb();			/* update queue values beक्रमe going on */
	BUG_ON((prod - cons) > माप(पूर्णांकf->out));

	जबतक ((sent < len) && ((prod - cons) < माप(पूर्णांकf->out)))
		पूर्णांकf->out[MASK_XENCONS_IDX(prod++, पूर्णांकf->out)] = data[sent++];

	wmb();			/* ग_लिखो ring beक्रमe updating poपूर्णांकer */
	पूर्णांकf->out_prod = prod;

	अगर (sent)
		notअगरy_daemon(xencons);
	वापस sent;
पूर्ण

अटल पूर्णांक करोmU_ग_लिखो_console(uपूर्णांक32_t vtermno, स्थिर अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक ret = len;
	काष्ठा xencons_info *cons = vtermno_to_xencons(vtermno);
	अगर (cons == शून्य)
		वापस -EINVAL;

	/*
	 * Make sure the whole buffer is emitted, polling अगर
	 * necessary.  We करोn't ever want to rely on the hvc daemon
	 * because the most पूर्णांकeresting console output is when the
	 * kernel is crippled.
	 */
	जबतक (len) अणु
		पूर्णांक sent = __ग_लिखो_console(cons, data, len);
		
		data += sent;
		len -= sent;

		अगर (unlikely(len))
			HYPERVISOR_sched_op(SCHEDOP_yield, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक करोmU_पढ़ो_console(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा xencons_पूर्णांकerface *पूर्णांकf;
	XENCONS_RING_IDX cons, prod;
	पूर्णांक recv = 0;
	काष्ठा xencons_info *xencons = vtermno_to_xencons(vtermno);
	अगर (xencons == शून्य)
		वापस -EINVAL;
	पूर्णांकf = xencons->पूर्णांकf;

	cons = पूर्णांकf->in_cons;
	prod = पूर्णांकf->in_prod;
	mb();			/* get poपूर्णांकers beक्रमe पढ़ोing ring */
	BUG_ON((prod - cons) > माप(पूर्णांकf->in));

	जबतक (cons != prod && recv < len)
		buf[recv++] = पूर्णांकf->in[MASK_XENCONS_IDX(cons++, पूर्णांकf->in)];

	mb();			/* पढ़ो ring beक्रमe consuming */
	पूर्णांकf->in_cons = cons;

	notअगरy_daemon(xencons);
	वापस recv;
पूर्ण

अटल स्थिर काष्ठा hv_ops करोmU_hvc_ops = अणु
	.get_अक्षरs = करोmU_पढ़ो_console,
	.put_अक्षरs = करोmU_ग_लिखो_console,
	.notअगरier_add = notअगरier_add_irq,
	.notअगरier_del = notअगरier_del_irq,
	.notअगरier_hangup = notअगरier_hangup_irq,
पूर्ण;

अटल पूर्णांक करोm0_पढ़ो_console(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक len)
अणु
	वापस HYPERVISOR_console_io(CONSOLEIO_पढ़ो, len, buf);
पूर्ण

/*
 * Either क्रम a करोm0 to ग_लिखो to the प्रणाली console, or a करोmU with a
 * debug version of Xen
 */
अटल पूर्णांक करोm0_ग_लिखो_console(uपूर्णांक32_t vtermno, स्थिर अक्षर *str, पूर्णांक len)
अणु
	पूर्णांक rc = HYPERVISOR_console_io(CONSOLEIO_ग_लिखो, len, (अक्षर *)str);
	अगर (rc < 0)
		वापस rc;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा hv_ops करोm0_hvc_ops = अणु
	.get_अक्षरs = करोm0_पढ़ो_console,
	.put_अक्षरs = करोm0_ग_लिखो_console,
	.notअगरier_add = notअगरier_add_irq,
	.notअगरier_del = notअगरier_del_irq,
	.notअगरier_hangup = notअगरier_hangup_irq,
पूर्ण;

अटल पूर्णांक xen_hvm_console_init(व्योम)
अणु
	पूर्णांक r;
	uपूर्णांक64_t v = 0;
	अचिन्हित दीर्घ gfn;
	काष्ठा xencons_info *info;

	अगर (!xen_hvm_करोमुख्य())
		वापस -ENODEV;

	info = vtermno_to_xencons(HVC_COOKIE);
	अगर (!info) अणु
		info = kzalloc(माप(काष्ठा xencons_info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;
	पूर्ण अन्यथा अगर (info->पूर्णांकf != शून्य) अणु
		/* alपढ़ोy configured */
		वापस 0;
	पूर्ण
	/*
	 * If the toolstack (or the hypervisor) hasn't set these values, the
	 * शेष value is 0. Even though gfn = 0 and evtchn = 0 are
	 * theoretically correct values, in practice they never are and they
	 * mean that a legacy toolstack hasn't initialized the pv console correctly.
	 */
	r = hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN, &v);
	अगर (r < 0 || v == 0)
		जाओ err;
	info->evtchn = v;
	v = 0;
	r = hvm_get_parameter(HVM_PARAM_CONSOLE_PFN, &v);
	अगर (r < 0 || v == 0)
		जाओ err;
	gfn = v;
	info->पूर्णांकf = xen_remap(gfn << XEN_PAGE_SHIFT, XEN_PAGE_SIZE);
	अगर (info->पूर्णांकf == शून्य)
		जाओ err;
	info->vtermno = HVC_COOKIE;

	spin_lock(&xencons_lock);
	list_add_tail(&info->list, &xenconsoles);
	spin_unlock(&xencons_lock);

	वापस 0;
err:
	kमुक्त(info);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक xencons_info_pv_init(काष्ठा xencons_info *info, पूर्णांक vtermno)
अणु
	info->evtchn = xen_start_info->console.करोmU.evtchn;
	/* GFN == MFN क्रम PV guest */
	info->पूर्णांकf = gfn_to_virt(xen_start_info->console.करोmU.mfn);
	info->vtermno = vtermno;

	list_add_tail(&info->list, &xenconsoles);

	वापस 0;
पूर्ण

अटल पूर्णांक xen_pv_console_init(व्योम)
अणु
	काष्ठा xencons_info *info;

	अगर (!xen_pv_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_start_info->console.करोmU.evtchn)
		वापस -ENODEV;

	info = vtermno_to_xencons(HVC_COOKIE);
	अगर (!info) अणु
		info = kzalloc(माप(काष्ठा xencons_info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;
	पूर्ण अन्यथा अगर (info->पूर्णांकf != शून्य) अणु
		/* alपढ़ोy configured */
		वापस 0;
	पूर्ण
	spin_lock(&xencons_lock);
	xencons_info_pv_init(info, HVC_COOKIE);
	spin_unlock(&xencons_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक xen_initial_करोमुख्य_console_init(व्योम)
अणु
	काष्ठा xencons_info *info;

	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	info = vtermno_to_xencons(HVC_COOKIE);
	अगर (!info) अणु
		info = kzalloc(माप(काष्ठा xencons_info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;
	पूर्ण

	info->irq = bind_virq_to_irq(VIRQ_CONSOLE, 0, false);
	info->vtermno = HVC_COOKIE;

	spin_lock(&xencons_lock);
	list_add_tail(&info->list, &xenconsoles);
	spin_unlock(&xencons_lock);

	वापस 0;
पूर्ण

अटल व्योम xen_console_update_evtchn(काष्ठा xencons_info *info)
अणु
	अगर (xen_hvm_करोमुख्य()) अणु
		uपूर्णांक64_t v = 0;
		पूर्णांक err;

		err = hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN, &v);
		अगर (!err && v)
			info->evtchn = v;
	पूर्ण अन्यथा
		info->evtchn = xen_start_info->console.करोmU.evtchn;
पूर्ण

व्योम xen_console_resume(व्योम)
अणु
	काष्ठा xencons_info *info = vtermno_to_xencons(HVC_COOKIE);
	अगर (info != शून्य && info->irq) अणु
		अगर (!xen_initial_करोमुख्य())
			xen_console_update_evtchn(info);
		rebind_evtchn_irq(info->evtchn, info->irq);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HVC_XEN_FRONTEND
अटल व्योम xencons_disconnect_backend(काष्ठा xencons_info *info)
अणु
	अगर (info->irq > 0)
		unbind_from_irqhandler(info->irq, शून्य);
	info->irq = 0;
	अगर (info->evtchn > 0)
		xenbus_मुक्त_evtchn(info->xbdev, info->evtchn);
	info->evtchn = 0;
	अगर (info->gntref > 0)
		gnttab_मुक्त_grant_references(info->gntref);
	info->gntref = 0;
	अगर (info->hvc != शून्य)
		hvc_हटाओ(info->hvc);
	info->hvc = शून्य;
पूर्ण

अटल व्योम xencons_मुक्त(काष्ठा xencons_info *info)
अणु
	मुक्त_page((अचिन्हित दीर्घ)info->पूर्णांकf);
	info->पूर्णांकf = शून्य;
	info->vtermno = 0;
	kमुक्त(info);
पूर्ण

अटल पूर्णांक xen_console_हटाओ(काष्ठा xencons_info *info)
अणु
	xencons_disconnect_backend(info);
	spin_lock(&xencons_lock);
	list_del(&info->list);
	spin_unlock(&xencons_lock);
	अगर (info->xbdev != शून्य)
		xencons_मुक्त(info);
	अन्यथा अणु
		अगर (xen_hvm_करोमुख्य())
			iounmap(info->पूर्णांकf);
		kमुक्त(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xencons_हटाओ(काष्ठा xenbus_device *dev)
अणु
	वापस xen_console_हटाओ(dev_get_drvdata(&dev->dev));
पूर्ण

अटल पूर्णांक xencons_connect_backend(काष्ठा xenbus_device *dev,
				  काष्ठा xencons_info *info)
अणु
	पूर्णांक ret, evtchn, devid, ref, irq;
	काष्ठा xenbus_transaction xbt;
	grant_ref_t gref_head;

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	अगर (ret)
		वापस ret;
	info->evtchn = evtchn;
	irq = bind_evtchn_to_irq(evtchn);
	अगर (irq < 0)
		वापस irq;
	info->irq = irq;
	devid = dev->nodename[म_माप(dev->nodename) - 1] - '0';
	info->hvc = hvc_alloc(xenbus_devid_to_vtermno(devid),
			irq, &करोmU_hvc_ops, 256);
	अगर (IS_ERR(info->hvc))
		वापस PTR_ERR(info->hvc);
	ret = gnttab_alloc_grant_references(1, &gref_head);
	अगर (ret < 0)
		वापस ret;
	info->gntref = gref_head;
	ref = gnttab_claim_grant_reference(&gref_head);
	अगर (ref < 0)
		वापस ref;
	gnttab_grant_क्रमeign_access_ref(ref, info->xbdev->otherend_id,
					virt_to_gfn(info->पूर्णांकf), 0);

 again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "starting transaction");
		वापस ret;
	पूर्ण
	ret = xenbus_म_लिखो(xbt, dev->nodename, "ring-ref", "%d", ref);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "port", "%u",
			    evtchn);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret) अणु
		अगर (ret == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		वापस ret;
	पूर्ण

	xenbus_चयन_state(dev, XenbusStateInitialised);
	वापस 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
	वापस ret;
पूर्ण

अटल पूर्णांक xencons_probe(काष्ठा xenbus_device *dev,
				  स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक ret, devid;
	काष्ठा xencons_info *info;

	devid = dev->nodename[म_माप(dev->nodename) - 1] - '0';
	अगर (devid == 0)
		वापस -ENODEV;

	info = kzalloc(माप(काष्ठा xencons_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	dev_set_drvdata(&dev->dev, info);
	info->xbdev = dev;
	info->vtermno = xenbus_devid_to_vtermno(devid);
	info->पूर्णांकf = (व्योम *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!info->पूर्णांकf)
		जाओ error_nomem;

	ret = xencons_connect_backend(dev, info);
	अगर (ret < 0)
		जाओ error;
	spin_lock(&xencons_lock);
	list_add_tail(&info->list, &xenconsoles);
	spin_unlock(&xencons_lock);

	वापस 0;

 error_nomem:
	ret = -ENOMEM;
	xenbus_dev_fatal(dev, ret, "allocating device memory");
 error:
	xencons_disconnect_backend(info);
	xencons_मुक्त(info);
	वापस ret;
पूर्ण

अटल पूर्णांक xencons_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xencons_info *info = dev_get_drvdata(&dev->dev);

	xencons_disconnect_backend(info);
	स_रखो(info->पूर्णांकf, 0, XEN_PAGE_SIZE);
	वापस xencons_connect_backend(dev, info);
पूर्ण

अटल व्योम xencons_backend_changed(काष्ठा xenbus_device *dev,
				   क्रमागत xenbus_state backend_state)
अणु
	चयन (backend_state) अणु
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		अवरोध;

	हाल XenbusStateConnected:
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xencons_ids[] = अणु
	अणु "console" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xencons_driver = अणु
	.name = "xenconsole",
	.ids = xencons_ids,
	.probe = xencons_probe,
	.हटाओ = xencons_हटाओ,
	.resume = xencons_resume,
	.otherend_changed = xencons_backend_changed,
पूर्ण;
#पूर्ण_अगर /* CONFIG_HVC_XEN_FRONTEND */

अटल पूर्णांक __init xen_hvc_init(व्योम)
अणु
	पूर्णांक r;
	काष्ठा xencons_info *info;
	स्थिर काष्ठा hv_ops *ops;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (xen_initial_करोमुख्य()) अणु
		ops = &करोm0_hvc_ops;
		r = xen_initial_करोमुख्य_console_init();
		अगर (r < 0)
			वापस r;
		info = vtermno_to_xencons(HVC_COOKIE);
	पूर्ण अन्यथा अणु
		ops = &करोmU_hvc_ops;
		अगर (xen_hvm_करोमुख्य())
			r = xen_hvm_console_init();
		अन्यथा
			r = xen_pv_console_init();
		अगर (r < 0)
			वापस r;

		info = vtermno_to_xencons(HVC_COOKIE);
		info->irq = bind_evtchn_to_irq(info->evtchn);
	पूर्ण
	अगर (info->irq < 0)
		info->irq = 0; /* NO_IRQ */
	अन्यथा
		irq_set_noprobe(info->irq);

	info->hvc = hvc_alloc(HVC_COOKIE, info->irq, ops, 256);
	अगर (IS_ERR(info->hvc)) अणु
		r = PTR_ERR(info->hvc);
		spin_lock(&xencons_lock);
		list_del(&info->list);
		spin_unlock(&xencons_lock);
		अगर (info->irq)
			unbind_from_irqhandler(info->irq, शून्य);
		kमुक्त(info);
		वापस r;
	पूर्ण

	r = 0;
#अगर_घोषित CONFIG_HVC_XEN_FRONTEND
	r = xenbus_रेजिस्टर_frontend(&xencons_driver);
#पूर्ण_अगर
	वापस r;
पूर्ण
device_initcall(xen_hvc_init);

अटल पूर्णांक xen_cons_init(व्योम)
अणु
	स्थिर काष्ठा hv_ops *ops;

	अगर (!xen_करोमुख्य())
		वापस 0;

	अगर (xen_initial_करोमुख्य())
		ops = &करोm0_hvc_ops;
	अन्यथा अणु
		पूर्णांक r;
		ops = &करोmU_hvc_ops;

		अगर (xen_hvm_करोमुख्य())
			r = xen_hvm_console_init();
		अन्यथा
			r = xen_pv_console_init();
		अगर (r < 0)
			वापस r;
	पूर्ण

	hvc_instantiate(HVC_COOKIE, 0, ops);
	वापस 0;
पूर्ण
console_initcall(xen_cons_init);

#अगर_घोषित CONFIG_X86
अटल व्योम xen_hvm_early_ग_लिखो(uपूर्णांक32_t vtermno, स्थिर अक्षर *str, पूर्णांक len)
अणु
	अगर (xen_cpuid_base())
		outsb(0xe9, str, len);
पूर्ण
#अन्यथा
अटल व्योम xen_hvm_early_ग_लिखो(uपूर्णांक32_t vtermno, स्थिर अक्षर *str, पूर्णांक len) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EARLY_PRINTK
अटल पूर्णांक __init xenboot_console_setup(काष्ठा console *console, अक्षर *string)
अणु
	अटल काष्ठा xencons_info xenboot;

	अगर (xen_initial_करोमुख्य())
		वापस 0;
	अगर (!xen_pv_करोमुख्य())
		वापस -ENODEV;

	वापस xencons_info_pv_init(&xenboot, 0);
पूर्ण

अटल व्योम xenboot_ग_लिखो_console(काष्ठा console *console, स्थिर अक्षर *string,
				  अचिन्हित len)
अणु
	अचिन्हित पूर्णांक linelen, off = 0;
	स्थिर अक्षर *pos;

	अगर (!xen_pv_करोमुख्य()) अणु
		xen_hvm_early_ग_लिखो(0, string, len);
		वापस;
	पूर्ण

	करोm0_ग_लिखो_console(0, string, len);

	अगर (xen_initial_करोमुख्य())
		वापस;

	करोmU_ग_लिखो_console(0, "(early) ", 8);
	जबतक (off < len && शून्य != (pos = म_अक्षर(string+off, '\n'))) अणु
		linelen = pos-string+off;
		अगर (off + linelen > len)
			अवरोध;
		करोmU_ग_लिखो_console(0, string+off, linelen);
		करोmU_ग_लिखो_console(0, "\r\n", 2);
		off += linelen + 1;
	पूर्ण
	अगर (off < len)
		करोmU_ग_लिखो_console(0, string+off, len-off);
पूर्ण

काष्ठा console xenboot_console = अणु
	.name		= "xenboot",
	.ग_लिखो		= xenboot_ग_लिखो_console,
	.setup		= xenboot_console_setup,
	.flags		= CON_PRINTBUFFER | CON_BOOT | CON_ANYTIME,
	.index		= -1,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_EARLY_PRINTK */

व्योम xen_raw_console_ग_लिखो(स्थिर अक्षर *str)
अणु
	sमाप_प्रकार len = म_माप(str);
	पूर्णांक rc = 0;

	अगर (xen_करोमुख्य()) अणु
		rc = करोm0_ग_लिखो_console(0, str, len);
		अगर (rc != -ENOSYS || !xen_hvm_करोमुख्य())
			वापस;
	पूर्ण
	xen_hvm_early_ग_लिखो(0, str, len);
पूर्ण

व्योम xen_raw_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	अटल अक्षर buf[512];
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, ap);
	बहु_पूर्ण(ap);

	xen_raw_console_ग_लिखो(buf);
पूर्ण

अटल व्योम xenboot_earlycon_ग_लिखो(काष्ठा console *console,
				  स्थिर अक्षर *string,
				  अचिन्हित len)
अणु
	करोm0_ग_लिखो_console(0, string, len);
पूर्ण

अटल पूर्णांक __init xenboot_earlycon_setup(काष्ठा earlycon_device *device,
					    स्थिर अक्षर *opt)
अणु
	device->con->ग_लिखो = xenboot_earlycon_ग_लिखो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(xenboot, xenboot_earlycon_setup);
