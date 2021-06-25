<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INT3400 thermal driver
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Zhang Rui <rui.zhang@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश "acpi_thermal_rel.h"

#घोषणा INT3400_THERMAL_TABLE_CHANGED 0x83
#घोषणा INT3400_ODVP_CHANGED 0x88
#घोषणा INT3400_KEEP_ALIVE 0xA0

क्रमागत पूर्णांक3400_thermal_uuid अणु
	INT3400_THERMAL_PASSIVE_1,
	INT3400_THERMAL_ACTIVE,
	INT3400_THERMAL_CRITICAL,
	INT3400_THERMAL_ADAPTIVE_PERFORMANCE,
	INT3400_THERMAL_EMERGENCY_CALL_MODE,
	INT3400_THERMAL_PASSIVE_2,
	INT3400_THERMAL_POWER_BOSS,
	INT3400_THERMAL_VIRTUAL_SENSOR,
	INT3400_THERMAL_COOLING_MODE,
	INT3400_THERMAL_HARDWARE_DUTY_CYCLING,
	INT3400_THERMAL_MAXIMUM_UUID,
पूर्ण;

अटल अक्षर *पूर्णांक3400_thermal_uuids[INT3400_THERMAL_MAXIMUM_UUID] = अणु
	"42A441D6-AE6A-462b-A84B-4A8CE79027D3",
	"3A95C389-E4B8-4629-A526-C52C88626BAE",
	"97C68AE7-15FA-499c-B8C9-5DA81D606E0A",
	"63BE270F-1C11-48FD-A6F7-3AF253FF3E2D",
	"5349962F-71E6-431D-9AE8-0A635B710AEE",
	"9E04115A-AE87-4D1C-9500-0F3E340BFE75",
	"F5A35014-C209-46A4-993A-EB56DE7530A1",
	"6ED722A7-9240-48A5-B479-31EEF723D7CF",
	"16CAF1B7-DD38-40ED-B1C1-1B8A1913D531",
	"BE84BABF-C4D4-403D-B495-3128FD44dAC1",
पूर्ण;

काष्ठा odvp_attr;

काष्ठा पूर्णांक3400_thermal_priv अणु
	काष्ठा acpi_device *adev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा thermal_zone_device *thermal;
	पूर्णांक art_count;
	काष्ठा art *arts;
	पूर्णांक trt_count;
	काष्ठा trt *trts;
	u8 uuid_biपंचांगap;
	पूर्णांक rel_misc_dev_res;
	पूर्णांक current_uuid_index;
	अक्षर *data_vault;
	पूर्णांक odvp_count;
	पूर्णांक *odvp;
	काष्ठा odvp_attr *odvp_attrs;
पूर्ण;

अटल पूर्णांक evaluate_odvp(काष्ठा पूर्णांक3400_thermal_priv *priv);

काष्ठा odvp_attr अणु
	पूर्णांक odvp;
	काष्ठा पूर्णांक3400_thermal_priv *priv;
	काष्ठा kobj_attribute attr;
पूर्ण;

अटल sमाप_प्रकार data_vault_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
	     काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	स_नकल(buf, attr->निजी + off, count);
	वापस count;
पूर्ण

अटल BIN_ATTR_RO(data_vault, 0);

अटल काष्ठा bin_attribute *data_attributes[] = अणु
	&bin_attr_data_vault,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार imok_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = dev_get_drvdata(dev);
	acpi_status status;
	पूर्णांक input, ret;

	ret = kstrtouपूर्णांक(buf, 10, &input);
	अगर (ret)
		वापस ret;
	status = acpi_execute_simple_method(priv->adev->handle, "IMOK", input);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(imok);

अटल काष्ठा attribute *imok_attr[] = अणु
	&dev_attr_imok.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group data_attribute_group = अणु
	.bin_attrs = data_attributes,
	.attrs = imok_attr,
पूर्ण;

