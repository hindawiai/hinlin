<शैली गुरु>
/*
 * The DSP56001 Device Driver, saviour of the Free World(पंचांग)
 *
 * Authors: Fredrik Noring   <noring@nocrew.org>
 *          lars brinkhoff   <lars@nocrew.org>
 *          Tomas Berndtsson <tomas@nocrew.org>
 *
 * First version May 1996
 *
 * History:
 *  97-01-29   Tomas Berndtsson,
 *               Integrated with Linux 2.1.21 kernel sources.
 *  97-02-15   Tomas Berndtsson,
 *               Fixed क्रम kernel 2.1.26
 *
 * BUGS:
 *  Hmm... there must be something here :)
 *
 * Copyright (C) 1996,1997 Fredrik Noring, lars brinkhoff & Tomas Berndtsson
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/major.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>	/* guess what */
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>	/* For put_user and get_user */

#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/dsp56k.h>

/* minor devices */
#घोषणा DSP56K_DEV_56001        0    /* The only device so far */

#घोषणा TIMEOUT    10   /* Host port समयout in number of tries */
#घोषणा MAXIO    2048   /* Maximum number of words beक्रमe sleep */
#घोषणा DSP56K_MAX_BINARY_LENGTH (3*64*1024)

#घोषणा DSP56K_TX_INT_ON	dsp56k_host_पूर्णांकerface.icr |=  DSP56K_ICR_TREQ
#घोषणा DSP56K_RX_INT_ON	dsp56k_host_पूर्णांकerface.icr |=  DSP56K_ICR_RREQ
#घोषणा DSP56K_TX_INT_OFF	dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_TREQ
#घोषणा DSP56K_RX_INT_OFF	dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_RREQ

#घोषणा DSP56K_TRANSMIT		(dsp56k_host_पूर्णांकerface.isr & DSP56K_ISR_TXDE)
#घोषणा DSP56K_RECEIVE		(dsp56k_host_पूर्णांकerface.isr & DSP56K_ISR_RXDF)

#घोषणा handshake(count, maxio, समयout, ENABLE, f) \
अणु \
	दीर्घ i, t, m; \
	जबतक (count > 0) अणु \
		m = min_t(अचिन्हित दीर्घ, count, maxio); \
		क्रम (i = 0; i < m; i++) अणु \
			क्रम (t = 0; t < समयout && !ENABLE; t++) \
				msleep(20); \
			अगर(!ENABLE) \
				वापस -EIO; \
			f; \
		पूर्ण \
		count -= m; \
		अगर (m == maxio) msleep(20); \
	पूर्ण \
पूर्ण

#घोषणा tx_रुको(n) \
अणु \
	पूर्णांक t; \
	क्रम(t = 0; t < n && !DSP56K_TRANSMIT; t++) \
		msleep(10); \
	अगर(!DSP56K_TRANSMIT) अणु \
		वापस -EIO; \
	पूर्ण \
पूर्ण

#घोषणा rx_रुको(n) \
अणु \
	पूर्णांक t; \
	क्रम(t = 0; t < n && !DSP56K_RECEIVE; t++) \
		msleep(10); \
	अगर(!DSP56K_RECEIVE) अणु \
		वापस -EIO; \
	पूर्ण \
पूर्ण

अटल DEFINE_MUTEX(dsp56k_mutex);
अटल काष्ठा dsp56k_device अणु
	अचिन्हित दीर्घ in_use;
	दीर्घ maxio, समयout;
	पूर्णांक tx_wsize, rx_wsize;
पूर्ण dsp56k;

अटल काष्ठा class *dsp56k_class;

अटल पूर्णांक dsp56k_reset(व्योम)
अणु
	u_अक्षर status;
	
	/* Power करोwn the DSP */
	sound_ym.rd_data_reg_sel = 14;
	status = sound_ym.rd_data_reg_sel & 0xef;
	sound_ym.wd_data = status;
	sound_ym.wd_data = status | 0x10;
  
	udelay(10);
  
	/* Power up the DSP */
	sound_ym.rd_data_reg_sel = 14;
	sound_ym.wd_data = sound_ym.rd_data_reg_sel & 0xef;

	वापस 0;
पूर्ण

