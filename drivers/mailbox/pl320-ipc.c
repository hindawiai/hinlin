<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Calxeda, Inc.
 */
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>

#समावेश <linux/pl320-ipc.h>

#घोषणा IPCMxSOURCE(m)		((m) * 0x40)
#घोषणा IPCMxDSET(m)		(((m) * 0x40) + 0x004)
#घोषणा IPCMxDCLEAR(m)		(((m) * 0x40) + 0x008)
#घोषणा IPCMxDSTATUS(m)		(((m) * 0x40) + 0x00C)
#घोषणा IPCMxMODE(m)		(((m) * 0x40) + 0x010)
#घोषणा IPCMxMSET(m)		(((m) * 0x40) + 0x014)
#घोषणा IPCMxMCLEAR(m)		(((m) * 0x40) + 0x018)
#घोषणा IPCMxMSTATUS(m)		(((m) * 0x40) + 0x01C)
#घोषणा IPCMxSEND(m)		(((m) * 0x40) + 0x020)
#घोषणा IPCMxDR(m, dr)		(((m) * 0x40) + ((dr) * 4) + 0x024)

#घोषणा IPCMMIS(irq)		(((irq) * 8) + 0x800)
#घोषणा IPCMRIS(irq)		(((irq) * 8) + 0x804)

#घोषणा MBOX_MASK(n)		(1 << (n))
#घोषणा IPC_TX_MBOX		1
#घोषणा IPC_RX_MBOX		2

#घोषणा CHAN_MASK(n)		(1 << (n))
#घोषणा A9_SOURCE		1
#घोषणा M3_SOURCE		0

अटल व्योम __iomem *ipc_base;
अटल पूर्णांक ipc_irq;
अटल DEFINE_MUTEX(ipc_m1_lock);
अटल DECLARE_COMPLETION(ipc_completion);
अटल ATOMIC_NOTIFIER_HEAD(ipc_notअगरier);

अटल अंतरभूत व्योम set_destination(पूर्णांक source, पूर्णांक mbox)
अणु
	ग_लिखोl_relaxed(CHAN_MASK(source), ipc_base + IPCMxDSET(mbox));
	ग_लिखोl_relaxed(CHAN_MASK(source), ipc_base + IPCMxMSET(mbox));
पूर्ण

अटल अंतरभूत व्योम clear_destination(पूर्णांक source, पूर्णांक mbox)
अणु
	ग_लिखोl_relaxed(CHAN_MASK(source), ipc_base + IPCMxDCLEAR(mbox));
	ग_लिखोl_relaxed(CHAN_MASK(source), ipc_base + IPCMxMCLEAR(mbox));
पूर्ण

अटल व्योम __ipc_send(पूर्णांक mbox, u32 *data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 7; i++)
		ग_लिखोl_relaxed(data[i], ipc_base + IPCMxDR(mbox, i));
	ग_लिखोl_relaxed(0x1, ipc_base + IPCMxSEND(mbox));
पूर्ण

अटल u32 __ipc_rcv(पूर्णांक mbox, u32 *data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 7; i++)
		data[i] = पढ़ोl_relaxed(ipc_base + IPCMxDR(mbox, i));
	वापस data[1];
पूर्ण

/* blocking implementation from the A9 side, not usable in पूर्णांकerrupts! */
पूर्णांक pl320_ipc_transmit(u32 *data)
अणु
	पूर्णांक ret;

	mutex_lock(&ipc_m1_lock);

	init_completion(&ipc_completion);
	__ipc_send(IPC_TX_MBOX, data);
	ret = रुको_क्रम_completion_समयout(&ipc_completion,
					  msecs_to_jअगरfies(1000));
	अगर (ret == 0) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	ret = __ipc_rcv(IPC_TX_MBOX, data);
out:
	mutex_unlock(&ipc_m1_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pl320_ipc_transmit);

अटल irqवापस_t ipc_handler(पूर्णांक irq, व्योम *dev)
अणु
	u32 irq_stat;
	u32 data[7];

	irq_stat = पढ़ोl_relaxed(ipc_base + IPCMMIS(1));
	अगर (irq_stat & MBOX_MASK(IPC_TX_MBOX)) अणु
		ग_लिखोl_relaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));
		complete(&ipc_completion);
	पूर्ण
	अगर (irq_stat & MBOX_MASK(IPC_RX_MBOX)) अणु
		__ipc_rcv(IPC_RX_MBOX, data);
		atomic_notअगरier_call_chain(&ipc_notअगरier, data[0], data + 1);
		ग_लिखोl_relaxed(2, ipc_base + IPCMxSEND(IPC_RX_MBOX));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक pl320_ipc_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&ipc_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(pl320_ipc_रेजिस्टर_notअगरier);

पूर्णांक pl320_ipc_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&ipc_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(pl320_ipc_unरेजिस्टर_notअगरier);

अटल पूर्णांक pl320_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;

	ipc_base = ioremap(adev->res.start, resource_size(&adev->res));
	अगर (ipc_base == शून्य)
		वापस -ENOMEM;

	ग_लिखोl_relaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));

	ipc_irq = adev->irq[0];
	ret = request_irq(ipc_irq, ipc_handler, 0, dev_name(&adev->dev), शून्य);
	अगर (ret < 0)
		जाओ err;

	/* Init slow mailbox */
	ग_लिखोl_relaxed(CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxSOURCE(IPC_TX_MBOX));
	ग_लिखोl_relaxed(CHAN_MASK(M3_SOURCE),
		       ipc_base + IPCMxDSET(IPC_TX_MBOX));
	ग_लिखोl_relaxed(CHAN_MASK(M3_SOURCE) | CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxMSET(IPC_TX_MBOX));

	/* Init receive mailbox */
	ग_लिखोl_relaxed(CHAN_MASK(M3_SOURCE),
		       ipc_base + IPCMxSOURCE(IPC_RX_MBOX));
	ग_लिखोl_relaxed(CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxDSET(IPC_RX_MBOX));
	ग_लिखोl_relaxed(CHAN_MASK(M3_SOURCE) | CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxMSET(IPC_RX_MBOX));

	वापस 0;
err:
	iounmap(ipc_base);
	वापस ret;
पूर्ण

अटल काष्ठा amba_id pl320_ids[] = अणु
	अणु
		.id	= 0x00041320,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा amba_driver pl320_driver = अणु
	.drv = अणु
		.name	= "pl320",
	पूर्ण,
	.id_table	= pl320_ids,
	.probe		= pl320_probe,
पूर्ण;

अटल पूर्णांक __init ipc_init(व्योम)
अणु
	वापस amba_driver_रेजिस्टर(&pl320_driver);
पूर्ण
subsys_initcall(ipc_init);
