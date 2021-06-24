<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/drivers/misc/xillybus.h
 *
 * Copyright 2011 Xillybus Ltd, http://xillybus.com
 *
 * Header file क्रम the Xillybus FPGA/host framework.
 */

#अगर_अघोषित __XILLYBUS_H
#घोषणा __XILLYBUS_H

#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/cdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

काष्ठा xilly_endpoपूर्णांक_hardware;

काष्ठा xilly_buffer अणु
	व्योम *addr;
	dma_addr_t dma_addr;
	पूर्णांक end_offset; /* Counting elements, not bytes */
पूर्ण;

काष्ठा xilly_idt_handle अणु
	अचिन्हित अक्षर *chandesc;
	अचिन्हित अक्षर *idt;
	पूर्णांक entries;
पूर्ण;

/*
 * Read-ग_लिखो confusion: wr_* and rd_* notation sticks to FPGA view, so
 * wr_* buffers are those consumed by पढ़ो(), since the FPGA ग_लिखोs to them
 * and vice versa.
 */

काष्ठा xilly_channel अणु
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक chan_num;
	पूर्णांक log2_element_size;
	पूर्णांक seekable;

	काष्ठा xilly_buffer **wr_buffers; /* FPGA ग_लिखोs, driver पढ़ोs! */
	पूर्णांक num_wr_buffers;
	अचिन्हित पूर्णांक wr_buf_size; /* In bytes */
	पूर्णांक wr_fpga_buf_idx;
	पूर्णांक wr_host_buf_idx;
	पूर्णांक wr_host_buf_pos;
	पूर्णांक wr_empty;
	पूर्णांक wr_पढ़ोy; /* Signअगरicant only when wr_empty == 1 */
	पूर्णांक wr_sleepy;
	पूर्णांक wr_eof;
	पूर्णांक wr_hangup;
	spinlock_t wr_spinlock;
	काष्ठा mutex wr_mutex;
	रुको_queue_head_t wr_रुको;
	रुको_queue_head_t wr_पढ़ोy_रुको;
	पूर्णांक wr_ref_count;
	पूर्णांक wr_synchronous;
	पूर्णांक wr_allow_partial;
	पूर्णांक wr_exclusive_खोलो;
	पूर्णांक wr_supports_nonempty;

	काष्ठा xilly_buffer **rd_buffers; /* FPGA पढ़ोs, driver ग_लिखोs! */
	पूर्णांक num_rd_buffers;
	अचिन्हित पूर्णांक rd_buf_size; /* In bytes */
	पूर्णांक rd_fpga_buf_idx;
	पूर्णांक rd_host_buf_pos;
	पूर्णांक rd_host_buf_idx;
	पूर्णांक rd_full;
	spinlock_t rd_spinlock;
	काष्ठा mutex rd_mutex;
	रुको_queue_head_t rd_रुको;
	पूर्णांक rd_ref_count;
	पूर्णांक rd_allow_partial;
	पूर्णांक rd_synchronous;
	पूर्णांक rd_exclusive_खोलो;
	काष्ठा delayed_work rd_workitem;
	अचिन्हित अक्षर rd_leftovers[4];
पूर्ण;

काष्ठा xilly_endpoपूर्णांक अणु
	/*
	 * One of pdev and dev is always शून्य, and the other is a valid
	 * poपूर्णांकer, depending on the type of device
	 */
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;
	काष्ठा xilly_endpoपूर्णांक_hardware *ephw;

	काष्ठा list_head ep_list;
	पूर्णांक dma_using_dac; /* =1 अगर 64-bit DMA is used, =0 otherwise. */
	__iomem व्योम *रेजिस्टरs;
	पूर्णांक fatal_error;

	काष्ठा mutex रेजिस्टर_mutex;
	रुको_queue_head_t ep_रुको;

	/* Channels and message handling */
	काष्ठा cdev cdev;

	पूर्णांक major;
	पूर्णांक lowest_minor; /* Highest minor = lowest_minor + num_channels - 1 */

	पूर्णांक num_channels; /* EXCLUDING message buffer */
	काष्ठा xilly_channel **channels;
	पूर्णांक msg_counter;
	पूर्णांक failed_messages;
	पूर्णांक idtlen;

	u32 *msgbuf_addr;
	dma_addr_t msgbuf_dma_addr;
	अचिन्हित पूर्णांक msg_buf_size;
पूर्ण;

काष्ठा xilly_endpoपूर्णांक_hardware अणु
	काष्ठा module *owner;
	व्योम (*hw_sync_sgl_क्रम_cpu)(काष्ठा xilly_endpoपूर्णांक *,
				    dma_addr_t,
				    माप_प्रकार,
				    पूर्णांक);
	व्योम (*hw_sync_sgl_क्रम_device)(काष्ठा xilly_endpoपूर्णांक *,
				       dma_addr_t,
				       माप_प्रकार,
				       पूर्णांक);
	पूर्णांक (*map_single)(काष्ठा xilly_endpoपूर्णांक *,
			  व्योम *,
			  माप_प्रकार,
			  पूर्णांक,
			  dma_addr_t *);
पूर्ण;

काष्ठा xilly_mapping अणु
	व्योम *device;
	dma_addr_t dma_addr;
	माप_प्रकार size;
	पूर्णांक direction;
पूर्ण;

irqवापस_t xillybus_isr(पूर्णांक irq, व्योम *data);

काष्ठा xilly_endpoपूर्णांक *xillybus_init_endpoपूर्णांक(काष्ठा pci_dev *pdev,
					      काष्ठा device *dev,
					      काष्ठा xilly_endpoपूर्णांक_hardware
					      *ephw);

पूर्णांक xillybus_endpoपूर्णांक_discovery(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक);

व्योम xillybus_endpoपूर्णांक_हटाओ(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक);

#पूर्ण_अगर /* __XILLYBUS_H */
