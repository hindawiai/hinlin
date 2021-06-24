<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* inode.c: /proc/खोलोprom handling routines
 *
 * Copyright (C) 1996-1999 Jakub Jelinek  (jakub@redhat.com)
 * Copyright (C) 1998      Eddie C. Dost  (ecd@skynet.be)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/magic.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>

अटल DEFINE_MUTEX(op_mutex);

#घोषणा OPENPROM_ROOT_INO	0

क्रमागत op_inode_type अणु
	op_inode_node,
	op_inode_prop,
पूर्ण;

जोड़ op_inode_data अणु
	काष्ठा device_node	*node;
	काष्ठा property		*prop;
पूर्ण;

काष्ठा op_inode_info अणु
	काष्ठा inode		vfs_inode;
	क्रमागत op_inode_type	type;
	जोड़ op_inode_data	u;
पूर्ण;

अटल काष्ठा inode *खोलोprom_iget(काष्ठा super_block *sb, ino_t ino);

अटल अंतरभूत काष्ठा op_inode_info *OP_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा op_inode_info, vfs_inode);
पूर्ण

अटल पूर्णांक is_string(अचिन्हित अक्षर *p, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित अक्षर val = p[i];

		अगर ((i && !val) ||
		    (val >= ' ' && val <= '~'))
			जारी;

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक property_show(काष्ठा seq_file *f, व्योम *v)
अणु
	काष्ठा property *prop = f->निजी;
	व्योम *pval;
	पूर्णांक len;

	len = prop->length;
	pval = prop->value;

	अगर (is_string(pval, len)) अणु
		जबतक (len > 0) अणु
			पूर्णांक n = म_माप(pval);

			seq_म_लिखो(f, "%s", (अक्षर *) pval);

			/* Skip over the शून्य byte too.  */
			pval += n + 1;
			len -= n + 1;

			अगर (len > 0)
				seq_म_लिखो(f, " + ");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (len & 3) अणु
			जबतक (len) अणु
				len--;
				अगर (len)
					seq_म_लिखो(f, "%02x.",
						   *(अचिन्हित अक्षर *) pval);
				अन्यथा
					seq_म_लिखो(f, "%02x",
						   *(अचिन्हित अक्षर *) pval);
				pval++;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (len >= 4) अणु
				len -= 4;

				अगर (len)
					seq_म_लिखो(f, "%08x.",
						   *(अचिन्हित पूर्णांक *) pval);
				अन्यथा
					seq_म_लिखो(f, "%08x",
						   *(अचिन्हित पूर्णांक *) pval);
				pval += 4;
			पूर्ण
		पूर्ण
	पूर्ण
	seq_म_लिखो(f, "\n");

	वापस 0;
पूर्ण

अटल व्योम *property_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	अगर (*pos == 0)
		वापस pos;
	वापस शून्य;
पूर्ण

अटल व्योम *property_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम property_stop(काष्ठा seq_file *f, व्योम *v)
अणु
	/* Nothing to करो */
पूर्ण

अटल स्थिर काष्ठा seq_operations property_op = अणु
	.start		= property_start,
	.next		= property_next,
	.stop		= property_stop,
	.show		= property_show
पूर्ण;

अटल पूर्णांक property_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा op_inode_info *oi = OP_I(inode);
	पूर्णांक ret;

	BUG_ON(oi->type != op_inode_prop);

	ret = seq_खोलो(file, &property_op);
	अगर (!ret) अणु
		काष्ठा seq_file *m = file->निजी_data;
		m->निजी = oi->u.prop;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations खोलोpromfs_prop_ops = अणु
	.खोलो		= property_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल पूर्णांक खोलोpromfs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

अटल स्थिर काष्ठा file_operations खोलोprom_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= खोलोpromfs_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल काष्ठा dentry *खोलोpromfs_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);

अटल स्थिर काष्ठा inode_operations खोलोprom_inode_operations = अणु
	.lookup		= खोलोpromfs_lookup,
पूर्ण;

