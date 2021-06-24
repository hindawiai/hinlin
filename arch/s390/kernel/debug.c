<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   S/390 debug facility
 *
 *    Copyright IBM Corp. 1999, 2020
 *
 *    Author(s): Michael Holzheu (holzheu@de.ibm.com),
 *		 Holger Smolinski (Holger.Smolinski@de.ibm.com)
 *
 *    Bugreports to: <Linux390@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "s390dbf"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/debug.h>

#घोषणा DEBUG_PROLOG_ENTRY -1

#घोषणा ALL_AREAS 0 /* copy all debug areas */
#घोषणा NO_AREAS  1 /* copy no debug areas */

/* प्रकारs */

प्रकार काष्ठा file_निजी_info अणु
	loff_t offset;			/* offset of last पढ़ो in file */
	पूर्णांक    act_area;		/* number of last क्रमmated area */
	पूर्णांक    act_page;		/* act page in given area */
	पूर्णांक    act_entry;		/* last क्रमmated entry (offset */
					/* relative to beginning of last */
					/* क्रमmated page) */
	माप_प्रकार act_entry_offset;	/* up to this offset we copied */
					/* in last पढ़ो the last क्रमmated */
					/* entry to userland */
	अक्षर   temp_buf[2048];		/* buffer क्रम output */
	debug_info_t *debug_info_org;	/* original debug inक्रमmation */
	debug_info_t *debug_info_snap;	/* snapshot of debug inक्रमmation */
	काष्ठा debug_view *view;	/* used view of debug info */
पूर्ण file_निजी_info_t;

प्रकार काष्ठा अणु
	अक्षर *string;
	/*
	 * This assumes that all args are converted पूर्णांकo दीर्घs
	 * on L/390 this is the हाल क्रम all types of parameter
	 * except of भग्नs, and दीर्घ दीर्घ (32 bit)
	 *
	 */
	दीर्घ args[0];
पूर्ण debug_प्र_लिखो_entry_t;

/* पूर्णांकernal function prototyes */

अटल पूर्णांक debug_init(व्योम);
अटल sमाप_प्रकार debug_output(काष्ठा file *file, अक्षर __user *user_buf,
			    माप_प्रकार user_len, loff_t *offset);
अटल sमाप_प्रकार debug_input(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			   माप_प्रकार user_len, loff_t *offset);
अटल पूर्णांक debug_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक debug_बंद(काष्ठा inode *inode, काष्ठा file *file);
अटल debug_info_t *debug_info_create(स्थिर अक्षर *name, पूर्णांक pages_per_area,
				       पूर्णांक nr_areas, पूर्णांक buf_size, umode_t mode);
अटल व्योम debug_info_get(debug_info_t *);
अटल व्योम debug_info_put(debug_info_t *);
अटल पूर्णांक debug_prolog_level_fn(debug_info_t *id,
				 काष्ठा debug_view *view, अक्षर *out_buf);
अटल पूर्णांक debug_input_level_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_buf_size, loff_t *offset);
अटल पूर्णांक debug_prolog_pages_fn(debug_info_t *id,
				 काष्ठा debug_view *view, अक्षर *out_buf);
अटल पूर्णांक debug_input_pages_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_buf_size, loff_t *offset);
अटल पूर्णांक debug_input_flush_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_buf_size, loff_t *offset);
अटल पूर्णांक debug_hex_ascii_क्रमmat_fn(debug_info_t *id, काष्ठा debug_view *view,
				     अक्षर *out_buf, स्थिर अक्षर *in_buf);
अटल पूर्णांक debug_प्र_लिखो_क्रमmat_fn(debug_info_t *id, काष्ठा debug_view *view,
				   अक्षर *out_buf, debug_प्र_लिखो_entry_t *curr_event);

/* globals */

काष्ठा debug_view debug_hex_ascii_view = अणु
	"hex_ascii",
	शून्य,
	&debug_dflt_header_fn,
	&debug_hex_ascii_क्रमmat_fn,
	शून्य,
	शून्य
पूर्ण;
EXPORT_SYMBOL(debug_hex_ascii_view);

अटल काष्ठा debug_view debug_level_view = अणु
	"level",
	&debug_prolog_level_fn,
	शून्य,
	शून्य,
	&debug_input_level_fn,
	शून्य
पूर्ण;

अटल काष्ठा debug_view debug_pages_view = अणु
	"pages",
	&debug_prolog_pages_fn,
	शून्य,
	शून्य,
	&debug_input_pages_fn,
	शून्य
पूर्ण;

अटल काष्ठा debug_view debug_flush_view = अणु
	"flush",
	शून्य,
	शून्य,
	शून्य,
	&debug_input_flush_fn,
	शून्य
पूर्ण;

काष्ठा debug_view debug_प्र_लिखो_view = अणु
	"sprintf",
	शून्य,
	&debug_dflt_header_fn,
	(debug_क्रमmat_proc_t *)&debug_प्र_लिखो_क्रमmat_fn,
	शून्य,
	शून्य
पूर्ण;
EXPORT_SYMBOL(debug_प्र_लिखो_view);

/* used by dump analysis tools to determine version of debug feature */
अटल अचिन्हित पूर्णांक __used debug_feature_version = __DEBUG_FEATURE_VERSION;

/* अटल globals */

अटल debug_info_t *debug_area_first;
अटल debug_info_t *debug_area_last;
अटल DEFINE_MUTEX(debug_mutex);

अटल पूर्णांक initialized;
अटल पूर्णांक debug_critical;

अटल स्थिर काष्ठा file_operations debug_file_ops = अणु
	.owner	 = THIS_MODULE,
	.पढ़ो	 = debug_output,
	.ग_लिखो	 = debug_input,
	.खोलो	 = debug_खोलो,
	.release = debug_बंद,
	.llseek  = no_llseek,
पूर्ण;

अटल काष्ठा dentry *debug_debugfs_root_entry;

/* functions */

/*
 * debug_areas_alloc
 * - Debug areas are implemented as a threedimensonal array:
 *   areas[areanumber][pagक्रमागतber][pageoffset]
 */

