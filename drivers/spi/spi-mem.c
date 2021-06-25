<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Exceet Electronics GmbH
 * Copyright (C) 2018 Bootlin
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

#समावेश "internals.h"

#घोषणा SPI_MEM_MAX_BUSWIDTH		8

/**
 * spi_controller_dma_map_mem_op_data() - DMA-map the buffer attached to a
 *					  memory operation
 * @ctlr: the SPI controller requesting this dma_map()
 * @op: the memory operation containing the buffer to map
 * @sgt: a poपूर्णांकer to a non-initialized sg_table that will be filled by this
 *	 function
 *
 * Some controllers might want to करो DMA on the data buffer embedded in @op.
 * This helper prepares everything क्रम you and provides a पढ़ोy-to-use
 * sg_table. This function is not पूर्णांकended to be called from spi drivers.
 * Only SPI controller drivers should use it.
 * Note that the caller must ensure the memory region poपूर्णांकed by
 * op->data.buf.अणुin,outपूर्ण is DMA-able beक्रमe calling this function.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक spi_controller_dma_map_mem_op_data(काष्ठा spi_controller *ctlr,
				       स्थिर काष्ठा spi_mem_op *op,
				       काष्ठा sg_table *sgt)
अणु
	काष्ठा device *dmadev;

	अगर (!op->data.nbytes)
		वापस -EINVAL;

	अगर (op->data.dir == SPI_MEM_DATA_OUT && ctlr->dma_tx)
		dmadev = ctlr->dma_tx->device->dev;
	अन्यथा अगर (op->data.dir == SPI_MEM_DATA_IN && ctlr->dma_rx)
		dmadev = ctlr->dma_rx->device->dev;
	अन्यथा
		dmadev = ctlr->dev.parent;

	अगर (!dmadev)
		वापस -EINVAL;

	वापस spi_map_buf(ctlr, dmadev, sgt, op->data.buf.in, op->data.nbytes,
			   op->data.dir == SPI_MEM_DATA_IN ?
			   DMA_FROM_DEVICE : DMA_TO_DEVICE);
पूर्ण
EXPORT_SYMBOL_GPL(spi_controller_dma_map_mem_op_data);

/**
 * spi_controller_dma_unmap_mem_op_data() - DMA-unmap the buffer attached to a
 *					    memory operation
 * @ctlr: the SPI controller requesting this dma_unmap()
 * @op: the memory operation containing the buffer to unmap
 * @sgt: a poपूर्णांकer to an sg_table previously initialized by
 *	 spi_controller_dma_map_mem_op_data()
 *
 * Some controllers might want to करो DMA on the data buffer embedded in @op.
 * This helper prepares things so that the CPU can access the
 * op->data.buf.अणुin,outपूर्ण buffer again.
 *
 * This function is not पूर्णांकended to be called from SPI drivers. Only SPI
 * controller drivers should use it.
 *
 * This function should be called after the DMA operation has finished and is
 * only valid अगर the previous spi_controller_dma_map_mem_op_data() call
 * वापसed 0.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
व्योम spi_controller_dma_unmap_mem_op_data(काष्ठा spi_controller *ctlr,
					  स्थिर काष्ठा spi_mem_op *op,
					  काष्ठा sg_table *sgt)
अणु
	काष्ठा device *dmadev;

	अगर (!op->data.nbytes)
		वापस;

	अगर (op->data.dir == SPI_MEM_DATA_OUT && ctlr->dma_tx)
		dmadev = ctlr->dma_tx->device->dev;
	अन्यथा अगर (op->data.dir == SPI_MEM_DATA_IN && ctlr->dma_rx)
		dmadev = ctlr->dma_rx->device->dev;
	अन्यथा
		dmadev = ctlr->dev.parent;

	spi_unmap_buf(ctlr, dmadev, sgt,
		      op->data.dir == SPI_MEM_DATA_IN ?
		      DMA_FROM_DEVICE : DMA_TO_DEVICE);
पूर्ण
EXPORT_SYMBOL_GPL(spi_controller_dma_unmap_mem_op_data);

अटल पूर्णांक spi_check_buswidth_req(काष्ठा spi_mem *mem, u8 buswidth, bool tx)
अणु
	u32 mode = mem->spi->mode;

	चयन (buswidth) अणु
	हाल 1:
		वापस 0;

	हाल 2:
		अगर ((tx &&
		     (mode & (SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL))) ||
		    (!tx &&
		     (mode & (SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL))))
			वापस 0;

		अवरोध;

	हाल 4:
		अगर ((tx && (mode & (SPI_TX_QUAD | SPI_TX_OCTAL))) ||
		    (!tx && (mode & (SPI_RX_QUAD | SPI_RX_OCTAL))))
			वापस 0;

		अवरोध;

	हाल 8:
		अगर ((tx && (mode & SPI_TX_OCTAL)) ||
		    (!tx && (mode & SPI_RX_OCTAL)))
			वापस 0;

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल bool spi_mem_check_buswidth(काष्ठा spi_mem *mem,
				   स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (spi_check_buswidth_req(mem, op->cmd.buswidth, true))
		वापस false;

	अगर (op->addr.nbytes &&
	    spi_check_buswidth_req(mem, op->addr.buswidth, true))
		वापस false;

	अगर (op->dummy.nbytes &&
	    spi_check_buswidth_req(mem, op->dummy.buswidth, true))
		वापस false;

	अगर (op->data.dir != SPI_MEM_NO_DATA &&
	    spi_check_buswidth_req(mem, op->data.buswidth,
				   op->data.dir == SPI_MEM_DATA_OUT))
		वापस false;

	वापस true;
पूर्ण

bool spi_mem_dtr_supports_op(काष्ठा spi_mem *mem,
			     स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (op->cmd.nbytes != 2)
		वापस false;

	वापस spi_mem_check_buswidth(mem, op);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_dtr_supports_op);

bool spi_mem_शेष_supports_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (op->cmd.dtr || op->addr.dtr || op->dummy.dtr || op->data.dtr)
		वापस false;

	अगर (op->cmd.nbytes != 1)
		वापस false;

	वापस spi_mem_check_buswidth(mem, op);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_शेष_supports_op);

अटल bool spi_mem_buswidth_is_valid(u8 buswidth)
अणु
	अगर (hweight8(buswidth) > 1 || buswidth > SPI_MEM_MAX_BUSWIDTH)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक spi_mem_check_op(स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (!op->cmd.buswidth || !op->cmd.nbytes)
		वापस -EINVAL;

	अगर ((op->addr.nbytes && !op->addr.buswidth) ||
	    (op->dummy.nbytes && !op->dummy.buswidth) ||
	    (op->data.nbytes && !op->data.buswidth))
		वापस -EINVAL;

	अगर (!spi_mem_buswidth_is_valid(op->cmd.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->addr.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->dummy.buswidth) ||
	    !spi_mem_buswidth_is_valid(op->data.buswidth))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool spi_mem_पूर्णांकernal_supports_op(काष्ठा spi_mem *mem,
					 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_controller *ctlr = mem->spi->controller;

	अगर (ctlr->mem_ops && ctlr->mem_ops->supports_op)
		वापस ctlr->mem_ops->supports_op(mem, op);

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

/**
 * spi_mem_supports_op() - Check अगर a memory device and the controller it is
 *			   connected to support a specअगरic memory operation
 * @mem: the SPI memory
 * @op: the memory operation to check
 *
 * Some controllers are only supporting Single or Dual IOs, others might only
 * support specअगरic opcodes, or it can even be that the controller and device
 * both support Quad IOs but the hardware prevents you from using it because
 * only 2 IO lines are connected.
 *
 * This function checks whether a specअगरic operation is supported.
 *
 * Return: true अगर @op is supported, false otherwise.
 */
