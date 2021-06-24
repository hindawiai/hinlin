<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * binfmt_misc.c
 *
 * Copyright (C) 1997 Riअक्षरd Gथञnther
 *
 * binfmt_misc detects binaries via a magic or filename extension and invokes
 * a specअगरied wrapper. See Documentation/admin-guide/binfmt-misc.rst क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/magic.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/string_helpers.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"

#अगर_घोषित DEBUG
# define USE_DEBUG 1
#अन्यथा
# define USE_DEBUG 0
#पूर्ण_अगर

क्रमागत अणु
	VERBOSE_STATUS = 1 /* make it zero to save 400 bytes kernel memory */
पूर्ण;

अटल LIST_HEAD(entries);
अटल पूर्णांक enabled = 1;

क्रमागत अणुEnabled, Magicपूर्ण;
#घोषणा MISC_FMT_PRESERVE_ARGV0 (1 << 31)
#घोषणा MISC_FMT_OPEN_BINARY (1 << 30)
#घोषणा MISC_FMT_CREDENTIALS (1 << 29)
#घोषणा MISC_FMT_OPEN_खाता (1 << 28)

प्रकार काष्ठा अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;		/* type, status, etc. */
	पूर्णांक offset;			/* offset of magic */
	पूर्णांक size;			/* size of magic/mask */
	अक्षर *magic;			/* magic or filename extension */
	अक्षर *mask;			/* mask, शून्य क्रम exact match */
	स्थिर अक्षर *पूर्णांकerpreter;	/* filename of पूर्णांकerpreter */
	अक्षर *name;
	काष्ठा dentry *dentry;
	काष्ठा file *पूर्णांकerp_file;
पूर्ण Node;

अटल DEFINE_RWLOCK(entries_lock);
अटल काष्ठा file_प्रणाली_type bm_fs_type;
अटल काष्ठा vfsmount *bm_mnt;
अटल पूर्णांक entry_count;

/*
 * Max length of the रेजिस्टर string.  Determined by:
 *  - 7 delimiters
 *  - name:   ~50 bytes
 *  - type:   1 byte
 *  - offset: 3 bytes (has to be smaller than BINPRM_BUF_SIZE)
 *  - magic:  128 bytes (512 in escaped क्रमm)
 *  - mask:   128 bytes (512 in escaped क्रमm)
 *  - पूर्णांकerp: ~50 bytes
 *  - flags:  5 bytes
 * Round that up a bit, and then back off to hold the पूर्णांकernal data
 * (like काष्ठा Node).
 */
#घोषणा MAX_REGISTER_LENGTH 1920

/*
 * Check अगर we support the binfmt
 * अगर we करो, वापस the node, अन्यथा शून्य
 * locking is करोne in load_misc_binary
 */
अटल Node *check_file(काष्ठा linux_binprm *bprm)
अणु
	अक्षर *p = म_खोजप(bprm->पूर्णांकerp, '.');
	काष्ठा list_head *l;

	/* Walk all the रेजिस्टरed handlers. */
	list_क्रम_each(l, &entries) अणु
		Node *e = list_entry(l, Node, list);
		अक्षर *s;
		पूर्णांक j;

		/* Make sure this one is currently enabled. */
		अगर (!test_bit(Enabled, &e->flags))
			जारी;

		/* Do matching based on extension अगर applicable. */
		अगर (!test_bit(Magic, &e->flags)) अणु
			अगर (p && !म_भेद(e->magic, p + 1))
				वापस e;
			जारी;
		पूर्ण

		/* Do matching based on magic & mask. */
		s = bprm->buf + e->offset;
		अगर (e->mask) अणु
			क्रम (j = 0; j < e->size; j++)
				अगर ((*s++ ^ e->magic[j]) & e->mask[j])
					अवरोध;
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < e->size; j++)
				अगर ((*s++ ^ e->magic[j]))
					अवरोध;
		पूर्ण
		अगर (j == e->size)
			वापस e;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * the loader itself
 */
