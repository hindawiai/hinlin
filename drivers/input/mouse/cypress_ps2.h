<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CYPRESS_PS2_H
#घोषणा _CYPRESS_PS2_H

#समावेश "psmouse.h"

#घोषणा CMD_BITS_MASK 0x03
#घोषणा COMPOSIT(x, s) (((x) & CMD_BITS_MASK) << (s))

#घोषणा ENCODE_CMD(aa, bb, cc, dd) \
	(COMPOSIT((aa), 6) | COMPOSIT((bb), 4) | COMPOSIT((cc), 2) | COMPOSIT((dd), 0))
#घोषणा CYTP_CMD_ABS_NO_PRESSURE_MODE       ENCODE_CMD(0, 1, 0, 0)
#घोषणा CYTP_CMD_ABS_WITH_PRESSURE_MODE     ENCODE_CMD(0, 1, 0, 1)
#घोषणा CYTP_CMD_SMBUS_MODE                 ENCODE_CMD(0, 1, 1, 0)
#घोषणा CYTP_CMD_STANDARD_MODE              ENCODE_CMD(0, 2, 0, 0)  /* not implemented yet. */
#घोषणा CYTP_CMD_CYPRESS_REL_MODE           ENCODE_CMD(1, 1, 1, 1)  /* not implemented yet. */
#घोषणा CYTP_CMD_READ_CYPRESS_ID            ENCODE_CMD(0, 0, 0, 0)
#घोषणा CYTP_CMD_READ_TP_METRICS            ENCODE_CMD(0, 0, 0, 1)
#घोषणा CYTP_CMD_SET_HSCROLL_WIDTH(w)       ENCODE_CMD(1, 1, 0, (w))
#घोषणा     CYTP_CMD_SET_HSCROLL_MASK       ENCODE_CMD(1, 1, 0, 0)
#घोषणा CYTP_CMD_SET_VSCROLL_WIDTH(w)       ENCODE_CMD(1, 2, 0, (w))
#घोषणा     CYTP_CMD_SET_VSCROLL_MASK       ENCODE_CMD(1, 2, 0, 0)
#घोषणा CYTP_CMD_SET_PALM_GEOMETRY(e)       ENCODE_CMD(1, 2, 1, (e))
#घोषणा     CYTP_CMD_PALM_GEMMETRY_MASK     ENCODE_CMD(1, 2, 1, 0)
#घोषणा CYTP_CMD_SET_PALM_SENSITIVITY(s)    ENCODE_CMD(1, 2, 2, (s))
#घोषणा     CYTP_CMD_PALM_SENSITIVITY_MASK  ENCODE_CMD(1, 2, 2, 0)
#घोषणा CYTP_CMD_SET_MOUSE_SENSITIVITY(s)   ENCODE_CMD(1, 3, ((s) >> 2), (s))
#घोषणा     CYTP_CMD_MOUSE_SENSITIVITY_MASK ENCODE_CMD(1, 3, 0, 0)
#घोषणा CYTP_CMD_REQUEST_BASELINE_STATUS    ENCODE_CMD(2, 0, 0, 1)
#घोषणा CYTP_CMD_REQUEST_RECALIBRATION      ENCODE_CMD(2, 0, 0, 3)

#घोषणा DECODE_CMD_AA(x) (((x) >> 6) & CMD_BITS_MASK)
#घोषणा DECODE_CMD_BB(x) (((x) >> 4) & CMD_BITS_MASK)
#घोषणा DECODE_CMD_CC(x) (((x) >> 2) & CMD_BITS_MASK)
#घोषणा DECODE_CMD_DD(x) ((x) & CMD_BITS_MASK)

/* Cypress trackpad working mode. */
#घोषणा CYTP_BIT_ABS_PRESSURE    (1 << 3)
#घोषणा CYTP_BIT_ABS_NO_PRESSURE (1 << 2)
#घोषणा CYTP_BIT_CYPRESS_REL     (1 << 1)
#घोषणा CYTP_BIT_STANDARD_REL    (1 << 0)
#घोषणा CYTP_BIT_REL_MASK (CYTP_BIT_CYPRESS_REL | CYTP_BIT_STANDARD_REL)
#घोषणा CYTP_BIT_ABS_MASK (CYTP_BIT_ABS_PRESSURE | CYTP_BIT_ABS_NO_PRESSURE)
#घोषणा CYTP_BIT_ABS_REL_MASK (CYTP_BIT_ABS_MASK | CYTP_BIT_REL_MASK)

#घोषणा CYTP_BIT_HIGH_RATE       (1 << 4)
/*
 * report mode bit is set, firmware working in Remote Mode.
 * report mode bit is cleared, firmware working in Stream Mode.
 */
#घोषणा CYTP_BIT_REPORT_MODE     (1 << 5)

/* scrolling width values क्रम set HSCROLL and VSCROLL width command. */
#घोषणा SCROLL_WIDTH_NARROW 1
#घोषणा SCROLL_WIDTH_NORMAL 2
#घोषणा SCROLL_WIDTH_WIDE   3

#घोषणा PALM_GEOMETRY_ENABLE  1
#घोषणा PALM_GEOMETRY_DISABLE 0

#घोषणा TP_METRICS_MASK  0x80
#घोषणा FW_VERSION_MASX    0x7f
#घोषणा FW_VER_HIGH_MASK 0x70
#घोषणा FW_VER_LOW_MASK  0x0f