अटल sमाप_प्रकार available_uuids_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = dev_get_drvdata(dev);
	पूर्णांक i;
	पूर्णांक length = 0;

	अगर (!priv->uuid_biपंचांगap)
		वापस प्र_लिखो(buf, "UNKNOWN\n");

	क्रम (i = 0; i < INT3400_THERMAL_MAXIMUM_UUID; i++) अणु
		अगर (priv->uuid_biपंचांगap & (1 << i))
			अगर (PAGE_SIZE - length > 0)
				length += scnम_लिखो(&buf[length],
						   PAGE_SIZE - length,
						   "%s\n",
						   पूर्णांक3400_thermal_uuids[i]);
	पूर्ण

	वापस length;
पूर्ण

अटल sमाप_प्रकार current_uuid_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = dev_get_drvdata(dev);

	अगर (priv->current_uuid_index == -1)
		वापस प्र_लिखो(buf, "INVALID\n");

	वापस प्र_लिखो(buf, "%s\n",
		       पूर्णांक3400_thermal_uuids[priv->current_uuid_index]);
पूर्ण

अटल sमाप_प्रकार current_uuid_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < INT3400_THERMAL_MAXIMUM_UUID; ++i) अणु
		अगर (!म_भेदन(buf, पूर्णांक3400_thermal_uuids[i],
			     माप(पूर्णांक3400_thermal_uuids[i]) - 1)) अणु
			/*
			 * If we have a list of supported UUIDs, make sure
			 * this one is supported.
			 */
			अगर (priv->uuid_biपंचांगap &&
			    !(priv->uuid_biपंचांगap & (1 << i)))
				वापस -EINVAL;

			priv->current_uuid_index = i;
			वापस count;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल DEVICE_ATTR_RW(current_uuid);
अटल DEVICE_ATTR_RO(available_uuids);
अटल काष्ठा attribute *uuid_attrs[] = अणु
	&dev_attr_available_uuids.attr,
	&dev_attr_current_uuid.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group uuid_attribute_group = अणु
	.attrs = uuid_attrs,
	.name = "uuids"
पूर्ण;

अटल पूर्णांक पूर्णांक3400_thermal_get_uuids(काष्ठा पूर्णांक3400_thermal_priv *priv)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *obja, *objb;
	पूर्णांक i, j;
	पूर्णांक result = 0;
	acpi_status status;

	status = acpi_evaluate_object(priv->adev->handle, "IDSP", शून्य, &buf);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	obja = (जोड़ acpi_object *)buf.poपूर्णांकer;
	अगर (obja->type != ACPI_TYPE_PACKAGE) अणु
		result = -EINVAL;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < obja->package.count; i++) अणु
		objb = &obja->package.elements[i];
		अगर (objb->type != ACPI_TYPE_BUFFER) अणु
			result = -EINVAL;
			जाओ end;
		पूर्ण

		/* UUID must be 16 bytes */
		अगर (objb->buffer.length != 16) अणु
			result = -EINVAL;
			जाओ end;
		पूर्ण

		क्रम (j = 0; j < INT3400_THERMAL_MAXIMUM_UUID; j++) अणु
			guid_t guid;

			guid_parse(पूर्णांक3400_thermal_uuids[j], &guid);
			अगर (guid_equal((guid_t *)objb->buffer.poपूर्णांकer, &guid)) अणु
				priv->uuid_biपंचांगap |= (1 << j);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

end:
	kमुक्त(buf.poपूर्णांकer);
	वापस result;
पूर्ण

अटल पूर्णांक पूर्णांक3400_thermal_run_osc(acpi_handle handle,
				क्रमागत पूर्णांक3400_thermal_uuid uuid, bool enable)
