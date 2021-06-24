<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx AXIS FIFO: पूर्णांकerface to the Xilinx AXI-Stream FIFO IP core
 *
 * Copyright (C) 2018 Jacob Feder
 *
 * Authors:  Jacob Feder <jacobsfeder@gmail.com>
 *
 * See Xilinx PG080 करोcument क्रम IP details
 */

/* ----------------------------
 *           includes
 * ----------------------------
 */

#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/param.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

/* ----------------------------
 *       driver parameters
 * ----------------------------
 */

#घोषणा DRIVER_NAME "axis_fifo"

#घोषणा READ_BUF_SIZE 128U /* पढ़ो buffer length in words */
#घोषणा WRITE_BUF_SIZE 128U /* ग_लिखो buffer length in words */

/* ----------------------------
 *     IP रेजिस्टर offsets
 * ----------------------------
 */

#घोषणा XLLF_ISR_OFFSET  0x00000000  /* Interrupt Status */
#घोषणा XLLF_IER_OFFSET  0x00000004  /* Interrupt Enable */

#घोषणा XLLF_TDFR_OFFSET 0x00000008  /* Transmit Reset */
#घोषणा XLLF_TDFV_OFFSET 0x0000000c  /* Transmit Vacancy */
#घोषणा XLLF_TDFD_OFFSET 0x00000010  /* Transmit Data */
#घोषणा XLLF_TLR_OFFSET  0x00000014  /* Transmit Length */

#घोषणा XLLF_RDFR_OFFSET 0x00000018  /* Receive Reset */
#घोषणा XLLF_RDFO_OFFSET 0x0000001c  /* Receive Occupancy */
#घोषणा XLLF_RDFD_OFFSET 0x00000020  /* Receive Data */
#घोषणा XLLF_RLR_OFFSET  0x00000024  /* Receive Length */
#घोषणा XLLF_SRR_OFFSET  0x00000028  /* Local Link Reset */
#घोषणा XLLF_TDR_OFFSET  0x0000002C  /* Transmit Destination */
#घोषणा XLLF_RDR_OFFSET  0x00000030  /* Receive Destination */

/* ----------------------------
 *     reset रेजिस्टर masks
 * ----------------------------
 */

#घोषणा XLLF_RDFR_RESET_MASK        0x000000a5 /* receive reset value */
#घोषणा XLLF_TDFR_RESET_MASK        0x000000a5 /* Transmit reset value */
#घोषणा XLLF_SRR_RESET_MASK         0x000000a5 /* Local Link reset value */

/* ----------------------------
 *       पूर्णांकerrupt masks
 * ----------------------------
 */

#घोषणा XLLF_INT_RPURE_MASK       0x80000000 /* Receive under-पढ़ो */
#घोषणा XLLF_INT_RPORE_MASK       0x40000000 /* Receive over-पढ़ो */
#घोषणा XLLF_INT_RPUE_MASK        0x20000000 /* Receive underrun (empty) */
#घोषणा XLLF_INT_TPOE_MASK        0x10000000 /* Transmit overrun */
#घोषणा XLLF_INT_TC_MASK          0x08000000 /* Transmit complete */
#घोषणा XLLF_INT_RC_MASK          0x04000000 /* Receive complete */
#घोषणा XLLF_INT_TSE_MASK         0x02000000 /* Transmit length mismatch */
#घोषणा XLLF_INT_TRC_MASK         0x01000000 /* Transmit reset complete */
#घोषणा XLLF_INT_RRC_MASK         0x00800000 /* Receive reset complete */
#घोषणा XLLF_INT_TFPF_MASK        0x00400000 /* Tx FIFO Programmable Full */
#घोषणा XLLF_INT_TFPE_MASK        0x00200000 /* Tx FIFO Programmable Empty */
#घोषणा XLLF_INT_RFPF_MASK        0x00100000 /* Rx FIFO Programmable Full */
#घोषणा XLLF_INT_RFPE_MASK        0x00080000 /* Rx FIFO Programmable Empty */
#घोषणा XLLF_INT_ALL_MASK         0xfff80000 /* All the पूर्णांकs */
#घोषणा XLLF_INT_ERROR_MASK       0xf2000000 /* Error status पूर्णांकs */
#घोषणा XLLF_INT_RXERROR_MASK     0xe0000000 /* Receive Error status पूर्णांकs */
#घोषणा XLLF_INT_TXERROR_MASK     0x12000000 /* Transmit Error status पूर्णांकs */

