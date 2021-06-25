<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __COW_H__
#घोषणा __COW_H__

#समावेश <यंत्र/types.h>

बाह्य पूर्णांक init_cow_file(पूर्णांक fd, अक्षर *cow_file, अक्षर *backing_file,
			 पूर्णांक sectorsize, पूर्णांक alignment, पूर्णांक *biपंचांगap_offset_out,
			 अचिन्हित दीर्घ *biपंचांगap_len_out, पूर्णांक *data_offset_out);

बाह्य पूर्णांक file_पढ़ोer(__u64 offset, अक्षर *buf, पूर्णांक len, व्योम *arg);
बाह्य पूर्णांक पढ़ो_cow_header(पूर्णांक (*पढ़ोer)(__u64, अक्षर *, पूर्णांक, व्योम *),
			   व्योम *arg, __u32 *version_out,
			   अक्षर **backing_file_out, दीर्घ दीर्घ *mसमय_out,
			   अचिन्हित दीर्घ दीर्घ *size_out, पूर्णांक *sectorsize_out,
			   __u32 *align_out, पूर्णांक *biपंचांगap_offset_out);

बाह्य पूर्णांक ग_लिखो_cow_header(अक्षर *cow_file, पूर्णांक fd, अक्षर *backing_file,
			    पूर्णांक sectorsize, पूर्णांक alignment,
			    अचिन्हित दीर्घ दीर्घ *size);

बाह्य व्योम cow_sizes(पूर्णांक version, __u64 size, पूर्णांक sectorsize, पूर्णांक align,
		      पूर्णांक biपंचांगap_offset, अचिन्हित दीर्घ *biपंचांगap_len_out,
		      पूर्णांक *data_offset_out);

#पूर्ण_अगर
