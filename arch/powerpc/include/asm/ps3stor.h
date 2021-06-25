<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PS3 Storage Devices
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corp.
 */

#अगर_अघोषित _ASM_POWERPC_PS3STOR_H_
#घोषणा _ASM_POWERPC_PS3STOR_H_

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/ps3.h>


काष्ठा ps3_storage_region अणु
	अचिन्हित पूर्णांक id;
	u64 start;
	u64 size;
पूर्ण;

काष्ठा ps3_storage_device अणु
	काष्ठा ps3_प्रणाली_bus_device sbd;

	काष्ठा ps3_dma_region dma_region;
	अचिन्हित पूर्णांक irq;
	u64 blk_size;

	u64 tag;
	u64 lv1_status;
	काष्ठा completion करोne;

	अचिन्हित दीर्घ bounce_size;
	व्योम *bounce_buf;
	u64 bounce_lpar;
	dma_addr_t bounce_dma;

	अचिन्हित पूर्णांक num_regions;
	अचिन्हित दीर्घ accessible_regions;
	अचिन्हित पूर्णांक region_idx;		/* first accessible region */
	काष्ठा ps3_storage_region regions[];	/* Must be last */
पूर्ण;

अटल अंतरभूत काष्ठा ps3_storage_device *to_ps3_storage_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा ps3_storage_device, sbd.core);
पूर्ण

बाह्य पूर्णांक ps3stor_setup(काष्ठा ps3_storage_device *dev,
			 irq_handler_t handler);
बाह्य व्योम ps3stor_tearकरोwn(काष्ठा ps3_storage_device *dev);
बाह्य u64 ps3stor_पढ़ो_ग_लिखो_sectors(काष्ठा ps3_storage_device *dev, u64 lpar,
				      u64 start_sector, u64 sectors,
				      पूर्णांक ग_लिखो);
बाह्य u64 ps3stor_send_command(काष्ठा ps3_storage_device *dev, u64 cmd,
				u64 arg1, u64 arg2, u64 arg3, u64 arg4);

#पूर्ण_अगर /* _ASM_POWERPC_PS3STOR_H_ */