bool spi_mem_supports_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (spi_mem_check_op(op))
		वापस false;

	वापस spi_mem_पूर्णांकernal_supports_op(mem, op);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_supports_op);

अटल पूर्णांक spi_mem_access_start(काष्ठा spi_mem *mem)
अणु
	काष्ठा spi_controller *ctlr = mem->spi->controller;

	/*
	 * Flush the message queue beक्रमe executing our SPI memory
	 * operation to prevent preemption of regular SPI transfers.
	 */
	spi_flush_queue(ctlr);

	अगर (ctlr->स्वतः_runसमय_pm) अणु
		पूर्णांक ret;

		ret = pm_runसमय_get_sync(ctlr->dev.parent);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(ctlr->dev.parent);
			dev_err(&ctlr->dev, "Failed to power device: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&ctlr->bus_lock_mutex);
	mutex_lock(&ctlr->io_mutex);

	वापस 0;
पूर्ण

अटल व्योम spi_mem_access_end(काष्ठा spi_mem *mem)
अणु
	काष्ठा spi_controller *ctlr = mem->spi->controller;

	mutex_unlock(&ctlr->io_mutex);
	mutex_unlock(&ctlr->bus_lock_mutex);

	अगर (ctlr->स्वतः_runसमय_pm)
		pm_runसमय_put(ctlr->dev.parent);
पूर्ण

/**
 * spi_mem_exec_op() - Execute a memory operation
 * @mem: the SPI memory
 * @op: the memory operation to execute
 *
 * Executes a memory operation.
 *
 * This function first checks that @op is supported and then tries to execute
 * it.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक spi_mem_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	अचिन्हित पूर्णांक पंचांगpbufsize, xferpos = 0, totalxferlen = 0;
	काष्ठा spi_controller *ctlr = mem->spi->controller;
	काष्ठा spi_transfer xfers[4] = अणु पूर्ण;
	काष्ठा spi_message msg;
	u8 *पंचांगpbuf;
	पूर्णांक ret;

	ret = spi_mem_check_op(op);
	अगर (ret)
		वापस ret;

	अगर (!spi_mem_पूर्णांकernal_supports_op(mem, op))
		वापस -ENOTSUPP;

	अगर (ctlr->mem_ops && !mem->spi->cs_gpiod) अणु
		ret = spi_mem_access_start(mem);
		अगर (ret)
			वापस ret;

		ret = ctlr->mem_ops->exec_op(mem, op);

		spi_mem_access_end(mem);

		/*
		 * Some controllers only optimize specअगरic paths (typically the
		 * पढ़ो path) and expect the core to use the regular SPI
		 * पूर्णांकerface in other हालs.
		 */
		अगर (!ret || ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	पंचांगpbufsize = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;

	/*
	 * Allocate a buffer to transmit the CMD, ADDR cycles with kदो_स्मृति() so
	 * we're guaranteed that this buffer is DMA-able, as required by the
	 * SPI layer.
	 */
	पंचांगpbuf = kzalloc(पंचांगpbufsize, GFP_KERNEL | GFP_DMA);
	अगर (!पंचांगpbuf)
		वापस -ENOMEM;

	spi_message_init(&msg);

	पंचांगpbuf[0] = op->cmd.opcode;
	xfers[xferpos].tx_buf = पंचांगpbuf;
	xfers[xferpos].len = op->cmd.nbytes;
	xfers[xferpos].tx_nbits = op->cmd.buswidth;
	spi_message_add_tail(&xfers[xferpos], &msg);
	xferpos++;
	totalxferlen++;

	अगर (op->addr.nbytes) अणु
		पूर्णांक i;

		क्रम (i = 0; i < op->addr.nbytes; i++)
			पंचांगpbuf[i + 1] = op->addr.val >>
					(8 * (op->addr.nbytes - i - 1));

		xfers[xferpos].tx_buf = पंचांगpbuf + 1;
		xfers[xferpos].len = op->addr.nbytes;
		xfers[xferpos].tx_nbits = op->addr.buswidth;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->addr.nbytes;
	पूर्ण

	अगर (op->dummy.nbytes) अणु
		स_रखो(पंचांगpbuf + op->addr.nbytes + 1, 0xff, op->dummy.nbytes);
		xfers[xferpos].tx_buf = पंचांगpbuf + op->addr.nbytes + 1;
		xfers[xferpos].len = op->dummy.nbytes;
		xfers[xferpos].tx_nbits = op->dummy.buswidth;
		xfers[xferpos].dummy_data = 1;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->dummy.nbytes;
	पूर्ण

	अगर (op->data.nbytes) अणु
		अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
			xfers[xferpos].rx_buf = op->data.buf.in;
			xfers[xferpos].rx_nbits = op->data.buswidth;
		पूर्ण अन्यथा अणु
			xfers[xferpos].tx_buf = op->data.buf.out;
			xfers[xferpos].tx_nbits = op->data.buswidth;
		पूर्ण

		xfers[xferpos].len = op->data.nbytes;
		spi_message_add_tail(&xfers[xferpos], &msg);
		xferpos++;
		totalxferlen += op->data.nbytes;
	पूर्ण

	ret = spi_sync(mem->spi, &msg);

	kमुक्त(पंचांगpbuf);

	अगर (ret)
		वापस ret;

	अगर (msg.actual_length != totalxferlen)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_exec_op);

/**
 * spi_mem_get_name() - Return the SPI mem device name to be used by the
 *			upper layer अगर necessary
 * @mem: the SPI memory
 *
 * This function allows SPI mem users to retrieve the SPI mem device name.
 * It is useful अगर the upper layer needs to expose a custom name क्रम
 * compatibility reasons.
 *
 * Return: a string containing the name of the memory device to be used
 *	   by the SPI mem user
 */
स्थिर अक्षर *spi_mem_get_name(काष्ठा spi_mem *mem)
अणु
	वापस mem->name;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_get_name);

