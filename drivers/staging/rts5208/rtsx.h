<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_H
#घोषणा __REALTEK_RTSX_H

#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय64.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>

#घोषणा CR_DRIVER_NAME		"rts5208"

/*
 * macros क्रम easy use
 */
#घोषणा rtsx_ग_लिखोl(chip, reg, value) \
	ioग_लिखो32(value, (chip)->rtsx->remap_addr + reg)
#घोषणा rtsx_पढ़ोl(chip, reg) \
	ioपढ़ो32((chip)->rtsx->remap_addr + reg)
#घोषणा rtsx_ग_लिखोw(chip, reg, value) \
	ioग_लिखो16(value, (chip)->rtsx->remap_addr + reg)
#घोषणा rtsx_पढ़ोw(chip, reg) \
	ioपढ़ो16((chip)->rtsx->remap_addr + reg)
#घोषणा rtsx_ग_लिखोb(chip, reg, value) \
	ioग_लिखो8(value, (chip)->rtsx->remap_addr + reg)
#घोषणा rtsx_पढ़ोb(chip, reg) \
	ioपढ़ो8((chip)->rtsx->remap_addr + reg)

#घोषणा rtsx_पढ़ो_config_byte(chip, where, val) \
	pci_पढ़ो_config_byte((chip)->rtsx->pci, where, val)

#घोषणा rtsx_ग_लिखो_config_byte(chip, where, val) \
	pci_ग_लिखो_config_byte((chip)->rtsx->pci, where, val)

#घोषणा रुको_समयout_x(task_state, msecs)	\
करो अणु						\
	set_current_state((task_state));	\
	schedule_समयout((msecs) * HZ / 1000);	\
पूर्ण जबतक (0)
#घोषणा रुको_समयout(msecs)	रुको_समयout_x(TASK_INTERRUPTIBLE, (msecs))

#घोषणा STATE_TRANS_NONE	0
#घोषणा STATE_TRANS_CMD		1
#घोषणा STATE_TRANS_BUF		2
#घोषणा STATE_TRANS_SG		3

#घोषणा TRANS_NOT_READY		0
#घोषणा TRANS_RESULT_OK		1
#घोषणा TRANS_RESULT_FAIL	2

#घोषणा SCSI_LUN(srb)		((srb)->device->lun)

काष्ठा rtsx_chip;

काष्ठा rtsx_dev अणु
	काष्ठा pci_dev *pci;

	/* pci resources */
	अचिन्हित दीर्घ		addr;
	व्योम __iomem		*remap_addr;
	पूर्णांक irq;

	/* locks */
	spinlock_t		reg_lock;

	काष्ठा task_काष्ठा	*ctl_thपढ़ो;	 /* the control thपढ़ो   */
	काष्ठा task_काष्ठा	*polling_thपढ़ो; /* the polling thपढ़ो   */

	/* mutual exclusion and synchronization काष्ठाures */
	काष्ठा completion	cmnd_पढ़ोy;	 /* to sleep thपढ़ो on	    */
	काष्ठा completion	control_निकास;	 /* control thपढ़ो निकास	    */
	काष्ठा completion	polling_निकास;	 /* polling thपढ़ो निकास	    */
	काष्ठा completion	notअगरy;		 /* thपढ़ो begin/end	    */
	काष्ठा completion	scanning_करोne;	 /* रुको क्रम scan thपढ़ो    */

	रुको_queue_head_t	delay_रुको;	 /* रुको during scan, reset */
	काष्ठा mutex		dev_mutex;

	/* host reserved buffer */
	व्योम			*rtsx_resv_buf;
	dma_addr_t		rtsx_resv_buf_addr;

	अक्षर			trans_result;
	अक्षर			trans_state;

	काष्ठा completion	*करोne;
	/* Whether पूर्णांकerrupt handler should care card cd info */
	u32			check_card_cd;

	काष्ठा rtsx_chip	*chip;
पूर्ण;

/* Convert between rtsx_dev and the corresponding Scsi_Host */
अटल अंतरभूत काष्ठा Scsi_Host *rtsx_to_host(काष्ठा rtsx_dev *dev)
अणु
	वापस container_of((व्योम *)dev, काष्ठा Scsi_Host, hostdata);
पूर्ण

अटल अंतरभूत काष्ठा rtsx_dev *host_to_rtsx(काष्ठा Scsi_Host *host)
अणु
	वापस (काष्ठा rtsx_dev *)host->hostdata;
पूर्ण

/*
 * The scsi_lock() and scsi_unlock() macros protect the sm_state and the
 * single queue element srb क्रम ग_लिखो access
 */
#घोषणा scsi_unlock(host)	spin_unlock_irq(host->host_lock)
#घोषणा scsi_lock(host)		spin_lock_irq(host->host_lock)

#घोषणा lock_state(chip)	spin_lock_irq(&((chip)->rtsx->reg_lock))
#घोषणा unlock_state(chip)	spin_unlock_irq(&((chip)->rtsx->reg_lock))

/* काष्ठा scsi_cmnd transfer buffer access utilities */
क्रमागत xfer_buf_dir	अणुTO_XFER_BUF, FROM_XFER_BUFपूर्ण;

#समावेश "rtsx_chip.h"
#समावेश "rtsx_transport.h"
#समावेश "rtsx_scsi.h"
#समावेश "rtsx_card.h"
#समावेश "rtsx_sys.h"
#समावेश "general.h"

#पूर्ण_अगर  /* __REALTEK_RTSX_H */
