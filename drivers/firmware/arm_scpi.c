<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Control and Power Interface (SCPI) Message Protocol driver
 *
 * SCPI Message Protocol is used between the System Control Processor(SCP)
 * and the Application Processors(AP). The Message Handling Unit(MHU)
 * provides a mechanism क्रम पूर्णांकer-processor communication between SCP's
 * Cortex M3 and AP.
 *
 * SCP offers control and management of the core/cluster घातer states,
 * various घातer करोमुख्य DVFS including the core/cluster, certain प्रणाली
 * घड़ीs configuration, thermal sensors and many others.
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/scpi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/spinlock.h>

#घोषणा CMD_ID_MASK		GENMASK(6, 0)
#घोषणा CMD_TOKEN_ID_MASK	GENMASK(15, 8)
#घोषणा CMD_DATA_SIZE_MASK	GENMASK(24, 16)
#घोषणा CMD_LEGACY_DATA_SIZE_MASK	GENMASK(28, 20)
#घोषणा PACK_SCPI_CMD(cmd_id, tx_sz)		\
	(FIELD_PREP(CMD_ID_MASK, cmd_id) |	\
	FIELD_PREP(CMD_DATA_SIZE_MASK, tx_sz))
#घोषणा PACK_LEGACY_SCPI_CMD(cmd_id, tx_sz)	\
	(FIELD_PREP(CMD_ID_MASK, cmd_id) |	\
	FIELD_PREP(CMD_LEGACY_DATA_SIZE_MASK, tx_sz))

#घोषणा CMD_SIZE(cmd)	FIELD_GET(CMD_DATA_SIZE_MASK, cmd)
#घोषणा CMD_UNIQ_MASK	(CMD_TOKEN_ID_MASK | CMD_ID_MASK)
#घोषणा CMD_XTRACT_UNIQ(cmd)	((cmd) & CMD_UNIQ_MASK)

#घोषणा SCPI_SLOT		0

#घोषणा MAX_DVFS_DOMAINS	8
#घोषणा MAX_DVFS_OPPS		16

#घोषणा PROTO_REV_MAJOR_MASK	GENMASK(31, 16)
#घोषणा PROTO_REV_MINOR_MASK	GENMASK(15, 0)

#घोषणा FW_REV_MAJOR_MASK	GENMASK(31, 24)
#घोषणा FW_REV_MINOR_MASK	GENMASK(23, 16)
#घोषणा FW_REV_PATCH_MASK	GENMASK(15, 0)

#घोषणा MAX_RX_TIMEOUT		(msecs_to_jअगरfies(30))

क्रमागत scpi_error_codes अणु
	SCPI_SUCCESS = 0, /* Success */
	SCPI_ERR_PARAM = 1, /* Invalid parameter(s) */
	SCPI_ERR_ALIGN = 2, /* Invalid alignment */
	SCPI_ERR_SIZE = 3, /* Invalid size */
	SCPI_ERR_HANDLER = 4, /* Invalid handler/callback */
	SCPI_ERR_ACCESS = 5, /* Invalid access/permission denied */
	SCPI_ERR_RANGE = 6, /* Value out of range */
	SCPI_ERR_TIMEOUT = 7, /* Timeout has occurred */
	SCPI_ERR_NOMEM = 8, /* Invalid memory area or poपूर्णांकer */
	SCPI_ERR_PWRSTATE = 9, /* Invalid घातer state */
	SCPI_ERR_SUPPORT = 10, /* Not supported or disabled */
	SCPI_ERR_DEVICE = 11, /* Device error */
	SCPI_ERR_BUSY = 12, /* Device busy */
	SCPI_ERR_MAX
पूर्ण;

/* SCPI Standard commands */
क्रमागत scpi_std_cmd अणु
	SCPI_CMD_INVALID		= 0x00,
	SCPI_CMD_SCPI_READY		= 0x01,
	SCPI_CMD_SCPI_CAPABILITIES	= 0x02,
	SCPI_CMD_SET_CSS_PWR_STATE	= 0x03,
	SCPI_CMD_GET_CSS_PWR_STATE	= 0x04,
	SCPI_CMD_SET_SYS_PWR_STATE	= 0x05,
	SCPI_CMD_SET_CPU_TIMER		= 0x06,
	SCPI_CMD_CANCEL_CPU_TIMER	= 0x07,
	SCPI_CMD_DVFS_CAPABILITIES	= 0x08,
	SCPI_CMD_GET_DVFS_INFO		= 0x09,
	SCPI_CMD_SET_DVFS		= 0x0a,
	SCPI_CMD_GET_DVFS		= 0x0b,
	SCPI_CMD_GET_DVFS_STAT		= 0x0c,
	SCPI_CMD_CLOCK_CAPABILITIES	= 0x0d,
	SCPI_CMD_GET_CLOCK_INFO		= 0x0e,
	SCPI_CMD_SET_CLOCK_VALUE	= 0x0f,
	SCPI_CMD_GET_CLOCK_VALUE	= 0x10,
	SCPI_CMD_PSU_CAPABILITIES	= 0x11,
	SCPI_CMD_GET_PSU_INFO		= 0x12,
	SCPI_CMD_SET_PSU		= 0x13,
	SCPI_CMD_GET_PSU		= 0x14,
	SCPI_CMD_SENSOR_CAPABILITIES	= 0x15,
	SCPI_CMD_SENSOR_INFO		= 0x16,
	SCPI_CMD_SENSOR_VALUE		= 0x17,
	SCPI_CMD_SENSOR_CFG_PERIODIC	= 0x18,
	SCPI_CMD_SENSOR_CFG_BOUNDS	= 0x19,
	SCPI_CMD_SENSOR_ASYNC_VALUE	= 0x1a,
	SCPI_CMD_SET_DEVICE_PWR_STATE	= 0x1b,
	SCPI_CMD_GET_DEVICE_PWR_STATE	= 0x1c,
	SCPI_CMD_COUNT
