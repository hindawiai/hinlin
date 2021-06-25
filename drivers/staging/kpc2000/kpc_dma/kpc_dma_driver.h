<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित KPC_DMA_DRIVER_H
#घोषणा KPC_DMA_DRIVER_H
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश "../kpc.h"

काष्ठा kp2000_device;
काष्ठा kpc_dma_device अणु
	काष्ठा list_head            list;
	काष्ठा platक्रमm_device     *pldev;
	u32 __iomem                *eng_regs;
	काष्ठा device              *kpc_dma_dev;
	काष्ठा kobject              kobj;
	अक्षर                        name[16];

	पूर्णांक                         dir; // DMA_FROM_DEVICE || DMA_TO_DEVICE
	काष्ठा mutex                sem;
	अचिन्हित पूर्णांक                irq;
	काष्ठा work_काष्ठा          irq_work;

	atomic_t                    खोलो_count;

	माप_प्रकार                      accumulated_bytes;
	u32                         accumulated_flags;

	// Descriptor "Pool" housekeeping
	u32                         desc_pool_cnt;
	काष्ठा dma_pool            *desc_pool;
	काष्ठा kpc_dma_descriptor  *desc_pool_first;
	काष्ठा kpc_dma_descriptor  *desc_pool_last;

	काष्ठा kpc_dma_descriptor  *desc_next;
	काष्ठा kpc_dma_descriptor  *desc_completed;
पूर्ण;

काष्ठा dev_निजी_data अणु
	काष्ठा kpc_dma_device      *ldev;
	u64                         card_addr;
	u64                         user_ctl;
	u64                         user_ctl_last;
	u64                         user_sts;
पूर्ण;

काष्ठा kpc_dma_device *kpc_dma_lookup_device(पूर्णांक minor);

बाह्य स्थिर काष्ठा file_operations  kpc_dma_fops;

#घोषणा ENG_CAP_PRESENT                 0x00000001
#घोषणा ENG_CAP_सूचीECTION               0x00000002
#घोषणा ENG_CAP_TYPE_MASK               0x000000F0
#घोषणा ENG_CAP_NUMBER_MASK             0x0000FF00
#घोषणा ENG_CAP_CARD_ADDR_SIZE_MASK     0x007F0000
#घोषणा ENG_CAP_DESC_MAX_BYTE_CNT_MASK  0x3F000000
#घोषणा ENG_CAP_PERF_SCALE_MASK         0xC0000000

#घोषणा ENG_CTL_IRQ_ENABLE              BIT(0)
#घोषणा ENG_CTL_IRQ_ACTIVE              BIT(1)
#घोषणा ENG_CTL_DESC_COMPLETE           BIT(2)
#घोषणा ENG_CTL_DESC_ALIGN_ERR          BIT(3)
#घोषणा ENG_CTL_DESC_FETCH_ERR          BIT(4)
#घोषणा ENG_CTL_SW_ABORT_ERR            BIT(5)
#घोषणा ENG_CTL_DESC_CHAIN_END          BIT(7)
#घोषणा ENG_CTL_DMA_ENABLE              BIT(8)
#घोषणा ENG_CTL_DMA_RUNNING             BIT(10)
#घोषणा ENG_CTL_DMA_WAITING             BIT(11)
#घोषणा ENG_CTL_DMA_WAITING_PERSIST     BIT(12)
#घोषणा ENG_CTL_DMA_RESET_REQUEST       BIT(14)
#घोषणा ENG_CTL_DMA_RESET               BIT(15)
#घोषणा ENG_CTL_DESC_FETCH_ERR_CLASS_MASK   0x700000

काष्ठा aio_cb_data अणु
	काष्ठा dev_निजी_data    *priv;
	काष्ठा kpc_dma_device      *ldev;
	काष्ठा completion  *cpl;
	अचिन्हित अक्षर       flags;
	माप_प्रकार              len;

	अचिन्हित पूर्णांक        page_count;
	काष्ठा page       **user_pages;
	काष्ठा sg_table     sgt;
	पूर्णांक                 mapped_entry_count;
पूर्ण;

#घोषणा ACD_FLAG_DONE               0
#घोषणा ACD_FLAG_ABORT              1
#घोषणा ACD_FLAG_ENG_ACCUM_ERROR    4
#घोषणा ACD_FLAG_ENG_ACCUM_SHORT    5

काष्ठा kpc_dma_descriptor अणु
	काष्ठा अणु
		अस्थिर u32  DescByteCount              :20;
		अस्थिर u32  DescStatusErrorFlags       :4;
		अस्थिर u32  DescStatusFlags            :8;
	पूर्ण;
		अस्थिर u32  DescUserControlLS;
		अस्थिर u32  DescUserControlMS;
		अस्थिर u32  DescCardAddrLS;
	काष्ठा अणु
		अस्थिर u32  DescBufferByteCount        :20;
		अस्थिर u32  DescCardAddrMS             :4;
		अस्थिर u32  DescControlFlags           :8;
	पूर्ण;
		अस्थिर u32  DescSystemAddrLS;
		अस्थिर u32  DescSystemAddrMS;
		अस्थिर u32  DescNextDescPtr;

		dma_addr_t    MyDMAAddr;
		काष्ठा kpc_dma_descriptor   *Next;

		काष्ठा aio_cb_data  *acd;
