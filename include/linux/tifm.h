<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  tअगरm.h - TI FlashMedia driver
 *
 *  Copyright (C) 2006 Alex Dubov <oakad@yahoo.com>
 */

#अगर_अघोषित _TIFM_H
#घोषणा _TIFM_H

#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>

/* Host रेजिस्टरs (relative to pci base address): */
क्रमागत अणु
	FM_SET_INTERRUPT_ENABLE   = 0x008,
	FM_CLEAR_INTERRUPT_ENABLE = 0x00c,
	FM_INTERRUPT_STATUS       = 0x014
पूर्ण;

/* Socket रेजिस्टरs (relative to socket base address): */
क्रमागत अणु
	SOCK_CONTROL                   = 0x004,
	SOCK_PRESENT_STATE             = 0x008,
	SOCK_DMA_ADDRESS               = 0x00c,
	SOCK_DMA_CONTROL               = 0x010,
	SOCK_DMA_FIFO_INT_ENABLE_SET   = 0x014,
	SOCK_DMA_FIFO_INT_ENABLE_CLEAR = 0x018,
	SOCK_DMA_FIFO_STATUS           = 0x020,
	SOCK_FIFO_CONTROL              = 0x024,
	SOCK_FIFO_PAGE_SIZE            = 0x028,
	SOCK_MMCSD_COMMAND             = 0x104,
	SOCK_MMCSD_ARG_LOW             = 0x108,
	SOCK_MMCSD_ARG_HIGH            = 0x10c,
	SOCK_MMCSD_CONFIG              = 0x110,
	SOCK_MMCSD_STATUS              = 0x114,
	SOCK_MMCSD_INT_ENABLE          = 0x118,
	SOCK_MMCSD_COMMAND_TO          = 0x11c,
	SOCK_MMCSD_DATA_TO             = 0x120,
	SOCK_MMCSD_DATA                = 0x124,
	SOCK_MMCSD_BLOCK_LEN           = 0x128,
	SOCK_MMCSD_NUM_BLOCKS          = 0x12c,
	SOCK_MMCSD_BUFFER_CONFIG       = 0x130,
	SOCK_MMCSD_SPI_CONFIG          = 0x134,
	SOCK_MMCSD_SDIO_MODE_CONFIG    = 0x138,
	SOCK_MMCSD_RESPONSE            = 0x144,
	SOCK_MMCSD_SDIO_SR             = 0x164,
	SOCK_MMCSD_SYSTEM_CONTROL      = 0x168,
	SOCK_MMCSD_SYSTEM_STATUS       = 0x16c,
	SOCK_MS_COMMAND                = 0x184,
	SOCK_MS_DATA                   = 0x188,
	SOCK_MS_STATUS                 = 0x18c,
	SOCK_MS_SYSTEM                 = 0x190,
	SOCK_FIFO_ACCESS               = 0x200
पूर्ण;

#घोषणा TIFM_CTRL_LED             0x00000040
#घोषणा TIFM_CTRL_FAST_CLK        0x00000100
#घोषणा TIFM_CTRL_POWER_MASK      0x00000007

#घोषणा TIFM_SOCK_STATE_OCCUPIED  0x00000008
#घोषणा TIFM_SOCK_STATE_POWERED   0x00000080

#घोषणा TIFM_FIFO_ENABLE          0x00000001
#घोषणा TIFM_FIFO_READY           0x00000001
#घोषणा TIFM_FIFO_MORE            0x00000008
#घोषणा TIFM_FIFO_INT_SETALL      0x0000ffff
#घोषणा TIFM_FIFO_INTMASK         0x00000005

#घोषणा TIFM_DMA_RESET            0x00000002
#घोषणा TIFM_DMA_TX               0x00008000
#घोषणा TIFM_DMA_EN               0x00000001
#घोषणा TIFM_DMA_TSIZE            0x0000007f

#घोषणा TIFM_TYPE_XD 1
#घोषणा TIFM_TYPE_MS 2
#घोषणा TIFM_TYPE_SD 3

