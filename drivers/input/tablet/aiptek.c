<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Native support क्रम the Aiptek HyperPen USB Tablets
 *  (4000U/5000U/6000U/8000U/12000U)
 *
 *  Copyright (c) 2001      Chris Atenasio   <chris@crud.net>
 *  Copyright (c) 2002-2004 Bryan W. Headley <bwheadley@earthlink.net>
 *
 *  based on wacom.c by
 *     Vojtech Pavlik      <vojtech@suse.cz>
 *     Andreas Bach Aaen   <abach@stofanet.dk>
 *     Clअगरक्रमd Wolf       <clअगरक्रमd@clअगरक्रमd.at>
 *     Sam Mosel           <sam.mosel@computer.org>
 *     James E. Blair      <corvus@gnu.org>
 *     Daniel Egger        <egger@suse.de>
 *
 *  Many thanks to Oliver Kuechemann क्रम his support.
 *
 *  ChangeLog:
 *      v0.1 - Initial release
 *      v0.2 - Hack to get around fake event 28's. (Bryan W. Headley)
 *      v0.3 - Make URB dynamic (Bryan W. Headley, Jun-8-2002)
 *             Released to Linux 2.4.19 and 2.5.x
 *      v0.4 - Rewrote substantial portions of the code to deal with
 *             corrected control sequences, timing, dynamic configuration,
 *             support of 6000U - 12000U, procfs, and macro key support
 *             (Jan-1-2003 - Feb-5-2003, Bryan W. Headley)
 *      v1.0 - Added support क्रम diagnostic messages, count of messages
 *             received from URB - Mar-8-2003, Bryan W. Headley
 *      v1.1 - added support क्रम tablet resolution, changed DV and proximity
 *             some corrections - Jun-22-2003, martin schneebacher
 *           - Added support क्रम the sysfs पूर्णांकerface, deprecating the
 *             procfs पूर्णांकerface क्रम 2.5.x kernel. Also added support क्रम
 *             Wheel command. Bryan W. Headley July-15-2003.
 *      v1.2 - Reworked jitter समयr as a kernel thपढ़ो.
 *             Bryan W. Headley November-28-2003/Jan-10-2004.
 *      v1.3 - Repaired issue of kernel thपढ़ो going nuts on single-processor
 *             machines, पूर्णांकroduced programmableDelay as a command line
 *             parameter. Feb 7 2004, Bryan W. Headley.
 *      v1.4 - Re-wire jitter so it करोes not require a thपढ़ो. Courtesy of
 *             Rene van Paassen. Added reporting of physical poपूर्णांकer device
 *             (e.g., stylus, mouse in reports 2, 3, 4, 5. We करोn't know
 *             क्रम reports 1, 6.)
 *             what physical device reports क्रम reports 1, 6.) Also enabled
 *             MOUSE and LENS tool button modes. Renamed "rubber" to "eraser".
 *             Feb 20, 2004, Bryan W. Headley.
 *      v1.5 - Added previousJitterable, so we करोn't करो jitter delay when the
 *             user is holding a button करोwn क्रम periods of समय.
 *
 * NOTE:
 *      This kernel driver is augmented by the "Aiptek" XFree86 input
 *      driver क्रम your X server, as well as the Gaiptek GUI Front-end
 *      "Tablet Manager".
 *      These three products are highly पूर्णांकeractive with one another,
 *      so thereक्रमe it's easier to करोcument them all as one subप्रणाली.
 *      Please visit the project's "home page", located at,
 *      http://aiptektablet.sourceक्रमge.net.
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

/*
 * Aiptek status packet:
 *
 * (वापसed as Report 1 - relative coordinates from mouse and stylus)
 *
 *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
 * byte0   0     0     0     0     0     0     0     1
 * byte1   0     0     0     0     0    BS2   BS    Tip
 * byte2  X7    X6    X5    X4    X3    X2    X1    X0
 * byte3  Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0
 *
 * (वापसed as Report 2 - असलolute coordinates from the stylus)
 *
 *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
 * byte0   0     0     0     0     0     0     1     0
 * byte1  X7    X6    X5    X4    X3    X2    X1    X0
 * byte2  X15   X14   X13   X12   X11   X10   X9    X8
 * byte3  Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0
 * byte4  Y15   Y14   Y13   Y12   Y11   Y10   Y9    Y8
 * byte5   *     *     *    BS2   BS1   Tip   IR    DV
 * byte6  P7    P6    P5    P4    P3    P2    P1    P0
 * byte7  P15   P14   P13   P12   P11   P10   P9    P8
 *
 * (वापसed as Report 3 - असलolute coordinates from the mouse)
 *
 *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
 * byte0   0     0     0     0     0     0     1     1
 * byte1  X7    X6    X5    X4    X3    X2    X1    X0
 * byte2  X15   X14   X13   X12   X11   X10   X9    X8
 * byte3  Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0
 * byte4  Y15   Y14   Y13   Y12   Y11   Y10   Y9    Y8
 * byte5   *     *     *    BS2   BS1   Tip   IR    DV
 * byte6  P7    P6    P5    P4    P3    P2    P1    P0
 * byte7  P15   P14   P13   P12   P11   P10   P9    P8
 *
 * (वापसed as Report 4 - macrokeys from the stylus)
 *
 *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
 * byte0   0     0     0     0     0     1     0     0
 * byte1   0     0     0    BS2   BS    Tip   IR    DV
 * byte2   0     0     0     0     0     0     1     0
 * byte3   0     0     0    K4    K3    K2    K1    K0
 * byte4  P7    P6    P5    P4    P3    P2    P1    P0
 * byte5  P15   P14   P13   P12   P11   P10   P9    P8
 *
 * (वापसed as Report 5 - macrokeys from the mouse)
 *
 *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0
 * byte0   0     0     0     0     0     1     0     1
 * byte1   0     0     0    BS2   BS    Tip   IR    DV
 * byte2   0     0     0     0     0     0     1     0
 * byte3   0     0     0    K4    K3    K2    K1    K0
 * byte4  P7    P6    P5    P4    P3    P2    P1    P0
 * byte5  P15   P14   P13   P12   P11   P10   P9    P8
 *
 * IR: In Range = Proximity on
 * DV = Data Valid
 * BS = Barrel Switch (as in, macro keys)
 * BS2 also referred to as Tablet Pick
 *
 * Command Summary:
 *
 * Use report_type CONTROL (3)
 * Use report_id   2
 *
 * Command/Data    Description     Return Bytes    Return Value
 * 0x10/0x00       SwitchToMouse       0
 * 0x10/0x01       SwitchToTablet      0
 * 0x18/0x04       SetResolution       0
 * 0x12/0xFF       AutoGainOn          0
 * 0x17/0x00       FilterOn            0
 * 0x01/0x00       GetXExtension       2           MaxX
 * 0x01/0x01       GetYExtension       2           MaxY
 * 0x02/0x00       GetModelCode        2           ModelCode = LOBYTE
 * 0x03/0x00       GetODMCode          2           ODMCode
 * 0x08/0x00       GetPressureLevels   2           =512
 * 0x04/0x00       GetFirmwareVersion  2           Firmware Version
 * 0x11/0x02       EnableMacroKeys     0
 *
 * To initialize the tablet:
 *
 * (1) Send Resolution500LPI (Command)
 * (2) Query क्रम Model code (Option Report)
 * (3) Query क्रम ODM code (Option Report)
 * (4) Query क्रम firmware (Option Report)
 * (5) Query क्रम GetXExtension (Option Report)
 * (6) Query क्रम GetYExtension (Option Report)
 * (7) Query क्रम GetPressureLevels (Option Report)
 * (8) SwitchToTablet क्रम Absolute coordinates, or
 *     SwitchToMouse क्रम Relative coordinates (Command)
 * (9) EnableMacroKeys (Command)
 * (10) FilterOn (Command)
 * (11) AutoGainOn (Command)
 *
 * (Step 9 can be omitted, but you'll then have no function keys.)
 */

#घोषणा USB_VENDOR_ID_AIPTEK				0x08ca
#घोषणा USB_VENDOR_ID_KYE				0x0458
#घोषणा USB_REQ_GET_REPORT				0x01
#घोषणा USB_REQ_SET_REPORT				0x09

	/* Poपूर्णांकerMode codes
	 */
#घोषणा AIPTEK_POINTER_ONLY_MOUSE_MODE			0
#घोषणा AIPTEK_POINTER_ONLY_STYLUS_MODE			1
#घोषणा AIPTEK_POINTER_EITHER_MODE			2

#घोषणा AIPTEK_POINTER_ALLOW_MOUSE_MODE(a)		\
	(a == AIPTEK_POINTER_ONLY_MOUSE_MODE ||		\
	 a == AIPTEK_POINTER_EITHER_MODE)
#घोषणा AIPTEK_POINTER_ALLOW_STYLUS_MODE(a)		\
	(a == AIPTEK_POINTER_ONLY_STYLUS_MODE ||	\
	 a == AIPTEK_POINTER_EITHER_MODE)

	/* CoordinateMode code
	 */
#घोषणा AIPTEK_COORDINATE_RELATIVE_MODE			0
#घोषणा AIPTEK_COORDINATE_ABSOLUTE_MODE			1

       /* XTilt and YTilt values
        */
