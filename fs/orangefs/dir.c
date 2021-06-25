<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 Omnibond Systems, L.L.C.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"

काष्ठा orangefs_dir_part अणु
	काष्ठा orangefs_dir_part *next;
	माप_प्रकार len;
पूर्ण;

काष्ठा orangefs_dir अणु
	__u64 token;
	काष्ठा orangefs_dir_part *part;
	loff_t end;
	पूर्णांक error;
पूर्ण;

#घोषणा PART_SHIFT (24)
#घोषणा PART_SIZE (1<<24)
#घोषणा PART_MASK (~(PART_SIZE - 1))

/*
 * There can be up to 512 directory entries.  Each entry is encoded as
 * follows:
 * 4 bytes: string size (n)
 * n bytes: string
 * 1 byte: trailing zero
 * padding to 8 bytes
 * 16 bytes: khandle
 * padding to 8 bytes
 *
 * The trailer_buf starts with a काष्ठा orangefs_सूची_पढ़ो_response_s
 * which must be skipped to get to the directory data.
 *
 * The data which is received from the userspace daemon is termed a
 * part and is stored in a linked list in हाल more than one part is
 * needed क्रम a large directory.
 *
 * The position poपूर्णांकer (ctx->pos) encodes the part and offset on which
 * to begin पढ़ोing at.  Bits above PART_SHIFT encode the part and bits
 * below PART_SHIFT encode the offset.  Parts are stored in a linked
 * list which grows as data is received from the server.  The overhead
 * associated with managing the list is presumed to be small compared to
 * the overhead of communicating with the server.
 *
 * As data is received from the server, it is placed at the end of the
 * part list.  Data is parsed from the current position as it is needed.
 * When data is determined to be corrupt, it is either because the
 * userspace component has sent back corrupt data or because the file
 * poपूर्णांकer has been moved to an invalid location.  Since the two cannot
 * be dअगरferentiated, वापस EIO.
 *
 * Part zero is synthesized to contains `.' and `..'.  Part one is the
 * first part of the part list.
 */

अटल पूर्णांक करो_सूची_पढ़ो(काष्ठा orangefs_inode_s *oi,
    काष्ठा orangefs_dir *od, काष्ठा dentry *dentry,
    काष्ठा orangefs_kernel_op_s *op)
अणु
	काष्ठा orangefs_सूची_पढ़ो_response_s *resp;
	पूर्णांक bufi, r;

	/*
	 * Despite the badly named field, सूची_पढ़ो करोes not use shared
	 * memory.  However, there are a limited number of सूची_पढ़ो
	 * slots, which must be allocated here.  This flag simply tells
	 * the op scheduler to वापस the op here क्रम retry.
	 */
	op->uses_shared_memory = 1;
	op->upcall.req.सूची_पढ़ो.refn = oi->refn;
	op->upcall.req.सूची_पढ़ो.token = od->token;
	op->upcall.req.सूची_पढ़ो.max_dirent_count =
	    ORANGEFS_MAX_सूचीENT_COUNT_READसूची;

again:
	bufi = orangefs_सूची_पढ़ो_index_get();
	अगर (bufi < 0) अणु
		od->error = bufi;
		वापस bufi;
	पूर्ण

	op->upcall.req.सूची_पढ़ो.buf_index = bufi;

	r = service_operation(op, "orangefs_readdir",
	    get_पूर्णांकerruptible_flag(dentry->d_inode));

	orangefs_सूची_पढ़ो_index_put(bufi);

	अगर (op_state_purged(op)) अणु
		अगर (r == -EAGAIN) अणु
			vमुक्त(op->करोwncall.trailer_buf);
			जाओ again;
		पूर्ण अन्यथा अगर (r == -EIO) अणु
			vमुक्त(op->करोwncall.trailer_buf);
			od->error = r;
			वापस r;
		पूर्ण
	पूर्ण

	अगर (r < 0) अणु
		vमुक्त(op->करोwncall.trailer_buf);
		od->error = r;
		वापस r;
	पूर्ण अन्यथा अगर (op->करोwncall.status) अणु
		vमुक्त(op->करोwncall.trailer_buf);
		od->error = op->करोwncall.status;
		वापस op->करोwncall.status;
	पूर्ण

	/*
	 * The maximum size is size per entry बार the 512 entries plus
	 * the header.  This is well under the limit.
	 */
	अगर (op->करोwncall.trailer_size > PART_SIZE) अणु
		vमुक्त(op->करोwncall.trailer_buf);
		od->error = -EIO;
		वापस -EIO;
	पूर्ण

	resp = (काष्ठा orangefs_सूची_पढ़ो_response_s *)
	    op->करोwncall.trailer_buf;
	od->token = resp->token;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_सूची_पढ़ो(काष्ठा orangefs_dir *od,
    काष्ठा orangefs_kernel_op_s *op)