/**
 * spi_mem_adjust_op_size() - Adjust the data size of a SPI mem operation to
 *			      match controller limitations
 * @mem: the SPI memory
 * @op: the operation to adjust
 *
 * Some controllers have FIFO limitations and must split a data transfer
 * operation पूर्णांकo multiple ones, others require a specअगरic alignment क्रम
 * optimized accesses. This function allows SPI mem drivers to split a single
 * operation पूर्णांकo multiple sub-operations when required.
 *
 * Return: a negative error code अगर the controller can't properly adjust @op,
 *	   0 otherwise. Note that @op->data.nbytes will be updated अगर @op
 *	   can't be handled in a single step.
 */
पूर्णांक spi_mem_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	काष्ठा spi_controller *ctlr = mem->spi->controller;
	माप_प्रकार len;

	अगर (ctlr->mem_ops && ctlr->mem_ops->adjust_op_size)
		वापस ctlr->mem_ops->adjust_op_size(mem, op);

	अगर (!ctlr->mem_ops || !ctlr->mem_ops->exec_op) अणु
		len = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;

		अगर (len > spi_max_transfer_size(mem->spi))
			वापस -EINVAL;

		op->data.nbytes = min3((माप_प्रकार)op->data.nbytes,
				       spi_max_transfer_size(mem->spi),
				       spi_max_message_size(mem->spi) -
				       len);
		अगर (!op->data.nbytes)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_adjust_op_size);

