<शैली गुरु>
/*
 * XZ decoder tester
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/crc32.h>
#समावेश <linux/xz.h>

/* Maximum supported dictionary size */
#घोषणा DICT_MAX (1 << 20)

/* Device name to pass to रेजिस्टर_chrdev(). */
#घोषणा DEVICE_NAME "xz_dec_test"

/* Dynamically allocated device major number */
अटल पूर्णांक device_major;

/*
 * We reuse the same decoder state, and thus can decode only one
 * file at a समय.
 */
अटल bool device_is_खोलो;

/* XZ decoder state */
अटल काष्ठा xz_dec *state;

/*
 * Return value of xz_dec_run(). We need to aव्योम calling xz_dec_run() after
 * it has वापसed XZ_STREAM_END, so we make this अटल.
 */
अटल क्रमागत xz_ret ret;

/*
 * Input and output buffers. The input buffer is used as a temporary safe
 * place क्रम the data coming from the userspace.
 */
अटल uपूर्णांक8_t buffer_in[1024];
अटल uपूर्णांक8_t buffer_out[1024];

/*
 * Structure to pass the input and output buffers to the XZ decoder.
 * A few of the fields are never modअगरied so we initialize them here.
 */
अटल काष्ठा xz_buf buffers = अणु
	.in = buffer_in,
	.out = buffer_out,
	.out_size = माप(buffer_out)
पूर्ण;

/*
 * CRC32 of uncompressed data. This is used to give the user a simple way
 * to check that the decoder produces correct output.
 */
अटल uपूर्णांक32_t crc;

अटल पूर्णांक xz_dec_test_खोलो(काष्ठा inode *i, काष्ठा file *f)
अणु
	अगर (device_is_खोलो)
		वापस -EBUSY;

	device_is_खोलो = true;

	xz_dec_reset(state);
	ret = XZ_OK;
	crc = 0xFFFFFFFF;

	buffers.in_pos = 0;
	buffers.in_size = 0;
	buffers.out_pos = 0;

	prपूर्णांकk(KERN_INFO DEVICE_NAME ": opened\n");
	वापस 0;
पूर्ण

अटल पूर्णांक xz_dec_test_release(काष्ठा inode *i, काष्ठा file *f)
अणु
	device_is_खोलो = false;

	अगर (ret == XZ_OK)
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": input was truncated\n");

	prपूर्णांकk(KERN_INFO DEVICE_NAME ": closed\n");
	वापस 0;
पूर्ण

/*
 * Decode the data given to us from the userspace. CRC32 of the uncompressed
 * data is calculated and is prपूर्णांकed at the end of successful decoding. The
 * uncompressed data isn't stored anywhere क्रम further use.
 *
 * The .xz file must have exactly one Stream and no Stream Padding. The data
 * after the first Stream is considered to be garbage.
 */
अटल sमाप_प्रकार xz_dec_test_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	माप_प्रकार reमुख्यing;

	अगर (ret != XZ_OK) अणु
		अगर (size > 0)
			prपूर्णांकk(KERN_INFO DEVICE_NAME ": %zu bytes of "
					"garbage at the end of the file\n",
					size);

		वापस -ENOSPC;
	पूर्ण

	prपूर्णांकk(KERN_INFO DEVICE_NAME ": decoding %zu bytes of input\n",
			size);

	reमुख्यing = size;
	जबतक ((reमुख्यing > 0 || buffers.out_pos == buffers.out_size)
			&& ret == XZ_OK) अणु
		अगर (buffers.in_pos == buffers.in_size) अणु
			buffers.in_pos = 0;
			buffers.in_size = min(reमुख्यing, माप(buffer_in));
			अगर (copy_from_user(buffer_in, buf, buffers.in_size))
				वापस -EFAULT;

			buf += buffers.in_size;
			reमुख्यing -= buffers.in_size;
		पूर्ण

		buffers.out_pos = 0;
		ret = xz_dec_run(state, &buffers);
		crc = crc32(crc, buffer_out, buffers.out_pos);
	पूर्ण

	चयन (ret) अणु
	हाल XZ_OK:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_OK\n");
		वापस size;

	हाल XZ_STREAM_END:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_STREAM_END, "
				"CRC32 = 0x%08X\n", ~crc);
		वापस size - reमुख्यing - (buffers.in_size - buffers.in_pos);

	हाल XZ_MEMLIMIT_ERROR:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_MEMLIMIT_ERROR\n");
		अवरोध;

	हाल XZ_FORMAT_ERROR:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_FORMAT_ERROR\n");
		अवरोध;

	हाल XZ_OPTIONS_ERROR:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_OPTIONS_ERROR\n");
		अवरोध;

	हाल XZ_DATA_ERROR:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_DATA_ERROR\n");
		अवरोध;

	हाल XZ_BUF_ERROR:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": XZ_BUF_ERROR\n");
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_INFO DEVICE_NAME ": Bug detected!\n");
		अवरोध;
	पूर्ण

	वापस -EIO;
पूर्ण

/* Allocate the XZ decoder state and रेजिस्टर the अक्षरacter device. */
अटल पूर्णांक __init xz_dec_test_init(व्योम)
अणु
	अटल स्थिर काष्ठा file_operations fileops = अणु
		.owner = THIS_MODULE,
		.खोलो = &xz_dec_test_खोलो,
		.release = &xz_dec_test_release,
		.ग_लिखो = &xz_dec_test_ग_लिखो
	पूर्ण;

	state = xz_dec_init(XZ_PREALLOC, DICT_MAX);
	अगर (state == शून्य)
		वापस -ENOMEM;

	device_major = रेजिस्टर_chrdev(0, DEVICE_NAME, &fileops);
	अगर (device_major < 0) अणु
		xz_dec_end(state);
		वापस device_major;
	पूर्ण

	prपूर्णांकk(KERN_INFO DEVICE_NAME ": module loaded\n");
	prपूर्णांकk(KERN_INFO DEVICE_NAME ": Create a device node with "
			"'mknod " DEVICE_NAME " c %d 0' and write .xz files "
			"to it.\n", device_major);
	वापस 0;
पूर्ण

अटल व्योम __निकास xz_dec_test_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev(device_major, DEVICE_NAME);
	xz_dec_end(state);
	prपूर्णांकk(KERN_INFO DEVICE_NAME ": module unloaded\n");
पूर्ण

module_init(xz_dec_test_init);
module_निकास(xz_dec_test_निकास);

MODULE_DESCRIPTION("XZ decompressor tester");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Lasse Collin <lasse.collin@tukaani.org>");

/*
 * This code is in the खुला करोमुख्य, but in Linux it's simplest to just
 * say it's GPL and consider the authors as the copyright holders.
 */
MODULE_LICENSE("GPL");