अटल debug_entry_t ***debug_areas_alloc(पूर्णांक pages_per_area, पूर्णांक nr_areas)
अणु
	debug_entry_t ***areas;
	पूर्णांक i, j;

	areas = kदो_स्मृति_array(nr_areas, माप(debug_entry_t **), GFP_KERNEL);
	अगर (!areas)
		जाओ fail_दो_स्मृति_areas;
	क्रम (i = 0; i < nr_areas; i++) अणु
		/* GFP_NOWARN to aव्योम user triggerable WARN, we handle fails */
		areas[i] = kदो_स्मृति_array(pages_per_area,
					 माप(debug_entry_t *),
					 GFP_KERNEL | __GFP_NOWARN);
		अगर (!areas[i])
			जाओ fail_दो_स्मृति_areas2;
		क्रम (j = 0; j < pages_per_area; j++) अणु
			areas[i][j] = kzalloc(PAGE_SIZE, GFP_KERNEL);
			अगर (!areas[i][j]) अणु
				क्रम (j--; j >= 0 ; j--)
					kमुक्त(areas[i][j]);
				kमुक्त(areas[i]);
				जाओ fail_दो_स्मृति_areas2;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस areas;

fail_दो_स्मृति_areas2:
	क्रम (i--; i >= 0; i--) अणु
		क्रम (j = 0; j < pages_per_area; j++)
			kमुक्त(areas[i][j]);
		kमुक्त(areas[i]);
	पूर्ण
	kमुक्त(areas);
fail_दो_स्मृति_areas:
	वापस शून्य;
पूर्ण

/*
 * debug_info_alloc
 * - alloc new debug-info
 */
अटल debug_info_t *debug_info_alloc(स्थिर अक्षर *name, पूर्णांक pages_per_area,
				      पूर्णांक nr_areas, पूर्णांक buf_size, पूर्णांक level,
				      पूर्णांक mode)
अणु
	debug_info_t *rc;

	/* alloc everything */
	rc = kदो_स्मृति(माप(debug_info_t), GFP_KERNEL);
	अगर (!rc)
		जाओ fail_दो_स्मृति_rc;
	rc->active_entries = kसुस्मृति(nr_areas, माप(पूर्णांक), GFP_KERNEL);
	अगर (!rc->active_entries)
		जाओ fail_दो_स्मृति_active_entries;
	rc->active_pages = kसुस्मृति(nr_areas, माप(पूर्णांक), GFP_KERNEL);
	अगर (!rc->active_pages)
		जाओ fail_दो_स्मृति_active_pages;
	अगर ((mode == ALL_AREAS) && (pages_per_area != 0)) अणु
		rc->areas = debug_areas_alloc(pages_per_area, nr_areas);
		अगर (!rc->areas)
			जाओ fail_दो_स्मृति_areas;
	पूर्ण अन्यथा अणु
		rc->areas = शून्य;
	पूर्ण

	/* initialize members */
	spin_lock_init(&rc->lock);
	rc->pages_per_area = pages_per_area;
	rc->nr_areas	   = nr_areas;
	rc->active_area    = 0;
	rc->level	   = level;
	rc->buf_size	   = buf_size;
	rc->entry_size	   = माप(debug_entry_t) + buf_size;
	strlcpy(rc->name, name, माप(rc->name));
	स_रखो(rc->views, 0, DEBUG_MAX_VIEWS * माप(काष्ठा debug_view *));
	स_रखो(rc->debugfs_entries, 0, DEBUG_MAX_VIEWS * माप(काष्ठा dentry *));
	refcount_set(&(rc->ref_count), 0);

	वापस rc;

fail_दो_स्मृति_areas:
	kमुक्त(rc->active_pages);
fail_दो_स्मृति_active_pages:
	kमुक्त(rc->active_entries);
fail_दो_स्मृति_active_entries:
	kमुक्त(rc);
fail_दो_स्मृति_rc:
	वापस शून्य;
पूर्ण

/*
 * debug_areas_मुक्त
 * - मुक्त all debug areas
 */
अटल व्योम debug_areas_मुक्त(debug_info_t *db_info)
अणु
	पूर्णांक i, j;

	अगर (!db_info->areas)
		वापस;
	क्रम (i = 0; i < db_info->nr_areas; i++) अणु
		क्रम (j = 0; j < db_info->pages_per_area; j++)
			kमुक्त(db_info->areas[i][j]);
		kमुक्त(db_info->areas[i]);
	पूर्ण
	kमुक्त(db_info->areas);
	db_info->areas = शून्य;
पूर्ण

/*
 * debug_info_मुक्त
 * - मुक्त memory debug-info
 */
अटल व्योम debug_info_मुक्त(debug_info_t *db_info)
अणु
	debug_areas_मुक्त(db_info);
	kमुक्त(db_info->active_entries);
	kमुक्त(db_info->active_pages);
	kमुक्त(db_info);
पूर्ण

/*
 * debug_info_create
 * - create new debug-info
 */

अटल debug_info_t *debug_info_create(स्थिर अक्षर *name, पूर्णांक pages_per_area,
				       पूर्णांक nr_areas, पूर्णांक buf_size, umode_t mode)
अणु
	debug_info_t *rc;

	rc = debug_info_alloc(name, pages_per_area, nr_areas, buf_size,
			      DEBUG_DEFAULT_LEVEL, ALL_AREAS);
	अगर (!rc)
		जाओ out;

	rc->mode = mode & ~S_IFMT;

	/* create root directory */
	rc->debugfs_root_entry = debugfs_create_dir(rc->name,
						    debug_debugfs_root_entry);

	/* append new element to linked list */
	अगर (!debug_area_first) अणु
		/* first element in list */
		debug_area_first = rc;
		rc->prev = शून्य;
	पूर्ण अन्यथा अणु
		/* append element to end of list */
		debug_area_last->next = rc;
		rc->prev = debug_area_last;
	पूर्ण
	debug_area_last = rc;
	rc->next = शून्य;

	refcount_set(&rc->ref_count, 1);
out:
	वापस rc;
पूर्ण

/*
 * debug_info_copy
 * - copy debug-info
 */
अटल debug_info_t *debug_info_copy(debug_info_t *in, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;
	debug_info_t *rc;
	पूर्णांक i, j;

	/* get a consistent copy of the debug areas */
	करो अणु
		rc = debug_info_alloc(in->name, in->pages_per_area,
			in->nr_areas, in->buf_size, in->level, mode);
		spin_lock_irqsave(&in->lock, flags);
		अगर (!rc)
			जाओ out;
		/* has something changed in the meanसमय ? */
		अगर ((rc->pages_per_area == in->pages_per_area) &&
		    (rc->nr_areas == in->nr_areas)) अणु
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&in->lock, flags);
		debug_info_मुक्त(rc);
	पूर्ण जबतक (1);

	अगर (mode == NO_AREAS)
		जाओ out;

	क्रम (i = 0; i < in->nr_areas; i++) अणु
		क्रम (j = 0; j < in->pages_per_area; j++)
			स_नकल(rc->areas[i][j], in->areas[i][j], PAGE_SIZE);
	पूर्ण
