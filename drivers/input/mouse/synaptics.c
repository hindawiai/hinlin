<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synaptics TouchPad PS/2 mouse driver
 *
 *   2003 Dmitry Torokhov <dtor@mail.ru>
 *     Added support क्रम pass-through port. Special thanks to Peter Berg Larsen
 *     क्रम explaining various Synaptics quirks.
 *
 *   2003 Peter Osterlund <petero2@telia.com>
 *     Ported to 2.5 input device infraकाष्ठाure.
 *
 *   Copyright (C) 2001 Stefan Gmeiner <riddlebox@मुक्तsurf.ch>
 *     start merging tpconfig and gpm code to a xमुक्त-input module
 *     adding some changes and extensions (ex. 3rd and 4th button)
 *
 *   Copyright (c) 1997 C. Scott Ananian <cananian@alumni.priceton.edu>
 *   Copyright (c) 1998-2000 Bruce Kalk <kall@compass.com>
 *     code क्रम the special synaptics commands (from the tpconfig-source)
 *
 * Trademarks are the property of their respective owners.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/rmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश "psmouse.h"
#समावेश "synaptics.h"

/*
 * The x/y limits are taken from the Synaptics TouchPad पूर्णांकerfacing Guide,
 * section 2.3.2, which says that they should be valid regardless of the
 * actual size of the sensor.
 * Note that newer firmware allows querying device क्रम maximum useable
 * coordinates.
 */
#घोषणा XMIN 0
#घोषणा XMAX 6143
#घोषणा YMIN 0
#घोषणा YMAX 6143
#घोषणा XMIN_NOMINAL 1472
#घोषणा XMAX_NOMINAL 5472
#घोषणा YMIN_NOMINAL 1408
#घोषणा YMAX_NOMINAL 4448

/* Size in bits of असलolute position values reported by the hardware */
#घोषणा ABS_POS_BITS 13

/*
 * These values should represent the असलolute maximum value that will
 * be reported क्रम a positive position value. Some Synaptics firmware
 * uses this value to indicate a finger near the edge of the touchpad
 * whose precise position cannot be determined.
 *
 * At least one touchpad is known to report positions in excess of this
 * value which are actually negative values truncated to the 13-bit
 * reporting range. These values have never been observed to be lower
 * than 8184 (i.e. -8), so we treat all values greater than 8176 as
 * negative and any other value as positive.
 */
#घोषणा X_MAX_POSITIVE 8176
#घोषणा Y_MAX_POSITIVE 8176

/* maximum ABS_MT_POSITION displacement (in mm) */
#घोषणा DMAX 10

/*****************************************************************************
 *	Stuff we need even when we करो not want native Synaptics support
 ****************************************************************************/

/*
 * Set the synaptics touchpad mode byte by special commands
 */
अटल पूर्णांक synaptics_mode_cmd(काष्ठा psmouse *psmouse, u8 mode)
अणु
	u8 param[1];
	पूर्णांक error;

	error = ps2_sliced_command(&psmouse->ps2dev, mode);
	अगर (error)
		वापस error;

	param[0] = SYN_PS_SET_MODE2;
	error = ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_SETRATE);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

पूर्णांक synaptics_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4] = अणु 0 पूर्ण;

	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO);

	अगर (param[1] != 0x47)
		वापस -ENODEV;

	अगर (set_properties) अणु
		psmouse->venकरोr = "Synaptics";
		psmouse->name = "TouchPad";
	पूर्ण

	वापस 0;
पूर्ण

व्योम synaptics_reset(काष्ठा psmouse *psmouse)
अणु
	/* reset touchpad back to relative mode, gestures enabled */
	synaptics_mode_cmd(psmouse, 0);
पूर्ण

#अगर defined(CONFIG_MOUSE_PS2_SYNAPTICS) || \
    defined(CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS)

/* This list has been kindly provided by Synaptics. */
अटल स्थिर अक्षर * स्थिर topbuttonpad_pnp_ids[] = अणु
	"LEN0017",
	"LEN0018",
	"LEN0019",
	"LEN0023",
	"LEN002A",
	"LEN002B",
	"LEN002C",
	"LEN002D",
	"LEN002E",
	"LEN0033", /* Helix */
	"LEN0034", /* T431s, L440, L540, T540, W540, X1 Carbon 2nd */
	"LEN0035", /* X240 */
	"LEN0036", /* T440 */
	"LEN0037", /* X1 Carbon 2nd */
	"LEN0038",
	"LEN0039", /* T440s */
	"LEN0041",
	"LEN0042", /* Yoga */
	"LEN0045",
	"LEN0047",
	"LEN2000", /* S540 */
	"LEN2001", /* Edge E431 */
	"LEN2002", /* Edge E531 */
	"LEN2003",
	"LEN2004", /* L440 */
	"LEN2005",
	"LEN2006", /* Edge E440/E540 */
	"LEN2007",
	"LEN2008",
	"LEN2009",
	"LEN200A",
	"LEN200B",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर smbus_pnp_ids[] = अणु
	/* all of the topbuttonpad_pnp_ids are valid, we just add some extras */
	"LEN0048", /* X1 Carbon 3 */
	"LEN0046", /* X250 */
	"LEN0049", /* Yoga 11e */
	"LEN004a", /* W541 */
	"LEN005b", /* P50 */
	"LEN005e", /* T560 */
	"LEN006c", /* T470s */
	"LEN007a", /* T470s */
	"LEN0071", /* T480 */
	"LEN0072", /* X1 Carbon Gen 5 (2017) - Elan/ALPS trackpoपूर्णांक */
	"LEN0073", /* X1 Carbon G5 (Elantech) */
	"LEN0091", /* X1 Carbon 6 */
	"LEN0092", /* X1 Carbon 6 */
	"LEN0093", /* T480 */
	"LEN0096", /* X280 */
	"LEN0097", /* X280 -> ALPS trackpoपूर्णांक */
	"LEN0099", /* X1 Extreme Gen 1 / P1 Gen 1 */
	"LEN009b", /* T580 */
	"LEN0402", /* X1 Extreme Gen 2 / P1 Gen 2 */
	"LEN200f", /* T450s */
	"LEN2044", /* L470  */
	"LEN2054", /* E480 */
	"LEN2055", /* E580 */
	"LEN2068", /* T14 Gen 1 */
	"SYN3052", /* HP EliteBook 840 G4 */
	"SYN3221", /* HP 15-ay000 */
	"SYN323d", /* HP Spectre X360 13-w013dx */
	"SYN3257", /* HP Envy 13-ad105ng */
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर क्रमcepad_pnp_ids[] = अणु
	"SYN300D",
	"SYN3014",
	शून्य
पूर्ण;

/*
 * Send a command to the synaptics touchpad by special commands
 */
अटल पूर्णांक synaptics_send_cmd(काष्ठा psmouse *psmouse, u8 cmd, u8 *param)
अणु
	पूर्णांक error;

	error = ps2_sliced_command(&psmouse->ps2dev, cmd);
	अगर (error)
		वापस error;

	error = ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETINFO);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक synaptics_query_पूर्णांक(काष्ठा psmouse *psmouse, u8 query_cmd, u32 *val)
अणु
	पूर्णांक error;
	जोड़ अणु
		__be32 be_val;
		अक्षर buf[4];
	पूर्ण resp = अणु 0 पूर्ण;

	error = synaptics_send_cmd(psmouse, query_cmd, resp.buf + 1);
	अगर (error)
		वापस error;

	*val = be32_to_cpu(resp.be_val);
	वापस 0;
पूर्ण

/*
 * Identअगरy Touchpad
 * See also the SYN_ID_* macros
 */
अटल पूर्णांक synaptics_identअगरy(काष्ठा psmouse *psmouse,
			      काष्ठा synaptics_device_info *info)
अणु
	पूर्णांक error;

	error = synaptics_query_पूर्णांक(psmouse, SYN_QUE_IDENTIFY, &info->identity);
	अगर (error)
		वापस error;

	वापस SYN_ID_IS_SYNAPTICS(info->identity) ? 0 : -ENXIO;
पूर्ण

/*
 * Read the model-id bytes from the touchpad
 * see also SYN_MODEL_* macros
 */
अटल पूर्णांक synaptics_model_id(काष्ठा psmouse *psmouse,
			      काष्ठा synaptics_device_info *info)
अणु
	वापस synaptics_query_पूर्णांक(psmouse, SYN_QUE_MODEL, &info->model_id);
पूर्ण

/*
 * Read the firmware id from the touchpad
 */
अटल पूर्णांक synaptics_firmware_id(काष्ठा psmouse *psmouse,
				 काष्ठा synaptics_device_info *info)
