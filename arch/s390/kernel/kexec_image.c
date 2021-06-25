<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Image loader क्रम kexec_file_load प्रणाली call.
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Philipp Ruकरो <pruकरो@linux.vnet.ibm.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/setup.h>

अटल पूर्णांक kexec_file_add_kernel_image(काष्ठा kimage *image,
				       काष्ठा s390_load_data *data)
अणु
	काष्ठा kexec_buf buf;

	buf.image = image;

	buf.buffer = image->kernel_buf;
	buf.bufsz = image->kernel_buf_len;

	buf.mem = 0;
	अगर (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	data->kernel_buf = image->kernel_buf;
	data->kernel_mem = buf.mem;
	data->parm = image->kernel_buf + PARMAREA;
	data->memsz += buf.memsz;

	ipl_report_add_component(data->report, &buf,
				 IPL_RB_COMPONENT_FLAG_SIGNED |
				 IPL_RB_COMPONENT_FLAG_VERIFIED,
				 IPL_RB_CERT_UNKNOWN);
	वापस kexec_add_buffer(&buf);
पूर्ण

अटल व्योम *s390_image_load(काष्ठा kimage *image,
			     अक्षर *kernel, अचिन्हित दीर्घ kernel_len,
			     अक्षर *initrd, अचिन्हित दीर्घ initrd_len,
			     अक्षर *cmdline, अचिन्हित दीर्घ cmdline_len)
अणु
	वापस kexec_file_add_components(image, kexec_file_add_kernel_image);
पूर्ण

अटल पूर्णांक s390_image_probe(स्थिर अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	/* Can't reliably tell अगर an image is valid.  Thereक्रमe give the
	 * user whatever he wants.
	 */
	वापस 0;
पूर्ण

स्थिर काष्ठा kexec_file_ops s390_kexec_image_ops = अणु
	.probe = s390_image_probe,
	.load = s390_image_load,
#अगर_घोषित CONFIG_KEXEC_SIG
	.verअगरy_sig = s390_verअगरy_sig,
#पूर्ण_अगर /* CONFIG_KEXEC_SIG */
पूर्ण;
