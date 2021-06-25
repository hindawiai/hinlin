<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright (C) IBM Corporation 2020

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/fsi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>

#घोषणा FSI_ENGID_SPI			0x23
#घोषणा FSI_MBOX_ROOT_CTRL_8		0x2860
#घोषणा  FSI_MBOX_ROOT_CTRL_8_SPI_MUX	 0xf0000000

#घोषणा FSI2SPI_DATA0			0x00
#घोषणा FSI2SPI_DATA1			0x04
#घोषणा FSI2SPI_CMD			0x08
#घोषणा  FSI2SPI_CMD_WRITE		 BIT(31)
#घोषणा FSI2SPI_RESET			0x18
#घोषणा FSI2SPI_STATUS			0x1c
#घोषणा  FSI2SPI_STATUS_ANY_ERROR	 BIT(31)
#घोषणा FSI2SPI_IRQ			0x20

#घोषणा SPI_FSI_BASE			0x70000
#घोषणा SPI_FSI_INIT_TIMEOUT_MS		1000
#घोषणा SPI_FSI_MAX_XFR_SIZE		2048
#घोषणा SPI_FSI_MAX_XFR_SIZE_RESTRICTED	8

#घोषणा SPI_FSI_ERROR			0x0
#घोषणा SPI_FSI_COUNTER_CFG		0x1
#घोषणा  SPI_FSI_COUNTER_CFG_LOOPS(x)	 (((u64)(x) & 0xffULL) << 32)
#घोषणा  SPI_FSI_COUNTER_CFG_N2_RX	 BIT_ULL(8)
#घोषणा  SPI_FSI_COUNTER_CFG_N2_TX	 BIT_ULL(9)
#घोषणा  SPI_FSI_COUNTER_CFG_N2_IMPLICIT BIT_ULL(10)
#घोषणा  SPI_FSI_COUNTER_CFG_N2_RELOAD	 BIT_ULL(11)
#घोषणा SPI_FSI_CFG1			0x2
#घोषणा SPI_FSI_CLOCK_CFG		0x3
#घोषणा  SPI_FSI_CLOCK_CFG_MM_ENABLE	 BIT_ULL(32)
#घोषणा  SPI_FSI_CLOCK_CFG_ECC_DISABLE	 (BIT_ULL(35) | BIT_ULL(33))
#घोषणा  SPI_FSI_CLOCK_CFG_RESET1	 (BIT_ULL(36) | BIT_ULL(38))
#घोषणा  SPI_FSI_CLOCK_CFG_RESET2	 (BIT_ULL(37) | BIT_ULL(39))
#घोषणा  SPI_FSI_CLOCK_CFG_MODE		 (BIT_ULL(41) | BIT_ULL(42))
#घोषणा  SPI_FSI_CLOCK_CFG_SCK_RECV_DEL	 GENMASK_ULL(51, 44)
#घोषणा   SPI_FSI_CLOCK_CFG_SCK_NO_DEL	  BIT_ULL(51)
#घोषणा  SPI_FSI_CLOCK_CFG_SCK_DIV	 GENMASK_ULL(63, 52)
#घोषणा SPI_FSI_MMAP			0x4
#घोषणा SPI_FSI_DATA_TX			0x5
#घोषणा SPI_FSI_DATA_RX			0x6
#घोषणा SPI_FSI_SEQUENCE		0x7
#घोषणा  SPI_FSI_SEQUENCE_STOP		 0x00
#घोषणा  SPI_FSI_SEQUENCE_SEL_SLAVE(x)	 (0x10 | ((x) & 0xf))
#घोषणा  SPI_FSI_SEQUENCE_SHIFT_OUT(x)	 (0x30 | ((x) & 0xf))
#घोषणा  SPI_FSI_SEQUENCE_SHIFT_IN(x)	 (0x40 | ((x) & 0xf))
#घोषणा  SPI_FSI_SEQUENCE_COPY_DATA_TX	 0xc0
#घोषणा  SPI_FSI_SEQUENCE_BRANCH(x)	 (0xe0 | ((x) & 0xf))
#घोषणा SPI_FSI_STATUS			0x8
#घोषणा  SPI_FSI_STATUS_ERROR		 \
	(GENMASK_ULL(31, 21) | GENMASK_ULL(15, 12))
