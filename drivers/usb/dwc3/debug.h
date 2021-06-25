<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * debug.h - DesignWare USB3 DRD Controller Debug Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#अगर_अघोषित __DWC3_DEBUG_H
#घोषणा __DWC3_DEBUG_H

#समावेश "core.h"

/**
 * dwc3_gadget_ep_cmd_string - वापसs endpoपूर्णांक command string
 * @cmd: command code
 */
अटल अंतरभूत स्थिर अक्षर *
dwc3_gadget_ep_cmd_string(u8 cmd)
अणु
	चयन (cmd) अणु
	हाल DWC3_DEPCMD_DEPSTARTCFG:
		वापस "Start New Configuration";
	हाल DWC3_DEPCMD_ENDTRANSFER:
		वापस "End Transfer";
	हाल DWC3_DEPCMD_UPDATETRANSFER:
		वापस "Update Transfer";
	हाल DWC3_DEPCMD_STARTTRANSFER:
		वापस "Start Transfer";
	हाल DWC3_DEPCMD_CLEARSTALL:
		वापस "Clear Stall";
	हाल DWC3_DEPCMD_SETSTALL:
		वापस "Set Stall";
	हाल DWC3_DEPCMD_GETEPSTATE:
		वापस "Get Endpoint State";
	हाल DWC3_DEPCMD_SETTRANSFRESOURCE:
		वापस "Set Endpoint Transfer Resource";
	हाल DWC3_DEPCMD_SETEPCONFIG:
		वापस "Set Endpoint Configuration";
	शेष:
		वापस "UNKNOWN command";
	पूर्ण
पूर्ण

/**
 * dwc3_gadget_generic_cmd_string - वापसs generic command string
 * @cmd: command code
 */
अटल अंतरभूत स्थिर अक्षर *
dwc3_gadget_generic_cmd_string(u8 cmd)
अणु
	चयन (cmd) अणु
	हाल DWC3_DGCMD_SET_LMP:
		वापस "Set LMP";
	हाल DWC3_DGCMD_SET_PERIODIC_PAR:
		वापस "Set Periodic Parameters";
	हाल DWC3_DGCMD_XMIT_FUNCTION:
		वापस "Transmit Function Wake Device Notification";
	हाल DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO:
		वापस "Set Scratchpad Buffer Array Address Lo";
	हाल DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI:
		वापस "Set Scratchpad Buffer Array Address Hi";
	हाल DWC3_DGCMD_SELECTED_FIFO_FLUSH:
		वापस "Selected FIFO Flush";
	हाल DWC3_DGCMD_ALL_FIFO_FLUSH:
		वापस "All FIFO Flush";
	हाल DWC3_DGCMD_SET_ENDPOINT_NRDY:
		वापस "Set Endpoint NRDY";
	हाल DWC3_DGCMD_SET_ENDPOINT_PRIME:
		वापस "Set Endpoint Prime";
	हाल DWC3_DGCMD_RUN_SOC_BUS_LOOPBACK:
		वापस "Run SoC Bus Loopback Test";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

/**
 * dwc3_gadget_link_string - वापसs link name
 * @link_state: link state code
 */
अटल अंतरभूत स्थिर अक्षर *
dwc3_gadget_link_string(क्रमागत dwc3_link_state link_state)
अणु
	चयन (link_state) अणु
	हाल DWC3_LINK_STATE_U0:
		वापस "U0";
	हाल DWC3_LINK_STATE_U1:
		वापस "U1";
	हाल DWC3_LINK_STATE_U2:
		वापस "U2";
	हाल DWC3_LINK_STATE_U3:
		वापस "U3";
	हाल DWC3_LINK_STATE_SS_DIS:
		वापस "SS.Disabled";
	हाल DWC3_LINK_STATE_RX_DET:
		वापस "RX.Detect";
	हाल DWC3_LINK_STATE_SS_INACT:
		वापस "SS.Inactive";
	हाल DWC3_LINK_STATE_POLL:
		वापस "Polling";
	हाल DWC3_LINK_STATE_RECOV:
		वापस "Recovery";
	हाल DWC3_LINK_STATE_HRESET:
		वापस "Hot Reset";
	हाल DWC3_LINK_STATE_CMPLY:
		वापस "Compliance";
	हाल DWC3_LINK_STATE_LPBK:
		वापस "Loopback";
	हाल DWC3_LINK_STATE_RESET:
		वापस "Reset";
	हाल DWC3_LINK_STATE_RESUME:
		वापस "Resume";
	शेष:
		वापस "UNKNOWN link state";
	पूर्ण
पूर्ण

/**
 * dwc3_gadget_hs_link_string - वापसs highspeed and below link name
 * @link_state: link state code
 */
