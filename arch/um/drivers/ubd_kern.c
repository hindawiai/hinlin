<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Cambridge Greys Ltd
 * Copyright (C) 2015-2016 Anton Ivanov (aivanov@brocade.com)
 * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)
 */

/* 2001-09-28...2002-04-17
 * Partition stuff by James_McMechan@hoपंचांगail.com
 * old style ubd by setting UBD_SHIFT to 0
 * 2002-09-27...2002-10-18 massive tinkering क्रम 2.5
 * partitions have changed in 2.5
 * 2003-01-29 more tinkering क्रम 2.5.59-1
 * This should now address the sysfs problems and has
 * the symlink क्रम devfs to allow क्रम booting with
 * the common /dev/ubd/discX/... names rather than
 * only /dev/ubdN/discN this version also has lots of
 * clean ups preparing क्रम ubd-many.
 * James McMechan
 */

#घोषणा UBD_SHIFT 4

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/ata.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <kern_util.h>
#समावेश "mconsole_kern.h"
#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश "ubd.h"
#समावेश <os.h>
#समावेश "cow.h"

/* Max request size is determined by sector mask - 32K */
#घोषणा UBD_MAX_REQUEST (8 * माप(दीर्घ))

काष्ठा io_desc अणु
	अक्षर *buffer;
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ sector_mask;
	अचिन्हित दीर्घ दीर्घ cow_offset;
	अचिन्हित दीर्घ biपंचांगap_words[2];
पूर्ण;

काष्ठा io_thपढ़ो_req अणु
	काष्ठा request *req;
	पूर्णांक fds[2];
	अचिन्हित दीर्घ offsets[2];
	अचिन्हित दीर्घ दीर्घ offset;
	पूर्णांक sectorsize;
	पूर्णांक error;

	पूर्णांक desc_cnt;
	/* io_desc has to be the last element of the काष्ठा */
	काष्ठा io_desc io_desc[];
पूर्ण;


अटल काष्ठा io_thपढ़ो_req * (*irq_req_buffer)[];
अटल काष्ठा io_thपढ़ो_req *irq_reमुख्यder;
अटल पूर्णांक irq_reमुख्यder_size;

अटल काष्ठा io_thपढ़ो_req * (*io_req_buffer)[];
अटल काष्ठा io_thपढ़ो_req *io_reमुख्यder;
अटल पूर्णांक io_reमुख्यder_size;



अटल अंतरभूत पूर्णांक ubd_test_bit(__u64 bit, अचिन्हित अक्षर *data)
अणु
	__u64 n;
	पूर्णांक bits, off;

	bits = माप(data[0]) * 8;
	n = bit / bits;
	off = bit % bits;
	वापस (data[n] & (1 << off)) != 0;
पूर्ण

अटल अंतरभूत व्योम ubd_set_bit(__u64 bit, अचिन्हित अक्षर *data)
अणु
	__u64 n;
	पूर्णांक bits, off;

	bits = माप(data[0]) * 8;
	n = bit / bits;
	off = bit % bits;
	data[n] |= (1 << off);
पूर्ण
/*End stuff from ubd_user.h*/

#घोषणा DRIVER_NAME "uml-blkdev"

अटल DEFINE_MUTEX(ubd_lock);
अटल DEFINE_MUTEX(ubd_mutex); /* replaces BKL, might not be needed */

अटल पूर्णांक ubd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल व्योम ubd_release(काष्ठा gendisk *disk, भ_शेषe_t mode);
अटल पूर्णांक ubd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक ubd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo);

#घोषणा MAX_DEV (16)

अटल स्थिर काष्ठा block_device_operations ubd_blops = अणु
        .owner		= THIS_MODULE,
        .खोलो		= ubd_खोलो,
        .release	= ubd_release,
        .ioctl		= ubd_ioctl,
        .compat_ioctl	= blkdev_compat_ptr_ioctl,
	.getgeo		= ubd_getgeo,
पूर्ण;

/* Protected by ubd_lock */
अटल पूर्णांक fake_major = UBD_MAJOR;
अटल काष्ठा gendisk *ubd_gendisk[MAX_DEV];
अटल काष्ठा gendisk *fake_gendisk[MAX_DEV];

#अगर_घोषित CONFIG_BLK_DEV_UBD_SYNC
#घोषणा OPEN_FLAGS ((काष्ठा खोलोflags) अणु .r = 1, .w = 1, .s = 1, .c = 0, \
					 .cl = 1 पूर्ण)
#अन्यथा
#घोषणा OPEN_FLAGS ((काष्ठा खोलोflags) अणु .r = 1, .w = 1, .s = 0, .c = 0, \
					 .cl = 1 पूर्ण)
#पूर्ण_अगर
अटल काष्ठा खोलोflags global_खोलोflags = OPEN_FLAGS;

काष्ठा cow अणु
	/* backing file name */
	अक्षर *file;
	/* backing file fd */
	पूर्णांक fd;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ biपंचांगap_len;
	पूर्णांक biपंचांगap_offset;
	पूर्णांक data_offset;
पूर्ण;

#घोषणा MAX_SG 64

काष्ठा ubd अणु
	/* name (and fd, below) of the file खोलोed क्रम writing, either the
	 * backing or the cow file. */
	अक्षर *file;
	अक्षर *serial;
	पूर्णांक count;
	पूर्णांक fd;
	__u64 size;
	काष्ठा खोलोflags boot_खोलोflags;
	काष्ठा खोलोflags खोलोflags;
	अचिन्हित shared:1;
	अचिन्हित no_cow:1;
	अचिन्हित no_trim:1;
	काष्ठा cow cow;
	काष्ठा platक्रमm_device pdev;
	काष्ठा request_queue *queue;
	काष्ठा blk_mq_tag_set tag_set;
	spinlock_t lock;
पूर्ण;

#घोषणा DEFAULT_COW अणु \
	.file =			शून्य, \
	.fd =			-1,	\
	.biपंचांगap =		शून्य, \
	.biपंचांगap_offset =	0, \
	.data_offset =		0, \
पूर्ण

#घोषणा DEFAULT_UBD अणु \
	.file = 		शून्य, \
	.serial =		शून्य, \
	.count =		0, \
	.fd =			-1, \
	.size =			-1, \
	.boot_खोलोflags =	OPEN_FLAGS, \
	.खोलोflags =		OPEN_FLAGS, \
	.no_cow =               0, \
	.no_trim =		0, \
	.shared =		0, \
	.cow =			DEFAULT_COW, \
	.lock =			__SPIN_LOCK_UNLOCKED(ubd_devs.lock), \
पूर्ण

/* Protected by ubd_lock */
अटल काष्ठा ubd ubd_devs[MAX_DEV] = अणु [0 ... MAX_DEV - 1] = DEFAULT_UBD पूर्ण;

/* Only changed by fake_ide_setup which is a setup */
अटल पूर्णांक fake_ide = 0;
अटल काष्ठा proc_dir_entry *proc_ide_root = शून्य;
अटल काष्ठा proc_dir_entry *proc_ide = शून्य;

अटल blk_status_t ubd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd);

अटल व्योम make_proc_ide(व्योम)
अणु
	proc_ide_root = proc_सूची_गढ़ो("ide", शून्य);
	proc_ide = proc_सूची_गढ़ो("ide0", proc_ide_root);
पूर्ण

अटल पूर्णांक fake_ide_media_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_माला_दो(m, "disk\n");
	वापस 0;
पूर्ण

