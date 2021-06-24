<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Exceet Electronics GmbH
 * Copyright (C) 2018 Bootlin
 *
 * Author:
 *	Peter Pan <peterpanकरोng@micron.com>
 *	Boris Brezillon <boris.brezillon@bootlin.com>
 */

#अगर_अघोषित __LINUX_SPI_MEM_H
#घोषणा __LINUX_SPI_MEM_H

#समावेश <linux/spi/spi.h>

#घोषणा SPI_MEM_OP_CMD(__opcode, __buswidth)			\
	अणु							\
		.buswidth = __buswidth,				\
		.opcode = __opcode,				\
		.nbytes = 1,					\
	पूर्ण

#घोषणा SPI_MEM_OP_ADDR(__nbytes, __val, __buswidth)		\
	अणु							\
		.nbytes = __nbytes,				\
		.val = __val,					\
		.buswidth = __buswidth,				\
	पूर्ण

#घोषणा SPI_MEM_OP_NO_ADDR	अणु पूर्ण

#घोषणा SPI_MEM_OP_DUMMY(__nbytes, __buswidth)			\
	अणु							\
		.nbytes = __nbytes,				\
		.buswidth = __buswidth,				\
	पूर्ण

#घोषणा SPI_MEM_OP_NO_DUMMY	अणु पूर्ण

#घोषणा SPI_MEM_OP_DATA_IN(__nbytes, __buf, __buswidth)		\
	अणु							\
		.dir = SPI_MEM_DATA_IN,				\
		.nbytes = __nbytes,				\
		.buf.in = __buf,				\
		.buswidth = __buswidth,				\
	पूर्ण

#घोषणा SPI_MEM_OP_DATA_OUT(__nbytes, __buf, __buswidth)	\
	अणु							\
		.dir = SPI_MEM_DATA_OUT,			\
		.nbytes = __nbytes,				\
		.buf.out = __buf,				\
		.buswidth = __buswidth,				\
	पूर्ण

#घोषणा SPI_MEM_OP_NO_DATA	अणु पूर्ण

/**
 * क्रमागत spi_mem_data_dir - describes the direction of a SPI memory data
 *			   transfer from the controller perspective
 * @SPI_MEM_NO_DATA: no data transferred
 * @SPI_MEM_DATA_IN: data coming from the SPI memory
 * @SPI_MEM_DATA_OUT: data sent to the SPI memory
 */
क्रमागत spi_mem_data_dir अणु
	SPI_MEM_NO_DATA,
	SPI_MEM_DATA_IN,
	SPI_MEM_DATA_OUT,
पूर्ण;

/**
 * काष्ठा spi_mem_op - describes a SPI memory operation
 * @cmd.nbytes: number of opcode bytes (only 1 or 2 are valid). The opcode is
 *		sent MSB-first.
 * @cmd.buswidth: number of IO lines used to transmit the command
 * @cmd.opcode: operation opcode
 * @cmd.dtr: whether the command opcode should be sent in DTR mode or not
 * @addr.nbytes: number of address bytes to send. Can be zero अगर the operation
 *		 करोes not need to send an address
 * @addr.buswidth: number of IO lines used to transmit the address cycles
 * @addr.dtr: whether the address should be sent in DTR mode or not
 * @addr.val: address value. This value is always sent MSB first on the bus.
 *	      Note that only @addr.nbytes are taken पूर्णांकo account in this
 *	      address value, so users should make sure the value fits in the
 *	      asचिन्हित number of bytes.
 * @dummy.nbytes: number of dummy bytes to send after an opcode or address. Can
 *		  be zero अगर the operation करोes not require dummy bytes
 * @dummy.buswidth: number of IO lanes used to transmit the dummy bytes
 * @dummy.dtr: whether the dummy bytes should be sent in DTR mode or not
 * @data.buswidth: number of IO lanes used to send/receive the data
 * @data.dtr: whether the data should be sent in DTR mode or not
 * @data.dir: direction of the transfer
 * @data.nbytes: number of data bytes to send/receive. Can be zero अगर the
 *		 operation करोes not involve transferring data
 * @data.buf.in: input buffer (must be DMA-able)
 * @data.buf.out: output buffer (must be DMA-able)
 */
