<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * What:		/sys/kernel/debug/orangefs/debug-help
 * Date:		June 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			List of client and kernel debug keywords.
 *
 *
 * What:		/sys/kernel/debug/orangefs/client-debug
 * Date:		June 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Debug setting क्रम "the client", the userspace
 * 			helper क्रम the kernel module.
 *
 *
 * What:		/sys/kernel/debug/orangefs/kernel-debug
 * Date:		June 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Debug setting क्रम the orangefs kernel module.
 *
 * 			Any of the keywords, or comma-separated lists
 * 			of keywords, from debug-help can be catted to
 * 			client-debug or kernel-debug.
 *
 * 			"none", "all" and "verbose" are special keywords
 * 			क्रम client-debug. Setting client-debug to "all"
 * 			is kind of like trying to drink water from a
 * 			fire hose, "verbose" triggers most of the same
 * 			output except क्रम the स्थिरant flow of output
 * 			from the मुख्य रुको loop.
 *
 * 			"none" and "all" are similar settings क्रम kernel-debug
 * 			no need क्रम a "verbose".
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>

#समावेश "orangefs-debugfs.h"
#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"

#घोषणा DEBUG_HELP_STRING_SIZE 4096
#घोषणा HELP_STRING_UNINITIALIZED \
	"Client Debug Keywords are unknown until the first time\n" \
	"the client is started after boot.\n"
#घोषणा ORANGEFS_KMOD_DEBUG_HELP_खाता "debug-help"
#घोषणा ORANGEFS_KMOD_DEBUG_खाता "kernel-debug"
#घोषणा ORANGEFS_CLIENT_DEBUG_खाता "client-debug"
#घोषणा ORANGEFS_VERBOSE "verbose"
#घोषणा ORANGEFS_ALL "all"

/*
 * An array of client_debug_mask will be built to hold debug keyword/mask
 * values fetched from userspace.
 */
काष्ठा client_debug_mask अणु
	अक्षर *keyword;
	__u64 mask1;
	__u64 mask2;
पूर्ण;

अटल व्योम orangefs_kernel_debug_init(व्योम);

अटल पूर्णांक orangefs_debug_help_खोलो(काष्ठा inode *, काष्ठा file *);
अटल व्योम *help_start(काष्ठा seq_file *, loff_t *);
अटल व्योम *help_next(काष्ठा seq_file *, व्योम *, loff_t *);
अटल व्योम help_stop(काष्ठा seq_file *, व्योम *);
अटल पूर्णांक help_show(काष्ठा seq_file *, व्योम *);

अटल पूर्णांक orangefs_debug_खोलो(काष्ठा inode *, काष्ठा file *);

अटल sमाप_प्रकार orangefs_debug_पढ़ो(काष्ठा file *,
				 अक्षर __user *,
				 माप_प्रकार,
				 loff_t *);

अटल sमाप_प्रकार orangefs_debug_ग_लिखो(काष्ठा file *,
				  स्थिर अक्षर __user *,
				  माप_प्रकार,
				  loff_t *);

अटल पूर्णांक orangefs_prepare_cdm_array(अक्षर *);
अटल व्योम debug_mask_to_string(व्योम *, पूर्णांक);
अटल व्योम करो_k_string(व्योम *, पूर्णांक);
अटल व्योम करो_c_string(व्योम *, पूर्णांक);
अटल पूर्णांक keyword_is_amalgam(अक्षर *);
अटल पूर्णांक check_amalgam_keyword(व्योम *, पूर्णांक);
अटल व्योम debug_string_to_mask(अक्षर *, व्योम *, पूर्णांक);
अटल व्योम करो_c_mask(पूर्णांक, अक्षर *, काष्ठा client_debug_mask **);
अटल व्योम करो_k_mask(पूर्णांक, अक्षर *, __u64 **);

अटल अक्षर kernel_debug_string[ORANGEFS_MAX_DEBUG_STRING_LEN] = "none";
अटल अक्षर *debug_help_string;
अटल अक्षर client_debug_string[ORANGEFS_MAX_DEBUG_STRING_LEN];
अटल अक्षर client_debug_array_string[ORANGEFS_MAX_DEBUG_STRING_LEN];

अटल काष्ठा dentry *client_debug_dentry;
अटल काष्ठा dentry *debug_dir;