अटल व्योम make_ide_entries(स्थिर अक्षर *dev_name)
अणु
	काष्ठा proc_dir_entry *dir, *ent;
	अक्षर name[64];

	अगर(proc_ide_root == शून्य) make_proc_ide();

	dir = proc_सूची_गढ़ो(dev_name, proc_ide);
	अगर(!dir) वापस;

	ent = proc_create_single("media", S_IRUGO, dir,
			fake_ide_media_proc_show);
	अगर(!ent) वापस;
	snम_लिखो(name, माप(name), "ide0/%s", dev_name);
	proc_symlink(dev_name, proc_ide_root, name);
पूर्ण

अटल पूर्णांक fake_ide_setup(अक्षर *str)
अणु
	fake_ide = 1;
	वापस 1;
पूर्ण

__setup("fake_ide", fake_ide_setup);

__uml_help(fake_ide_setup,
"fake_ide\n"
"    Create ide0 entries that map onto ubd devices.\n\n"
);

अटल पूर्णांक parse_unit(अक्षर **ptr)
अणु
	अक्षर *str = *ptr, *end;
	पूर्णांक n = -1;

	अगर(है_अंक(*str)) अणु
		n = simple_म_से_अदीर्घ(str, &end, 0);
		अगर(end == str)
			वापस -1;
		*ptr = end;
	पूर्ण
	अन्यथा अगर (('a' <= *str) && (*str <= 'z')) अणु
		n = *str - 'a';
		str++;
		*ptr = str;
	पूर्ण
	वापस n;
पूर्ण

/* If *index_out == -1 at निकास, the passed option was a general one;
 * otherwise, the str poपूर्णांकer is used (and owned) inside ubd_devs array, so it
 * should not be मुक्तd on निकास.
 */
अटल पूर्णांक ubd_setup_common(अक्षर *str, पूर्णांक *index_out, अक्षर **error_out)
अणु
	काष्ठा ubd *ubd_dev;
	काष्ठा खोलोflags flags = global_खोलोflags;
	अक्षर *file, *backing_file, *serial;
	पूर्णांक n, err = 0, i;

	अगर(index_out) *index_out = -1;
	n = *str;
	अगर(n == '=')अणु
		अक्षर *end;
		पूर्णांक major;

		str++;
		अगर(!म_भेद(str, "sync"))अणु
			global_खोलोflags = of_sync(global_खोलोflags);
			वापस err;
		पूर्ण

		err = -EINVAL;
		major = simple_म_से_अदीर्घ(str, &end, 0);
		अगर((*end != '\0') || (end == str))अणु
			*error_out = "Didn't parse major number";
			वापस err;
		पूर्ण

		mutex_lock(&ubd_lock);
		अगर (fake_major != UBD_MAJOR) अणु
			*error_out = "Can't assign a fake major twice";
			जाओ out1;
		पूर्ण

		fake_major = major;

		prपूर्णांकk(KERN_INFO "Setting extra ubd major number to %d\n",
		       major);
		err = 0;
	out1:
		mutex_unlock(&ubd_lock);
		वापस err;
	पूर्ण

	n = parse_unit(&str);
	अगर(n < 0)अणु
		*error_out = "Couldn't parse device number";
		वापस -EINVAL;
	पूर्ण
	अगर(n >= MAX_DEV)अणु
		*error_out = "Device number out of range";
		वापस 1;
	पूर्ण

	err = -EBUSY;
	mutex_lock(&ubd_lock);

	ubd_dev = &ubd_devs[n];
	अगर(ubd_dev->file != शून्य)अणु
		*error_out = "Device is already configured";
		जाओ out;
	पूर्ण

	अगर (index_out)
		*index_out = n;

	err = -EINVAL;
	क्रम (i = 0; i < माप("rscdt="); i++) अणु
		चयन (*str) अणु
		हाल 'r':
			flags.w = 0;
			अवरोध;
		हाल 's':
			flags.s = 1;
			अवरोध;
		हाल 'd':
			ubd_dev->no_cow = 1;
			अवरोध;
		हाल 'c':
			ubd_dev->shared = 1;
			अवरोध;
		हाल 't':
			ubd_dev->no_trim = 1;
			अवरोध;
		हाल '=':
			str++;
			जाओ अवरोध_loop;
		शेष:
			*error_out = "Expected '=' or flag letter "
				"(r, s, c, t or d)";
			जाओ out;
		पूर्ण
		str++;
	पूर्ण

	अगर (*str == '=')
		*error_out = "Too many flags specified";
	अन्यथा
		*error_out = "Missing '='";
	जाओ out;

अवरोध_loop:
	file = strsep(&str, ",:");
	अगर (*file == '\0')
		file = शून्य;

	backing_file = strsep(&str, ",:");
	अगर (backing_file && *backing_file == '\0')
		backing_file = शून्य;

	serial = strsep(&str, ",:");
	अगर (serial && *serial == '\0')
		serial = शून्य;

	अगर (backing_file && ubd_dev->no_cow) अणु
		*error_out = "Can't specify both 'd' and a cow file";
		जाओ out;
	पूर्ण

	err = 0;
	ubd_dev->file = file;
	ubd_dev->cow.file = backing_file;
	ubd_dev->serial = serial;
	ubd_dev->boot_खोलोflags = flags;
