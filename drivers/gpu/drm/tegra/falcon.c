<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, NVIDIA Corporation.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/iopoll.h>

#समावेश "falcon.h"
#समावेश "drm.h"

क्रमागत falcon_memory अणु
	FALCON_MEMORY_IMEM,
	FALCON_MEMORY_DATA,
पूर्ण;

अटल व्योम falcon_ग_लिखोl(काष्ठा falcon *falcon, u32 value, u32 offset)
अणु
	ग_लिखोl(value, falcon->regs + offset);
पूर्ण

पूर्णांक falcon_रुको_idle(काष्ठा falcon *falcon)
अणु
	u32 value;

	वापस पढ़ोl_poll_समयout(falcon->regs + FALCON_IDLESTATE, value,
				  (value == 0), 10, 100000);
पूर्ण

अटल पूर्णांक falcon_dma_रुको_idle(काष्ठा falcon *falcon)
अणु
	u32 value;

	वापस पढ़ोl_poll_समयout(falcon->regs + FALCON_DMATRFCMD, value,
				  (value & FALCON_DMATRFCMD_IDLE), 10, 100000);
पूर्ण

अटल पूर्णांक falcon_copy_chunk(काष्ठा falcon *falcon,
			     phys_addr_t base,
			     अचिन्हित दीर्घ offset,
			     क्रमागत falcon_memory target)
अणु
	u32 cmd = FALCON_DMATRFCMD_SIZE_256B;

	अगर (target == FALCON_MEMORY_IMEM)
		cmd |= FALCON_DMATRFCMD_IMEM;

	falcon_ग_लिखोl(falcon, offset, FALCON_DMATRFMOFFS);
	falcon_ग_लिखोl(falcon, base, FALCON_DMATRFFBOFFS);
	falcon_ग_लिखोl(falcon, cmd, FALCON_DMATRFCMD);

	वापस falcon_dma_रुको_idle(falcon);
पूर्ण

अटल व्योम falcon_copy_firmware_image(काष्ठा falcon *falcon,
				       स्थिर काष्ठा firmware *firmware)
अणु
	u32 *virt = falcon->firmware.virt;
	माप_प्रकार i;

	/* copy the whole thing taking पूर्णांकo account endianness */
	क्रम (i = 0; i < firmware->size / माप(u32); i++)
		virt[i] = le32_to_cpu(((u32 *)firmware->data)[i]);
पूर्ण

अटल पूर्णांक falcon_parse_firmware_image(काष्ठा falcon *falcon)
अणु
	काष्ठा falcon_fw_bin_header_v1 *bin = (व्योम *)falcon->firmware.virt;
	काष्ठा falcon_fw_os_header_v1 *os;

	/* endian problems would show up right here */
	अगर (bin->magic != PCI_VENDOR_ID_NVIDIA && bin->magic != 0x10fe) अणु
		dev_err(falcon->dev, "incorrect firmware magic\n");
		वापस -EINVAL;
	पूर्ण

	/* currently only version 1 is supported */
	अगर (bin->version != 1) अणु
		dev_err(falcon->dev, "unsupported firmware version\n");
		वापस -EINVAL;
	पूर्ण

	/* check that the firmware size is consistent */
	अगर (bin->size > falcon->firmware.size) अणु
		dev_err(falcon->dev, "firmware image size inconsistency\n");
		वापस -EINVAL;
	पूर्ण

	os = falcon->firmware.virt + bin->os_header_offset;

	falcon->firmware.bin_data.size = bin->os_size;
	falcon->firmware.bin_data.offset = bin->os_data_offset;
	falcon->firmware.code.offset = os->code_offset;
	falcon->firmware.code.size = os->code_size;
	falcon->firmware.data.offset = os->data_offset;
	falcon->firmware.data.size = os->data_size;

	वापस 0;
पूर्ण