अटल अचिन्हित पूर्णांक kernel_mask_set_mod_init;
अटल पूर्णांक orangefs_debug_disabled = 1;
अटल पूर्णांक help_string_initialized;

अटल स्थिर काष्ठा seq_operations help_debug_ops = अणु
	.start	= help_start,
	.next	= help_next,
	.stop	= help_stop,
	.show	= help_show,
पूर्ण;

अटल स्थिर काष्ठा file_operations debug_help_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = orangefs_debug_help_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.release        = seq_release,
	.llseek         = seq_lseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations kernel_debug_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = orangefs_debug_खोलो,
	.पढ़ो           = orangefs_debug_पढ़ो,
	.ग_लिखो		= orangefs_debug_ग_लिखो,
	.llseek         = generic_file_llseek,
पूर्ण;

अटल पूर्णांक client_all_index;
अटल पूर्णांक client_verbose_index;

अटल काष्ठा client_debug_mask *cdm_array;
अटल पूर्णांक cdm_element_count;

अटल काष्ठा client_debug_mask client_debug_mask;

/*
 * Used to protect data in ORANGEFS_KMOD_DEBUG_खाता and
 * ORANGEFS_KMOD_DEBUG_खाता.
 */
अटल DEFINE_MUTEX(orangefs_debug_lock);

/* Used to protect data in ORANGEFS_KMOD_DEBUG_HELP_खाता */
अटल DEFINE_MUTEX(orangefs_help_file_lock);

/*
 * initialize kmod debug operations, create orangefs debugfs dir and
 * ORANGEFS_KMOD_DEBUG_HELP_खाता.
 */
व्योम orangefs_debugfs_init(पूर्णांक debug_mask)
अणु
	/* convert input debug mask to a 64-bit अचिन्हित पूर्णांकeger */
        orangefs_gossip_debug_mask = (अचिन्हित दीर्घ दीर्घ)debug_mask;

	/*
	 * set the kernel's gossip debug string; invalid mask values will
	 * be ignored.
	 */
	debug_mask_to_string(&orangefs_gossip_debug_mask, 0);

	/* हटाओ any invalid values from the mask */
	debug_string_to_mask(kernel_debug_string, &orangefs_gossip_debug_mask,
	    0);

	/*
	 * अगर the mask has a non-zero value, then indicate that the mask
	 * was set when the kernel module was loaded.  The orangefs dev ioctl
	 * command will look at this boolean to determine अगर the kernel's
	 * debug mask should be overwritten when the client-core is started.
	 */
	अगर (orangefs_gossip_debug_mask != 0)
		kernel_mask_set_mod_init = true;

	pr_info("%s: called with debug mask: :%s: :%llx:\n",
		__func__,
		kernel_debug_string,
		(अचिन्हित दीर्घ दीर्घ)orangefs_gossip_debug_mask);

	debug_dir = debugfs_create_dir("orangefs", शून्य);

	debugfs_create_file(ORANGEFS_KMOD_DEBUG_HELP_खाता, 0444, debug_dir,
			    debug_help_string, &debug_help_fops);

	orangefs_debug_disabled = 0;

	orangefs_kernel_debug_init();
पूर्ण

/*
 * initialize the kernel-debug file.
 */
अटल व्योम orangefs_kernel_debug_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;
	अक्षर *k_buffer = शून्य;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "%s: start\n", __func__);

	k_buffer = kzalloc(ORANGEFS_MAX_DEBUG_STRING_LEN, GFP_KERNEL);
	अगर (!k_buffer)
		जाओ out;

	अगर (म_माप(kernel_debug_string) + 1 < ORANGEFS_MAX_DEBUG_STRING_LEN) अणु
		म_नकल(k_buffer, kernel_debug_string);
		म_जोड़ो(k_buffer, "\n");
	पूर्ण अन्यथा अणु
		म_नकल(k_buffer, "none\n");
		pr_info("%s: overflow 1!\n", __func__);
	पूर्ण

	debugfs_create_file(ORANGEFS_KMOD_DEBUG_खाता, 0444, debug_dir, k_buffer,
			    &kernel_debug_fops);

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "%s: rc:%d:\n", __func__, rc);
पूर्ण


व्योम orangefs_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ_recursive(debug_dir);
पूर्ण