अटल sमाप_प्रकार spi_mem_no_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
				      u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा spi_mem_op op = desc->info.op_पंचांगpl;
	पूर्णांक ret;

	op.addr.val = desc->info.offset + offs;
	op.data.buf.in = buf;
	op.data.nbytes = len;
	ret = spi_mem_adjust_op_size(desc->mem, &op);
	अगर (ret)
		वापस ret;

	ret = spi_mem_exec_op(desc->mem, &op);
	अगर (ret)
		वापस ret;

	वापस op.data.nbytes;
पूर्ण

अटल sमाप_प्रकार spi_mem_no_dirmap_ग_लिखो(काष्ठा spi_mem_dirmap_desc *desc,
				       u64 offs, माप_प्रकार len, स्थिर व्योम *buf)
अणु
	काष्ठा spi_mem_op op = desc->info.op_पंचांगpl;
	पूर्णांक ret;

	op.addr.val = desc->info.offset + offs;
	op.data.buf.out = buf;
	op.data.nbytes = len;
	ret = spi_mem_adjust_op_size(desc->mem, &op);
	अगर (ret)
		वापस ret;

	ret = spi_mem_exec_op(desc->mem, &op);
	अगर (ret)
		वापस ret;

	वापस op.data.nbytes;
पूर्ण

