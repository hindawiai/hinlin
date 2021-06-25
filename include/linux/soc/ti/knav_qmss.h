<शैली गुरु>
/*
 * Keystone Navigator Queue Management Sub-System header
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 * Author:	Sandeep Nair <sandeep_n@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __SOC_TI_KNAV_QMSS_H__
#घोषणा __SOC_TI_KNAV_QMSS_H__

#समावेश <linux/err.h>
#समावेश <linux/समय.स>
#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/dma-mapping.h>

/* queue types */
#घोषणा KNAV_QUEUE_QPEND	((अचिन्हित)-2) /* पूर्णांकerruptible qpend queue */
#घोषणा KNAV_QUEUE_ACC		((अचिन्हित)-3) /* Accumulated queue */
#घोषणा KNAV_QUEUE_GP		((अचिन्हित)-4) /* General purpose queue */

/* queue flags */
#घोषणा KNAV_QUEUE_SHARED	0x0001		/* Queue can be shared */

/**
 * क्रमागत knav_queue_ctrl_cmd -	queue operations.
 * @KNAV_QUEUE_GET_ID:		Get the ID number क्रम an खोलो queue
 * @KNAV_QUEUE_FLUSH:		क्रमcibly empty a queue अगर possible
 * @KNAV_QUEUE_SET_NOTIFIER:	Set a notअगरier callback to a queue handle.
 * @KNAV_QUEUE_ENABLE_NOTIFY:	Enable notअगरier callback क्रम a queue handle.
 * @KNAV_QUEUE_DISABLE_NOTIFY:	Disable notअगरier callback क्रम a queue handle.
 * @KNAV_QUEUE_GET_COUNT:	Get number of queues.
 */
क्रमागत knav_queue_ctrl_cmd अणु
	KNAV_QUEUE_GET_ID,
	KNAV_QUEUE_FLUSH,
	KNAV_QUEUE_SET_NOTIFIER,
	KNAV_QUEUE_ENABLE_NOTIFY,
	KNAV_QUEUE_DISABLE_NOTIFY,
	KNAV_QUEUE_GET_COUNT
पूर्ण;

/* Queue notअगरier callback prototype */
प्रकार व्योम (*knav_queue_notअगरy_fn)(व्योम *arg);

/**
 * काष्ठा knav_queue_notअगरy_config:	Notअगरier configuration
 * @fn:					Notअगरier function
 * @fn_arg:				Notअगरier function arguments
 */
काष्ठा knav_queue_notअगरy_config अणु
	knav_queue_notअगरy_fn fn;
	व्योम *fn_arg;
पूर्ण;

व्योम *knav_queue_खोलो(स्थिर अक्षर *name, अचिन्हित id,
					अचिन्हित flags);
व्योम knav_queue_बंद(व्योम *qhandle);
पूर्णांक knav_queue_device_control(व्योम *qhandle,
				क्रमागत knav_queue_ctrl_cmd cmd,
				अचिन्हित दीर्घ arg);
dma_addr_t knav_queue_pop(व्योम *qhandle, अचिन्हित *size);
पूर्णांक knav_queue_push(व्योम *qhandle, dma_addr_t dma,
				अचिन्हित size, अचिन्हित flags);

व्योम *knav_pool_create(स्थिर अक्षर *name,
				पूर्णांक num_desc, पूर्णांक region_id);
व्योम knav_pool_destroy(व्योम *ph);
पूर्णांक knav_pool_count(व्योम *ph);
व्योम *knav_pool_desc_get(व्योम *ph);
व्योम knav_pool_desc_put(व्योम *ph, व्योम *desc);
पूर्णांक knav_pool_desc_map(व्योम *ph, व्योम *desc, अचिन्हित size,
					dma_addr_t *dma, अचिन्हित *dma_sz);
व्योम *knav_pool_desc_unmap(व्योम *ph, dma_addr_t dma, अचिन्हित dma_sz);
dma_addr_t knav_pool_desc_virt_to_dma(व्योम *ph, व्योम *virt);
व्योम *knav_pool_desc_dma_to_virt(व्योम *ph, dma_addr_t dma);
bool knav_qmss_device_पढ़ोy(व्योम);

#पूर्ण_अगर /* __SOC_TI_KNAV_QMSS_H__ */