/* खोलो ORANGEFS_KMOD_DEBUG_HELP_खाता */
अटल पूर्णांक orangefs_debug_help_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = -ENODEV;
	पूर्णांक ret;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_help_open: start\n");

	अगर (orangefs_debug_disabled)
		जाओ out;

	ret = seq_खोलो(file, &help_debug_ops);
	अगर (ret)
		जाओ out;

	((काष्ठा seq_file *)(file->निजी_data))->निजी = inode->i_निजी;

	rc = 0;

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_help_open: rc:%d:\n",
		     rc);
	वापस rc;
पूर्ण

/*
 * I think start always माला_लो called again after stop. Start
 * needs to वापस शून्य when it is करोne. The whole "payload"
 * in this हाल is a single (दीर्घ) string, so by the second
 * समय we get to start (pos = 1), we're करोne.
 */
अटल व्योम *help_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	व्योम *payload = शून्य;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "help_start: start\n");

	mutex_lock(&orangefs_help_file_lock);

	अगर (*pos == 0)
		payload = m->निजी;

	वापस payload;
पूर्ण

अटल व्योम *help_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "help_next: start\n");

	वापस शून्य;
पूर्ण

अटल व्योम help_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "help_stop: start\n");
	mutex_unlock(&orangefs_help_file_lock);
पूर्ण

अटल पूर्णांक help_show(काष्ठा seq_file *m, व्योम *v)
अणु
	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "help_show: start\n");

	seq_माला_दो(m, v);

	वापस 0;
पूर्ण

/*
 * initialize the client-debug file.
 */
अटल पूर्णांक orangefs_client_debug_init(व्योम)
अणु

	पूर्णांक rc = -ENOMEM;
	अक्षर *c_buffer = शून्य;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "%s: start\n", __func__);

	c_buffer = kzalloc(ORANGEFS_MAX_DEBUG_STRING_LEN, GFP_KERNEL);
	अगर (!c_buffer)
		जाओ out;

	अगर (म_माप(client_debug_string) + 1 < ORANGEFS_MAX_DEBUG_STRING_LEN) अणु
		म_नकल(c_buffer, client_debug_string);
		म_जोड़ो(c_buffer, "\n");
	पूर्ण अन्यथा अणु
		म_नकल(c_buffer, "none\n");
		pr_info("%s: overflow! 2\n", __func__);
	पूर्ण

	client_debug_dentry = debugfs_create_file(ORANGEFS_CLIENT_DEBUG_खाता,
						  0444,
						  debug_dir,
						  c_buffer,
						  &kernel_debug_fops);

	rc = 0;

out:

	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "%s: rc:%d:\n", __func__, rc);
	वापस rc;
पूर्ण

/* खोलो ORANGEFS_KMOD_DEBUG_खाता or ORANGEFS_CLIENT_DEBUG_खाता.*/
अटल पूर्णांक orangefs_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = -ENODEV;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "%s: orangefs_debug_disabled: %d\n",
		     __func__,
		     orangefs_debug_disabled);

	अगर (orangefs_debug_disabled)
		जाओ out;

	rc = 0;
	mutex_lock(&orangefs_debug_lock);
	file->निजी_data = inode->i_निजी;
	mutex_unlock(&orangefs_debug_lock);

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_open: rc: %d\n",
		     rc);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार orangefs_debug_पढ़ो(काष्ठा file *file,
				 अक्षर __user *ubuf,
				 माप_प्रकार count,
				 loff_t *ppos)
अणु
	अक्षर *buf;
	पूर्णांक प्र_लिखो_ret;
	sमाप_प्रकार पढ़ो_ret = -ENOMEM;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG, "orangefs_debug_read: start\n");

	buf = kदो_स्मृति(ORANGEFS_MAX_DEBUG_STRING_LEN, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	mutex_lock(&orangefs_debug_lock);
	प्र_लिखो_ret = प्र_लिखो(buf, "%s", (अक्षर *)file->निजी_data);
	mutex_unlock(&orangefs_debug_lock);

	पढ़ो_ret = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, प्र_लिखो_ret);

	kमुक्त(buf);

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_read: ret: %zu\n",
		     पढ़ो_ret);

	वापस पढ़ो_ret;
पूर्ण

