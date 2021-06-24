<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM X-Gene SoC Hardware Monitoring Driver
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *         Hoan Tran <hotran@apm.com>
 *
 * This driver provides the following features:
 *  - Retrieve CPU total घातer (uW)
 *  - Retrieve IO total घातer (uW)
 *  - Retrieve SoC temperature (milli-degree C) and alarm
 */
#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <acpi/pcc.h>

/* SLIMpro message defines */
#घोषणा MSG_TYPE_DBG			0
#घोषणा MSG_TYPE_ERR			7
#घोषणा MSG_TYPE_PWRMGMT		9

#घोषणा MSG_TYPE(v)			(((v) & 0xF0000000) >> 28)
#घोषणा MSG_TYPE_SET(v)			(((v) << 28) & 0xF0000000)
#घोषणा MSG_SUBTYPE(v)			(((v) & 0x0F000000) >> 24)
#घोषणा MSG_SUBTYPE_SET(v)		(((v) << 24) & 0x0F000000)

#घोषणा DBG_SUBTYPE_SENSOR_READ		4
#घोषणा SENSOR_RD_MSG			0x04FFE902
#घोषणा SENSOR_RD_EN_ADDR(a)		((a) & 0x000FFFFF)
#घोषणा PMD_PWR_REG			0x20
#घोषणा PMD_PWR_MW_REG			0x26
#घोषणा SOC_PWR_REG			0x21
#घोषणा SOC_PWR_MW_REG			0x27
#घोषणा SOC_TEMP_REG			0x10

#घोषणा TEMP_NEGATIVE_BIT		8
#घोषणा SENSOR_INVALID_DATA		BIT(15)

#घोषणा PWRMGMT_SUBTYPE_TPC		1
#घोषणा TPC_ALARM			2
#घोषणा TPC_GET_ALARM			3
#घोषणा TPC_CMD(v)			(((v) & 0x00FF0000) >> 16)
#घोषणा TPC_CMD_SET(v)			(((v) << 16) & 0x00FF0000)
#घोषणा TPC_EN_MSG(hndl, cmd, type) \
	(MSG_TYPE_SET(MSG_TYPE_PWRMGMT) | \
	MSG_SUBTYPE_SET(hndl) | TPC_CMD_SET(cmd) | type)

/* PCC defines */
#घोषणा PCC_SIGNATURE_MASK		0x50424300
#घोषणा PCCC_GENERATE_DB_INT		BIT(15)
#घोषणा PCCS_CMD_COMPLETE		BIT(0)
#घोषणा PCCS_SCI_DOORBEL		BIT(1)
#घोषणा PCCS_PLATFORM_NOTIFICATION	BIT(3)
/*
 * Arbitrary retries in हाल the remote processor is slow to respond
 * to PCC commands
 */
#घोषणा PCC_NUM_RETRIES			500

#घोषणा ASYNC_MSG_FIFO_SIZE		16
#घोषणा MBOX_OP_TIMEOUTMS		1000

#घोषणा WATT_TO_mWATT(x)		((x) * 1000)
#घोषणा mWATT_TO_uWATT(x)		((x) * 1000)
#घोषणा CELSIUS_TO_mCELSIUS(x)		((x) * 1000)

#घोषणा to_xgene_hwmon_dev(cl)		\
	container_of(cl, काष्ठा xgene_hwmon_dev, mbox_client)

क्रमागत xgene_hwmon_version अणु
	XGENE_HWMON_V1 = 0,
	XGENE_HWMON_V2 = 1,
पूर्ण;

काष्ठा slimpro_resp_msg अणु
	u32 msg;
	u32 param1;
	u32 param2;
पूर्ण __packed;