काष्ठा spi_mem_op अणु
	काष्ठा अणु
		u8 nbytes;
		u8 buswidth;
		u8 dtr : 1;
		u16 opcode;
	पूर्ण cmd;

	काष्ठा अणु
		u8 nbytes;
		u8 buswidth;
		u8 dtr : 1;
		u64 val;
	पूर्ण addr;

	काष्ठा अणु
		u8 nbytes;
		u8 buswidth;
		u8 dtr : 1;
	पूर्ण dummy;

	काष्ठा अणु
		u8 buswidth;
		u8 dtr : 1;
		क्रमागत spi_mem_data_dir dir;
		अचिन्हित पूर्णांक nbytes;
		जोड़ अणु
			व्योम *in;
			स्थिर व्योम *out;
		पूर्ण buf;
	पूर्ण data;
पूर्ण;

#घोषणा SPI_MEM_OP(__cmd, __addr, __dummy, __data)		\
	अणु							\
		.cmd = __cmd,					\
		.addr = __addr,					\
		.dummy = __dummy,				\
		.data = __data,					\
	पूर्ण

/**
 * काष्ठा spi_mem_dirmap_info - Direct mapping inक्रमmation
 * @op_पंचांगpl: operation ढाँचा that should be used by the direct mapping when
 *	     the memory device is accessed
 * @offset: असलolute offset this direct mapping is poपूर्णांकing to
 * @length: length in byte of this direct mapping
 *
 * These inक्रमmation are used by the controller specअगरic implementation to know
 * the portion of memory that is directly mapped and the spi_mem_op that should
 * be used to access the device.
 * A direct mapping is only valid क्रम one direction (पढ़ो or ग_लिखो) and this
 * direction is directly encoded in the ->op_पंचांगpl.data.dir field.
 */
काष्ठा spi_mem_dirmap_info अणु
	काष्ठा spi_mem_op op_पंचांगpl;
	u64 offset;
	u64 length;
पूर्ण;

/**
 * काष्ठा spi_mem_dirmap_desc - Direct mapping descriptor
 * @mem: the SPI memory device this direct mapping is attached to
 * @info: inक्रमmation passed at direct mapping creation समय
 * @nodirmap: set to 1 अगर the SPI controller करोes not implement
 *	      ->mem_ops->dirmap_create() or when this function वापसed an
 *	      error. If @nodirmap is true, all spi_mem_dirmap_अणुपढ़ो,ग_लिखोपूर्ण()
 *	      calls will use spi_mem_exec_op() to access the memory. This is a
 *	      degraded mode that allows spi_mem drivers to use the same code
 *	      no matter whether the controller supports direct mapping or not
 * @priv: field poपूर्णांकing to controller specअगरic data
 *
 * Common part of a direct mapping descriptor. This object is created by
 * spi_mem_dirmap_create() and controller implementation of ->create_dirmap()
 * can create/attach direct mapping resources to the descriptor in the ->priv
 * field.
 */
काष्ठा spi_mem_dirmap_desc अणु
	काष्ठा spi_mem *mem;
	काष्ठा spi_mem_dirmap_info info;
	अचिन्हित पूर्णांक nodirmap;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा spi_mem - describes a SPI memory device
 * @spi: the underlying SPI device
 * @drvpriv: spi_mem_driver निजी data
 * @name: name of the SPI memory device
 *
 * Extra inक्रमmation that describe the SPI memory device and may be needed by
 * the controller to properly handle this device should be placed here.
 *
 * One example would be the device size since some controller expose their SPI
 * mem devices through a io-mapped region.
 */
काष्ठा spi_mem अणु
	काष्ठा spi_device *spi;
	व्योम *drvpriv;
	स्थिर अक्षर *name;
पूर्ण;

/**
 * काष्ठा spi_mem_set_drvdata() - attach driver निजी data to a SPI mem
 *				  device
 * @mem: memory device
 * @data: data to attach to the memory device
 */
अटल अंतरभूत व्योम spi_mem_set_drvdata(काष्ठा spi_mem *mem, व्योम *data)
अणु
	mem->drvpriv = data;
पूर्ण

/**
 * काष्ठा spi_mem_get_drvdata() - get driver निजी data attached to a SPI mem
 *				  device
 * @mem: memory device
 *
 * Return: the data attached to the mem device.
 */