अणु
	u32 ret, buf[2];
	acpi_status status;
	पूर्णांक result = 0;
	काष्ठा acpi_osc_context context = अणु
		.uuid_str = शून्य,
		.rev = 1,
		.cap.length = 8,
	पूर्ण;

	अगर (uuid < 0 || uuid >= INT3400_THERMAL_MAXIMUM_UUID)
		वापस -EINVAL;

	context.uuid_str = पूर्णांक3400_thermal_uuids[uuid];

	buf[OSC_QUERY_DWORD] = 0;
	buf[OSC_SUPPORT_DWORD] = enable;

	context.cap.poपूर्णांकer = buf;

	status = acpi_run_osc(handle, &context);
	अगर (ACPI_SUCCESS(status)) अणु
		ret = *((u32 *)(context.ret.poपूर्णांकer + 4));
		अगर (ret != enable)
			result = -EPERM;
	पूर्ण अन्यथा
		result = -EPERM;

	kमुक्त(context.ret.poपूर्णांकer);

	वापस result;
पूर्ण

अटल sमाप_प्रकार odvp_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा odvp_attr *odvp_attr;

	odvp_attr = container_of(attr, काष्ठा odvp_attr, attr);

	वापस प्र_लिखो(buf, "%d\n", odvp_attr->priv->odvp[odvp_attr->odvp]);
पूर्ण

अटल व्योम cleanup_odvp(काष्ठा पूर्णांक3400_thermal_priv *priv)
अणु
	पूर्णांक i;

	अगर (priv->odvp_attrs) अणु
		क्रम (i = 0; i < priv->odvp_count; i++) अणु
			sysfs_हटाओ_file(&priv->pdev->dev.kobj,
					  &priv->odvp_attrs[i].attr.attr);
			kमुक्त(priv->odvp_attrs[i].attr.attr.name);
		पूर्ण
		kमुक्त(priv->odvp_attrs);
	पूर्ण
	kमुक्त(priv->odvp);
	priv->odvp_count = 0;
पूर्ण

अटल पूर्णांक evaluate_odvp(काष्ठा पूर्णांक3400_thermal_priv *priv)
अणु
	काष्ठा acpi_buffer odvp = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj = शून्य;
	acpi_status status;
	पूर्णांक i, ret;

	status = acpi_evaluate_object(priv->adev->handle, "ODVP", शून्य, &odvp);
	अगर (ACPI_FAILURE(status)) अणु
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	obj = odvp.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_PACKAGE) अणु
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (priv->odvp == शून्य) अणु
		priv->odvp_count = obj->package.count;
		priv->odvp = kदो_स्मृति_array(priv->odvp_count, माप(पूर्णांक),
				     GFP_KERNEL);
		अगर (!priv->odvp) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (priv->odvp_attrs == शून्य) अणु
		priv->odvp_attrs = kसुस्मृति(priv->odvp_count,
					   माप(काष्ठा odvp_attr),
					   GFP_KERNEL);
		अगर (!priv->odvp_attrs) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
		क्रम (i = 0; i < priv->odvp_count; i++) अणु
			काष्ठा odvp_attr *odvp = &priv->odvp_attrs[i];

			sysfs_attr_init(&odvp->attr.attr);
			odvp->priv = priv;
			odvp->odvp = i;
			odvp->attr.attr.name = kaप्र_लिखो(GFP_KERNEL,
							 "odvp%d", i);

			अगर (!odvp->attr.attr.name) अणु
				ret = -ENOMEM;
				जाओ out_err;
			पूर्ण
			odvp->attr.attr.mode = 0444;
			odvp->attr.show = odvp_show;
			odvp->attr.store = शून्य;
			ret = sysfs_create_file(&priv->pdev->dev.kobj,
						&odvp->attr.attr);
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < obj->package.count; i++) अणु
		अगर (obj->package.elements[i].type == ACPI_TYPE_INTEGER)
			priv->odvp[i] = obj->package.elements[i].पूर्णांकeger.value;
	पूर्ण

	kमुक्त(obj);
	वापस 0;