काष्ठा xgene_hwmon_dev अणु
	काष्ठा device		*dev;
	काष्ठा mbox_chan	*mbox_chan;
	काष्ठा mbox_client	mbox_client;
	पूर्णांक			mbox_idx;

	spinlock_t		kfअगरo_lock;
	काष्ठा mutex		rd_mutex;
	काष्ठा completion	rd_complete;
	पूर्णांक			resp_pending;
	काष्ठा slimpro_resp_msg sync_msg;

	काष्ठा work_काष्ठा	workq;
	काष्ठा kfअगरo_rec_ptr_1	async_msg_fअगरo;

	काष्ठा device		*hwmon_dev;
	bool			temp_critical_alarm;

	phys_addr_t		comm_base_addr;
	व्योम			*pcc_comm_addr;
	u64			usecs_lat;
पूर्ण;

/*
 * This function tests and clears a biपंचांगask then वापसs its old value
 */
अटल u16 xgene_word_tst_and_clr(u16 *addr, u16 mask)
अणु
	u16 ret, val;

	val = le16_to_cpu(READ_ONCE(*addr));
	ret = val & mask;
	val &= ~mask;
	WRITE_ONCE(*addr, cpu_to_le16(val));

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_hwmon_pcc_rd(काष्ठा xgene_hwmon_dev *ctx, u32 *msg)
अणु
	काष्ठा acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;
	u32 *ptr = (व्योम *)(generic_comm_base + 1);
	पूर्णांक rc, i;
	u16 val;

	mutex_lock(&ctx->rd_mutex);
	init_completion(&ctx->rd_complete);
	ctx->resp_pending = true;

	/* Write signature क्रम subspace */
	WRITE_ONCE(generic_comm_base->signature,
		   cpu_to_le32(PCC_SIGNATURE_MASK | ctx->mbox_idx));

	/* Write to the shared command region */
	WRITE_ONCE(generic_comm_base->command,
		   cpu_to_le16(MSG_TYPE(msg[0]) | PCCC_GENERATE_DB_INT));

	/* Flip CMD COMPLETE bit */
	val = le16_to_cpu(READ_ONCE(generic_comm_base->status));
	val &= ~PCCS_CMD_COMPLETE;
	WRITE_ONCE(generic_comm_base->status, cpu_to_le16(val));

	/* Copy the message to the PCC comm space */
	क्रम (i = 0; i < माप(काष्ठा slimpro_resp_msg) / 4; i++)
		WRITE_ONCE(ptr[i], cpu_to_le32(msg[i]));

	/* Ring the करोorbell */
	rc = mbox_send_message(ctx->mbox_chan, msg);
	अगर (rc < 0) अणु
		dev_err(ctx->dev, "Mailbox send error %d\n", rc);
		जाओ err;
	पूर्ण
	अगर (!रुको_क्रम_completion_समयout(&ctx->rd_complete,
					 usecs_to_jअगरfies(ctx->usecs_lat))) अणु
		dev_err(ctx->dev, "Mailbox operation timed out\n");
		rc = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	/* Check क्रम error message */
	अगर (MSG_TYPE(ctx->sync_msg.msg) == MSG_TYPE_ERR) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	msg[0] = ctx->sync_msg.msg;
	msg[1] = ctx->sync_msg.param1;
	msg[2] = ctx->sync_msg.param2;

err:
	mbox_chan_txकरोne(ctx->mbox_chan, 0);
	ctx->resp_pending = false;
	mutex_unlock(&ctx->rd_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_hwmon_rd(काष्ठा xgene_hwmon_dev *ctx, u32 *msg)
अणु
	पूर्णांक rc;

	mutex_lock(&ctx->rd_mutex);
	init_completion(&ctx->rd_complete);
	ctx->resp_pending = true;

	rc = mbox_send_message(ctx->mbox_chan, msg);
	अगर (rc < 0) अणु
		dev_err(ctx->dev, "Mailbox send error %d\n", rc);
		जाओ err;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ctx->rd_complete,
					 msecs_to_jअगरfies(MBOX_OP_TIMEOUTMS))) अणु
		dev_err(ctx->dev, "Mailbox operation timed out\n");
		rc = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	/* Check क्रम error message */
	अगर (MSG_TYPE(ctx->sync_msg.msg) == MSG_TYPE_ERR) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	msg[0] = ctx->sync_msg.msg;
	msg[1] = ctx->sync_msg.param1;
	msg[2] = ctx->sync_msg.param2;

