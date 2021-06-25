<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_rd.c
 *
 * This file contains the Storage Engine <-> Ramdisk transport
 * specअगरic functions.
 *
 * (c) Copyright 2003-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समयr.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <scsi/scsi_proto.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>

#समावेश "target_core_rd.h"

अटल अंतरभूत काष्ठा rd_dev *RD_DEV(काष्ठा se_device *dev)
अणु
	वापस container_of(dev, काष्ठा rd_dev, dev);
पूर्ण

अटल पूर्णांक rd_attach_hba(काष्ठा se_hba *hba, u32 host_id)
अणु
	काष्ठा rd_host *rd_host;

	rd_host = kzalloc(माप(*rd_host), GFP_KERNEL);
	अगर (!rd_host)
		वापस -ENOMEM;

	rd_host->rd_host_id = host_id;

	hba->hba_ptr = rd_host;

	pr_debug("CORE_HBA[%d] - TCM Ramdisk HBA Driver %s on"
		" Generic Target Core Stack %s\n", hba->hba_id,
		RD_HBA_VERSION, TARGET_CORE_VERSION);

	वापस 0;
पूर्ण

अटल व्योम rd_detach_hba(काष्ठा se_hba *hba)
अणु
	काष्ठा rd_host *rd_host = hba->hba_ptr;

	pr_debug("CORE_HBA[%d] - Detached Ramdisk HBA: %u from"
		" Generic Target Core\n", hba->hba_id, rd_host->rd_host_id);

	kमुक्त(rd_host);
	hba->hba_ptr = शून्य;
पूर्ण

अटल u32 rd_release_sgl_table(काष्ठा rd_dev *rd_dev, काष्ठा rd_dev_sg_table *sg_table,
				 u32 sg_table_count)
अणु
	काष्ठा page *pg;
	काष्ठा scatterlist *sg;
	u32 i, j, page_count = 0, sg_per_table;

	क्रम (i = 0; i < sg_table_count; i++) अणु
		sg = sg_table[i].sg_table;
		sg_per_table = sg_table[i].rd_sg_count;

		क्रम (j = 0; j < sg_per_table; j++) अणु
			pg = sg_page(&sg[j]);
			अगर (pg) अणु
				__मुक्त_page(pg);
				page_count++;
			पूर्ण
		पूर्ण
		kमुक्त(sg);
	पूर्ण

	kमुक्त(sg_table);
	वापस page_count;
पूर्ण

अटल व्योम rd_release_device_space(काष्ठा rd_dev *rd_dev)
अणु
	u32 page_count;

	अगर (!rd_dev->sg_table_array || !rd_dev->sg_table_count)
		वापस;

	page_count = rd_release_sgl_table(rd_dev, rd_dev->sg_table_array,
					  rd_dev->sg_table_count);

	pr_debug("CORE_RD[%u] - Released device space for Ramdisk"
		" Device ID: %u, pages %u in %u tables total bytes %lu\n",
		rd_dev->rd_host->rd_host_id, rd_dev->rd_dev_id, page_count,
		rd_dev->sg_table_count, (अचिन्हित दीर्घ)page_count * PAGE_SIZE);

	rd_dev->sg_table_array = शून्य;
	rd_dev->sg_table_count = 0;
पूर्ण


/*	rd_build_device_space():
 *
 *
 */
अटल पूर्णांक rd_allocate_sgl_table(काष्ठा rd_dev *rd_dev, काष्ठा rd_dev_sg_table *sg_table,
				 u32 total_sg_needed, अचिन्हित अक्षर init_payload)
