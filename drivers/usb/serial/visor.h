<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * USB HandSpring Visor driver
 *
 *	Copyright (C) 1999 - 2003
 *	    Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver.
 *
 */

#अगर_अघोषित __LINUX_USB_SERIAL_VISOR_H
#घोषणा __LINUX_USB_SERIAL_VISOR_H


#घोषणा HANDSPRING_VENDOR_ID		0x082d
#घोषणा HANDSPRING_VISOR_ID		0x0100
#घोषणा HANDSPRING_TREO_ID		0x0200
#घोषणा HANDSPRING_TREO600_ID		0x0300

#घोषणा PALM_VENDOR_ID			0x0830
#घोषणा PALM_M500_ID			0x0001
#घोषणा PALM_M505_ID			0x0002
#घोषणा PALM_M515_ID			0x0003
#घोषणा PALM_I705_ID			0x0020
#घोषणा PALM_M125_ID			0x0040
#घोषणा PALM_M130_ID			0x0050
#घोषणा PALM_TUNGSTEN_T_ID		0x0060
#घोषणा PALM_TREO_650			0x0061
#घोषणा PALM_TUNGSTEN_Z_ID		0x0031
#घोषणा PALM_ZIRE_ID			0x0070
#घोषणा PALM_M100_ID			0x0080

#घोषणा GSPDA_VENDOR_ID		0x115e
#घोषणा GSPDA_XPLORE_M68_ID		0xf100

#घोषणा SONY_VENDOR_ID			0x054C
#घोषणा SONY_CLIE_3_5_ID		0x0038
#घोषणा SONY_CLIE_4_0_ID		0x0066
#घोषणा SONY_CLIE_S360_ID		0x0095
#घोषणा SONY_CLIE_4_1_ID		0x009A
#घोषणा SONY_CLIE_NX60_ID		0x00DA
#घोषणा SONY_CLIE_NZ90V_ID		0x00E9
#घोषणा SONY_CLIE_UX50_ID		0x0144
#घोषणा SONY_CLIE_TJ25_ID		0x0169

#घोषणा ACER_VENDOR_ID			0x0502
#घोषणा ACER_S10_ID			0x0001

#घोषणा SAMSUNG_VENDOR_ID		0x04E8
#घोषणा SAMSUNG_SCH_I330_ID		0x8001
#घोषणा SAMSUNG_SPH_I500_ID		0x6601

#घोषणा TAPWAVE_VENDOR_ID		0x12EF
#घोषणा TAPWAVE_ZODIAC_ID		0x0100

#घोषणा GARMIN_VENDOR_ID		0x091E
#घोषणा GARMIN_IQUE_3600_ID		0x0004

#घोषणा ACEECA_VENDOR_ID		0x4766
#घोषणा ACEECA_MEZ1000_ID		0x0001

#घोषणा KYOCERA_VENDOR_ID		0x0C88
#घोषणा KYOCERA_7135_ID			0x0021

#घोषणा FOSSIL_VENDOR_ID		0x0E67
#घोषणा FOSSIL_ABACUS_ID		0x0002

/****************************************************************************
 * Handspring Visor Venकरोr specअगरic request codes (bRequest values)
 * A big thank you to Handspring क्रम providing the following inक्रमmation.
 * If anyone wants the original file where these values and काष्ठाures came
 * from, send email to <greg@kroah.com>.
 ****************************************************************************/

/****************************************************************************
 * VISOR_REQUEST_BYTES_AVAILABLE asks the visor क्रम the number of bytes that
 * are available to be transferred to the host क्रम the specअगरied endpoपूर्णांक.
 * Currently this is not used, and always वापसs 0x0001
 ****************************************************************************/
#घोषणा VISOR_REQUEST_BYTES_AVAILABLE		0x01

/****************************************************************************
 * VISOR_CLOSE_NOTIFICATION is set to the device to notअगरy it that the host
 * is now closing the pipe. An empty packet is sent in response.
 ****************************************************************************/
#घोषणा VISOR_CLOSE_NOTIFICATION		0x02

/****************************************************************************
 * VISOR_GET_CONNECTION_INFORMATION is sent by the host during क्रमागतeration to
 * get the endpoपूर्णांकs used by the connection.
 ****************************************************************************/
#घोषणा VISOR_GET_CONNECTION_INFORMATION	0x03


/****************************************************************************
 * VISOR_GET_CONNECTION_INFORMATION वापसs data in the following क्रमmat
 ****************************************************************************/
काष्ठा visor_connection_info अणु
	__le16	num_ports;
	काष्ठा अणु
		__u8	port_function_id;
		__u8	port;
	पूर्ण connections[2];
पूर्ण;


/* काष्ठा visor_connection_info.connection[x].port defines: */
#घोषणा VISOR_ENDPOINT_1		0x01
#घोषणा VISOR_ENDPOINT_2		0x02

/* काष्ठा visor_connection_info.connection[x].port_function_id defines: */
#घोषणा VISOR_FUNCTION_GENERIC		0x00
#घोषणा VISOR_FUNCTION_DEBUGGER		0x01
#घोषणा VISOR_FUNCTION_HOTSYNC		0x02
#घोषणा VISOR_FUNCTION_CONSOLE		0x03
#घोषणा VISOR_FUNCTION_REMOTE_खाता_SYS	0x04


/****************************************************************************
 * PALM_GET_SOME_UNKNOWN_INFORMATION is sent by the host during क्रमागतeration to
 * get some inक्रमmation from the M series devices, that is currently unknown.
 ****************************************************************************/
#घोषणा PALM_GET_EXT_CONNECTION_INFORMATION	0x04

/**
 * काष्ठा palm_ext_connection_info - वापस data from a PALM_GET_EXT_CONNECTION_INFORMATION request
 * @num_ports: maximum number of functions/connections in use
 * @endpoपूर्णांक_numbers_dअगरferent: will be 1 अगर in and out endpoपूर्णांकs numbers are
 *	dअगरferent, otherwise it is 0.  If value is 1, then
 *	connections.end_poपूर्णांक_info is non-zero.  If value is 0, then
 *	connections.port contains the endpoपूर्णांक number, which is the same क्रम in
 *	and out.
 * @port_function_id: contains the creator id of the application that खोलोed
 *	this connection.
 * @port: contains the in/out endpoपूर्णांक number.  Is 0 अगर in and out endpoपूर्णांक
 *	numbers are dअगरferent.
 * @end_poपूर्णांक_info: high nubbe is in endpoपूर्णांक and low nibble will indicate out
 *	endpoपूर्णांक.  Is 0 अगर in and out endpoपूर्णांकs are the same.
 *
 * The maximum number of connections currently supported is 2
 */
काष्ठा palm_ext_connection_info अणु
	__u8 num_ports;
	__u8 endpoपूर्णांक_numbers_dअगरferent;
	__le16 reserved1;
	काष्ठा अणु
		__u32 port_function_id;
		__u8 port;
		__u8 end_poपूर्णांक_info;
		__le16 reserved;
	पूर्ण connections[2];
पूर्ण;

#पूर्ण_अगर