out:
	mutex_unlock(&ubd_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ubd_setup(अक्षर *str)
अणु
	अक्षर *error;
	पूर्णांक err;

	err = ubd_setup_common(str, शून्य, &error);
	अगर(err)
		prपूर्णांकk(KERN_ERR "Failed to initialize device with \"%s\" : "
		       "%s\n", str, error);
	वापस 1;
पूर्ण

__setup("ubd", ubd_setup);
__uml_help(ubd_setup,
"ubd<n><flags>=<filename>[(:|,)<filename2>][(:|,)<serial>]\n"
"    This is used to associate a device with a file in the underlying\n"
"    filesystem. When specifying two filenames, the first one is the\n"
"    COW name and the second is the backing file name. As separator you can\n"
"    use either a ':' or a ',': the first one allows writing things like;\n"
"	ubd0=~/Uml/root_cow:~/Uml/root_backing_file\n"
"    while with a ',' the shell would not expand the 2nd '~'.\n"
"    When using only one filename, UML will detect whether to treat it like\n"
"    a COW file or a backing file. To override this detection, add the 'd'\n"
"    flag:\n"
"	ubd0d=BackingFile\n"
"    Usually, there is a filesystem in the file, but \n"
"    that's not required. Swap devices containing swap files can be\n"
"    specified like this. Also, a file which doesn't contain a\n"
"    filesystem can have its contents read in the virtual \n"
"    machine by running 'dd' on the device. <n> must be in the range\n"
"    0 to 7. Appending an 'r' to the number will cause that device\n"
"    to be mounted read-only. For example ubd1r=./ext_fs. Appending\n"
"    an 's' will cause data to be written to disk on the host immediately.\n"
"    'c' will cause the device to be treated as being shared between multiple\n"
"    UMLs and file locking will be turned off - this is appropriate for a\n"
"    cluster filesystem and inappropriate at almost all other times.\n\n"
"    't' will disable trim/discard support on the device (enabled by default).\n\n"
"    An optional device serial number can be exposed using the serial parameter\n"
"    on the cmdline which is exposed as a sysfs entry. This is particularly\n"
"    useful when a unique number should be given to the device. Note when\n"
"    specifying a label, the filename2 must be also presented. It can be\n"
"    an empty string, in which case the backing file is not used:\n"
"       ubd0=File,,Serial\n"
);

अटल पूर्णांक udb_setup(अक्षर *str)
अणु
	prपूर्णांकk("udb%s specified on command line is almost certainly a ubd -> "
	       "udb TYPO\n", str);
	वापस 1;
पूर्ण

__setup("udb", udb_setup);
__uml_help(udb_setup,
"udb\n"
"    This option is here solely to catch ubd -> udb typos, which can be\n"
"    to impossible to catch visually unless you specifically look for\n"
"    them.  The only result of any option starting with 'udb' is an error\n"
"    in the boot output.\n\n"
);

/* Only changed by ubd_init, which is an initcall. */
अटल पूर्णांक thपढ़ो_fd = -1;

/* Function to पढ़ो several request poपूर्णांकers at a समय
* handling fractional पढ़ोs अगर (and as) needed
*/

अटल पूर्णांक bulk_req_safe_पढ़ो(
	पूर्णांक fd,
	काष्ठा io_thपढ़ो_req * (*request_buffer)[],
	काष्ठा io_thपढ़ो_req **reमुख्यder,
	पूर्णांक *reमुख्यder_size,
	पूर्णांक max_recs
	)
अणु
	पूर्णांक n = 0;
	पूर्णांक res = 0;

	अगर (*reमुख्यder_size > 0) अणु
		स_हटाओ(
			(अक्षर *) request_buffer,
			(अक्षर *) reमुख्यder, *reमुख्यder_size
		);
		n = *reमुख्यder_size;
	पूर्ण

	res = os_पढ़ो_file(
			fd,
			((अक्षर *) request_buffer) + *reमुख्यder_size,
			माप(काष्ठा io_thपढ़ो_req *)*max_recs
				- *reमुख्यder_size
		);
	अगर (res > 0) अणु
		n += res;
		अगर ((n % माप(काष्ठा io_thपढ़ो_req *)) > 0) अणु
			/*
			* Read somehow वापसed not a multiple of dword
			* theoretically possible, but never observed in the
			* wild, so पढ़ो routine must be able to handle it
			*/
			*reमुख्यder_size = n % माप(काष्ठा io_thपढ़ो_req *);
			WARN(*reमुख्यder_size > 0, "UBD IPC read returned a partial result");
			स_हटाओ(
				reमुख्यder,
				((अक्षर *) request_buffer) +
					(n/माप(काष्ठा io_thपढ़ो_req *))*माप(काष्ठा io_thपढ़ो_req *),
				*reमुख्यder_size
			);
			n = n - *reमुख्यder_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		n = res;
	पूर्ण
	वापस n;
पूर्ण

/* Called without dev->lock held, and only in पूर्णांकerrupt context. */
अटल व्योम ubd_handler(व्योम)
अणु
	पूर्णांक n;
	पूर्णांक count;

	जबतक(1)अणु
		n = bulk_req_safe_पढ़ो(
			thपढ़ो_fd,
			irq_req_buffer,
			&irq_reमुख्यder,
			&irq_reमुख्यder_size,
			UBD_REQ_BUFFER_SIZE
		);
		अगर (n < 0) अणु
			अगर(n == -EAGAIN)
				अवरोध;
			prपूर्णांकk(KERN_ERR "spurious interrupt in ubd_handler, "
			       "err = %d\n", -n);
			वापस;
		पूर्ण
		क्रम (count = 0; count < n/माप(काष्ठा io_thपढ़ो_req *); count++) अणु
			काष्ठा io_thपढ़ो_req *io_req = (*irq_req_buffer)[count];

			अगर ((io_req->error == BLK_STS_NOTSUPP) && (req_op(io_req->req) == REQ_OP_DISCARD)) अणु
				blk_queue_max_discard_sectors(io_req->req->q, 0);
				blk_queue_max_ग_लिखो_zeroes_sectors(io_req->req->q, 0);
				blk_queue_flag_clear(QUEUE_FLAG_DISCARD, io_req->req->q);
			पूर्ण
			blk_mq_end_request(io_req->req, io_req->error);
			kमुक्त(io_req);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t ubd_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	ubd_handler();
	वापस IRQ_HANDLED;
पूर्ण

/* Only changed by ubd_init, which is an initcall. */
अटल पूर्णांक io_pid = -1;

अटल व्योम समाप्त_io_thपढ़ो(व्योम)
अणु
	अगर(io_pid != -1)
		os_समाप्त_process(io_pid, 1);
पूर्ण

__uml_निकासcall(समाप्त_io_thपढ़ो);

अटल अंतरभूत पूर्णांक ubd_file_size(काष्ठा ubd *ubd_dev, __u64 *size_out)
अणु
	अक्षर *file;
	पूर्णांक fd;
	पूर्णांक err;

	__u32 version;
	__u32 align;
	अक्षर *backing_file;
	समय64_t mसमय;
	अचिन्हित दीर्घ दीर्घ size;
	पूर्णांक sector_size;
	पूर्णांक biपंचांगap_offset;

	अगर (ubd_dev->file && ubd_dev->cow.file) अणु
		file = ubd_dev->cow.file;

		जाओ out;
	पूर्ण

	fd = os_खोलो_file(ubd_dev->file, of_पढ़ो(OPENFLAGS()), 0);
	अगर (fd < 0)
		वापस fd;

	err = पढ़ो_cow_header(file_पढ़ोer, &fd, &version, &backing_file, \
		&mसमय, &size, &sector_size, &align, &biपंचांगap_offset);
	os_बंद_file(fd);

	अगर(err == -EINVAL)
		file = ubd_dev->file;
	अन्यथा
		file = backing_file;

out:
	वापस os_file_size(file, size_out);
पूर्ण

अटल पूर्णांक पढ़ो_cow_biपंचांगap(पूर्णांक fd, व्योम *buf, पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक err;

	err = os_pपढ़ो_file(fd, buf, len, offset);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक backing_file_mismatch(अक्षर *file, __u64 size, समय64_t mसमय)
अणु
	समय64_t modसमय;
	अचिन्हित दीर्घ दीर्घ actual;
	पूर्णांक err;

	err = os_file_modसमय(file, &modसमय);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to get modification time of backing "
		       "file \"%s\", err = %d\n", file, -err);
		वापस err;
	पूर्ण

	err = os_file_size(file, &actual);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to get size of backing file \"%s\", "
		       "err = %d\n", file, -err);
		वापस err;
	पूर्ण

	अगर (actual != size) अणु
		/*__u64 can be a दीर्घ on AMD64 and with %lu GCC complains; so
		 * the typecast.*/
		prपूर्णांकk(KERN_ERR "Size mismatch (%llu vs %llu) of COW header "
		       "vs backing file\n", (अचिन्हित दीर्घ दीर्घ) size, actual);
		वापस -EINVAL;
	पूर्ण
	अगर (modसमय != mसमय) अणु
		prपूर्णांकk(KERN_ERR "mtime mismatch (%lld vs %lld) of COW header vs "
		       "backing file\n", mसमय, modसमय);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक path_requires_चयन(अक्षर *from_cmdline, अक्षर *from_cow, अक्षर *cow)
अणु
	काष्ठा uml_stat buf1, buf2;
	पूर्णांक err;

	अगर (from_cmdline == शून्य)
		वापस 0;
	अगर (!म_भेद(from_cmdline, from_cow))
		वापस 0;

	err = os_stat_file(from_cmdline, &buf1);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Couldn't stat '%s', err = %d\n", from_cmdline,
		       -err);
		वापस 0;
	पूर्ण
	err = os_stat_file(from_cow, &buf2);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Couldn't stat '%s', err = %d\n", from_cow,
		       -err);
		वापस 1;
	पूर्ण
	अगर ((buf1.ust_dev == buf2.ust_dev) && (buf1.ust_ino == buf2.ust_ino))
		वापस 0;

	prपूर्णांकk(KERN_ERR "Backing file mismatch - \"%s\" requested, "
	       "\"%s\" specified in COW header of \"%s\"\n",
	       from_cmdline, from_cow, cow);
	वापस 1;