अटल पूर्णांक load_misc_binary(काष्ठा linux_binprm *bprm)
अणु
	Node *fmt;
	काष्ठा file *पूर्णांकerp_file = शून्य;
	पूर्णांक retval;

	retval = -ENOEXEC;
	अगर (!enabled)
		वापस retval;

	/* to keep locking समय low, we copy the पूर्णांकerpreter string */
	पढ़ो_lock(&entries_lock);
	fmt = check_file(bprm);
	अगर (fmt)
		dget(fmt->dentry);
	पढ़ो_unlock(&entries_lock);
	अगर (!fmt)
		वापस retval;

	/* Need to be able to load the file after exec */
	retval = -ENOENT;
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		जाओ ret;

	अगर (fmt->flags & MISC_FMT_PRESERVE_ARGV0) अणु
		bprm->पूर्णांकerp_flags |= BINPRM_FLAGS_PRESERVE_ARGV0;
	पूर्ण अन्यथा अणु
		retval = हटाओ_arg_zero(bprm);
		अगर (retval)
			जाओ ret;
	पूर्ण

	अगर (fmt->flags & MISC_FMT_OPEN_BINARY)
		bprm->have_execfd = 1;

	/* make argv[1] be the path to the binary */
	retval = copy_string_kernel(bprm->पूर्णांकerp, bprm);
	अगर (retval < 0)
		जाओ ret;
	bprm->argc++;

	/* add the पूर्णांकerp as argv[0] */
	retval = copy_string_kernel(fmt->पूर्णांकerpreter, bprm);
	अगर (retval < 0)
		जाओ ret;
	bprm->argc++;

	/* Update पूर्णांकerp in हाल binfmt_script needs it. */
	retval = bprm_change_पूर्णांकerp(fmt->पूर्णांकerpreter, bprm);
	अगर (retval < 0)
		जाओ ret;

	अगर (fmt->flags & MISC_FMT_OPEN_खाता) अणु
		पूर्णांकerp_file = file_clone_खोलो(fmt->पूर्णांकerp_file);
		अगर (!IS_ERR(पूर्णांकerp_file))
			deny_ग_लिखो_access(पूर्णांकerp_file);
	पूर्ण अन्यथा अणु
		पूर्णांकerp_file = खोलो_exec(fmt->पूर्णांकerpreter);
	पूर्ण
	retval = PTR_ERR(पूर्णांकerp_file);
	अगर (IS_ERR(पूर्णांकerp_file))
		जाओ ret;

	bprm->पूर्णांकerpreter = पूर्णांकerp_file;
	अगर (fmt->flags & MISC_FMT_CREDENTIALS)
		bprm->execfd_creds = 1;

	retval = 0;
ret:
	dput(fmt->dentry);
	वापस retval;
पूर्ण

/* Command parsers */

/*
 * parses and copies one argument enबंदd in del from *sp to *dp,
 * recognising the \ष special.
 * वापसs poपूर्णांकer to the copied argument or शून्य in हाल of an
 * error (and sets err) or null argument length.
 */
अटल अक्षर *scanarg(अक्षर *s, अक्षर del)
अणु
	अक्षर c;

	जबतक ((c = *s++) != del) अणु
		अगर (c == '\\' && *s == 'x') अणु
			s++;
			अगर (!है_षष्ठादशक(*s++))
				वापस शून्य;
			अगर (!है_षष्ठादशक(*s++))
				वापस शून्य;
		पूर्ण
	पूर्ण
	s[-1] ='\0';
	वापस s;
पूर्ण

अटल अक्षर *check_special_flags(अक्षर *sfs, Node *e)
अणु
	अक्षर *p = sfs;
	पूर्णांक cont = 1;

	/* special flags */
	जबतक (cont) अणु
		चयन (*p) अणु
		हाल 'P':
			pr_debug("register: flag: P (preserve argv0)\n");
			p++;
			e->flags |= MISC_FMT_PRESERVE_ARGV0;
			अवरोध;
		हाल 'O':
			pr_debug("register: flag: O (open binary)\n");
			p++;
			e->flags |= MISC_FMT_OPEN_BINARY;
			अवरोध;
		हाल 'C':
			pr_debug("register: flag: C (preserve creds)\n");
			p++;
			/* this flags also implies the
			   खोलो-binary flag */
			e->flags |= (MISC_FMT_CREDENTIALS |
					MISC_FMT_OPEN_BINARY);
			अवरोध;
		हाल 'F':
			pr_debug("register: flag: F: open interpreter file now\n");
			p++;
			e->flags |= MISC_FMT_OPEN_खाता;
			अवरोध;
		शेष:
			cont = 0;
		पूर्ण
	पूर्ण

	वापस p;
