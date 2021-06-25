<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित PERF_COPYखाता_H_
#घोषणा PERF_COPYखाता_H_

#समावेश <linux/types.h>
#समावेश <sys/types.h>
#समावेश <fcntl.h>

काष्ठा nsinfo;

पूर्णांक copyfile(स्थिर अक्षर *from, स्थिर अक्षर *to);
पूर्णांक copyfile_mode(स्थिर अक्षर *from, स्थिर अक्षर *to, mode_t mode);
पूर्णांक copyfile_ns(स्थिर अक्षर *from, स्थिर अक्षर *to, काष्ठा nsinfo *nsi);
पूर्णांक copyfile_offset(पूर्णांक अगरd, loff_t off_in, पूर्णांक ofd, loff_t off_out, u64 size);

#पूर्ण_अगर // PERF_COPYखाता_H_
