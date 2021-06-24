<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/scatterlist.h>

#समावेश "usbip_common.h"
#समावेश "stub.h"

#घोषणा DRIVER_AUTHOR "Takahiro Hirofuchi"
#घोषणा DRIVER_DESC "USB/IP Host Driver"

काष्ठा kmem_cache *stub_priv_cache;

/*
 * busid_tables defines matching busids that usbip can grab. A user can change
 * dynamically what device is locally used and what device is exported to a
 * remote host.
 */
#घोषणा MAX_BUSID 16
अटल काष्ठा bus_id_priv busid_table[MAX_BUSID];
अटल DEFINE_SPINLOCK(busid_table_lock);

अटल व्योम init_busid_table(व्योम)
अणु
	पूर्णांक i;

	/*
	 * This also sets the bus_table[i].status to
	 * STUB_BUSID_OTHER, which is 0.
	 */
	स_रखो(busid_table, 0, माप(busid_table));

	क्रम (i = 0; i < MAX_BUSID; i++)
		spin_lock_init(&busid_table[i].busid_lock);
पूर्ण

/*
 * Find the index of the busid by name.
 * Must be called with busid_table_lock held.
 */
अटल पूर्णांक get_busid_idx(स्थिर अक्षर *busid)
अणु
	पूर्णांक i;
	पूर्णांक idx = -1;

	क्रम (i = 0; i < MAX_BUSID; i++) अणु
		spin_lock(&busid_table[i].busid_lock);
		अगर (busid_table[i].name[0])
			अगर (!म_भेदन(busid_table[i].name, busid, BUSID_SIZE)) अणु
				idx = i;
				spin_unlock(&busid_table[i].busid_lock);
				अवरोध;
			पूर्ण
		spin_unlock(&busid_table[i].busid_lock);
	पूर्ण
	वापस idx;
पूर्ण

/* Returns holding busid_lock. Should call put_busid_priv() to unlock */
काष्ठा bus_id_priv *get_busid_priv(स्थिर अक्षर *busid)
अणु
	पूर्णांक idx;
	काष्ठा bus_id_priv *bid = शून्य;

	spin_lock(&busid_table_lock);
	idx = get_busid_idx(busid);
	अगर (idx >= 0) अणु
		bid = &(busid_table[idx]);
		/* get busid_lock beक्रमe वापसing */
		spin_lock(&bid->busid_lock);
	पूर्ण
	spin_unlock(&busid_table_lock);

	वापस bid;
पूर्ण

व्योम put_busid_priv(काष्ठा bus_id_priv *bid)
अणु
	अगर (bid)
		spin_unlock(&bid->busid_lock);
पूर्ण

अटल पूर्णांक add_match_busid(अक्षर *busid)
अणु
	पूर्णांक i;
	पूर्णांक ret = -1;

	spin_lock(&busid_table_lock);
	/* alपढ़ोy रेजिस्टरed? */
	अगर (get_busid_idx(busid) >= 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < MAX_BUSID; i++) अणु
		spin_lock(&busid_table[i].busid_lock);
		अगर (!busid_table[i].name[0]) अणु
			strlcpy(busid_table[i].name, busid, BUSID_SIZE);
			अगर ((busid_table[i].status != STUB_BUSID_ALLOC) &&
			    (busid_table[i].status != STUB_BUSID_REMOV))
				busid_table[i].status = STUB_BUSID_ADDED;
			ret = 0;
			spin_unlock(&busid_table[i].busid_lock);
			अवरोध;
		पूर्ण
		spin_unlock(&busid_table[i].busid_lock);
	पूर्ण

out:
	spin_unlock(&busid_table_lock);

	वापस ret;
पूर्ण

पूर्णांक del_match_busid(अक्षर *busid)
अणु
	पूर्णांक idx;
	पूर्णांक ret = -1;

	spin_lock(&busid_table_lock);
	idx = get_busid_idx(busid);
	अगर (idx < 0)
		जाओ out;

	/* found */
	ret = 0;

	spin_lock(&busid_table[idx].busid_lock);

	अगर (busid_table[idx].status == STUB_BUSID_OTHER)
		स_रखो(busid_table[idx].name, 0, BUSID_SIZE);

	अगर ((busid_table[idx].status != STUB_BUSID_OTHER) &&
	    (busid_table[idx].status != STUB_BUSID_ADDED))
		busid_table[idx].status = STUB_BUSID_REMOV;

	spin_unlock(&busid_table[idx].busid_lock);