out:
	spin_unlock_irqrestore(&in->lock, flags);
	वापस rc;
पूर्ण

/*
 * debug_info_get
 * - increments reference count क्रम debug-info
 */
अटल व्योम debug_info_get(debug_info_t *db_info)
अणु
	अगर (db_info)
		refcount_inc(&db_info->ref_count);
पूर्ण

/*
 * debug_info_put:
 * - decreases reference count क्रम debug-info and मुक्तs it अगर necessary
 */
अटल व्योम debug_info_put(debug_info_t *db_info)
अणु
	पूर्णांक i;

	अगर (!db_info)
		वापस;
	अगर (refcount_dec_and_test(&db_info->ref_count)) अणु
		क्रम (i = 0; i < DEBUG_MAX_VIEWS; i++) अणु
			अगर (!db_info->views[i])
				जारी;
			debugfs_हटाओ(db_info->debugfs_entries[i]);
		पूर्ण
		debugfs_हटाओ(db_info->debugfs_root_entry);
		अगर (db_info == debug_area_first)
			debug_area_first = db_info->next;
		अगर (db_info == debug_area_last)
			debug_area_last = db_info->prev;
		अगर (db_info->prev)
			db_info->prev->next = db_info->next;
		अगर (db_info->next)
			db_info->next->prev = db_info->prev;
		debug_info_मुक्त(db_info);
	पूर्ण
पूर्ण

/*
 * debug_क्रमmat_entry:
 * - क्रमmat one debug entry and वापस size of क्रमmated data
 */
अटल पूर्णांक debug_क्रमmat_entry(file_निजी_info_t *p_info)
अणु
	debug_info_t *id_snap	= p_info->debug_info_snap;
	काष्ठा debug_view *view = p_info->view;
	debug_entry_t *act_entry;
	माप_प्रकार len = 0;

	अगर (p_info->act_entry == DEBUG_PROLOG_ENTRY) अणु
		/* prपूर्णांक prolog */
		अगर (view->prolog_proc)
			len += view->prolog_proc(id_snap, view, p_info->temp_buf);
		जाओ out;
	पूर्ण
	अगर (!id_snap->areas) /* this is true, अगर we have a prolog only view */
		जाओ out;    /* or अगर 'pages_per_area' is 0 */
	act_entry = (debug_entry_t *) ((अक्षर *)id_snap->areas[p_info->act_area]
				       [p_info->act_page] + p_info->act_entry);

	अगर (act_entry->घड़ी == 0LL)
		जाओ out; /* empty entry */
	अगर (view->header_proc)
		len += view->header_proc(id_snap, view, p_info->act_area,
					 act_entry, p_info->temp_buf + len);
	अगर (view->क्रमmat_proc)
		len += view->क्रमmat_proc(id_snap, view, p_info->temp_buf + len,
					 DEBUG_DATA(act_entry));
out:
	वापस len;
पूर्ण

/*
 * debug_next_entry:
 * - जाओ next entry in p_info
 */
अटल अंतरभूत पूर्णांक debug_next_entry(file_निजी_info_t *p_info)
अणु
	debug_info_t *id;

	id = p_info->debug_info_snap;
	अगर (p_info->act_entry == DEBUG_PROLOG_ENTRY) अणु
		p_info->act_entry = 0;
		p_info->act_page  = 0;
		जाओ out;
	पूर्ण
	अगर (!id->areas)
		वापस 1;
	p_info->act_entry += id->entry_size;
	/* चयन to next page, अगर we reached the end of the page  */
	अगर (p_info->act_entry > (PAGE_SIZE - id->entry_size)) अणु
		/* next page */
		p_info->act_entry = 0;
		p_info->act_page += 1;
		अगर ((p_info->act_page % id->pages_per_area) == 0) अणु
			/* next area */
			p_info->act_area++;
			p_info->act_page = 0;
		पूर्ण
		अगर (p_info->act_area >= id->nr_areas)
			वापस 1;
	पूर्ण
out:
	वापस 0;
पूर्ण

/*
 * debug_output:
 * - called क्रम user पढ़ो()
 * - copies क्रमmated debug entries to the user buffer
 */
अटल sमाप_प्रकार debug_output(काष्ठा file *file,		/* file descriptor */
			    अक्षर __user *user_buf,	/* user buffer */
			    माप_प्रकार len,			/* length of buffer */
			    loff_t *offset)		/* offset in the file */
अणु
	माप_प्रकार count = 0;
	माप_प्रकार entry_offset;
	file_निजी_info_t *p_info;

	p_info = (file_निजी_info_t *) file->निजी_data;
	अगर (*offset != p_info->offset)
		वापस -EPIPE;
	अगर (p_info->act_area >= p_info->debug_info_snap->nr_areas)
		वापस 0;
	entry_offset = p_info->act_entry_offset;
	जबतक (count < len) अणु
		पूर्णांक क्रमmatted_line_residue;
		पूर्णांक क्रमmatted_line_size;
		पूर्णांक user_buf_residue;
		माप_प्रकार copy_size;

		क्रमmatted_line_size = debug_क्रमmat_entry(p_info);
		क्रमmatted_line_residue = क्रमmatted_line_size - entry_offset;
		user_buf_residue = len-count;
		copy_size = min(user_buf_residue, क्रमmatted_line_residue);
		अगर (copy_size) अणु
			अगर (copy_to_user(user_buf + count, p_info->temp_buf
					 + entry_offset, copy_size))
				वापस -EFAULT;
			count += copy_size;
			entry_offset += copy_size;
		पूर्ण
		अगर (copy_size == क्रमmatted_line_residue) अणु
			entry_offset = 0;
			अगर (debug_next_entry(p_info))
				जाओ out;
		पूर्ण
	पूर्ण
out:
	p_info->offset		 = *offset + count;
	p_info->act_entry_offset = entry_offset;
	*offset = p_info->offset;
	वापस count;
पूर्ण

/*
 * debug_input:
 * - called क्रम user ग_लिखो()
 * - calls input function of view
 */
