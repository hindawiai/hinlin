<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, NVIDIA Corporation.
 */

#अगर_अघोषित _FALCON_H_
#घोषणा _FALCON_H_

#समावेश <linux/types.h>

#घोषणा FALCON_UCLASS_METHOD_OFFSET		0x00000040

#घोषणा FALCON_UCLASS_METHOD_DATA		0x00000044

#घोषणा FALCON_IRQMSET				0x00001010
#घोषणा FALCON_IRQMSET_WDTMR			(1 << 1)
#घोषणा FALCON_IRQMSET_HALT			(1 << 4)
#घोषणा FALCON_IRQMSET_EXTERR			(1 << 5)
#घोषणा FALCON_IRQMSET_SWGEN0			(1 << 6)
#घोषणा FALCON_IRQMSET_SWGEN1			(1 << 7)
#घोषणा FALCON_IRQMSET_EXT(v)			(((v) & 0xff) << 8)

#घोषणा FALCON_IRQDEST				0x0000101c
#घोषणा FALCON_IRQDEST_HALT			(1 << 4)
#घोषणा FALCON_IRQDEST_EXTERR			(1 << 5)
#घोषणा FALCON_IRQDEST_SWGEN0			(1 << 6)
#घोषणा FALCON_IRQDEST_SWGEN1			(1 << 7)
#घोषणा FALCON_IRQDEST_EXT(v)			(((v) & 0xff) << 8)

#घोषणा FALCON_ITFEN				0x00001048
#घोषणा FALCON_ITFEN_CTXEN			(1 << 0)
#घोषणा FALCON_ITFEN_MTHDEN			(1 << 1)

#घोषणा FALCON_IDLESTATE			0x0000104c

#घोषणा FALCON_CPUCTL				0x00001100
#घोषणा FALCON_CPUCTL_STARTCPU			(1 << 1)

#घोषणा FALCON_BOOTVEC				0x00001104

#घोषणा FALCON_DMACTL				0x0000110c
#घोषणा FALCON_DMACTL_DMEM_SCRUBBING		(1 << 1)
#घोषणा FALCON_DMACTL_IMEM_SCRUBBING		(1 << 2)

#घोषणा FALCON_DMATRFBASE			0x00001110

#घोषणा FALCON_DMATRFMOFFS			0x00001114

#घोषणा FALCON_DMATRFCMD			0x00001118
#घोषणा FALCON_DMATRFCMD_IDLE			(1 << 1)
#घोषणा FALCON_DMATRFCMD_IMEM			(1 << 4)
#घोषणा FALCON_DMATRFCMD_SIZE_256B		(6 << 8)

#घोषणा FALCON_DMATRFFBOFFS			0x0000111c

काष्ठा falcon_fw_bin_header_v1 अणु
	u32 magic;		/* 0x10de */
	u32 version;		/* version of bin क्रमmat (1) */
	u32 size;		/* entire image size including this header */
	u32 os_header_offset;
	u32 os_data_offset;
	u32 os_size;
पूर्ण;

काष्ठा falcon_fw_os_app_v1 अणु
	u32 offset;
	u32 size;
पूर्ण;

काष्ठा falcon_fw_os_header_v1 अणु
	u32 code_offset;
	u32 code_size;
	u32 data_offset;
	u32 data_size;
पूर्ण;

काष्ठा falcon_firmware_section अणु
	अचिन्हित दीर्घ offset;
	माप_प्रकार size;
पूर्ण;

काष्ठा falcon_firmware अणु
	/* Firmware after it is पढ़ो but not loaded */
	स्थिर काष्ठा firmware *firmware;

	/* Raw firmware data */
	dma_addr_t iova;
	dma_addr_t phys;
	व्योम *virt;
	माप_प्रकार size;

	/* Parsed firmware inक्रमmation */
	काष्ठा falcon_firmware_section bin_data;
	काष्ठा falcon_firmware_section data;
	काष्ठा falcon_firmware_section code;
पूर्ण;

काष्ठा falcon अणु
	/* Set by falcon client */
	काष्ठा device *dev;
	व्योम __iomem *regs;

	काष्ठा falcon_firmware firmware;
पूर्ण;

पूर्णांक falcon_init(काष्ठा falcon *falcon);
व्योम falcon_निकास(काष्ठा falcon *falcon);
पूर्णांक falcon_पढ़ो_firmware(काष्ठा falcon *falcon, स्थिर अक्षर *firmware_name);
पूर्णांक falcon_load_firmware(काष्ठा falcon *falcon);
पूर्णांक falcon_boot(काष्ठा falcon *falcon);
व्योम falcon_execute_method(काष्ठा falcon *falcon, u32 method, u32 data);
पूर्णांक falcon_रुको_idle(काष्ठा falcon *falcon);

#पूर्ण_अगर /* _FALCON_H_ */
