<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/seq_file.c
 *
 * helper functions क्रम making synthetic files from sequences of records.
 * initial implementation -- AV, Oct 2001.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cache.h>
#समावेश <linux/fs.h>
#समावेश <linux/export.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/mm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/uपन.स>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>

अटल काष्ठा kmem_cache *seq_file_cache __ro_after_init;

अटल व्योम seq_set_overflow(काष्ठा seq_file *m)
अणु
	m->count = m->size;
पूर्ण

अटल व्योम *seq_buf_alloc(अचिन्हित दीर्घ size)
अणु
	वापस kvदो_स्मृति(size, GFP_KERNEL_ACCOUNT);
पूर्ण

/**
 *	seq_खोलो -	initialize sequential file
 *	@file: file we initialize
 *	@op: method table describing the sequence
 *
 *	seq_खोलो() sets @file, associating it with a sequence described
 *	by @op.  @op->start() sets the iterator up and वापसs the first
 *	element of sequence. @op->stop() shuts it करोwn.  @op->next()
 *	वापसs the next element of sequence.  @op->show() prपूर्णांकs element
 *	पूर्णांकo the buffer.  In हाल of error ->start() and ->next() वापस
 *	ERR_PTR(error).  In the end of sequence they वापस %शून्य. ->show()
 *	वापसs 0 in हाल of success and negative number in हाल of error.
 *	Returning SEQ_SKIP means "discard this element and move on".
 *	Note: seq_खोलो() will allocate a काष्ठा seq_file and store its
 *	poपूर्णांकer in @file->निजी_data. This poपूर्णांकer should not be modअगरied.
 */