अटल sमाप_प्रकार debug_input(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			   माप_प्रकार length, loff_t *offset)
अणु
	file_निजी_info_t *p_info;
	पूर्णांक rc = 0;

	mutex_lock(&debug_mutex);
	p_info = ((file_निजी_info_t *) file->निजी_data);
	अगर (p_info->view->input_proc) अणु
		rc = p_info->view->input_proc(p_info->debug_info_org,
					      p_info->view, file, user_buf,
					      length, offset);
	पूर्ण अन्यथा अणु
		rc = -EPERM;
	पूर्ण
	mutex_unlock(&debug_mutex);
	वापस rc; /* number of input अक्षरacters */
पूर्ण

/*
 * debug_खोलो:
 * - called क्रम user खोलो()
 * - copies क्रमmated output to निजी_data area of the file
 *   handle
 */
अटल पूर्णांक debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	debug_info_t *debug_info, *debug_info_snapshot;
	file_निजी_info_t *p_info;
	पूर्णांक i, rc = 0;

	mutex_lock(&debug_mutex);
	debug_info = file_inode(file)->i_निजी;
	/* find debug view */
	क्रम (i = 0; i < DEBUG_MAX_VIEWS; i++) अणु
		अगर (!debug_info->views[i])
			जारी;
		अन्यथा अगर (debug_info->debugfs_entries[i] == file->f_path.dentry)
			जाओ found; /* found view ! */
	पूर्ण
	/* no entry found */
	rc = -EINVAL;
	जाओ out;

found:

	/* Make snapshot of current debug areas to get it consistent.	  */
	/* To copy all the areas is only needed, अगर we have a view which  */
	/* क्रमmats the debug areas. */

	अगर (!debug_info->views[i]->क्रमmat_proc && !debug_info->views[i]->header_proc)
		debug_info_snapshot = debug_info_copy(debug_info, NO_AREAS);
	अन्यथा
		debug_info_snapshot = debug_info_copy(debug_info, ALL_AREAS);

	अगर (!debug_info_snapshot) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	p_info = kदो_स्मृति(माप(file_निजी_info_t), GFP_KERNEL);
	अगर (!p_info) अणु
		debug_info_मुक्त(debug_info_snapshot);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	p_info->offset = 0;
	p_info->debug_info_snap = debug_info_snapshot;
	p_info->debug_info_org	= debug_info;
	p_info->view = debug_info->views[i];
	p_info->act_area = 0;
	p_info->act_page = 0;
	p_info->act_entry = DEBUG_PROLOG_ENTRY;
	p_info->act_entry_offset = 0;
	file->निजी_data = p_info;
	debug_info_get(debug_info);
	nonseekable_खोलो(inode, file);
out:
	mutex_unlock(&debug_mutex);
	वापस rc;
पूर्ण

/*
 * debug_बंद:
 * - called क्रम user बंद()
 * - deletes  निजी_data area of the file handle
 */
अटल पूर्णांक debug_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file_निजी_info_t *p_info;

	p_info = (file_निजी_info_t *) file->निजी_data;
	अगर (p_info->debug_info_snap)
		debug_info_मुक्त(p_info->debug_info_snap);
	debug_info_put(p_info->debug_info_org);
	kमुक्त(file->निजी_data);
	वापस 0; /* success */
पूर्ण

/**
 * debug_रेजिस्टर_mode() - creates and initializes debug area.
 *
 * @name:	Name of debug log (e.g. used क्रम debugfs entry)
 * @pages_per_area:	Number of pages, which will be allocated per area
 * @nr_areas:	Number of debug areas
 * @buf_size:	Size of data area in each debug entry
 * @mode:	File mode क्रम debugfs files. E.g. S_IRWXUGO
 * @uid:	User ID क्रम debugfs files. Currently only 0 is supported.
 * @gid:	Group ID क्रम debugfs files. Currently only 0 is supported.
 *
 * Return:
 * - Handle क्रम generated debug area
 * - %शून्य अगर रेजिस्टर failed
 *
 * Allocates memory क्रम a debug log.
 * Must not be called within an पूर्णांकerrupt handler.
 */
debug_info_t *debug_रेजिस्टर_mode(स्थिर अक्षर *name, पूर्णांक pages_per_area,
				  पूर्णांक nr_areas, पूर्णांक buf_size, umode_t mode,
				  uid_t uid, gid_t gid)
अणु
	debug_info_t *rc = शून्य;

	/* Since debugfs currently करोes not support uid/gid other than root, */
	/* we करो not allow gid/uid != 0 until we get support क्रम that. */
	अगर ((uid != 0) || (gid != 0))
		pr_warn("Root becomes the owner of all s390dbf files in sysfs\n");
	BUG_ON(!initialized);
	mutex_lock(&debug_mutex);

	/* create new debug_info */
	rc = debug_info_create(name, pages_per_area, nr_areas, buf_size, mode);
	अगर (!rc)
		जाओ out;
	debug_रेजिस्टर_view(rc, &debug_level_view);
	debug_रेजिस्टर_view(rc, &debug_flush_view);
	debug_रेजिस्टर_view(rc, &debug_pages_view);
