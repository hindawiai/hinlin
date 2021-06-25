<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * chaoskey - driver क्रम ChaosKey device from Altus Metrum.
 *
 * This device provides true अक्रमom numbers using a noise source based
 * on a reverse-biased p-n junction in avalanche अवरोधकरोwn. More
 * details can be found at http://chaoskey.org
 *
 * The driver connects to the kernel hardware RNG पूर्णांकerface to provide
 * entropy क्रम /dev/अक्रमom and other kernel activities. It also offers
 * a separate /dev/ entry to allow क्रम direct access to the अक्रमom
 * bit stream.
 *
 * Copyright तऊ 2015 Keith Packard <keithp@keithp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

अटल काष्ठा usb_driver chaoskey_driver;
अटल काष्ठा usb_class_driver chaoskey_class;
अटल पूर्णांक chaoskey_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data,
			     माप_प्रकार max, bool रुको);

#घोषणा usb_dbg(usb_अगर, क्रमmat, arg...) \
	dev_dbg(&(usb_अगर)->dev, क्रमmat, ## arg)

#घोषणा usb_err(usb_अगर, क्रमmat, arg...) \
	dev_err(&(usb_अगर)->dev, क्रमmat, ## arg)

/* Version Inक्रमmation */
#घोषणा DRIVER_AUTHOR	"Keith Packard, keithp@keithp.com"
#घोषणा DRIVER_DESC	"Altus Metrum ChaosKey driver"
#घोषणा DRIVER_SHORT	"chaoskey"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा CHAOSKEY_VENDOR_ID	0x1d50	/* OpenMoko */
#घोषणा CHAOSKEY_PRODUCT_ID	0x60c6	/* ChaosKey */

#घोषणा ALEA_VENDOR_ID		0x12d8	/* Araneus */
#घोषणा ALEA_PRODUCT_ID		0x0001	/* Alea I */

#घोषणा CHAOSKEY_BUF_LEN	64	/* max size of USB full speed packet */

#घोषणा NAK_TIMEOUT (HZ)		/* normal stall/रुको समयout */
#घोषणा ALEA_FIRST_TIMEOUT (HZ*3)	/* first stall/रुको समयout क्रम Alea */

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा USB_CHAOSKEY_MINOR_BASE 0
#अन्यथा

/* IOWARRIOR_MINOR_BASE + 16, not official yet */
#घोषणा USB_CHAOSKEY_MINOR_BASE 224
#पूर्ण_अगर

अटल स्थिर काष्ठा usb_device_id chaoskey_table[] = अणु
	अणु USB_DEVICE(CHAOSKEY_VENDOR_ID, CHAOSKEY_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ALEA_VENDOR_ID, ALEA_PRODUCT_ID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, chaoskey_table);

अटल व्योम chaos_पढ़ो_callback(काष्ठा urb *urb);

/* Driver-local specअगरic stuff */
काष्ठा chaoskey अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	अक्षर in_ep;
	काष्ठा mutex lock;
	काष्ठा mutex rng_lock;
	पूर्णांक खोलो;			/* खोलो count */
	bool present;			/* device not disconnected */
	bool पढ़ोing;			/* ongoing IO */
	bool पढ़ोs_started;		/* track first पढ़ो क्रम Alea */
	पूर्णांक size;			/* size of buf */
	पूर्णांक valid;			/* bytes of buf पढ़ो */
	पूर्णांक used;			/* bytes of buf consumed */
	अक्षर *name;			/* product + serial */
	काष्ठा hwrng hwrng;		/* Embedded काष्ठा क्रम hwrng */
	पूर्णांक hwrng_रेजिस्टरed;		/* रेजिस्टरed with hwrng API */
	रुको_queue_head_t रुको_q;	/* क्रम समयouts */
	काष्ठा urb *urb;		/* क्रम perक्रमming IO */
	अक्षर *buf;
पूर्ण;

अटल व्योम chaoskey_मुक्त(काष्ठा chaoskey *dev)
अणु
	अगर (dev) अणु
		usb_dbg(dev->पूर्णांकerface, "free");
		usb_मुक्त_urb(dev->urb);
		kमुक्त(dev->name);
		kमुक्त(dev->buf);
		usb_put_पूर्णांकf(dev->पूर्णांकerface);
		kमुक्त(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक chaoskey_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *altsetting = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक in_ep;
	काष्ठा chaoskey *dev;
	पूर्णांक result = -ENOMEM;
	पूर्णांक size;
	पूर्णांक res;

	usb_dbg(पूर्णांकerface, "probe %s-%s", udev->product, udev->serial);

	/* Find the first bulk IN endpoपूर्णांक and its packet size */
	res = usb_find_bulk_in_endpoपूर्णांक(altsetting, &epd);
	अगर (res) अणु
		usb_dbg(पूर्णांकerface, "no IN endpoint found");
		वापस res;
	पूर्ण

	in_ep = usb_endpoपूर्णांक_num(epd);
	size = usb_endpoपूर्णांक_maxp(epd);

	/* Validate endpoपूर्णांक and size */
	अगर (size <= 0) अणु
		usb_dbg(पूर्णांकerface, "invalid size (%d)", size);
		वापस -ENODEV;
	पूर्ण

	अगर (size > CHAOSKEY_BUF_LEN) अणु
		usb_dbg(पूर्णांकerface, "size reduced from %d to %d\n",
			size, CHAOSKEY_BUF_LEN);
		size = CHAOSKEY_BUF_LEN;
	पूर्ण

	/* Looks good, allocate and initialize */

	dev = kzalloc(माप(काष्ठा chaoskey), GFP_KERNEL);

	अगर (dev == शून्य)
		जाओ out;

	dev->पूर्णांकerface = usb_get_पूर्णांकf(पूर्णांकerface);

	dev->buf = kदो_स्मृति(size, GFP_KERNEL);

	अगर (dev->buf == शून्य)
		जाओ out;

	dev->urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!dev->urb)
		जाओ out;

	usb_fill_bulk_urb(dev->urb,
		udev,
		usb_rcvbulkpipe(udev, in_ep),
		dev->buf,
		size,
		chaos_पढ़ो_callback,
		dev);

	/* Conकाष्ठा a name using the product and serial values. Each
	 * device needs a unique name क्रम the hwrng code
	 */

	अगर (udev->product && udev->serial) अणु
		dev->name = kaप्र_लिखो(GFP_KERNEL, "%s-%s", udev->product,
				      udev->serial);
		अगर (dev->name == शून्य)
			जाओ out;
	पूर्ण

	dev->in_ep = in_ep;

	अगर (le16_to_cpu(udev->descriptor.idVenकरोr) != ALEA_VENDOR_ID)
		dev->पढ़ोs_started = true;

	dev->size = size;
	dev->present = true;

	init_रुकोqueue_head(&dev->रुको_q);

	mutex_init(&dev->lock);
	mutex_init(&dev->rng_lock);

	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	result = usb_रेजिस्टर_dev(पूर्णांकerface, &chaoskey_class);
	अगर (result) अणु
		usb_err(पूर्णांकerface, "Unable to allocate minor number.");
		जाओ out;
	पूर्ण

	dev->hwrng.name = dev->name ? dev->name : chaoskey_driver.name;
	dev->hwrng.पढ़ो = chaoskey_rng_पढ़ो;
	dev->hwrng.quality = 1024;

	dev->hwrng_रेजिस्टरed = (hwrng_रेजिस्टर(&dev->hwrng) == 0);
	अगर (!dev->hwrng_रेजिस्टरed)
		usb_err(पूर्णांकerface, "Unable to register with hwrng");

	usb_enable_स्वतःsuspend(udev);

	usb_dbg(पूर्णांकerface, "chaoskey probe success, size %d", dev->size);
	वापस 0;

out:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	chaoskey_मुक्त(dev);
	वापस result;
पूर्ण

अटल व्योम chaoskey_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा chaoskey	*dev;

	usb_dbg(पूर्णांकerface, "disconnect");
	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		usb_dbg(पूर्णांकerface, "disconnect failed - no dev");
		वापस;
	पूर्ण

	अगर (dev->hwrng_रेजिस्टरed)
		hwrng_unरेजिस्टर(&dev->hwrng);

	usb_deरेजिस्टर_dev(पूर्णांकerface, &chaoskey_class);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	mutex_lock(&dev->lock);

	dev->present = false;
	usb_poison_urb(dev->urb);

	अगर (!dev->खोलो) अणु
		mutex_unlock(&dev->lock);
		chaoskey_मुक्त(dev);
	पूर्ण अन्यथा
		mutex_unlock(&dev->lock);

	usb_dbg(पूर्णांकerface, "disconnect done");
पूर्ण

अटल पूर्णांक chaoskey_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा chaoskey *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	/* get the पूर्णांकerface from minor number and driver inक्रमmation */
	पूर्णांकerface = usb_find_पूर्णांकerface(&chaoskey_driver, iminor(inode));
	अगर (!पूर्णांकerface)
		वापस -ENODEV;

	usb_dbg(पूर्णांकerface, "open");

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		usb_dbg(पूर्णांकerface, "open (dev)");
		वापस -ENODEV;
	पूर्ण

	file->निजी_data = dev;
	mutex_lock(&dev->lock);
	++dev->खोलो;
	mutex_unlock(&dev->lock);

	usb_dbg(पूर्णांकerface, "open success");
	वापस 0;
पूर्ण

अटल पूर्णांक chaoskey_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा chaoskey *dev = file->निजी_data;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	अगर (dev == शून्य)
		वापस -ENODEV;

	पूर्णांकerface = dev->पूर्णांकerface;

	usb_dbg(पूर्णांकerface, "release");

	mutex_lock(&dev->lock);

	usb_dbg(पूर्णांकerface, "open count at release is %d", dev->खोलो);

	अगर (dev->खोलो <= 0) अणु
		usb_dbg(पूर्णांकerface, "invalid open count (%d)", dev->खोलो);
		mutex_unlock(&dev->lock);
		वापस -ENODEV;
	पूर्ण

	--dev->खोलो;

	अगर (!dev->present) अणु
		अगर (dev->खोलो == 0) अणु
			mutex_unlock(&dev->lock);
			chaoskey_मुक्त(dev);
		पूर्ण अन्यथा
			mutex_unlock(&dev->lock);
	पूर्ण अन्यथा
		mutex_unlock(&dev->lock);

	usb_dbg(पूर्णांकerface, "release success");
	वापस 0;
पूर्ण

अटल व्योम chaos_पढ़ो_callback(काष्ठा urb *urb)
अणु
	काष्ठा chaoskey *dev = urb->context;
	पूर्णांक status = urb->status;

	usb_dbg(dev->पूर्णांकerface, "callback status (%d)", status);

	अगर (status == 0)
		dev->valid = urb->actual_length;
	अन्यथा
		dev->valid = 0;

	dev->used = 0;

	/* must be seen first beक्रमe validity is announced */
	smp_wmb();

	dev->पढ़ोing = false;
	wake_up(&dev->रुको_q);
पूर्ण

/* Fill the buffer. Called with dev->lock held
 */
अटल पूर्णांक _chaoskey_fill(काष्ठा chaoskey *dev)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक result;
	bool started;

	usb_dbg(dev->पूर्णांकerface, "fill");

	/* Return immediately अगर someone called beक्रमe the buffer was
	 * empty */
	अगर (dev->valid != dev->used) अणु
		usb_dbg(dev->पूर्णांकerface, "not empty yet (valid %d used %d)",
			dev->valid, dev->used);
		वापस 0;
	पूर्ण

	/* Bail अगर the device has been हटाओd */
	अगर (!dev->present) अणु
		usb_dbg(dev->पूर्णांकerface, "device not present");
		वापस -ENODEV;
	पूर्ण

	/* Make sure the device is awake */
	result = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकerface);
	अगर (result) अणु
		usb_dbg(dev->पूर्णांकerface, "wakeup failed (result %d)", result);
		वापस result;
	पूर्ण

	dev->पढ़ोing = true;
	result = usb_submit_urb(dev->urb, GFP_KERNEL);
	अगर (result < 0) अणु
		result = usb_translate_errors(result);
		dev->पढ़ोing = false;
		जाओ out;
	पूर्ण

	/* The first पढ़ो on the Alea takes a little under 2 seconds.
	 * Reads after the first पढ़ो take only a few microseconds
	 * though.  Presumably the entropy-generating circuit needs
	 * समय to ramp up.  So, we रुको दीर्घer on the first पढ़ो.
	 */
	started = dev->पढ़ोs_started;
	dev->पढ़ोs_started = true;
	result = रुको_event_पूर्णांकerruptible_समयout(
		dev->रुको_q,
		!dev->पढ़ोing,
		(started ? NAK_TIMEOUT : ALEA_FIRST_TIMEOUT) );

	अगर (result < 0) अणु
		usb_समाप्त_urb(dev->urb);
		जाओ out;
	पूर्ण

	अगर (result == 0) अणु
		result = -ETIMEDOUT;
		usb_समाप्त_urb(dev->urb);
	पूर्ण अन्यथा अणु
		result = dev->valid;
	पूर्ण
out:
	/* Let the device go back to sleep eventually */
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकerface);

	usb_dbg(dev->पूर्णांकerface, "read %d bytes", dev->valid);

	वापस result;
