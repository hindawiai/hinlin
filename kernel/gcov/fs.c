<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  This code exports profiling data as debugfs files to userspace.
 *
 *    Copyright IBM Corp. 2009
 *    Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *
 *    Uses gcc-पूर्णांकernal data definitions.
 *    Based on the gcov-kernel patch by:
 *		 Hubertus Franke <frankeh@us.ibm.com>
 *		 Nigel Hinds <nhinds@us.ibm.com>
 *		 Rajan Ravindran <rajancr@us.ibm.com>
 *		 Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *		 Paul Larson
 *		 Yi CDL Yang
 */

#घोषणा pr_fmt(fmt)	"gcov: " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mm.h>
#समावेश "gcov.h"

/**
 * काष्ठा gcov_node - represents a debugfs entry
 * @list: list head क्रम child node list
 * @children: child nodes
 * @all: list head क्रम list of all nodes
 * @parent: parent node
 * @loaded_info: array of poपूर्णांकers to profiling data sets क्रम loaded object
 *   files.
 * @num_loaded: number of profiling data sets क्रम loaded object files.
 * @unloaded_info: accumulated copy of profiling data sets क्रम unloaded
 *   object files. Used only when gcov_persist=1.
 * @dentry: मुख्य debugfs entry, either a directory or data file
 * @links: associated symbolic links
 * @name: data file basename
 *
 * काष्ठा gcov_node represents an entity within the gcov/ subdirectory
 * of debugfs. There are directory and data file nodes. The latter represent
 * the actual synthesized data file plus any associated symbolic links which
 * are needed by the gcov tool to work correctly.
 */
काष्ठा gcov_node अणु
	काष्ठा list_head list;
	काष्ठा list_head children;
	काष्ठा list_head all;
	काष्ठा gcov_node *parent;
	काष्ठा gcov_info **loaded_info;
	काष्ठा gcov_info *unloaded_info;
	काष्ठा dentry *dentry;
	काष्ठा dentry **links;
	पूर्णांक num_loaded;
	अक्षर name[];
पूर्ण;

अटल स्थिर अक्षर objtree[] = OBJTREE;
अटल स्थिर अक्षर srctree[] = SRCTREE;
अटल काष्ठा gcov_node root_node;
अटल LIST_HEAD(all_head);
अटल DEFINE_MUTEX(node_lock);

/* If non-zero, keep copies of profiling data क्रम unloaded modules. */
अटल पूर्णांक gcov_persist = 1;

अटल पूर्णांक __init gcov_persist_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(str, 0, &val)) अणु
		pr_warn("invalid gcov_persist parameter '%s'\n", str);
		वापस 0;
	पूर्ण
	gcov_persist = val;
	pr_info("setting gcov_persist to %d\n", gcov_persist);

	वापस 1;
पूर्ण
__setup("gcov_persist=", gcov_persist_setup);

#घोषणा ITER_STRIDE	PAGE_SIZE

/**
 * काष्ठा gcov_iterator - specअगरies current file position in logical records
 * @info: associated profiling data
 * @buffer: buffer containing file data
 * @size: size of buffer
 * @pos: current position in file
 */
काष्ठा gcov_iterator अणु
	काष्ठा gcov_info *info;
	माप_प्रकार size;
	loff_t pos;
	अक्षर buffer[];
पूर्ण;

/**
 * gcov_iter_new - allocate and initialize profiling data iterator
 * @info: profiling data set to be iterated
 *
 * Return file iterator on success, %शून्य otherwise.
 */
