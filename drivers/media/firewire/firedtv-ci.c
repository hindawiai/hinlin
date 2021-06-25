<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 * Copyright (C) 2008 Henrik Kurelid <henrik@kurelid.se>
 */

#समावेश <linux/device.h>
#समावेश <linux/dvb/ca.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>

#समावेश <media/dvbdev.h>

#समावेश "firedtv.h"

#घोषणा EN50221_TAG_APP_INFO_ENQUIRY	0x9f8020
#घोषणा EN50221_TAG_CA_INFO_ENQUIRY	0x9f8030
#घोषणा EN50221_TAG_CA_PMT		0x9f8032
#घोषणा EN50221_TAG_ENTER_MENU		0x9f8022

अटल पूर्णांक fdtv_ca_पढ़ोy(काष्ठा firedtv_tuner_status *stat)
अणु
	वापस stat->ca_initialization_status	== 1 &&
	       stat->ca_error_flag		== 0 &&
	       stat->ca_dvb_flag		== 1 &&
	       stat->ca_module_present_status	== 1;
पूर्ण

अटल पूर्णांक fdtv_get_ca_flags(काष्ठा firedtv_tuner_status *stat)
अणु
	पूर्णांक flags = 0;

	अगर (stat->ca_module_present_status == 1)
		flags |= CA_CI_MODULE_PRESENT;
	अगर (stat->ca_initialization_status == 1 &&
	    stat->ca_error_flag            == 0 &&
	    stat->ca_dvb_flag              == 1)
		flags |= CA_CI_MODULE_READY;
	वापस flags;
पूर्ण