पूर्ण

/*
 * This रेजिस्टरs a new binary क्रमmat, it recognises the syntax
 * ':name:type:offset:magic:mask:interpreter:flags'
 * where the ':' is the IFS, that can be chosen with the first अक्षर
 */
अटल Node *create_entry(स्थिर अक्षर __user *buffer, माप_प्रकार count)
अणु
	Node *e;
	पूर्णांक memsize, err;
	अक्षर *buf, *p;
	अक्षर del;

	pr_debug("register: received %zu bytes\n", count);

	/* some sanity checks */
	err = -EINVAL;
	अगर ((count < 11) || (count > MAX_REGISTER_LENGTH))
		जाओ out;

	err = -ENOMEM;
	memsize = माप(Node) + count + 8;
	e = kदो_स्मृति(memsize, GFP_KERNEL);
	अगर (!e)
		जाओ out;

	p = buf = (अक्षर *)e + माप(Node);

	स_रखो(e, 0, माप(Node));
	अगर (copy_from_user(buf, buffer, count))
		जाओ efault;

	del = *p++;	/* delimeter */

	pr_debug("register: delim: %#x {%c}\n", del, del);

	/* Pad the buffer with the delim to simplअगरy parsing below. */
	स_रखो(buf + count, del, 8);

	/* Parse the 'name' field. */
	e->name = p;
	p = म_अक्षर(p, del);
	अगर (!p)
		जाओ einval;
	*p++ = '\0';
	अगर (!e->name[0] ||
	    !म_भेद(e->name, ".") ||
	    !म_भेद(e->name, "..") ||
	    म_अक्षर(e->name, '/'))
		जाओ einval;

	pr_debug("register: name: {%s}\n", e->name);

	/* Parse the 'type' field. */
	चयन (*p++) अणु
	हाल 'E':
		pr_debug("register: type: E (extension)\n");
		e->flags = 1 << Enabled;
		अवरोध;
	हाल 'M':
		pr_debug("register: type: M (magic)\n");
		e->flags = (1 << Enabled) | (1 << Magic);
		अवरोध;
	शेष:
		जाओ einval;
	पूर्ण
	अगर (*p++ != del)
		जाओ einval;

	अगर (test_bit(Magic, &e->flags)) अणु
		/* Handle the 'M' (magic) क्रमmat. */
		अक्षर *s;

		/* Parse the 'offset' field. */
		s = म_अक्षर(p, del);
		अगर (!s)
			जाओ einval;
		*s = '\0';
		अगर (p != s) अणु
			पूर्णांक r = kstrtoपूर्णांक(p, 10, &e->offset);
			अगर (r != 0 || e->offset < 0)
				जाओ einval;
		पूर्ण
		p = s;
		अगर (*p++)
			जाओ einval;
		pr_debug("register: offset: %#x\n", e->offset);

		/* Parse the 'magic' field. */
		e->magic = p;
		p = scanarg(p, del);
		अगर (!p)
			जाओ einval;
		अगर (!e->magic[0])
			जाओ einval;
		अगर (USE_DEBUG)
			prपूर्णांक_hex_dump_bytes(
				KBUILD_MODNAME ": register: magic[raw]: ",
				DUMP_PREFIX_NONE, e->magic, p - e->magic);

		/* Parse the 'mask' field. */
		e->mask = p;
		p = scanarg(p, del);
		अगर (!p)
			जाओ einval;
		अगर (!e->mask[0]) अणु
			e->mask = शून्य;
			pr_debug("register:  mask[raw]: none\n");
		पूर्ण अन्यथा अगर (USE_DEBUG)
			prपूर्णांक_hex_dump_bytes(
				KBUILD_MODNAME ": register:  mask[raw]: ",
				DUMP_PREFIX_NONE, e->mask, p - e->mask);

		/*
		 * Decode the magic & mask fields.
		 * Note: जबतक we might have accepted embedded NUL bytes from
		 * above, the unescape helpers here will stop at the first one
		 * it encounters.
		 */
		e->size = string_unescape_inplace(e->magic, UNESCAPE_HEX);
		अगर (e->mask &&
		    string_unescape_inplace(e->mask, UNESCAPE_HEX) != e->size)
			जाओ einval;
		अगर (e->size > BINPRM_BUF_SIZE ||
		    BINPRM_BUF_SIZE - e->size < e->offset)
			जाओ einval;
		pr_debug("register: magic/mask length: %i\n", e->size);
		अगर (USE_DEBUG) अणु
			prपूर्णांक_hex_dump_bytes(
				KBUILD_MODNAME ": register: magic[decoded]: ",
				DUMP_PREFIX_NONE, e->magic, e->size);

			अगर (e->mask) अणु
				पूर्णांक i;
				अक्षर *masked = kदो_स्मृति(e->size, GFP_KERNEL);

				prपूर्णांक_hex_dump_bytes(
					KBUILD_MODNAME ": register:  mask[decoded]: ",
					DUMP_PREFIX_NONE, e->mask, e->size);

				अगर (masked) अणु
					क्रम (i = 0; i < e->size; ++i)
						masked[i] = e->magic[i] & e->mask[i];
					prपूर्णांक_hex_dump_bytes(
						KBUILD_MODNAME ": register:  magic[masked]: ",
						DUMP_PREFIX_NONE, masked, e->size);

					kमुक्त(masked);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Handle the 'E' (extension) क्रमmat. */

		/* Skip the 'offset' field. */
		p = म_अक्षर(p, del);
		अगर (!p)
			जाओ einval;
		*p++ = '\0';

		/* Parse the 'magic' field. */
		e->magic = p;
		p = म_अक्षर(p, del);
		अगर (!p)
			जाओ einval;
		*p++ = '\0';
		अगर (!e->magic[0] || म_अक्षर(e->magic, '/'))
			जाओ einval;
		pr_debug("register: extension: {%s}\n", e->magic);

		/* Skip the 'mask' field. */
		p = म_अक्षर(p, del);
		अगर (!p)
			जाओ einval;
		*p++ = '\0';
	पूर्ण

	/* Parse the 'interpreter' field. */
	e->पूर्णांकerpreter = p;
	p = म_अक्षर(p, del);
	अगर (!p)
		जाओ einval;
	*p++ = '\0';
	अगर (!e->पूर्णांकerpreter[0])
		जाओ einval;
	pr_debug("register: interpreter: {%s}\n", e->पूर्णांकerpreter);

	/* Parse the 'flags' field. */
	p = check_special_flags(p, e);
	अगर (*p == '\n')
		p++;
	अगर (p != buf + count)
		जाओ einval;

	वापस e;

