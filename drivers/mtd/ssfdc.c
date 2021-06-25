<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux driver क्रम SSFDC Flash Translation Layer (Read only)
 * तऊ 2005 Eptar srl
 * Author: Claudio Lanconelli <lanconelli.claudio@eptar.com>
 *
 * Based on NTFL and MTDBLOCK_RO drivers
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/blktrans.h>

काष्ठा ssfdcr_record अणु
	काष्ठा mtd_blktrans_dev mbd;
	पूर्णांक usecount;
	अचिन्हित अक्षर heads;
	अचिन्हित अक्षर sectors;
	अचिन्हित लघु cylinders;
	पूर्णांक cis_block;			/* block n. containing CIS/IDI */
	पूर्णांक erase_size;			/* phys_block_size */
	अचिन्हित लघु *logic_block_map; /* all zones (max 8192 phys blocks on
					    the 128MiB) */
	पूर्णांक map_len;			/* n. phys_blocks on the card */
पूर्ण;

#घोषणा SSFDCR_MAJOR		257
#घोषणा SSFDCR_PARTN_BITS	3

#घोषणा SECTOR_SIZE		512
#घोषणा SECTOR_SHIFT		9
#घोषणा OOB_SIZE		16

#घोषणा MAX_LOGIC_BLK_PER_ZONE	1000
#घोषणा MAX_PHYS_BLK_PER_ZONE	1024

#घोषणा KiB(x)	( (x) * 1024L )
#घोषणा MiB(x)	( KiB(x) * 1024L )

/** CHS Table
		1MiB	2MiB	4MiB	8MiB	16MiB	32MiB	64MiB	128MiB
NCylinder	125	125	250	250	500	500	500	500
NHead		4	4	4	4	4	8	8	16
NSector		4	8	8	16	16	16	32	32
SumSector	2,000	4,000	8,000	16,000	32,000	64,000	128,000	256,000
SectorSize	512	512	512	512	512	512	512	512
**/

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ size;
	अचिन्हित लघु cyl;
	अचिन्हित अक्षर head;
	अचिन्हित अक्षर sec;
पूर्ण chs_entry_t;

/* Must be ordered by size */
अटल स्थिर chs_entry_t chs_table[] = अणु
	अणु MiB(  1), 125,  4,  4 पूर्ण,
	अणु MiB(  2), 125,  4,  8 पूर्ण,
	अणु MiB(  4), 250,  4,  8 पूर्ण,
	अणु MiB(  8), 250,  4, 16 पूर्ण,
	अणु MiB( 16), 500,  4, 16 पूर्ण,
	अणु MiB( 32), 500,  8, 16 पूर्ण,
	अणु MiB( 64), 500,  8, 32 पूर्ण,
	अणु MiB(128), 500, 16, 32 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल पूर्णांक get_chs(अचिन्हित दीर्घ size, अचिन्हित लघु *cyl, अचिन्हित अक्षर *head,
			अचिन्हित अक्षर *sec)
अणु
	पूर्णांक k;
	पूर्णांक found = 0;

	k = 0;
	जबतक (chs_table[k].size > 0 && size > chs_table[k].size)
		k++;

	अगर (chs_table[k].size > 0) अणु
		अगर (cyl)
			*cyl = chs_table[k].cyl;
		अगर (head)
			*head = chs_table[k].head;
		अगर (sec)
			*sec = chs_table[k].sec;
		found = 1;
	पूर्ण

	वापस found;
पूर्ण

/* These bytes are the signature क्रम the CIS/IDI sector */
अटल स्थिर uपूर्णांक8_t cis_numbers[] = अणु
	0x01, 0x03, 0xD9, 0x01, 0xFF, 0x18, 0x02, 0xDF, 0x01, 0x20
पूर्ण;

