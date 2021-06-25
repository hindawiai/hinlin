<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Architecture specअगरic debugfs files
 *
 * Copyright (C) 2007, Intel Corp.
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/setup.h>

काष्ठा dentry *arch_debugfs_dir;
EXPORT_SYMBOL(arch_debugfs_dir);

#अगर_घोषित CONFIG_DEBUG_BOOT_PARAMS
काष्ठा setup_data_node अणु
	u64 paddr;
	u32 type;
	u32 len;
पूर्ण;

अटल sमाप_प्रकार setup_data_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा setup_data_node *node = file->निजी_data;
	अचिन्हित दीर्घ reमुख्य;
	loff_t pos = *ppos;
	व्योम *p;
	u64 pa;

	अगर (pos < 0)
		वापस -EINVAL;

	अगर (pos >= node->len)
		वापस 0;

	अगर (count > node->len - pos)
		count = node->len - pos;

	pa = node->paddr + pos;

	/* Is it direct data or invalid indirect one? */
	अगर (!(node->type & SETUP_INसूचीECT) || node->type == SETUP_INसूचीECT)
		pa += माप(काष्ठा setup_data);

	p = memremap(pa, count, MEMREMAP_WB);
	अगर (!p)
		वापस -ENOMEM;

	reमुख्य = copy_to_user(user_buf, p, count);

	memunmap(p);

	अगर (reमुख्य)
		वापस -EFAULT;

	*ppos = pos + count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_setup_data = अणु
	.पढ़ो		= setup_data_पढ़ो,
	.खोलो		= simple_खोलो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल व्योम __init
create_setup_data_node(काष्ठा dentry *parent, पूर्णांक no,
		       काष्ठा setup_data_node *node)
अणु
	काष्ठा dentry *d;
	अक्षर buf[16];

	प्र_लिखो(buf, "%d", no);
	d = debugfs_create_dir(buf, parent);

	debugfs_create_x32("type", S_IRUGO, d, &node->type);
	debugfs_create_file("data", S_IRUGO, d, node, &fops_setup_data);
पूर्ण

अटल पूर्णांक __init create_setup_data_nodes(काष्ठा dentry *parent)
अणु
	काष्ठा setup_data_node *node;
	काष्ठा setup_data *data;
	पूर्णांक error;
	काष्ठा dentry *d;
	u64 pa_data;
	पूर्णांक no = 0;

	d = debugfs_create_dir("setup_data", parent);

	pa_data = boot_params.hdr.setup_data;

	जबतक (pa_data) अणु
		node = kदो_स्मृति(माप(*node), GFP_KERNEL);
		अगर (!node) अणु
			error = -ENOMEM;
			जाओ err_dir;
		पूर्ण

		data = memremap(pa_data, माप(*data), MEMREMAP_WB);
		अगर (!data) अणु
			kमुक्त(node);
			error = -ENOMEM;
			जाओ err_dir;
		पूर्ण

		अगर (data->type == SETUP_INसूचीECT &&
		    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT) अणु
			node->paddr = ((काष्ठा setup_indirect *)data->data)->addr;
			node->type  = ((काष्ठा setup_indirect *)data->data)->type;
			node->len   = ((काष्ठा setup_indirect *)data->data)->len;
		पूर्ण अन्यथा अणु
			node->paddr = pa_data;
			node->type  = data->type;
			node->len   = data->len;
		पूर्ण

		create_setup_data_node(d, no, node);
		pa_data = data->next;

		memunmap(data);
		no++;
	पूर्ण

	वापस 0;

err_dir:
	debugfs_हटाओ_recursive(d);
	वापस error;
पूर्ण

अटल काष्ठा debugfs_blob_wrapper boot_params_blob = अणु
	.data		= &boot_params,
	.size		= माप(boot_params),
पूर्ण;

अटल पूर्णांक __init boot_params_kdebugfs_init(व्योम)
अणु
	काष्ठा dentry *dbp;
	पूर्णांक error;

	dbp = debugfs_create_dir("boot_params", arch_debugfs_dir);

	debugfs_create_x16("version", S_IRUGO, dbp, &boot_params.hdr.version);
	debugfs_create_blob("data", S_IRUGO, dbp, &boot_params_blob);

	error = create_setup_data_nodes(dbp);
	अगर (error)
		debugfs_हटाओ_recursive(dbp);

	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_BOOT_PARAMS */

अटल पूर्णांक __init arch_kdebugfs_init(व्योम)
अणु
	पूर्णांक error = 0;

	arch_debugfs_dir = debugfs_create_dir("x86", शून्य);

#अगर_घोषित CONFIG_DEBUG_BOOT_PARAMS
	error = boot_params_kdebugfs_init();
#पूर्ण_अगर

	वापस error;
पूर्ण
arch_initcall(arch_kdebugfs_init);
