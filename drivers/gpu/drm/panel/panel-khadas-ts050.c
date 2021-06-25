<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा khadas_ts050_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *enable_gpio;

	bool prepared;
	bool enabled;
पूर्ण;

काष्ठा khadas_ts050_panel_cmd अणु
	u8 cmd;
	u8 data;
पूर्ण;

/* Only the CMD1 User Command set is करोcumented */
अटल स्थिर काष्ठा khadas_ts050_panel_cmd init_code[] = अणु
	/* Select Unknown CMD Page (Unकरोcumented) */
	अणु0xff, 0xeeपूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	अणु0x1f, 0x45पूर्ण,
	अणु0x24, 0x4fपूर्ण,
	अणु0x38, 0xc8पूर्ण,
	अणु0x39, 0x27पूर्ण,
	अणु0x1e, 0x77पूर्ण,
	अणु0x1d, 0x0fपूर्ण,
	अणु0x7e, 0x71पूर्ण,
	अणु0x7c, 0x03पूर्ण,
	अणु0xff, 0x00पूर्ण,
	अणु0xfb, 0x01पूर्ण,
	अणु0x35, 0x01पूर्ण,
	/* Select CMD2 Page0 (Unकरोcumented) */
	अणु0xff, 0x01पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	अणु0x00, 0x01पूर्ण,
	अणु0x01, 0x55पूर्ण,
	अणु0x02, 0x40पूर्ण,
	अणु0x05, 0x40पूर्ण,
	अणु0x06, 0x4aपूर्ण,
	अणु0x07, 0x24पूर्ण,
	अणु0x08, 0x0cपूर्ण,
	अणु0x0b, 0x7dपूर्ण,
	अणु0x0c, 0x7dपूर्ण,
	अणु0x0e, 0xb0पूर्ण,
	अणु0x0f, 0xaeपूर्ण,
	अणु0x11, 0x10पूर्ण,
	अणु0x12, 0x10पूर्ण,
	अणु0x13, 0x03पूर्ण,
	अणु0x14, 0x4aपूर्ण,
	अणु0x15, 0x12पूर्ण,
	अणु0x16, 0x12पूर्ण,
	अणु0x18, 0x00पूर्ण,
	अणु0x19, 0x77पूर्ण,
	अणु0x1a, 0x55पूर्ण,
	अणु0x1b, 0x13पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x00पूर्ण,
	अणु0x1e, 0x13पूर्ण,
	अणु0x1f, 0x00पूर्ण,
	अणु0x23, 0x00पूर्ण,
	अणु0x24, 0x00पूर्ण,
	अणु0x25, 0x00पूर्ण,
	अणु0x26, 0x00पूर्ण,
	अणु0x27, 0x00पूर्ण,
	अणु0x28, 0x00पूर्ण,
	अणु0x35, 0x00पूर्ण,
	अणु0x66, 0x00पूर्ण,
	अणु0x58, 0x82पूर्ण,
	अणु0x59, 0x02पूर्ण,
	अणु0x5a, 0x02पूर्ण,
	अणु0x5b, 0x02पूर्ण,
	अणु0x5c, 0x82पूर्ण,
	अणु0x5d, 0x82पूर्ण,
	अणु0x5e, 0x02पूर्ण,
	अणु0x5f, 0x02पूर्ण,
	अणु0x72, 0x31पूर्ण,
	/* Select CMD2 Page4 (Unकरोcumented) */
	अणु0xff, 0x05पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	अणु0x00, 0x01पूर्ण,
	अणु0x01, 0x0bपूर्ण,
	अणु0x02, 0x0cपूर्ण,
	अणु0x03, 0x09पूर्ण,
	अणु0x04, 0x0aपूर्ण,
	अणु0x05, 0x00पूर्ण,
	अणु0x06, 0x0fपूर्ण,
	अणु0x07, 0x10पूर्ण,
	अणु0x08, 0x00पूर्ण,
	अणु0x09, 0x00पूर्ण,
	अणु0x0a, 0x00पूर्ण,
	अणु0x0b, 0x00पूर्ण,
	अणु0x0c, 0x00पूर्ण,
	अणु0x0d, 0x13पूर्ण,
	अणु0x0e, 0x15पूर्ण,
	अणु0x0f, 0x17पूर्ण,
	अणु0x10, 0x01पूर्ण,
	अणु0x11, 0x0bपूर्ण,
	अणु0x12, 0x0cपूर्ण,
	अणु0x13, 0x09पूर्ण,
	अणु0x14, 0x0aपूर्ण,
	अणु0x15, 0x00पूर्ण,
	अणु0x16, 0x0fपूर्ण,
	अणु0x17, 0x10पूर्ण,
	अणु0x18, 0x00पूर्ण,
	अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x00पूर्ण,
	अणु0x1b, 0x00पूर्ण,
	अणु0x1c, 0x00पूर्ण,
	अणु0x1d, 0x13पूर्ण,
	अणु0x1e, 0x15पूर्ण,
	अणु0x1f, 0x17पूर्ण,
	अणु0x20, 0x00पूर्ण,
	अणु0x21, 0x03पूर्ण,
	अणु0x22, 0x01पूर्ण,
	अणु0x23, 0x40पूर्ण,
	अणु0x24, 0x40पूर्ण,
	अणु0x25, 0xedपूर्ण,
	अणु0x29, 0x58पूर्ण,
	अणु0x2a, 0x12पूर्ण,
	अणु0x2b, 0x01पूर्ण,
	अणु0x4b, 0x06पूर्ण,
	अणु0x4c, 0x11पूर्ण,
	अणु0x4d, 0x20पूर्ण,
	अणु0x4e, 0x02पूर्ण,
	अणु0x4f, 0x02पूर्ण,
	अणु0x50, 0x20पूर्ण,
	अणु0x51, 0x61पूर्ण,
	अणु0x52, 0x01पूर्ण,
	अणु0x53, 0x63पूर्ण,
	अणु0x54, 0x77पूर्ण,
	अणु0x55, 0xedपूर्ण,
	अणु0x5b, 0x00पूर्ण,
	अणु0x5c, 0x00पूर्ण,
	अणु0x5d, 0x00पूर्ण,
	अणु0x5e, 0x00पूर्ण,
	अणु0x5f, 0x15पूर्ण,
	अणु0x60, 0x75पूर्ण,
	अणु0x61, 0x00पूर्ण,
	अणु0x62, 0x00पूर्ण,
	अणु0x63, 0x00पूर्ण,
	अणु0x64, 0x00पूर्ण,
	अणु0x65, 0x00पूर्ण,
	अणु0x66, 0x00पूर्ण,
	अणु0x67, 0x00पूर्ण,
	अणु0x68, 0x04पूर्ण,
	अणु0x69, 0x00पूर्ण,
	अणु0x6a, 0x00पूर्ण,
	अणु0x6c, 0x40पूर्ण,
	अणु0x75, 0x01पूर्ण,
	अणु0x76, 0x01पूर्ण,
	अणु0x7a, 0x80पूर्ण,
	अणु0x7b, 0xa3पूर्ण,
	अणु0x7c, 0xd8पूर्ण,
	अणु0x7d, 0x60पूर्ण,
	अणु0x7f, 0x15पूर्ण,
	अणु0x80, 0x81पूर्ण,
	अणु0x83, 0x05पूर्ण,
	अणु0x93, 0x08पूर्ण,
	अणु0x94, 0x10पूर्ण,
	अणु0x8a, 0x00पूर्ण,
	अणु0x9b, 0x0fपूर्ण,
	अणु0xea, 0xffपूर्ण,
	अणु0xec, 0x00पूर्ण,
	/* Select CMD2 Page0 (Unकरोcumented) */
	अणु0xff, 0x01पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	अणु0x75, 0x00पूर्ण,
	अणु0x76, 0xdfपूर्ण,
	अणु0x77, 0x00पूर्ण,
	अणु0x78, 0xe4पूर्ण,
	अणु0x79, 0x00पूर्ण,
	अणु0x7a, 0xedपूर्ण,
	अणु0x7b, 0x00पूर्ण,
	अणु0x7c, 0xf6पूर्ण,
	अणु0x7d, 0x00पूर्ण,
	अणु0x7e, 0xffपूर्ण,
	अणु0x7f, 0x01पूर्ण,
	अणु0x80, 0x07पूर्ण,
	अणु0x81, 0x01पूर्ण,
	अणु0x82, 0x10पूर्ण,
	अणु0x83, 0x01पूर्ण,
	अणु0x84, 0x18पूर्ण,
	अणु0x85, 0x01पूर्ण,
	अणु0x86, 0x20पूर्ण,
	अणु0x87, 0x01पूर्ण,
	अणु0x88, 0x3dपूर्ण,
	अणु0x89, 0x01पूर्ण,
	अणु0x8a, 0x56पूर्ण,
	अणु0x8b, 0x01पूर्ण,
	अणु0x8c, 0x84पूर्ण,
	अणु0x8d, 0x01पूर्ण,
	अणु0x8e, 0xabपूर्ण,
	अणु0x8f, 0x01पूर्ण,
	अणु0x90, 0xecपूर्ण,
	अणु0x91, 0x02पूर्ण,
	अणु0x92, 0x22पूर्ण,
	अणु0x93, 0x02पूर्ण,
	अणु0x94, 0x23पूर्ण,
	अणु0x95, 0x02पूर्ण,
	अणु0x96, 0x55पूर्ण,
	अणु0x97, 0x02पूर्ण,
	अणु0x98, 0x8bपूर्ण,
	अणु0x99, 0x02पूर्ण,
	अणु0x9a, 0xafपूर्ण,
	अणु0x9b, 0x02पूर्ण,
	अणु0x9c, 0xdfपूर्ण,
	अणु0x9d, 0x03पूर्ण,
	अणु0x9e, 0x01पूर्ण,
	अणु0x9f, 0x03पूर्ण,
	अणु0xa0, 0x2cपूर्ण,
	अणु0xa2, 0x03पूर्ण,
	अणु0xa3, 0x39पूर्ण,
	अणु0xa4, 0x03पूर्ण,
	अणु0xa5, 0x47पूर्ण,
	अणु0xa6, 0x03पूर्ण,
	अणु0xa7, 0x56पूर्ण,
	अणु0xa9, 0x03पूर्ण,
	अणु0xaa, 0x66पूर्ण,
	अणु0xab, 0x03पूर्ण,
	अणु0xac, 0x76पूर्ण,
	अणु0xad, 0x03पूर्ण,
	अणु0xae, 0x85पूर्ण,
	अणु0xaf, 0x03पूर्ण,
	अणु0xb0, 0x90पूर्ण,
	अणु0xb1, 0x03पूर्ण,
	अणु0xb2, 0xcbपूर्ण,
	अणु0xb3, 0x00पूर्ण,
	अणु0xb4, 0xdfपूर्ण,
	अणु0xb5, 0x00पूर्ण,
	अणु0xb6, 0xe4पूर्ण,
	अणु0xb7, 0x00पूर्ण,
	अणु0xb8, 0xedपूर्ण,
	अणु0xb9, 0x00पूर्ण,
	अणु0xba, 0xf6पूर्ण,
	अणु0xbb, 0x00पूर्ण,
	अणु0xbc, 0xffपूर्ण,
	अणु0xbd, 0x01पूर्ण,
	अणु0xbe, 0x07पूर्ण,
	अणु0xbf, 0x01पूर्ण,
	अणु0xc0, 0x10पूर्ण,
	अणु0xc1, 0x01पूर्ण,
	अणु0xc2, 0x18पूर्ण,
	अणु0xc3, 0x01पूर्ण,
	अणु0xc4, 0x20पूर्ण,
	अणु0xc5, 0x01पूर्ण,
	अणु0xc6, 0x3dपूर्ण,
	अणु0xc7, 0x01पूर्ण,
	अणु0xc8, 0x56पूर्ण,
	अणु0xc9, 0x01पूर्ण,
	अणु0xca, 0x84पूर्ण,
	अणु0xcb, 0x01पूर्ण,
	अणु0xcc, 0xabपूर्ण,
	अणु0xcd, 0x01पूर्ण,
	अणु0xce, 0xecपूर्ण,
	अणु0xcf, 0x02पूर्ण,
	अणु0xd0, 0x22पूर्ण,
	अणु0xd1, 0x02पूर्ण,
	अणु0xd2, 0x23पूर्ण,
	अणु0xd3, 0x02पूर्ण,
	अणु0xd4, 0x55पूर्ण,
	अणु0xd5, 0x02पूर्ण,
	अणु0xd6, 0x8bपूर्ण,
	अणु0xd7, 0x02पूर्ण,
	अणु0xd8, 0xafपूर्ण,
	अणु0xd9, 0x02पूर्ण,
	अणु0xda, 0xdfपूर्ण,
	अणु0xdb, 0x03पूर्ण,
	अणु0xdc, 0x01पूर्ण,
	अणु0xdd, 0x03पूर्ण,
	अणु0xde, 0x2cपूर्ण,
	अणु0xdf, 0x03पूर्ण,
	अणु0xe0, 0x39पूर्ण,
	अणु0xe1, 0x03पूर्ण,
	अणु0xe2, 0x47पूर्ण,
	अणु0xe3, 0x03पूर्ण,
	अणु0xe4, 0x56पूर्ण,
	अणु0xe5, 0x03पूर्ण,
	अणु0xe6, 0x66पूर्ण,
	अणु0xe7, 0x03पूर्ण,
	अणु0xe8, 0x76पूर्ण,
	अणु0xe9, 0x03पूर्ण,
	अणु0xea, 0x85पूर्ण,
	अणु0xeb, 0x03पूर्ण,
	अणु0xec, 0x90पूर्ण,
	अणु0xed, 0x03पूर्ण,
	अणु0xee, 0xcbपूर्ण,
	अणु0xef, 0x00पूर्ण,
	अणु0xf0, 0xbbपूर्ण,
	अणु0xf1, 0x00पूर्ण,
	अणु0xf2, 0xc0पूर्ण,
	अणु0xf3, 0x00पूर्ण,
	अणु0xf4, 0xccपूर्ण,
	अणु0xf5, 0x00पूर्ण,
	अणु0xf6, 0xd6पूर्ण,
	अणु0xf7, 0x00पूर्ण,
	अणु0xf8, 0xe1पूर्ण,
	अणु0xf9, 0x00पूर्ण,
	अणु0xfa, 0xeaपूर्ण,
	/* Select CMD2 Page2 (Unकरोcumented) */
	अणु0xff, 0x02पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	अणु0x00, 0x00पूर्ण,
	अणु0x01, 0xf4पूर्ण,
	अणु0x02, 0x00पूर्ण,
	अणु0x03, 0xefपूर्ण,
	अणु0x04, 0x01पूर्ण,
	अणु0x05, 0x07पूर्ण,
	अणु0x06, 0x01पूर्ण,
	अणु0x07, 0x28पूर्ण,
	अणु0x08, 0x01पूर्ण,
	अणु0x09, 0x44पूर्ण,
	अणु0x0a, 0x01पूर्ण,
	अणु0x0b, 0x76पूर्ण,
	अणु0x0c, 0x01पूर्ण,
	अणु0x0d, 0xa0पूर्ण,
	अणु0x0e, 0x01पूर्ण,
	अणु0x0f, 0xe7पूर्ण,
	अणु0x10, 0x02पूर्ण,
	अणु0x11, 0x1fपूर्ण,
	अणु0x12, 0x02पूर्ण,
	अणु0x13, 0x22पूर्ण,
	अणु0x14, 0x02पूर्ण,
	अणु0x15, 0x54पूर्ण,
	अणु0x16, 0x02पूर्ण,
	अणु0x17, 0x8bपूर्ण,
	अणु0x18, 0x02पूर्ण,
	अणु0x19, 0xafपूर्ण,
	अणु0x1a, 0x02पूर्ण,
	अणु0x1b, 0xe0पूर्ण,
	अणु0x1c, 0x03पूर्ण,
	अणु0x1d, 0x01पूर्ण,
	अणु0x1e, 0x03पूर्ण,
	अणु0x1f, 0x2dपूर्ण,
	अणु0x20, 0x03पूर्ण,
	अणु0x21, 0x39पूर्ण,
	अणु0x22, 0x03पूर्ण,
	अणु0x23, 0x47पूर्ण,
	अणु0x24, 0x03पूर्ण,
	अणु0x25, 0x57पूर्ण,
	अणु0x26, 0x03पूर्ण,
	अणु0x27, 0x65पूर्ण,
	अणु0x28, 0x03पूर्ण,
	अणु0x29, 0x77पूर्ण,
	अणु0x2a, 0x03पूर्ण,
	अणु0x2b, 0x85पूर्ण,
	अणु0x2d, 0x03पूर्ण,
	अणु0x2f, 0x8fपूर्ण,
	अणु0x30, 0x03पूर्ण,
	अणु0x31, 0xcbपूर्ण,
	अणु0x32, 0x00पूर्ण,
	अणु0x33, 0xbbपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0xc0पूर्ण,
	अणु0x36, 0x00पूर्ण,
	अणु0x37, 0xccपूर्ण,
	अणु0x38, 0x00पूर्ण,
	अणु0x39, 0xd6पूर्ण,
	अणु0x3a, 0x00पूर्ण,
	अणु0x3b, 0xe1पूर्ण,
	अणु0x3d, 0x00पूर्ण,
	अणु0x3f, 0xeaपूर्ण,
	अणु0x40, 0x00पूर्ण,
	अणु0x41, 0xf4पूर्ण,
	अणु0x42, 0x00पूर्ण,
	अणु0x43, 0xfeपूर्ण,
	अणु0x44, 0x01पूर्ण,
	अणु0x45, 0x07पूर्ण,
	अणु0x46, 0x01पूर्ण,
	अणु0x47, 0x28पूर्ण,
	अणु0x48, 0x01पूर्ण,
	अणु0x49, 0x44पूर्ण,
	अणु0x4a, 0x01पूर्ण,
	अणु0x4b, 0x76पूर्ण,
	अणु0x4c, 0x01पूर्ण,
	अणु0x4d, 0xa0पूर्ण,
	अणु0x4e, 0x01पूर्ण,
	अणु0x4f, 0xe7पूर्ण,
	अणु0x50, 0x02पूर्ण,
	अणु0x51, 0x1fपूर्ण,
	अणु0x52, 0x02पूर्ण,
	अणु0x53, 0x22पूर्ण,
	अणु0x54, 0x02पूर्ण,
	अणु0x55, 0x54पूर्ण,
	अणु0x56, 0x02पूर्ण,
	अणु0x58, 0x8bपूर्ण,
	अणु0x59, 0x02पूर्ण,
	अणु0x5a, 0xafपूर्ण,
	अणु0x5b, 0x02पूर्ण,
	अणु0x5c, 0xe0पूर्ण,
	अणु0x5d, 0x03पूर्ण,
	अणु0x5e, 0x01पूर्ण,
	अणु0x5f, 0x03पूर्ण,
	अणु0x60, 0x2dपूर्ण,
	अणु0x61, 0x03पूर्ण,
	अणु0x62, 0x39पूर्ण,
	अणु0x63, 0x03पूर्ण,
	अणु0x64, 0x47पूर्ण,
	अणु0x65, 0x03पूर्ण,
	अणु0x66, 0x57पूर्ण,
	अणु0x67, 0x03पूर्ण,
	अणु0x68, 0x65पूर्ण,
	अणु0x69, 0x03पूर्ण,
	अणु0x6a, 0x77पूर्ण,
	अणु0x6b, 0x03पूर्ण,
	अणु0x6c, 0x85पूर्ण,
	अणु0x6d, 0x03पूर्ण,
	अणु0x6e, 0x8fपूर्ण,
	अणु0x6f, 0x03पूर्ण,
	अणु0x70, 0xcbपूर्ण,
	अणु0x71, 0x00पूर्ण,
	अणु0x72, 0x00पूर्ण,
	अणु0x73, 0x00पूर्ण,
	अणु0x74, 0x21पूर्ण,
	अणु0x75, 0x00पूर्ण,
	अणु0x76, 0x4cपूर्ण,
	अणु0x77, 0x00पूर्ण,
	अणु0x78, 0x6bपूर्ण,
	अणु0x79, 0x00पूर्ण,
	अणु0x7a, 0x85पूर्ण,
	अणु0x7b, 0x00पूर्ण,
	अणु0x7c, 0x9aपूर्ण,
	अणु0x7d, 0x00पूर्ण,
	अणु0x7e, 0xadपूर्ण,
	अणु0x7f, 0x00पूर्ण,
	अणु0x80, 0xbeपूर्ण,
	अणु0x81, 0x00पूर्ण,
	अणु0x82, 0xcdपूर्ण,
	अणु0x83, 0x01पूर्ण,
	अणु0x84, 0x01पूर्ण,
	अणु0x85, 0x01पूर्ण,
	अणु0x86, 0x29पूर्ण,
	अणु0x87, 0x01पूर्ण,
	अणु0x88, 0x68पूर्ण,
	अणु0x89, 0x01पूर्ण,
	अणु0x8a, 0x98पूर्ण,
	अणु0x8b, 0x01पूर्ण,
	अणु0x8c, 0xe5पूर्ण,
	अणु0x8d, 0x02पूर्ण,
	अणु0x8e, 0x1eपूर्ण,
	अणु0x8f, 0x02पूर्ण,
	अणु0x90, 0x30पूर्ण,
	अणु0x91, 0x02पूर्ण,
	अणु0x92, 0x52पूर्ण,
	अणु0x93, 0x02पूर्ण,
	अणु0x94, 0x88पूर्ण,
	अणु0x95, 0x02पूर्ण,
	अणु0x96, 0xaaपूर्ण,
	अणु0x97, 0x02पूर्ण,
	अणु0x98, 0xd7पूर्ण,
	अणु0x99, 0x02पूर्ण,
	अणु0x9a, 0xf7पूर्ण,
	अणु0x9b, 0x03पूर्ण,
	अणु0x9c, 0x21पूर्ण,
	अणु0x9d, 0x03पूर्ण,
	अणु0x9e, 0x2eपूर्ण,
	अणु0x9f, 0x03पूर्ण,
	अणु0xa0, 0x3dपूर्ण,
	अणु0xa2, 0x03पूर्ण,
	अणु0xa3, 0x4cपूर्ण,
	अणु0xa4, 0x03पूर्ण,
	अणु0xa5, 0x5eपूर्ण,
	अणु0xa6, 0x03पूर्ण,
	अणु0xa7, 0x71पूर्ण,
	अणु0xa9, 0x03पूर्ण,
	अणु0xaa, 0x86पूर्ण,
	अणु0xab, 0x03पूर्ण,
	अणु0xac, 0x94पूर्ण,
	अणु0xad, 0x03पूर्ण,
	अणु0xae, 0xfaपूर्ण,
	अणु0xaf, 0x00पूर्ण,
	अणु0xb0, 0x00पूर्ण,
	अणु0xb1, 0x00पूर्ण,
	अणु0xb2, 0x21पूर्ण,
	अणु0xb3, 0x00पूर्ण,
	अणु0xb4, 0x4cपूर्ण,
	अणु0xb5, 0x00पूर्ण,
	अणु0xb6, 0x6bपूर्ण,
	अणु0xb7, 0x00पूर्ण,
	अणु0xb8, 0x85पूर्ण,
	अणु0xb9, 0x00पूर्ण,
	अणु0xba, 0x9aपूर्ण,
	अणु0xbb, 0x00पूर्ण,
	अणु0xbc, 0xadपूर्ण,
	अणु0xbd, 0x00पूर्ण,
	अणु0xbe, 0xbeपूर्ण,
	अणु0xbf, 0x00पूर्ण,
	अणु0xc0, 0xcdपूर्ण,
	अणु0xc1, 0x01पूर्ण,
	अणु0xc2, 0x01पूर्ण,
	अणु0xc3, 0x01पूर्ण,
	अणु0xc4, 0x29पूर्ण,
	अणु0xc5, 0x01पूर्ण,
	अणु0xc6, 0x68पूर्ण,
	अणु0xc7, 0x01पूर्ण,
	अणु0xc8, 0x98पूर्ण,
	अणु0xc9, 0x01पूर्ण,
	अणु0xca, 0xe5पूर्ण,
	अणु0xcb, 0x02पूर्ण,
	अणु0xcc, 0x1eपूर्ण,
	अणु0xcd, 0x02पूर्ण,
	अणु0xce, 0x20पूर्ण,
	अणु0xcf, 0x02पूर्ण,
	अणु0xd0, 0x52पूर्ण,
	अणु0xd1, 0x02पूर्ण,
	अणु0xd2, 0x88पूर्ण,
	अणु0xd3, 0x02पूर्ण,
	अणु0xd4, 0xaaपूर्ण,
	अणु0xd5, 0x02पूर्ण,
	अणु0xd6, 0xd7पूर्ण,
	अणु0xd7, 0x02पूर्ण,
	अणु0xd8, 0xf7पूर्ण,
	अणु0xd9, 0x03पूर्ण,
	अणु0xda, 0x21पूर्ण,
	अणु0xdb, 0x03पूर्ण,
	अणु0xdc, 0x2eपूर्ण,
	अणु0xdd, 0x03पूर्ण,
	अणु0xde, 0x3dपूर्ण,
	अणु0xdf, 0x03पूर्ण,
	अणु0xe0, 0x4cपूर्ण,
	अणु0xe1, 0x03पूर्ण,
	अणु0xe2, 0x5eपूर्ण,
	अणु0xe3, 0x03पूर्ण,
	अणु0xe4, 0x71पूर्ण,
	अणु0xe5, 0x03पूर्ण,
	अणु0xe6, 0x86पूर्ण,
	अणु0xe7, 0x03पूर्ण,
	अणु0xe8, 0x94पूर्ण,
	अणु0xe9, 0x03पूर्ण,
	अणु0xea, 0xfaपूर्ण,
	/* Select CMD2 Page0 (Unकरोcumented) */
	अणु0xff, 0x01पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	/* Select CMD2 Page1 (Unकरोcumented) */
	अणु0xff, 0x02पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	/* Select CMD2 Page3 (Unकरोcumented) */
	अणु0xff, 0x04पूर्ण,
	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	अणु0xfb, 0x01पूर्ण,
	/* Select CMD1 */
	अणु0xff, 0x00पूर्ण,
	अणु0xd3, 0x05पूर्ण, /* RGBMIPICTRL: VSYNC back porch = 5 */
	अणु0xd4, 0x04पूर्ण, /* RGBMIPICTRL: VSYNC front porch = 4 */
