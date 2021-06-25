<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * coreboot_table.h
 *
 * Internal header क्रम coreboot table access.
 *
 * Copyright 2014 Gerd Hoffmann <kraxel@redhat.com>
 * Copyright 2017 Google Inc.
 * Copyright 2017 Samuel Holland <samuel@sholland.org>
 */

#अगर_अघोषित __COREBOOT_TABLE_H
#घोषणा __COREBOOT_TABLE_H

#समावेश <linux/device.h>

/* Coreboot table header काष्ठाure */
काष्ठा coreboot_table_header अणु
	अक्षर signature[4];
	u32 header_bytes;
	u32 header_checksum;
	u32 table_bytes;
	u32 table_checksum;
	u32 table_entries;
पूर्ण;

/* List of coreboot entry काष्ठाures that is used */
/* Generic */
काष्ठा coreboot_table_entry अणु
	u32 tag;
	u32 size;
पूर्ण;

/* Poपूर्णांकs to a CBMEM entry */
काष्ठा lb_cbmem_ref अणु
	u32 tag;
	u32 size;

	u64 cbmem_addr;
पूर्ण;

/* Describes framebuffer setup by coreboot */
काष्ठा lb_framebuffer अणु
	u32 tag;
	u32 size;

	u64 physical_address;
	u32 x_resolution;
	u32 y_resolution;
	u32 bytes_per_line;
	u8  bits_per_pixel;
	u8  red_mask_pos;
	u8  red_mask_size;
	u8  green_mask_pos;
	u8  green_mask_size;
	u8  blue_mask_pos;
	u8  blue_mask_size;
	u8  reserved_mask_pos;
	u8  reserved_mask_size;
पूर्ण;

/* A device, additionally with inक्रमmation from coreboot. */
काष्ठा coreboot_device अणु
	काष्ठा device dev;
	जोड़ अणु
		काष्ठा coreboot_table_entry entry;
		काष्ठा lb_cbmem_ref cbmem_ref;
		काष्ठा lb_framebuffer framebuffer;
	पूर्ण;
पूर्ण;

/* A driver क्रम handling devices described in coreboot tables. */
काष्ठा coreboot_driver अणु
	पूर्णांक (*probe)(काष्ठा coreboot_device *);
	व्योम (*हटाओ)(काष्ठा coreboot_device *);
	काष्ठा device_driver drv;
	u32 tag;
पूर्ण;

/* Register a driver that uses the data from a coreboot table. */
पूर्णांक coreboot_driver_रेजिस्टर(काष्ठा coreboot_driver *driver);

/* Unरेजिस्टर a driver that uses the data from a coreboot table. */
व्योम coreboot_driver_unरेजिस्टर(काष्ठा coreboot_driver *driver);

/* module_coreboot_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_coreboot_driver(__coreboot_driver) \
	module_driver(__coreboot_driver, coreboot_driver_रेजिस्टर, \
			coreboot_driver_unरेजिस्टर)

#पूर्ण_अगर /* __COREBOOT_TABLE_H */
