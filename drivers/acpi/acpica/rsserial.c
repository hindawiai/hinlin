<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsserial - GPIO/serial_bus resource descriptors
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsserial")

/*******************************************************************************
 *
 * acpi_rs_convert_gpio
 *
 ******************************************************************************/
काष्ठा acpi_rsconvert_info acpi_rs_convert_gpio[18] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_GPIO,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_gpio),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_gpio)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_GPIO,
	 माप(काष्ठा aml_resource_gpio),
	 0पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * revision_id
	 * connection_type
	 */
	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.gpio.revision_id),
	 AML_OFFSET(gpio.revision_id),
	 2पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.gpio.producer_consumer),
	 AML_OFFSET(gpio.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.gpio.shareable),
	 AML_OFFSET(gpio.पूर्णांक_flags),
	 3पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.gpio.wake_capable),
	 AML_OFFSET(gpio.पूर्णांक_flags),
	 4पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.gpio.io_restriction),
	 AML_OFFSET(gpio.पूर्णांक_flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.gpio.triggering),
	 AML_OFFSET(gpio.पूर्णांक_flags),
	 0पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.gpio.polarity),
	 AML_OFFSET(gpio.पूर्णांक_flags),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.gpio.pin_config),
	 AML_OFFSET(gpio.pin_config),
	 1पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * drive_strength
	 * debounce_समयout
	 */
	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.gpio.drive_strength),
	 AML_OFFSET(gpio.drive_strength),
	 2पूर्ण,

	/* Pin Table */

	अणुACPI_RSC_COUNT_GPIO_PIN, ACPI_RS_OFFSET(data.gpio.pin_table_length),
	 AML_OFFSET(gpio.pin_table_offset),
	 AML_OFFSET(gpio.res_source_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_PIN, ACPI_RS_OFFSET(data.gpio.pin_table),
	 AML_OFFSET(gpio.pin_table_offset),
	 0पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.gpio.resource_source.index),
	 AML_OFFSET(gpio.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.gpio.resource_source.string_length),
	 AML_OFFSET(gpio.res_source_offset),
	 AML_OFFSET(gpio.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.gpio.resource_source.string_ptr),
	 AML_OFFSET(gpio.res_source_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN, ACPI_RS_OFFSET(data.gpio.venकरोr_length),
	 AML_OFFSET(gpio.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES, ACPI_RS_OFFSET(data.gpio.venकरोr_data),
	 AML_OFFSET(gpio.venकरोr_offset),
	 0पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_pinfunction
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_function[13] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_PIN_FUNCTION,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_pin_function),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_pin_function)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_PIN_FUNCTION,
	 माप(काष्ठा aml_resource_pin_function),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_function.revision_id),
	 AML_OFFSET(pin_function.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_function.shareable),
	 AML_OFFSET(pin_function.flags),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_function.pin_config),
	 AML_OFFSET(pin_function.pin_config),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.pin_function.function_number),
	 AML_OFFSET(pin_function.function_number),
	 2पूर्ण,

	/* Pin Table */

	/*
	 * It is OK to use GPIO operations here because none of them refer GPIO
	 * काष्ठाures directly but instead use offsets given here.
	 */

	अणुACPI_RSC_COUNT_GPIO_PIN,
	 ACPI_RS_OFFSET(data.pin_function.pin_table_length),
	 AML_OFFSET(pin_function.pin_table_offset),
	 AML_OFFSET(pin_function.res_source_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_PIN, ACPI_RS_OFFSET(data.pin_function.pin_table),
	 AML_OFFSET(pin_function.pin_table_offset),
	 0पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.pin_function.resource_source.index),
	 AML_OFFSET(pin_function.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_function.resource_source.string_length),
	 AML_OFFSET(pin_function.res_source_offset),
	 AML_OFFSET(pin_function.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_function.resource_source.string_ptr),
	 AML_OFFSET(pin_function.res_source_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN,
	 ACPI_RS_OFFSET(data.pin_function.venकरोr_length),
	 AML_OFFSET(pin_function.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES, ACPI_RS_OFFSET(data.pin_function.venकरोr_data),
	 AML_OFFSET(pin_function.venकरोr_offset),
	 0पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_csi2_serial_bus
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_csi2_serial_bus[14] = अणु
	अणु ACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_SERIAL_BUS,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_csi2_serialbus),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_csi2_serial_bus) पूर्ण,

	अणु ACPI_RSC_INITSET, ACPI_RESOURCE_NAME_SERIAL_BUS,
	 माप(काष्ठा aml_resource_csi2_serialbus),
	 0 पूर्ण,

	अणु ACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.revision_id),
	 AML_OFFSET(common_serial_bus.revision_id),
	 1 पूर्ण,

	अणु ACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.csi2_serial_bus.type),
	 AML_OFFSET(csi2_serial_bus.type),
	 1 पूर्ण,

	अणु ACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.producer_consumer),
	 AML_OFFSET(csi2_serial_bus.flags),
	 1 पूर्ण,

	अणु ACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.csi2_serial_bus.slave_mode),
	 AML_OFFSET(csi2_serial_bus.flags),
	 0 पूर्ण,

	अणु ACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.csi2_serial_bus.phy_type),
	 AML_OFFSET(csi2_serial_bus.type_specअगरic_flags),
	 0 पूर्ण,

	अणु ACPI_RSC_6BITFLAG,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.local_port_instance),
	 AML_OFFSET(csi2_serial_bus.type_specअगरic_flags),
	 2 पूर्ण,

	अणु ACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.csi2_serial_bus.type_revision_id),
	 AML_OFFSET(csi2_serial_bus.type_revision_id),
	 1 पूर्ण,

	/* Venकरोr data */

	अणु ACPI_RSC_COUNT_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.venकरोr_length),
	 AML_OFFSET(csi2_serial_bus.type_data_length),
	 AML_RESOURCE_CSI2_MIN_DATA_LEN पूर्ण,

	अणु ACPI_RSC_MOVE_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.venकरोr_data),
	 0,
	 माप(काष्ठा aml_resource_csi2_serialbus) पूर्ण,

	/* Resource Source */

	अणु ACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.resource_source.index),
	 AML_OFFSET(csi2_serial_bus.res_source_index),
	 1 पूर्ण,

	अणु ACPI_RSC_COUNT_SERIAL_RES,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.resource_source.string_length),
	 AML_OFFSET(csi2_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_csi2_serialbus) पूर्ण,

	अणु ACPI_RSC_MOVE_SERIAL_RES,
	 ACPI_RS_OFFSET(data.csi2_serial_bus.resource_source.string_ptr),
	 AML_OFFSET(csi2_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_csi2_serialbus) पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_i2c_serial_bus
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_i2c_serial_bus[17] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_SERIAL_BUS,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_i2c_serialbus),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_i2c_serial_bus)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_SERIAL_BUS,
	 माप(काष्ठा aml_resource_i2c_serialbus),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.revision_id),
	 AML_OFFSET(common_serial_bus.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.type),
	 AML_OFFSET(common_serial_bus.type),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.common_serial_bus.slave_mode),
	 AML_OFFSET(common_serial_bus.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.producer_consumer),
	 AML_OFFSET(common_serial_bus.flags),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.connection_sharing),
	 AML_OFFSET(common_serial_bus.flags),
	 2पूर्ण,

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_revision_id),
	 AML_OFFSET(common_serial_bus.type_revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_data_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 1पूर्ण,

	/* Venकरोr data */

	अणुACPI_RSC_COUNT_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 AML_RESOURCE_I2C_MIN_DATA_LENपूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_data),
	 0,
	 माप(काष्ठा aml_resource_i2c_serialbus)पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.index),
	 AML_OFFSET(common_serial_bus.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_ptr),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	/* I2C bus type specअगरic */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.i2c_serial_bus.access_mode),
	 AML_OFFSET(i2c_serial_bus.type_specअगरic_flags),
	 0पूर्ण,

	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.i2c_serial_bus.connection_speed),
	 AML_OFFSET(i2c_serial_bus.connection_speed),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.i2c_serial_bus.slave_address),
	 AML_OFFSET(i2c_serial_bus.slave_address),
	 1पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_spi_serial_bus
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_spi_serial_bus[21] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_SERIAL_BUS,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_spi_serialbus),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_spi_serial_bus)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_SERIAL_BUS,
	 माप(काष्ठा aml_resource_spi_serialbus),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.revision_id),
	 AML_OFFSET(common_serial_bus.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.type),
	 AML_OFFSET(common_serial_bus.type),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.common_serial_bus.slave_mode),
	 AML_OFFSET(common_serial_bus.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.producer_consumer),
	 AML_OFFSET(common_serial_bus.flags),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.connection_sharing),
	 AML_OFFSET(common_serial_bus.flags),
	 2पूर्ण,

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_revision_id),
	 AML_OFFSET(common_serial_bus.type_revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_data_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 1पूर्ण,

	/* Venकरोr data */

	अणुACPI_RSC_COUNT_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 AML_RESOURCE_SPI_MIN_DATA_LENपूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_data),
	 0,
	 माप(काष्ठा aml_resource_spi_serialbus)पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.index),
	 AML_OFFSET(common_serial_bus.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_ptr),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	/* Spi bus type specअगरic  */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.spi_serial_bus.wire_mode),
	 AML_OFFSET(spi_serial_bus.type_specअगरic_flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.spi_serial_bus.device_polarity),
	 AML_OFFSET(spi_serial_bus.type_specअगरic_flags),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.spi_serial_bus.data_bit_length),
	 AML_OFFSET(spi_serial_bus.data_bit_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.spi_serial_bus.घड़ी_phase),
	 AML_OFFSET(spi_serial_bus.घड़ी_phase),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.spi_serial_bus.घड़ी_polarity),
	 AML_OFFSET(spi_serial_bus.घड़ी_polarity),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.spi_serial_bus.device_selection),
	 AML_OFFSET(spi_serial_bus.device_selection),
	 1पूर्ण,

	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.spi_serial_bus.connection_speed),
	 AML_OFFSET(spi_serial_bus.connection_speed),
	 1पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_uart_serial_bus
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_uart_serial_bus[23] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_SERIAL_BUS,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_uart_serialbus),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_uart_serial_bus)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_SERIAL_BUS,
	 माप(काष्ठा aml_resource_uart_serialbus),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.revision_id),
	 AML_OFFSET(common_serial_bus.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.common_serial_bus.type),
	 AML_OFFSET(common_serial_bus.type),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.common_serial_bus.slave_mode),
	 AML_OFFSET(common_serial_bus.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.producer_consumer),
	 AML_OFFSET(common_serial_bus.flags),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.common_serial_bus.connection_sharing),
	 AML_OFFSET(common_serial_bus.flags),
	 2पूर्ण,

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_revision_id),
	 AML_OFFSET(common_serial_bus.type_revision_id),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16,
	 ACPI_RS_OFFSET(data.common_serial_bus.type_data_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 1पूर्ण,

	/* Venकरोr data */

	अणुACPI_RSC_COUNT_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 AML_RESOURCE_UART_MIN_DATA_LENपूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_VEN,
	 ACPI_RS_OFFSET(data.common_serial_bus.venकरोr_data),
	 0,
	 माप(काष्ठा aml_resource_uart_serialbus)पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.index),
	 AML_OFFSET(common_serial_bus.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_length),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	अणुACPI_RSC_MOVE_SERIAL_RES,
	 ACPI_RS_OFFSET(data.common_serial_bus.resource_source.string_ptr),
	 AML_OFFSET(common_serial_bus.type_data_length),
	 माप(काष्ठा aml_resource_common_serialbus)पूर्ण,

	/* Uart bus type specअगरic  */

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.uart_serial_bus.flow_control),
	 AML_OFFSET(uart_serial_bus.type_specअगरic_flags),
	 0पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.uart_serial_bus.stop_bits),
	 AML_OFFSET(uart_serial_bus.type_specअगरic_flags),
	 2पूर्ण,

	अणुACPI_RSC_3BITFLAG, ACPI_RS_OFFSET(data.uart_serial_bus.data_bits),
	 AML_OFFSET(uart_serial_bus.type_specअगरic_flags),
	 4पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.uart_serial_bus.endian),
	 AML_OFFSET(uart_serial_bus.type_specअगरic_flags),
	 7पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.uart_serial_bus.parity),
	 AML_OFFSET(uart_serial_bus.parity),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.uart_serial_bus.lines_enabled),
	 AML_OFFSET(uart_serial_bus.lines_enabled),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.uart_serial_bus.rx_fअगरo_size),
	 AML_OFFSET(uart_serial_bus.rx_fअगरo_size),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.uart_serial_bus.tx_fअगरo_size),
	 AML_OFFSET(uart_serial_bus.tx_fअगरo_size),
	 1पूर्ण,

	अणुACPI_RSC_MOVE32,
	 ACPI_RS_OFFSET(data.uart_serial_bus.शेष_baud_rate),
	 AML_OFFSET(uart_serial_bus.शेष_baud_rate),
	 1पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_pin_config
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_config[14] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_PIN_CONFIG,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_pin_config),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_pin_config)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_PIN_CONFIG,
	 माप(काष्ठा aml_resource_pin_config),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_config.revision_id),
	 AML_OFFSET(pin_config.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_config.shareable),
	 AML_OFFSET(pin_config.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_config.producer_consumer),
	 AML_OFFSET(pin_config.flags),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_config.pin_config_type),
	 AML_OFFSET(pin_config.pin_config_type),
	 1पूर्ण,

	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.pin_config.pin_config_value),
	 AML_OFFSET(pin_config.pin_config_value),
	 1पूर्ण,

	/* Pin Table */

	/*
	 * It is OK to use GPIO operations here because none of them refer GPIO
	 * काष्ठाures directly but instead use offsets given here.
	 */

	अणुACPI_RSC_COUNT_GPIO_PIN,
	 ACPI_RS_OFFSET(data.pin_config.pin_table_length),
	 AML_OFFSET(pin_config.pin_table_offset),
	 AML_OFFSET(pin_config.res_source_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_PIN, ACPI_RS_OFFSET(data.pin_config.pin_table),
	 AML_OFFSET(pin_config.pin_table_offset),
	 0पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_config.resource_source.index),
	 AML_OFFSET(pin_config.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_config.resource_source.string_length),
	 AML_OFFSET(pin_config.res_source_offset),
	 AML_OFFSET(pin_config.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_config.resource_source.string_ptr),
	 AML_OFFSET(pin_config.res_source_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN, ACPI_RS_OFFSET(data.pin_config.venकरोr_length),
	 AML_OFFSET(pin_config.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES, ACPI_RS_OFFSET(data.pin_config.venकरोr_data),
	 AML_OFFSET(pin_config.venकरोr_offset),
	 0पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_pin_group
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group[10] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_PIN_GROUP,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_pin_group)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_PIN_GROUP,
	 माप(काष्ठा aml_resource_pin_group),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_group.revision_id),
	 AML_OFFSET(pin_group.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_group.producer_consumer),
	 AML_OFFSET(pin_group.flags),
	 0पूर्ण,

	/* Pin Table */

	/*
	 * It is OK to use GPIO operations here because none of them refer GPIO
	 * काष्ठाures directly but instead use offsets given here.
	 */

	अणुACPI_RSC_COUNT_GPIO_PIN,
	 ACPI_RS_OFFSET(data.pin_group.pin_table_length),
	 AML_OFFSET(pin_group.pin_table_offset),
	 AML_OFFSET(pin_group.label_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_PIN, ACPI_RS_OFFSET(data.pin_group.pin_table),
	 AML_OFFSET(pin_group.pin_table_offset),
	 0पूर्ण,

	/* Resource Label */

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group.resource_label.string_length),
	 AML_OFFSET(pin_group.label_offset),
	 AML_OFFSET(pin_group.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group.resource_label.string_ptr),
	 AML_OFFSET(pin_group.label_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN, ACPI_RS_OFFSET(data.pin_group.venकरोr_length),
	 AML_OFFSET(pin_group.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES, ACPI_RS_OFFSET(data.pin_group.venकरोr_data),
	 AML_OFFSET(pin_group.venकरोr_offset),
	 0पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_pin_group_function
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group_function[13] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group_function),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_pin_group_function)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION,
	 माप(काष्ठा aml_resource_pin_group_function),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_group_function.revision_id),
	 AML_OFFSET(pin_group_function.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_group_function.shareable),
	 AML_OFFSET(pin_group_function.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.pin_group_function.producer_consumer),
	 AML_OFFSET(pin_group_function.flags),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16,
	 ACPI_RS_OFFSET(data.pin_group_function.function_number),
	 AML_OFFSET(pin_group_function.function_number),
	 1पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.pin_group_function.resource_source.index),
	 AML_OFFSET(pin_group_function.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_function.resource_source.string_length),
	 AML_OFFSET(pin_group_function.res_source_offset),
	 AML_OFFSET(pin_group_function.res_source_label_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_function.resource_source.string_ptr),
	 AML_OFFSET(pin_group_function.res_source_offset),
	 0पूर्ण,

	/* Resource Source Label */

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_function.resource_source_label.
			string_length),
	 AML_OFFSET(pin_group_function.res_source_label_offset),
	 AML_OFFSET(pin_group_function.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_function.resource_source_label.
			string_ptr),
	 AML_OFFSET(pin_group_function.res_source_label_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN,
	 ACPI_RS_OFFSET(data.pin_group_function.venकरोr_length),
	 AML_OFFSET(pin_group_function.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_function.venकरोr_data),
	 AML_OFFSET(pin_group_function.venकरोr_offset),
	 0पूर्ण,
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_pin_group_config
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group_config[14] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group_config),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_pin_group_config)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG,
	 माप(काष्ठा aml_resource_pin_group_config),
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_group_config.revision_id),
	 AML_OFFSET(pin_group_config.revision_id),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.pin_group_config.shareable),
	 AML_OFFSET(pin_group_config.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.pin_group_config.producer_consumer),
	 AML_OFFSET(pin_group_config.flags),
	 1पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.pin_group_config.pin_config_type),
	 AML_OFFSET(pin_group_config.pin_config_type),
	 1पूर्ण,

	अणुACPI_RSC_MOVE32,
	 ACPI_RS_OFFSET(data.pin_group_config.pin_config_value),
	 AML_OFFSET(pin_group_config.pin_config_value),
	 1पूर्ण,

	/* Resource Source */

	अणुACPI_RSC_MOVE8,
	 ACPI_RS_OFFSET(data.pin_group_config.resource_source.index),
	 AML_OFFSET(pin_group_config.res_source_index),
	 1पूर्ण,

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_config.resource_source.string_length),
	 AML_OFFSET(pin_group_config.res_source_offset),
	 AML_OFFSET(pin_group_config.res_source_label_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_config.resource_source.string_ptr),
	 AML_OFFSET(pin_group_config.res_source_offset),
	 0पूर्ण,

	/* Resource Source Label */

	अणुACPI_RSC_COUNT_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_config.resource_source_label.
			string_length),
	 AML_OFFSET(pin_group_config.res_source_label_offset),
	 AML_OFFSET(pin_group_config.venकरोr_offset)पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_config.resource_source_label.string_ptr),
	 AML_OFFSET(pin_group_config.res_source_label_offset),
	 0पूर्ण,

	/* Venकरोr Data */

	अणुACPI_RSC_COUNT_GPIO_VEN,
	 ACPI_RS_OFFSET(data.pin_group_config.venकरोr_length),
	 AML_OFFSET(pin_group_config.venकरोr_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE_GPIO_RES,
	 ACPI_RS_OFFSET(data.pin_group_config.venकरोr_data),
	 AML_OFFSET(pin_group_config.venकरोr_offset),
	 0पूर्ण,
पूर्ण;
