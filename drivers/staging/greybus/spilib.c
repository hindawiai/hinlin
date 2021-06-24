<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus SPI library
 *
 * Copyright 2014-2016 Google Inc.
 * Copyright 2014-2016 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>
#समावेश <linux/spi/spi.h>

#समावेश "spilib.h"

काष्ठा gb_spilib अणु
	काष्ठा gb_connection	*connection;
	काष्ठा device		*parent;
	काष्ठा spi_transfer	*first_xfer;
	काष्ठा spi_transfer	*last_xfer;
	काष्ठा spilib_ops	*ops;
	u32			rx_xfer_offset;
	u32			tx_xfer_offset;
	u32			last_xfer_size;
	अचिन्हित पूर्णांक		op_समयout;
	u16			mode;
	u16			flags;
	u32			bits_per_word_mask;
	u8			num_chipselect;
	u32			min_speed_hz;
	u32			max_speed_hz;
पूर्ण;

#घोषणा GB_SPI_STATE_MSG_DONE		((व्योम *)0)
#घोषणा GB_SPI_STATE_MSG_IDLE		((व्योम *)1)
#घोषणा GB_SPI_STATE_MSG_RUNNING	((व्योम *)2)
#घोषणा GB_SPI_STATE_OP_READY		((व्योम *)3)
#घोषणा GB_SPI_STATE_OP_DONE		((व्योम *)4)
#घोषणा GB_SPI_STATE_MSG_ERROR		((व्योम *)-1)

#घोषणा XFER_TIMEOUT_TOLERANCE		200

अटल काष्ठा spi_master *get_master_from_spi(काष्ठा gb_spilib *spi)
अणु
	वापस gb_connection_get_data(spi->connection);
पूर्ण

अटल पूर्णांक tx_header_fit_operation(u32 tx_size, u32 count, माप_प्रकार data_max)
अणु
	माप_प्रकार headers_size;

	data_max -= माप(काष्ठा gb_spi_transfer_request);
	headers_size = (count + 1) * माप(काष्ठा gb_spi_transfer);

	वापस tx_size + headers_size > data_max ? 0 : 1;
पूर्ण

अटल माप_प्रकार calc_rx_xfer_size(u32 rx_size, u32 *tx_xfer_size, u32 len,
				माप_प्रकार data_max)
अणु
	माप_प्रकार rx_xfer_size;

	data_max -= माप(काष्ठा gb_spi_transfer_response);

	अगर (rx_size + len > data_max)
		rx_xfer_size = data_max - rx_size;
	अन्यथा
		rx_xfer_size = len;

	/* अगर this is a ग_लिखो_पढ़ो, क्रम symmetry पढ़ो the same as ग_लिखो */
	अगर (*tx_xfer_size && rx_xfer_size > *tx_xfer_size)
		rx_xfer_size = *tx_xfer_size;
	अगर (*tx_xfer_size && rx_xfer_size < *tx_xfer_size)
		*tx_xfer_size = rx_xfer_size;

	वापस rx_xfer_size;
पूर्ण

अटल माप_प्रकार calc_tx_xfer_size(u32 tx_size, u32 count, माप_प्रकार len,
				माप_प्रकार data_max)
अणु
	माप_प्रकार headers_size;

	data_max -= माप(काष्ठा gb_spi_transfer_request);
	headers_size = (count + 1) * माप(काष्ठा gb_spi_transfer);

	अगर (tx_size + headers_size + len > data_max)
		वापस data_max - (tx_size + माप(काष्ठा gb_spi_transfer));

	वापस len;
पूर्ण

अटल व्योम clean_xfer_state(काष्ठा gb_spilib *spi)
अणु
	spi->first_xfer = शून्य;
	spi->last_xfer = शून्य;
	spi->rx_xfer_offset = 0;
	spi->tx_xfer_offset = 0;
	spi->last_xfer_size = 0;
	spi->op_समयout = 0;
पूर्ण

