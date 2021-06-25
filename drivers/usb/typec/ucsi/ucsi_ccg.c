<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UCSI driver क्रम Cypress CCGx Type-C controller
 *
 * Copyright (C) 2017-2018 NVIDIA Corporation. All rights reserved.
 * Author: Ajay Gupta <ajayg@nvidia.com>
 *
 * Some code borrowed from drivers/usb/typec/ucsi/ucsi_acpi.c
 */
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/usb/typec_dp.h>

#समावेश <यंत्र/unaligned.h>
#समावेश "ucsi.h"

क्रमागत क्रमागत_fw_mode अणु
	BOOT,   /* bootloader */
	FW1,    /* FW partition-1 (contains secondary fw) */
	FW2,    /* FW partition-2 (contains primary fw) */
	FW_INVALID,
पूर्ण;

#घोषणा CCGX_RAB_DEVICE_MODE			0x0000
#घोषणा CCGX_RAB_INTR_REG			0x0006
#घोषणा  DEV_INT				BIT(0)
#घोषणा  PORT0_INT				BIT(1)
#घोषणा  PORT1_INT				BIT(2)
#घोषणा  UCSI_READ_INT				BIT(7)
#घोषणा CCGX_RAB_JUMP_TO_BOOT			0x0007
#घोषणा  TO_BOOT				'J'
#घोषणा  TO_ALT_FW				'A'
#घोषणा CCGX_RAB_RESET_REQ			0x0008
#घोषणा  RESET_SIG				'R'
#घोषणा  CMD_RESET_I2C				0x0
#घोषणा  CMD_RESET_DEV				0x1
#घोषणा CCGX_RAB_ENTER_FLASHING			0x000A
#घोषणा  FLASH_ENTER_SIG			'P'
#घोषणा CCGX_RAB_VALIDATE_FW			0x000B
#घोषणा CCGX_RAB_FLASH_ROW_RW			0x000C
#घोषणा  FLASH_SIG				'F'
#घोषणा  FLASH_RD_CMD				0x0
#घोषणा  FLASH_WR_CMD				0x1
#घोषणा  FLASH_FWCT1_WR_CMD			0x2
#घोषणा  FLASH_FWCT2_WR_CMD			0x3
#घोषणा  FLASH_FWCT_SIG_WR_CMD			0x4
#घोषणा CCGX_RAB_READ_ALL_VER			0x0010
#घोषणा CCGX_RAB_READ_FW2_VER			0x0020
#घोषणा CCGX_RAB_UCSI_CONTROL			0x0039
#घोषणा CCGX_RAB_UCSI_CONTROL_START		BIT(0)
#घोषणा CCGX_RAB_UCSI_CONTROL_STOP		BIT(1)
#घोषणा CCGX_RAB_UCSI_DATA_BLOCK(offset)	(0xf000 | ((offset) & 0xff))
#घोषणा REG_FLASH_RW_MEM        0x0200
#घोषणा DEV_REG_IDX				CCGX_RAB_DEVICE_MODE
#घोषणा CCGX_RAB_PDPORT_ENABLE			0x002C
#घोषणा  PDPORT_1		BIT(0)
#घोषणा  PDPORT_2		BIT(1)
#घोषणा CCGX_RAB_RESPONSE			0x007E
#घोषणा  ASYNC_EVENT				BIT(7)

/* CCGx events & async msg codes */
#घोषणा RESET_COMPLETE		0x80
#घोषणा EVENT_INDEX		RESET_COMPLETE
#घोषणा PORT_CONNECT_DET	0x84
#घोषणा PORT_DISCONNECT_DET	0x85
#घोषणा ROLE_SWAP_COMPELETE	0x87

/* ccg firmware */
#घोषणा CYACD_LINE_SIZE         527
#घोषणा CCG4_ROW_SIZE           256
#घोषणा FW1_METADATA_ROW        0x1FF
#घोषणा FW2_METADATA_ROW        0x1FE
#घोषणा FW_CFG_TABLE_SIG_SIZE	256

अटल पूर्णांक secondary_fw_min_ver = 41;

क्रमागत क्रमागत_flash_mode अणु
	SECONDARY_BL,	/* update secondary using bootloader */
	PRIMARY,	/* update primary using secondary */
	SECONDARY,	/* update secondary using primary */
	FLASH_NOT_NEEDED,	/* update not required */
	FLASH_INVALID,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ccg_fw_names[] = अणु
	"ccg_boot.cyacd",
	"ccg_primary.cyacd",
	"ccg_secondary.cyacd"
पूर्ण;

काष्ठा ccg_dev_info अणु
#घोषणा CCG_DEVINFO_FWMODE_SHIFT (0)
#घोषणा CCG_DEVINFO_FWMODE_MASK (0x3 << CCG_DEVINFO_FWMODE_SHIFT)
#घोषणा CCG_DEVINFO_PDPORTS_SHIFT (2)
#घोषणा CCG_DEVINFO_PDPORTS_MASK (0x3 << CCG_DEVINFO_PDPORTS_SHIFT)
	u8 mode;
	u8 bl_mode;
	__le16 silicon_id;
	__le16 bl_last_row;
पूर्ण __packed;

काष्ठा version_क्रमmat अणु
	__le16 build;
	u8 patch;
	u8 ver;
#घोषणा CCG_VERSION_PATCH(x) ((x) << 16)
#घोषणा CCG_VERSION(x)	((x) << 24)
#घोषणा CCG_VERSION_MIN_SHIFT (0)
#घोषणा CCG_VERSION_MIN_MASK (0xf << CCG_VERSION_MIN_SHIFT)
#घोषणा CCG_VERSION_MAJ_SHIFT (4)
#घोषणा CCG_VERSION_MAJ_MASK (0xf << CCG_VERSION_MAJ_SHIFT)
पूर्ण __packed;

/*
 * Firmware version 3.1.10 or earlier, built क्रम NVIDIA has known issue
 * of missing पूर्णांकerrupt when a device is connected क्रम runसमय resume
 */
#घोषणा CCG_FW_BUILD_NVIDIA	(('n' << 8) | 'v')
#घोषणा CCG_OLD_FW_VERSION	(CCG_VERSION(0x31) | CCG_VERSION_PATCH(10))

/* Alपंचांगode offset क्रम NVIDIA Function Test Board (FTB) */
#घोषणा NVIDIA_FTB_DP_OFFSET	(2)
#घोषणा NVIDIA_FTB_DBG_OFFSET	(3)

काष्ठा version_info अणु
	काष्ठा version_क्रमmat base;
	काष्ठा version_क्रमmat app;
पूर्ण;

