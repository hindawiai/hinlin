<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple synchronous userspace पूर्णांकerface to SPI devices
 *
 * Copyright (C) 2006 SWAPP
 *	Andrea Paterniani <a.paterniani@swapp-eng.it>
 * Copyright (C) 2007 David Brownell (simplअगरication, cleanup)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/acpi.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spidev.h>

#समावेश <linux/uaccess.h>


/*
 * This supports access to SPI devices using normal userspace I/O calls.
 * Note that जबतक traditional UNIX/POSIX I/O semantics are half duplex,
 * and often mask message boundaries, full SPI support requires full duplex
 * transfers.  There are several kinds of पूर्णांकernal message boundaries to
 * handle chipselect management and other protocol options.
 *
 * SPI has a अक्षरacter major number asचिन्हित.  We allocate minor numbers
 * dynamically using a biपंचांगask.  You must use hotplug tools, such as udev
 * (or mdev with busybox) to create and destroy the /dev/spidevB.C device
 * nodes, since there is no fixed association of minor numbers with any
 * particular SPI bus or device.
 */
#घोषणा SPIDEV_MAJOR			153	/* asचिन्हित */
#घोषणा N_SPI_MINORS			32	/* ... up to 256 */

अटल DECLARE_BITMAP(minors, N_SPI_MINORS);


/* Bit masks क्रम spi_device.mode management.  Note that incorrect
 * settings क्रम some settings can cause *lots* of trouble क्रम other
 * devices on a shared bus:
 *
 *  - CS_HIGH ... this device will be active when it shouldn't be
 *  - 3WIRE ... when active, it won't behave as it should
 *  - NO_CS ... there will be no explicit message boundaries; this
 *	is completely incompatible with the shared bus model
 *  - READY ... transfers may proceed when they shouldn't.
 *
 * REVISIT should changing those flags be privileged?
 */
#घोषणा SPI_MODE_MASK		(SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
				| SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
				| SPI_NO_CS | SPI_READY | SPI_TX_DUAL \
				| SPI_TX_QUAD | SPI_TX_OCTAL | SPI_RX_DUAL \
				| SPI_RX_QUAD | SPI_RX_OCTAL)

काष्ठा spidev_data अणु
	dev_t			devt;
	spinlock_t		spi_lock;
	काष्ठा spi_device	*spi;
	काष्ठा list_head	device_entry;

	/* TX/RX buffers are शून्य unless this device is खोलो (users > 0) */
	काष्ठा mutex		buf_lock;
	अचिन्हित		users;
	u8			*tx_buffer;
	u8			*rx_buffer;
	u32			speed_hz;
पूर्ण;

अटल LIST_HEAD(device_list);
अटल DEFINE_MUTEX(device_list_lock);

