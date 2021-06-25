<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Probing flash chips with QINFO records.
 * (C) 2008 Korolev Alexey <akorolev@infradead.org>
 * (C) 2008 Vasiliy Leonenko <vasiliy.leonenko@gmail.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mtd/xip.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/pfow.h>
#समावेश <linux/mtd/qinfo.h>

अटल पूर्णांक lpddr_chip_setup(काष्ठा map_info *map, काष्ठा lpddr_निजी *lpddr);
काष्ठा mtd_info *lpddr_probe(काष्ठा map_info *map);
अटल काष्ठा lpddr_निजी *lpddr_probe_chip(काष्ठा map_info *map);
अटल पूर्णांक lpddr_pfow_present(काष्ठा map_info *map,
			काष्ठा lpddr_निजी *lpddr);

अटल काष्ठा qinfo_query_info qinfo_array[] = अणु
	/* General device info */
	अणु0, 0, "DevSizeShift", "Device size 2^n bytes"पूर्ण,
	अणु0, 3, "BufSizeShift", "Program buffer size 2^n bytes"पूर्ण,
	/* Erase block inक्रमmation */
	अणु1, 1, "TotalBlocksNum", "Total number of blocks"पूर्ण,
	अणु1, 2, "UniformBlockSizeShift", "Unअगरorm block size 2^n bytes"पूर्ण,
	/* Partition inक्रमmation */
	अणु2, 1, "HWPartsNum", "Number of hardware partitions"पूर्ण,
	/* Optional features */
	अणु5, 1, "SuspEraseSupp", "Suspend erase supported"पूर्ण,
	/* Operation typical समय */
	अणु10, 0, "SingleWordProgTime", "Single word program 2^n u-sec"पूर्ण,
	अणु10, 1, "ProgBufferTime", "Program buffer ग_लिखो 2^n u-sec"पूर्ण,
	अणु10, 2, "BlockEraseTime", "Block erase 2^n m-sec"पूर्ण,
	अणु10, 3, "FullChipEraseTime", "Full chip erase 2^n m-sec"पूर्ण,
पूर्ण;

अटल दीर्घ lpddr_get_qinक्रमec_pos(काष्ठा map_info *map, अक्षर *id_str)
अणु
	पूर्णांक qinfo_lines = ARRAY_SIZE(qinfo_array);
	पूर्णांक i;
	पूर्णांक bankwidth = map_bankwidth(map) * 8;
	पूर्णांक major, minor;

	क्रम (i = 0; i < qinfo_lines; i++) अणु
		अगर (म_भेद(id_str, qinfo_array[i].id_str) == 0) अणु
			major = qinfo_array[i].major & ((1 << bankwidth) - 1);
			minor = qinfo_array[i].minor & ((1 << bankwidth) - 1);
			वापस minor | (major << bankwidth);
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_ERR"%s qinfo id string is wrong! \n", map->name);
	BUG();
	वापस -1;
पूर्ण

अटल uपूर्णांक16_t lpddr_info_query(काष्ठा map_info *map, अक्षर *id_str)
अणु
	अचिन्हित पूर्णांक dsr, val;
	पूर्णांक bits_per_chip = map_bankwidth(map) * 8;
	अचिन्हित दीर्घ adr = lpddr_get_qinक्रमec_pos(map, id_str);
	पूर्णांक attempts = 20;

	/* Write a request क्रम the PFOW record */
	map_ग_लिखो(map, CMD(LPDDR_INFO_QUERY),
			map->pfow_base + PFOW_COMMAND_CODE);
	map_ग_लिखो(map, CMD(adr & ((1 << bits_per_chip) - 1)),
			map->pfow_base + PFOW_COMMAND_ADDRESS_L);
	map_ग_लिखो(map, CMD(adr >> bits_per_chip),
			map->pfow_base + PFOW_COMMAND_ADDRESS_H);
	map_ग_लिखो(map, CMD(LPDDR_START_EXECUTION),
			map->pfow_base + PFOW_COMMAND_EXECUTE);

	जबतक ((attempts--) > 0) अणु
		dsr = CMDVAL(map_पढ़ो(map, map->pfow_base + PFOW_DSR));
		अगर (dsr & DSR_READY_STATUS)
			अवरोध;
		udelay(10);
	पूर्ण

	val = CMDVAL(map_पढ़ो(map, map->pfow_base + PFOW_COMMAND_DATA));
	वापस val;
पूर्ण

अटल पूर्णांक lpddr_pfow_present(काष्ठा map_info *map, काष्ठा lpddr_निजी *lpddr)
अणु
	map_word pfow_val[4];

	/* Check identअगरication string */
	pfow_val[0] = map_पढ़ो(map, map->pfow_base + PFOW_QUERY_STRING_P);
	pfow_val[1] = map_पढ़ो(map, map->pfow_base + PFOW_QUERY_STRING_F);
	pfow_val[2] = map_पढ़ो(map, map->pfow_base + PFOW_QUERY_STRING_O);
	pfow_val[3] = map_पढ़ो(map, map->pfow_base + PFOW_QUERY_STRING_W);

	अगर (!map_word_equal(map, CMD('P'), pfow_val[0]))
		जाओ out;

	अगर (!map_word_equal(map, CMD('F'), pfow_val[1]))
		जाओ out;

	अगर (!map_word_equal(map, CMD('O'), pfow_val[2]))
		जाओ out;

	अगर (!map_word_equal(map, CMD('W'), pfow_val[3]))
		जाओ out;

	वापस 1;	/* "PFOW" is found */