पूर्णांक seq_खोलो(काष्ठा file *file, स्थिर काष्ठा seq_operations *op)
अणु
	काष्ठा seq_file *p;

	WARN_ON(file->निजी_data);

	p = kmem_cache_zalloc(seq_file_cache, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	file->निजी_data = p;

	mutex_init(&p->lock);
	p->op = op;

	// No refcounting: the lअगरeसमय of 'p' is स्थिरrained
	// to the lअगरeसमय of the file.
	p->file = file;

	/*
	 * seq_files support lseek() and pपढ़ो().  They करो not implement
	 * ग_लिखो() at all, but we clear FMODE_PWRITE here क्रम historical
	 * reasons.
	 *
	 * If a client of seq_files a) implements file.ग_लिखो() and b) wishes to
	 * support pग_लिखो() then that client will need to implement its own
	 * file.खोलो() which calls seq_खोलो() and then sets FMODE_PWRITE.
	 */
	file->f_mode &= ~FMODE_PWRITE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(seq_खोलो);

अटल पूर्णांक traverse(काष्ठा seq_file *m, loff_t offset)
अणु
	loff_t pos = 0;
	पूर्णांक error = 0;
	व्योम *p;

	m->index = 0;
	m->count = m->from = 0;
	अगर (!offset)
		वापस 0;

	अगर (!m->buf) अणु
		m->buf = seq_buf_alloc(m->size = PAGE_SIZE);
		अगर (!m->buf)
			वापस -ENOMEM;
	पूर्ण
	p = m->op->start(m, &m->index);
	जबतक (p) अणु
		error = PTR_ERR(p);
		अगर (IS_ERR(p))
			अवरोध;
		error = m->op->show(m, p);
		अगर (error < 0)
			अवरोध;
		अगर (unlikely(error)) अणु
			error = 0;
			m->count = 0;
		पूर्ण
		अगर (seq_has_overflowed(m))
			जाओ Eoverflow;
		p = m->op->next(m, p, &m->index);
		अगर (pos + m->count > offset) अणु
			m->from = offset - pos;
			m->count -= m->from;
			अवरोध;
		पूर्ण
		pos += m->count;
		m->count = 0;
		अगर (pos == offset)
			अवरोध;
	पूर्ण
	m->op->stop(m, p);
	वापस error;

Eoverflow:
	m->op->stop(m, p);
	kvमुक्त(m->buf);
	m->count = 0;
	m->buf = seq_buf_alloc(m->size <<= 1);
	वापस !m->buf ? -ENOMEM : -EAGAIN;
पूर्ण

/**
 *	seq_पढ़ो -	->पढ़ो() method क्रम sequential files.
 *	@file: the file to पढ़ो from
 *	@buf: the buffer to पढ़ो to
 *	@size: the maximum number of bytes to पढ़ो
 *	@ppos: the current position in the file
 *
 *	Ready-made ->f_op->पढ़ो()
 */
sमाप_प्रकार seq_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा iovec iov = अणु .iov_base = buf, .iov_len = sizeपूर्ण;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	init_sync_kiocb(&kiocb, file);
	iov_iter_init(&iter, READ, &iov, 1, size);

	kiocb.ki_pos = *ppos;
	ret = seq_पढ़ो_iter(&kiocb, &iter);
	*ppos = kiocb.ki_pos;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(seq_पढ़ो);

/*
 * Ready-made ->f_op->पढ़ो_iter()
 */
sमाप_प्रकार seq_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा seq_file *m = iocb->ki_filp->निजी_data;
	माप_प्रकार copied = 0;
	माप_प्रकार n;
	व्योम *p;
	पूर्णांक err = 0;

	अगर (!iov_iter_count(iter))
		वापस 0;

	mutex_lock(&m->lock);

	/*
	 * अगर request is to पढ़ो from zero offset, reset iterator to first
	 * record as it might have been alपढ़ोy advanced by previous requests
	 */
	अगर (iocb->ki_pos == 0) अणु
		m->index = 0;
		m->count = 0;
	पूर्ण

	/* Don't assume ki_pos is where we left it */
	अगर (unlikely(iocb->ki_pos != m->पढ़ो_pos)) अणु
		जबतक ((err = traverse(m, iocb->ki_pos)) == -EAGAIN)
			;
		अगर (err) अणु
			/* With prejudice... */
			m->पढ़ो_pos = 0;
			m->index = 0;
			m->count = 0;
			जाओ Done;
		पूर्ण अन्यथा अणु
			m->पढ़ो_pos = iocb->ki_pos;
		पूर्ण
	पूर्ण

	/* grab buffer अगर we didn't have one */
	अगर (!m->buf) अणु
		m->buf = seq_buf_alloc(m->size = PAGE_SIZE);
		अगर (!m->buf)
			जाओ Enomem;
	पूर्ण
	// something left in the buffer - copy it out first
	अगर (m->count) अणु
		n = copy_to_iter(m->buf + m->from, m->count, iter);
		m->count -= n;
		m->from += n;
		copied += n;
		अगर (m->count)	// hadn't managed to copy everything
			जाओ Done;
	पूर्ण
	// get a non-empty record in the buffer
	m->from = 0;
	p = m->op->start(m, &m->index);
	जबतक (1) अणु
		err = PTR_ERR(p);
		अगर (!p || IS_ERR(p))	// खातापूर्ण or an error
			अवरोध;
		err = m->op->show(m, p);
		अगर (err < 0)		// hard error
			अवरोध;
		अगर (unlikely(err))	// ->show() says "skip it"
			m->count = 0;
		अगर (unlikely(!m->count)) अणु // empty record
			p = m->op->next(m, p, &m->index);
			जारी;
		पूर्ण
		अगर (!seq_has_overflowed(m)) // got it
			जाओ Fill;
		// need a bigger buffer
		m->op->stop(m, p);
		kvमुक्त(m->buf);
		m->count = 0;
		m->buf = seq_buf_alloc(m->size <<= 1);
		अगर (!m->buf)
			जाओ Enomem;
		p = m->op->start(m, &m->index);
	पूर्ण
	// खातापूर्ण or an error
	m->op->stop(m, p);
	m->count = 0;
	जाओ Done;
Fill:
	// one non-empty record is in the buffer; अगर they want more,
	// try to fit more in, but in any हाल we need to advance
	// the iterator once क्रम every record shown.
	जबतक (1) अणु
		माप_प्रकार offs = m->count;
		loff_t pos = m->index;

		p = m->op->next(m, p, &m->index);
		अगर (pos == m->index) अणु
			pr_info_ratelimited("buggy .next function %ps did not update position index\n",
					    m->op->next);
			m->index++;
		पूर्ण
		अगर (!p || IS_ERR(p))	// no next record क्रम us
			अवरोध;
		अगर (m->count >= iov_iter_count(iter))
			अवरोध;
		err = m->op->show(m, p);
		अगर (err > 0) अणु		// ->show() says "skip it"
			m->count = offs;
		पूर्ण अन्यथा अगर (err || seq_has_overflowed(m)) अणु
			m->count = offs;
			अवरोध;
		पूर्ण
	पूर्ण
	m->op->stop(m, p);
	n = copy_to_iter(m->buf, m->count, iter);
	copied += n;
	m->count -= n;
	m->from = n;
Done:
	अगर (unlikely(!copied)) अणु
		copied = m->count ? -EFAULT : err;
	पूर्ण अन्यथा अणु
		iocb->ki_pos += copied;
		m->पढ़ो_pos += copied;
	पूर्ण
	mutex_unlock(&m->lock);
	वापस copied;
Enomem:
	err = -ENOMEM;
	जाओ Done;
पूर्ण
EXPORT_SYMBOL(seq_पढ़ो_iter);

/**
 *	seq_lseek -	->llseek() method क्रम sequential files.
 *	@file: the file in question
 *	@offset: new position
 *	@whence: 0 क्रम असलolute, 1 क्रम relative position
 *
 *	Ready-made ->f_op->llseek()
 */
loff_t seq_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	loff_t retval = -EINVAL;

	mutex_lock(&m->lock);
	चयन (whence) अणु
	हाल प्रस्तुत_से:
		offset += file->f_pos;
		fallthrough;
	हाल शुरू_से:
		अगर (offset < 0)
			अवरोध;
		retval = offset;
		अगर (offset != m->पढ़ो_pos) अणु
			जबतक ((retval = traverse(m, offset)) == -EAGAIN)
				;
			अगर (retval) अणु
				/* with extreme prejudice... */
				file->f_pos = 0;
				m->पढ़ो_pos = 0;
				m->index = 0;
				m->count = 0;
			पूर्ण अन्यथा अणु
				m->पढ़ो_pos = offset;
				retval = file->f_pos = offset;
			पूर्ण
		पूर्ण अन्यथा अणु
			file->f_pos = offset;
		पूर्ण
	पूर्ण
	mutex_unlock(&m->lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(seq_lseek);

/**
 *	seq_release -	मुक्त the काष्ठाures associated with sequential file.
 *	@file: file in question
 *	@inode: its inode
 *
 *	Frees the काष्ठाures associated with sequential file; can be used
 *	as ->f_op->release() अगर you करोn't have निजी data to destroy.
 */
पूर्णांक seq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	kvमुक्त(m->buf);
	kmem_cache_मुक्त(seq_file_cache, m);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(seq_release);

/**
 *	seq_escape -	prपूर्णांक string पूर्णांकo buffer, escaping some अक्षरacters
 *	@m:	target buffer
 *	@s:	string
 *	@esc:	set of अक्षरacters that need escaping
 *
 *	Puts string पूर्णांकo buffer, replacing each occurrence of अक्षरacter from
 *	@esc with usual octal escape.
 *	Use seq_has_overflowed() to check क्रम errors.
 */
व्योम seq_escape(काष्ठा seq_file *m, स्थिर अक्षर *s, स्थिर अक्षर *esc)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_get_buf(m, &buf);
	पूर्णांक ret;

	ret = string_escape_str(s, buf, size, ESCAPE_OCTAL, esc);
	seq_commit(m, ret < size ? ret : -1);
पूर्ण
EXPORT_SYMBOL(seq_escape);

व्योम seq_escape_mem_ascii(काष्ठा seq_file *m, स्थिर अक्षर *src, माप_प्रकार isz)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_get_buf(m, &buf);
	पूर्णांक ret;

	ret = string_escape_mem_ascii(src, isz, buf, size);
	seq_commit(m, ret < size ? ret : -1);
पूर्ण
EXPORT_SYMBOL(seq_escape_mem_ascii);

व्योम seq_भ_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *f, बहु_सूची args)
अणु
	पूर्णांक len;

	अगर (m->count < m->size) अणु
		len = vsnम_लिखो(m->buf + m->count, m->size - m->count, f, args);
		अगर (m->count + len < m->size) अणु
			m->count += len;
			वापस;
		पूर्ण
	पूर्ण
	seq_set_overflow(m);
पूर्ण
EXPORT_SYMBOL(seq_भ_लिखो);

व्योम seq_म_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *f, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, f);
	seq_भ_लिखो(m, f, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(seq_म_लिखो);

#अगर_घोषित CONFIG_BINARY_PRINTF
व्योम seq_bम_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *f, स्थिर u32 *binary)
अणु
	पूर्णांक len;

	अगर (m->count < m->size) अणु
		len = bstr_म_लिखो(m->buf + m->count, m->size - m->count, f,
				  binary);
		अगर (m->count + len < m->size) अणु
			m->count += len;
			वापस;
		पूर्ण
	पूर्ण
	seq_set_overflow(m);