#घोषणा  SPI_FSI_STATUS_SEQ_STATE	 GENMASK_ULL(55, 48)
#घोषणा   SPI_FSI_STATUS_SEQ_STATE_IDLE	  BIT_ULL(48)
#घोषणा  SPI_FSI_STATUS_TDR_UNDERRUN	 BIT_ULL(57)
#घोषणा  SPI_FSI_STATUS_TDR_OVERRUN	 BIT_ULL(58)
#घोषणा  SPI_FSI_STATUS_TDR_FULL	 BIT_ULL(59)
#घोषणा  SPI_FSI_STATUS_RDR_UNDERRUN	 BIT_ULL(61)
#घोषणा  SPI_FSI_STATUS_RDR_OVERRUN	 BIT_ULL(62)
#घोषणा  SPI_FSI_STATUS_RDR_FULL	 BIT_ULL(63)
#घोषणा  SPI_FSI_STATUS_ANY_ERROR	 \
	(SPI_FSI_STATUS_ERROR | \
	 SPI_FSI_STATUS_TDR_OVERRUN | SPI_FSI_STATUS_RDR_UNDERRUN | \
	 SPI_FSI_STATUS_RDR_OVERRUN)
#घोषणा SPI_FSI_PORT_CTRL		0x9

काष्ठा fsi_spi अणु
	काष्ठा device *dev;	/* SPI controller device */
	काष्ठा fsi_device *fsi;	/* FSI2SPI CFAM engine device */
	u32 base;
	माप_प्रकार max_xfr_size;
	bool restricted;
पूर्ण;

काष्ठा fsi_spi_sequence अणु
	पूर्णांक bit;
	u64 data;
पूर्ण;

अटल पूर्णांक fsi_spi_check_mux(काष्ठा fsi_device *fsi, काष्ठा device *dev)
अणु
	पूर्णांक rc;
	u32 root_ctrl_8;
	__be32 root_ctrl_8_be;

	rc = fsi_slave_पढ़ो(fsi->slave, FSI_MBOX_ROOT_CTRL_8, &root_ctrl_8_be,
			    माप(root_ctrl_8_be));
	अगर (rc)
		वापस rc;

	root_ctrl_8 = be32_to_cpu(root_ctrl_8_be);
	dev_dbg(dev, "Root control register 8: %08x\n", root_ctrl_8);
	अगर ((root_ctrl_8 & FSI_MBOX_ROOT_CTRL_8_SPI_MUX) ==
	     FSI_MBOX_ROOT_CTRL_8_SPI_MUX)
		वापस 0;

	वापस -ENOLINK;
पूर्ण

अटल पूर्णांक fsi_spi_check_status(काष्ठा fsi_spi *ctx)
अणु
	पूर्णांक rc;
	u32 sts;
	__be32 sts_be;

	rc = fsi_device_पढ़ो(ctx->fsi, FSI2SPI_STATUS, &sts_be,
			     माप(sts_be));
	अगर (rc)
		वापस rc;

	sts = be32_to_cpu(sts_be);
	अगर (sts & FSI2SPI_STATUS_ANY_ERROR) अणु
		dev_err(ctx->dev, "Error with FSI2SPI interface: %08x.\n", sts);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_spi_पढ़ो_reg(काष्ठा fsi_spi *ctx, u32 offset, u64 *value)
