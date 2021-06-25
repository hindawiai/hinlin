<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// soc-apci.c - support क्रम ACPI क्रमागतeration.
//
// Copyright (c) 2013-15, Intel Corporation.

#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <sound/soc-acpi.h>

काष्ठा snd_soc_acpi_mach *
snd_soc_acpi_find_machine(काष्ठा snd_soc_acpi_mach *machines)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा snd_soc_acpi_mach *mach_alt;

	क्रम (mach = machines; mach->id[0]; mach++) अणु
		अगर (acpi_dev_present(mach->id, शून्य, -1)) अणु
			अगर (mach->machine_quirk) अणु
				mach_alt = mach->machine_quirk(mach);
				अगर (!mach_alt)
					जारी; /* not full match, ignore */
				mach = mach_alt;
			पूर्ण

			वापस mach;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_acpi_find_machine);

अटल acpi_status snd_soc_acpi_find_package(acpi_handle handle, u32 level,
					     व्योम *context, व्योम **ret)
अणु
	काष्ठा acpi_device *adev;
	acpi_status status;
	काष्ठा snd_soc_acpi_package_context *pkg_ctx = context;

	pkg_ctx->data_valid = false;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (adev->status.present && adev->status.functional) अणु
		काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
		जोड़ acpi_object  *myobj = शून्य;

		status = acpi_evaluate_object_typed(handle, pkg_ctx->name,
						शून्य, &buffer,
						ACPI_TYPE_PACKAGE);
		अगर (ACPI_FAILURE(status))
			वापस AE_OK;

		myobj = buffer.poपूर्णांकer;
		अगर (!myobj || myobj->package.count != pkg_ctx->length) अणु
			kमुक्त(buffer.poपूर्णांकer);
			वापस AE_OK;
		पूर्ण

		status = acpi_extract_package(myobj,
					pkg_ctx->क्रमmat, pkg_ctx->state);
		अगर (ACPI_FAILURE(status)) अणु
			kमुक्त(buffer.poपूर्णांकer);
			वापस AE_OK;
		पूर्ण

		kमुक्त(buffer.poपूर्णांकer);
		pkg_ctx->data_valid = true;
		वापस AE_CTRL_TERMINATE;
	पूर्ण

	वापस AE_OK;
पूर्ण

bool snd_soc_acpi_find_package_from_hid(स्थिर u8 hid[ACPI_ID_LEN],
				काष्ठा snd_soc_acpi_package_context *ctx)
अणु
	acpi_status status;

	status = acpi_get_devices(hid, snd_soc_acpi_find_package, ctx, शून्य);

	अगर (ACPI_FAILURE(status) || !ctx->data_valid)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_acpi_find_package_from_hid);

काष्ठा snd_soc_acpi_mach *snd_soc_acpi_codec_list(व्योम *arg)
अणु
	काष्ठा snd_soc_acpi_mach *mach = arg;
	काष्ठा snd_soc_acpi_codecs *codec_list =
		(काष्ठा snd_soc_acpi_codecs *) mach->quirk_data;
	पूर्णांक i;

	अगर (mach->quirk_data == शून्य)
		वापस mach;

	क्रम (i = 0; i < codec_list->num_codecs; i++) अणु
		अगर (!acpi_dev_present(codec_list->codecs[i], शून्य, -1))
			वापस शून्य;
	पूर्ण

	वापस mach;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_acpi_codec_list);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ALSA SoC ACPI module");