out:
	अगर (!rc)
		pr_err("Registering debug feature %s failed\n", name);
	mutex_unlock(&debug_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(debug_रेजिस्टर_mode);

/**
 * debug_रेजिस्टर() - creates and initializes debug area with शेष file mode.
 *
 * @name:	Name of debug log (e.g. used क्रम debugfs entry)
 * @pages_per_area:	Number of pages, which will be allocated per area
 * @nr_areas:	Number of debug areas
 * @buf_size:	Size of data area in each debug entry
 *
 * Return:
 * - Handle क्रम generated debug area
 * - %शून्य अगर रेजिस्टर failed
 *
 * Allocates memory क्रम a debug log.
 * The debugfs file mode access permissions are पढ़ो and ग_लिखो क्रम user.
 * Must not be called within an पूर्णांकerrupt handler.
 */
debug_info_t *debug_रेजिस्टर(स्थिर अक्षर *name, पूर्णांक pages_per_area,
			     पूर्णांक nr_areas, पूर्णांक buf_size)
अणु
	वापस debug_रेजिस्टर_mode(name, pages_per_area, nr_areas, buf_size,
				   S_IRUSR | S_IWUSR, 0, 0);
पूर्ण
EXPORT_SYMBOL(debug_रेजिस्टर);

/**
 * debug_unरेजिस्टर() - give back debug area.
 *
 * @id:		handle क्रम debug log
 *
 * Return:
 *    none
 */
व्योम debug_unरेजिस्टर(debug_info_t *id)
अणु
	अगर (!id)
		वापस;
	mutex_lock(&debug_mutex);
	debug_info_put(id);
	mutex_unlock(&debug_mutex);
पूर्ण
EXPORT_SYMBOL(debug_unरेजिस्टर);

/*
 * debug_set_size:
 * - set area size (number of pages) and number of areas
 */
अटल पूर्णांक debug_set_size(debug_info_t *id, पूर्णांक nr_areas, पूर्णांक pages_per_area)
अणु
	debug_entry_t ***new_areas;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (!id || (nr_areas <= 0) || (pages_per_area < 0))
		वापस -EINVAL;
	अगर (pages_per_area > 0) अणु
		new_areas = debug_areas_alloc(pages_per_area, nr_areas);
		अगर (!new_areas) अणु
			pr_info("Allocating memory for %i pages failed\n",
				pages_per_area);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_areas = शून्य;
	पूर्ण
	spin_lock_irqsave(&id->lock, flags);
	debug_areas_मुक्त(id);
	id->areas = new_areas;
	id->nr_areas = nr_areas;
	id->pages_per_area = pages_per_area;
	id->active_area = 0;
	स_रखो(id->active_entries, 0, माप(पूर्णांक)*id->nr_areas);
	स_रखो(id->active_pages, 0, माप(पूर्णांक)*id->nr_areas);
	spin_unlock_irqrestore(&id->lock, flags);
	pr_info("%s: set new size (%i pages)\n", id->name, pages_per_area);
out:
	वापस rc;
पूर्ण

/**
 * debug_set_level() - Sets new actual debug level अगर new_level is valid.
 *
 * @id:		handle क्रम debug log
 * @new_level:	new debug level
 *
 * Return:
 *    none
 */
व्योम debug_set_level(debug_info_t *id, पूर्णांक new_level)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!id)
		वापस;
	spin_lock_irqsave(&id->lock, flags);
	अगर (new_level == DEBUG_OFF_LEVEL) अणु
		id->level = DEBUG_OFF_LEVEL;
		pr_info("%s: switched off\n", id->name);
	पूर्ण अन्यथा अगर ((new_level > DEBUG_MAX_LEVEL) || (new_level < 0)) अणु
		pr_info("%s: level %i is out of range (%i - %i)\n",
			id->name, new_level, 0, DEBUG_MAX_LEVEL);
	पूर्ण अन्यथा अणु
		id->level = new_level;
	पूर्ण
	spin_unlock_irqrestore(&id->lock, flags);
पूर्ण
EXPORT_SYMBOL(debug_set_level);

/*
 * proceed_active_entry:
 * - set active entry to next in the ring buffer
 */
अटल अंतरभूत व्योम proceed_active_entry(debug_info_t *id)
अणु
	अगर ((id->active_entries[id->active_area] += id->entry_size)
	    > (PAGE_SIZE - id->entry_size)) अणु
		id->active_entries[id->active_area] = 0;
		id->active_pages[id->active_area] =
			(id->active_pages[id->active_area] + 1) %
			id->pages_per_area;
	पूर्ण
पूर्ण

/*
 * proceed_active_area:
 * - set active area to next in the ring buffer
 */
अटल अंतरभूत व्योम proceed_active_area(debug_info_t *id)
अणु
	id->active_area++;
	id->active_area = id->active_area % id->nr_areas;
पूर्ण

/*
 * get_active_entry:
 */
अटल अंतरभूत debug_entry_t *get_active_entry(debug_info_t *id)
अणु
	वापस (debug_entry_t *) (((अक्षर *) id->areas[id->active_area]
				   [id->active_pages[id->active_area]]) +
				  id->active_entries[id->active_area]);
पूर्ण

/*
 * debug_finish_entry:
 * - set बारtamp, caller address, cpu number etc.
 */

अटल अंतरभूत व्योम debug_finish_entry(debug_info_t *id, debug_entry_t *active,
				      पूर्णांक level, पूर्णांक exception)
अणु
	अचिन्हित दीर्घ बारtamp;
	जोड़ tod_घड़ी clk;

	store_tod_घड़ी_ext(&clk);
	बारtamp = clk.us;
	बारtamp -= TOD_UNIX_EPOCH >> 12;
	active->घड़ी = बारtamp;
	active->cpu = smp_processor_id();
	active->caller = __builtin_वापस_address(0);
	active->exception = exception;
	active->level = level;
	proceed_active_entry(id);
	अगर (exception)
		proceed_active_area(id);
पूर्ण

अटल पूर्णांक debug_stoppable = 1;
अटल पूर्णांक debug_active = 1;

#घोषणा CTL_S390DBF_STOPPABLE 5678
#घोषणा CTL_S390DBF_ACTIVE 5679

/*
 * proc handler क्रम the running debug_active sysctl
 * always allow पढ़ो, allow ग_लिखो only अगर debug_stoppable is set or
 * अगर debug_active is alपढ़ोy off
 */
अटल पूर्णांक s390dbf_procactive(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (!ग_लिखो || debug_stoppable || !debug_active)
		वापस proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अन्यथा
		वापस 0;
पूर्ण

अटल काष्ठा ctl_table s390dbf_table[] = अणु
	अणु
		.procname	= "debug_stoppable",
		.data		= &debug_stoppable,
		.maxlen		= माप(पूर्णांक),
		.mode		= S_IRUGO | S_IWUSR,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "debug_active",
		.data		= &debug_active,
		.maxlen		= माप(पूर्णांक),
		.mode		= S_IRUGO | S_IWUSR,
		.proc_handler	= s390dbf_procactive,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table s390dbf_dir_table[] = अणु
	अणु
		.procname	= "s390dbf",
		.maxlen		= 0,
		.mode		= S_IRUGO | S_IXUGO,
		.child		= s390dbf_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *s390dbf_sysctl_header;

/**
 * debug_stop_all() - stops the debug feature अगर stopping is allowed.
 *
 * Return:
 * -   none
 *
 * Currently used in हाल of a kernel oops.
 */
व्योम debug_stop_all(व्योम)
अणु
	अगर (debug_stoppable)
		debug_active = 0;
पूर्ण
EXPORT_SYMBOL(debug_stop_all);

/**
 * debug_set_critical() - event/exception functions try lock instead of spin.
 *
 * Return:
 * -   none
 *
 * Currently used in हाल of stopping all CPUs but the current one.
 * Once in this state, functions to ग_लिखो a debug entry क्रम an
 * event or exception no दीर्घer spin on the debug area lock,
 * but only try to get it and fail अगर they करो not get the lock.
 */
व्योम debug_set_critical(व्योम)
अणु
	debug_critical = 1;
पूर्ण

/*
 * debug_event_common:
 * - ग_लिखो debug entry with given size
 */
debug_entry_t *debug_event_common(debug_info_t *id, पूर्णांक level, स्थिर व्योम *buf,
				  पूर्णांक len)
अणु
	debug_entry_t *active;
	अचिन्हित दीर्घ flags;

	अगर (!debug_active || !id->areas)
		वापस शून्य;
	अगर (debug_critical) अणु
		अगर (!spin_trylock_irqsave(&id->lock, flags))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&id->lock, flags);
	पूर्ण
	करो अणु
		active = get_active_entry(id);
		स_नकल(DEBUG_DATA(active), buf, min(len, id->buf_size));
		अगर (len < id->buf_size)
			स_रखो((DEBUG_DATA(active)) + len, 0, id->buf_size - len);
		debug_finish_entry(id, active, level, 0);
		len -= id->buf_size;
		buf += id->buf_size;
	पूर्ण जबतक (len > 0);

	spin_unlock_irqrestore(&id->lock, flags);
	वापस active;