out:
	prपूर्णांकk(KERN_WARNING"%s: PFOW string at 0x%lx is not found \n",
					map->name, map->pfow_base);
	वापस 0;
पूर्ण

अटल पूर्णांक lpddr_chip_setup(काष्ठा map_info *map, काष्ठा lpddr_निजी *lpddr)
अणु

	lpddr->qinfo = kzalloc(माप(काष्ठा qinfo_chip), GFP_KERNEL);
	अगर (!lpddr->qinfo)
		वापस 0;

	/* Get the ManuID */
	lpddr->ManufactId = CMDVAL(map_पढ़ो(map, map->pfow_base + PFOW_MANUFACTURER_ID));
	/* Get the DeviceID */
	lpddr->DevId = CMDVAL(map_पढ़ो(map, map->pfow_base + PFOW_DEVICE_ID));
	/* पढ़ो parameters from chip qinfo table */
	lpddr->qinfo->DevSizeShअगरt = lpddr_info_query(map, "DevSizeShift");
	lpddr->qinfo->TotalBlocksNum = lpddr_info_query(map, "TotalBlocksNum");
	lpddr->qinfo->BufSizeShअगरt = lpddr_info_query(map, "BufSizeShift");
	lpddr->qinfo->HWPartsNum = lpddr_info_query(map, "HWPartsNum");
	lpddr->qinfo->UnअगरormBlockSizeShअगरt =
				lpddr_info_query(map, "UniformBlockSizeShift");
	lpddr->qinfo->SuspEraseSupp = lpddr_info_query(map, "SuspEraseSupp");
	lpddr->qinfo->SingleWordProgTime =
				lpddr_info_query(map, "SingleWordProgTime");
	lpddr->qinfo->ProgBufferTime = lpddr_info_query(map, "ProgBufferTime");
	lpddr->qinfo->BlockEraseTime = lpddr_info_query(map, "BlockEraseTime");
	वापस 1;
पूर्ण
अटल काष्ठा lpddr_निजी *lpddr_probe_chip(काष्ठा map_info *map)
अणु
	काष्ठा lpddr_निजी lpddr;
	काष्ठा lpddr_निजी *retlpddr;
	पूर्णांक numvirtchips;


	अगर ((map->pfow_base + 0x1000) >= map->size) अणु
		prपूर्णांकk(KERN_NOTICE"%s Probe at base (0x%08lx) past the end of"
				"the map(0x%08lx)\n", map->name,
				(अचिन्हित दीर्घ)map->pfow_base, map->size - 1);
		वापस शून्य;
	पूर्ण
	स_रखो(&lpddr, 0, माप(काष्ठा lpddr_निजी));
	अगर (!lpddr_pfow_present(map, &lpddr))
		वापस शून्य;

	अगर (!lpddr_chip_setup(map, &lpddr))
		वापस शून्य;

	/* Ok so we found a chip */
	lpddr.chipshअगरt = lpddr.qinfo->DevSizeShअगरt;
	lpddr.numchips = 1;

	numvirtchips = lpddr.numchips * lpddr.qinfo->HWPartsNum;
	retlpddr = kzalloc(काष्ठा_size(retlpddr, chips, numvirtchips),
			   GFP_KERNEL);
	अगर (!retlpddr)
		वापस शून्य;

	स_नकल(retlpddr, &lpddr, माप(काष्ठा lpddr_निजी));

	retlpddr->numchips = numvirtchips;
	retlpddr->chipshअगरt = retlpddr->qinfo->DevSizeShअगरt -
				__ffs(retlpddr->qinfo->HWPartsNum);

	वापस retlpddr;
पूर्ण

काष्ठा mtd_info *lpddr_probe(काष्ठा map_info *map)
अणु
	काष्ठा mtd_info *mtd = शून्य;
	काष्ठा lpddr_निजी *lpddr;

	/* First probe the map to see अगर we havecan खोलो PFOW here */
	lpddr = lpddr_probe_chip(map);
	अगर (!lpddr)
		वापस शून्य;

	map->fldrv_priv = lpddr;
	mtd = lpddr_cmdset(map);
	अगर (mtd) अणु
		अगर (mtd->size > map->size) अणु
			prपूर्णांकk(KERN_WARNING "Reducing visibility of %ldKiB chip"
				"to %ldKiB\n", (अचिन्हित दीर्घ)mtd->size >> 10,
				(अचिन्हित दीर्घ)map->size >> 10);
			mtd->size = map->size;
		पूर्ण
		वापस mtd;
	पूर्ण

	kमुक्त(lpddr->qinfo);
	kमुक्त(lpddr);
	map->fldrv_priv = शून्य;
	वापस शून्य;
पूर्ण

अटल काष्ठा mtd_chip_driver lpddr_chipdrv = अणु
	.probe		= lpddr_probe,
	.name		= "qinfo_probe",
	.module		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init lpddr_probe_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&lpddr_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास lpddr_probe_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&lpddr_chipdrv);
पूर्ण

module_init(lpddr_probe_init);
module_निकास(lpddr_probe_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vasiliy Leonenko <vasiliy.leonenko@gmail.com>");
MODULE_DESCRIPTION("Driver to probe qinfo flash chips");

