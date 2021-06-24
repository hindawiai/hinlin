<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
    AudioScience HPI driver
    Common Linux HPI ioctl and module probe/हटाओ functions

    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


*******************************************************************************/
#घोषणा SOURCEखाता_NAME "hpioctl.c"

#समावेश "hpi_internal.h"
#समावेश "hpi_version.h"
#समावेश "hpimsginit.h"
#समावेश "hpidebug.h"
#समावेश "hpimsgx.h"
#समावेश "hpioctl.h"
#समावेश "hpicmn.h"

#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pci.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/nospec.h>

#अगर_घोषित MODULE_FIRMWARE
MODULE_FIRMWARE("asihpi/dsp5000.bin");
MODULE_FIRMWARE("asihpi/dsp6200.bin");
MODULE_FIRMWARE("asihpi/dsp6205.bin");
MODULE_FIRMWARE("asihpi/dsp6400.bin");
MODULE_FIRMWARE("asihpi/dsp6600.bin");
MODULE_FIRMWARE("asihpi/dsp8700.bin");
MODULE_FIRMWARE("asihpi/dsp8900.bin");
#पूर्ण_अगर

अटल पूर्णांक pपुनः_स्मृति_stream_buf;
module_param(pपुनः_स्मृति_stream_buf, पूर्णांक, 0444);
MODULE_PARM_DESC(pपुनः_स्मृति_stream_buf,
	"Preallocate size for per-adapter stream buffer");