अणु
	u32 i = 0, j, page_offset = 0, sg_per_table;
	u32 max_sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				माप(काष्ठा scatterlist));
	काष्ठा page *pg;
	काष्ठा scatterlist *sg;
	अचिन्हित अक्षर *p;

	जबतक (total_sg_needed) अणु
		अचिन्हित पूर्णांक chain_entry = 0;

		sg_per_table = (total_sg_needed > max_sg_per_table) ?
			max_sg_per_table : total_sg_needed;

		/*
		 * Reserve extra element क्रम chain entry
		 */
		अगर (sg_per_table < total_sg_needed)
			chain_entry = 1;

		sg = kदो_स्मृति_array(sg_per_table + chain_entry, माप(*sg),
				GFP_KERNEL);
		अगर (!sg)
			वापस -ENOMEM;

		sg_init_table(sg, sg_per_table + chain_entry);

		अगर (i > 0) अणु
			sg_chain(sg_table[i - 1].sg_table,
				 max_sg_per_table + 1, sg);
		पूर्ण

		sg_table[i].sg_table = sg;
		sg_table[i].rd_sg_count = sg_per_table;
		sg_table[i].page_start_offset = page_offset;
		sg_table[i++].page_end_offset = (page_offset + sg_per_table)
						- 1;

		क्रम (j = 0; j < sg_per_table; j++) अणु
			pg = alloc_pages(GFP_KERNEL, 0);
			अगर (!pg) अणु
				pr_err("Unable to allocate scatterlist"
					" pages for struct rd_dev_sg_table\n");
				वापस -ENOMEM;
			पूर्ण
			sg_assign_page(&sg[j], pg);
			sg[j].length = PAGE_SIZE;

			p = kmap(pg);
			स_रखो(p, init_payload, PAGE_SIZE);
			kunmap(pg);
		पूर्ण

		page_offset += sg_per_table;
		total_sg_needed -= sg_per_table;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rd_build_device_space(काष्ठा rd_dev *rd_dev)
अणु
	काष्ठा rd_dev_sg_table *sg_table;
	u32 sg_tables, total_sg_needed;
	u32 max_sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				माप(काष्ठा scatterlist));
	पूर्णांक rc;

	अगर (rd_dev->rd_page_count <= 0) अणु
		pr_err("Illegal page count: %u for Ramdisk device\n",
		       rd_dev->rd_page_count);
		वापस -EINVAL;
	पूर्ण

	/* Don't need backing pages क्रम शून्यIO */
	अगर (rd_dev->rd_flags & RDF_शून्यIO)
		वापस 0;

	total_sg_needed = rd_dev->rd_page_count;

	sg_tables = (total_sg_needed / max_sg_per_table) + 1;
	sg_table = kसुस्मृति(sg_tables, माप(*sg_table), GFP_KERNEL);
	अगर (!sg_table)
		वापस -ENOMEM;

	rd_dev->sg_table_array = sg_table;
	rd_dev->sg_table_count = sg_tables;

	rc = rd_allocate_sgl_table(rd_dev, sg_table, total_sg_needed, 0x00);
	अगर (rc)
		वापस rc;

	pr_debug("CORE_RD[%u] - Built Ramdisk Device ID: %u space of"
		 " %u pages in %u tables\n", rd_dev->rd_host->rd_host_id,
		 rd_dev->rd_dev_id, rd_dev->rd_page_count,
		 rd_dev->sg_table_count);

	वापस 0;
पूर्ण

अटल व्योम rd_release_prot_space(काष्ठा rd_dev *rd_dev)
अणु
	u32 page_count;

	अगर (!rd_dev->sg_prot_array || !rd_dev->sg_prot_count)
		वापस;

	page_count = rd_release_sgl_table(rd_dev, rd_dev->sg_prot_array,
					  rd_dev->sg_prot_count);

	pr_debug("CORE_RD[%u] - Released protection space for Ramdisk"
		 " Device ID: %u, pages %u in %u tables total bytes %lu\n",
		 rd_dev->rd_host->rd_host_id, rd_dev->rd_dev_id, page_count,
		 rd_dev->sg_table_count, (अचिन्हित दीर्घ)page_count * PAGE_SIZE);

	rd_dev->sg_prot_array = शून्य;
	rd_dev->sg_prot_count = 0;
पूर्ण

अटल पूर्णांक rd_build_prot_space(काष्ठा rd_dev *rd_dev, पूर्णांक prot_length, पूर्णांक block_size)
अणु
	काष्ठा rd_dev_sg_table *sg_table;
	u32 total_sg_needed, sg_tables;
	u32 max_sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				माप(काष्ठा scatterlist));
	पूर्णांक rc;

	अगर (rd_dev->rd_flags & RDF_शून्यIO)
		वापस 0;
	/*
	 * prot_length=8byte dअगर data
	 * tot sg needed = rd_page_count * (PGSZ/block_size) *
	 * 		   (prot_length/block_size) + pad
	 * PGSZ canceled each other.
	 */
	total_sg_needed = (rd_dev->rd_page_count * prot_length / block_size) + 1;

	sg_tables = (total_sg_needed / max_sg_per_table) + 1;
	sg_table = kसुस्मृति(sg_tables, माप(*sg_table), GFP_KERNEL);
	अगर (!sg_table)
		वापस -ENOMEM;

	rd_dev->sg_prot_array = sg_table;
	rd_dev->sg_prot_count = sg_tables;

	rc = rd_allocate_sgl_table(rd_dev, sg_table, total_sg_needed, 0xff);
	अगर (rc)
		वापस rc;

	pr_debug("CORE_RD[%u] - Built Ramdisk Device ID: %u prot space of"
		 " %u pages in %u tables\n", rd_dev->rd_host->rd_host_id,
		 rd_dev->rd_dev_id, total_sg_needed, rd_dev->sg_prot_count);

	वापस 0;
पूर्ण

अटल काष्ठा se_device *rd_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name)
अणु
	काष्ठा rd_dev *rd_dev;
	काष्ठा rd_host *rd_host = hba->hba_ptr;

	rd_dev = kzalloc(माप(*rd_dev), GFP_KERNEL);
	अगर (!rd_dev)
		वापस शून्य;

	rd_dev->rd_host = rd_host;

	वापस &rd_dev->dev;
पूर्ण

अटल पूर्णांक rd_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);
	काष्ठा rd_host *rd_host = dev->se_hba->hba_ptr;
	पूर्णांक ret;

	अगर (!(rd_dev->rd_flags & RDF_HAS_PAGE_COUNT)) अणु
		pr_debug("Missing rd_pages= parameter\n");
		वापस -EINVAL;
	पूर्ण

	ret = rd_build_device_space(rd_dev);
	अगर (ret < 0)
		जाओ fail;

	dev->dev_attrib.hw_block_size = RD_BLOCKSIZE;
	dev->dev_attrib.hw_max_sectors = अच_पूर्णांक_उच्च;
	dev->dev_attrib.hw_queue_depth = RD_MAX_DEVICE_QUEUE_DEPTH;
	dev->dev_attrib.is_nonrot = 1;

	rd_dev->rd_dev_id = rd_host->rd_host_dev_id_count++;

	pr_debug("CORE_RD[%u] - Added TCM MEMCPY Ramdisk Device ID: %u of"
		" %u pages in %u tables, %lu total bytes\n",
		rd_host->rd_host_id, rd_dev->rd_dev_id, rd_dev->rd_page_count,
		rd_dev->sg_table_count,
		(अचिन्हित दीर्घ)(rd_dev->rd_page_count * PAGE_SIZE));

	वापस 0;

fail:
	rd_release_device_space(rd_dev);
	वापस ret;
पूर्ण

अटल व्योम rd_dev_call_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा se_device *dev = container_of(p, काष्ठा se_device, rcu_head);
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

	kमुक्त(rd_dev);
पूर्ण

अटल व्योम rd_मुक्त_device(काष्ठा se_device *dev)
अणु
	call_rcu(&dev->rcu_head, rd_dev_call_rcu);
पूर्ण

अटल व्योम rd_destroy_device(काष्ठा se_device *dev)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

	rd_release_device_space(rd_dev);
पूर्ण

अटल काष्ठा rd_dev_sg_table *rd_get_sg_table(काष्ठा rd_dev *rd_dev, u32 page)
अणु
	काष्ठा rd_dev_sg_table *sg_table;
	u32 i, sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				माप(काष्ठा scatterlist));

	i = page / sg_per_table;
	अगर (i < rd_dev->sg_table_count) अणु
		sg_table = &rd_dev->sg_table_array[i];
		अगर ((sg_table->page_start_offset <= page) &&
		    (sg_table->page_end_offset >= page))
			वापस sg_table;
	पूर्ण

	pr_err("Unable to locate struct rd_dev_sg_table for page: %u\n",
			page);

	वापस शून्य;
पूर्ण

अटल काष्ठा rd_dev_sg_table *rd_get_prot_table(काष्ठा rd_dev *rd_dev, u32 page)
अणु
	काष्ठा rd_dev_sg_table *sg_table;
	u32 i, sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				माप(काष्ठा scatterlist));

	i = page / sg_per_table;
	अगर (i < rd_dev->sg_prot_count) अणु
		sg_table = &rd_dev->sg_prot_array[i];
		अगर ((sg_table->page_start_offset <= page) &&
		     (sg_table->page_end_offset >= page))
			वापस sg_table;
	पूर्ण

	pr_err("Unable to locate struct prot rd_dev_sg_table for page: %u\n",
			page);

	वापस शून्य;
पूर्ण

अटल sense_reason_t rd_करो_prot_rw(काष्ठा se_cmd *cmd, bool is_पढ़ो)
अणु
	काष्ठा se_device *se_dev = cmd->se_dev;
	काष्ठा rd_dev *dev = RD_DEV(se_dev);
	काष्ठा rd_dev_sg_table *prot_table;
	काष्ठा scatterlist *prot_sg;
	u32 sectors = cmd->data_length / se_dev->dev_attrib.block_size;
	u32 prot_offset, prot_page;
	u32 prot_npages __maybe_unused;
	u64 पंचांगp;
	sense_reason_t rc = 0;

	पंचांगp = cmd->t_task_lba * se_dev->prot_length;
	prot_offset = करो_भाग(पंचांगp, PAGE_SIZE);
	prot_page = पंचांगp;

	prot_table = rd_get_prot_table(dev, prot_page);
	अगर (!prot_table)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	prot_sg = &prot_table->sg_table[prot_page -
					prot_table->page_start_offset];

	अगर (se_dev->dev_attrib.pi_prot_verअगरy) अणु
		अगर (is_पढ़ो)
			rc = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba, sectors, 0,
					    prot_sg, prot_offset);
		अन्यथा
			rc = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba, sectors, 0,
					    cmd->t_prot_sg, 0);
	पूर्ण
	अगर (!rc)
		sbc_dअगर_copy_prot(cmd, sectors, is_पढ़ो, prot_sg, prot_offset);

	वापस rc;
पूर्ण

अटल sense_reason_t
rd_execute_rw(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
	      क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा se_device *se_dev = cmd->se_dev;
	काष्ठा rd_dev *dev = RD_DEV(se_dev);
	काष्ठा rd_dev_sg_table *table;
	काष्ठा scatterlist *rd_sg;
	काष्ठा sg_mapping_iter m;
	u32 rd_offset;
	u32 rd_size;
	u32 rd_page;
	u32 src_len;
	u64 पंचांगp;
	sense_reason_t rc;

	अगर (dev->rd_flags & RDF_शून्यIO) अणु
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		वापस 0;
	पूर्ण

	पंचांगp = cmd->t_task_lba * se_dev->dev_attrib.block_size;
	rd_offset = करो_भाग(पंचांगp, PAGE_SIZE);
	rd_page = पंचांगp;
	rd_size = cmd->data_length;

	table = rd_get_sg_table(dev, rd_page);
	अगर (!table)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	rd_sg = &table->sg_table[rd_page - table->page_start_offset];

	pr_debug("RD[%u]: %s LBA: %llu, Size: %u Page: %u, Offset: %u\n",
			dev->rd_dev_id,
			data_direction == DMA_FROM_DEVICE ? "Read" : "Write",
			cmd->t_task_lba, rd_size, rd_page, rd_offset);

	अगर (cmd->prot_type && se_dev->dev_attrib.pi_prot_type &&
	    data_direction == DMA_TO_DEVICE) अणु
		rc = rd_करो_prot_rw(cmd, false);
		अगर (rc)
			वापस rc;
	पूर्ण

	src_len = PAGE_SIZE - rd_offset;
	sg_miter_start(&m, sgl, sgl_nents,
			data_direction == DMA_FROM_DEVICE ?
				SG_MITER_TO_SG : SG_MITER_FROM_SG);
	जबतक (rd_size) अणु
		u32 len;
		व्योम *rd_addr;

		sg_miter_next(&m);
		अगर (!(u32)m.length) अणु
			pr_debug("RD[%u]: invalid sgl %p len %zu\n",
				 dev->rd_dev_id, m.addr, m.length);
			sg_miter_stop(&m);
			वापस TCM_INCORRECT_AMOUNT_OF_DATA;
		पूर्ण
		len = min((u32)m.length, src_len);
		अगर (len > rd_size) अणु
			pr_debug("RD[%u]: size underrun page %d offset %d "
				 "size %d\n", dev->rd_dev_id,
				 rd_page, rd_offset, rd_size);
			len = rd_size;
		पूर्ण
		m.consumed = len;

		rd_addr = sg_virt(rd_sg) + rd_offset;

		अगर (data_direction == DMA_FROM_DEVICE)
			स_नकल(m.addr, rd_addr, len);
		अन्यथा
			स_नकल(rd_addr, m.addr, len);

		rd_size -= len;
		अगर (!rd_size)
			जारी;

		src_len -= len;
		अगर (src_len) अणु
			rd_offset += len;
			जारी;
		पूर्ण

		/* rd page completed, next one please */
		rd_page++;
		rd_offset = 0;
		src_len = PAGE_SIZE;
		अगर (rd_page <= table->page_end_offset) अणु
			rd_sg++;
			जारी;
		पूर्ण

		table = rd_get_sg_table(dev, rd_page);
		अगर (!table) अणु
			sg_miter_stop(&m);
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण

		/* since we increment, the first sg entry is correct */
		rd_sg = table->sg_table;
	पूर्ण
	sg_miter_stop(&m);

	अगर (cmd->prot_type && se_dev->dev_attrib.pi_prot_type &&
	    data_direction == DMA_FROM_DEVICE) अणु
		rc = rd_करो_prot_rw(cmd, true);
		अगर (rc)
			वापस rc;
	पूर्ण

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	वापस 0;
पूर्ण

क्रमागत अणु
	Opt_rd_pages, Opt_rd_nullio, Opt_rd_dummy, Opt_err
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_rd_pages, "rd_pages=%d"पूर्ण,
	अणुOpt_rd_nullio, "rd_nullio=%d"पूर्ण,
	अणुOpt_rd_dummy, "rd_dummy=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल sमाप_प्रकार rd_set_configfs_dev_params(काष्ठा se_device *dev,
		स्थिर अक्षर *page, sमाप_प्रकार count)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);
	अक्षर *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;

	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_rd_pages:
			match_पूर्णांक(args, &arg);
			rd_dev->rd_page_count = arg;
			pr_debug("RAMDISK: Referencing Page"
				" Count: %u\n", rd_dev->rd_page_count);
			rd_dev->rd_flags |= RDF_HAS_PAGE_COUNT;
			अवरोध;
		हाल Opt_rd_nullio:
			match_पूर्णांक(args, &arg);
			अगर (arg != 1)
				अवरोध;

			pr_debug("RAMDISK: Setting NULLIO flag: %d\n", arg);
			rd_dev->rd_flags |= RDF_शून्यIO;
			अवरोध;
		हाल Opt_rd_dummy:
			match_पूर्णांक(args, &arg);
			अगर (arg != 1)
				अवरोध;

			pr_debug("RAMDISK: Setting DUMMY flag: %d\n", arg);
			rd_dev->rd_flags |= RDF_DUMMY;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(orig);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rd_show_configfs_dev_params(काष्ठा se_device *dev, अक्षर *b)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

	sमाप_प्रकार bl = प्र_लिखो(b, "TCM RamDisk ID: %u  RamDisk Makeup: rd_mcp\n",
			rd_dev->rd_dev_id);
	bl += प्र_लिखो(b + bl, "        PAGES/PAGE_SIZE: %u*%lu"
			"  SG_table_count: %u  nullio: %d dummy: %d\n",
			rd_dev->rd_page_count,
			PAGE_SIZE, rd_dev->sg_table_count,
			!!(rd_dev->rd_flags & RDF_शून्यIO),
			!!(rd_dev->rd_flags & RDF_DUMMY));
	वापस bl;
पूर्ण

अटल u32 rd_get_device_type(काष्ठा se_device *dev)
अणु
	अगर (RD_DEV(dev)->rd_flags & RDF_DUMMY)
		वापस 0x3f; /* Unknown device type, not connected */
	अन्यथा
		वापस sbc_get_device_type(dev);
पूर्ण

अटल sector_t rd_get_blocks(काष्ठा se_device *dev)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

	अचिन्हित दीर्घ दीर्घ blocks_दीर्घ = ((rd_dev->rd_page_count * PAGE_SIZE) /
			dev->dev_attrib.block_size) - 1;

	वापस blocks_दीर्घ;
पूर्ण

अटल पूर्णांक rd_init_prot(काष्ठा se_device *dev)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

        अगर (!dev->dev_attrib.pi_prot_type)
		वापस 0;

	वापस rd_build_prot_space(rd_dev, dev->prot_length,
				   dev->dev_attrib.block_size);
पूर्ण

अटल व्योम rd_मुक्त_prot(काष्ठा se_device *dev)
अणु
	काष्ठा rd_dev *rd_dev = RD_DEV(dev);

	rd_release_prot_space(rd_dev);
पूर्ण

अटल काष्ठा sbc_ops rd_sbc_ops = अणु
	.execute_rw		= rd_execute_rw,
पूर्ण;

अटल sense_reason_t
rd_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	वापस sbc_parse_cdb(cmd, &rd_sbc_ops);
पूर्ण

अटल स्थिर काष्ठा target_backend_ops rd_mcp_ops = अणु
	.name			= "rd_mcp",
	.inquiry_prod		= "RAMDISK-MCP",
	.inquiry_rev		= RD_MCP_VERSION,
	.attach_hba		= rd_attach_hba,
	.detach_hba		= rd_detach_hba,
	.alloc_device		= rd_alloc_device,
	.configure_device	= rd_configure_device,
	.destroy_device		= rd_destroy_device,
	.मुक्त_device		= rd_मुक्त_device,
	.parse_cdb		= rd_parse_cdb,
	.set_configfs_dev_params = rd_set_configfs_dev_params,
	.show_configfs_dev_params = rd_show_configfs_dev_params,
	.get_device_type	= rd_get_device_type,
	.get_blocks		= rd_get_blocks,
	.init_prot		= rd_init_prot,
	.मुक्त_prot		= rd_मुक्त_prot,
	.tb_dev_attrib_attrs	= sbc_attrib_attrs,
पूर्ण;

पूर्णांक __init rd_module_init(व्योम)
अणु
	वापस transport_backend_रेजिस्टर(&rd_mcp_ops);
पूर्ण

व्योम rd_module_निकास(व्योम)
अणु
	target_backend_unरेजिस्टर(&rd_mcp_ops);
पूर्ण