पूर्ण
EXPORT_SYMBOL(debug_event_common);

/*
 * debug_exception_common:
 * - ग_लिखो debug entry with given size and चयन to next debug area
 */
debug_entry_t *debug_exception_common(debug_info_t *id, पूर्णांक level,
				      स्थिर व्योम *buf, पूर्णांक len)
अणु
	debug_entry_t *active;
	अचिन्हित दीर्घ flags;

	अगर (!debug_active || !id->areas)
		वापस शून्य;
	अगर (debug_critical) अणु
		अगर (!spin_trylock_irqsave(&id->lock, flags))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&id->lock, flags);
	पूर्ण
	करो अणु
		active = get_active_entry(id);
		स_नकल(DEBUG_DATA(active), buf, min(len, id->buf_size));
		अगर (len < id->buf_size)
			स_रखो((DEBUG_DATA(active)) + len, 0, id->buf_size - len);
		debug_finish_entry(id, active, level, len <= id->buf_size);
		len -= id->buf_size;
		buf += id->buf_size;
	पूर्ण जबतक (len > 0);

	spin_unlock_irqrestore(&id->lock, flags);
	वापस active;
पूर्ण
EXPORT_SYMBOL(debug_exception_common);

/*
 * counts arguments in क्रमmat string क्रम प्र_लिखो view
 */
अटल अंतरभूत पूर्णांक debug_count_numargs(अक्षर *string)
अणु
	पूर्णांक numargs = 0;

	जबतक (*string) अणु
		अगर (*string++ == '%')
			numargs++;
	पूर्ण
	वापस numargs;
पूर्ण

/*
 * debug_प्र_लिखो_event:
 */
debug_entry_t *__debug_प्र_लिखो_event(debug_info_t *id, पूर्णांक level, अक्षर *string, ...)
अणु
	debug_प्र_लिखो_entry_t *curr_event;
	debug_entry_t *active;
	अचिन्हित दीर्घ flags;
	पूर्णांक numargs, idx;
	बहु_सूची ap;

	अगर (!debug_active || !id->areas)
		वापस शून्य;
	numargs = debug_count_numargs(string);

	अगर (debug_critical) अणु
		अगर (!spin_trylock_irqsave(&id->lock, flags))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&id->lock, flags);
	पूर्ण
	active = get_active_entry(id);
	curr_event = (debug_प्र_लिखो_entry_t *) DEBUG_DATA(active);
	बहु_शुरू(ap, string);
	curr_event->string = string;
	क्रम (idx = 0; idx < min(numargs, (पूर्णांक)(id->buf_size / माप(दीर्घ)) - 1); idx++)
		curr_event->args[idx] = बहु_तर्क(ap, दीर्घ);
	बहु_पूर्ण(ap);
	debug_finish_entry(id, active, level, 0);
	spin_unlock_irqrestore(&id->lock, flags);

	वापस active;
पूर्ण
EXPORT_SYMBOL(__debug_प्र_लिखो_event);

/*
 * debug_प्र_लिखो_exception:
 */
debug_entry_t *__debug_प्र_लिखो_exception(debug_info_t *id, पूर्णांक level, अक्षर *string, ...)
अणु
	debug_प्र_लिखो_entry_t *curr_event;
	debug_entry_t *active;
	अचिन्हित दीर्घ flags;
	पूर्णांक numargs, idx;
	बहु_सूची ap;

	अगर (!debug_active || !id->areas)
		वापस शून्य;

	numargs = debug_count_numargs(string);

	अगर (debug_critical) अणु
		अगर (!spin_trylock_irqsave(&id->lock, flags))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&id->lock, flags);
	पूर्ण
	active = get_active_entry(id);
	curr_event = (debug_प्र_लिखो_entry_t *)DEBUG_DATA(active);
	बहु_शुरू(ap, string);
	curr_event->string = string;
	क्रम (idx = 0; idx < min(numargs, (पूर्णांक)(id->buf_size / माप(दीर्घ)) - 1); idx++)
		curr_event->args[idx] = बहु_तर्क(ap, दीर्घ);
	बहु_पूर्ण(ap);
	debug_finish_entry(id, active, level, 1);
	spin_unlock_irqrestore(&id->lock, flags);

	वापस active;
पूर्ण
EXPORT_SYMBOL(__debug_प्र_लिखो_exception);

/**
 * debug_रेजिस्टर_view() - रेजिस्टरs new debug view and creates debugfs
 *			   dir entry
 *
 * @id:		handle क्रम debug log
 * @view:	poपूर्णांकer to debug view काष्ठा
 *
 * Return:
 * -   0  : ok
 * -   < 0: Error
 */
