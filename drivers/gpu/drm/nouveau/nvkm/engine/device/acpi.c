<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
#समावेश "acpi.h"

#समावेश <core/device.h>

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक
nvkm_acpi_ntfy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा nvkm_device *device =
		container_of(nb, typeof(*device), acpi.nb);
	काष्ठा acpi_bus_event *info = data;

	अगर (!म_भेद(info->device_class, "ac_adapter"))
		nvkm_event_send(&device->event, 1, 0, शून्य, 0);

	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

व्योम
nvkm_acpi_fini(काष्ठा nvkm_device *device)
अणु
#अगर_घोषित CONFIG_ACPI
	unरेजिस्टर_acpi_notअगरier(&device->acpi.nb);
#पूर्ण_अगर
पूर्ण

व्योम
nvkm_acpi_init(काष्ठा nvkm_device *device)
अणु
#अगर_घोषित CONFIG_ACPI
	device->acpi.nb.notअगरier_call = nvkm_acpi_ntfy;
	रेजिस्टर_acpi_notअगरier(&device->acpi.nb);
#पूर्ण_अगर
पूर्ण