err:
	ctx->resp_pending = false;
	mutex_unlock(&ctx->rd_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_hwmon_reg_map_rd(काष्ठा xgene_hwmon_dev *ctx, u32 addr,
				  u32 *data)
अणु
	u32 msg[3];
	पूर्णांक rc;

	msg[0] = SENSOR_RD_MSG;
	msg[1] = SENSOR_RD_EN_ADDR(addr);
	msg[2] = 0;

	अगर (acpi_disabled)
		rc = xgene_hwmon_rd(ctx, msg);
	अन्यथा
		rc = xgene_hwmon_pcc_rd(ctx, msg);

	अगर (rc < 0)
		वापस rc;

	/*
	 * Check अगर sensor data is valid.
	 */
	अगर (msg[1] & SENSOR_INVALID_DATA)
		वापस -ENODATA;

	*data = msg[1];

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_hwmon_get_notअगरication_msg(काष्ठा xgene_hwmon_dev *ctx,
					    u32 *amsg)
अणु
	u32 msg[3];
	पूर्णांक rc;

	msg[0] = TPC_EN_MSG(PWRMGMT_SUBTYPE_TPC, TPC_GET_ALARM, 0);
	msg[1] = 0;
	msg[2] = 0;

	rc = xgene_hwmon_pcc_rd(ctx, msg);
	अगर (rc < 0)
		वापस rc;

	amsg[0] = msg[0];
	amsg[1] = msg[1];
	amsg[2] = msg[2];

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_hwmon_get_cpu_pwr(काष्ठा xgene_hwmon_dev *ctx, u32 *val)
अणु
	u32 watt, mwatt;
	पूर्णांक rc;

	rc = xgene_hwmon_reg_map_rd(ctx, PMD_PWR_REG, &watt);
	अगर (rc < 0)
		वापस rc;

	rc = xgene_hwmon_reg_map_rd(ctx, PMD_PWR_MW_REG, &mwatt);
	अगर (rc < 0)
		वापस rc;

	*val = WATT_TO_mWATT(watt) + mwatt;
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_hwmon_get_io_pwr(काष्ठा xgene_hwmon_dev *ctx, u32 *val)
अणु
	u32 watt, mwatt;
	पूर्णांक rc;

	rc = xgene_hwmon_reg_map_rd(ctx, SOC_PWR_REG, &watt);
	अगर (rc < 0)
		वापस rc;

	rc = xgene_hwmon_reg_map_rd(ctx, SOC_PWR_MW_REG, &mwatt);
	अगर (rc < 0)
		वापस rc;

	*val = WATT_TO_mWATT(watt) + mwatt;
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_hwmon_get_temp(काष्ठा xgene_hwmon_dev *ctx, u32 *val)
अणु
	वापस xgene_hwmon_reg_map_rd(ctx, SOC_TEMP_REG, val);
पूर्ण

/*
 * Sensor temperature/घातer functions
 */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा xgene_hwmon_dev *ctx = dev_get_drvdata(dev);
	पूर्णांक rc, temp;
	u32 val;

	rc = xgene_hwmon_get_temp(ctx, &val);
	अगर (rc < 0)
		वापस rc;

	temp = sign_extend32(val, TEMP_NEGATIVE_BIT);

	वापस sysfs_emit(buf, "%d\n", CELSIUS_TO_mCELSIUS(temp));
पूर्ण

अटल sमाप_प्रकार temp1_label_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "SoC Temperature\n");
पूर्ण

अटल sमाप_प्रकार temp1_critical_alarm_show(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 अक्षर *buf)
अणु
	काष्ठा xgene_hwmon_dev *ctx = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", ctx->temp_critical_alarm);
पूर्ण

अटल sमाप_प्रकार घातer1_label_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "CPU power\n");
पूर्ण

अटल sमाप_प्रकार घातer2_label_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "IO power\n");
पूर्ण