अटल पूर्णांक fdtv_ca_get_caps(व्योम *arg)
अणु
	काष्ठा ca_caps *cap = arg;

	cap->slot_num = 1;
	cap->slot_type = CA_CI;
	cap->descr_num = 1;
	cap->descr_type = CA_ECD;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_ca_get_slot_info(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा firedtv_tuner_status stat;
	काष्ठा ca_slot_info *slot = arg;
	पूर्णांक err;

	err = avc_tuner_status(fdtv, &stat);
	अगर (err)
		वापस err;

	अगर (slot->num != 0)
		वापस -EACCES;

	slot->type = CA_CI;
	slot->flags = fdtv_get_ca_flags(&stat);
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_ca_app_info(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा ca_msg *reply = arg;

	वापस avc_ca_app_info(fdtv, reply->msg, &reply->length);
पूर्ण

अटल पूर्णांक fdtv_ca_info(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा ca_msg *reply = arg;

	वापस avc_ca_info(fdtv, reply->msg, &reply->length);
पूर्ण

अटल पूर्णांक fdtv_ca_get_mmi(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा ca_msg *reply = arg;

	वापस avc_ca_get_mmi(fdtv, reply->msg, &reply->length);
पूर्ण

अटल पूर्णांक fdtv_ca_get_msg(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा firedtv_tuner_status stat;
	पूर्णांक err;

	चयन (fdtv->ca_last_command) अणु
	हाल EN50221_TAG_APP_INFO_ENQUIRY:
		err = fdtv_ca_app_info(fdtv, arg);
		अवरोध;
	हाल EN50221_TAG_CA_INFO_ENQUIRY:
		err = fdtv_ca_info(fdtv, arg);
		अवरोध;
	शेष:
		err = avc_tuner_status(fdtv, &stat);
		अगर (err)
			अवरोध;
		अगर (stat.ca_mmi == 1)
			err = fdtv_ca_get_mmi(fdtv, arg);
		अन्यथा अणु
			dev_info(fdtv->device, "unhandled CA message 0x%08x\n",
				 fdtv->ca_last_command);
			err = -EACCES;
		पूर्ण
	पूर्ण
	fdtv->ca_last_command = 0;
	वापस err;
पूर्ण

अटल पूर्णांक fdtv_ca_pmt(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा ca_msg *msg = arg;
	पूर्णांक data_pos;
	पूर्णांक data_length;
	पूर्णांक i;

	data_pos = 4;
	अगर (msg->msg[3] & 0x80) अणु
		data_length = 0;
		क्रम (i = 0; i < (msg->msg[3] & 0x7f); i++)
			data_length = (data_length << 8) + msg->msg[data_pos++];
	पूर्ण अन्यथा अणु
		data_length = msg->msg[3];
	पूर्ण

	वापस avc_ca_pmt(fdtv, &msg->msg[data_pos], data_length);
पूर्ण

अटल पूर्णांक fdtv_ca_send_msg(काष्ठा firedtv *fdtv, व्योम *arg)
अणु
	काष्ठा ca_msg *msg = arg;
	पूर्णांक err;

	/* Do we need a semaphore क्रम this? */
	fdtv->ca_last_command =
		(msg->msg[0] << 16) + (msg->msg[1] << 8) + msg->msg[2];
	चयन (fdtv->ca_last_command) अणु
	हाल EN50221_TAG_CA_PMT:
		err = fdtv_ca_pmt(fdtv, arg);
		अवरोध;
	हाल EN50221_TAG_APP_INFO_ENQUIRY:
		/* handled in ca_get_msg */
		err = 0;
		अवरोध;
	हाल EN50221_TAG_CA_INFO_ENQUIRY:
		/* handled in ca_get_msg */
		err = 0;
		अवरोध;
	हाल EN50221_TAG_ENTER_MENU:
		err = avc_ca_enter_menu(fdtv);
		अवरोध;
	शेष:
		dev_err(fdtv->device, "unhandled CA message 0x%08x\n",
			fdtv->ca_last_command);
		err = -EACCES;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fdtv_ca_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा firedtv *fdtv = dvbdev->priv;
	काष्ठा firedtv_tuner_status stat;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल CA_RESET:
		err = avc_ca_reset(fdtv);
		अवरोध;
	हाल CA_GET_CAP:
		err = fdtv_ca_get_caps(arg);
		अवरोध;
	हाल CA_GET_SLOT_INFO:
		err = fdtv_ca_get_slot_info(fdtv, arg);
		अवरोध;
	हाल CA_GET_MSG:
		err = fdtv_ca_get_msg(fdtv, arg);
		अवरोध;
	हाल CA_SEND_MSG:
		err = fdtv_ca_send_msg(fdtv, arg);
		अवरोध;
	शेष:
		dev_info(fdtv->device, "unhandled CA ioctl %u\n", cmd);
		err = -EOPNOTSUPP;
	पूर्ण

	/* FIXME Is this necessary? */
	avc_tuner_status(fdtv, &stat);

	वापस err;
पूर्ण

अटल __poll_t fdtv_ca_io_poll(काष्ठा file *file, poll_table *रुको)
अणु
	वापस EPOLLIN;
पूर्ण

अटल स्थिर काष्ठा file_operations fdtv_ca_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= dvb_generic_ioctl,
	.खोलो		= dvb_generic_खोलो,
	.release	= dvb_generic_release,
	.poll		= fdtv_ca_io_poll,
	.llseek		= noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा dvb_device fdtv_ca = अणु
	.users		= 1,
	.पढ़ोers	= 1,
	.ग_लिखोrs	= 1,
	.fops		= &fdtv_ca_fops,
	.kernel_ioctl	= fdtv_ca_ioctl,
पूर्ण;

पूर्णांक fdtv_ca_रेजिस्टर(काष्ठा firedtv *fdtv)
अणु
	काष्ठा firedtv_tuner_status stat;
	पूर्णांक err;

	अगर (avc_tuner_status(fdtv, &stat))
		वापस -EINVAL;

	अगर (!fdtv_ca_पढ़ोy(&stat))
		वापस -EFAULT;

	err = dvb_रेजिस्टर_device(&fdtv->adapter, &fdtv->cadev,
				  &fdtv_ca, fdtv, DVB_DEVICE_CA, 0);

	अगर (stat.ca_application_info == 0)
		dev_err(fdtv->device, "CaApplicationInfo is not set\n");
	अगर (stat.ca_date_समय_request == 1)
		avc_ca_get_समय_date(fdtv, &fdtv->ca_समय_पूर्णांकerval);

	वापस err;
पूर्ण

व्योम fdtv_ca_release(काष्ठा firedtv *fdtv)
अणु
	dvb_unरेजिस्टर_device(fdtv->cadev);
पूर्ण
