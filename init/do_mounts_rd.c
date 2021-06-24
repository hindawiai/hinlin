<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/minix_fs.h>
#समावेश <linux/ext2_fs.h>
#समावेश <linux/romfs_fs.h>
#समावेश <uapi/linux/cramfs_fs.h>
#समावेश <linux/initrd.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश "do_mounts.h"
#समावेश "../fs/squashfs/squashfs_fs.h"

#समावेश <linux/decompress/generic.h>

अटल काष्ठा file *in_file, *out_file;
अटल loff_t in_pos, out_pos;

अटल पूर्णांक __init prompt_ramdisk(अक्षर *str)
अणु
	pr_warn("ignoring the deprecated prompt_ramdisk= option\n");
	वापस 1;
पूर्ण
__setup("prompt_ramdisk=", prompt_ramdisk);

पूर्णांक __initdata rd_image_start;		/* starting block # of image */

अटल पूर्णांक __init ramdisk_start_setup(अक्षर *str)
अणु
	rd_image_start = simple_म_से_दीर्घ(str,शून्य,0);
	वापस 1;
पूर्ण
__setup("ramdisk_start=", ramdisk_start_setup);

अटल पूर्णांक __init crd_load(decompress_fn deco);

/*
 * This routine tries to find a RAM disk image to load, and वापसs the
 * number of blocks to पढ़ो क्रम a non-compressed image, 0 अगर the image
 * is a compressed image, and -1 अगर an image with the right magic
 * numbers could not be found.
 *
 * We currently check क्रम the following magic numbers:
 *	minix
 *	ext2
 *	romfs
 *	cramfs
 *	squashfs
 *	gzip
 *	bzip2
 *	lzma
 *	xz
 *	lzo
 *	lz4
 */
अटल पूर्णांक __init
identअगरy_ramdisk_image(काष्ठा file *file, loff_t pos,
		decompress_fn *decompressor)