अणु
	पूर्णांक rc;
	__be32 cmd_be;
	__be32 data_be;
	u32 cmd = offset + ctx->base;

	*value = 0ULL;

	अगर (cmd & FSI2SPI_CMD_WRITE)
		वापस -EINVAL;

	cmd_be = cpu_to_be32(cmd);
	rc = fsi_device_ग_लिखो(ctx->fsi, FSI2SPI_CMD, &cmd_be, माप(cmd_be));
	अगर (rc)
		वापस rc;

	rc = fsi_spi_check_status(ctx);
	अगर (rc)
		वापस rc;

	rc = fsi_device_पढ़ो(ctx->fsi, FSI2SPI_DATA0, &data_be,
			     माप(data_be));
	अगर (rc)
		वापस rc;

	*value |= (u64)be32_to_cpu(data_be) << 32;

	rc = fsi_device_पढ़ो(ctx->fsi, FSI2SPI_DATA1, &data_be,
			     माप(data_be));
	अगर (rc)
		वापस rc;

	*value |= (u64)be32_to_cpu(data_be);
	dev_dbg(ctx->dev, "Read %02x[%016llx].\n", offset, *value);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_spi_ग_लिखो_reg(काष्ठा fsi_spi *ctx, u32 offset, u64 value)
अणु
	पूर्णांक rc;
	__be32 cmd_be;
	__be32 data_be;
	u32 cmd = offset + ctx->base;

	अगर (cmd & FSI2SPI_CMD_WRITE)
		वापस -EINVAL;

	dev_dbg(ctx->dev, "Write %02x[%016llx].\n", offset, value);

	data_be = cpu_to_be32(upper_32_bits(value));
	rc = fsi_device_ग_लिखो(ctx->fsi, FSI2SPI_DATA0, &data_be,
			      माप(data_be));
	अगर (rc)
		वापस rc;

	data_be = cpu_to_be32(lower_32_bits(value));
	rc = fsi_device_ग_लिखो(ctx->fsi, FSI2SPI_DATA1, &data_be,
			      माप(data_be));
	अगर (rc)
		वापस rc;

	cmd_be = cpu_to_be32(cmd | FSI2SPI_CMD_WRITE);
	rc = fsi_device_ग_लिखो(ctx->fsi, FSI2SPI_CMD, &cmd_be, माप(cmd_be));
	अगर (rc)
		वापस rc;

	वापस fsi_spi_check_status(ctx);
पूर्ण

अटल पूर्णांक fsi_spi_data_in(u64 in, u8 *rx, पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक num_bytes = min(len, 8);

	क्रम (i = 0; i < num_bytes; ++i)
		rx[i] = (u8)(in >> (8 * ((num_bytes - 1) - i)));

	वापस num_bytes;
पूर्ण

अटल पूर्णांक fsi_spi_data_out(u64 *out, स्थिर u8 *tx, पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक num_bytes = min(len, 8);
	u8 *out_bytes = (u8 *)out;

	/* Unused bytes of the tx data should be 0. */
	*out = 0ULL;

	क्रम (i = 0; i < num_bytes; ++i)
		out_bytes[8 - (i + 1)] = tx[i];

	वापस num_bytes;
पूर्ण

अटल पूर्णांक fsi_spi_reset(काष्ठा fsi_spi *ctx)
अणु
	पूर्णांक rc;

	dev_dbg(ctx->dev, "Resetting SPI controller.\n");

	rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_CLOCK_CFG,
			       SPI_FSI_CLOCK_CFG_RESET1);
	अगर (rc)
		वापस rc;

	rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_CLOCK_CFG,
			       SPI_FSI_CLOCK_CFG_RESET2);
	अगर (rc)
		वापस rc;

	वापस fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_STATUS, 0ULL);
पूर्ण

अटल पूर्णांक fsi_spi_sequence_add(काष्ठा fsi_spi_sequence *seq, u8 val)
अणु
	/*
	 * Add the next byte of inकाष्ठाion to the 8-byte sequence रेजिस्टर.
	 * Then decrement the counter so that the next inकाष्ठाion will go in
	 * the right place. Return the index of the slot we just filled in the
	 * sequence रेजिस्टर.
	 */
	seq->data |= (u64)val << seq->bit;
	seq->bit -= 8;

	वापस ((64 - seq->bit) / 8) - 2;
पूर्ण

अटल व्योम fsi_spi_sequence_init(काष्ठा fsi_spi_sequence *seq)
अणु
	seq->bit = 56;
	seq->data = 0ULL;
पूर्ण