out:
	वापस ERR_PTR(err);

efault:
	kमुक्त(e);
	वापस ERR_PTR(-EFAULT);
einval:
	kमुक्त(e);
	वापस ERR_PTR(-EINVAL);
पूर्ण

/*
 * Set status of entry/binfmt_misc:
 * '1' enables, '0' disables and '-1' clears entry/binfmt_misc
 */
अटल पूर्णांक parse_command(स्थिर अक्षर __user *buffer, माप_प्रकार count)
अणु
	अक्षर s[4];

	अगर (count > 3)
		वापस -EINVAL;
	अगर (copy_from_user(s, buffer, count))
		वापस -EFAULT;
	अगर (!count)
		वापस 0;
	अगर (s[count - 1] == '\n')
		count--;
	अगर (count == 1 && s[0] == '0')
		वापस 1;
	अगर (count == 1 && s[0] == '1')
		वापस 2;
	अगर (count == 2 && s[0] == '-' && s[1] == '1')
		वापस 3;
	वापस -EINVAL;
पूर्ण

/* generic stuff */

अटल व्योम entry_status(Node *e, अक्षर *page)
अणु
	अक्षर *dp = page;
	स्थिर अक्षर *status = "disabled";

	अगर (test_bit(Enabled, &e->flags))
		status = "enabled";

	अगर (!VERBOSE_STATUS) अणु
		प्र_लिखो(page, "%s\n", status);
		वापस;
	पूर्ण

	dp += प्र_लिखो(dp, "%s\ninterpreter %s\n", status, e->पूर्णांकerpreter);

	/* prपूर्णांक the special flags */
	dp += प्र_लिखो(dp, "flags: ");
	अगर (e->flags & MISC_FMT_PRESERVE_ARGV0)
		*dp++ = 'P';
	अगर (e->flags & MISC_FMT_OPEN_BINARY)
		*dp++ = 'O';
	अगर (e->flags & MISC_FMT_CREDENTIALS)
		*dp++ = 'C';
	अगर (e->flags & MISC_FMT_OPEN_खाता)
		*dp++ = 'F';
	*dp++ = '\n';

	अगर (!test_bit(Magic, &e->flags)) अणु
		प्र_लिखो(dp, "extension .%s\n", e->magic);
	पूर्ण अन्यथा अणु
		dp += प्र_लिखो(dp, "offset %i\nmagic ", e->offset);
		dp = bin2hex(dp, e->magic, e->size);
		अगर (e->mask) अणु
			dp += प्र_लिखो(dp, "\nmask ");
			dp = bin2hex(dp, e->mask, e->size);
		पूर्ण
		*dp++ = '\n';
		*dp = '\0';
	पूर्ण