पूर्ण

अटल पूर्णांक खोलो_ubd_file(अक्षर *file, काष्ठा खोलोflags *खोलोflags, पूर्णांक shared,
		  अक्षर **backing_file_out, पूर्णांक *biपंचांगap_offset_out,
		  अचिन्हित दीर्घ *biपंचांगap_len_out, पूर्णांक *data_offset_out,
		  पूर्णांक *create_cow_out)
अणु
	समय64_t mसमय;
	अचिन्हित दीर्घ दीर्घ size;
	__u32 version, align;
	अक्षर *backing_file;
	पूर्णांक fd, err, sectorsize, asked_चयन, mode = 0644;

	fd = os_खोलो_file(file, *खोलोflags, mode);
	अगर (fd < 0) अणु
		अगर ((fd == -ENOENT) && (create_cow_out != शून्य))
			*create_cow_out = 1;
		अगर (!खोलोflags->w ||
		    ((fd != -EROFS) && (fd != -EACCES)))
			वापस fd;
		खोलोflags->w = 0;
		fd = os_खोलो_file(file, *खोलोflags, mode);
		अगर (fd < 0)
			वापस fd;
	पूर्ण

	अगर (shared)
		prपूर्णांकk(KERN_INFO "Not locking \"%s\" on the host\n", file);
	अन्यथा अणु
		err = os_lock_file(fd, खोलोflags->w);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "Failed to lock '%s', err = %d\n",
			       file, -err);
			जाओ out_बंद;
		पूर्ण
	पूर्ण

	/* Successful वापस हाल! */
	अगर (backing_file_out == शून्य)
		वापस fd;

	err = पढ़ो_cow_header(file_पढ़ोer, &fd, &version, &backing_file, &mसमय,
			      &size, &sectorsize, &align, biपंचांगap_offset_out);
	अगर (err && (*backing_file_out != शून्य)) अणु
		prपूर्णांकk(KERN_ERR "Failed to read COW header from COW file "
		       "\"%s\", errno = %d\n", file, -err);
		जाओ out_बंद;
	पूर्ण
	अगर (err)
		वापस fd;

	asked_चयन = path_requires_चयन(*backing_file_out, backing_file,
					    file);

	/* Allow चयनing only अगर no mismatch. */
	अगर (asked_चयन && !backing_file_mismatch(*backing_file_out, size,
						   mसमय)) अणु
		prपूर्णांकk(KERN_ERR "Switching backing file to '%s'\n",
		       *backing_file_out);
		err = ग_लिखो_cow_header(file, fd, *backing_file_out,
				       sectorsize, align, &size);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "Switch failed, errno = %d\n", -err);
			जाओ out_बंद;
		पूर्ण
	पूर्ण अन्यथा अणु
		*backing_file_out = backing_file;
		err = backing_file_mismatch(*backing_file_out, size, mसमय);
		अगर (err)
			जाओ out_बंद;
	पूर्ण

	cow_sizes(version, size, sectorsize, align, *biपंचांगap_offset_out,
		  biपंचांगap_len_out, data_offset_out);

	वापस fd;
 out_बंद:
	os_बंद_file(fd);
	वापस err;
पूर्ण

अटल पूर्णांक create_cow_file(अक्षर *cow_file, अक्षर *backing_file,
		    काष्ठा खोलोflags flags,
		    पूर्णांक sectorsize, पूर्णांक alignment, पूर्णांक *biपंचांगap_offset_out,
		    अचिन्हित दीर्घ *biपंचांगap_len_out, पूर्णांक *data_offset_out)
अणु
	पूर्णांक err, fd;

	flags.c = 1;
	fd = खोलो_ubd_file(cow_file, &flags, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
	अगर (fd < 0) अणु
		err = fd;
		prपूर्णांकk(KERN_ERR "Open of COW file '%s' failed, errno = %d\n",
		       cow_file, -err);
		जाओ out;
	पूर्ण

	err = init_cow_file(fd, cow_file, backing_file, sectorsize, alignment,
			    biपंचांगap_offset_out, biपंचांगap_len_out,
			    data_offset_out);
	अगर (!err)
		वापस fd;
	os_बंद_file(fd);
 out:
	वापस err;
पूर्ण

अटल व्योम ubd_बंद_dev(काष्ठा ubd *ubd_dev)
अणु
	os_बंद_file(ubd_dev->fd);
	अगर(ubd_dev->cow.file == शून्य)
		वापस;

	os_बंद_file(ubd_dev->cow.fd);
	vमुक्त(ubd_dev->cow.biपंचांगap);
	ubd_dev->cow.biपंचांगap = शून्य;
पूर्ण

अटल पूर्णांक ubd_खोलो_dev(काष्ठा ubd *ubd_dev)
अणु
	काष्ठा खोलोflags flags;
	अक्षर **back_ptr;
	पूर्णांक err, create_cow, *create_ptr;
	पूर्णांक fd;

	ubd_dev->खोलोflags = ubd_dev->boot_खोलोflags;
	create_cow = 0;
	create_ptr = (ubd_dev->cow.file != शून्य) ? &create_cow : शून्य;
	back_ptr = ubd_dev->no_cow ? शून्य : &ubd_dev->cow.file;

	fd = खोलो_ubd_file(ubd_dev->file, &ubd_dev->खोलोflags, ubd_dev->shared,
				back_ptr, &ubd_dev->cow.biपंचांगap_offset,
				&ubd_dev->cow.biपंचांगap_len, &ubd_dev->cow.data_offset,
				create_ptr);

	अगर((fd == -ENOENT) && create_cow)अणु
		fd = create_cow_file(ubd_dev->file, ubd_dev->cow.file,
					  ubd_dev->खोलोflags, SECTOR_SIZE, PAGE_SIZE,
					  &ubd_dev->cow.biपंचांगap_offset,
					  &ubd_dev->cow.biपंचांगap_len,
					  &ubd_dev->cow.data_offset);
		अगर(fd >= 0)अणु
			prपूर्णांकk(KERN_INFO "Creating \"%s\" as COW file for "
			       "\"%s\"\n", ubd_dev->file, ubd_dev->cow.file);
		पूर्ण
	पूर्ण

	अगर(fd < 0)अणु
		prपूर्णांकk("Failed to open '%s', errno = %d\n", ubd_dev->file,
		       -fd);
		वापस fd;
	पूर्ण
	ubd_dev->fd = fd;

	अगर(ubd_dev->cow.file != शून्य)अणु
		blk_queue_max_hw_sectors(ubd_dev->queue, 8 * माप(दीर्घ));

		err = -ENOMEM;
		ubd_dev->cow.biपंचांगap = vदो_स्मृति(ubd_dev->cow.biपंचांगap_len);
		अगर(ubd_dev->cow.biपंचांगap == शून्य)अणु
			prपूर्णांकk(KERN_ERR "Failed to vmalloc COW bitmap\n");
			जाओ error;
		पूर्ण
		flush_tlb_kernel_vm();

		err = पढ़ो_cow_biपंचांगap(ubd_dev->fd, ubd_dev->cow.biपंचांगap,
				      ubd_dev->cow.biपंचांगap_offset,
				      ubd_dev->cow.biपंचांगap_len);
		अगर(err < 0)
			जाओ error;

		flags = ubd_dev->खोलोflags;
		flags.w = 0;
		err = खोलो_ubd_file(ubd_dev->cow.file, &flags, ubd_dev->shared, शून्य,
				    शून्य, शून्य, शून्य, शून्य);
		अगर(err < 0) जाओ error;
		ubd_dev->cow.fd = err;
	पूर्ण
	अगर (ubd_dev->no_trim == 0) अणु
		ubd_dev->queue->limits.discard_granularity = SECTOR_SIZE;
		ubd_dev->queue->limits.discard_alignment = SECTOR_SIZE;
		blk_queue_max_discard_sectors(ubd_dev->queue, UBD_MAX_REQUEST);
		blk_queue_max_ग_लिखो_zeroes_sectors(ubd_dev->queue, UBD_MAX_REQUEST);
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, ubd_dev->queue);
	पूर्ण
	blk_queue_flag_set(QUEUE_FLAG_NONROT, ubd_dev->queue);
	वापस 0;
 error:
	os_बंद_file(ubd_dev->fd);
	वापस err;