अटल पूर्णांक fsi_spi_sequence_transfer(काष्ठा fsi_spi *ctx,
				     काष्ठा fsi_spi_sequence *seq,
				     काष्ठा spi_transfer *transfer)
अणु
	पूर्णांक loops;
	पूर्णांक idx;
	पूर्णांक rc;
	u8 val = 0;
	u8 len = min(transfer->len, 8U);
	u8 rem = transfer->len % len;

	loops = transfer->len / len;

	अगर (transfer->tx_buf) अणु
		val = SPI_FSI_SEQUENCE_SHIFT_OUT(len);
		idx = fsi_spi_sequence_add(seq, val);

		अगर (rem)
			rem = SPI_FSI_SEQUENCE_SHIFT_OUT(rem);
	पूर्ण अन्यथा अगर (transfer->rx_buf) अणु
		val = SPI_FSI_SEQUENCE_SHIFT_IN(len);
		idx = fsi_spi_sequence_add(seq, val);

		अगर (rem)
			rem = SPI_FSI_SEQUENCE_SHIFT_IN(rem);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->restricted && loops > 1) अणु
		dev_warn(ctx->dev,
			 "Transfer too large; no branches permitted.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (loops > 1) अणु
		u64 cfg = SPI_FSI_COUNTER_CFG_LOOPS(loops - 1);

		fsi_spi_sequence_add(seq, SPI_FSI_SEQUENCE_BRANCH(idx));

		अगर (transfer->rx_buf)
			cfg |= SPI_FSI_COUNTER_CFG_N2_RX |
				SPI_FSI_COUNTER_CFG_N2_TX |
				SPI_FSI_COUNTER_CFG_N2_IMPLICIT |
				SPI_FSI_COUNTER_CFG_N2_RELOAD;

		rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_COUNTER_CFG, cfg);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_COUNTER_CFG, 0ULL);
	पूर्ण

	अगर (rem)
		fsi_spi_sequence_add(seq, rem);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_spi_transfer_data(काष्ठा fsi_spi *ctx,
				 काष्ठा spi_transfer *transfer)
अणु
	पूर्णांक rc = 0;
	u64 status = 0ULL;
	u64 cfg = 0ULL;

	अगर (transfer->tx_buf) अणु
		पूर्णांक nb;
		पूर्णांक sent = 0;
		u64 out = 0ULL;
		स्थिर u8 *tx = transfer->tx_buf;

		जबतक (transfer->len > sent) अणु
			nb = fsi_spi_data_out(&out, &tx[sent],
					      (पूर्णांक)transfer->len - sent);

			rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_DATA_TX, out);
			अगर (rc)
				वापस rc;

			करो अणु
				rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_STATUS,
						      &status);
				अगर (rc)
					वापस rc;

				अगर (status & SPI_FSI_STATUS_ANY_ERROR) अणु
					rc = fsi_spi_reset(ctx);
					अगर (rc)
						वापस rc;

					वापस -EREMOTEIO;
				पूर्ण
			पूर्ण जबतक (status & SPI_FSI_STATUS_TDR_FULL);

			sent += nb;
		पूर्ण
	पूर्ण अन्यथा अगर (transfer->rx_buf) अणु
		पूर्णांक recv = 0;
		u64 in = 0ULL;
		u8 *rx = transfer->rx_buf;

		rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_COUNTER_CFG, &cfg);
		अगर (rc)
			वापस rc;

		अगर (cfg & SPI_FSI_COUNTER_CFG_N2_IMPLICIT) अणु
			rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_DATA_TX, 0);
			अगर (rc)
				वापस rc;
		पूर्ण

		जबतक (transfer->len > recv) अणु
			करो अणु
				rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_STATUS,
						      &status);
				अगर (rc)
					वापस rc;

				अगर (status & SPI_FSI_STATUS_ANY_ERROR) अणु
					rc = fsi_spi_reset(ctx);
					अगर (rc)
						वापस rc;

					वापस -EREMOTEIO;
				पूर्ण
			पूर्ण जबतक (!(status & SPI_FSI_STATUS_RDR_FULL));

			rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_DATA_RX, &in);
			अगर (rc)
				वापस rc;

			recv += fsi_spi_data_in(in, &rx[recv],
						(पूर्णांक)transfer->len - recv);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_spi_transfer_init(काष्ठा fsi_spi *ctx)
