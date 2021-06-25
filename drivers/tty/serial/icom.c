<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
  * icom.c
  *
  * Copyright (C) 2001 IBM Corporation. All rights reserved.
  *
  * Serial device driver.
  *
  * Based on code from serial.c
  */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/termios.h>
#समावेश <linux/fs.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/firmware.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "icom.h"

/*#घोषणा ICOM_TRACE		 enable port trace capabilities */

#घोषणा ICOM_DRIVER_NAME "icom"
#घोषणा ICOM_VERSION_STR "1.3.1"
#घोषणा NR_PORTS	       128
#घोषणा ICOM_PORT ((काष्ठा icom_port *)port)
#घोषणा to_icom_adapter(d) container_of(d, काष्ठा icom_adapter, kref)

अटल स्थिर काष्ठा pci_device_id icom_pci_table[] = अणु
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.device = PCI_DEVICE_ID_IBM_ICOM_DEV_ID_1,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.driver_data = ADAPTER_V1,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.device = PCI_DEVICE_ID_IBM_ICOM_DEV_ID_2,
		.subvenकरोr = PCI_VENDOR_ID_IBM,
		.subdevice = PCI_DEVICE_ID_IBM_ICOM_V2_TWO_PORTS_RVX,
		.driver_data = ADAPTER_V2,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.device = PCI_DEVICE_ID_IBM_ICOM_DEV_ID_2,
		.subvenकरोr = PCI_VENDOR_ID_IBM,
		.subdevice = PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM,
		.driver_data = ADAPTER_V2,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.device = PCI_DEVICE_ID_IBM_ICOM_DEV_ID_2,
		.subvenकरोr = PCI_VENDOR_ID_IBM,
		.subdevice = PCI_DEVICE_ID_IBM_ICOM_FOUR_PORT_MODEL,
		.driver_data = ADAPTER_V2,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.device = PCI_DEVICE_ID_IBM_ICOM_DEV_ID_2,
		.subvenकरोr = PCI_VENDOR_ID_IBM,
		.subdevice = PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM_PCIE,
		.driver_data = ADAPTER_V2,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा lookup_proc_table start_proc[4] = अणु
	अणुशून्य, ICOM_CONTROL_START_Aपूर्ण,
	अणुशून्य, ICOM_CONTROL_START_Bपूर्ण,
	अणुशून्य, ICOM_CONTROL_START_Cपूर्ण,
	अणुशून्य, ICOM_CONTROL_START_Dपूर्ण
पूर्ण;


अटल काष्ठा lookup_proc_table stop_proc[4] = अणु
	अणुशून्य, ICOM_CONTROL_STOP_Aपूर्ण,
	अणुशून्य, ICOM_CONTROL_STOP_Bपूर्ण,
	अणुशून्य, ICOM_CONTROL_STOP_Cपूर्ण,
	अणुशून्य, ICOM_CONTROL_STOP_Dपूर्ण
पूर्ण;

अटल काष्ठा lookup_पूर्णांक_table पूर्णांक_mask_tbl[4] = अणु
	अणुशून्य, ICOM_INT_MASK_PRC_Aपूर्ण,
	अणुशून्य, ICOM_INT_MASK_PRC_Bपूर्ण,
	अणुशून्य, ICOM_INT_MASK_PRC_Cपूर्ण,
	अणुशून्य, ICOM_INT_MASK_PRC_Dपूर्ण,
पूर्ण;


MODULE_DEVICE_TABLE(pci, icom_pci_table);

अटल LIST_HEAD(icom_adapter_head);

/* spinlock क्रम adapter initialization and changing adapter operations */
अटल DEFINE_SPINLOCK(icom_lock);

#अगर_घोषित ICOM_TRACE
अटल अंतरभूत व्योम trace(काष्ठा icom_port *icom_port, अक्षर *trace_pt,
			अचिन्हित दीर्घ trace_data)