पूर्ण

अटल व्योम ubd_device_release(काष्ठा device *dev)
अणु
	काष्ठा ubd *ubd_dev = dev_get_drvdata(dev);

	blk_cleanup_queue(ubd_dev->queue);
	blk_mq_मुक्त_tag_set(&ubd_dev->tag_set);
	*ubd_dev = ((काष्ठा ubd) DEFAULT_UBD);
पूर्ण

अटल sमाप_प्रकार serial_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा ubd *ubd_dev = disk->निजी_data;

	अगर (!ubd_dev)
		वापस 0;

	वापस प्र_लिखो(buf, "%s", ubd_dev->serial);
पूर्ण

अटल DEVICE_ATTR_RO(serial);

अटल काष्ठा attribute *ubd_attrs[] = अणु
	&dev_attr_serial.attr,
	शून्य,
पूर्ण;

अटल umode_t ubd_attrs_are_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *a, पूर्णांक n)
अणु
	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group ubd_attr_group = अणु
	.attrs = ubd_attrs,
	.is_visible = ubd_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ubd_attr_groups[] = अणु
	&ubd_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ubd_disk_रेजिस्टर(पूर्णांक major, u64 size, पूर्णांक unit,
			     काष्ठा gendisk **disk_out)
अणु
	काष्ठा device *parent = शून्य;
	काष्ठा gendisk *disk;

	disk = alloc_disk(1 << UBD_SHIFT);
	अगर(disk == शून्य)
		वापस -ENOMEM;

	disk->major = major;
	disk->first_minor = unit << UBD_SHIFT;
	disk->fops = &ubd_blops;
	set_capacity(disk, size / 512);
	अगर (major == UBD_MAJOR)
		प्र_लिखो(disk->disk_name, "ubd%c", 'a' + unit);
	अन्यथा
		प्र_लिखो(disk->disk_name, "ubd_fake%d", unit);

	/* sysfs रेजिस्टर (not क्रम ide fake devices) */
	अगर (major == UBD_MAJOR) अणु
		ubd_devs[unit].pdev.id   = unit;
		ubd_devs[unit].pdev.name = DRIVER_NAME;
		ubd_devs[unit].pdev.dev.release = ubd_device_release;
		dev_set_drvdata(&ubd_devs[unit].pdev.dev, &ubd_devs[unit]);
		platक्रमm_device_रेजिस्टर(&ubd_devs[unit].pdev);
		parent = &ubd_devs[unit].pdev.dev;
	पूर्ण

	disk->निजी_data = &ubd_devs[unit];
	disk->queue = ubd_devs[unit].queue;
	device_add_disk(parent, disk, ubd_attr_groups);

	*disk_out = disk;
	वापस 0;
पूर्ण

#घोषणा ROUND_BLOCK(n) ((n + (SECTOR_SIZE - 1)) & (-SECTOR_SIZE))

अटल स्थिर काष्ठा blk_mq_ops ubd_mq_ops = अणु
	.queue_rq = ubd_queue_rq,
पूर्ण;

अटल पूर्णांक ubd_add(पूर्णांक n, अक्षर **error_out)
अणु
	काष्ठा ubd *ubd_dev = &ubd_devs[n];
	पूर्णांक err = 0;

	अगर(ubd_dev->file == शून्य)
		जाओ out;

	err = ubd_file_size(ubd_dev, &ubd_dev->size);
	अगर(err < 0)अणु
		*error_out = "Couldn't determine size of device's file";
		जाओ out;
	पूर्ण

	ubd_dev->size = ROUND_BLOCK(ubd_dev->size);

	ubd_dev->tag_set.ops = &ubd_mq_ops;
	ubd_dev->tag_set.queue_depth = 64;
	ubd_dev->tag_set.numa_node = NUMA_NO_NODE;
	ubd_dev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ubd_dev->tag_set.driver_data = ubd_dev;
	ubd_dev->tag_set.nr_hw_queues = 1;

	err = blk_mq_alloc_tag_set(&ubd_dev->tag_set);
	अगर (err)
		जाओ out;

	ubd_dev->queue = blk_mq_init_queue(&ubd_dev->tag_set);
	अगर (IS_ERR(ubd_dev->queue)) अणु
		err = PTR_ERR(ubd_dev->queue);
		जाओ out_cleanup_tags;
	पूर्ण

	ubd_dev->queue->queuedata = ubd_dev;
	blk_queue_ग_लिखो_cache(ubd_dev->queue, true, false);

	blk_queue_max_segments(ubd_dev->queue, MAX_SG);
	blk_queue_segment_boundary(ubd_dev->queue, PAGE_SIZE - 1);
	err = ubd_disk_रेजिस्टर(UBD_MAJOR, ubd_dev->size, n, &ubd_gendisk[n]);
	अगर(err)अणु
		*error_out = "Failed to register device";
		जाओ out_cleanup_tags;
	पूर्ण

	अगर (fake_major != UBD_MAJOR)
		ubd_disk_रेजिस्टर(fake_major, ubd_dev->size, n,
				  &fake_gendisk[n]);

	/*
	 * Perhaps this should also be under the "if (fake_major)" above
	 * using the fake_disk->disk_name
	 */
	अगर (fake_ide)
		make_ide_entries(ubd_gendisk[n]->disk_name);

	err = 0;
out:
	वापस err;

out_cleanup_tags:
	blk_mq_मुक्त_tag_set(&ubd_dev->tag_set);
	अगर (!(IS_ERR(ubd_dev->queue)))
		blk_cleanup_queue(ubd_dev->queue);
	जाओ out;
पूर्ण

अटल पूर्णांक ubd_config(अक्षर *str, अक्षर **error_out)
अणु
	पूर्णांक n, ret;

	/* This string is possibly broken up and stored, so it's only
	 * मुक्तd अगर ubd_setup_common fails, or अगर only general options
	 * were set.
	 */
	str = kstrdup(str, GFP_KERNEL);
	अगर (str == शून्य) अणु
		*error_out = "Failed to allocate memory";
		वापस -ENOMEM;
	पूर्ण

	ret = ubd_setup_common(str, &n, error_out);
	अगर (ret)
		जाओ err_मुक्त;

	अगर (n == -1) अणु
		ret = 0;
		जाओ err_मुक्त;
	पूर्ण

	mutex_lock(&ubd_lock);
	ret = ubd_add(n, error_out);
	अगर (ret)
		ubd_devs[n].file = शून्य;
	mutex_unlock(&ubd_lock);

out:
	वापस ret;

err_मुक्त:
	kमुक्त(str);
	जाओ out;
पूर्ण