अटल sमाप_प्रकार घातer1_input_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा xgene_hwmon_dev *ctx = dev_get_drvdata(dev);
	u32 val;
	पूर्णांक rc;

	rc = xgene_hwmon_get_cpu_pwr(ctx, &val);
	अगर (rc < 0)
		वापस rc;

	वापस sysfs_emit(buf, "%u\n", mWATT_TO_uWATT(val));
पूर्ण

अटल sमाप_प्रकार घातer2_input_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा xgene_hwmon_dev *ctx = dev_get_drvdata(dev);
	u32 val;
	पूर्णांक rc;

	rc = xgene_hwmon_get_io_pwr(ctx, &val);
	अगर (rc < 0)
		वापस rc;

	वापस sysfs_emit(buf, "%u\n", mWATT_TO_uWATT(val));
पूर्ण

अटल DEVICE_ATTR_RO(temp1_label);
अटल DEVICE_ATTR_RO(temp1_input);
अटल DEVICE_ATTR_RO(temp1_critical_alarm);
अटल DEVICE_ATTR_RO(घातer1_label);
अटल DEVICE_ATTR_RO(घातer1_input);
अटल DEVICE_ATTR_RO(घातer2_label);
अटल DEVICE_ATTR_RO(घातer2_input);

अटल काष्ठा attribute *xgene_hwmon_attrs[] = अणु
	&dev_attr_temp1_label.attr,
	&dev_attr_temp1_input.attr,
	&dev_attr_temp1_critical_alarm.attr,
	&dev_attr_घातer1_label.attr,
	&dev_attr_घातer1_input.attr,
	&dev_attr_घातer2_label.attr,
	&dev_attr_घातer2_input.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(xgene_hwmon);

अटल पूर्णांक xgene_hwmon_tpc_alarm(काष्ठा xgene_hwmon_dev *ctx,
				 काष्ठा slimpro_resp_msg *amsg)
अणु
	ctx->temp_critical_alarm = !!amsg->param2;
	sysfs_notअगरy(&ctx->dev->kobj, शून्य, "temp1_critical_alarm");

	वापस 0;
पूर्ण

अटल व्योम xgene_hwmon_process_pwrmsg(काष्ठा xgene_hwmon_dev *ctx,
				       काष्ठा slimpro_resp_msg *amsg)
अणु
	अगर ((MSG_SUBTYPE(amsg->msg) == PWRMGMT_SUBTYPE_TPC) &&
	    (TPC_CMD(amsg->msg) == TPC_ALARM))
		xgene_hwmon_tpc_alarm(ctx, amsg);
पूर्ण

/*
 * This function is called to process async work queue
 */
अटल व्योम xgene_hwmon_evt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा slimpro_resp_msg amsg;
	काष्ठा xgene_hwmon_dev *ctx;
	पूर्णांक ret;

	ctx = container_of(work, काष्ठा xgene_hwmon_dev, workq);
	जबतक (kfअगरo_out_spinlocked(&ctx->async_msg_fअगरo, &amsg,
				    माप(काष्ठा slimpro_resp_msg),
				    &ctx->kfअगरo_lock)) अणु
		/*
		 * If PCC, send a consumer command to Platक्रमm to get info
		 * If Slimpro Mailbox, get message from specअगरic FIFO
		 */
		अगर (!acpi_disabled) अणु
			ret = xgene_hwmon_get_notअगरication_msg(ctx,
							       (u32 *)&amsg);
			अगर (ret < 0)
				जारी;
		पूर्ण

		अगर (MSG_TYPE(amsg.msg) == MSG_TYPE_PWRMGMT)
			xgene_hwmon_process_pwrmsg(ctx, &amsg);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_hwmon_rx_पढ़ोy(काष्ठा xgene_hwmon_dev *ctx, व्योम *msg)