पूर्णांक falcon_पढ़ो_firmware(काष्ठा falcon *falcon, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	/* request_firmware prपूर्णांकs error अगर it fails */
	err = request_firmware(&falcon->firmware.firmware, name, falcon->dev);
	अगर (err < 0)
		वापस err;

	falcon->firmware.size = falcon->firmware.firmware->size;

	वापस 0;
पूर्ण

पूर्णांक falcon_load_firmware(काष्ठा falcon *falcon)
अणु
	स्थिर काष्ठा firmware *firmware = falcon->firmware.firmware;
	पूर्णांक err;

	/* copy firmware image पूर्णांकo local area. this also ensures endianness */
	falcon_copy_firmware_image(falcon, firmware);

	/* parse the image data */
	err = falcon_parse_firmware_image(falcon);
	अगर (err < 0) अणु
		dev_err(falcon->dev, "failed to parse firmware image\n");
		वापस err;
	पूर्ण

	release_firmware(firmware);
	falcon->firmware.firmware = शून्य;

	वापस 0;
पूर्ण

पूर्णांक falcon_init(काष्ठा falcon *falcon)
अणु
	falcon->firmware.virt = शून्य;

	वापस 0;
पूर्ण

व्योम falcon_निकास(काष्ठा falcon *falcon)
अणु
	अगर (falcon->firmware.firmware)
		release_firmware(falcon->firmware.firmware);
पूर्ण

पूर्णांक falcon_boot(काष्ठा falcon *falcon)
अणु
	अचिन्हित दीर्घ offset;
	u32 value;
	पूर्णांक err;

	अगर (!falcon->firmware.virt)
		वापस -EINVAL;

	err = पढ़ोl_poll_समयout(falcon->regs + FALCON_DMACTL, value,
				 (value & (FALCON_DMACTL_IMEM_SCRUBBING |
					   FALCON_DMACTL_DMEM_SCRUBBING)) == 0,
				 10, 10000);
	अगर (err < 0)
		वापस err;

	falcon_ग_लिखोl(falcon, 0, FALCON_DMACTL);

	/* setup the address of the binary data so Falcon can access it later */
	falcon_ग_लिखोl(falcon, (falcon->firmware.iova +
			       falcon->firmware.bin_data.offset) >> 8,
		      FALCON_DMATRFBASE);

	/* copy the data segment पूर्णांकo Falcon पूर्णांकernal memory */
	क्रम (offset = 0; offset < falcon->firmware.data.size; offset += 256)
		falcon_copy_chunk(falcon,
				  falcon->firmware.data.offset + offset,
				  offset, FALCON_MEMORY_DATA);

	/* copy the code segment पूर्णांकo Falcon पूर्णांकernal memory */
	क्रम (offset = 0; offset < falcon->firmware.code.size; offset += 256)
		falcon_copy_chunk(falcon, falcon->firmware.code.offset + offset,
				  offset, FALCON_MEMORY_IMEM);

	/* setup falcon पूर्णांकerrupts */
	falcon_ग_लिखोl(falcon, FALCON_IRQMSET_EXT(0xff) |
			      FALCON_IRQMSET_SWGEN1 |
			      FALCON_IRQMSET_SWGEN0 |
			      FALCON_IRQMSET_EXTERR |
			      FALCON_IRQMSET_HALT |
			      FALCON_IRQMSET_WDTMR,
		      FALCON_IRQMSET);
	falcon_ग_लिखोl(falcon, FALCON_IRQDEST_EXT(0xff) |
			      FALCON_IRQDEST_SWGEN1 |
			      FALCON_IRQDEST_SWGEN0 |
			      FALCON_IRQDEST_EXTERR |
			      FALCON_IRQDEST_HALT,
		      FALCON_IRQDEST);

	/* enable पूर्णांकerface */
	falcon_ग_लिखोl(falcon, FALCON_ITFEN_MTHDEN |
			      FALCON_ITFEN_CTXEN,
		      FALCON_ITFEN);

	/* boot falcon */
	falcon_ग_लिखोl(falcon, 0x00000000, FALCON_BOOTVEC);
	falcon_ग_लिखोl(falcon, FALCON_CPUCTL_STARTCPU, FALCON_CPUCTL);

	err = falcon_रुको_idle(falcon);
	अगर (err < 0) अणु
		dev_err(falcon->dev, "Falcon boot failed due to timeout\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम falcon_execute_method(काष्ठा falcon *falcon, u32 method, u32 data)
अणु
	falcon_ग_लिखोl(falcon, method >> 2, FALCON_UCLASS_METHOD_OFFSET);
	falcon_ग_लिखोl(falcon, data, FALCON_UCLASS_METHOD_DATA);
पूर्ण