out_err:
	cleanup_odvp(priv);
	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांक3400_notअगरy(acpi_handle handle,
			u32 event,
			व्योम *data)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = data;
	अक्षर *thermal_prop[5];
	पूर्णांक therm_event;

	अगर (!priv)
		वापस;

	चयन (event) अणु
	हाल INT3400_THERMAL_TABLE_CHANGED:
		therm_event = THERMAL_TABLE_CHANGED;
		अवरोध;
	हाल INT3400_KEEP_ALIVE:
		therm_event = THERMAL_EVENT_KEEP_ALIVE;
		अवरोध;
	हाल INT3400_ODVP_CHANGED:
		evaluate_odvp(priv);
		therm_event = THERMAL_DEVICE_POWER_CAPABILITY_CHANGED;
		अवरोध;
	शेष:
		/* Ignore unknown notअगरication codes sent to INT3400 device */
		वापस;
	पूर्ण

	thermal_prop[0] = kaप्र_लिखो(GFP_KERNEL, "NAME=%s", priv->thermal->type);
	thermal_prop[1] = kaप्र_लिखो(GFP_KERNEL, "TEMP=%d", priv->thermal->temperature);
	thermal_prop[2] = kaप्र_लिखो(GFP_KERNEL, "TRIP=");
	thermal_prop[3] = kaप्र_लिखो(GFP_KERNEL, "EVENT=%d", therm_event);
	thermal_prop[4] = शून्य;
	kobject_uevent_env(&priv->thermal->device.kobj, KOBJ_CHANGE, thermal_prop);
पूर्ण

अटल पूर्णांक पूर्णांक3400_thermal_get_temp(काष्ठा thermal_zone_device *thermal,
			पूर्णांक *temp)
अणु
	*temp = 20 * 1000; /* faked temp sensor with 20C */
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक3400_thermal_change_mode(काष्ठा thermal_zone_device *thermal,
				       क्रमागत thermal_device_mode mode)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = thermal->devdata;
	पूर्णांक result = 0;

	अगर (!priv)
		वापस -EINVAL;

	अगर (mode != thermal->mode)
		result = पूर्णांक3400_thermal_run_osc(priv->adev->handle,
						priv->current_uuid_index,
						mode == THERMAL_DEVICE_ENABLED);


	evaluate_odvp(priv);

	वापस result;
पूर्ण

अटल काष्ठा thermal_zone_device_ops पूर्णांक3400_thermal_ops = अणु
	.get_temp = पूर्णांक3400_thermal_get_temp,
	.change_mode = पूर्णांक3400_thermal_change_mode,
पूर्ण;

अटल काष्ठा thermal_zone_params पूर्णांक3400_thermal_params = अणु
	.governor_name = "user_space",
	.no_hwmon = true,
पूर्ण;

अटल व्योम पूर्णांक3400_setup_gddv(काष्ठा पूर्णांक3400_thermal_priv *priv)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = acpi_evaluate_object(priv->adev->handle, "GDDV", शून्य,
				      &buffer);
	अगर (ACPI_FAILURE(status) || !buffer.length)
		वापस;

	obj = buffer.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_PACKAGE || obj->package.count != 1
	    || obj->package.elements[0].type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस;
	पूर्ण

	priv->data_vault = kmemdup(obj->package.elements[0].buffer.poपूर्णांकer,
				   obj->package.elements[0].buffer.length,
				   GFP_KERNEL);
	bin_attr_data_vault.निजी = priv->data_vault;
	bin_attr_data_vault.size = obj->package.elements[0].buffer.length;
	kमुक्त(buffer.poपूर्णांकer);
पूर्ण

