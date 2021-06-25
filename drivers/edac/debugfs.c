<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "edac_module.h"

अटल काष्ठा dentry *edac_debugfs;

अटल sमाप_प्रकार edac_fake_inject_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *data,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = file->निजी_data;
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	अटल क्रमागत hw_event_mc_err_type type;
	u16 errcount = mci->fake_inject_count;

	अगर (!errcount)
		errcount = 1;

	type = mci->fake_inject_ue ? HW_EVENT_ERR_UNCORRECTED
				   : HW_EVENT_ERR_CORRECTED;

	prपूर्णांकk(KERN_DEBUG
	       "Generating %d %s fake error%s to %d.%d.%d to test core handling. NOTE: this won't test the driver-specific decoding logic.\n",
		errcount,
		(type == HW_EVENT_ERR_UNCORRECTED) ? "UE" : "CE",
		errcount > 1 ? "s" : "",
		mci->fake_inject_layer[0],
		mci->fake_inject_layer[1],
		mci->fake_inject_layer[2]
	       );
	edac_mc_handle_error(type, mci, errcount, 0, 0, 0,
			     mci->fake_inject_layer[0],
			     mci->fake_inject_layer[1],
			     mci->fake_inject_layer[2],
			     "FAKE ERROR", "for EDAC testing only");

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debug_fake_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = edac_fake_inject_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

व्योम __init edac_debugfs_init(व्योम)
अणु
	edac_debugfs = debugfs_create_dir("edac", शून्य);
पूर्ण

व्योम edac_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(edac_debugfs);
पूर्ण

व्योम edac_create_debugfs_nodes(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा dentry *parent;
	अक्षर name[80];
	पूर्णांक i;

	parent = debugfs_create_dir(mci->dev.kobj.name, edac_debugfs);

	क्रम (i = 0; i < mci->n_layers; i++) अणु
		प्र_लिखो(name, "fake_inject_%s",
			     edac_layer_name[mci->layers[i].type]);
		debugfs_create_u8(name, S_IRUGO | S_IWUSR, parent,
				  &mci->fake_inject_layer[i]);
	पूर्ण

	debugfs_create_bool("fake_inject_ue", S_IRUGO | S_IWUSR, parent,
			    &mci->fake_inject_ue);

	debugfs_create_u16("fake_inject_count", S_IRUGO | S_IWUSR, parent,
			   &mci->fake_inject_count);

	debugfs_create_file("fake_inject", S_IWUSR, parent, &mci->dev,
			    &debug_fake_inject_fops);

	mci->debugfs = parent;
पूर्ण

/* Create a toplevel dir under EDAC's debugfs hierarchy */
काष्ठा dentry *edac_debugfs_create_dir(स्थिर अक्षर *स_नाम)
अणु
	अगर (!edac_debugfs)
		वापस शून्य;

	वापस debugfs_create_dir(स_नाम, edac_debugfs);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_dir);

/* Create a toplevel dir under EDAC's debugfs hierarchy with parent @parent */
काष्ठा dentry *
edac_debugfs_create_dir_at(स्थिर अक्षर *स_नाम, काष्ठा dentry *parent)
अणु
	वापस debugfs_create_dir(स_नाम, parent);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_dir_at);

/*
 * Create a file under EDAC's hierarchy or a sub-hierarchy:
 *
 * @name: file name
 * @mode: file permissions
 * @parent: parent dentry. If शून्य, it becomes the toplevel EDAC dir
 * @data: निजी data of caller
 * @fops: file operations of this file
 */
काष्ठा dentry *
edac_debugfs_create_file(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			 व्योम *data, स्थिर काष्ठा file_operations *fops)
अणु
	अगर (!parent)
		parent = edac_debugfs;

	वापस debugfs_create_file(name, mode, parent, data, fops);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_file);

/* Wrapper क्रम debugfs_create_x8() */
व्योम edac_debugfs_create_x8(स्थिर अक्षर *name, umode_t mode,
			    काष्ठा dentry *parent, u8 *value)
अणु
	अगर (!parent)
		parent = edac_debugfs;

	debugfs_create_x8(name, mode, parent, value);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_x8);

/* Wrapper क्रम debugfs_create_x16() */
व्योम edac_debugfs_create_x16(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, u16 *value)
अणु
	अगर (!parent)
		parent = edac_debugfs;

	debugfs_create_x16(name, mode, parent, value);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_x16);

/* Wrapper क्रम debugfs_create_x32() */
व्योम edac_debugfs_create_x32(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, u32 *value)
अणु
	अगर (!parent)
		parent = edac_debugfs;

	debugfs_create_x32(name, mode, parent, value);
पूर्ण
EXPORT_SYMBOL_GPL(edac_debugfs_create_x32);