out:
	spin_unlock(&busid_table_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार match_busid_show(काष्ठा device_driver *drv, अक्षर *buf)
अणु
	पूर्णांक i;
	अक्षर *out = buf;

	spin_lock(&busid_table_lock);
	क्रम (i = 0; i < MAX_BUSID; i++) अणु
		spin_lock(&busid_table[i].busid_lock);
		अगर (busid_table[i].name[0])
			out += प्र_लिखो(out, "%s ", busid_table[i].name);
		spin_unlock(&busid_table[i].busid_lock);
	पूर्ण
	spin_unlock(&busid_table_lock);
	out += प्र_लिखो(out, "\n");

	वापस out - buf;
पूर्ण

अटल sमाप_प्रकार match_busid_store(काष्ठा device_driver *dev, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक len;
	अक्षर busid[BUSID_SIZE];

	अगर (count < 5)
		वापस -EINVAL;

	/* busid needs to include \0 termination */
	len = strlcpy(busid, buf + 4, BUSID_SIZE);
	अगर (माप(busid) <= len)
		वापस -EINVAL;

	अगर (!म_भेदन(buf, "add ", 4)) अणु
		अगर (add_match_busid(busid) < 0)
			वापस -ENOMEM;

		pr_debug("add busid %s\n", busid);
		वापस count;
	पूर्ण

	अगर (!म_भेदन(buf, "del ", 4)) अणु
		अगर (del_match_busid(busid) < 0)
			वापस -ENODEV;

		pr_debug("del busid %s\n", busid);
		वापस count;
	पूर्ण

	वापस -EINVAL;
पूर्ण
अटल DRIVER_ATTR_RW(match_busid);

अटल पूर्णांक करो_rebind(अक्षर *busid, काष्ठा bus_id_priv *busid_priv)
अणु
	पूर्णांक ret = 0;

	/* device_attach() callers should hold parent lock क्रम USB */
	अगर (busid_priv->udev->dev.parent)
		device_lock(busid_priv->udev->dev.parent);
	ret = device_attach(&busid_priv->udev->dev);
	अगर (busid_priv->udev->dev.parent)
		device_unlock(busid_priv->udev->dev.parent);
	अगर (ret < 0)
		dev_err(&busid_priv->udev->dev, "rebind failed\n");
	वापस ret;
पूर्ण

अटल व्योम stub_device_rebind(व्योम)
अणु
#अगर IS_MODULE(CONFIG_USBIP_HOST)
	काष्ठा bus_id_priv *busid_priv;
	पूर्णांक i;

	/* update status to STUB_BUSID_OTHER so probe ignores the device */
	spin_lock(&busid_table_lock);
	क्रम (i = 0; i < MAX_BUSID; i++) अणु
		अगर (busid_table[i].name[0] &&
		    busid_table[i].shutकरोwn_busid) अणु
			busid_priv = &(busid_table[i]);
			busid_priv->status = STUB_BUSID_OTHER;
		पूर्ण
	पूर्ण
	spin_unlock(&busid_table_lock);

	/* now run rebind - no need to hold locks. driver files are हटाओd */
	क्रम (i = 0; i < MAX_BUSID; i++) अणु
		अगर (busid_table[i].name[0] &&
		    busid_table[i].shutकरोwn_busid) अणु
			busid_priv = &(busid_table[i]);
			करो_rebind(busid_table[i].name, busid_priv);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल sमाप_प्रकार rebind_store(काष्ठा device_driver *dev, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक len;
	काष्ठा bus_id_priv *bid;

	/* buf length should be less that BUSID_SIZE */
	len = strnlen(buf, BUSID_SIZE);

	अगर (!(len < BUSID_SIZE))
		वापस -EINVAL;

	bid = get_busid_priv(buf);
	अगर (!bid)
		वापस -ENODEV;

	/* mark the device क्रम deletion so probe ignores it during rescan */
	bid->status = STUB_BUSID_OTHER;
	/* release the busid lock */
	put_busid_priv(bid);

	ret = करो_rebind((अक्षर *) buf, bid);
	अगर (ret < 0)
		वापस ret;

	/* delete device from busid_table */
	del_match_busid((अक्षर *) buf);

	वापस count;
पूर्ण

अटल DRIVER_ATTR_WO(rebind);

अटल काष्ठा stub_priv *stub_priv_pop_from_listhead(काष्ठा list_head *listhead)
अणु
	काष्ठा stub_priv *priv, *पंचांगp;

	list_क्रम_each_entry_safe(priv, पंचांगp, listhead, list) अणु
		list_del_init(&priv->list);
		वापस priv;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम stub_मुक्त_priv_and_urb(काष्ठा stub_priv *priv)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_urbs; i++) अणु
		urb = priv->urbs[i];

		अगर (!urb)
			वापस;

		kमुक्त(urb->setup_packet);
		urb->setup_packet = शून्य;


		अगर (urb->transfer_buffer && !priv->sgl) अणु
			kमुक्त(urb->transfer_buffer);
			urb->transfer_buffer = शून्य;
		पूर्ण

		अगर (urb->num_sgs) अणु
			sgl_मुक्त(urb->sg);
			urb->sg = शून्य;
			urb->num_sgs = 0;
		पूर्ण

		usb_मुक्त_urb(urb);
	पूर्ण
	अगर (!list_empty(&priv->list))
		list_del(&priv->list);
	अगर (priv->sgl)
		sgl_मुक्त(priv->sgl);
	kमुक्त(priv->urbs);
	kmem_cache_मुक्त(stub_priv_cache, priv);
पूर्ण

अटल काष्ठा stub_priv *stub_priv_pop(काष्ठा stub_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stub_priv *priv;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	priv = stub_priv_pop_from_listhead(&sdev->priv_init);
	अगर (priv)
		जाओ करोne;

	priv = stub_priv_pop_from_listhead(&sdev->priv_tx);
	अगर (priv)
		जाओ करोne;

	priv = stub_priv_pop_from_listhead(&sdev->priv_मुक्त);

करोne:
	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस priv;
पूर्ण

व्योम stub_device_cleanup_urbs(काष्ठा stub_device *sdev)
अणु
	काष्ठा stub_priv *priv;
	पूर्णांक i;

	dev_dbg(&sdev->udev->dev, "Stub device cleaning up urbs\n");

	जबतक ((priv = stub_priv_pop(sdev))) अणु
		क्रम (i = 0; i < priv->num_urbs; i++)
			usb_समाप्त_urb(priv->urbs[i]);

		stub_मुक्त_priv_and_urb(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक __init usbip_host_init(व्योम)
अणु
	पूर्णांक ret;

	init_busid_table();

	stub_priv_cache = KMEM_CACHE(stub_priv, SLAB_HWCACHE_ALIGN);
	अगर (!stub_priv_cache) अणु
		pr_err("kmem_cache_create failed\n");
		वापस -ENOMEM;
	पूर्ण

	ret = usb_रेजिस्टर_device_driver(&stub_driver, THIS_MODULE);
	अगर (ret) अणु
		pr_err("usb_register failed %d\n", ret);
		जाओ err_usb_रेजिस्टर;
	पूर्ण

	ret = driver_create_file(&stub_driver.drvwrap.driver,
				 &driver_attr_match_busid);
	अगर (ret) अणु
		pr_err("driver_create_file failed\n");
		जाओ err_create_file;
	पूर्ण

	ret = driver_create_file(&stub_driver.drvwrap.driver,
				 &driver_attr_rebind);
	अगर (ret) अणु
		pr_err("driver_create_file failed\n");
		जाओ err_create_file;
	पूर्ण

	वापस ret;

err_create_file:
	usb_deरेजिस्टर_device_driver(&stub_driver);
err_usb_रेजिस्टर:
	kmem_cache_destroy(stub_priv_cache);
	वापस ret;
पूर्ण

अटल व्योम __निकास usbip_host_निकास(व्योम)
अणु
	driver_हटाओ_file(&stub_driver.drvwrap.driver,
			   &driver_attr_match_busid);

	driver_हटाओ_file(&stub_driver.drvwrap.driver,
			   &driver_attr_rebind);

	/*
	 * deरेजिस्टर() calls stub_disconnect() क्रम all devices. Device
	 * specअगरic data is cleared in stub_disconnect().
	 */
	usb_deरेजिस्टर_device_driver(&stub_driver);

	/* initiate scan to attach devices */
	stub_device_rebind();

	kmem_cache_destroy(stub_priv_cache);
पूर्ण

module_init(usbip_host_init);
module_निकास(usbip_host_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