अटल sमाप_प्रकार orangefs_debug_ग_लिखो(काष्ठा file *file,
				  स्थिर अक्षर __user *ubuf,
				  माप_प्रकार count,
				  loff_t *ppos)
अणु
	अक्षर *buf;
	पूर्णांक rc = -EFAULT;
	माप_प्रकार silly = 0;
	अक्षर *debug_string;
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	काष्ठा client_debug_mask c_mask = अणु शून्य, 0, 0 पूर्ण;
	अक्षर *s;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		"orangefs_debug_write: %pD\n",
		file);

	अगर (count == 0)
		वापस 0;

	/*
	 * Thwart users who try to jamb a ridiculous number
	 * of bytes पूर्णांकo the debug file...
	 */
	अगर (count > ORANGEFS_MAX_DEBUG_STRING_LEN + 1) अणु
		silly = count;
		count = ORANGEFS_MAX_DEBUG_STRING_LEN + 1;
	पूर्ण

	buf = kzalloc(ORANGEFS_MAX_DEBUG_STRING_LEN, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	अगर (copy_from_user(buf, ubuf, count - 1)) अणु
		gossip_debug(GOSSIP_DEBUGFS_DEBUG,
			     "%s: copy_from_user failed!\n",
			     __func__);
		जाओ out;
	पूर्ण

	/*
	 * Map the keyword string from userspace पूर्णांकo a valid debug mask.
	 * The mapping process involves mapping the human-inputted string
	 * पूर्णांकo a valid mask, and then rebuilding the string from the
	 * verअगरied valid mask.
	 *
	 * A service operation is required to set a new client-side
	 * debug mask.
	 */
	अगर (!म_भेद(file->f_path.dentry->d_name.name,
		    ORANGEFS_KMOD_DEBUG_खाता)) अणु
		debug_string_to_mask(buf, &orangefs_gossip_debug_mask, 0);
		debug_mask_to_string(&orangefs_gossip_debug_mask, 0);
		debug_string = kernel_debug_string;
		gossip_debug(GOSSIP_DEBUGFS_DEBUG,
			     "New kernel debug string is %s\n",
			     kernel_debug_string);
	पूर्ण अन्यथा अणु
		/* Can't reset client debug mask अगर client is not running. */
		अगर (is_daemon_in_service()) अणु
			pr_info("%s: Client not running :%d:\n",
				__func__,
				is_daemon_in_service());
			जाओ out;
		पूर्ण

		debug_string_to_mask(buf, &c_mask, 1);
		debug_mask_to_string(&c_mask, 1);
		debug_string = client_debug_string;

		new_op = op_alloc(ORANGEFS_VFS_OP_PARAM);
		अगर (!new_op) अणु
			pr_info("%s: op_alloc failed!\n", __func__);
			जाओ out;
		पूर्ण

		new_op->upcall.req.param.op =
			ORANGEFS_PARAM_REQUEST_OP_TWO_MASK_VALUES;
		new_op->upcall.req.param.type = ORANGEFS_PARAM_REQUEST_SET;
		स_रखो(new_op->upcall.req.param.s_value,
		       0,
		       ORANGEFS_MAX_DEBUG_STRING_LEN);
		प्र_लिखो(new_op->upcall.req.param.s_value,
			"%llx %llx\n",
			c_mask.mask1,
			c_mask.mask2);

		/* service_operation वापसs 0 on success... */
		rc = service_operation(new_op,
				       "orangefs_param",
					ORANGEFS_OP_INTERRUPTIBLE);

		अगर (rc)
			gossip_debug(GOSSIP_DEBUGFS_DEBUG,
				     "%s: service_operation failed! rc:%d:\n",
				     __func__,
				     rc);

		op_release(new_op);
	पूर्ण

	mutex_lock(&orangefs_debug_lock);
	s = file_inode(file)->i_निजी;
	स_रखो(s, 0, ORANGEFS_MAX_DEBUG_STRING_LEN);
	प्र_लिखो(s, "%s\n", debug_string);
	mutex_unlock(&orangefs_debug_lock);

	*ppos += count;
	अगर (silly)
		rc = silly;
	अन्यथा
		rc = count;

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_write: rc: %d\n",
		     rc);
	kमुक्त(buf);
	वापस rc;
पूर्ण

/*
 * After obtaining a string representation of the client's debug
 * keywords and their associated masks, this function is called to build an
 * array of these values.
 */