अटल पूर्णांक ubd_get_config(अक्षर *name, अक्षर *str, पूर्णांक size, अक्षर **error_out)
अणु
	काष्ठा ubd *ubd_dev;
	पूर्णांक n, len = 0;

	n = parse_unit(&name);
	अगर((n >= MAX_DEV) || (n < 0))अणु
		*error_out = "ubd_get_config : device number out of range";
		वापस -1;
	पूर्ण

	ubd_dev = &ubd_devs[n];
	mutex_lock(&ubd_lock);

	अगर(ubd_dev->file == शून्य)अणु
		CONFIG_CHUNK(str, size, len, "", 1);
		जाओ out;
	पूर्ण

	CONFIG_CHUNK(str, size, len, ubd_dev->file, 0);

	अगर(ubd_dev->cow.file != शून्य)अणु
		CONFIG_CHUNK(str, size, len, ",", 0);
		CONFIG_CHUNK(str, size, len, ubd_dev->cow.file, 1);
	पूर्ण
	अन्यथा CONFIG_CHUNK(str, size, len, "", 1);

 out:
	mutex_unlock(&ubd_lock);
	वापस len;
पूर्ण

अटल पूर्णांक ubd_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out)
अणु
	पूर्णांक n;

	n = parse_unit(str);
	*start_out = 0;
	*end_out = MAX_DEV - 1;
	वापस n;
पूर्ण

अटल पूर्णांक ubd_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	काष्ठा gendisk *disk = ubd_gendisk[n];
	काष्ठा ubd *ubd_dev;
	पूर्णांक err = -ENODEV;

	mutex_lock(&ubd_lock);

	ubd_dev = &ubd_devs[n];

	अगर(ubd_dev->file == शून्य)
		जाओ out;

	/* you cannot हटाओ a खोलो disk */
	err = -EBUSY;
	अगर(ubd_dev->count > 0)
		जाओ out;

	ubd_gendisk[n] = शून्य;
	अगर(disk != शून्य)अणु
		del_gendisk(disk);
		put_disk(disk);
	पूर्ण

	अगर(fake_gendisk[n] != शून्य)अणु
		del_gendisk(fake_gendisk[n]);
		put_disk(fake_gendisk[n]);
		fake_gendisk[n] = शून्य;
	पूर्ण

	err = 0;
	platक्रमm_device_unरेजिस्टर(&ubd_dev->pdev);
out:
	mutex_unlock(&ubd_lock);
	वापस err;
पूर्ण

/* All these are called by mconsole in process context and without
 * ubd-specअगरic locks.  The काष्ठाure itself is स्थिर except क्रम .list.
 */
अटल काष्ठा mc_device ubd_mc = अणु
	.list		= LIST_HEAD_INIT(ubd_mc.list),
	.name		= "ubd",
	.config		= ubd_config,
	.get_config	= ubd_get_config,
	.id		= ubd_id,
	.हटाओ		= ubd_हटाओ,
पूर्ण;

अटल पूर्णांक __init ubd_mc_init(व्योम)
अणु
	mconsole_रेजिस्टर_dev(&ubd_mc);
	वापस 0;
पूर्ण

__initcall(ubd_mc_init);

अटल पूर्णांक __init ubd0_init(व्योम)
अणु
	काष्ठा ubd *ubd_dev = &ubd_devs[0];

	mutex_lock(&ubd_lock);
	अगर(ubd_dev->file == शून्य)
		ubd_dev->file = "root_fs";
	mutex_unlock(&ubd_lock);

	वापस 0;
पूर्ण

__initcall(ubd0_init);