पूर्ण

अटल sमाप_प्रकार chaoskey_पढ़ो(काष्ठा file *file,
			     अक्षर __user *buffer,
			     माप_प्रकार count,
			     loff_t *ppos)
अणु
	काष्ठा chaoskey *dev;
	sमाप_प्रकार पढ़ो_count = 0;
	पूर्णांक this_समय;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ reमुख्य;

	dev = file->निजी_data;

	अगर (dev == शून्य || !dev->present)
		वापस -ENODEV;

	usb_dbg(dev->पूर्णांकerface, "read %zu", count);

	जबतक (count > 0) अणु

		/* Grab the rng_lock briefly to ensure that the hwrng पूर्णांकerface
		 * माला_लो priority over other user access
		 */
		result = mutex_lock_पूर्णांकerruptible(&dev->rng_lock);
		अगर (result)
			जाओ bail;
		mutex_unlock(&dev->rng_lock);

		result = mutex_lock_पूर्णांकerruptible(&dev->lock);
		अगर (result)
			जाओ bail;
		अगर (dev->valid == dev->used) अणु
			result = _chaoskey_fill(dev);
			अगर (result < 0) अणु
				mutex_unlock(&dev->lock);
				जाओ bail;
			पूर्ण
		पूर्ण

		this_समय = dev->valid - dev->used;
		अगर (this_समय > count)
			this_समय = count;

		reमुख्य = copy_to_user(buffer, dev->buf + dev->used, this_समय);
		अगर (reमुख्य) अणु
			result = -EFAULT;

			/* Consume the bytes that were copied so we करोn't leak
			 * data to user space
			 */
			dev->used += this_समय - reमुख्य;
			mutex_unlock(&dev->lock);
			जाओ bail;
		पूर्ण

		count -= this_समय;
		पढ़ो_count += this_समय;
		buffer += this_समय;
		dev->used += this_समय;
		mutex_unlock(&dev->lock);
	पूर्ण