#घोषणा AIPTEK_TILT_MIN					(-128)
#घोषणा AIPTEK_TILT_MAX					127
#घोषणा AIPTEK_TILT_DISABLE				(-10101)

	/* Wheel values
	 */
#घोषणा AIPTEK_WHEEL_MIN				0
#घोषणा AIPTEK_WHEEL_MAX				1024
#घोषणा AIPTEK_WHEEL_DISABLE				(-10101)

	/* ToolCode values, which BTW are 0x140 .. 0x14f
	 * We have things set up such that अगर the tool button has changed,
	 * the tools get reset.
	 */
	/* toolMode codes
	 */
#घोषणा AIPTEK_TOOL_BUTTON_PEN_MODE			BTN_TOOL_PEN
#घोषणा AIPTEK_TOOL_BUTTON_PENCIL_MODE			BTN_TOOL_PENCIL
#घोषणा AIPTEK_TOOL_BUTTON_BRUSH_MODE			BTN_TOOL_BRUSH
#घोषणा AIPTEK_TOOL_BUTTON_AIRBRUSH_MODE		BTN_TOOL_AIRBRUSH
#घोषणा AIPTEK_TOOL_BUTTON_ERASER_MODE			BTN_TOOL_RUBBER
#घोषणा AIPTEK_TOOL_BUTTON_MOUSE_MODE			BTN_TOOL_MOUSE
#घोषणा AIPTEK_TOOL_BUTTON_LENS_MODE			BTN_TOOL_LENS

	/* Diagnostic message codes
	 */
#घोषणा AIPTEK_DIAGNOSTIC_NA				0
#घोषणा AIPTEK_DIAGNOSTIC_SENDING_RELATIVE_IN_ABSOLUTE	1
#घोषणा AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE	2
#घोषणा AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED		3

	/* Time to रुको (in ms) to help mask hand jittering
	 * when pressing the stylus buttons.
	 */
#घोषणा AIPTEK_JITTER_DELAY_DEFAULT			50

	/* Time to रुको (in ms) in-between sending the tablet
	 * a command and beginning the process of पढ़ोing the वापस
	 * sequence from the tablet.
	 */
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_25		25
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_50		50
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_100		100
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_200		200
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_300		300
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_400		400
#घोषणा AIPTEK_PROGRAMMABLE_DELAY_DEFAULT	AIPTEK_PROGRAMMABLE_DELAY_400

	/* Mouse button programming
	 */
#घोषणा AIPTEK_MOUSE_LEFT_BUTTON		0x04
#घोषणा AIPTEK_MOUSE_RIGHT_BUTTON		0x08
#घोषणा AIPTEK_MOUSE_MIDDLE_BUTTON		0x10

	/* Stylus button programming
	 */
#घोषणा AIPTEK_STYLUS_LOWER_BUTTON		0x08
#घोषणा AIPTEK_STYLUS_UPPER_BUTTON		0x10

	/* Length of incoming packet from the tablet
	 */
#घोषणा AIPTEK_PACKET_LENGTH			8

	/* We report in EV_MISC both the proximity and
	 * whether the report came from the stylus, tablet mouse
	 * or "unknown" -- Unknown when the tablet is in relative
	 * mode, because we only get report 1's.
	 */
#घोषणा AIPTEK_REPORT_TOOL_UNKNOWN		0x10
#घोषणा AIPTEK_REPORT_TOOL_STYLUS		0x20
#घोषणा AIPTEK_REPORT_TOOL_MOUSE		0x40

अटल पूर्णांक programmableDelay = AIPTEK_PROGRAMMABLE_DELAY_DEFAULT;
अटल पूर्णांक jitterDelay = AIPTEK_JITTER_DELAY_DEFAULT;

काष्ठा aiptek_features अणु
	पूर्णांक odmCode;		/* Tablet manufacturer code       */
	पूर्णांक modelCode;		/* Tablet model code (not unique) */
	पूर्णांक firmwareCode;	/* prom/eeprom version            */
	अक्षर usbPath[64 + 1];	/* device's physical usb path     */
पूर्ण;

काष्ठा aiptek_settings अणु
	पूर्णांक poपूर्णांकerMode;	/* stylus-, mouse-only or either */
	पूर्णांक coordinateMode;	/* असलolute/relative coords      */
	पूर्णांक toolMode;		/* pen, pencil, brush, etc. tool */
	पूर्णांक xTilt;		/* synthetic xTilt amount        */
	पूर्णांक yTilt;		/* synthetic yTilt amount        */
	पूर्णांक wheel;		/* synthetic wheel amount        */
	पूर्णांक stylusButtonUpper;	/* stylus upper btn delivers...  */
	पूर्णांक stylusButtonLower;	/* stylus lower btn delivers...  */
	पूर्णांक mouseButtonLeft;	/* mouse left btn delivers...    */
	पूर्णांक mouseButtonMiddle;	/* mouse middle btn delivers...  */
	पूर्णांक mouseButtonRight;	/* mouse right btn delivers...   */
	पूर्णांक programmableDelay;	/* delay क्रम tablet programming  */
	पूर्णांक jitterDelay;	/* delay क्रम hand jittering      */
पूर्ण;

काष्ठा aiptek अणु
	काष्ठा input_dev *inputdev;		/* input device काष्ठा           */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;		/* usb पूर्णांकerface काष्ठा          */
	काष्ठा urb *urb;			/* urb क्रम incoming reports      */
	dma_addr_t data_dma;			/* our dma stuffage              */
	काष्ठा aiptek_features features;	/* tablet's array of features    */
	काष्ठा aiptek_settings curSetting;	/* tablet's current programmable */
	काष्ठा aiptek_settings newSetting;	/* ... and new param settings    */
	अचिन्हित पूर्णांक अगरnum;			/* पूर्णांकerface number क्रम IO       */
	पूर्णांक diagnostic;				/* tablet diagnostic codes       */
	अचिन्हित दीर्घ eventCount;		/* event count                   */
	पूर्णांक inDelay;				/* jitter: in jitter delay?      */
	अचिन्हित दीर्घ endDelay;			/* jitter: समय when delay ends  */
	पूर्णांक previousJitterable;			/* jitterable prev value     */

	पूर्णांक lastMacro;				/* macro key to reset            */
	पूर्णांक previousToolMode;			/* pen, pencil, brush, etc. tool */
	अचिन्हित अक्षर *data;			/* incoming packet data          */
पूर्ण;

अटल स्थिर पूर्णांक eventTypes[] = अणु
        EV_KEY, EV_ABS, EV_REL, EV_MSC,
पूर्ण;

अटल स्थिर पूर्णांक असलEvents[] = अणु
        ABS_X, ABS_Y, ABS_PRESSURE, ABS_TILT_X, ABS_TILT_Y,
        ABS_WHEEL, ABS_MISC,
पूर्ण;

अटल स्थिर पूर्णांक relEvents[] = अणु
        REL_X, REL_Y, REL_WHEEL,
पूर्ण;

अटल स्थिर पूर्णांक buttonEvents[] = अणु
	BTN_LEFT, BTN_RIGHT, BTN_MIDDLE,
	BTN_TOOL_PEN, BTN_TOOL_RUBBER, BTN_TOOL_PENCIL, BTN_TOOL_AIRBRUSH,
	BTN_TOOL_BRUSH, BTN_TOOL_MOUSE, BTN_TOOL_LENS, BTN_TOUCH,
	BTN_STYLUS, BTN_STYLUS2,
पूर्ण;

/*
 * Permit easy lookup of keyboard events to send, versus
 * the biपंचांगap which comes from the tablet. This hides the
 * issue that the F_keys are not sequentially numbered.
 */
अटल स्थिर पूर्णांक macroKeyEvents[] = अणु
	KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
	KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11,
	KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17,
	KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23,
	KEY_F24, KEY_STOP, KEY_AGAIN, KEY_PROPS, KEY_UNDO,
	KEY_FRONT, KEY_COPY, KEY_OPEN, KEY_PASTE, 0
पूर्ण;

/***********************************************************************
 * Map values to strings and back. Every map should have the following
 * as its last element: अणु शून्य, AIPTEK_INVALID_VALUE पूर्ण.
 */
#घोषणा AIPTEK_INVALID_VALUE	-1

काष्ठा aiptek_map अणु
	स्थिर अक्षर *string;
	पूर्णांक value;
पूर्ण;

अटल पूर्णांक map_str_to_val(स्थिर काष्ठा aiptek_map *map, स्थिर अक्षर *str, माप_प्रकार count)
अणु
	स्थिर काष्ठा aiptek_map *p;

	अगर (str[count - 1] == '\n')
		count--;

	क्रम (p = map; p->string; p++)
	        अगर (!म_भेदन(str, p->string, count))
			वापस p->value;

	वापस AIPTEK_INVALID_VALUE;
पूर्ण

अटल स्थिर अक्षर *map_val_to_str(स्थिर काष्ठा aiptek_map *map, पूर्णांक val)
अणु
	स्थिर काष्ठा aiptek_map *p;

	क्रम (p = map; p->value != AIPTEK_INVALID_VALUE; p++)
		अगर (val == p->value)
			वापस p->string;

	वापस "unknown";
पूर्ण