पूर्णांक debug_रेजिस्टर_view(debug_info_t *id, काष्ठा debug_view *view)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dentry *pde;
	umode_t mode;
	पूर्णांक rc = 0;
	पूर्णांक i;

	अगर (!id)
		जाओ out;
	mode = (id->mode | S_IFREG) & ~S_IXUGO;
	अगर (!(view->prolog_proc || view->क्रमmat_proc || view->header_proc))
		mode &= ~(S_IRUSR | S_IRGRP | S_IROTH);
	अगर (!view->input_proc)
		mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
	pde = debugfs_create_file(view->name, mode, id->debugfs_root_entry,
				  id, &debug_file_ops);
	spin_lock_irqsave(&id->lock, flags);
	क्रम (i = 0; i < DEBUG_MAX_VIEWS; i++) अणु
		अगर (!id->views[i])
			अवरोध;
	पूर्ण
	अगर (i == DEBUG_MAX_VIEWS) अणु
		pr_err("Registering view %s/%s would exceed the maximum "
		       "number of views %i\n", id->name, view->name, i);
		rc = -1;
	पूर्ण अन्यथा अणु
		id->views[i] = view;
		id->debugfs_entries[i] = pde;
	पूर्ण
	spin_unlock_irqrestore(&id->lock, flags);
	अगर (rc)
		debugfs_हटाओ(pde);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(debug_रेजिस्टर_view);

/**
 * debug_unरेजिस्टर_view() - unरेजिस्टरs debug view and हटाओs debugfs
 *			     dir entry
 *
 * @id:		handle क्रम debug log
 * @view:	poपूर्णांकer to debug view काष्ठा
 *
 * Return:
 * -   0  : ok
 * -   < 0: Error
 */
पूर्णांक debug_unरेजिस्टर_view(debug_info_t *id, काष्ठा debug_view *view)
अणु
	काष्ठा dentry *dentry = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, rc = 0;

	अगर (!id)
		जाओ out;
	spin_lock_irqsave(&id->lock, flags);
	क्रम (i = 0; i < DEBUG_MAX_VIEWS; i++) अणु
		अगर (id->views[i] == view)
			अवरोध;
	पूर्ण
	अगर (i == DEBUG_MAX_VIEWS) अणु
		rc = -1;
	पूर्ण अन्यथा अणु
		dentry = id->debugfs_entries[i];
		id->views[i] = शून्य;
		id->debugfs_entries[i] = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&id->lock, flags);
	debugfs_हटाओ(dentry);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(debug_unरेजिस्टर_view);

अटल अंतरभूत अक्षर *debug_get_user_string(स्थिर अक्षर __user *user_buf,
					  माप_प्रकार user_len)
अणु
	अक्षर *buffer;

	buffer = kदो_स्मृति(user_len + 1, GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);
	अगर (copy_from_user(buffer, user_buf, user_len) != 0) अणु
		kमुक्त(buffer);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	/* got the string, now strip linefeed. */
	अगर (buffer[user_len - 1] == '\n')
		buffer[user_len - 1] = 0;
	अन्यथा
		buffer[user_len] = 0;
	वापस buffer;
पूर्ण

अटल अंतरभूत पूर्णांक debug_get_uपूर्णांक(अक्षर *buf)
अणु
	पूर्णांक rc;

	buf = skip_spaces(buf);
	rc = simple_म_से_अदीर्घ(buf, &buf, 10);
	अगर (*buf)
		rc = -EINVAL;
	वापस rc;
पूर्ण

/*
 * functions क्रम debug-views
 ***********************************
*/

/*
 * prपूर्णांकs out actual debug level
 */

अटल पूर्णांक debug_prolog_pages_fn(debug_info_t *id, काष्ठा debug_view *view,
				 अक्षर *out_buf)
अणु
	वापस प्र_लिखो(out_buf, "%i\n", id->pages_per_area);
पूर्ण

/*
 * पढ़ोs new size (number of pages per debug area)
 */

अटल पूर्णांक debug_input_pages_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_len, loff_t *offset)
अणु
	पूर्णांक rc, new_pages;
	अक्षर *str;

	अगर (user_len > 0x10000)
		user_len = 0x10000;
	अगर (*offset != 0) अणु
		rc = -EPIPE;
		जाओ out;
	पूर्ण
	str = debug_get_user_string(user_buf, user_len);
	अगर (IS_ERR(str)) अणु
		rc = PTR_ERR(str);
		जाओ out;
	पूर्ण
	new_pages = debug_get_uपूर्णांक(str);
	अगर (new_pages < 0) अणु
		rc = -EINVAL;
		जाओ मुक्त_str;
	पूर्ण
	rc = debug_set_size(id, id->nr_areas, new_pages);
	अगर (rc != 0) अणु
		rc = -EINVAL;
		जाओ मुक्त_str;
	पूर्ण
	rc = user_len;
मुक्त_str:
	kमुक्त(str);
out:
	*offset += user_len;
	वापस rc;		/* number of input अक्षरacters */
पूर्ण

/*
 * prपूर्णांकs out actual debug level
 */
अटल पूर्णांक debug_prolog_level_fn(debug_info_t *id, काष्ठा debug_view *view,
				 अक्षर *out_buf)
अणु
	पूर्णांक rc = 0;

	अगर (id->level == DEBUG_OFF_LEVEL)
		rc = प्र_लिखो(out_buf, "-\n");
	अन्यथा
		rc = प्र_लिखो(out_buf, "%i\n", id->level);
	वापस rc;
पूर्ण

/*
 * पढ़ोs new debug level
 */
अटल पूर्णांक debug_input_level_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_len, loff_t *offset)
अणु
	पूर्णांक rc, new_level;
	अक्षर *str;

	अगर (user_len > 0x10000)
		user_len = 0x10000;
	अगर (*offset != 0) अणु
		rc = -EPIPE;
		जाओ out;
	पूर्ण
	str = debug_get_user_string(user_buf, user_len);
	अगर (IS_ERR(str)) अणु
		rc = PTR_ERR(str);
		जाओ out;
	पूर्ण
	अगर (str[0] == '-') अणु
		debug_set_level(id, DEBUG_OFF_LEVEL);
		rc = user_len;
		जाओ मुक्त_str;
	पूर्ण अन्यथा अणु
		new_level = debug_get_uपूर्णांक(str);
	पूर्ण
	अगर (new_level < 0) अणु
		pr_warn("%s is not a valid level for a debug feature\n", str);
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		debug_set_level(id, new_level);
		rc = user_len;
	पूर्ण
मुक्त_str:
	kमुक्त(str);
out:
	*offset += user_len;
	वापस rc;		/* number of input अक्षरacters */
पूर्ण

/*
 * flushes debug areas
 */