काष्ठा fw_config_table अणु
	u32 identity;
	u16 table_size;
	u8 fwct_version;
	u8 is_key_change;
	u8 guid[16];
	काष्ठा version_क्रमmat base;
	काष्ठा version_क्रमmat app;
	u8 primary_fw_digest[32];
	u32 key_exp_length;
	u8 key_modulus[256];
	u8 key_exp[4];
पूर्ण;

/* CCGx response codes */
क्रमागत ccg_resp_code अणु
	CMD_NO_RESP             = 0x00,
	CMD_SUCCESS             = 0x02,
	FLASH_DATA_AVAILABLE    = 0x03,
	CMD_INVALID             = 0x05,
	FLASH_UPDATE_FAIL       = 0x07,
	INVALID_FW              = 0x08,
	INVALID_ARG             = 0x09,
	CMD_NOT_SUPPORT         = 0x0A,
	TRANSACTION_FAIL        = 0x0C,
	PD_CMD_FAIL             = 0x0D,
	UNDEF_ERROR             = 0x0F,
	INVALID_RESP		= 0x10,
पूर्ण;

#घोषणा CCG_EVENT_MAX	(EVENT_INDEX + 43)

काष्ठा ccg_cmd अणु
	u16 reg;
	u32 data;
	पूर्णांक len;
	u32 delay; /* ms delay क्रम cmd समयout  */
पूर्ण;

काष्ठा ccg_resp अणु
	u8 code;
	u8 length;
पूर्ण;

काष्ठा ucsi_ccg_alपंचांगode अणु
	u16 svid;
	u32 mid;
	u8 linked_idx;
	u8 active_idx;
#घोषणा UCSI_MULTI_DP_INDEX	(0xff)
	bool checked;
पूर्ण __packed;

काष्ठा ucsi_ccg अणु
	काष्ठा device *dev;
	काष्ठा ucsi *ucsi;
	काष्ठा i2c_client *client;

	काष्ठा ccg_dev_info info;
	/* version info क्रम boot, primary and secondary */
	काष्ठा version_info version[FW2 + 1];
	u32 fw_version;
	/* CCG HPI communication flags */
	अचिन्हित दीर्घ flags;
#घोषणा RESET_PENDING	0
#घोषणा DEV_CMD_PENDING	1
	काष्ठा ccg_resp dev_resp;
	u8 cmd_resp;
	पूर्णांक port_num;
	पूर्णांक irq;
	काष्ठा work_काष्ठा work;
	काष्ठा mutex lock; /* to sync between user and driver thपढ़ो */

	/* fw build with venकरोr inक्रमmation */
	u16 fw_build;
	काष्ठा work_काष्ठा pm_work;

	काष्ठा completion complete;

	u64 last_cmd_sent;
	bool has_multiple_dp;
	काष्ठा ucsi_ccg_alपंचांगode orig[UCSI_MAX_ALTMODES];
	काष्ठा ucsi_ccg_alपंचांगode updated[UCSI_MAX_ALTMODES];
पूर्ण;

अटल पूर्णांक ccg_पढ़ो(काष्ठा ucsi_ccg *uc, u16 rab, u8 *data, u32 len)
अणु
	काष्ठा i2c_client *client = uc->client;
	स्थिर काष्ठा i2c_adapter_quirks *quirks = client->adapter->quirks;
	अचिन्हित अक्षर buf[2];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags  = 0x0,
			.len	= माप(buf),
			.buf	= buf,
		पूर्ण,
		अणु
			.addr	= client->addr,
			.flags  = I2C_M_RD,
			.buf	= data,
		पूर्ण,
	पूर्ण;
	u32 rlen, rem_len = len, max_पढ़ो_len = len;
	पूर्णांक status;

	/* check any max_पढ़ो_len limitation on i2c adapter */
	अगर (quirks && quirks->max_पढ़ो_len)
		max_पढ़ो_len = quirks->max_पढ़ो_len;

	pm_runसमय_get_sync(uc->dev);
	जबतक (rem_len > 0) अणु
		msgs[1].buf = &data[len - rem_len];
		rlen = min_t(u16, rem_len, max_पढ़ो_len);
		msgs[1].len = rlen;
		put_unaligned_le16(rab, buf);
		status = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
		अगर (status < 0) अणु
			dev_err(uc->dev, "i2c_transfer failed %d\n", status);
			pm_runसमय_put_sync(uc->dev);
			वापस status;
		पूर्ण
		rab += rlen;
		rem_len -= rlen;
	पूर्ण

	pm_runसमय_put_sync(uc->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ccg_ग_लिखो(काष्ठा ucsi_ccg *uc, u16 rab, स्थिर u8 *data, u32 len)
अणु
	काष्ठा i2c_client *client = uc->client;
	अचिन्हित अक्षर *buf;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags  = 0x0,
		पूर्ण
	पूर्ण;
	पूर्णांक status;

	buf = kzalloc(len + माप(rab), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	put_unaligned_le16(rab, buf);
	स_नकल(buf + माप(rab), data, len);

	msgs[0].len = len + माप(rab);
	msgs[0].buf = buf;

	pm_runसमय_get_sync(uc->dev);
	status = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (status < 0) अणु
		dev_err(uc->dev, "i2c_transfer failed %d\n", status);
		pm_runसमय_put_sync(uc->dev);
		kमुक्त(buf);
		वापस status;
	पूर्ण

	pm_runसमय_put_sync(uc->dev);
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_ccg_init(काष्ठा ucsi_ccg *uc)
अणु
	अचिन्हित पूर्णांक count = 10;
	u8 data;
	पूर्णांक status;

	data = CCGX_RAB_UCSI_CONTROL_STOP;
	status = ccg_ग_लिखो(uc, CCGX_RAB_UCSI_CONTROL, &data, माप(data));
	अगर (status < 0)
		वापस status;

	data = CCGX_RAB_UCSI_CONTROL_START;
	status = ccg_ग_लिखो(uc, CCGX_RAB_UCSI_CONTROL, &data, माप(data));
	अगर (status < 0)
		वापस status;

	/*
	 * Flush CCGx RESPONSE queue by acking पूर्णांकerrupts. Above ucsi control
	 * रेजिस्टर ग_लिखो will push response which must be cleared.
	 */
	करो अणु
		status = ccg_पढ़ो(uc, CCGX_RAB_INTR_REG, &data, माप(data));
		अगर (status < 0)
			वापस status;

		अगर (!data)
			वापस 0;

		status = ccg_ग_लिखो(uc, CCGX_RAB_INTR_REG, &data, माप(data));
		अगर (status < 0)
			वापस status;

		usleep_range(10000, 11000);
	पूर्ण जबतक (--count);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम ucsi_ccg_update_get_current_cam_cmd(काष्ठा ucsi_ccg *uc, u8 *data)
अणु
	u8 cam, new_cam;

	cam = data[0];
	new_cam = uc->orig[cam].linked_idx;
	uc->updated[new_cam].active_idx = cam;
	data[0] = new_cam;
पूर्ण

अटल bool ucsi_ccg_update_alपंचांगodes(काष्ठा ucsi *ucsi,
				     काष्ठा ucsi_alपंचांगode *orig,
				     काष्ठा ucsi_alपंचांगode *updated)
अणु
	काष्ठा ucsi_ccg *uc = ucsi_get_drvdata(ucsi);
	काष्ठा ucsi_ccg_alपंचांगode *alt, *new_alt;
	पूर्णांक i, j, k = 0;
	bool found = false;

	alt = uc->orig;
	new_alt = uc->updated;
	स_रखो(uc->updated, 0, माप(uc->updated));

	/*
	 * Copy original connector alपंचांगodes to new काष्ठाure.
	 * We need this beक्रमe second loop since second loop
	 * checks क्रम duplicate alपंचांगodes.
	 */
	क्रम (i = 0; i < UCSI_MAX_ALTMODES; i++) अणु
		alt[i].svid = orig[i].svid;
		alt[i].mid = orig[i].mid;
		अगर (!alt[i].svid)
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < UCSI_MAX_ALTMODES; i++) अणु
		अगर (!alt[i].svid)
			अवरोध;

		/* alपढ़ोy checked and considered */
		अगर (alt[i].checked)
			जारी;

		अगर (!DP_CONF_GET_PIN_ASSIGN(alt[i].mid)) अणु
			/* Found Non DP alपंचांगode */
			new_alt[k].svid = alt[i].svid;
			new_alt[k].mid |= alt[i].mid;
			new_alt[k].linked_idx = i;
			alt[i].linked_idx = k;
			updated[k].svid = new_alt[k].svid;
			updated[k].mid = new_alt[k].mid;
			k++;
			जारी;
		पूर्ण

		क्रम (j = i + 1; j < UCSI_MAX_ALTMODES; j++) अणु
			अगर (alt[i].svid != alt[j].svid ||
			    !DP_CONF_GET_PIN_ASSIGN(alt[j].mid)) अणु
				जारी;
			पूर्ण अन्यथा अणु
				/* Found duplicate DP mode */
				new_alt[k].svid = alt[i].svid;
				new_alt[k].mid |= alt[i].mid | alt[j].mid;
				new_alt[k].linked_idx = UCSI_MULTI_DP_INDEX;
				alt[i].linked_idx = k;
				alt[j].linked_idx = k;
				alt[j].checked = true;
				found = true;
			पूर्ण
		पूर्ण
		अगर (found) अणु
			uc->has_multiple_dp = true;
		पूर्ण अन्यथा अणु
			/* Didn't find any duplicate DP alपंचांगode */
			new_alt[k].svid = alt[i].svid;
			new_alt[k].mid |= alt[i].mid;
			new_alt[k].linked_idx = i;
			alt[i].linked_idx = k;
		पूर्ण
		updated[k].svid = new_alt[k].svid;
		updated[k].mid = new_alt[k].mid;
		k++;
	पूर्ण
	वापस found;
पूर्ण

अटल व्योम ucsi_ccg_update_set_new_cam_cmd(काष्ठा ucsi_ccg *uc,
					    काष्ठा ucsi_connector *con,
					    u64 *cmd)
अणु
	काष्ठा ucsi_ccg_alपंचांगode *new_port, *port;
	काष्ठा typec_alपंचांगode *alt = शून्य;
	u8 new_cam, cam, pin;
	bool enter_new_mode;
	पूर्णांक i, j, k = 0xff;

	port = uc->orig;
	new_cam = UCSI_SET_NEW_CAM_GET_AM(*cmd);
	new_port = &uc->updated[new_cam];
	cam = new_port->linked_idx;
	enter_new_mode = UCSI_SET_NEW_CAM_ENTER(*cmd);

	/*
	 * If CAM is UCSI_MULTI_DP_INDEX then this is DP alपंचांगode
	 * with multiple DP mode. Find out CAM क्रम best pin assignment
	 * among all DP mode. Priorite pin E->D->C after making sure
	 * the partner supports that pin.
	 */
	अगर (cam == UCSI_MULTI_DP_INDEX) अणु
		अगर (enter_new_mode) अणु
			क्रम (i = 0; con->partner_alपंचांगode[i]; i++) अणु
				alt = con->partner_alपंचांगode[i];
				अगर (alt->svid == new_port->svid)
					अवरोध;
			पूर्ण
			/*
			 * alt will always be non शून्य since this is
			 * UCSI_SET_NEW_CAM command and so there will be
			 * at least one con->partner_alपंचांगode[i] with svid
			 * matching with new_port->svid.
			 */
			क्रम (j = 0; port[j].svid; j++) अणु
				pin = DP_CONF_GET_PIN_ASSIGN(port[j].mid);
				अगर (alt && port[j].svid == alt->svid &&
				    (pin & DP_CONF_GET_PIN_ASSIGN(alt->vकरो))) अणु
					/* prioritize pin E->D->C */
					अगर (k == 0xff || (k != 0xff && pin >
					    DP_CONF_GET_PIN_ASSIGN(port[k].mid))
					    ) अणु
						k = j;
					पूर्ण
				पूर्ण
			पूर्ण
			cam = k;
			new_port->active_idx = cam;
		पूर्ण अन्यथा अणु
			cam = new_port->active_idx;
		पूर्ण
	पूर्ण
	*cmd &= ~UCSI_SET_NEW_CAM_AM_MASK;
	*cmd |= UCSI_SET_NEW_CAM_SET_AM(cam);
पूर्ण

/*
 * Change the order of vकरो values of NVIDIA test device FTB
 * (Function Test Board) which reports alपंचांगode list with vकरो=0x3
 * first and then vकरो=0x. Current logic to assign mode value is
 * based on order in alपंचांगode list and it causes a mismatch of CON
 * and SOP alपंचांगodes since NVIDIA GPU connector has order of vकरो=0x1
 * first and then vकरो=0x3
 */
अटल व्योम ucsi_ccg_nvidia_alपंचांगode(काष्ठा ucsi_ccg *uc,
				    काष्ठा ucsi_alपंचांगode *alt)
अणु
	चयन (UCSI_ALTMODE_OFFSET(uc->last_cmd_sent)) अणु
	हाल NVIDIA_FTB_DP_OFFSET:
		अगर (alt[0].mid == USB_TYPEC_NVIDIA_VLINK_DBG_VDO)
			alt[0].mid = USB_TYPEC_NVIDIA_VLINK_DP_VDO |
				DP_CAP_DP_SIGNALING | DP_CAP_USB |
				DP_CONF_SET_PIN_ASSIGN(BIT(DP_PIN_ASSIGN_E));
		अवरोध;
	हाल NVIDIA_FTB_DBG_OFFSET:
		अगर (alt[0].mid == USB_TYPEC_NVIDIA_VLINK_DP_VDO)
			alt[0].mid = USB_TYPEC_NVIDIA_VLINK_DBG_VDO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ucsi_ccg_पढ़ो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
			 व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा ucsi_ccg *uc = ucsi_get_drvdata(ucsi);
	u16 reg = CCGX_RAB_UCSI_DATA_BLOCK(offset);
	काष्ठा ucsi_alपंचांगode *alt;
	पूर्णांक ret;

	ret = ccg_पढ़ो(uc, reg, val, val_len);
	अगर (ret)
		वापस ret;

	अगर (offset != UCSI_MESSAGE_IN)
		वापस ret;

	चयन (UCSI_COMMAND(uc->last_cmd_sent)) अणु
	हाल UCSI_GET_CURRENT_CAM:
		अगर (uc->has_multiple_dp)
			ucsi_ccg_update_get_current_cam_cmd(uc, (u8 *)val);
		अवरोध;
	हाल UCSI_GET_ALTERNATE_MODES:
		अगर (UCSI_ALTMODE_RECIPIENT(uc->last_cmd_sent) ==
		    UCSI_RECIPIENT_SOP) अणु
			alt = val;
			अगर (alt[0].svid == USB_TYPEC_NVIDIA_VLINK_SID)
				ucsi_ccg_nvidia_alपंचांगode(uc, alt);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	uc->last_cmd_sent = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक ucsi_ccg_async_ग_लिखो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
				स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	u16 reg = CCGX_RAB_UCSI_DATA_BLOCK(offset);

	वापस ccg_ग_लिखो(ucsi_get_drvdata(ucsi), reg, val, val_len);
पूर्ण

अटल पूर्णांक ucsi_ccg_sync_ग_लिखो(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
			       स्थिर व्योम *val, माप_प्रकार val_len)
अणु
	काष्ठा ucsi_ccg *uc = ucsi_get_drvdata(ucsi);
	काष्ठा ucsi_connector *con;
	पूर्णांक con_index;
	पूर्णांक ret;

	mutex_lock(&uc->lock);
	pm_runसमय_get_sync(uc->dev);
	set_bit(DEV_CMD_PENDING, &uc->flags);

	अगर (offset == UCSI_CONTROL && val_len == माप(uc->last_cmd_sent)) अणु
		uc->last_cmd_sent = *(u64 *)val;

		अगर (UCSI_COMMAND(uc->last_cmd_sent) == UCSI_SET_NEW_CAM &&
		    uc->has_multiple_dp) अणु
			con_index = (uc->last_cmd_sent >> 16) &
				    UCSI_CMD_CONNECTOR_MASK;
			con = &uc->ucsi->connector[con_index - 1];
			ucsi_ccg_update_set_new_cam_cmd(uc, con, (u64 *)val);
		पूर्ण
	पूर्ण

	ret = ucsi_ccg_async_ग_लिखो(ucsi, offset, val, val_len);
	अगर (ret)
		जाओ err_clear_bit;

	अगर (!रुको_क्रम_completion_समयout(&uc->complete, msecs_to_jअगरfies(5000)))
		ret = -ETIMEDOUT;

err_clear_bit:
	clear_bit(DEV_CMD_PENDING, &uc->flags);
	pm_runसमय_put_sync(uc->dev);
	mutex_unlock(&uc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ucsi_operations ucsi_ccg_ops = अणु
	.पढ़ो = ucsi_ccg_पढ़ो,
	.sync_ग_लिखो = ucsi_ccg_sync_ग_लिखो,
	.async_ग_लिखो = ucsi_ccg_async_ग_लिखो,
	.update_alपंचांगodes = ucsi_ccg_update_alपंचांगodes
पूर्ण;

अटल irqवापस_t ccg_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	u16 reg = CCGX_RAB_UCSI_DATA_BLOCK(UCSI_CCI);
	काष्ठा ucsi_ccg *uc = data;
	u8 पूर्णांकr_reg;
	u32 cci;
	पूर्णांक ret;

	ret = ccg_पढ़ो(uc, CCGX_RAB_INTR_REG, &पूर्णांकr_reg, माप(पूर्णांकr_reg));
	अगर (ret)
		वापस ret;

	ret = ccg_पढ़ो(uc, reg, (व्योम *)&cci, माप(cci));
	अगर (ret)
		जाओ err_clear_irq;

	अगर (UCSI_CCI_CONNECTOR(cci))
		ucsi_connector_change(uc->ucsi, UCSI_CCI_CONNECTOR(cci));

	अगर (test_bit(DEV_CMD_PENDING, &uc->flags) &&
	    cci & (UCSI_CCI_ACK_COMPLETE | UCSI_CCI_COMMAND_COMPLETE))
		complete(&uc->complete);

err_clear_irq:
	ccg_ग_लिखो(uc, CCGX_RAB_INTR_REG, &पूर्णांकr_reg, माप(पूर्णांकr_reg));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ccg_pm_workaround_work(काष्ठा work_काष्ठा *pm_work)
अणु
	ccg_irq_handler(0, container_of(pm_work, काष्ठा ucsi_ccg, pm_work));
पूर्ण

अटल पूर्णांक get_fw_info(काष्ठा ucsi_ccg *uc)
अणु
	पूर्णांक err;

	err = ccg_पढ़ो(uc, CCGX_RAB_READ_ALL_VER, (u8 *)(&uc->version),
		       माप(uc->version));
	अगर (err < 0)
		वापस err;

	uc->fw_version = CCG_VERSION(uc->version[FW2].app.ver) |
			CCG_VERSION_PATCH(uc->version[FW2].app.patch);

	err = ccg_पढ़ो(uc, CCGX_RAB_DEVICE_MODE, (u8 *)(&uc->info),
		       माप(uc->info));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल अंतरभूत bool invalid_async_evt(पूर्णांक code)
अणु
	वापस (code >= CCG_EVENT_MAX) || (code < EVENT_INDEX);
पूर्ण

अटल व्योम ccg_process_response(काष्ठा ucsi_ccg *uc)
अणु
	काष्ठा device *dev = uc->dev;

	अगर (uc->dev_resp.code & ASYNC_EVENT) अणु
		अगर (uc->dev_resp.code == RESET_COMPLETE) अणु
			अगर (test_bit(RESET_PENDING, &uc->flags))
				uc->cmd_resp = uc->dev_resp.code;
			get_fw_info(uc);
		पूर्ण
		अगर (invalid_async_evt(uc->dev_resp.code))
			dev_err(dev, "invalid async evt %d\n",
				uc->dev_resp.code);
	पूर्ण अन्यथा अणु
		अगर (test_bit(DEV_CMD_PENDING, &uc->flags)) अणु
			uc->cmd_resp = uc->dev_resp.code;
			clear_bit(DEV_CMD_PENDING, &uc->flags);
		पूर्ण अन्यथा अणु
			dev_err(dev, "dev resp 0x%04x but no cmd pending\n",
				uc->dev_resp.code);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ccg_पढ़ो_response(काष्ठा ucsi_ccg *uc)
अणु
	अचिन्हित दीर्घ target = jअगरfies + msecs_to_jअगरfies(1000);
	काष्ठा device *dev = uc->dev;
	u8 पूर्णांकval;
	पूर्णांक status;

	/* रुको क्रम पूर्णांकerrupt status to get updated */
	करो अणु
		status = ccg_पढ़ो(uc, CCGX_RAB_INTR_REG, &पूर्णांकval,
				  माप(पूर्णांकval));
		अगर (status < 0)
			वापस status;

		अगर (पूर्णांकval & DEV_INT)
			अवरोध;
		usleep_range(500, 600);
	पूर्ण जबतक (समय_is_after_jअगरfies(target));

	अगर (समय_is_beक्रमe_jअगरfies(target)) अणु
		dev_err(dev, "response timeout error\n");
		वापस -ETIME;
	पूर्ण

	status = ccg_पढ़ो(uc, CCGX_RAB_RESPONSE, (u8 *)&uc->dev_resp,
			  माप(uc->dev_resp));
	अगर (status < 0)
		वापस status;

	status = ccg_ग_लिखो(uc, CCGX_RAB_INTR_REG, &पूर्णांकval, माप(पूर्णांकval));
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

/* Caller must hold uc->lock */
अटल पूर्णांक ccg_send_command(काष्ठा ucsi_ccg *uc, काष्ठा ccg_cmd *cmd)
अणु
	काष्ठा device *dev = uc->dev;
	पूर्णांक ret;

	चयन (cmd->reg & 0xF000) अणु
	हाल DEV_REG_IDX:
		set_bit(DEV_CMD_PENDING, &uc->flags);
		अवरोध;
	शेष:
		dev_err(dev, "invalid cmd register\n");
		अवरोध;
	पूर्ण

	ret = ccg_ग_लिखो(uc, cmd->reg, (u8 *)&cmd->data, cmd->len);
	अगर (ret < 0)
		वापस ret;

	msleep(cmd->delay);

	ret = ccg_पढ़ो_response(uc);
	अगर (ret < 0) अणु
		dev_err(dev, "response read error\n");
		चयन (cmd->reg & 0xF000) अणु
		हाल DEV_REG_IDX:
			clear_bit(DEV_CMD_PENDING, &uc->flags);
			अवरोध;
		शेष:
			dev_err(dev, "invalid cmd register\n");
			अवरोध;
		पूर्ण
		वापस -EIO;
	पूर्ण
	ccg_process_response(uc);

	वापस uc->cmd_resp;
पूर्ण

अटल पूर्णांक ccg_cmd_enter_flashing(काष्ठा ucsi_ccg *uc)
अणु
	काष्ठा ccg_cmd cmd;
	पूर्णांक ret;

	cmd.reg = CCGX_RAB_ENTER_FLASHING;
	cmd.data = FLASH_ENTER_SIG;
	cmd.len = 1;
	cmd.delay = 50;

	mutex_lock(&uc->lock);

	ret = ccg_send_command(uc, &cmd);

	mutex_unlock(&uc->lock);

	अगर (ret != CMD_SUCCESS) अणु
		dev_err(uc->dev, "enter flashing failed ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccg_cmd_reset(काष्ठा ucsi_ccg *uc)
अणु
	काष्ठा ccg_cmd cmd;
	u8 *p;
	पूर्णांक ret;

	p = (u8 *)&cmd.data;
	cmd.reg = CCGX_RAB_RESET_REQ;
	p[0] = RESET_SIG;
	p[1] = CMD_RESET_DEV;
	cmd.len = 2;
	cmd.delay = 5000;

	mutex_lock(&uc->lock);

	set_bit(RESET_PENDING, &uc->flags);

	ret = ccg_send_command(uc, &cmd);
	अगर (ret != RESET_COMPLETE)
		जाओ err_clear_flag;

	ret = 0;

err_clear_flag:
	clear_bit(RESET_PENDING, &uc->flags);

	mutex_unlock(&uc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ccg_cmd_port_control(काष्ठा ucsi_ccg *uc, bool enable)
अणु
	काष्ठा ccg_cmd cmd;
	पूर्णांक ret;

	cmd.reg = CCGX_RAB_PDPORT_ENABLE;
	अगर (enable)
		cmd.data = (uc->port_num == 1) ?
			    PDPORT_1 : (PDPORT_1 | PDPORT_2);
	अन्यथा
		cmd.data = 0x0;
	cmd.len = 1;
	cmd.delay = 10;

	mutex_lock(&uc->lock);

	ret = ccg_send_command(uc, &cmd);

	mutex_unlock(&uc->lock);

	अगर (ret != CMD_SUCCESS) अणु
		dev_err(uc->dev, "port control failed ret=%d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ccg_cmd_jump_boot_mode(काष्ठा ucsi_ccg *uc, पूर्णांक bl_mode)
अणु
	काष्ठा ccg_cmd cmd;
	पूर्णांक ret;

	cmd.reg = CCGX_RAB_JUMP_TO_BOOT;

	अगर (bl_mode)
		cmd.data = TO_BOOT;
	अन्यथा
		cmd.data = TO_ALT_FW;

	cmd.len = 1;
	cmd.delay = 100;

	mutex_lock(&uc->lock);

	set_bit(RESET_PENDING, &uc->flags);

	ret = ccg_send_command(uc, &cmd);
	अगर (ret != RESET_COMPLETE)
		जाओ err_clear_flag;

	ret = 0;

err_clear_flag:
	clear_bit(RESET_PENDING, &uc->flags);

	mutex_unlock(&uc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
ccg_cmd_ग_लिखो_flash_row(काष्ठा ucsi_ccg *uc, u16 row,
			स्थिर व्योम *data, u8 fcmd)
अणु
	काष्ठा i2c_client *client = uc->client;
	काष्ठा ccg_cmd cmd;
	u8 buf[CCG4_ROW_SIZE + 2];
	u8 *p;
	पूर्णांक ret;

	/* Copy the data पूर्णांकo the flash पढ़ो/ग_लिखो memory. */
	put_unaligned_le16(REG_FLASH_RW_MEM, buf);

	स_नकल(buf + 2, data, CCG4_ROW_SIZE);

	mutex_lock(&uc->lock);

	ret = i2c_master_send(client, buf, CCG4_ROW_SIZE + 2);
	अगर (ret != CCG4_ROW_SIZE + 2) अणु
		dev_err(uc->dev, "REG_FLASH_RW_MEM write fail %d\n", ret);
		mutex_unlock(&uc->lock);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	/* Use the FLASH_ROW_READ_WRITE रेजिस्टर to trigger */
	/* writing of data to the desired flash row */
	p = (u8 *)&cmd.data;
	cmd.reg = CCGX_RAB_FLASH_ROW_RW;
	p[0] = FLASH_SIG;
	p[1] = fcmd;
	put_unaligned_le16(row, &p[2]);
	cmd.len = 4;
	cmd.delay = 50;
	अगर (fcmd == FLASH_FWCT_SIG_WR_CMD)
		cmd.delay += 400;
	अगर (row == 510)
		cmd.delay += 220;
	ret = ccg_send_command(uc, &cmd);

	mutex_unlock(&uc->lock);

	अगर (ret != CMD_SUCCESS) अणु
		dev_err(uc->dev, "write flash row failed ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccg_cmd_validate_fw(काष्ठा ucsi_ccg *uc, अचिन्हित पूर्णांक fwid)
अणु
	काष्ठा ccg_cmd cmd;
	पूर्णांक ret;

	cmd.reg = CCGX_RAB_VALIDATE_FW;
	cmd.data = fwid;
	cmd.len = 1;
	cmd.delay = 500;

	mutex_lock(&uc->lock);

	ret = ccg_send_command(uc, &cmd);

	mutex_unlock(&uc->lock);

	अगर (ret != CMD_SUCCESS)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool ccg_check_venकरोr_version(काष्ठा ucsi_ccg *uc,
				     काष्ठा version_क्रमmat *app,
				     काष्ठा fw_config_table *fw_cfg)
अणु
	काष्ठा device *dev = uc->dev;

	/* Check अगर the fw build is क्रम supported venकरोrs */
	अगर (le16_to_cpu(app->build) != uc->fw_build) अणु
		dev_info(dev, "current fw is not from supported vendor\n");
		वापस false;
	पूर्ण

	/* Check अगर the new fw build is क्रम supported venकरोrs */
	अगर (le16_to_cpu(fw_cfg->app.build) != uc->fw_build) अणु
		dev_info(dev, "new fw is not from supported vendor\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool ccg_check_fw_version(काष्ठा ucsi_ccg *uc, स्थिर अक्षर *fw_name,
				 काष्ठा version_क्रमmat *app)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा device *dev = uc->dev;
	काष्ठा fw_config_table fw_cfg;
	u32 cur_version, new_version;
	bool is_later = false;

	अगर (request_firmware(&fw, fw_name, dev) != 0) अणु
		dev_err(dev, "error: Failed to open cyacd file %s\n", fw_name);
		वापस false;
	पूर्ण

	/*
	 * check अगर चिन्हित fw
	 * last part of fw image is fw cfg table and signature
	 */
	अगर (fw->size < माप(fw_cfg) + FW_CFG_TABLE_SIG_SIZE)
		जाओ out_release_firmware;

	स_नकल((uपूर्णांक8_t *)&fw_cfg, fw->data + fw->size -
	       माप(fw_cfg) - FW_CFG_TABLE_SIG_SIZE, माप(fw_cfg));

	अगर (fw_cfg.identity != ('F' | 'W' << 8 | 'C' << 16 | 'T' << 24)) अणु
		dev_info(dev, "not a signed image\n");
		जाओ out_release_firmware;
	पूर्ण

	/* compare input version with FWCT version */
	cur_version = le16_to_cpu(app->build) | CCG_VERSION_PATCH(app->patch) |
			CCG_VERSION(app->ver);

	new_version = le16_to_cpu(fw_cfg.app.build) |
			CCG_VERSION_PATCH(fw_cfg.app.patch) |
			CCG_VERSION(fw_cfg.app.ver);

	अगर (!ccg_check_venकरोr_version(uc, app, &fw_cfg))
		जाओ out_release_firmware;

	अगर (new_version > cur_version)
		is_later = true;

out_release_firmware:
	release_firmware(fw);
	वापस is_later;
पूर्ण

अटल पूर्णांक ccg_fw_update_needed(काष्ठा ucsi_ccg *uc,
				क्रमागत क्रमागत_flash_mode *mode)
अणु
	काष्ठा device *dev = uc->dev;
	पूर्णांक err;
	काष्ठा version_info version[3];

	err = ccg_पढ़ो(uc, CCGX_RAB_DEVICE_MODE, (u8 *)(&uc->info),
		       माप(uc->info));
	अगर (err) अणु
		dev_err(dev, "read device mode failed\n");
		वापस err;
	पूर्ण

	err = ccg_पढ़ो(uc, CCGX_RAB_READ_ALL_VER, (u8 *)version,
		       माप(version));
	अगर (err) अणु
		dev_err(dev, "read device mode failed\n");
		वापस err;
	पूर्ण

	अगर (स_भेद(&version[FW1], "\0\0\0\0\0\0\0\0",
		   माप(काष्ठा version_info)) == 0) अणु
		dev_info(dev, "secondary fw is not flashed\n");
		*mode = SECONDARY_BL;
	पूर्ण अन्यथा अगर (le16_to_cpu(version[FW1].base.build) <
		secondary_fw_min_ver) अणु
		dev_info(dev, "secondary fw version is too low (< %d)\n",
			 secondary_fw_min_ver);
		*mode = SECONDARY;
	पूर्ण अन्यथा अगर (स_भेद(&version[FW2], "\0\0\0\0\0\0\0\0",
		   माप(काष्ठा version_info)) == 0) अणु
		dev_info(dev, "primary fw is not flashed\n");
		*mode = PRIMARY;
	पूर्ण अन्यथा अगर (ccg_check_fw_version(uc, ccg_fw_names[PRIMARY],
		   &version[FW2].app)) अणु
		dev_info(dev, "found primary fw with later version\n");
		*mode = PRIMARY;
	पूर्ण अन्यथा अणु
		dev_info(dev, "secondary and primary fw are the latest\n");
		*mode = FLASH_NOT_NEEDED;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_flash(काष्ठा ucsi_ccg *uc, क्रमागत क्रमागत_flash_mode mode)
अणु
	काष्ठा device *dev = uc->dev;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर अक्षर *p, *s;
	स्थिर अक्षर *eof;
	पूर्णांक err, row, len, line_sz, line_cnt = 0;
	अचिन्हित दीर्घ start_समय = jअगरfies;
	काष्ठा fw_config_table  fw_cfg;
	u8 fw_cfg_sig[FW_CFG_TABLE_SIG_SIZE];
	u8 *wr_buf;

	err = request_firmware(&fw, ccg_fw_names[mode], dev);
	अगर (err) अणु
		dev_err(dev, "request %s failed err=%d\n",
			ccg_fw_names[mode], err);
		वापस err;
	पूर्ण

	अगर (((uc->info.mode & CCG_DEVINFO_FWMODE_MASK) >>
			CCG_DEVINFO_FWMODE_SHIFT) == FW2) अणु
		err = ccg_cmd_port_control(uc, false);
		अगर (err < 0)
			जाओ release_fw;
		err = ccg_cmd_jump_boot_mode(uc, 0);
		अगर (err < 0)
			जाओ release_fw;
	पूर्ण

	eof = fw->data + fw->size;

	/*
	 * check अगर चिन्हित fw
	 * last part of fw image is fw cfg table and signature
	 */
	अगर (fw->size < माप(fw_cfg) + माप(fw_cfg_sig))
		जाओ not_चिन्हित_fw;

	स_नकल((uपूर्णांक8_t *)&fw_cfg, fw->data + fw->size -
	       माप(fw_cfg) - माप(fw_cfg_sig), माप(fw_cfg));

	अगर (fw_cfg.identity != ('F' | ('W' << 8) | ('C' << 16) | ('T' << 24))) अणु
		dev_info(dev, "not a signed image\n");
		जाओ not_चिन्हित_fw;
	पूर्ण
	eof = fw->data + fw->size - माप(fw_cfg) - माप(fw_cfg_sig);

	स_नकल((uपूर्णांक8_t *)&fw_cfg_sig,
	       fw->data + fw->size - माप(fw_cfg_sig), माप(fw_cfg_sig));

	/* flash fw config table and signature first */
	err = ccg_cmd_ग_लिखो_flash_row(uc, 0, (u8 *)&fw_cfg,
				      FLASH_FWCT1_WR_CMD);
	अगर (err)
		जाओ release_fw;

	err = ccg_cmd_ग_लिखो_flash_row(uc, 0, (u8 *)&fw_cfg + CCG4_ROW_SIZE,
				      FLASH_FWCT2_WR_CMD);
	अगर (err)
		जाओ release_fw;

	err = ccg_cmd_ग_लिखो_flash_row(uc, 0, &fw_cfg_sig,
				      FLASH_FWCT_SIG_WR_CMD);
	अगर (err)
		जाओ release_fw;

not_चिन्हित_fw:
	wr_buf = kzalloc(CCG4_ROW_SIZE + 4, GFP_KERNEL);
	अगर (!wr_buf) अणु
		err = -ENOMEM;
		जाओ release_fw;
	पूर्ण

	err = ccg_cmd_enter_flashing(uc);
	अगर (err)
		जाओ release_mem;

	/*****************************************************************
	 * CCG firmware image (.cyacd) file line क्रमmat
	 *
	 * :00rrrrllll[dd....]cc/r/n
	 *
	 * :00   header
	 * rrrr is row number to flash				(4 अक्षर)
	 * llll is data len to flash				(4 अक्षर)
	 * dd   is a data field represents one byte of data	(512 अक्षर)
	 * cc   is checksum					(2 अक्षर)
	 * \ल\न newline
	 *
	 * Total length: 3 + 4 + 4 + 512 + 2 + 2 = 527
	 *
	 *****************************************************************/

	p = strnchr(fw->data, fw->size, ':');
	जबतक (p < eof) अणु
		s = strnchr(p + 1, eof - p - 1, ':');

		अगर (!s)
			s = eof;

		line_sz = s - p;

		अगर (line_sz != CYACD_LINE_SIZE) अणु
			dev_err(dev, "Bad FW format line_sz=%d\n", line_sz);
			err =  -EINVAL;
			जाओ release_mem;
		पूर्ण

		अगर (hex2bin(wr_buf, p + 3, CCG4_ROW_SIZE + 4)) अणु
			err =  -EINVAL;
			जाओ release_mem;
		पूर्ण

		row = get_unaligned_be16(wr_buf);
		len = get_unaligned_be16(&wr_buf[2]);

		अगर (len != CCG4_ROW_SIZE) अणु
			err =  -EINVAL;
			जाओ release_mem;
		पूर्ण

		err = ccg_cmd_ग_लिखो_flash_row(uc, row, wr_buf + 4,
					      FLASH_WR_CMD);
		अगर (err)
			जाओ release_mem;

		line_cnt++;
		p = s;
	पूर्ण

	dev_info(dev, "total %d row flashed. time: %dms\n",
		 line_cnt, jअगरfies_to_msecs(jअगरfies - start_समय));

	err = ccg_cmd_validate_fw(uc, (mode == PRIMARY) ? FW2 :  FW1);
	अगर (err)
		dev_err(dev, "%s validation failed err=%d\n",
			(mode == PRIMARY) ? "FW2" :  "FW1", err);
	अन्यथा
		dev_info(dev, "%s validated\n",
			 (mode == PRIMARY) ? "FW2" :  "FW1");

	err = ccg_cmd_port_control(uc, false);
	अगर (err < 0)
		जाओ release_mem;

	err = ccg_cmd_reset(uc);
	अगर (err < 0)
		जाओ release_mem;

	err = ccg_cmd_port_control(uc, true);
	अगर (err < 0)
		जाओ release_mem;

release_mem:
	kमुक्त(wr_buf);

release_fw:
	release_firmware(fw);
	वापस err;
पूर्ण

/*******************************************************************************
 * CCG4 has two copies of the firmware in addition to the bootloader.
 * If the device is running FW1, FW2 can be updated with the new version.
 * Dual firmware mode allows the CCG device to stay in a PD contract and support
 * USB PD and Type-C functionality जबतक a firmware update is in progress.
 ******************************************************************************/
अटल पूर्णांक ccg_fw_update(काष्ठा ucsi_ccg *uc, क्रमागत क्रमागत_flash_mode flash_mode)
अणु
	पूर्णांक err = 0;

	जबतक (flash_mode != FLASH_NOT_NEEDED) अणु
		err = करो_flash(uc, flash_mode);
		अगर (err < 0)
			वापस err;
		err = ccg_fw_update_needed(uc, &flash_mode);
		अगर (err < 0)
			वापस err;
	पूर्ण
	dev_info(uc->dev, "CCG FW update successful\n");

	वापस err;
पूर्ण

अटल पूर्णांक ccg_restart(काष्ठा ucsi_ccg *uc)
अणु
	काष्ठा device *dev = uc->dev;
	पूर्णांक status;

	status = ucsi_ccg_init(uc);
	अगर (status < 0) अणु
		dev_err(dev, "ucsi_ccg_start fail, err=%d\n", status);
		वापस status;
	पूर्ण

	status = request_thपढ़ोed_irq(uc->irq, शून्य, ccg_irq_handler,
				      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
				      dev_name(dev), uc);
	अगर (status < 0) अणु
		dev_err(dev, "request_threaded_irq failed - %d\n", status);
		वापस status;
	पूर्ण

	status = ucsi_रेजिस्टर(uc->ucsi);
	अगर (status) अणु
		dev_err(uc->dev, "failed to register the interface\n");
		वापस status;
	पूर्ण

	pm_runसमय_enable(uc->dev);
	वापस 0;
पूर्ण

अटल व्योम ccg_update_firmware(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucsi_ccg *uc = container_of(work, काष्ठा ucsi_ccg, work);
	क्रमागत क्रमागत_flash_mode flash_mode;
	पूर्णांक status;

	status = ccg_fw_update_needed(uc, &flash_mode);
	अगर (status < 0)
		वापस;

	अगर (flash_mode != FLASH_NOT_NEEDED) अणु
		ucsi_unरेजिस्टर(uc->ucsi);
		pm_runसमय_disable(uc->dev);
		मुक्त_irq(uc->irq, uc);

		ccg_fw_update(uc, flash_mode);
		ccg_restart(uc);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार करो_flash_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा ucsi_ccg *uc = i2c_get_clientdata(to_i2c_client(dev));
	bool flash;

	अगर (kstrtobool(buf, &flash))
		वापस -EINVAL;

	अगर (!flash)
		वापस n;

	अगर (uc->fw_build == 0x0) अणु
		dev_err(dev, "fail to flash FW due to missing FW build info\n");
		वापस -EINVAL;
	पूर्ण

	schedule_work(&uc->work);
	वापस n;
पूर्ण

अटल DEVICE_ATTR_WO(करो_flash);

अटल काष्ठा attribute *ucsi_ccg_attrs[] = अणु
	&dev_attr_करो_flash.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ucsi_ccg);

अटल पूर्णांक ucsi_ccg_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ucsi_ccg *uc;
	पूर्णांक status;

	uc = devm_kzalloc(dev, माप(*uc), GFP_KERNEL);
	अगर (!uc)
		वापस -ENOMEM;

	uc->dev = dev;
	uc->client = client;
	mutex_init(&uc->lock);
	init_completion(&uc->complete);
	INIT_WORK(&uc->work, ccg_update_firmware);
	INIT_WORK(&uc->pm_work, ccg_pm_workaround_work);

	/* Only fail FW flashing when FW build inक्रमmation is not provided */
	status = device_property_पढ़ो_u16(dev, "ccgx,firmware-build",
					  &uc->fw_build);
	अगर (status)
		dev_err(uc->dev, "failed to get FW build information\n");

	/* reset ccg device and initialize ucsi */
	status = ucsi_ccg_init(uc);
	अगर (status < 0) अणु
		dev_err(uc->dev, "ucsi_ccg_init failed - %d\n", status);
		वापस status;
	पूर्ण

	status = get_fw_info(uc);
	अगर (status < 0) अणु
		dev_err(uc->dev, "get_fw_info failed - %d\n", status);
		वापस status;
	पूर्ण

	uc->port_num = 1;

	अगर (uc->info.mode & CCG_DEVINFO_PDPORTS_MASK)
		uc->port_num++;

	uc->ucsi = ucsi_create(dev, &ucsi_ccg_ops);
	अगर (IS_ERR(uc->ucsi))
		वापस PTR_ERR(uc->ucsi);

	ucsi_set_drvdata(uc->ucsi, uc);

	status = request_thपढ़ोed_irq(client->irq, शून्य, ccg_irq_handler,
				      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
				      dev_name(dev), uc);
	अगर (status < 0) अणु
		dev_err(uc->dev, "request_threaded_irq failed - %d\n", status);
		जाओ out_ucsi_destroy;
	पूर्ण

	uc->irq = client->irq;

	status = ucsi_रेजिस्टर(uc->ucsi);
	अगर (status)
		जाओ out_मुक्त_irq;

	i2c_set_clientdata(client, uc);

	pm_runसमय_set_active(uc->dev);
	pm_runसमय_enable(uc->dev);
	pm_runसमय_use_स्वतःsuspend(uc->dev);
	pm_runसमय_set_स्वतःsuspend_delay(uc->dev, 5000);
	pm_runसमय_idle(uc->dev);

	वापस 0;

out_मुक्त_irq:
	मुक्त_irq(uc->irq, uc);
out_ucsi_destroy:
	ucsi_destroy(uc->ucsi);

	वापस status;
पूर्ण

अटल पूर्णांक ucsi_ccg_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ucsi_ccg *uc = i2c_get_clientdata(client);

	cancel_work_sync(&uc->pm_work);
	cancel_work_sync(&uc->work);
	pm_runसमय_disable(uc->dev);
	ucsi_unरेजिस्टर(uc->ucsi);
	ucsi_destroy(uc->ucsi);
	मुक्त_irq(uc->irq, uc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ucsi_ccg_device_id[] = अणु
	अणु"ccgx-ucsi", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ucsi_ccg_device_id);

अटल पूर्णांक ucsi_ccg_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ucsi_ccg *uc = i2c_get_clientdata(client);

	वापस ucsi_resume(uc->ucsi);
पूर्ण

अटल पूर्णांक ucsi_ccg_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ucsi_ccg_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ucsi_ccg *uc = i2c_get_clientdata(client);

	/*
	 * Firmware version 3.1.10 or earlier, built क्रम NVIDIA has known issue
	 * of missing पूर्णांकerrupt when a device is connected क्रम runसमय resume.
	 * Schedule a work to call ISR as a workaround.
	 */
	अगर (uc->fw_build == CCG_FW_BUILD_NVIDIA &&
	    uc->fw_version <= CCG_OLD_FW_VERSION)
		schedule_work(&uc->pm_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ucsi_ccg_pm = अणु
	.resume = ucsi_ccg_resume,
	.runसमय_suspend = ucsi_ccg_runसमय_suspend,
	.runसमय_resume = ucsi_ccg_runसमय_resume,
पूर्ण;

अटल काष्ठा i2c_driver ucsi_ccg_driver = अणु
	.driver = अणु
		.name = "ucsi_ccg",
		.pm = &ucsi_ccg_pm,
		.dev_groups = ucsi_ccg_groups,
	पूर्ण,
	.probe = ucsi_ccg_probe,
	.हटाओ = ucsi_ccg_हटाओ,
	.id_table = ucsi_ccg_device_id,
पूर्ण;

module_i2c_driver(ucsi_ccg_driver);

MODULE_AUTHOR("Ajay Gupta <ajayg@nvidia.com>");
MODULE_DESCRIPTION("UCSI driver for Cypress CCGx Type-C controller");
MODULE_LICENSE("GPL v2");