bail:
	अगर (पढ़ो_count) अणु
		usb_dbg(dev->पूर्णांकerface, "read %zu bytes", पढ़ो_count);
		वापस पढ़ो_count;
	पूर्ण
	usb_dbg(dev->पूर्णांकerface, "empty read, result %d", result);
	अगर (result == -ETIMEDOUT)
		result = -EAGAIN;
	वापस result;
पूर्ण

अटल पूर्णांक chaoskey_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data,
			     माप_प्रकार max, bool रुको)
अणु
	काष्ठा chaoskey *dev = container_of(rng, काष्ठा chaoskey, hwrng);
	पूर्णांक this_समय;

	usb_dbg(dev->पूर्णांकerface, "rng_read max %zu wait %d", max, रुको);

	अगर (!dev->present) अणु
		usb_dbg(dev->पूर्णांकerface, "device not present");
		वापस 0;
	पूर्ण

	/* Hold the rng_lock until we acquire the device lock so that
	 * this operation माला_लो priority over other user access to the
	 * device
	 */
	mutex_lock(&dev->rng_lock);

	mutex_lock(&dev->lock);

	mutex_unlock(&dev->rng_lock);

	/* Try to fill the buffer अगर empty. It करोesn't actually matter
	 * अगर _chaoskey_fill works; we'll just वापस zero bytes as
	 * the buffer will still be empty
	 */
	अगर (dev->valid == dev->used)
		(व्योम) _chaoskey_fill(dev);

	this_समय = dev->valid - dev->used;
	अगर (this_समय > max)
		this_समय = max;

	स_नकल(data, dev->buf + dev->used, this_समय);

	dev->used += this_समय;

	mutex_unlock(&dev->lock);

	usb_dbg(dev->पूर्णांकerface, "rng_read this_time %d\n", this_समय);
	वापस this_समय;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक chaoskey_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    pm_message_t message)
