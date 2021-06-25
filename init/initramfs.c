<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/async.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/dirent.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uसमय.स>
#समावेश <linux/file.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/namei.h>
#समावेश <linux/init_syscalls.h>

अटल sमाप_प्रकार __init xग_लिखो(काष्ठा file *file, स्थिर अक्षर *p, माप_प्रकार count,
		loff_t *pos)
अणु
	sमाप_प्रकार out = 0;

	/* sys_ग_लिखो only can ग_लिखो MAX_RW_COUNT aka 2G-4K bytes at most */
	जबतक (count) अणु
		sमाप_प्रकार rv = kernel_ग_लिखो(file, p, count, pos);

		अगर (rv < 0) अणु
			अगर (rv == -EINTR || rv == -EAGAIN)
				जारी;
			वापस out ? out : rv;
		पूर्ण अन्यथा अगर (rv == 0)
			अवरोध;

		p += rv;
		out += rv;
		count -= rv;
	पूर्ण

	वापस out;
पूर्ण

अटल __initdata अक्षर *message;
अटल व्योम __init error(अक्षर *x)
अणु
	अगर (!message)
		message = x;
पूर्ण

अटल व्योम panic_show_mem(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	show_mem(0, शून्य);
	बहु_शुरू(args, fmt);
	panic(fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/* link hash */

#घोषणा N_ALIGN(len) ((((len) + 1) & ~3) + 2)

अटल __initdata काष्ठा hash अणु
	पूर्णांक ino, minor, major;
	umode_t mode;
	काष्ठा hash *next;
	अक्षर name[N_ALIGN(PATH_MAX)];
पूर्ण *head[32];

अटल अंतरभूत पूर्णांक hash(पूर्णांक major, पूर्णांक minor, पूर्णांक ino)
अणु
	अचिन्हित दीर्घ पंचांगp = ino + minor + (major << 3);
	पंचांगp += पंचांगp >> 5;
	वापस पंचांगp & 31;
पूर्ण

अटल अक्षर __init *find_link(पूर्णांक major, पूर्णांक minor, पूर्णांक ino,
			      umode_t mode, अक्षर *name)
अणु
	काष्ठा hash **p, *q;
	क्रम (p = head + hash(major, minor, ino); *p; p = &(*p)->next) अणु
		अगर ((*p)->ino != ino)
			जारी;
		अगर ((*p)->minor != minor)
			जारी;
		अगर ((*p)->major != major)
			जारी;
		अगर (((*p)->mode ^ mode) & S_IFMT)
			जारी;
		वापस (*p)->name;
	पूर्ण
	q = kदो_स्मृति(माप(काष्ठा hash), GFP_KERNEL);
	अगर (!q)
		panic_show_mem("can't allocate link hash entry");
	q->major = major;
	q->minor = minor;
	q->ino = ino;
	q->mode = mode;
	म_नकल(q->name, name);
	q->next = शून्य;
	*p = q;
	वापस शून्य;
पूर्ण

अटल व्योम __init मुक्त_hash(व्योम)
अणु
	काष्ठा hash **p, *q;
	क्रम (p = head; p < head + 32; p++) अणु
		जबतक (*p) अणु
			q = *p;
			*p = q->next;
			kमुक्त(q);
		पूर्ण
	पूर्ण
पूर्ण

अटल दीर्घ __init करो_uसमय(अक्षर *filename, समय64_t mसमय)
अणु
	काष्ठा बारpec64 t[2];

	t[0].tv_sec = mसमय;
	t[0].tv_nsec = 0;
	t[1].tv_sec = mसमय;
	t[1].tv_nsec = 0;
	वापस init_uबार(filename, t);
पूर्ण

अटल __initdata LIST_HEAD(dir_list);
काष्ठा dir_entry अणु
	काष्ठा list_head list;
	अक्षर *name;
	समय64_t mसमय;
पूर्ण;

अटल व्योम __init dir_add(स्थिर अक्षर *name, समय64_t mसमय)
अणु
	काष्ठा dir_entry *de = kदो_स्मृति(माप(काष्ठा dir_entry), GFP_KERNEL);
	अगर (!de)
		panic_show_mem("can't allocate dir_entry buffer");
	INIT_LIST_HEAD(&de->list);
	de->name = kstrdup(name, GFP_KERNEL);
	de->mसमय = mसमय;
	list_add(&de->list, &dir_list);
पूर्ण

अटल व्योम __init dir_uसमय(व्योम)
अणु
	काष्ठा dir_entry *de, *पंचांगp;
	list_क्रम_each_entry_safe(de, पंचांगp, &dir_list, list) अणु
		list_del(&de->list);
		करो_uसमय(de->name, de->mसमय);
		kमुक्त(de->name);
		kमुक्त(de);
	पूर्ण
पूर्ण

अटल __initdata समय64_t mसमय;

/* cpio header parsing */

अटल __initdata अचिन्हित दीर्घ ino, major, minor, nlink;
अटल __initdata umode_t mode;
अटल __initdata अचिन्हित दीर्घ body_len, name_len;
अटल __initdata uid_t uid;
अटल __initdata gid_t gid;
अटल __initdata अचिन्हित rdev;

अटल व्योम __init parse_header(अक्षर *s)
अणु
	अचिन्हित दीर्घ parsed[12];
	अक्षर buf[9];
	पूर्णांक i;

	buf[8] = '\0';
	क्रम (i = 0, s += 6; i < 12; i++, s += 8) अणु
		स_नकल(buf, s, 8);
		parsed[i] = simple_म_से_अदीर्घ(buf, शून्य, 16);
	पूर्ण
	ino = parsed[0];
	mode = parsed[1];
	uid = parsed[2];
	gid = parsed[3];
	nlink = parsed[4];
	mसमय = parsed[5]; /* अवरोधs in y2106 */
	body_len = parsed[6];
	major = parsed[7];
	minor = parsed[8];
	rdev = new_encode_dev(MKDEV(parsed[9], parsed[10]));
	name_len = parsed[11];
पूर्ण

/* FSM */

अटल __initdata क्रमागत state अणु
	Start,
	Collect,
	GotHeader,
	SkipIt,
	GotName,
	CopyFile,
	GotSymlink,
	Reset
पूर्ण state, next_state;

अटल __initdata अक्षर *victim;
अटल अचिन्हित दीर्घ byte_count __initdata;
अटल __initdata loff_t this_header, next_header;

अटल अंतरभूत व्योम __init eat(अचिन्हित n)
अणु
	victim += n;
	this_header += n;
	byte_count -= n;
पूर्ण

अटल __initdata अक्षर *collected;
अटल दीर्घ reमुख्यs __initdata;
अटल __initdata अक्षर *collect;

अटल व्योम __init पढ़ो_पूर्णांकo(अक्षर *buf, अचिन्हित size, क्रमागत state next)
अणु
	अगर (byte_count >= size) अणु
		collected = victim;
		eat(size);
		state = next;
	पूर्ण अन्यथा अणु
		collect = collected = buf;
		reमुख्यs = size;
		next_state = next;
		state = Collect;
	पूर्ण
पूर्ण

अटल __initdata अक्षर *header_buf, *symlink_buf, *name_buf;

अटल पूर्णांक __init करो_start(व्योम)
अणु
	पढ़ो_पूर्णांकo(header_buf, 110, GotHeader);
	वापस 0;
पूर्ण

अटल पूर्णांक __init करो_collect(व्योम)
अणु
	अचिन्हित दीर्घ n = reमुख्यs;
	अगर (byte_count < n)
		n = byte_count;
	स_नकल(collect, victim, n);
	eat(n);
	collect += n;
	अगर ((reमुख्यs -= n) != 0)
		वापस 1;
	state = next_state;
	वापस 0;
पूर्ण

अटल पूर्णांक __init करो_header(व्योम)
अणु
	अगर (स_भेद(collected, "070707", 6)==0) अणु
		error("incorrect cpio method used: use -H newc option");
		वापस 1;
	पूर्ण
	अगर (स_भेद(collected, "070701", 6)) अणु
		error("no cpio magic");
		वापस 1;
	पूर्ण
	parse_header(collected);
	next_header = this_header + N_ALIGN(name_len) + body_len;
	next_header = (next_header + 3) & ~3;
	state = SkipIt;
	अगर (name_len <= 0 || name_len > PATH_MAX)
		वापस 0;
	अगर (S_ISLNK(mode)) अणु
		अगर (body_len > PATH_MAX)
			वापस 0;
		collect = collected = symlink_buf;
		reमुख्यs = N_ALIGN(name_len) + body_len;
		next_state = GotSymlink;
		state = Collect;
		वापस 0;
	पूर्ण
	अगर (S_ISREG(mode) || !body_len)
		पढ़ो_पूर्णांकo(name_buf, N_ALIGN(name_len), GotName);
	वापस 0;
पूर्ण

अटल पूर्णांक __init करो_skip(व्योम)
अणु
	अगर (this_header + byte_count < next_header) अणु
		eat(byte_count);
		वापस 1;
	पूर्ण अन्यथा अणु
		eat(next_header - this_header);
		state = next_state;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __init करो_reset(व्योम)
अणु
	जबतक (byte_count && *victim == '\0')
		eat(1);
	अगर (byte_count && (this_header & 3))
		error("broken padding");
	वापस 1;
पूर्ण

अटल व्योम __init clean_path(अक्षर *path, umode_t भ_शेषe)
अणु
	काष्ठा kstat st;

	अगर (!init_stat(path, &st, AT_SYMLINK_NOFOLLOW) &&
	    (st.mode ^ भ_शेषe) & S_IFMT) अणु
		अगर (S_ISसूची(st.mode))
			init_सूची_हटाओ(path);
		अन्यथा
			init_unlink(path);
	पूर्ण
पूर्ण

अटल पूर्णांक __init maybe_link(व्योम)
अणु
	अगर (nlink >= 2) अणु
		अक्षर *old = find_link(major, minor, ino, mode, collected);
		अगर (old) अणु
			clean_path(collected, 0);
			वापस (init_link(old, collected) < 0) ? -1 : 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल __initdata काष्ठा file *wfile;
अटल __initdata loff_t wfile_pos;

अटल पूर्णांक __init करो_name(व्योम)
अणु
	state = SkipIt;
	next_state = Reset;
	अगर (म_भेद(collected, "TRAILER!!!") == 0) अणु
		मुक्त_hash();
		वापस 0;
	पूर्ण
	clean_path(collected, mode);
	अगर (S_ISREG(mode)) अणु
		पूर्णांक ml = maybe_link();
		अगर (ml >= 0) अणु
			पूर्णांक खोलोflags = O_WRONLY|O_CREAT;
			अगर (ml != 1)
				खोलोflags |= O_TRUNC;
			wfile = filp_खोलो(collected, खोलोflags, mode);
			अगर (IS_ERR(wfile))
				वापस 0;
			wfile_pos = 0;

			vfs_fchown(wfile, uid, gid);
			vfs_fchmod(wfile, mode);
			अगर (body_len)
				vfs_truncate(&wfile->f_path, body_len);
			state = CopyFile;
		पूर्ण
	पूर्ण अन्यथा अगर (S_ISसूची(mode)) अणु
		init_सूची_गढ़ो(collected, mode);
		init_chown(collected, uid, gid, 0);
		init_chmod(collected, mode);
		dir_add(collected, mसमय);
	पूर्ण अन्यथा अगर (S_ISBLK(mode) || S_ISCHR(mode) ||
		   S_ISFIFO(mode) || S_ISSOCK(mode)) अणु
		अगर (maybe_link() == 0) अणु
			init_mknod(collected, mode, rdev);
			init_chown(collected, uid, gid, 0);
			init_chmod(collected, mode);
			करो_uसमय(collected, mसमय);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init करो_copy(व्योम)
अणु
	अगर (byte_count >= body_len) अणु
		काष्ठा बारpec64 t[2] = अणु पूर्ण;
		अगर (xग_लिखो(wfile, victim, body_len, &wfile_pos) != body_len)
			error("write error");

		t[0].tv_sec = mसमय;
		t[1].tv_sec = mसमय;
		vfs_uबार(&wfile->f_path, t);

		fput(wfile);
		eat(body_len);
		state = SkipIt;
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (xग_लिखो(wfile, victim, byte_count, &wfile_pos) != byte_count)
			error("write error");
		body_len -= byte_count;
		eat(byte_count);
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक __init करो_symlink(व्योम)
अणु
	collected[N_ALIGN(name_len) + body_len] = '\0';
	clean_path(collected, 0);
	init_symlink(collected + N_ALIGN(name_len), collected);
	init_chown(collected, uid, gid, AT_SYMLINK_NOFOLLOW);
	करो_uसमय(collected, mसमय);
	state = SkipIt;
	next_state = Reset;
	वापस 0;
पूर्ण

अटल __initdata पूर्णांक (*actions[])(व्योम) = अणु
	[Start]		= करो_start,
	[Collect]	= करो_collect,
	[GotHeader]	= करो_header,
	[SkipIt]	= करो_skip,
	[GotName]	= करो_name,
	[CopyFile]	= करो_copy,
	[GotSymlink]	= करो_symlink,
	[Reset]		= करो_reset,
पूर्ण;

अटल दीर्घ __init ग_लिखो_buffer(अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	byte_count = len;
	victim = buf;

	जबतक (!actions[state]())
		;
	वापस len - byte_count;
पूर्ण

अटल दीर्घ __init flush_buffer(व्योम *bufv, अचिन्हित दीर्घ len)
अणु
	अक्षर *buf = (अक्षर *) bufv;
	दीर्घ written;
	दीर्घ origLen = len;
	अगर (message)
		वापस -1;
	जबतक ((written = ग_लिखो_buffer(buf, len)) < len && !message) अणु
		अक्षर c = buf[written];
		अगर (c == '0') अणु
			buf += written;
			len -= written;
			state = Start;
		पूर्ण अन्यथा अगर (c == 0) अणु
			buf += written;
			len -= written;
			state = Reset;
		पूर्ण अन्यथा
			error("junk within compressed archive");
	पूर्ण
	वापस origLen;
पूर्ण

अटल अचिन्हित दीर्घ my_inptr; /* index of next byte to be processed in inbuf */

#समावेश <linux/decompress/generic.h>

अटल अक्षर * __init unpack_to_rootfs(अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	दीर्घ written;
	decompress_fn decompress;
	स्थिर अक्षर *compress_name;
	अटल __initdata अक्षर msg_buf[64];

	header_buf = kदो_स्मृति(110, GFP_KERNEL);
	symlink_buf = kदो_स्मृति(PATH_MAX + N_ALIGN(PATH_MAX) + 1, GFP_KERNEL);
	name_buf = kदो_स्मृति(N_ALIGN(PATH_MAX), GFP_KERNEL);

	अगर (!header_buf || !symlink_buf || !name_buf)
		panic_show_mem("can't allocate buffers");

	state = Start;
	this_header = 0;
	message = शून्य;
	जबतक (!message && len) अणु
		loff_t saved_offset = this_header;
		अगर (*buf == '0' && !(this_header & 3)) अणु
			state = Start;
			written = ग_लिखो_buffer(buf, len);
			buf += written;
			len -= written;
			जारी;
		पूर्ण
		अगर (!*buf) अणु
			buf++;
			len--;
			this_header++;
			जारी;
		पूर्ण
		this_header = 0;
		decompress = decompress_method(buf, len, &compress_name);
		pr_debug("Detected %s compressed data\n", compress_name);
		अगर (decompress) अणु
			पूर्णांक res = decompress(buf, len, शून्य, flush_buffer, शून्य,
				   &my_inptr, error);
			अगर (res)
				error("decompressor failed");
		पूर्ण अन्यथा अगर (compress_name) अणु
			अगर (!message) अणु
				snम_लिखो(msg_buf, माप msg_buf,
					 "compression method %s not configured",
					 compress_name);
				message = msg_buf;
			पूर्ण
		पूर्ण अन्यथा
			error("invalid magic at start of compressed archive");
		अगर (state != Reset)
			error("junk at the end of compressed archive");
		this_header = saved_offset + my_inptr;
		buf += my_inptr;
		len -= my_inptr;
	पूर्ण
	dir_uसमय();
	kमुक्त(name_buf);
	kमुक्त(symlink_buf);
	kमुक्त(header_buf);
	वापस message;
पूर्ण

अटल पूर्णांक __initdata करो_retain_initrd;

अटल पूर्णांक __init retain_initrd_param(अक्षर *str)
अणु
	अगर (*str)
		वापस 0;
	करो_retain_initrd = 1;
	वापस 1;
पूर्ण
__setup("retain_initrd", retain_initrd_param);

#अगर_घोषित CONFIG_ARCH_HAS_KEEPINITRD
अटल पूर्णांक __init keepinitrd_setup(अक्षर *__unused)
अणु
	करो_retain_initrd = 1;
	वापस 1;
पूर्ण
__setup("keepinitrd", keepinitrd_setup);
#पूर्ण_अगर

अटल bool __initdata initramfs_async = true;
अटल पूर्णांक __init initramfs_async_setup(अक्षर *str)
अणु
	strtobool(str, &initramfs_async);
	वापस 1;
पूर्ण
__setup("initramfs_async=", initramfs_async_setup);

बाह्य अक्षर __initramfs_start[];
बाह्य अचिन्हित दीर्घ __initramfs_size;
#समावेश <linux/initrd.h>
#समावेश <linux/kexec.h>

व्योम __init reserve_initrd_mem(व्योम)
अणु
	phys_addr_t start;
	अचिन्हित दीर्घ size;

	/* Ignore the virtul address computed during device tree parsing */
	initrd_start = initrd_end = 0;

	अगर (!phys_initrd_size)
		वापस;
	/*
	 * Round the memory region to page boundaries as per मुक्त_initrd_mem()
	 * This allows us to detect whether the pages overlapping the initrd
	 * are in use, but more importantly, reserves the entire set of pages
	 * as we करोn't want these pages allocated क्रम other purposes.
	 */
	start = round_करोwn(phys_initrd_start, PAGE_SIZE);
	size = phys_initrd_size + (phys_initrd_start - start);
	size = round_up(size, PAGE_SIZE);

	अगर (!memblock_is_region_memory(start, size)) अणु
		pr_err("INITRD: 0x%08llx+0x%08lx is not a memory region",
		       (u64)start, size);
		जाओ disable;
	पूर्ण

	अगर (memblock_is_region_reserved(start, size)) अणु
		pr_err("INITRD: 0x%08llx+0x%08lx overlaps in-use memory region\n",
		       (u64)start, size);
		जाओ disable;
	पूर्ण

	memblock_reserve(start, size);
	/* Now convert initrd to भव addresses */
	initrd_start = (अचिन्हित दीर्घ)__va(phys_initrd_start);
	initrd_end = initrd_start + phys_initrd_size;
	initrd_below_start_ok = 1;

	वापस;
disable:
	pr_cont(" - disabling initrd\n");
	initrd_start = 0;
	initrd_end = 0;
पूर्ण

व्योम __weak __init मुक्त_initrd_mem(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
#अगर_घोषित CONFIG_ARCH_KEEP_MEMBLOCK
	अचिन्हित दीर्घ aligned_start = ALIGN_DOWN(start, PAGE_SIZE);
	अचिन्हित दीर्घ aligned_end = ALIGN(end, PAGE_SIZE);

	memblock_मुक्त(__pa(aligned_start), aligned_end - aligned_start);
#पूर्ण_अगर

	मुक्त_reserved_area((व्योम *)start, (व्योम *)end, POISON_FREE_INITMEM,
			"initrd");
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
अटल bool __init kexec_मुक्त_initrd(व्योम)
अणु
	अचिन्हित दीर्घ crashk_start = (अचिन्हित दीर्घ)__va(crashk_res.start);
	अचिन्हित दीर्घ crashk_end   = (अचिन्हित दीर्घ)__va(crashk_res.end);

	/*
	 * If the initrd region is overlapped with crashkernel reserved region,
	 * मुक्त only memory that is not part of crashkernel region.
	 */
	अगर (initrd_start >= crashk_end || initrd_end <= crashk_start)
		वापस false;

	/*
	 * Initialize initrd memory region since the kexec boot करोes not करो.
	 */
	स_रखो((व्योम *)initrd_start, 0, initrd_end - initrd_start);
	अगर (initrd_start < crashk_start)
		मुक्त_initrd_mem(initrd_start, crashk_start);
	अगर (initrd_end > crashk_end)
		मुक्त_initrd_mem(crashk_end, initrd_end);
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool kexec_मुक्त_initrd(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_BLK_DEV_RAM
अटल व्योम __init populate_initrd_image(अक्षर *err)
अणु
	sमाप_प्रकार written;
	काष्ठा file *file;
	loff_t pos = 0;

	unpack_to_rootfs(__initramfs_start, __initramfs_size);

	prपूर्णांकk(KERN_INFO "rootfs image is not initramfs (%s); looks like an initrd\n",
			err);
	file = filp_खोलो("/initrd.image", O_WRONLY | O_CREAT, 0700);
	अगर (IS_ERR(file))
		वापस;

	written = xग_लिखो(file, (अक्षर *)initrd_start, initrd_end - initrd_start,
			&pos);
	अगर (written != initrd_end - initrd_start)
		pr_err("/initrd.image: incomplete write (%zd != %ld)\n",
		       written, initrd_end - initrd_start);
	fput(file);
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_RAM */

अटल व्योम __init करो_populate_rootfs(व्योम *unused, async_cookie_t cookie)
अणु
	/* Load the built in initramfs */
	अक्षर *err = unpack_to_rootfs(__initramfs_start, __initramfs_size);
	अगर (err)
		panic_show_mem("%s", err); /* Failed to decompress INTERNAL initramfs */

	अगर (!initrd_start || IS_ENABLED(CONFIG_INITRAMFS_FORCE))
		जाओ करोne;

	अगर (IS_ENABLED(CONFIG_BLK_DEV_RAM))
		prपूर्णांकk(KERN_INFO "Trying to unpack rootfs image as initramfs...\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "Unpacking initramfs...\n");

	err = unpack_to_rootfs((अक्षर *)initrd_start, initrd_end - initrd_start);
	अगर (err) अणु
#अगर_घोषित CONFIG_BLK_DEV_RAM
		populate_initrd_image(err);
#अन्यथा
		prपूर्णांकk(KERN_EMERG "Initramfs unpacking failed: %s\n", err);
#पूर्ण_अगर
	पूर्ण

करोne:
	/*
	 * If the initrd region is overlapped with crashkernel reserved region,
	 * मुक्त only memory that is not part of crashkernel region.
	 */
	अगर (!करो_retain_initrd && initrd_start && !kexec_मुक्त_initrd())
		मुक्त_initrd_mem(initrd_start, initrd_end);
	initrd_start = 0;
	initrd_end = 0;

	flush_delayed_fput();
पूर्ण

अटल ASYNC_DOMAIN_EXCLUSIVE(initramfs_करोमुख्य);
अटल async_cookie_t initramfs_cookie;

व्योम रुको_क्रम_initramfs(व्योम)
अणु
	अगर (!initramfs_cookie) अणु
		/*
		 * Something beक्रमe rootfs_initcall wants to access
		 * the fileप्रणाली/initramfs. Probably a bug. Make a
		 * note, aव्योम deadlocking the machine, and let the
		 * caller's access fail as it used to.
		 */
		pr_warn_once("wait_for_initramfs() called before rootfs_initcalls\n");
		वापस;
	पूर्ण
	async_synchronize_cookie_करोमुख्य(initramfs_cookie + 1, &initramfs_करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(रुको_क्रम_initramfs);

अटल पूर्णांक __init populate_rootfs(व्योम)
अणु
	initramfs_cookie = async_schedule_करोमुख्य(करो_populate_rootfs, शून्य,
						 &initramfs_करोमुख्य);
	अगर (!initramfs_async)
		रुको_क्रम_initramfs();
	वापस 0;
पूर्ण
rootfs_initcall(populate_rootfs);