पूर्ण
EXPORT_SYMBOL(seq_bम_लिखो);
#पूर्ण_अगर /* CONFIG_BINARY_PRINTF */

/**
 *	mangle_path -	mangle and copy path to buffer beginning
 *	@s: buffer start
 *	@p: beginning of path in above buffer
 *	@esc: set of अक्षरacters that need escaping
 *
 *      Copy the path from @p to @s, replacing each occurrence of अक्षरacter from
 *      @esc with usual octal escape.
 *      Returns poपूर्णांकer past last written अक्षरacter in @s, or शून्य in हाल of
 *      failure.
 */
अक्षर *mangle_path(अक्षर *s, स्थिर अक्षर *p, स्थिर अक्षर *esc)
अणु
	जबतक (s <= p) अणु
		अक्षर c = *p++;
		अगर (!c) अणु
			वापस s;
		पूर्ण अन्यथा अगर (!म_अक्षर(esc, c)) अणु
			*s++ = c;
		पूर्ण अन्यथा अगर (s + 4 > p) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			*s++ = '\\';
			*s++ = '0' + ((c & 0300) >> 6);
			*s++ = '0' + ((c & 070) >> 3);
			*s++ = '0' + (c & 07);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mangle_path);

/**
 * seq_path - seq_file पूर्णांकerface to prपूर्णांक a pathname
 * @m: the seq_file handle
 * @path: the काष्ठा path to prपूर्णांक
 * @esc: set of अक्षरacters to escape in the output
 *
 * वापस the असलolute path of 'path', as represented by the
 * dentry / mnt pair in the path parameter.
 */
पूर्णांक seq_path(काष्ठा seq_file *m, स्थिर काष्ठा path *path, स्थिर अक्षर *esc)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_get_buf(m, &buf);
	पूर्णांक res = -1;

	अगर (size) अणु
		अक्षर *p = d_path(path, buf, size);
		अगर (!IS_ERR(p)) अणु
			अक्षर *end = mangle_path(buf, p, esc);
			अगर (end)
				res = end - buf;
		पूर्ण
	पूर्ण
	seq_commit(m, res);

	वापस res;
पूर्ण
EXPORT_SYMBOL(seq_path);

/**
 * seq_file_path - seq_file पूर्णांकerface to prपूर्णांक a pathname of a file
 * @m: the seq_file handle
 * @file: the काष्ठा file to prपूर्णांक
 * @esc: set of अक्षरacters to escape in the output
 *
 * वापस the असलolute path to the file.
 */
पूर्णांक seq_file_path(काष्ठा seq_file *m, काष्ठा file *file, स्थिर अक्षर *esc)
अणु
	वापस seq_path(m, &file->f_path, esc);
पूर्ण
EXPORT_SYMBOL(seq_file_path);

/*
 * Same as seq_path, but relative to supplied root.
 */
पूर्णांक seq_path_root(काष्ठा seq_file *m, स्थिर काष्ठा path *path,
		  स्थिर काष्ठा path *root, स्थिर अक्षर *esc)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_get_buf(m, &buf);
	पूर्णांक res = -ENAMETOOLONG;

	अगर (size) अणु
		अक्षर *p;

		p = __d_path(path, root, buf, size);
		अगर (!p)
			वापस SEQ_SKIP;
		res = PTR_ERR(p);
		अगर (!IS_ERR(p)) अणु
			अक्षर *end = mangle_path(buf, p, esc);
			अगर (end)
				res = end - buf;
			अन्यथा
				res = -ENAMETOOLONG;
		पूर्ण
	पूर्ण
	seq_commit(m, res);

	वापस res < 0 && res != -ENAMETOOLONG ? res : 0;
पूर्ण

/*
 * वापसs the path of the 'dentry' from the root of its fileप्रणाली.
 */
पूर्णांक seq_dentry(काष्ठा seq_file *m, काष्ठा dentry *dentry, स्थिर अक्षर *esc)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_get_buf(m, &buf);
	पूर्णांक res = -1;

	अगर (size) अणु
		अक्षर *p = dentry_path(dentry, buf, size);
		अगर (!IS_ERR(p)) अणु
			अक्षर *end = mangle_path(buf, p, esc);
			अगर (end)
				res = end - buf;
		पूर्ण
	पूर्ण
	seq_commit(m, res);

	वापस res;
पूर्ण
EXPORT_SYMBOL(seq_dentry);

