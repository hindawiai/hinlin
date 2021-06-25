<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Logging driver क्रम ChromeOS EC based USBPD Charger.
 *
 * Copyright 2018 Google LLC.
 */

#समावेश <linux/kसमय.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा DRV_NAME "cros-usbpd-logger"

#घोषणा CROS_USBPD_MAX_LOG_ENTRIES	30
#घोषणा CROS_USBPD_LOG_UPDATE_DELAY	msecs_to_jअगरfies(60000)
#घोषणा CROS_USBPD_DATA_SIZE		16
#घोषणा CROS_USBPD_LOG_RESP_SIZE	(माप(काष्ठा ec_response_pd_log) + \
					 CROS_USBPD_DATA_SIZE)
#घोषणा CROS_USBPD_BUFFER_SIZE		(माप(काष्ठा cros_ec_command) + \
					 CROS_USBPD_LOG_RESP_SIZE)
/* Buffer क्रम building the PDLOG string */
#घोषणा BUF_SIZE	80

काष्ठा logger_data अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_dev *ec_dev;
	u8 ec_buffer[CROS_USBPD_BUFFER_SIZE];
	काष्ठा delayed_work log_work;
	काष्ठा workqueue_काष्ठा *log_workqueue;
पूर्ण;

अटल स्थिर अक्षर * स्थिर chg_type_names[] = अणु
	"None", "PD", "Type-C", "Proprietary", "DCP", "CDP", "SDP",
	"Other", "VBUS"
पूर्ण;

अटल स्थिर अक्षर * स्थिर role_names[] = अणु
	"Disconnected", "SRC", "SNK", "SNK (not charging)"
पूर्ण;

अटल स्थिर अक्षर * स्थिर fault_names[] = अणु
	"---", "OCP", "fast OCP", "OVP", "Discharge"
पूर्ण;

