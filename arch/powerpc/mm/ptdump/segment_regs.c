<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018, Christophe Leroy CS S.I.
 * <christophe.leroy@c-s.fr>
 *
 * This dumps the content of Segment Registers
 */

#समावेश <यंत्र/debugfs.h>

अटल व्योम seg_show(काष्ठा seq_file *m, पूर्णांक i)
अणु
	u32 val = mfsr(i << 28);

	seq_म_लिखो(m, "0x%01x0000000-0x%01xfffffff ", i, i);
	seq_म_लिखो(m, "Kern key %d ", (val >> 30) & 1);
	seq_म_लिखो(m, "User key %d ", (val >> 29) & 1);
	अगर (val & 0x80000000) अणु
		seq_म_लिखो(m, "Device 0x%03x", (val >> 20) & 0x1ff);
		seq_म_लिखो(m, "-0x%05x", val & 0xfffff);
	पूर्ण अन्यथा अणु
		अगर (val & 0x10000000)
			seq_माला_दो(m, "No Exec ");
		seq_म_लिखो(m, "VSID 0x%06x", val & 0xffffff);
	पूर्ण
	seq_माला_दो(m, "\n");
पूर्ण

अटल पूर्णांक sr_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	seq_माला_दो(m, "---[ User Segments ]---\n");
	क्रम (i = 0; i < TASK_SIZE >> 28; i++)
		seg_show(m, i);

	seq_माला_दो(m, "\n---[ Kernel Segments ]---\n");
	क्रम (; i < 16; i++)
		seg_show(m, i);

	वापस 0;
पूर्ण

अटल पूर्णांक sr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sr_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations sr_fops = अणु
	.खोलो		= sr_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init sr_init(व्योम)
अणु
	debugfs_create_file("segment_registers", 0400, घातerpc_debugfs_root,
			    शून्य, &sr_fops);
	वापस 0;
पूर्ण
device_initcall(sr_init);