अणु
	वापस synaptics_query_पूर्णांक(psmouse, SYN_QUE_FIRMWARE_ID,
				   &info->firmware_id);
पूर्ण

/*
 * Read the board id and the "More Extended Queries" from the touchpad
 * The board id is encoded in the "QUERY MODES" response
 */
अटल पूर्णांक synaptics_query_modes(काष्ठा psmouse *psmouse,
				 काष्ठा synaptics_device_info *info)
अणु
	u8 bid[3];
	पूर्णांक error;

	/* firmwares prior 7.5 have no board_id encoded */
	अगर (SYN_ID_FULL(info->identity) < 0x705)
		वापस 0;

	error = synaptics_send_cmd(psmouse, SYN_QUE_MODES, bid);
	अगर (error)
		वापस error;

	info->board_id = ((bid[0] & 0xfc) << 6) | bid[1];

	अगर (SYN_MEXT_CAP_BIT(bid[0]))
		वापस synaptics_query_पूर्णांक(psmouse, SYN_QUE_MEXT_CAPAB_10,
					   &info->ext_cap_10);

	वापस 0;
पूर्ण

/*
 * Read the capability-bits from the touchpad
 * see also the SYN_CAP_* macros
 */
अटल पूर्णांक synaptics_capability(काष्ठा psmouse *psmouse,
				काष्ठा synaptics_device_info *info)