अटल काष्ठा dentry *खोलोpromfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा op_inode_info *ent_oi, *oi = OP_I(dir);
	काष्ठा device_node *dp, *child;
	काष्ठा property *prop;
	क्रमागत op_inode_type ent_type;
	जोड़ op_inode_data ent_data;
	स्थिर अक्षर *name;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक ino;
	पूर्णांक len;
	
	BUG_ON(oi->type != op_inode_node);

	dp = oi->u.node;

	name = dentry->d_name.name;
	len = dentry->d_name.len;

	mutex_lock(&op_mutex);

	child = dp->child;
	जबतक (child) अणु
		स्थिर अक्षर *node_name = kbasename(child->full_name);
		पूर्णांक n = म_माप(node_name);

		अगर (len == n &&
		    !म_भेदन(node_name, name, len)) अणु
			ent_type = op_inode_node;
			ent_data.node = child;
			ino = child->unique_id;
			जाओ found;
		पूर्ण
		child = child->sibling;
	पूर्ण

	prop = dp->properties;
	जबतक (prop) अणु
		पूर्णांक n = म_माप(prop->name);

		अगर (len == n && !म_भेदन(prop->name, name, len)) अणु
			ent_type = op_inode_prop;
			ent_data.prop = prop;
			ino = prop->unique_id;
			जाओ found;
		पूर्ण

		prop = prop->next;
	पूर्ण

	mutex_unlock(&op_mutex);
	वापस ERR_PTR(-ENOENT);

found:
	inode = खोलोprom_iget(dir->i_sb, ino);
	mutex_unlock(&op_mutex);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (inode->i_state & I_NEW) अणु
		inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
		ent_oi = OP_I(inode);
		ent_oi->type = ent_type;
		ent_oi->u = ent_data;

		चयन (ent_type) अणु
		हाल op_inode_node:
			inode->i_mode = S_IFसूची | S_IRUGO | S_IXUGO;
			inode->i_op = &खोलोprom_inode_operations;
			inode->i_fop = &खोलोprom_operations;
			set_nlink(inode, 2);
			अवरोध;
		हाल op_inode_prop:
			अगर (of_node_name_eq(dp, "options") && (len == 17) &&
			    !म_भेदन (name, "security-password", 17))
				inode->i_mode = S_IFREG | S_IRUSR | S_IWUSR;
			अन्यथा
				inode->i_mode = S_IFREG | S_IRUGO;
			inode->i_fop = &खोलोpromfs_prop_ops;
			set_nlink(inode, 1);
			inode->i_size = ent_oi->u.prop->length;
			अवरोध;
		पूर्ण
		unlock_new_inode(inode);
	पूर्ण

	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक खोलोpromfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा op_inode_info *oi = OP_I(inode);
	काष्ठा device_node *dp = oi->u.node;
	काष्ठा device_node *child;
	काष्ठा property *prop;
	पूर्णांक i;

	mutex_lock(&op_mutex);
	
	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit(ctx, ".", 1, inode->i_ino, DT_सूची))
			जाओ out;
		ctx->pos = 1;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (!dir_emit(ctx, "..", 2,
			    (dp->parent == शून्य ?
			     OPENPROM_ROOT_INO :
			     dp->parent->unique_id), DT_सूची))
			जाओ out;
		ctx->pos = 2;
	पूर्ण
	i = ctx->pos - 2;

	/* First, the children nodes as directories.  */
	child = dp->child;
	जबतक (i && child) अणु
		child = child->sibling;
		i--;
	पूर्ण
	जबतक (child) अणु
		अगर (!dir_emit(ctx,
			    kbasename(child->full_name),
			    म_माप(kbasename(child->full_name)),
			    child->unique_id, DT_सूची))
			जाओ out;

		ctx->pos++;
		child = child->sibling;
	पूर्ण

	/* Next, the properties as files.  */
	prop = dp->properties;
	जबतक (i && prop) अणु
		prop = prop->next;
		i--;
	पूर्ण
	जबतक (prop) अणु
		अगर (!dir_emit(ctx, prop->name, म_माप(prop->name),
			    prop->unique_id, DT_REG))
			जाओ out;

		ctx->pos++;
		prop = prop->next;
	पूर्ण

