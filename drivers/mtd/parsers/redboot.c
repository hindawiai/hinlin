<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Parse RedBoot-style Flash Image System (FIS) tables and
 * produce a Linux partition array to match.
 *
 * Copyright तऊ 2001      Red Hat UK Limited
 * Copyright तऊ 2001-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/module.h>

काष्ठा fis_image_desc अणु
    अचिन्हित अक्षर name[16];      // Null terminated name
    uपूर्णांक32_t	  flash_base;    // Address within FLASH of image
    uपूर्णांक32_t	  mem_base;      // Address in memory where it executes
    uपूर्णांक32_t	  size;          // Length of image
    uपूर्णांक32_t	  entry_poपूर्णांक;   // Execution entry poपूर्णांक
    uपूर्णांक32_t	  data_length;   // Length of actual data
    अचिन्हित अक्षर _pad[256-(16+7*माप(uपूर्णांक32_t))];
    uपूर्णांक32_t	  desc_cksum;    // Checksum over image descriptor
    uपूर्णांक32_t	  file_cksum;    // Checksum over image data
पूर्ण;

काष्ठा fis_list अणु
	काष्ठा fis_image_desc *img;
	काष्ठा fis_list *next;
पूर्ण;

अटल पूर्णांक directory = CONFIG_MTD_REDBOOT_सूचीECTORY_BLOCK;
module_param(directory, पूर्णांक, 0);

अटल अंतरभूत पूर्णांक redboot_checksum(काष्ठा fis_image_desc *img)
अणु
	/* RedBoot करोesn't actually ग_लिखो the desc_cksum field yet AFAICT */
	वापस 1;
पूर्ण

अटल व्योम parse_redboot_of(काष्ठा mtd_info *master)
अणु
	काष्ठा device_node *np;
	u32 dirblock;
	पूर्णांक ret;

	np = mtd_get_of_node(master);
	अगर (!np)
		वापस;

	ret = of_property_पढ़ो_u32(np, "fis-index-block", &dirblock);
	अगर (ret)
		वापस;

	/*
	 * Assign the block found in the device tree to the local
	 * directory block poपूर्णांकer.
	 */
	directory = dirblock;
पूर्ण

अटल पूर्णांक parse_redboot_partitions(काष्ठा mtd_info *master,
				    स्थिर काष्ठा mtd_partition **pparts,
				    काष्ठा mtd_part_parser_data *data)
अणु
	पूर्णांक nrparts = 0;
	काष्ठा fis_image_desc *buf;
	काष्ठा mtd_partition *parts;
	काष्ठा fis_list *fl = शून्य, *पंचांगp_fl;
	पूर्णांक ret, i;
	माप_प्रकार retlen;
	अक्षर *names;
	अक्षर *nullname;
	पूर्णांक namelen = 0;
	पूर्णांक nulllen = 0;
	पूर्णांक numslots;
	अचिन्हित दीर्घ offset;
#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_UNALLOCATED
	अटल अक्षर nullstring[] = "unallocated";
#पूर्ण_अगर

	parse_redboot_of(master);

	अगर ( directory < 0 ) अणु
		offset = master->size + directory * master->erasesize;
		जबतक (mtd_block_isbad(master, offset)) अणु
			अगर (!offset) अणु
			nogood:
				prपूर्णांकk(KERN_NOTICE "Failed to find a non-bad block to check for RedBoot partition table\n");
				वापस -EIO;
			पूर्ण
			offset -= master->erasesize;
		पूर्ण
	पूर्ण अन्यथा अणु
		offset = directory * master->erasesize;
		जबतक (mtd_block_isbad(master, offset)) अणु
			offset += master->erasesize;
			अगर (offset == master->size)
				जाओ nogood;
		पूर्ण
	पूर्ण
	buf = vदो_स्मृति(master->erasesize);

	अगर (!buf)
		वापस -ENOMEM;

	prपूर्णांकk(KERN_NOTICE "Searching for RedBoot partition table in %s at offset 0x%lx\n",
	       master->name, offset);

	ret = mtd_पढ़ो(master, offset, master->erasesize, &retlen,
		       (व्योम *)buf);

	अगर (ret)
		जाओ out;

	अगर (retlen != master->erasesize) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	numslots = (master->erasesize / माप(काष्ठा fis_image_desc));
	क्रम (i = 0; i < numslots; i++) अणु
		अगर (!स_भेद(buf[i].name, "FIS directory", 14)) अणु
			/* This is apparently the FIS directory entry क्रम the
			 * FIS directory itself.  The FIS directory size is
			 * one erase block; अगर the buf[i].size field is
			 * swab32(erasesize) then we know we are looking at
			 * a byte swapped FIS directory - swap all the entries!
			 * (NOTE: this is 'size' not 'data_length'; size is
			 * the full size of the entry.)
			 */

			/* RedBoot can combine the FIS directory and
			   config partitions पूर्णांकo a single eraseblock;
			   we assume wrong-endian अगर either the swapped
			   'size' matches the eraseblock size precisely,
			   or अगर the swapped size actually fits in an
			   eraseblock जबतक the unswapped size करोesn't. */
			अगर (swab32(buf[i].size) == master->erasesize ||
			    (buf[i].size > master->erasesize
			     && swab32(buf[i].size) < master->erasesize)) अणु
				पूर्णांक j;
				/* Update numslots based on actual FIS directory size */
				numslots = swab32(buf[i].size) / माप (काष्ठा fis_image_desc);
				क्रम (j = 0; j < numslots; ++j) अणु

					/* A single 0xff denotes a deleted entry.
					 * Two of them in a row is the end of the table.
					 */
					अगर (buf[j].name[0] == 0xff) अणु
				  		अगर (buf[j].name[1] == 0xff) अणु
							अवरोध;
						पूर्ण अन्यथा अणु
							जारी;
						पूर्ण
					पूर्ण

					/* The अचिन्हित दीर्घ fields were written with the
					 * wrong byte sex, name and pad have no byte sex.
					 */
					swab32s(&buf[j].flash_base);
					swab32s(&buf[j].mem_base);
					swab32s(&buf[j].size);
					swab32s(&buf[j].entry_poपूर्णांक);
					swab32s(&buf[j].data_length);
					swab32s(&buf[j].desc_cksum);
					swab32s(&buf[j].file_cksum);
				पूर्ण
			पूर्ण अन्यथा अगर (buf[i].size < master->erasesize) अणु
				/* Update numslots based on actual FIS directory size */
				numslots = buf[i].size / माप(काष्ठा fis_image_desc);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == numslots) अणु
		/* Didn't find it */
		prपूर्णांकk(KERN_NOTICE "No RedBoot partition table detected in %s\n",
		       master->name);
		ret = 0;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < numslots; i++) अणु
		काष्ठा fis_list *new_fl, **prev;

		अगर (buf[i].name[0] == 0xff) अणु
			अगर (buf[i].name[1] == 0xff) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				जारी;
			पूर्ण
		पूर्ण
		अगर (!redboot_checksum(&buf[i]))
			अवरोध;

		new_fl = kदो_स्मृति(माप(काष्ठा fis_list), GFP_KERNEL);
		namelen += म_माप(buf[i].name)+1;
		अगर (!new_fl) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		new_fl->img = &buf[i];
		अगर (data && data->origin)
			buf[i].flash_base -= data->origin;
		अन्यथा
			buf[i].flash_base &= master->size-1;

		/* I'm sure the JFFS2 code has करोne me permanent damage.
		 * I now think the following is _normal_
		 */
		prev = &fl;
		जबतक(*prev && (*prev)->img->flash_base < new_fl->img->flash_base)
			prev = &(*prev)->next;
		new_fl->next = *prev;
		*prev = new_fl;

		nrparts++;
	पूर्ण
