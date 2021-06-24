<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2002 Benjamin Herrenschmidt (benh@kernel.crashing.org)
 *
 *  Toकरो: - add support क्रम the OF persistent properties
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/nvram.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/memblock.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/nvram.h>

#समावेश "pmac.h"

#घोषणा DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

#घोषणा NVRAM_SIZE		0x2000	/* 8kB of non-अस्थिर RAM */

#घोषणा CORE99_SIGNATURE	0x5a
#घोषणा CORE99_ADLER_START	0x14

/* On Core99, nvram is either a sharp, a micron or an AMD flash */
#घोषणा SM_FLASH_STATUS_DONE	0x80
#घोषणा SM_FLASH_STATUS_ERR	0x38

#घोषणा SM_FLASH_CMD_ERASE_CONFIRM	0xd0
#घोषणा SM_FLASH_CMD_ERASE_SETUP	0x20
#घोषणा SM_FLASH_CMD_RESET		0xff
#घोषणा SM_FLASH_CMD_WRITE_SETUP	0x40
#घोषणा SM_FLASH_CMD_CLEAR_STATUS	0x50
#घोषणा SM_FLASH_CMD_READ_STATUS	0x70

/* CHRP NVRAM header */
काष्ठा chrp_header अणु
  u8		signature;
  u8		cksum;
  u16		len;
  अक्षर          name[12];
  u8		data[];
पूर्ण;

काष्ठा core99_header अणु
  काष्ठा chrp_header	hdr;
  u32			adler;
  u32			generation;
  u32			reserved[2];
पूर्ण;

/*
 * Read and ग_लिखो the non-अस्थिर RAM on PowerMacs and CHRP machines.
 */
अटल पूर्णांक nvram_naddrs;
अटल अस्थिर अचिन्हित अक्षर __iomem *nvram_data;
अटल पूर्णांक is_core_99;
अटल पूर्णांक core99_bank = 0;
अटल पूर्णांक nvram_partitions[3];
// XXX Turn that पूर्णांकo a sem
अटल DEFINE_RAW_SPINLOCK(nv_lock);

अटल पूर्णांक (*core99_ग_लिखो_bank)(पूर्णांक bank, u8* datas);
अटल पूर्णांक (*core99_erase_bank)(पूर्णांक bank);

अटल अक्षर *nvram_image;


अटल अचिन्हित अक्षर core99_nvram_पढ़ो_byte(पूर्णांक addr)
अणु
	अगर (nvram_image == शून्य)
		वापस 0xff;
	वापस nvram_image[addr];
पूर्ण