/***********************************************************************
 * aiptek_irq can receive one of six potential reports.
 * The करोcumentation क्रम each is in the body of the function.
 *
 * The tablet reports on several attributes per invocation of
 * aiptek_irq. Because the Linux Input Event प्रणाली allows the
 * transmission of ONE attribute per input_report_xxx() call,
 * collation has to be करोne on the other end to reस्थिरitute
 * a complete tablet report. Further, the number of Input Event reports
 * submitted varies, depending on what USB report type, and circumstance.
 * To deal with this, EV_MSC is used to indicate an 'end-of-report'
 * message. This has been an unकरोcumented convention understood by the kernel
 * tablet driver and clients such as gpm and XFree86's tablet drivers.
 *
 * Of the inक्रमmation received from the tablet, the one piece I
 * cannot transmit is the proximity bit (without resorting to an EV_MSC
 * convention above.) I thereक्रमe have taken over REL_MISC and ABS_MISC
 * (क्रम relative and असलolute reports, respectively) क्रम communicating
 * Proximity. Why two events? I thought it पूर्णांकeresting to know अगर the
 * Proximity event occurred जबतक the tablet was in असलolute or relative
 * mode.
 * Update: REL_MISC proved not to be such a good idea. With REL_MISC you
 * get an event transmitted each समय. ABS_MISC works better, since it
 * can be set and re-set. Thus, only using ABS_MISC from now on.
 *
 * Other tablets use the notion of a certain minimum stylus pressure
 * to infer proximity. While that could have been करोne, that is yet
 * another 'by convention' behavior, the करोcumentation क्रम which
 * would be spपढ़ो between two (or more) pieces of software.
 *
 * EV_MSC usage was terminated क्रम this purpose in Linux 2.5.x, and
 * replaced with the input_sync() method (which emits EV_SYN.)
 */