अटल पूर्णांक orangefs_prepare_cdm_array(अक्षर *debug_array_string)
अणु
	पूर्णांक i;
	पूर्णांक rc = -EINVAL;
	अक्षर *cds_head = शून्य;
	अक्षर *cds_delimiter = शून्य;
	पूर्णांक keyword_len = 0;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: start\n", __func__);

	/*
	 * figure out how many elements the cdm_array needs.
	 */
	क्रम (i = 0; i < म_माप(debug_array_string); i++)
		अगर (debug_array_string[i] == '\n')
			cdm_element_count++;

	अगर (!cdm_element_count) अणु
		pr_info("No elements in client debug array string!\n");
		जाओ out;
	पूर्ण

	cdm_array = kसुस्मृति(cdm_element_count, माप(*cdm_array), GFP_KERNEL);
	अगर (!cdm_array) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cds_head = debug_array_string;

	क्रम (i = 0; i < cdm_element_count; i++) अणु
		cds_delimiter = म_अक्षर(cds_head, '\n');
		*cds_delimiter = '\0';

		keyword_len = म_खोज(cds_head, " ");

		cdm_array[i].keyword = kzalloc(keyword_len + 1, GFP_KERNEL);
		अगर (!cdm_array[i].keyword) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		माला_पूछो(cds_head,
		       "%s %llx %llx",
		       cdm_array[i].keyword,
		       (अचिन्हित दीर्घ दीर्घ *)&(cdm_array[i].mask1),
		       (अचिन्हित दीर्घ दीर्घ *)&(cdm_array[i].mask2));

		अगर (!म_भेद(cdm_array[i].keyword, ORANGEFS_VERBOSE))
			client_verbose_index = i;

		अगर (!म_भेद(cdm_array[i].keyword, ORANGEFS_ALL))
			client_all_index = i;

		cds_head = cds_delimiter + 1;
	पूर्ण

	rc = cdm_element_count;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: rc:%d:\n", __func__, rc);

out:

	वापस rc;

पूर्ण

/*
 * /sys/kernel/debug/orangefs/debug-help can be catted to
 * see all the available kernel and client debug keywords.
 *
 * When orangefs.ko initializes, we have no idea what keywords the
 * client supports, nor their associated masks.
 *
 * We pass through this function once at module-load and stamp a
 * boilerplate "we don't know" message क्रम the client in the
 * debug-help file. We pass through here again when the client
 * starts and then we can fill out the debug-help file fully.
 *
 * The client might be restarted any number of बार between
 * module reloads, we only build the debug-help file the first समय.
 */
पूर्णांक orangefs_prepare_debugfs_help_string(पूर्णांक at_boot)
अणु
	अक्षर *client_title = "Client Debug Keywords:\n";
	अक्षर *kernel_title = "Kernel Debug Keywords:\n";
	माप_प्रकार string_size =  DEBUG_HELP_STRING_SIZE;
	माप_प्रकार result_size;
	माप_प्रकार i;
	अक्षर *new;
	पूर्णांक rc = -EINVAL;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: start\n", __func__);

	अगर (at_boot)
		client_title = HELP_STRING_UNINITIALIZED;

	/* build a new debug_help_string. */
	new = kzalloc(DEBUG_HELP_STRING_SIZE, GFP_KERNEL);
	अगर (!new) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * strlcat(dst, src, size) will append at most
	 * "size - strlen(dst) - 1" bytes of src onto dst,
	 * null terminating the result, and वापस the total
	 * length of the string it tried to create.
	 *
	 * We'll just plow through here building our new debug
	 * help string and let strlcat take care of assuring that
	 * dst करोesn't overflow.
	 */
	strlcat(new, client_title, string_size);

	अगर (!at_boot) अणु

                /*
		 * fill the client keyword/mask array and remember
		 * how many elements there were.
		 */
		cdm_element_count =
			orangefs_prepare_cdm_array(client_debug_array_string);
		अगर (cdm_element_count <= 0) अणु
			kमुक्त(new);
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < cdm_element_count; i++) अणु
			strlcat(new, "\t", string_size);
			strlcat(new, cdm_array[i].keyword, string_size);
			strlcat(new, "\n", string_size);
		पूर्ण
	पूर्ण

	strlcat(new, "\n", string_size);
	strlcat(new, kernel_title, string_size);

	क्रम (i = 0; i < num_kmod_keyword_mask_map; i++) अणु
		strlcat(new, "\t", string_size);
		strlcat(new, s_kmod_keyword_mask_map[i].keyword, string_size);
		result_size = strlcat(new, "\n", string_size);
	पूर्ण

	/* See अगर we tried to put too many bytes पूर्णांकo "new"... */
	अगर (result_size >= string_size) अणु
		kमुक्त(new);
		जाओ out;
	पूर्ण

	अगर (at_boot) अणु
		debug_help_string = new;
	पूर्ण अन्यथा अणु
		mutex_lock(&orangefs_help_file_lock);
		स_रखो(debug_help_string, 0, DEBUG_HELP_STRING_SIZE);
		strlcat(debug_help_string, new, string_size);
		mutex_unlock(&orangefs_help_file_lock);
	पूर्ण

	rc = 0;