अणु
	काष्ठा orangefs_dir_part *part, *new;
	माप_प्रकार count;

	count = 1;
	part = od->part;
	जबतक (part) अणु
		count++;
		अगर (part->next)
			part = part->next;
		अन्यथा
			अवरोध;
	पूर्ण

	new = (व्योम *)op->करोwncall.trailer_buf;
	new->next = शून्य;
	new->len = op->करोwncall.trailer_size -
	    माप(काष्ठा orangefs_सूची_पढ़ो_response_s);
	अगर (!od->part)
		od->part = new;
	अन्यथा
		part->next = new;
	count++;
	od->end = count << PART_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक orangefs_dir_more(काष्ठा orangefs_inode_s *oi,
    काष्ठा orangefs_dir *od, काष्ठा dentry *dentry)
अणु
	काष्ठा orangefs_kernel_op_s *op;
	पूर्णांक r;

	op = op_alloc(ORANGEFS_VFS_OP_READसूची);
	अगर (!op) अणु
		od->error = -ENOMEM;
		वापस -ENOMEM;
	पूर्ण
	r = करो_सूची_पढ़ो(oi, od, dentry, op);
	अगर (r) अणु
		od->error = r;
		जाओ out;
	पूर्ण
	r = parse_सूची_पढ़ो(od, op);
	अगर (r) अणु
		od->error = r;
		जाओ out;
	पूर्ण

	od->error = 0;
out:
	op_release(op);
	वापस od->error;
पूर्ण

अटल पूर्णांक fill_from_part(काष्ठा orangefs_dir_part *part,
    काष्ठा dir_context *ctx)
अणु
	स्थिर पूर्णांक offset = माप(काष्ठा orangefs_सूची_पढ़ो_response_s);
	काष्ठा orangefs_khandle *khandle;
	__u32 *len, padlen;
	loff_t i;
	अक्षर *s;
	i = ctx->pos & ~PART_MASK;

	/* The file offset from userspace is too large. */
	अगर (i > part->len)
		वापस 1;

	/*
	 * If the seek poपूर्णांकer is positioned just beक्रमe an entry it
	 * should find the next entry.
	 */
	अगर (i % 8)
		i = i + (8 - i%8)%8;

	जबतक (i < part->len) अणु
		अगर (part->len < i + माप *len)
			अवरोध;
		len = (व्योम *)part + offset + i;
		/*
		 * len is the size of the string itself.  padlen is the
		 * total size of the encoded string.
		 */
		padlen = (माप *len + *len + 1) +
		    (8 - (माप *len + *len + 1)%8)%8;
		अगर (part->len < i + padlen + माप *khandle)
			जाओ next;
		s = (व्योम *)part + offset + i + माप *len;
		अगर (s[*len] != 0)
			जाओ next;
		khandle = (व्योम *)part + offset + i + padlen;
		अगर (!dir_emit(ctx, s, *len,
		    orangefs_khandle_to_ino(khandle),
		    DT_UNKNOWN))
			वापस 0;
		i += padlen + माप *khandle;
		i = i + (8 - i%8)%8;
		BUG_ON(i > part->len);
		ctx->pos = (ctx->pos & PART_MASK) | i;
		जारी;
next:
		i += 8;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक orangefs_dir_fill(काष्ठा orangefs_inode_s *oi,
    काष्ठा orangefs_dir *od, काष्ठा dentry *dentry,
    काष्ठा dir_context *ctx)