/* ----------------------------
 *           globals
 * ----------------------------
 */

अटल काष्ठा class *axis_fअगरo_driver_class; /* अक्षर device class */

अटल पूर्णांक पढ़ो_समयout = 1000; /* ms to रुको beक्रमe पढ़ो() बार out */
अटल पूर्णांक ग_लिखो_समयout = 1000; /* ms to रुको beक्रमe ग_लिखो() बार out */

/* ----------------------------
 * module command-line arguments
 * ----------------------------
 */

module_param(पढ़ो_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(पढ़ो_समयout, "ms to wait before blocking read() timing out; set to -1 for no timeout");
module_param(ग_लिखो_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(ग_लिखो_समयout, "ms to wait before blocking write() timing out; set to -1 for no timeout");

/* ----------------------------
 *            types
 * ----------------------------
 */

काष्ठा axis_fअगरo अणु
	पूर्णांक irq; /* पूर्णांकerrupt */
	व्योम __iomem *base_addr; /* kernel space memory */

	अचिन्हित पूर्णांक rx_fअगरo_depth; /* max words in the receive fअगरo */
	अचिन्हित पूर्णांक tx_fअगरo_depth; /* max words in the transmit fअगरo */
	पूर्णांक has_rx_fअगरo; /* whether the IP has the rx fअगरo enabled */
	पूर्णांक has_tx_fअगरo; /* whether the IP has the tx fअगरo enabled */

	रुको_queue_head_t पढ़ो_queue; /* रुको queue क्रम asynchronos पढ़ो */
	काष्ठा mutex पढ़ो_lock; /* lock क्रम पढ़ोing */
	रुको_queue_head_t ग_लिखो_queue; /* रुको queue क्रम asynchronos ग_लिखो */
	काष्ठा mutex ग_लिखो_lock; /* lock क्रम writing */
	अचिन्हित पूर्णांक ग_लिखो_flags; /* ग_लिखो file flags */
	अचिन्हित पूर्णांक पढ़ो_flags; /* पढ़ो file flags */

	काष्ठा device *dt_device; /* device created from the device tree */
	काष्ठा device *device; /* device associated with अक्षर_device */
	dev_t devt; /* our अक्षर device number */
	काष्ठा cdev अक्षर_device; /* our अक्षर device */
पूर्ण;

/* ----------------------------
 *         sysfs entries
 * ----------------------------
 */

अटल sमाप_प्रकार sysfs_ग_लिखो(काष्ठा device *dev, स्थिर अक्षर *buf,
			   माप_प्रकार count, अचिन्हित पूर्णांक addr_offset)
अणु
	काष्ठा axis_fअगरo *fअगरo = dev_get_drvdata(dev);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 0, &पंचांगp);
	अगर (rc < 0)
		वापस rc;

	ioग_लिखो32(पंचांगp, fअगरo->base_addr + addr_offset);

	वापस count;
पूर्ण

अटल sमाप_प्रकार sysfs_पढ़ो(काष्ठा device *dev, अक्षर *buf,
			  अचिन्हित पूर्णांक addr_offset)
अणु
	काष्ठा axis_fअगरo *fअगरo = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पढ़ो_val;
	अचिन्हित पूर्णांक len;
	अक्षर पंचांगp[32];

	पढ़ो_val = ioपढ़ो32(fअगरo->base_addr + addr_offset);
	len =  snम_लिखो(पंचांगp, माप(पंचांगp), "0x%x\n", पढ़ो_val);
	स_नकल(buf, पंचांगp, len);

	वापस len;
पूर्ण

अटल sमाप_प्रकार isr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_ISR_OFFSET);
पूर्ण

अटल sमाप_प्रकार isr_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_ISR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RW(isr);

अटल sमाप_प्रकार ier_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_IER_OFFSET);
पूर्ण

अटल sमाप_प्रकार ier_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_IER_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RW(ier);

अटल sमाप_प्रकार tdfr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_TDFR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(tdfr);

अटल sमाप_प्रकार tdfv_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_TDFV_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RO(tdfv);

अटल sमाप_प्रकार tdfd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_TDFD_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(tdfd);

अटल sमाप_प्रकार tlr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_TLR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(tlr);

अटल sमाप_प्रकार rdfr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_RDFR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(rdfr);

अटल sमाप_प्रकार rdfo_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_RDFO_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RO(rdfo);

अटल sमाप_प्रकार rdfd_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_RDFD_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RO(rdfd);

