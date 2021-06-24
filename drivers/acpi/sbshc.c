<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMBus driver क्रम ACPI Embedded Controller (v0.1)
 *
 * Copyright (c) 2007 Alexey Starikovskiy
 */

#समावेश <linux/acpi.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "sbshc.h"

#घोषणा PREFIX "ACPI: "

#घोषणा ACPI_SMB_HC_CLASS	"smbus_host_ctl"
#घोषणा ACPI_SMB_HC_DEVICE_NAME	"ACPI SMBus HC"

काष्ठा acpi_smb_hc अणु
	काष्ठा acpi_ec *ec;
	काष्ठा mutex lock;
	रुको_queue_head_t रुको;
	u8 offset;
	u8 query_bit;
	smbus_alarm_callback callback;
	व्योम *context;
	bool करोne;
पूर्ण;

अटल पूर्णांक acpi_smbus_hc_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_smbus_hc_हटाओ(काष्ठा acpi_device *device);

अटल स्थिर काष्ठा acpi_device_id sbs_device_ids[] = अणु
	अणु"ACPI0001", 0पूर्ण,
	अणु"ACPI0005", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, sbs_device_ids);

अटल काष्ठा acpi_driver acpi_smb_hc_driver = अणु
	.name = "smbus_hc",
	.class = ACPI_SMB_HC_CLASS,
	.ids = sbs_device_ids,
	.ops = अणु
		.add = acpi_smbus_hc_add,
		.हटाओ = acpi_smbus_hc_हटाओ,
		पूर्ण,
पूर्ण;

जोड़ acpi_smb_status अणु
	u8 raw;
	काष्ठा अणु
		u8 status:5;
		u8 reserved:1;
		u8 alarm:1;
		u8 करोne:1;
	पूर्ण fields;
पूर्ण;

क्रमागत acpi_smb_status_codes अणु
	SMBUS_OK = 0,
	SMBUS_UNKNOWN_FAILURE = 0x07,
	SMBUS_DEVICE_ADDRESS_NACK = 0x10,
	SMBUS_DEVICE_ERROR = 0x11,
	SMBUS_DEVICE_COMMAND_ACCESS_DENIED = 0x12,
	SMBUS_UNKNOWN_ERROR = 0x13,
	SMBUS_DEVICE_ACCESS_DENIED = 0x17,
	SMBUS_TIMEOUT = 0x18,
	SMBUS_HOST_UNSUPPORTED_PROTOCOL = 0x19,
	SMBUS_BUSY = 0x1a,
	SMBUS_PEC_ERROR = 0x1f,
पूर्ण;

क्रमागत acpi_smb_offset अणु
	ACPI_SMB_PROTOCOL = 0,	/* protocol, PEC */
	ACPI_SMB_STATUS = 1,	/* status */
	ACPI_SMB_ADDRESS = 2,	/* address */
	ACPI_SMB_COMMAND = 3,	/* command */
	ACPI_SMB_DATA = 4,	/* 32 data रेजिस्टरs */
	ACPI_SMB_BLOCK_COUNT = 0x24,	/* number of data bytes */
	ACPI_SMB_ALARM_ADDRESS = 0x25,	/* alarm address */
	ACPI_SMB_ALARM_DATA = 0x26,	/* 2 bytes alarm data */
पूर्ण;

अटल अंतरभूत पूर्णांक smb_hc_पढ़ो(काष्ठा acpi_smb_hc *hc, u8 address, u8 *data)
अणु
	वापस ec_पढ़ो(hc->offset + address, data);
पूर्ण

अटल अंतरभूत पूर्णांक smb_hc_ग_लिखो(काष्ठा acpi_smb_hc *hc, u8 address, u8 data)
अणु
	वापस ec_ग_लिखो(hc->offset + address, data);
पूर्ण

अटल पूर्णांक रुको_transaction_complete(काष्ठा acpi_smb_hc *hc, पूर्णांक समयout)
अणु
	अगर (रुको_event_समयout(hc->रुको, hc->करोne, msecs_to_jअगरfies(समयout)))
		वापस 0;
	वापस -ETIME;
पूर्ण

अटल पूर्णांक acpi_smbus_transaction(काष्ठा acpi_smb_hc *hc, u8 protocol,
				  u8 address, u8 command, u8 *data, u8 length)
अणु
	पूर्णांक ret = -EFAULT, i;
	u8 temp, sz = 0;

	अगर (!hc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "host controller is not configured\n");
		वापस ret;
	पूर्ण

	mutex_lock(&hc->lock);
	hc->करोne = false;
	अगर (smb_hc_पढ़ो(hc, ACPI_SMB_PROTOCOL, &temp))
		जाओ end;
	अगर (temp) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण
	smb_hc_ग_लिखो(hc, ACPI_SMB_COMMAND, command);
	अगर (!(protocol & 0x01)) अणु
		smb_hc_ग_लिखो(hc, ACPI_SMB_BLOCK_COUNT, length);
		क्रम (i = 0; i < length; ++i)
			smb_hc_ग_लिखो(hc, ACPI_SMB_DATA + i, data[i]);
	पूर्ण
	smb_hc_ग_लिखो(hc, ACPI_SMB_ADDRESS, address << 1);
	smb_hc_ग_लिखो(hc, ACPI_SMB_PROTOCOL, protocol);
	/*
	 * Wait क्रम completion. Save the status code, data size,
	 * and data पूर्णांकo the वापस package (अगर required by the protocol).
	 */
	ret = रुको_transaction_complete(hc, 1000);
	अगर (ret || !(protocol & 0x01))
		जाओ end;
	चयन (protocol) अणु
	हाल SMBUS_RECEIVE_BYTE:
	हाल SMBUS_READ_BYTE:
		sz = 1;
		अवरोध;
	हाल SMBUS_READ_WORD:
		sz = 2;
		अवरोध;
	हाल SMBUS_READ_BLOCK:
		अगर (smb_hc_पढ़ो(hc, ACPI_SMB_BLOCK_COUNT, &sz)) अणु
			ret = -EFAULT;
			जाओ end;
		पूर्ण
		sz &= 0x1f;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < sz; ++i)
		smb_hc_पढ़ो(hc, ACPI_SMB_DATA + i, &data[i]);
      end:
	mutex_unlock(&hc->lock);
	वापस ret;
