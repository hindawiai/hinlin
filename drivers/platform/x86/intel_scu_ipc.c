<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Intel SCU IPC mechanism
 *
 * (C) Copyright 2008-2010,2015 Intel Corporation
 * Author: Sreedhara DS (sreedhara.ds@पूर्णांकel.com)
 *
 * SCU running in ARC processor communicates with other entity running in IA
 * core through IPC mechanism which in turn messaging between IA core ad SCU.
 * SCU has two IPC mechanism IPC-1 and IPC-2. IPC-1 is used between IA32 and
 * SCU where IPC-2 is used between P-Unit and SCU. This driver delas with
 * IPC-1 Driver provides an API क्रम घातer control unit रेजिस्टरs (e.g. MSIC)
 * aदीर्घ with other APIs.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

/* IPC defines the following message types */
#घोषणा IPCMSG_PCNTRL         0xff /* Power controller unit पढ़ो/ग_लिखो */

/* Command id associated with message IPCMSG_PCNTRL */
#घोषणा IPC_CMD_PCNTRL_W      0 /* Register ग_लिखो */
#घोषणा IPC_CMD_PCNTRL_R      1 /* Register पढ़ो */
#घोषणा IPC_CMD_PCNTRL_M      2 /* Register पढ़ो-modअगरy-ग_लिखो */

/*
 * IPC रेजिस्टर summary
 *
 * IPC रेजिस्टर blocks are memory mapped at fixed address of PCI BAR 0.
 * To पढ़ो or ग_लिखो inक्रमmation to the SCU, driver ग_लिखोs to IPC-1 memory
 * mapped रेजिस्टरs. The following is the IPC mechanism
 *
 * 1. IA core cDMI पूर्णांकerface claims this transaction and converts it to a
 *    Transaction Layer Packet (TLP) message which is sent across the cDMI.
 *
 * 2. South Complex cDMI block receives this message and ग_लिखोs it to
 *    the IPC-1 रेजिस्टर block, causing an पूर्णांकerrupt to the SCU
 *
 * 3. SCU firmware decodes this पूर्णांकerrupt and IPC message and the appropriate
 *    message handler is called within firmware.
 */

#घोषणा IPC_WWBUF_SIZE    20		/* IPC Write buffer Size */
#घोषणा IPC_RWBUF_SIZE    20		/* IPC Read buffer Size */
#घोषणा IPC_IOC	          0x100		/* IPC command रेजिस्टर IOC bit */

काष्ठा पूर्णांकel_scu_ipc_dev अणु
	काष्ठा device dev;
	काष्ठा resource mem;
	काष्ठा module *owner;
	पूर्णांक irq;
	व्योम __iomem *ipc_base;
	काष्ठा completion cmd_complete;
पूर्ण;

#घोषणा IPC_STATUS		0x04
#घोषणा IPC_STATUS_IRQ		BIT(2)
#घोषणा IPC_STATUS_ERR		BIT(1)
#घोषणा IPC_STATUS_BUSY		BIT(0)

/*
 * IPC Write/Read Buffers:
 * 16 byte buffer क्रम sending and receiving data to and from SCU.
 */
#घोषणा IPC_WRITE_BUFFER	0x80
#घोषणा IPC_READ_BUFFER		0x90

/* Timeout in jअगरfies */
#घोषणा IPC_TIMEOUT		(5 * HZ)

अटल काष्ठा पूर्णांकel_scu_ipc_dev *ipcdev; /* Only one क्रम now */
अटल DEFINE_MUTEX(ipघड़ी); /* lock used to prevent multiple call to SCU */

अटल काष्ठा class पूर्णांकel_scu_ipc_class = अणु
	.name = "intel_scu_ipc",
	.owner = THIS_MODULE,
पूर्ण;