अटल sमाप_प्रकार rlr_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_RLR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RO(rlr);

अटल sमाप_प्रकार srr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_SRR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(srr);

अटल sमाप_प्रकार tdr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस sysfs_ग_लिखो(dev, buf, count, XLLF_TDR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_WO(tdr);

अटल sमाप_प्रकार rdr_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_पढ़ो(dev, buf, XLLF_RDR_OFFSET);
पूर्ण

अटल DEVICE_ATTR_RO(rdr);

अटल काष्ठा attribute *axis_fअगरo_attrs[] = अणु
	&dev_attr_isr.attr,
	&dev_attr_ier.attr,
	&dev_attr_tdfr.attr,
	&dev_attr_tdfv.attr,
	&dev_attr_tdfd.attr,
	&dev_attr_tlr.attr,
	&dev_attr_rdfr.attr,
	&dev_attr_rdfo.attr,
	&dev_attr_rdfd.attr,
	&dev_attr_rlr.attr,
	&dev_attr_srr.attr,
	&dev_attr_tdr.attr,
	&dev_attr_rdr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group axis_fअगरo_attrs_group = अणु
	.name = "ip_registers",
	.attrs = axis_fअगरo_attrs,
पूर्ण;

/* ----------------------------
 *        implementation
 * ----------------------------
 */

अटल व्योम reset_ip_core(काष्ठा axis_fअगरo *fअगरo)
अणु
	ioग_लिखो32(XLLF_SRR_RESET_MASK, fअगरo->base_addr + XLLF_SRR_OFFSET);
	ioग_लिखो32(XLLF_TDFR_RESET_MASK, fअगरo->base_addr + XLLF_TDFR_OFFSET);
	ioग_लिखो32(XLLF_RDFR_RESET_MASK, fअगरo->base_addr + XLLF_RDFR_OFFSET);
	ioग_लिखो32(XLLF_INT_TC_MASK | XLLF_INT_RC_MASK | XLLF_INT_RPURE_MASK |
		  XLLF_INT_RPORE_MASK | XLLF_INT_RPUE_MASK |
		  XLLF_INT_TPOE_MASK | XLLF_INT_TSE_MASK,
		  fअगरo->base_addr + XLLF_IER_OFFSET);
	ioग_लिखो32(XLLF_INT_ALL_MASK, fअगरo->base_addr + XLLF_ISR_OFFSET);
पूर्ण

/**
 * axis_fअगरo_ग_लिखो() - Read a packet from AXIS-FIFO अक्षरacter device.
 * @f Open file.
 * @buf User space buffer to पढ़ो to.
 * @len User space buffer length.
 * @off Buffer offset.
 *
 * As defined by the device's documentation, we need to check the device's
 * occupancy beक्रमe पढ़ोing the length रेजिस्टर and then the data. All these
 * operations must be executed atomically, in order and one after the other
 * without missing any.
 *
 * Returns the number of bytes पढ़ो from the device or negative error code
 *	on failure.
 */
अटल sमाप_प्रकार axis_fअगरo_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
			      माप_प्रकार len, loff_t *off)
