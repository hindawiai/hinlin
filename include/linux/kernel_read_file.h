<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KERNEL_READ_खाता_H
#घोषणा _LINUX_KERNEL_READ_खाता_H

#समावेश <linux/file.h>
#समावेश <linux/types.h>

/* This is a list of *what* is being पढ़ो, not *how* nor *where*. */
#घोषणा __kernel_पढ़ो_file_id(id) \
	id(UNKNOWN, unknown)		\
	id(FIRMWARE, firmware)		\
	id(MODULE, kernel-module)		\
	id(KEXEC_IMAGE, kexec-image)		\
	id(KEXEC_INITRAMFS, kexec-initramfs)	\
	id(POLICY, security-policy)		\
	id(X509_CERTIFICATE, x509-certअगरicate)	\
	id(MAX_ID, )

#घोषणा __fid_क्रमागतअगरy(ENUM, dummy) READING_ ## ENUM,
#घोषणा __fid_stringअगरy(dummy, str) #str,

क्रमागत kernel_पढ़ो_file_id अणु
	__kernel_पढ़ो_file_id(__fid_क्रमागतअगरy)
पूर्ण;

अटल स्थिर अक्षर * स्थिर kernel_पढ़ो_file_str[] = अणु
	__kernel_पढ़ो_file_id(__fid_stringअगरy)
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *kernel_पढ़ो_file_id_str(क्रमागत kernel_पढ़ो_file_id id)
अणु
	अगर ((अचिन्हित पूर्णांक)id >= READING_MAX_ID)
		वापस kernel_पढ़ो_file_str[READING_UNKNOWN];

	वापस kernel_पढ़ो_file_str[id];
पूर्ण

पूर्णांक kernel_पढ़ो_file(काष्ठा file *file, loff_t offset,
		     व्योम **buf, माप_प्रकार buf_size,
		     माप_प्रकार *file_size,
		     क्रमागत kernel_पढ़ो_file_id id);
पूर्णांक kernel_पढ़ो_file_from_path(स्थिर अक्षर *path, loff_t offset,
			       व्योम **buf, माप_प्रकार buf_size,
			       माप_प्रकार *file_size,
			       क्रमागत kernel_पढ़ो_file_id id);
पूर्णांक kernel_पढ़ो_file_from_path_initns(स्थिर अक्षर *path, loff_t offset,
				      व्योम **buf, माप_प्रकार buf_size,
				      माप_प्रकार *file_size,
				      क्रमागत kernel_पढ़ो_file_id id);
पूर्णांक kernel_पढ़ो_file_from_fd(पूर्णांक fd, loff_t offset,
			     व्योम **buf, माप_प्रकार buf_size,
			     माप_प्रकार *file_size,
			     क्रमागत kernel_पढ़ो_file_id id);

#पूर्ण_अगर /* _LINUX_KERNEL_READ_खाता_H */