अणु
	dev_info(&icom_port->adapter->pci_dev->dev, ":%d:%s - %lx\n",
	icom_port->port, trace_pt, trace_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम trace(काष्ठा icom_port *icom_port, अक्षर *trace_pt, अचिन्हित दीर्घ trace_data) अणुपूर्ण;
#पूर्ण_अगर
अटल व्योम icom_kref_release(काष्ठा kref *kref);

अटल व्योम मुक्त_port_memory(काष्ठा icom_port *icom_port)
अणु
	काष्ठा pci_dev *dev = icom_port->adapter->pci_dev;

	trace(icom_port, "RET_PORT_MEM", 0);
	अगर (icom_port->recv_buf) अणु
		dma_मुक्त_coherent(&dev->dev, 4096, icom_port->recv_buf,
				  icom_port->recv_buf_pci);
		icom_port->recv_buf = शून्य;
	पूर्ण
	अगर (icom_port->xmit_buf) अणु
		dma_मुक्त_coherent(&dev->dev, 4096, icom_port->xmit_buf,
				  icom_port->xmit_buf_pci);
		icom_port->xmit_buf = शून्य;
	पूर्ण
	अगर (icom_port->statStg) अणु
		dma_मुक्त_coherent(&dev->dev, 4096, icom_port->statStg,
				  icom_port->statStg_pci);
		icom_port->statStg = शून्य;
	पूर्ण

	अगर (icom_port->xmitRestart) अणु
		dma_मुक्त_coherent(&dev->dev, 4096, icom_port->xmitRestart,
				  icom_port->xmitRestart_pci);
		icom_port->xmitRestart = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक get_port_memory(काष्ठा icom_port *icom_port)
अणु
	पूर्णांक index;
	अचिन्हित दीर्घ stgAddr;
	अचिन्हित दीर्घ startStgAddr;
	अचिन्हित दीर्घ offset;
	काष्ठा pci_dev *dev = icom_port->adapter->pci_dev;

	icom_port->xmit_buf =
	    dma_alloc_coherent(&dev->dev, 4096, &icom_port->xmit_buf_pci,
			       GFP_KERNEL);
	अगर (!icom_port->xmit_buf) अणु
		dev_err(&dev->dev, "Can not allocate Transmit buffer\n");
		वापस -ENOMEM;
	पूर्ण

	trace(icom_port, "GET_PORT_MEM",
	      (अचिन्हित दीर्घ) icom_port->xmit_buf);

	icom_port->recv_buf =
	    dma_alloc_coherent(&dev->dev, 4096, &icom_port->recv_buf_pci,
			       GFP_KERNEL);
	अगर (!icom_port->recv_buf) अणु
		dev_err(&dev->dev, "Can not allocate Receive buffer\n");
		मुक्त_port_memory(icom_port);
		वापस -ENOMEM;
	पूर्ण
	trace(icom_port, "GET_PORT_MEM",
	      (अचिन्हित दीर्घ) icom_port->recv_buf);

	icom_port->statStg =
	    dma_alloc_coherent(&dev->dev, 4096, &icom_port->statStg_pci,
			       GFP_KERNEL);
	अगर (!icom_port->statStg) अणु
		dev_err(&dev->dev, "Can not allocate Status buffer\n");
		मुक्त_port_memory(icom_port);
		वापस -ENOMEM;
	पूर्ण
	trace(icom_port, "GET_PORT_MEM",
	      (अचिन्हित दीर्घ) icom_port->statStg);

	icom_port->xmitRestart =
	    dma_alloc_coherent(&dev->dev, 4096, &icom_port->xmitRestart_pci,
			       GFP_KERNEL);
	अगर (!icom_port->xmitRestart) अणु
		dev_err(&dev->dev,
			"Can not allocate xmit Restart buffer\n");
		मुक्त_port_memory(icom_port);
		वापस -ENOMEM;
	पूर्ण

	/* FODs: Frame Out Descriptor Queue, this is a FIFO queue that
           indicates that frames are to be transmitted
	*/

	stgAddr = (अचिन्हित दीर्घ) icom_port->statStg;
	क्रम (index = 0; index < NUM_XBUFFS; index++) अणु
		trace(icom_port, "FOD_ADDR", stgAddr);
		stgAddr = stgAddr + माप(icom_port->statStg->xmit[0]);
		अगर (index < (NUM_XBUFFS - 1)) अणु
			स_रखो(&icom_port->statStg->xmit[index], 0, माप(काष्ठा xmit_status_area));
			icom_port->statStg->xmit[index].leLengthASD =
			    (अचिन्हित लघु पूर्णांक) cpu_to_le16(XMIT_BUFF_SZ);
			trace(icom_port, "FOD_ADDR", stgAddr);
			trace(icom_port, "FOD_XBUFF",
			      (अचिन्हित दीर्घ) icom_port->xmit_buf);
			icom_port->statStg->xmit[index].leBuffer =
			    cpu_to_le32(icom_port->xmit_buf_pci);
		पूर्ण अन्यथा अगर (index == (NUM_XBUFFS - 1)) अणु
			स_रखो(&icom_port->statStg->xmit[index], 0, माप(काष्ठा xmit_status_area));
			icom_port->statStg->xmit[index].leLengthASD =
			    (अचिन्हित लघु पूर्णांक) cpu_to_le16(XMIT_BUFF_SZ);
			trace(icom_port, "FOD_XBUFF",
			      (अचिन्हित दीर्घ) icom_port->xmit_buf);
			icom_port->statStg->xmit[index].leBuffer =
			    cpu_to_le32(icom_port->xmit_buf_pci);
		पूर्ण अन्यथा अणु
			स_रखो(&icom_port->statStg->xmit[index], 0, माप(काष्ठा xmit_status_area));
		पूर्ण
	पूर्ण
	/* FIDs */
	startStgAddr = stgAddr;

	/* fill in every entry, even अगर no buffer */
	क्रम (index = 0; index <  NUM_RBUFFS; index++) अणु
		trace(icom_port, "FID_ADDR", stgAddr);
		stgAddr = stgAddr + माप(icom_port->statStg->rcv[0]);
		icom_port->statStg->rcv[index].leLength = 0;
		icom_port->statStg->rcv[index].WorkingLength =
		    (अचिन्हित लघु पूर्णांक) cpu_to_le16(RCV_BUFF_SZ);
		अगर (index < (NUM_RBUFFS - 1) ) अणु
			offset = stgAddr - (अचिन्हित दीर्घ) icom_port->statStg;
			icom_port->statStg->rcv[index].leNext =
			      cpu_to_le32(icom_port-> statStg_pci + offset);
			trace(icom_port, "FID_RBUFF",
			      (अचिन्हित दीर्घ) icom_port->recv_buf);
			icom_port->statStg->rcv[index].leBuffer =
			    cpu_to_le32(icom_port->recv_buf_pci);
		पूर्ण अन्यथा अगर (index == (NUM_RBUFFS -1) ) अणु
			offset = startStgAddr - (अचिन्हित दीर्घ) icom_port->statStg;
			icom_port->statStg->rcv[index].leNext =
			    cpu_to_le32(icom_port-> statStg_pci + offset);
			trace(icom_port, "FID_RBUFF",
			      (अचिन्हित दीर्घ) icom_port->recv_buf + 2048);
			icom_port->statStg->rcv[index].leBuffer =
			    cpu_to_le32(icom_port->recv_buf_pci + 2048);
		पूर्ण अन्यथा अणु
			icom_port->statStg->rcv[index].leNext = 0;
			icom_port->statStg->rcv[index].leBuffer = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stop_processor(काष्ठा icom_port *icom_port)
अणु
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ flags;
	पूर्णांक port;

	spin_lock_irqsave(&icom_lock, flags);

	port = icom_port->port;
	अगर (port >= ARRAY_SIZE(stop_proc)) अणु
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Invalid port assignment\n");
		जाओ unlock;
	पूर्ण

	अगर (port == 0 || port == 1)
		stop_proc[port].global_control_reg = &icom_port->global_reg->control;
	अन्यथा
		stop_proc[port].global_control_reg = &icom_port->global_reg->control_2;

	temp = पढ़ोl(stop_proc[port].global_control_reg);
	temp = (temp & ~start_proc[port].processor_id) | stop_proc[port].processor_id;
	ग_लिखोl(temp, stop_proc[port].global_control_reg);

	/* ग_लिखो flush */
	पढ़ोl(stop_proc[port].global_control_reg);

unlock:
	spin_unlock_irqrestore(&icom_lock, flags);
पूर्ण

अटल व्योम start_processor(काष्ठा icom_port *icom_port)
अणु
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ flags;
	पूर्णांक port;

	spin_lock_irqsave(&icom_lock, flags);

	port = icom_port->port;
	अगर (port >= ARRAY_SIZE(start_proc)) अणु
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Invalid port assignment\n");
		जाओ unlock;
	पूर्ण

	अगर (port == 0 || port == 1)
		start_proc[port].global_control_reg = &icom_port->global_reg->control;
	अन्यथा
		start_proc[port].global_control_reg = &icom_port->global_reg->control_2;

	temp = पढ़ोl(start_proc[port].global_control_reg);
	temp = (temp & ~stop_proc[port].processor_id) | start_proc[port].processor_id;
	ग_लिखोl(temp, start_proc[port].global_control_reg);

	/* ग_लिखो flush */
	पढ़ोl(start_proc[port].global_control_reg);

unlock:
	spin_unlock_irqrestore(&icom_lock, flags);
पूर्ण

अटल व्योम load_code(काष्ठा icom_port *icom_port)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर __iomem *iram_ptr;
	पूर्णांक index;
	पूर्णांक status = 0;
	व्योम __iomem *dram_ptr = icom_port->dram;
	dma_addr_t temp_pci;
	अचिन्हित अक्षर *new_page = शून्य;
	अचिन्हित अक्षर cable_id = NO_CABLE;
	काष्ठा pci_dev *dev = icom_port->adapter->pci_dev;

	/* Clear out any pending पूर्णांकerrupts */
	ग_लिखोw(0x3FFF, icom_port->पूर्णांक_reg);

	trace(icom_port, "CLEAR_INTERRUPTS", 0);

	/* Stop processor */
	stop_processor(icom_port);

	/* Zero out DRAM */
	स_रखो_io(dram_ptr, 0, 512);

	/* Load Call Setup पूर्णांकo Adapter */
	अगर (request_firmware(&fw, "icom_call_setup.bin", &dev->dev) < 0) अणु
		dev_err(&dev->dev,"Unable to load icom_call_setup.bin firmware image\n");
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	अगर (fw->size > ICOM_DCE_IRAM_OFFSET) अणु
		dev_err(&dev->dev, "Invalid firmware image for icom_call_setup.bin found.\n");
		release_firmware(fw);
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	iram_ptr = (अक्षर __iomem *)icom_port->dram + ICOM_IRAM_OFFSET;
	क्रम (index = 0; index < fw->size; index++)
		ग_लिखोb(fw->data[index], &iram_ptr[index]);

	release_firmware(fw);

	/* Load Resident DCE portion of Adapter */
	अगर (request_firmware(&fw, "icom_res_dce.bin", &dev->dev) < 0) अणु
		dev_err(&dev->dev,"Unable to load icom_res_dce.bin firmware image\n");
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	अगर (fw->size > ICOM_IRAM_SIZE) अणु
		dev_err(&dev->dev, "Invalid firmware image for icom_res_dce.bin found.\n");
		release_firmware(fw);
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	iram_ptr = (अक्षर __iomem *) icom_port->dram + ICOM_IRAM_OFFSET;
	क्रम (index = ICOM_DCE_IRAM_OFFSET; index < fw->size; index++)
		ग_लिखोb(fw->data[index], &iram_ptr[index]);

	release_firmware(fw);

	/* Set Hardware level */
	अगर (icom_port->adapter->version == ADAPTER_V2)
		ग_लिखोb(V2_HARDWARE, &(icom_port->dram->misc_flags));

	/* Start the processor in Adapter */
	start_processor(icom_port);

	ग_लिखोb((HDLC_PPP_PURE_ASYNC | HDLC_FF_FILL),
	       &(icom_port->dram->HDLCConfigReg));
	ग_लिखोb(0x04, &(icom_port->dram->FlagFillIdleTimer));	/* 0.5 seconds */
	ग_लिखोb(0x00, &(icom_port->dram->CmdReg));
	ग_लिखोb(0x10, &(icom_port->dram->async_config3));
	ग_लिखोb((ICOM_ACFG_DRIVE1 | ICOM_ACFG_NO_PARITY | ICOM_ACFG_8BPC |
		ICOM_ACFG_1STOP_BIT), &(icom_port->dram->async_config2));

	/*Set up data in icom DRAM to indicate where personality
	 *code is located and its length.
	 */
	new_page = dma_alloc_coherent(&dev->dev, 4096, &temp_pci, GFP_KERNEL);

	अगर (!new_page) अणु
		dev_err(&dev->dev, "Can not allocate DMA buffer\n");
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	अगर (request_firmware(&fw, "icom_asc.bin", &dev->dev) < 0) अणु
		dev_err(&dev->dev,"Unable to load icom_asc.bin firmware image\n");
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	अगर (fw->size > ICOM_DCE_IRAM_OFFSET) अणु
		dev_err(&dev->dev, "Invalid firmware image for icom_asc.bin found.\n");
		release_firmware(fw);
		status = -1;
		जाओ load_code_निकास;
	पूर्ण

	क्रम (index = 0; index < fw->size; index++)
		new_page[index] = fw->data[index];

	ग_लिखोb((अक्षर) ((fw->size + 16)/16), &icom_port->dram->mac_length);
	ग_लिखोl(temp_pci, &icom_port->dram->mac_load_addr);

	release_firmware(fw);

	/*Setting the syncReg to 0x80 causes adapter to start करोwnloading
	   the personality code पूर्णांकo adapter inकाष्ठाion RAM.
	   Once code is loaded, it will begin executing and, based on
	   inक्रमmation provided above, will start DMAing data from
	   shared memory to adapter DRAM.
	 */
	/* the रुको loop below verअगरies this ग_लिखो operation has been करोne
	   and processed
	*/
	ग_लिखोb(START_DOWNLOAD, &icom_port->dram->sync);

	/* Wait max 1 Sec क्रम data करोwnload and processor to start */
	क्रम (index = 0; index < 10; index++) अणु
		msleep(100);
		अगर (पढ़ोb(&icom_port->dram->misc_flags) & ICOM_HDW_ACTIVE)
			अवरोध;
	पूर्ण

	अगर (index == 10)
		status = -1;

	/*
	 * check Cable ID
	 */
	cable_id = पढ़ोb(&icom_port->dram->cable_id);

	अगर (cable_id & ICOM_CABLE_ID_VALID) अणु
		/* Get cable ID पूर्णांकo the lower 4 bits (standard क्रमm) */
		cable_id = (cable_id & ICOM_CABLE_ID_MASK) >> 4;
		icom_port->cable_id = cable_id;
	पूर्ण अन्यथा अणु
		dev_err(&dev->dev,"Invalid or no cable attached\n");
		icom_port->cable_id = NO_CABLE;
	पूर्ण

      load_code_निकास:

	अगर (status != 0) अणु
		/* Clear out any pending पूर्णांकerrupts */
		ग_लिखोw(0x3FFF, icom_port->पूर्णांक_reg);

		/* Turn off port */
		ग_लिखोb(ICOM_DISABLE, &(icom_port->dram->disable));

		/* Stop processor */
		stop_processor(icom_port);

		dev_err(&icom_port->adapter->pci_dev->dev,"Port not operational\n");
	पूर्ण

	अगर (new_page != शून्य)
		dma_मुक्त_coherent(&dev->dev, 4096, new_page, temp_pci);
पूर्ण

अटल पूर्णांक startup(काष्ठा icom_port *icom_port)
अणु
	अचिन्हित दीर्घ temp;
	अचिन्हित अक्षर cable_id, raw_cable_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक port;

	trace(icom_port, "STARTUP", 0);

	अगर (!icom_port->dram) अणु
		/* should NEVER be शून्य */
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Unusable Port, port configuration missing\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * check Cable ID
	 */
	raw_cable_id = पढ़ोb(&icom_port->dram->cable_id);
	trace(icom_port, "CABLE_ID", raw_cable_id);

	/* Get cable ID पूर्णांकo the lower 4 bits (standard क्रमm) */
	cable_id = (raw_cable_id & ICOM_CABLE_ID_MASK) >> 4;

	/* Check क्रम valid Cable ID */
	अगर (!(raw_cable_id & ICOM_CABLE_ID_VALID) ||
	    (cable_id != icom_port->cable_id)) अणु

		/* reload adapter code, pick up any potential changes in cable id */
		load_code(icom_port);

		/* still no sign of cable, error out */
		raw_cable_id = पढ़ोb(&icom_port->dram->cable_id);
		cable_id = (raw_cable_id & ICOM_CABLE_ID_MASK) >> 4;
		अगर (!(raw_cable_id & ICOM_CABLE_ID_VALID) ||
		    (icom_port->cable_id == NO_CABLE))
			वापस -EIO;
	पूर्ण

	/*
	 * Finally, clear and  enable पूर्णांकerrupts
	 */
	spin_lock_irqsave(&icom_lock, flags);
	port = icom_port->port;
	अगर (port >= ARRAY_SIZE(पूर्णांक_mask_tbl)) अणु
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Invalid port assignment\n");
		जाओ unlock;
	पूर्ण

	अगर (port == 0 || port == 1)
		पूर्णांक_mask_tbl[port].global_पूर्णांक_mask = &icom_port->global_reg->पूर्णांक_mask;
	अन्यथा
		पूर्णांक_mask_tbl[port].global_पूर्णांक_mask = &icom_port->global_reg->पूर्णांक_mask_2;

	अगर (port == 0 || port == 2)
		ग_लिखोw(0x00FF, icom_port->पूर्णांक_reg);
	अन्यथा
		ग_लिखोw(0x3F00, icom_port->पूर्णांक_reg);

	temp = पढ़ोl(पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);
	ग_लिखोl(temp & ~पूर्णांक_mask_tbl[port].processor_id, पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);

	/* ग_लिखो flush */
	पढ़ोl(पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);

unlock:
	spin_unlock_irqrestore(&icom_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम shutकरोwn(काष्ठा icom_port *icom_port)
अणु
	अचिन्हित दीर्घ temp;
	अचिन्हित अक्षर cmdReg;
	अचिन्हित दीर्घ flags;
	पूर्णांक port;

	spin_lock_irqsave(&icom_lock, flags);
	trace(icom_port, "SHUTDOWN", 0);

	/*
	 * disable all पूर्णांकerrupts
	 */
	port = icom_port->port;
	अगर (port >= ARRAY_SIZE(पूर्णांक_mask_tbl)) अणु
		dev_err(&icom_port->adapter->pci_dev->dev,
			"Invalid port assignment\n");
		जाओ unlock;
	पूर्ण
	अगर (port == 0 || port == 1)
		पूर्णांक_mask_tbl[port].global_पूर्णांक_mask = &icom_port->global_reg->पूर्णांक_mask;
	अन्यथा
		पूर्णांक_mask_tbl[port].global_पूर्णांक_mask = &icom_port->global_reg->पूर्णांक_mask_2;

	temp = पढ़ोl(पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);
	ग_लिखोl(temp | पूर्णांक_mask_tbl[port].processor_id, पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);

	/* ग_लिखो flush */
	पढ़ोl(पूर्णांक_mask_tbl[port].global_पूर्णांक_mask);

unlock:
	spin_unlock_irqrestore(&icom_lock, flags);

	/*
	 * disable अवरोध condition
	 */
	cmdReg = पढ़ोb(&icom_port->dram->CmdReg);
	अगर (cmdReg & CMD_SND_BREAK) अणु
		ग_लिखोb(cmdReg & ~CMD_SND_BREAK, &icom_port->dram->CmdReg);
	पूर्ण
पूर्ण

अटल पूर्णांक icom_ग_लिखो(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ data_count;
	अचिन्हित अक्षर cmdReg;
	अचिन्हित दीर्घ offset;
	पूर्णांक temp_tail = port->state->xmit.tail;

	trace(ICOM_PORT, "WRITE", 0);

	अगर (cpu_to_le16(ICOM_PORT->statStg->xmit[0].flags) &
	    SA_FLAGS_READY_TO_XMIT) अणु
		trace(ICOM_PORT, "WRITE_FULL", 0);
		वापस 0;
	पूर्ण

	data_count = 0;
	जबतक ((port->state->xmit.head != temp_tail) &&
	       (data_count <= XMIT_BUFF_SZ)) अणु

		ICOM_PORT->xmit_buf[data_count++] =
		    port->state->xmit.buf[temp_tail];

		temp_tail++;
		temp_tail &= (UART_XMIT_SIZE - 1);
	पूर्ण

	अगर (data_count) अणु
		ICOM_PORT->statStg->xmit[0].flags =
		    cpu_to_le16(SA_FLAGS_READY_TO_XMIT);
		ICOM_PORT->statStg->xmit[0].leLength =
		    cpu_to_le16(data_count);
		offset =
		    (अचिन्हित दीर्घ) &ICOM_PORT->statStg->xmit[0] -
		    (अचिन्हित दीर्घ) ICOM_PORT->statStg;
		*ICOM_PORT->xmitRestart =
		    cpu_to_le32(ICOM_PORT->statStg_pci + offset);
		cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
		ग_लिखोb(cmdReg | CMD_XMIT_RCV_ENABLE,
		       &ICOM_PORT->dram->CmdReg);
		ग_लिखोb(START_XMIT, &ICOM_PORT->dram->StartXmitCmd);
		trace(ICOM_PORT, "WRITE_START", data_count);
		/* ग_लिखो flush */
		पढ़ोb(&ICOM_PORT->dram->StartXmitCmd);
	पूर्ण

	वापस data_count;
पूर्ण

अटल अंतरभूत व्योम check_modem_status(काष्ठा icom_port *icom_port)
अणु
	अटल अक्षर old_status = 0;
	अक्षर delta_status;
	अचिन्हित अक्षर status;

	spin_lock(&icom_port->uart_port.lock);

	/*modem input रेजिस्टर */
	status = पढ़ोb(&icom_port->dram->isr);
	trace(icom_port, "CHECK_MODEM", status);
	delta_status = status ^ old_status;
	अगर (delta_status) अणु
		अगर (delta_status & ICOM_RI)
			icom_port->uart_port.icount.rng++;
		अगर (delta_status & ICOM_DSR)
			icom_port->uart_port.icount.dsr++;
		अगर (delta_status & ICOM_DCD)
			uart_handle_dcd_change(&icom_port->uart_port,
					       delta_status & ICOM_DCD);
		अगर (delta_status & ICOM_CTS)
			uart_handle_cts_change(&icom_port->uart_port,
					       delta_status & ICOM_CTS);

		wake_up_पूर्णांकerruptible(&icom_port->uart_port.state->
				      port.delta_msr_रुको);
		old_status = status;
	पूर्ण
	spin_unlock(&icom_port->uart_port.lock);
पूर्ण

अटल व्योम xmit_पूर्णांकerrupt(u16 port_पूर्णांक_reg, काष्ठा icom_port *icom_port)
अणु
	अचिन्हित लघु पूर्णांक count;
	पूर्णांक i;

	अगर (port_पूर्णांक_reg & (INT_XMIT_COMPLETED)) अणु
		trace(icom_port, "XMIT_COMPLETE", 0);

		/* clear buffer in use bit */
		icom_port->statStg->xmit[0].flags &=
			cpu_to_le16(~SA_FLAGS_READY_TO_XMIT);

		count = (अचिन्हित लघु पूर्णांक)
			cpu_to_le16(icom_port->statStg->xmit[0].leLength);
		icom_port->uart_port.icount.tx += count;

		क्रम (i=0; i<count &&
			!uart_circ_empty(&icom_port->uart_port.state->xmit); i++) अणु

			icom_port->uart_port.state->xmit.tail++;
			icom_port->uart_port.state->xmit.tail &=
				(UART_XMIT_SIZE - 1);
		पूर्ण

		अगर (!icom_ग_लिखो(&icom_port->uart_port))
			/* activate ग_लिखो queue */
			uart_ग_लिखो_wakeup(&icom_port->uart_port);
	पूर्ण अन्यथा
		trace(icom_port, "XMIT_DISABLED", 0);
पूर्ण

अटल व्योम recv_पूर्णांकerrupt(u16 port_पूर्णांक_reg, काष्ठा icom_port *icom_port)
अणु
	लघु पूर्णांक count, rcv_buff;
	काष्ठा tty_port *port = &icom_port->uart_port.state->port;
	अचिन्हित लघु पूर्णांक status;
	काष्ठा uart_icount *icount;
	अचिन्हित दीर्घ offset;
	अचिन्हित अक्षर flag;

	trace(icom_port, "RCV_COMPLETE", 0);
	rcv_buff = icom_port->next_rcv;

	status = cpu_to_le16(icom_port->statStg->rcv[rcv_buff].flags);
	जबतक (status & SA_FL_RCV_DONE) अणु
		पूर्णांक first = -1;

		trace(icom_port, "FID_STATUS", status);
		count = cpu_to_le16(icom_port->statStg->rcv[rcv_buff].leLength);

		trace(icom_port, "RCV_COUNT", count);

		trace(icom_port, "REAL_COUNT", count);

		offset =
			cpu_to_le32(icom_port->statStg->rcv[rcv_buff].leBuffer) -
			icom_port->recv_buf_pci;

		/* Block copy all but the last byte as this may have status */
		अगर (count > 0) अणु
			first = icom_port->recv_buf[offset];
			tty_insert_flip_string(port, icom_port->recv_buf + offset, count - 1);
		पूर्ण

		icount = &icom_port->uart_port.icount;
		icount->rx += count;

		/* Break detect logic */
		अगर ((status & SA_FLAGS_FRAME_ERROR)
		    && first == 0) अणु
			status &= ~SA_FLAGS_FRAME_ERROR;
			status |= SA_FLAGS_BREAK_DET;
			trace(icom_port, "BREAK_DET", 0);
		पूर्ण

		flag = TTY_NORMAL;

		अगर (status &
		    (SA_FLAGS_BREAK_DET | SA_FLAGS_PARITY_ERROR |
		     SA_FLAGS_FRAME_ERROR | SA_FLAGS_OVERRUN)) अणु

			अगर (status & SA_FLAGS_BREAK_DET)
				icount->brk++;
			अगर (status & SA_FLAGS_PARITY_ERROR)
				icount->parity++;
			अगर (status & SA_FLAGS_FRAME_ERROR)
				icount->frame++;
			अगर (status & SA_FLAGS_OVERRUN)
				icount->overrun++;

			/*
			 * Now check to see अगर अक्षरacter should be
			 * ignored, and mask off conditions which
			 * should be ignored.
			 */
			अगर (status & icom_port->ignore_status_mask) अणु
				trace(icom_port, "IGNORE_CHAR", 0);
				जाओ ignore_अक्षर;
			पूर्ण

			status &= icom_port->पढ़ो_status_mask;

			अगर (status & SA_FLAGS_BREAK_DET) अणु
				flag = TTY_BREAK;
			पूर्ण अन्यथा अगर (status & SA_FLAGS_PARITY_ERROR) अणु
				trace(icom_port, "PARITY_ERROR", 0);
				flag = TTY_PARITY;
			पूर्ण अन्यथा अगर (status & SA_FLAGS_FRAME_ERROR)
				flag = TTY_FRAME;

		पूर्ण

		tty_insert_flip_अक्षर(port, *(icom_port->recv_buf + offset + count - 1), flag);

		अगर (status & SA_FLAGS_OVERRUN)
			/*
			 * Overrun is special, since it's
			 * reported immediately, and करोesn't
			 * affect the current अक्षरacter
			 */
			tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
ignore_अक्षर:
		icom_port->statStg->rcv[rcv_buff].flags = 0;
		icom_port->statStg->rcv[rcv_buff].leLength = 0;
		icom_port->statStg->rcv[rcv_buff].WorkingLength =
			(अचिन्हित लघु पूर्णांक) cpu_to_le16(RCV_BUFF_SZ);

		rcv_buff++;
		अगर (rcv_buff == NUM_RBUFFS)
			rcv_buff = 0;

		status = cpu_to_le16(icom_port->statStg->rcv[rcv_buff].flags);
	पूर्ण
	icom_port->next_rcv = rcv_buff;

	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम process_पूर्णांकerrupt(u16 port_पूर्णांक_reg,
			      काष्ठा icom_port *icom_port)
अणु

	spin_lock(&icom_port->uart_port.lock);
	trace(icom_port, "INTERRUPT", port_पूर्णांक_reg);

	अगर (port_पूर्णांक_reg & (INT_XMIT_COMPLETED | INT_XMIT_DISABLED))
		xmit_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);

	अगर (port_पूर्णांक_reg & INT_RCV_COMPLETED)
		recv_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);

	spin_unlock(&icom_port->uart_port.lock);
पूर्ण

अटल irqवापस_t icom_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	व्योम __iomem * पूर्णांक_reg;
	u32 adapter_पूर्णांकerrupts;
	u16 port_पूर्णांक_reg;
	काष्ठा icom_adapter *icom_adapter;
	काष्ठा icom_port *icom_port;

	/* find icom_port क्रम this पूर्णांकerrupt */
	icom_adapter = (काष्ठा icom_adapter *) dev_id;

	अगर (icom_adapter->version == ADAPTER_V2) अणु
		पूर्णांक_reg = icom_adapter->base_addr + 0x8024;

		adapter_पूर्णांकerrupts = पढ़ोl(पूर्णांक_reg);

		अगर (adapter_पूर्णांकerrupts & 0x00003FFF) अणु
			/* port 2 पूर्णांकerrupt,  NOTE:  क्रम all ADAPTER_V2, port 2 will be active */
			icom_port = &icom_adapter->port_info[2];
			port_पूर्णांक_reg = (u16) adapter_पूर्णांकerrupts;
			process_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);
			check_modem_status(icom_port);
		पूर्ण
		अगर (adapter_पूर्णांकerrupts & 0x3FFF0000) अणु
			/* port 3 पूर्णांकerrupt */
			icom_port = &icom_adapter->port_info[3];
			अगर (icom_port->status == ICOM_PORT_ACTIVE) अणु
				port_पूर्णांक_reg =
				    (u16) (adapter_पूर्णांकerrupts >> 16);
				process_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);
				check_modem_status(icom_port);
			पूर्ण
		पूर्ण

		/* Clear out any pending पूर्णांकerrupts */
		ग_लिखोl(adapter_पूर्णांकerrupts, पूर्णांक_reg);

		पूर्णांक_reg = icom_adapter->base_addr + 0x8004;
	पूर्ण अन्यथा अणु
		पूर्णांक_reg = icom_adapter->base_addr + 0x4004;
	पूर्ण

	adapter_पूर्णांकerrupts = पढ़ोl(पूर्णांक_reg);

	अगर (adapter_पूर्णांकerrupts & 0x00003FFF) अणु
		/* port 0 पूर्णांकerrupt, NOTE:  क्रम all adapters, port 0 will be active */
		icom_port = &icom_adapter->port_info[0];
		port_पूर्णांक_reg = (u16) adapter_पूर्णांकerrupts;
		process_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);
		check_modem_status(icom_port);
	पूर्ण
	अगर (adapter_पूर्णांकerrupts & 0x3FFF0000) अणु
		/* port 1 पूर्णांकerrupt */
		icom_port = &icom_adapter->port_info[1];
		अगर (icom_port->status == ICOM_PORT_ACTIVE) अणु
			port_पूर्णांक_reg = (u16) (adapter_पूर्णांकerrupts >> 16);
			process_पूर्णांकerrupt(port_पूर्णांक_reg, icom_port);
			check_modem_status(icom_port);
		पूर्ण
	पूर्ण

	/* Clear out any pending पूर्णांकerrupts */
	ग_लिखोl(adapter_पूर्णांकerrupts, पूर्णांक_reg);

	/* flush the ग_लिखो */
	adapter_पूर्णांकerrupts = पढ़ोl(पूर्णांक_reg);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * ------------------------------------------------------------------
 * Begin serial-core API
 * ------------------------------------------------------------------
 */