अटल अंतरभूत व्योम *spi_mem_get_drvdata(काष्ठा spi_mem *mem)
अणु
	वापस mem->drvpriv;
पूर्ण

/**
 * काष्ठा spi_controller_mem_ops - SPI memory operations
 * @adjust_op_size: shrink the data xfer of an operation to match controller's
 *		    limitations (can be alignment of max RX/TX size
 *		    limitations)
 * @supports_op: check अगर an operation is supported by the controller
 * @exec_op: execute a SPI memory operation
 * @get_name: get a custom name क्रम the SPI mem device from the controller.
 *	      This might be needed अगर the controller driver has been ported
 *	      to use the SPI mem layer and a custom name is used to keep
 *	      mtdparts compatible.
 *	      Note that अगर the implementation of this function allocates memory
 *	      dynamically, then it should करो so with devm_xxx(), as we करोn't
 *	      have a ->मुक्त_name() function.
 * @dirmap_create: create a direct mapping descriptor that can later be used to
 *		   access the memory device. This method is optional
 * @dirmap_destroy: destroy a memory descriptor previous created by
 *		    ->dirmap_create()
 * @dirmap_पढ़ो: पढ़ो data from the memory device using the direct mapping
 *		 created by ->dirmap_create(). The function can वापस less
 *		 data than requested (क्रम example when the request is crossing
 *		 the currently mapped area), and the caller of
 *		 spi_mem_dirmap_पढ़ो() is responsible क्रम calling it again in
 *		 this हाल.
 * @dirmap_ग_लिखो: ग_लिखो data to the memory device using the direct mapping
 *		  created by ->dirmap_create(). The function can वापस less
 *		  data than requested (क्रम example when the request is crossing
 *		  the currently mapped area), and the caller of
 *		  spi_mem_dirmap_ग_लिखो() is responsible क्रम calling it again in
 *		  this हाल.
 *
 * This पूर्णांकerface should be implemented by SPI controllers providing an
 * high-level पूर्णांकerface to execute SPI memory operation, which is usually the
 * हाल क्रम QSPI controllers.
 *
 * Note on ->dirmap_अणुपढ़ो,ग_लिखोपूर्ण(): drivers should aव्योम accessing the direct
 * mapping from the CPU because करोing that can stall the CPU रुकोing क्रम the
 * SPI mem transaction to finish, and this will make real-समय मुख्यtainers
 * unhappy and might make your प्रणाली less reactive. Instead, drivers should
 * use DMA to access this direct mapping.
 */
काष्ठा spi_controller_mem_ops अणु
	पूर्णांक (*adjust_op_size)(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op);
	bool (*supports_op)(काष्ठा spi_mem *mem,
			    स्थिर काष्ठा spi_mem_op *op);
	पूर्णांक (*exec_op)(काष्ठा spi_mem *mem,
		       स्थिर काष्ठा spi_mem_op *op);
	स्थिर अक्षर *(*get_name)(काष्ठा spi_mem *mem);
	पूर्णांक (*dirmap_create)(काष्ठा spi_mem_dirmap_desc *desc);
	व्योम (*dirmap_destroy)(काष्ठा spi_mem_dirmap_desc *desc);
	sमाप_प्रकार (*dirmap_पढ़ो)(काष्ठा spi_mem_dirmap_desc *desc,
			       u64 offs, माप_प्रकार len, व्योम *buf);
	sमाप_प्रकार (*dirmap_ग_लिखो)(काष्ठा spi_mem_dirmap_desc *desc,
				u64 offs, माप_प्रकार len, स्थिर व्योम *buf);
पूर्ण;

/**
 * काष्ठा spi_mem_driver - SPI memory driver
 * @spidrv: inherit from a SPI driver
 * @probe: probe a SPI memory. Usually where detection/initialization takes
 *	   place
 * @हटाओ: हटाओ a SPI memory
 * @shutकरोwn: take appropriate action when the प्रणाली is shutकरोwn
 *
 * This is just a thin wrapper around a spi_driver. The core takes care of
 * allocating the spi_mem object and क्रमwarding the probe/हटाओ/shutकरोwn
 * request to the spi_mem_driver. The reason we use this wrapper is because
 * we might have to stuff more inक्रमmation पूर्णांकo the spi_mem काष्ठा to let
 * SPI controllers know more about the SPI memory they पूर्णांकeract with, and
 * having this पूर्णांकermediate layer allows us to करो that without adding more
 * useless fields to the spi_device object.
 */