अटल व्योम aiptek_irq(काष्ठा urb *urb)
अणु
	काष्ठा aiptek *aiptek = urb->context;
	अचिन्हित अक्षर *data = aiptek->data;
	काष्ठा input_dev *inputdev = aiptek->inputdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = aiptek->पूर्णांकf;
	पूर्णांक jitterable = 0;
	पूर्णांक retval, macro, x, y, z, left, right, middle, p, dv, tip, bs, pck;

	चयन (urb->status) अणु
	हाल 0:
		/* Success */
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* This urb is terminated, clean up */
		dev_dbg(&पूर्णांकf->dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;

	शेष:
		dev_dbg(&पूर्णांकf->dev, "%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	/* See अगर we are in a delay loop -- throw out report अगर true.
	 */
	अगर (aiptek->inDelay == 1 && समय_after(aiptek->endDelay, jअगरfies)) अणु
		जाओ निकास;
	पूर्ण

	aiptek->inDelay = 0;
	aiptek->eventCount++;

	/* Report 1 delivers relative coordinates with either a stylus
	 * or the mouse. You करो not know, however, which input
	 * tool generated the event.
	 */
	अगर (data[0] == 1) अणु
		अगर (aiptek->curSetting.coordinateMode ==
		    AIPTEK_COORDINATE_ABSOLUTE_MODE) अणु
			aiptek->diagnostic =
			    AIPTEK_DIAGNOSTIC_SENDING_RELATIVE_IN_ABSOLUTE;
		पूर्ण अन्यथा अणु
			x = (चिन्हित अक्षर) data[2];
			y = (चिन्हित अक्षर) data[3];

			/* jitterable keeps track of whether any button has been pressed.
			 * We're also using it to remap the physical mouse button mask
			 * to pseuकरो-settings. (We करोn't specifically care about it's
			 * value after moving/transposing mouse button biपंचांगasks, except
			 * that a non-zero value indicates that one or more
			 * mouse button was pressed.)
			 */
			jitterable = data[1] & 0x07;

			left = (data[1] & aiptek->curSetting.mouseButtonLeft >> 2) != 0 ? 1 : 0;
			right = (data[1] & aiptek->curSetting.mouseButtonRight >> 2) != 0 ? 1 : 0;
			middle = (data[1] & aiptek->curSetting.mouseButtonMiddle >> 2) != 0 ? 1 : 0;

			input_report_key(inputdev, BTN_LEFT, left);
			input_report_key(inputdev, BTN_MIDDLE, middle);
			input_report_key(inputdev, BTN_RIGHT, right);

			input_report_असल(inputdev, ABS_MISC,
					 1 | AIPTEK_REPORT_TOOL_UNKNOWN);
			input_report_rel(inputdev, REL_X, x);
			input_report_rel(inputdev, REL_Y, y);

			/* Wheel support is in the क्रमm of a single-event
			 * firing.
			 */
			अगर (aiptek->curSetting.wheel != AIPTEK_WHEEL_DISABLE) अणु
				input_report_rel(inputdev, REL_WHEEL,
						 aiptek->curSetting.wheel);
				aiptek->curSetting.wheel = AIPTEK_WHEEL_DISABLE;
			पूर्ण
			अगर (aiptek->lastMacro != -1) अणु
			        input_report_key(inputdev,
						 macroKeyEvents[aiptek->lastMacro], 0);
				aiptek->lastMacro = -1;
			पूर्ण
			input_sync(inputdev);
		पूर्ण
	पूर्ण
	/* Report 2 is delivered only by the stylus, and delivers
	 * असलolute coordinates.
	 */
	अन्यथा अगर (data[0] == 2) अणु
		अगर (aiptek->curSetting.coordinateMode == AIPTEK_COORDINATE_RELATIVE_MODE) अणु
			aiptek->diagnostic = AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE;
		पूर्ण अन्यथा अगर (!AIPTEK_POINTER_ALLOW_STYLUS_MODE
			    (aiptek->curSetting.poपूर्णांकerMode)) अणु
				aiptek->diagnostic = AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED;
		पूर्ण अन्यथा अणु
			x = get_unaligned_le16(data + 1);
			y = get_unaligned_le16(data + 3);
			z = get_unaligned_le16(data + 6);

			dv = (data[5] & 0x01) != 0 ? 1 : 0;
			p = (data[5] & 0x02) != 0 ? 1 : 0;
			tip = (data[5] & 0x04) != 0 ? 1 : 0;

			/* Use jitterable to re-arrange button masks
			 */
			jitterable = data[5] & 0x18;

			bs = (data[5] & aiptek->curSetting.stylusButtonLower) != 0 ? 1 : 0;
			pck = (data[5] & aiptek->curSetting.stylusButtonUpper) != 0 ? 1 : 0;

			/* dv indicates 'data valid' (e.g., the tablet is in sync
			 * and has delivered a "correct" report) We will ignore
			 * all 'bad' reports...
			 */
			अगर (dv != 0) अणु
				/* If the selected tool changed, reset the old
				 * tool key, and set the new one.
				 */
				अगर (aiptek->previousToolMode !=
				    aiptek->curSetting.toolMode) अणु
				        input_report_key(inputdev,
							 aiptek->previousToolMode, 0);
					input_report_key(inputdev,
							 aiptek->curSetting.toolMode,
							 1);
					aiptek->previousToolMode =
					          aiptek->curSetting.toolMode;
				पूर्ण

				अगर (p != 0) अणु
					input_report_असल(inputdev, ABS_X, x);
					input_report_असल(inputdev, ABS_Y, y);
					input_report_असल(inputdev, ABS_PRESSURE, z);

					input_report_key(inputdev, BTN_TOUCH, tip);
					input_report_key(inputdev, BTN_STYLUS, bs);
					input_report_key(inputdev, BTN_STYLUS2, pck);

					अगर (aiptek->curSetting.xTilt !=
					    AIPTEK_TILT_DISABLE) अणु
						input_report_असल(inputdev,
								 ABS_TILT_X,
								 aiptek->curSetting.xTilt);
					पूर्ण
					अगर (aiptek->curSetting.yTilt != AIPTEK_TILT_DISABLE) अणु
						input_report_असल(inputdev,
								 ABS_TILT_Y,
								 aiptek->curSetting.yTilt);
					पूर्ण

					/* Wheel support is in the क्रमm of a single-event
					 * firing.
					 */
					अगर (aiptek->curSetting.wheel !=
					    AIPTEK_WHEEL_DISABLE) अणु
						input_report_असल(inputdev,
								 ABS_WHEEL,
								 aiptek->curSetting.wheel);
						aiptek->curSetting.wheel = AIPTEK_WHEEL_DISABLE;
					पूर्ण
				पूर्ण
				input_report_असल(inputdev, ABS_MISC, p | AIPTEK_REPORT_TOOL_STYLUS);
				अगर (aiptek->lastMacro != -1) अणु
			                input_report_key(inputdev,
							 macroKeyEvents[aiptek->lastMacro], 0);
					aiptek->lastMacro = -1;
				पूर्ण
				input_sync(inputdev);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Report 3's come from the mouse in असलolute mode.
	 */
	अन्यथा अगर (data[0] == 3) अणु
		अगर (aiptek->curSetting.coordinateMode == AIPTEK_COORDINATE_RELATIVE_MODE) अणु
			aiptek->diagnostic = AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE;
		पूर्ण अन्यथा अगर (!AIPTEK_POINTER_ALLOW_MOUSE_MODE
			(aiptek->curSetting.poपूर्णांकerMode)) अणु
			aiptek->diagnostic = AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED;
		पूर्ण अन्यथा अणु
			x = get_unaligned_le16(data + 1);
			y = get_unaligned_le16(data + 3);

			jitterable = data[5] & 0x1c;

			dv = (data[5] & 0x01) != 0 ? 1 : 0;
			p = (data[5] & 0x02) != 0 ? 1 : 0;
			left = (data[5] & aiptek->curSetting.mouseButtonLeft) != 0 ? 1 : 0;
			right = (data[5] & aiptek->curSetting.mouseButtonRight) != 0 ? 1 : 0;
			middle = (data[5] & aiptek->curSetting.mouseButtonMiddle) != 0 ? 1 : 0;

			अगर (dv != 0) अणु
				/* If the selected tool changed, reset the old
				 * tool key, and set the new one.
				 */
				अगर (aiptek->previousToolMode !=
				    aiptek->curSetting.toolMode) अणु
				        input_report_key(inputdev,
							 aiptek->previousToolMode, 0);
					input_report_key(inputdev,
							 aiptek->curSetting.toolMode,
							 1);
					aiptek->previousToolMode =
					          aiptek->curSetting.toolMode;
				पूर्ण

				अगर (p != 0) अणु
					input_report_असल(inputdev, ABS_X, x);
					input_report_असल(inputdev, ABS_Y, y);

					input_report_key(inputdev, BTN_LEFT, left);
					input_report_key(inputdev, BTN_MIDDLE, middle);
					input_report_key(inputdev, BTN_RIGHT, right);

					/* Wheel support is in the क्रमm of a single-event
					 * firing.
					 */
					अगर (aiptek->curSetting.wheel != AIPTEK_WHEEL_DISABLE) अणु
						input_report_असल(inputdev,
								 ABS_WHEEL,
								 aiptek->curSetting.wheel);
						aiptek->curSetting.wheel = AIPTEK_WHEEL_DISABLE;
					पूर्ण
				पूर्ण
				input_report_असल(inputdev, ABS_MISC, p | AIPTEK_REPORT_TOOL_MOUSE);
				अगर (aiptek->lastMacro != -1) अणु
			                input_report_key(inputdev,
							 macroKeyEvents[aiptek->lastMacro], 0);
				        aiptek->lastMacro = -1;
				पूर्ण
				input_sync(inputdev);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Report 4s come from the macro keys when pressed by stylus
	 */
	अन्यथा अगर (data[0] == 4) अणु
		jitterable = data[1] & 0x18;

		dv = (data[1] & 0x01) != 0 ? 1 : 0;
		p = (data[1] & 0x02) != 0 ? 1 : 0;
		tip = (data[1] & 0x04) != 0 ? 1 : 0;
		bs = (data[1] & aiptek->curSetting.stylusButtonLower) != 0 ? 1 : 0;
		pck = (data[1] & aiptek->curSetting.stylusButtonUpper) != 0 ? 1 : 0;

		macro = dv && p && tip && !(data[3] & 1) ? (data[3] >> 1) : -1;
		z = get_unaligned_le16(data + 4);

		अगर (dv) अणु
		        /* If the selected tool changed, reset the old
			 * tool key, and set the new one.
			 */
		        अगर (aiptek->previousToolMode !=
			    aiptek->curSetting.toolMode) अणु
			        input_report_key(inputdev,
						 aiptek->previousToolMode, 0);
				input_report_key(inputdev,
						 aiptek->curSetting.toolMode,
						 1);
				aiptek->previousToolMode =
				        aiptek->curSetting.toolMode;
			पूर्ण
		पूर्ण

		अगर (aiptek->lastMacro != -1 && aiptek->lastMacro != macro) अणु
		        input_report_key(inputdev, macroKeyEvents[aiptek->lastMacro], 0);
			aiptek->lastMacro = -1;
		पूर्ण

		अगर (macro != -1 && macro != aiptek->lastMacro) अणु
			input_report_key(inputdev, macroKeyEvents[macro], 1);
			aiptek->lastMacro = macro;
		पूर्ण
		input_report_असल(inputdev, ABS_MISC,
				 p | AIPTEK_REPORT_TOOL_STYLUS);
		input_sync(inputdev);
	पूर्ण
	/* Report 5s come from the macro keys when pressed by mouse
	 */
	अन्यथा अगर (data[0] == 5) अणु
		jitterable = data[1] & 0x1c;

		dv = (data[1] & 0x01) != 0 ? 1 : 0;
		p = (data[1] & 0x02) != 0 ? 1 : 0;
		left = (data[1]& aiptek->curSetting.mouseButtonLeft) != 0 ? 1 : 0;
		right = (data[1] & aiptek->curSetting.mouseButtonRight) != 0 ? 1 : 0;
		middle = (data[1] & aiptek->curSetting.mouseButtonMiddle) != 0 ? 1 : 0;
		macro = dv && p && left && !(data[3] & 1) ? (data[3] >> 1) : 0;

		अगर (dv) अणु
		        /* If the selected tool changed, reset the old
			 * tool key, and set the new one.
			 */
		        अगर (aiptek->previousToolMode !=
			    aiptek->curSetting.toolMode) अणु
		                input_report_key(inputdev,
						 aiptek->previousToolMode, 0);
			        input_report_key(inputdev,
						 aiptek->curSetting.toolMode, 1);
			        aiptek->previousToolMode = aiptek->curSetting.toolMode;
			पूर्ण
		पूर्ण

		अगर (aiptek->lastMacro != -1 && aiptek->lastMacro != macro) अणु
		        input_report_key(inputdev, macroKeyEvents[aiptek->lastMacro], 0);
			aiptek->lastMacro = -1;
		पूर्ण

		अगर (macro != -1 && macro != aiptek->lastMacro) अणु
			input_report_key(inputdev, macroKeyEvents[macro], 1);
			aiptek->lastMacro = macro;
		पूर्ण

		input_report_असल(inputdev, ABS_MISC,
				 p | AIPTEK_REPORT_TOOL_MOUSE);
		input_sync(inputdev);
	पूर्ण
	/* We have no idea which tool can generate a report 6. Theoretically,
	 * neither need to, having been given reports 4 & 5 क्रम such use.
	 * However, report 6 is the 'official-looking' report क्रम macroKeys;
	 * reports 4 & 5 supposively are used to support unnamed, unknown
	 * hat चयनes (which just so happen to be the macroKeys.)
	 */
	अन्यथा अगर (data[0] == 6) अणु
		macro = get_unaligned_le16(data + 1);
		अगर (macro > 0) अणु
			input_report_key(inputdev, macroKeyEvents[macro - 1],
					 0);
		पूर्ण
		अगर (macro < 25) अणु
			input_report_key(inputdev, macroKeyEvents[macro + 1],
					 0);
		पूर्ण

		/* If the selected tool changed, reset the old
		   tool key, and set the new one.
		*/
		अगर (aiptek->previousToolMode !=
		    aiptek->curSetting.toolMode) अणु
		        input_report_key(inputdev,
					 aiptek->previousToolMode, 0);
			input_report_key(inputdev,
					 aiptek->curSetting.toolMode,
					 1);
			aiptek->previousToolMode =
				aiptek->curSetting.toolMode;
		पूर्ण

		input_report_key(inputdev, macroKeyEvents[macro], 1);
		input_report_असल(inputdev, ABS_MISC,
				 1 | AIPTEK_REPORT_TOOL_UNKNOWN);
		input_sync(inputdev);
	पूर्ण अन्यथा अणु
		dev_dbg(&पूर्णांकf->dev, "Unknown report %d\n", data[0]);
	पूर्ण

	/* Jitter may occur when the user presses a button on the stlyus
	 * or the mouse. What we करो to prevent that is रुको 'x' milliseconds
	 * following a 'jitterable' event, which should give the hand some समय
	 * stabilize itself.
	 *
	 * We just पूर्णांकroduced aiptek->previousJitterable to carry क्रमth the
	 * notion that jitter occurs when the button state changes from on to off:
	 * a person drawing, holding a button करोwn is not subject to jittering.
	 * With that in mind, changing from upper button depressed to lower button
	 * WILL transition through a jitter delay.
	 */

	अगर (aiptek->previousJitterable != jitterable &&
	    aiptek->curSetting.jitterDelay != 0 && aiptek->inDelay != 1) अणु
		aiptek->endDelay = jअगरfies +
		    ((aiptek->curSetting.jitterDelay * HZ) / 1000);
		aiptek->inDelay = 1;
	पूर्ण
	aiptek->previousJitterable = jitterable;

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval != 0) अणु
		dev_err(&पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
	पूर्ण
पूर्ण

/***********************************************************************
 * These are the USB id's known so far. We करो not identअगरy them to
 * specअगरic Aiptek model numbers, because there has been overlaps,
 * use, and reuse of id's in existing models. Certain models have
 * been known to use more than one ID, indicative perhaps of
 * manufacturing revisions. In any event, we consider these
 * IDs to not be model-specअगरic nor unique.
 */
अटल स्थिर काष्ठा usb_device_id aiptek_ids[] = अणु
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x01)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x10)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x20)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x21)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x22)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x23)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_AIPTEK, 0x24)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_KYE, 0x5003)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, aiptek_ids);