अटल काष्ठा gcov_iterator *gcov_iter_new(काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_iterator *iter;
	माप_प्रकार size;

	/* Dry-run to get the actual buffer size. */
	size = convert_to_gcda(शून्य, info);

	iter = kvदो_स्मृति(काष्ठा_size(iter, buffer, size), GFP_KERNEL);
	अगर (!iter)
		वापस शून्य;

	iter->info = info;
	iter->size = size;
	convert_to_gcda(iter->buffer, info);

	वापस iter;
पूर्ण


/**
 * gcov_iter_मुक्त - मुक्त iterator data
 * @iter: file iterator
 */
अटल व्योम gcov_iter_मुक्त(काष्ठा gcov_iterator *iter)
अणु
	kvमुक्त(iter);
पूर्ण

/**
 * gcov_iter_get_info - वापस profiling data set क्रम given file iterator
 * @iter: file iterator
 */
अटल काष्ठा gcov_info *gcov_iter_get_info(काष्ठा gcov_iterator *iter)
अणु
	वापस iter->info;
पूर्ण

/**
 * gcov_iter_start - reset file iterator to starting position
 * @iter: file iterator
 */
अटल व्योम gcov_iter_start(काष्ठा gcov_iterator *iter)
अणु
	iter->pos = 0;
पूर्ण

/**
 * gcov_iter_next - advance file iterator to next logical record
 * @iter: file iterator
 *
 * Return zero अगर new position is valid, non-zero अगर iterator has reached end.
 */
अटल पूर्णांक gcov_iter_next(काष्ठा gcov_iterator *iter)
अणु
	अगर (iter->pos < iter->size)
		iter->pos += ITER_STRIDE;

	अगर (iter->pos >= iter->size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * gcov_iter_ग_लिखो - ग_लिखो data क्रम current pos to seq_file
 * @iter: file iterator
 * @seq: seq_file handle
 *
 * Return zero on success, non-zero otherwise.
 */
अटल पूर्णांक gcov_iter_ग_लिखो(काष्ठा gcov_iterator *iter, काष्ठा seq_file *seq)
अणु
	माप_प्रकार len;

	अगर (iter->pos >= iter->size)
		वापस -EINVAL;

	len = ITER_STRIDE;
	अगर (iter->pos + len > iter->size)
		len = iter->size - iter->pos;

	seq_ग_लिखो(seq, iter->buffer + iter->pos, len);

	वापस 0;
पूर्ण

/*
 * seq_file.start() implementation क्रम gcov data files. Note that the
 * gcov_iterator पूर्णांकerface is deचिन्हित to be more restrictive than seq_file
 * (no start from arbitrary position, etc.), to simplअगरy the iterator
 * implementation.
 */
अटल व्योम *gcov_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	loff_t i;

	gcov_iter_start(seq->निजी);
	क्रम (i = 0; i < *pos; i++) अणु
		अगर (gcov_iter_next(seq->निजी))
			वापस शून्य;
	पूर्ण
	वापस seq->निजी;
पूर्ण

/* seq_file.next() implementation क्रम gcov data files. */
अटल व्योम *gcov_seq_next(काष्ठा seq_file *seq, व्योम *data, loff_t *pos)
अणु
	काष्ठा gcov_iterator *iter = data;

	(*pos)++;
	अगर (gcov_iter_next(iter))
		वापस शून्य;

	वापस iter;
पूर्ण

/* seq_file.show() implementation क्रम gcov data files. */
अटल पूर्णांक gcov_seq_show(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा gcov_iterator *iter = data;

	अगर (gcov_iter_ग_लिखो(iter, seq))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम gcov_seq_stop(काष्ठा seq_file *seq, व्योम *data)
अणु
	/* Unused. */
पूर्ण

अटल स्थिर काष्ठा seq_operations gcov_seq_ops = अणु
	.start	= gcov_seq_start,
	.next	= gcov_seq_next,
	.show	= gcov_seq_show,
	.stop	= gcov_seq_stop,
पूर्ण;

/*
 * Return a profiling data set associated with the given node. This is
 * either a data set क्रम a loaded object file or a data set copy in हाल
 * all associated object files have been unloaded.
 */
अटल काष्ठा gcov_info *get_node_info(काष्ठा gcov_node *node)
अणु
	अगर (node->num_loaded > 0)
		वापस node->loaded_info[0];

	वापस node->unloaded_info;
पूर्ण

/*
 * Return a newly allocated profiling data set which contains the sum of
 * all profiling data associated with the given node.
 */
अटल काष्ठा gcov_info *get_accumulated_info(काष्ठा gcov_node *node)
अणु
	काष्ठा gcov_info *info;
	पूर्णांक i = 0;

	अगर (node->unloaded_info)
		info = gcov_info_dup(node->unloaded_info);
	अन्यथा
		info = gcov_info_dup(node->loaded_info[i++]);
	अगर (!info)
		वापस शून्य;
	क्रम (; i < node->num_loaded; i++)
		gcov_info_add(info, node->loaded_info[i]);

	वापस info;
पूर्ण

/*
 * खोलो() implementation क्रम gcov data files. Create a copy of the profiling
 * data set and initialize the iterator and seq_file पूर्णांकerface.
 */
अटल पूर्णांक gcov_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gcov_node *node = inode->i_निजी;
	काष्ठा gcov_iterator *iter;
	काष्ठा seq_file *seq;
	काष्ठा gcov_info *info;
	पूर्णांक rc = -ENOMEM;

	mutex_lock(&node_lock);
	/*
	 * Read from a profiling data copy to minimize reference tracking
	 * complनिकासy and concurrent access and to keep accumulating multiple
	 * profiling data sets associated with one node simple.
	 */
	info = get_accumulated_info(node);
	अगर (!info)
		जाओ out_unlock;
	iter = gcov_iter_new(info);
	अगर (!iter)
		जाओ err_मुक्त_info;
	rc = seq_खोलो(file, &gcov_seq_ops);
	अगर (rc)
		जाओ err_मुक्त_iter_info;
	seq = file->निजी_data;
	seq->निजी = iter;
out_unlock:
	mutex_unlock(&node_lock);
	वापस rc;

err_मुक्त_iter_info:
	gcov_iter_मुक्त(iter);
err_मुक्त_info:
	gcov_info_मुक्त(info);
	जाओ out_unlock;
पूर्ण

/*
 * release() implementation क्रम gcov data files. Release resources allocated
 * by खोलो().
 */
अटल पूर्णांक gcov_seq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gcov_iterator *iter;
	काष्ठा gcov_info *info;
	काष्ठा seq_file *seq;

	seq = file->निजी_data;
	iter = seq->निजी;
	info = gcov_iter_get_info(iter);
	gcov_iter_मुक्त(iter);
	gcov_info_मुक्त(info);
	seq_release(inode, file);

	वापस 0;
पूर्ण

/*
 * Find a node by the associated data file name. Needs to be called with
 * node_lock held.
 */
अटल काष्ठा gcov_node *get_node_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा gcov_node *node;
	काष्ठा gcov_info *info;

	list_क्रम_each_entry(node, &all_head, all) अणु
		info = get_node_info(node);
		अगर (info && (म_भेद(gcov_info_filename(info), name) == 0))
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Reset all profiling data associated with the specअगरied node.
 */
अटल व्योम reset_node(काष्ठा gcov_node *node)
अणु
	पूर्णांक i;

	अगर (node->unloaded_info)
		gcov_info_reset(node->unloaded_info);
	क्रम (i = 0; i < node->num_loaded; i++)
		gcov_info_reset(node->loaded_info[i]);
पूर्ण

अटल व्योम हटाओ_node(काष्ठा gcov_node *node);

/*
 * ग_लिखो() implementation क्रम gcov data files. Reset profiling data क्रम the
 * corresponding file. If all associated object files have been unloaded,
 * हटाओ the debug fs node as well.
 */
अटल sमाप_प्रकार gcov_seq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *addr,
			      माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा seq_file *seq;
	काष्ठा gcov_info *info;
	काष्ठा gcov_node *node;

	seq = file->निजी_data;
	info = gcov_iter_get_info(seq->निजी);
	mutex_lock(&node_lock);
	node = get_node_by_name(gcov_info_filename(info));
	अगर (node) अणु
		/* Reset counts or हटाओ node क्रम unloaded modules. */
		अगर (node->num_loaded == 0)
			हटाओ_node(node);
		अन्यथा
			reset_node(node);
	पूर्ण
	/* Reset counts क्रम खोलो file. */
	gcov_info_reset(info);
	mutex_unlock(&node_lock);

	वापस len;
पूर्ण

/*
 * Given a string <path> representing a file path of क्रमmat:
 *   path/to/file.gcda
 * स्थिरruct and वापस a new string:
 *   <dir/>path/to/file.<ext>
 */
अटल अक्षर *link_target(स्थिर अक्षर *dir, स्थिर अक्षर *path, स्थिर अक्षर *ext)
अणु
	अक्षर *target;
	अक्षर *old_ext;
	अक्षर *copy;

	copy = kstrdup(path, GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;
	old_ext = म_खोजप(copy, '.');
	अगर (old_ext)
		*old_ext = '\0';
	अगर (dir)
		target = kaप्र_लिखो(GFP_KERNEL, "%s/%s.%s", dir, copy, ext);
	अन्यथा
		target = kaप्र_लिखो(GFP_KERNEL, "%s.%s", copy, ext);
	kमुक्त(copy);

	वापस target;
पूर्ण

/*
 * Conकाष्ठा a string representing the symbolic link target क्रम the given
 * gcov data file name and link type. Depending on the link type and the
 * location of the data file, the link target can either poपूर्णांक to a
 * subdirectory of srctree, objtree or in an बाह्यal location.
 */
अटल अक्षर *get_link_target(स्थिर अक्षर *filename, स्थिर काष्ठा gcov_link *ext)
अणु
	स्थिर अक्षर *rel;
	अक्षर *result;

	अगर (म_भेदन(filename, objtree, म_माप(objtree)) == 0) अणु
		rel = filename + म_माप(objtree) + 1;
		अगर (ext->dir == SRC_TREE)
			result = link_target(srctree, rel, ext->ext);
		अन्यथा
			result = link_target(objtree, rel, ext->ext);
	पूर्ण अन्यथा अणु
		/* External compilation. */
		result = link_target(शून्य, filename, ext->ext);
	पूर्ण

	वापस result;
पूर्ण

#घोषणा SKEW_PREFIX	".tmp_"

/*
 * For a filename .पंचांगp_filename.ext वापस filename.ext. Needed to compensate
 * क्रम filename skewing caused by the mod-versioning mechanism.
 */
अटल स्थिर अक्षर *deskew(स्थिर अक्षर *basename)
अणु
	अगर (म_भेदन(basename, SKEW_PREFIX, माप(SKEW_PREFIX) - 1) == 0)
		वापस basename + माप(SKEW_PREFIX) - 1;
	वापस basename;
पूर्ण

/*
 * Create links to additional files (usually .c and .gcno files) which the
 * gcov tool expects to find in the same directory as the gcov data file.
 */
अटल व्योम add_links(काष्ठा gcov_node *node, काष्ठा dentry *parent)
अणु
	स्थिर अक्षर *basename;
	अक्षर *target;
	पूर्णांक num;
	पूर्णांक i;

	क्रम (num = 0; gcov_link[num].ext; num++)
		/* Nothing. */;
	node->links = kसुस्मृति(num, माप(काष्ठा dentry *), GFP_KERNEL);
	अगर (!node->links)
		वापस;
	क्रम (i = 0; i < num; i++) अणु
		target = get_link_target(
				gcov_info_filename(get_node_info(node)),
				&gcov_link[i]);
		अगर (!target)
			जाओ out_err;
		basename = kbasename(target);
		अगर (basename == target)
			जाओ out_err;
		node->links[i] = debugfs_create_symlink(deskew(basename),
							parent,	target);
		kमुक्त(target);
	पूर्ण

	वापस;
out_err:
	kमुक्त(target);
	जबतक (i-- > 0)
		debugfs_हटाओ(node->links[i]);
	kमुक्त(node->links);
	node->links = शून्य;
पूर्ण

अटल स्थिर काष्ठा file_operations gcov_data_fops = अणु
	.खोलो		= gcov_seq_खोलो,
	.release	= gcov_seq_release,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.ग_लिखो		= gcov_seq_ग_लिखो,
पूर्ण;

/* Basic initialization of a new node. */
अटल व्योम init_node(काष्ठा gcov_node *node, काष्ठा gcov_info *info,
		      स्थिर अक्षर *name, काष्ठा gcov_node *parent)
अणु
	INIT_LIST_HEAD(&node->list);
	INIT_LIST_HEAD(&node->children);
	INIT_LIST_HEAD(&node->all);
	अगर (node->loaded_info) अणु
		node->loaded_info[0] = info;
		node->num_loaded = 1;
	पूर्ण
	node->parent = parent;
	अगर (name)
		म_नकल(node->name, name);
पूर्ण

/*
 * Create a new node and associated debugfs entry. Needs to be called with
 * node_lock held.
 */
अटल काष्ठा gcov_node *new_node(काष्ठा gcov_node *parent,
				  काष्ठा gcov_info *info, स्थिर अक्षर *name)
अणु
	काष्ठा gcov_node *node;

	node = kzalloc(माप(काष्ठा gcov_node) + म_माप(name) + 1, GFP_KERNEL);
	अगर (!node)
		जाओ err_nomem;
	अगर (info) अणु
		node->loaded_info = kसुस्मृति(1, माप(काष्ठा gcov_info *),
					   GFP_KERNEL);
		अगर (!node->loaded_info)
			जाओ err_nomem;
	पूर्ण
	init_node(node, info, name, parent);
	/* Dअगरferentiate between gcov data file nodes and directory nodes. */
	अगर (info) अणु
		node->dentry = debugfs_create_file(deskew(node->name), 0600,
					parent->dentry, node, &gcov_data_fops);
	पूर्ण अन्यथा
		node->dentry = debugfs_create_dir(node->name, parent->dentry);
	अगर (info)
		add_links(node, parent->dentry);
	list_add(&node->list, &parent->children);
	list_add(&node->all, &all_head);

	वापस node;

err_nomem:
	kमुक्त(node);
	pr_warn("out of memory\n");
	वापस शून्य;
पूर्ण

/* Remove symbolic links associated with node. */
अटल व्योम हटाओ_links(काष्ठा gcov_node *node)
अणु
	पूर्णांक i;

	अगर (!node->links)
		वापस;
	क्रम (i = 0; gcov_link[i].ext; i++)
		debugfs_हटाओ(node->links[i]);
	kमुक्त(node->links);
	node->links = शून्य;
पूर्ण

/*
 * Remove node from all lists and debugfs and release associated resources.
 * Needs to be called with node_lock held.
 */
अटल व्योम release_node(काष्ठा gcov_node *node)
अणु
	list_del(&node->list);
	list_del(&node->all);
	debugfs_हटाओ(node->dentry);
	हटाओ_links(node);
	kमुक्त(node->loaded_info);
	अगर (node->unloaded_info)
		gcov_info_मुक्त(node->unloaded_info);
	kमुक्त(node);
पूर्ण

/* Release node and empty parents. Needs to be called with node_lock held. */
अटल व्योम हटाओ_node(काष्ठा gcov_node *node)
अणु
	काष्ठा gcov_node *parent;

	जबतक ((node != &root_node) && list_empty(&node->children)) अणु
		parent = node->parent;
		release_node(node);
		node = parent;
	पूर्ण
पूर्ण

/*
 * Find child node with given basename. Needs to be called with node_lock
 * held.
 */
अटल काष्ठा gcov_node *get_child_by_name(काष्ठा gcov_node *parent,
					   स्थिर अक्षर *name)
अणु
	काष्ठा gcov_node *node;

	list_क्रम_each_entry(node, &parent->children, list) अणु
		अगर (म_भेद(node->name, name) == 0)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * ग_लिखो() implementation क्रम reset file. Reset all profiling data to zero
 * and हटाओ nodes क्रम which all associated object files are unloaded.
 */
अटल sमाप_प्रकार reset_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *addr,
			   माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा gcov_node *node;

	mutex_lock(&node_lock);
restart:
	list_क्रम_each_entry(node, &all_head, all) अणु
		अगर (node->num_loaded > 0)
			reset_node(node);
		अन्यथा अगर (list_empty(&node->children)) अणु
			हटाओ_node(node);
			/* Several nodes may have gone - restart loop. */
			जाओ restart;
		पूर्ण
	पूर्ण
	mutex_unlock(&node_lock);

	वापस len;
पूर्ण

/* पढ़ो() implementation क्रम reset file. Unused. */
अटल sमाप_प्रकार reset_पढ़ो(काष्ठा file *file, अक्षर __user *addr, माप_प्रकार len,
			  loff_t *pos)
अणु
	/* Allow पढ़ो operation so that a recursive copy won't fail. */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gcov_reset_fops = अणु
	.ग_लिखो	= reset_ग_लिखो,
	.पढ़ो	= reset_पढ़ो,
	.llseek = noop_llseek,
पूर्ण;

/*
 * Create a node क्रम a given profiling data set and add it to all lists and
 * debugfs. Needs to be called with node_lock held.
 */
अटल व्योम add_node(काष्ठा gcov_info *info)
अणु
	अक्षर *filename;
	अक्षर *curr;
	अक्षर *next;
	काष्ठा gcov_node *parent;
	काष्ठा gcov_node *node;

	filename = kstrdup(gcov_info_filename(info), GFP_KERNEL);
	अगर (!filename)
		वापस;
	parent = &root_node;
	/* Create directory nodes aदीर्घ the path. */
	क्रम (curr = filename; (next = म_अक्षर(curr, '/')); curr = next + 1) अणु
		अगर (curr == next)
			जारी;
		*next = 0;
		अगर (म_भेद(curr, ".") == 0)
			जारी;
		अगर (म_भेद(curr, "..") == 0) अणु
			अगर (!parent->parent)
				जाओ err_हटाओ;
			parent = parent->parent;
			जारी;
		पूर्ण
		node = get_child_by_name(parent, curr);
		अगर (!node) अणु
			node = new_node(parent, शून्य, curr);
			अगर (!node)
				जाओ err_हटाओ;
		पूर्ण
		parent = node;
	पूर्ण
	/* Create file node. */
	node = new_node(parent, info, curr);
	अगर (!node)
		जाओ err_हटाओ;
out:
	kमुक्त(filename);
	वापस;

err_हटाओ:
	हटाओ_node(parent);
	जाओ out;
पूर्ण

/*
 * Associate a profiling data set with an existing node. Needs to be called
 * with node_lock held.
 */
अटल व्योम add_info(काष्ठा gcov_node *node, काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_info **loaded_info;
	पूर्णांक num = node->num_loaded;

	/*
	 * Prepare new array. This is करोne first to simplअगरy cleanup in
	 * हाल the new data set is incompatible, the node only contains
	 * unloaded data sets and there's not enough memory क्रम the array.
	 */
	loaded_info = kसुस्मृति(num + 1, माप(काष्ठा gcov_info *), GFP_KERNEL);
	अगर (!loaded_info) अणु
		pr_warn("could not add '%s' (out of memory)\n",
			gcov_info_filename(info));
		वापस;
	पूर्ण
	स_नकल(loaded_info, node->loaded_info,
	       num * माप(काष्ठा gcov_info *));
	loaded_info[num] = info;
	/* Check अगर the new data set is compatible. */
	अगर (num == 0) अणु
		/*
		 * A module was unloaded, modअगरied and reloaded. The new
		 * data set replaces the copy of the last one.
		 */
		अगर (!gcov_info_is_compatible(node->unloaded_info, info)) अणु
			pr_warn("discarding saved data for %s "
				"(incompatible version)\n",
				gcov_info_filename(info));
			gcov_info_मुक्त(node->unloaded_info);
			node->unloaded_info = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Two dअगरferent versions of the same object file are loaded.
		 * The initial one takes precedence.
		 */
		अगर (!gcov_info_is_compatible(node->loaded_info[0], info)) अणु
			pr_warn("could not add '%s' (incompatible "
				"version)\n", gcov_info_filename(info));
			kमुक्त(loaded_info);
			वापस;
		पूर्ण
	पूर्ण
	/* Overग_लिखो previous array. */
	kमुक्त(node->loaded_info);
	node->loaded_info = loaded_info;
	node->num_loaded = num + 1;
पूर्ण

/*
 * Return the index of a profiling data set associated with a node.
 */
अटल पूर्णांक get_info_index(काष्ठा gcov_node *node, काष्ठा gcov_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < node->num_loaded; i++) अणु
		अगर (node->loaded_info[i] == info)
			वापस i;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/*
 * Save the data of a profiling data set which is being unloaded.
 */
अटल व्योम save_info(काष्ठा gcov_node *node, काष्ठा gcov_info *info)
अणु
	अगर (node->unloaded_info)
		gcov_info_add(node->unloaded_info, info);
	अन्यथा अणु
		node->unloaded_info = gcov_info_dup(info);
		अगर (!node->unloaded_info) अणु
			pr_warn("could not save data for '%s' "
				"(out of memory)\n",
				gcov_info_filename(info));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Disassociate a profiling data set from a node. Needs to be called with
 * node_lock held.
 */
अटल व्योम हटाओ_info(काष्ठा gcov_node *node, काष्ठा gcov_info *info)
अणु
	पूर्णांक i;

	i = get_info_index(node, info);
	अगर (i < 0) अणु
		pr_warn("could not remove '%s' (not found)\n",
			gcov_info_filename(info));
		वापस;
	पूर्ण
	अगर (gcov_persist)
		save_info(node, info);
	/* Shrink array. */
	node->loaded_info[i] = node->loaded_info[node->num_loaded - 1];
	node->num_loaded--;
	अगर (node->num_loaded > 0)
		वापस;
	/* Last loaded data set was हटाओd. */
	kमुक्त(node->loaded_info);
	node->loaded_info = शून्य;
	node->num_loaded = 0;
	अगर (!node->unloaded_info)
		हटाओ_node(node);
पूर्ण

/*
 * Callback to create/हटाओ profiling files when code compiled with
 * -fprofile-arcs is loaded/unloaded.
 */
व्योम gcov_event(क्रमागत gcov_action action, काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_node *node;

	mutex_lock(&node_lock);
	node = get_node_by_name(gcov_info_filename(info));
	चयन (action) अणु
	हाल GCOV_ADD:
		अगर (node)
			add_info(node, info);
		अन्यथा
			add_node(info);
		अवरोध;
	हाल GCOV_REMOVE:
		अगर (node)
			हटाओ_info(node, info);
		अन्यथा अणु
			pr_warn("could not remove '%s' (not found)\n",
				gcov_info_filename(info));
		पूर्ण
		अवरोध;
	पूर्ण
	mutex_unlock(&node_lock);
पूर्ण

/* Create debugfs entries. */
अटल __init पूर्णांक gcov_fs_init(व्योम)
अणु
	init_node(&root_node, शून्य, शून्य, शून्य);
	/*
	 * /sys/kernel/debug/gcov will be parent क्रम the reset control file
	 * and all profiling files.
	 */
	root_node.dentry = debugfs_create_dir("gcov", शून्य);
	/*
	 * Create reset file which resets all profiling counts when written
	 * to.
	 */
	debugfs_create_file("reset", 0600, root_node.dentry, शून्य,
			    &gcov_reset_fops);
	/* Replay previous events to get our fs hierarchy up-to-date. */
	gcov_enable_events();
	वापस 0;
पूर्ण
device_initcall(gcov_fs_init);
