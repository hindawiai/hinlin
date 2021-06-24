<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/device.h>

#समावेश "lima_device.h"
#समावेश "lima_mmu.h"
#समावेश "lima_vm.h"
#समावेश "lima_regs.h"

#घोषणा mmu_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा mmu_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

#घोषणा lima_mmu_send_command(cmd, addr, val, cond)	     \
(अणु							     \
	पूर्णांक __ret;					     \
							     \
	mmu_ग_लिखो(LIMA_MMU_COMMAND, cmd);		     \
	__ret = पढ़ोl_poll_समयout(ip->iomem + (addr), val,  \
				  cond, 0, 100);	     \
	अगर (__ret)					     \
		dev_err(dev->dev,			     \
			"mmu command %x timeout\n", cmd);    \
	__ret;						     \
पूर्ण)

अटल irqवापस_t lima_mmu_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lima_ip *ip = data;
	काष्ठा lima_device *dev = ip->dev;
	u32 status = mmu_पढ़ो(LIMA_MMU_INT_STATUS);
	काष्ठा lima_sched_pipe *pipe;

	/* क्रम shared irq हाल */
	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & LIMA_MMU_INT_PAGE_FAULT) अणु
		u32 fault = mmu_पढ़ो(LIMA_MMU_PAGE_FAULT_ADDR);

		dev_err(dev->dev, "mmu page fault at 0x%x from bus id %d of type %s on %s\n",
			fault, LIMA_MMU_STATUS_BUS_ID(status),
			status & LIMA_MMU_STATUS_PAGE_FAULT_IS_WRITE ? "write" : "read",
			lima_ip_name(ip));
	पूर्ण

	अगर (status & LIMA_MMU_INT_READ_BUS_ERROR)
		dev_err(dev->dev, "mmu %s irq bus error\n", lima_ip_name(ip));

	/* mask all पूर्णांकerrupts beक्रमe resume */
	mmu_ग_लिखो(LIMA_MMU_INT_MASK, 0);
	mmu_ग_लिखो(LIMA_MMU_INT_CLEAR, status);

	pipe = dev->pipe + (ip->id == lima_ip_gpmmu ? lima_pipe_gp : lima_pipe_pp);
	lima_sched_pipe_mmu_error(pipe);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lima_mmu_hw_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;
	u32 v;

	mmu_ग_लिखो(LIMA_MMU_COMMAND, LIMA_MMU_COMMAND_HARD_RESET);
	err = lima_mmu_send_command(LIMA_MMU_COMMAND_HARD_RESET,
				    LIMA_MMU_DTE_ADDR, v, v == 0);
	अगर (err)
		वापस err;

	mmu_ग_लिखो(LIMA_MMU_INT_MASK,
		  LIMA_MMU_INT_PAGE_FAULT | LIMA_MMU_INT_READ_BUS_ERROR);
	mmu_ग_लिखो(LIMA_MMU_DTE_ADDR, dev->empty_vm->pd.dma);
	वापस lima_mmu_send_command(LIMA_MMU_COMMAND_ENABLE_PAGING,
				     LIMA_MMU_STATUS, v,
				     v & LIMA_MMU_STATUS_PAGING_ENABLED);
पूर्ण

पूर्णांक lima_mmu_resume(काष्ठा lima_ip *ip)
अणु
	अगर (ip->id == lima_ip_ppmmu_bcast)
		वापस 0;

	वापस lima_mmu_hw_init(ip);
पूर्ण

व्योम lima_mmu_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_mmu_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;

	अगर (ip->id == lima_ip_ppmmu_bcast)
		वापस 0;

	mmu_ग_लिखो(LIMA_MMU_DTE_ADDR, 0xCAFEBABE);
	अगर (mmu_पढ़ो(LIMA_MMU_DTE_ADDR) != 0xCAFEB000) अणु
		dev_err(dev->dev, "mmu %s dte write test fail\n", lima_ip_name(ip));
		वापस -EIO;
	पूर्ण

	err = devm_request_irq(dev->dev, ip->irq, lima_mmu_irq_handler,
			       IRQF_SHARED, lima_ip_name(ip), ip);
	अगर (err) अणु
		dev_err(dev->dev, "mmu %s fail to request irq\n", lima_ip_name(ip));
		वापस err;
	पूर्ण

	वापस lima_mmu_hw_init(ip);
पूर्ण

व्योम lima_mmu_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण

व्योम lima_mmu_flush_tlb(काष्ठा lima_ip *ip)
अणु
	mmu_ग_लिखो(LIMA_MMU_COMMAND, LIMA_MMU_COMMAND_ZAP_CACHE);
पूर्ण

व्योम lima_mmu_चयन_vm(काष्ठा lima_ip *ip, काष्ठा lima_vm *vm)
अणु
	काष्ठा lima_device *dev = ip->dev;
	u32 v;

	lima_mmu_send_command(LIMA_MMU_COMMAND_ENABLE_STALL,
			      LIMA_MMU_STATUS, v,
			      v & LIMA_MMU_STATUS_STALL_ACTIVE);

	mmu_ग_लिखो(LIMA_MMU_DTE_ADDR, vm->pd.dma);

	/* flush the TLB */
	mmu_ग_लिखो(LIMA_MMU_COMMAND, LIMA_MMU_COMMAND_ZAP_CACHE);

	lima_mmu_send_command(LIMA_MMU_COMMAND_DISABLE_STALL,
			      LIMA_MMU_STATUS, v,
			      !(v & LIMA_MMU_STATUS_STALL_ACTIVE));
पूर्ण

व्योम lima_mmu_page_fault_resume(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	u32 status = mmu_पढ़ो(LIMA_MMU_STATUS);
	u32 v;

	अगर (status & LIMA_MMU_STATUS_PAGE_FAULT_ACTIVE) अणु
		dev_info(dev->dev, "mmu resume\n");

		mmu_ग_लिखो(LIMA_MMU_INT_MASK, 0);
		mmu_ग_लिखो(LIMA_MMU_DTE_ADDR, 0xCAFEBABE);
		lima_mmu_send_command(LIMA_MMU_COMMAND_HARD_RESET,
				      LIMA_MMU_DTE_ADDR, v, v == 0);
		mmu_ग_लिखो(LIMA_MMU_INT_MASK, LIMA_MMU_INT_PAGE_FAULT | LIMA_MMU_INT_READ_BUS_ERROR);
		mmu_ग_लिखो(LIMA_MMU_DTE_ADDR, dev->empty_vm->pd.dma);
		lima_mmu_send_command(LIMA_MMU_COMMAND_ENABLE_PAGING,
				      LIMA_MMU_STATUS, v,
				      v & LIMA_MMU_STATUS_PAGING_ENABLED);
	पूर्ण
पूर्ण