/* Read and check क्रम a valid CIS sector */
अटल पूर्णांक get_valid_cis_sector(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक ret, k, cis_sector;
	माप_प्रकार retlen;
	loff_t offset;
	uपूर्णांक8_t *sect_buf;

	cis_sector = -1;

	sect_buf = kदो_स्मृति(SECTOR_SIZE, GFP_KERNEL);
	अगर (!sect_buf)
		जाओ out;

	/*
	 * Look क्रम CIS/IDI sector on the first GOOD block (give up after 4 bad
	 * blocks). If the first good block करोesn't contain CIS number the flash
	 * is not SSFDC क्रमmatted
	 */
	क्रम (k = 0, offset = 0; k < 4; k++, offset += mtd->erasesize) अणु
		अगर (mtd_block_isbad(mtd, offset)) अणु
			ret = mtd_पढ़ो(mtd, offset, SECTOR_SIZE, &retlen,
				       sect_buf);

			/* CIS pattern match on the sector buffer */
			अगर (ret < 0 || retlen != SECTOR_SIZE) अणु
				prपूर्णांकk(KERN_WARNING
					"SSFDC_RO:can't read CIS/IDI sector\n");
			पूर्ण अन्यथा अगर (!स_भेद(sect_buf, cis_numbers,
					माप(cis_numbers))) अणु
				/* Found */
				cis_sector = (पूर्णांक)(offset >> SECTOR_SHIFT);
			पूर्ण अन्यथा अणु
				pr_debug("SSFDC_RO: CIS/IDI sector not found"
					" on %s (mtd%d)\n", mtd->name,
					mtd->index);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(sect_buf);
 out:
	वापस cis_sector;
पूर्ण

/* Read physical sector (wrapper to MTD_READ) */
अटल पूर्णांक पढ़ो_physical_sector(काष्ठा mtd_info *mtd, uपूर्णांक8_t *sect_buf,
				पूर्णांक sect_no)
अणु
	पूर्णांक ret;
	माप_प्रकार retlen;
	loff_t offset = (loff_t)sect_no << SECTOR_SHIFT;

	ret = mtd_पढ़ो(mtd, offset, SECTOR_SIZE, &retlen, sect_buf);
	अगर (ret < 0 || retlen != SECTOR_SIZE)
		वापस -1;

	वापस 0;
पूर्ण

/* Read redundancy area (wrapper to MTD_READ_OOB */
अटल पूर्णांक पढ़ो_raw_oob(काष्ठा mtd_info *mtd, loff_t offs, uपूर्णांक8_t *buf)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret;

	ops.mode = MTD_OPS_RAW;
	ops.ooboffs = 0;
	ops.ooblen = OOB_SIZE;
	ops.oobbuf = buf;
	ops.datbuf = शून्य;

	ret = mtd_पढ़ो_oob(mtd, offs, &ops);
	अगर (ret < 0 || ops.oobretlen != OOB_SIZE)
		वापस -1;

	वापस 0;
पूर्ण

/* Parity calculator on a word of n bit size */
अटल पूर्णांक get_parity(पूर्णांक number, पूर्णांक size)
अणु
 	पूर्णांक k;
	पूर्णांक parity;

	parity = 1;
	क्रम (k = 0; k < size; k++) अणु
		parity += (number >> k);
		parity &= 1;
	पूर्ण
	वापस parity;
पूर्ण

/* Read and validate the logical block address field stored in the OOB */
अटल पूर्णांक get_logical_address(uपूर्णांक8_t *oob_buf)
अणु
	पूर्णांक block_address, parity;
	पूर्णांक offset[2] = अणु6, 11पूर्ण; /* offset of the 2 address fields within OOB */
	पूर्णांक j;
	पूर्णांक ok = 0;

	/*
	 * Look क्रम the first valid logical address
	 * Valid address has fixed pattern on most signअगरicant bits and
	 * parity check
	 */
	क्रम (j = 0; j < ARRAY_SIZE(offset); j++) अणु
		block_address = ((पूर्णांक)oob_buf[offset[j]] << 8) |
			oob_buf[offset[j]+1];

		/* Check क्रम the signature bits in the address field (MSBits) */
		अगर ((block_address & ~0x7FF) == 0x1000) अणु
			parity = block_address & 0x01;
			block_address &= 0x7FF;
			block_address >>= 1;

			अगर (get_parity(block_address, 10) != parity) अणु
				pr_debug("SSFDC_RO: logical address field%d"
					"parity error(0x%04X)\n", j+1,
					block_address);
			पूर्ण अन्यथा अणु
				ok = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ok)
		block_address = -2;

	pr_debug("SSFDC_RO: get_logical_address() %d\n",
		block_address);

	वापस block_address;
पूर्ण