पूर्ण;

/* SCPI Legacy Commands */
क्रमागत legacy_scpi_std_cmd अणु
	LEGACY_SCPI_CMD_INVALID			= 0x00,
	LEGACY_SCPI_CMD_SCPI_READY		= 0x01,
	LEGACY_SCPI_CMD_SCPI_CAPABILITIES	= 0x02,
	LEGACY_SCPI_CMD_EVENT			= 0x03,
	LEGACY_SCPI_CMD_SET_CSS_PWR_STATE	= 0x04,
	LEGACY_SCPI_CMD_GET_CSS_PWR_STATE	= 0x05,
	LEGACY_SCPI_CMD_CFG_PWR_STATE_STAT	= 0x06,
	LEGACY_SCPI_CMD_GET_PWR_STATE_STAT	= 0x07,
	LEGACY_SCPI_CMD_SYS_PWR_STATE		= 0x08,
	LEGACY_SCPI_CMD_L2_READY		= 0x09,
	LEGACY_SCPI_CMD_SET_AP_TIMER		= 0x0a,
	LEGACY_SCPI_CMD_CANCEL_AP_TIME		= 0x0b,
	LEGACY_SCPI_CMD_DVFS_CAPABILITIES	= 0x0c,
	LEGACY_SCPI_CMD_GET_DVFS_INFO		= 0x0d,
	LEGACY_SCPI_CMD_SET_DVFS		= 0x0e,
	LEGACY_SCPI_CMD_GET_DVFS		= 0x0f,
	LEGACY_SCPI_CMD_GET_DVFS_STAT		= 0x10,
	LEGACY_SCPI_CMD_SET_RTC			= 0x11,
	LEGACY_SCPI_CMD_GET_RTC			= 0x12,
	LEGACY_SCPI_CMD_CLOCK_CAPABILITIES	= 0x13,
	LEGACY_SCPI_CMD_SET_CLOCK_INDEX		= 0x14,
	LEGACY_SCPI_CMD_SET_CLOCK_VALUE		= 0x15,
	LEGACY_SCPI_CMD_GET_CLOCK_VALUE		= 0x16,
	LEGACY_SCPI_CMD_PSU_CAPABILITIES	= 0x17,
	LEGACY_SCPI_CMD_SET_PSU			= 0x18,
	LEGACY_SCPI_CMD_GET_PSU			= 0x19,
	LEGACY_SCPI_CMD_SENSOR_CAPABILITIES	= 0x1a,
	LEGACY_SCPI_CMD_SENSOR_INFO		= 0x1b,
	LEGACY_SCPI_CMD_SENSOR_VALUE		= 0x1c,
	LEGACY_SCPI_CMD_SENSOR_CFG_PERIODIC	= 0x1d,
	LEGACY_SCPI_CMD_SENSOR_CFG_BOUNDS	= 0x1e,
	LEGACY_SCPI_CMD_SENSOR_ASYNC_VALUE	= 0x1f,
	LEGACY_SCPI_CMD_COUNT
पूर्ण;

/* List all commands that are required to go through the high priority link */
अटल पूर्णांक legacy_hpriority_cmds[] = अणु
	LEGACY_SCPI_CMD_GET_CSS_PWR_STATE,
	LEGACY_SCPI_CMD_CFG_PWR_STATE_STAT,
	LEGACY_SCPI_CMD_GET_PWR_STATE_STAT,
	LEGACY_SCPI_CMD_SET_DVFS,
	LEGACY_SCPI_CMD_GET_DVFS,
	LEGACY_SCPI_CMD_SET_RTC,
	LEGACY_SCPI_CMD_GET_RTC,
	LEGACY_SCPI_CMD_SET_CLOCK_INDEX,
	LEGACY_SCPI_CMD_SET_CLOCK_VALUE,
	LEGACY_SCPI_CMD_GET_CLOCK_VALUE,
	LEGACY_SCPI_CMD_SET_PSU,
	LEGACY_SCPI_CMD_GET_PSU,
	LEGACY_SCPI_CMD_SENSOR_CFG_PERIODIC,
	LEGACY_SCPI_CMD_SENSOR_CFG_BOUNDS,
पूर्ण;

/* List all commands used by this driver, used as indexes */
क्रमागत scpi_drv_cmds अणु
	CMD_SCPI_CAPABILITIES = 0,
	CMD_GET_CLOCK_INFO,
	CMD_GET_CLOCK_VALUE,
	CMD_SET_CLOCK_VALUE,
	CMD_GET_DVFS,
	CMD_SET_DVFS,
	CMD_GET_DVFS_INFO,
	CMD_SENSOR_CAPABILITIES,
	CMD_SENSOR_INFO,
	CMD_SENSOR_VALUE,
	CMD_SET_DEVICE_PWR_STATE,
	CMD_GET_DEVICE_PWR_STATE,
	CMD_MAX_COUNT,