/* Allow the debug level to be changed after module load.
 E.g.   echo 2 > /sys/module/asihpi/parameters/hpiDebugLevel
*/
module_param(hpi_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(hpi_debug_level, "debug verbosity 0..5");

/* List of adapters found */
अटल काष्ठा hpi_adapter adapters[HPI_MAX_ADAPTERS];

/* Wrapper function to HPI_Message to enable dumping of the
   message and response types.
*/
अटल व्योम hpi_send_recv_f(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	काष्ठा file *file)
अणु
	अगर ((phm->adapter_index >= HPI_MAX_ADAPTERS)
		&& (phm->object != HPI_OBJ_SUBSYSTEM))
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
	अन्यथा
		hpi_send_recv_ex(phm, phr, file);
पूर्ण

/* This is called from hpअगरunc.c functions, called by ALSA
 * (or other kernel process) In this हाल there is no file descriptor
 * available क्रम the message cache code
 */
व्योम hpi_send_recv(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	hpi_send_recv_f(phm, phr, HOWNER_KERNEL);
पूर्ण

EXPORT_SYMBOL(hpi_send_recv);
/* क्रम radio-asihpi */

पूर्णांक asihpi_hpi_release(काष्ठा file *file)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

/* HPI_DEBUG_LOG(INFO,"hpi_release file %p, pid %d\n", file, current->pid); */
	/* बंद the subप्रणाली just in हाल the application क्रमgot to. */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_CLOSE);
	hpi_send_recv_ex(&hm, &hr, file);
	वापस 0;
पूर्ण

दीर्घ asihpi_hpi_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hpi_ioctl_linux __user *phpi_ioctl_data;
	व्योम __user *puhm;
	व्योम __user *puhr;
	जोड़ hpi_message_buffer_v1 *hm;
	जोड़ hpi_response_buffer_v1 *hr;
	u16 msg_size;
	u16 res_max_size;
	u32 uncopied_bytes;
	पूर्णांक err = 0;

	अगर (cmd != HPI_IOCTL_LINUX)
		वापस -EINVAL;

	hm = kदो_स्मृति(माप(*hm), GFP_KERNEL);
	hr = kzalloc(माप(*hr), GFP_KERNEL);
	अगर (!hm || !hr) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	phpi_ioctl_data = (काष्ठा hpi_ioctl_linux __user *)arg;

	/* Read the message and response poपूर्णांकers from user space.  */
	अगर (get_user(puhm, &phpi_ioctl_data->phm)
		|| get_user(puhr, &phpi_ioctl_data->phr)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	/* Now पढ़ो the message size and data from user space.  */
	अगर (get_user(msg_size, (u16 __user *)puhm)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (msg_size > माप(*hm))
		msg_size = माप(*hm);

	/* prपूर्णांकk(KERN_INFO "message size %d\n", hm->h.wSize); */

	uncopied_bytes = copy_from_user(hm, puhm, msg_size);
	अगर (uncopied_bytes) अणु
		HPI_DEBUG_LOG(ERROR, "uncopied bytes %d\n", uncopied_bytes);
		err = -EFAULT;
		जाओ out;
	पूर्ण

	/* Override h.size in हाल it is changed between two userspace fetches */
	hm->h.size = msg_size;

	अगर (get_user(res_max_size, (u16 __user *)puhr)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	/* prपूर्णांकk(KERN_INFO "user response size %d\n", res_max_size); */
	अगर (res_max_size < माप(काष्ठा hpi_response_header)) अणु
		HPI_DEBUG_LOG(WARNING, "small res size %d\n", res_max_size);
		err = -EFAULT;
		जाओ out;
	पूर्ण

	res_max_size = min_t(माप_प्रकार, res_max_size, माप(*hr));

	चयन (hm->h.function) अणु
	हाल HPI_SUBSYS_CREATE_ADAPTER:
	हाल HPI_ADAPTER_DELETE:
		/* Application must not use these functions! */
		hr->h.size = माप(hr->h);
		hr->h.error = HPI_ERROR_INVALID_OPERATION;
		hr->h.function = hm->h.function;
		uncopied_bytes = copy_to_user(puhr, hr, hr->h.size);
		अगर (uncopied_bytes)
			err = -EFAULT;
		अन्यथा
			err = 0;
		जाओ out;
	पूर्ण

	hr->h.size = res_max_size;
	अगर (hm->h.object == HPI_OBJ_SUBSYSTEM) अणु
		hpi_send_recv_f(&hm->m0, &hr->r0, file);
	पूर्ण अन्यथा अणु
		u16 __user *ptr = शून्य;
		u32 size = 0;
		/* -1=no data 0=पढ़ो from user mem, 1=ग_लिखो to user mem */
		पूर्णांक wrflag = -1;
		काष्ठा hpi_adapter *pa = शून्य;

		अगर (hm->h.adapter_index < ARRAY_SIZE(adapters))
			pa = &adapters[array_index_nospec(hm->h.adapter_index,
							  ARRAY_SIZE(adapters))];

		अगर (!pa || !pa->adapter || !pa->adapter->type) अणु
			hpi_init_response(&hr->r0, hm->h.object,
				hm->h.function, HPI_ERROR_BAD_ADAPTER_NUMBER);

			uncopied_bytes =
				copy_to_user(puhr, hr, माप(hr->h));
			अगर (uncopied_bytes)
				err = -EFAULT;
			अन्यथा
				err = 0;
			जाओ out;
		पूर्ण

		अगर (mutex_lock_पूर्णांकerruptible(&pa->mutex)) अणु
			err = -EINTR;
			जाओ out;
		पूर्ण

		/* Dig out any poपूर्णांकers embedded in the message.  */
		चयन (hm->h.function) अणु
		हाल HPI_OSTREAM_WRITE:
		हाल HPI_ISTREAM_READ:अणु
				/* Yes, sparse, this is correct. */
				ptr = (u16 __user *)hm->m0.u.d.u.data.pb_data;
				size = hm->m0.u.d.u.data.data_size;

				/* Allocate buffer according to application request.
				   ?Is it better to alloc/मुक्त क्रम the duration
				   of the transaction?
				 */
				अगर (pa->buffer_size < size) अणु
					HPI_DEBUG_LOG(DEBUG,
						"Realloc adapter %d stream "
						"buffer from %zd to %d\n",
						hm->h.adapter_index,
						pa->buffer_size, size);
					अगर (pa->p_buffer) अणु
						pa->buffer_size = 0;
						vमुक्त(pa->p_buffer);
					पूर्ण
					pa->p_buffer = vदो_स्मृति(size);
					अगर (pa->p_buffer)
						pa->buffer_size = size;
					अन्यथा अणु
						HPI_DEBUG_LOG(ERROR,
							"HPI could not allocate "
							"stream buffer size %d\n",
							size);

						mutex_unlock(&pa->mutex);
						err = -EINVAL;
						जाओ out;
					पूर्ण
				पूर्ण

				hm->m0.u.d.u.data.pb_data = pa->p_buffer;
				अगर (hm->h.function == HPI_ISTREAM_READ)
					/* from card, WRITE to user mem */
					wrflag = 1;
				अन्यथा
					wrflag = 0;
				अवरोध;
			पूर्ण

		शेष:
			size = 0;
			अवरोध;
		पूर्ण

		अगर (size && (wrflag == 0)) अणु
			uncopied_bytes =
				copy_from_user(pa->p_buffer, ptr, size);
			अगर (uncopied_bytes)
				HPI_DEBUG_LOG(WARNING,
					"Missed %d of %d "
					"bytes from user\n", uncopied_bytes,
					size);
		पूर्ण

		hpi_send_recv_f(&hm->m0, &hr->r0, file);

		अगर (size && (wrflag == 1)) अणु
			uncopied_bytes =
				copy_to_user(ptr, pa->p_buffer, size);
			अगर (uncopied_bytes)
				HPI_DEBUG_LOG(WARNING,
					"Missed %d of %d " "bytes to user\n",
					uncopied_bytes, size);
		पूर्ण

		mutex_unlock(&pa->mutex);
	पूर्ण

	/* on वापस response size must be set */
	/*prपूर्णांकk(KERN_INFO "response size %d\n", hr->h.wSize); */

	अगर (!hr->h.size) अणु
		HPI_DEBUG_LOG(ERROR, "response zero size\n");
		err = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (hr->h.size > res_max_size) अणु
		HPI_DEBUG_LOG(ERROR, "response too big %d %d\n", hr->h.size,
			res_max_size);
		hr->h.error = HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;
		hr->h.specअगरic_error = hr->h.size;
		hr->h.size = माप(hr->h);
	पूर्ण

	uncopied_bytes = copy_to_user(puhr, hr, hr->h.size);
	अगर (uncopied_bytes) अणु
		HPI_DEBUG_LOG(ERROR, "uncopied bytes %d\n", uncopied_bytes);
		err = -EFAULT;
		जाओ out;
	पूर्ण

out:
	kमुक्त(hm);
	kमुक्त(hr);
	वापस err;
पूर्ण

अटल पूर्णांक asihpi_irq_count;

अटल irqवापस_t asihpi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hpi_adapter *a = dev_id;
	पूर्णांक handled;

	अगर (!a->adapter->irq_query_and_clear) अणु
		pr_err("asihpi_isr ASI%04X:%d no handler\n", a->adapter->type,
			a->adapter->index);
		वापस IRQ_NONE;
	पूर्ण

	handled = a->adapter->irq_query_and_clear(a->adapter, 0);

	अगर (!handled)
		वापस IRQ_NONE;

	asihpi_irq_count++;
	/* prपूर्णांकk(KERN_INFO "asihpi_isr %d ASI%04X:%d irq handled\n",
	   asihpi_irq_count, a->adapter->type, a->adapter->index); */

	अगर (a->पूर्णांकerrupt_callback)
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t asihpi_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hpi_adapter *a = dev_id;

	अगर (a->पूर्णांकerrupt_callback)
		a->पूर्णांकerrupt_callback(a);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक asihpi_adapter_probe(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक idx, nm, low_latency_mode = 0, irq_supported = 0;
	पूर्णांक adapter_index;
	अचिन्हित पूर्णांक memlen;
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	काष्ठा hpi_adapter adapter;
	काष्ठा hpi_pci pci = अणु 0 पूर्ण;

	स_रखो(&adapter, 0, माप(adapter));

	dev_prपूर्णांकk(KERN_DEBUG, &pci_dev->dev,
		"probe %04x:%04x,%04x:%04x,%04x\n", pci_dev->venकरोr,
		pci_dev->device, pci_dev->subप्रणाली_venकरोr,
		pci_dev->subप्रणाली_device, pci_dev->devfn);

	अगर (pci_enable_device(pci_dev) < 0) अणु
		dev_err(&pci_dev->dev,
			"pci_enable_device failed, disabling device\n");
		वापस -EIO;
	पूर्ण

	pci_set_master(pci_dev);	/* also sets latency समयr अगर < 16 */

	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_CREATE_ADAPTER);
	hpi_init_response(&hr, HPI_OBJ_SUBSYSTEM, HPI_SUBSYS_CREATE_ADAPTER,
		HPI_ERROR_PROCESSING_MESSAGE);

	hm.adapter_index = HPI_ADAPTER_INDEX_INVALID;

	nm = HPI_MAX_ADAPTER_MEM_SPACES;

	क्रम (idx = 0; idx < nm; idx++) अणु
		HPI_DEBUG_LOG(INFO, "resource %d %pR\n", idx,
			&pci_dev->resource[idx]);

		अगर (pci_resource_flags(pci_dev, idx) & IORESOURCE_MEM) अणु
			memlen = pci_resource_len(pci_dev, idx);
			pci.ap_mem_base[idx] =
				ioremap(pci_resource_start(pci_dev, idx),
				memlen);
			अगर (!pci.ap_mem_base[idx]) अणु
				HPI_DEBUG_LOG(ERROR,
					"ioremap failed, aborting\n");
				/* unmap previously mapped pci mem space */
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	pci.pci_dev = pci_dev;
	hm.u.s.resource.bus_type = HPI_BUS_PCI;
	hm.u.s.resource.r.pci = &pci;

	/* call CreateAdapterObject on the relevant hpi module */
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);
	अगर (hr.error)
		जाओ err;

	adapter_index = hr.u.s.adapter_index;
	adapter.adapter = hpi_find_adapter(adapter_index);

	अगर (pपुनः_स्मृति_stream_buf) अणु
		adapter.p_buffer = vदो_स्मृति(pपुनः_स्मृति_stream_buf);
		अगर (!adapter.p_buffer) अणु
			HPI_DEBUG_LOG(ERROR,
				"HPI could not allocate "
				"kernel buffer size %d\n",
				pपुनः_स्मृति_stream_buf);
			जाओ err;
		पूर्ण
	पूर्ण

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_OPEN);
	hm.adapter_index = adapter.adapter->index;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	अगर (hr.error) अणु
		HPI_DEBUG_LOG(ERROR, "HPI_ADAPTER_OPEN failed, aborting\n");
		जाओ err;
	पूर्ण

	/* Check अगर current mode == Low Latency mode */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_MODE);
	hm.adapter_index = adapter.adapter->index;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	अगर (!hr.error
		&& hr.u.ax.mode.adapter_mode == HPI_ADAPTER_MODE_LOW_LATENCY)
		low_latency_mode = 1;
	अन्यथा
		dev_info(&pci_dev->dev,
			"Adapter at index %d is not in low latency mode\n",
			adapter.adapter->index);

	/* Check अगर IRQs are supported */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_PROPERTY);
	hm.adapter_index = adapter.adapter->index;
	hm.u.ax.property_set.property = HPI_ADAPTER_PROPERTY_SUPPORTS_IRQ;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);
	अगर (hr.error || !hr.u.ax.property_get.parameter1) अणु
		dev_info(&pci_dev->dev,
			"IRQs not supported by adapter at index %d\n",
			adapter.adapter->index);
	पूर्ण अन्यथा अणु
		irq_supported = 1;
	पूर्ण

	/* WARNING can't init mutex in 'adapter'
	 * and then copy it to adapters[] ?!?!
	 */
	adapters[adapter_index] = adapter;
	mutex_init(&adapters[adapter_index].mutex);
	pci_set_drvdata(pci_dev, &adapters[adapter_index]);

	अगर (low_latency_mode && irq_supported) अणु
		अगर (!adapter.adapter->irq_query_and_clear) अणु
			dev_err(&pci_dev->dev,
				"no IRQ handler for adapter %d, aborting\n",
				adapter.adapter->index);
			जाओ err;
		पूर्ण

		/* Disable IRQ generation on DSP side by setting the rate to 0 */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
			HPI_ADAPTER_SET_PROPERTY);
		hm.adapter_index = adapter.adapter->index;
		hm.u.ax.property_set.property = HPI_ADAPTER_PROPERTY_IRQ_RATE;
		hm.u.ax.property_set.parameter1 = 0;
		hm.u.ax.property_set.parameter2 = 0;
		hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);
		अगर (hr.error) अणु
			HPI_DEBUG_LOG(ERROR,
				"HPI_ADAPTER_GET_MODE failed, aborting\n");
			जाओ err;
		पूर्ण

		/* Note: request_irq calls asihpi_isr here */
		अगर (request_thपढ़ोed_irq(pci_dev->irq, asihpi_isr,
					 asihpi_isr_thपढ़ो, IRQF_SHARED,
					 "asihpi", &adapters[adapter_index])) अणु
			dev_err(&pci_dev->dev, "request_irq(%d) failed\n",
				pci_dev->irq);
			जाओ err;
		पूर्ण

		adapters[adapter_index].पूर्णांकerrupt_mode = 1;

		dev_info(&pci_dev->dev, "using irq %d\n", pci_dev->irq);
		adapters[adapter_index].irq = pci_dev->irq;
	पूर्ण अन्यथा अणु
		dev_info(&pci_dev->dev, "using polled mode\n");
	पूर्ण

	dev_info(&pci_dev->dev, "probe succeeded for ASI%04X HPI index %d\n",
		 adapter.adapter->type, adapter_index);

	वापस 0;