/**
 * पूर्णांकel_scu_ipc_dev_get() - Get SCU IPC instance
 *
 * The recommended new API takes SCU IPC instance as parameter and this
 * function can be called by driver to get the instance. This also makes
 * sure the driver providing the IPC functionality cannot be unloaded
 * जबतक the caller has the instance.
 *
 * Call पूर्णांकel_scu_ipc_dev_put() to release the instance.
 *
 * Returns %शून्य अगर SCU IPC is not currently available.
 */
काष्ठा पूर्णांकel_scu_ipc_dev *पूर्णांकel_scu_ipc_dev_get(व्योम)
अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = शून्य;

	mutex_lock(&ipघड़ी);
	अगर (ipcdev) अणु
		get_device(&ipcdev->dev);
		/*
		 * Prevent the IPC provider from being unloaded जबतक it
		 * is being used.
		 */
		अगर (!try_module_get(ipcdev->owner))
			put_device(&ipcdev->dev);
		अन्यथा
			scu = ipcdev;
	पूर्ण

	mutex_unlock(&ipघड़ी);
	वापस scu;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_scu_ipc_dev_get);

/**
 * पूर्णांकel_scu_ipc_dev_put() - Put SCU IPC instance
 * @scu: SCU IPC instance
 *
 * This function releases the SCU IPC instance retrieved from
 * पूर्णांकel_scu_ipc_dev_get() and allows the driver providing IPC to be
 * unloaded.
 */