पूर्ण __attribute__((packed));
// DescControlFlags:
#घोषणा DMA_DESC_CTL_SOP            BIT(7)
#घोषणा DMA_DESC_CTL_EOP            BIT(6)
#घोषणा DMA_DESC_CTL_AFIFO          BIT(2)
#घोषणा DMA_DESC_CTL_IRQONERR       BIT(1)
#घोषणा DMA_DESC_CTL_IRQONDONE      BIT(0)
// DescStatusFlags:
#घोषणा DMA_DESC_STS_SOP            BIT(7)
#घोषणा DMA_DESC_STS_EOP            BIT(6)
#घोषणा DMA_DESC_STS_ERROR          BIT(4)
#घोषणा DMA_DESC_STS_USMSZ          BIT(3)
#घोषणा DMA_DESC_STS_USLSZ          BIT(2)
#घोषणा DMA_DESC_STS_SHORT          BIT(1)
#घोषणा DMA_DESC_STS_COMPLETE       BIT(0)
// DescStatusErrorFlags:
#घोषणा DMA_DESC_ESTS_ECRC          BIT(2)
#घोषणा DMA_DESC_ESTS_POISON        BIT(1)
#घोषणा DMA_DESC_ESTS_UNSUCCESSFUL  BIT(0)

#घोषणा DMA_DESC_ALIGNMENT          0x20

अटल अंतरभूत
u32  GetEngineCapabilities(काष्ठा kpc_dma_device *eng)
अणु
	वापस पढ़ोl(eng->eng_regs + 0);
पूर्ण

अटल अंतरभूत
व्योम  WriteEngineControl(काष्ठा kpc_dma_device *eng, u32 value)
अणु
	ग_लिखोl(value, eng->eng_regs + 1);
पूर्ण

अटल अंतरभूत
u32  GetEngineControl(काष्ठा kpc_dma_device *eng)
अणु
	वापस पढ़ोl(eng->eng_regs + 1);
पूर्ण

अटल अंतरभूत
व्योम  SetClearEngineControl(काष्ठा kpc_dma_device *eng, u32 set_bits, u32 clear_bits)
अणु
	u32 val = GetEngineControl(eng);

	val |= set_bits;
	val &= ~clear_bits;
	WriteEngineControl(eng, val);
पूर्ण

अटल अंतरभूत
व्योम  SetEngineNextPtr(काष्ठा kpc_dma_device *eng, काष्ठा kpc_dma_descriptor *desc)
अणु
	ग_लिखोl(desc->MyDMAAddr, eng->eng_regs + 2);
पूर्ण

अटल अंतरभूत
व्योम  SetEngineSWPtr(काष्ठा kpc_dma_device *eng, काष्ठा kpc_dma_descriptor *desc)
अणु
	ग_लिखोl(desc->MyDMAAddr, eng->eng_regs + 3);
पूर्ण

अटल अंतरभूत
व्योम  ClearEngineCompletePtr(काष्ठा kpc_dma_device *eng)
अणु
	ग_लिखोl(0, eng->eng_regs + 4);
पूर्ण

अटल अंतरभूत
u32  GetEngineCompletePtr(काष्ठा kpc_dma_device *eng)
अणु
	वापस पढ़ोl(eng->eng_regs + 4);
पूर्ण

अटल अंतरभूत
व्योम  lock_engine(काष्ठा kpc_dma_device *eng)
अणु
	BUG_ON(!eng);
	mutex_lock(&eng->sem);
पूर्ण

अटल अंतरभूत
व्योम  unlock_engine(काष्ठा kpc_dma_device *eng)
अणु
	BUG_ON(!eng);
	mutex_unlock(&eng->sem);
पूर्ण

/// Shared Functions
व्योम  start_dma_engine(काष्ठा kpc_dma_device *eng);
पूर्णांक   setup_dma_engine(काष्ठा kpc_dma_device *eng, u32 desc_cnt);
व्योम  stop_dma_engine(काष्ठा kpc_dma_device *eng);
व्योम  destroy_dma_engine(काष्ठा kpc_dma_device *eng);
व्योम  clear_desc(काष्ठा kpc_dma_descriptor *desc);
पूर्णांक   count_descriptors_available(काष्ठा kpc_dma_device *eng);
व्योम  transfer_complete_cb(काष्ठा aio_cb_data *acd, माप_प्रकार xfr_count, u32 flags);

#पूर्ण_अगर /* KPC_DMA_DRIVER_H */