अणु
	usb_dbg(पूर्णांकerface, "suspend");
	वापस 0;
पूर्ण

अटल पूर्णांक chaoskey_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा chaoskey *dev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	usb_dbg(पूर्णांकerface, "resume");
	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	/*
	 * We may have lost घातer.
	 * In that हाल the device that needs a दीर्घ समय
	 * क्रम the first requests needs an extended समयout
	 * again
	 */
	अगर (le16_to_cpu(udev->descriptor.idVenकरोr) == ALEA_VENDOR_ID)
		dev->पढ़ोs_started = false;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा chaoskey_suspend शून्य
#घोषणा chaoskey_resume शून्य
#पूर्ण_अगर

/* file operation poपूर्णांकers */
अटल स्थिर काष्ठा file_operations chaoskey_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = chaoskey_पढ़ो,
	.खोलो = chaoskey_खोलो,
	.release = chaoskey_release,
	.llseek = शेष_llseek,
पूर्ण;

/* class driver inक्रमmation */
अटल काष्ठा usb_class_driver chaoskey_class = अणु
	.name = "chaoskey%d",
	.fops = &chaoskey_fops,
	.minor_base = USB_CHAOSKEY_MINOR_BASE,
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver chaoskey_driver = अणु
	.name = DRIVER_SHORT,
	.probe = chaoskey_probe,
	.disconnect = chaoskey_disconnect,
	.suspend = chaoskey_suspend,
	.resume = chaoskey_resume,
	.reset_resume = chaoskey_resume,
	.id_table = chaoskey_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(chaoskey_driver);