काष्ठा spi_mem_driver अणु
	काष्ठा spi_driver spidrv;
	पूर्णांक (*probe)(काष्ठा spi_mem *mem);
	पूर्णांक (*हटाओ)(काष्ठा spi_mem *mem);
	व्योम (*shutकरोwn)(काष्ठा spi_mem *mem);
पूर्ण;

#अगर IS_ENABLED(CONFIG_SPI_MEM)
पूर्णांक spi_controller_dma_map_mem_op_data(काष्ठा spi_controller *ctlr,
				       स्थिर काष्ठा spi_mem_op *op,
				       काष्ठा sg_table *sg);

व्योम spi_controller_dma_unmap_mem_op_data(काष्ठा spi_controller *ctlr,
					  स्थिर काष्ठा spi_mem_op *op,
					  काष्ठा sg_table *sg);

bool spi_mem_शेष_supports_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op);

bool spi_mem_dtr_supports_op(काष्ठा spi_mem *mem,
			     स्थिर काष्ठा spi_mem_op *op);

#अन्यथा
अटल अंतरभूत पूर्णांक
spi_controller_dma_map_mem_op_data(काष्ठा spi_controller *ctlr,
				   स्थिर काष्ठा spi_mem_op *op,
				   काष्ठा sg_table *sg)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम
spi_controller_dma_unmap_mem_op_data(काष्ठा spi_controller *ctlr,
				     स्थिर काष्ठा spi_mem_op *op,
				     काष्ठा sg_table *sg)
अणु
पूर्ण

अटल अंतरभूत
bool spi_mem_शेष_supports_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
bool spi_mem_dtr_supports_op(काष्ठा spi_mem *mem,
			     स्थिर काष्ठा spi_mem_op *op)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPI_MEM */

पूर्णांक spi_mem_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op);

bool spi_mem_supports_op(काष्ठा spi_mem *mem,
			 स्थिर काष्ठा spi_mem_op *op);

पूर्णांक spi_mem_exec_op(काष्ठा spi_mem *mem,
		    स्थिर काष्ठा spi_mem_op *op);

स्थिर अक्षर *spi_mem_get_name(काष्ठा spi_mem *mem);

काष्ठा spi_mem_dirmap_desc *
spi_mem_dirmap_create(काष्ठा spi_mem *mem,
		      स्थिर काष्ठा spi_mem_dirmap_info *info);
व्योम spi_mem_dirmap_destroy(काष्ठा spi_mem_dirmap_desc *desc);
sमाप_प्रकार spi_mem_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
			    u64 offs, माप_प्रकार len, व्योम *buf);
sमाप_प्रकार spi_mem_dirmap_ग_लिखो(काष्ठा spi_mem_dirmap_desc *desc,
			     u64 offs, माप_प्रकार len, स्थिर व्योम *buf);
काष्ठा spi_mem_dirmap_desc *
devm_spi_mem_dirmap_create(काष्ठा device *dev, काष्ठा spi_mem *mem,
			   स्थिर काष्ठा spi_mem_dirmap_info *info);
व्योम devm_spi_mem_dirmap_destroy(काष्ठा device *dev,
				 काष्ठा spi_mem_dirmap_desc *desc);

पूर्णांक spi_mem_driver_रेजिस्टर_with_owner(काष्ठा spi_mem_driver *drv,
				       काष्ठा module *owner);

व्योम spi_mem_driver_unरेजिस्टर(काष्ठा spi_mem_driver *drv);

#घोषणा spi_mem_driver_रेजिस्टर(__drv)                                  \
	spi_mem_driver_रेजिस्टर_with_owner(__drv, THIS_MODULE)

#घोषणा module_spi_mem_driver(__drv)                                    \
	module_driver(__drv, spi_mem_driver_रेजिस्टर,                   \
		      spi_mem_driver_unरेजिस्टर)

#पूर्ण_अगर /* __LINUX_SPI_MEM_H */