पूर्ण;

अटल पूर्णांक scpi_std_commands[CMD_MAX_COUNT] = अणु
	SCPI_CMD_SCPI_CAPABILITIES,
	SCPI_CMD_GET_CLOCK_INFO,
	SCPI_CMD_GET_CLOCK_VALUE,
	SCPI_CMD_SET_CLOCK_VALUE,
	SCPI_CMD_GET_DVFS,
	SCPI_CMD_SET_DVFS,
	SCPI_CMD_GET_DVFS_INFO,
	SCPI_CMD_SENSOR_CAPABILITIES,
	SCPI_CMD_SENSOR_INFO,
	SCPI_CMD_SENSOR_VALUE,
	SCPI_CMD_SET_DEVICE_PWR_STATE,
	SCPI_CMD_GET_DEVICE_PWR_STATE,
पूर्ण;

अटल पूर्णांक scpi_legacy_commands[CMD_MAX_COUNT] = अणु
	LEGACY_SCPI_CMD_SCPI_CAPABILITIES,
	-1, /* GET_CLOCK_INFO */
	LEGACY_SCPI_CMD_GET_CLOCK_VALUE,
	LEGACY_SCPI_CMD_SET_CLOCK_VALUE,
	LEGACY_SCPI_CMD_GET_DVFS,
	LEGACY_SCPI_CMD_SET_DVFS,
	LEGACY_SCPI_CMD_GET_DVFS_INFO,
	LEGACY_SCPI_CMD_SENSOR_CAPABILITIES,
	LEGACY_SCPI_CMD_SENSOR_INFO,
	LEGACY_SCPI_CMD_SENSOR_VALUE,
	-1, /* SET_DEVICE_PWR_STATE */
	-1, /* GET_DEVICE_PWR_STATE */
पूर्ण;

काष्ठा scpi_xfer अणु
	u32 slot; /* has to be first element */
	u32 cmd;
	u32 status;
	स्थिर व्योम *tx_buf;
	व्योम *rx_buf;
	अचिन्हित पूर्णांक tx_len;
	अचिन्हित पूर्णांक rx_len;
	काष्ठा list_head node;
	काष्ठा completion करोne;
पूर्ण;

काष्ठा scpi_chan अणु
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *chan;
	व्योम __iomem *tx_payload;
	व्योम __iomem *rx_payload;
	काष्ठा list_head rx_pending;
	काष्ठा list_head xfers_list;
	काष्ठा scpi_xfer *xfers;
	spinlock_t rx_lock; /* locking क्रम the rx pending list */
	काष्ठा mutex xfers_lock;
	u8 token;
पूर्ण;

काष्ठा scpi_drvinfo अणु
	u32 protocol_version;
	u32 firmware_version;
	bool is_legacy;
	पूर्णांक num_chans;
	पूर्णांक *commands;
	DECLARE_BITMAP(cmd_priority, LEGACY_SCPI_CMD_COUNT);
	atomic_t next_chan;
	काष्ठा scpi_ops *scpi_ops;
	काष्ठा scpi_chan *channels;
	काष्ठा scpi_dvfs_info *dvfs[MAX_DVFS_DOMAINS];
पूर्ण;

/*
 * The SCP firmware only executes in little-endian mode, so any buffers
 * shared through SCPI should have their contents converted to little-endian
 */
काष्ठा scpi_shared_mem अणु
	__le32 command;
	__le32 status;
	u8 payload[];
पूर्ण __packed;

काष्ठा legacy_scpi_shared_mem अणु
	__le32 status;
	u8 payload[];
पूर्ण __packed;

काष्ठा scp_capabilities अणु
	__le32 protocol_version;
	__le32 event_version;
	__le32 platक्रमm_version;
	__le32 commands[4];
पूर्ण __packed;

काष्ठा clk_get_info अणु
	__le16 id;
	__le16 flags;
	__le32 min_rate;
	__le32 max_rate;
	u8 name[20];
पूर्ण __packed;

काष्ठा clk_set_value अणु
	__le16 id;
	__le16 reserved;
	__le32 rate;
पूर्ण __packed;

काष्ठा legacy_clk_set_value अणु
	__le32 rate;
	__le16 id;
	__le16 reserved;
पूर्ण __packed;

काष्ठा dvfs_info अणु
	u8 करोमुख्य;
	u8 opp_count;
	__le16 latency;
	काष्ठा अणु
		__le32 freq;
		__le32 m_volt;
	पूर्ण opps[MAX_DVFS_OPPS];
पूर्ण __packed;

काष्ठा dvfs_set अणु
	u8 करोमुख्य;
	u8 index;
पूर्ण __packed;

काष्ठा _scpi_sensor_info अणु
	__le16 sensor_id;
	u8 class;
	u8 trigger_type;
	अक्षर name[20];
पूर्ण;

काष्ठा dev_pstate_set अणु
	__le16 dev_id;
	u8 pstate;
पूर्ण __packed;

अटल काष्ठा scpi_drvinfo *scpi_info;