अटल अचिन्हित पूर्णांक icom_tx_empty(काष्ठा uart_port *port)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	अगर (cpu_to_le16(ICOM_PORT->statStg->xmit[0].flags) &
	    SA_FLAGS_READY_TO_XMIT)
		ret = TIOCSER_TEMT;
	अन्यथा
		ret = 0;

	spin_unlock_irqrestore(&port->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम icom_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित अक्षर local_osr;

	trace(ICOM_PORT, "SET_MODEM", 0);
	local_osr = पढ़ोb(&ICOM_PORT->dram->osr);

	अगर (mctrl & TIOCM_RTS) अणु
		trace(ICOM_PORT, "RAISE_RTS", 0);
		local_osr |= ICOM_RTS;
	पूर्ण अन्यथा अणु
		trace(ICOM_PORT, "LOWER_RTS", 0);
		local_osr &= ~ICOM_RTS;
	पूर्ण

	अगर (mctrl & TIOCM_DTR) अणु
		trace(ICOM_PORT, "RAISE_DTR", 0);
		local_osr |= ICOM_DTR;
	पूर्ण अन्यथा अणु
		trace(ICOM_PORT, "LOWER_DTR", 0);
		local_osr &= ~ICOM_DTR;
	पूर्ण

	ग_लिखोb(local_osr, &ICOM_PORT->dram->osr);
पूर्ण

अटल अचिन्हित पूर्णांक icom_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक result;

	trace(ICOM_PORT, "GET_MODEM", 0);

	status = पढ़ोb(&ICOM_PORT->dram->isr);

	result = ((status & ICOM_DCD) ? TIOCM_CAR : 0)
	    | ((status & ICOM_RI) ? TIOCM_RNG : 0)
	    | ((status & ICOM_DSR) ? TIOCM_DSR : 0)
	    | ((status & ICOM_CTS) ? TIOCM_CTS : 0);
	वापस result;
पूर्ण

अटल व्योम icom_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर cmdReg;

	trace(ICOM_PORT, "STOP", 0);
	cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
	ग_लिखोb(cmdReg | CMD_HOLD_XMIT, &ICOM_PORT->dram->CmdReg);
पूर्ण

अटल व्योम icom_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर cmdReg;

	trace(ICOM_PORT, "START", 0);
	cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
	अगर ((cmdReg & CMD_HOLD_XMIT) == CMD_HOLD_XMIT)
		ग_लिखोb(cmdReg & ~CMD_HOLD_XMIT,
		       &ICOM_PORT->dram->CmdReg);

	icom_ग_लिखो(port);
पूर्ण

अटल व्योम icom_send_xअक्षर(काष्ठा uart_port *port, अक्षर ch)
अणु
	अचिन्हित अक्षर xdata;
	पूर्णांक index;
	अचिन्हित दीर्घ flags;

	trace(ICOM_PORT, "SEND_XCHAR", ch);

	/* रुको .1 sec to send अक्षर */
	क्रम (index = 0; index < 10; index++) अणु
		spin_lock_irqsave(&port->lock, flags);
		xdata = पढ़ोb(&ICOM_PORT->dram->xअक्षर);
		अगर (xdata == 0x00) अणु
			trace(ICOM_PORT, "QUICK_WRITE", 0);
			ग_लिखोb(ch, &ICOM_PORT->dram->xअक्षर);

			/* flush ग_लिखो operation */
			xdata = पढ़ोb(&ICOM_PORT->dram->xअक्षर);
			spin_unlock_irqrestore(&port->lock, flags);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&port->lock, flags);
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम icom_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर cmdReg;

	cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
	ग_लिखोb(cmdReg & ~CMD_RCV_ENABLE, &ICOM_PORT->dram->CmdReg);