/* Times to retry a ps2_command and millisecond delay between tries. */
#घोषणा CYTP_PS2_CMD_TRIES 3
#घोषणा CYTP_PS2_CMD_DELAY 500

/* समय out क्रम PS/2 command only in milliseconds. */
#घोषणा CYTP_CMD_TIMEOUT  200
#घोषणा CYTP_DATA_TIMEOUT 30

#घोषणा CYTP_EXT_CMD   0xe8
#घोषणा CYTP_PS2_RETRY 0xfe
#घोषणा CYTP_PS2_ERROR 0xfc

#घोषणा CYTP_RESP_RETRY 0x01
#घोषणा CYTP_RESP_ERROR 0xfe


#घोषणा CYTP_105001_WIDTH  97   /* Dell XPS 13 */
#घोषणा CYTP_105001_HIGH   59
#घोषणा CYTP_DEFAULT_WIDTH (CYTP_105001_WIDTH)
#घोषणा CYTP_DEFAULT_HIGH  (CYTP_105001_HIGH)

#घोषणा CYTP_ABS_MAX_X     1600
#घोषणा CYTP_ABS_MAX_Y     900
#घोषणा CYTP_MAX_PRESSURE  255
#घोषणा CYTP_MIN_PRESSURE  0

/* header byte bits of relative package. */
#घोषणा BTN_LEFT_BIT   0x01
#घोषणा BTN_RIGHT_BIT  0x02
#घोषणा BTN_MIDDLE_BIT 0x04
#घोषणा REL_X_SIGN_BIT 0x10
#घोषणा REL_Y_SIGN_BIT 0x20

/* header byte bits of असलolute package. */
#घोषणा ABS_VSCROLL_BIT 0x10
#घोषणा ABS_HSCROLL_BIT 0x20
#घोषणा ABS_MULTIFINGER_TAP 0x04
#घोषणा ABS_EDGE_MOTION_MASK 0x80

#घोषणा DFLT_RESP_BITS_VALID     0x88  /* SMBus bit should not be set. */
#घोषणा DFLT_RESP_SMBUS_BIT      0x80
#घोषणा   DFLT_SMBUS_MODE        0x80
#घोषणा   DFLT_PS2_MODE          0x00
#घोषणा DFLT_RESP_BIT_MODE       0x40
#घोषणा   DFLT_RESP_REMOTE_MODE  0x40
#घोषणा   DFLT_RESP_STREAM_MODE  0x00
#घोषणा DFLT_RESP_BIT_REPORTING  0x20
#घोषणा DFLT_RESP_BIT_SCALING    0x10

#घोषणा TP_METRICS_BIT_PALM               0x80
#घोषणा TP_METRICS_BIT_STUBBORN           0x40
#घोषणा TP_METRICS_BIT_2F_JITTER          0x30
#घोषणा TP_METRICS_BIT_1F_JITTER          0x0c
#घोषणा TP_METRICS_BIT_APA                0x02
#घोषणा TP_METRICS_BIT_MTG                0x01
#घोषणा TP_METRICS_BIT_ABS_PKT_FORMAT_SET 0xf0
#घोषणा TP_METRICS_BIT_2F_SPIKE           0x0c
#घोषणा TP_METRICS_BIT_1F_SPIKE           0x03

/* bits of first byte response of E9h-Status Request command. */
#घोषणा RESP_BTN_RIGHT_BIT  0x01
#घोषणा RESP_BTN_MIDDLE_BIT 0x02
#घोषणा RESP_BTN_LEFT_BIT   0x04
#घोषणा RESP_SCALING_BIT    0x10
#घोषणा RESP_ENABLE_BIT     0x20
#घोषणा RESP_REMOTE_BIT     0x40
#घोषणा RESP_SMBUS_BIT      0x80

#घोषणा CYTP_MAX_MT_SLOTS 2

काष्ठा cytp_contact अणु
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक z;  /* also named as touch pressure. */
पूर्ण;

/* The काष्ठाure of Cypress Trackpad event data. */
काष्ठा cytp_report_data अणु
	पूर्णांक contact_cnt;
	काष्ठा cytp_contact contacts[CYTP_MAX_MT_SLOTS];
	अचिन्हित पूर्णांक left:1;
	अचिन्हित पूर्णांक right:1;
	अचिन्हित पूर्णांक middle:1;
	अचिन्हित पूर्णांक tap:1;  /* multi-finger tap detected. */
पूर्ण;

/* The काष्ठाure of Cypress Trackpad device निजी data. */
काष्ठा cytp_data अणु
	पूर्णांक fw_version;

	पूर्णांक pkt_size;
	पूर्णांक mode;

	पूर्णांक tp_min_pressure;
	पूर्णांक tp_max_pressure;
	पूर्णांक tp_width;  /* X direction physical size in mm. */
	पूर्णांक tp_high;  /* Y direction physical size in mm. */
	पूर्णांक tp_max_असल_x;  /* Max X असलolute units that can be reported. */
	पूर्णांक tp_max_असल_y;  /* Max Y असलolute units that can be reported. */

	पूर्णांक tp_res_x;  /* X resolution in units/mm. */
	पूर्णांक tp_res_y;  /* Y resolution in units/mm. */

	पूर्णांक tp_metrics_supported;
पूर्ण;


पूर्णांक cypress_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक cypress_init(काष्ठा psmouse *psmouse);

#पूर्ण_अगर  /* _CYPRESS_PS2_H */
