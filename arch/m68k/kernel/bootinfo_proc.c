<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based on arch/arm/kernel/atags_proc.c
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/byteorder.h>


अटल अक्षर bootinfo_पंचांगp[1536] __initdata;

अटल व्योम *bootinfo_copy;
अटल माप_प्रकार bootinfo_size;

अटल sमाप_प्रकार bootinfo_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, bootinfo_copy,
				       bootinfo_size);
पूर्ण

अटल स्थिर काष्ठा proc_ops bootinfo_proc_ops = अणु
	.proc_पढ़ो	= bootinfo_पढ़ो,
	.proc_lseek	= शेष_llseek,
पूर्ण;

व्योम __init save_bootinfo(स्थिर काष्ठा bi_record *bi)
अणु
	स्थिर व्योम *start = bi;
	माप_प्रकार size = माप(bi->tag);

	जबतक (be16_to_cpu(bi->tag) != BI_LAST) अणु
		uपूर्णांक16_t n = be16_to_cpu(bi->size);
		size += n;
		bi = (काष्ठा bi_record *)((अचिन्हित दीर्घ)bi + n);
	पूर्ण

	अगर (size > माप(bootinfo_पंचांगp)) अणु
		pr_err("Cannot save %zu bytes of bootinfo\n", size);
		वापस;
	पूर्ण

	pr_info("Saving %zu bytes of bootinfo\n", size);
	स_नकल(bootinfo_पंचांगp, start, size);
	bootinfo_size = size;
पूर्ण

अटल पूर्णांक __init init_bootinfo_procfs(व्योम)
अणु
	/*
	 * This cannot go पूर्णांकo save_bootinfo() because kदो_स्मृति and proc करोn't
	 * work yet when it is called.
	 */
	काष्ठा proc_dir_entry *pde;

	अगर (!bootinfo_size)
		वापस -EINVAL;

	bootinfo_copy = kmemdup(bootinfo_पंचांगp, bootinfo_size, GFP_KERNEL);
	अगर (!bootinfo_copy)
		वापस -ENOMEM;

	pde = proc_create_data("bootinfo", 0400, शून्य, &bootinfo_proc_ops, शून्य);
	अगर (!pde) अणु
		kमुक्त(bootinfo_copy);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(init_bootinfo_procfs);
