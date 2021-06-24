<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा CREATE_TRACE_POINTS
#समावेश "ucsi.h"
#समावेश "trace.h"

अटल स्थिर अक्षर * स्थिर ucsi_cmd_strs[] = अणु
	[0]				= "Unknown command",
	[UCSI_PPM_RESET]		= "PPM_RESET",
	[UCSI_CANCEL]			= "CANCEL",
	[UCSI_CONNECTOR_RESET]		= "CONNECTOR_RESET",
	[UCSI_ACK_CC_CI]		= "ACK_CC_CI",
	[UCSI_SET_NOTIFICATION_ENABLE]	= "SET_NOTIFICATION_ENABLE",
	[UCSI_GET_CAPABILITY]		= "GET_CAPABILITY",
	[UCSI_GET_CONNECTOR_CAPABILITY]	= "GET_CONNECTOR_CAPABILITY",
	[UCSI_SET_UOM]			= "SET_UOM",
	[UCSI_SET_UOR]			= "SET_UOR",
	[UCSI_SET_PDM]			= "SET_PDM",
	[UCSI_SET_PDR]			= "SET_PDR",
	[UCSI_GET_ALTERNATE_MODES]	= "GET_ALTERNATE_MODES",
	[UCSI_GET_CAM_SUPPORTED]	= "GET_CAM_SUPPORTED",
	[UCSI_GET_CURRENT_CAM]		= "GET_CURRENT_CAM",
	[UCSI_SET_NEW_CAM]		= "SET_NEW_CAM",
	[UCSI_GET_PDOS]			= "GET_PDOS",
	[UCSI_GET_CABLE_PROPERTY]	= "GET_CABLE_PROPERTY",
	[UCSI_GET_CONNECTOR_STATUS]	= "GET_CONNECTOR_STATUS",
	[UCSI_GET_ERROR_STATUS]		= "GET_ERROR_STATUS",
पूर्ण;

स्थिर अक्षर *ucsi_cmd_str(u64 raw_cmd)
अणु
	u8 cmd = raw_cmd & GENMASK(7, 0);

	वापस ucsi_cmd_strs[(cmd >= ARRAY_SIZE(ucsi_cmd_strs)) ? 0 : cmd];
पूर्ण

स्थिर अक्षर *ucsi_cci_str(u32 cci)
अणु
	अगर (UCSI_CCI_CONNECTOR(cci)) अणु
		अगर (cci & UCSI_CCI_ACK_COMPLETE)
			वापस "Event pending (ACK completed)";
		अगर (cci & UCSI_CCI_COMMAND_COMPLETE)
			वापस "Event pending (command completed)";
		वापस "Connector Change";
	पूर्ण
	अगर (cci & UCSI_CCI_ACK_COMPLETE)
		वापस "ACK completed";
	अगर (cci & UCSI_CCI_COMMAND_COMPLETE)
		वापस "Command completed";

	वापस "";
पूर्ण

अटल स्थिर अक्षर * स्थिर ucsi_recipient_strs[] = अणु
	[UCSI_RECIPIENT_CON]		= "port",
	[UCSI_RECIPIENT_SOP]		= "partner",
	[UCSI_RECIPIENT_SOP_P]		= "plug (prime)",
	[UCSI_RECIPIENT_SOP_PP]		= "plug (double prime)",
पूर्ण;

स्थिर अक्षर *ucsi_recipient_str(u8 recipient)
अणु
	वापस ucsi_recipient_strs[recipient];
पूर्ण