अटल पूर्णांक scpi_linux_errmap[SCPI_ERR_MAX] = अणु
	/* better than चयन हाल as दीर्घ as वापस value is continuous */
	0, /* SCPI_SUCCESS */
	-EINVAL, /* SCPI_ERR_PARAM */
	-ENOEXEC, /* SCPI_ERR_ALIGN */
	-EMSGSIZE, /* SCPI_ERR_SIZE */
	-EINVAL, /* SCPI_ERR_HANDLER */
	-EACCES, /* SCPI_ERR_ACCESS */
	-दुस्फल, /* SCPI_ERR_RANGE */
	-ETIMEDOUT, /* SCPI_ERR_TIMEOUT */
	-ENOMEM, /* SCPI_ERR_NOMEM */
	-EINVAL, /* SCPI_ERR_PWRSTATE */
	-EOPNOTSUPP, /* SCPI_ERR_SUPPORT */
	-EIO, /* SCPI_ERR_DEVICE */
	-EBUSY, /* SCPI_ERR_BUSY */
पूर्ण;

अटल अंतरभूत पूर्णांक scpi_to_linux_त्रुटि_सं(पूर्णांक त्रुटि_सं)
अणु
	अगर (त्रुटि_सं >= SCPI_SUCCESS && त्रुटि_सं < SCPI_ERR_MAX)
		वापस scpi_linux_errmap[त्रुटि_सं];
	वापस -EIO;
पूर्ण

अटल व्योम scpi_process_cmd(काष्ठा scpi_chan *ch, u32 cmd)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा scpi_xfer *t, *match = शून्य;

	spin_lock_irqsave(&ch->rx_lock, flags);
	अगर (list_empty(&ch->rx_pending)) अणु
		spin_unlock_irqrestore(&ch->rx_lock, flags);
		वापस;
	पूर्ण

	/* Command type is not replied by the SCP Firmware in legacy Mode
	 * We should consider that command is the head of pending RX commands
	 * अगर the list is not empty. In TX only mode, the list would be empty.
	 */
	अगर (scpi_info->is_legacy) अणु
		match = list_first_entry(&ch->rx_pending, काष्ठा scpi_xfer,
					 node);
		list_del(&match->node);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(t, &ch->rx_pending, node)
			अगर (CMD_XTRACT_UNIQ(t->cmd) == CMD_XTRACT_UNIQ(cmd)) अणु
				list_del(&t->node);
				match = t;
				अवरोध;
			पूर्ण
	पूर्ण
	/* check अगर रुको_क्रम_completion is in progress or समयd-out */
	अगर (match && !completion_करोne(&match->करोne)) अणु
		अचिन्हित पूर्णांक len;

		अगर (scpi_info->is_legacy) अणु
			काष्ठा legacy_scpi_shared_mem __iomem *mem =
							ch->rx_payload;

			/* RX Length is not replied by the legacy Firmware */
			len = match->rx_len;

			match->status = ioपढ़ो32(&mem->status);
			स_नकल_fromio(match->rx_buf, mem->payload, len);
		पूर्ण अन्यथा अणु
			काष्ठा scpi_shared_mem __iomem *mem = ch->rx_payload;

			len = min_t(अचिन्हित पूर्णांक, match->rx_len, CMD_SIZE(cmd));

			match->status = ioपढ़ो32(&mem->status);
			स_नकल_fromio(match->rx_buf, mem->payload, len);
		पूर्ण

		अगर (match->rx_len > len)
			स_रखो(match->rx_buf + len, 0, match->rx_len - len);
		complete(&match->करोne);
	पूर्ण
	spin_unlock_irqrestore(&ch->rx_lock, flags);
पूर्ण

अटल व्योम scpi_handle_remote_msg(काष्ठा mbox_client *c, व्योम *msg)
अणु
	काष्ठा scpi_chan *ch = container_of(c, काष्ठा scpi_chan, cl);
	काष्ठा scpi_shared_mem __iomem *mem = ch->rx_payload;
	u32 cmd = 0;

	अगर (!scpi_info->is_legacy)
		cmd = ioपढ़ो32(&mem->command);

	scpi_process_cmd(ch, cmd);
पूर्ण

