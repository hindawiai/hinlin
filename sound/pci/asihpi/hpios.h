<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


HPI Operating System Specअगरic macros क्रम Linux Kernel driver

(C) Copyright AudioScience Inc. 1997-2003
******************************************************************************/
#अगर_अघोषित _HPIOS_H_
#घोषणा _HPIOS_H_

#अघोषित HPI_OS_LINUX_KERNEL
#घोषणा HPI_OS_LINUX_KERNEL

#घोषणा HPI_OS_DEFINED
#घोषणा HPI_BUILD_KERNEL_MODE

#समावेश <linux/पन.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#घोषणा HPI_NO_OS_खाता_OPS

/** Details of a memory area allocated with  pci_alloc_consistent
Need all info क्रम parameters to pci_मुक्त_consistent
*/
काष्ठा consistent_dma_area अणु
	काष्ठा device *pdev;
	/* looks like dma-mapping dma_devres ?! */
	माप_प्रकार size;
	व्योम *vaddr;
	dma_addr_t dma_handle;
पूर्ण;

अटल अंतरभूत u16 hpios_locked_mem_get_phys_addr(काष्ठा consistent_dma_area
	*locked_mem_handle, u32 *p_physical_addr)
अणु
	*p_physical_addr = locked_mem_handle->dma_handle;
	वापस 0;
पूर्ण

अटल अंतरभूत u16 hpios_locked_mem_get_virt_addr(काष्ठा consistent_dma_area
	*locked_mem_handle, व्योम **pp_भव_addr)
अणु
	*pp_भव_addr = locked_mem_handle->vaddr;
	वापस 0;
पूर्ण

अटल अंतरभूत u16 hpios_locked_mem_valid(काष्ठा consistent_dma_area
	*locked_mem_handle)
अणु
	वापस locked_mem_handle->size != 0;
पूर्ण

काष्ठा hpi_ioctl_linux अणु
	व्योम __user *phm;
	व्योम __user *phr;
पूर्ण;

/* Conflict?: H is alपढ़ोy used by a number of drivers hid, bluetooth hci,
   and some sound drivers sb16, hdsp, emu10k. AFAIK 0xFC is unused command
*/
#घोषणा HPI_IOCTL_LINUX _IOWR('H', 0xFC, काष्ठा hpi_ioctl_linux)

#घोषणा HPI_DEBUG_FLAG_ERROR   KERN_ERR
#घोषणा HPI_DEBUG_FLAG_WARNING KERN_WARNING
#घोषणा HPI_DEBUG_FLAG_NOTICE  KERN_NOTICE
#घोषणा HPI_DEBUG_FLAG_INFO    KERN_INFO
#घोषणा HPI_DEBUG_FLAG_DEBUG   KERN_DEBUG
#घोषणा HPI_DEBUG_FLAG_VERBOSE KERN_DEBUG	/* kernel has no verbose */

#समावेश <linux/spinlock.h>

#घोषणा HPI_LOCKING

काष्ठा hpios_spinlock अणु
	spinlock_t lock;	/* SEE hpios_spinlock */
	पूर्णांक lock_context;
पूर्ण;

/* The reason क्रम all this evilness is that ALSA calls some of a drivers
 * चालकs in atomic context, and some not.  But all our functions channel
 * through the HPI_Message conduit, so we can't handle the dअगरferent context
 * per function
 */
#घोषणा IN_LOCK_BH 1
#घोषणा IN_LOCK_IRQ 0
अटल अंतरभूत व्योम cond_lock(काष्ठा hpios_spinlock *l)
अणु
	अगर (irqs_disabled()) अणु
		/* NO bh or isr can execute on this processor,
		   so ordinary lock will करो
		 */
		spin_lock(&((l)->lock));
		l->lock_context = IN_LOCK_IRQ;
	पूर्ण अन्यथा अणु
		spin_lock_bh(&((l)->lock));
		l->lock_context = IN_LOCK_BH;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cond_unlock(काष्ठा hpios_spinlock *l)
अणु
	अगर (l->lock_context == IN_LOCK_BH)
		spin_unlock_bh(&((l)->lock));
	अन्यथा
		spin_unlock(&((l)->lock));
पूर्ण

#घोषणा hpios_msgxlock_init(obj)      spin_lock_init(&(obj)->lock)
#घोषणा hpios_msgxlock_lock(obj)   cond_lock(obj)
#घोषणा hpios_msgxlock_unlock(obj) cond_unlock(obj)

#घोषणा hpios_dsplock_init(obj)       spin_lock_init(&(obj)->dsp_lock.lock)
#घोषणा hpios_dsplock_lock(obj)    cond_lock(&(obj)->dsp_lock)
#घोषणा hpios_dsplock_unlock(obj)  cond_unlock(&(obj)->dsp_lock)

#अगर_घोषित CONFIG_SND_DEBUG
#घोषणा HPI_BUILD_DEBUG
#पूर्ण_अगर

#घोषणा HPI_ALIST_LOCKING
#घोषणा hpios_alistlock_init(obj)    spin_lock_init(&((obj)->list_lock.lock))
#घोषणा hpios_alistlock_lock(obj) spin_lock(&((obj)->list_lock.lock))
#घोषणा hpios_alistlock_unlock(obj) spin_unlock(&((obj)->list_lock.lock))

काष्ठा snd_card;

/** pci drvdata poपूर्णांकs to an instance of this काष्ठा */
काष्ठा hpi_adapter अणु
	काष्ठा hpi_adapter_obj *adapter;
	काष्ठा snd_card *snd_card;

	पूर्णांक irq;
	पूर्णांक पूर्णांकerrupt_mode;
	व्योम (*पूर्णांकerrupt_callback) (काष्ठा hpi_adapter *);

	/* mutex prevents contention क्रम one card
	   between multiple user programs (via ioctl) */
	काष्ठा mutex mutex;
	अक्षर *p_buffer;
	माप_प्रकार buffer_size;
पूर्ण;

#पूर्ण_अगर