अटल व्योम debug_flush(debug_info_t *id, पूर्णांक area)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j;

	अगर (!id || !id->areas)
		वापस;
	spin_lock_irqsave(&id->lock, flags);
	अगर (area == DEBUG_FLUSH_ALL) अणु
		id->active_area = 0;
		स_रखो(id->active_entries, 0, id->nr_areas * माप(पूर्णांक));
		क्रम (i = 0; i < id->nr_areas; i++) अणु
			id->active_pages[i] = 0;
			क्रम (j = 0; j < id->pages_per_area; j++)
				स_रखो(id->areas[i][j], 0, PAGE_SIZE);
		पूर्ण
	पूर्ण अन्यथा अगर (area >= 0 && area < id->nr_areas) अणु
		id->active_entries[area] = 0;
		id->active_pages[area] = 0;
		क्रम (i = 0; i < id->pages_per_area; i++)
			स_रखो(id->areas[area][i], 0, PAGE_SIZE);
	पूर्ण
	spin_unlock_irqrestore(&id->lock, flags);
पूर्ण

/*
 * view function: flushes debug areas
 */
अटल पूर्णांक debug_input_flush_fn(debug_info_t *id, काष्ठा debug_view *view,
				काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार user_len, loff_t *offset)
अणु
	अक्षर input_buf[1];
	पूर्णांक rc = user_len;

	अगर (user_len > 0x10000)
		user_len = 0x10000;
	अगर (*offset != 0) अणु
		rc = -EPIPE;
		जाओ out;
	पूर्ण
	अगर (copy_from_user(input_buf, user_buf, 1)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (input_buf[0] == '-') अणु
		debug_flush(id, DEBUG_FLUSH_ALL);
		जाओ out;
	पूर्ण
	अगर (है_अंक(input_buf[0])) अणु
		पूर्णांक area = ((पूर्णांक) input_buf[0] - (पूर्णांक) '0');

		debug_flush(id, area);
		जाओ out;
	पूर्ण

	pr_info("Flushing debug data failed because %c is not a valid "
		 "area\n", input_buf[0]);

out:
	*offset += user_len;
	वापस rc;		/* number of input अक्षरacters */
पूर्ण

/*
 * prपूर्णांकs debug data in hex/ascii क्रमmat
 */
अटल पूर्णांक debug_hex_ascii_क्रमmat_fn(debug_info_t *id, काष्ठा debug_view *view,
				     अक्षर *out_buf, स्थिर अक्षर *in_buf)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < id->buf_size; i++)
		rc += प्र_लिखो(out_buf + rc, "%02x ", ((अचिन्हित अक्षर *) in_buf)[i]);
	rc += प्र_लिखो(out_buf + rc, "| ");
	क्रम (i = 0; i < id->buf_size; i++) अणु
		अचिन्हित अक्षर c = in_buf[i];

		अगर (isascii(c) && है_छाप(c))
			rc += प्र_लिखो(out_buf + rc, "%c", c);
		अन्यथा
			rc += प्र_लिखो(out_buf + rc, ".");
	पूर्ण
	rc += प्र_लिखो(out_buf + rc, "\n");
	वापस rc;
पूर्ण

/*
 * prपूर्णांकs header क्रम debug entry
 */
पूर्णांक debug_dflt_header_fn(debug_info_t *id, काष्ठा debug_view *view,
			 पूर्णांक area, debug_entry_t *entry, अक्षर *out_buf)
अणु
	अचिन्हित दीर्घ sec, usec;
	अचिन्हित दीर्घ caller;
	अचिन्हित पूर्णांक level;
	अक्षर *except_str;
	पूर्णांक rc = 0;

	level = entry->level;
	sec = entry->घड़ी;
	usec = करो_भाग(sec, USEC_PER_SEC);

	अगर (entry->exception)
		except_str = "*";
	अन्यथा
		except_str = "-";
	caller = (अचिन्हित दीर्घ) entry->caller;
	rc += प्र_लिखो(out_buf, "%02i %011ld:%06lu %1u %1s %04u %pK  ",
		      area, sec, usec, level, except_str,
		      entry->cpu, (व्योम *)caller);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(debug_dflt_header_fn);

/*
 * prपूर्णांकs debug data प्र_लिखो-क्रमmated:
 * debug_sprinf_event/exception calls must be used together with this view
 */

#घोषणा DEBUG_SPRINTF_MAX_ARGS 10

अटल पूर्णांक debug_प्र_लिखो_क्रमmat_fn(debug_info_t *id, काष्ठा debug_view *view,
				   अक्षर *out_buf, debug_प्र_लिखो_entry_t *curr_event)
अणु
	पूर्णांक num_दीर्घs, num_used_args = 0, i, rc = 0;
	पूर्णांक index[DEBUG_SPRINTF_MAX_ARGS];

	/* count of दीर्घs fit पूर्णांकo one entry */
	num_दीर्घs = id->buf_size / माप(दीर्घ);

	अगर (num_दीर्घs < 1)
		जाओ out; /* bufsize of entry too small */
	अगर (num_दीर्घs == 1) अणु
		/* no args, we use only the string */
		म_नकल(out_buf, curr_event->string);
		rc = म_माप(curr_event->string);
		जाओ out;
	पूर्ण

	/* number of arguments used क्रम प्र_लिखो (without the क्रमmat string) */
	num_used_args = min(DEBUG_SPRINTF_MAX_ARGS, (num_दीर्घs - 1));

	स_रखो(index, 0, DEBUG_SPRINTF_MAX_ARGS * माप(पूर्णांक));

	क्रम (i = 0; i < num_used_args; i++)
		index[i] = i;

	rc = प्र_लिखो(out_buf, curr_event->string, curr_event->args[index[0]],
		     curr_event->args[index[1]], curr_event->args[index[2]],
		     curr_event->args[index[3]], curr_event->args[index[4]],
		     curr_event->args[index[5]], curr_event->args[index[6]],
		     curr_event->args[index[7]], curr_event->args[index[8]],
		     curr_event->args[index[9]]);
out:
	वापस rc;
पूर्ण

/*
 * debug_init:
 * - is called exactly once to initialize the debug feature
 */
अटल पूर्णांक __init debug_init(व्योम)
अणु
	s390dbf_sysctl_header = रेजिस्टर_sysctl_table(s390dbf_dir_table);
	mutex_lock(&debug_mutex);
	debug_debugfs_root_entry = debugfs_create_dir(DEBUG_सूची_ROOT, शून्य);
	initialized = 1;
	mutex_unlock(&debug_mutex);
	वापस 0;
पूर्ण
postcore_initcall(debug_init);