अटल व्योम scpi_tx_prepare(काष्ठा mbox_client *c, व्योम *msg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा scpi_xfer *t = msg;
	काष्ठा scpi_chan *ch = container_of(c, काष्ठा scpi_chan, cl);
	काष्ठा scpi_shared_mem __iomem *mem = ch->tx_payload;

	अगर (t->tx_buf) अणु
		अगर (scpi_info->is_legacy)
			स_नकल_toio(ch->tx_payload, t->tx_buf, t->tx_len);
		अन्यथा
			स_नकल_toio(mem->payload, t->tx_buf, t->tx_len);
	पूर्ण

	अगर (t->rx_buf) अणु
		अगर (!(++ch->token))
			++ch->token;
		t->cmd |= FIELD_PREP(CMD_TOKEN_ID_MASK, ch->token);
		spin_lock_irqsave(&ch->rx_lock, flags);
		list_add_tail(&t->node, &ch->rx_pending);
		spin_unlock_irqrestore(&ch->rx_lock, flags);
	पूर्ण

	अगर (!scpi_info->is_legacy)
		ioग_लिखो32(t->cmd, &mem->command);
पूर्ण

अटल काष्ठा scpi_xfer *get_scpi_xfer(काष्ठा scpi_chan *ch)
अणु
	काष्ठा scpi_xfer *t;

	mutex_lock(&ch->xfers_lock);
	अगर (list_empty(&ch->xfers_list)) अणु
		mutex_unlock(&ch->xfers_lock);
		वापस शून्य;
	पूर्ण
	t = list_first_entry(&ch->xfers_list, काष्ठा scpi_xfer, node);
	list_del(&t->node);
	mutex_unlock(&ch->xfers_lock);
	वापस t;
पूर्ण

अटल व्योम put_scpi_xfer(काष्ठा scpi_xfer *t, काष्ठा scpi_chan *ch)
अणु
	mutex_lock(&ch->xfers_lock);
	list_add_tail(&t->node, &ch->xfers_list);
	mutex_unlock(&ch->xfers_lock);
पूर्ण

अटल पूर्णांक scpi_send_message(u8 idx, व्योम *tx_buf, अचिन्हित पूर्णांक tx_len,
			     व्योम *rx_buf, अचिन्हित पूर्णांक rx_len)
अणु
	पूर्णांक ret;
	u8 chan;
	u8 cmd;
	काष्ठा scpi_xfer *msg;
	काष्ठा scpi_chan *scpi_chan;

	अगर (scpi_info->commands[idx] < 0)
		वापस -EOPNOTSUPP;

	cmd = scpi_info->commands[idx];

	अगर (scpi_info->is_legacy)
		chan = test_bit(cmd, scpi_info->cmd_priority) ? 1 : 0;
	अन्यथा
		chan = atomic_inc_वापस(&scpi_info->next_chan) %
			scpi_info->num_chans;
	scpi_chan = scpi_info->channels + chan;

	msg = get_scpi_xfer(scpi_chan);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (scpi_info->is_legacy) अणु
		msg->cmd = PACK_LEGACY_SCPI_CMD(cmd, tx_len);
		msg->slot = msg->cmd;
	पूर्ण अन्यथा अणु
		msg->slot = BIT(SCPI_SLOT);
		msg->cmd = PACK_SCPI_CMD(cmd, tx_len);
	पूर्ण
	msg->tx_buf = tx_buf;
	msg->tx_len = tx_len;
	msg->rx_buf = rx_buf;
	msg->rx_len = rx_len;
	reinit_completion(&msg->करोne);

	ret = mbox_send_message(scpi_chan->chan, msg);
	अगर (ret < 0 || !rx_buf)
		जाओ out;

	अगर (!रुको_क्रम_completion_समयout(&msg->करोne, MAX_RX_TIMEOUT))
		ret = -ETIMEDOUT;
	अन्यथा
		/* first status word */
		ret = msg->status;
out:
	अगर (ret < 0 && rx_buf) /* हटाओ entry from the list अगर समयd-out */
		scpi_process_cmd(scpi_chan, msg->cmd);

	put_scpi_xfer(msg, scpi_chan);
	/* SCPI error codes > 0, translate them to Linux scale*/
	वापस ret > 0 ? scpi_to_linux_त्रुटि_सं(ret) : ret;
पूर्ण

अटल u32 scpi_get_version(व्योम)
अणु
	वापस scpi_info->protocol_version;
पूर्ण

अटल पूर्णांक
scpi_clk_get_range(u16 clk_id, अचिन्हित दीर्घ *min, अचिन्हित दीर्घ *max)
अणु
	पूर्णांक ret;
	काष्ठा clk_get_info clk;
	__le16 le_clk_id = cpu_to_le16(clk_id);

	ret = scpi_send_message(CMD_GET_CLOCK_INFO, &le_clk_id,
				माप(le_clk_id), &clk, माप(clk));
	अगर (!ret) अणु
		*min = le32_to_cpu(clk.min_rate);
		*max = le32_to_cpu(clk.max_rate);
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ scpi_clk_get_val(u16 clk_id)
अणु
	पूर्णांक ret;
	__le32 rate;
	__le16 le_clk_id = cpu_to_le16(clk_id);

	ret = scpi_send_message(CMD_GET_CLOCK_VALUE, &le_clk_id,
				माप(le_clk_id), &rate, माप(rate));
	अगर (ret)
		वापस 0;

	वापस le32_to_cpu(rate);
पूर्ण

अटल पूर्णांक scpi_clk_set_val(u16 clk_id, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक stat;
	काष्ठा clk_set_value clk = अणु
		.id = cpu_to_le16(clk_id),
		.rate = cpu_to_le32(rate)
	पूर्ण;

	वापस scpi_send_message(CMD_SET_CLOCK_VALUE, &clk, माप(clk),
				 &stat, माप(stat));
पूर्ण

अटल पूर्णांक legacy_scpi_clk_set_val(u16 clk_id, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक stat;
	काष्ठा legacy_clk_set_value clk = अणु
		.id = cpu_to_le16(clk_id),
		.rate = cpu_to_le32(rate)
	पूर्ण;

	वापस scpi_send_message(CMD_SET_CLOCK_VALUE, &clk, माप(clk),
				 &stat, माप(stat));
पूर्ण

अटल पूर्णांक scpi_dvfs_get_idx(u8 करोमुख्य)
अणु
	पूर्णांक ret;
	u8 dvfs_idx;

	ret = scpi_send_message(CMD_GET_DVFS, &करोमुख्य, माप(करोमुख्य),
				&dvfs_idx, माप(dvfs_idx));

	वापस ret ? ret : dvfs_idx;
पूर्ण

अटल पूर्णांक scpi_dvfs_set_idx(u8 करोमुख्य, u8 index)
अणु
	पूर्णांक stat;
	काष्ठा dvfs_set dvfs = अणुकरोमुख्य, indexपूर्ण;

	वापस scpi_send_message(CMD_SET_DVFS, &dvfs, माप(dvfs),
				 &stat, माप(stat));
पूर्ण

अटल पूर्णांक opp_cmp_func(स्थिर व्योम *opp1, स्थिर व्योम *opp2)
अणु
	स्थिर काष्ठा scpi_opp *t1 = opp1, *t2 = opp2;

	वापस t1->freq - t2->freq;
पूर्ण

अटल काष्ठा scpi_dvfs_info *scpi_dvfs_get_info(u8 करोमुख्य)
अणु
	काष्ठा scpi_dvfs_info *info;
	काष्ठा scpi_opp *opp;
	काष्ठा dvfs_info buf;
	पूर्णांक ret, i;

	अगर (करोमुख्य >= MAX_DVFS_DOMAINS)
		वापस ERR_PTR(-EINVAL);

	अगर (scpi_info->dvfs[करोमुख्य])	/* data alपढ़ोy populated */
		वापस scpi_info->dvfs[करोमुख्य];

	ret = scpi_send_message(CMD_GET_DVFS_INFO, &करोमुख्य, माप(करोमुख्य),
				&buf, माप(buf));
	अगर (ret)
		वापस ERR_PTR(ret);

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	info->count = buf.opp_count;
	info->latency = le16_to_cpu(buf.latency) * 1000; /* uS to nS */

	info->opps = kसुस्मृति(info->count, माप(*opp), GFP_KERNEL);
	अगर (!info->opps) अणु
		kमुक्त(info);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0, opp = info->opps; i < info->count; i++, opp++) अणु
		opp->freq = le32_to_cpu(buf.opps[i].freq);
		opp->m_volt = le32_to_cpu(buf.opps[i].m_volt);
	पूर्ण

	sort(info->opps, info->count, माप(*opp), opp_cmp_func, शून्य);

	scpi_info->dvfs[करोमुख्य] = info;
	वापस info;
पूर्ण

अटल पूर्णांक scpi_dev_करोमुख्य_id(काष्ठा device *dev)
अणु
	काष्ठा of_phandle_args clkspec;

	अगर (of_parse_phandle_with_args(dev->of_node, "clocks", "#clock-cells",
				       0, &clkspec))
		वापस -EINVAL;

	वापस clkspec.args[0];
पूर्ण

अटल काष्ठा scpi_dvfs_info *scpi_dvfs_info(काष्ठा device *dev)
अणु
	पूर्णांक करोमुख्य = scpi_dev_करोमुख्य_id(dev);

	अगर (करोमुख्य < 0)
		वापस ERR_PTR(करोमुख्य);

	वापस scpi_dvfs_get_info(करोमुख्य);
पूर्ण

अटल पूर्णांक scpi_dvfs_get_transition_latency(काष्ठा device *dev)
अणु
	काष्ठा scpi_dvfs_info *info = scpi_dvfs_info(dev);

	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	वापस info->latency;
पूर्ण

अटल पूर्णांक scpi_dvfs_add_opps_to_device(काष्ठा device *dev)
अणु
	पूर्णांक idx, ret;
	काष्ठा scpi_opp *opp;
	काष्ठा scpi_dvfs_info *info = scpi_dvfs_info(dev);

	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	अगर (!info->opps)
		वापस -EIO;

	क्रम (opp = info->opps, idx = 0; idx < info->count; idx++, opp++) अणु
		ret = dev_pm_opp_add(dev, opp->freq, opp->m_volt * 1000);
		अगर (ret) अणु
			dev_warn(dev, "failed to add opp %uHz %umV\n",
				 opp->freq, opp->m_volt);
			जबतक (idx-- > 0)
				dev_pm_opp_हटाओ(dev, (--opp)->freq);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक scpi_sensor_get_capability(u16 *sensors)
अणु
	__le16 cap;
	पूर्णांक ret;

	ret = scpi_send_message(CMD_SENSOR_CAPABILITIES, शून्य, 0, &cap,
				माप(cap));
	अगर (!ret)
		*sensors = le16_to_cpu(cap);

	वापस ret;
पूर्ण

अटल पूर्णांक scpi_sensor_get_info(u16 sensor_id, काष्ठा scpi_sensor_info *info)
अणु
	__le16 id = cpu_to_le16(sensor_id);
	काष्ठा _scpi_sensor_info _info;
	पूर्णांक ret;

	ret = scpi_send_message(CMD_SENSOR_INFO, &id, माप(id),
				&_info, माप(_info));
	अगर (!ret) अणु
		स_नकल(info, &_info, माप(*info));
		info->sensor_id = le16_to_cpu(_info.sensor_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scpi_sensor_get_value(u16 sensor, u64 *val)
अणु
	__le16 id = cpu_to_le16(sensor);
	__le64 value;
	पूर्णांक ret;

	ret = scpi_send_message(CMD_SENSOR_VALUE, &id, माप(id),
				&value, माप(value));
	अगर (ret)
		वापस ret;

	अगर (scpi_info->is_legacy)
		/* only 32-bits supported, upper 32 bits can be junk */
		*val = le32_to_cpup((__le32 *)&value);
	अन्यथा
		*val = le64_to_cpu(value);

	वापस 0;
पूर्ण

अटल पूर्णांक scpi_device_get_घातer_state(u16 dev_id)
अणु
	पूर्णांक ret;
	u8 pstate;
	__le16 id = cpu_to_le16(dev_id);

	ret = scpi_send_message(CMD_GET_DEVICE_PWR_STATE, &id,
				माप(id), &pstate, माप(pstate));
	वापस ret ? ret : pstate;
पूर्ण

अटल पूर्णांक scpi_device_set_घातer_state(u16 dev_id, u8 pstate)
अणु
	पूर्णांक stat;
	काष्ठा dev_pstate_set dev_set = अणु
		.dev_id = cpu_to_le16(dev_id),
		.pstate = pstate,
	पूर्ण;

	वापस scpi_send_message(CMD_SET_DEVICE_PWR_STATE, &dev_set,
				 माप(dev_set), &stat, माप(stat));
पूर्ण

अटल काष्ठा scpi_ops scpi_ops = अणु
	.get_version = scpi_get_version,
	.clk_get_range = scpi_clk_get_range,
	.clk_get_val = scpi_clk_get_val,
	.clk_set_val = scpi_clk_set_val,
	.dvfs_get_idx = scpi_dvfs_get_idx,
	.dvfs_set_idx = scpi_dvfs_set_idx,
	.dvfs_get_info = scpi_dvfs_get_info,
	.device_करोमुख्य_id = scpi_dev_करोमुख्य_id,
	.get_transition_latency = scpi_dvfs_get_transition_latency,
	.add_opps_to_device = scpi_dvfs_add_opps_to_device,
	.sensor_get_capability = scpi_sensor_get_capability,
	.sensor_get_info = scpi_sensor_get_info,
	.sensor_get_value = scpi_sensor_get_value,
	.device_get_घातer_state = scpi_device_get_घातer_state,
	.device_set_घातer_state = scpi_device_set_घातer_state,
पूर्ण;

काष्ठा scpi_ops *get_scpi_ops(व्योम)
अणु
	वापस scpi_info ? scpi_info->scpi_ops : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_scpi_ops);

अटल पूर्णांक scpi_init_versions(काष्ठा scpi_drvinfo *info)
अणु
	पूर्णांक ret;
	काष्ठा scp_capabilities caps;

	ret = scpi_send_message(CMD_SCPI_CAPABILITIES, शून्य, 0,
				&caps, माप(caps));
	अगर (!ret) अणु
		info->protocol_version = le32_to_cpu(caps.protocol_version);
		info->firmware_version = le32_to_cpu(caps.platक्रमm_version);
	पूर्ण
	/* Ignore error अगर not implemented */
	अगर (scpi_info->is_legacy && ret == -EOPNOTSUPP)
		वापस 0;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार protocol_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scpi_drvinfo *scpi_info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lu.%lu\n",
		FIELD_GET(PROTO_REV_MAJOR_MASK, scpi_info->protocol_version),
		FIELD_GET(PROTO_REV_MINOR_MASK, scpi_info->protocol_version));
पूर्ण
अटल DEVICE_ATTR_RO(protocol_version);

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scpi_drvinfo *scpi_info = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lu.%lu.%lu\n",
		FIELD_GET(FW_REV_MAJOR_MASK, scpi_info->firmware_version),
		FIELD_GET(FW_REV_MINOR_MASK, scpi_info->firmware_version),
		FIELD_GET(FW_REV_PATCH_MASK, scpi_info->firmware_version));