अटल पूर्णांक dsp56k_upload(u_अक्षर __user *bin, पूर्णांक len)
अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fw_name[] = "dsp56k/bootstrap.bin";
	पूर्णांक err;
	पूर्णांक i;

	dsp56k_reset();

	pdev = platक्रमm_device_रेजिस्टर_simple("dsp56k", 0, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		prपूर्णांकk(KERN_ERR "Failed to register device for \"%s\"\n",
		       fw_name);
		वापस -EINVAL;
	पूर्ण
	err = request_firmware(&fw, fw_name, &pdev->dev);
	platक्रमm_device_unरेजिस्टर(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fw_name, err);
		वापस err;
	पूर्ण
	अगर (fw->size % 3) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %d in image \"%s\"\n",
		       fw->size, fw_name);
		release_firmware(fw);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < fw->size; i = i + 3) अणु
		/* tx_रुको(10); */
		dsp56k_host_पूर्णांकerface.data.b[1] = fw->data[i];
		dsp56k_host_पूर्णांकerface.data.b[2] = fw->data[i + 1];
		dsp56k_host_पूर्णांकerface.data.b[3] = fw->data[i + 2];
	पूर्ण
	release_firmware(fw);
	क्रम (; i < 512; i++) अणु
		/* tx_रुको(10); */
		dsp56k_host_पूर्णांकerface.data.b[1] = 0;
		dsp56k_host_पूर्णांकerface.data.b[2] = 0;
		dsp56k_host_पूर्णांकerface.data.b[3] = 0;
	पूर्ण
  
	क्रम (i = 0; i < len; i++) अणु
		tx_रुको(10);
		get_user(dsp56k_host_पूर्णांकerface.data.b[1], bin++);
		get_user(dsp56k_host_पूर्णांकerface.data.b[2], bin++);
		get_user(dsp56k_host_पूर्णांकerface.data.b[3], bin++);
	पूर्ण

	tx_रुको(10);
	dsp56k_host_पूर्णांकerface.data.l = 3;    /* Magic execute */

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dsp56k_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			   loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक dev = iminor(inode) & 0x0f;

	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:
	अणु

		दीर्घ n;

		/* Don't करो anything अगर nothing is to be करोne */
		अगर (!count) वापस 0;

		n = 0;
		चयन (dsp56k.rx_wsize) अणु
		हाल 1:  /* 8 bit */
		अणु
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_RECEIVE,
				  put_user(dsp56k_host_पूर्णांकerface.data.b[3], buf+n++));
			वापस n;
		पूर्ण
		हाल 2:  /* 16 bit */
		अणु
			लघु __user *data;

			count /= 2;
			data = (लघु __user *) buf;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_RECEIVE,
				  put_user(dsp56k_host_पूर्णांकerface.data.w[1], data+n++));
			वापस 2*n;
		पूर्ण
		हाल 3:  /* 24 bit */
		अणु
			count /= 3;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_RECEIVE,
				  put_user(dsp56k_host_पूर्णांकerface.data.b[1], buf+n++);
				  put_user(dsp56k_host_पूर्णांकerface.data.b[2], buf+n++);
				  put_user(dsp56k_host_पूर्णांकerface.data.b[3], buf+n++));
			वापस 3*n;
		पूर्ण
		हाल 4:  /* 32 bit */
		अणु
			दीर्घ __user *data;

			count /= 4;
			data = (दीर्घ __user *) buf;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_RECEIVE,
				  put_user(dsp56k_host_पूर्णांकerface.data.l, data+n++));
			वापस 4*n;
		पूर्ण
		पूर्ण
		वापस -EFAULT;
	पूर्ण

	शेष:
		prपूर्णांकk(KERN_ERR "DSP56k driver: Unknown minor device: %d\n", dev);
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार dsp56k_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक dev = iminor(inode) & 0x0f;

	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:
	अणु
		दीर्घ n;

		/* Don't करो anything अगर nothing is to be करोne */
		अगर (!count) वापस 0;

		n = 0;
		चयन (dsp56k.tx_wsize) अणु
		हाल 1:  /* 8 bit */
		अणु
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_TRANSMIT,
				  get_user(dsp56k_host_पूर्णांकerface.data.b[3], buf+n++));
			वापस n;
		पूर्ण
		हाल 2:  /* 16 bit */
		अणु
			स्थिर लघु __user *data;

			count /= 2;
			data = (स्थिर लघु __user *)buf;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_TRANSMIT,
				  get_user(dsp56k_host_पूर्णांकerface.data.w[1], data+n++));
			वापस 2*n;
		पूर्ण
		हाल 3:  /* 24 bit */
		अणु
			count /= 3;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_TRANSMIT,
				  get_user(dsp56k_host_पूर्णांकerface.data.b[1], buf+n++);
				  get_user(dsp56k_host_पूर्णांकerface.data.b[2], buf+n++);
				  get_user(dsp56k_host_पूर्णांकerface.data.b[3], buf+n++));
			वापस 3*n;
		पूर्ण
		हाल 4:  /* 32 bit */
		अणु
			स्थिर दीर्घ __user *data;

			count /= 4;
			data = (स्थिर दीर्घ __user *)buf;
			handshake(count, dsp56k.maxio, dsp56k.समयout, DSP56K_TRANSMIT,
				  get_user(dsp56k_host_पूर्णांकerface.data.l, data+n++));
			वापस 4*n;
		पूर्ण
		पूर्ण

		वापस -EFAULT;
	पूर्ण
	शेष:
		prपूर्णांकk(KERN_ERR "DSP56k driver: Unknown minor device: %d\n", dev);
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल दीर्घ dsp56k_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक dev = iminor(file_inode(file)) & 0x0f;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:

		चयन(cmd) अणु
		हाल DSP56K_UPLOAD:
		अणु
			अक्षर __user *bin;
			पूर्णांक r, len;
			काष्ठा dsp56k_upload __user *binary = argp;
    
			अगर(get_user(len, &binary->len) < 0)
				वापस -EFAULT;
			अगर(get_user(bin, &binary->bin) < 0)
				वापस -EFAULT;
		
			अगर (len <= 0) अणु
				वापस -EINVAL;      /* nothing to upload?!? */
			पूर्ण
			अगर (len > DSP56K_MAX_BINARY_LENGTH) अणु
				वापस -EINVAL;
			पूर्ण
			mutex_lock(&dsp56k_mutex);
			r = dsp56k_upload(bin, len);
			mutex_unlock(&dsp56k_mutex);
			अगर (r < 0) अणु
				वापस r;
			पूर्ण
    
			अवरोध;
		पूर्ण
		हाल DSP56K_SET_TX_WSIZE:
			अगर (arg > 4 || arg < 1)
				वापस -EINVAL;
			mutex_lock(&dsp56k_mutex);
			dsp56k.tx_wsize = (पूर्णांक) arg;
			mutex_unlock(&dsp56k_mutex);
			अवरोध;
		हाल DSP56K_SET_RX_WSIZE:
			अगर (arg > 4 || arg < 1)
				वापस -EINVAL;
			mutex_lock(&dsp56k_mutex);
			dsp56k.rx_wsize = (पूर्णांक) arg;
			mutex_unlock(&dsp56k_mutex);
			अवरोध;
		हाल DSP56K_HOST_FLAGS:
		अणु
			पूर्णांक dir, out, status;
			काष्ठा dsp56k_host_flags __user *hf = argp;
    
			अगर(get_user(dir, &hf->dir) < 0)
				वापस -EFAULT;
			अगर(get_user(out, &hf->out) < 0)
				वापस -EFAULT;

			mutex_lock(&dsp56k_mutex);
			अगर ((dir & 0x1) && (out & 0x1))
				dsp56k_host_पूर्णांकerface.icr |= DSP56K_ICR_HF0;
			अन्यथा अगर (dir & 0x1)
				dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_HF0;
			अगर ((dir & 0x2) && (out & 0x2))
				dsp56k_host_पूर्णांकerface.icr |= DSP56K_ICR_HF1;
			अन्यथा अगर (dir & 0x2)
				dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_HF1;

			status = 0;
			अगर (dsp56k_host_पूर्णांकerface.icr & DSP56K_ICR_HF0) status |= 0x1;
			अगर (dsp56k_host_पूर्णांकerface.icr & DSP56K_ICR_HF1) status |= 0x2;
			अगर (dsp56k_host_पूर्णांकerface.isr & DSP56K_ISR_HF2) status |= 0x4;
			अगर (dsp56k_host_पूर्णांकerface.isr & DSP56K_ISR_HF3) status |= 0x8;
			mutex_unlock(&dsp56k_mutex);
			वापस put_user(status, &hf->status);
		पूर्ण
		हाल DSP56K_HOST_CMD:
			अगर (arg > 31)
				वापस -EINVAL;
			mutex_lock(&dsp56k_mutex);
			dsp56k_host_पूर्णांकerface.cvr = (u_अक्षर)((arg & DSP56K_CVR_HV_MASK) |
							     DSP56K_CVR_HC);
			mutex_unlock(&dsp56k_mutex);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	शेष:
		prपूर्णांकk(KERN_ERR "DSP56k driver: Unknown minor device: %d\n", dev);
		वापस -ENXIO;
	पूर्ण
