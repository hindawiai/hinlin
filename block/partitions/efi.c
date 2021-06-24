<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/************************************************************
 * EFI GUID Partition Table handling
 *
 * http://www.uefi.org/specs/
 * http://www.पूर्णांकel.com/technology/efi/
 *
 * efi.[ch] by Matt Domsch <Matt_Domsch@dell.com>
 *   Copyright 2000,2001,2002,2004 Dell Inc.
 *
 * TODO:
 *
 * Changelog:
 * Mon August 5th, 2013 Davidlohr Bueso <davidlohr@hp.com>
 * - detect hybrid MBRs, tighter pMBR checking & cleanups.
 *
 * Mon Nov 09 2004 Matt Domsch <Matt_Domsch@dell.com>
 * - test क्रम valid PMBR and valid PGPT beक्रमe ever पढ़ोing
 *   AGPT, allow override with 'gpt' kernel command line option.
 * - check क्रम first/last_usable_lba outside of size of disk
 *
 * Tue  Mar 26 2002 Matt Domsch <Matt_Domsch@dell.com>
 * - Ported to 2.5.7-pre1 and 2.5.7-dj2
 * - Applied patch to aव्योम fault in alternate header handling
 * - cleaned up find_valid_gpt
 * - On-disk काष्ठाure and copy in memory is *always* LE now - 
 *   swab fields as needed
 * - हटाओ prपूर्णांक_gpt_header()
 * - only use first max_p partition entries, to keep the kernel minor number
 *   and partition numbers tied.
 *
 * Mon  Feb 04 2002 Matt Domsch <Matt_Domsch@dell.com>
 * - Removed __PRIPTR_PREFIX - not being used
 *
 * Mon  Jan 14 2002 Matt Domsch <Matt_Domsch@dell.com>
 * - Ported to 2.5.2-pre11 + library crc32 patch Linus applied
 *
 * Thu Dec 6 2001 Matt Domsch <Matt_Domsch@dell.com>
 * - Added compare_gpts().
 * - moved le_efi_guid_to_cpus() back पूर्णांकo this file.  GPT is the only
 *   thing that keeps EFI GUIDs on disk.
 * - Changed gpt काष्ठाure names and members to be simpler and more Linux-like.
 * 
 * Wed Oct 17 2001 Matt Domsch <Matt_Domsch@dell.com>
 * - Removed CONFIG_DEVFS_VOLUMES_UUID code entirely per Martin Wilck
 *
 * Wed Oct 10 2001 Matt Domsch <Matt_Domsch@dell.com>
 * - Changed function comments to DocBook style per Andreas Dilger suggestion.
 *
 * Mon Oct 08 2001 Matt Domsch <Matt_Domsch@dell.com>
 * - Change पढ़ो_lba() to use the page cache per Al Viro's work.
 * - prपूर्णांक u64s properly on all architectures
 * - fixed debug_prपूर्णांकk(), now Dprपूर्णांकk()
 *
 * Mon Oct 01 2001 Matt Domsch <Matt_Domsch@dell.com>
 * - Style cleanups
 * - made most functions अटल
 * - Endianness addition
 * - हटाओ test क्रम second alternate header, as it's not per spec,
 *   and is unnecessary.  There's now a method to पढ़ो/ग_लिखो the last
 *   sector of an odd-sized disk from user space.  No tools have ever
 *   been released which used this code, so it's effectively dead.
 * - Per Asit Mallick of Intel, added a test क्रम a valid PMBR.
 * - Added kernel command line option 'gpt' to override valid PMBR test.
 *
 * Wed Jun  6 2001 Martin Wilck <Martin.Wilck@Fujitsu-Siemens.com>
 * - added devfs volume UUID support (/dev/volumes/uuids) क्रम
 *   mounting file प्रणालीs by the partition GUID. 
 *
 * Tue Dec  5 2000 Matt Domsch <Matt_Domsch@dell.com>
 * - Moved crc32() to linux/lib, added efi_crc32().
 *
 * Thu Nov 30 2000 Matt Domsch <Matt_Domsch@dell.com>
 * - Replaced Intel's CRC32 function with an equivalent
 *   non-license-restricted version.
 *
 * Wed Oct 25 2000 Matt Domsch <Matt_Domsch@dell.com>
 * - Fixed the last_lba() call to वापस the proper last block
 *
 * Thu Oct 12 2000 Matt Domsch <Matt_Domsch@dell.com>
 * - Thanks to Andries Brouwer क्रम his debugging assistance.
 * - Code works, detects all the partitions.
 *
 ************************************************************/
#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>
#समावेश "check.h"
#समावेश "efi.h"

/* This allows a kernel command line option 'gpt' to override
 * the test क्रम invalid PMBR.  Not __initdata because reloading
 * the partition tables happens after init too.
 */
अटल पूर्णांक क्रमce_gpt;
अटल पूर्णांक __init
क्रमce_gpt_fn(अक्षर *str)
अणु
	क्रमce_gpt = 1;
	वापस 1;
पूर्ण
__setup("gpt", क्रमce_gpt_fn);


/**
 * efi_crc32() - EFI version of crc32 function
 * @buf: buffer to calculate crc32 of
 * @len: length of buf
 *
 * Description: Returns EFI-style CRC32 value क्रम @buf
 * 
 * This function uses the little endian Ethernet polynomial
 * but seeds the function with ~0, and xor's with ~0 at the end.
 * Note, the EFI Specअगरication, v1.02, has a reference to
 * Dr. Dobbs Journal, May 1994 (actually it's in May 1992).
 */
अटल अंतरभूत u32
efi_crc32(स्थिर व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस (crc32(~0L, buf, len) ^ ~0L);
पूर्ण

/**
 * last_lba(): वापस number of last logical block of device
 * @bdev: block device
 * 
 * Description: Returns last LBA value on success, 0 on error.
 * This is stored (by sd and ide-geometry) in
 *  the part[0] entry क्रम this disk, and is the number of
 *  physical sectors available on the disk.
 */
अटल u64 last_lba(काष्ठा block_device *bdev)
अणु
	अगर (!bdev || !bdev->bd_inode)
		वापस 0;
	वापस भाग_u64(bdev->bd_inode->i_size,
		       bdev_logical_block_size(bdev)) - 1ULL;
पूर्ण

अटल अंतरभूत पूर्णांक pmbr_part_valid(gpt_mbr_record *part)
अणु
	अगर (part->os_type != EFI_PMBR_OSTYPE_EFI_GPT)
		जाओ invalid;

	/* set to 0x00000001 (i.e., the LBA of the GPT Partition Header) */
	अगर (le32_to_cpu(part->starting_lba) != GPT_PRIMARY_PARTITION_TABLE_LBA)
		जाओ invalid;

	वापस GPT_MBR_PROTECTIVE;
invalid:
	वापस 0;
पूर्ण

/**
 * is_pmbr_valid(): test Protective MBR क्रम validity
 * @mbr: poपूर्णांकer to a legacy mbr काष्ठाure
 * @total_sectors: amount of sectors in the device
 *
 * Description: Checks क्रम a valid protective or hybrid
 * master boot record (MBR). The validity of a pMBR depends
 * on all of the following properties:
 *  1) MSDOS signature is in the last two bytes of the MBR
 *  2) One partition of type 0xEE is found
 *
 * In addition, a hybrid MBR will have up to three additional
 * primary partitions, which poपूर्णांक to the same space that's
 * marked out by up to three GPT partitions.
 *
 * Returns 0 upon invalid MBR, or GPT_MBR_PROTECTIVE or
 * GPT_MBR_HYBRID depending on the device layout.
 */
अटल पूर्णांक is_pmbr_valid(legacy_mbr *mbr, sector_t total_sectors)
अणु
	uपूर्णांक32_t sz = 0;
	पूर्णांक i, part = 0, ret = 0; /* invalid by शेष */

	अगर (!mbr || le16_to_cpu(mbr->signature) != MSDOS_MBR_SIGNATURE)
		जाओ करोne;

	क्रम (i = 0; i < 4; i++) अणु
		ret = pmbr_part_valid(&mbr->partition_record[i]);
		अगर (ret == GPT_MBR_PROTECTIVE) अणु
			part = i;
			/*
			 * Ok, we at least know that there's a protective MBR,
			 * now check अगर there are other partition types क्रम
			 * hybrid MBR.
			 */
			जाओ check_hybrid;
		पूर्ण
	पूर्ण

	अगर (ret != GPT_MBR_PROTECTIVE)
		जाओ करोne;
check_hybrid:
	क्रम (i = 0; i < 4; i++)
		अगर ((mbr->partition_record[i].os_type !=
			EFI_PMBR_OSTYPE_EFI_GPT) &&
		    (mbr->partition_record[i].os_type != 0x00))
			ret = GPT_MBR_HYBRID;

	/*
	 * Protective MBRs take up the lesser of the whole disk
	 * or 2 TiB (32bit LBA), ignoring the rest of the disk.
	 * Some partitioning programs, nonetheless, choose to set
	 * the size to the maximum 32-bit limitation, disregarding
	 * the disk size.
	 *
	 * Hybrid MBRs करो not necessarily comply with this.
	 *
	 * Consider a bad value here to be a warning to support dd'ing
	 * an image from a smaller disk to a larger disk.
	 */
	अगर (ret == GPT_MBR_PROTECTIVE) अणु
		sz = le32_to_cpu(mbr->partition_record[part].size_in_lba);
		अगर (sz != (uपूर्णांक32_t) total_sectors - 1 && sz != 0xFFFFFFFF)
			pr_debug("GPT: mbr size in lba (%u) different than whole disk (%u).\n",
				 sz, min_t(uपूर्णांक32_t,
					   total_sectors - 1, 0xFFFFFFFF));
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/**
 * पढ़ो_lba(): Read bytes from disk, starting at given LBA
 * @state: disk parsed partitions
 * @lba: the Logical Block Address of the partition table
 * @buffer: destination buffer
 * @count: bytes to पढ़ो
 *
 * Description: Reads @count bytes from @state->bdev पूर्णांकo @buffer.
 * Returns number of bytes पढ़ो on success, 0 on error.
 */
अटल माप_प्रकार पढ़ो_lba(काष्ठा parsed_partitions *state,
		       u64 lba, u8 *buffer, माप_प्रकार count)
अणु
	माप_प्रकार totalपढ़ोcount = 0;
	काष्ठा block_device *bdev = state->bdev;
	sector_t n = lba * (bdev_logical_block_size(bdev) / 512);

	अगर (!buffer || lba > last_lba(bdev))
                वापस 0;

	जबतक (count) अणु
		पूर्णांक copied = 512;
		Sector sect;
		अचिन्हित अक्षर *data = पढ़ो_part_sector(state, n++, &sect);
		अगर (!data)
			अवरोध;
		अगर (copied > count)
			copied = count;
		स_नकल(buffer, data, copied);
		put_dev_sector(sect);
		buffer += copied;
		totalपढ़ोcount +=copied;
		count -= copied;
	पूर्ण
	वापस totalपढ़ोcount;
पूर्ण

/**
 * alloc_पढ़ो_gpt_entries(): पढ़ोs partition entries from disk
 * @state: disk parsed partitions
 * @gpt: GPT header
 * 
 * Description: Returns ptes on success,  शून्य on error.
 * Allocates space क्रम PTEs based on inक्रमmation found in @gpt.
 * Notes: remember to मुक्त pte when you're करोne!
 */
अटल gpt_entry *alloc_पढ़ो_gpt_entries(काष्ठा parsed_partitions *state,
					 gpt_header *gpt)
अणु
	माप_प्रकार count;
	gpt_entry *pte;

	अगर (!gpt)
		वापस शून्य;

	count = (माप_प्रकार)le32_to_cpu(gpt->num_partition_entries) *
                le32_to_cpu(gpt->माप_partition_entry);
	अगर (!count)
		वापस शून्य;
	pte = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!pte)
		वापस शून्य;

	अगर (पढ़ो_lba(state, le64_to_cpu(gpt->partition_entry_lba),
			(u8 *) pte, count) < count) अणु
		kमुक्त(pte);
                pte=शून्य;
		वापस शून्य;
	पूर्ण
	वापस pte;
पूर्ण

/**
 * alloc_पढ़ो_gpt_header(): Allocates GPT header, पढ़ोs पूर्णांकo it from disk
 * @state: disk parsed partitions
 * @lba: the Logical Block Address of the partition table
 * 
 * Description: वापसs GPT header on success, शून्य on error.   Allocates
 * and fills a GPT header starting at @ from @state->bdev.
 * Note: remember to मुक्त gpt when finished with it.
 */
अटल gpt_header *alloc_पढ़ो_gpt_header(काष्ठा parsed_partitions *state,
					 u64 lba)
अणु
	gpt_header *gpt;
	अचिन्हित ssz = bdev_logical_block_size(state->bdev);

	gpt = kदो_स्मृति(ssz, GFP_KERNEL);
	अगर (!gpt)
		वापस शून्य;

	अगर (पढ़ो_lba(state, lba, (u8 *) gpt, ssz) < ssz) अणु
		kमुक्त(gpt);
                gpt=शून्य;
		वापस शून्य;
	पूर्ण

	वापस gpt;
पूर्ण

/**
 * is_gpt_valid() - tests one GPT header and PTEs क्रम validity
 * @state: disk parsed partitions
 * @lba: logical block address of the GPT header to test
 * @gpt: GPT header ptr, filled on वापस.
 * @ptes: PTEs ptr, filled on वापस.
 *
 * Description: वापसs 1 अगर valid,  0 on error.
 * If valid, वापसs poपूर्णांकers to newly allocated GPT header and PTEs.
 */
अटल पूर्णांक is_gpt_valid(काष्ठा parsed_partitions *state, u64 lba,
			gpt_header **gpt, gpt_entry **ptes)
अणु
	u32 crc, origcrc;
	u64 lastlba, pt_size;

	अगर (!ptes)
		वापस 0;
	अगर (!(*gpt = alloc_पढ़ो_gpt_header(state, lba)))
		वापस 0;

	/* Check the GUID Partition Table signature */
	अगर (le64_to_cpu((*gpt)->signature) != GPT_HEADER_SIGNATURE) अणु
		pr_debug("GUID Partition Table Header signature is wrong:"
			 "%lld != %lld\n",
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->signature),
			 (अचिन्हित दीर्घ दीर्घ)GPT_HEADER_SIGNATURE);
		जाओ fail;
	पूर्ण

	/* Check the GUID Partition Table header size is too big */
	अगर (le32_to_cpu((*gpt)->header_size) >
			bdev_logical_block_size(state->bdev)) अणु
		pr_debug("GUID Partition Table Header size is too large: %u > %u\n",
			le32_to_cpu((*gpt)->header_size),
			bdev_logical_block_size(state->bdev));
		जाओ fail;
	पूर्ण

	/* Check the GUID Partition Table header size is too small */
	अगर (le32_to_cpu((*gpt)->header_size) < माप(gpt_header)) अणु
		pr_debug("GUID Partition Table Header size is too small: %u < %zu\n",
			le32_to_cpu((*gpt)->header_size),
			माप(gpt_header));
		जाओ fail;
	पूर्ण

	/* Check the GUID Partition Table CRC */
	origcrc = le32_to_cpu((*gpt)->header_crc32);
	(*gpt)->header_crc32 = 0;
	crc = efi_crc32((स्थिर अचिन्हित अक्षर *) (*gpt), le32_to_cpu((*gpt)->header_size));

	अगर (crc != origcrc) अणु
		pr_debug("GUID Partition Table Header CRC is wrong: %x != %x\n",
			 crc, origcrc);
		जाओ fail;
	पूर्ण
	(*gpt)->header_crc32 = cpu_to_le32(origcrc);

	/* Check that the my_lba entry poपूर्णांकs to the LBA that contains
	 * the GUID Partition Table */
	अगर (le64_to_cpu((*gpt)->my_lba) != lba) अणु
		pr_debug("GPT my_lba incorrect: %lld != %lld\n",
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->my_lba),
			 (अचिन्हित दीर्घ दीर्घ)lba);
		जाओ fail;
	पूर्ण

	/* Check the first_usable_lba and last_usable_lba are
	 * within the disk.
	 */
	lastlba = last_lba(state->bdev);
	अगर (le64_to_cpu((*gpt)->first_usable_lba) > lastlba) अणु
		pr_debug("GPT: first_usable_lba incorrect: %lld > %lld\n",
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->first_usable_lba),
			 (अचिन्हित दीर्घ दीर्घ)lastlba);
		जाओ fail;
	पूर्ण
	अगर (le64_to_cpu((*gpt)->last_usable_lba) > lastlba) अणु
		pr_debug("GPT: last_usable_lba incorrect: %lld > %lld\n",
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->last_usable_lba),
			 (अचिन्हित दीर्घ दीर्घ)lastlba);
		जाओ fail;
	पूर्ण
	अगर (le64_to_cpu((*gpt)->last_usable_lba) < le64_to_cpu((*gpt)->first_usable_lba)) अणु
		pr_debug("GPT: last_usable_lba incorrect: %lld > %lld\n",
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->last_usable_lba),
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu((*gpt)->first_usable_lba));
		जाओ fail;
	पूर्ण
	/* Check that माप_partition_entry has the correct value */
	अगर (le32_to_cpu((*gpt)->माप_partition_entry) != माप(gpt_entry)) अणु
		pr_debug("GUID Partition Entry Size check failed.\n");
		जाओ fail;
	पूर्ण

	/* Sanity check partition table size */
	pt_size = (u64)le32_to_cpu((*gpt)->num_partition_entries) *
		le32_to_cpu((*gpt)->माप_partition_entry);
	अगर (pt_size > KMALLOC_MAX_SIZE) अणु
		pr_debug("GUID Partition Table is too large: %llu > %lu bytes\n",
			 (अचिन्हित दीर्घ दीर्घ)pt_size, KMALLOC_MAX_SIZE);
		जाओ fail;
	पूर्ण

	अगर (!(*ptes = alloc_पढ़ो_gpt_entries(state, *gpt)))
		जाओ fail;

	/* Check the GUID Partition Entry Array CRC */
	crc = efi_crc32((स्थिर अचिन्हित अक्षर *) (*ptes), pt_size);

	अगर (crc != le32_to_cpu((*gpt)->partition_entry_array_crc32)) अणु
		pr_debug("GUID Partition Entry Array CRC check failed.\n");
		जाओ fail_ptes;
	पूर्ण

	/* We're done, all's well */
	वापस 1;

 fail_ptes:
	kमुक्त(*ptes);
	*ptes = शून्य;
 fail:
	kमुक्त(*gpt);
	*gpt = शून्य;
	वापस 0;
पूर्ण

/**
 * is_pte_valid() - tests one PTE क्रम validity
 * @pte:pte to check
 * @lastlba: last lba of the disk
 *
 * Description: वापसs 1 अगर valid,  0 on error.
 */
अटल अंतरभूत पूर्णांक
is_pte_valid(स्थिर gpt_entry *pte, स्थिर u64 lastlba)
अणु
	अगर ((!efi_guidcmp(pte->partition_type_guid, शून्य_GUID)) ||
	    le64_to_cpu(pte->starting_lba) > lastlba         ||
	    le64_to_cpu(pte->ending_lba)   > lastlba)
		वापस 0;
	वापस 1;
पूर्ण

/**
 * compare_gpts() - Search disk क्रम valid GPT headers and PTEs
 * @pgpt: primary GPT header
 * @agpt: alternate GPT header
 * @lastlba: last LBA number
 *
 * Description: Returns nothing.  Sanity checks pgpt and agpt fields
 * and prपूर्णांकs warnings on discrepancies.
 * 
 */
अटल व्योम
compare_gpts(gpt_header *pgpt, gpt_header *agpt, u64 lastlba)
अणु
	पूर्णांक error_found = 0;
	अगर (!pgpt || !agpt)
		वापस;
	अगर (le64_to_cpu(pgpt->my_lba) != le64_to_cpu(agpt->alternate_lba)) अणु
		pr_warn("GPT:Primary header LBA != Alt. header alternate_lba\n");
		pr_warn("GPT:%lld != %lld\n",
		       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pgpt->my_lba),
                       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(agpt->alternate_lba));
		error_found++;
	पूर्ण
	अगर (le64_to_cpu(pgpt->alternate_lba) != le64_to_cpu(agpt->my_lba)) अणु
		pr_warn("GPT:Primary header alternate_lba != Alt. header my_lba\n");
		pr_warn("GPT:%lld != %lld\n",
		       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pgpt->alternate_lba),
                       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(agpt->my_lba));
		error_found++;
	पूर्ण
	अगर (le64_to_cpu(pgpt->first_usable_lba) !=
            le64_to_cpu(agpt->first_usable_lba)) अणु
		pr_warn("GPT:first_usable_lbas don't match.\n");
		pr_warn("GPT:%lld != %lld\n",
		       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pgpt->first_usable_lba),
                       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(agpt->first_usable_lba));
		error_found++;
	पूर्ण
	अगर (le64_to_cpu(pgpt->last_usable_lba) !=
            le64_to_cpu(agpt->last_usable_lba)) अणु
		pr_warn("GPT:last_usable_lbas don't match.\n");
		pr_warn("GPT:%lld != %lld\n",
		       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pgpt->last_usable_lba),
                       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(agpt->last_usable_lba));
		error_found++;
	पूर्ण
	अगर (efi_guidcmp(pgpt->disk_guid, agpt->disk_guid)) अणु
		pr_warn("GPT:disk_guids don't match.\n");
		error_found++;
	पूर्ण
	अगर (le32_to_cpu(pgpt->num_partition_entries) !=
            le32_to_cpu(agpt->num_partition_entries)) अणु
		pr_warn("GPT:num_partition_entries don't match: "
		       "0x%x != 0x%x\n",
		       le32_to_cpu(pgpt->num_partition_entries),
		       le32_to_cpu(agpt->num_partition_entries));
		error_found++;
	पूर्ण
	अगर (le32_to_cpu(pgpt->माप_partition_entry) !=
            le32_to_cpu(agpt->माप_partition_entry)) अणु
		pr_warn("GPT:sizeof_partition_entry values don't match: "
		       "0x%x != 0x%x\n",
                       le32_to_cpu(pgpt->माप_partition_entry),
		       le32_to_cpu(agpt->माप_partition_entry));
		error_found++;
	पूर्ण
	अगर (le32_to_cpu(pgpt->partition_entry_array_crc32) !=
            le32_to_cpu(agpt->partition_entry_array_crc32)) अणु
		pr_warn("GPT:partition_entry_array_crc32 values don't match: "
		       "0x%x != 0x%x\n",
                       le32_to_cpu(pgpt->partition_entry_array_crc32),
		       le32_to_cpu(agpt->partition_entry_array_crc32));
		error_found++;
	पूर्ण
	अगर (le64_to_cpu(pgpt->alternate_lba) != lastlba) अणु
		pr_warn("GPT:Primary header thinks Alt. header is not at the end of the disk.\n");
		pr_warn("GPT:%lld != %lld\n",
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pgpt->alternate_lba),
			(अचिन्हित दीर्घ दीर्घ)lastlba);
		error_found++;
	पूर्ण

	अगर (le64_to_cpu(agpt->my_lba) != lastlba) अणु
		pr_warn("GPT:Alternate GPT header not at the end of the disk.\n");
		pr_warn("GPT:%lld != %lld\n",
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(agpt->my_lba),
			(अचिन्हित दीर्घ दीर्घ)lastlba);
		error_found++;
	पूर्ण

	अगर (error_found)
		pr_warn("GPT: Use GNU Parted to correct GPT errors.\n");
	वापस;
पूर्ण

/**
 * find_valid_gpt() - Search disk क्रम valid GPT headers and PTEs
 * @state: disk parsed partitions
 * @gpt: GPT header ptr, filled on वापस.
 * @ptes: PTEs ptr, filled on वापस.
 *
 * Description: Returns 1 अगर valid, 0 on error.
 * If valid, वापसs poपूर्णांकers to newly allocated GPT header and PTEs.
 * Validity depends on PMBR being valid (or being overridden by the
 * 'gpt' kernel command line option) and finding either the Primary
 * GPT header and PTEs valid, or the Alternate GPT header and PTEs
 * valid.  If the Primary GPT header is not valid, the Alternate GPT header
 * is not checked unless the 'gpt' kernel command line option is passed.
 * This protects against devices which misreport their size, and क्रमces
 * the user to decide to use the Alternate GPT.
 */
अटल पूर्णांक find_valid_gpt(काष्ठा parsed_partitions *state, gpt_header **gpt,
			  gpt_entry **ptes)
अणु
	पूर्णांक good_pgpt = 0, good_agpt = 0, good_pmbr = 0;
	gpt_header *pgpt = शून्य, *agpt = शून्य;
	gpt_entry *pptes = शून्य, *aptes = शून्य;
	legacy_mbr *legacymbr;
	sector_t total_sectors = i_size_पढ़ो(state->bdev->bd_inode) >> 9;
	u64 lastlba;

	अगर (!ptes)
		वापस 0;

	lastlba = last_lba(state->bdev);
        अगर (!क्रमce_gpt) अणु
		/* This will be added to the EFI Spec. per Intel after v1.02. */
		legacymbr = kzalloc(माप(*legacymbr), GFP_KERNEL);
		अगर (!legacymbr)
			जाओ fail;

		पढ़ो_lba(state, 0, (u8 *)legacymbr, माप(*legacymbr));
		good_pmbr = is_pmbr_valid(legacymbr, total_sectors);
		kमुक्त(legacymbr);

		अगर (!good_pmbr)
			जाओ fail;

		pr_debug("Device has a %s MBR\n",
			 good_pmbr == GPT_MBR_PROTECTIVE ?
						"protective" : "hybrid");
	पूर्ण

	good_pgpt = is_gpt_valid(state, GPT_PRIMARY_PARTITION_TABLE_LBA,
				 &pgpt, &pptes);
        अगर (good_pgpt)
		good_agpt = is_gpt_valid(state,
					 le64_to_cpu(pgpt->alternate_lba),
					 &agpt, &aptes);
        अगर (!good_agpt && क्रमce_gpt)
                good_agpt = is_gpt_valid(state, lastlba, &agpt, &aptes);

        /* The obviously unsuccessful हाल */
        अगर (!good_pgpt && !good_agpt)
                जाओ fail;

        compare_gpts(pgpt, agpt, lastlba);

        /* The good हालs */
        अगर (good_pgpt) अणु
                *gpt  = pgpt;
                *ptes = pptes;
                kमुक्त(agpt);
                kमुक्त(aptes);
		अगर (!good_agpt)
                        pr_warn("Alternate GPT is invalid, using primary GPT.\n");
                वापस 1;
        पूर्ण
        अन्यथा अगर (good_agpt) अणु
                *gpt  = agpt;
                *ptes = aptes;
                kमुक्त(pgpt);
                kमुक्त(pptes);
		pr_warn("Primary GPT is invalid, using alternate GPT.\n");
                वापस 1;
        पूर्ण

 fail:
        kमुक्त(pgpt);
        kमुक्त(agpt);
        kमुक्त(pptes);
        kमुक्त(aptes);
        *gpt = शून्य;
        *ptes = शून्य;
        वापस 0;
पूर्ण

/**
 * utf16_le_to_7bit(): Naively converts a UTF-16LE string to 7-bit ASCII अक्षरacters
 * @in: input UTF-16LE string
 * @size: size of the input string
 * @out: output string ptr, should be capable to store @size+1 अक्षरacters
 *
 * Description: Converts @size UTF16-LE symbols from @in string to 7-bit
 * ASCII अक्षरacters and stores them to @out. Adds trailing zero to @out array.
 */
अटल व्योम utf16_le_to_7bit(स्थिर __le16 *in, अचिन्हित पूर्णांक size, u8 *out)
अणु
	अचिन्हित पूर्णांक i = 0;

	out[size] = 0;

	जबतक (i < size) अणु
		u8 c = le16_to_cpu(in[i]) & 0xff;

		अगर (c && !है_छाप(c))
			c = '!';
		out[i] = c;
		i++;
	पूर्ण
पूर्ण

/**
 * efi_partition - scan क्रम GPT partitions
 * @state: disk parsed partitions
 *
 * Description: called from check.c, अगर the disk contains GPT
 * partitions, sets up partition entries in the kernel.
 *
 * If the first block on the disk is a legacy MBR,
 * it will get handled by msकरोs_partition().
 * If it's a Protective MBR, we'll handle it here.
 *
 * We करो not create a Linux partition क्रम GPT, but
 * only क्रम the actual data partitions.
 * Returns:
 * -1 अगर unable to पढ़ो the partition table
 *  0 अगर this isn't our partition table
 *  1 अगर successful
 *
 */
पूर्णांक efi_partition(काष्ठा parsed_partitions *state)
अणु
	gpt_header *gpt = शून्य;
	gpt_entry *ptes = शून्य;
	u32 i;
	अचिन्हित ssz = bdev_logical_block_size(state->bdev) / 512;

	अगर (!find_valid_gpt(state, &gpt, &ptes) || !gpt || !ptes) अणु
		kमुक्त(gpt);
		kमुक्त(ptes);
		वापस 0;
	पूर्ण

	pr_debug("GUID Partition Table is valid!  Yea!\n");

	क्रम (i = 0; i < le32_to_cpu(gpt->num_partition_entries) && i < state->limit-1; i++) अणु
		काष्ठा partition_meta_info *info;
		अचिन्हित label_max;
		u64 start = le64_to_cpu(ptes[i].starting_lba);
		u64 size = le64_to_cpu(ptes[i].ending_lba) -
			   le64_to_cpu(ptes[i].starting_lba) + 1ULL;

		अगर (!is_pte_valid(&ptes[i], last_lba(state->bdev)))
			जारी;

		put_partition(state, i+1, start * ssz, size * ssz);

		/* If this is a RAID volume, tell md */
		अगर (!efi_guidcmp(ptes[i].partition_type_guid, PARTITION_LINUX_RAID_GUID))
			state->parts[i + 1].flags = ADDPART_FLAG_RAID;

		info = &state->parts[i + 1].info;
		efi_guid_to_str(&ptes[i].unique_partition_guid, info->uuid);

		/* Naively convert UTF16-LE to 7 bits. */
		label_max = min(ARRAY_SIZE(info->volname) - 1,
				ARRAY_SIZE(ptes[i].partition_name));
		utf16_le_to_7bit(ptes[i].partition_name, label_max, info->volname);
		state->parts[i + 1].has_info = true;
	पूर्ण
	kमुक्त(ptes);
	kमुक्त(gpt);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण
