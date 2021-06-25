<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide access to भव console memory.
 * /dev/vcs: the screen as it is being viewed right now (possibly scrolled)
 * /dev/vcsN: the screen of /dev/ttyN (1 <= N <= 63)
 *            [minor: N]
 *
 * /dev/vcsaN: idem, but including attributes, and prefixed with
 *	the 4 bytes lines,columns,x,y (as screendump used to give).
 *	Attribute/अक्षरacter pair is in native endianity.
 *            [minor: N+128]
 *
 * /dev/vcsuN: similar to /dev/vcsaN but using 4-byte unicode values
 *	instead of 1-byte screen glyph values.
 *            [minor: N+64]
 *
 * /dev/vcsuaN: same idea as /dev/vcsaN क्रम unicode (not yet implemented).
 *
 * This replaces screendump and part of selection, so that the प्रणाली
 * administrator can control access using file प्रणाली permissions.
 *
 * aeb@cwi.nl - efter Friedas begravअन्यथा - 950211
 *
 * machek@k332.feld.cvut.cz - modअगरied not to send अक्षरacters to wrong console
 *	 - fixed some fatal off-by-one bugs (0-- no दीर्घer == -1 -> looping and looping and looping...)
 *	 - making it लघुer - scr_पढ़ोw are macros which expand in PRETTY दीर्घ code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/tty.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/selection.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/console.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा HEADER_SIZE	4u
#घोषणा CON_BUF_SIZE (CONFIG_BASE_SMALL ? 256 : PAGE_SIZE)

/*
 * Our minor space:
 *
 *   0 ... 63	glyph mode without attributes
 *  64 ... 127	unicode mode without attributes
 * 128 ... 191	glyph mode with attributes
 * 192 ... 255	unused (reserved क्रम unicode with attributes)
 *
 * This relies on MAX_NR_CONSOLES being  <= 63, meaning 63 actual consoles
 * with minors 0, 64, 128 and 192 being proxies क्रम the क्रमeground console.
 */
#अगर MAX_NR_CONSOLES > 63
#warning "/dev/vcs* devices may not accommodate more than 63 consoles"
#पूर्ण_अगर

#घोषणा console(inode)		(iminor(inode) & 63)
#घोषणा use_unicode(inode)	(iminor(inode) & 64)
#घोषणा use_attributes(inode)	(iminor(inode) & 128)


काष्ठा vcs_poll_data अणु
	काष्ठा notअगरier_block notअगरier;
	अचिन्हित पूर्णांक cons_num;
	पूर्णांक event;
	रुको_queue_head_t रुकोq;
	काष्ठा fasync_काष्ठा *fasync;
पूर्ण;

अटल पूर्णांक
vcs_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code, व्योम *_param)
अणु
	काष्ठा vt_notअगरier_param *param = _param;
	काष्ठा vc_data *vc = param->vc;
	काष्ठा vcs_poll_data *poll =
		container_of(nb, काष्ठा vcs_poll_data, notअगरier);
	पूर्णांक currcons = poll->cons_num;
	पूर्णांक fa_band;

	चयन (code) अणु
	हाल VT_UPDATE:
		fa_band = POLL_PRI;
		अवरोध;
	हाल VT_DEALLOCATE:
		fa_band = POLL_HUP;
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (currcons == 0)
		currcons = fg_console;
	अन्यथा
		currcons--;
	अगर (currcons != vc->vc_num)
		वापस NOTIFY_DONE;

	poll->event = code;
	wake_up_पूर्णांकerruptible(&poll->रुकोq);
	समाप्त_fasync(&poll->fasync, SIGIO, fa_band);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम
vcs_poll_data_मुक्त(काष्ठा vcs_poll_data *poll)
अणु
	unरेजिस्टर_vt_notअगरier(&poll->notअगरier);
	kमुक्त(poll);
पूर्ण

अटल काष्ठा vcs_poll_data *
vcs_poll_data_get(काष्ठा file *file)
अणु
	काष्ठा vcs_poll_data *poll = file->निजी_data, *समाप्त = शून्य;

	अगर (poll)
		वापस poll;

	poll = kzalloc(माप(*poll), GFP_KERNEL);
	अगर (!poll)
		वापस शून्य;
	poll->cons_num = console(file_inode(file));
	init_रुकोqueue_head(&poll->रुकोq);
	poll->notअगरier.notअगरier_call = vcs_notअगरier;
	/*
	 * In order not to lose any update event, we must pretend one might
	 * have occurred beक्रमe we have a chance to रेजिस्टर our notअगरier.
	 * This is also how user space has come to detect which kernels
	 * support POLLPRI on /dev/vcs* devices i.e. using poll() with
	 * POLLPRI and a zero समयout.
	 */
	poll->event = VT_UPDATE;

	अगर (रेजिस्टर_vt_notअगरier(&poll->notअगरier) != 0) अणु
		kमुक्त(poll);
		वापस शून्य;
	पूर्ण

	/*
	 * This code may be called either through ->poll() or ->fasync().
	 * If we have two thपढ़ोs using the same file descriptor, they could
	 * both enter this function, both notice that the काष्ठाure hasn't
	 * been allocated yet and go ahead allocating it in parallel, but
	 * only one of them must survive and be shared otherwise we'd leak
	 * memory with a dangling notअगरier callback.
	 */
	spin_lock(&file->f_lock);
	अगर (!file->निजी_data) अणु
		file->निजी_data = poll;
	पूर्ण अन्यथा अणु
		/* someone अन्यथा raced ahead of us */
		समाप्त = poll;
		poll = file->निजी_data;
	पूर्ण
	spin_unlock(&file->f_lock);
	अगर (समाप्त)
		vcs_poll_data_मुक्त(समाप्त);

	वापस poll;
पूर्ण

/**
 * vcs_vc -- वापस VC क्रम @inode
 * @inode: inode क्रम which to वापस a VC
 * @viewed: वापसs whether this console is currently क्रमeground (viewed)
 *
 * Must be called with console_lock.
 */
अटल काष्ठा vc_data *vcs_vc(काष्ठा inode *inode, bool *viewed)
अणु
	अचिन्हित पूर्णांक currcons = console(inode);

	WARN_CONSOLE_UNLOCKED();

	अगर (currcons == 0) अणु
		currcons = fg_console;
		अगर (viewed)
			*viewed = true;
	पूर्ण अन्यथा अणु
		currcons--;
		अगर (viewed)
			*viewed = false;
	पूर्ण
	वापस vc_cons[currcons].d;
पूर्ण

/**
 * vcs_size -- वापस size क्रम a VC in @vc
 * @vc: which VC
 * @attr: करोes it use attributes?
 * @unicode: is it unicode?
 *
 * Must be called with console_lock.
 */
अटल पूर्णांक vcs_size(स्थिर काष्ठा vc_data *vc, bool attr, bool unicode)
अणु
	पूर्णांक size;

	WARN_CONSOLE_UNLOCKED();

	size = vc->vc_rows * vc->vc_cols;

	अगर (attr) अणु
		अगर (unicode)
			वापस -EOPNOTSUPP;

		size = 2 * size + HEADER_SIZE;
	पूर्ण अन्यथा अगर (unicode)
		size *= 4;

	वापस size;
पूर्ण

अटल loff_t vcs_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा vc_data *vc;
	पूर्णांक size;

	console_lock();
	vc = vcs_vc(inode, शून्य);
	अगर (!vc) अणु
		console_unlock();
		वापस -ENXIO;
	पूर्ण

	size = vcs_size(vc, use_attributes(inode), use_unicode(inode));
	console_unlock();
	अगर (size < 0)
		वापस size;
	वापस fixed_size_llseek(file, offset, orig, size);
पूर्ण

अटल पूर्णांक vcs_पढ़ो_buf_uni(काष्ठा vc_data *vc, अक्षर *con_buf,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, bool viewed)
अणु
	अचिन्हित पूर्णांक nr, row, col, maxcol = vc->vc_cols;
	पूर्णांक ret;

	ret = vc_uniscr_check(vc);
	अगर (ret)
		वापस ret;

	pos /= 4;
	row = pos / maxcol;
	col = pos % maxcol;
	nr = maxcol - col;
	करो अणु
		अगर (nr > count / 4)
			nr = count / 4;
		vc_uniscr_copy_line(vc, con_buf, viewed, row, col, nr);
		con_buf += nr * 4;
		count -= nr * 4;
		row++;
		col = 0;
		nr = maxcol;
	पूर्ण जबतक (count);

	वापस 0;
पूर्ण

अटल व्योम vcs_पढ़ो_buf_noattr(स्थिर काष्ठा vc_data *vc, अक्षर *con_buf,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, bool viewed)
अणु
	u16 *org;
	अचिन्हित पूर्णांक col, maxcol = vc->vc_cols;

	org = screen_pos(vc, pos, viewed);
	col = pos % maxcol;
	pos += maxcol - col;

	जबतक (count-- > 0) अणु
		*con_buf++ = (vcs_scr_पढ़ोw(vc, org++) & 0xff);
		अगर (++col == maxcol) अणु
			org = screen_pos(vc, pos, viewed);
			col = 0;
			pos += maxcol;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक vcs_पढ़ो_buf(स्थिर काष्ठा vc_data *vc, अक्षर *con_buf,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, bool viewed,
		अचिन्हित पूर्णांक *skip)
अणु
	u16 *org, *con_buf16;
	अचिन्हित पूर्णांक col, maxcol = vc->vc_cols;
	अचिन्हित पूर्णांक filled = count;

	अगर (pos < HEADER_SIZE) अणु
		/* clamp header values अगर they करोn't fit */
		con_buf[0] = min(vc->vc_rows, 0xFFu);
		con_buf[1] = min(vc->vc_cols, 0xFFu);
		अ_लोonsxy(vc, con_buf + 2);

		*skip += pos;
		count += pos;
		अगर (count > CON_BUF_SIZE) अणु
			count = CON_BUF_SIZE;
			filled = count - pos;
		पूर्ण

		/* Advance state poपूर्णांकers and move on. */
		count -= min(HEADER_SIZE, count);
		pos = HEADER_SIZE;
		con_buf += HEADER_SIZE;
		/* If count >= 0, then pos is even... */
	पूर्ण अन्यथा अगर (pos & 1) अणु
		/*
		 * Skip first byte क्रम output अगर start address is odd. Update
		 * region sizes up/करोwn depending on मुक्त space in buffer.
		 */
		(*skip)++;
		अगर (count < CON_BUF_SIZE)
			count++;
		अन्यथा
			filled--;
	पूर्ण

	अगर (!count)
		वापस filled;

	pos -= HEADER_SIZE;
	pos /= 2;
	col = pos % maxcol;

	org = screen_pos(vc, pos, viewed);
	pos += maxcol - col;

	/*
	 * Buffer has even length, so we can always copy अक्षरacter + attribute.
	 * We करो not copy last byte to userspace अगर count is odd.
	 */
	count = (count + 1) / 2;
	con_buf16 = (u16 *)con_buf;

	जबतक (count) अणु
		*con_buf16++ = vcs_scr_पढ़ोw(vc, org++);
		count--;
		अगर (++col == maxcol) अणु
			org = screen_pos(vc, pos, viewed);
			col = 0;
			pos += maxcol;
		पूर्ण
	पूर्ण

	वापस filled;
पूर्ण

अटल sमाप_प्रकार
vcs_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा vc_data *vc;
	काष्ठा vcs_poll_data *poll;
	अचिन्हित पूर्णांक पढ़ो;
	sमाप_प्रकार ret;
	अक्षर *con_buf;
	loff_t pos;
	bool viewed, attr, uni_mode;

	con_buf = (अक्षर *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!con_buf)
		वापस -ENOMEM;

	pos = *ppos;

	/* Select the proper current console and verअगरy
	 * sanity of the situation under the console lock.
	 */
	console_lock();

	uni_mode = use_unicode(inode);
	attr = use_attributes(inode);
	ret = -ENXIO;
	vc = vcs_vc(inode, &viewed);
	अगर (!vc)
		जाओ unlock_out;

	ret = -EINVAL;
	अगर (pos < 0)
		जाओ unlock_out;
	/* we enक्रमce 32-bit alignment क्रम pos and count in unicode mode */
	अगर (uni_mode && (pos | count) & 3)
		जाओ unlock_out;

	poll = file->निजी_data;
	अगर (count && poll)
		poll->event = 0;
	पढ़ो = 0;
	ret = 0;
	जबतक (count) अणु
		अचिन्हित पूर्णांक this_round, skip = 0;
		पूर्णांक size;

		/* Check whether we are above size each round,
		 * as copy_to_user at the end of this loop
		 * could sleep.
		 */
		size = vcs_size(vc, attr, uni_mode);
		अगर (size < 0) अणु
			अगर (पढ़ो)
				अवरोध;
			ret = size;
			जाओ unlock_out;
		पूर्ण
		अगर (pos >= size)
			अवरोध;
		अगर (count > size - pos)
			count = size - pos;

		this_round = count;
		अगर (this_round > CON_BUF_SIZE)
			this_round = CON_BUF_SIZE;

		/* Perक्रमm the whole पढ़ो पूर्णांकo the local con_buf.
		 * Then we can drop the console spinlock and safely
		 * attempt to move it to userspace.
		 */

		अगर (uni_mode) अणु
			ret = vcs_पढ़ो_buf_uni(vc, con_buf, pos, this_round,
					viewed);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अगर (!attr) अणु
			vcs_पढ़ो_buf_noattr(vc, con_buf, pos, this_round,
					viewed);
		पूर्ण अन्यथा अणु
			this_round = vcs_पढ़ो_buf(vc, con_buf, pos, this_round,
					viewed, &skip);
		पूर्ण

		/* Finally, release the console semaphore जबतक we push
		 * all the data to userspace from our temporary buffer.
		 *
		 * AKPM: Even though it's a semaphore, we should drop it because
		 * the pagefault handling code may want to call prपूर्णांकk().
		 */

		console_unlock();
		ret = copy_to_user(buf, con_buf + skip, this_round);
		console_lock();

		अगर (ret) अणु
			पढ़ो += this_round - ret;
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		buf += this_round;
		pos += this_round;
		पढ़ो += this_round;
		count -= this_round;
	पूर्ण
	*ppos += पढ़ो;
	अगर (पढ़ो)
		ret = पढ़ो;
unlock_out:
	console_unlock();
	मुक्त_page((अचिन्हित दीर्घ) con_buf);
	वापस ret;
पूर्ण

अटल u16 *vcs_ग_लिखो_buf_noattr(काष्ठा vc_data *vc, स्थिर अक्षर *con_buf,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, bool viewed, u16 **org0)
अणु
	u16 *org;
	अचिन्हित पूर्णांक col, maxcol = vc->vc_cols;

	*org0 = org = screen_pos(vc, pos, viewed);
	col = pos % maxcol;
	pos += maxcol - col;

	जबतक (count > 0) अणु
		अचिन्हित अक्षर c = *con_buf++;

		count--;
		vcs_scr_ग_लिखोw(vc,
			       (vcs_scr_पढ़ोw(vc, org) & 0xff00) | c, org);
		org++;
		अगर (++col == maxcol) अणु
			org = screen_pos(vc, pos, viewed);
			col = 0;
			pos += maxcol;
		पूर्ण
	पूर्ण

	वापस org;
पूर्ण

/*
 * Compilers (gcc 10) are unable to optimize the swap in cpu_to_le16. So करो it
 * the poor man way.
 */
अटल अंतरभूत u16 vc_compile_le16(u8 hi, u8 lo)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (lo << 8u) | hi;
#अन्यथा
	वापस (hi << 8u) | lo;
#पूर्ण_अगर
पूर्ण

अटल u16 *vcs_ग_लिखो_buf(काष्ठा vc_data *vc, स्थिर अक्षर *con_buf,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, bool viewed, u16 **org0)
अणु
	u16 *org;
	अचिन्हित पूर्णांक col, maxcol = vc->vc_cols;
	अचिन्हित अक्षर c;

	/* header */
	अगर (pos < HEADER_SIZE) अणु
		अक्षर header[HEADER_SIZE];

		अ_लोonsxy(vc, header + 2);
		जबतक (pos < HEADER_SIZE && count > 0) अणु
			count--;
			header[pos++] = *con_buf++;
		पूर्ण
		अगर (!viewed)
			अ_दोonsxy(vc, header + 2);
	पूर्ण

	अगर (!count)
		वापस शून्य;

	pos -= HEADER_SIZE;
	col = (pos/2) % maxcol;

	*org0 = org = screen_pos(vc, pos/2, viewed);

	/* odd pos -- the first single अक्षरacter */
	अगर (pos & 1) अणु
		count--;
		c = *con_buf++;
		vcs_scr_ग_लिखोw(vc, vc_compile_le16(c, vcs_scr_पढ़ोw(vc, org)),
				org);
		org++;
		pos++;
		अगर (++col == maxcol) अणु
			org = screen_pos(vc, pos/2, viewed);
			col = 0;
		पूर्ण
	पूर्ण

	pos /= 2;
	pos += maxcol - col;

	/* even pos -- handle attr+अक्षरacter pairs */
	जबतक (count > 1) अणु
		अचिन्हित लघु w;

		w = get_unaligned(((अचिन्हित लघु *)con_buf));
		vcs_scr_ग_लिखोw(vc, w, org++);
		con_buf += 2;
		count -= 2;
		अगर (++col == maxcol) अणु
			org = screen_pos(vc, pos, viewed);
			col = 0;
			pos += maxcol;
		पूर्ण
	पूर्ण

	अगर (!count)
		वापस org;

	/* odd pos -- the reमुख्यing अक्षरacter */
	c = *con_buf++;
	vcs_scr_ग_लिखोw(vc, vc_compile_le16(vcs_scr_पढ़ोw(vc, org) >> 8, c),
				org);

	वापस org;
पूर्ण

अटल sमाप_प्रकार
vcs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा vc_data *vc;
	अक्षर *con_buf;
	u16 *org0, *org;
	अचिन्हित पूर्णांक written;
	पूर्णांक size;
	sमाप_प्रकार ret;
	loff_t pos;
	bool viewed, attr;

	अगर (use_unicode(inode))
		वापस -EOPNOTSUPP;

	con_buf = (अक्षर *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!con_buf)
		वापस -ENOMEM;

	pos = *ppos;

	/* Select the proper current console and verअगरy
	 * sanity of the situation under the console lock.
	 */
	console_lock();

	attr = use_attributes(inode);
	ret = -ENXIO;
	vc = vcs_vc(inode, &viewed);
	अगर (!vc)
		जाओ unlock_out;

	size = vcs_size(vc, attr, false);
	अगर (size < 0) अणु
		ret = size;
		जाओ unlock_out;
	पूर्ण
	ret = -EINVAL;
	अगर (pos < 0 || pos > size)
		जाओ unlock_out;
	अगर (count > size - pos)
		count = size - pos;
	written = 0;
	जबतक (count) अणु
		अचिन्हित पूर्णांक this_round = count;

		अगर (this_round > CON_BUF_SIZE)
			this_round = CON_BUF_SIZE;

		/* Temporarily drop the console lock so that we can पढ़ो
		 * in the ग_लिखो data from userspace safely.
		 */
		console_unlock();
		ret = copy_from_user(con_buf, buf, this_round);
		console_lock();

		अगर (ret) अणु
			this_round -= ret;
			अगर (!this_round) अणु
				/* Abort loop अगर no data were copied. Otherwise
				 * fail with -EFAULT.
				 */
				अगर (written)
					अवरोध;
				ret = -EFAULT;
				जाओ unlock_out;
			पूर्ण
		पूर्ण

		/* The vcs_size might have changed जबतक we slept to grab
		 * the user buffer, so recheck.
		 * Return data written up to now on failure.
		 */
		size = vcs_size(vc, attr, false);
		अगर (size < 0) अणु
			अगर (written)
				अवरोध;
			ret = size;
			जाओ unlock_out;
		पूर्ण
		अगर (pos >= size)
			अवरोध;
		अगर (this_round > size - pos)
			this_round = size - pos;

		/* OK, now actually push the ग_लिखो to the console
		 * under the lock using the local kernel buffer.
		 */

		अगर (attr)
			org = vcs_ग_लिखो_buf(vc, con_buf, pos, this_round,
					viewed, &org0);
		अन्यथा
			org = vcs_ग_लिखो_buf_noattr(vc, con_buf, pos, this_round,
					viewed, &org0);

		count -= this_round;
		written += this_round;
		buf += this_round;
		pos += this_round;
		अगर (org)
			update_region(vc, (अचिन्हित दीर्घ)(org0), org - org0);
	पूर्ण
	*ppos += written;
	ret = written;
	अगर (written)
		vcs_scr_updated(vc);

unlock_out:
	console_unlock();
	मुक्त_page((अचिन्हित दीर्घ) con_buf);
	वापस ret;
पूर्ण

अटल __poll_t
vcs_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा vcs_poll_data *poll = vcs_poll_data_get(file);
	__poll_t ret = DEFAULT_POLLMASK|EPOLLERR;

	अगर (poll) अणु
		poll_रुको(file, &poll->रुकोq, रुको);
		चयन (poll->event) अणु
		हाल VT_UPDATE:
			ret = DEFAULT_POLLMASK|EPOLLPRI;
			अवरोध;
		हाल VT_DEALLOCATE:
			ret = DEFAULT_POLLMASK|EPOLLHUP|EPOLLERR;
			अवरोध;
		हाल 0:
			ret = DEFAULT_POLLMASK;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
vcs_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा vcs_poll_data *poll = file->निजी_data;

	अगर (!poll) अणु
		/* करोn't allocate anything अगर all we want is disable fasync */
		अगर (!on)
			वापस 0;
		poll = vcs_poll_data_get(file);
		अगर (!poll)
			वापस -ENOMEM;
	पूर्ण

	वापस fasync_helper(fd, file, on, &poll->fasync);
पूर्ण

अटल पूर्णांक
vcs_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अचिन्हित पूर्णांक currcons = console(inode);
	bool attr = use_attributes(inode);
	bool uni_mode = use_unicode(inode);
	पूर्णांक ret = 0;

	/* we currently करोn't support attributes in unicode mode */
	अगर (attr && uni_mode)
		वापस -EOPNOTSUPP;

	console_lock();
	अगर(currcons && !vc_cons_allocated(currcons-1))
		ret = -ENXIO;
	console_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक vcs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vcs_poll_data *poll = file->निजी_data;

	अगर (poll)
		vcs_poll_data_मुक्त(poll);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vcs_fops = अणु
	.llseek		= vcs_lseek,
	.पढ़ो		= vcs_पढ़ो,
	.ग_लिखो		= vcs_ग_लिखो,
	.poll		= vcs_poll,
	.fasync		= vcs_fasync,
	.खोलो		= vcs_खोलो,
	.release	= vcs_release,
पूर्ण;

अटल काष्ठा class *vc_class;

व्योम vcs_make_sysfs(पूर्णांक index)
अणु
	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, index + 1), शून्य,
		      "vcs%u", index + 1);
	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, index + 65), शून्य,
		      "vcsu%u", index + 1);
	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, index + 129), शून्य,
		      "vcsa%u", index + 1);
पूर्ण

व्योम vcs_हटाओ_sysfs(पूर्णांक index)
अणु
	device_destroy(vc_class, MKDEV(VCS_MAJOR, index + 1));
	device_destroy(vc_class, MKDEV(VCS_MAJOR, index + 65));
	device_destroy(vc_class, MKDEV(VCS_MAJOR, index + 129));
पूर्ण

पूर्णांक __init vcs_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (रेजिस्टर_chrdev(VCS_MAJOR, "vcs", &vcs_fops))
		panic("unable to get major %d for vcs device", VCS_MAJOR);
	vc_class = class_create(THIS_MODULE, "vc");

	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, 0), शून्य, "vcs");
	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, 64), शून्य, "vcsu");
	device_create(vc_class, शून्य, MKDEV(VCS_MAJOR, 128), शून्य, "vcsa");
	क्रम (i = 0; i < MIN_NR_CONSOLES; i++)
		vcs_make_sysfs(i);
	वापस 0;
पूर्ण