/**
 * spi_mem_dirmap_create() - Create a direct mapping descriptor
 * @mem: SPI mem device this direct mapping should be created क्रम
 * @info: direct mapping inक्रमmation
 *
 * This function is creating a direct mapping descriptor which can then be used
 * to access the memory using spi_mem_dirmap_पढ़ो() or spi_mem_dirmap_ग_लिखो().
 * If the SPI controller driver करोes not support direct mapping, this function
 * falls back to an implementation using spi_mem_exec_op(), so that the caller
 * करोesn't have to bother implementing a fallback on his own.
 *
 * Return: a valid poपूर्णांकer in हाल of success, and ERR_PTR() otherwise.
 */
काष्ठा spi_mem_dirmap_desc *
spi_mem_dirmap_create(काष्ठा spi_mem *mem,
		      स्थिर काष्ठा spi_mem_dirmap_info *info)
अणु
	काष्ठा spi_controller *ctlr = mem->spi->controller;
	काष्ठा spi_mem_dirmap_desc *desc;
	पूर्णांक ret = -ENOTSUPP;

	/* Make sure the number of address cycles is between 1 and 8 bytes. */
	अगर (!info->op_पंचांगpl.addr.nbytes || info->op_पंचांगpl.addr.nbytes > 8)
		वापस ERR_PTR(-EINVAL);

	/* data.dir should either be SPI_MEM_DATA_IN or SPI_MEM_DATA_OUT. */
	अगर (info->op_पंचांगpl.data.dir == SPI_MEM_NO_DATA)
		वापस ERR_PTR(-EINVAL);

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस ERR_PTR(-ENOMEM);

	desc->mem = mem;
	desc->info = *info;
	अगर (ctlr->mem_ops && ctlr->mem_ops->dirmap_create)
		ret = ctlr->mem_ops->dirmap_create(desc);

	अगर (ret) अणु
		desc->nodirmap = true;
		अगर (!spi_mem_supports_op(desc->mem, &desc->info.op_पंचांगpl))
			ret = -ENOTSUPP;
		अन्यथा
			ret = 0;
	पूर्ण

	अगर (ret) अणु
		kमुक्त(desc);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_dirmap_create);

/**
 * spi_mem_dirmap_destroy() - Destroy a direct mapping descriptor
 * @desc: the direct mapping descriptor to destroy
 *
 * This function destroys a direct mapping descriptor previously created by
 * spi_mem_dirmap_create().
 */
व्योम spi_mem_dirmap_destroy(काष्ठा spi_mem_dirmap_desc *desc)
अणु
	काष्ठा spi_controller *ctlr = desc->mem->spi->controller;

	अगर (!desc->nodirmap && ctlr->mem_ops && ctlr->mem_ops->dirmap_destroy)
		ctlr->mem_ops->dirmap_destroy(desc);

	kमुक्त(desc);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_dirmap_destroy);

अटल व्योम devm_spi_mem_dirmap_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा spi_mem_dirmap_desc *desc = *(काष्ठा spi_mem_dirmap_desc **)res;

	spi_mem_dirmap_destroy(desc);
पूर्ण

/**
 * devm_spi_mem_dirmap_create() - Create a direct mapping descriptor and attach
 *				  it to a device
 * @dev: device the dirmap desc will be attached to
 * @mem: SPI mem device this direct mapping should be created क्रम
 * @info: direct mapping inक्रमmation
 *
 * devm_ variant of the spi_mem_dirmap_create() function. See
 * spi_mem_dirmap_create() क्रम more details.
 *
 * Return: a valid poपूर्णांकer in हाल of success, and ERR_PTR() otherwise.
 */
