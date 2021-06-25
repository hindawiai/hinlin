<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2012 Intel Corporation
 * Author: Josh Triplett <josh@joshtriplett.org>
 *
 * Based on the bgrt driver:
 * Copyright 2012 Red Hat, Inc <mjg@redhat.com>
 * Author: Matthew Garrett
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/efi-bgrt.h>

काष्ठा acpi_table_bgrt bgrt_tab;
माप_प्रकार bgrt_image_size;

काष्ठा bmp_header अणु
	u16 id;
	u32 size;
पूर्ण __packed;

व्योम __init efi_bgrt_init(काष्ठा acpi_table_header *table)
अणु
	व्योम *image;
	काष्ठा bmp_header bmp_header;
	काष्ठा acpi_table_bgrt *bgrt = &bgrt_tab;

	अगर (acpi_disabled)
		वापस;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	अगर (table->length < माप(bgrt_tab)) अणु
		pr_notice("Ignoring BGRT: invalid length %u (expected %zu)\n",
		       table->length, माप(bgrt_tab));
		वापस;
	पूर्ण
	*bgrt = *(काष्ठा acpi_table_bgrt *)table;
	/*
	 * Only version 1 is defined but some older laptops (seen on Lenovo
	 * Ivy Bridge models) have a correct version 1 BGRT table with the
	 * version set to 0, so we accept version 0 and 1.
	 */
	अगर (bgrt->version > 1) अणु
		pr_notice("Ignoring BGRT: invalid version %u (expected 1)\n",
		       bgrt->version);
		जाओ out;
	पूर्ण
	अगर (bgrt->image_type != 0) अणु
		pr_notice("Ignoring BGRT: invalid image type %u (expected 0)\n",
		       bgrt->image_type);
		जाओ out;
	पूर्ण
	अगर (!bgrt->image_address) अणु
		pr_notice("Ignoring BGRT: null image address\n");
		जाओ out;
	पूर्ण

	अगर (efi_mem_type(bgrt->image_address) != EFI_BOOT_SERVICES_DATA) अणु
		pr_notice("Ignoring BGRT: invalid image address\n");
		जाओ out;
	पूर्ण
	image = early_memremap(bgrt->image_address, माप(bmp_header));
	अगर (!image) अणु
		pr_notice("Ignoring BGRT: failed to map image header memory\n");
		जाओ out;
	पूर्ण

	स_नकल(&bmp_header, image, माप(bmp_header));
	early_memunmap(image, माप(bmp_header));
	अगर (bmp_header.id != 0x4d42) अणु
		pr_notice("Ignoring BGRT: Incorrect BMP magic number 0x%x (expected 0x4d42)\n",
			bmp_header.id);
		जाओ out;
	पूर्ण
	bgrt_image_size = bmp_header.size;
	efi_mem_reserve(bgrt->image_address, bgrt_image_size);

	वापस;
out:
	स_रखो(bgrt, 0, माप(bgrt_tab));
पूर्ण
