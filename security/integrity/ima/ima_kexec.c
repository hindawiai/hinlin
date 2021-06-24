<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 IBM Corporation
 *
 * Authors:
 * Thiago Jung Bauermann <bauerman@linux.vnet.ibm.com>
 * Mimi Zohar <zohar@linux.vnet.ibm.com>
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kexec.h>
#समावेश <linux/of.h>
#समावेश "ima.h"

#अगर_घोषित CONFIG_IMA_KEXEC
अटल पूर्णांक ima_dump_measurement_list(अचिन्हित दीर्घ *buffer_size, व्योम **buffer,
				     अचिन्हित दीर्घ segment_size)
अणु
	काष्ठा ima_queue_entry *qe;
	काष्ठा seq_file file;
	काष्ठा ima_kexec_hdr khdr;
	पूर्णांक ret = 0;

	/* segment size can't change between kexec load and execute */
	file.buf = vदो_स्मृति(segment_size);
	अगर (!file.buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	file.size = segment_size;
	file.पढ़ो_pos = 0;
	file.count = माप(khdr);	/* reserved space */

	स_रखो(&khdr, 0, माप(khdr));
	khdr.version = 1;
	list_क्रम_each_entry_rcu(qe, &ima_measurements, later) अणु
		अगर (file.count < file.size) अणु
			khdr.count++;
			ima_measurements_show(&file, qe);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		जाओ out;

	/*
	 * fill in reserved space with some buffer details
	 * (eg. version, buffer size, number of measurements)
	 */
	khdr.buffer_size = file.count;
	अगर (ima_canonical_fmt) अणु
		khdr.version = cpu_to_le16(khdr.version);
		khdr.count = cpu_to_le64(khdr.count);
		khdr.buffer_size = cpu_to_le64(khdr.buffer_size);
	पूर्ण
	स_नकल(file.buf, &khdr, माप(khdr));

	prपूर्णांक_hex_dump(KERN_DEBUG, "ima dump: ", DUMP_PREFIX_NONE,
			16, 1, file.buf,
			file.count < 100 ? file.count : 100, true);

	*buffer_size = file.count;
	*buffer = file.buf;
out:
	अगर (ret == -EINVAL)
		vमुक्त(file.buf);
	वापस ret;
पूर्ण

/*
 * Called during kexec_file_load so that IMA can add a segment to the kexec
 * image क्रम the measurement list क्रम the next kernel.
 *
 * This function assumes that kexec_mutex is held.
 */
व्योम ima_add_kexec_buffer(काष्ठा kimage *image)
अणु
	काष्ठा kexec_buf kbuf = अणु .image = image, .buf_align = PAGE_SIZE,
				  .buf_min = 0, .buf_max = अच_दीर्घ_उच्च,
				  .top_करोwn = true पूर्ण;
	अचिन्हित दीर्घ binary_runसमय_size;

	/* use more understandable variable names than defined in kbuf */
	व्योम *kexec_buffer = शून्य;
	माप_प्रकार kexec_buffer_size;
	माप_प्रकार kexec_segment_size;
	पूर्णांक ret;

	/*
	 * Reserve an extra half page of memory क्रम additional measurements
	 * added during the kexec load.
	 */
	binary_runसमय_size = ima_get_binary_runसमय_size();
	अगर (binary_runसमय_size >= अच_दीर्घ_उच्च - PAGE_SIZE)
		kexec_segment_size = अच_दीर्घ_उच्च;
	अन्यथा
		kexec_segment_size = ALIGN(ima_get_binary_runसमय_size() +
					   PAGE_SIZE / 2, PAGE_SIZE);
	अगर ((kexec_segment_size == अच_दीर्घ_उच्च) ||
	    ((kexec_segment_size >> PAGE_SHIFT) > totalram_pages() / 2)) अणु
		pr_err("Binary measurement list too large.\n");
		वापस;
	पूर्ण

	ima_dump_measurement_list(&kexec_buffer_size, &kexec_buffer,
				  kexec_segment_size);
	अगर (!kexec_buffer) अणु
		pr_err("Not enough memory for the kexec measurement buffer.\n");
		वापस;
	पूर्ण

	kbuf.buffer = kexec_buffer;
	kbuf.bufsz = kexec_buffer_size;
	kbuf.memsz = kexec_segment_size;
	ret = kexec_add_buffer(&kbuf);
	अगर (ret) अणु
		pr_err("Error passing over kexec measurement buffer.\n");
		vमुक्त(kexec_buffer);
		वापस;
	पूर्ण

	image->ima_buffer_addr = kbuf.mem;
	image->ima_buffer_size = kexec_segment_size;
	image->ima_buffer = kexec_buffer;

	pr_debug("kexec measurement buffer for the loaded kernel at 0x%lx.\n",
		 kbuf.mem);
पूर्ण
#पूर्ण_अगर /* IMA_KEXEC */

/*
 * Restore the measurement list from the previous kernel.
 */
व्योम ima_load_kexec_buffer(व्योम)
अणु
	व्योम *kexec_buffer = शून्य;
	माप_प्रकार kexec_buffer_size = 0;
	पूर्णांक rc;

	rc = ima_get_kexec_buffer(&kexec_buffer, &kexec_buffer_size);
	चयन (rc) अणु
	हाल 0:
		rc = ima_restore_measurement_list(kexec_buffer_size,
						  kexec_buffer);
		अगर (rc != 0)
			pr_err("Failed to restore the measurement list: %d\n",
				rc);

		ima_मुक्त_kexec_buffer();
		अवरोध;
	हाल -ENOTSUPP:
		pr_debug("Restoring the measurement list not supported\n");
		अवरोध;
	हाल -ENOENT:
		pr_debug("No measurement list to restore\n");
		अवरोध;
	शेष:
		pr_debug("Error restoring the measurement list: %d\n", rc);
	पूर्ण
पूर्ण
