<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "mxms.h"

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/mxm.h>
#समावेश <subdev/i2c.h>

अटल bool
mxm_shaकरोw_rom_fetch(काष्ठा nvkm_i2c_bus *bus, u8 addr,
		     u8 offset, u8 size, u8 *data)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु .addr = addr, .flags = 0, .len = 1, .buf = &offset पूर्ण,
		अणु .addr = addr, .flags = I2C_M_RD, .len = size, .buf = data, पूर्ण,
	पूर्ण;

	वापस i2c_transfer(&bus->i2c, msgs, 2) == 2;
पूर्ण

अटल bool
mxm_shaकरोw_rom(काष्ठा nvkm_mxm *mxm, u8 version)
अणु
	काष्ठा nvkm_device *device = mxm->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_i2c *i2c = device->i2c;
	काष्ठा nvkm_i2c_bus *bus = शून्य;
	u8 i2cidx, mxms[6], addr, size;

	i2cidx = mxm_ddc_map(bios, 1 /* LVDS_DDC */) & 0x0f;
	अगर (i2cidx < 0x0f)
		bus = nvkm_i2c_bus_find(i2c, i2cidx);
	अगर (!bus)
		वापस false;

	addr = 0x54;
	अगर (!mxm_shaकरोw_rom_fetch(bus, addr, 0, 6, mxms)) अणु
		addr = 0x56;
		अगर (!mxm_shaकरोw_rom_fetch(bus, addr, 0, 6, mxms))
			वापस false;
	पूर्ण

	mxm->mxms = mxms;
	size = mxms_headerlen(mxm) + mxms_काष्ठाlen(mxm);
	mxm->mxms = kदो_स्मृति(size, GFP_KERNEL);

	अगर (mxm->mxms &&
	    mxm_shaकरोw_rom_fetch(bus, addr, 0, size, mxm->mxms))
		वापस true;

	kमुक्त(mxm->mxms);
	mxm->mxms = शून्य;
	वापस false;
पूर्ण

#अगर defined(CONFIG_ACPI)
अटल bool
mxm_shaकरोw_dsm(काष्ठा nvkm_mxm *mxm, u8 version)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अटल guid_t muid =
		GUID_INIT(0x4004A400, 0x917D, 0x4CF2,
			  0xB8, 0x9C, 0x79, 0xB6, 0x2F, 0xD5, 0x56, 0x65);
	u32 mxms_args[] = अणु 0x00000000 पूर्ण;
	जोड़ acpi_object argv4 = अणु
		.buffer.type = ACPI_TYPE_BUFFER,
		.buffer.length = माप(mxms_args),
		.buffer.poपूर्णांकer = (अक्षर *)mxms_args,
	पूर्ण;
	जोड़ acpi_object *obj;
	acpi_handle handle;
	पूर्णांक rev;

	handle = ACPI_HANDLE(device->dev);
	अगर (!handle)
		वापस false;

	/*
	 * spec says this can be zero to mean "highest revision", but
	 * of course there's at least one bios out there which fails
	 * unless you pass in exactly the version it supports..
	 */
	rev = (version & 0xf0) << 4 | (version & 0x0f);
	obj = acpi_evaluate_dsm(handle, &muid, rev, 0x00000010, &argv4);
	अगर (!obj) अणु
		nvkm_debug(subdev, "DSM MXMS failed\n");
		वापस false;
	पूर्ण

	अगर (obj->type == ACPI_TYPE_BUFFER) अणु
		mxm->mxms = kmemdup(obj->buffer.poपूर्णांकer,
					 obj->buffer.length, GFP_KERNEL);
	पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_INTEGER) अणु
		nvkm_debug(subdev, "DSM MXMS returned 0x%llx\n",
			   obj->पूर्णांकeger.value);
	पूर्ण

	ACPI_FREE(obj);
	वापस mxm->mxms != शून्य;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODULE)

#घोषणा WMI_WMMX_GUID "F6CB5C3C-9CAE-4EBD-B577-931EA32A2CC0"

अटल u8
wmi_wmmx_mxmi(काष्ठा nvkm_mxm *mxm, u8 version)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	u32 mxmi_args[] = अणु 0x494D584D /* MXMI */, version, 0 पूर्ण;
	काष्ठा acpi_buffer args = अणु माप(mxmi_args), mxmi_args पूर्ण;
	काष्ठा acpi_buffer retn = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_evaluate_method(WMI_WMMX_GUID, 0, 0, &args, &retn);
	अगर (ACPI_FAILURE(status)) अणु
		nvkm_debug(subdev, "WMMX MXMI returned %d\n", status);
		वापस 0x00;
	पूर्ण

	obj = retn.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_INTEGER) अणु
		version = obj->पूर्णांकeger.value;
		nvkm_debug(subdev, "WMMX MXMI version %d.%d\n",
			   (version >> 4), version & 0x0f);
	पूर्ण अन्यथा अणु
		version = 0;
		nvkm_debug(subdev, "WMMX MXMI returned non-integer\n");
	पूर्ण

	kमुक्त(obj);
	वापस version;