out:
	mutex_unlock(&op_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा kmem_cache *op_inode_cachep;

अटल काष्ठा inode *खोलोprom_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा op_inode_info *oi;

	oi = kmem_cache_alloc(op_inode_cachep, GFP_KERNEL);
	अगर (!oi)
		वापस शून्य;

	वापस &oi->vfs_inode;
पूर्ण

अटल व्योम खोलोprom_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(op_inode_cachep, OP_I(inode));
पूर्ण

अटल काष्ठा inode *खोलोprom_iget(काष्ठा super_block *sb, ino_t ino)
अणु
	काष्ठा inode *inode = iget_locked(sb, ino);
	अगर (!inode)
		inode = ERR_PTR(-ENOMEM);
	वापस inode;
पूर्ण

अटल पूर्णांक खोलोprom_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_NOATIME;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations खोलोprom_sops = अणु
	.alloc_inode	= खोलोprom_alloc_inode,
	.मुक्त_inode	= खोलोprom_मुक्त_inode,
	.statfs		= simple_statfs,
	.remount_fs	= खोलोprom_remount,
पूर्ण;

अटल पूर्णांक खोलोprom_fill_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *root_inode;
	काष्ठा op_inode_info *oi;
	पूर्णांक ret;

	s->s_flags |= SB_NOATIME;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = OPENPROM_SUPER_MAGIC;
	s->s_op = &खोलोprom_sops;
	s->s_समय_gran = 1;
	root_inode = खोलोprom_iget(s, OPENPROM_ROOT_INO);
	अगर (IS_ERR(root_inode)) अणु
		ret = PTR_ERR(root_inode);
		जाओ out_no_root;
	पूर्ण

	root_inode->i_mसमय = root_inode->i_aसमय =
		root_inode->i_स_समय = current_समय(root_inode);
	root_inode->i_op = &खोलोprom_inode_operations;
	root_inode->i_fop = &खोलोprom_operations;
	root_inode->i_mode = S_IFसूची | S_IRUGO | S_IXUGO;
	oi = OP_I(root_inode);
	oi->type = op_inode_node;
	oi->u.node = of_find_node_by_path("/");
	unlock_new_inode(root_inode);

	s->s_root = d_make_root(root_inode);
	अगर (!s->s_root)
		जाओ out_no_root_dentry;
	वापस 0;

out_no_root_dentry:
	ret = -ENOMEM;
out_no_root:
	prपूर्णांकk("openprom_fill_super: get root inode failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक खोलोpromfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, खोलोprom_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations खोलोpromfs_context_ops = अणु
	.get_tree	= खोलोpromfs_get_tree,
पूर्ण;

अटल पूर्णांक खोलोpromfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &खोलोpromfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type खोलोprom_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "openpromfs",
	.init_fs_context = खोलोpromfs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;
MODULE_ALIAS_FS("openpromfs");

अटल व्योम op_inode_init_once(व्योम *data)
अणु
	काष्ठा op_inode_info *oi = (काष्ठा op_inode_info *) data;

	inode_init_once(&oi->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_खोलोprom_fs(व्योम)
अणु
	पूर्णांक err;

	op_inode_cachep = kmem_cache_create("op_inode_cache",
					    माप(काष्ठा op_inode_info),
					    0,
					    (SLAB_RECLAIM_ACCOUNT |
					     SLAB_MEM_SPREAD | SLAB_ACCOUNT),
					    op_inode_init_once);
	अगर (!op_inode_cachep)
		वापस -ENOMEM;

	err = रेजिस्टर_fileप्रणाली(&खोलोprom_fs_type);
	अगर (err)
		kmem_cache_destroy(op_inode_cachep);

	वापस err;
पूर्ण

अटल व्योम __निकास निकास_खोलोprom_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&खोलोprom_fs_type);
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(op_inode_cachep);
पूर्ण

module_init(init_खोलोprom_fs)
module_निकास(निकास_खोलोprom_fs)
MODULE_LICENSE("GPL");