अटल bool is_last_xfer_करोne(काष्ठा gb_spilib *spi)
अणु
	काष्ठा spi_transfer *last_xfer = spi->last_xfer;

	अगर ((spi->tx_xfer_offset + spi->last_xfer_size == last_xfer->len) ||
	    (spi->rx_xfer_offset + spi->last_xfer_size == last_xfer->len))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक setup_next_xfer(काष्ठा gb_spilib *spi, काष्ठा spi_message *msg)
अणु
	काष्ठा spi_transfer *last_xfer = spi->last_xfer;

	अगर (msg->state != GB_SPI_STATE_OP_DONE)
		वापस 0;

	/*
	 * अगर we transferred all content of the last transfer, reset values and
	 * check अगर this was the last transfer in the message
	 */
	अगर (is_last_xfer_करोne(spi)) अणु
		spi->tx_xfer_offset = 0;
		spi->rx_xfer_offset = 0;
		spi->op_समयout = 0;
		अगर (last_xfer == list_last_entry(&msg->transfers,
						 काष्ठा spi_transfer,
						 transfer_list))
			msg->state = GB_SPI_STATE_MSG_DONE;
		अन्यथा
			spi->first_xfer = list_next_entry(last_xfer,
							  transfer_list);
		वापस 0;
	पूर्ण

	spi->first_xfer = last_xfer;
	अगर (last_xfer->tx_buf)
		spi->tx_xfer_offset += spi->last_xfer_size;

	अगर (last_xfer->rx_buf)
		spi->rx_xfer_offset += spi->last_xfer_size;

	वापस 0;
पूर्ण

अटल काष्ठा spi_transfer *get_next_xfer(काष्ठा spi_transfer *xfer,
					  काष्ठा spi_message *msg)
अणु
	अगर (xfer == list_last_entry(&msg->transfers, काष्ठा spi_transfer,
				    transfer_list))
		वापस शून्य;

	वापस list_next_entry(xfer, transfer_list);
पूर्ण

/* Routines to transfer data */
अटल काष्ठा gb_operation *gb_spi_operation_create(काष्ठा gb_spilib *spi,
		काष्ठा gb_connection *connection, काष्ठा spi_message *msg)