पूर्ण

पूर्णांक acpi_smbus_पढ़ो(काष्ठा acpi_smb_hc *hc, u8 protocol, u8 address,
		    u8 command, u8 *data)
अणु
	वापस acpi_smbus_transaction(hc, protocol, address, command, data, 0);
पूर्ण

EXPORT_SYMBOL_GPL(acpi_smbus_पढ़ो);

पूर्णांक acpi_smbus_ग_लिखो(काष्ठा acpi_smb_hc *hc, u8 protocol, u8 address,
		     u8 command, u8 *data, u8 length)
अणु
	वापस acpi_smbus_transaction(hc, protocol, address, command, data, length);
पूर्ण

EXPORT_SYMBOL_GPL(acpi_smbus_ग_लिखो);

पूर्णांक acpi_smbus_रेजिस्टर_callback(काष्ठा acpi_smb_hc *hc,
				 smbus_alarm_callback callback, व्योम *context)
अणु
	mutex_lock(&hc->lock);
	hc->callback = callback;
	hc->context = context;
	mutex_unlock(&hc->lock);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(acpi_smbus_रेजिस्टर_callback);

पूर्णांक acpi_smbus_unरेजिस्टर_callback(काष्ठा acpi_smb_hc *hc)
अणु
	mutex_lock(&hc->lock);
	hc->callback = शून्य;
	hc->context = शून्य;
	mutex_unlock(&hc->lock);
	acpi_os_रुको_events_complete();
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(acpi_smbus_unरेजिस्टर_callback);

अटल अंतरभूत व्योम acpi_smbus_callback(व्योम *context)
अणु
	काष्ठा acpi_smb_hc *hc = context;
	अगर (hc->callback)
		hc->callback(hc->context);
पूर्ण

अटल पूर्णांक smbus_alarm(व्योम *context)
अणु
	काष्ठा acpi_smb_hc *hc = context;
	जोड़ acpi_smb_status status;
	u8 address;
	अगर (smb_hc_पढ़ो(hc, ACPI_SMB_STATUS, &status.raw))
		वापस 0;
	/* Check अगर it is only a completion notअगरy */
	अगर (status.fields.करोne && status.fields.status == SMBUS_OK) अणु
		hc->करोne = true;
		wake_up(&hc->रुको);
	पूर्ण
	अगर (!status.fields.alarm)
		वापस 0;
	mutex_lock(&hc->lock);
	smb_hc_पढ़ो(hc, ACPI_SMB_ALARM_ADDRESS, &address);
	status.fields.alarm = 0;
	smb_hc_ग_लिखो(hc, ACPI_SMB_STATUS, status.raw);
	/* We are only पूर्णांकerested in events coming from known devices */
	चयन (address >> 1) अणु
		हाल ACPI_SBS_CHARGER:
		हाल ACPI_SBS_MANAGER:
		हाल ACPI_SBS_BATTERY:
			acpi_os_execute(OSL_NOTIFY_HANDLER,
					acpi_smbus_callback, hc);
		शेष:;
	पूर्ण
	mutex_unlock(&hc->lock);
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*acpi_ec_query_func) (व्योम *data);

बाह्य पूर्णांक acpi_ec_add_query_handler(काष्ठा acpi_ec *ec, u8 query_bit,
			      acpi_handle handle, acpi_ec_query_func func,
			      व्योम *data);

अटल पूर्णांक acpi_smbus_hc_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ दीर्घ val;
	काष्ठा acpi_smb_hc *hc;

	अगर (!device)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "_EC", शून्य, &val);
	अगर (ACPI_FAILURE(status)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "error obtaining _EC.\n");
		वापस -EIO;
	पूर्ण

	म_नकल(acpi_device_name(device), ACPI_SMB_HC_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_SMB_HC_CLASS);

	hc = kzalloc(माप(काष्ठा acpi_smb_hc), GFP_KERNEL);
	अगर (!hc)
		वापस -ENOMEM;
	mutex_init(&hc->lock);
	init_रुकोqueue_head(&hc->रुको);

	hc->ec = acpi_driver_data(device->parent);
	hc->offset = (val >> 8) & 0xff;
	hc->query_bit = val & 0xff;
	device->driver_data = hc;

	acpi_ec_add_query_handler(hc->ec, hc->query_bit, शून्य, smbus_alarm, hc);
	dev_info(&device->dev, "SBS HC: offset = 0x%0x, query_bit = 0x%0x\n",
		 hc->offset, hc->query_bit);

	वापस 0;
पूर्ण

बाह्य व्योम acpi_ec_हटाओ_query_handler(काष्ठा acpi_ec *ec, u8 query_bit);

अटल पूर्णांक acpi_smbus_hc_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_smb_hc *hc;

	अगर (!device)
		वापस -EINVAL;

	hc = acpi_driver_data(device);
	acpi_ec_हटाओ_query_handler(hc->ec, hc->query_bit);
	acpi_os_रुको_events_complete();
	kमुक्त(hc);
	device->driver_data = शून्य;
	वापस 0;
पूर्ण

module_acpi_driver(acpi_smb_hc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Starikovskiy");
MODULE_DESCRIPTION("ACPI SMBus HC driver");