काष्ठा tअगरm_device_id अणु
	अचिन्हित अक्षर type;
पूर्ण;

काष्ठा tअगरm_driver;
काष्ठा tअगरm_dev अणु
	अक्षर __iomem  *addr;
	spinlock_t    lock;
	अचिन्हित अक्षर type;
	अचिन्हित पूर्णांक  socket_id;

	व्योम          (*card_event)(काष्ठा tअगरm_dev *sock);
	व्योम          (*data_event)(काष्ठा tअगरm_dev *sock);

	काष्ठा device dev;
पूर्ण;

काष्ठा tअगरm_driver अणु
	काष्ठा tअगरm_device_id *id_table;
	पूर्णांक                   (*probe)(काष्ठा tअगरm_dev *dev);
	व्योम                  (*हटाओ)(काष्ठा tअगरm_dev *dev);
	पूर्णांक                   (*suspend)(काष्ठा tअगरm_dev *dev,
					 pm_message_t state);
	पूर्णांक                   (*resume)(काष्ठा tअगरm_dev *dev);

	काष्ठा device_driver  driver;
पूर्ण;

काष्ठा tअगरm_adapter अणु
	अक्षर __iomem        *addr;
	spinlock_t          lock;
	अचिन्हित पूर्णांक        irq_status;
	अचिन्हित पूर्णांक        socket_change_set;
	अचिन्हित पूर्णांक        id;
	अचिन्हित पूर्णांक        num_sockets;
	काष्ठा completion   *finish_me;

	काष्ठा work_काष्ठा  media_चयनer;
	काष्ठा device	    dev;

	व्योम                (*eject)(काष्ठा tअगरm_adapter *fm,
				     काष्ठा tअगरm_dev *sock);
	पूर्णांक                 (*has_ms_pअगर)(काष्ठा tअगरm_adapter *fm,
					  काष्ठा tअगरm_dev *sock);

	काष्ठा tअगरm_dev     *sockets[];
पूर्ण;

काष्ठा tअगरm_adapter *tअगरm_alloc_adapter(अचिन्हित पूर्णांक num_sockets,
					काष्ठा device *dev);
पूर्णांक tअगरm_add_adapter(काष्ठा tअगरm_adapter *fm);
व्योम tअगरm_हटाओ_adapter(काष्ठा tअगरm_adapter *fm);
व्योम tअगरm_मुक्त_adapter(काष्ठा tअगरm_adapter *fm);

व्योम tअगरm_मुक्त_device(काष्ठा device *dev);
काष्ठा tअगरm_dev *tअगरm_alloc_device(काष्ठा tअगरm_adapter *fm, अचिन्हित पूर्णांक id,
				   अचिन्हित अक्षर type);

पूर्णांक tअगरm_रेजिस्टर_driver(काष्ठा tअगरm_driver *drv);
व्योम tअगरm_unरेजिस्टर_driver(काष्ठा tअगरm_driver *drv);
व्योम tअगरm_eject(काष्ठा tअगरm_dev *sock);
पूर्णांक tअगरm_has_ms_pअगर(काष्ठा tअगरm_dev *sock);
पूर्णांक tअगरm_map_sg(काष्ठा tअगरm_dev *sock, काष्ठा scatterlist *sg, पूर्णांक nents,
		पूर्णांक direction);
व्योम tअगरm_unmap_sg(काष्ठा tअगरm_dev *sock, काष्ठा scatterlist *sg, पूर्णांक nents,
		   पूर्णांक direction);
व्योम tअगरm_queue_work(काष्ठा work_काष्ठा *work);

अटल अंतरभूत व्योम *tअगरm_get_drvdata(काष्ठा tअगरm_dev *dev)
अणु
	वापस dev_get_drvdata(&dev->dev);
पूर्ण

अटल अंतरभूत व्योम tअगरm_set_drvdata(काष्ठा tअगरm_dev *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->dev, data);
पूर्ण

#पूर्ण_अगर