पूर्ण;

अटल अंतरभूत
काष्ठा khadas_ts050_panel *to_khadas_ts050_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा khadas_ts050_panel, base);
पूर्ण

अटल पूर्णांक khadas_ts050_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = to_khadas_ts050_panel(panel);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (khadas_ts050->prepared)
		वापस 0;

	gpiod_set_value_cansleep(khadas_ts050->enable_gpio, 0);

	err = regulator_enable(khadas_ts050->supply);
	अगर (err < 0)
		वापस err;

	gpiod_set_value_cansleep(khadas_ts050->enable_gpio, 1);

	msleep(60);

	gpiod_set_value_cansleep(khadas_ts050->reset_gpio, 1);

	usleep_range(10000, 11000);

	gpiod_set_value_cansleep(khadas_ts050->reset_gpio, 0);

	/* Select CMD2 page 4 (Unकरोcumented) */
	mipi_dsi_dcs_ग_लिखो(khadas_ts050->link, 0xff, (u8[])अणु 0x05 पूर्ण, 1);

	/* Reload CMD1: Don't reload शेष value to रेजिस्टर */
	mipi_dsi_dcs_ग_लिखो(khadas_ts050->link, 0xfb, (u8[])अणु 0x01 पूर्ण, 1);

	mipi_dsi_dcs_ग_लिखो(khadas_ts050->link, 0xc5, (u8[])अणु 0x01 पूर्ण, 1);

	msleep(100);

	क्रम (i = 0; i < ARRAY_SIZE(init_code); i++) अणु
		err = mipi_dsi_dcs_ग_लिखो(khadas_ts050->link,
					 init_code[i].cmd,
					 &init_code[i].data, 1);
		अगर (err < 0) अणु
			dev_err(panel->dev, "failed write cmds: %d\n", err);
			जाओ घातeroff;
		पूर्ण
	पूर्ण

	err = mipi_dsi_dcs_निकास_sleep_mode(khadas_ts050->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	msleep(120);

	/* Select CMD1 */
	mipi_dsi_dcs_ग_लिखो(khadas_ts050->link, 0xff, (u8[])अणु 0x00 पूर्ण, 1);

	err = mipi_dsi_dcs_set_tear_on(khadas_ts050->link,
				       MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set tear on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	err = mipi_dsi_dcs_set_display_on(khadas_ts050->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	usleep_range(10000, 11000);

	khadas_ts050->prepared = true;

	वापस 0;

घातeroff:
	gpiod_set_value_cansleep(khadas_ts050->enable_gpio, 0);
	gpiod_set_value_cansleep(khadas_ts050->reset_gpio, 1);

	regulator_disable(khadas_ts050->supply);

	वापस err;
पूर्ण

अटल पूर्णांक khadas_ts050_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = to_khadas_ts050_panel(panel);
	पूर्णांक err;

	अगर (!khadas_ts050->prepared)
		वापस 0;

	khadas_ts050->prepared = false;

	err = mipi_dsi_dcs_enter_sleep_mode(khadas_ts050->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);

	msleep(150);

	gpiod_set_value_cansleep(khadas_ts050->enable_gpio, 0);
	gpiod_set_value_cansleep(khadas_ts050->reset_gpio, 1);

	err = regulator_disable(khadas_ts050->supply);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_ts050_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = to_khadas_ts050_panel(panel);

	khadas_ts050->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_ts050_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = to_khadas_ts050_panel(panel);
	पूर्णांक err;

	अगर (!khadas_ts050->enabled)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(khadas_ts050->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	usleep_range(10000, 11000);

	khadas_ts050->enabled = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 120000,
	.hdisplay = 1088,
	.hsync_start = 1088 + 104,
	.hsync_end = 1088 + 104 + 4,
	.htotal = 1088 + 104 + 4 + 127,
	.vdisplay = 1920,
	.vsync_start = 1920 + 4,
	.vsync_end = 1920 + 4 + 2,
	.vtotal = 1920 + 4 + 2 + 3,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल पूर्णांक khadas_ts050_panel_get_modes(काष्ठा drm_panel *panel,
					काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 64;
	connector->display_info.height_mm = 118;
	connector->display_info.bpc = 8;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs khadas_ts050_panel_funcs = अणु
	.prepare = khadas_ts050_panel_prepare,
	.unprepare = khadas_ts050_panel_unprepare,
	.enable = khadas_ts050_panel_enable,
	.disable = khadas_ts050_panel_disable,
	.get_modes = khadas_ts050_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id khadas_ts050_of_match[] = अणु
	अणु .compatible = "khadas,ts050", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, khadas_ts050_of_match);

अटल पूर्णांक khadas_ts050_panel_add(काष्ठा khadas_ts050_panel *khadas_ts050)
अणु
	काष्ठा device *dev = &khadas_ts050->link->dev;
	पूर्णांक err;

	khadas_ts050->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(khadas_ts050->supply))
		वापस dev_err_probe(dev, PTR_ERR(khadas_ts050->supply),
				     "failed to get power supply");

	khadas_ts050->reset_gpio = devm_gpiod_get(dev, "reset",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(khadas_ts050->reset_gpio))
		वापस dev_err_probe(dev, PTR_ERR(khadas_ts050->reset_gpio),
				     "failed to get reset gpio");

	khadas_ts050->enable_gpio = devm_gpiod_get(dev, "enable",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(khadas_ts050->enable_gpio))
		वापस dev_err_probe(dev, PTR_ERR(khadas_ts050->enable_gpio),
				     "failed to get enable gpio");

	drm_panel_init(&khadas_ts050->base, &khadas_ts050->link->dev,
		       &khadas_ts050_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	err = drm_panel_of_backlight(&khadas_ts050->base);
	अगर (err)
		वापस err;

	drm_panel_add(&khadas_ts050->base);

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_ts050_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050;
	पूर्णांक err;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_EOT_PACKET;

	khadas_ts050 = devm_kzalloc(&dsi->dev, माप(*khadas_ts050),
				    GFP_KERNEL);
	अगर (!khadas_ts050)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, khadas_ts050);
	khadas_ts050->link = dsi;

	err = khadas_ts050_panel_add(khadas_ts050);
	अगर (err < 0)
		वापस err;

	err = mipi_dsi_attach(dsi);
	अगर (err)
		drm_panel_हटाओ(&khadas_ts050->base);

	वापस err;
पूर्ण

अटल पूर्णांक khadas_ts050_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	drm_panel_हटाओ(&khadas_ts050->base);
	drm_panel_disable(&khadas_ts050->base);
	drm_panel_unprepare(&khadas_ts050->base);

	वापस 0;
पूर्ण

अटल व्योम khadas_ts050_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा khadas_ts050_panel *khadas_ts050 = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&khadas_ts050->base);
	drm_panel_unprepare(&khadas_ts050->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver khadas_ts050_panel_driver = अणु
	.driver = अणु
		.name = "panel-khadas-ts050",
		.of_match_table = khadas_ts050_of_match,
	पूर्ण,
	.probe = khadas_ts050_panel_probe,
	.हटाओ = khadas_ts050_panel_हटाओ,
	.shutकरोwn = khadas_ts050_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(khadas_ts050_panel_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Khadas TS050 panel driver");
MODULE_LICENSE("GPL v2");