err:
	जबतक (--idx >= 0) अणु
		अगर (pci.ap_mem_base[idx]) अणु
			iounmap(pci.ap_mem_base[idx]);
			pci.ap_mem_base[idx] = शून्य;
		पूर्ण
	पूर्ण

	अगर (adapter.p_buffer) अणु
		adapter.buffer_size = 0;
		vमुक्त(adapter.p_buffer);
	पूर्ण

	HPI_DEBUG_LOG(ERROR, "adapter_probe failed\n");
	वापस -ENODEV;
पूर्ण

व्योम asihpi_adapter_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक idx;
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	काष्ठा hpi_adapter *pa;
	काष्ठा hpi_pci pci;

	pa = pci_get_drvdata(pci_dev);
	pci = pa->adapter->pci;

	/* Disable IRQ generation on DSP side */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_SET_PROPERTY);
	hm.adapter_index = pa->adapter->index;
	hm.u.ax.property_set.property = HPI_ADAPTER_PROPERTY_IRQ_RATE;
	hm.u.ax.property_set.parameter1 = 0;
	hm.u.ax.property_set.parameter2 = 0;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_DELETE);
	hm.adapter_index = pa->adapter->index;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	/* unmap PCI memory space, mapped during device init. */
	क्रम (idx = 0; idx < HPI_MAX_ADAPTER_MEM_SPACES; ++idx)
		iounmap(pci.ap_mem_base[idx]);

	अगर (pa->irq)
		मुक्त_irq(pa->irq, pa);

	vमुक्त(pa->p_buffer);

	अगर (1)
		dev_info(&pci_dev->dev,
			 "remove %04x:%04x,%04x:%04x,%04x, HPI index %d\n",
			 pci_dev->venकरोr, pci_dev->device,
			 pci_dev->subप्रणाली_venकरोr, pci_dev->subप्रणाली_device,
			 pci_dev->devfn, pa->adapter->index);

	स_रखो(pa, 0, माप(*pa));
पूर्ण

व्योम __init asihpi_init(व्योम)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	स_रखो(adapters, 0, माप(adapters));

	prपूर्णांकk(KERN_INFO "ASIHPI driver " HPI_VER_STRING "\n");

	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_DRIVER_LOAD);
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);
पूर्ण

व्योम asihpi_निकास(व्योम)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_DRIVER_UNLOAD);
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);
पूर्ण
