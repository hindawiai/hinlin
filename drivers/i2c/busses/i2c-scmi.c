<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMBus driver क्रम ACPI SMBus CMI
 *
 * Copyright (C) 2009 Crane Cai <crane.cai@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>

#घोषणा ACPI_SMBUS_HC_CLASS		"smbus"
#घोषणा ACPI_SMBUS_HC_DEVICE_NAME	"cmi"

/* SMBUS HID definition as supported by Microsoft Winकरोws */
#घोषणा ACPI_SMBUS_MS_HID		"SMB0001"

काष्ठा smbus_methods_t अणु
	अक्षर *mt_info;
	अक्षर *mt_sbr;
	अक्षर *mt_sbw;
पूर्ण;

काष्ठा acpi_smbus_cmi अणु
	acpi_handle handle;
	काष्ठा i2c_adapter adapter;
	u8 cap_info:1;
	u8 cap_पढ़ो:1;
	u8 cap_ग_लिखो:1;
	काष्ठा smbus_methods_t *methods;
पूर्ण;

अटल स्थिर काष्ठा smbus_methods_t smbus_methods = अणु
	.mt_info = "_SBI",
	.mt_sbr  = "_SBR",
	.mt_sbw  = "_SBW",
पूर्ण;

/* Some IBM BIOSes omit the leading underscore */
अटल स्थिर काष्ठा smbus_methods_t ibm_smbus_methods = अणु
	.mt_info = "SBI_",
	.mt_sbr  = "SBR_",
	.mt_sbw  = "SBW_",
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id acpi_smbus_cmi_ids[] = अणु
	अणु"SMBUS01", (kernel_uदीर्घ_t)&smbus_methodsपूर्ण,
	अणुACPI_SMBUS_IBM_HID, (kernel_uदीर्घ_t)&ibm_smbus_methodsपूर्ण,
	अणुACPI_SMBUS_MS_HID, (kernel_uदीर्घ_t)&smbus_methodsपूर्ण,
	अणु"", 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_smbus_cmi_ids);

#घोषणा ACPI_SMBUS_STATUS_OK			0x00
#घोषणा ACPI_SMBUS_STATUS_FAIL			0x07
#घोषणा ACPI_SMBUS_STATUS_DNAK			0x10
#घोषणा ACPI_SMBUS_STATUS_DERR			0x11
#घोषणा ACPI_SMBUS_STATUS_CMD_DENY		0x12
#घोषणा ACPI_SMBUS_STATUS_UNKNOWN		0x13
#घोषणा ACPI_SMBUS_STATUS_ACC_DENY		0x17
#घोषणा ACPI_SMBUS_STATUS_TIMEOUT		0x18
#घोषणा ACPI_SMBUS_STATUS_NOTSUP		0x19
#घोषणा ACPI_SMBUS_STATUS_BUSY			0x1a
#घोषणा ACPI_SMBUS_STATUS_PEC			0x1f

#घोषणा ACPI_SMBUS_PRTCL_WRITE			0x00
#घोषणा ACPI_SMBUS_PRTCL_READ			0x01
#घोषणा ACPI_SMBUS_PRTCL_QUICK			0x02
#घोषणा ACPI_SMBUS_PRTCL_BYTE			0x04
#घोषणा ACPI_SMBUS_PRTCL_BYTE_DATA		0x06
#घोषणा ACPI_SMBUS_PRTCL_WORD_DATA		0x08
#घोषणा ACPI_SMBUS_PRTCL_BLOCK_DATA		0x0a