काष्ठा spi_mem_dirmap_desc *
devm_spi_mem_dirmap_create(काष्ठा device *dev, काष्ठा spi_mem *mem,
			   स्थिर काष्ठा spi_mem_dirmap_info *info)
अणु
	काष्ठा spi_mem_dirmap_desc **ptr, *desc;

	ptr = devres_alloc(devm_spi_mem_dirmap_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	desc = spi_mem_dirmap_create(mem, info);
	अगर (IS_ERR(desc)) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = desc;
		devres_add(dev, ptr);
	पूर्ण

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_spi_mem_dirmap_create);

अटल पूर्णांक devm_spi_mem_dirmap_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा spi_mem_dirmap_desc **ptr = res;

	अगर (WARN_ON(!ptr || !*ptr))
		वापस 0;

	वापस *ptr == data;
पूर्ण

/**
 * devm_spi_mem_dirmap_destroy() - Destroy a direct mapping descriptor attached
 *				   to a device
 * @dev: device the dirmap desc is attached to
 * @desc: the direct mapping descriptor to destroy
 *
 * devm_ variant of the spi_mem_dirmap_destroy() function. See
 * spi_mem_dirmap_destroy() क्रम more details.
 */
व्योम devm_spi_mem_dirmap_destroy(काष्ठा device *dev,
				 काष्ठा spi_mem_dirmap_desc *desc)
अणु
	devres_release(dev, devm_spi_mem_dirmap_release,
		       devm_spi_mem_dirmap_match, desc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_spi_mem_dirmap_destroy);

/**
 * spi_mem_dirmap_पढ़ो() - Read data through a direct mapping
 * @desc: direct mapping descriptor
 * @offs: offset to start पढ़ोing from. Note that this is not an असलolute
 *	  offset, but the offset within the direct mapping which alपढ़ोy has
 *	  its own offset
 * @len: length in bytes
 * @buf: destination buffer. This buffer must be DMA-able
 *
 * This function पढ़ोs data from a memory device using a direct mapping
 * previously instantiated with spi_mem_dirmap_create().
 *
 * Return: the amount of data पढ़ो from the memory device or a negative error
 * code. Note that the वापसed size might be smaller than @len, and the caller
 * is responsible क्रम calling spi_mem_dirmap_पढ़ो() again when that happens.
 */
sमाप_प्रकार spi_mem_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
			    u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा spi_controller *ctlr = desc->mem->spi->controller;
	sमाप_प्रकार ret;

	अगर (desc->info.op_पंचांगpl.data.dir != SPI_MEM_DATA_IN)
		वापस -EINVAL;

	अगर (!len)
		वापस 0;

	अगर (desc->nodirmap) अणु
		ret = spi_mem_no_dirmap_पढ़ो(desc, offs, len, buf);
	पूर्ण अन्यथा अगर (ctlr->mem_ops && ctlr->mem_ops->dirmap_पढ़ो) अणु
		ret = spi_mem_access_start(desc->mem);
		अगर (ret)
			वापस ret;

		ret = ctlr->mem_ops->dirmap_पढ़ो(desc, offs, len, buf);

		spi_mem_access_end(desc->mem);
	पूर्ण अन्यथा अणु
		ret = -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_dirmap_पढ़ो);

/**
 * spi_mem_dirmap_ग_लिखो() - Write data through a direct mapping
 * @desc: direct mapping descriptor
 * @offs: offset to start writing from. Note that this is not an असलolute
 *	  offset, but the offset within the direct mapping which alपढ़ोy has
 *	  its own offset
 * @len: length in bytes
 * @buf: source buffer. This buffer must be DMA-able
 *
 * This function ग_लिखोs data to a memory device using a direct mapping
 * previously instantiated with spi_mem_dirmap_create().
 *
 * Return: the amount of data written to the memory device or a negative error
 * code. Note that the वापसed size might be smaller than @len, and the caller
 * is responsible क्रम calling spi_mem_dirmap_ग_लिखो() again when that happens.
 */