/* Used in ubd_init, which is an initcall */
अटल काष्ठा platक्रमm_driver ubd_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ubd_init(व्योम)
अणु
	अक्षर *error;
	पूर्णांक i, err;

	अगर (रेजिस्टर_blkdev(UBD_MAJOR, "ubd"))
		वापस -1;

	अगर (fake_major != UBD_MAJOR) अणु
		अक्षर name[माप("ubd_nnn\0")];

		snम_लिखो(name, माप(name), "ubd_%d", fake_major);
		अगर (रेजिस्टर_blkdev(fake_major, "ubd"))
			वापस -1;
	पूर्ण

	irq_req_buffer = kदो_स्मृति_array(UBD_REQ_BUFFER_SIZE,
				       माप(काष्ठा io_thपढ़ो_req *),
				       GFP_KERNEL
		);
	irq_reमुख्यder = 0;

	अगर (irq_req_buffer == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to initialize ubd buffering\n");
		वापस -1;
	पूर्ण
	io_req_buffer = kदो_स्मृति_array(UBD_REQ_BUFFER_SIZE,
				      माप(काष्ठा io_thपढ़ो_req *),
				      GFP_KERNEL
		);

	io_reमुख्यder = 0;

	अगर (io_req_buffer == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to initialize ubd buffering\n");
		वापस -1;
	पूर्ण
	platक्रमm_driver_रेजिस्टर(&ubd_driver);
	mutex_lock(&ubd_lock);
	क्रम (i = 0; i < MAX_DEV; i++)अणु
		err = ubd_add(i, &error);
		अगर(err)
			prपूर्णांकk(KERN_ERR "Failed to initialize ubd device %d :"
			       "%s\n", i, error);
	पूर्ण
	mutex_unlock(&ubd_lock);
	वापस 0;
पूर्ण

late_initcall(ubd_init);

अटल पूर्णांक __init ubd_driver_init(व्योम)अणु
	अचिन्हित दीर्घ stack;
	पूर्णांक err;

	/* Set by CONFIG_BLK_DEV_UBD_SYNC or ubd=sync.*/
	अगर(global_खोलोflags.s)अणु
		prपूर्णांकk(KERN_INFO "ubd: Synchronous mode\n");
		/* Letting ubd=sync be like using ubd#s= instead of ubd#= is
		 * enough. So use anyway the io thपढ़ो. */
	पूर्ण
	stack = alloc_stack(0, 0);
	io_pid = start_io_thपढ़ो(stack + PAGE_SIZE - माप(व्योम *),
				 &thपढ़ो_fd);
	अगर(io_pid < 0)अणु
		prपूर्णांकk(KERN_ERR
		       "ubd : Failed to start I/O thread (errno = %d) - "
		       "falling back to synchronous I/O\n", -io_pid);
		io_pid = -1;
		वापस 0;
	पूर्ण
	err = um_request_irq(UBD_IRQ, thपढ़ो_fd, IRQ_READ, ubd_पूर्णांकr,
			     0, "ubd", ubd_devs);
	अगर(err < 0)
		prपूर्णांकk(KERN_ERR "um_request_irq failed - errno = %d\n", -err);
	वापस 0;
पूर्ण

device_initcall(ubd_driver_init);

अटल पूर्णांक ubd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा ubd *ubd_dev = disk->निजी_data;
	पूर्णांक err = 0;

	mutex_lock(&ubd_mutex);
	अगर(ubd_dev->count == 0)अणु
		err = ubd_खोलो_dev(ubd_dev);
		अगर(err)अणु
			prपूर्णांकk(KERN_ERR "%s: Can't open \"%s\": errno = %d\n",
			       disk->disk_name, ubd_dev->file, -err);
			जाओ out;
		पूर्ण
	पूर्ण
	ubd_dev->count++;
	set_disk_ro(disk, !ubd_dev->खोलोflags.w);

	/* This should no more be needed. And it didn't work anyway to exclude
	 * पढ़ो-ग_लिखो remounting of fileप्रणालीs.*/
	/*अगर((mode & FMODE_WRITE) && !ubd_dev->खोलोflags.w)अणु
	        अगर(--ubd_dev->count == 0) ubd_बंद_dev(ubd_dev);
	        err = -EROFS;
	पूर्ण*/
out:
	mutex_unlock(&ubd_mutex);
	वापस err;
पूर्ण

अटल व्योम ubd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा ubd *ubd_dev = disk->निजी_data;

	mutex_lock(&ubd_mutex);
	अगर(--ubd_dev->count == 0)
		ubd_बंद_dev(ubd_dev);
	mutex_unlock(&ubd_mutex);
पूर्ण

अटल व्योम cowअगरy_biपंचांगap(__u64 io_offset, पूर्णांक length, अचिन्हित दीर्घ *cow_mask,
			  __u64 *cow_offset, अचिन्हित दीर्घ *biपंचांगap,
			  __u64 biपंचांगap_offset, अचिन्हित दीर्घ *biपंचांगap_words,
			  __u64 biपंचांगap_len)
अणु
	__u64 sector = io_offset >> SECTOR_SHIFT;
	पूर्णांक i, update_biपंचांगap = 0;

	क्रम (i = 0; i < length >> SECTOR_SHIFT; i++) अणु
		अगर(cow_mask != शून्य)
			ubd_set_bit(i, (अचिन्हित अक्षर *) cow_mask);
		अगर(ubd_test_bit(sector + i, (अचिन्हित अक्षर *) biपंचांगap))
			जारी;

		update_biपंचांगap = 1;
		ubd_set_bit(sector + i, (अचिन्हित अक्षर *) biपंचांगap);
	पूर्ण

	अगर(!update_biपंचांगap)
		वापस;

	*cow_offset = sector / (माप(अचिन्हित दीर्घ) * 8);

	/* This takes care of the हाल where we're exactly at the end of the
	 * device, and *cow_offset + 1 is off the end.  So, just back it up
	 * by one word.  Thanks to Lynn Kerby क्रम the fix and James McMechan
	 * क्रम the original diagnosis.
	 */
	अगर (*cow_offset == (DIV_ROUND_UP(biपंचांगap_len,
					 माप(अचिन्हित दीर्घ)) - 1))
		(*cow_offset)--;

	biपंचांगap_words[0] = biपंचांगap[*cow_offset];
	biपंचांगap_words[1] = biपंचांगap[*cow_offset + 1];

	*cow_offset *= माप(अचिन्हित दीर्घ);
	*cow_offset += biपंचांगap_offset;
पूर्ण

अटल व्योम cowअगरy_req(काष्ठा io_thपढ़ो_req *req, काष्ठा io_desc *segment,
		       अचिन्हित दीर्घ offset, अचिन्हित दीर्घ *biपंचांगap,
		       __u64 biपंचांगap_offset, __u64 biपंचांगap_len)
अणु
	__u64 sector = offset >> SECTOR_SHIFT;
	पूर्णांक i;

	अगर (segment->length > (माप(segment->sector_mask) * 8) << SECTOR_SHIFT)
		panic("Operation too long");

	अगर (req_op(req->req) == REQ_OP_READ) अणु
		क्रम (i = 0; i < segment->length >> SECTOR_SHIFT; i++) अणु
			अगर(ubd_test_bit(sector + i, (अचिन्हित अक्षर *) biपंचांगap))
				ubd_set_bit(i, (अचिन्हित अक्षर *)
					    &segment->sector_mask);
		पूर्ण
	पूर्ण अन्यथा अणु
		cowअगरy_biपंचांगap(offset, segment->length, &segment->sector_mask,
			      &segment->cow_offset, biपंचांगap, biपंचांगap_offset,
			      segment->biपंचांगap_words, biपंचांगap_len);
	पूर्ण
पूर्ण

अटल व्योम ubd_map_req(काष्ठा ubd *dev, काष्ठा io_thपढ़ो_req *io_req,
			काष्ठा request *req)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा req_iterator iter;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ byte_offset = io_req->offset;
	पूर्णांक op = req_op(req);

	अगर (op == REQ_OP_WRITE_ZEROES || op == REQ_OP_DISCARD) अणु
		io_req->io_desc[0].buffer = शून्य;
		io_req->io_desc[0].length = blk_rq_bytes(req);
	पूर्ण अन्यथा अणु
		rq_क्रम_each_segment(bvec, req, iter) अणु
			BUG_ON(i >= io_req->desc_cnt);

			io_req->io_desc[i].buffer =
				page_address(bvec.bv_page) + bvec.bv_offset;
			io_req->io_desc[i].length = bvec.bv_len;
			i++;
		पूर्ण
	पूर्ण

	अगर (dev->cow.file) अणु
		क्रम (i = 0; i < io_req->desc_cnt; i++) अणु
			cowअगरy_req(io_req, &io_req->io_desc[i], byte_offset,
				   dev->cow.biपंचांगap, dev->cow.biपंचांगap_offset,
				   dev->cow.biपंचांगap_len);
			byte_offset += io_req->io_desc[i].length;
		पूर्ण

	पूर्ण
पूर्ण

अटल काष्ठा io_thपढ़ो_req *ubd_alloc_req(काष्ठा ubd *dev, काष्ठा request *req,
					   पूर्णांक desc_cnt)
अणु
	काष्ठा io_thपढ़ो_req *io_req;
	पूर्णांक i;

	io_req = kदो_स्मृति(माप(*io_req) +
			 (desc_cnt * माप(काष्ठा io_desc)),
			 GFP_ATOMIC);
	अगर (!io_req)
		वापस शून्य;

	io_req->req = req;
	अगर (dev->cow.file)
		io_req->fds[0] = dev->cow.fd;
	अन्यथा
		io_req->fds[0] = dev->fd;
	io_req->error = 0;
	io_req->sectorsize = SECTOR_SIZE;
	io_req->fds[1] = dev->fd;
	io_req->offset = (u64) blk_rq_pos(req) << SECTOR_SHIFT;
	io_req->offsets[0] = 0;
	io_req->offsets[1] = dev->cow.data_offset;

	क्रम (i = 0 ; i < desc_cnt; i++) अणु
		io_req->io_desc[i].sector_mask = 0;
		io_req->io_desc[i].cow_offset = -1;
	पूर्ण

	वापस io_req;
पूर्ण

अटल पूर्णांक ubd_submit_request(काष्ठा ubd *dev, काष्ठा request *req)
अणु
	पूर्णांक segs = 0;
	काष्ठा io_thपढ़ो_req *io_req;
	पूर्णांक ret;
	पूर्णांक op = req_op(req);

	अगर (op == REQ_OP_FLUSH)
		segs = 0;
	अन्यथा अगर (op == REQ_OP_WRITE_ZEROES || op == REQ_OP_DISCARD)
		segs = 1;
	अन्यथा
		segs = blk_rq_nr_phys_segments(req);

	io_req = ubd_alloc_req(dev, req, segs);
	अगर (!io_req)
		वापस -ENOMEM;

	io_req->desc_cnt = segs;
	अगर (segs)
		ubd_map_req(dev, io_req, req);

	ret = os_ग_लिखो_file(thपढ़ो_fd, &io_req, माप(io_req));
	अगर (ret != माप(io_req)) अणु
		अगर (ret != -EAGAIN)
			pr_err("write to io thread failed: %d\n", -ret);
		kमुक्त(io_req);
	पूर्ण
	वापस ret;
पूर्ण

अटल blk_status_t ubd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा ubd *ubd_dev = hctx->queue->queuedata;
	काष्ठा request *req = bd->rq;
	पूर्णांक ret = 0, res = BLK_STS_OK;

	blk_mq_start_request(req);

	spin_lock_irq(&ubd_dev->lock);

	चयन (req_op(req)) अणु
	हाल REQ_OP_FLUSH:
	हाल REQ_OP_READ:
	हाल REQ_OP_WRITE:
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_WRITE_ZEROES:
		ret = ubd_submit_request(ubd_dev, req);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		res = BLK_STS_NOTSUPP;
	पूर्ण

	spin_unlock_irq(&ubd_dev->lock);

	अगर (ret < 0) अणु
		अगर (ret == -ENOMEM)
			res = BLK_STS_RESOURCE;
		अन्यथा
			res = BLK_STS_DEV_RESOURCE;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक ubd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा ubd *ubd_dev = bdev->bd_disk->निजी_data;

	geo->heads = 128;
	geo->sectors = 32;
	geo->cylinders = ubd_dev->size / (128 * 32 * 512);
	वापस 0;
पूर्ण

अटल पूर्णांक ubd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ubd *ubd_dev = bdev->bd_disk->निजी_data;
	u16 ubd_id[ATA_ID_WORDS];

	चयन (cmd) अणु
		काष्ठा cdrom_volctrl volume;
	हाल HDIO_GET_IDENTITY:
		स_रखो(&ubd_id, 0, ATA_ID_WORDS * 2);
		ubd_id[ATA_ID_CYLS]	= ubd_dev->size / (128 * 32 * 512);
		ubd_id[ATA_ID_HEADS]	= 128;
		ubd_id[ATA_ID_SECTORS]	= 32;
		अगर(copy_to_user((अक्षर __user *) arg, (अक्षर *) &ubd_id,
				 माप(ubd_id)))
			वापस -EFAULT;
		वापस 0;

	हाल CDROMVOLREAD:
		अगर(copy_from_user(&volume, (अक्षर __user *) arg, माप(volume)))
			वापस -EFAULT;
		volume.channel0 = 255;
		volume.channel1 = 255;
		volume.channel2 = 255;
		volume.channel3 = 255;
		अगर(copy_to_user((अक्षर __user *) arg, &volume, माप(volume)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक map_error(पूर्णांक error_code)
अणु
	चयन (error_code) अणु
	हाल 0:
		वापस BLK_STS_OK;
	हाल ENOSYS:
	हाल EOPNOTSUPP:
		वापस BLK_STS_NOTSUPP;
	हाल ENOSPC:
		वापस BLK_STS_NOSPC;
	पूर्ण
	वापस BLK_STS_IOERR;
पूर्ण

/*
 * Everything from here onwards *IS NOT PART OF THE KERNEL*
 *
 * The following functions are part of UML hypervisor code.
 * All functions from here onwards are executed as a helper
 * thपढ़ो and are not allowed to execute any kernel functions.
 *
 * Any communication must occur strictly via shared memory and IPC.
 *
 * Do not add prपूर्णांकks, locks, kernel memory operations, etc - it
 * will result in unpredictable behaviour and/or crashes.
 */

अटल पूर्णांक update_biपंचांगap(काष्ठा io_thपढ़ो_req *req, काष्ठा io_desc *segment)
अणु
	पूर्णांक n;

	अगर (segment->cow_offset == -1)
		वापस map_error(0);

	n = os_pग_लिखो_file(req->fds[1], &segment->biपंचांगap_words,
			  माप(segment->biपंचांगap_words), segment->cow_offset);
	अगर (n != माप(segment->biपंचांगap_words))
		वापस map_error(-n);

	वापस map_error(0);
पूर्ण

अटल व्योम करो_io(काष्ठा io_thपढ़ो_req *req, काष्ठा io_desc *desc)
अणु
	अक्षर *buf = शून्य;
	अचिन्हित दीर्घ len;
	पूर्णांक n, nsectors, start, end, bit;
	__u64 off;

	/* FLUSH is really a special हाल, we cannot "case" it with others */

	अगर (req_op(req->req) == REQ_OP_FLUSH) अणु
		/* fds[0] is always either the rw image or our cow file */
		req->error = map_error(-os_sync_file(req->fds[0]));
		वापस;
	पूर्ण

	nsectors = desc->length / req->sectorsize;
	start = 0;
	करो अणु
		bit = ubd_test_bit(start, (अचिन्हित अक्षर *) &desc->sector_mask);
		end = start;
		जबतक((end < nsectors) &&
		      (ubd_test_bit(end, (अचिन्हित अक्षर *) &desc->sector_mask) == bit))
			end++;

		off = req->offset + req->offsets[bit] +
			start * req->sectorsize;
		len = (end - start) * req->sectorsize;
		अगर (desc->buffer != शून्य)
			buf = &desc->buffer[start * req->sectorsize];

		चयन (req_op(req->req)) अणु
		हाल REQ_OP_READ:
			n = 0;
			करो अणु
				buf = &buf[n];
				len -= n;
				n = os_pपढ़ो_file(req->fds[bit], buf, len, off);
				अगर (n < 0) अणु
					req->error = map_error(-n);
					वापस;
				पूर्ण
			पूर्ण जबतक((n < len) && (n != 0));
			अगर (n < len) स_रखो(&buf[n], 0, len - n);
			अवरोध;
		हाल REQ_OP_WRITE:
			n = os_pग_लिखो_file(req->fds[bit], buf, len, off);
			अगर(n != len)अणु
				req->error = map_error(-n);
				वापस;
			पूर्ण
			अवरोध;
		हाल REQ_OP_DISCARD:
		हाल REQ_OP_WRITE_ZEROES:
			n = os_falloc_punch(req->fds[bit], off, len);
			अगर (n) अणु
				req->error = map_error(-n);
				वापस;
			पूर्ण
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			req->error = BLK_STS_NOTSUPP;
			वापस;
		पूर्ण

		start = end;
	पूर्ण जबतक(start < nsectors);

	req->offset += len;
	req->error = update_biपंचांगap(req, desc);
पूर्ण

/* Changed in start_io_thपढ़ो, which is serialized by being called only
 * from ubd_init, which is an initcall.
 */
पूर्णांक kernel_fd = -1;

/* Only changed by the io thपढ़ो. XXX: currently unused. */
अटल पूर्णांक io_count = 0;

पूर्णांक io_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक n, count, written, res;

	os_fix_helper_संकेतs();

	जबतक(1)अणु
		n = bulk_req_safe_पढ़ो(
			kernel_fd,
			io_req_buffer,
			&io_reमुख्यder,
			&io_reमुख्यder_size,
			UBD_REQ_BUFFER_SIZE
		);
		अगर (n <= 0) अणु
			अगर (n == -EAGAIN)
				ubd_पढ़ो_poll(-1);

			जारी;
		पूर्ण

		क्रम (count = 0; count < n/माप(काष्ठा io_thपढ़ो_req *); count++) अणु
			काष्ठा io_thपढ़ो_req *req = (*io_req_buffer)[count];
			पूर्णांक i;

			io_count++;
			क्रम (i = 0; !req->error && i < req->desc_cnt; i++)
				करो_io(req, &(req->io_desc[i]));

		पूर्ण

		written = 0;

		करो अणु
			res = os_ग_लिखो_file(kernel_fd,
					    ((अक्षर *) io_req_buffer) + written,
					    n - written);
			अगर (res >= 0) अणु
				written += res;
			पूर्ण
			अगर (written < n) अणु
				ubd_ग_लिखो_poll(-1);
			पूर्ण
		पूर्ण जबतक (written < n);
	पूर्ण

	वापस 0;
पूर्ण