अणु
	काष्ठा axis_fअगरo *fअगरo = (काष्ठा axis_fअगरo *)f->निजी_data;
	माप_प्रकार bytes_available;
	अचिन्हित पूर्णांक words_available;
	अचिन्हित पूर्णांक copied;
	अचिन्हित पूर्णांक copy;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	u32 पंचांगp_buf[READ_BUF_SIZE];

	अगर (fअगरo->पढ़ो_flags & O_NONBLOCK) अणु
		/*
		 * Device खोलोed in non-blocking mode. Try to lock it and then
		 * check अगर any packet is available.
		 */
		अगर (!mutex_trylock(&fअगरo->पढ़ो_lock))
			वापस -EAGAIN;

		अगर (!ioपढ़ो32(fअगरo->base_addr + XLLF_RDFO_OFFSET)) अणु
			ret = -EAGAIN;
			जाओ end_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* खोलोed in blocking mode
		 * रुको क्रम a packet available पूर्णांकerrupt (or समयout)
		 * अगर nothing is currently available
		 */
		mutex_lock(&fअगरo->पढ़ो_lock);
		ret = रुको_event_पूर्णांकerruptible_समयout(fअगरo->पढ़ो_queue,
			ioपढ़ो32(fअगरo->base_addr + XLLF_RDFO_OFFSET),
				 (पढ़ो_समयout >= 0) ?
				  msecs_to_jअगरfies(पढ़ो_समयout) :
				  MAX_SCHEDULE_TIMEOUT);

		अगर (ret <= 0) अणु
			अगर (ret == 0) अणु
				ret = -EAGAIN;
			पूर्ण अन्यथा अगर (ret != -ERESTARTSYS) अणु
				dev_err(fअगरo->dt_device, "wait_event_interruptible_timeout() error in read (ret=%i)\n",
					ret);
			पूर्ण

			जाओ end_unlock;
		पूर्ण
	पूर्ण

	bytes_available = ioपढ़ो32(fअगरo->base_addr + XLLF_RLR_OFFSET);
	अगर (!bytes_available) अणु
		dev_err(fअगरo->dt_device, "received a packet of length 0 - fifo core will be reset\n");
		reset_ip_core(fअगरo);
		ret = -EIO;
		जाओ end_unlock;
	पूर्ण

	अगर (bytes_available > len) अणु
		dev_err(fअगरo->dt_device, "user read buffer too small (available bytes=%zu user buffer bytes=%zu) - fifo core will be reset\n",
			bytes_available, len);
		reset_ip_core(fअगरo);
		ret = -EINVAL;
		जाओ end_unlock;
	पूर्ण

	अगर (bytes_available % माप(u32)) अणु
		/* this probably can't happen unless IP
		 * रेजिस्टरs were previously mishandled
		 */
		dev_err(fअगरo->dt_device, "received a packet that isn't word-aligned - fifo core will be reset\n");
		reset_ip_core(fअगरo);
		ret = -EIO;
		जाओ end_unlock;
	पूर्ण

	words_available = bytes_available / माप(u32);

	/* पढ़ो data पूर्णांकo an पूर्णांकermediate buffer, copying the contents
	 * to userspace when the buffer is full
	 */
	copied = 0;
	जबतक (words_available > 0) अणु
		copy = min(words_available, READ_BUF_SIZE);

		क्रम (i = 0; i < copy; i++) अणु
			पंचांगp_buf[i] = ioपढ़ो32(fअगरo->base_addr +
					      XLLF_RDFD_OFFSET);
		पूर्ण

		अगर (copy_to_user(buf + copied * माप(u32), पंचांगp_buf,
				 copy * माप(u32))) अणु
			reset_ip_core(fअगरo);
			ret = -EFAULT;
			जाओ end_unlock;
		पूर्ण

		copied += copy;
		words_available -= copy;
	पूर्ण

	ret = bytes_available;

end_unlock:
	mutex_unlock(&fअगरo->पढ़ो_lock);

	वापस ret;
पूर्ण

/**
 * axis_fअगरo_ग_लिखो() - Write buffer to AXIS-FIFO अक्षरacter device.
 * @f Open file.
 * @buf User space buffer to ग_लिखो to the device.
 * @len User space buffer length.
 * @off Buffer offset.
 *
 * As defined by the device's documentation, we need to write to the device's
 * data buffer then to the device's packet length रेजिस्टर atomically. Also,
 * we need to lock beक्रमe checking अगर the device has available space to aव्योम
 * any concurrency issue.
 *
 * Returns the number of bytes written to the device or negative error code
 *	on failure.
 */
अटल sमाप_प्रकार axis_fअगरo_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
			       माप_प्रकार len, loff_t *off)