पूर्ण

अटल काष्ठा inode *bm_get_inode(काष्ठा super_block *sb, पूर्णांक mode)
अणु
	काष्ठा inode *inode = new_inode(sb);

	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय =
			current_समय(inode);
	पूर्ण
	वापस inode;
पूर्ण

अटल व्योम bm_evict_inode(काष्ठा inode *inode)
अणु
	Node *e = inode->i_निजी;

	अगर (e && e->flags & MISC_FMT_OPEN_खाता)
		filp_बंद(e->पूर्णांकerp_file, शून्य);

	clear_inode(inode);
	kमुक्त(e);
पूर्ण

अटल व्योम समाप्त_node(Node *e)
अणु
	काष्ठा dentry *dentry;

	ग_लिखो_lock(&entries_lock);
	list_del_init(&e->list);
	ग_लिखो_unlock(&entries_lock);

	dentry = e->dentry;
	drop_nlink(d_inode(dentry));
	d_drop(dentry);
	dput(dentry);
	simple_release_fs(&bm_mnt, &entry_count);
पूर्ण

/* /<entry> */

अटल sमाप_प्रकार
bm_entry_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes, loff_t *ppos)
अणु
	Node *e = file_inode(file)->i_निजी;
	sमाप_प्रकार res;
	अक्षर *page;

	page = (अक्षर *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	entry_status(e, page);

	res = simple_पढ़ो_from_buffer(buf, nbytes, ppos, page, म_माप(page));

	मुक्त_page((अचिन्हित दीर्घ) page);
	वापस res;
पूर्ण

अटल sमाप_प्रकार bm_entry_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dentry *root;
	Node *e = file_inode(file)->i_निजी;
	पूर्णांक res = parse_command(buffer, count);

	चयन (res) अणु
	हाल 1:
		/* Disable this handler. */
		clear_bit(Enabled, &e->flags);
		अवरोध;
	हाल 2:
		/* Enable this handler. */
		set_bit(Enabled, &e->flags);
		अवरोध;
	हाल 3:
		/* Delete this handler. */
		root = file_inode(file)->i_sb->s_root;
		inode_lock(d_inode(root));

		अगर (!list_empty(&e->list))
			समाप्त_node(e);

		inode_unlock(d_inode(root));
		अवरोध;
	शेष:
		वापस res;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations bm_entry_operations = अणु
	.पढ़ो		= bm_entry_पढ़ो,
	.ग_लिखो		= bm_entry_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

/* /रेजिस्टर */

अटल sमाप_प्रकार bm_रेजिस्टर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			       माप_प्रकार count, loff_t *ppos)
अणु
	Node *e;
	काष्ठा inode *inode;
	काष्ठा super_block *sb = file_inode(file)->i_sb;
	काष्ठा dentry *root = sb->s_root, *dentry;
	पूर्णांक err = 0;
	काष्ठा file *f = शून्य;

	e = create_entry(buffer, count);

	अगर (IS_ERR(e))
		वापस PTR_ERR(e);

	अगर (e->flags & MISC_FMT_OPEN_खाता) अणु
		f = खोलो_exec(e->पूर्णांकerpreter);
		अगर (IS_ERR(f)) अणु
			pr_notice("register: failed to install interpreter file %s\n",
				 e->पूर्णांकerpreter);
			kमुक्त(e);
			वापस PTR_ERR(f);
		पूर्ण
		e->पूर्णांकerp_file = f;
	पूर्ण

	inode_lock(d_inode(root));
	dentry = lookup_one_len(e->name, root, म_माप(e->name));
	err = PTR_ERR(dentry);
	अगर (IS_ERR(dentry))
		जाओ out;

	err = -EEXIST;
	अगर (d_really_is_positive(dentry))
		जाओ out2;

	inode = bm_get_inode(sb, S_IFREG | 0644);

	err = -ENOMEM;
	अगर (!inode)
		जाओ out2;

	err = simple_pin_fs(&bm_fs_type, &bm_mnt, &entry_count);
	अगर (err) अणु
		iput(inode);
		inode = शून्य;
		जाओ out2;
	पूर्ण

	e->dentry = dget(dentry);
	inode->i_निजी = e;
	inode->i_fop = &bm_entry_operations;

	d_instantiate(dentry, inode);
	ग_लिखो_lock(&entries_lock);
	list_add(&e->list, &entries);
	ग_लिखो_unlock(&entries_lock);

	err = 0;