अटल अंतरभूत स्थिर अक्षर *
dwc3_gadget_hs_link_string(क्रमागत dwc3_link_state link_state)
अणु
	चयन (link_state) अणु
	हाल DWC3_LINK_STATE_U0:
		वापस "On";
	हाल DWC3_LINK_STATE_U2:
		वापस "Sleep";
	हाल DWC3_LINK_STATE_U3:
		वापस "Suspend";
	हाल DWC3_LINK_STATE_SS_DIS:
		वापस "Disconnected";
	हाल DWC3_LINK_STATE_RX_DET:
		वापस "Early Suspend";
	हाल DWC3_LINK_STATE_RECOV:
		वापस "Recovery";
	हाल DWC3_LINK_STATE_RESET:
		वापस "Reset";
	हाल DWC3_LINK_STATE_RESUME:
		वापस "Resume";
	शेष:
		वापस "UNKNOWN link state";
	पूर्ण
पूर्ण

/**
 * dwc3_trb_type_string - वापसs TRB type as a string
 * @type: the type of the TRB
 */
अटल अंतरभूत स्थिर अक्षर *dwc3_trb_type_string(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल DWC3_TRBCTL_NORMAL:
		वापस "normal";
	हाल DWC3_TRBCTL_CONTROL_SETUP:
		वापस "setup";
	हाल DWC3_TRBCTL_CONTROL_STATUS2:
		वापस "status2";
	हाल DWC3_TRBCTL_CONTROL_STATUS3:
		वापस "status3";
	हाल DWC3_TRBCTL_CONTROL_DATA:
		वापस "data";
	हाल DWC3_TRBCTL_ISOCHRONOUS_FIRST:
		वापस "isoc-first";
	हाल DWC3_TRBCTL_ISOCHRONOUS:
		वापस "isoc";
	हाल DWC3_TRBCTL_LINK_TRB:
		वापस "link";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *dwc3_ep0_state_string(क्रमागत dwc3_ep0_state state)
अणु
	चयन (state) अणु
	हाल EP0_UNCONNECTED:
		वापस "Unconnected";
	हाल EP0_SETUP_PHASE:
		वापस "Setup Phase";
	हाल EP0_DATA_PHASE:
		वापस "Data Phase";
	हाल EP0_STATUS_PHASE:
		वापस "Status Phase";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

/**
 * dwc3_gadget_event_string - वापसs event name
 * @event: the event code
 */
अटल अंतरभूत स्थिर अक्षर *dwc3_gadget_event_string(अक्षर *str, माप_प्रकार size,
		स्थिर काष्ठा dwc3_event_devt *event)
अणु
	क्रमागत dwc3_link_state state = event->event_info & DWC3_LINK_STATE_MASK;

	चयन (event->type) अणु
	हाल DWC3_DEVICE_EVENT_DISCONNECT:
		snम_लिखो(str, size, "Disconnect: [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_RESET:
		snम_लिखो(str, size, "Reset [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_CONNECT_DONE:
		snम_लिखो(str, size, "Connection Done [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		snम_लिखो(str, size, "Link Change [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_WAKEUP:
		snम_लिखो(str, size, "WakeUp [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_SUSPEND:
		snम_लिखो(str, size, "Suspend [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_SOF:
		snम_लिखो(str, size, "Start-Of-Frame [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_ERRATIC_ERROR:
		snम_लिखो(str, size, "Erratic Error [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_CMD_CMPL:
		snम_लिखो(str, size, "Command Complete [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	हाल DWC3_DEVICE_EVENT_OVERFLOW:
		snम_लिखो(str, size, "Overflow [%s]",
				dwc3_gadget_link_string(state));
		अवरोध;
	शेष:
		snम_लिखो(str, size, "UNKNOWN");
	पूर्ण

	वापस str;
पूर्ण

/**
 * dwc3_ep_event_string - वापसs event name
 * @event: then event code
 */
अटल अंतरभूत स्थिर अक्षर *dwc3_ep_event_string(अक्षर *str, माप_प्रकार size,
		स्थिर काष्ठा dwc3_event_depevt *event, u32 ep0state)
अणु
	u8 epnum = event->endpoपूर्णांक_number;
	माप_प्रकार len;
	पूर्णांक status;

	len = scnम_लिखो(str, size, "ep%d%s: ", epnum >> 1,
			(epnum & 1) ? "in" : "out");

	status = event->status;

	चयन (event->endpoपूर्णांक_event) अणु
	हाल DWC3_DEPEVT_XFERCOMPLETE:
		len += scnम_लिखो(str + len, size - len,
				"Transfer Complete (%c%c%c)",
				status & DEPEVT_STATUS_SHORT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_LST ? 'L' : 'l');

		अगर (epnum <= 1)
			scnम_लिखो(str + len, size - len, " [%s]",
					dwc3_ep0_state_string(ep0state));
		अवरोध;
	हाल DWC3_DEPEVT_XFERINPROGRESS:
		scnम_लिखो(str + len, size - len,
				"Transfer In Progress [%d] (%c%c%c)",
				event->parameters,
				status & DEPEVT_STATUS_SHORT ? 'S' : 's',
				status & DEPEVT_STATUS_IOC ? 'I' : 'i',
				status & DEPEVT_STATUS_LST ? 'M' : 'm');
		अवरोध;
	हाल DWC3_DEPEVT_XFERNOTREADY:
		len += scnम_लिखो(str + len, size - len,
				"Transfer Not Ready [%d]%s",
				event->parameters,
				status & DEPEVT_STATUS_TRANSFER_ACTIVE ?
				" (Active)" : " (Not Active)");

		/* Control Endpoपूर्णांकs */
		अगर (epnum <= 1) अणु
			पूर्णांक phase = DEPEVT_STATUS_CONTROL_PHASE(event->status);

			चयन (phase) अणु
			हाल DEPEVT_STATUS_CONTROL_DATA:
				scnम_लिखो(str + len, size - len,
						" [Data Phase]");
				अवरोध;
			हाल DEPEVT_STATUS_CONTROL_STATUS:
				scnम_लिखो(str + len, size - len,
						" [Status Phase]");
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DWC3_DEPEVT_RXTXFIFOEVT:
		scnम_लिखो(str + len, size - len, "FIFO");
		अवरोध;
	हाल DWC3_DEPEVT_STREAMEVT:
		status = event->status;

		चयन (status) अणु
		हाल DEPEVT_STREAMEVT_FOUND:
			scnम_लिखो(str + len, size - len, " Stream %d Found",
					event->parameters);
			अवरोध;
		हाल DEPEVT_STREAMEVT_NOTFOUND:
		शेष:
			scnम_लिखो(str + len, size - len, " Stream Not Found");
			अवरोध;
		पूर्ण

		अवरोध;
	हाल DWC3_DEPEVT_EPCMDCMPLT:
		scnम_लिखो(str + len, size - len, "Endpoint Command Complete");
		अवरोध;
	शेष:
		scnम_लिखो(str + len, size - len, "UNKNOWN");
	पूर्ण

	वापस str;
पूर्ण

/**
 * dwc3_gadget_event_type_string - वापस event name
 * @event: the event code
 */
अटल अंतरभूत स्थिर अक्षर *dwc3_gadget_event_type_string(u8 event)
अणु
	चयन (event) अणु
	हाल DWC3_DEVICE_EVENT_DISCONNECT:
		वापस "Disconnect";
	हाल DWC3_DEVICE_EVENT_RESET:
		वापस "Reset";
	हाल DWC3_DEVICE_EVENT_CONNECT_DONE:
		वापस "Connect Done";
	हाल DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		वापस "Link Status Change";
	हाल DWC3_DEVICE_EVENT_WAKEUP:
		वापस "Wake-Up";
	हाल DWC3_DEVICE_EVENT_HIBER_REQ:
		वापस "Hibernation";
	हाल DWC3_DEVICE_EVENT_SUSPEND:
		वापस "Suspend";
	हाल DWC3_DEVICE_EVENT_SOF:
		वापस "Start of Frame";
	हाल DWC3_DEVICE_EVENT_ERRATIC_ERROR:
		वापस "Erratic Error";
	हाल DWC3_DEVICE_EVENT_CMD_CMPL:
		वापस "Command Complete";
	हाल DWC3_DEVICE_EVENT_OVERFLOW:
		वापस "Overflow";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *dwc3_decode_event(अक्षर *str, माप_प्रकार size, u32 event,
		u32 ep0state)
अणु
	जोड़ dwc3_event evt;

	स_नकल(&evt, &event, माप(event));

	अगर (evt.type.is_devspec)
		वापस dwc3_gadget_event_string(str, size, &evt.devt);
	अन्यथा
		वापस dwc3_ep_event_string(str, size, &evt.depevt, ep0state);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *dwc3_ep_cmd_status_string(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल -ETIMEDOUT:
		वापस "Timed Out";
	हाल 0:
		वापस "Successful";
	हाल DEPEVT_TRANSFER_NO_RESOURCE:
		वापस "No Resource";
	हाल DEPEVT_TRANSFER_BUS_EXPIRY:
		वापस "Bus Expiry";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *dwc3_gadget_generic_cmd_status_string(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल -ETIMEDOUT:
		वापस "Timed Out";
	हाल 0:
		वापस "Successful";
	हाल 1:
		वापस "Error";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_DEBUG_FS
बाह्य व्योम dwc3_debugfs_create_endpoपूर्णांक_dir(काष्ठा dwc3_ep *dep);
बाह्य व्योम dwc3_debugfs_init(काष्ठा dwc3 *d);
बाह्य व्योम dwc3_debugfs_निकास(काष्ठा dwc3 *d);
#अन्यथा
अटल अंतरभूत व्योम dwc3_debugfs_create_endpoपूर्णांक_dir(काष्ठा dwc3_ep *dep)
अणु  पूर्ण
अटल अंतरभूत व्योम dwc3_debugfs_init(काष्ठा dwc3 *d)
अणु  पूर्ण
अटल अंतरभूत व्योम dwc3_debugfs_निकास(काष्ठा dwc3 *d)
अणु  पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __DWC3_DEBUG_H */