अणु
	काष्ठा axis_fअगरo *fअगरo = (काष्ठा axis_fअगरo *)f->निजी_data;
	अचिन्हित पूर्णांक words_to_ग_लिखो;
	अचिन्हित पूर्णांक copied;
	अचिन्हित पूर्णांक copy;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	u32 पंचांगp_buf[WRITE_BUF_SIZE];

	अगर (len % माप(u32)) अणु
		dev_err(fअगरo->dt_device,
			"tried to send a packet that isn't word-aligned\n");
		वापस -EINVAL;
	पूर्ण

	words_to_ग_लिखो = len / माप(u32);

	अगर (!words_to_ग_लिखो) अणु
		dev_err(fअगरo->dt_device,
			"tried to send a packet of length 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (words_to_ग_लिखो > fअगरo->tx_fअगरo_depth) अणु
		dev_err(fअगरo->dt_device, "tried to write more words [%u] than slots in the fifo buffer [%u]\n",
			words_to_ग_लिखो, fअगरo->tx_fअगरo_depth);
		वापस -EINVAL;
	पूर्ण

	अगर (fअगरo->ग_लिखो_flags & O_NONBLOCK) अणु
		/*
		 * Device खोलोed in non-blocking mode. Try to lock it and then
		 * check अगर there is any room to ग_लिखो the given buffer.
		 */
		अगर (!mutex_trylock(&fअगरo->ग_लिखो_lock))
			वापस -EAGAIN;

		अगर (words_to_ग_लिखो > ioपढ़ो32(fअगरo->base_addr +
					      XLLF_TDFV_OFFSET)) अणु
			ret = -EAGAIN;
			जाओ end_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* खोलोed in blocking mode */

		/* रुको क्रम an पूर्णांकerrupt (or समयout) अगर there isn't
		 * currently enough room in the fअगरo
		 */
		mutex_lock(&fअगरo->ग_लिखो_lock);
		ret = रुको_event_पूर्णांकerruptible_समयout(fअगरo->ग_लिखो_queue,
			ioपढ़ो32(fअगरo->base_addr + XLLF_TDFV_OFFSET)
				 >= words_to_ग_लिखो,
				 (ग_लिखो_समयout >= 0) ?
				  msecs_to_jअगरfies(ग_लिखो_समयout) :
				  MAX_SCHEDULE_TIMEOUT);

		अगर (ret <= 0) अणु
			अगर (ret == 0) अणु
				ret = -EAGAIN;
			पूर्ण अन्यथा अगर (ret != -ERESTARTSYS) अणु
				dev_err(fअगरo->dt_device, "wait_event_interruptible_timeout() error in write (ret=%i)\n",
					ret);
			पूर्ण

			जाओ end_unlock;
		पूर्ण
	पूर्ण

	/* ग_लिखो data from an पूर्णांकermediate buffer पूर्णांकo the fअगरo IP, refilling
	 * the buffer with userspace data as needed
	 */
	copied = 0;
	जबतक (words_to_ग_लिखो > 0) अणु
		copy = min(words_to_ग_लिखो, WRITE_BUF_SIZE);

		अगर (copy_from_user(पंचांगp_buf, buf + copied * माप(u32),
				   copy * माप(u32))) अणु
			reset_ip_core(fअगरo);
			ret = -EFAULT;
			जाओ end_unlock;
		पूर्ण

		क्रम (i = 0; i < copy; i++)
			ioग_लिखो32(पंचांगp_buf[i], fअगरo->base_addr +
				  XLLF_TDFD_OFFSET);

		copied += copy;
		words_to_ग_लिखो -= copy;
	पूर्ण

	ret = copied * माप(u32);

	/* ग_लिखो packet size to fअगरo */
	ioग_लिखो32(ret, fअगरo->base_addr + XLLF_TLR_OFFSET);

end_unlock:
	mutex_unlock(&fअगरo->ग_लिखो_lock);

	वापस ret;
पूर्ण

अटल irqवापस_t axis_fअगरo_irq(पूर्णांक irq, व्योम *dw)
अणु
	काष्ठा axis_fअगरo *fअगरo = (काष्ठा axis_fअगरo *)dw;
	अचिन्हित पूर्णांक pending_पूर्णांकerrupts;

	करो अणु
		pending_पूर्णांकerrupts = ioपढ़ो32(fअगरo->base_addr +
					      XLLF_IER_OFFSET) &
					      ioपढ़ो32(fअगरo->base_addr
					      + XLLF_ISR_OFFSET);
		अगर (pending_पूर्णांकerrupts & XLLF_INT_RC_MASK) अणु
			/* packet received */

			/* wake the पढ़ोer process अगर it is रुकोing */
			wake_up(&fअगरo->पढ़ो_queue);

			/* clear पूर्णांकerrupt */
			ioग_लिखो32(XLLF_INT_RC_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TC_MASK) अणु
			/* packet sent */

			/* wake the ग_लिखोr process अगर it is रुकोing */
			wake_up(&fअगरo->ग_लिखो_queue);

			ioग_लिखो32(XLLF_INT_TC_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TFPF_MASK) अणु
			/* transmit fअगरo programmable full */

			ioग_लिखो32(XLLF_INT_TFPF_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TFPE_MASK) अणु
			/* transmit fअगरo programmable empty */

			ioग_लिखो32(XLLF_INT_TFPE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RFPF_MASK) अणु
			/* receive fअगरo programmable full */

			ioग_लिखो32(XLLF_INT_RFPF_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RFPE_MASK) अणु
			/* receive fअगरo programmable empty */

			ioग_लिखो32(XLLF_INT_RFPE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TRC_MASK) अणु
			/* transmit reset complete पूर्णांकerrupt */

			ioग_लिखो32(XLLF_INT_TRC_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RRC_MASK) अणु
			/* receive reset complete पूर्णांकerrupt */

			ioग_लिखो32(XLLF_INT_RRC_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RPURE_MASK) अणु
			/* receive fअगरo under-पढ़ो error पूर्णांकerrupt */
			dev_err(fअगरo->dt_device,
				"receive under-read interrupt\n");

			ioग_लिखो32(XLLF_INT_RPURE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RPORE_MASK) अणु
			/* receive over-पढ़ो error पूर्णांकerrupt */
			dev_err(fअगरo->dt_device,
				"receive over-read interrupt\n");

			ioग_लिखो32(XLLF_INT_RPORE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_RPUE_MASK) अणु
			/* receive underrun error पूर्णांकerrupt */
			dev_err(fअगरo->dt_device,
				"receive underrun error interrupt\n");

			ioग_लिखो32(XLLF_INT_RPUE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TPOE_MASK) अणु
			/* transmit overrun error पूर्णांकerrupt */
			dev_err(fअगरo->dt_device,
				"transmit overrun error interrupt\n");

			ioग_लिखो32(XLLF_INT_TPOE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts & XLLF_INT_TSE_MASK) अणु
			/* transmit length mismatch error पूर्णांकerrupt */
			dev_err(fअगरo->dt_device,
				"transmit length mismatch error interrupt\n");

			ioग_लिखो32(XLLF_INT_TSE_MASK & XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण अन्यथा अगर (pending_पूर्णांकerrupts) अणु
			/* unknown पूर्णांकerrupt type */
			dev_err(fअगरo->dt_device,
				"unknown interrupt(s) 0x%x\n",
				pending_पूर्णांकerrupts);

			ioग_लिखो32(XLLF_INT_ALL_MASK,
				  fअगरo->base_addr + XLLF_ISR_OFFSET);
		पूर्ण
	पूर्ण जबतक (pending_पूर्णांकerrupts);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक axis_fअगरo_खोलो(काष्ठा inode *inod, काष्ठा file *f)
अणु
	काष्ठा axis_fअगरo *fअगरo = (काष्ठा axis_fअगरo *)container_of(inod->i_cdev,
					काष्ठा axis_fअगरo, अक्षर_device);
	f->निजी_data = fअगरo;

	अगर (((f->f_flags & O_ACCMODE) == O_WRONLY) ||
	    ((f->f_flags & O_ACCMODE) == O_RDWR)) अणु
		अगर (fअगरo->has_tx_fअगरo) अणु
			fअगरo->ग_लिखो_flags = f->f_flags;
		पूर्ण अन्यथा अणु
			dev_err(fअगरo->dt_device, "tried to open device for write but the transmit fifo is disabled\n");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	अगर (((f->f_flags & O_ACCMODE) == O_RDONLY) ||
	    ((f->f_flags & O_ACCMODE) == O_RDWR)) अणु
		अगर (fअगरo->has_rx_fअगरo) अणु
			fअगरo->पढ़ो_flags = f->f_flags;
		पूर्ण अन्यथा अणु
			dev_err(fअगरo->dt_device, "tried to open device for read but the receive fifo is disabled\n");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axis_fअगरo_बंद(काष्ठा inode *inod, काष्ठा file *f)
अणु
	f->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner = THIS_MODULE,
	.खोलो = axis_fअगरo_खोलो,
	.release = axis_fअगरo_बंद,
	.पढ़ो = axis_fअगरo_पढ़ो,
	.ग_लिखो = axis_fअगरo_ग_लिखो
पूर्ण;

/* पढ़ो named property from the device tree */
अटल पूर्णांक get_dts_property(काष्ठा axis_fअगरo *fअगरo,
			    अक्षर *name, अचिन्हित पूर्णांक *var)
अणु
	पूर्णांक rc;

	rc = of_property_पढ़ो_u32(fअगरo->dt_device->of_node, name, var);
	अगर (rc) अणु
		dev_err(fअगरo->dt_device, "couldn't read IP dts property '%s'",
			name);
		वापस rc;
	पूर्ण
	dev_dbg(fअगरo->dt_device, "dts property '%s' = %u\n",
		name, *var);

	वापस 0;
पूर्ण

अटल पूर्णांक axis_fअगरo_parse_dt(काष्ठा axis_fअगरo *fअगरo)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	ret = get_dts_property(fअगरo, "xlnx,axi-str-rxd-tdata-width", &value);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,axi-str-rxd-tdata-width property\n");
		जाओ end;
	पूर्ण अन्यथा अगर (value != 32) अणु
		dev_err(fअगरo->dt_device, "xlnx,axi-str-rxd-tdata-width only supports 32 bits\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

	ret = get_dts_property(fअगरo, "xlnx,axi-str-txd-tdata-width", &value);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,axi-str-txd-tdata-width property\n");
		जाओ end;
	पूर्ण अन्यथा अगर (value != 32) अणु
		dev_err(fअगरo->dt_device, "xlnx,axi-str-txd-tdata-width only supports 32 bits\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

	ret = get_dts_property(fअगरo, "xlnx,rx-fifo-depth",
			       &fअगरo->rx_fअगरo_depth);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,rx-fifo-depth property\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

	ret = get_dts_property(fअगरo, "xlnx,tx-fifo-depth",
			       &fअगरo->tx_fअगरo_depth);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,tx-fifo-depth property\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

	/* IP sets TDFV to fअगरo depth - 4 so we will करो the same */
	fअगरo->tx_fअगरo_depth -= 4;

	ret = get_dts_property(fअगरo, "xlnx,use-rx-data", &fअगरo->has_rx_fअगरo);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,use-rx-data property\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

	ret = get_dts_property(fअगरo, "xlnx,use-tx-data", &fअगरo->has_tx_fअगरo);
	अगर (ret) अणु
		dev_err(fअगरo->dt_device, "missing xlnx,use-tx-data property\n");
		ret = -EIO;
		जाओ end;
	पूर्ण

end:
	वापस ret;
पूर्ण

अटल पूर्णांक axis_fअगरo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r_irq; /* पूर्णांकerrupt resources */
	काष्ठा resource *r_mem; /* IO mem resources */
	काष्ठा device *dev = &pdev->dev; /* OS device (from device tree) */
	काष्ठा axis_fअगरo *fअगरo = शून्य;

	अक्षर device_name[32];

	पूर्णांक rc = 0; /* error वापस value */

	/* ----------------------------
	 *     init wrapper device
	 * ----------------------------
	 */

	/* allocate device wrapper memory */
	fअगरo = devm_kदो_स्मृति(dev, माप(*fअगरo), GFP_KERNEL);
	अगर (!fअगरo)
		वापस -ENOMEM;

	dev_set_drvdata(dev, fअगरo);
	fअगरo->dt_device = dev;

	init_रुकोqueue_head(&fअगरo->पढ़ो_queue);
	init_रुकोqueue_head(&fअगरo->ग_लिखो_queue);

	mutex_init(&fअगरo->पढ़ो_lock);
	mutex_init(&fअगरo->ग_लिखो_lock);

	/* ----------------------------
	 *   init device memory space
	 * ----------------------------
	 */

	/* get iospace क्रम the device */
	r_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r_mem) अणु
		dev_err(fअगरo->dt_device, "invalid address\n");
		rc = -ENODEV;
		जाओ err_initial;
	पूर्ण

	/* request physical memory */
	fअगरo->base_addr = devm_ioremap_resource(fअगरo->dt_device, r_mem);
	अगर (IS_ERR(fअगरo->base_addr)) अणु
		rc = PTR_ERR(fअगरo->base_addr);
		जाओ err_initial;
	पूर्ण

	dev_dbg(fअगरo->dt_device, "remapped memory to 0x%p\n", fअगरo->base_addr);

	/* create unique device name */
	snम_लिखो(device_name, माप(device_name), "%s_%pa",
		 DRIVER_NAME, &r_mem->start);

	dev_dbg(fअगरo->dt_device, "device name [%s]\n", device_name);

	/* ----------------------------
	 *          init IP
	 * ----------------------------
	 */

	rc = axis_fअगरo_parse_dt(fअगरo);
	अगर (rc)
		जाओ err_initial;

	reset_ip_core(fअगरo);

	/* ----------------------------
	 *    init device पूर्णांकerrupts
	 * ----------------------------
	 */

	/* get IRQ resource */
	r_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!r_irq) अणु
		dev_err(fअगरo->dt_device, "no IRQ found for 0x%pa\n",
			&r_mem->start);
		rc = -EIO;
		जाओ err_initial;
	पूर्ण

	/* request IRQ */
	fअगरo->irq = r_irq->start;
	rc = devm_request_irq(fअगरo->dt_device, fअगरo->irq, &axis_fअगरo_irq, 0,
			      DRIVER_NAME, fअगरo);
	अगर (rc) अणु
		dev_err(fअगरo->dt_device, "couldn't allocate interrupt %i\n",
			fअगरo->irq);
		जाओ err_initial;
	पूर्ण

	/* ----------------------------
	 *      init अक्षर device
	 * ----------------------------
	 */

	/* allocate device number */
	rc = alloc_chrdev_region(&fअगरo->devt, 0, 1, DRIVER_NAME);
	अगर (rc < 0)
		जाओ err_initial;
	dev_dbg(fअगरo->dt_device, "allocated device number major %i minor %i\n",
		MAJOR(fअगरo->devt), MINOR(fअगरo->devt));

	/* create driver file */
	fअगरo->device = device_create(axis_fअगरo_driver_class, शून्य, fअगरo->devt,
				     शून्य, device_name);
	अगर (IS_ERR(fअगरo->device)) अणु
		dev_err(fअगरo->dt_device,
			"couldn't create driver file\n");
		rc = PTR_ERR(fअगरo->device);
		जाओ err_chrdev_region;
	पूर्ण
	dev_set_drvdata(fअगरo->device, fअगरo);

	/* create अक्षरacter device */
	cdev_init(&fअगरo->अक्षर_device, &fops);
	rc = cdev_add(&fअगरo->अक्षर_device, fअगरo->devt, 1);
	अगर (rc < 0) अणु
		dev_err(fअगरo->dt_device, "couldn't create character device\n");
		जाओ err_dev;
	पूर्ण

	/* create sysfs entries */
	rc = devm_device_add_group(fअगरo->device, &axis_fअगरo_attrs_group);
	अगर (rc < 0) अणु
		dev_err(fअगरo->dt_device, "couldn't register sysfs group\n");
		जाओ err_cdev;
	पूर्ण

	dev_info(fअगरo->dt_device, "axis-fifo created at %pa mapped to 0x%pa, irq=%i, major=%i, minor=%i\n",
		 &r_mem->start, &fअगरo->base_addr, fअगरo->irq,
		 MAJOR(fअगरo->devt), MINOR(fअगरo->devt));

	वापस 0;

err_cdev:
	cdev_del(&fअगरo->अक्षर_device);
err_dev:
	device_destroy(axis_fअगरo_driver_class, fअगरo->devt);
err_chrdev_region:
	unरेजिस्टर_chrdev_region(fअगरo->devt, 1);
err_initial:
	dev_set_drvdata(dev, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक axis_fअगरo_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा axis_fअगरo *fअगरo = dev_get_drvdata(dev);

	cdev_del(&fअगरo->अक्षर_device);
	dev_set_drvdata(fअगरo->device, शून्य);
	device_destroy(axis_fअगरo_driver_class, fअगरo->devt);
	unरेजिस्टर_chrdev_region(fअगरo->devt, 1);
	dev_set_drvdata(dev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axis_fअगरo_of_match[] = अणु
	अणु .compatible = "xlnx,axi-fifo-mm-s-4.1", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axis_fअगरo_of_match);

अटल काष्ठा platक्रमm_driver axis_fअगरo_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table	= axis_fअगरo_of_match,
	पूर्ण,
	.probe		= axis_fअगरo_probe,
	.हटाओ		= axis_fअगरo_हटाओ,
पूर्ण;

अटल पूर्णांक __init axis_fअगरo_init(व्योम)
अणु
	pr_info("axis-fifo driver loaded with parameters read_timeout = %i, write_timeout = %i\n",
		पढ़ो_समयout, ग_लिखो_समयout);
	axis_fअगरo_driver_class = class_create(THIS_MODULE, DRIVER_NAME);
	अगर (IS_ERR(axis_fअगरo_driver_class))
		वापस PTR_ERR(axis_fअगरo_driver_class);
	वापस platक्रमm_driver_रेजिस्टर(&axis_fअगरo_driver);
पूर्ण

module_init(axis_fअगरo_init);

अटल व्योम __निकास axis_fअगरo_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&axis_fअगरo_driver);
	class_destroy(axis_fअगरo_driver_class);
पूर्ण

module_निकास(axis_fअगरo_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jacob Feder <jacobsfeder@gmail.com>");
MODULE_DESCRIPTION("Xilinx AXI-Stream FIFO v4.1 IP core driver");