out:	वापस rc;

पूर्ण

/*
 * kernel = type 0
 * client = type 1
 */
अटल व्योम debug_mask_to_string(व्योम *mask, पूर्णांक type)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;
	अक्षर *debug_string;
	पूर्णांक element_count = 0;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: start\n", __func__);

	अगर (type) अणु
		debug_string = client_debug_string;
		element_count = cdm_element_count;
	पूर्ण अन्यथा अणु
		debug_string = kernel_debug_string;
		element_count = num_kmod_keyword_mask_map;
	पूर्ण

	स_रखो(debug_string, 0, ORANGEFS_MAX_DEBUG_STRING_LEN);

	/*
	 * Some keywords, like "all" or "verbose", are amalgams of
	 * numerous other keywords. Make a special check क्रम those
	 * beक्रमe grinding through the whole mask only to find out
	 * later...
	 */
	अगर (check_amalgam_keyword(mask, type))
		जाओ out;

	/* Build the debug string. */
	क्रम (i = 0; i < element_count; i++)
		अगर (type)
			करो_c_string(mask, i);
		अन्यथा
			करो_k_string(mask, i);

	len = म_माप(debug_string);

	अगर ((len) && (type))
		client_debug_string[len - 1] = '\0';
	अन्यथा अगर (len)
		kernel_debug_string[len - 1] = '\0';
	अन्यथा अगर (type)
		म_नकल(client_debug_string, "none");
	अन्यथा
		म_नकल(kernel_debug_string, "none");

out:
gossip_debug(GOSSIP_UTILS_DEBUG, "%s: string:%s:\n", __func__, debug_string);

	वापस;

पूर्ण

अटल व्योम करो_k_string(व्योम *k_mask, पूर्णांक index)
अणु
	__u64 *mask = (__u64 *) k_mask;

	अगर (keyword_is_amalgam((अक्षर *) s_kmod_keyword_mask_map[index].keyword))
		जाओ out;

	अगर (*mask & s_kmod_keyword_mask_map[index].mask_val) अणु
		अगर ((म_माप(kernel_debug_string) +
		     म_माप(s_kmod_keyword_mask_map[index].keyword))
			< ORANGEFS_MAX_DEBUG_STRING_LEN - 1) अणु
				म_जोड़ो(kernel_debug_string,
				       s_kmod_keyword_mask_map[index].keyword);
				म_जोड़ो(kernel_debug_string, ",");
			पूर्ण अन्यथा अणु
				gossip_err("%s: overflow!\n", __func__);
				म_नकल(kernel_debug_string, ORANGEFS_ALL);
				जाओ out;
			पूर्ण
	पूर्ण

out:

	वापस;
पूर्ण

अटल व्योम करो_c_string(व्योम *c_mask, पूर्णांक index)
अणु
	काष्ठा client_debug_mask *mask = (काष्ठा client_debug_mask *) c_mask;

	अगर (keyword_is_amalgam(cdm_array[index].keyword))
		जाओ out;

	अगर ((mask->mask1 & cdm_array[index].mask1) ||
	    (mask->mask2 & cdm_array[index].mask2)) अणु
		अगर ((म_माप(client_debug_string) +
		     म_माप(cdm_array[index].keyword) + 1)
			< ORANGEFS_MAX_DEBUG_STRING_LEN - 2) अणु
				म_जोड़ो(client_debug_string,
				       cdm_array[index].keyword);
				म_जोड़ो(client_debug_string, ",");
			पूर्ण अन्यथा अणु
				gossip_err("%s: overflow!\n", __func__);
				म_नकल(client_debug_string, ORANGEFS_ALL);
				जाओ out;
			पूर्ण
	पूर्ण
