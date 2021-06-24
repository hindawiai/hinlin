<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PSMOUSE_H
#घोषणा _PSMOUSE_H

#घोषणा PSMOUSE_OOB_NONE	0x00
#घोषणा PSMOUSE_OOB_EXTRA_BTNS	0x01

#घोषणा PSMOUSE_CMD_SETSCALE11	0x00e6
#घोषणा PSMOUSE_CMD_SETSCALE21	0x00e7
#घोषणा PSMOUSE_CMD_SETRES	0x10e8
#घोषणा PSMOUSE_CMD_GETINFO	0x03e9
#घोषणा PSMOUSE_CMD_SETSTREAM	0x00ea
#घोषणा PSMOUSE_CMD_SETPOLL	0x00f0
#घोषणा PSMOUSE_CMD_POLL	0x00eb	/* caller sets number of bytes to receive */
#घोषणा PSMOUSE_CMD_RESET_WRAP	0x00ec
#घोषणा PSMOUSE_CMD_GETID	0x02f2
#घोषणा PSMOUSE_CMD_SETRATE	0x10f3
#घोषणा PSMOUSE_CMD_ENABLE	0x00f4
#घोषणा PSMOUSE_CMD_DISABLE	0x00f5
#घोषणा PSMOUSE_CMD_RESET_DIS	0x00f6
#घोषणा PSMOUSE_CMD_RESET_BAT	0x02ff

#घोषणा PSMOUSE_RET_BAT		0xaa
#घोषणा PSMOUSE_RET_ID		0x00
#घोषणा PSMOUSE_RET_ACK		0xfa
#घोषणा PSMOUSE_RET_NAK		0xfe

क्रमागत psmouse_state अणु
	PSMOUSE_IGNORE,
	PSMOUSE_INITIALIZING,
	PSMOUSE_RESYNCING,
	PSMOUSE_CMD_MODE,
	PSMOUSE_ACTIVATED,
पूर्ण;

/* psmouse protocol handler वापस codes */
प्रकार क्रमागत अणु
	PSMOUSE_BAD_DATA,
	PSMOUSE_GOOD_DATA,
	PSMOUSE_FULL_PACKET
पूर्ण psmouse_ret_t;

क्रमागत psmouse_scale अणु
	PSMOUSE_SCALE11,
	PSMOUSE_SCALE21
पूर्ण;

क्रमागत psmouse_type अणु
	PSMOUSE_NONE,
	PSMOUSE_PS2,
	PSMOUSE_PS2PP,
	PSMOUSE_THINKPS,
	PSMOUSE_GENPS,
	PSMOUSE_IMPS,
	PSMOUSE_IMEX,
	PSMOUSE_SYNAPTICS,
	PSMOUSE_ALPS,
	PSMOUSE_LIFEBOOK,
	PSMOUSE_TRACKPOINT,
	PSMOUSE_TOUCHKIT_PS2,
	PSMOUSE_CORTRON,
	PSMOUSE_HGPK,
	PSMOUSE_ELANTECH,
	PSMOUSE_FSP,
	PSMOUSE_SYNAPTICS_RELATIVE,
	PSMOUSE_CYPRESS,
	PSMOUSE_FOCALTECH,
	PSMOUSE_VMMOUSE,
	PSMOUSE_BYD,
	PSMOUSE_SYNAPTICS_SMBUS,
	PSMOUSE_ELANTECH_SMBUS,
	PSMOUSE_AUTO		/* This one should always be last */
पूर्ण;

काष्ठा psmouse;

काष्ठा psmouse_protocol अणु
	क्रमागत psmouse_type type;
	bool maxproto;
	bool ignore_parity; /* Protocol should ignore parity errors from KBC */
	bool try_passthru; /* Try protocol also on passthrough ports */
	bool smbus_companion; /* "Protocol" is a stub, device is on SMBus */
	स्थिर अक्षर *name;
	स्थिर अक्षर *alias;
	पूर्णांक (*detect)(काष्ठा psmouse *, bool);
	पूर्णांक (*init)(काष्ठा psmouse *);
पूर्ण;