अणु
	स्थिर पूर्णांक size = 512;
	काष्ठा minix_super_block *minixsb;
	काष्ठा romfs_super_block *romfsb;
	काष्ठा cramfs_super *cramfsb;
	काष्ठा squashfs_super_block *squashfsb;
	पूर्णांक nblocks = -1;
	अचिन्हित अक्षर *buf;
	स्थिर अक्षर *compress_name;
	अचिन्हित दीर्घ n;
	पूर्णांक start_block = rd_image_start;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	minixsb = (काष्ठा minix_super_block *) buf;
	romfsb = (काष्ठा romfs_super_block *) buf;
	cramfsb = (काष्ठा cramfs_super *) buf;
	squashfsb = (काष्ठा squashfs_super_block *) buf;
	स_रखो(buf, 0xe5, size);

	/*
	 * Read block 0 to test क्रम compressed kernel
	 */
	pos = start_block * BLOCK_SIZE;
	kernel_पढ़ो(file, buf, size, &pos);

	*decompressor = decompress_method(buf, size, &compress_name);
	अगर (compress_name) अणु
		prपूर्णांकk(KERN_NOTICE "RAMDISK: %s image found at block %d\n",
		       compress_name, start_block);
		अगर (!*decompressor)
			prपूर्णांकk(KERN_EMERG
			       "RAMDISK: %s decompressor not configured!\n",
			       compress_name);
		nblocks = 0;
		जाओ करोne;
	पूर्ण

	/* romfs is at block zero too */
	अगर (romfsb->word0 == ROMSB_WORD0 &&
	    romfsb->word1 == ROMSB_WORD1) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: romfs filesystem found at block %d\n",
		       start_block);
		nblocks = (ntohl(romfsb->size)+BLOCK_SIZE-1)>>BLOCK_SIZE_BITS;
		जाओ करोne;
	पूर्ण

	अगर (cramfsb->magic == CRAMFS_MAGIC) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: cramfs filesystem found at block %d\n",
		       start_block);
		nblocks = (cramfsb->size + BLOCK_SIZE - 1) >> BLOCK_SIZE_BITS;
		जाओ करोne;
	पूर्ण

	/* squashfs is at block zero too */
	अगर (le32_to_cpu(squashfsb->s_magic) == SQUASHFS_MAGIC) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: squashfs filesystem found at block %d\n",
		       start_block);
		nblocks = (le64_to_cpu(squashfsb->bytes_used) + BLOCK_SIZE - 1)
			 >> BLOCK_SIZE_BITS;
		जाओ करोne;
	पूर्ण

	/*
	 * Read 512 bytes further to check अगर cramfs is padded
	 */
	pos = start_block * BLOCK_SIZE + 0x200;
	kernel_पढ़ो(file, buf, size, &pos);

	अगर (cramfsb->magic == CRAMFS_MAGIC) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: cramfs filesystem found at block %d\n",
		       start_block);
		nblocks = (cramfsb->size + BLOCK_SIZE - 1) >> BLOCK_SIZE_BITS;
		जाओ करोne;
	पूर्ण

	/*
	 * Read block 1 to test क्रम minix and ext2 superblock
	 */
	pos = (start_block + 1) * BLOCK_SIZE;
	kernel_पढ़ो(file, buf, size, &pos);

	/* Try minix */
	अगर (minixsb->s_magic == MINIX_SUPER_MAGIC ||
	    minixsb->s_magic == MINIX_SUPER_MAGIC2) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: Minix filesystem found at block %d\n",
		       start_block);
		nblocks = minixsb->s_nzones << minixsb->s_log_zone_size;
		जाओ करोne;
	पूर्ण

	/* Try ext2 */
	n = ext2_image_size(buf);
	अगर (n) अणु
		prपूर्णांकk(KERN_NOTICE
		       "RAMDISK: ext2 filesystem found at block %d\n",
		       start_block);
		nblocks = n;
		जाओ करोne;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE
	       "RAMDISK: Couldn't find valid RAM disk image starting at %d.\n",
	       start_block);

करोne:
	kमुक्त(buf);
	वापस nblocks;
पूर्ण

अटल अचिन्हित दीर्घ nr_blocks(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file->f_mapping->host;

	अगर (!S_ISBLK(inode->i_mode))
		वापस 0;
	वापस i_size_पढ़ो(inode) >> 10;
पूर्ण

पूर्णांक __init rd_load_image(अक्षर *from)
अणु
	पूर्णांक res = 0;
	अचिन्हित दीर्घ rd_blocks, devblocks;
	पूर्णांक nblocks, i;
	अक्षर *buf = शून्य;
	अचिन्हित लघु rotate = 0;
	decompress_fn decompressor = शून्य;
#अगर !defined(CONFIG_S390)
	अक्षर rotator[4] = अणु '|' , '/' , '-' , '\\' पूर्ण;
#पूर्ण_अगर

	out_file = filp_खोलो("/dev/ram", O_RDWR, 0);
	अगर (IS_ERR(out_file))
		जाओ out;

	in_file = filp_खोलो(from, O_RDONLY, 0);
	अगर (IS_ERR(in_file))
		जाओ noबंद_input;

	in_pos = rd_image_start * BLOCK_SIZE;
	nblocks = identअगरy_ramdisk_image(in_file, in_pos, &decompressor);
	अगर (nblocks < 0)
		जाओ करोne;

	अगर (nblocks == 0) अणु
		अगर (crd_load(decompressor) == 0)
			जाओ successful_load;
		जाओ करोne;
	पूर्ण

	/*
	 * NOTE NOTE: nblocks is not actually blocks but
	 * the number of kibibytes of data to load पूर्णांकo a ramdisk.
	 */
	rd_blocks = nr_blocks(out_file);
	अगर (nblocks > rd_blocks) अणु
		prपूर्णांकk("RAMDISK: image too big! (%dKiB/%ldKiB)\n",
		       nblocks, rd_blocks);
		जाओ करोne;
	पूर्ण

	/*
	 * OK, समय to copy in the data
	 */
	अगर (म_भेद(from, "/initrd.image") == 0)
		devblocks = nblocks;
	अन्यथा
		devblocks = nr_blocks(in_file);

	अगर (devblocks == 0) अणु
		prपूर्णांकk(KERN_ERR "RAMDISK: could not determine device size\n");
		जाओ करोne;
	पूर्ण

	buf = kदो_स्मृति(BLOCK_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR "RAMDISK: could not allocate buffer\n");
		जाओ करोne;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "RAMDISK: Loading %dKiB [%ld disk%s] into ram disk... ",
		nblocks, ((nblocks-1)/devblocks)+1, nblocks>devblocks ? "s" : "");
	क्रम (i = 0; i < nblocks; i++) अणु
		अगर (i && (i % devblocks == 0)) अणु
			pr_cont("done disk #1.\n");
			rotate = 0;
			fput(in_file);
			अवरोध;
		पूर्ण
		kernel_पढ़ो(in_file, buf, BLOCK_SIZE, &in_pos);
		kernel_ग_लिखो(out_file, buf, BLOCK_SIZE, &out_pos);