/* Build the logic block map */
अटल पूर्णांक build_logical_block_map(काष्ठा ssfdcr_record *ssfdc)
अणु
	अचिन्हित दीर्घ offset;
	uपूर्णांक8_t oob_buf[OOB_SIZE];
	पूर्णांक ret, block_address, phys_block;
	काष्ठा mtd_info *mtd = ssfdc->mbd.mtd;

	pr_debug("SSFDC_RO: build_block_map() nblks=%d (%luK)\n",
	      ssfdc->map_len,
	      (अचिन्हित दीर्घ)ssfdc->map_len * ssfdc->erase_size / 1024);

	/* Scan every physical block, skip CIS block */
	क्रम (phys_block = ssfdc->cis_block + 1; phys_block < ssfdc->map_len;
			phys_block++) अणु
		offset = (अचिन्हित दीर्घ)phys_block * ssfdc->erase_size;
		अगर (mtd_block_isbad(mtd, offset))
			जारी;	/* skip bad blocks */

		ret = पढ़ो_raw_oob(mtd, offset, oob_buf);
		अगर (ret < 0) अणु
			pr_debug("SSFDC_RO: mtd read_oob() failed at %lu\n",
				offset);
			वापस -1;
		पूर्ण
		block_address = get_logical_address(oob_buf);

		/* Skip invalid addresses */
		अगर (block_address >= 0 &&
				block_address < MAX_LOGIC_BLK_PER_ZONE) अणु
			पूर्णांक zone_index;

			zone_index = phys_block / MAX_PHYS_BLK_PER_ZONE;
			block_address += zone_index * MAX_LOGIC_BLK_PER_ZONE;
			ssfdc->logic_block_map[block_address] =
				(अचिन्हित लघु)phys_block;

			pr_debug("SSFDC_RO: build_block_map() phys_block=%d,"
				"logic_block_addr=%d, zone=%d\n",
				phys_block, block_address, zone_index);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ssfdcr_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा ssfdcr_record *ssfdc;
	पूर्णांक cis_sector;

	/* Check क्रम small page न_अंकD flash */
	अगर (!mtd_type_is_nand(mtd) || mtd->oobsize != OOB_SIZE ||
	    mtd->size > अच_पूर्णांक_उच्च)
		वापस;

	/* Check क्रम SSDFC क्रमmat by पढ़ोing CIS/IDI sector */
	cis_sector = get_valid_cis_sector(mtd);
	अगर (cis_sector == -1)
		वापस;

	ssfdc = kzalloc(माप(काष्ठा ssfdcr_record), GFP_KERNEL);
	अगर (!ssfdc)
		वापस;

	ssfdc->mbd.mtd = mtd;
	ssfdc->mbd.devnum = -1;
	ssfdc->mbd.tr = tr;
	ssfdc->mbd.पढ़ोonly = 1;

	ssfdc->cis_block = cis_sector / (mtd->erasesize >> SECTOR_SHIFT);
	ssfdc->erase_size = mtd->erasesize;
	ssfdc->map_len = (u32)mtd->size / mtd->erasesize;

	pr_debug("SSFDC_RO: cis_block=%d,erase_size=%d,map_len=%d,n_zones=%d\n",
		ssfdc->cis_block, ssfdc->erase_size, ssfdc->map_len,
		DIV_ROUND_UP(ssfdc->map_len, MAX_PHYS_BLK_PER_ZONE));

	/* Set geometry */
	ssfdc->heads = 16;
	ssfdc->sectors = 32;
	get_chs(mtd->size, शून्य, &ssfdc->heads, &ssfdc->sectors);
	ssfdc->cylinders = (अचिन्हित लघु)(((u32)mtd->size >> SECTOR_SHIFT) /
			((दीर्घ)ssfdc->sectors * (दीर्घ)ssfdc->heads));

	pr_debug("SSFDC_RO: using C:%d H:%d S:%d == %ld sects\n",
		ssfdc->cylinders, ssfdc->heads , ssfdc->sectors,
		(दीर्घ)ssfdc->cylinders * (दीर्घ)ssfdc->heads *
		(दीर्घ)ssfdc->sectors);

	ssfdc->mbd.size = (दीर्घ)ssfdc->heads * (दीर्घ)ssfdc->cylinders *
				(दीर्घ)ssfdc->sectors;

	/* Allocate logical block map */
	ssfdc->logic_block_map =
		kदो_स्मृति_array(ssfdc->map_len,
			      माप(ssfdc->logic_block_map[0]), GFP_KERNEL);
	अगर (!ssfdc->logic_block_map)
		जाओ out_err;
	स_रखो(ssfdc->logic_block_map, 0xff, माप(ssfdc->logic_block_map[0]) *
		ssfdc->map_len);

	/* Build logical block map */
	अगर (build_logical_block_map(ssfdc) < 0)
		जाओ out_err;

	/* Register device + partitions */
	अगर (add_mtd_blktrans_dev(&ssfdc->mbd))
		जाओ out_err;

	prपूर्णांकk(KERN_INFO "SSFDC_RO: Found ssfdc%c on mtd%d (%s)\n",
		ssfdc->mbd.devnum + 'a', mtd->index, mtd->name);
	वापस;

out_err:
	kमुक्त(ssfdc->logic_block_map);
        kमुक्त(ssfdc);
पूर्ण

अटल व्योम ssfdcr_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा ssfdcr_record *ssfdc = (काष्ठा ssfdcr_record *)dev;

	pr_debug("SSFDC_RO: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);
	kमुक्त(ssfdc->logic_block_map);
पूर्ण

अटल पूर्णांक ssfdcr_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev,
				अचिन्हित दीर्घ logic_sect_no, अक्षर *buf)
अणु
	काष्ठा ssfdcr_record *ssfdc = (काष्ठा ssfdcr_record *)dev;
	पूर्णांक sectors_per_block, offset, block_address;

	sectors_per_block = ssfdc->erase_size >> SECTOR_SHIFT;
	offset = (पूर्णांक)(logic_sect_no % sectors_per_block);
	block_address = (पूर्णांक)(logic_sect_no / sectors_per_block);

	pr_debug("SSFDC_RO: ssfdcr_readsect(%lu) sec_per_blk=%d, ofst=%d,"
		" block_addr=%d\n", logic_sect_no, sectors_per_block, offset,
		block_address);

	BUG_ON(block_address >= ssfdc->map_len);

	block_address = ssfdc->logic_block_map[block_address];

	pr_debug("SSFDC_RO: ssfdcr_readsect() phys_block_addr=%d\n",
		block_address);

	अगर (block_address < 0xffff) अणु
		अचिन्हित दीर्घ sect_no;

		sect_no = (अचिन्हित दीर्घ)block_address * sectors_per_block +
				offset;

		pr_debug("SSFDC_RO: ssfdcr_readsect() phys_sect_no=%lu\n",
			sect_no);

		अगर (पढ़ो_physical_sector(ssfdc->mbd.mtd, buf, sect_no) < 0)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		स_रखो(buf, 0xff, SECTOR_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssfdcr_getgeo(काष्ठा mtd_blktrans_dev *dev,  काष्ठा hd_geometry *geo)
अणु
	काष्ठा ssfdcr_record *ssfdc = (काष्ठा ssfdcr_record *)dev;

	pr_debug("SSFDC_RO: ssfdcr_getgeo() C=%d, H=%d, S=%d\n",
			ssfdc->cylinders, ssfdc->heads, ssfdc->sectors);

	geo->heads = ssfdc->heads;
	geo->sectors = ssfdc->sectors;
	geo->cylinders = ssfdc->cylinders;

	वापस 0;
पूर्ण

/****************************************************************************
 *
 * Module stuff
 *
 ****************************************************************************/

अटल काष्ठा mtd_blktrans_ops ssfdcr_tr = अणु
	.name		= "ssfdc",
	.major		= SSFDCR_MAJOR,
	.part_bits	= SSFDCR_PARTN_BITS,
	.blksize	= SECTOR_SIZE,
	.getgeo		= ssfdcr_getgeo,
	.पढ़ोsect	= ssfdcr_पढ़ोsect,
	.add_mtd	= ssfdcr_add_mtd,
	.हटाओ_dev	= ssfdcr_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_ssfdcr(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "SSFDC read-only Flash Translation layer\n");

	वापस रेजिस्टर_mtd_blktrans(&ssfdcr_tr);
पूर्ण

अटल व्योम __निकास cleanup_ssfdcr(व्योम)
अणु
	deरेजिस्टर_mtd_blktrans(&ssfdcr_tr);
पूर्ण

module_init(init_ssfdcr);
module_निकास(cleanup_ssfdcr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Claudio Lanconelli <lanconelli.claudio@eptar.com>");
MODULE_DESCRIPTION("Flash Translation Layer for read-only SSFDC SmartMedia card");