अटल अचिन्हित bufsiz = 4096;
module_param(bufsiz, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(bufsiz, "data bytes in biggest supported SPI message");

/*-------------------------------------------------------------------------*/

अटल sमाप_प्रकार
spidev_sync(काष्ठा spidev_data *spidev, काष्ठा spi_message *message)
अणु
	पूर्णांक status;
	काष्ठा spi_device *spi;

	spin_lock_irq(&spidev->spi_lock);
	spi = spidev->spi;
	spin_unlock_irq(&spidev->spi_lock);

	अगर (spi == शून्य)
		status = -ESHUTDOWN;
	अन्यथा
		status = spi_sync(spi, message);

	अगर (status == 0)
		status = message->actual_length;

	वापस status;
पूर्ण

अटल अंतरभूत sमाप_प्रकार
spidev_sync_ग_लिखो(काष्ठा spidev_data *spidev, माप_प्रकार len)
अणु
	काष्ठा spi_transfer	t = अणु
			.tx_buf		= spidev->tx_buffer,
			.len		= len,
			.speed_hz	= spidev->speed_hz,
		पूर्ण;
	काष्ठा spi_message	m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	वापस spidev_sync(spidev, &m);
पूर्ण

अटल अंतरभूत sमाप_प्रकार
spidev_sync_पढ़ो(काष्ठा spidev_data *spidev, माप_प्रकार len)
अणु
	काष्ठा spi_transfer	t = अणु
			.rx_buf		= spidev->rx_buffer,
			.len		= len,
			.speed_hz	= spidev->speed_hz,
		पूर्ण;
	काष्ठा spi_message	m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	वापस spidev_sync(spidev, &m);
पूर्ण

/*-------------------------------------------------------------------------*/

/* Read-only message with current device setup */
अटल sमाप_प्रकार
spidev_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा spidev_data	*spidev;
	sमाप_प्रकार			status;

	/* chipselect only toggles at start or end of operation */
	अगर (count > bufsiz)
		वापस -EMSGSIZE;

	spidev = filp->निजी_data;

	mutex_lock(&spidev->buf_lock);
	status = spidev_sync_पढ़ो(spidev, count);
	अगर (status > 0) अणु
		अचिन्हित दीर्घ	missing;

		missing = copy_to_user(buf, spidev->rx_buffer, status);
		अगर (missing == status)
			status = -EFAULT;
		अन्यथा
			status = status - missing;
	पूर्ण
	mutex_unlock(&spidev->buf_lock);

	वापस status;
पूर्ण

/* Write-only message with current device setup */
अटल sमाप_प्रकार
spidev_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा spidev_data	*spidev;
	sमाप_प्रकार			status;
	अचिन्हित दीर्घ		missing;

	/* chipselect only toggles at start or end of operation */
	अगर (count > bufsiz)
		वापस -EMSGSIZE;

	spidev = filp->निजी_data;

	mutex_lock(&spidev->buf_lock);
	missing = copy_from_user(spidev->tx_buffer, buf, count);
	अगर (missing == 0)
		status = spidev_sync_ग_लिखो(spidev, count);
	अन्यथा
		status = -EFAULT;
	mutex_unlock(&spidev->buf_lock);

	वापस status;
पूर्ण

अटल पूर्णांक spidev_message(काष्ठा spidev_data *spidev,
		काष्ठा spi_ioc_transfer *u_xfers, अचिन्हित n_xfers)
अणु
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	*k_xfers;
	काष्ठा spi_transfer	*k_पंचांगp;
	काष्ठा spi_ioc_transfer *u_पंचांगp;
	अचिन्हित		n, total, tx_total, rx_total;
	u8			*tx_buf, *rx_buf;
	पूर्णांक			status = -EFAULT;

	spi_message_init(&msg);
	k_xfers = kसुस्मृति(n_xfers, माप(*k_पंचांगp), GFP_KERNEL);
	अगर (k_xfers == शून्य)
		वापस -ENOMEM;

	/* Conकाष्ठा spi_message, copying any tx data to bounce buffer.
	 * We walk the array of user-provided transfers, using each one
	 * to initialize a kernel version of the same transfer.
	 */
	tx_buf = spidev->tx_buffer;
	rx_buf = spidev->rx_buffer;
	total = 0;
	tx_total = 0;
	rx_total = 0;
	क्रम (n = n_xfers, k_पंचांगp = k_xfers, u_पंचांगp = u_xfers;
			n;
			n--, k_पंचांगp++, u_पंचांगp++) अणु
		/* Ensure that also following allocations from rx_buf/tx_buf will meet
		 * DMA alignment requirements.
		 */
		अचिन्हित पूर्णांक len_aligned = ALIGN(u_पंचांगp->len, ARCH_KMALLOC_MINALIGN);

		k_पंचांगp->len = u_पंचांगp->len;

		total += k_पंचांगp->len;
		/* Since the function वापसs the total length of transfers
		 * on success, restrict the total to positive पूर्णांक values to
		 * aव्योम the वापस value looking like an error.  Also check
		 * each transfer length to aव्योम arithmetic overflow.
		 */
		अगर (total > पूर्णांक_उच्च || k_पंचांगp->len > पूर्णांक_उच्च) अणु
			status = -EMSGSIZE;
			जाओ करोne;
		पूर्ण

		अगर (u_पंचांगp->rx_buf) अणु
			/* this transfer needs space in RX bounce buffer */
			rx_total += len_aligned;
			अगर (rx_total > bufsiz) अणु
				status = -EMSGSIZE;
				जाओ करोne;
			पूर्ण
			k_पंचांगp->rx_buf = rx_buf;
			rx_buf += len_aligned;
		पूर्ण
		अगर (u_पंचांगp->tx_buf) अणु
			/* this transfer needs space in TX bounce buffer */
			tx_total += len_aligned;
			अगर (tx_total > bufsiz) अणु
				status = -EMSGSIZE;
				जाओ करोne;
			पूर्ण
			k_पंचांगp->tx_buf = tx_buf;
			अगर (copy_from_user(tx_buf, (स्थिर u8 __user *)
						(uपूर्णांकptr_t) u_पंचांगp->tx_buf,
					u_पंचांगp->len))
				जाओ करोne;
			tx_buf += len_aligned;
		पूर्ण

		k_पंचांगp->cs_change = !!u_पंचांगp->cs_change;
		k_पंचांगp->tx_nbits = u_पंचांगp->tx_nbits;
		k_पंचांगp->rx_nbits = u_पंचांगp->rx_nbits;
		k_पंचांगp->bits_per_word = u_पंचांगp->bits_per_word;
		k_पंचांगp->delay.value = u_पंचांगp->delay_usecs;
		k_पंचांगp->delay.unit = SPI_DELAY_UNIT_USECS;
		k_पंचांगp->speed_hz = u_पंचांगp->speed_hz;
		k_पंचांगp->word_delay.value = u_पंचांगp->word_delay_usecs;
		k_पंचांगp->word_delay.unit = SPI_DELAY_UNIT_USECS;
		अगर (!k_पंचांगp->speed_hz)
			k_पंचांगp->speed_hz = spidev->speed_hz;
#अगर_घोषित VERBOSE
		dev_dbg(&spidev->spi->dev,
			"  xfer len %u %s%s%s%dbits %u usec %u usec %uHz\n",
			k_पंचांगp->len,
			k_पंचांगp->rx_buf ? "rx " : "",
			k_पंचांगp->tx_buf ? "tx " : "",
			k_पंचांगp->cs_change ? "cs " : "",
			k_पंचांगp->bits_per_word ? : spidev->spi->bits_per_word,
			k_पंचांगp->delay.value,
			k_पंचांगp->word_delay.value,
			k_पंचांगp->speed_hz ? : spidev->spi->max_speed_hz);
#पूर्ण_अगर
		spi_message_add_tail(k_पंचांगp, &msg);
	पूर्ण

	status = spidev_sync(spidev, &msg);
	अगर (status < 0)
		जाओ करोne;

	/* copy any rx data out of bounce buffer */
	क्रम (n = n_xfers, k_पंचांगp = k_xfers, u_पंचांगp = u_xfers;
			n;
			n--, k_पंचांगp++, u_पंचांगp++) अणु
		अगर (u_पंचांगp->rx_buf) अणु
			अगर (copy_to_user((u8 __user *)
					(uपूर्णांकptr_t) u_पंचांगp->rx_buf, k_पंचांगp->rx_buf,
					u_पंचांगp->len)) अणु
				status = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
	status = total;

करोne:
	kमुक्त(k_xfers);
	वापस status;
पूर्ण

अटल काष्ठा spi_ioc_transfer *
spidev_get_ioc_message(अचिन्हित पूर्णांक cmd, काष्ठा spi_ioc_transfer __user *u_ioc,
		अचिन्हित *n_ioc)
अणु
	u32	पंचांगp;

	/* Check type, command number and direction */
	अगर (_IOC_TYPE(cmd) != SPI_IOC_MAGIC
			|| _IOC_NR(cmd) != _IOC_NR(SPI_IOC_MESSAGE(0))
			|| _IOC_सूची(cmd) != _IOC_WRITE)
		वापस ERR_PTR(-ENOTTY);

	पंचांगp = _IOC_SIZE(cmd);
	अगर ((पंचांगp % माप(काष्ठा spi_ioc_transfer)) != 0)
		वापस ERR_PTR(-EINVAL);
	*n_ioc = पंचांगp / माप(काष्ठा spi_ioc_transfer);
	अगर (*n_ioc == 0)
		वापस शून्य;

	/* copy पूर्णांकo scratch area */
	वापस memdup_user(u_ioc, पंचांगp);
पूर्ण

अटल दीर्घ
spidev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक			retval = 0;
	काष्ठा spidev_data	*spidev;
	काष्ठा spi_device	*spi;
	u32			पंचांगp;
	अचिन्हित		n_ioc;
	काष्ठा spi_ioc_transfer	*ioc;

	/* Check type and command number */
	अगर (_IOC_TYPE(cmd) != SPI_IOC_MAGIC)
		वापस -ENOTTY;

	/* guard against device removal beक्रमe, or जबतक,
	 * we issue this ioctl.
	 */
	spidev = filp->निजी_data;
	spin_lock_irq(&spidev->spi_lock);
	spi = spi_dev_get(spidev->spi);
	spin_unlock_irq(&spidev->spi_lock);

	अगर (spi == शून्य)
		वापस -ESHUTDOWN;

	/* use the buffer lock here क्रम triple duty:
	 *  - prevent I/O (from us) so calling spi_setup() is safe;
	 *  - prevent concurrent SPI_IOC_WR_* from morphing
	 *    data fields जबतक SPI_IOC_RD_* पढ़ोs them;
	 *  - SPI_IOC_MESSAGE needs the buffer locked "normally".
	 */
	mutex_lock(&spidev->buf_lock);

	चयन (cmd) अणु
	/* पढ़ो requests */
	हाल SPI_IOC_RD_MODE:
		retval = put_user(spi->mode & SPI_MODE_MASK,
					(__u8 __user *)arg);
		अवरोध;
	हाल SPI_IOC_RD_MODE32:
		retval = put_user(spi->mode & SPI_MODE_MASK,
					(__u32 __user *)arg);
		अवरोध;
	हाल SPI_IOC_RD_LSB_FIRST:
		retval = put_user((spi->mode & SPI_LSB_FIRST) ?  1 : 0,
					(__u8 __user *)arg);
		अवरोध;
	हाल SPI_IOC_RD_BITS_PER_WORD:
		retval = put_user(spi->bits_per_word, (__u8 __user *)arg);
		अवरोध;
	हाल SPI_IOC_RD_MAX_SPEED_HZ:
		retval = put_user(spidev->speed_hz, (__u32 __user *)arg);
		अवरोध;

	/* ग_लिखो requests */
	हाल SPI_IOC_WR_MODE:
	हाल SPI_IOC_WR_MODE32:
		अगर (cmd == SPI_IOC_WR_MODE)
			retval = get_user(पंचांगp, (u8 __user *)arg);
		अन्यथा
			retval = get_user(पंचांगp, (u32 __user *)arg);
		अगर (retval == 0) अणु
			काष्ठा spi_controller *ctlr = spi->controller;
			u32	save = spi->mode;

			अगर (पंचांगp & ~SPI_MODE_MASK) अणु
				retval = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (ctlr->use_gpio_descriptors && ctlr->cs_gpiods &&
			    ctlr->cs_gpiods[spi->chip_select])
				पंचांगp |= SPI_CS_HIGH;

			पंचांगp |= spi->mode & ~SPI_MODE_MASK;
			spi->mode = (u16)पंचांगp;
			retval = spi_setup(spi);
			अगर (retval < 0)
				spi->mode = save;
			अन्यथा
				dev_dbg(&spi->dev, "spi mode %x\n", पंचांगp);
		पूर्ण
		अवरोध;
	हाल SPI_IOC_WR_LSB_FIRST:
		retval = get_user(पंचांगp, (__u8 __user *)arg);
		अगर (retval == 0) अणु
			u32	save = spi->mode;

			अगर (पंचांगp)
				spi->mode |= SPI_LSB_FIRST;
			अन्यथा
				spi->mode &= ~SPI_LSB_FIRST;
			retval = spi_setup(spi);
			अगर (retval < 0)
				spi->mode = save;
			अन्यथा
				dev_dbg(&spi->dev, "%csb first\n",
						पंचांगp ? 'l' : 'm');
		पूर्ण
		अवरोध;
	हाल SPI_IOC_WR_BITS_PER_WORD:
		retval = get_user(पंचांगp, (__u8 __user *)arg);
		अगर (retval == 0) अणु
			u8	save = spi->bits_per_word;

			spi->bits_per_word = पंचांगp;
			retval = spi_setup(spi);
			अगर (retval < 0)
				spi->bits_per_word = save;
			अन्यथा
				dev_dbg(&spi->dev, "%d bits per word\n", पंचांगp);
		पूर्ण
		अवरोध;
	हाल SPI_IOC_WR_MAX_SPEED_HZ:
		retval = get_user(पंचांगp, (__u32 __user *)arg);
		अगर (retval == 0) अणु
			u32	save = spi->max_speed_hz;

			spi->max_speed_hz = पंचांगp;
			retval = spi_setup(spi);
			अगर (retval == 0) अणु
				spidev->speed_hz = पंचांगp;
				dev_dbg(&spi->dev, "%d Hz (max)\n",
					spidev->speed_hz);
			पूर्ण
			spi->max_speed_hz = save;
		पूर्ण
		अवरोध;

	शेष:
		/* segmented and/or full-duplex I/O request */
		/* Check message and copy पूर्णांकo scratch area */
		ioc = spidev_get_ioc_message(cmd,
				(काष्ठा spi_ioc_transfer __user *)arg, &n_ioc);
		अगर (IS_ERR(ioc)) अणु
			retval = PTR_ERR(ioc);
			अवरोध;
		पूर्ण
		अगर (!ioc)
			अवरोध;	/* n_ioc is also 0 */

		/* translate to spi_message, execute */
		retval = spidev_message(spidev, ioc, n_ioc);
		kमुक्त(ioc);
		अवरोध;
	पूर्ण

	mutex_unlock(&spidev->buf_lock);
	spi_dev_put(spi);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
spidev_compat_ioc_message(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा spi_ioc_transfer __user	*u_ioc;
	पूर्णांक				retval = 0;
	काष्ठा spidev_data		*spidev;
	काष्ठा spi_device		*spi;
	अचिन्हित			n_ioc, n;
	काष्ठा spi_ioc_transfer		*ioc;

	u_ioc = (काष्ठा spi_ioc_transfer __user *) compat_ptr(arg);

	/* guard against device removal beक्रमe, or जबतक,
	 * we issue this ioctl.
	 */
	spidev = filp->निजी_data;
	spin_lock_irq(&spidev->spi_lock);
	spi = spi_dev_get(spidev->spi);
	spin_unlock_irq(&spidev->spi_lock);

	अगर (spi == शून्य)
		वापस -ESHUTDOWN;

	/* SPI_IOC_MESSAGE needs the buffer locked "normally" */
	mutex_lock(&spidev->buf_lock);

	/* Check message and copy पूर्णांकo scratch area */
	ioc = spidev_get_ioc_message(cmd, u_ioc, &n_ioc);
	अगर (IS_ERR(ioc)) अणु
		retval = PTR_ERR(ioc);
		जाओ करोne;
	पूर्ण
	अगर (!ioc)
		जाओ करोne;	/* n_ioc is also 0 */

	/* Convert buffer poपूर्णांकers */
	क्रम (n = 0; n < n_ioc; n++) अणु
		ioc[n].rx_buf = (uपूर्णांकptr_t) compat_ptr(ioc[n].rx_buf);
		ioc[n].tx_buf = (uपूर्णांकptr_t) compat_ptr(ioc[n].tx_buf);
	पूर्ण

	/* translate to spi_message, execute */
	retval = spidev_message(spidev, ioc, n_ioc);
	kमुक्त(ioc);

करोne:
	mutex_unlock(&spidev->buf_lock);
	spi_dev_put(spi);
	वापस retval;
पूर्ण

अटल दीर्घ
spidev_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (_IOC_TYPE(cmd) == SPI_IOC_MAGIC
			&& _IOC_NR(cmd) == _IOC_NR(SPI_IOC_MESSAGE(0))
			&& _IOC_सूची(cmd) == _IOC_WRITE)
		वापस spidev_compat_ioc_message(filp, cmd, arg);

	वापस spidev_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा spidev_compat_ioctl शून्य
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक spidev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा spidev_data	*spidev;
	पूर्णांक			status = -ENXIO;

	mutex_lock(&device_list_lock);

	list_क्रम_each_entry(spidev, &device_list, device_entry) अणु
		अगर (spidev->devt == inode->i_rdev) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status) अणु
		pr_debug("spidev: nothing for minor %d\n", iminor(inode));
		जाओ err_find_dev;
	पूर्ण

	अगर (!spidev->tx_buffer) अणु
		spidev->tx_buffer = kदो_स्मृति(bufsiz, GFP_KERNEL);
		अगर (!spidev->tx_buffer) अणु
			dev_dbg(&spidev->spi->dev, "open/ENOMEM\n");
			status = -ENOMEM;
			जाओ err_find_dev;
		पूर्ण
	पूर्ण

	अगर (!spidev->rx_buffer) अणु
		spidev->rx_buffer = kदो_स्मृति(bufsiz, GFP_KERNEL);
		अगर (!spidev->rx_buffer) अणु
			dev_dbg(&spidev->spi->dev, "open/ENOMEM\n");
			status = -ENOMEM;
			जाओ err_alloc_rx_buf;
		पूर्ण
	पूर्ण

	spidev->users++;
	filp->निजी_data = spidev;
	stream_खोलो(inode, filp);

	mutex_unlock(&device_list_lock);
	वापस 0;

err_alloc_rx_buf:
	kमुक्त(spidev->tx_buffer);
	spidev->tx_buffer = शून्य;
err_find_dev:
	mutex_unlock(&device_list_lock);
	वापस status;
पूर्ण

अटल पूर्णांक spidev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा spidev_data	*spidev;
	पूर्णांक			करोमुक्त;

	mutex_lock(&device_list_lock);
	spidev = filp->निजी_data;
	filp->निजी_data = शून्य;

	spin_lock_irq(&spidev->spi_lock);
	/* ... after we unbound from the underlying device? */
	करोमुक्त = (spidev->spi == शून्य);
	spin_unlock_irq(&spidev->spi_lock);

	/* last बंद? */
	spidev->users--;
	अगर (!spidev->users) अणु

		kमुक्त(spidev->tx_buffer);
		spidev->tx_buffer = शून्य;

		kमुक्त(spidev->rx_buffer);
		spidev->rx_buffer = शून्य;

		अगर (करोमुक्त)
			kमुक्त(spidev);
		अन्यथा
			spidev->speed_hz = spidev->spi->max_speed_hz;
	पूर्ण
#अगर_घोषित CONFIG_SPI_SLAVE
	अगर (!करोमुक्त)
		spi_slave_पात(spidev->spi);
#पूर्ण_अगर
	mutex_unlock(&device_list_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spidev_fops = अणु
	.owner =	THIS_MODULE,
	/* REVISIT चयन to aio primitives, so that userspace
	 * माला_लो more complete API coverage.  It'll simplअगरy things
	 * too, except क्रम the locking.
	 */
	.ग_लिखो =	spidev_ग_लिखो,
	.पढ़ो =		spidev_पढ़ो,
	.unlocked_ioctl = spidev_ioctl,
	.compat_ioctl = spidev_compat_ioctl,
	.खोलो =		spidev_खोलो,
	.release =	spidev_release,
	.llseek =	no_llseek,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* The मुख्य reason to have this class is to make mdev/udev create the
 * /dev/spidevB.C अक्षरacter device nodes exposing our userspace API.
 * It also simplअगरies memory management.
 */

अटल काष्ठा class *spidev_class;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spidev_dt_ids[] = अणु
	अणु .compatible = "rohm,dh2228fv" पूर्ण,
	अणु .compatible = "lineartechnology,ltc2488" पूर्ण,
	अणु .compatible = "ge,achc" पूर्ण,
	अणु .compatible = "semtech,sx1301" पूर्ण,
	अणु .compatible = "lwn,bk4" पूर्ण,
	अणु .compatible = "dh,dhcom-board" पूर्ण,
	अणु .compatible = "menlo,m53cpld" पूर्ण,
	अणु .compatible = "cisco,spi-petra" पूर्ण,
	अणु .compatible = "micron,spi-authenta" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spidev_dt_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI

/* Dummy SPI devices not to be used in production प्रणालीs */
#घोषणा SPIDEV_ACPI_DUMMY	1

अटल स्थिर काष्ठा acpi_device_id spidev_acpi_ids[] = अणु
	/*
	 * The ACPI SPT000* devices are only meant क्रम development and
	 * testing. Systems used in production should have a proper ACPI
	 * description of the connected peripheral and they should also use
	 * a proper driver instead of poking directly to the SPI bus.
	 */
	अणु "SPT0001", SPIDEV_ACPI_DUMMY पूर्ण,
	अणु "SPT0002", SPIDEV_ACPI_DUMMY पूर्ण,
	अणु "SPT0003", SPIDEV_ACPI_DUMMY पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, spidev_acpi_ids);

अटल व्योम spidev_probe_acpi(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	अगर (!has_acpi_companion(&spi->dev))
		वापस;

	id = acpi_match_device(spidev_acpi_ids, &spi->dev);
	अगर (WARN_ON(!id))
		वापस;

	अगर (id->driver_data == SPIDEV_ACPI_DUMMY)
		dev_warn(&spi->dev, "do not use this driver in production systems!\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spidev_probe_acpi(काष्ठा spi_device *spi) अणुपूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल पूर्णांक spidev_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा spidev_data	*spidev;
	पूर्णांक			status;
	अचिन्हित दीर्घ		minor;

	/*
	 * spidev should never be referenced in DT without a specअगरic
	 * compatible string, it is a Linux implementation thing
	 * rather than a description of the hardware.
	 */
	WARN(spi->dev.of_node &&
	     of_device_is_compatible(spi->dev.of_node, "spidev"),
	     "%pOF: buggy DT: spidev listed directly in DT\n", spi->dev.of_node);

	spidev_probe_acpi(spi);

	/* Allocate driver data */
	spidev = kzalloc(माप(*spidev), GFP_KERNEL);
	अगर (!spidev)
		वापस -ENOMEM;

	/* Initialize the driver data */
	spidev->spi = spi;
	spin_lock_init(&spidev->spi_lock);
	mutex_init(&spidev->buf_lock);

	INIT_LIST_HEAD(&spidev->device_entry);

	/* If we can allocate a minor number, hook up this device.
	 * Reusing minors is fine so दीर्घ as udev or mdev is working.
	 */
	mutex_lock(&device_list_lock);
	minor = find_first_zero_bit(minors, N_SPI_MINORS);
	अगर (minor < N_SPI_MINORS) अणु
		काष्ठा device *dev;

		spidev->devt = MKDEV(SPIDEV_MAJOR, minor);
		dev = device_create(spidev_class, &spi->dev, spidev->devt,
				    spidev, "spidev%d.%d",
				    spi->master->bus_num, spi->chip_select);
		status = PTR_ERR_OR_ZERO(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(&spi->dev, "no minor number available!\n");
		status = -ENODEV;
	पूर्ण
	अगर (status == 0) अणु
		set_bit(minor, minors);
		list_add(&spidev->device_entry, &device_list);
	पूर्ण
	mutex_unlock(&device_list_lock);

	spidev->speed_hz = spi->max_speed_hz;

	अगर (status == 0)
		spi_set_drvdata(spi, spidev);
	अन्यथा
		kमुक्त(spidev);

	वापस status;
पूर्ण

अटल पूर्णांक spidev_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा spidev_data	*spidev = spi_get_drvdata(spi);

	/* prevent new खोलोs */
	mutex_lock(&device_list_lock);
	/* make sure ops on existing fds can पात cleanly */
	spin_lock_irq(&spidev->spi_lock);
	spidev->spi = शून्य;
	spin_unlock_irq(&spidev->spi_lock);

	list_del(&spidev->device_entry);
	device_destroy(spidev_class, spidev->devt);
	clear_bit(MINOR(spidev->devt), minors);
	अगर (spidev->users == 0)
		kमुक्त(spidev);
	mutex_unlock(&device_list_lock);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver spidev_spi_driver = अणु
	.driver = अणु
		.name =		"spidev",
		.of_match_table = of_match_ptr(spidev_dt_ids),
		.acpi_match_table = ACPI_PTR(spidev_acpi_ids),
	पूर्ण,
	.probe =	spidev_probe,
	.हटाओ =	spidev_हटाओ,

	/* NOTE:  suspend/resume methods are not necessary here.
	 * We करोn't करो anything except pass the requests to/from
	 * the underlying controller.  The refrigerator handles
	 * most issues; the controller driver handles the rest.
	 */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init spidev_init(व्योम)
अणु
	पूर्णांक status;

	/* Claim our 256 reserved device numbers.  Then रेजिस्टर a class
	 * that will key udev/mdev to add/हटाओ /dev nodes.  Last, रेजिस्टर
	 * the driver which manages those device numbers.
	 */
	BUILD_BUG_ON(N_SPI_MINORS > 256);
	status = रेजिस्टर_chrdev(SPIDEV_MAJOR, "spi", &spidev_fops);
	अगर (status < 0)
		वापस status;

	spidev_class = class_create(THIS_MODULE, "spidev");
	अगर (IS_ERR(spidev_class)) अणु
		unरेजिस्टर_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);
		वापस PTR_ERR(spidev_class);
	पूर्ण

	status = spi_रेजिस्टर_driver(&spidev_spi_driver);
	अगर (status < 0) अणु
		class_destroy(spidev_class);
		unरेजिस्टर_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);
	पूर्ण
	वापस status;
पूर्ण
module_init(spidev_init);

अटल व्योम __निकास spidev_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&spidev_spi_driver);
	class_destroy(spidev_class);
	unरेजिस्टर_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);
पूर्ण
module_निकास(spidev_निकास);

MODULE_AUTHOR("Andrea Paterniani, <a.paterniani@swapp-eng.it>");
MODULE_DESCRIPTION("User mode SPI device interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:spidev");