#अगर !defined(CONFIG_S390)
		अगर (!(i % 16)) अणु
			pr_cont("%c\b", rotator[rotate & 0x3]);
			rotate++;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	pr_cont("done.\n");

successful_load:
	res = 1;
करोne:
	fput(in_file);
noबंद_input:
	fput(out_file);
out:
	kमुक्त(buf);
	init_unlink("/dev/ram");
	वापस res;
पूर्ण

पूर्णांक __init rd_load_disk(पूर्णांक n)
अणु
	create_dev("/dev/root", ROOT_DEV);
	create_dev("/dev/ram", MKDEV(RAMDISK_MAJOR, n));
	वापस rd_load_image("/dev/root");
पूर्ण

अटल पूर्णांक निकास_code;
अटल पूर्णांक decompress_error;

अटल दीर्घ __init compr_fill(व्योम *buf, अचिन्हित दीर्घ len)
अणु
	दीर्घ r = kernel_पढ़ो(in_file, buf, len, &in_pos);
	अगर (r < 0)
		prपूर्णांकk(KERN_ERR "RAMDISK: error while reading compressed data");
	अन्यथा अगर (r == 0)
		prपूर्णांकk(KERN_ERR "RAMDISK: EOF while reading compressed data");
	वापस r;
पूर्ण

अटल दीर्घ __init compr_flush(व्योम *winकरोw, अचिन्हित दीर्घ outcnt)
अणु
	दीर्घ written = kernel_ग_लिखो(out_file, winकरोw, outcnt, &out_pos);
	अगर (written != outcnt) अणु
		अगर (decompress_error == 0)
			prपूर्णांकk(KERN_ERR
			       "RAMDISK: incomplete write (%ld != %ld)\n",
			       written, outcnt);
		decompress_error = 1;
		वापस -1;
	पूर्ण
	वापस outcnt;
पूर्ण

अटल व्योम __init error(अक्षर *x)
अणु
	prपूर्णांकk(KERN_ERR "%s\n", x);
	निकास_code = 1;
	decompress_error = 1;
पूर्ण

अटल पूर्णांक __init crd_load(decompress_fn deco)
अणु
	पूर्णांक result;

	अगर (!deco) अणु
		pr_emerg("Invalid ramdisk decompression routine.  "
			 "Select appropriate config option.\n");
		panic("Could not decompress initial ramdisk image.");
	पूर्ण

	result = deco(शून्य, 0, compr_fill, compr_flush, शून्य, शून्य, error);
	अगर (decompress_error)
		result = 1;
	वापस result;
पूर्ण