out2:
	dput(dentry);
out:
	inode_unlock(d_inode(root));

	अगर (err) अणु
		अगर (f)
			filp_बंद(f, शून्य);
		kमुक्त(e);
		वापस err;
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations bm_रेजिस्टर_operations = अणु
	.ग_लिखो		= bm_रेजिस्टर_ग_लिखो,
	.llseek		= noop_llseek,
पूर्ण;

/* /status */

अटल sमाप_प्रकार
bm_status_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes, loff_t *ppos)
अणु
	अक्षर *s = enabled ? "enabled\n" : "disabled\n";

	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, s, म_माप(s));
पूर्ण

अटल sमाप_प्रकार bm_status_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक res = parse_command(buffer, count);
	काष्ठा dentry *root;

	चयन (res) अणु
	हाल 1:
		/* Disable all handlers. */
		enabled = 0;
		अवरोध;
	हाल 2:
		/* Enable all handlers. */
		enabled = 1;
		अवरोध;
	हाल 3:
		/* Delete all handlers. */
		root = file_inode(file)->i_sb->s_root;
		inode_lock(d_inode(root));

		जबतक (!list_empty(&entries))
			समाप्त_node(list_first_entry(&entries, Node, list));

		inode_unlock(d_inode(root));
		अवरोध;
	शेष:
		वापस res;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations bm_status_operations = अणु
	.पढ़ो		= bm_status_पढ़ो,
	.ग_लिखो		= bm_status_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

/* Superblock handling */

अटल स्थिर काष्ठा super_operations s_ops = अणु
	.statfs		= simple_statfs,
	.evict_inode	= bm_evict_inode,
पूर्ण;

अटल पूर्णांक bm_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	पूर्णांक err;
	अटल स्थिर काष्ठा tree_descr bm_files[] = अणु
		[2] = अणु"status", &bm_status_operations, S_IWUSR|S_IRUGOपूर्ण,
		[3] = अणु"register", &bm_रेजिस्टर_operations, S_IWUSRपूर्ण,
		/* last one */ अणु""पूर्ण
	पूर्ण;

	err = simple_fill_super(sb, BINFMTFS_MAGIC, bm_files);
	अगर (!err)
		sb->s_op = &s_ops;
	वापस err;
पूर्ण

अटल पूर्णांक bm_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, bm_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations bm_context_ops = अणु
	.get_tree	= bm_get_tree,
पूर्ण;

अटल पूर्णांक bm_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &bm_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा linux_binfmt misc_क्रमmat = अणु
	.module = THIS_MODULE,
	.load_binary = load_misc_binary,
पूर्ण;

अटल काष्ठा file_प्रणाली_type bm_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "binfmt_misc",
	.init_fs_context = bm_init_fs_context,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("binfmt_misc");

अटल पूर्णांक __init init_misc_binfmt(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_fileप्रणाली(&bm_fs_type);
	अगर (!err)
		insert_binfmt(&misc_क्रमmat);
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_misc_binfmt(व्योम)
अणु
	unरेजिस्टर_binfmt(&misc_क्रमmat);
	unरेजिस्टर_fileप्रणाली(&bm_fs_type);
पूर्ण

core_initcall(init_misc_binfmt);
module_निकास(निकास_misc_binfmt);
MODULE_LICENSE("GPL");