पूर्ण

/* As of 2.1.26 this should be dsp56k_poll,
 * but how करो I then check device minor number?
 * Do I need this function at all???
 */
#अगर 0
अटल __poll_t dsp56k_poll(काष्ठा file *file, poll_table *रुको)
अणु
	पूर्णांक dev = iminor(file_inode(file)) & 0x0f;

	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:
		/* poll_रुको(file, ???, रुको); */
		वापस EPOLLIN | EPOLLRDNORM | EPOLLOUT;

	शेष:
		prपूर्णांकk("DSP56k driver: Unknown minor device: %d\n", dev);
		वापस 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dsp56k_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक dev = iminor(inode) & 0x0f;
	पूर्णांक ret = 0;

	mutex_lock(&dsp56k_mutex);
	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:

		अगर (test_and_set_bit(0, &dsp56k.in_use)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		dsp56k.समयout = TIMEOUT;
		dsp56k.maxio = MAXIO;
		dsp56k.rx_wsize = dsp56k.tx_wsize = 4; 

		DSP56K_TX_INT_OFF;
		DSP56K_RX_INT_OFF;

		/* Zero host flags */
		dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_HF0;
		dsp56k_host_पूर्णांकerface.icr &= ~DSP56K_ICR_HF1;

		अवरोध;

	शेष:
		ret = -ENODEV;
	पूर्ण
out:
	mutex_unlock(&dsp56k_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dsp56k_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक dev = iminor(inode) & 0x0f;

	चयन(dev)
	अणु
	हाल DSP56K_DEV_56001:
		clear_bit(0, &dsp56k.in_use);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "DSP56k driver: Unknown minor device: %d\n", dev);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations dsp56k_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= dsp56k_पढ़ो,
	.ग_लिखो		= dsp56k_ग_लिखो,
	.unlocked_ioctl	= dsp56k_ioctl,
	.खोलो		= dsp56k_खोलो,
	.release	= dsp56k_release,
	.llseek		= noop_llseek,
पूर्ण;


/****** Init and module functions ******/

अटल स्थिर अक्षर banner[] __initस्थिर = KERN_INFO "DSP56k driver installed\n";

अटल पूर्णांक __init dsp56k_init_driver(व्योम)
अणु
	पूर्णांक err = 0;

	अगर(!MACH_IS_ATARI || !ATARIHW_PRESENT(DSP56K)) अणु
		prपूर्णांकk("DSP56k driver: Hardware not present\n");
		वापस -ENODEV;
	पूर्ण

	अगर(रेजिस्टर_chrdev(DSP56K_MAJOR, "dsp56k", &dsp56k_fops)) अणु
		prपूर्णांकk("DSP56k driver: Unable to register driver\n");
		वापस -ENODEV;
	पूर्ण
	dsp56k_class = class_create(THIS_MODULE, "dsp56k");
	अगर (IS_ERR(dsp56k_class)) अणु
		err = PTR_ERR(dsp56k_class);
		जाओ out_chrdev;
	पूर्ण
	device_create(dsp56k_class, शून्य, MKDEV(DSP56K_MAJOR, 0), शून्य,
		      "dsp56k");

	prपूर्णांकk(banner);
	जाओ out;

out_chrdev:
	unरेजिस्टर_chrdev(DSP56K_MAJOR, "dsp56k");
out:
	वापस err;
पूर्ण
module_init(dsp56k_init_driver);

अटल व्योम __निकास dsp56k_cleanup_driver(व्योम)
अणु
	device_destroy(dsp56k_class, MKDEV(DSP56K_MAJOR, 0));
	class_destroy(dsp56k_class);
	unरेजिस्टर_chrdev(DSP56K_MAJOR, "dsp56k");
पूर्ण
module_निकास(dsp56k_cleanup_driver);

MODULE_LICENSE("GPL");
MODULE_FIRMWARE("dsp56k/bootstrap.bin");