अटल व्योम core99_nvram_ग_लिखो_byte(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	अगर (nvram_image == शून्य)
		वापस;
	nvram_image[addr] = val;
पूर्ण

अटल sमाप_प्रकार core99_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	पूर्णांक i;

	अगर (nvram_image == शून्य)
		वापस -ENODEV;
	अगर (*index > NVRAM_SIZE)
		वापस 0;

	i = *index;
	अगर (i + count > NVRAM_SIZE)
		count = NVRAM_SIZE - i;

	स_नकल(buf, &nvram_image[i], count);
	*index = i + count;
	वापस count;
पूर्ण

अटल sमाप_प्रकार core99_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	पूर्णांक i;

	अगर (nvram_image == शून्य)
		वापस -ENODEV;
	अगर (*index > NVRAM_SIZE)
		वापस 0;

	i = *index;
	अगर (i + count > NVRAM_SIZE)
		count = NVRAM_SIZE - i;

	स_नकल(&nvram_image[i], buf, count);
	*index = i + count;
	वापस count;
पूर्ण

अटल sमाप_प्रकार core99_nvram_size(व्योम)
अणु
	अगर (nvram_image == शून्य)
		वापस -ENODEV;
	वापस NVRAM_SIZE;
पूर्ण

#अगर_घोषित CONFIG_PPC32
अटल अस्थिर अचिन्हित अक्षर __iomem *nvram_addr;
अटल पूर्णांक nvram_mult;

अटल sमाप_प्रकार ppc32_nvram_size(व्योम)
अणु
	वापस NVRAM_SIZE;
पूर्ण

अटल अचिन्हित अक्षर direct_nvram_पढ़ो_byte(पूर्णांक addr)
अणु
	वापस in_8(&nvram_data[(addr & (NVRAM_SIZE - 1)) * nvram_mult]);
पूर्ण

अटल व्योम direct_nvram_ग_लिखो_byte(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	out_8(&nvram_data[(addr & (NVRAM_SIZE - 1)) * nvram_mult], val);
पूर्ण


अटल अचिन्हित अक्षर indirect_nvram_पढ़ो_byte(पूर्णांक addr)
अणु
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&nv_lock, flags);
	out_8(nvram_addr, addr >> 5);
	val = in_8(&nvram_data[(addr & 0x1f) << 4]);
	raw_spin_unlock_irqrestore(&nv_lock, flags);

	वापस val;
पूर्ण

अटल व्योम indirect_nvram_ग_लिखो_byte(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&nv_lock, flags);
	out_8(nvram_addr, addr >> 5);
	out_8(&nvram_data[(addr & 0x1f) << 4], val);
	raw_spin_unlock_irqrestore(&nv_lock, flags);
पूर्ण


#अगर_घोषित CONFIG_ADB_PMU

अटल व्योम pmu_nvram_complete(काष्ठा adb_request *req)
अणु
	अगर (req->arg)
		complete((काष्ठा completion *)req->arg);
पूर्ण

अटल अचिन्हित अक्षर pmu_nvram_पढ़ो_byte(पूर्णांक addr)
अणु
	काष्ठा adb_request req;
	DECLARE_COMPLETION_ONSTACK(req_complete);
	
	req.arg = प्रणाली_state == SYSTEM_RUNNING ? &req_complete : शून्य;
	अगर (pmu_request(&req, pmu_nvram_complete, 3, PMU_READ_NVRAM,
			(addr >> 8) & 0xff, addr & 0xff))
		वापस 0xff;
	अगर (प्रणाली_state == SYSTEM_RUNNING)
		रुको_क्रम_completion(&req_complete);
	जबतक (!req.complete)
		pmu_poll();
	वापस req.reply[0];
पूर्ण

अटल व्योम pmu_nvram_ग_लिखो_byte(पूर्णांक addr, अचिन्हित अक्षर val)
अणु
	काष्ठा adb_request req;
	DECLARE_COMPLETION_ONSTACK(req_complete);
	
	req.arg = प्रणाली_state == SYSTEM_RUNNING ? &req_complete : शून्य;
	अगर (pmu_request(&req, pmu_nvram_complete, 4, PMU_WRITE_NVRAM,
			(addr >> 8) & 0xff, addr & 0xff, val))
		वापस;
	अगर (प्रणाली_state == SYSTEM_RUNNING)
		रुको_क्रम_completion(&req_complete);
	जबतक (!req.complete)
		pmu_poll();
पूर्ण

#पूर्ण_अगर /* CONFIG_ADB_PMU */
#पूर्ण_अगर /* CONFIG_PPC32 */

अटल u8 chrp_checksum(काष्ठा chrp_header* hdr)
अणु
	u8 *ptr;
	u16 sum = hdr->signature;
	क्रम (ptr = (u8 *)&hdr->len; ptr < hdr->data; ptr++)
		sum += *ptr;
	जबतक (sum > 0xFF)
		sum = (sum & 0xFF) + (sum>>8);
	वापस sum;
पूर्ण

अटल u32 core99_calc_adler(u8 *buffer)
अणु
	पूर्णांक cnt;
	u32 low, high;

   	buffer += CORE99_ADLER_START;
	low = 1;
	high = 0;
	क्रम (cnt=0; cnt<(NVRAM_SIZE-CORE99_ADLER_START); cnt++) अणु
		अगर ((cnt % 5000) == 0) अणु
			high  %= 65521UL;
			high %= 65521UL;
		पूर्ण
		low += buffer[cnt];
		high += low;
	पूर्ण
	low  %= 65521UL;
	high %= 65521UL;

	वापस (high << 16) | low;
पूर्ण

अटल u32 core99_check(u8* datas)
अणु
	काष्ठा core99_header* hdr99 = (काष्ठा core99_header*)datas;

	अगर (hdr99->hdr.signature != CORE99_SIGNATURE) अणु
		DBG("Invalid signature\n");
		वापस 0;
	पूर्ण
	अगर (hdr99->hdr.cksum != chrp_checksum(&hdr99->hdr)) अणु
		DBG("Invalid checksum\n");
		वापस 0;
	पूर्ण
	अगर (hdr99->adler != core99_calc_adler(datas)) अणु
		DBG("Invalid adler\n");
		वापस 0;
	पूर्ण
	वापस hdr99->generation;
पूर्ण

अटल पूर्णांक sm_erase_bank(पूर्णांक bank)
अणु
	पूर्णांक stat;
	अचिन्हित दीर्घ समयout;

	u8 __iomem *base = (u8 __iomem *)nvram_data + core99_bank*NVRAM_SIZE;

       	DBG("nvram: Sharp/Micron Erasing bank %d...\n", bank);

	out_8(base, SM_FLASH_CMD_ERASE_SETUP);
	out_8(base, SM_FLASH_CMD_ERASE_CONFIRM);
	समयout = 0;
	करो अणु
		अगर (++समयout > 1000000) अणु
			prपूर्णांकk(KERN_ERR "nvram: Sharp/Micron flash erase timeout !\n");
			अवरोध;
		पूर्ण
		out_8(base, SM_FLASH_CMD_READ_STATUS);
		stat = in_8(base);
	पूर्ण जबतक (!(stat & SM_FLASH_STATUS_DONE));

	out_8(base, SM_FLASH_CMD_CLEAR_STATUS);
	out_8(base, SM_FLASH_CMD_RESET);

	अगर (स_प्रथम_inv(base, 0xff, NVRAM_SIZE)) अणु
		prपूर्णांकk(KERN_ERR "nvram: Sharp/Micron flash erase failed !\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sm_ग_लिखो_bank(पूर्णांक bank, u8* datas)
अणु
	पूर्णांक i, stat = 0;
	अचिन्हित दीर्घ समयout;

	u8 __iomem *base = (u8 __iomem *)nvram_data + core99_bank*NVRAM_SIZE;

       	DBG("nvram: Sharp/Micron Writing bank %d...\n", bank);

	क्रम (i=0; i<NVRAM_SIZE; i++) अणु
		out_8(base+i, SM_FLASH_CMD_WRITE_SETUP);
		udelay(1);
		out_8(base+i, datas[i]);
		समयout = 0;
		करो अणु
			अगर (++समयout > 1000000) अणु
				prपूर्णांकk(KERN_ERR "nvram: Sharp/Micron flash write timeout !\n");
				अवरोध;
			पूर्ण
			out_8(base, SM_FLASH_CMD_READ_STATUS);
			stat = in_8(base);
		पूर्ण जबतक (!(stat & SM_FLASH_STATUS_DONE));
		अगर (!(stat & SM_FLASH_STATUS_DONE))
			अवरोध;
	पूर्ण
	out_8(base, SM_FLASH_CMD_CLEAR_STATUS);
	out_8(base, SM_FLASH_CMD_RESET);
	अगर (स_भेद(base, datas, NVRAM_SIZE)) अणु
		prपूर्णांकk(KERN_ERR "nvram: Sharp/Micron flash write failed !\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amd_erase_bank(पूर्णांक bank)
अणु
	पूर्णांक stat = 0;
	अचिन्हित दीर्घ समयout;

	u8 __iomem *base = (u8 __iomem *)nvram_data + core99_bank*NVRAM_SIZE;

       	DBG("nvram: AMD Erasing bank %d...\n", bank);

	/* Unlock 1 */
	out_8(base+0x555, 0xaa);
	udelay(1);
	/* Unlock 2 */
	out_8(base+0x2aa, 0x55);
	udelay(1);

	/* Sector-Erase */
	out_8(base+0x555, 0x80);
	udelay(1);
	out_8(base+0x555, 0xaa);
	udelay(1);
	out_8(base+0x2aa, 0x55);
	udelay(1);
	out_8(base, 0x30);
	udelay(1);

	समयout = 0;
	करो अणु
		अगर (++समयout > 1000000) अणु
			prपूर्णांकk(KERN_ERR "nvram: AMD flash erase timeout !\n");
			अवरोध;
		पूर्ण
		stat = in_8(base) ^ in_8(base);
	पूर्ण जबतक (stat != 0);
	
	/* Reset */
	out_8(base, 0xf0);
	udelay(1);

	अगर (स_प्रथम_inv(base, 0xff, NVRAM_SIZE)) अणु
		prपूर्णांकk(KERN_ERR "nvram: AMD flash erase failed !\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amd_ग_लिखो_bank(पूर्णांक bank, u8* datas)
अणु
	पूर्णांक i, stat = 0;
	अचिन्हित दीर्घ समयout;

	u8 __iomem *base = (u8 __iomem *)nvram_data + core99_bank*NVRAM_SIZE;

       	DBG("nvram: AMD Writing bank %d...\n", bank);

	क्रम (i=0; i<NVRAM_SIZE; i++) अणु
		/* Unlock 1 */
		out_8(base+0x555, 0xaa);
		udelay(1);
		/* Unlock 2 */
		out_8(base+0x2aa, 0x55);
		udelay(1);

		/* Write single word */
		out_8(base+0x555, 0xa0);
		udelay(1);
		out_8(base+i, datas[i]);
		
		समयout = 0;
		करो अणु
			अगर (++समयout > 1000000) अणु
				prपूर्णांकk(KERN_ERR "nvram: AMD flash write timeout !\n");
				अवरोध;
			पूर्ण
			stat = in_8(base) ^ in_8(base);
		पूर्ण जबतक (stat != 0);
		अगर (stat != 0)
			अवरोध;
	पूर्ण

	/* Reset */
	out_8(base, 0xf0);
	udelay(1);

	अगर (स_भेद(base, datas, NVRAM_SIZE)) अणु
		prपूर्णांकk(KERN_ERR "nvram: AMD flash write failed !\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init lookup_partitions(व्योम)
अणु
	u8 buffer[17];
	पूर्णांक i, offset;
	काष्ठा chrp_header* hdr;

	अगर (pmac_newworld) अणु
		nvram_partitions[pmac_nvram_OF] = -1;
		nvram_partitions[pmac_nvram_XPRAM] = -1;
		nvram_partitions[pmac_nvram_NR] = -1;
		hdr = (काष्ठा chrp_header *)buffer;

		offset = 0;
		buffer[16] = 0;
		करो अणु
			क्रम (i=0;i<16;i++)
				buffer[i] = ppc_md.nvram_पढ़ो_val(offset+i);
			अगर (!म_भेद(hdr->name, "common"))
				nvram_partitions[pmac_nvram_OF] = offset + 0x10;
			अगर (!म_भेद(hdr->name, "APL,MacOS75")) अणु
				nvram_partitions[pmac_nvram_XPRAM] = offset + 0x10;
				nvram_partitions[pmac_nvram_NR] = offset + 0x110;
			पूर्ण
			offset += (hdr->len * 0x10);
		पूर्ण जबतक(offset < NVRAM_SIZE);
	पूर्ण अन्यथा अणु
		nvram_partitions[pmac_nvram_OF] = 0x1800;
		nvram_partitions[pmac_nvram_XPRAM] = 0x1300;
		nvram_partitions[pmac_nvram_NR] = 0x1400;
	पूर्ण
	DBG("nvram: OF partition at 0x%x\n", nvram_partitions[pmac_nvram_OF]);
	DBG("nvram: XP partition at 0x%x\n", nvram_partitions[pmac_nvram_XPRAM]);
	DBG("nvram: NR partition at 0x%x\n", nvram_partitions[pmac_nvram_NR]);
पूर्ण

अटल व्योम core99_nvram_sync(व्योम)
अणु
	काष्ठा core99_header* hdr99;
	अचिन्हित दीर्घ flags;

	अगर (!is_core_99 || !nvram_data || !nvram_image)
		वापस;

	raw_spin_lock_irqsave(&nv_lock, flags);
	अगर (!स_भेद(nvram_image, (u8*)nvram_data + core99_bank*NVRAM_SIZE,
		NVRAM_SIZE))
		जाओ bail;

	DBG("Updating nvram...\n");

	hdr99 = (काष्ठा core99_header*)nvram_image;
	hdr99->generation++;
	hdr99->hdr.signature = CORE99_SIGNATURE;
	hdr99->hdr.cksum = chrp_checksum(&hdr99->hdr);
	hdr99->adler = core99_calc_adler(nvram_image);
	core99_bank = core99_bank ? 0 : 1;
	अगर (core99_erase_bank)
		अगर (core99_erase_bank(core99_bank)) अणु
			prपूर्णांकk("nvram: Error erasing bank %d\n", core99_bank);
			जाओ bail;
		पूर्ण
	अगर (core99_ग_लिखो_bank)
		अगर (core99_ग_लिखो_bank(core99_bank, nvram_image))
			prपूर्णांकk("nvram: Error writing bank %d\n", core99_bank);
 bail:
	raw_spin_unlock_irqrestore(&nv_lock, flags);

#अगर_घोषित DEBUG
       	mdelay(2000);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init core99_nvram_setup(काष्ठा device_node *dp, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;
	u32 gen_bank0, gen_bank1;

	अगर (nvram_naddrs < 1) अणु
		prपूर्णांकk(KERN_ERR "nvram: no address\n");
		वापस -EINVAL;
	पूर्ण
	nvram_image = memblock_alloc(NVRAM_SIZE, SMP_CACHE_BYTES);
	अगर (!nvram_image)
		panic("%s: Failed to allocate %u bytes\n", __func__,
		      NVRAM_SIZE);
	nvram_data = ioremap(addr, NVRAM_SIZE*2);
	nvram_naddrs = 1; /* Make sure we get the correct हाल */

	DBG("nvram: Checking bank 0...\n");

	gen_bank0 = core99_check((u8 *)nvram_data);
	gen_bank1 = core99_check((u8 *)nvram_data + NVRAM_SIZE);
	core99_bank = (gen_bank0 < gen_bank1) ? 1 : 0;

	DBG("nvram: gen0=%d, gen1=%d\n", gen_bank0, gen_bank1);
	DBG("nvram: Active bank is: %d\n", core99_bank);

	क्रम (i=0; i<NVRAM_SIZE; i++)
		nvram_image[i] = nvram_data[i + core99_bank*NVRAM_SIZE];

	ppc_md.nvram_पढ़ो_val	= core99_nvram_पढ़ो_byte;
	ppc_md.nvram_ग_लिखो_val	= core99_nvram_ग_लिखो_byte;
	ppc_md.nvram_पढ़ो	= core99_nvram_पढ़ो;
	ppc_md.nvram_ग_लिखो	= core99_nvram_ग_लिखो;
	ppc_md.nvram_size	= core99_nvram_size;
	ppc_md.nvram_sync	= core99_nvram_sync;
	ppc_md.machine_shutकरोwn	= core99_nvram_sync;
	/* 
	 * Maybe we could be smarter here though making an exclusive list
	 * of known flash chips is a bit nasty as older OF didn't provide us
	 * with a useful "compatible" entry. A solution would be to really
	 * identअगरy the chip using flash id commands and base ourselves on
	 * a list of known chips IDs
	 */
	अगर (of_device_is_compatible(dp, "amd-0137")) अणु
		core99_erase_bank = amd_erase_bank;
		core99_ग_लिखो_bank = amd_ग_लिखो_bank;
	पूर्ण अन्यथा अणु
		core99_erase_bank = sm_erase_bank;
		core99_ग_लिखो_bank = sm_ग_लिखो_bank;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init pmac_nvram_init(व्योम)
अणु
	काष्ठा device_node *dp;
	काष्ठा resource r1, r2;
	अचिन्हित पूर्णांक s1 = 0, s2 = 0;
	पूर्णांक err = 0;

	nvram_naddrs = 0;

	dp = of_find_node_by_name(शून्य, "nvram");
	अगर (dp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Can't find NVRAM device\n");
		वापस -ENODEV;
	पूर्ण

	/* Try to obtain an address */
	अगर (of_address_to_resource(dp, 0, &r1) == 0) अणु
		nvram_naddrs = 1;
		s1 = resource_size(&r1);
		अगर (of_address_to_resource(dp, 1, &r2) == 0) अणु
			nvram_naddrs = 2;
			s2 = resource_size(&r2);
		पूर्ण
	पूर्ण

	is_core_99 = of_device_is_compatible(dp, "nvram,flash");
	अगर (is_core_99) अणु
		err = core99_nvram_setup(dp, r1.start);
		जाओ bail;
	पूर्ण

#अगर_घोषित CONFIG_PPC32
	अगर (machine_is(chrp) && nvram_naddrs == 1) अणु
		nvram_data = ioremap(r1.start, s1);
		nvram_mult = 1;
		ppc_md.nvram_पढ़ो_val	= direct_nvram_पढ़ो_byte;
		ppc_md.nvram_ग_लिखो_val	= direct_nvram_ग_लिखो_byte;
		ppc_md.nvram_size	= ppc32_nvram_size;
	पूर्ण अन्यथा अगर (nvram_naddrs == 1) अणु
		nvram_data = ioremap(r1.start, s1);
		nvram_mult = (s1 + NVRAM_SIZE - 1) / NVRAM_SIZE;
		ppc_md.nvram_पढ़ो_val	= direct_nvram_पढ़ो_byte;
		ppc_md.nvram_ग_लिखो_val	= direct_nvram_ग_लिखो_byte;
		ppc_md.nvram_size	= ppc32_nvram_size;
	पूर्ण अन्यथा अगर (nvram_naddrs == 2) अणु
		nvram_addr = ioremap(r1.start, s1);
		nvram_data = ioremap(r2.start, s2);
		ppc_md.nvram_पढ़ो_val	= indirect_nvram_पढ़ो_byte;
		ppc_md.nvram_ग_लिखो_val	= indirect_nvram_ग_लिखो_byte;
		ppc_md.nvram_size	= ppc32_nvram_size;
	पूर्ण अन्यथा अगर (nvram_naddrs == 0 && sys_ctrler == SYS_CTRLER_PMU) अणु
#अगर_घोषित CONFIG_ADB_PMU
		nvram_naddrs = -1;
		ppc_md.nvram_पढ़ो_val	= pmu_nvram_पढ़ो_byte;
		ppc_md.nvram_ग_लिखो_val	= pmu_nvram_ग_लिखो_byte;
		ppc_md.nvram_size	= ppc32_nvram_size;
#पूर्ण_अगर /* CONFIG_ADB_PMU */
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Incompatible type of NVRAM\n");
		err = -ENXIO;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */
bail:
	of_node_put(dp);
	अगर (err == 0)
		lookup_partitions();
	वापस err;
पूर्ण

पूर्णांक pmac_get_partition(पूर्णांक partition)
अणु
	वापस nvram_partitions[partition];
पूर्ण

u8 pmac_xpram_पढ़ो(पूर्णांक xpaddr)
अणु
	पूर्णांक offset = pmac_get_partition(pmac_nvram_XPRAM);

	अगर (offset < 0 || xpaddr < 0 || xpaddr > 0x100)
		वापस 0xff;

	वापस ppc_md.nvram_पढ़ो_val(xpaddr + offset);
पूर्ण

व्योम pmac_xpram_ग_लिखो(पूर्णांक xpaddr, u8 data)
अणु
	पूर्णांक offset = pmac_get_partition(pmac_nvram_XPRAM);

	अगर (offset < 0 || xpaddr < 0 || xpaddr > 0x100)
		वापस;

	ppc_md.nvram_ग_लिखो_val(xpaddr + offset, data);
पूर्ण

EXPORT_SYMBOL(pmac_get_partition);
EXPORT_SYMBOL(pmac_xpram_पढ़ो);
EXPORT_SYMBOL(pmac_xpram_ग_लिखो);