अणु
	पूर्णांक rc;
	bool reset = false;
	अचिन्हित दीर्घ end;
	u64 seq_state;
	u64 घड़ी_cfg = 0ULL;
	u64 status = 0ULL;
	u64 wanted_घड़ी_cfg = SPI_FSI_CLOCK_CFG_ECC_DISABLE |
		SPI_FSI_CLOCK_CFG_SCK_NO_DEL |
		FIELD_PREP(SPI_FSI_CLOCK_CFG_SCK_DIV, 19);

	end = jअगरfies + msecs_to_jअगरfies(SPI_FSI_INIT_TIMEOUT_MS);
	करो अणु
		अगर (समय_after(jअगरfies, end))
			वापस -ETIMEDOUT;

		rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_STATUS, &status);
		अगर (rc)
			वापस rc;

		seq_state = status & SPI_FSI_STATUS_SEQ_STATE;

		अगर (status & (SPI_FSI_STATUS_ANY_ERROR |
			      SPI_FSI_STATUS_TDR_FULL |
			      SPI_FSI_STATUS_RDR_FULL)) अणु
			अगर (reset)
				वापस -EIO;

			rc = fsi_spi_reset(ctx);
			अगर (rc)
				वापस rc;

			reset = true;
			जारी;
		पूर्ण
	पूर्ण जबतक (seq_state && (seq_state != SPI_FSI_STATUS_SEQ_STATE_IDLE));

	rc = fsi_spi_पढ़ो_reg(ctx, SPI_FSI_CLOCK_CFG, &घड़ी_cfg);
	अगर (rc)
		वापस rc;

	अगर ((घड़ी_cfg & (SPI_FSI_CLOCK_CFG_MM_ENABLE |
			  SPI_FSI_CLOCK_CFG_ECC_DISABLE |
			  SPI_FSI_CLOCK_CFG_MODE |
			  SPI_FSI_CLOCK_CFG_SCK_RECV_DEL |
			  SPI_FSI_CLOCK_CFG_SCK_DIV)) != wanted_घड़ी_cfg)
		rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_CLOCK_CFG,
				       wanted_घड़ी_cfg);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_spi_transfer_one_message(काष्ठा spi_controller *ctlr,
					काष्ठा spi_message *mesg)
अणु
	पूर्णांक rc;
	u8 seq_slave = SPI_FSI_SEQUENCE_SEL_SLAVE(mesg->spi->chip_select + 1);
	काष्ठा spi_transfer *transfer;
	काष्ठा fsi_spi *ctx = spi_controller_get_devdata(ctlr);

	rc = fsi_spi_check_mux(ctx->fsi, ctx->dev);
	अगर (rc)
		जाओ error;

	list_क्रम_each_entry(transfer, &mesg->transfers, transfer_list) अणु
		काष्ठा fsi_spi_sequence seq;
		काष्ठा spi_transfer *next = शून्य;

		/* Sequencer must करो shअगरt out (tx) first. */
		अगर (!transfer->tx_buf ||
		    transfer->len > (ctx->max_xfr_size + 8)) अणु
			rc = -EINVAL;
			जाओ error;
		पूर्ण

		dev_dbg(ctx->dev, "Start tx of %d bytes.\n", transfer->len);

		rc = fsi_spi_transfer_init(ctx);
		अगर (rc < 0)
			जाओ error;

		fsi_spi_sequence_init(&seq);
		fsi_spi_sequence_add(&seq, seq_slave);

		rc = fsi_spi_sequence_transfer(ctx, &seq, transfer);
		अगर (rc)
			जाओ error;

		अगर (!list_is_last(&transfer->transfer_list,
				  &mesg->transfers)) अणु
			next = list_next_entry(transfer, transfer_list);

			/* Sequencer can only करो shअगरt in (rx) after tx. */
			अगर (next->rx_buf) अणु
				अगर (next->len > ctx->max_xfr_size) अणु
					rc = -EINVAL;
					जाओ error;
				पूर्ण

				dev_dbg(ctx->dev, "Sequence rx of %d bytes.\n",
					next->len);

				rc = fsi_spi_sequence_transfer(ctx, &seq,
							       next);
				अगर (rc)
					जाओ error;
			पूर्ण अन्यथा अणु
				next = शून्य;
			पूर्ण
		पूर्ण

		fsi_spi_sequence_add(&seq, SPI_FSI_SEQUENCE_SEL_SLAVE(0));

		rc = fsi_spi_ग_लिखो_reg(ctx, SPI_FSI_SEQUENCE, seq.data);
		अगर (rc)
			जाओ error;

		rc = fsi_spi_transfer_data(ctx, transfer);
		अगर (rc)
			जाओ error;

		अगर (next) अणु
			rc = fsi_spi_transfer_data(ctx, next);
			अगर (rc)
				जाओ error;

			transfer = next;
		पूर्ण
	पूर्ण