sमाप_प्रकार spi_mem_dirmap_ग_लिखो(काष्ठा spi_mem_dirmap_desc *desc,
			     u64 offs, माप_प्रकार len, स्थिर व्योम *buf)
अणु
	काष्ठा spi_controller *ctlr = desc->mem->spi->controller;
	sमाप_प्रकार ret;

	अगर (desc->info.op_पंचांगpl.data.dir != SPI_MEM_DATA_OUT)
		वापस -EINVAL;

	अगर (!len)
		वापस 0;

	अगर (desc->nodirmap) अणु
		ret = spi_mem_no_dirmap_ग_लिखो(desc, offs, len, buf);
	पूर्ण अन्यथा अगर (ctlr->mem_ops && ctlr->mem_ops->dirmap_ग_लिखो) अणु
		ret = spi_mem_access_start(desc->mem);
		अगर (ret)
			वापस ret;

		ret = ctlr->mem_ops->dirmap_ग_लिखो(desc, offs, len, buf);

		spi_mem_access_end(desc->mem);
	पूर्ण अन्यथा अणु
		ret = -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_dirmap_ग_लिखो);

अटल अंतरभूत काष्ठा spi_mem_driver *to_spi_mem_drv(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा spi_mem_driver, spidrv.driver);
पूर्ण

अटल पूर्णांक spi_mem_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mem_driver *memdrv = to_spi_mem_drv(spi->dev.driver);
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा spi_mem *mem;

	mem = devm_kzalloc(&spi->dev, माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	mem->spi = spi;

	अगर (ctlr->mem_ops && ctlr->mem_ops->get_name)
		mem->name = ctlr->mem_ops->get_name(mem);
	अन्यथा
		mem->name = dev_name(&spi->dev);

	अगर (IS_ERR_OR_शून्य(mem->name))
		वापस PTR_ERR_OR_ZERO(mem->name);

	spi_set_drvdata(spi, mem);

	वापस memdrv->probe(mem);
पूर्ण

अटल पूर्णांक spi_mem_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mem_driver *memdrv = to_spi_mem_drv(spi->dev.driver);
	काष्ठा spi_mem *mem = spi_get_drvdata(spi);

	अगर (memdrv->हटाओ)
		वापस memdrv->हटाओ(mem);

	वापस 0;
पूर्ण

अटल व्योम spi_mem_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mem_driver *memdrv = to_spi_mem_drv(spi->dev.driver);
	काष्ठा spi_mem *mem = spi_get_drvdata(spi);

	अगर (memdrv->shutकरोwn)
		memdrv->shutकरोwn(mem);
पूर्ण

/**
 * spi_mem_driver_रेजिस्टर_with_owner() - Register a SPI memory driver
 * @memdrv: the SPI memory driver to रेजिस्टर
 * @owner: the owner of this driver
 *
 * Registers a SPI memory driver.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */

पूर्णांक spi_mem_driver_रेजिस्टर_with_owner(काष्ठा spi_mem_driver *memdrv,
				       काष्ठा module *owner)
अणु
	memdrv->spidrv.probe = spi_mem_probe;
	memdrv->spidrv.हटाओ = spi_mem_हटाओ;
	memdrv->spidrv.shutकरोwn = spi_mem_shutकरोwn;

	वापस __spi_रेजिस्टर_driver(owner, &memdrv->spidrv);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_driver_रेजिस्टर_with_owner);

/**
 * spi_mem_driver_unरेजिस्टर_with_owner() - Unरेजिस्टर a SPI memory driver
 * @memdrv: the SPI memory driver to unरेजिस्टर
 *
 * Unरेजिस्टरs a SPI memory driver.
 */
व्योम spi_mem_driver_unरेजिस्टर(काष्ठा spi_mem_driver *memdrv)
अणु
	spi_unरेजिस्टर_driver(&memdrv->spidrv);
पूर्ण
EXPORT_SYMBOL_GPL(spi_mem_driver_unरेजिस्टर);