अटल पूर्णांक
acpi_smbus_cmi_access(काष्ठा i2c_adapter *adap, u16 addr, अचिन्हित लघु flags,
		   अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक size,
		   जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक result = 0;
	काष्ठा acpi_smbus_cmi *smbus_cmi = adap->algo_data;
	अचिन्हित अक्षर protocol;
	acpi_status status = 0;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object mt_params[5];
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	जोड़ acpi_object *pkg;
	अक्षर *method;
	पूर्णांक len = 0;

	dev_dbg(&adap->dev, "access size: %d %s\n", size,
		(पढ़ो_ग_लिखो) ? "READ" : "WRITE");
	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		protocol = ACPI_SMBUS_PRTCL_QUICK;
		command = 0;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].पूर्णांकeger.value = 0;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].पूर्णांकeger.value = 0;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		protocol = ACPI_SMBUS_PRTCL_BYTE;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].पूर्णांकeger.value = 0;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].पूर्णांकeger.value = 0;
		पूर्ण अन्यथा अणु
			command = 0;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		protocol = ACPI_SMBUS_PRTCL_BYTE_DATA;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].पूर्णांकeger.value = 1;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].पूर्णांकeger.value = data->byte;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		protocol = ACPI_SMBUS_PRTCL_WORD_DATA;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].पूर्णांकeger.value = 2;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].पूर्णांकeger.value = data->word;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		protocol = ACPI_SMBUS_PRTCL_BLOCK_DATA;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
				वापस -EINVAL;
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].पूर्णांकeger.value = len;
			mt_params[4].type = ACPI_TYPE_BUFFER;
			mt_params[4].buffer.length = len;
			mt_params[4].buffer.poपूर्णांकer = data->block + 1;
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
		protocol |= ACPI_SMBUS_PRTCL_READ;
		method = smbus_cmi->methods->mt_sbr;
		input.count = 3;
	पूर्ण अन्यथा अणु
		protocol |= ACPI_SMBUS_PRTCL_WRITE;
		method = smbus_cmi->methods->mt_sbw;
		input.count = 5;
	पूर्ण

	input.poपूर्णांकer = mt_params;
	mt_params[0].type = ACPI_TYPE_INTEGER;
	mt_params[0].पूर्णांकeger.value = protocol;
	mt_params[1].type = ACPI_TYPE_INTEGER;
	mt_params[1].पूर्णांकeger.value = addr;
	mt_params[2].type = ACPI_TYPE_INTEGER;
	mt_params[2].पूर्णांकeger.value = command;

	status = acpi_evaluate_object(smbus_cmi->handle, method, &input,
				      &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(smbus_cmi->handle,
				"Failed to evaluate %s: %i\n", method, status);
		वापस -EIO;
	पूर्ण

	pkg = buffer.poपूर्णांकer;
	अगर (pkg && pkg->type == ACPI_TYPE_PACKAGE)
		obj = pkg->package.elements;
	अन्यथा अणु
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		जाओ out;
	पूर्ण
	अगर (obj == शून्य || obj->type != ACPI_TYPE_INTEGER) अणु
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		जाओ out;
	पूर्ण

	result = obj->पूर्णांकeger.value;
	acpi_handle_debug(smbus_cmi->handle,  "%s return status: %i\n", method,
			  result);

	चयन (result) अणु
	हाल ACPI_SMBUS_STATUS_OK:
		result = 0;
		अवरोध;
	हाल ACPI_SMBUS_STATUS_BUSY:
		result = -EBUSY;
		जाओ out;
	हाल ACPI_SMBUS_STATUS_TIMEOUT:
		result = -ETIMEDOUT;
		जाओ out;
	हाल ACPI_SMBUS_STATUS_DNAK:
		result = -ENXIO;
		जाओ out;
	शेष:
		result = -EIO;
		जाओ out;
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE || size == I2C_SMBUS_QUICK)
		जाओ out;

	obj = pkg->package.elements + 1;
	अगर (obj->type != ACPI_TYPE_INTEGER) अणु
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		जाओ out;
	पूर्ण

	len = obj->पूर्णांकeger.value;
	obj = pkg->package.elements + 2;
	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
	हाल I2C_SMBUS_WORD_DATA:
		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_err(smbus_cmi->handle,
					"Invalid argument type\n");
			result = -EIO;
			जाओ out;
		पूर्ण
		अगर (len == 2)
			data->word = obj->पूर्णांकeger.value;
		अन्यथा
			data->byte = obj->पूर्णांकeger.value;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (obj->type != ACPI_TYPE_BUFFER) अणु
			acpi_handle_err(smbus_cmi->handle,
					"Invalid argument type\n");
			result = -EIO;
			जाओ out;
		पूर्ण
		अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
			वापस -EPROTO;
		data->block[0] = len;
		स_नकल(data->block + 1, obj->buffer.poपूर्णांकer, len);
		अवरोध;
	पूर्ण

out:
	kमुक्त(buffer.poपूर्णांकer);
	dev_dbg(&adap->dev, "Transaction status: %i\n", result);
	वापस result;
पूर्ण

अटल u32 acpi_smbus_cmi_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा acpi_smbus_cmi *smbus_cmi = adapter->algo_data;
	u32 ret;

	ret = smbus_cmi->cap_पढ़ो | smbus_cmi->cap_ग_लिखो ?
		I2C_FUNC_SMBUS_QUICK : 0;

	ret |= smbus_cmi->cap_पढ़ो ?
		(I2C_FUNC_SMBUS_READ_BYTE |
		I2C_FUNC_SMBUS_READ_BYTE_DATA |
		I2C_FUNC_SMBUS_READ_WORD_DATA |
		I2C_FUNC_SMBUS_READ_BLOCK_DATA) : 0;

	ret |= smbus_cmi->cap_ग_लिखो ?
		(I2C_FUNC_SMBUS_WRITE_BYTE |
		I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
		I2C_FUNC_SMBUS_WRITE_WORD_DATA |
		I2C_FUNC_SMBUS_WRITE_BLOCK_DATA) : 0;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm acpi_smbus_cmi_algorithm = अणु
	.smbus_xfer = acpi_smbus_cmi_access,
	.functionality = acpi_smbus_cmi_func,
पूर्ण;


