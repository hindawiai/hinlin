<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 */
#समावेश "priv.h"

अटल पूर्णांक
acpi_पढ़ो_bios(acpi_handle rom_handle, u8 *bios, u32 offset, u32 length)
अणु
#अगर defined(CONFIG_ACPI) && defined(CONFIG_X86)
	acpi_status status;
	जोड़ acpi_object rom_arg_elements[2], *obj;
	काष्ठा acpi_object_list rom_arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्यपूर्ण;

	rom_arg.count = 2;
	rom_arg.poपूर्णांकer = &rom_arg_elements[0];

	rom_arg_elements[0].type = ACPI_TYPE_INTEGER;
	rom_arg_elements[0].पूर्णांकeger.value = offset;

	rom_arg_elements[1].type = ACPI_TYPE_INTEGER;
	rom_arg_elements[1].पूर्णांकeger.value = length;

	status = acpi_evaluate_object(rom_handle, शून्य, &rom_arg, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		pr_info("failed to evaluate ROM got %s\n",
			acpi_क्रमmat_exception(status));
		वापस -ENODEV;
	पूर्ण
	obj = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	length = min(length, obj->buffer.length);
	स_नकल(bios+offset, obj->buffer.poपूर्णांकer, length);
	kमुक्त(buffer.poपूर्णांकer);
	वापस length;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

/* This version of the shaकरोw function disobeys the ACPI spec and tries
 * to fetch in units of more than 4KiB at a समय.  This is a LOT faster
 * on some प्रणालीs, such as Lenovo W530.
 */
अटल u32
acpi_पढ़ो_fast(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	u32 limit = (offset + length + 0xfff) & ~0xfff;
	u32 start = offset & ~0x00000fff;
	u32 fetch = limit - start;

	अगर (nvbios_extend(bios, limit) >= 0) अणु
		पूर्णांक ret = acpi_पढ़ो_bios(data, bios->data, start, fetch);
		अगर (ret == fetch)
			वापस fetch;
	पूर्ण

	वापस 0;
पूर्ण

/* Other प्रणालीs, such as the one in fकरो#55948, will report a success
 * but only वापस 4KiB of data.  The common bios fetching logic will
 * detect an invalid image, and fall back to this version of the पढ़ो
 * function.
 */
अटल u32
acpi_पढ़ो_slow(व्योम *data, u32 offset, u32 length, काष्ठा nvkm_bios *bios)
अणु
	u32 limit = (offset + length + 0xfff) & ~0xfff;
	u32 start = offset & ~0xfff;
	u32 fetch = 0;

	अगर (nvbios_extend(bios, limit) >= 0) अणु
		जबतक (start + fetch < limit) अणु
			पूर्णांक ret = acpi_पढ़ो_bios(data, bios->data,
						 start + fetch, 0x1000);
			अगर (ret != 0x1000)
				अवरोध;
			fetch += 0x1000;
		पूर्ण
	पूर्ण

	वापस fetch;
पूर्ण

अटल व्योम *
acpi_init(काष्ठा nvkm_bios *bios, स्थिर अक्षर *name)
अणु
#अगर defined(CONFIG_ACPI) && defined(CONFIG_X86)
	acpi_status status;
	acpi_handle dhandle, rom_handle;

	dhandle = ACPI_HANDLE(bios->subdev.device->dev);
	अगर (!dhandle)
		वापस ERR_PTR(-ENODEV);

	status = acpi_get_handle(dhandle, "_ROM", &rom_handle);
	अगर (ACPI_FAILURE(status))
		वापस ERR_PTR(-ENODEV);

	वापस rom_handle;
#अन्यथा
	वापस ERR_PTR(-ENODEV);
#पूर्ण_अगर
पूर्ण

स्थिर काष्ठा nvbios_source
nvbios_acpi_fast = अणु
	.name = "ACPI",
	.init = acpi_init,
	.पढ़ो = acpi_पढ़ो_fast,
	.rw = false,
	.require_checksum = true,
पूर्ण;

स्थिर काष्ठा nvbios_source
nvbios_acpi_slow = अणु
	.name = "ACPI",
	.init = acpi_init,
	.पढ़ो = acpi_पढ़ो_slow,
	.rw = false,
पूर्ण;
