<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FSNOTIFY_FDINFO_H__
#घोषणा __FSNOTIFY_FDINFO_H__

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>

काष्ठा seq_file;
काष्ठा file;

#अगर_घोषित CONFIG_PROC_FS

#अगर_घोषित CONFIG_INOTIFY_USER
व्योम inotअगरy_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FANOTIFY
व्योम fanotअगरy_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f);
#पूर्ण_अगर

#अन्यथा /* CONFIG_PROC_FS */

#घोषणा inotअगरy_show_fdinfo	शून्य
#घोषणा fanotअगरy_show_fdinfo	शून्य

#पूर्ण_अगर /* CONFIG_PROC_FS */

#पूर्ण_अगर /* __FSNOTIFY_FDINFO_H__ */