अणु
	काष्ठा orangefs_dir_part *part;
	माप_प्रकार count;

	count = ((ctx->pos & PART_MASK) >> PART_SHIFT) - 1;

	part = od->part;
	जबतक (part->next && count) अणु
		count--;
		part = part->next;
	पूर्ण
	/* This means the userspace file offset is invalid. */
	अगर (count) अणु
		od->error = -EIO;
		वापस -EIO;
	पूर्ण

	जबतक (part && part->len) अणु
		पूर्णांक r;
		r = fill_from_part(part, ctx);
		अगर (r < 0) अणु
			od->error = r;
			वापस r;
		पूर्ण अन्यथा अगर (r == 0) अणु
			/* Userspace buffer is full. */
			अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * The part ran out of data.  Move to the next
			 * part. */
			ctx->pos = (ctx->pos & PART_MASK) +
			    (1 << PART_SHIFT);
			part = part->next;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल loff_t orangefs_dir_llseek(काष्ठा file *file, loff_t offset,
    पूर्णांक whence)
अणु
	काष्ठा orangefs_dir *od = file->निजी_data;
	/*
	 * Delete the stored data so userspace sees new directory
	 * entries.
	 */
	अगर (!whence && offset < od->end) अणु
		काष्ठा orangefs_dir_part *part = od->part;
		जबतक (part) अणु
			काष्ठा orangefs_dir_part *next = part->next;
			vमुक्त(part);
			part = next;
		पूर्ण
		od->token = ORANGEFS_ITERATE_START;
		od->part = शून्य;
		od->end = 1 << PART_SHIFT;
	पूर्ण
	वापस शेष_llseek(file, offset, whence);
पूर्ण

अटल पूर्णांक orangefs_dir_iterate(काष्ठा file *file,
    काष्ठा dir_context *ctx)
अणु
	काष्ठा orangefs_inode_s *oi;
	काष्ठा orangefs_dir *od;
	काष्ठा dentry *dentry;
	पूर्णांक r;

	dentry = file->f_path.dentry;
	oi = ORANGEFS_I(dentry->d_inode);
	od = file->निजी_data;

	अगर (od->error)
		वापस od->error;

	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit_करोt(file, ctx))
			वापस 0;
		ctx->pos++;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (!dir_emit_करोtकरोt(file, ctx))
			वापस 0;
		ctx->pos = 1 << PART_SHIFT;
	पूर्ण

	/*
	 * The seek position is in the first synthesized part but is not
	 * valid.
	 */
	अगर ((ctx->pos & PART_MASK) == 0)
		वापस -EIO;

	r = 0;

	/*
	 * Must पढ़ो more अगर the user has sought past what has been पढ़ो
	 * so far.  Stop a user who has sought past the end.
	 */
	जबतक (od->token != ORANGEFS_ITERATE_END &&
	    ctx->pos > od->end) अणु
		r = orangefs_dir_more(oi, od, dentry);
		अगर (r)
			वापस r;
	पूर्ण
	अगर (od->token == ORANGEFS_ITERATE_END && ctx->pos > od->end)
		वापस -EIO;

	/* Then try to fill अगर there's any left in the buffer. */
	अगर (ctx->pos < od->end) अणु
		r = orangefs_dir_fill(oi, od, dentry, ctx);
		अगर (r)
			वापस r;
	पूर्ण

	/* Finally get some more and try to fill. */
	अगर (od->token != ORANGEFS_ITERATE_END) अणु
		r = orangefs_dir_more(oi, od, dentry);
		अगर (r)
			वापस r;
		r = orangefs_dir_fill(oi, od, dentry, ctx);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक orangefs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा orangefs_dir *od;
	file->निजी_data = kदो_स्मृति(माप(काष्ठा orangefs_dir),
	    GFP_KERNEL);
	अगर (!file->निजी_data)
		वापस -ENOMEM;
	od = file->निजी_data;
	od->token = ORANGEFS_ITERATE_START;
	od->part = शून्य;
	od->end = 1 << PART_SHIFT;
	od->error = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक orangefs_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा orangefs_dir *od = file->निजी_data;
	काष्ठा orangefs_dir_part *part = od->part;
	जबतक (part) अणु
		काष्ठा orangefs_dir_part *next = part->next;
		vमुक्त(part);
		part = next;
	पूर्ण
	kमुक्त(od);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations orangefs_dir_operations = अणु
	.llseek = orangefs_dir_llseek,
	.पढ़ो = generic_पढ़ो_dir,
	.iterate = orangefs_dir_iterate,
	.खोलो = orangefs_dir_खोलो,
	.release = orangefs_dir_release
पूर्ण;