/***********************************************************************
 * Open an instance of the tablet driver.
 */
अटल पूर्णांक aiptek_खोलो(काष्ठा input_dev *inputdev)
अणु
	काष्ठा aiptek *aiptek = input_get_drvdata(inputdev);

	aiptek->urb->dev = पूर्णांकerface_to_usbdev(aiptek->पूर्णांकf);
	अगर (usb_submit_urb(aiptek->urb, GFP_KERNEL) != 0)
		वापस -EIO;

	वापस 0;
पूर्ण

/***********************************************************************
 * Close an instance of the tablet driver.
 */
अटल व्योम aiptek_बंद(काष्ठा input_dev *inputdev)
अणु
	काष्ठा aiptek *aiptek = input_get_drvdata(inputdev);

	usb_समाप्त_urb(aiptek->urb);
पूर्ण

/***********************************************************************
 * aiptek_set_report and aiptek_get_report() are borrowed from Linux 2.4.x,
 * where they were known as usb_set_report and usb_get_report.
 */
अटल पूर्णांक
aiptek_set_report(काष्ठा aiptek *aiptek,
		  अचिन्हित अक्षर report_type,
		  अचिन्हित अक्षर report_id, व्योम *buffer, पूर्णांक size)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(aiptek->पूर्णांकf);

	वापस usb_control_msg(udev,
			       usb_sndctrlpipe(udev, 0),
			       USB_REQ_SET_REPORT,
			       USB_TYPE_CLASS | USB_RECIP_INTERFACE |
			       USB_सूची_OUT, (report_type << 8) + report_id,
			       aiptek->अगरnum, buffer, size, 5000);
पूर्ण

अटल पूर्णांक
aiptek_get_report(काष्ठा aiptek *aiptek,
		  अचिन्हित अक्षर report_type,
		  अचिन्हित अक्षर report_id, व्योम *buffer, पूर्णांक size)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(aiptek->पूर्णांकf);

	वापस usb_control_msg(udev,
			       usb_rcvctrlpipe(udev, 0),
			       USB_REQ_GET_REPORT,
			       USB_TYPE_CLASS | USB_RECIP_INTERFACE |
			       USB_सूची_IN, (report_type << 8) + report_id,
			       aiptek->अगरnum, buffer, size, 5000);
पूर्ण

/***********************************************************************
 * Send a command to the tablet.
 */