अटल व्योम *single_start(काष्ठा seq_file *p, loff_t *pos)
अणु
	वापस शून्य + (*pos == 0);
पूर्ण

अटल व्योम *single_next(काष्ठा seq_file *p, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस शून्य;
पूर्ण

अटल व्योम single_stop(काष्ठा seq_file *p, व्योम *v)
अणु
पूर्ण

पूर्णांक single_खोलो(काष्ठा file *file, पूर्णांक (*show)(काष्ठा seq_file *, व्योम *),
		व्योम *data)
अणु
	काष्ठा seq_operations *op = kदो_स्मृति(माप(*op), GFP_KERNEL_ACCOUNT);
	पूर्णांक res = -ENOMEM;

	अगर (op) अणु
		op->start = single_start;
		op->next = single_next;
		op->stop = single_stop;
		op->show = show;
		res = seq_खोलो(file, op);
		अगर (!res)
			((काष्ठा seq_file *)file->निजी_data)->निजी = data;
		अन्यथा
			kमुक्त(op);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(single_खोलो);

पूर्णांक single_खोलो_size(काष्ठा file *file, पूर्णांक (*show)(काष्ठा seq_file *, व्योम *),
		व्योम *data, माप_प्रकार size)
अणु
	अक्षर *buf = seq_buf_alloc(size);
	पूर्णांक ret;
	अगर (!buf)
		वापस -ENOMEM;
	ret = single_खोलो(file, show, data);
	अगर (ret) अणु
		kvमुक्त(buf);
		वापस ret;
	पूर्ण
	((काष्ठा seq_file *)file->निजी_data)->buf = buf;
	((काष्ठा seq_file *)file->निजी_data)->size = size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(single_खोलो_size);

पूर्णांक single_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा seq_operations *op = ((काष्ठा seq_file *)file->निजी_data)->op;
	पूर्णांक res = seq_release(inode, file);
	kमुक्त(op);
	वापस res;
पूर्ण
EXPORT_SYMBOL(single_release);

पूर्णांक seq_release_निजी(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;

	kमुक्त(seq->निजी);
	seq->निजी = शून्य;
	वापस seq_release(inode, file);
पूर्ण
EXPORT_SYMBOL(seq_release_निजी);

व्योम *__seq_खोलो_निजी(काष्ठा file *f, स्थिर काष्ठा seq_operations *ops,
		पूर्णांक psize)
अणु
	पूर्णांक rc;
	व्योम *निजी;
	काष्ठा seq_file *seq;

	निजी = kzalloc(psize, GFP_KERNEL_ACCOUNT);
	अगर (निजी == शून्य)
		जाओ out;

	rc = seq_खोलो(f, ops);
	अगर (rc < 0)
		जाओ out_मुक्त;

	seq = f->निजी_data;
	seq->निजी = निजी;
	वापस निजी;

out_मुक्त:
	kमुक्त(निजी);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__seq_खोलो_निजी);

पूर्णांक seq_खोलो_निजी(काष्ठा file *filp, स्थिर काष्ठा seq_operations *ops,
		पूर्णांक psize)
अणु
	वापस __seq_खोलो_निजी(filp, ops, psize) ? 0 : -ENOMEM;
पूर्ण
EXPORT_SYMBOL(seq_खोलो_निजी);

व्योम seq_अ_दो(काष्ठा seq_file *m, अक्षर c)
अणु
	अगर (m->count >= m->size)
		वापस;

	m->buf[m->count++] = c;
पूर्ण
EXPORT_SYMBOL(seq_अ_दो);

व्योम seq_माला_दो(काष्ठा seq_file *m, स्थिर अक्षर *s)
अणु
	पूर्णांक len = म_माप(s);

	अगर (m->count + len >= m->size) अणु
		seq_set_overflow(m);
		वापस;
	पूर्ण
	स_नकल(m->buf + m->count, s, len);
	m->count += len;
पूर्ण
EXPORT_SYMBOL(seq_माला_दो);

/**
 * seq_put_decimal_ull_width - A helper routine क्रम putting decimal numbers
 * 			       without rich क्रमmat of म_लिखो().
 * only 'unsigned long long' is supported.
 * @m: seq_file identअगरying the buffer to which data should be written
 * @delimiter: a string which is prपूर्णांकed beक्रमe the number
 * @num: the number
 * @width: a minimum field width
 *
 * This routine will put म_माप(delimiter) + number पूर्णांकo seq_filed.
 * This routine is very quick when you show lots of numbers.
 * In usual हालs, it will be better to use seq_म_लिखो(). It's easier to पढ़ो.
 */
व्योम seq_put_decimal_ull_width(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
			 अचिन्हित दीर्घ दीर्घ num, अचिन्हित पूर्णांक width)
अणु
	पूर्णांक len;

	अगर (m->count + 2 >= m->size) /* we'll ग_लिखो 2 bytes at least */
		जाओ overflow;

	अगर (delimiter && delimiter[0]) अणु
		अगर (delimiter[1] == 0)
			seq_अ_दो(m, delimiter[0]);
		अन्यथा
			seq_माला_दो(m, delimiter);
	पूर्ण

	अगर (!width)
		width = 1;

	अगर (m->count + width >= m->size)
		जाओ overflow;

	len = num_to_str(m->buf + m->count, m->size - m->count, num, width);
	अगर (!len)
		जाओ overflow;

	m->count += len;
	वापस;

overflow:
	seq_set_overflow(m);
पूर्ण

व्योम seq_put_decimal_ull(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
			 अचिन्हित दीर्घ दीर्घ num)
अणु
	वापस seq_put_decimal_ull_width(m, delimiter, num, 0);
पूर्ण
EXPORT_SYMBOL(seq_put_decimal_ull);

/**
 * seq_put_hex_ll - put a number in hexadecimal notation
 * @m: seq_file identअगरying the buffer to which data should be written
 * @delimiter: a string which is prपूर्णांकed beक्रमe the number
 * @v: the number
 * @width: a minimum field width
 *
 * seq_put_hex_ll(m, "", v, 8) is equal to seq_म_लिखो(m, "%08llx", v)
 *
 * This routine is very quick when you show lots of numbers.
 * In usual हालs, it will be better to use seq_म_लिखो(). It's easier to पढ़ो.
 */
व्योम seq_put_hex_ll(काष्ठा seq_file *m, स्थिर अक्षर *delimiter,
				अचिन्हित दीर्घ दीर्घ v, अचिन्हित पूर्णांक width)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक i;

	अगर (delimiter && delimiter[0]) अणु
		अगर (delimiter[1] == 0)
			seq_अ_दो(m, delimiter[0]);
		अन्यथा
			seq_माला_दो(m, delimiter);
	पूर्ण

	/* If x is 0, the result of __builtin_clzll is undefined */
	अगर (v == 0)
		len = 1;
	अन्यथा
		len = (माप(v) * 8 - __builtin_clzll(v) + 3) / 4;

	अगर (len < width)
		len = width;

	अगर (m->count + len > m->size) अणु
		seq_set_overflow(m);
		वापस;
	पूर्ण

	क्रम (i = len - 1; i >= 0; i--) अणु
		m->buf[m->count + i] = hex_asc[0xf & v];
		v = v >> 4;
	पूर्ण
	m->count += len;
पूर्ण

व्योम seq_put_decimal_ll(काष्ठा seq_file *m, स्थिर अक्षर *delimiter, दीर्घ दीर्घ num)
अणु
	पूर्णांक len;

	अगर (m->count + 3 >= m->size) /* we'll ग_लिखो 2 bytes at least */
		जाओ overflow;

	अगर (delimiter && delimiter[0]) अणु
		अगर (delimiter[1] == 0)
			seq_अ_दो(m, delimiter[0]);
		अन्यथा
			seq_माला_दो(m, delimiter);
	पूर्ण

	अगर (m->count + 2 >= m->size)
		जाओ overflow;

	अगर (num < 0) अणु
		m->buf[m->count++] = '-';
		num = -num;
	पूर्ण

	अगर (num < 10) अणु
		m->buf[m->count++] = num + '0';
		वापस;
	पूर्ण

	len = num_to_str(m->buf + m->count, m->size - m->count, num, 0);
	अगर (!len)
		जाओ overflow;

	m->count += len;
	वापस;

overflow:
	seq_set_overflow(m);
पूर्ण
EXPORT_SYMBOL(seq_put_decimal_ll);

/**
 * seq_ग_लिखो - ग_लिखो arbitrary data to buffer
 * @seq: seq_file identअगरying the buffer to which data should be written
 * @data: data address
 * @len: number of bytes
 *
 * Return 0 on success, non-zero otherwise.
 */
पूर्णांक seq_ग_लिखो(काष्ठा seq_file *seq, स्थिर व्योम *data, माप_प्रकार len)
अणु
	अगर (seq->count + len < seq->size) अणु
		स_नकल(seq->buf + seq->count, data, len);
		seq->count += len;
		वापस 0;
	पूर्ण
	seq_set_overflow(seq);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(seq_ग_लिखो);

/**
 * seq_pad - ग_लिखो padding spaces to buffer
 * @m: seq_file identअगरying the buffer to which data should be written
 * @c: the byte to append after padding अगर non-zero
 */
व्योम seq_pad(काष्ठा seq_file *m, अक्षर c)
अणु
	पूर्णांक size = m->pad_until - m->count;
	अगर (size > 0) अणु
		अगर (size + m->count > m->size) अणु
			seq_set_overflow(m);
			वापस;
		पूर्ण
		स_रखो(m->buf + m->count, ' ', size);
		m->count += size;
	पूर्ण
	अगर (c)
		seq_अ_दो(m, c);
पूर्ण
EXPORT_SYMBOL(seq_pad);

/* A complete analogue of prपूर्णांक_hex_dump() */
व्योम seq_hex_dump(काष्ठा seq_file *m, स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		  पूर्णांक rowsize, पूर्णांक groupsize, स्थिर व्योम *buf, माप_प्रकार len,
		  bool ascii)
अणु
	स्थिर u8 *ptr = buf;
	पूर्णांक i, linelen, reमुख्यing = len;
	अक्षर *buffer;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	क्रम (i = 0; i < len && !seq_has_overflowed(m); i += rowsize) अणु
		linelen = min(reमुख्यing, rowsize);
		reमुख्यing -= rowsize;

		चयन (prefix_type) अणु
		हाल DUMP_PREFIX_ADDRESS:
			seq_म_लिखो(m, "%s%p: ", prefix_str, ptr + i);
			अवरोध;
		हाल DUMP_PREFIX_OFFSET:
			seq_म_लिखो(m, "%s%.8x: ", prefix_str, i);
			अवरोध;
		शेष:
			seq_म_लिखो(m, "%s", prefix_str);
			अवरोध;
		पूर्ण

		size = seq_get_buf(m, &buffer);
		ret = hex_dump_to_buffer(ptr + i, linelen, rowsize, groupsize,
					 buffer, size, ascii);
		seq_commit(m, ret < size ? ret : -1);

		seq_अ_दो(m, '\n');
	पूर्ण
पूर्ण
EXPORT_SYMBOL(seq_hex_dump);

काष्ठा list_head *seq_list_start(काष्ठा list_head *head, loff_t pos)
अणु
	काष्ठा list_head *lh;

	list_क्रम_each(lh, head)
		अगर (pos-- == 0)
			वापस lh;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(seq_list_start);

काष्ठा list_head *seq_list_start_head(काष्ठा list_head *head, loff_t pos)
अणु
	अगर (!pos)
		वापस head;

	वापस seq_list_start(head, pos - 1);
पूर्ण
EXPORT_SYMBOL(seq_list_start_head);

काष्ठा list_head *seq_list_next(व्योम *v, काष्ठा list_head *head, loff_t *ppos)
अणु
	काष्ठा list_head *lh;

	lh = ((काष्ठा list_head *)v)->next;
	++*ppos;
	वापस lh == head ? शून्य : lh;
पूर्ण
EXPORT_SYMBOL(seq_list_next);

/**
 * seq_hlist_start - start an iteration of a hlist
 * @head: the head of the hlist
 * @pos:  the start position of the sequence
 *
 * Called at seq_file->op->start().
 */
काष्ठा hlist_node *seq_hlist_start(काष्ठा hlist_head *head, loff_t pos)
अणु
	काष्ठा hlist_node *node;

	hlist_क्रम_each(node, head)
		अगर (pos-- == 0)
			वापस node;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(seq_hlist_start);

/**
 * seq_hlist_start_head - start an iteration of a hlist
 * @head: the head of the hlist
 * @pos:  the start position of the sequence
 *
 * Called at seq_file->op->start(). Call this function अगर you want to
 * prपूर्णांक a header at the top of the output.
 */
काष्ठा hlist_node *seq_hlist_start_head(काष्ठा hlist_head *head, loff_t pos)
अणु
	अगर (!pos)
		वापस SEQ_START_TOKEN;

	वापस seq_hlist_start(head, pos - 1);
पूर्ण
EXPORT_SYMBOL(seq_hlist_start_head);

/**
 * seq_hlist_next - move to the next position of the hlist
 * @v:    the current iterator
 * @head: the head of the hlist
 * @ppos: the current position
 *
 * Called at seq_file->op->next().
 */
काष्ठा hlist_node *seq_hlist_next(व्योम *v, काष्ठा hlist_head *head,
				  loff_t *ppos)
अणु
	काष्ठा hlist_node *node = v;

	++*ppos;
	अगर (v == SEQ_START_TOKEN)
		वापस head->first;
	अन्यथा
		वापस node->next;
पूर्ण
EXPORT_SYMBOL(seq_hlist_next);

/**
 * seq_hlist_start_rcu - start an iteration of a hlist रक्षित by RCU
 * @head: the head of the hlist
 * @pos:  the start position of the sequence
 *
 * Called at seq_file->op->start().
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
काष्ठा hlist_node *seq_hlist_start_rcu(काष्ठा hlist_head *head,
				       loff_t pos)
अणु
	काष्ठा hlist_node *node;

	__hlist_क्रम_each_rcu(node, head)
		अगर (pos-- == 0)
			वापस node;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(seq_hlist_start_rcu);

/**
 * seq_hlist_start_head_rcu - start an iteration of a hlist रक्षित by RCU
 * @head: the head of the hlist
 * @pos:  the start position of the sequence
 *
 * Called at seq_file->op->start(). Call this function अगर you want to
 * prपूर्णांक a header at the top of the output.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
काष्ठा hlist_node *seq_hlist_start_head_rcu(काष्ठा hlist_head *head,
					    loff_t pos)
अणु
	अगर (!pos)
		वापस SEQ_START_TOKEN;

	वापस seq_hlist_start_rcu(head, pos - 1);
पूर्ण
EXPORT_SYMBOL(seq_hlist_start_head_rcu);

/**
 * seq_hlist_next_rcu - move to the next position of the hlist रक्षित by RCU
 * @v:    the current iterator
 * @head: the head of the hlist
 * @ppos: the current position
 *
 * Called at seq_file->op->next().
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
काष्ठा hlist_node *seq_hlist_next_rcu(व्योम *v,
				      काष्ठा hlist_head *head,
				      loff_t *ppos)
अणु
	काष्ठा hlist_node *node = v;

	++*ppos;
	अगर (v == SEQ_START_TOKEN)
		वापस rcu_dereference(head->first);
	अन्यथा
		वापस rcu_dereference(node->next);
पूर्ण
EXPORT_SYMBOL(seq_hlist_next_rcu);

/**
 * seq_hlist_start_percpu - start an iteration of a percpu hlist array
 * @head: poपूर्णांकer to percpu array of काष्ठा hlist_heads
 * @cpu:  poपूर्णांकer to cpu "cursor"
 * @pos:  start position of sequence
 *
 * Called at seq_file->op->start().
 */
काष्ठा hlist_node *
seq_hlist_start_percpu(काष्ठा hlist_head __percpu *head, पूर्णांक *cpu, loff_t pos)
अणु
	काष्ठा hlist_node *node;

	क्रम_each_possible_cpu(*cpu) अणु
		hlist_क्रम_each(node, per_cpu_ptr(head, *cpu)) अणु
			अगर (pos-- == 0)
				वापस node;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(seq_hlist_start_percpu);

/**
 * seq_hlist_next_percpu - move to the next position of the percpu hlist array
 * @v:    poपूर्णांकer to current hlist_node
 * @head: poपूर्णांकer to percpu array of काष्ठा hlist_heads
 * @cpu:  poपूर्णांकer to cpu "cursor"
 * @pos:  start position of sequence
 *
 * Called at seq_file->op->next().
 */
काष्ठा hlist_node *
seq_hlist_next_percpu(व्योम *v, काष्ठा hlist_head __percpu *head,
			पूर्णांक *cpu, loff_t *pos)
अणु
	काष्ठा hlist_node *node = v;

	++*pos;

	अगर (node->next)
		वापस node->next;

	क्रम (*cpu = cpumask_next(*cpu, cpu_possible_mask); *cpu < nr_cpu_ids;
	     *cpu = cpumask_next(*cpu, cpu_possible_mask)) अणु
		काष्ठा hlist_head *bucket = per_cpu_ptr(head, *cpu);

		अगर (!hlist_empty(bucket))
			वापस bucket->first;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(seq_hlist_next_percpu);

व्योम __init seq_file_init(व्योम)
अणु
	seq_file_cache = KMEM_CACHE(seq_file, SLAB_ACCOUNT|SLAB_PANIC);
पूर्ण
