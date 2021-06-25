<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#अगर_अघोषित __VIAFBDEV_H__
#घोषणा __VIAFBDEV_H__

#समावेश <linux/proc_fs.h>
#समावेश <linux/fb.h>
#समावेश <linux/spinlock.h>

#समावेश "via_aux.h"
#समावेश "ioctl.h"
#समावेश "share.h"
#समावेश "chip.h"
#समावेश "hw.h"

#घोषणा VERSION_MAJOR       2
#घोषणा VERSION_KERNEL      6	/* For kernel 2.6 */

#घोषणा VERSION_OS          0	/* 0: क्रम 32 bits OS, 1: क्रम 64 bits OS */
#घोषणा VERSION_MINOR       4

#घोषणा VIAFB_NUM_I2C		5

काष्ठा viafb_shared अणु
	u32 iga1_devices;
	u32 iga2_devices;

	काष्ठा proc_dir_entry *proc_entry;	/*viafb proc entry */
	काष्ठा proc_dir_entry *iga1_proc_entry;
	काष्ठा proc_dir_entry *iga2_proc_entry;
	काष्ठा viafb_dev *vdev;			/* Global dev info */

	/* I2C busses that may have auxiliary devices */
	काष्ठा via_aux_bus *i2c_26;
	काष्ठा via_aux_bus *i2c_31;
	काष्ठा via_aux_bus *i2c_2C;

	/* All the inक्रमmation will be needed to set engine */
	काष्ठा पंचांगds_setting_inक्रमmation पंचांगds_setting_info;
	काष्ठा lvds_setting_inक्रमmation lvds_setting_info;
	काष्ठा lvds_setting_inक्रमmation lvds_setting_info2;
	काष्ठा chip_inक्रमmation chip_info;

	/* hardware acceleration stuff */
	u32 cursor_vram_addr;
	u32 vq_vram_addr;	/* भव queue address in video ram */
	पूर्णांक (*hw_bitblt)(व्योम __iomem *engine, u8 op, u32 width, u32 height,
		u8 dst_bpp, u32 dst_addr, u32 dst_pitch, u32 dst_x, u32 dst_y,
		u32 *src_mem, u32 src_addr, u32 src_pitch, u32 src_x, u32 src_y,
		u32 fg_color, u32 bg_color, u8 fill_rop);
पूर्ण;

काष्ठा viafb_par अणु
	u8 depth;
	u32 vram_addr;

	अचिन्हित पूर्णांक fbmem;	/*framebuffer physical memory address */
	अचिन्हित पूर्णांक memsize;	/*size of fbmem */
	u32 fbmem_मुक्त;		/* Free FB memory */
	u32 fbmem_used;		/* Use FB memory size */
	u32 iga_path;

	काष्ठा viafb_shared *shared;

	/* All the inक्रमmation will be needed to set engine */
	/* depreciated, use the ones in shared directly */
	काष्ठा पंचांगds_setting_inक्रमmation *पंचांगds_setting_info;
	काष्ठा lvds_setting_inक्रमmation *lvds_setting_info;
	काष्ठा lvds_setting_inक्रमmation *lvds_setting_info2;
	काष्ठा chip_inक्रमmation *chip_info;
पूर्ण;

बाह्य पूर्णांक viafb_SAMM_ON;
बाह्य पूर्णांक viafb_dual_fb;
बाह्य पूर्णांक viafb_LCD2_ON;
बाह्य पूर्णांक viafb_LCD_ON;
बाह्य पूर्णांक viafb_DVI_ON;
बाह्य पूर्णांक viafb_hotplug;

u8 viafb_gpio_i2c_पढ़ो_lvds(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation
	*plvds_chip_info, u8 index);
व्योम viafb_gpio_i2c_ग_लिखो_mask_lvds(काष्ठा lvds_setting_inक्रमmation
			      *plvds_setting_info, काष्ठा lvds_chip_inक्रमmation
			      *plvds_chip_info, काष्ठा IODATA io_data);
पूर्णांक via_fb_pci_probe(काष्ठा viafb_dev *vdev);
व्योम via_fb_pci_हटाओ(काष्ठा pci_dev *pdev);
/* Temporary */
पूर्णांक viafb_init(व्योम);
व्योम viafb_निकास(व्योम);
#पूर्ण_अगर /* __VIAFBDEV_H__ */