अणु
	काष्ठा gb_spi_transfer_request *request;
	काष्ठा spi_device *dev = msg->spi;
	काष्ठा spi_transfer *xfer;
	काष्ठा gb_spi_transfer *gb_xfer;
	काष्ठा gb_operation *operation;
	u32 tx_size = 0, rx_size = 0, count = 0, xfer_len = 0, request_size;
	u32 tx_xfer_size = 0, rx_xfer_size = 0, len;
	u32 total_len = 0;
	अचिन्हित पूर्णांक xfer_समयout;
	माप_प्रकार data_max;
	व्योम *tx_data;

	data_max = gb_operation_get_payload_size_max(connection);
	xfer = spi->first_xfer;

	/* Find number of transfers queued and tx/rx length in the message */

	जबतक (msg->state != GB_SPI_STATE_OP_READY) अणु
		msg->state = GB_SPI_STATE_MSG_RUNNING;
		spi->last_xfer = xfer;

		अगर (!xfer->tx_buf && !xfer->rx_buf) अणु
			dev_err(spi->parent,
				"bufferless transfer, length %u\n", xfer->len);
			msg->state = GB_SPI_STATE_MSG_ERROR;
			वापस शून्य;
		पूर्ण

		tx_xfer_size = 0;
		rx_xfer_size = 0;

		अगर (xfer->tx_buf) अणु
			len = xfer->len - spi->tx_xfer_offset;
			अगर (!tx_header_fit_operation(tx_size, count, data_max))
				अवरोध;
			tx_xfer_size = calc_tx_xfer_size(tx_size, count,
							 len, data_max);
			spi->last_xfer_size = tx_xfer_size;
		पूर्ण

		अगर (xfer->rx_buf) अणु
			len = xfer->len - spi->rx_xfer_offset;
			rx_xfer_size = calc_rx_xfer_size(rx_size, &tx_xfer_size,
							 len, data_max);
			spi->last_xfer_size = rx_xfer_size;
		पूर्ण

		tx_size += tx_xfer_size;
		rx_size += rx_xfer_size;

		total_len += spi->last_xfer_size;
		count++;

		xfer = get_next_xfer(xfer, msg);
		अगर (!xfer || total_len >= data_max)
			msg->state = GB_SPI_STATE_OP_READY;
	पूर्ण

	/*
	 * In addition to space क्रम all message descriptors we need
	 * to have enough to hold all tx data.
	 */
	request_size = माप(*request);
	request_size += count * माप(*gb_xfer);
	request_size += tx_size;

	/* Response consists only of incoming data */
	operation = gb_operation_create(connection, GB_SPI_TYPE_TRANSFER,
					request_size, rx_size, GFP_KERNEL);
	अगर (!operation)
		वापस शून्य;

	request = operation->request->payload;
	request->count = cpu_to_le16(count);
	request->mode = dev->mode;
	request->chip_select = dev->chip_select;

	gb_xfer = &request->transfers[0];
	tx_data = gb_xfer + count;	/* place tx data after last gb_xfer */

	/* Fill in the transfers array */
	xfer = spi->first_xfer;
	जबतक (msg->state != GB_SPI_STATE_OP_DONE) अणु
		पूर्णांक xfer_delay;
		अगर (xfer == spi->last_xfer)
			xfer_len = spi->last_xfer_size;
		अन्यथा
			xfer_len = xfer->len;

		/* make sure we करो not समयout in a slow transfer */
		xfer_समयout = xfer_len * 8 * MSEC_PER_SEC / xfer->speed_hz;
		xfer_समयout += GB_OPERATION_TIMEOUT_DEFAULT;

		अगर (xfer_समयout > spi->op_समयout)
			spi->op_समयout = xfer_समयout;

		gb_xfer->speed_hz = cpu_to_le32(xfer->speed_hz);
		gb_xfer->len = cpu_to_le32(xfer_len);
		xfer_delay = spi_delay_to_ns(&xfer->delay, xfer) / 1000;
		xfer_delay = clamp_t(u16, xfer_delay, 0, U16_MAX);
		gb_xfer->delay_usecs = cpu_to_le16(xfer_delay);
		gb_xfer->cs_change = xfer->cs_change;
		gb_xfer->bits_per_word = xfer->bits_per_word;

		/* Copy tx data */
		अगर (xfer->tx_buf) अणु
			gb_xfer->xfer_flags |= GB_SPI_XFER_WRITE;
			स_नकल(tx_data, xfer->tx_buf + spi->tx_xfer_offset,
			       xfer_len);
			tx_data += xfer_len;
		पूर्ण

		अगर (xfer->rx_buf)
			gb_xfer->xfer_flags |= GB_SPI_XFER_READ;

		अगर (xfer == spi->last_xfer) अणु
			अगर (!is_last_xfer_करोne(spi))
				gb_xfer->xfer_flags |= GB_SPI_XFER_INPROGRESS;
			msg->state = GB_SPI_STATE_OP_DONE;
			जारी;
		पूर्ण

		gb_xfer++;
		xfer = get_next_xfer(xfer, msg);
	पूर्ण

	msg->actual_length += total_len;

	वापस operation;
पूर्ण

अटल व्योम gb_spi_decode_response(काष्ठा gb_spilib *spi,
				   काष्ठा spi_message *msg,
				   काष्ठा gb_spi_transfer_response *response)
अणु
	काष्ठा spi_transfer *xfer = spi->first_xfer;
	व्योम *rx_data = response->data;
	u32 xfer_len;

	जबतक (xfer) अणु
		/* Copy rx data */
		अगर (xfer->rx_buf) अणु
			अगर (xfer == spi->first_xfer)
				xfer_len = xfer->len - spi->rx_xfer_offset;
			अन्यथा अगर (xfer == spi->last_xfer)
				xfer_len = spi->last_xfer_size;
			अन्यथा
				xfer_len = xfer->len;

			स_नकल(xfer->rx_buf + spi->rx_xfer_offset, rx_data,
			       xfer_len);
			rx_data += xfer_len;
		पूर्ण

		अगर (xfer == spi->last_xfer)
			अवरोध;

		xfer = list_next_entry(xfer, transfer_list);
	पूर्ण
पूर्ण

अटल पूर्णांक gb_spi_transfer_one_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *msg)
अणु
	काष्ठा gb_spilib *spi = spi_master_get_devdata(master);
	काष्ठा gb_connection *connection = spi->connection;
	काष्ठा gb_spi_transfer_response *response;
	काष्ठा gb_operation *operation;
	पूर्णांक ret = 0;

	spi->first_xfer = list_first_entry_or_null(&msg->transfers,
						   काष्ठा spi_transfer,
						   transfer_list);
	अगर (!spi->first_xfer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	msg->state = GB_SPI_STATE_MSG_IDLE;

	जबतक (msg->state != GB_SPI_STATE_MSG_DONE &&
	       msg->state != GB_SPI_STATE_MSG_ERROR) अणु
		operation = gb_spi_operation_create(spi, connection, msg);
		अगर (!operation) अणु
			msg->state = GB_SPI_STATE_MSG_ERROR;
			ret = -EINVAL;
			जारी;
		पूर्ण

		ret = gb_operation_request_send_sync_समयout(operation,
							     spi->op_समयout);
		अगर (!ret) अणु
			response = operation->response->payload;
			अगर (response)
				gb_spi_decode_response(spi, msg, response);
		पूर्ण अन्यथा अणु
			dev_err(spi->parent,
				"transfer operation failed: %d\n", ret);
			msg->state = GB_SPI_STATE_MSG_ERROR;
		पूर्ण

		gb_operation_put(operation);
		setup_next_xfer(spi, msg);
	पूर्ण

out:
	msg->status = ret;
	clean_xfer_state(spi);
	spi_finalize_current_message(master);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_spi_prepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा gb_spilib *spi = spi_master_get_devdata(master);

	वापस spi->ops->prepare_transfer_hardware(spi->parent);
पूर्ण

अटल पूर्णांक gb_spi_unprepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा gb_spilib *spi = spi_master_get_devdata(master);

	spi->ops->unprepare_transfer_hardware(spi->parent);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_spi_setup(काष्ठा spi_device *spi)
अणु
	/* Nothing to करो क्रम now */
	वापस 0;
पूर्ण

अटल व्योम gb_spi_cleanup(काष्ठा spi_device *spi)
अणु
	/* Nothing to करो क्रम now */
पूर्ण

/* Routines to get controller inक्रमmation */

/*
 * Map Greybus spi mode bits/flags/bpw पूर्णांकo Linux ones.
 * All bits are same क्रम now and so these macro's वापस same values.
 */
#घोषणा gb_spi_mode_map(mode) mode
#घोषणा gb_spi_flags_map(flags) flags

अटल पूर्णांक gb_spi_get_master_config(काष्ठा gb_spilib *spi)
अणु
	काष्ठा gb_spi_master_config_response response;
	u16 mode, flags;
	पूर्णांक ret;

	ret = gb_operation_sync(spi->connection, GB_SPI_TYPE_MASTER_CONFIG,
				शून्य, 0, &response, माप(response));
	अगर (ret < 0)
		वापस ret;

	mode = le16_to_cpu(response.mode);
	spi->mode = gb_spi_mode_map(mode);

	flags = le16_to_cpu(response.flags);
	spi->flags = gb_spi_flags_map(flags);

	spi->bits_per_word_mask = le32_to_cpu(response.bits_per_word_mask);
	spi->num_chipselect = response.num_chipselect;

	spi->min_speed_hz = le32_to_cpu(response.min_speed_hz);
	spi->max_speed_hz = le32_to_cpu(response.max_speed_hz);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_spi_setup_device(काष्ठा gb_spilib *spi, u8 cs)
अणु
	काष्ठा spi_master *master = get_master_from_spi(spi);
	काष्ठा gb_spi_device_config_request request;
	काष्ठा gb_spi_device_config_response response;
	काष्ठा spi_board_info spi_board = अणु अणु0पूर्ण पूर्ण;
	काष्ठा spi_device *spidev;
	पूर्णांक ret;
	u8 dev_type;

	request.chip_select = cs;

	ret = gb_operation_sync(spi->connection, GB_SPI_TYPE_DEVICE_CONFIG,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0)
		वापस ret;

	dev_type = response.device_type;

	अगर (dev_type == GB_SPI_SPI_DEV)
		strscpy(spi_board.modalias, "spidev",
			माप(spi_board.modalias));
	अन्यथा अगर (dev_type == GB_SPI_SPI_NOR)
		strscpy(spi_board.modalias, "spi-nor",
			माप(spi_board.modalias));
	अन्यथा अगर (dev_type == GB_SPI_SPI_MODALIAS)
		स_नकल(spi_board.modalias, response.name,
		       माप(spi_board.modalias));
	अन्यथा
		वापस -EINVAL;

	spi_board.mode		= le16_to_cpu(response.mode);
	spi_board.bus_num	= master->bus_num;
	spi_board.chip_select	= cs;
	spi_board.max_speed_hz	= le32_to_cpu(response.max_speed_hz);

	spidev = spi_new_device(master, &spi_board);
	अगर (!spidev)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक gb_spilib_master_init(काष्ठा gb_connection *connection, काष्ठा device *dev,
			  काष्ठा spilib_ops *ops)
अणु
	काष्ठा gb_spilib *spi;
	काष्ठा spi_master *master;
	पूर्णांक ret;
	u8 i;

	/* Allocate master with space क्रम data */
	master = spi_alloc_master(dev, माप(*spi));
	अगर (!master) अणु
		dev_err(dev, "cannot alloc SPI master\n");
		वापस -ENOMEM;
	पूर्ण

	spi = spi_master_get_devdata(master);
	spi->connection = connection;
	gb_connection_set_data(connection, master);
	spi->parent = dev;
	spi->ops = ops;

	/* get master configuration */
	ret = gb_spi_get_master_config(spi);
	अगर (ret)
		जाओ निकास_spi_put;

	master->bus_num = -1; /* Allow spi-core to allocate it dynamically */
	master->num_chipselect = spi->num_chipselect;
	master->mode_bits = spi->mode;
	master->flags = spi->flags;
	master->bits_per_word_mask = spi->bits_per_word_mask;

	/* Attach methods */
	master->cleanup = gb_spi_cleanup;
	master->setup = gb_spi_setup;
	master->transfer_one_message = gb_spi_transfer_one_message;

	अगर (ops && ops->prepare_transfer_hardware) अणु
		master->prepare_transfer_hardware =
			gb_spi_prepare_transfer_hardware;
	पूर्ण

	अगर (ops && ops->unprepare_transfer_hardware) अणु
		master->unprepare_transfer_hardware =
			gb_spi_unprepare_transfer_hardware;
	पूर्ण

	master->स्वतः_runसमय_pm = true;

	ret = spi_रेजिस्टर_master(master);
	अगर (ret < 0)
		जाओ निकास_spi_put;

	/* now, fetch the devices configuration */
	क्रम (i = 0; i < spi->num_chipselect; i++) अणु
		ret = gb_spi_setup_device(spi, i);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to allocate spi device %d: %d\n",
				i, ret);
			जाओ निकास_spi_unरेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

निकास_spi_put:
	spi_master_put(master);

	वापस ret;

निकास_spi_unरेजिस्टर:
	spi_unरेजिस्टर_master(master);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_spilib_master_init);

व्योम gb_spilib_master_निकास(काष्ठा gb_connection *connection)
अणु
	काष्ठा spi_master *master = gb_connection_get_data(connection);

	spi_unरेजिस्टर_master(master);
पूर्ण
EXPORT_SYMBOL_GPL(gb_spilib_master_निकास);

MODULE_LICENSE("GPL v2");
