<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based on m25p80.c, by Mike Lavender (mike@steroidmicros.com), with
 * influence from lart.c (Abraham Van Der Merwe) and mtd_dataflash.c
 *
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/math64.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

/* Define max बार to check status रेजिस्टर beक्रमe we give up. */

/*
 * For everything but full-chip erase; probably could be much smaller, but kept
 * around क्रम safety क्रम now
 */
#घोषणा DEFAULT_READY_WAIT_JIFFIES		(40UL * HZ)

/*
 * For full-chip erase, calibrated to a 2MB flash (M25P16); should be scaled up
 * क्रम larger flash
 */
#घोषणा CHIP_ERASE_2MB_READY_WAIT_JIFFIES	(40UL * HZ)

#घोषणा SPI_NOR_MAX_ADDR_WIDTH	4

#घोषणा SPI_NOR_SRST_SLEEP_MIN 200
#घोषणा SPI_NOR_SRST_SLEEP_MAX 400

/**
 * spi_nor_get_cmd_ext() - Get the command opcode extension based on the
 *			   extension type.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @op:			poपूर्णांकer to the 'struct spi_mem_op' whose properties
 *			need to be initialized.
 *
 * Right now, only "repeat" and "invert" are supported.
 *
 * Return: The opcode extension.
 */
अटल u8 spi_nor_get_cmd_ext(स्थिर काष्ठा spi_nor *nor,
			      स्थिर काष्ठा spi_mem_op *op)
अणु
	चयन (nor->cmd_ext_type) अणु
	हाल SPI_NOR_EXT_INVERT:
		वापस ~op->cmd.opcode;

	हाल SPI_NOR_EXT_REPEAT:
		वापस op->cmd.opcode;

	शेष:
		dev_err(nor->dev, "Unknown command extension type\n");
		वापस 0;
	पूर्ण
पूर्ण

/**
 * spi_nor_spimem_setup_op() - Set up common properties of a spi-mem op.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @op:			poपूर्णांकer to the 'struct spi_mem_op' whose properties
 *			need to be initialized.
 * @proto:		the protocol from which the properties need to be set.
 */
व्योम spi_nor_spimem_setup_op(स्थिर काष्ठा spi_nor *nor,
			     काष्ठा spi_mem_op *op,
			     स्थिर क्रमागत spi_nor_protocol proto)
अणु
	u8 ext;

	op->cmd.buswidth = spi_nor_get_protocol_inst_nbits(proto);

	अगर (op->addr.nbytes)
		op->addr.buswidth = spi_nor_get_protocol_addr_nbits(proto);

	अगर (op->dummy.nbytes)
		op->dummy.buswidth = spi_nor_get_protocol_addr_nbits(proto);

	अगर (op->data.nbytes)
		op->data.buswidth = spi_nor_get_protocol_data_nbits(proto);

	अगर (spi_nor_protocol_is_dtr(proto)) अणु
		/*
		 * SPIMEM supports mixed DTR modes, but right now we can only
		 * have all phases either DTR or STR. IOW, SPIMEM can have
		 * something like 4S-4D-4D, but SPI NOR can't. So, set all 4
		 * phases to either DTR or STR.
		 */
		op->cmd.dtr = true;
		op->addr.dtr = true;
		op->dummy.dtr = true;
		op->data.dtr = true;

		/* 2 bytes per घड़ी cycle in DTR mode. */
		op->dummy.nbytes *= 2;

		ext = spi_nor_get_cmd_ext(nor, op);
		op->cmd.opcode = (op->cmd.opcode << 8) | ext;
		op->cmd.nbytes = 2;
	पूर्ण
पूर्ण

/**
 * spi_nor_spimem_bounce() - check अगर a bounce buffer is needed क्रम the data
 *                           transfer
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @op:         poपूर्णांकer to 'struct spi_mem_op' ढाँचा क्रम transfer
 *
 * If we have to use the bounce buffer, the data field in @op will be updated.
 *
 * Return: true अगर the bounce buffer is needed, false अगर not
 */
अटल bool spi_nor_spimem_bounce(काष्ठा spi_nor *nor, काष्ठा spi_mem_op *op)
अणु
	/* op->data.buf.in occupies the same memory as op->data.buf.out */
	अगर (object_is_on_stack(op->data.buf.in) ||
	    !virt_addr_valid(op->data.buf.in)) अणु
		अगर (op->data.nbytes > nor->bouncebuf_size)
			op->data.nbytes = nor->bouncebuf_size;
		op->data.buf.in = nor->bouncebuf;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * spi_nor_spimem_exec_op() - execute a memory operation
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @op:         poपूर्णांकer to 'struct spi_mem_op' ढाँचा क्रम transfer
 *
 * Return: 0 on success, -error otherwise.
 */
अटल पूर्णांक spi_nor_spimem_exec_op(काष्ठा spi_nor *nor, काष्ठा spi_mem_op *op)
अणु
	पूर्णांक error;

	error = spi_mem_adjust_op_size(nor->spimem, op);
	अगर (error)
		वापस error;

	वापस spi_mem_exec_op(nor->spimem, op);
पूर्ण

अटल पूर्णांक spi_nor_controller_ops_पढ़ो_reg(काष्ठा spi_nor *nor, u8 opcode,
					   u8 *buf, माप_प्रकार len)
अणु
	अगर (spi_nor_protocol_is_dtr(nor->reg_proto))
		वापस -EOPNOTSUPP;

	वापस nor->controller_ops->पढ़ो_reg(nor, opcode, buf, len);
पूर्ण

अटल पूर्णांक spi_nor_controller_ops_ग_लिखो_reg(काष्ठा spi_nor *nor, u8 opcode,
					    स्थिर u8 *buf, माप_प्रकार len)
अणु
	अगर (spi_nor_protocol_is_dtr(nor->reg_proto))
		वापस -EOPNOTSUPP;

	वापस nor->controller_ops->ग_लिखो_reg(nor, opcode, buf, len);
पूर्ण

अटल पूर्णांक spi_nor_controller_ops_erase(काष्ठा spi_nor *nor, loff_t offs)
अणु
	अगर (spi_nor_protocol_is_dtr(nor->ग_लिखो_proto))
		वापस -EOPNOTSUPP;

	वापस nor->controller_ops->erase(nor, offs);
पूर्ण

/**
 * spi_nor_spimem_पढ़ो_data() - पढ़ो data from flash's memory region via
 *                              spi-mem
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @from:       offset to पढ़ो from
 * @len:        number of bytes to पढ़ो
 * @buf:        poपूर्णांकer to dst buffer
 *
 * Return: number of bytes पढ़ो successfully, -त्रुटि_सं otherwise
 */
अटल sमाप_प्रकार spi_nor_spimem_पढ़ो_data(काष्ठा spi_nor *nor, loff_t from,
					माप_प्रकार len, u8 *buf)
अणु
	काष्ठा spi_mem_op op =
		SPI_MEM_OP(SPI_MEM_OP_CMD(nor->पढ़ो_opcode, 0),
			   SPI_MEM_OP_ADDR(nor->addr_width, from, 0),
			   SPI_MEM_OP_DUMMY(nor->पढ़ो_dummy, 0),
			   SPI_MEM_OP_DATA_IN(len, buf, 0));
	bool usebouncebuf;
	sमाप_प्रकार nbytes;
	पूर्णांक error;

	spi_nor_spimem_setup_op(nor, &op, nor->पढ़ो_proto);

	/* convert the dummy cycles to the number of bytes */
	op.dummy.nbytes = (nor->पढ़ो_dummy * op.dummy.buswidth) / 8;
	अगर (spi_nor_protocol_is_dtr(nor->पढ़ो_proto))
		op.dummy.nbytes *= 2;

	usebouncebuf = spi_nor_spimem_bounce(nor, &op);

	अगर (nor->dirmap.rdesc) अणु
		nbytes = spi_mem_dirmap_पढ़ो(nor->dirmap.rdesc, op.addr.val,
					     op.data.nbytes, op.data.buf.in);
	पूर्ण अन्यथा अणु
		error = spi_nor_spimem_exec_op(nor, &op);
		अगर (error)
			वापस error;
		nbytes = op.data.nbytes;
	पूर्ण

	अगर (usebouncebuf && nbytes > 0)
		स_नकल(buf, op.data.buf.in, nbytes);

	वापस nbytes;
पूर्ण

/**
 * spi_nor_पढ़ो_data() - पढ़ो data from flash memory
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @from:       offset to पढ़ो from
 * @len:        number of bytes to पढ़ो
 * @buf:        poपूर्णांकer to dst buffer
 *
 * Return: number of bytes पढ़ो successfully, -त्रुटि_सं otherwise
 */
sमाप_प्रकार spi_nor_पढ़ो_data(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len, u8 *buf)
अणु
	अगर (nor->spimem)
		वापस spi_nor_spimem_पढ़ो_data(nor, from, len, buf);

	वापस nor->controller_ops->पढ़ो(nor, from, len, buf);
पूर्ण

/**
 * spi_nor_spimem_ग_लिखो_data() - ग_लिखो data to flash memory via
 *                               spi-mem
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @to:         offset to ग_लिखो to
 * @len:        number of bytes to ग_लिखो
 * @buf:        poपूर्णांकer to src buffer
 *
 * Return: number of bytes written successfully, -त्रुटि_सं otherwise
 */
अटल sमाप_प्रकार spi_nor_spimem_ग_लिखो_data(काष्ठा spi_nor *nor, loff_t to,
					 माप_प्रकार len, स्थिर u8 *buf)
अणु
	काष्ठा spi_mem_op op =
		SPI_MEM_OP(SPI_MEM_OP_CMD(nor->program_opcode, 0),
			   SPI_MEM_OP_ADDR(nor->addr_width, to, 0),
			   SPI_MEM_OP_NO_DUMMY,
			   SPI_MEM_OP_DATA_OUT(len, buf, 0));
	sमाप_प्रकार nbytes;
	पूर्णांक error;

	अगर (nor->program_opcode == SPINOR_OP_AAI_WP && nor->sst_ग_लिखो_second)
		op.addr.nbytes = 0;

	spi_nor_spimem_setup_op(nor, &op, nor->ग_लिखो_proto);

	अगर (spi_nor_spimem_bounce(nor, &op))
		स_नकल(nor->bouncebuf, buf, op.data.nbytes);

	अगर (nor->dirmap.wdesc) अणु
		nbytes = spi_mem_dirmap_ग_लिखो(nor->dirmap.wdesc, op.addr.val,
					      op.data.nbytes, op.data.buf.out);
	पूर्ण अन्यथा अणु
		error = spi_nor_spimem_exec_op(nor, &op);
		अगर (error)
			वापस error;
		nbytes = op.data.nbytes;
	पूर्ण

	वापस nbytes;
पूर्ण

/**
 * spi_nor_ग_लिखो_data() - ग_लिखो data to flash memory
 * @nor:        poपूर्णांकer to 'struct spi_nor'
 * @to:         offset to ग_लिखो to
 * @len:        number of bytes to ग_लिखो
 * @buf:        poपूर्णांकer to src buffer
 *
 * Return: number of bytes written successfully, -त्रुटि_सं otherwise
 */
sमाप_प्रकार spi_nor_ग_लिखो_data(काष्ठा spi_nor *nor, loff_t to, माप_प्रकार len,
			   स्थिर u8 *buf)
अणु
	अगर (nor->spimem)
		वापस spi_nor_spimem_ग_लिखो_data(nor, to, len, buf);

	वापस nor->controller_ops->ग_लिखो(nor, to, len, buf);
पूर्ण