error:
	mesg->status = rc;
	spi_finalize_current_message(ctlr);

	वापस rc;
पूर्ण

अटल माप_प्रकार fsi_spi_max_transfer_size(काष्ठा spi_device *spi)
अणु
	काष्ठा fsi_spi *ctx = spi_controller_get_devdata(spi->controller);

	वापस ctx->max_xfr_size;
पूर्ण

अटल पूर्णांक fsi_spi_probe(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा device_node *np;
	पूर्णांक num_controllers_रेजिस्टरed = 0;
	काष्ठा fsi_device *fsi = to_fsi_dev(dev);

	rc = fsi_spi_check_mux(fsi, dev);
	अगर (rc)
		वापस -ENODEV;

	क्रम_each_available_child_of_node(dev->of_node, np) अणु
		u32 base;
		काष्ठा fsi_spi *ctx;
		काष्ठा spi_controller *ctlr;

		अगर (of_property_पढ़ो_u32(np, "reg", &base))
			जारी;

		ctlr = spi_alloc_master(dev, माप(*ctx));
		अगर (!ctlr) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण

		ctlr->dev.of_node = np;
		ctlr->num_chipselect = of_get_available_child_count(np) ?: 1;
		ctlr->flags = SPI_CONTROLLER_HALF_DUPLEX;
		ctlr->max_transfer_size = fsi_spi_max_transfer_size;
		ctlr->transfer_one_message = fsi_spi_transfer_one_message;

		ctx = spi_controller_get_devdata(ctlr);
		ctx->dev = &ctlr->dev;
		ctx->fsi = fsi;
		ctx->base = base + SPI_FSI_BASE;

		अगर (of_device_is_compatible(np, "ibm,fsi2spi-restricted")) अणु
			ctx->restricted = true;
			ctx->max_xfr_size = SPI_FSI_MAX_XFR_SIZE_RESTRICTED;
		पूर्ण अन्यथा अणु
			ctx->restricted = false;
			ctx->max_xfr_size = SPI_FSI_MAX_XFR_SIZE;
		पूर्ण

		rc = devm_spi_रेजिस्टर_controller(dev, ctlr);
		अगर (rc)
			spi_controller_put(ctlr);
		अन्यथा
			num_controllers_रेजिस्टरed++;
	पूर्ण

	अगर (!num_controllers_रेजिस्टरed)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsi_device_id fsi_spi_ids[] = अणु
	अणु FSI_ENGID_SPI, FSI_VERSION_ANY पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(fsi, fsi_spi_ids);

अटल काष्ठा fsi_driver fsi_spi_driver = अणु
	.id_table = fsi_spi_ids,
	.drv = अणु
		.name = "spi-fsi",
		.bus = &fsi_bus_type,
		.probe = fsi_spi_probe,
	पूर्ण,
पूर्ण;
module_fsi_driver(fsi_spi_driver);

MODULE_AUTHOR("Eddie James <eajames@linux.ibm.com>");
MODULE_DESCRIPTION("FSI attached SPI controller");
MODULE_LICENSE("GPL");