पूर्ण

अटल bool
mxm_shaकरोw_wmi(काष्ठा nvkm_mxm *mxm, u8 version)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	u32 mxms_args[] = अणु 0x534D584D /* MXMS */, version, 0 पूर्ण;
	काष्ठा acpi_buffer args = अणु माप(mxms_args), mxms_args पूर्ण;
	काष्ठा acpi_buffer retn = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	अगर (!wmi_has_guid(WMI_WMMX_GUID)) अणु
		nvkm_debug(subdev, "WMMX GUID not found\n");
		वापस false;
	पूर्ण

	mxms_args[1] = wmi_wmmx_mxmi(mxm, 0x00);
	अगर (!mxms_args[1])
		mxms_args[1] = wmi_wmmx_mxmi(mxm, version);
	अगर (!mxms_args[1])
		वापस false;

	status = wmi_evaluate_method(WMI_WMMX_GUID, 0, 0, &args, &retn);
	अगर (ACPI_FAILURE(status)) अणु
		nvkm_debug(subdev, "WMMX MXMS returned %d\n", status);
		वापस false;
	पूर्ण

	obj = retn.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_BUFFER) अणु
		mxm->mxms = kmemdup(obj->buffer.poपूर्णांकer,
				    obj->buffer.length, GFP_KERNEL);
	पूर्ण

	kमुक्त(obj);
	वापस mxm->mxms != शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा mxm_shaकरोw_h अणु
	स्थिर अक्षर *name;
	bool (*exec)(काष्ठा nvkm_mxm *, u8 version);
पूर्ण _mxm_shaकरोw[] = अणु
	अणु "ROM", mxm_shaकरोw_rom पूर्ण,
#अगर defined(CONFIG_ACPI)
	अणु "DSM", mxm_shaकरोw_dsm पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODULE)
	अणु "WMI", mxm_shaकरोw_wmi पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
mxm_shaकरोw(काष्ठा nvkm_mxm *mxm, u8 version)
अणु
	काष्ठा mxm_shaकरोw_h *shaकरोw = _mxm_shaकरोw;
	करो अणु
		nvkm_debug(&mxm->subdev, "checking %s\n", shaकरोw->name);
		अगर (shaकरोw->exec(mxm, version)) अणु
			अगर (mxms_valid(mxm))
				वापस 0;
			kमुक्त(mxm->mxms);
			mxm->mxms = शून्य;
		पूर्ण
	पूर्ण जबतक ((++shaकरोw)->name);
	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_mxm = अणु
पूर्ण;

पूर्णांक
nvkm_mxm_new_(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_mxm **pmxm)
अणु
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_mxm *mxm;
	u8  ver, len;
	u16 data;

	अगर (!(mxm = *pmxm = kzalloc(माप(*mxm), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_mxm, device, type, inst, &mxm->subdev);

	data = mxm_table(bios, &ver, &len);
	अगर (!data || !(ver = nvbios_rd08(bios, data))) अणु
		nvkm_debug(&mxm->subdev, "no VBIOS data, nothing to do\n");
		वापस 0;
	पूर्ण

	nvkm_info(&mxm->subdev, "BIOS version %d.%d\n", ver >> 4, ver & 0x0f);
	nvkm_debug(&mxm->subdev, "module flags: %02x\n",
		   nvbios_rd08(bios, data + 0x01));
	nvkm_debug(&mxm->subdev, "config flags: %02x\n",
		   nvbios_rd08(bios, data + 0x02));

	अगर (mxm_shaकरोw(mxm, ver)) अणु
		nvkm_warn(&mxm->subdev, "failed to locate valid SIS\n");
#अगर 0
		/* we should, perhaps, fall back to some kind of limited
		 * mode here अगर the x86 vbios hasn't alपढ़ोy करोne the
		 * work क्रम us (so we prevent loading with completely
		 * whacked vbios tables).
		 */
		वापस -EINVAL;
#अन्यथा
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	nvkm_debug(&mxm->subdev, "MXMS Version %d.%d\n",
		   mxms_version(mxm) >> 8, mxms_version(mxm) & 0xff);
	mxms_क्रमeach(mxm, 0, शून्य, शून्य);

	अगर (nvkm_boolopt(device->cfgopt, "NvMXMDCB", true))
		mxm->action |= MXM_SANITISE_DCB;
	वापस 0;
पूर्ण
