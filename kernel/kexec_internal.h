<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_KEXEC_INTERNAL_H
#घोषणा LINUX_KEXEC_INTERNAL_H

#समावेश <linux/kexec.h>

काष्ठा kimage *करो_kimage_alloc_init(व्योम);
पूर्णांक sanity_check_segment_list(काष्ठा kimage *image);
व्योम kimage_मुक्त_page_list(काष्ठा list_head *list);
व्योम kimage_मुक्त(काष्ठा kimage *image);
पूर्णांक kimage_load_segment(काष्ठा kimage *image, काष्ठा kexec_segment *segment);
व्योम kimage_terminate(काष्ठा kimage *image);
पूर्णांक kimage_is_destination_range(काष्ठा kimage *image,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

बाह्य काष्ठा mutex kexec_mutex;

#अगर_घोषित CONFIG_KEXEC_खाता
#समावेश <linux/purgatory.h>
व्योम kimage_file_post_load_cleanup(काष्ठा kimage *image);
बाह्य अक्षर kexec_purgatory[];
बाह्य माप_प्रकार kexec_purgatory_size;
#अन्यथा /* CONFIG_KEXEC_खाता */
अटल अंतरभूत व्योम kimage_file_post_load_cleanup(काष्ठा kimage *image) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_खाता */
#पूर्ण_अगर /* LINUX_KEXEC_INTERNAL_H */
