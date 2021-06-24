<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * ChipCommon serial flash पूर्णांकerface
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>

अटल काष्ठा resource ssb_sflash_resource = अणु
	.name	= "ssb_sflash",
	.start	= SSB_FLASH2,
	.end	= 0,
	.flags  = IORESOURCE_MEM | IORESOURCE_READONLY,
पूर्ण;

काष्ठा platक्रमm_device ssb_sflash_dev = अणु
	.name		= "ssb_sflash",
	.resource	= &ssb_sflash_resource,
	.num_resources	= 1,
पूर्ण;

काष्ठा ssb_sflash_tbl_e अणु
	अक्षर *name;
	u32 id;
	u32 blocksize;
	u16 numblocks;
पूर्ण;

अटल स्थिर काष्ठा ssb_sflash_tbl_e ssb_sflash_st_tbl[] = अणु
	अणु "M25P20", 0x11, 0x10000, 4, पूर्ण,
	अणु "M25P40", 0x12, 0x10000, 8, पूर्ण,

	अणु "M25P16", 0x14, 0x10000, 32, पूर्ण,
	अणु "M25P32", 0x15, 0x10000, 64, पूर्ण,
	अणु "M25P64", 0x16, 0x10000, 128, पूर्ण,
	अणु "M25FL128", 0x17, 0x10000, 256, पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ssb_sflash_tbl_e ssb_sflash_sst_tbl[] = अणु
	अणु "SST25WF512", 1, 0x1000, 16, पूर्ण,
	अणु "SST25VF512", 0x48, 0x1000, 16, पूर्ण,
	अणु "SST25WF010", 2, 0x1000, 32, पूर्ण,
	अणु "SST25VF010", 0x49, 0x1000, 32, पूर्ण,
	अणु "SST25WF020", 3, 0x1000, 64, पूर्ण,
	अणु "SST25VF020", 0x43, 0x1000, 64, पूर्ण,
	अणु "SST25WF040", 4, 0x1000, 128, पूर्ण,
	अणु "SST25VF040", 0x44, 0x1000, 128, पूर्ण,
	अणु "SST25VF040B", 0x8d, 0x1000, 128, पूर्ण,
	अणु "SST25WF080", 5, 0x1000, 256, पूर्ण,
	अणु "SST25VF080B", 0x8e, 0x1000, 256, पूर्ण,
	अणु "SST25VF016", 0x41, 0x1000, 512, पूर्ण,
	अणु "SST25VF032", 0x4a, 0x1000, 1024, पूर्ण,
	अणु "SST25VF064", 0x4b, 0x1000, 2048, पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ssb_sflash_tbl_e ssb_sflash_at_tbl[] = अणु
	अणु "AT45DB011", 0xc, 256, 512, पूर्ण,
	अणु "AT45DB021", 0x14, 256, 1024, पूर्ण,
	अणु "AT45DB041", 0x1c, 256, 2048, पूर्ण,
	अणु "AT45DB081", 0x24, 256, 4096, पूर्ण,
	अणु "AT45DB161", 0x2c, 512, 4096, पूर्ण,
	अणु "AT45DB321", 0x34, 512, 8192, पूर्ण,
	अणु "AT45DB642", 0x3c, 1024, 8192, पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल व्योम ssb_sflash_cmd(काष्ठा ssb_chipcommon *cc, u32 opcode)
अणु
	पूर्णांक i;
	chipco_ग_लिखो32(cc, SSB_CHIPCO_FLASHCTL,
		       SSB_CHIPCO_FLASHCTL_START | opcode);
	क्रम (i = 0; i < 1000; i++) अणु
		अगर (!(chipco_पढ़ो32(cc, SSB_CHIPCO_FLASHCTL) &
		      SSB_CHIPCO_FLASHCTL_BUSY))
			वापस;
		cpu_relax();
	पूर्ण
	dev_err(cc->dev->dev, "SFLASH control command failed (timeout)!\n");
पूर्ण

/* Initialize serial flash access */
पूर्णांक ssb_sflash_init(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_sflash *sflash = &cc->dev->bus->mipscore.sflash;
	स्थिर काष्ठा ssb_sflash_tbl_e *e;
	u32 id, id2;

	चयन (cc->capabilities & SSB_CHIPCO_CAP_FLASHT) अणु
	हाल SSB_CHIPCO_FLASHT_STSER:
		ssb_sflash_cmd(cc, SSB_CHIPCO_FLASHCTL_ST_DP);

		chipco_ग_लिखो32(cc, SSB_CHIPCO_FLASHADDR, 0);
		ssb_sflash_cmd(cc, SSB_CHIPCO_FLASHCTL_ST_RES);
		id = chipco_पढ़ो32(cc, SSB_CHIPCO_FLASHDATA);

		chipco_ग_लिखो32(cc, SSB_CHIPCO_FLASHADDR, 1);
		ssb_sflash_cmd(cc, SSB_CHIPCO_FLASHCTL_ST_RES);
		id2 = chipco_पढ़ो32(cc, SSB_CHIPCO_FLASHDATA);

		चयन (id) अणु
		हाल 0xbf:
			क्रम (e = ssb_sflash_sst_tbl; e->name; e++) अणु
				अगर (e->id == id2)
					अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x13:
			वापस -ENOTSUPP;
		शेष:
			क्रम (e = ssb_sflash_st_tbl; e->name; e++) अणु
				अगर (e->id == id)
					अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (!e->name) अणु
			pr_err("Unsupported ST serial flash (id: 0x%X, id2: 0x%X)\n",
			       id, id2);
			वापस -ENOTSUPP;
		पूर्ण

		अवरोध;
	हाल SSB_CHIPCO_FLASHT_ATSER:
		ssb_sflash_cmd(cc, SSB_CHIPCO_FLASHCTL_AT_STATUS);
		id = chipco_पढ़ो32(cc, SSB_CHIPCO_FLASHDATA) & 0x3c;

		क्रम (e = ssb_sflash_at_tbl; e->name; e++) अणु
			अगर (e->id == id)
				अवरोध;
		पूर्ण
		अगर (!e->name) अणु
			pr_err("Unsupported Atmel serial flash (id: 0x%X)\n",
			       id);
			वापस -ENOTSUPP;
		पूर्ण

		अवरोध;
	शेष:
		pr_err("Unsupported flash type\n");
		वापस -ENOTSUPP;
	पूर्ण

	sflash->winकरोw = SSB_FLASH2;
	sflash->blocksize = e->blocksize;
	sflash->numblocks = e->numblocks;
	sflash->size = sflash->blocksize * sflash->numblocks;
	sflash->present = true;

	pr_info("Found %s serial flash (size: %dKiB, blocksize: 0x%X, blocks: %d)\n",
		e->name, sflash->size / 1024, e->blocksize, e->numblocks);

	/* Prepare platक्रमm device, but करोn't register it yet. It's too early,
	 * दो_स्मृति (required by device_निजी_init) is not available yet. */
	ssb_sflash_dev.resource[0].end = ssb_sflash_dev.resource[0].start +
					 sflash->size;
	ssb_sflash_dev.dev.platक्रमm_data = sflash;

	वापस 0;
पूर्ण