काष्ठा psmouse अणु
	व्योम *निजी;
	काष्ठा input_dev *dev;
	काष्ठा ps2dev ps2dev;
	काष्ठा delayed_work resync_work;
	स्थिर अक्षर *venकरोr;
	स्थिर अक्षर *name;
	स्थिर काष्ठा psmouse_protocol *protocol;
	अचिन्हित अक्षर packet[8];
	अचिन्हित अक्षर badbyte;
	अचिन्हित अक्षर pktcnt;
	अचिन्हित अक्षर pktsize;
	अचिन्हित अक्षर oob_data_type;
	अचिन्हित अक्षर extra_buttons;
	bool acks_disable_command;
	अचिन्हित पूर्णांक model;
	अचिन्हित दीर्घ last;
	अचिन्हित दीर्घ out_of_sync_cnt;
	अचिन्हित दीर्घ num_resyncs;
	क्रमागत psmouse_state state;
	अक्षर devname[64];
	अक्षर phys[32];

	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक resolution;
	अचिन्हित पूर्णांक resetafter;
	अचिन्हित पूर्णांक resync_समय;
	bool smartscroll;	/* Logitech only */

	psmouse_ret_t (*protocol_handler)(काष्ठा psmouse *psmouse);
	व्योम (*set_rate)(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate);
	व्योम (*set_resolution)(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक resolution);
	व्योम (*set_scale)(काष्ठा psmouse *psmouse, क्रमागत psmouse_scale scale);

	पूर्णांक (*reconnect)(काष्ठा psmouse *psmouse);
	पूर्णांक (*fast_reconnect)(काष्ठा psmouse *psmouse);
	व्योम (*disconnect)(काष्ठा psmouse *psmouse);
	व्योम (*cleanup)(काष्ठा psmouse *psmouse);
	पूर्णांक (*poll)(काष्ठा psmouse *psmouse);

	व्योम (*pt_activate)(काष्ठा psmouse *psmouse);
	व्योम (*pt_deactivate)(काष्ठा psmouse *psmouse);
पूर्ण;

व्योम psmouse_queue_work(काष्ठा psmouse *psmouse, काष्ठा delayed_work *work,
		अचिन्हित दीर्घ delay);
पूर्णांक psmouse_reset(काष्ठा psmouse *psmouse);
व्योम psmouse_set_state(काष्ठा psmouse *psmouse, क्रमागत psmouse_state new_state);
व्योम psmouse_set_resolution(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक resolution);
psmouse_ret_t psmouse_process_byte(काष्ठा psmouse *psmouse);
पूर्णांक psmouse_activate(काष्ठा psmouse *psmouse);
पूर्णांक psmouse_deactivate(काष्ठा psmouse *psmouse);
bool psmouse_matches_pnp_id(काष्ठा psmouse *psmouse, स्थिर अक्षर * स्थिर ids[]);

व्योम psmouse_report_standard_buttons(काष्ठा input_dev *, u8 buttons);
व्योम psmouse_report_standard_motion(काष्ठा input_dev *, u8 *packet);
व्योम psmouse_report_standard_packet(काष्ठा input_dev *, u8 *packet);

काष्ठा psmouse_attribute अणु
	काष्ठा device_attribute dattr;
	व्योम *data;
	sमाप_प्रकार (*show)(काष्ठा psmouse *psmouse, व्योम *data, अक्षर *buf);
	sमाप_प्रकार (*set)(काष्ठा psmouse *psmouse, व्योम *data,
			स्थिर अक्षर *buf, माप_प्रकार count);
	bool protect;
पूर्ण;
#घोषणा to_psmouse_attr(a)	container_of((a), काष्ठा psmouse_attribute, dattr)

sमाप_प्रकार psmouse_attr_show_helper(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 अक्षर *buf);
sमाप_प्रकार psmouse_attr_set_helper(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count);

#घोषणा __PSMOUSE_DEFINE_ATTR_VAR(_name, _mode, _data, _show, _set, _protect)	\
अटल काष्ठा psmouse_attribute psmouse_attr_##_name = अणु			\
	.dattr	= अणु								\
		.attr	= अणु							\
			.name	= __stringअगरy(_name),				\
			.mode	= _mode,					\
		पूर्ण,								\
		.show	= psmouse_attr_show_helper,				\
		.store	= psmouse_attr_set_helper,				\
	पूर्ण,									\
	.data	= _data,							\
	.show	= _show,							\
	.set	= _set,								\
	.protect = _protect,							\