अटल पूर्णांक acpi_smbus_cmi_add_cap(काष्ठा acpi_smbus_cmi *smbus_cmi,
				  स्थिर अक्षर *name)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_handle *handle = smbus_cmi->handle;
	जोड़ acpi_object *obj;
	acpi_status status;

	अगर (!म_भेद(name, smbus_cmi->methods->mt_info)) अणु
		status = acpi_evaluate_object(smbus_cmi->handle,
					smbus_cmi->methods->mt_info,
					शून्य, &buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_err(handle, "Failed to evaluate %s: %i\n",
					smbus_cmi->methods->mt_info, status);
			वापस -EIO;
		पूर्ण

		obj = buffer.poपूर्णांकer;
		अगर (obj && obj->type == ACPI_TYPE_PACKAGE)
			obj = obj->package.elements;
		अन्यथा अणु
			acpi_handle_err(handle, "Invalid argument type\n");
			kमुक्त(buffer.poपूर्णांकer);
			वापस -EIO;
		पूर्ण

		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_err(handle, "Invalid argument type\n");
			kमुक्त(buffer.poपूर्णांकer);
			वापस -EIO;
		पूर्ण अन्यथा
			acpi_handle_debug(handle, "SMBus CMI Version %x\n",
					  (पूर्णांक)obj->पूर्णांकeger.value);

		kमुक्त(buffer.poपूर्णांकer);
		smbus_cmi->cap_info = 1;
	पूर्ण अन्यथा अगर (!म_भेद(name, smbus_cmi->methods->mt_sbr))
		smbus_cmi->cap_पढ़ो = 1;
	अन्यथा अगर (!म_भेद(name, smbus_cmi->methods->mt_sbw))
		smbus_cmi->cap_ग_लिखो = 1;
	अन्यथा
		acpi_handle_debug(handle, "Unsupported CMI method: %s\n", name);

	वापस 0;
पूर्ण

अटल acpi_status acpi_smbus_cmi_query_methods(acpi_handle handle, u32 level,
			व्योम *context, व्योम **वापस_value)
अणु
	अक्षर node_name[5];
	काष्ठा acpi_buffer buffer = अणु माप(node_name), node_name पूर्ण;
	काष्ठा acpi_smbus_cmi *smbus_cmi = context;
	acpi_status status;

	status = acpi_get_name(handle, ACPI_SINGLE_NAME, &buffer);

	अगर (ACPI_SUCCESS(status))
		acpi_smbus_cmi_add_cap(smbus_cmi, node_name);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक acpi_smbus_cmi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_smbus_cmi *smbus_cmi;
	स्थिर काष्ठा acpi_device_id *id;
	पूर्णांक ret;

	smbus_cmi = kzalloc(माप(काष्ठा acpi_smbus_cmi), GFP_KERNEL);
	अगर (!smbus_cmi)
		वापस -ENOMEM;

	smbus_cmi->handle = device->handle;
	म_नकल(acpi_device_name(device), ACPI_SMBUS_HC_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_SMBUS_HC_CLASS);
	device->driver_data = smbus_cmi;
	smbus_cmi->cap_info = 0;
	smbus_cmi->cap_पढ़ो = 0;
	smbus_cmi->cap_ग_लिखो = 0;

	क्रम (id = acpi_smbus_cmi_ids; id->id[0]; id++)
		अगर (!म_भेद(id->id, acpi_device_hid(device)))
			smbus_cmi->methods =
				(काष्ठा smbus_methods_t *) id->driver_data;

	acpi_walk_namespace(ACPI_TYPE_METHOD, smbus_cmi->handle, 1,
			    acpi_smbus_cmi_query_methods, शून्य, smbus_cmi, शून्य);

	अगर (smbus_cmi->cap_info == 0) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	snम_लिखो(smbus_cmi->adapter.name, माप(smbus_cmi->adapter.name),
		"SMBus CMI adapter %s",
		acpi_device_name(device));
	smbus_cmi->adapter.owner = THIS_MODULE;
	smbus_cmi->adapter.algo = &acpi_smbus_cmi_algorithm;
	smbus_cmi->adapter.algo_data = smbus_cmi;
	smbus_cmi->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	smbus_cmi->adapter.dev.parent = &device->dev;

	ret = i2c_add_adapter(&smbus_cmi->adapter);
	अगर (ret) अणु
		dev_err(&device->dev, "Couldn't register adapter!\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	kमुक्त(smbus_cmi);
	device->driver_data = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_smbus_cmi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_smbus_cmi *smbus_cmi = acpi_driver_data(device);

	i2c_del_adapter(&smbus_cmi->adapter);
	kमुक्त(smbus_cmi);
	device->driver_data = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver acpi_smbus_cmi_driver = अणु
	.name = ACPI_SMBUS_HC_DEVICE_NAME,
	.class = ACPI_SMBUS_HC_CLASS,
	.ids = acpi_smbus_cmi_ids,
	.ops = अणु
		.add = acpi_smbus_cmi_add,
		.हटाओ = acpi_smbus_cmi_हटाओ,
	पूर्ण,
पूर्ण;
module_acpi_driver(acpi_smbus_cmi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Crane Cai <crane.cai@amd.com>");
MODULE_DESCRIPTION("ACPI SMBus CMI driver");
