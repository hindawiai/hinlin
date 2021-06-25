<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#घोषणा BOOTROM_OFFSET	0x10118000
#घोषणा BOOTROM_SIZE	0x8000

अटल व्योम __iomem *membase = (व्योम __iomem *) KSEG1ADDR(BOOTROM_OFFSET);

अटल पूर्णांक bootrom_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	seq_ग_लिखो(s, membase, BOOTROM_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक bootrom_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, bootrom_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations bootrom_file_ops = अणु
	.खोलो		= bootrom_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init bootrom_setup(व्योम)
अणु
	debugfs_create_file("bootrom", 0444, शून्य, शून्य, &bootrom_file_ops);
	वापस 0;
पूर्ण

postcore_initcall(bootrom_setup);