out:
	वापस;
पूर्ण

अटल पूर्णांक keyword_is_amalgam(अक्षर *keyword)
अणु
	पूर्णांक rc = 0;

	अगर ((!म_भेद(keyword, ORANGEFS_ALL)) || (!म_भेद(keyword, ORANGEFS_VERBOSE)))
		rc = 1;

	वापस rc;
पूर्ण

/*
 * kernel = type 0
 * client = type 1
 *
 * वापस 1 अगर we found an amalgam.
 */
अटल पूर्णांक check_amalgam_keyword(व्योम *mask, पूर्णांक type)
अणु
	__u64 *k_mask;
	काष्ठा client_debug_mask *c_mask;
	पूर्णांक k_all_index = num_kmod_keyword_mask_map - 1;
	पूर्णांक rc = 0;

	अगर (type) अणु
		c_mask = (काष्ठा client_debug_mask *) mask;

		अगर ((c_mask->mask1 == cdm_array[client_all_index].mask1) &&
		    (c_mask->mask2 == cdm_array[client_all_index].mask2)) अणु
			म_नकल(client_debug_string, ORANGEFS_ALL);
			rc = 1;
			जाओ out;
		पूर्ण

		अगर ((c_mask->mask1 == cdm_array[client_verbose_index].mask1) &&
		    (c_mask->mask2 == cdm_array[client_verbose_index].mask2)) अणु
			म_नकल(client_debug_string, ORANGEFS_VERBOSE);
			rc = 1;
			जाओ out;
		पूर्ण

	पूर्ण अन्यथा अणु
		k_mask = (__u64 *) mask;

		अगर (*k_mask >= s_kmod_keyword_mask_map[k_all_index].mask_val) अणु
			म_नकल(kernel_debug_string, ORANGEFS_ALL);
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण

out:

	वापस rc;
पूर्ण

/*
 * kernel = type 0
 * client = type 1
 */
अटल व्योम debug_string_to_mask(अक्षर *debug_string, व्योम *mask, पूर्णांक type)
अणु
	अक्षर *unchecked_keyword;
	पूर्णांक i;
	अक्षर *strsep_fodder = kstrdup(debug_string, GFP_KERNEL);
	अक्षर *original_poपूर्णांकer;
	पूर्णांक element_count = 0;
	काष्ठा client_debug_mask *c_mask = शून्य;
	__u64 *k_mask = शून्य;

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: start\n", __func__);

	अगर (type) अणु
		c_mask = (काष्ठा client_debug_mask *)mask;
		element_count = cdm_element_count;
	पूर्ण अन्यथा अणु
		k_mask = (__u64 *)mask;
		*k_mask = 0;
		element_count = num_kmod_keyword_mask_map;
	पूर्ण

	original_poपूर्णांकer = strsep_fodder;
	जबतक ((unchecked_keyword = strsep(&strsep_fodder, ",")))
		अगर (म_माप(unchecked_keyword)) अणु
			क्रम (i = 0; i < element_count; i++)
				अगर (type)
					करो_c_mask(i,
						  unchecked_keyword,
						  &c_mask);
				अन्यथा
					करो_k_mask(i,
						  unchecked_keyword,
						  &k_mask);
		पूर्ण

	kमुक्त(original_poपूर्णांकer);
पूर्ण

अटल व्योम करो_c_mask(पूर्णांक i, अक्षर *unchecked_keyword,
    काष्ठा client_debug_mask **sane_mask)
अणु

	अगर (!म_भेद(cdm_array[i].keyword, unchecked_keyword)) अणु
		(**sane_mask).mask1 = (**sane_mask).mask1 | cdm_array[i].mask1;
		(**sane_mask).mask2 = (**sane_mask).mask2 | cdm_array[i].mask2;
	पूर्ण
पूर्ण

