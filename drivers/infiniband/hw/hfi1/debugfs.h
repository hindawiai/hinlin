<शैली गुरु>
#अगर_अघोषित _HFI1_DEBUGFS_H
#घोषणा _HFI1_DEBUGFS_H
/*
 * Copyright(c) 2015, 2016, 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

काष्ठा hfi1_ibdev;

#घोषणा DEBUGFS_SEQ_खाता_OPS(name) \
अटल स्थिर काष्ठा seq_operations _##name##_seq_ops = अणु \
	.start = _##name##_seq_start, \
	.next  = _##name##_seq_next, \
	.stop  = _##name##_seq_stop, \
	.show  = _##name##_seq_show \
पूर्ण

#घोषणा DEBUGFS_SEQ_खाता_OPEN(name) \
अटल पूर्णांक _##name##_खोलो(काष्ठा inode *inode, काष्ठा file *s) \
अणु \
	काष्ठा seq_file *seq; \
	पूर्णांक ret; \
	ret =  seq_खोलो(s, &_##name##_seq_ops); \
	अगर (ret) \
		वापस ret; \
	seq = s->निजी_data; \
	seq->निजी = inode->i_निजी; \
	वापस 0; \
पूर्ण

#घोषणा DEBUGFS_खाता_OPS(name) \
अटल स्थिर काष्ठा file_operations _##name##_file_ops = अणु \
	.owner   = THIS_MODULE, \
	.खोलो    = _##name##_खोलो, \
	.पढ़ो    = hfi1_seq_पढ़ो, \
	.llseek  = hfi1_seq_lseek, \
	.release = seq_release \
पूर्ण


sमाप_प्रकार hfi1_seq_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
		      loff_t *ppos);
loff_t hfi1_seq_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम hfi1_dbg_ibdev_init(काष्ठा hfi1_ibdev *ibd);
व्योम hfi1_dbg_ibdev_निकास(काष्ठा hfi1_ibdev *ibd);
व्योम hfi1_dbg_init(व्योम);
व्योम hfi1_dbg_निकास(व्योम);

#अन्यथा
अटल अंतरभूत व्योम hfi1_dbg_ibdev_init(काष्ठा hfi1_ibdev *ibd)
अणु
पूर्ण

अटल अंतरभूत व्योम hfi1_dbg_ibdev_निकास(काष्ठा hfi1_ibdev *ibd)
अणु
पूर्ण

अटल अंतरभूत व्योम hfi1_dbg_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम hfi1_dbg_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर                          /* _HFI1_DEBUGFS_H */