__म_लिखो(3, 4)
अटल पूर्णांक append_str(अक्षर *buf, पूर्णांक pos, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vsnम_लिखो(buf + pos, BUF_SIZE - pos, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण

अटल काष्ठा ec_response_pd_log *ec_get_log_entry(काष्ठा logger_data *logger)
अणु
	काष्ठा cros_ec_dev *ec_dev = logger->ec_dev;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = (काष्ठा cros_ec_command *)logger->ec_buffer;

	msg->command = ec_dev->cmd_offset + EC_CMD_PD_GET_LOG_ENTRY;
	msg->insize = CROS_USBPD_LOG_RESP_SIZE;

	ret = cros_ec_cmd_xfer_status(ec_dev->ec_dev, msg);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस (काष्ठा ec_response_pd_log *)msg->data;
पूर्ण

अटल व्योम cros_usbpd_prपूर्णांक_log_entry(काष्ठा ec_response_pd_log *r,
				       kसमय_प्रकार tstamp)
अणु
	स्थिर अक्षर *fault, *role, *chg_type;
	काष्ठा usb_chg_measures *meas;
	काष्ठा mcdp_info *minfo;
	पूर्णांक role_idx, type_idx;
	अक्षर buf[BUF_SIZE + 1];
	काष्ठा rtc_समय rt;
	पूर्णांक len = 0;
	s32 rem;
	पूर्णांक i;

	/* The बारtamp is the number of 1024th of seconds in the past */
	tstamp = kसमय_sub_us(tstamp, r->बारtamp << PD_LOG_TIMESTAMP_SHIFT);
	rt = rtc_kसमय_प्रकारo_पंचांग(tstamp);

	चयन (r->type) अणु
	हाल PD_EVENT_MCU_CHARGE:
		अगर (r->data & CHARGE_FLAGS_OVERRIDE)
			len += append_str(buf, len, "override ");

		अगर (r->data & CHARGE_FLAGS_DELAYED_OVERRIDE)
			len += append_str(buf, len, "pending_override ");

		role_idx = r->data & CHARGE_FLAGS_ROLE_MASK;
		role = role_idx < ARRAY_SIZE(role_names) ?
			role_names[role_idx] : "Unknown";

		type_idx = (r->data & CHARGE_FLAGS_TYPE_MASK)
			 >> CHARGE_FLAGS_TYPE_SHIFT;

		chg_type = type_idx < ARRAY_SIZE(chg_type_names) ?
			chg_type_names[type_idx] : "???";

		अगर (role_idx == USB_PD_PORT_POWER_DISCONNECTED ||
		    role_idx == USB_PD_PORT_POWER_SOURCE) अणु
			len += append_str(buf, len, "%s", role);
			अवरोध;
		पूर्ण

		meas = (काष्ठा usb_chg_measures *)r->payload;
		len += append_str(buf, len, "%s %s %s %dmV max %dmV / %dmA",
				  role,	r->data & CHARGE_FLAGS_DUAL_ROLE ?
				  "DRP" : "Charger",
				  chg_type, meas->voltage_now,
				  meas->voltage_max, meas->current_max);
		अवरोध;
	हाल PD_EVENT_ACC_RW_FAIL:
		len += append_str(buf, len, "RW signature check failed");
		अवरोध;
	हाल PD_EVENT_PS_FAULT:
		fault = r->data < ARRAY_SIZE(fault_names) ? fault_names[r->data]
							  : "???";
		len += append_str(buf, len, "Power supply fault: %s", fault);
		अवरोध;
	हाल PD_EVENT_VIDEO_DP_MODE:
		len += append_str(buf, len, "DP mode %sabled", r->data == 1 ?
				  "en" : "dis");
		अवरोध;
	हाल PD_EVENT_VIDEO_CODEC:
		minfo = (काष्ठा mcdp_info *)r->payload;
		len += append_str(buf, len, "HDMI info: family:%04x chipid:%04x ",
				  MCDP_FAMILY(minfo->family),
				  MCDP_CHIPID(minfo->chipid));
		len += append_str(buf, len, "irom:%d.%d.%d fw:%d.%d.%d",
				  minfo->irom.major, minfo->irom.minor,
				  minfo->irom.build, minfo->fw.major,
				  minfo->fw.minor, minfo->fw.build);
		अवरोध;
	शेष:
		len += append_str(buf, len, "Event %02x (%04x) [", r->type,
				  r->data);

		क्रम (i = 0; i < PD_LOG_SIZE(r->size_port); i++)
			len += append_str(buf, len, "%02x ", r->payload[i]);

		len += append_str(buf, len, "]");
		अवरोध;
	पूर्ण

	भाग_s64_rem(kसमय_प्रकारo_ms(tstamp), MSEC_PER_SEC, &rem);
	pr_info("PDLOG %d/%02d/%02d %02d:%02d:%02d.%03d P%d %s\n",
		rt.पंचांग_year + 1900, rt.पंचांग_mon + 1, rt.पंचांग_mday,
		rt.पंचांग_hour, rt.पंचांग_min, rt.पंचांग_sec, rem,
		PD_LOG_PORT(r->size_port), buf);
पूर्ण

अटल व्योम cros_usbpd_log_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा logger_data *logger = container_of(to_delayed_work(work),
						  काष्ठा logger_data,
						  log_work);
	काष्ठा device *dev = logger->dev;
	काष्ठा ec_response_pd_log *r;
	पूर्णांक entries = 0;
	kसमय_प्रकार now;

	जबतक (entries++ < CROS_USBPD_MAX_LOG_ENTRIES) अणु
		r = ec_get_log_entry(logger);
		now = kसमय_get_real();
		अगर (IS_ERR(r)) अणु
			dev_dbg(dev, "Cannot get PD log %ld\n", PTR_ERR(r));
			अवरोध;
		पूर्ण
		अगर (r->type == PD_EVENT_NO_ENTRY)
			अवरोध;

		cros_usbpd_prपूर्णांक_log_entry(r, now);
	पूर्ण

	queue_delayed_work(logger->log_workqueue, &logger->log_work,
			   CROS_USBPD_LOG_UPDATE_DELAY);
पूर्ण

अटल पूर्णांक cros_usbpd_logger_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	काष्ठा device *dev = &pd->dev;
	काष्ठा logger_data *logger;

	logger = devm_kzalloc(dev, माप(*logger), GFP_KERNEL);
	अगर (!logger)
		वापस -ENOMEM;

	logger->dev = dev;
	logger->ec_dev = ec_dev;

	platक्रमm_set_drvdata(pd, logger);

	/* Retrieve PD event logs periodically */
	INIT_DELAYED_WORK(&logger->log_work, cros_usbpd_log_check);
	logger->log_workqueue =	create_singlethपढ़ो_workqueue("cros_usbpd_log");
	अगर (!logger->log_workqueue)
		वापस -ENOMEM;

	queue_delayed_work(logger->log_workqueue, &logger->log_work,
			   CROS_USBPD_LOG_UPDATE_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_logger_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा logger_data *logger = platक्रमm_get_drvdata(pd);

	cancel_delayed_work_sync(&logger->log_work);
	destroy_workqueue(logger->log_workqueue);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_usbpd_logger_resume(काष्ठा device *dev)
अणु
	काष्ठा logger_data *logger = dev_get_drvdata(dev);

	queue_delayed_work(logger->log_workqueue, &logger->log_work,
			   CROS_USBPD_LOG_UPDATE_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_usbpd_logger_suspend(काष्ठा device *dev)
अणु
	काष्ठा logger_data *logger = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&logger->log_work);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cros_usbpd_logger_pm_ops, cros_usbpd_logger_suspend,
			 cros_usbpd_logger_resume);

अटल काष्ठा platक्रमm_driver cros_usbpd_logger_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_usbpd_logger_pm_ops,
	पूर्ण,
	.probe = cros_usbpd_logger_probe,
	.हटाओ = cros_usbpd_logger_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_usbpd_logger_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Logging driver for ChromeOS EC USBPD Charger.");
MODULE_ALIAS("platform:" DRV_NAME);