अणु
	अगर (IS_ERR_OR_शून्य(ctx->hwmon_dev) && !ctx->resp_pending) अणु
		/* Enqueue to the FIFO */
		kfअगरo_in_spinlocked(&ctx->async_msg_fअगरo, msg,
				    माप(काष्ठा slimpro_resp_msg),
				    &ctx->kfअगरo_lock);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is called when the SLIMpro Mailbox received a message
 */
अटल व्योम xgene_hwmon_rx_cb(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा xgene_hwmon_dev *ctx = to_xgene_hwmon_dev(cl);

	/*
	 * While the driver रेजिस्टरs with the mailbox framework, an पूर्णांकerrupt
	 * can be pending beक्रमe the probe function completes its
	 * initialization. If such condition occurs, just queue up the message
	 * as the driver is not पढ़ोy क्रम servicing the callback.
	 */
	अगर (xgene_hwmon_rx_पढ़ोy(ctx, msg) < 0)
		वापस;

	/*
	 * Response message क्रमmat:
	 * msg[0] is the वापस code of the operation
	 * msg[1] is the first parameter word
	 * msg[2] is the second parameter word
	 *
	 * As message only supports dword size, just assign it.
	 */

	/* Check क्रम sync query */
	अगर (ctx->resp_pending &&
	    ((MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_ERR) ||
	     (MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_DBG &&
	      MSG_SUBTYPE(((u32 *)msg)[0]) == DBG_SUBTYPE_SENSOR_READ) ||
	     (MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_PWRMGMT &&
	      MSG_SUBTYPE(((u32 *)msg)[0]) == PWRMGMT_SUBTYPE_TPC &&
	      TPC_CMD(((u32 *)msg)[0]) == TPC_ALARM))) अणु
		ctx->sync_msg.msg = ((u32 *)msg)[0];
		ctx->sync_msg.param1 = ((u32 *)msg)[1];
		ctx->sync_msg.param2 = ((u32 *)msg)[2];

		/* Operation रुकोing क्रम response */
		complete(&ctx->rd_complete);

		वापस;
	पूर्ण

	/* Enqueue to the FIFO */
	kfअगरo_in_spinlocked(&ctx->async_msg_fअगरo, msg,
			    माप(काष्ठा slimpro_resp_msg), &ctx->kfअगरo_lock);
	/* Schedule the bottom handler */
	schedule_work(&ctx->workq);
पूर्ण

/*
 * This function is called when the PCC Mailbox received a message
 */
अटल व्योम xgene_hwmon_pcc_rx_cb(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा xgene_hwmon_dev *ctx = to_xgene_hwmon_dev(cl);
	काष्ठा acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;
	काष्ठा slimpro_resp_msg amsg;

	/*
	 * While the driver रेजिस्टरs with the mailbox framework, an पूर्णांकerrupt
	 * can be pending beक्रमe the probe function completes its
	 * initialization. If such condition occurs, just queue up the message
	 * as the driver is not पढ़ोy क्रम servicing the callback.
	 */
	अगर (xgene_hwmon_rx_पढ़ोy(ctx, &amsg) < 0)
		वापस;

	msg = generic_comm_base + 1;
	/* Check अगर platक्रमm sends पूर्णांकerrupt */
	अगर (!xgene_word_tst_and_clr(&generic_comm_base->status,
				    PCCS_SCI_DOORBEL))
		वापस;

	/*
	 * Response message क्रमmat:
	 * msg[0] is the वापस code of the operation
	 * msg[1] is the first parameter word
	 * msg[2] is the second parameter word
	 *
	 * As message only supports dword size, just assign it.
	 */

	/* Check क्रम sync query */
	अगर (ctx->resp_pending &&
	    ((MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_ERR) ||
	     (MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_DBG &&
	      MSG_SUBTYPE(((u32 *)msg)[0]) == DBG_SUBTYPE_SENSOR_READ) ||
	     (MSG_TYPE(((u32 *)msg)[0]) == MSG_TYPE_PWRMGMT &&
	      MSG_SUBTYPE(((u32 *)msg)[0]) == PWRMGMT_SUBTYPE_TPC &&
	      TPC_CMD(((u32 *)msg)[0]) == TPC_ALARM))) अणु
		/* Check अगर platक्रमm completes command */
		अगर (xgene_word_tst_and_clr(&generic_comm_base->status,
					   PCCS_CMD_COMPLETE)) अणु
			ctx->sync_msg.msg = ((u32 *)msg)[0];
			ctx->sync_msg.param1 = ((u32 *)msg)[1];
			ctx->sync_msg.param2 = ((u32 *)msg)[2];

			/* Operation रुकोing क्रम response */
			complete(&ctx->rd_complete);

			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Platक्रमm notअगरies पूर्णांकerrupt to OSPM.
	 * OPSM schedules a consumer command to get this inक्रमmation
	 * in a workqueue. Platक्रमm must रुको until OSPM has issued
	 * a consumer command that serves this notअगरication.
	 */

	/* Enqueue to the FIFO */
	kfअगरo_in_spinlocked(&ctx->async_msg_fअगरo, &amsg,
			    माप(काष्ठा slimpro_resp_msg), &ctx->kfअगरo_lock);
	/* Schedule the bottom handler */
	schedule_work(&ctx->workq);
पूर्ण

अटल व्योम xgene_hwmon_tx_करोne(काष्ठा mbox_client *cl, व्योम *msg, पूर्णांक ret)
अणु
	अगर (ret) अणु
		dev_dbg(cl->dev, "TX did not complete: CMD sent:%x, ret:%d\n",
			*(u16 *)msg, ret);
	पूर्ण अन्यथा अणु
		dev_dbg(cl->dev, "TX completed. CMD sent:%x, ret:%d\n",
			*(u16 *)msg, ret);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_hwmon_acpi_match[] = अणु
	अणु"APMC0D29", XGENE_HWMON_V1पूर्ण,
	अणु"APMC0D8A", XGENE_HWMON_V2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_hwmon_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक xgene_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_hwmon_dev *ctx;
	काष्ठा mbox_client *cl;
	पूर्णांक rc;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ctx);
	cl = &ctx->mbox_client;

	spin_lock_init(&ctx->kfअगरo_lock);
	mutex_init(&ctx->rd_mutex);

	rc = kfअगरo_alloc(&ctx->async_msg_fअगरo,
			 माप(काष्ठा slimpro_resp_msg) * ASYNC_MSG_FIFO_SIZE,
			 GFP_KERNEL);
	अगर (rc)
		वापस -ENOMEM;

	INIT_WORK(&ctx->workq, xgene_hwmon_evt_work);

	/* Request mailbox channel */
	cl->dev = &pdev->dev;
	cl->tx_करोne = xgene_hwmon_tx_करोne;
	cl->tx_block = false;
	cl->tx_tout = MBOX_OP_TIMEOUTMS;
	cl->knows_txकरोne = false;
	अगर (acpi_disabled) अणु
		cl->rx_callback = xgene_hwmon_rx_cb;
		ctx->mbox_chan = mbox_request_channel(cl, 0);
		अगर (IS_ERR(ctx->mbox_chan)) अणु
			dev_err(&pdev->dev,
				"SLIMpro mailbox channel request failed\n");
			rc = -ENODEV;
			जाओ out_mbox_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा acpi_pcct_hw_reduced *cppc_ss;
		स्थिर काष्ठा acpi_device_id *acpi_id;
		पूर्णांक version;

		acpi_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
					    &pdev->dev);
		अगर (!acpi_id)
			वापस -EINVAL;

		version = (पूर्णांक)acpi_id->driver_data;

		अगर (device_property_पढ़ो_u32(&pdev->dev, "pcc-channel",
					     &ctx->mbox_idx)) अणु
			dev_err(&pdev->dev, "no pcc-channel property\n");
			rc = -ENODEV;
			जाओ out_mbox_मुक्त;
		पूर्ण

		cl->rx_callback = xgene_hwmon_pcc_rx_cb;
		ctx->mbox_chan = pcc_mbox_request_channel(cl, ctx->mbox_idx);
		अगर (IS_ERR(ctx->mbox_chan)) अणु
			dev_err(&pdev->dev,
				"PPC channel request failed\n");
			rc = -ENODEV;
			जाओ out_mbox_मुक्त;
		पूर्ण

		/*
		 * The PCC mailbox controller driver should
		 * have parsed the PCCT (global table of all
		 * PCC channels) and stored poपूर्णांकers to the
		 * subspace communication region in con_priv.
		 */
		cppc_ss = ctx->mbox_chan->con_priv;
		अगर (!cppc_ss) अणु
			dev_err(&pdev->dev, "PPC subspace not found\n");
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (!ctx->mbox_chan->mbox->txकरोne_irq) अणु
			dev_err(&pdev->dev, "PCC IRQ not supported\n");
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		/*
		 * This is the shared communication region
		 * क्रम the OS and Platक्रमm to communicate over.
		 */
		ctx->comm_base_addr = cppc_ss->base_address;
		अगर (ctx->comm_base_addr) अणु
			अगर (version == XGENE_HWMON_V2)
				ctx->pcc_comm_addr = (व्योम __क्रमce *)ioremap(
							ctx->comm_base_addr,
							cppc_ss->length);
			अन्यथा
				ctx->pcc_comm_addr = memremap(
							ctx->comm_base_addr,
							cppc_ss->length,
							MEMREMAP_WB);
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Failed to get PCC comm region\n");
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (!ctx->pcc_comm_addr) अणु
			dev_err(&pdev->dev,
				"Failed to ioremap PCC comm region\n");
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		/*
		 * cppc_ss->latency is just a Nominal value. In reality
		 * the remote processor could be much slower to reply.
		 * So add an arbitrary amount of रुको on top of Nominal.
		 */
		ctx->usecs_lat = PCC_NUM_RETRIES * cppc_ss->latency;
	पूर्ण

	ctx->hwmon_dev = hwmon_device_रेजिस्टर_with_groups(ctx->dev,
							   "apm_xgene",
							   ctx,
							   xgene_hwmon_groups);
	अगर (IS_ERR(ctx->hwmon_dev)) अणु
		dev_err(&pdev->dev, "Failed to register HW monitor device\n");
		rc = PTR_ERR(ctx->hwmon_dev);
		जाओ out;
	पूर्ण

	/*
	 * Schedule the bottom handler अगर there is a pending message.
	 */
	schedule_work(&ctx->workq);

	dev_info(&pdev->dev, "APM X-Gene SoC HW monitor driver registered\n");

	वापस 0;

out:
	अगर (acpi_disabled)
		mbox_मुक्त_channel(ctx->mbox_chan);
	अन्यथा
		pcc_mbox_मुक्त_channel(ctx->mbox_chan);
out_mbox_मुक्त:
	kfअगरo_मुक्त(&ctx->async_msg_fअगरo);

	वापस rc;
पूर्ण

अटल पूर्णांक xgene_hwmon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_hwmon_dev *ctx = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(ctx->hwmon_dev);
	kfअगरo_मुक्त(&ctx->async_msg_fअगरo);
	अगर (acpi_disabled)
		mbox_मुक्त_channel(ctx->mbox_chan);
	अन्यथा
		pcc_mbox_मुक्त_channel(ctx->mbox_chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_hwmon_of_match[] = अणु
	अणु.compatible = "apm,xgene-slimpro-hwmon"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_hwmon_of_match);

अटल काष्ठा platक्रमm_driver xgene_hwmon_driver = अणु
	.probe = xgene_hwmon_probe,
	.हटाओ = xgene_hwmon_हटाओ,
	.driver = अणु
		.name = "xgene-slimpro-hwmon",
		.of_match_table = xgene_hwmon_of_match,
		.acpi_match_table = ACPI_PTR(xgene_hwmon_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xgene_hwmon_driver);

MODULE_DESCRIPTION("APM X-Gene SoC hardware monitor");
MODULE_LICENSE("GPL");