अटल पूर्णांक
aiptek_command(काष्ठा aiptek *aiptek, अचिन्हित अक्षर command, अचिन्हित अक्षर data)
अणु
	स्थिर पूर्णांक माप_buf = 3 * माप(u8);
	पूर्णांक ret;
	u8 *buf;

	buf = kदो_स्मृति(माप_buf, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = 2;
	buf[1] = command;
	buf[2] = data;

	अगर ((ret =
	     aiptek_set_report(aiptek, 3, 2, buf, माप_buf)) != माप_buf) अणु
		dev_dbg(&aiptek->पूर्णांकf->dev,
			"aiptek_program: failed, tried to send: 0x%02x 0x%02x\n",
			command, data);
	पूर्ण
	kमुक्त(buf);
	वापस ret < 0 ? ret : 0;
पूर्ण

/***********************************************************************
 * Retrieve inक्रमmation from the tablet. Querying info is defined as first
 * sending the अणुcommand,dataपूर्ण sequence as a command, followed by a रुको
 * (aka, "programmaticDelay") and then a "read" request.
 */
अटल पूर्णांक
aiptek_query(काष्ठा aiptek *aiptek, अचिन्हित अक्षर command, अचिन्हित अक्षर data)
अणु
	स्थिर पूर्णांक माप_buf = 3 * माप(u8);
	पूर्णांक ret;
	u8 *buf;

	buf = kदो_स्मृति(माप_buf, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = 2;
	buf[1] = command;
	buf[2] = data;

	अगर (aiptek_command(aiptek, command, data) != 0) अणु
		kमुक्त(buf);
		वापस -EIO;
	पूर्ण
	msleep(aiptek->curSetting.programmableDelay);

	अगर ((ret =
	     aiptek_get_report(aiptek, 3, 2, buf, माप_buf)) != माप_buf) अणु
		dev_dbg(&aiptek->पूर्णांकf->dev,
			"aiptek_query failed: returned 0x%02x 0x%02x 0x%02x\n",
			buf[0], buf[1], buf[2]);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		ret = get_unaligned_le16(buf + 1);
	पूर्ण
	kमुक्त(buf);
	वापस ret;
पूर्ण

/***********************************************************************
 * Program the tablet पूर्णांकo either असलolute or relative mode.
 * We also get inक्रमmation about the tablet's size.
 */
अटल पूर्णांक aiptek_program_tablet(काष्ठा aiptek *aiptek)
अणु
	पूर्णांक ret;
	/* Execute Resolution500LPI */
	अगर ((ret = aiptek_command(aiptek, 0x18, 0x04)) < 0)
		वापस ret;

	/* Query getModelCode */
	अगर ((ret = aiptek_query(aiptek, 0x02, 0x00)) < 0)
		वापस ret;
	aiptek->features.modelCode = ret & 0xff;

	/* Query getODMCode */
	अगर ((ret = aiptek_query(aiptek, 0x03, 0x00)) < 0)
		वापस ret;
	aiptek->features.odmCode = ret;

	/* Query getFirmwareCode */
	अगर ((ret = aiptek_query(aiptek, 0x04, 0x00)) < 0)
		वापस ret;
	aiptek->features.firmwareCode = ret;

	/* Query getXextension */
	अगर ((ret = aiptek_query(aiptek, 0x01, 0x00)) < 0)
		वापस ret;
	input_set_असल_params(aiptek->inputdev, ABS_X, 0, ret - 1, 0, 0);

	/* Query getYextension */
	अगर ((ret = aiptek_query(aiptek, 0x01, 0x01)) < 0)
		वापस ret;
	input_set_असल_params(aiptek->inputdev, ABS_Y, 0, ret - 1, 0, 0);

	/* Query getPressureLevels */
	अगर ((ret = aiptek_query(aiptek, 0x08, 0x00)) < 0)
		वापस ret;
	input_set_असल_params(aiptek->inputdev, ABS_PRESSURE, 0, ret - 1, 0, 0);

	/* Depending on whether we are in असलolute or relative mode, we will
	 * करो a चयनToTablet(असलolute) or चयनToMouse(relative) command.
	 */
	अगर (aiptek->curSetting.coordinateMode ==
	    AIPTEK_COORDINATE_ABSOLUTE_MODE) अणु
		/* Execute चयनToTablet */
		अगर ((ret = aiptek_command(aiptek, 0x10, 0x01)) < 0) अणु
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Execute चयनToMouse */
		अगर ((ret = aiptek_command(aiptek, 0x10, 0x00)) < 0) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable the macro keys */
	अगर ((ret = aiptek_command(aiptek, 0x11, 0x02)) < 0)
		वापस ret;
#अगर 0
	/* Execute FilterOn */
	अगर ((ret = aiptek_command(aiptek, 0x17, 0x00)) < 0)
		वापस ret;
#पूर्ण_अगर

	/* Execute AutoGainOn */
	अगर ((ret = aiptek_command(aiptek, 0x12, 0xff)) < 0)
		वापस ret;

	/* Reset the eventCount, so we track events from last (re)programming
	 */
	aiptek->diagnostic = AIPTEK_DIAGNOSTIC_NA;
	aiptek->eventCount = 0;

	वापस 0;
पूर्ण

/***********************************************************************
 * Sysfs functions. Sysfs prefers that inभागidually-tunable parameters
 * exist in their separate pseuकरो-files. Summary data that is immutable
 * may exist in a singular file so दीर्घ as you करोn't define a ग_लिखोable
 * पूर्णांकerface.
 */

/***********************************************************************
 * support the 'size' file -- display support
 */
अटल sमाप_प्रकार show_tabletSize(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%dx%d\n",
			  input_असल_get_max(aiptek->inputdev, ABS_X) + 1,
			  input_असल_get_max(aiptek->inputdev, ABS_Y) + 1);
पूर्ण

/* These काष्ठाs define the sysfs files, param #1 is the name of the
 * file, param 2 is the file permissions, param 3 & 4 are to the
 * output generator and input parser routines. Absence of a routine is
 * permitted -- it only means can't either 'cat' the file, or send data
 * to it.
 */
अटल DEVICE_ATTR(size, S_IRUGO, show_tabletSize, शून्य);

/***********************************************************************
 * support routines क्रम the 'pointer_mode' file. Note that this file
 * both displays current setting and allows reprogramming.
 */
अटल काष्ठा aiptek_map poपूर्णांकer_mode_map[] = अणु
	अणु "stylus",	AIPTEK_POINTER_ONLY_STYLUS_MODE पूर्ण,
	अणु "mouse",	AIPTEK_POINTER_ONLY_MOUSE_MODE पूर्ण,
	अणु "either",	AIPTEK_POINTER_EITHER_MODE पूर्ण,
	अणु शून्य,		AIPTEK_INVALID_VALUE पूर्ण
पूर्ण;

अटल sमाप_प्रकार show_tabletPoपूर्णांकerMode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(poपूर्णांकer_mode_map,
						      aiptek->curSetting.poपूर्णांकerMode));
पूर्ण

अटल sमाप_प्रकार
store_tabletPoपूर्णांकerMode(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_mode = map_str_to_val(poपूर्णांकer_mode_map, buf, count);

	अगर (new_mode == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.poपूर्णांकerMode = new_mode;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(poपूर्णांकer_mode,
		   S_IRUGO | S_IWUSR,
		   show_tabletPoपूर्णांकerMode, store_tabletPoपूर्णांकerMode);

/***********************************************************************
 * support routines क्रम the 'coordinate_mode' file. Note that this file
 * both displays current setting and allows reprogramming.
 */

अटल काष्ठा aiptek_map coordinate_mode_map[] = अणु
	अणु "absolute",	AIPTEK_COORDINATE_ABSOLUTE_MODE पूर्ण,
	अणु "relative",	AIPTEK_COORDINATE_RELATIVE_MODE पूर्ण,
	अणु शून्य,		AIPTEK_INVALID_VALUE पूर्ण
पूर्ण;

अटल sमाप_प्रकार show_tabletCoordinateMode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(coordinate_mode_map,
						      aiptek->curSetting.coordinateMode));
पूर्ण

अटल sमाप_प्रकार
store_tabletCoordinateMode(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_mode = map_str_to_val(coordinate_mode_map, buf, count);

	अगर (new_mode == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.coordinateMode = new_mode;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(coordinate_mode,
		   S_IRUGO | S_IWUSR,
		   show_tabletCoordinateMode, store_tabletCoordinateMode);

/***********************************************************************
 * support routines क्रम the 'tool_mode' file. Note that this file
 * both displays current setting and allows reprogramming.
 */

अटल काष्ठा aiptek_map tool_mode_map[] = अणु
	अणु "mouse",	AIPTEK_TOOL_BUTTON_MOUSE_MODE पूर्ण,
	अणु "eraser",	AIPTEK_TOOL_BUTTON_ERASER_MODE पूर्ण,
	अणु "pencil",	AIPTEK_TOOL_BUTTON_PENCIL_MODE पूर्ण,
	अणु "pen",	AIPTEK_TOOL_BUTTON_PEN_MODE पूर्ण,
	अणु "brush",	AIPTEK_TOOL_BUTTON_BRUSH_MODE पूर्ण,
	अणु "airbrush",	AIPTEK_TOOL_BUTTON_AIRBRUSH_MODE पूर्ण,
	अणु "lens",	AIPTEK_TOOL_BUTTON_LENS_MODE पूर्ण,
	अणु शून्य,		AIPTEK_INVALID_VALUE पूर्ण
पूर्ण;

अटल sमाप_प्रकार show_tabletToolMode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(tool_mode_map,
						      aiptek->curSetting.toolMode));
पूर्ण

अटल sमाप_प्रकार
store_tabletToolMode(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_mode = map_str_to_val(tool_mode_map, buf, count);

	अगर (new_mode == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.toolMode = new_mode;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(tool_mode,
		   S_IRUGO | S_IWUSR,
		   show_tabletToolMode, store_tabletToolMode);

/***********************************************************************
 * support routines क्रम the 'xtilt' file. Note that this file
 * both displays current setting and allows reprogramming.
 */
अटल sमाप_प्रकार show_tabletXtilt(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	अगर (aiptek->curSetting.xTilt == AIPTEK_TILT_DISABLE) अणु
		वापस sysfs_emit(buf, "disable\n");
	पूर्ण अन्यथा अणु
		वापस sysfs_emit(buf, "%d\n", aiptek->curSetting.xTilt);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
store_tabletXtilt(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक x;

	अगर (kstrtoपूर्णांक(buf, 10, &x)) अणु
		माप_प्रकार len = buf[count - 1] == '\n' ? count - 1 : count;

		अगर (म_भेदन(buf, "disable", len))
			वापस -EINVAL;

		aiptek->newSetting.xTilt = AIPTEK_TILT_DISABLE;
	पूर्ण अन्यथा अणु
		अगर (x < AIPTEK_TILT_MIN || x > AIPTEK_TILT_MAX)
			वापस -EINVAL;

		aiptek->newSetting.xTilt = x;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(xtilt,
		   S_IRUGO | S_IWUSR, show_tabletXtilt, store_tabletXtilt);

/***********************************************************************
 * support routines क्रम the 'ytilt' file. Note that this file
 * both displays current setting and allows reprogramming.
 */
अटल sमाप_प्रकार show_tabletYtilt(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	अगर (aiptek->curSetting.yTilt == AIPTEK_TILT_DISABLE) अणु
		वापस sysfs_emit(buf, "disable\n");
	पूर्ण अन्यथा अणु
		वापस sysfs_emit(buf, "%d\n", aiptek->curSetting.yTilt);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
store_tabletYtilt(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक y;

	अगर (kstrtoपूर्णांक(buf, 10, &y)) अणु
		माप_प्रकार len = buf[count - 1] == '\n' ? count - 1 : count;

		अगर (म_भेदन(buf, "disable", len))
			वापस -EINVAL;

		aiptek->newSetting.yTilt = AIPTEK_TILT_DISABLE;
	पूर्ण अन्यथा अणु
		अगर (y < AIPTEK_TILT_MIN || y > AIPTEK_TILT_MAX)
			वापस -EINVAL;

		aiptek->newSetting.yTilt = y;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(ytilt,
		   S_IRUGO | S_IWUSR, show_tabletYtilt, store_tabletYtilt);

/***********************************************************************
 * support routines क्रम the 'jitter' file. Note that this file
 * both displays current setting and allows reprogramming.
 */
अटल sमाप_प्रकार show_tabletJitterDelay(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", aiptek->curSetting.jitterDelay);
पूर्ण

अटल sमाप_प्रकार
store_tabletJitterDelay(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक err, j;

	err = kstrtoपूर्णांक(buf, 10, &j);
	अगर (err)
		वापस err;

	aiptek->newSetting.jitterDelay = j;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(jitter,
		   S_IRUGO | S_IWUSR,
		   show_tabletJitterDelay, store_tabletJitterDelay);

/***********************************************************************
 * support routines क्रम the 'delay' file. Note that this file
 * both displays current setting and allows reprogramming.
 */
अटल sमाप_प्रकार show_tabletProgrammableDelay(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", aiptek->curSetting.programmableDelay);
पूर्ण

अटल sमाप_प्रकार
store_tabletProgrammableDelay(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक err, d;

	err = kstrtoपूर्णांक(buf, 10, &d);
	अगर (err)
		वापस err;

	aiptek->newSetting.programmableDelay = d;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(delay,
		   S_IRUGO | S_IWUSR,
		   show_tabletProgrammableDelay, store_tabletProgrammableDelay);

/***********************************************************************
 * support routines क्रम the 'event_count' file. Note that this file
 * only displays current setting.
 */
अटल sमाप_प्रकार show_tabletEventsReceived(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%ld\n", aiptek->eventCount);
पूर्ण

अटल DEVICE_ATTR(event_count, S_IRUGO, show_tabletEventsReceived, शून्य);

/***********************************************************************
 * support routines क्रम the 'diagnostic' file. Note that this file
 * only displays current setting.
 */
अटल sमाप_प्रकार show_tabletDiagnosticMessage(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	अक्षर *retMsg;

	चयन (aiptek->diagnostic) अणु
	हाल AIPTEK_DIAGNOSTIC_NA:
		retMsg = "no errors\n";
		अवरोध;

	हाल AIPTEK_DIAGNOSTIC_SENDING_RELATIVE_IN_ABSOLUTE:
		retMsg = "Error: receiving relative reports\n";
		अवरोध;

	हाल AIPTEK_DIAGNOSTIC_SENDING_ABSOLUTE_IN_RELATIVE:
		retMsg = "Error: receiving absolute reports\n";
		अवरोध;

	हाल AIPTEK_DIAGNOSTIC_TOOL_DISALLOWED:
		अगर (aiptek->curSetting.poपूर्णांकerMode ==
		    AIPTEK_POINTER_ONLY_MOUSE_MODE) अणु
			retMsg = "Error: receiving stylus reports\n";
		पूर्ण अन्यथा अणु
			retMsg = "Error: receiving mouse reports\n";
		पूर्ण
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण
	वापस sysfs_emit(buf, retMsg);
पूर्ण

अटल DEVICE_ATTR(diagnostic, S_IRUGO, show_tabletDiagnosticMessage, शून्य);

/***********************************************************************
 * support routines क्रम the 'stylus_upper' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */

अटल काष्ठा aiptek_map stylus_button_map[] = अणु
	अणु "upper",	AIPTEK_STYLUS_UPPER_BUTTON पूर्ण,
	अणु "lower",	AIPTEK_STYLUS_LOWER_BUTTON पूर्ण,
	अणु शून्य,		AIPTEK_INVALID_VALUE पूर्ण
पूर्ण;

अटल sमाप_प्रकार show_tabletStylusUpper(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(stylus_button_map,
						      aiptek->curSetting.stylusButtonUpper));
पूर्ण

अटल sमाप_प्रकार
store_tabletStylusUpper(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_button = map_str_to_val(stylus_button_map, buf, count);

	अगर (new_button == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.stylusButtonUpper = new_button;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(stylus_upper,
		   S_IRUGO | S_IWUSR,
		   show_tabletStylusUpper, store_tabletStylusUpper);

/***********************************************************************
 * support routines क्रम the 'stylus_lower' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */

अटल sमाप_प्रकार show_tabletStylusLower(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(stylus_button_map,
						      aiptek->curSetting.stylusButtonLower));
पूर्ण

अटल sमाप_प्रकार
store_tabletStylusLower(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_button = map_str_to_val(stylus_button_map, buf, count);

	अगर (new_button == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.stylusButtonLower = new_button;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(stylus_lower,
		   S_IRUGO | S_IWUSR,
		   show_tabletStylusLower, store_tabletStylusLower);

/***********************************************************************
 * support routines क्रम the 'mouse_left' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */

अटल काष्ठा aiptek_map mouse_button_map[] = अणु
	अणु "left",	AIPTEK_MOUSE_LEFT_BUTTON पूर्ण,
	अणु "middle",	AIPTEK_MOUSE_MIDDLE_BUTTON पूर्ण,
	अणु "right",	AIPTEK_MOUSE_RIGHT_BUTTON पूर्ण,
	अणु शून्य,		AIPTEK_INVALID_VALUE पूर्ण
पूर्ण;

अटल sमाप_प्रकार show_tabletMouseLeft(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(mouse_button_map,
						      aiptek->curSetting.mouseButtonLeft));
पूर्ण

अटल sमाप_प्रकार
store_tabletMouseLeft(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_button = map_str_to_val(mouse_button_map, buf, count);

	अगर (new_button == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.mouseButtonLeft = new_button;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(mouse_left,
		   S_IRUGO | S_IWUSR,
		   show_tabletMouseLeft, store_tabletMouseLeft);

/***********************************************************************
 * support routines क्रम the 'mouse_middle' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */
अटल sमाप_प्रकार show_tabletMouseMiddle(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(mouse_button_map,
						      aiptek->curSetting.mouseButtonMiddle));
पूर्ण

अटल sमाप_प्रकार
store_tabletMouseMiddle(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_button = map_str_to_val(mouse_button_map, buf, count);

	अगर (new_button == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.mouseButtonMiddle = new_button;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(mouse_middle,
		   S_IRUGO | S_IWUSR,
		   show_tabletMouseMiddle, store_tabletMouseMiddle);

/***********************************************************************
 * support routines क्रम the 'mouse_right' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */
अटल sमाप_प्रकार show_tabletMouseRight(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", map_val_to_str(mouse_button_map,
						      aiptek->curSetting.mouseButtonRight));
पूर्ण

अटल sमाप_प्रकार
store_tabletMouseRight(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक new_button = map_str_to_val(mouse_button_map, buf, count);

	अगर (new_button == AIPTEK_INVALID_VALUE)
		वापस -EINVAL;

	aiptek->newSetting.mouseButtonRight = new_button;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(mouse_right,
		   S_IRUGO | S_IWUSR,
		   show_tabletMouseRight, store_tabletMouseRight);

/***********************************************************************
 * support routines क्रम the 'wheel' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */
अटल sमाप_प्रकार show_tabletWheel(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	अगर (aiptek->curSetting.wheel == AIPTEK_WHEEL_DISABLE) अणु
		वापस sysfs_emit(buf, "disable\n");
	पूर्ण अन्यथा अणु
		वापस sysfs_emit(buf, "%d\n", aiptek->curSetting.wheel);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
store_tabletWheel(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);
	पूर्णांक err, w;

	err = kstrtoपूर्णांक(buf, 10, &w);
	अगर (err)
		वापस err;

	aiptek->newSetting.wheel = w;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(wheel,
		   S_IRUGO | S_IWUSR, show_tabletWheel, store_tabletWheel);

/***********************************************************************
 * support routines क्रम the 'execute' file. Note that this file
 * both displays current setting and allows क्रम setting changing.
 */
अटल sमाप_प्रकार show_tabletExecute(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	/* There is nothing useful to display, so a one-line manual
	 * is in order...
	 */
	वापस sysfs_emit(buf, "Write anything to this file to program your tablet.\n");
पूर्ण

अटल sमाप_प्रकार
store_tabletExecute(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	/* We करो not care what you ग_लिखो to this file. Merely the action
	 * of writing to this file triggers a tablet reprogramming.
	 */
	स_नकल(&aiptek->curSetting, &aiptek->newSetting,
	       माप(काष्ठा aiptek_settings));

	अगर (aiptek_program_tablet(aiptek) < 0)
		वापस -EIO;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(execute,
		   S_IRUGO | S_IWUSR, show_tabletExecute, store_tabletExecute);

/***********************************************************************
 * support routines क्रम the 'odm_code' file. Note that this file
 * only displays current setting.
 */
अटल sमाप_प्रकार show_tabletODMCode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "0x%04x\n", aiptek->features.odmCode);
पूर्ण

अटल DEVICE_ATTR(odm_code, S_IRUGO, show_tabletODMCode, शून्य);

/***********************************************************************
 * support routines क्रम the 'model_code' file. Note that this file
 * only displays current setting.
 */
अटल sमाप_प्रकार show_tabletModelCode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "0x%04x\n", aiptek->features.modelCode);
पूर्ण

अटल DEVICE_ATTR(model_code, S_IRUGO, show_tabletModelCode, शून्य);

/***********************************************************************
 * support routines क्रम the 'firmware_code' file. Note that this file
 * only displays current setting.
 */
अटल sमाप_प्रकार show_firmwareCode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aiptek *aiptek = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%04x\n", aiptek->features.firmwareCode);
पूर्ण

अटल DEVICE_ATTR(firmware_code, S_IRUGO, show_firmwareCode, शून्य);

अटल काष्ठा attribute *aiptek_attributes[] = अणु
	&dev_attr_size.attr,
	&dev_attr_poपूर्णांकer_mode.attr,
	&dev_attr_coordinate_mode.attr,
	&dev_attr_tool_mode.attr,
	&dev_attr_xtilt.attr,
	&dev_attr_ytilt.attr,
	&dev_attr_jitter.attr,
	&dev_attr_delay.attr,
	&dev_attr_event_count.attr,
	&dev_attr_diagnostic.attr,
	&dev_attr_odm_code.attr,
	&dev_attr_model_code.attr,
	&dev_attr_firmware_code.attr,
	&dev_attr_stylus_lower.attr,
	&dev_attr_stylus_upper.attr,
	&dev_attr_mouse_left.attr,
	&dev_attr_mouse_middle.attr,
	&dev_attr_mouse_right.attr,
	&dev_attr_wheel.attr,
	&dev_attr_execute.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group aiptek_attribute_group = अणु
	.attrs	= aiptek_attributes,
पूर्ण;

/***********************************************************************
 * This routine is called when a tablet has been identअगरied. It basically
 * sets up the tablet and the driver's पूर्णांकernal काष्ठाures.
 */
अटल पूर्णांक
aiptek_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा aiptek *aiptek;
	काष्ठा input_dev *inputdev;
	पूर्णांक i;
	पूर्णांक speeds[] = अणु 0,
		AIPTEK_PROGRAMMABLE_DELAY_50,
		AIPTEK_PROGRAMMABLE_DELAY_400,
		AIPTEK_PROGRAMMABLE_DELAY_25,
		AIPTEK_PROGRAMMABLE_DELAY_100,
		AIPTEK_PROGRAMMABLE_DELAY_200,
		AIPTEK_PROGRAMMABLE_DELAY_300
	पूर्ण;
	पूर्णांक err = -ENOMEM;

	/* programmableDelay is where the command-line specअगरied
	 * delay is kept. We make it the first element of speeds[],
	 * so thereक्रमe, your override speed is tried first, then the
	 * reमुख्यder. Note that the शेष value of 400ms will be tried
	 * अगर you करो not specअगरy any command line parameter.
	 */
	speeds[0] = programmableDelay;

	aiptek = kzalloc(माप(काष्ठा aiptek), GFP_KERNEL);
	inputdev = input_allocate_device();
	अगर (!aiptek || !inputdev) अणु
		dev_warn(&पूर्णांकf->dev,
			 "cannot allocate memory or input device\n");
		जाओ fail1;
        पूर्ण

	aiptek->data = usb_alloc_coherent(usbdev, AIPTEK_PACKET_LENGTH,
					  GFP_KERNEL, &aiptek->data_dma);
        अगर (!aiptek->data) अणु
		dev_warn(&पूर्णांकf->dev, "cannot allocate usb buffer\n");
		जाओ fail1;
	पूर्ण

	aiptek->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!aiptek->urb) अणु
	        dev_warn(&पूर्णांकf->dev, "cannot allocate urb\n");
		जाओ fail2;
	पूर्ण

	aiptek->inputdev = inputdev;
	aiptek->पूर्णांकf = पूर्णांकf;
	aiptek->अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	aiptek->inDelay = 0;
	aiptek->endDelay = 0;
	aiptek->previousJitterable = 0;
	aiptek->lastMacro = -1;

	/* Set up the curSettings काष्ठा. Said काष्ठा contains the current
	 * programmable parameters. The newSetting काष्ठा contains changes
	 * the user makes to the settings via the sysfs पूर्णांकerface. Those
	 * changes are not "committed" to curSettings until the user
	 * ग_लिखोs to the sysfs/.../execute file.
	 */
	aiptek->curSetting.poपूर्णांकerMode = AIPTEK_POINTER_EITHER_MODE;
	aiptek->curSetting.coordinateMode = AIPTEK_COORDINATE_ABSOLUTE_MODE;
	aiptek->curSetting.toolMode = AIPTEK_TOOL_BUTTON_PEN_MODE;
	aiptek->curSetting.xTilt = AIPTEK_TILT_DISABLE;
	aiptek->curSetting.yTilt = AIPTEK_TILT_DISABLE;
	aiptek->curSetting.mouseButtonLeft = AIPTEK_MOUSE_LEFT_BUTTON;
	aiptek->curSetting.mouseButtonMiddle = AIPTEK_MOUSE_MIDDLE_BUTTON;
	aiptek->curSetting.mouseButtonRight = AIPTEK_MOUSE_RIGHT_BUTTON;
	aiptek->curSetting.stylusButtonUpper = AIPTEK_STYLUS_UPPER_BUTTON;
	aiptek->curSetting.stylusButtonLower = AIPTEK_STYLUS_LOWER_BUTTON;
	aiptek->curSetting.jitterDelay = jitterDelay;
	aiptek->curSetting.programmableDelay = programmableDelay;

	/* Both काष्ठाs should have equivalent settings
	 */
	aiptek->newSetting = aiptek->curSetting;

	/* Determine the usb devices' physical path.
	 * Asketh not why we always pretend we're using "../input0",
	 * but I suspect this will have to be refactored one
	 * day अगर a single USB device can be a keyboard & a mouse
	 * & a tablet, and the inputX number actually will tell
	 * us something...
	 */
	usb_make_path(usbdev, aiptek->features.usbPath,
			माप(aiptek->features.usbPath));
	strlcat(aiptek->features.usbPath, "/input0",
		माप(aiptek->features.usbPath));

	/* Set up client data, poपूर्णांकers to खोलो and बंद routines
	 * क्रम the input device.
	 */
	inputdev->name = "Aiptek";
	inputdev->phys = aiptek->features.usbPath;
	usb_to_input_id(usbdev, &inputdev->id);
	inputdev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(inputdev, aiptek);

	inputdev->खोलो = aiptek_खोलो;
	inputdev->बंद = aiptek_बंद;

	/* Now program the capacities of the tablet, in terms of being
	 * an input device.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(eventTypes); ++i)
	        __set_bit(eventTypes[i], inputdev->evbit);

	क्रम (i = 0; i < ARRAY_SIZE(असलEvents); ++i)
	        __set_bit(असलEvents[i], inputdev->असलbit);

	क्रम (i = 0; i < ARRAY_SIZE(relEvents); ++i)
	        __set_bit(relEvents[i], inputdev->relbit);

	__set_bit(MSC_SERIAL, inputdev->mscbit);

	/* Set up key and button codes */
	क्रम (i = 0; i < ARRAY_SIZE(buttonEvents); ++i)
		__set_bit(buttonEvents[i], inputdev->keybit);

	क्रम (i = 0; i < ARRAY_SIZE(macroKeyEvents); ++i)
		__set_bit(macroKeyEvents[i], inputdev->keybit);

	/*
	 * Program the input device coordinate capacities. We करो not yet
	 * know what maximum X, Y, and Z values are, so we're putting fake
	 * values in. Later, we'll ask the tablet to put in the correct
	 * values.
	 */
	input_set_असल_params(inputdev, ABS_X, 0, 2999, 0, 0);
	input_set_असल_params(inputdev, ABS_Y, 0, 2249, 0, 0);
	input_set_असल_params(inputdev, ABS_PRESSURE, 0, 511, 0, 0);
	input_set_असल_params(inputdev, ABS_TILT_X, AIPTEK_TILT_MIN, AIPTEK_TILT_MAX, 0, 0);
	input_set_असल_params(inputdev, ABS_TILT_Y, AIPTEK_TILT_MIN, AIPTEK_TILT_MAX, 0, 0);
	input_set_असल_params(inputdev, ABS_WHEEL, AIPTEK_WHEEL_MIN, AIPTEK_WHEEL_MAX - 1, 0, 0);

	/* Verअगरy that a device really has an endpoपूर्णांक */
	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1) अणु
		dev_err(&पूर्णांकf->dev,
			"interface has %d endpoints, but must have minimum 1\n",
			पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs);
		err = -EINVAL;
		जाओ fail3;
	पूर्ण
	endpoपूर्णांक = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc;

	/* Go set up our URB, which is called when the tablet receives
	 * input.
	 */
	usb_fill_पूर्णांक_urb(aiptek->urb,
			 usbdev,
			 usb_rcvपूर्णांकpipe(usbdev,
					endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 aiptek->data, 8, aiptek_irq, aiptek,
			 endpoपूर्णांक->bInterval);

	aiptek->urb->transfer_dma = aiptek->data_dma;
	aiptek->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* Program the tablet. This sets the tablet up in the mode
	 * specअगरied in newSetting, and also queries the tablet's
	 * physical capacities.
	 *
	 * Sanity check: अगर a tablet करोesn't like the slow programmatic
	 * delay, we often get sizes of 0x0. Let's use that as an indicator
	 * to try faster delays, up to 25 ms. If that logic fails, well, you'll
	 * have to explain to us how your tablet thinks it's 0x0, and yet that's
	 * not an error :-)
	 */

	क्रम (i = 0; i < ARRAY_SIZE(speeds); ++i) अणु
		aiptek->curSetting.programmableDelay = speeds[i];
		(व्योम)aiptek_program_tablet(aiptek);
		अगर (input_असल_get_max(aiptek->inputdev, ABS_X) > 0) अणु
			dev_info(&पूर्णांकf->dev,
				 "Aiptek using %d ms programming speed\n",
				 aiptek->curSetting.programmableDelay);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Murphy says that some day someone will have a tablet that fails the
	   above test. That's you, Frederic Rodrigo */
	अगर (i == ARRAY_SIZE(speeds)) अणु
		dev_info(&पूर्णांकf->dev,
			 "Aiptek tried all speeds, no sane response\n");
		err = -EINVAL;
		जाओ fail3;
	पूर्ण

	/* Associate this driver's काष्ठा with the usb पूर्णांकerface.
	 */
	usb_set_पूर्णांकfdata(पूर्णांकf, aiptek);

	/* Set up the sysfs files
	 */
	err = sysfs_create_group(&पूर्णांकf->dev.kobj, &aiptek_attribute_group);
	अगर (err) अणु
		dev_warn(&पूर्णांकf->dev, "cannot create sysfs group err: %d\n",
			 err);
		जाओ fail3;
        पूर्ण

	/* Register the tablet as an Input Device
	 */
	err = input_रेजिस्टर_device(aiptek->inputdev);
	अगर (err) अणु
		dev_warn(&पूर्णांकf->dev,
			 "input_register_device returned err: %d\n", err);
		जाओ fail4;
        पूर्ण
	वापस 0;

 fail4:	sysfs_हटाओ_group(&पूर्णांकf->dev.kobj, &aiptek_attribute_group);
 fail3: usb_मुक्त_urb(aiptek->urb);
 fail2:	usb_मुक्त_coherent(usbdev, AIPTEK_PACKET_LENGTH, aiptek->data,
			  aiptek->data_dma);
 fail1: usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	input_मुक्त_device(inputdev);
	kमुक्त(aiptek);
	वापस err;
पूर्ण

/***********************************************************************
 * Deal with tablet disconnecting from the प्रणाली.
 */
अटल व्योम aiptek_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा aiptek *aiptek = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* Disassociate driver's काष्ठा with usb पूर्णांकerface
	 */
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (aiptek != शून्य) अणु
		/* Free & unhook everything from the प्रणाली.
		 */
		usb_समाप्त_urb(aiptek->urb);
		input_unरेजिस्टर_device(aiptek->inputdev);
		sysfs_हटाओ_group(&पूर्णांकf->dev.kobj, &aiptek_attribute_group);
		usb_मुक्त_urb(aiptek->urb);
		usb_मुक्त_coherent(पूर्णांकerface_to_usbdev(पूर्णांकf),
				  AIPTEK_PACKET_LENGTH,
				  aiptek->data, aiptek->data_dma);
		kमुक्त(aiptek);
	पूर्ण
पूर्ण

अटल काष्ठा usb_driver aiptek_driver = अणु
	.name = "aiptek",
	.probe = aiptek_probe,
	.disconnect = aiptek_disconnect,
	.id_table = aiptek_ids,
पूर्ण;

module_usb_driver(aiptek_driver);

MODULE_AUTHOR("Bryan W. Headley/Chris Atenasio/Cedric Brun/Rene van Paassen");
MODULE_DESCRIPTION("Aiptek HyperPen USB Tablet Driver");
MODULE_LICENSE("GPL");

module_param(programmableDelay, पूर्णांक, 0);
MODULE_PARM_DESC(programmableDelay, "delay used during tablet programming");
module_param(jitterDelay, पूर्णांक, 0);
MODULE_PARM_DESC(jitterDelay, "stylus/mouse settlement delay");