अणु
	पूर्णांक error;

	error = synaptics_query_पूर्णांक(psmouse, SYN_QUE_CAPABILITIES,
				    &info->capabilities);
	अगर (error)
		वापस error;

	info->ext_cap = info->ext_cap_0c = 0;

	/*
	 * Older firmwares had submodel ID fixed to 0x47
	 */
	अगर (SYN_ID_FULL(info->identity) < 0x705 &&
	    SYN_CAP_SUBMODEL_ID(info->capabilities) != 0x47) अणु
		वापस -ENXIO;
	पूर्ण

	/*
	 * Unless capExtended is set the rest of the flags should be ignored
	 */
	अगर (!SYN_CAP_EXTENDED(info->capabilities))
		info->capabilities = 0;

	अगर (SYN_EXT_CAP_REQUESTS(info->capabilities) >= 1) अणु
		error = synaptics_query_पूर्णांक(psmouse, SYN_QUE_EXT_CAPAB,
					    &info->ext_cap);
		अगर (error) अणु
			psmouse_warn(psmouse,
				     "device claims to have extended capabilities, but I'm not able to read them.\n");
		पूर्ण अन्यथा अणु
			/*
			 * अगर nExtBtn is greater than 8 it should be considered
			 * invalid and treated as 0
			 */
			अगर (SYN_CAP_MULTI_BUTTON_NO(info->ext_cap) > 8)
				info->ext_cap &= ~SYN_CAP_MB_MASK;
		पूर्ण
	पूर्ण

	अगर (SYN_EXT_CAP_REQUESTS(info->capabilities) >= 4) अणु
		error = synaptics_query_पूर्णांक(psmouse, SYN_QUE_EXT_CAPAB_0C,
					    &info->ext_cap_0c);
		अगर (error)
			psmouse_warn(psmouse,
				     "device claims to have extended capability 0x0c, but I'm not able to read it.\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read touchpad resolution and maximum reported coordinates
 * Resolution is left zero अगर touchpad करोes not support the query
 */
अटल पूर्णांक synaptics_resolution(काष्ठा psmouse *psmouse,
				काष्ठा synaptics_device_info *info)
अणु
	u8 resp[3];
	पूर्णांक error;

	अगर (SYN_ID_MAJOR(info->identity) < 4)
		वापस 0;

	error = synaptics_send_cmd(psmouse, SYN_QUE_RESOLUTION, resp);
	अगर (!error) अणु
		अगर (resp[0] != 0 && (resp[1] & 0x80) && resp[2] != 0) अणु
			info->x_res = resp[0]; /* x resolution in units/mm */
			info->y_res = resp[2]; /* y resolution in units/mm */
		पूर्ण
	पूर्ण

	अगर (SYN_EXT_CAP_REQUESTS(info->capabilities) >= 5 &&
	    SYN_CAP_MAX_DIMENSIONS(info->ext_cap_0c)) अणु
		error = synaptics_send_cmd(psmouse,
					   SYN_QUE_EXT_MAX_COORDS, resp);
		अगर (error) अणु
			psmouse_warn(psmouse,
				     "device claims to have max coordinates query, but I'm not able to read it.\n");
		पूर्ण अन्यथा अणु
			info->x_max = (resp[0] << 5) | ((resp[1] & 0x0f) << 1);
			info->y_max = (resp[2] << 5) | ((resp[1] & 0xf0) >> 3);
			psmouse_info(psmouse,
				     "queried max coordinates: x [..%d], y [..%d]\n",
				     info->x_max, info->y_max);
		पूर्ण
	पूर्ण

	अगर (SYN_CAP_MIN_DIMENSIONS(info->ext_cap_0c) &&
	    (SYN_EXT_CAP_REQUESTS(info->capabilities) >= 7 ||
	     /*
	      * Firmware v8.1 करोes not report proper number of extended
	      * capabilities, but has been proven to report correct min
	      * coordinates.
	      */
	     SYN_ID_FULL(info->identity) == 0x801)) अणु
		error = synaptics_send_cmd(psmouse,
					   SYN_QUE_EXT_MIN_COORDS, resp);
		अगर (error) अणु
			psmouse_warn(psmouse,
				     "device claims to have min coordinates query, but I'm not able to read it.\n");
		पूर्ण अन्यथा अणु
			info->x_min = (resp[0] << 5) | ((resp[1] & 0x0f) << 1);
			info->y_min = (resp[2] << 5) | ((resp[1] & 0xf0) >> 3);
			psmouse_info(psmouse,
				     "queried min coordinates: x [%d..], y [%d..]\n",
				     info->x_min, info->y_min);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक synaptics_query_hardware(काष्ठा psmouse *psmouse,
				    काष्ठा synaptics_device_info *info)
अणु
	पूर्णांक error;

	स_रखो(info, 0, माप(*info));

	error = synaptics_identअगरy(psmouse, info);
	अगर (error)
		वापस error;

	error = synaptics_model_id(psmouse, info);
	अगर (error)
		वापस error;

	error = synaptics_firmware_id(psmouse, info);
	अगर (error)
		वापस error;

	error = synaptics_query_modes(psmouse, info);
	अगर (error)
		वापस error;

	error = synaptics_capability(psmouse, info);
	अगर (error)
		वापस error;

	error = synaptics_resolution(psmouse, info);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_SYNAPTICS || CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS */

#अगर_घोषित CONFIG_MOUSE_PS2_SYNAPTICS

अटल bool cr48_profile_sensor;

#घोषणा ANY_BOARD_ID 0
काष्ठा min_max_quirk अणु
	स्थिर अक्षर * स्थिर *pnp_ids;
	काष्ठा अणु
		u32 min, max;
	पूर्ण board_id;
	u32 x_min, x_max, y_min, y_max;
पूर्ण;

अटल स्थिर काष्ठा min_max_quirk min_max_pnpid_table[] = अणु
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN0033", शून्यपूर्ण,
		अणुANY_BOARD_ID, ANY_BOARD_IDपूर्ण,
		1024, 5052, 2258, 4832
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN0042", शून्यपूर्ण,
		अणुANY_BOARD_ID, ANY_BOARD_IDपूर्ण,
		1232, 5710, 1156, 4696
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN0034", "LEN0036", "LEN0037",
					"LEN0039", "LEN2002", "LEN2004",
					शून्यपूर्ण,
		अणुANY_BOARD_ID, 2961पूर्ण,
		1024, 5112, 2024, 4832
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN2000", शून्यपूर्ण,
		अणुANY_BOARD_ID, ANY_BOARD_IDपूर्ण,
		1024, 5113, 2021, 4832
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN2001", शून्यपूर्ण,
		अणुANY_BOARD_ID, ANY_BOARD_IDपूर्ण,
		1024, 5022, 2508, 4832
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN2006", शून्यपूर्ण,
		अणु2691, 2691पूर्ण,
		1024, 5045, 2457, 4832
	पूर्ण,
	अणु
		(स्थिर अक्षर * स्थिर [])अणु"LEN2006", शून्यपूर्ण,
		अणुANY_BOARD_ID, ANY_BOARD_IDपूर्ण,
		1264, 5675, 1171, 4688
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*****************************************************************************
 *	Synaptics communications functions
 ****************************************************************************/

/*
 * Synaptics touchpads report the y coordinate from bottom to top, which is
 * opposite from what userspace expects.
 * This function is used to invert y beक्रमe reporting.
 */
अटल पूर्णांक synaptics_invert_y(पूर्णांक y)
अणु
	वापस YMAX_NOMINAL + YMIN_NOMINAL - y;
पूर्ण

/*
 * Apply quirk(s) अगर the hardware matches
 */
अटल व्योम synaptics_apply_quirks(काष्ठा psmouse *psmouse,
				   काष्ठा synaptics_device_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; min_max_pnpid_table[i].pnp_ids; i++) अणु
		अगर (!psmouse_matches_pnp_id(psmouse,
					    min_max_pnpid_table[i].pnp_ids))
			जारी;

		अगर (min_max_pnpid_table[i].board_id.min != ANY_BOARD_ID &&
		    info->board_id < min_max_pnpid_table[i].board_id.min)
			जारी;

		अगर (min_max_pnpid_table[i].board_id.max != ANY_BOARD_ID &&
		    info->board_id > min_max_pnpid_table[i].board_id.max)
			जारी;

		info->x_min = min_max_pnpid_table[i].x_min;
		info->x_max = min_max_pnpid_table[i].x_max;
		info->y_min = min_max_pnpid_table[i].y_min;
		info->y_max = min_max_pnpid_table[i].y_max;
		psmouse_info(psmouse,
			     "quirked min/max coordinates: x [%d..%d], y [%d..%d]\n",
			     info->x_min, info->x_max,
			     info->y_min, info->y_max);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool synaptics_has_agm(काष्ठा synaptics_data *priv)
अणु
	वापस (SYN_CAP_ADV_GESTURE(priv->info.ext_cap_0c) ||
		SYN_CAP_IMAGE_SENSOR(priv->info.ext_cap_0c));
पूर्ण

अटल पूर्णांक synaptics_set_advanced_gesture_mode(काष्ठा psmouse *psmouse)
अणु
	अटल u8 param = 0xc8;
	पूर्णांक error;

	error = ps2_sliced_command(&psmouse->ps2dev, SYN_QUE_MODEL);
	अगर (error)
		वापस error;

	error = ps2_command(&psmouse->ps2dev, &param, PSMOUSE_CMD_SETRATE);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक synaptics_set_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;
	पूर्णांक error;

	priv->mode = 0;
	अगर (priv->असलolute_mode)
		priv->mode |= SYN_BIT_ABSOLUTE_MODE;
	अगर (priv->disable_gesture)
		priv->mode |= SYN_BIT_DISABLE_GESTURE;
	अगर (psmouse->rate >= 80)
		priv->mode |= SYN_BIT_HIGH_RATE;
	अगर (SYN_CAP_EXTENDED(priv->info.capabilities))
		priv->mode |= SYN_BIT_W_MODE;

	error = synaptics_mode_cmd(psmouse, priv->mode);
	अगर (error)
		वापस error;

	अगर (priv->असलolute_mode && synaptics_has_agm(priv)) अणु
		error = synaptics_set_advanced_gesture_mode(psmouse);
		अगर (error) अणु
			psmouse_err(psmouse,
				    "Advanced gesture mode init failed: %d\n",
				    error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम synaptics_set_rate(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;

	अगर (rate >= 80) अणु
		priv->mode |= SYN_BIT_HIGH_RATE;
		psmouse->rate = 80;
	पूर्ण अन्यथा अणु
		priv->mode &= ~SYN_BIT_HIGH_RATE;
		psmouse->rate = 40;
	पूर्ण

	synaptics_mode_cmd(psmouse, priv->mode);
पूर्ण

/*****************************************************************************
 *	Synaptics pass-through PS/2 port support
 ****************************************************************************/
अटल पूर्णांक synaptics_pt_ग_लिखो(काष्ठा serio *serio, u8 c)
अणु
	काष्ठा psmouse *parent = serio_get_drvdata(serio->parent);
	u8 rate_param = SYN_PS_CLIENT_CMD; /* indicates that we want pass-through port */
	पूर्णांक error;

	error = ps2_sliced_command(&parent->ps2dev, c);
	अगर (error)
		वापस error;

	error = ps2_command(&parent->ps2dev, &rate_param, PSMOUSE_CMD_SETRATE);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक synaptics_pt_start(काष्ठा serio *serio)
अणु
	काष्ठा psmouse *parent = serio_get_drvdata(serio->parent);
	काष्ठा synaptics_data *priv = parent->निजी;

	serio_छोड़ो_rx(parent->ps2dev.serio);
	priv->pt_port = serio;
	serio_जारी_rx(parent->ps2dev.serio);

	वापस 0;
पूर्ण

अटल व्योम synaptics_pt_stop(काष्ठा serio *serio)
अणु
	काष्ठा psmouse *parent = serio_get_drvdata(serio->parent);
	काष्ठा synaptics_data *priv = parent->निजी;

	serio_छोड़ो_rx(parent->ps2dev.serio);
	priv->pt_port = शून्य;
	serio_जारी_rx(parent->ps2dev.serio);
पूर्ण

अटल पूर्णांक synaptics_is_pt_packet(u8 *buf)
अणु
	वापस (buf[0] & 0xFC) == 0x84 && (buf[3] & 0xCC) == 0xC4;
पूर्ण

अटल व्योम synaptics_pass_pt_packet(काष्ठा serio *ptport, u8 *packet)
अणु
	काष्ठा psmouse *child = serio_get_drvdata(ptport);

	अगर (child && child->state == PSMOUSE_ACTIVATED) अणु
		serio_पूर्णांकerrupt(ptport, packet[1], 0);
		serio_पूर्णांकerrupt(ptport, packet[4], 0);
		serio_पूर्णांकerrupt(ptport, packet[5], 0);
		अगर (child->pktsize == 4)
			serio_पूर्णांकerrupt(ptport, packet[2], 0);
	पूर्ण अन्यथा अणु
		serio_पूर्णांकerrupt(ptport, packet[1], 0);
	पूर्ण
पूर्ण

अटल व्योम synaptics_pt_activate(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;
	काष्ठा psmouse *child = serio_get_drvdata(priv->pt_port);

	/* adjust the touchpad to child's choice of protocol */
	अगर (child) अणु
		अगर (child->pktsize == 4)
			priv->mode |= SYN_BIT_FOUR_BYTE_CLIENT;
		अन्यथा
			priv->mode &= ~SYN_BIT_FOUR_BYTE_CLIENT;

		अगर (synaptics_mode_cmd(psmouse, priv->mode))
			psmouse_warn(psmouse,
				     "failed to switch guest protocol\n");
	पूर्ण
पूर्ण

अटल व्योम synaptics_pt_create(काष्ठा psmouse *psmouse)
अणु
	काष्ठा serio *serio;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio) अणु
		psmouse_err(psmouse,
			    "not enough memory for pass-through port\n");
		वापस;
	पूर्ण

	serio->id.type = SERIO_PS_PSTHRU;
	strlcpy(serio->name, "Synaptics pass-through", माप(serio->name));
	strlcpy(serio->phys, "synaptics-pt/serio0", माप(serio->phys));
	serio->ग_लिखो = synaptics_pt_ग_लिखो;
	serio->start = synaptics_pt_start;
	serio->stop = synaptics_pt_stop;
	serio->parent = psmouse->ps2dev.serio;

	psmouse->pt_activate = synaptics_pt_activate;

	psmouse_info(psmouse, "serio: %s port at %s\n",
		     serio->name, psmouse->phys);
	serio_रेजिस्टर_port(serio);
पूर्ण

/*****************************************************************************
 *	Functions to पूर्णांकerpret the असलolute mode packets
 ****************************************************************************/

अटल व्योम synaptics_parse_agm(स्थिर u8 buf[],
				काष्ठा synaptics_data *priv,
				काष्ठा synaptics_hw_state *hw)
अणु
	काष्ठा synaptics_hw_state *agm = &priv->agm;
	पूर्णांक agm_packet_type;

	agm_packet_type = (buf[5] & 0x30) >> 4;
	चयन (agm_packet_type) अणु
	हाल 1:
		/* Gesture packet: (x, y, z) half resolution */
		agm->w = hw->w;
		agm->x = (((buf[4] & 0x0f) << 8) | buf[1]) << 1;
		agm->y = (((buf[4] & 0xf0) << 4) | buf[2]) << 1;
		agm->z = ((buf[3] & 0x30) | (buf[5] & 0x0f)) << 1;
		अवरोध;

	हाल 2:
		/* AGM-CONTACT packet: we are only पूर्णांकerested in the count */
		priv->agm_count = buf[1];
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम synaptics_parse_ext_buttons(स्थिर u8 buf[],
					काष्ठा synaptics_data *priv,
					काष्ठा synaptics_hw_state *hw)
अणु
	अचिन्हित पूर्णांक ext_bits =
		(SYN_CAP_MULTI_BUTTON_NO(priv->info.ext_cap) + 1) >> 1;
	अचिन्हित पूर्णांक ext_mask = GENMASK(ext_bits - 1, 0);

	hw->ext_buttons = buf[4] & ext_mask;
	hw->ext_buttons |= (buf[5] & ext_mask) << ext_bits;
पूर्ण

अटल पूर्णांक synaptics_parse_hw_state(स्थिर u8 buf[],
				    काष्ठा synaptics_data *priv,
				    काष्ठा synaptics_hw_state *hw)
अणु
	स_रखो(hw, 0, माप(काष्ठा synaptics_hw_state));

	अगर (SYN_MODEL_NEWABS(priv->info.model_id)) अणु
		hw->w = (((buf[0] & 0x30) >> 2) |
			 ((buf[0] & 0x04) >> 1) |
			 ((buf[3] & 0x04) >> 2));

		अगर (synaptics_has_agm(priv) && hw->w == 2) अणु
			synaptics_parse_agm(buf, priv, hw);
			वापस 1;
		पूर्ण

		hw->x = (((buf[3] & 0x10) << 8) |
			 ((buf[1] & 0x0f) << 8) |
			 buf[4]);
		hw->y = (((buf[3] & 0x20) << 7) |
			 ((buf[1] & 0xf0) << 4) |
			 buf[5]);
		hw->z = buf[2];

		hw->left  = (buf[0] & 0x01) ? 1 : 0;
		hw->right = (buf[0] & 0x02) ? 1 : 0;

		अगर (priv->is_क्रमcepad) अणु
			/*
			 * ForcePads, like Clickpads, use middle button
			 * bits to report primary button clicks.
			 * Unक्रमtunately they report primary button not
			 * only when user presses on the pad above certain
			 * threshold, but also when there are more than one
			 * finger on the touchpad, which पूर्णांकerferes with
			 * out multi-finger gestures.
			 */
			अगर (hw->z == 0) अणु
				/* No contacts */
				priv->press = priv->report_press = false;
			पूर्ण अन्यथा अगर (hw->w >= 4 && ((buf[0] ^ buf[3]) & 0x01)) अणु
				/*
				 * Single-finger touch with pressure above
				 * the threshold. If pressure stays दीर्घ
				 * enough, we'll start reporting primary
				 * button. We rely on the device continuing
				 * sending data even अगर finger करोes not
				 * move.
				 */
				अगर  (!priv->press) अणु
					priv->press_start = jअगरfies;
					priv->press = true;
				पूर्ण अन्यथा अगर (समय_after(jअगरfies,
						priv->press_start +
							msecs_to_jअगरfies(50))) अणु
					priv->report_press = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				priv->press = false;
			पूर्ण

			hw->left = priv->report_press;

		पूर्ण अन्यथा अगर (SYN_CAP_CLICKPAD(priv->info.ext_cap_0c)) अणु
			/*
			 * Clickpad's button is transmitted as middle button,
			 * however, since it is primary button, we will report
			 * it as BTN_LEFT.
			 */
			hw->left = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;

		पूर्ण अन्यथा अगर (SYN_CAP_MIDDLE_BUTTON(priv->info.capabilities)) अणु
			hw->middle = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;
			अगर (hw->w == 2)
				hw->scroll = (s8)buf[1];
		पूर्ण

		अगर (SYN_CAP_FOUR_BUTTON(priv->info.capabilities)) अणु
			hw->up   = ((buf[0] ^ buf[3]) & 0x01) ? 1 : 0;
			hw->करोwn = ((buf[0] ^ buf[3]) & 0x02) ? 1 : 0;
		पूर्ण

		अगर (SYN_CAP_MULTI_BUTTON_NO(priv->info.ext_cap) > 0 &&
		    ((buf[0] ^ buf[3]) & 0x02)) अणु
			synaptics_parse_ext_buttons(buf, priv, hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		hw->x = (((buf[1] & 0x1f) << 8) | buf[2]);
		hw->y = (((buf[4] & 0x1f) << 8) | buf[5]);

		hw->z = (((buf[0] & 0x30) << 2) | (buf[3] & 0x3F));
		hw->w = (((buf[1] & 0x80) >> 4) | ((buf[0] & 0x04) >> 1));

		hw->left  = (buf[0] & 0x01) ? 1 : 0;
		hw->right = (buf[0] & 0x02) ? 1 : 0;
	पूर्ण

	/*
	 * Convert wrap-around values to negative. (X|Y)_MAX_POSITIVE
	 * is used by some firmware to indicate a finger at the edge of
	 * the touchpad whose precise position cannot be determined, so
	 * convert these values to the maximum axis value.
	 */
	अगर (hw->x > X_MAX_POSITIVE)
		hw->x -= 1 << ABS_POS_BITS;
	अन्यथा अगर (hw->x == X_MAX_POSITIVE)
		hw->x = XMAX;

	अगर (hw->y > Y_MAX_POSITIVE)
		hw->y -= 1 << ABS_POS_BITS;
	अन्यथा अगर (hw->y == Y_MAX_POSITIVE)
		hw->y = YMAX;

	वापस 0;
पूर्ण

अटल व्योम synaptics_report_semi_mt_slot(काष्ठा input_dev *dev, पूर्णांक slot,
					  bool active, पूर्णांक x, पूर्णांक y)
अणु
	input_mt_slot(dev, slot);
	input_mt_report_slot_state(dev, MT_TOOL_FINGER, active);
	अगर (active) अणु
		input_report_असल(dev, ABS_MT_POSITION_X, x);
		input_report_असल(dev, ABS_MT_POSITION_Y, synaptics_invert_y(y));
	पूर्ण
पूर्ण

अटल व्योम synaptics_report_semi_mt_data(काष्ठा input_dev *dev,
					  स्थिर काष्ठा synaptics_hw_state *a,
					  स्थिर काष्ठा synaptics_hw_state *b,
					  पूर्णांक num_fingers)
अणु
	अगर (num_fingers >= 2) अणु
		synaptics_report_semi_mt_slot(dev, 0, true, min(a->x, b->x),
					      min(a->y, b->y));
		synaptics_report_semi_mt_slot(dev, 1, true, max(a->x, b->x),
					      max(a->y, b->y));
	पूर्ण अन्यथा अगर (num_fingers == 1) अणु
		synaptics_report_semi_mt_slot(dev, 0, true, a->x, a->y);
		synaptics_report_semi_mt_slot(dev, 1, false, 0, 0);
	पूर्ण अन्यथा अणु
		synaptics_report_semi_mt_slot(dev, 0, false, 0, 0);
		synaptics_report_semi_mt_slot(dev, 1, false, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम synaptics_report_ext_buttons(काष्ठा psmouse *psmouse,
					 स्थिर काष्ठा synaptics_hw_state *hw)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा synaptics_data *priv = psmouse->निजी;
	पूर्णांक ext_bits = (SYN_CAP_MULTI_BUTTON_NO(priv->info.ext_cap) + 1) >> 1;
	पूर्णांक i;

	अगर (!SYN_CAP_MULTI_BUTTON_NO(priv->info.ext_cap))
		वापस;

	/* Bug in FW 8.1 & 8.2, buttons are reported only when ExtBit is 1 */
	अगर ((SYN_ID_FULL(priv->info.identity) == 0x801 ||
	     SYN_ID_FULL(priv->info.identity) == 0x802) &&
	    !((psmouse->packet[0] ^ psmouse->packet[3]) & 0x02))
		वापस;

	अगर (!SYN_CAP_EXT_BUTTONS_STICK(priv->info.ext_cap_10)) अणु
		क्रम (i = 0; i < ext_bits; i++) अणु
			input_report_key(dev, BTN_0 + 2 * i,
				hw->ext_buttons & BIT(i));
			input_report_key(dev, BTN_1 + 2 * i,
				hw->ext_buttons & BIT(i + ext_bits));
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * This generation of touchpads has the trackstick buttons
	 * physically wired to the touchpad. Re-route them through
	 * the pass-through पूर्णांकerface.
	 */
	अगर (priv->pt_port) अणु
		u8 pt_buttons;

		/* The trackstick expects at most 3 buttons */
		pt_buttons = SYN_EXT_BUTTON_STICK_L(hw->ext_buttons)      |
			     SYN_EXT_BUTTON_STICK_R(hw->ext_buttons) << 1 |
			     SYN_EXT_BUTTON_STICK_M(hw->ext_buttons) << 2;

		serio_पूर्णांकerrupt(priv->pt_port,
				PSMOUSE_OOB_EXTRA_BTNS, SERIO_OOB_DATA);
		serio_पूर्णांकerrupt(priv->pt_port, pt_buttons, SERIO_OOB_DATA);
	पूर्ण
पूर्ण

अटल व्योम synaptics_report_buttons(काष्ठा psmouse *psmouse,
				     स्थिर काष्ठा synaptics_hw_state *hw)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा synaptics_data *priv = psmouse->निजी;

	input_report_key(dev, BTN_LEFT, hw->left);
	input_report_key(dev, BTN_RIGHT, hw->right);

	अगर (SYN_CAP_MIDDLE_BUTTON(priv->info.capabilities))
		input_report_key(dev, BTN_MIDDLE, hw->middle);

	अगर (SYN_CAP_FOUR_BUTTON(priv->info.capabilities)) अणु
		input_report_key(dev, BTN_FORWARD, hw->up);
		input_report_key(dev, BTN_BACK, hw->करोwn);
	पूर्ण

	synaptics_report_ext_buttons(psmouse, hw);
पूर्ण

अटल व्योम synaptics_report_mt_data(काष्ठा psmouse *psmouse,
				     स्थिर काष्ठा synaptics_hw_state *sgm,
				     पूर्णांक num_fingers)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा synaptics_data *priv = psmouse->निजी;
	स्थिर काष्ठा synaptics_hw_state *hw[2] = अणु sgm, &priv->agm पूर्ण;
	काष्ठा input_mt_pos pos[2];
	पूर्णांक slot[2], nsemi, i;

	nsemi = clamp_val(num_fingers, 0, 2);

	क्रम (i = 0; i < nsemi; i++) अणु
		pos[i].x = hw[i]->x;
		pos[i].y = synaptics_invert_y(hw[i]->y);
	पूर्ण

	input_mt_assign_slots(dev, slot, pos, nsemi, DMAX * priv->info.x_res);

	क्रम (i = 0; i < nsemi; i++) अणु
		input_mt_slot(dev, slot[i]);
		input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);
		input_report_असल(dev, ABS_MT_POSITION_X, pos[i].x);
		input_report_असल(dev, ABS_MT_POSITION_Y, pos[i].y);
		input_report_असल(dev, ABS_MT_PRESSURE, hw[i]->z);
	पूर्ण

	input_mt_drop_unused(dev);

	/* Don't use active slot count to generate BTN_TOOL events. */
	input_mt_report_poपूर्णांकer_emulation(dev, false);

	/* Send the number of fingers reported by touchpad itself. */
	input_mt_report_finger_count(dev, num_fingers);

	synaptics_report_buttons(psmouse, sgm);

	input_sync(dev);
पूर्ण

अटल व्योम synaptics_image_sensor_process(काष्ठा psmouse *psmouse,
					   काष्ठा synaptics_hw_state *sgm)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;
	पूर्णांक num_fingers;

	/*
	 * Update mt_state using the new finger count and current mt_state.
	 */
	अगर (sgm->z == 0)
		num_fingers = 0;
	अन्यथा अगर (sgm->w >= 4)
		num_fingers = 1;
	अन्यथा अगर (sgm->w == 0)
		num_fingers = 2;
	अन्यथा अगर (sgm->w == 1)
		num_fingers = priv->agm_count ? priv->agm_count : 3;
	अन्यथा
		num_fingers = 4;

	/* Send resulting input events to user space */
	synaptics_report_mt_data(psmouse, sgm, num_fingers);
पूर्ण

अटल bool synaptics_has_multअगरinger(काष्ठा synaptics_data *priv)
अणु
	अगर (SYN_CAP_MULTIFINGER(priv->info.capabilities))
		वापस true;

	/* Advanced gesture mode also sends multi finger data */
	वापस synaptics_has_agm(priv);
पूर्ण

/*
 *  called क्रम each full received packet from the touchpad
 */
अटल व्योम synaptics_process_packet(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा synaptics_data *priv = psmouse->निजी;
	काष्ठा synaptics_device_info *info = &priv->info;
	काष्ठा synaptics_hw_state hw;
	पूर्णांक num_fingers;
	पूर्णांक finger_width;

	अगर (synaptics_parse_hw_state(psmouse->packet, priv, &hw))
		वापस;

	अगर (SYN_CAP_IMAGE_SENSOR(info->ext_cap_0c)) अणु
		synaptics_image_sensor_process(psmouse, &hw);
		वापस;
	पूर्ण

	अगर (hw.scroll) अणु
		priv->scroll += hw.scroll;

		जबतक (priv->scroll >= 4) अणु
			input_report_key(dev, BTN_BACK, !hw.करोwn);
			input_sync(dev);
			input_report_key(dev, BTN_BACK, hw.करोwn);
			input_sync(dev);
			priv->scroll -= 4;
		पूर्ण
		जबतक (priv->scroll <= -4) अणु
			input_report_key(dev, BTN_FORWARD, !hw.up);
			input_sync(dev);
			input_report_key(dev, BTN_FORWARD, hw.up);
			input_sync(dev);
			priv->scroll += 4;
		पूर्ण
		वापस;
	पूर्ण

	अगर (hw.z > 0 && hw.x > 1) अणु
		num_fingers = 1;
		finger_width = 5;
		अगर (SYN_CAP_EXTENDED(info->capabilities)) अणु
			चयन (hw.w) अणु
			हाल 0 ... 1:
				अगर (synaptics_has_multअगरinger(priv))
					num_fingers = hw.w + 2;
				अवरोध;
			हाल 2:
				/*
				 * SYN_MODEL_PEN(info->model_id): even अगर
				 * the device supports pen, we treat it as
				 * a single finger.
				 */
				अवरोध;
			हाल 4 ... 15:
				अगर (SYN_CAP_PALMDETECT(info->capabilities))
					finger_width = hw.w;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		num_fingers = 0;
		finger_width = 0;
	पूर्ण

	अगर (cr48_profile_sensor) अणु
		synaptics_report_mt_data(psmouse, &hw, num_fingers);
		वापस;
	पूर्ण

	अगर (SYN_CAP_ADV_GESTURE(info->ext_cap_0c))
		synaptics_report_semi_mt_data(dev, &hw, &priv->agm,
					      num_fingers);

	/* Post events
	 * BTN_TOUCH has to be first as mousedev relies on it when करोing
	 * असलolute -> relative conversion
	 */
	अगर (hw.z > 30) input_report_key(dev, BTN_TOUCH, 1);
	अगर (hw.z < 25) input_report_key(dev, BTN_TOUCH, 0);

	अगर (num_fingers > 0) अणु
		input_report_असल(dev, ABS_X, hw.x);
		input_report_असल(dev, ABS_Y, synaptics_invert_y(hw.y));
	पूर्ण
	input_report_असल(dev, ABS_PRESSURE, hw.z);

	अगर (SYN_CAP_PALMDETECT(info->capabilities))
		input_report_असल(dev, ABS_TOOL_WIDTH, finger_width);

	input_report_key(dev, BTN_TOOL_FINGER, num_fingers == 1);
	अगर (synaptics_has_multअगरinger(priv)) अणु
		input_report_key(dev, BTN_TOOL_DOUBLETAP, num_fingers == 2);
		input_report_key(dev, BTN_TOOL_TRIPLETAP, num_fingers == 3);
	पूर्ण

	synaptics_report_buttons(psmouse, &hw);

	input_sync(dev);
पूर्ण

अटल bool synaptics_validate_byte(काष्ठा psmouse *psmouse,
				    पूर्णांक idx, क्रमागत synaptics_pkt_type pkt_type)
अणु
	अटल स्थिर u8 newअसल_mask[]	  = अणु 0xC8, 0x00, 0x00, 0xC8, 0x00 पूर्ण;
	अटल स्थिर u8 newअसल_rel_mask[] = अणु 0xC0, 0x00, 0x00, 0xC0, 0x00 पूर्ण;
	अटल स्थिर u8 newअसल_rslt[]	  = अणु 0x80, 0x00, 0x00, 0xC0, 0x00 पूर्ण;
	अटल स्थिर u8 oldअसल_mask[]	  = अणु 0xC0, 0x60, 0x00, 0xC0, 0x60 पूर्ण;
	अटल स्थिर u8 oldअसल_rslt[]	  = अणु 0xC0, 0x00, 0x00, 0x80, 0x00 पूर्ण;
	स्थिर u8 *packet = psmouse->packet;

	अगर (idx < 0 || idx > 4)
		वापस false;

	चयन (pkt_type) अणु

	हाल SYN_NEWABS:
	हाल SYN_NEWABS_RELAXED:
		वापस (packet[idx] & newअसल_rel_mask[idx]) == newअसल_rslt[idx];

	हाल SYN_NEWABS_STRICT:
		वापस (packet[idx] & newअसल_mask[idx]) == newअसल_rslt[idx];

	हाल SYN_OLDABS:
		वापस (packet[idx] & oldअसल_mask[idx]) == oldअसल_rslt[idx];

	शेष:
		psmouse_err(psmouse, "unknown packet type %d\n", pkt_type);
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत synaptics_pkt_type
synaptics_detect_pkt_type(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		अगर (!synaptics_validate_byte(psmouse, i, SYN_NEWABS_STRICT)) अणु
			psmouse_info(psmouse, "using relaxed packet validation\n");
			वापस SYN_NEWABS_RELAXED;
		पूर्ण
	पूर्ण

	वापस SYN_NEWABS_STRICT;
पूर्ण

अटल psmouse_ret_t synaptics_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;

	अगर (psmouse->pktcnt >= 6) अणु /* Full packet received */
		अगर (unlikely(priv->pkt_type == SYN_NEWABS))
			priv->pkt_type = synaptics_detect_pkt_type(psmouse);

		अगर (SYN_CAP_PASS_THROUGH(priv->info.capabilities) &&
		    synaptics_is_pt_packet(psmouse->packet)) अणु
			अगर (priv->pt_port)
				synaptics_pass_pt_packet(priv->pt_port,
							 psmouse->packet);
		पूर्ण अन्यथा
			synaptics_process_packet(psmouse);

		वापस PSMOUSE_FULL_PACKET;
	पूर्ण

	वापस synaptics_validate_byte(psmouse, psmouse->pktcnt - 1, priv->pkt_type) ?
		PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
पूर्ण

/*****************************************************************************
 *	Driver initialization/cleanup functions
 ****************************************************************************/
अटल व्योम set_असल_position_params(काष्ठा input_dev *dev,
				    काष्ठा synaptics_device_info *info,
				    पूर्णांक x_code, पूर्णांक y_code)
अणु
	पूर्णांक x_min = info->x_min ?: XMIN_NOMINAL;
	पूर्णांक x_max = info->x_max ?: XMAX_NOMINAL;
	पूर्णांक y_min = info->y_min ?: YMIN_NOMINAL;
	पूर्णांक y_max = info->y_max ?: YMAX_NOMINAL;
	पूर्णांक fuzz = SYN_CAP_REDUCED_FILTERING(info->ext_cap_0c) ?
			SYN_REDUCED_FILTER_FUZZ : 0;

	input_set_असल_params(dev, x_code, x_min, x_max, fuzz, 0);
	input_set_असल_params(dev, y_code, y_min, y_max, fuzz, 0);
	input_असल_set_res(dev, x_code, info->x_res);
	input_असल_set_res(dev, y_code, info->y_res);
पूर्ण

अटल पूर्णांक set_input_params(काष्ठा psmouse *psmouse,
			    काष्ठा synaptics_data *priv)
अणु
	काष्ठा input_dev *dev = psmouse->dev;
	काष्ठा synaptics_device_info *info = &priv->info;
	पूर्णांक i;
	पूर्णांक error;

	/* Reset शेष psmouse capabilities */
	__clear_bit(EV_REL, dev->evbit);
	biपंचांगap_zero(dev->relbit, REL_CNT);
	biपंचांगap_zero(dev->keybit, KEY_CNT);

	/* Things that apply to both modes */
	__set_bit(INPUT_PROP_POINTER, dev->propbit);

	input_set_capability(dev, EV_KEY, BTN_LEFT);

	/* Clickpads report only left button */
	अगर (!SYN_CAP_CLICKPAD(info->ext_cap_0c)) अणु
		input_set_capability(dev, EV_KEY, BTN_RIGHT);
		अगर (SYN_CAP_MIDDLE_BUTTON(info->capabilities))
			input_set_capability(dev, EV_KEY, BTN_MIDDLE);
	पूर्ण

	अगर (!priv->असलolute_mode) अणु
		/* Relative mode */
		input_set_capability(dev, EV_REL, REL_X);
		input_set_capability(dev, EV_REL, REL_Y);
		वापस 0;
	पूर्ण

	/* Absolute mode */
	set_असल_position_params(dev, &priv->info, ABS_X, ABS_Y);
	input_set_असल_params(dev, ABS_PRESSURE, 0, 255, 0, 0);

	अगर (cr48_profile_sensor)
		input_set_असल_params(dev, ABS_MT_PRESSURE, 0, 255, 0, 0);

	अगर (SYN_CAP_IMAGE_SENSOR(info->ext_cap_0c)) अणु
		set_असल_position_params(dev, info,
					ABS_MT_POSITION_X, ABS_MT_POSITION_Y);
		/* Image sensors can report per-contact pressure */
		input_set_असल_params(dev, ABS_MT_PRESSURE, 0, 255, 0, 0);

		error = input_mt_init_slots(dev, 2,
					    INPUT_MT_POINTER | INPUT_MT_TRACK);
		अगर (error)
			वापस error;

		/* Image sensors can संकेत 4 and 5 finger clicks */
		input_set_capability(dev, EV_KEY, BTN_TOOL_QUADTAP);
		input_set_capability(dev, EV_KEY, BTN_TOOL_QUINTTAP);
	पूर्ण अन्यथा अगर (SYN_CAP_ADV_GESTURE(info->ext_cap_0c)) अणु
		set_असल_position_params(dev, info,
					ABS_MT_POSITION_X, ABS_MT_POSITION_Y);
		/*
		 * Profile sensor in CR-48 tracks contacts reasonably well,
		 * other non-image sensors with AGM use semi-mt.
		 */
		error = input_mt_init_slots(dev, 2,
					    INPUT_MT_POINTER |
					     (cr48_profile_sensor ?
					      INPUT_MT_TRACK :
					      INPUT_MT_SEMI_MT));
		अगर (error)
			वापस error;

		/*
		 * For semi-mt devices we send ABS_X/Y ourselves instead of
		 * input_mt_report_poपूर्णांकer_emulation. But
		 * input_mt_init_slots() resets the fuzz to 0, leading to a
		 * filtered ABS_MT_POSITION_X but an unfiltered ABS_X
		 * position. Let's re-initialize ABS_X/Y here.
		 */
		अगर (!cr48_profile_sensor)
			set_असल_position_params(dev, &priv->info, ABS_X, ABS_Y);
	पूर्ण

	अगर (SYN_CAP_PALMDETECT(info->capabilities))
		input_set_असल_params(dev, ABS_TOOL_WIDTH, 0, 15, 0, 0);

	input_set_capability(dev, EV_KEY, BTN_TOUCH);
	input_set_capability(dev, EV_KEY, BTN_TOOL_FINGER);

	अगर (synaptics_has_multअगरinger(priv)) अणु
		input_set_capability(dev, EV_KEY, BTN_TOOL_DOUBLETAP);
		input_set_capability(dev, EV_KEY, BTN_TOOL_TRIPLETAP);
	पूर्ण

	अगर (SYN_CAP_FOUR_BUTTON(info->capabilities) ||
	    SYN_CAP_MIDDLE_BUTTON(info->capabilities)) अणु
		input_set_capability(dev, EV_KEY, BTN_FORWARD);
		input_set_capability(dev, EV_KEY, BTN_BACK);
	पूर्ण

	अगर (!SYN_CAP_EXT_BUTTONS_STICK(info->ext_cap_10))
		क्रम (i = 0; i < SYN_CAP_MULTI_BUTTON_NO(info->ext_cap); i++)
			input_set_capability(dev, EV_KEY, BTN_0 + i);

	अगर (SYN_CAP_CLICKPAD(info->ext_cap_0c)) अणु
		__set_bit(INPUT_PROP_BUTTONPAD, dev->propbit);
		अगर (psmouse_matches_pnp_id(psmouse, topbuttonpad_pnp_ids) &&
		    !SYN_CAP_EXT_BUTTONS_STICK(info->ext_cap_10))
			__set_bit(INPUT_PROP_TOPBUTTONPAD, dev->propbit);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार synaptics_show_disable_gesture(काष्ठा psmouse *psmouse,
					      व्योम *data, अक्षर *buf)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;

	वापस प्र_लिखो(buf, "%c\n", priv->disable_gesture ? '1' : '0');
पूर्ण

अटल sमाप_प्रकार synaptics_set_disable_gesture(काष्ठा psmouse *psmouse,
					     व्योम *data, स्थिर अक्षर *buf,
					     माप_प्रकार len)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (value == priv->disable_gesture)
		वापस len;

	priv->disable_gesture = value;
	अगर (value)
		priv->mode |= SYN_BIT_DISABLE_GESTURE;
	अन्यथा
		priv->mode &= ~SYN_BIT_DISABLE_GESTURE;

	अगर (synaptics_mode_cmd(psmouse, priv->mode))
		वापस -EIO;

	वापस len;
पूर्ण

PSMOUSE_DEFINE_ATTR(disable_gesture, S_IWUSR | S_IRUGO, शून्य,
		    synaptics_show_disable_gesture,
		    synaptics_set_disable_gesture);

अटल व्योम synaptics_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;

	/*
	 * We might have left a bपढ़ोcrumb when trying to
	 * set up SMbus companion.
	 */
	psmouse_smbus_cleanup(psmouse);

	अगर (!priv->असलolute_mode &&
			SYN_ID_DISGEST_SUPPORTED(priv->info.identity))
		device_हटाओ_file(&psmouse->ps2dev.serio->dev,
				   &psmouse_attr_disable_gesture.dattr);

	synaptics_reset(psmouse);
	kमुक्त(priv);
	psmouse->निजी = शून्य;
पूर्ण

अटल पूर्णांक synaptics_reconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_data *priv = psmouse->निजी;
	काष्ठा synaptics_device_info info;
	u8 param[2];
	पूर्णांक retry = 0;
	पूर्णांक error;

	करो अणु
		psmouse_reset(psmouse);
		अगर (retry) अणु
			/*
			 * On some boxes, right after resuming, the touchpad
			 * needs some समय to finish initializing (I assume
			 * it needs समय to calibrate) and start responding
			 * to Synaptics-specअगरic queries, so let's रुको a
			 * bit.
			 */
			ssleep(1);
		पूर्ण
		ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETID);
		error = synaptics_detect(psmouse, 0);
	पूर्ण जबतक (error && ++retry < 3);

	अगर (error)
		वापस error;

	अगर (retry > 1)
		psmouse_dbg(psmouse, "reconnected after %d tries\n", retry);

	error = synaptics_query_hardware(psmouse, &info);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to query device.\n");
		वापस error;
	पूर्ण

	error = synaptics_set_mode(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to initialize device.\n");
		वापस error;
	पूर्ण

	अगर (info.identity != priv->info.identity ||
	    info.model_id != priv->info.model_id ||
	    info.capabilities != priv->info.capabilities ||
	    info.ext_cap != priv->info.ext_cap) अणु
		psmouse_err(psmouse,
			    "hardware appears to be different: id(%u-%u), model(%u-%u), caps(%x-%x), ext(%x-%x).\n",
			    priv->info.identity, info.identity,
			    priv->info.model_id, info.model_id,
			    priv->info.capabilities, info.capabilities,
			    priv->info.ext_cap, info.ext_cap);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool impaired_toshiba_kbc;

अटल स्थिर काष्ठा dmi_प्रणाली_id toshiba_dmi_table[] __initस्थिर = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Toshiba Satellite */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Satellite"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Toshiba Dynabook */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "dynabook"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Toshiba Portege M300 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PORTEGE M300"),
		पूर्ण,

	पूर्ण,
	अणु
		/* Toshiba Portege M300 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Portable PC"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Version 1.0"),
		पूर्ण,

	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल bool broken_olpc_ec;

अटल स्थिर काष्ठा dmi_प्रणाली_id olpc_dmi_table[] __initस्थिर = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_OLPC)
	अणु
		/* OLPC XO-1 or XO-1.5 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "OLPC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "XO"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर cr48_dmi_table[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		/* Cr-48 Chromebook (Codename Mario) */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IEC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Mario"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

व्योम __init synaptics_module_init(व्योम)
अणु
	impaired_toshiba_kbc = dmi_check_प्रणाली(toshiba_dmi_table);
	broken_olpc_ec = dmi_check_प्रणाली(olpc_dmi_table);
	cr48_profile_sensor = dmi_check_प्रणाली(cr48_dmi_table);
पूर्ण

अटल पूर्णांक synaptics_init_ps2(काष्ठा psmouse *psmouse,
			      काष्ठा synaptics_device_info *info,
			      bool असलolute_mode)
अणु
	काष्ठा synaptics_data *priv;
	पूर्णांक err;

	synaptics_apply_quirks(psmouse, info);

	psmouse->निजी = priv = kzalloc(माप(काष्ठा synaptics_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->info = *info;
	priv->असलolute_mode = असलolute_mode;
	अगर (SYN_ID_DISGEST_SUPPORTED(info->identity))
		priv->disable_gesture = true;

	/*
	 * Unक्रमtunately ForcePad capability is not exported over PS/2,
	 * so we have to resort to checking PNP IDs.
	 */
	priv->is_क्रमcepad = psmouse_matches_pnp_id(psmouse, क्रमcepad_pnp_ids);

	err = synaptics_set_mode(psmouse);
	अगर (err) अणु
		psmouse_err(psmouse, "Unable to initialize device.\n");
		जाओ init_fail;
	पूर्ण

	priv->pkt_type = SYN_MODEL_NEWABS(info->model_id) ?
					SYN_NEWABS : SYN_OLDABS;

	psmouse_info(psmouse,
		     "Touchpad model: %lu, fw: %lu.%lu, id: %#x, caps: %#x/%#x/%#x/%#x, board id: %u, fw id: %u\n",
		     SYN_ID_MODEL(info->identity),
		     SYN_ID_MAJOR(info->identity), SYN_ID_MINOR(info->identity),
		     info->model_id,
		     info->capabilities, info->ext_cap, info->ext_cap_0c,
		     info->ext_cap_10, info->board_id, info->firmware_id);

	err = set_input_params(psmouse, priv);
	अगर (err) अणु
		psmouse_err(psmouse,
			    "failed to set up capabilities: %d\n", err);
		जाओ init_fail;
	पूर्ण

	/*
	 * Encode touchpad model so that it can be used to set
	 * input device->id.version and be visible to userspace.
	 * Because version is __u16 we have to drop something.
	 * Hardware info bits seem to be good candidates as they
	 * are करोcumented to be क्रम Synaptics corp. पूर्णांकernal use.
	 */
	psmouse->model = ((info->model_id & 0x00ff0000) >> 8) |
			  (info->model_id & 0x000000ff);

	अगर (असलolute_mode) अणु
		psmouse->protocol_handler = synaptics_process_byte;
		psmouse->pktsize = 6;
	पूर्ण अन्यथा अणु
		/* Relative mode follows standard PS/2 mouse protocol */
		psmouse->protocol_handler = psmouse_process_byte;
		psmouse->pktsize = 3;
	पूर्ण

	psmouse->set_rate = synaptics_set_rate;
	psmouse->disconnect = synaptics_disconnect;
	psmouse->reconnect = synaptics_reconnect;
	psmouse->cleanup = synaptics_reset;
	/* Synaptics can usually stay in sync without extra help */
	psmouse->resync_समय = 0;

	अगर (SYN_CAP_PASS_THROUGH(info->capabilities))
		synaptics_pt_create(psmouse);

	/*
	 * Toshiba's KBC seems to have trouble handling data from
	 * Synaptics at full rate.  Switch to a lower rate (roughly
	 * the same rate as a standard PS/2 mouse).
	 */
	अगर (psmouse->rate >= 80 && impaired_toshiba_kbc) अणु
		psmouse_info(psmouse,
			     "Toshiba %s detected, limiting rate to 40pps.\n",
			     dmi_get_प्रणाली_info(DMI_PRODUCT_NAME));
		psmouse->rate = 40;
	पूर्ण

	अगर (!priv->असलolute_mode && SYN_ID_DISGEST_SUPPORTED(info->identity)) अणु
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_disable_gesture.dattr);
		अगर (err) अणु
			psmouse_err(psmouse,
				    "Failed to create disable_gesture attribute (%d)",
				    err);
			जाओ init_fail;
		पूर्ण
	पूर्ण

	वापस 0;

 init_fail:
	kमुक्त(priv);
	वापस err;
पूर्ण

अटल पूर्णांक __synaptics_init(काष्ठा psmouse *psmouse, bool असलolute_mode)
अणु
	काष्ठा synaptics_device_info info;
	पूर्णांक error;

	psmouse_reset(psmouse);

	error = synaptics_query_hardware(psmouse, &info);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to query device: %d\n", error);
		वापस error;
	पूर्ण

	वापस synaptics_init_ps2(psmouse, &info, असलolute_mode);
पूर्ण

पूर्णांक synaptics_init_असलolute(काष्ठा psmouse *psmouse)
अणु
	वापस __synaptics_init(psmouse, true);
पूर्ण

पूर्णांक synaptics_init_relative(काष्ठा psmouse *psmouse)
अणु
	वापस __synaptics_init(psmouse, false);
पूर्ण

अटल पूर्णांक synaptics_setup_ps2(काष्ठा psmouse *psmouse,
			       काष्ठा synaptics_device_info *info)
अणु
	bool असलolute_mode = true;
	पूर्णांक error;

	/*
	 * The OLPC XO has issues with Synaptics' असलolute mode; the स्थिरant
	 * packet spew overloads the EC such that key presses on the keyboard
	 * are missed.  Given that, करोn't even attempt to use Absolute mode.
	 * Relative mode seems to work just fine.
	 */
	अगर (broken_olpc_ec) अणु
		psmouse_info(psmouse,
			     "OLPC XO detected, forcing relative protocol.\n");
		असलolute_mode = false;
	पूर्ण

	error = synaptics_init_ps2(psmouse, info, असलolute_mode);
	अगर (error)
		वापस error;

	वापस असलolute_mode ? PSMOUSE_SYNAPTICS : PSMOUSE_SYNAPTICS_RELATIVE;
पूर्ण

#अन्यथा /* CONFIG_MOUSE_PS2_SYNAPTICS */

व्योम __init synaptics_module_init(व्योम)
अणु
पूर्ण

अटल पूर्णांक __maybe_unused
synaptics_setup_ps2(काष्ठा psmouse *psmouse,
		    काष्ठा synaptics_device_info *info)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_SYNAPTICS */

#अगर_घोषित CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS

/*
 * The newest Synaptics device can use a secondary bus (called InterTouch) which
 * provides a better bandwidth and allow a better control of the touchpads.
 * This is used to decide अगर we need to use this bus or not.
 */
क्रमागत अणु
	SYNAPTICS_INTERTOUCH_NOT_SET = -1,
	SYNAPTICS_INTERTOUCH_OFF,
	SYNAPTICS_INTERTOUCH_ON,
पूर्ण;

अटल पूर्णांक synaptics_पूर्णांकertouch = IS_ENABLED(CONFIG_RMI4_SMB) ?
		SYNAPTICS_INTERTOUCH_NOT_SET : SYNAPTICS_INTERTOUCH_OFF;
module_param_named(synaptics_पूर्णांकertouch, synaptics_पूर्णांकertouch, पूर्णांक, 0644);
MODULE_PARM_DESC(synaptics_पूर्णांकertouch, "Use a secondary bus for the Synaptics device.");

अटल पूर्णांक synaptics_create_पूर्णांकertouch(काष्ठा psmouse *psmouse,
				       काष्ठा synaptics_device_info *info,
				       bool leave_bपढ़ोcrumbs)
अणु
	bool topbuttonpad =
		psmouse_matches_pnp_id(psmouse, topbuttonpad_pnp_ids) &&
		!SYN_CAP_EXT_BUTTONS_STICK(info->ext_cap_10);
	स्थिर काष्ठा rmi_device_platक्रमm_data pdata = अणु
		.sensor_pdata = अणु
			.sensor_type = rmi_sensor_touchpad,
			.axis_align.flip_y = true,
			.kernel_tracking = false,
			.topbuttonpad = topbuttonpad,
		पूर्ण,
		.gpio_data = अणु
			.buttonpad = SYN_CAP_CLICKPAD(info->ext_cap_0c),
			.trackstick_buttons =
				!!SYN_CAP_EXT_BUTTONS_STICK(info->ext_cap_10),
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा i2c_board_info पूर्णांकertouch_board = अणु
		I2C_BOARD_INFO("rmi4_smbus", 0x2c),
		.flags = I2C_CLIENT_HOST_NOTIFY,
	पूर्ण;

	वापस psmouse_smbus_init(psmouse, &पूर्णांकertouch_board,
				  &pdata, माप(pdata), true,
				  leave_bपढ़ोcrumbs);
पूर्ण

/*
 * synaptics_setup_पूर्णांकertouch - called once the PS/2 devices are क्रमागतerated
 * and decides to instantiate a SMBus InterTouch device.
 */
अटल पूर्णांक synaptics_setup_पूर्णांकertouch(काष्ठा psmouse *psmouse,
				      काष्ठा synaptics_device_info *info,
				      bool leave_bपढ़ोcrumbs)
अणु
	पूर्णांक error;

	अगर (synaptics_पूर्णांकertouch == SYNAPTICS_INTERTOUCH_OFF)
		वापस -ENXIO;

	अगर (synaptics_पूर्णांकertouch == SYNAPTICS_INTERTOUCH_NOT_SET) अणु
		अगर (!psmouse_matches_pnp_id(psmouse, topbuttonpad_pnp_ids) &&
		    !psmouse_matches_pnp_id(psmouse, smbus_pnp_ids)) अणु

			अगर (!psmouse_matches_pnp_id(psmouse, क्रमcepad_pnp_ids))
				psmouse_info(psmouse,
					     "Your touchpad (%s) says it can support a different bus. "
					     "If i2c-hid and hid-rmi are not used, you might want to try setting psmouse.synaptics_intertouch to 1 and report this to linux-input@vger.kernel.org.\n",
					     psmouse->ps2dev.serio->firmware_id);

			वापस -ENXIO;
		पूर्ण
	पूर्ण

	psmouse_info(psmouse, "Trying to set up SMBus access\n");

	error = synaptics_create_पूर्णांकertouch(psmouse, info, leave_bपढ़ोcrumbs);
	अगर (error) अणु
		अगर (error == -EAGAIN)
			psmouse_info(psmouse, "SMbus companion is not ready yet\n");
		अन्यथा
			psmouse_err(psmouse, "unable to create intertouch device\n");

		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक synaptics_init_smbus(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_device_info info;
	पूर्णांक error;

	psmouse_reset(psmouse);

	error = synaptics_query_hardware(psmouse, &info);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to query device: %d\n", error);
		वापस error;
	पूर्ण

	अगर (!SYN_CAP_INTERTOUCH(info.ext_cap_0c))
		वापस -ENXIO;

	वापस synaptics_create_पूर्णांकertouch(psmouse, &info, false);
पूर्ण

#अन्यथा /* CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS */

अटल पूर्णांक __maybe_unused
synaptics_setup_पूर्णांकertouch(काष्ठा psmouse *psmouse,
			   काष्ठा synaptics_device_info *info,
			   bool leave_bपढ़ोcrumbs)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक synaptics_init_smbus(काष्ठा psmouse *psmouse)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS */

#अगर defined(CONFIG_MOUSE_PS2_SYNAPTICS) || \
    defined(CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS)

पूर्णांक synaptics_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा synaptics_device_info info;
	पूर्णांक error;
	पूर्णांक retval;

	psmouse_reset(psmouse);

	error = synaptics_query_hardware(psmouse, &info);
	अगर (error) अणु
		psmouse_err(psmouse, "Unable to query device: %d\n", error);
		वापस error;
	पूर्ण

	अगर (SYN_CAP_INTERTOUCH(info.ext_cap_0c)) अणु
		अगर ((!IS_ENABLED(CONFIG_RMI4_SMB) ||
		     !IS_ENABLED(CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS)) &&
		    /* Forcepads need F21, which is not पढ़ोy */
		    !psmouse_matches_pnp_id(psmouse, क्रमcepad_pnp_ids)) अणु
			psmouse_warn(psmouse,
				     "The touchpad can support a better bus than the too old PS/2 protocol. "
				     "Make sure MOUSE_PS2_SYNAPTICS_SMBUS and RMI4_SMB are enabled to get a better touchpad experience.\n");
		पूर्ण

		error = synaptics_setup_पूर्णांकertouch(psmouse, &info, true);
		अगर (!error)
			वापस PSMOUSE_SYNAPTICS_SMBUS;
	पूर्ण

	retval = synaptics_setup_ps2(psmouse, &info);
	अगर (retval < 0) अणु
		/*
		 * Not using any flavor of Synaptics support, so clean up
		 * SMbus bपढ़ोcrumbs, अगर any.
		 */
		psmouse_smbus_cleanup(psmouse);
	पूर्ण

	वापस retval;
पूर्ण

#अन्यथा /* CONFIG_MOUSE_PS2_SYNAPTICS || CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS */

पूर्णांक synaptics_init(काष्ठा psmouse *psmouse)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_SYNAPTICS || CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS */
