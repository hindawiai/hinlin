<शैली गुरु>
/*
 * arch/sh/mm/tlb-debugfs.c
 *
 * debugfs ops क्रम SH-4 ITLB/UTLBs.
 *
 * Copyright (C) 2010  Matt Fleming
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

क्रमागत tlb_type अणु
	TLB_TYPE_ITLB,
	TLB_TYPE_UTLB,
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक bits;
	स्थिर अक्षर *size;
पूर्ण tlb_sizes[] = अणु
	अणु 0x0, "  1KB" पूर्ण,
	अणु 0x1, "  4KB" पूर्ण,
	अणु 0x2, "  8KB" पूर्ण,
	अणु 0x4, " 64KB" पूर्ण,
	अणु 0x5, "256KB" पूर्ण,
	अणु 0x7, "  1MB" पूर्ण,
	अणु 0x8, "  4MB" पूर्ण,
	अणु 0xc, " 64MB" पूर्ण,
पूर्ण;

अटल पूर्णांक tlb_seq_show(काष्ठा seq_file *file, व्योम *iter)
अणु
	अचिन्हित पूर्णांक tlb_type = (अचिन्हित पूर्णांक)file->निजी;
	अचिन्हित दीर्घ addr1, addr2, data1, data2;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mmucr;
	अचिन्हित पूर्णांक nentries, entry;
	अचिन्हित पूर्णांक urb;

	mmucr = __raw_पढ़ोl(MMUCR);
	अगर ((mmucr & 0x1) == 0) अणु
		seq_म_लिखो(file, "address translation disabled\n");
		वापस 0;
	पूर्ण

	अगर (tlb_type == TLB_TYPE_ITLB) अणु
		addr1 = MMU_ITLB_ADDRESS_ARRAY;
		addr2 = MMU_ITLB_ADDRESS_ARRAY2;
		data1 = MMU_ITLB_DATA_ARRAY;
		data2 = MMU_ITLB_DATA_ARRAY2;
		nentries = 4;
	पूर्ण अन्यथा अणु
		addr1 = MMU_UTLB_ADDRESS_ARRAY;
		addr2 = MMU_UTLB_ADDRESS_ARRAY2;
		data1 = MMU_UTLB_DATA_ARRAY;
		data2 = MMU_UTLB_DATA_ARRAY2;
		nentries = 64;
	पूर्ण

	local_irq_save(flags);
	jump_to_uncached();

	urb = (mmucr & MMUCR_URB) >> MMUCR_URB_SHIFT;

	/* Make the "entry >= urb" test fail. */
	अगर (urb == 0)
		urb = MMUCR_URB_NENTRIES + 1;

	अगर (tlb_type == TLB_TYPE_ITLB) अणु
		addr1 = MMU_ITLB_ADDRESS_ARRAY;
		addr2 = MMU_ITLB_ADDRESS_ARRAY2;
		data1 = MMU_ITLB_DATA_ARRAY;
		data2 = MMU_ITLB_DATA_ARRAY2;
		nentries = 4;
	पूर्ण अन्यथा अणु
		addr1 = MMU_UTLB_ADDRESS_ARRAY;
		addr2 = MMU_UTLB_ADDRESS_ARRAY2;
		data1 = MMU_UTLB_DATA_ARRAY;
		data2 = MMU_UTLB_DATA_ARRAY2;
		nentries = 64;
	पूर्ण

	seq_म_लिखो(file, "entry:     vpn        ppn     asid  size valid wired\n");

	क्रम (entry = 0; entry < nentries; entry++) अणु
		अचिन्हित दीर्घ vpn, ppn, asid, size;
		अचिन्हित दीर्घ valid;
		अचिन्हित दीर्घ val;
		स्थिर अक्षर *sz = "    ?";
		पूर्णांक i;

		val = __raw_पढ़ोl(addr1 | (entry << MMU_TLB_ENTRY_SHIFT));
		ctrl_barrier();
		vpn = val & 0xfffffc00;
		valid = val & 0x100;

		val = __raw_पढ़ोl(addr2 | (entry << MMU_TLB_ENTRY_SHIFT));
		ctrl_barrier();
		asid = val & MMU_CONTEXT_ASID_MASK;

		val = __raw_पढ़ोl(data1 | (entry << MMU_TLB_ENTRY_SHIFT));
		ctrl_barrier();
		ppn = (val & 0x0ffffc00) << 4;

		val = __raw_पढ़ोl(data2 | (entry << MMU_TLB_ENTRY_SHIFT));
		ctrl_barrier();
		size = (val & 0xf0) >> 4;

		क्रम (i = 0; i < ARRAY_SIZE(tlb_sizes); i++) अणु
			अगर (tlb_sizes[i].bits == size)
				अवरोध;
		पूर्ण

		अगर (i != ARRAY_SIZE(tlb_sizes))
			sz = tlb_sizes[i].size;

		seq_म_लिखो(file, "%2d:    0x%08lx 0x%08lx %5lu %s   %s     %s\n",
			   entry, vpn, ppn, asid,
			   sz, valid ? "V" : "-",
			   (urb <= entry) ? "W" : "-");
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tlb_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, tlb_seq_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tlb_debugfs_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= tlb_debugfs_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init tlb_debugfs_init(व्योम)
अणु
	debugfs_create_file("itlb", S_IRUSR, arch_debugfs_dir,
			    (व्योम *)TLB_TYPE_ITLB, &tlb_debugfs_fops);
	debugfs_create_file("utlb", S_IRUSR, arch_debugfs_dir,
			    (व्योम *)TLB_TYPE_UTLB, &tlb_debugfs_fops);
	वापस 0;
पूर्ण
module_init(tlb_debugfs_init);

MODULE_LICENSE("GPL v2");
