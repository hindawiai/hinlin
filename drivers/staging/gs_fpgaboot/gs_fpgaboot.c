<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "gs_fpgaboot.h"
#समावेश "io.h"

#घोषणा DEVICE_NAME "device"
#घोषणा CLASS_NAME  "fpgaboot"

अटल u8 bits_magic[] = अणु
	0x0, 0x9, 0xf, 0xf0, 0xf, 0xf0,
	0xf, 0xf0, 0xf, 0xf0, 0x0, 0x0, 0x1पूर्ण;

/* fake device क्रम request_firmware */
अटल काष्ठा platक्रमm_device	*firmware_pdev;

अटल अक्षर	*file = "xlinx_fpga_firmware.bit";
module_param(file, अक्षरp, 0444);
MODULE_PARM_DESC(file, "Xilinx FPGA firmware file.");

अटल व्योम पढ़ो_bitstream(u8 *bitdata, u8 *buf, पूर्णांक *offset, पूर्णांक rdsize)
अणु
	स_नकल(buf, bitdata + *offset, rdsize);
	*offset += rdsize;
पूर्ण

अटल पूर्णांक पढ़ोinfo_bitstream(u8 *bitdata, u8 *buf, पूर्णांक size, पूर्णांक *offset)
अणु
	u8 tbuf[2];
	u16 len;

	/* पढ़ो section अक्षर */
	पढ़ो_bitstream(bitdata, tbuf, offset, 1);

	/* पढ़ो length */
	पढ़ो_bitstream(bitdata, tbuf, offset, 2);

	len = get_unaligned_be16(tbuf);
	अगर (len >= size) अणु
		pr_err("error: readinfo buffer too small\n");
		वापस -EINVAL;
	पूर्ण

	पढ़ो_bitstream(bitdata, buf, offset, len);
	buf[len] = '\0';

	वापस 0;
पूर्ण

/*
 * पढ़ो bitdata length
 */
अटल पूर्णांक पढ़ोlength_bitstream(u8 *bitdata, पूर्णांक *lendata, पूर्णांक *offset)
अणु
	u8 tbuf[4];

	/* पढ़ो section अक्षर */
	पढ़ो_bitstream(bitdata, tbuf, offset, 1);

	/* make sure it is section 'e' */
	अगर (tbuf[0] != 'e') अणु
		pr_err("error: length section is not 'e', but %c\n", tbuf[0]);
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो 4bytes length */
	पढ़ो_bitstream(bitdata, tbuf, offset, 4);

	*lendata = get_unaligned_be32(tbuf);

	वापस 0;
पूर्ण

/*
 * पढ़ो first 13 bytes to check bitstream magic number
 */
अटल पूर्णांक पढ़ोmagic_bitstream(u8 *bitdata, पूर्णांक *offset)
अणु
	u8 buf[13];
	पूर्णांक r;

	पढ़ो_bitstream(bitdata, buf, offset, 13);
	r = स_भेद(buf, bits_magic, 13);
	अगर (r) अणु
		pr_err("error: corrupted header\n");
		वापस -EINVAL;
	पूर्ण
	pr_info("bitstream file magic number Ok\n");

	*offset = 13;	/* magic length */

	वापस 0;
पूर्ण

/*
 * NOTE: supports only bitstream क्रमmat
 */
अटल क्रमागत fmt_image get_imageक्रमmat(व्योम)
अणु
	वापस f_bit;
पूर्ण

अटल व्योम gs_prपूर्णांक_header(काष्ठा fpgaimage *fimage)
अणु
	pr_info("file: %s\n", fimage->filename);
	pr_info("part: %s\n", fimage->part);
	pr_info("date: %s\n", fimage->date);
	pr_info("time: %s\n", fimage->समय);
	pr_info("lendata: %d\n", fimage->lendata);
पूर्ण

अटल पूर्णांक gs_पढ़ो_bitstream(काष्ठा fpgaimage *fimage)
अणु
	u8 *bitdata;
	पूर्णांक offset;
	पूर्णांक err;

	offset = 0;
	bitdata = (u8 *)fimage->fw_entry->data;

	err = पढ़ोmagic_bitstream(bitdata, &offset);
	अगर (err)
		वापस err;

	err = पढ़ोinfo_bitstream(bitdata, fimage->filename, MAX_STR, &offset);
	अगर (err)
		वापस err;
	err = पढ़ोinfo_bitstream(bitdata, fimage->part, MAX_STR, &offset);
	अगर (err)
		वापस err;
	err = पढ़ोinfo_bitstream(bitdata, fimage->date, MAX_STR, &offset);
	अगर (err)
		वापस err;
	err = पढ़ोinfo_bitstream(bitdata, fimage->समय, MAX_STR, &offset);
	अगर (err)
		वापस err;

	err = पढ़ोlength_bitstream(bitdata, &fimage->lendata, &offset);
	अगर (err)
		वापस err;

	fimage->fpgadata = bitdata + offset;

	वापस 0;
पूर्ण

अटल पूर्णांक gs_पढ़ो_image(काष्ठा fpgaimage *fimage)
अणु
	पूर्णांक img_fmt;
	पूर्णांक err;

	img_fmt = get_imageक्रमmat();

	चयन (img_fmt) अणु
	हाल f_bit:
		pr_info("image is bitstream format\n");
		err = gs_पढ़ो_bitstream(fimage);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		pr_err("unsupported fpga image format\n");
		वापस -EINVAL;
	पूर्ण

	gs_prपूर्णांक_header(fimage);

	वापस 0;
पूर्ण

अटल पूर्णांक gs_load_image(काष्ठा fpgaimage *fimage, अक्षर *fw_file)
अणु
	पूर्णांक err;

	pr_info("load fpgaimage %s\n", fw_file);

	err = request_firmware(&fimage->fw_entry, fw_file, &firmware_pdev->dev);
	अगर (err != 0) अणु
		pr_err("firmware %s is missing, cannot continue.\n", fw_file);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gs_करोwnload_image(काष्ठा fpgaimage *fimage, क्रमागत wbus bus_bytes)
अणु
	u8 *bitdata;
	पूर्णांक size, i, cnt;

	cnt = 0;
	bitdata = (u8 *)fimage->fpgadata;
	size = fimage->lendata;

#अगर_घोषित DEBUG_FPGA
	prपूर्णांक_hex_dump_bytes("bitfile sample: ", DUMP_PREFIX_OFFSET,
			     bitdata, 0x100);
#पूर्ण_अगर /* DEBUG_FPGA */
	अगर (!xl_supported_prog_bus_width(bus_bytes)) अणु
		pr_err("unsupported program bus width %d\n",
		       bus_bytes);
		वापस -EINVAL;
	पूर्ण

	/* Bring csi_b, rdwr_b Low and program_b High */
	xl_program_b(1);
	xl_rdwr_b(0);
	xl_csi_b(0);

	/* Configuration reset */
	xl_program_b(0);
	msleep(20);
	xl_program_b(1);

	/* Wait क्रम Device Initialization */
	जबतक (xl_get_init_b() == 0)
		;

	pr_info("device init done\n");

	क्रम (i = 0; i < size; i += bus_bytes)
		xl_shअगरt_bytes_out(bus_bytes, bitdata + i);

	pr_info("program done\n");

	/* Check INIT_B */
	अगर (xl_get_init_b() == 0) अणु
		pr_err("init_b 0\n");
		वापस -EIO;
	पूर्ण

	जबतक (xl_get_करोne_b() == 0) अणु
		अगर (cnt++ > MAX_WAIT_DONE) अणु
			pr_err("init_B %d\n", xl_get_init_b());
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cnt > MAX_WAIT_DONE) अणु
		pr_err("fpga download fail\n");
		वापस -EIO;
	पूर्ण

	pr_info("download fpgaimage\n");

	/* Compensate क्रम Special Startup Conditions */
	xl_shअगरt_cclk(8);

	वापस 0;
पूर्ण

अटल पूर्णांक gs_release_image(काष्ठा fpgaimage *fimage)
अणु
	release_firmware(fimage->fw_entry);
	pr_info("release fpgaimage\n");

	वापस 0;
पूर्ण

/*
 * NOTE: supports प्रणालीmap parallel programming
 */
अटल पूर्णांक gs_set_करोwnload_method(काष्ठा fpgaimage *fimage)
अणु
	pr_info("set program method\n");

	fimage->dmethod = m_प्रणालीmap;

	pr_info("systemmap program method\n");

	वापस 0;
पूर्ण

अटल पूर्णांक init_driver(व्योम)
अणु
	firmware_pdev = platक्रमm_device_रेजिस्टर_simple("fpgaboot", -1,
							शून्य, 0);
	वापस PTR_ERR_OR_ZERO(firmware_pdev);
पूर्ण

अटल पूर्णांक gs_fpgaboot(व्योम)
अणु
	पूर्णांक err;
	काष्ठा fpgaimage	*fimage;

	fimage = kदो_स्मृति(माप(*fimage), GFP_KERNEL);
	अगर (!fimage)
		वापस -ENOMEM;

	err = gs_load_image(fimage, file);
	अगर (err) अणु
		pr_err("gs_load_image error\n");
		जाओ err_out1;
	पूर्ण

	err = gs_पढ़ो_image(fimage);
	अगर (err) अणु
		pr_err("gs_read_image error\n");
		जाओ err_out2;
	पूर्ण

	err = gs_set_करोwnload_method(fimage);
	अगर (err) अणु
		pr_err("gs_set_download_method error\n");
		जाओ err_out2;
	पूर्ण

	err = gs_करोwnload_image(fimage, bus_2byte);
	अगर (err) अणु
		pr_err("gs_download_image error\n");
		जाओ err_out2;
	पूर्ण

	err = gs_release_image(fimage);
	अगर (err) अणु
		pr_err("gs_release_image error\n");
		जाओ err_out1;
	पूर्ण

	kमुक्त(fimage);
	वापस 0;

err_out2:
	err = gs_release_image(fimage);
	अगर (err)
		pr_err("gs_release_image error\n");
err_out1:
	kमुक्त(fimage);

	वापस err;
पूर्ण

अटल पूर्णांक __init gs_fpgaboot_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("FPGA DOWNLOAD --->\n");

	pr_info("FPGA image file name: %s\n", file);

	err = init_driver();
	अगर (err) अणु
		pr_err("FPGA DRIVER INIT FAIL!!\n");
		वापस err;
	पूर्ण

	err = xl_init_io();
	अगर (err) अणु
		pr_err("GPIO INIT FAIL!!\n");
		जाओ errout;
	पूर्ण

	err = gs_fpgaboot();
	अगर (err) अणु
		pr_err("FPGA DOWNLOAD FAIL!!\n");
		जाओ errout;
	पूर्ण

	pr_info("FPGA DOWNLOAD DONE <---\n");

	वापस 0;

errout:
	platक्रमm_device_unरेजिस्टर(firmware_pdev);

	वापस err;
पूर्ण

अटल व्योम __निकास gs_fpgaboot_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(firmware_pdev);
	pr_info("FPGA image download module removed\n");
पूर्ण

module_init(gs_fpgaboot_init);
module_निकास(gs_fpgaboot_निकास);

MODULE_AUTHOR("Insop Song");
MODULE_DESCRIPTION("Xlinix FPGA firmware download");
MODULE_LICENSE("GPL");