अटल व्योम करो_k_mask(पूर्णांक i, अक्षर *unchecked_keyword, __u64 **sane_mask)
अणु

	अगर (!म_भेद(s_kmod_keyword_mask_map[i].keyword, unchecked_keyword))
		**sane_mask = (**sane_mask) |
				s_kmod_keyword_mask_map[i].mask_val;
पूर्ण

पूर्णांक orangefs_debugfs_new_client_mask(व्योम __user *arg)
अणु
	काष्ठा dev_mask2_info_s mask2_info = अणु0पूर्ण;
	पूर्णांक ret;

	ret = copy_from_user(&mask2_info,
			     (व्योम __user *)arg,
			     माप(काष्ठा dev_mask2_info_s));

	अगर (ret != 0)
		वापस -EIO;

	client_debug_mask.mask1 = mask2_info.mask1_value;
	client_debug_mask.mask2 = mask2_info.mask2_value;

	pr_info("%s: client debug mask has been been received "
		":%llx: :%llx:\n",
		__func__,
		(अचिन्हित दीर्घ दीर्घ)client_debug_mask.mask1,
		(अचिन्हित दीर्घ दीर्घ)client_debug_mask.mask2);

	वापस ret;
पूर्ण

पूर्णांक orangefs_debugfs_new_client_string(व्योम __user *arg)
अणु
	पूर्णांक ret;

	ret = copy_from_user(&client_debug_array_string,
			     (व्योम __user *)arg,
			     ORANGEFS_MAX_DEBUG_STRING_LEN);

	अगर (ret != 0) अणु
		pr_info("%s: CLIENT_STRING: copy_from_user failed\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	/*
	 * The real client-core makes an efक्रमt to ensure
	 * that actual strings that aren't too दीर्घ to fit in
	 * this buffer is what we get here. We're going to use
	 * string functions on the stuff we got, so we'll make
	 * this extra efक्रमt to try and keep from
	 * flowing out of this buffer when we use the string
	 * functions, even अगर somehow the stuff we end up
	 * with here is garbage.
	 */
	client_debug_array_string[ORANGEFS_MAX_DEBUG_STRING_LEN - 1] =
		'\0';

	pr_info("%s: client debug array string has been received.\n",
		__func__);

	अगर (!help_string_initialized) अणु

		/* Build a proper debug help string. */
		ret = orangefs_prepare_debugfs_help_string(0);
		अगर (ret) अणु
			gossip_err("%s: no debug help string \n",
				   __func__);
			वापस ret;
		पूर्ण

	पूर्ण

	debug_mask_to_string(&client_debug_mask, 1);

	debugfs_हटाओ(client_debug_dentry);

	orangefs_client_debug_init();

	help_string_initialized++;

	वापस 0;
पूर्ण

पूर्णांक orangefs_debugfs_new_debug(व्योम __user *arg)
अणु
	काष्ठा dev_mask_info_s mask_info = अणु0पूर्ण;
	पूर्णांक ret;

	ret = copy_from_user(&mask_info,
			     (व्योम __user *)arg,
			     माप(mask_info));

	अगर (ret != 0)
		वापस -EIO;

	अगर (mask_info.mask_type == KERNEL_MASK) अणु
		अगर ((mask_info.mask_value == 0)
		    && (kernel_mask_set_mod_init)) अणु
			/*
			 * the kernel debug mask was set when the
			 * kernel module was loaded; करोn't override
			 * it अगर the client-core was started without
			 * a value क्रम ORANGEFS_KMODMASK.
			 */
			वापस 0;
		पूर्ण
		debug_mask_to_string(&mask_info.mask_value,
				     mask_info.mask_type);
		orangefs_gossip_debug_mask = mask_info.mask_value;
		pr_info("%s: kernel debug mask has been modified to "
			":%s: :%llx:\n",
			__func__,
			kernel_debug_string,
			(अचिन्हित दीर्घ दीर्घ)orangefs_gossip_debug_mask);
	पूर्ण अन्यथा अगर (mask_info.mask_type == CLIENT_MASK) अणु
		debug_mask_to_string(&mask_info.mask_value,
				     mask_info.mask_type);
		pr_info("%s: client debug mask has been modified to"
			":%s: :%llx:\n",
			__func__,
			client_debug_string,
			llu(mask_info.mask_value));
	पूर्ण अन्यथा अणु
		gossip_err("Invalid mask type....\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