/**
 * spi_nor_ग_लिखो_enable() - Set ग_लिखो enable latch with Write Enable command.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_enable(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WREN, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_WREN,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d on Write Enable\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_ग_लिखो_disable() - Send Write Disable inकाष्ठाion to the chip.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_disable(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRDI, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_WRDI,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d on Write Disable\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_पढ़ो_sr() - Read the Status Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @sr:		poपूर्णांकer to a DMA-able buffer where the value of the
 *              Status Register will be written. Should be at least 2 bytes.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_पढ़ो_sr(काष्ठा spi_nor *nor, u8 *sr)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(1, sr, 0));

		अगर (nor->reg_proto == SNOR_PROTO_8_8_8_DTR) अणु
			op.addr.nbytes = nor->params->rdsr_addr_nbytes;
			op.dummy.nbytes = nor->params->rdsr_dummy;
			/*
			 * We करोn't want to पढ़ो only one byte in DTR mode. So,
			 * पढ़ो 2 and then discard the second byte.
			 */
			op.data.nbytes = 2;
		पूर्ण

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_पढ़ो_reg(nor, SPINOR_OP_RDSR, sr,
						      1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d reading SR\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_पढ़ो_fsr() - Read the Flag Status Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'
 * @fsr:	poपूर्णांकer to a DMA-able buffer where the value of the
 *              Flag Status Register will be written. Should be at least 2
 *              bytes.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_पढ़ो_fsr(काष्ठा spi_nor *nor, u8 *fsr)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDFSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(1, fsr, 0));

		अगर (nor->reg_proto == SNOR_PROTO_8_8_8_DTR) अणु
			op.addr.nbytes = nor->params->rdsr_addr_nbytes;
			op.dummy.nbytes = nor->params->rdsr_dummy;
			/*
			 * We करोn't want to पढ़ो only one byte in DTR mode. So,
			 * पढ़ो 2 and then discard the second byte.
			 */
			op.data.nbytes = 2;
		पूर्ण

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_पढ़ो_reg(nor, SPINOR_OP_RDFSR, fsr,
						      1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d reading FSR\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_पढ़ो_cr() - Read the Configuration Register using the
 * SPINOR_OP_RDCR (35h) command.
 * @nor:	poपूर्णांकer to 'struct spi_nor'
 * @cr:		poपूर्णांकer to a DMA-able buffer where the value of the
 *              Configuration Register will be written.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_पढ़ो_cr(काष्ठा spi_nor *nor, u8 *cr)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDCR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(1, cr, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_पढ़ो_reg(nor, SPINOR_OP_RDCR, cr,
						      1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d reading CR\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_set_4byte_addr_mode() - Enter/Exit 4-byte address mode.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @enable:	true to enter the 4-byte address mode, false to निकास the 4-byte
 *		address mode.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_set_4byte_addr_mode(काष्ठा spi_nor *nor, bool enable)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(enable ?
						  SPINOR_OP_EN4B :
						  SPINOR_OP_EX4B,
						  0),
				  SPI_MEM_OP_NO_ADDR,
				  SPI_MEM_OP_NO_DUMMY,
				  SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor,
						       enable ? SPINOR_OP_EN4B :
								SPINOR_OP_EX4B,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d setting 4-byte mode\n", ret);

	वापस ret;
पूर्ण

/**
 * spansion_set_4byte_addr_mode() - Set 4-byte address mode क्रम Spansion
 * flashes.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @enable:	true to enter the 4-byte address mode, false to निकास the 4-byte
 *		address mode.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spansion_set_4byte_addr_mode(काष्ठा spi_nor *nor, bool enable)
अणु
	पूर्णांक ret;

	nor->bouncebuf[0] = enable << 7;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_BRWR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(1, nor->bouncebuf, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_BRWR,
						       nor->bouncebuf, 1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d setting 4-byte mode\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_ग_लिखो_ear() - Write Extended Address Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @ear:	value to ग_लिखो to the Extended Address Register.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_ear(काष्ठा spi_nor *nor, u8 ear)
अणु
	पूर्णांक ret;

	nor->bouncebuf[0] = ear;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WREAR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(1, nor->bouncebuf, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_WREAR,
						       nor->bouncebuf, 1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d writing EAR\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_xपढ़ो_sr() - Read the Status Register on S3AN flashes.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @sr:		poपूर्णांकer to a DMA-able buffer where the value of the
 *              Status Register will be written.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_xपढ़ो_sr(काष्ठा spi_nor *nor, u8 *sr)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_XRDSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(1, sr, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_पढ़ो_reg(nor, SPINOR_OP_XRDSR, sr,
						      1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d reading XRDSR\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_xsr_पढ़ोy() - Query the Status Register of the S3AN flash to see अगर
 * the flash is पढ़ोy क्रम new commands.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 1 अगर पढ़ोy, 0 अगर not पढ़ोy, -त्रुटि_सं on errors.
 */
अटल पूर्णांक spi_nor_xsr_पढ़ोy(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	ret = spi_nor_xपढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	वापस !!(nor->bouncebuf[0] & XSR_RDY);
पूर्ण

/**
 * spi_nor_clear_sr() - Clear the Status Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 */
अटल व्योम spi_nor_clear_sr(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CLSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_CLSR,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d clearing SR\n", ret);
पूर्ण

/**
 * spi_nor_sr_पढ़ोy() - Query the Status Register to see अगर the flash is पढ़ोy
 * क्रम new commands.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 1 अगर पढ़ोy, 0 अगर not पढ़ोy, -त्रुटि_सं on errors.
 */
अटल पूर्णांक spi_nor_sr_पढ़ोy(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);

	अगर (ret)
		वापस ret;

	अगर (nor->flags & SNOR_F_USE_CLSR &&
	    nor->bouncebuf[0] & (SR_E_ERR | SR_P_ERR)) अणु
		अगर (nor->bouncebuf[0] & SR_E_ERR)
			dev_err(nor->dev, "Erase Error occurred\n");
		अन्यथा
			dev_err(nor->dev, "Programming Error occurred\n");

		spi_nor_clear_sr(nor);

		/*
		 * WEL bit reमुख्यs set to one when an erase or page program
		 * error occurs. Issue a Write Disable command to protect
		 * against inadvertent ग_लिखोs that can possibly corrupt the
		 * contents of the memory.
		 */
		ret = spi_nor_ग_लिखो_disable(nor);
		अगर (ret)
			वापस ret;

		वापस -EIO;
	पूर्ण

	वापस !(nor->bouncebuf[0] & SR_WIP);
पूर्ण

/**
 * spi_nor_clear_fsr() - Clear the Flag Status Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 */
अटल व्योम spi_nor_clear_fsr(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CLFSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_CLFSR,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d clearing FSR\n", ret);
पूर्ण

/**
 * spi_nor_fsr_पढ़ोy() - Query the Flag Status Register to see अगर the flash is
 * पढ़ोy क्रम new commands.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 1 अगर पढ़ोy, 0 अगर not पढ़ोy, -त्रुटि_सं on errors.
 */
अटल पूर्णांक spi_nor_fsr_पढ़ोy(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret = spi_nor_पढ़ो_fsr(nor, nor->bouncebuf);

	अगर (ret)
		वापस ret;

	अगर (nor->bouncebuf[0] & (FSR_E_ERR | FSR_P_ERR)) अणु
		अगर (nor->bouncebuf[0] & FSR_E_ERR)
			dev_err(nor->dev, "Erase operation failed.\n");
		अन्यथा
			dev_err(nor->dev, "Program operation failed.\n");

		अगर (nor->bouncebuf[0] & FSR_PT_ERR)
			dev_err(nor->dev,
			"Attempted to modify a protected sector.\n");

		spi_nor_clear_fsr(nor);

		/*
		 * WEL bit reमुख्यs set to one when an erase or page program
		 * error occurs. Issue a Write Disable command to protect
		 * against inadvertent ग_लिखोs that can possibly corrupt the
		 * contents of the memory.
		 */
		ret = spi_nor_ग_लिखो_disable(nor);
		अगर (ret)
			वापस ret;

		वापस -EIO;
	पूर्ण

	वापस !!(nor->bouncebuf[0] & FSR_READY);
पूर्ण

/**
 * spi_nor_पढ़ोy() - Query the flash to see अगर it is पढ़ोy क्रम new commands.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 1 अगर पढ़ोy, 0 अगर not पढ़ोy, -त्रुटि_सं on errors.
 */
अटल पूर्णांक spi_nor_पढ़ोy(काष्ठा spi_nor *nor)
अणु
	पूर्णांक sr, fsr;

	अगर (nor->flags & SNOR_F_READY_XSR_RDY)
		sr = spi_nor_xsr_पढ़ोy(nor);
	अन्यथा
		sr = spi_nor_sr_पढ़ोy(nor);
	अगर (sr < 0)
		वापस sr;
	fsr = nor->flags & SNOR_F_USE_FSR ? spi_nor_fsr_पढ़ोy(nor) : 1;
	अगर (fsr < 0)
		वापस fsr;
	वापस sr && fsr;
पूर्ण

/**
 * spi_nor_रुको_till_पढ़ोy_with_समयout() - Service routine to पढ़ो the
 * Status Register until पढ़ोy, or समयout occurs.
 * @nor:		poपूर्णांकer to "struct spi_nor".
 * @समयout_jअगरfies:	jअगरfies to रुको until समयout.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_रुको_till_पढ़ोy_with_समयout(काष्ठा spi_nor *nor,
						अचिन्हित दीर्घ समयout_jअगरfies)
अणु
	अचिन्हित दीर्घ deadline;
	पूर्णांक समयout = 0, ret;

	deadline = jअगरfies + समयout_jअगरfies;

	जबतक (!समयout) अणु
		अगर (समय_after_eq(jअगरfies, deadline))
			समयout = 1;

		ret = spi_nor_पढ़ोy(nor);
		अगर (ret < 0)
			वापस ret;
		अगर (ret)
			वापस 0;

		cond_resched();
	पूर्ण

	dev_dbg(nor->dev, "flash operation timed out\n");

	वापस -ETIMEDOUT;
पूर्ण

/**
 * spi_nor_रुको_till_पढ़ोy() - Wait क्रम a predefined amount of समय क्रम the
 * flash to be पढ़ोy, or समयout occurs.
 * @nor:	poपूर्णांकer to "struct spi_nor".
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_रुको_till_पढ़ोy(काष्ठा spi_nor *nor)
अणु
	वापस spi_nor_रुको_till_पढ़ोy_with_समयout(nor,
						    DEFAULT_READY_WAIT_JIFFIES);
पूर्ण

/**
 * spi_nor_global_block_unlock() - Unlock Global Block Protection.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_global_block_unlock(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_GBULK, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_GBULK,
						       शून्य, 0);
	पूर्ण

	अगर (ret) अणु
		dev_dbg(nor->dev, "error %d on Global Block Unlock\n", ret);
		वापस ret;
	पूर्ण

	वापस spi_nor_रुको_till_पढ़ोy(nor);
पूर्ण

/**
 * spi_nor_ग_लिखो_sr() - Write the Status Register.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @sr:		poपूर्णांकer to DMA-able buffer to ग_लिखो to the Status Register.
 * @len:	number of bytes to ग_लिखो to the Status Register.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_sr(काष्ठा spi_nor *nor, स्थिर u8 *sr, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRSR, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(len, sr, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_WRSR, sr,
						       len);
	पूर्ण

	अगर (ret) अणु
		dev_dbg(nor->dev, "error %d writing SR\n", ret);
		वापस ret;
	पूर्ण

	वापस spi_nor_रुको_till_पढ़ोy(nor);
पूर्ण

/**
 * spi_nor_ग_लिखो_sr1_and_check() - Write one byte to the Status Register 1 and
 * ensure that the byte written match the received value.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_ग_लिखो_sr1_and_check(काष्ठा spi_nor *nor, u8 sr1)
अणु
	पूर्णांक ret;

	nor->bouncebuf[0] = sr1;

	ret = spi_nor_ग_लिखो_sr(nor, nor->bouncebuf, 1);
	अगर (ret)
		वापस ret;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	अगर (nor->bouncebuf[0] != sr1) अणु
		dev_dbg(nor->dev, "SR1: read back test failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_nor_ग_लिखो_16bit_sr_and_check() - Write the Status Register 1 and the
 * Status Register 2 in one shot. Ensure that the byte written in the Status
 * Register 1 match the received value, and that the 16-bit Write did not
 * affect what was alपढ़ोy in the Status Register 2.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register 1.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_ग_लिखो_16bit_sr_and_check(काष्ठा spi_nor *nor, u8 sr1)
अणु
	पूर्णांक ret;
	u8 *sr_cr = nor->bouncebuf;
	u8 cr_written;

	/* Make sure we करोn't overग_लिखो the contents of Status Register 2. */
	अगर (!(nor->flags & SNOR_F_NO_READ_CR)) अणु
		ret = spi_nor_पढ़ो_cr(nor, &sr_cr[1]);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (nor->params->quad_enable) अणु
		/*
		 * If the Status Register 2 Read command (35h) is not
		 * supported, we should at least be sure we करोn't
		 * change the value of the SR2 Quad Enable bit.
		 *
		 * We can safely assume that when the Quad Enable method is
		 * set, the value of the QE bit is one, as a consequence of the
		 * nor->params->quad_enable() call.
		 *
		 * We can safely assume that the Quad Enable bit is present in
		 * the Status Register 2 at BIT(1). According to the JESD216
		 * revB standard, BFPT DWORDS[15], bits 22:20, the 16-bit
		 * Write Status (01h) command is available just क्रम the हालs
		 * in which the QE bit is described in SR2 at BIT(1).
		 */
		sr_cr[1] = SR2_QUAD_EN_BIT1;
	पूर्ण अन्यथा अणु
		sr_cr[1] = 0;
	पूर्ण

	sr_cr[0] = sr1;

	ret = spi_nor_ग_लिखो_sr(nor, sr_cr, 2);
	अगर (ret)
		वापस ret;

	अगर (nor->flags & SNOR_F_NO_READ_CR)
		वापस 0;

	cr_written = sr_cr[1];

	ret = spi_nor_पढ़ो_cr(nor, &sr_cr[1]);
	अगर (ret)
		वापस ret;

	अगर (cr_written != sr_cr[1]) अणु
		dev_dbg(nor->dev, "CR: read back test failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_nor_ग_लिखो_16bit_cr_and_check() - Write the Status Register 1 and the
 * Configuration Register in one shot. Ensure that the byte written in the
 * Configuration Register match the received value, and that the 16-bit Write
 * did not affect what was alपढ़ोy in the Status Register 1.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 * @cr:		byte value to be written to the Configuration Register.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_16bit_cr_and_check(काष्ठा spi_nor *nor, u8 cr)
अणु
	पूर्णांक ret;
	u8 *sr_cr = nor->bouncebuf;
	u8 sr_written;

	/* Keep the current value of the Status Register 1. */
	ret = spi_nor_पढ़ो_sr(nor, sr_cr);
	अगर (ret)
		वापस ret;

	sr_cr[1] = cr;

	ret = spi_nor_ग_लिखो_sr(nor, sr_cr, 2);
	अगर (ret)
		वापस ret;

	sr_written = sr_cr[0];

	ret = spi_nor_पढ़ो_sr(nor, sr_cr);
	अगर (ret)
		वापस ret;

	अगर (sr_written != sr_cr[0]) अणु
		dev_dbg(nor->dev, "SR: Read back test failed\n");
		वापस -EIO;
	पूर्ण

	अगर (nor->flags & SNOR_F_NO_READ_CR)
		वापस 0;

	ret = spi_nor_पढ़ो_cr(nor, &sr_cr[1]);
	अगर (ret)
		वापस ret;

	अगर (cr != sr_cr[1]) अणु
		dev_dbg(nor->dev, "CR: read back test failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_nor_ग_लिखो_sr_and_check() - Write the Status Register 1 and ensure that
 * the byte written match the received value without affecting other bits in the
 * Status Register 1 and 2.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 * @sr1:	byte value to be written to the Status Register.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_ग_लिखो_sr_and_check(काष्ठा spi_nor *nor, u8 sr1)
अणु
	अगर (nor->flags & SNOR_F_HAS_16BIT_SR)
		वापस spi_nor_ग_लिखो_16bit_sr_and_check(nor, sr1);

	वापस spi_nor_ग_लिखो_sr1_and_check(nor, sr1);
पूर्ण

/**
 * spi_nor_ग_लिखो_sr2() - Write the Status Register 2 using the
 * SPINOR_OP_WRSR2 (3eh) command.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @sr2:	poपूर्णांकer to DMA-able buffer to ग_लिखो to the Status Register 2.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_ग_लिखो_sr2(काष्ठा spi_nor *nor, स्थिर u8 *sr2)
अणु
	पूर्णांक ret;

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WRSR2, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(1, sr2, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor, SPINOR_OP_WRSR2,
						       sr2, 1);
	पूर्ण

	अगर (ret) अणु
		dev_dbg(nor->dev, "error %d writing SR2\n", ret);
		वापस ret;
	पूर्ण

	वापस spi_nor_रुको_till_पढ़ोy(nor);
पूर्ण

/**
 * spi_nor_पढ़ो_sr2() - Read the Status Register 2 using the
 * SPINOR_OP_RDSR2 (3fh) command.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @sr2:	poपूर्णांकer to DMA-able buffer where the value of the
 *		Status Register 2 will be written.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_पढ़ो_sr2(काष्ठा spi_nor *nor, u8 *sr2)
अणु
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDSR2, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(1, sr2, 0));

		spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_पढ़ो_reg(nor, SPINOR_OP_RDSR2, sr2,
						      1);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d reading SR2\n", ret);

	वापस ret;
पूर्ण

/**
 * spi_nor_erase_chip() - Erase the entire flash memory.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_erase_chip(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	dev_dbg(nor->dev, " %lldKiB\n", (दीर्घ दीर्घ)(nor->mtd.size >> 10));

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_CHIP_ERASE, 0),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->ग_लिखो_proto);

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = spi_nor_controller_ops_ग_लिखो_reg(nor,
						       SPINOR_OP_CHIP_ERASE,
						       शून्य, 0);
	पूर्ण

	अगर (ret)
		dev_dbg(nor->dev, "error %d erasing chip\n", ret);

	वापस ret;
पूर्ण

अटल u8 spi_nor_convert_opcode(u8 opcode, स्थिर u8 table[][2], माप_प्रकार size)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++)
		अगर (table[i][0] == opcode)
			वापस table[i][1];

	/* No conversion found, keep input op code. */
	वापस opcode;
पूर्ण

u8 spi_nor_convert_3to4_पढ़ो(u8 opcode)
अणु
	अटल स्थिर u8 spi_nor_3to4_पढ़ो[][2] = अणु
		अणु SPINOR_OP_READ,	SPINOR_OP_READ_4B पूर्ण,
		अणु SPINOR_OP_READ_FAST,	SPINOR_OP_READ_FAST_4B पूर्ण,
		अणु SPINOR_OP_READ_1_1_2,	SPINOR_OP_READ_1_1_2_4B पूर्ण,
		अणु SPINOR_OP_READ_1_2_2,	SPINOR_OP_READ_1_2_2_4B पूर्ण,
		अणु SPINOR_OP_READ_1_1_4,	SPINOR_OP_READ_1_1_4_4B पूर्ण,
		अणु SPINOR_OP_READ_1_4_4,	SPINOR_OP_READ_1_4_4_4B पूर्ण,
		अणु SPINOR_OP_READ_1_1_8,	SPINOR_OP_READ_1_1_8_4B पूर्ण,
		अणु SPINOR_OP_READ_1_8_8,	SPINOR_OP_READ_1_8_8_4B पूर्ण,

		अणु SPINOR_OP_READ_1_1_1_DTR,	SPINOR_OP_READ_1_1_1_DTR_4B पूर्ण,
		अणु SPINOR_OP_READ_1_2_2_DTR,	SPINOR_OP_READ_1_2_2_DTR_4B पूर्ण,
		अणु SPINOR_OP_READ_1_4_4_DTR,	SPINOR_OP_READ_1_4_4_DTR_4B पूर्ण,
	पूर्ण;

	वापस spi_nor_convert_opcode(opcode, spi_nor_3to4_पढ़ो,
				      ARRAY_SIZE(spi_nor_3to4_पढ़ो));
पूर्ण

अटल u8 spi_nor_convert_3to4_program(u8 opcode)
अणु
	अटल स्थिर u8 spi_nor_3to4_program[][2] = अणु
		अणु SPINOR_OP_PP,		SPINOR_OP_PP_4B पूर्ण,
		अणु SPINOR_OP_PP_1_1_4,	SPINOR_OP_PP_1_1_4_4B पूर्ण,
		अणु SPINOR_OP_PP_1_4_4,	SPINOR_OP_PP_1_4_4_4B पूर्ण,
		अणु SPINOR_OP_PP_1_1_8,	SPINOR_OP_PP_1_1_8_4B पूर्ण,
		अणु SPINOR_OP_PP_1_8_8,	SPINOR_OP_PP_1_8_8_4B पूर्ण,
	पूर्ण;

	वापस spi_nor_convert_opcode(opcode, spi_nor_3to4_program,
				      ARRAY_SIZE(spi_nor_3to4_program));
पूर्ण

अटल u8 spi_nor_convert_3to4_erase(u8 opcode)
अणु
	अटल स्थिर u8 spi_nor_3to4_erase[][2] = अणु
		अणु SPINOR_OP_BE_4K,	SPINOR_OP_BE_4K_4B पूर्ण,
		अणु SPINOR_OP_BE_32K,	SPINOR_OP_BE_32K_4B पूर्ण,
		अणु SPINOR_OP_SE,		SPINOR_OP_SE_4B पूर्ण,
	पूर्ण;

	वापस spi_nor_convert_opcode(opcode, spi_nor_3to4_erase,
				      ARRAY_SIZE(spi_nor_3to4_erase));
पूर्ण

अटल bool spi_nor_has_unअगरorm_erase(स्थिर काष्ठा spi_nor *nor)
अणु
	वापस !!nor->params->erase_map.unअगरorm_erase_type;
पूर्ण

अटल व्योम spi_nor_set_4byte_opcodes(काष्ठा spi_nor *nor)
अणु
	nor->पढ़ो_opcode = spi_nor_convert_3to4_पढ़ो(nor->पढ़ो_opcode);
	nor->program_opcode = spi_nor_convert_3to4_program(nor->program_opcode);
	nor->erase_opcode = spi_nor_convert_3to4_erase(nor->erase_opcode);

	अगर (!spi_nor_has_unअगरorm_erase(nor)) अणु
		काष्ठा spi_nor_erase_map *map = &nor->params->erase_map;
		काष्ठा spi_nor_erase_type *erase;
		पूर्णांक i;

		क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) अणु
			erase = &map->erase_type[i];
			erase->opcode =
				spi_nor_convert_3to4_erase(erase->opcode);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक spi_nor_lock_and_prep(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&nor->lock);

	अगर (nor->controller_ops &&  nor->controller_ops->prepare) अणु
		ret = nor->controller_ops->prepare(nor);
		अगर (ret) अणु
			mutex_unlock(&nor->lock);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम spi_nor_unlock_and_unprep(काष्ठा spi_nor *nor)
अणु
	अगर (nor->controller_ops && nor->controller_ops->unprepare)
		nor->controller_ops->unprepare(nor);
	mutex_unlock(&nor->lock);
पूर्ण

अटल u32 spi_nor_convert_addr(काष्ठा spi_nor *nor, loff_t addr)
अणु
	अगर (!nor->params->convert_addr)
		वापस addr;

	वापस nor->params->convert_addr(nor, addr);
पूर्ण

/*
 * Initiate the erasure of a single sector
 */
अटल पूर्णांक spi_nor_erase_sector(काष्ठा spi_nor *nor, u32 addr)
अणु
	पूर्णांक i;

	addr = spi_nor_convert_addr(nor, addr);

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(nor->erase_opcode, 0),
				   SPI_MEM_OP_ADDR(nor->addr_width, addr, 0),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		spi_nor_spimem_setup_op(nor, &op, nor->ग_लिखो_proto);

		वापस spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अगर (nor->controller_ops->erase) अणु
		वापस spi_nor_controller_ops_erase(nor, addr);
	पूर्ण

	/*
	 * Default implementation, अगर driver करोesn't have a specialized HW
	 * control
	 */
	क्रम (i = nor->addr_width - 1; i >= 0; i--) अणु
		nor->bouncebuf[i] = addr & 0xff;
		addr >>= 8;
	पूर्ण

	वापस spi_nor_controller_ops_ग_लिखो_reg(nor, nor->erase_opcode,
						nor->bouncebuf, nor->addr_width);
पूर्ण

/**
 * spi_nor_भाग_by_erase_size() - calculate reमुख्यder and update new भागidend
 * @erase:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase type
 * @भागidend:	भागidend value
 * @reमुख्यder:	poपूर्णांकer to u32 reमुख्यder (will be updated)
 *
 * Return: the result of the भागision
 */
अटल u64 spi_nor_भाग_by_erase_size(स्थिर काष्ठा spi_nor_erase_type *erase,
				     u64 भागidend, u32 *reमुख्यder)
अणु
	/* JEDEC JESD216B Standard imposes erase sizes to be घातer of 2. */
	*reमुख्यder = (u32)भागidend & erase->size_mask;
	वापस भागidend >> erase->size_shअगरt;
पूर्ण

/**
 * spi_nor_find_best_erase_type() - find the best erase type क्रम the given
 *				    offset in the serial flash memory and the
 *				    number of bytes to erase. The region in
 *				    which the address fits is expected to be
 *				    provided.
 * @map:	the erase map of the SPI NOR
 * @region:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase region
 * @addr:	offset in the serial flash memory
 * @len:	number of bytes to erase
 *
 * Return: a poपूर्णांकer to the best fitted erase type, शून्य otherwise.
 */
अटल स्थिर काष्ठा spi_nor_erase_type *
spi_nor_find_best_erase_type(स्थिर काष्ठा spi_nor_erase_map *map,
			     स्थिर काष्ठा spi_nor_erase_region *region,
			     u64 addr, u32 len)
अणु
	स्थिर काष्ठा spi_nor_erase_type *erase;
	u32 rem;
	पूर्णांक i;
	u8 erase_mask = region->offset & SNOR_ERASE_TYPE_MASK;

	/*
	 * Erase types are ordered by size, with the smallest erase type at
	 * index 0.
	 */
	क्रम (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) अणु
		/* Does the erase region support the tested erase type? */
		अगर (!(erase_mask & BIT(i)))
			जारी;

		erase = &map->erase_type[i];

		/* Alignment is not mandatory क्रम overlaid regions */
		अगर (region->offset & SNOR_OVERLAID_REGION &&
		    region->size <= len)
			वापस erase;

		/* Don't erase more than what the user has asked क्रम. */
		अगर (erase->size > len)
			जारी;

		spi_nor_भाग_by_erase_size(erase, addr, &rem);
		अगर (rem)
			जारी;
		अन्यथा
			वापस erase;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल u64 spi_nor_region_is_last(स्थिर काष्ठा spi_nor_erase_region *region)
अणु
	वापस region->offset & SNOR_LAST_REGION;
पूर्ण

अटल u64 spi_nor_region_end(स्थिर काष्ठा spi_nor_erase_region *region)
अणु
	वापस (region->offset & ~SNOR_ERASE_FLAGS_MASK) + region->size;
पूर्ण

/**
 * spi_nor_region_next() - get the next spi nor region
 * @region:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase region
 *
 * Return: the next spi nor region or शून्य अगर last region.
 */
काष्ठा spi_nor_erase_region *
spi_nor_region_next(काष्ठा spi_nor_erase_region *region)
अणु
	अगर (spi_nor_region_is_last(region))
		वापस शून्य;
	region++;
	वापस region;
पूर्ण

/**
 * spi_nor_find_erase_region() - find the region of the serial flash memory in
 *				 which the offset fits
 * @map:	the erase map of the SPI NOR
 * @addr:	offset in the serial flash memory
 *
 * Return: a poपूर्णांकer to the spi_nor_erase_region काष्ठा, ERR_PTR(-त्रुटि_सं)
 *	   otherwise.
 */
अटल काष्ठा spi_nor_erase_region *
spi_nor_find_erase_region(स्थिर काष्ठा spi_nor_erase_map *map, u64 addr)
अणु
	काष्ठा spi_nor_erase_region *region = map->regions;
	u64 region_start = region->offset & ~SNOR_ERASE_FLAGS_MASK;
	u64 region_end = region_start + region->size;

	जबतक (addr < region_start || addr >= region_end) अणु
		region = spi_nor_region_next(region);
		अगर (!region)
			वापस ERR_PTR(-EINVAL);

		region_start = region->offset & ~SNOR_ERASE_FLAGS_MASK;
		region_end = region_start + region->size;
	पूर्ण

	वापस region;
पूर्ण

/**
 * spi_nor_init_erase_cmd() - initialize an erase command
 * @region:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase region
 * @erase:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase type
 *
 * Return: the poपूर्णांकer to the allocated erase command, ERR_PTR(-त्रुटि_सं)
 *	   otherwise.
 */
अटल काष्ठा spi_nor_erase_command *
spi_nor_init_erase_cmd(स्थिर काष्ठा spi_nor_erase_region *region,
		       स्थिर काष्ठा spi_nor_erase_type *erase)
अणु
	काष्ठा spi_nor_erase_command *cmd;

	cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&cmd->list);
	cmd->opcode = erase->opcode;
	cmd->count = 1;

	अगर (region->offset & SNOR_OVERLAID_REGION)
		cmd->size = region->size;
	अन्यथा
		cmd->size = erase->size;

	वापस cmd;
पूर्ण

/**
 * spi_nor_destroy_erase_cmd_list() - destroy erase command list
 * @erase_list:	list of erase commands
 */
अटल व्योम spi_nor_destroy_erase_cmd_list(काष्ठा list_head *erase_list)
अणु
	काष्ठा spi_nor_erase_command *cmd, *next;

	list_क्रम_each_entry_safe(cmd, next, erase_list, list) अणु
		list_del(&cmd->list);
		kमुक्त(cmd);
	पूर्ण
पूर्ण

/**
 * spi_nor_init_erase_cmd_list() - initialize erase command list
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @erase_list:	list of erase commands to be executed once we validate that the
 *		erase can be perक्रमmed
 * @addr:	offset in the serial flash memory
 * @len:	number of bytes to erase
 *
 * Builds the list of best fitted erase commands and verअगरies अगर the erase can
 * be perक्रमmed.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_init_erase_cmd_list(काष्ठा spi_nor *nor,
				       काष्ठा list_head *erase_list,
				       u64 addr, u32 len)
अणु
	स्थिर काष्ठा spi_nor_erase_map *map = &nor->params->erase_map;
	स्थिर काष्ठा spi_nor_erase_type *erase, *prev_erase = शून्य;
	काष्ठा spi_nor_erase_region *region;
	काष्ठा spi_nor_erase_command *cmd = शून्य;
	u64 region_end;
	पूर्णांक ret = -EINVAL;

	region = spi_nor_find_erase_region(map, addr);
	अगर (IS_ERR(region))
		वापस PTR_ERR(region);

	region_end = spi_nor_region_end(region);

	जबतक (len) अणु
		erase = spi_nor_find_best_erase_type(map, region, addr, len);
		अगर (!erase)
			जाओ destroy_erase_cmd_list;

		अगर (prev_erase != erase ||
		    erase->size != cmd->size ||
		    region->offset & SNOR_OVERLAID_REGION) अणु
			cmd = spi_nor_init_erase_cmd(region, erase);
			अगर (IS_ERR(cmd)) अणु
				ret = PTR_ERR(cmd);
				जाओ destroy_erase_cmd_list;
			पूर्ण

			list_add_tail(&cmd->list, erase_list);
		पूर्ण अन्यथा अणु
			cmd->count++;
		पूर्ण

		addr += cmd->size;
		len -= cmd->size;

		अगर (len && addr >= region_end) अणु
			region = spi_nor_region_next(region);
			अगर (!region)
				जाओ destroy_erase_cmd_list;
			region_end = spi_nor_region_end(region);
		पूर्ण

		prev_erase = erase;
	पूर्ण

	वापस 0;

destroy_erase_cmd_list:
	spi_nor_destroy_erase_cmd_list(erase_list);
	वापस ret;
पूर्ण

/**
 * spi_nor_erase_multi_sectors() - perक्रमm a non-unअगरorm erase
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @addr:	offset in the serial flash memory
 * @len:	number of bytes to erase
 *
 * Build a list of best fitted erase commands and execute it once we validate
 * that the erase can be perक्रमmed.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_erase_multi_sectors(काष्ठा spi_nor *nor, u64 addr, u32 len)
अणु
	LIST_HEAD(erase_list);
	काष्ठा spi_nor_erase_command *cmd, *next;
	पूर्णांक ret;

	ret = spi_nor_init_erase_cmd_list(nor, &erase_list, addr, len);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry_safe(cmd, next, &erase_list, list) अणु
		nor->erase_opcode = cmd->opcode;
		जबतक (cmd->count) अणु
			dev_vdbg(nor->dev, "erase_cmd->size = 0x%08x, erase_cmd->opcode = 0x%02x, erase_cmd->count = %u\n",
				 cmd->size, cmd->opcode, cmd->count);

			ret = spi_nor_ग_लिखो_enable(nor);
			अगर (ret)
				जाओ destroy_erase_cmd_list;

			ret = spi_nor_erase_sector(nor, addr);
			अगर (ret)
				जाओ destroy_erase_cmd_list;

			ret = spi_nor_रुको_till_पढ़ोy(nor);
			अगर (ret)
				जाओ destroy_erase_cmd_list;

			addr += cmd->size;
			cmd->count--;
		पूर्ण
		list_del(&cmd->list);
		kमुक्त(cmd);
	पूर्ण

	वापस 0;

destroy_erase_cmd_list:
	spi_nor_destroy_erase_cmd_list(&erase_list);
	वापस ret;
पूर्ण

/*
 * Erase an address range on the nor chip.  The address range may extend
 * one or more erase sectors. Return an error अगर there is a problem erasing.
 */
अटल पूर्णांक spi_nor_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	u32 addr, len;
	uपूर्णांक32_t rem;
	पूर्णांक ret;

	dev_dbg(nor->dev, "at 0x%llx, len %lld\n", (दीर्घ दीर्घ)instr->addr,
			(दीर्घ दीर्घ)instr->len);

	अगर (spi_nor_has_unअगरorm_erase(nor)) अणु
		भाग_u64_rem(instr->len, mtd->erasesize, &rem);
		अगर (rem)
			वापस -EINVAL;
	पूर्ण

	addr = instr->addr;
	len = instr->len;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	/* whole-chip erase? */
	अगर (len == mtd->size && !(nor->flags & SNOR_F_NO_OP_CHIP_ERASE)) अणु
		अचिन्हित दीर्घ समयout;

		ret = spi_nor_ग_लिखो_enable(nor);
		अगर (ret)
			जाओ erase_err;

		ret = spi_nor_erase_chip(nor);
		अगर (ret)
			जाओ erase_err;

		/*
		 * Scale the समयout linearly with the size of the flash, with
		 * a minimum calibrated to an old 2MB flash. We could try to
		 * pull these from CFI/SFDP, but these values should be good
		 * enough क्रम now.
		 */
		समयout = max(CHIP_ERASE_2MB_READY_WAIT_JIFFIES,
			      CHIP_ERASE_2MB_READY_WAIT_JIFFIES *
			      (अचिन्हित दीर्घ)(mtd->size / SZ_2M));
		ret = spi_nor_रुको_till_पढ़ोy_with_समयout(nor, समयout);
		अगर (ret)
			जाओ erase_err;

	/* REVISIT in some हालs we could speed up erasing large regions
	 * by using SPINOR_OP_SE instead of SPINOR_OP_BE_4K.  We may have set up
	 * to use "small sector erase", but that's not always optimal.
	 */

	/* "sector"-at-a-समय erase */
	पूर्ण अन्यथा अगर (spi_nor_has_unअगरorm_erase(nor)) अणु
		जबतक (len) अणु
			ret = spi_nor_ग_लिखो_enable(nor);
			अगर (ret)
				जाओ erase_err;

			ret = spi_nor_erase_sector(nor, addr);
			अगर (ret)
				जाओ erase_err;

			ret = spi_nor_रुको_till_पढ़ोy(nor);
			अगर (ret)
				जाओ erase_err;

			addr += mtd->erasesize;
			len -= mtd->erasesize;
		पूर्ण

	/* erase multiple sectors */
	पूर्ण अन्यथा अणु
		ret = spi_nor_erase_multi_sectors(nor, addr, len);
		अगर (ret)
			जाओ erase_err;
	पूर्ण

	ret = spi_nor_ग_लिखो_disable(nor);

erase_err:
	spi_nor_unlock_and_unprep(nor);

	वापस ret;
पूर्ण

/**
 * spi_nor_sr1_bit6_quad_enable() - Set the Quad Enable BIT(6) in the Status
 * Register 1.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 *
 * Bit 6 of the Status Register 1 is the QE bit क्रम Macronix like QSPI memories.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_sr1_bit6_quad_enable(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	अगर (nor->bouncebuf[0] & SR1_QUAD_EN_BIT6)
		वापस 0;

	nor->bouncebuf[0] |= SR1_QUAD_EN_BIT6;

	वापस spi_nor_ग_लिखो_sr1_and_check(nor, nor->bouncebuf[0]);
पूर्ण

/**
 * spi_nor_sr2_bit1_quad_enable() - set the Quad Enable BIT(1) in the Status
 * Register 2.
 * @nor:       poपूर्णांकer to a 'struct spi_nor'.
 *
 * Bit 1 of the Status Register 2 is the QE bit क्रम Spansion like QSPI memories.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_sr2_bit1_quad_enable(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (nor->flags & SNOR_F_NO_READ_CR)
		वापस spi_nor_ग_लिखो_16bit_cr_and_check(nor, SR2_QUAD_EN_BIT1);

	ret = spi_nor_पढ़ो_cr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	अगर (nor->bouncebuf[0] & SR2_QUAD_EN_BIT1)
		वापस 0;

	nor->bouncebuf[0] |= SR2_QUAD_EN_BIT1;

	वापस spi_nor_ग_लिखो_16bit_cr_and_check(nor, nor->bouncebuf[0]);
पूर्ण

/**
 * spi_nor_sr2_bit7_quad_enable() - set QE bit in Status Register 2.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 *
 * Set the Quad Enable (QE) bit in the Status Register 2.
 *
 * This is one of the procedures to set the QE bit described in the SFDP
 * (JESD216 rev B) specअगरication but no manufacturer using this procedure has
 * been identअगरied yet, hence the name of the function.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_sr2_bit7_quad_enable(काष्ठा spi_nor *nor)
अणु
	u8 *sr2 = nor->bouncebuf;
	पूर्णांक ret;
	u8 sr2_written;

	/* Check current Quad Enable bit value. */
	ret = spi_nor_पढ़ो_sr2(nor, sr2);
	अगर (ret)
		वापस ret;
	अगर (*sr2 & SR2_QUAD_EN_BIT7)
		वापस 0;

	/* Update the Quad Enable bit. */
	*sr2 |= SR2_QUAD_EN_BIT7;

	ret = spi_nor_ग_लिखो_sr2(nor, sr2);
	अगर (ret)
		वापस ret;

	sr2_written = *sr2;

	/* Read back and check it. */
	ret = spi_nor_पढ़ो_sr2(nor, sr2);
	अगर (ret)
		वापस ret;

	अगर (*sr2 != sr2_written) अणु
		dev_dbg(nor->dev, "SR2: Read back test failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_nor_manufacturer *manufacturers[] = अणु
	&spi_nor_aपंचांगel,
	&spi_nor_catalyst,
	&spi_nor_eon,
	&spi_nor_esmt,
	&spi_nor_everspin,
	&spi_nor_fujitsu,
	&spi_nor_gigadevice,
	&spi_nor_पूर्णांकel,
	&spi_nor_issi,
	&spi_nor_macronix,
	&spi_nor_micron,
	&spi_nor_st,
	&spi_nor_spansion,
	&spi_nor_sst,
	&spi_nor_winbond,
	&spi_nor_xilinx,
	&spi_nor_xmc,
पूर्ण;

अटल स्थिर काष्ठा flash_info *
spi_nor_search_part_by_id(स्थिर काष्ठा flash_info *parts, अचिन्हित पूर्णांक nparts,
			  स्थिर u8 *id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nparts; i++) अणु
		अगर (parts[i].id_len &&
		    !स_भेद(parts[i].id, id, parts[i].id_len))
			वापस &parts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा flash_info *spi_nor_पढ़ो_id(काष्ठा spi_nor *nor)
अणु
	स्थिर काष्ठा flash_info *info;
	u8 *id = nor->bouncebuf;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (nor->spimem) अणु
		काष्ठा spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDID, 1),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(SPI_NOR_MAX_ID_LEN, id, 1));

		ret = spi_mem_exec_op(nor->spimem, &op);
	पूर्ण अन्यथा अणु
		ret = nor->controller_ops->पढ़ो_reg(nor, SPINOR_OP_RDID, id,
						    SPI_NOR_MAX_ID_LEN);
	पूर्ण
	अगर (ret) अणु
		dev_dbg(nor->dev, "error %d reading JEDEC ID\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(manufacturers); i++) अणु
		info = spi_nor_search_part_by_id(manufacturers[i]->parts,
						 manufacturers[i]->nparts,
						 id);
		अगर (info) अणु
			nor->manufacturer = manufacturers[i];
			वापस info;
		पूर्ण
	पूर्ण

	dev_err(nor->dev, "unrecognized JEDEC id bytes: %*ph\n",
		SPI_NOR_MAX_ID_LEN, id);
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक spi_nor_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	sमाप_प्रकार ret;

	dev_dbg(nor->dev, "from 0x%08x, len %zd\n", (u32)from, len);

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	जबतक (len) अणु
		loff_t addr = from;

		addr = spi_nor_convert_addr(nor, addr);

		ret = spi_nor_पढ़ो_data(nor, addr, len, buf);
		अगर (ret == 0) अणु
			/* We shouldn't see 0-length पढ़ोs */
			ret = -EIO;
			जाओ पढ़ो_err;
		पूर्ण
		अगर (ret < 0)
			जाओ पढ़ो_err;

		WARN_ON(ret > len);
		*retlen += ret;
		buf += ret;
		from += ret;
		len -= ret;
	पूर्ण
	ret = 0;

पढ़ो_err:
	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

/*
 * Write an address range to the nor chip.  Data must be written in
 * FLASH_PAGESIZE chunks.  The address range may be any size provided
 * it is within the physical boundaries.
 */
अटल पूर्णांक spi_nor_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
	माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	माप_प्रकार page_offset, page_reमुख्य, i;
	sमाप_प्रकार ret;

	dev_dbg(nor->dev, "to 0x%08x, len %zd\n", (u32)to, len);

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < len; ) अणु
		sमाप_प्रकार written;
		loff_t addr = to + i;

		/*
		 * If page_size is a घातer of two, the offset can be quickly
		 * calculated with an AND operation. On the other हालs we
		 * need to करो a modulus operation (more expensive).
		 */
		अगर (is_घातer_of_2(nor->page_size)) अणु
			page_offset = addr & (nor->page_size - 1);
		पूर्ण अन्यथा अणु
			uपूर्णांक64_t aux = addr;

			page_offset = करो_भाग(aux, nor->page_size);
		पूर्ण
		/* the size of data reमुख्यing on the first page */
		page_reमुख्य = min_t(माप_प्रकार,
				    nor->page_size - page_offset, len - i);

		addr = spi_nor_convert_addr(nor, addr);

		ret = spi_nor_ग_लिखो_enable(nor);
		अगर (ret)
			जाओ ग_लिखो_err;

		ret = spi_nor_ग_लिखो_data(nor, addr, page_reमुख्य, buf + i);
		अगर (ret < 0)
			जाओ ग_लिखो_err;
		written = ret;

		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			जाओ ग_लिखो_err;
		*retlen += written;
		i += written;
	पूर्ण

ग_लिखो_err:
	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_nor_check(काष्ठा spi_nor *nor)
अणु
	अगर (!nor->dev ||
	    (!nor->spimem && !nor->controller_ops) ||
	    (!nor->spimem && nor->controller_ops &&
	    (!nor->controller_ops->पढ़ो ||
	     !nor->controller_ops->ग_लिखो ||
	     !nor->controller_ops->पढ़ो_reg ||
	     !nor->controller_ops->ग_लिखो_reg))) अणु
		pr_err("spi-nor: please fill all the necessary fields!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nor->spimem && nor->controller_ops) अणु
		dev_err(nor->dev, "nor->spimem and nor->controller_ops are mutually exclusive, please set just one of them.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
spi_nor_set_पढ़ो_settings(काष्ठा spi_nor_पढ़ो_command *पढ़ो,
			  u8 num_mode_घड़ीs,
			  u8 num_रुको_states,
			  u8 opcode,
			  क्रमागत spi_nor_protocol proto)
अणु
	पढ़ो->num_mode_घड़ीs = num_mode_घड़ीs;
	पढ़ो->num_रुको_states = num_रुको_states;
	पढ़ो->opcode = opcode;
	पढ़ो->proto = proto;
पूर्ण

व्योम spi_nor_set_pp_settings(काष्ठा spi_nor_pp_command *pp, u8 opcode,
			     क्रमागत spi_nor_protocol proto)
अणु
	pp->opcode = opcode;
	pp->proto = proto;
पूर्ण

अटल पूर्णांक spi_nor_hwcaps2cmd(u32 hwcaps, स्थिर पूर्णांक table[][2], माप_प्रकार size)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++)
		अगर (table[i][0] == (पूर्णांक)hwcaps)
			वापस table[i][1];

	वापस -EINVAL;
पूर्ण

पूर्णांक spi_nor_hwcaps_पढ़ो2cmd(u32 hwcaps)
अणु
	अटल स्थिर पूर्णांक hwcaps_पढ़ो2cmd[][2] = अणु
		अणु SNOR_HWCAPS_READ,		SNOR_CMD_READ पूर्ण,
		अणु SNOR_HWCAPS_READ_FAST,	SNOR_CMD_READ_FAST पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_1_DTR,	SNOR_CMD_READ_1_1_1_DTR पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_2,	SNOR_CMD_READ_1_1_2 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_2_2,	SNOR_CMD_READ_1_2_2 पूर्ण,
		अणु SNOR_HWCAPS_READ_2_2_2,	SNOR_CMD_READ_2_2_2 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_2_2_DTR,	SNOR_CMD_READ_1_2_2_DTR पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_4,	SNOR_CMD_READ_1_1_4 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_4_4,	SNOR_CMD_READ_1_4_4 पूर्ण,
		अणु SNOR_HWCAPS_READ_4_4_4,	SNOR_CMD_READ_4_4_4 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_4_4_DTR,	SNOR_CMD_READ_1_4_4_DTR पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_8,	SNOR_CMD_READ_1_1_8 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_8_8,	SNOR_CMD_READ_1_8_8 पूर्ण,
		अणु SNOR_HWCAPS_READ_8_8_8,	SNOR_CMD_READ_8_8_8 पूर्ण,
		अणु SNOR_HWCAPS_READ_1_8_8_DTR,	SNOR_CMD_READ_1_8_8_DTR पूर्ण,
		अणु SNOR_HWCAPS_READ_8_8_8_DTR,	SNOR_CMD_READ_8_8_8_DTR पूर्ण,
	पूर्ण;

	वापस spi_nor_hwcaps2cmd(hwcaps, hwcaps_पढ़ो2cmd,
				  ARRAY_SIZE(hwcaps_पढ़ो2cmd));
पूर्ण

अटल पूर्णांक spi_nor_hwcaps_pp2cmd(u32 hwcaps)
अणु
	अटल स्थिर पूर्णांक hwcaps_pp2cmd[][2] = अणु
		अणु SNOR_HWCAPS_PP,		SNOR_CMD_PP पूर्ण,
		अणु SNOR_HWCAPS_PP_1_1_4,		SNOR_CMD_PP_1_1_4 पूर्ण,
		अणु SNOR_HWCAPS_PP_1_4_4,		SNOR_CMD_PP_1_4_4 पूर्ण,
		अणु SNOR_HWCAPS_PP_4_4_4,		SNOR_CMD_PP_4_4_4 पूर्ण,
		अणु SNOR_HWCAPS_PP_1_1_8,		SNOR_CMD_PP_1_1_8 पूर्ण,
		अणु SNOR_HWCAPS_PP_1_8_8,		SNOR_CMD_PP_1_8_8 पूर्ण,
		अणु SNOR_HWCAPS_PP_8_8_8,		SNOR_CMD_PP_8_8_8 पूर्ण,
		अणु SNOR_HWCAPS_PP_8_8_8_DTR,	SNOR_CMD_PP_8_8_8_DTR पूर्ण,
	पूर्ण;

	वापस spi_nor_hwcaps2cmd(hwcaps, hwcaps_pp2cmd,
				  ARRAY_SIZE(hwcaps_pp2cmd));
पूर्ण

/**
 * spi_nor_spimem_check_op - check अगर the operation is supported
 *                           by controller
 *@nor:        poपूर्णांकer to a 'struct spi_nor'
 *@op:         poपूर्णांकer to op ढाँचा to be checked
 *
 * Returns 0 अगर operation is supported, -EOPNOTSUPP otherwise.
 */
अटल पूर्णांक spi_nor_spimem_check_op(काष्ठा spi_nor *nor,
				   काष्ठा spi_mem_op *op)
अणु
	/*
	 * First test with 4 address bytes. The opcode itself might
	 * be a 3B addressing opcode but we करोn't care, because
	 * SPI controller implementation should not check the opcode,
	 * but just the sequence.
	 */
	op->addr.nbytes = 4;
	अगर (!spi_mem_supports_op(nor->spimem, op)) अणु
		अगर (nor->mtd.size > SZ_16M)
			वापस -EOPNOTSUPP;

		/* If flash size <= 16MB, 3 address bytes are sufficient */
		op->addr.nbytes = 3;
		अगर (!spi_mem_supports_op(nor->spimem, op))
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_nor_spimem_check_पढ़ोop - check अगर the पढ़ो op is supported
 *                               by controller
 *@nor:         poपूर्णांकer to a 'struct spi_nor'
 *@पढ़ो:        poपूर्णांकer to op ढाँचा to be checked
 *
 * Returns 0 अगर operation is supported, -EOPNOTSUPP otherwise.
 */
अटल पूर्णांक spi_nor_spimem_check_पढ़ोop(काष्ठा spi_nor *nor,
				       स्थिर काष्ठा spi_nor_पढ़ो_command *पढ़ो)
अणु
	काष्ठा spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(पढ़ो->opcode, 0),
					  SPI_MEM_OP_ADDR(3, 0, 0),
					  SPI_MEM_OP_DUMMY(1, 0),
					  SPI_MEM_OP_DATA_IN(1, शून्य, 0));

	spi_nor_spimem_setup_op(nor, &op, पढ़ो->proto);

	/* convert the dummy cycles to the number of bytes */
	op.dummy.nbytes = (nor->पढ़ो_dummy * op.dummy.buswidth) / 8;
	अगर (spi_nor_protocol_is_dtr(nor->पढ़ो_proto))
		op.dummy.nbytes *= 2;

	वापस spi_nor_spimem_check_op(nor, &op);
पूर्ण

/**
 * spi_nor_spimem_check_pp - check अगर the page program op is supported
 *                           by controller
 *@nor:         poपूर्णांकer to a 'struct spi_nor'
 *@pp:          poपूर्णांकer to op ढाँचा to be checked
 *
 * Returns 0 अगर operation is supported, -EOPNOTSUPP otherwise.
 */
अटल पूर्णांक spi_nor_spimem_check_pp(काष्ठा spi_nor *nor,
				   स्थिर काष्ठा spi_nor_pp_command *pp)
अणु
	काष्ठा spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(pp->opcode, 0),
					  SPI_MEM_OP_ADDR(3, 0, 0),
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(1, शून्य, 0));

	spi_nor_spimem_setup_op(nor, &op, pp->proto);

	वापस spi_nor_spimem_check_op(nor, &op);
पूर्ण

/**
 * spi_nor_spimem_adjust_hwcaps - Find optimal Read/Write protocol
 *                                based on SPI controller capabilities
 * @nor:        poपूर्णांकer to a 'struct spi_nor'
 * @hwcaps:     poपूर्णांकer to resulting capabilities after adjusting
 *              according to controller and flash's capability
 */
अटल व्योम
spi_nor_spimem_adjust_hwcaps(काष्ठा spi_nor *nor, u32 *hwcaps)
अणु
	काष्ठा spi_nor_flash_parameter *params = nor->params;
	अचिन्हित पूर्णांक cap;

	/* X-X-X modes are not supported yet, mask them all. */
	*hwcaps &= ~SNOR_HWCAPS_X_X_X;

	/*
	 * If the reset line is broken, we करो not want to enter a stateful
	 * mode.
	 */
	अगर (nor->flags & SNOR_F_BROKEN_RESET)
		*hwcaps &= ~(SNOR_HWCAPS_X_X_X | SNOR_HWCAPS_X_X_X_DTR);

	क्रम (cap = 0; cap < माप(*hwcaps) * BITS_PER_BYTE; cap++) अणु
		पूर्णांक rdidx, ppidx;

		अगर (!(*hwcaps & BIT(cap)))
			जारी;

		rdidx = spi_nor_hwcaps_पढ़ो2cmd(BIT(cap));
		अगर (rdidx >= 0 &&
		    spi_nor_spimem_check_पढ़ोop(nor, &params->पढ़ोs[rdidx]))
			*hwcaps &= ~BIT(cap);

		ppidx = spi_nor_hwcaps_pp2cmd(BIT(cap));
		अगर (ppidx < 0)
			जारी;

		अगर (spi_nor_spimem_check_pp(nor,
					    &params->page_programs[ppidx]))
			*hwcaps &= ~BIT(cap);
	पूर्ण
पूर्ण

/**
 * spi_nor_set_erase_type() - set a SPI NOR erase type
 * @erase:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase type
 * @size:	the size of the sector/block erased by the erase type
 * @opcode:	the SPI command op code to erase the sector/block
 */
व्योम spi_nor_set_erase_type(काष्ठा spi_nor_erase_type *erase, u32 size,
			    u8 opcode)
अणु
	erase->size = size;
	erase->opcode = opcode;
	/* JEDEC JESD216B Standard imposes erase sizes to be घातer of 2. */
	erase->size_shअगरt = ffs(erase->size) - 1;
	erase->size_mask = (1 << erase->size_shअगरt) - 1;
पूर्ण

/**
 * spi_nor_init_unअगरorm_erase_map() - Initialize unअगरorm erase map
 * @map:		the erase map of the SPI NOR
 * @erase_mask:		biपंचांगask encoding erase types that can erase the entire
 *			flash memory
 * @flash_size:		the spi nor flash memory size
 */
व्योम spi_nor_init_unअगरorm_erase_map(काष्ठा spi_nor_erase_map *map,
				    u8 erase_mask, u64 flash_size)
अणु
	/* Offset 0 with erase_mask and SNOR_LAST_REGION bit set */
	map->unअगरorm_region.offset = (erase_mask & SNOR_ERASE_TYPE_MASK) |
				     SNOR_LAST_REGION;
	map->unअगरorm_region.size = flash_size;
	map->regions = &map->unअगरorm_region;
	map->unअगरorm_erase_type = erase_mask;
पूर्ण

पूर्णांक spi_nor_post_bfpt_fixups(काष्ठा spi_nor *nor,
			     स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			     स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	पूर्णांक ret;

	अगर (nor->manufacturer && nor->manufacturer->fixups &&
	    nor->manufacturer->fixups->post_bfpt) अणु
		ret = nor->manufacturer->fixups->post_bfpt(nor, bfpt_header,
							   bfpt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (nor->info->fixups && nor->info->fixups->post_bfpt)
		वापस nor->info->fixups->post_bfpt(nor, bfpt_header, bfpt);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_nor_select_पढ़ो(काष्ठा spi_nor *nor,
			       u32 shared_hwcaps)
अणु
	पूर्णांक cmd, best_match = fls(shared_hwcaps & SNOR_HWCAPS_READ_MASK) - 1;
	स्थिर काष्ठा spi_nor_पढ़ो_command *पढ़ो;

	अगर (best_match < 0)
		वापस -EINVAL;

	cmd = spi_nor_hwcaps_पढ़ो2cmd(BIT(best_match));
	अगर (cmd < 0)
		वापस -EINVAL;

	पढ़ो = &nor->params->पढ़ोs[cmd];
	nor->पढ़ो_opcode = पढ़ो->opcode;
	nor->पढ़ो_proto = पढ़ो->proto;

	/*
	 * In the SPI NOR framework, we करोn't need to make the dअगरference
	 * between mode घड़ी cycles and रुको state घड़ी cycles.
	 * Indeed, the value of the mode घड़ी cycles is used by a QSPI
	 * flash memory to know whether it should enter or leave its 0-4-4
	 * (Continuous Read / XIP) mode.
	 * eXecution In Place is out of the scope of the mtd sub-प्रणाली.
	 * Hence we choose to merge both mode and रुको state घड़ी cycles
	 * पूर्णांकo the so called dummy घड़ी cycles.
	 */
	nor->पढ़ो_dummy = पढ़ो->num_mode_घड़ीs + पढ़ो->num_रुको_states;
	वापस 0;
पूर्ण

अटल पूर्णांक spi_nor_select_pp(काष्ठा spi_nor *nor,
			     u32 shared_hwcaps)
अणु
	पूर्णांक cmd, best_match = fls(shared_hwcaps & SNOR_HWCAPS_PP_MASK) - 1;
	स्थिर काष्ठा spi_nor_pp_command *pp;

	अगर (best_match < 0)
		वापस -EINVAL;

	cmd = spi_nor_hwcaps_pp2cmd(BIT(best_match));
	अगर (cmd < 0)
		वापस -EINVAL;

	pp = &nor->params->page_programs[cmd];
	nor->program_opcode = pp->opcode;
	nor->ग_लिखो_proto = pp->proto;
	वापस 0;
पूर्ण

/**
 * spi_nor_select_unअगरorm_erase() - select optimum unअगरorm erase type
 * @map:		the erase map of the SPI NOR
 * @wanted_size:	the erase type size to search क्रम. Contains the value of
 *			info->sector_size or of the "small sector" size in हाल
 *			CONFIG_MTD_SPI_NOR_USE_4K_SECTORS is defined.
 *
 * Once the optimum unअगरorm sector erase command is found, disable all the
 * other.
 *
 * Return: poपूर्णांकer to erase type on success, शून्य otherwise.
 */
अटल स्थिर काष्ठा spi_nor_erase_type *
spi_nor_select_unअगरorm_erase(काष्ठा spi_nor_erase_map *map,
			     स्थिर u32 wanted_size)
अणु
	स्थिर काष्ठा spi_nor_erase_type *tested_erase, *erase = शून्य;
	पूर्णांक i;
	u8 unअगरorm_erase_type = map->unअगरorm_erase_type;

	क्रम (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) अणु
		अगर (!(unअगरorm_erase_type & BIT(i)))
			जारी;

		tested_erase = &map->erase_type[i];

		/*
		 * If the current erase size is the one, stop here:
		 * we have found the right unअगरorm Sector Erase command.
		 */
		अगर (tested_erase->size == wanted_size) अणु
			erase = tested_erase;
			अवरोध;
		पूर्ण

		/*
		 * Otherwise, the current erase size is still a valid candidate.
		 * Select the biggest valid candidate.
		 */
		अगर (!erase && tested_erase->size)
			erase = tested_erase;
			/* keep iterating to find the wanted_size */
	पूर्ण

	अगर (!erase)
		वापस शून्य;

	/* Disable all other Sector Erase commands. */
	map->unअगरorm_erase_type &= ~SNOR_ERASE_TYPE_MASK;
	map->unअगरorm_erase_type |= BIT(erase - map->erase_type);
	वापस erase;
पूर्ण

अटल पूर्णांक spi_nor_select_erase(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_nor_erase_map *map = &nor->params->erase_map;
	स्थिर काष्ठा spi_nor_erase_type *erase = शून्य;
	काष्ठा mtd_info *mtd = &nor->mtd;
	u32 wanted_size = nor->info->sector_size;
	पूर्णांक i;

	/*
	 * The previous implementation handling Sector Erase commands assumed
	 * that the SPI flash memory has an unअगरorm layout then used only one
	 * of the supported erase sizes क्रम all Sector Erase commands.
	 * So to be backward compatible, the new implementation also tries to
	 * manage the SPI flash memory as unअगरorm with a single erase sector
	 * size, when possible.
	 */
#अगर_घोषित CONFIG_MTD_SPI_NOR_USE_4K_SECTORS
	/* prefer "small sector" erase अगर possible */
	wanted_size = 4096u;
#पूर्ण_अगर

	अगर (spi_nor_has_unअगरorm_erase(nor)) अणु
		erase = spi_nor_select_unअगरorm_erase(map, wanted_size);
		अगर (!erase)
			वापस -EINVAL;
		nor->erase_opcode = erase->opcode;
		mtd->erasesize = erase->size;
		वापस 0;
	पूर्ण

	/*
	 * For non-unअगरorm SPI flash memory, set mtd->erasesize to the
	 * maximum erase sector size. No need to set nor->erase_opcode.
	 */
	क्रम (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) अणु
		अगर (map->erase_type[i].size) अणु
			erase = &map->erase_type[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!erase)
		वापस -EINVAL;

	mtd->erasesize = erase->size;
	वापस 0;
पूर्ण

अटल पूर्णांक spi_nor_शेष_setup(काष्ठा spi_nor *nor,
				 स्थिर काष्ठा spi_nor_hwcaps *hwcaps)
अणु
	काष्ठा spi_nor_flash_parameter *params = nor->params;
	u32 ignored_mask, shared_mask;
	पूर्णांक err;

	/*
	 * Keep only the hardware capabilities supported by both the SPI
	 * controller and the SPI flash memory.
	 */
	shared_mask = hwcaps->mask & params->hwcaps.mask;

	अगर (nor->spimem) अणु
		/*
		 * When called from spi_nor_probe(), all caps are set and we
		 * need to discard some of them based on what the SPI
		 * controller actually supports (using spi_mem_supports_op()).
		 */
		spi_nor_spimem_adjust_hwcaps(nor, &shared_mask);
	पूर्ण अन्यथा अणु
		/*
		 * SPI n-n-n protocols are not supported when the SPI
		 * controller directly implements the spi_nor पूर्णांकerface.
		 * Yet another reason to चयन to spi-mem.
		 */
		ignored_mask = SNOR_HWCAPS_X_X_X | SNOR_HWCAPS_X_X_X_DTR;
		अगर (shared_mask & ignored_mask) अणु
			dev_dbg(nor->dev,
				"SPI n-n-n protocols are not supported.\n");
			shared_mask &= ~ignored_mask;
		पूर्ण
	पूर्ण

	/* Select the (Fast) Read command. */
	err = spi_nor_select_पढ़ो(nor, shared_mask);
	अगर (err) अणु
		dev_dbg(nor->dev,
			"can't select read settings supported by both the SPI controller and memory.\n");
		वापस err;
	पूर्ण

	/* Select the Page Program command. */
	err = spi_nor_select_pp(nor, shared_mask);
	अगर (err) अणु
		dev_dbg(nor->dev,
			"can't select write settings supported by both the SPI controller and memory.\n");
		वापस err;
	पूर्ण

	/* Select the Sector Erase command. */
	err = spi_nor_select_erase(nor);
	अगर (err) अणु
		dev_dbg(nor->dev,
			"can't select erase settings supported by both the SPI controller and memory.\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_nor_setup(काष्ठा spi_nor *nor,
			 स्थिर काष्ठा spi_nor_hwcaps *hwcaps)
अणु
	अगर (!nor->params->setup)
		वापस 0;

	वापस nor->params->setup(nor, hwcaps);
पूर्ण

/**
 * spi_nor_manufacturer_init_params() - Initialize the flash's parameters and
 * settings based on MFR रेजिस्टर and ->शेष_init() hook.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 */
अटल व्योम spi_nor_manufacturer_init_params(काष्ठा spi_nor *nor)
अणु
	अगर (nor->manufacturer && nor->manufacturer->fixups &&
	    nor->manufacturer->fixups->शेष_init)
		nor->manufacturer->fixups->शेष_init(nor);

	अगर (nor->info->fixups && nor->info->fixups->शेष_init)
		nor->info->fixups->शेष_init(nor);
पूर्ण

/**
 * spi_nor_sfdp_init_params() - Initialize the flash's parameters and settings
 * based on JESD216 SFDP standard.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 *
 * The method has a roll-back mechanism: in हाल the SFDP parsing fails, the
 * legacy flash parameters and settings will be restored.
 */
अटल व्योम spi_nor_sfdp_init_params(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_nor_flash_parameter sfdp_params;

	स_नकल(&sfdp_params, nor->params, माप(sfdp_params));

	अगर (spi_nor_parse_sfdp(nor)) अणु
		स_नकल(nor->params, &sfdp_params, माप(*nor->params));
		nor->addr_width = 0;
		nor->flags &= ~SNOR_F_4B_OPCODES;
	पूर्ण
पूर्ण

/**
 * spi_nor_info_init_params() - Initialize the flash's parameters and settings
 * based on nor->info data.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 */
अटल व्योम spi_nor_info_init_params(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_nor_flash_parameter *params = nor->params;
	काष्ठा spi_nor_erase_map *map = &params->erase_map;
	स्थिर काष्ठा flash_info *info = nor->info;
	काष्ठा device_node *np = spi_nor_get_flash_node(nor);
	u8 i, erase_mask;

	/* Initialize शेष flash parameters and settings. */
	params->quad_enable = spi_nor_sr2_bit1_quad_enable;
	params->set_4byte_addr_mode = spansion_set_4byte_addr_mode;
	params->setup = spi_nor_शेष_setup;
	params->otp.org = &info->otp_org;

	/* Default to 16-bit Write Status (01h) Command */
	nor->flags |= SNOR_F_HAS_16BIT_SR;

	/* Set SPI NOR sizes. */
	params->ग_लिखोsize = 1;
	params->size = (u64)info->sector_size * info->n_sectors;
	params->page_size = info->page_size;

	अगर (!(info->flags & SPI_NOR_NO_FR)) अणु
		/* Default to Fast Read क्रम DT and non-DT platक्रमm devices. */
		params->hwcaps.mask |= SNOR_HWCAPS_READ_FAST;

		/* Mask out Fast Read अगर not requested at DT instantiation. */
		अगर (np && !of_property_पढ़ो_bool(np, "m25p,fast-read"))
			params->hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;
	पूर्ण

	/* (Fast) Read settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_READ;
	spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ],
				  0, 0, SPINOR_OP_READ,
				  SNOR_PROTO_1_1_1);

	अगर (params->hwcaps.mask & SNOR_HWCAPS_READ_FAST)
		spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ_FAST],
					  0, 8, SPINOR_OP_READ_FAST,
					  SNOR_PROTO_1_1_1);

	अगर (info->flags & SPI_NOR_DUAL_READ) अणु
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
		spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ_1_1_2],
					  0, 8, SPINOR_OP_READ_1_1_2,
					  SNOR_PROTO_1_1_2);
	पूर्ण

	अगर (info->flags & SPI_NOR_QUAD_READ) अणु
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
		spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ_1_1_4],
					  0, 8, SPINOR_OP_READ_1_1_4,
					  SNOR_PROTO_1_1_4);
	पूर्ण

	अगर (info->flags & SPI_NOR_OCTAL_READ) अणु
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_8;
		spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ_1_1_8],
					  0, 8, SPINOR_OP_READ_1_1_8,
					  SNOR_PROTO_1_1_8);
	पूर्ण

	अगर (info->flags & SPI_NOR_OCTAL_DTR_READ) अणु
		params->hwcaps.mask |= SNOR_HWCAPS_READ_8_8_8_DTR;
		spi_nor_set_पढ़ो_settings(&params->पढ़ोs[SNOR_CMD_READ_8_8_8_DTR],
					  0, 20, SPINOR_OP_READ_FAST,
					  SNOR_PROTO_8_8_8_DTR);
	पूर्ण

	/* Page Program settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_PP;
	spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP],
				SPINOR_OP_PP, SNOR_PROTO_1_1_1);

	अगर (info->flags & SPI_NOR_OCTAL_DTR_PP) अणु
		params->hwcaps.mask |= SNOR_HWCAPS_PP_8_8_8_DTR;
		/*
		 * Since xSPI Page Program opcode is backward compatible with
		 * Legacy SPI, use Legacy SPI opcode there as well.
		 */
		spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP_8_8_8_DTR],
					SPINOR_OP_PP, SNOR_PROTO_8_8_8_DTR);
	पूर्ण

	/*
	 * Sector Erase settings. Sort Erase Types in ascending order, with the
	 * smallest erase size starting at BIT(0).
	 */
	erase_mask = 0;
	i = 0;
	अगर (info->flags & SECT_4K_PMC) अणु
		erase_mask |= BIT(i);
		spi_nor_set_erase_type(&map->erase_type[i], 4096u,
				       SPINOR_OP_BE_4K_PMC);
		i++;
	पूर्ण अन्यथा अगर (info->flags & SECT_4K) अणु
		erase_mask |= BIT(i);
		spi_nor_set_erase_type(&map->erase_type[i], 4096u,
				       SPINOR_OP_BE_4K);
		i++;
	पूर्ण
	erase_mask |= BIT(i);
	spi_nor_set_erase_type(&map->erase_type[i], info->sector_size,
			       SPINOR_OP_SE);
	spi_nor_init_unअगरorm_erase_map(map, erase_mask, params->size);
पूर्ण

/**
 * spi_nor_post_sfdp_fixups() - Updates the flash's parameters and settings
 * after SFDP has been parsed (is also called क्रम SPI NORs that करो not
 * support RDSFDP).
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 *
 * Typically used to tweak various parameters that could not be extracted by
 * other means (i.e. when inक्रमmation provided by the SFDP/flash_info tables
 * are incomplete or wrong).
 */
अटल व्योम spi_nor_post_sfdp_fixups(काष्ठा spi_nor *nor)
अणु
	अगर (nor->manufacturer && nor->manufacturer->fixups &&
	    nor->manufacturer->fixups->post_sfdp)
		nor->manufacturer->fixups->post_sfdp(nor);

	अगर (nor->info->fixups && nor->info->fixups->post_sfdp)
		nor->info->fixups->post_sfdp(nor);
पूर्ण

/**
 * spi_nor_late_init_params() - Late initialization of शेष flash parameters.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 *
 * Used to set शेष flash parameters and settings when the ->शेष_init()
 * hook or the SFDP parser let व्योमs.
 */
अटल व्योम spi_nor_late_init_params(काष्ठा spi_nor *nor)
अणु
	/*
	 * NOR protection support. When locking_ops are not provided, we pick
	 * the शेष ones.
	 */
	अगर (nor->flags & SNOR_F_HAS_LOCK && !nor->params->locking_ops)
		spi_nor_init_शेष_locking_ops(nor);
पूर्ण

/**
 * spi_nor_init_params() - Initialize the flash's parameters and settings.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 *
 * The flash parameters and settings are initialized based on a sequence of
 * calls that are ordered by priority:
 *
 * 1/ Default flash parameters initialization. The initializations are करोne
 *    based on nor->info data:
 *		spi_nor_info_init_params()
 *
 * which can be overwritten by:
 * 2/ Manufacturer flash parameters initialization. The initializations are
 *    करोne based on MFR रेजिस्टर, or when the decisions can not be करोne solely
 *    based on MFR, by using specअगरic flash_info tweeks, ->शेष_init():
 *		spi_nor_manufacturer_init_params()
 *
 * which can be overwritten by:
 * 3/ SFDP flash parameters initialization. JESD216 SFDP is a standard and
 *    should be more accurate that the above.
 *		spi_nor_sfdp_init_params()
 *
 *    Please note that there is a ->post_bfpt() fixup hook that can overग_लिखो
 *    the flash parameters and settings immediately after parsing the Basic
 *    Flash Parameter Table.
 *
 * which can be overwritten by:
 * 4/ Post SFDP flash parameters initialization. Used to tweak various
 *    parameters that could not be extracted by other means (i.e. when
 *    inक्रमmation provided by the SFDP/flash_info tables are incomplete or
 *    wrong).
 *		spi_nor_post_sfdp_fixups()
 *
 * 5/ Late शेष flash parameters initialization, used when the
 * ->शेष_init() hook or the SFDP parser करो not set specअगरic params.
 *		spi_nor_late_init_params()
 */
अटल पूर्णांक spi_nor_init_params(काष्ठा spi_nor *nor)
अणु
	nor->params = devm_kzalloc(nor->dev, माप(*nor->params), GFP_KERNEL);
	अगर (!nor->params)
		वापस -ENOMEM;

	spi_nor_info_init_params(nor);

	spi_nor_manufacturer_init_params(nor);

	अगर ((nor->info->flags & (SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
				 SPI_NOR_OCTAL_READ | SPI_NOR_OCTAL_DTR_READ)) &&
	    !(nor->info->flags & SPI_NOR_SKIP_SFDP))
		spi_nor_sfdp_init_params(nor);

	spi_nor_post_sfdp_fixups(nor);

	spi_nor_late_init_params(nor);

	वापस 0;
पूर्ण

/** spi_nor_octal_dtr_enable() - enable Octal DTR I/O अगर needed
 * @nor:                 poपूर्णांकer to a 'struct spi_nor'
 * @enable:              whether to enable or disable Octal DTR
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_octal_dtr_enable(काष्ठा spi_nor *nor, bool enable)
अणु
	पूर्णांक ret;

	अगर (!nor->params->octal_dtr_enable)
		वापस 0;

	अगर (!(nor->पढ़ो_proto == SNOR_PROTO_8_8_8_DTR &&
	      nor->ग_लिखो_proto == SNOR_PROTO_8_8_8_DTR))
		वापस 0;

	अगर (!(nor->flags & SNOR_F_IO_MODE_EN_VOLATILE))
		वापस 0;

	ret = nor->params->octal_dtr_enable(nor, enable);
	अगर (ret)
		वापस ret;

	अगर (enable)
		nor->reg_proto = SNOR_PROTO_8_8_8_DTR;
	अन्यथा
		nor->reg_proto = SNOR_PROTO_1_1_1;

	वापस 0;
पूर्ण

/**
 * spi_nor_quad_enable() - enable Quad I/O अगर needed.
 * @nor:                poपूर्णांकer to a 'struct spi_nor'
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_quad_enable(काष्ठा spi_nor *nor)
अणु
	अगर (!nor->params->quad_enable)
		वापस 0;

	अगर (!(spi_nor_get_protocol_width(nor->पढ़ो_proto) == 4 ||
	      spi_nor_get_protocol_width(nor->ग_लिखो_proto) == 4))
		वापस 0;

	वापस nor->params->quad_enable(nor);
पूर्ण

अटल पूर्णांक spi_nor_init(काष्ठा spi_nor *nor)
अणु
	पूर्णांक err;

	err = spi_nor_octal_dtr_enable(nor, true);
	अगर (err) अणु
		dev_dbg(nor->dev, "octal mode not supported\n");
		वापस err;
	पूर्ण

	err = spi_nor_quad_enable(nor);
	अगर (err) अणु
		dev_dbg(nor->dev, "quad mode not supported\n");
		वापस err;
	पूर्ण

	/*
	 * Some SPI NOR flashes are ग_लिखो रक्षित by शेष after a घातer-on
	 * reset cycle, in order to aव्योम inadvertent ग_लिखोs during घातer-up.
	 * Backward compatibility imposes to unlock the entire flash memory
	 * array at घातer-up by शेष. Depending on the kernel configuration
	 * (1) करो nothing, (2) always unlock the entire flash array or (3)
	 * unlock the entire flash array only when the software ग_लिखो
	 * protection bits are अस्थिर. The latter is indicated by
	 * SNOR_F_SWP_IS_VOLATILE.
	 */
	अगर (IS_ENABLED(CONFIG_MTD_SPI_NOR_SWP_DISABLE) ||
	    (IS_ENABLED(CONFIG_MTD_SPI_NOR_SWP_DISABLE_ON_VOLATILE) &&
	     nor->flags & SNOR_F_SWP_IS_VOLATILE))
		spi_nor_try_unlock_all(nor);

	अगर (nor->addr_width == 4 &&
	    nor->पढ़ो_proto != SNOR_PROTO_8_8_8_DTR &&
	    !(nor->flags & SNOR_F_4B_OPCODES)) अणु
		/*
		 * If the RESET# pin isn't hooked up properly, or the प्रणाली
		 * otherwise करोesn't perक्रमm a reset command in the boot
		 * sequence, it's impossible to 100% protect against unexpected
		 * reboots (e.g., crashes). Warn the user (or hopefully, प्रणाली
		 * designer) that this is bad.
		 */
		WARN_ONCE(nor->flags & SNOR_F_BROKEN_RESET,
			  "enabling reset hack; may not recover from unexpected reboots\n");
		nor->params->set_4byte_addr_mode(nor, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spi_nor_soft_reset(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_mem_op op;
	पूर्णांक ret;

	op = (काष्ठा spi_mem_op)SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_SRSTEN, 0),
			SPI_MEM_OP_NO_DUMMY,
			SPI_MEM_OP_NO_ADDR,
			SPI_MEM_OP_NO_DATA);

	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	ret = spi_mem_exec_op(nor->spimem, &op);
	अगर (ret) अणु
		dev_warn(nor->dev, "Software reset failed: %d\n", ret);
		वापस;
	पूर्ण

	op = (काष्ठा spi_mem_op)SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_SRST, 0),
			SPI_MEM_OP_NO_DUMMY,
			SPI_MEM_OP_NO_ADDR,
			SPI_MEM_OP_NO_DATA);

	spi_nor_spimem_setup_op(nor, &op, nor->reg_proto);

	ret = spi_mem_exec_op(nor->spimem, &op);
	अगर (ret) अणु
		dev_warn(nor->dev, "Software reset failed: %d\n", ret);
		वापस;
	पूर्ण

	/*
	 * Software Reset is not instant, and the delay varies from flash to
	 * flash. Looking at a few flashes, most range somewhere below 100
	 * microseconds. So, sleep क्रम a range of 200-400 us.
	 */
	usleep_range(SPI_NOR_SRST_SLEEP_MIN, SPI_NOR_SRST_SLEEP_MAX);
पूर्ण

/* mtd suspend handler */
अटल पूर्णांक spi_nor_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	पूर्णांक ret;

	/* Disable octal DTR mode अगर we enabled it. */
	ret = spi_nor_octal_dtr_enable(nor, false);
	अगर (ret)
		dev_err(nor->dev, "suspend() failed\n");

	वापस ret;
पूर्ण

/* mtd resume handler */
अटल व्योम spi_nor_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	काष्ठा device *dev = nor->dev;
	पूर्णांक ret;

	/* re-initialize the nor chip */
	ret = spi_nor_init(nor);
	अगर (ret)
		dev_err(dev, "resume() failed\n");
पूर्ण

अटल पूर्णांक spi_nor_get_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	काष्ठा spi_nor *nor = mtd_to_spi_nor(master);
	काष्ठा device *dev;

	अगर (nor->spimem)
		dev = nor->spimem->spi->controller->dev.parent;
	अन्यथा
		dev = nor->dev;

	अगर (!try_module_get(dev->driver->owner))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम spi_nor_put_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	काष्ठा spi_nor *nor = mtd_to_spi_nor(master);
	काष्ठा device *dev;

	अगर (nor->spimem)
		dev = nor->spimem->spi->controller->dev.parent;
	अन्यथा
		dev = nor->dev;

	module_put(dev->driver->owner);
पूर्ण

व्योम spi_nor_restore(काष्ठा spi_nor *nor)
अणु
	/* restore the addressing mode */
	अगर (nor->addr_width == 4 && !(nor->flags & SNOR_F_4B_OPCODES) &&
	    nor->flags & SNOR_F_BROKEN_RESET)
		nor->params->set_4byte_addr_mode(nor, false);

	अगर (nor->flags & SNOR_F_SOFT_RESET)
		spi_nor_soft_reset(nor);
पूर्ण
EXPORT_SYMBOL_GPL(spi_nor_restore);

अटल स्थिर काष्ठा flash_info *spi_nor_match_id(काष्ठा spi_nor *nor,
						 स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(manufacturers); i++) अणु
		क्रम (j = 0; j < manufacturers[i]->nparts; j++) अणु
			अगर (!म_भेद(name, manufacturers[i]->parts[j].name)) अणु
				nor->manufacturer = manufacturers[i];
				वापस &manufacturers[i]->parts[j];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक spi_nor_set_addr_width(काष्ठा spi_nor *nor)
अणु
	अगर (nor->addr_width) अणु
		/* alपढ़ोy configured from SFDP */
	पूर्ण अन्यथा अगर (nor->पढ़ो_proto == SNOR_PROTO_8_8_8_DTR) अणु
		/*
		 * In 8D-8D-8D mode, one byte takes half a cycle to transfer. So
		 * in this protocol an odd address width cannot be used because
		 * then the address phase would only span a cycle and a half.
		 * Half a cycle would be left over. We would then have to start
		 * the dummy phase in the middle of a cycle and so too the data
		 * phase, and we will end the transaction with half a cycle left
		 * over.
		 *
		 * Force all 8D-8D-8D flashes to use an address width of 4 to
		 * aव्योम this situation.
		 */
		nor->addr_width = 4;
	पूर्ण अन्यथा अगर (nor->info->addr_width) अणु
		nor->addr_width = nor->info->addr_width;
	पूर्ण अन्यथा अणु
		nor->addr_width = 3;
	पूर्ण

	अगर (nor->addr_width == 3 && nor->mtd.size > 0x1000000) अणु
		/* enable 4-byte addressing अगर the device exceeds 16MiB */
		nor->addr_width = 4;
	पूर्ण

	अगर (nor->addr_width > SPI_NOR_MAX_ADDR_WIDTH) अणु
		dev_dbg(nor->dev, "address width is too large: %u\n",
			nor->addr_width);
		वापस -EINVAL;
	पूर्ण

	/* Set 4byte opcodes when possible. */
	अगर (nor->addr_width == 4 && nor->flags & SNOR_F_4B_OPCODES &&
	    !(nor->flags & SNOR_F_HAS_4BAIT))
		spi_nor_set_4byte_opcodes(nor);

	वापस 0;
पूर्ण

अटल व्योम spi_nor_debugfs_init(काष्ठा spi_nor *nor,
				 स्थिर काष्ठा flash_info *info)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;

	mtd->dbg.partname = info->name;
	mtd->dbg.partid = devm_kaप्र_लिखो(nor->dev, GFP_KERNEL, "spi-nor:%*phN",
					 info->id_len, info->id);
पूर्ण

अटल स्थिर काष्ठा flash_info *spi_nor_get_flash_info(काष्ठा spi_nor *nor,
						       स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा flash_info *info = शून्य;

	अगर (name)
		info = spi_nor_match_id(nor, name);
	/* Try to स्वतः-detect अगर chip name wasn't specअगरied or not found */
	अगर (!info)
		info = spi_nor_पढ़ो_id(nor);
	अगर (IS_ERR_OR_शून्य(info))
		वापस ERR_PTR(-ENOENT);

	/*
	 * If caller has specअगरied name of flash model that can normally be
	 * detected using JEDEC, let's verअगरy it.
	 */
	अगर (name && info->id_len) अणु
		स्थिर काष्ठा flash_info *jinfo;

		jinfo = spi_nor_पढ़ो_id(nor);
		अगर (IS_ERR(jinfo)) अणु
			वापस jinfo;
		पूर्ण अन्यथा अगर (jinfo != info) अणु
			/*
			 * JEDEC knows better, so overग_लिखो platक्रमm ID. We
			 * can't trust partitions any longer, but we'll let
			 * mtd apply them anyway, since some partitions may be
			 * marked पढ़ो-only, and we करोn't want to lose that
			 * inक्रमmation, even अगर it's not 100% accurate.
			 */
			dev_warn(nor->dev, "found %s, expected %s\n",
				 jinfo->name, info->name);
			info = jinfo;
		पूर्ण
	पूर्ण

	वापस info;
पूर्ण

पूर्णांक spi_nor_scan(काष्ठा spi_nor *nor, स्थिर अक्षर *name,
		 स्थिर काष्ठा spi_nor_hwcaps *hwcaps)
अणु
	स्थिर काष्ठा flash_info *info;
	काष्ठा device *dev = nor->dev;
	काष्ठा mtd_info *mtd = &nor->mtd;
	काष्ठा device_node *np = spi_nor_get_flash_node(nor);
	पूर्णांक ret;
	पूर्णांक i;

	ret = spi_nor_check(nor);
	अगर (ret)
		वापस ret;

	/* Reset SPI protocol क्रम all commands. */
	nor->reg_proto = SNOR_PROTO_1_1_1;
	nor->पढ़ो_proto = SNOR_PROTO_1_1_1;
	nor->ग_लिखो_proto = SNOR_PROTO_1_1_1;

	/*
	 * We need the bounce buffer early to पढ़ो/ग_लिखो रेजिस्टरs when going
	 * through the spi-mem layer (buffers have to be DMA-able).
	 * For spi-mem drivers, we'll पुनः_स्मृतिate a new buffer अगर
	 * nor->page_size turns out to be greater than PAGE_SIZE (which
	 * shouldn't happen beक्रमe दीर्घ since NOR pages are usually less
	 * than 1KB) after spi_nor_scan() वापसs.
	 */
	nor->bouncebuf_size = PAGE_SIZE;
	nor->bouncebuf = devm_kदो_स्मृति(dev, nor->bouncebuf_size,
				      GFP_KERNEL);
	अगर (!nor->bouncebuf)
		वापस -ENOMEM;

	info = spi_nor_get_flash_info(nor, name);
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	nor->info = info;

	spi_nor_debugfs_init(nor, info);

	mutex_init(&nor->lock);

	/*
	 * Make sure the XSR_RDY flag is set beक्रमe calling
	 * spi_nor_रुको_till_पढ़ोy(). Xilinx S3AN share MFR
	 * with Aपंचांगel SPI NOR.
	 */
	अगर (info->flags & SPI_NOR_XSR_RDY)
		nor->flags |=  SNOR_F_READY_XSR_RDY;

	अगर (info->flags & SPI_NOR_HAS_LOCK)
		nor->flags |= SNOR_F_HAS_LOCK;

	mtd->_ग_लिखो = spi_nor_ग_लिखो;

	/* Init flash parameters based on flash_info काष्ठा and SFDP */
	ret = spi_nor_init_params(nor);
	अगर (ret)
		वापस ret;

	अगर (!mtd->name)
		mtd->name = dev_name(dev);
	mtd->priv = nor;
	mtd->type = MTD_NORFLASH;
	mtd->ग_लिखोsize = nor->params->ग_लिखोsize;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->size = nor->params->size;
	mtd->_erase = spi_nor_erase;
	mtd->_पढ़ो = spi_nor_पढ़ो;
	mtd->_suspend = spi_nor_suspend;
	mtd->_resume = spi_nor_resume;
	mtd->_get_device = spi_nor_get_device;
	mtd->_put_device = spi_nor_put_device;

	अगर (info->flags & USE_FSR)
		nor->flags |= SNOR_F_USE_FSR;
	अगर (info->flags & SPI_NOR_HAS_TB) अणु
		nor->flags |= SNOR_F_HAS_SR_TB;
		अगर (info->flags & SPI_NOR_TB_SR_BIT6)
			nor->flags |= SNOR_F_HAS_SR_TB_BIT6;
	पूर्ण

	अगर (info->flags & NO_CHIP_ERASE)
		nor->flags |= SNOR_F_NO_OP_CHIP_ERASE;
	अगर (info->flags & USE_CLSR)
		nor->flags |= SNOR_F_USE_CLSR;
	अगर (info->flags & SPI_NOR_SWP_IS_VOLATILE)
		nor->flags |= SNOR_F_SWP_IS_VOLATILE;

	अगर (info->flags & SPI_NOR_4BIT_BP) अणु
		nor->flags |= SNOR_F_HAS_4BIT_BP;
		अगर (info->flags & SPI_NOR_BP3_SR_BIT6)
			nor->flags |= SNOR_F_HAS_SR_BP3_BIT6;
	पूर्ण

	अगर (info->flags & SPI_NOR_NO_ERASE)
		mtd->flags |= MTD_NO_ERASE;

	mtd->dev.parent = dev;
	nor->page_size = nor->params->page_size;
	mtd->ग_लिखोbufsize = nor->page_size;

	अगर (of_property_पढ़ो_bool(np, "broken-flash-reset"))
		nor->flags |= SNOR_F_BROKEN_RESET;

	/*
	 * Configure the SPI memory:
	 * - select op codes क्रम (Fast) Read, Page Program and Sector Erase.
	 * - set the number of dummy cycles (mode cycles + रुको states).
	 * - set the SPI protocols क्रम रेजिस्टर and memory accesses.
	 */
	ret = spi_nor_setup(nor, hwcaps);
	अगर (ret)
		वापस ret;

	अगर (info->flags & SPI_NOR_4B_OPCODES)
		nor->flags |= SNOR_F_4B_OPCODES;

	अगर (info->flags & SPI_NOR_IO_MODE_EN_VOLATILE)
		nor->flags |= SNOR_F_IO_MODE_EN_VOLATILE;

	ret = spi_nor_set_addr_width(nor);
	अगर (ret)
		वापस ret;

	spi_nor_रेजिस्टर_locking_ops(nor);

	/* Send all the required SPI flash commands to initialize device */
	ret = spi_nor_init(nor);
	अगर (ret)
		वापस ret;

	/* Configure OTP parameters and ops */
	spi_nor_otp_init(nor);

	dev_info(dev, "%s (%lld Kbytes)\n", info->name,
			(दीर्घ दीर्घ)mtd->size >> 10);

	dev_dbg(dev,
		"mtd .name = %s, .size = 0x%llx (%lldMiB), "
		".erasesize = 0x%.8x (%uKiB) .numeraseregions = %d\n",
		mtd->name, (दीर्घ दीर्घ)mtd->size, (दीर्घ दीर्घ)(mtd->size >> 20),
		mtd->erasesize, mtd->erasesize / 1024, mtd->numeraseregions);

	अगर (mtd->numeraseregions)
		क्रम (i = 0; i < mtd->numeraseregions; i++)
			dev_dbg(dev,
				"mtd.eraseregions[%d] = { .offset = 0x%llx, "
				".erasesize = 0x%.8x (%uKiB), "
				".numblocks = %d }\n",
				i, (दीर्घ दीर्घ)mtd->eraseregions[i].offset,
				mtd->eraseregions[i].erasesize,
				mtd->eraseregions[i].erasesize / 1024,
				mtd->eraseregions[i].numblocks);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_nor_scan);

अटल पूर्णांक spi_nor_create_पढ़ो_dirmap(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_mem_dirmap_info info = अणु
		.op_पंचांगpl = SPI_MEM_OP(SPI_MEM_OP_CMD(nor->पढ़ो_opcode, 0),
				      SPI_MEM_OP_ADDR(nor->addr_width, 0, 0),
				      SPI_MEM_OP_DUMMY(nor->पढ़ो_dummy, 0),
				      SPI_MEM_OP_DATA_IN(0, शून्य, 0)),
		.offset = 0,
		.length = nor->mtd.size,
	पूर्ण;
	काष्ठा spi_mem_op *op = &info.op_पंचांगpl;

	spi_nor_spimem_setup_op(nor, op, nor->पढ़ो_proto);

	/* convert the dummy cycles to the number of bytes */
	op->dummy.nbytes = (nor->पढ़ो_dummy * op->dummy.buswidth) / 8;
	अगर (spi_nor_protocol_is_dtr(nor->पढ़ो_proto))
		op->dummy.nbytes *= 2;

	/*
	 * Since spi_nor_spimem_setup_op() only sets buswidth when the number
	 * of data bytes is non-zero, the data buswidth won't be set here. So,
	 * करो it explicitly.
	 */
	op->data.buswidth = spi_nor_get_protocol_data_nbits(nor->पढ़ो_proto);

	nor->dirmap.rdesc = devm_spi_mem_dirmap_create(nor->dev, nor->spimem,
						       &info);
	वापस PTR_ERR_OR_ZERO(nor->dirmap.rdesc);
पूर्ण

अटल पूर्णांक spi_nor_create_ग_लिखो_dirmap(काष्ठा spi_nor *nor)
अणु
	काष्ठा spi_mem_dirmap_info info = अणु
		.op_पंचांगpl = SPI_MEM_OP(SPI_MEM_OP_CMD(nor->program_opcode, 0),
				      SPI_MEM_OP_ADDR(nor->addr_width, 0, 0),
				      SPI_MEM_OP_NO_DUMMY,
				      SPI_MEM_OP_DATA_OUT(0, शून्य, 0)),
		.offset = 0,
		.length = nor->mtd.size,
	पूर्ण;
	काष्ठा spi_mem_op *op = &info.op_पंचांगpl;

	अगर (nor->program_opcode == SPINOR_OP_AAI_WP && nor->sst_ग_लिखो_second)
		op->addr.nbytes = 0;

	spi_nor_spimem_setup_op(nor, op, nor->ग_लिखो_proto);

	/*
	 * Since spi_nor_spimem_setup_op() only sets buswidth when the number
	 * of data bytes is non-zero, the data buswidth won't be set here. So,
	 * करो it explicitly.
	 */
	op->data.buswidth = spi_nor_get_protocol_data_nbits(nor->ग_लिखो_proto);

	nor->dirmap.wdesc = devm_spi_mem_dirmap_create(nor->dev, nor->spimem,
						       &info);
	वापस PTR_ERR_OR_ZERO(nor->dirmap.wdesc);
पूर्ण

अटल पूर्णांक spi_nor_probe(काष्ठा spi_mem *spimem)
अणु
	काष्ठा spi_device *spi = spimem->spi;
	काष्ठा flash_platक्रमm_data *data = dev_get_platdata(&spi->dev);
	काष्ठा spi_nor *nor;
	/*
	 * Enable all caps by शेष. The core will mask them after
	 * checking what's really supported using spi_mem_supports_op().
	 */
	स्थिर काष्ठा spi_nor_hwcaps hwcaps = अणु .mask = SNOR_HWCAPS_ALL पूर्ण;
	अक्षर *flash_name;
	पूर्णांक ret;

	nor = devm_kzalloc(&spi->dev, माप(*nor), GFP_KERNEL);
	अगर (!nor)
		वापस -ENOMEM;

	nor->spimem = spimem;
	nor->dev = &spi->dev;
	spi_nor_set_flash_node(nor, spi->dev.of_node);

	spi_mem_set_drvdata(spimem, nor);

	अगर (data && data->name)
		nor->mtd.name = data->name;

	अगर (!nor->mtd.name)
		nor->mtd.name = spi_mem_get_name(spimem);

	/*
	 * For some (historical?) reason many platक्रमms provide two dअगरferent
	 * names in flash_platक्रमm_data: "name" and "type". Quite often name is
	 * set to "m25p80" and then "type" provides a real chip name.
	 * If that's the हाल, respect "type" and ignore a "name".
	 */
	अगर (data && data->type)
		flash_name = data->type;
	अन्यथा अगर (!म_भेद(spi->modalias, "spi-nor"))
		flash_name = शून्य; /* स्वतः-detect */
	अन्यथा
		flash_name = spi->modalias;

	ret = spi_nor_scan(nor, flash_name, &hwcaps);
	अगर (ret)
		वापस ret;

	/*
	 * None of the existing parts have > 512B pages, but let's play safe
	 * and add this logic so that अगर anyone ever adds support क्रम such
	 * a NOR we करोn't end up with buffer overflows.
	 */
	अगर (nor->page_size > PAGE_SIZE) अणु
		nor->bouncebuf_size = nor->page_size;
		devm_kमुक्त(nor->dev, nor->bouncebuf);
		nor->bouncebuf = devm_kदो_स्मृति(nor->dev,
					      nor->bouncebuf_size,
					      GFP_KERNEL);
		अगर (!nor->bouncebuf)
			वापस -ENOMEM;
	पूर्ण

	ret = spi_nor_create_पढ़ो_dirmap(nor);
	अगर (ret)
		वापस ret;

	ret = spi_nor_create_ग_लिखो_dirmap(nor);
	अगर (ret)
		वापस ret;

	वापस mtd_device_रेजिस्टर(&nor->mtd, data ? data->parts : शून्य,
				   data ? data->nr_parts : 0);
पूर्ण

अटल पूर्णांक spi_nor_हटाओ(काष्ठा spi_mem *spimem)
अणु
	काष्ठा spi_nor *nor = spi_mem_get_drvdata(spimem);

	spi_nor_restore(nor);

	/* Clean up MTD stuff. */
	वापस mtd_device_unरेजिस्टर(&nor->mtd);
पूर्ण

अटल व्योम spi_nor_shutकरोwn(काष्ठा spi_mem *spimem)
अणु
	काष्ठा spi_nor *nor = spi_mem_get_drvdata(spimem);

	spi_nor_restore(nor);
पूर्ण

/*
 * Do NOT add to this array without पढ़ोing the following:
 *
 * Historically, many flash devices are bound to this driver by their name. But
 * since most of these flash are compatible to some extent, and their
 * dअगरferences can often be dअगरferentiated by the JEDEC पढ़ो-ID command, we
 * encourage new users to add support to the spi-nor library, and simply bind
 * against a generic string here (e.g., "jedec,spi-nor").
 *
 * Many flash names are kept here in this list (as well as in spi-nor.c) to
 * keep them available as module aliases क्रम existing platक्रमms.
 */
अटल स्थिर काष्ठा spi_device_id spi_nor_dev_ids[] = अणु
	/*
	 * Allow non-DT platक्रमm devices to bind to the "spi-nor" modalias, and
	 * hack around the fact that the SPI core करोes not provide uevent
	 * matching क्रम .of_match_table
	 */
	अणु"spi-nor"पूर्ण,

	/*
	 * Entries not used in DTs that should be safe to drop after replacing
	 * them with "spi-nor" in platक्रमm data.
	 */
	अणु"s25sl064a"पूर्ण,	अणु"w25x16"पूर्ण,	अणु"m25p10"पूर्ण,	अणु"m25px64"पूर्ण,

	/*
	 * Entries that were used in DTs without "jedec,spi-nor" fallback and
	 * should be kept क्रम backward compatibility.
	 */
	अणु"at25df321a"पूर्ण,	अणु"at25df641"पूर्ण,	अणु"at26df081a"पूर्ण,
	अणु"mx25l4005a"पूर्ण,	अणु"mx25l1606e"पूर्ण,	अणु"mx25l6405d"पूर्ण,	अणु"mx25l12805d"पूर्ण,
	अणु"mx25l25635e"पूर्ण,अणु"mx66l51235l"पूर्ण,
	अणु"n25q064"पूर्ण,	अणु"n25q128a11"पूर्ण,	अणु"n25q128a13"पूर्ण,	अणु"n25q512a"पूर्ण,
	अणु"s25fl256s1"पूर्ण,	अणु"s25fl512s"पूर्ण,	अणु"s25sl12801"पूर्ण,	अणु"s25fl008k"पूर्ण,
	अणु"s25fl064k"पूर्ण,
	अणु"sst25vf040b"पूर्ण,अणु"sst25vf016b"पूर्ण,अणु"sst25vf032b"पूर्ण,अणु"sst25wf040"पूर्ण,
	अणु"m25p40"पूर्ण,	अणु"m25p80"पूर्ण,	अणु"m25p16"पूर्ण,	अणु"m25p32"पूर्ण,
	अणु"m25p64"पूर्ण,	अणु"m25p128"पूर्ण,
	अणु"w25x80"पूर्ण,	अणु"w25x32"पूर्ण,	अणु"w25q32"पूर्ण,	अणु"w25q32dw"पूर्ण,
	अणु"w25q80bl"पूर्ण,	अणु"w25q128"पूर्ण,	अणु"w25q256"पूर्ण,

	/* Flashes that can't be detected using JEDEC */
	अणु"m25p05-nonjedec"पूर्ण,	अणु"m25p10-nonjedec"पूर्ण,	अणु"m25p20-nonjedec"पूर्ण,
	अणु"m25p40-nonjedec"पूर्ण,	अणु"m25p80-nonjedec"पूर्ण,	अणु"m25p16-nonjedec"पूर्ण,
	अणु"m25p32-nonjedec"पूर्ण,	अणु"m25p64-nonjedec"पूर्ण,	अणु"m25p128-nonjedec"पूर्ण,

	/* Everspin MRAMs (non-JEDEC) */
	अणु "mr25h128" पूर्ण, /* 128 Kib, 40 MHz */
	अणु "mr25h256" पूर्ण, /* 256 Kib, 40 MHz */
	अणु "mr25h10" पूर्ण,  /*   1 Mib, 40 MHz */
	अणु "mr25h40" पूर्ण,  /*   4 Mib, 40 MHz */

	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, spi_nor_dev_ids);

अटल स्थिर काष्ठा of_device_id spi_nor_of_table[] = अणु
	/*
	 * Generic compatibility क्रम SPI NOR that can be identअगरied by the
	 * JEDEC READ ID opcode (0x9F). Use this, अगर possible.
	 */
	अणु .compatible = "jedec,spi-nor" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_nor_of_table);

/*
 * REVISIT: many of these chips have deep घातer-करोwn modes, which
 * should clearly be entered on suspend() to minimize घातer use.
 * And also when they're otherwise idle...
 */
अटल काष्ठा spi_mem_driver spi_nor_driver = अणु
	.spidrv = अणु
		.driver = अणु
			.name = "spi-nor",
			.of_match_table = spi_nor_of_table,
		पूर्ण,
		.id_table = spi_nor_dev_ids,
	पूर्ण,
	.probe = spi_nor_probe,
	.हटाओ = spi_nor_हटाओ,
	.shutकरोwn = spi_nor_shutकरोwn,
पूर्ण;
module_spi_mem_driver(spi_nor_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Huang Shijie <shijie8@gmail.com>");
MODULE_AUTHOR("Mike Lavender");
MODULE_DESCRIPTION("framework for SPI NOR");