#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_UNALLOCATED
	अगर (fl->img->flash_base) अणु
		nrparts++;
		nulllen = माप(nullstring);
	पूर्ण

	क्रम (पंचांगp_fl = fl; पंचांगp_fl->next; पंचांगp_fl = पंचांगp_fl->next) अणु
		अगर (पंचांगp_fl->img->flash_base + पंचांगp_fl->img->size + master->erasesize <= पंचांगp_fl->next->img->flash_base) अणु
			nrparts++;
			nulllen = माप(nullstring);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	parts = kzalloc(माप(*parts)*nrparts + nulllen + namelen, GFP_KERNEL);

	अगर (!parts) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	nullname = (अक्षर *)&parts[nrparts];
#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_UNALLOCATED
	अगर (nulllen > 0) अणु
		म_नकल(nullname, nullstring);
	पूर्ण
#पूर्ण_अगर
	names = nullname + nulllen;

	i=0;

#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_UNALLOCATED
	अगर (fl->img->flash_base) अणु
	       parts[0].name = nullname;
	       parts[0].size = fl->img->flash_base;
	       parts[0].offset = 0;
		i++;
	पूर्ण
#पूर्ण_अगर
	क्रम ( ; i<nrparts; i++) अणु
		parts[i].size = fl->img->size;
		parts[i].offset = fl->img->flash_base;
		parts[i].name = names;

		म_नकल(names, fl->img->name);
#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_READONLY
		अगर (!स_भेद(names, "RedBoot", 8) ||
				!स_भेद(names, "RedBoot config", 15) ||
				!स_भेद(names, "FIS directory", 14)) अणु
			parts[i].mask_flags = MTD_WRITEABLE;
		पूर्ण
#पूर्ण_अगर
		names += म_माप(names)+1;

#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS_UNALLOCATED
		अगर(fl->next && fl->img->flash_base + fl->img->size + master->erasesize <= fl->next->img->flash_base) अणु
			i++;
			parts[i].offset = parts[i-1].size + parts[i-1].offset;
			parts[i].size = fl->next->img->flash_base - parts[i].offset;
			parts[i].name = nullname;
		पूर्ण
#पूर्ण_अगर
		पंचांगp_fl = fl;
		fl = fl->next;
		kमुक्त(पंचांगp_fl);
	पूर्ण
	ret = nrparts;
	*pparts = parts;
 out:
	जबतक (fl) अणु
		काष्ठा fis_list *old = fl;
		fl = fl->next;
		kमुक्त(old);
	पूर्ण
	vमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtd_parser_redboot_of_match_table[] = अणु
	अणु .compatible = "redboot-fis" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtd_parser_redboot_of_match_table);

अटल काष्ठा mtd_part_parser redboot_parser = अणु
	.parse_fn = parse_redboot_partitions,
	.name = "RedBoot",
	.of_match_table = mtd_parser_redboot_of_match_table,
पूर्ण;
module_mtd_part_parser(redboot_parser);

/* mtd parsers will request the module by parser name */
MODULE_ALIAS("RedBoot");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Parsing code for RedBoot Flash Image System (FIS) tables");
