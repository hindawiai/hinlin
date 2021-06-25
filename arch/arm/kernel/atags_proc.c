<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/page.h>

काष्ठा buffer अणु
	माप_प्रकार size;
	अक्षर data[];
पूर्ण;

अटल sमाप_प्रकार atags_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा buffer *b = PDE_DATA(file_inode(file));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, b->data, b->size);
पूर्ण

अटल स्थिर काष्ठा proc_ops atags_proc_ops = अणु
	.proc_पढ़ो	= atags_पढ़ो,
	.proc_lseek	= शेष_llseek,
पूर्ण;

#घोषणा BOOT_PARAMS_SIZE 1536
अटल अक्षर __initdata atags_copy[BOOT_PARAMS_SIZE];

व्योम __init save_atags(स्थिर काष्ठा tag *tags)
अणु
	स_नकल(atags_copy, tags, माप(atags_copy));
पूर्ण

अटल पूर्णांक __init init_atags_procfs(व्योम)
अणु
	/*
	 * This cannot go पूर्णांकo save_atags() because kदो_स्मृति and proc करोn't work
	 * yet when it is called.
	 */
	काष्ठा proc_dir_entry *tags_entry;
	काष्ठा tag *tag = (काष्ठा tag *)atags_copy;
	काष्ठा buffer *b;
	माप_प्रकार size;

	अगर (tag->hdr.tag != ATAG_CORE) अणु
		pr_info("No ATAGs?\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (; tag->hdr.size; tag = tag_next(tag))
		;

	/* include the terminating ATAG_NONE */
	size = (अक्षर *)tag - atags_copy + माप(काष्ठा tag_header);

	WARN_ON(tag->hdr.tag != ATAG_NONE);

	b = kदो_स्मृति(माप(*b) + size, GFP_KERNEL);
	अगर (!b)
		जाओ nomem;

	b->size = size;
	स_नकल(b->data, atags_copy, size);

	tags_entry = proc_create_data("atags", 0400, शून्य, &atags_proc_ops, b);
	अगर (!tags_entry)
		जाओ nomem;

	वापस 0;

nomem:
	kमुक्त(b);
	pr_err("Exporting ATAGs: not enough memory\n");

	वापस -ENOMEM;
पूर्ण
arch_initcall(init_atags_procfs);
