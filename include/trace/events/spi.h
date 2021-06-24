<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM spi

#अगर !defined(_TRACE_SPI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SPI_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(spi_controller,

	TP_PROTO(काष्ठा spi_controller *controller),

	TP_ARGS(controller),

	TP_STRUCT__entry(
		__field(        पूर्णांक,           bus_num             )
	),

	TP_fast_assign(
		__entry->bus_num = controller->bus_num;
	),

	TP_prपूर्णांकk("spi%d", (पूर्णांक)__entry->bus_num)

);

DEFINE_EVENT(spi_controller, spi_controller_idle,

	TP_PROTO(काष्ठा spi_controller *controller),

	TP_ARGS(controller)

);

DEFINE_EVENT(spi_controller, spi_controller_busy,

	TP_PROTO(काष्ठा spi_controller *controller),

	TP_ARGS(controller)

);

DECLARE_EVENT_CLASS(spi_message,

	TP_PROTO(काष्ठा spi_message *msg),

	TP_ARGS(msg),

	TP_STRUCT__entry(
		__field(        पूर्णांक,            bus_num         )
		__field(        पूर्णांक,            chip_select     )
		__field(        काष्ठा spi_message *,   msg     )
	),

	TP_fast_assign(
		__entry->bus_num = msg->spi->controller->bus_num;
		__entry->chip_select = msg->spi->chip_select;
		__entry->msg = msg;
	),

        TP_prपूर्णांकk("spi%d.%d %p", (पूर्णांक)__entry->bus_num,
		  (पूर्णांक)__entry->chip_select,
		  (काष्ठा spi_message *)__entry->msg)
);

DEFINE_EVENT(spi_message, spi_message_submit,

	TP_PROTO(काष्ठा spi_message *msg),

	TP_ARGS(msg)

);

DEFINE_EVENT(spi_message, spi_message_start,

	TP_PROTO(काष्ठा spi_message *msg),

	TP_ARGS(msg)

);

TRACE_EVENT(spi_message_करोne,

	TP_PROTO(काष्ठा spi_message *msg),

	TP_ARGS(msg),

	TP_STRUCT__entry(
		__field(        पूर्णांक,            bus_num         )
		__field(        पूर्णांक,            chip_select     )
		__field(        काष्ठा spi_message *,   msg     )
		__field(        अचिन्हित,       frame           )
		__field(        अचिन्हित,       actual          )
	),

	TP_fast_assign(
		__entry->bus_num = msg->spi->controller->bus_num;
		__entry->chip_select = msg->spi->chip_select;
		__entry->msg = msg;
		__entry->frame = msg->frame_length;
		__entry->actual = msg->actual_length;
	),

        TP_prपूर्णांकk("spi%d.%d %p len=%u/%u", (पूर्णांक)__entry->bus_num,
		  (पूर्णांक)__entry->chip_select,
		  (काष्ठा spi_message *)__entry->msg,
                  (अचिन्हित)__entry->actual, (अचिन्हित)__entry->frame)
);

/*
 * consider a buffer valid अगर non-शून्य and अगर it करोesn't match the dummy buffer
 * that only exist to work with controllers that have SPI_CONTROLLER_MUST_TX or
 * SPI_CONTROLLER_MUST_RX.
 */
#घोषणा spi_valid_txbuf(msg, xfer) \
	(xfer->tx_buf && xfer->tx_buf != msg->spi->controller->dummy_tx)
#घोषणा spi_valid_rxbuf(msg, xfer) \
	(xfer->rx_buf && xfer->rx_buf != msg->spi->controller->dummy_rx)

DECLARE_EVENT_CLASS(spi_transfer,

	TP_PROTO(काष्ठा spi_message *msg, काष्ठा spi_transfer *xfer),

	TP_ARGS(msg, xfer),

	TP_STRUCT__entry(
		__field(        पूर्णांक,            bus_num         )
		__field(        पूर्णांक,            chip_select     )
		__field(        काष्ठा spi_transfer *,   xfer   )
		__field(        पूर्णांक,            len             )
		__dynamic_array(u8, rx_buf,
				spi_valid_rxbuf(msg, xfer) ?
					(xfer->len < 64 ? xfer->len : 64) : 0)
		__dynamic_array(u8, tx_buf,
				spi_valid_txbuf(msg, xfer) ?
					(xfer->len < 64 ? xfer->len : 64) : 0)
	),

	TP_fast_assign(
		__entry->bus_num = msg->spi->controller->bus_num;
		__entry->chip_select = msg->spi->chip_select;
		__entry->xfer = xfer;
		__entry->len = xfer->len;

		अगर (spi_valid_txbuf(msg, xfer))
			स_नकल(__get_dynamic_array(tx_buf),
			       xfer->tx_buf, __get_dynamic_array_len(tx_buf));

		अगर (spi_valid_rxbuf(msg, xfer))
			स_नकल(__get_dynamic_array(rx_buf),
			       xfer->rx_buf, __get_dynamic_array_len(rx_buf));
	),

	TP_prपूर्णांकk("spi%d.%d %p len=%d tx=[%*phD] rx=[%*phD]",
		  __entry->bus_num, __entry->chip_select,
		  __entry->xfer, __entry->len,
		  __get_dynamic_array_len(tx_buf), __get_dynamic_array(tx_buf),
		  __get_dynamic_array_len(rx_buf), __get_dynamic_array(rx_buf))
);

DEFINE_EVENT(spi_transfer, spi_transfer_start,

	TP_PROTO(काष्ठा spi_message *msg, काष्ठा spi_transfer *xfer),

	TP_ARGS(msg, xfer)

);

DEFINE_EVENT(spi_transfer, spi_transfer_stop,

	TP_PROTO(काष्ठा spi_message *msg, काष्ठा spi_transfer *xfer),

	TP_ARGS(msg, xfer)

);

#पूर्ण_अगर /* _TRACE_POWER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