पूर्ण

अटल व्योम icom_अवरोध(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित अक्षर cmdReg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	trace(ICOM_PORT, "BREAK", 0);
	cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
	अगर (अवरोध_state == -1) अणु
		ग_लिखोb(cmdReg | CMD_SND_BREAK, &ICOM_PORT->dram->CmdReg);
	पूर्ण अन्यथा अणु
		ग_लिखोb(cmdReg & ~CMD_SND_BREAK, &ICOM_PORT->dram->CmdReg);
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक icom_खोलो(काष्ठा uart_port *port)
अणु
	पूर्णांक retval;

	kref_get(&ICOM_PORT->adapter->kref);
	retval = startup(ICOM_PORT);

	अगर (retval) अणु
		kref_put(&ICOM_PORT->adapter->kref, icom_kref_release);
		trace(ICOM_PORT, "STARTUP_ERROR", 0);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम icom_बंद(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर cmdReg;

	trace(ICOM_PORT, "CLOSE", 0);

	/* stop receiver */
	cmdReg = पढ़ोb(&ICOM_PORT->dram->CmdReg);
	ग_लिखोb(cmdReg & ~CMD_RCV_ENABLE, &ICOM_PORT->dram->CmdReg);

	shutकरोwn(ICOM_PORT);

	kref_put(&ICOM_PORT->adapter->kref, icom_kref_release);
पूर्ण

अटल व्योम icom_set_termios(काष्ठा uart_port *port,
			     काष्ठा ktermios *termios,
			     काष्ठा ktermios *old_termios)
अणु
	पूर्णांक baud;
	अचिन्हित cflag, अगरlag;
	अक्षर new_config2;
	अक्षर new_config3 = 0;
	अक्षर पंचांगp_byte;
	पूर्णांक index;
	पूर्णांक rcv_buff, xmit_buff;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	trace(ICOM_PORT, "CHANGE_SPEED", 0);

	cflag = termios->c_cflag;
	अगरlag = termios->c_अगरlag;

	new_config2 = ICOM_ACFG_DRIVE1;

	/* byte size and parity */
	चयन (cflag & CSIZE) अणु
	हाल CS5:		/* 5 bits/अक्षर */
		new_config2 |= ICOM_ACFG_5BPC;
		अवरोध;
	हाल CS6:		/* 6 bits/अक्षर */
		new_config2 |= ICOM_ACFG_6BPC;
		अवरोध;
	हाल CS7:		/* 7 bits/अक्षर */
		new_config2 |= ICOM_ACFG_7BPC;
		अवरोध;
	हाल CS8:		/* 8 bits/अक्षर */
		new_config2 |= ICOM_ACFG_8BPC;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (cflag & CSTOPB) अणु
		/* 2 stop bits */
		new_config2 |= ICOM_ACFG_2STOP_BIT;
	पूर्ण
	अगर (cflag & PARENB) अणु
		/* parity bit enabled */
		new_config2 |= ICOM_ACFG_PARITY_ENAB;
		trace(ICOM_PORT, "PARENB", 0);
	पूर्ण
	अगर (cflag & PARODD) अणु
		/* odd parity */
		new_config2 |= ICOM_ACFG_PARITY_ODD;
		trace(ICOM_PORT, "PARODD", 0);
	पूर्ण

	/* Determine भागisor based on baud rate */
	baud = uart_get_baud_rate(port, termios, old_termios,
				  icom_acfg_baud[0],
				  icom_acfg_baud[BAUD_TABLE_LIMIT]);
	अगर (!baud)
		baud = 9600;	/* B0 transition handled in rs_set_termios */

	क्रम (index = 0; index < BAUD_TABLE_LIMIT; index++) अणु
		अगर (icom_acfg_baud[index] == baud) अणु
			new_config3 = index;
			अवरोध;
		पूर्ण
	पूर्ण

	uart_update_समयout(port, cflag, baud);

	/* CTS flow control flag and modem status पूर्णांकerrupts */
	पंचांगp_byte = पढ़ोb(&(ICOM_PORT->dram->HDLCConfigReg));
	अगर (cflag & CRTSCTS)
		पंचांगp_byte |= HDLC_HDW_FLOW;
	अन्यथा
		पंचांगp_byte &= ~HDLC_HDW_FLOW;
	ग_लिखोb(पंचांगp_byte, &(ICOM_PORT->dram->HDLCConfigReg));

	/*
	 * Set up parity check flag
	 */
	ICOM_PORT->पढ़ो_status_mask = SA_FLAGS_OVERRUN | SA_FL_RCV_DONE;
	अगर (अगरlag & INPCK)
		ICOM_PORT->पढ़ो_status_mask |=
		    SA_FLAGS_FRAME_ERROR | SA_FLAGS_PARITY_ERROR;

	अगर ((अगरlag & BRKINT) || (अगरlag & PARMRK))
		ICOM_PORT->पढ़ो_status_mask |= SA_FLAGS_BREAK_DET;

	/*
	 * Characters to ignore
	 */
	ICOM_PORT->ignore_status_mask = 0;
	अगर (अगरlag & IGNPAR)
		ICOM_PORT->ignore_status_mask |=
		    SA_FLAGS_PARITY_ERROR | SA_FLAGS_FRAME_ERROR;
	अगर (अगरlag & IGNBRK) अणु
		ICOM_PORT->ignore_status_mask |= SA_FLAGS_BREAK_DET;
		/*
		 * If we're ignore parity and अवरोध indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		अगर (अगरlag & IGNPAR)
			ICOM_PORT->ignore_status_mask |= SA_FLAGS_OVERRUN;
	पूर्ण

	/*
	 * !!! ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((cflag & CREAD) == 0)
		ICOM_PORT->ignore_status_mask |= SA_FL_RCV_DONE;

	/* Turn off Receiver to prepare क्रम reset */
	ग_लिखोb(CMD_RCV_DISABLE, &ICOM_PORT->dram->CmdReg);

	क्रम (index = 0; index < 10; index++) अणु
		अगर (पढ़ोb(&ICOM_PORT->dram->PrevCmdReg) == 0x00) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* clear all current buffers of data */
	क्रम (rcv_buff = 0; rcv_buff < NUM_RBUFFS; rcv_buff++) अणु
		ICOM_PORT->statStg->rcv[rcv_buff].flags = 0;
		ICOM_PORT->statStg->rcv[rcv_buff].leLength = 0;
		ICOM_PORT->statStg->rcv[rcv_buff].WorkingLength =
		    (अचिन्हित लघु पूर्णांक) cpu_to_le16(RCV_BUFF_SZ);
	पूर्ण

	क्रम (xmit_buff = 0; xmit_buff < NUM_XBUFFS; xmit_buff++) अणु
		ICOM_PORT->statStg->xmit[xmit_buff].flags = 0;
	पूर्ण

	/* activate changes and start xmit and receiver here */
	/* Enable the receiver */
	ग_लिखोb(new_config3, &(ICOM_PORT->dram->async_config3));
	ग_लिखोb(new_config2, &(ICOM_PORT->dram->async_config2));
	पंचांगp_byte = पढ़ोb(&(ICOM_PORT->dram->HDLCConfigReg));
	पंचांगp_byte |= HDLC_PPP_PURE_ASYNC | HDLC_FF_FILL;
	ग_लिखोb(पंचांगp_byte, &(ICOM_PORT->dram->HDLCConfigReg));
	ग_लिखोb(0x04, &(ICOM_PORT->dram->FlagFillIdleTimer));	/* 0.5 seconds */
	ग_लिखोb(0xFF, &(ICOM_PORT->dram->ier));	/* enable modem संकेत पूर्णांकerrupts */

	/* reset processor */
	ग_लिखोb(CMD_RESTART, &ICOM_PORT->dram->CmdReg);

	क्रम (index = 0; index < 10; index++) अणु
		अगर (पढ़ोb(&ICOM_PORT->dram->CmdReg) == 0x00) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Enable Transmitter and Receiver */
	offset =
	    (अचिन्हित दीर्घ) &ICOM_PORT->statStg->rcv[0] -
	    (अचिन्हित दीर्घ) ICOM_PORT->statStg;
	ग_लिखोl(ICOM_PORT->statStg_pci + offset,
	       &ICOM_PORT->dram->RcvStatusAddr);
	ICOM_PORT->next_rcv = 0;
	ICOM_PORT->put_length = 0;
	*ICOM_PORT->xmitRestart = 0;
	ग_लिखोl(ICOM_PORT->xmitRestart_pci,
	       &ICOM_PORT->dram->XmitStatusAddr);
	trace(ICOM_PORT, "XR_ENAB", 0);
	ग_लिखोb(CMD_XMIT_RCV_ENABLE, &ICOM_PORT->dram->CmdReg);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *icom_type(काष्ठा uart_port *port)
अणु
	वापस "icom";
पूर्ण

अटल व्योम icom_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक icom_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम icom_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_ICOM;
पूर्ण

अटल स्थिर काष्ठा uart_ops icom_ops = अणु
	.tx_empty = icom_tx_empty,
	.set_mctrl = icom_set_mctrl,
	.get_mctrl = icom_get_mctrl,
	.stop_tx = icom_stop_tx,
	.start_tx = icom_start_tx,
	.send_xअक्षर = icom_send_xअक्षर,
	.stop_rx = icom_stop_rx,
	.अवरोध_ctl = icom_अवरोध,
	.startup = icom_खोलो,
	.shutकरोwn = icom_बंद,
	.set_termios = icom_set_termios,
	.type = icom_type,
	.release_port = icom_release_port,
	.request_port = icom_request_port,
	.config_port = icom_config_port,
पूर्ण;

#घोषणा ICOM_CONSOLE शून्य

अटल काष्ठा uart_driver icom_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = ICOM_DRIVER_NAME,
	.dev_name = "ttyA",
	.major = ICOM_MAJOR,
	.minor = ICOM_MINOR_START,
	.nr = NR_PORTS,
	.cons = ICOM_CONSOLE,
पूर्ण;

अटल पूर्णांक icom_init_ports(काष्ठा icom_adapter *icom_adapter)
अणु
	u32 subप्रणाली_id = icom_adapter->subप्रणाली_id;
	पूर्णांक i;
	काष्ठा icom_port *icom_port;

	अगर (icom_adapter->version == ADAPTER_V1) अणु
		icom_adapter->numb_ports = 2;

		क्रम (i = 0; i < 2; i++) अणु
			icom_port = &icom_adapter->port_info[i];
			icom_port->port = i;
			icom_port->status = ICOM_PORT_ACTIVE;
			icom_port->imbed_modem = ICOM_UNKNOWN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (subप्रणाली_id == PCI_DEVICE_ID_IBM_ICOM_FOUR_PORT_MODEL) अणु
			icom_adapter->numb_ports = 4;

			क्रम (i = 0; i < 4; i++) अणु
				icom_port = &icom_adapter->port_info[i];

				icom_port->port = i;
				icom_port->status = ICOM_PORT_ACTIVE;
				icom_port->imbed_modem = ICOM_IMBED_MODEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			icom_adapter->numb_ports = 4;

			icom_adapter->port_info[0].port = 0;
			icom_adapter->port_info[0].status = ICOM_PORT_ACTIVE;

			अगर (subप्रणाली_id ==
			    PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM) अणु
				icom_adapter->port_info[0].imbed_modem = ICOM_IMBED_MODEM;
			पूर्ण अन्यथा अणु
				icom_adapter->port_info[0].imbed_modem = ICOM_RVX;
			पूर्ण

			icom_adapter->port_info[1].status = ICOM_PORT_OFF;

			icom_adapter->port_info[2].port = 2;
			icom_adapter->port_info[2].status = ICOM_PORT_ACTIVE;
			icom_adapter->port_info[2].imbed_modem = ICOM_RVX;
			icom_adapter->port_info[3].status = ICOM_PORT_OFF;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम icom_port_active(काष्ठा icom_port *icom_port, काष्ठा icom_adapter *icom_adapter, पूर्णांक port_num)
अणु
	अगर (icom_adapter->version == ADAPTER_V1) अणु
		icom_port->global_reg = icom_adapter->base_addr + 0x4000;
		icom_port->पूर्णांक_reg = icom_adapter->base_addr +
		    0x4004 + 2 - 2 * port_num;
	पूर्ण अन्यथा अणु
		icom_port->global_reg = icom_adapter->base_addr + 0x8000;
		अगर (icom_port->port < 2)
			icom_port->पूर्णांक_reg = icom_adapter->base_addr +
			    0x8004 + 2 - 2 * icom_port->port;
		अन्यथा
			icom_port->पूर्णांक_reg = icom_adapter->base_addr +
			    0x8024 + 2 - 2 * (icom_port->port - 2);
	पूर्ण
पूर्ण
अटल पूर्णांक icom_load_ports(काष्ठा icom_adapter *icom_adapter)
अणु
	काष्ठा icom_port *icom_port;
	पूर्णांक port_num;

	क्रम (port_num = 0; port_num < icom_adapter->numb_ports; port_num++) अणु

		icom_port = &icom_adapter->port_info[port_num];

		अगर (icom_port->status == ICOM_PORT_ACTIVE) अणु
			icom_port_active(icom_port, icom_adapter, port_num);
			icom_port->dram = icom_adapter->base_addr +
					0x2000 * icom_port->port;

			icom_port->adapter = icom_adapter;

			/* get port memory */
			अगर (get_port_memory(icom_port) != 0) अणु
				dev_err(&icom_port->adapter->pci_dev->dev,
					"Memory allocation for port FAILED\n");
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक icom_alloc_adapter(काष्ठा icom_adapter
					**icom_adapter_ref)
अणु
	पूर्णांक adapter_count = 0;
	काष्ठा icom_adapter *icom_adapter;
	काष्ठा icom_adapter *cur_adapter_entry;
	काष्ठा list_head *पंचांगp;

	icom_adapter = kzalloc(माप(काष्ठा icom_adapter), GFP_KERNEL);

	अगर (!icom_adapter) अणु
		वापस -ENOMEM;
	पूर्ण

	list_क्रम_each(पंचांगp, &icom_adapter_head) अणु
		cur_adapter_entry =
		    list_entry(पंचांगp, काष्ठा icom_adapter,
			       icom_adapter_entry);
		अगर (cur_adapter_entry->index != adapter_count) अणु
			अवरोध;
		पूर्ण
		adapter_count++;
	पूर्ण

	icom_adapter->index = adapter_count;
	list_add_tail(&icom_adapter->icom_adapter_entry, पंचांगp);

	*icom_adapter_ref = icom_adapter;
	वापस 0;
पूर्ण

अटल व्योम icom_मुक्त_adapter(काष्ठा icom_adapter *icom_adapter)
अणु
	list_del(&icom_adapter->icom_adapter_entry);
	kमुक्त(icom_adapter);
पूर्ण

अटल व्योम icom_हटाओ_adapter(काष्ठा icom_adapter *icom_adapter)
अणु
	काष्ठा icom_port *icom_port;
	पूर्णांक index;

	क्रम (index = 0; index < icom_adapter->numb_ports; index++) अणु
		icom_port = &icom_adapter->port_info[index];

		अगर (icom_port->status == ICOM_PORT_ACTIVE) अणु
			dev_info(&icom_adapter->pci_dev->dev,
				 "Device removed\n");

			uart_हटाओ_one_port(&icom_uart_driver,
					     &icom_port->uart_port);

			/* be sure that DTR and RTS are dropped */
			ग_लिखोb(0x00, &icom_port->dram->osr);

			/* Wait 0.1 Sec क्रम simple Init to complete */
			msleep(100);

			/* Stop proccessor */
			stop_processor(icom_port);

			मुक्त_port_memory(icom_port);
		पूर्ण
	पूर्ण

	मुक्त_irq(icom_adapter->pci_dev->irq, (व्योम *) icom_adapter);
	iounmap(icom_adapter->base_addr);
	pci_release_regions(icom_adapter->pci_dev);
	icom_मुक्त_adapter(icom_adapter);
पूर्ण

अटल व्योम icom_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा icom_adapter *icom_adapter;

	icom_adapter = to_icom_adapter(kref);
	icom_हटाओ_adapter(icom_adapter);
पूर्ण

अटल पूर्णांक icom_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक index;
	अचिन्हित पूर्णांक command_reg;
	पूर्णांक retval;
	काष्ठा icom_adapter *icom_adapter;
	काष्ठा icom_port *icom_port;

	retval = pci_enable_device(dev);
	अगर (retval) अणु
		dev_err(&dev->dev, "Device enable FAILED\n");
		वापस retval;
	पूर्ण

	retval = pci_request_regions(dev, "icom");
	अगर (retval) अणु
		 dev_err(&dev->dev, "pci_request_regions FAILED\n");
		 pci_disable_device(dev);
		 वापस retval;
	 पूर्ण

	pci_set_master(dev);

	retval = pci_पढ़ो_config_dword(dev, PCI_COMMAND, &command_reg);
	अगर (retval) अणु
		dev_err(&dev->dev, "PCI Config read FAILED\n");
		वापस retval;
	पूर्ण

	pci_ग_लिखो_config_dword(dev, PCI_COMMAND,
		command_reg | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER
 		| PCI_COMMAND_PARITY | PCI_COMMAND_SERR);

	अगर (ent->driver_data == ADAPTER_V1) अणु
		pci_ग_लिखो_config_dword(dev, 0x44, 0x8300830A);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_dword(dev, 0x44, 0x42004200);
		pci_ग_लिखो_config_dword(dev, 0x48, 0x42004200);
	पूर्ण


	retval = icom_alloc_adapter(&icom_adapter);
	अगर (retval) अणु
		 dev_err(&dev->dev, "icom_alloc_adapter FAILED\n");
		 retval = -EIO;
		 जाओ probe_निकास0;
	पूर्ण

	icom_adapter->base_addr_pci = pci_resource_start(dev, 0);
	icom_adapter->pci_dev = dev;
	icom_adapter->version = ent->driver_data;
	icom_adapter->subप्रणाली_id = ent->subdevice;


	retval = icom_init_ports(icom_adapter);
	अगर (retval) अणु
		dev_err(&dev->dev, "Port configuration failed\n");
		जाओ probe_निकास1;
	पूर्ण

	icom_adapter->base_addr = pci_ioremap_bar(dev, 0);

	अगर (!icom_adapter->base_addr) अणु
		retval = -ENOMEM;
		जाओ probe_निकास1;
	पूर्ण

	 /* save off irq and request irq line */
	 retval = request_irq(dev->irq, icom_पूर्णांकerrupt, IRQF_SHARED, ICOM_DRIVER_NAME, (व्योम *)icom_adapter);
	 अगर (retval) अणु
		  जाओ probe_निकास2;
	 पूर्ण

	retval = icom_load_ports(icom_adapter);

	क्रम (index = 0; index < icom_adapter->numb_ports; index++) अणु
		icom_port = &icom_adapter->port_info[index];

		अगर (icom_port->status == ICOM_PORT_ACTIVE) अणु
			icom_port->uart_port.irq = icom_port->adapter->pci_dev->irq;
			icom_port->uart_port.type = PORT_ICOM;
			icom_port->uart_port.iotype = UPIO_MEM;
			icom_port->uart_port.membase =
				(अचिन्हित अक्षर __iomem *)icom_adapter->base_addr_pci;
			icom_port->uart_port.fअगरosize = 16;
			icom_port->uart_port.ops = &icom_ops;
			icom_port->uart_port.line =
		        icom_port->port + icom_adapter->index * 4;
			अगर (uart_add_one_port (&icom_uart_driver, &icom_port->uart_port)) अणु
				icom_port->status = ICOM_PORT_OFF;
				dev_err(&dev->dev, "Device add failed\n");
			 पूर्ण अन्यथा
				dev_info(&dev->dev, "Device added\n");
		पूर्ण
	पूर्ण

	kref_init(&icom_adapter->kref);
	वापस 0;

probe_निकास2:
	iounmap(icom_adapter->base_addr);
probe_निकास1:
	icom_मुक्त_adapter(icom_adapter);

probe_निकास0:
	pci_release_regions(dev);
	pci_disable_device(dev);

	वापस retval;
पूर्ण

अटल व्योम icom_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा icom_adapter *icom_adapter;
	काष्ठा list_head *पंचांगp;

	list_क्रम_each(पंचांगp, &icom_adapter_head) अणु
		icom_adapter = list_entry(पंचांगp, काष्ठा icom_adapter,
					  icom_adapter_entry);
		अगर (icom_adapter->pci_dev == dev) अणु
			kref_put(&icom_adapter->kref, icom_kref_release);
			वापस;
		पूर्ण
	पूर्ण

	dev_err(&dev->dev, "Unable to find device to remove\n");
पूर्ण

अटल काष्ठा pci_driver icom_pci_driver = अणु
	.name = ICOM_DRIVER_NAME,
	.id_table = icom_pci_table,
	.probe = icom_probe,
	.हटाओ = icom_हटाओ,
पूर्ण;

अटल पूर्णांक __init icom_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&icom_uart_driver);
	अगर (ret)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&icom_pci_driver);

	अगर (ret < 0)
		uart_unरेजिस्टर_driver(&icom_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास icom_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&icom_pci_driver);
	uart_unरेजिस्टर_driver(&icom_uart_driver);
पूर्ण

module_init(icom_init);
module_निकास(icom_निकास);

MODULE_AUTHOR("Michael Anderson <mjanders@us.ibm.com>");
MODULE_DESCRIPTION("IBM iSeries Serial IOA driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("icom_call_setup.bin");
MODULE_FIRMWARE("icom_res_dce.bin");
MODULE_FIRMWARE("icom_asc.bin");