व्योम पूर्णांकel_scu_ipc_dev_put(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	अगर (scu) अणु
		module_put(scu->owner);
		put_device(&scu->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_scu_ipc_dev_put);

काष्ठा पूर्णांकel_scu_ipc_devres अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
पूर्ण;

अटल व्योम devm_पूर्णांकel_scu_ipc_dev_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा पूर्णांकel_scu_ipc_devres *dr = res;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = dr->scu;

	पूर्णांकel_scu_ipc_dev_put(scu);
पूर्ण

/**
 * devm_पूर्णांकel_scu_ipc_dev_get() - Allocate managed SCU IPC device
 * @dev: Device requesting the SCU IPC device
 *
 * The recommended new API takes SCU IPC instance as parameter and this
 * function can be called by driver to get the instance. This also makes
 * sure the driver providing the IPC functionality cannot be unloaded
 * जबतक the caller has the instance.
 *
 * Returns %शून्य अगर SCU IPC is not currently available.
 */
काष्ठा पूर्णांकel_scu_ipc_dev *devm_पूर्णांकel_scu_ipc_dev_get(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_scu_ipc_devres *dr;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;

	dr = devres_alloc(devm_पूर्णांकel_scu_ipc_dev_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	scu = पूर्णांकel_scu_ipc_dev_get();
	अगर (!scu) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	dr->scu = scu;
	devres_add(dev, dr);

	वापस scu;
पूर्ण
EXPORT_SYMBOL_GPL(devm_पूर्णांकel_scu_ipc_dev_get);

/*
 * Send ipc command
 * Command Register (Write Only):
 * A ग_लिखो to this रेजिस्टर results in an पूर्णांकerrupt to the SCU core processor
 * Format:
 * |rfu2(8) | size(8) | command id(4) | rfu1(3) | ioc(1) | command(8)|
 */
अटल अंतरभूत व्योम ipc_command(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u32 cmd)
अणु
	reinit_completion(&scu->cmd_complete);
	ग_लिखोl(cmd | IPC_IOC, scu->ipc_base);
पूर्ण

/*
 * Write ipc data
 * IPC Write Buffer (Write Only):
 * 16-byte buffer क्रम sending data associated with IPC command to
 * SCU. Size of the data is specअगरied in the IPC_COMMAND_REG रेजिस्टर
 */
अटल अंतरभूत व्योम ipc_data_ग_लिखोl(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u32 data, u32 offset)
अणु
	ग_लिखोl(data, scu->ipc_base + IPC_WRITE_BUFFER + offset);
पूर्ण

/*
 * Status Register (Read Only):
 * Driver will पढ़ो this रेजिस्टर to get the पढ़ोy/busy status of the IPC
 * block and error status of the IPC command that was just processed by SCU
 * Format:
 * |rfu3(8)|error code(8)|initiator id(8)|cmd id(4)|rfu1(2)|error(1)|busy(1)|
 */
अटल अंतरभूत u8 ipc_पढ़ो_status(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	वापस __raw_पढ़ोl(scu->ipc_base + IPC_STATUS);
पूर्ण

/* Read ipc byte data */
अटल अंतरभूत u8 ipc_data_पढ़ोb(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u32 offset)
अणु
	वापस पढ़ोb(scu->ipc_base + IPC_READ_BUFFER + offset);
पूर्ण

/* Read ipc u32 data */
अटल अंतरभूत u32 ipc_data_पढ़ोl(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u32 offset)
अणु
	वापस पढ़ोl(scu->ipc_base + IPC_READ_BUFFER + offset);
पूर्ण

/* Wait till scu status is busy */
अटल अंतरभूत पूर्णांक busy_loop(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(IPC_TIMEOUT);

	करो अणु
		u32 status;

		status = ipc_पढ़ो_status(scu);
		अगर (!(status & IPC_STATUS_BUSY))
			वापस (status & IPC_STATUS_ERR) ? -EIO : 0;

		usleep_range(50, 100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस -ETIMEDOUT;
पूर्ण

/* Wait till ipc ioc पूर्णांकerrupt is received or समयout in 3 HZ */
अटल अंतरभूत पूर्णांक ipc_रुको_क्रम_पूर्णांकerrupt(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	पूर्णांक status;

	अगर (!रुको_क्रम_completion_समयout(&scu->cmd_complete, IPC_TIMEOUT))
		वापस -ETIMEDOUT;

	status = ipc_पढ़ो_status(scu);
	अगर (status & IPC_STATUS_ERR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_scu_ipc_check_status(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	वापस scu->irq > 0 ? ipc_रुको_क्रम_पूर्णांकerrupt(scu) : busy_loop(scu);
पूर्ण

/* Read/Write घातer control(PMIC in Langwell, MSIC in PenWell) रेजिस्टरs */
अटल पूर्णांक pwr_reg_rdwr(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 *addr, u8 *data,
			u32 count, u32 op, u32 id)
अणु
	पूर्णांक nc;
	u32 offset = 0;
	पूर्णांक err;
	u8 cbuf[IPC_WWBUF_SIZE];
	u32 *wbuf = (u32 *)&cbuf;

	स_रखो(cbuf, 0, माप(cbuf));

	mutex_lock(&ipघड़ी);
	अगर (!scu)
		scu = ipcdev;
	अगर (!scu) अणु
		mutex_unlock(&ipघड़ी);
		वापस -ENODEV;
	पूर्ण

	क्रम (nc = 0; nc < count; nc++, offset += 2) अणु
		cbuf[offset] = addr[nc];
		cbuf[offset + 1] = addr[nc] >> 8;
	पूर्ण

	अगर (id == IPC_CMD_PCNTRL_R) अणु
		क्रम (nc = 0, offset = 0; nc < count; nc++, offset += 4)
			ipc_data_ग_लिखोl(scu, wbuf[nc], offset);
		ipc_command(scu, (count * 2) << 16 | id << 12 | 0 << 8 | op);
	पूर्ण अन्यथा अगर (id == IPC_CMD_PCNTRL_W) अणु
		क्रम (nc = 0; nc < count; nc++, offset += 1)
			cbuf[offset] = data[nc];
		क्रम (nc = 0, offset = 0; nc < count; nc++, offset += 4)
			ipc_data_ग_लिखोl(scu, wbuf[nc], offset);
		ipc_command(scu, (count * 3) << 16 | id << 12 | 0 << 8 | op);
	पूर्ण अन्यथा अगर (id == IPC_CMD_PCNTRL_M) अणु
		cbuf[offset] = data[0];
		cbuf[offset + 1] = data[1];
		ipc_data_ग_लिखोl(scu, wbuf[0], 0); /* Write wbuff */
		ipc_command(scu, 4 << 16 | id << 12 | 0 << 8 | op);
	पूर्ण

	err = पूर्णांकel_scu_ipc_check_status(scu);
	अगर (!err && id == IPC_CMD_PCNTRL_R) अणु /* Read rbuf */
		/* Workaround: values are पढ़ो as 0 without स_नकल_fromio */
		स_नकल_fromio(cbuf, scu->ipc_base + 0x90, 16);
		क्रम (nc = 0; nc < count; nc++)
			data[nc] = ipc_data_पढ़ोb(scu, nc);
	पूर्ण
	mutex_unlock(&ipघड़ी);
	वापस err;
पूर्ण

/**
 * पूर्णांकel_scu_ipc_dev_ioपढ़ो8() - Read a byte via the SCU
 * @scu: Optional SCU IPC instance
 * @addr: Register on SCU
 * @data: Return poपूर्णांकer क्रम पढ़ो byte
 *
 * Read a single रेजिस्टर. Returns %0 on success or an error code. All
 * locking between SCU accesses is handled क्रम the caller.
 *
 * This function may sleep.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_ioपढ़ो8(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr, u8 *data)
अणु
	वापस pwr_reg_rdwr(scu, &addr, data, 1, IPCMSG_PCNTRL, IPC_CMD_PCNTRL_R);
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_ioपढ़ो8);

/**
 * पूर्णांकel_scu_ipc_dev_ioग_लिखो8() - Write a byte via the SCU
 * @scu: Optional SCU IPC instance
 * @addr: Register on SCU
 * @data: Byte to ग_लिखो
 *
 * Write a single रेजिस्टर. Returns %0 on success or an error code. All
 * locking between SCU accesses is handled क्रम the caller.
 *
 * This function may sleep.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_ioग_लिखो8(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr, u8 data)
अणु
	वापस pwr_reg_rdwr(scu, &addr, &data, 1, IPCMSG_PCNTRL, IPC_CMD_PCNTRL_W);
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_ioग_लिखो8);

/**
 * पूर्णांकel_scu_ipc_dev_पढ़ोv() - Read a set of रेजिस्टरs
 * @scu: Optional SCU IPC instance
 * @addr: Register list
 * @data: Bytes to वापस
 * @len: Length of array
 *
 * Read रेजिस्टरs. Returns %0 on success or an error code. All locking
 * between SCU accesses is handled क्रम the caller.
 *
 * The largest array length permitted by the hardware is 5 items.
 *
 * This function may sleep.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_पढ़ोv(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 *addr, u8 *data,
			    माप_प्रकार len)
अणु
	वापस pwr_reg_rdwr(scu, addr, data, len, IPCMSG_PCNTRL, IPC_CMD_PCNTRL_R);
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_पढ़ोv);

/**
 * पूर्णांकel_scu_ipc_dev_ग_लिखोv() - Write a set of रेजिस्टरs
 * @scu: Optional SCU IPC instance
 * @addr: Register list
 * @data: Bytes to ग_लिखो
 * @len: Length of array
 *
 * Write रेजिस्टरs. Returns %0 on success or an error code. All locking
 * between SCU accesses is handled क्रम the caller.
 *
 * The largest array length permitted by the hardware is 5 items.
 *
 * This function may sleep.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_ग_लिखोv(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 *addr, u8 *data,
			     माप_प्रकार len)
अणु
	वापस pwr_reg_rdwr(scu, addr, data, len, IPCMSG_PCNTRL, IPC_CMD_PCNTRL_W);
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_ग_लिखोv);

/**
 * पूर्णांकel_scu_ipc_dev_update() - Update a रेजिस्टर
 * @scu: Optional SCU IPC instance
 * @addr: Register address
 * @data: Bits to update
 * @mask: Mask of bits to update
 *
 * Read-modअगरy-ग_लिखो घातer control unit रेजिस्टर. The first data argument
 * must be रेजिस्टर value and second is mask value mask is a biपंचांगap that
 * indicates which bits to update. %0 = masked. Don't modअगरy this bit, %1 =
 * modअगरy this bit. वापसs %0 on success or an error code.
 *
 * This function may sleep. Locking between SCU accesses is handled
 * क्रम the caller.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_update(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr, u8 data,
			     u8 mask)
अणु
	u8 पंचांगp[2] = अणु data, mask पूर्ण;
	वापस pwr_reg_rdwr(scu, &addr, पंचांगp, 1, IPCMSG_PCNTRL, IPC_CMD_PCNTRL_M);
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_update);

/**
 * पूर्णांकel_scu_ipc_dev_simple_command() - Send a simple command
 * @scu: Optional SCU IPC instance
 * @cmd: Command
 * @sub: Sub type
 *
 * Issue a simple command to the SCU. Do not use this पूर्णांकerface अगर you must
 * then access data as any data values may be overwritten by another SCU
 * access by the समय this function वापसs.
 *
 * This function may sleep. Locking क्रम SCU accesses is handled क्रम the
 * caller.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_simple_command(काष्ठा पूर्णांकel_scu_ipc_dev *scu, पूर्णांक cmd,
				     पूर्णांक sub)
अणु
	u32 cmdval;
	पूर्णांक err;

	mutex_lock(&ipघड़ी);
	अगर (!scu)
		scu = ipcdev;
	अगर (!scu) अणु
		mutex_unlock(&ipघड़ी);
		वापस -ENODEV;
	पूर्ण
	scu = ipcdev;
	cmdval = sub << 12 | cmd;
	ipc_command(scu, cmdval);
	err = पूर्णांकel_scu_ipc_check_status(scu);
	mutex_unlock(&ipघड़ी);
	अगर (err)
		dev_err(&scu->dev, "IPC command %#x failed with %d\n", cmdval, err);
	वापस err;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_simple_command);

/**
 * पूर्णांकel_scu_ipc_command_with_size() - Command with data
 * @scu: Optional SCU IPC instance
 * @cmd: Command
 * @sub: Sub type
 * @in: Input data
 * @inlen: Input length in bytes
 * @size: Input size written to the IPC command रेजिस्टर in whatever
 *	  units (dword, byte) the particular firmware requires. Normally
 *	  should be the same as @inlen.
 * @out: Output data
 * @outlen: Output length in bytes
 *
 * Issue a command to the SCU which involves data transfers. Do the
 * data copies under the lock but leave it क्रम the caller to पूर्णांकerpret.
 */
पूर्णांक पूर्णांकel_scu_ipc_dev_command_with_size(काष्ठा पूर्णांकel_scu_ipc_dev *scu, पूर्णांक cmd,
					पूर्णांक sub, स्थिर व्योम *in, माप_प्रकार inlen,
					माप_प्रकार size, व्योम *out, माप_प्रकार outlen)
अणु
	माप_प्रकार outbuflen = DIV_ROUND_UP(outlen, माप(u32));
	माप_प्रकार inbuflen = DIV_ROUND_UP(inlen, माप(u32));
	u32 cmdval, inbuf[4] = अणुपूर्ण;
	पूर्णांक i, err;

	अगर (inbuflen > 4 || outbuflen > 4)
		वापस -EINVAL;

	mutex_lock(&ipघड़ी);
	अगर (!scu)
		scu = ipcdev;
	अगर (!scu) अणु
		mutex_unlock(&ipघड़ी);
		वापस -ENODEV;
	पूर्ण

	स_नकल(inbuf, in, inlen);
	क्रम (i = 0; i < inbuflen; i++)
		ipc_data_ग_लिखोl(scu, inbuf[i], 4 * i);

	cmdval = (size << 16) | (sub << 12) | cmd;
	ipc_command(scu, cmdval);
	err = पूर्णांकel_scu_ipc_check_status(scu);

	अगर (!err) अणु
		u32 outbuf[4] = अणुपूर्ण;

		क्रम (i = 0; i < outbuflen; i++)
			outbuf[i] = ipc_data_पढ़ोl(scu, 4 * i);

		स_नकल(out, outbuf, outlen);
	पूर्ण

	mutex_unlock(&ipघड़ी);
	अगर (err)
		dev_err(&scu->dev, "IPC command %#x failed with %d\n", cmdval, err);
	वापस err;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_scu_ipc_dev_command_with_size);

/*
 * Interrupt handler माला_लो called when ioc bit of IPC_COMMAND_REG set to 1
 * When ioc bit is set to 1, caller api must रुको क्रम पूर्णांकerrupt handler called
 * which in turn unlocks the caller api. Currently this is not used
 *
 * This is edge triggered so we need take no action to clear anything
 */
अटल irqवापस_t ioc(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = dev_id;
	पूर्णांक status = ipc_पढ़ो_status(scu);

	ग_लिखोl(status | IPC_STATUS_IRQ, scu->ipc_base + IPC_STATUS);
	complete(&scu->cmd_complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम पूर्णांकel_scu_ipc_release(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;

	scu = container_of(dev, काष्ठा पूर्णांकel_scu_ipc_dev, dev);
	अगर (scu->irq > 0)
		मुक्त_irq(scu->irq, scu);
	iounmap(scu->ipc_base);
	release_mem_region(scu->mem.start, resource_size(&scu->mem));
	kमुक्त(scu);
पूर्ण

/**
 * __पूर्णांकel_scu_ipc_रेजिस्टर() - Register SCU IPC device
 * @parent: Parent device
 * @scu_data: Data used to configure SCU IPC
 * @owner: Module रेजिस्टरing the SCU IPC device
 *
 * Call this function to रेजिस्टर SCU IPC mechanism under @parent.
 * Returns poपूर्णांकer to the new SCU IPC device or ERR_PTR() in हाल of
 * failure. The caller may use the वापसed instance अगर it needs to करो
 * SCU IPC calls itself.
 */
काष्ठा पूर्णांकel_scu_ipc_dev *
__पूर्णांकel_scu_ipc_रेजिस्टर(काष्ठा device *parent,
			 स्थिर काष्ठा पूर्णांकel_scu_ipc_data *scu_data,
			 काष्ठा module *owner)
अणु
	पूर्णांक err;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	व्योम __iomem *ipc_base;

	mutex_lock(&ipघड़ी);
	/* We support only one IPC */
	अगर (ipcdev) अणु
		err = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	scu = kzalloc(माप(*scu), GFP_KERNEL);
	अगर (!scu) अणु
		err = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	scu->owner = owner;
	scu->dev.parent = parent;
	scu->dev.class = &पूर्णांकel_scu_ipc_class;
	scu->dev.release = पूर्णांकel_scu_ipc_release;
	dev_set_name(&scu->dev, "intel_scu_ipc");

	अगर (!request_mem_region(scu_data->mem.start, resource_size(&scu_data->mem),
				"intel_scu_ipc")) अणु
		err = -EBUSY;
		जाओ err_मुक्त;
	पूर्ण

	ipc_base = ioremap(scu_data->mem.start, resource_size(&scu_data->mem));
	अगर (!ipc_base) अणु
		err = -ENOMEM;
		जाओ err_release;
	पूर्ण

	scu->ipc_base = ipc_base;
	scu->mem = scu_data->mem;
	scu->irq = scu_data->irq;
	init_completion(&scu->cmd_complete);

	अगर (scu->irq > 0) अणु
		err = request_irq(scu->irq, ioc, 0, "intel_scu_ipc", scu);
		अगर (err)
			जाओ err_unmap;
	पूर्ण

	/*
	 * After this poपूर्णांक पूर्णांकel_scu_ipc_release() takes care of
	 * releasing the SCU IPC resources once refcount drops to zero.
	 */
	err = device_रेजिस्टर(&scu->dev);
	अगर (err) अणु
		put_device(&scu->dev);
		जाओ err_unlock;
	पूर्ण

	/* Assign device at last */
	ipcdev = scu;
	mutex_unlock(&ipघड़ी);

	वापस scu;

err_unmap:
	iounmap(ipc_base);
err_release:
	release_mem_region(scu_data->mem.start, resource_size(&scu_data->mem));
err_मुक्त:
	kमुक्त(scu);
err_unlock:
	mutex_unlock(&ipघड़ी);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(__पूर्णांकel_scu_ipc_रेजिस्टर);

/**
 * पूर्णांकel_scu_ipc_unरेजिस्टर() - Unरेजिस्टर SCU IPC
 * @scu: SCU IPC handle
 *
 * This unरेजिस्टरs the SCU IPC device and releases the acquired
 * resources once the refcount goes to zero.
 */
व्योम पूर्णांकel_scu_ipc_unरेजिस्टर(काष्ठा पूर्णांकel_scu_ipc_dev *scu)
अणु
	mutex_lock(&ipघड़ी);
	अगर (!WARN_ON(!ipcdev)) अणु
		ipcdev = शून्य;
		device_unरेजिस्टर(&scu->dev);
	पूर्ण
	mutex_unlock(&ipघड़ी);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_scu_ipc_unरेजिस्टर);

अटल व्योम devm_पूर्णांकel_scu_ipc_unरेजिस्टर(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा पूर्णांकel_scu_ipc_devres *dr = res;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = dr->scu;

	पूर्णांकel_scu_ipc_unरेजिस्टर(scu);
पूर्ण

/**
 * __devm_पूर्णांकel_scu_ipc_रेजिस्टर() - Register managed SCU IPC device
 * @parent: Parent device
 * @scu_data: Data used to configure SCU IPC
 * @owner: Module रेजिस्टरing the SCU IPC device
 *
 * Call this function to रेजिस्टर managed SCU IPC mechanism under
 * @parent. Returns poपूर्णांकer to the new SCU IPC device or ERR_PTR() in
 * हाल of failure. The caller may use the वापसed instance अगर it needs
 * to करो SCU IPC calls itself.
 */
काष्ठा पूर्णांकel_scu_ipc_dev *
__devm_पूर्णांकel_scu_ipc_रेजिस्टर(काष्ठा device *parent,
			      स्थिर काष्ठा पूर्णांकel_scu_ipc_data *scu_data,
			      काष्ठा module *owner)
अणु
	काष्ठा पूर्णांकel_scu_ipc_devres *dr;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;

	dr = devres_alloc(devm_पूर्णांकel_scu_ipc_unरेजिस्टर, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	scu = __पूर्णांकel_scu_ipc_रेजिस्टर(parent, scu_data, owner);
	अगर (IS_ERR(scu)) अणु
		devres_मुक्त(dr);
		वापस scu;
	पूर्ण

	dr->scu = scu;
	devres_add(parent, dr);

	वापस scu;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_पूर्णांकel_scu_ipc_रेजिस्टर);

अटल पूर्णांक __init पूर्णांकel_scu_ipc_init(व्योम)
अणु
	वापस class_रेजिस्टर(&पूर्णांकel_scu_ipc_class);
पूर्ण
subsys_initcall(पूर्णांकel_scu_ipc_init);

अटल व्योम __निकास पूर्णांकel_scu_ipc_निकास(व्योम)
अणु
	class_unरेजिस्टर(&पूर्णांकel_scu_ipc_class);
पूर्ण
module_निकास(पूर्णांकel_scu_ipc_निकास);