अटल पूर्णांक पूर्णांक3400_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	काष्ठा पूर्णांक3400_thermal_priv *priv;
	पूर्णांक result;

	अगर (!adev)
		वापस -ENODEV;

	priv = kzalloc(माप(काष्ठा पूर्णांक3400_thermal_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdev = pdev;
	priv->adev = adev;

	result = पूर्णांक3400_thermal_get_uuids(priv);

	/* Missing IDSP isn't fatal */
	अगर (result && result != -ENODEV)
		जाओ मुक्त_priv;

	priv->current_uuid_index = -1;

	result = acpi_parse_art(priv->adev->handle, &priv->art_count,
				&priv->arts, true);
	अगर (result)
		dev_dbg(&pdev->dev, "_ART table parsing error\n");

	result = acpi_parse_trt(priv->adev->handle, &priv->trt_count,
				&priv->trts, true);
	अगर (result)
		dev_dbg(&pdev->dev, "_TRT table parsing error\n");

	platक्रमm_set_drvdata(pdev, priv);

	पूर्णांक3400_setup_gddv(priv);

	evaluate_odvp(priv);

	priv->thermal = thermal_zone_device_रेजिस्टर("INT3400 Thermal", 0, 0,
						priv, &पूर्णांक3400_thermal_ops,
						&पूर्णांक3400_thermal_params, 0, 0);
	अगर (IS_ERR(priv->thermal)) अणु
		result = PTR_ERR(priv->thermal);
		जाओ मुक्त_art_trt;
	पूर्ण

	priv->rel_misc_dev_res = acpi_thermal_rel_misc_device_add(
							priv->adev->handle);

	result = sysfs_create_group(&pdev->dev.kobj, &uuid_attribute_group);
	अगर (result)
		जाओ मुक्त_rel_misc;

	अगर (priv->data_vault) अणु
		result = sysfs_create_group(&pdev->dev.kobj,
					    &data_attribute_group);
		अगर (result)
			जाओ मुक्त_uuid;
	पूर्ण

	result = acpi_install_notअगरy_handler(
			priv->adev->handle, ACPI_DEVICE_NOTIFY, पूर्णांक3400_notअगरy,
			(व्योम *)priv);
	अगर (result)
		जाओ मुक्त_sysfs;

	वापस 0;

मुक्त_sysfs:
	cleanup_odvp(priv);
	अगर (priv->data_vault) अणु
		sysfs_हटाओ_group(&pdev->dev.kobj, &data_attribute_group);
		kमुक्त(priv->data_vault);
	पूर्ण
मुक्त_uuid:
	sysfs_हटाओ_group(&pdev->dev.kobj, &uuid_attribute_group);
मुक्त_rel_misc:
	अगर (!priv->rel_misc_dev_res)
		acpi_thermal_rel_misc_device_हटाओ(priv->adev->handle);
	thermal_zone_device_unरेजिस्टर(priv->thermal);
मुक्त_art_trt:
	kमुक्त(priv->trts);
	kमुक्त(priv->arts);
मुक्त_priv:
	kमुक्त(priv);
	वापस result;
पूर्ण

अटल पूर्णांक पूर्णांक3400_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांक3400_thermal_priv *priv = platक्रमm_get_drvdata(pdev);

	acpi_हटाओ_notअगरy_handler(
			priv->adev->handle, ACPI_DEVICE_NOTIFY,
			पूर्णांक3400_notअगरy);

	cleanup_odvp(priv);

	अगर (!priv->rel_misc_dev_res)
		acpi_thermal_rel_misc_device_हटाओ(priv->adev->handle);

	अगर (priv->data_vault)
		sysfs_हटाओ_group(&pdev->dev.kobj, &data_attribute_group);
	sysfs_हटाओ_group(&pdev->dev.kobj, &uuid_attribute_group);
	thermal_zone_device_unरेजिस्टर(priv->thermal);
	kमुक्त(priv->data_vault);
	kमुक्त(priv->trts);
	kमुक्त(priv->arts);
	kमुक्त(priv);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3400_thermal_match[] = अणु
	अणु"INT3400", 0पूर्ण,
	अणु"INTC1040", 0पूर्ण,
	अणु"INTC1041", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, पूर्णांक3400_thermal_match);

अटल काष्ठा platक्रमm_driver पूर्णांक3400_thermal_driver = अणु
	.probe = पूर्णांक3400_thermal_probe,
	.हटाओ = पूर्णांक3400_thermal_हटाओ,
	.driver = अणु
		   .name = "int3400 thermal",
		   .acpi_match_table = ACPI_PTR(पूर्णांक3400_thermal_match),
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांक3400_thermal_driver);

MODULE_DESCRIPTION("INT3400 Thermal driver");
MODULE_AUTHOR("Zhang Rui <rui.zhang@intel.com>");
MODULE_LICENSE("GPL");