पूर्ण
अटल DEVICE_ATTR_RO(firmware_version);

अटल काष्ठा attribute *versions_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_protocol_version.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(versions);

अटल व्योम scpi_मुक्त_channels(व्योम *data)
अणु
	काष्ठा scpi_drvinfo *info = data;
	पूर्णांक i;

	क्रम (i = 0; i < info->num_chans; i++)
		mbox_मुक्त_channel(info->channels[i].chan);
पूर्ण

अटल पूर्णांक scpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा scpi_drvinfo *info = platक्रमm_get_drvdata(pdev);

	scpi_info = शून्य; /* stop exporting SCPI ops through get_scpi_ops */

	क्रम (i = 0; i < MAX_DVFS_DOMAINS && info->dvfs[i]; i++) अणु
		kमुक्त(info->dvfs[i]->opps);
		kमुक्त(info->dvfs[i]);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MAX_SCPI_XFERS		10
अटल पूर्णांक scpi_alloc_xfer_list(काष्ठा device *dev, काष्ठा scpi_chan *ch)
अणु
	पूर्णांक i;
	काष्ठा scpi_xfer *xfers;

	xfers = devm_kसुस्मृति(dev, MAX_SCPI_XFERS, माप(*xfers), GFP_KERNEL);
	अगर (!xfers)
		वापस -ENOMEM;

	ch->xfers = xfers;
	क्रम (i = 0; i < MAX_SCPI_XFERS; i++, xfers++) अणु
		init_completion(&xfers->करोne);
		list_add_tail(&xfers->node, &ch->xfers_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id legacy_scpi_of_match[] = अणु
	अणु.compatible = "arm,scpi-pre-1.0"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक scpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक count, idx, ret;
	काष्ठा resource res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	scpi_info = devm_kzalloc(dev, माप(*scpi_info), GFP_KERNEL);
	अगर (!scpi_info)
		वापस -ENOMEM;

	अगर (of_match_device(legacy_scpi_of_match, &pdev->dev))
		scpi_info->is_legacy = true;

	count = of_count_phandle_with_args(np, "mboxes", "#mbox-cells");
	अगर (count < 0) अणु
		dev_err(dev, "no mboxes property in '%pOF'\n", np);
		वापस -ENODEV;
	पूर्ण

	scpi_info->channels = devm_kसुस्मृति(dev, count, माप(काष्ठा scpi_chan),
					   GFP_KERNEL);
	अगर (!scpi_info->channels)
		वापस -ENOMEM;

	ret = devm_add_action(dev, scpi_मुक्त_channels, scpi_info);
	अगर (ret)
		वापस ret;

	क्रम (; scpi_info->num_chans < count; scpi_info->num_chans++) अणु
		resource_माप_प्रकार size;
		पूर्णांक idx = scpi_info->num_chans;
		काष्ठा scpi_chan *pchan = scpi_info->channels + idx;
		काष्ठा mbox_client *cl = &pchan->cl;
		काष्ठा device_node *shmem = of_parse_phandle(np, "shmem", idx);

		ret = of_address_to_resource(shmem, 0, &res);
		of_node_put(shmem);
		अगर (ret) अणु
			dev_err(dev, "failed to get SCPI payload mem resource\n");
			वापस ret;
		पूर्ण

		size = resource_size(&res);
		pchan->rx_payload = devm_ioremap(dev, res.start, size);
		अगर (!pchan->rx_payload) अणु
			dev_err(dev, "failed to ioremap SCPI payload\n");
			वापस -EADDRNOTAVAIL;
		पूर्ण
		pchan->tx_payload = pchan->rx_payload + (size >> 1);

		cl->dev = dev;
		cl->rx_callback = scpi_handle_remote_msg;
		cl->tx_prepare = scpi_tx_prepare;
		cl->tx_block = true;
		cl->tx_tout = 20;
		cl->knows_txकरोne = false; /* controller can't ack */

		INIT_LIST_HEAD(&pchan->rx_pending);
		INIT_LIST_HEAD(&pchan->xfers_list);
		spin_lock_init(&pchan->rx_lock);
		mutex_init(&pchan->xfers_lock);

		ret = scpi_alloc_xfer_list(dev, pchan);
		अगर (!ret) अणु
			pchan->chan = mbox_request_channel(cl, idx);
			अगर (!IS_ERR(pchan->chan))
				जारी;
			ret = PTR_ERR(pchan->chan);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to get channel%d err %d\n",
					idx, ret);
		पूर्ण
		वापस ret;
	पूर्ण

	scpi_info->commands = scpi_std_commands;

	platक्रमm_set_drvdata(pdev, scpi_info);

	अगर (scpi_info->is_legacy) अणु
		/* Replace with legacy variants */
		scpi_ops.clk_set_val = legacy_scpi_clk_set_val;
		scpi_info->commands = scpi_legacy_commands;

		/* Fill priority biपंचांगap */
		क्रम (idx = 0; idx < ARRAY_SIZE(legacy_hpriority_cmds); idx++)
			set_bit(legacy_hpriority_cmds[idx],
				scpi_info->cmd_priority);
	पूर्ण

	ret = scpi_init_versions(scpi_info);
	अगर (ret) अणु
		dev_err(dev, "incorrect or no SCP firmware found\n");
		वापस ret;
	पूर्ण

	अगर (scpi_info->is_legacy && !scpi_info->protocol_version &&
	    !scpi_info->firmware_version)
		dev_info(dev, "SCP Protocol legacy pre-1.0 firmware\n");
	अन्यथा
		dev_info(dev, "SCP Protocol %lu.%lu Firmware %lu.%lu.%lu version\n",
			 FIELD_GET(PROTO_REV_MAJOR_MASK,
				   scpi_info->protocol_version),
			 FIELD_GET(PROTO_REV_MINOR_MASK,
				   scpi_info->protocol_version),
			 FIELD_GET(FW_REV_MAJOR_MASK,
				   scpi_info->firmware_version),
			 FIELD_GET(FW_REV_MINOR_MASK,
				   scpi_info->firmware_version),
			 FIELD_GET(FW_REV_PATCH_MASK,
				   scpi_info->firmware_version));
	scpi_info->scpi_ops = &scpi_ops;

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id scpi_of_match[] = अणु
	अणु.compatible = "arm,scpi"पूर्ण,
	अणु.compatible = "arm,scpi-pre-1.0"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, scpi_of_match);

अटल काष्ठा platक्रमm_driver scpi_driver = अणु
	.driver = अणु
		.name = "scpi_protocol",
		.of_match_table = scpi_of_match,
		.dev_groups = versions_groups,
	पूर्ण,
	.probe = scpi_probe,
	.हटाओ = scpi_हटाओ,
पूर्ण;
module_platक्रमm_driver(scpi_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCPI mailbox protocol driver");
MODULE_LICENSE("GPL v2");