पूर्ण

#घोषणा __PSMOUSE_DEFINE_ATTR(_name, _mode, _data, _show, _set, _protect)	\
	अटल sमाप_प्रकार _show(काष्ठा psmouse *, व्योम *, अक्षर *);			\
	अटल sमाप_प्रकार _set(काष्ठा psmouse *, व्योम *, स्थिर अक्षर *, माप_प्रकार);	\
	__PSMOUSE_DEFINE_ATTR_VAR(_name, _mode, _data, _show, _set, _protect)

#घोषणा PSMOUSE_DEFINE_ATTR(_name, _mode, _data, _show, _set)			\
	__PSMOUSE_DEFINE_ATTR(_name, _mode, _data, _show, _set, true)

#घोषणा PSMOUSE_DEFINE_RO_ATTR(_name, _mode, _data, _show)			\
	अटल sमाप_प्रकार _show(काष्ठा psmouse *, व्योम *, अक्षर *);			\
	__PSMOUSE_DEFINE_ATTR_VAR(_name, _mode, _data, _show, शून्य, true)

#घोषणा PSMOUSE_DEFINE_WO_ATTR(_name, _mode, _data, _set)			\
	अटल sमाप_प्रकार _set(काष्ठा psmouse *, व्योम *, स्थिर अक्षर *, माप_प्रकार);	\
	__PSMOUSE_DEFINE_ATTR_VAR(_name, _mode, _data, शून्य, _set, true)

#अगर_अघोषित psmouse_fmt
#घोषणा psmouse_fmt(fmt)	KBUILD_BASENAME ": " fmt
#पूर्ण_अगर

#घोषणा psmouse_dbg(psmouse, क्रमmat, ...)		\
	dev_dbg(&(psmouse)->ps2dev.serio->dev,		\
		psmouse_fmt(क्रमmat), ##__VA_ARGS__)
#घोषणा psmouse_info(psmouse, क्रमmat, ...)		\
	dev_info(&(psmouse)->ps2dev.serio->dev,		\
		 psmouse_fmt(क्रमmat), ##__VA_ARGS__)
#घोषणा psmouse_warn(psmouse, क्रमmat, ...)		\
	dev_warn(&(psmouse)->ps2dev.serio->dev,		\
		 psmouse_fmt(क्रमmat), ##__VA_ARGS__)
#घोषणा psmouse_err(psmouse, क्रमmat, ...)		\
	dev_err(&(psmouse)->ps2dev.serio->dev,		\
		psmouse_fmt(क्रमmat), ##__VA_ARGS__)
#घोषणा psmouse_notice(psmouse, क्रमmat, ...)		\
	dev_notice(&(psmouse)->ps2dev.serio->dev,	\
		   psmouse_fmt(क्रमmat), ##__VA_ARGS__)
#घोषणा psmouse_prपूर्णांकk(level, psmouse, क्रमmat, ...)	\
	dev_prपूर्णांकk(level,				\
		   &(psmouse)->ps2dev.serio->dev,	\
		   psmouse_fmt(क्रमmat), ##__VA_ARGS__)

#अगर_घोषित CONFIG_MOUSE_PS2_SMBUS

पूर्णांक psmouse_smbus_module_init(व्योम);
व्योम psmouse_smbus_module_निकास(व्योम);

काष्ठा i2c_board_info;

पूर्णांक psmouse_smbus_init(काष्ठा psmouse *psmouse,
		       स्थिर काष्ठा i2c_board_info *board,
		       स्थिर व्योम *pdata, माप_प्रकार pdata_size,
		       bool need_deactivate,
		       bool leave_bपढ़ोcrumbs);
व्योम psmouse_smbus_cleanup(काष्ठा psmouse *psmouse);

#अन्यथा /* !CONFIG_MOUSE_PS2_SMBUS */

अटल अंतरभूत पूर्णांक psmouse_smbus_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम psmouse_smbus_module_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम psmouse_smbus_cleanup(काष्ठा psmouse *psmouse)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MOUSE_PS2_SMBUS */

#पूर्ण_अगर /* _PSMOUSE_H */
